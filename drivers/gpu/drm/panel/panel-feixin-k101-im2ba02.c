<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright (C) 2019-2020 Icenowy Zheng <icenowy@aosc.io>
 */

#समावेश <linux/gpio/consumer.h>
#समावेश <linux/delay.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/regulator/consumer.h>

#समावेश <drm/drm_mipi_dsi.h>
#समावेश <drm/drm_modes.h>
#समावेश <drm/drm_panel.h>

#घोषणा K101_IM2BA02_INIT_CMD_LEN	2

अटल स्थिर अक्षर * स्थिर regulator_names[] = अणु
	"dvdd",
	"avdd",
	"cvdd"
पूर्ण;

काष्ठा k101_im2ba02 अणु
	काष्ठा drm_panel	panel;
	काष्ठा mipi_dsi_device	*dsi;

	काष्ठा regulator_bulk_data supplies[ARRAY_SIZE(regulator_names)];
	काष्ठा gpio_desc	*reset;
पूर्ण;

अटल अंतरभूत काष्ठा k101_im2ba02 *panel_to_k101_im2ba02(काष्ठा drm_panel *panel)
अणु
	वापस container_of(panel, काष्ठा k101_im2ba02, panel);
पूर्ण

काष्ठा k101_im2ba02_init_cmd अणु
	u8 data[K101_IM2BA02_INIT_CMD_LEN];
पूर्ण;

अटल स्थिर काष्ठा k101_im2ba02_init_cmd k101_im2ba02_init_cmds[] = अणु
	/* Switch to page 0 */
	अणु .data = अणु 0xE0, 0x00 पूर्ण पूर्ण,

	/* Seems to be some password */
	अणु .data = अणु 0xE1, 0x93पूर्ण पूर्ण,
	अणु .data = अणु 0xE2, 0x65 पूर्ण पूर्ण,
	अणु .data = अणु 0xE3, 0xF8 पूर्ण पूर्ण,

	/* Lane number, 0x02 - 3 lanes, 0x03 - 4 lanes */
	अणु .data = अणु 0x80, 0x03 पूर्ण पूर्ण,

	/* Sequence control */
	अणु .data = अणु 0x70, 0x02 पूर्ण पूर्ण,
	अणु .data = अणु 0x71, 0x23 पूर्ण पूर्ण,
	अणु .data = अणु 0x72, 0x06 पूर्ण पूर्ण,

	/* Switch to page 1 */
	अणु .data = अणु 0xE0, 0x01 पूर्ण पूर्ण,

	/* Set VCOM */
	अणु .data = अणु 0x00, 0x00 पूर्ण पूर्ण,
	अणु .data = अणु 0x01, 0x66 पूर्ण पूर्ण,
	/* Set VCOM_Reverse */
	अणु .data = अणु 0x03, 0x00 पूर्ण पूर्ण,
	अणु .data = अणु 0x04, 0x25 पूर्ण पूर्ण,

	/* Set Gamma Power, VG[MS][PN] */
	अणु .data = अणु 0x17, 0x00 पूर्ण पूर्ण,
	अणु .data = अणु 0x18, 0x6D पूर्ण पूर्ण,
	अणु .data = अणु 0x19, 0x00 पूर्ण पूर्ण,
	अणु .data = अणु 0x1A, 0x00 पूर्ण पूर्ण,
	अणु .data = अणु 0x1B, 0xBF पूर्ण पूर्ण, /* VGMN = -4.5V */
	अणु .data = अणु 0x1C, 0x00 पूर्ण पूर्ण,

	/* Set Gate Power */
	अणु .data = अणु 0x1F, 0x3E पूर्ण पूर्ण, /* VGH_R = 15V */
	अणु .data = अणु 0x20, 0x28 पूर्ण पूर्ण, /* VGL_R = -11V */
	अणु .data = अणु 0x21, 0x28 पूर्ण पूर्ण, /* VGL_R2 = -11V */
	अणु .data = अणु 0x22, 0x0E पूर्ण पूर्ण, /* PA[6:4] = 0, PA[0] = 0 */

	/* Set Panel */
	अणु .data = अणु 0x37, 0x09 पूर्ण पूर्ण, /* SS = 1, BGR = 1 */

	/* Set RGBCYC */
	अणु .data = अणु 0x38, 0x04 पूर्ण पूर्ण, /* JDT = 100 column inversion */
	अणु .data = अणु 0x39, 0x08 पूर्ण पूर्ण, /* RGB_N_EQ1 */
	अणु .data = अणु 0x3A, 0x12 पूर्ण पूर्ण, /* RGB_N_EQ2 */
	अणु .data = अणु 0x3C, 0x78 पूर्ण पूर्ण, /* set EQ3 क्रम TE_H */
	अणु .data = अणु 0x3D, 0xFF पूर्ण पूर्ण, /* set CHGEN_ON */
	अणु .data = अणु 0x3E, 0xFF पूर्ण पूर्ण, /* set CHGEN_OFF */
	अणु .data = अणु 0x3F, 0x7F पूर्ण पूर्ण, /* set CHGEN_OFF2 */

	/* Set TCON parameter */
	अणु .data = अणु 0x40, 0x06 पूर्ण पूर्ण, /* RSO = 800 poपूर्णांकs */
	अणु .data = अणु 0x41, 0xA0 पूर्ण पूर्ण, /* LN = 1280 lines */

	/* Set घातer voltage */
	अणु .data = अणु 0x55, 0x0F पूर्ण पूर्ण, /* DCDCM */
	अणु .data = अणु 0x56, 0x01 पूर्ण पूर्ण,
	अणु .data = अणु 0x57, 0x69 पूर्ण पूर्ण,
	अणु .data = अणु 0x58, 0x0A पूर्ण पूर्ण,
	अणु .data = अणु 0x59, 0x0A पूर्ण पूर्ण,
	अणु .data = अणु 0x5A, 0x45 पूर्ण पूर्ण,
	अणु .data = अणु 0x5B, 0x15 पूर्ण पूर्ण,

	/* Set gamma */
	अणु .data = अणु 0x5D, 0x7C पूर्ण पूर्ण,
	अणु .data = अणु 0x5E, 0x65 पूर्ण पूर्ण,
	अणु .data = अणु 0x5F, 0x55 पूर्ण पूर्ण,
	अणु .data = अणु 0x60, 0x49 पूर्ण पूर्ण,
	अणु .data = अणु 0x61, 0x44 पूर्ण पूर्ण,
	अणु .data = अणु 0x62, 0x35 पूर्ण पूर्ण,
	अणु .data = अणु 0x63, 0x3A पूर्ण पूर्ण,
	अणु .data = अणु 0x64, 0x23 पूर्ण पूर्ण,
	अणु .data = अणु 0x65, 0x3D पूर्ण पूर्ण,
	अणु .data = अणु 0x66, 0x3C पूर्ण पूर्ण,
	अणु .data = अणु 0x67, 0x3D पूर्ण पूर्ण,
	अणु .data = अणु 0x68, 0x5D पूर्ण पूर्ण,
	अणु .data = अणु 0x69, 0x4D पूर्ण पूर्ण,
	अणु .data = अणु 0x6A, 0x56 पूर्ण पूर्ण,
	अणु .data = अणु 0x6B, 0x48 पूर्ण पूर्ण,
	अणु .data = अणु 0x6C, 0x45 पूर्ण पूर्ण,
	अणु .data = अणु 0x6D, 0x38 पूर्ण पूर्ण,
	अणु .data = अणु 0x6E, 0x25 पूर्ण पूर्ण,
	अणु .data = अणु 0x6F, 0x00 पूर्ण पूर्ण,
	अणु .data = अणु 0x70, 0x7C पूर्ण पूर्ण,
	अणु .data = अणु 0x71, 0x65 पूर्ण पूर्ण,
	अणु .data = अणु 0x72, 0x55 पूर्ण पूर्ण,
	अणु .data = अणु 0x73, 0x49 पूर्ण पूर्ण,
	अणु .data = अणु 0x74, 0x44 पूर्ण पूर्ण,
	अणु .data = अणु 0x75, 0x35 पूर्ण पूर्ण,
	अणु .data = अणु 0x76, 0x3A पूर्ण पूर्ण,
	अणु .data = अणु 0x77, 0x23 पूर्ण पूर्ण,
	अणु .data = अणु 0x78, 0x3D पूर्ण पूर्ण,
	अणु .data = अणु 0x79, 0x3C पूर्ण पूर्ण,
	अणु .data = अणु 0x7A, 0x3D पूर्ण पूर्ण,
	अणु .data = अणु 0x7B, 0x5D पूर्ण पूर्ण,
	अणु .data = अणु 0x7C, 0x4D पूर्ण पूर्ण,
	अणु .data = अणु 0x7D, 0x56 पूर्ण पूर्ण,
	अणु .data = अणु 0x7E, 0x48 पूर्ण पूर्ण,
	अणु .data = अणु 0x7F, 0x45 पूर्ण पूर्ण,
	अणु .data = अणु 0x80, 0x38 पूर्ण पूर्ण,
	अणु .data = अणु 0x81, 0x25 पूर्ण पूर्ण,
	अणु .data = अणु 0x82, 0x00 पूर्ण पूर्ण,

	/* Switch to page 2, क्रम GIP */
	अणु .data = अणु 0xE0, 0x02 पूर्ण पूर्ण,

	अणु .data = अणु 0x00, 0x1E पूर्ण पूर्ण,
	अणु .data = अणु 0x01, 0x1E पूर्ण पूर्ण,
	अणु .data = अणु 0x02, 0x41 पूर्ण पूर्ण,
	अणु .data = अणु 0x03, 0x41 पूर्ण पूर्ण,
	अणु .data = अणु 0x04, 0x43 पूर्ण पूर्ण,
	अणु .data = अणु 0x05, 0x43 पूर्ण पूर्ण,
	अणु .data = अणु 0x06, 0x1F पूर्ण पूर्ण,
	अणु .data = अणु 0x07, 0x1F पूर्ण पूर्ण,
	अणु .data = अणु 0x08, 0x1F पूर्ण पूर्ण,
	अणु .data = अणु 0x09, 0x1F पूर्ण पूर्ण,
	अणु .data = अणु 0x0A, 0x1E पूर्ण पूर्ण,
	अणु .data = अणु 0x0B, 0x1E पूर्ण पूर्ण,
	अणु .data = अणु 0x0C, 0x1F पूर्ण पूर्ण,
	अणु .data = अणु 0x0D, 0x47 पूर्ण पूर्ण,
	अणु .data = अणु 0x0E, 0x47 पूर्ण पूर्ण,
	अणु .data = अणु 0x0F, 0x45 पूर्ण पूर्ण,
	अणु .data = अणु 0x10, 0x45 पूर्ण पूर्ण,
	अणु .data = अणु 0x11, 0x4B पूर्ण पूर्ण,
	अणु .data = अणु 0x12, 0x4B पूर्ण पूर्ण,
	अणु .data = अणु 0x13, 0x49 पूर्ण पूर्ण,
	अणु .data = अणु 0x14, 0x49 पूर्ण पूर्ण,
	अणु .data = अणु 0x15, 0x1F पूर्ण पूर्ण,

	अणु .data = अणु 0x16, 0x1E पूर्ण पूर्ण,
	अणु .data = अणु 0x17, 0x1E पूर्ण पूर्ण,
	अणु .data = अणु 0x18, 0x40 पूर्ण पूर्ण,
	अणु .data = अणु 0x19, 0x40 पूर्ण पूर्ण,
	अणु .data = अणु 0x1A, 0x42 पूर्ण पूर्ण,
	अणु .data = अणु 0x1B, 0x42 पूर्ण पूर्ण,
	अणु .data = अणु 0x1C, 0x1F पूर्ण पूर्ण,
	अणु .data = अणु 0x1D, 0x1F पूर्ण पूर्ण,
	अणु .data = अणु 0x1E, 0x1F पूर्ण पूर्ण,
	अणु .data = अणु 0x1F, 0x1f पूर्ण पूर्ण,
	अणु .data = अणु 0x20, 0x1E पूर्ण पूर्ण,
	अणु .data = अणु 0x21, 0x1E पूर्ण पूर्ण,
	अणु .data = अणु 0x22, 0x1f पूर्ण पूर्ण,
	अणु .data = अणु 0x23, 0x46 पूर्ण पूर्ण,
	अणु .data = अणु 0x24, 0x46 पूर्ण पूर्ण,
	अणु .data = अणु 0x25, 0x44 पूर्ण पूर्ण,
	अणु .data = अणु 0x26, 0x44 पूर्ण पूर्ण,
	अणु .data = अणु 0x27, 0x4A पूर्ण पूर्ण,
	अणु .data = अणु 0x28, 0x4A पूर्ण पूर्ण,
	अणु .data = अणु 0x29, 0x48 पूर्ण पूर्ण,
	अणु .data = अणु 0x2A, 0x48 पूर्ण पूर्ण,
	अणु .data = अणु 0x2B, 0x1f पूर्ण पूर्ण,

	अणु .data = अणु 0x2C, 0x1F पूर्ण पूर्ण,
	अणु .data = अणु 0x2D, 0x1F पूर्ण पूर्ण,
	अणु .data = अणु 0x2E, 0x42 पूर्ण पूर्ण,
	अणु .data = अणु 0x2F, 0x42 पूर्ण पूर्ण,
	अणु .data = अणु 0x30, 0x40 पूर्ण पूर्ण,
	अणु .data = अणु 0x31, 0x40 पूर्ण पूर्ण,
	अणु .data = अणु 0x32, 0x1E पूर्ण पूर्ण,
	अणु .data = अणु 0x33, 0x1E पूर्ण पूर्ण,
	अणु .data = अणु 0x34, 0x1F पूर्ण पूर्ण,
	अणु .data = अणु 0x35, 0x1F पूर्ण पूर्ण,
	अणु .data = अणु 0x36, 0x1E पूर्ण पूर्ण,
	अणु .data = अणु 0x37, 0x1E पूर्ण पूर्ण,
	अणु .data = अणु 0x38, 0x1F पूर्ण पूर्ण,
	अणु .data = अणु 0x39, 0x48 पूर्ण पूर्ण,
	अणु .data = अणु 0x3A, 0x48 पूर्ण पूर्ण,
	अणु .data = अणु 0x3B, 0x4A पूर्ण पूर्ण,
	अणु .data = अणु 0x3C, 0x4A पूर्ण पूर्ण,
	अणु .data = अणु 0x3D, 0x44 पूर्ण पूर्ण,
	अणु .data = अणु 0x3E, 0x44 पूर्ण पूर्ण,
	अणु .data = अणु 0x3F, 0x46 पूर्ण पूर्ण,
	अणु .data = अणु 0x40, 0x46 पूर्ण पूर्ण,
	अणु .data = अणु 0x41, 0x1F पूर्ण पूर्ण,

	अणु .data = अणु 0x42, 0x1F पूर्ण पूर्ण,
	अणु .data = अणु 0x43, 0x1F पूर्ण पूर्ण,
	अणु .data = अणु 0x44, 0x43 पूर्ण पूर्ण,
	अणु .data = अणु 0x45, 0x43 पूर्ण पूर्ण,
	अणु .data = अणु 0x46, 0x41 पूर्ण पूर्ण,
	अणु .data = अणु 0x47, 0x41 पूर्ण पूर्ण,
	अणु .data = अणु 0x48, 0x1E पूर्ण पूर्ण,
	अणु .data = अणु 0x49, 0x1E पूर्ण पूर्ण,
	अणु .data = अणु 0x4A, 0x1E पूर्ण पूर्ण,
	अणु .data = अणु 0x4B, 0x1F पूर्ण पूर्ण,
	अणु .data = अणु 0x4C, 0x1E पूर्ण पूर्ण,
	अणु .data = अणु 0x4D, 0x1E पूर्ण पूर्ण,
	अणु .data = अणु 0x4E, 0x1F पूर्ण पूर्ण,
	अणु .data = अणु 0x4F, 0x49 पूर्ण पूर्ण,
	अणु .data = अणु 0x50, 0x49 पूर्ण पूर्ण,
	अणु .data = अणु 0x51, 0x4B पूर्ण पूर्ण,
	अणु .data = अणु 0x52, 0x4B पूर्ण पूर्ण,
	अणु .data = अणु 0x53, 0x45 पूर्ण पूर्ण,
	अणु .data = अणु 0x54, 0x45 पूर्ण पूर्ण,
	अणु .data = अणु 0x55, 0x47 पूर्ण पूर्ण,
	अणु .data = अणु 0x56, 0x47 पूर्ण पूर्ण,
	अणु .data = अणु 0x57, 0x1F पूर्ण पूर्ण,

	अणु .data = अणु 0x58, 0x10 पूर्ण पूर्ण,
	अणु .data = अणु 0x59, 0x00 पूर्ण पूर्ण,
	अणु .data = अणु 0x5A, 0x00 पूर्ण पूर्ण,
	अणु .data = अणु 0x5B, 0x30 पूर्ण पूर्ण,
	अणु .data = अणु 0x5C, 0x02 पूर्ण पूर्ण,
	अणु .data = अणु 0x5D, 0x40 पूर्ण पूर्ण,
	अणु .data = अणु 0x5E, 0x01 पूर्ण पूर्ण,
	अणु .data = अणु 0x5F, 0x02 पूर्ण पूर्ण,
	अणु .data = अणु 0x60, 0x30 पूर्ण पूर्ण,
	अणु .data = अणु 0x61, 0x01 पूर्ण पूर्ण,
	अणु .data = अणु 0x62, 0x02 पूर्ण पूर्ण,
	अणु .data = अणु 0x63, 0x6A पूर्ण पूर्ण,
	अणु .data = अणु 0x64, 0x6A पूर्ण पूर्ण,
	अणु .data = अणु 0x65, 0x05 पूर्ण पूर्ण,
	अणु .data = अणु 0x66, 0x12 पूर्ण पूर्ण,
	अणु .data = अणु 0x67, 0x74 पूर्ण पूर्ण,
	अणु .data = अणु 0x68, 0x04 पूर्ण पूर्ण,
	अणु .data = अणु 0x69, 0x6A पूर्ण पूर्ण,
	अणु .data = अणु 0x6A, 0x6A पूर्ण पूर्ण,
	अणु .data = अणु 0x6B, 0x08 पूर्ण पूर्ण,

	अणु .data = अणु 0x6C, 0x00 पूर्ण पूर्ण,
	अणु .data = अणु 0x6D, 0x04 पूर्ण पूर्ण,
	अणु .data = अणु 0x6E, 0x04 पूर्ण पूर्ण,
	अणु .data = अणु 0x6F, 0x88 पूर्ण पूर्ण,
	अणु .data = अणु 0x70, 0x00 पूर्ण पूर्ण,
	अणु .data = अणु 0x71, 0x00 पूर्ण पूर्ण,
	अणु .data = अणु 0x72, 0x06 पूर्ण पूर्ण,
	अणु .data = अणु 0x73, 0x7B पूर्ण पूर्ण,
	अणु .data = अणु 0x74, 0x00 पूर्ण पूर्ण,
	अणु .data = अणु 0x75, 0x07 पूर्ण पूर्ण,
	अणु .data = अणु 0x76, 0x00 पूर्ण पूर्ण,
	अणु .data = अणु 0x77, 0x5D पूर्ण पूर्ण,
	अणु .data = अणु 0x78, 0x17 पूर्ण पूर्ण,
	अणु .data = अणु 0x79, 0x1F पूर्ण पूर्ण,
	अणु .data = अणु 0x7A, 0x00 पूर्ण पूर्ण,
	अणु .data = अणु 0x7B, 0x00 पूर्ण पूर्ण,
	अणु .data = अणु 0x7C, 0x00 पूर्ण पूर्ण,
	अणु .data = अणु 0x7D, 0x03 पूर्ण पूर्ण,
	अणु .data = अणु 0x7E, 0x7B पूर्ण पूर्ण,

	अणु .data = अणु 0xE0, 0x04 पूर्ण पूर्ण,
	अणु .data = अणु 0x2B, 0x2B पूर्ण पूर्ण,
	अणु .data = अणु 0x2E, 0x44 पूर्ण पूर्ण,

	अणु .data = अणु 0xE0, 0x01 पूर्ण पूर्ण,
	अणु .data = अणु 0x0E, 0x01 पूर्ण पूर्ण,

	अणु .data = अणु 0xE0, 0x03 पूर्ण पूर्ण,
	अणु .data = अणु 0x98, 0x2F पूर्ण पूर्ण,

	अणु .data = अणु 0xE0, 0x00 पूर्ण पूर्ण,
	अणु .data = अणु 0xE6, 0x02 पूर्ण पूर्ण,
	अणु .data = अणु 0xE7, 0x02 पूर्ण पूर्ण,

	अणु .data = अणु 0x11, 0x00 पूर्ण पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा k101_im2ba02_init_cmd समयd_cmds[] = अणु
	अणु .data = अणु 0x29, 0x00 पूर्ण पूर्ण,
	अणु .data = अणु 0x35, 0x00 पूर्ण पूर्ण,
पूर्ण;

अटल पूर्णांक k101_im2ba02_prepare(काष्ठा drm_panel *panel)
अणु
	काष्ठा k101_im2ba02 *ctx = panel_to_k101_im2ba02(panel);
	काष्ठा mipi_dsi_device *dsi = ctx->dsi;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	ret = regulator_bulk_enable(ARRAY_SIZE(ctx->supplies), ctx->supplies);
	अगर (ret)
		वापस ret;

	msleep(30);

	gpiod_set_value(ctx->reset, 1);
	msleep(50);

	gpiod_set_value(ctx->reset, 0);
	msleep(50);

	gpiod_set_value(ctx->reset, 1);
	msleep(200);

	क्रम (i = 0; i < ARRAY_SIZE(k101_im2ba02_init_cmds); i++) अणु
		स्थिर काष्ठा k101_im2ba02_init_cmd *cmd = &k101_im2ba02_init_cmds[i];

		ret = mipi_dsi_dcs_ग_लिखो_buffer(dsi, cmd->data, K101_IM2BA02_INIT_CMD_LEN);
		अगर (ret < 0)
			जाओ घातerकरोwn;
	पूर्ण

	वापस 0;

घातerकरोwn:
	gpiod_set_value(ctx->reset, 0);
	msleep(50);

	वापस regulator_bulk_disable(ARRAY_SIZE(ctx->supplies), ctx->supplies);
पूर्ण

अटल पूर्णांक k101_im2ba02_enable(काष्ठा drm_panel *panel)
अणु
	काष्ठा k101_im2ba02 *ctx = panel_to_k101_im2ba02(panel);
	स्थिर काष्ठा k101_im2ba02_init_cmd *cmd = &समयd_cmds[1];
	पूर्णांक ret;

	msleep(150);

	ret = mipi_dsi_dcs_set_display_on(ctx->dsi);
	अगर (ret < 0)
		वापस ret;

	msleep(50);

	वापस mipi_dsi_dcs_ग_लिखो_buffer(ctx->dsi, cmd->data, K101_IM2BA02_INIT_CMD_LEN);
पूर्ण

अटल पूर्णांक k101_im2ba02_disable(काष्ठा drm_panel *panel)
अणु
	काष्ठा k101_im2ba02 *ctx = panel_to_k101_im2ba02(panel);

	वापस mipi_dsi_dcs_set_display_off(ctx->dsi);
पूर्ण

अटल पूर्णांक k101_im2ba02_unprepare(काष्ठा drm_panel *panel)
अणु
	काष्ठा k101_im2ba02 *ctx = panel_to_k101_im2ba02(panel);
	पूर्णांक ret;

	ret = mipi_dsi_dcs_set_display_off(ctx->dsi);
	अगर (ret < 0)
		dev_err(panel->dev, "failed to set display off: %d\n", ret);

	ret = mipi_dsi_dcs_enter_sleep_mode(ctx->dsi);
	अगर (ret < 0)
		dev_err(panel->dev, "failed to enter sleep mode: %d\n", ret);

	msleep(200);

	gpiod_set_value(ctx->reset, 0);
	msleep(20);

	वापस regulator_bulk_disable(ARRAY_SIZE(ctx->supplies), ctx->supplies);
पूर्ण

अटल स्थिर काष्ठा drm_display_mode k101_im2ba02_शेष_mode = अणु
	.घड़ी = 70000,

	.hdisplay = 800,
	.hsync_start = 800 + 20,
	.hsync_end = 800 + 20 + 20,
	.htotal = 800 + 20 + 20 + 20,

	.vdisplay = 1280,
	.vsync_start = 1280 + 16,
	.vsync_end = 1280 + 16 + 4,
	.vtotal = 1280 + 16 + 4 + 4,

	.type = DRM_MODE_TYPE_DRIVER | DRM_MODE_TYPE_PREFERRED,
	.width_mm	= 136,
	.height_mm	= 217,
पूर्ण;

अटल पूर्णांक k101_im2ba02_get_modes(काष्ठा drm_panel *panel,
				  काष्ठा drm_connector *connector)
अणु
	काष्ठा k101_im2ba02 *ctx = panel_to_k101_im2ba02(panel);
	काष्ठा drm_display_mode *mode;

	mode = drm_mode_duplicate(connector->dev, &k101_im2ba02_शेष_mode);
	अगर (!mode) अणु
		dev_err(&ctx->dsi->dev, "failed to add mode %ux%u@%u\n",
			k101_im2ba02_शेष_mode.hdisplay,
			k101_im2ba02_शेष_mode.vdisplay,
			drm_mode_vrefresh(&k101_im2ba02_शेष_mode));
		वापस -ENOMEM;
	पूर्ण

	drm_mode_set_name(mode);

	mode->type = DRM_MODE_TYPE_DRIVER | DRM_MODE_TYPE_PREFERRED;
	connector->display_info.width_mm = mode->width_mm;
	connector->display_info.height_mm = mode->height_mm;
	drm_mode_probed_add(connector, mode);

	वापस 1;
पूर्ण

अटल स्थिर काष्ठा drm_panel_funcs k101_im2ba02_funcs = अणु
	.disable = k101_im2ba02_disable,
	.unprepare = k101_im2ba02_unprepare,
	.prepare = k101_im2ba02_prepare,
	.enable = k101_im2ba02_enable,
	.get_modes = k101_im2ba02_get_modes,
पूर्ण;

अटल पूर्णांक k101_im2ba02_dsi_probe(काष्ठा mipi_dsi_device *dsi)
अणु
	काष्ठा k101_im2ba02 *ctx;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	ctx = devm_kzalloc(&dsi->dev, माप(*ctx), GFP_KERNEL);
	अगर (!ctx)
		वापस -ENOMEM;

	mipi_dsi_set_drvdata(dsi, ctx);
	ctx->dsi = dsi;

	क्रम (i = 0; i < ARRAY_SIZE(ctx->supplies); i++)
		ctx->supplies[i].supply = regulator_names[i];

	ret = devm_regulator_bulk_get(&dsi->dev, ARRAY_SIZE(ctx->supplies),
				      ctx->supplies);
	अगर (ret < 0) अणु
		dev_err(&dsi->dev, "Couldn't get regulators\n");
		वापस ret;
	पूर्ण

	ctx->reset = devm_gpiod_get(&dsi->dev, "reset", GPIOD_OUT_LOW);
	अगर (IS_ERR(ctx->reset)) अणु
		dev_err(&dsi->dev, "Couldn't get our reset GPIO\n");
		वापस PTR_ERR(ctx->reset);
	पूर्ण

	drm_panel_init(&ctx->panel, &dsi->dev, &k101_im2ba02_funcs,
		       DRM_MODE_CONNECTOR_DSI);

	ret = drm_panel_of_backlight(&ctx->panel);
	अगर (ret)
		वापस ret;

	drm_panel_add(&ctx->panel);

	dsi->mode_flags = MIPI_DSI_MODE_VIDEO;
	dsi->क्रमmat = MIPI_DSI_FMT_RGB888;
	dsi->lanes = 4;

	ret = mipi_dsi_attach(dsi);
	अगर (ret < 0) अणु
		drm_panel_हटाओ(&ctx->panel);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक k101_im2ba02_dsi_हटाओ(काष्ठा mipi_dsi_device *dsi)
अणु
	काष्ठा k101_im2ba02 *ctx = mipi_dsi_get_drvdata(dsi);

	mipi_dsi_detach(dsi);
	drm_panel_हटाओ(&ctx->panel);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id k101_im2ba02_of_match[] = अणु
	अणु .compatible = "feixin,k101-im2ba02", पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, k101_im2ba02_of_match);

अटल काष्ठा mipi_dsi_driver k101_im2ba02_driver = अणु
	.probe = k101_im2ba02_dsi_probe,
	.हटाओ = k101_im2ba02_dsi_हटाओ,
	.driver = अणु
		.name = "feixin-k101-im2ba02",
		.of_match_table = k101_im2ba02_of_match,
	पूर्ण,
पूर्ण;
module_mipi_dsi_driver(k101_im2ba02_driver);

MODULE_AUTHOR("Icenowy Zheng <icenowy@aosc.io>");
MODULE_DESCRIPTION("Feixin K101 IM2BA02 MIPI-DSI LCD panel");
MODULE_LICENSE("GPL");
