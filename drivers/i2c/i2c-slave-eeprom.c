<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * I2C slave mode EEPROM simulator
 *
 * Copyright (C) 2014 by Wolfram Sang, Sang Engineering <wsa@sang-engineering.com>
 * Copyright (C) 2014 by Renesas Electronics Corporation
 *
 * Because most slave IP cores can only detect one I2C slave address anyhow,
 * this driver करोes not support simulating EEPROM types which take more than
 * one address.
 */

/*
 * FIXME: What to करो अगर only 8 bits of a 16 bit address are sent?
 * The ST-M24C64 sends only 0xff then. Needs verअगरication with other
 * EEPROMs, though. We currently use the 8 bit as a valid address.
 */

#समावेश <linux/bitfield.h>
#समावेश <linux/firmware.h>
#समावेश <linux/i2c.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/sysfs.h>

काष्ठा eeprom_data अणु
	काष्ठा bin_attribute bin;
	spinlock_t buffer_lock;
	u16 buffer_idx;
	u16 address_mask;
	u8 num_address_bytes;
	u8 idx_ग_लिखो_cnt;
	bool पढ़ो_only;
	u8 buffer[];
पूर्ण;

#घोषणा I2C_SLAVE_BYTELEN GENMASK(15, 0)
#घोषणा I2C_SLAVE_FLAG_ADDR16 BIT(16)
#घोषणा I2C_SLAVE_FLAG_RO BIT(17)
#घोषणा I2C_SLAVE_DEVICE_MAGIC(_len, _flags) ((_flags) | ((_len) - 1))

अटल पूर्णांक i2c_slave_eeprom_slave_cb(काष्ठा i2c_client *client,
				     क्रमागत i2c_slave_event event, u8 *val)
अणु
	काष्ठा eeprom_data *eeprom = i2c_get_clientdata(client);

	चयन (event) अणु
	हाल I2C_SLAVE_WRITE_RECEIVED:
		अगर (eeprom->idx_ग_लिखो_cnt < eeprom->num_address_bytes) अणु
			अगर (eeprom->idx_ग_लिखो_cnt == 0)
				eeprom->buffer_idx = 0;
			eeprom->buffer_idx = *val | (eeprom->buffer_idx << 8);
			eeprom->idx_ग_लिखो_cnt++;
		पूर्ण अन्यथा अणु
			अगर (!eeprom->पढ़ो_only) अणु
				spin_lock(&eeprom->buffer_lock);
				eeprom->buffer[eeprom->buffer_idx++ & eeprom->address_mask] = *val;
				spin_unlock(&eeprom->buffer_lock);
			पूर्ण
		पूर्ण
		अवरोध;

	हाल I2C_SLAVE_READ_PROCESSED:
		/* The previous byte made it to the bus, get next one */
		eeprom->buffer_idx++;
		fallthrough;
	हाल I2C_SLAVE_READ_REQUESTED:
		spin_lock(&eeprom->buffer_lock);
		*val = eeprom->buffer[eeprom->buffer_idx & eeprom->address_mask];
		spin_unlock(&eeprom->buffer_lock);
		/*
		 * Do not increment buffer_idx here, because we करोn't know अगर
		 * this byte will be actually used. Read Linux I2C slave करोcs
		 * क्रम details.
		 */
		अवरोध;

	हाल I2C_SLAVE_STOP:
	हाल I2C_SLAVE_WRITE_REQUESTED:
		eeprom->idx_ग_लिखो_cnt = 0;
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल sमाप_प्रकार i2c_slave_eeprom_bin_पढ़ो(काष्ठा file *filp, काष्ठा kobject *kobj,
		काष्ठा bin_attribute *attr, अक्षर *buf, loff_t off, माप_प्रकार count)
अणु
	काष्ठा eeprom_data *eeprom;
	अचिन्हित दीर्घ flags;

	eeprom = dev_get_drvdata(kobj_to_dev(kobj));

	spin_lock_irqsave(&eeprom->buffer_lock, flags);
	स_नकल(buf, &eeprom->buffer[off], count);
	spin_unlock_irqrestore(&eeprom->buffer_lock, flags);

	वापस count;
पूर्ण

अटल sमाप_प्रकार i2c_slave_eeprom_bin_ग_लिखो(काष्ठा file *filp, काष्ठा kobject *kobj,
		काष्ठा bin_attribute *attr, अक्षर *buf, loff_t off, माप_प्रकार count)
अणु
	काष्ठा eeprom_data *eeprom;
	अचिन्हित दीर्घ flags;

	eeprom = dev_get_drvdata(kobj_to_dev(kobj));

	spin_lock_irqsave(&eeprom->buffer_lock, flags);
	स_नकल(&eeprom->buffer[off], buf, count);
	spin_unlock_irqrestore(&eeprom->buffer_lock, flags);

	वापस count;
पूर्ण

अटल पूर्णांक i2c_slave_init_eeprom_data(काष्ठा eeprom_data *eeprom, काष्ठा i2c_client *client,
				      अचिन्हित पूर्णांक size)
अणु
	स्थिर काष्ठा firmware *fw;
	स्थिर अक्षर *eeprom_data;
	पूर्णांक ret = device_property_पढ़ो_string(&client->dev, "firmware-name", &eeprom_data);

	अगर (!ret) अणु
		ret = request_firmware_पूर्णांकo_buf(&fw, eeprom_data, &client->dev,
						eeprom->buffer, size);
		अगर (ret)
			वापस ret;
		release_firmware(fw);
	पूर्ण अन्यथा अणु
		/* An empty eeprom typically has all bits set to 1 */
		स_रखो(eeprom->buffer, 0xff, size);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक i2c_slave_eeprom_probe(काष्ठा i2c_client *client, स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा eeprom_data *eeprom;
	पूर्णांक ret;
	अचिन्हित पूर्णांक size = FIELD_GET(I2C_SLAVE_BYTELEN, id->driver_data) + 1;
	अचिन्हित पूर्णांक flag_addr16 = FIELD_GET(I2C_SLAVE_FLAG_ADDR16, id->driver_data);

	eeprom = devm_kzalloc(&client->dev, माप(काष्ठा eeprom_data) + size, GFP_KERNEL);
	अगर (!eeprom)
		वापस -ENOMEM;

	eeprom->num_address_bytes = flag_addr16 ? 2 : 1;
	eeprom->address_mask = size - 1;
	eeprom->पढ़ो_only = FIELD_GET(I2C_SLAVE_FLAG_RO, id->driver_data);
	spin_lock_init(&eeprom->buffer_lock);
	i2c_set_clientdata(client, eeprom);

	ret = i2c_slave_init_eeprom_data(eeprom, client, size);
	अगर (ret)
		वापस ret;

	sysfs_bin_attr_init(&eeprom->bin);
	eeprom->bin.attr.name = "slave-eeprom";
	eeprom->bin.attr.mode = S_IRUSR | S_IWUSR;
	eeprom->bin.पढ़ो = i2c_slave_eeprom_bin_पढ़ो;
	eeprom->bin.ग_लिखो = i2c_slave_eeprom_bin_ग_लिखो;
	eeprom->bin.size = size;

	ret = sysfs_create_bin_file(&client->dev.kobj, &eeprom->bin);
	अगर (ret)
		वापस ret;

	ret = i2c_slave_रेजिस्टर(client, i2c_slave_eeprom_slave_cb);
	अगर (ret) अणु
		sysfs_हटाओ_bin_file(&client->dev.kobj, &eeprom->bin);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण;

अटल पूर्णांक i2c_slave_eeprom_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा eeprom_data *eeprom = i2c_get_clientdata(client);

	i2c_slave_unरेजिस्टर(client);
	sysfs_हटाओ_bin_file(&client->dev.kobj, &eeprom->bin);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id i2c_slave_eeprom_id[] = अणु
	अणु "slave-24c02", I2C_SLAVE_DEVICE_MAGIC(2048 / 8,  0) पूर्ण,
	अणु "slave-24c02ro", I2C_SLAVE_DEVICE_MAGIC(2048 / 8,  I2C_SLAVE_FLAG_RO) पूर्ण,
	अणु "slave-24c32", I2C_SLAVE_DEVICE_MAGIC(32768 / 8, I2C_SLAVE_FLAG_ADDR16) पूर्ण,
	अणु "slave-24c32ro", I2C_SLAVE_DEVICE_MAGIC(32768 / 8, I2C_SLAVE_FLAG_ADDR16 | I2C_SLAVE_FLAG_RO) पूर्ण,
	अणु "slave-24c64", I2C_SLAVE_DEVICE_MAGIC(65536 / 8, I2C_SLAVE_FLAG_ADDR16) पूर्ण,
	अणु "slave-24c64ro", I2C_SLAVE_DEVICE_MAGIC(65536 / 8, I2C_SLAVE_FLAG_ADDR16 | I2C_SLAVE_FLAG_RO) पूर्ण,
	अणु "slave-24c512", I2C_SLAVE_DEVICE_MAGIC(524288 / 8, I2C_SLAVE_FLAG_ADDR16) पूर्ण,
	अणु "slave-24c512ro", I2C_SLAVE_DEVICE_MAGIC(524288 / 8, I2C_SLAVE_FLAG_ADDR16 | I2C_SLAVE_FLAG_RO) पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, i2c_slave_eeprom_id);

अटल काष्ठा i2c_driver i2c_slave_eeprom_driver = अणु
	.driver = अणु
		.name = "i2c-slave-eeprom",
	पूर्ण,
	.probe = i2c_slave_eeprom_probe,
	.हटाओ = i2c_slave_eeprom_हटाओ,
	.id_table = i2c_slave_eeprom_id,
पूर्ण;
module_i2c_driver(i2c_slave_eeprom_driver);

MODULE_AUTHOR("Wolfram Sang <wsa@sang-engineering.com>");
MODULE_DESCRIPTION("I2C slave mode EEPROM simulator");
MODULE_LICENSE("GPL v2");
