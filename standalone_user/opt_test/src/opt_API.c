/*
 * opt_API.c
 *
 *  Created on: 2015Äê8ÔÂ12ÈÕ
 *      Author: harryfan
 */

#include <stdio.h>
#include "platform.h"
#include "xparameters.h"
#include "opt_API.h"

static XGpio Opt;

void SetOptDirection(void) {
	XGpio_descMWrite(&Opt, Opt_ch, Opt1, Opt_Dir);
	XGpio_descMWrite(&Opt, Opt_ch, Opt2, Opt_Dir);
	XGpio_descMWrite(&Opt, Opt_ch, Opt3, Opt_Dir);
	XGpio_descMWrite(&Opt, Opt_ch, Opt4, Opt_Dir);
	XGpio_descMWrite(&Opt, Opt_ch, Opt5, Opt_Dir);
}

int OptInit(void) {
	int Status;
	Status = init_Gpio(&Opt, OPT_GPIO_DEVICE_ID);
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}
	SetOptDirection();

	return XST_SUCCESS;
}

int OptGetSingle(int OptNum, u8 *OptVal) {
	*OptVal = XGpio_descRead(&Opt, Opt_ch, OptNum);
	return XST_SUCCESS;
}

u8 OptGetAll(void) {
	u8 OptVal, OptVal1, OptVal2, OptVal3, OptVal4, OptVal5;
	OptGetSingle(Opt1, &OptVal1);
	OptGetSingle(Opt2, &OptVal2);
	OptGetSingle(Opt3, &OptVal3);
	OptGetSingle(Opt4, &OptVal4);
	OptGetSingle(Opt5, &OptVal5);
	OptVal = (OptVal1 << 0) + (OptVal2 << 1) + (OptVal3 << 2) + (OptVal4 << 3)
			+ (OptVal5 << 4);
	return OptVal;
}
