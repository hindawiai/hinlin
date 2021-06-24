<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * USB Driver क्रम ALi m5602 based webcams
 *
 * Copyright (C) 2008 Erik Andrथऊn
 * Copyright (C) 2007 Ilyes Gouta. Based on the m5603x Linux Driver Project.
 * Copyright (C) 2005 m5603x Linux Driver Project <m5602@x3ng.com.br>
 *
 * Portions of code to USB पूर्णांकerface and ALi driver software,
 * Copyright (c) 2006 Willem Duinker
 * v4l2 पूर्णांकerface modeled after the V4L2 driver
 * क्रम SN9C10x PC Camera Controllers
 */

#अगर_अघोषित M5602_BRIDGE_H_
#घोषणा M5602_BRIDGE_H_

#समावेश <linux/slab.h>
#समावेश "gspca.h"

#घोषणा MODULE_NAME "ALi m5602"

/*****************************************************************************/

#घोषणा M5602_XB_SENSOR_TYPE		0x00
#घोषणा M5602_XB_SENSOR_CTRL		0x01
#घोषणा M5602_XB_LINE_OF_FRAME_H	0x02
#घोषणा M5602_XB_LINE_OF_FRAME_L	0x03
#घोषणा M5602_XB_PIX_OF_LINE_H		0x04
#घोषणा M5602_XB_PIX_OF_LINE_L		0x05
#घोषणा M5602_XB_VSYNC_PARA		0x06
#घोषणा M5602_XB_HSYNC_PARA		0x07
#घोषणा M5602_XB_TEST_MODE_1		0x08
#घोषणा M5602_XB_TEST_MODE_2		0x09
#घोषणा M5602_XB_SIG_INI		0x0a
#घोषणा M5602_XB_DS_PARA		0x0e
#घोषणा M5602_XB_TRIG_PARA		0x0f
#घोषणा M5602_XB_CLK_PD			0x10
#घोषणा M5602_XB_MCU_CLK_CTRL		0x12
#घोषणा M5602_XB_MCU_CLK_DIV		0x13
#घोषणा M5602_XB_SEN_CLK_CTRL		0x14
#घोषणा M5602_XB_SEN_CLK_DIV		0x15
#घोषणा M5602_XB_AUD_CLK_CTRL		0x16
#घोषणा M5602_XB_AUD_CLK_DIV		0x17
#घोषणा M5602_OB_AC_LINK_STATE		0x22
#घोषणा M5602_OB_PCM_SLOT_INDEX		0x24
#घोषणा M5602_OB_GPIO_SLOT_INDEX	0x25
#घोषणा M5602_OB_ACRX_STATUS_ADDRESS_H	0x28
#घोषणा M5602_OB_ACRX_STATUS_DATA_L	0x29
#घोषणा M5602_OB_ACRX_STATUS_DATA_H	0x2a
#घोषणा M5602_OB_ACTX_COMMAND_ADDRESS	0x31
#घोषणा M5602_OB_ACRX_COMMAND_DATA_L	0x32
#घोषणा M5602_OB_ACTX_COMMAND_DATA_H	0X33
#घोषणा M5602_XB_DEVCTR1		0x41
#घोषणा M5602_XB_EPSETR0		0x42
#घोषणा M5602_XB_EPAFCTR		0x47
#घोषणा M5602_XB_EPBFCTR		0x49
#घोषणा M5602_XB_EPEFCTR		0x4f
#घोषणा M5602_XB_TEST_REG		0x53
#घोषणा M5602_XB_ALT2SIZE		0x54
#घोषणा M5602_XB_ALT3SIZE		0x55
#घोषणा M5602_XB_OBSFRAME		0x56
#घोषणा M5602_XB_PWR_CTL		0x59
#घोषणा M5602_XB_ADC_CTRL		0x60
#घोषणा M5602_XB_ADC_DATA		0x61
#घोषणा M5602_XB_MISC_CTRL		0x62
#घोषणा M5602_XB_SNAPSHOT		0x63
#घोषणा M5602_XB_SCRATCH_1		0x64
#घोषणा M5602_XB_SCRATCH_2		0x65
#घोषणा M5602_XB_SCRATCH_3		0x66
#घोषणा M5602_XB_SCRATCH_4		0x67
#घोषणा M5602_XB_I2C_CTRL		0x68
#घोषणा M5602_XB_I2C_CLK_DIV		0x69
#घोषणा M5602_XB_I2C_DEV_ADDR		0x6a
#घोषणा M5602_XB_I2C_REG_ADDR		0x6b
#घोषणा M5602_XB_I2C_DATA		0x6c
#घोषणा M5602_XB_I2C_STATUS		0x6d
#घोषणा M5602_XB_GPIO_DAT_H		0x70
#घोषणा M5602_XB_GPIO_DAT_L		0x71
#घोषणा M5602_XB_GPIO_सूची_H		0x72
#घोषणा M5602_XB_GPIO_सूची_L		0x73
#घोषणा M5602_XB_GPIO_EN_H		0x74
#घोषणा M5602_XB_GPIO_EN_L		0x75
#घोषणा M5602_XB_GPIO_DAT		0x76
#घोषणा M5602_XB_GPIO_सूची		0x77
#घोषणा M5602_XB_SEN_CLK_CONTROL	0x80
#घोषणा M5602_XB_SEN_CLK_DIVISION	0x81
#घोषणा M5602_XB_CPR_CLK_CONTROL	0x82
#घोषणा M5602_XB_CPR_CLK_DIVISION	0x83
#घोषणा M5602_XB_MCU_CLK_CONTROL	0x84
#घोषणा M5602_XB_MCU_CLK_DIVISION	0x85
#घोषणा M5602_XB_DCT_CLK_CONTROL	0x86
#घोषणा M5602_XB_DCT_CLK_DIVISION	0x87
#घोषणा M5602_XB_EC_CLK_CONTROL		0x88
#घोषणा M5602_XB_EC_CLK_DIVISION	0x89
#घोषणा M5602_XB_LBUF_CLK_CONTROL	0x8a
#घोषणा M5602_XB_LBUF_CLK_DIVISION	0x8b

#घोषणा I2C_BUSY 0x80

/*****************************************************************************/

/* Driver info */
#घोषणा DRIVER_AUTHOR "ALi m5602 Linux Driver Project"
#घोषणा DRIVER_DESC "ALi m5602 webcam driver"

#घोषणा M5602_ISOC_ENDPOINT_ADDR 0x81
#घोषणा M5602_INTR_ENDPOINT_ADDR 0x82

#घोषणा M5602_URB_MSG_TIMEOUT   5000

/*****************************************************************************/

काष्ठा sd अणु
	काष्ठा gspca_dev gspca_dev;

	/* A poपूर्णांकer to the currently connected sensor */
	स्थिर काष्ठा m5602_sensor *sensor;

	/* The current frame's id, used to detect frame boundaries */
	u8 frame_id;

	/* The current frame count */
	u32 frame_count;

	/* Camera rotation polling thपढ़ो क्रम "flipable" cams */
	काष्ठा task_काष्ठा *rotation_thपढ़ो;

	काष्ठा अणु /* स्वतः-white-bal + green/red/blue balance control cluster */
		काष्ठा v4l2_ctrl *स्वतः_white_bal;
		काष्ठा v4l2_ctrl *red_bal;
		काष्ठा v4l2_ctrl *blue_bal;
		काष्ठा v4l2_ctrl *green_bal;
	पूर्ण;
	काष्ठा अणु /* स्वतःexpo / expo cluster */
		काष्ठा v4l2_ctrl *स्वतःexpo;
		काष्ठा v4l2_ctrl *expo;
	पूर्ण;
	काष्ठा अणु /* स्वतःgain / gain cluster */
		काष्ठा v4l2_ctrl *स्वतःgain;
		काष्ठा v4l2_ctrl *gain;
	पूर्ण;
	काष्ठा अणु /* hflip/vflip cluster */
		काष्ठा v4l2_ctrl *hflip;
		काष्ठा v4l2_ctrl *vflip;
	पूर्ण;
पूर्ण;

पूर्णांक m5602_पढ़ो_bridge(
	काष्ठा sd *sd, स्थिर u8 address, u8 *i2c_data);

पूर्णांक m5602_ग_लिखो_bridge(
	काष्ठा sd *sd, स्थिर u8 address, स्थिर u8 i2c_data);

पूर्णांक m5602_ग_लिखो_sensor(काष्ठा sd *sd, स्थिर u8 address,
		       u8 *i2c_data, स्थिर u8 len);

पूर्णांक m5602_पढ़ो_sensor(काष्ठा sd *sd, स्थिर u8 address,
		      u8 *i2c_data, स्थिर u8 len);

#पूर्ण_अगर
