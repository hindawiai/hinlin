<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Driver क्रम the s5k83a sensor
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

#अगर_अघोषित M5602_S5K83A_H_
#घोषणा M5602_S5K83A_H_

#समावेश "m5602_sensor.h"

#घोषणा S5K83A_FLIP			0x01
#घोषणा S5K83A_HFLIP_TUNE		0x03
#घोषणा S5K83A_VFLIP_TUNE		0x05
#घोषणा S5K83A_BRIGHTNESS		0x0a
#घोषणा S5K83A_EXPOSURE			0x18
#घोषणा S5K83A_GAIN			0x1b
#घोषणा S5K83A_PAGE_MAP			0xec

#घोषणा S5K83A_DEFAULT_GAIN		0x71
#घोषणा S5K83A_DEFAULT_BRIGHTNESS	0x7e
#घोषणा S5K83A_DEFAULT_EXPOSURE		0x00
#घोषणा S5K83A_MAXIMUM_EXPOSURE		0x3c
#घोषणा S5K83A_FLIP_MASK		0x10
#घोषणा S5K83A_GPIO_LED_MASK		0x10
#घोषणा S5K83A_GPIO_ROTATION_MASK	0x40

/*****************************************************************************/

/* Kernel module parameters */
बाह्य पूर्णांक क्रमce_sensor;
बाह्य bool dump_sensor;

पूर्णांक s5k83a_probe(काष्ठा sd *sd);
पूर्णांक s5k83a_init(काष्ठा sd *sd);
पूर्णांक s5k83a_init_controls(काष्ठा sd *sd);
पूर्णांक s5k83a_start(काष्ठा sd *sd);
पूर्णांक s5k83a_stop(काष्ठा sd *sd);
व्योम s5k83a_disconnect(काष्ठा sd *sd);

अटल स्थिर काष्ठा m5602_sensor s5k83a = अणु
	.name = "S5K83A",
	.probe = s5k83a_probe,
	.init = s5k83a_init,
	.init_controls = s5k83a_init_controls,
	.start = s5k83a_start,
	.stop = s5k83a_stop,
	.disconnect = s5k83a_disconnect,
	.i2c_slave_id = 0x5a,
	.i2c_regW = 2,
पूर्ण;
#पूर्ण_अगर
