<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2011 Samsung Electronics Co., Ltd.
 * MyungJoo Ham <myungjoo.ham@samsung.com>
 *
 * This driver enables to monitor battery health and control अक्षरger
 * during suspend-to-mem.
 * Charger manager depends on other devices. Register this later than
 * the depending devices.
 *
**/

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/irq.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/rtc.h>
#समावेश <linux/slab.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/घातer/अक्षरger-manager.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/sysfs.h>
#समावेश <linux/of.h>
#समावेश <linux/thermal.h>

अटल काष्ठा अणु
	स्थिर अक्षर *name;
	u64 extcon_type;
पूर्ण extcon_mapping[] = अणु
	/* Current textual representations */
	अणु "USB", EXTCON_USB पूर्ण,
	अणु "USB-HOST", EXTCON_USB_HOST पूर्ण,
	अणु "SDP", EXTCON_CHG_USB_SDP पूर्ण,
	अणु "DCP", EXTCON_CHG_USB_DCP पूर्ण,
	अणु "CDP", EXTCON_CHG_USB_CDP पूर्ण,
	अणु "ACA", EXTCON_CHG_USB_ACA पूर्ण,
	अणु "FAST-CHARGER", EXTCON_CHG_USB_FAST पूर्ण,
	अणु "SLOW-CHARGER", EXTCON_CHG_USB_SLOW पूर्ण,
	अणु "WPT", EXTCON_CHG_WPT पूर्ण,
	अणु "PD", EXTCON_CHG_USB_PD पूर्ण,
	अणु "DOCK", EXTCON_DOCK पूर्ण,
	अणु "JIG", EXTCON_JIG पूर्ण,
	अणु "MECHANICAL", EXTCON_MECHANICAL पूर्ण,
	/* Deprecated textual representations */
	अणु "TA", EXTCON_CHG_USB_SDP पूर्ण,
	अणु "CHARGE-DOWNSTREAM", EXTCON_CHG_USB_CDP पूर्ण,
पूर्ण;

/*
 * Default temperature threshold क्रम अक्षरging.
 * Every temperature units are in tenth of centigrade.
 */
#घोषणा CM_DEFAULT_RECHARGE_TEMP_DIFF	50
#घोषणा CM_DEFAULT_CHARGE_TEMP_MAX	500

/*
 * Regard CM_JIFFIES_SMALL jअगरfies is small enough to ignore क्रम
 * delayed works so that we can run delayed works with CM_JIFFIES_SMALL
 * without any delays.
 */
#घोषणा	CM_JIFFIES_SMALL	(2)

/* If y is valid (> 0) and smaller than x, करो x = y */
#घोषणा CM_MIN_VALID(x, y)	x = (((y > 0) && ((x) > (y))) ? (y) : (x))

/*
 * Regard CM_RTC_SMALL (sec) is small enough to ignore error in invoking
 * rtc alarm. It should be 2 or larger
 */
#घोषणा CM_RTC_SMALL		(2)

अटल LIST_HEAD(cm_list);
अटल DEFINE_MUTEX(cm_list_mtx);

/* About in-suspend (suspend-again) monitoring */
अटल काष्ठा alarm *cm_समयr;

अटल bool cm_suspended;
अटल bool cm_समयr_set;
अटल अचिन्हित दीर्घ cm_suspend_duration_ms;

/* About normal (not suspended) monitoring */
अटल अचिन्हित दीर्घ polling_jअगरfy = अच_दीर्घ_उच्च; /* अच_दीर्घ_उच्च: no polling */
अटल अचिन्हित दीर्घ next_polling; /* Next appoपूर्णांकed polling समय */
अटल काष्ठा workqueue_काष्ठा *cm_wq; /* init at driver add */
अटल काष्ठा delayed_work cm_monitor_work; /* init at driver add */

/**
 * is_batt_present - See अगर the battery presents in place.
 * @cm: the Charger Manager representing the battery.
 */
अटल bool is_batt_present(काष्ठा अक्षरger_manager *cm)
अणु
	जोड़ घातer_supply_propval val;
	काष्ठा घातer_supply *psy;
	bool present = false;
	पूर्णांक i, ret;

	चयन (cm->desc->battery_present) अणु
	हाल CM_BATTERY_PRESENT:
		present = true;
		अवरोध;
	हाल CM_NO_BATTERY:
		अवरोध;
	हाल CM_FUEL_GAUGE:
		psy = घातer_supply_get_by_name(cm->desc->psy_fuel_gauge);
		अगर (!psy)
			अवरोध;

		ret = घातer_supply_get_property(psy, POWER_SUPPLY_PROP_PRESENT,
				&val);
		अगर (ret == 0 && val.पूर्णांकval)
			present = true;
		घातer_supply_put(psy);
		अवरोध;
	हाल CM_CHARGER_STAT:
		क्रम (i = 0; cm->desc->psy_अक्षरger_stat[i]; i++) अणु
			psy = घातer_supply_get_by_name(
					cm->desc->psy_अक्षरger_stat[i]);
			अगर (!psy) अणु
				dev_err(cm->dev, "Cannot find power supply \"%s\"\n",
					cm->desc->psy_अक्षरger_stat[i]);
				जारी;
			पूर्ण

			ret = घातer_supply_get_property(psy,
				POWER_SUPPLY_PROP_PRESENT, &val);
			घातer_supply_put(psy);
			अगर (ret == 0 && val.पूर्णांकval) अणु
				present = true;
				अवरोध;
			पूर्ण
		पूर्ण
		अवरोध;
	पूर्ण

	वापस present;
पूर्ण

/**
 * is_ext_pwr_online - See अगर an बाह्यal घातer source is attached to अक्षरge
 * @cm: the Charger Manager representing the battery.
 *
 * Returns true अगर at least one of the अक्षरgers of the battery has an बाह्यal
 * घातer source attached to अक्षरge the battery regardless of whether it is
 * actually अक्षरging or not.
 */
अटल bool is_ext_pwr_online(काष्ठा अक्षरger_manager *cm)
अणु
	जोड़ घातer_supply_propval val;
	काष्ठा घातer_supply *psy;
	bool online = false;
	पूर्णांक i, ret;

	/* If at least one of them has one, it's yes. */
	क्रम (i = 0; cm->desc->psy_अक्षरger_stat[i]; i++) अणु
		psy = घातer_supply_get_by_name(cm->desc->psy_अक्षरger_stat[i]);
		अगर (!psy) अणु
			dev_err(cm->dev, "Cannot find power supply \"%s\"\n",
					cm->desc->psy_अक्षरger_stat[i]);
			जारी;
		पूर्ण

		ret = घातer_supply_get_property(psy, POWER_SUPPLY_PROP_ONLINE,
				&val);
		घातer_supply_put(psy);
		अगर (ret == 0 && val.पूर्णांकval) अणु
			online = true;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस online;
पूर्ण

/**
 * get_batt_uV - Get the voltage level of the battery
 * @cm: the Charger Manager representing the battery.
 * @uV: the voltage level वापसed.
 *
 * Returns 0 अगर there is no error.
 * Returns a negative value on error.
 */
अटल पूर्णांक get_batt_uV(काष्ठा अक्षरger_manager *cm, पूर्णांक *uV)
अणु
	जोड़ घातer_supply_propval val;
	काष्ठा घातer_supply *fuel_gauge;
	पूर्णांक ret;

	fuel_gauge = घातer_supply_get_by_name(cm->desc->psy_fuel_gauge);
	अगर (!fuel_gauge)
		वापस -ENODEV;

	ret = घातer_supply_get_property(fuel_gauge,
				POWER_SUPPLY_PROP_VOLTAGE_NOW, &val);
	घातer_supply_put(fuel_gauge);
	अगर (ret)
		वापस ret;

	*uV = val.पूर्णांकval;
	वापस 0;
पूर्ण

/**
 * is_अक्षरging - Returns true अगर the battery is being अक्षरged.
 * @cm: the Charger Manager representing the battery.
 */
अटल bool is_अक्षरging(काष्ठा अक्षरger_manager *cm)
अणु
	पूर्णांक i, ret;
	bool अक्षरging = false;
	काष्ठा घातer_supply *psy;
	जोड़ घातer_supply_propval val;

	/* If there is no battery, it cannot be अक्षरged */
	अगर (!is_batt_present(cm))
		वापस false;

	/* If at least one of the अक्षरger is अक्षरging, वापस yes */
	क्रम (i = 0; cm->desc->psy_अक्षरger_stat[i]; i++) अणु
		/* 1. The अक्षरger sholuld not be DISABLED */
		अगर (cm->emergency_stop)
			जारी;
		अगर (!cm->अक्षरger_enabled)
			जारी;

		psy = घातer_supply_get_by_name(cm->desc->psy_अक्षरger_stat[i]);
		अगर (!psy) अणु
			dev_err(cm->dev, "Cannot find power supply \"%s\"\n",
					cm->desc->psy_अक्षरger_stat[i]);
			जारी;
		पूर्ण

		/* 2. The अक्षरger should be online (ext-घातer) */
		ret = घातer_supply_get_property(psy, POWER_SUPPLY_PROP_ONLINE,
				&val);
		अगर (ret) अणु
			dev_warn(cm->dev, "Cannot read ONLINE value from %s\n",
				 cm->desc->psy_अक्षरger_stat[i]);
			घातer_supply_put(psy);
			जारी;
		पूर्ण
		अगर (val.पूर्णांकval == 0) अणु
			घातer_supply_put(psy);
			जारी;
		पूर्ण

		/*
		 * 3. The अक्षरger should not be FULL, DISCHARGING,
		 * or NOT_CHARGING.
		 */
		ret = घातer_supply_get_property(psy, POWER_SUPPLY_PROP_STATUS,
				&val);
		घातer_supply_put(psy);
		अगर (ret) अणु
			dev_warn(cm->dev, "Cannot read STATUS value from %s\n",
				 cm->desc->psy_अक्षरger_stat[i]);
			जारी;
		पूर्ण
		अगर (val.पूर्णांकval == POWER_SUPPLY_STATUS_FULL ||
				val.पूर्णांकval == POWER_SUPPLY_STATUS_DISCHARGING ||
				val.पूर्णांकval == POWER_SUPPLY_STATUS_NOT_CHARGING)
			जारी;

		/* Then, this is अक्षरging. */
		अक्षरging = true;
		अवरोध;
	पूर्ण

	वापस अक्षरging;
पूर्ण

/**
 * is_full_अक्षरged - Returns true अगर the battery is fully अक्षरged.
 * @cm: the Charger Manager representing the battery.
 */
अटल bool is_full_अक्षरged(काष्ठा अक्षरger_manager *cm)
अणु
	काष्ठा अक्षरger_desc *desc = cm->desc;
	जोड़ घातer_supply_propval val;
	काष्ठा घातer_supply *fuel_gauge;
	bool is_full = false;
	पूर्णांक ret = 0;
	पूर्णांक uV;

	/* If there is no battery, it cannot be अक्षरged */
	अगर (!is_batt_present(cm))
		वापस false;

	fuel_gauge = घातer_supply_get_by_name(cm->desc->psy_fuel_gauge);
	अगर (!fuel_gauge)
		वापस false;

	/* Full, अगर it's over the fullbatt voltage */
	अगर (desc->fullbatt_uV > 0) अणु
		ret = get_batt_uV(cm, &uV);
		अगर (!ret) अणु
			/* Battery is alपढ़ोy full, checks voltage drop. */
			अगर (cm->battery_status == POWER_SUPPLY_STATUS_FULL
					&& desc->fullbatt_vchkdrop_uV)
				uV += desc->fullbatt_vchkdrop_uV;
			अगर (uV >= desc->fullbatt_uV)
				वापस true;
		पूर्ण
	पूर्ण

	अगर (desc->fullbatt_full_capacity > 0) अणु
		val.पूर्णांकval = 0;

		/* Not full अगर capacity of fuel gauge isn't full */
		ret = घातer_supply_get_property(fuel_gauge,
				POWER_SUPPLY_PROP_CHARGE_FULL, &val);
		अगर (!ret && val.पूर्णांकval > desc->fullbatt_full_capacity) अणु
			is_full = true;
			जाओ out;
		पूर्ण
	पूर्ण

	/* Full, अगर the capacity is more than fullbatt_soc */
	अगर (desc->fullbatt_soc > 0) अणु
		val.पूर्णांकval = 0;

		ret = घातer_supply_get_property(fuel_gauge,
				POWER_SUPPLY_PROP_CAPACITY, &val);
		अगर (!ret && val.पूर्णांकval >= desc->fullbatt_soc) अणु
			is_full = true;
			जाओ out;
		पूर्ण
	पूर्ण

out:
	घातer_supply_put(fuel_gauge);
	वापस is_full;
पूर्ण

/**
 * is_polling_required - Return true अगर need to जारी polling क्रम this CM.
 * @cm: the Charger Manager representing the battery.
 */
अटल bool is_polling_required(काष्ठा अक्षरger_manager *cm)
अणु
	चयन (cm->desc->polling_mode) अणु
	हाल CM_POLL_DISABLE:
		वापस false;
	हाल CM_POLL_ALWAYS:
		वापस true;
	हाल CM_POLL_EXTERNAL_POWER_ONLY:
		वापस is_ext_pwr_online(cm);
	हाल CM_POLL_CHARGING_ONLY:
		वापस is_अक्षरging(cm);
	शेष:
		dev_warn(cm->dev, "Incorrect polling_mode (%d)\n",
			 cm->desc->polling_mode);
	पूर्ण

	वापस false;
पूर्ण

/**
 * try_अक्षरger_enable - Enable/Disable अक्षरgers altogether
 * @cm: the Charger Manager representing the battery.
 * @enable: true: enable / false: disable
 *
 * Note that Charger Manager keeps the अक्षरger enabled regardless whether
 * the अक्षरger is अक्षरging or not (because battery is full or no बाह्यal
 * घातer source exists) except when CM needs to disable अक्षरgers क्रमcibly
 * because of emergency causes; when the battery is overheated or too cold.
 */
अटल पूर्णांक try_अक्षरger_enable(काष्ठा अक्षरger_manager *cm, bool enable)
अणु
	पूर्णांक err = 0, i;
	काष्ठा अक्षरger_desc *desc = cm->desc;

	/* Ignore अगर it's redundant command */
	अगर (enable == cm->अक्षरger_enabled)
		वापस 0;

	अगर (enable) अणु
		अगर (cm->emergency_stop)
			वापस -EAGAIN;

		/*
		 * Save start समय of अक्षरging to limit
		 * maximum possible अक्षरging समय.
		 */
		cm->अक्षरging_start_समय = kसमय_प्रकारo_ms(kसमय_get());
		cm->अक्षरging_end_समय = 0;

		क्रम (i = 0 ; i < desc->num_अक्षरger_regulators ; i++) अणु
			अगर (desc->अक्षरger_regulators[i].बाह्यally_control)
				जारी;

			err = regulator_enable(desc->अक्षरger_regulators[i].consumer);
			अगर (err < 0) अणु
				dev_warn(cm->dev, "Cannot enable %s regulator\n",
					 desc->अक्षरger_regulators[i].regulator_name);
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		/*
		 * Save end समय of अक्षरging to मुख्यtain fully अक्षरged state
		 * of battery after full-batt.
		 */
		cm->अक्षरging_start_समय = 0;
		cm->अक्षरging_end_समय = kसमय_प्रकारo_ms(kसमय_get());

		क्रम (i = 0 ; i < desc->num_अक्षरger_regulators ; i++) अणु
			अगर (desc->अक्षरger_regulators[i].बाह्यally_control)
				जारी;

			err = regulator_disable(desc->अक्षरger_regulators[i].consumer);
			अगर (err < 0) अणु
				dev_warn(cm->dev, "Cannot disable %s regulator\n",
					 desc->अक्षरger_regulators[i].regulator_name);
			पूर्ण
		पूर्ण

		/*
		 * Abnormal battery state - Stop अक्षरging क्रमcibly,
		 * even अगर अक्षरger was enabled at the other places
		 */
		क्रम (i = 0; i < desc->num_अक्षरger_regulators; i++) अणु
			अगर (regulator_is_enabled(
				    desc->अक्षरger_regulators[i].consumer)) अणु
				regulator_क्रमce_disable(
					desc->अक्षरger_regulators[i].consumer);
				dev_warn(cm->dev, "Disable regulator(%s) forcibly\n",
					 desc->अक्षरger_regulators[i].regulator_name);
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (!err)
		cm->अक्षरger_enabled = enable;

	वापस err;
पूर्ण

/**
 * check_अक्षरging_duration - Monitor अक्षरging/disअक्षरging duration
 * @cm: the Charger Manager representing the battery.
 *
 * If whole अक्षरging duration exceed 'charging_max_duration_ms',
 * cm stop अक्षरging to prevent overअक्षरge/overheat. If disअक्षरging
 * duration exceed 'discharging _max_duration_ms', अक्षरger cable is
 * attached, after full-batt, cm start अक्षरging to मुख्यtain fully
 * अक्षरged state क्रम battery.
 */
अटल पूर्णांक check_अक्षरging_duration(काष्ठा अक्षरger_manager *cm)
अणु
	काष्ठा अक्षरger_desc *desc = cm->desc;
	u64 curr = kसमय_प्रकारo_ms(kसमय_get());
	u64 duration;
	पूर्णांक ret = false;

	अगर (!desc->अक्षरging_max_duration_ms &&
			!desc->disअक्षरging_max_duration_ms)
		वापस ret;

	अगर (cm->अक्षरger_enabled) अणु
		duration = curr - cm->अक्षरging_start_समय;

		अगर (duration > desc->अक्षरging_max_duration_ms) अणु
			dev_info(cm->dev, "Charging duration exceed %ums\n",
				 desc->अक्षरging_max_duration_ms);
			ret = true;
		पूर्ण
	पूर्ण अन्यथा अगर (cm->battery_status == POWER_SUPPLY_STATUS_NOT_CHARGING) अणु
		duration = curr - cm->अक्षरging_end_समय;

		अगर (duration > desc->disअक्षरging_max_duration_ms) अणु
			dev_info(cm->dev, "Discharging duration exceed %ums\n",
				 desc->disअक्षरging_max_duration_ms);
			ret = true;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक cm_get_battery_temperature_by_psy(काष्ठा अक्षरger_manager *cm,
					पूर्णांक *temp)
अणु
	काष्ठा घातer_supply *fuel_gauge;
	पूर्णांक ret;

	fuel_gauge = घातer_supply_get_by_name(cm->desc->psy_fuel_gauge);
	अगर (!fuel_gauge)
		वापस -ENODEV;

	ret = घातer_supply_get_property(fuel_gauge,
				POWER_SUPPLY_PROP_TEMP,
				(जोड़ घातer_supply_propval *)temp);
	घातer_supply_put(fuel_gauge);

	वापस ret;
पूर्ण

अटल पूर्णांक cm_get_battery_temperature(काष्ठा अक्षरger_manager *cm,
					पूर्णांक *temp)
अणु
	पूर्णांक ret;

	अगर (!cm->desc->measure_battery_temp)
		वापस -ENODEV;

#अगर_घोषित CONFIG_THERMAL
	अगर (cm->tzd_batt) अणु
		ret = thermal_zone_get_temp(cm->tzd_batt, temp);
		अगर (!ret)
			/* Calibrate temperature unit */
			*temp /= 100;
	पूर्ण अन्यथा
#पूर्ण_अगर
	अणु
		/* अगर-अन्यथा जारीd from CONFIG_THERMAL */
		ret = cm_get_battery_temperature_by_psy(cm, temp);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक cm_check_thermal_status(काष्ठा अक्षरger_manager *cm)
अणु
	काष्ठा अक्षरger_desc *desc = cm->desc;
	पूर्णांक temp, upper_limit, lower_limit;
	पूर्णांक ret = 0;

	ret = cm_get_battery_temperature(cm, &temp);
	अगर (ret) अणु
		/* FIXME:
		 * No inक्रमmation of battery temperature might
		 * occur hazarकरोus result. We have to handle it
		 * depending on battery type.
		 */
		dev_err(cm->dev, "Failed to get battery temperature\n");
		वापस 0;
	पूर्ण

	upper_limit = desc->temp_max;
	lower_limit = desc->temp_min;

	अगर (cm->emergency_stop) अणु
		upper_limit -= desc->temp_dअगरf;
		lower_limit += desc->temp_dअगरf;
	पूर्ण

	अगर (temp > upper_limit)
		ret = CM_BATT_OVERHEAT;
	अन्यथा अगर (temp < lower_limit)
		ret = CM_BATT_COLD;
	अन्यथा
		ret = CM_BATT_OK;

	cm->emergency_stop = ret;

	वापस ret;
पूर्ण

/**
 * cm_get_target_status - Check current status and get next target status.
 * @cm: the Charger Manager representing the battery.
 */
अटल पूर्णांक cm_get_target_status(काष्ठा अक्षरger_manager *cm)
अणु
	अगर (!is_ext_pwr_online(cm))
		वापस POWER_SUPPLY_STATUS_DISCHARGING;

	अगर (cm_check_thermal_status(cm)) अणु
		/* Check अगर disअक्षरging duration exceeds limit. */
		अगर (check_अक्षरging_duration(cm))
			जाओ अक्षरging_ok;
		वापस POWER_SUPPLY_STATUS_NOT_CHARGING;
	पूर्ण

	चयन (cm->battery_status) अणु
	हाल POWER_SUPPLY_STATUS_CHARGING:
		/* Check अगर अक्षरging duration exceeds limit. */
		अगर (check_अक्षरging_duration(cm))
			वापस POWER_SUPPLY_STATUS_FULL;
		fallthrough;
	हाल POWER_SUPPLY_STATUS_FULL:
		अगर (is_full_अक्षरged(cm))
			वापस POWER_SUPPLY_STATUS_FULL;
		fallthrough;
	शेष:
		अवरोध;
	पूर्ण

अक्षरging_ok:
	/* Charging is allowed. */
	वापस POWER_SUPPLY_STATUS_CHARGING;
पूर्ण

/**
 * _cm_monitor - Monitor the temperature and वापस true क्रम exceptions.
 * @cm: the Charger Manager representing the battery.
 *
 * Returns true अगर there is an event to notअगरy क्रम the battery.
 * (True अगर the status of "emergency_stop" changes)
 */
अटल bool _cm_monitor(काष्ठा अक्षरger_manager *cm)
अणु
	पूर्णांक target;

	target = cm_get_target_status(cm);

	try_अक्षरger_enable(cm, (target == POWER_SUPPLY_STATUS_CHARGING));

	अगर (cm->battery_status != target) अणु
		cm->battery_status = target;
		घातer_supply_changed(cm->अक्षरger_psy);
	पूर्ण

	वापस (cm->battery_status == POWER_SUPPLY_STATUS_NOT_CHARGING);
पूर्ण

/**
 * cm_monitor - Monitor every battery.
 *
 * Returns true अगर there is an event to notअगरy from any of the batteries.
 * (True अगर the status of "emergency_stop" changes)
 */
अटल bool cm_monitor(व्योम)
अणु
	bool stop = false;
	काष्ठा अक्षरger_manager *cm;

	mutex_lock(&cm_list_mtx);

	list_क्रम_each_entry(cm, &cm_list, entry) अणु
		अगर (_cm_monitor(cm))
			stop = true;
	पूर्ण

	mutex_unlock(&cm_list_mtx);

	वापस stop;
पूर्ण

/**
 * _setup_polling - Setup the next instance of polling.
 * @work: work_काष्ठा of the function _setup_polling.
 */
अटल व्योम _setup_polling(काष्ठा work_काष्ठा *work)
अणु
	अचिन्हित दीर्घ min = अच_दीर्घ_उच्च;
	काष्ठा अक्षरger_manager *cm;
	bool keep_polling = false;
	अचिन्हित दीर्घ _next_polling;

	mutex_lock(&cm_list_mtx);

	list_क्रम_each_entry(cm, &cm_list, entry) अणु
		अगर (is_polling_required(cm) && cm->desc->polling_पूर्णांकerval_ms) अणु
			keep_polling = true;

			अगर (min > cm->desc->polling_पूर्णांकerval_ms)
				min = cm->desc->polling_पूर्णांकerval_ms;
		पूर्ण
	पूर्ण

	polling_jअगरfy = msecs_to_jअगरfies(min);
	अगर (polling_jअगरfy <= CM_JIFFIES_SMALL)
		polling_jअगरfy = CM_JIFFIES_SMALL + 1;

	अगर (!keep_polling)
		polling_jअगरfy = अच_दीर्घ_उच्च;
	अगर (polling_jअगरfy == अच_दीर्घ_उच्च)
		जाओ out;

	WARN(cm_wq == शून्य, "charger-manager: workqueue not initialized"
			    ". try it later. %s\n", __func__);

	/*
	 * Use mod_delayed_work() अगरf the next polling पूर्णांकerval should
	 * occur beक्रमe the currently scheduled one.  If @cm_monitor_work
	 * isn't active, the end result is the same, so no need to worry
	 * about stale @next_polling.
	 */
	_next_polling = jअगरfies + polling_jअगरfy;

	अगर (समय_beक्रमe(_next_polling, next_polling)) अणु
		mod_delayed_work(cm_wq, &cm_monitor_work, polling_jअगरfy);
		next_polling = _next_polling;
	पूर्ण अन्यथा अणु
		अगर (queue_delayed_work(cm_wq, &cm_monitor_work, polling_jअगरfy))
			next_polling = _next_polling;
	पूर्ण
out:
	mutex_unlock(&cm_list_mtx);
पूर्ण
अटल DECLARE_WORK(setup_polling, _setup_polling);

/**
 * cm_monitor_poller - The Monitor / Poller.
 * @work: work_काष्ठा of the function cm_monitor_poller
 *
 * During non-suspended state, cm_monitor_poller is used to poll and monitor
 * the batteries.
 */
अटल व्योम cm_monitor_poller(काष्ठा work_काष्ठा *work)
अणु
	cm_monitor();
	schedule_work(&setup_polling);
पूर्ण

अटल पूर्णांक अक्षरger_get_property(काष्ठा घातer_supply *psy,
		क्रमागत घातer_supply_property psp,
		जोड़ घातer_supply_propval *val)
अणु
	काष्ठा अक्षरger_manager *cm = घातer_supply_get_drvdata(psy);
	काष्ठा अक्षरger_desc *desc = cm->desc;
	काष्ठा घातer_supply *fuel_gauge = शून्य;
	पूर्णांक ret = 0;
	पूर्णांक uV;

	चयन (psp) अणु
	हाल POWER_SUPPLY_PROP_STATUS:
		val->पूर्णांकval = cm->battery_status;
		अवरोध;
	हाल POWER_SUPPLY_PROP_HEALTH:
		अगर (cm->emergency_stop == CM_BATT_OVERHEAT)
			val->पूर्णांकval = POWER_SUPPLY_HEALTH_OVERHEAT;
		अन्यथा अगर (cm->emergency_stop == CM_BATT_COLD)
			val->पूर्णांकval = POWER_SUPPLY_HEALTH_COLD;
		अन्यथा
			val->पूर्णांकval = POWER_SUPPLY_HEALTH_GOOD;
		अवरोध;
	हाल POWER_SUPPLY_PROP_PRESENT:
		अगर (is_batt_present(cm))
			val->पूर्णांकval = 1;
		अन्यथा
			val->पूर्णांकval = 0;
		अवरोध;
	हाल POWER_SUPPLY_PROP_VOLTAGE_NOW:
		ret = get_batt_uV(cm, &val->पूर्णांकval);
		अवरोध;
	हाल POWER_SUPPLY_PROP_CURRENT_NOW:
		fuel_gauge = घातer_supply_get_by_name(cm->desc->psy_fuel_gauge);
		अगर (!fuel_gauge) अणु
			ret = -ENODEV;
			अवरोध;
		पूर्ण
		ret = घातer_supply_get_property(fuel_gauge,
				POWER_SUPPLY_PROP_CURRENT_NOW, val);
		अवरोध;
	हाल POWER_SUPPLY_PROP_TEMP:
		वापस cm_get_battery_temperature(cm, &val->पूर्णांकval);
	हाल POWER_SUPPLY_PROP_CAPACITY:
		अगर (!is_batt_present(cm)) अणु
			/* There is no battery. Assume 100% */
			val->पूर्णांकval = 100;
			अवरोध;
		पूर्ण

		fuel_gauge = घातer_supply_get_by_name(cm->desc->psy_fuel_gauge);
		अगर (!fuel_gauge) अणु
			ret = -ENODEV;
			अवरोध;
		पूर्ण

		ret = घातer_supply_get_property(fuel_gauge,
					POWER_SUPPLY_PROP_CAPACITY, val);
		अगर (ret)
			अवरोध;

		अगर (val->पूर्णांकval > 100) अणु
			val->पूर्णांकval = 100;
			अवरोध;
		पूर्ण
		अगर (val->पूर्णांकval < 0)
			val->पूर्णांकval = 0;

		/* Do not adjust SOC when अक्षरging: voltage is overrated */
		अगर (is_अक्षरging(cm))
			अवरोध;

		/*
		 * If the capacity value is inconsistent, calibrate it base on
		 * the battery voltage values and the thresholds given as desc
		 */
		ret = get_batt_uV(cm, &uV);
		अगर (ret) अणु
			/* Voltage inक्रमmation not available. No calibration */
			ret = 0;
			अवरोध;
		पूर्ण

		अगर (desc->fullbatt_uV > 0 && uV >= desc->fullbatt_uV &&
		    !is_अक्षरging(cm)) अणु
			val->पूर्णांकval = 100;
			अवरोध;
		पूर्ण

		अवरोध;
	हाल POWER_SUPPLY_PROP_ONLINE:
		अगर (is_ext_pwr_online(cm))
			val->पूर्णांकval = 1;
		अन्यथा
			val->पूर्णांकval = 0;
		अवरोध;
	हाल POWER_SUPPLY_PROP_CHARGE_FULL:
	हाल POWER_SUPPLY_PROP_CHARGE_NOW:
		fuel_gauge = घातer_supply_get_by_name(cm->desc->psy_fuel_gauge);
		अगर (!fuel_gauge) अणु
			ret = -ENODEV;
			अवरोध;
		पूर्ण
		ret = घातer_supply_get_property(fuel_gauge, psp, val);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	अगर (fuel_gauge)
		घातer_supply_put(fuel_gauge);
	वापस ret;
पूर्ण

#घोषणा NUM_CHARGER_PSY_OPTIONAL	(4)
अटल क्रमागत घातer_supply_property शेष_अक्षरger_props[] = अणु
	/* Guaranteed to provide */
	POWER_SUPPLY_PROP_STATUS,
	POWER_SUPPLY_PROP_HEALTH,
	POWER_SUPPLY_PROP_PRESENT,
	POWER_SUPPLY_PROP_VOLTAGE_NOW,
	POWER_SUPPLY_PROP_CAPACITY,
	POWER_SUPPLY_PROP_ONLINE,
	/*
	 * Optional properties are:
	 * POWER_SUPPLY_PROP_CHARGE_FULL,
	 * POWER_SUPPLY_PROP_CHARGE_NOW,
	 * POWER_SUPPLY_PROP_CURRENT_NOW,
	 * POWER_SUPPLY_PROP_TEMP,
	 */
पूर्ण;

अटल स्थिर काष्ठा घातer_supply_desc psy_शेष = अणु
	.name = "battery",
	.type = POWER_SUPPLY_TYPE_BATTERY,
	.properties = शेष_अक्षरger_props,
	.num_properties = ARRAY_SIZE(शेष_अक्षरger_props),
	.get_property = अक्षरger_get_property,
	.no_thermal = true,
पूर्ण;

/**
 * cm_setup_समयr - For in-suspend monitoring setup wakeup alarm
 *		    क्रम suspend_again.
 *
 * Returns true अगर the alarm is set क्रम Charger Manager to use.
 * Returns false अगर
 *	cm_setup_समयr fails to set an alarm,
 *	cm_setup_समयr करोes not need to set an alarm क्रम Charger Manager,
 *	or an alarm previously configured is to be used.
 */
अटल bool cm_setup_समयr(व्योम)
अणु
	काष्ठा अक्षरger_manager *cm;
	अचिन्हित पूर्णांक wakeup_ms = अच_पूर्णांक_उच्च;
	पूर्णांक समयr_req = 0;

	अगर (समय_after(next_polling, jअगरfies))
		CM_MIN_VALID(wakeup_ms,
			jअगरfies_to_msecs(next_polling - jअगरfies));

	mutex_lock(&cm_list_mtx);
	list_क्रम_each_entry(cm, &cm_list, entry) अणु
		/* Skip अगर polling is not required क्रम this CM */
		अगर (!is_polling_required(cm) && !cm->emergency_stop)
			जारी;
		समयr_req++;
		अगर (cm->desc->polling_पूर्णांकerval_ms == 0)
			जारी;
		CM_MIN_VALID(wakeup_ms, cm->desc->polling_पूर्णांकerval_ms);
	पूर्ण
	mutex_unlock(&cm_list_mtx);

	अगर (समयr_req && cm_समयr) अणु
		kसमय_प्रकार now, add;

		/*
		 * Set alarm with the polling पूर्णांकerval (wakeup_ms)
		 * The alarm समय should be NOW + CM_RTC_SMALL or later.
		 */
		अगर (wakeup_ms == अच_पूर्णांक_उच्च ||
			wakeup_ms < CM_RTC_SMALL * MSEC_PER_SEC)
			wakeup_ms = 2 * CM_RTC_SMALL * MSEC_PER_SEC;

		pr_info("Charger Manager wakeup timer: %u ms\n", wakeup_ms);

		now = kसमय_get_bootसमय();
		add = kसमय_set(wakeup_ms / MSEC_PER_SEC,
				(wakeup_ms % MSEC_PER_SEC) * NSEC_PER_MSEC);
		alarm_start(cm_समयr, kसमय_add(now, add));

		cm_suspend_duration_ms = wakeup_ms;

		वापस true;
	पूर्ण
	वापस false;
पूर्ण

/**
 * अक्षरger_extcon_work - enable/diable अक्षरger according to the state
 *			of अक्षरger cable
 *
 * @work: work_काष्ठा of the function अक्षरger_extcon_work.
 */
अटल व्योम अक्षरger_extcon_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा अक्षरger_cable *cable =
			container_of(work, काष्ठा अक्षरger_cable, wq);
	पूर्णांक ret;

	अगर (cable->attached && cable->min_uA != 0 && cable->max_uA != 0) अणु
		ret = regulator_set_current_limit(cable->अक्षरger->consumer,
					cable->min_uA, cable->max_uA);
		अगर (ret < 0) अणु
			pr_err("Cannot set current limit of %s (%s)\n",
			       cable->अक्षरger->regulator_name, cable->name);
			वापस;
		पूर्ण

		pr_info("Set current limit of %s : %duA ~ %duA\n",
			cable->अक्षरger->regulator_name,
			cable->min_uA, cable->max_uA);
	पूर्ण

	cancel_delayed_work(&cm_monitor_work);
	queue_delayed_work(cm_wq, &cm_monitor_work, 0);
पूर्ण

/**
 * अक्षरger_extcon_notअगरier - receive the state of अक्षरger cable
 *			when रेजिस्टरed cable is attached or detached.
 *
 * @self: the notअगरier block of the अक्षरger_extcon_notअगरier.
 * @event: the cable state.
 * @ptr: the data poपूर्णांकer of notअगरier block.
 */
अटल पूर्णांक अक्षरger_extcon_notअगरier(काष्ठा notअगरier_block *self,
			अचिन्हित दीर्घ event, व्योम *ptr)
अणु
	काष्ठा अक्षरger_cable *cable =
		container_of(self, काष्ठा अक्षरger_cable, nb);

	/*
	 * The newly state of अक्षरger cable.
	 * If cable is attached, cable->attached is true.
	 */
	cable->attached = event;

	/*
	 * Setup work क्रम controlling अक्षरger(regulator)
	 * according to अक्षरger cable.
	 */
	schedule_work(&cable->wq);

	वापस NOTIFY_DONE;
पूर्ण

/**
 * अक्षरger_extcon_init - रेजिस्टर बाह्यal connector to use it
 *			as the अक्षरger cable
 *
 * @cm: the Charger Manager representing the battery.
 * @cable: the Charger cable representing the बाह्यal connector.
 */
अटल पूर्णांक अक्षरger_extcon_init(काष्ठा अक्षरger_manager *cm,
		काष्ठा अक्षरger_cable *cable)
अणु
	पूर्णांक ret, i;
	u64 extcon_type = EXTCON_NONE;

	/*
	 * Charger manager use Extcon framework to identअगरy
	 * the अक्षरger cable among various बाह्यal connector
	 * cable (e.g., TA, USB, MHL, Dock).
	 */
	INIT_WORK(&cable->wq, अक्षरger_extcon_work);
	cable->nb.notअगरier_call = अक्षरger_extcon_notअगरier;

	cable->extcon_dev = extcon_get_extcon_dev(cable->extcon_name);
	अगर (IS_ERR_OR_शून्य(cable->extcon_dev)) अणु
		pr_err("Cannot find extcon_dev for %s (cable: %s)\n",
			cable->extcon_name, cable->name);
		अगर (cable->extcon_dev == शून्य)
			वापस -EPROBE_DEFER;
		अन्यथा
			वापस PTR_ERR(cable->extcon_dev);
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(extcon_mapping); i++) अणु
		अगर (!म_भेद(cable->name, extcon_mapping[i].name)) अणु
			extcon_type = extcon_mapping[i].extcon_type;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (extcon_type == EXTCON_NONE) अणु
		pr_err("Cannot find cable for type %s", cable->name);
		वापस -EINVAL;
	पूर्ण

	cable->extcon_type = extcon_type;

	ret = devm_extcon_रेजिस्टर_notअगरier(cm->dev, cable->extcon_dev,
		cable->extcon_type, &cable->nb);
	अगर (ret < 0) अणु
		pr_err("Cannot register extcon_dev for %s (cable: %s)\n",
			cable->extcon_name, cable->name);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * अक्षरger_manager_रेजिस्टर_extcon - Register extcon device to receive state
 *				     of अक्षरger cable.
 * @cm: the Charger Manager representing the battery.
 *
 * This function support EXTCON(External Connector) subप्रणाली to detect the
 * state of अक्षरger cables क्रम enabling or disabling अक्षरger(regulator) and
 * select the अक्षरger cable क्रम अक्षरging among a number of बाह्यal cable
 * according to policy of H/W board.
 */
अटल पूर्णांक अक्षरger_manager_रेजिस्टर_extcon(काष्ठा अक्षरger_manager *cm)
अणु
	काष्ठा अक्षरger_desc *desc = cm->desc;
	काष्ठा अक्षरger_regulator *अक्षरger;
	अचिन्हित दीर्घ event;
	पूर्णांक ret;
	पूर्णांक i;
	पूर्णांक j;

	क्रम (i = 0; i < desc->num_अक्षरger_regulators; i++) अणु
		अक्षरger = &desc->अक्षरger_regulators[i];

		अक्षरger->consumer = regulator_get(cm->dev,
					अक्षरger->regulator_name);
		अगर (IS_ERR(अक्षरger->consumer)) अणु
			dev_err(cm->dev, "Cannot find charger(%s)\n",
				अक्षरger->regulator_name);
			वापस PTR_ERR(अक्षरger->consumer);
		पूर्ण
		अक्षरger->cm = cm;

		क्रम (j = 0; j < अक्षरger->num_cables; j++) अणु
			काष्ठा अक्षरger_cable *cable = &अक्षरger->cables[j];

			ret = अक्षरger_extcon_init(cm, cable);
			अगर (ret < 0) अणु
				dev_err(cm->dev, "Cannot initialize charger(%s)\n",
					अक्षरger->regulator_name);
				वापस ret;
			पूर्ण
			cable->अक्षरger = अक्षरger;
			cable->cm = cm;

			event = extcon_get_state(cable->extcon_dev,
				cable->extcon_type);
			अक्षरger_extcon_notअगरier(&cable->nb,
				event, शून्य);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/* help function of sysfs node to control अक्षरger(regulator) */
अटल sमाप_प्रकार अक्षरger_name_show(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा अक्षरger_regulator *अक्षरger
		= container_of(attr, काष्ठा अक्षरger_regulator, attr_name);

	वापस प्र_लिखो(buf, "%s\n", अक्षरger->regulator_name);
पूर्ण

अटल sमाप_प्रकार अक्षरger_state_show(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा अक्षरger_regulator *अक्षरger
		= container_of(attr, काष्ठा अक्षरger_regulator, attr_state);
	पूर्णांक state = 0;

	अगर (!अक्षरger->बाह्यally_control)
		state = regulator_is_enabled(अक्षरger->consumer);

	वापस प्र_लिखो(buf, "%s\n", state ? "enabled" : "disabled");
पूर्ण

अटल sमाप_प्रकार अक्षरger_बाह्यally_control_show(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा अक्षरger_regulator *अक्षरger = container_of(attr,
			काष्ठा अक्षरger_regulator, attr_बाह्यally_control);

	वापस प्र_लिखो(buf, "%d\n", अक्षरger->बाह्यally_control);
पूर्ण

अटल sमाप_प्रकार अक्षरger_बाह्यally_control_store(काष्ठा device *dev,
				काष्ठा device_attribute *attr, स्थिर अक्षर *buf,
				माप_प्रकार count)
अणु
	काष्ठा अक्षरger_regulator *अक्षरger
		= container_of(attr, काष्ठा अक्षरger_regulator,
					attr_बाह्यally_control);
	काष्ठा अक्षरger_manager *cm = अक्षरger->cm;
	काष्ठा अक्षरger_desc *desc = cm->desc;
	पूर्णांक i;
	पूर्णांक ret;
	पूर्णांक बाह्यally_control;
	पूर्णांक अक्षरgers_बाह्यally_control = 1;

	ret = माला_पूछो(buf, "%d", &बाह्यally_control);
	अगर (ret == 0) अणु
		ret = -EINVAL;
		वापस ret;
	पूर्ण

	अगर (!बाह्यally_control) अणु
		अक्षरger->बाह्यally_control = 0;
		वापस count;
	पूर्ण

	क्रम (i = 0; i < desc->num_अक्षरger_regulators; i++) अणु
		अगर (&desc->अक्षरger_regulators[i] != अक्षरger &&
			!desc->अक्षरger_regulators[i].बाह्यally_control) अणु
			/*
			 * At least, one अक्षरger is controlled by
			 * अक्षरger-manager
			 */
			अक्षरgers_बाह्यally_control = 0;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!अक्षरgers_बाह्यally_control) अणु
		अगर (cm->अक्षरger_enabled) अणु
			try_अक्षरger_enable(अक्षरger->cm, false);
			अक्षरger->बाह्यally_control = बाह्यally_control;
			try_अक्षरger_enable(अक्षरger->cm, true);
		पूर्ण अन्यथा अणु
			अक्षरger->बाह्यally_control = बाह्यally_control;
		पूर्ण
	पूर्ण अन्यथा अणु
		dev_warn(cm->dev,
			 "'%s' regulator should be controlled in charger-manager because charger-manager must need at least one charger for charging\n",
			 अक्षरger->regulator_name);
	पूर्ण

	वापस count;
पूर्ण

/**
 * अक्षरger_manager_prepare_sysfs - Prepare sysfs entry क्रम each अक्षरger
 * @cm: the Charger Manager representing the battery.
 *
 * This function add sysfs entry क्रम अक्षरger(regulator) to control अक्षरger from
 * user-space. If some development board use one more अक्षरgers क्रम अक्षरging
 * but only need one अक्षरger on specअगरic हाल which is dependent on user
 * scenario or hardware restrictions, the user enter 1 or 0(zero) to '/sys/
 * class/घातer_supply/battery/अक्षरger.[index]/बाह्यally_control'. For example,
 * अगर user enter 1 to 'sys/class/घातer_supply/battery/अक्षरger.[index]/
 * बाह्यally_control, this अक्षरger isn't controlled from अक्षरger-manager and
 * always stay off state of regulator.
 */
अटल पूर्णांक अक्षरger_manager_prepare_sysfs(काष्ठा अक्षरger_manager *cm)
अणु
	काष्ठा अक्षरger_desc *desc = cm->desc;
	काष्ठा अक्षरger_regulator *अक्षरger;
	पूर्णांक अक्षरgers_बाह्यally_control = 1;
	अक्षर *name;
	पूर्णांक i;

	/* Create sysfs entry to control अक्षरger(regulator) */
	क्रम (i = 0; i < desc->num_अक्षरger_regulators; i++) अणु
		अक्षरger = &desc->अक्षरger_regulators[i];

		name = devm_kaप्र_लिखो(cm->dev, GFP_KERNEL, "charger.%d", i);
		अगर (!name)
			वापस -ENOMEM;

		अक्षरger->attrs[0] = &अक्षरger->attr_name.attr;
		अक्षरger->attrs[1] = &अक्षरger->attr_state.attr;
		अक्षरger->attrs[2] = &अक्षरger->attr_बाह्यally_control.attr;
		अक्षरger->attrs[3] = शून्य;

		अक्षरger->attr_grp.name = name;
		अक्षरger->attr_grp.attrs = अक्षरger->attrs;
		desc->sysfs_groups[i] = &अक्षरger->attr_grp;

		sysfs_attr_init(&अक्षरger->attr_name.attr);
		अक्षरger->attr_name.attr.name = "name";
		अक्षरger->attr_name.attr.mode = 0444;
		अक्षरger->attr_name.show = अक्षरger_name_show;

		sysfs_attr_init(&अक्षरger->attr_state.attr);
		अक्षरger->attr_state.attr.name = "state";
		अक्षरger->attr_state.attr.mode = 0444;
		अक्षरger->attr_state.show = अक्षरger_state_show;

		sysfs_attr_init(&अक्षरger->attr_बाह्यally_control.attr);
		अक्षरger->attr_बाह्यally_control.attr.name
				= "externally_control";
		अक्षरger->attr_बाह्यally_control.attr.mode = 0644;
		अक्षरger->attr_बाह्यally_control.show
				= अक्षरger_बाह्यally_control_show;
		अक्षरger->attr_बाह्यally_control.store
				= अक्षरger_बाह्यally_control_store;

		अगर (!desc->अक्षरger_regulators[i].बाह्यally_control ||
				!अक्षरgers_बाह्यally_control)
			अक्षरgers_बाह्यally_control = 0;

		dev_info(cm->dev, "'%s' regulator's externally_control is %d\n",
			 अक्षरger->regulator_name, अक्षरger->बाह्यally_control);
	पूर्ण

	अगर (अक्षरgers_बाह्यally_control) अणु
		dev_err(cm->dev, "Cannot register regulator because charger-manager must need at least one charger for charging battery\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cm_init_thermal_data(काष्ठा अक्षरger_manager *cm,
		काष्ठा घातer_supply *fuel_gauge,
		क्रमागत घातer_supply_property *properties,
		माप_प्रकार *num_properties)
अणु
	काष्ठा अक्षरger_desc *desc = cm->desc;
	जोड़ घातer_supply_propval val;
	पूर्णांक ret;

	/* Verअगरy whether fuel gauge provides battery temperature */
	ret = घातer_supply_get_property(fuel_gauge,
					POWER_SUPPLY_PROP_TEMP, &val);

	अगर (!ret) अणु
		properties[*num_properties] = POWER_SUPPLY_PROP_TEMP;
		(*num_properties)++;
		cm->desc->measure_battery_temp = true;
	पूर्ण
#अगर_घोषित CONFIG_THERMAL
	अगर (ret && desc->thermal_zone) अणु
		cm->tzd_batt =
			thermal_zone_get_zone_by_name(desc->thermal_zone);
		अगर (IS_ERR(cm->tzd_batt))
			वापस PTR_ERR(cm->tzd_batt);

		/* Use बाह्यal thermometer */
		properties[*num_properties] = POWER_SUPPLY_PROP_TEMP;
		(*num_properties)++;
		cm->desc->measure_battery_temp = true;
		ret = 0;
	पूर्ण
#पूर्ण_अगर
	अगर (cm->desc->measure_battery_temp) अणु
		/* NOTICE : Default allowable minimum अक्षरge temperature is 0 */
		अगर (!desc->temp_max)
			desc->temp_max = CM_DEFAULT_CHARGE_TEMP_MAX;
		अगर (!desc->temp_dअगरf)
			desc->temp_dअगरf = CM_DEFAULT_RECHARGE_TEMP_DIFF;
	पूर्ण

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा of_device_id अक्षरger_manager_match[] = अणु
	अणु
		.compatible = "charger-manager",
	पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल काष्ठा अक्षरger_desc *of_cm_parse_desc(काष्ठा device *dev)
अणु
	काष्ठा अक्षरger_desc *desc;
	काष्ठा device_node *np = dev->of_node;
	u32 poll_mode = CM_POLL_DISABLE;
	u32 battery_stat = CM_NO_BATTERY;
	पूर्णांक num_chgs = 0;

	desc = devm_kzalloc(dev, माप(*desc), GFP_KERNEL);
	अगर (!desc)
		वापस ERR_PTR(-ENOMEM);

	of_property_पढ़ो_string(np, "cm-name", &desc->psy_name);

	of_property_पढ़ो_u32(np, "cm-poll-mode", &poll_mode);
	desc->polling_mode = poll_mode;

	of_property_पढ़ो_u32(np, "cm-poll-interval",
				&desc->polling_पूर्णांकerval_ms);

	of_property_पढ़ो_u32(np, "cm-fullbatt-vchkdrop-volt",
					&desc->fullbatt_vchkdrop_uV);
	of_property_पढ़ो_u32(np, "cm-fullbatt-voltage", &desc->fullbatt_uV);
	of_property_पढ़ो_u32(np, "cm-fullbatt-soc", &desc->fullbatt_soc);
	of_property_पढ़ो_u32(np, "cm-fullbatt-capacity",
					&desc->fullbatt_full_capacity);

	of_property_पढ़ो_u32(np, "cm-battery-stat", &battery_stat);
	desc->battery_present = battery_stat;

	/* अक्षरgers */
	num_chgs = of_property_count_strings(np, "cm-chargers");
	अगर (num_chgs > 0) अणु
		पूर्णांक i;

		/* Allocate empty bin at the tail of array */
		desc->psy_अक्षरger_stat = devm_kसुस्मृति(dev,
						      num_chgs + 1,
						      माप(अक्षर *),
						      GFP_KERNEL);
		अगर (!desc->psy_अक्षरger_stat)
			वापस ERR_PTR(-ENOMEM);

		क्रम (i = 0; i < num_chgs; i++)
			of_property_पढ़ो_string_index(np, "cm-chargers",
						      i, &desc->psy_अक्षरger_stat[i]);
	पूर्ण

	of_property_पढ़ो_string(np, "cm-fuel-gauge", &desc->psy_fuel_gauge);

	of_property_पढ़ो_string(np, "cm-thermal-zone", &desc->thermal_zone);

	of_property_पढ़ो_u32(np, "cm-battery-cold", &desc->temp_min);
	अगर (of_get_property(np, "cm-battery-cold-in-minus", शून्य))
		desc->temp_min *= -1;
	of_property_पढ़ो_u32(np, "cm-battery-hot", &desc->temp_max);
	of_property_पढ़ो_u32(np, "cm-battery-temp-diff", &desc->temp_dअगरf);

	of_property_पढ़ो_u32(np, "cm-charging-max",
				&desc->अक्षरging_max_duration_ms);
	of_property_पढ़ो_u32(np, "cm-discharging-max",
				&desc->disअक्षरging_max_duration_ms);

	/* battery अक्षरger regulators */
	desc->num_अक्षरger_regulators = of_get_child_count(np);
	अगर (desc->num_अक्षरger_regulators) अणु
		काष्ठा अक्षरger_regulator *chg_regs;
		काष्ठा device_node *child;

		chg_regs = devm_kसुस्मृति(dev,
					desc->num_अक्षरger_regulators,
					माप(*chg_regs),
					GFP_KERNEL);
		अगर (!chg_regs)
			वापस ERR_PTR(-ENOMEM);

		desc->अक्षरger_regulators = chg_regs;

		desc->sysfs_groups = devm_kसुस्मृति(dev,
					desc->num_अक्षरger_regulators + 1,
					माप(*desc->sysfs_groups),
					GFP_KERNEL);
		अगर (!desc->sysfs_groups)
			वापस ERR_PTR(-ENOMEM);

		क्रम_each_child_of_node(np, child) अणु
			काष्ठा अक्षरger_cable *cables;
			काष्ठा device_node *_child;

			of_property_पढ़ो_string(child, "cm-regulator-name",
					&chg_regs->regulator_name);

			/* अक्षरger cables */
			chg_regs->num_cables = of_get_child_count(child);
			अगर (chg_regs->num_cables) अणु
				cables = devm_kसुस्मृति(dev,
						      chg_regs->num_cables,
						      माप(*cables),
						      GFP_KERNEL);
				अगर (!cables) अणु
					of_node_put(child);
					वापस ERR_PTR(-ENOMEM);
				पूर्ण

				chg_regs->cables = cables;

				क्रम_each_child_of_node(child, _child) अणु
					of_property_पढ़ो_string(_child,
					"cm-cable-name", &cables->name);
					of_property_पढ़ो_string(_child,
					"cm-cable-extcon",
					&cables->extcon_name);
					of_property_पढ़ो_u32(_child,
					"cm-cable-min",
					&cables->min_uA);
					of_property_पढ़ो_u32(_child,
					"cm-cable-max",
					&cables->max_uA);
					cables++;
				पूर्ण
			पूर्ण
			chg_regs++;
		पूर्ण
	पूर्ण
	वापस desc;
पूर्ण

अटल अंतरभूत काष्ठा अक्षरger_desc *cm_get_drv_data(काष्ठा platक्रमm_device *pdev)
अणु
	अगर (pdev->dev.of_node)
		वापस of_cm_parse_desc(&pdev->dev);
	वापस dev_get_platdata(&pdev->dev);
पूर्ण

अटल क्रमागत alarmसमयr_restart cm_समयr_func(काष्ठा alarm *alarm, kसमय_प्रकार now)
अणु
	cm_समयr_set = false;
	वापस ALARMTIMER_NORESTART;
पूर्ण

अटल पूर्णांक अक्षरger_manager_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा अक्षरger_desc *desc = cm_get_drv_data(pdev);
	काष्ठा अक्षरger_manager *cm;
	पूर्णांक ret, i = 0;
	जोड़ घातer_supply_propval val;
	काष्ठा घातer_supply *fuel_gauge;
	क्रमागत घातer_supply_property *properties;
	माप_प्रकार num_properties;
	काष्ठा घातer_supply_config psy_cfg = अणुपूर्ण;

	अगर (IS_ERR(desc)) अणु
		dev_err(&pdev->dev, "No platform data (desc) found\n");
		वापस PTR_ERR(desc);
	पूर्ण

	cm = devm_kzalloc(&pdev->dev, माप(*cm), GFP_KERNEL);
	अगर (!cm)
		वापस -ENOMEM;

	/* Basic Values. Unspecअगरied are Null or 0 */
	cm->dev = &pdev->dev;
	cm->desc = desc;
	psy_cfg.drv_data = cm;

	/* Initialize alarm समयr */
	अगर (alarmसमयr_get_rtcdev()) अणु
		cm_समयr = devm_kzalloc(cm->dev, माप(*cm_समयr), GFP_KERNEL);
		अगर (!cm_समयr)
			वापस -ENOMEM;
		alarm_init(cm_समयr, ALARM_BOOTTIME, cm_समयr_func);
	पूर्ण

	/*
	 * Some of the following करो not need to be errors.
	 * Users may पूर्णांकentionally ignore those features.
	 */
	अगर (desc->fullbatt_uV == 0) अणु
		dev_info(&pdev->dev, "Ignoring full-battery voltage threshold as it is not supplied\n");
	पूर्ण
	अगर (!desc->fullbatt_vchkdrop_uV) अणु
		dev_info(&pdev->dev, "Disabling full-battery voltage drop checking mechanism as it is not supplied\n");
		desc->fullbatt_vchkdrop_uV = 0;
	पूर्ण
	अगर (desc->fullbatt_soc == 0) अणु
		dev_info(&pdev->dev, "Ignoring full-battery soc(state of charge) threshold as it is not supplied\n");
	पूर्ण
	अगर (desc->fullbatt_full_capacity == 0) अणु
		dev_info(&pdev->dev, "Ignoring full-battery full capacity threshold as it is not supplied\n");
	पूर्ण

	अगर (!desc->अक्षरger_regulators || desc->num_अक्षरger_regulators < 1) अणु
		dev_err(&pdev->dev, "charger_regulators undefined\n");
		वापस -EINVAL;
	पूर्ण

	अगर (!desc->psy_अक्षरger_stat || !desc->psy_अक्षरger_stat[0]) अणु
		dev_err(&pdev->dev, "No power supply defined\n");
		वापस -EINVAL;
	पूर्ण

	अगर (!desc->psy_fuel_gauge) अणु
		dev_err(&pdev->dev, "No fuel gauge power supply defined\n");
		वापस -EINVAL;
	पूर्ण

	/* Check अगर अक्षरger's supplies are present at probe */
	क्रम (i = 0; desc->psy_अक्षरger_stat[i]; i++) अणु
		काष्ठा घातer_supply *psy;

		psy = घातer_supply_get_by_name(desc->psy_अक्षरger_stat[i]);
		अगर (!psy) अणु
			dev_err(&pdev->dev, "Cannot find power supply \"%s\"\n",
				desc->psy_अक्षरger_stat[i]);
			वापस -ENODEV;
		पूर्ण
		घातer_supply_put(psy);
	पूर्ण

	अगर (cm->desc->polling_mode != CM_POLL_DISABLE &&
	    (desc->polling_पूर्णांकerval_ms == 0 ||
	     msecs_to_jअगरfies(desc->polling_पूर्णांकerval_ms) <= CM_JIFFIES_SMALL)) अणु
		dev_err(&pdev->dev, "polling_interval_ms is too small\n");
		वापस -EINVAL;
	पूर्ण

	अगर (!desc->अक्षरging_max_duration_ms ||
			!desc->disअक्षरging_max_duration_ms) अणु
		dev_info(&pdev->dev, "Cannot limit charging duration checking mechanism to prevent overcharge/overheat and control discharging duration\n");
		desc->अक्षरging_max_duration_ms = 0;
		desc->disअक्षरging_max_duration_ms = 0;
	पूर्ण

	platक्रमm_set_drvdata(pdev, cm);

	स_नकल(&cm->अक्षरger_psy_desc, &psy_शेष, माप(psy_शेष));

	अगर (!desc->psy_name)
		म_नकलन(cm->psy_name_buf, psy_शेष.name, PSY_NAME_MAX);
	अन्यथा
		म_नकलन(cm->psy_name_buf, desc->psy_name, PSY_NAME_MAX);
	cm->अक्षरger_psy_desc.name = cm->psy_name_buf;

	/* Allocate क्रम psy properties because they may vary */
	properties = devm_kसुस्मृति(&pdev->dev,
			     ARRAY_SIZE(शेष_अक्षरger_props) +
				NUM_CHARGER_PSY_OPTIONAL,
			     माप(*properties), GFP_KERNEL);
	अगर (!properties)
		वापस -ENOMEM;

	स_नकल(properties, शेष_अक्षरger_props,
		माप(क्रमागत घातer_supply_property) *
		ARRAY_SIZE(शेष_अक्षरger_props));
	num_properties = ARRAY_SIZE(शेष_अक्षरger_props);

	/* Find which optional psy-properties are available */
	fuel_gauge = घातer_supply_get_by_name(desc->psy_fuel_gauge);
	अगर (!fuel_gauge) अणु
		dev_err(&pdev->dev, "Cannot find power supply \"%s\"\n",
			desc->psy_fuel_gauge);
		वापस -ENODEV;
	पूर्ण
	अगर (!घातer_supply_get_property(fuel_gauge,
					POWER_SUPPLY_PROP_CHARGE_FULL, &val)) अणु
		properties[num_properties] =
				POWER_SUPPLY_PROP_CHARGE_FULL;
		num_properties++;
	पूर्ण
	अगर (!घातer_supply_get_property(fuel_gauge,
					  POWER_SUPPLY_PROP_CHARGE_NOW, &val)) अणु
		properties[num_properties] =
				POWER_SUPPLY_PROP_CHARGE_NOW;
		num_properties++;
	पूर्ण
	अगर (!घातer_supply_get_property(fuel_gauge,
					  POWER_SUPPLY_PROP_CURRENT_NOW,
					  &val)) अणु
		properties[num_properties] =
				POWER_SUPPLY_PROP_CURRENT_NOW;
		num_properties++;
	पूर्ण

	ret = cm_init_thermal_data(cm, fuel_gauge, properties, &num_properties);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Failed to initialize thermal data\n");
		cm->desc->measure_battery_temp = false;
	पूर्ण
	घातer_supply_put(fuel_gauge);

	cm->अक्षरger_psy_desc.properties = properties;
	cm->अक्षरger_psy_desc.num_properties = num_properties;

	/* Register sysfs entry क्रम अक्षरger(regulator) */
	ret = अक्षरger_manager_prepare_sysfs(cm);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev,
			"Cannot prepare sysfs entry of regulators\n");
		वापस ret;
	पूर्ण
	psy_cfg.attr_grp = desc->sysfs_groups;

	cm->अक्षरger_psy = घातer_supply_रेजिस्टर(&pdev->dev,
						&cm->अक्षरger_psy_desc,
						&psy_cfg);
	अगर (IS_ERR(cm->अक्षरger_psy)) अणु
		dev_err(&pdev->dev, "Cannot register charger-manager with name \"%s\"\n",
			cm->अक्षरger_psy_desc.name);
		वापस PTR_ERR(cm->अक्षरger_psy);
	पूर्ण

	/* Register extcon device क्रम अक्षरger cable */
	ret = अक्षरger_manager_रेजिस्टर_extcon(cm);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "Cannot initialize extcon device\n");
		जाओ err_reg_extcon;
	पूर्ण

	/* Add to the list */
	mutex_lock(&cm_list_mtx);
	list_add(&cm->entry, &cm_list);
	mutex_unlock(&cm_list_mtx);

	/*
	 * Charger-manager is capable of waking up the प्रणाली from sleep
	 * when event is happened through cm_notअगरy_event()
	 */
	device_init_wakeup(&pdev->dev, true);
	device_set_wakeup_capable(&pdev->dev, false);

	/*
	 * Charger-manager have to check the अक्षरging state right after
	 * initialization of अक्षरger-manager and then update current अक्षरging
	 * state.
	 */
	cm_monitor();

	schedule_work(&setup_polling);

	वापस 0;

err_reg_extcon:
	क्रम (i = 0; i < desc->num_अक्षरger_regulators; i++)
		regulator_put(desc->अक्षरger_regulators[i].consumer);

	घातer_supply_unरेजिस्टर(cm->अक्षरger_psy);

	वापस ret;
पूर्ण

अटल पूर्णांक अक्षरger_manager_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा अक्षरger_manager *cm = platक्रमm_get_drvdata(pdev);
	काष्ठा अक्षरger_desc *desc = cm->desc;
	पूर्णांक i = 0;

	/* Remove from the list */
	mutex_lock(&cm_list_mtx);
	list_del(&cm->entry);
	mutex_unlock(&cm_list_mtx);

	cancel_work_sync(&setup_polling);
	cancel_delayed_work_sync(&cm_monitor_work);

	क्रम (i = 0 ; i < desc->num_अक्षरger_regulators ; i++)
		regulator_put(desc->अक्षरger_regulators[i].consumer);

	घातer_supply_unरेजिस्टर(cm->अक्षरger_psy);

	try_अक्षरger_enable(cm, false);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा platक्रमm_device_id अक्षरger_manager_id[] = अणु
	अणु "charger-manager", 0 पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(platक्रमm, अक्षरger_manager_id);

अटल पूर्णांक cm_suspend_noirq(काष्ठा device *dev)
अणु
	अगर (device_may_wakeup(dev)) अणु
		device_set_wakeup_capable(dev, false);
		वापस -EAGAIN;
	पूर्ण

	वापस 0;
पूर्ण

अटल bool cm_need_to_awake(व्योम)
अणु
	काष्ठा अक्षरger_manager *cm;

	अगर (cm_समयr)
		वापस false;

	mutex_lock(&cm_list_mtx);
	list_क्रम_each_entry(cm, &cm_list, entry) अणु
		अगर (is_अक्षरging(cm)) अणु
			mutex_unlock(&cm_list_mtx);
			वापस true;
		पूर्ण
	पूर्ण
	mutex_unlock(&cm_list_mtx);

	वापस false;
पूर्ण

अटल पूर्णांक cm_suspend_prepare(काष्ठा device *dev)
अणु
	अगर (cm_need_to_awake())
		वापस -EBUSY;

	अगर (!cm_suspended)
		cm_suspended = true;

	cm_समयr_set = cm_setup_समयr();

	अगर (cm_समयr_set) अणु
		cancel_work_sync(&setup_polling);
		cancel_delayed_work_sync(&cm_monitor_work);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम cm_suspend_complete(काष्ठा device *dev)
अणु
	काष्ठा अक्षरger_manager *cm = dev_get_drvdata(dev);

	अगर (cm_suspended)
		cm_suspended = false;

	अगर (cm_समयr_set) अणु
		kसमय_प्रकार reमुख्य;

		alarm_cancel(cm_समयr);
		cm_समयr_set = false;
		reमुख्य = alarm_expires_reमुख्यing(cm_समयr);
		cm_suspend_duration_ms -= kसमय_प्रकारo_ms(reमुख्य);
		schedule_work(&setup_polling);
	पूर्ण

	_cm_monitor(cm);

	device_set_wakeup_capable(cm->dev, false);
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops अक्षरger_manager_pm = अणु
	.prepare	= cm_suspend_prepare,
	.suspend_noirq	= cm_suspend_noirq,
	.complete	= cm_suspend_complete,
पूर्ण;

अटल काष्ठा platक्रमm_driver अक्षरger_manager_driver = अणु
	.driver = अणु
		.name = "charger-manager",
		.pm = &अक्षरger_manager_pm,
		.of_match_table = अक्षरger_manager_match,
	पूर्ण,
	.probe = अक्षरger_manager_probe,
	.हटाओ = अक्षरger_manager_हटाओ,
	.id_table = अक्षरger_manager_id,
पूर्ण;

अटल पूर्णांक __init अक्षरger_manager_init(व्योम)
अणु
	cm_wq = create_मुक्तzable_workqueue("charger_manager");
	अगर (unlikely(!cm_wq))
		वापस -ENOMEM;

	INIT_DELAYED_WORK(&cm_monitor_work, cm_monitor_poller);

	वापस platक्रमm_driver_रेजिस्टर(&अक्षरger_manager_driver);
पूर्ण
late_initcall(अक्षरger_manager_init);

अटल व्योम __निकास अक्षरger_manager_cleanup(व्योम)
अणु
	destroy_workqueue(cm_wq);
	cm_wq = शून्य;

	platक्रमm_driver_unरेजिस्टर(&अक्षरger_manager_driver);
पूर्ण
module_निकास(अक्षरger_manager_cleanup);

MODULE_AUTHOR("MyungJoo Ham <myungjoo.ham@samsung.com>");
MODULE_DESCRIPTION("Charger Manager");
MODULE_LICENSE("GPL");
