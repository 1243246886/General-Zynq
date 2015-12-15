/*
 * ultra_API.h
 *
 *  Created on: 2015Äê8ÔÂ16ÈÕ
 *      Author: harryfan
 */

#ifndef ULTRA_API_H_
#define ULTRA_API_H_

#include "Ultrasonic_ip.h"
#include "xparameters.h"
#include "xil_io.h"

#define	ULTRASONIC_BASEADDR	XPAR_ULTRASONIC_IP_V1_0_0_BASEADDR
#define ULTRASONIC_PARAM	0.17

int UltraGetAll(float *val);
int UltraGetSingle(int num, float * val);

#endif /* ULTRA_API_H_ */
