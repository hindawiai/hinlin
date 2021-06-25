<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Power supply driver क्रम the Active-semi ACT8945A PMIC
 *
 * Copyright (C) 2015 Aपंचांगel Corporation
 *
 * Author: Wenyou Yang <wenyou.yang@aपंचांगel.com>
 */
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/घातer_supply.h>
#समावेश <linux/regmap.h>
#समावेश <linux/gpio/consumer.h>

अटल स्थिर अक्षर *act8945a_अक्षरger_model = "ACT8945A";
अटल स्थिर अक्षर *act8945a_अक्षरger_manufacturer = "Active-semi";

/*
 * ACT8945A Charger Register Map
 */

/* 0x70: Reserved */
#घोषणा ACT8945A_APCH_CFG		0x71
#घोषणा ACT8945A_APCH_STATUS		0x78
#घोषणा ACT8945A_APCH_CTRL		0x79
#घोषणा ACT8945A_APCH_STATE		0x7A

/* ACT8945A_APCH_CFG */
#घोषणा APCH_CFG_OVPSET			(0x3 << 0)
#घोषणा APCH_CFG_OVPSET_6V6		(0x0 << 0)
#घोषणा APCH_CFG_OVPSET_7V		(0x1 << 0)
#घोषणा APCH_CFG_OVPSET_7V5		(0x2 << 0)
#घोषणा APCH_CFG_OVPSET_8V		(0x3 << 0)
#घोषणा APCH_CFG_PRETIMO		(0x3 << 2)
#घोषणा APCH_CFG_PRETIMO_40_MIN		(0x0 << 2)
#घोषणा APCH_CFG_PRETIMO_60_MIN		(0x1 << 2)
#घोषणा APCH_CFG_PRETIMO_80_MIN		(0x2 << 2)
#घोषणा APCH_CFG_PRETIMO_DISABLED	(0x3 << 2)
#घोषणा APCH_CFG_TOTTIMO		(0x3 << 4)
#घोषणा APCH_CFG_TOTTIMO_3_HOUR		(0x0 << 4)
#घोषणा APCH_CFG_TOTTIMO_4_HOUR		(0x1 << 4)
#घोषणा APCH_CFG_TOTTIMO_5_HOUR		(0x2 << 4)
#घोषणा APCH_CFG_TOTTIMO_DISABLED	(0x3 << 4)
#घोषणा APCH_CFG_SUSCHG			(0x1 << 7)

#घोषणा APCH_STATUS_CHGDAT		BIT(0)
#घोषणा APCH_STATUS_INDAT		BIT(1)
#घोषणा APCH_STATUS_TEMPDAT		BIT(2)
#घोषणा APCH_STATUS_TIMRDAT		BIT(3)
#घोषणा APCH_STATUS_CHGSTAT		BIT(4)
#घोषणा APCH_STATUS_INSTAT		BIT(5)
#घोषणा APCH_STATUS_TEMPSTAT		BIT(6)
#घोषणा APCH_STATUS_TIMRSTAT		BIT(7)

#घोषणा APCH_CTRL_CHGEOCOUT		BIT(0)
#घोषणा APCH_CTRL_INDIS			BIT(1)
#घोषणा APCH_CTRL_TEMPOUT		BIT(2)
#घोषणा APCH_CTRL_TIMRPRE		BIT(3)
#घोषणा APCH_CTRL_CHGEOCIN		BIT(4)
#घोषणा APCH_CTRL_INCON			BIT(5)
#घोषणा APCH_CTRL_TEMPIN		BIT(6)
#घोषणा APCH_CTRL_TIMRTOT		BIT(7)

#घोषणा APCH_STATE_ACINSTAT		(0x1 << 1)
#घोषणा APCH_STATE_CSTATE		(0x3 << 4)
#घोषणा APCH_STATE_CSTATE_SHIFT		4
#घोषणा APCH_STATE_CSTATE_DISABLED	0x00
#घोषणा APCH_STATE_CSTATE_EOC		0x01
#घोषणा APCH_STATE_CSTATE_FAST		0x02
#घोषणा APCH_STATE_CSTATE_PRE		0x03

काष्ठा act8945a_अक्षरger अणु
	काष्ठा घातer_supply *psy;
	काष्ठा घातer_supply_desc desc;
	काष्ठा regmap *regmap;
	काष्ठा work_काष्ठा work;

	bool init_करोne;
	काष्ठा gpio_desc *lbo_gpio;
	काष्ठा gpio_desc *chglev_gpio;
पूर्ण;

अटल पूर्णांक act8945a_get_अक्षरger_state(काष्ठा regmap *regmap, पूर्णांक *val)
अणु
	पूर्णांक ret;
	अचिन्हित पूर्णांक status, state;

	ret = regmap_पढ़ो(regmap, ACT8945A_APCH_STATUS, &status);
	अगर (ret < 0)
		वापस ret;

	ret = regmap_पढ़ो(regmap, ACT8945A_APCH_STATE, &state);
	अगर (ret < 0)
		वापस ret;

	state &= APCH_STATE_CSTATE;
	state >>= APCH_STATE_CSTATE_SHIFT;

	चयन (state) अणु
	हाल APCH_STATE_CSTATE_PRE:
	हाल APCH_STATE_CSTATE_FAST:
		*val = POWER_SUPPLY_STATUS_CHARGING;
		अवरोध;
	हाल APCH_STATE_CSTATE_EOC:
		अगर (status & APCH_STATUS_CHGDAT)
			*val = POWER_SUPPLY_STATUS_FULL;
		अन्यथा
			*val = POWER_SUPPLY_STATUS_CHARGING;
		अवरोध;
	हाल APCH_STATE_CSTATE_DISABLED:
	शेष:
		अगर (!(status & APCH_STATUS_INDAT))
			*val = POWER_SUPPLY_STATUS_DISCHARGING;
		अन्यथा
			*val = POWER_SUPPLY_STATUS_NOT_CHARGING;
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक act8945a_get_अक्षरge_type(काष्ठा regmap *regmap, पूर्णांक *val)
अणु
	पूर्णांक ret;
	अचिन्हित पूर्णांक status, state;

	ret = regmap_पढ़ो(regmap, ACT8945A_APCH_STATUS, &status);
	अगर (ret < 0)
		वापस ret;

	ret = regmap_पढ़ो(regmap, ACT8945A_APCH_STATE, &state);
	अगर (ret < 0)
		वापस ret;

	state &= APCH_STATE_CSTATE;
	state >>= APCH_STATE_CSTATE_SHIFT;

	चयन (state) अणु
	हाल APCH_STATE_CSTATE_PRE:
		*val = POWER_SUPPLY_CHARGE_TYPE_TRICKLE;
		अवरोध;
	हाल APCH_STATE_CSTATE_FAST:
		*val = POWER_SUPPLY_CHARGE_TYPE_FAST;
		अवरोध;
	हाल APCH_STATE_CSTATE_EOC:
		*val = POWER_SUPPLY_CHARGE_TYPE_NONE;
		अवरोध;
	हाल APCH_STATE_CSTATE_DISABLED:
	शेष:
		अगर (!(status & APCH_STATUS_INDAT))
			*val = POWER_SUPPLY_CHARGE_TYPE_NONE;
		अन्यथा
			*val = POWER_SUPPLY_CHARGE_TYPE_UNKNOWN;
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक act8945a_get_battery_health(काष्ठा regmap *regmap, पूर्णांक *val)
अणु
	पूर्णांक ret;
	अचिन्हित पूर्णांक status, state, config;

	ret = regmap_पढ़ो(regmap, ACT8945A_APCH_STATUS, &status);
	अगर (ret < 0)
		वापस ret;

	ret = regmap_पढ़ो(regmap, ACT8945A_APCH_CFG, &config);
	अगर (ret < 0)
		वापस ret;

	ret = regmap_पढ़ो(regmap, ACT8945A_APCH_STATE, &state);
	अगर (ret < 0)
		वापस ret;

	state &= APCH_STATE_CSTATE;
	state >>= APCH_STATE_CSTATE_SHIFT;

	चयन (state) अणु
	हाल APCH_STATE_CSTATE_DISABLED:
		अगर (config & APCH_CFG_SUSCHG) अणु
			*val = POWER_SUPPLY_HEALTH_UNKNOWN;
		पूर्ण अन्यथा अगर (status & APCH_STATUS_INDAT) अणु
			अगर (!(status & APCH_STATUS_TEMPDAT))
				*val = POWER_SUPPLY_HEALTH_OVERHEAT;
			अन्यथा अगर (status & APCH_STATUS_TIMRDAT)
				*val = POWER_SUPPLY_HEALTH_SAFETY_TIMER_EXPIRE;
			अन्यथा
				*val = POWER_SUPPLY_HEALTH_OVERVOLTAGE;
		पूर्ण अन्यथा अणु
			*val = POWER_SUPPLY_HEALTH_GOOD;
		पूर्ण
		अवरोध;
	हाल APCH_STATE_CSTATE_PRE:
	हाल APCH_STATE_CSTATE_FAST:
	हाल APCH_STATE_CSTATE_EOC:
	शेष:
		*val = POWER_SUPPLY_HEALTH_GOOD;
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक act8945a_get_capacity_level(काष्ठा act8945a_अक्षरger *अक्षरger,
				       काष्ठा regmap *regmap, पूर्णांक *val)
अणु
	पूर्णांक ret;
	अचिन्हित पूर्णांक status, state, config;
	पूर्णांक lbo_level = gpiod_get_value(अक्षरger->lbo_gpio);

	ret = regmap_पढ़ो(regmap, ACT8945A_APCH_STATUS, &status);
	अगर (ret < 0)
		वापस ret;

	ret = regmap_पढ़ो(regmap, ACT8945A_APCH_CFG, &config);
	अगर (ret < 0)
		वापस ret;

	ret = regmap_पढ़ो(regmap, ACT8945A_APCH_STATE, &state);
	अगर (ret < 0)
		वापस ret;

	state &= APCH_STATE_CSTATE;
	state >>= APCH_STATE_CSTATE_SHIFT;

	चयन (state) अणु
	हाल APCH_STATE_CSTATE_PRE:
		*val = POWER_SUPPLY_CAPACITY_LEVEL_LOW;
		अवरोध;
	हाल APCH_STATE_CSTATE_FAST:
		अगर (lbo_level)
			*val = POWER_SUPPLY_CAPACITY_LEVEL_HIGH;
		अन्यथा
			*val = POWER_SUPPLY_CAPACITY_LEVEL_LOW;
		अवरोध;
	हाल APCH_STATE_CSTATE_EOC:
		अगर (status & APCH_STATUS_CHGDAT)
			*val = POWER_SUPPLY_CAPACITY_LEVEL_FULL;
		अन्यथा
			*val = POWER_SUPPLY_CAPACITY_LEVEL_NORMAL;
		अवरोध;
	हाल APCH_STATE_CSTATE_DISABLED:
	शेष:
		अगर (config & APCH_CFG_SUSCHG) अणु
			*val = POWER_SUPPLY_CAPACITY_LEVEL_UNKNOWN;
		पूर्ण अन्यथा अणु
			*val = POWER_SUPPLY_CAPACITY_LEVEL_NORMAL;
			अगर (!(status & APCH_STATUS_INDAT)) अणु
				अगर (!lbo_level)
					*val = POWER_SUPPLY_CAPACITY_LEVEL_CRITICAL;
			पूर्ण
		पूर्ण
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

#घोषणा MAX_CURRENT_USB_HIGH	450000
#घोषणा MAX_CURRENT_USB_LOW	90000
#घोषणा MAX_CURRENT_USB_PRE	45000
/*
 * Riset(K) = 2336 * (1V/Ichg(mA)) - 0.205
 * Riset = 2.43K
 */
#घोषणा MAX_CURRENT_AC_HIGH		886527
#घोषणा MAX_CURRENT_AC_LOW		117305
#घोषणा MAX_CURRENT_AC_HIGH_PRE		88653
#घोषणा MAX_CURRENT_AC_LOW_PRE		11731

अटल पूर्णांक act8945a_get_current_max(काष्ठा act8945a_अक्षरger *अक्षरger,
				    काष्ठा regmap *regmap, पूर्णांक *val)
अणु
	पूर्णांक ret;
	अचिन्हित पूर्णांक status, state;
	अचिन्हित पूर्णांक acin_state;
	पूर्णांक chgin_level = gpiod_get_value(अक्षरger->chglev_gpio);

	ret = regmap_पढ़ो(regmap, ACT8945A_APCH_STATUS, &status);
	अगर (ret < 0)
		वापस ret;

	ret = regmap_पढ़ो(regmap, ACT8945A_APCH_STATE, &state);
	अगर (ret < 0)
		वापस ret;

	acin_state = (state & APCH_STATE_ACINSTAT) >> 1;

	state &= APCH_STATE_CSTATE;
	state >>= APCH_STATE_CSTATE_SHIFT;

	चयन (state) अणु
	हाल APCH_STATE_CSTATE_PRE:
		अगर (acin_state) अणु
			अगर (chgin_level)
				*val = MAX_CURRENT_AC_HIGH_PRE;
			अन्यथा
				*val = MAX_CURRENT_AC_LOW_PRE;
		पूर्ण अन्यथा अणु
			*val = MAX_CURRENT_USB_PRE;
		पूर्ण
		अवरोध;
	हाल APCH_STATE_CSTATE_FAST:
		अगर (acin_state) अणु
			अगर (chgin_level)
				*val = MAX_CURRENT_AC_HIGH;
			अन्यथा
				*val = MAX_CURRENT_AC_LOW;
		पूर्ण अन्यथा अणु
			अगर (chgin_level)
				*val = MAX_CURRENT_USB_HIGH;
			अन्यथा
				*val = MAX_CURRENT_USB_LOW;
		पूर्ण
		अवरोध;
	हाल APCH_STATE_CSTATE_EOC:
	हाल APCH_STATE_CSTATE_DISABLED:
	शेष:
		*val = 0;
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल क्रमागत घातer_supply_property act8945a_अक्षरger_props[] = अणु
	POWER_SUPPLY_PROP_STATUS,
	POWER_SUPPLY_PROP_CHARGE_TYPE,
	POWER_SUPPLY_PROP_TECHNOLOGY,
	POWER_SUPPLY_PROP_HEALTH,
	POWER_SUPPLY_PROP_CAPACITY_LEVEL,
	POWER_SUPPLY_PROP_CURRENT_MAX,
	POWER_SUPPLY_PROP_MODEL_NAME,
	POWER_SUPPLY_PROP_MANUFACTURER
पूर्ण;

अटल पूर्णांक act8945a_अक्षरger_get_property(काष्ठा घातer_supply *psy,
					 क्रमागत घातer_supply_property prop,
					 जोड़ घातer_supply_propval *val)
अणु
	काष्ठा act8945a_अक्षरger *अक्षरger = घातer_supply_get_drvdata(psy);
	काष्ठा regmap *regmap = अक्षरger->regmap;
	पूर्णांक ret = 0;

	चयन (prop) अणु
	हाल POWER_SUPPLY_PROP_STATUS:
		ret = act8945a_get_अक्षरger_state(regmap, &val->पूर्णांकval);
		अवरोध;
	हाल POWER_SUPPLY_PROP_CHARGE_TYPE:
		ret = act8945a_get_अक्षरge_type(regmap, &val->पूर्णांकval);
		अवरोध;
	हाल POWER_SUPPLY_PROP_TECHNOLOGY:
		val->पूर्णांकval = POWER_SUPPLY_TECHNOLOGY_LION;
		अवरोध;
	हाल POWER_SUPPLY_PROP_HEALTH:
		ret = act8945a_get_battery_health(regmap, &val->पूर्णांकval);
		अवरोध;
	हाल POWER_SUPPLY_PROP_CAPACITY_LEVEL:
		ret = act8945a_get_capacity_level(अक्षरger,
						  regmap, &val->पूर्णांकval);
		अवरोध;
	हाल POWER_SUPPLY_PROP_CURRENT_MAX:
		ret = act8945a_get_current_max(अक्षरger,
					       regmap, &val->पूर्णांकval);
		अवरोध;
	हाल POWER_SUPPLY_PROP_MODEL_NAME:
		val->strval = act8945a_अक्षरger_model;
		अवरोध;
	हाल POWER_SUPPLY_PROP_MANUFACTURER:
		val->strval = act8945a_अक्षरger_manufacturer;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक act8945a_enable_पूर्णांकerrupt(काष्ठा act8945a_अक्षरger *अक्षरger)
अणु
	काष्ठा regmap *regmap = अक्षरger->regmap;
	अचिन्हित अक्षर ctrl;
	पूर्णांक ret;

	ctrl = APCH_CTRL_CHGEOCOUT | APCH_CTRL_CHGEOCIN |
	       APCH_CTRL_INDIS | APCH_CTRL_INCON |
	       APCH_CTRL_TEMPOUT | APCH_CTRL_TEMPIN |
	       APCH_CTRL_TIMRPRE | APCH_CTRL_TIMRTOT;
	ret = regmap_ग_लिखो(regmap, ACT8945A_APCH_CTRL, ctrl);
	अगर (ret)
		वापस ret;

	ctrl = APCH_STATUS_CHGSTAT | APCH_STATUS_INSTAT |
	       APCH_STATUS_TEMPSTAT | APCH_STATUS_TIMRSTAT;
	ret = regmap_ग_लिखो(regmap, ACT8945A_APCH_STATUS, ctrl);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक act8945a_set_supply_type(काष्ठा act8945a_अक्षरger *अक्षरger,
					     अचिन्हित पूर्णांक *type)
अणु
	अचिन्हित पूर्णांक status, state;
	पूर्णांक ret;

	ret = regmap_पढ़ो(अक्षरger->regmap, ACT8945A_APCH_STATUS, &status);
	अगर (ret < 0)
		वापस ret;

	ret = regmap_पढ़ो(अक्षरger->regmap, ACT8945A_APCH_STATE, &state);
	अगर (ret < 0)
		वापस ret;

	अगर (status & APCH_STATUS_INDAT) अणु
		अगर (state & APCH_STATE_ACINSTAT)
			*type = POWER_SUPPLY_TYPE_MAINS;
		अन्यथा
			*type = POWER_SUPPLY_TYPE_USB;
	पूर्ण अन्यथा अणु
		*type = POWER_SUPPLY_TYPE_BATTERY;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम act8945a_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा act8945a_अक्षरger *अक्षरger =
			container_of(work, काष्ठा act8945a_अक्षरger, work);

	act8945a_set_supply_type(अक्षरger, &अक्षरger->desc.type);

	घातer_supply_changed(अक्षरger->psy);
पूर्ण

अटल irqवापस_t act8945a_status_changed(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा act8945a_अक्षरger *अक्षरger = dev_id;

	अगर (अक्षरger->init_करोne)
		schedule_work(&अक्षरger->work);

	वापस IRQ_HANDLED;
पूर्ण

#घोषणा DEFAULT_TOTAL_TIME_OUT		3
#घोषणा DEFAULT_PRE_TIME_OUT		40
#घोषणा DEFAULT_INPUT_OVP_THRESHOLD	6600

अटल पूर्णांक act8945a_अक्षरger_config(काष्ठा device *dev,
				   काष्ठा act8945a_अक्षरger *अक्षरger)
अणु
	काष्ठा device_node *np = dev->of_node;
	काष्ठा regmap *regmap = अक्षरger->regmap;

	u32 total_समय_out;
	u32 pre_समय_out;
	u32 input_voltage_threshold;
	पूर्णांक err, ret;

	अचिन्हित पूर्णांक पंचांगp;
	अचिन्हित पूर्णांक value = 0;

	अगर (!np) अणु
		dev_err(dev, "no charger of node\n");
		वापस -EINVAL;
	पूर्ण

	ret = regmap_पढ़ो(regmap, ACT8945A_APCH_CFG, &पंचांगp);
	अगर (ret)
		वापस ret;

	अगर (पंचांगp & APCH_CFG_SUSCHG) अणु
		value |= APCH_CFG_SUSCHG;
		dev_info(dev, "have been suspended\n");
	पूर्ण

	अक्षरger->lbo_gpio = devm_gpiod_get_optional(dev, "active-semi,lbo",
						    GPIOD_IN);
	अगर (IS_ERR(अक्षरger->lbo_gpio)) अणु
		err = PTR_ERR(अक्षरger->lbo_gpio);
		dev_err(dev, "unable to claim gpio \"lbo\": %d\n", err);
		वापस err;
	पूर्ण

	ret = devm_request_irq(dev, gpiod_to_irq(अक्षरger->lbo_gpio),
			       act8945a_status_changed,
			       (IRQF_TRIGGER_FALLING | IRQF_TRIGGER_RISING),
			       "act8945a_lbo_detect", अक्षरger);
	अगर (ret)
		dev_info(dev, "failed to request gpio \"lbo\" IRQ\n");

	अक्षरger->chglev_gpio = devm_gpiod_get_optional(dev,
						       "active-semi,chglev",
						       GPIOD_IN);
	अगर (IS_ERR(अक्षरger->chglev_gpio)) अणु
		err = PTR_ERR(अक्षरger->chglev_gpio);
		dev_err(dev, "unable to claim gpio \"chglev\": %d\n", err);
		वापस err;
	पूर्ण

	अगर (of_property_पढ़ो_u32(np,
				 "active-semi,input-voltage-threshold-microvolt",
				 &input_voltage_threshold))
		input_voltage_threshold = DEFAULT_INPUT_OVP_THRESHOLD;

	अगर (of_property_पढ़ो_u32(np,
				 "active-semi,precondition-timeout",
				 &pre_समय_out))
		pre_समय_out = DEFAULT_PRE_TIME_OUT;

	अगर (of_property_पढ़ो_u32(np, "active-semi,total-timeout",
				 &total_समय_out))
		total_समय_out = DEFAULT_TOTAL_TIME_OUT;

	चयन (input_voltage_threshold) अणु
	हाल 8000:
		value |= APCH_CFG_OVPSET_8V;
		अवरोध;
	हाल 7500:
		value |= APCH_CFG_OVPSET_7V5;
		अवरोध;
	हाल 7000:
		value |= APCH_CFG_OVPSET_7V;
		अवरोध;
	हाल 6600:
	शेष:
		value |= APCH_CFG_OVPSET_6V6;
		अवरोध;
	पूर्ण

	चयन (pre_समय_out) अणु
	हाल 60:
		value |= APCH_CFG_PRETIMO_60_MIN;
		अवरोध;
	हाल 80:
		value |= APCH_CFG_PRETIMO_80_MIN;
		अवरोध;
	हाल 0:
		value |= APCH_CFG_PRETIMO_DISABLED;
		अवरोध;
	हाल 40:
	शेष:
		value |= APCH_CFG_PRETIMO_40_MIN;
		अवरोध;
	पूर्ण

	चयन (total_समय_out) अणु
	हाल 4:
		value |= APCH_CFG_TOTTIMO_4_HOUR;
		अवरोध;
	हाल 5:
		value |= APCH_CFG_TOTTIMO_5_HOUR;
		अवरोध;
	हाल 0:
		value |= APCH_CFG_TOTTIMO_DISABLED;
		अवरोध;
	हाल 3:
	शेष:
		value |= APCH_CFG_TOTTIMO_3_HOUR;
		अवरोध;
	पूर्ण

	वापस regmap_ग_लिखो(regmap, ACT8945A_APCH_CFG, value);
पूर्ण

अटल पूर्णांक act8945a_अक्षरger_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा act8945a_अक्षरger *अक्षरger;
	काष्ठा घातer_supply_config psy_cfg = अणुपूर्ण;
	पूर्णांक irq, ret;

	अक्षरger = devm_kzalloc(&pdev->dev, माप(*अक्षरger), GFP_KERNEL);
	अगर (!अक्षरger)
		वापस -ENOMEM;

	अक्षरger->regmap = dev_get_regmap(pdev->dev.parent, शून्य);
	अगर (!अक्षरger->regmap) अणु
		dev_err(&pdev->dev, "Parent did not provide regmap\n");
		वापस -EINVAL;
	पूर्ण

	ret = act8945a_अक्षरger_config(&pdev->dev, अक्षरger);
	अगर (ret)
		वापस ret;

	irq = of_irq_get(pdev->dev.of_node, 0);
	अगर (irq <= 0) अणु
		dev_err(&pdev->dev, "failed to find IRQ number\n");
		वापस irq ?: -ENXIO;
	पूर्ण

	ret = devm_request_irq(&pdev->dev, irq, act8945a_status_changed,
			       IRQF_TRIGGER_FALLING, "act8945a_interrupt",
			       अक्षरger);
	अगर (ret) अणु
		dev_err(&pdev->dev, "failed to request nIRQ pin IRQ\n");
		वापस ret;
	पूर्ण

	अक्षरger->desc.name = "act8945a-charger";
	अक्षरger->desc.get_property = act8945a_अक्षरger_get_property;
	अक्षरger->desc.properties = act8945a_अक्षरger_props;
	अक्षरger->desc.num_properties = ARRAY_SIZE(act8945a_अक्षरger_props);

	ret = act8945a_set_supply_type(अक्षरger, &अक्षरger->desc.type);
	अगर (ret)
		वापस -EINVAL;

	psy_cfg.of_node	= pdev->dev.of_node;
	psy_cfg.drv_data = अक्षरger;

	अक्षरger->psy = devm_घातer_supply_रेजिस्टर(&pdev->dev,
						  &अक्षरger->desc,
						  &psy_cfg);
	अगर (IS_ERR(अक्षरger->psy)) अणु
		dev_err(&pdev->dev, "failed to register power supply\n");
		वापस PTR_ERR(अक्षरger->psy);
	पूर्ण

	platक्रमm_set_drvdata(pdev, अक्षरger);

	INIT_WORK(&अक्षरger->work, act8945a_work);

	ret = act8945a_enable_पूर्णांकerrupt(अक्षरger);
	अगर (ret)
		वापस -EIO;

	अक्षरger->init_करोne = true;

	वापस 0;
पूर्ण

अटल पूर्णांक act8945a_अक्षरger_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा act8945a_अक्षरger *अक्षरger = platक्रमm_get_drvdata(pdev);

	अक्षरger->init_करोne = false;
	cancel_work_sync(&अक्षरger->work);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver act8945a_अक्षरger_driver = अणु
	.driver	= अणु
		.name = "act8945a-charger",
	पूर्ण,
	.probe	= act8945a_अक्षरger_probe,
	.हटाओ = act8945a_अक्षरger_हटाओ,
पूर्ण;
module_platक्रमm_driver(act8945a_अक्षरger_driver);

MODULE_DESCRIPTION("Active-semi ACT8945A ActivePath charger driver");
MODULE_AUTHOR("Wenyou Yang <wenyou.yang@atmel.com>");
MODULE_LICENSE("GPL");
