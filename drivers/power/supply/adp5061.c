<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * ADP5061 I2C Programmable Linear Battery Charger
 *
 * Copyright 2018 Analog Devices Inc.
 */

#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/i2c.h>
#समावेश <linux/delay.h>
#समावेश <linux/pm.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/घातer_supply.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/of.h>
#समावेश <linux/regmap.h>

/* ADP5061 रेजिस्टरs definition */
#घोषणा ADP5061_ID			0x00
#घोषणा ADP5061_REV			0x01
#घोषणा ADP5061_VINX_SET		0x02
#घोषणा ADP5061_TERM_SET		0x03
#घोषणा ADP5061_CHG_CURR		0x04
#घोषणा ADP5061_VOLTAGE_TH		0x05
#घोषणा ADP5061_TIMER_SET		0x06
#घोषणा ADP5061_FUNC_SET_1		0x07
#घोषणा ADP5061_FUNC_SET_2		0x08
#घोषणा ADP5061_INT_EN			0x09
#घोषणा ADP5061_INT_ACT			0x0A
#घोषणा ADP5061_CHG_STATUS_1		0x0B
#घोषणा ADP5061_CHG_STATUS_2		0x0C
#घोषणा ADP5061_FAULT			0x0D
#घोषणा ADP5061_BATTERY_SHORT		0x10
#घोषणा ADP5061_IEND			0x11

/* ADP5061_VINX_SET */
#घोषणा ADP5061_VINX_SET_ILIM_MSK		GENMASK(3, 0)
#घोषणा ADP5061_VINX_SET_ILIM_MODE(x)		(((x) & 0x0F) << 0)

/* ADP5061_TERM_SET */
#घोषणा ADP5061_TERM_SET_VTRM_MSK		GENMASK(7, 2)
#घोषणा ADP5061_TERM_SET_VTRM_MODE(x)		(((x) & 0x3F) << 2)
#घोषणा ADP5061_TERM_SET_CHG_VLIM_MSK		GENMASK(1, 0)
#घोषणा ADP5061_TERM_SET_CHG_VLIM_MODE(x)	(((x) & 0x03) << 0)

/* ADP5061_CHG_CURR */
#घोषणा ADP5061_CHG_CURR_ICHG_MSK		GENMASK(6, 2)
#घोषणा ADP5061_CHG_CURR_ICHG_MODE(x)		(((x) & 0x1F) << 2)
#घोषणा ADP5061_CHG_CURR_ITRK_DEAD_MSK		GENMASK(1, 0)
#घोषणा ADP5061_CHG_CURR_ITRK_DEAD_MODE(x)	(((x) & 0x03) << 0)

/* ADP5061_VOLTAGE_TH */
#घोषणा ADP5061_VOLTAGE_TH_DIS_RCH_MSK		BIT(7)
#घोषणा ADP5061_VOLTAGE_TH_DIS_RCH_MODE(x)	(((x) & 0x01) << 7)
#घोषणा ADP5061_VOLTAGE_TH_VRCH_MSK		GENMASK(6, 5)
#घोषणा ADP5061_VOLTAGE_TH_VRCH_MODE(x)		(((x) & 0x03) << 5)
#घोषणा ADP5061_VOLTAGE_TH_VTRK_DEAD_MSK	GENMASK(4, 3)
#घोषणा ADP5061_VOLTAGE_TH_VTRK_DEAD_MODE(x)	(((x) & 0x03) << 3)
#घोषणा ADP5061_VOLTAGE_TH_VWEAK_MSK		GENMASK(2, 0)
#घोषणा ADP5061_VOLTAGE_TH_VWEAK_MODE(x)	(((x) & 0x07) << 0)

/* ADP5061_CHG_STATUS_1 */
#घोषणा ADP5061_CHG_STATUS_1_VIN_OV(x)		(((x) >> 7) & 0x1)
#घोषणा ADP5061_CHG_STATUS_1_VIN_OK(x)		(((x) >> 6) & 0x1)
#घोषणा ADP5061_CHG_STATUS_1_VIN_ILIM(x)	(((x) >> 5) & 0x1)
#घोषणा ADP5061_CHG_STATUS_1_THERM_LIM(x)	(((x) >> 4) & 0x1)
#घोषणा ADP5061_CHG_STATUS_1_CHDONE(x)		(((x) >> 3) & 0x1)
#घोषणा ADP5061_CHG_STATUS_1_CHG_STATUS(x)	(((x) >> 0) & 0x7)

/* ADP5061_CHG_STATUS_2 */
#घोषणा ADP5061_CHG_STATUS_2_THR_STATUS(x)	(((x) >> 5) & 0x7)
#घोषणा ADP5061_CHG_STATUS_2_RCH_LIM_INFO(x)	(((x) >> 3) & 0x1)
#घोषणा ADP5061_CHG_STATUS_2_BAT_STATUS(x)	(((x) >> 0) & 0x7)

/* ADP5061_IEND */
#घोषणा ADP5061_IEND_IEND_MSK			GENMASK(7, 5)
#घोषणा ADP5061_IEND_IEND_MODE(x)		(((x) & 0x07) << 5)

#घोषणा ADP5061_NO_BATTERY	0x01
#घोषणा ADP5061_ICHG_MAX	1300 // mA

क्रमागत adp5061_chg_status अणु
	ADP5061_CHG_OFF,
	ADP5061_CHG_TRICKLE,
	ADP5061_CHG_FAST_CC,
	ADP5061_CHG_FAST_CV,
	ADP5061_CHG_COMPLETE,
	ADP5061_CHG_LDO_MODE,
	ADP5061_CHG_TIMER_EXP,
	ADP5061_CHG_BAT_DET,
पूर्ण;

अटल स्थिर पूर्णांक adp5061_chg_type[4] = अणु
	[ADP5061_CHG_OFF] = POWER_SUPPLY_CHARGE_TYPE_NONE,
	[ADP5061_CHG_TRICKLE] = POWER_SUPPLY_CHARGE_TYPE_TRICKLE,
	[ADP5061_CHG_FAST_CC] = POWER_SUPPLY_CHARGE_TYPE_FAST,
	[ADP5061_CHG_FAST_CV] = POWER_SUPPLY_CHARGE_TYPE_FAST,
पूर्ण;

अटल स्थिर पूर्णांक adp5061_vweak_th[8] = अणु
	2700, 2800, 2900, 3000, 3100, 3200, 3300, 3400,
पूर्ण;

अटल स्थिर पूर्णांक adp5061_prechg_current[4] = अणु
	5, 10, 20, 80,
पूर्ण;

अटल स्थिर पूर्णांक adp5061_vmin[4] = अणु
	2000, 2500, 2600, 2900,
पूर्ण;

अटल स्थिर पूर्णांक adp5061_स्थिर_chg_vmax[4] = अणु
	3200, 3400, 3700, 3800,
पूर्ण;

अटल स्थिर पूर्णांक adp5061_स्थिर_ichg[24] = अणु
	50, 100, 150, 200, 250, 300, 350, 400, 450, 500, 550, 600, 650,
	700, 750, 800, 850, 900, 950, 1000, 1050, 1100, 1200, 1300,
पूर्ण;

अटल स्थिर पूर्णांक adp5061_vmax[36] = अणु
	3800, 3820, 3840, 3860, 3880, 3900, 3920, 3940, 3960, 3980,
	4000, 4020, 4040, 4060, 4080, 4100, 4120, 4140, 4160, 4180,
	4200, 4220, 4240, 4260, 4280, 4300, 4320, 4340, 4360, 4380,
	4400, 4420, 4440, 4460, 4480, 4500,
पूर्ण;

अटल स्थिर पूर्णांक adp5061_in_current_lim[16] = अणु
	100, 150, 200, 250, 300, 400, 500, 600, 700,
	800, 900, 1000, 1200, 1500, 1800, 2100,
पूर्ण;

अटल स्थिर पूर्णांक adp5061_iend[8] = अणु
	12500, 32500, 52500, 72500, 92500, 117500, 142500, 170000,
पूर्ण;

काष्ठा adp5061_state अणु
	काष्ठा i2c_client		*client;
	काष्ठा regmap			*regmap;
	काष्ठा घातer_supply		*psy;
पूर्ण;

अटल पूर्णांक adp5061_get_array_index(स्थिर पूर्णांक *array, u8 size, पूर्णांक val)
अणु
	पूर्णांक i;

	क्रम (i = 1; i < size; i++) अणु
		अगर (val < array[i])
			अवरोध;
	पूर्ण

	वापस i-1;
पूर्ण

अटल पूर्णांक adp5061_get_status(काष्ठा adp5061_state *st,
			      u8 *status1, u8 *status2)
अणु
	u8 buf[2];
	पूर्णांक ret;

	/* CHG_STATUS1 and CHG_STATUS2 are adjacent regs */
	ret = regmap_bulk_पढ़ो(st->regmap, ADP5061_CHG_STATUS_1,
			       &buf[0], 2);
	अगर (ret < 0)
		वापस ret;

	*status1 = buf[0];
	*status2 = buf[1];

	वापस ret;
पूर्ण

अटल पूर्णांक adp5061_get_input_current_limit(काष्ठा adp5061_state *st,
		जोड़ घातer_supply_propval *val)
अणु
	अचिन्हित पूर्णांक regval;
	पूर्णांक mode, ret;

	ret = regmap_पढ़ो(st->regmap, ADP5061_VINX_SET, &regval);
	अगर (ret < 0)
		वापस ret;

	mode = ADP5061_VINX_SET_ILIM_MODE(regval);
	val->पूर्णांकval = adp5061_in_current_lim[mode] * 1000;

	वापस ret;
पूर्ण

अटल पूर्णांक adp5061_set_input_current_limit(काष्ठा adp5061_state *st, पूर्णांक val)
अणु
	पूर्णांक index;

	/* Convert from uA to mA */
	val /= 1000;
	index = adp5061_get_array_index(adp5061_in_current_lim,
					ARRAY_SIZE(adp5061_in_current_lim),
					val);
	अगर (index < 0)
		वापस index;

	वापस regmap_update_bits(st->regmap, ADP5061_VINX_SET,
				  ADP5061_VINX_SET_ILIM_MSK,
				  ADP5061_VINX_SET_ILIM_MODE(index));
पूर्ण

अटल पूर्णांक adp5061_set_min_voltage(काष्ठा adp5061_state *st, पूर्णांक val)
अणु
	पूर्णांक index;

	/* Convert from uV to mV */
	val /= 1000;
	index = adp5061_get_array_index(adp5061_vmin,
					ARRAY_SIZE(adp5061_vmin),
					val);
	अगर (index < 0)
		वापस index;

	वापस regmap_update_bits(st->regmap, ADP5061_VOLTAGE_TH,
				  ADP5061_VOLTAGE_TH_VTRK_DEAD_MSK,
				  ADP5061_VOLTAGE_TH_VTRK_DEAD_MODE(index));
पूर्ण

अटल पूर्णांक adp5061_get_min_voltage(काष्ठा adp5061_state *st,
				   जोड़ घातer_supply_propval *val)
अणु
	अचिन्हित पूर्णांक regval;
	पूर्णांक ret;

	ret = regmap_पढ़ो(st->regmap, ADP5061_VOLTAGE_TH, &regval);
	अगर (ret < 0)
		वापस ret;

	regval = ((regval & ADP5061_VOLTAGE_TH_VTRK_DEAD_MSK) >> 3);
	val->पूर्णांकval = adp5061_vmin[regval] * 1000;

	वापस ret;
पूर्ण

अटल पूर्णांक adp5061_get_chg_volt_lim(काष्ठा adp5061_state *st,
				    जोड़ घातer_supply_propval *val)
अणु
	अचिन्हित पूर्णांक regval;
	पूर्णांक mode, ret;

	ret = regmap_पढ़ो(st->regmap, ADP5061_TERM_SET, &regval);
	अगर (ret < 0)
		वापस ret;

	mode = ADP5061_TERM_SET_CHG_VLIM_MODE(regval);
	val->पूर्णांकval = adp5061_स्थिर_chg_vmax[mode] * 1000;

	वापस ret;
पूर्ण

अटल पूर्णांक adp5061_get_max_voltage(काष्ठा adp5061_state *st,
				   जोड़ घातer_supply_propval *val)
अणु
	अचिन्हित पूर्णांक regval;
	पूर्णांक ret;

	ret = regmap_पढ़ो(st->regmap, ADP5061_TERM_SET, &regval);
	अगर (ret < 0)
		वापस ret;

	regval = ((regval & ADP5061_TERM_SET_VTRM_MSK) >> 2) - 0x0F;
	अगर (regval >= ARRAY_SIZE(adp5061_vmax))
		regval = ARRAY_SIZE(adp5061_vmax) - 1;

	val->पूर्णांकval = adp5061_vmax[regval] * 1000;

	वापस ret;
पूर्ण

अटल पूर्णांक adp5061_set_max_voltage(काष्ठा adp5061_state *st, पूर्णांक val)
अणु
	पूर्णांक vmax_index;

	/* Convert from uV to mV */
	val /= 1000;
	अगर (val > 4500)
		val = 4500;

	vmax_index = adp5061_get_array_index(adp5061_vmax,
					     ARRAY_SIZE(adp5061_vmax), val);
	अगर (vmax_index < 0)
		वापस vmax_index;

	vmax_index += 0x0F;

	वापस regmap_update_bits(st->regmap, ADP5061_TERM_SET,
				  ADP5061_TERM_SET_VTRM_MSK,
				  ADP5061_TERM_SET_VTRM_MODE(vmax_index));
पूर्ण

अटल पूर्णांक adp5061_set_स्थिर_chg_vmax(काष्ठा adp5061_state *st, पूर्णांक val)
अणु
	पूर्णांक index;

	/* Convert from uV to mV */
	val /= 1000;
	index = adp5061_get_array_index(adp5061_स्थिर_chg_vmax,
					ARRAY_SIZE(adp5061_स्थिर_chg_vmax),
					val);
	अगर (index < 0)
		वापस index;

	वापस regmap_update_bits(st->regmap, ADP5061_TERM_SET,
				  ADP5061_TERM_SET_CHG_VLIM_MSK,
				  ADP5061_TERM_SET_CHG_VLIM_MODE(index));
पूर्ण

अटल पूर्णांक adp5061_set_स्थिर_chg_current(काष्ठा adp5061_state *st, पूर्णांक val)
अणु

	पूर्णांक index;

	/* Convert from uA to mA */
	val /= 1000;
	अगर (val > ADP5061_ICHG_MAX)
		val = ADP5061_ICHG_MAX;

	index = adp5061_get_array_index(adp5061_स्थिर_ichg,
					ARRAY_SIZE(adp5061_स्थिर_ichg),
					val);
	अगर (index < 0)
		वापस index;

	वापस regmap_update_bits(st->regmap, ADP5061_CHG_CURR,
				  ADP5061_CHG_CURR_ICHG_MSK,
				  ADP5061_CHG_CURR_ICHG_MODE(index));
पूर्ण

अटल पूर्णांक adp5061_get_स्थिर_chg_current(काष्ठा adp5061_state *st,
		जोड़ घातer_supply_propval *val)
अणु
	अचिन्हित पूर्णांक regval;
	पूर्णांक ret;

	ret = regmap_पढ़ो(st->regmap, ADP5061_CHG_CURR, &regval);
	अगर (ret < 0)
		वापस ret;

	regval = ((regval & ADP5061_CHG_CURR_ICHG_MSK) >> 2);
	अगर (regval >= ARRAY_SIZE(adp5061_स्थिर_ichg))
		regval = ARRAY_SIZE(adp5061_स्थिर_ichg) - 1;

	val->पूर्णांकval = adp5061_स्थिर_ichg[regval] * 1000;

	वापस ret;
पूर्ण

अटल पूर्णांक adp5061_get_prechg_current(काष्ठा adp5061_state *st,
				      जोड़ घातer_supply_propval *val)
अणु
	अचिन्हित पूर्णांक regval;
	पूर्णांक ret;

	ret = regmap_पढ़ो(st->regmap, ADP5061_CHG_CURR, &regval);
	अगर (ret < 0)
		वापस ret;

	regval &= ADP5061_CHG_CURR_ITRK_DEAD_MSK;
	val->पूर्णांकval = adp5061_prechg_current[regval] * 1000;

	वापस ret;
पूर्ण

अटल पूर्णांक adp5061_set_prechg_current(काष्ठा adp5061_state *st, पूर्णांक val)
अणु
	पूर्णांक index;

	/* Convert from uA to mA */
	val /= 1000;
	index = adp5061_get_array_index(adp5061_prechg_current,
					ARRAY_SIZE(adp5061_prechg_current),
					val);
	अगर (index < 0)
		वापस index;

	वापस regmap_update_bits(st->regmap, ADP5061_CHG_CURR,
				  ADP5061_CHG_CURR_ITRK_DEAD_MSK,
				  ADP5061_CHG_CURR_ITRK_DEAD_MODE(index));
पूर्ण

अटल पूर्णांक adp5061_get_vweak_th(काष्ठा adp5061_state *st,
				जोड़ घातer_supply_propval *val)
अणु
	अचिन्हित पूर्णांक regval;
	पूर्णांक ret;

	ret = regmap_पढ़ो(st->regmap, ADP5061_VOLTAGE_TH, &regval);
	अगर (ret < 0)
		वापस ret;

	regval &= ADP5061_VOLTAGE_TH_VWEAK_MSK;
	val->पूर्णांकval = adp5061_vweak_th[regval] * 1000;

	वापस ret;
पूर्ण

अटल पूर्णांक adp5061_set_vweak_th(काष्ठा adp5061_state *st, पूर्णांक val)
अणु
	पूर्णांक index;

	/* Convert from uV to mV */
	val /= 1000;
	index = adp5061_get_array_index(adp5061_vweak_th,
					ARRAY_SIZE(adp5061_vweak_th),
					val);
	अगर (index < 0)
		वापस index;

	वापस regmap_update_bits(st->regmap, ADP5061_VOLTAGE_TH,
				  ADP5061_VOLTAGE_TH_VWEAK_MSK,
				  ADP5061_VOLTAGE_TH_VWEAK_MODE(index));
पूर्ण

अटल पूर्णांक adp5061_get_chg_type(काष्ठा adp5061_state *st,
				जोड़ घातer_supply_propval *val)
अणु
	u8 status1, status2;
	पूर्णांक chg_type, ret;

	ret = adp5061_get_status(st, &status1, &status2);
	अगर (ret < 0)
		वापस ret;

	chg_type = adp5061_chg_type[ADP5061_CHG_STATUS_1_CHG_STATUS(status1)];
	अगर (chg_type > ADP5061_CHG_FAST_CV)
		val->पूर्णांकval = POWER_SUPPLY_STATUS_UNKNOWN;
	अन्यथा
		val->पूर्णांकval = chg_type;

	वापस ret;
पूर्ण

अटल पूर्णांक adp5061_get_अक्षरger_status(काष्ठा adp5061_state *st,
				      जोड़ घातer_supply_propval *val)
अणु
	u8 status1, status2;
	पूर्णांक ret;

	ret = adp5061_get_status(st, &status1, &status2);
	अगर (ret < 0)
		वापस ret;

	चयन (ADP5061_CHG_STATUS_1_CHG_STATUS(status1)) अणु
	हाल ADP5061_CHG_OFF:
		val->पूर्णांकval = POWER_SUPPLY_STATUS_NOT_CHARGING;
		अवरोध;
	हाल ADP5061_CHG_TRICKLE:
	हाल ADP5061_CHG_FAST_CC:
	हाल ADP5061_CHG_FAST_CV:
		val->पूर्णांकval = POWER_SUPPLY_STATUS_CHARGING;
		अवरोध;
	हाल ADP5061_CHG_COMPLETE:
		val->पूर्णांकval = POWER_SUPPLY_STATUS_FULL;
		अवरोध;
	हाल ADP5061_CHG_TIMER_EXP:
		/* The battery must be disअक्षरging अगर there is a अक्षरge fault */
		val->पूर्णांकval = POWER_SUPPLY_STATUS_DISCHARGING;
		अवरोध;
	शेष:
		val->पूर्णांकval = POWER_SUPPLY_STATUS_UNKNOWN;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक adp5061_get_battery_status(काष्ठा adp5061_state *st,
				      जोड़ घातer_supply_propval *val)
अणु
	u8 status1, status2;
	पूर्णांक ret;

	ret = adp5061_get_status(st, &status1, &status2);
	अगर (ret < 0)
		वापस ret;

	चयन (ADP5061_CHG_STATUS_2_BAT_STATUS(status2)) अणु
	हाल 0x0: /* Battery monitor off */
	हाल 0x1: /* No battery */
		val->पूर्णांकval = POWER_SUPPLY_CAPACITY_LEVEL_UNKNOWN;
		अवरोध;
	हाल 0x2: /* VBAT < VTRK */
		val->पूर्णांकval = POWER_SUPPLY_CAPACITY_LEVEL_CRITICAL;
		अवरोध;
	हाल 0x3: /* VTRK < VBAT_SNS < VWEAK */
		val->पूर्णांकval = POWER_SUPPLY_CAPACITY_LEVEL_LOW;
		अवरोध;
	हाल 0x4: /* VBAT_SNS > VWEAK */
		val->पूर्णांकval = POWER_SUPPLY_CAPACITY_LEVEL_NORMAL;
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक adp5061_get_termination_current(काष्ठा adp5061_state *st,
					   जोड़ घातer_supply_propval *val)
अणु
	अचिन्हित पूर्णांक regval;
	पूर्णांक ret;

	ret = regmap_पढ़ो(st->regmap, ADP5061_IEND, &regval);
	अगर (ret < 0)
		वापस ret;

	regval = (regval & ADP5061_IEND_IEND_MSK) >> 5;
	val->पूर्णांकval = adp5061_iend[regval];

	वापस ret;
पूर्ण

अटल पूर्णांक adp5061_set_termination_current(काष्ठा adp5061_state *st, पूर्णांक val)
अणु
	पूर्णांक index;

	index = adp5061_get_array_index(adp5061_iend,
					ARRAY_SIZE(adp5061_iend),
					val);
	अगर (index < 0)
		वापस index;

	वापस regmap_update_bits(st->regmap, ADP5061_IEND,
				  ADP5061_IEND_IEND_MSK,
				  ADP5061_IEND_IEND_MODE(index));
पूर्ण

अटल पूर्णांक adp5061_get_property(काष्ठा घातer_supply *psy,
				क्रमागत घातer_supply_property psp,
				जोड़ घातer_supply_propval *val)
अणु
	काष्ठा adp5061_state *st = घातer_supply_get_drvdata(psy);
	u8 status1, status2;
	पूर्णांक mode, ret;

	चयन (psp) अणु
	हाल POWER_SUPPLY_PROP_PRESENT:
		ret = adp5061_get_status(st, &status1, &status2);
		अगर (ret < 0)
			वापस ret;

		mode = ADP5061_CHG_STATUS_2_BAT_STATUS(status2);
		अगर (mode == ADP5061_NO_BATTERY)
			val->पूर्णांकval = 0;
		अन्यथा
			val->पूर्णांकval = 1;
		अवरोध;
	हाल POWER_SUPPLY_PROP_CHARGE_TYPE:
		वापस adp5061_get_chg_type(st, val);
	हाल POWER_SUPPLY_PROP_INPUT_CURRENT_LIMIT:
		/* This property is used to indicate the input current
		 * limit पूर्णांकo VINx (ILIM)
		 */
		वापस adp5061_get_input_current_limit(st, val);
	हाल POWER_SUPPLY_PROP_VOLTAGE_MAX:
		/* This property is used to indicate the termination
		 * voltage (VTRM)
		 */
		वापस adp5061_get_max_voltage(st, val);
	हाल POWER_SUPPLY_PROP_VOLTAGE_MIN:
		/*
		 * This property is used to indicate the trickle to fast
		 * अक्षरge threshold (VTRK_DEAD)
		 */
		वापस adp5061_get_min_voltage(st, val);
	हाल POWER_SUPPLY_PROP_CONSTANT_CHARGE_VOLTAGE_MAX:
		/* This property is used to indicate the अक्षरging
		 * voltage limit (CHG_VLIM)
		 */
		वापस adp5061_get_chg_volt_lim(st, val);
	हाल POWER_SUPPLY_PROP_CONSTANT_CHARGE_CURRENT:
		/*
		 * This property is used to indicate the value of the स्थिरant
		 * current अक्षरge (ICHG)
		 */
		वापस adp5061_get_स्थिर_chg_current(st, val);
	हाल POWER_SUPPLY_PROP_PRECHARGE_CURRENT:
		/*
		 * This property is used to indicate the value of the trickle
		 * and weak अक्षरge currents (ITRK_DEAD)
		 */
		वापस adp5061_get_prechg_current(st, val);
	हाल POWER_SUPPLY_PROP_VOLTAGE_AVG:
		/*
		 * This property is used to set the VWEAK threshold
		 * bellow this value, weak अक्षरge mode is entered
		 * above this value, fast अक्षरgerge mode is entered
		 */
		वापस adp5061_get_vweak_th(st, val);
	हाल POWER_SUPPLY_PROP_STATUS:
		/*
		 * Indicate the अक्षरger status in relation to घातer
		 * supply status property
		 */
		वापस adp5061_get_अक्षरger_status(st, val);
	हाल POWER_SUPPLY_PROP_CAPACITY_LEVEL:
		/*
		 * Indicate the battery status in relation to घातer
		 * supply capacity level property
		 */
		वापस adp5061_get_battery_status(st, val);
	हाल POWER_SUPPLY_PROP_CHARGE_TERM_CURRENT:
		/* Indicate the values of the termination current */
		वापस adp5061_get_termination_current(st, val);
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक adp5061_set_property(काष्ठा घातer_supply *psy,
				क्रमागत घातer_supply_property psp,
				स्थिर जोड़ घातer_supply_propval *val)
अणु
	काष्ठा adp5061_state *st = घातer_supply_get_drvdata(psy);

	चयन (psp) अणु
	हाल POWER_SUPPLY_PROP_INPUT_CURRENT_LIMIT:
		वापस adp5061_set_input_current_limit(st, val->पूर्णांकval);
	हाल POWER_SUPPLY_PROP_VOLTAGE_MAX:
		वापस adp5061_set_max_voltage(st, val->पूर्णांकval);
	हाल POWER_SUPPLY_PROP_VOLTAGE_MIN:
		वापस adp5061_set_min_voltage(st, val->पूर्णांकval);
	हाल POWER_SUPPLY_PROP_CONSTANT_CHARGE_VOLTAGE_MAX:
		वापस adp5061_set_स्थिर_chg_vmax(st, val->पूर्णांकval);
	हाल POWER_SUPPLY_PROP_CONSTANT_CHARGE_CURRENT:
		वापस adp5061_set_स्थिर_chg_current(st, val->पूर्णांकval);
	हाल POWER_SUPPLY_PROP_PRECHARGE_CURRENT:
		वापस adp5061_set_prechg_current(st, val->पूर्णांकval);
	हाल POWER_SUPPLY_PROP_VOLTAGE_AVG:
		वापस adp5061_set_vweak_th(st, val->पूर्णांकval);
	हाल POWER_SUPPLY_PROP_CHARGE_TERM_CURRENT:
		वापस adp5061_set_termination_current(st, val->पूर्णांकval);
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक adp5061_prop_ग_लिखोable(काष्ठा घातer_supply *psy,
				  क्रमागत घातer_supply_property psp)
अणु
	चयन (psp) अणु
	हाल POWER_SUPPLY_PROP_INPUT_CURRENT_LIMIT:
	हाल POWER_SUPPLY_PROP_VOLTAGE_MAX:
	हाल POWER_SUPPLY_PROP_VOLTAGE_MIN:
	हाल POWER_SUPPLY_PROP_CONSTANT_CHARGE_VOLTAGE_MAX:
	हाल POWER_SUPPLY_PROP_CONSTANT_CHARGE_CURRENT:
	हाल POWER_SUPPLY_PROP_PRECHARGE_CURRENT:
	हाल POWER_SUPPLY_PROP_VOLTAGE_AVG:
	हाल POWER_SUPPLY_PROP_CHARGE_TERM_CURRENT:
		वापस 1;
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

अटल क्रमागत घातer_supply_property adp5061_props[] = अणु
	POWER_SUPPLY_PROP_PRESENT,
	POWER_SUPPLY_PROP_CHARGE_TYPE,
	POWER_SUPPLY_PROP_INPUT_CURRENT_LIMIT,
	POWER_SUPPLY_PROP_VOLTAGE_MAX,
	POWER_SUPPLY_PROP_VOLTAGE_MIN,
	POWER_SUPPLY_PROP_CONSTANT_CHARGE_VOLTAGE_MAX,
	POWER_SUPPLY_PROP_CONSTANT_CHARGE_CURRENT,
	POWER_SUPPLY_PROP_PRECHARGE_CURRENT,
	POWER_SUPPLY_PROP_VOLTAGE_AVG,
	POWER_SUPPLY_PROP_STATUS,
	POWER_SUPPLY_PROP_CAPACITY_LEVEL,
	POWER_SUPPLY_PROP_CHARGE_TERM_CURRENT,
पूर्ण;

अटल स्थिर काष्ठा regmap_config adp5061_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 8,
पूर्ण;

अटल स्थिर काष्ठा घातer_supply_desc adp5061_desc = अणु
	.name			= "adp5061",
	.type			= POWER_SUPPLY_TYPE_USB,
	.get_property		= adp5061_get_property,
	.set_property		= adp5061_set_property,
	.property_is_ग_लिखोable	= adp5061_prop_ग_लिखोable,
	.properties		= adp5061_props,
	.num_properties		= ARRAY_SIZE(adp5061_props),
पूर्ण;

अटल पूर्णांक adp5061_probe(काष्ठा i2c_client *client,
			 स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा घातer_supply_config psy_cfg = अणुपूर्ण;
	काष्ठा adp5061_state *st;

	st = devm_kzalloc(&client->dev, माप(*st), GFP_KERNEL);
	अगर (!st)
		वापस -ENOMEM;

	st->client = client;
	st->regmap = devm_regmap_init_i2c(client,
					  &adp5061_regmap_config);
	अगर (IS_ERR(st->regmap)) अणु
		dev_err(&client->dev, "Failed to initialize register map\n");
		वापस -EINVAL;
	पूर्ण

	i2c_set_clientdata(client, st);
	psy_cfg.drv_data = st;

	st->psy = devm_घातer_supply_रेजिस्टर(&client->dev,
					     &adp5061_desc,
					     &psy_cfg);

	अगर (IS_ERR(st->psy)) अणु
		dev_err(&client->dev, "Failed to register power supply\n");
		वापस PTR_ERR(st->psy);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id adp5061_id[] = अणु
	अणु "adp5061", 0पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, adp5061_id);

अटल काष्ठा i2c_driver adp5061_driver = अणु
	.driver = अणु
		.name = KBUILD_MODNAME,
	पूर्ण,
	.probe = adp5061_probe,
	.id_table = adp5061_id,
पूर्ण;
module_i2c_driver(adp5061_driver);

MODULE_DESCRIPTION("Analog Devices adp5061 battery charger driver");
MODULE_AUTHOR("Stefan Popa <stefan.popa@analog.com>");
MODULE_LICENSE("GPL v2");
