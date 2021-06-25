<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Sony ACX565AKM LCD Panel driver
 *
 * Copyright (C) 2010 Nokia Corporation
 *
 * Original Driver Author: Imre Deak <imre.deak@nokia.com>
 * Based on panel-generic.c by Tomi Valkeinen <tomi.valkeinen@nokia.com>
 * Adapted to new DSS2 framework: Roger Quadros <roger.quadros@nokia.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/delay.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/sched.h>
#समावेश <linux/backlight.h>
#समावेश <linux/fb.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/of.h>
#समावेश <linux/of_gpपन.स>

#समावेश <video/omapfb_dss.h>
#समावेश <video/omap-panel-data.h>

#घोषणा MIPID_CMD_READ_DISP_ID		0x04
#घोषणा MIPID_CMD_READ_RED		0x06
#घोषणा MIPID_CMD_READ_GREEN		0x07
#घोषणा MIPID_CMD_READ_BLUE		0x08
#घोषणा MIPID_CMD_READ_DISP_STATUS	0x09
#घोषणा MIPID_CMD_RDDSDR		0x0F
#घोषणा MIPID_CMD_SLEEP_IN		0x10
#घोषणा MIPID_CMD_SLEEP_OUT		0x11
#घोषणा MIPID_CMD_DISP_OFF		0x28
#घोषणा MIPID_CMD_DISP_ON		0x29
#घोषणा MIPID_CMD_WRITE_DISP_BRIGHTNESS	0x51
#घोषणा MIPID_CMD_READ_DISP_BRIGHTNESS	0x52
#घोषणा MIPID_CMD_WRITE_CTRL_DISP	0x53

#घोषणा CTRL_DISP_BRIGHTNESS_CTRL_ON	(1 << 5)
#घोषणा CTRL_DISP_AMBIENT_LIGHT_CTRL_ON	(1 << 4)
#घोषणा CTRL_DISP_BACKLIGHT_ON		(1 << 2)
#घोषणा CTRL_DISP_AUTO_BRIGHTNESS_ON	(1 << 1)

#घोषणा MIPID_CMD_READ_CTRL_DISP	0x54
#घोषणा MIPID_CMD_WRITE_CABC		0x55
#घोषणा MIPID_CMD_READ_CABC		0x56

#घोषणा MIPID_VER_LPH8923		3
#घोषणा MIPID_VER_LS041Y3		4
#घोषणा MIPID_VER_L4F00311		8
#घोषणा MIPID_VER_ACX565AKM		9

काष्ठा panel_drv_data अणु
	काष्ठा omap_dss_device	dssdev;
	काष्ठा omap_dss_device *in;

	पूर्णांक reset_gpio;
	पूर्णांक datapairs;

	काष्ठा omap_video_timings videomode;

	अक्षर		*name;
	पूर्णांक		enabled;
	पूर्णांक		model;
	पूर्णांक		revision;
	u8		display_id[3];
	अचिन्हित	has_bc:1;
	अचिन्हित	has_cabc:1;
	अचिन्हित	cabc_mode;
	अचिन्हित दीर्घ	hw_guard_end;		/* next value of jअगरfies
						   when we can issue the
						   next sleep in/out command */
	अचिन्हित दीर्घ	hw_guard_रुको;		/* max guard समय in jअगरfies */

	काष्ठा spi_device	*spi;
	काष्ठा mutex		mutex;

	काष्ठा backlight_device *bl_dev;
पूर्ण;

अटल स्थिर काष्ठा omap_video_timings acx565akm_panel_timings = अणु
	.x_res		= 800,
	.y_res		= 480,
	.pixelघड़ी	= 24000000,
	.hfp		= 28,
	.hsw		= 4,
	.hbp		= 24,
	.vfp		= 3,
	.vsw		= 3,
	.vbp		= 4,

	.vsync_level	= OMAPDSS_SIG_ACTIVE_LOW,
	.hsync_level	= OMAPDSS_SIG_ACTIVE_LOW,

	.data_pclk_edge	= OMAPDSS_DRIVE_SIG_RISING_EDGE,
	.de_level	= OMAPDSS_SIG_ACTIVE_HIGH,
	.sync_pclk_edge	= OMAPDSS_DRIVE_SIG_FALLING_EDGE,
पूर्ण;

#घोषणा to_panel_data(p) container_of(p, काष्ठा panel_drv_data, dssdev)

अटल व्योम acx565akm_transfer(काष्ठा panel_drv_data *ddata, पूर्णांक cmd,
			      स्थिर u8 *wbuf, पूर्णांक wlen, u8 *rbuf, पूर्णांक rlen)
अणु
	काष्ठा spi_message	m;
	काष्ठा spi_transfer	*x, xfer[5];
	पूर्णांक			r;

	BUG_ON(ddata->spi == शून्य);

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

	r = spi_sync(ddata->spi, &m);
	अगर (r < 0)
		dev_dbg(&ddata->spi->dev, "spi_sync %d\n", r);
पूर्ण

अटल अंतरभूत व्योम acx565akm_cmd(काष्ठा panel_drv_data *ddata, पूर्णांक cmd)
अणु
	acx565akm_transfer(ddata, cmd, शून्य, 0, शून्य, 0);
पूर्ण

अटल अंतरभूत व्योम acx565akm_ग_लिखो(काष्ठा panel_drv_data *ddata,
			       पूर्णांक reg, स्थिर u8 *buf, पूर्णांक len)
अणु
	acx565akm_transfer(ddata, reg, buf, len, शून्य, 0);
पूर्ण

अटल अंतरभूत व्योम acx565akm_पढ़ो(काष्ठा panel_drv_data *ddata,
			      पूर्णांक reg, u8 *buf, पूर्णांक len)
अणु
	acx565akm_transfer(ddata, reg, शून्य, 0, buf, len);
पूर्ण

अटल व्योम hw_guard_start(काष्ठा panel_drv_data *ddata, पूर्णांक guard_msec)
अणु
	ddata->hw_guard_रुको = msecs_to_jअगरfies(guard_msec);
	ddata->hw_guard_end = jअगरfies + ddata->hw_guard_रुको;
पूर्ण

अटल व्योम hw_guard_रुको(काष्ठा panel_drv_data *ddata)
अणु
	अचिन्हित दीर्घ रुको = ddata->hw_guard_end - jअगरfies;

	अगर ((दीर्घ)रुको > 0 && रुको <= ddata->hw_guard_रुको) अणु
		set_current_state(TASK_UNINTERRUPTIBLE);
		schedule_समयout(रुको);
	पूर्ण
पूर्ण

अटल व्योम set_sleep_mode(काष्ठा panel_drv_data *ddata, पूर्णांक on)
अणु
	पूर्णांक cmd;

	अगर (on)
		cmd = MIPID_CMD_SLEEP_IN;
	अन्यथा
		cmd = MIPID_CMD_SLEEP_OUT;
	/*
	 * We have to keep 120msec between sleep in/out commands.
	 * (8.2.15, 8.2.16).
	 */
	hw_guard_रुको(ddata);
	acx565akm_cmd(ddata, cmd);
	hw_guard_start(ddata, 120);
पूर्ण

अटल व्योम set_display_state(काष्ठा panel_drv_data *ddata, पूर्णांक enabled)
अणु
	पूर्णांक cmd = enabled ? MIPID_CMD_DISP_ON : MIPID_CMD_DISP_OFF;

	acx565akm_cmd(ddata, cmd);
पूर्ण

अटल पूर्णांक panel_enabled(काष्ठा panel_drv_data *ddata)
अणु
	u32 disp_status;
	पूर्णांक enabled;

	acx565akm_पढ़ो(ddata, MIPID_CMD_READ_DISP_STATUS,
			(u8 *)&disp_status, 4);
	disp_status = __be32_to_cpu(disp_status);
	enabled = (disp_status & (1 << 17)) && (disp_status & (1 << 10));
	dev_dbg(&ddata->spi->dev,
		"LCD panel %senabled by bootloader (status 0x%04x)\n",
		enabled ? "" : "not ", disp_status);
	वापस enabled;
पूर्ण

अटल पूर्णांक panel_detect(काष्ठा panel_drv_data *ddata)
अणु
	acx565akm_पढ़ो(ddata, MIPID_CMD_READ_DISP_ID, ddata->display_id, 3);
	dev_dbg(&ddata->spi->dev, "MIPI display ID: %02x%02x%02x\n",
		ddata->display_id[0],
		ddata->display_id[1],
		ddata->display_id[2]);

	चयन (ddata->display_id[0]) अणु
	हाल 0x10:
		ddata->model = MIPID_VER_ACX565AKM;
		ddata->name = "acx565akm";
		ddata->has_bc = 1;
		ddata->has_cabc = 1;
		अवरोध;
	हाल 0x29:
		ddata->model = MIPID_VER_L4F00311;
		ddata->name = "l4f00311";
		अवरोध;
	हाल 0x45:
		ddata->model = MIPID_VER_LPH8923;
		ddata->name = "lph8923";
		अवरोध;
	हाल 0x83:
		ddata->model = MIPID_VER_LS041Y3;
		ddata->name = "ls041y3";
		अवरोध;
	शेष:
		ddata->name = "unknown";
		dev_err(&ddata->spi->dev, "invalid display ID\n");
		वापस -ENODEV;
	पूर्ण

	ddata->revision = ddata->display_id[1];

	dev_info(&ddata->spi->dev, "omapfb: %s rev %02x LCD detected\n",
			ddata->name, ddata->revision);

	वापस 0;
पूर्ण

/*----------------------Backlight Control-------------------------*/

अटल व्योम enable_backlight_ctrl(काष्ठा panel_drv_data *ddata, पूर्णांक enable)
अणु
	u16 ctrl;

	acx565akm_पढ़ो(ddata, MIPID_CMD_READ_CTRL_DISP, (u8 *)&ctrl, 1);
	अगर (enable) अणु
		ctrl |= CTRL_DISP_BRIGHTNESS_CTRL_ON |
			CTRL_DISP_BACKLIGHT_ON;
	पूर्ण अन्यथा अणु
		ctrl &= ~(CTRL_DISP_BRIGHTNESS_CTRL_ON |
			  CTRL_DISP_BACKLIGHT_ON);
	पूर्ण

	ctrl |= 1 << 8;
	acx565akm_ग_लिखो(ddata, MIPID_CMD_WRITE_CTRL_DISP, (u8 *)&ctrl, 2);
पूर्ण

अटल व्योम set_cabc_mode(काष्ठा panel_drv_data *ddata, अचिन्हित mode)
अणु
	u16 cabc_ctrl;

	ddata->cabc_mode = mode;
	अगर (!ddata->enabled)
		वापस;
	cabc_ctrl = 0;
	acx565akm_पढ़ो(ddata, MIPID_CMD_READ_CABC, (u8 *)&cabc_ctrl, 1);
	cabc_ctrl &= ~3;
	cabc_ctrl |= (1 << 8) | (mode & 3);
	acx565akm_ग_लिखो(ddata, MIPID_CMD_WRITE_CABC, (u8 *)&cabc_ctrl, 2);
पूर्ण

अटल अचिन्हित get_cabc_mode(काष्ठा panel_drv_data *ddata)
अणु
	वापस ddata->cabc_mode;
पूर्ण

अटल अचिन्हित get_hw_cabc_mode(काष्ठा panel_drv_data *ddata)
अणु
	u8 cabc_ctrl;

	acx565akm_पढ़ो(ddata, MIPID_CMD_READ_CABC, &cabc_ctrl, 1);
	वापस cabc_ctrl & 3;
पूर्ण

अटल व्योम acx565akm_set_brightness(काष्ठा panel_drv_data *ddata, पूर्णांक level)
अणु
	पूर्णांक bv;

	bv = level | (1 << 8);
	acx565akm_ग_लिखो(ddata, MIPID_CMD_WRITE_DISP_BRIGHTNESS, (u8 *)&bv, 2);

	अगर (level)
		enable_backlight_ctrl(ddata, 1);
	अन्यथा
		enable_backlight_ctrl(ddata, 0);
पूर्ण

अटल पूर्णांक acx565akm_get_actual_brightness(काष्ठा panel_drv_data *ddata)
अणु
	u8 bv;

	acx565akm_पढ़ो(ddata, MIPID_CMD_READ_DISP_BRIGHTNESS, &bv, 1);

	वापस bv;
पूर्ण


अटल पूर्णांक acx565akm_bl_update_status(काष्ठा backlight_device *dev)
अणु
	काष्ठा panel_drv_data *ddata = dev_get_drvdata(&dev->dev);
	पूर्णांक level;

	dev_dbg(&ddata->spi->dev, "%s\n", __func__);

	अगर (dev->props.fb_blank == FB_BLANK_UNBLANK &&
			dev->props.घातer == FB_BLANK_UNBLANK)
		level = dev->props.brightness;
	अन्यथा
		level = 0;

	अगर (ddata->has_bc)
		acx565akm_set_brightness(ddata, level);
	अन्यथा
		वापस -ENODEV;

	वापस 0;
पूर्ण

अटल पूर्णांक acx565akm_bl_get_पूर्णांकensity(काष्ठा backlight_device *dev)
अणु
	काष्ठा panel_drv_data *ddata = dev_get_drvdata(&dev->dev);

	dev_dbg(&dev->dev, "%s\n", __func__);

	अगर (!ddata->has_bc)
		वापस -ENODEV;

	अगर (dev->props.fb_blank == FB_BLANK_UNBLANK &&
			dev->props.घातer == FB_BLANK_UNBLANK) अणु
		अगर (ddata->has_bc)
			वापस acx565akm_get_actual_brightness(ddata);
		अन्यथा
			वापस dev->props.brightness;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक acx565akm_bl_update_status_locked(काष्ठा backlight_device *dev)
अणु
	काष्ठा panel_drv_data *ddata = dev_get_drvdata(&dev->dev);
	पूर्णांक r;

	mutex_lock(&ddata->mutex);
	r = acx565akm_bl_update_status(dev);
	mutex_unlock(&ddata->mutex);

	वापस r;
पूर्ण

अटल पूर्णांक acx565akm_bl_get_पूर्णांकensity_locked(काष्ठा backlight_device *dev)
अणु
	काष्ठा panel_drv_data *ddata = dev_get_drvdata(&dev->dev);
	पूर्णांक r;

	mutex_lock(&ddata->mutex);
	r = acx565akm_bl_get_पूर्णांकensity(dev);
	mutex_unlock(&ddata->mutex);

	वापस r;
पूर्ण

अटल स्थिर काष्ठा backlight_ops acx565akm_bl_ops = अणु
	.get_brightness = acx565akm_bl_get_पूर्णांकensity_locked,
	.update_status  = acx565akm_bl_update_status_locked,
पूर्ण;

/*--------------------Auto Brightness control via Sysfs---------------------*/

अटल स्थिर अक्षर * स्थिर cabc_modes[] = अणु
	"off",		/* always used when CABC is not supported */
	"ui",
	"still-image",
	"moving-image",
पूर्ण;

अटल sमाप_प्रकार show_cabc_mode(काष्ठा device *dev,
		काष्ठा device_attribute *attr,
		अक्षर *buf)
अणु
	काष्ठा panel_drv_data *ddata = dev_get_drvdata(dev);
	स्थिर अक्षर *mode_str;
	पूर्णांक mode;
	पूर्णांक len;

	अगर (!ddata->has_cabc)
		mode = 0;
	अन्यथा
		mode = get_cabc_mode(ddata);
	mode_str = "unknown";
	अगर (mode >= 0 && mode < ARRAY_SIZE(cabc_modes))
		mode_str = cabc_modes[mode];
	len = snम_लिखो(buf, PAGE_SIZE, "%s\n", mode_str);

	वापस len < PAGE_SIZE - 1 ? len : PAGE_SIZE - 1;
पूर्ण

अटल sमाप_प्रकार store_cabc_mode(काष्ठा device *dev,
		काष्ठा device_attribute *attr,
		स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा panel_drv_data *ddata = dev_get_drvdata(dev);
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(cabc_modes); i++) अणु
		स्थिर अक्षर *mode_str = cabc_modes[i];
		पूर्णांक cmp_len = म_माप(mode_str);

		अगर (count > 0 && buf[count - 1] == '\n')
			count--;
		अगर (count != cmp_len)
			जारी;

		अगर (म_भेदन(buf, mode_str, cmp_len) == 0)
			अवरोध;
	पूर्ण

	अगर (i == ARRAY_SIZE(cabc_modes))
		वापस -EINVAL;

	अगर (!ddata->has_cabc && i != 0)
		वापस -EINVAL;

	mutex_lock(&ddata->mutex);
	set_cabc_mode(ddata, i);
	mutex_unlock(&ddata->mutex);

	वापस count;
पूर्ण

अटल sमाप_प्रकार show_cabc_available_modes(काष्ठा device *dev,
		काष्ठा device_attribute *attr,
		अक्षर *buf)
अणु
	काष्ठा panel_drv_data *ddata = dev_get_drvdata(dev);
	पूर्णांक len;
	पूर्णांक i;

	अगर (!ddata->has_cabc)
		वापस snम_लिखो(buf, PAGE_SIZE, "%s\n", cabc_modes[0]);

	क्रम (i = 0, len = 0;
	     len < PAGE_SIZE && i < ARRAY_SIZE(cabc_modes); i++)
		len += snम_लिखो(&buf[len], PAGE_SIZE - len, "%s%s%s",
			i ? " " : "", cabc_modes[i],
			i == ARRAY_SIZE(cabc_modes) - 1 ? "\n" : "");

	वापस len < PAGE_SIZE ? len : PAGE_SIZE - 1;
पूर्ण

अटल DEVICE_ATTR(cabc_mode, S_IRUGO | S_IWUSR,
		show_cabc_mode, store_cabc_mode);
अटल DEVICE_ATTR(cabc_available_modes, S_IRUGO,
		show_cabc_available_modes, शून्य);

अटल काष्ठा attribute *bldev_attrs[] = अणु
	&dev_attr_cabc_mode.attr,
	&dev_attr_cabc_available_modes.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group bldev_attr_group = अणु
	.attrs = bldev_attrs,
पूर्ण;

अटल पूर्णांक acx565akm_connect(काष्ठा omap_dss_device *dssdev)
अणु
	काष्ठा panel_drv_data *ddata = to_panel_data(dssdev);
	काष्ठा omap_dss_device *in = ddata->in;

	अगर (omapdss_device_is_connected(dssdev))
		वापस 0;

	वापस in->ops.sdi->connect(in, dssdev);
पूर्ण

अटल व्योम acx565akm_disconnect(काष्ठा omap_dss_device *dssdev)
अणु
	काष्ठा panel_drv_data *ddata = to_panel_data(dssdev);
	काष्ठा omap_dss_device *in = ddata->in;

	अगर (!omapdss_device_is_connected(dssdev))
		वापस;

	in->ops.sdi->disconnect(in, dssdev);
पूर्ण

अटल पूर्णांक acx565akm_panel_घातer_on(काष्ठा omap_dss_device *dssdev)
अणु
	काष्ठा panel_drv_data *ddata = to_panel_data(dssdev);
	काष्ठा omap_dss_device *in = ddata->in;
	पूर्णांक r;

	dev_dbg(&ddata->spi->dev, "%s\n", __func__);

	in->ops.sdi->set_timings(in, &ddata->videomode);

	अगर (ddata->datapairs > 0)
		in->ops.sdi->set_datapairs(in, ddata->datapairs);

	r = in->ops.sdi->enable(in);
	अगर (r) अणु
		pr_err("%s sdi enable failed\n", __func__);
		वापस r;
	पूर्ण

	/*FIXME tweak me */
	msleep(50);

	अगर (gpio_is_valid(ddata->reset_gpio))
		gpio_set_value(ddata->reset_gpio, 1);

	अगर (ddata->enabled) अणु
		dev_dbg(&ddata->spi->dev, "panel already enabled\n");
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

	set_sleep_mode(ddata, 0);
	ddata->enabled = 1;

	/* 5msec between sleep out and the next command. (8.2.16) */
	usleep_range(5000, 10000);
	set_display_state(ddata, 1);
	set_cabc_mode(ddata, ddata->cabc_mode);

	वापस acx565akm_bl_update_status(ddata->bl_dev);
पूर्ण

अटल व्योम acx565akm_panel_घातer_off(काष्ठा omap_dss_device *dssdev)
अणु
	काष्ठा panel_drv_data *ddata = to_panel_data(dssdev);
	काष्ठा omap_dss_device *in = ddata->in;

	dev_dbg(dssdev->dev, "%s\n", __func__);

	अगर (!ddata->enabled)
		वापस;

	set_display_state(ddata, 0);
	set_sleep_mode(ddata, 1);
	ddata->enabled = 0;
	/*
	 * We have to provide PCLK,HS,VS संकेतs क्रम 2 frames (worst हाल
	 * ~50msec) after sending the sleep in command and निश्चितing the
	 * reset संकेत. We probably could निश्चित the reset w/o the delay
	 * but we still delay to aव्योम possible artअगरacts. (7.6.1)
	 */
	msleep(50);

	अगर (gpio_is_valid(ddata->reset_gpio))
		gpio_set_value(ddata->reset_gpio, 0);

	/* FIXME need to tweak this delay */
	msleep(100);

	in->ops.sdi->disable(in);
पूर्ण

अटल पूर्णांक acx565akm_enable(काष्ठा omap_dss_device *dssdev)
अणु
	काष्ठा panel_drv_data *ddata = to_panel_data(dssdev);
	पूर्णांक r;

	dev_dbg(dssdev->dev, "%s\n", __func__);

	अगर (!omapdss_device_is_connected(dssdev))
		वापस -ENODEV;

	अगर (omapdss_device_is_enabled(dssdev))
		वापस 0;

	mutex_lock(&ddata->mutex);
	r = acx565akm_panel_घातer_on(dssdev);
	mutex_unlock(&ddata->mutex);
	अगर (r)
		वापस r;

	dssdev->state = OMAP_DSS_DISPLAY_ACTIVE;

	वापस 0;
पूर्ण

अटल व्योम acx565akm_disable(काष्ठा omap_dss_device *dssdev)
अणु
	काष्ठा panel_drv_data *ddata = to_panel_data(dssdev);

	dev_dbg(dssdev->dev, "%s\n", __func__);

	अगर (!omapdss_device_is_enabled(dssdev))
		वापस;

	mutex_lock(&ddata->mutex);
	acx565akm_panel_घातer_off(dssdev);
	mutex_unlock(&ddata->mutex);

	dssdev->state = OMAP_DSS_DISPLAY_DISABLED;
पूर्ण

अटल व्योम acx565akm_set_timings(काष्ठा omap_dss_device *dssdev,
		काष्ठा omap_video_timings *timings)
अणु
	काष्ठा panel_drv_data *ddata = to_panel_data(dssdev);
	काष्ठा omap_dss_device *in = ddata->in;

	ddata->videomode = *timings;
	dssdev->panel.timings = *timings;

	in->ops.sdi->set_timings(in, timings);
पूर्ण

अटल व्योम acx565akm_get_timings(काष्ठा omap_dss_device *dssdev,
		काष्ठा omap_video_timings *timings)
अणु
	काष्ठा panel_drv_data *ddata = to_panel_data(dssdev);

	*timings = ddata->videomode;
पूर्ण

अटल पूर्णांक acx565akm_check_timings(काष्ठा omap_dss_device *dssdev,
		काष्ठा omap_video_timings *timings)
अणु
	काष्ठा panel_drv_data *ddata = to_panel_data(dssdev);
	काष्ठा omap_dss_device *in = ddata->in;

	वापस in->ops.sdi->check_timings(in, timings);
पूर्ण

अटल काष्ठा omap_dss_driver acx565akm_ops = अणु
	.connect	= acx565akm_connect,
	.disconnect	= acx565akm_disconnect,

	.enable		= acx565akm_enable,
	.disable	= acx565akm_disable,

	.set_timings	= acx565akm_set_timings,
	.get_timings	= acx565akm_get_timings,
	.check_timings	= acx565akm_check_timings,

	.get_resolution	= omapdss_शेष_get_resolution,
पूर्ण;

अटल पूर्णांक acx565akm_probe_pdata(काष्ठा spi_device *spi)
अणु
	स्थिर काष्ठा panel_acx565akm_platक्रमm_data *pdata;
	काष्ठा panel_drv_data *ddata = dev_get_drvdata(&spi->dev);
	काष्ठा omap_dss_device *dssdev, *in;

	pdata = dev_get_platdata(&spi->dev);

	ddata->reset_gpio = pdata->reset_gpio;

	in = omap_dss_find_output(pdata->source);
	अगर (in == शून्य) अणु
		dev_err(&spi->dev, "failed to find video source '%s'\n",
				pdata->source);
		वापस -EPROBE_DEFER;
	पूर्ण
	ddata->in = in;

	ddata->datapairs = pdata->datapairs;

	dssdev = &ddata->dssdev;
	dssdev->name = pdata->name;

	वापस 0;
पूर्ण

अटल पूर्णांक acx565akm_probe_of(काष्ठा spi_device *spi)
अणु
	काष्ठा panel_drv_data *ddata = dev_get_drvdata(&spi->dev);
	काष्ठा device_node *np = spi->dev.of_node;

	ddata->reset_gpio = of_get_named_gpio(np, "reset-gpios", 0);

	ddata->in = omapdss_of_find_source_क्रम_first_ep(np);
	अगर (IS_ERR(ddata->in)) अणु
		dev_err(&spi->dev, "failed to find video source\n");
		वापस PTR_ERR(ddata->in);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक acx565akm_probe(काष्ठा spi_device *spi)
अणु
	काष्ठा panel_drv_data *ddata;
	काष्ठा omap_dss_device *dssdev;
	काष्ठा backlight_device *bldev;
	पूर्णांक max_brightness, brightness;
	काष्ठा backlight_properties props;
	पूर्णांक r;

	dev_dbg(&spi->dev, "%s\n", __func__);

	spi->mode = SPI_MODE_3;

	ddata = devm_kzalloc(&spi->dev, माप(*ddata), GFP_KERNEL);
	अगर (ddata == शून्य)
		वापस -ENOMEM;

	dev_set_drvdata(&spi->dev, ddata);

	ddata->spi = spi;

	mutex_init(&ddata->mutex);

	अगर (dev_get_platdata(&spi->dev)) अणु
		r = acx565akm_probe_pdata(spi);
		अगर (r)
			वापस r;
	पूर्ण अन्यथा अगर (spi->dev.of_node) अणु
		r = acx565akm_probe_of(spi);
		अगर (r)
			वापस r;
	पूर्ण अन्यथा अणु
		dev_err(&spi->dev, "platform data missing!\n");
		वापस -ENODEV;
	पूर्ण

	अगर (gpio_is_valid(ddata->reset_gpio)) अणु
		r = devm_gpio_request_one(&spi->dev, ddata->reset_gpio,
				GPIOF_OUT_INIT_LOW, "lcd reset");
		अगर (r)
			जाओ err_gpio;
	पूर्ण

	अगर (gpio_is_valid(ddata->reset_gpio))
		gpio_set_value(ddata->reset_gpio, 1);

	/*
	 * After reset we have to रुको 5 msec beक्रमe the first
	 * command can be sent.
	 */
	usleep_range(5000, 10000);

	ddata->enabled = panel_enabled(ddata);

	r = panel_detect(ddata);

	अगर (!ddata->enabled && gpio_is_valid(ddata->reset_gpio))
		gpio_set_value(ddata->reset_gpio, 0);

	अगर (r) अणु
		dev_err(&spi->dev, "%s panel detect error\n", __func__);
		जाओ err_detect;
	पूर्ण

	स_रखो(&props, 0, माप(props));
	props.fb_blank = FB_BLANK_UNBLANK;
	props.घातer = FB_BLANK_UNBLANK;
	props.type = BACKLIGHT_RAW;

	bldev = backlight_device_रेजिस्टर("acx565akm", &ddata->spi->dev,
			ddata, &acx565akm_bl_ops, &props);
	अगर (IS_ERR(bldev)) अणु
		r = PTR_ERR(bldev);
		जाओ err_reg_bl;
	पूर्ण
	ddata->bl_dev = bldev;
	अगर (ddata->has_cabc) अणु
		r = sysfs_create_group(&bldev->dev.kobj, &bldev_attr_group);
		अगर (r) अणु
			dev_err(&bldev->dev,
				"%s failed to create sysfs files\n", __func__);
			जाओ err_sysfs;
		पूर्ण
		ddata->cabc_mode = get_hw_cabc_mode(ddata);
	पूर्ण

	max_brightness = 255;

	अगर (ddata->has_bc)
		brightness = acx565akm_get_actual_brightness(ddata);
	अन्यथा
		brightness = 0;

	bldev->props.max_brightness = max_brightness;
	bldev->props.brightness = brightness;

	acx565akm_bl_update_status(bldev);


	ddata->videomode = acx565akm_panel_timings;

	dssdev = &ddata->dssdev;
	dssdev->dev = &spi->dev;
	dssdev->driver = &acx565akm_ops;
	dssdev->type = OMAP_DISPLAY_TYPE_SDI;
	dssdev->owner = THIS_MODULE;
	dssdev->panel.timings = ddata->videomode;

	r = omapdss_रेजिस्टर_display(dssdev);
	अगर (r) अणु
		dev_err(&spi->dev, "Failed to register panel\n");
		जाओ err_reg;
	पूर्ण

	वापस 0;

err_reg:
	sysfs_हटाओ_group(&bldev->dev.kobj, &bldev_attr_group);
err_sysfs:
	backlight_device_unरेजिस्टर(bldev);
err_reg_bl:
err_detect:
err_gpio:
	omap_dss_put_device(ddata->in);
	वापस r;
पूर्ण

अटल पूर्णांक acx565akm_हटाओ(काष्ठा spi_device *spi)
अणु
	काष्ठा panel_drv_data *ddata = dev_get_drvdata(&spi->dev);
	काष्ठा omap_dss_device *dssdev = &ddata->dssdev;
	काष्ठा omap_dss_device *in = ddata->in;

	dev_dbg(&ddata->spi->dev, "%s\n", __func__);

	sysfs_हटाओ_group(&ddata->bl_dev->dev.kobj, &bldev_attr_group);
	backlight_device_unरेजिस्टर(ddata->bl_dev);

	omapdss_unरेजिस्टर_display(dssdev);

	acx565akm_disable(dssdev);
	acx565akm_disconnect(dssdev);

	omap_dss_put_device(in);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id acx565akm_of_match[] = अणु
	अणु .compatible = "omapdss,sony,acx565akm", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, acx565akm_of_match);

अटल काष्ठा spi_driver acx565akm_driver = अणु
	.driver = अणु
		.name	= "acx565akm",
		.of_match_table = acx565akm_of_match,
		.suppress_bind_attrs = true,
	पूर्ण,
	.probe	= acx565akm_probe,
	.हटाओ	= acx565akm_हटाओ,
पूर्ण;

module_spi_driver(acx565akm_driver);

MODULE_AUTHOR("Nokia Corporation");
MODULE_DESCRIPTION("acx565akm LCD Driver");
MODULE_LICENSE("GPL");
