//Steel -LinzerSchnitte Entangled Sparks Transmitter Software
//Josh Gardiner
//2014 06 05
//Copyright (C) Josh Gardiner 2014
/*
	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <netdb.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <assert.h>
#include "sparkfunc.h"
#include <unistd.h>
#include "i2c_bitbang.h"

#define BUFSIZE 2048
float version = 1.00;

uint32_t frameid;
uint32_t data01 = 0;
uint32_t data02 = 0;
uint32_t data03 = 0;
uint32_t data04 = 0;
uint32_t last_data01 = 0;
uint32_t last_data02 = 0;
uint32_t last_data03 = 0;
uint32_t last_data04 = 0;
double timestamp = 0;
int wait=80000;

void processData(char *message, int messageLength);
void sendRDS();

int main(int argc, char **argv)
{
	fprintf(stderr, "Steel:Entangled Sparks: FM Transmitter Contoller for Entagngled Sparks Version %1.2f\n", version);
	fprintf(stderr, "Copyright (C)2014 Josh Gardiner josh@zool.com\n");
	fprintf(stderr, "\nThis program comes with ABSOLUTELY NO WARRANTY; for details type -w\n");
	fprintf(stderr, "This is free software, and you are welcome to redistribute it\n");
	fprintf(stderr, "under certain conditions; type -c for details.\n");
	fprintf(stderr, "\ntype -h for help\n\n");


	int cmd_option;
	int port = 1535;

	while((cmd_option=getopt(argc, argv, "hp:wcd:")) != EOF)
	switch(cmd_option)
	{
		default:
		case 'h': print_steel_help(); 
		case 'p': port=atoi(optarg); break;
		case 'w': print_warranty();
		case 'c': print_conditions();
		case 'd': wait=atoi(optarg); break;
	}

	struct sockaddr_in myaddr;
	struct sockaddr_in remaddr;
	socklen_t addrlen = sizeof(remaddr);
	int recvlen;
	int fd;

	char buf[BUFSIZE];

	if (gpioSetup() != OK)
	{
			dbgPrint(DBG_INFO, "gpioSetup failed. Exiting\n");
			return 1;
	}

	LS_CMD(10,0xffff,0);
	sleep(1);
	LS_CMD(10,0xffff,0);
	sleep(1);
	RDS_CONFIG();
	sleep(1);
	RDS_ENABLE_UDG1();
	sleep(1);

//	RDS_SET_PS();
//	sleep(1);

	if ((fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
		perror("cannot create socket\n");
		return 0;
	}

	memset((char *)&myaddr, 0, sizeof(myaddr));
	myaddr.sin_family = AF_INET;
	myaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	myaddr.sin_port = htons(port);

	if (bind(fd, (struct sockaddr *)&myaddr, sizeof(myaddr)) < 0) {
		perror("bind failed");
		return 0;
	}

	printf("waiting on port %d\n", port);

	for (;;) {
		recvlen = recvfrom(fd, buf, BUFSIZE, 0, (struct sockaddr *)&remaddr, &addrlen);
		// system("clear");
		if (recvlen > 0) {
			buf[recvlen] = 0;
			processData(buf,recvlen);
			sendRDS();
		}
		else {
			printf("uh oh - something went wrong!\n");
		}
		sprintf(buf, "FRAMEID=%d\n%6.6f\n", frameid, getTime());
		printf("sending response %s", buf);
		if (sendto(fd, buf, strlen(buf), 0, (struct sockaddr *)&remaddr, addrlen) < 0)
			perror("sendto");

	}

}



void processData(char *message, int messageLength)
{
	char FRAMEIDstr[100], TIMESTAMPstr[100], DATA01str[100], DATA02str[100], DATA03str[100], DATA04str[100];

	sscanf(message, "%s %s %s %s %s %s",FRAMEIDstr, TIMESTAMPstr, DATA01str, DATA02str, DATA03str, DATA04str);

	fprintf(stderr, "%s\n %s\n %s\n %s\n %s\n %s\n",FRAMEIDstr, TIMESTAMPstr, DATA01str, DATA02str, DATA03str, DATA04str);

	char *data;
	const char delim[2] = "=";

	if (memcmp(FRAMEIDstr,"FRAMEID=",8)==0 ) {
		data = split(FRAMEIDstr,delim);
		frameid = atoi(data);
		fprintf(stderr,"FRAMEID=%d\n",frameid);
	}
	if (memcmp(TIMESTAMPstr,"TIMESTAMP=",10)==0 ) {
		data = split(TIMESTAMPstr,delim);
		timestamp = atof(data);
		fprintf(stderr,"TIMESTAMP=%6.6f\n",timestamp);
	}
	if (memcmp(DATA01str,"DATA01=",7)==0 ) {
		data = split(DATA01str,delim);
		data01 = atoi(data);
		fprintf(stderr,"%08X = ",data01);
		printbitssimple(data01);
		fprintf(stderr,"\n");

	}
	if (memcmp(DATA02str,"DATA02=",7)==0 ) {
		data = split(DATA02str,delim);
		data02 = atoi(data);
		fprintf(stderr,"%08X = ",data02);
		printbitssimple(data02);
		fprintf(stderr,"\n");
	}
	if (memcmp(DATA03str,"DATA03=",7)==0 ) {
		data = split(DATA03str,delim);
		data03 = atoi(data);
		fprintf(stderr,"%08X = ",data03);
		printbitssimple(data03);
		fprintf(stderr,"\n");
	}
	if (memcmp(DATA04str,"DATA04=",7)==0 ) {
		data = split(DATA04str,delim);
		data04 = atoi(data);
		fprintf(stderr,"%08X = ",data04);
		printbitssimple(data04);
		fprintf(stderr,"\n");
	}

}

void sendRDS()
{
//	RESEND_LS_RAW2();

//if(data01!=last_data01) {LS_RAW2((int)20,(uint32_t)data01); RESEND_LS_RAW2(); last_data01=data01; fprintf(stderr,"CMD 20 %08X\n",data01);}
//if(data02!=last_data02) {LS_RAW2((int)21,(uint32_t)data02); RESEND_LS_RAW2(); last_data02=data02; fprintf(stderr,"CMD 21 %08X\n",data02);}
//if(data03!=last_data03) {LS_RAW2((int)22,(uint32_t)data03); RESEND_LS_RAW2(); last_data03=data03; fprintf(stderr,"CMD 22 %08X\n",data03);}
//if(data04!=last_data04) {LS_RAW2((int)23,(uint32_t)data04); RESEND_LS_RAW2(); last_data04=data04; fprintf(stderr,"CMD 23 %08X\n",data04);}

if(data01!=last_data01) {LS_RAW2((int)20,(uint32_t)data01,wait); last_data01=data01; fprintf(stderr,"CMD 20 %08X\n",data01);}
if(data02!=last_data02) {LS_RAW2((int)21,(uint32_t)data02,wait); last_data02=data02; fprintf(stderr,"CMD 21 %08X\n",data02);}
if(data03!=last_data03) {LS_RAW2((int)22,(uint32_t)data03,wait); last_data03=data03; fprintf(stderr,"CMD 22 %08X\n",data03);}
if(data04!=last_data04) {LS_RAW2((int)23,(uint32_t)data04,wait); last_data04=data04; fprintf(stderr,"CMD 23 %08X\n",data04);}

//LS_DOUBLE(20,data01,21,data02,wait);


//if(data01!=last_data01) {LS_RAW((int)20,(uint32_t)data01); last_data01=data01; fprintf(stderr,"CMD 20 %08X\n",data01);}
//if(data02!=last_data02) {LS_RAW2((int)21,(uint32_t)data02); last_data02=data02; fprintf(stderr,"CMD 21 %08X\n",data02);}
//if(data03!=last_data03) {LS_RAW((int)22,(uint32_t)data03); last_data03=data03; fprintf(stderr,"CMD 22 %08X\n",data03);}
//if(data04!=last_data04) {LS_RAW2((int)23,(uint32_t)data04); last_data04=data04; fprintf(stderr,"CMD 23 %08X\n",data04);}

}
