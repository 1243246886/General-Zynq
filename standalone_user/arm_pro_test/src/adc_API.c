/*
 * adc_API.c
 *
 *  Created on: 2015Äê8ÔÂ21ÈÕ
 *      Author: harryfan
 */

#include "adc_API.h"

XSysMon *SysMonInstPtr = &SysMonInst;

int AdcInit(void) {
	XSysMon_Config *ConfigPtr;
	int Status;


	ConfigPtr = XSysMon_LookupConfig(SYSMON_DEVICE_ID);
	if (ConfigPtr == NULL) {
		return XST_FAILURE;
	}

	XSysMon_CfgInitialize(SysMonInstPtr, ConfigPtr, ConfigPtr->BaseAddress);
	XSysMon_SetSequencerMode(SysMonInstPtr, XSM_SEQ_MODE_SAFE);
	XSysMon_SetAlarmEnables(SysMonInstPtr, 0x0);
	XSysMon_SetAvg(SysMonInstPtr, XSM_AVG_0_SAMPLES);

	Status = XSysMon_SetSeqInputMode(SysMonInstPtr, XSM_SEQ_CH_AUX00);
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}

	Status = XSysMon_SetSeqAcqTime(SysMonInstPtr,
			XSM_SEQ_CH_AUX00 | XSM_SEQ_CH_AUX06 | XSM_SEQ_CH_AUX07
					| XSM_SEQ_CH_AUX14 | XSM_SEQ_CH_AUX15);
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}

	Status = XSysMon_SetSeqChEnables(SysMonInstPtr,
			XSM_SEQ_CH_AUX00 | XSM_SEQ_CH_AUX06 | XSM_SEQ_CH_AUX07
					| XSM_SEQ_CH_AUX14 | XSM_SEQ_CH_AUX15);
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}

	XSysMon_SetAdcClkDivisor(SysMonInstPtr, 32);

	XSysMon_SetCalibEnables(SysMonInstPtr,
			XSM_CFR1_CAL_PS_GAIN_OFFSET_MASK
					| XSM_CFR1_CAL_ADC_GAIN_OFFSET_MASK);

	XSysMon_SetSequencerMode(SysMonInstPtr, XSM_SEQ_MODE_CONTINPASS);

	XSysMon_GetStatus(SysMonInstPtr);
	while ((XSysMon_GetStatus(SysMonInstPtr) & XSM_SR_EOS_MASK)
			!= XSM_SR_EOS_MASK);
	return 0;
}

u16 AdcGet(u8 Channel) {
	return (XSysMon_GetAdcData(SysMonInstPtr, XSM_CH_AUX_MIN + Channel));
}
