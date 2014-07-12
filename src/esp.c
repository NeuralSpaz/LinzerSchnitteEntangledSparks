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



espDataPacket data_hton(espDataPacket hostpacket)
{
	espDataPacket networkpacket;

	networkpacket.data01		=	htonl(hostpacket.data01);
	networkpacket.data02		=	htonl(hostpacket.data02);
	networkpacket.data03		= 	htonl(hostpacket.data03);
	networkpacket.data04		=	htonl(hostpacket.data04);
	networkpacket.ptime_sec		= 	htonl(hostpacket.ptime_sec);
	networkpacket.ptime_usec	= 	htonl(hostpacket.ptime_usec);
	networkpacket.clockadj_usec	= 	htonl(hostpacket.clockadj_usec);
	networkpacket.frameid		= 	htonl(hostpacket.frameid);

	return networkpacket;
}

espDataPacket data_ntoh(espDataPacket networkpacket)
{
	espDataPacket hostpacket;

	hostpacket.data01			=	ntohl(networkpacket.data01);
	hostpacket.data02			=	ntohl(networkpacket.data02);
	hostpacket.data03			= 	ntohl(networkpacket.data03);
	hostpacket.data04			=	ntohl(networkpacket.data04);
	hostpacket.ptime_sec		= 	ntohl(networkpacket.ptime_sec);
	hostpacket.ptime_usec		= 	ntohl(networkpacket.ptime_usec);
	hostpacket.clockadj_usec	= 	ntohl(networkpacket.clockadj_usec);
	hostpacket.frameid			= 	ntohl(networkpacket.frameid);

	return hostpacket;
}

espAckPacket ack_hton(espAckPacket hostpacket)
{
	espAckPacket networkpacket;

	networkpacket.ptime_sec 	= 	htonl(hostpacket.ptime_sec);
	networkpacket.ptime_usec 	=	htonl(hostpacket.ptime_usec);
	networkpacket.acktime_sec 	= 	htonl(hostpacket.acktime_sec);
	networkpacket.acktime_usec	= 	htonl(hostpacket.acktime_usec);
	networkpacket.frameid		= 	htonl(hostpacket.frameid);
	networkpacket.acks 			= 	htonl(hostpacket.acks);

	return networkpacket;
}

espAckPacket ack_ntoh(espAckPacket networkpacket)
{
	espAckPacket hostpacket;

	hostpacket.ptime_sec 		= 	ntohl(networkpacket.ptime_sec);
	hostpacket.ptime_usec 		=	ntohl(networkpacket.ptime_usec);
	hostpacket.acktime_sec 		= 	ntohl(networkpacket.acktime_sec);
	hostpacket.acktime_usec		= 	ntohl(networkpacket.acktime_usec);
	hostpacket.frameid			= 	ntohl(networkpacket.frameid);
	hostpacket.acks 			= 	ntohl(networkpacket.acks);

	return hostpacket;
}