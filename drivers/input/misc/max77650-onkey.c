<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Copyright (C) 2018 BayLibre SAS
// Author: Bartosz Golaszewski <bgolaszewski@baylibre.com>
//
// ONKEY driver क्रम MAXIM 77650/77651 अक्षरger/घातer-supply.

#समावेश <linux/i2c.h>
#समावेश <linux/input.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/mfd/max77650.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>

#घोषणा MAX77650_ONKEY_MODE_MASK	BIT(3)
#घोषणा MAX77650_ONKEY_MODE_PUSH	0x00
#घोषणा MAX77650_ONKEY_MODE_SLIDE	BIT(3)

काष्ठा max77650_onkey अणु
	काष्ठा input_dev *input;
	अचिन्हित पूर्णांक code;
पूर्ण;

अटल irqवापस_t max77650_onkey_falling(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा max77650_onkey *onkey = data;

	input_report_key(onkey->input, onkey->code, 0);
	input_sync(onkey->input);

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t max77650_onkey_rising(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा max77650_onkey *onkey = data;

	input_report_key(onkey->input, onkey->code, 1);
	input_sync(onkey->input);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक max77650_onkey_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक irq_r, irq_f, error, mode;
	काष्ठा max77650_onkey *onkey;
	काष्ठा device *dev, *parent;
	काष्ठा regmap *map;
	अचिन्हित पूर्णांक type;

	dev = &pdev->dev;
	parent = dev->parent;

	map = dev_get_regmap(parent, शून्य);
	अगर (!map)
		वापस -ENODEV;

	onkey = devm_kzalloc(dev, माप(*onkey), GFP_KERNEL);
	अगर (!onkey)
		वापस -ENOMEM;

	error = device_property_पढ़ो_u32(dev, "linux,code", &onkey->code);
	अगर (error)
		onkey->code = KEY_POWER;

	अगर (device_property_पढ़ो_bool(dev, "maxim,onkey-slide")) अणु
		mode = MAX77650_ONKEY_MODE_SLIDE;
		type = EV_SW;
	पूर्ण अन्यथा अणु
		mode = MAX77650_ONKEY_MODE_PUSH;
		type = EV_KEY;
	पूर्ण

	error = regmap_update_bits(map, MAX77650_REG_CNFG_GLBL,
				   MAX77650_ONKEY_MODE_MASK, mode);
	अगर (error)
		वापस error;

	irq_f = platक्रमm_get_irq_byname(pdev, "nEN_F");
	अगर (irq_f < 0)
		वापस irq_f;

	irq_r = platक्रमm_get_irq_byname(pdev, "nEN_R");
	अगर (irq_r < 0)
		वापस irq_r;

	onkey->input = devm_input_allocate_device(dev);
	अगर (!onkey->input)
		वापस -ENOMEM;

	onkey->input->name = "max77650_onkey";
	onkey->input->phys = "max77650_onkey/input0";
	onkey->input->id.bustype = BUS_I2C;
	input_set_capability(onkey->input, type, onkey->code);

	error = devm_request_any_context_irq(dev, irq_f, max77650_onkey_falling,
					     IRQF_ONESHOT, "onkey-down", onkey);
	अगर (error < 0)
		वापस error;

	error = devm_request_any_context_irq(dev, irq_r, max77650_onkey_rising,
					     IRQF_ONESHOT, "onkey-up", onkey);
	अगर (error < 0)
		वापस error;

	वापस input_रेजिस्टर_device(onkey->input);
पूर्ण

अटल स्थिर काष्ठा of_device_id max77650_onkey_of_match[] = अणु
	अणु .compatible = "maxim,max77650-onkey" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, max77650_onkey_of_match);

अटल काष्ठा platक्रमm_driver max77650_onkey_driver = अणु
	.driver = अणु
		.name = "max77650-onkey",
		.of_match_table = max77650_onkey_of_match,
	पूर्ण,
	.probe = max77650_onkey_probe,
पूर्ण;
module_platक्रमm_driver(max77650_onkey_driver);

MODULE_DESCRIPTION("MAXIM 77650/77651 ONKEY driver");
MODULE_AUTHOR("Bartosz Golaszewski <bgolaszewski@baylibre.com>");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:max77650-onkey");
