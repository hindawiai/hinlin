<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * LG.Philips LB035Q02 LCD Panel driver
 *
 * Copyright (C) 2013 Texas Instruments
 * Author: Tomi Valkeinen <tomi.valkeinen@ti.com>
 * Based on a driver by: Steve Sakoman <steve@sakoman.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/delay.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/mutex.h>
#समावेश <linux/gpपन.स>

#समावेश <video/omapfb_dss.h>

अटल स्थिर काष्ठा omap_video_timings lb035q02_timings = अणु
	.x_res = 320,
	.y_res = 240,

	.pixelघड़ी	= 6500000,

	.hsw		= 2,
	.hfp		= 20,
	.hbp		= 68,

	.vsw		= 2,
	.vfp		= 4,
	.vbp		= 18,

	.vsync_level	= OMAPDSS_SIG_ACTIVE_LOW,
	.hsync_level	= OMAPDSS_SIG_ACTIVE_LOW,
	.data_pclk_edge	= OMAPDSS_DRIVE_SIG_RISING_EDGE,
	.de_level	= OMAPDSS_SIG_ACTIVE_HIGH,
	.sync_pclk_edge	= OMAPDSS_DRIVE_SIG_FALLING_EDGE,
पूर्ण;

काष्ठा panel_drv_data अणु
	काष्ठा omap_dss_device dssdev;
	काष्ठा omap_dss_device *in;

	काष्ठा spi_device *spi;

	पूर्णांक data_lines;

	काष्ठा omap_video_timings videomode;

	/* used क्रम non-DT boot, to be हटाओd */
	पूर्णांक backlight_gpio;

	काष्ठा gpio_desc *enable_gpio;
पूर्ण;

#घोषणा to_panel_data(p) container_of(p, काष्ठा panel_drv_data, dssdev)

अटल पूर्णांक lb035q02_ग_लिखो_reg(काष्ठा spi_device *spi, u8 reg, u16 val)
अणु
	काष्ठा spi_message msg;
	काष्ठा spi_transfer index_xfer = अणु
		.len		= 3,
		.cs_change	= 1,
	पूर्ण;
	काष्ठा spi_transfer value_xfer = अणु
		.len		= 3,
	पूर्ण;
	u8	buffer[16];

	spi_message_init(&msg);

	/* रेजिस्टर index */
	buffer[0] = 0x70;
	buffer[1] = 0x00;
	buffer[2] = reg & 0x7f;
	index_xfer.tx_buf = buffer;
	spi_message_add_tail(&index_xfer, &msg);

	/* रेजिस्टर value */
	buffer[4] = 0x72;
	buffer[5] = val >> 8;
	buffer[6] = val;
	value_xfer.tx_buf = buffer + 4;
	spi_message_add_tail(&value_xfer, &msg);

	वापस spi_sync(spi, &msg);
पूर्ण

अटल व्योम init_lb035q02_panel(काष्ठा spi_device *spi)
अणु
	/* Init sequence from page 28 of the lb035q02 spec */
	lb035q02_ग_लिखो_reg(spi, 0x01, 0x6300);
	lb035q02_ग_लिखो_reg(spi, 0x02, 0x0200);
	lb035q02_ग_लिखो_reg(spi, 0x03, 0x0177);
	lb035q02_ग_लिखो_reg(spi, 0x04, 0x04c7);
	lb035q02_ग_लिखो_reg(spi, 0x05, 0xffc0);
	lb035q02_ग_लिखो_reg(spi, 0x06, 0xe806);
	lb035q02_ग_लिखो_reg(spi, 0x0a, 0x4008);
	lb035q02_ग_लिखो_reg(spi, 0x0b, 0x0000);
	lb035q02_ग_लिखो_reg(spi, 0x0d, 0x0030);
	lb035q02_ग_लिखो_reg(spi, 0x0e, 0x2800);
	lb035q02_ग_लिखो_reg(spi, 0x0f, 0x0000);
	lb035q02_ग_लिखो_reg(spi, 0x16, 0x9f80);
	lb035q02_ग_लिखो_reg(spi, 0x17, 0x0a0f);
	lb035q02_ग_लिखो_reg(spi, 0x1e, 0x00c1);
	lb035q02_ग_लिखो_reg(spi, 0x30, 0x0300);
	lb035q02_ग_लिखो_reg(spi, 0x31, 0x0007);
	lb035q02_ग_लिखो_reg(spi, 0x32, 0x0000);
	lb035q02_ग_लिखो_reg(spi, 0x33, 0x0000);
	lb035q02_ग_लिखो_reg(spi, 0x34, 0x0707);
	lb035q02_ग_लिखो_reg(spi, 0x35, 0x0004);
	lb035q02_ग_लिखो_reg(spi, 0x36, 0x0302);
	lb035q02_ग_लिखो_reg(spi, 0x37, 0x0202);
	lb035q02_ग_लिखो_reg(spi, 0x3a, 0x0a0d);
	lb035q02_ग_लिखो_reg(spi, 0x3b, 0x0806);
पूर्ण

अटल पूर्णांक lb035q02_connect(काष्ठा omap_dss_device *dssdev)
अणु
	काष्ठा panel_drv_data *ddata = to_panel_data(dssdev);
	काष्ठा omap_dss_device *in = ddata->in;
	पूर्णांक r;

	अगर (omapdss_device_is_connected(dssdev))
		वापस 0;

	r = in->ops.dpi->connect(in, dssdev);
	अगर (r)
		वापस r;

	init_lb035q02_panel(ddata->spi);

	वापस 0;
पूर्ण

अटल व्योम lb035q02_disconnect(काष्ठा omap_dss_device *dssdev)
अणु
	काष्ठा panel_drv_data *ddata = to_panel_data(dssdev);
	काष्ठा omap_dss_device *in = ddata->in;

	अगर (!omapdss_device_is_connected(dssdev))
		वापस;

	in->ops.dpi->disconnect(in, dssdev);
पूर्ण

अटल पूर्णांक lb035q02_enable(काष्ठा omap_dss_device *dssdev)
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

	अगर (ddata->enable_gpio)
		gpiod_set_value_cansleep(ddata->enable_gpio, 1);

	अगर (gpio_is_valid(ddata->backlight_gpio))
		gpio_set_value_cansleep(ddata->backlight_gpio, 1);

	dssdev->state = OMAP_DSS_DISPLAY_ACTIVE;

	वापस 0;
पूर्ण

अटल व्योम lb035q02_disable(काष्ठा omap_dss_device *dssdev)
अणु
	काष्ठा panel_drv_data *ddata = to_panel_data(dssdev);
	काष्ठा omap_dss_device *in = ddata->in;

	अगर (!omapdss_device_is_enabled(dssdev))
		वापस;

	अगर (ddata->enable_gpio)
		gpiod_set_value_cansleep(ddata->enable_gpio, 0);

	अगर (gpio_is_valid(ddata->backlight_gpio))
		gpio_set_value_cansleep(ddata->backlight_gpio, 0);

	in->ops.dpi->disable(in);

	dssdev->state = OMAP_DSS_DISPLAY_DISABLED;
पूर्ण

अटल व्योम lb035q02_set_timings(काष्ठा omap_dss_device *dssdev,
		काष्ठा omap_video_timings *timings)
अणु
	काष्ठा panel_drv_data *ddata = to_panel_data(dssdev);
	काष्ठा omap_dss_device *in = ddata->in;

	ddata->videomode = *timings;
	dssdev->panel.timings = *timings;

	in->ops.dpi->set_timings(in, timings);
पूर्ण

अटल व्योम lb035q02_get_timings(काष्ठा omap_dss_device *dssdev,
		काष्ठा omap_video_timings *timings)
अणु
	काष्ठा panel_drv_data *ddata = to_panel_data(dssdev);

	*timings = ddata->videomode;
पूर्ण

अटल पूर्णांक lb035q02_check_timings(काष्ठा omap_dss_device *dssdev,
		काष्ठा omap_video_timings *timings)
अणु
	काष्ठा panel_drv_data *ddata = to_panel_data(dssdev);
	काष्ठा omap_dss_device *in = ddata->in;

	वापस in->ops.dpi->check_timings(in, timings);
पूर्ण

अटल काष्ठा omap_dss_driver lb035q02_ops = अणु
	.connect	= lb035q02_connect,
	.disconnect	= lb035q02_disconnect,

	.enable		= lb035q02_enable,
	.disable	= lb035q02_disable,

	.set_timings	= lb035q02_set_timings,
	.get_timings	= lb035q02_get_timings,
	.check_timings	= lb035q02_check_timings,

	.get_resolution	= omapdss_शेष_get_resolution,
पूर्ण;

अटल पूर्णांक lb035q02_probe_of(काष्ठा spi_device *spi)
अणु
	काष्ठा device_node *node = spi->dev.of_node;
	काष्ठा panel_drv_data *ddata = spi_get_drvdata(spi);
	काष्ठा omap_dss_device *in;
	काष्ठा gpio_desc *gpio;

	gpio = devm_gpiod_get(&spi->dev, "enable", GPIOD_OUT_LOW);
	अगर (IS_ERR(gpio)) अणु
		dev_err(&spi->dev, "failed to parse enable gpio\n");
		वापस PTR_ERR(gpio);
	पूर्ण

	ddata->enable_gpio = gpio;

	ddata->backlight_gpio = -ENOENT;

	in = omapdss_of_find_source_क्रम_first_ep(node);
	अगर (IS_ERR(in)) अणु
		dev_err(&spi->dev, "failed to find video source\n");
		वापस PTR_ERR(in);
	पूर्ण

	ddata->in = in;

	वापस 0;
पूर्ण

अटल पूर्णांक lb035q02_panel_spi_probe(काष्ठा spi_device *spi)
अणु
	काष्ठा panel_drv_data *ddata;
	काष्ठा omap_dss_device *dssdev;
	पूर्णांक r;

	अगर (!spi->dev.of_node)
		वापस -ENODEV;

	ddata = devm_kzalloc(&spi->dev, माप(*ddata), GFP_KERNEL);
	अगर (ddata == शून्य)
		वापस -ENOMEM;

	spi_set_drvdata(spi, ddata);

	ddata->spi = spi;

	r = lb035q02_probe_of(spi);
	अगर (r)
		वापस r;

	अगर (gpio_is_valid(ddata->backlight_gpio)) अणु
		r = devm_gpio_request_one(&spi->dev, ddata->backlight_gpio,
				GPIOF_OUT_INIT_LOW, "panel backlight");
		अगर (r)
			जाओ err_gpio;
	पूर्ण

	ddata->videomode = lb035q02_timings;

	dssdev = &ddata->dssdev;
	dssdev->dev = &spi->dev;
	dssdev->driver = &lb035q02_ops;
	dssdev->type = OMAP_DISPLAY_TYPE_DPI;
	dssdev->owner = THIS_MODULE;
	dssdev->panel.timings = ddata->videomode;
	dssdev->phy.dpi.data_lines = ddata->data_lines;

	r = omapdss_रेजिस्टर_display(dssdev);
	अगर (r) अणु
		dev_err(&spi->dev, "Failed to register panel\n");
		जाओ err_reg;
	पूर्ण

	वापस 0;

err_reg:
err_gpio:
	omap_dss_put_device(ddata->in);
	वापस r;
पूर्ण

अटल पूर्णांक lb035q02_panel_spi_हटाओ(काष्ठा spi_device *spi)
अणु
	काष्ठा panel_drv_data *ddata = spi_get_drvdata(spi);
	काष्ठा omap_dss_device *dssdev = &ddata->dssdev;
	काष्ठा omap_dss_device *in = ddata->in;

	omapdss_unरेजिस्टर_display(dssdev);

	lb035q02_disable(dssdev);
	lb035q02_disconnect(dssdev);

	omap_dss_put_device(in);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id lb035q02_of_match[] = अणु
	अणु .compatible = "omapdss,lgphilips,lb035q02", पूर्ण,
	अणुपूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(of, lb035q02_of_match);

अटल काष्ठा spi_driver lb035q02_spi_driver = अणु
	.probe		= lb035q02_panel_spi_probe,
	.हटाओ		= lb035q02_panel_spi_हटाओ,
	.driver		= अणु
		.name	= "panel_lgphilips_lb035q02",
		.of_match_table = lb035q02_of_match,
		.suppress_bind_attrs = true,
	पूर्ण,
पूर्ण;

module_spi_driver(lb035q02_spi_driver);

MODULE_ALIAS("spi:lgphilips,lb035q02");
MODULE_AUTHOR("Tomi Valkeinen <tomi.valkeinen@ti.com>");
MODULE_DESCRIPTION("LG.Philips LB035Q02 LCD Panel driver");
MODULE_LICENSE("GPL");
