//Flint -LinzerSchnitte Entangled Sparks Transmitter Sender
//Josh Gardiner
//2014 06 05

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/time.h>
#include <unistd.h>
#include "sparkfunc.h"

#define BUFFERSIZE 2048

float version = 1.00;

double processData(char *message, int messageLength);

int main(int argc, char**argv)
{
	fprintf(stderr, "Flint: Contoller for Entagngled Sparks\n");
	fprintf(stderr, "Version %1.2f <josh@zool.com> use -h for help\n\n", version);

	int cmd_option;
	int port = 1535;
	char *server = "127.0.0.1";
	int delay = 1000;

	while((cmd_option=getopt(argc, argv, "hp:s:t:")) != EOF)
	switch(cmd_option)
	{
		default:
		case 'h': print_flint_help();
		case 'p': port=atoi(optarg); break;
		case 's': server=(optarg); break;
		case 't': delay=atoi(optarg); break;
	}

	struct sockaddr_in myaddr;
	struct sockaddr_in remaddr;
	
	int fd;
	int i;
	int slen=sizeof(remaddr);

	char buf[BUFFERSIZE];
	int recvlen;


	if ((fd=socket(AF_INET, SOCK_DGRAM, 0))==-1)
		printf("socket created\n");


	memset((char *)&myaddr, 0, sizeof(myaddr));
	myaddr.sin_family = AF_INET;
	myaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	myaddr.sin_port = htons(0);

	if (bind(fd, (struct sockaddr *)&myaddr, sizeof(myaddr)) < 0) {
		perror("bind failed");
		return 0;
	}  
	
   	memset((char *) &remaddr, 0, sizeof(remaddr));
	remaddr.sin_family = AF_INET;
	remaddr.sin_port = htons(port);
	if (inet_aton(server, &remaddr.sin_addr)==0) {
		fprintf(stderr, "inet_aton() failed\n");
		exit(1);
	}
	short shiftleft1=1;
	short shiftleft2=1;
//	short shiftleft3=1;
//	short shiftleft4=1;
	double timenow;
	//double acktime;
	//double roundtriptime;
	while(1)
	{
	
		uint32_t data01 = 0X00000001;
		uint32_t data02 = 0X00000800;
		uint32_t data03 = 0X00080000;
		uint32_t data04 = 0X08000000;
	
		for (i=0; data01 < 0xFFFFFFFF; i++) {
			timenow=getTime();
			printf("Sending Frame %d to %s port %d\n", i, server, port);
			sprintf(buf, "FRAMEID=%d\nTIMESTAMP=%8.8f\nDATA01=%u\nDATA02=%u\nDATA03=%u\nDATA04=%u\n"
				, i, timenow,data01,data02,data03,data04);
			if (sendto(fd, buf, strlen(buf), 0, (struct sockaddr *)&remaddr, slen)==-1) {
				perror("sendto");
				exit(1);
			}
	
			recvlen = recvfrom(fd, buf, BUFFERSIZE, 0, (struct sockaddr *)&remaddr, (socklen_t *)&slen);
					if (recvlen >= 0) {
							buf[recvlen] = 0;
							processData(buf,recvlen);
							fprintf(stderr, "Latency=%lf\n", ((getTime()-timenow)/2) );
					}


		if (data01 == 0X80000000){ shiftleft1=0; }
		if (shiftleft1==1) {data01 <<= 1;}
		if (shiftleft1==0) {data01 >>= 1;}
		if (data01 == 0X00000001) {shiftleft1=1;}

		if (data02 == 0X80000000){ shiftleft2=0; }
		if (shiftleft2==1) {data02 <<= 1;}
		if (shiftleft2==0) {data02 >>= 1;}
		if (data02 == 0X00000001) {shiftleft2=1;}
/*
		if (data03 == 0X80000000){ shiftleft3=0; }
		if (shiftleft3==1) {data03 <<= 1;}
		if (shiftleft3==0) {data03 >>= 1;}
		if (data03 == 0X00000001) {shiftleft3=1;}

		if (data04 == 0X80000000){ shiftleft4=0; }
		if (shiftleft4==1) {data04 <<= 1;}
		if (shiftleft4==0) {data04 >>= 1;}
		if (data04 == 0X00000001) {shiftleft4=1;}
*/
		usleep(1000*delay);

		}

	}

	close(fd);
	return 0;
}

double processData(char *message, int messageLength)
{
	char FRAMEIDstr[100];
	double recivedtime;

	sscanf(message, "%s %lf",FRAMEIDstr, &recivedtime);
	
	//fprintf(stderr, "%s\n %s\n %s\n %s\n %s\n %s\n",FRAMEIDstr, TIMESTAMPstr, DATA01str, DATA02str, DATA03str, DATA04str);

	if (memcmp(FRAMEIDstr,"FRAMEID=",8)==0 ) {
		//data = split(FRAMEIDstr,delim);
		fprintf(stderr,"%s ACK\n",FRAMEIDstr);
	}

	//fprintf(stderr,"RecivedTime=%lf \n", recivedtime);
	return (recivedtime);

}
