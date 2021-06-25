<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Generic DVI Connector driver
 *
 * Copyright (C) 2013 Texas Instruments
 * Author: Tomi Valkeinen <tomi.valkeinen@ti.com>
 */

#समावेश <linux/i2c.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>

#समावेश <drm/drm_edid.h>

#समावेश <video/omapfb_dss.h>

अटल स्थिर काष्ठा omap_video_timings dvic_शेष_timings = अणु
	.x_res		= 640,
	.y_res		= 480,

	.pixelघड़ी	= 23500000,

	.hfp		= 48,
	.hsw		= 32,
	.hbp		= 80,

	.vfp		= 3,
	.vsw		= 4,
	.vbp		= 7,

	.vsync_level	= OMAPDSS_SIG_ACTIVE_HIGH,
	.hsync_level	= OMAPDSS_SIG_ACTIVE_HIGH,
	.data_pclk_edge	= OMAPDSS_DRIVE_SIG_RISING_EDGE,
	.de_level	= OMAPDSS_SIG_ACTIVE_HIGH,
	.sync_pclk_edge	= OMAPDSS_DRIVE_SIG_FALLING_EDGE,
पूर्ण;

काष्ठा panel_drv_data अणु
	काष्ठा omap_dss_device dssdev;
	काष्ठा omap_dss_device *in;

	काष्ठा omap_video_timings timings;

	काष्ठा i2c_adapter *i2c_adapter;
पूर्ण;

#घोषणा to_panel_data(x) container_of(x, काष्ठा panel_drv_data, dssdev)

अटल पूर्णांक dvic_connect(काष्ठा omap_dss_device *dssdev)
अणु
	काष्ठा panel_drv_data *ddata = to_panel_data(dssdev);
	काष्ठा omap_dss_device *in = ddata->in;

	अगर (omapdss_device_is_connected(dssdev))
		वापस 0;

	वापस in->ops.dvi->connect(in, dssdev);
पूर्ण

अटल व्योम dvic_disconnect(काष्ठा omap_dss_device *dssdev)
अणु
	काष्ठा panel_drv_data *ddata = to_panel_data(dssdev);
	काष्ठा omap_dss_device *in = ddata->in;

	अगर (!omapdss_device_is_connected(dssdev))
		वापस;

	in->ops.dvi->disconnect(in, dssdev);
पूर्ण

अटल पूर्णांक dvic_enable(काष्ठा omap_dss_device *dssdev)
अणु
	काष्ठा panel_drv_data *ddata = to_panel_data(dssdev);
	काष्ठा omap_dss_device *in = ddata->in;
	पूर्णांक r;

	अगर (!omapdss_device_is_connected(dssdev))
		वापस -ENODEV;

	अगर (omapdss_device_is_enabled(dssdev))
		वापस 0;

	in->ops.dvi->set_timings(in, &ddata->timings);

	r = in->ops.dvi->enable(in);
	अगर (r)
		वापस r;

	dssdev->state = OMAP_DSS_DISPLAY_ACTIVE;

	वापस 0;
पूर्ण

अटल व्योम dvic_disable(काष्ठा omap_dss_device *dssdev)
अणु
	काष्ठा panel_drv_data *ddata = to_panel_data(dssdev);
	काष्ठा omap_dss_device *in = ddata->in;

	अगर (!omapdss_device_is_enabled(dssdev))
		वापस;

	in->ops.dvi->disable(in);

	dssdev->state = OMAP_DSS_DISPLAY_DISABLED;
पूर्ण

अटल व्योम dvic_set_timings(काष्ठा omap_dss_device *dssdev,
		काष्ठा omap_video_timings *timings)
अणु
	काष्ठा panel_drv_data *ddata = to_panel_data(dssdev);
	काष्ठा omap_dss_device *in = ddata->in;

	ddata->timings = *timings;
	dssdev->panel.timings = *timings;

	in->ops.dvi->set_timings(in, timings);
पूर्ण

अटल व्योम dvic_get_timings(काष्ठा omap_dss_device *dssdev,
		काष्ठा omap_video_timings *timings)
अणु
	काष्ठा panel_drv_data *ddata = to_panel_data(dssdev);

	*timings = ddata->timings;
पूर्ण

अटल पूर्णांक dvic_check_timings(काष्ठा omap_dss_device *dssdev,
		काष्ठा omap_video_timings *timings)
अणु
	काष्ठा panel_drv_data *ddata = to_panel_data(dssdev);
	काष्ठा omap_dss_device *in = ddata->in;

	वापस in->ops.dvi->check_timings(in, timings);
पूर्ण

अटल पूर्णांक dvic_ddc_पढ़ो(काष्ठा i2c_adapter *adapter,
		अचिन्हित अक्षर *buf, u16 count, u8 offset)
अणु
	पूर्णांक r, retries;

	क्रम (retries = 3; retries > 0; retries--) अणु
		काष्ठा i2c_msg msgs[] = अणु
			अणु
				.addr   = DDC_ADDR,
				.flags  = 0,
				.len    = 1,
				.buf    = &offset,
			पूर्ण, अणु
				.addr   = DDC_ADDR,
				.flags  = I2C_M_RD,
				.len    = count,
				.buf    = buf,
			पूर्ण
		पूर्ण;

		r = i2c_transfer(adapter, msgs, 2);
		अगर (r == 2)
			वापस 0;

		अगर (r != -EAGAIN)
			अवरोध;
	पूर्ण

	वापस r < 0 ? r : -EIO;
पूर्ण

अटल पूर्णांक dvic_पढ़ो_edid(काष्ठा omap_dss_device *dssdev,
		u8 *edid, पूर्णांक len)
अणु
	काष्ठा panel_drv_data *ddata = to_panel_data(dssdev);
	पूर्णांक r, l, bytes_पढ़ो;

	अगर (!ddata->i2c_adapter)
		वापस -ENODEV;

	l = min(EDID_LENGTH, len);
	r = dvic_ddc_पढ़ो(ddata->i2c_adapter, edid, l, 0);
	अगर (r)
		वापस r;

	bytes_पढ़ो = l;

	/* अगर there are extensions, पढ़ो second block */
	अगर (len > EDID_LENGTH && edid[0x7e] > 0) अणु
		l = min(EDID_LENGTH, len - EDID_LENGTH);

		r = dvic_ddc_पढ़ो(ddata->i2c_adapter, edid + EDID_LENGTH,
				l, EDID_LENGTH);
		अगर (r)
			वापस r;

		bytes_पढ़ो += l;
	पूर्ण

	वापस bytes_पढ़ो;
पूर्ण

अटल bool dvic_detect(काष्ठा omap_dss_device *dssdev)
अणु
	काष्ठा panel_drv_data *ddata = to_panel_data(dssdev);
	अचिन्हित अक्षर out;
	पूर्णांक r;

	अगर (!ddata->i2c_adapter)
		वापस true;

	r = dvic_ddc_पढ़ो(ddata->i2c_adapter, &out, 1, 0);

	वापस r == 0;
पूर्ण

अटल काष्ठा omap_dss_driver dvic_driver = अणु
	.connect	= dvic_connect,
	.disconnect	= dvic_disconnect,

	.enable		= dvic_enable,
	.disable	= dvic_disable,

	.set_timings	= dvic_set_timings,
	.get_timings	= dvic_get_timings,
	.check_timings	= dvic_check_timings,

	.get_resolution	= omapdss_शेष_get_resolution,

	.पढ़ो_edid	= dvic_पढ़ो_edid,
	.detect		= dvic_detect,
पूर्ण;

अटल पूर्णांक dvic_probe_of(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा panel_drv_data *ddata = platक्रमm_get_drvdata(pdev);
	काष्ठा device_node *node = pdev->dev.of_node;
	काष्ठा omap_dss_device *in;
	काष्ठा device_node *adapter_node;
	काष्ठा i2c_adapter *adapter;

	in = omapdss_of_find_source_क्रम_first_ep(node);
	अगर (IS_ERR(in)) अणु
		dev_err(&pdev->dev, "failed to find video source\n");
		वापस PTR_ERR(in);
	पूर्ण

	ddata->in = in;

	adapter_node = of_parse_phandle(node, "ddc-i2c-bus", 0);
	अगर (adapter_node) अणु
		adapter = of_get_i2c_adapter_by_node(adapter_node);
		अगर (adapter == शून्य) अणु
			dev_err(&pdev->dev, "failed to parse ddc-i2c-bus\n");
			omap_dss_put_device(ddata->in);
			वापस -EPROBE_DEFER;
		पूर्ण

		ddata->i2c_adapter = adapter;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक dvic_probe(काष्ठा platक्रमm_device *pdev)
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

	r = dvic_probe_of(pdev);
	अगर (r)
		वापस r;

	ddata->timings = dvic_शेष_timings;

	dssdev = &ddata->dssdev;
	dssdev->driver = &dvic_driver;
	dssdev->dev = &pdev->dev;
	dssdev->type = OMAP_DISPLAY_TYPE_DVI;
	dssdev->owner = THIS_MODULE;
	dssdev->panel.timings = dvic_शेष_timings;

	r = omapdss_रेजिस्टर_display(dssdev);
	अगर (r) अणु
		dev_err(&pdev->dev, "Failed to register panel\n");
		जाओ err_reg;
	पूर्ण

	वापस 0;

err_reg:
	omap_dss_put_device(ddata->in);

	i2c_put_adapter(ddata->i2c_adapter);

	वापस r;
पूर्ण

अटल पूर्णांक __निकास dvic_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा panel_drv_data *ddata = platक्रमm_get_drvdata(pdev);
	काष्ठा omap_dss_device *dssdev = &ddata->dssdev;
	काष्ठा omap_dss_device *in = ddata->in;

	omapdss_unरेजिस्टर_display(&ddata->dssdev);

	dvic_disable(dssdev);
	dvic_disconnect(dssdev);

	omap_dss_put_device(in);

	i2c_put_adapter(ddata->i2c_adapter);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id dvic_of_match[] = अणु
	अणु .compatible = "omapdss,dvi-connector", पूर्ण,
	अणुपूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(of, dvic_of_match);

अटल काष्ठा platक्रमm_driver dvi_connector_driver = अणु
	.probe	= dvic_probe,
	.हटाओ	= __निकास_p(dvic_हटाओ),
	.driver	= अणु
		.name	= "connector-dvi",
		.of_match_table = dvic_of_match,
		.suppress_bind_attrs = true,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(dvi_connector_driver);

MODULE_AUTHOR("Tomi Valkeinen <tomi.valkeinen@ti.com>");
MODULE_DESCRIPTION("Generic DVI Connector driver");
MODULE_LICENSE("GPL");
