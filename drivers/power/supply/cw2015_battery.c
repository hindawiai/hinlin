<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Fuel gauge driver क्रम CellWise 2013 / 2015
 *
 * Copyright (C) 2012, RockChip
 * Copyright (C) 2020, Tobias Schramm
 *
 * Authors: xuhuicong <xhc@rock-chips.com>
 * Authors: Tobias Schramm <t.schramm@manjaro.org>
 */

#समावेश <linux/bits.h>
#समावेश <linux/delay.h>
#समावेश <linux/i2c.h>
#समावेश <linux/gfp.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/घातer_supply.h>
#समावेश <linux/property.h>
#समावेश <linux/regmap.h>
#समावेश <linux/समय.स>
#समावेश <linux/workqueue.h>

#घोषणा CW2015_SIZE_BATINFO		64

#घोषणा CW2015_RESET_TRIES		5

#घोषणा CW2015_REG_VERSION		0x00
#घोषणा CW2015_REG_VCELL		0x02
#घोषणा CW2015_REG_SOC			0x04
#घोषणा CW2015_REG_RRT_ALERT		0x06
#घोषणा CW2015_REG_CONFIG		0x08
#घोषणा CW2015_REG_MODE			0x0A
#घोषणा CW2015_REG_BATINFO		0x10

#घोषणा CW2015_MODE_SLEEP_MASK		GENMASK(7, 6)
#घोषणा CW2015_MODE_SLEEP		(0x03 << 6)
#घोषणा CW2015_MODE_NORMAL		(0x00 << 6)
#घोषणा CW2015_MODE_QUICK_START		(0x03 << 4)
#घोषणा CW2015_MODE_RESTART		(0x0f << 0)

#घोषणा CW2015_CONFIG_UPDATE_FLG	(0x01 << 1)
#घोषणा CW2015_ATHD(x)			((x) << 3)
#घोषणा CW2015_MASK_ATHD		GENMASK(7, 3)
#घोषणा CW2015_MASK_SOC			GENMASK(12, 0)

/* reset gauge of no valid state of अक्षरge could be polled क्रम 40s */
#घोषणा CW2015_BAT_SOC_ERROR_MS		(40 * MSEC_PER_SEC)
/* reset gauge अगर state of अक्षरge stuck क्रम half an hour during अक्षरging */
#घोषणा CW2015_BAT_CHARGING_STUCK_MS	(1800 * MSEC_PER_SEC)

/* poll पूर्णांकerval from CellWise GPL Android driver example */
#घोषणा CW2015_DEFAULT_POLL_INTERVAL_MS		8000

#घोषणा CW2015_AVERAGING_SAMPLES		3

काष्ठा cw_battery अणु
	काष्ठा device *dev;
	काष्ठा workqueue_काष्ठा *battery_workqueue;
	काष्ठा delayed_work battery_delay_work;
	काष्ठा regmap *regmap;
	काष्ठा घातer_supply *rk_bat;
	काष्ठा घातer_supply_battery_info battery;
	u8 *bat_profile;

	bool अक्षरger_attached;
	bool battery_changed;

	पूर्णांक soc;
	पूर्णांक voltage_mv;
	पूर्णांक status;
	पूर्णांक समय_प्रकारo_empty;
	पूर्णांक अक्षरge_count;

	u32 poll_पूर्णांकerval_ms;
	u8 alert_level;

	अचिन्हित पूर्णांक पढ़ो_errors;
	अचिन्हित पूर्णांक अक्षरge_stuck_cnt;
पूर्ण;

अटल पूर्णांक cw_पढ़ो_word(काष्ठा cw_battery *cw_bat, u8 reg, u16 *val)
अणु
	__be16 value;
	पूर्णांक ret;

	ret = regmap_bulk_पढ़ो(cw_bat->regmap, reg, &value, माप(value));
	अगर (ret)
		वापस ret;

	*val = be16_to_cpu(value);
	वापस 0;
पूर्ण

अटल पूर्णांक cw_update_profile(काष्ठा cw_battery *cw_bat)
अणु
	पूर्णांक ret;
	अचिन्हित पूर्णांक reg_val;
	u8 reset_val;

	/* make sure gauge is not in sleep mode */
	ret = regmap_पढ़ो(cw_bat->regmap, CW2015_REG_MODE, &reg_val);
	अगर (ret)
		वापस ret;

	reset_val = reg_val;
	अगर ((reg_val & CW2015_MODE_SLEEP_MASK) == CW2015_MODE_SLEEP) अणु
		dev_err(cw_bat->dev,
			"Gauge is in sleep mode, can't update battery info\n");
		वापस -EINVAL;
	पूर्ण

	/* ग_लिखो new battery info */
	ret = regmap_raw_ग_लिखो(cw_bat->regmap, CW2015_REG_BATINFO,
			       cw_bat->bat_profile,
			       CW2015_SIZE_BATINFO);
	अगर (ret)
		वापस ret;

	/* set config update flag  */
	reg_val |= CW2015_CONFIG_UPDATE_FLG;
	reg_val &= ~CW2015_MASK_ATHD;
	reg_val |= CW2015_ATHD(cw_bat->alert_level);
	ret = regmap_ग_लिखो(cw_bat->regmap, CW2015_REG_CONFIG, reg_val);
	अगर (ret)
		वापस ret;

	/* reset gauge to apply new battery profile */
	reset_val &= ~CW2015_MODE_RESTART;
	reg_val = reset_val | CW2015_MODE_RESTART;
	ret = regmap_ग_लिखो(cw_bat->regmap, CW2015_REG_MODE, reg_val);
	अगर (ret)
		वापस ret;

	/* रुको क्रम gauge to reset */
	msleep(20);

	/* clear reset flag */
	ret = regmap_ग_लिखो(cw_bat->regmap, CW2015_REG_MODE, reset_val);
	अगर (ret)
		वापस ret;

	/* रुको क्रम gauge to become पढ़ोy */
	ret = regmap_पढ़ो_poll_समयout(cw_bat->regmap, CW2015_REG_SOC,
				       reg_val, reg_val <= 100,
				       10 * USEC_PER_MSEC, 10 * USEC_PER_SEC);
	अगर (ret)
		dev_err(cw_bat->dev,
			"Gauge did not become ready after profile upload\n");
	अन्यथा
		dev_dbg(cw_bat->dev, "Battery profile updated\n");

	वापस ret;
पूर्ण

अटल पूर्णांक cw_init(काष्ठा cw_battery *cw_bat)
अणु
	पूर्णांक ret;
	अचिन्हित पूर्णांक reg_val = CW2015_MODE_SLEEP;

	अगर ((reg_val & CW2015_MODE_SLEEP_MASK) == CW2015_MODE_SLEEP) अणु
		reg_val = CW2015_MODE_NORMAL;
		ret = regmap_ग_लिखो(cw_bat->regmap, CW2015_REG_MODE, reg_val);
		अगर (ret)
			वापस ret;
	पूर्ण

	ret = regmap_पढ़ो(cw_bat->regmap, CW2015_REG_CONFIG, &reg_val);
	अगर (ret)
		वापस ret;

	अगर ((reg_val & CW2015_MASK_ATHD) != CW2015_ATHD(cw_bat->alert_level)) अणु
		dev_dbg(cw_bat->dev, "Setting new alert level\n");
		reg_val &= ~CW2015_MASK_ATHD;
		reg_val |= ~CW2015_ATHD(cw_bat->alert_level);
		ret = regmap_ग_लिखो(cw_bat->regmap, CW2015_REG_CONFIG, reg_val);
		अगर (ret)
			वापस ret;
	पूर्ण

	ret = regmap_पढ़ो(cw_bat->regmap, CW2015_REG_CONFIG, &reg_val);
	अगर (ret)
		वापस ret;

	अगर (!(reg_val & CW2015_CONFIG_UPDATE_FLG)) अणु
		dev_dbg(cw_bat->dev,
			"Battery profile not present, uploading battery profile\n");
		अगर (cw_bat->bat_profile) अणु
			ret = cw_update_profile(cw_bat);
			अगर (ret) अणु
				dev_err(cw_bat->dev,
					"Failed to upload battery profile\n");
				वापस ret;
			पूर्ण
		पूर्ण अन्यथा अणु
			dev_warn(cw_bat->dev,
				 "No profile specified, continuing without profile\n");
		पूर्ण
	पूर्ण अन्यथा अगर (cw_bat->bat_profile) अणु
		u8 bat_info[CW2015_SIZE_BATINFO];

		ret = regmap_raw_पढ़ो(cw_bat->regmap, CW2015_REG_BATINFO,
				      bat_info, CW2015_SIZE_BATINFO);
		अगर (ret) अणु
			dev_err(cw_bat->dev,
				"Failed to read stored battery profile\n");
			वापस ret;
		पूर्ण

		अगर (स_भेद(bat_info, cw_bat->bat_profile, CW2015_SIZE_BATINFO)) अणु
			dev_warn(cw_bat->dev, "Replacing stored battery profile\n");
			ret = cw_update_profile(cw_bat);
			अगर (ret)
				वापस ret;
		पूर्ण
	पूर्ण अन्यथा अणु
		dev_warn(cw_bat->dev,
			 "Can't check current battery profile, no profile provided\n");
	पूर्ण

	dev_dbg(cw_bat->dev, "Battery profile configured\n");
	वापस 0;
पूर्ण

अटल पूर्णांक cw_घातer_on_reset(काष्ठा cw_battery *cw_bat)
अणु
	पूर्णांक ret;
	अचिन्हित अक्षर reset_val;

	reset_val = CW2015_MODE_SLEEP;
	ret = regmap_ग_लिखो(cw_bat->regmap, CW2015_REG_MODE, reset_val);
	अगर (ret)
		वापस ret;

	/* रुको क्रम gauge to enter sleep */
	msleep(20);

	reset_val = CW2015_MODE_NORMAL;
	ret = regmap_ग_लिखो(cw_bat->regmap, CW2015_REG_MODE, reset_val);
	अगर (ret)
		वापस ret;

	ret = cw_init(cw_bat);
	अगर (ret)
		वापस ret;
	वापस 0;
पूर्ण

#घोषणा HYSTERESIS(current, previous, up, करोwn) \
	(((current) < (previous) + (up)) && ((current) > (previous) - (करोwn)))

अटल पूर्णांक cw_get_soc(काष्ठा cw_battery *cw_bat)
अणु
	अचिन्हित पूर्णांक soc;
	पूर्णांक ret;

	ret = regmap_पढ़ो(cw_bat->regmap, CW2015_REG_SOC, &soc);
	अगर (ret)
		वापस ret;

	अगर (soc > 100) अणु
		पूर्णांक max_error_cycles =
			CW2015_BAT_SOC_ERROR_MS / cw_bat->poll_पूर्णांकerval_ms;

		dev_err(cw_bat->dev, "Invalid SoC %d%%\n", soc);
		cw_bat->पढ़ो_errors++;
		अगर (cw_bat->पढ़ो_errors > max_error_cycles) अणु
			dev_warn(cw_bat->dev,
				 "Too many invalid SoC reports, resetting gauge\n");
			cw_घातer_on_reset(cw_bat);
			cw_bat->पढ़ो_errors = 0;
		पूर्ण
		वापस cw_bat->soc;
	पूर्ण
	cw_bat->पढ़ो_errors = 0;

	/* Reset gauge अगर stuck जबतक अक्षरging */
	अगर (cw_bat->status == POWER_SUPPLY_STATUS_CHARGING && soc == cw_bat->soc) अणु
		पूर्णांक max_stuck_cycles =
			CW2015_BAT_CHARGING_STUCK_MS / cw_bat->poll_पूर्णांकerval_ms;

		cw_bat->अक्षरge_stuck_cnt++;
		अगर (cw_bat->अक्षरge_stuck_cnt > max_stuck_cycles) अणु
			dev_warn(cw_bat->dev,
				 "SoC stuck @%u%%, resetting gauge\n", soc);
			cw_घातer_on_reset(cw_bat);
			cw_bat->अक्षरge_stuck_cnt = 0;
		पूर्ण
	पूर्ण अन्यथा अणु
		cw_bat->अक्षरge_stuck_cnt = 0;
	पूर्ण

	/* Ignore voltage dips during अक्षरge */
	अगर (cw_bat->अक्षरger_attached && HYSTERESIS(soc, cw_bat->soc, 0, 3))
		soc = cw_bat->soc;

	/* Ignore voltage spikes during disअक्षरge */
	अगर (!cw_bat->अक्षरger_attached && HYSTERESIS(soc, cw_bat->soc, 3, 0))
		soc = cw_bat->soc;

	वापस soc;
पूर्ण

अटल पूर्णांक cw_get_voltage(काष्ठा cw_battery *cw_bat)
अणु
	पूर्णांक ret, i, voltage_mv;
	u16 reg_val;
	u32 avg = 0;

	क्रम (i = 0; i < CW2015_AVERAGING_SAMPLES; i++) अणु
		ret = cw_पढ़ो_word(cw_bat, CW2015_REG_VCELL, &reg_val);
		अगर (ret)
			वापस ret;

		avg += reg_val;
	पूर्ण
	avg /= CW2015_AVERAGING_SAMPLES;

	/*
	 * 305 uV per ADC step
	 * Use 312 / 1024  as efficient approximation of 305 / 1000
	 * Negligible error of 0.1%
	 */
	voltage_mv = avg * 312 / 1024;

	dev_dbg(cw_bat->dev, "Read voltage: %d mV, raw=0x%04x\n",
		voltage_mv, reg_val);
	वापस voltage_mv;
पूर्ण

अटल पूर्णांक cw_get_समय_प्रकारo_empty(काष्ठा cw_battery *cw_bat)
अणु
	पूर्णांक ret;
	u16 value16;

	ret = cw_पढ़ो_word(cw_bat, CW2015_REG_RRT_ALERT, &value16);
	अगर (ret)
		वापस ret;

	वापस value16 & CW2015_MASK_SOC;
पूर्ण

अटल व्योम cw_update_अक्षरge_status(काष्ठा cw_battery *cw_bat)
अणु
	पूर्णांक ret;

	ret = घातer_supply_am_i_supplied(cw_bat->rk_bat);
	अगर (ret < 0) अणु
		dev_warn(cw_bat->dev, "Failed to get supply state: %d\n", ret);
	पूर्ण अन्यथा अणु
		bool अक्षरger_attached;

		अक्षरger_attached = !!ret;
		अगर (cw_bat->अक्षरger_attached != अक्षरger_attached) अणु
			cw_bat->battery_changed = true;
			अगर (अक्षरger_attached)
				cw_bat->अक्षरge_count++;
		पूर्ण
		cw_bat->अक्षरger_attached = अक्षरger_attached;
	पूर्ण
पूर्ण

अटल व्योम cw_update_soc(काष्ठा cw_battery *cw_bat)
अणु
	पूर्णांक soc;

	soc = cw_get_soc(cw_bat);
	अगर (soc < 0)
		dev_err(cw_bat->dev, "Failed to get SoC from gauge: %d\n", soc);
	अन्यथा अगर (cw_bat->soc != soc) अणु
		cw_bat->soc = soc;
		cw_bat->battery_changed = true;
	पूर्ण
पूर्ण

अटल व्योम cw_update_voltage(काष्ठा cw_battery *cw_bat)
अणु
	पूर्णांक voltage_mv;

	voltage_mv = cw_get_voltage(cw_bat);
	अगर (voltage_mv < 0)
		dev_err(cw_bat->dev, "Failed to get voltage from gauge: %d\n",
			voltage_mv);
	अन्यथा
		cw_bat->voltage_mv = voltage_mv;
पूर्ण

अटल व्योम cw_update_status(काष्ठा cw_battery *cw_bat)
अणु
	पूर्णांक status = POWER_SUPPLY_STATUS_DISCHARGING;

	अगर (cw_bat->अक्षरger_attached) अणु
		अगर (cw_bat->soc >= 100)
			status = POWER_SUPPLY_STATUS_FULL;
		अन्यथा
			status = POWER_SUPPLY_STATUS_CHARGING;
	पूर्ण

	अगर (cw_bat->status != status)
		cw_bat->battery_changed = true;
	cw_bat->status = status;
पूर्ण

अटल व्योम cw_update_समय_प्रकारo_empty(काष्ठा cw_battery *cw_bat)
अणु
	पूर्णांक समय_प्रकारo_empty;

	समय_प्रकारo_empty = cw_get_समय_प्रकारo_empty(cw_bat);
	अगर (समय_प्रकारo_empty < 0)
		dev_err(cw_bat->dev, "Failed to get time to empty from gauge: %d\n",
			समय_प्रकारo_empty);
	अन्यथा अगर (cw_bat->समय_प्रकारo_empty != समय_प्रकारo_empty) अणु
		cw_bat->समय_प्रकारo_empty = समय_प्रकारo_empty;
		cw_bat->battery_changed = true;
	पूर्ण
पूर्ण

अटल व्योम cw_bat_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा delayed_work *delay_work;
	काष्ठा cw_battery *cw_bat;
	पूर्णांक ret;
	अचिन्हित पूर्णांक reg_val;

	delay_work = to_delayed_work(work);
	cw_bat = container_of(delay_work, काष्ठा cw_battery, battery_delay_work);
	ret = regmap_पढ़ो(cw_bat->regmap, CW2015_REG_MODE, &reg_val);
	अगर (ret) अणु
		dev_err(cw_bat->dev, "Failed to read mode from gauge: %d\n", ret);
	पूर्ण अन्यथा अणु
		अगर ((reg_val & CW2015_MODE_SLEEP_MASK) == CW2015_MODE_SLEEP) अणु
			पूर्णांक i;

			क्रम (i = 0; i < CW2015_RESET_TRIES; i++) अणु
				अगर (!cw_घातer_on_reset(cw_bat))
					अवरोध;
			पूर्ण
		पूर्ण
		cw_update_soc(cw_bat);
		cw_update_voltage(cw_bat);
		cw_update_अक्षरge_status(cw_bat);
		cw_update_status(cw_bat);
		cw_update_समय_प्रकारo_empty(cw_bat);
	पूर्ण
	dev_dbg(cw_bat->dev, "charger_attached = %d\n", cw_bat->अक्षरger_attached);
	dev_dbg(cw_bat->dev, "status = %d\n", cw_bat->status);
	dev_dbg(cw_bat->dev, "soc = %d%%\n", cw_bat->soc);
	dev_dbg(cw_bat->dev, "voltage = %dmV\n", cw_bat->voltage_mv);

	अगर (cw_bat->battery_changed)
		घातer_supply_changed(cw_bat->rk_bat);
	cw_bat->battery_changed = false;

	queue_delayed_work(cw_bat->battery_workqueue,
			   &cw_bat->battery_delay_work,
			   msecs_to_jअगरfies(cw_bat->poll_पूर्णांकerval_ms));
पूर्ण

अटल bool cw_battery_valid_समय_प्रकारo_empty(काष्ठा cw_battery *cw_bat)
अणु
	वापस	cw_bat->समय_प्रकारo_empty > 0 &&
		cw_bat->समय_प्रकारo_empty < CW2015_MASK_SOC &&
		cw_bat->status == POWER_SUPPLY_STATUS_DISCHARGING;
पूर्ण

अटल पूर्णांक cw_battery_get_property(काष्ठा घातer_supply *psy,
				   क्रमागत घातer_supply_property psp,
				   जोड़ घातer_supply_propval *val)
अणु
	काष्ठा cw_battery *cw_bat;

	cw_bat = घातer_supply_get_drvdata(psy);
	चयन (psp) अणु
	हाल POWER_SUPPLY_PROP_CAPACITY:
		val->पूर्णांकval = cw_bat->soc;
		अवरोध;

	हाल POWER_SUPPLY_PROP_STATUS:
		val->पूर्णांकval = cw_bat->status;
		अवरोध;

	हाल POWER_SUPPLY_PROP_PRESENT:
		val->पूर्णांकval = !!cw_bat->voltage_mv;
		अवरोध;

	हाल POWER_SUPPLY_PROP_VOLTAGE_NOW:
		val->पूर्णांकval = cw_bat->voltage_mv * 1000;
		अवरोध;

	हाल POWER_SUPPLY_PROP_TIME_TO_EMPTY_NOW:
		अगर (cw_battery_valid_समय_प्रकारo_empty(cw_bat))
			val->पूर्णांकval = cw_bat->समय_प्रकारo_empty;
		अन्यथा
			val->पूर्णांकval = 0;
		अवरोध;

	हाल POWER_SUPPLY_PROP_TECHNOLOGY:
		val->पूर्णांकval = POWER_SUPPLY_TECHNOLOGY_LION;
		अवरोध;

	हाल POWER_SUPPLY_PROP_CHARGE_COUNTER:
		val->पूर्णांकval = cw_bat->अक्षरge_count;
		अवरोध;

	हाल POWER_SUPPLY_PROP_CHARGE_FULL:
	हाल POWER_SUPPLY_PROP_CHARGE_FULL_DESIGN:
		अगर (cw_bat->battery.अक्षरge_full_design_uah > 0)
			val->पूर्णांकval = cw_bat->battery.अक्षरge_full_design_uah;
		अन्यथा
			val->पूर्णांकval = 0;
		अवरोध;

	हाल POWER_SUPPLY_PROP_CHARGE_NOW:
		val->पूर्णांकval = cw_bat->battery.अक्षरge_full_design_uah;
		val->पूर्णांकval = val->पूर्णांकval * cw_bat->soc / 100;
		अवरोध;

	हाल POWER_SUPPLY_PROP_CURRENT_NOW:
		अगर (cw_battery_valid_समय_प्रकारo_empty(cw_bat) &&
		    cw_bat->battery.अक्षरge_full_design_uah > 0) अणु
			/* calculate reमुख्यing capacity */
			val->पूर्णांकval = cw_bat->battery.अक्षरge_full_design_uah;
			val->पूर्णांकval = val->पूर्णांकval * cw_bat->soc / 100;

			/* estimate current based on समय to empty */
			val->पूर्णांकval = 60 * val->पूर्णांकval / cw_bat->समय_प्रकारo_empty;
		पूर्ण अन्यथा अणु
			val->पूर्णांकval = 0;
		पूर्ण

		अवरोध;

	शेष:
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल क्रमागत घातer_supply_property cw_battery_properties[] = अणु
	POWER_SUPPLY_PROP_CAPACITY,
	POWER_SUPPLY_PROP_STATUS,
	POWER_SUPPLY_PROP_PRESENT,
	POWER_SUPPLY_PROP_VOLTAGE_NOW,
	POWER_SUPPLY_PROP_TIME_TO_EMPTY_NOW,
	POWER_SUPPLY_PROP_TECHNOLOGY,
	POWER_SUPPLY_PROP_CHARGE_COUNTER,
	POWER_SUPPLY_PROP_CHARGE_FULL,
	POWER_SUPPLY_PROP_CHARGE_FULL_DESIGN,
	POWER_SUPPLY_PROP_CHARGE_NOW,
	POWER_SUPPLY_PROP_CURRENT_NOW,
पूर्ण;

अटल स्थिर काष्ठा घातer_supply_desc cw2015_bat_desc = अणु
	.name		= "cw2015-battery",
	.type		= POWER_SUPPLY_TYPE_BATTERY,
	.properties	= cw_battery_properties,
	.num_properties	= ARRAY_SIZE(cw_battery_properties),
	.get_property	= cw_battery_get_property,
पूर्ण;

अटल पूर्णांक cw2015_parse_properties(काष्ठा cw_battery *cw_bat)
अणु
	काष्ठा device *dev = cw_bat->dev;
	पूर्णांक length;
	पूर्णांक ret;

	length = device_property_count_u8(dev, "cellwise,battery-profile");
	अगर (length < 0) अणु
		dev_warn(cw_bat->dev,
			 "No battery-profile found, using current flash contents\n");
	पूर्ण अन्यथा अगर (length != CW2015_SIZE_BATINFO) अणु
		dev_err(cw_bat->dev, "battery-profile must be %d bytes\n",
			CW2015_SIZE_BATINFO);
		वापस -EINVAL;
	पूर्ण अन्यथा अणु
		cw_bat->bat_profile = devm_kzalloc(dev, length, GFP_KERNEL);
		अगर (!cw_bat->bat_profile)
			वापस -ENOMEM;

		ret = device_property_पढ़ो_u8_array(dev,
						"cellwise,battery-profile",
						cw_bat->bat_profile,
						length);
		अगर (ret)
			वापस ret;
	पूर्ण

	ret = device_property_पढ़ो_u32(dev, "cellwise,monitor-interval-ms",
				       &cw_bat->poll_पूर्णांकerval_ms);
	अगर (ret) अणु
		dev_dbg(cw_bat->dev, "Using default poll interval\n");
		cw_bat->poll_पूर्णांकerval_ms = CW2015_DEFAULT_POLL_INTERVAL_MS;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा regmap_range regmap_ranges_rd_yes[] = अणु
	regmap_reg_range(CW2015_REG_VERSION, CW2015_REG_VERSION),
	regmap_reg_range(CW2015_REG_VCELL, CW2015_REG_CONFIG),
	regmap_reg_range(CW2015_REG_MODE, CW2015_REG_MODE),
	regmap_reg_range(CW2015_REG_BATINFO,
			CW2015_REG_BATINFO + CW2015_SIZE_BATINFO - 1),
पूर्ण;

अटल स्थिर काष्ठा regmap_access_table regmap_rd_table = अणु
	.yes_ranges = regmap_ranges_rd_yes,
	.n_yes_ranges = 4,
पूर्ण;

अटल स्थिर काष्ठा regmap_range regmap_ranges_wr_yes[] = अणु
	regmap_reg_range(CW2015_REG_RRT_ALERT, CW2015_REG_CONFIG),
	regmap_reg_range(CW2015_REG_MODE, CW2015_REG_MODE),
	regmap_reg_range(CW2015_REG_BATINFO,
			CW2015_REG_BATINFO + CW2015_SIZE_BATINFO - 1),
पूर्ण;

अटल स्थिर काष्ठा regmap_access_table regmap_wr_table = अणु
	.yes_ranges = regmap_ranges_wr_yes,
	.n_yes_ranges = 3,
पूर्ण;

अटल स्थिर काष्ठा regmap_range regmap_ranges_vol_yes[] = अणु
	regmap_reg_range(CW2015_REG_VCELL, CW2015_REG_SOC + 1),
पूर्ण;

अटल स्थिर काष्ठा regmap_access_table regmap_vol_table = अणु
	.yes_ranges = regmap_ranges_vol_yes,
	.n_yes_ranges = 1,
पूर्ण;

अटल स्थिर काष्ठा regmap_config cw2015_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 8,
	.rd_table = &regmap_rd_table,
	.wr_table = &regmap_wr_table,
	.अस्थिर_table = &regmap_vol_table,
	.max_रेजिस्टर = CW2015_REG_BATINFO + CW2015_SIZE_BATINFO - 1,
पूर्ण;

अटल पूर्णांक cw_bat_probe(काष्ठा i2c_client *client)
अणु
	पूर्णांक ret;
	काष्ठा cw_battery *cw_bat;
	काष्ठा घातer_supply_config psy_cfg = अणु 0 पूर्ण;

	cw_bat = devm_kzalloc(&client->dev, माप(*cw_bat), GFP_KERNEL);
	अगर (!cw_bat)
		वापस -ENOMEM;

	i2c_set_clientdata(client, cw_bat);
	cw_bat->dev = &client->dev;
	cw_bat->soc = 1;

	ret = cw2015_parse_properties(cw_bat);
	अगर (ret) अणु
		dev_err(cw_bat->dev, "Failed to parse cw2015 properties\n");
		वापस ret;
	पूर्ण

	cw_bat->regmap = devm_regmap_init_i2c(client, &cw2015_regmap_config);
	अगर (IS_ERR(cw_bat->regmap)) अणु
		dev_err(cw_bat->dev, "Failed to allocate regmap: %ld\n",
			PTR_ERR(cw_bat->regmap));
		वापस PTR_ERR(cw_bat->regmap);
	पूर्ण

	ret = cw_init(cw_bat);
	अगर (ret) अणु
		dev_err(cw_bat->dev, "Init failed: %d\n", ret);
		वापस ret;
	पूर्ण

	psy_cfg.drv_data = cw_bat;
	psy_cfg.fwnode = dev_fwnode(cw_bat->dev);

	cw_bat->rk_bat = devm_घातer_supply_रेजिस्टर(&client->dev,
						    &cw2015_bat_desc,
						    &psy_cfg);
	अगर (IS_ERR(cw_bat->rk_bat)) अणु
		dev_err(cw_bat->dev, "Failed to register power supply\n");
		वापस PTR_ERR(cw_bat->rk_bat);
	पूर्ण

	ret = घातer_supply_get_battery_info(cw_bat->rk_bat, &cw_bat->battery);
	अगर (ret) अणु
		dev_warn(cw_bat->dev,
			 "No monitored battery, some properties will be missing\n");
	पूर्ण

	cw_bat->battery_workqueue = create_singlethपढ़ो_workqueue("rk_battery");
	INIT_DELAYED_WORK(&cw_bat->battery_delay_work, cw_bat_work);
	queue_delayed_work(cw_bat->battery_workqueue,
			   &cw_bat->battery_delay_work, msecs_to_jअगरfies(10));
	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused cw_bat_suspend(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा cw_battery *cw_bat = i2c_get_clientdata(client);

	cancel_delayed_work_sync(&cw_bat->battery_delay_work);
	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused cw_bat_resume(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा cw_battery *cw_bat = i2c_get_clientdata(client);

	queue_delayed_work(cw_bat->battery_workqueue,
			   &cw_bat->battery_delay_work, 0);
	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(cw_bat_pm_ops, cw_bat_suspend, cw_bat_resume);

अटल पूर्णांक cw_bat_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा cw_battery *cw_bat = i2c_get_clientdata(client);

	cancel_delayed_work_sync(&cw_bat->battery_delay_work);
	घातer_supply_put_battery_info(cw_bat->rk_bat, &cw_bat->battery);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id cw_bat_id_table[] = अणु
	अणु "cw2015", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल स्थिर काष्ठा of_device_id cw2015_of_match[] = अणु
	अणु .compatible = "cellwise,cw2015" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, cw2015_of_match);

अटल काष्ठा i2c_driver cw_bat_driver = अणु
	.driver = अणु
		.name = "cw2015",
		.of_match_table = cw2015_of_match,
		.pm = &cw_bat_pm_ops,
	पूर्ण,
	.probe_new = cw_bat_probe,
	.हटाओ = cw_bat_हटाओ,
	.id_table = cw_bat_id_table,
पूर्ण;

module_i2c_driver(cw_bat_driver);

MODULE_AUTHOR("xhc<xhc@rock-chips.com>");
MODULE_AUTHOR("Tobias Schramm <t.schramm@manjaro.org>");
MODULE_DESCRIPTION("cw2015/cw2013 battery driver");
MODULE_LICENSE("GPL");
