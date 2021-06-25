<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Generic MIPI DPI Panel Driver
 *
 * Copyright (C) 2013 Texas Instruments
 * Author: Tomi Valkeinen <tomi.valkeinen@ti.com>
 */

#समावेश <linux/gpपन.स>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/of.h>
#समावेश <linux/of_gpपन.स>

#समावेश <video/omapfb_dss.h>
#समावेश <video/omap-panel-data.h>
#समावेश <video/of_display_timing.h>

काष्ठा panel_drv_data अणु
	काष्ठा omap_dss_device dssdev;
	काष्ठा omap_dss_device *in;

	पूर्णांक data_lines;

	काष्ठा omap_video_timings videomode;

	/* used क्रम non-DT boot, to be हटाओd */
	पूर्णांक backlight_gpio;

	काष्ठा gpio_desc *enable_gpio;
पूर्ण;

#घोषणा to_panel_data(p) container_of(p, काष्ठा panel_drv_data, dssdev)

अटल पूर्णांक panel_dpi_connect(काष्ठा omap_dss_device *dssdev)
अणु
	काष्ठा panel_drv_data *ddata = to_panel_data(dssdev);
	काष्ठा omap_dss_device *in = ddata->in;

	अगर (omapdss_device_is_connected(dssdev))
		वापस 0;

	वापस in->ops.dpi->connect(in, dssdev);
पूर्ण

अटल व्योम panel_dpi_disconnect(काष्ठा omap_dss_device *dssdev)
अणु
	काष्ठा panel_drv_data *ddata = to_panel_data(dssdev);
	काष्ठा omap_dss_device *in = ddata->in;

	अगर (!omapdss_device_is_connected(dssdev))
		वापस;

	in->ops.dpi->disconnect(in, dssdev);
पूर्ण

अटल पूर्णांक panel_dpi_enable(काष्ठा omap_dss_device *dssdev)
अणु
	काष्ठा panel_drv_data *ddata = to_panel_data(dssdev);
	काष्ठा omap_dss_device *in = ddata->in;
	पूर्णांक r;

	अगर (!omapdss_device_is_connected(dssdev))
		वापस -ENODEV;

	अगर (omapdss_device_is_enabled(dssdev))
		वापस 0;

	अगर (ddata->data_lines)
		in->ops.dpi->set_data_lines(in, ddata->data_lines);
	in->ops.dpi->set_timings(in, &ddata->videomode);

	r = in->ops.dpi->enable(in);
	अगर (r)
		वापस r;

	gpiod_set_value_cansleep(ddata->enable_gpio, 1);

	अगर (gpio_is_valid(ddata->backlight_gpio))
		gpio_set_value_cansleep(ddata->backlight_gpio, 1);

	dssdev->state = OMAP_DSS_DISPLAY_ACTIVE;

	वापस 0;
पूर्ण

अटल व्योम panel_dpi_disable(काष्ठा omap_dss_device *dssdev)
अणु
	काष्ठा panel_drv_data *ddata = to_panel_data(dssdev);
	काष्ठा omap_dss_device *in = ddata->in;

	अगर (!omapdss_device_is_enabled(dssdev))
		वापस;

	अगर (gpio_is_valid(ddata->backlight_gpio))
		gpio_set_value_cansleep(ddata->backlight_gpio, 0);

	gpiod_set_value_cansleep(ddata->enable_gpio, 0);

	in->ops.dpi->disable(in);

	dssdev->state = OMAP_DSS_DISPLAY_DISABLED;
पूर्ण

अटल व्योम panel_dpi_set_timings(काष्ठा omap_dss_device *dssdev,
		काष्ठा omap_video_timings *timings)
अणु
	काष्ठा panel_drv_data *ddata = to_panel_data(dssdev);
	काष्ठा omap_dss_device *in = ddata->in;

	ddata->videomode = *timings;
	dssdev->panel.timings = *timings;

	in->ops.dpi->set_timings(in, timings);
पूर्ण

अटल व्योम panel_dpi_get_timings(काष्ठा omap_dss_device *dssdev,
		काष्ठा omap_video_timings *timings)
अणु
	काष्ठा panel_drv_data *ddata = to_panel_data(dssdev);

	*timings = ddata->videomode;
पूर्ण

अटल पूर्णांक panel_dpi_check_timings(काष्ठा omap_dss_device *dssdev,
		काष्ठा omap_video_timings *timings)
अणु
	काष्ठा panel_drv_data *ddata = to_panel_data(dssdev);
	काष्ठा omap_dss_device *in = ddata->in;

	वापस in->ops.dpi->check_timings(in, timings);
पूर्ण

अटल काष्ठा omap_dss_driver panel_dpi_ops = अणु
	.connect	= panel_dpi_connect,
	.disconnect	= panel_dpi_disconnect,

	.enable		= panel_dpi_enable,
	.disable	= panel_dpi_disable,

	.set_timings	= panel_dpi_set_timings,
	.get_timings	= panel_dpi_get_timings,
	.check_timings	= panel_dpi_check_timings,

	.get_resolution	= omapdss_शेष_get_resolution,
पूर्ण;

अटल पूर्णांक panel_dpi_probe_pdata(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा panel_dpi_platक्रमm_data *pdata;
	काष्ठा panel_drv_data *ddata = platक्रमm_get_drvdata(pdev);
	काष्ठा omap_dss_device *dssdev, *in;
	काष्ठा videomode vm;
	पूर्णांक r;

	pdata = dev_get_platdata(&pdev->dev);

	in = omap_dss_find_output(pdata->source);
	अगर (in == शून्य) अणु
		dev_err(&pdev->dev, "failed to find video source '%s'\n",
				pdata->source);
		वापस -EPROBE_DEFER;
	पूर्ण

	ddata->in = in;

	ddata->data_lines = pdata->data_lines;

	videomode_from_timing(pdata->display_timing, &vm);
	videomode_to_omap_video_timings(&vm, &ddata->videomode);

	dssdev = &ddata->dssdev;
	dssdev->name = pdata->name;

	r = devm_gpio_request_one(&pdev->dev, pdata->enable_gpio,
					GPIOF_OUT_INIT_LOW, "panel enable");
	अगर (r)
		जाओ err_gpio;

	ddata->enable_gpio = gpio_to_desc(pdata->enable_gpio);

	ddata->backlight_gpio = pdata->backlight_gpio;

	वापस 0;

err_gpio:
	omap_dss_put_device(ddata->in);
	वापस r;
पूर्ण

अटल पूर्णांक panel_dpi_probe_of(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा panel_drv_data *ddata = platक्रमm_get_drvdata(pdev);
	काष्ठा device_node *node = pdev->dev.of_node;
	काष्ठा omap_dss_device *in;
	पूर्णांक r;
	काष्ठा display_timing timing;
	काष्ठा videomode vm;
	काष्ठा gpio_desc *gpio;

	gpio = devm_gpiod_get_optional(&pdev->dev, "enable", GPIOD_OUT_LOW);
	अगर (IS_ERR(gpio))
		वापस PTR_ERR(gpio);

	ddata->enable_gpio = gpio;

	ddata->backlight_gpio = -ENOENT;

	r = of_get_display_timing(node, "panel-timing", &timing);
	अगर (r) अणु
		dev_err(&pdev->dev, "failed to get video timing\n");
		वापस r;
	पूर्ण

	videomode_from_timing(&timing, &vm);
	videomode_to_omap_video_timings(&vm, &ddata->videomode);

	in = omapdss_of_find_source_क्रम_first_ep(node);
	अगर (IS_ERR(in)) अणु
		dev_err(&pdev->dev, "failed to find video source\n");
		वापस PTR_ERR(in);
	पूर्ण

	ddata->in = in;

	वापस 0;
पूर्ण

अटल पूर्णांक panel_dpi_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा panel_drv_data *ddata;
	काष्ठा omap_dss_device *dssdev;
	पूर्णांक r;

	ddata = devm_kzalloc(&pdev->dev, माप(*ddata), GFP_KERNEL);
	अगर (ddata == शून्य)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, ddata);

	अगर (dev_get_platdata(&pdev->dev)) अणु
		r = panel_dpi_probe_pdata(pdev);
		अगर (r)
			वापस r;
	पूर्ण अन्यथा अगर (pdev->dev.of_node) अणु
		r = panel_dpi_probe_of(pdev);
		अगर (r)
			वापस r;
	पूर्ण अन्यथा अणु
		वापस -ENODEV;
	पूर्ण

	अगर (gpio_is_valid(ddata->backlight_gpio)) अणु
		r = devm_gpio_request_one(&pdev->dev, ddata->backlight_gpio,
				GPIOF_OUT_INIT_LOW, "panel backlight");
		अगर (r)
			जाओ err_gpio;
	पूर्ण

	dssdev = &ddata->dssdev;
	dssdev->dev = &pdev->dev;
	dssdev->driver = &panel_dpi_ops;
	dssdev->type = OMAP_DISPLAY_TYPE_DPI;
	dssdev->owner = THIS_MODULE;
	dssdev->panel.timings = ddata->videomode;
	dssdev->phy.dpi.data_lines = ddata->data_lines;

	r = omapdss_रेजिस्टर_display(dssdev);
	अगर (r) अणु
		dev_err(&pdev->dev, "Failed to register panel\n");
		जाओ err_reg;
	पूर्ण

	वापस 0;

err_reg:
err_gpio:
	omap_dss_put_device(ddata->in);
	वापस r;
पूर्ण

अटल पूर्णांक __निकास panel_dpi_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा panel_drv_data *ddata = platक्रमm_get_drvdata(pdev);
	काष्ठा omap_dss_device *dssdev = &ddata->dssdev;
	काष्ठा omap_dss_device *in = ddata->in;

	omapdss_unरेजिस्टर_display(dssdev);

	panel_dpi_disable(dssdev);
	panel_dpi_disconnect(dssdev);

	omap_dss_put_device(in);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id panel_dpi_of_match[] = अणु
	अणु .compatible = "omapdss,panel-dpi", पूर्ण,
	अणुपूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(of, panel_dpi_of_match);

अटल काष्ठा platक्रमm_driver panel_dpi_driver = अणु
	.probe = panel_dpi_probe,
	.हटाओ = __निकास_p(panel_dpi_हटाओ),
	.driver = अणु
		.name = "panel-dpi",
		.of_match_table = panel_dpi_of_match,
		.suppress_bind_attrs = true,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(panel_dpi_driver);

MODULE_AUTHOR("Tomi Valkeinen <tomi.valkeinen@ti.com>");
MODULE_DESCRIPTION("Generic MIPI DPI Panel Driver");
MODULE_LICENSE("GPL");
