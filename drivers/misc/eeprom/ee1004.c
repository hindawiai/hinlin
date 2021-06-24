<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * ee1004 - driver क्रम DDR4 SPD EEPROMs
 *
 * Copyright (C) 2017-2019 Jean Delvare
 *
 * Based on the at24 driver:
 * Copyright (C) 2005-2007 David Brownell
 * Copyright (C) 2008 Wolfram Sang, Pengutronix
 */

#समावेश <linux/i2c.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>

/*
 * DDR4 memory modules use special EEPROMs following the Jedec EE1004
 * specअगरication. These are 512-byte EEPROMs using a single I2C address
 * in the 0x50-0x57 range क्रम data. One of two 256-byte page is selected
 * by writing a command to I2C address 0x36 or 0x37 on the same I2C bus.
 *
 * Thereक्रमe we need to request these 2 additional addresses, and serialize
 * access to all such EEPROMs with a single mutex.
 *
 * We assume it is safe to पढ़ो up to 32 bytes at once from these EEPROMs.
 * We use SMBus access even अगर I2C is available, these EEPROMs are small
 * enough, and पढ़ोing from them infrequent enough, that we favor simplicity
 * over perक्रमmance.
 */

#घोषणा EE1004_ADDR_SET_PAGE		0x36
#घोषणा EE1004_EEPROM_SIZE		512
#घोषणा EE1004_PAGE_SIZE		256
#घोषणा EE1004_PAGE_SHIFT		8

/*
 * Mutex protects ee1004_set_page and ee1004_dev_count, and must be held
 * from page selection to end of पढ़ो.
 */
अटल DEFINE_MUTEX(ee1004_bus_lock);
अटल काष्ठा i2c_client *ee1004_set_page[2];
अटल अचिन्हित पूर्णांक ee1004_dev_count;
अटल पूर्णांक ee1004_current_page;

अटल स्थिर काष्ठा i2c_device_id ee1004_ids[] = अणु
	अणु "ee1004", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, ee1004_ids);

/*-------------------------------------------------------------------------*/

अटल पूर्णांक ee1004_get_current_page(व्योम)
अणु
	पूर्णांक err;

	err = i2c_smbus_पढ़ो_byte(ee1004_set_page[0]);
	अगर (err == -ENXIO) अणु
		/* Nack means page 1 is selected */
		वापस 1;
	पूर्ण
	अगर (err < 0) अणु
		/* Anything अन्यथा is a real error, bail out */
		वापस err;
	पूर्ण

	/* Ack means page 0 is selected, वापसed value meaningless */
	वापस 0;
पूर्ण

अटल sमाप_प्रकार ee1004_eeprom_पढ़ो(काष्ठा i2c_client *client, अक्षर *buf,
				  अचिन्हित पूर्णांक offset, माप_प्रकार count)
अणु
	पूर्णांक status;

	अगर (count > I2C_SMBUS_BLOCK_MAX)
		count = I2C_SMBUS_BLOCK_MAX;
	/* Can't cross page boundaries */
	अगर (unlikely(offset + count > EE1004_PAGE_SIZE))
		count = EE1004_PAGE_SIZE - offset;

	status = i2c_smbus_पढ़ो_i2c_block_data_or_emulated(client, offset,
							   count, buf);
	dev_dbg(&client->dev, "read %zu@%d --> %d\n", count, offset, status);

	वापस status;
पूर्ण

अटल sमाप_प्रकार ee1004_पढ़ो(काष्ठा file *filp, काष्ठा kobject *kobj,
			   काष्ठा bin_attribute *bin_attr,
			   अक्षर *buf, loff_t off, माप_प्रकार count)
अणु
	काष्ठा device *dev = kobj_to_dev(kobj);
	काष्ठा i2c_client *client = to_i2c_client(dev);
	माप_प्रकार requested = count;
	पूर्णांक page;

	अगर (unlikely(!count))
		वापस count;

	page = off >> EE1004_PAGE_SHIFT;
	अगर (unlikely(page > 1))
		वापस 0;
	off &= (1 << EE1004_PAGE_SHIFT) - 1;

	/*
	 * Read data from chip, protecting against concurrent access to
	 * other EE1004 SPD EEPROMs on the same adapter.
	 */
	mutex_lock(&ee1004_bus_lock);

	जबतक (count) अणु
		पूर्णांक status;

		/* Select page */
		अगर (page != ee1004_current_page) अणु
			/* Data is ignored */
			status = i2c_smbus_ग_लिखो_byte(ee1004_set_page[page],
						      0x00);
			अगर (status == -ENXIO) अणु
				/*
				 * Don't give up just yet. Some memory
				 * modules will select the page but not
				 * ack the command. Check which page is
				 * selected now.
				 */
				अगर (ee1004_get_current_page() == page)
					status = 0;
			पूर्ण
			अगर (status < 0) अणु
				dev_err(dev, "Failed to select page %d (%d)\n",
					page, status);
				mutex_unlock(&ee1004_bus_lock);
				वापस status;
			पूर्ण
			dev_dbg(dev, "Selected page %d\n", page);
			ee1004_current_page = page;
		पूर्ण

		status = ee1004_eeprom_पढ़ो(client, buf, off, count);
		अगर (status < 0) अणु
			mutex_unlock(&ee1004_bus_lock);
			वापस status;
		पूर्ण
		buf += status;
		off += status;
		count -= status;

		अगर (off == EE1004_PAGE_SIZE) अणु
			page++;
			off = 0;
		पूर्ण
	पूर्ण

	mutex_unlock(&ee1004_bus_lock);

	वापस requested;
पूर्ण

अटल स्थिर काष्ठा bin_attribute eeprom_attr = अणु
	.attr = अणु
		.name = "eeprom",
		.mode = 0444,
	पूर्ण,
	.size = EE1004_EEPROM_SIZE,
	.पढ़ो = ee1004_पढ़ो,
पूर्ण;

अटल पूर्णांक ee1004_probe(काष्ठा i2c_client *client,
			स्थिर काष्ठा i2c_device_id *id)
अणु
	पूर्णांक err, cnr = 0;
	स्थिर अक्षर *slow = शून्य;

	/* Make sure we can operate on this adapter */
	अगर (!i2c_check_functionality(client->adapter,
				     I2C_FUNC_SMBUS_READ_BYTE |
				     I2C_FUNC_SMBUS_READ_I2C_BLOCK)) अणु
		अगर (i2c_check_functionality(client->adapter,
				     I2C_FUNC_SMBUS_READ_BYTE |
				     I2C_FUNC_SMBUS_READ_WORD_DATA))
			slow = "word";
		अन्यथा अगर (i2c_check_functionality(client->adapter,
				     I2C_FUNC_SMBUS_READ_BYTE |
				     I2C_FUNC_SMBUS_READ_BYTE_DATA))
			slow = "byte";
		अन्यथा
			वापस -EPFNOSUPPORT;
	पूर्ण

	/* Use 2 dummy devices क्रम page select command */
	mutex_lock(&ee1004_bus_lock);
	अगर (++ee1004_dev_count == 1) अणु
		क्रम (cnr = 0; cnr < 2; cnr++) अणु
			ee1004_set_page[cnr] = i2c_new_dummy_device(client->adapter,
						EE1004_ADDR_SET_PAGE + cnr);
			अगर (IS_ERR(ee1004_set_page[cnr])) अणु
				dev_err(&client->dev,
					"address 0x%02x unavailable\n",
					EE1004_ADDR_SET_PAGE + cnr);
				err = PTR_ERR(ee1004_set_page[cnr]);
				जाओ err_clients;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अगर (i2c_adapter_id(client->adapter) !=
		   i2c_adapter_id(ee1004_set_page[0]->adapter)) अणु
		dev_err(&client->dev,
			"Driver only supports devices on a single I2C bus\n");
		err = -EOPNOTSUPP;
		जाओ err_clients;
	पूर्ण

	/* Remember current page to aव्योम unneeded page select */
	err = ee1004_get_current_page();
	अगर (err < 0)
		जाओ err_clients;
	ee1004_current_page = err;
	dev_dbg(&client->dev, "Currently selected page: %d\n",
		ee1004_current_page);
	mutex_unlock(&ee1004_bus_lock);

	/* Create the sysfs eeprom file */
	err = sysfs_create_bin_file(&client->dev.kobj, &eeprom_attr);
	अगर (err)
		जाओ err_clients_lock;

	dev_info(&client->dev,
		 "%u byte EE1004-compliant SPD EEPROM, read-only\n",
		 EE1004_EEPROM_SIZE);
	अगर (slow)
		dev_notice(&client->dev,
			   "Falling back to %s reads, performance will suffer\n",
			   slow);

	वापस 0;

 err_clients_lock:
	mutex_lock(&ee1004_bus_lock);
 err_clients:
	अगर (--ee1004_dev_count == 0) अणु
		क्रम (cnr--; cnr >= 0; cnr--) अणु
			i2c_unरेजिस्टर_device(ee1004_set_page[cnr]);
			ee1004_set_page[cnr] = शून्य;
		पूर्ण
	पूर्ण
	mutex_unlock(&ee1004_bus_lock);

	वापस err;
पूर्ण

अटल पूर्णांक ee1004_हटाओ(काष्ठा i2c_client *client)
अणु
	पूर्णांक i;

	sysfs_हटाओ_bin_file(&client->dev.kobj, &eeprom_attr);

	/* Remove page select clients अगर this is the last device */
	mutex_lock(&ee1004_bus_lock);
	अगर (--ee1004_dev_count == 0) अणु
		क्रम (i = 0; i < 2; i++) अणु
			i2c_unरेजिस्टर_device(ee1004_set_page[i]);
			ee1004_set_page[i] = शून्य;
		पूर्ण
	पूर्ण
	mutex_unlock(&ee1004_bus_lock);

	वापस 0;
पूर्ण

/*-------------------------------------------------------------------------*/

अटल काष्ठा i2c_driver ee1004_driver = अणु
	.driver = अणु
		.name = "ee1004",
	पूर्ण,
	.probe = ee1004_probe,
	.हटाओ = ee1004_हटाओ,
	.id_table = ee1004_ids,
पूर्ण;
module_i2c_driver(ee1004_driver);

MODULE_DESCRIPTION("Driver for EE1004-compliant DDR4 SPD EEPROMs");
MODULE_AUTHOR("Jean Delvare");
MODULE_LICENSE("GPL");
