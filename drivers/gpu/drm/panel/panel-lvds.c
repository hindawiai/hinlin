<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Generic LVDS panel driver
 *
 * Copyright (C) 2016 Laurent Pinअक्षरt
 * Copyright (C) 2016 Renesas Electronics Corporation
 *
 * Contact: Laurent Pinअक्षरt (laurent.pinअक्षरt@ideasonboard.com)
 */

#समावेश <linux/gpio/consumer.h>
#समावेश <linux/module.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/slab.h>

#समावेश <video/display_timing.h>
#समावेश <video/of_display_timing.h>
#समावेश <video/videomode.h>

#समावेश <drm/drm_crtc.h>
#समावेश <drm/drm_panel.h>

काष्ठा panel_lvds अणु
	काष्ठा drm_panel panel;
	काष्ठा device *dev;

	स्थिर अक्षर *label;
	अचिन्हित पूर्णांक width;
	अचिन्हित पूर्णांक height;
	काष्ठा videomode video_mode;
	अचिन्हित पूर्णांक bus_क्रमmat;
	bool data_mirror;

	काष्ठा regulator *supply;

	काष्ठा gpio_desc *enable_gpio;
	काष्ठा gpio_desc *reset_gpio;

	क्रमागत drm_panel_orientation orientation;
पूर्ण;

अटल अंतरभूत काष्ठा panel_lvds *to_panel_lvds(काष्ठा drm_panel *panel)
अणु
	वापस container_of(panel, काष्ठा panel_lvds, panel);
पूर्ण

अटल पूर्णांक panel_lvds_unprepare(काष्ठा drm_panel *panel)
अणु
	काष्ठा panel_lvds *lvds = to_panel_lvds(panel);

	अगर (lvds->enable_gpio)
		gpiod_set_value_cansleep(lvds->enable_gpio, 0);

	अगर (lvds->supply)
		regulator_disable(lvds->supply);

	वापस 0;
पूर्ण

अटल पूर्णांक panel_lvds_prepare(काष्ठा drm_panel *panel)
अणु
	काष्ठा panel_lvds *lvds = to_panel_lvds(panel);

	अगर (lvds->supply) अणु
		पूर्णांक err;

		err = regulator_enable(lvds->supply);
		अगर (err < 0) अणु
			dev_err(lvds->dev, "failed to enable supply: %d\n",
				err);
			वापस err;
		पूर्ण
	पूर्ण

	अगर (lvds->enable_gpio)
		gpiod_set_value_cansleep(lvds->enable_gpio, 1);

	वापस 0;
पूर्ण

अटल पूर्णांक panel_lvds_get_modes(काष्ठा drm_panel *panel,
				काष्ठा drm_connector *connector)
अणु
	काष्ठा panel_lvds *lvds = to_panel_lvds(panel);
	काष्ठा drm_display_mode *mode;

	mode = drm_mode_create(connector->dev);
	अगर (!mode)
		वापस 0;

	drm_display_mode_from_videomode(&lvds->video_mode, mode);
	mode->type |= DRM_MODE_TYPE_DRIVER | DRM_MODE_TYPE_PREFERRED;
	drm_mode_probed_add(connector, mode);

	connector->display_info.width_mm = lvds->width;
	connector->display_info.height_mm = lvds->height;
	drm_display_info_set_bus_क्रमmats(&connector->display_info,
					 &lvds->bus_क्रमmat, 1);
	connector->display_info.bus_flags = lvds->data_mirror
					  ? DRM_BUS_FLAG_DATA_LSB_TO_MSB
					  : DRM_BUS_FLAG_DATA_MSB_TO_LSB;
	drm_connector_set_panel_orientation(connector, lvds->orientation);

	वापस 1;
पूर्ण

अटल स्थिर काष्ठा drm_panel_funcs panel_lvds_funcs = अणु
	.unprepare = panel_lvds_unprepare,
	.prepare = panel_lvds_prepare,
	.get_modes = panel_lvds_get_modes,
पूर्ण;

अटल पूर्णांक panel_lvds_parse_dt(काष्ठा panel_lvds *lvds)
अणु
	काष्ठा device_node *np = lvds->dev->of_node;
	काष्ठा display_timing timing;
	स्थिर अक्षर *mapping;
	पूर्णांक ret;

	ret = of_drm_get_panel_orientation(np, &lvds->orientation);
	अगर (ret < 0) अणु
		dev_err(lvds->dev, "%pOF: failed to get orientation %d\n", np, ret);
		वापस ret;
	पूर्ण

	ret = of_get_display_timing(np, "panel-timing", &timing);
	अगर (ret < 0) अणु
		dev_err(lvds->dev, "%pOF: problems parsing panel-timing (%d)\n",
			np, ret);
		वापस ret;
	पूर्ण

	videomode_from_timing(&timing, &lvds->video_mode);

	ret = of_property_पढ़ो_u32(np, "width-mm", &lvds->width);
	अगर (ret < 0) अणु
		dev_err(lvds->dev, "%pOF: invalid or missing %s DT property\n",
			np, "width-mm");
		वापस -ENODEV;
	पूर्ण
	ret = of_property_पढ़ो_u32(np, "height-mm", &lvds->height);
	अगर (ret < 0) अणु
		dev_err(lvds->dev, "%pOF: invalid or missing %s DT property\n",
			np, "height-mm");
		वापस -ENODEV;
	पूर्ण

	of_property_पढ़ो_string(np, "label", &lvds->label);

	ret = of_property_पढ़ो_string(np, "data-mapping", &mapping);
	अगर (ret < 0) अणु
		dev_err(lvds->dev, "%pOF: invalid or missing %s DT property\n",
			np, "data-mapping");
		वापस -ENODEV;
	पूर्ण

	अगर (!म_भेद(mapping, "jeida-18")) अणु
		lvds->bus_क्रमmat = MEDIA_BUS_FMT_RGB666_1X7X3_SPWG;
	पूर्ण अन्यथा अगर (!म_भेद(mapping, "jeida-24")) अणु
		lvds->bus_क्रमmat = MEDIA_BUS_FMT_RGB888_1X7X4_JEIDA;
	पूर्ण अन्यथा अगर (!म_भेद(mapping, "vesa-24")) अणु
		lvds->bus_क्रमmat = MEDIA_BUS_FMT_RGB888_1X7X4_SPWG;
	पूर्ण अन्यथा अणु
		dev_err(lvds->dev, "%pOF: invalid or missing %s DT property\n",
			np, "data-mapping");
		वापस -EINVAL;
	पूर्ण

	lvds->data_mirror = of_property_पढ़ो_bool(np, "data-mirror");

	वापस 0;
पूर्ण

अटल पूर्णांक panel_lvds_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा panel_lvds *lvds;
	पूर्णांक ret;

	lvds = devm_kzalloc(&pdev->dev, माप(*lvds), GFP_KERNEL);
	अगर (!lvds)
		वापस -ENOMEM;

	lvds->dev = &pdev->dev;

	ret = panel_lvds_parse_dt(lvds);
	अगर (ret < 0)
		वापस ret;

	lvds->supply = devm_regulator_get_optional(lvds->dev, "power");
	अगर (IS_ERR(lvds->supply)) अणु
		ret = PTR_ERR(lvds->supply);

		अगर (ret != -ENODEV) अणु
			अगर (ret != -EPROBE_DEFER)
				dev_err(lvds->dev, "failed to request regulator: %d\n",
					ret);
			वापस ret;
		पूर्ण

		lvds->supply = शून्य;
	पूर्ण

	/* Get GPIOs and backlight controller. */
	lvds->enable_gpio = devm_gpiod_get_optional(lvds->dev, "enable",
						     GPIOD_OUT_LOW);
	अगर (IS_ERR(lvds->enable_gpio)) अणु
		ret = PTR_ERR(lvds->enable_gpio);
		dev_err(lvds->dev, "failed to request %s GPIO: %d\n",
			"enable", ret);
		वापस ret;
	पूर्ण

	lvds->reset_gpio = devm_gpiod_get_optional(lvds->dev, "reset",
						     GPIOD_OUT_HIGH);
	अगर (IS_ERR(lvds->reset_gpio)) अणु
		ret = PTR_ERR(lvds->reset_gpio);
		dev_err(lvds->dev, "failed to request %s GPIO: %d\n",
			"reset", ret);
		वापस ret;
	पूर्ण

	/*
	 * TODO: Handle all घातer supplies specअगरied in the DT node in a generic
	 * way क्रम panels that करोn't care about घातer supply ordering. LVDS
	 * panels that require a specअगरic घातer sequence will need a dedicated
	 * driver.
	 */

	/* Register the panel. */
	drm_panel_init(&lvds->panel, lvds->dev, &panel_lvds_funcs,
		       DRM_MODE_CONNECTOR_LVDS);

	ret = drm_panel_of_backlight(&lvds->panel);
	अगर (ret)
		वापस ret;

	drm_panel_add(&lvds->panel);

	dev_set_drvdata(lvds->dev, lvds);
	वापस 0;
पूर्ण

अटल पूर्णांक panel_lvds_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा panel_lvds *lvds = platक्रमm_get_drvdata(pdev);

	drm_panel_हटाओ(&lvds->panel);

	drm_panel_disable(&lvds->panel);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id panel_lvds_of_table[] = अणु
	अणु .compatible = "panel-lvds", पूर्ण,
	अणु /* Sentinel */ पूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(of, panel_lvds_of_table);

अटल काष्ठा platक्रमm_driver panel_lvds_driver = अणु
	.probe		= panel_lvds_probe,
	.हटाओ		= panel_lvds_हटाओ,
	.driver		= अणु
		.name	= "panel-lvds",
		.of_match_table = panel_lvds_of_table,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(panel_lvds_driver);

MODULE_AUTHOR("Laurent Pinchart <laurent.pinchart@ideasonboard.com>");
MODULE_DESCRIPTION("LVDS Panel Driver");
MODULE_LICENSE("GPL");
