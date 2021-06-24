<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Generic DSI Command Mode panel driver
 *
 * Copyright (C) 2013 Texas Instruments Incorporated - https://www.ti.com/
 * Author: Tomi Valkeinen <tomi.valkeinen@ti.com>
 */

#समावेश <linux/backlight.h>
#समावेश <linux/delay.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/regulator/consumer.h>

#समावेश <drm/drm_connector.h>
#समावेश <drm/drm_mipi_dsi.h>
#समावेश <drm/drm_modes.h>
#समावेश <drm/drm_panel.h>

#समावेश <video/mipi_display.h>

#घोषणा DCS_GET_ID1		0xda
#घोषणा DCS_GET_ID2		0xdb
#घोषणा DCS_GET_ID3		0xdc

#घोषणा DCS_REGULATOR_SUPPLY_NUM 2

अटल स्थिर काष्ठा of_device_id dsicm_of_match[];

काष्ठा dsic_panel_data अणु
	u32 xres;
	u32 yres;
	u32 refresh;
	u32 width_mm;
	u32 height_mm;
	u32 max_hs_rate;
	u32 max_lp_rate;
	bool te_support;
पूर्ण;

काष्ठा panel_drv_data अणु
	काष्ठा mipi_dsi_device *dsi;
	काष्ठा drm_panel panel;
	काष्ठा drm_display_mode mode;

	काष्ठा mutex lock;

	काष्ठा backlight_device *bldev;
	काष्ठा backlight_device *extbldev;

	अचिन्हित दीर्घ	hw_guard_end;	/* next value of jअगरfies when we can
					 * issue the next sleep in/out command
					 */
	अचिन्हित दीर्घ	hw_guard_रुको;	/* max guard समय in jअगरfies */

	स्थिर काष्ठा dsic_panel_data *panel_data;

	काष्ठा gpio_desc *reset_gpio;

	काष्ठा regulator_bulk_data supplies[DCS_REGULATOR_SUPPLY_NUM];

	bool use_dsi_backlight;

	/* runसमय variables */
	bool enabled;

	bool पूर्णांकro_prपूर्णांकed;
पूर्ण;

अटल अंतरभूत काष्ठा panel_drv_data *panel_to_ddata(काष्ठा drm_panel *panel)
अणु
	वापस container_of(panel, काष्ठा panel_drv_data, panel);
पूर्ण

अटल व्योम dsicm_bl_घातer(काष्ठा panel_drv_data *ddata, bool enable)
अणु
	काष्ठा backlight_device *backlight;

	अगर (ddata->bldev)
		backlight = ddata->bldev;
	अन्यथा अगर (ddata->extbldev)
		backlight = ddata->extbldev;
	अन्यथा
		वापस;

	अगर (enable) अणु
		backlight->props.fb_blank = FB_BLANK_UNBLANK;
		backlight->props.state = ~(BL_CORE_FBBLANK | BL_CORE_SUSPENDED);
		backlight->props.घातer = FB_BLANK_UNBLANK;
	पूर्ण अन्यथा अणु
		backlight->props.fb_blank = FB_BLANK_NORMAL;
		backlight->props.घातer = FB_BLANK_POWERDOWN;
		backlight->props.state |= BL_CORE_FBBLANK | BL_CORE_SUSPENDED;
	पूर्ण

	backlight_update_status(backlight);
पूर्ण

अटल व्योम hw_guard_start(काष्ठा panel_drv_data *ddata, पूर्णांक guard_msec)
अणु
	ddata->hw_guard_रुको = msecs_to_jअगरfies(guard_msec);
	ddata->hw_guard_end = jअगरfies + ddata->hw_guard_रुको;
पूर्ण

अटल व्योम hw_guard_रुको(काष्ठा panel_drv_data *ddata)
अणु
	अचिन्हित दीर्घ रुको = ddata->hw_guard_end - jअगरfies;

	अगर ((दीर्घ)रुको > 0 && रुको <= ddata->hw_guard_रुको) अणु
		set_current_state(TASK_UNINTERRUPTIBLE);
		schedule_समयout(रुको);
	पूर्ण
पूर्ण

अटल पूर्णांक dsicm_dcs_पढ़ो_1(काष्ठा panel_drv_data *ddata, u8 dcs_cmd, u8 *data)
अणु
	वापस mipi_dsi_dcs_पढ़ो(ddata->dsi, dcs_cmd, data, 1);
पूर्ण

अटल पूर्णांक dsicm_dcs_ग_लिखो_1(काष्ठा panel_drv_data *ddata, u8 dcs_cmd, u8 param)
अणु
	वापस mipi_dsi_dcs_ग_लिखो(ddata->dsi, dcs_cmd, &param, 1);
पूर्ण

अटल पूर्णांक dsicm_sleep_in(काष्ठा panel_drv_data *ddata)

अणु
	पूर्णांक r;

	hw_guard_रुको(ddata);

	r = mipi_dsi_dcs_enter_sleep_mode(ddata->dsi);
	अगर (r)
		वापस r;

	hw_guard_start(ddata, 120);

	usleep_range(5000, 10000);

	वापस 0;
पूर्ण

अटल पूर्णांक dsicm_sleep_out(काष्ठा panel_drv_data *ddata)
अणु
	पूर्णांक r;

	hw_guard_रुको(ddata);

	r = mipi_dsi_dcs_निकास_sleep_mode(ddata->dsi);
	अगर (r)
		वापस r;

	hw_guard_start(ddata, 120);

	usleep_range(5000, 10000);

	वापस 0;
पूर्ण

अटल पूर्णांक dsicm_get_id(काष्ठा panel_drv_data *ddata, u8 *id1, u8 *id2, u8 *id3)
अणु
	पूर्णांक r;

	r = dsicm_dcs_पढ़ो_1(ddata, DCS_GET_ID1, id1);
	अगर (r)
		वापस r;
	r = dsicm_dcs_पढ़ो_1(ddata, DCS_GET_ID2, id2);
	अगर (r)
		वापस r;
	r = dsicm_dcs_पढ़ो_1(ddata, DCS_GET_ID3, id3);
	अगर (r)
		वापस r;

	वापस 0;
पूर्ण

अटल पूर्णांक dsicm_set_update_winकरोw(काष्ठा panel_drv_data *ddata)
अणु
	काष्ठा mipi_dsi_device *dsi = ddata->dsi;
	पूर्णांक r;

	r = mipi_dsi_dcs_set_column_address(dsi, 0, ddata->mode.hdisplay - 1);
	अगर (r < 0)
		वापस r;

	r = mipi_dsi_dcs_set_page_address(dsi, 0, ddata->mode.vdisplay - 1);
	अगर (r < 0)
		वापस r;

	वापस 0;
पूर्ण

अटल पूर्णांक dsicm_bl_update_status(काष्ठा backlight_device *dev)
अणु
	काष्ठा panel_drv_data *ddata = dev_get_drvdata(&dev->dev);
	पूर्णांक r = 0;
	पूर्णांक level;

	अगर (dev->props.fb_blank == FB_BLANK_UNBLANK &&
			dev->props.घातer == FB_BLANK_UNBLANK)
		level = dev->props.brightness;
	अन्यथा
		level = 0;

	dev_dbg(&ddata->dsi->dev, "update brightness to %d\n", level);

	mutex_lock(&ddata->lock);

	अगर (ddata->enabled)
		r = dsicm_dcs_ग_लिखो_1(ddata, MIPI_DCS_SET_DISPLAY_BRIGHTNESS,
				      level);

	mutex_unlock(&ddata->lock);

	वापस r;
पूर्ण

अटल पूर्णांक dsicm_bl_get_पूर्णांकensity(काष्ठा backlight_device *dev)
अणु
	अगर (dev->props.fb_blank == FB_BLANK_UNBLANK &&
			dev->props.घातer == FB_BLANK_UNBLANK)
		वापस dev->props.brightness;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा backlight_ops dsicm_bl_ops = अणु
	.get_brightness = dsicm_bl_get_पूर्णांकensity,
	.update_status  = dsicm_bl_update_status,
पूर्ण;

अटल sमाप_प्रकार num_dsi_errors_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा panel_drv_data *ddata = dev_get_drvdata(dev);
	u8 errors = 0;
	पूर्णांक r = -ENODEV;

	mutex_lock(&ddata->lock);

	अगर (ddata->enabled)
		r = dsicm_dcs_पढ़ो_1(ddata, MIPI_DCS_GET_ERROR_COUNT_ON_DSI, &errors);

	mutex_unlock(&ddata->lock);

	अगर (r)
		वापस r;

	वापस snम_लिखो(buf, PAGE_SIZE, "%d\n", errors);
पूर्ण

अटल sमाप_प्रकार hw_revision_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा panel_drv_data *ddata = dev_get_drvdata(dev);
	u8 id1, id2, id3;
	पूर्णांक r = -ENODEV;

	mutex_lock(&ddata->lock);

	अगर (ddata->enabled)
		r = dsicm_get_id(ddata, &id1, &id2, &id3);

	mutex_unlock(&ddata->lock);

	अगर (r)
		वापस r;

	वापस snम_लिखो(buf, PAGE_SIZE, "%02x.%02x.%02x\n", id1, id2, id3);
पूर्ण

अटल DEVICE_ATTR_RO(num_dsi_errors);
अटल DEVICE_ATTR_RO(hw_revision);

अटल काष्ठा attribute *dsicm_attrs[] = अणु
	&dev_attr_num_dsi_errors.attr,
	&dev_attr_hw_revision.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group dsicm_attr_group = अणु
	.attrs = dsicm_attrs,
पूर्ण;

अटल व्योम dsicm_hw_reset(काष्ठा panel_drv_data *ddata)
अणु
	gpiod_set_value(ddata->reset_gpio, 1);
	udelay(10);
	/* reset the panel */
	gpiod_set_value(ddata->reset_gpio, 0);
	/* निश्चित reset */
	udelay(10);
	gpiod_set_value(ddata->reset_gpio, 1);
	/* रुको after releasing reset */
	usleep_range(5000, 10000);
पूर्ण

अटल पूर्णांक dsicm_घातer_on(काष्ठा panel_drv_data *ddata)
अणु
	u8 id1, id2, id3;
	पूर्णांक r;

	dsicm_hw_reset(ddata);

	ddata->dsi->mode_flags |= MIPI_DSI_MODE_LPM;

	r = dsicm_sleep_out(ddata);
	अगर (r)
		जाओ err;

	r = dsicm_get_id(ddata, &id1, &id2, &id3);
	अगर (r)
		जाओ err;

	r = dsicm_dcs_ग_लिखो_1(ddata, MIPI_DCS_SET_DISPLAY_BRIGHTNESS, 0xff);
	अगर (r)
		जाओ err;

	r = dsicm_dcs_ग_लिखो_1(ddata, MIPI_DCS_WRITE_CONTROL_DISPLAY,
			(1<<2) | (1<<5));	/* BL | BCTRL */
	अगर (r)
		जाओ err;

	r = mipi_dsi_dcs_set_pixel_क्रमmat(ddata->dsi, MIPI_DCS_PIXEL_FMT_24BIT);
	अगर (r)
		जाओ err;

	r = dsicm_set_update_winकरोw(ddata);
	अगर (r)
		जाओ err;

	r = mipi_dsi_dcs_set_display_on(ddata->dsi);
	अगर (r)
		जाओ err;

	अगर (ddata->panel_data->te_support) अणु
		r = mipi_dsi_dcs_set_tear_on(ddata->dsi, MIPI_DSI_DCS_TEAR_MODE_VBLANK);
		अगर (r)
			जाओ err;
	पूर्ण

	/* possible panel bug */
	msleep(100);

	ddata->enabled = true;

	अगर (!ddata->पूर्णांकro_prपूर्णांकed) अणु
		dev_info(&ddata->dsi->dev, "panel revision %02x.%02x.%02x\n",
			id1, id2, id3);
		ddata->पूर्णांकro_prपूर्णांकed = true;
	पूर्ण

	ddata->dsi->mode_flags &= ~MIPI_DSI_MODE_LPM;

	वापस 0;
err:
	dev_err(&ddata->dsi->dev, "error while enabling panel, issuing HW reset\n");

	dsicm_hw_reset(ddata);

	वापस r;
पूर्ण

अटल पूर्णांक dsicm_घातer_off(काष्ठा panel_drv_data *ddata)
अणु
	पूर्णांक r;

	ddata->enabled = false;

	r = mipi_dsi_dcs_set_display_off(ddata->dsi);
	अगर (!r)
		r = dsicm_sleep_in(ddata);

	अगर (r) अणु
		dev_err(&ddata->dsi->dev,
				"error disabling panel, issuing HW reset\n");
		dsicm_hw_reset(ddata);
	पूर्ण

	वापस r;
पूर्ण

अटल पूर्णांक dsicm_prepare(काष्ठा drm_panel *panel)
अणु
	काष्ठा panel_drv_data *ddata = panel_to_ddata(panel);
	पूर्णांक r;

	r = regulator_bulk_enable(ARRAY_SIZE(ddata->supplies), ddata->supplies);
	अगर (r)
		dev_err(&ddata->dsi->dev, "failed to enable supplies: %d\n", r);

	वापस r;
पूर्ण

अटल पूर्णांक dsicm_enable(काष्ठा drm_panel *panel)
अणु
	काष्ठा panel_drv_data *ddata = panel_to_ddata(panel);
	पूर्णांक r;

	mutex_lock(&ddata->lock);

	r = dsicm_घातer_on(ddata);
	अगर (r)
		जाओ err;

	mutex_unlock(&ddata->lock);

	dsicm_bl_घातer(ddata, true);

	वापस 0;
err:
	dev_err(&ddata->dsi->dev, "enable failed (%d)\n", r);
	mutex_unlock(&ddata->lock);
	वापस r;
पूर्ण

अटल पूर्णांक dsicm_unprepare(काष्ठा drm_panel *panel)
अणु
	काष्ठा panel_drv_data *ddata = panel_to_ddata(panel);
	पूर्णांक r;

	r = regulator_bulk_disable(ARRAY_SIZE(ddata->supplies), ddata->supplies);
	अगर (r)
		dev_err(&ddata->dsi->dev, "failed to disable supplies: %d\n", r);

	वापस r;
पूर्ण

अटल पूर्णांक dsicm_disable(काष्ठा drm_panel *panel)
अणु
	काष्ठा panel_drv_data *ddata = panel_to_ddata(panel);
	पूर्णांक r;

	dsicm_bl_घातer(ddata, false);

	mutex_lock(&ddata->lock);

	r = dsicm_घातer_off(ddata);

	mutex_unlock(&ddata->lock);

	वापस r;
पूर्ण

अटल पूर्णांक dsicm_get_modes(काष्ठा drm_panel *panel,
			   काष्ठा drm_connector *connector)
अणु
	काष्ठा panel_drv_data *ddata = panel_to_ddata(panel);
	काष्ठा drm_display_mode *mode;

	mode = drm_mode_duplicate(connector->dev, &ddata->mode);
	अगर (!mode) अणु
		dev_err(&ddata->dsi->dev, "failed to add mode %ux%ux@%u kHz\n",
			ddata->mode.hdisplay, ddata->mode.vdisplay,
			ddata->mode.घड़ी);
		वापस -ENOMEM;
	पूर्ण

	connector->display_info.width_mm = ddata->panel_data->width_mm;
	connector->display_info.height_mm = ddata->panel_data->height_mm;

	drm_mode_probed_add(connector, mode);

	वापस 1;
पूर्ण

अटल स्थिर काष्ठा drm_panel_funcs dsicm_panel_funcs = अणु
	.unprepare = dsicm_unprepare,
	.disable = dsicm_disable,
	.prepare = dsicm_prepare,
	.enable = dsicm_enable,
	.get_modes = dsicm_get_modes,
पूर्ण;

अटल पूर्णांक dsicm_probe_of(काष्ठा mipi_dsi_device *dsi)
अणु
	काष्ठा backlight_device *backlight;
	काष्ठा panel_drv_data *ddata = mipi_dsi_get_drvdata(dsi);
	पूर्णांक err;
	काष्ठा drm_display_mode *mode = &ddata->mode;

	ddata->reset_gpio = devm_gpiod_get(&dsi->dev, "reset", GPIOD_OUT_LOW);
	अगर (IS_ERR(ddata->reset_gpio)) अणु
		err = PTR_ERR(ddata->reset_gpio);
		dev_err(&dsi->dev, "reset gpio request failed: %d", err);
		वापस err;
	पूर्ण

	mode->hdisplay = mode->hsync_start = mode->hsync_end = mode->htotal =
		ddata->panel_data->xres;
	mode->vdisplay = mode->vsync_start = mode->vsync_end = mode->vtotal =
		ddata->panel_data->yres;
	mode->घड़ी = ddata->panel_data->xres * ddata->panel_data->yres *
		ddata->panel_data->refresh / 1000;
	mode->width_mm = ddata->panel_data->width_mm;
	mode->height_mm = ddata->panel_data->height_mm;
	mode->type = DRM_MODE_TYPE_DRIVER | DRM_MODE_TYPE_PREFERRED;
	drm_mode_set_name(mode);

	ddata->supplies[0].supply = "vpnl";
	ddata->supplies[1].supply = "vddi";
	err = devm_regulator_bulk_get(&dsi->dev, ARRAY_SIZE(ddata->supplies),
				      ddata->supplies);
	अगर (err)
		वापस err;

	backlight = devm_of_find_backlight(&dsi->dev);
	अगर (IS_ERR(backlight))
		वापस PTR_ERR(backlight);

	/* If no backlight device is found assume native backlight support */
	अगर (backlight)
		ddata->extbldev = backlight;
	अन्यथा
		ddata->use_dsi_backlight = true;

	वापस 0;
पूर्ण

अटल पूर्णांक dsicm_probe(काष्ठा mipi_dsi_device *dsi)
अणु
	काष्ठा panel_drv_data *ddata;
	काष्ठा backlight_device *bldev = शून्य;
	काष्ठा device *dev = &dsi->dev;
	पूर्णांक r;

	dev_dbg(dev, "probe\n");

	ddata = devm_kzalloc(dev, माप(*ddata), GFP_KERNEL);
	अगर (!ddata)
		वापस -ENOMEM;

	mipi_dsi_set_drvdata(dsi, ddata);
	ddata->dsi = dsi;

	ddata->panel_data = of_device_get_match_data(dev);
	अगर (!ddata->panel_data)
		वापस -ENODEV;

	r = dsicm_probe_of(dsi);
	अगर (r)
		वापस r;

	mutex_init(&ddata->lock);

	dsicm_hw_reset(ddata);

	drm_panel_init(&ddata->panel, dev, &dsicm_panel_funcs,
		       DRM_MODE_CONNECTOR_DSI);

	अगर (ddata->use_dsi_backlight) अणु
		काष्ठा backlight_properties props = अणु 0 पूर्ण;
		props.max_brightness = 255;
		props.type = BACKLIGHT_RAW;

		bldev = devm_backlight_device_रेजिस्टर(dev, dev_name(dev),
			dev, ddata, &dsicm_bl_ops, &props);
		अगर (IS_ERR(bldev)) अणु
			r = PTR_ERR(bldev);
			जाओ err_bl;
		पूर्ण

		ddata->bldev = bldev;
	पूर्ण

	r = sysfs_create_group(&dev->kobj, &dsicm_attr_group);
	अगर (r) अणु
		dev_err(dev, "failed to create sysfs files\n");
		जाओ err_bl;
	पूर्ण

	dsi->lanes = 2;
	dsi->क्रमmat = MIPI_DSI_FMT_RGB888;
	dsi->mode_flags = MIPI_DSI_CLOCK_NON_CONTINUOUS |
			  MIPI_DSI_MODE_EOT_PACKET;
	dsi->hs_rate = ddata->panel_data->max_hs_rate;
	dsi->lp_rate = ddata->panel_data->max_lp_rate;

	drm_panel_add(&ddata->panel);

	r = mipi_dsi_attach(dsi);
	अगर (r < 0)
		जाओ err_dsi_attach;

	वापस 0;

err_dsi_attach:
	drm_panel_हटाओ(&ddata->panel);
	sysfs_हटाओ_group(&dsi->dev.kobj, &dsicm_attr_group);
err_bl:
	अगर (ddata->extbldev)
		put_device(&ddata->extbldev->dev);

	वापस r;
पूर्ण

अटल पूर्णांक dsicm_हटाओ(काष्ठा mipi_dsi_device *dsi)
अणु
	काष्ठा panel_drv_data *ddata = mipi_dsi_get_drvdata(dsi);

	dev_dbg(&dsi->dev, "remove\n");

	mipi_dsi_detach(dsi);

	drm_panel_हटाओ(&ddata->panel);

	sysfs_हटाओ_group(&dsi->dev.kobj, &dsicm_attr_group);

	अगर (ddata->extbldev)
		put_device(&ddata->extbldev->dev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dsic_panel_data taal_data = अणु
	.xres = 864,
	.yres = 480,
	.refresh = 60,
	.width_mm = 0,
	.height_mm = 0,
	.max_hs_rate = 300000000,
	.max_lp_rate = 10000000,
	.te_support = true,
पूर्ण;

अटल स्थिर काष्ठा dsic_panel_data himalaya_data = अणु
	.xres = 480,
	.yres = 864,
	.refresh = 60,
	.width_mm = 49,
	.height_mm = 88,
	.max_hs_rate = 300000000,
	.max_lp_rate = 10000000,
	.te_support = false,
पूर्ण;

अटल स्थिर काष्ठा dsic_panel_data droid4_data = अणु
	.xres = 540,
	.yres = 960,
	.refresh = 60,
	.width_mm = 50,
	.height_mm = 89,
	.max_hs_rate = 300000000,
	.max_lp_rate = 10000000,
	.te_support = false,
पूर्ण;

अटल स्थिर काष्ठा of_device_id dsicm_of_match[] = अणु
	अणु .compatible = "tpo,taal", .data = &taal_data पूर्ण,
	अणु .compatible = "nokia,himalaya", &himalaya_data पूर्ण,
	अणु .compatible = "motorola,droid4-panel", &droid4_data पूर्ण,
	अणुपूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(of, dsicm_of_match);

अटल काष्ठा mipi_dsi_driver dsicm_driver = अणु
	.probe = dsicm_probe,
	.हटाओ = dsicm_हटाओ,
	.driver = अणु
		.name = "panel-dsi-cm",
		.of_match_table = dsicm_of_match,
	पूर्ण,
पूर्ण;
module_mipi_dsi_driver(dsicm_driver);

MODULE_AUTHOR("Tomi Valkeinen <tomi.valkeinen@ti.com>");
MODULE_DESCRIPTION("Generic DSI Command Mode Panel Driver");
MODULE_LICENSE("GPL");
