<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Dallas Semiconductor DS1682 Elapsed Time Recorder device driver
 *
 * Written by: Grant Likely <grant.likely@secretlab.ca>
 *
 * Copyright (C) 2007 Secret Lab Technologies Ltd.
 */

/*
 * The DS1682 elapsed समयr recorder is a simple device that implements
 * one elapsed समय counter, one event counter, an alarm संकेत and 10
 * bytes of general purpose EEPROM.
 *
 * This driver provides access to the DS1682 counters and user data via
 * the sysfs.  The following attributes are added to the device node:
 *     elapsed_समय (u32): Total elapsed event समय in ms resolution
 *     alarm_समय (u32): When elapsed समय exceeds the value in alarm_समय,
 *                       then the alarm pin is निश्चितed.
 *     event_count (u16): number of बार the event pin has gone low.
 *     eeprom (u8[10]): general purpose EEPROM
 *
 * Counter रेजिस्टरs and user data are both पढ़ो/ग_लिखो unless the device
 * has been ग_लिखो रक्षित.  This driver करोes not support turning off ग_लिखो
 * protection.  Once ग_लिखो protection is turned on, it is impossible to
 * turn it off again, so I have left the feature out of this driver to aव्योम
 * accidental enabling, but it is trivial to add ग_लिखो protect support.
 *
 */

#समावेश <linux/module.h>
#समावेश <linux/i2c.h>
#समावेश <linux/माला.स>
#समावेश <linux/list.h>
#समावेश <linux/sysfs.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/hwmon-sysfs.h>

/* Device रेजिस्टरs */
#घोषणा DS1682_REG_CONFIG		0x00
#घोषणा DS1682_REG_ALARM		0x01
#घोषणा DS1682_REG_ELAPSED		0x05
#घोषणा DS1682_REG_EVT_CNTR		0x09
#घोषणा DS1682_REG_EEPROM		0x0b
#घोषणा DS1682_REG_RESET		0x1d
#घोषणा DS1682_REG_WRITE_DISABLE	0x1e
#घोषणा DS1682_REG_WRITE_MEM_DISABLE	0x1f

#घोषणा DS1682_EEPROM_SIZE		10

/*
 * Generic counter attributes
 */
अटल sमाप_प्रकार ds1682_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			   अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute_2 *sattr = to_sensor_dev_attr_2(attr);
	काष्ठा i2c_client *client = to_i2c_client(dev);
	अचिन्हित दीर्घ दीर्घ val, check;
	__le32 val_le = 0;
	पूर्णांक rc;

	dev_dbg(dev, "ds1682_show() called on %s\n", attr->attr.name);

	/* Read the रेजिस्टर */
	rc = i2c_smbus_पढ़ो_i2c_block_data(client, sattr->index, sattr->nr,
					   (u8 *)&val_le);
	अगर (rc < 0)
		वापस -EIO;

	val = le32_to_cpu(val_le);

	अगर (sattr->index == DS1682_REG_ELAPSED) अणु
		पूर्णांक retries = 5;

		/* Detect and retry when a tick occurs mid-पढ़ो */
		करो अणु
			rc = i2c_smbus_पढ़ो_i2c_block_data(client, sattr->index,
							   sattr->nr,
							   (u8 *)&val_le);
			अगर (rc < 0 || retries <= 0)
				वापस -EIO;

			check = val;
			val = le32_to_cpu(val_le);
			retries--;
		पूर्ण जबतक (val != check && val != (check + 1));
	पूर्ण

	/* Format the output string and वापस # of bytes
	 * Special हाल: the 32 bit regs are समय values with 1/4s
	 * resolution, scale them up to milliseconds
	 */
	वापस प्र_लिखो(buf, "%llu\n", (sattr->nr == 4) ? (val * 250) : val);
पूर्ण

अटल sमाप_प्रकार ds1682_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
			    स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा sensor_device_attribute_2 *sattr = to_sensor_dev_attr_2(attr);
	काष्ठा i2c_client *client = to_i2c_client(dev);
	u64 val;
	__le32 val_le;
	पूर्णांक rc;

	dev_dbg(dev, "ds1682_store() called on %s\n", attr->attr.name);

	/* Decode input */
	rc = kम_से_अदीर्घl(buf, 0, &val);
	अगर (rc < 0) अणु
		dev_dbg(dev, "input string not a number\n");
		वापस -EINVAL;
	पूर्ण

	/* Special हाल: the 32 bit regs are समय values with 1/4s
	 * resolution, scale input करोwn to quarter-seconds */
	अगर (sattr->nr == 4)
		करो_भाग(val, 250);

	/* ग_लिखो out the value */
	val_le = cpu_to_le32(val);
	rc = i2c_smbus_ग_लिखो_i2c_block_data(client, sattr->index, sattr->nr,
					    (u8 *) & val_le);
	अगर (rc < 0) अणु
		dev_err(dev, "register write failed; reg=0x%x, size=%i\n",
			sattr->index, sattr->nr);
		वापस -EIO;
	पूर्ण

	वापस count;
पूर्ण

/*
 * Simple रेजिस्टर attributes
 */
अटल SENSOR_DEVICE_ATTR_2(elapsed_समय, S_IRUGO | S_IWUSR, ds1682_show,
			    ds1682_store, 4, DS1682_REG_ELAPSED);
अटल SENSOR_DEVICE_ATTR_2(alarm_समय, S_IRUGO | S_IWUSR, ds1682_show,
			    ds1682_store, 4, DS1682_REG_ALARM);
अटल SENSOR_DEVICE_ATTR_2(event_count, S_IRUGO | S_IWUSR, ds1682_show,
			    ds1682_store, 2, DS1682_REG_EVT_CNTR);

अटल स्थिर काष्ठा attribute_group ds1682_group = अणु
	.attrs = (काष्ठा attribute *[]) अणु
		&sensor_dev_attr_elapsed_समय.dev_attr.attr,
		&sensor_dev_attr_alarm_समय.dev_attr.attr,
		&sensor_dev_attr_event_count.dev_attr.attr,
		शून्य,
	पूर्ण,
पूर्ण;

/*
 * User data attribute
 */
अटल sमाप_प्रकार ds1682_eeprom_पढ़ो(काष्ठा file *filp, काष्ठा kobject *kobj,
				  काष्ठा bin_attribute *attr,
				  अक्षर *buf, loff_t off, माप_प्रकार count)
अणु
	काष्ठा i2c_client *client = kobj_to_i2c_client(kobj);
	पूर्णांक rc;

	dev_dbg(&client->dev, "ds1682_eeprom_read(p=%p, off=%lli, c=%zi)\n",
		buf, off, count);

	rc = i2c_smbus_पढ़ो_i2c_block_data(client, DS1682_REG_EEPROM + off,
					   count, buf);
	अगर (rc < 0)
		वापस -EIO;

	वापस count;
पूर्ण

अटल sमाप_प्रकार ds1682_eeprom_ग_लिखो(काष्ठा file *filp, काष्ठा kobject *kobj,
				   काष्ठा bin_attribute *attr,
				   अक्षर *buf, loff_t off, माप_प्रकार count)
अणु
	काष्ठा i2c_client *client = kobj_to_i2c_client(kobj);

	dev_dbg(&client->dev, "ds1682_eeprom_write(p=%p, off=%lli, c=%zi)\n",
		buf, off, count);

	/* Write out to the device */
	अगर (i2c_smbus_ग_लिखो_i2c_block_data(client, DS1682_REG_EEPROM + off,
					   count, buf) < 0)
		वापस -EIO;

	वापस count;
पूर्ण

अटल स्थिर काष्ठा bin_attribute ds1682_eeprom_attr = अणु
	.attr = अणु
		.name = "eeprom",
		.mode = S_IRUGO | S_IWUSR,
	पूर्ण,
	.size = DS1682_EEPROM_SIZE,
	.पढ़ो = ds1682_eeprom_पढ़ो,
	.ग_लिखो = ds1682_eeprom_ग_लिखो,
पूर्ण;

/*
 * Called when a ds1682 device is matched with this driver
 */
अटल पूर्णांक ds1682_probe(काष्ठा i2c_client *client,
			स्थिर काष्ठा i2c_device_id *id)
अणु
	पूर्णांक rc;

	अगर (!i2c_check_functionality(client->adapter,
				     I2C_FUNC_SMBUS_I2C_BLOCK)) अणु
		dev_err(&client->dev, "i2c bus does not support the ds1682\n");
		rc = -ENODEV;
		जाओ निकास;
	पूर्ण

	rc = sysfs_create_group(&client->dev.kobj, &ds1682_group);
	अगर (rc)
		जाओ निकास;

	rc = sysfs_create_bin_file(&client->dev.kobj, &ds1682_eeprom_attr);
	अगर (rc)
		जाओ निकास_bin_attr;

	वापस 0;

 निकास_bin_attr:
	sysfs_हटाओ_group(&client->dev.kobj, &ds1682_group);
 निकास:
	वापस rc;
पूर्ण

अटल पूर्णांक ds1682_हटाओ(काष्ठा i2c_client *client)
अणु
	sysfs_हटाओ_bin_file(&client->dev.kobj, &ds1682_eeprom_attr);
	sysfs_हटाओ_group(&client->dev.kobj, &ds1682_group);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id ds1682_id[] = अणु
	अणु "ds1682", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, ds1682_id);

अटल स्थिर काष्ठा of_device_id ds1682_of_match[] = अणु
	अणु .compatible = "dallas,ds1682", पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, ds1682_of_match);

अटल काष्ठा i2c_driver ds1682_driver = अणु
	.driver = अणु
		.name = "ds1682",
		.of_match_table = ds1682_of_match,
	पूर्ण,
	.probe = ds1682_probe,
	.हटाओ = ds1682_हटाओ,
	.id_table = ds1682_id,
पूर्ण;

module_i2c_driver(ds1682_driver);

MODULE_AUTHOR("Grant Likely <grant.likely@secretlab.ca>");
MODULE_DESCRIPTION("DS1682 Elapsed Time Indicator driver");
MODULE_LICENSE("GPL");
