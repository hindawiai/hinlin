<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * I2C client/driver क्रम the Linear Technology LTC2941, LTC2942, LTC2943
 * and LTC2944 Battery Gas Gauge IC
 *
 * Copyright (C) 2014 Topic Embedded Systems
 *
 * Author: Auryn Verwegen
 * Author: Mike Looijmans
 */
#समावेश <linux/devm-helpers.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/types.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/swab.h>
#समावेश <linux/i2c.h>
#समावेश <linux/delay.h>
#समावेश <linux/घातer_supply.h>
#समावेश <linux/slab.h>

#घोषणा I16_MSB(x)			((x >> 8) & 0xFF)
#घोषणा I16_LSB(x)			(x & 0xFF)

#घोषणा LTC294X_WORK_DELAY		10	/* Update delay in seconds */

#घोषणा LTC294X_MAX_VALUE		0xFFFF
#घोषणा LTC294X_MID_SUPPLY		0x7FFF

#घोषणा LTC2941_MAX_PRESCALER_EXP	7
#घोषणा LTC2943_MAX_PRESCALER_EXP	6

क्रमागत ltc294x_reg अणु
	LTC294X_REG_STATUS		= 0x00,
	LTC294X_REG_CONTROL		= 0x01,
	LTC294X_REG_ACC_CHARGE_MSB	= 0x02,
	LTC294X_REG_ACC_CHARGE_LSB	= 0x03,
	LTC294X_REG_CHARGE_THR_HIGH_MSB	= 0x04,
	LTC294X_REG_CHARGE_THR_HIGH_LSB	= 0x05,
	LTC294X_REG_CHARGE_THR_LOW_MSB	= 0x06,
	LTC294X_REG_CHARGE_THR_LOW_LSB	= 0x07,
	LTC294X_REG_VOLTAGE_MSB		= 0x08,
	LTC294X_REG_VOLTAGE_LSB		= 0x09,
	LTC2942_REG_TEMPERATURE_MSB	= 0x0C,
	LTC2942_REG_TEMPERATURE_LSB	= 0x0D,
	LTC2943_REG_CURRENT_MSB		= 0x0E,
	LTC2943_REG_CURRENT_LSB		= 0x0F,
	LTC2943_REG_TEMPERATURE_MSB	= 0x14,
	LTC2943_REG_TEMPERATURE_LSB	= 0x15,
पूर्ण;

क्रमागत ltc294x_id अणु
	LTC2941_ID,
	LTC2942_ID,
	LTC2943_ID,
	LTC2944_ID,
पूर्ण;

#घोषणा LTC2941_REG_STATUS_CHIP_ID	BIT(7)

#घोषणा LTC2942_REG_CONTROL_MODE_SCAN	(BIT(7) | BIT(6))
#घोषणा LTC2943_REG_CONTROL_MODE_SCAN	BIT(7)
#घोषणा LTC294X_REG_CONTROL_PRESCALER_MASK	(BIT(5) | BIT(4) | BIT(3))
#घोषणा LTC294X_REG_CONTROL_SHUTDOWN_MASK	(BIT(0))
#घोषणा LTC294X_REG_CONTROL_PRESCALER_SET(x) \
	((x << 3) & LTC294X_REG_CONTROL_PRESCALER_MASK)
#घोषणा LTC294X_REG_CONTROL_ALCC_CONFIG_DISABLED	0
#घोषणा LTC294X_REG_CONTROL_ADC_DISABLE(x)	((x) & ~(BIT(7) | BIT(6)))

काष्ठा ltc294x_info अणु
	काष्ठा i2c_client *client;	/* I2C Client poपूर्णांकer */
	काष्ठा घातer_supply *supply;	/* Supply poपूर्णांकer */
	काष्ठा घातer_supply_desc supply_desc;	/* Supply description */
	काष्ठा delayed_work work;	/* Work scheduler */
	क्रमागत ltc294x_id id;		/* Chip type */
	पूर्णांक अक्षरge;	/* Last अक्षरge रेजिस्टर content */
	पूर्णांक r_sense;	/* mOhm */
	पूर्णांक Qlsb;	/* nAh */
पूर्ण;

अटल अंतरभूत पूर्णांक convert_bin_to_uAh(
	स्थिर काष्ठा ltc294x_info *info, पूर्णांक Q)
अणु
	वापस ((Q * (info->Qlsb / 10))) / 100;
पूर्ण

अटल अंतरभूत पूर्णांक convert_uAh_to_bin(
	स्थिर काष्ठा ltc294x_info *info, पूर्णांक uAh)
अणु
	पूर्णांक Q;

	Q = (uAh * 100) / (info->Qlsb/10);
	वापस (Q < LTC294X_MAX_VALUE) ? Q : LTC294X_MAX_VALUE;
पूर्ण

अटल पूर्णांक ltc294x_पढ़ो_regs(काष्ठा i2c_client *client,
	क्रमागत ltc294x_reg reg, u8 *buf, पूर्णांक num_regs)
अणु
	पूर्णांक ret;
	काष्ठा i2c_msg msgs[2] = अणु पूर्ण;
	u8 reg_start = reg;

	msgs[0].addr	= client->addr;
	msgs[0].len	= 1;
	msgs[0].buf	= &reg_start;

	msgs[1].addr	= client->addr;
	msgs[1].len	= num_regs;
	msgs[1].buf	= buf;
	msgs[1].flags	= I2C_M_RD;

	ret = i2c_transfer(client->adapter, &msgs[0], 2);
	अगर (ret < 0) अणु
		dev_err(&client->dev, "ltc2941 read_reg failed!\n");
		वापस ret;
	पूर्ण

	dev_dbg(&client->dev, "%s (%#x, %d) -> %#x\n",
		__func__, reg, num_regs, *buf);

	वापस 0;
पूर्ण

अटल पूर्णांक ltc294x_ग_लिखो_regs(काष्ठा i2c_client *client,
	क्रमागत ltc294x_reg reg, स्थिर u8 *buf, पूर्णांक num_regs)
अणु
	पूर्णांक ret;
	u8 reg_start = reg;

	ret = i2c_smbus_ग_लिखो_i2c_block_data(client, reg_start, num_regs, buf);
	अगर (ret < 0) अणु
		dev_err(&client->dev, "ltc2941 write_reg failed!\n");
		वापस ret;
	पूर्ण

	dev_dbg(&client->dev, "%s (%#x, %d) -> %#x\n",
		__func__, reg, num_regs, *buf);

	वापस 0;
पूर्ण

अटल पूर्णांक ltc294x_reset(स्थिर काष्ठा ltc294x_info *info, पूर्णांक prescaler_exp)
अणु
	पूर्णांक ret;
	u8 value;
	u8 control;

	/* Read status and control रेजिस्टरs */
	ret = ltc294x_पढ़ो_regs(info->client, LTC294X_REG_CONTROL, &value, 1);
	अगर (ret < 0) अणु
		dev_err(&info->client->dev,
			"Could not read registers from device\n");
		जाओ error_निकास;
	पूर्ण

	control = LTC294X_REG_CONTROL_PRESCALER_SET(prescaler_exp) |
				LTC294X_REG_CONTROL_ALCC_CONFIG_DISABLED;
	/* Put device पूर्णांकo "monitor" mode */
	चयन (info->id) अणु
	हाल LTC2942_ID:	/* 2942 measures every 2 sec */
		control |= LTC2942_REG_CONTROL_MODE_SCAN;
		अवरोध;
	हाल LTC2943_ID:
	हाल LTC2944_ID:	/* 2943 and 2944 measure every 10 sec */
		control |= LTC2943_REG_CONTROL_MODE_SCAN;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	अगर (value != control) अणु
		ret = ltc294x_ग_लिखो_regs(info->client,
			LTC294X_REG_CONTROL, &control, 1);
		अगर (ret < 0) अणु
			dev_err(&info->client->dev,
				"Could not write register\n");
			जाओ error_निकास;
		पूर्ण
	पूर्ण

	वापस 0;

error_निकास:
	वापस ret;
पूर्ण

अटल पूर्णांक ltc294x_पढ़ो_अक्षरge_रेजिस्टर(स्थिर काष्ठा ltc294x_info *info,
					क्रमागत ltc294x_reg reg)
 अणु
	पूर्णांक ret;
	u8 datar[2];

	ret = ltc294x_पढ़ो_regs(info->client, reg, &datar[0], 2);
	अगर (ret < 0)
		वापस ret;
	वापस (datar[0] << 8) + datar[1];
पूर्ण

अटल पूर्णांक ltc294x_get_अक्षरge(स्थिर काष्ठा ltc294x_info *info,
				क्रमागत ltc294x_reg reg, पूर्णांक *val)
अणु
	पूर्णांक value = ltc294x_पढ़ो_अक्षरge_रेजिस्टर(info, reg);

	अगर (value < 0)
		वापस value;
	/* When r_sense < 0, this counts up when the battery disअक्षरges */
	अगर (info->Qlsb < 0)
		value -= 0xFFFF;
	*val = convert_bin_to_uAh(info, value);
	वापस 0;
पूर्ण

अटल पूर्णांक ltc294x_set_अक्षरge_now(स्थिर काष्ठा ltc294x_info *info, पूर्णांक val)
अणु
	पूर्णांक ret;
	u8 dataw[2];
	u8 ctrl_reg;
	s32 value;

	value = convert_uAh_to_bin(info, val);
	/* Direction depends on how sense+/- were connected */
	अगर (info->Qlsb < 0)
		value += 0xFFFF;
	अगर ((value < 0) || (value > 0xFFFF)) /* input validation */
		वापस -EINVAL;

	/* Read control रेजिस्टर */
	ret = ltc294x_पढ़ो_regs(info->client,
		LTC294X_REG_CONTROL, &ctrl_reg, 1);
	अगर (ret < 0)
		वापस ret;
	/* Disable analog section */
	ctrl_reg |= LTC294X_REG_CONTROL_SHUTDOWN_MASK;
	ret = ltc294x_ग_लिखो_regs(info->client,
		LTC294X_REG_CONTROL, &ctrl_reg, 1);
	अगर (ret < 0)
		वापस ret;
	/* Set new अक्षरge value */
	dataw[0] = I16_MSB(value);
	dataw[1] = I16_LSB(value);
	ret = ltc294x_ग_लिखो_regs(info->client,
		LTC294X_REG_ACC_CHARGE_MSB, &dataw[0], 2);
	अगर (ret < 0)
		जाओ error_निकास;
	/* Enable analog section */
error_निकास:
	ctrl_reg &= ~LTC294X_REG_CONTROL_SHUTDOWN_MASK;
	ret = ltc294x_ग_लिखो_regs(info->client,
		LTC294X_REG_CONTROL, &ctrl_reg, 1);

	वापस ret < 0 ? ret : 0;
पूर्ण

अटल पूर्णांक ltc294x_set_अक्षरge_thr(स्थिर काष्ठा ltc294x_info *info,
					क्रमागत ltc294x_reg reg, पूर्णांक val)
अणु
	u8 dataw[2];
	s32 value;

	value = convert_uAh_to_bin(info, val);
	/* Direction depends on how sense+/- were connected */
	अगर (info->Qlsb < 0)
		value += 0xFFFF;
	अगर ((value < 0) || (value > 0xFFFF)) /* input validation */
		वापस -EINVAL;

	/* Set new अक्षरge value */
	dataw[0] = I16_MSB(value);
	dataw[1] = I16_LSB(value);
	वापस ltc294x_ग_लिखो_regs(info->client, reg, &dataw[0], 2);
पूर्ण

अटल पूर्णांक ltc294x_get_अक्षरge_counter(
	स्थिर काष्ठा ltc294x_info *info, पूर्णांक *val)
अणु
	पूर्णांक value = ltc294x_पढ़ो_अक्षरge_रेजिस्टर(info, LTC294X_REG_ACC_CHARGE_MSB);

	अगर (value < 0)
		वापस value;
	value -= LTC294X_MID_SUPPLY;
	*val = convert_bin_to_uAh(info, value);
	वापस 0;
पूर्ण

अटल पूर्णांक ltc294x_get_voltage(स्थिर काष्ठा ltc294x_info *info, पूर्णांक *val)
अणु
	पूर्णांक ret;
	u8 datar[2];
	u32 value;

	ret = ltc294x_पढ़ो_regs(info->client,
		LTC294X_REG_VOLTAGE_MSB, &datar[0], 2);
	value = (datar[0] << 8) | datar[1];
	चयन (info->id) अणु
	हाल LTC2943_ID:
		value *= 23600 * 2;
		value /= 0xFFFF;
		value *= 1000 / 2;
		अवरोध;
	हाल LTC2944_ID:
		value *= 70800 / 5*4;
		value /= 0xFFFF;
		value *= 1000 * 5/4;
		अवरोध;
	शेष:
		value *= 6000 * 10;
		value /= 0xFFFF;
		value *= 1000 / 10;
		अवरोध;
	पूर्ण
	*val = value;
	वापस ret;
पूर्ण

अटल पूर्णांक ltc294x_get_current(स्थिर काष्ठा ltc294x_info *info, पूर्णांक *val)
अणु
	पूर्णांक ret;
	u8 datar[2];
	s32 value;

	ret = ltc294x_पढ़ो_regs(info->client,
		LTC2943_REG_CURRENT_MSB, &datar[0], 2);
	value = (datar[0] << 8) | datar[1];
	value -= 0x7FFF;
	अगर (info->id == LTC2944_ID)
		value *= 64000;
	अन्यथा
		value *= 60000;
	/* Value is in range -32k..+32k, r_sense is usually 10..50 mOhm,
	 * the क्रमmula below keeps everything in s32 range जबतक preserving
	 * enough digits */
	*val = 1000 * (value / (info->r_sense * 0x7FFF)); /* in uA */
	वापस ret;
पूर्ण

अटल पूर्णांक ltc294x_get_temperature(स्थिर काष्ठा ltc294x_info *info, पूर्णांक *val)
अणु
	क्रमागत ltc294x_reg reg;
	पूर्णांक ret;
	u8 datar[2];
	u32 value;

	अगर (info->id == LTC2942_ID) अणु
		reg = LTC2942_REG_TEMPERATURE_MSB;
		value = 6000;	/* Full-scale is 600 Kelvin */
	पूर्ण अन्यथा अणु
		reg = LTC2943_REG_TEMPERATURE_MSB;
		value = 5100;	/* Full-scale is 510 Kelvin */
	पूर्ण
	ret = ltc294x_पढ़ो_regs(info->client, reg, &datar[0], 2);
	value *= (datar[0] << 8) | datar[1];
	/* Convert to tenths of degree Celsius */
	*val = value / 0xFFFF - 2722;
	वापस ret;
पूर्ण

अटल पूर्णांक ltc294x_get_property(काष्ठा घातer_supply *psy,
				क्रमागत घातer_supply_property prop,
				जोड़ घातer_supply_propval *val)
अणु
	काष्ठा ltc294x_info *info = घातer_supply_get_drvdata(psy);

	चयन (prop) अणु
	हाल POWER_SUPPLY_PROP_CHARGE_FULL:
		वापस ltc294x_get_अक्षरge(info, LTC294X_REG_CHARGE_THR_HIGH_MSB,
						&val->पूर्णांकval);
	हाल POWER_SUPPLY_PROP_CHARGE_EMPTY:
		वापस ltc294x_get_अक्षरge(info, LTC294X_REG_CHARGE_THR_LOW_MSB,
						&val->पूर्णांकval);
	हाल POWER_SUPPLY_PROP_CHARGE_NOW:
		वापस ltc294x_get_अक्षरge(info, LTC294X_REG_ACC_CHARGE_MSB,
						&val->पूर्णांकval);
	हाल POWER_SUPPLY_PROP_CHARGE_COUNTER:
		वापस ltc294x_get_अक्षरge_counter(info, &val->पूर्णांकval);
	हाल POWER_SUPPLY_PROP_VOLTAGE_NOW:
		वापस ltc294x_get_voltage(info, &val->पूर्णांकval);
	हाल POWER_SUPPLY_PROP_CURRENT_NOW:
		वापस ltc294x_get_current(info, &val->पूर्णांकval);
	हाल POWER_SUPPLY_PROP_TEMP:
		वापस ltc294x_get_temperature(info, &val->पूर्णांकval);
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक ltc294x_set_property(काष्ठा घातer_supply *psy,
	क्रमागत घातer_supply_property psp,
	स्थिर जोड़ घातer_supply_propval *val)
अणु
	काष्ठा ltc294x_info *info = घातer_supply_get_drvdata(psy);

	चयन (psp) अणु
	हाल POWER_SUPPLY_PROP_CHARGE_FULL:
		वापस ltc294x_set_अक्षरge_thr(info,
			LTC294X_REG_CHARGE_THR_HIGH_MSB, val->पूर्णांकval);
	हाल POWER_SUPPLY_PROP_CHARGE_EMPTY:
		वापस ltc294x_set_अक्षरge_thr(info,
			LTC294X_REG_CHARGE_THR_LOW_MSB, val->पूर्णांकval);
	हाल POWER_SUPPLY_PROP_CHARGE_NOW:
		वापस ltc294x_set_अक्षरge_now(info, val->पूर्णांकval);
	शेष:
		वापस -EPERM;
	पूर्ण
पूर्ण

अटल पूर्णांक ltc294x_property_is_ग_लिखोable(
	काष्ठा घातer_supply *psy, क्रमागत घातer_supply_property psp)
अणु
	चयन (psp) अणु
	हाल POWER_SUPPLY_PROP_CHARGE_FULL:
	हाल POWER_SUPPLY_PROP_CHARGE_EMPTY:
	हाल POWER_SUPPLY_PROP_CHARGE_NOW:
		वापस 1;
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

अटल व्योम ltc294x_update(काष्ठा ltc294x_info *info)
अणु
	पूर्णांक अक्षरge = ltc294x_पढ़ो_अक्षरge_रेजिस्टर(info, LTC294X_REG_ACC_CHARGE_MSB);

	अगर (अक्षरge != info->अक्षरge) अणु
		info->अक्षरge = अक्षरge;
		घातer_supply_changed(info->supply);
	पूर्ण
पूर्ण

अटल व्योम ltc294x_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ltc294x_info *info;

	info = container_of(work, काष्ठा ltc294x_info, work.work);
	ltc294x_update(info);
	schedule_delayed_work(&info->work, LTC294X_WORK_DELAY * HZ);
पूर्ण

अटल क्रमागत घातer_supply_property ltc294x_properties[] = अणु
	POWER_SUPPLY_PROP_CHARGE_COUNTER,
	POWER_SUPPLY_PROP_CHARGE_FULL,
	POWER_SUPPLY_PROP_CHARGE_EMPTY,
	POWER_SUPPLY_PROP_CHARGE_NOW,
	POWER_SUPPLY_PROP_VOLTAGE_NOW,
	POWER_SUPPLY_PROP_TEMP,
	POWER_SUPPLY_PROP_CURRENT_NOW,
पूर्ण;

अटल पूर्णांक ltc294x_i2c_probe(काष्ठा i2c_client *client,
	स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा घातer_supply_config psy_cfg = अणुपूर्ण;
	काष्ठा ltc294x_info *info;
	काष्ठा device_node *np;
	पूर्णांक ret;
	u32 prescaler_exp;
	s32 r_sense;
	u8 status;

	info = devm_kzalloc(&client->dev, माप(*info), GFP_KERNEL);
	अगर (info == शून्य)
		वापस -ENOMEM;

	i2c_set_clientdata(client, info);

	np = of_node_get(client->dev.of_node);

	info->id = (क्रमागत ltc294x_id) (uपूर्णांकptr_t) of_device_get_match_data(
							&client->dev);
	info->supply_desc.name = np->name;

	/* r_sense can be negative, when sense+ is connected to the battery
	 * instead of the sense-. This results in reversed measurements. */
	ret = of_property_पढ़ो_u32(np, "lltc,resistor-sense", &r_sense);
	अगर (ret < 0) अणु
		dev_err(&client->dev,
			"Could not find lltc,resistor-sense in devicetree\n");
		वापस ret;
	पूर्ण
	info->r_sense = r_sense;

	ret = of_property_पढ़ो_u32(np, "lltc,prescaler-exponent",
		&prescaler_exp);
	अगर (ret < 0) अणु
		dev_warn(&client->dev,
			"lltc,prescaler-exponent not in devicetree\n");
		prescaler_exp = LTC2941_MAX_PRESCALER_EXP;
	पूर्ण

	अगर (info->id == LTC2943_ID) अणु
		अगर (prescaler_exp > LTC2943_MAX_PRESCALER_EXP)
			prescaler_exp = LTC2943_MAX_PRESCALER_EXP;
		info->Qlsb = ((340 * 50000) / r_sense) /
				(4096 / (1 << (2*prescaler_exp)));
	पूर्ण अन्यथा अणु
		अगर (prescaler_exp > LTC2941_MAX_PRESCALER_EXP)
			prescaler_exp = LTC2941_MAX_PRESCALER_EXP;
		info->Qlsb = ((85 * 50000) / r_sense) /
				(128 / (1 << prescaler_exp));
	पूर्ण

	/* Read status रेजिस्टर to check क्रम LTC2942 */
	अगर (info->id == LTC2941_ID || info->id == LTC2942_ID) अणु
		ret = ltc294x_पढ़ो_regs(client, LTC294X_REG_STATUS, &status, 1);
		अगर (ret < 0) अणु
			dev_err(&client->dev,
				"Could not read status register\n");
			वापस ret;
		पूर्ण
		अगर (status & LTC2941_REG_STATUS_CHIP_ID)
			info->id = LTC2941_ID;
		अन्यथा
			info->id = LTC2942_ID;
	पूर्ण

	info->client = client;
	info->supply_desc.type = POWER_SUPPLY_TYPE_BATTERY;
	info->supply_desc.properties = ltc294x_properties;
	चयन (info->id) अणु
	हाल LTC2944_ID:
	हाल LTC2943_ID:
		info->supply_desc.num_properties =
			ARRAY_SIZE(ltc294x_properties);
		अवरोध;
	हाल LTC2942_ID:
		info->supply_desc.num_properties =
			ARRAY_SIZE(ltc294x_properties) - 1;
		अवरोध;
	हाल LTC2941_ID:
	शेष:
		info->supply_desc.num_properties =
			ARRAY_SIZE(ltc294x_properties) - 3;
		अवरोध;
	पूर्ण
	info->supply_desc.get_property = ltc294x_get_property;
	info->supply_desc.set_property = ltc294x_set_property;
	info->supply_desc.property_is_ग_लिखोable = ltc294x_property_is_ग_लिखोable;
	info->supply_desc.बाह्यal_घातer_changed	= शून्य;

	psy_cfg.drv_data = info;

	ret = devm_delayed_work_स्वतःcancel(&client->dev, &info->work,
					   ltc294x_work);
	अगर (ret)
		वापस ret;

	ret = ltc294x_reset(info, prescaler_exp);
	अगर (ret < 0) अणु
		dev_err(&client->dev, "Communication with chip failed\n");
		वापस ret;
	पूर्ण

	info->supply = devm_घातer_supply_रेजिस्टर(&client->dev,
						  &info->supply_desc, &psy_cfg);
	अगर (IS_ERR(info->supply)) अणु
		dev_err(&client->dev, "failed to register ltc2941\n");
		वापस PTR_ERR(info->supply);
	पूर्ण अन्यथा अणु
		schedule_delayed_work(&info->work, LTC294X_WORK_DELAY * HZ);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम ltc294x_i2c_shutकरोwn(काष्ठा i2c_client *client)
अणु
	काष्ठा ltc294x_info *info = i2c_get_clientdata(client);
	पूर्णांक ret;
	u8 value;
	u8 control;

	/* The LTC2941 करोes not need any special handling */
	अगर (info->id == LTC2941_ID)
		वापस;

	/* Read control रेजिस्टर */
	ret = ltc294x_पढ़ो_regs(info->client, LTC294X_REG_CONTROL, &value, 1);
	अगर (ret < 0)
		वापस;

	/* Disable continuous ADC conversion as this drains the battery */
	control = LTC294X_REG_CONTROL_ADC_DISABLE(value);
	अगर (control != value)
		ltc294x_ग_लिखो_regs(info->client, LTC294X_REG_CONTROL,
			&control, 1);
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP

अटल पूर्णांक ltc294x_suspend(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा ltc294x_info *info = i2c_get_clientdata(client);

	cancel_delayed_work(&info->work);
	वापस 0;
पूर्ण

अटल पूर्णांक ltc294x_resume(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा ltc294x_info *info = i2c_get_clientdata(client);

	schedule_delayed_work(&info->work, LTC294X_WORK_DELAY * HZ);
	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(ltc294x_pm_ops, ltc294x_suspend, ltc294x_resume);
#घोषणा LTC294X_PM_OPS (&ltc294x_pm_ops)

#अन्यथा
#घोषणा LTC294X_PM_OPS शून्य
#पूर्ण_अगर /* CONFIG_PM_SLEEP */


अटल स्थिर काष्ठा i2c_device_id ltc294x_i2c_id[] = अणु
	अणु "ltc2941", LTC2941_ID, पूर्ण,
	अणु "ltc2942", LTC2942_ID, पूर्ण,
	अणु "ltc2943", LTC2943_ID, पूर्ण,
	अणु "ltc2944", LTC2944_ID, पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(i2c, ltc294x_i2c_id);

अटल स्थिर काष्ठा of_device_id ltc294x_i2c_of_match[] = अणु
	अणु
		.compatible = "lltc,ltc2941",
		.data = (व्योम *)LTC2941_ID,
	पूर्ण,
	अणु
		.compatible = "lltc,ltc2942",
		.data = (व्योम *)LTC2942_ID,
	पूर्ण,
	अणु
		.compatible = "lltc,ltc2943",
		.data = (व्योम *)LTC2943_ID,
	पूर्ण,
	अणु
		.compatible = "lltc,ltc2944",
		.data = (व्योम *)LTC2944_ID,
	पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, ltc294x_i2c_of_match);

अटल काष्ठा i2c_driver ltc294x_driver = अणु
	.driver = अणु
		.name	= "LTC2941",
		.of_match_table = ltc294x_i2c_of_match,
		.pm	= LTC294X_PM_OPS,
	पूर्ण,
	.probe		= ltc294x_i2c_probe,
	.shutकरोwn	= ltc294x_i2c_shutकरोwn,
	.id_table	= ltc294x_i2c_id,
पूर्ण;
module_i2c_driver(ltc294x_driver);

MODULE_AUTHOR("Auryn Verwegen, Topic Embedded Systems");
MODULE_AUTHOR("Mike Looijmans, Topic Embedded Products");
MODULE_DESCRIPTION("LTC2941/LTC2942/LTC2943/LTC2944 Battery Gas Gauge IC driver");
MODULE_LICENSE("GPL");
