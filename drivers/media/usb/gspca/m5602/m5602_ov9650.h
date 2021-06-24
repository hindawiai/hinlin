<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Driver क्रम the ov9650 sensor
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

#अगर_अघोषित M5602_OV9650_H_
#घोषणा M5602_OV9650_H_

#समावेश <linux/dmi.h>
#समावेश "m5602_sensor.h"

/*****************************************************************************/

#घोषणा OV9650_GAIN			0x00
#घोषणा OV9650_BLUE			0x01
#घोषणा OV9650_RED			0x02
#घोषणा OV9650_VREF			0x03
#घोषणा OV9650_COM1			0x04
#घोषणा OV9650_BAVE			0x05
#घोषणा OV9650_GEAVE			0x06
#घोषणा OV9650_RSVD7			0x07
#घोषणा OV9650_COM2			0x09
#घोषणा OV9650_PID			0x0a
#घोषणा OV9650_VER			0x0b
#घोषणा OV9650_COM3			0x0c
#घोषणा OV9650_COM4			0x0d
#घोषणा OV9650_COM5			0x0e
#घोषणा OV9650_COM6			0x0f
#घोषणा OV9650_AECH			0x10
#घोषणा OV9650_CLKRC			0x11
#घोषणा OV9650_COM7			0x12
#घोषणा OV9650_COM8			0x13
#घोषणा OV9650_COM9			0x14
#घोषणा OV9650_COM10			0x15
#घोषणा OV9650_RSVD16			0x16
#घोषणा OV9650_HSTART			0x17
#घोषणा OV9650_HSTOP			0x18
#घोषणा OV9650_VSTRT			0x19
#घोषणा OV9650_VSTOP			0x1a
#घोषणा OV9650_PSHFT			0x1b
#घोषणा OV9650_MVFP			0x1e
#घोषणा OV9650_AEW			0x24
#घोषणा OV9650_AEB			0x25
#घोषणा OV9650_VPT			0x26
#घोषणा OV9650_BBIAS			0x27
#घोषणा OV9650_GbBIAS			0x28
#घोषणा OV9650_Gr_COM			0x29
#घोषणा OV9650_RBIAS			0x2c
#घोषणा OV9650_HREF			0x32
#घोषणा OV9650_CHLF			0x33
#घोषणा OV9650_ARBLM			0x34
#घोषणा OV9650_RSVD35			0x35
#घोषणा OV9650_RSVD36			0x36
#घोषणा OV9650_ADC			0x37
#घोषणा OV9650_ACOM38			0x38
#घोषणा OV9650_OFON			0x39
#घोषणा OV9650_TSLB			0x3a
#घोषणा OV9650_COM12			0x3c
#घोषणा OV9650_COM13			0x3d
#घोषणा OV9650_COM15			0x40
#घोषणा OV9650_COM16			0x41
#घोषणा OV9650_LCC1			0x62
#घोषणा OV9650_LCC2			0x63
#घोषणा OV9650_LCC3			0x64
#घोषणा OV9650_LCC4			0x65
#घोषणा OV9650_LCC5			0x66
#घोषणा OV9650_HV			0x69
#घोषणा OV9650_DBLV			0x6b
#घोषणा OV9650_COM21			0x8b
#घोषणा OV9650_COM22			0x8c
#घोषणा OV9650_COM24			0x8e
#घोषणा OV9650_DBLC1			0x8f
#घोषणा OV9650_RSVD94			0x94
#घोषणा OV9650_RSVD95			0x95
#घोषणा OV9650_RSVD96			0x96
#घोषणा OV9650_LCCFB			0x9d
#घोषणा OV9650_LCCFR			0x9e
#घोषणा OV9650_AECHM			0xa1
#घोषणा OV9650_COM26			0xa5
#घोषणा OV9650_ACOMA8			0xa8
#घोषणा OV9650_ACOMA9			0xa9

#घोषणा OV9650_REGISTER_RESET		(1 << 7)
#घोषणा OV9650_VGA_SELECT		(1 << 6)
#घोषणा OV9650_CIF_SELECT		(1 << 5)
#घोषणा OV9650_QVGA_SELECT		(1 << 4)
#घोषणा OV9650_QCIF_SELECT		(1 << 3)
#घोषणा OV9650_RGB_SELECT		(1 << 2)
#घोषणा OV9650_RAW_RGB_SELECT		(1 << 0)

#घोषणा OV9650_FAST_AGC_AEC		(1 << 7)
#घोषणा OV9650_AEC_UNLIM_STEP_SIZE	(1 << 6)
#घोषणा OV9650_BANDING			(1 << 5)
#घोषणा OV9650_AGC_EN			(1 << 2)
#घोषणा OV9650_AWB_EN			(1 << 1)
#घोषणा OV9650_AEC_EN			(1 << 0)

#घोषणा OV9650_VARIOPIXEL		(1 << 2)
#घोषणा OV9650_SYSTEM_CLK_SEL		(1 << 7)
#घोषणा OV9650_SLAM_MODE		(1 << 4)

#घोषणा OV9650_QVGA_VARIOPIXEL		(1 << 7)

#घोषणा OV9650_VFLIP			(1 << 4)
#घोषणा OV9650_HFLIP			(1 << 5)

#घोषणा OV9650_SOFT_SLEEP		(1 << 4)
#घोषणा OV9650_OUTPUT_DRIVE_2X		(1 << 0)

#घोषणा OV9650_DENOISE_ENABLE		(1 << 5)
#घोषणा OV9650_WHITE_PIXEL_ENABLE	(1 << 1)
#घोषणा OV9650_WHITE_PIXEL_OPTION	(1 << 0)

#घोषणा OV9650_LEFT_OFFSET		0x62

#घोषणा GAIN_DEFAULT			0x14
#घोषणा RED_GAIN_DEFAULT		0x70
#घोषणा BLUE_GAIN_DEFAULT		0x20
#घोषणा EXPOSURE_DEFAULT		0x1ff

/*****************************************************************************/

/* Kernel module parameters */
बाह्य पूर्णांक क्रमce_sensor;
बाह्य bool dump_sensor;

पूर्णांक ov9650_probe(काष्ठा sd *sd);
पूर्णांक ov9650_init(काष्ठा sd *sd);
पूर्णांक ov9650_init_controls(काष्ठा sd *sd);
पूर्णांक ov9650_start(काष्ठा sd *sd);
पूर्णांक ov9650_stop(काष्ठा sd *sd);
व्योम ov9650_disconnect(काष्ठा sd *sd);

अटल स्थिर काष्ठा m5602_sensor ov9650 = अणु
	.name = "OV9650",
	.i2c_slave_id = 0x60,
	.i2c_regW = 1,
	.probe = ov9650_probe,
	.init = ov9650_init,
	.init_controls = ov9650_init_controls,
	.start = ov9650_start,
	.stop = ov9650_stop,
	.disconnect = ov9650_disconnect,
पूर्ण;

#पूर्ण_अगर
