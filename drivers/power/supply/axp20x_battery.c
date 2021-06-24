<शैली गुरु>
/*
 * Battery घातer supply driver क्रम X-Powers AXP20X and AXP22X PMICs
 *
 * Copyright 2016 Free Electrons NextThing Co.
 *	Quentin Schulz <quentin.schulz@मुक्त-electrons.com>
 *
 * This driver is based on a previous upstreaming attempt by:
 *	Bruno Prथऊmont <bonbons@linux-vserver.org>
 *
 * This file is subject to the terms and conditions of the GNU General
 * Public License. See the file "COPYING" in the मुख्य directory of this
 * archive क्रम more details.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License क्रम more details.
 */

#समावेश <linux/err.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/घातer_supply.h>
#समावेश <linux/regmap.h>
#समावेश <linux/slab.h>
#समावेश <linux/समय.स>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/consumer.h>
#समावेश <linux/mfd/axp20x.h>

#घोषणा AXP20X_PWR_STATUS_BAT_CHARGING	BIT(2)

#घोषणा AXP20X_PWR_OP_BATT_PRESENT	BIT(5)
#घोषणा AXP20X_PWR_OP_BATT_ACTIVATED	BIT(3)

#घोषणा AXP209_FG_PERCENT		GENMASK(6, 0)
#घोषणा AXP22X_FG_VALID			BIT(7)

#घोषणा AXP20X_CHRG_CTRL1_TGT_VOLT	GENMASK(6, 5)
#घोषणा AXP20X_CHRG_CTRL1_TGT_4_1V	(0 << 5)
#घोषणा AXP20X_CHRG_CTRL1_TGT_4_15V	(1 << 5)
#घोषणा AXP20X_CHRG_CTRL1_TGT_4_2V	(2 << 5)
#घोषणा AXP20X_CHRG_CTRL1_TGT_4_36V	(3 << 5)

#घोषणा AXP22X_CHRG_CTRL1_TGT_4_22V	(1 << 5)
#घोषणा AXP22X_CHRG_CTRL1_TGT_4_24V	(3 << 5)

#घोषणा AXP813_CHRG_CTRL1_TGT_4_35V	(3 << 5)

#घोषणा AXP20X_CHRG_CTRL1_TGT_CURR	GENMASK(3, 0)

#घोषणा AXP20X_V_OFF_MASK		GENMASK(2, 0)

काष्ठा axp20x_batt_ps;

काष्ठा axp_data अणु
	पूर्णांक	ccc_scale;
	पूर्णांक	ccc_offset;
	bool	has_fg_valid;
	पूर्णांक	(*get_max_voltage)(काष्ठा axp20x_batt_ps *batt, पूर्णांक *val);
	पूर्णांक	(*set_max_voltage)(काष्ठा axp20x_batt_ps *batt, पूर्णांक val);
पूर्ण;

काष्ठा axp20x_batt_ps अणु
	काष्ठा regmap *regmap;
	काष्ठा घातer_supply *batt;
	काष्ठा device *dev;
	काष्ठा iio_channel *batt_chrg_i;
	काष्ठा iio_channel *batt_dischrg_i;
	काष्ठा iio_channel *batt_v;
	/* Maximum स्थिरant अक्षरge current */
	अचिन्हित पूर्णांक max_ccc;
	स्थिर काष्ठा axp_data	*data;
पूर्ण;

अटल पूर्णांक axp20x_battery_get_max_voltage(काष्ठा axp20x_batt_ps *axp20x_batt,
					  पूर्णांक *val)
अणु
	पूर्णांक ret, reg;

	ret = regmap_पढ़ो(axp20x_batt->regmap, AXP20X_CHRG_CTRL1, &reg);
	अगर (ret)
		वापस ret;

	चयन (reg & AXP20X_CHRG_CTRL1_TGT_VOLT) अणु
	हाल AXP20X_CHRG_CTRL1_TGT_4_1V:
		*val = 4100000;
		अवरोध;
	हाल AXP20X_CHRG_CTRL1_TGT_4_15V:
		*val = 4150000;
		अवरोध;
	हाल AXP20X_CHRG_CTRL1_TGT_4_2V:
		*val = 4200000;
		अवरोध;
	हाल AXP20X_CHRG_CTRL1_TGT_4_36V:
		*val = 4360000;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक axp22x_battery_get_max_voltage(काष्ठा axp20x_batt_ps *axp20x_batt,
					  पूर्णांक *val)
अणु
	पूर्णांक ret, reg;

	ret = regmap_पढ़ो(axp20x_batt->regmap, AXP20X_CHRG_CTRL1, &reg);
	अगर (ret)
		वापस ret;

	चयन (reg & AXP20X_CHRG_CTRL1_TGT_VOLT) अणु
	हाल AXP20X_CHRG_CTRL1_TGT_4_1V:
		*val = 4100000;
		अवरोध;
	हाल AXP20X_CHRG_CTRL1_TGT_4_2V:
		*val = 4200000;
		अवरोध;
	हाल AXP22X_CHRG_CTRL1_TGT_4_22V:
		*val = 4220000;
		अवरोध;
	हाल AXP22X_CHRG_CTRL1_TGT_4_24V:
		*val = 4240000;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक axp813_battery_get_max_voltage(काष्ठा axp20x_batt_ps *axp20x_batt,
					  पूर्णांक *val)
अणु
	पूर्णांक ret, reg;

	ret = regmap_पढ़ो(axp20x_batt->regmap, AXP20X_CHRG_CTRL1, &reg);
	अगर (ret)
		वापस ret;

	चयन (reg & AXP20X_CHRG_CTRL1_TGT_VOLT) अणु
	हाल AXP20X_CHRG_CTRL1_TGT_4_1V:
		*val = 4100000;
		अवरोध;
	हाल AXP20X_CHRG_CTRL1_TGT_4_15V:
		*val = 4150000;
		अवरोध;
	हाल AXP20X_CHRG_CTRL1_TGT_4_2V:
		*val = 4200000;
		अवरोध;
	हाल AXP813_CHRG_CTRL1_TGT_4_35V:
		*val = 4350000;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक axp20x_get_स्थिरant_अक्षरge_current(काष्ठा axp20x_batt_ps *axp,
					      पूर्णांक *val)
अणु
	पूर्णांक ret;

	ret = regmap_पढ़ो(axp->regmap, AXP20X_CHRG_CTRL1, val);
	अगर (ret)
		वापस ret;

	*val &= AXP20X_CHRG_CTRL1_TGT_CURR;

	*val = *val * axp->data->ccc_scale + axp->data->ccc_offset;

	वापस 0;
पूर्ण

अटल पूर्णांक axp20x_battery_get_prop(काष्ठा घातer_supply *psy,
				   क्रमागत घातer_supply_property psp,
				   जोड़ घातer_supply_propval *val)
अणु
	काष्ठा axp20x_batt_ps *axp20x_batt = घातer_supply_get_drvdata(psy);
	काष्ठा iio_channel *chan;
	पूर्णांक ret = 0, reg, val1;

	चयन (psp) अणु
	हाल POWER_SUPPLY_PROP_PRESENT:
	हाल POWER_SUPPLY_PROP_ONLINE:
		ret = regmap_पढ़ो(axp20x_batt->regmap, AXP20X_PWR_OP_MODE,
				  &reg);
		अगर (ret)
			वापस ret;

		val->पूर्णांकval = !!(reg & AXP20X_PWR_OP_BATT_PRESENT);
		अवरोध;

	हाल POWER_SUPPLY_PROP_STATUS:
		ret = regmap_पढ़ो(axp20x_batt->regmap, AXP20X_PWR_INPUT_STATUS,
				  &reg);
		अगर (ret)
			वापस ret;

		अगर (reg & AXP20X_PWR_STATUS_BAT_CHARGING) अणु
			val->पूर्णांकval = POWER_SUPPLY_STATUS_CHARGING;
			वापस 0;
		पूर्ण

		ret = iio_पढ़ो_channel_processed(axp20x_batt->batt_dischrg_i,
						 &val1);
		अगर (ret)
			वापस ret;

		अगर (val1) अणु
			val->पूर्णांकval = POWER_SUPPLY_STATUS_DISCHARGING;
			वापस 0;
		पूर्ण

		ret = regmap_पढ़ो(axp20x_batt->regmap, AXP20X_FG_RES, &val1);
		अगर (ret)
			वापस ret;

		/*
		 * Fuel Gauge data takes 7 bits but the stored value seems to be
		 * directly the raw percentage without any scaling to 7 bits.
		 */
		अगर ((val1 & AXP209_FG_PERCENT) == 100)
			val->पूर्णांकval = POWER_SUPPLY_STATUS_FULL;
		अन्यथा
			val->पूर्णांकval = POWER_SUPPLY_STATUS_NOT_CHARGING;
		अवरोध;

	हाल POWER_SUPPLY_PROP_HEALTH:
		ret = regmap_पढ़ो(axp20x_batt->regmap, AXP20X_PWR_OP_MODE,
				  &val1);
		अगर (ret)
			वापस ret;

		अगर (val1 & AXP20X_PWR_OP_BATT_ACTIVATED) अणु
			val->पूर्णांकval = POWER_SUPPLY_HEALTH_DEAD;
			वापस 0;
		पूर्ण

		val->पूर्णांकval = POWER_SUPPLY_HEALTH_GOOD;
		अवरोध;

	हाल POWER_SUPPLY_PROP_CONSTANT_CHARGE_CURRENT:
		ret = axp20x_get_स्थिरant_अक्षरge_current(axp20x_batt,
							 &val->पूर्णांकval);
		अगर (ret)
			वापस ret;
		अवरोध;

	हाल POWER_SUPPLY_PROP_CONSTANT_CHARGE_CURRENT_MAX:
		val->पूर्णांकval = axp20x_batt->max_ccc;
		अवरोध;

	हाल POWER_SUPPLY_PROP_CURRENT_NOW:
		ret = regmap_पढ़ो(axp20x_batt->regmap, AXP20X_PWR_INPUT_STATUS,
				  &reg);
		अगर (ret)
			वापस ret;

		अगर (reg & AXP20X_PWR_STATUS_BAT_CHARGING)
			chan = axp20x_batt->batt_chrg_i;
		अन्यथा
			chan = axp20x_batt->batt_dischrg_i;

		ret = iio_पढ़ो_channel_processed(chan, &val->पूर्णांकval);
		अगर (ret)
			वापस ret;

		/* IIO framework gives mA but Power Supply framework gives uA */
		val->पूर्णांकval *= 1000;
		अवरोध;

	हाल POWER_SUPPLY_PROP_CAPACITY:
		/* When no battery is present, वापस capacity is 100% */
		ret = regmap_पढ़ो(axp20x_batt->regmap, AXP20X_PWR_OP_MODE,
				  &reg);
		अगर (ret)
			वापस ret;

		अगर (!(reg & AXP20X_PWR_OP_BATT_PRESENT)) अणु
			val->पूर्णांकval = 100;
			वापस 0;
		पूर्ण

		ret = regmap_पढ़ो(axp20x_batt->regmap, AXP20X_FG_RES, &reg);
		अगर (ret)
			वापस ret;

		अगर (axp20x_batt->data->has_fg_valid && !(reg & AXP22X_FG_VALID))
			वापस -EINVAL;

		/*
		 * Fuel Gauge data takes 7 bits but the stored value seems to be
		 * directly the raw percentage without any scaling to 7 bits.
		 */
		val->पूर्णांकval = reg & AXP209_FG_PERCENT;
		अवरोध;

	हाल POWER_SUPPLY_PROP_VOLTAGE_MAX_DESIGN:
		वापस axp20x_batt->data->get_max_voltage(axp20x_batt,
							  &val->पूर्णांकval);

	हाल POWER_SUPPLY_PROP_VOLTAGE_MIN_DESIGN:
		ret = regmap_पढ़ो(axp20x_batt->regmap, AXP20X_V_OFF, &reg);
		अगर (ret)
			वापस ret;

		val->पूर्णांकval = 2600000 + 100000 * (reg & AXP20X_V_OFF_MASK);
		अवरोध;

	हाल POWER_SUPPLY_PROP_VOLTAGE_NOW:
		ret = iio_पढ़ो_channel_processed(axp20x_batt->batt_v,
						 &val->पूर्णांकval);
		अगर (ret)
			वापस ret;

		/* IIO framework gives mV but Power Supply framework gives uV */
		val->पूर्णांकval *= 1000;
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक axp22x_battery_set_max_voltage(काष्ठा axp20x_batt_ps *axp20x_batt,
					  पूर्णांक val)
अणु
	चयन (val) अणु
	हाल 4100000:
		val = AXP20X_CHRG_CTRL1_TGT_4_1V;
		अवरोध;

	हाल 4200000:
		val = AXP20X_CHRG_CTRL1_TGT_4_2V;
		अवरोध;

	शेष:
		/*
		 * AXP20x max voltage can be set to 4.36V and AXP22X max voltage
		 * can be set to 4.22V and 4.24V, but these voltages are too
		 * high क्रम Lithium based batteries (AXP PMICs are supposed to
		 * be used with these kinds of battery).
		 */
		वापस -EINVAL;
	पूर्ण

	वापस regmap_update_bits(axp20x_batt->regmap, AXP20X_CHRG_CTRL1,
				  AXP20X_CHRG_CTRL1_TGT_VOLT, val);
पूर्ण

अटल पूर्णांक axp20x_battery_set_max_voltage(काष्ठा axp20x_batt_ps *axp20x_batt,
					  पूर्णांक val)
अणु
	चयन (val) अणु
	हाल 4100000:
		val = AXP20X_CHRG_CTRL1_TGT_4_1V;
		अवरोध;

	हाल 4150000:
		val = AXP20X_CHRG_CTRL1_TGT_4_15V;
		अवरोध;

	हाल 4200000:
		val = AXP20X_CHRG_CTRL1_TGT_4_2V;
		अवरोध;

	शेष:
		/*
		 * AXP20x max voltage can be set to 4.36V and AXP22X max voltage
		 * can be set to 4.22V and 4.24V, but these voltages are too
		 * high क्रम Lithium based batteries (AXP PMICs are supposed to
		 * be used with these kinds of battery).
		 */
		वापस -EINVAL;
	पूर्ण

	वापस regmap_update_bits(axp20x_batt->regmap, AXP20X_CHRG_CTRL1,
				  AXP20X_CHRG_CTRL1_TGT_VOLT, val);
पूर्ण

अटल पूर्णांक axp20x_set_स्थिरant_अक्षरge_current(काष्ठा axp20x_batt_ps *axp_batt,
					      पूर्णांक अक्षरge_current)
अणु
	अगर (अक्षरge_current > axp_batt->max_ccc)
		वापस -EINVAL;

	अक्षरge_current = (अक्षरge_current - axp_batt->data->ccc_offset) /
		axp_batt->data->ccc_scale;

	अगर (अक्षरge_current > AXP20X_CHRG_CTRL1_TGT_CURR || अक्षरge_current < 0)
		वापस -EINVAL;

	वापस regmap_update_bits(axp_batt->regmap, AXP20X_CHRG_CTRL1,
				  AXP20X_CHRG_CTRL1_TGT_CURR, अक्षरge_current);
पूर्ण

अटल पूर्णांक axp20x_set_max_स्थिरant_अक्षरge_current(काष्ठा axp20x_batt_ps *axp,
						  पूर्णांक अक्षरge_current)
अणु
	bool lower_max = false;

	अक्षरge_current = (अक्षरge_current - axp->data->ccc_offset) /
		axp->data->ccc_scale;

	अगर (अक्षरge_current > AXP20X_CHRG_CTRL1_TGT_CURR || अक्षरge_current < 0)
		वापस -EINVAL;

	अक्षरge_current = अक्षरge_current * axp->data->ccc_scale +
		axp->data->ccc_offset;

	अगर (अक्षरge_current > axp->max_ccc)
		dev_warn(axp->dev,
			 "Setting max constant charge current higher than previously defined. Note that increasing the constant charge current may damage your battery.\n");
	अन्यथा
		lower_max = true;

	axp->max_ccc = अक्षरge_current;

	अगर (lower_max) अणु
		पूर्णांक current_cc;

		axp20x_get_स्थिरant_अक्षरge_current(axp, &current_cc);
		अगर (current_cc > अक्षरge_current)
			axp20x_set_स्थिरant_अक्षरge_current(axp, अक्षरge_current);
	पूर्ण

	वापस 0;
पूर्ण
अटल पूर्णांक axp20x_set_voltage_min_design(काष्ठा axp20x_batt_ps *axp_batt,
					 पूर्णांक min_voltage)
अणु
	पूर्णांक val1 = (min_voltage - 2600000) / 100000;

	अगर (val1 < 0 || val1 > AXP20X_V_OFF_MASK)
		वापस -EINVAL;

	वापस regmap_update_bits(axp_batt->regmap, AXP20X_V_OFF,
				  AXP20X_V_OFF_MASK, val1);
पूर्ण

अटल पूर्णांक axp20x_battery_set_prop(काष्ठा घातer_supply *psy,
				   क्रमागत घातer_supply_property psp,
				   स्थिर जोड़ घातer_supply_propval *val)
अणु
	काष्ठा axp20x_batt_ps *axp20x_batt = घातer_supply_get_drvdata(psy);

	चयन (psp) अणु
	हाल POWER_SUPPLY_PROP_VOLTAGE_MIN_DESIGN:
		वापस axp20x_set_voltage_min_design(axp20x_batt, val->पूर्णांकval);

	हाल POWER_SUPPLY_PROP_VOLTAGE_MAX_DESIGN:
		वापस axp20x_batt->data->set_max_voltage(axp20x_batt, val->पूर्णांकval);

	हाल POWER_SUPPLY_PROP_CONSTANT_CHARGE_CURRENT:
		वापस axp20x_set_स्थिरant_अक्षरge_current(axp20x_batt,
							  val->पूर्णांकval);
	हाल POWER_SUPPLY_PROP_CONSTANT_CHARGE_CURRENT_MAX:
		वापस axp20x_set_max_स्थिरant_अक्षरge_current(axp20x_batt,
							      val->पूर्णांकval);

	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल क्रमागत घातer_supply_property axp20x_battery_props[] = अणु
	POWER_SUPPLY_PROP_PRESENT,
	POWER_SUPPLY_PROP_ONLINE,
	POWER_SUPPLY_PROP_STATUS,
	POWER_SUPPLY_PROP_VOLTAGE_NOW,
	POWER_SUPPLY_PROP_CURRENT_NOW,
	POWER_SUPPLY_PROP_CONSTANT_CHARGE_CURRENT,
	POWER_SUPPLY_PROP_CONSTANT_CHARGE_CURRENT_MAX,
	POWER_SUPPLY_PROP_HEALTH,
	POWER_SUPPLY_PROP_VOLTAGE_MAX_DESIGN,
	POWER_SUPPLY_PROP_VOLTAGE_MIN_DESIGN,
	POWER_SUPPLY_PROP_CAPACITY,
पूर्ण;

अटल पूर्णांक axp20x_battery_prop_ग_लिखोable(काष्ठा घातer_supply *psy,
					 क्रमागत घातer_supply_property psp)
अणु
	वापस psp == POWER_SUPPLY_PROP_VOLTAGE_MIN_DESIGN ||
	       psp == POWER_SUPPLY_PROP_VOLTAGE_MAX_DESIGN ||
	       psp == POWER_SUPPLY_PROP_CONSTANT_CHARGE_CURRENT ||
	       psp == POWER_SUPPLY_PROP_CONSTANT_CHARGE_CURRENT_MAX;
पूर्ण

अटल स्थिर काष्ठा घातer_supply_desc axp20x_batt_ps_desc = अणु
	.name = "axp20x-battery",
	.type = POWER_SUPPLY_TYPE_BATTERY,
	.properties = axp20x_battery_props,
	.num_properties = ARRAY_SIZE(axp20x_battery_props),
	.property_is_ग_लिखोable = axp20x_battery_prop_ग_लिखोable,
	.get_property = axp20x_battery_get_prop,
	.set_property = axp20x_battery_set_prop,
पूर्ण;

अटल स्थिर काष्ठा axp_data axp209_data = अणु
	.ccc_scale = 100000,
	.ccc_offset = 300000,
	.get_max_voltage = axp20x_battery_get_max_voltage,
	.set_max_voltage = axp20x_battery_set_max_voltage,
पूर्ण;

अटल स्थिर काष्ठा axp_data axp221_data = अणु
	.ccc_scale = 150000,
	.ccc_offset = 300000,
	.has_fg_valid = true,
	.get_max_voltage = axp22x_battery_get_max_voltage,
	.set_max_voltage = axp22x_battery_set_max_voltage,
पूर्ण;

अटल स्थिर काष्ठा axp_data axp813_data = अणु
	.ccc_scale = 200000,
	.ccc_offset = 200000,
	.has_fg_valid = true,
	.get_max_voltage = axp813_battery_get_max_voltage,
	.set_max_voltage = axp20x_battery_set_max_voltage,
पूर्ण;

अटल स्थिर काष्ठा of_device_id axp20x_battery_ps_id[] = अणु
	अणु
		.compatible = "x-powers,axp209-battery-power-supply",
		.data = (व्योम *)&axp209_data,
	पूर्ण, अणु
		.compatible = "x-powers,axp221-battery-power-supply",
		.data = (व्योम *)&axp221_data,
	पूर्ण, अणु
		.compatible = "x-powers,axp813-battery-power-supply",
		.data = (व्योम *)&axp813_data,
	पूर्ण, अणु /* sentinel */ पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, axp20x_battery_ps_id);

अटल पूर्णांक axp20x_घातer_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा axp20x_batt_ps *axp20x_batt;
	काष्ठा घातer_supply_config psy_cfg = अणुपूर्ण;
	काष्ठा घातer_supply_battery_info info;
	काष्ठा device *dev = &pdev->dev;

	अगर (!of_device_is_available(pdev->dev.of_node))
		वापस -ENODEV;

	axp20x_batt = devm_kzalloc(&pdev->dev, माप(*axp20x_batt),
				   GFP_KERNEL);
	अगर (!axp20x_batt)
		वापस -ENOMEM;

	axp20x_batt->dev = &pdev->dev;

	axp20x_batt->batt_v = devm_iio_channel_get(&pdev->dev, "batt_v");
	अगर (IS_ERR(axp20x_batt->batt_v)) अणु
		अगर (PTR_ERR(axp20x_batt->batt_v) == -ENODEV)
			वापस -EPROBE_DEFER;
		वापस PTR_ERR(axp20x_batt->batt_v);
	पूर्ण

	axp20x_batt->batt_chrg_i = devm_iio_channel_get(&pdev->dev,
							"batt_chrg_i");
	अगर (IS_ERR(axp20x_batt->batt_chrg_i)) अणु
		अगर (PTR_ERR(axp20x_batt->batt_chrg_i) == -ENODEV)
			वापस -EPROBE_DEFER;
		वापस PTR_ERR(axp20x_batt->batt_chrg_i);
	पूर्ण

	axp20x_batt->batt_dischrg_i = devm_iio_channel_get(&pdev->dev,
							   "batt_dischrg_i");
	अगर (IS_ERR(axp20x_batt->batt_dischrg_i)) अणु
		अगर (PTR_ERR(axp20x_batt->batt_dischrg_i) == -ENODEV)
			वापस -EPROBE_DEFER;
		वापस PTR_ERR(axp20x_batt->batt_dischrg_i);
	पूर्ण

	axp20x_batt->regmap = dev_get_regmap(pdev->dev.parent, शून्य);
	platक्रमm_set_drvdata(pdev, axp20x_batt);

	psy_cfg.drv_data = axp20x_batt;
	psy_cfg.of_node = pdev->dev.of_node;

	axp20x_batt->data = (काष्ठा axp_data *)of_device_get_match_data(dev);

	axp20x_batt->batt = devm_घातer_supply_रेजिस्टर(&pdev->dev,
						       &axp20x_batt_ps_desc,
						       &psy_cfg);
	अगर (IS_ERR(axp20x_batt->batt)) अणु
		dev_err(&pdev->dev, "failed to register power supply: %ld\n",
			PTR_ERR(axp20x_batt->batt));
		वापस PTR_ERR(axp20x_batt->batt);
	पूर्ण

	अगर (!घातer_supply_get_battery_info(axp20x_batt->batt, &info)) अणु
		पूर्णांक vmin = info.voltage_min_design_uv;
		पूर्णांक ccc = info.स्थिरant_अक्षरge_current_max_ua;

		अगर (vmin > 0 && axp20x_set_voltage_min_design(axp20x_batt,
							      vmin))
			dev_err(&pdev->dev,
				"couldn't set voltage_min_design\n");

		/* Set max to unverअगरied value to be able to set CCC */
		axp20x_batt->max_ccc = ccc;

		अगर (ccc <= 0 || axp20x_set_स्थिरant_अक्षरge_current(axp20x_batt,
								   ccc)) अणु
			dev_err(&pdev->dev,
				"couldn't set constant charge current from DT: fallback to minimum value\n");
			ccc = 300000;
			axp20x_batt->max_ccc = ccc;
			axp20x_set_स्थिरant_अक्षरge_current(axp20x_batt, ccc);
		पूर्ण
	पूर्ण

	/*
	 * Update max CCC to a valid value अगर battery info is present or set it
	 * to current रेजिस्टर value by शेष.
	 */
	axp20x_get_स्थिरant_अक्षरge_current(axp20x_batt,
					   &axp20x_batt->max_ccc);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver axp20x_batt_driver = अणु
	.probe    = axp20x_घातer_probe,
	.driver   = अणु
		.name  = "axp20x-battery-power-supply",
		.of_match_table = axp20x_battery_ps_id,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(axp20x_batt_driver);

MODULE_DESCRIPTION("Battery power supply driver for AXP20X and AXP22X PMICs");
MODULE_AUTHOR("Quentin Schulz <quentin.schulz@free-electrons.com>");
MODULE_LICENSE("GPL");
