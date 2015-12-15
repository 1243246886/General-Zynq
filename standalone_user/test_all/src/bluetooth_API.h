/*
 * bluetooth_API.h
 *
 *  Created on: 2015��8��17��
 *      Author: harryfan
 */

#ifndef BLUETOOTH_API_H_
#define BLUETOOTH_API_H_

#include "xuartps.h"

int BluetoothInit(void);
int BluetoothRecv(void *buff, int len);
int BluetoothSend(void *buff, int len);

#endif /* BLUETOOTH_API_H_ */
