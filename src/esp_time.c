//esp_time.c
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
#include <sys/time.h>

#include "esp_time.h"

#define USEC_PER_SEC 1000000

Clock initClock()
{
    Clock temp;
    struct timeval now;

    gettimeofday(&now, NULL);
    temp.seconds  = now.tv_sec;
    temp.useconds = now.tv_usec;

    return temp;
}

Clock getProgramClock(Clock offSetClock)
{
    Clock temp;

    int32_t  seconds;
    int32_t useconds;

    static struct timeval now;
    gettimeofday(&now, NULL);

    seconds  = now.tv_sec  - offSetClock.seconds;
    useconds = now.tv_usec - offSetClock.useconds;

    if (useconds<0)
    {
        seconds  -= 1;
        useconds += USEC_PER_SEC;
    }
    temp.seconds  =  seconds;
    temp.useconds = useconds;

    return temp;
}

Clock adjustClock(Clock offSetClock, int32_t correction)
{
    Clock temp;
    int sign=1;
    if(correction<0)
    {
        correction *= -1;
        sign       *= -1;
    }
    int correction_secs;
    int correction_usec;

    correction_secs = sign * (correction / USEC_PER_SEC);
    correction_secs *= -1;
    correction_usec = sign * (correction % USEC_PER_SEC);
    correction_usec *= -1;

    correction_secs += offSetClock.seconds;
    correction_usec += offSetClock.useconds;

    if (correction_usec<0)
    {
        correction_secs -= 1;
        correction_usec += USEC_PER_SEC;
    }
    if (correction_usec>USEC_PER_SEC)
    {
        correction_secs += 1;
        correction_usec -= USEC_PER_SEC;
    }
    temp.seconds  = (uint32_t)correction_secs;
    temp.useconds = (uint32_t)correction_usec;

    return temp;
}