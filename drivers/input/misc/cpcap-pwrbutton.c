<शैली गुरु>
/**
 * CPCAP Power Button Input Driver
 *
 * Copyright (C) 2017 Sebastian Reichel <sre@kernel.org>
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

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/input.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/regmap.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/mfd/motorola-cpcap.h>

#घोषणा CPCAP_IRQ_ON 23
#घोषणा CPCAP_IRQ_ON_BITMASK (1 << (CPCAP_IRQ_ON % 16))

काष्ठा cpcap_घातer_button अणु
	काष्ठा regmap *regmap;
	काष्ठा input_dev *idev;
	काष्ठा device *dev;
पूर्ण;

अटल irqवापस_t घातerbutton_irq(पूर्णांक irq, व्योम *_button)
अणु
	काष्ठा cpcap_घातer_button *button = _button;
	पूर्णांक val;

	val = cpcap_sense_virq(button->regmap, irq);
	अगर (val < 0) अणु
		dev_err(button->dev, "irq read failed: %d", val);
		वापस IRQ_HANDLED;
	पूर्ण

	pm_wakeup_event(button->dev, 0);
	input_report_key(button->idev, KEY_POWER, val);
	input_sync(button->idev);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक cpcap_घातer_button_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा cpcap_घातer_button *button;
	पूर्णांक irq = platक्रमm_get_irq(pdev, 0);
	पूर्णांक err;

	button = devm_kदो_स्मृति(&pdev->dev, माप(*button), GFP_KERNEL);
	अगर (!button)
		वापस -ENOMEM;

	button->idev = devm_input_allocate_device(&pdev->dev);
	अगर (!button->idev)
		वापस -ENOMEM;

	button->regmap = dev_get_regmap(pdev->dev.parent, शून्य);
	अगर (!button->regmap)
		वापस -ENODEV;

	button->dev = &pdev->dev;

	button->idev->name = "cpcap-pwrbutton";
	button->idev->phys = "cpcap-pwrbutton/input0";
	button->idev->dev.parent = button->dev;
	input_set_capability(button->idev, EV_KEY, KEY_POWER);

	err = devm_request_thपढ़ोed_irq(&pdev->dev, irq, शून्य,
		घातerbutton_irq, IRQF_ONESHOT, "cpcap_pwrbutton", button);
	अगर (err < 0) अणु
		dev_err(&pdev->dev, "IRQ request failed: %d\n", err);
		वापस err;
	पूर्ण

	err = input_रेजिस्टर_device(button->idev);
	अगर (err) अणु
		dev_err(&pdev->dev, "Input register failed: %d\n", err);
		वापस err;
	पूर्ण

	device_init_wakeup(&pdev->dev, true);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id cpcap_pwrbutton_dt_match_table[] = अणु
	अणु .compatible = "motorola,cpcap-pwrbutton" पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, cpcap_pwrbutton_dt_match_table);
#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver cpcap_घातer_button_driver = अणु
	.probe		= cpcap_घातer_button_probe,
	.driver		= अणु
		.name	= "cpcap-pwrbutton",
		.of_match_table = of_match_ptr(cpcap_pwrbutton_dt_match_table),
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(cpcap_घातer_button_driver);

MODULE_ALIAS("platform:cpcap-pwrbutton");
MODULE_DESCRIPTION("CPCAP Power Button");
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Sebastian Reichel <sre@kernel.org>");
