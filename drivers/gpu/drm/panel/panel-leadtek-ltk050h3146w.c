<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2020 Theobroma Systems Design und Consulting GmbH
 */

#समावेश <linux/delay.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/media-bus-क्रमmat.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/regulator/consumer.h>

#समावेश <video/display_timing.h>
#समावेश <video/mipi_display.h>

#समावेश <drm/drm_mipi_dsi.h>
#समावेश <drm/drm_modes.h>
#समावेश <drm/drm_panel.h>

काष्ठा ltk050h3146w_cmd अणु
	अक्षर cmd;
	अक्षर data;
पूर्ण;

काष्ठा ltk050h3146w;
काष्ठा ltk050h3146w_desc अणु
	स्थिर काष्ठा drm_display_mode *mode;
	पूर्णांक (*init)(काष्ठा ltk050h3146w *ctx);
पूर्ण;

काष्ठा ltk050h3146w अणु
	काष्ठा device *dev;
	काष्ठा drm_panel panel;
	काष्ठा gpio_desc *reset_gpio;
	काष्ठा regulator *vci;
	काष्ठा regulator *iovcc;
	स्थिर काष्ठा ltk050h3146w_desc *panel_desc;
	bool prepared;
पूर्ण;

अटल स्थिर काष्ठा ltk050h3146w_cmd page1_cmds[] = अणु
	अणु 0x22, 0x0A पूर्ण, /* BGR SS GS */
	अणु 0x31, 0x00 पूर्ण, /* column inversion */
	अणु 0x53, 0xA2 पूर्ण, /* VCOM1 */
	अणु 0x55, 0xA2 पूर्ण, /* VCOM2 */
	अणु 0x50, 0x81 पूर्ण, /* VREG1OUT=5V */
	अणु 0x51, 0x85 पूर्ण, /* VREG2OUT=-5V */
	अणु 0x62, 0x0D पूर्ण, /* EQT Time setting */
/*
 * The venकरोr init selected page 1 here _again_
 * Is this supposed to be page 2?
 */
	अणु 0xA0, 0x00 पूर्ण,
	अणु 0xA1, 0x1A पूर्ण,
	अणु 0xA2, 0x28 पूर्ण,
	अणु 0xA3, 0x13 पूर्ण,
	अणु 0xA4, 0x16 पूर्ण,
	अणु 0xA5, 0x29 पूर्ण,
	अणु 0xA6, 0x1D पूर्ण,
	अणु 0xA7, 0x1E पूर्ण,
	अणु 0xA8, 0x84 पूर्ण,
	अणु 0xA9, 0x1C पूर्ण,
	अणु 0xAA, 0x28 पूर्ण,
	अणु 0xAB, 0x75 पूर्ण,
	अणु 0xAC, 0x1A पूर्ण,
	अणु 0xAD, 0x19 पूर्ण,
	अणु 0xAE, 0x4D पूर्ण,
	अणु 0xAF, 0x22 पूर्ण,
	अणु 0xB0, 0x28 पूर्ण,
	अणु 0xB1, 0x54 पूर्ण,
	अणु 0xB2, 0x66 पूर्ण,
	अणु 0xB3, 0x39 पूर्ण,
	अणु 0xC0, 0x00 पूर्ण,
	अणु 0xC1, 0x1A पूर्ण,
	अणु 0xC2, 0x28 पूर्ण,
	अणु 0xC3, 0x13 पूर्ण,
	अणु 0xC4, 0x16 पूर्ण,
	अणु 0xC5, 0x29 पूर्ण,
	अणु 0xC6, 0x1D पूर्ण,
	अणु 0xC7, 0x1E पूर्ण,
	अणु 0xC8, 0x84 पूर्ण,
	अणु 0xC9, 0x1C पूर्ण,
	अणु 0xCA, 0x28 पूर्ण,
	अणु 0xCB, 0x75 पूर्ण,
	अणु 0xCC, 0x1A पूर्ण,
	अणु 0xCD, 0x19 पूर्ण,
	अणु 0xCE, 0x4D पूर्ण,
	अणु 0xCF, 0x22 पूर्ण,
	अणु 0xD0, 0x28 पूर्ण,
	अणु 0xD1, 0x54 पूर्ण,
	अणु 0xD2, 0x66 पूर्ण,
	अणु 0xD3, 0x39 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा ltk050h3146w_cmd page3_cmds[] = अणु
	अणु 0x01, 0x00 पूर्ण,
	अणु 0x02, 0x00 पूर्ण,
	अणु 0x03, 0x73 पूर्ण,
	अणु 0x04, 0x00 पूर्ण,
	अणु 0x05, 0x00 पूर्ण,
	अणु 0x06, 0x0a पूर्ण,
	अणु 0x07, 0x00 पूर्ण,
	अणु 0x08, 0x00 पूर्ण,
	अणु 0x09, 0x01 पूर्ण,
	अणु 0x0a, 0x00 पूर्ण,
	अणु 0x0b, 0x00 पूर्ण,
	अणु 0x0c, 0x01 पूर्ण,
	अणु 0x0d, 0x00 पूर्ण,
	अणु 0x0e, 0x00 पूर्ण,
	अणु 0x0f, 0x1d पूर्ण,
	अणु 0x10, 0x1d पूर्ण,
	अणु 0x11, 0x00 पूर्ण,
	अणु 0x12, 0x00 पूर्ण,
	अणु 0x13, 0x00 पूर्ण,
	अणु 0x14, 0x00 पूर्ण,
	अणु 0x15, 0x00 पूर्ण,
	अणु 0x16, 0x00 पूर्ण,
	अणु 0x17, 0x00 पूर्ण,
	अणु 0x18, 0x00 पूर्ण,
	अणु 0x19, 0x00 पूर्ण,
	अणु 0x1a, 0x00 पूर्ण,
	अणु 0x1b, 0x00 पूर्ण,
	अणु 0x1c, 0x00 पूर्ण,
	अणु 0x1d, 0x00 पूर्ण,
	अणु 0x1e, 0x40 पूर्ण,
	अणु 0x1f, 0x80 पूर्ण,
	अणु 0x20, 0x06 पूर्ण,
	अणु 0x21, 0x02 पूर्ण,
	अणु 0x22, 0x00 पूर्ण,
	अणु 0x23, 0x00 पूर्ण,
	अणु 0x24, 0x00 पूर्ण,
	अणु 0x25, 0x00 पूर्ण,
	अणु 0x26, 0x00 पूर्ण,
	अणु 0x27, 0x00 पूर्ण,
	अणु 0x28, 0x33 पूर्ण,
	अणु 0x29, 0x03 पूर्ण,
	अणु 0x2a, 0x00 पूर्ण,
	अणु 0x2b, 0x00 पूर्ण,
	अणु 0x2c, 0x00 पूर्ण,
	अणु 0x2d, 0x00 पूर्ण,
	अणु 0x2e, 0x00 पूर्ण,
	अणु 0x2f, 0x00 पूर्ण,
	अणु 0x30, 0x00 पूर्ण,
	अणु 0x31, 0x00 पूर्ण,
	अणु 0x32, 0x00 पूर्ण,
	अणु 0x33, 0x00 पूर्ण,
	अणु 0x34, 0x04 पूर्ण,
	अणु 0x35, 0x00 पूर्ण,
	अणु 0x36, 0x00 पूर्ण,
	अणु 0x37, 0x00 पूर्ण,
	अणु 0x38, 0x3C पूर्ण,
	अणु 0x39, 0x35 पूर्ण,
	अणु 0x3A, 0x01 पूर्ण,
	अणु 0x3B, 0x40 पूर्ण,
	अणु 0x3C, 0x00 पूर्ण,
	अणु 0x3D, 0x01 पूर्ण,
	अणु 0x3E, 0x00 पूर्ण,
	अणु 0x3F, 0x00 पूर्ण,
	अणु 0x40, 0x00 पूर्ण,
	अणु 0x41, 0x88 पूर्ण,
	अणु 0x42, 0x00 पूर्ण,
	अणु 0x43, 0x00 पूर्ण,
	अणु 0x44, 0x1F पूर्ण,
	अणु 0x50, 0x01 पूर्ण,
	अणु 0x51, 0x23 पूर्ण,
	अणु 0x52, 0x45 पूर्ण,
	अणु 0x53, 0x67 पूर्ण,
	अणु 0x54, 0x89 पूर्ण,
	अणु 0x55, 0xab पूर्ण,
	अणु 0x56, 0x01 पूर्ण,
	अणु 0x57, 0x23 पूर्ण,
	अणु 0x58, 0x45 पूर्ण,
	अणु 0x59, 0x67 पूर्ण,
	अणु 0x5a, 0x89 पूर्ण,
	अणु 0x5b, 0xab पूर्ण,
	अणु 0x5c, 0xcd पूर्ण,
	अणु 0x5d, 0xef पूर्ण,
	अणु 0x5e, 0x11 पूर्ण,
	अणु 0x5f, 0x01 पूर्ण,
	अणु 0x60, 0x00 पूर्ण,
	अणु 0x61, 0x15 पूर्ण,
	अणु 0x62, 0x14 पूर्ण,
	अणु 0x63, 0x0E पूर्ण,
	अणु 0x64, 0x0F पूर्ण,
	अणु 0x65, 0x0C पूर्ण,
	अणु 0x66, 0x0D पूर्ण,
	अणु 0x67, 0x06 पूर्ण,
	अणु 0x68, 0x02 पूर्ण,
	अणु 0x69, 0x07 पूर्ण,
	अणु 0x6a, 0x02 पूर्ण,
	अणु 0x6b, 0x02 पूर्ण,
	अणु 0x6c, 0x02 पूर्ण,
	अणु 0x6d, 0x02 पूर्ण,
	अणु 0x6e, 0x02 पूर्ण,
	अणु 0x6f, 0x02 पूर्ण,
	अणु 0x70, 0x02 पूर्ण,
	अणु 0x71, 0x02 पूर्ण,
	अणु 0x72, 0x02 पूर्ण,
	अणु 0x73, 0x02 पूर्ण,
	अणु 0x74, 0x02 पूर्ण,
	अणु 0x75, 0x01 पूर्ण,
	अणु 0x76, 0x00 पूर्ण,
	अणु 0x77, 0x14 पूर्ण,
	अणु 0x78, 0x15 पूर्ण,
	अणु 0x79, 0x0E पूर्ण,
	अणु 0x7a, 0x0F पूर्ण,
	अणु 0x7b, 0x0C पूर्ण,
	अणु 0x7c, 0x0D पूर्ण,
	अणु 0x7d, 0x06 पूर्ण,
	अणु 0x7e, 0x02 पूर्ण,
	अणु 0x7f, 0x07 पूर्ण,
	अणु 0x80, 0x02 पूर्ण,
	अणु 0x81, 0x02 पूर्ण,
	अणु 0x82, 0x02 पूर्ण,
	अणु 0x83, 0x02 पूर्ण,
	अणु 0x84, 0x02 पूर्ण,
	अणु 0x85, 0x02 पूर्ण,
	अणु 0x86, 0x02 पूर्ण,
	अणु 0x87, 0x02 पूर्ण,
	अणु 0x88, 0x02 पूर्ण,
	अणु 0x89, 0x02 पूर्ण,
	अणु 0x8A, 0x02 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा ltk050h3146w_cmd page4_cmds[] = अणु
	अणु 0x70, 0x00 पूर्ण,
	अणु 0x71, 0x00 पूर्ण,
	अणु 0x82, 0x0F पूर्ण, /* VGH_MOD clamp level=15v */
	अणु 0x84, 0x0F पूर्ण, /* VGH clamp level 15V */
	अणु 0x85, 0x0D पूर्ण, /* VGL clamp level (-10V) */
	अणु 0x32, 0xAC पूर्ण,
	अणु 0x8C, 0x80 पूर्ण,
	अणु 0x3C, 0xF5 पूर्ण,
	अणु 0xB5, 0x07 पूर्ण, /* GAMMA OP */
	अणु 0x31, 0x45 पूर्ण, /* SOURCE OP */
	अणु 0x3A, 0x24 पूर्ण, /* PS_EN OFF */
	अणु 0x88, 0x33 पूर्ण, /* LVD */
पूर्ण;

अटल अंतरभूत
काष्ठा ltk050h3146w *panel_to_ltk050h3146w(काष्ठा drm_panel *panel)
अणु
	वापस container_of(panel, काष्ठा ltk050h3146w, panel);
पूर्ण

#घोषणा dsi_dcs_ग_लिखो_seq(dsi, cmd, seq...) करो अणु			\
		अटल स्थिर u8 b[] = अणु cmd, seq पूर्ण;			\
		पूर्णांक ret;						\
		ret = mipi_dsi_dcs_ग_लिखो_buffer(dsi, b, ARRAY_SIZE(b));	\
		अगर (ret < 0)						\
			वापस ret;					\
	पूर्ण जबतक (0)

अटल पूर्णांक ltk050h3146w_init_sequence(काष्ठा ltk050h3146w *ctx)
अणु
	काष्ठा mipi_dsi_device *dsi = to_mipi_dsi_device(ctx->dev);
	पूर्णांक ret;

	/*
	 * Init sequence was supplied by the panel venकरोr without much
	 * करोcumentation.
	 */
	dsi_dcs_ग_लिखो_seq(dsi, 0xdf, 0x93, 0x65, 0xf8);
	dsi_dcs_ग_लिखो_seq(dsi, 0xb0, 0x01, 0x03, 0x02, 0x00, 0x64, 0x06,
			  0x01);
	dsi_dcs_ग_लिखो_seq(dsi, 0xb2, 0x00, 0xb5);
	dsi_dcs_ग_लिखो_seq(dsi, 0xb3, 0x00, 0xb5);
	dsi_dcs_ग_लिखो_seq(dsi, 0xb7, 0x00, 0xbf, 0x00, 0x00, 0xbf, 0x00);

	dsi_dcs_ग_लिखो_seq(dsi, 0xb9, 0x00, 0xc4, 0x23, 0x07);
	dsi_dcs_ग_लिखो_seq(dsi, 0xbb, 0x02, 0x01, 0x24, 0x00, 0x28, 0x0f,
			  0x28, 0x04, 0xcc, 0xcc, 0xcc);
	dsi_dcs_ग_लिखो_seq(dsi, 0xbc, 0x0f, 0x04);
	dsi_dcs_ग_लिखो_seq(dsi, 0xbe, 0x1e, 0xf2);
	dsi_dcs_ग_लिखो_seq(dsi, 0xc0, 0x26, 0x03);
	dsi_dcs_ग_लिखो_seq(dsi, 0xc1, 0x00, 0x12);
	dsi_dcs_ग_लिखो_seq(dsi, 0xc3, 0x04, 0x02, 0x02, 0x76, 0x01, 0x80,
			  0x80);
	dsi_dcs_ग_लिखो_seq(dsi, 0xc4, 0x24, 0x80, 0xb4, 0x81, 0x12, 0x0f,
			  0x16, 0x00, 0x00);
	dsi_dcs_ग_लिखो_seq(dsi, 0xc8, 0x7f, 0x72, 0x67, 0x5d, 0x5d, 0x50,
			  0x56, 0x41, 0x59, 0x57, 0x55, 0x70, 0x5b, 0x5f,
			  0x4f, 0x47, 0x38, 0x23, 0x08, 0x7f, 0x72, 0x67,
			  0x5d, 0x5d, 0x50, 0x56, 0x41, 0x59, 0x57, 0x55,
			  0x70, 0x5b, 0x5f, 0x4f, 0x47, 0x38, 0x23, 0x08);
	dsi_dcs_ग_लिखो_seq(dsi, 0xd0, 0x1e, 0x1f, 0x57, 0x58, 0x48, 0x4a,
			  0x44, 0x46, 0x40, 0x1f, 0x42, 0x1f, 0x1f, 0x1f,
			  0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f);
	dsi_dcs_ग_लिखो_seq(dsi, 0xd1, 0x1e, 0x1f, 0x57, 0x58, 0x49, 0x4b,
			  0x45, 0x47, 0x41, 0x1f, 0x43, 0x1f, 0x1f, 0x1f,
			  0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f);
	dsi_dcs_ग_लिखो_seq(dsi, 0xd2, 0x1f, 0x1e, 0x17, 0x18, 0x07, 0x05,
			  0x0b, 0x09, 0x03, 0x1f, 0x01, 0x1f, 0x1f, 0x1f,
			  0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f);
	dsi_dcs_ग_लिखो_seq(dsi, 0xd3, 0x1f, 0x1e, 0x17, 0x18, 0x06, 0x04,
			  0x0a, 0x08, 0x02, 0x1f, 0x00, 0x1f, 0x1f, 0x1f,
			  0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f);
	dsi_dcs_ग_लिखो_seq(dsi, 0xd4, 0x00, 0x00, 0x00, 0x0c, 0x06, 0x20,
			  0x01, 0x02, 0x00, 0x60, 0x15, 0xb0, 0x30, 0x03,
			  0x04, 0x00, 0x60, 0x72, 0x0a, 0x00, 0x60, 0x08);
	dsi_dcs_ग_लिखो_seq(dsi, 0xd5, 0x00, 0x06, 0x06, 0x00, 0x30, 0x00,
			  0x00, 0x00, 0x00, 0x00, 0xbc, 0x50, 0x00, 0x05,
			  0x21, 0x00, 0x60);
	dsi_dcs_ग_लिखो_seq(dsi, 0xdd, 0x2c, 0xa3, 0x00);
	dsi_dcs_ग_लिखो_seq(dsi, 0xde, 0x02);
	dsi_dcs_ग_लिखो_seq(dsi, 0xb2, 0x32, 0x1c);
	dsi_dcs_ग_लिखो_seq(dsi, 0xb7, 0x3b, 0x70, 0x00, 0x04);
	dsi_dcs_ग_लिखो_seq(dsi, 0xc1, 0x11);
	dsi_dcs_ग_लिखो_seq(dsi, 0xbb, 0x21, 0x22, 0x23, 0x24, 0x36, 0x37);
	dsi_dcs_ग_लिखो_seq(dsi, 0xc2, 0x20, 0x38, 0x1e, 0x84);
	dsi_dcs_ग_लिखो_seq(dsi, 0xde, 0x00);

	ret = mipi_dsi_dcs_set_tear_on(dsi, 1);
	अगर (ret < 0) अणु
		dev_err(ctx->dev, "failed to set tear on: %d\n", ret);
		वापस ret;
	पूर्ण

	msleep(60);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा drm_display_mode ltk050h3146w_mode = अणु
	.hdisplay	= 720,
	.hsync_start	= 720 + 42,
	.hsync_end	= 720 + 42 + 8,
	.htotal		= 720 + 42 + 8 + 42,
	.vdisplay	= 1280,
	.vsync_start	= 1280 + 12,
	.vsync_end	= 1280 + 12 + 4,
	.vtotal		= 1280 + 12 + 4 + 18,
	.घड़ी		= 64018,
	.width_mm	= 62,
	.height_mm	= 110,
पूर्ण;

अटल स्थिर काष्ठा ltk050h3146w_desc ltk050h3146w_data = अणु
	.mode = &ltk050h3146w_mode,
	.init = ltk050h3146w_init_sequence,
पूर्ण;

अटल पूर्णांक ltk050h3146w_a2_select_page(काष्ठा ltk050h3146w *ctx, पूर्णांक page)
अणु
	काष्ठा mipi_dsi_device *dsi = to_mipi_dsi_device(ctx->dev);
	u8 d[3] = अणु 0x98, 0x81, page पूर्ण;

	वापस mipi_dsi_dcs_ग_लिखो(dsi, 0xff, d, ARRAY_SIZE(d));
पूर्ण

अटल पूर्णांक ltk050h3146w_a2_ग_लिखो_page(काष्ठा ltk050h3146w *ctx, पूर्णांक page,
				      स्थिर काष्ठा ltk050h3146w_cmd *cmds,
				      पूर्णांक num)
अणु
	काष्ठा mipi_dsi_device *dsi = to_mipi_dsi_device(ctx->dev);
	पूर्णांक i, ret;

	ret = ltk050h3146w_a2_select_page(ctx, page);
	अगर (ret < 0) अणु
		dev_err(ctx->dev, "failed to select page %d: %d\n", page, ret);
		वापस ret;
	पूर्ण

	क्रम (i = 0; i < num; i++) अणु
		ret = mipi_dsi_generic_ग_लिखो(dsi, &cmds[i],
					     माप(काष्ठा ltk050h3146w_cmd));
		अगर (ret < 0) अणु
			dev_err(ctx->dev, "failed to write page %d init cmds: %d\n", page, ret);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ltk050h3146w_a2_init_sequence(काष्ठा ltk050h3146w *ctx)
अणु
	काष्ठा mipi_dsi_device *dsi = to_mipi_dsi_device(ctx->dev);
	पूर्णांक ret;

	/*
	 * Init sequence was supplied by the panel venकरोr without much
	 * करोcumentation.
	 */
	ret = ltk050h3146w_a2_ग_लिखो_page(ctx, 3, page3_cmds,
					 ARRAY_SIZE(page3_cmds));
	अगर (ret < 0)
		वापस ret;

	ret = ltk050h3146w_a2_ग_लिखो_page(ctx, 4, page4_cmds,
					 ARRAY_SIZE(page4_cmds));
	अगर (ret < 0)
		वापस ret;

	ret = ltk050h3146w_a2_ग_लिखो_page(ctx, 1, page1_cmds,
					 ARRAY_SIZE(page1_cmds));
	अगर (ret < 0)
		वापस ret;

	ret = ltk050h3146w_a2_select_page(ctx, 0);
	अगर (ret < 0) अणु
		dev_err(ctx->dev, "failed to select page 0: %d\n", ret);
		वापस ret;
	पूर्ण

	/* venकरोr code called this without param, where there should be one */
	ret = mipi_dsi_dcs_set_tear_on(dsi, 0);
	अगर (ret < 0) अणु
		dev_err(ctx->dev, "failed to set tear on: %d\n", ret);
		वापस ret;
	पूर्ण

	msleep(60);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा drm_display_mode ltk050h3146w_a2_mode = अणु
	.hdisplay	= 720,
	.hsync_start	= 720 + 42,
	.hsync_end	= 720 + 42 + 10,
	.htotal		= 720 + 42 + 10 + 60,
	.vdisplay	= 1280,
	.vsync_start	= 1280 + 18,
	.vsync_end	= 1280 + 18 + 4,
	.vtotal		= 1280 + 18 + 4 + 12,
	.घड़ी		= 65595,
	.width_mm	= 62,
	.height_mm	= 110,
पूर्ण;

अटल स्थिर काष्ठा ltk050h3146w_desc ltk050h3146w_a2_data = अणु
	.mode = &ltk050h3146w_a2_mode,
	.init = ltk050h3146w_a2_init_sequence,
पूर्ण;

अटल पूर्णांक ltk050h3146w_unprepare(काष्ठा drm_panel *panel)
अणु
	काष्ठा ltk050h3146w *ctx = panel_to_ltk050h3146w(panel);
	काष्ठा mipi_dsi_device *dsi = to_mipi_dsi_device(ctx->dev);
	पूर्णांक ret;

	अगर (!ctx->prepared)
		वापस 0;

	ret = mipi_dsi_dcs_set_display_off(dsi);
	अगर (ret < 0) अणु
		dev_err(ctx->dev, "failed to set display off: %d\n", ret);
		वापस ret;
	पूर्ण

	mipi_dsi_dcs_enter_sleep_mode(dsi);
	अगर (ret < 0) अणु
		dev_err(ctx->dev, "failed to enter sleep mode: %d\n", ret);
		वापस ret;
	पूर्ण

	regulator_disable(ctx->iovcc);
	regulator_disable(ctx->vci);

	ctx->prepared = false;

	वापस 0;
पूर्ण

अटल पूर्णांक ltk050h3146w_prepare(काष्ठा drm_panel *panel)
अणु
	काष्ठा ltk050h3146w *ctx = panel_to_ltk050h3146w(panel);
	काष्ठा mipi_dsi_device *dsi = to_mipi_dsi_device(ctx->dev);
	पूर्णांक ret;

	अगर (ctx->prepared)
		वापस 0;

	dev_dbg(ctx->dev, "Resetting the panel\n");
	ret = regulator_enable(ctx->vci);
	अगर (ret < 0) अणु
		dev_err(ctx->dev, "Failed to enable vci supply: %d\n", ret);
		वापस ret;
	पूर्ण
	ret = regulator_enable(ctx->iovcc);
	अगर (ret < 0) अणु
		dev_err(ctx->dev, "Failed to enable iovcc supply: %d\n", ret);
		जाओ disable_vci;
	पूर्ण

	gpiod_set_value_cansleep(ctx->reset_gpio, 1);
	usleep_range(5000, 6000);
	gpiod_set_value_cansleep(ctx->reset_gpio, 0);
	msleep(20);

	ret = ctx->panel_desc->init(ctx);
	अगर (ret < 0) अणु
		dev_err(ctx->dev, "Panel init sequence failed: %d\n", ret);
		जाओ disable_iovcc;
	पूर्ण

	ret = mipi_dsi_dcs_निकास_sleep_mode(dsi);
	अगर (ret < 0) अणु
		dev_err(ctx->dev, "Failed to exit sleep mode: %d\n", ret);
		जाओ disable_iovcc;
	पूर्ण

	/* T9: 120ms */
	msleep(120);

	ret = mipi_dsi_dcs_set_display_on(dsi);
	अगर (ret < 0) अणु
		dev_err(ctx->dev, "Failed to set display on: %d\n", ret);
		जाओ disable_iovcc;
	पूर्ण

	msleep(50);

	ctx->prepared = true;

	वापस 0;

disable_iovcc:
	regulator_disable(ctx->iovcc);
disable_vci:
	regulator_disable(ctx->vci);
	वापस ret;
पूर्ण

अटल पूर्णांक ltk050h3146w_get_modes(काष्ठा drm_panel *panel,
				  काष्ठा drm_connector *connector)
अणु
	काष्ठा ltk050h3146w *ctx = panel_to_ltk050h3146w(panel);
	काष्ठा drm_display_mode *mode;

	mode = drm_mode_duplicate(connector->dev, ctx->panel_desc->mode);
	अगर (!mode)
		वापस -ENOMEM;

	drm_mode_set_name(mode);

	mode->type = DRM_MODE_TYPE_DRIVER | DRM_MODE_TYPE_PREFERRED;
	connector->display_info.width_mm = mode->width_mm;
	connector->display_info.height_mm = mode->height_mm;
	drm_mode_probed_add(connector, mode);

	वापस 1;
पूर्ण

अटल स्थिर काष्ठा drm_panel_funcs ltk050h3146w_funcs = अणु
	.unprepare	= ltk050h3146w_unprepare,
	.prepare	= ltk050h3146w_prepare,
	.get_modes	= ltk050h3146w_get_modes,
पूर्ण;

अटल पूर्णांक ltk050h3146w_probe(काष्ठा mipi_dsi_device *dsi)
अणु
	काष्ठा device *dev = &dsi->dev;
	काष्ठा ltk050h3146w *ctx;
	पूर्णांक ret;

	ctx = devm_kzalloc(dev, माप(*ctx), GFP_KERNEL);
	अगर (!ctx)
		वापस -ENOMEM;

	ctx->panel_desc = of_device_get_match_data(dev);
	अगर (!ctx->panel_desc)
		वापस -EINVAL;

	ctx->reset_gpio = devm_gpiod_get_optional(dev, "reset", GPIOD_OUT_LOW);
	अगर (IS_ERR(ctx->reset_gpio)) अणु
		dev_err(dev, "cannot get reset gpio\n");
		वापस PTR_ERR(ctx->reset_gpio);
	पूर्ण

	ctx->vci = devm_regulator_get(dev, "vci");
	अगर (IS_ERR(ctx->vci)) अणु
		ret = PTR_ERR(ctx->vci);
		अगर (ret != -EPROBE_DEFER)
			dev_err(dev, "Failed to request vci regulator: %d\n", ret);
		वापस ret;
	पूर्ण

	ctx->iovcc = devm_regulator_get(dev, "iovcc");
	अगर (IS_ERR(ctx->iovcc)) अणु
		ret = PTR_ERR(ctx->iovcc);
		अगर (ret != -EPROBE_DEFER)
			dev_err(dev, "Failed to request iovcc regulator: %d\n", ret);
		वापस ret;
	पूर्ण

	mipi_dsi_set_drvdata(dsi, ctx);

	ctx->dev = dev;

	dsi->lanes = 4;
	dsi->क्रमmat = MIPI_DSI_FMT_RGB888;
	dsi->mode_flags = MIPI_DSI_MODE_VIDEO | MIPI_DSI_MODE_VIDEO_BURST |
			  MIPI_DSI_MODE_LPM | MIPI_DSI_MODE_EOT_PACKET;

	drm_panel_init(&ctx->panel, &dsi->dev, &ltk050h3146w_funcs,
		       DRM_MODE_CONNECTOR_DSI);

	ret = drm_panel_of_backlight(&ctx->panel);
	अगर (ret)
		वापस ret;

	drm_panel_add(&ctx->panel);

	ret = mipi_dsi_attach(dsi);
	अगर (ret < 0) अणु
		dev_err(dev, "mipi_dsi_attach failed: %d\n", ret);
		drm_panel_हटाओ(&ctx->panel);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम ltk050h3146w_shutकरोwn(काष्ठा mipi_dsi_device *dsi)
अणु
	काष्ठा ltk050h3146w *ctx = mipi_dsi_get_drvdata(dsi);
	पूर्णांक ret;

	ret = drm_panel_unprepare(&ctx->panel);
	अगर (ret < 0)
		dev_err(&dsi->dev, "Failed to unprepare panel: %d\n", ret);

	ret = drm_panel_disable(&ctx->panel);
	अगर (ret < 0)
		dev_err(&dsi->dev, "Failed to disable panel: %d\n", ret);
पूर्ण

अटल पूर्णांक ltk050h3146w_हटाओ(काष्ठा mipi_dsi_device *dsi)
अणु
	काष्ठा ltk050h3146w *ctx = mipi_dsi_get_drvdata(dsi);
	पूर्णांक ret;

	ltk050h3146w_shutकरोwn(dsi);

	ret = mipi_dsi_detach(dsi);
	अगर (ret < 0)
		dev_err(&dsi->dev, "Failed to detach from DSI host: %d\n", ret);

	drm_panel_हटाओ(&ctx->panel);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id ltk050h3146w_of_match[] = अणु
	अणु
		.compatible = "leadtek,ltk050h3146w",
		.data = &ltk050h3146w_data,
	पूर्ण,
	अणु
		.compatible = "leadtek,ltk050h3146w-a2",
		.data = &ltk050h3146w_a2_data,
	पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, ltk050h3146w_of_match);

अटल काष्ठा mipi_dsi_driver ltk050h3146w_driver = अणु
	.driver = अणु
		.name = "panel-leadtek-ltk050h3146w",
		.of_match_table = ltk050h3146w_of_match,
	पूर्ण,
	.probe	= ltk050h3146w_probe,
	.हटाओ = ltk050h3146w_हटाओ,
	.shutकरोwn = ltk050h3146w_shutकरोwn,
पूर्ण;
module_mipi_dsi_driver(ltk050h3146w_driver);

MODULE_AUTHOR("Heiko Stuebner <heiko.stuebner@theobroma-systems.com>");
MODULE_DESCRIPTION("DRM driver for Leadtek LTK050H3146W MIPI DSI panel");
MODULE_LICENSE("GPL v2");
