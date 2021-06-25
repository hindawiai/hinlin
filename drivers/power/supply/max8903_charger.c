<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * max8903_अक्षरger.c - Maxim 8903 USB/Adapter Charger Driver
 *
 * Copyright (C) 2011 Samsung Electronics
 * MyungJoo Ham <myungjoo.ham@samsung.com>
 */

#समावेश <linux/gpio/consumer.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/घातer_supply.h>
#समावेश <linux/platक्रमm_device.h>

काष्ठा max8903_data अणु
	काष्ठा device *dev;
	काष्ठा घातer_supply *psy;
	काष्ठा घातer_supply_desc psy_desc;
	/*
	 * GPIOs
	 * chg, flt, dcm and usus are optional.
	 * करोk or uok must be present.
	 * If करोk is present, cen must be present.
	 */
	काष्ठा gpio_desc *cen; /* Charger Enable input */
	काष्ठा gpio_desc *करोk; /* DC (Adapter) Power OK output */
	काष्ठा gpio_desc *uok; /* USB Power OK output */
	काष्ठा gpio_desc *chg; /* Charger status output */
	काष्ठा gpio_desc *flt; /* Fault output */
	काष्ठा gpio_desc *dcm; /* Current-Limit Mode input (1: DC, 2: USB) */
	काष्ठा gpio_desc *usus; /* USB Suspend Input (1: suspended) */
	bool fault;
	bool usb_in;
	bool ta_in;
पूर्ण;

अटल क्रमागत घातer_supply_property max8903_अक्षरger_props[] = अणु
	POWER_SUPPLY_PROP_STATUS, /* Charger status output */
	POWER_SUPPLY_PROP_ONLINE, /* External घातer source */
	POWER_SUPPLY_PROP_HEALTH, /* Fault or OK */
पूर्ण;

अटल पूर्णांक max8903_get_property(काष्ठा घातer_supply *psy,
		क्रमागत घातer_supply_property psp,
		जोड़ घातer_supply_propval *val)
अणु
	काष्ठा max8903_data *data = घातer_supply_get_drvdata(psy);

	चयन (psp) अणु
	हाल POWER_SUPPLY_PROP_STATUS:
		val->पूर्णांकval = POWER_SUPPLY_STATUS_UNKNOWN;
		अगर (data->chg) अणु
			अगर (gpiod_get_value(data->chg))
				/* CHG निश्चितed */
				val->पूर्णांकval = POWER_SUPPLY_STATUS_CHARGING;
			अन्यथा अगर (data->usb_in || data->ta_in)
				val->पूर्णांकval = POWER_SUPPLY_STATUS_NOT_CHARGING;
			अन्यथा
				val->पूर्णांकval = POWER_SUPPLY_STATUS_DISCHARGING;
		पूर्ण
		अवरोध;
	हाल POWER_SUPPLY_PROP_ONLINE:
		val->पूर्णांकval = 0;
		अगर (data->usb_in || data->ta_in)
			val->पूर्णांकval = 1;
		अवरोध;
	हाल POWER_SUPPLY_PROP_HEALTH:
		val->पूर्णांकval = POWER_SUPPLY_HEALTH_GOOD;
		अगर (data->fault)
			val->पूर्णांकval = POWER_SUPPLY_HEALTH_UNSPEC_FAILURE;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल irqवापस_t max8903_dcin(पूर्णांक irq, व्योम *_data)
अणु
	काष्ठा max8903_data *data = _data;
	bool ta_in;
	क्रमागत घातer_supply_type old_type;

	/*
	 * This means the line is निश्चितed.
	 *
	 * The संकेत is active low, but the inversion is handled in the GPIO
	 * library as the line should be flagged GPIO_ACTIVE_LOW in the device
	 * tree.
	 */
	ta_in = gpiod_get_value(data->करोk);

	अगर (ta_in == data->ta_in)
		वापस IRQ_HANDLED;

	data->ta_in = ta_in;

	/* Set Current-Limit-Mode 1:DC 0:USB */
	अगर (data->dcm)
		gpiod_set_value(data->dcm, ta_in);

	/* Charger Enable / Disable */
	अगर (data->cen) अणु
		पूर्णांक val;

		अगर (ta_in)
			/* Certainly enable अगर DOK is निश्चितed */
			val = 1;
		अन्यथा अगर (data->usb_in)
			/* Enable अगर the USB अक्षरger is enabled */
			val = 1;
		अन्यथा
			/* Else शेष-disable */
			val = 0;

		gpiod_set_value(data->cen, val);
	पूर्ण

	dev_dbg(data->dev, "TA(DC-IN) Charger %s.\n", ta_in ?
			"Connected" : "Disconnected");

	old_type = data->psy_desc.type;

	अगर (data->ta_in)
		data->psy_desc.type = POWER_SUPPLY_TYPE_MAINS;
	अन्यथा अगर (data->usb_in)
		data->psy_desc.type = POWER_SUPPLY_TYPE_USB;
	अन्यथा
		data->psy_desc.type = POWER_SUPPLY_TYPE_BATTERY;

	अगर (old_type != data->psy_desc.type)
		घातer_supply_changed(data->psy);

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t max8903_usbin(पूर्णांक irq, व्योम *_data)
अणु
	काष्ठा max8903_data *data = _data;
	bool usb_in;
	क्रमागत घातer_supply_type old_type;

	/*
	 * This means the line is निश्चितed.
	 *
	 * The संकेत is active low, but the inversion is handled in the GPIO
	 * library as the line should be flagged GPIO_ACTIVE_LOW in the device
	 * tree.
	 */
	usb_in = gpiod_get_value(data->uok);

	अगर (usb_in == data->usb_in)
		वापस IRQ_HANDLED;

	data->usb_in = usb_in;

	/* Do not touch Current-Limit-Mode */

	/* Charger Enable / Disable */
	अगर (data->cen) अणु
		पूर्णांक val;

		अगर (usb_in)
			/* Certainly enable अगर UOK is निश्चितed */
			val = 1;
		अन्यथा अगर (data->ta_in)
			/* Enable अगर the DC अक्षरger is enabled */
			val = 1;
		अन्यथा
			/* Else शेष-disable */
			val = 0;

		gpiod_set_value(data->cen, val);
	पूर्ण

	dev_dbg(data->dev, "USB Charger %s.\n", usb_in ?
			"Connected" : "Disconnected");

	old_type = data->psy_desc.type;

	अगर (data->ta_in)
		data->psy_desc.type = POWER_SUPPLY_TYPE_MAINS;
	अन्यथा अगर (data->usb_in)
		data->psy_desc.type = POWER_SUPPLY_TYPE_USB;
	अन्यथा
		data->psy_desc.type = POWER_SUPPLY_TYPE_BATTERY;

	अगर (old_type != data->psy_desc.type)
		घातer_supply_changed(data->psy);

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t max8903_fault(पूर्णांक irq, व्योम *_data)
अणु
	काष्ठा max8903_data *data = _data;
	bool fault;

	/*
	 * This means the line is निश्चितed.
	 *
	 * The संकेत is active low, but the inversion is handled in the GPIO
	 * library as the line should be flagged GPIO_ACTIVE_LOW in the device
	 * tree.
	 */
	fault = gpiod_get_value(data->flt);

	अगर (fault == data->fault)
		वापस IRQ_HANDLED;

	data->fault = fault;

	अगर (fault)
		dev_err(data->dev, "Charger suffers a fault and stops.\n");
	अन्यथा
		dev_err(data->dev, "Charger recovered from a fault.\n");

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक max8903_setup_gpios(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा max8903_data *data = platक्रमm_get_drvdata(pdev);
	काष्ठा device *dev = &pdev->dev;
	bool ta_in = false;
	bool usb_in = false;
	क्रमागत gpiod_flags flags;

	data->करोk = devm_gpiod_get_optional(dev, "dok", GPIOD_IN);
	अगर (IS_ERR(data->करोk))
		वापस dev_err_probe(dev, PTR_ERR(data->करोk),
				     "failed to get DOK GPIO");
	अगर (data->करोk) अणु
		gpiod_set_consumer_name(data->करोk, data->psy_desc.name);
		/*
		 * The DC OK is pulled up to 1 and goes low when a अक्षरger
		 * is plugged in (active low) but in the device tree the
		 * line is marked as GPIO_ACTIVE_LOW so we get a 1 (निश्चितed)
		 * here अगर the DC अक्षरger is plugged in.
		 */
		ta_in = gpiod_get_value(data->करोk);
	पूर्ण

	data->uok = devm_gpiod_get_optional(dev, "uok", GPIOD_IN);
	अगर (IS_ERR(data->uok))
		वापस dev_err_probe(dev, PTR_ERR(data->uok),
				     "failed to get UOK GPIO");
	अगर (data->uok) अणु
		gpiod_set_consumer_name(data->uok, data->psy_desc.name);
		/*
		 * The USB OK is pulled up to 1 and goes low when a USB अक्षरger
		 * is plugged in (active low) but in the device tree the
		 * line is marked as GPIO_ACTIVE_LOW so we get a 1 (निश्चितed)
		 * here अगर the USB अक्षरger is plugged in.
		 */
		usb_in = gpiod_get_value(data->uok);
	पूर्ण

	/* Either DC OK or USB OK must be provided */
	अगर (!data->करोk && !data->uok) अणु
		dev_err(dev, "no valid power source\n");
		वापस -EINVAL;
	पूर्ण

	/*
	 * If either अक्षरger is alपढ़ोy connected at this poपूर्णांक,
	 * निश्चित the CEN line and enable अक्षरging from the start.
	 *
	 * The line is active low but also marked with GPIO_ACTIVE_LOW
	 * in the device tree, so when we निश्चित the line with
	 * GPIOD_OUT_HIGH the line will be driven low.
	 */
	flags = (ta_in || usb_in) ? GPIOD_OUT_HIGH : GPIOD_OUT_LOW;
	/*
	 * If DC OK is provided, Charger Enable CEN is compulsory
	 * so this is not optional here.
	 */
	data->cen = devm_gpiod_get(dev, "cen", flags);
	अगर (IS_ERR(data->cen))
		वापस dev_err_probe(dev, PTR_ERR(data->cen),
				     "failed to get CEN GPIO");
	gpiod_set_consumer_name(data->cen, data->psy_desc.name);

	/*
	 * If the DC अक्षरger is connected, then select it.
	 *
	 * The DCM line should be marked GPIO_ACTIVE_HIGH in the
	 * device tree. Driving it high will enable the DC अक्षरger
	 * input over the USB अक्षरger input.
	 */
	flags = ta_in ? GPIOD_OUT_HIGH : GPIOD_OUT_LOW;
	data->dcm = devm_gpiod_get_optional(dev, "dcm", flags);
	अगर (IS_ERR(data->dcm))
		वापस dev_err_probe(dev, PTR_ERR(data->dcm),
				     "failed to get DCM GPIO");
	gpiod_set_consumer_name(data->dcm, data->psy_desc.name);

	data->chg = devm_gpiod_get_optional(dev, "chg", GPIOD_IN);
	अगर (IS_ERR(data->chg))
		वापस dev_err_probe(dev, PTR_ERR(data->chg),
				     "failed to get CHG GPIO");
	gpiod_set_consumer_name(data->chg, data->psy_desc.name);

	data->flt = devm_gpiod_get_optional(dev, "flt", GPIOD_IN);
	अगर (IS_ERR(data->flt))
		वापस dev_err_probe(dev, PTR_ERR(data->flt),
				     "failed to get FLT GPIO");
	gpiod_set_consumer_name(data->flt, data->psy_desc.name);

	data->usus = devm_gpiod_get_optional(dev, "usus", GPIOD_IN);
	अगर (IS_ERR(data->usus))
		वापस dev_err_probe(dev, PTR_ERR(data->usus),
				     "failed to get USUS GPIO");
	gpiod_set_consumer_name(data->usus, data->psy_desc.name);

	data->fault = false;
	data->ta_in = ta_in;
	data->usb_in = usb_in;

	वापस 0;
पूर्ण

अटल पूर्णांक max8903_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा max8903_data *data;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा घातer_supply_config psy_cfg = अणुपूर्ण;
	पूर्णांक ret = 0;

	data = devm_kzalloc(dev, माप(काष्ठा max8903_data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	data->dev = dev;
	platक्रमm_set_drvdata(pdev, data);

	ret = max8903_setup_gpios(pdev);
	अगर (ret)
		वापस ret;

	data->psy_desc.name = "max8903_charger";
	data->psy_desc.type = (data->ta_in) ? POWER_SUPPLY_TYPE_MAINS :
			((data->usb_in) ? POWER_SUPPLY_TYPE_USB :
			 POWER_SUPPLY_TYPE_BATTERY);
	data->psy_desc.get_property = max8903_get_property;
	data->psy_desc.properties = max8903_अक्षरger_props;
	data->psy_desc.num_properties = ARRAY_SIZE(max8903_अक्षरger_props);

	psy_cfg.of_node = dev->of_node;
	psy_cfg.drv_data = data;

	data->psy = devm_घातer_supply_रेजिस्टर(dev, &data->psy_desc, &psy_cfg);
	अगर (IS_ERR(data->psy)) अणु
		dev_err(dev, "failed: power supply register.\n");
		वापस PTR_ERR(data->psy);
	पूर्ण

	अगर (data->करोk) अणु
		ret = devm_request_thपढ़ोed_irq(dev, gpiod_to_irq(data->करोk),
					शून्य, max8903_dcin,
					IRQF_TRIGGER_FALLING |
					IRQF_TRIGGER_RISING | IRQF_ONESHOT,
					"MAX8903 DC IN", data);
		अगर (ret) अणु
			dev_err(dev, "Cannot request irq %d for DC (%d)\n",
					gpiod_to_irq(data->करोk), ret);
			वापस ret;
		पूर्ण
	पूर्ण

	अगर (data->uok) अणु
		ret = devm_request_thपढ़ोed_irq(dev, gpiod_to_irq(data->uok),
					शून्य, max8903_usbin,
					IRQF_TRIGGER_FALLING |
					IRQF_TRIGGER_RISING | IRQF_ONESHOT,
					"MAX8903 USB IN", data);
		अगर (ret) अणु
			dev_err(dev, "Cannot request irq %d for USB (%d)\n",
					gpiod_to_irq(data->uok), ret);
			वापस ret;
		पूर्ण
	पूर्ण

	अगर (data->flt) अणु
		ret = devm_request_thपढ़ोed_irq(dev, gpiod_to_irq(data->flt),
					शून्य, max8903_fault,
					IRQF_TRIGGER_FALLING |
					IRQF_TRIGGER_RISING | IRQF_ONESHOT,
					"MAX8903 Fault", data);
		अगर (ret) अणु
			dev_err(dev, "Cannot request irq %d for Fault (%d)\n",
					gpiod_to_irq(data->flt), ret);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id max8903_match_ids[] = अणु
	अणु .compatible = "maxim,max8903", पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, max8903_match_ids);

अटल काष्ठा platक्रमm_driver max8903_driver = अणु
	.probe	= max8903_probe,
	.driver = अणु
		.name	= "max8903-charger",
		.of_match_table = max8903_match_ids
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(max8903_driver);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("MAX8903 Charger Driver");
MODULE_AUTHOR("MyungJoo Ham <myungjoo.ham@samsung.com>");
MODULE_ALIAS("platform:max8903-charger");
