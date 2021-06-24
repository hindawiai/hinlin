<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * NEC NL8048HL11 Panel driver
 *
 * Copyright (C) 2010 Texas Instruments Inc.
 * Author: Erik Gilling <konkers@android.com>
 * Converted to new DSS device model: Tomi Valkeinen <tomi.valkeinen@ti.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/delay.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/fb.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/of_gpपन.स>

#समावेश <video/omapfb_dss.h>

काष्ठा panel_drv_data अणु
	काष्ठा omap_dss_device	dssdev;
	काष्ठा omap_dss_device *in;

	काष्ठा omap_video_timings videomode;

	पूर्णांक data_lines;

	पूर्णांक res_gpio;
	पूर्णांक qvga_gpio;

	काष्ठा spi_device *spi;
पूर्ण;

#घोषणा LCD_XRES		800
#घोषणा LCD_YRES		480
/*
 * NEC PIX Clock Ratings
 * MIN:21.8MHz TYP:23.8MHz MAX:25.7MHz
 */
#घोषणा LCD_PIXEL_CLOCK		23800000

अटल स्थिर काष्ठा अणु
	अचिन्हित अक्षर addr;
	अचिन्हित अक्षर dat;
पूर्ण nec_8048_init_seq[] = अणु
	अणु 3, 0x01 पूर्ण, अणु 0, 0x00 पूर्ण, अणु 1, 0x01 पूर्ण, अणु 4, 0x00 पूर्ण, अणु 5, 0x14 पूर्ण,
	अणु 6, 0x24 पूर्ण, अणु 16, 0xD7 पूर्ण, अणु 17, 0x00 पूर्ण, अणु 18, 0x00 पूर्ण, अणु 19, 0x55 पूर्ण,
	अणु 20, 0x01 पूर्ण, अणु 21, 0x70 पूर्ण, अणु 22, 0x1E पूर्ण, अणु 23, 0x25 पूर्ण,	अणु 24, 0x25 पूर्ण,
	अणु 25, 0x02 पूर्ण, अणु 26, 0x02 पूर्ण, अणु 27, 0xA0 पूर्ण, अणु 32, 0x2F पूर्ण, अणु 33, 0x0F पूर्ण,
	अणु 34, 0x0F पूर्ण, अणु 35, 0x0F पूर्ण, अणु 36, 0x0F पूर्ण, अणु 37, 0x0F पूर्ण,	अणु 38, 0x0F पूर्ण,
	अणु 39, 0x00 पूर्ण, अणु 40, 0x02 पूर्ण, अणु 41, 0x02 पूर्ण, अणु 42, 0x02 पूर्ण,	अणु 43, 0x0F पूर्ण,
	अणु 44, 0x0F पूर्ण, अणु 45, 0x0F पूर्ण, अणु 46, 0x0F पूर्ण, अणु 47, 0x0F पूर्ण,	अणु 48, 0x0F पूर्ण,
	अणु 49, 0x0F पूर्ण, अणु 50, 0x00 पूर्ण, अणु 51, 0x02 पूर्ण, अणु 52, 0x02 पूर्ण, अणु 53, 0x02 पूर्ण,
	अणु 80, 0x0C पूर्ण, अणु 83, 0x42 पूर्ण, अणु 84, 0x42 पूर्ण, अणु 85, 0x41 पूर्ण,	अणु 86, 0x14 पूर्ण,
	अणु 89, 0x88 पूर्ण, अणु 90, 0x01 पूर्ण, अणु 91, 0x00 पूर्ण, अणु 92, 0x02 पूर्ण,	अणु 93, 0x0C पूर्ण,
	अणु 94, 0x1C पूर्ण, अणु 95, 0x27 पूर्ण, अणु 98, 0x49 पूर्ण, अणु 99, 0x27 पूर्ण, अणु 102, 0x76 पूर्ण,
	अणु 103, 0x27 पूर्ण, अणु 112, 0x01 पूर्ण, अणु 113, 0x0E पूर्ण, अणु 114, 0x02 पूर्ण,
	अणु 115, 0x0C पूर्ण, अणु 118, 0x0C पूर्ण, अणु 121, 0x30 पूर्ण, अणु 130, 0x00 पूर्ण,
	अणु 131, 0x00 पूर्ण, अणु 132, 0xFC पूर्ण, अणु 134, 0x00 पूर्ण, अणु 136, 0x00 पूर्ण,
	अणु 138, 0x00 पूर्ण, अणु 139, 0x00 पूर्ण, अणु 140, 0x00 पूर्ण, अणु 141, 0xFC पूर्ण,
	अणु 143, 0x00 पूर्ण, अणु 145, 0x00 पूर्ण, अणु 147, 0x00 पूर्ण, अणु 148, 0x00 पूर्ण,
	अणु 149, 0x00 पूर्ण, अणु 150, 0xFC पूर्ण, अणु 152, 0x00 पूर्ण, अणु 154, 0x00 पूर्ण,
	अणु 156, 0x00 पूर्ण, अणु 157, 0x00 पूर्ण, अणु 2, 0x00 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा omap_video_timings nec_8048_panel_timings = अणु
	.x_res		= LCD_XRES,
	.y_res		= LCD_YRES,
	.pixelघड़ी	= LCD_PIXEL_CLOCK,
	.hfp		= 6,
	.hsw		= 1,
	.hbp		= 4,
	.vfp		= 3,
	.vsw		= 1,
	.vbp		= 4,

	.vsync_level	= OMAPDSS_SIG_ACTIVE_LOW,
	.hsync_level	= OMAPDSS_SIG_ACTIVE_LOW,
	.data_pclk_edge	= OMAPDSS_DRIVE_SIG_RISING_EDGE,
	.de_level	= OMAPDSS_SIG_ACTIVE_HIGH,
	.sync_pclk_edge	= OMAPDSS_DRIVE_SIG_RISING_EDGE,
पूर्ण;

#घोषणा to_panel_data(p) container_of(p, काष्ठा panel_drv_data, dssdev)

अटल पूर्णांक nec_8048_spi_send(काष्ठा spi_device *spi, अचिन्हित अक्षर reg_addr,
			अचिन्हित अक्षर reg_data)
अणु
	पूर्णांक ret = 0;
	अचिन्हित पूर्णांक cmd = 0, data = 0;

	cmd = 0x0000 | reg_addr; /* रेजिस्टर address ग_लिखो */
	data = 0x0100 | reg_data; /* रेजिस्टर data ग_लिखो */
	data = (cmd << 16) | data;

	ret = spi_ग_लिखो(spi, (अचिन्हित अक्षर *)&data, 4);
	अगर (ret)
		pr_err("error in spi_write %x\n", data);

	वापस ret;
पूर्ण

अटल पूर्णांक init_nec_8048_wvga_lcd(काष्ठा spi_device *spi)
अणु
	अचिन्हित पूर्णांक i;
	/* Initialization Sequence */
	/* nec_8048_spi_send(spi, REG, VAL) */
	क्रम (i = 0; i < (ARRAY_SIZE(nec_8048_init_seq) - 1); i++)
		nec_8048_spi_send(spi, nec_8048_init_seq[i].addr,
				nec_8048_init_seq[i].dat);
	udelay(20);
	nec_8048_spi_send(spi, nec_8048_init_seq[i].addr,
				nec_8048_init_seq[i].dat);
	वापस 0;
पूर्ण

अटल पूर्णांक nec_8048_connect(काष्ठा omap_dss_device *dssdev)
अणु
	काष्ठा panel_drv_data *ddata = to_panel_data(dssdev);
	काष्ठा omap_dss_device *in = ddata->in;
	पूर्णांक r;

	अगर (omapdss_device_is_connected(dssdev))
		वापस 0;

	r = in->ops.dpi->connect(in, dssdev);
	अगर (r)
		वापस r;

	वापस 0;
पूर्ण

अटल व्योम nec_8048_disconnect(काष्ठा omap_dss_device *dssdev)
अणु
	काष्ठा panel_drv_data *ddata = to_panel_data(dssdev);
	काष्ठा omap_dss_device *in = ddata->in;

	अगर (!omapdss_device_is_connected(dssdev))
		वापस;

	in->ops.dpi->disconnect(in, dssdev);
पूर्ण

अटल पूर्णांक nec_8048_enable(काष्ठा omap_dss_device *dssdev)
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

	अगर (gpio_is_valid(ddata->res_gpio))
		gpio_set_value_cansleep(ddata->res_gpio, 1);

	dssdev->state = OMAP_DSS_DISPLAY_ACTIVE;

	वापस 0;
पूर्ण

अटल व्योम nec_8048_disable(काष्ठा omap_dss_device *dssdev)
अणु
	काष्ठा panel_drv_data *ddata = to_panel_data(dssdev);
	काष्ठा omap_dss_device *in = ddata->in;

	अगर (!omapdss_device_is_enabled(dssdev))
		वापस;

	अगर (gpio_is_valid(ddata->res_gpio))
		gpio_set_value_cansleep(ddata->res_gpio, 0);

	in->ops.dpi->disable(in);

	dssdev->state = OMAP_DSS_DISPLAY_DISABLED;
पूर्ण

अटल व्योम nec_8048_set_timings(काष्ठा omap_dss_device *dssdev,
		काष्ठा omap_video_timings *timings)
अणु
	काष्ठा panel_drv_data *ddata = to_panel_data(dssdev);
	काष्ठा omap_dss_device *in = ddata->in;

	ddata->videomode = *timings;
	dssdev->panel.timings = *timings;

	in->ops.dpi->set_timings(in, timings);
पूर्ण

अटल व्योम nec_8048_get_timings(काष्ठा omap_dss_device *dssdev,
		काष्ठा omap_video_timings *timings)
अणु
	काष्ठा panel_drv_data *ddata = to_panel_data(dssdev);

	*timings = ddata->videomode;
पूर्ण

अटल पूर्णांक nec_8048_check_timings(काष्ठा omap_dss_device *dssdev,
		काष्ठा omap_video_timings *timings)
अणु
	काष्ठा panel_drv_data *ddata = to_panel_data(dssdev);
	काष्ठा omap_dss_device *in = ddata->in;

	वापस in->ops.dpi->check_timings(in, timings);
पूर्ण

अटल काष्ठा omap_dss_driver nec_8048_ops = अणु
	.connect	= nec_8048_connect,
	.disconnect	= nec_8048_disconnect,

	.enable		= nec_8048_enable,
	.disable	= nec_8048_disable,

	.set_timings	= nec_8048_set_timings,
	.get_timings	= nec_8048_get_timings,
	.check_timings	= nec_8048_check_timings,

	.get_resolution	= omapdss_शेष_get_resolution,
पूर्ण;


अटल पूर्णांक nec_8048_probe_of(काष्ठा spi_device *spi)
अणु
	काष्ठा device_node *node = spi->dev.of_node;
	काष्ठा panel_drv_data *ddata = dev_get_drvdata(&spi->dev);
	काष्ठा omap_dss_device *in;
	पूर्णांक gpio;

	gpio = of_get_named_gpio(node, "reset-gpios", 0);
	अगर (!gpio_is_valid(gpio)) अणु
		dev_err(&spi->dev, "failed to parse enable gpio\n");
		वापस gpio;
	पूर्ण
	ddata->res_gpio = gpio;

	/* XXX the panel spec करोesn't mention any QVGA pin?? */
	ddata->qvga_gpio = -ENOENT;

	in = omapdss_of_find_source_क्रम_first_ep(node);
	अगर (IS_ERR(in)) अणु
		dev_err(&spi->dev, "failed to find video source\n");
		वापस PTR_ERR(in);
	पूर्ण

	ddata->in = in;

	वापस 0;
पूर्ण

अटल पूर्णांक nec_8048_probe(काष्ठा spi_device *spi)
अणु
	काष्ठा panel_drv_data *ddata;
	काष्ठा omap_dss_device *dssdev;
	पूर्णांक r;

	dev_dbg(&spi->dev, "%s\n", __func__);

	अगर (!spi->dev.of_node)
		वापस -ENODEV;

	spi->mode = SPI_MODE_0;
	spi->bits_per_word = 32;

	r = spi_setup(spi);
	अगर (r < 0) अणु
		dev_err(&spi->dev, "spi_setup failed: %d\n", r);
		वापस r;
	पूर्ण

	init_nec_8048_wvga_lcd(spi);

	ddata = devm_kzalloc(&spi->dev, माप(*ddata), GFP_KERNEL);
	अगर (ddata == शून्य)
		वापस -ENOMEM;

	dev_set_drvdata(&spi->dev, ddata);

	ddata->spi = spi;

	r = nec_8048_probe_of(spi);
	अगर (r)
		वापस r;

	अगर (gpio_is_valid(ddata->qvga_gpio)) अणु
		r = devm_gpio_request_one(&spi->dev, ddata->qvga_gpio,
				GPIOF_OUT_INIT_HIGH, "lcd QVGA");
		अगर (r)
			जाओ err_gpio;
	पूर्ण

	अगर (gpio_is_valid(ddata->res_gpio)) अणु
		r = devm_gpio_request_one(&spi->dev, ddata->res_gpio,
				GPIOF_OUT_INIT_LOW, "lcd RES");
		अगर (r)
			जाओ err_gpio;
	पूर्ण

	ddata->videomode = nec_8048_panel_timings;

	dssdev = &ddata->dssdev;
	dssdev->dev = &spi->dev;
	dssdev->driver = &nec_8048_ops;
	dssdev->type = OMAP_DISPLAY_TYPE_DPI;
	dssdev->owner = THIS_MODULE;
	dssdev->panel.timings = ddata->videomode;

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

अटल पूर्णांक nec_8048_हटाओ(काष्ठा spi_device *spi)
अणु
	काष्ठा panel_drv_data *ddata = dev_get_drvdata(&spi->dev);
	काष्ठा omap_dss_device *dssdev = &ddata->dssdev;
	काष्ठा omap_dss_device *in = ddata->in;

	dev_dbg(&ddata->spi->dev, "%s\n", __func__);

	omapdss_unरेजिस्टर_display(dssdev);

	nec_8048_disable(dssdev);
	nec_8048_disconnect(dssdev);

	omap_dss_put_device(in);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक nec_8048_suspend(काष्ठा device *dev)
अणु
	काष्ठा spi_device *spi = to_spi_device(dev);

	nec_8048_spi_send(spi, 2, 0x01);
	mdelay(40);

	वापस 0;
पूर्ण

अटल पूर्णांक nec_8048_resume(काष्ठा device *dev)
अणु
	काष्ठा spi_device *spi = to_spi_device(dev);

	/* reinitialize the panel */
	spi_setup(spi);
	nec_8048_spi_send(spi, 2, 0x00);
	init_nec_8048_wvga_lcd(spi);

	वापस 0;
पूर्ण
अटल SIMPLE_DEV_PM_OPS(nec_8048_pm_ops, nec_8048_suspend,
		nec_8048_resume);
#घोषणा NEC_8048_PM_OPS (&nec_8048_pm_ops)
#अन्यथा
#घोषणा NEC_8048_PM_OPS शून्य
#पूर्ण_अगर

अटल स्थिर काष्ठा of_device_id nec_8048_of_match[] = अणु
	अणु .compatible = "omapdss,nec,nl8048hl11", पूर्ण,
	अणुपूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(of, nec_8048_of_match);

अटल काष्ठा spi_driver nec_8048_driver = अणु
	.driver = अणु
		.name	= "panel-nec-nl8048hl11",
		.pm	= NEC_8048_PM_OPS,
		.of_match_table = nec_8048_of_match,
		.suppress_bind_attrs = true,
	पूर्ण,
	.probe	= nec_8048_probe,
	.हटाओ	= nec_8048_हटाओ,
पूर्ण;

module_spi_driver(nec_8048_driver);

MODULE_ALIAS("spi:nec,nl8048hl11");
MODULE_AUTHOR("Erik Gilling <konkers@android.com>");
MODULE_DESCRIPTION("NEC-NL8048HL11 Driver");
MODULE_LICENSE("GPL");
