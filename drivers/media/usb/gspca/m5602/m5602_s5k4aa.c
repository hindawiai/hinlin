<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
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

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश "m5602_s5k4aa.h"

अटल स्थिर अचिन्हित अक्षर preinit_s5k4aa[][4] = अणु
	अणुBRIDGE, M5602_XB_MCU_CLK_DIV, 0x02, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_MCU_CLK_CTRL, 0xb0, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_SEN_CLK_DIV, 0x00, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_SEN_CLK_CTRL, 0xb0, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_ADC_CTRL, 0xc0, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_SENSOR_TYPE, 0x0d, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_SENSOR_CTRL, 0x00, 0x00पूर्ण,

	अणुBRIDGE, M5602_XB_GPIO_सूची, 0x1d, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_GPIO_DAT, 0x08, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_SEN_CLK_DIV, 0xb0, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_SEN_CLK_CTRL, 0x80, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_GPIO_EN_H, 0x3f, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_GPIO_सूची_H, 0x3f, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_GPIO_DAT_H, 0x00, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_GPIO_सूची, 0x1d, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_GPIO_DAT, 0x00, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_GPIO_EN_L, 0xff, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_GPIO_सूची_L, 0xff, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_GPIO_DAT_L, 0x00, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_SEN_CLK_DIV, 0x00, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_SEN_CLK_CTRL, 0xb0, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_ADC_CTRL, 0xc0, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_SENSOR_TYPE, 0x08, 0x00पूर्ण,

	अणुBRIDGE, M5602_XB_MCU_CLK_DIV, 0x02, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_MCU_CLK_CTRL, 0xb0, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_GPIO_सूची, 0x1d, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_GPIO_DAT, 0x14, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_SEN_CLK_DIV, 0x00, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_SEN_CLK_CTRL, 0xf0, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_GPIO_सूची, 0x1d, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_GPIO_DAT, 0x1c, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_GPIO_EN_H, 0x06, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_GPIO_सूची_H, 0x06, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_GPIO_DAT_H, 0x00, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_GPIO_EN_L, 0x00, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_I2C_CLK_DIV, 0x20, 0x00पूर्ण,

	अणुSENSOR, S5K4AA_PAGE_MAP, 0x00, 0x00पूर्ण
पूर्ण;

अटल स्थिर अचिन्हित अक्षर init_s5k4aa[][4] = अणु
	अणुBRIDGE, M5602_XB_MCU_CLK_DIV, 0x02, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_MCU_CLK_CTRL, 0xb0, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_SEN_CLK_DIV, 0x00, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_SEN_CLK_CTRL, 0xb0, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_ADC_CTRL, 0xc0, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_SENSOR_TYPE, 0x0d, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_SENSOR_CTRL, 0x00, 0x00पूर्ण,

	अणुBRIDGE, M5602_XB_GPIO_सूची, 0x1d, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_GPIO_DAT, 0x08, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_SEN_CLK_DIV, 0xb0, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_SEN_CLK_CTRL, 0x80, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_GPIO_EN_H, 0x3f, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_GPIO_सूची_H, 0x3f, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_GPIO_DAT_H, 0x00, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_GPIO_सूची, 0x1d, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_GPIO_DAT, 0x00, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_GPIO_EN_L, 0xff, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_GPIO_सूची_L, 0xff, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_GPIO_DAT_L, 0x00, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_SEN_CLK_DIV, 0x00, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_SEN_CLK_CTRL, 0xb0, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_ADC_CTRL, 0xc0, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_SENSOR_TYPE, 0x08, 0x00पूर्ण,

	अणुBRIDGE, M5602_XB_MCU_CLK_DIV, 0x02, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_MCU_CLK_CTRL, 0xb0, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_GPIO_सूची, 0x1d, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_GPIO_DAT, 0x14, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_SEN_CLK_DIV, 0x00, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_SEN_CLK_CTRL, 0xf0, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_GPIO_सूची, 0x1d, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_GPIO_DAT, 0x1c, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_GPIO_EN_H, 0x06, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_GPIO_सूची_H, 0x06, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_GPIO_DAT_H, 0x00, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_GPIO_EN_L, 0x00, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_I2C_CLK_DIV, 0x20, 0x00पूर्ण,

	अणुSENSOR, S5K4AA_PAGE_MAP, 0x07, 0x00पूर्ण,
	अणुSENSOR, 0x36, 0x01, 0x00पूर्ण,
	अणुSENSOR, S5K4AA_PAGE_MAP, 0x00, 0x00पूर्ण,
	अणुSENSOR, 0x7b, 0xff, 0x00पूर्ण,
	अणुSENSOR, S5K4AA_PAGE_MAP, 0x02, 0x00पूर्ण,
	अणुSENSOR, 0x0c, 0x05, 0x00पूर्ण,
	अणुSENSOR, 0x02, 0x0e, 0x00पूर्ण,
	अणुSENSOR, S5K4AA_READ_MODE, 0xa0, 0x00पूर्ण,
	अणुSENSOR, 0x37, 0x00, 0x00पूर्ण,
पूर्ण;

अटल स्थिर अचिन्हित अक्षर VGA_s5k4aa[][4] = अणु
	अणुBRIDGE, M5602_XB_SEN_CLK_DIV, 0x06, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_SEN_CLK_CTRL, 0xb0, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_ADC_CTRL, 0xc0, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_SENSOR_TYPE, 0x08, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_LINE_OF_FRAME_H, 0x81, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_PIX_OF_LINE_H, 0x82, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_SIG_INI, 0x01, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_VSYNC_PARA, 0x00, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_VSYNC_PARA, 0x00, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_VSYNC_PARA, 0x00, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_VSYNC_PARA, 0x00, 0x00पूर्ण,
	/* VSYNC_PARA, VSYNC_PARA : img height 480 = 0x01e0 */
	अणुBRIDGE, M5602_XB_VSYNC_PARA, 0x01, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_VSYNC_PARA, 0xe0, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_VSYNC_PARA, 0x00, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_VSYNC_PARA, 0x00, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_SIG_INI, 0x00, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_SIG_INI, 0x02, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_HSYNC_PARA, 0x00, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_HSYNC_PARA, 0x00, 0x00पूर्ण,
	/* HSYNC_PARA, HSYNC_PARA : img width 640 = 0x0280 */
	अणुBRIDGE, M5602_XB_HSYNC_PARA, 0x02, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_HSYNC_PARA, 0x80, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_SIG_INI, 0x00, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_SEN_CLK_DIV, 0x00, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_SEN_CLK_CTRL, 0xa0, 0x00पूर्ण, /* 48 MHz */

	अणुSENSOR, S5K4AA_PAGE_MAP, 0x02, 0x00पूर्ण,
	अणुSENSOR, S5K4AA_READ_MODE, S5K4AA_RM_H_FLIP | S5K4AA_RM_ROW_SKIP_2X
		| S5K4AA_RM_COL_SKIP_2X, 0x00पूर्ण,
	/* 0x37 : Fix image stability when light is too bright and improves
	 * image quality in 640x480, but worsens it in 1280x1024 */
	अणुSENSOR, 0x37, 0x01, 0x00पूर्ण,
	/* ROWSTART_HI, ROWSTART_LO : 10 + (1024-960)/2 = 42 = 0x002a */
	अणुSENSOR, S5K4AA_ROWSTART_HI, 0x00, 0x00पूर्ण,
	अणुSENSOR, S5K4AA_ROWSTART_LO, 0x29, 0x00पूर्ण,
	अणुSENSOR, S5K4AA_COLSTART_HI, 0x00, 0x00पूर्ण,
	अणुSENSOR, S5K4AA_COLSTART_LO, 0x0c, 0x00पूर्ण,
	/* winकरोw_height_hi, winकरोw_height_lo : 960 = 0x03c0 */
	अणुSENSOR, S5K4AA_WINDOW_HEIGHT_HI, 0x03, 0x00पूर्ण,
	अणुSENSOR, S5K4AA_WINDOW_HEIGHT_LO, 0xc0, 0x00पूर्ण,
	/* winकरोw_width_hi, winकरोw_width_lo : 1280 = 0x0500 */
	अणुSENSOR, S5K4AA_WINDOW_WIDTH_HI, 0x05, 0x00पूर्ण,
	अणुSENSOR, S5K4AA_WINDOW_WIDTH_LO, 0x00, 0x00पूर्ण,
	अणुSENSOR, S5K4AA_H_BLANK_HI__, 0x00, 0x00पूर्ण,
	अणुSENSOR, S5K4AA_H_BLANK_LO__, 0xa8, 0x00पूर्ण, /* helps to sync... */
	अणुSENSOR, S5K4AA_EXPOSURE_HI, 0x01, 0x00पूर्ण,
	अणुSENSOR, S5K4AA_EXPOSURE_LO, 0x00, 0x00पूर्ण,
	अणुSENSOR, 0x11, 0x04, 0x00पूर्ण,
	अणुSENSOR, 0x12, 0xc3, 0x00पूर्ण,
	अणुSENSOR, S5K4AA_PAGE_MAP, 0x02, 0x00पूर्ण,
	अणुSENSOR, 0x02, 0x0e, 0x00पूर्ण,
पूर्ण;

अटल स्थिर अचिन्हित अक्षर SXGA_s5k4aa[][4] = अणु
	अणुBRIDGE, M5602_XB_SEN_CLK_DIV, 0x06, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_SEN_CLK_CTRL, 0xb0, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_ADC_CTRL, 0xc0, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_SENSOR_TYPE, 0x08, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_LINE_OF_FRAME_H, 0x81, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_PIX_OF_LINE_H, 0x82, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_SIG_INI, 0x01, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_VSYNC_PARA, 0x00, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_VSYNC_PARA, 0x00, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_VSYNC_PARA, 0x00, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_VSYNC_PARA, 0x00, 0x00पूर्ण,
	/* VSYNC_PARA, VSYNC_PARA : img height 1024 = 0x0400 */
	अणुBRIDGE, M5602_XB_VSYNC_PARA, 0x04, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_VSYNC_PARA, 0x00, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_VSYNC_PARA, 0x00, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_VSYNC_PARA, 0x00, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_SIG_INI, 0x00, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_SIG_INI, 0x02, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_HSYNC_PARA, 0x00, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_HSYNC_PARA, 0x00, 0x00पूर्ण,
	/* HSYNC_PARA, HSYNC_PARA : img width 1280 = 0x0500 */
	अणुBRIDGE, M5602_XB_HSYNC_PARA, 0x05, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_HSYNC_PARA, 0x00, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_SIG_INI, 0x00, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_SEN_CLK_DIV, 0x00, 0x00पूर्ण,
	अणुBRIDGE, M5602_XB_SEN_CLK_CTRL, 0xa0, 0x00पूर्ण, /* 48 MHz */

	अणुSENSOR, S5K4AA_PAGE_MAP, 0x02, 0x00पूर्ण,
	अणुSENSOR, S5K4AA_READ_MODE, S5K4AA_RM_H_FLIP, 0x00पूर्ण,
	अणुSENSOR, 0x37, 0x01, 0x00पूर्ण,
	अणुSENSOR, S5K4AA_ROWSTART_HI, 0x00, 0x00पूर्ण,
	अणुSENSOR, S5K4AA_ROWSTART_LO, 0x09, 0x00पूर्ण,
	अणुSENSOR, S5K4AA_COLSTART_HI, 0x00, 0x00पूर्ण,
	अणुSENSOR, S5K4AA_COLSTART_LO, 0x0a, 0x00पूर्ण,
	अणुSENSOR, S5K4AA_WINDOW_HEIGHT_HI, 0x04, 0x00पूर्ण,
	अणुSENSOR, S5K4AA_WINDOW_HEIGHT_LO, 0x00, 0x00पूर्ण,
	अणुSENSOR, S5K4AA_WINDOW_WIDTH_HI, 0x05, 0x00पूर्ण,
	अणुSENSOR, S5K4AA_WINDOW_WIDTH_LO, 0x00, 0x00पूर्ण,
	अणुSENSOR, S5K4AA_H_BLANK_HI__, 0x01, 0x00पूर्ण,
	अणुSENSOR, S5K4AA_H_BLANK_LO__, 0xa8, 0x00पूर्ण,
	अणुSENSOR, S5K4AA_EXPOSURE_HI, 0x01, 0x00पूर्ण,
	अणुSENSOR, S5K4AA_EXPOSURE_LO, 0x00, 0x00पूर्ण,
	अणुSENSOR, 0x11, 0x04, 0x00पूर्ण,
	अणुSENSOR, 0x12, 0xc3, 0x00पूर्ण,
	अणुSENSOR, S5K4AA_PAGE_MAP, 0x02, 0x00पूर्ण,
	अणुSENSOR, 0x02, 0x0e, 0x00पूर्ण,
पूर्ण;


अटल पूर्णांक s5k4aa_s_ctrl(काष्ठा v4l2_ctrl *ctrl);
अटल व्योम s5k4aa_dump_रेजिस्टरs(काष्ठा sd *sd);

अटल स्थिर काष्ठा v4l2_ctrl_ops s5k4aa_ctrl_ops = अणु
	.s_ctrl = s5k4aa_s_ctrl,
पूर्ण;

अटल
    स्थिर
	काष्ठा dmi_प्रणाली_id s5k4aa_vflip_dmi_table[] = अणु
	अणु
		.ident = "BRUNEINIT",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "BRUNENIT"),
			DMI_MATCH(DMI_PRODUCT_NAME, "BRUNENIT"),
			DMI_MATCH(DMI_BOARD_VERSION, "00030D0000000001")
		पूर्ण
	पूर्ण, अणु
		.ident = "Fujitsu-Siemens Amilo Xa 2528",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "FUJITSU SIEMENS"),
			DMI_MATCH(DMI_PRODUCT_NAME, "AMILO Xa 2528")
		पूर्ण
	पूर्ण, अणु
		.ident = "Fujitsu-Siemens Amilo Xi 2428",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "FUJITSU SIEMENS"),
			DMI_MATCH(DMI_PRODUCT_NAME, "AMILO Xi 2428")
		पूर्ण
	पूर्ण, अणु
		.ident = "Fujitsu-Siemens Amilo Xi 2528",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "FUJITSU SIEMENS"),
			DMI_MATCH(DMI_PRODUCT_NAME, "AMILO Xi 2528")
		पूर्ण
	पूर्ण, अणु
		.ident = "Fujitsu-Siemens Amilo Xi 2550",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "FUJITSU SIEMENS"),
			DMI_MATCH(DMI_PRODUCT_NAME, "AMILO Xi 2550")
		पूर्ण
	पूर्ण, अणु
		.ident = "Fujitsu-Siemens Amilo Pa 2548",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "FUJITSU SIEMENS"),
			DMI_MATCH(DMI_PRODUCT_NAME, "AMILO Pa 2548")
		पूर्ण
	पूर्ण, अणु
		.ident = "Fujitsu-Siemens Amilo Pi 2530",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "FUJITSU SIEMENS"),
			DMI_MATCH(DMI_PRODUCT_NAME, "AMILO Pi 2530")
		पूर्ण
	पूर्ण, अणु
		.ident = "MSI GX700",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Micro-Star International"),
			DMI_MATCH(DMI_PRODUCT_NAME, "GX700"),
			DMI_MATCH(DMI_BIOS_DATE, "12/02/2008")
		पूर्ण
	पूर्ण, अणु
		.ident = "MSI GX700",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Micro-Star International"),
			DMI_MATCH(DMI_PRODUCT_NAME, "GX700"),
			DMI_MATCH(DMI_BIOS_DATE, "07/26/2007")
		पूर्ण
	पूर्ण, अणु
		.ident = "MSI GX700",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Micro-Star International"),
			DMI_MATCH(DMI_PRODUCT_NAME, "GX700"),
			DMI_MATCH(DMI_BIOS_DATE, "07/19/2007")
		पूर्ण
	पूर्ण, अणु
		.ident = "MSI GX700/GX705/EX700",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Micro-Star International"),
			DMI_MATCH(DMI_PRODUCT_NAME, "GX700/GX705/EX700")
		पूर्ण
	पूर्ण, अणु
		.ident = "MSI L735",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Micro-Star International"),
			DMI_MATCH(DMI_PRODUCT_NAME, "MS-1717X")
		पूर्ण
	पूर्ण, अणु
		.ident = "Lenovo Y300",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "L3000 Y300"),
			DMI_MATCH(DMI_PRODUCT_NAME, "Y300")
		पूर्ण
	पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल काष्ठा v4l2_pix_क्रमmat s5k4aa_modes[] = अणु
	अणु
		640,
		480,
		V4L2_PIX_FMT_SBGGR8,
		V4L2_FIELD_NONE,
		.sizeimage =
			640 * 480,
		.bytesperline = 640,
		.colorspace = V4L2_COLORSPACE_SRGB,
		.priv = 0
	पूर्ण,
	अणु
		1280,
		1024,
		V4L2_PIX_FMT_SBGGR8,
		V4L2_FIELD_NONE,
		.sizeimage =
			1280 * 1024,
		.bytesperline = 1280,
		.colorspace = V4L2_COLORSPACE_SRGB,
		.priv = 0
	पूर्ण
पूर्ण;

पूर्णांक s5k4aa_probe(काष्ठा sd *sd)
अणु
	u8 prod_id[6] = अणु0x00, 0x00, 0x00, 0x00, 0x00, 0x00पूर्ण;
	स्थिर u8 expected_prod_id[6] = अणु0x00, 0x10, 0x00, 0x4b, 0x33, 0x75पूर्ण;
	काष्ठा gspca_dev *gspca_dev = (काष्ठा gspca_dev *)sd;
	पूर्णांक i, err = 0;

	अगर (क्रमce_sensor) अणु
		अगर (क्रमce_sensor == S5K4AA_SENSOR) अणु
			pr_info("Forcing a %s sensor\n", s5k4aa.name);
			जाओ sensor_found;
		पूर्ण
		/* If we want to क्रमce another sensor, करोn't try to probe this
		 * one */
		वापस -ENODEV;
	पूर्ण

	gspca_dbg(gspca_dev, D_PROBE, "Probing for a s5k4aa sensor\n");

	/* Preinit the sensor */
	क्रम (i = 0; i < ARRAY_SIZE(preinit_s5k4aa) && !err; i++) अणु
		u8 data[2] = अणु0x00, 0x00पूर्ण;

		चयन (preinit_s5k4aa[i][0]) अणु
		हाल BRIDGE:
			err = m5602_ग_लिखो_bridge(sd,
						 preinit_s5k4aa[i][1],
						 preinit_s5k4aa[i][2]);
			अवरोध;

		हाल SENSOR:
			data[0] = preinit_s5k4aa[i][2];
			err = m5602_ग_लिखो_sensor(sd,
						  preinit_s5k4aa[i][1],
						  data, 1);
			अवरोध;

		हाल SENSOR_LONG:
			data[0] = preinit_s5k4aa[i][2];
			data[1] = preinit_s5k4aa[i][3];
			err = m5602_ग_लिखो_sensor(sd,
						  preinit_s5k4aa[i][1],
						  data, 2);
			अवरोध;
		शेष:
			pr_info("Invalid stream command, exiting init\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	/* Test some रेजिस्टरs, but we करोn't know their exact meaning yet */
	अगर (m5602_पढ़ो_sensor(sd, 0x00, prod_id, 2))
		वापस -ENODEV;
	अगर (m5602_पढ़ो_sensor(sd, 0x02, prod_id+2, 2))
		वापस -ENODEV;
	अगर (m5602_पढ़ो_sensor(sd, 0x04, prod_id+4, 2))
		वापस -ENODEV;

	अगर (स_भेद(prod_id, expected_prod_id, माप(prod_id)))
		वापस -ENODEV;
	अन्यथा
		pr_info("Detected a s5k4aa sensor\n");

sensor_found:
	sd->gspca_dev.cam.cam_mode = s5k4aa_modes;
	sd->gspca_dev.cam.nmodes = ARRAY_SIZE(s5k4aa_modes);

	वापस 0;
पूर्ण

पूर्णांक s5k4aa_start(काष्ठा sd *sd)
अणु
	पूर्णांक i, err = 0;
	u8 data[2];
	काष्ठा cam *cam = &sd->gspca_dev.cam;
	काष्ठा gspca_dev *gspca_dev = (काष्ठा gspca_dev *)sd;

	चयन (cam->cam_mode[sd->gspca_dev.curr_mode].width) अणु
	हाल 1280:
		gspca_dbg(gspca_dev, D_CONF, "Configuring camera for SXGA mode\n");

		क्रम (i = 0; i < ARRAY_SIZE(SXGA_s5k4aa); i++) अणु
			चयन (SXGA_s5k4aa[i][0]) अणु
			हाल BRIDGE:
				err = m5602_ग_लिखो_bridge(sd,
						 SXGA_s5k4aa[i][1],
						 SXGA_s5k4aa[i][2]);
			अवरोध;

			हाल SENSOR:
				data[0] = SXGA_s5k4aa[i][2];
				err = m5602_ग_लिखो_sensor(sd,
						 SXGA_s5k4aa[i][1],
						 data, 1);
			अवरोध;

			हाल SENSOR_LONG:
				data[0] = SXGA_s5k4aa[i][2];
				data[1] = SXGA_s5k4aa[i][3];
				err = m5602_ग_लिखो_sensor(sd,
						  SXGA_s5k4aa[i][1],
						  data, 2);
			अवरोध;

			शेष:
				pr_err("Invalid stream command, exiting init\n");
				वापस -EINVAL;
			पूर्ण
		पूर्ण
		अवरोध;

	हाल 640:
		gspca_dbg(gspca_dev, D_CONF, "Configuring camera for VGA mode\n");

		क्रम (i = 0; i < ARRAY_SIZE(VGA_s5k4aa); i++) अणु
			चयन (VGA_s5k4aa[i][0]) अणु
			हाल BRIDGE:
				err = m5602_ग_लिखो_bridge(sd,
						 VGA_s5k4aa[i][1],
						 VGA_s5k4aa[i][2]);
			अवरोध;

			हाल SENSOR:
				data[0] = VGA_s5k4aa[i][2];
				err = m5602_ग_लिखो_sensor(sd,
						 VGA_s5k4aa[i][1],
						 data, 1);
			अवरोध;

			हाल SENSOR_LONG:
				data[0] = VGA_s5k4aa[i][2];
				data[1] = VGA_s5k4aa[i][3];
				err = m5602_ग_लिखो_sensor(sd,
						  VGA_s5k4aa[i][1],
						  data, 2);
			अवरोध;

			शेष:
				pr_err("Invalid stream command, exiting init\n");
				वापस -EINVAL;
			पूर्ण
		पूर्ण
		अवरोध;
	पूर्ण
	अगर (err < 0)
		वापस err;

	वापस 0;
पूर्ण

पूर्णांक s5k4aa_init(काष्ठा sd *sd)
अणु
	पूर्णांक i, err = 0;

	क्रम (i = 0; i < ARRAY_SIZE(init_s5k4aa) && !err; i++) अणु
		u8 data[2] = अणु0x00, 0x00पूर्ण;

		चयन (init_s5k4aa[i][0]) अणु
		हाल BRIDGE:
			err = m5602_ग_लिखो_bridge(sd,
				init_s5k4aa[i][1],
				init_s5k4aa[i][2]);
			अवरोध;

		हाल SENSOR:
			data[0] = init_s5k4aa[i][2];
			err = m5602_ग_लिखो_sensor(sd,
				init_s5k4aa[i][1], data, 1);
			अवरोध;

		हाल SENSOR_LONG:
			data[0] = init_s5k4aa[i][2];
			data[1] = init_s5k4aa[i][3];
			err = m5602_ग_लिखो_sensor(sd,
				init_s5k4aa[i][1], data, 2);
			अवरोध;
		शेष:
			pr_info("Invalid stream command, exiting init\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	अगर (dump_sensor)
		s5k4aa_dump_रेजिस्टरs(sd);

	वापस err;
पूर्ण

पूर्णांक s5k4aa_init_controls(काष्ठा sd *sd)
अणु
	काष्ठा v4l2_ctrl_handler *hdl = &sd->gspca_dev.ctrl_handler;

	sd->gspca_dev.vdev.ctrl_handler = hdl;
	v4l2_ctrl_handler_init(hdl, 6);

	v4l2_ctrl_new_std(hdl, &s5k4aa_ctrl_ops, V4L2_CID_BRIGHTNESS,
			  0, 0x1f, 1, S5K4AA_DEFAULT_BRIGHTNESS);

	v4l2_ctrl_new_std(hdl, &s5k4aa_ctrl_ops, V4L2_CID_EXPOSURE,
			  13, 0xfff, 1, 0x100);

	v4l2_ctrl_new_std(hdl, &s5k4aa_ctrl_ops, V4L2_CID_GAIN,
			  0, 127, 1, S5K4AA_DEFAULT_GAIN);

	v4l2_ctrl_new_std(hdl, &s5k4aa_ctrl_ops, V4L2_CID_SHARPNESS,
			  0, 1, 1, 1);

	sd->hflip = v4l2_ctrl_new_std(hdl, &s5k4aa_ctrl_ops, V4L2_CID_HFLIP,
				      0, 1, 1, 0);
	sd->vflip = v4l2_ctrl_new_std(hdl, &s5k4aa_ctrl_ops, V4L2_CID_VFLIP,
				      0, 1, 1, 0);

	अगर (hdl->error) अणु
		pr_err("Could not initialize controls\n");
		वापस hdl->error;
	पूर्ण

	v4l2_ctrl_cluster(2, &sd->hflip);

	वापस 0;
पूर्ण

अटल पूर्णांक s5k4aa_set_exposure(काष्ठा gspca_dev *gspca_dev, __s32 val)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;
	u8 data = S5K4AA_PAGE_MAP_2;
	पूर्णांक err;

	gspca_dbg(gspca_dev, D_CONF, "Set exposure to %d\n", val);
	err = m5602_ग_लिखो_sensor(sd, S5K4AA_PAGE_MAP, &data, 1);
	अगर (err < 0)
		वापस err;
	data = (val >> 8) & 0xff;
	err = m5602_ग_लिखो_sensor(sd, S5K4AA_EXPOSURE_HI, &data, 1);
	अगर (err < 0)
		वापस err;
	data = val & 0xff;
	err = m5602_ग_लिखो_sensor(sd, S5K4AA_EXPOSURE_LO, &data, 1);

	वापस err;
पूर्ण

अटल पूर्णांक s5k4aa_set_hvflip(काष्ठा gspca_dev *gspca_dev)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;
	u8 data = S5K4AA_PAGE_MAP_2;
	पूर्णांक err;
	पूर्णांक hflip = sd->hflip->val;
	पूर्णांक vflip = sd->vflip->val;

	gspca_dbg(gspca_dev, D_CONF, "Set hvflip %d %d\n", hflip, vflip);
	err = m5602_ग_लिखो_sensor(sd, S5K4AA_PAGE_MAP, &data, 1);
	अगर (err < 0)
		वापस err;

	err = m5602_पढ़ो_sensor(sd, S5K4AA_READ_MODE, &data, 1);
	अगर (err < 0)
		वापस err;

	अगर (dmi_check_प्रणाली(s5k4aa_vflip_dmi_table)) अणु
		hflip = !hflip;
		vflip = !vflip;
	पूर्ण

	data = (data & 0x7f) | (vflip << 7) | (hflip << 6);
	err = m5602_ग_लिखो_sensor(sd, S5K4AA_READ_MODE, &data, 1);
	अगर (err < 0)
		वापस err;

	err = m5602_पढ़ो_sensor(sd, S5K4AA_COLSTART_LO, &data, 1);
	अगर (err < 0)
		वापस err;
	अगर (hflip)
		data &= 0xfe;
	अन्यथा
		data |= 0x01;
	err = m5602_ग_लिखो_sensor(sd, S5K4AA_COLSTART_LO, &data, 1);
	अगर (err < 0)
		वापस err;

	err = m5602_पढ़ो_sensor(sd, S5K4AA_ROWSTART_LO, &data, 1);
	अगर (err < 0)
		वापस err;
	अगर (vflip)
		data &= 0xfe;
	अन्यथा
		data |= 0x01;
	err = m5602_ग_लिखो_sensor(sd, S5K4AA_ROWSTART_LO, &data, 1);
	अगर (err < 0)
		वापस err;

	वापस 0;
पूर्ण

अटल पूर्णांक s5k4aa_set_gain(काष्ठा gspca_dev *gspca_dev, __s32 val)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;
	u8 data = S5K4AA_PAGE_MAP_2;
	पूर्णांक err;

	gspca_dbg(gspca_dev, D_CONF, "Set gain to %d\n", val);
	err = m5602_ग_लिखो_sensor(sd, S5K4AA_PAGE_MAP, &data, 1);
	अगर (err < 0)
		वापस err;

	data = val & 0xff;
	err = m5602_ग_लिखो_sensor(sd, S5K4AA_GAIN, &data, 1);

	वापस err;
पूर्ण

अटल पूर्णांक s5k4aa_set_brightness(काष्ठा gspca_dev *gspca_dev, __s32 val)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;
	u8 data = S5K4AA_PAGE_MAP_2;
	पूर्णांक err;

	gspca_dbg(gspca_dev, D_CONF, "Set brightness to %d\n", val);
	err = m5602_ग_लिखो_sensor(sd, S5K4AA_PAGE_MAP, &data, 1);
	अगर (err < 0)
		वापस err;

	data = val & 0xff;
	वापस m5602_ग_लिखो_sensor(sd, S5K4AA_BRIGHTNESS, &data, 1);
पूर्ण

अटल पूर्णांक s5k4aa_set_noise(काष्ठा gspca_dev *gspca_dev, __s32 val)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;
	u8 data = S5K4AA_PAGE_MAP_2;
	पूर्णांक err;

	gspca_dbg(gspca_dev, D_CONF, "Set noise to %d\n", val);
	err = m5602_ग_लिखो_sensor(sd, S5K4AA_PAGE_MAP, &data, 1);
	अगर (err < 0)
		वापस err;

	data = val & 0x01;
	वापस m5602_ग_लिखो_sensor(sd, S5K4AA_NOISE_SUPP, &data, 1);
पूर्ण

अटल पूर्णांक s5k4aa_s_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा gspca_dev *gspca_dev =
		container_of(ctrl->handler, काष्ठा gspca_dev, ctrl_handler);
	पूर्णांक err;

	अगर (!gspca_dev->streaming)
		वापस 0;

	चयन (ctrl->id) अणु
	हाल V4L2_CID_BRIGHTNESS:
		err = s5k4aa_set_brightness(gspca_dev, ctrl->val);
		अवरोध;
	हाल V4L2_CID_EXPOSURE:
		err = s5k4aa_set_exposure(gspca_dev, ctrl->val);
		अवरोध;
	हाल V4L2_CID_GAIN:
		err = s5k4aa_set_gain(gspca_dev, ctrl->val);
		अवरोध;
	हाल V4L2_CID_SHARPNESS:
		err = s5k4aa_set_noise(gspca_dev, ctrl->val);
		अवरोध;
	हाल V4L2_CID_HFLIP:
		err = s5k4aa_set_hvflip(gspca_dev);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस err;
पूर्ण

व्योम s5k4aa_disconnect(काष्ठा sd *sd)
अणु
	sd->sensor = शून्य;
पूर्ण

अटल व्योम s5k4aa_dump_रेजिस्टरs(काष्ठा sd *sd)
अणु
	पूर्णांक address;
	u8 page, old_page;
	m5602_पढ़ो_sensor(sd, S5K4AA_PAGE_MAP, &old_page, 1);
	क्रम (page = 0; page < 16; page++) अणु
		m5602_ग_लिखो_sensor(sd, S5K4AA_PAGE_MAP, &page, 1);
		pr_info("Dumping the s5k4aa register state for page 0x%x\n",
			page);
		क्रम (address = 0; address <= 0xff; address++) अणु
			u8 value = 0;
			m5602_पढ़ो_sensor(sd, address, &value, 1);
			pr_info("register 0x%x contains 0x%x\n",
				address, value);
		पूर्ण
	पूर्ण
	pr_info("s5k4aa register state dump complete\n");

	क्रम (page = 0; page < 16; page++) अणु
		m5602_ग_लिखो_sensor(sd, S5K4AA_PAGE_MAP, &page, 1);
		pr_info("Probing for which registers that are read/write for page 0x%x\n",
			page);
		क्रम (address = 0; address <= 0xff; address++) अणु
			u8 old_value, ctrl_value, test_value = 0xff;

			m5602_पढ़ो_sensor(sd, address, &old_value, 1);
			m5602_ग_लिखो_sensor(sd, address, &test_value, 1);
			m5602_पढ़ो_sensor(sd, address, &ctrl_value, 1);

			अगर (ctrl_value == test_value)
				pr_info("register 0x%x is writeable\n",
					address);
			अन्यथा
				pr_info("register 0x%x is read only\n",
					address);

			/* Restore original value */
			m5602_ग_लिखो_sensor(sd, address, &old_value, 1);
		पूर्ण
	पूर्ण
	pr_info("Read/write register probing complete\n");
	m5602_ग_लिखो_sensor(sd, S5K4AA_PAGE_MAP, &old_page, 1);
पूर्ण
