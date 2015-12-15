/*
 * eeprom_API.h
 *
 *  Created on: 2015Äê8ÔÂ20ÈÕ
 *      Author: harryfan
 */

#ifndef EEPROM_API_H_
#define EEPROM_API_H_

#include "xiicps.h"
#include "sleep.h"

#define IIC_SCLK_RATE		100000
#define IIC_SLAVE_ADDR		0x50

#define TEST_BUFFER_SIZE	10

int EepromInit(void);
void EepromWrite(u8 IicAddr, u8 *SendData, int ByteCount);
void EepromRead(u8 IicAddr, u8 *RecvData, int ByteCount);

#endif /* EEPROM_API_H_ */
