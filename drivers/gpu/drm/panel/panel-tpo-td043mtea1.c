<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Toppoly TD043MTEA1 Panel Driver
 *
 * Copyright (C) 2019 Texas Instruments Incorporated
 *
 * Based on the omapdrm-specअगरic panel-tpo-td043mtea1 driver
 *
 * Author: Graधठvydas Ignotas <notasas@gmail.com>
 */

#समावेश <linux/delay.h>
#समावेश <linux/module.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/spi/spi.h>

#समावेश <drm/drm_connector.h>
#समावेश <drm/drm_modes.h>
#समावेश <drm/drm_panel.h>

#घोषणा TPO_R02_MODE(x)			((x) & 7)
#घोषणा TPO_R02_MODE_800x480		7
#घोषणा TPO_R02_NCLK_RISING		BIT(3)
#घोषणा TPO_R02_HSYNC_HIGH		BIT(4)
#घोषणा TPO_R02_VSYNC_HIGH		BIT(5)

#घोषणा TPO_R03_NSTANDBY		BIT(0)
#घोषणा TPO_R03_EN_CP_CLK		BIT(1)
#घोषणा TPO_R03_EN_VGL_PUMP		BIT(2)
#घोषणा TPO_R03_EN_PWM			BIT(3)
#घोषणा TPO_R03_DRIVING_CAP_100		BIT(4)
#घोषणा TPO_R03_EN_PRE_CHARGE		BIT(6)
#घोषणा TPO_R03_SOFTWARE_CTL		BIT(7)

#घोषणा TPO_R04_NFLIP_H			BIT(0)
#घोषणा TPO_R04_NFLIP_V			BIT(1)
#घोषणा TPO_R04_CP_CLK_FREQ_1H		BIT(2)
#घोषणा TPO_R04_VGL_FREQ_1H		BIT(4)

#घोषणा TPO_R03_VAL_NORMAL \
	(TPO_R03_NSTANDBY | TPO_R03_EN_CP_CLK | TPO_R03_EN_VGL_PUMP | \
	 TPO_R03_EN_PWM | TPO_R03_DRIVING_CAP_100 | TPO_R03_EN_PRE_CHARGE | \
	 TPO_R03_SOFTWARE_CTL)

#घोषणा TPO_R03_VAL_STANDBY \
	(TPO_R03_DRIVING_CAP_100 | TPO_R03_EN_PRE_CHARGE | \
	 TPO_R03_SOFTWARE_CTL)

अटल स्थिर u16 td043mtea1_def_gamma[12] = अणु
	105, 315, 381, 431, 490, 537, 579, 686, 780, 837, 880, 1023
पूर्ण;

काष्ठा td043mtea1_panel अणु
	काष्ठा drm_panel panel;

	काष्ठा spi_device *spi;
	काष्ठा regulator *vcc_reg;
	काष्ठा gpio_desc *reset_gpio;

	अचिन्हित पूर्णांक mode;
	u16 gamma[12];
	bool vmirror;
	bool घातered_on;
	bool spi_suspended;
	bool घातer_on_resume;
पूर्ण;

#घोषणा to_td043mtea1_device(p) container_of(p, काष्ठा td043mtea1_panel, panel)

/* -----------------------------------------------------------------------------
 * Hardware Access
 */

अटल पूर्णांक td043mtea1_ग_लिखो(काष्ठा td043mtea1_panel *lcd, u8 addr, u8 value)
अणु
	काष्ठा spi_message msg;
	काष्ठा spi_transfer xfer;
	u16 data;
	पूर्णांक ret;

	spi_message_init(&msg);

	स_रखो(&xfer, 0, माप(xfer));

	data = ((u16)addr << 10) | (1 << 8) | value;
	xfer.tx_buf = &data;
	xfer.bits_per_word = 16;
	xfer.len = 2;
	spi_message_add_tail(&xfer, &msg);

	ret = spi_sync(lcd->spi, &msg);
	अगर (ret < 0)
		dev_warn(&lcd->spi->dev, "failed to write to LCD reg (%d)\n",
			 ret);

	वापस ret;
पूर्ण

अटल व्योम td043mtea1_ग_लिखो_gamma(काष्ठा td043mtea1_panel *lcd)
अणु
	स्थिर u16 *gamma = lcd->gamma;
	अचिन्हित पूर्णांक i;
	u8 val;

	/* gamma bits [9:8] */
	क्रम (val = i = 0; i < 4; i++)
		val |= (gamma[i] & 0x300) >> ((i + 1) * 2);
	td043mtea1_ग_लिखो(lcd, 0x11, val);

	क्रम (val = i = 0; i < 4; i++)
		val |= (gamma[i + 4] & 0x300) >> ((i + 1) * 2);
	td043mtea1_ग_लिखो(lcd, 0x12, val);

	क्रम (val = i = 0; i < 4; i++)
		val |= (gamma[i + 8] & 0x300) >> ((i + 1) * 2);
	td043mtea1_ग_लिखो(lcd, 0x13, val);

	/* gamma bits [7:0] */
	क्रम (i = 0; i < 12; i++)
		td043mtea1_ग_लिखो(lcd, 0x14 + i, gamma[i] & 0xff);
पूर्ण

अटल पूर्णांक td043mtea1_ग_लिखो_mirror(काष्ठा td043mtea1_panel *lcd)
अणु
	u8 reg4 = TPO_R04_NFLIP_H | TPO_R04_NFLIP_V |
		TPO_R04_CP_CLK_FREQ_1H | TPO_R04_VGL_FREQ_1H;
	अगर (lcd->vmirror)
		reg4 &= ~TPO_R04_NFLIP_V;

	वापस td043mtea1_ग_लिखो(lcd, 4, reg4);
पूर्ण

अटल पूर्णांक td043mtea1_घातer_on(काष्ठा td043mtea1_panel *lcd)
अणु
	पूर्णांक ret;

	अगर (lcd->घातered_on)
		वापस 0;

	ret = regulator_enable(lcd->vcc_reg);
	अगर (ret < 0)
		वापस ret;

	/* Wait क्रम the panel to stabilize. */
	msleep(160);

	gpiod_set_value(lcd->reset_gpio, 0);

	td043mtea1_ग_लिखो(lcd, 2, TPO_R02_MODE(lcd->mode) | TPO_R02_NCLK_RISING);
	td043mtea1_ग_लिखो(lcd, 3, TPO_R03_VAL_NORMAL);
	td043mtea1_ग_लिखो(lcd, 0x20, 0xf0);
	td043mtea1_ग_लिखो(lcd, 0x21, 0xf0);
	td043mtea1_ग_लिखो_mirror(lcd);
	td043mtea1_ग_लिखो_gamma(lcd);

	lcd->घातered_on = true;

	वापस 0;
पूर्ण

अटल व्योम td043mtea1_घातer_off(काष्ठा td043mtea1_panel *lcd)
अणु
	अगर (!lcd->घातered_on)
		वापस;

	td043mtea1_ग_लिखो(lcd, 3, TPO_R03_VAL_STANDBY | TPO_R03_EN_PWM);

	gpiod_set_value(lcd->reset_gpio, 1);

	/* रुको क्रम at least 2 vsyncs beक्रमe cutting off घातer */
	msleep(50);

	td043mtea1_ग_लिखो(lcd, 3, TPO_R03_VAL_STANDBY);

	regulator_disable(lcd->vcc_reg);

	lcd->घातered_on = false;
पूर्ण

/* -----------------------------------------------------------------------------
 * sysfs
 */

अटल sमाप_प्रकार vmirror_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			    अक्षर *buf)
अणु
	काष्ठा td043mtea1_panel *lcd = dev_get_drvdata(dev);

	वापस sysfs_emit(buf, "%d\n", lcd->vmirror);
पूर्ण

अटल sमाप_प्रकार vmirror_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
			     स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा td043mtea1_panel *lcd = dev_get_drvdata(dev);
	पूर्णांक val;
	पूर्णांक ret;

	ret = kstrtoपूर्णांक(buf, 0, &val);
	अगर (ret < 0)
		वापस ret;

	lcd->vmirror = !!val;

	ret = td043mtea1_ग_लिखो_mirror(lcd);
	अगर (ret < 0)
		वापस ret;

	वापस count;
पूर्ण

अटल sमाप_प्रकार mode_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			 अक्षर *buf)
अणु
	काष्ठा td043mtea1_panel *lcd = dev_get_drvdata(dev);

	वापस sysfs_emit(buf, "%d\n", lcd->mode);
पूर्ण

अटल sमाप_प्रकार mode_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
			  स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा td043mtea1_panel *lcd = dev_get_drvdata(dev);
	दीर्घ val;
	पूर्णांक ret;

	ret = kम_से_दीर्घ(buf, 0, &val);
	अगर (ret != 0 || val & ~7)
		वापस -EINVAL;

	lcd->mode = val;

	val |= TPO_R02_NCLK_RISING;
	td043mtea1_ग_लिखो(lcd, 2, val);

	वापस count;
पूर्ण

अटल sमाप_प्रकार gamma_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			  अक्षर *buf)
अणु
	काष्ठा td043mtea1_panel *lcd = dev_get_drvdata(dev);
	sमाप_प्रकार len = 0;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	क्रम (i = 0; i < ARRAY_SIZE(lcd->gamma); i++) अणु
		ret = snम_लिखो(buf + len, PAGE_SIZE - len, "%u ",
			       lcd->gamma[i]);
		अगर (ret < 0)
			वापस ret;
		len += ret;
	पूर्ण
	buf[len - 1] = '\n';

	वापस len;
पूर्ण

अटल sमाप_प्रकार gamma_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
			   स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा td043mtea1_panel *lcd = dev_get_drvdata(dev);
	अचिन्हित पूर्णांक g[12];
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	ret = माला_पूछो(buf, "%u %u %u %u %u %u %u %u %u %u %u %u",
		     &g[0], &g[1], &g[2], &g[3], &g[4], &g[5],
		     &g[6], &g[7], &g[8], &g[9], &g[10], &g[11]);
	अगर (ret != 12)
		वापस -EINVAL;

	क्रम (i = 0; i < 12; i++)
		lcd->gamma[i] = g[i];

	td043mtea1_ग_लिखो_gamma(lcd);

	वापस count;
पूर्ण

अटल DEVICE_ATTR_RW(vmirror);
अटल DEVICE_ATTR_RW(mode);
अटल DEVICE_ATTR_RW(gamma);

अटल काष्ठा attribute *td043mtea1_attrs[] = अणु
	&dev_attr_vmirror.attr,
	&dev_attr_mode.attr,
	&dev_attr_gamma.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group td043mtea1_attr_group = अणु
	.attrs = td043mtea1_attrs,
पूर्ण;

/* -----------------------------------------------------------------------------
 * Panel Operations
 */

अटल पूर्णांक td043mtea1_unprepare(काष्ठा drm_panel *panel)
अणु
	काष्ठा td043mtea1_panel *lcd = to_td043mtea1_device(panel);

	अगर (!lcd->spi_suspended)
		td043mtea1_घातer_off(lcd);

	वापस 0;
पूर्ण

अटल पूर्णांक td043mtea1_prepare(काष्ठा drm_panel *panel)
अणु
	काष्ठा td043mtea1_panel *lcd = to_td043mtea1_device(panel);
	पूर्णांक ret;

	/*
	 * If we are resuming from प्रणाली suspend, SPI might not be enabled
	 * yet, so we'll program the LCD from SPI PM resume callback.
	 */
	अगर (lcd->spi_suspended)
		वापस 0;

	ret = td043mtea1_घातer_on(lcd);
	अगर (ret) अणु
		dev_err(&lcd->spi->dev, "%s: power on failed (%d)\n",
			__func__, ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा drm_display_mode td043mtea1_mode = अणु
	.घड़ी = 36000,
	.hdisplay = 800,
	.hsync_start = 800 + 68,
	.hsync_end = 800 + 68 + 1,
	.htotal = 800 + 68 + 1 + 214,
	.vdisplay = 480,
	.vsync_start = 480 + 39,
	.vsync_end = 480 + 39 + 1,
	.vtotal = 480 + 39 + 1 + 34,
	.type = DRM_MODE_TYPE_DRIVER | DRM_MODE_TYPE_PREFERRED,
	.flags = DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC,
	.width_mm = 94,
	.height_mm = 56,
पूर्ण;

अटल पूर्णांक td043mtea1_get_modes(काष्ठा drm_panel *panel,
				काष्ठा drm_connector *connector)
अणु
	काष्ठा drm_display_mode *mode;

	mode = drm_mode_duplicate(connector->dev, &td043mtea1_mode);
	अगर (!mode)
		वापस -ENOMEM;

	drm_mode_set_name(mode);
	drm_mode_probed_add(connector, mode);

	connector->display_info.width_mm = td043mtea1_mode.width_mm;
	connector->display_info.height_mm = td043mtea1_mode.height_mm;
	/*
	 * FIXME: According to the datasheet sync संकेतs are sampled on the
	 * rising edge of the घड़ी, but the code running on the OMAP3 Panकरोra
	 * indicates sampling on the falling edge. This should be tested on a
	 * real device.
	 */
	connector->display_info.bus_flags = DRM_BUS_FLAG_DE_HIGH
					  | DRM_BUS_FLAG_SYNC_SAMPLE_NEGEDGE
					  | DRM_BUS_FLAG_PIXDATA_SAMPLE_POSEDGE;

	वापस 1;
पूर्ण

अटल स्थिर काष्ठा drm_panel_funcs td043mtea1_funcs = अणु
	.unprepare = td043mtea1_unprepare,
	.prepare = td043mtea1_prepare,
	.get_modes = td043mtea1_get_modes,
पूर्ण;

/* -----------------------------------------------------------------------------
 * Power Management, Probe and Remove
 */

अटल पूर्णांक __maybe_unused td043mtea1_suspend(काष्ठा device *dev)
अणु
	काष्ठा td043mtea1_panel *lcd = dev_get_drvdata(dev);

	अगर (lcd->घातered_on) अणु
		td043mtea1_घातer_off(lcd);
		lcd->घातered_on = true;
	पूर्ण

	lcd->spi_suspended = true;

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused td043mtea1_resume(काष्ठा device *dev)
अणु
	काष्ठा td043mtea1_panel *lcd = dev_get_drvdata(dev);
	पूर्णांक ret;

	lcd->spi_suspended = false;

	अगर (lcd->घातered_on) अणु
		lcd->घातered_on = false;
		ret = td043mtea1_घातer_on(lcd);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(td043mtea1_pm_ops, td043mtea1_suspend,
			 td043mtea1_resume);

अटल पूर्णांक td043mtea1_probe(काष्ठा spi_device *spi)
अणु
	काष्ठा td043mtea1_panel *lcd;
	पूर्णांक ret;

	lcd = devm_kzalloc(&spi->dev, माप(*lcd), GFP_KERNEL);
	अगर (lcd == शून्य)
		वापस -ENOMEM;

	spi_set_drvdata(spi, lcd);
	lcd->spi = spi;
	lcd->mode = TPO_R02_MODE_800x480;
	स_नकल(lcd->gamma, td043mtea1_def_gamma, माप(lcd->gamma));

	lcd->vcc_reg = devm_regulator_get(&spi->dev, "vcc");
	अगर (IS_ERR(lcd->vcc_reg)) अणु
		dev_err(&spi->dev, "failed to get VCC regulator\n");
		वापस PTR_ERR(lcd->vcc_reg);
	पूर्ण

	lcd->reset_gpio = devm_gpiod_get(&spi->dev, "reset", GPIOD_OUT_HIGH);
	अगर (IS_ERR(lcd->reset_gpio)) अणु
		dev_err(&spi->dev, "failed to get reset GPIO\n");
		वापस PTR_ERR(lcd->reset_gpio);
	पूर्ण

	spi->bits_per_word = 16;
	spi->mode = SPI_MODE_0;

	ret = spi_setup(spi);
	अगर (ret < 0) अणु
		dev_err(&spi->dev, "failed to setup SPI: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = sysfs_create_group(&spi->dev.kobj, &td043mtea1_attr_group);
	अगर (ret < 0) अणु
		dev_err(&spi->dev, "failed to create sysfs files\n");
		वापस ret;
	पूर्ण

	drm_panel_init(&lcd->panel, &lcd->spi->dev, &td043mtea1_funcs,
		       DRM_MODE_CONNECTOR_DPI);

	drm_panel_add(&lcd->panel);

	वापस 0;
पूर्ण

अटल पूर्णांक td043mtea1_हटाओ(काष्ठा spi_device *spi)
अणु
	काष्ठा td043mtea1_panel *lcd = spi_get_drvdata(spi);

	drm_panel_हटाओ(&lcd->panel);
	drm_panel_disable(&lcd->panel);
	drm_panel_unprepare(&lcd->panel);

	sysfs_हटाओ_group(&spi->dev.kobj, &td043mtea1_attr_group);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id td043mtea1_of_match[] = अणु
	अणु .compatible = "tpo,td043mtea1", पूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(of, td043mtea1_of_match);

अटल स्थिर काष्ठा spi_device_id td043mtea1_ids[] = अणु
	अणु "td043mtea1", 0 पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(spi, td043mtea1_ids);

अटल काष्ठा spi_driver td043mtea1_driver = अणु
	.probe		= td043mtea1_probe,
	.हटाओ		= td043mtea1_हटाओ,
	.id_table	= td043mtea1_ids,
	.driver		= अणु
		.name	= "panel-tpo-td043mtea1",
		.pm	= &td043mtea1_pm_ops,
		.of_match_table = td043mtea1_of_match,
	पूर्ण,
पूर्ण;

module_spi_driver(td043mtea1_driver);

MODULE_AUTHOR("Graधठvydas Ignotas <notasas@gmail.com>");
MODULE_DESCRIPTION("TPO TD043MTEA1 Panel Driver");
MODULE_LICENSE("GPL");
