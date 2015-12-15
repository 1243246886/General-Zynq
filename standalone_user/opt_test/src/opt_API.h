/*
 * opt_API.h
 *
 *  Created on: 2015Äê8ÔÂ12ÈÕ
 *      Author: harryfan
 */

#ifndef OPT_API_H_
#define OPT_API_H_

#include "xgpio.h"
#include "gpio_API.h"

#define OPT_GPIO_DEVICE_ID	XPAR_GPIO_2_DEVICE_ID

#define	Opt1	Gpio3
#define	Opt2	Gpio2
#define	Opt3	Gpio0
#define	Opt4	Gpio1
#define	Opt5	Gpio4

#define	Opt_ch	Gpio_ch2

#define	Opt_Dir	Gpio_input

void SetOptDirection(void);
int OptInit(void);
int OptGetSingle(int OptNum, u8 *OptVal);
u8 OptGetAll();

#endif /* OPT_API_H_ */
