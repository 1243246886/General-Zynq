/*
 * pwm_API.h
 *
 *  Created on: Jul 17, 2015
 *      Author: harryfan
 */

#ifndef PWM_API_H_
#define PWM_API_H_
#include "axi_pwm_6ch.h"

#define PWM_BASEADDR XPAR_AXI_PWM_6CH_0_S00_AXI_BASEADDR

void pwm_set(u32 period, float duty, int Channel);

#endif /* PWM_API_H_ */
