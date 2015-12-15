/*
 * motor_API.h
 *
 *  Created on: 2015年8月13日
 *      Author: harryfan
 */

#ifndef MOTOR_API_H_
#define MOTOR_API_H_

#include "xgpio.h"
#include "Quadrature_Encoder_IP.h"
#include "gpio_API.h"

typedef struct {
	int SetSpeed; //定义设定值
	int ActualSpeed; //定义实际值
	int err; //定义偏差值
	int err_last; //定义上一个偏差值
	float Kp, Ki, Kd; //定义比例、积分、微分系数
	float voltage; //定义控制执行器的变量
	float integral; //定义积分值
} pid;

XGpio Motor;

#define ENCODER_DEVICE_ID	XPAR_QUADRATURE_ENCODER_IP_V1_0_0_BASEADDR
#define MOTOR_GPIO_DEVICE_ID	XPAR_GPIO_2_DEVICE_ID
#define Motor_ch	Gpio_ch1
#define Motor_L_Pin	Gpio3
#define Motor_R_Pin	Gpio0
#define	MotorLPwm	0
#define	MotorRPwm	1
#define MotorL		0
#define MotorR		1
#define	MotorPeriod	6250

u8 GetMotorDir(u8 Num);
short GetMotorSpeed(u8 Num);
void MotorInit(void);
void PidInit(void);
int MotorPidSpeed(pid *motor, int Num, int Speed);
void UpdateSpeed(void);
void SetMotorSpeed(u8 Num, int Speed);

#endif /* MOTOR_API_H_ */
