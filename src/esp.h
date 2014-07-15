//esp.h
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

// Structures and word order convserisons for Entangles Sparks Protocal (esp)
#ifndef _ENTANGLED_SPARKS_PROT_H_
#define _ENTANGLED_SPARKS_PROT_H_

typedef struct espDataPacket 
{
	uint32_t prot_header;
	uint32_t frameid;
	uint32_t cmd;
	uint32_t data;
	uint32_t ptime_sec;	
	uint32_t ptime_usec;
	int32_t  clockadj_usec;

} espDataPacket;

typedef struct espAckPacket
{
	uint32_t prot_header;
	uint32_t frameid;
	uint32_t acks;
	uint32_t ptime_sec;	
	uint32_t ptime_usec;
	uint32_t acktime_sec;
	uint32_t acktime_usec;

} espAckPacket;
// This Converts an Entangled Sparks Protocol 
// from host word order to network word order
// Usage espDataPacket = data_hton(espDatapacket packet) etc...
// hton = host to network
// ntoh = network to host
espDataPacket data_hton(espDataPacket);
espDataPacket data_ntoh(espDataPacket);
espAckPacket  ack_hton(espAckPacket);
espAckPacket  ack_ntoh(espAckPacket);
void Print_espDataPacket(espDataPacket);
void Print_espAckPacket(espAckPacket);


#endif