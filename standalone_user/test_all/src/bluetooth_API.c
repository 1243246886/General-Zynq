/*
 * bluetooth_API.c
 *
 *  Created on: 2015Äê8ÔÂ17ÈÕ
 *      Author: harryfan
 */

#include "bluetooth_API.h"

static XUartPs Uart1_Ps;

int BluetoothInit(void) {

	int Status;
	XUartPs_Config *Config;

	/*
	 * Initialize the UART driver so that it's ready to use
	 * Look up the configuration in the config table and then initialize it.
	 */
	Config = XUartPs_LookupConfig(XPAR_XUARTPS_0_DEVICE_ID);
	if (NULL == Config) {
		return XST_FAILURE;
	}

	Status = XUartPs_CfgInitialize(&Uart1_Ps, Config, Config->BaseAddress);
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}

	XUartPs_SetBaudRate(&Uart1_Ps, 9600);
	return XST_SUCCESS;
}

int BluetoothRecv(void *buff, int len) {
	return XUartPs_Recv(&Uart1_Ps, buff, len); //rev command
}

int BluetoothSend(void *buff, int len) {
	return XUartPs_Send(&Uart1_Ps, buff, len);
}
