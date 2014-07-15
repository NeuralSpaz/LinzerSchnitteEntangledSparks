//tests
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

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


#include "esp.h"
#include "util.h"

int main (void)
{
    printf("Starting Tests\n\n");

    printf("Start esp Tests\n");

    // This just test some of the function ....
    // sandbox or whatever you want to call it...

    // Test espData Packet
    espDataPacket espHostPacket, espNetworkPacket, espHostPacket2;

    espHostPacket.prot_header   = 0XF0F0F0F0;
    espHostPacket.data          = 0XFFFF1111;

    espHostPacket.ptime_sec     = 0XB4B4B4B4;
    espHostPacket.ptime_usec    = 0XAAAAAAAA;
    espHostPacket.clockadj_usec = 0XCCCCCCCC;
    espHostPacket.frameid       = 0XDDDDDDDD;

    espNetworkPacket=data_hton(espHostPacket);
    espHostPacket2=data_ntoh(espNetworkPacket);

    if (espHostPacket2.ptime_sec==espHostPacket.ptime_sec)      
        {printf ("ESP ptime_sec Test Passed\n");} else { printf("Failed ptime_sec\n");  }
    if (espHostPacket2.ptime_usec==espHostPacket.ptime_usec)    
        {printf ("ESP ptime_usec Test Passed\n");} else { printf("Failed ptime_usec\n");  }
    if (espHostPacket2.clockadj_usec==espHostPacket.clockadj_usec) 
        {printf ("ESP clockadj_usec Test Passed\n");} else { printf("Failed clockadj_usec\n");  }
    if (espHostPacket2.frameid==espHostPacket.frameid)          
        {printf ("ESP espHostPacket Test Passed\n");} else { printf("Failed espHostPacket\n");  }



    // Create Queue

    RDS_Queue q1 = QueueCreate();
    // add stuff to queue
    RDS_Command newCommand;
    int i;
    for (i=0; i<128 ; i++)
    {
        newCommand.cmd=20 + (i%4);
        newCommand.data=i;
        QueueEnter(q1,newCommand);
    }
    // get stuff from queue
    RDS_Command oldComand;
    for (i=0; i<128; i++ )
    {
        oldComand=QueueDelete(q1);
        printf("From Queue: Prefix: %d, Data: %d \n",oldComand.cmd,oldComand.data);
    }

    for (i=0; i<128 ; i++)
    {
        printf("i %d mod 32 %d\n",i, i%32);
    }

    Print_espDataPacket(espHostPacket);
    Print_espDataPacket(espNetworkPacket);

    espAckPacket ackPacket;
    ackPacket.ptime_sec=    0X0101F0F0;
    ackPacket.ptime_usec=   0X0202FAFA;
    ackPacket.acktime_sec=  0X0303FBFB;
    ackPacket.acktime_usec= 0X0404FCFC;
    ackPacket.frameid=      0X0505FDFD;
    ackPacket.acks=         0X0606FEFE;

    Print_espAckPacket(ackPacket);
    ackPacket =ack_hton(ackPacket);
    Print_espAckPacket(ackPacket);
    ackPacket = ack_ntoh(ackPacket);
    Print_espAckPacket(ackPacket);

    return 0;
}
