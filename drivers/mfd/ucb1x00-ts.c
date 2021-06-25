<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  Touchscreen driver क्रम UCB1x00-based touchscreens
 *
 *  Copyright (C) 2001 Russell King, All Rights Reserved.
 *  Copyright (C) 2005 Pavel Machek
 *
 * 21-Jan-2002 <jco@ict.es> :
 *
 * Added support क्रम synchronous A/D mode. This mode is useful to
 * aव्योम noise induced in the touchpanel by the LCD, provided that
 * the UCB1x00 has a valid LCD sync संकेत routed to its ADCSYNC pin.
 * It is important to note that the संकेत connected to the ADCSYNC
 * pin should provide pulses even when the LCD is blanked, otherwise
 * a pen touch needed to unblank the LCD will never be पढ़ो.
 */
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/sched.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/completion.h>
#समावेश <linux/delay.h>
#समावेश <linux/माला.स>
#समावेश <linux/input.h>
#समावेश <linux/device.h>
#समावेश <linux/मुक्तzer.h>
#समावेश <linux/slab.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/mfd/ucb1x00.h>

#समावेश <mach/collie.h>
#समावेश <यंत्र/mach-types.h>



काष्ठा ucb1x00_ts अणु
	काष्ठा input_dev	*idev;
	काष्ठा ucb1x00		*ucb;

	spinlock_t		irq_lock;
	अचिन्हित		irq_disabled;
	रुको_queue_head_t	irq_रुको;
	काष्ठा task_काष्ठा	*rtask;
	u16			x_res;
	u16			y_res;

	अचिन्हित पूर्णांक		adcsync:1;
पूर्ण;

अटल पूर्णांक adcsync;

अटल अंतरभूत व्योम ucb1x00_ts_evt_add(काष्ठा ucb1x00_ts *ts, u16 pressure, u16 x, u16 y)
अणु
	काष्ठा input_dev *idev = ts->idev;

	input_report_असल(idev, ABS_X, x);
	input_report_असल(idev, ABS_Y, y);
	input_report_असल(idev, ABS_PRESSURE, pressure);
	input_report_key(idev, BTN_TOUCH, 1);
	input_sync(idev);
पूर्ण

अटल अंतरभूत व्योम ucb1x00_ts_event_release(काष्ठा ucb1x00_ts *ts)
अणु
	काष्ठा input_dev *idev = ts->idev;

	input_report_असल(idev, ABS_PRESSURE, 0);
	input_report_key(idev, BTN_TOUCH, 0);
	input_sync(idev);
पूर्ण

/*
 * Switch to पूर्णांकerrupt mode.
 */
अटल अंतरभूत व्योम ucb1x00_ts_mode_पूर्णांक(काष्ठा ucb1x00_ts *ts)
अणु
	ucb1x00_reg_ग_लिखो(ts->ucb, UCB_TS_CR,
			UCB_TS_CR_TSMX_POW | UCB_TS_CR_TSPX_POW |
			UCB_TS_CR_TSMY_GND | UCB_TS_CR_TSPY_GND |
			UCB_TS_CR_MODE_INT);
पूर्ण

/*
 * Switch to pressure mode, and पढ़ो pressure.  We करोn't need to रुको
 * here, since both plates are being driven.
 */
अटल अंतरभूत अचिन्हित पूर्णांक ucb1x00_ts_पढ़ो_pressure(काष्ठा ucb1x00_ts *ts)
अणु
	अगर (machine_is_collie()) अणु
		ucb1x00_io_ग_लिखो(ts->ucb, COLLIE_TC35143_GPIO_TBL_CHK, 0);
		ucb1x00_reg_ग_लिखो(ts->ucb, UCB_TS_CR,
				  UCB_TS_CR_TSPX_POW | UCB_TS_CR_TSMX_POW |
				  UCB_TS_CR_MODE_POS | UCB_TS_CR_BIAS_ENA);

		udelay(55);

		वापस ucb1x00_adc_पढ़ो(ts->ucb, UCB_ADC_INP_AD2, ts->adcsync);
	पूर्ण अन्यथा अणु
		ucb1x00_reg_ग_लिखो(ts->ucb, UCB_TS_CR,
				  UCB_TS_CR_TSMX_POW | UCB_TS_CR_TSPX_POW |
				  UCB_TS_CR_TSMY_GND | UCB_TS_CR_TSPY_GND |
				  UCB_TS_CR_MODE_PRES | UCB_TS_CR_BIAS_ENA);

		वापस ucb1x00_adc_पढ़ो(ts->ucb, UCB_ADC_INP_TSPY, ts->adcsync);
	पूर्ण
पूर्ण

/*
 * Switch to X position mode and measure Y plate.  We चयन the plate
 * configuration in pressure mode, then चयन to position mode.  This
 * gives a faster response समय.  Even so, we need to रुको about 55us
 * क्रम things to stabilise.
 */
अटल अंतरभूत अचिन्हित पूर्णांक ucb1x00_ts_पढ़ो_xpos(काष्ठा ucb1x00_ts *ts)
अणु
	अगर (machine_is_collie())
		ucb1x00_io_ग_लिखो(ts->ucb, 0, COLLIE_TC35143_GPIO_TBL_CHK);
	अन्यथा अणु
		ucb1x00_reg_ग_लिखो(ts->ucb, UCB_TS_CR,
				  UCB_TS_CR_TSMX_GND | UCB_TS_CR_TSPX_POW |
				  UCB_TS_CR_MODE_PRES | UCB_TS_CR_BIAS_ENA);
		ucb1x00_reg_ग_लिखो(ts->ucb, UCB_TS_CR,
				  UCB_TS_CR_TSMX_GND | UCB_TS_CR_TSPX_POW |
				  UCB_TS_CR_MODE_PRES | UCB_TS_CR_BIAS_ENA);
	पूर्ण
	ucb1x00_reg_ग_लिखो(ts->ucb, UCB_TS_CR,
			UCB_TS_CR_TSMX_GND | UCB_TS_CR_TSPX_POW |
			UCB_TS_CR_MODE_POS | UCB_TS_CR_BIAS_ENA);

	udelay(55);

	वापस ucb1x00_adc_पढ़ो(ts->ucb, UCB_ADC_INP_TSPY, ts->adcsync);
पूर्ण

/*
 * Switch to Y position mode and measure X plate.  We चयन the plate
 * configuration in pressure mode, then चयन to position mode.  This
 * gives a faster response समय.  Even so, we need to रुको about 55us
 * क्रम things to stabilise.
 */
अटल अंतरभूत अचिन्हित पूर्णांक ucb1x00_ts_पढ़ो_ypos(काष्ठा ucb1x00_ts *ts)
अणु
	अगर (machine_is_collie())
		ucb1x00_io_ग_लिखो(ts->ucb, 0, COLLIE_TC35143_GPIO_TBL_CHK);
	अन्यथा अणु
		ucb1x00_reg_ग_लिखो(ts->ucb, UCB_TS_CR,
				  UCB_TS_CR_TSMY_GND | UCB_TS_CR_TSPY_POW |
				  UCB_TS_CR_MODE_PRES | UCB_TS_CR_BIAS_ENA);
		ucb1x00_reg_ग_लिखो(ts->ucb, UCB_TS_CR,
				  UCB_TS_CR_TSMY_GND | UCB_TS_CR_TSPY_POW |
				  UCB_TS_CR_MODE_PRES | UCB_TS_CR_BIAS_ENA);
	पूर्ण

	ucb1x00_reg_ग_लिखो(ts->ucb, UCB_TS_CR,
			UCB_TS_CR_TSMY_GND | UCB_TS_CR_TSPY_POW |
			UCB_TS_CR_MODE_POS | UCB_TS_CR_BIAS_ENA);

	udelay(55);

	वापस ucb1x00_adc_पढ़ो(ts->ucb, UCB_ADC_INP_TSPX, ts->adcsync);
पूर्ण

/*
 * Switch to X plate resistance mode.  Set MX to ground, PX to
 * supply.  Measure current.
 */
अटल अंतरभूत अचिन्हित पूर्णांक ucb1x00_ts_पढ़ो_xres(काष्ठा ucb1x00_ts *ts)
अणु
	ucb1x00_reg_ग_लिखो(ts->ucb, UCB_TS_CR,
			UCB_TS_CR_TSMX_GND | UCB_TS_CR_TSPX_POW |
			UCB_TS_CR_MODE_PRES | UCB_TS_CR_BIAS_ENA);
	वापस ucb1x00_adc_पढ़ो(ts->ucb, 0, ts->adcsync);
पूर्ण

/*
 * Switch to Y plate resistance mode.  Set MY to ground, PY to
 * supply.  Measure current.
 */
अटल अंतरभूत अचिन्हित पूर्णांक ucb1x00_ts_पढ़ो_yres(काष्ठा ucb1x00_ts *ts)
अणु
	ucb1x00_reg_ग_लिखो(ts->ucb, UCB_TS_CR,
			UCB_TS_CR_TSMY_GND | UCB_TS_CR_TSPY_POW |
			UCB_TS_CR_MODE_PRES | UCB_TS_CR_BIAS_ENA);
	वापस ucb1x00_adc_पढ़ो(ts->ucb, 0, ts->adcsync);
पूर्ण

अटल अंतरभूत पूर्णांक ucb1x00_ts_pen_करोwn(काष्ठा ucb1x00_ts *ts)
अणु
	अचिन्हित पूर्णांक val = ucb1x00_reg_पढ़ो(ts->ucb, UCB_TS_CR);

	अगर (machine_is_collie())
		वापस (!(val & (UCB_TS_CR_TSPX_LOW)));
	अन्यथा
		वापस (val & (UCB_TS_CR_TSPX_LOW | UCB_TS_CR_TSMX_LOW));
पूर्ण

/*
 * This is a RT kernel thपढ़ो that handles the ADC accesses
 * (मुख्यly so we can use semaphores in the UCB1200 core code
 * to serialise accesses to the ADC).
 */
अटल पूर्णांक ucb1x00_thपढ़ो(व्योम *_ts)
अणु
	काष्ठा ucb1x00_ts *ts = _ts;
	DECLARE_WAITQUEUE(रुको, current);
	bool frozen, ignore = false;
	पूर्णांक valid = 0;

	set_मुक्तzable();
	add_रुको_queue(&ts->irq_रुको, &रुको);
	जबतक (!kthपढ़ो_मुक्तzable_should_stop(&frozen)) अणु
		अचिन्हित पूर्णांक x, y, p;
		चिन्हित दीर्घ समयout;

		अगर (frozen)
			ignore = true;

		ucb1x00_adc_enable(ts->ucb);

		x = ucb1x00_ts_पढ़ो_xpos(ts);
		y = ucb1x00_ts_पढ़ो_ypos(ts);
		p = ucb1x00_ts_पढ़ो_pressure(ts);

		/*
		 * Switch back to पूर्णांकerrupt mode.
		 */
		ucb1x00_ts_mode_पूर्णांक(ts);
		ucb1x00_adc_disable(ts->ucb);

		msleep(10);

		ucb1x00_enable(ts->ucb);


		अगर (ucb1x00_ts_pen_करोwn(ts)) अणु
			set_current_state(TASK_INTERRUPTIBLE);

			spin_lock_irq(&ts->irq_lock);
			अगर (ts->irq_disabled) अणु
				ts->irq_disabled = 0;
				enable_irq(ts->ucb->irq_base + UCB_IRQ_TSPX);
			पूर्ण
			spin_unlock_irq(&ts->irq_lock);
			ucb1x00_disable(ts->ucb);

			/*
			 * If we spat out a valid sample set last समय,
			 * spit out a "pen off" sample here.
			 */
			अगर (valid) अणु
				ucb1x00_ts_event_release(ts);
				valid = 0;
			पूर्ण

			समयout = MAX_SCHEDULE_TIMEOUT;
		पूर्ण अन्यथा अणु
			ucb1x00_disable(ts->ucb);

			/*
			 * Filtering is policy.  Policy beदीर्घs in user
			 * space.  We thereक्रमe leave it to user space
			 * to करो any filtering they please.
			 */
			अगर (!ignore) अणु
				ucb1x00_ts_evt_add(ts, p, x, y);
				valid = 1;
			पूर्ण

			set_current_state(TASK_INTERRUPTIBLE);
			समयout = HZ / 100;
		पूर्ण

		schedule_समयout(समयout);
	पूर्ण

	हटाओ_रुको_queue(&ts->irq_रुको, &रुको);

	ts->rtask = शून्य;
	वापस 0;
पूर्ण

/*
 * We only detect touch screen _touches_ with this पूर्णांकerrupt
 * handler, and even then we just schedule our task.
 */
अटल irqवापस_t ucb1x00_ts_irq(पूर्णांक irq, व्योम *id)
अणु
	काष्ठा ucb1x00_ts *ts = id;

	spin_lock(&ts->irq_lock);
	ts->irq_disabled = 1;
	disable_irq_nosync(ts->ucb->irq_base + UCB_IRQ_TSPX);
	spin_unlock(&ts->irq_lock);
	wake_up(&ts->irq_रुको);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक ucb1x00_ts_खोलो(काष्ठा input_dev *idev)
अणु
	काष्ठा ucb1x00_ts *ts = input_get_drvdata(idev);
	अचिन्हित दीर्घ flags = 0;
	पूर्णांक ret = 0;

	BUG_ON(ts->rtask);

	अगर (machine_is_collie())
		flags = IRQF_TRIGGER_RISING;
	अन्यथा
		flags = IRQF_TRIGGER_FALLING;

	ts->irq_disabled = 0;

	init_रुकोqueue_head(&ts->irq_रुको);
	ret = request_irq(ts->ucb->irq_base + UCB_IRQ_TSPX, ucb1x00_ts_irq,
			  flags, "ucb1x00-ts", ts);
	अगर (ret < 0)
		जाओ out;

	/*
	 * If we करो this at all, we should allow the user to
	 * measure and पढ़ो the X and Y resistance at any समय.
	 */
	ucb1x00_adc_enable(ts->ucb);
	ts->x_res = ucb1x00_ts_पढ़ो_xres(ts);
	ts->y_res = ucb1x00_ts_पढ़ो_yres(ts);
	ucb1x00_adc_disable(ts->ucb);

	ts->rtask = kthपढ़ो_run(ucb1x00_thपढ़ो, ts, "ktsd");
	अगर (!IS_ERR(ts->rtask)) अणु
		ret = 0;
	पूर्ण अन्यथा अणु
		मुक्त_irq(ts->ucb->irq_base + UCB_IRQ_TSPX, ts);
		ts->rtask = शून्य;
		ret = -EFAULT;
	पूर्ण

 out:
	वापस ret;
पूर्ण

/*
 * Release touchscreen resources.  Disable IRQs.
 */
अटल व्योम ucb1x00_ts_बंद(काष्ठा input_dev *idev)
अणु
	काष्ठा ucb1x00_ts *ts = input_get_drvdata(idev);

	अगर (ts->rtask)
		kthपढ़ो_stop(ts->rtask);

	ucb1x00_enable(ts->ucb);
	मुक्त_irq(ts->ucb->irq_base + UCB_IRQ_TSPX, ts);
	ucb1x00_reg_ग_लिखो(ts->ucb, UCB_TS_CR, 0);
	ucb1x00_disable(ts->ucb);
पूर्ण


/*
 * Initialisation.
 */
अटल पूर्णांक ucb1x00_ts_add(काष्ठा ucb1x00_dev *dev)
अणु
	काष्ठा ucb1x00_ts *ts;
	काष्ठा input_dev *idev;
	पूर्णांक err;

	ts = kzalloc(माप(काष्ठा ucb1x00_ts), GFP_KERNEL);
	idev = input_allocate_device();
	अगर (!ts || !idev) अणु
		err = -ENOMEM;
		जाओ fail;
	पूर्ण

	ts->ucb = dev->ucb;
	ts->idev = idev;
	ts->adcsync = adcsync ? UCB_SYNC : UCB_NOSYNC;
	spin_lock_init(&ts->irq_lock);

	idev->name       = "Touchscreen panel";
	idev->id.product = ts->ucb->id;
	idev->खोलो       = ucb1x00_ts_खोलो;
	idev->बंद      = ucb1x00_ts_बंद;
	idev->dev.parent = &ts->ucb->dev;

	idev->evbit[0]   = BIT_MASK(EV_ABS) | BIT_MASK(EV_KEY);
	idev->keybit[BIT_WORD(BTN_TOUCH)] = BIT_MASK(BTN_TOUCH);

	input_set_drvdata(idev, ts);

	ucb1x00_adc_enable(ts->ucb);
	ts->x_res = ucb1x00_ts_पढ़ो_xres(ts);
	ts->y_res = ucb1x00_ts_पढ़ो_yres(ts);
	ucb1x00_adc_disable(ts->ucb);

	input_set_असल_params(idev, ABS_X, 0, ts->x_res, 0, 0);
	input_set_असल_params(idev, ABS_Y, 0, ts->y_res, 0, 0);
	input_set_असल_params(idev, ABS_PRESSURE, 0, 0, 0, 0);

	err = input_रेजिस्टर_device(idev);
	अगर (err)
		जाओ fail;

	dev->priv = ts;

	वापस 0;

 fail:
	input_मुक्त_device(idev);
	kमुक्त(ts);
	वापस err;
पूर्ण

अटल व्योम ucb1x00_ts_हटाओ(काष्ठा ucb1x00_dev *dev)
अणु
	काष्ठा ucb1x00_ts *ts = dev->priv;

	input_unरेजिस्टर_device(ts->idev);
	kमुक्त(ts);
पूर्ण

अटल काष्ठा ucb1x00_driver ucb1x00_ts_driver = अणु
	.add		= ucb1x00_ts_add,
	.हटाओ		= ucb1x00_ts_हटाओ,
पूर्ण;

अटल पूर्णांक __init ucb1x00_ts_init(व्योम)
अणु
	वापस ucb1x00_रेजिस्टर_driver(&ucb1x00_ts_driver);
पूर्ण

अटल व्योम __निकास ucb1x00_ts_निकास(व्योम)
अणु
	ucb1x00_unरेजिस्टर_driver(&ucb1x00_ts_driver);
पूर्ण

module_param(adcsync, पूर्णांक, 0444);
module_init(ucb1x00_ts_init);
module_निकास(ucb1x00_ts_निकास);

MODULE_AUTHOR("Russell King <rmk@arm.linux.org.uk>");
MODULE_DESCRIPTION("UCB1x00 touchscreen driver");
MODULE_LICENSE("GPL");
