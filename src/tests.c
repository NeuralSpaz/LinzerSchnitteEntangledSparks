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
    printf("Starting Unit Tests\n\n");

    printf("Start esp Tests\n");


    // Test espData Packet
    espDataPacket espHostPacket, espNetworkPacket, espHostPacket2;

    espHostPacket.prot_header   = 0XF0F0F0F0;
    espHostPacket.data01        = 0XFFFF1111;
    espHostPacket.data02        = 0X10101010;
    espHostPacket.data03        = 0X01010101;
    espHostPacket.data04        = 0XA4A4A4A4;
    espHostPacket.ptime_sec     = 0XB4B4B4B4;
    espHostPacket.ptime_usec    = 0XAAAAAAAA;
    espHostPacket.clockadj_usec = 0XCCCCCCCC;
    espHostPacket.frameid       = 0XDDDDDDDD;

    espNetworkPacket=data_hton(espHostPacket);
    espHostPacket2=data_ntoh(espNetworkPacket);
    if (espHostPacket2.data01==espHostPacket.data01) 
        {printf ("ESP Data01 Test Passed\n");} else { printf("Failed Data01\n");  }
    if (espHostPacket2.data02==espHostPacket.data02) 
        {printf ("ESP Data02 Test Passed\n");} else { printf("Failed Data02\n");  }
    if (espHostPacket2.data03==espHostPacket.data03) 
        {printf ("ESP Data03 Test Passed\n");} else { printf("Failed Data03\n");  }
    if (espHostPacket2.data04==espHostPacket.data04) 
        {printf ("ESP Data04 Test Passed\n");} else { printf("Failed Data04\n");  }

    if (espHostPacket2.ptime_sec==espHostPacket.ptime_sec)      
        {printf ("ESP ptime_sec Test Passed\n");} else { printf("Failed ptime_sec\n");  }
    if (espHostPacket2.ptime_usec==espHostPacket.ptime_usec)    
        {printf ("ESP ptime_usec Test Passed\n");} else { printf("Failed ptime_usec\n");  }
    if (espHostPacket2.clockadj_usec==espHostPacket.clockadj_usec) 
        {printf ("ESP clockadj_usec Test Passed\n");} else { printf("Failed clockadj_usec\n");  }
    if (espHostPacket2.frameid==espHostPacket.frameid)          
        {printf ("ESP espHostPacket Test Passed\n");} else { printf("Failed espHostPacket\n");  }

    print32bits(espHostPacket.data01);
    print32bits(espNetworkPacket.data01);
    print32bits(espHostPacket2.data01);




    return 0;
}
