/*
 * gpio_API.c
 *
 *  Created on: Jul 17, 2015
 *      Author: harryfan
 */

#include <stdio.h>
#include <string.h>
#include "platform.h"
#include "xparameters.h"
#include "gpio_API.h"

int init_Gpio(XGpio * InstancePtr, int device_id) {
	int Status;
	Status = XGpio_Initialize(InstancePtr, device_id);
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}
	return XST_SUCCESS;
}

void XGpio_descWrite(XGpio * InstancePtr, u8 Channel, u8 PinNum, u8 value) {
	if (value == 0) {
		XGpio_DiscreteClear(InstancePtr, Channel, 1 << PinNum);
	} else {
		XGpio_DiscreteSet(InstancePtr, Channel, 1 << PinNum);
	}
}

u8 XGpio_descRead(XGpio * InstancePtr, u8 Channel, u8 PinNum) {
	u32 GpioState;
	u8 value;
	GpioState = XGpio_DiscreteRead(InstancePtr, Channel);
	value = (GpioState >> PinNum) & 1;
	return value;
}

void XGpio_descMWrite(XGpio * InstancePtr, u8 Channel, u8 PinNum, u8 value) {
	u32 GpioState;
	u32 SetBit = 0;
	SetBit = 1 << PinNum;
	GpioState = XGpio_GetDataDirection(InstancePtr, Channel);
	if (value == 0) {
		GpioState = GpioState & ~(SetBit);
	} else {
		GpioState = GpioState | SetBit;
	}
	XGpio_SetDataDirection(InstancePtr, Channel, GpioState);
}

u8 XGpio_descMRead(XGpio * InstancePtr, u8 Channel, u8 PinNum) {
	u32 GpioState;
	u8 value;
	GpioState = XGpio_GetDataDirection(InstancePtr, Channel);
	value = (GpioState >> PinNum) & 1;
	return value;
}

void XGpio_chipWrite(XGpio * InstancePtr, u8 Channel, u8 value) {
	if (value == 0) {
		XGpio_DiscreteWrite(InstancePtr, Channel, 0);
	} else {
		XGpio_DiscreteWrite(InstancePtr, Channel, 0xffffffff);
	}
}

u32 XGpio_chipRead(XGpio * InstancePtr, u8 Channel) {
	u32 GpioState;
	GpioState = XGpio_DiscreteRead(InstancePtr, Channel);
	return GpioState;
}

void XGpio_chipMWrite(XGpio * InstancePtr, u8 Channel, u8 value) {
	if (value == 0) {
		XGpio_SetDataDirection(InstancePtr, Channel, 0);
	} else {
		XGpio_SetDataDirection(InstancePtr, Channel, 0xffffffff);
	}
}

u32 XGpio_chipMRead(XGpio * InstancePtr, u8 Channel) {
	u32 GpioState;
	GpioState = XGpio_GetDataDirection(InstancePtr, Channel);
	return GpioState;
}
