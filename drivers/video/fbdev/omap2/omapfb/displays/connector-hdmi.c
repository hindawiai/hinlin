<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * HDMI Connector driver
 *
 * Copyright (C) 2013 Texas Instruments
 * Author: Tomi Valkeinen <tomi.valkeinen@ti.com>
 */

#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/of.h>
#समावेश <linux/of_gpपन.स>

#समावेश <drm/drm_edid.h>

#समावेश <video/omapfb_dss.h>

अटल स्थिर काष्ठा omap_video_timings hdmic_शेष_timings = अणु
	.x_res		= 640,
	.y_res		= 480,
	.pixelघड़ी	= 25175000,
	.hsw		= 96,
	.hfp		= 16,
	.hbp		= 48,
	.vsw		= 2,
	.vfp		= 11,
	.vbp		= 31,

	.vsync_level	= OMAPDSS_SIG_ACTIVE_LOW,
	.hsync_level	= OMAPDSS_SIG_ACTIVE_LOW,

	.पूर्णांकerlace	= false,
पूर्ण;

काष्ठा panel_drv_data अणु
	काष्ठा omap_dss_device dssdev;
	काष्ठा omap_dss_device *in;

	काष्ठा device *dev;

	काष्ठा omap_video_timings timings;

	पूर्णांक hpd_gpio;
पूर्ण;

#घोषणा to_panel_data(x) container_of(x, काष्ठा panel_drv_data, dssdev)

अटल पूर्णांक hdmic_connect(काष्ठा omap_dss_device *dssdev)
अणु
	काष्ठा panel_drv_data *ddata = to_panel_data(dssdev);
	काष्ठा omap_dss_device *in = ddata->in;

	dev_dbg(ddata->dev, "connect\n");

	अगर (omapdss_device_is_connected(dssdev))
		वापस 0;

	वापस in->ops.hdmi->connect(in, dssdev);
पूर्ण

अटल व्योम hdmic_disconnect(काष्ठा omap_dss_device *dssdev)
अणु
	काष्ठा panel_drv_data *ddata = to_panel_data(dssdev);
	काष्ठा omap_dss_device *in = ddata->in;

	dev_dbg(ddata->dev, "disconnect\n");

	अगर (!omapdss_device_is_connected(dssdev))
		वापस;

	in->ops.hdmi->disconnect(in, dssdev);
पूर्ण

अटल पूर्णांक hdmic_enable(काष्ठा omap_dss_device *dssdev)
अणु
	काष्ठा panel_drv_data *ddata = to_panel_data(dssdev);
	काष्ठा omap_dss_device *in = ddata->in;
	पूर्णांक r;

	dev_dbg(ddata->dev, "enable\n");

	अगर (!omapdss_device_is_connected(dssdev))
		वापस -ENODEV;

	अगर (omapdss_device_is_enabled(dssdev))
		वापस 0;

	in->ops.hdmi->set_timings(in, &ddata->timings);

	r = in->ops.hdmi->enable(in);
	अगर (r)
		वापस r;

	dssdev->state = OMAP_DSS_DISPLAY_ACTIVE;

	वापस r;
पूर्ण

अटल व्योम hdmic_disable(काष्ठा omap_dss_device *dssdev)
अणु
	काष्ठा panel_drv_data *ddata = to_panel_data(dssdev);
	काष्ठा omap_dss_device *in = ddata->in;

	dev_dbg(ddata->dev, "disable\n");

	अगर (!omapdss_device_is_enabled(dssdev))
		वापस;

	in->ops.hdmi->disable(in);

	dssdev->state = OMAP_DSS_DISPLAY_DISABLED;
पूर्ण

अटल व्योम hdmic_set_timings(काष्ठा omap_dss_device *dssdev,
		काष्ठा omap_video_timings *timings)
अणु
	काष्ठा panel_drv_data *ddata = to_panel_data(dssdev);
	काष्ठा omap_dss_device *in = ddata->in;

	ddata->timings = *timings;
	dssdev->panel.timings = *timings;

	in->ops.hdmi->set_timings(in, timings);
पूर्ण

अटल व्योम hdmic_get_timings(काष्ठा omap_dss_device *dssdev,
		काष्ठा omap_video_timings *timings)
अणु
	काष्ठा panel_drv_data *ddata = to_panel_data(dssdev);

	*timings = ddata->timings;
पूर्ण

अटल पूर्णांक hdmic_check_timings(काष्ठा omap_dss_device *dssdev,
		काष्ठा omap_video_timings *timings)
अणु
	काष्ठा panel_drv_data *ddata = to_panel_data(dssdev);
	काष्ठा omap_dss_device *in = ddata->in;

	वापस in->ops.hdmi->check_timings(in, timings);
पूर्ण

अटल पूर्णांक hdmic_पढ़ो_edid(काष्ठा omap_dss_device *dssdev,
		u8 *edid, पूर्णांक len)
अणु
	काष्ठा panel_drv_data *ddata = to_panel_data(dssdev);
	काष्ठा omap_dss_device *in = ddata->in;

	वापस in->ops.hdmi->पढ़ो_edid(in, edid, len);
पूर्ण

अटल bool hdmic_detect(काष्ठा omap_dss_device *dssdev)
अणु
	काष्ठा panel_drv_data *ddata = to_panel_data(dssdev);
	काष्ठा omap_dss_device *in = ddata->in;

	अगर (gpio_is_valid(ddata->hpd_gpio))
		वापस gpio_get_value_cansleep(ddata->hpd_gpio);
	अन्यथा
		वापस in->ops.hdmi->detect(in);
पूर्ण

अटल पूर्णांक hdmic_set_hdmi_mode(काष्ठा omap_dss_device *dssdev, bool hdmi_mode)
अणु
	काष्ठा panel_drv_data *ddata = to_panel_data(dssdev);
	काष्ठा omap_dss_device *in = ddata->in;

	वापस in->ops.hdmi->set_hdmi_mode(in, hdmi_mode);
पूर्ण

अटल पूर्णांक hdmic_set_infoframe(काष्ठा omap_dss_device *dssdev,
		स्थिर काष्ठा hdmi_avi_infoframe *avi)
अणु
	काष्ठा panel_drv_data *ddata = to_panel_data(dssdev);
	काष्ठा omap_dss_device *in = ddata->in;

	वापस in->ops.hdmi->set_infoframe(in, avi);
पूर्ण

अटल काष्ठा omap_dss_driver hdmic_driver = अणु
	.connect		= hdmic_connect,
	.disconnect		= hdmic_disconnect,

	.enable			= hdmic_enable,
	.disable		= hdmic_disable,

	.set_timings		= hdmic_set_timings,
	.get_timings		= hdmic_get_timings,
	.check_timings		= hdmic_check_timings,

	.get_resolution		= omapdss_शेष_get_resolution,

	.पढ़ो_edid		= hdmic_पढ़ो_edid,
	.detect			= hdmic_detect,
	.set_hdmi_mode		= hdmic_set_hdmi_mode,
	.set_hdmi_infoframe	= hdmic_set_infoframe,
पूर्ण;

अटल पूर्णांक hdmic_probe_of(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा panel_drv_data *ddata = platक्रमm_get_drvdata(pdev);
	काष्ठा device_node *node = pdev->dev.of_node;
	काष्ठा omap_dss_device *in;
	पूर्णांक gpio;

	/* HPD GPIO */
	gpio = of_get_named_gpio(node, "hpd-gpios", 0);
	अगर (gpio_is_valid(gpio))
		ddata->hpd_gpio = gpio;
	अन्यथा
		ddata->hpd_gpio = -ENODEV;

	in = omapdss_of_find_source_क्रम_first_ep(node);
	अगर (IS_ERR(in)) अणु
		dev_err(&pdev->dev, "failed to find video source\n");
		वापस PTR_ERR(in);
	पूर्ण

	ddata->in = in;

	वापस 0;
पूर्ण

अटल पूर्णांक hdmic_probe(काष्ठा platक्रमm_device *pdev)
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
	ddata->dev = &pdev->dev;

	r = hdmic_probe_of(pdev);
	अगर (r)
		वापस r;

	अगर (gpio_is_valid(ddata->hpd_gpio)) अणु
		r = devm_gpio_request_one(&pdev->dev, ddata->hpd_gpio,
				GPIOF_सूची_IN, "hdmi_hpd");
		अगर (r)
			जाओ err_reg;
	पूर्ण

	ddata->timings = hdmic_शेष_timings;

	dssdev = &ddata->dssdev;
	dssdev->driver = &hdmic_driver;
	dssdev->dev = &pdev->dev;
	dssdev->type = OMAP_DISPLAY_TYPE_HDMI;
	dssdev->owner = THIS_MODULE;
	dssdev->panel.timings = hdmic_शेष_timings;

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

अटल पूर्णांक __निकास hdmic_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा panel_drv_data *ddata = platक्रमm_get_drvdata(pdev);
	काष्ठा omap_dss_device *dssdev = &ddata->dssdev;
	काष्ठा omap_dss_device *in = ddata->in;

	omapdss_unरेजिस्टर_display(&ddata->dssdev);

	hdmic_disable(dssdev);
	hdmic_disconnect(dssdev);

	omap_dss_put_device(in);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id hdmic_of_match[] = अणु
	अणु .compatible = "omapdss,hdmi-connector", पूर्ण,
	अणुपूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(of, hdmic_of_match);

अटल काष्ठा platक्रमm_driver hdmi_connector_driver = अणु
	.probe	= hdmic_probe,
	.हटाओ	= __निकास_p(hdmic_हटाओ),
	.driver	= अणु
		.name	= "connector-hdmi",
		.of_match_table = hdmic_of_match,
		.suppress_bind_attrs = true,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(hdmi_connector_driver);

MODULE_AUTHOR("Tomi Valkeinen <tomi.valkeinen@ti.com>");
MODULE_DESCRIPTION("HDMI Connector driver");
MODULE_LICENSE("GPL");
