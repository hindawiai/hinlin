<शैली गुरु>
/*
 * Hisilicon PMIC घातerkey driver
 *
 * Copyright (C) 2013 Hisilicon Ltd.
 * Copyright (C) 2015, 2016 Linaro Ltd.
 *
 * This file is subject to the terms and conditions of the GNU General
 * Public License. See the file "COPYING" in the मुख्य directory of this
 * archive क्रम more details.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 */

#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/reboot.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/input.h>
#समावेश <linux/slab.h>

/* the held पूर्णांकerrupt will trigger after 4 seconds */
#घोषणा MAX_HELD_TIME	(4 * MSEC_PER_SEC)

अटल irqवापस_t hi65xx_घातer_press_isr(पूर्णांक irq, व्योम *q)
अणु
	काष्ठा input_dev *input = q;

	pm_wakeup_event(input->dev.parent, MAX_HELD_TIME);
	input_report_key(input, KEY_POWER, 1);
	input_sync(input);

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t hi65xx_घातer_release_isr(पूर्णांक irq, व्योम *q)
अणु
	काष्ठा input_dev *input = q;

	pm_wakeup_event(input->dev.parent, MAX_HELD_TIME);
	input_report_key(input, KEY_POWER, 0);
	input_sync(input);

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t hi65xx_restart_toggle_isr(पूर्णांक irq, व्योम *q)
अणु
	काष्ठा input_dev *input = q;
	पूर्णांक value = test_bit(KEY_RESTART, input->key);

	pm_wakeup_event(input->dev.parent, MAX_HELD_TIME);
	input_report_key(input, KEY_RESTART, !value);
	input_sync(input);

	वापस IRQ_HANDLED;
पूर्ण

अटल स्थिर काष्ठा अणु
	स्थिर अक्षर *name;
	irqवापस_t (*handler)(पूर्णांक irq, व्योम *q);
पूर्ण hi65xx_irq_info[] = अणु
	अणु "down", hi65xx_घातer_press_isr पूर्ण,
	अणु "up", hi65xx_घातer_release_isr पूर्ण,
	अणु "hold 4s", hi65xx_restart_toggle_isr पूर्ण,
पूर्ण;

अटल पूर्णांक hi65xx_घातerkey_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा input_dev *input;
	पूर्णांक irq, i, error;

	input = devm_input_allocate_device(dev);
	अगर (!input) अणु
		dev_err(dev, "failed to allocate input device\n");
		वापस -ENOMEM;
	पूर्ण

	input->phys = "hisi_on/input0";
	input->name = "HISI 65xx PowerOn Key";

	input_set_capability(input, EV_KEY, KEY_POWER);
	input_set_capability(input, EV_KEY, KEY_RESTART);

	क्रम (i = 0; i < ARRAY_SIZE(hi65xx_irq_info); i++) अणु

		irq = platक्रमm_get_irq_byname(pdev, hi65xx_irq_info[i].name);
		अगर (irq < 0)
			वापस irq;

		error = devm_request_any_context_irq(dev, irq,
						     hi65xx_irq_info[i].handler,
						     IRQF_ONESHOT,
						     hi65xx_irq_info[i].name,
						     input);
		अगर (error < 0) अणु
			dev_err(dev, "couldn't request irq %s: %d\n",
				hi65xx_irq_info[i].name, error);
			वापस error;
		पूर्ण
	पूर्ण

	error = input_रेजिस्टर_device(input);
	अगर (error) अणु
		dev_err(dev, "failed to register input device: %d\n", error);
		वापस error;
	पूर्ण

	device_init_wakeup(dev, 1);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver hi65xx_घातerkey_driver = अणु
	.driver = अणु
		.name = "hi65xx-powerkey",
	पूर्ण,
	.probe = hi65xx_घातerkey_probe,
पूर्ण;
module_platक्रमm_driver(hi65xx_घातerkey_driver);

MODULE_AUTHOR("Zhiliang Xue <xuezhiliang@huawei.com");
MODULE_DESCRIPTION("Hisi PMIC Power key driver");
MODULE_LICENSE("GPL v2");
