<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Power key driver क्रम SiRF PrimaII
 *
 * Copyright (c) 2013 - 2014 Cambridge Silicon Radio Limited, a CSR plc group
 * company.
 */

#समावेश <linux/module.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/delay.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/input.h>
#समावेश <linux/rtc/sirfsoc_rtciobrg.h>
#समावेश <linux/of.h>
#समावेश <linux/workqueue.h>

काष्ठा sirfsoc_pwrc_drvdata अणु
	u32			pwrc_base;
	काष्ठा input_dev	*input;
	काष्ठा delayed_work	work;
पूर्ण;

#घोषणा PWRC_ON_KEY_BIT			(1 << 0)

#घोषणा PWRC_INT_STATUS			0xc
#घोषणा PWRC_INT_MASK			0x10
#घोषणा PWRC_PIN_STATUS			0x14
#घोषणा PWRC_KEY_DETECT_UP_TIME		20	/* ms*/

अटल पूर्णांक sirfsoc_pwrc_is_on_key_करोwn(काष्ठा sirfsoc_pwrc_drvdata *pwrcdrv)
अणु
	u32 state = sirfsoc_rtc_iobrg_पढ़ोl(pwrcdrv->pwrc_base +
							PWRC_PIN_STATUS);
	वापस !(state & PWRC_ON_KEY_BIT); /* ON_KEY is active low */
पूर्ण

अटल व्योम sirfsoc_pwrc_report_event(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा sirfsoc_pwrc_drvdata *pwrcdrv =
		container_of(work, काष्ठा sirfsoc_pwrc_drvdata, work.work);

	अगर (sirfsoc_pwrc_is_on_key_करोwn(pwrcdrv)) अणु
		schedule_delayed_work(&pwrcdrv->work,
			msecs_to_jअगरfies(PWRC_KEY_DETECT_UP_TIME));
	पूर्ण अन्यथा अणु
		input_event(pwrcdrv->input, EV_KEY, KEY_POWER, 0);
		input_sync(pwrcdrv->input);
	पूर्ण
पूर्ण

अटल irqवापस_t sirfsoc_pwrc_isr(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा sirfsoc_pwrc_drvdata *pwrcdrv = dev_id;
	u32 पूर्णांक_status;

	पूर्णांक_status = sirfsoc_rtc_iobrg_पढ़ोl(pwrcdrv->pwrc_base +
							PWRC_INT_STATUS);
	sirfsoc_rtc_iobrg_ग_लिखोl(पूर्णांक_status & ~PWRC_ON_KEY_BIT,
				 pwrcdrv->pwrc_base + PWRC_INT_STATUS);

	input_event(pwrcdrv->input, EV_KEY, KEY_POWER, 1);
	input_sync(pwrcdrv->input);
	schedule_delayed_work(&pwrcdrv->work,
			      msecs_to_jअगरfies(PWRC_KEY_DETECT_UP_TIME));

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम sirfsoc_pwrc_toggle_पूर्णांकerrupts(काष्ठा sirfsoc_pwrc_drvdata *pwrcdrv,
					   bool enable)
अणु
	u32 पूर्णांक_mask;

	पूर्णांक_mask = sirfsoc_rtc_iobrg_पढ़ोl(pwrcdrv->pwrc_base + PWRC_INT_MASK);
	अगर (enable)
		पूर्णांक_mask |= PWRC_ON_KEY_BIT;
	अन्यथा
		पूर्णांक_mask &= ~PWRC_ON_KEY_BIT;
	sirfsoc_rtc_iobrg_ग_लिखोl(पूर्णांक_mask, pwrcdrv->pwrc_base + PWRC_INT_MASK);
पूर्ण

अटल पूर्णांक sirfsoc_pwrc_खोलो(काष्ठा input_dev *input)
अणु
	काष्ठा sirfsoc_pwrc_drvdata *pwrcdrv = input_get_drvdata(input);

	sirfsoc_pwrc_toggle_पूर्णांकerrupts(pwrcdrv, true);

	वापस 0;
पूर्ण

अटल व्योम sirfsoc_pwrc_बंद(काष्ठा input_dev *input)
अणु
	काष्ठा sirfsoc_pwrc_drvdata *pwrcdrv = input_get_drvdata(input);

	sirfsoc_pwrc_toggle_पूर्णांकerrupts(pwrcdrv, false);
	cancel_delayed_work_sync(&pwrcdrv->work);
पूर्ण

अटल स्थिर काष्ठा of_device_id sirfsoc_pwrc_of_match[] = अणु
	अणु .compatible = "sirf,prima2-pwrc" पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, sirfsoc_pwrc_of_match);

अटल पूर्णांक sirfsoc_pwrc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा sirfsoc_pwrc_drvdata *pwrcdrv;
	पूर्णांक irq;
	पूर्णांक error;

	pwrcdrv = devm_kzalloc(&pdev->dev, माप(काष्ठा sirfsoc_pwrc_drvdata),
			       GFP_KERNEL);
	अगर (!pwrcdrv) अणु
		dev_info(&pdev->dev, "Not enough memory for the device data\n");
		वापस -ENOMEM;
	पूर्ण

	/*
	 * We can't use of_iomap because pwrc is not mapped in memory,
	 * the so-called base address is only offset in rtciobrg
	 */
	error = of_property_पढ़ो_u32(np, "reg", &pwrcdrv->pwrc_base);
	अगर (error) अणु
		dev_err(&pdev->dev,
			"unable to find base address of pwrc node in dtb\n");
		वापस error;
	पूर्ण

	pwrcdrv->input = devm_input_allocate_device(&pdev->dev);
	अगर (!pwrcdrv->input)
		वापस -ENOMEM;

	pwrcdrv->input->name = "sirfsoc pwrckey";
	pwrcdrv->input->phys = "pwrc/input0";
	pwrcdrv->input->evbit[0] = BIT_MASK(EV_KEY);
	input_set_capability(pwrcdrv->input, EV_KEY, KEY_POWER);

	INIT_DELAYED_WORK(&pwrcdrv->work, sirfsoc_pwrc_report_event);

	pwrcdrv->input->खोलो = sirfsoc_pwrc_खोलो;
	pwrcdrv->input->बंद = sirfsoc_pwrc_बंद;

	input_set_drvdata(pwrcdrv->input, pwrcdrv);

	/* Make sure the device is quiesced */
	sirfsoc_pwrc_toggle_पूर्णांकerrupts(pwrcdrv, false);

	irq = platक्रमm_get_irq(pdev, 0);
	error = devm_request_irq(&pdev->dev, irq,
				 sirfsoc_pwrc_isr, 0,
				 "sirfsoc_pwrc_int", pwrcdrv);
	अगर (error) अणु
		dev_err(&pdev->dev, "unable to claim irq %d, error: %d\n",
			irq, error);
		वापस error;
	पूर्ण

	error = input_रेजिस्टर_device(pwrcdrv->input);
	अगर (error) अणु
		dev_err(&pdev->dev,
			"unable to register input device, error: %d\n",
			error);
		वापस error;
	पूर्ण

	dev_set_drvdata(&pdev->dev, pwrcdrv);
	device_init_wakeup(&pdev->dev, 1);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused sirfsoc_pwrc_resume(काष्ठा device *dev)
अणु
	काष्ठा sirfsoc_pwrc_drvdata *pwrcdrv = dev_get_drvdata(dev);
	काष्ठा input_dev *input = pwrcdrv->input;

	/*
	 * Do not mask pwrc पूर्णांकerrupt as we want pwrc work as a wakeup source
	 * अगर users touch X_ONKEY_B, see arch/arm/mach-prima2/pm.c
	 */
	mutex_lock(&input->mutex);
	अगर (input_device_enabled(input))
		sirfsoc_pwrc_toggle_पूर्णांकerrupts(pwrcdrv, true);
	mutex_unlock(&input->mutex);

	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(sirfsoc_pwrc_pm_ops, शून्य, sirfsoc_pwrc_resume);

अटल काष्ठा platक्रमm_driver sirfsoc_pwrc_driver = अणु
	.probe		= sirfsoc_pwrc_probe,
	.driver		= अणु
		.name	= "sirfsoc-pwrc",
		.pm	= &sirfsoc_pwrc_pm_ops,
		.of_match_table = sirfsoc_pwrc_of_match,
	पूर्ण
पूर्ण;

module_platक्रमm_driver(sirfsoc_pwrc_driver);

MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Binghua Duan <Binghua.Duan@csr.com>, Xianglong Du <Xianglong.Du@csr.com>");
MODULE_DESCRIPTION("CSR Prima2 PWRC Driver");
MODULE_ALIAS("platform:sirfsoc-pwrc");
