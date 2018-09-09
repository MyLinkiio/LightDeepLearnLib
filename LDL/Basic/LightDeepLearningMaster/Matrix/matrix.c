#include "matrix.h"
#include <stdio.h>
#include <stdlib.h>


void swap(int *a, int *b)
{
	int m;
	m = *a;
	*a = *b;
	*b = m;
}

void perm(int list[], int k, int m, int* p, Mat* mat, float* det)
{
	int i;

	if (k > m) {
		float res = mat->element[0][list[0]];

		for (i = 1; i < mat->row; i++) {
			res *= mat->element[i][list[i]];
		}

		if (*p % 2) {
			//odd is negative
			*det -= res;
		}
		else {
			//even is positive
			*det += res;
		}
	}
	else {
		// if the element is 0, we don't need to calculate the value for this permutation
		if (!equal(mat->element[k][list[k]], 0.0f))
			perm(list, k + 1, m, p, mat, det);
		for (i = k + 1; i <= m; i++)
		{
			if (equal(mat->element[k][list[i]], 0.0f))
				continue;
			swap(&list[k], &list[i]);
			*p += 1;
			perm(list, k + 1, m, p, mat, det);
			swap(&list[k], &list[i]);
			*p -= 1;
		}
	}
}

Mat* MatCreate(Mat* mat, int row, int col)
{
	int i,j;

	mat->element = (float**)malloc(row * sizeof(float*));
	if (mat->element == NULL) {
		printf("mat create fail!\n");
		return NULL;
	}
	for (i = 0; i < row; i++) {
		mat->element[i] = (float*)malloc(col * sizeof(float));
		if (mat->element[i] == NULL) {
			printf("mat create fail!\n");
			for (j = 0; j < i; j++)
				free(mat->element[j]);
			free(mat->element);
			return NULL;
		}
	}

	mat->row = row;
	mat->col = col;

	return mat;
}

void MatDelete(Mat* mat)
{
	int i;

	for (i = 0; i < mat->row; i++)
		free(mat->element[i]);
	free(mat->element);
}

Mat* MatSetVal(Mat* mat, float* val)
{
	int row, col;
	for (row = 0; row < mat->row; row++) {
		for (col = 0; col < mat->col; col++) {
			mat->element[row][col] = val[col + row * mat->col];
		}
	}

	return mat;
}

void MatDump(const Mat* mat)
{
	int row, col;

#ifdef MAT_LEGAL_CHECKING
	if (mat == NULL) {
		return;
	}
#endif

	printf("Mat %dx%d:\n", mat->row, mat->col);
	for (row = 0; row < mat->row; row++) {
		for (col = 0; col < mat->col; col++) {
			printf("%.4f\t", mat->element[row][col]);
		}
		printf("\n");
	}
}

Mat* MatZeros(Mat* mat)
{
	int row, col;

	for (row = 0; row < mat->row; row++) {
		for (col = 0; col < mat->col; col++) {
			mat->element[row][col] = 0.0f;
		}
	}

	return mat;
}

Mat* MatEye(Mat* mat)
{
	int i;

	MatZeros(mat);
	for (i = 0; i < min(mat->row, mat->col); i++) {
		mat->element[i][i] = 1.0f;
	}

	return mat;
}

Mat* MatAdd(Mat* src1, Mat* src2, Mat* dst)
{
	int row, col;

#ifdef MAT_LEGAL_CHECKING
	if (!(src1->row == src2->row && src2->row == dst->row && src1->col == src2->col && src2->col == dst->col)) {
		printf("err check, unmatch matrix for MatAdd\n");
		MatDump(src1);
		MatDump(src2);
		MatDump(dst);
		return NULL;
	}
#endif

	for (row = 0; row < src1->row; row++) {
		for (col = 0; col < src1->col; col++) {
			dst->element[row][col] = src1->element[row][col] + src2->element[row][col];
		}
	}

	return dst;
}

Mat* MatSub(Mat* src1, Mat* src2, Mat* dst)
{
	int row, col;

#ifdef MAT_LEGAL_CHECKING
	if (!(src1->row == src2->row && src2->row == dst->row && src1->col == src2->col && src2->col == dst->col)) {
		printf("err check, unmatch matrix for MatSub\n");
		MatDump(src1);
		MatDump(src2);
		MatDump(dst);
		return NULL;
	}
#endif

	for (row = 0; row < src1->row; row++) {
		for (col = 0; col < src1->col; col++) {
			dst->element[row][col] = src1->element[row][col] - src2->element[row][col];
		}
	}

	return dst;
}

Mat* MatMul(Mat* src1, Mat* src2, Mat* dst)
{
	int row, col;
	int i;
	float temp;

#ifdef MAT_LEGAL_CHECKING
	if (src1->col != src2->row || src1->row != dst->row || src2->col != dst->col) {
		printf("err check, unmatch matrix for MatMul\n");
		MatDump(src1);
		MatDump(src2);
		MatDump(dst);
		return NULL;
	}
#endif

	for (row = 0; row < dst->row; row++) {
		for (col = 0; col < dst->col; col++) {
			temp = 0.0f;
			for (i = 0; i < src1->col; i++) {
				temp += src1->element[row][i] * src2->element[i][col];
			}
			dst->element[row][col] = temp;
		}
	}

	return dst;
}

Mat* MatTrans(Mat* src, Mat* dst)
{
	int row, col;

#ifdef MAT_LEGAL_CHECKING
	if (src->row != dst->col || src->col != dst->row) {
		printf("err check, unmatch matrix for MatTranspose\n");
		MatDump(src);
		MatDump(dst);
		return NULL;
	}
#endif

	for (row = 0; row < dst->row; row++) {
		for (col = 0; col < dst->col; col++) {
			dst->element[row][col] = src->element[col][row];
		}
	}

	return dst;
}

float MatDet(Mat* mat)
{
	float det = 0.0f;
	int plarity = 0;
	int *list;
	int i;

#ifdef MAT_LEGAL_CHECKING
	if (mat->row != mat->col) {
		printf("err check, not a square matrix for MatDetermine\n");
		MatDump(mat);
		return 0.0f;
	}
#endif

	list = (int*)malloc(sizeof(int)*mat->col);
	if (list == NULL) {
		printf("malloc list fail\n");
		return NULL;
	}
	for (i = 0; i < mat->col; i++)
		list[i] = i;

	perm(list, 0, mat->row - 1, &plarity, mat, &det);
	free(list);

	return det;
}

Mat* MatAdj(Mat* src, Mat* dst)
{
	Mat smat;
	int row, col;
	int i, j, r, c;
	float det;

#ifdef MAT_LEGAL_CHECKING
	if (src->row != src->col || src->row != dst->row || src->col != dst->col) {
		printf("err check, not a square matrix for MatAdj\n");
		MatDump(src);
		MatDump(dst);
		return NULL;
	}
#endif

	MatCreate(&smat, src->row - 1, src->col - 1);

	for (row = 0; row < src->row; row++) {
		for (col = 0; col < src->col; col++) {
			r = 0;
			for (i = 0; i < src->row; i++) {
				if (i == row)
					continue;
				c = 0;
				for (j = 0; j < src->col; j++) {
					if (j == col)
						continue;
					smat.element[r][c] = src->element[i][j];
					c++;
				}
				r++;
			}
			det = MatDet(&smat);
			if ((row + col) % 2)
				det = -det;
			dst->element[col][row] = det;
		}
	}

	MatDelete(&smat);

	return dst;
}

Mat* MatInv(Mat* src, Mat* dst)
{
	Mat adj_mat;
	float det;
	int row, col;

#ifdef MAT_LEGAL_CHECKING
	if (src->row != src->col || src->row != dst->row || src->col != dst->col) {
		printf("err check, not a square matrix for MatInv\n");
		MatDump(src);
		MatDump(dst);
		return NULL;
	}
#endif
	MatCreate(&adj_mat, src->row, src->col);
	MatAdj(src, &adj_mat);
	det = MatDet(src);

	if (equal(det, 0.0f)) {
		printf("err, determinate is 0 for MatInv\n");
		return NULL;
	}

	for (row = 0; row < src->row; row++) {
		for (col = 0; col < src->col; col++)
			dst->element[row][col] = adj_mat.element[row][col] / det;
	}

	MatDelete(&adj_mat);

	return dst;
}

void MatCopy(Mat* src, Mat* dst)
{
	int row, col;

#ifdef MAT_LEGAL_CHECKING
	if (src->row != dst->row || src->col != dst->col) {
		printf("err check, unmathed matrix for MatCopy\n");
		MatDump(src);
		MatDump(dst);
		return;
	}
#endif

	for (row = 0; row < src->row; row++) {
		for (col = 0; col < src->col; col++)
			dst->element[row][col] = src->element[row][col];
	}
}

Mat* MatInterface(Mat * src, char opearteFunction)
{
	Mat* newStructure;
	int row, col;
	switch (opearteFunction)
	{
	case SIGMOID: {
		for (row = 0; row < src->row; row++)
			for (col = 0; col < src->col; col++) {
				newStructure->element[row][col] = Sigmoid(src->element[row][col]);
			}

		break;
	}

	case TANH: {
		for (row = 0; row < src->row; row++)
			for (col = 0; col < src->col; col++) {
				newStructure->element[row][col] = Tanh(src->element[row][col]);
			}

		break;
	}

	case RULE: {
		for (row = 0; row < src->row; row++)
			for (col = 0; col < src->col; col++) {
				newStructure->element[row][col] = Relu(src->element[row][col]);
			}

		break;
	}

	default:
		break;
	}

	newStructure->col = col;
	newStructure->row = row;

	return newStructure;
}



