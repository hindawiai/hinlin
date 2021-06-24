<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Raydium RM67191 MIPI-DSI panel driver
 *
 * Copyright 2019 NXP
 */

#समावेश <linux/backlight.h>
#समावेश <linux/delay.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/regulator/consumer.h>

#समावेश <video/mipi_display.h>
#समावेश <video/of_videomode.h>
#समावेश <video/videomode.h>

#समावेश <drm/drm_crtc.h>
#समावेश <drm/drm_mipi_dsi.h>
#समावेश <drm/drm_panel.h>

/* Panel specअगरic color-क्रमmat bits */
#घोषणा COL_FMT_16BPP 0x55
#घोषणा COL_FMT_18BPP 0x66
#घोषणा COL_FMT_24BPP 0x77

/* Write Manufacture Command Set Control */
#घोषणा WRMAUCCTR 0xFE

/* Manufacturer Command Set pages (CMD2) */
काष्ठा cmd_set_entry अणु
	u8 cmd;
	u8 param;
पूर्ण;

/*
 * There is no description in the Reference Manual about these commands.
 * We received them from venकरोr, so just use them as is.
 */
अटल स्थिर काष्ठा cmd_set_entry manufacturer_cmd_set[] = अणु
	अणु0xFE, 0x0Bपूर्ण,
	अणु0x28, 0x40पूर्ण,
	अणु0x29, 0x4Fपूर्ण,
	अणु0xFE, 0x0Eपूर्ण,
	अणु0x4B, 0x00पूर्ण,
	अणु0x4C, 0x0Fपूर्ण,
	अणु0x4D, 0x20पूर्ण,
	अणु0x4E, 0x40पूर्ण,
	अणु0x4F, 0x60पूर्ण,
	अणु0x50, 0xA0पूर्ण,
	अणु0x51, 0xC0पूर्ण,
	अणु0x52, 0xE0पूर्ण,
	अणु0x53, 0xFFपूर्ण,
	अणु0xFE, 0x0Dपूर्ण,
	अणु0x18, 0x08पूर्ण,
	अणु0x42, 0x00पूर्ण,
	अणु0x08, 0x41पूर्ण,
	अणु0x46, 0x02पूर्ण,
	अणु0x72, 0x09पूर्ण,
	अणु0xFE, 0x0Aपूर्ण,
	अणु0x24, 0x17पूर्ण,
	अणु0x04, 0x07पूर्ण,
	अणु0x1A, 0x0Cपूर्ण,
	अणु0x0F, 0x44पूर्ण,
	अणु0xFE, 0x04पूर्ण,
	अणु0x00, 0x0Cपूर्ण,
	अणु0x05, 0x08पूर्ण,
	अणु0x06, 0x08पूर्ण,
	अणु0x08, 0x08पूर्ण,
	अणु0x09, 0x08पूर्ण,
	अणु0x0A, 0xE6पूर्ण,
	अणु0x0B, 0x8Cपूर्ण,
	अणु0x1A, 0x12पूर्ण,
	अणु0x1E, 0xE0पूर्ण,
	अणु0x29, 0x93पूर्ण,
	अणु0x2A, 0x93पूर्ण,
	अणु0x2F, 0x02पूर्ण,
	अणु0x31, 0x02पूर्ण,
	अणु0x33, 0x05पूर्ण,
	अणु0x37, 0x2Dपूर्ण,
	अणु0x38, 0x2Dपूर्ण,
	अणु0x3A, 0x1Eपूर्ण,
	अणु0x3B, 0x1Eपूर्ण,
	अणु0x3D, 0x27पूर्ण,
	अणु0x3F, 0x80पूर्ण,
	अणु0x40, 0x40पूर्ण,
	अणु0x41, 0xE0पूर्ण,
	अणु0x4F, 0x2Fपूर्ण,
	अणु0x50, 0x1Eपूर्ण,
	अणु0xFE, 0x06पूर्ण,
	अणु0x00, 0xCCपूर्ण,
	अणु0x05, 0x05पूर्ण,
	अणु0x07, 0xA2पूर्ण,
	अणु0x08, 0xCCपूर्ण,
	अणु0x0D, 0x03पूर्ण,
	अणु0x0F, 0xA2पूर्ण,
	अणु0x32, 0xCCपूर्ण,
	अणु0x37, 0x05पूर्ण,
	अणु0x39, 0x83पूर्ण,
	अणु0x3A, 0xCCपूर्ण,
	अणु0x41, 0x04पूर्ण,
	अणु0x43, 0x83पूर्ण,
	अणु0x44, 0xCCपूर्ण,
	अणु0x49, 0x05पूर्ण,
	अणु0x4B, 0xA2पूर्ण,
	अणु0x4C, 0xCCपूर्ण,
	अणु0x51, 0x03पूर्ण,
	अणु0x53, 0xA2पूर्ण,
	अणु0x75, 0xCCपूर्ण,
	अणु0x7A, 0x03पूर्ण,
	अणु0x7C, 0x83पूर्ण,
	अणु0x7D, 0xCCपूर्ण,
	अणु0x82, 0x02पूर्ण,
	अणु0x84, 0x83पूर्ण,
	अणु0x85, 0xECपूर्ण,
	अणु0x86, 0x0Fपूर्ण,
	अणु0x87, 0xFFपूर्ण,
	अणु0x88, 0x00पूर्ण,
	अणु0x8A, 0x02पूर्ण,
	अणु0x8C, 0xA2पूर्ण,
	अणु0x8D, 0xEAपूर्ण,
	अणु0x8E, 0x01पूर्ण,
	अणु0x8F, 0xE8पूर्ण,
	अणु0xFE, 0x06पूर्ण,
	अणु0x90, 0x0Aपूर्ण,
	अणु0x92, 0x06पूर्ण,
	अणु0x93, 0xA0पूर्ण,
	अणु0x94, 0xA8पूर्ण,
	अणु0x95, 0xECपूर्ण,
	अणु0x96, 0x0Fपूर्ण,
	अणु0x97, 0xFFपूर्ण,
	अणु0x98, 0x00पूर्ण,
	अणु0x9A, 0x02पूर्ण,
	अणु0x9C, 0xA2पूर्ण,
	अणु0xAC, 0x04पूर्ण,
	अणु0xFE, 0x06पूर्ण,
	अणु0xB1, 0x12पूर्ण,
	अणु0xB2, 0x17पूर्ण,
	अणु0xB3, 0x17पूर्ण,
	अणु0xB4, 0x17पूर्ण,
	अणु0xB5, 0x17पूर्ण,
	अणु0xB6, 0x11पूर्ण,
	अणु0xB7, 0x08पूर्ण,
	अणु0xB8, 0x09पूर्ण,
	अणु0xB9, 0x06पूर्ण,
	अणु0xBA, 0x07पूर्ण,
	अणु0xBB, 0x17पूर्ण,
	अणु0xBC, 0x17पूर्ण,
	अणु0xBD, 0x17पूर्ण,
	अणु0xBE, 0x17पूर्ण,
	अणु0xBF, 0x17पूर्ण,
	अणु0xC0, 0x17पूर्ण,
	अणु0xC1, 0x17पूर्ण,
	अणु0xC2, 0x17पूर्ण,
	अणु0xC3, 0x17पूर्ण,
	अणु0xC4, 0x0Fपूर्ण,
	अणु0xC5, 0x0Eपूर्ण,
	अणु0xC6, 0x00पूर्ण,
	अणु0xC7, 0x01पूर्ण,
	अणु0xC8, 0x10पूर्ण,
	अणु0xFE, 0x06पूर्ण,
	अणु0x95, 0xECपूर्ण,
	अणु0x8D, 0xEEपूर्ण,
	अणु0x44, 0xECपूर्ण,
	अणु0x4C, 0xECपूर्ण,
	अणु0x32, 0xECपूर्ण,
	अणु0x3A, 0xECपूर्ण,
	अणु0x7D, 0xECपूर्ण,
	अणु0x75, 0xECपूर्ण,
	अणु0x00, 0xECपूर्ण,
	अणु0x08, 0xECपूर्ण,
	अणु0x85, 0xECपूर्ण,
	अणु0xA6, 0x21पूर्ण,
	अणु0xA7, 0x05पूर्ण,
	अणु0xA9, 0x06पूर्ण,
	अणु0x82, 0x06पूर्ण,
	अणु0x41, 0x06पूर्ण,
	अणु0x7A, 0x07पूर्ण,
	अणु0x37, 0x07पूर्ण,
	अणु0x05, 0x06पूर्ण,
	अणु0x49, 0x06पूर्ण,
	अणु0x0D, 0x04पूर्ण,
	अणु0x51, 0x04पूर्ण,
पूर्ण;

अटल स्थिर u32 rad_bus_क्रमmats[] = अणु
	MEDIA_BUS_FMT_RGB888_1X24,
	MEDIA_BUS_FMT_RGB666_1X18,
	MEDIA_BUS_FMT_RGB565_1X16,
पूर्ण;

अटल स्थिर u32 rad_bus_flags = DRM_BUS_FLAG_DE_LOW |
				 DRM_BUS_FLAG_PIXDATA_SAMPLE_POSEDGE;

काष्ठा rad_panel अणु
	काष्ठा drm_panel panel;
	काष्ठा mipi_dsi_device *dsi;

	काष्ठा gpio_desc *reset;
	काष्ठा backlight_device *backlight;

	काष्ठा regulator_bulk_data *supplies;
	अचिन्हित पूर्णांक num_supplies;

	bool prepared;
	bool enabled;
पूर्ण;

अटल स्थिर काष्ठा drm_display_mode शेष_mode = अणु
	.घड़ी = 132000,
	.hdisplay = 1080,
	.hsync_start = 1080 + 20,
	.hsync_end = 1080 + 20 + 2,
	.htotal = 1080 + 20 + 2 + 34,
	.vdisplay = 1920,
	.vsync_start = 1920 + 10,
	.vsync_end = 1920 + 10 + 2,
	.vtotal = 1920 + 10 + 2 + 4,
	.width_mm = 68,
	.height_mm = 121,
	.flags = DRM_MODE_FLAG_NHSYNC |
		 DRM_MODE_FLAG_NVSYNC,
पूर्ण;

अटल अंतरभूत काष्ठा rad_panel *to_rad_panel(काष्ठा drm_panel *panel)
अणु
	वापस container_of(panel, काष्ठा rad_panel, panel);
पूर्ण

अटल पूर्णांक rad_panel_push_cmd_list(काष्ठा mipi_dsi_device *dsi)
अणु
	माप_प्रकार i;
	माप_प्रकार count = ARRAY_SIZE(manufacturer_cmd_set);
	पूर्णांक ret = 0;

	क्रम (i = 0; i < count; i++) अणु
		स्थिर काष्ठा cmd_set_entry *entry = &manufacturer_cmd_set[i];
		u8 buffer[2] = अणु entry->cmd, entry->param पूर्ण;

		ret = mipi_dsi_generic_ग_लिखो(dsi, &buffer, माप(buffer));
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	वापस ret;
पूर्ण;

अटल पूर्णांक color_क्रमmat_from_dsi_क्रमmat(क्रमागत mipi_dsi_pixel_क्रमmat क्रमmat)
अणु
	चयन (क्रमmat) अणु
	हाल MIPI_DSI_FMT_RGB565:
		वापस COL_FMT_16BPP;
	हाल MIPI_DSI_FMT_RGB666:
	हाल MIPI_DSI_FMT_RGB666_PACKED:
		वापस COL_FMT_18BPP;
	हाल MIPI_DSI_FMT_RGB888:
		वापस COL_FMT_24BPP;
	शेष:
		वापस COL_FMT_24BPP; /* क्रम backward compatibility */
	पूर्ण
पूर्ण;

अटल पूर्णांक rad_panel_prepare(काष्ठा drm_panel *panel)
अणु
	काष्ठा rad_panel *rad = to_rad_panel(panel);
	पूर्णांक ret;

	अगर (rad->prepared)
		वापस 0;

	ret = regulator_bulk_enable(rad->num_supplies, rad->supplies);
	अगर (ret)
		वापस ret;

	अगर (rad->reset) अणु
		gpiod_set_value_cansleep(rad->reset, 1);
		usleep_range(3000, 5000);
		gpiod_set_value_cansleep(rad->reset, 0);
		usleep_range(18000, 20000);
	पूर्ण

	rad->prepared = true;

	वापस 0;
पूर्ण

अटल पूर्णांक rad_panel_unprepare(काष्ठा drm_panel *panel)
अणु
	काष्ठा rad_panel *rad = to_rad_panel(panel);
	पूर्णांक ret;

	अगर (!rad->prepared)
		वापस 0;

	/*
	 * Right after निश्चितing the reset, we need to release it, so that the
	 * touch driver can have an active connection with the touch controller
	 * even after the display is turned off.
	 */
	अगर (rad->reset) अणु
		gpiod_set_value_cansleep(rad->reset, 1);
		usleep_range(15000, 17000);
		gpiod_set_value_cansleep(rad->reset, 0);
	पूर्ण

	ret = regulator_bulk_disable(rad->num_supplies, rad->supplies);
	अगर (ret)
		वापस ret;

	rad->prepared = false;

	वापस 0;
पूर्ण

अटल पूर्णांक rad_panel_enable(काष्ठा drm_panel *panel)
अणु
	काष्ठा rad_panel *rad = to_rad_panel(panel);
	काष्ठा mipi_dsi_device *dsi = rad->dsi;
	काष्ठा device *dev = &dsi->dev;
	पूर्णांक color_क्रमmat = color_क्रमmat_from_dsi_क्रमmat(dsi->क्रमmat);
	पूर्णांक ret;

	अगर (rad->enabled)
		वापस 0;

	dsi->mode_flags |= MIPI_DSI_MODE_LPM;

	ret = rad_panel_push_cmd_list(dsi);
	अगर (ret < 0) अणु
		dev_err(dev, "Failed to send MCS (%d)\n", ret);
		जाओ fail;
	पूर्ण

	/* Select User Command Set table (CMD1) */
	ret = mipi_dsi_generic_ग_लिखो(dsi, (u8[])अणु WRMAUCCTR, 0x00 पूर्ण, 2);
	अगर (ret < 0)
		जाओ fail;

	/* Software reset */
	ret = mipi_dsi_dcs_soft_reset(dsi);
	अगर (ret < 0) अणु
		dev_err(dev, "Failed to do Software Reset (%d)\n", ret);
		जाओ fail;
	पूर्ण

	usleep_range(15000, 17000);

	/* Set DSI mode */
	ret = mipi_dsi_generic_ग_लिखो(dsi, (u8[])अणु 0xC2, 0x0B पूर्ण, 2);
	अगर (ret < 0) अणु
		dev_err(dev, "Failed to set DSI mode (%d)\n", ret);
		जाओ fail;
	पूर्ण
	/* Set tear ON */
	ret = mipi_dsi_dcs_set_tear_on(dsi, MIPI_DSI_DCS_TEAR_MODE_VBLANK);
	अगर (ret < 0) अणु
		dev_err(dev, "Failed to set tear ON (%d)\n", ret);
		जाओ fail;
	पूर्ण
	/* Set tear scanline */
	ret = mipi_dsi_dcs_set_tear_scanline(dsi, 0x380);
	अगर (ret < 0) अणु
		dev_err(dev, "Failed to set tear scanline (%d)\n", ret);
		जाओ fail;
	पूर्ण
	/* Set pixel क्रमmat */
	ret = mipi_dsi_dcs_set_pixel_क्रमmat(dsi, color_क्रमmat);
	dev_dbg(dev, "Interface color format set to 0x%x\n", color_क्रमmat);
	अगर (ret < 0) अणु
		dev_err(dev, "Failed to set pixel format (%d)\n", ret);
		जाओ fail;
	पूर्ण
	/* Exit sleep mode */
	ret = mipi_dsi_dcs_निकास_sleep_mode(dsi);
	अगर (ret < 0) अणु
		dev_err(dev, "Failed to exit sleep mode (%d)\n", ret);
		जाओ fail;
	पूर्ण

	usleep_range(5000, 7000);

	ret = mipi_dsi_dcs_set_display_on(dsi);
	अगर (ret < 0) अणु
		dev_err(dev, "Failed to set display ON (%d)\n", ret);
		जाओ fail;
	पूर्ण

	backlight_enable(rad->backlight);

	rad->enabled = true;

	वापस 0;

fail:
	gpiod_set_value_cansleep(rad->reset, 1);

	वापस ret;
पूर्ण

अटल पूर्णांक rad_panel_disable(काष्ठा drm_panel *panel)
अणु
	काष्ठा rad_panel *rad = to_rad_panel(panel);
	काष्ठा mipi_dsi_device *dsi = rad->dsi;
	काष्ठा device *dev = &dsi->dev;
	पूर्णांक ret;

	अगर (!rad->enabled)
		वापस 0;

	dsi->mode_flags |= MIPI_DSI_MODE_LPM;

	backlight_disable(rad->backlight);

	usleep_range(10000, 12000);

	ret = mipi_dsi_dcs_set_display_off(dsi);
	अगर (ret < 0) अणु
		dev_err(dev, "Failed to set display OFF (%d)\n", ret);
		वापस ret;
	पूर्ण

	usleep_range(5000, 10000);

	ret = mipi_dsi_dcs_enter_sleep_mode(dsi);
	अगर (ret < 0) अणु
		dev_err(dev, "Failed to enter sleep mode (%d)\n", ret);
		वापस ret;
	पूर्ण

	rad->enabled = false;

	वापस 0;
पूर्ण

अटल पूर्णांक rad_panel_get_modes(काष्ठा drm_panel *panel,
			       काष्ठा drm_connector *connector)
अणु
	काष्ठा drm_display_mode *mode;

	mode = drm_mode_duplicate(connector->dev, &शेष_mode);
	अगर (!mode) अणु
		dev_err(panel->dev, "failed to add mode %ux%u@%u\n",
			शेष_mode.hdisplay, शेष_mode.vdisplay,
			drm_mode_vrefresh(&शेष_mode));
		वापस -ENOMEM;
	पूर्ण

	drm_mode_set_name(mode);
	mode->type = DRM_MODE_TYPE_DRIVER | DRM_MODE_TYPE_PREFERRED;
	drm_mode_probed_add(connector, mode);

	connector->display_info.width_mm = mode->width_mm;
	connector->display_info.height_mm = mode->height_mm;
	connector->display_info.bus_flags = rad_bus_flags;

	drm_display_info_set_bus_क्रमmats(&connector->display_info,
					 rad_bus_क्रमmats,
					 ARRAY_SIZE(rad_bus_क्रमmats));
	वापस 1;
पूर्ण

अटल पूर्णांक rad_bl_get_brightness(काष्ठा backlight_device *bl)
अणु
	काष्ठा mipi_dsi_device *dsi = bl_get_data(bl);
	काष्ठा rad_panel *rad = mipi_dsi_get_drvdata(dsi);
	u16 brightness;
	पूर्णांक ret;

	अगर (!rad->prepared)
		वापस 0;

	dsi->mode_flags &= ~MIPI_DSI_MODE_LPM;

	ret = mipi_dsi_dcs_get_display_brightness(dsi, &brightness);
	अगर (ret < 0)
		वापस ret;

	bl->props.brightness = brightness;

	वापस brightness & 0xff;
पूर्ण

अटल पूर्णांक rad_bl_update_status(काष्ठा backlight_device *bl)
अणु
	काष्ठा mipi_dsi_device *dsi = bl_get_data(bl);
	काष्ठा rad_panel *rad = mipi_dsi_get_drvdata(dsi);
	पूर्णांक ret = 0;

	अगर (!rad->prepared)
		वापस 0;

	dsi->mode_flags &= ~MIPI_DSI_MODE_LPM;

	ret = mipi_dsi_dcs_set_display_brightness(dsi, bl->props.brightness);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा backlight_ops rad_bl_ops = अणु
	.update_status = rad_bl_update_status,
	.get_brightness = rad_bl_get_brightness,
पूर्ण;

अटल स्थिर काष्ठा drm_panel_funcs rad_panel_funcs = अणु
	.prepare = rad_panel_prepare,
	.unprepare = rad_panel_unprepare,
	.enable = rad_panel_enable,
	.disable = rad_panel_disable,
	.get_modes = rad_panel_get_modes,
पूर्ण;

अटल स्थिर अक्षर * स्थिर rad_supply_names[] = अणु
	"v3p3",
	"v1p8",
पूर्ण;

अटल पूर्णांक rad_init_regulators(काष्ठा rad_panel *rad)
अणु
	काष्ठा device *dev = &rad->dsi->dev;
	पूर्णांक i;

	rad->num_supplies = ARRAY_SIZE(rad_supply_names);
	rad->supplies = devm_kसुस्मृति(dev, rad->num_supplies,
				     माप(*rad->supplies), GFP_KERNEL);
	अगर (!rad->supplies)
		वापस -ENOMEM;

	क्रम (i = 0; i < rad->num_supplies; i++)
		rad->supplies[i].supply = rad_supply_names[i];

	वापस devm_regulator_bulk_get(dev, rad->num_supplies, rad->supplies);
पूर्ण;

अटल पूर्णांक rad_panel_probe(काष्ठा mipi_dsi_device *dsi)
अणु
	काष्ठा device *dev = &dsi->dev;
	काष्ठा device_node *np = dev->of_node;
	काष्ठा rad_panel *panel;
	काष्ठा backlight_properties bl_props;
	पूर्णांक ret;
	u32 video_mode;

	panel = devm_kzalloc(&dsi->dev, माप(*panel), GFP_KERNEL);
	अगर (!panel)
		वापस -ENOMEM;

	mipi_dsi_set_drvdata(dsi, panel);

	panel->dsi = dsi;

	dsi->क्रमmat = MIPI_DSI_FMT_RGB888;
	dsi->mode_flags =  MIPI_DSI_MODE_VIDEO_HSE | MIPI_DSI_MODE_VIDEO;

	ret = of_property_पढ़ो_u32(np, "video-mode", &video_mode);
	अगर (!ret) अणु
		चयन (video_mode) अणु
		हाल 0:
			/* burst mode */
			dsi->mode_flags |= MIPI_DSI_MODE_VIDEO_BURST;
			अवरोध;
		हाल 1:
			/* non-burst mode with sync event */
			अवरोध;
		हाल 2:
			/* non-burst mode with sync pulse */
			dsi->mode_flags |= MIPI_DSI_MODE_VIDEO_SYNC_PULSE;
			अवरोध;
		शेष:
			dev_warn(dev, "invalid video mode %d\n", video_mode);
			अवरोध;
		पूर्ण
	पूर्ण

	ret = of_property_पढ़ो_u32(np, "dsi-lanes", &dsi->lanes);
	अगर (ret) अणु
		dev_err(dev, "Failed to get dsi-lanes property (%d)\n", ret);
		वापस ret;
	पूर्ण

	panel->reset = devm_gpiod_get_optional(dev, "reset", GPIOD_OUT_LOW);
	अगर (IS_ERR(panel->reset))
		वापस PTR_ERR(panel->reset);

	स_रखो(&bl_props, 0, माप(bl_props));
	bl_props.type = BACKLIGHT_RAW;
	bl_props.brightness = 255;
	bl_props.max_brightness = 255;

	panel->backlight = devm_backlight_device_रेजिस्टर(dev, dev_name(dev),
							  dev, dsi, &rad_bl_ops,
							  &bl_props);
	अगर (IS_ERR(panel->backlight)) अणु
		ret = PTR_ERR(panel->backlight);
		dev_err(dev, "Failed to register backlight (%d)\n", ret);
		वापस ret;
	पूर्ण

	ret = rad_init_regulators(panel);
	अगर (ret)
		वापस ret;

	drm_panel_init(&panel->panel, dev, &rad_panel_funcs,
		       DRM_MODE_CONNECTOR_DSI);
	dev_set_drvdata(dev, panel);

	drm_panel_add(&panel->panel);

	ret = mipi_dsi_attach(dsi);
	अगर (ret)
		drm_panel_हटाओ(&panel->panel);

	वापस ret;
पूर्ण

अटल पूर्णांक rad_panel_हटाओ(काष्ठा mipi_dsi_device *dsi)
अणु
	काष्ठा rad_panel *rad = mipi_dsi_get_drvdata(dsi);
	काष्ठा device *dev = &dsi->dev;
	पूर्णांक ret;

	ret = mipi_dsi_detach(dsi);
	अगर (ret)
		dev_err(dev, "Failed to detach from host (%d)\n", ret);

	drm_panel_हटाओ(&rad->panel);

	वापस 0;
पूर्ण

अटल व्योम rad_panel_shutकरोwn(काष्ठा mipi_dsi_device *dsi)
अणु
	काष्ठा rad_panel *rad = mipi_dsi_get_drvdata(dsi);

	rad_panel_disable(&rad->panel);
	rad_panel_unprepare(&rad->panel);
पूर्ण

अटल स्थिर काष्ठा of_device_id rad_of_match[] = अणु
	अणु .compatible = "raydium,rm67191", पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, rad_of_match);

अटल काष्ठा mipi_dsi_driver rad_panel_driver = अणु
	.driver = अणु
		.name = "panel-raydium-rm67191",
		.of_match_table = rad_of_match,
	पूर्ण,
	.probe = rad_panel_probe,
	.हटाओ = rad_panel_हटाओ,
	.shutकरोwn = rad_panel_shutकरोwn,
पूर्ण;
module_mipi_dsi_driver(rad_panel_driver);

MODULE_AUTHOR("Robert Chiras <robert.chiras@nxp.com>");
MODULE_DESCRIPTION("DRM Driver for Raydium RM67191 MIPI DSI panel");
MODULE_LICENSE("GPL v2");
