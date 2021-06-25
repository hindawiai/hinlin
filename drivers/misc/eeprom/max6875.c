<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * max6875.c - driver क्रम MAX6874/MAX6875
 *
 * Copyright (C) 2005 Ben Gardner <bgardner@wabtec.com>
 *
 * Based on eeprom.c
 *
 * The MAX6875 has a bank of रेजिस्टरs and two banks of EEPROM.
 * Address ranges are defined as follows:
 *  * 0x0000 - 0x0046 = configuration रेजिस्टरs
 *  * 0x8000 - 0x8046 = configuration EEPROM
 *  * 0x8100 - 0x82FF = user EEPROM
 *
 * This driver makes the user EEPROM available क्रम पढ़ो.
 *
 * The रेजिस्टरs & config EEPROM should be accessed via i2c-dev.
 *
 * The MAX6875 ignores the lowest address bit, so each chip responds to
 * two addresses - 0x50/0x51 and 0x52/0x53.
 *
 * Note that the MAX6875 uses i2c_smbus_ग_लिखो_byte_data() to set the पढ़ो
 * address, so this driver is deकाष्ठाive अगर loaded क्रम the wrong EEPROM chip.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/i2c.h>
#समावेश <linux/mutex.h>

/* The MAX6875 can only पढ़ो/ग_लिखो 16 bytes at a समय */
#घोषणा SLICE_SIZE			16
#घोषणा SLICE_BITS			4

/* USER EEPROM is at addresses 0x8100 - 0x82FF */
#घोषणा USER_EEPROM_BASE		0x8100
#घोषणा USER_EEPROM_SIZE		0x0200
#घोषणा USER_EEPROM_SLICES		32

/* MAX6875 commands */
#घोषणा MAX6875_CMD_BLK_READ		0x84

/* Each client has this additional data */
काष्ठा max6875_data अणु
	काष्ठा i2c_client	*fake_client;
	काष्ठा mutex		update_lock;

	u32			valid;
	u8			data[USER_EEPROM_SIZE];
	अचिन्हित दीर्घ		last_updated[USER_EEPROM_SLICES];
पूर्ण;

अटल व्योम max6875_update_slice(काष्ठा i2c_client *client, पूर्णांक slice)
अणु
	काष्ठा max6875_data *data = i2c_get_clientdata(client);
	पूर्णांक i, j, addr;
	u8 *buf;

	अगर (slice >= USER_EEPROM_SLICES)
		वापस;

	mutex_lock(&data->update_lock);

	buf = &data->data[slice << SLICE_BITS];

	अगर (!(data->valid & (1 << slice)) ||
	    समय_after(jअगरfies, data->last_updated[slice])) अणु

		dev_dbg(&client->dev, "Starting update of slice %u\n", slice);

		data->valid &= ~(1 << slice);

		addr = USER_EEPROM_BASE + (slice << SLICE_BITS);

		/* select the eeprom address */
		अगर (i2c_smbus_ग_लिखो_byte_data(client, addr >> 8, addr & 0xFF)) अणु
			dev_err(&client->dev, "address set failed\n");
			जाओ निकास_up;
		पूर्ण

		अगर (i2c_check_functionality(client->adapter,
					    I2C_FUNC_SMBUS_READ_I2C_BLOCK)) अणु
			अगर (i2c_smbus_पढ़ो_i2c_block_data(client,
							  MAX6875_CMD_BLK_READ,
							  SLICE_SIZE,
							  buf) != SLICE_SIZE) अणु
				जाओ निकास_up;
			पूर्ण
		पूर्ण अन्यथा अणु
			क्रम (i = 0; i < SLICE_SIZE; i++) अणु
				j = i2c_smbus_पढ़ो_byte(client);
				अगर (j < 0) अणु
					जाओ निकास_up;
				पूर्ण
				buf[i] = j;
			पूर्ण
		पूर्ण
		data->last_updated[slice] = jअगरfies;
		data->valid |= (1 << slice);
	पूर्ण
निकास_up:
	mutex_unlock(&data->update_lock);
पूर्ण

अटल sमाप_प्रकार max6875_पढ़ो(काष्ठा file *filp, काष्ठा kobject *kobj,
			    काष्ठा bin_attribute *bin_attr,
			    अक्षर *buf, loff_t off, माप_प्रकार count)
अणु
	काष्ठा i2c_client *client = kobj_to_i2c_client(kobj);
	काष्ठा max6875_data *data = i2c_get_clientdata(client);
	पूर्णांक slice, max_slice;

	/* refresh slices which contain requested bytes */
	max_slice = (off + count - 1) >> SLICE_BITS;
	क्रम (slice = (off >> SLICE_BITS); slice <= max_slice; slice++)
		max6875_update_slice(client, slice);

	स_नकल(buf, &data->data[off], count);

	वापस count;
पूर्ण

अटल स्थिर काष्ठा bin_attribute user_eeprom_attr = अणु
	.attr = अणु
		.name = "eeprom",
		.mode = S_IRUGO,
	पूर्ण,
	.size = USER_EEPROM_SIZE,
	.पढ़ो = max6875_पढ़ो,
पूर्ण;

अटल पूर्णांक max6875_probe(काष्ठा i2c_client *client,
			 स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा i2c_adapter *adapter = client->adapter;
	काष्ठा max6875_data *data;
	पूर्णांक err;

	अगर (!i2c_check_functionality(adapter, I2C_FUNC_SMBUS_WRITE_BYTE_DATA
				     | I2C_FUNC_SMBUS_READ_BYTE))
		वापस -ENODEV;

	/* Only bind to even addresses */
	अगर (client->addr & 1)
		वापस -ENODEV;

	data = kzalloc(माप(काष्ठा max6875_data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	/* A fake client is created on the odd address */
	data->fake_client = i2c_new_dummy_device(client->adapter, client->addr + 1);
	अगर (IS_ERR(data->fake_client)) अणु
		err = PTR_ERR(data->fake_client);
		जाओ निकास_kमुक्त;
	पूर्ण

	/* Init real i2c_client */
	i2c_set_clientdata(client, data);
	mutex_init(&data->update_lock);

	err = sysfs_create_bin_file(&client->dev.kobj, &user_eeprom_attr);
	अगर (err)
		जाओ निकास_हटाओ_fake;

	वापस 0;

निकास_हटाओ_fake:
	i2c_unरेजिस्टर_device(data->fake_client);
निकास_kमुक्त:
	kमुक्त(data);
	वापस err;
पूर्ण

अटल पूर्णांक max6875_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा max6875_data *data = i2c_get_clientdata(client);

	i2c_unरेजिस्टर_device(data->fake_client);

	sysfs_हटाओ_bin_file(&client->dev.kobj, &user_eeprom_attr);
	kमुक्त(data);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id max6875_id[] = अणु
	अणु "max6875", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, max6875_id);

अटल काष्ठा i2c_driver max6875_driver = अणु
	.driver = अणु
		.name	= "max6875",
	पूर्ण,
	.probe		= max6875_probe,
	.हटाओ		= max6875_हटाओ,
	.id_table	= max6875_id,
पूर्ण;

module_i2c_driver(max6875_driver);

MODULE_AUTHOR("Ben Gardner <bgardner@wabtec.com>");
MODULE_DESCRIPTION("MAX6875 driver");
MODULE_LICENSE("GPL");
