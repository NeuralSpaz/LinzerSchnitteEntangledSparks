//LinzerSchnitte Entangled Sparks Transmitter Software
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

#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sparkfunc.h"

void print_flint_help(void)
{
  fprintf(stderr, "options: -h - display this text\n");
  fprintf(stderr, "         -s - Server IP address\n");
  fprintf(stderr, "         -p - UDP port number\n");
  fprintf(stderr, "         -t - Time to wait before sendind next frame\n");
  fprintf(stderr, "\n");
  exit(EXIT_FAILURE);
}

void print_steel_help(void)
{
	fprintf(stderr, "options: -h - display this text\n");
	fprintf(stderr, "         -p - UDP port number\n");
	fprintf(stderr, "\n");
	exit(EXIT_FAILURE);
}
void print_warranty(void)
{
	fprintf(stderr,"\n");
	fprintf(stderr,"Disclaimer of Warranty.\n");
	fprintf(stderr,"\n");
	fprintf(stderr,"  THERE IS NO WARRANTY FOR THE PROGRAM, TO THE EXTENT PERMITTED BY\n");
	fprintf(stderr,"APPLICABLE LAW.  EXCEPT WHEN OTHERWISE STATED IN WRITING THE COPYRIGHT\n");
	fprintf(stderr,"HOLDERS AND/OR OTHER PARTIES PROVIDE THE PROGRAM \"AS IS\" WITHOUT WARRANTY\n");
	fprintf(stderr,"OF ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING, BUT NOT LIMITED TO,\n");
	fprintf(stderr,"THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR\n");
	fprintf(stderr,"PURPOSE.  THE ENTIRE RISK AS TO THE QUALITY AND PERFORMANCE OF THE PROGRAM\n");
	fprintf(stderr,"IS WITH YOU.  SHOULD THE PROGRAM PROVE DEFECTIVE, YOU ASSUME THE COST OF\n");
	fprintf(stderr,"ALL NECESSARY SERVICING, REPAIR OR CORRECTION.\n");
	exit(EXIT_FAILURE);
}

void print_conditions(void)
{
	fprintf(stderr,"\n");
	fprintf(stderr,"see the License file in the directory or see <http://www.gnu.org/licenses/");
	fprintf(stderr,"\n");
	exit(EXIT_FAILURE);
}

double getTime(void){

	struct timeval now;
	double timenow;

	if(!(gettimeofday(&now, NULL))) {
		timenow = now.tv_sec+ (double)now.tv_usec/1000000 ;
	}
	else {
		fprintf(stderr,"gettimeofday() failed");
		exit(EXIT_FAILURE);
	}

	return timenow;
}

void printbitssimple(unsigned int n) {
	unsigned int i;
	i = 1<<(sizeof(n) * 8 - 1);

	while (i > 0) {
		if (n & i)
			fprintf(stderr,"1");
		else
			fprintf(stderr,"0");
		i >>= 1;
	}
}

char *split(char *str, const char *del){
	char *value;
	value = strtok(str, del);
	value = strtok(NULL, del);
	return (value);
}
