<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Driver क्रम the ov7660 sensor
 *
 * Copyright (C) 2009 Erik Andrथऊn
 * Copyright (C) 2007 Ilyes Gouta. Based on the m5603x Linux Driver Project.
 * Copyright (C) 2005 m5603x Linux Driver Project <m5602@x3ng.com.br>
 *
 * Portions of code to USB पूर्णांकerface and ALi driver software,
 * Copyright (c) 2006 Willem Duinker
 * v4l2 पूर्णांकerface modeled after the V4L2 driver
 * क्रम SN9C10x PC Camera Controllers
 */

#अगर_अघोषित M5602_OV7660_H_
#घोषणा M5602_OV7660_H_

#समावेश "m5602_sensor.h"

#घोषणा OV7660_GAIN		0x00
#घोषणा OV7660_BLUE_GAIN	0x01
#घोषणा OV7660_RED_GAIN		0x02
#घोषणा OV7660_VREF		0x03
#घोषणा OV7660_COM1		0x04
#घोषणा OV7660_BAVE		0x05
#घोषणा OV7660_GEAVE		0x06
#घोषणा OV7660_AECHH		0x07
#घोषणा OV7660_RAVE		0x08
#घोषणा OV7660_COM2		0x09
#घोषणा OV7660_PID		0x0a
#घोषणा OV7660_VER		0x0b
#घोषणा OV7660_COM3		0x0c
#घोषणा OV7660_COM4		0x0d
#घोषणा OV7660_COM5		0x0e
#घोषणा OV7660_COM6		0x0f
#घोषणा OV7660_AECH		0x10
#घोषणा OV7660_CLKRC		0x11
#घोषणा OV7660_COM7		0x12
#घोषणा OV7660_COM8		0x13
#घोषणा OV7660_COM9		0x14
#घोषणा OV7660_COM10		0x15
#घोषणा OV7660_RSVD16		0x16
#घोषणा OV7660_HSTART		0x17
#घोषणा OV7660_HSTOP		0x18
#घोषणा OV7660_VSTART		0x19
#घोषणा OV7660_VSTOP		0x1a
#घोषणा OV7660_PSHFT		0x1b
#घोषणा OV7660_MIDH		0x1c
#घोषणा OV7660_MIDL		0x1d
#घोषणा OV7660_MVFP		0x1e
#घोषणा OV7660_LAEC		0x1f
#घोषणा OV7660_BOS		0x20
#घोषणा OV7660_GBOS		0x21
#घोषणा OV7660_GROS		0x22
#घोषणा OV7660_ROS		0x23
#घोषणा OV7660_AEW		0x24
#घोषणा OV7660_AEB		0x25
#घोषणा OV7660_VPT		0x26
#घोषणा OV7660_BBIAS		0x27
#घोषणा OV7660_GbBIAS		0x28
#घोषणा OV7660_RSVD29		0x29
#घोषणा OV7660_RBIAS		0x2c
#घोषणा OV7660_HREF		0x32
#घोषणा OV7660_ADC		0x37
#घोषणा OV7660_OFON		0x39
#घोषणा OV7660_TSLB		0x3a
#घोषणा OV7660_COM12		0x3c
#घोषणा OV7660_COM13		0x3d
#घोषणा OV7660_LCC1		0x62
#घोषणा OV7660_LCC2		0x63
#घोषणा OV7660_LCC3		0x64
#घोषणा OV7660_LCC4		0x65
#घोषणा OV7660_LCC5		0x66
#घोषणा OV7660_HV		0x69
#घोषणा OV7660_RSVDA1		0xa1

#घोषणा OV7660_DEFAULT_GAIN		0x0e
#घोषणा OV7660_DEFAULT_RED_GAIN		0x80
#घोषणा OV7660_DEFAULT_BLUE_GAIN	0x80
#घोषणा OV7660_DEFAULT_SATURATION	0x00
#घोषणा OV7660_DEFAULT_EXPOSURE		0x20

/* Kernel module parameters */
बाह्य पूर्णांक क्रमce_sensor;
बाह्य bool dump_sensor;

पूर्णांक ov7660_probe(काष्ठा sd *sd);
पूर्णांक ov7660_init(काष्ठा sd *sd);
पूर्णांक ov7660_init(काष्ठा sd *sd);
पूर्णांक ov7660_init_controls(काष्ठा sd *sd);
पूर्णांक ov7660_start(काष्ठा sd *sd);
पूर्णांक ov7660_stop(काष्ठा sd *sd);
व्योम ov7660_disconnect(काष्ठा sd *sd);

अटल स्थिर काष्ठा m5602_sensor ov7660 = अणु
	.name = "ov7660",
	.i2c_slave_id = 0x42,
	.i2c_regW = 1,
	.probe = ov7660_probe,
	.init = ov7660_init,
	.init_controls = ov7660_init_controls,
	.start = ov7660_start,
	.stop = ov7660_stop,
	.disconnect = ov7660_disconnect,
पूर्ण;
#पूर्ण_अगर
