<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  sbs.c - ACPI Smart Battery System Driver ($Revision: 2.0 $)
 *
 *  Copyright (c) 2007 Alexey Starikovskiy <astarikovskiy@suse.de>
 *  Copyright (c) 2005-2007 Vladimir Lebedev <vladimir.p.lebedev@पूर्णांकel.com>
 *  Copyright (c) 2005 Rich Townsend <rhdt@bartol.udel.edu>
 */

#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/kernel.h>

#समावेश <linux/acpi.h>
#समावेश <linux/समयr.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/delay.h>
#समावेश <linux/घातer_supply.h>
#समावेश <linux/platक्रमm_data/x86/apple.h>
#समावेश <acpi/battery.h>

#समावेश "sbshc.h"

#घोषणा PREFIX "ACPI: "

#घोषणा ACPI_SBS_CLASS			"sbs"
#घोषणा ACPI_AC_CLASS			"ac_adapter"
#घोषणा ACPI_SBS_DEVICE_NAME		"Smart Battery System"
#घोषणा ACPI_BATTERY_सूची_NAME		"BAT%i"
#घोषणा ACPI_AC_सूची_NAME		"AC0"

#घोषणा ACPI_SBS_NOTIFY_STATUS		0x80
#घोषणा ACPI_SBS_NOTIFY_INFO		0x81

MODULE_AUTHOR("Alexey Starikovskiy <astarikovskiy@suse.de>");
MODULE_DESCRIPTION("Smart Battery System ACPI interface driver");
MODULE_LICENSE("GPL");

अटल अचिन्हित पूर्णांक cache_समय = 1000;
module_param(cache_समय, uपूर्णांक, 0644);
MODULE_PARM_DESC(cache_समय, "cache time in milliseconds");

#घोषणा MAX_SBS_BAT			4
#घोषणा ACPI_SBS_BLOCK_MAX		32

अटल स्थिर काष्ठा acpi_device_id sbs_device_ids[] = अणु
	अणु"ACPI0002", 0पूर्ण,
	अणु"", 0पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(acpi, sbs_device_ids);

काष्ठा acpi_battery अणु
	काष्ठा घातer_supply *bat;
	काष्ठा घातer_supply_desc bat_desc;
	काष्ठा acpi_sbs *sbs;
	अचिन्हित दीर्घ update_समय;
	अक्षर name[8];
	अक्षर manufacturer_name[ACPI_SBS_BLOCK_MAX];
	अक्षर device_name[ACPI_SBS_BLOCK_MAX];
	अक्षर device_chemistry[ACPI_SBS_BLOCK_MAX];
	u16 alarm_capacity;
	u16 full_अक्षरge_capacity;
	u16 design_capacity;
	u16 design_voltage;
	u16 serial_number;
	u16 cycle_count;
	u16 temp_now;
	u16 voltage_now;
	s16 rate_now;
	s16 rate_avg;
	u16 capacity_now;
	u16 state_of_अक्षरge;
	u16 state;
	u16 mode;
	u16 spec;
	u8 id;
	u8 present:1;
	u8 have_sysfs_alarm:1;
पूर्ण;

#घोषणा to_acpi_battery(x) घातer_supply_get_drvdata(x)

काष्ठा acpi_sbs अणु
	काष्ठा घातer_supply *अक्षरger;
	काष्ठा acpi_device *device;
	काष्ठा acpi_smb_hc *hc;
	काष्ठा mutex lock;
	काष्ठा acpi_battery battery[MAX_SBS_BAT];
	u8 batteries_supported:4;
	u8 manager_present:1;
	u8 अक्षरger_present:1;
	u8 अक्षरger_exists:1;
पूर्ण;

#घोषणा to_acpi_sbs(x) घातer_supply_get_drvdata(x)

अटल पूर्णांक acpi_sbs_हटाओ(काष्ठा acpi_device *device);
अटल पूर्णांक acpi_battery_get_state(काष्ठा acpi_battery *battery);

अटल अंतरभूत पूर्णांक battery_scale(पूर्णांक log)
अणु
	पूर्णांक scale = 1;
	जबतक (log--)
		scale *= 10;
	वापस scale;
पूर्ण

अटल अंतरभूत पूर्णांक acpi_battery_vscale(काष्ठा acpi_battery *battery)
अणु
	वापस battery_scale((battery->spec & 0x0f00) >> 8);
पूर्ण

अटल अंतरभूत पूर्णांक acpi_battery_ipscale(काष्ठा acpi_battery *battery)
अणु
	वापस battery_scale((battery->spec & 0xf000) >> 12);
पूर्ण

अटल अंतरभूत पूर्णांक acpi_battery_mode(काष्ठा acpi_battery *battery)
अणु
	वापस (battery->mode & 0x8000);
पूर्ण

अटल अंतरभूत पूर्णांक acpi_battery_scale(काष्ठा acpi_battery *battery)
अणु
	वापस (acpi_battery_mode(battery) ? 10 : 1) *
	    acpi_battery_ipscale(battery);
पूर्ण

अटल पूर्णांक sbs_get_ac_property(काष्ठा घातer_supply *psy,
			       क्रमागत घातer_supply_property psp,
			       जोड़ घातer_supply_propval *val)
अणु
	काष्ठा acpi_sbs *sbs = to_acpi_sbs(psy);
	चयन (psp) अणु
	हाल POWER_SUPPLY_PROP_ONLINE:
		val->पूर्णांकval = sbs->अक्षरger_present;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक acpi_battery_technology(काष्ठा acpi_battery *battery)
अणु
	अगर (!strहालcmp("NiCd", battery->device_chemistry))
		वापस POWER_SUPPLY_TECHNOLOGY_NiCd;
	अगर (!strहालcmp("NiMH", battery->device_chemistry))
		वापस POWER_SUPPLY_TECHNOLOGY_NiMH;
	अगर (!strहालcmp("LION", battery->device_chemistry))
		वापस POWER_SUPPLY_TECHNOLOGY_LION;
	अगर (!strहालcmp("LiP", battery->device_chemistry))
		वापस POWER_SUPPLY_TECHNOLOGY_LIPO;
	वापस POWER_SUPPLY_TECHNOLOGY_UNKNOWN;
पूर्ण

अटल पूर्णांक acpi_sbs_battery_get_property(काष्ठा घातer_supply *psy,
					 क्रमागत घातer_supply_property psp,
					 जोड़ घातer_supply_propval *val)
अणु
	काष्ठा acpi_battery *battery = to_acpi_battery(psy);

	अगर ((!battery->present) && psp != POWER_SUPPLY_PROP_PRESENT)
		वापस -ENODEV;

	acpi_battery_get_state(battery);
	चयन (psp) अणु
	हाल POWER_SUPPLY_PROP_STATUS:
		अगर (battery->rate_now < 0)
			val->पूर्णांकval = POWER_SUPPLY_STATUS_DISCHARGING;
		अन्यथा अगर (battery->rate_now > 0)
			val->पूर्णांकval = POWER_SUPPLY_STATUS_CHARGING;
		अन्यथा
			val->पूर्णांकval = POWER_SUPPLY_STATUS_FULL;
		अवरोध;
	हाल POWER_SUPPLY_PROP_PRESENT:
		val->पूर्णांकval = battery->present;
		अवरोध;
	हाल POWER_SUPPLY_PROP_TECHNOLOGY:
		val->पूर्णांकval = acpi_battery_technology(battery);
		अवरोध;
	हाल POWER_SUPPLY_PROP_CYCLE_COUNT:
		val->पूर्णांकval = battery->cycle_count;
		अवरोध;
	हाल POWER_SUPPLY_PROP_VOLTAGE_MIN_DESIGN:
		val->पूर्णांकval = battery->design_voltage *
			acpi_battery_vscale(battery) * 1000;
		अवरोध;
	हाल POWER_SUPPLY_PROP_VOLTAGE_NOW:
		val->पूर्णांकval = battery->voltage_now *
				acpi_battery_vscale(battery) * 1000;
		अवरोध;
	हाल POWER_SUPPLY_PROP_CURRENT_NOW:
	हाल POWER_SUPPLY_PROP_POWER_NOW:
		val->पूर्णांकval = असल(battery->rate_now) *
				acpi_battery_ipscale(battery) * 1000;
		val->पूर्णांकval *= (acpi_battery_mode(battery)) ?
				(battery->voltage_now *
				acpi_battery_vscale(battery) / 1000) : 1;
		अवरोध;
	हाल POWER_SUPPLY_PROP_CURRENT_AVG:
	हाल POWER_SUPPLY_PROP_POWER_AVG:
		val->पूर्णांकval = असल(battery->rate_avg) *
				acpi_battery_ipscale(battery) * 1000;
		val->पूर्णांकval *= (acpi_battery_mode(battery)) ?
				(battery->voltage_now *
				acpi_battery_vscale(battery) / 1000) : 1;
		अवरोध;
	हाल POWER_SUPPLY_PROP_CAPACITY:
		val->पूर्णांकval = battery->state_of_अक्षरge;
		अवरोध;
	हाल POWER_SUPPLY_PROP_CHARGE_FULL_DESIGN:
	हाल POWER_SUPPLY_PROP_ENERGY_FULL_DESIGN:
		val->पूर्णांकval = battery->design_capacity *
			acpi_battery_scale(battery) * 1000;
		अवरोध;
	हाल POWER_SUPPLY_PROP_CHARGE_FULL:
	हाल POWER_SUPPLY_PROP_ENERGY_FULL:
		val->पूर्णांकval = battery->full_अक्षरge_capacity *
			acpi_battery_scale(battery) * 1000;
		अवरोध;
	हाल POWER_SUPPLY_PROP_CHARGE_NOW:
	हाल POWER_SUPPLY_PROP_ENERGY_NOW:
		val->पूर्णांकval = battery->capacity_now *
				acpi_battery_scale(battery) * 1000;
		अवरोध;
	हाल POWER_SUPPLY_PROP_TEMP:
		val->पूर्णांकval = battery->temp_now - 2730;	// dK -> dC
		अवरोध;
	हाल POWER_SUPPLY_PROP_MODEL_NAME:
		val->strval = battery->device_name;
		अवरोध;
	हाल POWER_SUPPLY_PROP_MANUFACTURER:
		val->strval = battery->manufacturer_name;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल क्रमागत घातer_supply_property sbs_ac_props[] = अणु
	POWER_SUPPLY_PROP_ONLINE,
पूर्ण;

अटल क्रमागत घातer_supply_property sbs_अक्षरge_battery_props[] = अणु
	POWER_SUPPLY_PROP_STATUS,
	POWER_SUPPLY_PROP_PRESENT,
	POWER_SUPPLY_PROP_TECHNOLOGY,
	POWER_SUPPLY_PROP_CYCLE_COUNT,
	POWER_SUPPLY_PROP_VOLTAGE_MIN_DESIGN,
	POWER_SUPPLY_PROP_VOLTAGE_NOW,
	POWER_SUPPLY_PROP_CURRENT_NOW,
	POWER_SUPPLY_PROP_CURRENT_AVG,
	POWER_SUPPLY_PROP_CAPACITY,
	POWER_SUPPLY_PROP_CHARGE_FULL_DESIGN,
	POWER_SUPPLY_PROP_CHARGE_FULL,
	POWER_SUPPLY_PROP_CHARGE_NOW,
	POWER_SUPPLY_PROP_TEMP,
	POWER_SUPPLY_PROP_MODEL_NAME,
	POWER_SUPPLY_PROP_MANUFACTURER,
पूर्ण;

अटल क्रमागत घातer_supply_property sbs_energy_battery_props[] = अणु
	POWER_SUPPLY_PROP_STATUS,
	POWER_SUPPLY_PROP_PRESENT,
	POWER_SUPPLY_PROP_TECHNOLOGY,
	POWER_SUPPLY_PROP_VOLTAGE_MIN_DESIGN,
	POWER_SUPPLY_PROP_VOLTAGE_NOW,
	POWER_SUPPLY_PROP_CURRENT_NOW,
	POWER_SUPPLY_PROP_CURRENT_AVG,
	POWER_SUPPLY_PROP_POWER_NOW,
	POWER_SUPPLY_PROP_POWER_AVG,
	POWER_SUPPLY_PROP_CAPACITY,
	POWER_SUPPLY_PROP_ENERGY_FULL_DESIGN,
	POWER_SUPPLY_PROP_ENERGY_FULL,
	POWER_SUPPLY_PROP_ENERGY_NOW,
	POWER_SUPPLY_PROP_TEMP,
	POWER_SUPPLY_PROP_MODEL_NAME,
	POWER_SUPPLY_PROP_MANUFACTURER,
पूर्ण;

अटल स्थिर काष्ठा घातer_supply_desc acpi_sbs_अक्षरger_desc = अणु
	.name		= "sbs-charger",
	.type		= POWER_SUPPLY_TYPE_MAINS,
	.properties	= sbs_ac_props,
	.num_properties	= ARRAY_SIZE(sbs_ac_props),
	.get_property	= sbs_get_ac_property,
पूर्ण;

/* --------------------------------------------------------------------------
                            Smart Battery System Management
   -------------------------------------------------------------------------- */

काष्ठा acpi_battery_पढ़ोer अणु
	u8 command;		/* command क्रम battery */
	u8 mode;		/* word or block? */
	माप_प्रकार offset;		/* offset inside काष्ठा acpi_sbs_battery */
पूर्ण;

अटल काष्ठा acpi_battery_पढ़ोer info_पढ़ोers[] = अणु
	अणु0x01, SMBUS_READ_WORD, दुरत्व(काष्ठा acpi_battery, alarm_capacity)पूर्ण,
	अणु0x03, SMBUS_READ_WORD, दुरत्व(काष्ठा acpi_battery, mode)पूर्ण,
	अणु0x10, SMBUS_READ_WORD, दुरत्व(काष्ठा acpi_battery, full_अक्षरge_capacity)पूर्ण,
	अणु0x17, SMBUS_READ_WORD, दुरत्व(काष्ठा acpi_battery, cycle_count)पूर्ण,
	अणु0x18, SMBUS_READ_WORD, दुरत्व(काष्ठा acpi_battery, design_capacity)पूर्ण,
	अणु0x19, SMBUS_READ_WORD, दुरत्व(काष्ठा acpi_battery, design_voltage)पूर्ण,
	अणु0x1a, SMBUS_READ_WORD, दुरत्व(काष्ठा acpi_battery, spec)पूर्ण,
	अणु0x1c, SMBUS_READ_WORD, दुरत्व(काष्ठा acpi_battery, serial_number)पूर्ण,
	अणु0x20, SMBUS_READ_BLOCK, दुरत्व(काष्ठा acpi_battery, manufacturer_name)पूर्ण,
	अणु0x21, SMBUS_READ_BLOCK, दुरत्व(काष्ठा acpi_battery, device_name)पूर्ण,
	अणु0x22, SMBUS_READ_BLOCK, दुरत्व(काष्ठा acpi_battery, device_chemistry)पूर्ण,
पूर्ण;

अटल काष्ठा acpi_battery_पढ़ोer state_पढ़ोers[] = अणु
	अणु0x08, SMBUS_READ_WORD, दुरत्व(काष्ठा acpi_battery, temp_now)पूर्ण,
	अणु0x09, SMBUS_READ_WORD, दुरत्व(काष्ठा acpi_battery, voltage_now)पूर्ण,
	अणु0x0a, SMBUS_READ_WORD, दुरत्व(काष्ठा acpi_battery, rate_now)पूर्ण,
	अणु0x0b, SMBUS_READ_WORD, दुरत्व(काष्ठा acpi_battery, rate_avg)पूर्ण,
	अणु0x0f, SMBUS_READ_WORD, दुरत्व(काष्ठा acpi_battery, capacity_now)पूर्ण,
	अणु0x0e, SMBUS_READ_WORD, दुरत्व(काष्ठा acpi_battery, state_of_अक्षरge)पूर्ण,
	अणु0x16, SMBUS_READ_WORD, दुरत्व(काष्ठा acpi_battery, state)पूर्ण,
पूर्ण;

अटल पूर्णांक acpi_manager_get_info(काष्ठा acpi_sbs *sbs)
अणु
	पूर्णांक result = 0;
	u16 battery_प्रणाली_info;

	result = acpi_smbus_पढ़ो(sbs->hc, SMBUS_READ_WORD, ACPI_SBS_MANAGER,
				 0x04, (u8 *)&battery_प्रणाली_info);
	अगर (!result)
		sbs->batteries_supported = battery_प्रणाली_info & 0x000f;
	वापस result;
पूर्ण

अटल पूर्णांक acpi_battery_get_info(काष्ठा acpi_battery *battery)
अणु
	पूर्णांक i, result = 0;

	क्रम (i = 0; i < ARRAY_SIZE(info_पढ़ोers); ++i) अणु
		result = acpi_smbus_पढ़ो(battery->sbs->hc,
					 info_पढ़ोers[i].mode,
					 ACPI_SBS_BATTERY,
					 info_पढ़ोers[i].command,
					 (u8 *) battery +
						info_पढ़ोers[i].offset);
		अगर (result)
			अवरोध;
	पूर्ण
	वापस result;
पूर्ण

अटल पूर्णांक acpi_battery_get_state(काष्ठा acpi_battery *battery)
अणु
	पूर्णांक i, result = 0;

	अगर (battery->update_समय &&
	    समय_beक्रमe(jअगरfies, battery->update_समय +
				msecs_to_jअगरfies(cache_समय)))
		वापस 0;
	क्रम (i = 0; i < ARRAY_SIZE(state_पढ़ोers); ++i) अणु
		result = acpi_smbus_पढ़ो(battery->sbs->hc,
					 state_पढ़ोers[i].mode,
					 ACPI_SBS_BATTERY,
					 state_पढ़ोers[i].command,
					 (u8 *)battery +
						state_पढ़ोers[i].offset);
		अगर (result)
			जाओ end;
	पूर्ण
      end:
	battery->update_समय = jअगरfies;
	वापस result;
पूर्ण

अटल पूर्णांक acpi_battery_get_alarm(काष्ठा acpi_battery *battery)
अणु
	वापस acpi_smbus_पढ़ो(battery->sbs->hc, SMBUS_READ_WORD,
				 ACPI_SBS_BATTERY, 0x01,
				 (u8 *)&battery->alarm_capacity);
पूर्ण

अटल पूर्णांक acpi_battery_set_alarm(काष्ठा acpi_battery *battery)
अणु
	काष्ठा acpi_sbs *sbs = battery->sbs;
	u16 value, sel = 1 << (battery->id + 12);

	पूर्णांक ret;


	अगर (sbs->manager_present) अणु
		ret = acpi_smbus_पढ़ो(sbs->hc, SMBUS_READ_WORD, ACPI_SBS_MANAGER,
				0x01, (u8 *)&value);
		अगर (ret)
			जाओ end;
		अगर ((value & 0xf000) != sel) अणु
			value &= 0x0fff;
			value |= sel;
			ret = acpi_smbus_ग_लिखो(sbs->hc, SMBUS_WRITE_WORD,
					 ACPI_SBS_MANAGER,
					 0x01, (u8 *)&value, 2);
			अगर (ret)
				जाओ end;
		पूर्ण
	पूर्ण
	ret = acpi_smbus_ग_लिखो(sbs->hc, SMBUS_WRITE_WORD, ACPI_SBS_BATTERY,
				0x01, (u8 *)&battery->alarm_capacity, 2);
      end:
	वापस ret;
पूर्ण

अटल पूर्णांक acpi_ac_get_present(काष्ठा acpi_sbs *sbs)
अणु
	पूर्णांक result;
	u16 status;

	result = acpi_smbus_पढ़ो(sbs->hc, SMBUS_READ_WORD, ACPI_SBS_CHARGER,
				 0x13, (u8 *) & status);

	अगर (result)
		वापस result;

	/*
	 * The spec requires that bit 4 always be 1. If it's not set, assume
	 * that the implementation करोesn't support an SBS अक्षरger.
	 *
	 * And on some MacBooks a status of 0xffff is always वापसed, no
	 * matter whether the अक्षरger is plugged in or not, which is also
	 * wrong, so ignore the SBS अक्षरger क्रम those too.
	 */
	अगर (!((status >> 4) & 0x1) || status == 0xffff)
		वापस -ENODEV;

	sbs->अक्षरger_present = (status >> 15) & 0x1;
	वापस 0;
पूर्ण

अटल sमाप_प्रकार acpi_battery_alarm_show(काष्ठा device *dev,
					काष्ठा device_attribute *attr,
					अक्षर *buf)
अणु
	काष्ठा acpi_battery *battery = to_acpi_battery(dev_get_drvdata(dev));
	acpi_battery_get_alarm(battery);
	वापस प्र_लिखो(buf, "%d\n", battery->alarm_capacity *
				acpi_battery_scale(battery) * 1000);
पूर्ण

अटल sमाप_प्रकार acpi_battery_alarm_store(काष्ठा device *dev,
					काष्ठा device_attribute *attr,
					स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	अचिन्हित दीर्घ x;
	काष्ठा acpi_battery *battery = to_acpi_battery(dev_get_drvdata(dev));
	अगर (माला_पूछो(buf, "%lu\n", &x) == 1)
		battery->alarm_capacity = x /
			(1000 * acpi_battery_scale(battery));
	अगर (battery->present)
		acpi_battery_set_alarm(battery);
	वापस count;
पूर्ण

अटल स्थिर काष्ठा device_attribute alarm_attr = अणु
	.attr = अणु.name = "alarm", .mode = 0644पूर्ण,
	.show = acpi_battery_alarm_show,
	.store = acpi_battery_alarm_store,
पूर्ण;

/* --------------------------------------------------------------------------
                                 Driver Interface
   -------------------------------------------------------------------------- */
अटल पूर्णांक acpi_battery_पढ़ो(काष्ठा acpi_battery *battery)
अणु
	पूर्णांक result = 0, saved_present = battery->present;
	u16 state;

	अगर (battery->sbs->manager_present) अणु
		result = acpi_smbus_पढ़ो(battery->sbs->hc, SMBUS_READ_WORD,
				ACPI_SBS_MANAGER, 0x01, (u8 *)&state);
		अगर (!result)
			battery->present = state & (1 << battery->id);
		state &= 0x0fff;
		state |= 1 << (battery->id + 12);
		acpi_smbus_ग_लिखो(battery->sbs->hc, SMBUS_WRITE_WORD,
				  ACPI_SBS_MANAGER, 0x01, (u8 *)&state, 2);
	पूर्ण अन्यथा अगर (battery->id == 0)
		battery->present = 1;

	अगर (result || !battery->present)
		वापस result;

	अगर (saved_present != battery->present) अणु
		battery->update_समय = 0;
		result = acpi_battery_get_info(battery);
		अगर (result) अणु
			battery->present = 0;
			वापस result;
		पूर्ण
	पूर्ण
	result = acpi_battery_get_state(battery);
	अगर (result)
		battery->present = 0;
	वापस result;
पूर्ण

/* Smart Battery */
अटल पूर्णांक acpi_battery_add(काष्ठा acpi_sbs *sbs, पूर्णांक id)
अणु
	काष्ठा acpi_battery *battery = &sbs->battery[id];
	काष्ठा घातer_supply_config psy_cfg = अणु .drv_data = battery, पूर्ण;
	पूर्णांक result;

	battery->id = id;
	battery->sbs = sbs;
	result = acpi_battery_पढ़ो(battery);
	अगर (result)
		वापस result;

	प्र_लिखो(battery->name, ACPI_BATTERY_सूची_NAME, id);
	battery->bat_desc.name = battery->name;
	battery->bat_desc.type = POWER_SUPPLY_TYPE_BATTERY;
	अगर (!acpi_battery_mode(battery)) अणु
		battery->bat_desc.properties = sbs_अक्षरge_battery_props;
		battery->bat_desc.num_properties =
		    ARRAY_SIZE(sbs_अक्षरge_battery_props);
	पूर्ण अन्यथा अणु
		battery->bat_desc.properties = sbs_energy_battery_props;
		battery->bat_desc.num_properties =
		    ARRAY_SIZE(sbs_energy_battery_props);
	पूर्ण
	battery->bat_desc.get_property = acpi_sbs_battery_get_property;
	battery->bat = घातer_supply_रेजिस्टर(&sbs->device->dev,
					&battery->bat_desc, &psy_cfg);
	अगर (IS_ERR(battery->bat)) अणु
		result = PTR_ERR(battery->bat);
		battery->bat = शून्य;
		जाओ end;
	पूर्ण

	result = device_create_file(&battery->bat->dev, &alarm_attr);
	अगर (result)
		जाओ end;
	battery->have_sysfs_alarm = 1;
      end:
	prपूर्णांकk(KERN_INFO PREFIX "%s [%s]: Battery Slot [%s] (battery %s)\n",
	       ACPI_SBS_DEVICE_NAME, acpi_device_bid(sbs->device),
	       battery->name, battery->present ? "present" : "absent");
	वापस result;
पूर्ण

अटल व्योम acpi_battery_हटाओ(काष्ठा acpi_sbs *sbs, पूर्णांक id)
अणु
	काष्ठा acpi_battery *battery = &sbs->battery[id];

	अगर (battery->bat) अणु
		अगर (battery->have_sysfs_alarm)
			device_हटाओ_file(&battery->bat->dev, &alarm_attr);
		घातer_supply_unरेजिस्टर(battery->bat);
	पूर्ण
पूर्ण

अटल पूर्णांक acpi_अक्षरger_add(काष्ठा acpi_sbs *sbs)
अणु
	पूर्णांक result;
	काष्ठा घातer_supply_config psy_cfg = अणु .drv_data = sbs, पूर्ण;

	result = acpi_ac_get_present(sbs);
	अगर (result)
		जाओ end;

	sbs->अक्षरger_exists = 1;
	sbs->अक्षरger = घातer_supply_रेजिस्टर(&sbs->device->dev,
					&acpi_sbs_अक्षरger_desc, &psy_cfg);
	अगर (IS_ERR(sbs->अक्षरger)) अणु
		result = PTR_ERR(sbs->अक्षरger);
		sbs->अक्षरger = शून्य;
	पूर्ण
	prपूर्णांकk(KERN_INFO PREFIX "%s [%s]: AC Adapter [%s] (%s)\n",
	       ACPI_SBS_DEVICE_NAME, acpi_device_bid(sbs->device),
	       ACPI_AC_सूची_NAME, sbs->अक्षरger_present ? "on-line" : "off-line");
      end:
	वापस result;
पूर्ण

अटल व्योम acpi_अक्षरger_हटाओ(काष्ठा acpi_sbs *sbs)
अणु
	अगर (sbs->अक्षरger)
		घातer_supply_unरेजिस्टर(sbs->अक्षरger);
पूर्ण

अटल व्योम acpi_sbs_callback(व्योम *context)
अणु
	पूर्णांक id;
	काष्ठा acpi_sbs *sbs = context;
	काष्ठा acpi_battery *bat;
	u8 saved_अक्षरger_state = sbs->अक्षरger_present;
	u8 saved_battery_state;

	अगर (sbs->अक्षरger_exists) अणु
		acpi_ac_get_present(sbs);
		अगर (sbs->अक्षरger_present != saved_अक्षरger_state)
			kobject_uevent(&sbs->अक्षरger->dev.kobj, KOBJ_CHANGE);
	पूर्ण

	अगर (sbs->manager_present) अणु
		क्रम (id = 0; id < MAX_SBS_BAT; ++id) अणु
			अगर (!(sbs->batteries_supported & (1 << id)))
				जारी;
			bat = &sbs->battery[id];
			saved_battery_state = bat->present;
			acpi_battery_पढ़ो(bat);
			अगर (saved_battery_state == bat->present)
				जारी;
			kobject_uevent(&bat->bat->dev.kobj, KOBJ_CHANGE);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक acpi_sbs_add(काष्ठा acpi_device *device)
अणु
	काष्ठा acpi_sbs *sbs;
	पूर्णांक result = 0;
	पूर्णांक id;

	sbs = kzalloc(माप(काष्ठा acpi_sbs), GFP_KERNEL);
	अगर (!sbs) अणु
		result = -ENOMEM;
		जाओ end;
	पूर्ण

	mutex_init(&sbs->lock);

	sbs->hc = acpi_driver_data(device->parent);
	sbs->device = device;
	म_नकल(acpi_device_name(device), ACPI_SBS_DEVICE_NAME);
	म_नकल(acpi_device_class(device), ACPI_SBS_CLASS);
	device->driver_data = sbs;

	result = acpi_अक्षरger_add(sbs);
	अगर (result && result != -ENODEV)
		जाओ end;

	result = 0;

	अगर (!x86_apple_machine) अणु
		result = acpi_manager_get_info(sbs);
		अगर (!result) अणु
			sbs->manager_present = 1;
			क्रम (id = 0; id < MAX_SBS_BAT; ++id)
				अगर ((sbs->batteries_supported & (1 << id)))
					acpi_battery_add(sbs, id);
		पूर्ण
	पूर्ण

	अगर (!sbs->manager_present)
		acpi_battery_add(sbs, 0);

	acpi_smbus_रेजिस्टर_callback(sbs->hc, acpi_sbs_callback, sbs);
      end:
	अगर (result)
		acpi_sbs_हटाओ(device);
	वापस result;
पूर्ण

अटल पूर्णांक acpi_sbs_हटाओ(काष्ठा acpi_device *device)
अणु
	काष्ठा acpi_sbs *sbs;
	पूर्णांक id;

	अगर (!device)
		वापस -EINVAL;
	sbs = acpi_driver_data(device);
	अगर (!sbs)
		वापस -EINVAL;
	mutex_lock(&sbs->lock);
	acpi_smbus_unरेजिस्टर_callback(sbs->hc);
	क्रम (id = 0; id < MAX_SBS_BAT; ++id)
		acpi_battery_हटाओ(sbs, id);
	acpi_अक्षरger_हटाओ(sbs);
	mutex_unlock(&sbs->lock);
	mutex_destroy(&sbs->lock);
	kमुक्त(sbs);
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक acpi_sbs_resume(काष्ठा device *dev)
अणु
	काष्ठा acpi_sbs *sbs;
	अगर (!dev)
		वापस -EINVAL;
	sbs = to_acpi_device(dev)->driver_data;
	acpi_sbs_callback(sbs);
	वापस 0;
पूर्ण
#अन्यथा
#घोषणा acpi_sbs_resume शून्य
#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(acpi_sbs_pm, शून्य, acpi_sbs_resume);

अटल काष्ठा acpi_driver acpi_sbs_driver = अणु
	.name = "sbs",
	.class = ACPI_SBS_CLASS,
	.ids = sbs_device_ids,
	.ops = अणु
		.add = acpi_sbs_add,
		.हटाओ = acpi_sbs_हटाओ,
		पूर्ण,
	.drv.pm = &acpi_sbs_pm,
पूर्ण;
module_acpi_driver(acpi_sbs_driver);
