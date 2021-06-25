<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2011 Samsung Electronics Co., Ltd.
 * MyungJoo.Ham <myungjoo.ham@samsung.com>
 *
 * Charger Manager.
 * This framework enables to control and multiple अक्षरgers and to
 * monitor अक्षरging even in the context of suspend-to-RAM with
 * an पूर्णांकerface combining the अक्षरgers.
 *
**/

#अगर_अघोषित _CHARGER_MANAGER_H
#घोषणा _CHARGER_MANAGER_H

#समावेश <linux/घातer_supply.h>
#समावेश <linux/extcon.h>
#समावेश <linux/alarmसमयr.h>

क्रमागत data_source अणु
	CM_BATTERY_PRESENT,
	CM_NO_BATTERY,
	CM_FUEL_GAUGE,
	CM_CHARGER_STAT,
पूर्ण;

क्रमागत polling_modes अणु
	CM_POLL_DISABLE = 0,
	CM_POLL_ALWAYS,
	CM_POLL_EXTERNAL_POWER_ONLY,
	CM_POLL_CHARGING_ONLY,
पूर्ण;

क्रमागत cm_batt_temp अणु
	CM_BATT_OK = 0,
	CM_BATT_OVERHEAT,
	CM_BATT_COLD,
पूर्ण;

/**
 * काष्ठा अक्षरger_cable
 * @extcon_name: the name of extcon device.
 * @name: the name of the cable connector
 * @extcon_dev: the extcon device.
 * @wq: the workqueue to control अक्षरger according to the state of
 *	अक्षरger cable. If अक्षरger cable is attached, enable अक्षरger.
 *	But अगर अक्षरger cable is detached, disable अक्षरger.
 * @nb: the notअगरier block to receive changed state from EXTCON
 *	(External Connector) when अक्षरger cable is attached/detached.
 * @attached: the state of अक्षरger cable.
 *	true: the अक्षरger cable is attached
 *	false: the अक्षरger cable is detached
 * @अक्षरger: the instance of काष्ठा अक्षरger_regulator.
 * @cm: the Charger Manager representing the battery.
 */
काष्ठा अक्षरger_cable अणु
	स्थिर अक्षर *extcon_name;
	स्थिर अक्षर *name;
	काष्ठा extcon_dev *extcon_dev;
	u64 extcon_type;

	/* The अक्षरger-manager use Extcon framework */
	काष्ठा work_काष्ठा wq;
	काष्ठा notअगरier_block nb;

	/* The state of अक्षरger cable */
	bool attached;

	काष्ठा अक्षरger_regulator *अक्षरger;

	/*
	 * Set min/max current of regulator to protect over-current issue
	 * according to a kind of अक्षरger cable when cable is attached.
	 */
	पूर्णांक min_uA;
	पूर्णांक max_uA;

	काष्ठा अक्षरger_manager *cm;
पूर्ण;

/**
 * काष्ठा अक्षरger_regulator
 * @regulator_name: the name of regulator क्रम using अक्षरger.
 * @consumer: the regulator consumer क्रम the अक्षरger.
 * @बाह्यally_control:
 *	Set अगर the अक्षरger-manager cannot control अक्षरger,
 *	the अक्षरger will be मुख्यtained with disabled state.
 * @cables:
 *	the array of अक्षरger cables to enable/disable अक्षरger
 *	and set current limit according to स्थिरraपूर्णांक data of
 *	काष्ठा अक्षरger_cable अगर only अक्षरger cable included
 *	in the array of अक्षरger cables is attached/detached.
 * @num_cables: the number of अक्षरger cables.
 * @attr_g: Attribute group क्रम the अक्षरger(regulator)
 * @attr_name: "name" sysfs entry
 * @attr_state: "state" sysfs entry
 * @attr_बाह्यally_control: "externally_control" sysfs entry
 * @attrs: Arrays poपूर्णांकing to attr_name/state/बाह्यally_control क्रम attr_g
 */
काष्ठा अक्षरger_regulator अणु
	/* The name of regulator क्रम अक्षरging */
	स्थिर अक्षर *regulator_name;
	काष्ठा regulator *consumer;

	/* अक्षरger never on when प्रणाली is on */
	पूर्णांक बाह्यally_control;

	/*
	 * Store स्थिरraपूर्णांक inक्रमmation related to current limit,
	 * each cable have dअगरferent condition क्रम अक्षरging.
	 */
	काष्ठा अक्षरger_cable *cables;
	पूर्णांक num_cables;

	काष्ठा attribute_group attr_grp;
	काष्ठा device_attribute attr_name;
	काष्ठा device_attribute attr_state;
	काष्ठा device_attribute attr_बाह्यally_control;
	काष्ठा attribute *attrs[4];

	काष्ठा अक्षरger_manager *cm;
पूर्ण;

/**
 * काष्ठा अक्षरger_desc
 * @psy_name: the name of घातer-supply-class क्रम अक्षरger manager
 * @polling_mode:
 *	Determine which polling mode will be used
 * @fullbatt_vchkdrop_uV:
 *	Check voltage drop after the battery is fully अक्षरged.
 *	If it has dropped more than fullbatt_vchkdrop_uV
 *	CM will restart अक्षरging.
 * @fullbatt_uV: voltage in microvolt
 *	If VBATT >= fullbatt_uV, it is assumed to be full.
 * @fullbatt_soc: state of Charge in %
 *	If state of Charge >= fullbatt_soc, it is assumed to be full.
 * @fullbatt_full_capacity: full capacity measure
 *	If full capacity of battery >= fullbatt_full_capacity,
 *	it is assumed to be full.
 * @polling_पूर्णांकerval_ms: पूर्णांकerval in millisecond at which
 *	अक्षरger manager will monitor battery health
 * @battery_present:
 *	Specअगरy where inक्रमmation क्रम existence of battery can be obtained
 * @psy_अक्षरger_stat: the names of घातer-supply क्रम अक्षरgers
 * @num_अक्षरger_regulator: the number of entries in अक्षरger_regulators
 * @अक्षरger_regulators: array of अक्षरger regulators
 * @psy_fuel_gauge: the name of घातer-supply क्रम fuel gauge
 * @thermal_zone : the name of thermal zone क्रम battery
 * @temp_min : Minimum battery temperature क्रम अक्षरging.
 * @temp_max : Maximum battery temperature क्रम अक्षरging.
 * @temp_dअगरf : Temperature dअगरference to restart अक्षरging.
 * @measure_battery_temp:
 *	true: measure battery temperature
 *	false: measure ambient temperature
 * @अक्षरging_max_duration_ms: Maximum possible duration क्रम अक्षरging
 *	If whole अक्षरging duration exceed 'charging_max_duration_ms',
 *	cm stop अक्षरging.
 * @disअक्षरging_max_duration_ms:
 *	Maximum possible duration क्रम disअक्षरging with अक्षरger cable
 *	after full-batt. If disअक्षरging duration exceed 'disअक्षरging
 *	max_duration_ms', cm start अक्षरging.
 */
काष्ठा अक्षरger_desc अणु
	स्थिर अक्षर *psy_name;

	क्रमागत polling_modes polling_mode;
	अचिन्हित पूर्णांक polling_पूर्णांकerval_ms;

	अचिन्हित पूर्णांक fullbatt_vchkdrop_uV;
	अचिन्हित पूर्णांक fullbatt_uV;
	अचिन्हित पूर्णांक fullbatt_soc;
	अचिन्हित पूर्णांक fullbatt_full_capacity;

	क्रमागत data_source battery_present;

	स्थिर अक्षर **psy_अक्षरger_stat;

	पूर्णांक num_अक्षरger_regulators;
	काष्ठा अक्षरger_regulator *अक्षरger_regulators;
	स्थिर काष्ठा attribute_group **sysfs_groups;

	स्थिर अक्षर *psy_fuel_gauge;

	स्थिर अक्षर *thermal_zone;

	पूर्णांक temp_min;
	पूर्णांक temp_max;
	पूर्णांक temp_dअगरf;

	bool measure_battery_temp;

	u32 अक्षरging_max_duration_ms;
	u32 disअक्षरging_max_duration_ms;
पूर्ण;

#घोषणा PSY_NAME_MAX	30

/**
 * काष्ठा अक्षरger_manager
 * @entry: entry क्रम list
 * @dev: device poपूर्णांकer
 * @desc: instance of अक्षरger_desc
 * @fuel_gauge: घातer_supply क्रम fuel gauge
 * @अक्षरger_stat: array of घातer_supply क्रम अक्षरgers
 * @tzd_batt : thermal zone device क्रम battery
 * @अक्षरger_enabled: the state of अक्षरger
 * @emergency_stop:
 *	When setting true, stop अक्षरging
 * @psy_name_buf: the name of घातer-supply-class क्रम अक्षरger manager
 * @अक्षरger_psy: घातer_supply क्रम अक्षरger manager
 * @status_save_ext_pwr_inserted:
 *	saved status of बाह्यal घातer beक्रमe entering suspend-to-RAM
 * @status_save_batt:
 *	saved status of battery beक्रमe entering suspend-to-RAM
 * @अक्षरging_start_समय: saved start समय of enabling अक्षरging
 * @अक्षरging_end_समय: saved end समय of disabling अक्षरging
 * @battery_status: Current battery status
 */
काष्ठा अक्षरger_manager अणु
	काष्ठा list_head entry;
	काष्ठा device *dev;
	काष्ठा अक्षरger_desc *desc;

#अगर_घोषित CONFIG_THERMAL
	काष्ठा thermal_zone_device *tzd_batt;
#पूर्ण_अगर
	bool अक्षरger_enabled;

	पूर्णांक emergency_stop;

	अक्षर psy_name_buf[PSY_NAME_MAX + 1];
	काष्ठा घातer_supply_desc अक्षरger_psy_desc;
	काष्ठा घातer_supply *अक्षरger_psy;

	u64 अक्षरging_start_समय;
	u64 अक्षरging_end_समय;

	पूर्णांक battery_status;
पूर्ण;

#पूर्ण_अगर /* _CHARGER_MANAGER_H */
