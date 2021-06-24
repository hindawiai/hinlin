<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Battery driver क्रम 7th-generation Microsoft Surface devices via Surface
 * System Aggregator Module (SSAM).
 *
 * Copyright (C) 2019-2021 Maximilian Luz <luzmaximilian@gmail.com>
 */

#समावेश <यंत्र/unaligned.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/घातer_supply.h>
#समावेश <linux/sysfs.h>
#समावेश <linux/types.h>
#समावेश <linux/workqueue.h>

#समावेश <linux/surface_aggregator/device.h>


/* -- SAM पूर्णांकerface. -------------------------------------------------------- */

क्रमागत sam_event_cid_bat अणु
	SAM_EVENT_CID_BAT_BIX         = 0x15,
	SAM_EVENT_CID_BAT_BST         = 0x16,
	SAM_EVENT_CID_BAT_ADP         = 0x17,
	SAM_EVENT_CID_BAT_PROT        = 0x18,
	SAM_EVENT_CID_BAT_DPTF        = 0x53,
पूर्ण;

क्रमागत sam_battery_sta अणु
	SAM_BATTERY_STA_OK            = 0x0f,
	SAM_BATTERY_STA_PRESENT	      = 0x10,
पूर्ण;

क्रमागत sam_battery_state अणु
	SAM_BATTERY_STATE_DISCHARGING = BIT(0),
	SAM_BATTERY_STATE_CHARGING    = BIT(1),
	SAM_BATTERY_STATE_CRITICAL    = BIT(2),
पूर्ण;

क्रमागत sam_battery_घातer_unit अणु
	SAM_BATTERY_POWER_UNIT_mW     = 0,
	SAM_BATTERY_POWER_UNIT_mA     = 1,
पूर्ण;

/* Equivalent to data वापसed in ACPI _BIX method, revision 0. */
काष्ठा spwr_bix अणु
	u8  revision;
	__le32 घातer_unit;
	__le32 design_cap;
	__le32 last_full_अक्षरge_cap;
	__le32 technology;
	__le32 design_voltage;
	__le32 design_cap_warn;
	__le32 design_cap_low;
	__le32 cycle_count;
	__le32 measurement_accuracy;
	__le32 max_sampling_समय;
	__le32 min_sampling_समय;
	__le32 max_avg_पूर्णांकerval;
	__le32 min_avg_पूर्णांकerval;
	__le32 bat_cap_granularity_1;
	__le32 bat_cap_granularity_2;
	__u8 model[21];
	__u8 serial[11];
	__u8 type[5];
	__u8 oem_info[21];
पूर्ण __packed;

अटल_निश्चित(माप(काष्ठा spwr_bix) == 119);

/* Equivalent to data वापसed in ACPI _BST method. */
काष्ठा spwr_bst अणु
	__le32 state;
	__le32 present_rate;
	__le32 reमुख्यing_cap;
	__le32 present_voltage;
पूर्ण __packed;

अटल_निश्चित(माप(काष्ठा spwr_bst) == 16);

#घोषणा SPWR_BIX_REVISION		0
#घोषणा SPWR_BATTERY_VALUE_UNKNOWN	0xffffffff

/* Get battery status (_STA) */
SSAM_DEFINE_SYNC_REQUEST_CL_R(ssam_bat_get_sta, __le32, अणु
	.target_category = SSAM_SSH_TC_BAT,
	.command_id      = 0x01,
पूर्ण);

/* Get battery अटल inक्रमmation (_BIX). */
SSAM_DEFINE_SYNC_REQUEST_CL_R(ssam_bat_get_bix, काष्ठा spwr_bix, अणु
	.target_category = SSAM_SSH_TC_BAT,
	.command_id      = 0x02,
पूर्ण);

/* Get battery dynamic inक्रमmation (_BST). */
SSAM_DEFINE_SYNC_REQUEST_CL_R(ssam_bat_get_bst, काष्ठा spwr_bst, अणु
	.target_category = SSAM_SSH_TC_BAT,
	.command_id      = 0x03,
पूर्ण);

/* Set battery trip poपूर्णांक (_BTP). */
SSAM_DEFINE_SYNC_REQUEST_CL_W(ssam_bat_set_btp, __le32, अणु
	.target_category = SSAM_SSH_TC_BAT,
	.command_id      = 0x04,
पूर्ण);


/* -- Device काष्ठाures. ---------------------------------------------------- */

काष्ठा spwr_psy_properties अणु
	स्थिर अक्षर *name;
	काष्ठा ssam_event_registry registry;
पूर्ण;

काष्ठा spwr_battery_device अणु
	काष्ठा ssam_device *sdev;

	अक्षर name[32];
	काष्ठा घातer_supply *psy;
	काष्ठा घातer_supply_desc psy_desc;

	काष्ठा delayed_work update_work;

	काष्ठा ssam_event_notअगरier notअगर;

	काष्ठा mutex lock;  /* Guards access to state data below. */
	अचिन्हित दीर्घ बारtamp;

	__le32 sta;
	काष्ठा spwr_bix bix;
	काष्ठा spwr_bst bst;
	u32 alarm;
पूर्ण;


/* -- Module parameters. ---------------------------------------------------- */

अटल अचिन्हित पूर्णांक cache_समय = 1000;
module_param(cache_समय, uपूर्णांक, 0644);
MODULE_PARM_DESC(cache_समय, "battery state caching time in milliseconds [default: 1000]");


/* -- State management. ----------------------------------------------------- */

/*
 * Delay क्रम battery update quirk. See spwr_बाह्यal_घातer_changed() below
 * क्रम more details.
 */
#घोषणा SPWR_AC_BAT_UPDATE_DELAY	msecs_to_jअगरfies(5000)

अटल bool spwr_battery_present(काष्ठा spwr_battery_device *bat)
अणु
	lockdep_निश्चित_held(&bat->lock);

	वापस le32_to_cpu(bat->sta) & SAM_BATTERY_STA_PRESENT;
पूर्ण

अटल पूर्णांक spwr_battery_load_sta(काष्ठा spwr_battery_device *bat)
अणु
	lockdep_निश्चित_held(&bat->lock);

	वापस ssam_retry(ssam_bat_get_sta, bat->sdev, &bat->sta);
पूर्ण

अटल पूर्णांक spwr_battery_load_bix(काष्ठा spwr_battery_device *bat)
अणु
	पूर्णांक status;

	lockdep_निश्चित_held(&bat->lock);

	अगर (!spwr_battery_present(bat))
		वापस 0;

	status = ssam_retry(ssam_bat_get_bix, bat->sdev, &bat->bix);

	/* Enक्रमce शून्य terminated strings in हाल anything goes wrong... */
	bat->bix.model[ARRAY_SIZE(bat->bix.model) - 1] = 0;
	bat->bix.serial[ARRAY_SIZE(bat->bix.serial) - 1] = 0;
	bat->bix.type[ARRAY_SIZE(bat->bix.type) - 1] = 0;
	bat->bix.oem_info[ARRAY_SIZE(bat->bix.oem_info) - 1] = 0;

	वापस status;
पूर्ण

अटल पूर्णांक spwr_battery_load_bst(काष्ठा spwr_battery_device *bat)
अणु
	lockdep_निश्चित_held(&bat->lock);

	अगर (!spwr_battery_present(bat))
		वापस 0;

	वापस ssam_retry(ssam_bat_get_bst, bat->sdev, &bat->bst);
पूर्ण

अटल पूर्णांक spwr_battery_set_alarm_unlocked(काष्ठा spwr_battery_device *bat, u32 value)
अणु
	__le32 value_le = cpu_to_le32(value);

	lockdep_निश्चित_held(&bat->lock);

	bat->alarm = value;
	वापस ssam_retry(ssam_bat_set_btp, bat->sdev, &value_le);
पूर्ण

अटल पूर्णांक spwr_battery_update_bst_unlocked(काष्ठा spwr_battery_device *bat, bool cached)
अणु
	अचिन्हित दीर्घ cache_deadline = bat->बारtamp + msecs_to_jअगरfies(cache_समय);
	पूर्णांक status;

	lockdep_निश्चित_held(&bat->lock);

	अगर (cached && bat->बारtamp && समय_is_after_jअगरfies(cache_deadline))
		वापस 0;

	status = spwr_battery_load_sta(bat);
	अगर (status)
		वापस status;

	status = spwr_battery_load_bst(bat);
	अगर (status)
		वापस status;

	bat->बारtamp = jअगरfies;
	वापस 0;
पूर्ण

अटल पूर्णांक spwr_battery_update_bst(काष्ठा spwr_battery_device *bat, bool cached)
अणु
	पूर्णांक status;

	mutex_lock(&bat->lock);
	status = spwr_battery_update_bst_unlocked(bat, cached);
	mutex_unlock(&bat->lock);

	वापस status;
पूर्ण

अटल पूर्णांक spwr_battery_update_bix_unlocked(काष्ठा spwr_battery_device *bat)
अणु
	पूर्णांक status;

	lockdep_निश्चित_held(&bat->lock);

	status = spwr_battery_load_sta(bat);
	अगर (status)
		वापस status;

	status = spwr_battery_load_bix(bat);
	अगर (status)
		वापस status;

	status = spwr_battery_load_bst(bat);
	अगर (status)
		वापस status;

	अगर (bat->bix.revision != SPWR_BIX_REVISION)
		dev_warn(&bat->sdev->dev, "unsupported battery revision: %u\n", bat->bix.revision);

	bat->बारtamp = jअगरfies;
	वापस 0;
पूर्ण

अटल u32 sprw_battery_get_full_cap_safe(काष्ठा spwr_battery_device *bat)
अणु
	u32 full_cap = get_unaligned_le32(&bat->bix.last_full_अक्षरge_cap);

	lockdep_निश्चित_held(&bat->lock);

	अगर (full_cap == 0 || full_cap == SPWR_BATTERY_VALUE_UNKNOWN)
		full_cap = get_unaligned_le32(&bat->bix.design_cap);

	वापस full_cap;
पूर्ण

अटल bool spwr_battery_is_full(काष्ठा spwr_battery_device *bat)
अणु
	u32 state = get_unaligned_le32(&bat->bst.state);
	u32 full_cap = sprw_battery_get_full_cap_safe(bat);
	u32 reमुख्यing_cap = get_unaligned_le32(&bat->bst.reमुख्यing_cap);

	lockdep_निश्चित_held(&bat->lock);

	वापस full_cap != SPWR_BATTERY_VALUE_UNKNOWN && full_cap != 0 &&
		reमुख्यing_cap != SPWR_BATTERY_VALUE_UNKNOWN &&
		reमुख्यing_cap >= full_cap &&
		state == 0;
पूर्ण

अटल पूर्णांक spwr_battery_recheck_full(काष्ठा spwr_battery_device *bat)
अणु
	bool present;
	u32 unit;
	पूर्णांक status;

	mutex_lock(&bat->lock);
	unit = get_unaligned_le32(&bat->bix.घातer_unit);
	present = spwr_battery_present(bat);

	status = spwr_battery_update_bix_unlocked(bat);
	अगर (status)
		जाओ out;

	/* If battery has been attached, (re-)initialize alarm. */
	अगर (!present && spwr_battery_present(bat)) अणु
		u32 cap_warn = get_unaligned_le32(&bat->bix.design_cap_warn);

		status = spwr_battery_set_alarm_unlocked(bat, cap_warn);
		अगर (status)
			जाओ out;
	पूर्ण

	/*
	 * Warn अगर the unit has changed. This is something we genuinely करोn't
	 * expect to happen, so make this a big warning. If it करोes, we'll
	 * need to add support क्रम it.
	 */
	WARN_ON(unit != get_unaligned_le32(&bat->bix.घातer_unit));

out:
	mutex_unlock(&bat->lock);

	अगर (!status)
		घातer_supply_changed(bat->psy);

	वापस status;
पूर्ण

अटल पूर्णांक spwr_battery_recheck_status(काष्ठा spwr_battery_device *bat)
अणु
	पूर्णांक status;

	status = spwr_battery_update_bst(bat, false);
	अगर (!status)
		घातer_supply_changed(bat->psy);

	वापस status;
पूर्ण

अटल u32 spwr_notअगरy_bat(काष्ठा ssam_event_notअगरier *nf, स्थिर काष्ठा ssam_event *event)
अणु
	काष्ठा spwr_battery_device *bat = container_of(nf, काष्ठा spwr_battery_device, notअगर);
	पूर्णांक status;

	dev_dbg(&bat->sdev->dev, "power event (cid = %#04x, iid = %#04x, tid = %#04x)\n",
		event->command_id, event->instance_id, event->target_id);

	चयन (event->command_id) अणु
	हाल SAM_EVENT_CID_BAT_BIX:
		status = spwr_battery_recheck_full(bat);
		अवरोध;

	हाल SAM_EVENT_CID_BAT_BST:
		status = spwr_battery_recheck_status(bat);
		अवरोध;

	हाल SAM_EVENT_CID_BAT_PROT:
		/*
		 * TODO: Implement support क्रम battery protection status change
		 *       event.
		 */
		status = 0;
		अवरोध;

	हाल SAM_EVENT_CID_BAT_DPTF:
		/*
		 * TODO: Implement support क्रम DPTF event.
		 */
		status = 0;
		अवरोध;

	शेष:
		वापस 0;
	पूर्ण

	वापस ssam_notअगरier_from_त्रुटि_सं(status) | SSAM_NOTIF_HANDLED;
पूर्ण

अटल व्योम spwr_battery_update_bst_workfn(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा delayed_work *dwork = to_delayed_work(work);
	काष्ठा spwr_battery_device *bat;
	पूर्णांक status;

	bat = container_of(dwork, काष्ठा spwr_battery_device, update_work);

	status = spwr_battery_update_bst(bat, false);
	अगर (status) अणु
		dev_err(&bat->sdev->dev, "failed to update battery state: %d\n", status);
		वापस;
	पूर्ण

	घातer_supply_changed(bat->psy);
पूर्ण

अटल व्योम spwr_बाह्यal_घातer_changed(काष्ठा घातer_supply *psy)
अणु
	काष्ठा spwr_battery_device *bat = घातer_supply_get_drvdata(psy);

	/*
	 * Handle battery update quirk: When the battery is fully अक्षरged (or
	 * अक्षरged up to the limit imposed by the UEFI battery limit) and the
	 * adapter is plugged in or हटाओd, the EC करोes not send a separate
	 * event क्रम the state (अक्षरging/disअक्षरging) change. Furthermore it
	 * may take some समय until the state is updated on the battery.
	 * Schedule an update to solve this.
	 */

	schedule_delayed_work(&bat->update_work, SPWR_AC_BAT_UPDATE_DELAY);
पूर्ण


/* -- Properties. ----------------------------------------------------------- */

अटल स्थिर क्रमागत घातer_supply_property spwr_battery_props_chg[] = अणु
	POWER_SUPPLY_PROP_STATUS,
	POWER_SUPPLY_PROP_PRESENT,
	POWER_SUPPLY_PROP_TECHNOLOGY,
	POWER_SUPPLY_PROP_CYCLE_COUNT,
	POWER_SUPPLY_PROP_VOLTAGE_MIN_DESIGN,
	POWER_SUPPLY_PROP_VOLTAGE_NOW,
	POWER_SUPPLY_PROP_CURRENT_NOW,
	POWER_SUPPLY_PROP_CHARGE_FULL_DESIGN,
	POWER_SUPPLY_PROP_CHARGE_FULL,
	POWER_SUPPLY_PROP_CHARGE_NOW,
	POWER_SUPPLY_PROP_CAPACITY,
	POWER_SUPPLY_PROP_CAPACITY_LEVEL,
	POWER_SUPPLY_PROP_MODEL_NAME,
	POWER_SUPPLY_PROP_MANUFACTURER,
	POWER_SUPPLY_PROP_SERIAL_NUMBER,
पूर्ण;

अटल स्थिर क्रमागत घातer_supply_property spwr_battery_props_eng[] = अणु
	POWER_SUPPLY_PROP_STATUS,
	POWER_SUPPLY_PROP_PRESENT,
	POWER_SUPPLY_PROP_TECHNOLOGY,
	POWER_SUPPLY_PROP_CYCLE_COUNT,
	POWER_SUPPLY_PROP_VOLTAGE_MIN_DESIGN,
	POWER_SUPPLY_PROP_VOLTAGE_NOW,
	POWER_SUPPLY_PROP_POWER_NOW,
	POWER_SUPPLY_PROP_ENERGY_FULL_DESIGN,
	POWER_SUPPLY_PROP_ENERGY_FULL,
	POWER_SUPPLY_PROP_ENERGY_NOW,
	POWER_SUPPLY_PROP_CAPACITY,
	POWER_SUPPLY_PROP_CAPACITY_LEVEL,
	POWER_SUPPLY_PROP_MODEL_NAME,
	POWER_SUPPLY_PROP_MANUFACTURER,
	POWER_SUPPLY_PROP_SERIAL_NUMBER,
पूर्ण;

अटल पूर्णांक spwr_battery_prop_status(काष्ठा spwr_battery_device *bat)
अणु
	u32 state = get_unaligned_le32(&bat->bst.state);
	u32 present_rate = get_unaligned_le32(&bat->bst.present_rate);

	lockdep_निश्चित_held(&bat->lock);

	अगर (state & SAM_BATTERY_STATE_DISCHARGING)
		वापस POWER_SUPPLY_STATUS_DISCHARGING;

	अगर (state & SAM_BATTERY_STATE_CHARGING)
		वापस POWER_SUPPLY_STATUS_CHARGING;

	अगर (spwr_battery_is_full(bat))
		वापस POWER_SUPPLY_STATUS_FULL;

	अगर (present_rate == 0)
		वापस POWER_SUPPLY_STATUS_NOT_CHARGING;

	वापस POWER_SUPPLY_STATUS_UNKNOWN;
पूर्ण

अटल पूर्णांक spwr_battery_prop_technology(काष्ठा spwr_battery_device *bat)
अणु
	lockdep_निश्चित_held(&bat->lock);

	अगर (!strहालcmp("NiCd", bat->bix.type))
		वापस POWER_SUPPLY_TECHNOLOGY_NiCd;

	अगर (!strहालcmp("NiMH", bat->bix.type))
		वापस POWER_SUPPLY_TECHNOLOGY_NiMH;

	अगर (!strहालcmp("LION", bat->bix.type))
		वापस POWER_SUPPLY_TECHNOLOGY_LION;

	अगर (!strnहालcmp("LI-ION", bat->bix.type, 6))
		वापस POWER_SUPPLY_TECHNOLOGY_LION;

	अगर (!strहालcmp("LiP", bat->bix.type))
		वापस POWER_SUPPLY_TECHNOLOGY_LIPO;

	वापस POWER_SUPPLY_TECHNOLOGY_UNKNOWN;
पूर्ण

अटल पूर्णांक spwr_battery_prop_capacity(काष्ठा spwr_battery_device *bat)
अणु
	u32 full_cap = sprw_battery_get_full_cap_safe(bat);
	u32 reमुख्यing_cap = get_unaligned_le32(&bat->bst.reमुख्यing_cap);

	lockdep_निश्चित_held(&bat->lock);

	अगर (full_cap == 0 || full_cap == SPWR_BATTERY_VALUE_UNKNOWN)
		वापस -ENODATA;

	अगर (reमुख्यing_cap == SPWR_BATTERY_VALUE_UNKNOWN)
		वापस -ENODATA;

	वापस reमुख्यing_cap * 100 / full_cap;
पूर्ण

अटल पूर्णांक spwr_battery_prop_capacity_level(काष्ठा spwr_battery_device *bat)
अणु
	u32 state = get_unaligned_le32(&bat->bst.state);
	u32 reमुख्यing_cap = get_unaligned_le32(&bat->bst.reमुख्यing_cap);

	lockdep_निश्चित_held(&bat->lock);

	अगर (state & SAM_BATTERY_STATE_CRITICAL)
		वापस POWER_SUPPLY_CAPACITY_LEVEL_CRITICAL;

	अगर (spwr_battery_is_full(bat))
		वापस POWER_SUPPLY_CAPACITY_LEVEL_FULL;

	अगर (reमुख्यing_cap <= bat->alarm)
		वापस POWER_SUPPLY_CAPACITY_LEVEL_LOW;

	वापस POWER_SUPPLY_CAPACITY_LEVEL_NORMAL;
पूर्ण

अटल पूर्णांक spwr_battery_get_property(काष्ठा घातer_supply *psy, क्रमागत घातer_supply_property psp,
				     जोड़ घातer_supply_propval *val)
अणु
	काष्ठा spwr_battery_device *bat = घातer_supply_get_drvdata(psy);
	u32 value;
	पूर्णांक status;

	mutex_lock(&bat->lock);

	status = spwr_battery_update_bst_unlocked(bat, true);
	अगर (status)
		जाओ out;

	/* Abort अगर battery is not present. */
	अगर (!spwr_battery_present(bat) && psp != POWER_SUPPLY_PROP_PRESENT) अणु
		status = -ENODEV;
		जाओ out;
	पूर्ण

	चयन (psp) अणु
	हाल POWER_SUPPLY_PROP_STATUS:
		val->पूर्णांकval = spwr_battery_prop_status(bat);
		अवरोध;

	हाल POWER_SUPPLY_PROP_PRESENT:
		val->पूर्णांकval = spwr_battery_present(bat);
		अवरोध;

	हाल POWER_SUPPLY_PROP_TECHNOLOGY:
		val->पूर्णांकval = spwr_battery_prop_technology(bat);
		अवरोध;

	हाल POWER_SUPPLY_PROP_CYCLE_COUNT:
		value = get_unaligned_le32(&bat->bix.cycle_count);
		अगर (value != SPWR_BATTERY_VALUE_UNKNOWN)
			val->पूर्णांकval = value;
		अन्यथा
			status = -ENODATA;
		अवरोध;

	हाल POWER_SUPPLY_PROP_VOLTAGE_MIN_DESIGN:
		value = get_unaligned_le32(&bat->bix.design_voltage);
		अगर (value != SPWR_BATTERY_VALUE_UNKNOWN)
			val->पूर्णांकval = value * 1000;
		अन्यथा
			status = -ENODATA;
		अवरोध;

	हाल POWER_SUPPLY_PROP_VOLTAGE_NOW:
		value = get_unaligned_le32(&bat->bst.present_voltage);
		अगर (value != SPWR_BATTERY_VALUE_UNKNOWN)
			val->पूर्णांकval = value * 1000;
		अन्यथा
			status = -ENODATA;
		अवरोध;

	हाल POWER_SUPPLY_PROP_CURRENT_NOW:
	हाल POWER_SUPPLY_PROP_POWER_NOW:
		value = get_unaligned_le32(&bat->bst.present_rate);
		अगर (value != SPWR_BATTERY_VALUE_UNKNOWN)
			val->पूर्णांकval = value * 1000;
		अन्यथा
			status = -ENODATA;
		अवरोध;

	हाल POWER_SUPPLY_PROP_CHARGE_FULL_DESIGN:
	हाल POWER_SUPPLY_PROP_ENERGY_FULL_DESIGN:
		value = get_unaligned_le32(&bat->bix.design_cap);
		अगर (value != SPWR_BATTERY_VALUE_UNKNOWN)
			val->पूर्णांकval = value * 1000;
		अन्यथा
			status = -ENODATA;
		अवरोध;

	हाल POWER_SUPPLY_PROP_CHARGE_FULL:
	हाल POWER_SUPPLY_PROP_ENERGY_FULL:
		value = get_unaligned_le32(&bat->bix.last_full_अक्षरge_cap);
		अगर (value != SPWR_BATTERY_VALUE_UNKNOWN)
			val->पूर्णांकval = value * 1000;
		अन्यथा
			status = -ENODATA;
		अवरोध;

	हाल POWER_SUPPLY_PROP_CHARGE_NOW:
	हाल POWER_SUPPLY_PROP_ENERGY_NOW:
		value = get_unaligned_le32(&bat->bst.reमुख्यing_cap);
		अगर (value != SPWR_BATTERY_VALUE_UNKNOWN)
			val->पूर्णांकval = value * 1000;
		अन्यथा
			status = -ENODATA;
		अवरोध;

	हाल POWER_SUPPLY_PROP_CAPACITY:
		val->पूर्णांकval = spwr_battery_prop_capacity(bat);
		अवरोध;

	हाल POWER_SUPPLY_PROP_CAPACITY_LEVEL:
		val->पूर्णांकval = spwr_battery_prop_capacity_level(bat);
		अवरोध;

	हाल POWER_SUPPLY_PROP_MODEL_NAME:
		val->strval = bat->bix.model;
		अवरोध;

	हाल POWER_SUPPLY_PROP_MANUFACTURER:
		val->strval = bat->bix.oem_info;
		अवरोध;

	हाल POWER_SUPPLY_PROP_SERIAL_NUMBER:
		val->strval = bat->bix.serial;
		अवरोध;

	शेष:
		status = -EINVAL;
		अवरोध;
	पूर्ण

out:
	mutex_unlock(&bat->lock);
	वापस status;
पूर्ण


/* -- Alarm attribute. ------------------------------------------------------ */

अटल sमाप_प्रकार alarm_show(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा घातer_supply *psy = dev_get_drvdata(dev);
	काष्ठा spwr_battery_device *bat = घातer_supply_get_drvdata(psy);
	पूर्णांक status;

	mutex_lock(&bat->lock);
	status = sysfs_emit(buf, "%d\n", bat->alarm * 1000);
	mutex_unlock(&bat->lock);

	वापस status;
पूर्ण

अटल sमाप_प्रकार alarm_store(काष्ठा device *dev, काष्ठा device_attribute *attr, स्थिर अक्षर *buf,
			   माप_प्रकार count)
अणु
	काष्ठा घातer_supply *psy = dev_get_drvdata(dev);
	काष्ठा spwr_battery_device *bat = घातer_supply_get_drvdata(psy);
	अचिन्हित दीर्घ value;
	पूर्णांक status;

	status = kम_से_अदीर्घ(buf, 0, &value);
	अगर (status)
		वापस status;

	mutex_lock(&bat->lock);

	अगर (!spwr_battery_present(bat)) अणु
		mutex_unlock(&bat->lock);
		वापस -ENODEV;
	पूर्ण

	status = spwr_battery_set_alarm_unlocked(bat, value / 1000);
	अगर (status) अणु
		mutex_unlock(&bat->lock);
		वापस status;
	पूर्ण

	mutex_unlock(&bat->lock);
	वापस count;
पूर्ण

अटल DEVICE_ATTR_RW(alarm);

अटल काष्ठा attribute *spwr_battery_attrs[] = अणु
	&dev_attr_alarm.attr,
	शून्य,
पूर्ण;
ATTRIBUTE_GROUPS(spwr_battery);


/* -- Device setup. --------------------------------------------------------- */

अटल व्योम spwr_battery_init(काष्ठा spwr_battery_device *bat, काष्ठा ssam_device *sdev,
			      काष्ठा ssam_event_registry registry, स्थिर अक्षर *name)
अणु
	mutex_init(&bat->lock);
	म_नकलन(bat->name, name, ARRAY_SIZE(bat->name) - 1);

	bat->sdev = sdev;

	bat->notअगर.base.priority = 1;
	bat->notअगर.base.fn = spwr_notअगरy_bat;
	bat->notअगर.event.reg = registry;
	bat->notअगर.event.id.target_category = sdev->uid.category;
	bat->notअगर.event.id.instance = 0;
	bat->notअगर.event.mask = SSAM_EVENT_MASK_STRICT;
	bat->notअगर.event.flags = SSAM_EVENT_SEQUENCED;

	bat->psy_desc.name = bat->name;
	bat->psy_desc.type = POWER_SUPPLY_TYPE_BATTERY;
	bat->psy_desc.get_property = spwr_battery_get_property;

	INIT_DELAYED_WORK(&bat->update_work, spwr_battery_update_bst_workfn);
पूर्ण

अटल पूर्णांक spwr_battery_रेजिस्टर(काष्ठा spwr_battery_device *bat)
अणु
	काष्ठा घातer_supply_config psy_cfg = अणुपूर्ण;
	__le32 sta;
	पूर्णांक status;

	/* Make sure the device is there and functioning properly. */
	status = ssam_retry(ssam_bat_get_sta, bat->sdev, &sta);
	अगर (status)
		वापस status;

	अगर ((le32_to_cpu(sta) & SAM_BATTERY_STA_OK) != SAM_BATTERY_STA_OK)
		वापस -ENODEV;

	/* Satisfy lockdep although we are in an exclusive context here. */
	mutex_lock(&bat->lock);

	status = spwr_battery_update_bix_unlocked(bat);
	अगर (status) अणु
		mutex_unlock(&bat->lock);
		वापस status;
	पूर्ण

	अगर (spwr_battery_present(bat)) अणु
		u32 cap_warn = get_unaligned_le32(&bat->bix.design_cap_warn);

		status = spwr_battery_set_alarm_unlocked(bat, cap_warn);
		अगर (status) अणु
			mutex_unlock(&bat->lock);
			वापस status;
		पूर्ण
	पूर्ण

	mutex_unlock(&bat->lock);

	bat->psy_desc.बाह्यal_घातer_changed = spwr_बाह्यal_घातer_changed;

	चयन (get_unaligned_le32(&bat->bix.घातer_unit)) अणु
	हाल SAM_BATTERY_POWER_UNIT_mW:
		bat->psy_desc.properties = spwr_battery_props_eng;
		bat->psy_desc.num_properties = ARRAY_SIZE(spwr_battery_props_eng);
		अवरोध;

	हाल SAM_BATTERY_POWER_UNIT_mA:
		bat->psy_desc.properties = spwr_battery_props_chg;
		bat->psy_desc.num_properties = ARRAY_SIZE(spwr_battery_props_chg);
		अवरोध;

	शेष:
		dev_err(&bat->sdev->dev, "unsupported battery power unit: %u\n",
			get_unaligned_le32(&bat->bix.घातer_unit));
		वापस -EINVAL;
	पूर्ण

	psy_cfg.drv_data = bat;
	psy_cfg.attr_grp = spwr_battery_groups;

	bat->psy = devm_घातer_supply_रेजिस्टर(&bat->sdev->dev, &bat->psy_desc, &psy_cfg);
	अगर (IS_ERR(bat->psy))
		वापस PTR_ERR(bat->psy);

	वापस ssam_notअगरier_रेजिस्टर(bat->sdev->ctrl, &bat->notअगर);
पूर्ण


/* -- Driver setup. --------------------------------------------------------- */

अटल पूर्णांक __maybe_unused surface_battery_resume(काष्ठा device *dev)
अणु
	वापस spwr_battery_recheck_full(dev_get_drvdata(dev));
पूर्ण
अटल SIMPLE_DEV_PM_OPS(surface_battery_pm_ops, शून्य, surface_battery_resume);

अटल पूर्णांक surface_battery_probe(काष्ठा ssam_device *sdev)
अणु
	स्थिर काष्ठा spwr_psy_properties *p;
	काष्ठा spwr_battery_device *bat;

	p = ssam_device_get_match_data(sdev);
	अगर (!p)
		वापस -ENODEV;

	bat = devm_kzalloc(&sdev->dev, माप(*bat), GFP_KERNEL);
	अगर (!bat)
		वापस -ENOMEM;

	spwr_battery_init(bat, sdev, p->registry, p->name);
	ssam_device_set_drvdata(sdev, bat);

	वापस spwr_battery_रेजिस्टर(bat);
पूर्ण

अटल व्योम surface_battery_हटाओ(काष्ठा ssam_device *sdev)
अणु
	काष्ठा spwr_battery_device *bat = ssam_device_get_drvdata(sdev);

	ssam_notअगरier_unरेजिस्टर(sdev->ctrl, &bat->notअगर);
	cancel_delayed_work_sync(&bat->update_work);
पूर्ण

अटल स्थिर काष्ठा spwr_psy_properties spwr_psy_props_bat1 = अणु
	.name = "BAT1",
	.registry = SSAM_EVENT_REGISTRY_SAM,
पूर्ण;

अटल स्थिर काष्ठा spwr_psy_properties spwr_psy_props_bat2_sb3 = अणु
	.name = "BAT2",
	.registry = SSAM_EVENT_REGISTRY_KIP,
पूर्ण;

अटल स्थिर काष्ठा ssam_device_id surface_battery_match[] = अणु
	अणु SSAM_SDEV(BAT, 0x01, 0x01, 0x00), (अचिन्हित दीर्घ)&spwr_psy_props_bat1     पूर्ण,
	अणु SSAM_SDEV(BAT, 0x02, 0x01, 0x00), (अचिन्हित दीर्घ)&spwr_psy_props_bat2_sb3 पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(ssam, surface_battery_match);

अटल काष्ठा ssam_device_driver surface_battery_driver = अणु
	.probe = surface_battery_probe,
	.हटाओ = surface_battery_हटाओ,
	.match_table = surface_battery_match,
	.driver = अणु
		.name = "surface_battery",
		.pm = &surface_battery_pm_ops,
		.probe_type = PROBE_PREFER_ASYNCHRONOUS,
	पूर्ण,
पूर्ण;
module_ssam_device_driver(surface_battery_driver);

MODULE_AUTHOR("Maximilian Luz <luzmaximilian@gmail.com>");
MODULE_DESCRIPTION("Battery driver for Surface System Aggregator Module");
MODULE_LICENSE("GPL");
