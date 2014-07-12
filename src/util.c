//util.c
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
#include "util.h"

void print_warranty(void)
{

}

void print_conditions(void)
{

}

void print32bits(uint32_t n)
{
    unsigned int i;
    i = 1<<(sizeof(n) * 8 - 1);

    while (i > 0) {
        if (n & i)
            fprintf(stderr,"1");
        else
            fprintf(stderr,"0");
        i >>= 1;
    }
    fprintf(stderr,"\n");
}

void print64bits(uint64_t n)
{
    uint64_t i;
    i = (uint64_t)1<<(sizeof(n) * 8 - 1);

    while (i > 0) {
        if (n & i)
            fprintf(stderr,"1");
        else
            fprintf(stderr,"0");
        i >>= 1;
    }
    fprintf(stderr,"\n");
}

double int2double_time(uint32_t seconds, uint32_t useconds)
{
    double value;
    value = (double)seconds + (double)useconds/USECS_PER_SEC;
    return value;
}