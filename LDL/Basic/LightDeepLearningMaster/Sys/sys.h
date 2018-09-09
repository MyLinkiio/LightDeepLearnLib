#ifndef _SYS_H
#define _SYS_H

#include "matrix.h"
#include "math.h"
#include "stdlib.h"

#define COMPARE_WITH_ZERO(num) ((num>0)?(num):(0))
#define MAT_DATA_TYPE float



typedef unsigned char uint_8;
typedef unsigned short uint_16;
typedef unsigned int uint_32;
typedef unsigned long uint_64;
typedef int int_32;
typedef short int_16;
typedef long int_64;



MAT_DATA_TYPE Relu(MAT_DATA_TYPE input);
MAT_DATA_TYPE Tanh(MAT_DATA_TYPE input);
MAT_DATA_TYPE Sigmoid(MAT_DATA_TYPE input);

#endif


