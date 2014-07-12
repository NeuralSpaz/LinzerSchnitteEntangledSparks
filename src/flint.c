//Flint -LinzerSchnitte Entangled Sparks Transmitter Sender
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
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/time.h>
#include <unistd.h>

#include "util.h"
#include "esp.h"
#include "esp_time.h"
#include "udp.h"

#define BUFFERSIZE 32

float version = 1.10;

int main(int argc, char**argv)
{
	fprintf(stderr, "Flint:Entangled Sparks: Frame Contoller for Entagngled Sparks Version %1.2f\n", version);
	fprintf(stderr, "Copyright (C)2014 Josh Gardiner josh@zool.com\n");
	fprintf(stderr, "\nThis program comes with ABSOLUTELY NO WARRANTY; for details type -w'\n");
	fprintf(stderr, "This is free software, and you are welcome to redistribute it\n");
	fprintf(stderr, "under certain conditions; type -c for details.\n");
	fprintf(stderr, "\ntype -h for help\n\n");




	return 0;
}
