<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * TPD12S015 HDMI ESD protection & level shअगरter chip driver
 *
 * Copyright (C) 2013 Texas Instruments
 * Author: Tomi Valkeinen <tomi.valkeinen@ti.com>
 */

#समावेश <linux/completion.h>
#समावेश <linux/delay.h>
#समावेश <linux/module.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/slab.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/gpio/consumer.h>

#समावेश <video/omapfb_dss.h>

काष्ठा panel_drv_data अणु
	काष्ठा omap_dss_device dssdev;
	काष्ठा omap_dss_device *in;

	काष्ठा gpio_desc *ct_cp_hpd_gpio;
	काष्ठा gpio_desc *ls_oe_gpio;
	काष्ठा gpio_desc *hpd_gpio;

	काष्ठा omap_video_timings timings;
पूर्ण;

#घोषणा to_panel_data(x) container_of(x, काष्ठा panel_drv_data, dssdev)

अटल पूर्णांक tpd_connect(काष्ठा omap_dss_device *dssdev,
		काष्ठा omap_dss_device *dst)
अणु
	काष्ठा panel_drv_data *ddata = to_panel_data(dssdev);
	काष्ठा omap_dss_device *in = ddata->in;
	पूर्णांक r;

	r = in->ops.hdmi->connect(in, dssdev);
	अगर (r)
		वापस r;

	dst->src = dssdev;
	dssdev->dst = dst;

	अगर (ddata->ct_cp_hpd_gpio) अणु
		gpiod_set_value_cansleep(ddata->ct_cp_hpd_gpio, 1);
		/* DC-DC converter needs at max 300us to get to 90% of 5V */
		udelay(300);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम tpd_disconnect(काष्ठा omap_dss_device *dssdev,
		काष्ठा omap_dss_device *dst)
अणु
	काष्ठा panel_drv_data *ddata = to_panel_data(dssdev);
	काष्ठा omap_dss_device *in = ddata->in;

	WARN_ON(dst != dssdev->dst);

	अगर (dst != dssdev->dst)
		वापस;

	gpiod_set_value_cansleep(ddata->ct_cp_hpd_gpio, 0);

	dst->src = शून्य;
	dssdev->dst = शून्य;

	in->ops.hdmi->disconnect(in, &ddata->dssdev);
पूर्ण

अटल पूर्णांक tpd_enable(काष्ठा omap_dss_device *dssdev)
अणु
	काष्ठा panel_drv_data *ddata = to_panel_data(dssdev);
	काष्ठा omap_dss_device *in = ddata->in;
	पूर्णांक r;

	अगर (dssdev->state == OMAP_DSS_DISPLAY_ACTIVE)
		वापस 0;

	in->ops.hdmi->set_timings(in, &ddata->timings);

	r = in->ops.hdmi->enable(in);
	अगर (r)
		वापस r;

	dssdev->state = OMAP_DSS_DISPLAY_ACTIVE;

	वापस r;
पूर्ण

अटल व्योम tpd_disable(काष्ठा omap_dss_device *dssdev)
अणु
	काष्ठा panel_drv_data *ddata = to_panel_data(dssdev);
	काष्ठा omap_dss_device *in = ddata->in;

	अगर (dssdev->state != OMAP_DSS_DISPLAY_ACTIVE)
		वापस;

	in->ops.hdmi->disable(in);

	dssdev->state = OMAP_DSS_DISPLAY_DISABLED;
पूर्ण

अटल व्योम tpd_set_timings(काष्ठा omap_dss_device *dssdev,
		काष्ठा omap_video_timings *timings)
अणु
	काष्ठा panel_drv_data *ddata = to_panel_data(dssdev);
	काष्ठा omap_dss_device *in = ddata->in;

	ddata->timings = *timings;
	dssdev->panel.timings = *timings;

	in->ops.hdmi->set_timings(in, timings);
पूर्ण

अटल व्योम tpd_get_timings(काष्ठा omap_dss_device *dssdev,
		काष्ठा omap_video_timings *timings)
अणु
	काष्ठा panel_drv_data *ddata = to_panel_data(dssdev);

	*timings = ddata->timings;
पूर्ण

अटल पूर्णांक tpd_check_timings(काष्ठा omap_dss_device *dssdev,
		काष्ठा omap_video_timings *timings)
अणु
	काष्ठा panel_drv_data *ddata = to_panel_data(dssdev);
	काष्ठा omap_dss_device *in = ddata->in;
	पूर्णांक r;

	r = in->ops.hdmi->check_timings(in, timings);

	वापस r;
पूर्ण

अटल पूर्णांक tpd_पढ़ो_edid(काष्ठा omap_dss_device *dssdev,
		u8 *edid, पूर्णांक len)
अणु
	काष्ठा panel_drv_data *ddata = to_panel_data(dssdev);
	काष्ठा omap_dss_device *in = ddata->in;
	पूर्णांक r;

	अगर (!gpiod_get_value_cansleep(ddata->hpd_gpio))
		वापस -ENODEV;

	gpiod_set_value_cansleep(ddata->ls_oe_gpio, 1);

	r = in->ops.hdmi->पढ़ो_edid(in, edid, len);

	gpiod_set_value_cansleep(ddata->ls_oe_gpio, 0);

	वापस r;
पूर्ण

अटल bool tpd_detect(काष्ठा omap_dss_device *dssdev)
अणु
	काष्ठा panel_drv_data *ddata = to_panel_data(dssdev);

	वापस gpiod_get_value_cansleep(ddata->hpd_gpio);
पूर्ण

अटल पूर्णांक tpd_set_infoframe(काष्ठा omap_dss_device *dssdev,
		स्थिर काष्ठा hdmi_avi_infoframe *avi)
अणु
	काष्ठा panel_drv_data *ddata = to_panel_data(dssdev);
	काष्ठा omap_dss_device *in = ddata->in;

	वापस in->ops.hdmi->set_infoframe(in, avi);
पूर्ण

अटल पूर्णांक tpd_set_hdmi_mode(काष्ठा omap_dss_device *dssdev,
		bool hdmi_mode)
अणु
	काष्ठा panel_drv_data *ddata = to_panel_data(dssdev);
	काष्ठा omap_dss_device *in = ddata->in;

	वापस in->ops.hdmi->set_hdmi_mode(in, hdmi_mode);
पूर्ण

अटल स्थिर काष्ठा omapdss_hdmi_ops tpd_hdmi_ops = अणु
	.connect		= tpd_connect,
	.disconnect		= tpd_disconnect,

	.enable			= tpd_enable,
	.disable		= tpd_disable,

	.check_timings		= tpd_check_timings,
	.set_timings		= tpd_set_timings,
	.get_timings		= tpd_get_timings,

	.पढ़ो_edid		= tpd_पढ़ो_edid,
	.detect			= tpd_detect,
	.set_infoframe		= tpd_set_infoframe,
	.set_hdmi_mode		= tpd_set_hdmi_mode,
पूर्ण;

अटल पूर्णांक tpd_probe_of(काष्ठा platक्रमm_device *pdev)
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

अटल पूर्णांक tpd_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा omap_dss_device *dssdev;
	काष्ठा panel_drv_data *ddata;
	पूर्णांक r;
	काष्ठा gpio_desc *gpio;

	ddata = devm_kzalloc(&pdev->dev, माप(*ddata), GFP_KERNEL);
	अगर (!ddata)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, ddata);

	अगर (pdev->dev.of_node) अणु
		r = tpd_probe_of(pdev);
		अगर (r)
			वापस r;
	पूर्ण अन्यथा अणु
		वापस -ENODEV;
	पूर्ण

	gpio = devm_gpiod_get_index_optional(&pdev->dev, शून्य, 0,
		GPIOD_OUT_LOW);
	अगर (IS_ERR(gpio)) अणु
		r = PTR_ERR(gpio);
		जाओ err_gpio;
	पूर्ण

	ddata->ct_cp_hpd_gpio = gpio;

	gpio = devm_gpiod_get_index_optional(&pdev->dev, शून्य, 1,
		GPIOD_OUT_LOW);
	अगर (IS_ERR(gpio)) अणु
		r = PTR_ERR(gpio);
		जाओ err_gpio;
	पूर्ण

	ddata->ls_oe_gpio = gpio;

	gpio = devm_gpiod_get_index(&pdev->dev, शून्य, 2,
		GPIOD_IN);
	अगर (IS_ERR(gpio)) अणु
		r = PTR_ERR(gpio);
		जाओ err_gpio;
	पूर्ण

	ddata->hpd_gpio = gpio;

	dssdev = &ddata->dssdev;
	dssdev->ops.hdmi = &tpd_hdmi_ops;
	dssdev->dev = &pdev->dev;
	dssdev->type = OMAP_DISPLAY_TYPE_HDMI;
	dssdev->output_type = OMAP_DISPLAY_TYPE_HDMI;
	dssdev->owner = THIS_MODULE;
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

अटल पूर्णांक __निकास tpd_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा panel_drv_data *ddata = platक्रमm_get_drvdata(pdev);
	काष्ठा omap_dss_device *dssdev = &ddata->dssdev;
	काष्ठा omap_dss_device *in = ddata->in;

	omapdss_unरेजिस्टर_output(&ddata->dssdev);

	WARN_ON(omapdss_device_is_enabled(dssdev));
	अगर (omapdss_device_is_enabled(dssdev))
		tpd_disable(dssdev);

	WARN_ON(omapdss_device_is_connected(dssdev));
	अगर (omapdss_device_is_connected(dssdev))
		tpd_disconnect(dssdev, dssdev->dst);

	omap_dss_put_device(in);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id tpd_of_match[] = अणु
	अणु .compatible = "omapdss,ti,tpd12s015", पूर्ण,
	अणुपूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(of, tpd_of_match);

अटल काष्ठा platक्रमm_driver tpd_driver = अणु
	.probe	= tpd_probe,
	.हटाओ	= __निकास_p(tpd_हटाओ),
	.driver	= अणु
		.name	= "tpd12s015",
		.of_match_table = tpd_of_match,
		.suppress_bind_attrs = true,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(tpd_driver);

MODULE_AUTHOR("Tomi Valkeinen <tomi.valkeinen@ti.com>");
MODULE_DESCRIPTION("TPD12S015 driver");
MODULE_LICENSE("GPL");
