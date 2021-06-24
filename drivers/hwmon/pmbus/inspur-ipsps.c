<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright 2019 Inspur Corp.
 */

#समावेश <linux/debugfs.h>
#समावेश <linux/device.h>
#समावेश <linux/fs.h>
#समावेश <linux/i2c.h>
#समावेश <linux/module.h>
#समावेश <linux/pmbus.h>
#समावेश <linux/hwmon-sysfs.h>

#समावेश "pmbus.h"

#घोषणा IPSPS_REG_VENDOR_ID	0x99
#घोषणा IPSPS_REG_MODEL		0x9A
#घोषणा IPSPS_REG_FW_VERSION	0x9B
#घोषणा IPSPS_REG_PN		0x9C
#घोषणा IPSPS_REG_SN		0x9E
#घोषणा IPSPS_REG_HW_VERSION	0xB0
#घोषणा IPSPS_REG_MODE		0xFC

#घोषणा MODE_ACTIVE		0x55
#घोषणा MODE_STANDBY		0x0E
#घोषणा MODE_REDUNDANCY		0x00

#घोषणा MODE_ACTIVE_STRING		"active"
#घोषणा MODE_STANDBY_STRING		"standby"
#घोषणा MODE_REDUNDANCY_STRING		"redundancy"

क्रमागत ipsps_index अणु
	venकरोr,
	model,
	fw_version,
	part_number,
	serial_number,
	hw_version,
	mode,
	num_regs,
पूर्ण;

अटल स्थिर u8 ipsps_regs[num_regs] = अणु
	[venकरोr] = IPSPS_REG_VENDOR_ID,
	[model] = IPSPS_REG_MODEL,
	[fw_version] = IPSPS_REG_FW_VERSION,
	[part_number] = IPSPS_REG_PN,
	[serial_number] = IPSPS_REG_SN,
	[hw_version] = IPSPS_REG_HW_VERSION,
	[mode] = IPSPS_REG_MODE,
पूर्ण;

अटल sमाप_प्रकार ipsps_string_show(काष्ठा device *dev,
				 काष्ठा device_attribute *devattr,
				 अक्षर *buf)
अणु
	u8 reg;
	पूर्णांक rc;
	अक्षर *p;
	अक्षर data[I2C_SMBUS_BLOCK_MAX + 1];
	काष्ठा i2c_client *client = to_i2c_client(dev->parent);
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(devattr);

	reg = ipsps_regs[attr->index];
	rc = i2c_smbus_पढ़ो_block_data(client, reg, data);
	अगर (rc < 0)
		वापस rc;

	/* filled with prपूर्णांकable अक्षरacters, ending with # */
	p = memscan(data, '#', rc);
	*p = '\0';

	वापस sysfs_emit(buf, "%s\n", data);
पूर्ण

अटल sमाप_प्रकार ipsps_fw_version_show(काष्ठा device *dev,
				     काष्ठा device_attribute *devattr,
				     अक्षर *buf)
अणु
	u8 reg;
	पूर्णांक rc;
	u8 data[I2C_SMBUS_BLOCK_MAX] = अणु 0 पूर्ण;
	काष्ठा i2c_client *client = to_i2c_client(dev->parent);
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(devattr);

	reg = ipsps_regs[attr->index];
	rc = i2c_smbus_पढ़ो_block_data(client, reg, data);
	अगर (rc < 0)
		वापस rc;

	अगर (rc != 6)
		वापस -EPROTO;

	वापस sysfs_emit(buf, "%u.%02u%u-%u.%02u\n",
			  data[1], data[2]/* < 100 */, data[3]/*< 10*/,
			  data[4], data[5]/* < 100 */);
पूर्ण

अटल sमाप_प्रकार ipsps_mode_show(काष्ठा device *dev,
			       काष्ठा device_attribute *devattr, अक्षर *buf)
अणु
	u8 reg;
	पूर्णांक rc;
	काष्ठा i2c_client *client = to_i2c_client(dev->parent);
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(devattr);

	reg = ipsps_regs[attr->index];
	rc = i2c_smbus_पढ़ो_byte_data(client, reg);
	अगर (rc < 0)
		वापस rc;

	चयन (rc) अणु
	हाल MODE_ACTIVE:
		वापस sysfs_emit(buf, "[%s] %s %s\n",
				  MODE_ACTIVE_STRING,
				  MODE_STANDBY_STRING, MODE_REDUNDANCY_STRING);
	हाल MODE_STANDBY:
		वापस sysfs_emit(buf, "%s [%s] %s\n",
				  MODE_ACTIVE_STRING,
				  MODE_STANDBY_STRING, MODE_REDUNDANCY_STRING);
	हाल MODE_REDUNDANCY:
		वापस sysfs_emit(buf, "%s %s [%s]\n",
				  MODE_ACTIVE_STRING,
				  MODE_STANDBY_STRING, MODE_REDUNDANCY_STRING);
	शेष:
		वापस sysfs_emit(buf, "unspecified\n");
	पूर्ण
पूर्ण

अटल sमाप_प्रकार ipsps_mode_store(काष्ठा device *dev,
				काष्ठा device_attribute *devattr,
				स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	u8 reg;
	पूर्णांक rc;
	काष्ठा i2c_client *client = to_i2c_client(dev->parent);
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(devattr);

	reg = ipsps_regs[attr->index];
	अगर (sysfs_streq(MODE_STANDBY_STRING, buf)) अणु
		rc = i2c_smbus_ग_लिखो_byte_data(client, reg,
					       MODE_STANDBY);
		अगर (rc < 0)
			वापस rc;
		वापस count;
	पूर्ण अन्यथा अगर (sysfs_streq(MODE_ACTIVE_STRING, buf)) अणु
		rc = i2c_smbus_ग_लिखो_byte_data(client, reg,
					       MODE_ACTIVE);
		अगर (rc < 0)
			वापस rc;
		वापस count;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल SENSOR_DEVICE_ATTR_RO(venकरोr, ipsps_string, venकरोr);
अटल SENSOR_DEVICE_ATTR_RO(model, ipsps_string, model);
अटल SENSOR_DEVICE_ATTR_RO(part_number, ipsps_string, part_number);
अटल SENSOR_DEVICE_ATTR_RO(serial_number, ipsps_string, serial_number);
अटल SENSOR_DEVICE_ATTR_RO(hw_version, ipsps_string, hw_version);
अटल SENSOR_DEVICE_ATTR_RO(fw_version, ipsps_fw_version, fw_version);
अटल SENSOR_DEVICE_ATTR_RW(mode, ipsps_mode, mode);

अटल काष्ठा attribute *ipsps_attrs[] = अणु
	&sensor_dev_attr_venकरोr.dev_attr.attr,
	&sensor_dev_attr_model.dev_attr.attr,
	&sensor_dev_attr_part_number.dev_attr.attr,
	&sensor_dev_attr_serial_number.dev_attr.attr,
	&sensor_dev_attr_hw_version.dev_attr.attr,
	&sensor_dev_attr_fw_version.dev_attr.attr,
	&sensor_dev_attr_mode.dev_attr.attr,
	शून्य,
पूर्ण;

ATTRIBUTE_GROUPS(ipsps);

अटल काष्ठा pmbus_driver_info ipsps_info = अणु
	.pages = 1,
	.func[0] = PMBUS_HAVE_VIN | PMBUS_HAVE_VOUT | PMBUS_HAVE_IOUT |
		PMBUS_HAVE_IIN | PMBUS_HAVE_POUT | PMBUS_HAVE_PIN |
		PMBUS_HAVE_FAN12 | PMBUS_HAVE_TEMP | PMBUS_HAVE_TEMP2 |
		PMBUS_HAVE_TEMP3 | PMBUS_HAVE_STATUS_VOUT |
		PMBUS_HAVE_STATUS_IOUT | PMBUS_HAVE_STATUS_INPUT |
		PMBUS_HAVE_STATUS_TEMP | PMBUS_HAVE_STATUS_FAN12,
	.groups = ipsps_groups,
पूर्ण;

अटल काष्ठा pmbus_platक्रमm_data ipsps_pdata = अणु
	.flags = PMBUS_SKIP_STATUS_CHECK,
पूर्ण;

अटल पूर्णांक ipsps_probe(काष्ठा i2c_client *client)
अणु
	client->dev.platक्रमm_data = &ipsps_pdata;
	वापस pmbus_करो_probe(client, &ipsps_info);
पूर्ण

अटल स्थिर काष्ठा i2c_device_id ipsps_id[] = अणु
	अणु "ipsps1", 0 पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, ipsps_id);

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id ipsps_of_match[] = अणु
	अणु .compatible = "inspur,ipsps1" पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, ipsps_of_match);
#पूर्ण_अगर

अटल काष्ठा i2c_driver ipsps_driver = अणु
	.driver = अणु
		.name = "inspur-ipsps",
		.of_match_table = of_match_ptr(ipsps_of_match),
	पूर्ण,
	.probe_new = ipsps_probe,
	.id_table = ipsps_id,
पूर्ण;

module_i2c_driver(ipsps_driver);

MODULE_AUTHOR("John Wang");
MODULE_DESCRIPTION("PMBus driver for Inspur Power System power supplies");
MODULE_LICENSE("GPL");
MODULE_IMPORT_NS(PMBUS);
