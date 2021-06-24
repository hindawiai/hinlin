<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Hardware monitoring driver क्रम ucd9200 series Digital PWM System Controllers
 *
 * Copyright (C) 2011 Ericsson AB.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/init.h>
#समावेश <linux/err.h>
#समावेश <linux/slab.h>
#समावेश <linux/i2c.h>
#समावेश <linux/pmbus.h>
#समावेश "pmbus.h"

#घोषणा UCD9200_PHASE_INFO	0xd2
#घोषणा UCD9200_DEVICE_ID	0xfd

क्रमागत chips अणु ucd9200, ucd9220, ucd9222, ucd9224, ucd9240, ucd9244, ucd9246,
	     ucd9248 पूर्ण;

अटल स्थिर काष्ठा i2c_device_id ucd9200_id[] = अणु
	अणु"ucd9200", ucd9200पूर्ण,
	अणु"ucd9220", ucd9220पूर्ण,
	अणु"ucd9222", ucd9222पूर्ण,
	अणु"ucd9224", ucd9224पूर्ण,
	अणु"ucd9240", ucd9240पूर्ण,
	अणु"ucd9244", ucd9244पूर्ण,
	अणु"ucd9246", ucd9246पूर्ण,
	अणु"ucd9248", ucd9248पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, ucd9200_id);

अटल स्थिर काष्ठा of_device_id __maybe_unused ucd9200_of_match[] = अणु
	अणु
		.compatible = "ti,cd9200",
		.data = (व्योम *)ucd9200
	पूर्ण,
	अणु
		.compatible = "ti,cd9220",
		.data = (व्योम *)ucd9220
	पूर्ण,
	अणु
		.compatible = "ti,cd9222",
		.data = (व्योम *)ucd9222
	पूर्ण,
	अणु
		.compatible = "ti,cd9224",
		.data = (व्योम *)ucd9224
	पूर्ण,
	अणु
		.compatible = "ti,cd9240",
		.data = (व्योम *)ucd9240
	पूर्ण,
	अणु
		.compatible = "ti,cd9244",
		.data = (व्योम *)ucd9244
	पूर्ण,
	अणु
		.compatible = "ti,cd9246",
		.data = (व्योम *)ucd9246
	पूर्ण,
	अणु
		.compatible = "ti,cd9248",
		.data = (व्योम *)ucd9248
	पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, ucd9200_of_match);

अटल पूर्णांक ucd9200_probe(काष्ठा i2c_client *client)
अणु
	u8 block_buffer[I2C_SMBUS_BLOCK_MAX + 1];
	काष्ठा pmbus_driver_info *info;
	स्थिर काष्ठा i2c_device_id *mid;
	क्रमागत chips chip;
	पूर्णांक i, j, ret;

	अगर (!i2c_check_functionality(client->adapter,
				     I2C_FUNC_SMBUS_BYTE_DATA |
				     I2C_FUNC_SMBUS_BLOCK_DATA))
		वापस -ENODEV;

	ret = i2c_smbus_पढ़ो_block_data(client, UCD9200_DEVICE_ID,
					block_buffer);
	अगर (ret < 0) अणु
		dev_err(&client->dev, "Failed to read device ID\n");
		वापस ret;
	पूर्ण
	block_buffer[ret] = '\0';
	dev_info(&client->dev, "Device ID %s\n", block_buffer);

	क्रम (mid = ucd9200_id; mid->name[0]; mid++) अणु
		अगर (!strnहालcmp(mid->name, block_buffer, म_माप(mid->name)))
			अवरोध;
	पूर्ण
	अगर (!mid->name[0]) अणु
		dev_err(&client->dev, "Unsupported device\n");
		वापस -ENODEV;
	पूर्ण

	अगर (client->dev.of_node)
		chip = (क्रमागत chips)of_device_get_match_data(&client->dev);
	अन्यथा
		chip = mid->driver_data;

	अगर (chip != ucd9200 && म_भेद(client->name, mid->name) != 0)
		dev_notice(&client->dev,
			   "Device mismatch: Configured %s, detected %s\n",
			   client->name, mid->name);

	info = devm_kzalloc(&client->dev, माप(काष्ठा pmbus_driver_info),
			    GFP_KERNEL);
	अगर (!info)
		वापस -ENOMEM;

	ret = i2c_smbus_पढ़ो_block_data(client, UCD9200_PHASE_INFO,
					block_buffer);
	अगर (ret < 0) अणु
		dev_err(&client->dev, "Failed to read phase information\n");
		वापस ret;
	पूर्ण

	/*
	 * Calculate number of configured pages (rails) from PHASE_INFO
	 * रेजिस्टर.
	 * Rails have to be sequential, so we can पात after finding
	 * the first unconfigured rail.
	 */
	info->pages = 0;
	क्रम (i = 0; i < ret; i++) अणु
		अगर (!block_buffer[i])
			अवरोध;
		info->pages++;
	पूर्ण
	अगर (!info->pages) अणु
		dev_err(&client->dev, "No rails configured\n");
		वापस -ENODEV;
	पूर्ण
	dev_info(&client->dev, "%d rails configured\n", info->pages);

	/*
	 * Set PHASE रेजिस्टरs on all pages to 0xff to ensure that phase
	 * specअगरic commands will apply to all phases of a given page (rail).
	 * This only affects the READ_IOUT and READ_TEMPERATURE2 रेजिस्टरs.
	 * READ_IOUT will वापस the sum of currents of all phases of a rail,
	 * and READ_TEMPERATURE2 will वापस the maximum temperature detected
	 * क्रम the the phases of the rail.
	 */
	क्रम (i = 0; i < info->pages; i++) अणु
		/*
		 * Setting PAGE & PHASE fails once in a जबतक क्रम no obvious
		 * reason, so we need to retry a couple of बार.
		 */
		क्रम (j = 0; j < 3; j++) अणु
			ret = i2c_smbus_ग_लिखो_byte_data(client, PMBUS_PAGE, i);
			अगर (ret < 0)
				जारी;
			ret = i2c_smbus_ग_लिखो_byte_data(client, PMBUS_PHASE,
							0xff);
			अगर (ret < 0)
				जारी;
			अवरोध;
		पूर्ण
		अगर (ret < 0) अणु
			dev_err(&client->dev,
				"Failed to initialize PHASE registers\n");
			वापस ret;
		पूर्ण
	पूर्ण
	अगर (info->pages > 1)
		i2c_smbus_ग_लिखो_byte_data(client, PMBUS_PAGE, 0);

	info->func[0] = PMBUS_HAVE_VIN | PMBUS_HAVE_STATUS_INPUT |
			PMBUS_HAVE_IIN | PMBUS_HAVE_PIN |
			PMBUS_HAVE_VOUT | PMBUS_HAVE_STATUS_VOUT |
			PMBUS_HAVE_IOUT | PMBUS_HAVE_STATUS_IOUT |
			PMBUS_HAVE_POUT | PMBUS_HAVE_TEMP |
			PMBUS_HAVE_TEMP2 | PMBUS_HAVE_STATUS_TEMP;

	क्रम (i = 1; i < info->pages; i++)
		info->func[i] = PMBUS_HAVE_VOUT | PMBUS_HAVE_STATUS_VOUT |
			PMBUS_HAVE_IOUT | PMBUS_HAVE_STATUS_IOUT |
			PMBUS_HAVE_POUT |
			PMBUS_HAVE_TEMP2 | PMBUS_HAVE_STATUS_TEMP;

	/* ucd9240 supports a single fan */
	अगर (mid->driver_data == ucd9240)
		info->func[0] |= PMBUS_HAVE_FAN12 | PMBUS_HAVE_STATUS_FAN12;

	वापस pmbus_करो_probe(client, info);
पूर्ण

/* This is the driver that will be inserted */
अटल काष्ठा i2c_driver ucd9200_driver = अणु
	.driver = अणु
		.name = "ucd9200",
		.of_match_table = of_match_ptr(ucd9200_of_match),
	पूर्ण,
	.probe_new = ucd9200_probe,
	.id_table = ucd9200_id,
पूर्ण;

module_i2c_driver(ucd9200_driver);

MODULE_AUTHOR("Guenter Roeck");
MODULE_DESCRIPTION("PMBus driver for TI UCD922x, UCD924x");
MODULE_LICENSE("GPL");
MODULE_IMPORT_NS(PMBUS);
