//esp_time.h
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
#ifndef _ENTANGLED_SPARKS_TIME_H_
#define _ENTANGLED_SPARKS_TIME_H_


typedef struct Clock
{
    uint32_t  seconds;
    uint32_t useconds;
} Clock;

Clock initClock();
Clock getProgramClock(Clock offSetClock);
Clock adjustClock(Clock offSetClock, int32_t correction);


#endif