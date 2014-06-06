
#ifndef _RPI_RDS_H_
#define _RPI_RDS_H_

#include <stdio.h>
#include <unistd.h>
#include "rpiGpio.h"


extern void LS_CMD ( int , int , int );
extern void LS_RAW ( int , uint32_t);
extern void RDS_CONFIG ();

#endif
