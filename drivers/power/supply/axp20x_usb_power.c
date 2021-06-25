<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * AXP20x PMIC USB घातer supply status driver
 *
 * Copyright (C) 2015 Hans de Goede <hdegoede@redhat.com>
 * Copyright (C) 2014 Bruno Prथऊmont <bonbons@linux-vserver.org>
 */

#समावेश <linux/bitops.h>
#समावेश <linux/device.h>
#समावेश <linux/devm-helpers.h>
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
#समावेश <linux/workqueue.h>

#घोषणा DRVNAME "axp20x-usb-power-supply"

#घोषणा AXP20X_PWR_STATUS_VBUS_PRESENT	BIT(5)
#घोषणा AXP20X_PWR_STATUS_VBUS_USED	BIT(4)

#घोषणा AXP20X_USB_STATUS_VBUS_VALID	BIT(2)

#घोषणा AXP20X_VBUS_PATH_SEL		BIT(7)
#घोषणा AXP20X_VBUS_PATH_SEL_OFFSET	7

#घोषणा AXP20X_VBUS_VHOLD_uV(b)		(4000000 + (((b) >> 3) & 7) * 100000)
#घोषणा AXP20X_VBUS_VHOLD_MASK		GENMASK(5, 3)
#घोषणा AXP20X_VBUS_VHOLD_OFFSET	3
#घोषणा AXP20X_VBUS_CLIMIT_MASK		3
#घोषणा AXP20X_VBUS_CLIMIT_900mA	0
#घोषणा AXP20X_VBUS_CLIMIT_500mA	1
#घोषणा AXP20X_VBUS_CLIMIT_100mA	2
#घोषणा AXP20X_VBUS_CLIMIT_NONE		3

#घोषणा AXP813_VBUS_CLIMIT_900mA	0
#घोषणा AXP813_VBUS_CLIMIT_1500mA	1
#घोषणा AXP813_VBUS_CLIMIT_2000mA	2
#घोषणा AXP813_VBUS_CLIMIT_2500mA	3

#घोषणा AXP20X_ADC_EN1_VBUS_CURR	BIT(2)
#घोषणा AXP20X_ADC_EN1_VBUS_VOLT	BIT(3)

#घोषणा AXP20X_VBUS_MON_VBUS_VALID	BIT(3)

#घोषणा AXP813_BC_EN		BIT(0)

/*
 * Note करो not उठाओ the debounce समय, we must report Vusb high within
 * 100ms otherwise we get Vbus errors in musb.
 */
#घोषणा DEBOUNCE_TIME			msecs_to_jअगरfies(50)

काष्ठा axp20x_usb_घातer अणु
	काष्ठा regmap *regmap;
	काष्ठा घातer_supply *supply;
	क्रमागत axp20x_variants axp20x_id;
	काष्ठा iio_channel *vbus_v;
	काष्ठा iio_channel *vbus_i;
	काष्ठा delayed_work vbus_detect;
	अचिन्हित पूर्णांक old_status;
	अचिन्हित पूर्णांक online;
	अचिन्हित पूर्णांक num_irqs;
	अचिन्हित पूर्णांक irqs[];
पूर्ण;

अटल bool axp20x_usb_vbus_needs_polling(काष्ठा axp20x_usb_घातer *घातer)
अणु
	/*
	 * Polling is only necessary जबतक VBUS is offline. While online, a
	 * present->असलent transition implies an online->offline transition
	 * and will trigger the VBUS_REMOVAL IRQ.
	 */
	अगर (घातer->axp20x_id >= AXP221_ID && !घातer->online)
		वापस true;

	वापस false;
पूर्ण

अटल irqवापस_t axp20x_usb_घातer_irq(पूर्णांक irq, व्योम *devid)
अणु
	काष्ठा axp20x_usb_घातer *घातer = devid;

	घातer_supply_changed(घातer->supply);

	mod_delayed_work(प्रणाली_घातer_efficient_wq, &घातer->vbus_detect, DEBOUNCE_TIME);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम axp20x_usb_घातer_poll_vbus(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा axp20x_usb_घातer *घातer =
		container_of(work, काष्ठा axp20x_usb_घातer, vbus_detect.work);
	अचिन्हित पूर्णांक val;
	पूर्णांक ret;

	ret = regmap_पढ़ो(घातer->regmap, AXP20X_PWR_INPUT_STATUS, &val);
	अगर (ret)
		जाओ out;

	val &= (AXP20X_PWR_STATUS_VBUS_PRESENT | AXP20X_PWR_STATUS_VBUS_USED);
	अगर (val != घातer->old_status)
		घातer_supply_changed(घातer->supply);

	घातer->old_status = val;
	घातer->online = val & AXP20X_PWR_STATUS_VBUS_USED;

out:
	अगर (axp20x_usb_vbus_needs_polling(घातer))
		mod_delayed_work(प्रणाली_घातer_efficient_wq, &घातer->vbus_detect, DEBOUNCE_TIME);
पूर्ण

अटल पूर्णांक axp20x_get_current_max(काष्ठा axp20x_usb_घातer *घातer, पूर्णांक *val)
अणु
	अचिन्हित पूर्णांक v;
	पूर्णांक ret = regmap_पढ़ो(घातer->regmap, AXP20X_VBUS_IPSOUT_MGMT, &v);

	अगर (ret)
		वापस ret;

	चयन (v & AXP20X_VBUS_CLIMIT_MASK) अणु
	हाल AXP20X_VBUS_CLIMIT_100mA:
		अगर (घातer->axp20x_id == AXP221_ID)
			*val = -1; /* No 100mA limit */
		अन्यथा
			*val = 100000;
		अवरोध;
	हाल AXP20X_VBUS_CLIMIT_500mA:
		*val = 500000;
		अवरोध;
	हाल AXP20X_VBUS_CLIMIT_900mA:
		*val = 900000;
		अवरोध;
	हाल AXP20X_VBUS_CLIMIT_NONE:
		*val = -1;
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक axp813_get_current_max(काष्ठा axp20x_usb_घातer *घातer, पूर्णांक *val)
अणु
	अचिन्हित पूर्णांक v;
	पूर्णांक ret = regmap_पढ़ो(घातer->regmap, AXP20X_VBUS_IPSOUT_MGMT, &v);

	अगर (ret)
		वापस ret;

	चयन (v & AXP20X_VBUS_CLIMIT_MASK) अणु
	हाल AXP813_VBUS_CLIMIT_900mA:
		*val = 900000;
		अवरोध;
	हाल AXP813_VBUS_CLIMIT_1500mA:
		*val = 1500000;
		अवरोध;
	हाल AXP813_VBUS_CLIMIT_2000mA:
		*val = 2000000;
		अवरोध;
	हाल AXP813_VBUS_CLIMIT_2500mA:
		*val = 2500000;
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक axp20x_usb_घातer_get_property(काष्ठा घातer_supply *psy,
	क्रमागत घातer_supply_property psp, जोड़ घातer_supply_propval *val)
अणु
	काष्ठा axp20x_usb_घातer *घातer = घातer_supply_get_drvdata(psy);
	अचिन्हित पूर्णांक input, v;
	पूर्णांक ret;

	चयन (psp) अणु
	हाल POWER_SUPPLY_PROP_VOLTAGE_MIN:
		ret = regmap_पढ़ो(घातer->regmap, AXP20X_VBUS_IPSOUT_MGMT, &v);
		अगर (ret)
			वापस ret;

		val->पूर्णांकval = AXP20X_VBUS_VHOLD_uV(v);
		वापस 0;
	हाल POWER_SUPPLY_PROP_VOLTAGE_NOW:
		अगर (IS_ENABLED(CONFIG_AXP20X_ADC)) अणु
			ret = iio_पढ़ो_channel_processed(घातer->vbus_v,
							 &val->पूर्णांकval);
			अगर (ret)
				वापस ret;

			/*
			 * IIO framework gives mV but Power Supply framework
			 * gives uV.
			 */
			val->पूर्णांकval *= 1000;
			वापस 0;
		पूर्ण

		ret = axp20x_पढ़ो_variable_width(घातer->regmap,
						 AXP20X_VBUS_V_ADC_H, 12);
		अगर (ret < 0)
			वापस ret;

		val->पूर्णांकval = ret * 1700; /* 1 step = 1.7 mV */
		वापस 0;
	हाल POWER_SUPPLY_PROP_CURRENT_MAX:
		अगर (घातer->axp20x_id == AXP813_ID)
			वापस axp813_get_current_max(घातer, &val->पूर्णांकval);
		वापस axp20x_get_current_max(घातer, &val->पूर्णांकval);
	हाल POWER_SUPPLY_PROP_CURRENT_NOW:
		अगर (IS_ENABLED(CONFIG_AXP20X_ADC)) अणु
			ret = iio_पढ़ो_channel_processed(घातer->vbus_i,
							 &val->पूर्णांकval);
			अगर (ret)
				वापस ret;

			/*
			 * IIO framework gives mA but Power Supply framework
			 * gives uA.
			 */
			val->पूर्णांकval *= 1000;
			वापस 0;
		पूर्ण

		ret = axp20x_पढ़ो_variable_width(घातer->regmap,
						 AXP20X_VBUS_I_ADC_H, 12);
		अगर (ret < 0)
			वापस ret;

		val->पूर्णांकval = ret * 375; /* 1 step = 0.375 mA */
		वापस 0;
	शेष:
		अवरोध;
	पूर्ण

	/* All the properties below need the input-status reg value */
	ret = regmap_पढ़ो(घातer->regmap, AXP20X_PWR_INPUT_STATUS, &input);
	अगर (ret)
		वापस ret;

	चयन (psp) अणु
	हाल POWER_SUPPLY_PROP_HEALTH:
		अगर (!(input & AXP20X_PWR_STATUS_VBUS_PRESENT)) अणु
			val->पूर्णांकval = POWER_SUPPLY_HEALTH_UNKNOWN;
			अवरोध;
		पूर्ण

		val->पूर्णांकval = POWER_SUPPLY_HEALTH_GOOD;

		अगर (घातer->axp20x_id == AXP202_ID) अणु
			ret = regmap_पढ़ो(घातer->regmap,
					  AXP20X_USB_OTG_STATUS, &v);
			अगर (ret)
				वापस ret;

			अगर (!(v & AXP20X_USB_STATUS_VBUS_VALID))
				val->पूर्णांकval =
					POWER_SUPPLY_HEALTH_UNSPEC_FAILURE;
		पूर्ण
		अवरोध;
	हाल POWER_SUPPLY_PROP_PRESENT:
		val->पूर्णांकval = !!(input & AXP20X_PWR_STATUS_VBUS_PRESENT);
		अवरोध;
	हाल POWER_SUPPLY_PROP_ONLINE:
		val->पूर्णांकval = !!(input & AXP20X_PWR_STATUS_VBUS_USED);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक axp813_usb_घातer_set_online(काष्ठा axp20x_usb_घातer *घातer,
				       पूर्णांक पूर्णांकval)
अणु
	पूर्णांक val = !पूर्णांकval << AXP20X_VBUS_PATH_SEL_OFFSET;

	वापस regmap_update_bits(घातer->regmap,
				  AXP20X_VBUS_IPSOUT_MGMT,
				  AXP20X_VBUS_PATH_SEL, val);
पूर्ण

अटल पूर्णांक axp20x_usb_घातer_set_voltage_min(काष्ठा axp20x_usb_घातer *घातer,
					    पूर्णांक पूर्णांकval)
अणु
	पूर्णांक val;

	चयन (पूर्णांकval) अणु
	हाल 4000000:
	हाल 4100000:
	हाल 4200000:
	हाल 4300000:
	हाल 4400000:
	हाल 4500000:
	हाल 4600000:
	हाल 4700000:
		val = (पूर्णांकval - 4000000) / 100000;
		वापस regmap_update_bits(घातer->regmap,
					  AXP20X_VBUS_IPSOUT_MGMT,
					  AXP20X_VBUS_VHOLD_MASK,
					  val << AXP20X_VBUS_VHOLD_OFFSET);
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक axp813_usb_घातer_set_current_max(काष्ठा axp20x_usb_घातer *घातer,
					    पूर्णांक पूर्णांकval)
अणु
	पूर्णांक val;

	चयन (पूर्णांकval) अणु
	हाल 900000:
		वापस regmap_update_bits(घातer->regmap,
					  AXP20X_VBUS_IPSOUT_MGMT,
					  AXP20X_VBUS_CLIMIT_MASK,
					  AXP813_VBUS_CLIMIT_900mA);
	हाल 1500000:
	हाल 2000000:
	हाल 2500000:
		val = (पूर्णांकval - 1000000) / 500000;
		वापस regmap_update_bits(घातer->regmap,
					  AXP20X_VBUS_IPSOUT_MGMT,
					  AXP20X_VBUS_CLIMIT_MASK, val);
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक axp20x_usb_घातer_set_current_max(काष्ठा axp20x_usb_घातer *घातer,
					    पूर्णांक पूर्णांकval)
अणु
	पूर्णांक val;

	चयन (पूर्णांकval) अणु
	हाल 100000:
		अगर (घातer->axp20x_id == AXP221_ID)
			वापस -EINVAL;
		fallthrough;
	हाल 500000:
	हाल 900000:
		val = (900000 - पूर्णांकval) / 400000;
		वापस regmap_update_bits(घातer->regmap,
					  AXP20X_VBUS_IPSOUT_MGMT,
					  AXP20X_VBUS_CLIMIT_MASK, val);
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक axp20x_usb_घातer_set_property(काष्ठा घातer_supply *psy,
					 क्रमागत घातer_supply_property psp,
					 स्थिर जोड़ घातer_supply_propval *val)
अणु
	काष्ठा axp20x_usb_घातer *घातer = घातer_supply_get_drvdata(psy);

	चयन (psp) अणु
	हाल POWER_SUPPLY_PROP_ONLINE:
		अगर (घातer->axp20x_id != AXP813_ID)
			वापस -EINVAL;
		वापस axp813_usb_घातer_set_online(घातer, val->पूर्णांकval);

	हाल POWER_SUPPLY_PROP_VOLTAGE_MIN:
		वापस axp20x_usb_घातer_set_voltage_min(घातer, val->पूर्णांकval);

	हाल POWER_SUPPLY_PROP_CURRENT_MAX:
		अगर (घातer->axp20x_id == AXP813_ID)
			वापस axp813_usb_घातer_set_current_max(घातer,
								val->पूर्णांकval);
		वापस axp20x_usb_घातer_set_current_max(घातer, val->पूर्णांकval);

	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक axp20x_usb_घातer_prop_ग_लिखोable(काष्ठा घातer_supply *psy,
					   क्रमागत घातer_supply_property psp)
अणु
	काष्ठा axp20x_usb_घातer *घातer = घातer_supply_get_drvdata(psy);

	/*
	 * The VBUS path select flag works dअगरferently on AXP288 and newer:
	 *  - On AXP20x and AXP22x, the flag enables VBUS (ignoring N_VBUSEN).
	 *  - On AXP288 and AXP8xx, the flag disables VBUS (ignoring N_VBUSEN).
	 * We only expose the control on variants where it can be used to क्रमce
	 * the VBUS input offline.
	 */
	अगर (psp == POWER_SUPPLY_PROP_ONLINE)
		वापस घातer->axp20x_id == AXP813_ID;

	वापस psp == POWER_SUPPLY_PROP_VOLTAGE_MIN ||
	       psp == POWER_SUPPLY_PROP_CURRENT_MAX;
पूर्ण

अटल क्रमागत घातer_supply_property axp20x_usb_घातer_properties[] = अणु
	POWER_SUPPLY_PROP_HEALTH,
	POWER_SUPPLY_PROP_PRESENT,
	POWER_SUPPLY_PROP_ONLINE,
	POWER_SUPPLY_PROP_VOLTAGE_MIN,
	POWER_SUPPLY_PROP_VOLTAGE_NOW,
	POWER_SUPPLY_PROP_CURRENT_MAX,
	POWER_SUPPLY_PROP_CURRENT_NOW,
पूर्ण;

अटल क्रमागत घातer_supply_property axp22x_usb_घातer_properties[] = अणु
	POWER_SUPPLY_PROP_HEALTH,
	POWER_SUPPLY_PROP_PRESENT,
	POWER_SUPPLY_PROP_ONLINE,
	POWER_SUPPLY_PROP_VOLTAGE_MIN,
	POWER_SUPPLY_PROP_CURRENT_MAX,
पूर्ण;

अटल स्थिर काष्ठा घातer_supply_desc axp20x_usb_घातer_desc = अणु
	.name = "axp20x-usb",
	.type = POWER_SUPPLY_TYPE_USB,
	.properties = axp20x_usb_घातer_properties,
	.num_properties = ARRAY_SIZE(axp20x_usb_घातer_properties),
	.property_is_ग_लिखोable = axp20x_usb_घातer_prop_ग_लिखोable,
	.get_property = axp20x_usb_घातer_get_property,
	.set_property = axp20x_usb_घातer_set_property,
पूर्ण;

अटल स्थिर काष्ठा घातer_supply_desc axp22x_usb_घातer_desc = अणु
	.name = "axp20x-usb",
	.type = POWER_SUPPLY_TYPE_USB,
	.properties = axp22x_usb_घातer_properties,
	.num_properties = ARRAY_SIZE(axp22x_usb_घातer_properties),
	.property_is_ग_लिखोable = axp20x_usb_घातer_prop_ग_लिखोable,
	.get_property = axp20x_usb_घातer_get_property,
	.set_property = axp20x_usb_घातer_set_property,
पूर्ण;

अटल स्थिर अक्षर * स्थिर axp20x_irq_names[] = अणु
	"VBUS_PLUGIN",
	"VBUS_REMOVAL",
	"VBUS_VALID",
	"VBUS_NOT_VALID",
पूर्ण;

अटल स्थिर अक्षर * स्थिर axp22x_irq_names[] = अणु
	"VBUS_PLUGIN",
	"VBUS_REMOVAL",
पूर्ण;

काष्ठा axp_data अणु
	स्थिर काष्ठा घातer_supply_desc	*घातer_desc;
	स्थिर अक्षर * स्थिर		*irq_names;
	अचिन्हित पूर्णांक			num_irq_names;
	क्रमागत axp20x_variants		axp20x_id;
पूर्ण;

अटल स्थिर काष्ठा axp_data axp202_data = अणु
	.घातer_desc	= &axp20x_usb_घातer_desc,
	.irq_names	= axp20x_irq_names,
	.num_irq_names	= ARRAY_SIZE(axp20x_irq_names),
	.axp20x_id	= AXP202_ID,
पूर्ण;

अटल स्थिर काष्ठा axp_data axp221_data = अणु
	.घातer_desc	= &axp22x_usb_घातer_desc,
	.irq_names	= axp22x_irq_names,
	.num_irq_names	= ARRAY_SIZE(axp22x_irq_names),
	.axp20x_id	= AXP221_ID,
पूर्ण;

अटल स्थिर काष्ठा axp_data axp223_data = अणु
	.घातer_desc	= &axp22x_usb_घातer_desc,
	.irq_names	= axp22x_irq_names,
	.num_irq_names	= ARRAY_SIZE(axp22x_irq_names),
	.axp20x_id	= AXP223_ID,
पूर्ण;

अटल स्थिर काष्ठा axp_data axp813_data = अणु
	.घातer_desc	= &axp22x_usb_घातer_desc,
	.irq_names	= axp22x_irq_names,
	.num_irq_names	= ARRAY_SIZE(axp22x_irq_names),
	.axp20x_id	= AXP813_ID,
पूर्ण;

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक axp20x_usb_घातer_suspend(काष्ठा device *dev)
अणु
	काष्ठा axp20x_usb_घातer *घातer = dev_get_drvdata(dev);
	पूर्णांक i = 0;

	/*
	 * Allow wake via VBUS_PLUGIN only.
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

अटल पूर्णांक axp20x_usb_घातer_resume(काष्ठा device *dev)
अणु
	काष्ठा axp20x_usb_घातer *घातer = dev_get_drvdata(dev);
	पूर्णांक i = 0;

	अगर (device_may_wakeup(&घातer->supply->dev))
		disable_irq_wake(घातer->irqs[i++]);
	जबतक (i < घातer->num_irqs)
		enable_irq(घातer->irqs[i++]);

	mod_delayed_work(प्रणाली_घातer_efficient_wq, &घातer->vbus_detect, DEBOUNCE_TIME);

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(axp20x_usb_घातer_pm_ops, axp20x_usb_घातer_suspend,
						  axp20x_usb_घातer_resume);

अटल पूर्णांक configure_iio_channels(काष्ठा platक्रमm_device *pdev,
				  काष्ठा axp20x_usb_घातer *घातer)
अणु
	घातer->vbus_v = devm_iio_channel_get(&pdev->dev, "vbus_v");
	अगर (IS_ERR(घातer->vbus_v)) अणु
		अगर (PTR_ERR(घातer->vbus_v) == -ENODEV)
			वापस -EPROBE_DEFER;
		वापस PTR_ERR(घातer->vbus_v);
	पूर्ण

	घातer->vbus_i = devm_iio_channel_get(&pdev->dev, "vbus_i");
	अगर (IS_ERR(घातer->vbus_i)) अणु
		अगर (PTR_ERR(घातer->vbus_i) == -ENODEV)
			वापस -EPROBE_DEFER;
		वापस PTR_ERR(घातer->vbus_i);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक configure_adc_रेजिस्टरs(काष्ठा axp20x_usb_घातer *घातer)
अणु
	/* Enable vbus voltage and current measurement */
	वापस regmap_update_bits(घातer->regmap, AXP20X_ADC_EN1,
				  AXP20X_ADC_EN1_VBUS_CURR |
				  AXP20X_ADC_EN1_VBUS_VOLT,
				  AXP20X_ADC_EN1_VBUS_CURR |
				  AXP20X_ADC_EN1_VBUS_VOLT);
पूर्ण

अटल पूर्णांक axp20x_usb_घातer_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा axp20x_dev *axp20x = dev_get_drvdata(pdev->dev.parent);
	काष्ठा घातer_supply_config psy_cfg = अणुपूर्ण;
	काष्ठा axp20x_usb_घातer *घातer;
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

	platक्रमm_set_drvdata(pdev, घातer);

	घातer->axp20x_id = axp_data->axp20x_id;
	घातer->regmap = axp20x->regmap;
	घातer->num_irqs = axp_data->num_irq_names;

	ret = devm_delayed_work_स्वतःcancel(&pdev->dev, &घातer->vbus_detect,
					   axp20x_usb_घातer_poll_vbus);
	अगर (ret)
		वापस ret;

	अगर (घातer->axp20x_id == AXP202_ID) अणु
		/* Enable vbus valid checking */
		ret = regmap_update_bits(घातer->regmap, AXP20X_VBUS_MON,
					 AXP20X_VBUS_MON_VBUS_VALID,
					 AXP20X_VBUS_MON_VBUS_VALID);
		अगर (ret)
			वापस ret;

		अगर (IS_ENABLED(CONFIG_AXP20X_ADC))
			ret = configure_iio_channels(pdev, घातer);
		अन्यथा
			ret = configure_adc_रेजिस्टरs(घातer);

		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (घातer->axp20x_id == AXP813_ID) अणु
		/* Enable USB Battery Charging specअगरication detection */
		ret = regmap_update_bits(axp20x->regmap, AXP288_BC_GLOBAL,
				   AXP813_BC_EN, AXP813_BC_EN);
		अगर (ret)
			वापस ret;
	पूर्ण

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
						   axp20x_usb_घातer_irq, 0,
						   DRVNAME, घातer);
		अगर (ret < 0) अणु
			dev_err(&pdev->dev, "Error requesting %s IRQ: %d\n",
				axp_data->irq_names[i], ret);
			वापस ret;
		पूर्ण
	पूर्ण

	अगर (axp20x_usb_vbus_needs_polling(घातer))
		queue_delayed_work(प्रणाली_घातer_efficient_wq, &घातer->vbus_detect, 0);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id axp20x_usb_घातer_match[] = अणु
	अणु
		.compatible = "x-powers,axp202-usb-power-supply",
		.data = &axp202_data,
	पूर्ण, अणु
		.compatible = "x-powers,axp221-usb-power-supply",
		.data = &axp221_data,
	पूर्ण, अणु
		.compatible = "x-powers,axp223-usb-power-supply",
		.data = &axp223_data,
	पूर्ण, अणु
		.compatible = "x-powers,axp813-usb-power-supply",
		.data = &axp813_data,
	पूर्ण, अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, axp20x_usb_घातer_match);

अटल काष्ठा platक्रमm_driver axp20x_usb_घातer_driver = अणु
	.probe = axp20x_usb_घातer_probe,
	.driver = अणु
		.name		= DRVNAME,
		.of_match_table	= axp20x_usb_घातer_match,
		.pm		= &axp20x_usb_घातer_pm_ops,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(axp20x_usb_घातer_driver);

MODULE_AUTHOR("Hans de Goede <hdegoede@redhat.com>");
MODULE_DESCRIPTION("AXP20x PMIC USB power supply status driver");
MODULE_LICENSE("GPL");
