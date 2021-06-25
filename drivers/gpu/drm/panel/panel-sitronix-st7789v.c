<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2017 Free Electrons
 */

#समावेश <linux/delay.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/module.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/spi/spi.h>

#समावेश <video/mipi_display.h>

#समावेश <drm/drm_device.h>
#समावेश <drm/drm_modes.h>
#समावेश <drm/drm_panel.h>

#घोषणा ST7789V_COLMOD_RGB_FMT_18BITS		(6 << 4)
#घोषणा ST7789V_COLMOD_CTRL_FMT_18BITS		(6 << 0)

#घोषणा ST7789V_RAMCTRL_CMD		0xb0
#घोषणा ST7789V_RAMCTRL_RM_RGB			BIT(4)
#घोषणा ST7789V_RAMCTRL_DM_RGB			BIT(0)
#घोषणा ST7789V_RAMCTRL_MAGIC			(3 << 6)
#घोषणा ST7789V_RAMCTRL_EPF(n)			(((n) & 3) << 4)

#घोषणा ST7789V_RGBCTRL_CMD		0xb1
#घोषणा ST7789V_RGBCTRL_WO			BIT(7)
#घोषणा ST7789V_RGBCTRL_RCM(n)			(((n) & 3) << 5)
#घोषणा ST7789V_RGBCTRL_VSYNC_HIGH		BIT(3)
#घोषणा ST7789V_RGBCTRL_HSYNC_HIGH		BIT(2)
#घोषणा ST7789V_RGBCTRL_PCLK_HIGH		BIT(1)
#घोषणा ST7789V_RGBCTRL_VBP(n)			((n) & 0x7f)
#घोषणा ST7789V_RGBCTRL_HBP(n)			((n) & 0x1f)

#घोषणा ST7789V_PORCTRL_CMD		0xb2
#घोषणा ST7789V_PORCTRL_IDLE_BP(n)		(((n) & 0xf) << 4)
#घोषणा ST7789V_PORCTRL_IDLE_FP(n)		((n) & 0xf)
#घोषणा ST7789V_PORCTRL_PARTIAL_BP(n)		(((n) & 0xf) << 4)
#घोषणा ST7789V_PORCTRL_PARTIAL_FP(n)		((n) & 0xf)

#घोषणा ST7789V_GCTRL_CMD		0xb7
#घोषणा ST7789V_GCTRL_VGHS(n)			(((n) & 7) << 4)
#घोषणा ST7789V_GCTRL_VGLS(n)			((n) & 7)

#घोषणा ST7789V_VCOMS_CMD		0xbb

#घोषणा ST7789V_LCMCTRL_CMD		0xc0
#घोषणा ST7789V_LCMCTRL_XBGR			BIT(5)
#घोषणा ST7789V_LCMCTRL_XMX			BIT(3)
#घोषणा ST7789V_LCMCTRL_XMH			BIT(2)

#घोषणा ST7789V_VDVVRHEN_CMD		0xc2
#घोषणा ST7789V_VDVVRHEN_CMDEN			BIT(0)

#घोषणा ST7789V_VRHS_CMD		0xc3

#घोषणा ST7789V_VDVS_CMD		0xc4

#घोषणा ST7789V_FRCTRL2_CMD		0xc6

#घोषणा ST7789V_PWCTRL1_CMD		0xd0
#घोषणा ST7789V_PWCTRL1_MAGIC			0xa4
#घोषणा ST7789V_PWCTRL1_AVDD(n)			(((n) & 3) << 6)
#घोषणा ST7789V_PWCTRL1_AVCL(n)			(((n) & 3) << 4)
#घोषणा ST7789V_PWCTRL1_VDS(n)			((n) & 3)

#घोषणा ST7789V_PVGAMCTRL_CMD		0xe0
#घोषणा ST7789V_PVGAMCTRL_JP0(n)		(((n) & 3) << 4)
#घोषणा ST7789V_PVGAMCTRL_JP1(n)		(((n) & 3) << 4)
#घोषणा ST7789V_PVGAMCTRL_VP0(n)		((n) & 0xf)
#घोषणा ST7789V_PVGAMCTRL_VP1(n)		((n) & 0x3f)
#घोषणा ST7789V_PVGAMCTRL_VP2(n)		((n) & 0x3f)
#घोषणा ST7789V_PVGAMCTRL_VP4(n)		((n) & 0x1f)
#घोषणा ST7789V_PVGAMCTRL_VP6(n)		((n) & 0x1f)
#घोषणा ST7789V_PVGAMCTRL_VP13(n)		((n) & 0xf)
#घोषणा ST7789V_PVGAMCTRL_VP20(n)		((n) & 0x7f)
#घोषणा ST7789V_PVGAMCTRL_VP27(n)		((n) & 7)
#घोषणा ST7789V_PVGAMCTRL_VP36(n)		(((n) & 7) << 4)
#घोषणा ST7789V_PVGAMCTRL_VP43(n)		((n) & 0x7f)
#घोषणा ST7789V_PVGAMCTRL_VP50(n)		((n) & 0xf)
#घोषणा ST7789V_PVGAMCTRL_VP57(n)		((n) & 0x1f)
#घोषणा ST7789V_PVGAMCTRL_VP59(n)		((n) & 0x1f)
#घोषणा ST7789V_PVGAMCTRL_VP61(n)		((n) & 0x3f)
#घोषणा ST7789V_PVGAMCTRL_VP62(n)		((n) & 0x3f)
#घोषणा ST7789V_PVGAMCTRL_VP63(n)		(((n) & 0xf) << 4)

#घोषणा ST7789V_NVGAMCTRL_CMD		0xe1
#घोषणा ST7789V_NVGAMCTRL_JN0(n)		(((n) & 3) << 4)
#घोषणा ST7789V_NVGAMCTRL_JN1(n)		(((n) & 3) << 4)
#घोषणा ST7789V_NVGAMCTRL_VN0(n)		((n) & 0xf)
#घोषणा ST7789V_NVGAMCTRL_VN1(n)		((n) & 0x3f)
#घोषणा ST7789V_NVGAMCTRL_VN2(n)		((n) & 0x3f)
#घोषणा ST7789V_NVGAMCTRL_VN4(n)		((n) & 0x1f)
#घोषणा ST7789V_NVGAMCTRL_VN6(n)		((n) & 0x1f)
#घोषणा ST7789V_NVGAMCTRL_VN13(n)		((n) & 0xf)
#घोषणा ST7789V_NVGAMCTRL_VN20(n)		((n) & 0x7f)
#घोषणा ST7789V_NVGAMCTRL_VN27(n)		((n) & 7)
#घोषणा ST7789V_NVGAMCTRL_VN36(n)		(((n) & 7) << 4)
#घोषणा ST7789V_NVGAMCTRL_VN43(n)		((n) & 0x7f)
#घोषणा ST7789V_NVGAMCTRL_VN50(n)		((n) & 0xf)
#घोषणा ST7789V_NVGAMCTRL_VN57(n)		((n) & 0x1f)
#घोषणा ST7789V_NVGAMCTRL_VN59(n)		((n) & 0x1f)
#घोषणा ST7789V_NVGAMCTRL_VN61(n)		((n) & 0x3f)
#घोषणा ST7789V_NVGAMCTRL_VN62(n)		((n) & 0x3f)
#घोषणा ST7789V_NVGAMCTRL_VN63(n)		(((n) & 0xf) << 4)

#घोषणा ST7789V_TEST(val, func)			\
	करो अणु					\
		अगर ((val = (func)))		\
			वापस val;		\
	पूर्ण जबतक (0)

काष्ठा st7789v अणु
	काष्ठा drm_panel panel;
	काष्ठा spi_device *spi;
	काष्ठा gpio_desc *reset;
	काष्ठा regulator *घातer;
पूर्ण;

क्रमागत st7789v_prefix अणु
	ST7789V_COMMAND = 0,
	ST7789V_DATA = 1,
पूर्ण;

अटल अंतरभूत काष्ठा st7789v *panel_to_st7789v(काष्ठा drm_panel *panel)
अणु
	वापस container_of(panel, काष्ठा st7789v, panel);
पूर्ण

अटल पूर्णांक st7789v_spi_ग_लिखो(काष्ठा st7789v *ctx, क्रमागत st7789v_prefix prefix,
			     u8 data)
अणु
	काष्ठा spi_transfer xfer = अणु पूर्ण;
	काष्ठा spi_message msg;
	u16 txbuf = ((prefix & 1) << 8) | data;

	spi_message_init(&msg);

	xfer.tx_buf = &txbuf;
	xfer.bits_per_word = 9;
	xfer.len = माप(txbuf);

	spi_message_add_tail(&xfer, &msg);
	वापस spi_sync(ctx->spi, &msg);
पूर्ण

अटल पूर्णांक st7789v_ग_लिखो_command(काष्ठा st7789v *ctx, u8 cmd)
अणु
	वापस st7789v_spi_ग_लिखो(ctx, ST7789V_COMMAND, cmd);
पूर्ण

अटल पूर्णांक st7789v_ग_लिखो_data(काष्ठा st7789v *ctx, u8 cmd)
अणु
	वापस st7789v_spi_ग_लिखो(ctx, ST7789V_DATA, cmd);
पूर्ण

अटल स्थिर काष्ठा drm_display_mode शेष_mode = अणु
	.घड़ी = 7000,
	.hdisplay = 240,
	.hsync_start = 240 + 38,
	.hsync_end = 240 + 38 + 10,
	.htotal = 240 + 38 + 10 + 10,
	.vdisplay = 320,
	.vsync_start = 320 + 8,
	.vsync_end = 320 + 8 + 4,
	.vtotal = 320 + 8 + 4 + 4,
पूर्ण;

अटल पूर्णांक st7789v_get_modes(काष्ठा drm_panel *panel,
			     काष्ठा drm_connector *connector)
अणु
	काष्ठा drm_display_mode *mode;

	mode = drm_mode_duplicate(connector->dev, &शेष_mode);
	अगर (!mode) अणु
		dev_err(panel->dev, "failed to add mode %ux%ux@%u\n",
			शेष_mode.hdisplay, शेष_mode.vdisplay,
			drm_mode_vrefresh(&शेष_mode));
		वापस -ENOMEM;
	पूर्ण

	drm_mode_set_name(mode);

	mode->type = DRM_MODE_TYPE_DRIVER | DRM_MODE_TYPE_PREFERRED;
	drm_mode_probed_add(connector, mode);

	connector->display_info.width_mm = 61;
	connector->display_info.height_mm = 103;

	वापस 1;
पूर्ण

अटल पूर्णांक st7789v_prepare(काष्ठा drm_panel *panel)
अणु
	काष्ठा st7789v *ctx = panel_to_st7789v(panel);
	पूर्णांक ret;

	ret = regulator_enable(ctx->घातer);
	अगर (ret)
		वापस ret;

	gpiod_set_value(ctx->reset, 1);
	msleep(30);
	gpiod_set_value(ctx->reset, 0);
	msleep(120);

	ST7789V_TEST(ret, st7789v_ग_लिखो_command(ctx, MIPI_DCS_EXIT_SLEEP_MODE));

	/* We need to रुको 120ms after a sleep out command */
	msleep(120);

	ST7789V_TEST(ret, st7789v_ग_लिखो_command(ctx,
						MIPI_DCS_SET_ADDRESS_MODE));
	ST7789V_TEST(ret, st7789v_ग_लिखो_data(ctx, 0));

	ST7789V_TEST(ret, st7789v_ग_लिखो_command(ctx,
						MIPI_DCS_SET_PIXEL_FORMAT));
	ST7789V_TEST(ret, st7789v_ग_लिखो_data(ctx,
					     (MIPI_DCS_PIXEL_FMT_18BIT << 4) |
					     (MIPI_DCS_PIXEL_FMT_18BIT)));

	ST7789V_TEST(ret, st7789v_ग_लिखो_command(ctx, ST7789V_PORCTRL_CMD));
	ST7789V_TEST(ret, st7789v_ग_लिखो_data(ctx, 0xc));
	ST7789V_TEST(ret, st7789v_ग_लिखो_data(ctx, 0xc));
	ST7789V_TEST(ret, st7789v_ग_लिखो_data(ctx, 0));
	ST7789V_TEST(ret, st7789v_ग_लिखो_data(ctx, ST7789V_PORCTRL_IDLE_BP(3) |
					     ST7789V_PORCTRL_IDLE_FP(3)));
	ST7789V_TEST(ret, st7789v_ग_लिखो_data(ctx,
					     ST7789V_PORCTRL_PARTIAL_BP(3) |
					     ST7789V_PORCTRL_PARTIAL_FP(3)));

	ST7789V_TEST(ret, st7789v_ग_लिखो_command(ctx, ST7789V_GCTRL_CMD));
	ST7789V_TEST(ret, st7789v_ग_लिखो_data(ctx, ST7789V_GCTRL_VGLS(5) |
					     ST7789V_GCTRL_VGHS(3)));

	ST7789V_TEST(ret, st7789v_ग_लिखो_command(ctx, ST7789V_VCOMS_CMD));
	ST7789V_TEST(ret, st7789v_ग_लिखो_data(ctx, 0x2b));

	ST7789V_TEST(ret, st7789v_ग_लिखो_command(ctx, ST7789V_LCMCTRL_CMD));
	ST7789V_TEST(ret, st7789v_ग_लिखो_data(ctx, ST7789V_LCMCTRL_XMH |
					     ST7789V_LCMCTRL_XMX |
					     ST7789V_LCMCTRL_XBGR));

	ST7789V_TEST(ret, st7789v_ग_लिखो_command(ctx, ST7789V_VDVVRHEN_CMD));
	ST7789V_TEST(ret, st7789v_ग_लिखो_data(ctx, ST7789V_VDVVRHEN_CMDEN));

	ST7789V_TEST(ret, st7789v_ग_लिखो_command(ctx, ST7789V_VRHS_CMD));
	ST7789V_TEST(ret, st7789v_ग_लिखो_data(ctx, 0xf));

	ST7789V_TEST(ret, st7789v_ग_लिखो_command(ctx, ST7789V_VDVS_CMD));
	ST7789V_TEST(ret, st7789v_ग_लिखो_data(ctx, 0x20));

	ST7789V_TEST(ret, st7789v_ग_लिखो_command(ctx, ST7789V_FRCTRL2_CMD));
	ST7789V_TEST(ret, st7789v_ग_लिखो_data(ctx, 0xf));

	ST7789V_TEST(ret, st7789v_ग_लिखो_command(ctx, ST7789V_PWCTRL1_CMD));
	ST7789V_TEST(ret, st7789v_ग_लिखो_data(ctx, ST7789V_PWCTRL1_MAGIC));
	ST7789V_TEST(ret, st7789v_ग_लिखो_data(ctx, ST7789V_PWCTRL1_AVDD(2) |
					     ST7789V_PWCTRL1_AVCL(2) |
					     ST7789V_PWCTRL1_VDS(1)));

	ST7789V_TEST(ret, st7789v_ग_लिखो_command(ctx, ST7789V_PVGAMCTRL_CMD));
	ST7789V_TEST(ret, st7789v_ग_लिखो_data(ctx, ST7789V_PVGAMCTRL_VP63(0xd)));
	ST7789V_TEST(ret, st7789v_ग_लिखो_data(ctx, ST7789V_PVGAMCTRL_VP1(0xca)));
	ST7789V_TEST(ret, st7789v_ग_लिखो_data(ctx, ST7789V_PVGAMCTRL_VP2(0xe)));
	ST7789V_TEST(ret, st7789v_ग_लिखो_data(ctx, ST7789V_PVGAMCTRL_VP4(8)));
	ST7789V_TEST(ret, st7789v_ग_लिखो_data(ctx, ST7789V_PVGAMCTRL_VP6(9)));
	ST7789V_TEST(ret, st7789v_ग_लिखो_data(ctx, ST7789V_PVGAMCTRL_VP13(7)));
	ST7789V_TEST(ret, st7789v_ग_लिखो_data(ctx, ST7789V_PVGAMCTRL_VP20(0x2d)));
	ST7789V_TEST(ret, st7789v_ग_लिखो_data(ctx, ST7789V_PVGAMCTRL_VP27(0xb) |
					     ST7789V_PVGAMCTRL_VP36(3)));
	ST7789V_TEST(ret, st7789v_ग_लिखो_data(ctx, ST7789V_PVGAMCTRL_VP43(0x3d)));
	ST7789V_TEST(ret, st7789v_ग_लिखो_data(ctx, ST7789V_PVGAMCTRL_JP1(3) |
					     ST7789V_PVGAMCTRL_VP50(4)));
	ST7789V_TEST(ret, st7789v_ग_लिखो_data(ctx, ST7789V_PVGAMCTRL_VP57(0xa)));
	ST7789V_TEST(ret, st7789v_ग_लिखो_data(ctx, ST7789V_PVGAMCTRL_VP59(0xa)));
	ST7789V_TEST(ret, st7789v_ग_लिखो_data(ctx, ST7789V_PVGAMCTRL_VP61(0x1b)));
	ST7789V_TEST(ret, st7789v_ग_लिखो_data(ctx, ST7789V_PVGAMCTRL_VP62(0x28)));

	ST7789V_TEST(ret, st7789v_ग_लिखो_command(ctx, ST7789V_NVGAMCTRL_CMD));
	ST7789V_TEST(ret, st7789v_ग_लिखो_data(ctx, ST7789V_NVGAMCTRL_VN63(0xd)));
	ST7789V_TEST(ret, st7789v_ग_लिखो_data(ctx, ST7789V_NVGAMCTRL_VN1(0xca)));
	ST7789V_TEST(ret, st7789v_ग_लिखो_data(ctx, ST7789V_NVGAMCTRL_VN2(0xf)));
	ST7789V_TEST(ret, st7789v_ग_लिखो_data(ctx, ST7789V_NVGAMCTRL_VN4(8)));
	ST7789V_TEST(ret, st7789v_ग_लिखो_data(ctx, ST7789V_NVGAMCTRL_VN6(8)));
	ST7789V_TEST(ret, st7789v_ग_लिखो_data(ctx, ST7789V_NVGAMCTRL_VN13(7)));
	ST7789V_TEST(ret, st7789v_ग_लिखो_data(ctx, ST7789V_NVGAMCTRL_VN20(0x2e)));
	ST7789V_TEST(ret, st7789v_ग_लिखो_data(ctx, ST7789V_NVGAMCTRL_VN27(0xc) |
					     ST7789V_NVGAMCTRL_VN36(5)));
	ST7789V_TEST(ret, st7789v_ग_लिखो_data(ctx, ST7789V_NVGAMCTRL_VN43(0x40)));
	ST7789V_TEST(ret, st7789v_ग_लिखो_data(ctx, ST7789V_NVGAMCTRL_JN1(3) |
					     ST7789V_NVGAMCTRL_VN50(4)));
	ST7789V_TEST(ret, st7789v_ग_लिखो_data(ctx, ST7789V_NVGAMCTRL_VN57(9)));
	ST7789V_TEST(ret, st7789v_ग_लिखो_data(ctx, ST7789V_NVGAMCTRL_VN59(0xb)));
	ST7789V_TEST(ret, st7789v_ग_लिखो_data(ctx, ST7789V_NVGAMCTRL_VN61(0x1b)));
	ST7789V_TEST(ret, st7789v_ग_लिखो_data(ctx, ST7789V_NVGAMCTRL_VN62(0x28)));

	ST7789V_TEST(ret, st7789v_ग_लिखो_command(ctx, MIPI_DCS_ENTER_INVERT_MODE));

	ST7789V_TEST(ret, st7789v_ग_लिखो_command(ctx, ST7789V_RAMCTRL_CMD));
	ST7789V_TEST(ret, st7789v_ग_लिखो_data(ctx, ST7789V_RAMCTRL_DM_RGB |
					     ST7789V_RAMCTRL_RM_RGB));
	ST7789V_TEST(ret, st7789v_ग_लिखो_data(ctx, ST7789V_RAMCTRL_EPF(3) |
					     ST7789V_RAMCTRL_MAGIC));

	ST7789V_TEST(ret, st7789v_ग_लिखो_command(ctx, ST7789V_RGBCTRL_CMD));
	ST7789V_TEST(ret, st7789v_ग_लिखो_data(ctx, ST7789V_RGBCTRL_WO |
					     ST7789V_RGBCTRL_RCM(2) |
					     ST7789V_RGBCTRL_VSYNC_HIGH |
					     ST7789V_RGBCTRL_HSYNC_HIGH |
					     ST7789V_RGBCTRL_PCLK_HIGH));
	ST7789V_TEST(ret, st7789v_ग_लिखो_data(ctx, ST7789V_RGBCTRL_VBP(8)));
	ST7789V_TEST(ret, st7789v_ग_लिखो_data(ctx, ST7789V_RGBCTRL_HBP(20)));

	वापस 0;
पूर्ण

अटल पूर्णांक st7789v_enable(काष्ठा drm_panel *panel)
अणु
	काष्ठा st7789v *ctx = panel_to_st7789v(panel);

	वापस st7789v_ग_लिखो_command(ctx, MIPI_DCS_SET_DISPLAY_ON);
पूर्ण

अटल पूर्णांक st7789v_disable(काष्ठा drm_panel *panel)
अणु
	काष्ठा st7789v *ctx = panel_to_st7789v(panel);
	पूर्णांक ret;

	ST7789V_TEST(ret, st7789v_ग_लिखो_command(ctx, MIPI_DCS_SET_DISPLAY_OFF));

	वापस 0;
पूर्ण

अटल पूर्णांक st7789v_unprepare(काष्ठा drm_panel *panel)
अणु
	काष्ठा st7789v *ctx = panel_to_st7789v(panel);
	पूर्णांक ret;

	ST7789V_TEST(ret, st7789v_ग_लिखो_command(ctx, MIPI_DCS_ENTER_SLEEP_MODE));

	regulator_disable(ctx->घातer);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा drm_panel_funcs st7789v_drm_funcs = अणु
	.disable	= st7789v_disable,
	.enable		= st7789v_enable,
	.get_modes	= st7789v_get_modes,
	.prepare	= st7789v_prepare,
	.unprepare	= st7789v_unprepare,
पूर्ण;

अटल पूर्णांक st7789v_probe(काष्ठा spi_device *spi)
अणु
	काष्ठा st7789v *ctx;
	पूर्णांक ret;

	ctx = devm_kzalloc(&spi->dev, माप(*ctx), GFP_KERNEL);
	अगर (!ctx)
		वापस -ENOMEM;

	spi_set_drvdata(spi, ctx);
	ctx->spi = spi;

	drm_panel_init(&ctx->panel, &spi->dev, &st7789v_drm_funcs,
		       DRM_MODE_CONNECTOR_DPI);

	ctx->घातer = devm_regulator_get(&spi->dev, "power");
	अगर (IS_ERR(ctx->घातer))
		वापस PTR_ERR(ctx->घातer);

	ctx->reset = devm_gpiod_get(&spi->dev, "reset", GPIOD_OUT_LOW);
	अगर (IS_ERR(ctx->reset)) अणु
		dev_err(&spi->dev, "Couldn't get our reset line\n");
		वापस PTR_ERR(ctx->reset);
	पूर्ण

	ret = drm_panel_of_backlight(&ctx->panel);
	अगर (ret)
		वापस ret;

	drm_panel_add(&ctx->panel);

	वापस 0;
पूर्ण

अटल पूर्णांक st7789v_हटाओ(काष्ठा spi_device *spi)
अणु
	काष्ठा st7789v *ctx = spi_get_drvdata(spi);

	drm_panel_हटाओ(&ctx->panel);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id st7789v_of_match[] = अणु
	अणु .compatible = "sitronix,st7789v" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, st7789v_of_match);

अटल काष्ठा spi_driver st7789v_driver = अणु
	.probe = st7789v_probe,
	.हटाओ = st7789v_हटाओ,
	.driver = अणु
		.name = "st7789v",
		.of_match_table = st7789v_of_match,
	पूर्ण,
पूर्ण;
module_spi_driver(st7789v_driver);

MODULE_AUTHOR("Maxime Ripard <maxime.ripard@free-electrons.com>");
MODULE_DESCRIPTION("Sitronix st7789v LCD Driver");
MODULE_LICENSE("GPL v2");
