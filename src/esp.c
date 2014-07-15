//esp.c
//LinzerSchnitte Entangled Sparks
//Josh Gardiner
//2014 07 12
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

#include <stdint.h>
#include <arpa/inet.h>
#include "esp.h"
#include <stdio.h>

espDataPacket data_hton(espDataPacket hostpacket)
{
    espDataPacket networkpacket;

    networkpacket.prot_header   =   htonl(hostpacket.prot_header);
    networkpacket.frameid       =   htonl(hostpacket.frameid);
    networkpacket.cmd           =   htonl(hostpacket.cmd);  
    networkpacket.data          =   htonl(hostpacket.data);;
    networkpacket.ptime_sec     =   htonl(hostpacket.ptime_sec);
    networkpacket.ptime_usec    =   htonl(hostpacket.ptime_usec);
    networkpacket.clockadj_usec =   htonl(hostpacket.clockadj_usec);

    return networkpacket;
}

espDataPacket data_ntoh(espDataPacket networkpacket)
{
    espDataPacket hostpacket;

    hostpacket.prot_header   =   htonl(networkpacket.prot_header);
    hostpacket.frameid       =   htonl(networkpacket.frameid);
    hostpacket.cmd           =   htonl(networkpacket.cmd);  
    hostpacket.data          =   htonl(networkpacket.data);
    hostpacket.ptime_sec     =   htonl(networkpacket.ptime_sec);
    hostpacket.ptime_usec    =   htonl(networkpacket.ptime_usec);
    hostpacket.clockadj_usec =   htonl(networkpacket.clockadj_usec);

    return hostpacket;
}

espAckPacket ack_hton(espAckPacket hostpacket)
{
    espAckPacket networkpacket;

    networkpacket.prot_header   =   htonl(hostpacket.prot_header);
    networkpacket.frameid       =   htonl(hostpacket.frameid);
    networkpacket.ptime_sec     =   htonl(hostpacket.ptime_sec);
    networkpacket.ptime_usec    =   htonl(hostpacket.ptime_usec);
    networkpacket.acktime_sec   =   htonl(hostpacket.acktime_sec);
    networkpacket.acktime_usec  =   htonl(hostpacket.acktime_usec);
    networkpacket.acks          =   htonl(hostpacket.acks);

    return networkpacket;
}

espAckPacket ack_ntoh(espAckPacket networkpacket)
{
    espAckPacket hostpacket;

    hostpacket.prot_header      =   htonl(networkpacket.prot_header);
    hostpacket.frameid          =   ntohl(networkpacket.frameid);
    hostpacket.ptime_sec        =   ntohl(networkpacket.ptime_sec);
    hostpacket.ptime_usec       =   ntohl(networkpacket.ptime_usec);
    hostpacket.acktime_sec      =   ntohl(networkpacket.acktime_sec);
    hostpacket.acktime_usec     =   ntohl(networkpacket.acktime_usec);
    hostpacket.acks             =   ntohl(networkpacket.acks);

    return hostpacket;
}


void Print_espDataPacket(espDataPacket dataPacket)
{
    printf("dataPacket.prot_header=   %08X\n" ,dataPacket.prot_header);
    printf("dataPacket.frameid=       %08X\n" ,dataPacket.frameid);
    printf("dataPacket.cmd=           %08X\n", dataPacket.cmd);
    printf("dataPacket.data=          %08X\n" ,dataPacket.data);  
    printf("dataPacket.ptime_sec=     %08X\n" ,dataPacket.ptime_sec);
    printf("dataPacket.ptime_usec=    %08X\n" ,dataPacket.ptime_usec);
    printf("dataPacket.clockadj_usec= %08X\n" ,dataPacket.clockadj_usec);
}

void Print_espAckPacket(espAckPacket ackPacket)
{
    printf("ackPacket.prot_header=    %08X\n",ackPacket.prot_header);
    printf("ackPacket.frameid=        %08X\n",ackPacket.frameid);
    printf("ackPacket.ptime_sec=      %08X\n",ackPacket.ptime_sec);
    printf("ackPacket.ptime_usec=     %08X\n",ackPacket.ptime_usec);
    printf("ackPacket.acktime_sec=    %08X\n",ackPacket.acktime_sec);
    printf("ackPacket.acktime_usec=   %08X\n",ackPacket.acktime_usec);
    printf("ackPacket.acks=           %08X\n",ackPacket.acks);
}
