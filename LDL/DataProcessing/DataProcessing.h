#ifndef DATA_PROCESSING_H
#define DATA_PROCESSING_H

#include "matrix.h"
#include "sys.h"

#define FEATURE_SIZE 12

#ifndef _REGION_
#define _REGION_

#include "Location.h"
#include "CanBus_Interface.h"
#include "PTP.h"

/*
*	wheel1
*	wheel2
*	wheel3
*	action
*/
#endif

uint_32 output;
uint8_t decision[4];
Mat* dataSet;
uint_8 row,col;
float buffer[FEATURE_SIZE];
uint_8 checkPoint=0;

void DataInit(void);
Mat* ImportData(void);

#define READ_BUFFER_DATA 	{								\
					buffer[0] = Get_Laser1_data();	\
					buffer[1] = Get_Laser2_data();	\
					buffer[2] = Get_Laser3_data();	\
					buffer[3] = Get_Laser4_data();	\
					buffer[4] = Get_Laser4_data();	\
					buffer[5] = Get_Laser4_data();	\
					buffer[6] = Get_Laser4_data();	\
					buffer[7] = Get_Laser4_data();	\
					buffer[8] = Get_Laser4_data();	\
					buffer[9] = Get_Laser4_data();	\
}

void DataAnalysis(void);


#endif