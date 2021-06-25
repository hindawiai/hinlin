<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  Philips UCB1400 touchscreen driver
 *
 *  Author:	Nicolas Pitre
 *  Created:	September 25, 2006
 *  Copyright:	MontaVista Software, Inc.
 *
 * Spliting करोne by: Marek Vasut <marek.vasut@gmail.com>
 * If something करोesn't work and it worked beक्रमe spliting, e-mail me,
 * करोnt bother Nicolas please ;-)
 *
 * This code is heavily based on ucb1x00-*.c copyrighted by Russell King
 * covering the UCB1100, UCB1200 and UCB1300..  Support क्रम the UCB1400 has
 * been made separate from ucb1x00-core/ucb1x00-ts on Russell's request.
 */

#समावेश <linux/module.h>
#समावेश <linux/delay.h>
#समावेश <linux/sched.h>
#समावेश <linux/रुको.h>
#समावेश <linux/input.h>
#समावेश <linux/device.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/ucb1400.h>

#घोषणा UCB1400_TS_POLL_PERIOD	10 /* ms */

अटल bool adcsync;
अटल पूर्णांक ts_delay = 55; /* us */
अटल पूर्णांक ts_delay_pressure;	/* us */

/* Switch to पूर्णांकerrupt mode. */
अटल व्योम ucb1400_ts_mode_पूर्णांक(काष्ठा ucb1400_ts *ucb)
अणु
	ucb1400_reg_ग_लिखो(ucb->ac97, UCB_TS_CR,
			UCB_TS_CR_TSMX_POW | UCB_TS_CR_TSPX_POW |
			UCB_TS_CR_TSMY_GND | UCB_TS_CR_TSPY_GND |
			UCB_TS_CR_MODE_INT);
पूर्ण

/*
 * Switch to pressure mode, and पढ़ो pressure.  We करोn't need to रुको
 * here, since both plates are being driven.
 */
अटल अचिन्हित पूर्णांक ucb1400_ts_पढ़ो_pressure(काष्ठा ucb1400_ts *ucb)
अणु
	ucb1400_reg_ग_लिखो(ucb->ac97, UCB_TS_CR,
			UCB_TS_CR_TSMX_POW | UCB_TS_CR_TSPX_POW |
			UCB_TS_CR_TSMY_GND | UCB_TS_CR_TSPY_GND |
			UCB_TS_CR_MODE_PRES | UCB_TS_CR_BIAS_ENA);

	udelay(ts_delay_pressure);

	वापस ucb1400_adc_पढ़ो(ucb->ac97, UCB_ADC_INP_TSPY, adcsync);
पूर्ण

/*
 * Switch to X position mode and measure Y plate.  We चयन the plate
 * configuration in pressure mode, then चयन to position mode.  This
 * gives a faster response समय.  Even so, we need to रुको about 55us
 * क्रम things to stabilise.
 */
अटल अचिन्हित पूर्णांक ucb1400_ts_पढ़ो_xpos(काष्ठा ucb1400_ts *ucb)
अणु
	ucb1400_reg_ग_लिखो(ucb->ac97, UCB_TS_CR,
			UCB_TS_CR_TSMX_GND | UCB_TS_CR_TSPX_POW |
			UCB_TS_CR_MODE_PRES | UCB_TS_CR_BIAS_ENA);
	ucb1400_reg_ग_लिखो(ucb->ac97, UCB_TS_CR,
			UCB_TS_CR_TSMX_GND | UCB_TS_CR_TSPX_POW |
			UCB_TS_CR_MODE_PRES | UCB_TS_CR_BIAS_ENA);
	ucb1400_reg_ग_लिखो(ucb->ac97, UCB_TS_CR,
			UCB_TS_CR_TSMX_GND | UCB_TS_CR_TSPX_POW |
			UCB_TS_CR_MODE_POS | UCB_TS_CR_BIAS_ENA);

	udelay(ts_delay);

	वापस ucb1400_adc_पढ़ो(ucb->ac97, UCB_ADC_INP_TSPY, adcsync);
पूर्ण

/*
 * Switch to Y position mode and measure X plate.  We चयन the plate
 * configuration in pressure mode, then चयन to position mode.  This
 * gives a faster response समय.  Even so, we need to रुको about 55us
 * क्रम things to stabilise.
 */
अटल पूर्णांक ucb1400_ts_पढ़ो_ypos(काष्ठा ucb1400_ts *ucb)
अणु
	ucb1400_reg_ग_लिखो(ucb->ac97, UCB_TS_CR,
			UCB_TS_CR_TSMY_GND | UCB_TS_CR_TSPY_POW |
			UCB_TS_CR_MODE_PRES | UCB_TS_CR_BIAS_ENA);
	ucb1400_reg_ग_लिखो(ucb->ac97, UCB_TS_CR,
			UCB_TS_CR_TSMY_GND | UCB_TS_CR_TSPY_POW |
			UCB_TS_CR_MODE_PRES | UCB_TS_CR_BIAS_ENA);
	ucb1400_reg_ग_लिखो(ucb->ac97, UCB_TS_CR,
			UCB_TS_CR_TSMY_GND | UCB_TS_CR_TSPY_POW |
			UCB_TS_CR_MODE_POS | UCB_TS_CR_BIAS_ENA);

	udelay(ts_delay);

	वापस ucb1400_adc_पढ़ो(ucb->ac97, UCB_ADC_INP_TSPX, adcsync);
पूर्ण

/*
 * Switch to X plate resistance mode.  Set MX to ground, PX to
 * supply.  Measure current.
 */
अटल अचिन्हित पूर्णांक ucb1400_ts_पढ़ो_xres(काष्ठा ucb1400_ts *ucb)
अणु
	ucb1400_reg_ग_लिखो(ucb->ac97, UCB_TS_CR,
			UCB_TS_CR_TSMX_GND | UCB_TS_CR_TSPX_POW |
			UCB_TS_CR_MODE_PRES | UCB_TS_CR_BIAS_ENA);
	वापस ucb1400_adc_पढ़ो(ucb->ac97, 0, adcsync);
पूर्ण

/*
 * Switch to Y plate resistance mode.  Set MY to ground, PY to
 * supply.  Measure current.
 */
अटल अचिन्हित पूर्णांक ucb1400_ts_पढ़ो_yres(काष्ठा ucb1400_ts *ucb)
अणु
	ucb1400_reg_ग_लिखो(ucb->ac97, UCB_TS_CR,
			UCB_TS_CR_TSMY_GND | UCB_TS_CR_TSPY_POW |
			UCB_TS_CR_MODE_PRES | UCB_TS_CR_BIAS_ENA);
	वापस ucb1400_adc_पढ़ो(ucb->ac97, 0, adcsync);
पूर्ण

अटल पूर्णांक ucb1400_ts_pen_up(काष्ठा ucb1400_ts *ucb)
अणु
	अचिन्हित लघु val = ucb1400_reg_पढ़ो(ucb->ac97, UCB_TS_CR);

	वापस val & (UCB_TS_CR_TSPX_LOW | UCB_TS_CR_TSMX_LOW);
पूर्ण

अटल व्योम ucb1400_ts_irq_enable(काष्ठा ucb1400_ts *ucb)
अणु
	ucb1400_reg_ग_लिखो(ucb->ac97, UCB_IE_CLEAR, UCB_IE_TSPX);
	ucb1400_reg_ग_लिखो(ucb->ac97, UCB_IE_CLEAR, 0);
	ucb1400_reg_ग_लिखो(ucb->ac97, UCB_IE_FAL, UCB_IE_TSPX);
पूर्ण

अटल व्योम ucb1400_ts_irq_disable(काष्ठा ucb1400_ts *ucb)
अणु
	ucb1400_reg_ग_लिखो(ucb->ac97, UCB_IE_FAL, 0);
पूर्ण

अटल व्योम ucb1400_ts_report_event(काष्ठा input_dev *idev, u16 pressure, u16 x, u16 y)
अणु
	input_report_असल(idev, ABS_X, x);
	input_report_असल(idev, ABS_Y, y);
	input_report_असल(idev, ABS_PRESSURE, pressure);
	input_report_key(idev, BTN_TOUCH, 1);
	input_sync(idev);
पूर्ण

अटल व्योम ucb1400_ts_event_release(काष्ठा input_dev *idev)
अणु
	input_report_असल(idev, ABS_PRESSURE, 0);
	input_report_key(idev, BTN_TOUCH, 0);
	input_sync(idev);
पूर्ण

अटल व्योम ucb1400_clear_pending_irq(काष्ठा ucb1400_ts *ucb)
अणु
	अचिन्हित पूर्णांक isr;

	isr = ucb1400_reg_पढ़ो(ucb->ac97, UCB_IE_STATUS);
	ucb1400_reg_ग_लिखो(ucb->ac97, UCB_IE_CLEAR, isr);
	ucb1400_reg_ग_लिखो(ucb->ac97, UCB_IE_CLEAR, 0);

	अगर (isr & UCB_IE_TSPX)
		ucb1400_ts_irq_disable(ucb);
	अन्यथा
		dev_dbg(&ucb->ts_idev->dev,
			"ucb1400: unexpected IE_STATUS = %#x\n", isr);
पूर्ण

/*
 * A restriction with पूर्णांकerrupts exists when using the ucb1400, as
 * the codec पढ़ो/ग_लिखो routines may sleep जबतक रुकोing क्रम codec
 * access completion and uses semaphores क्रम access control to the
 * AC97 bus. Thereक्रमe the driver is क्रमced to use thपढ़ोed पूर्णांकerrupt
 * handler.
 */
अटल irqवापस_t ucb1400_irq(पूर्णांक irqnr, व्योम *devid)
अणु
	काष्ठा ucb1400_ts *ucb = devid;
	अचिन्हित पूर्णांक x, y, p;
	bool penup;

	अगर (unlikely(irqnr != ucb->irq))
		वापस IRQ_NONE;

	ucb1400_clear_pending_irq(ucb);

	/* Start with a small delay beक्रमe checking penकरोwn state */
	msleep(UCB1400_TS_POLL_PERIOD);

	जबतक (!ucb->stopped && !(penup = ucb1400_ts_pen_up(ucb))) अणु

		ucb1400_adc_enable(ucb->ac97);
		x = ucb1400_ts_पढ़ो_xpos(ucb);
		y = ucb1400_ts_पढ़ो_ypos(ucb);
		p = ucb1400_ts_पढ़ो_pressure(ucb);
		ucb1400_adc_disable(ucb->ac97);

		ucb1400_ts_report_event(ucb->ts_idev, p, x, y);

		रुको_event_समयout(ucb->ts_रुको, ucb->stopped,
				   msecs_to_jअगरfies(UCB1400_TS_POLL_PERIOD));
	पूर्ण

	ucb1400_ts_event_release(ucb->ts_idev);

	अगर (!ucb->stopped) अणु
		/* Switch back to पूर्णांकerrupt mode. */
		ucb1400_ts_mode_पूर्णांक(ucb);
		ucb1400_ts_irq_enable(ucb);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम ucb1400_ts_stop(काष्ठा ucb1400_ts *ucb)
अणु
	/* Signal IRQ thपढ़ो to stop polling and disable the handler. */
	ucb->stopped = true;
	mb();
	wake_up(&ucb->ts_रुको);
	disable_irq(ucb->irq);

	ucb1400_ts_irq_disable(ucb);
	ucb1400_reg_ग_लिखो(ucb->ac97, UCB_TS_CR, 0);
पूर्ण

/* Must be called with ts->lock held */
अटल व्योम ucb1400_ts_start(काष्ठा ucb1400_ts *ucb)
अणु
	/* Tell IRQ thपढ़ो that it may poll the device. */
	ucb->stopped = false;
	mb();

	ucb1400_ts_mode_पूर्णांक(ucb);
	ucb1400_ts_irq_enable(ucb);

	enable_irq(ucb->irq);
पूर्ण

अटल पूर्णांक ucb1400_ts_खोलो(काष्ठा input_dev *idev)
अणु
	काष्ठा ucb1400_ts *ucb = input_get_drvdata(idev);

	ucb1400_ts_start(ucb);

	वापस 0;
पूर्ण

अटल व्योम ucb1400_ts_बंद(काष्ठा input_dev *idev)
अणु
	काष्ठा ucb1400_ts *ucb = input_get_drvdata(idev);

	ucb1400_ts_stop(ucb);
पूर्ण

#अगर_अघोषित NO_IRQ
#घोषणा NO_IRQ	0
#पूर्ण_अगर

/*
 * Try to probe our पूर्णांकerrupt, rather than relying on lots of
 * hard-coded machine dependencies.
 */
अटल पूर्णांक ucb1400_ts_detect_irq(काष्ठा ucb1400_ts *ucb,
					   काष्ठा platक्रमm_device *pdev)
अणु
	अचिन्हित दीर्घ mask, समयout;

	mask = probe_irq_on();

	/* Enable the ADC पूर्णांकerrupt. */
	ucb1400_reg_ग_लिखो(ucb->ac97, UCB_IE_RIS, UCB_IE_ADC);
	ucb1400_reg_ग_लिखो(ucb->ac97, UCB_IE_FAL, UCB_IE_ADC);
	ucb1400_reg_ग_लिखो(ucb->ac97, UCB_IE_CLEAR, 0xffff);
	ucb1400_reg_ग_लिखो(ucb->ac97, UCB_IE_CLEAR, 0);

	/* Cause an ADC पूर्णांकerrupt. */
	ucb1400_reg_ग_लिखो(ucb->ac97, UCB_ADC_CR, UCB_ADC_ENA);
	ucb1400_reg_ग_लिखो(ucb->ac97, UCB_ADC_CR, UCB_ADC_ENA | UCB_ADC_START);

	/* Wait क्रम the conversion to complete. */
	समयout = jअगरfies + HZ/2;
	जबतक (!(ucb1400_reg_पढ़ो(ucb->ac97, UCB_ADC_DATA) &
						UCB_ADC_DAT_VALID)) अणु
		cpu_relax();
		अगर (समय_after(jअगरfies, समयout)) अणु
			dev_err(&pdev->dev, "timed out in IRQ probe\n");
			probe_irq_off(mask);
			वापस -ENODEV;
		पूर्ण
	पूर्ण
	ucb1400_reg_ग_लिखो(ucb->ac97, UCB_ADC_CR, 0);

	/* Disable and clear पूर्णांकerrupt. */
	ucb1400_reg_ग_लिखो(ucb->ac97, UCB_IE_RIS, 0);
	ucb1400_reg_ग_लिखो(ucb->ac97, UCB_IE_FAL, 0);
	ucb1400_reg_ग_लिखो(ucb->ac97, UCB_IE_CLEAR, 0xffff);
	ucb1400_reg_ग_लिखो(ucb->ac97, UCB_IE_CLEAR, 0);

	/* Read triggered पूर्णांकerrupt. */
	ucb->irq = probe_irq_off(mask);
	अगर (ucb->irq < 0 || ucb->irq == NO_IRQ)
		वापस -ENODEV;

	वापस 0;
पूर्ण

अटल पूर्णांक ucb1400_ts_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा ucb1400_ts *ucb = dev_get_platdata(&pdev->dev);
	पूर्णांक error, x_res, y_res;
	u16 fcsr;

	ucb->ts_idev = input_allocate_device();
	अगर (!ucb->ts_idev) अणु
		error = -ENOMEM;
		जाओ err;
	पूर्ण

	/* Only in हाल the IRQ line wasn't supplied, try detecting it */
	अगर (ucb->irq < 0) अणु
		error = ucb1400_ts_detect_irq(ucb, pdev);
		अगर (error) अणु
			dev_err(&pdev->dev, "IRQ probe failed\n");
			जाओ err_मुक्त_devs;
		पूर्ण
	पूर्ण
	dev_dbg(&pdev->dev, "found IRQ %d\n", ucb->irq);

	init_रुकोqueue_head(&ucb->ts_रुको);

	input_set_drvdata(ucb->ts_idev, ucb);

	ucb->ts_idev->dev.parent	= &pdev->dev;
	ucb->ts_idev->name		= "UCB1400 touchscreen interface";
	ucb->ts_idev->id.venकरोr		= ucb1400_reg_पढ़ो(ucb->ac97,
						AC97_VENDOR_ID1);
	ucb->ts_idev->id.product	= ucb->id;
	ucb->ts_idev->खोलो		= ucb1400_ts_खोलो;
	ucb->ts_idev->बंद		= ucb1400_ts_बंद;
	ucb->ts_idev->evbit[0]		= BIT_MASK(EV_ABS) | BIT_MASK(EV_KEY);
	ucb->ts_idev->keybit[BIT_WORD(BTN_TOUCH)] = BIT_MASK(BTN_TOUCH);

	/*
	 * Enable ADC filter to prevent horrible jitter on Colibri.
	 * This also further reduces jitter on boards where ADCSYNC
	 * pin is connected.
	 */
	fcsr = ucb1400_reg_पढ़ो(ucb->ac97, UCB_FCSR);
	ucb1400_reg_ग_लिखो(ucb->ac97, UCB_FCSR, fcsr | UCB_FCSR_AVE);

	ucb1400_adc_enable(ucb->ac97);
	x_res = ucb1400_ts_पढ़ो_xres(ucb);
	y_res = ucb1400_ts_पढ़ो_yres(ucb);
	ucb1400_adc_disable(ucb->ac97);
	dev_dbg(&pdev->dev, "x/y = %d/%d\n", x_res, y_res);

	input_set_असल_params(ucb->ts_idev, ABS_X, 0, x_res, 0, 0);
	input_set_असल_params(ucb->ts_idev, ABS_Y, 0, y_res, 0, 0);
	input_set_असल_params(ucb->ts_idev, ABS_PRESSURE, 0, 0, 0, 0);

	ucb1400_ts_stop(ucb);

	error = request_thपढ़ोed_irq(ucb->irq, शून्य, ucb1400_irq,
				     IRQF_TRIGGER_RISING | IRQF_ONESHOT,
				     "UCB1400", ucb);
	अगर (error) अणु
		dev_err(&pdev->dev,
			"unable to grab irq%d: %d\n", ucb->irq, error);
		जाओ err_मुक्त_devs;
	पूर्ण

	error = input_रेजिस्टर_device(ucb->ts_idev);
	अगर (error)
		जाओ err_मुक्त_irq;

	वापस 0;

err_मुक्त_irq:
	मुक्त_irq(ucb->irq, ucb);
err_मुक्त_devs:
	input_मुक्त_device(ucb->ts_idev);
err:
	वापस error;
पूर्ण

अटल पूर्णांक ucb1400_ts_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा ucb1400_ts *ucb = dev_get_platdata(&pdev->dev);

	मुक्त_irq(ucb->irq, ucb);
	input_unरेजिस्टर_device(ucb->ts_idev);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused ucb1400_ts_suspend(काष्ठा device *dev)
अणु
	काष्ठा ucb1400_ts *ucb = dev_get_platdata(dev);
	काष्ठा input_dev *idev = ucb->ts_idev;

	mutex_lock(&idev->mutex);

	अगर (input_device_enabled(idev))
		ucb1400_ts_stop(ucb);

	mutex_unlock(&idev->mutex);
	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused ucb1400_ts_resume(काष्ठा device *dev)
अणु
	काष्ठा ucb1400_ts *ucb = dev_get_platdata(dev);
	काष्ठा input_dev *idev = ucb->ts_idev;

	mutex_lock(&idev->mutex);

	अगर (input_device_enabled(idev))
		ucb1400_ts_start(ucb);

	mutex_unlock(&idev->mutex);
	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(ucb1400_ts_pm_ops,
			 ucb1400_ts_suspend, ucb1400_ts_resume);

अटल काष्ठा platक्रमm_driver ucb1400_ts_driver = अणु
	.probe	= ucb1400_ts_probe,
	.हटाओ	= ucb1400_ts_हटाओ,
	.driver	= अणु
		.name	= "ucb1400_ts",
		.pm	= &ucb1400_ts_pm_ops,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(ucb1400_ts_driver);

module_param(adcsync, bool, 0444);
MODULE_PARM_DESC(adcsync, "Synchronize touch readings with ADCSYNC pin.");

module_param(ts_delay, पूर्णांक, 0444);
MODULE_PARM_DESC(ts_delay, "Delay between panel setup and"
			    " position read. Default = 55us.");

module_param(ts_delay_pressure, पूर्णांक, 0444);
MODULE_PARM_DESC(ts_delay_pressure,
		"delay between panel setup and pressure read."
		"  Default = 0us.");

MODULE_DESCRIPTION("Philips UCB1400 touchscreen driver");
MODULE_LICENSE("GPL");
