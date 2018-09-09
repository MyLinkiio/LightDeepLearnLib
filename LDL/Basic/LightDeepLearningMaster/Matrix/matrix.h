#ifndef __LIGHT_MATRIX__
#define __LIGHT_MATRIX__

#define min(a, b) ((a) > (b) ? (b) : (a))
#define equal(a, b)	((a-b)<1e-7 && (a-b)>-(1e-7))

#define SIGMOID 'S'
#define RULE 'R'
#define TANH 'T'

#include "sys.h"

typedef struct  {
	int row, col;
	float **element;
}Mat;

Mat* MatCreate(Mat* mat, int row, int col);
void MatDelete(Mat* mat);
Mat* MatSetVal(Mat* mat, float* val);
void MatDump(const Mat* mat);

Mat* MatZeros(Mat* mat);
Mat* MatEye(Mat* mat);

Mat* MatAdd(Mat* src1, Mat* src2, Mat* dst);
Mat* MatSub(Mat* src1, Mat* src2, Mat* dst);
Mat* MatMul(Mat* src1, Mat* src2, Mat* dst);
Mat* MatTrans(Mat* src, Mat* dst);
float MatDet(Mat* mat);
Mat* MatAdj(Mat* src, Mat* dst);
Mat* MatInv(Mat* src, Mat* dst);
Mat* MatInv(Mat* src, Mat* dst);
void MatCopy(Mat* src, Mat* dst);


Mat* MatInterface(Mat* src, char opearteFunction);

#endif


