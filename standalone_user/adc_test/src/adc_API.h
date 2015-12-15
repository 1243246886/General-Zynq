/*
 * adc_API.h
 *
 *  Created on: 2015Äê8ÔÂ21ÈÕ
 *      Author: harryfan
 */

#ifndef ADC_API_H_
#define ADC_API_H_

#include <stdio.h>
#include "platform.h"
#include "xsysmon.h"
#include "xparameters.h"
#include "xstatus.h"
#include "sleep.h"

XSysMon SysMonInst;

#define SYSMON_DEVICE_ID 	XPAR_SYSMON_0_DEVICE_ID

int AdcInit(void);
u16 AdcGet(u8 Channel);


#endif /* ADC_API_H_ */
