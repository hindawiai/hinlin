<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * AXP20X and AXP22X PMICs' ACIN घातer supply driver
 *
 * Copyright (C) 2016 Free Electrons
 *	Quentin Schulz <quentin.schulz@मुक्त-electrons.com>
 */

#समावेश <linux/device.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mfd/axp20x.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm.h>
#समावेश <linux/घातer_supply.h>
#समावेश <linux/regmap.h>
#समावेश <linux/slab.h>
#समावेश <linux/iio/consumer.h>

#घोषणा AXP20X_PWR_STATUS_ACIN_PRESENT	BIT(7)
#घोषणा AXP20X_PWR_STATUS_ACIN_AVAIL	BIT(6)

#घोषणा AXP813_ACIN_PATH_SEL		BIT(7)
#घोषणा AXP813_ACIN_PATH_SEL_TO_BIT(x)	(!!(x) << 7)

#घोषणा AXP813_VHOLD_MASK		GENMASK(5, 3)
#घोषणा AXP813_VHOLD_UV_TO_BIT(x)	((((x) / 100000) - 40) << 3)
#घोषणा AXP813_VHOLD_REG_TO_UV(x)	\
	(((((x) & AXP813_VHOLD_MASK) >> 3) + 40) * 100000)

#घोषणा AXP813_CURR_LIMIT_MASK		GENMASK(2, 0)
#घोषणा AXP813_CURR_LIMIT_UA_TO_BIT(x)	(((x) / 500000) - 3)
#घोषणा AXP813_CURR_LIMIT_REG_TO_UA(x)	\
	((((x) & AXP813_CURR_LIMIT_MASK) + 3) * 500000)

#घोषणा DRVNAME "axp20x-ac-power-supply"

काष्ठा axp20x_ac_घातer अणु
	काष्ठा regmap *regmap;
	काष्ठा घातer_supply *supply;
	काष्ठा iio_channel *acin_v;
	काष्ठा iio_channel *acin_i;
	bool has_acin_path_sel;
	अचिन्हित पूर्णांक num_irqs;
	अचिन्हित पूर्णांक irqs[];
पूर्ण;

अटल irqवापस_t axp20x_ac_घातer_irq(पूर्णांक irq, व्योम *devid)
अणु
	काष्ठा axp20x_ac_घातer *घातer = devid;

	घातer_supply_changed(घातer->supply);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक axp20x_ac_घातer_get_property(काष्ठा घातer_supply *psy,
					क्रमागत घातer_supply_property psp,
					जोड़ घातer_supply_propval *val)
अणु
	काष्ठा axp20x_ac_घातer *घातer = घातer_supply_get_drvdata(psy);
	पूर्णांक ret, reg;

	चयन (psp) अणु
	हाल POWER_SUPPLY_PROP_HEALTH:
		ret = regmap_पढ़ो(घातer->regmap, AXP20X_PWR_INPUT_STATUS, &reg);
		अगर (ret)
			वापस ret;

		अगर (reg & AXP20X_PWR_STATUS_ACIN_PRESENT) अणु
			val->पूर्णांकval = POWER_SUPPLY_HEALTH_GOOD;
			वापस 0;
		पूर्ण

		val->पूर्णांकval = POWER_SUPPLY_HEALTH_UNKNOWN;
		वापस 0;

	हाल POWER_SUPPLY_PROP_PRESENT:
		ret = regmap_पढ़ो(घातer->regmap, AXP20X_PWR_INPUT_STATUS, &reg);
		अगर (ret)
			वापस ret;

		val->पूर्णांकval = !!(reg & AXP20X_PWR_STATUS_ACIN_PRESENT);
		वापस 0;

	हाल POWER_SUPPLY_PROP_ONLINE:
		ret = regmap_पढ़ो(घातer->regmap, AXP20X_PWR_INPUT_STATUS, &reg);
		अगर (ret)
			वापस ret;

		val->पूर्णांकval = !!(reg & AXP20X_PWR_STATUS_ACIN_AVAIL);

		/* ACIN_PATH_SEL disables ACIN even अगर ACIN_AVAIL is set. */
		अगर (val->पूर्णांकval && घातer->has_acin_path_sel) अणु
			ret = regmap_पढ़ो(घातer->regmap, AXP813_ACIN_PATH_CTRL,
					  &reg);
			अगर (ret)
				वापस ret;

			val->पूर्णांकval = !!(reg & AXP813_ACIN_PATH_SEL);
		पूर्ण

		वापस 0;

	हाल POWER_SUPPLY_PROP_VOLTAGE_NOW:
		ret = iio_पढ़ो_channel_processed(घातer->acin_v, &val->पूर्णांकval);
		अगर (ret)
			वापस ret;

		/* IIO framework gives mV but Power Supply framework gives uV */
		val->पूर्णांकval *= 1000;

		वापस 0;

	हाल POWER_SUPPLY_PROP_CURRENT_NOW:
		ret = iio_पढ़ो_channel_processed(घातer->acin_i, &val->पूर्णांकval);
		अगर (ret)
			वापस ret;

		/* IIO framework gives mA but Power Supply framework gives uA */
		val->पूर्णांकval *= 1000;

		वापस 0;

	हाल POWER_SUPPLY_PROP_VOLTAGE_MIN:
		ret = regmap_पढ़ो(घातer->regmap, AXP813_ACIN_PATH_CTRL, &reg);
		अगर (ret)
			वापस ret;

		val->पूर्णांकval = AXP813_VHOLD_REG_TO_UV(reg);

		वापस 0;

	हाल POWER_SUPPLY_PROP_INPUT_CURRENT_LIMIT:
		ret = regmap_पढ़ो(घातer->regmap, AXP813_ACIN_PATH_CTRL, &reg);
		अगर (ret)
			वापस ret;

		val->पूर्णांकval = AXP813_CURR_LIMIT_REG_TO_UA(reg);
		/* AXP813 datasheet defines values 11x as 4000mA */
		अगर (val->पूर्णांकval > 4000000)
			val->पूर्णांकval = 4000000;

		वापस 0;

	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक axp813_ac_घातer_set_property(काष्ठा घातer_supply *psy,
					क्रमागत घातer_supply_property psp,
					स्थिर जोड़ घातer_supply_propval *val)
अणु
	काष्ठा axp20x_ac_घातer *घातer = घातer_supply_get_drvdata(psy);

	चयन (psp) अणु
	हाल POWER_SUPPLY_PROP_ONLINE:
		वापस regmap_update_bits(घातer->regmap, AXP813_ACIN_PATH_CTRL,
					  AXP813_ACIN_PATH_SEL,
					  AXP813_ACIN_PATH_SEL_TO_BIT(val->पूर्णांकval));

	हाल POWER_SUPPLY_PROP_VOLTAGE_MIN:
		अगर (val->पूर्णांकval < 4000000 || val->पूर्णांकval > 4700000)
			वापस -EINVAL;

		वापस regmap_update_bits(घातer->regmap, AXP813_ACIN_PATH_CTRL,
					  AXP813_VHOLD_MASK,
					  AXP813_VHOLD_UV_TO_BIT(val->पूर्णांकval));

	हाल POWER_SUPPLY_PROP_INPUT_CURRENT_LIMIT:
		अगर (val->पूर्णांकval < 1500000 || val->पूर्णांकval > 4000000)
			वापस -EINVAL;

		वापस regmap_update_bits(घातer->regmap, AXP813_ACIN_PATH_CTRL,
					  AXP813_CURR_LIMIT_MASK,
					  AXP813_CURR_LIMIT_UA_TO_BIT(val->पूर्णांकval));

	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक axp813_ac_घातer_prop_ग_लिखोable(काष्ठा घातer_supply *psy,
					  क्रमागत घातer_supply_property psp)
अणु
	वापस psp == POWER_SUPPLY_PROP_ONLINE ||
	       psp == POWER_SUPPLY_PROP_VOLTAGE_MIN ||
	       psp == POWER_SUPPLY_PROP_INPUT_CURRENT_LIMIT;
पूर्ण

अटल क्रमागत घातer_supply_property axp20x_ac_घातer_properties[] = अणु
	POWER_SUPPLY_PROP_HEALTH,
	POWER_SUPPLY_PROP_PRESENT,
	POWER_SUPPLY_PROP_ONLINE,
	POWER_SUPPLY_PROP_VOLTAGE_NOW,
	POWER_SUPPLY_PROP_CURRENT_NOW,
पूर्ण;

अटल क्रमागत घातer_supply_property axp22x_ac_घातer_properties[] = अणु
	POWER_SUPPLY_PROP_HEALTH,
	POWER_SUPPLY_PROP_PRESENT,
	POWER_SUPPLY_PROP_ONLINE,
पूर्ण;

अटल क्रमागत घातer_supply_property axp813_ac_घातer_properties[] = अणु
	POWER_SUPPLY_PROP_HEALTH,
	POWER_SUPPLY_PROP_PRESENT,
	POWER_SUPPLY_PROP_ONLINE,
	POWER_SUPPLY_PROP_VOLTAGE_MIN,
	POWER_SUPPLY_PROP_INPUT_CURRENT_LIMIT,
पूर्ण;

अटल स्थिर काष्ठा घातer_supply_desc axp20x_ac_घातer_desc = अणु
	.name = "axp20x-ac",
	.type = POWER_SUPPLY_TYPE_MAINS,
	.properties = axp20x_ac_घातer_properties,
	.num_properties = ARRAY_SIZE(axp20x_ac_घातer_properties),
	.get_property = axp20x_ac_घातer_get_property,
पूर्ण;

अटल स्थिर काष्ठा घातer_supply_desc axp22x_ac_घातer_desc = अणु
	.name = "axp22x-ac",
	.type = POWER_SUPPLY_TYPE_MAINS,
	.properties = axp22x_ac_घातer_properties,
	.num_properties = ARRAY_SIZE(axp22x_ac_घातer_properties),
	.get_property = axp20x_ac_घातer_get_property,
पूर्ण;

अटल स्थिर काष्ठा घातer_supply_desc axp813_ac_घातer_desc = अणु
	.name = "axp813-ac",
	.type = POWER_SUPPLY_TYPE_MAINS,
	.properties = axp813_ac_घातer_properties,
	.num_properties = ARRAY_SIZE(axp813_ac_घातer_properties),
	.property_is_ग_लिखोable = axp813_ac_घातer_prop_ग_लिखोable,
	.get_property = axp20x_ac_घातer_get_property,
	.set_property = axp813_ac_घातer_set_property,
पूर्ण;

अटल स्थिर अक्षर * स्थिर axp20x_irq_names[] = अणु
	"ACIN_PLUGIN",
	"ACIN_REMOVAL",
पूर्ण;

काष्ठा axp_data अणु
	स्थिर काष्ठा घातer_supply_desc	*घातer_desc;
	स्थिर अक्षर * स्थिर		*irq_names;
	अचिन्हित पूर्णांक			num_irq_names;
	bool				acin_adc;
	bool				acin_path_sel;
पूर्ण;

अटल स्थिर काष्ठा axp_data axp20x_data = अणु
	.घातer_desc	= &axp20x_ac_घातer_desc,
	.irq_names	= axp20x_irq_names,
	.num_irq_names	= ARRAY_SIZE(axp20x_irq_names),
	.acin_adc	= true,
	.acin_path_sel	= false,
पूर्ण;

अटल स्थिर काष्ठा axp_data axp22x_data = अणु
	.घातer_desc	= &axp22x_ac_घातer_desc,
	.irq_names	= axp20x_irq_names,
	.num_irq_names	= ARRAY_SIZE(axp20x_irq_names),
	.acin_adc	= false,
	.acin_path_sel	= false,
पूर्ण;

अटल स्थिर काष्ठा axp_data axp813_data = अणु
	.घातer_desc	= &axp813_ac_घातer_desc,
	.irq_names	= axp20x_irq_names,
	.num_irq_names	= ARRAY_SIZE(axp20x_irq_names),
	.acin_adc	= false,
	.acin_path_sel	= true,
पूर्ण;

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक axp20x_ac_घातer_suspend(काष्ठा device *dev)
अणु
	काष्ठा axp20x_ac_घातer *घातer = dev_get_drvdata(dev);
	पूर्णांक i = 0;

	/*
	 * Allow wake via ACIN_PLUGIN only.
	 *
	 * As nested thपढ़ोed IRQs are not स्वतःmatically disabled during
	 * suspend, we must explicitly disable the reमुख्यder of the IRQs.
	 */
	अगर (device_may_wakeup(&घातer->supply->dev))
		enable_irq_wake(घातer->irqs[i++]);
	जबतक (i < घातer->num_irqs)
		disable_irq(घातer->irqs[i++]);

	वापस 0;
पूर्ण

अटल पूर्णांक axp20x_ac_घातer_resume(काष्ठा device *dev)
अणु
	काष्ठा axp20x_ac_घातer *घातer = dev_get_drvdata(dev);
	पूर्णांक i = 0;

	अगर (device_may_wakeup(&घातer->supply->dev))
		disable_irq_wake(घातer->irqs[i++]);
	जबतक (i < घातer->num_irqs)
		enable_irq(घातer->irqs[i++]);

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(axp20x_ac_घातer_pm_ops, axp20x_ac_घातer_suspend,
						 axp20x_ac_घातer_resume);

अटल पूर्णांक axp20x_ac_घातer_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा axp20x_dev *axp20x = dev_get_drvdata(pdev->dev.parent);
	काष्ठा घातer_supply_config psy_cfg = अणुपूर्ण;
	काष्ठा axp20x_ac_घातer *घातer;
	स्थिर काष्ठा axp_data *axp_data;
	पूर्णांक i, irq, ret;

	अगर (!of_device_is_available(pdev->dev.of_node))
		वापस -ENODEV;

	अगर (!axp20x) अणु
		dev_err(&pdev->dev, "Parent drvdata not set\n");
		वापस -EINVAL;
	पूर्ण

	axp_data = of_device_get_match_data(&pdev->dev);

	घातer = devm_kzalloc(&pdev->dev,
			     काष्ठा_size(घातer, irqs, axp_data->num_irq_names),
			     GFP_KERNEL);
	अगर (!घातer)
		वापस -ENOMEM;

	अगर (axp_data->acin_adc) अणु
		घातer->acin_v = devm_iio_channel_get(&pdev->dev, "acin_v");
		अगर (IS_ERR(घातer->acin_v)) अणु
			अगर (PTR_ERR(घातer->acin_v) == -ENODEV)
				वापस -EPROBE_DEFER;
			वापस PTR_ERR(घातer->acin_v);
		पूर्ण

		घातer->acin_i = devm_iio_channel_get(&pdev->dev, "acin_i");
		अगर (IS_ERR(घातer->acin_i)) अणु
			अगर (PTR_ERR(घातer->acin_i) == -ENODEV)
				वापस -EPROBE_DEFER;
			वापस PTR_ERR(घातer->acin_i);
		पूर्ण
	पूर्ण

	घातer->regmap = dev_get_regmap(pdev->dev.parent, शून्य);
	घातer->has_acin_path_sel = axp_data->acin_path_sel;
	घातer->num_irqs = axp_data->num_irq_names;

	platक्रमm_set_drvdata(pdev, घातer);

	psy_cfg.of_node = pdev->dev.of_node;
	psy_cfg.drv_data = घातer;

	घातer->supply = devm_घातer_supply_रेजिस्टर(&pdev->dev,
						   axp_data->घातer_desc,
						   &psy_cfg);
	अगर (IS_ERR(घातer->supply))
		वापस PTR_ERR(घातer->supply);

	/* Request irqs after रेजिस्टरing, as irqs may trigger immediately */
	क्रम (i = 0; i < axp_data->num_irq_names; i++) अणु
		irq = platक्रमm_get_irq_byname(pdev, axp_data->irq_names[i]);
		अगर (irq < 0) अणु
			dev_err(&pdev->dev, "No IRQ for %s: %d\n",
				axp_data->irq_names[i], irq);
			वापस irq;
		पूर्ण
		घातer->irqs[i] = regmap_irq_get_virq(axp20x->regmap_irqc, irq);
		ret = devm_request_any_context_irq(&pdev->dev, घातer->irqs[i],
						   axp20x_ac_घातer_irq, 0,
						   DRVNAME, घातer);
		अगर (ret < 0) अणु
			dev_err(&pdev->dev, "Error requesting %s IRQ: %d\n",
				axp_data->irq_names[i], ret);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id axp20x_ac_घातer_match[] = अणु
	अणु
		.compatible = "x-powers,axp202-ac-power-supply",
		.data = &axp20x_data,
	पूर्ण, अणु
		.compatible = "x-powers,axp221-ac-power-supply",
		.data = &axp22x_data,
	पूर्ण, अणु
		.compatible = "x-powers,axp813-ac-power-supply",
		.data = &axp813_data,
	पूर्ण, अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, axp20x_ac_घातer_match);

अटल काष्ठा platक्रमm_driver axp20x_ac_घातer_driver = अणु
	.probe = axp20x_ac_घातer_probe,
	.driver = अणु
		.name		= DRVNAME,
		.of_match_table	= axp20x_ac_घातer_match,
		.pm		= &axp20x_ac_घातer_pm_ops,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(axp20x_ac_घातer_driver);

MODULE_AUTHOR("Quentin Schulz <quentin.schulz@free-electrons.com>");
MODULE_DESCRIPTION("AXP20X and AXP22X PMICs' AC power supply driver");
MODULE_LICENSE("GPL");
