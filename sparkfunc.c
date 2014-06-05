//LinzerSchnitte Entangled Sparks Transmitter Software
//Josh Gardiner
//2014 06 05

#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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