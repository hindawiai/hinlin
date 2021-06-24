<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2018, The Linux Foundation. All rights reserved.
 */

#समावेश <linux/backlight.h>
#समावेश <linux/delay.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_graph.h>
#समावेश <linux/pinctrl/consumer.h>
#समावेश <linux/regulator/consumer.h>

#समावेश <video/mipi_display.h>

#समावेश <drm/drm_mipi_dsi.h>
#समावेश <drm/drm_modes.h>
#समावेश <drm/drm_panel.h>

अटल स्थिर अक्षर * स्थिर regulator_names[] = अणु
	"vdda",
	"vdispp",
	"vdispn",
पूर्ण;

अटल अचिन्हित दीर्घ स्थिर regulator_enable_loads[] = अणु
	62000,
	100000,
	100000,
पूर्ण;

अटल अचिन्हित दीर्घ स्थिर regulator_disable_loads[] = अणु
	80,
	100,
	100,
पूर्ण;

काष्ठा cmd_set अणु
	u8 commands[4];
	u8 size;
पूर्ण;

काष्ठा nt35597_config अणु
	u32 width_mm;
	u32 height_mm;
	स्थिर अक्षर *panel_name;
	स्थिर काष्ठा cmd_set *panel_on_cmds;
	u32 num_on_cmds;
	स्थिर काष्ठा drm_display_mode *dm;
पूर्ण;

काष्ठा truly_nt35597 अणु
	काष्ठा device *dev;
	काष्ठा drm_panel panel;

	काष्ठा regulator_bulk_data supplies[ARRAY_SIZE(regulator_names)];

	काष्ठा gpio_desc *reset_gpio;
	काष्ठा gpio_desc *mode_gpio;

	काष्ठा backlight_device *backlight;

	काष्ठा mipi_dsi_device *dsi[2];

	स्थिर काष्ठा nt35597_config *config;
	bool prepared;
	bool enabled;
पूर्ण;

अटल अंतरभूत काष्ठा truly_nt35597 *panel_to_ctx(काष्ठा drm_panel *panel)
अणु
	वापस container_of(panel, काष्ठा truly_nt35597, panel);
पूर्ण

अटल स्थिर काष्ठा cmd_set qcom_2k_panel_magic_cmds[] = अणु
	/* CMD2_P0 */
	अणु अणु 0xff, 0x20 पूर्ण, 2 पूर्ण,
	अणु अणु 0xfb, 0x01 पूर्ण, 2 पूर्ण,
	अणु अणु 0x00, 0x01 पूर्ण, 2 पूर्ण,
	अणु अणु 0x01, 0x55 पूर्ण, 2 पूर्ण,
	अणु अणु 0x02, 0x45 पूर्ण, 2 पूर्ण,
	अणु अणु 0x05, 0x40 पूर्ण, 2 पूर्ण,
	अणु अणु 0x06, 0x19 पूर्ण, 2 पूर्ण,
	अणु अणु 0x07, 0x1e पूर्ण, 2 पूर्ण,
	अणु अणु 0x0b, 0x73 पूर्ण, 2 पूर्ण,
	अणु अणु 0x0c, 0x73 पूर्ण, 2 पूर्ण,
	अणु अणु 0x0e, 0xb0 पूर्ण, 2 पूर्ण,
	अणु अणु 0x0f, 0xae पूर्ण, 2 पूर्ण,
	अणु अणु 0x11, 0xb8 पूर्ण, 2 पूर्ण,
	अणु अणु 0x13, 0x00 पूर्ण, 2 पूर्ण,
	अणु अणु 0x58, 0x80 पूर्ण, 2 पूर्ण,
	अणु अणु 0x59, 0x01 पूर्ण, 2 पूर्ण,
	अणु अणु 0x5a, 0x00 पूर्ण, 2 पूर्ण,
	अणु अणु 0x5b, 0x01 पूर्ण, 2 पूर्ण,
	अणु अणु 0x5c, 0x80 पूर्ण, 2 पूर्ण,
	अणु अणु 0x5d, 0x81 पूर्ण, 2 पूर्ण,
	अणु अणु 0x5e, 0x00 पूर्ण, 2 पूर्ण,
	अणु अणु 0x5f, 0x01 पूर्ण, 2 पूर्ण,
	अणु अणु 0x72, 0x11 पूर्ण, 2 पूर्ण,
	अणु अणु 0x68, 0x03 पूर्ण, 2 पूर्ण,
	/* CMD2_P4 */
	अणु अणु 0xFF, 0x24 पूर्ण, 2 पूर्ण,
	अणु अणु 0xFB, 0x01 पूर्ण, 2 पूर्ण,
	अणु अणु 0x00, 0x1C पूर्ण, 2 पूर्ण,
	अणु अणु 0x01, 0x0B पूर्ण, 2 पूर्ण,
	अणु अणु 0x02, 0x0C पूर्ण, 2 पूर्ण,
	अणु अणु 0x03, 0x01 पूर्ण, 2 पूर्ण,
	अणु अणु 0x04, 0x0F पूर्ण, 2 पूर्ण,
	अणु अणु 0x05, 0x10 पूर्ण, 2 पूर्ण,
	अणु अणु 0x06, 0x10 पूर्ण, 2 पूर्ण,
	अणु अणु 0x07, 0x10 पूर्ण, 2 पूर्ण,
	अणु अणु 0x08, 0x89 पूर्ण, 2 पूर्ण,
	अणु अणु 0x09, 0x8A पूर्ण, 2 पूर्ण,
	अणु अणु 0x0A, 0x13 पूर्ण, 2 पूर्ण,
	अणु अणु 0x0B, 0x13 पूर्ण, 2 पूर्ण,
	अणु अणु 0x0C, 0x15 पूर्ण, 2 पूर्ण,
	अणु अणु 0x0D, 0x15 पूर्ण, 2 पूर्ण,
	अणु अणु 0x0E, 0x17 पूर्ण, 2 पूर्ण,
	अणु अणु 0x0F, 0x17 पूर्ण, 2 पूर्ण,
	अणु अणु 0x10, 0x1C पूर्ण, 2 पूर्ण,
	अणु अणु 0x11, 0x0B पूर्ण, 2 पूर्ण,
	अणु अणु 0x12, 0x0C पूर्ण, 2 पूर्ण,
	अणु अणु 0x13, 0x01 पूर्ण, 2 पूर्ण,
	अणु अणु 0x14, 0x0F पूर्ण, 2 पूर्ण,
	अणु अणु 0x15, 0x10 पूर्ण, 2 पूर्ण,
	अणु अणु 0x16, 0x10 पूर्ण, 2 पूर्ण,
	अणु अणु 0x17, 0x10 पूर्ण, 2 पूर्ण,
	अणु अणु 0x18, 0x89 पूर्ण, 2 पूर्ण,
	अणु अणु 0x19, 0x8A पूर्ण, 2 पूर्ण,
	अणु अणु 0x1A, 0x13 पूर्ण, 2 पूर्ण,
	अणु अणु 0x1B, 0x13 पूर्ण, 2 पूर्ण,
	अणु अणु 0x1C, 0x15 पूर्ण, 2 पूर्ण,
	अणु अणु 0x1D, 0x15 पूर्ण, 2 पूर्ण,
	अणु अणु 0x1E, 0x17 पूर्ण, 2 पूर्ण,
	अणु अणु 0x1F, 0x17 पूर्ण, 2 पूर्ण,
	/* STV */
	अणु अणु 0x20, 0x40 पूर्ण, 2 पूर्ण,
	अणु अणु 0x21, 0x01 पूर्ण, 2 पूर्ण,
	अणु अणु 0x22, 0x00 पूर्ण, 2 पूर्ण,
	अणु अणु 0x23, 0x40 पूर्ण, 2 पूर्ण,
	अणु अणु 0x24, 0x40 पूर्ण, 2 पूर्ण,
	अणु अणु 0x25, 0x6D पूर्ण, 2 पूर्ण,
	अणु अणु 0x26, 0x40 पूर्ण, 2 पूर्ण,
	अणु अणु 0x27, 0x40 पूर्ण, 2 पूर्ण,
	/* Vend */
	अणु अणु 0xE0, 0x00 पूर्ण, 2 पूर्ण,
	अणु अणु 0xDC, 0x21 पूर्ण, 2 पूर्ण,
	अणु अणु 0xDD, 0x22 पूर्ण, 2 पूर्ण,
	अणु अणु 0xDE, 0x07 पूर्ण, 2 पूर्ण,
	अणु अणु 0xDF, 0x07 पूर्ण, 2 पूर्ण,
	अणु अणु 0xE3, 0x6D पूर्ण, 2 पूर्ण,
	अणु अणु 0xE1, 0x07 पूर्ण, 2 पूर्ण,
	अणु अणु 0xE2, 0x07 पूर्ण, 2 पूर्ण,
	/* UD */
	अणु अणु 0x29, 0xD8 पूर्ण, 2 पूर्ण,
	अणु अणु 0x2A, 0x2A पूर्ण, 2 पूर्ण,
	/* CLK */
	अणु अणु 0x4B, 0x03 पूर्ण, 2 पूर्ण,
	अणु अणु 0x4C, 0x11 पूर्ण, 2 पूर्ण,
	अणु अणु 0x4D, 0x10 पूर्ण, 2 पूर्ण,
	अणु अणु 0x4E, 0x01 पूर्ण, 2 पूर्ण,
	अणु अणु 0x4F, 0x01 पूर्ण, 2 पूर्ण,
	अणु अणु 0x50, 0x10 पूर्ण, 2 पूर्ण,
	अणु अणु 0x51, 0x00 पूर्ण, 2 पूर्ण,
	अणु अणु 0x52, 0x80 पूर्ण, 2 पूर्ण,
	अणु अणु 0x53, 0x00 पूर्ण, 2 पूर्ण,
	अणु अणु 0x56, 0x00 पूर्ण, 2 पूर्ण,
	अणु अणु 0x54, 0x07 पूर्ण, 2 पूर्ण,
	अणु अणु 0x58, 0x07 पूर्ण, 2 पूर्ण,
	अणु अणु 0x55, 0x25 पूर्ण, 2 पूर्ण,
	/* Reset XDONB */
	अणु अणु 0x5B, 0x43 पूर्ण, 2 पूर्ण,
	अणु अणु 0x5C, 0x00 पूर्ण, 2 पूर्ण,
	अणु अणु 0x5F, 0x73 पूर्ण, 2 पूर्ण,
	अणु अणु 0x60, 0x73 पूर्ण, 2 पूर्ण,
	अणु अणु 0x63, 0x22 पूर्ण, 2 पूर्ण,
	अणु अणु 0x64, 0x00 पूर्ण, 2 पूर्ण,
	अणु अणु 0x67, 0x08 पूर्ण, 2 पूर्ण,
	अणु अणु 0x68, 0x04 पूर्ण, 2 पूर्ण,
	/* Resolution:1440x2560 */
	अणु अणु 0x72, 0x02 पूर्ण, 2 पूर्ण,
	/* mux */
	अणु अणु 0x7A, 0x80 पूर्ण, 2 पूर्ण,
	अणु अणु 0x7B, 0x91 पूर्ण, 2 पूर्ण,
	अणु अणु 0x7C, 0xD8 पूर्ण, 2 पूर्ण,
	अणु अणु 0x7D, 0x60 पूर्ण, 2 पूर्ण,
	अणु अणु 0x7F, 0x15 पूर्ण, 2 पूर्ण,
	अणु अणु 0x75, 0x15 पूर्ण, 2 पूर्ण,
	/* ABOFF */
	अणु अणु 0xB3, 0xC0 पूर्ण, 2 पूर्ण,
	अणु अणु 0xB4, 0x00 पूर्ण, 2 पूर्ण,
	अणु अणु 0xB5, 0x00 पूर्ण, 2 पूर्ण,
	/* Source EQ */
	अणु अणु 0x78, 0x00 पूर्ण, 2 पूर्ण,
	अणु अणु 0x79, 0x00 पूर्ण, 2 पूर्ण,
	अणु अणु 0x80, 0x00 पूर्ण, 2 पूर्ण,
	अणु अणु 0x83, 0x00 पूर्ण, 2 पूर्ण,
	/* FP BP */
	अणु अणु 0x93, 0x0A पूर्ण, 2 पूर्ण,
	अणु अणु 0x94, 0x0A पूर्ण, 2 पूर्ण,
	/* Inversion Type */
	अणु अणु 0x8A, 0x00 पूर्ण, 2 पूर्ण,
	अणु अणु 0x9B, 0xFF पूर्ण, 2 पूर्ण,
	/* IMGSWAP =1 @PortSwap=1 */
	अणु अणु 0x9D, 0xB0 पूर्ण, 2 पूर्ण,
	अणु अणु 0x9F, 0x63 पूर्ण, 2 पूर्ण,
	अणु अणु 0x98, 0x10 पूर्ण, 2 पूर्ण,
	/* FRM */
	अणु अणु 0xEC, 0x00 पूर्ण, 2 पूर्ण,
	/* CMD1 */
	अणु अणु 0xFF, 0x10 पूर्ण, 2 पूर्ण,
	/* VBP+VSA=,VFP = 10H */
	अणु अणु 0x3B, 0x03, 0x0A, 0x0A पूर्ण, 4 पूर्ण,
	/* FTE on */
	अणु अणु 0x35, 0x00 पूर्ण, 2 पूर्ण,
	/* EN_BK =1(स्वतः black) */
	अणु अणु 0xE5, 0x01 पूर्ण, 2 पूर्ण,
	/* CMD mode(10) VDO mode(03) */
	अणु अणु 0xBB, 0x03 पूर्ण, 2 पूर्ण,
	/* Non Reload MTP */
	अणु अणु 0xFB, 0x01 पूर्ण, 2 पूर्ण,
पूर्ण;

अटल पूर्णांक truly_dcs_ग_लिखो(काष्ठा drm_panel *panel, u32 command)
अणु
	काष्ठा truly_nt35597 *ctx = panel_to_ctx(panel);
	पूर्णांक i, ret;

	क्रम (i = 0; i < ARRAY_SIZE(ctx->dsi); i++) अणु
		ret = mipi_dsi_dcs_ग_लिखो(ctx->dsi[i], command, शून्य, 0);
		अगर (ret < 0) अणु
			dev_err(ctx->dev, "cmd 0x%x failed for dsi = %d\n", command, i);
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक truly_dcs_ग_लिखो_buf(काष्ठा drm_panel *panel,
	u32 size, स्थिर u8 *buf)
अणु
	काष्ठा truly_nt35597 *ctx = panel_to_ctx(panel);
	पूर्णांक ret = 0;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(ctx->dsi); i++) अणु
		ret = mipi_dsi_dcs_ग_लिखो_buffer(ctx->dsi[i], buf, size);
		अगर (ret < 0) अणु
			dev_err(ctx->dev, "failed to tx cmd [%d], err: %d\n", i, ret);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक truly_35597_घातer_on(काष्ठा truly_nt35597 *ctx)
अणु
	पूर्णांक ret, i;

	क्रम (i = 0; i < ARRAY_SIZE(ctx->supplies); i++) अणु
		ret = regulator_set_load(ctx->supplies[i].consumer,
					regulator_enable_loads[i]);
		अगर (ret)
			वापस ret;
	पूर्ण

	ret = regulator_bulk_enable(ARRAY_SIZE(ctx->supplies), ctx->supplies);
	अगर (ret < 0)
		वापस ret;

	/*
	 * Reset sequence of truly panel requires the panel to be
	 * out of reset क्रम 10ms, followed by being held in reset
	 * क्रम 10ms and then out again
	 */
	gpiod_set_value(ctx->reset_gpio, 0);
	usleep_range(10000, 20000);
	gpiod_set_value(ctx->reset_gpio, 1);
	usleep_range(10000, 20000);
	gpiod_set_value(ctx->reset_gpio, 0);
	usleep_range(10000, 20000);

	वापस 0;
पूर्ण

अटल पूर्णांक truly_nt35597_घातer_off(काष्ठा truly_nt35597 *ctx)
अणु
	पूर्णांक ret = 0;
	पूर्णांक i;

	gpiod_set_value(ctx->reset_gpio, 1);

	क्रम (i = 0; i < ARRAY_SIZE(ctx->supplies); i++) अणु
		ret = regulator_set_load(ctx->supplies[i].consumer,
				regulator_disable_loads[i]);
		अगर (ret) अणु
			dev_err(ctx->dev, "regulator_set_load failed %d\n", ret);
			वापस ret;
		पूर्ण
	पूर्ण

	ret = regulator_bulk_disable(ARRAY_SIZE(ctx->supplies), ctx->supplies);
	अगर (ret) अणु
		dev_err(ctx->dev, "regulator_bulk_disable failed %d\n", ret);
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक truly_nt35597_disable(काष्ठा drm_panel *panel)
अणु
	काष्ठा truly_nt35597 *ctx = panel_to_ctx(panel);
	पूर्णांक ret;

	अगर (!ctx->enabled)
		वापस 0;

	अगर (ctx->backlight) अणु
		ret = backlight_disable(ctx->backlight);
		अगर (ret < 0)
			dev_err(ctx->dev, "backlight disable failed %d\n", ret);
	पूर्ण

	ctx->enabled = false;
	वापस 0;
पूर्ण

अटल पूर्णांक truly_nt35597_unprepare(काष्ठा drm_panel *panel)
अणु
	काष्ठा truly_nt35597 *ctx = panel_to_ctx(panel);
	पूर्णांक ret = 0;

	अगर (!ctx->prepared)
		वापस 0;

	ctx->dsi[0]->mode_flags = 0;
	ctx->dsi[1]->mode_flags = 0;

	ret = truly_dcs_ग_लिखो(panel, MIPI_DCS_SET_DISPLAY_OFF);
	अगर (ret < 0) अणु
		dev_err(ctx->dev, "set_display_off cmd failed ret = %d\n", ret);
	पूर्ण

	/* 120ms delay required here as per DCS spec */
	msleep(120);

	ret = truly_dcs_ग_लिखो(panel, MIPI_DCS_ENTER_SLEEP_MODE);
	अगर (ret < 0) अणु
		dev_err(ctx->dev, "enter_sleep cmd failed ret = %d\n", ret);
	पूर्ण

	ret = truly_nt35597_घातer_off(ctx);
	अगर (ret < 0)
		dev_err(ctx->dev, "power_off failed ret = %d\n", ret);

	ctx->prepared = false;
	वापस ret;
पूर्ण

अटल पूर्णांक truly_nt35597_prepare(काष्ठा drm_panel *panel)
अणु
	काष्ठा truly_nt35597 *ctx = panel_to_ctx(panel);
	पूर्णांक ret;
	पूर्णांक i;
	स्थिर काष्ठा cmd_set *panel_on_cmds;
	स्थिर काष्ठा nt35597_config *config;
	u32 num_cmds;

	अगर (ctx->prepared)
		वापस 0;

	ret = truly_35597_घातer_on(ctx);
	अगर (ret < 0)
		वापस ret;

	ctx->dsi[0]->mode_flags |= MIPI_DSI_MODE_LPM;
	ctx->dsi[1]->mode_flags |= MIPI_DSI_MODE_LPM;

	config = ctx->config;
	panel_on_cmds = config->panel_on_cmds;
	num_cmds = config->num_on_cmds;

	क्रम (i = 0; i < num_cmds; i++) अणु
		ret = truly_dcs_ग_लिखो_buf(panel,
				panel_on_cmds[i].size,
					panel_on_cmds[i].commands);
		अगर (ret < 0) अणु
			dev_err(ctx->dev, "cmd set tx failed i = %d ret = %d\n", i, ret);
			जाओ घातer_off;
		पूर्ण
	पूर्ण

	ret = truly_dcs_ग_लिखो(panel, MIPI_DCS_EXIT_SLEEP_MODE);
	अगर (ret < 0) अणु
		dev_err(ctx->dev, "exit_sleep_mode cmd failed ret = %d\n", ret);
		जाओ घातer_off;
	पूर्ण

	/* Per DSI spec रुको 120ms after sending निकास sleep DCS command */
	msleep(120);

	ret = truly_dcs_ग_लिखो(panel, MIPI_DCS_SET_DISPLAY_ON);
	अगर (ret < 0) अणु
		dev_err(ctx->dev, "set_display_on cmd failed ret = %d\n", ret);
		जाओ घातer_off;
	पूर्ण

	/* Per DSI spec रुको 120ms after sending set_display_on DCS command */
	msleep(120);

	ctx->prepared = true;

	वापस 0;

घातer_off:
	अगर (truly_nt35597_घातer_off(ctx))
		dev_err(ctx->dev, "power_off failed\n");
	वापस ret;
पूर्ण

अटल पूर्णांक truly_nt35597_enable(काष्ठा drm_panel *panel)
अणु
	काष्ठा truly_nt35597 *ctx = panel_to_ctx(panel);
	पूर्णांक ret;

	अगर (ctx->enabled)
		वापस 0;

	अगर (ctx->backlight) अणु
		ret = backlight_enable(ctx->backlight);
		अगर (ret < 0)
			dev_err(ctx->dev, "backlight enable failed %d\n", ret);
	पूर्ण

	ctx->enabled = true;

	वापस 0;
पूर्ण

अटल पूर्णांक truly_nt35597_get_modes(काष्ठा drm_panel *panel,
				   काष्ठा drm_connector *connector)
अणु
	काष्ठा truly_nt35597 *ctx = panel_to_ctx(panel);
	काष्ठा drm_display_mode *mode;
	स्थिर काष्ठा nt35597_config *config;

	config = ctx->config;
	mode = drm_mode_create(connector->dev);
	अगर (!mode) अणु
		dev_err(ctx->dev, "failed to create a new display mode\n");
		वापस 0;
	पूर्ण

	connector->display_info.width_mm = config->width_mm;
	connector->display_info.height_mm = config->height_mm;
	drm_mode_copy(mode, config->dm);
	mode->type = DRM_MODE_TYPE_DRIVER | DRM_MODE_TYPE_PREFERRED;
	drm_mode_probed_add(connector, mode);

	वापस 1;
पूर्ण

अटल स्थिर काष्ठा drm_panel_funcs truly_nt35597_drm_funcs = अणु
	.disable = truly_nt35597_disable,
	.unprepare = truly_nt35597_unprepare,
	.prepare = truly_nt35597_prepare,
	.enable = truly_nt35597_enable,
	.get_modes = truly_nt35597_get_modes,
पूर्ण;

अटल पूर्णांक truly_nt35597_panel_add(काष्ठा truly_nt35597 *ctx)
अणु
	काष्ठा device *dev = ctx->dev;
	पूर्णांक ret, i;

	क्रम (i = 0; i < ARRAY_SIZE(ctx->supplies); i++)
		ctx->supplies[i].supply = regulator_names[i];

	ret = devm_regulator_bulk_get(dev, ARRAY_SIZE(ctx->supplies),
				      ctx->supplies);
	अगर (ret < 0)
		वापस ret;

	ctx->reset_gpio = devm_gpiod_get(dev, "reset", GPIOD_OUT_LOW);
	अगर (IS_ERR(ctx->reset_gpio)) अणु
		dev_err(dev, "cannot get reset gpio %ld\n", PTR_ERR(ctx->reset_gpio));
		वापस PTR_ERR(ctx->reset_gpio);
	पूर्ण

	ctx->mode_gpio = devm_gpiod_get(dev, "mode", GPIOD_OUT_LOW);
	अगर (IS_ERR(ctx->mode_gpio)) अणु
		dev_err(dev, "cannot get mode gpio %ld\n", PTR_ERR(ctx->mode_gpio));
		वापस PTR_ERR(ctx->mode_gpio);
	पूर्ण

	/* dual port */
	gpiod_set_value(ctx->mode_gpio, 0);

	drm_panel_init(&ctx->panel, dev, &truly_nt35597_drm_funcs,
		       DRM_MODE_CONNECTOR_DSI);
	drm_panel_add(&ctx->panel);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा drm_display_mode qcom_sdm845_mtp_2k_mode = अणु
	.name = "1440x2560",
	.घड़ी = 268316,
	.hdisplay = 1440,
	.hsync_start = 1440 + 200,
	.hsync_end = 1440 + 200 + 32,
	.htotal = 1440 + 200 + 32 + 64,
	.vdisplay = 2560,
	.vsync_start = 2560 + 8,
	.vsync_end = 2560 + 8 + 1,
	.vtotal = 2560 + 8 + 1 + 7,
	.flags = 0,
पूर्ण;

अटल स्थिर काष्ठा nt35597_config nt35597_dir = अणु
	.width_mm = 74,
	.height_mm = 131,
	.panel_name = "qcom_sdm845_mtp_2k_panel",
	.dm = &qcom_sdm845_mtp_2k_mode,
	.panel_on_cmds = qcom_2k_panel_magic_cmds,
	.num_on_cmds = ARRAY_SIZE(qcom_2k_panel_magic_cmds),
पूर्ण;

अटल पूर्णांक truly_nt35597_probe(काष्ठा mipi_dsi_device *dsi)
अणु
	काष्ठा device *dev = &dsi->dev;
	काष्ठा truly_nt35597 *ctx;
	काष्ठा mipi_dsi_device *dsi1_device;
	काष्ठा device_node *dsi1;
	काष्ठा mipi_dsi_host *dsi1_host;
	काष्ठा mipi_dsi_device *dsi_dev;
	पूर्णांक ret = 0;
	पूर्णांक i;

	स्थिर काष्ठा mipi_dsi_device_info info = अणु
		.type = "trulynt35597",
		.channel = 0,
		.node = शून्य,
	पूर्ण;

	ctx = devm_kzalloc(dev, माप(*ctx), GFP_KERNEL);

	अगर (!ctx)
		वापस -ENOMEM;

	/*
	 * This device represents itself as one with two input ports which are
	 * fed by the output ports of the two DSI controllers . The DSI0 is
	 * the master controller and has most of the panel related info in its
	 * child node.
	 */

	ctx->config = of_device_get_match_data(dev);

	अगर (!ctx->config) अणु
		dev_err(dev, "missing device configuration\n");
		वापस -ENODEV;
	पूर्ण

	dsi1 = of_graph_get_remote_node(dsi->dev.of_node, 1, -1);
	अगर (!dsi1) अणु
		dev_err(dev, "failed to get remote node for dsi1_device\n");
		वापस -ENODEV;
	पूर्ण

	dsi1_host = of_find_mipi_dsi_host_by_node(dsi1);
	of_node_put(dsi1);
	अगर (!dsi1_host) अणु
		dev_err(dev, "failed to find dsi host\n");
		वापस -EPROBE_DEFER;
	पूर्ण

	/* रेजिस्टर the second DSI device */
	dsi1_device = mipi_dsi_device_रेजिस्टर_full(dsi1_host, &info);
	अगर (IS_ERR(dsi1_device)) अणु
		dev_err(dev, "failed to create dsi device\n");
		वापस PTR_ERR(dsi1_device);
	पूर्ण

	mipi_dsi_set_drvdata(dsi, ctx);

	ctx->dev = dev;
	ctx->dsi[0] = dsi;
	ctx->dsi[1] = dsi1_device;

	ret = truly_nt35597_panel_add(ctx);
	अगर (ret) अणु
		dev_err(dev, "failed to add panel\n");
		जाओ err_panel_add;
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(ctx->dsi); i++) अणु
		dsi_dev = ctx->dsi[i];
		dsi_dev->lanes = 4;
		dsi_dev->क्रमmat = MIPI_DSI_FMT_RGB888;
		dsi_dev->mode_flags = MIPI_DSI_MODE_VIDEO | MIPI_DSI_MODE_LPM |
			MIPI_DSI_CLOCK_NON_CONTINUOUS;
		ret = mipi_dsi_attach(dsi_dev);
		अगर (ret < 0) अणु
			dev_err(dev, "dsi attach failed i = %d\n", i);
			जाओ err_dsi_attach;
		पूर्ण
	पूर्ण

	वापस 0;

err_dsi_attach:
	drm_panel_हटाओ(&ctx->panel);
err_panel_add:
	mipi_dsi_device_unरेजिस्टर(dsi1_device);
	वापस ret;
पूर्ण

अटल पूर्णांक truly_nt35597_हटाओ(काष्ठा mipi_dsi_device *dsi)
अणु
	काष्ठा truly_nt35597 *ctx = mipi_dsi_get_drvdata(dsi);

	अगर (ctx->dsi[0])
		mipi_dsi_detach(ctx->dsi[0]);
	अगर (ctx->dsi[1]) अणु
		mipi_dsi_detach(ctx->dsi[1]);
		mipi_dsi_device_unरेजिस्टर(ctx->dsi[1]);
	पूर्ण

	drm_panel_हटाओ(&ctx->panel);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id truly_nt35597_of_match[] = अणु
	अणु
		.compatible = "truly,nt35597-2K-display",
		.data = &nt35597_dir,
	पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, truly_nt35597_of_match);

अटल काष्ठा mipi_dsi_driver truly_nt35597_driver = अणु
	.driver = अणु
		.name = "panel-truly-nt35597",
		.of_match_table = truly_nt35597_of_match,
	पूर्ण,
	.probe = truly_nt35597_probe,
	.हटाओ = truly_nt35597_हटाओ,
पूर्ण;
module_mipi_dsi_driver(truly_nt35597_driver);

MODULE_DESCRIPTION("Truly NT35597 DSI Panel Driver");
MODULE_LICENSE("GPL v2");
