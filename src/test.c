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

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <netdb.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <assert.h>
#include <unistd.h>
#include <inttypes.h>
#include <fcntl.h>
#include <poll.h>
#include <sys/timerfd.h>
#include <sched.h>

#include "util.h"
#include "esp.h"
#include "esp_time.h"
#include "udp.h"
#include "i2c_bitbang.h"

#define VESRION 1.10
#define RDS_PACKET_INTERVAL 180 //180ms //default
#define NANOSEC_PER_MILLISEC 1000000

typedef enum { testing, transmit }Mode;

int main(int argc, char **argv)
{
    /// interval cannot be more that 999
    int interval= RDS_PACKET_INTERVAL *NANOSEC_PER_MILLISEC;
    Mode mode;
    mode = transmit;
    int cmd_option;

    // Parse Options
    while((cmd_option=getopt(argc, argv, "i:m")) != EOF)
        switch(cmd_option)
        {
            default: 
            case 'i': interval=atoi(optarg)*NANOSEC_PER_MILLISEC; break;
            case 'm': mode=testing; break; // really just for me when not using transmitter

        }
    
    if(mode==transmit)
    {
        if (gpioSetup() != OK)
        {
            dbgPrint(DBG_INFO, "gpioSetup failed. Exiting\n");
            return 1;
        }

        LS_CMD(10,0xffff,0);
        sleep(1);
        LS_CMD(10,0xffff,0);
        sleep(1);
        RDS_CONFIG();
        sleep(1);
        RDS_ENABLE_UDG1();
        sleep(1);
    }
    


    struct itimerspec timspec;
    bzero(&timspec, sizeof(timspec));
    timspec.it_interval.tv_sec = 0;
    timspec.it_interval.tv_nsec = interval;
    timspec.it_value.tv_nsec =1;

    int timerfd = timerfd_create(CLOCK_MONOTONIC,0);
    timerfd_settime(timerfd, 0, &timspec, 0);

    struct pollfd ufds;
    ufds.fd = timerfd;
    ufds.events = POLLIN;
    uint64_t loopcount=0;
    int rv;

    uint32_t fake_data=0;
    for(;;)
    {
        rv = poll(&ufds,1,5); // 5 sec timeout....
        
        if (rv == -1) 
        {
            perror("poll"); // error occurred in poll()
        } else if (rv == 0) 
        {
            // Do Nothing 

        } else 
        {
            if (ufds.revents & POLLIN)
            {
                read(timerfd, &loopcount, sizeof(uint64_t)); // reset Time
                if(mode==transmit)
                {
                    LS_RAW(20,fake_data,0);
                } else {fprintf(stderr,"RDS COMMAND \n");}

                fake_data++;
                                
            }
        }
    }

    return 0;
}
