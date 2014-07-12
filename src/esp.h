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
	uint32_t prot_header;;
	uint32_t data01;
	uint32_t data02;
	uint32_t data03;
	uint32_t data04;
	uint32_t ptime_sec;	
	uint32_t ptime_usec;
	int32_t  clockadj_usec;
	uint32_t frameid;
} espDataPacket;

typedef struct espAckPacket
{
	uint32_t ptime_sec;	
	uint32_t ptime_usec;
	uint32_t acktime_sec;
	uint32_t acktime_usec;
	uint32_t frameid;
	uint32_t acks;
} espAckPacket;

espDataPacket data_hton(espDataPacket);
espDataPacket data_ntoh(espDataPacket);
espAckPacket ack_hton(espAckPacket);
espAckPacket ack_nton(espAckPacket);

#endif