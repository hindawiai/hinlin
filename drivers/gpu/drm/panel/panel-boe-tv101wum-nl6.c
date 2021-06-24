<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2018 MediaTek Inc.
 * Author: Jitao Shi <jitao.shi@mediatek.com>
 */

#समावेश <linux/delay.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/regulator/consumer.h>

#समावेश <drm/drm_connector.h>
#समावेश <drm/drm_crtc.h>
#समावेश <drm/drm_mipi_dsi.h>
#समावेश <drm/drm_panel.h>

#समावेश <video/mipi_display.h>

काष्ठा panel_desc अणु
	स्थिर काष्ठा drm_display_mode *modes;
	अचिन्हित पूर्णांक bpc;

	/**
	 * @width_mm: width of the panel's active display area
	 * @height_mm: height of the panel's active display area
	 */
	काष्ठा अणु
		अचिन्हित पूर्णांक width_mm;
		अचिन्हित पूर्णांक height_mm;
	पूर्ण size;

	अचिन्हित दीर्घ mode_flags;
	क्रमागत mipi_dsi_pixel_क्रमmat क्रमmat;
	स्थिर काष्ठा panel_init_cmd *init_cmds;
	अचिन्हित पूर्णांक lanes;
	bool disअक्षरge_on_disable;
पूर्ण;

काष्ठा boe_panel अणु
	काष्ठा drm_panel base;
	काष्ठा mipi_dsi_device *dsi;

	स्थिर काष्ठा panel_desc *desc;

	क्रमागत drm_panel_orientation orientation;
	काष्ठा regulator *pp1800;
	काष्ठा regulator *avee;
	काष्ठा regulator *avdd;
	काष्ठा gpio_desc *enable_gpio;

	bool prepared;
पूर्ण;

क्रमागत dsi_cmd_type अणु
	INIT_DCS_CMD,
	DELAY_CMD,
पूर्ण;

काष्ठा panel_init_cmd अणु
	क्रमागत dsi_cmd_type type;
	माप_प्रकार len;
	स्थिर अक्षर *data;
पूर्ण;

#घोषणा _INIT_DCS_CMD(...) अणु \
	.type = INIT_DCS_CMD, \
	.len = माप((अक्षर[])अणु__VA_ARGS__पूर्ण), \
	.data = (अक्षर[])अणु__VA_ARGS__पूर्ण पूर्ण

#घोषणा _INIT_DELAY_CMD(...) अणु \
	.type = DELAY_CMD,\
	.len = माप((अक्षर[])अणु__VA_ARGS__पूर्ण), \
	.data = (अक्षर[])अणु__VA_ARGS__पूर्ण पूर्ण

अटल स्थिर काष्ठा panel_init_cmd boe_init_cmd[] = अणु
	_INIT_DELAY_CMD(24),
	_INIT_DCS_CMD(0xB0, 0x05),
	_INIT_DCS_CMD(0xB1, 0xE5),
	_INIT_DCS_CMD(0xB3, 0x52),
	_INIT_DCS_CMD(0xB0, 0x00),
	_INIT_DCS_CMD(0xB3, 0x88),
	_INIT_DCS_CMD(0xB0, 0x04),
	_INIT_DCS_CMD(0xB8, 0x00),
	_INIT_DCS_CMD(0xB0, 0x00),
	_INIT_DCS_CMD(0xB6, 0x03),
	_INIT_DCS_CMD(0xBA, 0x8B),
	_INIT_DCS_CMD(0xBF, 0x1A),
	_INIT_DCS_CMD(0xC0, 0x0F),
	_INIT_DCS_CMD(0xC2, 0x0C),
	_INIT_DCS_CMD(0xC3, 0x02),
	_INIT_DCS_CMD(0xC4, 0x0C),
	_INIT_DCS_CMD(0xC5, 0x02),
	_INIT_DCS_CMD(0xB0, 0x01),
	_INIT_DCS_CMD(0xE0, 0x26),
	_INIT_DCS_CMD(0xE1, 0x26),
	_INIT_DCS_CMD(0xDC, 0x00),
	_INIT_DCS_CMD(0xDD, 0x00),
	_INIT_DCS_CMD(0xCC, 0x26),
	_INIT_DCS_CMD(0xCD, 0x26),
	_INIT_DCS_CMD(0xC8, 0x00),
	_INIT_DCS_CMD(0xC9, 0x00),
	_INIT_DCS_CMD(0xD2, 0x03),
	_INIT_DCS_CMD(0xD3, 0x03),
	_INIT_DCS_CMD(0xE6, 0x04),
	_INIT_DCS_CMD(0xE7, 0x04),
	_INIT_DCS_CMD(0xC4, 0x09),
	_INIT_DCS_CMD(0xC5, 0x09),
	_INIT_DCS_CMD(0xD8, 0x0A),
	_INIT_DCS_CMD(0xD9, 0x0A),
	_INIT_DCS_CMD(0xC2, 0x0B),
	_INIT_DCS_CMD(0xC3, 0x0B),
	_INIT_DCS_CMD(0xD6, 0x0C),
	_INIT_DCS_CMD(0xD7, 0x0C),
	_INIT_DCS_CMD(0xC0, 0x05),
	_INIT_DCS_CMD(0xC1, 0x05),
	_INIT_DCS_CMD(0xD4, 0x06),
	_INIT_DCS_CMD(0xD5, 0x06),
	_INIT_DCS_CMD(0xCA, 0x07),
	_INIT_DCS_CMD(0xCB, 0x07),
	_INIT_DCS_CMD(0xDE, 0x08),
	_INIT_DCS_CMD(0xDF, 0x08),
	_INIT_DCS_CMD(0xB0, 0x02),
	_INIT_DCS_CMD(0xC0, 0x00),
	_INIT_DCS_CMD(0xC1, 0x0D),
	_INIT_DCS_CMD(0xC2, 0x17),
	_INIT_DCS_CMD(0xC3, 0x26),
	_INIT_DCS_CMD(0xC4, 0x31),
	_INIT_DCS_CMD(0xC5, 0x1C),
	_INIT_DCS_CMD(0xC6, 0x2C),
	_INIT_DCS_CMD(0xC7, 0x33),
	_INIT_DCS_CMD(0xC8, 0x31),
	_INIT_DCS_CMD(0xC9, 0x37),
	_INIT_DCS_CMD(0xCA, 0x37),
	_INIT_DCS_CMD(0xCB, 0x37),
	_INIT_DCS_CMD(0xCC, 0x39),
	_INIT_DCS_CMD(0xCD, 0x2E),
	_INIT_DCS_CMD(0xCE, 0x2F),
	_INIT_DCS_CMD(0xCF, 0x2F),
	_INIT_DCS_CMD(0xD0, 0x07),
	_INIT_DCS_CMD(0xD2, 0x00),
	_INIT_DCS_CMD(0xD3, 0x0D),
	_INIT_DCS_CMD(0xD4, 0x17),
	_INIT_DCS_CMD(0xD5, 0x26),
	_INIT_DCS_CMD(0xD6, 0x31),
	_INIT_DCS_CMD(0xD7, 0x3F),
	_INIT_DCS_CMD(0xD8, 0x3F),
	_INIT_DCS_CMD(0xD9, 0x3F),
	_INIT_DCS_CMD(0xDA, 0x3F),
	_INIT_DCS_CMD(0xDB, 0x37),
	_INIT_DCS_CMD(0xDC, 0x37),
	_INIT_DCS_CMD(0xDD, 0x37),
	_INIT_DCS_CMD(0xDE, 0x39),
	_INIT_DCS_CMD(0xDF, 0x2E),
	_INIT_DCS_CMD(0xE0, 0x2F),
	_INIT_DCS_CMD(0xE1, 0x2F),
	_INIT_DCS_CMD(0xE2, 0x07),
	_INIT_DCS_CMD(0xB0, 0x03),
	_INIT_DCS_CMD(0xC8, 0x0B),
	_INIT_DCS_CMD(0xC9, 0x07),
	_INIT_DCS_CMD(0xC3, 0x00),
	_INIT_DCS_CMD(0xE7, 0x00),
	_INIT_DCS_CMD(0xC5, 0x2A),
	_INIT_DCS_CMD(0xDE, 0x2A),
	_INIT_DCS_CMD(0xCA, 0x43),
	_INIT_DCS_CMD(0xC9, 0x07),
	_INIT_DCS_CMD(0xE4, 0xC0),
	_INIT_DCS_CMD(0xE5, 0x0D),
	_INIT_DCS_CMD(0xCB, 0x00),
	_INIT_DCS_CMD(0xB0, 0x06),
	_INIT_DCS_CMD(0xB8, 0xA5),
	_INIT_DCS_CMD(0xC0, 0xA5),
	_INIT_DCS_CMD(0xC7, 0x0F),
	_INIT_DCS_CMD(0xD5, 0x32),
	_INIT_DCS_CMD(0xB8, 0x00),
	_INIT_DCS_CMD(0xC0, 0x00),
	_INIT_DCS_CMD(0xBC, 0x00),
	_INIT_DCS_CMD(0xB0, 0x07),
	_INIT_DCS_CMD(0xB1, 0x00),
	_INIT_DCS_CMD(0xB2, 0x02),
	_INIT_DCS_CMD(0xB3, 0x0F),
	_INIT_DCS_CMD(0xB4, 0x25),
	_INIT_DCS_CMD(0xB5, 0x39),
	_INIT_DCS_CMD(0xB6, 0x4E),
	_INIT_DCS_CMD(0xB7, 0x72),
	_INIT_DCS_CMD(0xB8, 0x97),
	_INIT_DCS_CMD(0xB9, 0xDC),
	_INIT_DCS_CMD(0xBA, 0x22),
	_INIT_DCS_CMD(0xBB, 0xA4),
	_INIT_DCS_CMD(0xBC, 0x2B),
	_INIT_DCS_CMD(0xBD, 0x2F),
	_INIT_DCS_CMD(0xBE, 0xA9),
	_INIT_DCS_CMD(0xBF, 0x25),
	_INIT_DCS_CMD(0xC0, 0x61),
	_INIT_DCS_CMD(0xC1, 0x97),
	_INIT_DCS_CMD(0xC2, 0xB2),
	_INIT_DCS_CMD(0xC3, 0xCD),
	_INIT_DCS_CMD(0xC4, 0xD9),
	_INIT_DCS_CMD(0xC5, 0xE7),
	_INIT_DCS_CMD(0xC6, 0xF4),
	_INIT_DCS_CMD(0xC7, 0xFA),
	_INIT_DCS_CMD(0xC8, 0xFC),
	_INIT_DCS_CMD(0xC9, 0x00),
	_INIT_DCS_CMD(0xCA, 0x00),
	_INIT_DCS_CMD(0xCB, 0x16),
	_INIT_DCS_CMD(0xCC, 0xAF),
	_INIT_DCS_CMD(0xCD, 0xFF),
	_INIT_DCS_CMD(0xCE, 0xFF),
	_INIT_DCS_CMD(0xB0, 0x08),
	_INIT_DCS_CMD(0xB1, 0x04),
	_INIT_DCS_CMD(0xB2, 0x05),
	_INIT_DCS_CMD(0xB3, 0x11),
	_INIT_DCS_CMD(0xB4, 0x24),
	_INIT_DCS_CMD(0xB5, 0x39),
	_INIT_DCS_CMD(0xB6, 0x4F),
	_INIT_DCS_CMD(0xB7, 0x72),
	_INIT_DCS_CMD(0xB8, 0x98),
	_INIT_DCS_CMD(0xB9, 0xDC),
	_INIT_DCS_CMD(0xBA, 0x23),
	_INIT_DCS_CMD(0xBB, 0xA6),
	_INIT_DCS_CMD(0xBC, 0x2C),
	_INIT_DCS_CMD(0xBD, 0x30),
	_INIT_DCS_CMD(0xBE, 0xAA),
	_INIT_DCS_CMD(0xBF, 0x26),
	_INIT_DCS_CMD(0xC0, 0x62),
	_INIT_DCS_CMD(0xC1, 0x9B),
	_INIT_DCS_CMD(0xC2, 0xB5),
	_INIT_DCS_CMD(0xC3, 0xCF),
	_INIT_DCS_CMD(0xC4, 0xDB),
	_INIT_DCS_CMD(0xC5, 0xE8),
	_INIT_DCS_CMD(0xC6, 0xF5),
	_INIT_DCS_CMD(0xC7, 0xFA),
	_INIT_DCS_CMD(0xC8, 0xFC),
	_INIT_DCS_CMD(0xC9, 0x00),
	_INIT_DCS_CMD(0xCA, 0x00),
	_INIT_DCS_CMD(0xCB, 0x16),
	_INIT_DCS_CMD(0xCC, 0xAF),
	_INIT_DCS_CMD(0xCD, 0xFF),
	_INIT_DCS_CMD(0xCE, 0xFF),
	_INIT_DCS_CMD(0xB0, 0x09),
	_INIT_DCS_CMD(0xB1, 0x04),
	_INIT_DCS_CMD(0xB2, 0x02),
	_INIT_DCS_CMD(0xB3, 0x16),
	_INIT_DCS_CMD(0xB4, 0x24),
	_INIT_DCS_CMD(0xB5, 0x3B),
	_INIT_DCS_CMD(0xB6, 0x4F),
	_INIT_DCS_CMD(0xB7, 0x73),
	_INIT_DCS_CMD(0xB8, 0x99),
	_INIT_DCS_CMD(0xB9, 0xE0),
	_INIT_DCS_CMD(0xBA, 0x26),
	_INIT_DCS_CMD(0xBB, 0xAD),
	_INIT_DCS_CMD(0xBC, 0x36),
	_INIT_DCS_CMD(0xBD, 0x3A),
	_INIT_DCS_CMD(0xBE, 0xAE),
	_INIT_DCS_CMD(0xBF, 0x2A),
	_INIT_DCS_CMD(0xC0, 0x66),
	_INIT_DCS_CMD(0xC1, 0x9E),
	_INIT_DCS_CMD(0xC2, 0xB8),
	_INIT_DCS_CMD(0xC3, 0xD1),
	_INIT_DCS_CMD(0xC4, 0xDD),
	_INIT_DCS_CMD(0xC5, 0xE9),
	_INIT_DCS_CMD(0xC6, 0xF6),
	_INIT_DCS_CMD(0xC7, 0xFA),
	_INIT_DCS_CMD(0xC8, 0xFC),
	_INIT_DCS_CMD(0xC9, 0x00),
	_INIT_DCS_CMD(0xCA, 0x00),
	_INIT_DCS_CMD(0xCB, 0x16),
	_INIT_DCS_CMD(0xCC, 0xAF),
	_INIT_DCS_CMD(0xCD, 0xFF),
	_INIT_DCS_CMD(0xCE, 0xFF),
	_INIT_DCS_CMD(0xB0, 0x0A),
	_INIT_DCS_CMD(0xB1, 0x00),
	_INIT_DCS_CMD(0xB2, 0x02),
	_INIT_DCS_CMD(0xB3, 0x0F),
	_INIT_DCS_CMD(0xB4, 0x25),
	_INIT_DCS_CMD(0xB5, 0x39),
	_INIT_DCS_CMD(0xB6, 0x4E),
	_INIT_DCS_CMD(0xB7, 0x72),
	_INIT_DCS_CMD(0xB8, 0x97),
	_INIT_DCS_CMD(0xB9, 0xDC),
	_INIT_DCS_CMD(0xBA, 0x22),
	_INIT_DCS_CMD(0xBB, 0xA4),
	_INIT_DCS_CMD(0xBC, 0x2B),
	_INIT_DCS_CMD(0xBD, 0x2F),
	_INIT_DCS_CMD(0xBE, 0xA9),
	_INIT_DCS_CMD(0xBF, 0x25),
	_INIT_DCS_CMD(0xC0, 0x61),
	_INIT_DCS_CMD(0xC1, 0x97),
	_INIT_DCS_CMD(0xC2, 0xB2),
	_INIT_DCS_CMD(0xC3, 0xCD),
	_INIT_DCS_CMD(0xC4, 0xD9),
	_INIT_DCS_CMD(0xC5, 0xE7),
	_INIT_DCS_CMD(0xC6, 0xF4),
	_INIT_DCS_CMD(0xC7, 0xFA),
	_INIT_DCS_CMD(0xC8, 0xFC),
	_INIT_DCS_CMD(0xC9, 0x00),
	_INIT_DCS_CMD(0xCA, 0x00),
	_INIT_DCS_CMD(0xCB, 0x16),
	_INIT_DCS_CMD(0xCC, 0xAF),
	_INIT_DCS_CMD(0xCD, 0xFF),
	_INIT_DCS_CMD(0xCE, 0xFF),
	_INIT_DCS_CMD(0xB0, 0x0B),
	_INIT_DCS_CMD(0xB1, 0x04),
	_INIT_DCS_CMD(0xB2, 0x05),
	_INIT_DCS_CMD(0xB3, 0x11),
	_INIT_DCS_CMD(0xB4, 0x24),
	_INIT_DCS_CMD(0xB5, 0x39),
	_INIT_DCS_CMD(0xB6, 0x4F),
	_INIT_DCS_CMD(0xB7, 0x72),
	_INIT_DCS_CMD(0xB8, 0x98),
	_INIT_DCS_CMD(0xB9, 0xDC),
	_INIT_DCS_CMD(0xBA, 0x23),
	_INIT_DCS_CMD(0xBB, 0xA6),
	_INIT_DCS_CMD(0xBC, 0x2C),
	_INIT_DCS_CMD(0xBD, 0x30),
	_INIT_DCS_CMD(0xBE, 0xAA),
	_INIT_DCS_CMD(0xBF, 0x26),
	_INIT_DCS_CMD(0xC0, 0x62),
	_INIT_DCS_CMD(0xC1, 0x9B),
	_INIT_DCS_CMD(0xC2, 0xB5),
	_INIT_DCS_CMD(0xC3, 0xCF),
	_INIT_DCS_CMD(0xC4, 0xDB),
	_INIT_DCS_CMD(0xC5, 0xE8),
	_INIT_DCS_CMD(0xC6, 0xF5),
	_INIT_DCS_CMD(0xC7, 0xFA),
	_INIT_DCS_CMD(0xC8, 0xFC),
	_INIT_DCS_CMD(0xC9, 0x00),
	_INIT_DCS_CMD(0xCA, 0x00),
	_INIT_DCS_CMD(0xCB, 0x16),
	_INIT_DCS_CMD(0xCC, 0xAF),
	_INIT_DCS_CMD(0xCD, 0xFF),
	_INIT_DCS_CMD(0xCE, 0xFF),
	_INIT_DCS_CMD(0xB0, 0x0C),
	_INIT_DCS_CMD(0xB1, 0x04),
	_INIT_DCS_CMD(0xB2, 0x02),
	_INIT_DCS_CMD(0xB3, 0x16),
	_INIT_DCS_CMD(0xB4, 0x24),
	_INIT_DCS_CMD(0xB5, 0x3B),
	_INIT_DCS_CMD(0xB6, 0x4F),
	_INIT_DCS_CMD(0xB7, 0x73),
	_INIT_DCS_CMD(0xB8, 0x99),
	_INIT_DCS_CMD(0xB9, 0xE0),
	_INIT_DCS_CMD(0xBA, 0x26),
	_INIT_DCS_CMD(0xBB, 0xAD),
	_INIT_DCS_CMD(0xBC, 0x36),
	_INIT_DCS_CMD(0xBD, 0x3A),
	_INIT_DCS_CMD(0xBE, 0xAE),
	_INIT_DCS_CMD(0xBF, 0x2A),
	_INIT_DCS_CMD(0xC0, 0x66),
	_INIT_DCS_CMD(0xC1, 0x9E),
	_INIT_DCS_CMD(0xC2, 0xB8),
	_INIT_DCS_CMD(0xC3, 0xD1),
	_INIT_DCS_CMD(0xC4, 0xDD),
	_INIT_DCS_CMD(0xC5, 0xE9),
	_INIT_DCS_CMD(0xC6, 0xF6),
	_INIT_DCS_CMD(0xC7, 0xFA),
	_INIT_DCS_CMD(0xC8, 0xFC),
	_INIT_DCS_CMD(0xC9, 0x00),
	_INIT_DCS_CMD(0xCA, 0x00),
	_INIT_DCS_CMD(0xCB, 0x16),
	_INIT_DCS_CMD(0xCC, 0xAF),
	_INIT_DCS_CMD(0xCD, 0xFF),
	_INIT_DCS_CMD(0xCE, 0xFF),
	_INIT_DCS_CMD(0xB0, 0x00),
	_INIT_DCS_CMD(0xB3, 0x08),
	_INIT_DCS_CMD(0xB0, 0x04),
	_INIT_DCS_CMD(0xB8, 0x68),
	_INIT_DELAY_CMD(150),
	अणुपूर्ण,
पूर्ण;

अटल स्थिर काष्ठा panel_init_cmd auo_kd101n80_45na_init_cmd[] = अणु
	_INIT_DELAY_CMD(24),
	_INIT_DCS_CMD(0x11),
	_INIT_DELAY_CMD(120),
	_INIT_DCS_CMD(0x29),
	_INIT_DELAY_CMD(120),
	अणुपूर्ण,
पूर्ण;

अटल स्थिर काष्ठा panel_init_cmd auo_b101uan08_3_init_cmd[] = अणु
	_INIT_DELAY_CMD(24),
	_INIT_DCS_CMD(0xB0, 0x01),
	_INIT_DCS_CMD(0xC0, 0x48),
	_INIT_DCS_CMD(0xC1, 0x48),
	_INIT_DCS_CMD(0xC2, 0x47),
	_INIT_DCS_CMD(0xC3, 0x47),
	_INIT_DCS_CMD(0xC4, 0x46),
	_INIT_DCS_CMD(0xC5, 0x46),
	_INIT_DCS_CMD(0xC6, 0x45),
	_INIT_DCS_CMD(0xC7, 0x45),
	_INIT_DCS_CMD(0xC8, 0x64),
	_INIT_DCS_CMD(0xC9, 0x64),
	_INIT_DCS_CMD(0xCA, 0x4F),
	_INIT_DCS_CMD(0xCB, 0x4F),
	_INIT_DCS_CMD(0xCC, 0x40),
	_INIT_DCS_CMD(0xCD, 0x40),
	_INIT_DCS_CMD(0xCE, 0x66),
	_INIT_DCS_CMD(0xCF, 0x66),
	_INIT_DCS_CMD(0xD0, 0x4F),
	_INIT_DCS_CMD(0xD1, 0x4F),
	_INIT_DCS_CMD(0xD2, 0x41),
	_INIT_DCS_CMD(0xD3, 0x41),
	_INIT_DCS_CMD(0xD4, 0x48),
	_INIT_DCS_CMD(0xD5, 0x48),
	_INIT_DCS_CMD(0xD6, 0x47),
	_INIT_DCS_CMD(0xD7, 0x47),
	_INIT_DCS_CMD(0xD8, 0x46),
	_INIT_DCS_CMD(0xD9, 0x46),
	_INIT_DCS_CMD(0xDA, 0x45),
	_INIT_DCS_CMD(0xDB, 0x45),
	_INIT_DCS_CMD(0xDC, 0x64),
	_INIT_DCS_CMD(0xDD, 0x64),
	_INIT_DCS_CMD(0xDE, 0x4F),
	_INIT_DCS_CMD(0xDF, 0x4F),
	_INIT_DCS_CMD(0xE0, 0x40),
	_INIT_DCS_CMD(0xE1, 0x40),
	_INIT_DCS_CMD(0xE2, 0x66),
	_INIT_DCS_CMD(0xE3, 0x66),
	_INIT_DCS_CMD(0xE4, 0x4F),
	_INIT_DCS_CMD(0xE5, 0x4F),
	_INIT_DCS_CMD(0xE6, 0x41),
	_INIT_DCS_CMD(0xE7, 0x41),
	_INIT_DELAY_CMD(150),
	अणुपूर्ण,
पूर्ण;

अटल अंतरभूत काष्ठा boe_panel *to_boe_panel(काष्ठा drm_panel *panel)
अणु
	वापस container_of(panel, काष्ठा boe_panel, base);
पूर्ण

अटल पूर्णांक boe_panel_init_dcs_cmd(काष्ठा boe_panel *boe)
अणु
	काष्ठा mipi_dsi_device *dsi = boe->dsi;
	काष्ठा drm_panel *panel = &boe->base;
	पूर्णांक i, err = 0;

	अगर (boe->desc->init_cmds) अणु
		स्थिर काष्ठा panel_init_cmd *init_cmds = boe->desc->init_cmds;

		क्रम (i = 0; init_cmds[i].len != 0; i++) अणु
			स्थिर काष्ठा panel_init_cmd *cmd = &init_cmds[i];

			चयन (cmd->type) अणु
			हाल DELAY_CMD:
				msleep(cmd->data[0]);
				err = 0;
				अवरोध;

			हाल INIT_DCS_CMD:
				err = mipi_dsi_dcs_ग_लिखो(dsi, cmd->data[0],
							 cmd->len <= 1 ? शून्य :
							 &cmd->data[1],
							 cmd->len - 1);
				अवरोध;

			शेष:
				err = -EINVAL;
			पूर्ण

			अगर (err < 0) अणु
				dev_err(panel->dev,
					"failed to write command %u\n", i);
				वापस err;
			पूर्ण
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक boe_panel_enter_sleep_mode(काष्ठा boe_panel *boe)
अणु
	काष्ठा mipi_dsi_device *dsi = boe->dsi;
	पूर्णांक ret;

	dsi->mode_flags &= ~MIPI_DSI_MODE_LPM;

	ret = mipi_dsi_dcs_set_display_off(dsi);
	अगर (ret < 0)
		वापस ret;

	ret = mipi_dsi_dcs_enter_sleep_mode(dsi);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक boe_panel_unprepare(काष्ठा drm_panel *panel)
अणु
	काष्ठा boe_panel *boe = to_boe_panel(panel);
	पूर्णांक ret;

	अगर (!boe->prepared)
		वापस 0;

	ret = boe_panel_enter_sleep_mode(boe);
	अगर (ret < 0) अणु
		dev_err(panel->dev, "failed to set panel off: %d\n", ret);
		वापस ret;
	पूर्ण

	msleep(150);

	अगर (boe->desc->disअक्षरge_on_disable) अणु
		regulator_disable(boe->avee);
		regulator_disable(boe->avdd);
		usleep_range(5000, 7000);
		gpiod_set_value(boe->enable_gpio, 0);
		usleep_range(5000, 7000);
		regulator_disable(boe->pp1800);
	पूर्ण अन्यथा अणु
		gpiod_set_value(boe->enable_gpio, 0);
		usleep_range(500, 1000);
		regulator_disable(boe->avee);
		regulator_disable(boe->avdd);
		usleep_range(5000, 7000);
		regulator_disable(boe->pp1800);
	पूर्ण

	boe->prepared = false;

	वापस 0;
पूर्ण

अटल पूर्णांक boe_panel_prepare(काष्ठा drm_panel *panel)
अणु
	काष्ठा boe_panel *boe = to_boe_panel(panel);
	पूर्णांक ret;

	अगर (boe->prepared)
		वापस 0;

	gpiod_set_value(boe->enable_gpio, 0);
	usleep_range(1000, 1500);

	ret = regulator_enable(boe->pp1800);
	अगर (ret < 0)
		वापस ret;

	usleep_range(3000, 5000);

	ret = regulator_enable(boe->avdd);
	अगर (ret < 0)
		जाओ घातeroff1v8;
	ret = regulator_enable(boe->avee);
	अगर (ret < 0)
		जाओ घातeroffavdd;

	usleep_range(5000, 10000);

	gpiod_set_value(boe->enable_gpio, 1);
	usleep_range(1000, 2000);
	gpiod_set_value(boe->enable_gpio, 0);
	usleep_range(1000, 2000);
	gpiod_set_value(boe->enable_gpio, 1);
	usleep_range(6000, 10000);

	ret = boe_panel_init_dcs_cmd(boe);
	अगर (ret < 0) अणु
		dev_err(panel->dev, "failed to init panel: %d\n", ret);
		जाओ घातeroff;
	पूर्ण

	boe->prepared = true;

	वापस 0;

घातeroff:
	regulator_disable(boe->avee);
घातeroffavdd:
	regulator_disable(boe->avdd);
घातeroff1v8:
	usleep_range(5000, 7000);
	regulator_disable(boe->pp1800);
	gpiod_set_value(boe->enable_gpio, 0);

	वापस ret;
पूर्ण

अटल पूर्णांक boe_panel_enable(काष्ठा drm_panel *panel)
अणु
	msleep(130);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा drm_display_mode boe_tv101wum_nl6_शेष_mode = अणु
	.घड़ी = 159425,
	.hdisplay = 1200,
	.hsync_start = 1200 + 100,
	.hsync_end = 1200 + 100 + 40,
	.htotal = 1200 + 100 + 40 + 24,
	.vdisplay = 1920,
	.vsync_start = 1920 + 10,
	.vsync_end = 1920 + 10 + 14,
	.vtotal = 1920 + 10 + 14 + 4,
पूर्ण;

अटल स्थिर काष्ठा panel_desc boe_tv101wum_nl6_desc = अणु
	.modes = &boe_tv101wum_nl6_शेष_mode,
	.bpc = 8,
	.size = अणु
		.width_mm = 135,
		.height_mm = 216,
	पूर्ण,
	.lanes = 4,
	.क्रमmat = MIPI_DSI_FMT_RGB888,
	.mode_flags = MIPI_DSI_MODE_VIDEO | MIPI_DSI_MODE_VIDEO_SYNC_PULSE |
		      MIPI_DSI_MODE_LPM,
	.init_cmds = boe_init_cmd,
	.disअक्षरge_on_disable = false,
पूर्ण;

अटल स्थिर काष्ठा drm_display_mode auo_kd101n80_45na_शेष_mode = अणु
	.घड़ी = 157000,
	.hdisplay = 1200,
	.hsync_start = 1200 + 60,
	.hsync_end = 1200 + 60 + 24,
	.htotal = 1200 + 60 + 24 + 56,
	.vdisplay = 1920,
	.vsync_start = 1920 + 16,
	.vsync_end = 1920 + 16 + 4,
	.vtotal = 1920 + 16 + 4 + 16,
पूर्ण;

अटल स्थिर काष्ठा panel_desc auo_kd101n80_45na_desc = अणु
	.modes = &auo_kd101n80_45na_शेष_mode,
	.bpc = 8,
	.size = अणु
		.width_mm = 135,
		.height_mm = 216,
	पूर्ण,
	.lanes = 4,
	.क्रमmat = MIPI_DSI_FMT_RGB888,
	.mode_flags = MIPI_DSI_MODE_VIDEO | MIPI_DSI_MODE_VIDEO_SYNC_PULSE |
		      MIPI_DSI_MODE_LPM,
	.init_cmds = auo_kd101n80_45na_init_cmd,
	.disअक्षरge_on_disable = true,
पूर्ण;

अटल स्थिर काष्ठा drm_display_mode boe_tv101wum_n53_शेष_mode = अणु
	.घड़ी = 159916,
	.hdisplay = 1200,
	.hsync_start = 1200 + 80,
	.hsync_end = 1200 + 80 + 24,
	.htotal = 1200 + 80 + 24 + 60,
	.vdisplay = 1920,
	.vsync_start = 1920 + 20,
	.vsync_end = 1920 + 20 + 4,
	.vtotal = 1920 + 20 + 4 + 10,
	.type = DRM_MODE_TYPE_DRIVER | DRM_MODE_TYPE_PREFERRED,
पूर्ण;

अटल स्थिर काष्ठा panel_desc boe_tv101wum_n53_desc = अणु
	.modes = &boe_tv101wum_n53_शेष_mode,
	.bpc = 8,
	.size = अणु
		.width_mm = 135,
		.height_mm = 216,
	पूर्ण,
	.lanes = 4,
	.क्रमmat = MIPI_DSI_FMT_RGB888,
	.mode_flags = MIPI_DSI_MODE_VIDEO | MIPI_DSI_MODE_VIDEO_SYNC_PULSE |
		      MIPI_DSI_MODE_LPM,
	.init_cmds = boe_init_cmd,
पूर्ण;

अटल स्थिर काष्ठा drm_display_mode auo_b101uan08_3_शेष_mode = अणु
	.घड़ी = 159667,
	.hdisplay = 1200,
	.hsync_start = 1200 + 60,
	.hsync_end = 1200 + 60 + 4,
	.htotal = 1200 + 60 + 4 + 80,
	.vdisplay = 1920,
	.vsync_start = 1920 + 34,
	.vsync_end = 1920 + 34 + 2,
	.vtotal = 1920 + 34 + 2 + 24,
	.type = DRM_MODE_TYPE_DRIVER | DRM_MODE_TYPE_PREFERRED,
पूर्ण;

अटल स्थिर काष्ठा panel_desc auo_b101uan08_3_desc = अणु
	.modes = &auo_b101uan08_3_शेष_mode,
	.bpc = 8,
	.size = अणु
		.width_mm = 135,
		.height_mm = 216,
	पूर्ण,
	.lanes = 4,
	.क्रमmat = MIPI_DSI_FMT_RGB888,
	.mode_flags = MIPI_DSI_MODE_VIDEO | MIPI_DSI_MODE_VIDEO_SYNC_PULSE |
		      MIPI_DSI_MODE_LPM,
	.init_cmds = auo_b101uan08_3_init_cmd,
पूर्ण;

अटल स्थिर काष्ठा drm_display_mode boe_tv105wum_nw0_शेष_mode = अणु
	.घड़ी = 159916,
	.hdisplay = 1200,
	.hsync_start = 1200 + 80,
	.hsync_end = 1200 + 80 + 24,
	.htotal = 1200 + 80 + 24 + 60,
	.vdisplay = 1920,
	.vsync_start = 1920 + 20,
	.vsync_end = 1920 + 20 + 4,
	.vtotal = 1920 + 20 + 4 + 10,
	.type = DRM_MODE_TYPE_DRIVER | DRM_MODE_TYPE_PREFERRED,
पूर्ण;

अटल स्थिर काष्ठा panel_desc boe_tv105wum_nw0_desc = अणु
	.modes = &boe_tv105wum_nw0_शेष_mode,
	.bpc = 8,
	.size = अणु
		.width_mm = 141,
		.height_mm = 226,
	पूर्ण,
	.lanes = 4,
	.क्रमmat = MIPI_DSI_FMT_RGB888,
	.mode_flags = MIPI_DSI_MODE_VIDEO | MIPI_DSI_MODE_VIDEO_SYNC_PULSE |
		      MIPI_DSI_MODE_LPM,
	.init_cmds = boe_init_cmd,
पूर्ण;

अटल पूर्णांक boe_panel_get_modes(काष्ठा drm_panel *panel,
			       काष्ठा drm_connector *connector)
अणु
	काष्ठा boe_panel *boe = to_boe_panel(panel);
	स्थिर काष्ठा drm_display_mode *m = boe->desc->modes;
	काष्ठा drm_display_mode *mode;

	mode = drm_mode_duplicate(connector->dev, m);
	अगर (!mode) अणु
		dev_err(panel->dev, "failed to add mode %ux%u@%u\n",
			m->hdisplay, m->vdisplay, drm_mode_vrefresh(m));
		वापस -ENOMEM;
	पूर्ण

	mode->type = DRM_MODE_TYPE_DRIVER | DRM_MODE_TYPE_PREFERRED;
	drm_mode_set_name(mode);
	drm_mode_probed_add(connector, mode);

	connector->display_info.width_mm = boe->desc->size.width_mm;
	connector->display_info.height_mm = boe->desc->size.height_mm;
	connector->display_info.bpc = boe->desc->bpc;
	drm_connector_set_panel_orientation(connector, boe->orientation);

	वापस 1;
पूर्ण

अटल स्थिर काष्ठा drm_panel_funcs boe_panel_funcs = अणु
	.unprepare = boe_panel_unprepare,
	.prepare = boe_panel_prepare,
	.enable = boe_panel_enable,
	.get_modes = boe_panel_get_modes,
पूर्ण;

अटल पूर्णांक boe_panel_add(काष्ठा boe_panel *boe)
अणु
	काष्ठा device *dev = &boe->dsi->dev;
	पूर्णांक err;

	boe->avdd = devm_regulator_get(dev, "avdd");
	अगर (IS_ERR(boe->avdd))
		वापस PTR_ERR(boe->avdd);

	boe->avee = devm_regulator_get(dev, "avee");
	अगर (IS_ERR(boe->avee))
		वापस PTR_ERR(boe->avee);

	boe->pp1800 = devm_regulator_get(dev, "pp1800");
	अगर (IS_ERR(boe->pp1800))
		वापस PTR_ERR(boe->pp1800);

	boe->enable_gpio = devm_gpiod_get(dev, "enable", GPIOD_OUT_LOW);
	अगर (IS_ERR(boe->enable_gpio)) अणु
		dev_err(dev, "cannot get reset-gpios %ld\n",
			PTR_ERR(boe->enable_gpio));
		वापस PTR_ERR(boe->enable_gpio);
	पूर्ण

	gpiod_set_value(boe->enable_gpio, 0);

	drm_panel_init(&boe->base, dev, &boe_panel_funcs,
		       DRM_MODE_CONNECTOR_DSI);
	err = of_drm_get_panel_orientation(dev->of_node, &boe->orientation);
	अगर (err < 0) अणु
		dev_err(dev, "%pOF: failed to get orientation %d\n", dev->of_node, err);
		वापस err;
	पूर्ण

	err = drm_panel_of_backlight(&boe->base);
	अगर (err)
		वापस err;

	boe->base.funcs = &boe_panel_funcs;
	boe->base.dev = &boe->dsi->dev;

	drm_panel_add(&boe->base);

	वापस 0;
पूर्ण

अटल पूर्णांक boe_panel_probe(काष्ठा mipi_dsi_device *dsi)
अणु
	काष्ठा boe_panel *boe;
	पूर्णांक ret;
	स्थिर काष्ठा panel_desc *desc;

	boe = devm_kzalloc(&dsi->dev, माप(*boe), GFP_KERNEL);
	अगर (!boe)
		वापस -ENOMEM;

	desc = of_device_get_match_data(&dsi->dev);
	dsi->lanes = desc->lanes;
	dsi->क्रमmat = desc->क्रमmat;
	dsi->mode_flags = desc->mode_flags;
	boe->desc = desc;
	boe->dsi = dsi;
	ret = boe_panel_add(boe);
	अगर (ret < 0)
		वापस ret;

	mipi_dsi_set_drvdata(dsi, boe);

	ret = mipi_dsi_attach(dsi);
	अगर (ret)
		drm_panel_हटाओ(&boe->base);

	वापस ret;
पूर्ण

अटल व्योम boe_panel_shutकरोwn(काष्ठा mipi_dsi_device *dsi)
अणु
	काष्ठा boe_panel *boe = mipi_dsi_get_drvdata(dsi);

	drm_panel_disable(&boe->base);
	drm_panel_unprepare(&boe->base);
पूर्ण

अटल पूर्णांक boe_panel_हटाओ(काष्ठा mipi_dsi_device *dsi)
अणु
	काष्ठा boe_panel *boe = mipi_dsi_get_drvdata(dsi);
	पूर्णांक ret;

	boe_panel_shutकरोwn(dsi);

	ret = mipi_dsi_detach(dsi);
	अगर (ret < 0)
		dev_err(&dsi->dev, "failed to detach from DSI host: %d\n", ret);

	अगर (boe->base.dev)
		drm_panel_हटाओ(&boe->base);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id boe_of_match[] = अणु
	अणु .compatible = "boe,tv101wum-nl6",
	  .data = &boe_tv101wum_nl6_desc
	पूर्ण,
	अणु .compatible = "auo,kd101n80-45na",
	  .data = &auo_kd101n80_45na_desc
	पूर्ण,
	अणु .compatible = "boe,tv101wum-n53",
	  .data = &boe_tv101wum_n53_desc
	पूर्ण,
	अणु .compatible = "auo,b101uan08.3",
	  .data = &auo_b101uan08_3_desc
	पूर्ण,
	अणु .compatible = "boe,tv105wum-nw0",
	  .data = &boe_tv105wum_nw0_desc
	पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, boe_of_match);

अटल काष्ठा mipi_dsi_driver boe_panel_driver = अणु
	.driver = अणु
		.name = "panel-boe-tv101wum-nl6",
		.of_match_table = boe_of_match,
	पूर्ण,
	.probe = boe_panel_probe,
	.हटाओ = boe_panel_हटाओ,
	.shutकरोwn = boe_panel_shutकरोwn,
पूर्ण;
module_mipi_dsi_driver(boe_panel_driver);

MODULE_AUTHOR("Jitao Shi <jitao.shi@mediatek.com>");
MODULE_DESCRIPTION("BOE tv101wum-nl6 1200x1920 video mode panel driver");
MODULE_LICENSE("GPL v2");
