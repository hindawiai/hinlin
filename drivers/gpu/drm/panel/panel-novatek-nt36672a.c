<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright (C) 2020 Linaro Ltd
 * Author: Sumit Semwal <sumit.semwal@linaro.org>
 *
 * This driver is क्रम the DSI पूर्णांकerface to panels using the NT36672A display driver IC
 * from Novatek.
 * Currently supported are the Tianma FHD+ panels found in some Xiaomi phones, including
 * some variants of the Poco F1 phone.
 *
 * Panels using the Novatek NT37762A IC should add appropriate configuration per-panel and
 * use this driver.
 */

#समावेश <linux/delay.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>

#समावेश <linux/gpio/consumer.h>
#समावेश <linux/pinctrl/consumer.h>
#समावेश <linux/regulator/consumer.h>

#समावेश <drm/drm_device.h>
#समावेश <drm/drm_mipi_dsi.h>
#समावेश <drm/drm_modes.h>
#समावेश <drm/drm_panel.h>

#समावेश <video/mipi_display.h>

काष्ठा nt36672a_panel_cmd अणु
	स्थिर अक्षर data[2];
पूर्ण;

अटल स्थिर अक्षर * स्थिर nt36672a_regulator_names[] = अणु
	"vddio",
	"vddpos",
	"vddneg",
पूर्ण;

अटल अचिन्हित दीर्घ स्थिर nt36672a_regulator_enable_loads[] = अणु
	62000,
	100000,
	100000
पूर्ण;

काष्ठा nt36672a_panel_desc अणु
	स्थिर काष्ठा drm_display_mode *display_mode;
	स्थिर अक्षर *panel_name;

	अचिन्हित पूर्णांक width_mm;
	अचिन्हित पूर्णांक height_mm;

	अचिन्हित दीर्घ mode_flags;
	क्रमागत mipi_dsi_pixel_क्रमmat क्रमmat;
	अचिन्हित पूर्णांक lanes;

	अचिन्हित पूर्णांक num_on_cmds_1;
	स्थिर काष्ठा nt36672a_panel_cmd *on_cmds_1;
	अचिन्हित पूर्णांक num_on_cmds_2;
	स्थिर काष्ठा nt36672a_panel_cmd *on_cmds_2;

	अचिन्हित पूर्णांक num_off_cmds;
	स्थिर काष्ठा nt36672a_panel_cmd *off_cmds;
पूर्ण;

काष्ठा nt36672a_panel अणु
	काष्ठा drm_panel base;
	काष्ठा mipi_dsi_device *link;
	स्थिर काष्ठा nt36672a_panel_desc *desc;

	काष्ठा regulator_bulk_data supplies[ARRAY_SIZE(nt36672a_regulator_names)];

	काष्ठा gpio_desc *reset_gpio;

	bool prepared;
पूर्ण;

अटल अंतरभूत काष्ठा nt36672a_panel *to_nt36672a_panel(काष्ठा drm_panel *panel)
अणु
	वापस container_of(panel, काष्ठा nt36672a_panel, base);
पूर्ण

अटल पूर्णांक nt36672a_send_cmds(काष्ठा drm_panel *panel, स्थिर काष्ठा nt36672a_panel_cmd *cmds,
			      पूर्णांक num)
अणु
	काष्ठा nt36672a_panel *pinfo = to_nt36672a_panel(panel);
	अचिन्हित पूर्णांक i;
	पूर्णांक err;

	क्रम (i = 0; i < num; i++) अणु
		स्थिर काष्ठा nt36672a_panel_cmd *cmd = &cmds[i];

		err = mipi_dsi_dcs_ग_लिखो(pinfo->link, cmd->data[0], cmd->data + 1, 1);

		अगर (err < 0)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक nt36672a_panel_घातer_off(काष्ठा drm_panel *panel)
अणु
	काष्ठा nt36672a_panel *pinfo = to_nt36672a_panel(panel);
	पूर्णांक ret = 0;

	gpiod_set_value(pinfo->reset_gpio, 1);

	ret = regulator_bulk_disable(ARRAY_SIZE(pinfo->supplies), pinfo->supplies);
	अगर (ret)
		dev_err(panel->dev, "regulator_bulk_disable failed %d\n", ret);

	वापस ret;
पूर्ण

अटल पूर्णांक nt36672a_panel_unprepare(काष्ठा drm_panel *panel)
अणु
	काष्ठा nt36672a_panel *pinfo = to_nt36672a_panel(panel);
	पूर्णांक ret;

	अगर (!pinfo->prepared)
		वापस 0;

	/* send off cmds */
	ret = nt36672a_send_cmds(panel, pinfo->desc->off_cmds,
				 pinfo->desc->num_off_cmds);

	अगर (ret < 0)
		dev_err(panel->dev, "failed to send DCS off cmds: %d\n", ret);

	ret = mipi_dsi_dcs_set_display_off(pinfo->link);
	अगर (ret < 0)
		dev_err(panel->dev, "set_display_off cmd failed ret = %d\n", ret);

	/* 120ms delay required here as per DCS spec */
	msleep(120);

	ret = mipi_dsi_dcs_enter_sleep_mode(pinfo->link);
	अगर (ret < 0)
		dev_err(panel->dev, "enter_sleep cmd failed ret = %d\n", ret);

	/* 0x3C = 60ms delay */
	msleep(60);

	ret = nt36672a_panel_घातer_off(panel);
	अगर (ret < 0)
		dev_err(panel->dev, "power_off failed ret = %d\n", ret);

	pinfo->prepared = false;

	वापस ret;
पूर्ण

अटल पूर्णांक nt36672a_panel_घातer_on(काष्ठा nt36672a_panel *pinfo)
अणु
	पूर्णांक ret;

	ret = regulator_bulk_enable(ARRAY_SIZE(pinfo->supplies), pinfo->supplies);
	अगर (ret < 0)
		वापस ret;

	/*
	 * As per करोwnstream kernel, Reset sequence of Tianma FHD panel requires the panel to
	 * be out of reset क्रम 10ms, followed by being held in reset क्रम 10ms. But क्रम Android
	 * AOSP, we needed to bump it upto 200ms otherwise we get white screen someबार.
	 * FIXME: Try to reduce this 200ms to a lesser value.
	 */
	gpiod_set_value(pinfo->reset_gpio, 1);
	msleep(200);
	gpiod_set_value(pinfo->reset_gpio, 0);
	msleep(200);

	वापस 0;
पूर्ण

अटल पूर्णांक nt36672a_panel_prepare(काष्ठा drm_panel *panel)
अणु
	काष्ठा nt36672a_panel *pinfo = to_nt36672a_panel(panel);
	पूर्णांक err;

	अगर (pinfo->prepared)
		वापस 0;

	err = nt36672a_panel_घातer_on(pinfo);
	अगर (err < 0)
		जाओ घातeroff;

	/* send first part of init cmds */
	err = nt36672a_send_cmds(panel, pinfo->desc->on_cmds_1,
				 pinfo->desc->num_on_cmds_1);

	अगर (err < 0) अणु
		dev_err(panel->dev, "failed to send DCS Init 1st Code: %d\n", err);
		जाओ घातeroff;
	पूर्ण

	err = mipi_dsi_dcs_निकास_sleep_mode(pinfo->link);
	अगर (err < 0) अणु
		dev_err(panel->dev, "failed to exit sleep mode: %d\n", err);
		जाओ घातeroff;
	पूर्ण

	/* 0x46 = 70 ms delay */
	msleep(70);

	err = mipi_dsi_dcs_set_display_on(pinfo->link);
	अगर (err < 0) अणु
		dev_err(panel->dev, "failed to Set Display ON: %d\n", err);
		जाओ घातeroff;
	पूर्ण

	/* Send rest of the init cmds */
	err = nt36672a_send_cmds(panel, pinfo->desc->on_cmds_2,
				 pinfo->desc->num_on_cmds_2);

	अगर (err < 0) अणु
		dev_err(panel->dev, "failed to send DCS Init 2nd Code: %d\n", err);
		जाओ घातeroff;
	पूर्ण

	msleep(120);

	pinfo->prepared = true;

	वापस 0;

घातeroff:
	gpiod_set_value(pinfo->reset_gpio, 0);
	वापस err;
पूर्ण

अटल पूर्णांक nt36672a_panel_get_modes(काष्ठा drm_panel *panel,
				    काष्ठा drm_connector *connector)
अणु
	काष्ठा nt36672a_panel *pinfo = to_nt36672a_panel(panel);
	स्थिर काष्ठा drm_display_mode *m = pinfo->desc->display_mode;
	काष्ठा drm_display_mode *mode;

	mode = drm_mode_duplicate(connector->dev, m);
	अगर (!mode) अणु
		dev_err(panel->dev, "failed to add mode %ux%u@%u\n", m->hdisplay,
			m->vdisplay, drm_mode_vrefresh(m));
		वापस -ENOMEM;
	पूर्ण

	connector->display_info.width_mm = pinfo->desc->width_mm;
	connector->display_info.height_mm = pinfo->desc->height_mm;

	drm_mode_set_name(mode);
	drm_mode_probed_add(connector, mode);

	वापस 1;
पूर्ण

अटल स्थिर काष्ठा drm_panel_funcs panel_funcs = अणु
	.unprepare = nt36672a_panel_unprepare,
	.prepare = nt36672a_panel_prepare,
	.get_modes = nt36672a_panel_get_modes,
पूर्ण;

अटल स्थिर काष्ठा nt36672a_panel_cmd tianma_fhd_video_on_cmds_1[] = अणु
	/* skin enhancement mode */
	अणु .data = अणु0xFF, 0x22पूर्ण पूर्ण,
	अणु .data = अणु0x00, 0x40पूर्ण पूर्ण,
	अणु .data = अणु0x01, 0xC0पूर्ण पूर्ण,
	अणु .data = अणु0x02, 0x40पूर्ण पूर्ण,
	अणु .data = अणु0x03, 0x40पूर्ण पूर्ण,
	अणु .data = अणु0x04, 0x40पूर्ण पूर्ण,
	अणु .data = अणु0x05, 0x40पूर्ण पूर्ण,
	अणु .data = अणु0x06, 0x40पूर्ण पूर्ण,
	अणु .data = अणु0x07, 0x40पूर्ण पूर्ण,
	अणु .data = अणु0x08, 0x40पूर्ण पूर्ण,
	अणु .data = अणु0x09, 0x40पूर्ण पूर्ण,
	अणु .data = अणु0x0A, 0x40पूर्ण पूर्ण,
	अणु .data = अणु0x0B, 0x40पूर्ण पूर्ण,
	अणु .data = अणु0x0C, 0x40पूर्ण पूर्ण,
	अणु .data = अणु0x0D, 0x40पूर्ण पूर्ण,
	अणु .data = अणु0x0E, 0x40पूर्ण पूर्ण,
	अणु .data = अणु0x0F, 0x40पूर्ण पूर्ण,
	अणु .data = अणु0x10, 0x40पूर्ण पूर्ण,
	अणु .data = अणु0x11, 0x50पूर्ण पूर्ण,
	अणु .data = अणु0x12, 0x60पूर्ण पूर्ण,
	अणु .data = अणु0x13, 0x70पूर्ण पूर्ण,
	अणु .data = अणु0x14, 0x58पूर्ण पूर्ण,
	अणु .data = अणु0x15, 0x68पूर्ण पूर्ण,
	अणु .data = अणु0x16, 0x78पूर्ण पूर्ण,
	अणु .data = अणु0x17, 0x77पूर्ण पूर्ण,
	अणु .data = अणु0x18, 0x39पूर्ण पूर्ण,
	अणु .data = अणु0x19, 0x2Dपूर्ण पूर्ण,
	अणु .data = अणु0x1A, 0x2Eपूर्ण पूर्ण,
	अणु .data = अणु0x1B, 0x32पूर्ण पूर्ण,
	अणु .data = अणु0x1C, 0x37पूर्ण पूर्ण,
	अणु .data = अणु0x1D, 0x3Aपूर्ण पूर्ण,
	अणु .data = अणु0x1E, 0x40पूर्ण पूर्ण,
	अणु .data = अणु0x1F, 0x40पूर्ण पूर्ण,
	अणु .data = अणु0x20, 0x40पूर्ण पूर्ण,
	अणु .data = अणु0x21, 0x40पूर्ण पूर्ण,
	अणु .data = अणु0x22, 0x40पूर्ण पूर्ण,
	अणु .data = अणु0x23, 0x40पूर्ण पूर्ण,
	अणु .data = अणु0x24, 0x40पूर्ण पूर्ण,
	अणु .data = अणु0x25, 0x40पूर्ण पूर्ण,
	अणु .data = अणु0x26, 0x40पूर्ण पूर्ण,
	अणु .data = अणु0x27, 0x40पूर्ण पूर्ण,
	अणु .data = अणु0x28, 0x40पूर्ण पूर्ण,
	अणु .data = अणु0x2D, 0x00पूर्ण पूर्ण,
	अणु .data = अणु0x2F, 0x40पूर्ण पूर्ण,
	अणु .data = अणु0x30, 0x40पूर्ण पूर्ण,
	अणु .data = अणु0x31, 0x40पूर्ण पूर्ण,
	अणु .data = अणु0x32, 0x40पूर्ण पूर्ण,
	अणु .data = अणु0x33, 0x40पूर्ण पूर्ण,
	अणु .data = अणु0x34, 0x40पूर्ण पूर्ण,
	अणु .data = अणु0x35, 0x40पूर्ण पूर्ण,
	अणु .data = अणु0x36, 0x40पूर्ण पूर्ण,
	अणु .data = अणु0x37, 0x40पूर्ण पूर्ण,
	अणु .data = अणु0x38, 0x40पूर्ण पूर्ण,
	अणु .data = अणु0x39, 0x40पूर्ण पूर्ण,
	अणु .data = अणु0x3A, 0x40पूर्ण पूर्ण,
	अणु .data = अणु0x3B, 0x40पूर्ण पूर्ण,
	अणु .data = अणु0x3D, 0x40पूर्ण पूर्ण,
	अणु .data = अणु0x3F, 0x40पूर्ण पूर्ण,
	अणु .data = अणु0x40, 0x40पूर्ण पूर्ण,
	अणु .data = अणु0x41, 0x40पूर्ण पूर्ण,
	अणु .data = अणु0x42, 0x40पूर्ण पूर्ण,
	अणु .data = अणु0x43, 0x40पूर्ण पूर्ण,
	अणु .data = अणु0x44, 0x40पूर्ण पूर्ण,
	अणु .data = अणु0x45, 0x40पूर्ण पूर्ण,
	अणु .data = अणु0x46, 0x40पूर्ण पूर्ण,
	अणु .data = अणु0x47, 0x40पूर्ण पूर्ण,
	अणु .data = अणु0x48, 0x40पूर्ण पूर्ण,
	अणु .data = अणु0x49, 0x40पूर्ण पूर्ण,
	अणु .data = अणु0x4A, 0x40पूर्ण पूर्ण,
	अणु .data = अणु0x4B, 0x40पूर्ण पूर्ण,
	अणु .data = अणु0x4C, 0x40पूर्ण पूर्ण,
	अणु .data = अणु0x4D, 0x40पूर्ण पूर्ण,
	अणु .data = अणु0x4E, 0x40पूर्ण पूर्ण,
	अणु .data = अणु0x4F, 0x40पूर्ण पूर्ण,
	अणु .data = अणु0x50, 0x40पूर्ण पूर्ण,
	अणु .data = अणु0x51, 0x40पूर्ण पूर्ण,
	अणु .data = अणु0x52, 0x40पूर्ण पूर्ण,
	अणु .data = अणु0x53, 0x01पूर्ण पूर्ण,
	अणु .data = अणु0x54, 0x01पूर्ण पूर्ण,
	अणु .data = अणु0x55, 0xFEपूर्ण पूर्ण,
	अणु .data = अणु0x56, 0x77पूर्ण पूर्ण,
	अणु .data = अणु0x58, 0xCDपूर्ण पूर्ण,
	अणु .data = अणु0x59, 0xD0पूर्ण पूर्ण,
	अणु .data = अणु0x5A, 0xD0पूर्ण पूर्ण,
	अणु .data = अणु0x5B, 0x50पूर्ण पूर्ण,
	अणु .data = अणु0x5C, 0x50पूर्ण पूर्ण,
	अणु .data = अणु0x5D, 0x50पूर्ण पूर्ण,
	अणु .data = अणु0x5E, 0x50पूर्ण पूर्ण,
	अणु .data = अणु0x5F, 0x50पूर्ण पूर्ण,
	अणु .data = अणु0x60, 0x50पूर्ण पूर्ण,
	अणु .data = अणु0x61, 0x50पूर्ण पूर्ण,
	अणु .data = अणु0x62, 0x50पूर्ण पूर्ण,
	अणु .data = अणु0x63, 0x50पूर्ण पूर्ण,
	अणु .data = अणु0x64, 0x50पूर्ण पूर्ण,
	अणु .data = अणु0x65, 0x50पूर्ण पूर्ण,
	अणु .data = अणु0x66, 0x50पूर्ण पूर्ण,
	अणु .data = अणु0x67, 0x50पूर्ण पूर्ण,
	अणु .data = अणु0x68, 0x50पूर्ण पूर्ण,
	अणु .data = अणु0x69, 0x50पूर्ण पूर्ण,
	अणु .data = अणु0x6A, 0x50पूर्ण पूर्ण,
	अणु .data = अणु0x6B, 0x50पूर्ण पूर्ण,
	अणु .data = अणु0x6C, 0x50पूर्ण पूर्ण,
	अणु .data = अणु0x6D, 0x50पूर्ण पूर्ण,
	अणु .data = अणु0x6E, 0x50पूर्ण पूर्ण,
	अणु .data = अणु0x6F, 0x50पूर्ण पूर्ण,
	अणु .data = अणु0x70, 0x07पूर्ण पूर्ण,
	अणु .data = अणु0x71, 0x00पूर्ण पूर्ण,
	अणु .data = अणु0x72, 0x00पूर्ण पूर्ण,
	अणु .data = अणु0x73, 0x00पूर्ण पूर्ण,
	अणु .data = अणु0x74, 0x06पूर्ण पूर्ण,
	अणु .data = अणु0x75, 0x0Cपूर्ण पूर्ण,
	अणु .data = अणु0x76, 0x03पूर्ण पूर्ण,
	अणु .data = अणु0x77, 0x09पूर्ण पूर्ण,
	अणु .data = अणु0x78, 0x0Fपूर्ण पूर्ण,
	अणु .data = अणु0x79, 0x68पूर्ण पूर्ण,
	अणु .data = अणु0x7A, 0x88पूर्ण पूर्ण,
	अणु .data = अणु0x7C, 0x80पूर्ण पूर्ण,
	अणु .data = अणु0x7D, 0x80पूर्ण पूर्ण,
	अणु .data = अणु0x7E, 0x80पूर्ण पूर्ण,
	अणु .data = अणु0x7F, 0x00पूर्ण पूर्ण,
	अणु .data = अणु0x80, 0x00पूर्ण पूर्ण,
	अणु .data = अणु0x81, 0x00पूर्ण पूर्ण,
	अणु .data = अणु0x83, 0x01पूर्ण पूर्ण,
	अणु .data = अणु0x84, 0x00पूर्ण पूर्ण,
	अणु .data = अणु0x85, 0x80पूर्ण पूर्ण,
	अणु .data = अणु0x86, 0x80पूर्ण पूर्ण,
	अणु .data = अणु0x87, 0x80पूर्ण पूर्ण,
	अणु .data = अणु0x88, 0x40पूर्ण पूर्ण,
	अणु .data = अणु0x89, 0x91पूर्ण पूर्ण,
	अणु .data = अणु0x8A, 0x98पूर्ण पूर्ण,
	अणु .data = अणु0x8B, 0x80पूर्ण पूर्ण,
	अणु .data = अणु0x8C, 0x80पूर्ण पूर्ण,
	अणु .data = अणु0x8D, 0x80पूर्ण पूर्ण,
	अणु .data = अणु0x8E, 0x80पूर्ण पूर्ण,
	अणु .data = अणु0x8F, 0x80पूर्ण पूर्ण,
	अणु .data = अणु0x90, 0x80पूर्ण पूर्ण,
	अणु .data = अणु0x91, 0x80पूर्ण पूर्ण,
	अणु .data = अणु0x92, 0x80पूर्ण पूर्ण,
	अणु .data = अणु0x93, 0x80पूर्ण पूर्ण,
	अणु .data = अणु0x94, 0x80पूर्ण पूर्ण,
	अणु .data = अणु0x95, 0x80पूर्ण पूर्ण,
	अणु .data = अणु0x96, 0x80पूर्ण पूर्ण,
	अणु .data = अणु0x97, 0x80पूर्ण पूर्ण,
	अणु .data = अणु0x98, 0x80पूर्ण पूर्ण,
	अणु .data = अणु0x99, 0x80पूर्ण पूर्ण,
	अणु .data = अणु0x9A, 0x80पूर्ण पूर्ण,
	अणु .data = अणु0x9B, 0x80पूर्ण पूर्ण,
	अणु .data = अणु0x9C, 0x80पूर्ण पूर्ण,
	अणु .data = अणु0x9D, 0x80पूर्ण पूर्ण,
	अणु .data = अणु0x9E, 0x80पूर्ण पूर्ण,
	अणु .data = अणु0x9F, 0x80पूर्ण पूर्ण,
	अणु .data = अणु0xA0, 0x8Aपूर्ण पूर्ण,
	अणु .data = अणु0xA2, 0x80पूर्ण पूर्ण,
	अणु .data = अणु0xA6, 0x80पूर्ण पूर्ण,
	अणु .data = अणु0xA7, 0x80पूर्ण पूर्ण,
	अणु .data = अणु0xA9, 0x80पूर्ण पूर्ण,
	अणु .data = अणु0xAA, 0x80पूर्ण पूर्ण,
	अणु .data = अणु0xAB, 0x80पूर्ण पूर्ण,
	अणु .data = अणु0xAC, 0x80पूर्ण पूर्ण,
	अणु .data = अणु0xAD, 0x80पूर्ण पूर्ण,
	अणु .data = अणु0xAE, 0x80पूर्ण पूर्ण,
	अणु .data = अणु0xAF, 0x80पूर्ण पूर्ण,
	अणु .data = अणु0xB7, 0x76पूर्ण पूर्ण,
	अणु .data = अणु0xB8, 0x76पूर्ण पूर्ण,
	अणु .data = अणु0xB9, 0x05पूर्ण पूर्ण,
	अणु .data = अणु0xBA, 0x0Dपूर्ण पूर्ण,
	अणु .data = अणु0xBB, 0x14पूर्ण पूर्ण,
	अणु .data = अणु0xBC, 0x0Fपूर्ण पूर्ण,
	अणु .data = अणु0xBD, 0x18पूर्ण पूर्ण,
	अणु .data = अणु0xBE, 0x1Fपूर्ण पूर्ण,
	अणु .data = अणु0xBF, 0x05पूर्ण पूर्ण,
	अणु .data = अणु0xC0, 0x0Dपूर्ण पूर्ण,
	अणु .data = अणु0xC1, 0x14पूर्ण पूर्ण,
	अणु .data = अणु0xC2, 0x03पूर्ण पूर्ण,
	अणु .data = अणु0xC3, 0x07पूर्ण पूर्ण,
	अणु .data = अणु0xC4, 0x0Aपूर्ण पूर्ण,
	अणु .data = अणु0xC5, 0xA0पूर्ण पूर्ण,
	अणु .data = अणु0xC6, 0x55पूर्ण पूर्ण,
	अणु .data = अणु0xC7, 0xFFपूर्ण पूर्ण,
	अणु .data = अणु0xC8, 0x39पूर्ण पूर्ण,
	अणु .data = अणु0xC9, 0x44पूर्ण पूर्ण,
	अणु .data = अणु0xCA, 0x12पूर्ण पूर्ण,
	अणु .data = अणु0xCD, 0x80पूर्ण पूर्ण,
	अणु .data = अणु0xDB, 0x80पूर्ण पूर्ण,
	अणु .data = अणु0xDC, 0x80पूर्ण पूर्ण,
	अणु .data = अणु0xDD, 0x80पूर्ण पूर्ण,
	अणु .data = अणु0xE0, 0x80पूर्ण पूर्ण,
	अणु .data = अणु0xE1, 0x80पूर्ण पूर्ण,
	अणु .data = अणु0xE2, 0x80पूर्ण पूर्ण,
	अणु .data = अणु0xE3, 0x80पूर्ण पूर्ण,
	अणु .data = अणु0xE4, 0x80पूर्ण पूर्ण,
	अणु .data = अणु0xE5, 0x40पूर्ण पूर्ण,
	अणु .data = अणु0xE6, 0x40पूर्ण पूर्ण,
	अणु .data = अणु0xE7, 0x40पूर्ण पूर्ण,
	अणु .data = अणु0xE8, 0x40पूर्ण पूर्ण,
	अणु .data = अणु0xE9, 0x40पूर्ण पूर्ण,
	अणु .data = अणु0xEA, 0x40पूर्ण पूर्ण,
	अणु .data = अणु0xEB, 0x40पूर्ण पूर्ण,
	अणु .data = अणु0xEC, 0x40पूर्ण पूर्ण,
	अणु .data = अणु0xED, 0x40पूर्ण पूर्ण,
	अणु .data = अणु0xEE, 0x40पूर्ण पूर्ण,
	अणु .data = अणु0xEF, 0x40पूर्ण पूर्ण,
	अणु .data = अणु0xF0, 0x40पूर्ण पूर्ण,
	अणु .data = अणु0xF1, 0x40पूर्ण पूर्ण,
	अणु .data = अणु0xF2, 0x40पूर्ण पूर्ण,
	अणु .data = अणु0xF3, 0x40पूर्ण पूर्ण,
	अणु .data = अणु0xF4, 0x40पूर्ण पूर्ण,
	अणु .data = अणु0xF5, 0x40पूर्ण पूर्ण,
	अणु .data = अणु0xF6, 0x40पूर्ण पूर्ण,
	अणु .data = अणु0xFB, 0x1पूर्ण पूर्ण,
	अणु .data = अणु0xFF, 0x23पूर्ण पूर्ण,
	अणु .data = अणु0xFB, 0x01पूर्ण पूर्ण,
	/* dimming enable */
	अणु .data = अणु0x01, 0x84पूर्ण पूर्ण,
	अणु .data = अणु0x05, 0x2Dपूर्ण पूर्ण,
	अणु .data = अणु0x06, 0x00पूर्ण पूर्ण,
	 /* resolution 1080*2246 */
	अणु .data = अणु0x11, 0x01पूर्ण पूर्ण,
	अणु .data = अणु0x12, 0x7Bपूर्ण पूर्ण,
	अणु .data = अणु0x15, 0x6Fपूर्ण पूर्ण,
	अणु .data = अणु0x16, 0x0Bपूर्ण पूर्ण,
	 /* UI mode */
	अणु .data = अणु0x29, 0x0Aपूर्ण पूर्ण,
	अणु .data = अणु0x30, 0xFFपूर्ण पूर्ण,
	अणु .data = अणु0x31, 0xFFपूर्ण पूर्ण,
	अणु .data = अणु0x32, 0xFFपूर्ण पूर्ण,
	अणु .data = अणु0x33, 0xFFपूर्ण पूर्ण,
	अणु .data = अणु0x34, 0xFFपूर्ण पूर्ण,
	अणु .data = अणु0x35, 0xFFपूर्ण पूर्ण,
	अणु .data = अणु0x36, 0xFFपूर्ण पूर्ण,
	अणु .data = अणु0x37, 0xFFपूर्ण पूर्ण,
	अणु .data = अणु0x38, 0xFCपूर्ण पूर्ण,
	अणु .data = अणु0x39, 0xF8पूर्ण पूर्ण,
	अणु .data = अणु0x3A, 0xF4पूर्ण पूर्ण,
	अणु .data = अणु0x3B, 0xF1पूर्ण पूर्ण,
	अणु .data = अणु0x3D, 0xEEपूर्ण पूर्ण,
	अणु .data = अणु0x3F, 0xEBपूर्ण पूर्ण,
	अणु .data = अणु0x40, 0xE8पूर्ण पूर्ण,
	अणु .data = अणु0x41, 0xE5पूर्ण पूर्ण,
	 /* STILL mode */
	अणु .data = अणु0x2A, 0x13पूर्ण पूर्ण,
	अणु .data = अणु0x45, 0xFFपूर्ण पूर्ण,
	अणु .data = अणु0x46, 0xFFपूर्ण पूर्ण,
	अणु .data = अणु0x47, 0xFFपूर्ण पूर्ण,
	अणु .data = अणु0x48, 0xFFपूर्ण पूर्ण,
	अणु .data = अणु0x49, 0xFFपूर्ण पूर्ण,
	अणु .data = अणु0x4A, 0xFFपूर्ण पूर्ण,
	अणु .data = अणु0x4B, 0xFFपूर्ण पूर्ण,
	अणु .data = अणु0x4C, 0xFFपूर्ण पूर्ण,
	अणु .data = अणु0x4D, 0xEDपूर्ण पूर्ण,
	अणु .data = अणु0x4E, 0xD5पूर्ण पूर्ण,
	अणु .data = अणु0x4F, 0xBFपूर्ण पूर्ण,
	अणु .data = अणु0x50, 0xA6पूर्ण पूर्ण,
	अणु .data = अणु0x51, 0x96पूर्ण पूर्ण,
	अणु .data = अणु0x52, 0x86पूर्ण पूर्ण,
	अणु .data = अणु0x53, 0x76पूर्ण पूर्ण,
	अणु .data = अणु0x54, 0x66पूर्ण पूर्ण,
	 /* MOVING mode */
	अणु .data = अणु0x2B, 0x0Eपूर्ण पूर्ण,
	अणु .data = अणु0x58, 0xFFपूर्ण पूर्ण,
	अणु .data = अणु0x59, 0xFFपूर्ण पूर्ण,
	अणु .data = अणु0x5A, 0xFFपूर्ण पूर्ण,
	अणु .data = अणु0x5B, 0xFFपूर्ण पूर्ण,
	अणु .data = अणु0x5C, 0xFFपूर्ण पूर्ण,
	अणु .data = अणु0x5D, 0xFFपूर्ण पूर्ण,
	अणु .data = अणु0x5E, 0xFFपूर्ण पूर्ण,
	अणु .data = अणु0x5F, 0xFFपूर्ण पूर्ण,
	अणु .data = अणु0x60, 0xF6पूर्ण पूर्ण,
	अणु .data = अणु0x61, 0xEAपूर्ण पूर्ण,
	अणु .data = अणु0x62, 0xE1पूर्ण पूर्ण,
	अणु .data = अणु0x63, 0xD8पूर्ण पूर्ण,
	अणु .data = अणु0x64, 0xCEपूर्ण पूर्ण,
	अणु .data = अणु0x65, 0xC3पूर्ण पूर्ण,
	अणु .data = अणु0x66, 0xBAपूर्ण पूर्ण,
	अणु .data = अणु0x67, 0xB3पूर्ण पूर्ण,
	अणु .data = अणु0xFF, 0x25पूर्ण पूर्ण,
	अणु .data = अणु0xFB, 0x01पूर्ण पूर्ण,
	अणु .data = अणु0x05, 0x04पूर्ण पूर्ण,
	अणु .data = अणु0xFF, 0x26पूर्ण पूर्ण,
	अणु .data = अणु0xFB, 0x01पूर्ण पूर्ण,
	अणु .data = अणु0x1C, 0xAFपूर्ण पूर्ण,
	अणु .data = अणु0xFF, 0x10पूर्ण पूर्ण,
	अणु .data = अणु0xFB, 0x01पूर्ण पूर्ण,
	अणु .data = अणु0x51, 0xFFपूर्ण पूर्ण,
	अणु .data = अणु0x53, 0x24पूर्ण पूर्ण,
	अणु .data = अणु0x55, 0x00पूर्ण पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा nt36672a_panel_cmd tianma_fhd_video_on_cmds_2[] = अणु
	अणु .data = अणु0xFF, 0x24पूर्ण पूर्ण,
	अणु .data = अणु0xFB, 0x01पूर्ण पूर्ण,
	अणु .data = अणु0xC3, 0x01पूर्ण पूर्ण,
	अणु .data = अणु0xC4, 0x54पूर्ण पूर्ण,
	अणु .data = अणु0xFF, 0x10पूर्ण पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा nt36672a_panel_cmd tianma_fhd_video_off_cmds[] = अणु
	अणु .data = अणु0xFF, 0x24पूर्ण पूर्ण,
	अणु .data = अणु0xFB, 0x01पूर्ण पूर्ण,
	अणु .data = अणु0xC3, 0x01पूर्ण पूर्ण,
	अणु .data = अणु0xFF, 0x10पूर्ण पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा drm_display_mode tianma_fhd_video_panel_शेष_mode = अणु
	.घड़ी		= 161331,

	.hdisplay	= 1080,
	.hsync_start	= 1080 + 40,
	.hsync_end	= 1080 + 40 + 20,
	.htotal		= 1080 + 40 + 20 + 44,

	.vdisplay	= 2246,
	.vsync_start	= 2246 + 15,
	.vsync_end	= 2246 + 15 + 2,
	.vtotal		= 2246 + 15 + 2 + 8,

	.type = DRM_MODE_TYPE_DRIVER | DRM_MODE_TYPE_PREFERRED,
पूर्ण;

अटल स्थिर काष्ठा nt36672a_panel_desc tianma_fhd_video_panel_desc = अणु
	.display_mode = &tianma_fhd_video_panel_शेष_mode,

	.width_mm = 68,
	.height_mm = 136,

	.mode_flags = MIPI_DSI_MODE_LPM | MIPI_DSI_MODE_VIDEO
			| MIPI_DSI_MODE_VIDEO_HSE
			| MIPI_DSI_CLOCK_NON_CONTINUOUS
			| MIPI_DSI_MODE_VIDEO_BURST,
	.क्रमmat = MIPI_DSI_FMT_RGB888,
	.lanes = 4,
	.on_cmds_1 = tianma_fhd_video_on_cmds_1,
	.num_on_cmds_1 = ARRAY_SIZE(tianma_fhd_video_on_cmds_1),
	.on_cmds_2 = tianma_fhd_video_on_cmds_2,
	.num_on_cmds_2 = ARRAY_SIZE(tianma_fhd_video_on_cmds_2),
	.off_cmds = tianma_fhd_video_off_cmds,
	.num_off_cmds = ARRAY_SIZE(tianma_fhd_video_off_cmds),
पूर्ण;

अटल पूर्णांक nt36672a_panel_add(काष्ठा nt36672a_panel *pinfo)
अणु
	काष्ठा device *dev = &pinfo->link->dev;
	पूर्णांक i, ret;

	क्रम (i = 0; i < ARRAY_SIZE(pinfo->supplies); i++)
		pinfo->supplies[i].supply = nt36672a_regulator_names[i];

	ret = devm_regulator_bulk_get(dev, ARRAY_SIZE(pinfo->supplies),
				      pinfo->supplies);
	अगर (ret < 0)
		वापस dev_err_probe(dev, ret, "failed to get regulators\n");

	क्रम (i = 0; i < ARRAY_SIZE(pinfo->supplies); i++) अणु
		ret = regulator_set_load(pinfo->supplies[i].consumer,
					 nt36672a_regulator_enable_loads[i]);
		अगर (ret)
			वापस  dev_err_probe(dev, ret, "failed to set regulator enable loads\n");
	पूर्ण

	pinfo->reset_gpio = devm_gpiod_get(dev, "reset", GPIOD_OUT_LOW);
	अगर (IS_ERR(pinfo->reset_gpio))
		वापस dev_err_probe(dev, PTR_ERR(pinfo->reset_gpio),
				     "failed to get reset gpio from DT\n");

	drm_panel_init(&pinfo->base, dev, &panel_funcs, DRM_MODE_CONNECTOR_DSI);

	drm_panel_add(&pinfo->base);

	वापस 0;
पूर्ण

अटल पूर्णांक nt36672a_panel_probe(काष्ठा mipi_dsi_device *dsi)
अणु
	काष्ठा nt36672a_panel *pinfo;
	स्थिर काष्ठा nt36672a_panel_desc *desc;
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

	err = nt36672a_panel_add(pinfo);
	अगर (err < 0)
		वापस err;

	वापस mipi_dsi_attach(dsi);
पूर्ण

अटल पूर्णांक nt36672a_panel_हटाओ(काष्ठा mipi_dsi_device *dsi)
अणु
	काष्ठा nt36672a_panel *pinfo = mipi_dsi_get_drvdata(dsi);
	पूर्णांक err;

	err = drm_panel_unprepare(&pinfo->base);
	अगर (err < 0)
		dev_err(&dsi->dev, "failed to unprepare panel: %d\n", err);

	err = drm_panel_disable(&pinfo->base);
	अगर (err < 0)
		dev_err(&dsi->dev, "failed to disable panel: %d\n", err);

	err = mipi_dsi_detach(dsi);
	अगर (err < 0)
		dev_err(&dsi->dev, "failed to detach from DSI host: %d\n", err);

	drm_panel_हटाओ(&pinfo->base);

	वापस 0;
पूर्ण

अटल व्योम nt36672a_panel_shutकरोwn(काष्ठा mipi_dsi_device *dsi)
अणु
	काष्ठा nt36672a_panel *pinfo = mipi_dsi_get_drvdata(dsi);

	drm_panel_disable(&pinfo->base);
	drm_panel_unprepare(&pinfo->base);
पूर्ण

अटल स्थिर काष्ठा of_device_id tianma_fhd_video_of_match[] = अणु
	अणु .compatible = "tianma,fhd-video", .data = &tianma_fhd_video_panel_desc पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, tianma_fhd_video_of_match);

अटल काष्ठा mipi_dsi_driver nt36672a_panel_driver = अणु
	.driver = अणु
		.name = "panel-tianma-nt36672a",
		.of_match_table = tianma_fhd_video_of_match,
	पूर्ण,
	.probe = nt36672a_panel_probe,
	.हटाओ = nt36672a_panel_हटाओ,
	.shutकरोwn = nt36672a_panel_shutकरोwn,
पूर्ण;
module_mipi_dsi_driver(nt36672a_panel_driver);

MODULE_AUTHOR("Sumit Semwal <sumit.semwal@linaro.org>");
MODULE_DESCRIPTION("NOVATEK NT36672A based MIPI-DSI LCD panel driver");
MODULE_LICENSE("GPL");
