 /*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  12/18/2015 04:24:50 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Xinyu Chen (@.@), xinyuc@xilinx.com
 *        Company:  Xilinx XUP
 *
 * =====================================================================================
 */


#include "xil_gpio.h"

#define GPIO_BASE_ADDR  0x41200000
#define LD0 0
#define LD1 1
#define LD4 7

/**
    当对PS的MIO进行整个bank操作的时候，mode的值与axi gpio相反
    0x0 全输入  0xffff ffff 全输出
 **/

int main()
{

    int i;
    xil_gpio *my_gpio = XilGpioCreate(GPIO_BASE_ADDR);
   
    my_gpio->modeChipWrite(my_gpio,GPIO_CH1,0x00);
	my_gpio->modeChipWrite(my_gpio,GPIO_CH2,0xff);
	
	while(1)
	{
		 my_gpio->digitalChipWrite(my_gpio,GPIO_CH1,my_gpio->digitalChipRead(my_gpio,GPIO_CH2));	
	}
	XilGpioDestroy(my_gpio);
    return 0;
}
