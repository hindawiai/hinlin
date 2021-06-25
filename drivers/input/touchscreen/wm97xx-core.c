<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * wm97xx-core.c  --  Touch screen driver core क्रम Wolfson WM9705, WM9712
 *                    and WM9713 AC97 Codecs.
 *
 * Copyright 2003, 2004, 2005, 2006, 2007, 2008 Wolfson Microelectronics PLC.
 * Author: Liam Girdwood <lrg@slimlogic.co.uk>
 * Parts Copyright : Ian Molton <spyro@f2s.com>
 *                   Andrew Zabolotny <zap@homelink.ru>
 *                   Russell King <rmk@arm.linux.org.uk>
 *
 * Notes:
 *
 *  Features:
 *       - supports WM9705, WM9712, WM9713
 *       - polling mode
 *       - continuous mode (arch-dependent)
 *       - adjustable rpu/dpp settings
 *       - adjustable pressure current
 *       - adjustable sample settle delay
 *       - 4 and 5 wire touchscreens (5 wire is WM9712 only)
 *       - pen करोwn detection
 *       - battery monitor
 *       - sample AUX adcs
 *       - घातer management
 *       - codec GPIO
 *       - codec event notअगरication
 * Toकरो
 *       - Support क्रम async sampling control क्रम noisy LCDs.
 */

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/माला.स>
#समावेश <linux/proc_fs.h>
#समावेश <linux/pm.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/bitops.h>
#समावेश <linux/mfd/wm97xx.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/wm97xx.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/पन.स>
#समावेश <linux/slab.h>

#घोषणा TS_NAME			"wm97xx"
#घोषणा WM_CORE_VERSION		"1.00"
#घोषणा DEFAULT_PRESSURE	0xb0c0


/*
 * Touchscreen असलolute values
 *
 * These parameters are used to help the input layer discard out of
 * range पढ़ोings and reduce jitter etc.
 *
 *   o min, max:- indicate the min and max values your touch screen वापसs
 *   o fuzz:- use a higher number to reduce jitter
 *
 * The शेष values correspond to Mainstone II in QVGA mode
 *
 * Please पढ़ो
 * Documentation/input/input-programming.rst क्रम more details.
 */

अटल पूर्णांक असल_x[3] = अणु150, 4000, 5पूर्ण;
module_param_array(असल_x, पूर्णांक, शून्य, 0);
MODULE_PARM_DESC(असल_x, "Touchscreen absolute X min, max, fuzz");

अटल पूर्णांक असल_y[3] = अणु200, 4000, 40पूर्ण;
module_param_array(असल_y, पूर्णांक, शून्य, 0);
MODULE_PARM_DESC(असल_y, "Touchscreen absolute Y min, max, fuzz");

अटल पूर्णांक असल_p[3] = अणु0, 150, 4पूर्ण;
module_param_array(असल_p, पूर्णांक, शून्य, 0);
MODULE_PARM_DESC(असल_p, "Touchscreen absolute Pressure min, max, fuzz");

/*
 * wm97xx IO access, all IO locking करोne by AC97 layer
 */
पूर्णांक wm97xx_reg_पढ़ो(काष्ठा wm97xx *wm, u16 reg)
अणु
	अगर (wm->ac97)
		वापस wm->ac97->bus->ops->पढ़ो(wm->ac97, reg);
	अन्यथा
		वापस -1;
पूर्ण
EXPORT_SYMBOL_GPL(wm97xx_reg_पढ़ो);

व्योम wm97xx_reg_ग_लिखो(काष्ठा wm97xx *wm, u16 reg, u16 val)
अणु
	/* cache digitiser रेजिस्टरs */
	अगर (reg >= AC97_WM9713_DIG1 && reg <= AC97_WM9713_DIG3)
		wm->dig[(reg - AC97_WM9713_DIG1) >> 1] = val;

	/* cache gpio regs */
	अगर (reg >= AC97_GPIO_CFG && reg <= AC97_MISC_AFE)
		wm->gpio[(reg - AC97_GPIO_CFG) >> 1] = val;

	/* wm9713 irq reg */
	अगर (reg == 0x5a)
		wm->misc = val;

	अगर (wm->ac97)
		wm->ac97->bus->ops->ग_लिखो(wm->ac97, reg, val);
पूर्ण
EXPORT_SYMBOL_GPL(wm97xx_reg_ग_लिखो);

/**
 * wm97xx_पढ़ो_aux_adc - Read the aux adc.
 * @wm: wm97xx device.
 * @adcsel: codec ADC to be पढ़ो
 *
 * Reads the selected AUX ADC.
 */

पूर्णांक wm97xx_पढ़ो_aux_adc(काष्ठा wm97xx *wm, u16 adcsel)
अणु
	पूर्णांक घातer_adc = 0, auxval;
	u16 घातer = 0;
	पूर्णांक rc = 0;
	पूर्णांक समयout = 0;

	/* get codec */
	mutex_lock(&wm->codec_mutex);

	/* When the touchscreen is not in use, we may have to घातer up
	 * the AUX ADC beक्रमe we can use sample the AUX inमाला_दो->
	 */
	अगर (wm->id == WM9713_ID2 &&
	    (घातer = wm97xx_reg_पढ़ो(wm, AC97_EXTENDED_MID)) & 0x8000) अणु
		घातer_adc = 1;
		wm97xx_reg_ग_लिखो(wm, AC97_EXTENDED_MID, घातer & 0x7fff);
	पूर्ण

	/* Prepare the codec क्रम AUX पढ़ोing */
	wm->codec->aux_prepare(wm);

	/* Turn polling mode on to पढ़ो AUX ADC */
	wm->pen_probably_करोwn = 1;

	जबतक (rc != RC_VALID && समयout++ < 5)
		rc = wm->codec->poll_sample(wm, adcsel, &auxval);

	अगर (घातer_adc)
		wm97xx_reg_ग_लिखो(wm, AC97_EXTENDED_MID, घातer | 0x8000);

	wm->codec->dig_restore(wm);

	wm->pen_probably_करोwn = 0;

	अगर (समयout >= 5) अणु
		dev_err(wm->dev,
			"timeout reading auxadc %d, disabling digitiser\n",
			adcsel);
		wm->codec->dig_enable(wm, false);
	पूर्ण

	mutex_unlock(&wm->codec_mutex);
	वापस (rc == RC_VALID ? auxval & 0xfff : -EBUSY);
पूर्ण
EXPORT_SYMBOL_GPL(wm97xx_पढ़ो_aux_adc);

/**
 * wm97xx_get_gpio - Get the status of a codec GPIO.
 * @wm: wm97xx device.
 * @gpio: gpio
 *
 * Get the status of a codec GPIO pin
 */

क्रमागत wm97xx_gpio_status wm97xx_get_gpio(काष्ठा wm97xx *wm, u32 gpio)
अणु
	u16 status;
	क्रमागत wm97xx_gpio_status ret;

	mutex_lock(&wm->codec_mutex);
	status = wm97xx_reg_पढ़ो(wm, AC97_GPIO_STATUS);

	अगर (status & gpio)
		ret = WM97XX_GPIO_HIGH;
	अन्यथा
		ret = WM97XX_GPIO_LOW;

	mutex_unlock(&wm->codec_mutex);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(wm97xx_get_gpio);

/**
 * wm97xx_set_gpio - Set the status of a codec GPIO.
 * @wm: wm97xx device.
 * @gpio: gpio
 * @status: status
 *
 * Set the status of a codec GPIO pin
 */

व्योम wm97xx_set_gpio(काष्ठा wm97xx *wm, u32 gpio,
				क्रमागत wm97xx_gpio_status status)
अणु
	u16 reg;

	mutex_lock(&wm->codec_mutex);
	reg = wm97xx_reg_पढ़ो(wm, AC97_GPIO_STATUS);

	अगर (status == WM97XX_GPIO_HIGH)
		reg |= gpio;
	अन्यथा
		reg &= ~gpio;

	अगर (wm->id == WM9712_ID2 && wm->variant != WM97xx_WM1613)
		wm97xx_reg_ग_लिखो(wm, AC97_GPIO_STATUS, reg << 1);
	अन्यथा
		wm97xx_reg_ग_लिखो(wm, AC97_GPIO_STATUS, reg);
	mutex_unlock(&wm->codec_mutex);
पूर्ण
EXPORT_SYMBOL_GPL(wm97xx_set_gpio);

/*
 * Codec GPIO pin configuration, this sets pin direction, polarity,
 * stickyness and wake up.
 */
व्योम wm97xx_config_gpio(काष्ठा wm97xx *wm, u32 gpio, क्रमागत wm97xx_gpio_dir dir,
		   क्रमागत wm97xx_gpio_pol pol, क्रमागत wm97xx_gpio_sticky sticky,
		   क्रमागत wm97xx_gpio_wake wake)
अणु
	u16 reg;

	mutex_lock(&wm->codec_mutex);
	reg = wm97xx_reg_पढ़ो(wm, AC97_GPIO_POLARITY);

	अगर (pol == WM97XX_GPIO_POL_HIGH)
		reg |= gpio;
	अन्यथा
		reg &= ~gpio;

	wm97xx_reg_ग_लिखो(wm, AC97_GPIO_POLARITY, reg);
	reg = wm97xx_reg_पढ़ो(wm, AC97_GPIO_STICKY);

	अगर (sticky == WM97XX_GPIO_STICKY)
		reg |= gpio;
	अन्यथा
		reg &= ~gpio;

	wm97xx_reg_ग_लिखो(wm, AC97_GPIO_STICKY, reg);
	reg = wm97xx_reg_पढ़ो(wm, AC97_GPIO_WAKEUP);

	अगर (wake == WM97XX_GPIO_WAKE)
		reg |= gpio;
	अन्यथा
		reg &= ~gpio;

	wm97xx_reg_ग_लिखो(wm, AC97_GPIO_WAKEUP, reg);
	reg = wm97xx_reg_पढ़ो(wm, AC97_GPIO_CFG);

	अगर (dir == WM97XX_GPIO_IN)
		reg |= gpio;
	अन्यथा
		reg &= ~gpio;

	wm97xx_reg_ग_लिखो(wm, AC97_GPIO_CFG, reg);
	mutex_unlock(&wm->codec_mutex);
पूर्ण
EXPORT_SYMBOL_GPL(wm97xx_config_gpio);

/*
 * Configure the WM97XX_PRP value to use जबतक प्रणाली is suspended.
 * If a value other than 0 is set then WM97xx pen detection will be
 * left enabled in the configured mode जबतक the प्रणाली is in suspend,
 * the device has users and suspend has not been disabled via the
 * wakeup sysfs entries.
 *
 * @wm:   WM97xx device to configure
 * @mode: WM97XX_PRP value to configure जबतक suspended
 */
व्योम wm97xx_set_suspend_mode(काष्ठा wm97xx *wm, u16 mode)
अणु
	wm->suspend_mode = mode;
	device_init_wakeup(&wm->input_dev->dev, mode != 0);
पूर्ण
EXPORT_SYMBOL_GPL(wm97xx_set_suspend_mode);

/*
 * Handle a pen करोwn पूर्णांकerrupt.
 */
अटल व्योम wm97xx_pen_irq_worker(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा wm97xx *wm = container_of(work, काष्ठा wm97xx, pen_event_work);
	पूर्णांक pen_was_करोwn = wm->pen_is_करोwn;

	/* करो we need to enable the touch panel पढ़ोer */
	अगर (wm->id == WM9705_ID2) अणु
		अगर (wm97xx_reg_पढ़ो(wm, AC97_WM97XX_DIGITISER_RD) &
					WM97XX_PEN_DOWN)
			wm->pen_is_करोwn = 1;
		अन्यथा
			wm->pen_is_करोwn = 0;
	पूर्ण अन्यथा अणु
		u16 status, pol;
		mutex_lock(&wm->codec_mutex);
		status = wm97xx_reg_पढ़ो(wm, AC97_GPIO_STATUS);
		pol = wm97xx_reg_पढ़ो(wm, AC97_GPIO_POLARITY);

		अगर (WM97XX_GPIO_13 & pol & status) अणु
			wm->pen_is_करोwn = 1;
			wm97xx_reg_ग_लिखो(wm, AC97_GPIO_POLARITY, pol &
						~WM97XX_GPIO_13);
		पूर्ण अन्यथा अणु
			wm->pen_is_करोwn = 0;
			wm97xx_reg_ग_लिखो(wm, AC97_GPIO_POLARITY, pol |
					 WM97XX_GPIO_13);
		पूर्ण

		अगर (wm->id == WM9712_ID2 && wm->variant != WM97xx_WM1613)
			wm97xx_reg_ग_लिखो(wm, AC97_GPIO_STATUS, (status &
						~WM97XX_GPIO_13) << 1);
		अन्यथा
			wm97xx_reg_ग_लिखो(wm, AC97_GPIO_STATUS, status &
						~WM97XX_GPIO_13);
		mutex_unlock(&wm->codec_mutex);
	पूर्ण

	/* If the प्रणाली is not using continuous mode or it provides a
	 * pen करोwn operation then we need to schedule polls जबतक the
	 * pen is करोwn.  Otherwise the machine driver is responsible
	 * क्रम scheduling पढ़ोs.
	 */
	अगर (!wm->mach_ops->acc_enabled || wm->mach_ops->acc_pen_करोwn) अणु
		अगर (wm->pen_is_करोwn && !pen_was_करोwn) अणु
			/* Data is not available immediately on pen करोwn */
			queue_delayed_work(wm->ts_workq, &wm->ts_पढ़ोer, 1);
		पूर्ण

		/* Let ts_पढ़ोer report the pen up क्रम debounce. */
		अगर (!wm->pen_is_करोwn && pen_was_करोwn)
			wm->pen_is_करोwn = 1;
	पूर्ण

	अगर (!wm->pen_is_करोwn && wm->mach_ops->acc_enabled)
		wm->mach_ops->acc_pen_up(wm);

	wm->mach_ops->irq_enable(wm, 1);
पूर्ण

/*
 * Codec PENDOWN irq handler
 *
 * We have to disable the codec पूर्णांकerrupt in the handler because it
 * can take up to 1ms to clear the पूर्णांकerrupt source. We schedule a task
 * in a work queue to करो the actual पूर्णांकeraction with the chip.  The
 * पूर्णांकerrupt is then enabled again in the slow handler when the source
 * has been cleared.
 */
अटल irqवापस_t wm97xx_pen_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा wm97xx *wm = dev_id;

	अगर (!work_pending(&wm->pen_event_work)) अणु
		wm->mach_ops->irq_enable(wm, 0);
		queue_work(wm->ts_workq, &wm->pen_event_work);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

/*
 * initialise pen IRQ handler and workqueue
 */
अटल पूर्णांक wm97xx_init_pen_irq(काष्ठा wm97xx *wm)
अणु
	u16 reg;

	/* If an पूर्णांकerrupt is supplied an IRQ enable operation must also be
	 * provided. */
	BUG_ON(!wm->mach_ops->irq_enable);

	अगर (request_irq(wm->pen_irq, wm97xx_pen_पूर्णांकerrupt, IRQF_SHARED,
			"wm97xx-pen", wm)) अणु
		dev_err(wm->dev,
			"Failed to register pen down interrupt, polling");
		wm->pen_irq = 0;
		वापस -EINVAL;
	पूर्ण

	/* Configure GPIO as पूर्णांकerrupt source on WM971x */
	अगर (wm->id != WM9705_ID2) अणु
		BUG_ON(!wm->mach_ops->irq_gpio);
		reg = wm97xx_reg_पढ़ो(wm, AC97_MISC_AFE);
		wm97xx_reg_ग_लिखो(wm, AC97_MISC_AFE,
				reg & ~(wm->mach_ops->irq_gpio));
		reg = wm97xx_reg_पढ़ो(wm, 0x5a);
		wm97xx_reg_ग_लिखो(wm, 0x5a, reg & ~0x0001);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक wm97xx_पढ़ो_samples(काष्ठा wm97xx *wm)
अणु
	काष्ठा wm97xx_data data;
	पूर्णांक rc;

	mutex_lock(&wm->codec_mutex);

	अगर (wm->mach_ops && wm->mach_ops->acc_enabled)
		rc = wm->mach_ops->acc_pen_करोwn(wm);
	अन्यथा
		rc = wm->codec->poll_touch(wm, &data);

	अगर (rc & RC_PENUP) अणु
		अगर (wm->pen_is_करोwn) अणु
			wm->pen_is_करोwn = 0;
			dev_dbg(wm->dev, "pen up\n");
			input_report_असल(wm->input_dev, ABS_PRESSURE, 0);
			input_report_key(wm->input_dev, BTN_TOUCH, 0);
			input_sync(wm->input_dev);
		पूर्ण अन्यथा अगर (!(rc & RC_AGAIN)) अणु
			/* We need high frequency updates only जबतक
			* pen is करोwn, the user never will be able to
			* touch screen faster than a few बार per
			* second... On the other hand, when the user
			* is actively working with the touchscreen we
			* करोn't want to lose the quick response. So we
			* will slowly increase sleep समय after the
			* pen is up and quicky restore it to ~one task
			* चयन when pen is करोwn again.
			*/
			अगर (wm->ts_पढ़ोer_पूर्णांकerval < HZ / 10)
				wm->ts_पढ़ोer_पूर्णांकerval++;
		पूर्ण

	पूर्ण अन्यथा अगर (rc & RC_VALID) अणु
		dev_dbg(wm->dev,
			"pen down: x=%x:%d, y=%x:%d, pressure=%x:%d\n",
			data.x >> 12, data.x & 0xfff, data.y >> 12,
			data.y & 0xfff, data.p >> 12, data.p & 0xfff);

		अगर (असल_x[0] > (data.x & 0xfff) ||
		    असल_x[1] < (data.x & 0xfff) ||
		    असल_y[0] > (data.y & 0xfff) ||
		    असल_y[1] < (data.y & 0xfff)) अणु
			dev_dbg(wm->dev, "Measurement out of range, dropping it\n");
			rc = RC_AGAIN;
			जाओ out;
		पूर्ण

		input_report_असल(wm->input_dev, ABS_X, data.x & 0xfff);
		input_report_असल(wm->input_dev, ABS_Y, data.y & 0xfff);
		input_report_असल(wm->input_dev, ABS_PRESSURE, data.p & 0xfff);
		input_report_key(wm->input_dev, BTN_TOUCH, 1);
		input_sync(wm->input_dev);
		wm->pen_is_करोwn = 1;
		wm->ts_पढ़ोer_पूर्णांकerval = wm->ts_पढ़ोer_min_पूर्णांकerval;
	पूर्ण अन्यथा अगर (rc & RC_PENDOWN) अणु
		dev_dbg(wm->dev, "pen down\n");
		wm->pen_is_करोwn = 1;
		wm->ts_पढ़ोer_पूर्णांकerval = wm->ts_पढ़ोer_min_पूर्णांकerval;
	पूर्ण

out:
	mutex_unlock(&wm->codec_mutex);
	वापस rc;
पूर्ण

/*
* The touchscreen sample पढ़ोer.
*/
अटल व्योम wm97xx_ts_पढ़ोer(काष्ठा work_काष्ठा *work)
अणु
	पूर्णांक rc;
	काष्ठा wm97xx *wm = container_of(work, काष्ठा wm97xx, ts_पढ़ोer.work);

	BUG_ON(!wm->codec);

	करो अणु
		rc = wm97xx_पढ़ो_samples(wm);
	पूर्ण जबतक (rc & RC_AGAIN);

	अगर (wm->pen_is_करोwn || !wm->pen_irq)
		queue_delayed_work(wm->ts_workq, &wm->ts_पढ़ोer,
				   wm->ts_पढ़ोer_पूर्णांकerval);
पूर्ण

/**
 * wm97xx_ts_input_खोलो - Open the touch screen input device.
 * @idev:	Input device to be खोलोed.
 *
 * Called by the input sub प्रणाली to खोलो a wm97xx touchscreen device.
 * Starts the touchscreen thपढ़ो and touch digitiser.
 */
अटल पूर्णांक wm97xx_ts_input_खोलो(काष्ठा input_dev *idev)
अणु
	काष्ठा wm97xx *wm = input_get_drvdata(idev);

	wm->ts_workq = alloc_ordered_workqueue("kwm97xx", 0);
	अगर (wm->ts_workq == शून्य) अणु
		dev_err(wm->dev,
			"Failed to create workqueue\n");
		वापस -EINVAL;
	पूर्ण

	/* start digitiser */
	अगर (wm->mach_ops && wm->mach_ops->acc_enabled)
		wm->codec->acc_enable(wm, 1);
	wm->codec->dig_enable(wm, 1);

	INIT_DELAYED_WORK(&wm->ts_पढ़ोer, wm97xx_ts_पढ़ोer);
	INIT_WORK(&wm->pen_event_work, wm97xx_pen_irq_worker);

	wm->ts_पढ़ोer_min_पूर्णांकerval = HZ >= 100 ? HZ / 100 : 1;
	अगर (wm->ts_पढ़ोer_min_पूर्णांकerval < 1)
		wm->ts_पढ़ोer_min_पूर्णांकerval = 1;
	wm->ts_पढ़ोer_पूर्णांकerval = wm->ts_पढ़ोer_min_पूर्णांकerval;

	wm->pen_is_करोwn = 0;
	अगर (wm->pen_irq)
		wm97xx_init_pen_irq(wm);
	अन्यथा
		dev_err(wm->dev, "No IRQ specified\n");

	/* If we either करोn't have an पूर्णांकerrupt क्रम pen करोwn events or
	 * failed to acquire it then we need to poll.
	 */
	अगर (wm->pen_irq == 0)
		queue_delayed_work(wm->ts_workq, &wm->ts_पढ़ोer,
				   wm->ts_पढ़ोer_पूर्णांकerval);

	वापस 0;
पूर्ण

/**
 * wm97xx_ts_input_बंद - Close the touch screen input device.
 * @idev:	Input device to be बंदd.
 *
 * Called by the input sub प्रणाली to बंद a wm97xx touchscreen
 * device.  Kills the touchscreen thपढ़ो and stops the touch
 * digitiser.
 */

अटल व्योम wm97xx_ts_input_बंद(काष्ठा input_dev *idev)
अणु
	काष्ठा wm97xx *wm = input_get_drvdata(idev);
	u16 reg;

	अगर (wm->pen_irq) अणु
		/* Return the पूर्णांकerrupt to GPIO usage (disabling it) */
		अगर (wm->id != WM9705_ID2) अणु
			BUG_ON(!wm->mach_ops->irq_gpio);
			reg = wm97xx_reg_पढ़ो(wm, AC97_MISC_AFE);
			wm97xx_reg_ग_लिखो(wm, AC97_MISC_AFE,
					 reg | wm->mach_ops->irq_gpio);
		पूर्ण

		मुक्त_irq(wm->pen_irq, wm);
	पूर्ण

	wm->pen_is_करोwn = 0;

	/* Balance out पूर्णांकerrupt disables/enables */
	अगर (cancel_work_sync(&wm->pen_event_work))
		wm->mach_ops->irq_enable(wm, 1);

	/* ts_पढ़ोer rearms itself so we need to explicitly stop it
	 * beक्रमe we destroy the workqueue.
	 */
	cancel_delayed_work_sync(&wm->ts_पढ़ोer);

	destroy_workqueue(wm->ts_workq);

	/* stop digitiser */
	wm->codec->dig_enable(wm, 0);
	अगर (wm->mach_ops && wm->mach_ops->acc_enabled)
		wm->codec->acc_enable(wm, 0);
पूर्ण

अटल पूर्णांक wm97xx_रेजिस्टर_touch(काष्ठा wm97xx *wm)
अणु
	काष्ठा wm97xx_pdata *pdata = dev_get_platdata(wm->dev);
	पूर्णांक ret;

	wm->input_dev = devm_input_allocate_device(wm->dev);
	अगर (wm->input_dev == शून्य)
		वापस -ENOMEM;

	/* set up touch configuration */
	wm->input_dev->name = "wm97xx touchscreen";
	wm->input_dev->phys = "wm97xx";
	wm->input_dev->खोलो = wm97xx_ts_input_खोलो;
	wm->input_dev->बंद = wm97xx_ts_input_बंद;

	__set_bit(EV_ABS, wm->input_dev->evbit);
	__set_bit(EV_KEY, wm->input_dev->evbit);
	__set_bit(BTN_TOUCH, wm->input_dev->keybit);

	input_set_असल_params(wm->input_dev, ABS_X, असल_x[0], असल_x[1],
			     असल_x[2], 0);
	input_set_असल_params(wm->input_dev, ABS_Y, असल_y[0], असल_y[1],
			     असल_y[2], 0);
	input_set_असल_params(wm->input_dev, ABS_PRESSURE, असल_p[0], असल_p[1],
			     असल_p[2], 0);

	input_set_drvdata(wm->input_dev, wm);
	wm->input_dev->dev.parent = wm->dev;

	ret = input_रेजिस्टर_device(wm->input_dev);
	अगर (ret)
		वापस ret;

	/*
	 * रेजिस्टर our extended touch device (क्रम machine specअगरic
	 * extensions)
	 */
	wm->touch_dev = platक्रमm_device_alloc("wm97xx-touch", -1);
	अगर (!wm->touch_dev) अणु
		ret = -ENOMEM;
		जाओ touch_err;
	पूर्ण
	platक्रमm_set_drvdata(wm->touch_dev, wm);
	wm->touch_dev->dev.parent = wm->dev;
	wm->touch_dev->dev.platक्रमm_data = pdata;
	ret = platक्रमm_device_add(wm->touch_dev);
	अगर (ret < 0)
		जाओ touch_reg_err;

	वापस 0;
touch_reg_err:
	platक्रमm_device_put(wm->touch_dev);
touch_err:
	input_unरेजिस्टर_device(wm->input_dev);
	wm->input_dev = शून्य;

	वापस ret;
पूर्ण

अटल व्योम wm97xx_unरेजिस्टर_touch(काष्ठा wm97xx *wm)
अणु
	platक्रमm_device_unरेजिस्टर(wm->touch_dev);
	input_unरेजिस्टर_device(wm->input_dev);
	wm->input_dev = शून्य;
पूर्ण

अटल पूर्णांक _wm97xx_probe(काष्ठा wm97xx *wm)
अणु
	पूर्णांक id = 0;

	mutex_init(&wm->codec_mutex);
	dev_set_drvdata(wm->dev, wm);

	/* check that we have a supported codec */
	id = wm97xx_reg_पढ़ो(wm, AC97_VENDOR_ID1);
	अगर (id != WM97XX_ID1) अणु
		dev_err(wm->dev,
			"Device with vendor %04x is not a wm97xx\n", id);
		वापस -ENODEV;
	पूर्ण

	wm->id = wm97xx_reg_पढ़ो(wm, AC97_VENDOR_ID2);

	wm->variant = WM97xx_GENERIC;

	dev_info(wm->dev, "detected a wm97%02x codec\n", wm->id & 0xff);

	चयन (wm->id & 0xff) अणु
#अगर_घोषित CONFIG_TOUCHSCREEN_WM9705
	हाल 0x05:
		wm->codec = &wm9705_codec;
		अवरोध;
#पूर्ण_अगर
#अगर_घोषित CONFIG_TOUCHSCREEN_WM9712
	हाल 0x12:
		wm->codec = &wm9712_codec;
		अवरोध;
#पूर्ण_अगर
#अगर_घोषित CONFIG_TOUCHSCREEN_WM9713
	हाल 0x13:
		wm->codec = &wm9713_codec;
		अवरोध;
#पूर्ण_अगर
	शेष:
		dev_err(wm->dev, "Support for wm97%02x not compiled in.\n",
			wm->id & 0xff);
		वापस -ENODEV;
	पूर्ण

	/* set up physical अक्षरacteristics */
	wm->codec->phy_init(wm);

	/* load gpio cache */
	wm->gpio[0] = wm97xx_reg_पढ़ो(wm, AC97_GPIO_CFG);
	wm->gpio[1] = wm97xx_reg_पढ़ो(wm, AC97_GPIO_POLARITY);
	wm->gpio[2] = wm97xx_reg_पढ़ो(wm, AC97_GPIO_STICKY);
	wm->gpio[3] = wm97xx_reg_पढ़ो(wm, AC97_GPIO_WAKEUP);
	wm->gpio[4] = wm97xx_reg_पढ़ो(wm, AC97_GPIO_STATUS);
	wm->gpio[5] = wm97xx_reg_पढ़ो(wm, AC97_MISC_AFE);

	वापस wm97xx_रेजिस्टर_touch(wm);
पूर्ण

अटल व्योम wm97xx_हटाओ_battery(काष्ठा wm97xx *wm)
अणु
	platक्रमm_device_unरेजिस्टर(wm->battery_dev);
पूर्ण

अटल पूर्णांक wm97xx_add_battery(काष्ठा wm97xx *wm,
			      काष्ठा wm97xx_batt_pdata *pdata)
अणु
	पूर्णांक ret;

	wm->battery_dev = platक्रमm_device_alloc("wm97xx-battery", -1);
	अगर (!wm->battery_dev)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(wm->battery_dev, wm);
	wm->battery_dev->dev.parent = wm->dev;
	wm->battery_dev->dev.platक्रमm_data = pdata;
	ret = platक्रमm_device_add(wm->battery_dev);
	अगर (ret)
		platक्रमm_device_put(wm->battery_dev);

	वापस ret;
पूर्ण

अटल पूर्णांक wm97xx_probe(काष्ठा device *dev)
अणु
	काष्ठा wm97xx *wm;
	पूर्णांक ret;
	काष्ठा wm97xx_pdata *pdata = dev_get_platdata(dev);

	wm = devm_kzalloc(dev, माप(काष्ठा wm97xx), GFP_KERNEL);
	अगर (!wm)
		वापस -ENOMEM;

	wm->dev = dev;
	wm->ac97 = to_ac97_t(dev);

	ret =  _wm97xx_probe(wm);
	अगर (ret)
		वापस ret;

	ret = wm97xx_add_battery(wm, pdata ? pdata->batt_pdata : शून्य);
	अगर (ret < 0)
		जाओ batt_err;

	वापस ret;

batt_err:
	wm97xx_unरेजिस्टर_touch(wm);
	वापस ret;
पूर्ण

अटल पूर्णांक wm97xx_हटाओ(काष्ठा device *dev)
अणु
	काष्ठा wm97xx *wm = dev_get_drvdata(dev);

	wm97xx_हटाओ_battery(wm);
	wm97xx_unरेजिस्टर_touch(wm);

	वापस 0;
पूर्ण

अटल पूर्णांक wm97xx_mfd_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा wm97xx *wm;
	काष्ठा wm97xx_platक्रमm_data *mfd_pdata = dev_get_platdata(&pdev->dev);
	पूर्णांक ret;

	wm = devm_kzalloc(&pdev->dev, माप(काष्ठा wm97xx), GFP_KERNEL);
	अगर (!wm)
		वापस -ENOMEM;

	wm->dev = &pdev->dev;
	wm->ac97 = mfd_pdata->ac97;

	ret =  _wm97xx_probe(wm);
	अगर (ret)
		वापस ret;

	ret = wm97xx_add_battery(wm, mfd_pdata->batt_pdata);
	अगर (ret < 0)
		जाओ batt_err;

	वापस ret;

batt_err:
	wm97xx_unरेजिस्टर_touch(wm);
	वापस ret;
पूर्ण

अटल पूर्णांक wm97xx_mfd_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	वापस wm97xx_हटाओ(&pdev->dev);
पूर्ण

अटल पूर्णांक __maybe_unused wm97xx_suspend(काष्ठा device *dev)
अणु
	काष्ठा wm97xx *wm = dev_get_drvdata(dev);
	u16 reg;
	पूर्णांक suspend_mode;

	अगर (device_may_wakeup(&wm->input_dev->dev))
		suspend_mode = wm->suspend_mode;
	अन्यथा
		suspend_mode = 0;

	mutex_lock(&wm->input_dev->mutex);
	अगर (input_device_enabled(wm->input_dev))
		cancel_delayed_work_sync(&wm->ts_पढ़ोer);

	/* Power करोwn the digitiser (bypassing the cache क्रम resume) */
	reg = wm97xx_reg_पढ़ो(wm, AC97_WM97XX_DIGITISER2);
	reg &= ~WM97XX_PRP_DET_DIG;
	अगर (input_device_enabled(wm->input_dev))
		reg |= suspend_mode;
	wm->ac97->bus->ops->ग_लिखो(wm->ac97, AC97_WM97XX_DIGITISER2, reg);

	/* WM9713 has an additional घातer bit - turn it off अगर there
	 * are no users or अगर suspend mode is zero. */
	अगर (wm->id == WM9713_ID2 &&
	    (!input_device_enabled(wm->input_dev) || !suspend_mode)) अणु
		reg = wm97xx_reg_पढ़ो(wm, AC97_EXTENDED_MID) | 0x8000;
		wm97xx_reg_ग_लिखो(wm, AC97_EXTENDED_MID, reg);
	पूर्ण
	mutex_unlock(&wm->input_dev->mutex);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused wm97xx_resume(काष्ठा device *dev)
अणु
	काष्ठा wm97xx *wm = dev_get_drvdata(dev);

	mutex_lock(&wm->input_dev->mutex);
	/* restore digitiser and gpios */
	अगर (wm->id == WM9713_ID2) अणु
		wm97xx_reg_ग_लिखो(wm, AC97_WM9713_DIG1, wm->dig[0]);
		wm97xx_reg_ग_लिखो(wm, 0x5a, wm->misc);
		अगर (input_device_enabled(wm->input_dev)) अणु
			u16 reg;
			reg = wm97xx_reg_पढ़ो(wm, AC97_EXTENDED_MID) & 0x7fff;
			wm97xx_reg_ग_लिखो(wm, AC97_EXTENDED_MID, reg);
		पूर्ण
	पूर्ण

	wm97xx_reg_ग_लिखो(wm, AC97_WM9713_DIG2, wm->dig[1]);
	wm97xx_reg_ग_लिखो(wm, AC97_WM9713_DIG3, wm->dig[2]);

	wm97xx_reg_ग_लिखो(wm, AC97_GPIO_CFG, wm->gpio[0]);
	wm97xx_reg_ग_लिखो(wm, AC97_GPIO_POLARITY, wm->gpio[1]);
	wm97xx_reg_ग_लिखो(wm, AC97_GPIO_STICKY, wm->gpio[2]);
	wm97xx_reg_ग_लिखो(wm, AC97_GPIO_WAKEUP, wm->gpio[3]);
	wm97xx_reg_ग_लिखो(wm, AC97_GPIO_STATUS, wm->gpio[4]);
	wm97xx_reg_ग_लिखो(wm, AC97_MISC_AFE, wm->gpio[5]);

	अगर (input_device_enabled(wm->input_dev) && !wm->pen_irq) अणु
		wm->ts_पढ़ोer_पूर्णांकerval = wm->ts_पढ़ोer_min_पूर्णांकerval;
		queue_delayed_work(wm->ts_workq, &wm->ts_पढ़ोer,
				   wm->ts_पढ़ोer_पूर्णांकerval);
	पूर्ण
	mutex_unlock(&wm->input_dev->mutex);

	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(wm97xx_pm_ops, wm97xx_suspend, wm97xx_resume);

/*
 * Machine specअगरic operations
 */
पूर्णांक wm97xx_रेजिस्टर_mach_ops(काष्ठा wm97xx *wm,
			     काष्ठा wm97xx_mach_ops *mach_ops)
अणु
	mutex_lock(&wm->codec_mutex);
	अगर (wm->mach_ops) अणु
		mutex_unlock(&wm->codec_mutex);
		वापस -EINVAL;
	पूर्ण
	wm->mach_ops = mach_ops;
	mutex_unlock(&wm->codec_mutex);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(wm97xx_रेजिस्टर_mach_ops);

व्योम wm97xx_unरेजिस्टर_mach_ops(काष्ठा wm97xx *wm)
अणु
	mutex_lock(&wm->codec_mutex);
	wm->mach_ops = शून्य;
	mutex_unlock(&wm->codec_mutex);
पूर्ण
EXPORT_SYMBOL_GPL(wm97xx_unरेजिस्टर_mach_ops);

अटल काष्ठा device_driver wm97xx_driver = अणु
	.name =		"wm97xx-ts",
#अगर_घोषित CONFIG_AC97_BUS
	.bus =		&ac97_bus_type,
#पूर्ण_अगर
	.owner =	THIS_MODULE,
	.probe =	wm97xx_probe,
	.हटाओ =	wm97xx_हटाओ,
	.pm =		&wm97xx_pm_ops,
पूर्ण;

अटल काष्ठा platक्रमm_driver wm97xx_mfd_driver = अणु
	.driver = अणु
		.name =		"wm97xx-ts",
		.pm =		&wm97xx_pm_ops,
	पूर्ण,
	.probe =	wm97xx_mfd_probe,
	.हटाओ =	wm97xx_mfd_हटाओ,
पूर्ण;

अटल पूर्णांक __init wm97xx_init(व्योम)
अणु
	पूर्णांक ret;

	ret = platक्रमm_driver_रेजिस्टर(&wm97xx_mfd_driver);
	अगर (ret)
		वापस ret;

	अगर (IS_BUILTIN(CONFIG_AC97_BUS))
		ret =  driver_रेजिस्टर(&wm97xx_driver);
	वापस ret;
पूर्ण

अटल व्योम __निकास wm97xx_निकास(व्योम)
अणु
	अगर (IS_BUILTIN(CONFIG_AC97_BUS))
		driver_unरेजिस्टर(&wm97xx_driver);
	platक्रमm_driver_unरेजिस्टर(&wm97xx_mfd_driver);
पूर्ण

module_init(wm97xx_init);
module_निकास(wm97xx_निकास);

/* Module inक्रमmation */
MODULE_AUTHOR("Liam Girdwood <lrg@slimlogic.co.uk>");
MODULE_DESCRIPTION("WM97xx Core - Touch Screen / AUX ADC / GPIO Driver");
MODULE_LICENSE("GPL");
