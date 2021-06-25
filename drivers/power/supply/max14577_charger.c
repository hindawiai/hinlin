<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
//
// max14577_अक्षरger.c - Battery अक्षरger driver क्रम the Maxim 14577/77836
//
// Copyright (C) 2013,2014 Samsung Electronics
// Krzysztof Kozlowski <krzk@kernel.org>

#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/घातer_supply.h>
#समावेश <linux/mfd/max14577-निजी.h>
#समावेश <linux/mfd/max14577.h>

काष्ठा max14577_अक्षरger अणु
	काष्ठा device		*dev;
	काष्ठा max14577		*max14577;
	काष्ठा घातer_supply	*अक्षरger;

	काष्ठा max14577_अक्षरger_platक्रमm_data	*pdata;
पूर्ण;

/*
 * Helper function क्रम mapping values of STATUS2/CHGTYP रेजिस्टर on max14577
 * and max77836 chipsets to क्रमागत maxim_muic_अक्षरger_type.
 */
अटल क्रमागत max14577_muic_अक्षरger_type maxim_get_अक्षरger_type(
		क्रमागत maxim_device_type dev_type, u8 val) अणु
	चयन (val) अणु
	हाल MAX14577_CHARGER_TYPE_NONE:
	हाल MAX14577_CHARGER_TYPE_USB:
	हाल MAX14577_CHARGER_TYPE_DOWNSTREAM_PORT:
	हाल MAX14577_CHARGER_TYPE_DEDICATED_CHG:
	हाल MAX14577_CHARGER_TYPE_SPECIAL_500MA:
	हाल MAX14577_CHARGER_TYPE_SPECIAL_1A:
		वापस val;
	हाल MAX14577_CHARGER_TYPE_DEAD_BATTERY:
	हाल MAX14577_CHARGER_TYPE_RESERVED:
		अगर (dev_type == MAXIM_DEVICE_TYPE_MAX77836)
			val |= 0x8;
		वापस val;
	शेष:
		WARN_ONCE(1, "max14577: Unsupported chgtyp register value 0x%02x", val);
		वापस val;
	पूर्ण
पूर्ण

अटल पूर्णांक max14577_get_अक्षरger_state(काष्ठा max14577_अक्षरger *chg, पूर्णांक *val)
अणु
	काष्ठा regmap *rmap = chg->max14577->regmap;
	पूर्णांक ret;
	u8 reg_data;

	/*
	 * Charging occurs only अगर:
	 *  - CHGCTRL2/MBCHOSTEN == 1
	 *  - STATUS2/CGMBC == 1
	 *
	 * TODO:
	 *  - handle FULL after Top-off समयr (EOC रेजिस्टर may be off
	 *    and the अक्षरger won't be अक्षरging although MBCHOSTEN is on)
	 *  - handle properly dead-battery अक्षरging (respect समयr)
	 *  - handle समयrs (fast-अक्षरge and prequal) /MBCCHGERR/
	 */
	ret = max14577_पढ़ो_reg(rmap, MAX14577_CHG_REG_CHG_CTRL2, &reg_data);
	अगर (ret < 0)
		जाओ out;

	अगर ((reg_data & CHGCTRL2_MBCHOSTEN_MASK) == 0) अणु
		*val = POWER_SUPPLY_STATUS_DISCHARGING;
		जाओ out;
	पूर्ण

	ret = max14577_पढ़ो_reg(rmap, MAX14577_CHG_REG_STATUS3, &reg_data);
	अगर (ret < 0)
		जाओ out;

	अगर (reg_data & STATUS3_CGMBC_MASK) अणु
		/* Charger or USB-cable is connected */
		अगर (reg_data & STATUS3_EOC_MASK)
			*val = POWER_SUPPLY_STATUS_FULL;
		अन्यथा
			*val = POWER_SUPPLY_STATUS_CHARGING;
		जाओ out;
	पूर्ण

	*val = POWER_SUPPLY_STATUS_DISCHARGING;

out:
	वापस ret;
पूर्ण

/*
 * Supported अक्षरge types:
 *  - POWER_SUPPLY_CHARGE_TYPE_NONE
 *  - POWER_SUPPLY_CHARGE_TYPE_FAST
 */
अटल पूर्णांक max14577_get_अक्षरge_type(काष्ठा max14577_अक्षरger *chg, पूर्णांक *val)
अणु
	पूर्णांक ret, अक्षरging;

	/*
	 * TODO: CHARGE_TYPE_TRICKLE (VCHGR_RC or EOC)?
	 * As spec says:
	 * [after reaching EOC पूर्णांकerrupt]
	 * "When the battery is fully अक्षरged, the 30-minute (typ)
	 *  top-off समयr starts. The device जारीs to trickle
	 *  अक्षरge the battery until the top-off समयr runs out."
	 */
	ret = max14577_get_अक्षरger_state(chg, &अक्षरging);
	अगर (ret < 0)
		वापस ret;

	अगर (अक्षरging == POWER_SUPPLY_STATUS_CHARGING)
		*val = POWER_SUPPLY_CHARGE_TYPE_FAST;
	अन्यथा
		*val = POWER_SUPPLY_CHARGE_TYPE_NONE;

	वापस 0;
पूर्ण

अटल पूर्णांक max14577_get_online(काष्ठा max14577_अक्षरger *chg, पूर्णांक *val)
अणु
	काष्ठा regmap *rmap = chg->max14577->regmap;
	u8 reg_data;
	पूर्णांक ret;
	क्रमागत max14577_muic_अक्षरger_type chg_type;

	ret = max14577_पढ़ो_reg(rmap, MAX14577_MUIC_REG_STATUS2, &reg_data);
	अगर (ret < 0)
		वापस ret;

	reg_data = ((reg_data & STATUS2_CHGTYP_MASK) >> STATUS2_CHGTYP_SHIFT);
	chg_type = maxim_get_अक्षरger_type(chg->max14577->dev_type, reg_data);
	चयन (chg_type) अणु
	हाल MAX14577_CHARGER_TYPE_USB:
	हाल MAX14577_CHARGER_TYPE_DEDICATED_CHG:
	हाल MAX14577_CHARGER_TYPE_SPECIAL_500MA:
	हाल MAX14577_CHARGER_TYPE_SPECIAL_1A:
	हाल MAX14577_CHARGER_TYPE_DEAD_BATTERY:
	हाल MAX77836_CHARGER_TYPE_SPECIAL_BIAS:
		*val = 1;
		अवरोध;
	हाल MAX14577_CHARGER_TYPE_NONE:
	हाल MAX14577_CHARGER_TYPE_DOWNSTREAM_PORT:
	हाल MAX14577_CHARGER_TYPE_RESERVED:
	हाल MAX77836_CHARGER_TYPE_RESERVED:
	शेष:
		*val = 0;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Supported health statuses:
 *  - POWER_SUPPLY_HEALTH_DEAD
 *  - POWER_SUPPLY_HEALTH_OVERVOLTAGE
 *  - POWER_SUPPLY_HEALTH_GOOD
 */
अटल पूर्णांक max14577_get_battery_health(काष्ठा max14577_अक्षरger *chg, पूर्णांक *val)
अणु
	काष्ठा regmap *rmap = chg->max14577->regmap;
	पूर्णांक ret;
	u8 reg_data;
	क्रमागत max14577_muic_अक्षरger_type chg_type;

	ret = max14577_पढ़ो_reg(rmap, MAX14577_MUIC_REG_STATUS2, &reg_data);
	अगर (ret < 0)
		जाओ out;

	reg_data = ((reg_data & STATUS2_CHGTYP_MASK) >> STATUS2_CHGTYP_SHIFT);
	chg_type = maxim_get_अक्षरger_type(chg->max14577->dev_type, reg_data);
	अगर (chg_type == MAX14577_CHARGER_TYPE_DEAD_BATTERY) अणु
		*val = POWER_SUPPLY_HEALTH_DEAD;
		जाओ out;
	पूर्ण

	ret = max14577_पढ़ो_reg(rmap, MAX14577_CHG_REG_STATUS3, &reg_data);
	अगर (ret < 0)
		जाओ out;

	अगर (reg_data & STATUS3_OVP_MASK) अणु
		*val = POWER_SUPPLY_HEALTH_OVERVOLTAGE;
		जाओ out;
	पूर्ण

	/* Not dead, not overvoltage */
	*val = POWER_SUPPLY_HEALTH_GOOD;

out:
	वापस ret;
पूर्ण

/*
 * Always वापसs 1.
 * The max14577 chip करोesn't report any status of battery presence.
 * Lets assume that it will always be used with some battery.
 */
अटल पूर्णांक max14577_get_present(काष्ठा max14577_अक्षरger *chg, पूर्णांक *val)
अणु
	*val = 1;

	वापस 0;
पूर्ण

अटल पूर्णांक max14577_set_fast_अक्षरge_समयr(काष्ठा max14577_अक्षरger *chg,
		अचिन्हित दीर्घ hours)
अणु
	u8 reg_data;

	चयन (hours) अणु
	हाल 5 ... 7:
		reg_data = hours - 3;
		अवरोध;
	हाल 0:
		/* Disable */
		reg_data = 0x7;
		अवरोध;
	शेष:
		dev_err(chg->dev, "Wrong value for Fast-Charge Timer: %lu\n",
				hours);
		वापस -EINVAL;
	पूर्ण
	reg_data <<= CHGCTRL1_TCHW_SHIFT;

	वापस max14577_update_reg(chg->max14577->regmap,
			MAX14577_REG_CHGCTRL1, CHGCTRL1_TCHW_MASK, reg_data);
पूर्ण

अटल पूर्णांक max14577_init_स्थिरant_voltage(काष्ठा max14577_अक्षरger *chg,
		अचिन्हित पूर्णांक uvolt)
अणु
	u8 reg_data;

	अगर (uvolt < MAXIM_CHARGER_CONSTANT_VOLTAGE_MIN ||
			uvolt > MAXIM_CHARGER_CONSTANT_VOLTAGE_MAX)
		वापस -EINVAL;

	अगर (uvolt == 4200000)
		reg_data = 0x0;
	अन्यथा अगर (uvolt == MAXIM_CHARGER_CONSTANT_VOLTAGE_MAX)
		reg_data = 0x1f;
	अन्यथा अगर (uvolt <= 4280000) अणु
		अचिन्हित पूर्णांक val = uvolt;

		val -= MAXIM_CHARGER_CONSTANT_VOLTAGE_MIN;
		val /= MAXIM_CHARGER_CONSTANT_VOLTAGE_STEP;
		अगर (uvolt <= 4180000)
			reg_data = 0x1 + val;
		अन्यथा
			reg_data = val; /* Fix क्रम gap between 4.18V and 4.22V */
	पूर्ण अन्यथा
		वापस -EINVAL;

	reg_data <<= CHGCTRL3_MBCCVWRC_SHIFT;

	वापस max14577_ग_लिखो_reg(chg->max14577->regmap,
			MAX14577_CHG_REG_CHG_CTRL3, reg_data);
पूर्ण

अटल पूर्णांक max14577_init_eoc(काष्ठा max14577_अक्षरger *chg,
		अचिन्हित पूर्णांक uamp)
अणु
	अचिन्हित पूर्णांक current_bits;
	u8 reg_data;

	चयन (chg->max14577->dev_type) अणु
	हाल MAXIM_DEVICE_TYPE_MAX77836:
		अगर (uamp < 5000)
			वापस -EINVAL; /* Requested current is too low */

		अगर (uamp >= 7500 && uamp < 10000)
			current_bits = 0x0;
		अन्यथा अगर (uamp <= 50000) अणु
			/* <5000, 7499> and <10000, 50000> */
			current_bits = uamp / 5000;
		पूर्ण अन्यथा अणु
			uamp = min(uamp, 100000U) - 50000U;
			current_bits = 0xa + uamp / 10000;
		पूर्ण
		अवरोध;

	हाल MAXIM_DEVICE_TYPE_MAX14577:
	शेष:
		अगर (uamp < MAX14577_CHARGER_EOC_CURRENT_LIMIT_MIN)
			वापस -EINVAL; /* Requested current is too low */

		uamp = min(uamp, MAX14577_CHARGER_EOC_CURRENT_LIMIT_MAX);
		uamp -= MAX14577_CHARGER_EOC_CURRENT_LIMIT_MIN;
		current_bits = uamp / MAX14577_CHARGER_EOC_CURRENT_LIMIT_STEP;
		अवरोध;
	पूर्ण

	reg_data = current_bits << CHGCTRL5_EOCS_SHIFT;

	वापस max14577_update_reg(chg->max14577->regmap,
			MAX14577_CHG_REG_CHG_CTRL5, CHGCTRL5_EOCS_MASK,
			reg_data);
पूर्ण

अटल पूर्णांक max14577_init_fast_अक्षरge(काष्ठा max14577_अक्षरger *chg,
		अचिन्हित पूर्णांक uamp)
अणु
	u8 reg_data;
	पूर्णांक ret;
	स्थिर काष्ठा maxim_अक्षरger_current *limits =
		&maxim_अक्षरger_currents[chg->max14577->dev_type];

	ret = maxim_अक्षरger_calc_reg_current(limits, uamp, uamp, &reg_data);
	अगर (ret) अणु
		dev_err(chg->dev, "Wrong value for fast charge: %u\n", uamp);
		वापस ret;
	पूर्ण

	वापस max14577_update_reg(chg->max14577->regmap,
			MAX14577_CHG_REG_CHG_CTRL4,
			CHGCTRL4_MBCICHWRCL_MASK | CHGCTRL4_MBCICHWRCH_MASK,
			reg_data);
पूर्ण

/*
 * Sets अक्षरger रेजिस्टरs to proper and safe शेष values.
 * Some of these values are equal to शेषs in MAX14577E
 * data sheet but there are minor dअगरferences.
 */
अटल पूर्णांक max14577_अक्षरger_reg_init(काष्ठा max14577_अक्षरger *chg)
अणु
	काष्ठा regmap *rmap = chg->max14577->regmap;
	u8 reg_data;
	पूर्णांक ret;

	/*
	 * Charger-Type Manual Detection, शेष off (set CHGTYPMAN to 0)
	 * Charger-Detection Enable, शेष on (set CHGDETEN to 1)
	 * Combined mask of CHGDETEN and CHGTYPMAN will zero the CHGTYPMAN bit
	 */
	reg_data = 0x1 << CDETCTRL1_CHGDETEN_SHIFT;
	max14577_update_reg(rmap, MAX14577_REG_CDETCTRL1,
			CDETCTRL1_CHGDETEN_MASK | CDETCTRL1_CHGTYPMAN_MASK,
			reg_data);

	/*
	 * Wall-Adapter Rapid Charge, शेष on
	 * Battery-Charger, शेष on
	 */
	reg_data = 0x1 << CHGCTRL2_VCHGR_RC_SHIFT;
	reg_data |= 0x1 << CHGCTRL2_MBCHOSTEN_SHIFT;
	max14577_ग_लिखो_reg(rmap, MAX14577_REG_CHGCTRL2, reg_data);

	/* Auto Charging Stop, शेष off */
	reg_data = 0x0 << CHGCTRL6_AUTOSTOP_SHIFT;
	max14577_ग_लिखो_reg(rmap, MAX14577_REG_CHGCTRL6, reg_data);

	ret = max14577_init_स्थिरant_voltage(chg, chg->pdata->स्थिरant_uvolt);
	अगर (ret)
		वापस ret;

	ret = max14577_init_eoc(chg, chg->pdata->eoc_uamp);
	अगर (ret)
		वापस ret;

	ret = max14577_init_fast_अक्षरge(chg, chg->pdata->fast_अक्षरge_uamp);
	अगर (ret)
		वापस ret;

	ret = max14577_set_fast_अक्षरge_समयr(chg,
			MAXIM_CHARGER_FAST_CHARGE_TIMER_DEFAULT);
	अगर (ret)
		वापस ret;

	/* Initialize Overvoltage-Protection Threshold */
	चयन (chg->pdata->ovp_uvolt) अणु
	हाल 7500000:
		reg_data = 0x0;
		अवरोध;
	हाल 6000000:
	हाल 6500000:
	हाल 7000000:
		reg_data = 0x1 + (chg->pdata->ovp_uvolt - 6000000) / 500000;
		अवरोध;
	शेष:
		dev_err(chg->dev, "Wrong value for OVP: %u\n",
				chg->pdata->ovp_uvolt);
		वापस -EINVAL;
	पूर्ण
	reg_data <<= CHGCTRL7_OTPCGHCVS_SHIFT;
	max14577_ग_लिखो_reg(rmap, MAX14577_REG_CHGCTRL7, reg_data);

	वापस 0;
पूर्ण

/* Support property from अक्षरger */
अटल क्रमागत घातer_supply_property max14577_अक्षरger_props[] = अणु
	POWER_SUPPLY_PROP_STATUS,
	POWER_SUPPLY_PROP_CHARGE_TYPE,
	POWER_SUPPLY_PROP_HEALTH,
	POWER_SUPPLY_PROP_PRESENT,
	POWER_SUPPLY_PROP_ONLINE,
	POWER_SUPPLY_PROP_MODEL_NAME,
	POWER_SUPPLY_PROP_MANUFACTURER,
पूर्ण;

अटल स्थिर अक्षर * स्थिर model_names[] = अणु
	[MAXIM_DEVICE_TYPE_UNKNOWN]	= "MAX14577-like",
	[MAXIM_DEVICE_TYPE_MAX14577]	= "MAX14577",
	[MAXIM_DEVICE_TYPE_MAX77836]	= "MAX77836",
पूर्ण;
अटल स्थिर अक्षर *manufacturer = "Maxim Integrated";

अटल पूर्णांक max14577_अक्षरger_get_property(काष्ठा घातer_supply *psy,
			    क्रमागत घातer_supply_property psp,
			    जोड़ घातer_supply_propval *val)
अणु
	काष्ठा max14577_अक्षरger *chg = घातer_supply_get_drvdata(psy);
	पूर्णांक ret = 0;

	चयन (psp) अणु
	हाल POWER_SUPPLY_PROP_STATUS:
		ret = max14577_get_अक्षरger_state(chg, &val->पूर्णांकval);
		अवरोध;
	हाल POWER_SUPPLY_PROP_CHARGE_TYPE:
		ret = max14577_get_अक्षरge_type(chg, &val->पूर्णांकval);
		अवरोध;
	हाल POWER_SUPPLY_PROP_HEALTH:
		ret = max14577_get_battery_health(chg, &val->पूर्णांकval);
		अवरोध;
	हाल POWER_SUPPLY_PROP_PRESENT:
		ret = max14577_get_present(chg, &val->पूर्णांकval);
		अवरोध;
	हाल POWER_SUPPLY_PROP_ONLINE:
		ret = max14577_get_online(chg, &val->पूर्णांकval);
		अवरोध;
	हाल POWER_SUPPLY_PROP_MODEL_NAME:
		BUILD_BUG_ON(ARRAY_SIZE(model_names) != MAXIM_DEVICE_TYPE_NUM);
		val->strval = model_names[chg->max14577->dev_type];
		अवरोध;
	हाल POWER_SUPPLY_PROP_MANUFACTURER:
		val->strval = manufacturer;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा घातer_supply_desc max14577_अक्षरger_desc = अणु
	.name = "max14577-charger",
	.type = POWER_SUPPLY_TYPE_BATTERY,
	.properties = max14577_अक्षरger_props,
	.num_properties = ARRAY_SIZE(max14577_अक्षरger_props),
	.get_property = max14577_अक्षरger_get_property,
पूर्ण;

#अगर_घोषित CONFIG_OF
अटल काष्ठा max14577_अक्षरger_platक्रमm_data *max14577_अक्षरger_dt_init(
		काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा max14577_अक्षरger_platक्रमm_data *pdata;
	काष्ठा device_node *np = pdev->dev.of_node;
	पूर्णांक ret;

	अगर (!np) अणु
		dev_err(&pdev->dev, "No charger OF node\n");
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	pdata = devm_kzalloc(&pdev->dev, माप(*pdata), GFP_KERNEL);
	अगर (!pdata)
		वापस ERR_PTR(-ENOMEM);

	ret = of_property_पढ़ो_u32(np, "maxim,constant-uvolt",
			&pdata->स्थिरant_uvolt);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Cannot parse maxim,constant-uvolt field from DT\n");
		वापस ERR_PTR(ret);
	पूर्ण

	ret = of_property_पढ़ो_u32(np, "maxim,fast-charge-uamp",
			&pdata->fast_अक्षरge_uamp);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Cannot parse maxim,fast-charge-uamp field from DT\n");
		वापस ERR_PTR(ret);
	पूर्ण

	ret = of_property_पढ़ो_u32(np, "maxim,eoc-uamp", &pdata->eoc_uamp);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Cannot parse maxim,eoc-uamp field from DT\n");
		वापस ERR_PTR(ret);
	पूर्ण

	ret = of_property_पढ़ो_u32(np, "maxim,ovp-uvolt", &pdata->ovp_uvolt);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Cannot parse maxim,ovp-uvolt field from DT\n");
		वापस ERR_PTR(ret);
	पूर्ण

	वापस pdata;
पूर्ण
#अन्यथा /* CONFIG_OF */
अटल काष्ठा max14577_अक्षरger_platक्रमm_data *max14577_अक्षरger_dt_init(
		काष्ठा platक्रमm_device *pdev)
अणु
	वापस शून्य;
पूर्ण
#पूर्ण_अगर /* CONFIG_OF */

अटल sमाप_प्रकार show_fast_अक्षरge_समयr(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा max14577_अक्षरger *chg = dev_get_drvdata(dev);
	u8 reg_data;
	पूर्णांक ret;
	अचिन्हित पूर्णांक val;

	ret = max14577_पढ़ो_reg(chg->max14577->regmap, MAX14577_REG_CHGCTRL1,
			&reg_data);
	अगर (ret)
		वापस ret;

	reg_data &= CHGCTRL1_TCHW_MASK;
	reg_data >>= CHGCTRL1_TCHW_SHIFT;
	चयन (reg_data) अणु
	हाल 0x2 ... 0x4:
		val = reg_data + 3;
		अवरोध;
	हाल 0x7:
		val = 0;
		अवरोध;
	शेष:
		val = 5;
		अवरोध;
	पूर्ण

	वापस scnम_लिखो(buf, PAGE_SIZE, "%u\n", val);
पूर्ण

अटल sमाप_प्रकार store_fast_अक्षरge_समयr(काष्ठा device *dev,
		काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा max14577_अक्षरger *chg = dev_get_drvdata(dev);
	अचिन्हित दीर्घ val;
	पूर्णांक ret;

	ret = kम_से_अदीर्घ(buf, 10, &val);
	अगर (ret)
		वापस ret;

	ret = max14577_set_fast_अक्षरge_समयr(chg, val);
	अगर (ret)
		वापस ret;

	वापस count;
पूर्ण

अटल DEVICE_ATTR(fast_अक्षरge_समयr, S_IRUGO | S_IWUSR,
		show_fast_अक्षरge_समयr, store_fast_अक्षरge_समयr);

अटल पूर्णांक max14577_अक्षरger_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा max14577_अक्षरger *chg;
	काष्ठा घातer_supply_config psy_cfg = अणुपूर्ण;
	काष्ठा max14577 *max14577 = dev_get_drvdata(pdev->dev.parent);
	पूर्णांक ret;

	chg = devm_kzalloc(&pdev->dev, माप(*chg), GFP_KERNEL);
	अगर (!chg)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, chg);
	chg->dev = &pdev->dev;
	chg->max14577 = max14577;

	chg->pdata = max14577_अक्षरger_dt_init(pdev);
	अगर (IS_ERR_OR_शून्य(chg->pdata))
		वापस PTR_ERR(chg->pdata);

	ret = max14577_अक्षरger_reg_init(chg);
	अगर (ret)
		वापस ret;

	ret = device_create_file(&pdev->dev, &dev_attr_fast_अक्षरge_समयr);
	अगर (ret) अणु
		dev_err(&pdev->dev, "failed: create sysfs entry\n");
		वापस ret;
	पूर्ण

	psy_cfg.drv_data = chg;
	chg->अक्षरger = घातer_supply_रेजिस्टर(&pdev->dev, &max14577_अक्षरger_desc,
						&psy_cfg);
	अगर (IS_ERR(chg->अक्षरger)) अणु
		dev_err(&pdev->dev, "failed: power supply register\n");
		ret = PTR_ERR(chg->अक्षरger);
		जाओ err;
	पूर्ण

	/* Check क्रम valid values क्रम अक्षरger */
	BUILD_BUG_ON(MAX14577_CHARGER_EOC_CURRENT_LIMIT_MIN +
			MAX14577_CHARGER_EOC_CURRENT_LIMIT_STEP * 0xf !=
			MAX14577_CHARGER_EOC_CURRENT_LIMIT_MAX);
	वापस 0;

err:
	device_हटाओ_file(&pdev->dev, &dev_attr_fast_अक्षरge_समयr);

	वापस ret;
पूर्ण

अटल पूर्णांक max14577_अक्षरger_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा max14577_अक्षरger *chg = platक्रमm_get_drvdata(pdev);

	device_हटाओ_file(&pdev->dev, &dev_attr_fast_अक्षरge_समयr);
	घातer_supply_unरेजिस्टर(chg->अक्षरger);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा platक्रमm_device_id max14577_अक्षरger_id[] = अणु
	अणु "max14577-charger", MAXIM_DEVICE_TYPE_MAX14577, पूर्ण,
	अणु "max77836-charger", MAXIM_DEVICE_TYPE_MAX77836, पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(platक्रमm, max14577_अक्षरger_id);

अटल स्थिर काष्ठा of_device_id of_max14577_अक्षरger_dt_match[] = अणु
	अणु .compatible = "maxim,max14577-charger",
	  .data = (व्योम *)MAXIM_DEVICE_TYPE_MAX14577, पूर्ण,
	अणु .compatible = "maxim,max77836-charger",
	  .data = (व्योम *)MAXIM_DEVICE_TYPE_MAX77836, पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, of_max14577_अक्षरger_dt_match);

अटल काष्ठा platक्रमm_driver max14577_अक्षरger_driver = अणु
	.driver = अणु
		.name	= "max14577-charger",
		.of_match_table = of_max14577_अक्षरger_dt_match,
	पूर्ण,
	.probe		= max14577_अक्षरger_probe,
	.हटाओ		= max14577_अक्षरger_हटाओ,
	.id_table	= max14577_अक्षरger_id,
पूर्ण;
module_platक्रमm_driver(max14577_अक्षरger_driver);

MODULE_AUTHOR("Krzysztof Kozlowski <krzk@kernel.org>");
MODULE_DESCRIPTION("Maxim 14577/77836 charger driver");
MODULE_LICENSE("GPL");
