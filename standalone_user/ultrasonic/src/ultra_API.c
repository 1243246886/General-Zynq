/*
 * ultra_API.c
 *
 *  Created on: 2015Äê8ÔÂ16ÈÕ
 *      Author: harryfan
 */

#include "ultra_API.h"

int UltraGetAll(float *val) {
	char cnt;

	for (cnt = 0; cnt < 3; cnt++) {
		*val = (float) Xil_In32(
				ULTRASONIC_BASEADDR + 4 * cnt) * ULTRASONIC_PARAM;
		val++;
	}

	return XST_SUCCESS;
}

int UltraGetSingle(int num, float * val) {
	*val = (float) Xil_In32(
			ULTRASONIC_BASEADDR + 4 * (num - 1)) * ULTRASONIC_PARAM;
	return XST_SUCCESS;
}
