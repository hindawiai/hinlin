<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  battery.c - ACPI Battery Driver (Revision: 2.0)
 *
 *  Copyright (C) 2007 Alexey Starikovskiy <astarikovskiy@suse.de>
 *  Copyright (C) 2004-2007 Vladimir Lebedev <vladimir.p.lebedev@पूर्णांकel.com>
 *  Copyright (C) 2001, 2002 Andy Grover <andrew.grover@पूर्णांकel.com>
 *  Copyright (C) 2001, 2002 Paul Diefenbaugh <paul.s.diefenbaugh@पूर्णांकel.com>
 */

#घोषणा pr_fmt(fmt) "ACPI: battery: " fmt

#समावेश <linux/async.h>
#समावेश <linux/delay.h>
#समावेश <linux/dmi.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/kernel.h>
#समावेश <linux/list.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/slab.h>
#समावेश <linux/suspend.h>
#समावेश <linux/types.h>

#समावेश <यंत्र/unaligned.h>

#समावेश <linux/acpi.h>
#समावेश <linux/घातer_supply.h>

#समावेश <acpi/battery.h>

#घोषणा ACPI_BATTERY_VALUE_UNKNOWN 0xFFFFFFFF
#घोषणा ACPI_BATTERY_CAPACITY_VALID(capacity) \
	((capacity) != 0 && (capacity) != ACPI_BATTERY_VALUE_UNKNOWN)

#घोषणा ACPI_BATTERY_DEVICE_NAME	"Battery"

/* Battery घातer unit: 0 means mW, 1 means mA */
#घोषणा ACPI_BATTERY_POWER_UNIT_MA	1

#घोषणा ACPI_BATTERY_STATE_DISCHARGING	0x1
#घोषणा ACPI_BATTERY_STATE_CHARGING	0x2
#घोषणा ACPI_BATTERY_STATE_CRITICAL	0x4

MODULE_AUTHOR("Paul Diefenbaugh");
MODULE_AUTHOR("Alexey Starikovskiy <astarikovskiy@suse.de>");
MODULE_DESCRIPTION("ACPI Battery Driver");
MODULE_LICENSE("GPL");

अटल async_cookie_t async_cookie;
अटल bool battery_driver_रेजिस्टरed;
अटल पूर्णांक battery_bix_broken_package;
अटल पूर्णांक battery_notअगरication_delay_ms;
अटल पूर्णांक battery_ac_is_broken;
अटल पूर्णांक battery_check_pmic = 1;
अटल अचिन्हित पूर्णांक cache_समय = 1000;
module_param(cache_समय, uपूर्णांक, 0644);
MODULE_PARM_DESC(cache_समय, "cache time in milliseconds");

अटल स्थिर काष्ठा acpi_device_id battery_device_ids[] = अणु
	अणु"PNP0C0A", 0पूर्ण,
	अणु"", 0पूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(acpi, battery_device_ids);

/* Lists of PMIC ACPI HIDs with an (often better) native battery driver */
अटल स्थिर अक्षर * स्थिर acpi_battery_blacklist[] = अणु
	"INT33F4", /* X-Powers AXP288 PMIC */
पूर्ण;

क्रमागत अणु
	ACPI_BATTERY_ALARM_PRESENT,
	ACPI_BATTERY_XINFO_PRESENT,
	ACPI_BATTERY_QUIRK_PERCENTAGE_CAPACITY,
	/* On Lenovo Thinkpad models from 2010 and 2011, the घातer unit
	 * चयनes between mWh and mAh depending on whether the प्रणाली
	 * is running on battery or not.  When mAh is the unit, most
	 * reported values are incorrect and need to be adjusted by
	 * 10000/design_voltage.  Verअगरied on x201, t410, t410s, and x220.
	 * Pre-2010 and 2012 models appear to always report in mWh and
	 * are thus unaffected (tested with t42, t61, t500, x200, x300,
	 * and x230).  Also, in mid-2012 Lenovo issued a BIOS update क्रम
	 *  the 2011 models that fixes the issue (tested on x220 with a
	 * post-1.29 BIOS), but as of Nov. 2012, no such update is
	 * available क्रम the 2010 models.
	 */
	ACPI_BATTERY_QUIRK_THINKPAD_MAH,
	/* क्रम batteries reporting current capacity with design capacity
	 * on a full अक्षरge, but showing degradation in full अक्षरge cap.
	 */
	ACPI_BATTERY_QUIRK_DEGRADED_FULL_CHARGE,
पूर्ण;

काष्ठा acpi_battery अणु
	काष्ठा mutex lock;
	काष्ठा mutex sysfs_lock;
	काष्ठा घातer_supply *bat;
	काष्ठा घातer_supply_desc bat_desc;
	काष्ठा acpi_device *device;
	काष्ठा notअगरier_block pm_nb;
	काष्ठा list_head list;
	अचिन्हित दीर्घ update_समय;
	पूर्णांक revision;
	पूर्णांक rate_now;
	पूर्णांक capacity_now;
	पूर्णांक voltage_now;
	पूर्णांक design_capacity;
	पूर्णांक full_अक्षरge_capacity;
	पूर्णांक technology;
	पूर्णांक design_voltage;
	पूर्णांक design_capacity_warning;
	पूर्णांक design_capacity_low;
	पूर्णांक cycle_count;
	पूर्णांक measurement_accuracy;
	पूर्णांक max_sampling_समय;
	पूर्णांक min_sampling_समय;
	पूर्णांक max_averaging_पूर्णांकerval;
	पूर्णांक min_averaging_पूर्णांकerval;
	पूर्णांक capacity_granularity_1;
	पूर्णांक capacity_granularity_2;
	पूर्णांक alarm;
	अक्षर model_number[32];
	अक्षर serial_number[32];
	अक्षर type[32];
	अक्षर oem_info[32];
	पूर्णांक state;
	पूर्णांक घातer_unit;
	अचिन्हित दीर्घ flags;
पूर्ण;

#घोषणा to_acpi_battery(x) घातer_supply_get_drvdata(x)

अटल अंतरभूत पूर्णांक acpi_battery_present(काष्ठा acpi_battery *battery)
अणु
	वापस battery->device->status.battery_present;
पूर्ण

अटल पूर्णांक acpi_battery_technology(काष्ठा acpi_battery *battery)
अणु
	अगर (!strहालcmp("NiCd", battery->type))
		वापस POWER_SUPPLY_TECHNOLOGY_NiCd;
	अगर (!strहालcmp("NiMH", battery->type))
		वापस POWER_SUPPLY_TECHNOLOGY_NiMH;
	अगर (!strहालcmp("LION", battery->type))
		वापस POWER_SUPPLY_TECHNOLOGY_LION;
	अगर (!strnहालcmp("LI-ION", battery->type, 6))
		वापस POWER_SUPPLY_TECHNOLOGY_LION;
	अगर (!strहालcmp("LiP", battery->type))
		वापस POWER_SUPPLY_TECHNOLOGY_LIPO;
	वापस POWER_SUPPLY_TECHNOLOGY_UNKNOWN;
पूर्ण

अटल पूर्णांक acpi_battery_get_state(काष्ठा acpi_battery *battery);

अटल पूर्णांक acpi_battery_is_अक्षरged(काष्ठा acpi_battery *battery)
अणु
	/* अक्षरging, disअक्षरging or critical low */
	अगर (battery->state != 0)
		वापस 0;

	/* battery not reporting अक्षरge */
	अगर (battery->capacity_now == ACPI_BATTERY_VALUE_UNKNOWN ||
	    battery->capacity_now == 0)
		वापस 0;

	/* good batteries update full_अक्षरge as the batteries degrade */
	अगर (battery->full_अक्षरge_capacity == battery->capacity_now)
		वापस 1;

	/* fallback to using design values क्रम broken batteries */
	अगर (battery->design_capacity == battery->capacity_now)
		वापस 1;

	/* we करोn't करो any sort of metric based on percentages */
	वापस 0;
पूर्ण

अटल bool acpi_battery_is_degraded(काष्ठा acpi_battery *battery)
अणु
	वापस ACPI_BATTERY_CAPACITY_VALID(battery->full_अक्षरge_capacity) &&
		ACPI_BATTERY_CAPACITY_VALID(battery->design_capacity) &&
		battery->full_अक्षरge_capacity < battery->design_capacity;
पूर्ण

अटल पूर्णांक acpi_battery_handle_disअक्षरging(काष्ठा acpi_battery *battery)
अणु
	/*
	 * Some devices wrongly report disअक्षरging अगर the battery's अक्षरge level
	 * was above the device's start अक्षरging threshold aपंचांग the AC adapter
	 * was plugged in and the device thus did not start a new अक्षरge cycle.
	 */
	अगर ((battery_ac_is_broken || घातer_supply_is_प्रणाली_supplied()) &&
	    battery->rate_now == 0)
		वापस POWER_SUPPLY_STATUS_NOT_CHARGING;

	वापस POWER_SUPPLY_STATUS_DISCHARGING;
पूर्ण

अटल पूर्णांक acpi_battery_get_property(काष्ठा घातer_supply *psy,
				     क्रमागत घातer_supply_property psp,
				     जोड़ घातer_supply_propval *val)
अणु
	पूर्णांक full_capacity = ACPI_BATTERY_VALUE_UNKNOWN, ret = 0;
	काष्ठा acpi_battery *battery = to_acpi_battery(psy);

	अगर (acpi_battery_present(battery)) अणु
		/* run battery update only अगर it is present */
		acpi_battery_get_state(battery);
	पूर्ण अन्यथा अगर (psp != POWER_SUPPLY_PROP_PRESENT)
		वापस -ENODEV;
	चयन (psp) अणु
	हाल POWER_SUPPLY_PROP_STATUS:
		अगर (battery->state & ACPI_BATTERY_STATE_DISCHARGING)
			val->पूर्णांकval = acpi_battery_handle_disअक्षरging(battery);
		अन्यथा अगर (battery->state & ACPI_BATTERY_STATE_CHARGING)
			val->पूर्णांकval = POWER_SUPPLY_STATUS_CHARGING;
		अन्यथा अगर (acpi_battery_is_अक्षरged(battery))
			val->पूर्णांकval = POWER_SUPPLY_STATUS_FULL;
		अन्यथा
			val->पूर्णांकval = POWER_SUPPLY_STATUS_UNKNOWN;
		अवरोध;
	हाल POWER_SUPPLY_PROP_PRESENT:
		val->पूर्णांकval = acpi_battery_present(battery);
		अवरोध;
	हाल POWER_SUPPLY_PROP_TECHNOLOGY:
		val->पूर्णांकval = acpi_battery_technology(battery);
		अवरोध;
	हाल POWER_SUPPLY_PROP_CYCLE_COUNT:
		val->पूर्णांकval = battery->cycle_count;
		अवरोध;
	हाल POWER_SUPPLY_PROP_VOLTAGE_MIN_DESIGN:
		अगर (battery->design_voltage == ACPI_BATTERY_VALUE_UNKNOWN)
			ret = -ENODEV;
		अन्यथा
			val->पूर्णांकval = battery->design_voltage * 1000;
		अवरोध;
	हाल POWER_SUPPLY_PROP_VOLTAGE_NOW:
		अगर (battery->voltage_now == ACPI_BATTERY_VALUE_UNKNOWN)
			ret = -ENODEV;
		अन्यथा
			val->पूर्णांकval = battery->voltage_now * 1000;
		अवरोध;
	हाल POWER_SUPPLY_PROP_CURRENT_NOW:
	हाल POWER_SUPPLY_PROP_POWER_NOW:
		अगर (battery->rate_now == ACPI_BATTERY_VALUE_UNKNOWN)
			ret = -ENODEV;
		अन्यथा
			val->पूर्णांकval = battery->rate_now * 1000;
		अवरोध;
	हाल POWER_SUPPLY_PROP_CHARGE_FULL_DESIGN:
	हाल POWER_SUPPLY_PROP_ENERGY_FULL_DESIGN:
		अगर (!ACPI_BATTERY_CAPACITY_VALID(battery->design_capacity))
			ret = -ENODEV;
		अन्यथा
			val->पूर्णांकval = battery->design_capacity * 1000;
		अवरोध;
	हाल POWER_SUPPLY_PROP_CHARGE_FULL:
	हाल POWER_SUPPLY_PROP_ENERGY_FULL:
		अगर (!ACPI_BATTERY_CAPACITY_VALID(battery->full_अक्षरge_capacity))
			ret = -ENODEV;
		अन्यथा
			val->पूर्णांकval = battery->full_अक्षरge_capacity * 1000;
		अवरोध;
	हाल POWER_SUPPLY_PROP_CHARGE_NOW:
	हाल POWER_SUPPLY_PROP_ENERGY_NOW:
		अगर (battery->capacity_now == ACPI_BATTERY_VALUE_UNKNOWN)
			ret = -ENODEV;
		अन्यथा
			val->पूर्णांकval = battery->capacity_now * 1000;
		अवरोध;
	हाल POWER_SUPPLY_PROP_CAPACITY:
		अगर (ACPI_BATTERY_CAPACITY_VALID(battery->full_अक्षरge_capacity))
			full_capacity = battery->full_अक्षरge_capacity;
		अन्यथा अगर (ACPI_BATTERY_CAPACITY_VALID(battery->design_capacity))
			full_capacity = battery->design_capacity;

		अगर (battery->capacity_now == ACPI_BATTERY_VALUE_UNKNOWN ||
		    full_capacity == ACPI_BATTERY_VALUE_UNKNOWN)
			ret = -ENODEV;
		अन्यथा
			val->पूर्णांकval = battery->capacity_now * 100/
					full_capacity;
		अवरोध;
	हाल POWER_SUPPLY_PROP_CAPACITY_LEVEL:
		अगर (battery->state & ACPI_BATTERY_STATE_CRITICAL)
			val->पूर्णांकval = POWER_SUPPLY_CAPACITY_LEVEL_CRITICAL;
		अन्यथा अगर (test_bit(ACPI_BATTERY_ALARM_PRESENT, &battery->flags) &&
			(battery->capacity_now <= battery->alarm))
			val->पूर्णांकval = POWER_SUPPLY_CAPACITY_LEVEL_LOW;
		अन्यथा अगर (acpi_battery_is_अक्षरged(battery))
			val->पूर्णांकval = POWER_SUPPLY_CAPACITY_LEVEL_FULL;
		अन्यथा
			val->पूर्णांकval = POWER_SUPPLY_CAPACITY_LEVEL_NORMAL;
		अवरोध;
	हाल POWER_SUPPLY_PROP_MODEL_NAME:
		val->strval = battery->model_number;
		अवरोध;
	हाल POWER_SUPPLY_PROP_MANUFACTURER:
		val->strval = battery->oem_info;
		अवरोध;
	हाल POWER_SUPPLY_PROP_SERIAL_NUMBER:
		val->strval = battery->serial_number;
		अवरोध;
	शेष:
		ret = -EINVAL;
	पूर्ण
	वापस ret;
पूर्ण

अटल क्रमागत घातer_supply_property अक्षरge_battery_props[] = अणु
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

अटल क्रमागत घातer_supply_property अक्षरge_battery_full_cap_broken_props[] = अणु
	POWER_SUPPLY_PROP_STATUS,
	POWER_SUPPLY_PROP_PRESENT,
	POWER_SUPPLY_PROP_TECHNOLOGY,
	POWER_SUPPLY_PROP_CYCLE_COUNT,
	POWER_SUPPLY_PROP_VOLTAGE_MIN_DESIGN,
	POWER_SUPPLY_PROP_VOLTAGE_NOW,
	POWER_SUPPLY_PROP_CURRENT_NOW,
	POWER_SUPPLY_PROP_CHARGE_NOW,
	POWER_SUPPLY_PROP_MODEL_NAME,
	POWER_SUPPLY_PROP_MANUFACTURER,
	POWER_SUPPLY_PROP_SERIAL_NUMBER,
पूर्ण;

अटल क्रमागत घातer_supply_property energy_battery_props[] = अणु
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

अटल क्रमागत घातer_supply_property energy_battery_full_cap_broken_props[] = अणु
	POWER_SUPPLY_PROP_STATUS,
	POWER_SUPPLY_PROP_PRESENT,
	POWER_SUPPLY_PROP_TECHNOLOGY,
	POWER_SUPPLY_PROP_CYCLE_COUNT,
	POWER_SUPPLY_PROP_VOLTAGE_MIN_DESIGN,
	POWER_SUPPLY_PROP_VOLTAGE_NOW,
	POWER_SUPPLY_PROP_POWER_NOW,
	POWER_SUPPLY_PROP_ENERGY_NOW,
	POWER_SUPPLY_PROP_MODEL_NAME,
	POWER_SUPPLY_PROP_MANUFACTURER,
	POWER_SUPPLY_PROP_SERIAL_NUMBER,
पूर्ण;

/* Battery Management */
काष्ठा acpi_offsets अणु
	माप_प्रकार offset;		/* offset inside काष्ठा acpi_sbs_battery */
	u8 mode;		/* पूर्णांक or string? */
पूर्ण;

अटल स्थिर काष्ठा acpi_offsets state_offsets[] = अणु
	अणुदुरत्व(काष्ठा acpi_battery, state), 0पूर्ण,
	अणुदुरत्व(काष्ठा acpi_battery, rate_now), 0पूर्ण,
	अणुदुरत्व(काष्ठा acpi_battery, capacity_now), 0पूर्ण,
	अणुदुरत्व(काष्ठा acpi_battery, voltage_now), 0पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा acpi_offsets info_offsets[] = अणु
	अणुदुरत्व(काष्ठा acpi_battery, घातer_unit), 0पूर्ण,
	अणुदुरत्व(काष्ठा acpi_battery, design_capacity), 0पूर्ण,
	अणुदुरत्व(काष्ठा acpi_battery, full_अक्षरge_capacity), 0पूर्ण,
	अणुदुरत्व(काष्ठा acpi_battery, technology), 0पूर्ण,
	अणुदुरत्व(काष्ठा acpi_battery, design_voltage), 0पूर्ण,
	अणुदुरत्व(काष्ठा acpi_battery, design_capacity_warning), 0पूर्ण,
	अणुदुरत्व(काष्ठा acpi_battery, design_capacity_low), 0पूर्ण,
	अणुदुरत्व(काष्ठा acpi_battery, capacity_granularity_1), 0पूर्ण,
	अणुदुरत्व(काष्ठा acpi_battery, capacity_granularity_2), 0पूर्ण,
	अणुदुरत्व(काष्ठा acpi_battery, model_number), 1पूर्ण,
	अणुदुरत्व(काष्ठा acpi_battery, serial_number), 1पूर्ण,
	अणुदुरत्व(काष्ठा acpi_battery, type), 1पूर्ण,
	अणुदुरत्व(काष्ठा acpi_battery, oem_info), 1पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा acpi_offsets extended_info_offsets[] = अणु
	अणुदुरत्व(काष्ठा acpi_battery, revision), 0पूर्ण,
	अणुदुरत्व(काष्ठा acpi_battery, घातer_unit), 0पूर्ण,
	अणुदुरत्व(काष्ठा acpi_battery, design_capacity), 0पूर्ण,
	अणुदुरत्व(काष्ठा acpi_battery, full_अक्षरge_capacity), 0पूर्ण,
	अणुदुरत्व(काष्ठा acpi_battery, technology), 0पूर्ण,
	अणुदुरत्व(काष्ठा acpi_battery, design_voltage), 0पूर्ण,
	अणुदुरत्व(काष्ठा acpi_battery, design_capacity_warning), 0पूर्ण,
	अणुदुरत्व(काष्ठा acpi_battery, design_capacity_low), 0पूर्ण,
	अणुदुरत्व(काष्ठा acpi_battery, cycle_count), 0पूर्ण,
	अणुदुरत्व(काष्ठा acpi_battery, measurement_accuracy), 0पूर्ण,
	अणुदुरत्व(काष्ठा acpi_battery, max_sampling_समय), 0पूर्ण,
	अणुदुरत्व(काष्ठा acpi_battery, min_sampling_समय), 0पूर्ण,
	अणुदुरत्व(काष्ठा acpi_battery, max_averaging_पूर्णांकerval), 0पूर्ण,
	अणुदुरत्व(काष्ठा acpi_battery, min_averaging_पूर्णांकerval), 0पूर्ण,
	अणुदुरत्व(काष्ठा acpi_battery, capacity_granularity_1), 0पूर्ण,
	अणुदुरत्व(काष्ठा acpi_battery, capacity_granularity_2), 0पूर्ण,
	अणुदुरत्व(काष्ठा acpi_battery, model_number), 1पूर्ण,
	अणुदुरत्व(काष्ठा acpi_battery, serial_number), 1पूर्ण,
	अणुदुरत्व(काष्ठा acpi_battery, type), 1पूर्ण,
	अणुदुरत्व(काष्ठा acpi_battery, oem_info), 1पूर्ण,
पूर्ण;

अटल पूर्णांक extract_package(काष्ठा acpi_battery *battery,
			   जोड़ acpi_object *package,
			   स्थिर काष्ठा acpi_offsets *offsets, पूर्णांक num)
अणु
	पूर्णांक i;
	जोड़ acpi_object *element;

	अगर (package->type != ACPI_TYPE_PACKAGE)
		वापस -EFAULT;
	क्रम (i = 0; i < num; ++i) अणु
		अगर (package->package.count <= i)
			वापस -EFAULT;
		element = &package->package.elements[i];
		अगर (offsets[i].mode) अणु
			u8 *ptr = (u8 *)battery + offsets[i].offset;

			अगर (element->type == ACPI_TYPE_STRING ||
			    element->type == ACPI_TYPE_BUFFER)
				म_नकलन(ptr, element->string.poपूर्णांकer, 32);
			अन्यथा अगर (element->type == ACPI_TYPE_INTEGER) अणु
				म_नकलन(ptr, (u8 *)&element->पूर्णांकeger.value,
					माप(u64));
				ptr[माप(u64)] = 0;
			पूर्ण अन्यथा
				*ptr = 0; /* करोn't have value */
		पूर्ण अन्यथा अणु
			पूर्णांक *x = (पूर्णांक *)((u8 *)battery + offsets[i].offset);
			*x = (element->type == ACPI_TYPE_INTEGER) ?
				element->पूर्णांकeger.value : -1;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक acpi_battery_get_status(काष्ठा acpi_battery *battery)
अणु
	अगर (acpi_bus_get_status(battery->device)) अणु
		acpi_handle_info(battery->device->handle,
				 "_STA evaluation failed\n");
		वापस -ENODEV;
	पूर्ण
	वापस 0;
पूर्ण


अटल पूर्णांक extract_battery_info(स्थिर पूर्णांक use_bix,
			 काष्ठा acpi_battery *battery,
			 स्थिर काष्ठा acpi_buffer *buffer)
अणु
	पूर्णांक result = -EFAULT;

	अगर (use_bix && battery_bix_broken_package)
		result = extract_package(battery, buffer->poपूर्णांकer,
				extended_info_offsets + 1,
				ARRAY_SIZE(extended_info_offsets) - 1);
	अन्यथा अगर (use_bix)
		result = extract_package(battery, buffer->poपूर्णांकer,
				extended_info_offsets,
				ARRAY_SIZE(extended_info_offsets));
	अन्यथा
		result = extract_package(battery, buffer->poपूर्णांकer,
				info_offsets, ARRAY_SIZE(info_offsets));
	अगर (test_bit(ACPI_BATTERY_QUIRK_PERCENTAGE_CAPACITY, &battery->flags))
		battery->full_अक्षरge_capacity = battery->design_capacity;
	अगर (test_bit(ACPI_BATTERY_QUIRK_THINKPAD_MAH, &battery->flags) &&
	    battery->घातer_unit && battery->design_voltage) अणु
		battery->design_capacity = battery->design_capacity *
		    10000 / battery->design_voltage;
		battery->full_अक्षरge_capacity = battery->full_अक्षरge_capacity *
		    10000 / battery->design_voltage;
		battery->design_capacity_warning =
		    battery->design_capacity_warning *
		    10000 / battery->design_voltage;
		/* Curiously, design_capacity_low, unlike the rest of them,
		 *  is correct.
		 */
		/* capacity_granularity_* equal 1 on the प्रणालीs tested, so
		 * it's impossible to tell अगर they would need an adjusपंचांगent
		 * or not अगर their values were higher.
		 */
	पूर्ण
	अगर (test_bit(ACPI_BATTERY_QUIRK_DEGRADED_FULL_CHARGE, &battery->flags) &&
	    battery->capacity_now > battery->full_अक्षरge_capacity)
		battery->capacity_now = battery->full_अक्षरge_capacity;

	वापस result;
पूर्ण

अटल पूर्णांक acpi_battery_get_info(काष्ठा acpi_battery *battery)
अणु
	स्थिर पूर्णांक xinfo = test_bit(ACPI_BATTERY_XINFO_PRESENT, &battery->flags);
	पूर्णांक use_bix;
	पूर्णांक result = -ENODEV;

	अगर (!acpi_battery_present(battery))
		वापस 0;


	क्रम (use_bix = xinfo ? 1 : 0; use_bix >= 0; use_bix--) अणु
		काष्ठा acpi_buffer buffer = अणु ACPI_ALLOCATE_BUFFER, शून्य पूर्ण;
		acpi_status status = AE_ERROR;

		mutex_lock(&battery->lock);
		status = acpi_evaluate_object(battery->device->handle,
					      use_bix ? "_BIX":"_BIF",
					      शून्य, &buffer);
		mutex_unlock(&battery->lock);

		अगर (ACPI_FAILURE(status)) अणु
			acpi_handle_info(battery->device->handle,
					 "%s evaluation failed: %s\n",
					 use_bix ? "_BIX":"_BIF",
					 acpi_क्रमmat_exception(status));
		पूर्ण अन्यथा अणु
			result = extract_battery_info(use_bix,
						      battery,
						      &buffer);

			kमुक्त(buffer.poपूर्णांकer);
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!result && !use_bix && xinfo)
		pr_warn(FW_BUG "The _BIX method is broken, using _BIF.\n");

	वापस result;
पूर्ण

अटल पूर्णांक acpi_battery_get_state(काष्ठा acpi_battery *battery)
अणु
	पूर्णांक result = 0;
	acpi_status status = 0;
	काष्ठा acpi_buffer buffer = अणु ACPI_ALLOCATE_BUFFER, शून्य पूर्ण;

	अगर (!acpi_battery_present(battery))
		वापस 0;

	अगर (battery->update_समय &&
	    समय_beक्रमe(jअगरfies, battery->update_समय +
			msecs_to_jअगरfies(cache_समय)))
		वापस 0;

	mutex_lock(&battery->lock);
	status = acpi_evaluate_object(battery->device->handle, "_BST",
				      शून्य, &buffer);
	mutex_unlock(&battery->lock);

	अगर (ACPI_FAILURE(status)) अणु
		acpi_handle_info(battery->device->handle,
				 "_BST evaluation failed: %s",
				 acpi_क्रमmat_exception(status));
		वापस -ENODEV;
	पूर्ण

	result = extract_package(battery, buffer.poपूर्णांकer,
				 state_offsets, ARRAY_SIZE(state_offsets));
	battery->update_समय = jअगरfies;
	kमुक्त(buffer.poपूर्णांकer);

	/* For buggy DSDTs that report negative 16-bit values क्रम either
	 * अक्षरging or disअक्षरging current and/or report 0 as 65536
	 * due to bad math.
	 */
	अगर (battery->घातer_unit == ACPI_BATTERY_POWER_UNIT_MA &&
		battery->rate_now != ACPI_BATTERY_VALUE_UNKNOWN &&
		(s16)(battery->rate_now) < 0) अणु
		battery->rate_now = असल((s16)battery->rate_now);
		pr_warn_once(FW_BUG "(dis)charge rate invalid.\n");
	पूर्ण

	अगर (test_bit(ACPI_BATTERY_QUIRK_PERCENTAGE_CAPACITY, &battery->flags)
	    && battery->capacity_now >= 0 && battery->capacity_now <= 100)
		battery->capacity_now = (battery->capacity_now *
				battery->full_अक्षरge_capacity) / 100;
	अगर (test_bit(ACPI_BATTERY_QUIRK_THINKPAD_MAH, &battery->flags) &&
	    battery->घातer_unit && battery->design_voltage) अणु
		battery->capacity_now = battery->capacity_now *
		    10000 / battery->design_voltage;
	पूर्ण
	अगर (test_bit(ACPI_BATTERY_QUIRK_DEGRADED_FULL_CHARGE, &battery->flags) &&
	    battery->capacity_now > battery->full_अक्षरge_capacity)
		battery->capacity_now = battery->full_अक्षरge_capacity;

	वापस result;
पूर्ण

अटल पूर्णांक acpi_battery_set_alarm(काष्ठा acpi_battery *battery)
अणु
	acpi_status status = 0;

	अगर (!acpi_battery_present(battery) ||
	    !test_bit(ACPI_BATTERY_ALARM_PRESENT, &battery->flags))
		वापस -ENODEV;

	mutex_lock(&battery->lock);
	status = acpi_execute_simple_method(battery->device->handle, "_BTP",
					    battery->alarm);
	mutex_unlock(&battery->lock);

	अगर (ACPI_FAILURE(status))
		वापस -ENODEV;

	acpi_handle_debug(battery->device->handle, "Alarm set to %d\n",
			  battery->alarm);

	वापस 0;
पूर्ण

अटल पूर्णांक acpi_battery_init_alarm(काष्ठा acpi_battery *battery)
अणु
	/* See अगर alarms are supported, and अगर so, set शेष */
	अगर (!acpi_has_method(battery->device->handle, "_BTP")) अणु
		clear_bit(ACPI_BATTERY_ALARM_PRESENT, &battery->flags);
		वापस 0;
	पूर्ण
	set_bit(ACPI_BATTERY_ALARM_PRESENT, &battery->flags);
	अगर (!battery->alarm)
		battery->alarm = battery->design_capacity_warning;
	वापस acpi_battery_set_alarm(battery);
पूर्ण

अटल sमाप_प्रकार acpi_battery_alarm_show(काष्ठा device *dev,
					काष्ठा device_attribute *attr,
					अक्षर *buf)
अणु
	काष्ठा acpi_battery *battery = to_acpi_battery(dev_get_drvdata(dev));

	वापस प्र_लिखो(buf, "%d\n", battery->alarm * 1000);
पूर्ण

अटल sमाप_प्रकार acpi_battery_alarm_store(काष्ठा device *dev,
					काष्ठा device_attribute *attr,
					स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	अचिन्हित दीर्घ x;
	काष्ठा acpi_battery *battery = to_acpi_battery(dev_get_drvdata(dev));

	अगर (माला_पूछो(buf, "%lu\n", &x) == 1)
		battery->alarm = x/1000;
	अगर (acpi_battery_present(battery))
		acpi_battery_set_alarm(battery);
	वापस count;
पूर्ण

अटल स्थिर काष्ठा device_attribute alarm_attr = अणु
	.attr = अणु.name = "alarm", .mode = 0644पूर्ण,
	.show = acpi_battery_alarm_show,
	.store = acpi_battery_alarm_store,
पूर्ण;

/*
 * The Battery Hooking API
 *
 * This API is used inside other drivers that need to expose
 * platक्रमm-specअगरic behaviour within the generic driver in a
 * generic way.
 *
 */

अटल LIST_HEAD(acpi_battery_list);
अटल LIST_HEAD(battery_hook_list);
अटल DEFINE_MUTEX(hook_mutex);

अटल व्योम __battery_hook_unरेजिस्टर(काष्ठा acpi_battery_hook *hook, पूर्णांक lock)
अणु
	काष्ठा acpi_battery *battery;
	/*
	 * In order to हटाओ a hook, we first need to
	 * de-रेजिस्टर all the batteries that are रेजिस्टरed.
	 */
	अगर (lock)
		mutex_lock(&hook_mutex);
	list_क्रम_each_entry(battery, &acpi_battery_list, list) अणु
		hook->हटाओ_battery(battery->bat);
	पूर्ण
	list_del(&hook->list);
	अगर (lock)
		mutex_unlock(&hook_mutex);
	pr_info("extension unregistered: %s\n", hook->name);
पूर्ण

व्योम battery_hook_unरेजिस्टर(काष्ठा acpi_battery_hook *hook)
अणु
	__battery_hook_unरेजिस्टर(hook, 1);
पूर्ण
EXPORT_SYMBOL_GPL(battery_hook_unरेजिस्टर);

व्योम battery_hook_रेजिस्टर(काष्ठा acpi_battery_hook *hook)
अणु
	काष्ठा acpi_battery *battery;

	mutex_lock(&hook_mutex);
	INIT_LIST_HEAD(&hook->list);
	list_add(&hook->list, &battery_hook_list);
	/*
	 * Now that the driver is रेजिस्टरed, we need
	 * to notअगरy the hook that a battery is available
	 * क्रम each battery, so that the driver may add
	 * its attributes.
	 */
	list_क्रम_each_entry(battery, &acpi_battery_list, list) अणु
		अगर (hook->add_battery(battery->bat)) अणु
			/*
			 * If a add-battery वापसs non-zero,
			 * the registration of the extension has failed,
			 * and we will not add it to the list of loaded
			 * hooks.
			 */
			pr_err("extension failed to load: %s", hook->name);
			__battery_hook_unरेजिस्टर(hook, 0);
			जाओ end;
		पूर्ण
	पूर्ण
	pr_info("new extension: %s\n", hook->name);
end:
	mutex_unlock(&hook_mutex);
पूर्ण
EXPORT_SYMBOL_GPL(battery_hook_रेजिस्टर);

/*
 * This function माला_लो called right after the battery sysfs
 * attributes have been added, so that the drivers that
 * define custom sysfs attributes can add their own.
 */
अटल व्योम battery_hook_add_battery(काष्ठा acpi_battery *battery)
अणु
	काष्ठा acpi_battery_hook *hook_node, *पंचांगp;

	mutex_lock(&hook_mutex);
	INIT_LIST_HEAD(&battery->list);
	list_add(&battery->list, &acpi_battery_list);
	/*
	 * Since we added a new battery to the list, we need to
	 * iterate over the hooks and call add_battery क्रम each
	 * hook that was रेजिस्टरed. This usually happens
	 * when a battery माला_लो hotplugged or initialized
	 * during the battery module initialization.
	 */
	list_क्रम_each_entry_safe(hook_node, पंचांगp, &battery_hook_list, list) अणु
		अगर (hook_node->add_battery(battery->bat)) अणु
			/*
			 * The notअगरication of the extensions has failed, to
			 * prevent further errors we will unload the extension.
			 */
			pr_err("error in extension, unloading: %s",
					hook_node->name);
			__battery_hook_unरेजिस्टर(hook_node, 0);
		पूर्ण
	पूर्ण
	mutex_unlock(&hook_mutex);
पूर्ण

अटल व्योम battery_hook_हटाओ_battery(काष्ठा acpi_battery *battery)
अणु
	काष्ठा acpi_battery_hook *hook;

	mutex_lock(&hook_mutex);
	/*
	 * Beक्रमe removing the hook, we need to हटाओ all
	 * custom attributes from the battery.
	 */
	list_क्रम_each_entry(hook, &battery_hook_list, list) अणु
		hook->हटाओ_battery(battery->bat);
	पूर्ण
	/* Then, just हटाओ the battery from the list */
	list_del(&battery->list);
	mutex_unlock(&hook_mutex);
पूर्ण

अटल व्योम __निकास battery_hook_निकास(व्योम)
अणु
	काष्ठा acpi_battery_hook *hook;
	काष्ठा acpi_battery_hook *ptr;
	/*
	 * At this poपूर्णांक, the acpi_bus_unरेजिस्टर_driver()
	 * has called हटाओ क्रम all batteries. We just
	 * need to हटाओ the hooks.
	 */
	list_क्रम_each_entry_safe(hook, ptr, &battery_hook_list, list) अणु
		__battery_hook_unरेजिस्टर(hook, 1);
	पूर्ण
	mutex_destroy(&hook_mutex);
पूर्ण

अटल पूर्णांक sysfs_add_battery(काष्ठा acpi_battery *battery)
अणु
	काष्ठा घातer_supply_config psy_cfg = अणु .drv_data = battery, पूर्ण;
	bool full_cap_broken = false;

	अगर (!ACPI_BATTERY_CAPACITY_VALID(battery->full_अक्षरge_capacity) &&
	    !ACPI_BATTERY_CAPACITY_VALID(battery->design_capacity))
		full_cap_broken = true;

	अगर (battery->घातer_unit == ACPI_BATTERY_POWER_UNIT_MA) अणु
		अगर (full_cap_broken) अणु
			battery->bat_desc.properties =
			    अक्षरge_battery_full_cap_broken_props;
			battery->bat_desc.num_properties =
			    ARRAY_SIZE(अक्षरge_battery_full_cap_broken_props);
		पूर्ण अन्यथा अणु
			battery->bat_desc.properties = अक्षरge_battery_props;
			battery->bat_desc.num_properties =
			    ARRAY_SIZE(अक्षरge_battery_props);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (full_cap_broken) अणु
			battery->bat_desc.properties =
			    energy_battery_full_cap_broken_props;
			battery->bat_desc.num_properties =
			    ARRAY_SIZE(energy_battery_full_cap_broken_props);
		पूर्ण अन्यथा अणु
			battery->bat_desc.properties = energy_battery_props;
			battery->bat_desc.num_properties =
			    ARRAY_SIZE(energy_battery_props);
		पूर्ण
	पूर्ण

	battery->bat_desc.name = acpi_device_bid(battery->device);
	battery->bat_desc.type = POWER_SUPPLY_TYPE_BATTERY;
	battery->bat_desc.get_property = acpi_battery_get_property;

	battery->bat = घातer_supply_रेजिस्टर_no_ws(&battery->device->dev,
				&battery->bat_desc, &psy_cfg);

	अगर (IS_ERR(battery->bat)) अणु
		पूर्णांक result = PTR_ERR(battery->bat);

		battery->bat = शून्य;
		वापस result;
	पूर्ण
	battery_hook_add_battery(battery);
	वापस device_create_file(&battery->bat->dev, &alarm_attr);
पूर्ण

अटल व्योम sysfs_हटाओ_battery(काष्ठा acpi_battery *battery)
अणु
	mutex_lock(&battery->sysfs_lock);
	अगर (!battery->bat) अणु
		mutex_unlock(&battery->sysfs_lock);
		वापस;
	पूर्ण
	battery_hook_हटाओ_battery(battery);
	device_हटाओ_file(&battery->bat->dev, &alarm_attr);
	घातer_supply_unरेजिस्टर(battery->bat);
	battery->bat = शून्य;
	mutex_unlock(&battery->sysfs_lock);
पूर्ण

अटल व्योम find_battery(स्थिर काष्ठा dmi_header *dm, व्योम *निजी)
अणु
	काष्ठा acpi_battery *battery = (काष्ठा acpi_battery *)निजी;
	/* Note: the hardcoded offsets below have been extracted from
	 * the source code of dmidecode.
	 */
	अगर (dm->type == DMI_ENTRY_PORTABLE_BATTERY && dm->length >= 8) अणु
		स्थिर u8 *dmi_data = (स्थिर u8 *)(dm + 1);
		पूर्णांक dmi_capacity = get_unaligned((स्थिर u16 *)(dmi_data + 6));

		अगर (dm->length >= 18)
			dmi_capacity *= dmi_data[17];
		अगर (battery->design_capacity * battery->design_voltage / 1000
		    != dmi_capacity &&
		    battery->design_capacity * 10 == dmi_capacity)
			set_bit(ACPI_BATTERY_QUIRK_THINKPAD_MAH,
				&battery->flags);
	पूर्ण
पूर्ण

/*
 * According to the ACPI spec, some kinds of primary batteries can
 * report percentage battery reमुख्यing capacity directly to OS.
 * In this हाल, it reports the Last Full Charged Capacity == 100
 * and BatteryPresentRate == 0xFFFFFFFF.
 *
 * Now we found some battery reports percentage reमुख्यing capacity
 * even अगर it's reअक्षरgeable.
 * https://bugzilla.kernel.org/show_bug.cgi?id=15979
 *
 * Handle this correctly so that they won't अवरोध userspace.
 */
अटल व्योम acpi_battery_quirks(काष्ठा acpi_battery *battery)
अणु
	अगर (test_bit(ACPI_BATTERY_QUIRK_PERCENTAGE_CAPACITY, &battery->flags))
		वापस;

	अगर (battery->full_अक्षरge_capacity == 100 &&
		battery->rate_now == ACPI_BATTERY_VALUE_UNKNOWN &&
		battery->capacity_now >= 0 && battery->capacity_now <= 100) अणु
		set_bit(ACPI_BATTERY_QUIRK_PERCENTAGE_CAPACITY, &battery->flags);
		battery->full_अक्षरge_capacity = battery->design_capacity;
		battery->capacity_now = (battery->capacity_now *
				battery->full_अक्षरge_capacity) / 100;
	पूर्ण

	अगर (test_bit(ACPI_BATTERY_QUIRK_THINKPAD_MAH, &battery->flags))
		वापस;

	अगर (battery->घातer_unit && dmi_name_in_venकरोrs("LENOVO")) अणु
		स्थिर अक्षर *s;

		s = dmi_get_प्रणाली_info(DMI_PRODUCT_VERSION);
		अगर (s && !strnहालcmp(s, "ThinkPad", 8)) अणु
			dmi_walk(find_battery, battery);
			अगर (test_bit(ACPI_BATTERY_QUIRK_THINKPAD_MAH,
				     &battery->flags) &&
			    battery->design_voltage) अणु
				battery->design_capacity =
				    battery->design_capacity *
				    10000 / battery->design_voltage;
				battery->full_अक्षरge_capacity =
				    battery->full_अक्षरge_capacity *
				    10000 / battery->design_voltage;
				battery->design_capacity_warning =
				    battery->design_capacity_warning *
				    10000 / battery->design_voltage;
				battery->capacity_now = battery->capacity_now *
				    10000 / battery->design_voltage;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (test_bit(ACPI_BATTERY_QUIRK_DEGRADED_FULL_CHARGE, &battery->flags))
		वापस;

	अगर (acpi_battery_is_degraded(battery) &&
	    battery->capacity_now > battery->full_अक्षरge_capacity) अणु
		set_bit(ACPI_BATTERY_QUIRK_DEGRADED_FULL_CHARGE, &battery->flags);
		battery->capacity_now = battery->full_अक्षरge_capacity;
	पूर्ण
पूर्ण

अटल पूर्णांक acpi_battery_update(काष्ठा acpi_battery *battery, bool resume)
अणु
	पूर्णांक result = acpi_battery_get_status(battery);

	अगर (result)
		वापस result;

	अगर (!acpi_battery_present(battery)) अणु
		sysfs_हटाओ_battery(battery);
		battery->update_समय = 0;
		वापस 0;
	पूर्ण

	अगर (resume)
		वापस 0;

	अगर (!battery->update_समय) अणु
		result = acpi_battery_get_info(battery);
		अगर (result)
			वापस result;
		acpi_battery_init_alarm(battery);
	पूर्ण

	result = acpi_battery_get_state(battery);
	अगर (result)
		वापस result;
	acpi_battery_quirks(battery);

	अगर (!battery->bat) अणु
		result = sysfs_add_battery(battery);
		अगर (result)
			वापस result;
	पूर्ण

	/*
	 * Wakeup the प्रणाली अगर battery is critical low
	 * or lower than the alarm level
	 */
	अगर ((battery->state & ACPI_BATTERY_STATE_CRITICAL) ||
	    (test_bit(ACPI_BATTERY_ALARM_PRESENT, &battery->flags) &&
	     (battery->capacity_now <= battery->alarm)))
		acpi_pm_wakeup_event(&battery->device->dev);

	वापस result;
पूर्ण

अटल व्योम acpi_battery_refresh(काष्ठा acpi_battery *battery)
अणु
	पूर्णांक घातer_unit;

	अगर (!battery->bat)
		वापस;

	घातer_unit = battery->घातer_unit;

	acpi_battery_get_info(battery);

	अगर (घातer_unit == battery->घातer_unit)
		वापस;

	/* The battery has changed its reporting units. */
	sysfs_हटाओ_battery(battery);
	sysfs_add_battery(battery);
पूर्ण

/* Driver Interface */
अटल व्योम acpi_battery_notअगरy(काष्ठा acpi_device *device, u32 event)
अणु
	काष्ठा acpi_battery *battery = acpi_driver_data(device);
	काष्ठा घातer_supply *old;

	अगर (!battery)
		वापस;
	old = battery->bat;
	/*
	 * On Acer Aspire V5-573G notअगरications are someबार triggered too
	 * early. For example, when AC is unplugged and notअगरication is
	 * triggered, battery state is still reported as "Full", and changes to
	 * "Discharging" only after लघु delay, without any notअगरication.
	 */
	अगर (battery_notअगरication_delay_ms > 0)
		msleep(battery_notअगरication_delay_ms);
	अगर (event == ACPI_BATTERY_NOTIFY_INFO)
		acpi_battery_refresh(battery);
	acpi_battery_update(battery, false);
	acpi_bus_generate_netlink_event(device->pnp.device_class,
					dev_name(&device->dev), event,
					acpi_battery_present(battery));
	acpi_notअगरier_call_chain(device, event, acpi_battery_present(battery));
	/* acpi_battery_update could हटाओ घातer_supply object */
	अगर (old && battery->bat)
		घातer_supply_changed(battery->bat);
पूर्ण

अटल पूर्णांक battery_notअगरy(काष्ठा notअगरier_block *nb,
			       अचिन्हित दीर्घ mode, व्योम *_unused)
अणु
	काष्ठा acpi_battery *battery = container_of(nb, काष्ठा acpi_battery,
						    pm_nb);
	पूर्णांक result;

	चयन (mode) अणु
	हाल PM_POST_HIBERNATION:
	हाल PM_POST_SUSPEND:
		अगर (!acpi_battery_present(battery))
			वापस 0;

		अगर (battery->bat) अणु
			acpi_battery_refresh(battery);
		पूर्ण अन्यथा अणु
			result = acpi_battery_get_info(battery);
			अगर (result)
				वापस result;

			result = sysfs_add_battery(battery);
			अगर (result)
				वापस result;
		पूर्ण

		acpi_battery_init_alarm(battery);
		acpi_battery_get_state(battery);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __init
battery_bix_broken_package_quirk(स्थिर काष्ठा dmi_प्रणाली_id *d)
अणु
	battery_bix_broken_package = 1;
	वापस 0;
पूर्ण

अटल पूर्णांक __init
battery_notअगरication_delay_quirk(स्थिर काष्ठा dmi_प्रणाली_id *d)
अणु
	battery_notअगरication_delay_ms = 1000;
	वापस 0;
पूर्ण

अटल पूर्णांक __init
battery_ac_is_broken_quirk(स्थिर काष्ठा dmi_प्रणाली_id *d)
अणु
	battery_ac_is_broken = 1;
	वापस 0;
पूर्ण

अटल पूर्णांक __init
battery_करो_not_check_pmic_quirk(स्थिर काष्ठा dmi_प्रणाली_id *d)
अणु
	battery_check_pmic = 0;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dmi_प्रणाली_id bat_dmi_table[] __initस्थिर = अणु
	अणु
		/* NEC LZ750/LS */
		.callback = battery_bix_broken_package_quirk,
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "NEC"),
			DMI_MATCH(DMI_PRODUCT_NAME, "PC-LZ750LS"),
		पूर्ण,
	पूर्ण,
	अणु
		/* Acer Aspire V5-573G */
		.callback = battery_notअगरication_delay_quirk,
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Acer"),
			DMI_MATCH(DMI_PRODUCT_NAME, "Aspire V5-573G"),
		पूर्ण,
	पूर्ण,
	अणु
		/* Poपूर्णांक of View mobii wपूर्णांकab p800w */
		.callback = battery_ac_is_broken_quirk,
		.matches = अणु
			DMI_MATCH(DMI_BOARD_VENDOR, "AMI Corporation"),
			DMI_MATCH(DMI_BOARD_NAME, "Aptio CRB"),
			DMI_MATCH(DMI_BIOS_VERSION, "3BAIR1013"),
			/* Above matches are too generic, add bios-date match */
			DMI_MATCH(DMI_BIOS_DATE, "08/22/2014"),
		पूर्ण,
	पूर्ण,
	अणु
		/* ECS EF20EA, AXP288 PMIC but uses separate fuel-gauge */
		.callback = battery_करो_not_check_pmic_quirk,
		.matches = अणु
			DMI_MATCH(DMI_PRODUCT_NAME, "EF20EA"),
		पूर्ण,
	पूर्ण,
	अणु
		/* Lenovo Ideapad Miix 320, AXP288 PMIC, separate fuel-gauge */
		.callback = battery_करो_not_check_pmic_quirk,
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "LENOVO"),
			DMI_MATCH(DMI_PRODUCT_NAME, "80XF"),
			DMI_MATCH(DMI_PRODUCT_VERSION, "Lenovo MIIX 320-10ICR"),
		पूर्ण,
	पूर्ण,
	अणुपूर्ण,
पूर्ण;

/*
 * Some machines'(E,G Lenovo Z480) ECs are not stable
 * during boot up and this causes battery driver fails to be
 * probed due to failure of getting battery inक्रमmation
 * from EC someबार. After several retries, the operation
 * may work. So add retry code here and 20ms sleep between
 * every retries.
 */
अटल पूर्णांक acpi_battery_update_retry(काष्ठा acpi_battery *battery)
अणु
	पूर्णांक retry, ret;

	क्रम (retry = 5; retry; retry--) अणु
		ret = acpi_battery_update(battery, false);
		अगर (!ret)
			अवरोध;

		msleep(20);
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक acpi_battery_add(काष्ठा acpi_device *device)
अणु
	पूर्णांक result = 0;
	काष्ठा acpi_battery *battery = शून्य;

	अगर (!device)
		वापस -EINVAL;

	अगर (device->dep_unmet)
		वापस -EPROBE_DEFER;

	battery = kzalloc(माप(काष्ठा acpi_battery), GFP_KERNEL);
	अगर (!battery)
		वापस -ENOMEM;
	battery->device = device;
	म_नकल(acpi_device_name(device), ACPI_BATTERY_DEVICE_NAME);
	म_नकल(acpi_device_class(device), ACPI_BATTERY_CLASS);
	device->driver_data = battery;
	mutex_init(&battery->lock);
	mutex_init(&battery->sysfs_lock);
	अगर (acpi_has_method(battery->device->handle, "_BIX"))
		set_bit(ACPI_BATTERY_XINFO_PRESENT, &battery->flags);

	result = acpi_battery_update_retry(battery);
	अगर (result)
		जाओ fail;

	pr_info("Slot [%s] (battery %s)\n", acpi_device_bid(device),
		device->status.battery_present ? "present" : "absent");

	battery->pm_nb.notअगरier_call = battery_notअगरy;
	रेजिस्टर_pm_notअगरier(&battery->pm_nb);

	device_init_wakeup(&device->dev, 1);

	वापस result;

fail:
	sysfs_हटाओ_battery(battery);
	mutex_destroy(&battery->lock);
	mutex_destroy(&battery->sysfs_lock);
	kमुक्त(battery);
	वापस result;
पूर्ण

अटल पूर्णांक acpi_battery_हटाओ(काष्ठा acpi_device *device)
अणु
	काष्ठा acpi_battery *battery = शून्य;

	अगर (!device || !acpi_driver_data(device))
		वापस -EINVAL;
	device_init_wakeup(&device->dev, 0);
	battery = acpi_driver_data(device);
	unरेजिस्टर_pm_notअगरier(&battery->pm_nb);
	sysfs_हटाओ_battery(battery);
	mutex_destroy(&battery->lock);
	mutex_destroy(&battery->sysfs_lock);
	kमुक्त(battery);
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
/* this is needed to learn about changes made in suspended state */
अटल पूर्णांक acpi_battery_resume(काष्ठा device *dev)
अणु
	काष्ठा acpi_battery *battery;

	अगर (!dev)
		वापस -EINVAL;

	battery = acpi_driver_data(to_acpi_device(dev));
	अगर (!battery)
		वापस -EINVAL;

	battery->update_समय = 0;
	acpi_battery_update(battery, true);
	वापस 0;
पूर्ण
#अन्यथा
#घोषणा acpi_battery_resume शून्य
#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(acpi_battery_pm, शून्य, acpi_battery_resume);

अटल काष्ठा acpi_driver acpi_battery_driver = अणु
	.name = "battery",
	.class = ACPI_BATTERY_CLASS,
	.ids = battery_device_ids,
	.flags = ACPI_DRIVER_ALL_NOTIFY_EVENTS,
	.ops = अणु
		.add = acpi_battery_add,
		.हटाओ = acpi_battery_हटाओ,
		.notअगरy = acpi_battery_notअगरy,
		पूर्ण,
	.drv.pm = &acpi_battery_pm,
पूर्ण;

अटल व्योम __init acpi_battery_init_async(व्योम *unused, async_cookie_t cookie)
अणु
	अचिन्हित पूर्णांक i;
	पूर्णांक result;

	dmi_check_प्रणाली(bat_dmi_table);

	अगर (battery_check_pmic) अणु
		क्रम (i = 0; i < ARRAY_SIZE(acpi_battery_blacklist); i++)
			अगर (acpi_dev_present(acpi_battery_blacklist[i], "1", -1)) अणु
				pr_info("found native %s PMIC, not loading\n",
					acpi_battery_blacklist[i]);
				वापस;
			पूर्ण
	पूर्ण

	result = acpi_bus_रेजिस्टर_driver(&acpi_battery_driver);
	battery_driver_रेजिस्टरed = (result == 0);
पूर्ण

अटल पूर्णांक __init acpi_battery_init(व्योम)
अणु
	अगर (acpi_disabled)
		वापस -ENODEV;

	async_cookie = async_schedule(acpi_battery_init_async, शून्य);
	वापस 0;
पूर्ण

अटल व्योम __निकास acpi_battery_निकास(व्योम)
अणु
	async_synchronize_cookie(async_cookie + 1);
	अगर (battery_driver_रेजिस्टरed) अणु
		acpi_bus_unरेजिस्टर_driver(&acpi_battery_driver);
		battery_hook_निकास();
	पूर्ण
पूर्ण

module_init(acpi_battery_init);
module_निकास(acpi_battery_निकास);
