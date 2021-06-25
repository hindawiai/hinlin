<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Analog TV Connector driver
 *
 * Copyright (C) 2013 Texas Instruments
 * Author: Tomi Valkeinen <tomi.valkeinen@ti.com>
 */

#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/of.h>

#समावेश <video/omapfb_dss.h>
#समावेश <video/omap-panel-data.h>

काष्ठा panel_drv_data अणु
	काष्ठा omap_dss_device dssdev;
	काष्ठा omap_dss_device *in;

	काष्ठा device *dev;

	काष्ठा omap_video_timings timings;

	bool invert_polarity;
पूर्ण;

अटल स्थिर काष्ठा omap_video_timings tvc_pal_timings = अणु
	.x_res		= 720,
	.y_res		= 574,
	.pixelघड़ी	= 13500000,
	.hsw		= 64,
	.hfp		= 12,
	.hbp		= 68,
	.vsw		= 5,
	.vfp		= 5,
	.vbp		= 41,

	.पूर्णांकerlace	= true,
पूर्ण;

अटल स्थिर काष्ठा of_device_id tvc_of_match[];

#घोषणा to_panel_data(x) container_of(x, काष्ठा panel_drv_data, dssdev)

अटल पूर्णांक tvc_connect(काष्ठा omap_dss_device *dssdev)
अणु
	काष्ठा panel_drv_data *ddata = to_panel_data(dssdev);
	काष्ठा omap_dss_device *in = ddata->in;

	dev_dbg(ddata->dev, "connect\n");

	अगर (omapdss_device_is_connected(dssdev))
		वापस 0;

	वापस in->ops.atv->connect(in, dssdev);
पूर्ण

अटल व्योम tvc_disconnect(काष्ठा omap_dss_device *dssdev)
अणु
	काष्ठा panel_drv_data *ddata = to_panel_data(dssdev);
	काष्ठा omap_dss_device *in = ddata->in;

	dev_dbg(ddata->dev, "disconnect\n");

	अगर (!omapdss_device_is_connected(dssdev))
		वापस;

	in->ops.atv->disconnect(in, dssdev);
पूर्ण

अटल पूर्णांक tvc_enable(काष्ठा omap_dss_device *dssdev)
अणु
	काष्ठा panel_drv_data *ddata = to_panel_data(dssdev);
	काष्ठा omap_dss_device *in = ddata->in;
	पूर्णांक r;

	dev_dbg(ddata->dev, "enable\n");

	अगर (!omapdss_device_is_connected(dssdev))
		वापस -ENODEV;

	अगर (omapdss_device_is_enabled(dssdev))
		वापस 0;

	in->ops.atv->set_timings(in, &ddata->timings);

	अगर (!ddata->dev->of_node) अणु
		in->ops.atv->set_type(in, OMAP_DSS_VENC_TYPE_COMPOSITE);

		in->ops.atv->invert_vid_out_polarity(in,
			ddata->invert_polarity);
	पूर्ण

	r = in->ops.atv->enable(in);
	अगर (r)
		वापस r;

	dssdev->state = OMAP_DSS_DISPLAY_ACTIVE;

	वापस r;
पूर्ण

अटल व्योम tvc_disable(काष्ठा omap_dss_device *dssdev)
अणु
	काष्ठा panel_drv_data *ddata = to_panel_data(dssdev);
	काष्ठा omap_dss_device *in = ddata->in;

	dev_dbg(ddata->dev, "disable\n");

	अगर (!omapdss_device_is_enabled(dssdev))
		वापस;

	in->ops.atv->disable(in);

	dssdev->state = OMAP_DSS_DISPLAY_DISABLED;
पूर्ण

अटल व्योम tvc_set_timings(काष्ठा omap_dss_device *dssdev,
		काष्ठा omap_video_timings *timings)
अणु
	काष्ठा panel_drv_data *ddata = to_panel_data(dssdev);
	काष्ठा omap_dss_device *in = ddata->in;

	ddata->timings = *timings;
	dssdev->panel.timings = *timings;

	in->ops.atv->set_timings(in, timings);
पूर्ण

अटल व्योम tvc_get_timings(काष्ठा omap_dss_device *dssdev,
		काष्ठा omap_video_timings *timings)
अणु
	काष्ठा panel_drv_data *ddata = to_panel_data(dssdev);

	*timings = ddata->timings;
पूर्ण

अटल पूर्णांक tvc_check_timings(काष्ठा omap_dss_device *dssdev,
		काष्ठा omap_video_timings *timings)
अणु
	काष्ठा panel_drv_data *ddata = to_panel_data(dssdev);
	काष्ठा omap_dss_device *in = ddata->in;

	वापस in->ops.atv->check_timings(in, timings);
पूर्ण

अटल u32 tvc_get_wss(काष्ठा omap_dss_device *dssdev)
अणु
	काष्ठा panel_drv_data *ddata = to_panel_data(dssdev);
	काष्ठा omap_dss_device *in = ddata->in;

	वापस in->ops.atv->get_wss(in);
पूर्ण

अटल पूर्णांक tvc_set_wss(काष्ठा omap_dss_device *dssdev, u32 wss)
अणु
	काष्ठा panel_drv_data *ddata = to_panel_data(dssdev);
	काष्ठा omap_dss_device *in = ddata->in;

	वापस in->ops.atv->set_wss(in, wss);
पूर्ण

अटल काष्ठा omap_dss_driver tvc_driver = अणु
	.connect		= tvc_connect,
	.disconnect		= tvc_disconnect,

	.enable			= tvc_enable,
	.disable		= tvc_disable,

	.set_timings		= tvc_set_timings,
	.get_timings		= tvc_get_timings,
	.check_timings		= tvc_check_timings,

	.get_resolution		= omapdss_शेष_get_resolution,

	.get_wss		= tvc_get_wss,
	.set_wss		= tvc_set_wss,
पूर्ण;

अटल पूर्णांक tvc_probe_pdata(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा panel_drv_data *ddata = platक्रमm_get_drvdata(pdev);
	काष्ठा connector_atv_platक्रमm_data *pdata;
	काष्ठा omap_dss_device *in, *dssdev;

	pdata = dev_get_platdata(&pdev->dev);

	in = omap_dss_find_output(pdata->source);
	अगर (in == शून्य) अणु
		dev_err(&pdev->dev, "Failed to find video source\n");
		वापस -EPROBE_DEFER;
	पूर्ण

	ddata->in = in;

	ddata->invert_polarity = pdata->invert_polarity;

	dssdev = &ddata->dssdev;
	dssdev->name = pdata->name;

	वापस 0;
पूर्ण

अटल पूर्णांक tvc_probe_of(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा panel_drv_data *ddata = platक्रमm_get_drvdata(pdev);
	काष्ठा device_node *node = pdev->dev.of_node;
	काष्ठा omap_dss_device *in;

	in = omapdss_of_find_source_क्रम_first_ep(node);
	अगर (IS_ERR(in)) अणु
		dev_err(&pdev->dev, "failed to find video source\n");
		वापस PTR_ERR(in);
	पूर्ण

	ddata->in = in;

	वापस 0;
पूर्ण

अटल पूर्णांक tvc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा panel_drv_data *ddata;
	काष्ठा omap_dss_device *dssdev;
	पूर्णांक r;

	ddata = devm_kzalloc(&pdev->dev, माप(*ddata), GFP_KERNEL);
	अगर (!ddata)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, ddata);
	ddata->dev = &pdev->dev;

	अगर (dev_get_platdata(&pdev->dev)) अणु
		r = tvc_probe_pdata(pdev);
		अगर (r)
			वापस r;
	पूर्ण अन्यथा अगर (pdev->dev.of_node) अणु
		r = tvc_probe_of(pdev);
		अगर (r)
			वापस r;
	पूर्ण अन्यथा अणु
		वापस -ENODEV;
	पूर्ण

	ddata->timings = tvc_pal_timings;

	dssdev = &ddata->dssdev;
	dssdev->driver = &tvc_driver;
	dssdev->dev = &pdev->dev;
	dssdev->type = OMAP_DISPLAY_TYPE_VENC;
	dssdev->owner = THIS_MODULE;
	dssdev->panel.timings = tvc_pal_timings;

	r = omapdss_रेजिस्टर_display(dssdev);
	अगर (r) अणु
		dev_err(&pdev->dev, "Failed to register panel\n");
		जाओ err_reg;
	पूर्ण

	वापस 0;
err_reg:
	omap_dss_put_device(ddata->in);
	वापस r;
पूर्ण

अटल पूर्णांक __निकास tvc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा panel_drv_data *ddata = platक्रमm_get_drvdata(pdev);
	काष्ठा omap_dss_device *dssdev = &ddata->dssdev;
	काष्ठा omap_dss_device *in = ddata->in;

	omapdss_unरेजिस्टर_display(&ddata->dssdev);

	tvc_disable(dssdev);
	tvc_disconnect(dssdev);

	omap_dss_put_device(in);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id tvc_of_match[] = अणु
	अणु .compatible = "omapdss,svideo-connector", पूर्ण,
	अणु .compatible = "omapdss,composite-video-connector", पूर्ण,
	अणुपूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(of, tvc_of_match);

अटल काष्ठा platक्रमm_driver tvc_connector_driver = अणु
	.probe	= tvc_probe,
	.हटाओ	= __निकास_p(tvc_हटाओ),
	.driver	= अणु
		.name	= "connector-analog-tv",
		.of_match_table = tvc_of_match,
		.suppress_bind_attrs = true,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(tvc_connector_driver);

MODULE_AUTHOR("Tomi Valkeinen <tomi.valkeinen@ti.com>");
MODULE_DESCRIPTION("Analog TV Connector driver");
MODULE_LICENSE("GPL");
