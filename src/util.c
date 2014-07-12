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
    fprintf(stderr,"\n");
    fprintf(stderr,"Disclaimer of Warranty.\n");
    fprintf(stderr,"\n");
    fprintf(stderr,"  THERE IS NO WARRANTY FOR THE PROGRAM, TO THE EXTENT PERMITTED BY\n");
    fprintf(stderr,"APPLICABLE LAW.  EXCEPT WHEN OTHERWISE STATED IN WRITING THE COPYRIGHT\n");
    fprintf(stderr,"HOLDERS AND/OR OTHER PARTIES PROVIDE THE PROGRAM \"AS IS\" WITHOUT WARRANTY\n");
    fprintf(stderr,"OF ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING, BUT NOT LIMITED TO,\n");
    fprintf(stderr,"THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR\n");
    fprintf(stderr,"PURPOSE.  THE ENTIRE RISK AS TO THE QUALITY AND PERFORMANCE OF THE PROGRAM\n");
    fprintf(stderr,"IS WITH YOU.  SHOULD THE PROGRAM PROVE DEFECTIVE, YOU ASSUME THE COST OF\n");
    fprintf(stderr,"ALL NECESSARY SERVICING, REPAIR OR CORRECTION.\n");
    exit(EXIT_FAILURE);
}

void print_conditions(void)
{
    fprintf(stderr,"\n");
    fprintf(stderr,"see the License file in the directory or see <http://www.gnu.org/licenses/");
    fprintf(stderr,"\n");
    exit(EXIT_FAILURE);
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