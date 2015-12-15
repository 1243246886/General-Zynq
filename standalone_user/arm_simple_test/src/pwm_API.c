/*
 * pwm_API.c
 *
 *  Created on: Jul 17, 2015
 *      Author: harryfan
 */

#include <stdio.h>
#include <string.h>
#include "xparameters.h"
#include "pwm_API.h"
#include "xil_io.h"

void pwm_set(u32 period, float duty, int Channel) {
	u32 high;
	switch (Channel) {
	case 0:
		AXI_PWM_6CH_mWriteReg(PWM_BASEADDR, AXI_PWM_6CH_S00_AXI_SLV_REG0_OFFSET,
				period);
		high = period * duty / 100;
		AXI_PWM_6CH_mWriteReg(PWM_BASEADDR, AXI_PWM_6CH_S00_AXI_SLV_REG1_OFFSET,
				0x80000000 + high);
		break;
	case 1:
		AXI_PWM_6CH_mWriteReg(PWM_BASEADDR, AXI_PWM_6CH_S00_AXI_SLV_REG2_OFFSET,
				period);
		high = period * duty / 100;
		AXI_PWM_6CH_mWriteReg(PWM_BASEADDR, AXI_PWM_6CH_S00_AXI_SLV_REG3_OFFSET,
				0x80000000 + high);
		break;
	case 2:
		AXI_PWM_6CH_mWriteReg(PWM_BASEADDR, AXI_PWM_6CH_S00_AXI_SLV_REG4_OFFSET,
				period);
		high = period * duty / 100;
		AXI_PWM_6CH_mWriteReg(PWM_BASEADDR, AXI_PWM_6CH_S00_AXI_SLV_REG5_OFFSET,
				0x80000000 + high);
		break;
	case 3:
		AXI_PWM_6CH_mWriteReg(PWM_BASEADDR, AXI_PWM_6CH_S00_AXI_SLV_REG6_OFFSET,
				period);
		high = period * duty / 100;
		AXI_PWM_6CH_mWriteReg(PWM_BASEADDR, AXI_PWM_6CH_S00_AXI_SLV_REG7_OFFSET,
				0x80000000 + high);
		break;
	case 4:
		AXI_PWM_6CH_mWriteReg(PWM_BASEADDR, AXI_PWM_6CH_S00_AXI_SLV_REG8_OFFSET,
				period);
		high = period * duty / 100;
		AXI_PWM_6CH_mWriteReg(PWM_BASEADDR, AXI_PWM_6CH_S00_AXI_SLV_REG9_OFFSET,
				0x80000000 + high);
		break;
	case 5:
		AXI_PWM_6CH_mWriteReg(PWM_BASEADDR, AXI_PWM_6CH_S00_AXI_SLV_REG10_OFFSET,
				period);
		high = period * duty / 100;
		AXI_PWM_6CH_mWriteReg(PWM_BASEADDR, AXI_PWM_6CH_S00_AXI_SLV_REG11_OFFSET,
				0x80000000 + high);
		break;
	}
}
