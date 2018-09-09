#include "sys.h"

MAT_DATA_TYPE Relu(MAT_DATA_TYPE input) {
	return COMPARE_WITH_ZERO(input);
}
MAT_DATA_TYPE Tanh(MAT_DATA_TYPE input) {
	return (1.0-exp(input))/(1.0+exp(input));
}
MAT_DATA_TYPE Sigmoid(MAT_DATA_TYPE input) {
	return 1.0/(-(1+exp(input)));
}
