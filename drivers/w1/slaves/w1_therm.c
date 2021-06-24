<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *	w1_therm.c
 *
 * Copyright (c) 2004 Evgeniy Polyakov <zbr@ioremap.net>
 */

#समावेश <यंत्र/types.h>

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/sched.h>
#समावेश <linux/device.h>
#समावेश <linux/types.h>
#समावेश <linux/slab.h>
#समावेश <linux/delay.h>
#समावेश <linux/hwmon.h>
#समावेश <linux/माला.स>
#समावेश <linux/jअगरfies.h>

#समावेश <linux/w1.h>

#घोषणा W1_THERM_DS18S20	0x10
#घोषणा W1_THERM_DS1822		0x22
#घोषणा W1_THERM_DS18B20	0x28
#घोषणा W1_THERM_DS1825		0x3B
#घोषणा W1_THERM_DS28EA00	0x42

/*
 * Allow the strong pullup to be disabled, but शेष to enabled.
 * If it was disabled a parasite घातered device might not get the require
 * current to करो a temperature conversion.  If it is enabled parasite घातered
 * devices have a better chance of getting the current required.
 * In हाल the parasite घातer-detection is not working (seems to be the हाल
 * क्रम some DS18S20) the strong pullup can also be क्रमced, regardless of the
 * घातer state of the devices.
 *
 * Summary of options:
 * - strong_pullup = 0	Disable strong pullup completely
 * - strong_pullup = 1	Enable स्वतःmatic strong pullup detection
 * - strong_pullup = 2	Force strong pullup
 */
अटल पूर्णांक w1_strong_pullup = 1;
module_param_named(strong_pullup, w1_strong_pullup, पूर्णांक, 0);

/* Counter क्रम devices supporting bulk पढ़ोing */
अटल u16 bulk_पढ़ो_device_counter; /* =0 as per C standard */

/* This command should be in खुला header w1.h but is not */
#घोषणा W1_RECALL_EEPROM	0xB8

/* Nb of try क्रम an operation */
#घोषणा W1_THERM_MAX_TRY		5

/* ms delay to retry bus mutex */
#घोषणा W1_THERM_RETRY_DELAY		20

/* delay in ms to ग_लिखो in EEPROM */
#घोषणा W1_THERM_EEPROM_WRITE_DELAY	10

#घोषणा EEPROM_CMD_WRITE    "save"	/* cmd क्रम ग_लिखो eeprom sysfs */
#घोषणा EEPROM_CMD_READ     "restore"	/* cmd क्रम पढ़ो eeprom sysfs */
#घोषणा BULK_TRIGGER_CMD    "trigger"	/* cmd to trigger a bulk पढ़ो */

#घोषणा MIN_TEMP	-55	/* min temperature that can be measured */
#घोषणा MAX_TEMP	125	/* max temperature that can be measured */

/* Allowed values क्रम sysfs conv_समय attribute */
#घोषणा CONV_TIME_DEFAULT 0
#घोषणा CONV_TIME_MEASURE 1

/* Bits in sysfs "features" value */
#घोषणा W1_THERM_CHECK_RESULT 1	/* Enable conversion success check */
#घोषणा W1_THERM_POLL_COMPLETION 2	/* Poll क्रम conversion completion */
#घोषणा W1_THERM_FEATURES_MASK 3		/* All values mask */

/* Poll period in milliseconds. Should be less then a लघुest operation on the device */
#घोषणा W1_POLL_PERIOD 32
#घोषणा W1_POLL_CONVERT_TEMP 2000	/* Timeout क्रम W1_CONVERT_TEMP, ms */
#घोषणा W1_POLL_RECALL_EEPROM 500	/* Timeout क्रम W1_RECALL_EEPROM, ms*/

/* Masks क्रम resolution functions, work with all devices */
/* Bit mask क्रम config रेजिस्टर क्रम all devices, bits 7,6,5 */
#घोषणा W1_THERM_RESOLUTION_MASK 0xE0
/* Bit offset of resolution in config रेजिस्टर क्रम all devices */
#घोषणा W1_THERM_RESOLUTION_SHIFT 5
/* Bit offset of resolution in config रेजिस्टर क्रम all devices */
#घोषणा W1_THERM_RESOLUTION_SHIFT 5
/* Add this to bit value to get resolution */
#घोषणा W1_THERM_RESOLUTION_MIN 9
/* Maximum allowed value */
#घोषणा W1_THERM_RESOLUTION_MAX 14

/* Helpers Macros */

/*
 * वापस a poपूर्णांकer on the slave w1_therm_family_converter काष्ठा:
 * always test family data existence beक्रमe using this macro
 */
#घोषणा SLAVE_SPECIFIC_FUNC(sl) \
	(((काष्ठा w1_therm_family_data *)(sl->family_data))->specअगरic_functions)

/*
 * वापस the घातer mode of the sl slave : 1-ext, 0-parasite, <0 unknown
 * always test family data existence beक्रमe using this macro
 */
#घोषणा SLAVE_POWERMODE(sl) \
	(((काष्ठा w1_therm_family_data *)(sl->family_data))->बाह्यal_घातered)

/*
 * वापस the resolution in bit of the sl slave : <0 unknown
 * always test family data existence beक्रमe using this macro
 */
#घोषणा SLAVE_RESOLUTION(sl) \
	(((काष्ठा w1_therm_family_data *)(sl->family_data))->resolution)

/*
 * वापस the conv_समय_override of the sl slave
 * always test family data existence beक्रमe using this macro
 */
 #घोषणा SLAVE_CONV_TIME_OVERRIDE(sl) \
	(((काष्ठा w1_therm_family_data *)(sl->family_data))->conv_समय_override)

/*
 * वापस the features of the sl slave
 * always test family data existence beक्रमe using this macro
 */
 #घोषणा SLAVE_FEATURES(sl) \
	(((काष्ठा w1_therm_family_data *)(sl->family_data))->features)

/*
 * वापस whether or not a converT command has been issued to the slave
 * * 0: no bulk पढ़ो is pending
 * * -1: conversion is in progress
 * * 1: conversion करोne, result to be पढ़ो
 */
#घोषणा SLAVE_CONVERT_TRIGGERED(sl) \
	(((काष्ठा w1_therm_family_data *)(sl->family_data))->convert_triggered)

/* वापस the address of the refcnt in the family data */
#घोषणा THERM_REFCNT(family_data) \
	(&((काष्ठा w1_therm_family_data *)family_data)->refcnt)

/* Structs definition */

/**
 * काष्ठा w1_therm_family_converter - bind device specअगरic functions
 * @broken: flag क्रम non-registred families
 * @reserved: not used here
 * @f: poपूर्णांकer to the device binding काष्ठाure
 * @convert: poपूर्णांकer to the device conversion function
 * @get_conversion_समय: poपूर्णांकer to the device conversion समय function
 * @set_resolution: poपूर्णांकer to the device set_resolution function
 * @get_resolution: poपूर्णांकer to the device get_resolution function
 * @ग_लिखो_data: poपूर्णांकer to the device writing function (2 or 3 bytes)
 * @bulk_पढ़ो: true अगर device family support bulk पढ़ो, false otherwise
 */
काष्ठा w1_therm_family_converter अणु
	u8		broken;
	u16		reserved;
	काष्ठा w1_family	*f;
	पूर्णांक		(*convert)(u8 rom[9]);
	पूर्णांक		(*get_conversion_समय)(काष्ठा w1_slave *sl);
	पूर्णांक		(*set_resolution)(काष्ठा w1_slave *sl, पूर्णांक val);
	पूर्णांक		(*get_resolution)(काष्ठा w1_slave *sl);
	पूर्णांक		(*ग_लिखो_data)(काष्ठा w1_slave *sl, स्थिर u8 *data);
	bool		bulk_पढ़ो;
पूर्ण;

/**
 * काष्ठा w1_therm_family_data - device data
 * @rom: ROM device id (64bit Lasered ROM code + 1 CRC byte)
 * @refcnt: ref count
 * @बाह्यal_घातered:	1 device घातered बाह्यally,
 *				0 device parasite घातered,
 *				-x error or undefined
 * @resolution: current device resolution
 * @convert_triggered: conversion state of the device
 * @conv_समय_override: user selected conversion समय or CONV_TIME_DEFAULT
 * @features: bit mask - enable temperature validity check, poll क्रम completion
 * @specअगरic_functions: poपूर्णांकer to काष्ठा of device specअगरic function
 */
काष्ठा w1_therm_family_data अणु
	uपूर्णांक8_t rom[9];
	atomic_t refcnt;
	पूर्णांक बाह्यal_घातered;
	पूर्णांक resolution;
	पूर्णांक convert_triggered;
	पूर्णांक conv_समय_override;
	अचिन्हित पूर्णांक features;
	काष्ठा w1_therm_family_converter *specअगरic_functions;
पूर्ण;

/**
 * काष्ठा therm_info - store temperature पढ़ोing
 * @rom: पढ़ो device data (8 data bytes + 1 CRC byte)
 * @crc: computed crc from rom
 * @verdict: 1 crc checked, 0 crc not matching
 */
काष्ठा therm_info अणु
	u8 rom[9];
	u8 crc;
	u8 verdict;
पूर्ण;

/* Hardware Functions declaration */

/**
 * reset_select_slave() - reset and select a slave
 * @sl: the slave to select
 *
 * Resets the bus and select the slave by sending a ROM MATCH cmd
 * w1_reset_select_slave() from w1_io.c could not be used here because
 * it sent a SKIP ROM command अगर only one device is on the line.
 * At the beginning of the such process, sl->master->slave_count is 1 even अगर
 * more devices are on the line, causing collision on the line.
 *
 * Context: The w1 master lock must be held.
 *
 * Return: 0 अगर success, negative kernel error code otherwise.
 */
अटल पूर्णांक reset_select_slave(काष्ठा w1_slave *sl);

/**
 * convert_t() - Query the device क्रम temperature conversion and पढ़ो
 * @sl: poपूर्णांकer to the slave to पढ़ो
 * @info: poपूर्णांकer to a काष्ठाure to store the पढ़ो results
 *
 * Return: 0 अगर success, -kernel error code otherwise
 */
अटल पूर्णांक convert_t(काष्ठा w1_slave *sl, काष्ठा therm_info *info);

/**
 * पढ़ो_scratchpad() - पढ़ो the data in device RAM
 * @sl: poपूर्णांकer to the slave to पढ़ो
 * @info: poपूर्णांकer to a काष्ठाure to store the पढ़ो results
 *
 * Return: 0 अगर success, -kernel error code otherwise
 */
अटल पूर्णांक पढ़ो_scratchpad(काष्ठा w1_slave *sl, काष्ठा therm_info *info);

/**
 * ग_लिखो_scratchpad() - ग_लिखो nb_bytes in the device RAM
 * @sl: poपूर्णांकer to the slave to ग_लिखो in
 * @data: poपूर्णांकer to an array of 3 bytes, as 3 bytes MUST be written
 * @nb_bytes: number of bytes to be written (2 क्रम DS18S20, 3 otherwise)
 *
 * Return: 0 अगर success, -kernel error code otherwise
 */
अटल पूर्णांक ग_लिखो_scratchpad(काष्ठा w1_slave *sl, स्थिर u8 *data, u8 nb_bytes);

/**
 * copy_scratchpad() - Copy the content of scratchpad in device EEPROM
 * @sl: slave involved
 *
 * Return: 0 अगर success, -kernel error code otherwise
 */
अटल पूर्णांक copy_scratchpad(काष्ठा w1_slave *sl);

/**
 * recall_eeprom() - Restore EEPROM data to device RAM
 * @sl: slave involved
 *
 * Return: 0 अगर success, -kernel error code otherwise
 */
अटल पूर्णांक recall_eeprom(काष्ठा w1_slave *sl);

/**
 * पढ़ो_घातermode() - Query the घातer mode of the slave
 * @sl: slave to retrieve the घातer mode
 *
 * Ask the device to get its घातer mode (बाह्यal or parasite)
 * and store the घातer status in the &काष्ठा w1_therm_family_data.
 *
 * Return:
 * * 0 parasite घातered device
 * * 1 बाह्यally घातered device
 * * <0 kernel error code
 */
अटल पूर्णांक पढ़ो_घातermode(काष्ठा w1_slave *sl);

/**
 * trigger_bulk_पढ़ो() - function to trigger a bulk पढ़ो on the bus
 * @dev_master: the device master of the bus
 *
 * Send a SKIP ROM follow by a CONVERT T commmand on the bus.
 * It also set the status flag in each slave &काष्ठा w1_therm_family_data
 * to संकेत that a conversion is in progress.
 *
 * Return: 0 अगर success, -kernel error code otherwise
 */
अटल पूर्णांक trigger_bulk_पढ़ो(काष्ठा w1_master *dev_master);

/* Sysfs पूर्णांकerface declaration */

अटल sमाप_प्रकार w1_slave_show(काष्ठा device *device,
	काष्ठा device_attribute *attr, अक्षर *buf);

अटल sमाप_प्रकार w1_slave_store(काष्ठा device *device,
	काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार size);

अटल sमाप_प्रकार w1_seq_show(काष्ठा device *device,
	काष्ठा device_attribute *attr, अक्षर *buf);

अटल sमाप_प्रकार temperature_show(काष्ठा device *device,
	काष्ठा device_attribute *attr, अक्षर *buf);

अटल sमाप_प्रकार ext_घातer_show(काष्ठा device *device,
	काष्ठा device_attribute *attr, अक्षर *buf);

अटल sमाप_प्रकार resolution_show(काष्ठा device *device,
	काष्ठा device_attribute *attr, अक्षर *buf);

अटल sमाप_प्रकार resolution_store(काष्ठा device *device,
	काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार size);

अटल sमाप_प्रकार eeprom_cmd_store(काष्ठा device *device,
	काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार size);

अटल sमाप_प्रकार alarms_store(काष्ठा device *device,
	काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार size);

अटल sमाप_प्रकार alarms_show(काष्ठा device *device,
	काष्ठा device_attribute *attr, अक्षर *buf);

अटल sमाप_प्रकार therm_bulk_पढ़ो_store(काष्ठा device *device,
	काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार size);

अटल sमाप_प्रकार therm_bulk_पढ़ो_show(काष्ठा device *device,
	काष्ठा device_attribute *attr, अक्षर *buf);

अटल sमाप_प्रकार conv_समय_show(काष्ठा device *device,
			      काष्ठा device_attribute *attr, अक्षर *buf);

अटल sमाप_प्रकार conv_समय_store(काष्ठा device *device,
			       काष्ठा device_attribute *attr, स्थिर अक्षर *buf,
			       माप_प्रकार size);

अटल sमाप_प्रकार features_show(काष्ठा device *device,
			      काष्ठा device_attribute *attr, अक्षर *buf);

अटल sमाप_प्रकार features_store(काष्ठा device *device,
			       काष्ठा device_attribute *attr, स्थिर अक्षर *buf,
			       माप_प्रकार size);
/* Attributes declarations */

अटल DEVICE_ATTR_RW(w1_slave);
अटल DEVICE_ATTR_RO(w1_seq);
अटल DEVICE_ATTR_RO(temperature);
अटल DEVICE_ATTR_RO(ext_घातer);
अटल DEVICE_ATTR_RW(resolution);
अटल DEVICE_ATTR_WO(eeprom_cmd);
अटल DEVICE_ATTR_RW(alarms);
अटल DEVICE_ATTR_RW(conv_समय);
अटल DEVICE_ATTR_RW(features);

अटल DEVICE_ATTR_RW(therm_bulk_पढ़ो); /* attribut at master level */

/* Interface Functions declaration */

/**
 * w1_therm_add_slave() - Called when a new slave is discovered
 * @sl: slave just discovered by the master.
 *
 * Called by the master when the slave is discovered on the bus. Used to
 * initialize slave state beक्रमe the beginning of any communication.
 *
 * Return: 0 - If success, negative kernel code otherwise
 */
अटल पूर्णांक w1_therm_add_slave(काष्ठा w1_slave *sl);

/**
 * w1_therm_हटाओ_slave() - Called when a slave is हटाओd
 * @sl: slave to be हटाओd.
 *
 * Called by the master when the slave is considered not to be on the bus
 * anymore. Used to मुक्त memory.
 */
अटल व्योम w1_therm_हटाओ_slave(काष्ठा w1_slave *sl);

/* Family attributes */

अटल काष्ठा attribute *w1_therm_attrs[] = अणु
	&dev_attr_w1_slave.attr,
	&dev_attr_temperature.attr,
	&dev_attr_ext_घातer.attr,
	&dev_attr_resolution.attr,
	&dev_attr_eeprom_cmd.attr,
	&dev_attr_alarms.attr,
	&dev_attr_conv_समय.attr,
	&dev_attr_features.attr,
	शून्य,
पूर्ण;

अटल काष्ठा attribute *w1_ds18s20_attrs[] = अणु
	&dev_attr_w1_slave.attr,
	&dev_attr_temperature.attr,
	&dev_attr_ext_घातer.attr,
	&dev_attr_eeprom_cmd.attr,
	&dev_attr_alarms.attr,
	&dev_attr_conv_समय.attr,
	&dev_attr_features.attr,
	शून्य,
पूर्ण;

अटल काष्ठा attribute *w1_ds28ea00_attrs[] = अणु
	&dev_attr_w1_slave.attr,
	&dev_attr_w1_seq.attr,
	&dev_attr_temperature.attr,
	&dev_attr_ext_घातer.attr,
	&dev_attr_resolution.attr,
	&dev_attr_eeprom_cmd.attr,
	&dev_attr_alarms.attr,
	&dev_attr_conv_समय.attr,
	&dev_attr_features.attr,
	शून्य,
पूर्ण;

/* Attribute groups */

ATTRIBUTE_GROUPS(w1_therm);
ATTRIBUTE_GROUPS(w1_ds18s20);
ATTRIBUTE_GROUPS(w1_ds28ea00);

#अगर IS_REACHABLE(CONFIG_HWMON)
अटल पूर्णांक w1_पढ़ो_temp(काष्ठा device *dev, u32 attr, पूर्णांक channel,
			दीर्घ *val);

अटल umode_t w1_is_visible(स्थिर व्योम *_data, क्रमागत hwmon_sensor_types type,
			     u32 attr, पूर्णांक channel)
अणु
	वापस attr == hwmon_temp_input ? 0444 : 0;
पूर्ण

अटल पूर्णांक w1_पढ़ो(काष्ठा device *dev, क्रमागत hwmon_sensor_types type,
		   u32 attr, पूर्णांक channel, दीर्घ *val)
अणु
	चयन (type) अणु
	हाल hwmon_temp:
		वापस w1_पढ़ो_temp(dev, attr, channel, val);
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल स्थिर u32 w1_temp_config[] = अणु
	HWMON_T_INPUT,
	0
पूर्ण;

अटल स्थिर काष्ठा hwmon_channel_info w1_temp = अणु
	.type = hwmon_temp,
	.config = w1_temp_config,
पूर्ण;

अटल स्थिर काष्ठा hwmon_channel_info *w1_info[] = अणु
	&w1_temp,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा hwmon_ops w1_hwmon_ops = अणु
	.is_visible = w1_is_visible,
	.पढ़ो = w1_पढ़ो,
पूर्ण;

अटल स्थिर काष्ठा hwmon_chip_info w1_chip_info = अणु
	.ops = &w1_hwmon_ops,
	.info = w1_info,
पूर्ण;
#घोषणा W1_CHIPINFO	(&w1_chip_info)
#अन्यथा
#घोषणा W1_CHIPINFO	शून्य
#पूर्ण_अगर

/* Family operations */

अटल स्थिर काष्ठा w1_family_ops w1_therm_fops = अणु
	.add_slave	= w1_therm_add_slave,
	.हटाओ_slave	= w1_therm_हटाओ_slave,
	.groups		= w1_therm_groups,
	.chip_info	= W1_CHIPINFO,
पूर्ण;

अटल स्थिर काष्ठा w1_family_ops w1_ds18s20_fops = अणु
	.add_slave	= w1_therm_add_slave,
	.हटाओ_slave	= w1_therm_हटाओ_slave,
	.groups		= w1_ds18s20_groups,
	.chip_info	= W1_CHIPINFO,
पूर्ण;

अटल स्थिर काष्ठा w1_family_ops w1_ds28ea00_fops = अणु
	.add_slave	= w1_therm_add_slave,
	.हटाओ_slave	= w1_therm_हटाओ_slave,
	.groups		= w1_ds28ea00_groups,
	.chip_info	= W1_CHIPINFO,
पूर्ण;

/* Family binding operations काष्ठा */

अटल काष्ठा w1_family w1_therm_family_DS18S20 = अणु
	.fid = W1_THERM_DS18S20,
	.fops = &w1_ds18s20_fops,
पूर्ण;

अटल काष्ठा w1_family w1_therm_family_DS18B20 = अणु
	.fid = W1_THERM_DS18B20,
	.fops = &w1_therm_fops,
पूर्ण;

अटल काष्ठा w1_family w1_therm_family_DS1822 = अणु
	.fid = W1_THERM_DS1822,
	.fops = &w1_therm_fops,
पूर्ण;

अटल काष्ठा w1_family w1_therm_family_DS28EA00 = अणु
	.fid = W1_THERM_DS28EA00,
	.fops = &w1_ds28ea00_fops,
पूर्ण;

अटल काष्ठा w1_family w1_therm_family_DS1825 = अणु
	.fid = W1_THERM_DS1825,
	.fops = &w1_therm_fops,
पूर्ण;

/* Device dependent func */

अटल अंतरभूत पूर्णांक w1_DS18B20_convert_समय(काष्ठा w1_slave *sl)
अणु
	पूर्णांक ret;

	अगर (!sl->family_data)
		वापस -ENODEV;	/* device unknown */

	अगर (SLAVE_CONV_TIME_OVERRIDE(sl) != CONV_TIME_DEFAULT)
		वापस SLAVE_CONV_TIME_OVERRIDE(sl);

	/* Return the conversion समय, depending on resolution,
	 * select maximum conversion समय among all compatible devices
	 */
	चयन (SLAVE_RESOLUTION(sl)) अणु
	हाल 9:
		ret = 95;
		अवरोध;
	हाल 10:
		ret = 190;
		अवरोध;
	हाल 11:
		ret = 375;
		अवरोध;
	हाल 12:
		ret = 750;
		अवरोध;
	हाल 13:
		ret = 850;  /* GX20MH01 only. Datasheet says 500ms, but that's not enough. */
		अवरोध;
	हाल 14:
		ret = 1600; /* GX20MH01 only. Datasheet says 1000ms - not enough */
		अवरोध;
	शेष:
		ret = 750;
	पूर्ण
	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक w1_DS18S20_convert_समय(काष्ठा w1_slave *sl)
अणु
	अगर (!sl->family_data)
		वापस -ENODEV;	/* device unknown */

	अगर (SLAVE_CONV_TIME_OVERRIDE(sl) == CONV_TIME_DEFAULT)
		वापस 750; /* शेष क्रम DS18S20 */
	अन्यथा
		वापस SLAVE_CONV_TIME_OVERRIDE(sl);
पूर्ण

अटल अंतरभूत पूर्णांक w1_DS18B20_ग_लिखो_data(काष्ठा w1_slave *sl,
				स्थिर u8 *data)
अणु
	वापस ग_लिखो_scratchpad(sl, data, 3);
पूर्ण

अटल अंतरभूत पूर्णांक w1_DS18S20_ग_लिखो_data(काष्ठा w1_slave *sl,
				स्थिर u8 *data)
अणु
	/* No config रेजिस्टर */
	वापस ग_लिखो_scratchpad(sl, data, 2);
पूर्ण

अटल अंतरभूत पूर्णांक w1_DS18B20_set_resolution(काष्ठा w1_slave *sl, पूर्णांक val)
अणु
	पूर्णांक ret;
	काष्ठा therm_info info, info2;

	/* DS18B20 resolution is 9 to 12 bits */
	/* GX20MH01 resolution is 9 to 14 bits */
	अगर (val < W1_THERM_RESOLUTION_MIN || val > W1_THERM_RESOLUTION_MAX)
		वापस -EINVAL;

	/* Calc bit value from resolution */
	val = (val - W1_THERM_RESOLUTION_MIN) << W1_THERM_RESOLUTION_SHIFT;

	/*
	 * Read the scratchpad to change only the required bits
	 * (bit5 & bit 6 from byte 4)
	 */
	ret = पढ़ो_scratchpad(sl, &info);

	अगर (ret)
		वापस ret;


	info.rom[4] &= ~W1_THERM_RESOLUTION_MASK;
	info.rom[4] |= val;

	/* Write data in the device RAM */
	ret = w1_DS18B20_ग_लिखो_data(sl, info.rom + 2);
	अगर (ret)
		वापस ret;

	/* Have to पढ़ो back the resolution to verअगरy an actual value
	 * GX20MH01 and DS18B20 are indistinguishable by family number, but resolutions dअगरfer
	 * Some DS18B20 clones करोn't support resolution change
	 */
	ret = पढ़ो_scratchpad(sl, &info2);
	अगर (ret)
		/* Scratchpad पढ़ो fail */
		वापस ret;

	अगर ((info2.rom[4] & W1_THERM_RESOLUTION_MASK) == (info.rom[4] & W1_THERM_RESOLUTION_MASK))
		वापस 0;

	/* Resolution verअगरy error */
	वापस -EIO;
पूर्ण

अटल अंतरभूत पूर्णांक w1_DS18B20_get_resolution(काष्ठा w1_slave *sl)
अणु
	पूर्णांक ret;
	पूर्णांक resolution;
	काष्ठा therm_info info;

	ret = पढ़ो_scratchpad(sl, &info);

	अगर (ret)
		वापस ret;

	resolution = ((info.rom[4] & W1_THERM_RESOLUTION_MASK) >> W1_THERM_RESOLUTION_SHIFT)
		+ W1_THERM_RESOLUTION_MIN;
	/* GX20MH01 has one special हाल:
	 *   >=14 means 14 bits when getting resolution from bit value.
	 * Other devices have no more then 12 bits.
	 */
	अगर (resolution > W1_THERM_RESOLUTION_MAX)
		resolution = W1_THERM_RESOLUTION_MAX;

	वापस resolution;
पूर्ण

/**
 * w1_DS18B20_convert_temp() - temperature computation क्रम DS18B20
 * @rom: data पढ़ो from device RAM (8 data bytes + 1 CRC byte)
 *
 * Can be called क्रम any DS18B20 compliant device.
 *
 * Return: value in millidegrees Celsius.
 */
अटल अंतरभूत पूर्णांक w1_DS18B20_convert_temp(u8 rom[9])
अणु
	u16 bv;
	s16 t;

	/* Signed 16-bit value to अचिन्हित, cpu order */
	bv = le16_to_cpup((__le16 *)rom);

	/* Config रेजिस्टर bit R2 = 1 - GX20MH01 in 13 or 14 bit resolution mode */
	अगर (rom[4] & 0x80) अणु
		/* Insert two temperature bits from config रेजिस्टर */
		/* Aव्योम arithmetic shअगरt of चिन्हित value */
		bv = (bv << 2) | (rom[4] & 3);
		t = (s16) bv;	/* Degrees, lowest bit is 2^-6 */
		वापस (पूर्णांक)t * 1000 / 64;	/* Sign-extend to पूर्णांक; millidegrees */
	पूर्ण
	t = (s16)bv;	/* Degrees, lowest bit is 2^-4 */
	वापस (पूर्णांक)t * 1000 / 16;	/* Sign-extend to पूर्णांक; millidegrees */
पूर्ण

/**
 * w1_DS18S20_convert_temp() - temperature computation क्रम DS18S20
 * @rom: data पढ़ो from device RAM (8 data bytes + 1 CRC byte)
 *
 * Can be called क्रम any DS18S20 compliant device.
 *
 * Return: value in millidegrees Celsius.
 */
अटल अंतरभूत पूर्णांक w1_DS18S20_convert_temp(u8 rom[9])
अणु
	पूर्णांक t, h;

	अगर (!rom[7]) अणु
		pr_debug("%s: Invalid argument for conversion\n", __func__);
		वापस 0;
	पूर्ण

	अगर (rom[1] == 0)
		t = ((s32)rom[0] >> 1)*1000;
	अन्यथा
		t = 1000*(-1*(s32)(0x100-rom[0]) >> 1);

	t -= 250;
	h = 1000*((s32)rom[7] - (s32)rom[6]);
	h /= (s32)rom[7];
	t += h;

	वापस t;
पूर्ण

/* Device capability description */
/* GX20MH01 device shares family number and काष्ठाure with DS18B20 */

अटल काष्ठा w1_therm_family_converter w1_therm_families[] = अणु
	अणु
		.f				= &w1_therm_family_DS18S20,
		.convert			= w1_DS18S20_convert_temp,
		.get_conversion_समय	= w1_DS18S20_convert_समय,
		.set_resolution		= शून्य,	/* no config रेजिस्टर */
		.get_resolution		= शून्य,	/* no config रेजिस्टर */
		.ग_लिखो_data			= w1_DS18S20_ग_लिखो_data,
		.bulk_पढ़ो			= true
	पूर्ण,
	अणु
		.f				= &w1_therm_family_DS1822,
		.convert			= w1_DS18B20_convert_temp,
		.get_conversion_समय	= w1_DS18B20_convert_समय,
		.set_resolution		= w1_DS18B20_set_resolution,
		.get_resolution		= w1_DS18B20_get_resolution,
		.ग_लिखो_data			= w1_DS18B20_ग_लिखो_data,
		.bulk_पढ़ो			= true
	पूर्ण,
	अणु
		/* Also used क्रम GX20MH01 */
		.f				= &w1_therm_family_DS18B20,
		.convert			= w1_DS18B20_convert_temp,
		.get_conversion_समय	= w1_DS18B20_convert_समय,
		.set_resolution		= w1_DS18B20_set_resolution,
		.get_resolution		= w1_DS18B20_get_resolution,
		.ग_लिखो_data			= w1_DS18B20_ग_लिखो_data,
		.bulk_पढ़ो			= true
	पूर्ण,
	अणु
		.f				= &w1_therm_family_DS28EA00,
		.convert			= w1_DS18B20_convert_temp,
		.get_conversion_समय	= w1_DS18B20_convert_समय,
		.set_resolution		= w1_DS18B20_set_resolution,
		.get_resolution		= w1_DS18B20_get_resolution,
		.ग_लिखो_data			= w1_DS18B20_ग_लिखो_data,
		.bulk_पढ़ो			= false
	पूर्ण,
	अणु
		.f				= &w1_therm_family_DS1825,
		.convert			= w1_DS18B20_convert_temp,
		.get_conversion_समय	= w1_DS18B20_convert_समय,
		.set_resolution		= w1_DS18B20_set_resolution,
		.get_resolution		= w1_DS18B20_get_resolution,
		.ग_लिखो_data			= w1_DS18B20_ग_लिखो_data,
		.bulk_पढ़ो			= true
	पूर्ण
पूर्ण;

/* Helpers Functions */

/**
 * device_family() - Retrieve a poपूर्णांकer on &काष्ठा w1_therm_family_converter
 * @sl: slave to retrieve the device specअगरic काष्ठाure
 *
 * Return: poपूर्णांकer to the slaves's family converter, शून्य अगर not known
 */
अटल काष्ठा w1_therm_family_converter *device_family(काष्ठा w1_slave *sl)
अणु
	काष्ठा w1_therm_family_converter *ret = शून्य;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(w1_therm_families); ++i) अणु
		अगर (w1_therm_families[i].f->fid == sl->family->fid) अणु
			ret = &w1_therm_families[i];
			अवरोध;
		पूर्ण
	पूर्ण
	वापस ret;
पूर्ण

/**
 * bus_mutex_lock() - Acquire the mutex
 * @lock: w1 bus mutex to acquire
 *
 * It try to acquire the mutex W1_THERM_MAX_TRY बार and रुको
 * W1_THERM_RETRY_DELAY between 2 attempts.
 *
 * Return: true is mutex is acquired and lock, false otherwise
 */
अटल अंतरभूत bool bus_mutex_lock(काष्ठा mutex *lock)
अणु
	पूर्णांक max_trying = W1_THERM_MAX_TRY;

	/* try to acquire the mutex, अगर not, sleep retry_delay beक्रमe retry) */
	जबतक (mutex_lock_पूर्णांकerruptible(lock) != 0 && max_trying > 0) अणु
		अचिन्हित दीर्घ sleep_rem;

		sleep_rem = msleep_पूर्णांकerruptible(W1_THERM_RETRY_DELAY);
		अगर (!sleep_rem)
			max_trying--;
	पूर्ण

	अगर (!max_trying)
		वापस false;	/* Didn't acquire the bus mutex */

	वापस true;
पूर्ण

/**
 * check_family_data() - Check अगर family data and specअगरic functions are present
 * @sl: W1 device data
 *
 * Return: 0 - OK, negative value - error
 */
अटल पूर्णांक check_family_data(काष्ठा w1_slave *sl)
अणु
	अगर ((!sl->family_data) || (!SLAVE_SPECIFIC_FUNC(sl))) अणु
		dev_info(&sl->dev,
			 "%s: Device is not supported by the driver\n", __func__);
		वापस -EINVAL;  /* No device family */
	पूर्ण
	वापस 0;
पूर्ण

/**
 * support_bulk_पढ़ो() - check अगर slave support bulk पढ़ो
 * @sl: device to check the ability
 *
 * Return: true अगर bulk पढ़ो is supported, false अगर not or error
 */
अटल अंतरभूत bool bulk_पढ़ो_support(काष्ठा w1_slave *sl)
अणु
	अगर (SLAVE_SPECIFIC_FUNC(sl))
		वापस SLAVE_SPECIFIC_FUNC(sl)->bulk_पढ़ो;

	dev_info(&sl->dev,
		"%s: Device not supported by the driver\n", __func__);

	वापस false;  /* No device family */
पूर्ण

/**
 * conversion_समय() - get the Tconv क्रम the slave
 * @sl: device to get the conversion समय
 *
 * On device supporting resolution settings, conversion समय depend
 * on the resolution setting. This helper function get the slave timing,
 * depending on its current setting.
 *
 * Return: conversion समय in ms, negative values are kernel error code
 */
अटल अंतरभूत पूर्णांक conversion_समय(काष्ठा w1_slave *sl)
अणु
	अगर (SLAVE_SPECIFIC_FUNC(sl))
		वापस SLAVE_SPECIFIC_FUNC(sl)->get_conversion_समय(sl);

	dev_info(&sl->dev,
		"%s: Device not supported by the driver\n", __func__);

	वापस -ENODEV;  /* No device family */
पूर्ण

/**
 * temperature_from_RAM() - Convert the पढ़ो info to temperature
 * @sl: device that sent the RAM data
 * @rom: पढ़ो value on the slave device RAM
 *
 * Device dependent, the function bind the correct computation method.
 *
 * Return: temperature in 1/1000degC, 0 on error.
 */
अटल अंतरभूत पूर्णांक temperature_from_RAM(काष्ठा w1_slave *sl, u8 rom[9])
अणु
	अगर (SLAVE_SPECIFIC_FUNC(sl))
		वापस SLAVE_SPECIFIC_FUNC(sl)->convert(rom);

	dev_info(&sl->dev,
		"%s: Device not supported by the driver\n", __func__);

	वापस 0;  /* No device family */
पूर्ण

/**
 * पूर्णांक_to_लघु() - Safe casting of पूर्णांक to लघु
 *
 * @i: पूर्णांकeger to be converted to लघु
 *
 * Device रेजिस्टर use 1 byte to store चिन्हित पूर्णांकeger.
 * This helper function convert the पूर्णांक in a चिन्हित लघु,
 * using the min/max values that device can measure as limits.
 * min/max values are defined by macro.
 *
 * Return: a लघु in the range of min/max value
 */
अटल अंतरभूत s8 पूर्णांक_to_लघु(पूर्णांक i)
अणु
	/* Prepare to cast to लघु by eliminating out of range values */
	i = clamp(i, MIN_TEMP, MAX_TEMP);
	वापस (s8) i;
पूर्ण

/* Interface Functions */

अटल पूर्णांक w1_therm_add_slave(काष्ठा w1_slave *sl)
अणु
	काष्ठा w1_therm_family_converter *sl_family_conv;

	/* Allocate memory */
	sl->family_data = kzalloc(माप(काष्ठा w1_therm_family_data),
		GFP_KERNEL);
	अगर (!sl->family_data)
		वापस -ENOMEM;

	atomic_set(THERM_REFCNT(sl->family_data), 1);

	/* Get a poपूर्णांकer to the device specअगरic function काष्ठा */
	sl_family_conv = device_family(sl);
	अगर (!sl_family_conv) अणु
		kमुक्त(sl->family_data);
		वापस -ENODEV;
	पूर्ण
	/* save this poपूर्णांकer to the device काष्ठाure */
	SLAVE_SPECIFIC_FUNC(sl) = sl_family_conv;

	अगर (bulk_पढ़ो_support(sl)) अणु
		/*
		 * add the sys entry to trigger bulk_पढ़ो
		 * at master level only the 1st समय
		 */
		अगर (!bulk_पढ़ो_device_counter) अणु
			पूर्णांक err = device_create_file(&sl->master->dev,
				&dev_attr_therm_bulk_पढ़ो);

			अगर (err)
				dev_warn(&sl->dev,
				"%s: Device has been added, but bulk read is unavailable. err=%d\n",
				__func__, err);
		पूर्ण
		/* Increment the counter */
		bulk_पढ़ो_device_counter++;
	पूर्ण

	/* Getting the घातer mode of the device अणुबाह्यal, parasiteपूर्ण */
	SLAVE_POWERMODE(sl) = पढ़ो_घातermode(sl);

	अगर (SLAVE_POWERMODE(sl) < 0) अणु
		/* no error वापसed as device has been added */
		dev_warn(&sl->dev,
			"%s: Device has been added, but power_mode may be corrupted. err=%d\n",
			 __func__, SLAVE_POWERMODE(sl));
	पूर्ण

	/* Getting the resolution of the device */
	अगर (SLAVE_SPECIFIC_FUNC(sl)->get_resolution) अणु
		SLAVE_RESOLUTION(sl) =
			SLAVE_SPECIFIC_FUNC(sl)->get_resolution(sl);
		अगर (SLAVE_RESOLUTION(sl) < 0) अणु
			/* no error वापसed as device has been added */
			dev_warn(&sl->dev,
				"%s:Device has been added, but resolution may be corrupted. err=%d\n",
				__func__, SLAVE_RESOLUTION(sl));
		पूर्ण
	पूर्ण

	/* Finally initialize convert_triggered flag */
	SLAVE_CONVERT_TRIGGERED(sl) = 0;

	वापस 0;
पूर्ण

अटल व्योम w1_therm_हटाओ_slave(काष्ठा w1_slave *sl)
अणु
	पूर्णांक refcnt = atomic_sub_वापस(1, THERM_REFCNT(sl->family_data));

	अगर (bulk_पढ़ो_support(sl)) अणु
		bulk_पढ़ो_device_counter--;
		/* Delete the entry अगर no more device support the feature */
		अगर (!bulk_पढ़ो_device_counter)
			device_हटाओ_file(&sl->master->dev,
				&dev_attr_therm_bulk_पढ़ो);
	पूर्ण

	जबतक (refcnt) अणु
		msleep(1000);
		refcnt = atomic_पढ़ो(THERM_REFCNT(sl->family_data));
	पूर्ण
	kमुक्त(sl->family_data);
	sl->family_data = शून्य;
पूर्ण

/* Hardware Functions */

/* Safe version of reset_select_slave - aव्योम using the one in w_io.c */
अटल पूर्णांक reset_select_slave(काष्ठा w1_slave *sl)
अणु
	u8 match[9] = अणु W1_MATCH_ROM, पूर्ण;
	u64 rn = le64_to_cpu(*((u64 *)&sl->reg_num));

	अगर (w1_reset_bus(sl->master))
		वापस -ENODEV;

	स_नकल(&match[1], &rn, 8);
	w1_ग_लिखो_block(sl->master, match, 9);

	वापस 0;
पूर्ण

/**
 * w1_poll_completion - Poll क्रम operation completion, with समयout
 * @dev_master: the device master of the bus
 * @tout_ms: समयout in milliseconds
 *
 * The device is answering 0's while an operation is in progress and 1's after it completes
 * Timeout may happen अगर the previous command was not recognised due to a line noise
 *
 * Return: 0 - OK, negative error - समयout
 */
अटल पूर्णांक w1_poll_completion(काष्ठा w1_master *dev_master, पूर्णांक tout_ms)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < tout_ms/W1_POLL_PERIOD; i++) अणु
		/* Delay is beक्रमe poll, क्रम device to recognize a command */
		msleep(W1_POLL_PERIOD);

		/* Compare all 8 bits to mitigate a noise on the bus */
		अगर (w1_पढ़ो_8(dev_master) == 0xFF)
			अवरोध;
	पूर्ण
	अगर (i == tout_ms/W1_POLL_PERIOD)
		वापस -EIO;

	वापस 0;
पूर्ण

अटल पूर्णांक convert_t(काष्ठा w1_slave *sl, काष्ठा therm_info *info)
अणु
	काष्ठा w1_master *dev_master = sl->master;
	पूर्णांक max_trying = W1_THERM_MAX_TRY;
	पूर्णांक t_conv;
	पूर्णांक ret = -ENODEV;
	bool strong_pullup;

	अगर (!sl->family_data)
		जाओ error;

	strong_pullup = (w1_strong_pullup == 2 ||
					(!SLAVE_POWERMODE(sl) &&
					w1_strong_pullup));

	अगर (strong_pullup && SLAVE_FEATURES(sl) & W1_THERM_POLL_COMPLETION) अणु
		dev_warn(&sl->dev,
			"%s: Disabling W1_THERM_POLL_COMPLETION in parasite power mode.\n",
			__func__);
		SLAVE_FEATURES(sl) &= ~W1_THERM_POLL_COMPLETION;
	पूर्ण

	/* get conversion duration device and id dependent */
	t_conv = conversion_समय(sl);

	स_रखो(info->rom, 0, माप(info->rom));

	/* prevent the slave from going away in sleep */
	atomic_inc(THERM_REFCNT(sl->family_data));

	अगर (!bus_mutex_lock(&dev_master->bus_mutex)) अणु
		ret = -EAGAIN;	/* Didn't acquire the mutex */
		जाओ dec_refcnt;
	पूर्ण

	जबतक (max_trying-- && ret) अणु /* ret should be 0 */

		info->verdict = 0;
		info->crc = 0;
		/* safe version to select slave */
		अगर (!reset_select_slave(sl)) अणु
			अचिन्हित दीर्घ sleep_rem;

			/* 750ms strong pullup (or delay) after the convert */
			अगर (strong_pullup)
				w1_next_pullup(dev_master, t_conv);

			w1_ग_लिखो_8(dev_master, W1_CONVERT_TEMP);

			अगर (strong_pullup) अणु /*some device need pullup */
				sleep_rem = msleep_पूर्णांकerruptible(t_conv);
				अगर (sleep_rem != 0) अणु
					ret = -EINTR;
					जाओ mt_unlock;
				पूर्ण
				mutex_unlock(&dev_master->bus_mutex);
			पूर्ण अन्यथा अणु /*no device need pullup */
				अगर (SLAVE_FEATURES(sl) & W1_THERM_POLL_COMPLETION) अणु
					ret = w1_poll_completion(dev_master, W1_POLL_CONVERT_TEMP);
					अगर (ret) अणु
						dev_dbg(&sl->dev, "%s: Timeout\n", __func__);
						जाओ mt_unlock;
					पूर्ण
					mutex_unlock(&dev_master->bus_mutex);
				पूर्ण अन्यथा अणु
					/* Fixed delay */
					mutex_unlock(&dev_master->bus_mutex);
					sleep_rem = msleep_पूर्णांकerruptible(t_conv);
					अगर (sleep_rem != 0) अणु
						ret = -EINTR;
						जाओ dec_refcnt;
					पूर्ण
				पूर्ण
			पूर्ण
			ret = पढ़ो_scratchpad(sl, info);

			/* If enabled, check क्रम conversion success */
			अगर ((SLAVE_FEATURES(sl) & W1_THERM_CHECK_RESULT) &&
				(info->rom[6] == 0xC) &&
				((info->rom[1] == 0x5 && info->rom[0] == 0x50) ||
				(info->rom[1] == 0x7 && info->rom[0] == 0xFF))
			) अणु
				/* Invalid पढ़ोing (scratchpad byte 6 = 0xC)
				 * due to insufficient conversion समय
				 * or घातer failure.
				 */
				ret = -EIO;
			पूर्ण

			जाओ dec_refcnt;
		पूर्ण

	पूर्ण

mt_unlock:
	mutex_unlock(&dev_master->bus_mutex);
dec_refcnt:
	atomic_dec(THERM_REFCNT(sl->family_data));
error:
	वापस ret;
पूर्ण

अटल पूर्णांक conv_समय_measure(काष्ठा w1_slave *sl, पूर्णांक *conv_समय)
अणु
	काष्ठा therm_info inf,
		*info = &inf;
	काष्ठा w1_master *dev_master = sl->master;
	पूर्णांक max_trying = W1_THERM_MAX_TRY;
	पूर्णांक ret = -ENODEV;
	bool strong_pullup;

	अगर (!sl->family_data)
		जाओ error;

	strong_pullup = (w1_strong_pullup == 2 ||
		(!SLAVE_POWERMODE(sl) &&
		w1_strong_pullup));

	अगर (strong_pullup) अणु
		pr_info("%s: Measure with strong_pullup is not supported.\n", __func__);
		वापस -EINVAL;
	पूर्ण

	स_रखो(info->rom, 0, माप(info->rom));

	/* prevent the slave from going away in sleep */
	atomic_inc(THERM_REFCNT(sl->family_data));

	अगर (!bus_mutex_lock(&dev_master->bus_mutex)) अणु
		ret = -EAGAIN;	/* Didn't acquire the mutex */
		जाओ dec_refcnt;
	पूर्ण

	जबतक (max_trying-- && ret) अणु /* ret should be 0 */
		info->verdict = 0;
		info->crc = 0;
		/* safe version to select slave */
		अगर (!reset_select_slave(sl)) अणु
			पूर्णांक j_start, j_end;

			/*no device need pullup */
			w1_ग_लिखो_8(dev_master, W1_CONVERT_TEMP);

			j_start = jअगरfies;
			ret = w1_poll_completion(dev_master, W1_POLL_CONVERT_TEMP);
			अगर (ret) अणु
				dev_dbg(&sl->dev, "%s: Timeout\n", __func__);
				जाओ mt_unlock;
			पूर्ण
			j_end = jअगरfies;
			/* 1.2x increase क्रम variation and changes over temperature range */
			*conv_समय = jअगरfies_to_msecs(j_end-j_start)*12/10;
			pr_debug("W1 Measure complete, conv_time = %d, HZ=%d.\n",
				*conv_समय, HZ);
			अगर (*conv_समय <= CONV_TIME_MEASURE) अणु
				ret = -EIO;
				जाओ mt_unlock;
			पूर्ण
			mutex_unlock(&dev_master->bus_mutex);
			ret = पढ़ो_scratchpad(sl, info);
			जाओ dec_refcnt;
		पूर्ण

	पूर्ण
mt_unlock:
	mutex_unlock(&dev_master->bus_mutex);
dec_refcnt:
	atomic_dec(THERM_REFCNT(sl->family_data));
error:
	वापस ret;
पूर्ण

अटल पूर्णांक पढ़ो_scratchpad(काष्ठा w1_slave *sl, काष्ठा therm_info *info)
अणु
	काष्ठा w1_master *dev_master = sl->master;
	पूर्णांक max_trying = W1_THERM_MAX_TRY;
	पूर्णांक ret = -ENODEV;

	info->verdict = 0;

	अगर (!sl->family_data)
		जाओ error;

	स_रखो(info->rom, 0, माप(info->rom));

	/* prevent the slave from going away in sleep */
	atomic_inc(THERM_REFCNT(sl->family_data));

	अगर (!bus_mutex_lock(&dev_master->bus_mutex)) अणु
		ret = -EAGAIN;	/* Didn't acquire the mutex */
		जाओ dec_refcnt;
	पूर्ण

	जबतक (max_trying-- && ret) अणु /* ret should be 0 */
		/* safe version to select slave */
		अगर (!reset_select_slave(sl)) अणु
			u8 nb_bytes_पढ़ो;

			w1_ग_लिखो_8(dev_master, W1_READ_SCRATCHPAD);

			nb_bytes_पढ़ो = w1_पढ़ो_block(dev_master, info->rom, 9);
			अगर (nb_bytes_पढ़ो != 9) अणु
				dev_warn(&sl->dev,
					"w1_read_block(): returned %u instead of 9.\n",
					nb_bytes_पढ़ो);
				ret = -EIO;
			पूर्ण

			info->crc = w1_calc_crc8(info->rom, 8);

			अगर (info->rom[8] == info->crc) अणु
				info->verdict = 1;
				ret = 0;
			पूर्ण अन्यथा
				ret = -EIO; /* CRC not checked */
		पूर्ण

	पूर्ण
	mutex_unlock(&dev_master->bus_mutex);

dec_refcnt:
	atomic_dec(THERM_REFCNT(sl->family_data));
error:
	वापस ret;
पूर्ण

अटल पूर्णांक ग_लिखो_scratchpad(काष्ठा w1_slave *sl, स्थिर u8 *data, u8 nb_bytes)
अणु
	काष्ठा w1_master *dev_master = sl->master;
	पूर्णांक max_trying = W1_THERM_MAX_TRY;
	पूर्णांक ret = -ENODEV;

	अगर (!sl->family_data)
		जाओ error;

	/* prevent the slave from going away in sleep */
	atomic_inc(THERM_REFCNT(sl->family_data));

	अगर (!bus_mutex_lock(&dev_master->bus_mutex)) अणु
		ret = -EAGAIN;	/* Didn't acquire the mutex */
		जाओ dec_refcnt;
	पूर्ण

	जबतक (max_trying-- && ret) अणु /* ret should be 0 */
		/* safe version to select slave */
		अगर (!reset_select_slave(sl)) अणु
			w1_ग_लिखो_8(dev_master, W1_WRITE_SCRATCHPAD);
			w1_ग_लिखो_block(dev_master, data, nb_bytes);
			ret = 0;
		पूर्ण
	पूर्ण
	mutex_unlock(&dev_master->bus_mutex);

dec_refcnt:
	atomic_dec(THERM_REFCNT(sl->family_data));
error:
	वापस ret;
पूर्ण

अटल पूर्णांक copy_scratchpad(काष्ठा w1_slave *sl)
अणु
	काष्ठा w1_master *dev_master = sl->master;
	पूर्णांक max_trying = W1_THERM_MAX_TRY;
	पूर्णांक t_ग_लिखो, ret = -ENODEV;
	bool strong_pullup;

	अगर (!sl->family_data)
		जाओ error;

	t_ग_लिखो = W1_THERM_EEPROM_WRITE_DELAY;
	strong_pullup = (w1_strong_pullup == 2 ||
					(!SLAVE_POWERMODE(sl) &&
					w1_strong_pullup));

	/* prevent the slave from going away in sleep */
	atomic_inc(THERM_REFCNT(sl->family_data));

	अगर (!bus_mutex_lock(&dev_master->bus_mutex)) अणु
		ret = -EAGAIN;	/* Didn't acquire the mutex */
		जाओ dec_refcnt;
	पूर्ण

	जबतक (max_trying-- && ret) अणु /* ret should be 0 */
		/* safe version to select slave */
		अगर (!reset_select_slave(sl)) अणु
			अचिन्हित दीर्घ sleep_rem;

			/* 10ms strong pullup (or delay) after the convert */
			अगर (strong_pullup)
				w1_next_pullup(dev_master, t_ग_लिखो);

			w1_ग_लिखो_8(dev_master, W1_COPY_SCRATCHPAD);

			अगर (strong_pullup) अणु
				sleep_rem = msleep_पूर्णांकerruptible(t_ग_लिखो);
				अगर (sleep_rem != 0) अणु
					ret = -EINTR;
					जाओ mt_unlock;
				पूर्ण
			पूर्ण
			ret = 0;
		पूर्ण

	पूर्ण

mt_unlock:
	mutex_unlock(&dev_master->bus_mutex);
dec_refcnt:
	atomic_dec(THERM_REFCNT(sl->family_data));
error:
	वापस ret;
पूर्ण

अटल पूर्णांक recall_eeprom(काष्ठा w1_slave *sl)
अणु
	काष्ठा w1_master *dev_master = sl->master;
	पूर्णांक max_trying = W1_THERM_MAX_TRY;
	पूर्णांक ret = -ENODEV;

	अगर (!sl->family_data)
		जाओ error;

	/* prevent the slave from going away in sleep */
	atomic_inc(THERM_REFCNT(sl->family_data));

	अगर (!bus_mutex_lock(&dev_master->bus_mutex)) अणु
		ret = -EAGAIN;	/* Didn't acquire the mutex */
		जाओ dec_refcnt;
	पूर्ण

	जबतक (max_trying-- && ret) अणु /* ret should be 0 */
		/* safe version to select slave */
		अगर (!reset_select_slave(sl)) अणु

			w1_ग_लिखो_8(dev_master, W1_RECALL_EEPROM);
			ret = w1_poll_completion(dev_master, W1_POLL_RECALL_EEPROM);
		पूर्ण

	पूर्ण

	mutex_unlock(&dev_master->bus_mutex);

dec_refcnt:
	atomic_dec(THERM_REFCNT(sl->family_data));
error:
	वापस ret;
पूर्ण

अटल पूर्णांक पढ़ो_घातermode(काष्ठा w1_slave *sl)
अणु
	काष्ठा w1_master *dev_master = sl->master;
	पूर्णांक max_trying = W1_THERM_MAX_TRY;
	पूर्णांक  ret = -ENODEV;

	अगर (!sl->family_data)
		जाओ error;

	/* prevent the slave from going away in sleep */
	atomic_inc(THERM_REFCNT(sl->family_data));

	अगर (!bus_mutex_lock(&dev_master->bus_mutex)) अणु
		ret = -EAGAIN;	/* Didn't acquire the mutex */
		जाओ dec_refcnt;
	पूर्ण

	जबतक ((max_trying--) && (ret < 0)) अणु
		/* safe version to select slave */
		अगर (!reset_select_slave(sl)) अणु
			w1_ग_लिखो_8(dev_master, W1_READ_PSUPPLY);
			/*
			 * Emit a पढ़ो समय slot and पढ़ो only one bit,
			 * 1 is बाह्यally घातered,
			 * 0 is parasite घातered
			 */
			ret = w1_touch_bit(dev_master, 1);
			/* ret should be either 1 either 0 */
		पूर्ण
	पूर्ण
	mutex_unlock(&dev_master->bus_mutex);

dec_refcnt:
	atomic_dec(THERM_REFCNT(sl->family_data));
error:
	वापस ret;
पूर्ण

अटल पूर्णांक trigger_bulk_पढ़ो(काष्ठा w1_master *dev_master)
अणु
	काष्ठा w1_slave *sl = शून्य; /* used to iterate through slaves */
	पूर्णांक max_trying = W1_THERM_MAX_TRY;
	पूर्णांक t_conv = 0;
	पूर्णांक ret = -ENODEV;
	bool strong_pullup = false;

	/*
	 * Check whether there are parasite घातered device on the bus,
	 * and compute duration of conversion क्रम these devices
	 * so we can apply a strong pullup अगर required
	 */
	list_क्रम_each_entry(sl, &dev_master->slist, w1_slave_entry) अणु
		अगर (!sl->family_data)
			जाओ error;
		अगर (bulk_पढ़ो_support(sl)) अणु
			पूर्णांक t_cur = conversion_समय(sl);

			t_conv = t_cur > t_conv ? t_cur : t_conv;
			strong_pullup = strong_pullup ||
					(w1_strong_pullup == 2 ||
					(!SLAVE_POWERMODE(sl) &&
					w1_strong_pullup));
		पूर्ण
	पूर्ण

	/*
	 * t_conv is the max conversion समय required on the bus
	 * If its 0, no device support the bulk पढ़ो feature
	 */
	अगर (!t_conv)
		जाओ error;

	अगर (!bus_mutex_lock(&dev_master->bus_mutex)) अणु
		ret = -EAGAIN;	/* Didn't acquire the mutex */
		जाओ error;
	पूर्ण

	जबतक ((max_trying--) && (ret < 0)) अणु /* ret should be either 0 */

		अगर (!w1_reset_bus(dev_master)) अणु	/* Just reset the bus */
			अचिन्हित दीर्घ sleep_rem;

			w1_ग_लिखो_8(dev_master, W1_SKIP_ROM);

			अगर (strong_pullup)	/* Apply pullup अगर required */
				w1_next_pullup(dev_master, t_conv);

			w1_ग_लिखो_8(dev_master, W1_CONVERT_TEMP);

			/* set a flag to inकाष्ठा that converT pending */
			list_क्रम_each_entry(sl,
				&dev_master->slist, w1_slave_entry) अणु
				अगर (bulk_पढ़ो_support(sl))
					SLAVE_CONVERT_TRIGGERED(sl) = -1;
			पूर्ण

			अगर (strong_pullup) अणु /* some device need pullup */
				sleep_rem = msleep_पूर्णांकerruptible(t_conv);
				अगर (sleep_rem != 0) अणु
					ret = -EINTR;
					जाओ mt_unlock;
				पूर्ण
				mutex_unlock(&dev_master->bus_mutex);
			पूर्ण अन्यथा अणु
				mutex_unlock(&dev_master->bus_mutex);
				sleep_rem = msleep_पूर्णांकerruptible(t_conv);
				अगर (sleep_rem != 0) अणु
					ret = -EINTR;
					जाओ set_flag;
				पूर्ण
			पूर्ण
			ret = 0;
			जाओ set_flag;
		पूर्ण
	पूर्ण

mt_unlock:
	mutex_unlock(&dev_master->bus_mutex);
set_flag:
	/* set a flag to रेजिस्टर convsersion is करोne */
	list_क्रम_each_entry(sl, &dev_master->slist, w1_slave_entry) अणु
		अगर (bulk_पढ़ो_support(sl))
			SLAVE_CONVERT_TRIGGERED(sl) = 1;
	पूर्ण
error:
	वापस ret;
पूर्ण

/* Sysfs Interface definition */

अटल sमाप_प्रकार w1_slave_show(काष्ठा device *device,
			     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा w1_slave *sl = dev_to_w1_slave(device);
	काष्ठा therm_info info;
	u8 *family_data = sl->family_data;
	पूर्णांक ret, i;
	sमाप_प्रकार c = PAGE_SIZE;

	अगर (bulk_पढ़ो_support(sl)) अणु
		अगर (SLAVE_CONVERT_TRIGGERED(sl) < 0) अणु
			dev_dbg(device,
				"%s: Conversion in progress, retry later\n",
				__func__);
			वापस 0;
		पूर्ण अन्यथा अगर (SLAVE_CONVERT_TRIGGERED(sl) > 0) अणु
			/* A bulk पढ़ो has been issued, पढ़ो the device RAM */
			ret = पढ़ो_scratchpad(sl, &info);
			SLAVE_CONVERT_TRIGGERED(sl) = 0;
		पूर्ण अन्यथा
			ret = convert_t(sl, &info);
	पूर्ण अन्यथा
		ret = convert_t(sl, &info);

	अगर (ret < 0) अणु
		dev_dbg(device,
			"%s: Temperature data may be corrupted. err=%d\n",
			__func__, ret);
		वापस 0;
	पूर्ण

	क्रम (i = 0; i < 9; ++i)
		c -= snम_लिखो(buf + PAGE_SIZE - c, c, "%02x ", info.rom[i]);
	c -= snम_लिखो(buf + PAGE_SIZE - c, c, ": crc=%02x %s\n",
		      info.crc, (info.verdict) ? "YES" : "NO");

	अगर (info.verdict)
		स_नकल(family_data, info.rom, माप(info.rom));
	अन्यथा
		dev_warn(device, "%s:Read failed CRC check\n", __func__);

	क्रम (i = 0; i < 9; ++i)
		c -= snम_लिखो(buf + PAGE_SIZE - c, c, "%02x ",
			      ((u8 *)family_data)[i]);

	c -= snम_लिखो(buf + PAGE_SIZE - c, c, "t=%d\n",
			temperature_from_RAM(sl, info.rom));

	ret = PAGE_SIZE - c;
	वापस ret;
पूर्ण

अटल sमाप_प्रकार w1_slave_store(काष्ठा device *device,
			      काष्ठा device_attribute *attr, स्थिर अक्षर *buf,
			      माप_प्रकार size)
अणु
	पूर्णांक val, ret = 0;
	काष्ठा w1_slave *sl = dev_to_w1_slave(device);

	ret = kstrtoपूर्णांक(buf, 10, &val); /* converting user entry to पूर्णांक */

	अगर (ret) अणु	/* conversion error */
		dev_info(device,
			"%s: conversion error. err= %d\n", __func__, ret);
		वापस size;	/* वापस size to aव्योम call back again */
	पूर्ण

	अगर ((!sl->family_data) || (!SLAVE_SPECIFIC_FUNC(sl))) अणु
		dev_info(device,
			"%s: Device not supported by the driver\n", __func__);
		वापस size;  /* No device family */
	पूर्ण

	अगर (val == 0)	/* val=0 : trigger a EEPROM save */
		ret = copy_scratchpad(sl);
	अन्यथा अणु
		अगर (SLAVE_SPECIFIC_FUNC(sl)->set_resolution)
			ret = SLAVE_SPECIFIC_FUNC(sl)->set_resolution(sl, val);
	पूर्ण

	अगर (ret) अणु
		dev_warn(device, "%s: Set resolution - error %d\n", __func__, ret);
		/* Propagate error to userspace */
		वापस ret;
	पूर्ण
	SLAVE_RESOLUTION(sl) = val;
	/* Reset the conversion समय to शेष - it depends on resolution */
	SLAVE_CONV_TIME_OVERRIDE(sl) = CONV_TIME_DEFAULT;

	वापस size; /* always वापस size to aव्योम infinite calling */
पूर्ण

अटल sमाप_प्रकार temperature_show(काष्ठा device *device,
	काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा w1_slave *sl = dev_to_w1_slave(device);
	काष्ठा therm_info info;
	पूर्णांक ret = 0;

	अगर ((!sl->family_data) || (!SLAVE_SPECIFIC_FUNC(sl))) अणु
		dev_info(device,
			"%s: Device not supported by the driver\n", __func__);
		वापस 0;  /* No device family */
	पूर्ण

	अगर (bulk_पढ़ो_support(sl)) अणु
		अगर (SLAVE_CONVERT_TRIGGERED(sl) < 0) अणु
			dev_dbg(device,
				"%s: Conversion in progress, retry later\n",
				__func__);
			वापस 0;
		पूर्ण अन्यथा अगर (SLAVE_CONVERT_TRIGGERED(sl) > 0) अणु
			/* A bulk पढ़ो has been issued, पढ़ो the device RAM */
			ret = पढ़ो_scratchpad(sl, &info);
			SLAVE_CONVERT_TRIGGERED(sl) = 0;
		पूर्ण अन्यथा
			ret = convert_t(sl, &info);
	पूर्ण अन्यथा
		ret = convert_t(sl, &info);

	अगर (ret < 0) अणु
		dev_dbg(device,
			"%s: Temperature data may be corrupted. err=%d\n",
			__func__, ret);
		वापस 0;
	पूर्ण

	वापस प्र_लिखो(buf, "%d\n", temperature_from_RAM(sl, info.rom));
पूर्ण

अटल sमाप_प्रकार ext_घातer_show(काष्ठा device *device,
	काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा w1_slave *sl = dev_to_w1_slave(device);

	अगर (!sl->family_data) अणु
		dev_info(device,
			"%s: Device not supported by the driver\n", __func__);
		वापस 0;  /* No device family */
	पूर्ण

	/* Getting the घातer mode of the device अणुबाह्यal, parasiteपूर्ण */
	SLAVE_POWERMODE(sl) = पढ़ो_घातermode(sl);

	अगर (SLAVE_POWERMODE(sl) < 0) अणु
		dev_dbg(device,
			"%s: Power_mode may be corrupted. err=%d\n",
			__func__, SLAVE_POWERMODE(sl));
	पूर्ण
	वापस प्र_लिखो(buf, "%d\n", SLAVE_POWERMODE(sl));
पूर्ण

अटल sमाप_प्रकार resolution_show(काष्ठा device *device,
	काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा w1_slave *sl = dev_to_w1_slave(device);

	अगर ((!sl->family_data) || (!SLAVE_SPECIFIC_FUNC(sl))) अणु
		dev_info(device,
			"%s: Device not supported by the driver\n", __func__);
		वापस 0;  /* No device family */
	पूर्ण

	/* get the correct function depending on the device */
	SLAVE_RESOLUTION(sl) = SLAVE_SPECIFIC_FUNC(sl)->get_resolution(sl);
	अगर (SLAVE_RESOLUTION(sl) < 0) अणु
		dev_dbg(device,
			"%s: Resolution may be corrupted. err=%d\n",
			__func__, SLAVE_RESOLUTION(sl));
	पूर्ण

	वापस प्र_लिखो(buf, "%d\n", SLAVE_RESOLUTION(sl));
पूर्ण

अटल sमाप_प्रकार resolution_store(काष्ठा device *device,
	काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	काष्ठा w1_slave *sl = dev_to_w1_slave(device);
	पूर्णांक val;
	पूर्णांक ret = 0;

	ret = kstrtoपूर्णांक(buf, 10, &val); /* converting user entry to पूर्णांक */

	अगर (ret) अणु	/* conversion error */
		dev_info(device,
			"%s: conversion error. err= %d\n", __func__, ret);
		वापस size;	/* वापस size to aव्योम call back again */
	पूर्ण

	अगर ((!sl->family_data) || (!SLAVE_SPECIFIC_FUNC(sl))) अणु
		dev_info(device,
			"%s: Device not supported by the driver\n", __func__);
		वापस size;  /* No device family */
	पूर्ण

	/*
	 * Don't deal with the val enterd by user,
	 * only device knows what is correct or not
	 */

	/* get the correct function depending on the device */
	ret = SLAVE_SPECIFIC_FUNC(sl)->set_resolution(sl, val);

	अगर (ret)
		वापस ret;

	SLAVE_RESOLUTION(sl) = val;
	/* Reset the conversion समय to शेष because it depends on resolution */
	SLAVE_CONV_TIME_OVERRIDE(sl) = CONV_TIME_DEFAULT;

	वापस size;
पूर्ण

अटल sमाप_प्रकार eeprom_cmd_store(काष्ठा device *device,
	काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	काष्ठा w1_slave *sl = dev_to_w1_slave(device);
	पूर्णांक ret = -EINVAL; /* Invalid argument */

	अगर (size == माप(EEPROM_CMD_WRITE)) अणु
		अगर (!म_भेदन(buf, EEPROM_CMD_WRITE, माप(EEPROM_CMD_WRITE)-1))
			ret = copy_scratchpad(sl);
	पूर्ण अन्यथा अगर (size == माप(EEPROM_CMD_READ)) अणु
		अगर (!म_भेदन(buf, EEPROM_CMD_READ, माप(EEPROM_CMD_READ)-1))
			ret = recall_eeprom(sl);
	पूर्ण

	अगर (ret)
		dev_info(device, "%s: error in process %d\n", __func__, ret);

	वापस size;
पूर्ण

अटल sमाप_प्रकार alarms_show(काष्ठा device *device,
	काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा w1_slave *sl = dev_to_w1_slave(device);
	पूर्णांक ret;
	s8 th = 0, tl = 0;
	काष्ठा therm_info scratchpad;

	ret = पढ़ो_scratchpad(sl, &scratchpad);

	अगर (!ret)	अणु
		th = scratchpad.rom[2]; /* TH is byte 2 */
		tl = scratchpad.rom[3]; /* TL is byte 3 */
	पूर्ण अन्यथा अणु
		dev_info(device,
			"%s: error reading alarms register %d\n",
			__func__, ret);
	पूर्ण

	वापस प्र_लिखो(buf, "%hd %hd\n", tl, th);
पूर्ण

अटल sमाप_प्रकार alarms_store(काष्ठा device *device,
	काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	काष्ठा w1_slave *sl = dev_to_w1_slave(device);
	काष्ठा therm_info info;
	u8 new_config_रेजिस्टर[3];	/* array of data to be written */
	पूर्णांक temp, ret;
	अक्षर *token = शून्य;
	s8 tl, th, tt;	/* 1 byte per value + temp ring order */
	अक्षर *p_args, *orig;

	p_args = orig = kदो_स्मृति(size, GFP_KERNEL);
	/* Safe string copys as buf is स्थिर */
	अगर (!p_args) अणु
		dev_warn(device,
			"%s: error unable to allocate memory %d\n",
			__func__, -ENOMEM);
		वापस size;
	पूर्ण
	म_नकल(p_args, buf);

	/* Split string using space अक्षर */
	token = strsep(&p_args, " ");

	अगर (!token)	अणु
		dev_info(device,
			"%s: error parsing args %d\n", __func__, -EINVAL);
		जाओ मुक्त_m;
	पूर्ण

	/* Convert 1st entry to पूर्णांक */
	ret = kstrtoपूर्णांक (token, 10, &temp);
	अगर (ret) अणु
		dev_info(device,
			"%s: error parsing args %d\n", __func__, ret);
		जाओ मुक्त_m;
	पूर्ण

	tl = पूर्णांक_to_लघु(temp);

	/* Split string using space अक्षर */
	token = strsep(&p_args, " ");
	अगर (!token)	अणु
		dev_info(device,
			"%s: error parsing args %d\n", __func__, -EINVAL);
		जाओ मुक्त_m;
	पूर्ण
	/* Convert 2nd entry to पूर्णांक */
	ret = kstrtoपूर्णांक (token, 10, &temp);
	अगर (ret) अणु
		dev_info(device,
			"%s: error parsing args %d\n", __func__, ret);
		जाओ मुक्त_m;
	पूर्ण

	/* Prepare to cast to लघु by eliminating out of range values */
	th = पूर्णांक_to_लघु(temp);

	/* Reorder अगर required th and tl */
	अगर (tl > th) अणु
		tt = tl; tl = th; th = tt;
	पूर्ण

	/*
	 * Read the scratchpad to change only the required bits
	 * (th : byte 2 - tl: byte 3)
	 */
	ret = पढ़ो_scratchpad(sl, &info);
	अगर (!ret) अणु
		new_config_रेजिस्टर[0] = th;	/* Byte 2 */
		new_config_रेजिस्टर[1] = tl;	/* Byte 3 */
		new_config_रेजिस्टर[2] = info.rom[4];/* Byte 4 */
	पूर्ण अन्यथा अणु
		dev_info(device,
			"%s: error reading from the slave device %d\n",
			__func__, ret);
		जाओ मुक्त_m;
	पूर्ण

	/* Write data in the device RAM */
	अगर (!SLAVE_SPECIFIC_FUNC(sl)) अणु
		dev_info(device,
			"%s: Device not supported by the driver %d\n",
			__func__, -ENODEV);
		जाओ मुक्त_m;
	पूर्ण

	ret = SLAVE_SPECIFIC_FUNC(sl)->ग_लिखो_data(sl, new_config_रेजिस्टर);
	अगर (ret)
		dev_info(device,
			"%s: error writing to the slave device %d\n",
			__func__, ret);

मुक्त_m:
	/* मुक्त allocated memory */
	kमुक्त(orig);

	वापस size;
पूर्ण

अटल sमाप_प्रकार therm_bulk_पढ़ो_store(काष्ठा device *device,
	काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	काष्ठा w1_master *dev_master = dev_to_w1_master(device);
	पूर्णांक ret = -EINVAL; /* Invalid argument */

	अगर (size == माप(BULK_TRIGGER_CMD))
		अगर (!म_भेदन(buf, BULK_TRIGGER_CMD,
				माप(BULK_TRIGGER_CMD)-1))
			ret = trigger_bulk_पढ़ो(dev_master);

	अगर (ret)
		dev_info(device,
			"%s: unable to trigger a bulk read on the bus. err=%d\n",
			__func__, ret);

	वापस size;
पूर्ण

अटल sमाप_प्रकार therm_bulk_पढ़ो_show(काष्ठा device *device,
	काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा w1_master *dev_master = dev_to_w1_master(device);
	काष्ठा w1_slave *sl = शून्य;
	पूर्णांक ret = 0;

	list_क्रम_each_entry(sl, &dev_master->slist, w1_slave_entry) अणु
		अगर (sl->family_data) अणु
			अगर (bulk_पढ़ो_support(sl)) अणु
				अगर (SLAVE_CONVERT_TRIGGERED(sl) == -1) अणु
					ret = -1;
					जाओ show_result;
				पूर्ण
				अगर (SLAVE_CONVERT_TRIGGERED(sl) == 1)
					/* जारी to check other slaves */
					ret = 1;
			पूर्ण
		पूर्ण
	पूर्ण
show_result:
	वापस प्र_लिखो(buf, "%d\n", ret);
पूर्ण

अटल sमाप_प्रकार conv_समय_show(काष्ठा device *device,
	काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा w1_slave *sl = dev_to_w1_slave(device);

	अगर ((!sl->family_data) || (!SLAVE_SPECIFIC_FUNC(sl))) अणु
		dev_info(device,
			"%s: Device is not supported by the driver\n", __func__);
		वापस 0;  /* No device family */
	पूर्ण
	वापस प्र_लिखो(buf, "%d\n", conversion_समय(sl));
पूर्ण

अटल sमाप_प्रकार conv_समय_store(काष्ठा device *device,
	काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	पूर्णांक val, ret = 0;
	काष्ठा w1_slave *sl = dev_to_w1_slave(device);

	अगर (kstrtoपूर्णांक(buf, 10, &val)) /* converting user entry to पूर्णांक */
		वापस -EINVAL;

	अगर (check_family_data(sl))
		वापस -ENODEV;

	अगर (val != CONV_TIME_MEASURE) अणु
		अगर (val >= CONV_TIME_DEFAULT)
			SLAVE_CONV_TIME_OVERRIDE(sl) = val;
		अन्यथा
			वापस -EINVAL;

	पूर्ण अन्यथा अणु
		पूर्णांक conv_समय;

		ret = conv_समय_measure(sl, &conv_समय);
		अगर (ret)
			वापस -EIO;
		SLAVE_CONV_TIME_OVERRIDE(sl) = conv_समय;
	पूर्ण
	वापस size;
पूर्ण

अटल sमाप_प्रकार features_show(काष्ठा device *device,
			     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा w1_slave *sl = dev_to_w1_slave(device);

	अगर ((!sl->family_data) || (!SLAVE_SPECIFIC_FUNC(sl))) अणु
		dev_info(device,
			 "%s: Device not supported by the driver\n", __func__);
		वापस 0;  /* No device family */
	पूर्ण
	वापस प्र_लिखो(buf, "%u\n", SLAVE_FEATURES(sl));
पूर्ण

अटल sमाप_प्रकार features_store(काष्ठा device *device,
			      काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	पूर्णांक val, ret = 0;
	bool strong_pullup;
	काष्ठा w1_slave *sl = dev_to_w1_slave(device);

	ret = kstrtouपूर्णांक(buf, 10, &val); /* converting user entry to पूर्णांक */
	अगर (ret)
		वापस -EINVAL;  /* invalid number */

	अगर ((!sl->family_data) || (!SLAVE_SPECIFIC_FUNC(sl))) अणु
		dev_info(device, "%s: Device not supported by the driver\n", __func__);
		वापस -ENODEV;
	पूर्ण

	अगर ((val & W1_THERM_FEATURES_MASK) != val)
		वापस -EINVAL;

	SLAVE_FEATURES(sl) = val;

	strong_pullup = (w1_strong_pullup == 2 ||
			 (!SLAVE_POWERMODE(sl) &&
			  w1_strong_pullup));

	अगर (strong_pullup && SLAVE_FEATURES(sl) & W1_THERM_POLL_COMPLETION) अणु
		dev_warn(&sl->dev,
			 "%s: W1_THERM_POLL_COMPLETION disabled in parasite power mode.\n",
			 __func__);
		SLAVE_FEATURES(sl) &= ~W1_THERM_POLL_COMPLETION;
	पूर्ण

	वापस size;
पूर्ण

#अगर IS_REACHABLE(CONFIG_HWMON)
अटल पूर्णांक w1_पढ़ो_temp(काष्ठा device *device, u32 attr, पूर्णांक channel,
			दीर्घ *val)
अणु
	काष्ठा w1_slave *sl = dev_get_drvdata(device);
	काष्ठा therm_info info;
	पूर्णांक ret;

	चयन (attr) अणु
	हाल hwmon_temp_input:
		ret = convert_t(sl, &info);
		अगर (ret)
			वापस ret;

		अगर (!info.verdict) अणु
			ret = -EIO;
			वापस ret;
		पूर्ण

		*val = temperature_from_RAM(sl, info.rom);
		ret = 0;
		अवरोध;
	शेष:
		ret = -EOPNOTSUPP;
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण
#पूर्ण_अगर

#घोषणा W1_42_CHAIN	0x99
#घोषणा W1_42_CHAIN_OFF	0x3C
#घोषणा W1_42_CHAIN_OFF_INV	0xC3
#घोषणा W1_42_CHAIN_ON	0x5A
#घोषणा W1_42_CHAIN_ON_INV	0xA5
#घोषणा W1_42_CHAIN_DONE 0x96
#घोषणा W1_42_CHAIN_DONE_INV 0x69
#घोषणा W1_42_COND_READ	0x0F
#घोषणा W1_42_SUCCESS_CONFIRM_BYTE 0xAA
#घोषणा W1_42_FINISHED_BYTE 0xFF
अटल sमाप_प्रकार w1_seq_show(काष्ठा device *device,
	काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा w1_slave *sl = dev_to_w1_slave(device);
	sमाप_प्रकार c = PAGE_SIZE;
	पूर्णांक rv;
	पूर्णांक i;
	u8 ack;
	u64 rn;
	काष्ठा w1_reg_num *reg_num;
	पूर्णांक seq = 0;

	mutex_lock(&sl->master->bus_mutex);
	/* Place all devices in CHAIN state */
	अगर (w1_reset_bus(sl->master))
		जाओ error;
	w1_ग_लिखो_8(sl->master, W1_SKIP_ROM);
	w1_ग_लिखो_8(sl->master, W1_42_CHAIN);
	w1_ग_लिखो_8(sl->master, W1_42_CHAIN_ON);
	w1_ग_लिखो_8(sl->master, W1_42_CHAIN_ON_INV);
	msleep(sl->master->pullup_duration);

	/* check क्रम acknowledgment */
	ack = w1_पढ़ो_8(sl->master);
	अगर (ack != W1_42_SUCCESS_CONFIRM_BYTE)
		जाओ error;

	/* In हाल the bus fails to send 0xFF, limit */
	क्रम (i = 0; i <= 64; i++) अणु
		अगर (w1_reset_bus(sl->master))
			जाओ error;

		w1_ग_लिखो_8(sl->master, W1_42_COND_READ);
		rv = w1_पढ़ो_block(sl->master, (u8 *)&rn, 8);
		reg_num = (काष्ठा w1_reg_num *) &rn;
		अगर (reg_num->family == W1_42_FINISHED_BYTE)
			अवरोध;
		अगर (sl->reg_num.id == reg_num->id)
			seq = i;

		w1_ग_लिखो_8(sl->master, W1_42_CHAIN);
		w1_ग_लिखो_8(sl->master, W1_42_CHAIN_DONE);
		w1_ग_लिखो_8(sl->master, W1_42_CHAIN_DONE_INV);
		w1_पढ़ो_block(sl->master, &ack, माप(ack));

		/* check क्रम acknowledgment */
		ack = w1_पढ़ो_8(sl->master);
		अगर (ack != W1_42_SUCCESS_CONFIRM_BYTE)
			जाओ error;

	पूर्ण

	/* Exit from CHAIN state */
	अगर (w1_reset_bus(sl->master))
		जाओ error;
	w1_ग_लिखो_8(sl->master, W1_SKIP_ROM);
	w1_ग_लिखो_8(sl->master, W1_42_CHAIN);
	w1_ग_लिखो_8(sl->master, W1_42_CHAIN_OFF);
	w1_ग_लिखो_8(sl->master, W1_42_CHAIN_OFF_INV);

	/* check क्रम acknowledgment */
	ack = w1_पढ़ो_8(sl->master);
	अगर (ack != W1_42_SUCCESS_CONFIRM_BYTE)
		जाओ error;
	mutex_unlock(&sl->master->bus_mutex);

	c -= snम_लिखो(buf + PAGE_SIZE - c, c, "%d\n", seq);
	वापस PAGE_SIZE - c;
error:
	mutex_unlock(&sl->master->bus_mutex);
	वापस -EIO;
पूर्ण

अटल पूर्णांक __init w1_therm_init(व्योम)
अणु
	पूर्णांक err, i;

	क्रम (i = 0; i < ARRAY_SIZE(w1_therm_families); ++i) अणु
		err = w1_रेजिस्टर_family(w1_therm_families[i].f);
		अगर (err)
			w1_therm_families[i].broken = 1;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम __निकास w1_therm_fini(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(w1_therm_families); ++i)
		अगर (!w1_therm_families[i].broken)
			w1_unरेजिस्टर_family(w1_therm_families[i].f);
पूर्ण

module_init(w1_therm_init);
module_निकास(w1_therm_fini);

MODULE_AUTHOR("Evgeniy Polyakov <zbr@ioremap.net>");
MODULE_DESCRIPTION("Driver for 1-wire Dallas network protocol, temperature family.");
MODULE_LICENSE("GPL");
MODULE_ALIAS("w1-family-" __stringअगरy(W1_THERM_DS18S20));
MODULE_ALIAS("w1-family-" __stringअगरy(W1_THERM_DS1822));
MODULE_ALIAS("w1-family-" __stringअगरy(W1_THERM_DS18B20));
MODULE_ALIAS("w1-family-" __stringअगरy(W1_THERM_DS1825));
MODULE_ALIAS("w1-family-" __stringअगरy(W1_THERM_DS28EA00));
