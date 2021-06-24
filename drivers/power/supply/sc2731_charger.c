<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (C) 2018 Spपढ़ोtrum Communications Inc.

#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/घातer_supply.h>
#समावेश <linux/usb/phy.h>
#समावेश <linux/regmap.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/of.h>

/* PMIC global रेजिस्टरs definition */
#घोषणा SC2731_CHARGE_STATUS		0xedc
#घोषणा SC2731_CHARGE_FULL		BIT(4)
#घोषणा SC2731_MODULE_EN1		0xc0c
#घोषणा SC2731_CHARGE_EN		BIT(5)

/* SC2731 चयन अक्षरger रेजिस्टरs definition */
#घोषणा SC2731_CHG_CFG0			0x0
#घोषणा SC2731_CHG_CFG1			0x4
#घोषणा SC2731_CHG_CFG2			0x8
#घोषणा SC2731_CHG_CFG3			0xc
#घोषणा SC2731_CHG_CFG4			0x10
#घोषणा SC2731_CHG_CFG5			0x28

/* SC2731_CHG_CFG0 रेजिस्टर definition */
#घोषणा SC2731_PRECHG_RNG_SHIFT		11
#घोषणा SC2731_PRECHG_RNG_MASK		GENMASK(12, 11)

#घोषणा SC2731_TERMINATION_VOL_MASK	GENMASK(2, 1)
#घोषणा SC2731_TERMINATION_VOL_SHIFT	1
#घोषणा SC2731_TERMINATION_VOL_CAL_MASK	GENMASK(8, 3)
#घोषणा SC2731_TERMINATION_VOL_CAL_SHIFT	3
#घोषणा SC2731_TERMINATION_CUR_MASK	GENMASK(2, 0)

#घोषणा SC2731_CC_EN			BIT(13)
#घोषणा SC2731_CHARGER_PD		BIT(0)

/* SC2731_CHG_CFG1 रेजिस्टर definition */
#घोषणा SC2731_CUR_MASK			GENMASK(5, 0)

/* SC2731_CHG_CFG5 रेजिस्टर definition */
#घोषणा SC2731_CUR_LIMIT_SHIFT		8
#घोषणा SC2731_CUR_LIMIT_MASK		GENMASK(9, 8)

/* Default current definition (unit is mA) */
#घोषणा SC2731_CURRENT_LIMIT_100	100
#घोषणा SC2731_CURRENT_LIMIT_500	500
#घोषणा SC2731_CURRENT_LIMIT_900	900
#घोषणा SC2731_CURRENT_LIMIT_2000	2000
#घोषणा SC2731_CURRENT_PRECHG		450
#घोषणा SC2731_CURRENT_STEP		50

काष्ठा sc2731_अक्षरger_info अणु
	काष्ठा device *dev;
	काष्ठा regmap *regmap;
	काष्ठा usb_phy *usb_phy;
	काष्ठा notअगरier_block usb_notअगरy;
	काष्ठा घातer_supply *psy_usb;
	काष्ठा work_काष्ठा work;
	काष्ठा mutex lock;
	bool अक्षरging;
	u32 base;
	u32 limit;
पूर्ण;

अटल व्योम sc2731_अक्षरger_stop_अक्षरge(काष्ठा sc2731_अक्षरger_info *info)
अणु
	regmap_update_bits(info->regmap, info->base + SC2731_CHG_CFG0,
			   SC2731_CC_EN, 0);

	regmap_update_bits(info->regmap, info->base + SC2731_CHG_CFG0,
			   SC2731_CHARGER_PD, SC2731_CHARGER_PD);
पूर्ण

अटल पूर्णांक sc2731_अक्षरger_start_अक्षरge(काष्ठा sc2731_अक्षरger_info *info)
अणु
	पूर्णांक ret;

	/* Enable अक्षरger स्थिरant current mode */
	ret = regmap_update_bits(info->regmap, info->base + SC2731_CHG_CFG0,
				 SC2731_CC_EN, SC2731_CC_EN);
	अगर (ret)
		वापस ret;

	/* Start अक्षरging */
	वापस regmap_update_bits(info->regmap, info->base + SC2731_CHG_CFG0,
				  SC2731_CHARGER_PD, 0);
पूर्ण

अटल पूर्णांक sc2731_अक्षरger_set_current_limit(काष्ठा sc2731_अक्षरger_info *info,
					    u32 limit)
अणु
	u32 val;

	अगर (limit <= SC2731_CURRENT_LIMIT_100)
		val = 0;
	अन्यथा अगर (limit <= SC2731_CURRENT_LIMIT_500)
		val = 3;
	अन्यथा अगर (limit <= SC2731_CURRENT_LIMIT_900)
		val = 2;
	अन्यथा
		val = 1;

	वापस regmap_update_bits(info->regmap, info->base + SC2731_CHG_CFG5,
				  SC2731_CUR_LIMIT_MASK,
				  val << SC2731_CUR_LIMIT_SHIFT);
पूर्ण

अटल पूर्णांक sc2731_अक्षरger_set_current(काष्ठा sc2731_अक्षरger_info *info, u32 cur)
अणु
	u32 val;
	पूर्णांक ret;

	अगर (cur > SC2731_CURRENT_LIMIT_2000)
		cur = SC2731_CURRENT_LIMIT_2000;
	अन्यथा अगर (cur < SC2731_CURRENT_PRECHG)
		cur = SC2731_CURRENT_PRECHG;

	/* Calculate the step value, each step is 50 mA */
	val = (cur - SC2731_CURRENT_PRECHG) / SC2731_CURRENT_STEP;

	/* Set pre-अक्षरge current as 450 mA */
	ret = regmap_update_bits(info->regmap, info->base + SC2731_CHG_CFG0,
				 SC2731_PRECHG_RNG_MASK,
				 0x3 << SC2731_PRECHG_RNG_SHIFT);
	अगर (ret)
		वापस ret;

	वापस regmap_update_bits(info->regmap, info->base + SC2731_CHG_CFG1,
				  SC2731_CUR_MASK, val);
पूर्ण

अटल पूर्णांक sc2731_अक्षरger_get_status(काष्ठा sc2731_अक्षरger_info *info)
अणु
	u32 val;
	पूर्णांक ret;

	ret = regmap_पढ़ो(info->regmap, SC2731_CHARGE_STATUS, &val);
	अगर (ret)
		वापस ret;

	अगर (val & SC2731_CHARGE_FULL)
		वापस POWER_SUPPLY_STATUS_FULL;

	वापस POWER_SUPPLY_STATUS_CHARGING;
पूर्ण

अटल पूर्णांक sc2731_अक्षरger_get_current(काष्ठा sc2731_अक्षरger_info *info,
				      u32 *cur)
अणु
	पूर्णांक ret;
	u32 val;

	ret = regmap_पढ़ो(info->regmap, info->base + SC2731_CHG_CFG1, &val);
	अगर (ret)
		वापस ret;

	val &= SC2731_CUR_MASK;
	*cur = val * SC2731_CURRENT_STEP + SC2731_CURRENT_PRECHG;

	वापस 0;
पूर्ण

अटल पूर्णांक sc2731_अक्षरger_get_current_limit(काष्ठा sc2731_अक्षरger_info *info,
					    u32 *cur)
अणु
	पूर्णांक ret;
	u32 val;

	ret = regmap_पढ़ो(info->regmap, info->base + SC2731_CHG_CFG5, &val);
	अगर (ret)
		वापस ret;

	val = (val & SC2731_CUR_LIMIT_MASK) >> SC2731_CUR_LIMIT_SHIFT;

	चयन (val) अणु
	हाल 0:
		*cur = SC2731_CURRENT_LIMIT_100;
		अवरोध;

	हाल 1:
		*cur = SC2731_CURRENT_LIMIT_2000;
		अवरोध;

	हाल 2:
		*cur = SC2731_CURRENT_LIMIT_900;
		अवरोध;

	हाल 3:
		*cur = SC2731_CURRENT_LIMIT_500;
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
sc2731_अक्षरger_usb_set_property(काष्ठा घातer_supply *psy,
				क्रमागत घातer_supply_property psp,
				स्थिर जोड़ घातer_supply_propval *val)
अणु
	काष्ठा sc2731_अक्षरger_info *info = घातer_supply_get_drvdata(psy);
	पूर्णांक ret;

	mutex_lock(&info->lock);

	अगर (!info->अक्षरging) अणु
		mutex_unlock(&info->lock);
		वापस -ENODEV;
	पूर्ण

	चयन (psp) अणु
	हाल POWER_SUPPLY_PROP_CONSTANT_CHARGE_CURRENT:
		ret = sc2731_अक्षरger_set_current(info, val->पूर्णांकval / 1000);
		अगर (ret < 0)
			dev_err(info->dev, "set charge current failed\n");
		अवरोध;

	हाल POWER_SUPPLY_PROP_INPUT_CURRENT_LIMIT:
		ret = sc2731_अक्षरger_set_current_limit(info,
						       val->पूर्णांकval / 1000);
		अगर (ret < 0)
			dev_err(info->dev, "set input current limit failed\n");
		अवरोध;

	शेष:
		ret = -EINVAL;
	पूर्ण

	mutex_unlock(&info->lock);
	वापस ret;
पूर्ण

अटल पूर्णांक sc2731_अक्षरger_usb_get_property(काष्ठा घातer_supply *psy,
					   क्रमागत घातer_supply_property psp,
					   जोड़ घातer_supply_propval *val)
अणु
	काष्ठा sc2731_अक्षरger_info *info = घातer_supply_get_drvdata(psy);
	पूर्णांक ret = 0;
	u32 cur;

	mutex_lock(&info->lock);

	चयन (psp) अणु
	हाल POWER_SUPPLY_PROP_STATUS:
		अगर (info->अक्षरging)
			val->पूर्णांकval = sc2731_अक्षरger_get_status(info);
		अन्यथा
			val->पूर्णांकval = POWER_SUPPLY_STATUS_NOT_CHARGING;
		अवरोध;

	हाल POWER_SUPPLY_PROP_CONSTANT_CHARGE_CURRENT:
		अगर (!info->अक्षरging) अणु
			val->पूर्णांकval = 0;
		पूर्ण अन्यथा अणु
			ret = sc2731_अक्षरger_get_current(info, &cur);
			अगर (ret)
				जाओ out;

			val->पूर्णांकval = cur * 1000;
		पूर्ण
		अवरोध;

	हाल POWER_SUPPLY_PROP_INPUT_CURRENT_LIMIT:
		अगर (!info->अक्षरging) अणु
			val->पूर्णांकval = 0;
		पूर्ण अन्यथा अणु
			ret = sc2731_अक्षरger_get_current_limit(info, &cur);
			अगर (ret)
				जाओ out;

			val->पूर्णांकval = cur * 1000;
		पूर्ण
		अवरोध;

	शेष:
		ret = -EINVAL;
	पूर्ण

out:
	mutex_unlock(&info->lock);
	वापस ret;
पूर्ण

अटल पूर्णांक sc2731_अक्षरger_property_is_ग_लिखोable(काष्ठा घातer_supply *psy,
						क्रमागत घातer_supply_property psp)
अणु
	पूर्णांक ret;

	चयन (psp) अणु
	हाल POWER_SUPPLY_PROP_CONSTANT_CHARGE_CURRENT:
	हाल POWER_SUPPLY_PROP_INPUT_CURRENT_LIMIT:
		ret = 1;
		अवरोध;

	शेष:
		ret = 0;
	पूर्ण

	वापस ret;
पूर्ण

अटल क्रमागत घातer_supply_property sc2731_usb_props[] = अणु
	POWER_SUPPLY_PROP_STATUS,
	POWER_SUPPLY_PROP_CONSTANT_CHARGE_CURRENT,
	POWER_SUPPLY_PROP_INPUT_CURRENT_LIMIT,
पूर्ण;

अटल स्थिर काष्ठा घातer_supply_desc sc2731_अक्षरger_desc = अणु
	.name			= "sc2731_charger",
	.type			= POWER_SUPPLY_TYPE_USB,
	.properties		= sc2731_usb_props,
	.num_properties		= ARRAY_SIZE(sc2731_usb_props),
	.get_property		= sc2731_अक्षरger_usb_get_property,
	.set_property		= sc2731_अक्षरger_usb_set_property,
	.property_is_ग_लिखोable	= sc2731_अक्षरger_property_is_ग_लिखोable,
पूर्ण;

अटल व्योम sc2731_अक्षरger_work(काष्ठा work_काष्ठा *data)
अणु
	काष्ठा sc2731_अक्षरger_info *info =
		container_of(data, काष्ठा sc2731_अक्षरger_info, work);
	पूर्णांक ret;

	mutex_lock(&info->lock);

	अगर (info->limit > 0 && !info->अक्षरging) अणु
		/* set current limitation and start to अक्षरge */
		ret = sc2731_अक्षरger_set_current_limit(info, info->limit);
		अगर (ret)
			जाओ out;

		ret = sc2731_अक्षरger_set_current(info, info->limit);
		अगर (ret)
			जाओ out;

		ret = sc2731_अक्षरger_start_अक्षरge(info);
		अगर (ret)
			जाओ out;

		info->अक्षरging = true;
	पूर्ण अन्यथा अगर (!info->limit && info->अक्षरging) अणु
		/* Stop अक्षरging */
		info->अक्षरging = false;
		sc2731_अक्षरger_stop_अक्षरge(info);
	पूर्ण

out:
	mutex_unlock(&info->lock);
पूर्ण

अटल पूर्णांक sc2731_अक्षरger_usb_change(काष्ठा notअगरier_block *nb,
				     अचिन्हित दीर्घ limit, व्योम *data)
अणु
	काष्ठा sc2731_अक्षरger_info *info =
		container_of(nb, काष्ठा sc2731_अक्षरger_info, usb_notअगरy);

	info->limit = limit;

	schedule_work(&info->work);

	वापस NOTIFY_OK;
पूर्ण

अटल पूर्णांक sc2731_अक्षरger_hw_init(काष्ठा sc2731_अक्षरger_info *info)
अणु
	काष्ठा घातer_supply_battery_info bat_info = अणु पूर्ण;
	u32 term_currrent, term_voltage, cur_val, vol_val;
	पूर्णांक ret;

	/* Enable अक्षरger module */
	ret = regmap_update_bits(info->regmap, SC2731_MODULE_EN1,
				 SC2731_CHARGE_EN, SC2731_CHARGE_EN);
	अगर (ret)
		वापस ret;

	ret = घातer_supply_get_battery_info(info->psy_usb, &bat_info);
	अगर (ret) अणु
		dev_warn(info->dev, "no battery information is supplied\n");

		/*
		 * If no battery inक्रमmation is supplied, we should set
		 * शेष अक्षरge termination current to 120 mA, and शेष
		 * अक्षरge termination voltage to 4.35V.
		 */
		cur_val = 0x2;
		vol_val = 0x1;
	पूर्ण अन्यथा अणु
		term_currrent = bat_info.अक्षरge_term_current_ua / 1000;

		अगर (term_currrent <= 90)
			cur_val = 0;
		अन्यथा अगर (term_currrent >= 265)
			cur_val = 0x7;
		अन्यथा
			cur_val = ((term_currrent - 90) / 25) + 1;

		term_voltage = bat_info.स्थिरant_अक्षरge_voltage_max_uv / 1000;

		अगर (term_voltage > 4500)
			term_voltage = 4500;

		अगर (term_voltage > 4200)
			vol_val = (term_voltage - 4200) / 100;
		अन्यथा
			vol_val = 0;

		घातer_supply_put_battery_info(info->psy_usb, &bat_info);
	पूर्ण

	/* Set अक्षरge termination current */
	ret = regmap_update_bits(info->regmap, info->base + SC2731_CHG_CFG2,
				 SC2731_TERMINATION_CUR_MASK, cur_val);
	अगर (ret)
		जाओ error;

	/* Set अक्षरge termination voltage */
	ret = regmap_update_bits(info->regmap, info->base + SC2731_CHG_CFG0,
				 SC2731_TERMINATION_VOL_MASK |
				 SC2731_TERMINATION_VOL_CAL_MASK,
				 (vol_val << SC2731_TERMINATION_VOL_SHIFT) |
				 (0x6 << SC2731_TERMINATION_VOL_CAL_SHIFT));
	अगर (ret)
		जाओ error;

	वापस 0;

error:
	regmap_update_bits(info->regmap, SC2731_MODULE_EN1, SC2731_CHARGE_EN, 0);
	वापस ret;
पूर्ण

अटल व्योम sc2731_अक्षरger_detect_status(काष्ठा sc2731_अक्षरger_info *info)
अणु
	अचिन्हित पूर्णांक min, max;

	/*
	 * If the USB अक्षरger status has been USB_CHARGER_PRESENT beक्रमe
	 * रेजिस्टरing the notअगरier, we should start to अक्षरge with getting
	 * the अक्षरge current.
	 */
	अगर (info->usb_phy->chg_state != USB_CHARGER_PRESENT)
		वापस;

	usb_phy_get_अक्षरger_current(info->usb_phy, &min, &max);
	info->limit = min;

	schedule_work(&info->work);
पूर्ण

अटल पूर्णांक sc2731_अक्षरger_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा sc2731_अक्षरger_info *info;
	काष्ठा घातer_supply_config अक्षरger_cfg = अणु पूर्ण;
	पूर्णांक ret;

	info = devm_kzalloc(&pdev->dev, माप(*info), GFP_KERNEL);
	अगर (!info)
		वापस -ENOMEM;

	mutex_init(&info->lock);
	info->dev = &pdev->dev;
	INIT_WORK(&info->work, sc2731_अक्षरger_work);

	info->regmap = dev_get_regmap(pdev->dev.parent, शून्य);
	अगर (!info->regmap) अणु
		dev_err(&pdev->dev, "failed to get charger regmap\n");
		वापस -ENODEV;
	पूर्ण

	ret = of_property_पढ़ो_u32(np, "reg", &info->base);
	अगर (ret) अणु
		dev_err(&pdev->dev, "failed to get register address\n");
		वापस -ENODEV;
	पूर्ण

	अक्षरger_cfg.drv_data = info;
	अक्षरger_cfg.of_node = np;
	info->psy_usb = devm_घातer_supply_रेजिस्टर(&pdev->dev,
						   &sc2731_अक्षरger_desc,
						   &अक्षरger_cfg);
	अगर (IS_ERR(info->psy_usb)) अणु
		dev_err(&pdev->dev, "failed to register power supply\n");
		वापस PTR_ERR(info->psy_usb);
	पूर्ण

	ret = sc2731_अक्षरger_hw_init(info);
	अगर (ret)
		वापस ret;

	info->usb_phy = devm_usb_get_phy_by_phandle(&pdev->dev, "phys", 0);
	अगर (IS_ERR(info->usb_phy)) अणु
		dev_err(&pdev->dev, "failed to find USB phy\n");
		वापस PTR_ERR(info->usb_phy);
	पूर्ण

	info->usb_notअगरy.notअगरier_call = sc2731_अक्षरger_usb_change;
	ret = usb_रेजिस्टर_notअगरier(info->usb_phy, &info->usb_notअगरy);
	अगर (ret) अणु
		dev_err(&pdev->dev, "failed to register notifier: %d\n", ret);
		वापस ret;
	पूर्ण

	sc2731_अक्षरger_detect_status(info);

	वापस 0;
पूर्ण

अटल पूर्णांक sc2731_अक्षरger_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sc2731_अक्षरger_info *info = platक्रमm_get_drvdata(pdev);

	usb_unरेजिस्टर_notअगरier(info->usb_phy, &info->usb_notअगरy);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id sc2731_अक्षरger_of_match[] = अणु
	अणु .compatible = "sprd,sc2731-charger", पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_driver sc2731_अक्षरger_driver = अणु
	.driver = अणु
		.name = "sc2731-charger",
		.of_match_table = sc2731_अक्षरger_of_match,
	पूर्ण,
	.probe = sc2731_अक्षरger_probe,
	.हटाओ = sc2731_अक्षरger_हटाओ,
पूर्ण;

module_platक्रमm_driver(sc2731_अक्षरger_driver);

MODULE_DESCRIPTION("Spreadtrum SC2731 Charger Driver");
MODULE_LICENSE("GPL v2");
