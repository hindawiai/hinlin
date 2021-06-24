<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Driver क्रम the s5k4aa sensor
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

#अगर_अघोषित M5602_S5K4AA_H_
#घोषणा M5602_S5K4AA_H_

#समावेश <linux/dmi.h>

#समावेश "m5602_sensor.h"

/*****************************************************************************/

#घोषणा S5K4AA_PAGE_MAP			0xec

#घोषणा S5K4AA_PAGE_MAP_0		0x00
#घोषणा S5K4AA_PAGE_MAP_1		0x01
#घोषणा S5K4AA_PAGE_MAP_2		0x02

/* Sensor रेजिस्टर definitions क्रम page 0x02 */
#घोषणा S5K4AA_READ_MODE		0x03
#घोषणा S5K4AA_ROWSTART_HI		0x04
#घोषणा S5K4AA_ROWSTART_LO		0x05
#घोषणा S5K4AA_COLSTART_HI		0x06
#घोषणा S5K4AA_COLSTART_LO		0x07
#घोषणा S5K4AA_WINDOW_HEIGHT_HI		0x08
#घोषणा S5K4AA_WINDOW_HEIGHT_LO		0x09
#घोषणा S5K4AA_WINDOW_WIDTH_HI		0x0a
#घोषणा S5K4AA_WINDOW_WIDTH_LO		0x0b
#घोषणा S5K4AA_GLOBAL_GAIN__		0x0f
/* sync lost, अगर too low, reduces frame rate अगर too high */
#घोषणा S5K4AA_H_BLANK_HI__		0x1d
#घोषणा S5K4AA_H_BLANK_LO__		0x1e
#घोषणा S5K4AA_EXPOSURE_HI		0x17
#घोषणा S5K4AA_EXPOSURE_LO		0x18
#घोषणा S5K4AA_BRIGHTNESS		0x1f /* (digital?) gain : 5 bits */
#घोषणा S5K4AA_GAIN			0x20 /* (analogue?) gain : 7 bits */
#घोषणा S5K4AA_NOISE_SUPP		0x37

#घोषणा S5K4AA_RM_ROW_SKIP_4X		0x08
#घोषणा S5K4AA_RM_ROW_SKIP_2X		0x04
#घोषणा S5K4AA_RM_COL_SKIP_4X		0x02
#घोषणा S5K4AA_RM_COL_SKIP_2X		0x01
#घोषणा S5K4AA_RM_H_FLIP		0x40
#घोषणा S5K4AA_RM_V_FLIP		0x80

#घोषणा S5K4AA_DEFAULT_GAIN		0x5f
#घोषणा S5K4AA_DEFAULT_BRIGHTNESS	0x10

/*****************************************************************************/

/* Kernel module parameters */
बाह्य पूर्णांक क्रमce_sensor;
बाह्य bool dump_sensor;

पूर्णांक s5k4aa_probe(काष्ठा sd *sd);
पूर्णांक s5k4aa_init(काष्ठा sd *sd);
पूर्णांक s5k4aa_init_controls(काष्ठा sd *sd);
पूर्णांक s5k4aa_start(काष्ठा sd *sd);
व्योम s5k4aa_disconnect(काष्ठा sd *sd);

अटल स्थिर काष्ठा m5602_sensor s5k4aa = अणु
	.name = "S5K4AA",
	.i2c_slave_id = 0x5a,
	.i2c_regW = 2,

	.probe = s5k4aa_probe,
	.init = s5k4aa_init,
	.init_controls = s5k4aa_init_controls,
	.start = s5k4aa_start,
	.disconnect = s5k4aa_disconnect,
पूर्ण;

#पूर्ण_अगर
