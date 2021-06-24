<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * TPO TD043MTEA1 Panel driver
 *
 * Author: Graधठvydas Ignotas <notasas@gmail.com>
 * Converted to new DSS device model: Tomi Valkeinen <tomi.valkeinen@ti.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/delay.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/err.h>
#समावेश <linux/slab.h>
#समावेश <linux/of_gpपन.स>

#समावेश <video/omapfb_dss.h>

#घोषणा TPO_R02_MODE(x)		((x) & 7)
#घोषणा TPO_R02_MODE_800x480	7
#घोषणा TPO_R02_NCLK_RISING	BIT(3)
#घोषणा TPO_R02_HSYNC_HIGH	BIT(4)
#घोषणा TPO_R02_VSYNC_HIGH	BIT(5)

#घोषणा TPO_R03_NSTANDBY	BIT(0)
#घोषणा TPO_R03_EN_CP_CLK	BIT(1)
#घोषणा TPO_R03_EN_VGL_PUMP	BIT(2)
#घोषणा TPO_R03_EN_PWM		BIT(3)
#घोषणा TPO_R03_DRIVING_CAP_100	BIT(4)
#घोषणा TPO_R03_EN_PRE_CHARGE	BIT(6)
#घोषणा TPO_R03_SOFTWARE_CTL	BIT(7)

#घोषणा TPO_R04_NFLIP_H		BIT(0)
#घोषणा TPO_R04_NFLIP_V		BIT(1)
#घोषणा TPO_R04_CP_CLK_FREQ_1H	BIT(2)
#घोषणा TPO_R04_VGL_FREQ_1H	BIT(4)

#घोषणा TPO_R03_VAL_NORMAL (TPO_R03_NSTANDBY | TPO_R03_EN_CP_CLK | \
			TPO_R03_EN_VGL_PUMP |  TPO_R03_EN_PWM | \
			TPO_R03_DRIVING_CAP_100 | TPO_R03_EN_PRE_CHARGE | \
			TPO_R03_SOFTWARE_CTL)

#घोषणा TPO_R03_VAL_STANDBY (TPO_R03_DRIVING_CAP_100 | \
			TPO_R03_EN_PRE_CHARGE | TPO_R03_SOFTWARE_CTL)

अटल स्थिर u16 tpo_td043_def_gamma[12] = अणु
	105, 315, 381, 431, 490, 537, 579, 686, 780, 837, 880, 1023
पूर्ण;

काष्ठा panel_drv_data अणु
	काष्ठा omap_dss_device	dssdev;
	काष्ठा omap_dss_device *in;

	काष्ठा omap_video_timings videomode;

	पूर्णांक data_lines;

	काष्ठा spi_device *spi;
	काष्ठा regulator *vcc_reg;
	पूर्णांक nreset_gpio;
	u16 gamma[12];
	u32 mode;
	u32 hmirror:1;
	u32 vmirror:1;
	u32 घातered_on:1;
	u32 spi_suspended:1;
	u32 घातer_on_resume:1;
पूर्ण;

अटल स्थिर काष्ठा omap_video_timings tpo_td043_timings = अणु
	.x_res		= 800,
	.y_res		= 480,

	.pixelघड़ी	= 36000000,

	.hsw		= 1,
	.hfp		= 68,
	.hbp		= 214,

	.vsw		= 1,
	.vfp		= 39,
	.vbp		= 34,

	.vsync_level	= OMAPDSS_SIG_ACTIVE_LOW,
	.hsync_level	= OMAPDSS_SIG_ACTIVE_LOW,
	.data_pclk_edge	= OMAPDSS_DRIVE_SIG_FALLING_EDGE,
	.de_level	= OMAPDSS_SIG_ACTIVE_HIGH,
	.sync_pclk_edge	= OMAPDSS_DRIVE_SIG_RISING_EDGE,
पूर्ण;

#घोषणा to_panel_data(p) container_of(p, काष्ठा panel_drv_data, dssdev)

अटल पूर्णांक tpo_td043_ग_लिखो(काष्ठा spi_device *spi, u8 addr, u8 data)
अणु
	काष्ठा spi_message	m;
	काष्ठा spi_transfer	xfer;
	u16			w;
	पूर्णांक			r;

	spi_message_init(&m);

	स_रखो(&xfer, 0, माप(xfer));

	w = ((u16)addr << 10) | (1 << 8) | data;
	xfer.tx_buf = &w;
	xfer.bits_per_word = 16;
	xfer.len = 2;
	spi_message_add_tail(&xfer, &m);

	r = spi_sync(spi, &m);
	अगर (r < 0)
		dev_warn(&spi->dev, "failed to write to LCD reg (%d)\n", r);
	वापस r;
पूर्ण

अटल व्योम tpo_td043_ग_लिखो_gamma(काष्ठा spi_device *spi, u16 gamma[12])
अणु
	u8 i, val;

	/* gamma bits [9:8] */
	क्रम (val = i = 0; i < 4; i++)
		val |= (gamma[i] & 0x300) >> ((i + 1) * 2);
	tpo_td043_ग_लिखो(spi, 0x11, val);

	क्रम (val = i = 0; i < 4; i++)
		val |= (gamma[i+4] & 0x300) >> ((i + 1) * 2);
	tpo_td043_ग_लिखो(spi, 0x12, val);

	क्रम (val = i = 0; i < 4; i++)
		val |= (gamma[i+8] & 0x300) >> ((i + 1) * 2);
	tpo_td043_ग_लिखो(spi, 0x13, val);

	/* gamma bits [7:0] */
	क्रम (val = i = 0; i < 12; i++)
		tpo_td043_ग_लिखो(spi, 0x14 + i, gamma[i] & 0xff);
पूर्ण

अटल पूर्णांक tpo_td043_ग_लिखो_mirror(काष्ठा spi_device *spi, bool h, bool v)
अणु
	u8 reg4 = TPO_R04_NFLIP_H | TPO_R04_NFLIP_V |
		TPO_R04_CP_CLK_FREQ_1H | TPO_R04_VGL_FREQ_1H;
	अगर (h)
		reg4 &= ~TPO_R04_NFLIP_H;
	अगर (v)
		reg4 &= ~TPO_R04_NFLIP_V;

	वापस tpo_td043_ग_लिखो(spi, 4, reg4);
पूर्ण

अटल पूर्णांक tpo_td043_set_hmirror(काष्ठा omap_dss_device *dssdev, bool enable)
अणु
	काष्ठा panel_drv_data *ddata = dev_get_drvdata(dssdev->dev);

	ddata->hmirror = enable;
	वापस tpo_td043_ग_लिखो_mirror(ddata->spi, ddata->hmirror,
			ddata->vmirror);
पूर्ण

अटल bool tpo_td043_get_hmirror(काष्ठा omap_dss_device *dssdev)
अणु
	काष्ठा panel_drv_data *ddata = dev_get_drvdata(dssdev->dev);

	वापस ddata->hmirror;
पूर्ण

अटल sमाप_प्रकार tpo_td043_vmirror_show(काष्ठा device *dev,
	काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा panel_drv_data *ddata = dev_get_drvdata(dev);

	वापस snम_लिखो(buf, PAGE_SIZE, "%d\n", ddata->vmirror);
पूर्ण

अटल sमाप_प्रकार tpo_td043_vmirror_store(काष्ठा device *dev,
	काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा panel_drv_data *ddata = dev_get_drvdata(dev);
	पूर्णांक val;
	पूर्णांक ret;

	ret = kstrtoपूर्णांक(buf, 0, &val);
	अगर (ret < 0)
		वापस ret;

	val = !!val;

	ret = tpo_td043_ग_लिखो_mirror(ddata->spi, ddata->hmirror, val);
	अगर (ret < 0)
		वापस ret;

	ddata->vmirror = val;

	वापस count;
पूर्ण

अटल sमाप_प्रकार tpo_td043_mode_show(काष्ठा device *dev,
	काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा panel_drv_data *ddata = dev_get_drvdata(dev);

	वापस snम_लिखो(buf, PAGE_SIZE, "%d\n", ddata->mode);
पूर्ण

अटल sमाप_प्रकार tpo_td043_mode_store(काष्ठा device *dev,
	काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा panel_drv_data *ddata = dev_get_drvdata(dev);
	दीर्घ val;
	पूर्णांक ret;

	ret = kम_से_दीर्घ(buf, 0, &val);
	अगर (ret != 0 || val & ~7)
		वापस -EINVAL;

	ddata->mode = val;

	val |= TPO_R02_NCLK_RISING;
	tpo_td043_ग_लिखो(ddata->spi, 2, val);

	वापस count;
पूर्ण

अटल sमाप_प्रकार tpo_td043_gamma_show(काष्ठा device *dev,
	काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा panel_drv_data *ddata = dev_get_drvdata(dev);
	sमाप_प्रकार len = 0;
	पूर्णांक ret;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(ddata->gamma); i++) अणु
		ret = snम_लिखो(buf + len, PAGE_SIZE - len, "%u ",
				ddata->gamma[i]);
		अगर (ret < 0)
			वापस ret;
		len += ret;
	पूर्ण
	buf[len - 1] = '\n';

	वापस len;
पूर्ण

अटल sमाप_प्रकार tpo_td043_gamma_store(काष्ठा device *dev,
	काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा panel_drv_data *ddata = dev_get_drvdata(dev);
	अचिन्हित पूर्णांक g[12];
	पूर्णांक ret;
	पूर्णांक i;

	ret = माला_पूछो(buf, "%u %u %u %u %u %u %u %u %u %u %u %u",
			&g[0], &g[1], &g[2], &g[3], &g[4], &g[5],
			&g[6], &g[7], &g[8], &g[9], &g[10], &g[11]);

	अगर (ret != 12)
		वापस -EINVAL;

	क्रम (i = 0; i < 12; i++)
		ddata->gamma[i] = g[i];

	tpo_td043_ग_लिखो_gamma(ddata->spi, ddata->gamma);

	वापस count;
पूर्ण

अटल DEVICE_ATTR(vmirror, S_IRUGO | S_IWUSR,
		tpo_td043_vmirror_show, tpo_td043_vmirror_store);
अटल DEVICE_ATTR(mode, S_IRUGO | S_IWUSR,
		tpo_td043_mode_show, tpo_td043_mode_store);
अटल DEVICE_ATTR(gamma, S_IRUGO | S_IWUSR,
		tpo_td043_gamma_show, tpo_td043_gamma_store);

अटल काष्ठा attribute *tpo_td043_attrs[] = अणु
	&dev_attr_vmirror.attr,
	&dev_attr_mode.attr,
	&dev_attr_gamma.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group tpo_td043_attr_group = अणु
	.attrs = tpo_td043_attrs,
पूर्ण;

अटल पूर्णांक tpo_td043_घातer_on(काष्ठा panel_drv_data *ddata)
अणु
	पूर्णांक r;

	अगर (ddata->घातered_on)
		वापस 0;

	r = regulator_enable(ddata->vcc_reg);
	अगर (r != 0)
		वापस r;

	/* रुको क्रम panel to stabilize */
	msleep(160);

	अगर (gpio_is_valid(ddata->nreset_gpio))
		gpio_set_value(ddata->nreset_gpio, 1);

	tpo_td043_ग_लिखो(ddata->spi, 2,
			TPO_R02_MODE(ddata->mode) | TPO_R02_NCLK_RISING);
	tpo_td043_ग_लिखो(ddata->spi, 3, TPO_R03_VAL_NORMAL);
	tpo_td043_ग_लिखो(ddata->spi, 0x20, 0xf0);
	tpo_td043_ग_लिखो(ddata->spi, 0x21, 0xf0);
	tpo_td043_ग_लिखो_mirror(ddata->spi, ddata->hmirror,
			ddata->vmirror);
	tpo_td043_ग_लिखो_gamma(ddata->spi, ddata->gamma);

	ddata->घातered_on = 1;
	वापस 0;
पूर्ण

अटल व्योम tpo_td043_घातer_off(काष्ठा panel_drv_data *ddata)
अणु
	अगर (!ddata->घातered_on)
		वापस;

	tpo_td043_ग_लिखो(ddata->spi, 3,
			TPO_R03_VAL_STANDBY | TPO_R03_EN_PWM);

	अगर (gpio_is_valid(ddata->nreset_gpio))
		gpio_set_value(ddata->nreset_gpio, 0);

	/* रुको क्रम at least 2 vsyncs beक्रमe cutting off घातer */
	msleep(50);

	tpo_td043_ग_लिखो(ddata->spi, 3, TPO_R03_VAL_STANDBY);

	regulator_disable(ddata->vcc_reg);

	ddata->घातered_on = 0;
पूर्ण

अटल पूर्णांक tpo_td043_connect(काष्ठा omap_dss_device *dssdev)
अणु
	काष्ठा panel_drv_data *ddata = to_panel_data(dssdev);
	काष्ठा omap_dss_device *in = ddata->in;

	अगर (omapdss_device_is_connected(dssdev))
		वापस 0;

	वापस in->ops.dpi->connect(in, dssdev);
पूर्ण

अटल व्योम tpo_td043_disconnect(काष्ठा omap_dss_device *dssdev)
अणु
	काष्ठा panel_drv_data *ddata = to_panel_data(dssdev);
	काष्ठा omap_dss_device *in = ddata->in;

	अगर (!omapdss_device_is_connected(dssdev))
		वापस;

	in->ops.dpi->disconnect(in, dssdev);
पूर्ण

अटल पूर्णांक tpo_td043_enable(काष्ठा omap_dss_device *dssdev)
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

	/*
	 * If we are resuming from प्रणाली suspend, SPI घड़ीs might not be
	 * enabled yet, so we'll program the LCD from SPI PM resume callback.
	 */
	अगर (!ddata->spi_suspended) अणु
		r = tpo_td043_घातer_on(ddata);
		अगर (r) अणु
			in->ops.dpi->disable(in);
			वापस r;
		पूर्ण
	पूर्ण

	dssdev->state = OMAP_DSS_DISPLAY_ACTIVE;

	वापस 0;
पूर्ण

अटल व्योम tpo_td043_disable(काष्ठा omap_dss_device *dssdev)
अणु
	काष्ठा panel_drv_data *ddata = to_panel_data(dssdev);
	काष्ठा omap_dss_device *in = ddata->in;

	अगर (!omapdss_device_is_enabled(dssdev))
		वापस;

	in->ops.dpi->disable(in);

	अगर (!ddata->spi_suspended)
		tpo_td043_घातer_off(ddata);

	dssdev->state = OMAP_DSS_DISPLAY_DISABLED;
पूर्ण

अटल व्योम tpo_td043_set_timings(काष्ठा omap_dss_device *dssdev,
		काष्ठा omap_video_timings *timings)
अणु
	काष्ठा panel_drv_data *ddata = to_panel_data(dssdev);
	काष्ठा omap_dss_device *in = ddata->in;

	ddata->videomode = *timings;
	dssdev->panel.timings = *timings;

	in->ops.dpi->set_timings(in, timings);
पूर्ण

अटल व्योम tpo_td043_get_timings(काष्ठा omap_dss_device *dssdev,
		काष्ठा omap_video_timings *timings)
अणु
	काष्ठा panel_drv_data *ddata = to_panel_data(dssdev);

	*timings = ddata->videomode;
पूर्ण

अटल पूर्णांक tpo_td043_check_timings(काष्ठा omap_dss_device *dssdev,
		काष्ठा omap_video_timings *timings)
अणु
	काष्ठा panel_drv_data *ddata = to_panel_data(dssdev);
	काष्ठा omap_dss_device *in = ddata->in;

	वापस in->ops.dpi->check_timings(in, timings);
पूर्ण

अटल काष्ठा omap_dss_driver tpo_td043_ops = अणु
	.connect	= tpo_td043_connect,
	.disconnect	= tpo_td043_disconnect,

	.enable		= tpo_td043_enable,
	.disable	= tpo_td043_disable,

	.set_timings	= tpo_td043_set_timings,
	.get_timings	= tpo_td043_get_timings,
	.check_timings	= tpo_td043_check_timings,

	.set_mirror	= tpo_td043_set_hmirror,
	.get_mirror	= tpo_td043_get_hmirror,

	.get_resolution	= omapdss_शेष_get_resolution,
पूर्ण;


अटल पूर्णांक tpo_td043_probe_of(काष्ठा spi_device *spi)
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
	ddata->nreset_gpio = gpio;

	in = omapdss_of_find_source_क्रम_first_ep(node);
	अगर (IS_ERR(in)) अणु
		dev_err(&spi->dev, "failed to find video source\n");
		वापस PTR_ERR(in);
	पूर्ण

	ddata->in = in;

	वापस 0;
पूर्ण

अटल पूर्णांक tpo_td043_probe(काष्ठा spi_device *spi)
अणु
	काष्ठा panel_drv_data *ddata;
	काष्ठा omap_dss_device *dssdev;
	पूर्णांक r;

	dev_dbg(&spi->dev, "%s\n", __func__);

	अगर (!spi->dev.of_node)
		वापस -ENODEV;

	spi->bits_per_word = 16;
	spi->mode = SPI_MODE_0;

	r = spi_setup(spi);
	अगर (r < 0) अणु
		dev_err(&spi->dev, "spi_setup failed: %d\n", r);
		वापस r;
	पूर्ण

	ddata = devm_kzalloc(&spi->dev, माप(*ddata), GFP_KERNEL);
	अगर (ddata == शून्य)
		वापस -ENOMEM;

	dev_set_drvdata(&spi->dev, ddata);

	ddata->spi = spi;

	r = tpo_td043_probe_of(spi);
	अगर (r)
		वापस r;

	ddata->mode = TPO_R02_MODE_800x480;
	स_नकल(ddata->gamma, tpo_td043_def_gamma, माप(ddata->gamma));

	ddata->vcc_reg = devm_regulator_get(&spi->dev, "vcc");
	अगर (IS_ERR(ddata->vcc_reg)) अणु
		dev_err(&spi->dev, "failed to get LCD VCC regulator\n");
		r = PTR_ERR(ddata->vcc_reg);
		जाओ err_regulator;
	पूर्ण

	अगर (gpio_is_valid(ddata->nreset_gpio)) अणु
		r = devm_gpio_request_one(&spi->dev,
				ddata->nreset_gpio, GPIOF_OUT_INIT_LOW,
				"lcd reset");
		अगर (r < 0) अणु
			dev_err(&spi->dev, "couldn't request reset GPIO\n");
			जाओ err_gpio_req;
		पूर्ण
	पूर्ण

	r = sysfs_create_group(&spi->dev.kobj, &tpo_td043_attr_group);
	अगर (r) अणु
		dev_err(&spi->dev, "failed to create sysfs files\n");
		जाओ err_sysfs;
	पूर्ण

	ddata->videomode = tpo_td043_timings;

	dssdev = &ddata->dssdev;
	dssdev->dev = &spi->dev;
	dssdev->driver = &tpo_td043_ops;
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
	sysfs_हटाओ_group(&spi->dev.kobj, &tpo_td043_attr_group);
err_sysfs:
err_gpio_req:
err_regulator:
	omap_dss_put_device(ddata->in);
	वापस r;
पूर्ण

अटल पूर्णांक tpo_td043_हटाओ(काष्ठा spi_device *spi)
अणु
	काष्ठा panel_drv_data *ddata = dev_get_drvdata(&spi->dev);
	काष्ठा omap_dss_device *dssdev = &ddata->dssdev;
	काष्ठा omap_dss_device *in = ddata->in;

	dev_dbg(&ddata->spi->dev, "%s\n", __func__);

	omapdss_unरेजिस्टर_display(dssdev);

	tpo_td043_disable(dssdev);
	tpo_td043_disconnect(dssdev);

	omap_dss_put_device(in);

	sysfs_हटाओ_group(&spi->dev.kobj, &tpo_td043_attr_group);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक tpo_td043_spi_suspend(काष्ठा device *dev)
अणु
	काष्ठा panel_drv_data *ddata = dev_get_drvdata(dev);

	dev_dbg(dev, "tpo_td043_spi_suspend, tpo %p\n", ddata);

	ddata->घातer_on_resume = ddata->घातered_on;
	tpo_td043_घातer_off(ddata);
	ddata->spi_suspended = 1;

	वापस 0;
पूर्ण

अटल पूर्णांक tpo_td043_spi_resume(काष्ठा device *dev)
अणु
	काष्ठा panel_drv_data *ddata = dev_get_drvdata(dev);
	पूर्णांक ret;

	dev_dbg(dev, "tpo_td043_spi_resume\n");

	अगर (ddata->घातer_on_resume) अणु
		ret = tpo_td043_घातer_on(ddata);
		अगर (ret)
			वापस ret;
	पूर्ण
	ddata->spi_suspended = 0;

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(tpo_td043_spi_pm,
	tpo_td043_spi_suspend, tpo_td043_spi_resume);

अटल स्थिर काष्ठा of_device_id tpo_td043_of_match[] = अणु
	अणु .compatible = "omapdss,tpo,td043mtea1", पूर्ण,
	अणुपूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(of, tpo_td043_of_match);

अटल काष्ठा spi_driver tpo_td043_spi_driver = अणु
	.driver = अणु
		.name	= "panel-tpo-td043mtea1",
		.pm	= &tpo_td043_spi_pm,
		.of_match_table = tpo_td043_of_match,
		.suppress_bind_attrs = true,
	पूर्ण,
	.probe	= tpo_td043_probe,
	.हटाओ	= tpo_td043_हटाओ,
पूर्ण;

module_spi_driver(tpo_td043_spi_driver);

MODULE_ALIAS("spi:tpo,td043mtea1");
MODULE_AUTHOR("Graधठvydas Ignotas <notasas@gmail.com>");
MODULE_DESCRIPTION("TPO TD043MTEA1 LCD Driver");
MODULE_LICENSE("GPL");
