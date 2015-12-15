/*
 * eeprom_API.c
 *
 *  Created on: 2015Äê8ÔÂ20ÈÕ
 *      Author: harryfan
 */
#include "eeprom_API.h"

XIicPs Eeprom;

u8 SendBuffer[TEST_BUFFER_SIZE + 1]; /**< Buffer for Transmitting Data */

int EepromInit(void) {
	int Status;
	XIicPs_Config *Config;

	Config = XIicPs_LookupConfig(XPAR_XIICPS_1_DEVICE_ID);
	if (NULL == Config) {
		return XST_FAILURE;
	}

	Status = XIicPs_CfgInitialize(&Eeprom, Config, Config->BaseAddress);
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}

	XIicPs_SetSClk(&Eeprom, IIC_SCLK_RATE);
	return XST_SUCCESS;
}

void EepromWrite(u8 IicAddr, u8 *SendData, int ByteCount) {
	int Index;
	SendBuffer[0] = IicAddr;
	for (Index = 0; Index < ByteCount; Index++) {
		SendBuffer[Index + 1] = SendData[Index];
	}
	XIicPs_MasterSendPolled(&Eeprom, SendBuffer, ByteCount, IIC_SLAVE_ADDR);
	usleep(50 * 1000);
}

void EepromRead(u8 IicAddr, u8 *RecvData, int ByteCount) {
	u8 RecvAddr[1];
	RecvAddr[0] = IicAddr;
	XIicPs_MasterSendPolled(&Eeprom, RecvAddr, 1, IIC_SLAVE_ADDR);
	XIicPs_MasterRecvPolled(&Eeprom, RecvData, ByteCount, IIC_SLAVE_ADDR);
}
