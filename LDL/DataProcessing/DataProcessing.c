#include "DataProcessing.h"

void DataInit(void){
	MatCreate(dataSet,1,FEATURE_SIZE);	
}

Mat* ImportData(void){
	READ_BUFFER_DATA
	for(row=0;row<dataSet->row;row++)
		for(col=0;col<dataSet->col;col++){
			dataSet->element[row][col] = buffer[checkPoint];
			checkPoint++;
		}
		checkPoint=0;
}		

void DataAnalysis(void){
	uint_8 i=4;
	do{
		decision[checkPoint++] = output&0xFF000000;
		output<<8;
	}
	while(i--);
}

