<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 *  Driver क्रम Analog Devices (Linear Technology) LT3651 अक्षरger IC.
 *  Copyright (C) 2017, Topic Embedded Products
 */

#समावेश <linux/device.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/घातer_supply.h>
#समावेश <linux/slab.h>
#समावेश <linux/of.h>

काष्ठा lt3651_अक्षरger अणु
	काष्ठा घातer_supply *अक्षरger;
	काष्ठा घातer_supply_desc अक्षरger_desc;
	काष्ठा gpio_desc *acpr_gpio;
	काष्ठा gpio_desc *fault_gpio;
	काष्ठा gpio_desc *chrg_gpio;
पूर्ण;

अटल irqवापस_t lt3651_अक्षरger_irq(पूर्णांक irq, व्योम *devid)
अणु
	काष्ठा घातer_supply *अक्षरger = devid;

	घातer_supply_changed(अक्षरger);

	वापस IRQ_HANDLED;
पूर्ण

अटल अंतरभूत काष्ठा lt3651_अक्षरger *psy_to_lt3651_अक्षरger(
	काष्ठा घातer_supply *psy)
अणु
	वापस घातer_supply_get_drvdata(psy);
पूर्ण

अटल पूर्णांक lt3651_अक्षरger_get_property(काष्ठा घातer_supply *psy,
		क्रमागत घातer_supply_property psp, जोड़ घातer_supply_propval *val)
अणु
	काष्ठा lt3651_अक्षरger *lt3651_अक्षरger = psy_to_lt3651_अक्षरger(psy);

	चयन (psp) अणु
	हाल POWER_SUPPLY_PROP_STATUS:
		अगर (!lt3651_अक्षरger->chrg_gpio) अणु
			val->पूर्णांकval = POWER_SUPPLY_STATUS_UNKNOWN;
			अवरोध;
		पूर्ण
		अगर (gpiod_get_value(lt3651_अक्षरger->chrg_gpio))
			val->पूर्णांकval = POWER_SUPPLY_STATUS_CHARGING;
		अन्यथा
			val->पूर्णांकval = POWER_SUPPLY_STATUS_NOT_CHARGING;
		अवरोध;
	हाल POWER_SUPPLY_PROP_ONLINE:
		val->पूर्णांकval = gpiod_get_value(lt3651_अक्षरger->acpr_gpio);
		अवरोध;
	हाल POWER_SUPPLY_PROP_HEALTH:
		अगर (!lt3651_अक्षरger->fault_gpio) अणु
			val->पूर्णांकval = POWER_SUPPLY_HEALTH_UNKNOWN;
			अवरोध;
		पूर्ण
		अगर (!gpiod_get_value(lt3651_अक्षरger->fault_gpio)) अणु
			val->पूर्णांकval = POWER_SUPPLY_HEALTH_GOOD;
			अवरोध;
		पूर्ण
		/*
		 * If the fault pin is active, the chrg pin explains the type
		 * of failure.
		 */
		अगर (!lt3651_अक्षरger->chrg_gpio) अणु
			val->पूर्णांकval = POWER_SUPPLY_HEALTH_UNSPEC_FAILURE;
			अवरोध;
		पूर्ण
		val->पूर्णांकval = gpiod_get_value(lt3651_अक्षरger->chrg_gpio) ?
				POWER_SUPPLY_HEALTH_OVERHEAT :
				POWER_SUPPLY_HEALTH_DEAD;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल क्रमागत घातer_supply_property lt3651_अक्षरger_properties[] = अणु
	POWER_SUPPLY_PROP_STATUS,
	POWER_SUPPLY_PROP_ONLINE,
	POWER_SUPPLY_PROP_HEALTH,
पूर्ण;

अटल पूर्णांक lt3651_अक्षरger_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा घातer_supply_config psy_cfg = अणुपूर्ण;
	काष्ठा lt3651_अक्षरger *lt3651_अक्षरger;
	काष्ठा घातer_supply_desc *अक्षरger_desc;
	पूर्णांक ret;

	lt3651_अक्षरger = devm_kzalloc(&pdev->dev, माप(*lt3651_अक्षरger),
					GFP_KERNEL);
	अगर (!lt3651_अक्षरger)
		वापस -ENOMEM;

	lt3651_अक्षरger->acpr_gpio = devm_gpiod_get(&pdev->dev,
					"lltc,acpr", GPIOD_IN);
	अगर (IS_ERR(lt3651_अक्षरger->acpr_gpio)) अणु
		ret = PTR_ERR(lt3651_अक्षरger->acpr_gpio);
		dev_err(&pdev->dev, "Failed to acquire acpr GPIO: %d\n", ret);
		वापस ret;
	पूर्ण
	lt3651_अक्षरger->fault_gpio = devm_gpiod_get_optional(&pdev->dev,
					"lltc,fault", GPIOD_IN);
	अगर (IS_ERR(lt3651_अक्षरger->fault_gpio)) अणु
		ret = PTR_ERR(lt3651_अक्षरger->fault_gpio);
		dev_err(&pdev->dev, "Failed to acquire fault GPIO: %d\n", ret);
		वापस ret;
	पूर्ण
	lt3651_अक्षरger->chrg_gpio = devm_gpiod_get_optional(&pdev->dev,
					"lltc,chrg", GPIOD_IN);
	अगर (IS_ERR(lt3651_अक्षरger->chrg_gpio)) अणु
		ret = PTR_ERR(lt3651_अक्षरger->chrg_gpio);
		dev_err(&pdev->dev, "Failed to acquire chrg GPIO: %d\n", ret);
		वापस ret;
	पूर्ण

	अक्षरger_desc = &lt3651_अक्षरger->अक्षरger_desc;
	अक्षरger_desc->name = pdev->dev.of_node->name;
	अक्षरger_desc->type = POWER_SUPPLY_TYPE_MAINS;
	अक्षरger_desc->properties = lt3651_अक्षरger_properties;
	अक्षरger_desc->num_properties = ARRAY_SIZE(lt3651_अक्षरger_properties);
	अक्षरger_desc->get_property = lt3651_अक्षरger_get_property;
	psy_cfg.of_node = pdev->dev.of_node;
	psy_cfg.drv_data = lt3651_अक्षरger;

	lt3651_अक्षरger->अक्षरger = devm_घातer_supply_रेजिस्टर(&pdev->dev,
						      अक्षरger_desc, &psy_cfg);
	अगर (IS_ERR(lt3651_अक्षरger->अक्षरger)) अणु
		ret = PTR_ERR(lt3651_अक्षरger->अक्षरger);
		dev_err(&pdev->dev, "Failed to register power supply: %d\n",
			ret);
		वापस ret;
	पूर्ण

	/*
	 * Acquire IRQs क्रम the GPIO pins अगर possible. If the प्रणाली करोes not
	 * support IRQs on these pins, userspace will have to poll the sysfs
	 * files manually.
	 */
	अगर (lt3651_अक्षरger->acpr_gpio) अणु
		ret = gpiod_to_irq(lt3651_अक्षरger->acpr_gpio);
		अगर (ret >= 0)
			ret = devm_request_any_context_irq(&pdev->dev, ret,
				lt3651_अक्षरger_irq,
				IRQF_TRIGGER_RISING | IRQF_TRIGGER_FALLING,
				dev_name(&pdev->dev), lt3651_अक्षरger->अक्षरger);
		अगर (ret < 0)
			dev_warn(&pdev->dev, "Failed to request acpr irq\n");
	पूर्ण
	अगर (lt3651_अक्षरger->fault_gpio) अणु
		ret = gpiod_to_irq(lt3651_अक्षरger->fault_gpio);
		अगर (ret >= 0)
			ret = devm_request_any_context_irq(&pdev->dev, ret,
				lt3651_अक्षरger_irq,
				IRQF_TRIGGER_RISING | IRQF_TRIGGER_FALLING,
				dev_name(&pdev->dev), lt3651_अक्षरger->अक्षरger);
		अगर (ret < 0)
			dev_warn(&pdev->dev, "Failed to request fault irq\n");
	पूर्ण
	अगर (lt3651_अक्षरger->chrg_gpio) अणु
		ret = gpiod_to_irq(lt3651_अक्षरger->chrg_gpio);
		अगर (ret >= 0)
			ret = devm_request_any_context_irq(&pdev->dev, ret,
				lt3651_अक्षरger_irq,
				IRQF_TRIGGER_RISING | IRQF_TRIGGER_FALLING,
				dev_name(&pdev->dev), lt3651_अक्षरger->अक्षरger);
		अगर (ret < 0)
			dev_warn(&pdev->dev, "Failed to request chrg irq\n");
	पूर्ण

	platक्रमm_set_drvdata(pdev, lt3651_अक्षरger);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id lt3651_अक्षरger_match[] = अणु
	अणु .compatible = "lltc,ltc3651-charger" पूर्ण, /* DEPRECATED */
	अणु .compatible = "lltc,lt3651-charger" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, lt3651_अक्षरger_match);

अटल काष्ठा platक्रमm_driver lt3651_अक्षरger_driver = अणु
	.probe = lt3651_अक्षरger_probe,
	.driver = अणु
		.name = "lt3651-charger",
		.of_match_table = lt3651_अक्षरger_match,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(lt3651_अक्षरger_driver);

MODULE_AUTHOR("Mike Looijmans <mike.looijmans@topic.nl>");
MODULE_DESCRIPTION("Driver for LT3651 charger");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:lt3651-charger");
