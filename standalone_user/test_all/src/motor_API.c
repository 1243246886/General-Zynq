/*
 * motor_API.c
 *
 *  Created on: 2015Äê8ÔÂ13ÈÕ
 *      Author: harryfan
 */

#include <stdio.h>
#include "platform.h"
#include "xparameters.h"
#include "motor_API.h"
#include "pwm_API.h"

pid pid_l, pid_r;

int Speed_l, Speed_r;

void MotorInit(void) {
	init_Gpio(&Motor, MOTOR_GPIO_DEVICE_ID);
	PidInit();

	XGpio_descMWrite(&Motor, Motor_ch, Motor_L_Pin, Gpio_output);
	XGpio_descMWrite(&Motor, Motor_ch, Motor_R_Pin, Gpio_output);
}

u8 GetMotorDir(u8 Num) {
	u8 dir;
	if (Num == MotorL) {
		dir = QUADRATURE_ENCODER_IP_mReadReg(ENCODER_DEVICE_ID,
				QUADRATURE_ENCODER_IP_S00_AXI_SLV_REG2_OFFSET);
		if (dir == 1)
			dir = 0;
		else if (dir == 0)
			dir = 1;
	} else if (Num == MotorR) {
		dir = QUADRATURE_ENCODER_IP_mReadReg(ENCODER_DEVICE_ID,
				QUADRATURE_ENCODER_IP_S00_AXI_SLV_REG3_OFFSET);
	} else {
		return -1;
	}
	return dir;
}

short GetMotorSpeed(u8 Num) {
	short speed;
	if (Num == MotorL) {
		speed = -QUADRATURE_ENCODER_IP_mReadReg(ENCODER_DEVICE_ID,
				QUADRATURE_ENCODER_IP_S00_AXI_SLV_REG0_OFFSET);
	} else if (Num == MotorR) {
		speed = QUADRATURE_ENCODER_IP_mReadReg(ENCODER_DEVICE_ID,
				QUADRATURE_ENCODER_IP_S00_AXI_SLV_REG1_OFFSET);
	} else {
		return -1;
	}
	if ((speed & 0x8000) != 0x0000)
		speed = 0xffff0000 + speed;
	else
		speed = speed;
	return speed;
}

void PidInit(void) {
	pid_l.SetSpeed = 0;
	pid_l.ActualSpeed = 0;
	pid_l.err = 0;
	pid_l.err_last = 0;
	pid_l.voltage = 0.0;
	pid_l.integral = 0.0;
	pid_l.Kp = 1.4;
	pid_l.Ki = 0;
	pid_l.Kd = 0;
	pid_r.SetSpeed = 0;
	pid_r.ActualSpeed = 0;
	pid_r.err = 0;
	pid_r.err_last = 0;
	pid_r.voltage = 0.0;
	pid_r.integral = 0.0;
	pid_r.Kp = 1.4;
	pid_r.Ki = 0;
	pid_r.Kd = 0;
}

int MotorPidSpeed(pid *motor, int Num, int Speed) {
	motor->SetSpeed = Speed;
	motor->ActualSpeed = GetMotorSpeed(Num);
	motor->err = motor->SetSpeed - motor->ActualSpeed;
	motor->integral += motor->err;
	motor->voltage = motor->Kp * motor->err + motor->Ki * motor->integral
			+ motor->Kd * (motor->err - motor->err_last);
	motor->err_last = motor->err;
	motor->ActualSpeed = (int) motor->voltage;
	return motor->ActualSpeed;
}

void UpdateSpeed(void) {
	int SpeedPid;
	SpeedPid = MotorPidSpeed(&pid_l, MotorL, Speed_l);
	if (SpeedPid > 0) {
		XGpio_descWrite(&Motor, Motor_ch, Motor_L_Pin, Gpio_low);
	} else if (SpeedPid < 0) {
		XGpio_descWrite(&Motor, Motor_ch, Motor_L_Pin, Gpio_high);
		SpeedPid = -SpeedPid;
	}
	pwm_set(MotorPeriod, SpeedPid, MotorRPwm);
	SpeedPid = MotorPidSpeed(&pid_r, MotorR, Speed_r);
	if (SpeedPid > 0) {
		XGpio_descWrite(&Motor, Motor_ch, Motor_R_Pin, Gpio_low);
	} else if (SpeedPid < 0) {
		XGpio_descWrite(&Motor, Motor_ch, Motor_R_Pin, Gpio_high);
		SpeedPid = -SpeedPid;
	}
	pwm_set(MotorPeriod, SpeedPid, MotorLPwm);
}

void SetMotorSpeed(u8 Num, int Speed) {
	if (Num == MotorL) {
		Speed_l = Speed;
	} else if (Num == MotorR) {
		Speed_r = Speed;
	}
}

