<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Mainly by David Woodhouse, somewhat modअगरied by Jordan Crouse
 *
 * Copyright तऊ 2006-2007  Red Hat, Inc.
 * Copyright तऊ 2006-2007  Advanced Micro Devices, Inc.
 * Copyright तऊ 2009       VIA Technology, Inc.
 * Copyright (c) 2010-2011  Andres Salomon <dilinger@queued.net>
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/fb.h>
#समावेश <linux/console.h>
#समावेश <linux/i2c.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/delay.h>
#समावेश <linux/module.h>
#समावेश <linux/backlight.h>
#समावेश <linux/device.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/reboot.h>
#समावेश <linux/olpc-ec.h>
#समावेश <यंत्र/tsc.h>
#समावेश <यंत्र/olpc.h>

#समावेश "olpc_dcon.h"

/* Module definitions */

अटल uलघु resumeline = 898;
module_param(resumeline, uलघु, 0444);

अटल काष्ठा dcon_platक्रमm_data *pdata;

/* I2C काष्ठाures */

/* Platक्रमm devices */
अटल काष्ठा platक्रमm_device *dcon_device;

अटल अचिन्हित लघु normal_i2c[] = अणु 0x0d, I2C_CLIENT_END पूर्ण;

अटल s32 dcon_ग_लिखो(काष्ठा dcon_priv *dcon, u8 reg, u16 val)
अणु
	वापस i2c_smbus_ग_लिखो_word_data(dcon->client, reg, val);
पूर्ण

अटल s32 dcon_पढ़ो(काष्ठा dcon_priv *dcon, u8 reg)
अणु
	वापस i2c_smbus_पढ़ो_word_data(dcon->client, reg);
पूर्ण

/* ===== API functions - these are called by a variety of users ==== */

अटल पूर्णांक dcon_hw_init(काष्ठा dcon_priv *dcon, पूर्णांक is_init)
अणु
	u16 ver;
	पूर्णांक rc = 0;

	ver = dcon_पढ़ो(dcon, DCON_REG_ID);
	अगर ((ver >> 8) != 0xDC) अणु
		pr_err("DCON ID not 0xDCxx: 0x%04x instead.\n", ver);
		rc = -ENXIO;
		जाओ err;
	पूर्ण

	अगर (is_init) अणु
		pr_info("Discovered DCON version %x\n", ver & 0xFF);
		rc = pdata->init(dcon);
		अगर (rc != 0) अणु
			pr_err("Unable to init.\n");
			जाओ err;
		पूर्ण
	पूर्ण

	अगर (ver < 0xdc02) अणु
		dev_err(&dcon->client->dev,
			"DCON v1 is unsupported, giving up..\n");
		rc = -ENODEV;
		जाओ err;
	पूर्ण

	/* SDRAM setup/hold समय */
	dcon_ग_लिखो(dcon, 0x3a, 0xc040);
	dcon_ग_लिखो(dcon, DCON_REG_MEM_OPT_A, 0x0000);  /* clear option bits */
	dcon_ग_लिखो(dcon, DCON_REG_MEM_OPT_A,
		   MEM_DLL_CLOCK_DELAY | MEM_POWER_DOWN);
	dcon_ग_लिखो(dcon, DCON_REG_MEM_OPT_B, MEM_SOFT_RESET);

	/* Colour swizzle, AA, no passthrough, backlight */
	अगर (is_init) अणु
		dcon->disp_mode = MODE_PASSTHRU | MODE_BL_ENABLE |
				MODE_CSWIZZLE | MODE_COL_AA;
	पूर्ण
	dcon_ग_लिखो(dcon, DCON_REG_MODE, dcon->disp_mode);

	/* Set the scanline to पूर्णांकerrupt on during resume */
	dcon_ग_लिखो(dcon, DCON_REG_SCAN_INT, resumeline);

err:
	वापस rc;
पूर्ण

/*
 * The smbus करोesn't always come back due to what is believed to be
 * hardware (घातer rail) bugs.  For older models where this is known to
 * occur, our solution is to attempt to रुको क्रम the bus to stabilize;
 * अगर it करोesn't happen, cut घातer to the dcon, reघातer it, and रुको
 * क्रम the bus to stabilize.  Rinse, repeat until we have a working
 * smbus.  For newer models, we simply BUG(); we want to know अगर this
 * still happens despite the घातer fixes that have been made!
 */
अटल पूर्णांक dcon_bus_stabilize(काष्ठा dcon_priv *dcon, पूर्णांक is_घातered_करोwn)
अणु
	अचिन्हित दीर्घ समयout;
	u8 pm;
	पूर्णांक x;

घातer_up:
	अगर (is_घातered_करोwn) अणु
		pm = 1;
		x = olpc_ec_cmd(EC_DCON_POWER_MODE, &pm, 1, शून्य, 0);
		अगर (x) अणु
			pr_warn("unable to force dcon to power up: %d!\n", x);
			वापस x;
		पूर्ण
		usleep_range(10000, 11000);  /* we'll be conservative */
	पूर्ण

	pdata->bus_stabilize_wiggle();

	क्रम (x = -1, समयout = 50; समयout && x < 0; समयout--) अणु
		usleep_range(1000, 1100);
		x = dcon_पढ़ो(dcon, DCON_REG_ID);
	पूर्ण
	अगर (x < 0) अणु
		pr_err("unable to stabilize dcon's smbus, reasserting power and praying.\n");
		BUG_ON(olpc_board_at_least(olpc_board(0xc2)));
		pm = 0;
		olpc_ec_cmd(EC_DCON_POWER_MODE, &pm, 1, शून्य, 0);
		msleep(100);
		is_घातered_करोwn = 1;
		जाओ घातer_up;	/* argh, stupid hardware.. */
	पूर्ण

	अगर (is_घातered_करोwn)
		वापस dcon_hw_init(dcon, 0);
	वापस 0;
पूर्ण

अटल व्योम dcon_set_backlight(काष्ठा dcon_priv *dcon, u8 level)
अणु
	dcon->bl_val = level;
	dcon_ग_लिखो(dcon, DCON_REG_BRIGHT, dcon->bl_val);

	/* Purposely turn off the backlight when we go to level 0 */
	अगर (dcon->bl_val == 0) अणु
		dcon->disp_mode &= ~MODE_BL_ENABLE;
		dcon_ग_लिखो(dcon, DCON_REG_MODE, dcon->disp_mode);
	पूर्ण अन्यथा अगर (!(dcon->disp_mode & MODE_BL_ENABLE)) अणु
		dcon->disp_mode |= MODE_BL_ENABLE;
		dcon_ग_लिखो(dcon, DCON_REG_MODE, dcon->disp_mode);
	पूर्ण
पूर्ण

/* Set the output type to either color or mono */
अटल पूर्णांक dcon_set_mono_mode(काष्ठा dcon_priv *dcon, bool enable_mono)
अणु
	अगर (dcon->mono == enable_mono)
		वापस 0;

	dcon->mono = enable_mono;

	अगर (enable_mono) अणु
		dcon->disp_mode &= ~(MODE_CSWIZZLE | MODE_COL_AA);
		dcon->disp_mode |= MODE_MONO_LUMA;
	पूर्ण अन्यथा अणु
		dcon->disp_mode &= ~(MODE_MONO_LUMA);
		dcon->disp_mode |= MODE_CSWIZZLE | MODE_COL_AA;
	पूर्ण

	dcon_ग_लिखो(dcon, DCON_REG_MODE, dcon->disp_mode);
	वापस 0;
पूर्ण

/* For now, this will be really stupid - we need to address how
 * DCONLOAD works in a sleep and account क्रम it accordingly
 */

अटल व्योम dcon_sleep(काष्ठा dcon_priv *dcon, bool sleep)
अणु
	पूर्णांक x;

	/* Turn off the backlight and put the DCON to sleep */

	अगर (dcon->asleep == sleep)
		वापस;

	अगर (!olpc_board_at_least(olpc_board(0xc2)))
		वापस;

	अगर (sleep) अणु
		u8 pm = 0;

		x = olpc_ec_cmd(EC_DCON_POWER_MODE, &pm, 1, शून्य, 0);
		अगर (x)
			pr_warn("unable to force dcon to power down: %d!\n", x);
		अन्यथा
			dcon->asleep = sleep;
	पूर्ण अन्यथा अणु
		/* Only re-enable the backlight अगर the backlight value is set */
		अगर (dcon->bl_val != 0)
			dcon->disp_mode |= MODE_BL_ENABLE;
		x = dcon_bus_stabilize(dcon, 1);
		अगर (x)
			pr_warn("unable to reinit dcon hardware: %d!\n", x);
		अन्यथा
			dcon->asleep = sleep;

		/* Restore backlight */
		dcon_set_backlight(dcon, dcon->bl_val);
	पूर्ण

	/* We should turn off some stuff in the framebuffer - but what? */
पूर्ण

/* the DCON seems to get confused अगर we change DCONLOAD too
 * frequently -- i.e., approximately faster than frame समय.
 * normally we करोn't change it this fast, so in general we won't
 * delay here.
 */
अटल व्योम dcon_load_holकरोff(काष्ठा dcon_priv *dcon)
अणु
	kसमय_प्रकार delta_t, now;

	जबतक (1) अणु
		now = kसमय_get();
		delta_t = kसमय_sub(now, dcon->load_समय);
		अगर (kसमय_प्रकारo_ns(delta_t) > NSEC_PER_MSEC * 20)
			अवरोध;
		mdelay(4);
	पूर्ण
पूर्ण

अटल bool dcon_blank_fb(काष्ठा dcon_priv *dcon, bool blank)
अणु
	पूर्णांक err;

	console_lock();
	lock_fb_info(dcon->fbinfo);

	dcon->ignore_fb_events = true;
	err = fb_blank(dcon->fbinfo,
		       blank ? FB_BLANK_POWERDOWN : FB_BLANK_UNBLANK);
	dcon->ignore_fb_events = false;
	unlock_fb_info(dcon->fbinfo);
	console_unlock();

	अगर (err) अणु
		dev_err(&dcon->client->dev, "couldn't %sblank framebuffer\n",
			blank ? "" : "un");
		वापस false;
	पूर्ण
	वापस true;
पूर्ण

/* Set the source of the display (CPU or DCON) */
अटल व्योम dcon_source_चयन(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा dcon_priv *dcon = container_of(work, काष्ठा dcon_priv,
			चयन_source);
	पूर्णांक source = dcon->pending_src;

	अगर (dcon->curr_src == source)
		वापस;

	dcon_load_holकरोff(dcon);

	dcon->चयनed = false;

	चयन (source) अणु
	हाल DCON_SOURCE_CPU:
		pr_info("%s to CPU\n", __func__);
		/* Enable the scanline पूर्णांकerrupt bit */
		अगर (dcon_ग_लिखो(dcon, DCON_REG_MODE,
			       dcon->disp_mode | MODE_SCAN_INT))
			pr_err("couldn't enable scanline interrupt!\n");
		अन्यथा
			/* Wait up to one second क्रम the scanline पूर्णांकerrupt */
			रुको_event_समयout(dcon->रुकोq, dcon->चयनed, HZ);

		अगर (!dcon->चयनed)
			pr_err("Timeout entering CPU mode; expect a screen glitch.\n");

		/* Turn off the scanline पूर्णांकerrupt */
		अगर (dcon_ग_लिखो(dcon, DCON_REG_MODE, dcon->disp_mode))
			pr_err("couldn't disable scanline interrupt!\n");

		/*
		 * Ideally we'd like to disable पूर्णांकerrupts here so that the
		 * fb unblanking and DCON turn on happen at a known समय value;
		 * however, we can't करो that right now with fb_blank
		 * messing with semaphores.
		 *
		 * For now, we just hope..
		 */
		अगर (!dcon_blank_fb(dcon, false)) अणु
			pr_err("Failed to enter CPU mode\n");
			dcon->pending_src = DCON_SOURCE_DCON;
			वापस;
		पूर्ण

		/* And turn off the DCON */
		pdata->set_dconload(1);
		dcon->load_समय = kसमय_get();

		pr_info("The CPU has control\n");
		अवरोध;
	हाल DCON_SOURCE_DCON:
	अणु
		kसमय_प्रकार delta_t;

		pr_info("%s to DCON\n", __func__);

		/* Clear DCONLOAD - this implies that the DCON is in control */
		pdata->set_dconload(0);
		dcon->load_समय = kसमय_get();

		रुको_event_समयout(dcon->रुकोq, dcon->चयनed, HZ / 2);

		अगर (!dcon->चयनed) अणु
			pr_err("Timeout entering DCON mode; expect a screen glitch.\n");
		पूर्ण अन्यथा अणु
			/* someबार the DCON करोesn't follow its own rules,
			 * and करोesn't रुको क्रम two vsync pulses beक्रमe
			 * ack'ing the frame load with an IRQ.  the result
			 * is that the display shows the *previously*
			 * loaded frame.  we can detect this by looking at
			 * the समय between निश्चितing DCONLOAD and the IRQ --
			 * अगर it's less than 20msec, then the DCON couldn't
			 * have seen two VSYNC pulses.  in that हाल we
			 * deनिश्चित and reनिश्चित, and hope क्रम the best.
			 * see http://dev.laptop.org/ticket/9664
			 */
			delta_t = kसमय_sub(dcon->irq_समय, dcon->load_समय);
			अगर (dcon->चयनed && kसमय_प्रकारo_ns(delta_t)
			    < NSEC_PER_MSEC * 20) अणु
				pr_err("missed loading, retrying\n");
				pdata->set_dconload(1);
				mdelay(41);
				pdata->set_dconload(0);
				dcon->load_समय = kसमय_get();
				mdelay(41);
			पूर्ण
		पूर्ण

		dcon_blank_fb(dcon, true);
		pr_info("The DCON has control\n");
		अवरोध;
	पूर्ण
	शेष:
		BUG();
	पूर्ण

	dcon->curr_src = source;
पूर्ण

अटल व्योम dcon_set_source(काष्ठा dcon_priv *dcon, पूर्णांक arg)
अणु
	अगर (dcon->pending_src == arg)
		वापस;

	dcon->pending_src = arg;

	अगर (dcon->curr_src != arg)
		schedule_work(&dcon->चयन_source);
पूर्ण

अटल व्योम dcon_set_source_sync(काष्ठा dcon_priv *dcon, पूर्णांक arg)
अणु
	dcon_set_source(dcon, arg);
	flush_scheduled_work();
पूर्ण

अटल sमाप_प्रकार dcon_mode_show(काष्ठा device *dev,
			      काष्ठा device_attribute *attr,
			      अक्षर *buf)
अणु
	काष्ठा dcon_priv *dcon = dev_get_drvdata(dev);

	वापस प्र_लिखो(buf, "%4.4X\n", dcon->disp_mode);
पूर्ण

अटल sमाप_प्रकार dcon_sleep_show(काष्ठा device *dev,
			       काष्ठा device_attribute *attr,
			       अक्षर *buf)
अणु
	काष्ठा dcon_priv *dcon = dev_get_drvdata(dev);

	वापस प्र_लिखो(buf, "%d\n", dcon->asleep);
पूर्ण

अटल sमाप_प्रकार dcon_मुक्तze_show(काष्ठा device *dev,
				काष्ठा device_attribute *attr,
				अक्षर *buf)
अणु
	काष्ठा dcon_priv *dcon = dev_get_drvdata(dev);

	वापस प्र_लिखो(buf, "%d\n", dcon->curr_src == DCON_SOURCE_DCON ? 1 : 0);
पूर्ण

अटल sमाप_प्रकार dcon_mono_show(काष्ठा device *dev,
			      काष्ठा device_attribute *attr,
			      अक्षर *buf)
अणु
	काष्ठा dcon_priv *dcon = dev_get_drvdata(dev);

	वापस प्र_लिखो(buf, "%d\n", dcon->mono);
पूर्ण

अटल sमाप_प्रकार dcon_resumeline_show(काष्ठा device *dev,
				    काष्ठा device_attribute *attr,
				    अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%d\n", resumeline);
पूर्ण

अटल sमाप_प्रकार dcon_mono_store(काष्ठा device *dev,
			       काष्ठा device_attribute *attr,
			       स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	अचिन्हित दीर्घ enable_mono;
	पूर्णांक rc;

	rc = kम_से_अदीर्घ(buf, 10, &enable_mono);
	अगर (rc)
		वापस rc;

	dcon_set_mono_mode(dev_get_drvdata(dev), enable_mono ? true : false);

	वापस count;
पूर्ण

अटल sमाप_प्रकार dcon_मुक्तze_store(काष्ठा device *dev,
				 काष्ठा device_attribute *attr,
				 स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा dcon_priv *dcon = dev_get_drvdata(dev);
	अचिन्हित दीर्घ output;
	पूर्णांक ret;

	ret = kम_से_अदीर्घ(buf, 10, &output);
	अगर (ret)
		वापस ret;

	चयन (output) अणु
	हाल 0:
		dcon_set_source(dcon, DCON_SOURCE_CPU);
		अवरोध;
	हाल 1:
		dcon_set_source_sync(dcon, DCON_SOURCE_DCON);
		अवरोध;
	हाल 2:  /* normally unused */
		dcon_set_source(dcon, DCON_SOURCE_DCON);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस count;
पूर्ण

अटल sमाप_प्रकार dcon_resumeline_store(काष्ठा device *dev,
				     काष्ठा device_attribute *attr,
				     स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	अचिन्हित लघु rl;
	पूर्णांक rc;

	rc = kstrtou16(buf, 10, &rl);
	अगर (rc)
		वापस rc;

	resumeline = rl;
	dcon_ग_लिखो(dev_get_drvdata(dev), DCON_REG_SCAN_INT, resumeline);

	वापस count;
पूर्ण

अटल sमाप_प्रकार dcon_sleep_store(काष्ठा device *dev,
				काष्ठा device_attribute *attr,
				स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	अचिन्हित दीर्घ output;
	पूर्णांक ret;

	ret = kम_से_अदीर्घ(buf, 10, &output);
	अगर (ret)
		वापस ret;

	dcon_sleep(dev_get_drvdata(dev), output ? true : false);
	वापस count;
पूर्ण

अटल काष्ठा device_attribute dcon_device_files[] = अणु
	__ATTR(mode, 0444, dcon_mode_show, शून्य),
	__ATTR(sleep, 0644, dcon_sleep_show, dcon_sleep_store),
	__ATTR(मुक्तze, 0644, dcon_मुक्तze_show, dcon_मुक्तze_store),
	__ATTR(monochrome, 0644, dcon_mono_show, dcon_mono_store),
	__ATTR(resumeline, 0644, dcon_resumeline_show, dcon_resumeline_store),
पूर्ण;

अटल पूर्णांक dcon_bl_update(काष्ठा backlight_device *dev)
अणु
	काष्ठा dcon_priv *dcon = bl_get_data(dev);
	u8 level = dev->props.brightness & 0x0F;

	अगर (dev->props.घातer != FB_BLANK_UNBLANK)
		level = 0;

	अगर (level != dcon->bl_val)
		dcon_set_backlight(dcon, level);

	/* घातer करोwn the DCON when the screen is blanked */
	अगर (!dcon->ignore_fb_events)
		dcon_sleep(dcon, !!(dev->props.state & BL_CORE_FBBLANK));

	वापस 0;
पूर्ण

अटल पूर्णांक dcon_bl_get(काष्ठा backlight_device *dev)
अणु
	काष्ठा dcon_priv *dcon = bl_get_data(dev);

	वापस dcon->bl_val;
पूर्ण

अटल स्थिर काष्ठा backlight_ops dcon_bl_ops = अणु
	.update_status = dcon_bl_update,
	.get_brightness = dcon_bl_get,
पूर्ण;

अटल काष्ठा backlight_properties dcon_bl_props = अणु
	.max_brightness = 15,
	.type = BACKLIGHT_RAW,
	.घातer = FB_BLANK_UNBLANK,
पूर्ण;

अटल पूर्णांक dcon_reboot_notअगरy(काष्ठा notअगरier_block *nb,
			      अचिन्हित दीर्घ foo, व्योम *bar)
अणु
	काष्ठा dcon_priv *dcon = container_of(nb, काष्ठा dcon_priv, reboot_nb);

	अगर (!dcon || !dcon->client)
		वापस NOTIFY_DONE;

	/* Turn off the DCON. Entirely. */
	dcon_ग_लिखो(dcon, DCON_REG_MODE, 0x39);
	dcon_ग_लिखो(dcon, DCON_REG_MODE, 0x32);
	वापस NOTIFY_DONE;
पूर्ण

अटल पूर्णांक unमुक्तze_on_panic(काष्ठा notअगरier_block *nb,
			     अचिन्हित दीर्घ e, व्योम *p)
अणु
	pdata->set_dconload(1);
	वापस NOTIFY_DONE;
पूर्ण

अटल काष्ठा notअगरier_block dcon_panic_nb = अणु
	.notअगरier_call = unमुक्तze_on_panic,
पूर्ण;

अटल पूर्णांक dcon_detect(काष्ठा i2c_client *client, काष्ठा i2c_board_info *info)
अणु
	strscpy(info->type, "olpc_dcon", I2C_NAME_SIZE);

	वापस 0;
पूर्ण

अटल पूर्णांक dcon_probe(काष्ठा i2c_client *client, स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा dcon_priv *dcon;
	पूर्णांक rc, i, j;

	अगर (!pdata)
		वापस -ENXIO;

	dcon = kzalloc(माप(*dcon), GFP_KERNEL);
	अगर (!dcon)
		वापस -ENOMEM;

	dcon->client = client;
	init_रुकोqueue_head(&dcon->रुकोq);
	INIT_WORK(&dcon->चयन_source, dcon_source_चयन);
	dcon->reboot_nb.notअगरier_call = dcon_reboot_notअगरy;
	dcon->reboot_nb.priority = -1;

	i2c_set_clientdata(client, dcon);

	अगर (num_रेजिस्टरed_fb < 1) अणु
		dev_err(&client->dev, "DCON driver requires a registered fb\n");
		rc = -EIO;
		जाओ einit;
	पूर्ण
	dcon->fbinfo = रेजिस्टरed_fb[0];

	rc = dcon_hw_init(dcon, 1);
	अगर (rc)
		जाओ einit;

	/* Add the DCON device */

	dcon_device = platक्रमm_device_alloc("dcon", -1);

	अगर (!dcon_device) अणु
		pr_err("Unable to create the DCON device\n");
		rc = -ENOMEM;
		जाओ eirq;
	पूर्ण
	rc = platक्रमm_device_add(dcon_device);
	platक्रमm_set_drvdata(dcon_device, dcon);

	अगर (rc) अणु
		pr_err("Unable to add the DCON device\n");
		जाओ edev;
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(dcon_device_files); i++) अणु
		rc = device_create_file(&dcon_device->dev,
					&dcon_device_files[i]);
		अगर (rc) अणु
			dev_err(&dcon_device->dev, "Cannot create sysfs file\n");
			जाओ ecreate;
		पूर्ण
	पूर्ण

	dcon->bl_val = dcon_पढ़ो(dcon, DCON_REG_BRIGHT) & 0x0F;

	/* Add the backlight device क्रम the DCON */
	dcon_bl_props.brightness = dcon->bl_val;
	dcon->bl_dev = backlight_device_रेजिस्टर("dcon-bl", &dcon_device->dev,
						 dcon, &dcon_bl_ops,
						 &dcon_bl_props);
	अगर (IS_ERR(dcon->bl_dev)) अणु
		dev_err(&client->dev, "cannot register backlight dev (%ld)\n",
			PTR_ERR(dcon->bl_dev));
		dcon->bl_dev = शून्य;
	पूर्ण

	रेजिस्टर_reboot_notअगरier(&dcon->reboot_nb);
	atomic_notअगरier_chain_रेजिस्टर(&panic_notअगरier_list, &dcon_panic_nb);

	वापस 0;

 ecreate:
	क्रम (j = 0; j < i; j++)
		device_हटाओ_file(&dcon_device->dev, &dcon_device_files[j]);
	platक्रमm_device_del(dcon_device);
 edev:
	platक्रमm_device_put(dcon_device);
	dcon_device = शून्य;
 eirq:
	मुक्त_irq(DCON_IRQ, dcon);
 einit:
	kमुक्त(dcon);
	वापस rc;
पूर्ण

अटल पूर्णांक dcon_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा dcon_priv *dcon = i2c_get_clientdata(client);

	unरेजिस्टर_reboot_notअगरier(&dcon->reboot_nb);
	atomic_notअगरier_chain_unरेजिस्टर(&panic_notअगरier_list, &dcon_panic_nb);

	मुक्त_irq(DCON_IRQ, dcon);

	backlight_device_unरेजिस्टर(dcon->bl_dev);

	अगर (dcon_device)
		platक्रमm_device_unरेजिस्टर(dcon_device);
	cancel_work_sync(&dcon->चयन_source);

	kमुक्त(dcon);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक dcon_suspend(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा dcon_priv *dcon = i2c_get_clientdata(client);

	अगर (!dcon->asleep) अणु
		/* Set up the DCON to have the source */
		dcon_set_source_sync(dcon, DCON_SOURCE_DCON);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक dcon_resume(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा dcon_priv *dcon = i2c_get_clientdata(client);

	अगर (!dcon->asleep) अणु
		dcon_bus_stabilize(dcon, 0);
		dcon_set_source(dcon, DCON_SOURCE_CPU);
	पूर्ण

	वापस 0;
पूर्ण

#अन्यथा

#घोषणा dcon_suspend शून्य
#घोषणा dcon_resume शून्य

#पूर्ण_अगर /* CONFIG_PM */

irqवापस_t dcon_पूर्णांकerrupt(पूर्णांक irq, व्योम *id)
अणु
	काष्ठा dcon_priv *dcon = id;
	u8 status;

	अगर (pdata->पढ़ो_status(&status))
		वापस IRQ_NONE;

	चयन (status & 3) अणु
	हाल 3:
		pr_debug("DCONLOAD_MISSED interrupt\n");
		अवरोध;

	हाल 2:	/* चयन to DCON mode */
	हाल 1: /* चयन to CPU mode */
		dcon->चयनed = true;
		dcon->irq_समय = kसमय_get();
		wake_up(&dcon->रुकोq);
		अवरोध;

	हाल 0:
		/* workaround resume हाल:  the DCON (on 1.5) करोesn't
		 * ever निश्चित status 0x01 when चयनing to CPU mode
		 * during resume.  this is because DCONLOAD is de-निश्चितed
		 * _immediately_ upon निकासing S3, so the actual release
		 * of the DCON happened दीर्घ beक्रमe this poपूर्णांक.
		 * see http://dev.laptop.org/ticket/9869
		 */
		अगर (dcon->curr_src != dcon->pending_src && !dcon->चयनed) अणु
			dcon->चयनed = true;
			dcon->irq_समय = kसमय_get();
			wake_up(&dcon->रुकोq);
			pr_debug("switching w/ status 0/0\n");
		पूर्ण अन्यथा अणु
			pr_debug("scanline interrupt w/CPU\n");
		पूर्ण
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops dcon_pm_ops = अणु
	.suspend = dcon_suspend,
	.resume = dcon_resume,
पूर्ण;

अटल स्थिर काष्ठा i2c_device_id dcon_idtable[] = अणु
	अणु "olpc_dcon",  0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, dcon_idtable);

अटल काष्ठा i2c_driver dcon_driver = अणु
	.driver = अणु
		.name	= "olpc_dcon",
		.pm = &dcon_pm_ops,
	पूर्ण,
	.class = I2C_CLASS_DDC | I2C_CLASS_HWMON,
	.id_table = dcon_idtable,
	.probe = dcon_probe,
	.हटाओ = dcon_हटाओ,
	.detect = dcon_detect,
	.address_list = normal_i2c,
पूर्ण;

अटल पूर्णांक __init olpc_dcon_init(व्योम)
अणु
	/* XO-1.5 */
	अगर (olpc_board_at_least(olpc_board(0xd0)))
		pdata = &dcon_pdata_xo_1_5;
	अन्यथा
		pdata = &dcon_pdata_xo_1;

	वापस i2c_add_driver(&dcon_driver);
पूर्ण

अटल व्योम __निकास olpc_dcon_निकास(व्योम)
अणु
	i2c_del_driver(&dcon_driver);
पूर्ण

module_init(olpc_dcon_init);
module_निकास(olpc_dcon_निकास);

MODULE_LICENSE("GPL");
