<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Driver क्रम the po1030 sensor.
 *
 * Copyright (c) 2008 Erik Andrथऊn
 * Copyright (c) 2007 Ilyes Gouta. Based on the m5603x Linux Driver Project.
 * Copyright (c) 2005 m5603x Linux Driver Project <m5602@x3ng.com.br>
 *
 * Portions of code to USB पूर्णांकerface and ALi driver software,
 * Copyright (c) 2006 Willem Duinker
 * v4l2 पूर्णांकerface modeled after the V4L2 driver
 * क्रम SN9C10x PC Camera Controllers
 *
 * Register defines taken from Pascal Stangs Procyon Armlib
 */

#अगर_अघोषित M5602_PO1030_H_
#घोषणा M5602_PO1030_H_

#समावेश "m5602_sensor.h"

/*****************************************************************************/

#घोषणा PO1030_DEVID_H		0x00
#घोषणा PO1030_DEVID_L		0x01
#घोषणा PO1030_FRAMEWIDTH_H	0x04
#घोषणा PO1030_FRAMEWIDTH_L	0x05
#घोषणा PO1030_FRAMEHEIGHT_H	0x06
#घोषणा PO1030_FRAMEHEIGHT_L	0x07
#घोषणा PO1030_WINDOWX_H	0x08
#घोषणा PO1030_WINDOWX_L	0x09
#घोषणा PO1030_WINDOWY_H	0x0a
#घोषणा PO1030_WINDOWY_L	0x0b
#घोषणा PO1030_WINDOWWIDTH_H	0x0c
#घोषणा PO1030_WINDOWWIDTH_L	0x0d
#घोषणा PO1030_WINDOWHEIGHT_H	0x0e
#घोषणा PO1030_WINDOWHEIGHT_L	0x0f

#घोषणा PO1030_GLOBALIBIAS	0x12
#घोषणा PO1030_PIXELIBIAS	0x13

#घोषणा PO1030_GLOBALGAIN	0x15
#घोषणा PO1030_RED_GAIN		0x16
#घोषणा PO1030_GREEN_1_GAIN	0x17
#घोषणा PO1030_BLUE_GAIN	0x18
#घोषणा PO1030_GREEN_2_GAIN	0x19

#घोषणा PO1030_INTEGLINES_H	0x1a
#घोषणा PO1030_INTEGLINES_M	0x1b
#घोषणा PO1030_INTEGLINES_L	0x1c

#घोषणा PO1030_CONTROL1		0x1d
#घोषणा PO1030_CONTROL2		0x1e
#घोषणा PO1030_CONTROL3		0x1f
#घोषणा PO1030_CONTROL4		0x20

#घोषणा PO1030_PERIOD50_H	0x23
#घोषणा PO1030_PERIOD50_L	0x24
#घोषणा PO1030_PERIOD60_H	0x25
#घोषणा PO1030_PERIOD60_L	0x26
#घोषणा PO1030_REGCLK167	0x27
#घोषणा PO1030_FLICKER_DELTA50	0x28
#घोषणा PO1030_FLICKERDELTA60	0x29

#घोषणा PO1030_ADCOFFSET	0x2c

/* Gamma Correction Coeffs */
#घोषणा PO1030_GC0		0x2d
#घोषणा PO1030_GC1		0x2e
#घोषणा PO1030_GC2		0x2f
#घोषणा PO1030_GC3		0x30
#घोषणा PO1030_GC4		0x31
#घोषणा PO1030_GC5		0x32
#घोषणा PO1030_GC6		0x33
#घोषणा PO1030_GC7		0x34

/* Color Transक्रमm Matrix */
#घोषणा PO1030_CT0		0x35
#घोषणा PO1030_CT1		0x36
#घोषणा PO1030_CT2		0x37
#घोषणा PO1030_CT3		0x38
#घोषणा PO1030_CT4		0x39
#घोषणा PO1030_CT5		0x3a
#घोषणा PO1030_CT6		0x3b
#घोषणा PO1030_CT7		0x3c
#घोषणा PO1030_CT8		0x3d

#घोषणा PO1030_AUTOCTRL1	0x3e
#घोषणा PO1030_AUTOCTRL2	0x3f

#घोषणा PO1030_YTARGET		0x40
#घोषणा PO1030_GLOBALGAINMIN	0x41
#घोषणा PO1030_GLOBALGAINMAX	0x42

#घोषणा PO1030_AWB_RED_TUNING	0x47
#घोषणा PO1030_AWB_BLUE_TUNING	0x48

/* Output क्रमmat control */
#घोषणा PO1030_OUTFORMCTRL1	0x5a
#घोषणा PO1030_OUTFORMCTRL2	0x5b
#घोषणा PO1030_OUTFORMCTRL3	0x5c
#घोषणा PO1030_OUTFORMCTRL4	0x5d
#घोषणा PO1030_OUTFORMCTRL5	0x5e

#घोषणा PO1030_EDGE_ENH_OFF	0x5f
#घोषणा PO1030_EGA		0x60

#घोषणा PO1030_Cb_U_GAIN	0x63
#घोषणा PO1030_Cr_V_GAIN	0x64

#घोषणा PO1030_YCONTRAST	0x74
#घोषणा PO1030_YSATURATION	0x75

#घोषणा PO1030_HFLIP		(1 << 7)
#घोषणा PO1030_VFLIP		(1 << 6)

#घोषणा PO1030_HREF_ENABLE	(1 << 6)

#घोषणा PO1030_RAW_RGB_BAYER	0x4

#घोषणा PO1030_FRAME_EQUAL	(1 << 3)
#घोषणा PO1030_AUTO_SUBSAMPLING (1 << 4)

#घोषणा PO1030_WEIGHT_WIN_2X	(1 << 3)

#घोषणा PO1030_SHUTTER_MODE	(1 << 6)
#घोषणा PO1030_AUTO_SUBSAMPLING	(1 << 4)
#घोषणा PO1030_FRAME_EQUAL	(1 << 3)

#घोषणा PO1030_SENSOR_RESET	(1 << 5)

#घोषणा PO1030_SUBSAMPLING	(1 << 6)

/*****************************************************************************/

#घोषणा PO1030_GLOBAL_GAIN_DEFAULT	0x12
#घोषणा PO1030_EXPOSURE_DEFAULT		0x0085
#घोषणा PO1030_BLUE_GAIN_DEFAULT	0x36
#घोषणा PO1030_RED_GAIN_DEFAULT		0x36
#घोषणा PO1030_GREEN_GAIN_DEFAULT	0x40

/*****************************************************************************/

/* Kernel module parameters */
बाह्य पूर्णांक क्रमce_sensor;
बाह्य bool dump_sensor;

पूर्णांक po1030_probe(काष्ठा sd *sd);
पूर्णांक po1030_init(काष्ठा sd *sd);
पूर्णांक po1030_init_controls(काष्ठा sd *sd);
पूर्णांक po1030_start(काष्ठा sd *sd);
व्योम po1030_disconnect(काष्ठा sd *sd);

अटल स्थिर काष्ठा m5602_sensor po1030 = अणु
	.name = "PO1030",

	.i2c_slave_id = 0xdc,
	.i2c_regW = 1,

	.probe = po1030_probe,
	.init = po1030_init,
	.init_controls = po1030_init_controls,
	.start = po1030_start,
	.disconnect = po1030_disconnect,
पूर्ण;
#पूर्ण_अगर
