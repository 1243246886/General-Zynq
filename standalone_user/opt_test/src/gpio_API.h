/*
 * gpio_API.h
 *
 *  Created on: Jul 17, 2015
 *      Author: harryfan
 */

#ifndef GPIO_API_H_
#define GPIO_API_H_
#include "xgpio.h"

#define GPIO_EXAMPLE_DEVICE_ID  XPAR_AXI_GPIO_0_DEVICE_ID

#define Gpio0  0
#define Gpio1  1
#define Gpio2  2
#define Gpio3  3
#define Gpio4  4
#define Gpio5  5
#define Gpio6  6
#define Gpio7  7
#define Gpio8  8
#define Gpio9  9
#define Gpio10 10
#define Gpio11 11
#define Gpio12 12
#define Gpio13 13
#define Gpio14 14
#define Gpio15 15
#define Gpio16 16
#define Gpio17 17
#define Gpio18 18
#define Gpio19 19
#define Gpio20 20
#define Gpio21 21
#define Gpio22 22
#define Gpio23 23
#define Gpio24 24
#define Gpio25 25
#define Gpio26 26
#define Gpio27 27
#define Gpio28 28
#define Gpio29 29
#define Gpio30 30
#define Gpio31 31

#define Gpio_output 0
#define Gpio_input	1

#define Gpio_high	1
#define Gpio_low 	0

#define Gpio_ch1	1
#define Gpio_ch2	2

int init_Gpio(XGpio * InstancePtr, int device_id);
void XGpio_descWrite(XGpio * InstancePtr, u8 Channel, u8 PinNum, u8 value);
u8 XGpio_descRead(XGpio * InstancePtr, u8 Channel, u8 PinNum);
void XGpio_descMWrite(XGpio * InstancePtr, u8 Channel, u8 PinNum, u8 value);
u8 XGpio_descMRead(XGpio * InstancePtr, u8 Channel, u8 PinNum);
void XGpio_chipWrite(XGpio * InstancePtr, u8 Channel, u8 value);
u32 XGpio_chipRead(XGpio * InstancePtr, u8 Channel);
void XGpio_chipMWrite(XGpio * InstancePtr, u8 Channel, u8 value);
u32 XGpio_chipMRead(XGpio * InstancePtr, u8 Channel);

#endif /* GPIO_API_H_ */
