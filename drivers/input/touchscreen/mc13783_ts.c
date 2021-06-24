<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Driver क्रम the Freescale Semiconductor MC13783 touchscreen.
 *
 * Copyright 2004-2007 Freescale Semiconductor, Inc. All Rights Reserved.
 * Copyright (C) 2009 Sascha Hauer, Pengutronix
 *
 * Initial development of this code was funded by
 * Phytec Messtechnik GmbH, http://www.phytec.de/
 */
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/mfd/mc13783.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/input.h>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश <linux/init.h>

#घोषणा MC13783_TS_NAME	"mc13783-ts"

#घोषणा DEFAULT_SAMPLE_TOLERANCE 300

अटल अचिन्हित पूर्णांक sample_tolerance = DEFAULT_SAMPLE_TOLERANCE;
module_param(sample_tolerance, uपूर्णांक, S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(sample_tolerance,
		"If the minimal and maximal value read out for one axis (out "
		"of three) differ by this value (default: "
		__stringअगरy(DEFAULT_SAMPLE_TOLERANCE) ") or more, the reading "
		"is supposed to be wrong and is discarded.  Set to 0 to "
		"disable this check.");

काष्ठा mc13783_ts_priv अणु
	काष्ठा input_dev *idev;
	काष्ठा mc13xxx *mc13xxx;
	काष्ठा delayed_work work;
	अचिन्हित पूर्णांक sample[4];
	काष्ठा mc13xxx_ts_platक्रमm_data *touch;
पूर्ण;

अटल irqवापस_t mc13783_ts_handler(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा mc13783_ts_priv *priv = data;

	mc13xxx_irq_ack(priv->mc13xxx, irq);

	/*
	 * Kick off पढ़ोing coordinates. Note that अगर work happens alपढ़ोy
	 * be queued क्रम future execution (it rearms itself) it will not
	 * be rescheduled क्रम immediate execution here. However the rearm
	 * delay is HZ / 50 which is acceptable.
	 */
	schedule_delayed_work(&priv->work, 0);

	वापस IRQ_HANDLED;
पूर्ण

#घोषणा sort3(a0, a1, a2) (अणु						\
		अगर (a0 > a1)						\
			swap(a0, a1);					\
		अगर (a1 > a2)						\
			swap(a1, a2);					\
		अगर (a0 > a1)						\
			swap(a0, a1);					\
		पूर्ण)

अटल व्योम mc13783_ts_report_sample(काष्ठा mc13783_ts_priv *priv)
अणु
	काष्ठा input_dev *idev = priv->idev;
	पूर्णांक x0, x1, x2, y0, y1, y2;
	पूर्णांक cr0, cr1;

	/*
	 * the values are 10-bit wide only, but the two least signअगरicant
	 * bits are क्रम future 12 bit use and पढ़ोing yields 0
	 */
	x0 = priv->sample[0] & 0xfff;
	x1 = priv->sample[1] & 0xfff;
	x2 = priv->sample[2] & 0xfff;
	y0 = priv->sample[3] & 0xfff;
	y1 = (priv->sample[0] >> 12) & 0xfff;
	y2 = (priv->sample[1] >> 12) & 0xfff;
	cr0 = (priv->sample[2] >> 12) & 0xfff;
	cr1 = (priv->sample[3] >> 12) & 0xfff;

	dev_dbg(&idev->dev,
		"x: (% 4d,% 4d,% 4d) y: (% 4d, % 4d,% 4d) cr: (% 4d, % 4d)\n",
		x0, x1, x2, y0, y1, y2, cr0, cr1);

	sort3(x0, x1, x2);
	sort3(y0, y1, y2);

	cr0 = (cr0 + cr1) / 2;

	अगर (!cr0 || !sample_tolerance ||
			(x2 - x0 < sample_tolerance &&
			 y2 - y0 < sample_tolerance)) अणु
		/* report the median coordinate and average pressure */
		अगर (cr0) अणु
			input_report_असल(idev, ABS_X, x1);
			input_report_असल(idev, ABS_Y, y1);

			dev_dbg(&idev->dev, "report (%d, %d, %d)\n",
					x1, y1, 0x1000 - cr0);
			schedule_delayed_work(&priv->work, HZ / 50);
		पूर्ण अन्यथा अणु
			dev_dbg(&idev->dev, "report release\n");
		पूर्ण

		input_report_असल(idev, ABS_PRESSURE,
				cr0 ? 0x1000 - cr0 : cr0);
		input_report_key(idev, BTN_TOUCH, cr0);
		input_sync(idev);
	पूर्ण अन्यथा अणु
		dev_dbg(&idev->dev, "discard event\n");
	पूर्ण
पूर्ण

अटल व्योम mc13783_ts_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा mc13783_ts_priv *priv =
		container_of(work, काष्ठा mc13783_ts_priv, work.work);
	अचिन्हित पूर्णांक mode = MC13XXX_ADC_MODE_TS;
	अचिन्हित पूर्णांक channel = 12;

	अगर (mc13xxx_adc_करो_conversion(priv->mc13xxx,
				mode, channel,
				priv->touch->ato, priv->touch->atox,
				priv->sample) == 0)
		mc13783_ts_report_sample(priv);
पूर्ण

अटल पूर्णांक mc13783_ts_खोलो(काष्ठा input_dev *dev)
अणु
	काष्ठा mc13783_ts_priv *priv = input_get_drvdata(dev);
	पूर्णांक ret;

	mc13xxx_lock(priv->mc13xxx);

	mc13xxx_irq_ack(priv->mc13xxx, MC13XXX_IRQ_TS);

	ret = mc13xxx_irq_request(priv->mc13xxx, MC13XXX_IRQ_TS,
		mc13783_ts_handler, MC13783_TS_NAME, priv);
	अगर (ret)
		जाओ out;

	ret = mc13xxx_reg_rmw(priv->mc13xxx, MC13XXX_ADC0,
			MC13XXX_ADC0_TSMOD_MASK, MC13XXX_ADC0_TSMOD0);
	अगर (ret)
		mc13xxx_irq_मुक्त(priv->mc13xxx, MC13XXX_IRQ_TS, priv);
out:
	mc13xxx_unlock(priv->mc13xxx);
	वापस ret;
पूर्ण

अटल व्योम mc13783_ts_बंद(काष्ठा input_dev *dev)
अणु
	काष्ठा mc13783_ts_priv *priv = input_get_drvdata(dev);

	mc13xxx_lock(priv->mc13xxx);
	mc13xxx_reg_rmw(priv->mc13xxx, MC13XXX_ADC0,
			MC13XXX_ADC0_TSMOD_MASK, 0);
	mc13xxx_irq_मुक्त(priv->mc13xxx, MC13XXX_IRQ_TS, priv);
	mc13xxx_unlock(priv->mc13xxx);

	cancel_delayed_work_sync(&priv->work);
पूर्ण

अटल पूर्णांक __init mc13783_ts_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mc13783_ts_priv *priv;
	काष्ठा input_dev *idev;
	पूर्णांक ret = -ENOMEM;

	priv = kzalloc(माप(*priv), GFP_KERNEL);
	idev = input_allocate_device();
	अगर (!priv || !idev)
		जाओ err_मुक्त_mem;

	INIT_DELAYED_WORK(&priv->work, mc13783_ts_work);
	priv->mc13xxx = dev_get_drvdata(pdev->dev.parent);
	priv->idev = idev;
	priv->touch = dev_get_platdata(&pdev->dev);
	अगर (!priv->touch) अणु
		dev_err(&pdev->dev, "missing platform data\n");
		ret = -ENODEV;
		जाओ err_मुक्त_mem;
	पूर्ण

	idev->name = MC13783_TS_NAME;
	idev->dev.parent = &pdev->dev;

	idev->evbit[0] = BIT_MASK(EV_KEY) | BIT_MASK(EV_ABS);
	idev->keybit[BIT_WORD(BTN_TOUCH)] = BIT_MASK(BTN_TOUCH);
	input_set_असल_params(idev, ABS_X, 0, 0xfff, 0, 0);
	input_set_असल_params(idev, ABS_Y, 0, 0xfff, 0, 0);
	input_set_असल_params(idev, ABS_PRESSURE, 0, 0xfff, 0, 0);

	idev->खोलो = mc13783_ts_खोलो;
	idev->बंद = mc13783_ts_बंद;

	input_set_drvdata(idev, priv);

	ret = input_रेजिस्टर_device(priv->idev);
	अगर (ret) अणु
		dev_err(&pdev->dev,
			"register input device failed with %d\n", ret);
		जाओ err_मुक्त_mem;
	पूर्ण

	platक्रमm_set_drvdata(pdev, priv);
	वापस 0;

err_मुक्त_mem:
	input_मुक्त_device(idev);
	kमुक्त(priv);
	वापस ret;
पूर्ण

अटल पूर्णांक mc13783_ts_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mc13783_ts_priv *priv = platक्रमm_get_drvdata(pdev);

	input_unरेजिस्टर_device(priv->idev);
	kमुक्त(priv);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver mc13783_ts_driver = अणु
	.हटाओ		= mc13783_ts_हटाओ,
	.driver		= अणु
		.name	= MC13783_TS_NAME,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver_probe(mc13783_ts_driver, mc13783_ts_probe);

MODULE_DESCRIPTION("MC13783 input touchscreen driver");
MODULE_AUTHOR("Sascha Hauer <s.hauer@pengutronix.de>");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:" MC13783_TS_NAME);
