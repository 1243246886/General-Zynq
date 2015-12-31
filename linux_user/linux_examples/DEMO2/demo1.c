 /*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  12/18/2015 04:24:59 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Xinyu Chen (@.@), xinyuc@xilinx.com
 *        Company:  Xilinx XUP
 *
 * =====================================================================================
 */

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/time.h>
#include "../xlib/xil_pwm.h"
#include "xil_gpio.h"

#define IIO_XADC_PATH       "/sys/bus/iio/devices/iio:device0/%s"
#define XSM_SEQ_CH_AUX06    "in_voltage8_raw"
#define XSM_SEQ_CH_AUX07    "in_voltage9_raw"
#define XSM_SEQ_CH_AUX14   "in_voltage10_raw"
#define XSM_SEQ_CH_AUX15   "in_voltage11_raw"

#define XADC_SCALE          4095.0
#define PWM_BASE_ADDR 0x43C00000
#define GPIO_BASE_ADDR  0x41200000

int read_sysfs_temp(float *pValue)
{
    int i;
    float value[3];
    char filepath[3][200];
    sprintf(filepath[1], IIO_XADC_PATH, "in_temp0_offset");
    sprintf(filepath[0], IIO_XADC_PATH, "in_temp0_raw");
    sprintf(filepath[2], IIO_XADC_PATH, "in_temp0_scale");
    for(i=0;i<3;i++)
    {
        FILE *fd = fopen(filepath[i], "r");
        if(!fd)
        {
            printf("not found %s!\n", filepath[i]);
            return -1;
        }
        fscanf(fd, "%f", &value[i]);
        fclose(fd);
    }
    *pValue = (value[0] - value[1]) / value[2];
    return  0;
}

int read_sysfs_u32(char *filename, int *pValue)
{
    char filepath[200];
    
    sprintf(filepath, IIO_XADC_PATH, filename);
    FILE *fd = fopen(filepath, "r");
    if(!fd)
    {
        printf("not found %s!\n", filepath);
        return -1;
    }
    fscanf(fd, "%d", pValue);
    fclose(fd);
    
    return 0;
}

int main()
{

    int value;
    int i = 0;
    float temp;
    xil_pwm* mypwm = XilPWMCreate(PWM_BASE_ADDR);	 
    mypwm->setPeriod(mypwm, 0, 2000000);
    xil_gpio *my_gpio = XilGpioCreate(GPIO_BASE_ADDR);
    my_gpio->modeChipWrite(my_gpio,GPIO_CH1,0x00);
    while(1)
    {
  
        if(read_sysfs_u32(XSM_SEQ_CH_AUX06, &value) == 0)
        {
            printf("AUX06 voltage is %.3f\n", value / XADC_SCALE);
        }   
	 
	if(i == 20)
        {
	  i = 0;	
	  my_gpio->digitalChipWrite(my_gpio,GPIO_CH1,(value / XADC_SCALE)*36);		
        }	
	  mypwm->setDuty(mypwm, 0,(value / XADC_SCALE)*30);
		
          usleep(2000); i ++;
    }      
    return 0;
}
