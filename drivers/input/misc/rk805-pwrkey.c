<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Rockchip RK805 PMIC Power Key driver
 *
 * Copyright (c) 2017, Fuzhou Rockchip Electronics Co., Ltd
 *
 * Author: Joseph Chen <chenjh@rock-chips.com>
 */

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/init.h>
#समावेश <linux/input.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>

अटल irqवापस_t pwrkey_fall_irq(पूर्णांक irq, व्योम *_pwr)
अणु
	काष्ठा input_dev *pwr = _pwr;

	input_report_key(pwr, KEY_POWER, 1);
	input_sync(pwr);

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t pwrkey_rise_irq(पूर्णांक irq, व्योम *_pwr)
अणु
	काष्ठा input_dev *pwr = _pwr;

	input_report_key(pwr, KEY_POWER, 0);
	input_sync(pwr);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक rk805_pwrkey_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा input_dev *pwr;
	पूर्णांक fall_irq, rise_irq;
	पूर्णांक err;

	pwr = devm_input_allocate_device(&pdev->dev);
	अगर (!pwr) अणु
		dev_err(&pdev->dev, "Can't allocate power button\n");
		वापस -ENOMEM;
	पूर्ण

	pwr->name = "rk805 pwrkey";
	pwr->phys = "rk805_pwrkey/input0";
	pwr->id.bustype = BUS_HOST;
	input_set_capability(pwr, EV_KEY, KEY_POWER);

	fall_irq = platक्रमm_get_irq(pdev, 0);
	अगर (fall_irq < 0)
		वापस fall_irq;

	rise_irq = platक्रमm_get_irq(pdev, 1);
	अगर (rise_irq < 0)
		वापस rise_irq;

	err = devm_request_any_context_irq(&pwr->dev, fall_irq,
					   pwrkey_fall_irq,
					   IRQF_TRIGGER_FALLING | IRQF_ONESHOT,
					   "rk805_pwrkey_fall", pwr);
	अगर (err < 0) अणु
		dev_err(&pdev->dev, "Can't register fall irq: %d\n", err);
		वापस err;
	पूर्ण

	err = devm_request_any_context_irq(&pwr->dev, rise_irq,
					   pwrkey_rise_irq,
					   IRQF_TRIGGER_RISING | IRQF_ONESHOT,
					   "rk805_pwrkey_rise", pwr);
	अगर (err < 0) अणु
		dev_err(&pdev->dev, "Can't register rise irq: %d\n", err);
		वापस err;
	पूर्ण

	err = input_रेजिस्टर_device(pwr);
	अगर (err) अणु
		dev_err(&pdev->dev, "Can't register power button: %d\n", err);
		वापस err;
	पूर्ण

	platक्रमm_set_drvdata(pdev, pwr);
	device_init_wakeup(&pdev->dev, true);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver rk805_pwrkey_driver = अणु
	.probe	= rk805_pwrkey_probe,
	.driver	= अणु
		.name = "rk805-pwrkey",
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(rk805_pwrkey_driver);

MODULE_AUTHOR("Joseph Chen <chenjh@rock-chips.com>");
MODULE_DESCRIPTION("RK805 PMIC Power Key driver");
MODULE_LICENSE("GPL");
