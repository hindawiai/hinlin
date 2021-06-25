<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Driver क्रम the mt9m111 sensor
 *
 * Copyright (C) 2008 Erik Andrथऊn
 * Copyright (C) 2007 Ilyes Gouta. Based on the m5603x Linux Driver Project.
 * Copyright (C) 2005 m5603x Linux Driver Project <m5602@x3ng.com.br>
 *
 * Portions of code to USB पूर्णांकerface and ALi driver software,
 * Copyright (c) 2006 Willem Duinker
 * v4l2 पूर्णांकerface modeled after the V4L2 driver
 * क्रम SN9C10x PC Camera Controllers
 *
 * Some defines taken from the mt9m111 sensor driver
 * Copyright (C) 2008, Robert Jarzmik <robert.jarzmik@मुक्त.fr>
 */

#अगर_अघोषित M5602_MT9M111_H_
#घोषणा M5602_MT9M111_H_

#समावेश "m5602_sensor.h"

/*****************************************************************************/

#घोषणा MT9M111_SC_CHIPVER			0x00
#घोषणा MT9M111_SC_ROWSTART			0x01
#घोषणा MT9M111_SC_COLSTART			0x02
#घोषणा MT9M111_SC_WINDOW_HEIGHT		0x03
#घोषणा MT9M111_SC_WINDOW_WIDTH			0x04
#घोषणा MT9M111_SC_HBLANK_CONTEXT_B		0x05
#घोषणा MT9M111_SC_VBLANK_CONTEXT_B		0x06
#घोषणा MT9M111_SC_HBLANK_CONTEXT_A		0x07
#घोषणा MT9M111_SC_VBLANK_CONTEXT_A		0x08
#घोषणा MT9M111_SC_SHUTTER_WIDTH		0x09
#घोषणा MT9M111_SC_ROW_SPEED			0x0a
#घोषणा MT9M111_SC_EXTRA_DELAY			0x0b
#घोषणा MT9M111_SC_SHUTTER_DELAY		0x0c
#घोषणा MT9M111_SC_RESET			0x0d
#घोषणा MT9M111_SC_R_MODE_CONTEXT_B		0x20
#घोषणा MT9M111_SC_R_MODE_CONTEXT_A		0x21
#घोषणा MT9M111_SC_FLASH_CONTROL		0x23
#घोषणा MT9M111_SC_GREEN_1_GAIN			0x2b
#घोषणा MT9M111_SC_BLUE_GAIN			0x2c
#घोषणा MT9M111_SC_RED_GAIN			0x2d
#घोषणा MT9M111_SC_GREEN_2_GAIN			0x2e
#घोषणा MT9M111_SC_GLOBAL_GAIN			0x2f

#घोषणा MT9M111_CONTEXT_CONTROL			0xc8
#घोषणा MT9M111_PAGE_MAP			0xf0
#घोषणा MT9M111_BYTEWISE_ADDRESS		0xf1

#घोषणा MT9M111_CP_OPERATING_MODE_CTL		0x06
#घोषणा MT9M111_CP_LUMA_OFFSET			0x34
#घोषणा MT9M111_CP_LUMA_CLIP			0x35
#घोषणा MT9M111_CP_OUTPUT_FORMAT_CTL2_CONTEXT_A 0x3a
#घोषणा MT9M111_CP_LENS_CORRECTION_1		0x3b
#घोषणा MT9M111_CP_DEFECT_CORR_CONTEXT_A	0x4c
#घोषणा MT9M111_CP_DEFECT_CORR_CONTEXT_B	0x4d
#घोषणा MT9M111_CP_OUTPUT_FORMAT_CTL2_CONTEXT_B 0x9b
#घोषणा MT9M111_CP_GLOBAL_CLK_CONTROL		0xb3

#घोषणा MT9M111_CC_AUTO_EXPOSURE_PARAMETER_18   0x65
#घोषणा MT9M111_CC_AWB_PARAMETER_7		0x28

#घोषणा MT9M111_SENSOR_CORE			0x00
#घोषणा MT9M111_COLORPIPE			0x01
#घोषणा MT9M111_CAMERA_CONTROL			0x02

#घोषणा MT9M111_RESET				(1 << 0)
#घोषणा MT9M111_RESTART				(1 << 1)
#घोषणा MT9M111_ANALOG_STANDBY			(1 << 2)
#घोषणा MT9M111_CHIP_ENABLE			(1 << 3)
#घोषणा MT9M111_CHIP_DISABLE			(0 << 3)
#घोषणा MT9M111_OUTPUT_DISABLE			(1 << 4)
#घोषणा MT9M111_SHOW_BAD_FRAMES			(1 << 0)
#घोषणा MT9M111_RESTART_BAD_FRAMES		(1 << 1)
#घोषणा MT9M111_SYNCHRONIZE_CHANGES		(1 << 7)

#घोषणा MT9M111_RMB_OVER_SIZED			(1 << 0)
#घोषणा MT9M111_RMB_MIRROR_ROWS			(1 << 0)
#घोषणा MT9M111_RMB_MIRROR_COLS			(1 << 1)
#घोषणा MT9M111_RMB_ROW_SKIP_2X			(1 << 2)
#घोषणा MT9M111_RMB_COLUMN_SKIP_2X		(1 << 3)
#घोषणा MT9M111_RMB_ROW_SKIP_4X			(1 << 4)
#घोषणा MT9M111_RMB_COLUMN_SKIP_4X		(1 << 5)

#घोषणा MT9M111_COLOR_MATRIX_BYPASS		(1 << 4)
#घोषणा MT9M111_SEL_CONTEXT_B			(1 << 3)

#घोषणा MT9M111_TRISTATE_PIN_IN_STANDBY		(1 << 1)
#घोषणा MT9M111_SOC_SOFT_STANDBY		(1 << 0)

#घोषणा MT9M111_2D_DEFECT_CORRECTION_ENABLE	(1 << 0)

#घोषणा INITIAL_MAX_GAIN			64
#घोषणा MT9M111_DEFAULT_GAIN			283
#घोषणा MT9M111_GREEN_GAIN_DEFAULT		0x20
#घोषणा MT9M111_BLUE_GAIN_DEFAULT		0x20
#घोषणा MT9M111_RED_GAIN_DEFAULT		0x20

/*****************************************************************************/

/* Kernel module parameters */
बाह्य पूर्णांक क्रमce_sensor;
बाह्य bool dump_sensor;

पूर्णांक mt9m111_probe(काष्ठा sd *sd);
पूर्णांक mt9m111_init(काष्ठा sd *sd);
पूर्णांक mt9m111_init_controls(काष्ठा sd *sd);
पूर्णांक mt9m111_start(काष्ठा sd *sd);
व्योम mt9m111_disconnect(काष्ठा sd *sd);

अटल स्थिर काष्ठा m5602_sensor mt9m111 = अणु
	.name = "MT9M111",

	.i2c_slave_id = 0xba,
	.i2c_regW = 2,

	.probe = mt9m111_probe,
	.init = mt9m111_init,
	.init_controls = mt9m111_init_controls,
	.disconnect = mt9m111_disconnect,
	.start = mt9m111_start,
पूर्ण;
#पूर्ण_अगर
