/* Copyright (c) 2011-2013, The Linux Foundation. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#ifndef _SENSOR_DRIVER_H_
#define _SENSOR_DRIVER_H_

#include <linux/kernel.h>

#include "hisi_sensor.h"



#define GPIO_8_0	64
#define GPIO_8_1	65
#define GPIO_8_2	66
#define GPIO_8_3	67
#define GPIO_8_4	68
#define GPIO_8_5	69
#define GPIO_8_6	70
#define GPIO_8_7	71

#define GPIO_9_0	72
#define GPIO_9_1	73
#define GPIO_9_2	74
#define GPIO_9_3	75
#define GPIO_9_4	76
#define GPIO_9_5	77
#define GPIO_9_6	78
#define GPIO_9_7	79

#define GPIO_10_0	80
#define GPIO_10_1	81
#define GPIO_10_2	82
#define GPIO_10_3	83
#define GPIO_10_4	84
#define GPIO_10_5	85
#define GPIO_10_6	86
#define GPIO_10_7	87

#define GPIO_11_0	88
#define GPIO_11_1	89
#define GPIO_11_2	90
#define GPIO_11_3	91
#define GPIO_11_4	92
#define GPIO_11_5	93
#define GPIO_11_6	94
#define GPIO_11_7	95

#define GPIO_12_0	96
#define GPIO_12_1	97
#define GPIO_12_2	98
#define GPIO_12_3	99
#define GPIO_12_4	100
#define GPIO_12_5	101
#define GPIO_12_6	102
#define GPIO_12_7	103

#define GPIO_13_0	104
#define GPIO_13_1	105

#define REG_ISP_CLK_DIVIDER             	(0x63023)

#define I2C_SPEED            			(0x00)
#define I2C_SLAVE_ID         			(0x01)
#define I2C_2BYTE_CONTROL    			(0x06)

#define SENSOR0_MCLK_DIV		0x44
#define SENSOR1_MCLK_DIV		0x44

#define REG_ISP_GPIO_SEL                (0x6302f)
#define REG_ISP_GPIO_CTL_H              (0x63030)
#define REG_ISP_GPIO_CTL_L              (0x63031)
#define REG_GPIO_R_REQ_CTRL_72        	(0x63d72)
#define REG_GPIO_R_REQ_CTRL_74        	(0x63d74)

/********************extern function declare**************************/
int hisi_sensor_power_up(struct hisi_sensor_ctrl_t *s_ctrl);
int hisi_sensor_power_down(struct hisi_sensor_ctrl_t *s_ctrl);
int hisi_sensor_i2c_read(struct hisi_sensor_ctrl_t *s_ctrl, void *data);
int hisi_sensor_i2c_write(struct hisi_sensor_ctrl_t *s_ctrl, void *data);
int hisi_sensor_i2c_read_seq(struct hisi_sensor_ctrl_t *s_ctrl, void *data);
int hisi_sensor_i2c_write_seq(struct hisi_sensor_ctrl_t *s_ctrl, void *data);
int hisi_sensor_apply_expo_gain(struct hisi_sensor_ctrl_t *s_ctrl, void *data);
int hisi_sensor_suspend_eg_task(struct hisi_sensor_ctrl_t *s_ctrl, void *data);
int hisi_sensor_apply_bshutter_expo_gain(struct hisi_sensor_ctrl_t *s_ctrl, void *data);

#endif /*_SENSOR_DRIVER_H_*/
