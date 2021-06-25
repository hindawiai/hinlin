<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Hardware monitoring driver क्रम UCD90xxx Sequencer and System Health
 * Controller series
 *
 * Copyright (C) 2011 Ericsson AB.
 */

#समावेश <linux/debugfs.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/init.h>
#समावेश <linux/err.h>
#समावेश <linux/slab.h>
#समावेश <linux/i2c.h>
#समावेश <linux/pmbus.h>
#समावेश <linux/gpio/driver.h>
#समावेश "pmbus.h"

क्रमागत chips अणु ucd9000, ucd90120, ucd90124, ucd90160, ucd90320, ucd9090,
	     ucd90910 पूर्ण;

#घोषणा UCD9000_MONITOR_CONFIG		0xd5
#घोषणा UCD9000_NUM_PAGES		0xd6
#घोषणा UCD9000_FAN_CONFIG_INDEX	0xe7
#घोषणा UCD9000_FAN_CONFIG		0xe8
#घोषणा UCD9000_MFR_STATUS		0xf3
#घोषणा UCD9000_GPIO_SELECT		0xfa
#घोषणा UCD9000_GPIO_CONFIG		0xfb
#घोषणा UCD9000_DEVICE_ID		0xfd

/* GPIO CONFIG bits */
#घोषणा UCD9000_GPIO_CONFIG_ENABLE	BIT(0)
#घोषणा UCD9000_GPIO_CONFIG_OUT_ENABLE	BIT(1)
#घोषणा UCD9000_GPIO_CONFIG_OUT_VALUE	BIT(2)
#घोषणा UCD9000_GPIO_CONFIG_STATUS	BIT(3)
#घोषणा UCD9000_GPIO_INPUT		0
#घोषणा UCD9000_GPIO_OUTPUT		1

#घोषणा UCD9000_MON_TYPE(x)	(((x) >> 5) & 0x07)
#घोषणा UCD9000_MON_PAGE(x)	((x) & 0x1f)

#घोषणा UCD9000_MON_VOLTAGE	1
#घोषणा UCD9000_MON_TEMPERATURE	2
#घोषणा UCD9000_MON_CURRENT	3
#घोषणा UCD9000_MON_VOLTAGE_HW	4

#घोषणा UCD9000_NUM_FAN		4

#घोषणा UCD9000_GPIO_NAME_LEN	16
#घोषणा UCD9090_NUM_GPIOS	23
#घोषणा UCD901XX_NUM_GPIOS	26
#घोषणा UCD90320_NUM_GPIOS	84
#घोषणा UCD90910_NUM_GPIOS	26

#घोषणा UCD9000_DEBUGFS_NAME_LEN	24
#घोषणा UCD9000_GPI_COUNT		8
#घोषणा UCD90320_GPI_COUNT		32

काष्ठा ucd9000_data अणु
	u8 fan_data[UCD9000_NUM_FAN][I2C_SMBUS_BLOCK_MAX];
	काष्ठा pmbus_driver_info info;
#अगर_घोषित CONFIG_GPIOLIB
	काष्ठा gpio_chip gpio;
#पूर्ण_अगर
	काष्ठा dentry *debugfs;
पूर्ण;
#घोषणा to_ucd9000_data(_info) container_of(_info, काष्ठा ucd9000_data, info)

काष्ठा ucd9000_debugfs_entry अणु
	काष्ठा i2c_client *client;
	u8 index;
पूर्ण;

अटल पूर्णांक ucd9000_get_fan_config(काष्ठा i2c_client *client, पूर्णांक fan)
अणु
	पूर्णांक fan_config = 0;
	काष्ठा ucd9000_data *data
	  = to_ucd9000_data(pmbus_get_driver_info(client));

	अगर (data->fan_data[fan][3] & 1)
		fan_config |= PB_FAN_2_INSTALLED;   /* Use lower bit position */

	/* Pulses/revolution */
	fan_config |= (data->fan_data[fan][3] & 0x06) >> 1;

	वापस fan_config;
पूर्ण

अटल पूर्णांक ucd9000_पढ़ो_byte_data(काष्ठा i2c_client *client, पूर्णांक page, पूर्णांक reg)
अणु
	पूर्णांक ret = 0;
	पूर्णांक fan_config;

	चयन (reg) अणु
	हाल PMBUS_FAN_CONFIG_12:
		अगर (page > 0)
			वापस -ENXIO;

		ret = ucd9000_get_fan_config(client, 0);
		अगर (ret < 0)
			वापस ret;
		fan_config = ret << 4;
		ret = ucd9000_get_fan_config(client, 1);
		अगर (ret < 0)
			वापस ret;
		fan_config |= ret;
		ret = fan_config;
		अवरोध;
	हाल PMBUS_FAN_CONFIG_34:
		अगर (page > 0)
			वापस -ENXIO;

		ret = ucd9000_get_fan_config(client, 2);
		अगर (ret < 0)
			वापस ret;
		fan_config = ret << 4;
		ret = ucd9000_get_fan_config(client, 3);
		अगर (ret < 0)
			वापस ret;
		fan_config |= ret;
		ret = fan_config;
		अवरोध;
	शेष:
		ret = -ENODATA;
		अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id ucd9000_id[] = अणु
	अणु"ucd9000", ucd9000पूर्ण,
	अणु"ucd90120", ucd90120पूर्ण,
	अणु"ucd90124", ucd90124पूर्ण,
	अणु"ucd90160", ucd90160पूर्ण,
	अणु"ucd90320", ucd90320पूर्ण,
	अणु"ucd9090", ucd9090पूर्ण,
	अणु"ucd90910", ucd90910पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, ucd9000_id);

अटल स्थिर काष्ठा of_device_id __maybe_unused ucd9000_of_match[] = अणु
	अणु
		.compatible = "ti,ucd9000",
		.data = (व्योम *)ucd9000
	पूर्ण,
	अणु
		.compatible = "ti,ucd90120",
		.data = (व्योम *)ucd90120
	पूर्ण,
	अणु
		.compatible = "ti,ucd90124",
		.data = (व्योम *)ucd90124
	पूर्ण,
	अणु
		.compatible = "ti,ucd90160",
		.data = (व्योम *)ucd90160
	पूर्ण,
	अणु
		.compatible = "ti,ucd90320",
		.data = (व्योम *)ucd90320
	पूर्ण,
	अणु
		.compatible = "ti,ucd9090",
		.data = (व्योम *)ucd9090
	पूर्ण,
	अणु
		.compatible = "ti,ucd90910",
		.data = (व्योम *)ucd90910
	पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, ucd9000_of_match);

#अगर_घोषित CONFIG_GPIOLIB
अटल पूर्णांक ucd9000_gpio_पढ़ो_config(काष्ठा i2c_client *client,
				    अचिन्हित पूर्णांक offset)
अणु
	पूर्णांक ret;

	/* No page set required */
	ret = i2c_smbus_ग_लिखो_byte_data(client, UCD9000_GPIO_SELECT, offset);
	अगर (ret < 0)
		वापस ret;

	वापस i2c_smbus_पढ़ो_byte_data(client, UCD9000_GPIO_CONFIG);
पूर्ण

अटल पूर्णांक ucd9000_gpio_get(काष्ठा gpio_chip *gc, अचिन्हित पूर्णांक offset)
अणु
	काष्ठा i2c_client *client  = gpiochip_get_data(gc);
	पूर्णांक ret;

	ret = ucd9000_gpio_पढ़ो_config(client, offset);
	अगर (ret < 0)
		वापस ret;

	वापस !!(ret & UCD9000_GPIO_CONFIG_STATUS);
पूर्ण

अटल व्योम ucd9000_gpio_set(काष्ठा gpio_chip *gc, अचिन्हित पूर्णांक offset,
			     पूर्णांक value)
अणु
	काष्ठा i2c_client *client = gpiochip_get_data(gc);
	पूर्णांक ret;

	ret = ucd9000_gpio_पढ़ो_config(client, offset);
	अगर (ret < 0) अणु
		dev_dbg(&client->dev, "failed to read GPIO %d config: %d\n",
			offset, ret);
		वापस;
	पूर्ण

	अगर (value) अणु
		अगर (ret & UCD9000_GPIO_CONFIG_STATUS)
			वापस;

		ret |= UCD9000_GPIO_CONFIG_STATUS;
	पूर्ण अन्यथा अणु
		अगर (!(ret & UCD9000_GPIO_CONFIG_STATUS))
			वापस;

		ret &= ~UCD9000_GPIO_CONFIG_STATUS;
	पूर्ण

	ret |= UCD9000_GPIO_CONFIG_ENABLE;

	/* Page set not required */
	ret = i2c_smbus_ग_लिखो_byte_data(client, UCD9000_GPIO_CONFIG, ret);
	अगर (ret < 0) अणु
		dev_dbg(&client->dev, "Failed to write GPIO %d config: %d\n",
			offset, ret);
		वापस;
	पूर्ण

	ret &= ~UCD9000_GPIO_CONFIG_ENABLE;

	ret = i2c_smbus_ग_लिखो_byte_data(client, UCD9000_GPIO_CONFIG, ret);
	अगर (ret < 0)
		dev_dbg(&client->dev, "Failed to write GPIO %d config: %d\n",
			offset, ret);
पूर्ण

अटल पूर्णांक ucd9000_gpio_get_direction(काष्ठा gpio_chip *gc,
				      अचिन्हित पूर्णांक offset)
अणु
	काष्ठा i2c_client *client = gpiochip_get_data(gc);
	पूर्णांक ret;

	ret = ucd9000_gpio_पढ़ो_config(client, offset);
	अगर (ret < 0)
		वापस ret;

	वापस !(ret & UCD9000_GPIO_CONFIG_OUT_ENABLE);
पूर्ण

अटल पूर्णांक ucd9000_gpio_set_direction(काष्ठा gpio_chip *gc,
				      अचिन्हित पूर्णांक offset, bool direction_out,
				      पूर्णांक requested_out)
अणु
	काष्ठा i2c_client *client = gpiochip_get_data(gc);
	पूर्णांक ret, config, out_val;

	ret = ucd9000_gpio_पढ़ो_config(client, offset);
	अगर (ret < 0)
		वापस ret;

	अगर (direction_out) अणु
		out_val = requested_out ? UCD9000_GPIO_CONFIG_OUT_VALUE : 0;

		अगर (ret & UCD9000_GPIO_CONFIG_OUT_ENABLE) अणु
			अगर ((ret & UCD9000_GPIO_CONFIG_OUT_VALUE) == out_val)
				वापस 0;
		पूर्ण अन्यथा अणु
			ret |= UCD9000_GPIO_CONFIG_OUT_ENABLE;
		पूर्ण

		अगर (out_val)
			ret |= UCD9000_GPIO_CONFIG_OUT_VALUE;
		अन्यथा
			ret &= ~UCD9000_GPIO_CONFIG_OUT_VALUE;

	पूर्ण अन्यथा अणु
		अगर (!(ret & UCD9000_GPIO_CONFIG_OUT_ENABLE))
			वापस 0;

		ret &= ~UCD9000_GPIO_CONFIG_OUT_ENABLE;
	पूर्ण

	ret |= UCD9000_GPIO_CONFIG_ENABLE;
	config = ret;

	/* Page set not required */
	ret = i2c_smbus_ग_लिखो_byte_data(client, UCD9000_GPIO_CONFIG, config);
	अगर (ret < 0)
		वापस ret;

	config &= ~UCD9000_GPIO_CONFIG_ENABLE;

	वापस i2c_smbus_ग_लिखो_byte_data(client, UCD9000_GPIO_CONFIG, config);
पूर्ण

अटल पूर्णांक ucd9000_gpio_direction_input(काष्ठा gpio_chip *gc,
					अचिन्हित पूर्णांक offset)
अणु
	वापस ucd9000_gpio_set_direction(gc, offset, UCD9000_GPIO_INPUT, 0);
पूर्ण

अटल पूर्णांक ucd9000_gpio_direction_output(काष्ठा gpio_chip *gc,
					 अचिन्हित पूर्णांक offset, पूर्णांक val)
अणु
	वापस ucd9000_gpio_set_direction(gc, offset, UCD9000_GPIO_OUTPUT,
					  val);
पूर्ण

अटल व्योम ucd9000_probe_gpio(काष्ठा i2c_client *client,
			       स्थिर काष्ठा i2c_device_id *mid,
			       काष्ठा ucd9000_data *data)
अणु
	पूर्णांक rc;

	चयन (mid->driver_data) अणु
	हाल ucd9090:
		data->gpio.ngpio = UCD9090_NUM_GPIOS;
		अवरोध;
	हाल ucd90120:
	हाल ucd90124:
	हाल ucd90160:
		data->gpio.ngpio = UCD901XX_NUM_GPIOS;
		अवरोध;
	हाल ucd90320:
		data->gpio.ngpio = UCD90320_NUM_GPIOS;
		अवरोध;
	हाल ucd90910:
		data->gpio.ngpio = UCD90910_NUM_GPIOS;
		अवरोध;
	शेष:
		वापस; /* GPIO support is optional. */
	पूर्ण

	/*
	 * Pinmux support has not been added to the new gpio_chip.
	 * This support should be added when possible given the mux
	 * behavior of these IO devices.
	 */
	data->gpio.label = client->name;
	data->gpio.get_direction = ucd9000_gpio_get_direction;
	data->gpio.direction_input = ucd9000_gpio_direction_input;
	data->gpio.direction_output = ucd9000_gpio_direction_output;
	data->gpio.get = ucd9000_gpio_get;
	data->gpio.set = ucd9000_gpio_set;
	data->gpio.can_sleep = true;
	data->gpio.base = -1;
	data->gpio.parent = &client->dev;

	rc = devm_gpiochip_add_data(&client->dev, &data->gpio, client);
	अगर (rc)
		dev_warn(&client->dev, "Could not add gpiochip: %d\n", rc);
पूर्ण
#अन्यथा
अटल व्योम ucd9000_probe_gpio(काष्ठा i2c_client *client,
			       स्थिर काष्ठा i2c_device_id *mid,
			       काष्ठा ucd9000_data *data)
अणु
पूर्ण
#पूर्ण_अगर /* CONFIG_GPIOLIB */

#अगर_घोषित CONFIG_DEBUG_FS
अटल पूर्णांक ucd9000_get_mfr_status(काष्ठा i2c_client *client, u8 *buffer)
अणु
	पूर्णांक ret = pmbus_set_page(client, 0, 0xff);

	अगर (ret < 0)
		वापस ret;

	वापस i2c_smbus_पढ़ो_block_data(client, UCD9000_MFR_STATUS, buffer);
पूर्ण

अटल पूर्णांक ucd9000_debugfs_show_mfr_status_bit(व्योम *data, u64 *val)
अणु
	काष्ठा ucd9000_debugfs_entry *entry = data;
	काष्ठा i2c_client *client = entry->client;
	u8 buffer[I2C_SMBUS_BLOCK_MAX];
	पूर्णांक ret, i;

	ret = ucd9000_get_mfr_status(client, buffer);
	अगर (ret < 0)
		वापस ret;

	/*
	 * GPI fault bits are in sets of 8, two bytes from end of response.
	 */
	i = ret - 3 - entry->index / 8;
	अगर (i >= 0)
		*val = !!(buffer[i] & BIT(entry->index % 8));

	वापस 0;
पूर्ण
DEFINE_DEBUGFS_ATTRIBUTE(ucd9000_debugfs_mfr_status_bit,
			 ucd9000_debugfs_show_mfr_status_bit, शून्य, "%1lld\n");

अटल sमाप_प्रकार ucd9000_debugfs_पढ़ो_mfr_status(काष्ठा file *file,
					       अक्षर __user *buf, माप_प्रकार count,
					       loff_t *ppos)
अणु
	काष्ठा i2c_client *client = file->निजी_data;
	u8 buffer[I2C_SMBUS_BLOCK_MAX];
	अक्षर str[(I2C_SMBUS_BLOCK_MAX * 2) + 2];
	अक्षर *res;
	पूर्णांक rc;

	rc = ucd9000_get_mfr_status(client, buffer);
	अगर (rc < 0)
		वापस rc;

	res = bin2hex(str, buffer, min(rc, I2C_SMBUS_BLOCK_MAX));
	*res++ = '\n';
	*res = 0;

	वापस simple_पढ़ो_from_buffer(buf, count, ppos, str, res - str);
पूर्ण

अटल स्थिर काष्ठा file_operations ucd9000_debugfs_show_mfr_status_fops = अणु
	.llseek = noop_llseek,
	.पढ़ो = ucd9000_debugfs_पढ़ो_mfr_status,
	.खोलो = simple_खोलो,
पूर्ण;

अटल पूर्णांक ucd9000_init_debugfs(काष्ठा i2c_client *client,
				स्थिर काष्ठा i2c_device_id *mid,
				काष्ठा ucd9000_data *data)
अणु
	काष्ठा dentry *debugfs;
	काष्ठा ucd9000_debugfs_entry *entries;
	पूर्णांक i, gpi_count;
	अक्षर name[UCD9000_DEBUGFS_NAME_LEN];

	debugfs = pmbus_get_debugfs_dir(client);
	अगर (!debugfs)
		वापस -ENOENT;

	data->debugfs = debugfs_create_dir(client->name, debugfs);
	अगर (!data->debugfs)
		वापस -ENOENT;

	/*
	 * Of the chips this driver supports, only the UCD9090, UCD90160,
	 * UCD90320, and UCD90910 report GPI faults in their MFR_STATUS
	 * रेजिस्टर, so only create the GPI fault debugfs attributes क्रम those
	 * chips.
	 */
	अगर (mid->driver_data == ucd9090 || mid->driver_data == ucd90160 ||
	    mid->driver_data == ucd90320 || mid->driver_data == ucd90910) अणु
		gpi_count = mid->driver_data == ucd90320 ? UCD90320_GPI_COUNT
							 : UCD9000_GPI_COUNT;
		entries = devm_kसुस्मृति(&client->dev,
				       gpi_count, माप(*entries),
				       GFP_KERNEL);
		अगर (!entries)
			वापस -ENOMEM;

		क्रम (i = 0; i < gpi_count; i++) अणु
			entries[i].client = client;
			entries[i].index = i;
			scnम_लिखो(name, UCD9000_DEBUGFS_NAME_LEN,
				  "gpi%d_alarm", i + 1);
			debugfs_create_file(name, 0444, data->debugfs,
					    &entries[i],
					    &ucd9000_debugfs_mfr_status_bit);
		पूर्ण
	पूर्ण

	scnम_लिखो(name, UCD9000_DEBUGFS_NAME_LEN, "mfr_status");
	debugfs_create_file(name, 0444, data->debugfs, client,
			    &ucd9000_debugfs_show_mfr_status_fops);

	वापस 0;
पूर्ण
#अन्यथा
अटल पूर्णांक ucd9000_init_debugfs(काष्ठा i2c_client *client,
				स्थिर काष्ठा i2c_device_id *mid,
				काष्ठा ucd9000_data *data)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_DEBUG_FS */

अटल पूर्णांक ucd9000_probe(काष्ठा i2c_client *client)
अणु
	u8 block_buffer[I2C_SMBUS_BLOCK_MAX + 1];
	काष्ठा ucd9000_data *data;
	काष्ठा pmbus_driver_info *info;
	स्थिर काष्ठा i2c_device_id *mid;
	क्रमागत chips chip;
	पूर्णांक i, ret;

	अगर (!i2c_check_functionality(client->adapter,
				     I2C_FUNC_SMBUS_BYTE_DATA |
				     I2C_FUNC_SMBUS_BLOCK_DATA))
		वापस -ENODEV;

	ret = i2c_smbus_पढ़ो_block_data(client, UCD9000_DEVICE_ID,
					block_buffer);
	अगर (ret < 0) अणु
		dev_err(&client->dev, "Failed to read device ID\n");
		वापस ret;
	पूर्ण
	block_buffer[ret] = '\0';
	dev_info(&client->dev, "Device ID %s\n", block_buffer);

	क्रम (mid = ucd9000_id; mid->name[0]; mid++) अणु
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

	अगर (chip != ucd9000 && म_भेद(client->name, mid->name) != 0)
		dev_notice(&client->dev,
			   "Device mismatch: Configured %s, detected %s\n",
			   client->name, mid->name);

	data = devm_kzalloc(&client->dev, माप(काष्ठा ucd9000_data),
			    GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;
	info = &data->info;

	ret = i2c_smbus_पढ़ो_byte_data(client, UCD9000_NUM_PAGES);
	अगर (ret < 0) अणु
		dev_err(&client->dev,
			"Failed to read number of active pages\n");
		वापस ret;
	पूर्ण
	info->pages = ret;
	अगर (!info->pages) अणु
		dev_err(&client->dev, "No pages configured\n");
		वापस -ENODEV;
	पूर्ण

	/* The पूर्णांकernal temperature sensor is always active */
	info->func[0] = PMBUS_HAVE_TEMP;

	/* Everything अन्यथा is configurable */
	ret = i2c_smbus_पढ़ो_block_data(client, UCD9000_MONITOR_CONFIG,
					block_buffer);
	अगर (ret <= 0) अणु
		dev_err(&client->dev, "Failed to read configuration data\n");
		वापस -ENODEV;
	पूर्ण
	क्रम (i = 0; i < ret; i++) अणु
		पूर्णांक page = UCD9000_MON_PAGE(block_buffer[i]);

		अगर (page >= info->pages)
			जारी;

		चयन (UCD9000_MON_TYPE(block_buffer[i])) अणु
		हाल UCD9000_MON_VOLTAGE:
		हाल UCD9000_MON_VOLTAGE_HW:
			info->func[page] |= PMBUS_HAVE_VOUT
			  | PMBUS_HAVE_STATUS_VOUT;
			अवरोध;
		हाल UCD9000_MON_TEMPERATURE:
			info->func[page] |= PMBUS_HAVE_TEMP2
			  | PMBUS_HAVE_STATUS_TEMP;
			अवरोध;
		हाल UCD9000_MON_CURRENT:
			info->func[page] |= PMBUS_HAVE_IOUT
			  | PMBUS_HAVE_STATUS_IOUT;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

	/* Fan configuration */
	अगर (mid->driver_data == ucd90124) अणु
		क्रम (i = 0; i < UCD9000_NUM_FAN; i++) अणु
			i2c_smbus_ग_लिखो_byte_data(client,
						  UCD9000_FAN_CONFIG_INDEX, i);
			ret = i2c_smbus_पढ़ो_block_data(client,
							UCD9000_FAN_CONFIG,
							data->fan_data[i]);
			अगर (ret < 0)
				वापस ret;
		पूर्ण
		i2c_smbus_ग_लिखो_byte_data(client, UCD9000_FAN_CONFIG_INDEX, 0);

		info->पढ़ो_byte_data = ucd9000_पढ़ो_byte_data;
		info->func[0] |= PMBUS_HAVE_FAN12 | PMBUS_HAVE_STATUS_FAN12
		  | PMBUS_HAVE_FAN34 | PMBUS_HAVE_STATUS_FAN34;
	पूर्ण

	ucd9000_probe_gpio(client, mid, data);

	ret = pmbus_करो_probe(client, info);
	अगर (ret)
		वापस ret;

	ret = ucd9000_init_debugfs(client, mid, data);
	अगर (ret)
		dev_warn(&client->dev, "Failed to register debugfs: %d\n",
			 ret);

	वापस 0;
पूर्ण

/* This is the driver that will be inserted */
अटल काष्ठा i2c_driver ucd9000_driver = अणु
	.driver = अणु
		.name = "ucd9000",
		.of_match_table = of_match_ptr(ucd9000_of_match),
	पूर्ण,
	.probe_new = ucd9000_probe,
	.id_table = ucd9000_id,
पूर्ण;

module_i2c_driver(ucd9000_driver);

MODULE_AUTHOR("Guenter Roeck");
MODULE_DESCRIPTION("PMBus driver for TI UCD90xxx");
MODULE_LICENSE("GPL");
MODULE_IMPORT_NS(PMBUS);
