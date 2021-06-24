<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * TFP410 DPI-to-DVI encoder driver
 *
 * Copyright (C) 2013 Texas Instruments
 * Author: Tomi Valkeinen <tomi.valkeinen@ti.com>
 */

#समावेश <linux/gpपन.स>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/of_gpपन.स>

#समावेश <video/omapfb_dss.h>

काष्ठा panel_drv_data अणु
	काष्ठा omap_dss_device dssdev;
	काष्ठा omap_dss_device *in;

	पूर्णांक pd_gpio;
	पूर्णांक data_lines;

	काष्ठा omap_video_timings timings;
पूर्ण;

#घोषणा to_panel_data(x) container_of(x, काष्ठा panel_drv_data, dssdev)

अटल पूर्णांक tfp410_connect(काष्ठा omap_dss_device *dssdev,
		काष्ठा omap_dss_device *dst)
अणु
	काष्ठा panel_drv_data *ddata = to_panel_data(dssdev);
	काष्ठा omap_dss_device *in = ddata->in;
	पूर्णांक r;

	अगर (omapdss_device_is_connected(dssdev))
		वापस -EBUSY;

	r = in->ops.dpi->connect(in, dssdev);
	अगर (r)
		वापस r;

	dst->src = dssdev;
	dssdev->dst = dst;

	वापस 0;
पूर्ण

अटल व्योम tfp410_disconnect(काष्ठा omap_dss_device *dssdev,
		काष्ठा omap_dss_device *dst)
अणु
	काष्ठा panel_drv_data *ddata = to_panel_data(dssdev);
	काष्ठा omap_dss_device *in = ddata->in;

	WARN_ON(!omapdss_device_is_connected(dssdev));
	अगर (!omapdss_device_is_connected(dssdev))
		वापस;

	WARN_ON(dst != dssdev->dst);
	अगर (dst != dssdev->dst)
		वापस;

	dst->src = शून्य;
	dssdev->dst = शून्य;

	in->ops.dpi->disconnect(in, &ddata->dssdev);
पूर्ण

अटल पूर्णांक tfp410_enable(काष्ठा omap_dss_device *dssdev)
अणु
	काष्ठा panel_drv_data *ddata = to_panel_data(dssdev);
	काष्ठा omap_dss_device *in = ddata->in;
	पूर्णांक r;

	अगर (!omapdss_device_is_connected(dssdev))
		वापस -ENODEV;

	अगर (omapdss_device_is_enabled(dssdev))
		वापस 0;

	in->ops.dpi->set_timings(in, &ddata->timings);
	अगर (ddata->data_lines)
		in->ops.dpi->set_data_lines(in, ddata->data_lines);

	r = in->ops.dpi->enable(in);
	अगर (r)
		वापस r;

	अगर (gpio_is_valid(ddata->pd_gpio))
		gpio_set_value_cansleep(ddata->pd_gpio, 1);

	dssdev->state = OMAP_DSS_DISPLAY_ACTIVE;

	वापस 0;
पूर्ण

अटल व्योम tfp410_disable(काष्ठा omap_dss_device *dssdev)
अणु
	काष्ठा panel_drv_data *ddata = to_panel_data(dssdev);
	काष्ठा omap_dss_device *in = ddata->in;

	अगर (!omapdss_device_is_enabled(dssdev))
		वापस;

	अगर (gpio_is_valid(ddata->pd_gpio))
		gpio_set_value_cansleep(ddata->pd_gpio, 0);

	in->ops.dpi->disable(in);

	dssdev->state = OMAP_DSS_DISPLAY_DISABLED;
पूर्ण

अटल व्योम tfp410_fix_timings(काष्ठा omap_video_timings *timings)
अणु
	timings->data_pclk_edge = OMAPDSS_DRIVE_SIG_RISING_EDGE;
	timings->sync_pclk_edge = OMAPDSS_DRIVE_SIG_RISING_EDGE;
	timings->de_level = OMAPDSS_SIG_ACTIVE_HIGH;
पूर्ण

अटल व्योम tfp410_set_timings(काष्ठा omap_dss_device *dssdev,
		काष्ठा omap_video_timings *timings)
अणु
	काष्ठा panel_drv_data *ddata = to_panel_data(dssdev);
	काष्ठा omap_dss_device *in = ddata->in;

	tfp410_fix_timings(timings);

	ddata->timings = *timings;
	dssdev->panel.timings = *timings;

	in->ops.dpi->set_timings(in, timings);
पूर्ण

अटल व्योम tfp410_get_timings(काष्ठा omap_dss_device *dssdev,
		काष्ठा omap_video_timings *timings)
अणु
	काष्ठा panel_drv_data *ddata = to_panel_data(dssdev);

	*timings = ddata->timings;
पूर्ण

अटल पूर्णांक tfp410_check_timings(काष्ठा omap_dss_device *dssdev,
		काष्ठा omap_video_timings *timings)
अणु
	काष्ठा panel_drv_data *ddata = to_panel_data(dssdev);
	काष्ठा omap_dss_device *in = ddata->in;

	tfp410_fix_timings(timings);

	वापस in->ops.dpi->check_timings(in, timings);
पूर्ण

अटल स्थिर काष्ठा omapdss_dvi_ops tfp410_dvi_ops = अणु
	.connect	= tfp410_connect,
	.disconnect	= tfp410_disconnect,

	.enable		= tfp410_enable,
	.disable	= tfp410_disable,

	.check_timings	= tfp410_check_timings,
	.set_timings	= tfp410_set_timings,
	.get_timings	= tfp410_get_timings,
पूर्ण;

अटल पूर्णांक tfp410_probe_of(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा panel_drv_data *ddata = platक्रमm_get_drvdata(pdev);
	काष्ठा device_node *node = pdev->dev.of_node;
	काष्ठा omap_dss_device *in;
	पूर्णांक gpio;

	gpio = of_get_named_gpio(node, "powerdown-gpios", 0);

	अगर (gpio_is_valid(gpio) || gpio == -ENOENT) अणु
		ddata->pd_gpio = gpio;
	पूर्ण अन्यथा अणु
		dev_err(&pdev->dev, "failed to parse PD gpio\n");
		वापस gpio;
	पूर्ण

	in = omapdss_of_find_source_क्रम_first_ep(node);
	अगर (IS_ERR(in)) अणु
		dev_err(&pdev->dev, "failed to find video source\n");
		वापस PTR_ERR(in);
	पूर्ण

	ddata->in = in;

	वापस 0;
पूर्ण

अटल पूर्णांक tfp410_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा panel_drv_data *ddata;
	काष्ठा omap_dss_device *dssdev;
	पूर्णांक r;

	अगर (!pdev->dev.of_node)
		वापस -ENODEV;

	ddata = devm_kzalloc(&pdev->dev, माप(*ddata), GFP_KERNEL);
	अगर (!ddata)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, ddata);

	r = tfp410_probe_of(pdev);
	अगर (r)
		वापस r;

	अगर (gpio_is_valid(ddata->pd_gpio)) अणु
		r = devm_gpio_request_one(&pdev->dev, ddata->pd_gpio,
				GPIOF_OUT_INIT_LOW, "tfp410 PD");
		अगर (r) अणु
			dev_err(&pdev->dev, "Failed to request PD GPIO %d\n",
					ddata->pd_gpio);
			जाओ err_gpio;
		पूर्ण
	पूर्ण

	dssdev = &ddata->dssdev;
	dssdev->ops.dvi = &tfp410_dvi_ops;
	dssdev->dev = &pdev->dev;
	dssdev->type = OMAP_DISPLAY_TYPE_DPI;
	dssdev->output_type = OMAP_DISPLAY_TYPE_DVI;
	dssdev->owner = THIS_MODULE;
	dssdev->phy.dpi.data_lines = ddata->data_lines;
	dssdev->port_num = 1;

	r = omapdss_रेजिस्टर_output(dssdev);
	अगर (r) अणु
		dev_err(&pdev->dev, "Failed to register output\n");
		जाओ err_reg;
	पूर्ण

	वापस 0;
err_reg:
err_gpio:
	omap_dss_put_device(ddata->in);
	वापस r;
पूर्ण

अटल पूर्णांक __निकास tfp410_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा panel_drv_data *ddata = platक्रमm_get_drvdata(pdev);
	काष्ठा omap_dss_device *dssdev = &ddata->dssdev;
	काष्ठा omap_dss_device *in = ddata->in;

	omapdss_unरेजिस्टर_output(&ddata->dssdev);

	WARN_ON(omapdss_device_is_enabled(dssdev));
	अगर (omapdss_device_is_enabled(dssdev))
		tfp410_disable(dssdev);

	WARN_ON(omapdss_device_is_connected(dssdev));
	अगर (omapdss_device_is_connected(dssdev))
		tfp410_disconnect(dssdev, dssdev->dst);

	omap_dss_put_device(in);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id tfp410_of_match[] = अणु
	अणु .compatible = "omapdss,ti,tfp410", पूर्ण,
	अणुपूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(of, tfp410_of_match);

अटल काष्ठा platक्रमm_driver tfp410_driver = अणु
	.probe	= tfp410_probe,
	.हटाओ	= __निकास_p(tfp410_हटाओ),
	.driver	= अणु
		.name	= "tfp410",
		.of_match_table = tfp410_of_match,
		.suppress_bind_attrs = true,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(tfp410_driver);

MODULE_AUTHOR("Tomi Valkeinen <tomi.valkeinen@ti.com>");
MODULE_DESCRIPTION("TFP410 DPI to DVI encoder driver");
MODULE_LICENSE("GPL");
