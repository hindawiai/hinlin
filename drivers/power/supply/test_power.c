<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Power supply driver क्रम testing.
 *
 * Copyright 2010  Anton Vorontsov <cbouaपंचांगailru@gmail.com>
 *
 * Dynamic module parameter code from the Virtual Battery Driver
 * Copyright (C) 2008 Pylone, Inc.
 * By: Masashi YOKOTA <yokota@pylone.jp>
 * Originally found here:
 * http://करोwnloads.pylone.jp/src/भव_battery/भव_battery-0.0.1.tar.bz2
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/घातer_supply.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/delay.h>
#समावेश <generated/utsrelease.h>

क्रमागत test_घातer_id अणु
	TEST_AC,
	TEST_BATTERY,
	TEST_USB,
	TEST_POWER_NUM,
पूर्ण;

अटल पूर्णांक ac_online			= 1;
अटल पूर्णांक usb_online			= 1;
अटल पूर्णांक battery_status		= POWER_SUPPLY_STATUS_DISCHARGING;
अटल पूर्णांक battery_health		= POWER_SUPPLY_HEALTH_GOOD;
अटल पूर्णांक battery_present		= 1; /* true */
अटल पूर्णांक battery_technology		= POWER_SUPPLY_TECHNOLOGY_LION;
अटल पूर्णांक battery_capacity		= 50;
अटल पूर्णांक battery_voltage		= 3300;
अटल पूर्णांक battery_अक्षरge_counter	= -1000;
अटल पूर्णांक battery_current		= -1600;

अटल bool module_initialized;

अटल पूर्णांक test_घातer_get_ac_property(काष्ठा घातer_supply *psy,
				      क्रमागत घातer_supply_property psp,
				      जोड़ घातer_supply_propval *val)
अणु
	चयन (psp) अणु
	हाल POWER_SUPPLY_PROP_ONLINE:
		val->पूर्णांकval = ac_online;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक test_घातer_get_usb_property(काष्ठा घातer_supply *psy,
				      क्रमागत घातer_supply_property psp,
				      जोड़ घातer_supply_propval *val)
अणु
	चयन (psp) अणु
	हाल POWER_SUPPLY_PROP_ONLINE:
		val->पूर्णांकval = usb_online;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक test_घातer_get_battery_property(काष्ठा घातer_supply *psy,
					   क्रमागत घातer_supply_property psp,
					   जोड़ घातer_supply_propval *val)
अणु
	चयन (psp) अणु
	हाल POWER_SUPPLY_PROP_MODEL_NAME:
		val->strval = "Test battery";
		अवरोध;
	हाल POWER_SUPPLY_PROP_MANUFACTURER:
		val->strval = "Linux";
		अवरोध;
	हाल POWER_SUPPLY_PROP_SERIAL_NUMBER:
		val->strval = UTS_RELEASE;
		अवरोध;
	हाल POWER_SUPPLY_PROP_STATUS:
		val->पूर्णांकval = battery_status;
		अवरोध;
	हाल POWER_SUPPLY_PROP_CHARGE_TYPE:
		val->पूर्णांकval = POWER_SUPPLY_CHARGE_TYPE_FAST;
		अवरोध;
	हाल POWER_SUPPLY_PROP_HEALTH:
		val->पूर्णांकval = battery_health;
		अवरोध;
	हाल POWER_SUPPLY_PROP_PRESENT:
		val->पूर्णांकval = battery_present;
		अवरोध;
	हाल POWER_SUPPLY_PROP_TECHNOLOGY:
		val->पूर्णांकval = battery_technology;
		अवरोध;
	हाल POWER_SUPPLY_PROP_CAPACITY_LEVEL:
		val->पूर्णांकval = POWER_SUPPLY_CAPACITY_LEVEL_NORMAL;
		अवरोध;
	हाल POWER_SUPPLY_PROP_CAPACITY:
	हाल POWER_SUPPLY_PROP_CHARGE_NOW:
		val->पूर्णांकval = battery_capacity;
		अवरोध;
	हाल POWER_SUPPLY_PROP_CHARGE_COUNTER:
		val->पूर्णांकval = battery_अक्षरge_counter;
		अवरोध;
	हाल POWER_SUPPLY_PROP_CHARGE_FULL_DESIGN:
	हाल POWER_SUPPLY_PROP_CHARGE_FULL:
		val->पूर्णांकval = 100;
		अवरोध;
	हाल POWER_SUPPLY_PROP_TIME_TO_EMPTY_AVG:
	हाल POWER_SUPPLY_PROP_TIME_TO_FULL_NOW:
		val->पूर्णांकval = 3600;
		अवरोध;
	हाल POWER_SUPPLY_PROP_TEMP:
		val->पूर्णांकval = 26;
		अवरोध;
	हाल POWER_SUPPLY_PROP_VOLTAGE_NOW:
		val->पूर्णांकval = battery_voltage;
		अवरोध;
	हाल POWER_SUPPLY_PROP_CURRENT_AVG:
	हाल POWER_SUPPLY_PROP_CURRENT_NOW:
		val->पूर्णांकval = battery_current;
		अवरोध;
	शेष:
		pr_info("%s: some properties deliberately report errors.\n",
			__func__);
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल क्रमागत घातer_supply_property test_घातer_ac_props[] = अणु
	POWER_SUPPLY_PROP_ONLINE,
पूर्ण;

अटल क्रमागत घातer_supply_property test_घातer_battery_props[] = अणु
	POWER_SUPPLY_PROP_STATUS,
	POWER_SUPPLY_PROP_CHARGE_TYPE,
	POWER_SUPPLY_PROP_HEALTH,
	POWER_SUPPLY_PROP_PRESENT,
	POWER_SUPPLY_PROP_TECHNOLOGY,
	POWER_SUPPLY_PROP_CHARGE_FULL_DESIGN,
	POWER_SUPPLY_PROP_CHARGE_FULL,
	POWER_SUPPLY_PROP_CHARGE_NOW,
	POWER_SUPPLY_PROP_CHARGE_COUNTER,
	POWER_SUPPLY_PROP_CAPACITY,
	POWER_SUPPLY_PROP_CAPACITY_LEVEL,
	POWER_SUPPLY_PROP_TIME_TO_EMPTY_AVG,
	POWER_SUPPLY_PROP_TIME_TO_FULL_NOW,
	POWER_SUPPLY_PROP_MODEL_NAME,
	POWER_SUPPLY_PROP_MANUFACTURER,
	POWER_SUPPLY_PROP_SERIAL_NUMBER,
	POWER_SUPPLY_PROP_TEMP,
	POWER_SUPPLY_PROP_VOLTAGE_NOW,
	POWER_SUPPLY_PROP_CURRENT_AVG,
	POWER_SUPPLY_PROP_CURRENT_NOW,
पूर्ण;

अटल अक्षर *test_घातer_ac_supplied_to[] = अणु
	"test_battery",
पूर्ण;

अटल काष्ठा घातer_supply *test_घातer_supplies[TEST_POWER_NUM];

अटल स्थिर काष्ठा घातer_supply_desc test_घातer_desc[] = अणु
	[TEST_AC] = अणु
		.name = "test_ac",
		.type = POWER_SUPPLY_TYPE_MAINS,
		.properties = test_घातer_ac_props,
		.num_properties = ARRAY_SIZE(test_घातer_ac_props),
		.get_property = test_घातer_get_ac_property,
	पूर्ण,
	[TEST_BATTERY] = अणु
		.name = "test_battery",
		.type = POWER_SUPPLY_TYPE_BATTERY,
		.properties = test_घातer_battery_props,
		.num_properties = ARRAY_SIZE(test_घातer_battery_props),
		.get_property = test_घातer_get_battery_property,
	पूर्ण,
	[TEST_USB] = अणु
		.name = "test_usb",
		.type = POWER_SUPPLY_TYPE_USB,
		.properties = test_घातer_ac_props,
		.num_properties = ARRAY_SIZE(test_घातer_ac_props),
		.get_property = test_घातer_get_usb_property,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा घातer_supply_config test_घातer_configs[] = अणु
	अणु
		/* test_ac */
		.supplied_to = test_घातer_ac_supplied_to,
		.num_supplicants = ARRAY_SIZE(test_घातer_ac_supplied_to),
	पूर्ण, अणु
		/* test_battery */
	पूर्ण, अणु
		/* test_usb */
		.supplied_to = test_घातer_ac_supplied_to,
		.num_supplicants = ARRAY_SIZE(test_घातer_ac_supplied_to),
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init test_घातer_init(व्योम)
अणु
	पूर्णांक i;
	पूर्णांक ret;

	BUILD_BUG_ON(TEST_POWER_NUM != ARRAY_SIZE(test_घातer_supplies));
	BUILD_BUG_ON(TEST_POWER_NUM != ARRAY_SIZE(test_घातer_configs));

	क्रम (i = 0; i < ARRAY_SIZE(test_घातer_supplies); i++) अणु
		test_घातer_supplies[i] = घातer_supply_रेजिस्टर(शून्य,
						&test_घातer_desc[i],
						&test_घातer_configs[i]);
		अगर (IS_ERR(test_घातer_supplies[i])) अणु
			pr_err("%s: failed to register %s\n", __func__,
				test_घातer_desc[i].name);
			ret = PTR_ERR(test_घातer_supplies[i]);
			जाओ failed;
		पूर्ण
	पूर्ण

	module_initialized = true;
	वापस 0;
failed:
	जबतक (--i >= 0)
		घातer_supply_unरेजिस्टर(test_घातer_supplies[i]);
	वापस ret;
पूर्ण
module_init(test_घातer_init);

अटल व्योम __निकास test_घातer_निकास(व्योम)
अणु
	पूर्णांक i;

	/* Let's see how we handle changes... */
	ac_online = 0;
	usb_online = 0;
	battery_status = POWER_SUPPLY_STATUS_DISCHARGING;
	क्रम (i = 0; i < ARRAY_SIZE(test_घातer_supplies); i++)
		घातer_supply_changed(test_घातer_supplies[i]);
	pr_info("%s: 'changed' event sent, sleeping for 10 seconds...\n",
		__func__);
	ssleep(10);

	क्रम (i = 0; i < ARRAY_SIZE(test_घातer_supplies); i++)
		घातer_supply_unरेजिस्टर(test_घातer_supplies[i]);

	module_initialized = false;
पूर्ण
module_निकास(test_घातer_निकास);



#घोषणा MAX_KEYLENGTH 256
काष्ठा battery_property_map अणु
	पूर्णांक value;
	अक्षर स्थिर *key;
पूर्ण;

अटल काष्ठा battery_property_map map_ac_online[] = अणु
	अणु 0,  "off"  पूर्ण,
	अणु 1,  "on" पूर्ण,
	अणु -1, शून्य  पूर्ण,
पूर्ण;

अटल काष्ठा battery_property_map map_status[] = अणु
	अणु POWER_SUPPLY_STATUS_CHARGING,     "charging"     पूर्ण,
	अणु POWER_SUPPLY_STATUS_DISCHARGING,  "discharging"  पूर्ण,
	अणु POWER_SUPPLY_STATUS_NOT_CHARGING, "not-charging" पूर्ण,
	अणु POWER_SUPPLY_STATUS_FULL,         "full"         पूर्ण,
	अणु -1,                               शून्य           पूर्ण,
पूर्ण;

अटल काष्ठा battery_property_map map_health[] = अणु
	अणु POWER_SUPPLY_HEALTH_GOOD,           "good"        पूर्ण,
	अणु POWER_SUPPLY_HEALTH_OVERHEAT,       "overheat"    पूर्ण,
	अणु POWER_SUPPLY_HEALTH_DEAD,           "dead"        पूर्ण,
	अणु POWER_SUPPLY_HEALTH_OVERVOLTAGE,    "overvoltage" पूर्ण,
	अणु POWER_SUPPLY_HEALTH_UNSPEC_FAILURE, "failure"     पूर्ण,
	अणु -1,                                 शून्य          पूर्ण,
पूर्ण;

अटल काष्ठा battery_property_map map_present[] = अणु
	अणु 0,  "false" पूर्ण,
	अणु 1,  "true"  पूर्ण,
	अणु -1, शून्य    पूर्ण,
पूर्ण;

अटल काष्ठा battery_property_map map_technology[] = अणु
	अणु POWER_SUPPLY_TECHNOLOGY_NiMH, "NiMH" पूर्ण,
	अणु POWER_SUPPLY_TECHNOLOGY_LION, "LION" पूर्ण,
	अणु POWER_SUPPLY_TECHNOLOGY_LIPO, "LIPO" पूर्ण,
	अणु POWER_SUPPLY_TECHNOLOGY_LiFe, "LiFe" पूर्ण,
	अणु POWER_SUPPLY_TECHNOLOGY_NiCd, "NiCd" पूर्ण,
	अणु POWER_SUPPLY_TECHNOLOGY_LiMn, "LiMn" पूर्ण,
	अणु -1,				शून्य   पूर्ण,
पूर्ण;


अटल पूर्णांक map_get_value(काष्ठा battery_property_map *map, स्थिर अक्षर *key,
				पूर्णांक def_val)
अणु
	अक्षर buf[MAX_KEYLENGTH];
	पूर्णांक cr;

	म_नकलन(buf, key, MAX_KEYLENGTH);
	buf[MAX_KEYLENGTH-1] = '\0';

	cr = strnlen(buf, MAX_KEYLENGTH) - 1;
	अगर (cr < 0)
		वापस def_val;
	अगर (buf[cr] == '\n')
		buf[cr] = '\0';

	जबतक (map->key) अणु
		अगर (strnहालcmp(map->key, buf, MAX_KEYLENGTH) == 0)
			वापस map->value;
		map++;
	पूर्ण

	वापस def_val;
पूर्ण


अटल स्थिर अक्षर *map_get_key(काष्ठा battery_property_map *map, पूर्णांक value,
				स्थिर अक्षर *def_key)
अणु
	जबतक (map->key) अणु
		अगर (map->value == value)
			वापस map->key;
		map++;
	पूर्ण

	वापस def_key;
पूर्ण

अटल अंतरभूत व्योम संकेत_घातer_supply_changed(काष्ठा घातer_supply *psy)
अणु
	अगर (module_initialized)
		घातer_supply_changed(psy);
पूर्ण

अटल पूर्णांक param_set_ac_online(स्थिर अक्षर *key, स्थिर काष्ठा kernel_param *kp)
अणु
	ac_online = map_get_value(map_ac_online, key, ac_online);
	संकेत_घातer_supply_changed(test_घातer_supplies[TEST_AC]);
	वापस 0;
पूर्ण

अटल पूर्णांक param_get_ac_online(अक्षर *buffer, स्थिर काष्ठा kernel_param *kp)
अणु
	वापस प्र_लिखो(buffer, "%s\n",
			map_get_key(map_ac_online, ac_online, "unknown"));
पूर्ण

अटल पूर्णांक param_set_usb_online(स्थिर अक्षर *key, स्थिर काष्ठा kernel_param *kp)
अणु
	usb_online = map_get_value(map_ac_online, key, usb_online);
	संकेत_घातer_supply_changed(test_घातer_supplies[TEST_USB]);
	वापस 0;
पूर्ण

अटल पूर्णांक param_get_usb_online(अक्षर *buffer, स्थिर काष्ठा kernel_param *kp)
अणु
	वापस प्र_लिखो(buffer, "%s\n",
			map_get_key(map_ac_online, usb_online, "unknown"));
पूर्ण

अटल पूर्णांक param_set_battery_status(स्थिर अक्षर *key,
					स्थिर काष्ठा kernel_param *kp)
अणु
	battery_status = map_get_value(map_status, key, battery_status);
	संकेत_घातer_supply_changed(test_घातer_supplies[TEST_BATTERY]);
	वापस 0;
पूर्ण

अटल पूर्णांक param_get_battery_status(अक्षर *buffer, स्थिर काष्ठा kernel_param *kp)
अणु
	वापस प्र_लिखो(buffer, "%s\n",
			map_get_key(map_ac_online, battery_status, "unknown"));
पूर्ण

अटल पूर्णांक param_set_battery_health(स्थिर अक्षर *key,
					स्थिर काष्ठा kernel_param *kp)
अणु
	battery_health = map_get_value(map_health, key, battery_health);
	संकेत_घातer_supply_changed(test_घातer_supplies[TEST_BATTERY]);
	वापस 0;
पूर्ण

अटल पूर्णांक param_get_battery_health(अक्षर *buffer, स्थिर काष्ठा kernel_param *kp)
अणु
	वापस प्र_लिखो(buffer, "%s\n",
			map_get_key(map_ac_online, battery_health, "unknown"));
पूर्ण

अटल पूर्णांक param_set_battery_present(स्थिर अक्षर *key,
					स्थिर काष्ठा kernel_param *kp)
अणु
	battery_present = map_get_value(map_present, key, battery_present);
	संकेत_घातer_supply_changed(test_घातer_supplies[TEST_AC]);
	वापस 0;
पूर्ण

अटल पूर्णांक param_get_battery_present(अक्षर *buffer,
					स्थिर काष्ठा kernel_param *kp)
अणु
	वापस प्र_लिखो(buffer, "%s\n",
			map_get_key(map_ac_online, battery_present, "unknown"));
पूर्ण

अटल पूर्णांक param_set_battery_technology(स्थिर अक्षर *key,
					स्थिर काष्ठा kernel_param *kp)
अणु
	battery_technology = map_get_value(map_technology, key,
						battery_technology);
	संकेत_घातer_supply_changed(test_घातer_supplies[TEST_BATTERY]);
	वापस 0;
पूर्ण

अटल पूर्णांक param_get_battery_technology(अक्षर *buffer,
					स्थिर काष्ठा kernel_param *kp)
अणु
	वापस प्र_लिखो(buffer, "%s\n",
			map_get_key(map_ac_online, battery_technology,
					"unknown"));
पूर्ण

अटल पूर्णांक param_set_battery_capacity(स्थिर अक्षर *key,
					स्थिर काष्ठा kernel_param *kp)
अणु
	पूर्णांक पंचांगp;

	अगर (1 != माला_पूछो(key, "%d", &पंचांगp))
		वापस -EINVAL;

	battery_capacity = पंचांगp;
	संकेत_घातer_supply_changed(test_घातer_supplies[TEST_BATTERY]);
	वापस 0;
पूर्ण

#घोषणा param_get_battery_capacity param_get_पूर्णांक

अटल पूर्णांक param_set_battery_voltage(स्थिर अक्षर *key,
					स्थिर काष्ठा kernel_param *kp)
अणु
	पूर्णांक पंचांगp;

	अगर (1 != माला_पूछो(key, "%d", &पंचांगp))
		वापस -EINVAL;

	battery_voltage = पंचांगp;
	संकेत_घातer_supply_changed(test_घातer_supplies[TEST_BATTERY]);
	वापस 0;
पूर्ण

#घोषणा param_get_battery_voltage param_get_पूर्णांक

अटल पूर्णांक param_set_battery_अक्षरge_counter(स्थिर अक्षर *key,
					स्थिर काष्ठा kernel_param *kp)
अणु
	पूर्णांक पंचांगp;

	अगर (1 != माला_पूछो(key, "%d", &पंचांगp))
		वापस -EINVAL;

	battery_अक्षरge_counter = पंचांगp;
	संकेत_घातer_supply_changed(test_घातer_supplies[TEST_BATTERY]);
	वापस 0;
पूर्ण

#घोषणा param_get_battery_अक्षरge_counter param_get_पूर्णांक

अटल पूर्णांक param_set_battery_current(स्थिर अक्षर *key,
					स्थिर काष्ठा kernel_param *kp)
अणु
	पूर्णांक पंचांगp;

	अगर (1 != माला_पूछो(key, "%d", &पंचांगp))
		वापस -EINVAL;

	battery_current = पंचांगp;
	संकेत_घातer_supply_changed(test_घातer_supplies[TEST_BATTERY]);
	वापस 0;
पूर्ण

#घोषणा param_get_battery_current param_get_पूर्णांक

अटल स्थिर काष्ठा kernel_param_ops param_ops_ac_online = अणु
	.set = param_set_ac_online,
	.get = param_get_ac_online,
पूर्ण;

अटल स्थिर काष्ठा kernel_param_ops param_ops_usb_online = अणु
	.set = param_set_usb_online,
	.get = param_get_usb_online,
पूर्ण;

अटल स्थिर काष्ठा kernel_param_ops param_ops_battery_status = अणु
	.set = param_set_battery_status,
	.get = param_get_battery_status,
पूर्ण;

अटल स्थिर काष्ठा kernel_param_ops param_ops_battery_present = अणु
	.set = param_set_battery_present,
	.get = param_get_battery_present,
पूर्ण;

अटल स्थिर काष्ठा kernel_param_ops param_ops_battery_technology = अणु
	.set = param_set_battery_technology,
	.get = param_get_battery_technology,
पूर्ण;

अटल स्थिर काष्ठा kernel_param_ops param_ops_battery_health = अणु
	.set = param_set_battery_health,
	.get = param_get_battery_health,
पूर्ण;

अटल स्थिर काष्ठा kernel_param_ops param_ops_battery_capacity = अणु
	.set = param_set_battery_capacity,
	.get = param_get_battery_capacity,
पूर्ण;

अटल स्थिर काष्ठा kernel_param_ops param_ops_battery_voltage = अणु
	.set = param_set_battery_voltage,
	.get = param_get_battery_voltage,
पूर्ण;

अटल स्थिर काष्ठा kernel_param_ops param_ops_battery_अक्षरge_counter = अणु
	.set = param_set_battery_अक्षरge_counter,
	.get = param_get_battery_अक्षरge_counter,
पूर्ण;

अटल स्थिर काष्ठा kernel_param_ops param_ops_battery_current = अणु
	.set = param_set_battery_current,
	.get = param_get_battery_current,
पूर्ण;

#घोषणा param_check_ac_online(name, p) __param_check(name, p, व्योम);
#घोषणा param_check_usb_online(name, p) __param_check(name, p, व्योम);
#घोषणा param_check_battery_status(name, p) __param_check(name, p, व्योम);
#घोषणा param_check_battery_present(name, p) __param_check(name, p, व्योम);
#घोषणा param_check_battery_technology(name, p) __param_check(name, p, व्योम);
#घोषणा param_check_battery_health(name, p) __param_check(name, p, व्योम);
#घोषणा param_check_battery_capacity(name, p) __param_check(name, p, व्योम);
#घोषणा param_check_battery_voltage(name, p) __param_check(name, p, व्योम);
#घोषणा param_check_battery_अक्षरge_counter(name, p) __param_check(name, p, व्योम);
#घोषणा param_check_battery_current(name, p) __param_check(name, p, व्योम);


module_param(ac_online, ac_online, 0644);
MODULE_PARM_DESC(ac_online, "AC charging state <on|off>");

module_param(usb_online, usb_online, 0644);
MODULE_PARM_DESC(usb_online, "USB charging state <on|off>");

module_param(battery_status, battery_status, 0644);
MODULE_PARM_DESC(battery_status,
	"battery status <charging|discharging|not-charging|full>");

module_param(battery_present, battery_present, 0644);
MODULE_PARM_DESC(battery_present,
	"battery presence state <good|overheat|dead|overvoltage|failure>");

module_param(battery_technology, battery_technology, 0644);
MODULE_PARM_DESC(battery_technology,
	"battery technology <NiMH|LION|LIPO|LiFe|NiCd|LiMn>");

module_param(battery_health, battery_health, 0644);
MODULE_PARM_DESC(battery_health,
	"battery health state <good|overheat|dead|overvoltage|failure>");

module_param(battery_capacity, battery_capacity, 0644);
MODULE_PARM_DESC(battery_capacity, "battery capacity (percentage)");

module_param(battery_voltage, battery_voltage, 0644);
MODULE_PARM_DESC(battery_voltage, "battery voltage (millivolts)");

module_param(battery_अक्षरge_counter, battery_अक्षरge_counter, 0644);
MODULE_PARM_DESC(battery_अक्षरge_counter,
	"battery charge counter (microampere-hours)");

module_param(battery_current, battery_current, 0644);
MODULE_PARM_DESC(battery_current, "battery current (milliampere)");

MODULE_DESCRIPTION("Power supply driver for testing");
MODULE_AUTHOR("Anton Vorontsov <cbouatmailru@gmail.com>");
MODULE_LICENSE("GPL");
