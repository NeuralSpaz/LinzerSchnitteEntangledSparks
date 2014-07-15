
#ifndef _RPI_RDS_H_
#define _RPI_RDS_H_

//#include <stdio.h>
//#include <unistd.h>
#include "rpiGpio.h"

extern void RDS_SET_PS();
extern void LS_CMD ( int , int , int );
extern void LS_RAW ( int , uint32_t, int);
extern void LS_RAW2 ( int , uint32_t, int);
extern void RDS_CONFIG ();
extern void RESEND_LS_RAW2();
extern void LS_DOUBLE(int,uint32_t,int,uint32_t,int);
extern void RDS_ENABLE_UDG1();
#endif
