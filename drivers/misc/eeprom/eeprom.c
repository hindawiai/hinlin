<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 1998, 1999  Froकरो Looijaard <froकरोl@dds.nl> and
 *                           Philip Edelbrock <phil@netroedge.com>
 * Copyright (C) 2003 Greg Kroah-Harपंचांगan <greg@kroah.com>
 * Copyright (C) 2003 IBM Corp.
 * Copyright (C) 2004 Jean Delvare <jdelvare@suse.de>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/device.h>
#समावेश <linux/capability.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/i2c.h>
#समावेश <linux/mutex.h>

/* Addresses to scan */
अटल स्थिर अचिन्हित लघु normal_i2c[] = अणु 0x50, 0x51, 0x52, 0x53, 0x54,
					0x55, 0x56, 0x57, I2C_CLIENT_END पूर्ण;


/* Size of EEPROM in bytes */
#घोषणा EEPROM_SIZE		256

/* possible types of eeprom devices */
क्रमागत eeprom_nature अणु
	UNKNOWN,
	VAIO,
पूर्ण;

/* Each client has this additional data */
काष्ठा eeprom_data अणु
	काष्ठा mutex update_lock;
	u8 valid;			/* bitfield, bit!=0 अगर slice is valid */
	अचिन्हित दीर्घ last_updated[8];	/* In jअगरfies, 8 slices */
	u8 data[EEPROM_SIZE];		/* Register values */
	क्रमागत eeprom_nature nature;
पूर्ण;


अटल व्योम eeprom_update_client(काष्ठा i2c_client *client, u8 slice)
अणु
	काष्ठा eeprom_data *data = i2c_get_clientdata(client);
	पूर्णांक i;

	mutex_lock(&data->update_lock);

	अगर (!(data->valid & (1 << slice)) ||
	    समय_after(jअगरfies, data->last_updated[slice] + 300 * HZ)) अणु
		dev_dbg(&client->dev, "Starting eeprom update, slice %u\n", slice);

		अगर (i2c_check_functionality(client->adapter, I2C_FUNC_SMBUS_READ_I2C_BLOCK)) अणु
			क्रम (i = slice << 5; i < (slice + 1) << 5; i += 32)
				अगर (i2c_smbus_पढ़ो_i2c_block_data(client, i,
							32, data->data + i)
							!= 32)
					जाओ निकास;
		पूर्ण अन्यथा अणु
			क्रम (i = slice << 5; i < (slice + 1) << 5; i += 2) अणु
				पूर्णांक word = i2c_smbus_पढ़ो_word_data(client, i);
				अगर (word < 0)
					जाओ निकास;
				data->data[i] = word & 0xff;
				data->data[i + 1] = word >> 8;
			पूर्ण
		पूर्ण
		data->last_updated[slice] = jअगरfies;
		data->valid |= (1 << slice);
	पूर्ण
निकास:
	mutex_unlock(&data->update_lock);
पूर्ण

अटल sमाप_प्रकार eeprom_पढ़ो(काष्ठा file *filp, काष्ठा kobject *kobj,
			   काष्ठा bin_attribute *bin_attr,
			   अक्षर *buf, loff_t off, माप_प्रकार count)
अणु
	काष्ठा i2c_client *client = kobj_to_i2c_client(kobj);
	काष्ठा eeprom_data *data = i2c_get_clientdata(client);
	u8 slice;

	/* Only refresh slices which contain requested bytes */
	क्रम (slice = off >> 5; slice <= (off + count - 1) >> 5; slice++)
		eeprom_update_client(client, slice);

	/* Hide Vaio निजी settings to regular users:
	   - BIOS passwords: bytes 0x00 to 0x0f
	   - UUID: bytes 0x10 to 0x1f
	   - Serial number: 0xc0 to 0xdf */
	अगर (data->nature == VAIO && !capable(CAP_SYS_ADMIN)) अणु
		पूर्णांक i;

		क्रम (i = 0; i < count; i++) अणु
			अगर ((off + i <= 0x1f) ||
			    (off + i >= 0xc0 && off + i <= 0xdf))
				buf[i] = 0;
			अन्यथा
				buf[i] = data->data[off + i];
		पूर्ण
	पूर्ण अन्यथा अणु
		स_नकल(buf, &data->data[off], count);
	पूर्ण

	वापस count;
पूर्ण

अटल स्थिर काष्ठा bin_attribute eeprom_attr = अणु
	.attr = अणु
		.name = "eeprom",
		.mode = S_IRUGO,
	पूर्ण,
	.size = EEPROM_SIZE,
	.पढ़ो = eeprom_पढ़ो,
पूर्ण;

/* Return 0 अगर detection is successful, -ENODEV otherwise */
अटल पूर्णांक eeprom_detect(काष्ठा i2c_client *client, काष्ठा i2c_board_info *info)
अणु
	काष्ठा i2c_adapter *adapter = client->adapter;

	/* EDID EEPROMs are often 24C00 EEPROMs, which answer to all
	   addresses 0x50-0x57, but we only care about 0x50. So decline
	   attaching to addresses >= 0x51 on DDC buses */
	अगर (!(adapter->class & I2C_CLASS_SPD) && client->addr >= 0x51)
		वापस -ENODEV;

	/* There are four ways we can पढ़ो the EEPROM data:
	   (1) I2C block पढ़ोs (faster, but unsupported by most adapters)
	   (2) Word पढ़ोs (128% overhead)
	   (3) Consecutive byte पढ़ोs (88% overhead, unsafe)
	   (4) Regular byte data पढ़ोs (265% overhead)
	   The third and fourth methods are not implemented by this driver
	   because all known adapters support one of the first two. */
	अगर (!i2c_check_functionality(adapter, I2C_FUNC_SMBUS_READ_WORD_DATA)
	 && !i2c_check_functionality(adapter, I2C_FUNC_SMBUS_READ_I2C_BLOCK))
		वापस -ENODEV;

	strlcpy(info->type, "eeprom", I2C_NAME_SIZE);

	वापस 0;
पूर्ण

अटल पूर्णांक eeprom_probe(काष्ठा i2c_client *client,
			स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा i2c_adapter *adapter = client->adapter;
	काष्ठा eeprom_data *data;

	data = devm_kzalloc(&client->dev, माप(काष्ठा eeprom_data),
			    GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	स_रखो(data->data, 0xff, EEPROM_SIZE);
	i2c_set_clientdata(client, data);
	mutex_init(&data->update_lock);
	data->nature = UNKNOWN;

	/* Detect the Vaio nature of EEPROMs.
	   We use the "PCG-" or "VGN-" prefix as the signature. */
	अगर (client->addr == 0x57
	 && i2c_check_functionality(adapter, I2C_FUNC_SMBUS_READ_BYTE_DATA)) अणु
		अक्षर name[4];

		name[0] = i2c_smbus_पढ़ो_byte_data(client, 0x80);
		name[1] = i2c_smbus_पढ़ो_byte_data(client, 0x81);
		name[2] = i2c_smbus_पढ़ो_byte_data(client, 0x82);
		name[3] = i2c_smbus_पढ़ो_byte_data(client, 0x83);

		अगर (!स_भेद(name, "PCG-", 4) || !स_भेद(name, "VGN-", 4)) अणु
			dev_info(&client->dev, "Vaio EEPROM detected, "
				 "enabling privacy protection\n");
			data->nature = VAIO;
		पूर्ण
	पूर्ण

	/* Let the users know they are using deprecated driver */
	dev_notice(&client->dev,
		   "eeprom driver is deprecated, please use at24 instead\n");

	/* create the sysfs eeprom file */
	वापस sysfs_create_bin_file(&client->dev.kobj, &eeprom_attr);
पूर्ण

अटल पूर्णांक eeprom_हटाओ(काष्ठा i2c_client *client)
अणु
	sysfs_हटाओ_bin_file(&client->dev.kobj, &eeprom_attr);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id eeprom_id[] = अणु
	अणु "eeprom", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल काष्ठा i2c_driver eeprom_driver = अणु
	.driver = अणु
		.name	= "eeprom",
	पूर्ण,
	.probe		= eeprom_probe,
	.हटाओ		= eeprom_हटाओ,
	.id_table	= eeprom_id,

	.class		= I2C_CLASS_DDC | I2C_CLASS_SPD,
	.detect		= eeprom_detect,
	.address_list	= normal_i2c,
पूर्ण;

module_i2c_driver(eeprom_driver);

MODULE_AUTHOR("Frodo Looijaard <frodol@dds.nl> and "
		"Philip Edelbrock <phil@netroedge.com> and "
		"Greg Kroah-Hartman <greg@kroah.com>");
MODULE_DESCRIPTION("I2C EEPROM driver");
MODULE_LICENSE("GPL");
