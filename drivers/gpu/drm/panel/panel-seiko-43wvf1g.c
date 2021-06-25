<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2017 NXP Semiconductors.
 * Author: Marco Franchi <marco.franchi@nxp.com>
 *
 * Based on Panel Simple driver by Thierry Reding <treding@nvidia.com>
 */

#समावेश <linux/delay.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regulator/consumer.h>

#समावेश <video/display_timing.h>
#समावेश <video/videomode.h>

#समावेश <drm/drm_crtc.h>
#समावेश <drm/drm_device.h>
#समावेश <drm/drm_panel.h>

काष्ठा seiko_panel_desc अणु
	स्थिर काष्ठा drm_display_mode *modes;
	अचिन्हित पूर्णांक num_modes;
	स्थिर काष्ठा display_timing *timings;
	अचिन्हित पूर्णांक num_timings;

	अचिन्हित पूर्णांक bpc;

	/**
	 * @width: width (in millimeters) of the panel's active display area
	 * @height: height (in millimeters) of the panel's active display area
	 */
	काष्ठा अणु
		अचिन्हित पूर्णांक width;
		अचिन्हित पूर्णांक height;
	पूर्ण size;

	u32 bus_क्रमmat;
	u32 bus_flags;
पूर्ण;

काष्ठा seiko_panel अणु
	काष्ठा drm_panel base;
	bool prepared;
	bool enabled;
	स्थिर काष्ठा seiko_panel_desc *desc;
	काष्ठा regulator *dvdd;
	काष्ठा regulator *avdd;
पूर्ण;

अटल अंतरभूत काष्ठा seiko_panel *to_seiko_panel(काष्ठा drm_panel *panel)
अणु
	वापस container_of(panel, काष्ठा seiko_panel, base);
पूर्ण

अटल पूर्णांक seiko_panel_get_fixed_modes(काष्ठा seiko_panel *panel,
				       काष्ठा drm_connector *connector)
अणु
	काष्ठा drm_display_mode *mode;
	अचिन्हित पूर्णांक i, num = 0;

	अगर (!panel->desc)
		वापस 0;

	क्रम (i = 0; i < panel->desc->num_timings; i++) अणु
		स्थिर काष्ठा display_timing *dt = &panel->desc->timings[i];
		काष्ठा videomode vm;

		videomode_from_timing(dt, &vm);
		mode = drm_mode_create(connector->dev);
		अगर (!mode) अणु
			dev_err(panel->base.dev, "failed to add mode %ux%u\n",
				dt->hactive.typ, dt->vactive.typ);
			जारी;
		पूर्ण

		drm_display_mode_from_videomode(&vm, mode);

		mode->type |= DRM_MODE_TYPE_DRIVER;

		अगर (panel->desc->num_timings == 1)
			mode->type |= DRM_MODE_TYPE_PREFERRED;

		drm_mode_probed_add(connector, mode);
		num++;
	पूर्ण

	क्रम (i = 0; i < panel->desc->num_modes; i++) अणु
		स्थिर काष्ठा drm_display_mode *m = &panel->desc->modes[i];

		mode = drm_mode_duplicate(connector->dev, m);
		अगर (!mode) अणु
			dev_err(panel->base.dev, "failed to add mode %ux%u@%u\n",
				m->hdisplay, m->vdisplay,
				drm_mode_vrefresh(m));
			जारी;
		पूर्ण

		mode->type |= DRM_MODE_TYPE_DRIVER;

		अगर (panel->desc->num_modes == 1)
			mode->type |= DRM_MODE_TYPE_PREFERRED;

		drm_mode_set_name(mode);

		drm_mode_probed_add(connector, mode);
		num++;
	पूर्ण

	connector->display_info.bpc = panel->desc->bpc;
	connector->display_info.width_mm = panel->desc->size.width;
	connector->display_info.height_mm = panel->desc->size.height;
	अगर (panel->desc->bus_क्रमmat)
		drm_display_info_set_bus_क्रमmats(&connector->display_info,
						 &panel->desc->bus_क्रमmat, 1);
	connector->display_info.bus_flags = panel->desc->bus_flags;

	वापस num;
पूर्ण

अटल पूर्णांक seiko_panel_disable(काष्ठा drm_panel *panel)
अणु
	काष्ठा seiko_panel *p = to_seiko_panel(panel);

	अगर (!p->enabled)
		वापस 0;

	p->enabled = false;

	वापस 0;
पूर्ण

अटल पूर्णांक seiko_panel_unprepare(काष्ठा drm_panel *panel)
अणु
	काष्ठा seiko_panel *p = to_seiko_panel(panel);

	अगर (!p->prepared)
		वापस 0;

	regulator_disable(p->avdd);

	/* Add a 100ms delay as per the panel datasheet */
	msleep(100);

	regulator_disable(p->dvdd);

	p->prepared = false;

	वापस 0;
पूर्ण

अटल पूर्णांक seiko_panel_prepare(काष्ठा drm_panel *panel)
अणु
	काष्ठा seiko_panel *p = to_seiko_panel(panel);
	पूर्णांक err;

	अगर (p->prepared)
		वापस 0;

	err = regulator_enable(p->dvdd);
	अगर (err < 0) अणु
		dev_err(panel->dev, "failed to enable dvdd: %d\n", err);
		वापस err;
	पूर्ण

	/* Add a 100ms delay as per the panel datasheet */
	msleep(100);

	err = regulator_enable(p->avdd);
	अगर (err < 0) अणु
		dev_err(panel->dev, "failed to enable avdd: %d\n", err);
		जाओ disable_dvdd;
	पूर्ण

	p->prepared = true;

	वापस 0;

disable_dvdd:
	regulator_disable(p->dvdd);
	वापस err;
पूर्ण

अटल पूर्णांक seiko_panel_enable(काष्ठा drm_panel *panel)
अणु
	काष्ठा seiko_panel *p = to_seiko_panel(panel);

	अगर (p->enabled)
		वापस 0;

	p->enabled = true;

	वापस 0;
पूर्ण

अटल पूर्णांक seiko_panel_get_modes(काष्ठा drm_panel *panel,
				 काष्ठा drm_connector *connector)
अणु
	काष्ठा seiko_panel *p = to_seiko_panel(panel);

	/* add hard-coded panel modes */
	वापस seiko_panel_get_fixed_modes(p, connector);
पूर्ण

अटल पूर्णांक seiko_panel_get_timings(काष्ठा drm_panel *panel,
				    अचिन्हित पूर्णांक num_timings,
				    काष्ठा display_timing *timings)
अणु
	काष्ठा seiko_panel *p = to_seiko_panel(panel);
	अचिन्हित पूर्णांक i;

	अगर (p->desc->num_timings < num_timings)
		num_timings = p->desc->num_timings;

	अगर (timings)
		क्रम (i = 0; i < num_timings; i++)
			timings[i] = p->desc->timings[i];

	वापस p->desc->num_timings;
पूर्ण

अटल स्थिर काष्ठा drm_panel_funcs seiko_panel_funcs = अणु
	.disable = seiko_panel_disable,
	.unprepare = seiko_panel_unprepare,
	.prepare = seiko_panel_prepare,
	.enable = seiko_panel_enable,
	.get_modes = seiko_panel_get_modes,
	.get_timings = seiko_panel_get_timings,
पूर्ण;

अटल पूर्णांक seiko_panel_probe(काष्ठा device *dev,
					स्थिर काष्ठा seiko_panel_desc *desc)
अणु
	काष्ठा seiko_panel *panel;
	पूर्णांक err;

	panel = devm_kzalloc(dev, माप(*panel), GFP_KERNEL);
	अगर (!panel)
		वापस -ENOMEM;

	panel->enabled = false;
	panel->prepared = false;
	panel->desc = desc;

	panel->dvdd = devm_regulator_get(dev, "dvdd");
	अगर (IS_ERR(panel->dvdd))
		वापस PTR_ERR(panel->dvdd);

	panel->avdd = devm_regulator_get(dev, "avdd");
	अगर (IS_ERR(panel->avdd))
		वापस PTR_ERR(panel->avdd);

	drm_panel_init(&panel->base, dev, &seiko_panel_funcs,
		       DRM_MODE_CONNECTOR_DPI);

	err = drm_panel_of_backlight(&panel->base);
	अगर (err)
		वापस err;

	drm_panel_add(&panel->base);

	dev_set_drvdata(dev, panel);

	वापस 0;
पूर्ण

अटल पूर्णांक seiko_panel_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा seiko_panel *panel = platक्रमm_get_drvdata(pdev);

	drm_panel_हटाओ(&panel->base);
	drm_panel_disable(&panel->base);

	वापस 0;
पूर्ण

अटल व्योम seiko_panel_shutकरोwn(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा seiko_panel *panel = platक्रमm_get_drvdata(pdev);

	drm_panel_disable(&panel->base);
पूर्ण

अटल स्थिर काष्ठा display_timing seiko_43wvf1g_timing = अणु
	.pixelघड़ी = अणु 33500000, 33500000, 33500000 पूर्ण,
	.hactive = अणु 800, 800, 800 पूर्ण,
	.hfront_porch = अणु  164, 164, 164 पूर्ण,
	.hback_porch = अणु 89, 89, 89 पूर्ण,
	.hsync_len = अणु 10, 10, 10 पूर्ण,
	.vactive = अणु 480, 480, 480 पूर्ण,
	.vfront_porch = अणु 10, 10, 10 पूर्ण,
	.vback_porch = अणु 23, 23, 23 पूर्ण,
	.vsync_len = अणु 10, 10, 10 पूर्ण,
	.flags = DISPLAY_FLAGS_DE_LOW,
पूर्ण;

अटल स्थिर काष्ठा seiko_panel_desc seiko_43wvf1g = अणु
	.timings = &seiko_43wvf1g_timing,
	.num_timings = 1,
	.bpc = 8,
	.size = अणु
		.width = 93,
		.height = 57,
	पूर्ण,
	.bus_क्रमmat = MEDIA_BUS_FMT_RGB888_1X24,
	.bus_flags = DRM_BUS_FLAG_DE_HIGH | DRM_BUS_FLAG_PIXDATA_DRIVE_NEGEDGE,
पूर्ण;

अटल स्थिर काष्ठा of_device_id platक्रमm_of_match[] = अणु
	अणु
		.compatible = "sii,43wvf1g",
		.data = &seiko_43wvf1g,
	पूर्ण, अणु
		/* sentinel */
	पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, platक्रमm_of_match);

अटल पूर्णांक seiko_panel_platक्रमm_probe(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा of_device_id *id;

	id = of_match_node(platक्रमm_of_match, pdev->dev.of_node);
	अगर (!id)
		वापस -ENODEV;

	वापस seiko_panel_probe(&pdev->dev, id->data);
पूर्ण

अटल काष्ठा platक्रमm_driver seiko_panel_platक्रमm_driver = अणु
	.driver = अणु
		.name = "seiko_panel",
		.of_match_table = platक्रमm_of_match,
	पूर्ण,
	.probe = seiko_panel_platक्रमm_probe,
	.हटाओ = seiko_panel_हटाओ,
	.shutकरोwn = seiko_panel_shutकरोwn,
पूर्ण;
module_platक्रमm_driver(seiko_panel_platक्रमm_driver);

MODULE_AUTHOR("Marco Franchi <marco.franchi@nxp.com>");
MODULE_DESCRIPTION("Seiko 43WVF1G panel driver");
MODULE_LICENSE("GPL v2");
