<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2019, Huaqin Telecom Technology Co., Ltd
 *
 * Author: Jerry Han <jerry.han.hq@gmail.com>
 *
 */

#समावेश <linux/delay.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>

#समावेश <linux/gpio/consumer.h>
#समावेश <linux/regulator/consumer.h>

#समावेश <drm/drm_device.h>
#समावेश <drm/drm_mipi_dsi.h>
#समावेश <drm/drm_modes.h>
#समावेश <drm/drm_panel.h>

#समावेश <video/mipi_display.h>

काष्ठा panel_cmd अणु
	अक्षर cmd;
	अक्षर data;
पूर्ण;

काष्ठा panel_desc अणु
	स्थिर काष्ठा drm_display_mode *display_mode;
	अचिन्हित पूर्णांक bpc;
	अचिन्हित पूर्णांक width_mm;
	अचिन्हित पूर्णांक height_mm;

	अचिन्हित दीर्घ mode_flags;
	क्रमागत mipi_dsi_pixel_क्रमmat क्रमmat;
	अचिन्हित पूर्णांक lanes;
	स्थिर काष्ठा panel_cmd *on_cmds;
	अचिन्हित पूर्णांक on_cmds_num;
पूर्ण;

काष्ठा panel_info अणु
	काष्ठा drm_panel base;
	काष्ठा mipi_dsi_device *link;
	स्थिर काष्ठा panel_desc *desc;

	काष्ठा gpio_desc *enable_gpio;
	काष्ठा gpio_desc *pp33_gpio;
	काष्ठा gpio_desc *pp18_gpio;

	bool prepared;
	bool enabled;
पूर्ण;

अटल अंतरभूत काष्ठा panel_info *to_panel_info(काष्ठा drm_panel *panel)
अणु
	वापस container_of(panel, काष्ठा panel_info, base);
पूर्ण

अटल व्योम disable_gpios(काष्ठा panel_info *pinfo)
अणु
	gpiod_set_value(pinfo->enable_gpio, 0);
	gpiod_set_value(pinfo->pp33_gpio, 0);
	gpiod_set_value(pinfo->pp18_gpio, 0);
पूर्ण

अटल पूर्णांक send_mipi_cmds(काष्ठा drm_panel *panel, स्थिर काष्ठा panel_cmd *cmds)
अणु
	काष्ठा panel_info *pinfo = to_panel_info(panel);
	अचिन्हित पूर्णांक i = 0;
	पूर्णांक err;

	क्रम (i = 0; i < pinfo->desc->on_cmds_num; i++) अणु
		err = mipi_dsi_dcs_ग_लिखो_buffer(pinfo->link, &cmds[i],
						माप(काष्ठा panel_cmd));

		अगर (err < 0)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक boe_panel_disable(काष्ठा drm_panel *panel)
अणु
	काष्ठा panel_info *pinfo = to_panel_info(panel);
	पूर्णांक err;

	अगर (!pinfo->enabled)
		वापस 0;

	err = mipi_dsi_dcs_set_display_off(pinfo->link);
	अगर (err < 0) अणु
		dev_err(panel->dev, "failed to set display off: %d\n", err);
		वापस err;
	पूर्ण

	pinfo->enabled = false;

	वापस 0;
पूर्ण

अटल पूर्णांक boe_panel_unprepare(काष्ठा drm_panel *panel)
अणु
	काष्ठा panel_info *pinfo = to_panel_info(panel);
	पूर्णांक err;

	अगर (!pinfo->prepared)
		वापस 0;

	err = mipi_dsi_dcs_set_display_off(pinfo->link);
	अगर (err < 0)
		dev_err(panel->dev, "failed to set display off: %d\n", err);

	err = mipi_dsi_dcs_enter_sleep_mode(pinfo->link);
	अगर (err < 0)
		dev_err(panel->dev, "failed to enter sleep mode: %d\n", err);

	/* sleep_mode_delay: 1ms - 2ms */
	usleep_range(1000, 2000);

	disable_gpios(pinfo);

	pinfo->prepared = false;

	वापस 0;
पूर्ण

अटल पूर्णांक boe_panel_prepare(काष्ठा drm_panel *panel)
अणु
	काष्ठा panel_info *pinfo = to_panel_info(panel);
	पूर्णांक err;

	अगर (pinfo->prepared)
		वापस 0;

	gpiod_set_value(pinfo->pp18_gpio, 1);
	/* T1: 5ms - 6ms */
	usleep_range(5000, 6000);
	gpiod_set_value(pinfo->pp33_gpio, 1);

	/* reset sequence */
	/* T2: 14ms - 15ms */
	usleep_range(14000, 15000);
	gpiod_set_value(pinfo->enable_gpio, 1);

	/* T3: 1ms - 2ms */
	usleep_range(1000, 2000);
	gpiod_set_value(pinfo->enable_gpio, 0);

	/* T4: 1ms - 2ms */
	usleep_range(1000, 2000);
	gpiod_set_value(pinfo->enable_gpio, 1);

	/* T5: 5ms - 6ms */
	usleep_range(5000, 6000);

	/* send init code */
	err = send_mipi_cmds(panel, pinfo->desc->on_cmds);
	अगर (err < 0) अणु
		dev_err(panel->dev, "failed to send DCS Init Code: %d\n", err);
		जाओ घातeroff;
	पूर्ण

	err = mipi_dsi_dcs_निकास_sleep_mode(pinfo->link);
	अगर (err < 0) अणु
		dev_err(panel->dev, "failed to exit sleep mode: %d\n", err);
		जाओ घातeroff;
	पूर्ण

	/* T6: 120ms - 121ms */
	usleep_range(120000, 121000);

	err = mipi_dsi_dcs_set_display_on(pinfo->link);
	अगर (err < 0) अणु
		dev_err(panel->dev, "failed to set display on: %d\n", err);
		जाओ घातeroff;
	पूर्ण

	/* T7: 20ms - 21ms */
	usleep_range(20000, 21000);

	pinfo->prepared = true;

	वापस 0;

घातeroff:
	disable_gpios(pinfo);
	वापस err;
पूर्ण

अटल पूर्णांक boe_panel_enable(काष्ठा drm_panel *panel)
अणु
	काष्ठा panel_info *pinfo = to_panel_info(panel);
	पूर्णांक ret;

	अगर (pinfo->enabled)
		वापस 0;

	usleep_range(120000, 121000);

	ret = mipi_dsi_dcs_set_display_on(pinfo->link);
	अगर (ret < 0) अणु
		dev_err(panel->dev, "failed to set display on: %d\n", ret);
		वापस ret;
	पूर्ण

	pinfo->enabled = true;

	वापस 0;
पूर्ण

अटल पूर्णांक boe_panel_get_modes(काष्ठा drm_panel *panel,
			       काष्ठा drm_connector *connector)
अणु
	काष्ठा panel_info *pinfo = to_panel_info(panel);
	स्थिर काष्ठा drm_display_mode *m = pinfo->desc->display_mode;
	काष्ठा drm_display_mode *mode;

	mode = drm_mode_duplicate(connector->dev, m);
	अगर (!mode) अणु
		dev_err(pinfo->base.dev, "failed to add mode %ux%u@%u\n",
			m->hdisplay, m->vdisplay, drm_mode_vrefresh(m));
		वापस -ENOMEM;
	पूर्ण

	drm_mode_set_name(mode);

	drm_mode_probed_add(connector, mode);

	connector->display_info.width_mm = pinfo->desc->width_mm;
	connector->display_info.height_mm = pinfo->desc->height_mm;
	connector->display_info.bpc = pinfo->desc->bpc;

	वापस 1;
पूर्ण

अटल स्थिर काष्ठा drm_panel_funcs panel_funcs = अणु
	.disable = boe_panel_disable,
	.unprepare = boe_panel_unprepare,
	.prepare = boe_panel_prepare,
	.enable = boe_panel_enable,
	.get_modes = boe_panel_get_modes,
पूर्ण;

अटल स्थिर काष्ठा drm_display_mode शेष_display_mode = अणु
	.घड़ी = 159420,
	.hdisplay = 1200,
	.hsync_start = 1200 + 80,
	.hsync_end = 1200 + 80 + 60,
	.htotal = 1200 + 80 + 60 + 24,
	.vdisplay = 1920,
	.vsync_start = 1920 + 10,
	.vsync_end = 1920 + 10 + 14,
	.vtotal = 1920 + 10 + 14 + 4,
पूर्ण;

/* 8 inch */
अटल स्थिर काष्ठा panel_cmd boe_himax8279d8p_on_cmds[] = अणु
	अणु 0xB0, 0x05 पूर्ण,
	अणु 0xB1, 0xE5 पूर्ण,
	अणु 0xB3, 0x52 पूर्ण,
	अणु 0xC0, 0x00 पूर्ण,
	अणु 0xC2, 0x57 पूर्ण,
	अणु 0xD9, 0x85 पूर्ण,
	अणु 0xB0, 0x01 पूर्ण,
	अणु 0xC8, 0x00 पूर्ण,
	अणु 0xC9, 0x00 पूर्ण,
	अणु 0xCC, 0x26 पूर्ण,
	अणु 0xCD, 0x26 पूर्ण,
	अणु 0xDC, 0x00 पूर्ण,
	अणु 0xDD, 0x00 पूर्ण,
	अणु 0xE0, 0x26 पूर्ण,
	अणु 0xE1, 0x26 पूर्ण,
	अणु 0xB0, 0x03 पूर्ण,
	अणु 0xC3, 0x2A पूर्ण,
	अणु 0xE7, 0x2A पूर्ण,
	अणु 0xC5, 0x2A पूर्ण,
	अणु 0xDE, 0x2A पूर्ण,
	अणु 0xBC, 0x02 पूर्ण,
	अणु 0xCB, 0x02 पूर्ण,
	अणु 0xB0, 0x00 पूर्ण,
	अणु 0xB6, 0x03 पूर्ण,
	अणु 0xBA, 0x8B पूर्ण,
	अणु 0xBF, 0x15 पूर्ण,
	अणु 0xC0, 0x18 पूर्ण,
	अणु 0xC2, 0x14 पूर्ण,
	अणु 0xC3, 0x02 पूर्ण,
	अणु 0xC4, 0x14 पूर्ण,
	अणु 0xC5, 0x02 पूर्ण,
	अणु 0xCC, 0x0A पूर्ण,
	अणु 0xB0, 0x06 पूर्ण,
	अणु 0xC0, 0xA5 पूर्ण,
	अणु 0xD5, 0x20 पूर्ण,
	अणु 0xC0, 0x00 पूर्ण,
	अणु 0xB0, 0x02 पूर्ण,
	अणु 0xC0, 0x00 पूर्ण,
	अणु 0xC1, 0x02 पूर्ण,
	अणु 0xC2, 0x06 पूर्ण,
	अणु 0xC3, 0x16 पूर्ण,
	अणु 0xC4, 0x0E पूर्ण,
	अणु 0xC5, 0x18 पूर्ण,
	अणु 0xC6, 0x26 पूर्ण,
	अणु 0xC7, 0x32 पूर्ण,
	अणु 0xC8, 0x3F पूर्ण,
	अणु 0xC9, 0x3F पूर्ण,
	अणु 0xCA, 0x3F पूर्ण,
	अणु 0xCB, 0x3F पूर्ण,
	अणु 0xCC, 0x3D पूर्ण,
	अणु 0xCD, 0x2F पूर्ण,
	अणु 0xCE, 0x2F पूर्ण,
	अणु 0xCF, 0x2F पूर्ण,
	अणु 0xD0, 0x07 पूर्ण,
	अणु 0xD2, 0x00 पूर्ण,
	अणु 0xD3, 0x02 पूर्ण,
	अणु 0xD4, 0x06 पूर्ण,
	अणु 0xD5, 0x12 पूर्ण,
	अणु 0xD6, 0x0A पूर्ण,
	अणु 0xD7, 0x14 पूर्ण,
	अणु 0xD8, 0x22 पूर्ण,
	अणु 0xD9, 0x2E पूर्ण,
	अणु 0xDA, 0x3D पूर्ण,
	अणु 0xDB, 0x3F पूर्ण,
	अणु 0xDC, 0x3F पूर्ण,
	अणु 0xDD, 0x3F पूर्ण,
	अणु 0xDE, 0x3D पूर्ण,
	अणु 0xDF, 0x2F पूर्ण,
	अणु 0xE0, 0x2F पूर्ण,
	अणु 0xE1, 0x2F पूर्ण,
	अणु 0xE2, 0x07 पूर्ण,
	अणु 0xB0, 0x07 पूर्ण,
	अणु 0xB1, 0x18 पूर्ण,
	अणु 0xB2, 0x19 पूर्ण,
	अणु 0xB3, 0x2E पूर्ण,
	अणु 0xB4, 0x52 पूर्ण,
	अणु 0xB5, 0x72 पूर्ण,
	अणु 0xB6, 0x8C पूर्ण,
	अणु 0xB7, 0xBD पूर्ण,
	अणु 0xB8, 0xEB पूर्ण,
	अणु 0xB9, 0x47 पूर्ण,
	अणु 0xBA, 0x96 पूर्ण,
	अणु 0xBB, 0x1E पूर्ण,
	अणु 0xBC, 0x90 पूर्ण,
	अणु 0xBD, 0x93 पूर्ण,
	अणु 0xBE, 0xFA पूर्ण,
	अणु 0xBF, 0x56 पूर्ण,
	अणु 0xC0, 0x8C पूर्ण,
	अणु 0xC1, 0xB7 पूर्ण,
	अणु 0xC2, 0xCC पूर्ण,
	अणु 0xC3, 0xDF पूर्ण,
	अणु 0xC4, 0xE8 पूर्ण,
	अणु 0xC5, 0xF0 पूर्ण,
	अणु 0xC6, 0xF8 पूर्ण,
	अणु 0xC7, 0xFA पूर्ण,
	अणु 0xC8, 0xFC पूर्ण,
	अणु 0xC9, 0x00 पूर्ण,
	अणु 0xCA, 0x00 पूर्ण,
	अणु 0xCB, 0x5A पूर्ण,
	अणु 0xCC, 0xAF पूर्ण,
	अणु 0xCD, 0xFF पूर्ण,
	अणु 0xCE, 0xFF पूर्ण,
	अणु 0xB0, 0x08 पूर्ण,
	अणु 0xB1, 0x04 पूर्ण,
	अणु 0xB2, 0x15 पूर्ण,
	अणु 0xB3, 0x2D पूर्ण,
	अणु 0xB4, 0x51 पूर्ण,
	अणु 0xB5, 0x72 पूर्ण,
	अणु 0xB6, 0x8D पूर्ण,
	अणु 0xB7, 0xBE पूर्ण,
	अणु 0xB8, 0xED पूर्ण,
	अणु 0xB9, 0x4A पूर्ण,
	अणु 0xBA, 0x9A पूर्ण,
	अणु 0xBB, 0x23 पूर्ण,
	अणु 0xBC, 0x95 पूर्ण,
	अणु 0xBD, 0x98 पूर्ण,
	अणु 0xBE, 0xFF पूर्ण,
	अणु 0xBF, 0x59 पूर्ण,
	अणु 0xC0, 0x8E पूर्ण,
	अणु 0xC1, 0xB9 पूर्ण,
	अणु 0xC2, 0xCD पूर्ण,
	अणु 0xC3, 0xDF पूर्ण,
	अणु 0xC4, 0xE8 पूर्ण,
	अणु 0xC5, 0xF0 पूर्ण,
	अणु 0xC6, 0xF8 पूर्ण,
	अणु 0xC7, 0xFA पूर्ण,
	अणु 0xC8, 0xFC पूर्ण,
	अणु 0xC9, 0x00 पूर्ण,
	अणु 0xCA, 0x00 पूर्ण,
	अणु 0xCB, 0x5A पूर्ण,
	अणु 0xCC, 0xAF पूर्ण,
	अणु 0xCD, 0xFF पूर्ण,
	अणु 0xCE, 0xFF पूर्ण,
	अणु 0xB0, 0x09 पूर्ण,
	अणु 0xB1, 0x04 पूर्ण,
	अणु 0xB2, 0x2C पूर्ण,
	अणु 0xB3, 0x36 पूर्ण,
	अणु 0xB4, 0x53 पूर्ण,
	अणु 0xB5, 0x73 पूर्ण,
	अणु 0xB6, 0x8E पूर्ण,
	अणु 0xB7, 0xC0 पूर्ण,
	अणु 0xB8, 0xEF पूर्ण,
	अणु 0xB9, 0x4C पूर्ण,
	अणु 0xBA, 0x9D पूर्ण,
	अणु 0xBB, 0x25 पूर्ण,
	अणु 0xBC, 0x96 पूर्ण,
	अणु 0xBD, 0x9A पूर्ण,
	अणु 0xBE, 0x01 पूर्ण,
	अणु 0xBF, 0x59 पूर्ण,
	अणु 0xC0, 0x8E पूर्ण,
	अणु 0xC1, 0xB9 पूर्ण,
	अणु 0xC2, 0xCD पूर्ण,
	अणु 0xC3, 0xDF पूर्ण,
	अणु 0xC4, 0xE8 पूर्ण,
	अणु 0xC5, 0xF0 पूर्ण,
	अणु 0xC6, 0xF8 पूर्ण,
	अणु 0xC7, 0xFA पूर्ण,
	अणु 0xC8, 0xFC पूर्ण,
	अणु 0xC9, 0x00 पूर्ण,
	अणु 0xCA, 0x00 पूर्ण,
	अणु 0xCB, 0x5A पूर्ण,
	अणु 0xCC, 0xBF पूर्ण,
	अणु 0xCD, 0xFF पूर्ण,
	अणु 0xCE, 0xFF पूर्ण,
	अणु 0xB0, 0x0A पूर्ण,
	अणु 0xB1, 0x18 पूर्ण,
	अणु 0xB2, 0x19 पूर्ण,
	अणु 0xB3, 0x2E पूर्ण,
	अणु 0xB4, 0x52 पूर्ण,
	अणु 0xB5, 0x72 पूर्ण,
	अणु 0xB6, 0x8C पूर्ण,
	अणु 0xB7, 0xBD पूर्ण,
	अणु 0xB8, 0xEB पूर्ण,
	अणु 0xB9, 0x47 पूर्ण,
	अणु 0xBA, 0x96 पूर्ण,
	अणु 0xBB, 0x1E पूर्ण,
	अणु 0xBC, 0x90 पूर्ण,
	अणु 0xBD, 0x93 पूर्ण,
	अणु 0xBE, 0xFA पूर्ण,
	अणु 0xBF, 0x56 पूर्ण,
	अणु 0xC0, 0x8C पूर्ण,
	अणु 0xC1, 0xB7 पूर्ण,
	अणु 0xC2, 0xCC पूर्ण,
	अणु 0xC3, 0xDF पूर्ण,
	अणु 0xC4, 0xE8 पूर्ण,
	अणु 0xC5, 0xF0 पूर्ण,
	अणु 0xC6, 0xF8 पूर्ण,
	अणु 0xC7, 0xFA पूर्ण,
	अणु 0xC8, 0xFC पूर्ण,
	अणु 0xC9, 0x00 पूर्ण,
	अणु 0xCA, 0x00 पूर्ण,
	अणु 0xCB, 0x5A पूर्ण,
	अणु 0xCC, 0xAF पूर्ण,
	अणु 0xCD, 0xFF पूर्ण,
	अणु 0xCE, 0xFF पूर्ण,
	अणु 0xB0, 0x0B पूर्ण,
	अणु 0xB1, 0x04 पूर्ण,
	अणु 0xB2, 0x15 पूर्ण,
	अणु 0xB3, 0x2D पूर्ण,
	अणु 0xB4, 0x51 पूर्ण,
	अणु 0xB5, 0x72 पूर्ण,
	अणु 0xB6, 0x8D पूर्ण,
	अणु 0xB7, 0xBE पूर्ण,
	अणु 0xB8, 0xED पूर्ण,
	अणु 0xB9, 0x4A पूर्ण,
	अणु 0xBA, 0x9A पूर्ण,
	अणु 0xBB, 0x23 पूर्ण,
	अणु 0xBC, 0x95 पूर्ण,
	अणु 0xBD, 0x98 पूर्ण,
	अणु 0xBE, 0xFF पूर्ण,
	अणु 0xBF, 0x59 पूर्ण,
	अणु 0xC0, 0x8E पूर्ण,
	अणु 0xC1, 0xB9 पूर्ण,
	अणु 0xC2, 0xCD पूर्ण,
	अणु 0xC3, 0xDF पूर्ण,
	अणु 0xC4, 0xE8 पूर्ण,
	अणु 0xC5, 0xF0 पूर्ण,
	अणु 0xC6, 0xF8 पूर्ण,
	अणु 0xC7, 0xFA पूर्ण,
	अणु 0xC8, 0xFC पूर्ण,
	अणु 0xC9, 0x00 पूर्ण,
	अणु 0xCA, 0x00 पूर्ण,
	अणु 0xCB, 0x5A पूर्ण,
	अणु 0xCC, 0xAF पूर्ण,
	अणु 0xCD, 0xFF पूर्ण,
	अणु 0xCE, 0xFF पूर्ण,
	अणु 0xB0, 0x0C पूर्ण,
	अणु 0xB1, 0x04 पूर्ण,
	अणु 0xB2, 0x2C पूर्ण,
	अणु 0xB3, 0x36 पूर्ण,
	अणु 0xB4, 0x53 पूर्ण,
	अणु 0xB5, 0x73 पूर्ण,
	अणु 0xB6, 0x8E पूर्ण,
	अणु 0xB7, 0xC0 पूर्ण,
	अणु 0xB8, 0xEF पूर्ण,
	अणु 0xB9, 0x4C पूर्ण,
	अणु 0xBA, 0x9D पूर्ण,
	अणु 0xBB, 0x25 पूर्ण,
	अणु 0xBC, 0x96 पूर्ण,
	अणु 0xBD, 0x9A पूर्ण,
	अणु 0xBE, 0x01 पूर्ण,
	अणु 0xBF, 0x59 पूर्ण,
	अणु 0xC0, 0x8E पूर्ण,
	अणु 0xC1, 0xB9 पूर्ण,
	अणु 0xC2, 0xCD पूर्ण,
	अणु 0xC3, 0xDF पूर्ण,
	अणु 0xC4, 0xE8 पूर्ण,
	अणु 0xC5, 0xF0 पूर्ण,
	अणु 0xC6, 0xF8 पूर्ण,
	अणु 0xC7, 0xFA पूर्ण,
	अणु 0xC8, 0xFC पूर्ण,
	अणु 0xC9, 0x00 पूर्ण,
	अणु 0xCA, 0x00 पूर्ण,
	अणु 0xCB, 0x5A पूर्ण,
	अणु 0xCC, 0xBF पूर्ण,
	अणु 0xCD, 0xFF पूर्ण,
	अणु 0xCE, 0xFF पूर्ण,
	अणु 0xB0, 0x04 पूर्ण,
	अणु 0xB5, 0x02 पूर्ण,
	अणु 0xB6, 0x01 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा panel_desc boe_himax8279d8p_panel_desc = अणु
	.display_mode = &शेष_display_mode,
	.bpc = 8,
	.width_mm = 107,
	.height_mm = 172,
	.mode_flags = MIPI_DSI_MODE_VIDEO | MIPI_DSI_MODE_VIDEO_SYNC_PULSE |
			MIPI_DSI_CLOCK_NON_CONTINUOUS | MIPI_DSI_MODE_LPM,
	.क्रमmat = MIPI_DSI_FMT_RGB888,
	.lanes = 4,
	.on_cmds = boe_himax8279d8p_on_cmds,
	.on_cmds_num = 260,
पूर्ण;

/* 10 inch */
अटल स्थिर काष्ठा panel_cmd boe_himax8279d10p_on_cmds[] = अणु
	अणु 0xB0, 0x05 पूर्ण,
	अणु 0xB1, 0xE5 पूर्ण,
	अणु 0xB3, 0x52 पूर्ण,
	अणु 0xB0, 0x00 पूर्ण,
	अणु 0xB6, 0x03 पूर्ण,
	अणु 0xBA, 0x8B पूर्ण,
	अणु 0xBF, 0x1A पूर्ण,
	अणु 0xC0, 0x0F पूर्ण,
	अणु 0xC2, 0x0C पूर्ण,
	अणु 0xC3, 0x02 पूर्ण,
	अणु 0xC4, 0x0C पूर्ण,
	अणु 0xC5, 0x02 पूर्ण,
	अणु 0xB0, 0x01 पूर्ण,
	अणु 0xE0, 0x26 पूर्ण,
	अणु 0xE1, 0x26 पूर्ण,
	अणु 0xDC, 0x00 पूर्ण,
	अणु 0xDD, 0x00 पूर्ण,
	अणु 0xCC, 0x26 पूर्ण,
	अणु 0xCD, 0x26 पूर्ण,
	अणु 0xC8, 0x00 पूर्ण,
	अणु 0xC9, 0x00 पूर्ण,
	अणु 0xD2, 0x03 पूर्ण,
	अणु 0xD3, 0x03 पूर्ण,
	अणु 0xE6, 0x04 पूर्ण,
	अणु 0xE7, 0x04 पूर्ण,
	अणु 0xC4, 0x09 पूर्ण,
	अणु 0xC5, 0x09 पूर्ण,
	अणु 0xD8, 0x0A पूर्ण,
	अणु 0xD9, 0x0A पूर्ण,
	अणु 0xC2, 0x0B पूर्ण,
	अणु 0xC3, 0x0B पूर्ण,
	अणु 0xD6, 0x0C पूर्ण,
	अणु 0xD7, 0x0C पूर्ण,
	अणु 0xC0, 0x05 पूर्ण,
	अणु 0xC1, 0x05 पूर्ण,
	अणु 0xD4, 0x06 पूर्ण,
	अणु 0xD5, 0x06 पूर्ण,
	अणु 0xCA, 0x07 पूर्ण,
	अणु 0xCB, 0x07 पूर्ण,
	अणु 0xDE, 0x08 पूर्ण,
	अणु 0xDF, 0x08 पूर्ण,
	अणु 0xB0, 0x02 पूर्ण,
	अणु 0xC0, 0x00 पूर्ण,
	अणु 0xC1, 0x0D पूर्ण,
	अणु 0xC2, 0x17 पूर्ण,
	अणु 0xC3, 0x26 पूर्ण,
	अणु 0xC4, 0x31 पूर्ण,
	अणु 0xC5, 0x1C पूर्ण,
	अणु 0xC6, 0x2C पूर्ण,
	अणु 0xC7, 0x33 पूर्ण,
	अणु 0xC8, 0x31 पूर्ण,
	अणु 0xC9, 0x37 पूर्ण,
	अणु 0xCA, 0x37 पूर्ण,
	अणु 0xCB, 0x37 पूर्ण,
	अणु 0xCC, 0x39 पूर्ण,
	अणु 0xCD, 0x2E पूर्ण,
	अणु 0xCE, 0x2F पूर्ण,
	अणु 0xCF, 0x2F पूर्ण,
	अणु 0xD0, 0x07 पूर्ण,
	अणु 0xD2, 0x00 पूर्ण,
	अणु 0xD3, 0x0D पूर्ण,
	अणु 0xD4, 0x17 पूर्ण,
	अणु 0xD5, 0x26 पूर्ण,
	अणु 0xD6, 0x31 पूर्ण,
	अणु 0xD7, 0x3F पूर्ण,
	अणु 0xD8, 0x3F पूर्ण,
	अणु 0xD9, 0x3F पूर्ण,
	अणु 0xDA, 0x3F पूर्ण,
	अणु 0xDB, 0x37 पूर्ण,
	अणु 0xDC, 0x37 पूर्ण,
	अणु 0xDD, 0x37 पूर्ण,
	अणु 0xDE, 0x39 पूर्ण,
	अणु 0xDF, 0x2E पूर्ण,
	अणु 0xE0, 0x2F पूर्ण,
	अणु 0xE1, 0x2F पूर्ण,
	अणु 0xE2, 0x07 पूर्ण,
	अणु 0xB0, 0x03 पूर्ण,
	अणु 0xC8, 0x0B पूर्ण,
	अणु 0xC9, 0x07 पूर्ण,
	अणु 0xC3, 0x00 पूर्ण,
	अणु 0xE7, 0x00 पूर्ण,
	अणु 0xC5, 0x2A पूर्ण,
	अणु 0xDE, 0x2A पूर्ण,
	अणु 0xCA, 0x43 पूर्ण,
	अणु 0xC9, 0x07 पूर्ण,
	अणु 0xE4, 0xC0 पूर्ण,
	अणु 0xE5, 0x0D पूर्ण,
	अणु 0xCB, 0x01 पूर्ण,
	अणु 0xBC, 0x01 पूर्ण,
	अणु 0xB0, 0x06 पूर्ण,
	अणु 0xB8, 0xA5 पूर्ण,
	अणु 0xC0, 0xA5 पूर्ण,
	अणु 0xC7, 0x0F पूर्ण,
	अणु 0xD5, 0x32 पूर्ण,
	अणु 0xB8, 0x00 पूर्ण,
	अणु 0xC0, 0x00 पूर्ण,
	अणु 0xBC, 0x00 पूर्ण,
	अणु 0xB0, 0x07 पूर्ण,
	अणु 0xB1, 0x00 पूर्ण,
	अणु 0xB2, 0x05 पूर्ण,
	अणु 0xB3, 0x10 पूर्ण,
	अणु 0xB4, 0x22 पूर्ण,
	अणु 0xB5, 0x36 पूर्ण,
	अणु 0xB6, 0x4A पूर्ण,
	अणु 0xB7, 0x6C पूर्ण,
	अणु 0xB8, 0x9A पूर्ण,
	अणु 0xB9, 0xD7 पूर्ण,
	अणु 0xBA, 0x17 पूर्ण,
	अणु 0xBB, 0x92 पूर्ण,
	अणु 0xBC, 0x15 पूर्ण,
	अणु 0xBD, 0x18 पूर्ण,
	अणु 0xBE, 0x8C पूर्ण,
	अणु 0xBF, 0x00 पूर्ण,
	अणु 0xC0, 0x3A पूर्ण,
	अणु 0xC1, 0x72 पूर्ण,
	अणु 0xC2, 0x8C पूर्ण,
	अणु 0xC3, 0xA5 पूर्ण,
	अणु 0xC4, 0xB1 पूर्ण,
	अणु 0xC5, 0xBE पूर्ण,
	अणु 0xC6, 0xCA पूर्ण,
	अणु 0xC7, 0xD1 पूर्ण,
	अणु 0xC8, 0xD4 पूर्ण,
	अणु 0xC9, 0x00 पूर्ण,
	अणु 0xCA, 0x00 पूर्ण,
	अणु 0xCB, 0x16 पूर्ण,
	अणु 0xCC, 0xAF पूर्ण,
	अणु 0xCD, 0xFF पूर्ण,
	अणु 0xCE, 0xFF पूर्ण,
	अणु 0xB0, 0x08 पूर्ण,
	अणु 0xB1, 0x04 पूर्ण,
	अणु 0xB2, 0x05 पूर्ण,
	अणु 0xB3, 0x11 पूर्ण,
	अणु 0xB4, 0x24 पूर्ण,
	अणु 0xB5, 0x39 पूर्ण,
	अणु 0xB6, 0x4E पूर्ण,
	अणु 0xB7, 0x72 पूर्ण,
	अणु 0xB8, 0xA3 पूर्ण,
	अणु 0xB9, 0xE1 पूर्ण,
	अणु 0xBA, 0x25 पूर्ण,
	अणु 0xBB, 0xA8 पूर्ण,
	अणु 0xBC, 0x2E पूर्ण,
	अणु 0xBD, 0x32 पूर्ण,
	अणु 0xBE, 0xAD पूर्ण,
	अणु 0xBF, 0x28 पूर्ण,
	अणु 0xC0, 0x63 पूर्ण,
	अणु 0xC1, 0x9B पूर्ण,
	अणु 0xC2, 0xB5 पूर्ण,
	अणु 0xC3, 0xCF पूर्ण,
	अणु 0xC4, 0xDB पूर्ण,
	अणु 0xC5, 0xE8 पूर्ण,
	अणु 0xC6, 0xF5 पूर्ण,
	अणु 0xC7, 0xFA पूर्ण,
	अणु 0xC8, 0xFC पूर्ण,
	अणु 0xC9, 0x00 पूर्ण,
	अणु 0xCA, 0x00 पूर्ण,
	अणु 0xCB, 0x16 पूर्ण,
	अणु 0xCC, 0xAF पूर्ण,
	अणु 0xCD, 0xFF पूर्ण,
	अणु 0xCE, 0xFF पूर्ण,
	अणु 0xB0, 0x09 पूर्ण,
	अणु 0xB1, 0x04 पूर्ण,
	अणु 0xB2, 0x04 पूर्ण,
	अणु 0xB3, 0x0F पूर्ण,
	अणु 0xB4, 0x22 पूर्ण,
	अणु 0xB5, 0x37 पूर्ण,
	अणु 0xB6, 0x4D पूर्ण,
	अणु 0xB7, 0x71 पूर्ण,
	अणु 0xB8, 0xA2 पूर्ण,
	अणु 0xB9, 0xE1 पूर्ण,
	अणु 0xBA, 0x26 पूर्ण,
	अणु 0xBB, 0xA9 पूर्ण,
	अणु 0xBC, 0x2F पूर्ण,
	अणु 0xBD, 0x33 पूर्ण,
	अणु 0xBE, 0xAC पूर्ण,
	अणु 0xBF, 0x24 पूर्ण,
	अणु 0xC0, 0x5D पूर्ण,
	अणु 0xC1, 0x94 पूर्ण,
	अणु 0xC2, 0xAC पूर्ण,
	अणु 0xC3, 0xC5 पूर्ण,
	अणु 0xC4, 0xD1 पूर्ण,
	अणु 0xC5, 0xDC पूर्ण,
	अणु 0xC6, 0xE8 पूर्ण,
	अणु 0xC7, 0xED पूर्ण,
	अणु 0xC8, 0xF0 पूर्ण,
	अणु 0xC9, 0x00 पूर्ण,
	अणु 0xCA, 0x00 पूर्ण,
	अणु 0xCB, 0x16 पूर्ण,
	अणु 0xCC, 0xAF पूर्ण,
	अणु 0xCD, 0xFF पूर्ण,
	अणु 0xCE, 0xFF पूर्ण,
	अणु 0xB0, 0x0A पूर्ण,
	अणु 0xB1, 0x00 पूर्ण,
	अणु 0xB2, 0x05 पूर्ण,
	अणु 0xB3, 0x10 पूर्ण,
	अणु 0xB4, 0x22 पूर्ण,
	अणु 0xB5, 0x36 पूर्ण,
	अणु 0xB6, 0x4A पूर्ण,
	अणु 0xB7, 0x6C पूर्ण,
	अणु 0xB8, 0x9A पूर्ण,
	अणु 0xB9, 0xD7 पूर्ण,
	अणु 0xBA, 0x17 पूर्ण,
	अणु 0xBB, 0x92 पूर्ण,
	अणु 0xBC, 0x15 पूर्ण,
	अणु 0xBD, 0x18 पूर्ण,
	अणु 0xBE, 0x8C पूर्ण,
	अणु 0xBF, 0x00 पूर्ण,
	अणु 0xC0, 0x3A पूर्ण,
	अणु 0xC1, 0x72 पूर्ण,
	अणु 0xC2, 0x8C पूर्ण,
	अणु 0xC3, 0xA5 पूर्ण,
	अणु 0xC4, 0xB1 पूर्ण,
	अणु 0xC5, 0xBE पूर्ण,
	अणु 0xC6, 0xCA पूर्ण,
	अणु 0xC7, 0xD1 पूर्ण,
	अणु 0xC8, 0xD4 पूर्ण,
	अणु 0xC9, 0x00 पूर्ण,
	अणु 0xCA, 0x00 पूर्ण,
	अणु 0xCB, 0x16 पूर्ण,
	अणु 0xCC, 0xAF पूर्ण,
	अणु 0xCD, 0xFF पूर्ण,
	अणु 0xCE, 0xFF पूर्ण,
	अणु 0xB0, 0x0B पूर्ण,
	अणु 0xB1, 0x04 पूर्ण,
	अणु 0xB2, 0x05 पूर्ण,
	अणु 0xB3, 0x11 पूर्ण,
	अणु 0xB4, 0x24 पूर्ण,
	अणु 0xB5, 0x39 पूर्ण,
	अणु 0xB6, 0x4E पूर्ण,
	अणु 0xB7, 0x72 पूर्ण,
	अणु 0xB8, 0xA3 पूर्ण,
	अणु 0xB9, 0xE1 पूर्ण,
	अणु 0xBA, 0x25 पूर्ण,
	अणु 0xBB, 0xA8 पूर्ण,
	अणु 0xBC, 0x2E पूर्ण,
	अणु 0xBD, 0x32 पूर्ण,
	अणु 0xBE, 0xAD पूर्ण,
	अणु 0xBF, 0x28 पूर्ण,
	अणु 0xC0, 0x63 पूर्ण,
	अणु 0xC1, 0x9B पूर्ण,
	अणु 0xC2, 0xB5 पूर्ण,
	अणु 0xC3, 0xCF पूर्ण,
	अणु 0xC4, 0xDB पूर्ण,
	अणु 0xC5, 0xE8 पूर्ण,
	अणु 0xC6, 0xF5 पूर्ण,
	अणु 0xC7, 0xFA पूर्ण,
	अणु 0xC8, 0xFC पूर्ण,
	अणु 0xC9, 0x00 पूर्ण,
	अणु 0xCA, 0x00 पूर्ण,
	अणु 0xCB, 0x16 पूर्ण,
	अणु 0xCC, 0xAF पूर्ण,
	अणु 0xCD, 0xFF पूर्ण,
	अणु 0xCE, 0xFF पूर्ण,
	अणु 0xB0, 0x0C पूर्ण,
	अणु 0xB1, 0x04 पूर्ण,
	अणु 0xB2, 0x04 पूर्ण,
	अणु 0xB3, 0x0F पूर्ण,
	अणु 0xB4, 0x22 पूर्ण,
	अणु 0xB5, 0x37 पूर्ण,
	अणु 0xB6, 0x4D पूर्ण,
	अणु 0xB7, 0x71 पूर्ण,
	अणु 0xB8, 0xA2 पूर्ण,
	अणु 0xB9, 0xE1 पूर्ण,
	अणु 0xBA, 0x26 पूर्ण,
	अणु 0xBB, 0xA9 पूर्ण,
	अणु 0xBC, 0x2F पूर्ण,
	अणु 0xBD, 0x33 पूर्ण,
	अणु 0xBE, 0xAC पूर्ण,
	अणु 0xBF, 0x24 पूर्ण,
	अणु 0xC0, 0x5D पूर्ण,
	अणु 0xC1, 0x94 पूर्ण,
	अणु 0xC2, 0xAC पूर्ण,
	अणु 0xC3, 0xC5 पूर्ण,
	अणु 0xC4, 0xD1 पूर्ण,
	अणु 0xC5, 0xDC पूर्ण,
	अणु 0xC6, 0xE8 पूर्ण,
	अणु 0xC7, 0xED पूर्ण,
	अणु 0xC8, 0xF0 पूर्ण,
	अणु 0xC9, 0x00 पूर्ण,
	अणु 0xCA, 0x00 पूर्ण,
	अणु 0xCB, 0x16 पूर्ण,
	अणु 0xCC, 0xAF पूर्ण,
	अणु 0xCD, 0xFF पूर्ण,
	अणु 0xCE, 0xFF पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा panel_desc boe_himax8279d10p_panel_desc = अणु
	.display_mode = &शेष_display_mode,
	.bpc = 8,
	.width_mm = 135,
	.height_mm = 216,
	.mode_flags = MIPI_DSI_MODE_VIDEO | MIPI_DSI_MODE_VIDEO_SYNC_PULSE |
			MIPI_DSI_CLOCK_NON_CONTINUOUS | MIPI_DSI_MODE_LPM,
	.क्रमmat = MIPI_DSI_FMT_RGB888,
	.lanes = 4,
	.on_cmds = boe_himax8279d10p_on_cmds,
	.on_cmds_num = 283,
पूर्ण;

अटल स्थिर काष्ठा of_device_id panel_of_match[] = अणु
	अणु
		.compatible = "boe,himax8279d8p",
		.data = &boe_himax8279d8p_panel_desc,
	पूर्ण,
	अणु
		.compatible = "boe,himax8279d10p",
		.data = &boe_himax8279d10p_panel_desc,
	पूर्ण,
	अणु
		/* sentinel */
	पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, panel_of_match);

अटल पूर्णांक panel_add(काष्ठा panel_info *pinfo)
अणु
	काष्ठा device *dev = &pinfo->link->dev;
	पूर्णांक ret;

	pinfo->pp18_gpio = devm_gpiod_get(dev, "pp18", GPIOD_OUT_HIGH);
	अगर (IS_ERR(pinfo->pp18_gpio)) अणु
		ret = PTR_ERR(pinfo->pp18_gpio);
		अगर (ret != -EPROBE_DEFER)
			dev_err(dev, "failed to get pp18 gpio: %d\n", ret);
		वापस ret;
	पूर्ण

	pinfo->pp33_gpio = devm_gpiod_get(dev, "pp33", GPIOD_OUT_HIGH);
	अगर (IS_ERR(pinfo->pp33_gpio)) अणु
		ret = PTR_ERR(pinfo->pp33_gpio);
		अगर (ret != -EPROBE_DEFER)
			dev_err(dev, "failed to get pp33 gpio: %d\n", ret);
		वापस ret;
	पूर्ण

	pinfo->enable_gpio = devm_gpiod_get(dev, "enable", GPIOD_OUT_HIGH);
	अगर (IS_ERR(pinfo->enable_gpio)) अणु
		ret = PTR_ERR(pinfo->enable_gpio);
		अगर (ret != -EPROBE_DEFER)
			dev_err(dev, "failed to get enable gpio: %d\n", ret);
		वापस ret;
	पूर्ण

	drm_panel_init(&pinfo->base, dev, &panel_funcs,
		       DRM_MODE_CONNECTOR_DSI);

	ret = drm_panel_of_backlight(&pinfo->base);
	अगर (ret)
		वापस ret;

	drm_panel_add(&pinfo->base);

	वापस 0;
पूर्ण

अटल पूर्णांक panel_probe(काष्ठा mipi_dsi_device *dsi)
अणु
	काष्ठा panel_info *pinfo;
	स्थिर काष्ठा panel_desc *desc;
	पूर्णांक err;

	pinfo = devm_kzalloc(&dsi->dev, माप(*pinfo), GFP_KERNEL);
	अगर (!pinfo)
		वापस -ENOMEM;

	desc = of_device_get_match_data(&dsi->dev);
	dsi->mode_flags = desc->mode_flags;
	dsi->क्रमmat = desc->क्रमmat;
	dsi->lanes = desc->lanes;
	pinfo->desc = desc;

	pinfo->link = dsi;
	mipi_dsi_set_drvdata(dsi, pinfo);

	err = panel_add(pinfo);
	अगर (err < 0)
		वापस err;

	err = mipi_dsi_attach(dsi);
	अगर (err < 0)
		drm_panel_हटाओ(&pinfo->base);

	वापस err;
पूर्ण

अटल पूर्णांक panel_हटाओ(काष्ठा mipi_dsi_device *dsi)
अणु
	काष्ठा panel_info *pinfo = mipi_dsi_get_drvdata(dsi);
	पूर्णांक err;

	err = boe_panel_disable(&pinfo->base);
	अगर (err < 0)
		dev_err(&dsi->dev, "failed to disable panel: %d\n", err);

	err = boe_panel_unprepare(&pinfo->base);
	अगर (err < 0)
		dev_err(&dsi->dev, "failed to unprepare panel: %d\n", err);

	err = mipi_dsi_detach(dsi);
	अगर (err < 0)
		dev_err(&dsi->dev, "failed to detach from DSI host: %d\n", err);

	drm_panel_हटाओ(&pinfo->base);

	वापस 0;
पूर्ण

अटल व्योम panel_shutकरोwn(काष्ठा mipi_dsi_device *dsi)
अणु
	काष्ठा panel_info *pinfo = mipi_dsi_get_drvdata(dsi);

	boe_panel_disable(&pinfo->base);
	boe_panel_unprepare(&pinfo->base);
पूर्ण

अटल काष्ठा mipi_dsi_driver panel_driver = अणु
	.driver = अणु
		.name = "panel-boe-himax8279d",
		.of_match_table = panel_of_match,
	पूर्ण,
	.probe = panel_probe,
	.हटाओ = panel_हटाओ,
	.shutकरोwn = panel_shutकरोwn,
पूर्ण;
module_mipi_dsi_driver(panel_driver);

MODULE_AUTHOR("Jerry Han <jerry.han.hq@gmail.com>");
MODULE_DESCRIPTION("Boe Himax8279d driver");
MODULE_LICENSE("GPL v2");
