<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Generic DSI Command Mode panel driver
 *
 * Copyright (C) 2013 Texas Instruments
 * Author: Tomi Valkeinen <tomi.valkeinen@ti.com>
 */

/* #घोषणा DEBUG */

#समावेश <linux/backlight.h>
#समावेश <linux/delay.h>
#समावेश <linux/fb.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/slab.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_gpपन.स>

#समावेश <video/omapfb_dss.h>
#समावेश <video/mipi_display.h>

/* DSI Virtual channel. Hardcoded क्रम now. */
#घोषणा TCH 0

#घोषणा DCS_READ_NUM_ERRORS	0x05
#घोषणा DCS_BRIGHTNESS		0x51
#घोषणा DCS_CTRL_DISPLAY	0x53
#घोषणा DCS_GET_ID1		0xda
#घोषणा DCS_GET_ID2		0xdb
#घोषणा DCS_GET_ID3		0xdc

काष्ठा panel_drv_data अणु
	काष्ठा omap_dss_device dssdev;
	काष्ठा omap_dss_device *in;

	काष्ठा omap_video_timings timings;

	काष्ठा platक्रमm_device *pdev;

	काष्ठा mutex lock;

	काष्ठा backlight_device *bldev;

	अचिन्हित दीर्घ	hw_guard_end;	/* next value of jअगरfies when we can
					 * issue the next sleep in/out command
					 */
	अचिन्हित दीर्घ	hw_guard_रुको;	/* max guard समय in jअगरfies */

	/* panel HW configuration from DT or platक्रमm data */
	पूर्णांक reset_gpio;
	पूर्णांक ext_te_gpio;

	bool use_dsi_backlight;

	काष्ठा omap_dsi_pin_config pin_config;

	/* runसमय variables */
	bool enabled;

	bool te_enabled;

	atomic_t करो_update;
	पूर्णांक channel;

	काष्ठा delayed_work te_समयout_work;

	bool पूर्णांकro_prपूर्णांकed;

	bool ulps_enabled;
	अचिन्हित ulps_समयout;
	काष्ठा delayed_work ulps_work;
पूर्ण;

#घोषणा to_panel_data(p) container_of(p, काष्ठा panel_drv_data, dssdev)

अटल irqवापस_t dsicm_te_isr(पूर्णांक irq, व्योम *data);
अटल व्योम dsicm_te_समयout_work_callback(काष्ठा work_काष्ठा *work);
अटल पूर्णांक _dsicm_enable_te(काष्ठा panel_drv_data *ddata, bool enable);

अटल पूर्णांक dsicm_panel_reset(काष्ठा panel_drv_data *ddata);

अटल व्योम dsicm_ulps_work(काष्ठा work_काष्ठा *work);

अटल व्योम hw_guard_start(काष्ठा panel_drv_data *ddata, पूर्णांक guard_msec)
अणु
	ddata->hw_guard_रुको = msecs_to_jअगरfies(guard_msec);
	ddata->hw_guard_end = jअगरfies + ddata->hw_guard_रुको;
पूर्ण

अटल व्योम hw_guard_रुको(काष्ठा panel_drv_data *ddata)
अणु
	अचिन्हित दीर्घ रुको = ddata->hw_guard_end - jअगरfies;

	अगर ((दीर्घ)रुको > 0 && समय_beक्रमe_eq(रुको, ddata->hw_guard_रुको)) अणु
		set_current_state(TASK_UNINTERRUPTIBLE);
		schedule_समयout(रुको);
	पूर्ण
पूर्ण

अटल पूर्णांक dsicm_dcs_पढ़ो_1(काष्ठा panel_drv_data *ddata, u8 dcs_cmd, u8 *data)
अणु
	काष्ठा omap_dss_device *in = ddata->in;
	पूर्णांक r;
	u8 buf[1];

	r = in->ops.dsi->dcs_पढ़ो(in, ddata->channel, dcs_cmd, buf, 1);

	अगर (r < 0)
		वापस r;

	*data = buf[0];

	वापस 0;
पूर्ण

अटल पूर्णांक dsicm_dcs_ग_लिखो_0(काष्ठा panel_drv_data *ddata, u8 dcs_cmd)
अणु
	काष्ठा omap_dss_device *in = ddata->in;
	वापस in->ops.dsi->dcs_ग_लिखो(in, ddata->channel, &dcs_cmd, 1);
पूर्ण

अटल पूर्णांक dsicm_dcs_ग_लिखो_1(काष्ठा panel_drv_data *ddata, u8 dcs_cmd, u8 param)
अणु
	काष्ठा omap_dss_device *in = ddata->in;
	u8 buf[2] = अणु dcs_cmd, param पूर्ण;

	वापस in->ops.dsi->dcs_ग_लिखो(in, ddata->channel, buf, 2);
पूर्ण

अटल पूर्णांक dsicm_sleep_in(काष्ठा panel_drv_data *ddata)

अणु
	काष्ठा omap_dss_device *in = ddata->in;
	u8 cmd;
	पूर्णांक r;

	hw_guard_रुको(ddata);

	cmd = MIPI_DCS_ENTER_SLEEP_MODE;
	r = in->ops.dsi->dcs_ग_लिखो_nosync(in, ddata->channel, &cmd, 1);
	अगर (r)
		वापस r;

	hw_guard_start(ddata, 120);

	usleep_range(5000, 10000);

	वापस 0;
पूर्ण

अटल पूर्णांक dsicm_sleep_out(काष्ठा panel_drv_data *ddata)
अणु
	पूर्णांक r;

	hw_guard_रुको(ddata);

	r = dsicm_dcs_ग_लिखो_0(ddata, MIPI_DCS_EXIT_SLEEP_MODE);
	अगर (r)
		वापस r;

	hw_guard_start(ddata, 120);

	usleep_range(5000, 10000);

	वापस 0;
पूर्ण

अटल पूर्णांक dsicm_get_id(काष्ठा panel_drv_data *ddata, u8 *id1, u8 *id2, u8 *id3)
अणु
	पूर्णांक r;

	r = dsicm_dcs_पढ़ो_1(ddata, DCS_GET_ID1, id1);
	अगर (r)
		वापस r;
	r = dsicm_dcs_पढ़ो_1(ddata, DCS_GET_ID2, id2);
	अगर (r)
		वापस r;
	r = dsicm_dcs_पढ़ो_1(ddata, DCS_GET_ID3, id3);
	अगर (r)
		वापस r;

	वापस 0;
पूर्ण

अटल पूर्णांक dsicm_set_update_winकरोw(काष्ठा panel_drv_data *ddata,
		u16 x, u16 y, u16 w, u16 h)
अणु
	काष्ठा omap_dss_device *in = ddata->in;
	पूर्णांक r;
	u16 x1 = x;
	u16 x2 = x + w - 1;
	u16 y1 = y;
	u16 y2 = y + h - 1;

	u8 buf[5];
	buf[0] = MIPI_DCS_SET_COLUMN_ADDRESS;
	buf[1] = (x1 >> 8) & 0xff;
	buf[2] = (x1 >> 0) & 0xff;
	buf[3] = (x2 >> 8) & 0xff;
	buf[4] = (x2 >> 0) & 0xff;

	r = in->ops.dsi->dcs_ग_लिखो_nosync(in, ddata->channel, buf, माप(buf));
	अगर (r)
		वापस r;

	buf[0] = MIPI_DCS_SET_PAGE_ADDRESS;
	buf[1] = (y1 >> 8) & 0xff;
	buf[2] = (y1 >> 0) & 0xff;
	buf[3] = (y2 >> 8) & 0xff;
	buf[4] = (y2 >> 0) & 0xff;

	r = in->ops.dsi->dcs_ग_लिखो_nosync(in, ddata->channel, buf, माप(buf));
	अगर (r)
		वापस r;

	in->ops.dsi->bta_sync(in, ddata->channel);

	वापस r;
पूर्ण

अटल व्योम dsicm_queue_ulps_work(काष्ठा panel_drv_data *ddata)
अणु
	अगर (ddata->ulps_समयout > 0)
		schedule_delayed_work(&ddata->ulps_work,
				msecs_to_jअगरfies(ddata->ulps_समयout));
पूर्ण

अटल व्योम dsicm_cancel_ulps_work(काष्ठा panel_drv_data *ddata)
अणु
	cancel_delayed_work(&ddata->ulps_work);
पूर्ण

अटल पूर्णांक dsicm_enter_ulps(काष्ठा panel_drv_data *ddata)
अणु
	काष्ठा omap_dss_device *in = ddata->in;
	पूर्णांक r;

	अगर (ddata->ulps_enabled)
		वापस 0;

	dsicm_cancel_ulps_work(ddata);

	r = _dsicm_enable_te(ddata, false);
	अगर (r)
		जाओ err;

	अगर (gpio_is_valid(ddata->ext_te_gpio))
		disable_irq(gpio_to_irq(ddata->ext_te_gpio));

	in->ops.dsi->disable(in, false, true);

	ddata->ulps_enabled = true;

	वापस 0;

err:
	dev_err(&ddata->pdev->dev, "enter ULPS failed");
	dsicm_panel_reset(ddata);

	ddata->ulps_enabled = false;

	dsicm_queue_ulps_work(ddata);

	वापस r;
पूर्ण

अटल पूर्णांक dsicm_निकास_ulps(काष्ठा panel_drv_data *ddata)
अणु
	काष्ठा omap_dss_device *in = ddata->in;
	पूर्णांक r;

	अगर (!ddata->ulps_enabled)
		वापस 0;

	r = in->ops.dsi->enable(in);
	अगर (r) अणु
		dev_err(&ddata->pdev->dev, "failed to enable DSI\n");
		जाओ err1;
	पूर्ण

	in->ops.dsi->enable_hs(in, ddata->channel, true);

	r = _dsicm_enable_te(ddata, true);
	अगर (r) अणु
		dev_err(&ddata->pdev->dev, "failed to re-enable TE");
		जाओ err2;
	पूर्ण

	अगर (gpio_is_valid(ddata->ext_te_gpio))
		enable_irq(gpio_to_irq(ddata->ext_te_gpio));

	dsicm_queue_ulps_work(ddata);

	ddata->ulps_enabled = false;

	वापस 0;

err2:
	dev_err(&ddata->pdev->dev, "failed to exit ULPS");

	r = dsicm_panel_reset(ddata);
	अगर (!r) अणु
		अगर (gpio_is_valid(ddata->ext_te_gpio))
			enable_irq(gpio_to_irq(ddata->ext_te_gpio));
		ddata->ulps_enabled = false;
	पूर्ण
err1:
	dsicm_queue_ulps_work(ddata);

	वापस r;
पूर्ण

अटल पूर्णांक dsicm_wake_up(काष्ठा panel_drv_data *ddata)
अणु
	अगर (ddata->ulps_enabled)
		वापस dsicm_निकास_ulps(ddata);

	dsicm_cancel_ulps_work(ddata);
	dsicm_queue_ulps_work(ddata);
	वापस 0;
पूर्ण

अटल पूर्णांक dsicm_bl_update_status(काष्ठा backlight_device *dev)
अणु
	काष्ठा panel_drv_data *ddata = dev_get_drvdata(&dev->dev);
	काष्ठा omap_dss_device *in = ddata->in;
	पूर्णांक r;
	पूर्णांक level;

	अगर (dev->props.fb_blank == FB_BLANK_UNBLANK &&
			dev->props.घातer == FB_BLANK_UNBLANK)
		level = dev->props.brightness;
	अन्यथा
		level = 0;

	dev_dbg(&ddata->pdev->dev, "update brightness to %d\n", level);

	mutex_lock(&ddata->lock);

	अगर (ddata->enabled) अणु
		in->ops.dsi->bus_lock(in);

		r = dsicm_wake_up(ddata);
		अगर (!r)
			r = dsicm_dcs_ग_लिखो_1(ddata, DCS_BRIGHTNESS, level);

		in->ops.dsi->bus_unlock(in);
	पूर्ण अन्यथा अणु
		r = 0;
	पूर्ण

	mutex_unlock(&ddata->lock);

	वापस r;
पूर्ण

अटल पूर्णांक dsicm_bl_get_पूर्णांकensity(काष्ठा backlight_device *dev)
अणु
	अगर (dev->props.fb_blank == FB_BLANK_UNBLANK &&
			dev->props.घातer == FB_BLANK_UNBLANK)
		वापस dev->props.brightness;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा backlight_ops dsicm_bl_ops = अणु
	.get_brightness = dsicm_bl_get_पूर्णांकensity,
	.update_status  = dsicm_bl_update_status,
पूर्ण;

अटल व्योम dsicm_get_resolution(काष्ठा omap_dss_device *dssdev,
		u16 *xres, u16 *yres)
अणु
	*xres = dssdev->panel.timings.x_res;
	*yres = dssdev->panel.timings.y_res;
पूर्ण

अटल sमाप_प्रकार dsicm_num_errors_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा panel_drv_data *ddata = dev_get_drvdata(dev);
	काष्ठा omap_dss_device *in = ddata->in;
	u8 errors = 0;
	पूर्णांक r;

	mutex_lock(&ddata->lock);

	अगर (ddata->enabled) अणु
		in->ops.dsi->bus_lock(in);

		r = dsicm_wake_up(ddata);
		अगर (!r)
			r = dsicm_dcs_पढ़ो_1(ddata, DCS_READ_NUM_ERRORS,
					&errors);

		in->ops.dsi->bus_unlock(in);
	पूर्ण अन्यथा अणु
		r = -ENODEV;
	पूर्ण

	mutex_unlock(&ddata->lock);

	अगर (r)
		वापस r;

	वापस snम_लिखो(buf, PAGE_SIZE, "%d\n", errors);
पूर्ण

अटल sमाप_प्रकार dsicm_hw_revision_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा panel_drv_data *ddata = dev_get_drvdata(dev);
	काष्ठा omap_dss_device *in = ddata->in;
	u8 id1, id2, id3;
	पूर्णांक r;

	mutex_lock(&ddata->lock);

	अगर (ddata->enabled) अणु
		in->ops.dsi->bus_lock(in);

		r = dsicm_wake_up(ddata);
		अगर (!r)
			r = dsicm_get_id(ddata, &id1, &id2, &id3);

		in->ops.dsi->bus_unlock(in);
	पूर्ण अन्यथा अणु
		r = -ENODEV;
	पूर्ण

	mutex_unlock(&ddata->lock);

	अगर (r)
		वापस r;

	वापस snम_लिखो(buf, PAGE_SIZE, "%02x.%02x.%02x\n", id1, id2, id3);
पूर्ण

अटल sमाप_प्रकार dsicm_store_ulps(काष्ठा device *dev,
		काष्ठा device_attribute *attr,
		स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा panel_drv_data *ddata = dev_get_drvdata(dev);
	काष्ठा omap_dss_device *in = ddata->in;
	अचिन्हित दीर्घ t;
	पूर्णांक r;

	r = kम_से_अदीर्घ(buf, 0, &t);
	अगर (r)
		वापस r;

	mutex_lock(&ddata->lock);

	अगर (ddata->enabled) अणु
		in->ops.dsi->bus_lock(in);

		अगर (t)
			r = dsicm_enter_ulps(ddata);
		अन्यथा
			r = dsicm_wake_up(ddata);

		in->ops.dsi->bus_unlock(in);
	पूर्ण

	mutex_unlock(&ddata->lock);

	अगर (r)
		वापस r;

	वापस count;
पूर्ण

अटल sमाप_प्रकार dsicm_show_ulps(काष्ठा device *dev,
		काष्ठा device_attribute *attr,
		अक्षर *buf)
अणु
	काष्ठा panel_drv_data *ddata = dev_get_drvdata(dev);
	अचिन्हित t;

	mutex_lock(&ddata->lock);
	t = ddata->ulps_enabled;
	mutex_unlock(&ddata->lock);

	वापस snम_लिखो(buf, PAGE_SIZE, "%u\n", t);
पूर्ण

अटल sमाप_प्रकार dsicm_store_ulps_समयout(काष्ठा device *dev,
		काष्ठा device_attribute *attr,
		स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा panel_drv_data *ddata = dev_get_drvdata(dev);
	काष्ठा omap_dss_device *in = ddata->in;
	अचिन्हित दीर्घ t;
	पूर्णांक r;

	r = kम_से_अदीर्घ(buf, 0, &t);
	अगर (r)
		वापस r;

	mutex_lock(&ddata->lock);
	ddata->ulps_समयout = t;

	अगर (ddata->enabled) अणु
		/* dsicm_wake_up will restart the समयr */
		in->ops.dsi->bus_lock(in);
		r = dsicm_wake_up(ddata);
		in->ops.dsi->bus_unlock(in);
	पूर्ण

	mutex_unlock(&ddata->lock);

	अगर (r)
		वापस r;

	वापस count;
पूर्ण

अटल sमाप_प्रकार dsicm_show_ulps_समयout(काष्ठा device *dev,
		काष्ठा device_attribute *attr,
		अक्षर *buf)
अणु
	काष्ठा panel_drv_data *ddata = dev_get_drvdata(dev);
	अचिन्हित t;

	mutex_lock(&ddata->lock);
	t = ddata->ulps_समयout;
	mutex_unlock(&ddata->lock);

	वापस snम_लिखो(buf, PAGE_SIZE, "%u\n", t);
पूर्ण

अटल DEVICE_ATTR(num_dsi_errors, S_IRUGO, dsicm_num_errors_show, शून्य);
अटल DEVICE_ATTR(hw_revision, S_IRUGO, dsicm_hw_revision_show, शून्य);
अटल DEVICE_ATTR(ulps, S_IRUGO | S_IWUSR,
		dsicm_show_ulps, dsicm_store_ulps);
अटल DEVICE_ATTR(ulps_समयout, S_IRUGO | S_IWUSR,
		dsicm_show_ulps_समयout, dsicm_store_ulps_समयout);

अटल काष्ठा attribute *dsicm_attrs[] = अणु
	&dev_attr_num_dsi_errors.attr,
	&dev_attr_hw_revision.attr,
	&dev_attr_ulps.attr,
	&dev_attr_ulps_समयout.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group dsicm_attr_group = अणु
	.attrs = dsicm_attrs,
पूर्ण;

अटल व्योम dsicm_hw_reset(काष्ठा panel_drv_data *ddata)
अणु
	अगर (!gpio_is_valid(ddata->reset_gpio))
		वापस;

	gpio_set_value(ddata->reset_gpio, 1);
	udelay(10);
	/* reset the panel */
	gpio_set_value(ddata->reset_gpio, 0);
	/* निश्चित reset */
	udelay(10);
	gpio_set_value(ddata->reset_gpio, 1);
	/* रुको after releasing reset */
	usleep_range(5000, 10000);
पूर्ण

अटल पूर्णांक dsicm_घातer_on(काष्ठा panel_drv_data *ddata)
अणु
	काष्ठा omap_dss_device *in = ddata->in;
	u8 id1, id2, id3;
	पूर्णांक r;
	काष्ठा omap_dss_dsi_config dsi_config = अणु
		.mode = OMAP_DSS_DSI_CMD_MODE,
		.pixel_क्रमmat = OMAP_DSS_DSI_FMT_RGB888,
		.timings = &ddata->timings,
		.hs_clk_min = 150000000,
		.hs_clk_max = 300000000,
		.lp_clk_min = 7000000,
		.lp_clk_max = 10000000,
	पूर्ण;

	अगर (ddata->pin_config.num_pins > 0) अणु
		r = in->ops.dsi->configure_pins(in, &ddata->pin_config);
		अगर (r) अणु
			dev_err(&ddata->pdev->dev,
				"failed to configure DSI pins\n");
			जाओ err0;
		पूर्ण
	पूर्ण

	r = in->ops.dsi->set_config(in, &dsi_config);
	अगर (r) अणु
		dev_err(&ddata->pdev->dev, "failed to configure DSI\n");
		जाओ err0;
	पूर्ण

	r = in->ops.dsi->enable(in);
	अगर (r) अणु
		dev_err(&ddata->pdev->dev, "failed to enable DSI\n");
		जाओ err0;
	पूर्ण

	dsicm_hw_reset(ddata);

	in->ops.dsi->enable_hs(in, ddata->channel, false);

	r = dsicm_sleep_out(ddata);
	अगर (r)
		जाओ err;

	r = dsicm_get_id(ddata, &id1, &id2, &id3);
	अगर (r)
		जाओ err;

	r = dsicm_dcs_ग_लिखो_1(ddata, DCS_BRIGHTNESS, 0xff);
	अगर (r)
		जाओ err;

	r = dsicm_dcs_ग_लिखो_1(ddata, DCS_CTRL_DISPLAY,
			(1<<2) | (1<<5));	/* BL | BCTRL */
	अगर (r)
		जाओ err;

	r = dsicm_dcs_ग_लिखो_1(ddata, MIPI_DCS_SET_PIXEL_FORMAT,
		MIPI_DCS_PIXEL_FMT_24BIT);
	अगर (r)
		जाओ err;

	r = dsicm_dcs_ग_लिखो_0(ddata, MIPI_DCS_SET_DISPLAY_ON);
	अगर (r)
		जाओ err;

	r = _dsicm_enable_te(ddata, ddata->te_enabled);
	अगर (r)
		जाओ err;

	r = in->ops.dsi->enable_video_output(in, ddata->channel);
	अगर (r)
		जाओ err;

	ddata->enabled = 1;

	अगर (!ddata->पूर्णांकro_prपूर्णांकed) अणु
		dev_info(&ddata->pdev->dev, "panel revision %02x.%02x.%02x\n",
			id1, id2, id3);
		ddata->पूर्णांकro_prपूर्णांकed = true;
	पूर्ण

	in->ops.dsi->enable_hs(in, ddata->channel, true);

	वापस 0;
err:
	dev_err(&ddata->pdev->dev, "error while enabling panel, issuing HW reset\n");

	dsicm_hw_reset(ddata);

	in->ops.dsi->disable(in, true, false);
err0:
	वापस r;
पूर्ण

अटल व्योम dsicm_घातer_off(काष्ठा panel_drv_data *ddata)
अणु
	काष्ठा omap_dss_device *in = ddata->in;
	पूर्णांक r;

	in->ops.dsi->disable_video_output(in, ddata->channel);

	r = dsicm_dcs_ग_लिखो_0(ddata, MIPI_DCS_SET_DISPLAY_OFF);
	अगर (!r)
		r = dsicm_sleep_in(ddata);

	अगर (r) अणु
		dev_err(&ddata->pdev->dev,
				"error disabling panel, issuing HW reset\n");
		dsicm_hw_reset(ddata);
	पूर्ण

	in->ops.dsi->disable(in, true, false);

	ddata->enabled = 0;
पूर्ण

अटल पूर्णांक dsicm_panel_reset(काष्ठा panel_drv_data *ddata)
अणु
	dev_err(&ddata->pdev->dev, "performing LCD reset\n");

	dsicm_घातer_off(ddata);
	dsicm_hw_reset(ddata);
	वापस dsicm_घातer_on(ddata);
पूर्ण

अटल पूर्णांक dsicm_connect(काष्ठा omap_dss_device *dssdev)
अणु
	काष्ठा panel_drv_data *ddata = to_panel_data(dssdev);
	काष्ठा omap_dss_device *in = ddata->in;
	काष्ठा device *dev = &ddata->pdev->dev;
	पूर्णांक r;

	अगर (omapdss_device_is_connected(dssdev))
		वापस 0;

	r = in->ops.dsi->connect(in, dssdev);
	अगर (r) अणु
		dev_err(dev, "Failed to connect to video source\n");
		वापस r;
	पूर्ण

	r = in->ops.dsi->request_vc(ddata->in, &ddata->channel);
	अगर (r) अणु
		dev_err(dev, "failed to get virtual channel\n");
		जाओ err_req_vc;
	पूर्ण

	r = in->ops.dsi->set_vc_id(ddata->in, ddata->channel, TCH);
	अगर (r) अणु
		dev_err(dev, "failed to set VC_ID\n");
		जाओ err_vc_id;
	पूर्ण

	वापस 0;

err_vc_id:
	in->ops.dsi->release_vc(ddata->in, ddata->channel);
err_req_vc:
	in->ops.dsi->disconnect(in, dssdev);
	वापस r;
पूर्ण

अटल व्योम dsicm_disconnect(काष्ठा omap_dss_device *dssdev)
अणु
	काष्ठा panel_drv_data *ddata = to_panel_data(dssdev);
	काष्ठा omap_dss_device *in = ddata->in;

	अगर (!omapdss_device_is_connected(dssdev))
		वापस;

	in->ops.dsi->release_vc(in, ddata->channel);
	in->ops.dsi->disconnect(in, dssdev);
पूर्ण

अटल पूर्णांक dsicm_enable(काष्ठा omap_dss_device *dssdev)
अणु
	काष्ठा panel_drv_data *ddata = to_panel_data(dssdev);
	काष्ठा omap_dss_device *in = ddata->in;
	पूर्णांक r;

	dev_dbg(&ddata->pdev->dev, "enable\n");

	mutex_lock(&ddata->lock);

	अगर (!omapdss_device_is_connected(dssdev)) अणु
		r = -ENODEV;
		जाओ err;
	पूर्ण

	अगर (omapdss_device_is_enabled(dssdev)) अणु
		r = 0;
		जाओ err;
	पूर्ण

	in->ops.dsi->bus_lock(in);

	r = dsicm_घातer_on(ddata);

	in->ops.dsi->bus_unlock(in);

	अगर (r)
		जाओ err;

	dssdev->state = OMAP_DSS_DISPLAY_ACTIVE;

	mutex_unlock(&ddata->lock);

	वापस 0;
err:
	dev_dbg(&ddata->pdev->dev, "enable failed\n");
	mutex_unlock(&ddata->lock);
	वापस r;
पूर्ण

अटल व्योम dsicm_disable(काष्ठा omap_dss_device *dssdev)
अणु
	काष्ठा panel_drv_data *ddata = to_panel_data(dssdev);
	काष्ठा omap_dss_device *in = ddata->in;
	पूर्णांक r;

	dev_dbg(&ddata->pdev->dev, "disable\n");

	mutex_lock(&ddata->lock);

	dsicm_cancel_ulps_work(ddata);

	in->ops.dsi->bus_lock(in);

	अगर (omapdss_device_is_enabled(dssdev)) अणु
		r = dsicm_wake_up(ddata);
		अगर (!r)
			dsicm_घातer_off(ddata);
	पूर्ण

	in->ops.dsi->bus_unlock(in);

	dssdev->state = OMAP_DSS_DISPLAY_DISABLED;

	mutex_unlock(&ddata->lock);
पूर्ण

अटल व्योम dsicm_frameकरोne_cb(पूर्णांक err, व्योम *data)
अणु
	काष्ठा panel_drv_data *ddata = data;
	काष्ठा omap_dss_device *in = ddata->in;

	dev_dbg(&ddata->pdev->dev, "framedone, err %d\n", err);
	in->ops.dsi->bus_unlock(ddata->in);
पूर्ण

अटल irqवापस_t dsicm_te_isr(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा panel_drv_data *ddata = data;
	काष्ठा omap_dss_device *in = ddata->in;
	पूर्णांक old;
	पूर्णांक r;

	old = atomic_cmpxchg(&ddata->करो_update, 1, 0);

	अगर (old) अणु
		cancel_delayed_work(&ddata->te_समयout_work);

		r = in->ops.dsi->update(in, ddata->channel, dsicm_frameकरोne_cb,
				ddata);
		अगर (r)
			जाओ err;
	पूर्ण

	वापस IRQ_HANDLED;
err:
	dev_err(&ddata->pdev->dev, "start update failed\n");
	in->ops.dsi->bus_unlock(in);
	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम dsicm_te_समयout_work_callback(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा panel_drv_data *ddata = container_of(work, काष्ठा panel_drv_data,
					te_समयout_work.work);
	काष्ठा omap_dss_device *in = ddata->in;

	dev_err(&ddata->pdev->dev, "TE not received for 250ms!\n");

	atomic_set(&ddata->करो_update, 0);
	in->ops.dsi->bus_unlock(in);
पूर्ण

अटल पूर्णांक dsicm_update(काष्ठा omap_dss_device *dssdev,
				    u16 x, u16 y, u16 w, u16 h)
अणु
	काष्ठा panel_drv_data *ddata = to_panel_data(dssdev);
	काष्ठा omap_dss_device *in = ddata->in;
	पूर्णांक r;

	dev_dbg(&ddata->pdev->dev, "update %d, %d, %d x %d\n", x, y, w, h);

	mutex_lock(&ddata->lock);
	in->ops.dsi->bus_lock(in);

	r = dsicm_wake_up(ddata);
	अगर (r)
		जाओ err;

	अगर (!ddata->enabled) अणु
		r = 0;
		जाओ err;
	पूर्ण

	/* XXX no need to send this every frame, but dsi अवरोध अगर not करोne */
	r = dsicm_set_update_winकरोw(ddata, 0, 0,
			dssdev->panel.timings.x_res,
			dssdev->panel.timings.y_res);
	अगर (r)
		जाओ err;

	अगर (ddata->te_enabled && gpio_is_valid(ddata->ext_te_gpio)) अणु
		schedule_delayed_work(&ddata->te_समयout_work,
				msecs_to_jअगरfies(250));
		atomic_set(&ddata->करो_update, 1);
	पूर्ण अन्यथा अणु
		r = in->ops.dsi->update(in, ddata->channel, dsicm_frameकरोne_cb,
				ddata);
		अगर (r)
			जाओ err;
	पूर्ण

	/* note: no bus_unlock here. unlock is in frameकरोne_cb */
	mutex_unlock(&ddata->lock);
	वापस 0;
err:
	in->ops.dsi->bus_unlock(in);
	mutex_unlock(&ddata->lock);
	वापस r;
पूर्ण

अटल पूर्णांक dsicm_sync(काष्ठा omap_dss_device *dssdev)
अणु
	काष्ठा panel_drv_data *ddata = to_panel_data(dssdev);
	काष्ठा omap_dss_device *in = ddata->in;

	dev_dbg(&ddata->pdev->dev, "sync\n");

	mutex_lock(&ddata->lock);
	in->ops.dsi->bus_lock(in);
	in->ops.dsi->bus_unlock(in);
	mutex_unlock(&ddata->lock);

	dev_dbg(&ddata->pdev->dev, "sync done\n");

	वापस 0;
पूर्ण

अटल पूर्णांक _dsicm_enable_te(काष्ठा panel_drv_data *ddata, bool enable)
अणु
	काष्ठा omap_dss_device *in = ddata->in;
	पूर्णांक r;

	अगर (enable)
		r = dsicm_dcs_ग_लिखो_1(ddata, MIPI_DCS_SET_TEAR_ON, 0);
	अन्यथा
		r = dsicm_dcs_ग_लिखो_0(ddata, MIPI_DCS_SET_TEAR_OFF);

	अगर (!gpio_is_valid(ddata->ext_te_gpio))
		in->ops.dsi->enable_te(in, enable);

	/* possible panel bug */
	msleep(100);

	वापस r;
पूर्ण

अटल पूर्णांक dsicm_enable_te(काष्ठा omap_dss_device *dssdev, bool enable)
अणु
	काष्ठा panel_drv_data *ddata = to_panel_data(dssdev);
	काष्ठा omap_dss_device *in = ddata->in;
	पूर्णांक r;

	mutex_lock(&ddata->lock);

	अगर (ddata->te_enabled == enable)
		जाओ end;

	in->ops.dsi->bus_lock(in);

	अगर (ddata->enabled) अणु
		r = dsicm_wake_up(ddata);
		अगर (r)
			जाओ err;

		r = _dsicm_enable_te(ddata, enable);
		अगर (r)
			जाओ err;
	पूर्ण

	ddata->te_enabled = enable;

	in->ops.dsi->bus_unlock(in);
end:
	mutex_unlock(&ddata->lock);

	वापस 0;
err:
	in->ops.dsi->bus_unlock(in);
	mutex_unlock(&ddata->lock);

	वापस r;
पूर्ण

अटल पूर्णांक dsicm_get_te(काष्ठा omap_dss_device *dssdev)
अणु
	काष्ठा panel_drv_data *ddata = to_panel_data(dssdev);
	पूर्णांक r;

	mutex_lock(&ddata->lock);
	r = ddata->te_enabled;
	mutex_unlock(&ddata->lock);

	वापस r;
पूर्ण

अटल पूर्णांक dsicm_memory_पढ़ो(काष्ठा omap_dss_device *dssdev,
		व्योम *buf, माप_प्रकार size,
		u16 x, u16 y, u16 w, u16 h)
अणु
	काष्ठा panel_drv_data *ddata = to_panel_data(dssdev);
	काष्ठा omap_dss_device *in = ddata->in;
	पूर्णांक r;
	पूर्णांक first = 1;
	पूर्णांक plen;
	अचिन्हित buf_used = 0;

	अगर (size < w * h * 3)
		वापस -ENOMEM;

	mutex_lock(&ddata->lock);

	अगर (!ddata->enabled) अणु
		r = -ENODEV;
		जाओ err1;
	पूर्ण

	size = min(w * h * 3,
			dssdev->panel.timings.x_res *
			dssdev->panel.timings.y_res * 3);

	in->ops.dsi->bus_lock(in);

	r = dsicm_wake_up(ddata);
	अगर (r)
		जाओ err2;

	/* plen 1 or 2 goes पूर्णांकo लघु packet. until checksum error is fixed,
	 * use लघु packets. plen 32 works, but bigger packets seem to cause
	 * an error. */
	अगर (size % 2)
		plen = 1;
	अन्यथा
		plen = 2;

	dsicm_set_update_winकरोw(ddata, x, y, w, h);

	r = in->ops.dsi->set_max_rx_packet_size(in, ddata->channel, plen);
	अगर (r)
		जाओ err2;

	जबतक (buf_used < size) अणु
		u8 dcs_cmd = first ? 0x2e : 0x3e;
		first = 0;

		r = in->ops.dsi->dcs_पढ़ो(in, ddata->channel, dcs_cmd,
				buf + buf_used, size - buf_used);

		अगर (r < 0) अणु
			dev_err(dssdev->dev, "read error\n");
			जाओ err3;
		पूर्ण

		buf_used += r;

		अगर (r < plen) अणु
			dev_err(&ddata->pdev->dev, "short read\n");
			अवरोध;
		पूर्ण

		अगर (संकेत_pending(current)) अणु
			dev_err(&ddata->pdev->dev, "signal pending, "
					"aborting memory read\n");
			r = -ERESTARTSYS;
			जाओ err3;
		पूर्ण
	पूर्ण

	r = buf_used;

err3:
	in->ops.dsi->set_max_rx_packet_size(in, ddata->channel, 1);
err2:
	in->ops.dsi->bus_unlock(in);
err1:
	mutex_unlock(&ddata->lock);
	वापस r;
पूर्ण

अटल व्योम dsicm_ulps_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा panel_drv_data *ddata = container_of(work, काष्ठा panel_drv_data,
			ulps_work.work);
	काष्ठा omap_dss_device *dssdev = &ddata->dssdev;
	काष्ठा omap_dss_device *in = ddata->in;

	mutex_lock(&ddata->lock);

	अगर (dssdev->state != OMAP_DSS_DISPLAY_ACTIVE || !ddata->enabled) अणु
		mutex_unlock(&ddata->lock);
		वापस;
	पूर्ण

	in->ops.dsi->bus_lock(in);

	dsicm_enter_ulps(ddata);

	in->ops.dsi->bus_unlock(in);
	mutex_unlock(&ddata->lock);
पूर्ण

अटल काष्ठा omap_dss_driver dsicm_ops = अणु
	.connect	= dsicm_connect,
	.disconnect	= dsicm_disconnect,

	.enable		= dsicm_enable,
	.disable	= dsicm_disable,

	.update		= dsicm_update,
	.sync		= dsicm_sync,

	.get_resolution	= dsicm_get_resolution,
	.get_recommended_bpp = omapdss_शेष_get_recommended_bpp,

	.enable_te	= dsicm_enable_te,
	.get_te		= dsicm_get_te,

	.memory_पढ़ो	= dsicm_memory_पढ़ो,
पूर्ण;

अटल पूर्णांक dsicm_probe_of(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *node = pdev->dev.of_node;
	काष्ठा panel_drv_data *ddata = platक्रमm_get_drvdata(pdev);
	काष्ठा omap_dss_device *in;
	पूर्णांक gpio;

	gpio = of_get_named_gpio(node, "reset-gpios", 0);
	अगर (!gpio_is_valid(gpio)) अणु
		dev_err(&pdev->dev, "failed to parse reset gpio\n");
		वापस gpio;
	पूर्ण
	ddata->reset_gpio = gpio;

	gpio = of_get_named_gpio(node, "te-gpios", 0);
	अगर (gpio_is_valid(gpio) || gpio == -ENOENT) अणु
		ddata->ext_te_gpio = gpio;
	पूर्ण अन्यथा अणु
		dev_err(&pdev->dev, "failed to parse TE gpio\n");
		वापस gpio;
	पूर्ण

	in = omapdss_of_find_source_क्रम_first_ep(node);
	अगर (IS_ERR(in)) अणु
		dev_err(&pdev->dev, "failed to find video source\n");
		वापस PTR_ERR(in);
	पूर्ण

	ddata->in = in;

	/* TODO: ulps, backlight */

	वापस 0;
पूर्ण

अटल पूर्णांक dsicm_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा backlight_properties props;
	काष्ठा panel_drv_data *ddata;
	काष्ठा backlight_device *bldev = शून्य;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा omap_dss_device *dssdev;
	पूर्णांक r;

	dev_dbg(dev, "probe\n");

	अगर (!pdev->dev.of_node)
		वापस -ENODEV;

	ddata = devm_kzalloc(dev, माप(*ddata), GFP_KERNEL);
	अगर (!ddata)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, ddata);
	ddata->pdev = pdev;

	r = dsicm_probe_of(pdev);
	अगर (r)
		वापस r;

	ddata->timings.x_res = 864;
	ddata->timings.y_res = 480;
	ddata->timings.pixelघड़ी = 864 * 480 * 60;

	dssdev = &ddata->dssdev;
	dssdev->dev = dev;
	dssdev->driver = &dsicm_ops;
	dssdev->panel.timings = ddata->timings;
	dssdev->type = OMAP_DISPLAY_TYPE_DSI;
	dssdev->owner = THIS_MODULE;

	dssdev->panel.dsi_pix_fmt = OMAP_DSS_DSI_FMT_RGB888;
	dssdev->caps = OMAP_DSS_DISPLAY_CAP_MANUAL_UPDATE |
		OMAP_DSS_DISPLAY_CAP_TEAR_ELIM;

	r = omapdss_रेजिस्टर_display(dssdev);
	अगर (r) अणु
		dev_err(dev, "Failed to register panel\n");
		जाओ err_reg;
	पूर्ण

	mutex_init(&ddata->lock);

	atomic_set(&ddata->करो_update, 0);

	अगर (gpio_is_valid(ddata->reset_gpio)) अणु
		r = devm_gpio_request_one(dev, ddata->reset_gpio,
				GPIOF_OUT_INIT_LOW, "taal rst");
		अगर (r) अणु
			dev_err(dev, "failed to request reset gpio\n");
			वापस r;
		पूर्ण
	पूर्ण

	अगर (gpio_is_valid(ddata->ext_te_gpio)) अणु
		r = devm_gpio_request_one(dev, ddata->ext_te_gpio,
				GPIOF_IN, "taal irq");
		अगर (r) अणु
			dev_err(dev, "GPIO request failed\n");
			वापस r;
		पूर्ण

		r = devm_request_irq(dev, gpio_to_irq(ddata->ext_te_gpio),
				dsicm_te_isr,
				IRQF_TRIGGER_RISING,
				"taal vsync", ddata);

		अगर (r) अणु
			dev_err(dev, "IRQ request failed\n");
			वापस r;
		पूर्ण

		INIT_DEFERRABLE_WORK(&ddata->te_समयout_work,
					dsicm_te_समयout_work_callback);

		dev_dbg(dev, "Using GPIO TE\n");
	पूर्ण

	INIT_DELAYED_WORK(&ddata->ulps_work, dsicm_ulps_work);

	dsicm_hw_reset(ddata);

	अगर (ddata->use_dsi_backlight) अणु
		स_रखो(&props, 0, माप(काष्ठा backlight_properties));
		props.max_brightness = 255;

		props.type = BACKLIGHT_RAW;
		bldev = backlight_device_रेजिस्टर(dev_name(dev),
				dev, ddata, &dsicm_bl_ops, &props);
		अगर (IS_ERR(bldev)) अणु
			r = PTR_ERR(bldev);
			जाओ err_reg;
		पूर्ण

		ddata->bldev = bldev;

		bldev->props.fb_blank = FB_BLANK_UNBLANK;
		bldev->props.घातer = FB_BLANK_UNBLANK;
		bldev->props.brightness = 255;

		dsicm_bl_update_status(bldev);
	पूर्ण

	r = sysfs_create_group(&dev->kobj, &dsicm_attr_group);
	अगर (r) अणु
		dev_err(dev, "failed to create sysfs files\n");
		जाओ err_sysfs_create;
	पूर्ण

	वापस 0;

err_sysfs_create:
	अगर (bldev != शून्य)
		backlight_device_unरेजिस्टर(bldev);
err_reg:
	वापस r;
पूर्ण

अटल पूर्णांक __निकास dsicm_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा panel_drv_data *ddata = platक्रमm_get_drvdata(pdev);
	काष्ठा omap_dss_device *dssdev = &ddata->dssdev;
	काष्ठा backlight_device *bldev;

	dev_dbg(&pdev->dev, "remove\n");

	omapdss_unरेजिस्टर_display(dssdev);

	dsicm_disable(dssdev);
	dsicm_disconnect(dssdev);

	sysfs_हटाओ_group(&pdev->dev.kobj, &dsicm_attr_group);

	bldev = ddata->bldev;
	अगर (bldev != शून्य) अणु
		bldev->props.घातer = FB_BLANK_POWERDOWN;
		dsicm_bl_update_status(bldev);
		backlight_device_unरेजिस्टर(bldev);
	पूर्ण

	omap_dss_put_device(ddata->in);

	dsicm_cancel_ulps_work(ddata);

	/* reset, to be sure that the panel is in a valid state */
	dsicm_hw_reset(ddata);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id dsicm_of_match[] = अणु
	अणु .compatible = "omapdss,panel-dsi-cm", पूर्ण,
	अणुपूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(of, dsicm_of_match);

अटल काष्ठा platक्रमm_driver dsicm_driver = अणु
	.probe = dsicm_probe,
	.हटाओ = __निकास_p(dsicm_हटाओ),
	.driver = अणु
		.name = "panel-dsi-cm",
		.of_match_table = dsicm_of_match,
		.suppress_bind_attrs = true,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(dsicm_driver);

MODULE_AUTHOR("Tomi Valkeinen <tomi.valkeinen@ti.com>");
MODULE_DESCRIPTION("Generic DSI Command Mode Panel Driver");
MODULE_LICENSE("GPL");
