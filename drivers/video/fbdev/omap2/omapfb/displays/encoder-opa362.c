<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * OPA362 analog video amplअगरier with output/घातer control
 *
 * Copyright (C) 2014 Golden Delicious Computers
 * Author: H. Nikolaus Schaller <hns@goldelico.com>
 *
 * based on encoder-tfp410
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

	काष्ठा gpio_desc *enable_gpio;

	काष्ठा omap_video_timings timings;
पूर्ण;

#घोषणा to_panel_data(x) container_of(x, काष्ठा panel_drv_data, dssdev)

अटल पूर्णांक opa362_connect(काष्ठा omap_dss_device *dssdev,
		काष्ठा omap_dss_device *dst)
अणु
	काष्ठा panel_drv_data *ddata = to_panel_data(dssdev);
	काष्ठा omap_dss_device *in = ddata->in;
	पूर्णांक r;

	dev_dbg(dssdev->dev, "connect\n");

	अगर (omapdss_device_is_connected(dssdev))
		वापस -EBUSY;

	r = in->ops.atv->connect(in, dssdev);
	अगर (r)
		वापस r;

	dst->src = dssdev;
	dssdev->dst = dst;

	वापस 0;
पूर्ण

अटल व्योम opa362_disconnect(काष्ठा omap_dss_device *dssdev,
		काष्ठा omap_dss_device *dst)
अणु
	काष्ठा panel_drv_data *ddata = to_panel_data(dssdev);
	काष्ठा omap_dss_device *in = ddata->in;

	dev_dbg(dssdev->dev, "disconnect\n");

	WARN_ON(!omapdss_device_is_connected(dssdev));
	अगर (!omapdss_device_is_connected(dssdev))
		वापस;

	WARN_ON(dst != dssdev->dst);
	अगर (dst != dssdev->dst)
		वापस;

	dst->src = शून्य;
	dssdev->dst = शून्य;

	in->ops.atv->disconnect(in, &ddata->dssdev);
पूर्ण

अटल पूर्णांक opa362_enable(काष्ठा omap_dss_device *dssdev)
अणु
	काष्ठा panel_drv_data *ddata = to_panel_data(dssdev);
	काष्ठा omap_dss_device *in = ddata->in;
	पूर्णांक r;

	dev_dbg(dssdev->dev, "enable\n");

	अगर (!omapdss_device_is_connected(dssdev))
		वापस -ENODEV;

	अगर (omapdss_device_is_enabled(dssdev))
		वापस 0;

	in->ops.atv->set_timings(in, &ddata->timings);

	r = in->ops.atv->enable(in);
	अगर (r)
		वापस r;

	अगर (ddata->enable_gpio)
		gpiod_set_value_cansleep(ddata->enable_gpio, 1);

	dssdev->state = OMAP_DSS_DISPLAY_ACTIVE;

	वापस 0;
पूर्ण

अटल व्योम opa362_disable(काष्ठा omap_dss_device *dssdev)
अणु
	काष्ठा panel_drv_data *ddata = to_panel_data(dssdev);
	काष्ठा omap_dss_device *in = ddata->in;

	dev_dbg(dssdev->dev, "disable\n");

	अगर (!omapdss_device_is_enabled(dssdev))
		वापस;

	अगर (ddata->enable_gpio)
		gpiod_set_value_cansleep(ddata->enable_gpio, 0);

	in->ops.atv->disable(in);

	dssdev->state = OMAP_DSS_DISPLAY_DISABLED;
पूर्ण

अटल व्योम opa362_set_timings(काष्ठा omap_dss_device *dssdev,
		काष्ठा omap_video_timings *timings)
अणु
	काष्ठा panel_drv_data *ddata = to_panel_data(dssdev);
	काष्ठा omap_dss_device *in = ddata->in;

	dev_dbg(dssdev->dev, "set_timings\n");

	ddata->timings = *timings;
	dssdev->panel.timings = *timings;

	in->ops.atv->set_timings(in, timings);
पूर्ण

अटल व्योम opa362_get_timings(काष्ठा omap_dss_device *dssdev,
		काष्ठा omap_video_timings *timings)
अणु
	काष्ठा panel_drv_data *ddata = to_panel_data(dssdev);

	dev_dbg(dssdev->dev, "get_timings\n");

	*timings = ddata->timings;
पूर्ण

अटल पूर्णांक opa362_check_timings(काष्ठा omap_dss_device *dssdev,
		काष्ठा omap_video_timings *timings)
अणु
	काष्ठा panel_drv_data *ddata = to_panel_data(dssdev);
	काष्ठा omap_dss_device *in = ddata->in;

	dev_dbg(dssdev->dev, "check_timings\n");

	वापस in->ops.atv->check_timings(in, timings);
पूर्ण

अटल व्योम opa362_set_type(काष्ठा omap_dss_device *dssdev,
		क्रमागत omap_dss_venc_type type)
अणु
	/* we can only drive a COMPOSITE output */
	WARN_ON(type != OMAP_DSS_VENC_TYPE_COMPOSITE);

पूर्ण

अटल स्थिर काष्ठा omapdss_atv_ops opa362_atv_ops = अणु
	.connect	= opa362_connect,
	.disconnect	= opa362_disconnect,

	.enable		= opa362_enable,
	.disable	= opa362_disable,

	.check_timings	= opa362_check_timings,
	.set_timings	= opa362_set_timings,
	.get_timings	= opa362_get_timings,

	.set_type	= opa362_set_type,
पूर्ण;

अटल पूर्णांक opa362_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *node = pdev->dev.of_node;
	काष्ठा panel_drv_data *ddata;
	काष्ठा omap_dss_device *dssdev, *in;
	काष्ठा gpio_desc *gpio;
	पूर्णांक r;

	dev_dbg(&pdev->dev, "probe\n");

	अगर (node == शून्य) अणु
		dev_err(&pdev->dev, "Unable to find device tree\n");
		वापस -EINVAL;
	पूर्ण

	ddata = devm_kzalloc(&pdev->dev, माप(*ddata), GFP_KERNEL);
	अगर (!ddata)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, ddata);

	gpio = devm_gpiod_get_optional(&pdev->dev, "enable", GPIOD_OUT_LOW);
	अगर (IS_ERR(gpio))
		वापस PTR_ERR(gpio);

	ddata->enable_gpio = gpio;

	in = omapdss_of_find_source_क्रम_first_ep(node);
	अगर (IS_ERR(in)) अणु
		dev_err(&pdev->dev, "failed to find video source\n");
		वापस PTR_ERR(in);
	पूर्ण

	ddata->in = in;

	dssdev = &ddata->dssdev;
	dssdev->ops.atv = &opa362_atv_ops;
	dssdev->dev = &pdev->dev;
	dssdev->type = OMAP_DISPLAY_TYPE_VENC;
	dssdev->output_type = OMAP_DISPLAY_TYPE_VENC;
	dssdev->owner = THIS_MODULE;

	r = omapdss_रेजिस्टर_output(dssdev);
	अगर (r) अणु
		dev_err(&pdev->dev, "Failed to register output\n");
		जाओ err_reg;
	पूर्ण

	वापस 0;
err_reg:
	omap_dss_put_device(ddata->in);
	वापस r;
पूर्ण

अटल पूर्णांक __निकास opa362_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा panel_drv_data *ddata = platक्रमm_get_drvdata(pdev);
	काष्ठा omap_dss_device *dssdev = &ddata->dssdev;
	काष्ठा omap_dss_device *in = ddata->in;

	omapdss_unरेजिस्टर_output(&ddata->dssdev);

	WARN_ON(omapdss_device_is_enabled(dssdev));
	अगर (omapdss_device_is_enabled(dssdev))
		opa362_disable(dssdev);

	WARN_ON(omapdss_device_is_connected(dssdev));
	अगर (omapdss_device_is_connected(dssdev))
		opa362_disconnect(dssdev, dssdev->dst);

	omap_dss_put_device(in);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id opa362_of_match[] = अणु
	अणु .compatible = "omapdss,ti,opa362", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, opa362_of_match);

अटल काष्ठा platक्रमm_driver opa362_driver = अणु
	.probe	= opa362_probe,
	.हटाओ	= __निकास_p(opa362_हटाओ),
	.driver	= अणु
		.name	= "amplifier-opa362",
		.of_match_table = opa362_of_match,
		.suppress_bind_attrs = true,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(opa362_driver);

MODULE_AUTHOR("H. Nikolaus Schaller <hns@goldelico.com>");
MODULE_DESCRIPTION("OPA362 analog video amplifier with output/power control");
MODULE_LICENSE("GPL v2");
