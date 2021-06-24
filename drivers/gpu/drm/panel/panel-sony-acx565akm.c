<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Sony ACX565AKM LCD Panel driver
 *
 * Copyright (C) 2019 Texas Instruments Incorporated
 *
 * Based on the omapdrm-specअगरic panel-sony-acx565akm driver
 *
 * Copyright (C) 2010 Nokia Corporation
 * Author: Imre Deak <imre.deak@nokia.com>
 */

/*
 * TODO (to be addressed with hardware access to test the changes):
 *
 * - Update backlight support to use backlight_update_status() etc.
 * - Use prepare/unprepare क्रम the basic घातer on/off of the backligt
 */

#समावेश <linux/backlight.h>
#समावेश <linux/delay.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/sched.h>
#समावेश <linux/spi/spi.h>
#समावेश <video/mipi_display.h>

#समावेश <drm/drm_connector.h>
#समावेश <drm/drm_modes.h>
#समावेश <drm/drm_panel.h>

#घोषणा CTRL_DISP_BRIGHTNESS_CTRL_ON		BIT(5)
#घोषणा CTRL_DISP_AMBIENT_LIGHT_CTRL_ON		BIT(4)
#घोषणा CTRL_DISP_BACKLIGHT_ON			BIT(2)
#घोषणा CTRL_DISP_AUTO_BRIGHTNESS_ON		BIT(1)

#घोषणा MIPID_CMD_WRITE_CABC		0x55
#घोषणा MIPID_CMD_READ_CABC		0x56

#घोषणा MIPID_VER_LPH8923		3
#घोषणा MIPID_VER_LS041Y3		4
#घोषणा MIPID_VER_L4F00311		8
#घोषणा MIPID_VER_ACX565AKM		9

काष्ठा acx565akm_panel अणु
	काष्ठा drm_panel panel;

	काष्ठा spi_device *spi;
	काष्ठा gpio_desc *reset_gpio;
	काष्ठा backlight_device *backlight;

	काष्ठा mutex mutex;

	स्थिर अक्षर *name;
	u8 display_id[3];
	पूर्णांक model;
	पूर्णांक revision;
	bool has_bc;
	bool has_cabc;

	bool enabled;
	अचिन्हित पूर्णांक cabc_mode;
	/*
	 * Next value of jअगरfies when we can issue the next sleep in/out
	 * command.
	 */
	अचिन्हित दीर्घ hw_guard_end;
	अचिन्हित दीर्घ hw_guard_रुको;		/* max guard समय in jअगरfies */
पूर्ण;

#घोषणा to_acx565akm_device(p) container_of(p, काष्ठा acx565akm_panel, panel)

अटल व्योम acx565akm_transfer(काष्ठा acx565akm_panel *lcd, पूर्णांक cmd,
			      स्थिर u8 *wbuf, पूर्णांक wlen, u8 *rbuf, पूर्णांक rlen)
अणु
	काष्ठा spi_message	m;
	काष्ठा spi_transfer	*x, xfer[5];
	पूर्णांक			ret;

	spi_message_init(&m);

	स_रखो(xfer, 0, माप(xfer));
	x = &xfer[0];

	cmd &=  0xff;
	x->tx_buf = &cmd;
	x->bits_per_word = 9;
	x->len = 2;

	अगर (rlen > 1 && wlen == 0) अणु
		/*
		 * Between the command and the response data there is a
		 * dummy घड़ी cycle. Add an extra bit after the command
		 * word to account क्रम this.
		 */
		x->bits_per_word = 10;
		cmd <<= 1;
	पूर्ण
	spi_message_add_tail(x, &m);

	अगर (wlen) अणु
		x++;
		x->tx_buf = wbuf;
		x->len = wlen;
		x->bits_per_word = 9;
		spi_message_add_tail(x, &m);
	पूर्ण

	अगर (rlen) अणु
		x++;
		x->rx_buf	= rbuf;
		x->len		= rlen;
		spi_message_add_tail(x, &m);
	पूर्ण

	ret = spi_sync(lcd->spi, &m);
	अगर (ret < 0)
		dev_dbg(&lcd->spi->dev, "spi_sync %d\n", ret);
पूर्ण

अटल अंतरभूत व्योम acx565akm_cmd(काष्ठा acx565akm_panel *lcd, पूर्णांक cmd)
अणु
	acx565akm_transfer(lcd, cmd, शून्य, 0, शून्य, 0);
पूर्ण

अटल अंतरभूत व्योम acx565akm_ग_लिखो(काष्ठा acx565akm_panel *lcd,
			       पूर्णांक reg, स्थिर u8 *buf, पूर्णांक len)
अणु
	acx565akm_transfer(lcd, reg, buf, len, शून्य, 0);
पूर्ण

अटल अंतरभूत व्योम acx565akm_पढ़ो(काष्ठा acx565akm_panel *lcd,
			      पूर्णांक reg, u8 *buf, पूर्णांक len)
अणु
	acx565akm_transfer(lcd, reg, शून्य, 0, buf, len);
पूर्ण

/* -----------------------------------------------------------------------------
 * Auto Brightness Control Via sysfs
 */

अटल अचिन्हित पूर्णांक acx565akm_get_cabc_mode(काष्ठा acx565akm_panel *lcd)
अणु
	वापस lcd->cabc_mode;
पूर्ण

अटल व्योम acx565akm_set_cabc_mode(काष्ठा acx565akm_panel *lcd,
				    अचिन्हित पूर्णांक mode)
अणु
	u16 cabc_ctrl;

	lcd->cabc_mode = mode;
	अगर (!lcd->enabled)
		वापस;
	cabc_ctrl = 0;
	acx565akm_पढ़ो(lcd, MIPID_CMD_READ_CABC, (u8 *)&cabc_ctrl, 1);
	cabc_ctrl &= ~3;
	cabc_ctrl |= (1 << 8) | (mode & 3);
	acx565akm_ग_लिखो(lcd, MIPID_CMD_WRITE_CABC, (u8 *)&cabc_ctrl, 2);
पूर्ण

अटल अचिन्हित पूर्णांक acx565akm_get_hw_cabc_mode(काष्ठा acx565akm_panel *lcd)
अणु
	u8 cabc_ctrl;

	acx565akm_पढ़ो(lcd, MIPID_CMD_READ_CABC, &cabc_ctrl, 1);
	वापस cabc_ctrl & 3;
पूर्ण

अटल स्थिर अक्षर * स्थिर acx565akm_cabc_modes[] = अणु
	"off",		/* always used when CABC is not supported */
	"ui",
	"still-image",
	"moving-image",
पूर्ण;

अटल sमाप_प्रकार cabc_mode_show(काष्ठा device *dev,
			      काष्ठा device_attribute *attr,
			      अक्षर *buf)
अणु
	काष्ठा acx565akm_panel *lcd = dev_get_drvdata(dev);
	स्थिर अक्षर *mode_str;
	पूर्णांक mode;

	अगर (!lcd->has_cabc)
		mode = 0;
	अन्यथा
		mode = acx565akm_get_cabc_mode(lcd);

	mode_str = "unknown";
	अगर (mode >= 0 && mode < ARRAY_SIZE(acx565akm_cabc_modes))
		mode_str = acx565akm_cabc_modes[mode];

	वापस प्र_लिखो(buf, "%s\n", mode_str);
पूर्ण

अटल sमाप_प्रकार cabc_mode_store(काष्ठा device *dev,
			       काष्ठा device_attribute *attr,
			       स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा acx565akm_panel *lcd = dev_get_drvdata(dev);
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(acx565akm_cabc_modes); i++) अणु
		स्थिर अक्षर *mode_str = acx565akm_cabc_modes[i];
		पूर्णांक cmp_len = म_माप(mode_str);

		अगर (count > 0 && buf[count - 1] == '\n')
			count--;
		अगर (count != cmp_len)
			जारी;

		अगर (म_भेदन(buf, mode_str, cmp_len) == 0)
			अवरोध;
	पूर्ण

	अगर (i == ARRAY_SIZE(acx565akm_cabc_modes))
		वापस -EINVAL;

	अगर (!lcd->has_cabc && i != 0)
		वापस -EINVAL;

	mutex_lock(&lcd->mutex);
	acx565akm_set_cabc_mode(lcd, i);
	mutex_unlock(&lcd->mutex);

	वापस count;
पूर्ण

अटल sमाप_प्रकार cabc_available_modes_show(काष्ठा device *dev,
					 काष्ठा device_attribute *attr,
					 अक्षर *buf)
अणु
	काष्ठा acx565akm_panel *lcd = dev_get_drvdata(dev);
	अचिन्हित पूर्णांक i;
	माप_प्रकार len = 0;

	अगर (!lcd->has_cabc)
		वापस प्र_लिखो(buf, "%s\n", acx565akm_cabc_modes[0]);

	क्रम (i = 0; i < ARRAY_SIZE(acx565akm_cabc_modes); i++)
		len += प्र_लिखो(&buf[len], "%s%s", i ? " " : "",
			       acx565akm_cabc_modes[i]);

	buf[len++] = '\n';

	वापस len;
पूर्ण

अटल DEVICE_ATTR_RW(cabc_mode);
अटल DEVICE_ATTR_RO(cabc_available_modes);

अटल काष्ठा attribute *acx565akm_cabc_attrs[] = अणु
	&dev_attr_cabc_mode.attr,
	&dev_attr_cabc_available_modes.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group acx565akm_cabc_attr_group = अणु
	.attrs = acx565akm_cabc_attrs,
पूर्ण;

/* -----------------------------------------------------------------------------
 * Backlight Device
 */

अटल पूर्णांक acx565akm_get_actual_brightness(काष्ठा acx565akm_panel *lcd)
अणु
	u8 bv;

	acx565akm_पढ़ो(lcd, MIPI_DCS_GET_DISPLAY_BRIGHTNESS, &bv, 1);

	वापस bv;
पूर्ण

अटल व्योम acx565akm_set_brightness(काष्ठा acx565akm_panel *lcd, पूर्णांक level)
अणु
	u16 ctrl;
	पूर्णांक bv;

	bv = level | (1 << 8);
	acx565akm_ग_लिखो(lcd, MIPI_DCS_SET_DISPLAY_BRIGHTNESS, (u8 *)&bv, 2);

	acx565akm_पढ़ो(lcd, MIPI_DCS_GET_CONTROL_DISPLAY, (u8 *)&ctrl, 1);
	अगर (level)
		ctrl |= CTRL_DISP_BRIGHTNESS_CTRL_ON |
			CTRL_DISP_BACKLIGHT_ON;
	अन्यथा
		ctrl &= ~(CTRL_DISP_BRIGHTNESS_CTRL_ON |
			  CTRL_DISP_BACKLIGHT_ON);

	ctrl |= 1 << 8;
	acx565akm_ग_लिखो(lcd, MIPI_DCS_WRITE_CONTROL_DISPLAY, (u8 *)&ctrl, 2);
पूर्ण

अटल पूर्णांक acx565akm_bl_update_status_locked(काष्ठा backlight_device *dev)
अणु
	काष्ठा acx565akm_panel *lcd = dev_get_drvdata(&dev->dev);
	पूर्णांक level;

	अगर (dev->props.fb_blank == FB_BLANK_UNBLANK &&
	    dev->props.घातer == FB_BLANK_UNBLANK)
		level = dev->props.brightness;
	अन्यथा
		level = 0;

	acx565akm_set_brightness(lcd, level);

	वापस 0;
पूर्ण

अटल पूर्णांक acx565akm_bl_update_status(काष्ठा backlight_device *dev)
अणु
	काष्ठा acx565akm_panel *lcd = dev_get_drvdata(&dev->dev);
	पूर्णांक ret;

	mutex_lock(&lcd->mutex);
	ret = acx565akm_bl_update_status_locked(dev);
	mutex_unlock(&lcd->mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक acx565akm_bl_get_पूर्णांकensity(काष्ठा backlight_device *dev)
अणु
	काष्ठा acx565akm_panel *lcd = dev_get_drvdata(&dev->dev);
	अचिन्हित पूर्णांक पूर्णांकensity;

	mutex_lock(&lcd->mutex);

	अगर (dev->props.fb_blank == FB_BLANK_UNBLANK &&
	    dev->props.घातer == FB_BLANK_UNBLANK)
		पूर्णांकensity = acx565akm_get_actual_brightness(lcd);
	अन्यथा
		पूर्णांकensity = 0;

	mutex_unlock(&lcd->mutex);

	वापस पूर्णांकensity;
पूर्ण

अटल स्थिर काष्ठा backlight_ops acx565akm_bl_ops = अणु
	.get_brightness = acx565akm_bl_get_पूर्णांकensity,
	.update_status  = acx565akm_bl_update_status,
पूर्ण;

अटल पूर्णांक acx565akm_backlight_init(काष्ठा acx565akm_panel *lcd)
अणु
	काष्ठा backlight_properties props = अणु
		.fb_blank = FB_BLANK_UNBLANK,
		.घातer = FB_BLANK_UNBLANK,
		.type = BACKLIGHT_RAW,
	पूर्ण;
	पूर्णांक ret;

	lcd->backlight = backlight_device_रेजिस्टर(lcd->name, &lcd->spi->dev,
						   lcd, &acx565akm_bl_ops,
						   &props);
	अगर (IS_ERR(lcd->backlight)) अणु
		ret = PTR_ERR(lcd->backlight);
		lcd->backlight = शून्य;
		वापस ret;
	पूर्ण

	अगर (lcd->has_cabc) अणु
		ret = sysfs_create_group(&lcd->backlight->dev.kobj,
					 &acx565akm_cabc_attr_group);
		अगर (ret < 0) अणु
			dev_err(&lcd->spi->dev,
				"%s failed to create sysfs files\n", __func__);
			backlight_device_unरेजिस्टर(lcd->backlight);
			वापस ret;
		पूर्ण

		lcd->cabc_mode = acx565akm_get_hw_cabc_mode(lcd);
	पूर्ण

	lcd->backlight->props.max_brightness = 255;
	lcd->backlight->props.brightness = acx565akm_get_actual_brightness(lcd);

	acx565akm_bl_update_status_locked(lcd->backlight);

	वापस 0;
पूर्ण

अटल व्योम acx565akm_backlight_cleanup(काष्ठा acx565akm_panel *lcd)
अणु
	अगर (lcd->has_cabc)
		sysfs_हटाओ_group(&lcd->backlight->dev.kobj,
				   &acx565akm_cabc_attr_group);

	backlight_device_unरेजिस्टर(lcd->backlight);
पूर्ण

/* -----------------------------------------------------------------------------
 * DRM Bridge Operations
 */

अटल व्योम acx565akm_set_sleep_mode(काष्ठा acx565akm_panel *lcd, पूर्णांक on)
अणु
	पूर्णांक cmd = on ? MIPI_DCS_ENTER_SLEEP_MODE : MIPI_DCS_EXIT_SLEEP_MODE;
	अचिन्हित दीर्घ रुको;

	/*
	 * We have to keep 120msec between sleep in/out commands.
	 * (8.2.15, 8.2.16).
	 */
	रुको = lcd->hw_guard_end - jअगरfies;
	अगर ((दीर्घ)रुको > 0 && रुको <= lcd->hw_guard_रुको) अणु
		set_current_state(TASK_UNINTERRUPTIBLE);
		schedule_समयout(रुको);
	पूर्ण

	acx565akm_cmd(lcd, cmd);

	lcd->hw_guard_रुको = msecs_to_jअगरfies(120);
	lcd->hw_guard_end = jअगरfies + lcd->hw_guard_रुको;
पूर्ण

अटल व्योम acx565akm_set_display_state(काष्ठा acx565akm_panel *lcd,
					पूर्णांक enabled)
अणु
	पूर्णांक cmd = enabled ? MIPI_DCS_SET_DISPLAY_ON : MIPI_DCS_SET_DISPLAY_OFF;

	acx565akm_cmd(lcd, cmd);
पूर्ण

अटल पूर्णांक acx565akm_घातer_on(काष्ठा acx565akm_panel *lcd)
अणु
	/*FIXME tweak me */
	msleep(50);

	gpiod_set_value(lcd->reset_gpio, 1);

	अगर (lcd->enabled) अणु
		dev_dbg(&lcd->spi->dev, "panel already enabled\n");
		वापस 0;
	पूर्ण

	/*
	 * We have to meet all the following delay requirements:
	 * 1. tRW: reset pulse width 10usec (7.12.1)
	 * 2. tRT: reset cancel समय 5msec (7.12.1)
	 * 3. Providing PCLK,HS,VS संकेतs क्रम 2 frames = ~50msec worst
	 *    हाल (7.6.2)
	 * 4. 120msec beक्रमe the sleep out command (7.12.1)
	 */
	msleep(120);

	acx565akm_set_sleep_mode(lcd, 0);
	lcd->enabled = true;

	/* 5msec between sleep out and the next command. (8.2.16) */
	usleep_range(5000, 10000);
	acx565akm_set_display_state(lcd, 1);
	acx565akm_set_cabc_mode(lcd, lcd->cabc_mode);

	वापस acx565akm_bl_update_status_locked(lcd->backlight);
पूर्ण

अटल व्योम acx565akm_घातer_off(काष्ठा acx565akm_panel *lcd)
अणु
	अगर (!lcd->enabled)
		वापस;

	acx565akm_set_display_state(lcd, 0);
	acx565akm_set_sleep_mode(lcd, 1);
	lcd->enabled = false;
	/*
	 * We have to provide PCLK,HS,VS संकेतs क्रम 2 frames (worst हाल
	 * ~50msec) after sending the sleep in command and निश्चितing the
	 * reset संकेत. We probably could निश्चित the reset w/o the delay
	 * but we still delay to aव्योम possible artअगरacts. (7.6.1)
	 */
	msleep(50);

	gpiod_set_value(lcd->reset_gpio, 0);

	/* FIXME need to tweak this delay */
	msleep(100);
पूर्ण

अटल पूर्णांक acx565akm_disable(काष्ठा drm_panel *panel)
अणु
	काष्ठा acx565akm_panel *lcd = to_acx565akm_device(panel);

	mutex_lock(&lcd->mutex);
	acx565akm_घातer_off(lcd);
	mutex_unlock(&lcd->mutex);

	वापस 0;
पूर्ण

अटल पूर्णांक acx565akm_enable(काष्ठा drm_panel *panel)
अणु
	काष्ठा acx565akm_panel *lcd = to_acx565akm_device(panel);

	mutex_lock(&lcd->mutex);
	acx565akm_घातer_on(lcd);
	mutex_unlock(&lcd->mutex);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा drm_display_mode acx565akm_mode = अणु
	.घड़ी = 24000,
	.hdisplay = 800,
	.hsync_start = 800 + 28,
	.hsync_end = 800 + 28 + 4,
	.htotal = 800 + 28 + 4 + 24,
	.vdisplay = 480,
	.vsync_start = 480 + 3,
	.vsync_end = 480 + 3 + 3,
	.vtotal = 480 + 3 + 3 + 4,
	.type = DRM_MODE_TYPE_DRIVER | DRM_MODE_TYPE_PREFERRED,
	.flags = DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC,
	.width_mm = 77,
	.height_mm = 46,
पूर्ण;

अटल पूर्णांक acx565akm_get_modes(काष्ठा drm_panel *panel,
			       काष्ठा drm_connector *connector)
अणु
	काष्ठा drm_display_mode *mode;

	mode = drm_mode_duplicate(connector->dev, &acx565akm_mode);
	अगर (!mode)
		वापस -ENOMEM;

	drm_mode_set_name(mode);
	drm_mode_probed_add(connector, mode);

	connector->display_info.width_mm = acx565akm_mode.width_mm;
	connector->display_info.height_mm = acx565akm_mode.height_mm;
	connector->display_info.bus_flags = DRM_BUS_FLAG_DE_HIGH
					  | DRM_BUS_FLAG_SYNC_SAMPLE_POSEDGE
					  | DRM_BUS_FLAG_PIXDATA_SAMPLE_NEGEDGE;

	वापस 1;
पूर्ण

अटल स्थिर काष्ठा drm_panel_funcs acx565akm_funcs = अणु
	.disable = acx565akm_disable,
	.enable = acx565akm_enable,
	.get_modes = acx565akm_get_modes,
पूर्ण;

/* -----------------------------------------------------------------------------
 * Probe, Detect and Remove
 */

अटल पूर्णांक acx565akm_detect(काष्ठा acx565akm_panel *lcd)
अणु
	__be32 value;
	u32 status;
	पूर्णांक ret = 0;

	/*
	 * After being taken out of reset the panel needs 5ms beक्रमe the first
	 * command can be sent.
	 */
	gpiod_set_value(lcd->reset_gpio, 1);
	usleep_range(5000, 10000);

	acx565akm_पढ़ो(lcd, MIPI_DCS_GET_DISPLAY_STATUS, (u8 *)&value, 4);
	status = __be32_to_cpu(value);
	lcd->enabled = (status & (1 << 17)) && (status & (1 << 10));

	dev_dbg(&lcd->spi->dev,
		"LCD panel %s by bootloader (status 0x%04x)\n",
		lcd->enabled ? "enabled" : "disabled ", status);

	acx565akm_पढ़ो(lcd, MIPI_DCS_GET_DISPLAY_ID, lcd->display_id, 3);
	dev_dbg(&lcd->spi->dev, "MIPI display ID: %02x%02x%02x\n",
		lcd->display_id[0], lcd->display_id[1], lcd->display_id[2]);

	चयन (lcd->display_id[0]) अणु
	हाल 0x10:
		lcd->model = MIPID_VER_ACX565AKM;
		lcd->name = "acx565akm";
		lcd->has_bc = 1;
		lcd->has_cabc = 1;
		अवरोध;
	हाल 0x29:
		lcd->model = MIPID_VER_L4F00311;
		lcd->name = "l4f00311";
		अवरोध;
	हाल 0x45:
		lcd->model = MIPID_VER_LPH8923;
		lcd->name = "lph8923";
		अवरोध;
	हाल 0x83:
		lcd->model = MIPID_VER_LS041Y3;
		lcd->name = "ls041y3";
		अवरोध;
	शेष:
		lcd->name = "unknown";
		dev_err(&lcd->spi->dev, "unknown display ID\n");
		ret = -ENODEV;
		जाओ करोne;
	पूर्ण

	lcd->revision = lcd->display_id[1];

	dev_info(&lcd->spi->dev, "%s rev %02x panel detected\n",
		 lcd->name, lcd->revision);

करोne:
	अगर (!lcd->enabled)
		gpiod_set_value(lcd->reset_gpio, 0);

	वापस ret;
पूर्ण

अटल पूर्णांक acx565akm_probe(काष्ठा spi_device *spi)
अणु
	काष्ठा acx565akm_panel *lcd;
	पूर्णांक ret;

	lcd = devm_kzalloc(&spi->dev, माप(*lcd), GFP_KERNEL);
	अगर (!lcd)
		वापस -ENOMEM;

	spi_set_drvdata(spi, lcd);
	spi->mode = SPI_MODE_3;

	lcd->spi = spi;
	mutex_init(&lcd->mutex);

	lcd->reset_gpio = devm_gpiod_get(&spi->dev, "reset", GPIOD_OUT_HIGH);
	अगर (IS_ERR(lcd->reset_gpio)) अणु
		dev_err(&spi->dev, "failed to get reset GPIO\n");
		वापस PTR_ERR(lcd->reset_gpio);
	पूर्ण

	ret = acx565akm_detect(lcd);
	अगर (ret < 0) अणु
		dev_err(&spi->dev, "panel detection failed\n");
		वापस ret;
	पूर्ण

	अगर (lcd->has_bc) अणु
		ret = acx565akm_backlight_init(lcd);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	drm_panel_init(&lcd->panel, &lcd->spi->dev, &acx565akm_funcs,
		       DRM_MODE_CONNECTOR_DPI);

	drm_panel_add(&lcd->panel);

	वापस 0;
पूर्ण

अटल पूर्णांक acx565akm_हटाओ(काष्ठा spi_device *spi)
अणु
	काष्ठा acx565akm_panel *lcd = spi_get_drvdata(spi);

	drm_panel_हटाओ(&lcd->panel);

	अगर (lcd->has_bc)
		acx565akm_backlight_cleanup(lcd);

	drm_panel_disable(&lcd->panel);
	drm_panel_unprepare(&lcd->panel);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id acx565akm_of_match[] = अणु
	अणु .compatible = "sony,acx565akm", पूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(of, acx565akm_of_match);

अटल स्थिर काष्ठा spi_device_id acx565akm_ids[] = अणु
	अणु "acx565akm", 0 पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(spi, acx565akm_ids);

अटल काष्ठा spi_driver acx565akm_driver = अणु
	.probe		= acx565akm_probe,
	.हटाओ		= acx565akm_हटाओ,
	.id_table	= acx565akm_ids,
	.driver		= अणु
		.name	= "panel-sony-acx565akm",
		.of_match_table = acx565akm_of_match,
	पूर्ण,
पूर्ण;

module_spi_driver(acx565akm_driver);

MODULE_AUTHOR("Nokia Corporation");
MODULE_DESCRIPTION("Sony ACX565AKM LCD Panel Driver");
MODULE_LICENSE("GPL");
