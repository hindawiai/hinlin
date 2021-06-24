<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Copyright (C) 2010, Lars-Peter Clausen <lars@metafoo.de>
 *  Driver क्रम अक्षरgers which report their online status through a GPIO pin
 */

#समावेश <linux/device.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/घातer_supply.h>
#समावेश <linux/slab.h>
#समावेश <linux/of.h>
#समावेश <linux/gpio/consumer.h>

#समावेश <linux/घातer/gpio-अक्षरger.h>

काष्ठा gpio_mapping अणु
	u32 limit_ua;
	u32 gpiodata;
पूर्ण __packed;

काष्ठा gpio_अक्षरger अणु
	काष्ठा device *dev;
	अचिन्हित पूर्णांक irq;
	अचिन्हित पूर्णांक अक्षरge_status_irq;
	bool wakeup_enabled;

	काष्ठा घातer_supply *अक्षरger;
	काष्ठा घातer_supply_desc अक्षरger_desc;
	काष्ठा gpio_desc *gpiod;
	काष्ठा gpio_desc *अक्षरge_status;

	काष्ठा gpio_descs *current_limit_gpios;
	काष्ठा gpio_mapping *current_limit_map;
	u32 current_limit_map_size;
	u32 अक्षरge_current_limit;
पूर्ण;

अटल irqवापस_t gpio_अक्षरger_irq(पूर्णांक irq, व्योम *devid)
अणु
	काष्ठा घातer_supply *अक्षरger = devid;

	घातer_supply_changed(अक्षरger);

	वापस IRQ_HANDLED;
पूर्ण

अटल अंतरभूत काष्ठा gpio_अक्षरger *psy_to_gpio_अक्षरger(काष्ठा घातer_supply *psy)
अणु
	वापस घातer_supply_get_drvdata(psy);
पूर्ण

अटल पूर्णांक set_अक्षरge_current_limit(काष्ठा gpio_अक्षरger *gpio_अक्षरger, पूर्णांक val)
अणु
	काष्ठा gpio_mapping mapping;
	पूर्णांक ndescs = gpio_अक्षरger->current_limit_gpios->ndescs;
	काष्ठा gpio_desc **gpios = gpio_अक्षरger->current_limit_gpios->desc;
	पूर्णांक i;

	अगर (!gpio_अक्षरger->current_limit_map_size)
		वापस -EINVAL;

	क्रम (i = 0; i < gpio_अक्षरger->current_limit_map_size; i++) अणु
		अगर (gpio_अक्षरger->current_limit_map[i].limit_ua <= val)
			अवरोध;
	पूर्ण
	mapping = gpio_अक्षरger->current_limit_map[i];

	क्रम (i = 0; i < ndescs; i++) अणु
		bool val = (mapping.gpiodata >> i) & 1;
		gpiod_set_value_cansleep(gpios[ndescs-i-1], val);
	पूर्ण

	gpio_अक्षरger->अक्षरge_current_limit = mapping.limit_ua;

	dev_dbg(gpio_अक्षरger->dev, "set charge current limit to %d (requested: %d)\n",
		gpio_अक्षरger->अक्षरge_current_limit, val);

	वापस 0;
पूर्ण

अटल पूर्णांक gpio_अक्षरger_get_property(काष्ठा घातer_supply *psy,
		क्रमागत घातer_supply_property psp, जोड़ घातer_supply_propval *val)
अणु
	काष्ठा gpio_अक्षरger *gpio_अक्षरger = psy_to_gpio_अक्षरger(psy);

	चयन (psp) अणु
	हाल POWER_SUPPLY_PROP_ONLINE:
		val->पूर्णांकval = gpiod_get_value_cansleep(gpio_अक्षरger->gpiod);
		अवरोध;
	हाल POWER_SUPPLY_PROP_STATUS:
		अगर (gpiod_get_value_cansleep(gpio_अक्षरger->अक्षरge_status))
			val->पूर्णांकval = POWER_SUPPLY_STATUS_CHARGING;
		अन्यथा
			val->पूर्णांकval = POWER_SUPPLY_STATUS_NOT_CHARGING;
		अवरोध;
	हाल POWER_SUPPLY_PROP_CONSTANT_CHARGE_CURRENT_MAX:
		val->पूर्णांकval = gpio_अक्षरger->अक्षरge_current_limit;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक gpio_अक्षरger_set_property(काष्ठा घातer_supply *psy,
	क्रमागत घातer_supply_property psp, स्थिर जोड़ घातer_supply_propval *val)
अणु
	काष्ठा gpio_अक्षरger *gpio_अक्षरger = psy_to_gpio_अक्षरger(psy);

	चयन (psp) अणु
	हाल POWER_SUPPLY_PROP_CONSTANT_CHARGE_CURRENT_MAX:
		वापस set_अक्षरge_current_limit(gpio_अक्षरger, val->पूर्णांकval);
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक gpio_अक्षरger_property_is_ग_लिखोable(काष्ठा घातer_supply *psy,
					      क्रमागत घातer_supply_property psp)
अणु
	चयन (psp) अणु
	हाल POWER_SUPPLY_PROP_CONSTANT_CHARGE_CURRENT_MAX:
		वापस 1;
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल क्रमागत घातer_supply_type gpio_अक्षरger_get_type(काष्ठा device *dev)
अणु
	स्थिर अक्षर *अक्षरgetype;

	अगर (!device_property_पढ़ो_string(dev, "charger-type", &अक्षरgetype)) अणु
		अगर (!म_भेद("unknown", अक्षरgetype))
			वापस POWER_SUPPLY_TYPE_UNKNOWN;
		अगर (!म_भेद("battery", अक्षरgetype))
			वापस POWER_SUPPLY_TYPE_BATTERY;
		अगर (!म_भेद("ups", अक्षरgetype))
			वापस POWER_SUPPLY_TYPE_UPS;
		अगर (!म_भेद("mains", अक्षरgetype))
			वापस POWER_SUPPLY_TYPE_MAINS;
		अगर (!म_भेद("usb-sdp", अक्षरgetype))
			वापस POWER_SUPPLY_TYPE_USB;
		अगर (!म_भेद("usb-dcp", अक्षरgetype))
			वापस POWER_SUPPLY_TYPE_USB;
		अगर (!म_भेद("usb-cdp", अक्षरgetype))
			वापस POWER_SUPPLY_TYPE_USB;
		अगर (!म_भेद("usb-aca", अक्षरgetype))
			वापस POWER_SUPPLY_TYPE_USB;
	पूर्ण
	dev_warn(dev, "unknown charger type %s\n", अक्षरgetype);

	वापस POWER_SUPPLY_TYPE_UNKNOWN;
पूर्ण

अटल पूर्णांक gpio_अक्षरger_get_irq(काष्ठा device *dev, व्योम *dev_id,
				काष्ठा gpio_desc *gpio)
अणु
	पूर्णांक ret, irq = gpiod_to_irq(gpio);

	अगर (irq > 0) अणु
		ret = devm_request_any_context_irq(dev, irq, gpio_अक्षरger_irq,
						   IRQF_TRIGGER_RISING |
						   IRQF_TRIGGER_FALLING,
						   dev_name(dev),
						   dev_id);
		अगर (ret < 0) अणु
			dev_warn(dev, "Failed to request irq: %d\n", ret);
			irq = 0;
		पूर्ण
	पूर्ण

	वापस irq;
पूर्ण

अटल पूर्णांक init_अक्षरge_current_limit(काष्ठा device *dev,
				    काष्ठा gpio_अक्षरger *gpio_अक्षरger)
अणु
	पूर्णांक i, len;
	u32 cur_limit = U32_MAX;

	gpio_अक्षरger->current_limit_gpios = devm_gpiod_get_array_optional(dev,
		"charge-current-limit", GPIOD_OUT_LOW);
	अगर (IS_ERR(gpio_अक्षरger->current_limit_gpios)) अणु
		dev_err(dev, "error getting current-limit GPIOs\n");
		वापस PTR_ERR(gpio_अक्षरger->current_limit_gpios);
	पूर्ण

	अगर (!gpio_अक्षरger->current_limit_gpios)
		वापस 0;

	len = device_property_पढ़ो_u32_array(dev, "charge-current-limit-mapping",
		शून्य, 0);
	अगर (len < 0)
		वापस len;

	अगर (len == 0 || len % 2) अणु
		dev_err(dev, "invalid charge-current-limit-mapping length\n");
		वापस -EINVAL;
	पूर्ण

	gpio_अक्षरger->current_limit_map = devm_kदो_स्मृति_array(dev,
		len / 2, माप(*gpio_अक्षरger->current_limit_map), GFP_KERNEL);
	अगर (!gpio_अक्षरger->current_limit_map)
		वापस -ENOMEM;

	gpio_अक्षरger->current_limit_map_size = len / 2;

	len = device_property_पढ़ो_u32_array(dev, "charge-current-limit-mapping",
		(u32*) gpio_अक्षरger->current_limit_map, len);
	अगर (len < 0)
		वापस len;

	क्रम (i=0; i < gpio_अक्षरger->current_limit_map_size; i++) अणु
		अगर (gpio_अक्षरger->current_limit_map[i].limit_ua > cur_limit) अणु
			dev_err(dev, "charge-current-limit-mapping not sorted by current in descending order\n");
			वापस -EINVAL;
		पूर्ण

		cur_limit = gpio_अक्षरger->current_limit_map[i].limit_ua;
	पूर्ण

	/* शेष to smallest current limitation क्रम safety reasons */
	len = gpio_अक्षरger->current_limit_map_size - 1;
	set_अक्षरge_current_limit(gpio_अक्षरger,
		gpio_अक्षरger->current_limit_map[len].limit_ua);

	वापस 0;
पूर्ण

/*
 * The entries will be overwritten by driver's probe routine depending
 * on the available features. This list ensures, that the array is big
 * enough क्रम all optional features.
 */
अटल क्रमागत घातer_supply_property gpio_अक्षरger_properties[] = अणु
	POWER_SUPPLY_PROP_ONLINE,
	POWER_SUPPLY_PROP_STATUS,
	POWER_SUPPLY_PROP_CONSTANT_CHARGE_CURRENT_MAX,
पूर्ण;

अटल पूर्णांक gpio_अक्षरger_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	स्थिर काष्ठा gpio_अक्षरger_platक्रमm_data *pdata = dev->platक्रमm_data;
	काष्ठा घातer_supply_config psy_cfg = अणुपूर्ण;
	काष्ठा gpio_अक्षरger *gpio_अक्षरger;
	काष्ठा घातer_supply_desc *अक्षरger_desc;
	काष्ठा gpio_desc *अक्षरge_status;
	पूर्णांक अक्षरge_status_irq;
	पूर्णांक ret;
	पूर्णांक num_props = 0;

	अगर (!pdata && !dev->of_node) अणु
		dev_err(dev, "No platform data\n");
		वापस -ENOENT;
	पूर्ण

	gpio_अक्षरger = devm_kzalloc(dev, माप(*gpio_अक्षरger), GFP_KERNEL);
	अगर (!gpio_अक्षरger)
		वापस -ENOMEM;
	gpio_अक्षरger->dev = dev;

	/*
	 * This will fetch a GPIO descriptor from device tree, ACPI or
	 * boardfile descriptor tables. It's good to try this first.
	 */
	gpio_अक्षरger->gpiod = devm_gpiod_get_optional(dev, शून्य, GPIOD_IN);
	अगर (IS_ERR(gpio_अक्षरger->gpiod)) अणु
		/* Just try again अगर this happens */
		वापस dev_err_probe(dev, PTR_ERR(gpio_अक्षरger->gpiod),
				     "error getting GPIO descriptor\n");
	पूर्ण

	अगर (gpio_अक्षरger->gpiod) अणु
		gpio_अक्षरger_properties[num_props] = POWER_SUPPLY_PROP_ONLINE;
		num_props++;
	पूर्ण

	अक्षरge_status = devm_gpiod_get_optional(dev, "charge-status", GPIOD_IN);
	अगर (IS_ERR(अक्षरge_status))
		वापस PTR_ERR(अक्षरge_status);
	अगर (अक्षरge_status) अणु
		gpio_अक्षरger->अक्षरge_status = अक्षरge_status;
		gpio_अक्षरger_properties[num_props] = POWER_SUPPLY_PROP_STATUS;
		num_props++;
	पूर्ण

	ret = init_अक्षरge_current_limit(dev, gpio_अक्षरger);
	अगर (ret < 0)
		वापस ret;
	अगर (gpio_अक्षरger->current_limit_map) अणु
		gpio_अक्षरger_properties[num_props] =
			POWER_SUPPLY_PROP_CONSTANT_CHARGE_CURRENT_MAX;
		num_props++;
	पूर्ण

	अक्षरger_desc = &gpio_अक्षरger->अक्षरger_desc;
	अक्षरger_desc->properties = gpio_अक्षरger_properties;
	अक्षरger_desc->num_properties = num_props;
	अक्षरger_desc->get_property = gpio_अक्षरger_get_property;
	अक्षरger_desc->set_property = gpio_अक्षरger_set_property;
	अक्षरger_desc->property_is_ग_लिखोable =
					gpio_अक्षरger_property_is_ग_लिखोable;

	psy_cfg.of_node = dev->of_node;
	psy_cfg.drv_data = gpio_अक्षरger;

	अगर (pdata) अणु
		अक्षरger_desc->name = pdata->name;
		अक्षरger_desc->type = pdata->type;
		psy_cfg.supplied_to = pdata->supplied_to;
		psy_cfg.num_supplicants = pdata->num_supplicants;
	पूर्ण अन्यथा अणु
		अक्षरger_desc->name = dev->of_node->name;
		अक्षरger_desc->type = gpio_अक्षरger_get_type(dev);
	पूर्ण

	अगर (!अक्षरger_desc->name)
		अक्षरger_desc->name = pdev->name;

	gpio_अक्षरger->अक्षरger = devm_घातer_supply_रेजिस्टर(dev, अक्षरger_desc,
							   &psy_cfg);
	अगर (IS_ERR(gpio_अक्षरger->अक्षरger)) अणु
		ret = PTR_ERR(gpio_अक्षरger->अक्षरger);
		dev_err(dev, "Failed to register power supply: %d\n", ret);
		वापस ret;
	पूर्ण

	gpio_अक्षरger->irq = gpio_अक्षरger_get_irq(dev, gpio_अक्षरger->अक्षरger,
						 gpio_अक्षरger->gpiod);

	अक्षरge_status_irq = gpio_अक्षरger_get_irq(dev, gpio_अक्षरger->अक्षरger,
						 gpio_अक्षरger->अक्षरge_status);
	gpio_अक्षरger->अक्षरge_status_irq = अक्षरge_status_irq;

	platक्रमm_set_drvdata(pdev, gpio_अक्षरger);

	device_init_wakeup(dev, 1);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक gpio_अक्षरger_suspend(काष्ठा device *dev)
अणु
	काष्ठा gpio_अक्षरger *gpio_अक्षरger = dev_get_drvdata(dev);

	अगर (device_may_wakeup(dev))
		gpio_अक्षरger->wakeup_enabled =
			!enable_irq_wake(gpio_अक्षरger->irq);

	वापस 0;
पूर्ण

अटल पूर्णांक gpio_अक्षरger_resume(काष्ठा device *dev)
अणु
	काष्ठा gpio_अक्षरger *gpio_अक्षरger = dev_get_drvdata(dev);

	अगर (device_may_wakeup(dev) && gpio_अक्षरger->wakeup_enabled)
		disable_irq_wake(gpio_अक्षरger->irq);
	घातer_supply_changed(gpio_अक्षरger->अक्षरger);

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(gpio_अक्षरger_pm_ops,
		gpio_अक्षरger_suspend, gpio_अक्षरger_resume);

अटल स्थिर काष्ठा of_device_id gpio_अक्षरger_match[] = अणु
	अणु .compatible = "gpio-charger" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, gpio_अक्षरger_match);

अटल काष्ठा platक्रमm_driver gpio_अक्षरger_driver = अणु
	.probe = gpio_अक्षरger_probe,
	.driver = अणु
		.name = "gpio-charger",
		.pm = &gpio_अक्षरger_pm_ops,
		.of_match_table = gpio_अक्षरger_match,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(gpio_अक्षरger_driver);

MODULE_AUTHOR("Lars-Peter Clausen <lars@metafoo.de>");
MODULE_DESCRIPTION("Driver for chargers only communicating via GPIO(s)");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:gpio-charger");
