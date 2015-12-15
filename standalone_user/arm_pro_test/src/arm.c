/*
 * arm.c
 *
 *  Created on: 2015Äê8ÔÂ19ÈÕ
 *      Author: harryfan
 */
#include "arm.h"

static XGpio ArmGpio;
static XGpio BTN;
static s16 ServoPwmMin[4];
static s16 ServoPwmMax[4];
static s16 heightLst;
static u8 gripperRst = 0;
static float tmp_height = 0;

int ArmInit(void) {
	int Status = 0;
	u8 i;
	Status |= init_Gpio(&ArmGpio, ARM_GPIO_DEVICE_ID);
	Status |= init_Gpio(&BTN, BTN_GPIO_DEVICE_ID);
	Status |= EepromInit();
	Status |= AdcInit();
	for (i = 0; i < 3; i++) {
		ServoPwmMin[i] = D150A_SERVO_MIN_PUL;
		ServoPwmMax[i] = D150A_SERVO_MAX_PUL;
	}
	ServoPwmMin[3] = D009A_SERVO_MIN_PUL;
	ServoPwmMax[3] = D009A_SERVO_MAX_PUL;

	XGpio_descMWrite(&ArmGpio, Gpio_ch1, PUMP_EN, Gpio_output);
	XGpio_descMWrite(&ArmGpio, Gpio_ch1, VALVE_EN, Gpio_output);
	XGpio_descMWrite(&ArmGpio, Gpio_ch1, LIMIT_SW, Gpio_input);

	XGpio_descMWrite(&BTN, Gpio_ch2, BTN3, Gpio_input);

	XGpio_descWrite(&ArmGpio, Gpio_ch1, PUMP_EN, Gpio_low);
	XGpio_descWrite(&ArmGpio, Gpio_ch1, VALVE_EN, Gpio_low);

	return Status;
}

float constrain(float x, float a, float b) {
	if (x > a && x < b)
		return x;
	else if (x <= a)
		return a;
	else
		return b;
}

unsigned int uArm_ADRead(unsigned char Channel) {
	int i = 0, adAdd = 0;
	for (i = 0; i < 5; i++) {
		adAdd += AdcGet(Channel);
	}
	return adAdd / 5;
}

void uArm_ServoClear(void) {
	u8 j;
	for (j = 0; j < 4; j++) {
		pwm_set(SERVO_PERIOD, 0, j);
	}
}

void uArm_ServoWrite(s16 angle, u8 Servo_Channel) {
	u16 pwm_duty = ServoPwmMin[Servo_Channel]
			+ (ServoPwmMax[Servo_Channel] - ServoPwmMin[Servo_Channel]) / 180
					* angle;
	float pwm = pwm_duty * 100.0 / 20000;
	pwm_set(SERVO_PERIOD, pwm, Servo_Channel);
}

void uArm_SetPosition(float _stretch, float _height, s16 _armRot, s16 _handRot) {
	float stretch2height2, angleA, angleB, angleC;
	signed char data[3] = {0};
	EepromRead(0x00,data,3);
	signed char offset_l = data[1];
	signed char offset_r = data[2];
	//xil_printf("L is %d, R is %d!\r\n",offset_l,offset_r);

	s16 angleR, angleL;
	_armRot = -_armRot;
	if (!XGpio_descRead(&ArmGpio, Gpio_ch1, LIMIT_SW) && _height < heightLst) //limit switch protection
		_height = heightLst;
	// input limit
	_stretch = constrain(_stretch, ARM_STRETCH_MIN, ARM_STRETCH_MAX) + 55; // +55, set stretch zero
	_height = constrain(_height, ARM_HEIGHT_MIN, ARM_HEIGHT_MAX);
	_armRot = constrain(_armRot, ARM_ROTATION_MIN, ARM_ROTATION_MAX) + 90; // +90, change -90~90 to 0~180
	_handRot = constrain(_handRot, HAND_ROTATION_MIN, HAND_ROTATION_MAX) + 90; // +90, change -90~90 to 0~180
	// angle calculation
	stretch2height2 = _stretch * _stretch + _height * _height;              //
	angleA = acos((ARM_A2B2 - stretch2height2) / ARM_2AB) * RAD_TO_DEG; // angle between the upper and the lower
	angleB = atan(_height / _stretch) * RAD_TO_DEG;                         //
	angleC = acos(
			(ARM_A2 + stretch2height2 - ARM_B2)
					/ (2 * ARM_A * sqrt(stretch2height2))) * RAD_TO_DEG; //
	angleR = 180 - angleA - angleB - angleC + FIXED_OFFSET_R + offset_r;      //
	angleL = angleB + angleC + FIXED_OFFSET_L + offset_l;                     //
	// angle limit
	angleL = constrain(angleL, 10 + offset_l, 145 + offset_l);
	angleR = constrain(angleR, 25 + offset_r, 150 + offset_r);
	angleR = constrain(angleR, angleL - 90 + offset_r, angleR);	// behind  -120+30 = -90

	if (angleL < 15 + offset_l)
		angleR = constrain(angleR, 70 + offset_r, angleR);		// front down
	// set servo position

	uArm_ServoWrite(angleR, SERVO_R);
	uArm_ServoWrite(angleL, SERVO_L);
	uArm_ServoWrite(_armRot, SERVO_ROT);
	uArm_ServoWrite(_handRot, SERVO_HANDROT);
	heightLst = _height;
}

//X, Y coordinate convert to _stretch, _armRot
void xyToSR(double set_X, double set_Y, float *set_stretch, s16 *set_armRot) {
	double setx = (double) (set_X + 55); //55mm
	double x2y2 = setx * setx + set_Y * set_Y;
	*set_stretch = sqrt(x2y2) - 55;
	*set_armRot = (atan(set_Y / (setx + 61))) * RAD_TO_DEG; // set_X + 55m + 61mm
}

void uArm_GripperCatch(void) {
	if (gripperRst == 0) {
		XGpio_descWrite(&ArmGpio, Gpio_ch1, VALVE_EN, Gpio_high);
		XGpio_descWrite(&ArmGpio, Gpio_ch1, PUMP_EN, Gpio_low);
		gripperRst = 1;
	}
}

void uArm_GripperRelease(void) {
	XGpio_descWrite(&ArmGpio, Gpio_ch1, VALVE_EN, Gpio_low);
	XGpio_descWrite(&ArmGpio, Gpio_ch1, PUMP_EN, Gpio_high);
	gripperRst = 0;
}

void ArmMove(s16 coX, s16 coY, s16 coZ, s16 handRotation) {
	float set_stretch;
	s16 set_armRot;

	xyToSR(coX, coY, &set_stretch, &set_armRot);
	uArm_SetPosition(set_stretch, coZ, set_armRot, handRotation);
}

void ArmGet(s16 co_x, s16 co_y, s16 co_z, s16 handRotation, u8 limit_en) {
	float in_stretch;
	s16 in_armRot;

	xyToSR(co_x, co_y, &in_stretch, &in_armRot);
	if (limit_en == TRUE) {
		while (1 == XGpio_descRead(&ArmGpio, 1, LIMIT_SW)) {
			tmp_height -= 2;
			uArm_SetPosition(in_stretch, co_z + tmp_height, in_armRot, handRotation);
			usleep(20000);
		}
	}
	uArm_GripperCatch();
	usleep(400000);
	while (tmp_height < 0) {
		tmp_height = tmp_height + 2;
		uArm_SetPosition(in_stretch, co_z + tmp_height, in_armRot, handRotation);
		usleep(20000);
	}
}

void ArmPut(s16 co_x, s16 co_y, s16 co_z, s16 handRotation, u8 limit_en) {
	float in_stretch;
	s16 in_armRot;

	xyToSR(co_x, co_y, &in_stretch, &in_armRot);
	if (limit_en == TRUE) {
		while (1 == XGpio_descRead(&ArmGpio, 1, LIMIT_SW)) {
			tmp_height -= 2;
			uArm_SetPosition(in_stretch, co_z + tmp_height, in_armRot, handRotation);
			usleep(20000);
		}
	}
	uArm_GripperRelease();
	usleep(400000);
	while (tmp_height < 0) {
		tmp_height = tmp_height + 2;
		uArm_SetPosition(in_stretch, co_z + tmp_height, in_armRot, handRotation);
		usleep(20000);
	}
}

void uArm_OffsetInitialize(void) {
	signed char data[3] = { 0 };
	EepromRead(0x00, data, 3);


	if (data[0] != CALIBRATION_FLAG) // read of offset flag
	{
		xil_printf("Warning: Calibration should be done first!\r\n");
	} else {
		xil_printf("Calibration have been done! Enjoy your project!\r\n");
		uArm_SetPosition(0, 0, 0, 0);
	}
}

void calibration(void) {
	int initPosL = INIT_POS_L + 20; // Added 20 degrees here to start at reasonable point
	int initPosR = INIT_POS_R + 20; // Added 20 degrees here to start at reasonable point

	signed char send_data[3];

	if (XGpio_descRead(&BTN, 2, BTN3)) {
		sleep(2);
		if (XGpio_descRead(&BTN, 2, BTN3)) {
			uArm_ServoClear();
			xil_printf("calibration: detach ...\r\n");
			while (XGpio_descRead(&BTN, 2, BTN3));
			usleep(500 * 1000);

			while (1) {
				int minAngle_L = uArm_ADRead(SERVO_L_AD) + 15;
				int minAngle_R = uArm_ADRead(SERVO_R_AD) + 15;

				if (XGpio_descRead(&BTN, 2, BTN3)) {
					printf("Start calibration ...\r\n");
					usleep(500000);
					uArm_ServoWrite(initPosR, SERVO_R);
					uArm_ServoWrite(initPosL, SERVO_L);
					usleep(500000);

					while (uArm_ADRead(SERVO_R_AD)
							< minAngle_R - SAMPLING_DEADZONE) {
						uArm_ServoWrite(++initPosR, SERVO_R);
						usleep(50000);
					}

					while (uArm_ADRead(SERVO_R_AD)
							< minAngle_R - SAMPLING_DEADZONE) {
						uArm_ServoWrite(++initPosR, SERVO_R);
						usleep(50000);
					}

					while (uArm_ADRead(SERVO_L_AD)
							< minAngle_L - SAMPLING_DEADZONE) {
						uArm_ServoWrite(++initPosL, SERVO_L);
						usleep(50000);
					}

					while (uArm_ADRead(SERVO_L_AD)
							< minAngle_L - SAMPLING_DEADZONE) {
						uArm_ServoWrite(++initPosL, SERVO_L);
						usleep(50000);
					}

					send_data[0] = CALIBRATION_FLAG;
					send_data[1] = initPosL - INIT_POS_L;
					send_data[2] = initPosR - INIT_POS_R;

					EepromWrite(0x00, send_data, 3);
					uArm_OffsetInitialize();
					break;
				}
			}
		}
	}
}

