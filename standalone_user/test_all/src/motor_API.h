/*
 * motor_API.h
 *
 *  Created on: 2015��8��13��
 *      Author: harryfan
 */

#ifndef MOTOR_API_H_
#define MOTOR_API_H_

#include "xgpio.h"
#include "Quadrature_Encoder_IP.h"
#include "gpio_API.h"

typedef struct {
	int SetSpeed; //�����趨ֵ
	int ActualSpeed; //����ʵ��ֵ
	int err; //����ƫ��ֵ
	int err_last; //������һ��ƫ��ֵ
	float Kp, Ki, Kd; //������������֡�΢��ϵ��
	float voltage; //�������ִ�����ı���
	float integral; //�������ֵ
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
