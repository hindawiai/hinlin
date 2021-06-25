<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Hardware monitoring driver क्रम Maxim MAX15301
 *
 * Copyright (c) 2021 Flextronics International Sweden AB
 *
 * Even though the specअगरication करोes not specअगरically mention it,
 * extensive empirical testing has revealed that स्वतः-detection of
 * limit-रेजिस्टरs will fail in a अक्रमom fashion unless the delay
 * parameter is set to above about 80us. The शेष delay is set
 * to 100us to include some safety margin.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/err.h>
#समावेश <linux/slab.h>
#समावेश <linux/i2c.h>
#समावेश <linux/kसमय.स>
#समावेश <linux/delay.h>
#समावेश <linux/pmbus.h>
#समावेश "pmbus.h"

अटल स्थिर काष्ठा i2c_device_id max15301_id[] = अणु
	अणु"bmr461", 0पूर्ण,
	अणु"max15301", 0पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, max15301_id);

काष्ठा max15301_data अणु
	पूर्णांक id;
	kसमय_प्रकार access;		/* Chip access समय */
	पूर्णांक delay;		/* Delay between chip accesses in us */
	काष्ठा pmbus_driver_info info;
पूर्ण;

#घोषणा to_max15301_data(x)  container_of(x, काष्ठा max15301_data, info)

#घोषणा MAX15301_WAIT_TIME		100	/* us	*/

अटल uलघु delay = MAX15301_WAIT_TIME;
module_param(delay, uलघु, 0644);
MODULE_PARM_DESC(delay, "Delay between chip accesses in us");

अटल काष्ठा max15301_data max15301_data = अणु
	.info = अणु
		.pages = 1,
		.func[0] = PMBUS_HAVE_VOUT | PMBUS_HAVE_STATUS_VOUT
			| PMBUS_HAVE_VIN | PMBUS_HAVE_STATUS_INPUT
			| PMBUS_HAVE_TEMP | PMBUS_HAVE_TEMP2
			| PMBUS_HAVE_STATUS_TEMP
			| PMBUS_HAVE_IOUT | PMBUS_HAVE_STATUS_IOUT,
	पूर्ण
पूर्ण;

/* This chip needs a delay between accesses */
अटल अंतरभूत व्योम max15301_रुको(स्थिर काष्ठा max15301_data *data)
अणु
	अगर (data->delay) अणु
		s64 delta = kसमय_us_delta(kसमय_get(), data->access);

		अगर (delta < data->delay)
			udelay(data->delay - delta);
	पूर्ण
पूर्ण

अटल पूर्णांक max15301_पढ़ो_word_data(काष्ठा i2c_client *client, पूर्णांक page,
				   पूर्णांक phase, पूर्णांक reg)
अणु
	स्थिर काष्ठा pmbus_driver_info *info = pmbus_get_driver_info(client);
	काष्ठा max15301_data *data = to_max15301_data(info);
	पूर्णांक ret;

	अगर (page > 0)
		वापस -ENXIO;

	अगर (reg >= PMBUS_VIRT_BASE)
		वापस -ENXIO;

	max15301_रुको(data);
	ret = pmbus_पढ़ो_word_data(client, page, phase, reg);
	data->access = kसमय_get();

	वापस ret;
पूर्ण

अटल पूर्णांक max15301_पढ़ो_byte_data(काष्ठा i2c_client *client, पूर्णांक page, पूर्णांक reg)
अणु
	स्थिर काष्ठा pmbus_driver_info *info = pmbus_get_driver_info(client);
	काष्ठा max15301_data *data = to_max15301_data(info);
	पूर्णांक ret;

	अगर (page > 0)
		वापस -ENXIO;

	max15301_रुको(data);
	ret = pmbus_पढ़ो_byte_data(client, page, reg);
	data->access = kसमय_get();

	वापस ret;
पूर्ण

अटल पूर्णांक max15301_ग_लिखो_word_data(काष्ठा i2c_client *client, पूर्णांक page, पूर्णांक reg,
				    u16 word)
अणु
	स्थिर काष्ठा pmbus_driver_info *info = pmbus_get_driver_info(client);
	काष्ठा max15301_data *data = to_max15301_data(info);
	पूर्णांक ret;

	अगर (page > 0)
		वापस -ENXIO;

	अगर (reg >= PMBUS_VIRT_BASE)
		वापस -ENXIO;

	max15301_रुको(data);
	ret = pmbus_ग_लिखो_word_data(client, page, reg, word);
	data->access = kसमय_get();

	वापस ret;
पूर्ण

अटल पूर्णांक max15301_ग_लिखो_byte(काष्ठा i2c_client *client, पूर्णांक page, u8 value)
अणु
	स्थिर काष्ठा pmbus_driver_info *info = pmbus_get_driver_info(client);
	काष्ठा max15301_data *data = to_max15301_data(info);
	पूर्णांक ret;

	अगर (page > 0)
		वापस -ENXIO;

	max15301_रुको(data);
	ret = pmbus_ग_लिखो_byte(client, page, value);
	data->access = kसमय_get();

	वापस ret;
पूर्ण

अटल पूर्णांक max15301_probe(काष्ठा i2c_client *client)
अणु
	पूर्णांक status;
	u8 device_id[I2C_SMBUS_BLOCK_MAX + 1];
	स्थिर काष्ठा i2c_device_id *mid;
	काष्ठा pmbus_driver_info *info = &max15301_data.info;

	अगर (!i2c_check_functionality(client->adapter,
				     I2C_FUNC_SMBUS_READ_BYTE_DATA
				     | I2C_FUNC_SMBUS_BLOCK_DATA))
		वापस -ENODEV;

	status = i2c_smbus_पढ़ो_block_data(client, PMBUS_IC_DEVICE_ID, device_id);
	अगर (status < 0) अणु
		dev_err(&client->dev, "Failed to read Device Id\n");
		वापस status;
	पूर्ण
	क्रम (mid = max15301_id; mid->name[0]; mid++) अणु
		अगर (!strnहालcmp(mid->name, device_id, म_माप(mid->name)))
			अवरोध;
	पूर्ण
	अगर (!mid->name[0]) अणु
		dev_err(&client->dev, "Unsupported device\n");
		वापस -ENODEV;
	पूर्ण

	max15301_data.delay = delay;

	info->पढ़ो_byte_data = max15301_पढ़ो_byte_data;
	info->पढ़ो_word_data = max15301_पढ़ो_word_data;
	info->ग_लिखो_byte = max15301_ग_लिखो_byte;
	info->ग_लिखो_word_data = max15301_ग_लिखो_word_data;

	वापस pmbus_करो_probe(client, info);
पूर्ण

अटल काष्ठा i2c_driver max15301_driver = अणु
	.driver = अणु
		   .name = "max15301",
		   पूर्ण,
	.probe_new = max15301_probe,
	.id_table = max15301_id,
पूर्ण;

module_i2c_driver(max15301_driver);

MODULE_AUTHOR("Erik Rosen <erik.rosen@metormote.com>");
MODULE_DESCRIPTION("PMBus driver for Maxim MAX15301");
MODULE_LICENSE("GPL");
MODULE_IMPORT_NS(PMBUS);
