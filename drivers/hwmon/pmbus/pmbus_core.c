<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Hardware monitoring driver क्रम PMBus devices
 *
 * Copyright (c) 2010, 2011 Ericsson AB.
 * Copyright (c) 2012 Guenter Roeck
 */

#समावेश <linux/debugfs.h>
#समावेश <linux/kernel.h>
#समावेश <linux/math64.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/err.h>
#समावेश <linux/slab.h>
#समावेश <linux/i2c.h>
#समावेश <linux/hwmon.h>
#समावेश <linux/hwmon-sysfs.h>
#समावेश <linux/pmbus.h>
#समावेश <linux/regulator/driver.h>
#समावेश <linux/regulator/machine.h>
#समावेश "pmbus.h"

/*
 * Number of additional attribute poपूर्णांकers to allocate
 * with each call to kपुनः_स्मृति
 */
#घोषणा PMBUS_ATTR_ALLOC_SIZE	32
#घोषणा PMBUS_NAME_SIZE		24

काष्ठा pmbus_sensor अणु
	काष्ठा pmbus_sensor *next;
	अक्षर name[PMBUS_NAME_SIZE];	/* sysfs sensor name */
	काष्ठा device_attribute attribute;
	u8 page;		/* page number */
	u8 phase;		/* phase number, 0xff क्रम all phases */
	u16 reg;		/* रेजिस्टर */
	क्रमागत pmbus_sensor_classes class;	/* sensor class */
	bool update;		/* runसमय sensor update needed */
	bool convert;		/* Whether or not to apply linear/vid/direct */
	पूर्णांक data;		/* Sensor data.
				   Negative अगर there was a पढ़ो error */
पूर्ण;
#घोषणा to_pmbus_sensor(_attr) \
	container_of(_attr, काष्ठा pmbus_sensor, attribute)

काष्ठा pmbus_boolean अणु
	अक्षर name[PMBUS_NAME_SIZE];	/* sysfs boolean name */
	काष्ठा sensor_device_attribute attribute;
	काष्ठा pmbus_sensor *s1;
	काष्ठा pmbus_sensor *s2;
पूर्ण;
#घोषणा to_pmbus_boolean(_attr) \
	container_of(_attr, काष्ठा pmbus_boolean, attribute)

काष्ठा pmbus_label अणु
	अक्षर name[PMBUS_NAME_SIZE];	/* sysfs label name */
	काष्ठा device_attribute attribute;
	अक्षर label[PMBUS_NAME_SIZE];	/* label */
पूर्ण;
#घोषणा to_pmbus_label(_attr) \
	container_of(_attr, काष्ठा pmbus_label, attribute)

/* Macros क्रम converting between sensor index and रेजिस्टर/page/status mask */

#घोषणा PB_STATUS_MASK	0xffff
#घोषणा PB_REG_SHIFT	16
#घोषणा PB_REG_MASK	0x3ff
#घोषणा PB_PAGE_SHIFT	26
#घोषणा PB_PAGE_MASK	0x3f

#घोषणा pb_reg_to_index(page, reg, mask)	(((page) << PB_PAGE_SHIFT) | \
						 ((reg) << PB_REG_SHIFT) | (mask))

#घोषणा pb_index_to_page(index)			(((index) >> PB_PAGE_SHIFT) & PB_PAGE_MASK)
#घोषणा pb_index_to_reg(index)			(((index) >> PB_REG_SHIFT) & PB_REG_MASK)
#घोषणा pb_index_to_mask(index)			((index) & PB_STATUS_MASK)

काष्ठा pmbus_data अणु
	काष्ठा device *dev;
	काष्ठा device *hwmon_dev;

	u32 flags;		/* from platक्रमm data */

	पूर्णांक exponent[PMBUS_PAGES];
				/* linear mode: exponent क्रम output voltages */

	स्थिर काष्ठा pmbus_driver_info *info;

	पूर्णांक max_attributes;
	पूर्णांक num_attributes;
	काष्ठा attribute_group group;
	स्थिर काष्ठा attribute_group **groups;
	काष्ठा dentry *debugfs;		/* debugfs device directory */

	काष्ठा pmbus_sensor *sensors;

	काष्ठा mutex update_lock;

	bool has_status_word;		/* device uses STATUS_WORD रेजिस्टर */
	पूर्णांक (*पढ़ो_status)(काष्ठा i2c_client *client, पूर्णांक page);

	s16 currpage;	/* current page, -1 क्रम unknown/unset */
	s16 currphase;	/* current phase, 0xff क्रम all, -1 क्रम unknown/unset */
पूर्ण;

काष्ठा pmbus_debugfs_entry अणु
	काष्ठा i2c_client *client;
	u8 page;
	u8 reg;
पूर्ण;

अटल स्थिर पूर्णांक pmbus_fan_rpm_mask[] = अणु
	PB_FAN_1_RPM,
	PB_FAN_2_RPM,
	PB_FAN_1_RPM,
	PB_FAN_2_RPM,
पूर्ण;

अटल स्थिर पूर्णांक pmbus_fan_config_रेजिस्टरs[] = अणु
	PMBUS_FAN_CONFIG_12,
	PMBUS_FAN_CONFIG_12,
	PMBUS_FAN_CONFIG_34,
	PMBUS_FAN_CONFIG_34
पूर्ण;

अटल स्थिर पूर्णांक pmbus_fan_command_रेजिस्टरs[] = अणु
	PMBUS_FAN_COMMAND_1,
	PMBUS_FAN_COMMAND_2,
	PMBUS_FAN_COMMAND_3,
	PMBUS_FAN_COMMAND_4,
पूर्ण;

व्योम pmbus_clear_cache(काष्ठा i2c_client *client)
अणु
	काष्ठा pmbus_data *data = i2c_get_clientdata(client);
	काष्ठा pmbus_sensor *sensor;

	क्रम (sensor = data->sensors; sensor; sensor = sensor->next)
		sensor->data = -ENODATA;
पूर्ण
EXPORT_SYMBOL_NS_GPL(pmbus_clear_cache, PMBUS);

व्योम pmbus_set_update(काष्ठा i2c_client *client, u8 reg, bool update)
अणु
	काष्ठा pmbus_data *data = i2c_get_clientdata(client);
	काष्ठा pmbus_sensor *sensor;

	क्रम (sensor = data->sensors; sensor; sensor = sensor->next)
		अगर (sensor->reg == reg)
			sensor->update = update;
पूर्ण
EXPORT_SYMBOL_NS_GPL(pmbus_set_update, PMBUS);

पूर्णांक pmbus_set_page(काष्ठा i2c_client *client, पूर्णांक page, पूर्णांक phase)
अणु
	काष्ठा pmbus_data *data = i2c_get_clientdata(client);
	पूर्णांक rv;

	अगर (page < 0)
		वापस 0;

	अगर (!(data->info->func[page] & PMBUS_PAGE_VIRTUAL) &&
	    data->info->pages > 1 && page != data->currpage) अणु
		rv = i2c_smbus_ग_लिखो_byte_data(client, PMBUS_PAGE, page);
		अगर (rv < 0)
			वापस rv;

		rv = i2c_smbus_पढ़ो_byte_data(client, PMBUS_PAGE);
		अगर (rv < 0)
			वापस rv;

		अगर (rv != page)
			वापस -EIO;
	पूर्ण
	data->currpage = page;

	अगर (data->info->phases[page] && data->currphase != phase &&
	    !(data->info->func[page] & PMBUS_PHASE_VIRTUAL)) अणु
		rv = i2c_smbus_ग_लिखो_byte_data(client, PMBUS_PHASE,
					       phase);
		अगर (rv)
			वापस rv;
	पूर्ण
	data->currphase = phase;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_NS_GPL(pmbus_set_page, PMBUS);

पूर्णांक pmbus_ग_लिखो_byte(काष्ठा i2c_client *client, पूर्णांक page, u8 value)
अणु
	पूर्णांक rv;

	rv = pmbus_set_page(client, page, 0xff);
	अगर (rv < 0)
		वापस rv;

	वापस i2c_smbus_ग_लिखो_byte(client, value);
पूर्ण
EXPORT_SYMBOL_NS_GPL(pmbus_ग_लिखो_byte, PMBUS);

/*
 * _pmbus_ग_लिखो_byte() is similar to pmbus_ग_लिखो_byte(), but checks अगर
 * a device specअगरic mapping function exists and calls it अगर necessary.
 */
अटल पूर्णांक _pmbus_ग_लिखो_byte(काष्ठा i2c_client *client, पूर्णांक page, u8 value)
अणु
	काष्ठा pmbus_data *data = i2c_get_clientdata(client);
	स्थिर काष्ठा pmbus_driver_info *info = data->info;
	पूर्णांक status;

	अगर (info->ग_लिखो_byte) अणु
		status = info->ग_लिखो_byte(client, page, value);
		अगर (status != -ENODATA)
			वापस status;
	पूर्ण
	वापस pmbus_ग_लिखो_byte(client, page, value);
पूर्ण

पूर्णांक pmbus_ग_लिखो_word_data(काष्ठा i2c_client *client, पूर्णांक page, u8 reg,
			  u16 word)
अणु
	पूर्णांक rv;

	rv = pmbus_set_page(client, page, 0xff);
	अगर (rv < 0)
		वापस rv;

	वापस i2c_smbus_ग_लिखो_word_data(client, reg, word);
पूर्ण
EXPORT_SYMBOL_NS_GPL(pmbus_ग_लिखो_word_data, PMBUS);


अटल पूर्णांक pmbus_ग_लिखो_virt_reg(काष्ठा i2c_client *client, पूर्णांक page, पूर्णांक reg,
				u16 word)
अणु
	पूर्णांक bit;
	पूर्णांक id;
	पूर्णांक rv;

	चयन (reg) अणु
	हाल PMBUS_VIRT_FAN_TARGET_1 ... PMBUS_VIRT_FAN_TARGET_4:
		id = reg - PMBUS_VIRT_FAN_TARGET_1;
		bit = pmbus_fan_rpm_mask[id];
		rv = pmbus_update_fan(client, page, id, bit, bit, word);
		अवरोध;
	शेष:
		rv = -ENXIO;
		अवरोध;
	पूर्ण

	वापस rv;
पूर्ण

/*
 * _pmbus_ग_लिखो_word_data() is similar to pmbus_ग_लिखो_word_data(), but checks अगर
 * a device specअगरic mapping function exists and calls it अगर necessary.
 */
अटल पूर्णांक _pmbus_ग_लिखो_word_data(काष्ठा i2c_client *client, पूर्णांक page, पूर्णांक reg,
				  u16 word)
अणु
	काष्ठा pmbus_data *data = i2c_get_clientdata(client);
	स्थिर काष्ठा pmbus_driver_info *info = data->info;
	पूर्णांक status;

	अगर (info->ग_लिखो_word_data) अणु
		status = info->ग_लिखो_word_data(client, page, reg, word);
		अगर (status != -ENODATA)
			वापस status;
	पूर्ण

	अगर (reg >= PMBUS_VIRT_BASE)
		वापस pmbus_ग_लिखो_virt_reg(client, page, reg, word);

	वापस pmbus_ग_लिखो_word_data(client, page, reg, word);
पूर्ण

पूर्णांक pmbus_update_fan(काष्ठा i2c_client *client, पूर्णांक page, पूर्णांक id,
		     u8 config, u8 mask, u16 command)
अणु
	पूर्णांक from;
	पूर्णांक rv;
	u8 to;

	from = pmbus_पढ़ो_byte_data(client, page,
				    pmbus_fan_config_रेजिस्टरs[id]);
	अगर (from < 0)
		वापस from;

	to = (from & ~mask) | (config & mask);
	अगर (to != from) अणु
		rv = pmbus_ग_लिखो_byte_data(client, page,
					   pmbus_fan_config_रेजिस्टरs[id], to);
		अगर (rv < 0)
			वापस rv;
	पूर्ण

	वापस _pmbus_ग_लिखो_word_data(client, page,
				      pmbus_fan_command_रेजिस्टरs[id], command);
पूर्ण
EXPORT_SYMBOL_NS_GPL(pmbus_update_fan, PMBUS);

पूर्णांक pmbus_पढ़ो_word_data(काष्ठा i2c_client *client, पूर्णांक page, पूर्णांक phase, u8 reg)
अणु
	पूर्णांक rv;

	rv = pmbus_set_page(client, page, phase);
	अगर (rv < 0)
		वापस rv;

	वापस i2c_smbus_पढ़ो_word_data(client, reg);
पूर्ण
EXPORT_SYMBOL_NS_GPL(pmbus_पढ़ो_word_data, PMBUS);

अटल पूर्णांक pmbus_पढ़ो_virt_reg(काष्ठा i2c_client *client, पूर्णांक page, पूर्णांक reg)
अणु
	पूर्णांक rv;
	पूर्णांक id;

	चयन (reg) अणु
	हाल PMBUS_VIRT_FAN_TARGET_1 ... PMBUS_VIRT_FAN_TARGET_4:
		id = reg - PMBUS_VIRT_FAN_TARGET_1;
		rv = pmbus_get_fan_rate_device(client, page, id, rpm);
		अवरोध;
	शेष:
		rv = -ENXIO;
		अवरोध;
	पूर्ण

	वापस rv;
पूर्ण

/*
 * _pmbus_पढ़ो_word_data() is similar to pmbus_पढ़ो_word_data(), but checks अगर
 * a device specअगरic mapping function exists and calls it अगर necessary.
 */
अटल पूर्णांक _pmbus_पढ़ो_word_data(काष्ठा i2c_client *client, पूर्णांक page,
				 पूर्णांक phase, पूर्णांक reg)
अणु
	काष्ठा pmbus_data *data = i2c_get_clientdata(client);
	स्थिर काष्ठा pmbus_driver_info *info = data->info;
	पूर्णांक status;

	अगर (info->पढ़ो_word_data) अणु
		status = info->पढ़ो_word_data(client, page, phase, reg);
		अगर (status != -ENODATA)
			वापस status;
	पूर्ण

	अगर (reg >= PMBUS_VIRT_BASE)
		वापस pmbus_पढ़ो_virt_reg(client, page, reg);

	वापस pmbus_पढ़ो_word_data(client, page, phase, reg);
पूर्ण

/* Same as above, but without phase parameter, क्रम use in check functions */
अटल पूर्णांक __pmbus_पढ़ो_word_data(काष्ठा i2c_client *client, पूर्णांक page, पूर्णांक reg)
अणु
	वापस _pmbus_पढ़ो_word_data(client, page, 0xff, reg);
पूर्ण

पूर्णांक pmbus_पढ़ो_byte_data(काष्ठा i2c_client *client, पूर्णांक page, u8 reg)
अणु
	पूर्णांक rv;

	rv = pmbus_set_page(client, page, 0xff);
	अगर (rv < 0)
		वापस rv;

	वापस i2c_smbus_पढ़ो_byte_data(client, reg);
पूर्ण
EXPORT_SYMBOL_NS_GPL(pmbus_पढ़ो_byte_data, PMBUS);

पूर्णांक pmbus_ग_लिखो_byte_data(काष्ठा i2c_client *client, पूर्णांक page, u8 reg, u8 value)
अणु
	पूर्णांक rv;

	rv = pmbus_set_page(client, page, 0xff);
	अगर (rv < 0)
		वापस rv;

	वापस i2c_smbus_ग_लिखो_byte_data(client, reg, value);
पूर्ण
EXPORT_SYMBOL_NS_GPL(pmbus_ग_लिखो_byte_data, PMBUS);

पूर्णांक pmbus_update_byte_data(काष्ठा i2c_client *client, पूर्णांक page, u8 reg,
			   u8 mask, u8 value)
अणु
	अचिन्हित पूर्णांक पंचांगp;
	पूर्णांक rv;

	rv = pmbus_पढ़ो_byte_data(client, page, reg);
	अगर (rv < 0)
		वापस rv;

	पंचांगp = (rv & ~mask) | (value & mask);

	अगर (पंचांगp != rv)
		rv = pmbus_ग_लिखो_byte_data(client, page, reg, पंचांगp);

	वापस rv;
पूर्ण
EXPORT_SYMBOL_NS_GPL(pmbus_update_byte_data, PMBUS);

/*
 * _pmbus_पढ़ो_byte_data() is similar to pmbus_पढ़ो_byte_data(), but checks अगर
 * a device specअगरic mapping function exists and calls it अगर necessary.
 */
अटल पूर्णांक _pmbus_पढ़ो_byte_data(काष्ठा i2c_client *client, पूर्णांक page, पूर्णांक reg)
अणु
	काष्ठा pmbus_data *data = i2c_get_clientdata(client);
	स्थिर काष्ठा pmbus_driver_info *info = data->info;
	पूर्णांक status;

	अगर (info->पढ़ो_byte_data) अणु
		status = info->पढ़ो_byte_data(client, page, reg);
		अगर (status != -ENODATA)
			वापस status;
	पूर्ण
	वापस pmbus_पढ़ो_byte_data(client, page, reg);
पूर्ण

अटल काष्ठा pmbus_sensor *pmbus_find_sensor(काष्ठा pmbus_data *data, पूर्णांक page,
					      पूर्णांक reg)
अणु
	काष्ठा pmbus_sensor *sensor;

	क्रम (sensor = data->sensors; sensor; sensor = sensor->next) अणु
		अगर (sensor->page == page && sensor->reg == reg)
			वापस sensor;
	पूर्ण

	वापस ERR_PTR(-EINVAL);
पूर्ण

अटल पूर्णांक pmbus_get_fan_rate(काष्ठा i2c_client *client, पूर्णांक page, पूर्णांक id,
			      क्रमागत pmbus_fan_mode mode,
			      bool from_cache)
अणु
	काष्ठा pmbus_data *data = i2c_get_clientdata(client);
	bool want_rpm, have_rpm;
	काष्ठा pmbus_sensor *s;
	पूर्णांक config;
	पूर्णांक reg;

	want_rpm = (mode == rpm);

	अगर (from_cache) अणु
		reg = want_rpm ? PMBUS_VIRT_FAN_TARGET_1 : PMBUS_VIRT_PWM_1;
		s = pmbus_find_sensor(data, page, reg + id);
		अगर (IS_ERR(s))
			वापस PTR_ERR(s);

		वापस s->data;
	पूर्ण

	config = pmbus_पढ़ो_byte_data(client, page,
				      pmbus_fan_config_रेजिस्टरs[id]);
	अगर (config < 0)
		वापस config;

	have_rpm = !!(config & pmbus_fan_rpm_mask[id]);
	अगर (want_rpm == have_rpm)
		वापस pmbus_पढ़ो_word_data(client, page, 0xff,
					    pmbus_fan_command_रेजिस्टरs[id]);

	/* Can't sensibly map between RPM and PWM, just वापस zero */
	वापस 0;
पूर्ण

पूर्णांक pmbus_get_fan_rate_device(काष्ठा i2c_client *client, पूर्णांक page, पूर्णांक id,
			      क्रमागत pmbus_fan_mode mode)
अणु
	वापस pmbus_get_fan_rate(client, page, id, mode, false);
पूर्ण
EXPORT_SYMBOL_NS_GPL(pmbus_get_fan_rate_device, PMBUS);

पूर्णांक pmbus_get_fan_rate_cached(काष्ठा i2c_client *client, पूर्णांक page, पूर्णांक id,
			      क्रमागत pmbus_fan_mode mode)
अणु
	वापस pmbus_get_fan_rate(client, page, id, mode, true);
पूर्ण
EXPORT_SYMBOL_NS_GPL(pmbus_get_fan_rate_cached, PMBUS);

अटल व्योम pmbus_clear_fault_page(काष्ठा i2c_client *client, पूर्णांक page)
अणु
	_pmbus_ग_लिखो_byte(client, page, PMBUS_CLEAR_FAULTS);
पूर्ण

व्योम pmbus_clear_faults(काष्ठा i2c_client *client)
अणु
	काष्ठा pmbus_data *data = i2c_get_clientdata(client);
	पूर्णांक i;

	क्रम (i = 0; i < data->info->pages; i++)
		pmbus_clear_fault_page(client, i);
पूर्ण
EXPORT_SYMBOL_NS_GPL(pmbus_clear_faults, PMBUS);

अटल पूर्णांक pmbus_check_status_cml(काष्ठा i2c_client *client)
अणु
	काष्ठा pmbus_data *data = i2c_get_clientdata(client);
	पूर्णांक status, status2;

	status = data->पढ़ो_status(client, -1);
	अगर (status < 0 || (status & PB_STATUS_CML)) अणु
		status2 = _pmbus_पढ़ो_byte_data(client, -1, PMBUS_STATUS_CML);
		अगर (status2 < 0 || (status2 & PB_CML_FAULT_INVALID_COMMAND))
			वापस -EIO;
	पूर्ण
	वापस 0;
पूर्ण

अटल bool pmbus_check_रेजिस्टर(काष्ठा i2c_client *client,
				 पूर्णांक (*func)(काष्ठा i2c_client *client,
					     पूर्णांक page, पूर्णांक reg),
				 पूर्णांक page, पूर्णांक reg)
अणु
	पूर्णांक rv;
	काष्ठा pmbus_data *data = i2c_get_clientdata(client);

	rv = func(client, page, reg);
	अगर (rv >= 0 && !(data->flags & PMBUS_SKIP_STATUS_CHECK))
		rv = pmbus_check_status_cml(client);
	pmbus_clear_fault_page(client, -1);
	वापस rv >= 0;
पूर्ण

अटल bool pmbus_check_status_रेजिस्टर(काष्ठा i2c_client *client, पूर्णांक page)
अणु
	पूर्णांक status;
	काष्ठा pmbus_data *data = i2c_get_clientdata(client);

	status = data->पढ़ो_status(client, page);
	अगर (status >= 0 && !(data->flags & PMBUS_SKIP_STATUS_CHECK) &&
	    (status & PB_STATUS_CML)) अणु
		status = _pmbus_पढ़ो_byte_data(client, -1, PMBUS_STATUS_CML);
		अगर (status < 0 || (status & PB_CML_FAULT_INVALID_COMMAND))
			status = -EIO;
	पूर्ण

	pmbus_clear_fault_page(client, -1);
	वापस status >= 0;
पूर्ण

bool pmbus_check_byte_रेजिस्टर(काष्ठा i2c_client *client, पूर्णांक page, पूर्णांक reg)
अणु
	वापस pmbus_check_रेजिस्टर(client, _pmbus_पढ़ो_byte_data, page, reg);
पूर्ण
EXPORT_SYMBOL_NS_GPL(pmbus_check_byte_रेजिस्टर, PMBUS);

bool pmbus_check_word_रेजिस्टर(काष्ठा i2c_client *client, पूर्णांक page, पूर्णांक reg)
अणु
	वापस pmbus_check_रेजिस्टर(client, __pmbus_पढ़ो_word_data, page, reg);
पूर्ण
EXPORT_SYMBOL_NS_GPL(pmbus_check_word_रेजिस्टर, PMBUS);

स्थिर काष्ठा pmbus_driver_info *pmbus_get_driver_info(काष्ठा i2c_client *client)
अणु
	काष्ठा pmbus_data *data = i2c_get_clientdata(client);

	वापस data->info;
पूर्ण
EXPORT_SYMBOL_NS_GPL(pmbus_get_driver_info, PMBUS);

अटल पूर्णांक pmbus_get_status(काष्ठा i2c_client *client, पूर्णांक page, पूर्णांक reg)
अणु
	काष्ठा pmbus_data *data = i2c_get_clientdata(client);
	पूर्णांक status;

	चयन (reg) अणु
	हाल PMBUS_STATUS_WORD:
		status = data->पढ़ो_status(client, page);
		अवरोध;
	शेष:
		status = _pmbus_पढ़ो_byte_data(client, page, reg);
		अवरोध;
	पूर्ण
	अगर (status < 0)
		pmbus_clear_faults(client);
	वापस status;
पूर्ण

अटल व्योम pmbus_update_sensor_data(काष्ठा i2c_client *client, काष्ठा pmbus_sensor *sensor)
अणु
	अगर (sensor->data < 0 || sensor->update)
		sensor->data = _pmbus_पढ़ो_word_data(client, sensor->page,
						     sensor->phase, sensor->reg);
पूर्ण

/*
 * Convert linear sensor values to milli- or micro-units
 * depending on sensor type.
 */
अटल s64 pmbus_reg2data_linear(काष्ठा pmbus_data *data,
				 काष्ठा pmbus_sensor *sensor)
अणु
	s16 exponent;
	s32 mantissa;
	s64 val;

	अगर (sensor->class == PSC_VOLTAGE_OUT) अणु	/* LINEAR16 */
		exponent = data->exponent[sensor->page];
		mantissa = (u16) sensor->data;
	पूर्ण अन्यथा अणु				/* LINEAR11 */
		exponent = ((s16)sensor->data) >> 11;
		mantissa = ((s16)((sensor->data & 0x7ff) << 5)) >> 5;
	पूर्ण

	val = mantissa;

	/* scale result to milli-units क्रम all sensors except fans */
	अगर (sensor->class != PSC_FAN)
		val = val * 1000LL;

	/* scale result to micro-units क्रम घातer sensors */
	अगर (sensor->class == PSC_POWER)
		val = val * 1000LL;

	अगर (exponent >= 0)
		val <<= exponent;
	अन्यथा
		val >>= -exponent;

	वापस val;
पूर्ण

/*
 * Convert direct sensor values to milli- or micro-units
 * depending on sensor type.
 */
अटल s64 pmbus_reg2data_direct(काष्ठा pmbus_data *data,
				 काष्ठा pmbus_sensor *sensor)
अणु
	s64 b, val = (s16)sensor->data;
	s32 m, R;

	m = data->info->m[sensor->class];
	b = data->info->b[sensor->class];
	R = data->info->R[sensor->class];

	अगर (m == 0)
		वापस 0;

	/* X = 1/m * (Y * 10^-R - b) */
	R = -R;
	/* scale result to milli-units क्रम everything but fans */
	अगर (!(sensor->class == PSC_FAN || sensor->class == PSC_PWM)) अणु
		R += 3;
		b *= 1000;
	पूर्ण

	/* scale result to micro-units क्रम घातer sensors */
	अगर (sensor->class == PSC_POWER) अणु
		R += 3;
		b *= 1000;
	पूर्ण

	जबतक (R > 0) अणु
		val *= 10;
		R--;
	पूर्ण
	जबतक (R < 0) अणु
		val = भाग_s64(val + 5LL, 10L);  /* round बंदst */
		R++;
	पूर्ण

	val = भाग_s64(val - b, m);
	वापस val;
पूर्ण

/*
 * Convert VID sensor values to milli- or micro-units
 * depending on sensor type.
 */
अटल s64 pmbus_reg2data_vid(काष्ठा pmbus_data *data,
			      काष्ठा pmbus_sensor *sensor)
अणु
	दीर्घ val = sensor->data;
	दीर्घ rv = 0;

	चयन (data->info->vrm_version[sensor->page]) अणु
	हाल vr11:
		अगर (val >= 0x02 && val <= 0xb2)
			rv = DIV_ROUND_CLOSEST(160000 - (val - 2) * 625, 100);
		अवरोध;
	हाल vr12:
		अगर (val >= 0x01)
			rv = 250 + (val - 1) * 5;
		अवरोध;
	हाल vr13:
		अगर (val >= 0x01)
			rv = 500 + (val - 1) * 10;
		अवरोध;
	हाल imvp9:
		अगर (val >= 0x01)
			rv = 200 + (val - 1) * 10;
		अवरोध;
	हाल amd625mv:
		अगर (val >= 0x0 && val <= 0xd8)
			rv = DIV_ROUND_CLOSEST(155000 - val * 625, 100);
		अवरोध;
	पूर्ण
	वापस rv;
पूर्ण

अटल s64 pmbus_reg2data(काष्ठा pmbus_data *data, काष्ठा pmbus_sensor *sensor)
अणु
	s64 val;

	अगर (!sensor->convert)
		वापस sensor->data;

	चयन (data->info->क्रमmat[sensor->class]) अणु
	हाल direct:
		val = pmbus_reg2data_direct(data, sensor);
		अवरोध;
	हाल vid:
		val = pmbus_reg2data_vid(data, sensor);
		अवरोध;
	हाल linear:
	शेष:
		val = pmbus_reg2data_linear(data, sensor);
		अवरोध;
	पूर्ण
	वापस val;
पूर्ण

#घोषणा MAX_MANTISSA	(1023 * 1000)
#घोषणा MIN_MANTISSA	(511 * 1000)

अटल u16 pmbus_data2reg_linear(काष्ठा pmbus_data *data,
				 काष्ठा pmbus_sensor *sensor, s64 val)
अणु
	s16 exponent = 0, mantissa;
	bool negative = false;

	/* simple हाल */
	अगर (val == 0)
		वापस 0;

	अगर (sensor->class == PSC_VOLTAGE_OUT) अणु
		/* LINEAR16 करोes not support negative voltages */
		अगर (val < 0)
			वापस 0;

		/*
		 * For a अटल exponents, we करोn't have a choice
		 * but to adjust the value to it.
		 */
		अगर (data->exponent[sensor->page] < 0)
			val <<= -data->exponent[sensor->page];
		अन्यथा
			val >>= data->exponent[sensor->page];
		val = DIV_ROUND_CLOSEST_ULL(val, 1000);
		वापस clamp_val(val, 0, 0xffff);
	पूर्ण

	अगर (val < 0) अणु
		negative = true;
		val = -val;
	पूर्ण

	/* Power is in uW. Convert to mW beक्रमe converting. */
	अगर (sensor->class == PSC_POWER)
		val = DIV_ROUND_CLOSEST_ULL(val, 1000);

	/*
	 * For simplicity, convert fan data to milli-units
	 * beक्रमe calculating the exponent.
	 */
	अगर (sensor->class == PSC_FAN)
		val = val * 1000LL;

	/* Reduce large mantissa until it fits पूर्णांकo 10 bit */
	जबतक (val >= MAX_MANTISSA && exponent < 15) अणु
		exponent++;
		val >>= 1;
	पूर्ण
	/* Increase small mantissa to improve precision */
	जबतक (val < MIN_MANTISSA && exponent > -15) अणु
		exponent--;
		val <<= 1;
	पूर्ण

	/* Convert mantissa from milli-units to units */
	mantissa = clamp_val(DIV_ROUND_CLOSEST_ULL(val, 1000), 0, 0x3ff);

	/* restore sign */
	अगर (negative)
		mantissa = -mantissa;

	/* Convert to 5 bit exponent, 11 bit mantissa */
	वापस (mantissa & 0x7ff) | ((exponent << 11) & 0xf800);
पूर्ण

अटल u16 pmbus_data2reg_direct(काष्ठा pmbus_data *data,
				 काष्ठा pmbus_sensor *sensor, s64 val)
अणु
	s64 b;
	s32 m, R;

	m = data->info->m[sensor->class];
	b = data->info->b[sensor->class];
	R = data->info->R[sensor->class];

	/* Power is in uW. Adjust R and b. */
	अगर (sensor->class == PSC_POWER) अणु
		R -= 3;
		b *= 1000;
	पूर्ण

	/* Calculate Y = (m * X + b) * 10^R */
	अगर (!(sensor->class == PSC_FAN || sensor->class == PSC_PWM)) अणु
		R -= 3;		/* Adjust R and b क्रम data in milli-units */
		b *= 1000;
	पूर्ण
	val = val * m + b;

	जबतक (R > 0) अणु
		val *= 10;
		R--;
	पूर्ण
	जबतक (R < 0) अणु
		val = भाग_s64(val + 5LL, 10L);  /* round बंदst */
		R++;
	पूर्ण

	वापस (u16)clamp_val(val, S16_MIN, S16_MAX);
पूर्ण

अटल u16 pmbus_data2reg_vid(काष्ठा pmbus_data *data,
			      काष्ठा pmbus_sensor *sensor, s64 val)
अणु
	val = clamp_val(val, 500, 1600);

	वापस 2 + DIV_ROUND_CLOSEST_ULL((1600LL - val) * 100LL, 625);
पूर्ण

अटल u16 pmbus_data2reg(काष्ठा pmbus_data *data,
			  काष्ठा pmbus_sensor *sensor, s64 val)
अणु
	u16 regval;

	अगर (!sensor->convert)
		वापस val;

	चयन (data->info->क्रमmat[sensor->class]) अणु
	हाल direct:
		regval = pmbus_data2reg_direct(data, sensor, val);
		अवरोध;
	हाल vid:
		regval = pmbus_data2reg_vid(data, sensor, val);
		अवरोध;
	हाल linear:
	शेष:
		regval = pmbus_data2reg_linear(data, sensor, val);
		अवरोध;
	पूर्ण
	वापस regval;
पूर्ण

/*
 * Return boolean calculated from converted data.
 * <index> defines a status रेजिस्टर index and mask.
 * The mask is in the lower 8 bits, the रेजिस्टर index is in bits 8..23.
 *
 * The associated pmbus_boolean काष्ठाure contains optional poपूर्णांकers to two
 * sensor attributes. If specअगरied, those attributes are compared against each
 * other to determine अगर a limit has been exceeded.
 *
 * If the sensor attribute poपूर्णांकers are शून्य, the function वापसs true अगर
 * (status[reg] & mask) is true.
 *
 * If sensor attribute poपूर्णांकers are provided, a comparison against a specअगरied
 * limit has to be perक्रमmed to determine the boolean result.
 * In this हाल, the function वापसs true अगर v1 >= v2 (where v1 and v2 are
 * sensor values referenced by sensor attribute poपूर्णांकers s1 and s2).
 *
 * To determine अगर an object exceeds upper limits, specअगरy <s1,s2> = <v,limit>.
 * To determine अगर an object exceeds lower limits, specअगरy <s1,s2> = <limit,v>.
 *
 * If a negative value is stored in any of the referenced रेजिस्टरs, this value
 * reflects an error code which will be वापसed.
 */
अटल पूर्णांक pmbus_get_boolean(काष्ठा i2c_client *client, काष्ठा pmbus_boolean *b,
			     पूर्णांक index)
अणु
	काष्ठा pmbus_data *data = i2c_get_clientdata(client);
	काष्ठा pmbus_sensor *s1 = b->s1;
	काष्ठा pmbus_sensor *s2 = b->s2;
	u16 mask = pb_index_to_mask(index);
	u8 page = pb_index_to_page(index);
	u16 reg = pb_index_to_reg(index);
	पूर्णांक ret, status;
	u16 regval;

	mutex_lock(&data->update_lock);
	status = pmbus_get_status(client, page, reg);
	अगर (status < 0) अणु
		ret = status;
		जाओ unlock;
	पूर्ण

	अगर (s1)
		pmbus_update_sensor_data(client, s1);
	अगर (s2)
		pmbus_update_sensor_data(client, s2);

	regval = status & mask;
	अगर (s1 && s2) अणु
		s64 v1, v2;

		अगर (s1->data < 0) अणु
			ret = s1->data;
			जाओ unlock;
		पूर्ण
		अगर (s2->data < 0) अणु
			ret = s2->data;
			जाओ unlock;
		पूर्ण

		v1 = pmbus_reg2data(data, s1);
		v2 = pmbus_reg2data(data, s2);
		ret = !!(regval && v1 >= v2);
	पूर्ण अन्यथा अणु
		ret = !!regval;
	पूर्ण
unlock:
	mutex_unlock(&data->update_lock);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार pmbus_show_boolean(काष्ठा device *dev,
				  काष्ठा device_attribute *da, अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(da);
	काष्ठा pmbus_boolean *boolean = to_pmbus_boolean(attr);
	काष्ठा i2c_client *client = to_i2c_client(dev->parent);
	पूर्णांक val;

	val = pmbus_get_boolean(client, boolean, attr->index);
	अगर (val < 0)
		वापस val;
	वापस sysfs_emit(buf, "%d\n", val);
पूर्ण

अटल sमाप_प्रकार pmbus_show_sensor(काष्ठा device *dev,
				 काष्ठा device_attribute *devattr, अक्षर *buf)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev->parent);
	काष्ठा pmbus_sensor *sensor = to_pmbus_sensor(devattr);
	काष्ठा pmbus_data *data = i2c_get_clientdata(client);
	sमाप_प्रकार ret;

	mutex_lock(&data->update_lock);
	pmbus_update_sensor_data(client, sensor);
	अगर (sensor->data < 0)
		ret = sensor->data;
	अन्यथा
		ret = sysfs_emit(buf, "%lld\n", pmbus_reg2data(data, sensor));
	mutex_unlock(&data->update_lock);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार pmbus_set_sensor(काष्ठा device *dev,
				काष्ठा device_attribute *devattr,
				स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev->parent);
	काष्ठा pmbus_data *data = i2c_get_clientdata(client);
	काष्ठा pmbus_sensor *sensor = to_pmbus_sensor(devattr);
	sमाप_प्रकार rv = count;
	s64 val;
	पूर्णांक ret;
	u16 regval;

	अगर (kstrtos64(buf, 10, &val) < 0)
		वापस -EINVAL;

	mutex_lock(&data->update_lock);
	regval = pmbus_data2reg(data, sensor, val);
	ret = _pmbus_ग_लिखो_word_data(client, sensor->page, sensor->reg, regval);
	अगर (ret < 0)
		rv = ret;
	अन्यथा
		sensor->data = -ENODATA;
	mutex_unlock(&data->update_lock);
	वापस rv;
पूर्ण

अटल sमाप_प्रकार pmbus_show_label(काष्ठा device *dev,
				काष्ठा device_attribute *da, अक्षर *buf)
अणु
	काष्ठा pmbus_label *label = to_pmbus_label(da);

	वापस sysfs_emit(buf, "%s\n", label->label);
पूर्ण

अटल पूर्णांक pmbus_add_attribute(काष्ठा pmbus_data *data, काष्ठा attribute *attr)
अणु
	अगर (data->num_attributes >= data->max_attributes - 1) अणु
		पूर्णांक new_max_attrs = data->max_attributes + PMBUS_ATTR_ALLOC_SIZE;
		व्योम *new_attrs = devm_kपुनः_स्मृति(data->dev, data->group.attrs,
						new_max_attrs * माप(व्योम *),
						GFP_KERNEL);
		अगर (!new_attrs)
			वापस -ENOMEM;
		data->group.attrs = new_attrs;
		data->max_attributes = new_max_attrs;
	पूर्ण

	data->group.attrs[data->num_attributes++] = attr;
	data->group.attrs[data->num_attributes] = शून्य;
	वापस 0;
पूर्ण

अटल व्योम pmbus_dev_attr_init(काष्ठा device_attribute *dev_attr,
				स्थिर अक्षर *name,
				umode_t mode,
				sमाप_प्रकार (*show)(काष्ठा device *dev,
						काष्ठा device_attribute *attr,
						अक्षर *buf),
				sमाप_प्रकार (*store)(काष्ठा device *dev,
						 काष्ठा device_attribute *attr,
						 स्थिर अक्षर *buf, माप_प्रकार count))
अणु
	sysfs_attr_init(&dev_attr->attr);
	dev_attr->attr.name = name;
	dev_attr->attr.mode = mode;
	dev_attr->show = show;
	dev_attr->store = store;
पूर्ण

अटल व्योम pmbus_attr_init(काष्ठा sensor_device_attribute *a,
			    स्थिर अक्षर *name,
			    umode_t mode,
			    sमाप_प्रकार (*show)(काष्ठा device *dev,
					    काष्ठा device_attribute *attr,
					    अक्षर *buf),
			    sमाप_प्रकार (*store)(काष्ठा device *dev,
					     काष्ठा device_attribute *attr,
					     स्थिर अक्षर *buf, माप_प्रकार count),
			    पूर्णांक idx)
अणु
	pmbus_dev_attr_init(&a->dev_attr, name, mode, show, store);
	a->index = idx;
पूर्ण

अटल पूर्णांक pmbus_add_boolean(काष्ठा pmbus_data *data,
			     स्थिर अक्षर *name, स्थिर अक्षर *type, पूर्णांक seq,
			     काष्ठा pmbus_sensor *s1,
			     काष्ठा pmbus_sensor *s2,
			     u8 page, u16 reg, u16 mask)
अणु
	काष्ठा pmbus_boolean *boolean;
	काष्ठा sensor_device_attribute *a;

	अगर (WARN((s1 && !s2) || (!s1 && s2), "Bad s1/s2 parameters\n"))
		वापस -EINVAL;

	boolean = devm_kzalloc(data->dev, माप(*boolean), GFP_KERNEL);
	अगर (!boolean)
		वापस -ENOMEM;

	a = &boolean->attribute;

	snम_लिखो(boolean->name, माप(boolean->name), "%s%d_%s",
		 name, seq, type);
	boolean->s1 = s1;
	boolean->s2 = s2;
	pmbus_attr_init(a, boolean->name, 0444, pmbus_show_boolean, शून्य,
			pb_reg_to_index(page, reg, mask));

	वापस pmbus_add_attribute(data, &a->dev_attr.attr);
पूर्ण

अटल काष्ठा pmbus_sensor *pmbus_add_sensor(काष्ठा pmbus_data *data,
					     स्थिर अक्षर *name, स्थिर अक्षर *type,
					     पूर्णांक seq, पूर्णांक page, पूर्णांक phase,
					     पूर्णांक reg,
					     क्रमागत pmbus_sensor_classes class,
					     bool update, bool पढ़ोonly,
					     bool convert)
अणु
	काष्ठा pmbus_sensor *sensor;
	काष्ठा device_attribute *a;

	sensor = devm_kzalloc(data->dev, माप(*sensor), GFP_KERNEL);
	अगर (!sensor)
		वापस शून्य;
	a = &sensor->attribute;

	अगर (type)
		snम_लिखो(sensor->name, माप(sensor->name), "%s%d_%s",
			 name, seq, type);
	अन्यथा
		snम_लिखो(sensor->name, माप(sensor->name), "%s%d",
			 name, seq);

	अगर (data->flags & PMBUS_WRITE_PROTECTED)
		पढ़ोonly = true;

	sensor->page = page;
	sensor->phase = phase;
	sensor->reg = reg;
	sensor->class = class;
	sensor->update = update;
	sensor->convert = convert;
	sensor->data = -ENODATA;
	pmbus_dev_attr_init(a, sensor->name,
			    पढ़ोonly ? 0444 : 0644,
			    pmbus_show_sensor, pmbus_set_sensor);

	अगर (pmbus_add_attribute(data, &a->attr))
		वापस शून्य;

	sensor->next = data->sensors;
	data->sensors = sensor;

	वापस sensor;
पूर्ण

अटल पूर्णांक pmbus_add_label(काष्ठा pmbus_data *data,
			   स्थिर अक्षर *name, पूर्णांक seq,
			   स्थिर अक्षर *lstring, पूर्णांक index, पूर्णांक phase)
अणु
	काष्ठा pmbus_label *label;
	काष्ठा device_attribute *a;

	label = devm_kzalloc(data->dev, माप(*label), GFP_KERNEL);
	अगर (!label)
		वापस -ENOMEM;

	a = &label->attribute;

	snम_लिखो(label->name, माप(label->name), "%s%d_label", name, seq);
	अगर (!index) अणु
		अगर (phase == 0xff)
			म_नकलन(label->label, lstring,
				माप(label->label) - 1);
		अन्यथा
			snम_लिखो(label->label, माप(label->label), "%s.%d",
				 lstring, phase);
	पूर्ण अन्यथा अणु
		अगर (phase == 0xff)
			snम_लिखो(label->label, माप(label->label), "%s%d",
				 lstring, index);
		अन्यथा
			snम_लिखो(label->label, माप(label->label), "%s%d.%d",
				 lstring, index, phase);
	पूर्ण

	pmbus_dev_attr_init(a, label->name, 0444, pmbus_show_label, शून्य);
	वापस pmbus_add_attribute(data, &a->attr);
पूर्ण

/*
 * Search क्रम attributes. Allocate sensors, booleans, and labels as needed.
 */

/*
 * The pmbus_limit_attr काष्ठाure describes a single limit attribute
 * and its associated alarm attribute.
 */
काष्ठा pmbus_limit_attr अणु
	u16 reg;		/* Limit रेजिस्टर */
	u16 sbit;		/* Alarm attribute status bit */
	bool update;		/* True अगर रेजिस्टर needs updates */
	bool low;		/* True अगर low limit; क्रम limits with compare
				   functions only */
	स्थिर अक्षर *attr;	/* Attribute name */
	स्थिर अक्षर *alarm;	/* Alarm attribute name */
पूर्ण;

/*
 * The pmbus_sensor_attr काष्ठाure describes one sensor attribute. This
 * description includes a reference to the associated limit attributes.
 */
काष्ठा pmbus_sensor_attr अणु
	u16 reg;			/* sensor रेजिस्टर */
	u16 gbit;			/* generic status bit */
	u8 nlimit;			/* # of limit रेजिस्टरs */
	क्रमागत pmbus_sensor_classes class;/* sensor class */
	स्थिर अक्षर *label;		/* sensor label */
	bool paged;			/* true अगर paged sensor */
	bool update;			/* true अगर update needed */
	bool compare;			/* true अगर compare function needed */
	u32 func;			/* sensor mask */
	u32 sfunc;			/* sensor status mask */
	पूर्णांक sreg;			/* status रेजिस्टर */
	स्थिर काष्ठा pmbus_limit_attr *limit;/* limit रेजिस्टरs */
पूर्ण;

/*
 * Add a set of limit attributes and, अगर supported, the associated
 * alarm attributes.
 * वापसs 0 अगर no alarm रेजिस्टर found, 1 अगर an alarm रेजिस्टर was found,
 * < 0 on errors.
 */
अटल पूर्णांक pmbus_add_limit_attrs(काष्ठा i2c_client *client,
				 काष्ठा pmbus_data *data,
				 स्थिर काष्ठा pmbus_driver_info *info,
				 स्थिर अक्षर *name, पूर्णांक index, पूर्णांक page,
				 काष्ठा pmbus_sensor *base,
				 स्थिर काष्ठा pmbus_sensor_attr *attr)
अणु
	स्थिर काष्ठा pmbus_limit_attr *l = attr->limit;
	पूर्णांक nlimit = attr->nlimit;
	पूर्णांक have_alarm = 0;
	पूर्णांक i, ret;
	काष्ठा pmbus_sensor *curr;

	क्रम (i = 0; i < nlimit; i++) अणु
		अगर (pmbus_check_word_रेजिस्टर(client, page, l->reg)) अणु
			curr = pmbus_add_sensor(data, name, l->attr, index,
						page, 0xff, l->reg, attr->class,
						attr->update || l->update,
						false, true);
			अगर (!curr)
				वापस -ENOMEM;
			अगर (l->sbit && (info->func[page] & attr->sfunc)) अणु
				ret = pmbus_add_boolean(data, name,
					l->alarm, index,
					attr->compare ?  l->low ? curr : base
						      : शून्य,
					attr->compare ? l->low ? base : curr
						      : शून्य,
					page, attr->sreg, l->sbit);
				अगर (ret)
					वापस ret;
				have_alarm = 1;
			पूर्ण
		पूर्ण
		l++;
	पूर्ण
	वापस have_alarm;
पूर्ण

अटल पूर्णांक pmbus_add_sensor_attrs_one(काष्ठा i2c_client *client,
				      काष्ठा pmbus_data *data,
				      स्थिर काष्ठा pmbus_driver_info *info,
				      स्थिर अक्षर *name,
				      पूर्णांक index, पूर्णांक page, पूर्णांक phase,
				      स्थिर काष्ठा pmbus_sensor_attr *attr,
				      bool paged)
अणु
	काष्ठा pmbus_sensor *base;
	bool upper = !!(attr->gbit & 0xff00);	/* need to check STATUS_WORD */
	पूर्णांक ret;

	अगर (attr->label) अणु
		ret = pmbus_add_label(data, name, index, attr->label,
				      paged ? page + 1 : 0, phase);
		अगर (ret)
			वापस ret;
	पूर्ण
	base = pmbus_add_sensor(data, name, "input", index, page, phase,
				attr->reg, attr->class, true, true, true);
	अगर (!base)
		वापस -ENOMEM;
	/* No limit and alarm attributes क्रम phase specअगरic sensors */
	अगर (attr->sfunc && phase == 0xff) अणु
		ret = pmbus_add_limit_attrs(client, data, info, name,
					    index, page, base, attr);
		अगर (ret < 0)
			वापस ret;
		/*
		 * Add generic alarm attribute only अगर there are no inभागidual
		 * alarm attributes, अगर there is a global alarm bit, and अगर
		 * the generic status रेजिस्टर (word or byte, depending on
		 * which global bit is set) क्रम this page is accessible.
		 */
		अगर (!ret && attr->gbit &&
		    (!upper || data->has_status_word) &&
		    pmbus_check_status_रेजिस्टर(client, page)) अणु
			ret = pmbus_add_boolean(data, name, "alarm", index,
						शून्य, शून्य,
						page, PMBUS_STATUS_WORD,
						attr->gbit);
			अगर (ret)
				वापस ret;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल bool pmbus_sensor_is_paged(स्थिर काष्ठा pmbus_driver_info *info,
				  स्थिर काष्ठा pmbus_sensor_attr *attr)
अणु
	पूर्णांक p;

	अगर (attr->paged)
		वापस true;

	/*
	 * Some attributes may be present on more than one page despite
	 * not being marked with the paged attribute. If that is the हाल,
	 * then treat the sensor as being paged and add the page suffix to the
	 * attribute name.
	 * We करोn't just add the paged attribute to all such attributes, in
	 * order to मुख्यtain the un-suffixed labels in the हाल where the
	 * attribute is only on page 0.
	 */
	क्रम (p = 1; p < info->pages; p++) अणु
		अगर (info->func[p] & attr->func)
			वापस true;
	पूर्ण
	वापस false;
पूर्ण

अटल पूर्णांक pmbus_add_sensor_attrs(काष्ठा i2c_client *client,
				  काष्ठा pmbus_data *data,
				  स्थिर अक्षर *name,
				  स्थिर काष्ठा pmbus_sensor_attr *attrs,
				  पूर्णांक nattrs)
अणु
	स्थिर काष्ठा pmbus_driver_info *info = data->info;
	पूर्णांक index, i;
	पूर्णांक ret;

	index = 1;
	क्रम (i = 0; i < nattrs; i++) अणु
		पूर्णांक page, pages;
		bool paged = pmbus_sensor_is_paged(info, attrs);

		pages = paged ? info->pages : 1;
		क्रम (page = 0; page < pages; page++) अणु
			अगर (!(info->func[page] & attrs->func))
				जारी;
			ret = pmbus_add_sensor_attrs_one(client, data, info,
							 name, index, page,
							 0xff, attrs, paged);
			अगर (ret)
				वापस ret;
			index++;
			अगर (info->phases[page]) अणु
				पूर्णांक phase;

				क्रम (phase = 0; phase < info->phases[page];
				     phase++) अणु
					अगर (!(info->pfunc[phase] & attrs->func))
						जारी;
					ret = pmbus_add_sensor_attrs_one(client,
						data, info, name, index, page,
						phase, attrs, paged);
					अगर (ret)
						वापस ret;
					index++;
				पूर्ण
			पूर्ण
		पूर्ण
		attrs++;
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा pmbus_limit_attr vin_limit_attrs[] = अणु
	अणु
		.reg = PMBUS_VIN_UV_WARN_LIMIT,
		.attr = "min",
		.alarm = "min_alarm",
		.sbit = PB_VOLTAGE_UV_WARNING,
	पूर्ण, अणु
		.reg = PMBUS_VIN_UV_FAULT_LIMIT,
		.attr = "lcrit",
		.alarm = "lcrit_alarm",
		.sbit = PB_VOLTAGE_UV_FAULT,
	पूर्ण, अणु
		.reg = PMBUS_VIN_OV_WARN_LIMIT,
		.attr = "max",
		.alarm = "max_alarm",
		.sbit = PB_VOLTAGE_OV_WARNING,
	पूर्ण, अणु
		.reg = PMBUS_VIN_OV_FAULT_LIMIT,
		.attr = "crit",
		.alarm = "crit_alarm",
		.sbit = PB_VOLTAGE_OV_FAULT,
	पूर्ण, अणु
		.reg = PMBUS_VIRT_READ_VIN_AVG,
		.update = true,
		.attr = "average",
	पूर्ण, अणु
		.reg = PMBUS_VIRT_READ_VIN_MIN,
		.update = true,
		.attr = "lowest",
	पूर्ण, अणु
		.reg = PMBUS_VIRT_READ_VIN_MAX,
		.update = true,
		.attr = "highest",
	पूर्ण, अणु
		.reg = PMBUS_VIRT_RESET_VIN_HISTORY,
		.attr = "reset_history",
	पूर्ण, अणु
		.reg = PMBUS_MFR_VIN_MIN,
		.attr = "rated_min",
	पूर्ण, अणु
		.reg = PMBUS_MFR_VIN_MAX,
		.attr = "rated_max",
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा pmbus_limit_attr vmon_limit_attrs[] = अणु
	अणु
		.reg = PMBUS_VIRT_VMON_UV_WARN_LIMIT,
		.attr = "min",
		.alarm = "min_alarm",
		.sbit = PB_VOLTAGE_UV_WARNING,
	पूर्ण, अणु
		.reg = PMBUS_VIRT_VMON_UV_FAULT_LIMIT,
		.attr = "lcrit",
		.alarm = "lcrit_alarm",
		.sbit = PB_VOLTAGE_UV_FAULT,
	पूर्ण, अणु
		.reg = PMBUS_VIRT_VMON_OV_WARN_LIMIT,
		.attr = "max",
		.alarm = "max_alarm",
		.sbit = PB_VOLTAGE_OV_WARNING,
	पूर्ण, अणु
		.reg = PMBUS_VIRT_VMON_OV_FAULT_LIMIT,
		.attr = "crit",
		.alarm = "crit_alarm",
		.sbit = PB_VOLTAGE_OV_FAULT,
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा pmbus_limit_attr vout_limit_attrs[] = अणु
	अणु
		.reg = PMBUS_VOUT_UV_WARN_LIMIT,
		.attr = "min",
		.alarm = "min_alarm",
		.sbit = PB_VOLTAGE_UV_WARNING,
	पूर्ण, अणु
		.reg = PMBUS_VOUT_UV_FAULT_LIMIT,
		.attr = "lcrit",
		.alarm = "lcrit_alarm",
		.sbit = PB_VOLTAGE_UV_FAULT,
	पूर्ण, अणु
		.reg = PMBUS_VOUT_OV_WARN_LIMIT,
		.attr = "max",
		.alarm = "max_alarm",
		.sbit = PB_VOLTAGE_OV_WARNING,
	पूर्ण, अणु
		.reg = PMBUS_VOUT_OV_FAULT_LIMIT,
		.attr = "crit",
		.alarm = "crit_alarm",
		.sbit = PB_VOLTAGE_OV_FAULT,
	पूर्ण, अणु
		.reg = PMBUS_VIRT_READ_VOUT_AVG,
		.update = true,
		.attr = "average",
	पूर्ण, अणु
		.reg = PMBUS_VIRT_READ_VOUT_MIN,
		.update = true,
		.attr = "lowest",
	पूर्ण, अणु
		.reg = PMBUS_VIRT_READ_VOUT_MAX,
		.update = true,
		.attr = "highest",
	पूर्ण, अणु
		.reg = PMBUS_VIRT_RESET_VOUT_HISTORY,
		.attr = "reset_history",
	पूर्ण, अणु
		.reg = PMBUS_MFR_VOUT_MIN,
		.attr = "rated_min",
	पूर्ण, अणु
		.reg = PMBUS_MFR_VOUT_MAX,
		.attr = "rated_max",
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा pmbus_sensor_attr voltage_attributes[] = अणु
	अणु
		.reg = PMBUS_READ_VIN,
		.class = PSC_VOLTAGE_IN,
		.label = "vin",
		.func = PMBUS_HAVE_VIN,
		.sfunc = PMBUS_HAVE_STATUS_INPUT,
		.sreg = PMBUS_STATUS_INPUT,
		.gbit = PB_STATUS_VIN_UV,
		.limit = vin_limit_attrs,
		.nlimit = ARRAY_SIZE(vin_limit_attrs),
	पूर्ण, अणु
		.reg = PMBUS_VIRT_READ_VMON,
		.class = PSC_VOLTAGE_IN,
		.label = "vmon",
		.func = PMBUS_HAVE_VMON,
		.sfunc = PMBUS_HAVE_STATUS_VMON,
		.sreg = PMBUS_VIRT_STATUS_VMON,
		.limit = vmon_limit_attrs,
		.nlimit = ARRAY_SIZE(vmon_limit_attrs),
	पूर्ण, अणु
		.reg = PMBUS_READ_VCAP,
		.class = PSC_VOLTAGE_IN,
		.label = "vcap",
		.func = PMBUS_HAVE_VCAP,
	पूर्ण, अणु
		.reg = PMBUS_READ_VOUT,
		.class = PSC_VOLTAGE_OUT,
		.label = "vout",
		.paged = true,
		.func = PMBUS_HAVE_VOUT,
		.sfunc = PMBUS_HAVE_STATUS_VOUT,
		.sreg = PMBUS_STATUS_VOUT,
		.gbit = PB_STATUS_VOUT_OV,
		.limit = vout_limit_attrs,
		.nlimit = ARRAY_SIZE(vout_limit_attrs),
	पूर्ण
पूर्ण;

/* Current attributes */

अटल स्थिर काष्ठा pmbus_limit_attr iin_limit_attrs[] = अणु
	अणु
		.reg = PMBUS_IIN_OC_WARN_LIMIT,
		.attr = "max",
		.alarm = "max_alarm",
		.sbit = PB_IIN_OC_WARNING,
	पूर्ण, अणु
		.reg = PMBUS_IIN_OC_FAULT_LIMIT,
		.attr = "crit",
		.alarm = "crit_alarm",
		.sbit = PB_IIN_OC_FAULT,
	पूर्ण, अणु
		.reg = PMBUS_VIRT_READ_IIN_AVG,
		.update = true,
		.attr = "average",
	पूर्ण, अणु
		.reg = PMBUS_VIRT_READ_IIN_MIN,
		.update = true,
		.attr = "lowest",
	पूर्ण, अणु
		.reg = PMBUS_VIRT_READ_IIN_MAX,
		.update = true,
		.attr = "highest",
	पूर्ण, अणु
		.reg = PMBUS_VIRT_RESET_IIN_HISTORY,
		.attr = "reset_history",
	पूर्ण, अणु
		.reg = PMBUS_MFR_IIN_MAX,
		.attr = "rated_max",
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा pmbus_limit_attr iout_limit_attrs[] = अणु
	अणु
		.reg = PMBUS_IOUT_OC_WARN_LIMIT,
		.attr = "max",
		.alarm = "max_alarm",
		.sbit = PB_IOUT_OC_WARNING,
	पूर्ण, अणु
		.reg = PMBUS_IOUT_UC_FAULT_LIMIT,
		.attr = "lcrit",
		.alarm = "lcrit_alarm",
		.sbit = PB_IOUT_UC_FAULT,
	पूर्ण, अणु
		.reg = PMBUS_IOUT_OC_FAULT_LIMIT,
		.attr = "crit",
		.alarm = "crit_alarm",
		.sbit = PB_IOUT_OC_FAULT,
	पूर्ण, अणु
		.reg = PMBUS_VIRT_READ_IOUT_AVG,
		.update = true,
		.attr = "average",
	पूर्ण, अणु
		.reg = PMBUS_VIRT_READ_IOUT_MIN,
		.update = true,
		.attr = "lowest",
	पूर्ण, अणु
		.reg = PMBUS_VIRT_READ_IOUT_MAX,
		.update = true,
		.attr = "highest",
	पूर्ण, अणु
		.reg = PMBUS_VIRT_RESET_IOUT_HISTORY,
		.attr = "reset_history",
	पूर्ण, अणु
		.reg = PMBUS_MFR_IOUT_MAX,
		.attr = "rated_max",
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा pmbus_sensor_attr current_attributes[] = अणु
	अणु
		.reg = PMBUS_READ_IIN,
		.class = PSC_CURRENT_IN,
		.label = "iin",
		.func = PMBUS_HAVE_IIN,
		.sfunc = PMBUS_HAVE_STATUS_INPUT,
		.sreg = PMBUS_STATUS_INPUT,
		.gbit = PB_STATUS_INPUT,
		.limit = iin_limit_attrs,
		.nlimit = ARRAY_SIZE(iin_limit_attrs),
	पूर्ण, अणु
		.reg = PMBUS_READ_IOUT,
		.class = PSC_CURRENT_OUT,
		.label = "iout",
		.paged = true,
		.func = PMBUS_HAVE_IOUT,
		.sfunc = PMBUS_HAVE_STATUS_IOUT,
		.sreg = PMBUS_STATUS_IOUT,
		.gbit = PB_STATUS_IOUT_OC,
		.limit = iout_limit_attrs,
		.nlimit = ARRAY_SIZE(iout_limit_attrs),
	पूर्ण
पूर्ण;

/* Power attributes */

अटल स्थिर काष्ठा pmbus_limit_attr pin_limit_attrs[] = अणु
	अणु
		.reg = PMBUS_PIN_OP_WARN_LIMIT,
		.attr = "max",
		.alarm = "alarm",
		.sbit = PB_PIN_OP_WARNING,
	पूर्ण, अणु
		.reg = PMBUS_VIRT_READ_PIN_AVG,
		.update = true,
		.attr = "average",
	पूर्ण, अणु
		.reg = PMBUS_VIRT_READ_PIN_MIN,
		.update = true,
		.attr = "input_lowest",
	पूर्ण, अणु
		.reg = PMBUS_VIRT_READ_PIN_MAX,
		.update = true,
		.attr = "input_highest",
	पूर्ण, अणु
		.reg = PMBUS_VIRT_RESET_PIN_HISTORY,
		.attr = "reset_history",
	पूर्ण, अणु
		.reg = PMBUS_MFR_PIN_MAX,
		.attr = "rated_max",
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा pmbus_limit_attr pout_limit_attrs[] = अणु
	अणु
		.reg = PMBUS_POUT_MAX,
		.attr = "cap",
		.alarm = "cap_alarm",
		.sbit = PB_POWER_LIMITING,
	पूर्ण, अणु
		.reg = PMBUS_POUT_OP_WARN_LIMIT,
		.attr = "max",
		.alarm = "max_alarm",
		.sbit = PB_POUT_OP_WARNING,
	पूर्ण, अणु
		.reg = PMBUS_POUT_OP_FAULT_LIMIT,
		.attr = "crit",
		.alarm = "crit_alarm",
		.sbit = PB_POUT_OP_FAULT,
	पूर्ण, अणु
		.reg = PMBUS_VIRT_READ_POUT_AVG,
		.update = true,
		.attr = "average",
	पूर्ण, अणु
		.reg = PMBUS_VIRT_READ_POUT_MIN,
		.update = true,
		.attr = "input_lowest",
	पूर्ण, अणु
		.reg = PMBUS_VIRT_READ_POUT_MAX,
		.update = true,
		.attr = "input_highest",
	पूर्ण, अणु
		.reg = PMBUS_VIRT_RESET_POUT_HISTORY,
		.attr = "reset_history",
	पूर्ण, अणु
		.reg = PMBUS_MFR_POUT_MAX,
		.attr = "rated_max",
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा pmbus_sensor_attr घातer_attributes[] = अणु
	अणु
		.reg = PMBUS_READ_PIN,
		.class = PSC_POWER,
		.label = "pin",
		.func = PMBUS_HAVE_PIN,
		.sfunc = PMBUS_HAVE_STATUS_INPUT,
		.sreg = PMBUS_STATUS_INPUT,
		.gbit = PB_STATUS_INPUT,
		.limit = pin_limit_attrs,
		.nlimit = ARRAY_SIZE(pin_limit_attrs),
	पूर्ण, अणु
		.reg = PMBUS_READ_POUT,
		.class = PSC_POWER,
		.label = "pout",
		.paged = true,
		.func = PMBUS_HAVE_POUT,
		.sfunc = PMBUS_HAVE_STATUS_IOUT,
		.sreg = PMBUS_STATUS_IOUT,
		.limit = pout_limit_attrs,
		.nlimit = ARRAY_SIZE(pout_limit_attrs),
	पूर्ण
पूर्ण;

/* Temperature atributes */

अटल स्थिर काष्ठा pmbus_limit_attr temp_limit_attrs[] = अणु
	अणु
		.reg = PMBUS_UT_WARN_LIMIT,
		.low = true,
		.attr = "min",
		.alarm = "min_alarm",
		.sbit = PB_TEMP_UT_WARNING,
	पूर्ण, अणु
		.reg = PMBUS_UT_FAULT_LIMIT,
		.low = true,
		.attr = "lcrit",
		.alarm = "lcrit_alarm",
		.sbit = PB_TEMP_UT_FAULT,
	पूर्ण, अणु
		.reg = PMBUS_OT_WARN_LIMIT,
		.attr = "max",
		.alarm = "max_alarm",
		.sbit = PB_TEMP_OT_WARNING,
	पूर्ण, अणु
		.reg = PMBUS_OT_FAULT_LIMIT,
		.attr = "crit",
		.alarm = "crit_alarm",
		.sbit = PB_TEMP_OT_FAULT,
	पूर्ण, अणु
		.reg = PMBUS_VIRT_READ_TEMP_MIN,
		.attr = "lowest",
	पूर्ण, अणु
		.reg = PMBUS_VIRT_READ_TEMP_AVG,
		.attr = "average",
	पूर्ण, अणु
		.reg = PMBUS_VIRT_READ_TEMP_MAX,
		.attr = "highest",
	पूर्ण, अणु
		.reg = PMBUS_VIRT_RESET_TEMP_HISTORY,
		.attr = "reset_history",
	पूर्ण, अणु
		.reg = PMBUS_MFR_MAX_TEMP_1,
		.attr = "rated_max",
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा pmbus_limit_attr temp_limit_attrs2[] = अणु
	अणु
		.reg = PMBUS_UT_WARN_LIMIT,
		.low = true,
		.attr = "min",
		.alarm = "min_alarm",
		.sbit = PB_TEMP_UT_WARNING,
	पूर्ण, अणु
		.reg = PMBUS_UT_FAULT_LIMIT,
		.low = true,
		.attr = "lcrit",
		.alarm = "lcrit_alarm",
		.sbit = PB_TEMP_UT_FAULT,
	पूर्ण, अणु
		.reg = PMBUS_OT_WARN_LIMIT,
		.attr = "max",
		.alarm = "max_alarm",
		.sbit = PB_TEMP_OT_WARNING,
	पूर्ण, अणु
		.reg = PMBUS_OT_FAULT_LIMIT,
		.attr = "crit",
		.alarm = "crit_alarm",
		.sbit = PB_TEMP_OT_FAULT,
	पूर्ण, अणु
		.reg = PMBUS_VIRT_READ_TEMP2_MIN,
		.attr = "lowest",
	पूर्ण, अणु
		.reg = PMBUS_VIRT_READ_TEMP2_AVG,
		.attr = "average",
	पूर्ण, अणु
		.reg = PMBUS_VIRT_READ_TEMP2_MAX,
		.attr = "highest",
	पूर्ण, अणु
		.reg = PMBUS_VIRT_RESET_TEMP2_HISTORY,
		.attr = "reset_history",
	पूर्ण, अणु
		.reg = PMBUS_MFR_MAX_TEMP_2,
		.attr = "rated_max",
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा pmbus_limit_attr temp_limit_attrs3[] = अणु
	अणु
		.reg = PMBUS_UT_WARN_LIMIT,
		.low = true,
		.attr = "min",
		.alarm = "min_alarm",
		.sbit = PB_TEMP_UT_WARNING,
	पूर्ण, अणु
		.reg = PMBUS_UT_FAULT_LIMIT,
		.low = true,
		.attr = "lcrit",
		.alarm = "lcrit_alarm",
		.sbit = PB_TEMP_UT_FAULT,
	पूर्ण, अणु
		.reg = PMBUS_OT_WARN_LIMIT,
		.attr = "max",
		.alarm = "max_alarm",
		.sbit = PB_TEMP_OT_WARNING,
	पूर्ण, अणु
		.reg = PMBUS_OT_FAULT_LIMIT,
		.attr = "crit",
		.alarm = "crit_alarm",
		.sbit = PB_TEMP_OT_FAULT,
	पूर्ण, अणु
		.reg = PMBUS_MFR_MAX_TEMP_3,
		.attr = "rated_max",
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा pmbus_sensor_attr temp_attributes[] = अणु
	अणु
		.reg = PMBUS_READ_TEMPERATURE_1,
		.class = PSC_TEMPERATURE,
		.paged = true,
		.update = true,
		.compare = true,
		.func = PMBUS_HAVE_TEMP,
		.sfunc = PMBUS_HAVE_STATUS_TEMP,
		.sreg = PMBUS_STATUS_TEMPERATURE,
		.gbit = PB_STATUS_TEMPERATURE,
		.limit = temp_limit_attrs,
		.nlimit = ARRAY_SIZE(temp_limit_attrs),
	पूर्ण, अणु
		.reg = PMBUS_READ_TEMPERATURE_2,
		.class = PSC_TEMPERATURE,
		.paged = true,
		.update = true,
		.compare = true,
		.func = PMBUS_HAVE_TEMP2,
		.sfunc = PMBUS_HAVE_STATUS_TEMP,
		.sreg = PMBUS_STATUS_TEMPERATURE,
		.gbit = PB_STATUS_TEMPERATURE,
		.limit = temp_limit_attrs2,
		.nlimit = ARRAY_SIZE(temp_limit_attrs2),
	पूर्ण, अणु
		.reg = PMBUS_READ_TEMPERATURE_3,
		.class = PSC_TEMPERATURE,
		.paged = true,
		.update = true,
		.compare = true,
		.func = PMBUS_HAVE_TEMP3,
		.sfunc = PMBUS_HAVE_STATUS_TEMP,
		.sreg = PMBUS_STATUS_TEMPERATURE,
		.gbit = PB_STATUS_TEMPERATURE,
		.limit = temp_limit_attrs3,
		.nlimit = ARRAY_SIZE(temp_limit_attrs3),
	पूर्ण
पूर्ण;

अटल स्थिर पूर्णांक pmbus_fan_रेजिस्टरs[] = अणु
	PMBUS_READ_FAN_SPEED_1,
	PMBUS_READ_FAN_SPEED_2,
	PMBUS_READ_FAN_SPEED_3,
	PMBUS_READ_FAN_SPEED_4
पूर्ण;

अटल स्थिर पूर्णांक pmbus_fan_status_रेजिस्टरs[] = अणु
	PMBUS_STATUS_FAN_12,
	PMBUS_STATUS_FAN_12,
	PMBUS_STATUS_FAN_34,
	PMBUS_STATUS_FAN_34
पूर्ण;

अटल स्थिर u32 pmbus_fan_flags[] = अणु
	PMBUS_HAVE_FAN12,
	PMBUS_HAVE_FAN12,
	PMBUS_HAVE_FAN34,
	PMBUS_HAVE_FAN34
पूर्ण;

अटल स्थिर u32 pmbus_fan_status_flags[] = अणु
	PMBUS_HAVE_STATUS_FAN12,
	PMBUS_HAVE_STATUS_FAN12,
	PMBUS_HAVE_STATUS_FAN34,
	PMBUS_HAVE_STATUS_FAN34
पूर्ण;

/* Fans */

/* Precondition: FAN_CONFIG_x_y and FAN_COMMAND_x must exist क्रम the fan ID */
अटल पूर्णांक pmbus_add_fan_ctrl(काष्ठा i2c_client *client,
		काष्ठा pmbus_data *data, पूर्णांक index, पूर्णांक page, पूर्णांक id,
		u8 config)
अणु
	काष्ठा pmbus_sensor *sensor;

	sensor = pmbus_add_sensor(data, "fan", "target", index, page,
				  0xff, PMBUS_VIRT_FAN_TARGET_1 + id, PSC_FAN,
				  false, false, true);

	अगर (!sensor)
		वापस -ENOMEM;

	अगर (!((data->info->func[page] & PMBUS_HAVE_PWM12) ||
			(data->info->func[page] & PMBUS_HAVE_PWM34)))
		वापस 0;

	sensor = pmbus_add_sensor(data, "pwm", शून्य, index, page,
				  0xff, PMBUS_VIRT_PWM_1 + id, PSC_PWM,
				  false, false, true);

	अगर (!sensor)
		वापस -ENOMEM;

	sensor = pmbus_add_sensor(data, "pwm", "enable", index, page,
				  0xff, PMBUS_VIRT_PWM_ENABLE_1 + id, PSC_PWM,
				  true, false, false);

	अगर (!sensor)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

अटल पूर्णांक pmbus_add_fan_attributes(काष्ठा i2c_client *client,
				    काष्ठा pmbus_data *data)
अणु
	स्थिर काष्ठा pmbus_driver_info *info = data->info;
	पूर्णांक index = 1;
	पूर्णांक page;
	पूर्णांक ret;

	क्रम (page = 0; page < info->pages; page++) अणु
		पूर्णांक f;

		क्रम (f = 0; f < ARRAY_SIZE(pmbus_fan_रेजिस्टरs); f++) अणु
			पूर्णांक regval;

			अगर (!(info->func[page] & pmbus_fan_flags[f]))
				अवरोध;

			अगर (!pmbus_check_word_रेजिस्टर(client, page,
						       pmbus_fan_रेजिस्टरs[f]))
				अवरोध;

			/*
			 * Skip fan अगर not installed.
			 * Each fan configuration रेजिस्टर covers multiple fans,
			 * so we have to करो some magic.
			 */
			regval = _pmbus_पढ़ो_byte_data(client, page,
				pmbus_fan_config_रेजिस्टरs[f]);
			अगर (regval < 0 ||
			    (!(regval & (PB_FAN_1_INSTALLED >> ((f & 1) * 4)))))
				जारी;

			अगर (pmbus_add_sensor(data, "fan", "input", index,
					     page, 0xff, pmbus_fan_रेजिस्टरs[f],
					     PSC_FAN, true, true, true) == शून्य)
				वापस -ENOMEM;

			/* Fan control */
			अगर (pmbus_check_word_रेजिस्टर(client, page,
					pmbus_fan_command_रेजिस्टरs[f])) अणु
				ret = pmbus_add_fan_ctrl(client, data, index,
							 page, f, regval);
				अगर (ret < 0)
					वापस ret;
			पूर्ण

			/*
			 * Each fan status रेजिस्टर covers multiple fans,
			 * so we have to करो some magic.
			 */
			अगर ((info->func[page] & pmbus_fan_status_flags[f]) &&
			    pmbus_check_byte_रेजिस्टर(client,
					page, pmbus_fan_status_रेजिस्टरs[f])) अणु
				पूर्णांक reg;

				अगर (f > 1)	/* fan 3, 4 */
					reg = PMBUS_STATUS_FAN_34;
				अन्यथा
					reg = PMBUS_STATUS_FAN_12;
				ret = pmbus_add_boolean(data, "fan",
					"alarm", index, शून्य, शून्य, page, reg,
					PB_FAN_FAN1_WARNING >> (f & 1));
				अगर (ret)
					वापस ret;
				ret = pmbus_add_boolean(data, "fan",
					"fault", index, शून्य, शून्य, page, reg,
					PB_FAN_FAN1_FAULT >> (f & 1));
				अगर (ret)
					वापस ret;
			पूर्ण
			index++;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

काष्ठा pmbus_samples_attr अणु
	पूर्णांक reg;
	अक्षर *name;
पूर्ण;

काष्ठा pmbus_samples_reg अणु
	पूर्णांक page;
	काष्ठा pmbus_samples_attr *attr;
	काष्ठा device_attribute dev_attr;
पूर्ण;

अटल काष्ठा pmbus_samples_attr pmbus_samples_रेजिस्टरs[] = अणु
	अणु
		.reg = PMBUS_VIRT_SAMPLES,
		.name = "samples",
	पूर्ण, अणु
		.reg = PMBUS_VIRT_IN_SAMPLES,
		.name = "in_samples",
	पूर्ण, अणु
		.reg = PMBUS_VIRT_CURR_SAMPLES,
		.name = "curr_samples",
	पूर्ण, अणु
		.reg = PMBUS_VIRT_POWER_SAMPLES,
		.name = "power_samples",
	पूर्ण, अणु
		.reg = PMBUS_VIRT_TEMP_SAMPLES,
		.name = "temp_samples",
	पूर्ण
पूर्ण;

#घोषणा to_samples_reg(x) container_of(x, काष्ठा pmbus_samples_reg, dev_attr)

अटल sमाप_प्रकार pmbus_show_samples(काष्ठा device *dev,
				  काष्ठा device_attribute *devattr, अक्षर *buf)
अणु
	पूर्णांक val;
	काष्ठा i2c_client *client = to_i2c_client(dev->parent);
	काष्ठा pmbus_samples_reg *reg = to_samples_reg(devattr);
	काष्ठा pmbus_data *data = i2c_get_clientdata(client);

	mutex_lock(&data->update_lock);
	val = _pmbus_पढ़ो_word_data(client, reg->page, 0xff, reg->attr->reg);
	mutex_unlock(&data->update_lock);
	अगर (val < 0)
		वापस val;

	वापस sysfs_emit(buf, "%d\n", val);
पूर्ण

अटल sमाप_प्रकार pmbus_set_samples(काष्ठा device *dev,
				 काष्ठा device_attribute *devattr,
				 स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक ret;
	दीर्घ val;
	काष्ठा i2c_client *client = to_i2c_client(dev->parent);
	काष्ठा pmbus_samples_reg *reg = to_samples_reg(devattr);
	काष्ठा pmbus_data *data = i2c_get_clientdata(client);

	अगर (kम_से_दीर्घ(buf, 0, &val) < 0)
		वापस -EINVAL;

	mutex_lock(&data->update_lock);
	ret = _pmbus_ग_लिखो_word_data(client, reg->page, reg->attr->reg, val);
	mutex_unlock(&data->update_lock);

	वापस ret ? : count;
पूर्ण

अटल पूर्णांक pmbus_add_samples_attr(काष्ठा pmbus_data *data, पूर्णांक page,
				  काष्ठा pmbus_samples_attr *attr)
अणु
	काष्ठा pmbus_samples_reg *reg;

	reg = devm_kzalloc(data->dev, माप(*reg), GFP_KERNEL);
	अगर (!reg)
		वापस -ENOMEM;

	reg->attr = attr;
	reg->page = page;

	pmbus_dev_attr_init(&reg->dev_attr, attr->name, 0644,
			    pmbus_show_samples, pmbus_set_samples);

	वापस pmbus_add_attribute(data, &reg->dev_attr.attr);
पूर्ण

अटल पूर्णांक pmbus_add_samples_attributes(काष्ठा i2c_client *client,
					काष्ठा pmbus_data *data)
अणु
	स्थिर काष्ठा pmbus_driver_info *info = data->info;
	पूर्णांक s;

	अगर (!(info->func[0] & PMBUS_HAVE_SAMPLES))
		वापस 0;

	क्रम (s = 0; s < ARRAY_SIZE(pmbus_samples_रेजिस्टरs); s++) अणु
		काष्ठा pmbus_samples_attr *attr;
		पूर्णांक ret;

		attr = &pmbus_samples_रेजिस्टरs[s];
		अगर (!pmbus_check_word_रेजिस्टर(client, 0, attr->reg))
			जारी;

		ret = pmbus_add_samples_attr(data, 0, attr);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक pmbus_find_attributes(काष्ठा i2c_client *client,
				 काष्ठा pmbus_data *data)
अणु
	पूर्णांक ret;

	/* Voltage sensors */
	ret = pmbus_add_sensor_attrs(client, data, "in", voltage_attributes,
				     ARRAY_SIZE(voltage_attributes));
	अगर (ret)
		वापस ret;

	/* Current sensors */
	ret = pmbus_add_sensor_attrs(client, data, "curr", current_attributes,
				     ARRAY_SIZE(current_attributes));
	अगर (ret)
		वापस ret;

	/* Power sensors */
	ret = pmbus_add_sensor_attrs(client, data, "power", घातer_attributes,
				     ARRAY_SIZE(घातer_attributes));
	अगर (ret)
		वापस ret;

	/* Temperature sensors */
	ret = pmbus_add_sensor_attrs(client, data, "temp", temp_attributes,
				     ARRAY_SIZE(temp_attributes));
	अगर (ret)
		वापस ret;

	/* Fans */
	ret = pmbus_add_fan_attributes(client, data);
	अगर (ret)
		वापस ret;

	ret = pmbus_add_samples_attributes(client, data);
	वापस ret;
पूर्ण

/*
 * Identअगरy chip parameters.
 * This function is called क्रम all chips.
 */
अटल पूर्णांक pmbus_identअगरy_common(काष्ठा i2c_client *client,
				 काष्ठा pmbus_data *data, पूर्णांक page)
अणु
	पूर्णांक vout_mode = -1;

	अगर (pmbus_check_byte_रेजिस्टर(client, page, PMBUS_VOUT_MODE))
		vout_mode = _pmbus_पढ़ो_byte_data(client, page,
						  PMBUS_VOUT_MODE);
	अगर (vout_mode >= 0 && vout_mode != 0xff) अणु
		/*
		 * Not all chips support the VOUT_MODE command,
		 * so a failure to पढ़ो it is not an error.
		 */
		चयन (vout_mode >> 5) अणु
		हाल 0:	/* linear mode      */
			अगर (data->info->क्रमmat[PSC_VOLTAGE_OUT] != linear)
				वापस -ENODEV;

			data->exponent[page] = ((s8)(vout_mode << 3)) >> 3;
			अवरोध;
		हाल 1: /* VID mode         */
			अगर (data->info->क्रमmat[PSC_VOLTAGE_OUT] != vid)
				वापस -ENODEV;
			अवरोध;
		हाल 2:	/* direct mode      */
			अगर (data->info->क्रमmat[PSC_VOLTAGE_OUT] != direct)
				वापस -ENODEV;
			अवरोध;
		शेष:
			वापस -ENODEV;
		पूर्ण
	पूर्ण

	pmbus_clear_fault_page(client, page);
	वापस 0;
पूर्ण

अटल पूर्णांक pmbus_पढ़ो_status_byte(काष्ठा i2c_client *client, पूर्णांक page)
अणु
	वापस _pmbus_पढ़ो_byte_data(client, page, PMBUS_STATUS_BYTE);
पूर्ण

अटल पूर्णांक pmbus_पढ़ो_status_word(काष्ठा i2c_client *client, पूर्णांक page)
अणु
	वापस _pmbus_पढ़ो_word_data(client, page, 0xff, PMBUS_STATUS_WORD);
पूर्ण

अटल पूर्णांक pmbus_init_common(काष्ठा i2c_client *client, काष्ठा pmbus_data *data,
			     काष्ठा pmbus_driver_info *info)
अणु
	काष्ठा device *dev = &client->dev;
	पूर्णांक page, ret;

	/*
	 * Some PMBus chips करोn't support PMBUS_STATUS_WORD, so try
	 * to use PMBUS_STATUS_BYTE instead अगर that is the हाल.
	 * Bail out अगर both रेजिस्टरs are not supported.
	 */
	data->पढ़ो_status = pmbus_पढ़ो_status_word;
	ret = i2c_smbus_पढ़ो_word_data(client, PMBUS_STATUS_WORD);
	अगर (ret < 0 || ret == 0xffff) अणु
		data->पढ़ो_status = pmbus_पढ़ो_status_byte;
		ret = i2c_smbus_पढ़ो_byte_data(client, PMBUS_STATUS_BYTE);
		अगर (ret < 0 || ret == 0xff) अणु
			dev_err(dev, "PMBus status register not found\n");
			वापस -ENODEV;
		पूर्ण
	पूर्ण अन्यथा अणु
		data->has_status_word = true;
	पूर्ण

	/* Enable PEC अगर the controller supports it */
	अगर (!(data->flags & PMBUS_NO_CAPABILITY)) अणु
		ret = i2c_smbus_पढ़ो_byte_data(client, PMBUS_CAPABILITY);
		अगर (ret >= 0 && (ret & PB_CAPABILITY_ERROR_CHECK))
			client->flags |= I2C_CLIENT_PEC;
	पूर्ण

	/*
	 * Check अगर the chip is ग_लिखो रक्षित. If it is, we can not clear
	 * faults, and we should not try it. Also, in that हाल, ग_लिखोs पूर्णांकo
	 * limit रेजिस्टरs need to be disabled.
	 */
	ret = i2c_smbus_पढ़ो_byte_data(client, PMBUS_WRITE_PROTECT);
	अगर (ret > 0 && (ret & PB_WP_ANY))
		data->flags |= PMBUS_WRITE_PROTECTED | PMBUS_SKIP_STATUS_CHECK;

	अगर (data->info->pages)
		pmbus_clear_faults(client);
	अन्यथा
		pmbus_clear_fault_page(client, -1);

	अगर (info->identअगरy) अणु
		ret = (*info->identअगरy)(client, info);
		अगर (ret < 0) अणु
			dev_err(dev, "Chip identification failed\n");
			वापस ret;
		पूर्ण
	पूर्ण

	अगर (info->pages <= 0 || info->pages > PMBUS_PAGES) अणु
		dev_err(dev, "Bad number of PMBus pages: %d\n", info->pages);
		वापस -ENODEV;
	पूर्ण

	क्रम (page = 0; page < info->pages; page++) अणु
		ret = pmbus_identअगरy_common(client, data, page);
		अगर (ret < 0) अणु
			dev_err(dev, "Failed to identify chip capabilities\n");
			वापस ret;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

#अगर IS_ENABLED(CONFIG_REGULATOR)
अटल पूर्णांक pmbus_regulator_is_enabled(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा device *dev = rdev_get_dev(rdev);
	काष्ठा i2c_client *client = to_i2c_client(dev->parent);
	u8 page = rdev_get_id(rdev);
	पूर्णांक ret;

	ret = pmbus_पढ़ो_byte_data(client, page, PMBUS_OPERATION);
	अगर (ret < 0)
		वापस ret;

	वापस !!(ret & PB_OPERATION_CONTROL_ON);
पूर्ण

अटल पूर्णांक _pmbus_regulator_on_off(काष्ठा regulator_dev *rdev, bool enable)
अणु
	काष्ठा device *dev = rdev_get_dev(rdev);
	काष्ठा i2c_client *client = to_i2c_client(dev->parent);
	u8 page = rdev_get_id(rdev);

	वापस pmbus_update_byte_data(client, page, PMBUS_OPERATION,
				      PB_OPERATION_CONTROL_ON,
				      enable ? PB_OPERATION_CONTROL_ON : 0);
पूर्ण

अटल पूर्णांक pmbus_regulator_enable(काष्ठा regulator_dev *rdev)
अणु
	वापस _pmbus_regulator_on_off(rdev, 1);
पूर्ण

अटल पूर्णांक pmbus_regulator_disable(काष्ठा regulator_dev *rdev)
अणु
	वापस _pmbus_regulator_on_off(rdev, 0);
पूर्ण

स्थिर काष्ठा regulator_ops pmbus_regulator_ops = अणु
	.enable = pmbus_regulator_enable,
	.disable = pmbus_regulator_disable,
	.is_enabled = pmbus_regulator_is_enabled,
पूर्ण;
EXPORT_SYMBOL_NS_GPL(pmbus_regulator_ops, PMBUS);

अटल पूर्णांक pmbus_regulator_रेजिस्टर(काष्ठा pmbus_data *data)
अणु
	काष्ठा device *dev = data->dev;
	स्थिर काष्ठा pmbus_driver_info *info = data->info;
	स्थिर काष्ठा pmbus_platक्रमm_data *pdata = dev_get_platdata(dev);
	काष्ठा regulator_dev *rdev;
	पूर्णांक i;

	क्रम (i = 0; i < info->num_regulators; i++) अणु
		काष्ठा regulator_config config = अणु पूर्ण;

		config.dev = dev;
		config.driver_data = data;

		अगर (pdata && pdata->reg_init_data)
			config.init_data = &pdata->reg_init_data[i];

		rdev = devm_regulator_रेजिस्टर(dev, &info->reg_desc[i],
					       &config);
		अगर (IS_ERR(rdev)) अणु
			dev_err(dev, "Failed to register %s regulator\n",
				info->reg_desc[i].name);
			वापस PTR_ERR(rdev);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण
#अन्यथा
अटल पूर्णांक pmbus_regulator_रेजिस्टर(काष्ठा pmbus_data *data)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल काष्ठा dentry *pmbus_debugfs_dir;	/* pmbus debugfs directory */

#अगर IS_ENABLED(CONFIG_DEBUG_FS)
अटल पूर्णांक pmbus_debugfs_get(व्योम *data, u64 *val)
अणु
	पूर्णांक rc;
	काष्ठा pmbus_debugfs_entry *entry = data;

	rc = _pmbus_पढ़ो_byte_data(entry->client, entry->page, entry->reg);
	अगर (rc < 0)
		वापस rc;

	*val = rc;

	वापस 0;
पूर्ण
DEFINE_DEBUGFS_ATTRIBUTE(pmbus_debugfs_ops, pmbus_debugfs_get, शून्य,
			 "0x%02llx\n");

अटल पूर्णांक pmbus_debugfs_get_status(व्योम *data, u64 *val)
अणु
	पूर्णांक rc;
	काष्ठा pmbus_debugfs_entry *entry = data;
	काष्ठा pmbus_data *pdata = i2c_get_clientdata(entry->client);

	rc = pdata->पढ़ो_status(entry->client, entry->page);
	अगर (rc < 0)
		वापस rc;

	*val = rc;

	वापस 0;
पूर्ण
DEFINE_DEBUGFS_ATTRIBUTE(pmbus_debugfs_ops_status, pmbus_debugfs_get_status,
			 शून्य, "0x%04llx\n");

अटल पूर्णांक pmbus_debugfs_get_pec(व्योम *data, u64 *val)
अणु
	काष्ठा i2c_client *client = data;

	*val = !!(client->flags & I2C_CLIENT_PEC);

	वापस 0;
पूर्ण

अटल पूर्णांक pmbus_debugfs_set_pec(व्योम *data, u64 val)
अणु
	पूर्णांक rc;
	काष्ठा i2c_client *client = data;

	अगर (!val) अणु
		client->flags &= ~I2C_CLIENT_PEC;
		वापस 0;
	पूर्ण

	अगर (val != 1)
		वापस -EINVAL;

	rc = i2c_smbus_पढ़ो_byte_data(client, PMBUS_CAPABILITY);
	अगर (rc < 0)
		वापस rc;

	अगर (!(rc & PB_CAPABILITY_ERROR_CHECK))
		वापस -EOPNOTSUPP;

	client->flags |= I2C_CLIENT_PEC;

	वापस 0;
पूर्ण
DEFINE_DEBUGFS_ATTRIBUTE(pmbus_debugfs_ops_pec, pmbus_debugfs_get_pec,
			 pmbus_debugfs_set_pec, "%llu\n");

अटल व्योम pmbus_हटाओ_debugfs(व्योम *data)
अणु
	काष्ठा dentry *entry = data;

	debugfs_हटाओ_recursive(entry);
पूर्ण

अटल पूर्णांक pmbus_init_debugfs(काष्ठा i2c_client *client,
			      काष्ठा pmbus_data *data)
अणु
	पूर्णांक i, idx = 0;
	अक्षर name[PMBUS_NAME_SIZE];
	काष्ठा pmbus_debugfs_entry *entries;

	अगर (!pmbus_debugfs_dir)
		वापस -ENODEV;

	/*
	 * Create the debugfs directory क्रम this device. Use the hwmon device
	 * name to aव्योम conflicts (hwmon numbers are globally unique).
	 */
	data->debugfs = debugfs_create_dir(dev_name(data->hwmon_dev),
					   pmbus_debugfs_dir);
	अगर (IS_ERR_OR_शून्य(data->debugfs)) अणु
		data->debugfs = शून्य;
		वापस -ENODEV;
	पूर्ण

	/* Allocate the max possible entries we need. */
	entries = devm_kसुस्मृति(data->dev,
			       data->info->pages * 10, माप(*entries),
			       GFP_KERNEL);
	अगर (!entries)
		वापस -ENOMEM;

	debugfs_create_file("pec", 0664, data->debugfs, client,
			    &pmbus_debugfs_ops_pec);

	क्रम (i = 0; i < data->info->pages; ++i) अणु
		/* Check accessibility of status रेजिस्टर अगर it's not page 0 */
		अगर (!i || pmbus_check_status_रेजिस्टर(client, i)) अणु
			/* No need to set reg as we have special पढ़ो op. */
			entries[idx].client = client;
			entries[idx].page = i;
			scnम_लिखो(name, PMBUS_NAME_SIZE, "status%d", i);
			debugfs_create_file(name, 0444, data->debugfs,
					    &entries[idx++],
					    &pmbus_debugfs_ops_status);
		पूर्ण

		अगर (data->info->func[i] & PMBUS_HAVE_STATUS_VOUT) अणु
			entries[idx].client = client;
			entries[idx].page = i;
			entries[idx].reg = PMBUS_STATUS_VOUT;
			scnम_लिखो(name, PMBUS_NAME_SIZE, "status%d_vout", i);
			debugfs_create_file(name, 0444, data->debugfs,
					    &entries[idx++],
					    &pmbus_debugfs_ops);
		पूर्ण

		अगर (data->info->func[i] & PMBUS_HAVE_STATUS_IOUT) अणु
			entries[idx].client = client;
			entries[idx].page = i;
			entries[idx].reg = PMBUS_STATUS_IOUT;
			scnम_लिखो(name, PMBUS_NAME_SIZE, "status%d_iout", i);
			debugfs_create_file(name, 0444, data->debugfs,
					    &entries[idx++],
					    &pmbus_debugfs_ops);
		पूर्ण

		अगर (data->info->func[i] & PMBUS_HAVE_STATUS_INPUT) अणु
			entries[idx].client = client;
			entries[idx].page = i;
			entries[idx].reg = PMBUS_STATUS_INPUT;
			scnम_लिखो(name, PMBUS_NAME_SIZE, "status%d_input", i);
			debugfs_create_file(name, 0444, data->debugfs,
					    &entries[idx++],
					    &pmbus_debugfs_ops);
		पूर्ण

		अगर (data->info->func[i] & PMBUS_HAVE_STATUS_TEMP) अणु
			entries[idx].client = client;
			entries[idx].page = i;
			entries[idx].reg = PMBUS_STATUS_TEMPERATURE;
			scnम_लिखो(name, PMBUS_NAME_SIZE, "status%d_temp", i);
			debugfs_create_file(name, 0444, data->debugfs,
					    &entries[idx++],
					    &pmbus_debugfs_ops);
		पूर्ण

		अगर (pmbus_check_byte_रेजिस्टर(client, i, PMBUS_STATUS_CML)) अणु
			entries[idx].client = client;
			entries[idx].page = i;
			entries[idx].reg = PMBUS_STATUS_CML;
			scnम_लिखो(name, PMBUS_NAME_SIZE, "status%d_cml", i);
			debugfs_create_file(name, 0444, data->debugfs,
					    &entries[idx++],
					    &pmbus_debugfs_ops);
		पूर्ण

		अगर (pmbus_check_byte_रेजिस्टर(client, i, PMBUS_STATUS_OTHER)) अणु
			entries[idx].client = client;
			entries[idx].page = i;
			entries[idx].reg = PMBUS_STATUS_OTHER;
			scnम_लिखो(name, PMBUS_NAME_SIZE, "status%d_other", i);
			debugfs_create_file(name, 0444, data->debugfs,
					    &entries[idx++],
					    &pmbus_debugfs_ops);
		पूर्ण

		अगर (pmbus_check_byte_रेजिस्टर(client, i,
					      PMBUS_STATUS_MFR_SPECIFIC)) अणु
			entries[idx].client = client;
			entries[idx].page = i;
			entries[idx].reg = PMBUS_STATUS_MFR_SPECIFIC;
			scnम_लिखो(name, PMBUS_NAME_SIZE, "status%d_mfr", i);
			debugfs_create_file(name, 0444, data->debugfs,
					    &entries[idx++],
					    &pmbus_debugfs_ops);
		पूर्ण

		अगर (data->info->func[i] & PMBUS_HAVE_STATUS_FAN12) अणु
			entries[idx].client = client;
			entries[idx].page = i;
			entries[idx].reg = PMBUS_STATUS_FAN_12;
			scnम_लिखो(name, PMBUS_NAME_SIZE, "status%d_fan12", i);
			debugfs_create_file(name, 0444, data->debugfs,
					    &entries[idx++],
					    &pmbus_debugfs_ops);
		पूर्ण

		अगर (data->info->func[i] & PMBUS_HAVE_STATUS_FAN34) अणु
			entries[idx].client = client;
			entries[idx].page = i;
			entries[idx].reg = PMBUS_STATUS_FAN_34;
			scnम_लिखो(name, PMBUS_NAME_SIZE, "status%d_fan34", i);
			debugfs_create_file(name, 0444, data->debugfs,
					    &entries[idx++],
					    &pmbus_debugfs_ops);
		पूर्ण
	पूर्ण

	वापस devm_add_action_or_reset(data->dev,
					pmbus_हटाओ_debugfs, data->debugfs);
पूर्ण
#अन्यथा
अटल पूर्णांक pmbus_init_debugfs(काष्ठा i2c_client *client,
			      काष्ठा pmbus_data *data)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर	/* IS_ENABLED(CONFIG_DEBUG_FS) */

पूर्णांक pmbus_करो_probe(काष्ठा i2c_client *client, काष्ठा pmbus_driver_info *info)
अणु
	काष्ठा device *dev = &client->dev;
	स्थिर काष्ठा pmbus_platक्रमm_data *pdata = dev_get_platdata(dev);
	काष्ठा pmbus_data *data;
	माप_प्रकार groups_num = 0;
	पूर्णांक ret;
	अक्षर *name;

	अगर (!info)
		वापस -ENODEV;

	अगर (!i2c_check_functionality(client->adapter, I2C_FUNC_SMBUS_WRITE_BYTE
				     | I2C_FUNC_SMBUS_BYTE_DATA
				     | I2C_FUNC_SMBUS_WORD_DATA))
		वापस -ENODEV;

	data = devm_kzalloc(dev, माप(*data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	अगर (info->groups)
		जबतक (info->groups[groups_num])
			groups_num++;

	data->groups = devm_kसुस्मृति(dev, groups_num + 2, माप(व्योम *),
				    GFP_KERNEL);
	अगर (!data->groups)
		वापस -ENOMEM;

	i2c_set_clientdata(client, data);
	mutex_init(&data->update_lock);
	data->dev = dev;

	अगर (pdata)
		data->flags = pdata->flags;
	data->info = info;
	data->currpage = -1;
	data->currphase = -1;

	ret = pmbus_init_common(client, data, info);
	अगर (ret < 0)
		वापस ret;

	ret = pmbus_find_attributes(client, data);
	अगर (ret)
		वापस ret;

	/*
	 * If there are no attributes, something is wrong.
	 * Bail out instead of trying to रेजिस्टर nothing.
	 */
	अगर (!data->num_attributes) अणु
		dev_err(dev, "No attributes found\n");
		वापस -ENODEV;
	पूर्ण

	name = devm_kstrdup(dev, client->name, GFP_KERNEL);
	अगर (!name)
		वापस -ENOMEM;
	strreplace(name, '-', '_');

	data->groups[0] = &data->group;
	स_नकल(data->groups + 1, info->groups, माप(व्योम *) * groups_num);
	data->hwmon_dev = devm_hwmon_device_रेजिस्टर_with_groups(dev,
					name, data, data->groups);
	अगर (IS_ERR(data->hwmon_dev)) अणु
		dev_err(dev, "Failed to register hwmon device\n");
		वापस PTR_ERR(data->hwmon_dev);
	पूर्ण

	ret = pmbus_regulator_रेजिस्टर(data);
	अगर (ret)
		वापस ret;

	ret = pmbus_init_debugfs(client, data);
	अगर (ret)
		dev_warn(dev, "Failed to register debugfs\n");

	वापस 0;
पूर्ण
EXPORT_SYMBOL_NS_GPL(pmbus_करो_probe, PMBUS);

काष्ठा dentry *pmbus_get_debugfs_dir(काष्ठा i2c_client *client)
अणु
	काष्ठा pmbus_data *data = i2c_get_clientdata(client);

	वापस data->debugfs;
पूर्ण
EXPORT_SYMBOL_NS_GPL(pmbus_get_debugfs_dir, PMBUS);

अटल पूर्णांक __init pmbus_core_init(व्योम)
अणु
	pmbus_debugfs_dir = debugfs_create_dir("pmbus", शून्य);
	अगर (IS_ERR(pmbus_debugfs_dir))
		pmbus_debugfs_dir = शून्य;

	वापस 0;
पूर्ण

अटल व्योम __निकास pmbus_core_निकास(व्योम)
अणु
	debugfs_हटाओ_recursive(pmbus_debugfs_dir);
पूर्ण

module_init(pmbus_core_init);
module_निकास(pmbus_core_निकास);

MODULE_AUTHOR("Guenter Roeck");
MODULE_DESCRIPTION("PMBus core driver");
MODULE_LICENSE("GPL");
