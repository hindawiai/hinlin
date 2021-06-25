<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Power supply driver क्रम the goldfish emulator
 *
 * Copyright (C) 2008 Google, Inc.
 * Copyright (C) 2012 Intel, Inc.
 * Copyright (C) 2013 Intel, Inc.
 * Author: Mike Lockwood <lockwood@android.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/err.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/घातer_supply.h>
#समावेश <linux/types.h>
#समावेश <linux/pci.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/acpi.h>

काष्ठा goldfish_battery_data अणु
	व्योम __iomem *reg_base;
	पूर्णांक irq;
	spinlock_t lock;

	काष्ठा घातer_supply *battery;
	काष्ठा घातer_supply *ac;
पूर्ण;

#घोषणा GOLDFISH_BATTERY_READ(data, addr) \
	(पढ़ोl(data->reg_base + addr))
#घोषणा GOLDFISH_BATTERY_WRITE(data, addr, x) \
	(ग_लिखोl(x, data->reg_base + addr))

क्रमागत अणु
	/* status रेजिस्टर */
	BATTERY_INT_STATUS	= 0x00,
	/* set this to enable IRQ */
	BATTERY_INT_ENABLE	= 0x04,

	BATTERY_AC_ONLINE	= 0x08,
	BATTERY_STATUS		= 0x0C,
	BATTERY_HEALTH		= 0x10,
	BATTERY_PRESENT		= 0x14,
	BATTERY_CAPACITY	= 0x18,
	BATTERY_VOLTAGE		= 0x1C,
	BATTERY_TEMP		= 0x20,
	BATTERY_CHARGE_COUNTER	= 0x24,
	BATTERY_VOLTAGE_MAX	= 0x28,
	BATTERY_CURRENT_MAX	= 0x2C,
	BATTERY_CURRENT_NOW	= 0x30,
	BATTERY_CURRENT_AVG	= 0x34,
	BATTERY_CHARGE_FULL_UAH	= 0x38,
	BATTERY_CYCLE_COUNT	= 0x40,

	BATTERY_STATUS_CHANGED	= 1U << 0,
	AC_STATUS_CHANGED	= 1U << 1,
	BATTERY_INT_MASK	= BATTERY_STATUS_CHANGED | AC_STATUS_CHANGED,
पूर्ण;


अटल पूर्णांक goldfish_ac_get_property(काष्ठा घातer_supply *psy,
			क्रमागत घातer_supply_property psp,
			जोड़ घातer_supply_propval *val)
अणु
	काष्ठा goldfish_battery_data *data = घातer_supply_get_drvdata(psy);
	पूर्णांक ret = 0;

	चयन (psp) अणु
	हाल POWER_SUPPLY_PROP_ONLINE:
		val->पूर्णांकval = GOLDFISH_BATTERY_READ(data, BATTERY_AC_ONLINE);
		अवरोध;
	हाल POWER_SUPPLY_PROP_VOLTAGE_MAX:
		val->पूर्णांकval = GOLDFISH_BATTERY_READ(data, BATTERY_VOLTAGE_MAX);
		अवरोध;
	हाल POWER_SUPPLY_PROP_CURRENT_MAX:
		val->पूर्णांकval = GOLDFISH_BATTERY_READ(data, BATTERY_CURRENT_MAX);
		अवरोध;
	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक goldfish_battery_get_property(काष्ठा घातer_supply *psy,
				 क्रमागत घातer_supply_property psp,
				 जोड़ घातer_supply_propval *val)
अणु
	काष्ठा goldfish_battery_data *data = घातer_supply_get_drvdata(psy);
	पूर्णांक ret = 0;

	चयन (psp) अणु
	हाल POWER_SUPPLY_PROP_STATUS:
		val->पूर्णांकval = GOLDFISH_BATTERY_READ(data, BATTERY_STATUS);
		अवरोध;
	हाल POWER_SUPPLY_PROP_HEALTH:
		val->पूर्णांकval = GOLDFISH_BATTERY_READ(data, BATTERY_HEALTH);
		अवरोध;
	हाल POWER_SUPPLY_PROP_PRESENT:
		val->पूर्णांकval = GOLDFISH_BATTERY_READ(data, BATTERY_PRESENT);
		अवरोध;
	हाल POWER_SUPPLY_PROP_TECHNOLOGY:
		val->पूर्णांकval = POWER_SUPPLY_TECHNOLOGY_LION;
		अवरोध;
	हाल POWER_SUPPLY_PROP_CAPACITY:
		val->पूर्णांकval = GOLDFISH_BATTERY_READ(data, BATTERY_CAPACITY);
		अवरोध;
	हाल POWER_SUPPLY_PROP_VOLTAGE_NOW:
		val->पूर्णांकval = GOLDFISH_BATTERY_READ(data, BATTERY_VOLTAGE);
		अवरोध;
	हाल POWER_SUPPLY_PROP_TEMP:
		val->पूर्णांकval = GOLDFISH_BATTERY_READ(data, BATTERY_TEMP);
		अवरोध;
	हाल POWER_SUPPLY_PROP_CHARGE_COUNTER:
		val->पूर्णांकval = GOLDFISH_BATTERY_READ(data,
						    BATTERY_CHARGE_COUNTER);
		अवरोध;
	हाल POWER_SUPPLY_PROP_CURRENT_NOW:
		val->पूर्णांकval = GOLDFISH_BATTERY_READ(data, BATTERY_CURRENT_NOW);
		अवरोध;
	हाल POWER_SUPPLY_PROP_CURRENT_AVG:
		val->पूर्णांकval = GOLDFISH_BATTERY_READ(data, BATTERY_CURRENT_AVG);
		अवरोध;
	हाल POWER_SUPPLY_PROP_CHARGE_FULL:
		val->पूर्णांकval = GOLDFISH_BATTERY_READ(data,
						    BATTERY_CHARGE_FULL_UAH);
		अवरोध;
	हाल POWER_SUPPLY_PROP_CYCLE_COUNT:
		val->पूर्णांकval = GOLDFISH_BATTERY_READ(data, BATTERY_CYCLE_COUNT);
		अवरोध;
	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल क्रमागत घातer_supply_property goldfish_battery_props[] = अणु
	POWER_SUPPLY_PROP_STATUS,
	POWER_SUPPLY_PROP_HEALTH,
	POWER_SUPPLY_PROP_PRESENT,
	POWER_SUPPLY_PROP_TECHNOLOGY,
	POWER_SUPPLY_PROP_CAPACITY,
	POWER_SUPPLY_PROP_VOLTAGE_NOW,
	POWER_SUPPLY_PROP_TEMP,
	POWER_SUPPLY_PROP_CHARGE_COUNTER,
	POWER_SUPPLY_PROP_CURRENT_NOW,
	POWER_SUPPLY_PROP_CURRENT_AVG,
	POWER_SUPPLY_PROP_CHARGE_FULL,
	POWER_SUPPLY_PROP_CYCLE_COUNT,
पूर्ण;

अटल क्रमागत घातer_supply_property goldfish_ac_props[] = अणु
	POWER_SUPPLY_PROP_ONLINE,
	POWER_SUPPLY_PROP_VOLTAGE_MAX,
	POWER_SUPPLY_PROP_CURRENT_MAX,
पूर्ण;

अटल irqवापस_t goldfish_battery_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	अचिन्हित दीर्घ irq_flags;
	काष्ठा goldfish_battery_data *data = dev_id;
	uपूर्णांक32_t status;

	spin_lock_irqsave(&data->lock, irq_flags);

	/* पढ़ो status flags, which will clear the पूर्णांकerrupt */
	status = GOLDFISH_BATTERY_READ(data, BATTERY_INT_STATUS);
	status &= BATTERY_INT_MASK;

	अगर (status & BATTERY_STATUS_CHANGED)
		घातer_supply_changed(data->battery);
	अगर (status & AC_STATUS_CHANGED)
		घातer_supply_changed(data->ac);

	spin_unlock_irqrestore(&data->lock, irq_flags);
	वापस status ? IRQ_HANDLED : IRQ_NONE;
पूर्ण

अटल स्थिर काष्ठा घातer_supply_desc battery_desc = अणु
	.properties	= goldfish_battery_props,
	.num_properties	= ARRAY_SIZE(goldfish_battery_props),
	.get_property	= goldfish_battery_get_property,
	.name		= "battery",
	.type		= POWER_SUPPLY_TYPE_BATTERY,
पूर्ण;

अटल स्थिर काष्ठा घातer_supply_desc ac_desc = अणु
	.properties	= goldfish_ac_props,
	.num_properties	= ARRAY_SIZE(goldfish_ac_props),
	.get_property	= goldfish_ac_get_property,
	.name		= "ac",
	.type		= POWER_SUPPLY_TYPE_MAINS,
पूर्ण;

अटल पूर्णांक goldfish_battery_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक ret;
	काष्ठा resource *r;
	काष्ठा goldfish_battery_data *data;
	काष्ठा घातer_supply_config psy_cfg = अणुपूर्ण;

	data = devm_kzalloc(&pdev->dev, माप(*data), GFP_KERNEL);
	अगर (data == शून्य)
		वापस -ENOMEM;

	spin_lock_init(&data->lock);

	r = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (r == शून्य) अणु
		dev_err(&pdev->dev, "platform_get_resource failed\n");
		वापस -ENODEV;
	पूर्ण

	data->reg_base = devm_ioremap(&pdev->dev, r->start, resource_size(r));
	अगर (data->reg_base == शून्य) अणु
		dev_err(&pdev->dev, "unable to remap MMIO\n");
		वापस -ENOMEM;
	पूर्ण

	data->irq = platक्रमm_get_irq(pdev, 0);
	अगर (data->irq < 0) अणु
		dev_err(&pdev->dev, "platform_get_irq failed\n");
		वापस -ENODEV;
	पूर्ण

	ret = devm_request_irq(&pdev->dev, data->irq,
			       goldfish_battery_पूर्णांकerrupt,
			       IRQF_SHARED, pdev->name, data);
	अगर (ret)
		वापस ret;

	psy_cfg.drv_data = data;

	data->ac = घातer_supply_रेजिस्टर(&pdev->dev, &ac_desc, &psy_cfg);
	अगर (IS_ERR(data->ac))
		वापस PTR_ERR(data->ac);

	data->battery = घातer_supply_रेजिस्टर(&pdev->dev, &battery_desc,
						&psy_cfg);
	अगर (IS_ERR(data->battery)) अणु
		घातer_supply_unरेजिस्टर(data->ac);
		वापस PTR_ERR(data->battery);
	पूर्ण

	platक्रमm_set_drvdata(pdev, data);

	GOLDFISH_BATTERY_WRITE(data, BATTERY_INT_ENABLE, BATTERY_INT_MASK);
	वापस 0;
पूर्ण

अटल पूर्णांक goldfish_battery_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा goldfish_battery_data *data = platक्रमm_get_drvdata(pdev);

	घातer_supply_unरेजिस्टर(data->battery);
	घातer_supply_unरेजिस्टर(data->ac);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id goldfish_battery_of_match[] = अणु
	अणु .compatible = "google,goldfish-battery", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, goldfish_battery_of_match);

#अगर_घोषित CONFIG_ACPI
अटल स्थिर काष्ठा acpi_device_id goldfish_battery_acpi_match[] = अणु
	अणु "GFSH0001", 0 पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(acpi, goldfish_battery_acpi_match);
#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver goldfish_battery_device = अणु
	.probe		= goldfish_battery_probe,
	.हटाओ		= goldfish_battery_हटाओ,
	.driver = अणु
		.name = "goldfish-battery",
		.of_match_table = goldfish_battery_of_match,
		.acpi_match_table = ACPI_PTR(goldfish_battery_acpi_match),
	पूर्ण
पूर्ण;
module_platक्रमm_driver(goldfish_battery_device);

MODULE_AUTHOR("Mike Lockwood lockwood@android.com");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Battery driver for the Goldfish emulator");
