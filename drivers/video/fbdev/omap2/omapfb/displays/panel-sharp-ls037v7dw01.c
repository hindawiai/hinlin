<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * LCD panel driver क्रम Sharp LS037V7DW01
 *
 * Copyright (C) 2013 Texas Instruments
 * Author: Tomi Valkeinen <tomi.valkeinen@ti.com>
 */

#समावेश <linux/delay.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_gpपन.स>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <video/omapfb_dss.h>

काष्ठा panel_drv_data अणु
	काष्ठा omap_dss_device dssdev;
	काष्ठा omap_dss_device *in;
	काष्ठा regulator *vcc;

	पूर्णांक data_lines;

	काष्ठा omap_video_timings videomode;

	काष्ठा gpio_desc *resb_gpio;	/* low = reset active min 20 us */
	काष्ठा gpio_desc *ini_gpio;	/* high = घातer on */
	काष्ठा gpio_desc *mo_gpio;	/* low = 480x640, high = 240x320 */
	काष्ठा gpio_desc *lr_gpio;	/* high = conventional horizontal scanning */
	काष्ठा gpio_desc *ud_gpio;	/* high = conventional vertical scanning */
पूर्ण;

अटल स्थिर काष्ठा omap_video_timings sharp_ls_timings = अणु
	.x_res = 480,
	.y_res = 640,

	.pixelघड़ी	= 19200000,

	.hsw		= 2,
	.hfp		= 1,
	.hbp		= 28,

	.vsw		= 1,
	.vfp		= 1,
	.vbp		= 1,

	.vsync_level	= OMAPDSS_SIG_ACTIVE_LOW,
	.hsync_level	= OMAPDSS_SIG_ACTIVE_LOW,
	.data_pclk_edge	= OMAPDSS_DRIVE_SIG_RISING_EDGE,
	.de_level	= OMAPDSS_SIG_ACTIVE_HIGH,
	.sync_pclk_edge	= OMAPDSS_DRIVE_SIG_FALLING_EDGE,
पूर्ण;

#घोषणा to_panel_data(p) container_of(p, काष्ठा panel_drv_data, dssdev)

अटल पूर्णांक sharp_ls_connect(काष्ठा omap_dss_device *dssdev)
अणु
	काष्ठा panel_drv_data *ddata = to_panel_data(dssdev);
	काष्ठा omap_dss_device *in = ddata->in;

	अगर (omapdss_device_is_connected(dssdev))
		वापस 0;

	वापस in->ops.dpi->connect(in, dssdev);
पूर्ण

अटल व्योम sharp_ls_disconnect(काष्ठा omap_dss_device *dssdev)
अणु
	काष्ठा panel_drv_data *ddata = to_panel_data(dssdev);
	काष्ठा omap_dss_device *in = ddata->in;

	अगर (!omapdss_device_is_connected(dssdev))
		वापस;

	in->ops.dpi->disconnect(in, dssdev);
पूर्ण

अटल पूर्णांक sharp_ls_enable(काष्ठा omap_dss_device *dssdev)
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

	अगर (ddata->vcc) अणु
		r = regulator_enable(ddata->vcc);
		अगर (r != 0)
			वापस r;
	पूर्ण

	r = in->ops.dpi->enable(in);
	अगर (r) अणु
		regulator_disable(ddata->vcc);
		वापस r;
	पूर्ण

	/* रुको couple of vsyncs until enabling the LCD */
	msleep(50);

	अगर (ddata->resb_gpio)
		gpiod_set_value_cansleep(ddata->resb_gpio, 1);

	अगर (ddata->ini_gpio)
		gpiod_set_value_cansleep(ddata->ini_gpio, 1);

	dssdev->state = OMAP_DSS_DISPLAY_ACTIVE;

	वापस 0;
पूर्ण

अटल व्योम sharp_ls_disable(काष्ठा omap_dss_device *dssdev)
अणु
	काष्ठा panel_drv_data *ddata = to_panel_data(dssdev);
	काष्ठा omap_dss_device *in = ddata->in;

	अगर (!omapdss_device_is_enabled(dssdev))
		वापस;

	अगर (ddata->ini_gpio)
		gpiod_set_value_cansleep(ddata->ini_gpio, 0);

	अगर (ddata->resb_gpio)
		gpiod_set_value_cansleep(ddata->resb_gpio, 0);

	/* रुको at least 5 vsyncs after disabling the LCD */

	msleep(100);

	in->ops.dpi->disable(in);

	अगर (ddata->vcc)
		regulator_disable(ddata->vcc);

	dssdev->state = OMAP_DSS_DISPLAY_DISABLED;
पूर्ण

अटल व्योम sharp_ls_set_timings(काष्ठा omap_dss_device *dssdev,
		काष्ठा omap_video_timings *timings)
अणु
	काष्ठा panel_drv_data *ddata = to_panel_data(dssdev);
	काष्ठा omap_dss_device *in = ddata->in;

	ddata->videomode = *timings;
	dssdev->panel.timings = *timings;

	in->ops.dpi->set_timings(in, timings);
पूर्ण

अटल व्योम sharp_ls_get_timings(काष्ठा omap_dss_device *dssdev,
		काष्ठा omap_video_timings *timings)
अणु
	काष्ठा panel_drv_data *ddata = to_panel_data(dssdev);

	*timings = ddata->videomode;
पूर्ण

अटल पूर्णांक sharp_ls_check_timings(काष्ठा omap_dss_device *dssdev,
		काष्ठा omap_video_timings *timings)
अणु
	काष्ठा panel_drv_data *ddata = to_panel_data(dssdev);
	काष्ठा omap_dss_device *in = ddata->in;

	वापस in->ops.dpi->check_timings(in, timings);
पूर्ण

अटल काष्ठा omap_dss_driver sharp_ls_ops = अणु
	.connect	= sharp_ls_connect,
	.disconnect	= sharp_ls_disconnect,

	.enable		= sharp_ls_enable,
	.disable	= sharp_ls_disable,

	.set_timings	= sharp_ls_set_timings,
	.get_timings	= sharp_ls_get_timings,
	.check_timings	= sharp_ls_check_timings,

	.get_resolution	= omapdss_शेष_get_resolution,
पूर्ण;

अटल  पूर्णांक sharp_ls_get_gpio_of(काष्ठा device *dev, पूर्णांक index, पूर्णांक val,
	स्थिर अक्षर *desc, काष्ठा gpio_desc **gpiod)
अणु
	काष्ठा gpio_desc *gd;

	*gpiod = शून्य;

	gd = devm_gpiod_get_index(dev, desc, index, GPIOD_OUT_LOW);
	अगर (IS_ERR(gd))
		वापस PTR_ERR(gd);

	*gpiod = gd;
	वापस 0;
पूर्ण

अटल पूर्णांक sharp_ls_probe_of(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा panel_drv_data *ddata = platक्रमm_get_drvdata(pdev);
	काष्ठा device_node *node = pdev->dev.of_node;
	काष्ठा omap_dss_device *in;
	पूर्णांक r;

	ddata->vcc = devm_regulator_get(&pdev->dev, "envdd");
	अगर (IS_ERR(ddata->vcc)) अणु
		dev_err(&pdev->dev, "failed to get regulator\n");
		वापस PTR_ERR(ddata->vcc);
	पूर्ण

	/* lcd INI */
	r = sharp_ls_get_gpio_of(&pdev->dev, 0, 0, "enable", &ddata->ini_gpio);
	अगर (r)
		वापस r;

	/* lcd RESB */
	r = sharp_ls_get_gpio_of(&pdev->dev, 0, 0, "reset", &ddata->resb_gpio);
	अगर (r)
		वापस r;

	/* lcd MO */
	r = sharp_ls_get_gpio_of(&pdev->dev, 0, 0, "mode", &ddata->mo_gpio);
	अगर (r)
		वापस r;

	/* lcd LR */
	r = sharp_ls_get_gpio_of(&pdev->dev, 1, 1, "mode", &ddata->lr_gpio);
	अगर (r)
		वापस r;

	/* lcd UD */
	r = sharp_ls_get_gpio_of(&pdev->dev, 2, 1, "mode", &ddata->ud_gpio);
	अगर (r)
		वापस r;

	in = omapdss_of_find_source_क्रम_first_ep(node);
	अगर (IS_ERR(in)) अणु
		dev_err(&pdev->dev, "failed to find video source\n");
		वापस PTR_ERR(in);
	पूर्ण

	ddata->in = in;

	वापस 0;
पूर्ण

अटल पूर्णांक sharp_ls_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा panel_drv_data *ddata;
	काष्ठा omap_dss_device *dssdev;
	पूर्णांक r;

	अगर (!pdev->dev.of_node)
		वापस -ENODEV;

	ddata = devm_kzalloc(&pdev->dev, माप(*ddata), GFP_KERNEL);
	अगर (ddata == शून्य)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, ddata);

	r = sharp_ls_probe_of(pdev);
	अगर (r)
		वापस r;

	ddata->videomode = sharp_ls_timings;

	dssdev = &ddata->dssdev;
	dssdev->dev = &pdev->dev;
	dssdev->driver = &sharp_ls_ops;
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
	omap_dss_put_device(ddata->in);
	वापस r;
पूर्ण

अटल पूर्णांक __निकास sharp_ls_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा panel_drv_data *ddata = platक्रमm_get_drvdata(pdev);
	काष्ठा omap_dss_device *dssdev = &ddata->dssdev;
	काष्ठा omap_dss_device *in = ddata->in;

	omapdss_unरेजिस्टर_display(dssdev);

	sharp_ls_disable(dssdev);
	sharp_ls_disconnect(dssdev);

	omap_dss_put_device(in);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id sharp_ls_of_match[] = अणु
	अणु .compatible = "omapdss,sharp,ls037v7dw01", पूर्ण,
	अणुपूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(of, sharp_ls_of_match);

अटल काष्ठा platक्रमm_driver sharp_ls_driver = अणु
	.probe = sharp_ls_probe,
	.हटाओ = __निकास_p(sharp_ls_हटाओ),
	.driver = अणु
		.name = "panel-sharp-ls037v7dw01",
		.of_match_table = sharp_ls_of_match,
		.suppress_bind_attrs = true,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(sharp_ls_driver);

MODULE_AUTHOR("Tomi Valkeinen <tomi.valkeinen@ti.com>");
MODULE_DESCRIPTION("Sharp LS037V7DW01 Panel Driver");
MODULE_LICENSE("GPL");
