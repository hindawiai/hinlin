<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * ADM1266 - Cascadable Super Sequencer with Margin
 * Control and Fault Recording
 *
 * Copyright 2020 Analog Devices Inc.
 */

#समावेश <linux/bitfield.h>
#समावेश <linux/crc8.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/gpio/driver.h>
#समावेश <linux/i2c.h>
#समावेश <linux/i2c-smbus.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/nvmem-consumer.h>
#समावेश <linux/nvmem-provider.h>
#समावेश "pmbus.h"
#समावेश <linux/slab.h>
#समावेश <linux/समयkeeping.h>

#घोषणा ADM1266_BLACKBOX_CONFIG	0xD3
#घोषणा ADM1266_PDIO_CONFIG	0xD4
#घोषणा ADM1266_READ_STATE	0xD9
#घोषणा ADM1266_READ_BLACKBOX	0xDE
#घोषणा ADM1266_SET_RTC		0xDF
#घोषणा ADM1266_GPIO_CONFIG	0xE1
#घोषणा ADM1266_BLACKBOX_INFO	0xE6
#घोषणा ADM1266_PDIO_STATUS	0xE9
#घोषणा ADM1266_GPIO_STATUS	0xEA

/* ADM1266 GPIO defines */
#घोषणा ADM1266_GPIO_NR			9
#घोषणा ADM1266_GPIO_FUNCTIONS(x)	FIELD_GET(BIT(0), x)
#घोषणा ADM1266_GPIO_INPUT_EN(x)	FIELD_GET(BIT(2), x)
#घोषणा ADM1266_GPIO_OUTPUT_EN(x)	FIELD_GET(BIT(3), x)
#घोषणा ADM1266_GPIO_OPEN_DRAIN(x)	FIELD_GET(BIT(4), x)

/* ADM1266 PDIO defines */
#घोषणा ADM1266_PDIO_NR			16
#घोषणा ADM1266_PDIO_PIN_CFG(x)		FIELD_GET(GENMASK(15, 13), x)
#घोषणा ADM1266_PDIO_GLITCH_FILT(x)	FIELD_GET(GENMASK(12, 9), x)
#घोषणा ADM1266_PDIO_OUT_CFG(x)		FIELD_GET(GENMASK(2, 0), x)

#घोषणा ADM1266_BLACKBOX_OFFSET		0
#घोषणा ADM1266_BLACKBOX_SIZE		64

#घोषणा ADM1266_PMBUS_BLOCK_MAX		255

काष्ठा adm1266_data अणु
	काष्ठा pmbus_driver_info info;
	काष्ठा gpio_chip gc;
	स्थिर अक्षर *gpio_names[ADM1266_GPIO_NR + ADM1266_PDIO_NR];
	काष्ठा i2c_client *client;
	काष्ठा dentry *debugfs_dir;
	काष्ठा nvmem_config nvmem_config;
	काष्ठा nvmem_device *nvmem;
	u8 *dev_mem;
	काष्ठा mutex buf_mutex;
	u8 ग_लिखो_buf[ADM1266_PMBUS_BLOCK_MAX + 1] ____cacheline_aligned;
	u8 पढ़ो_buf[ADM1266_PMBUS_BLOCK_MAX + 1] ____cacheline_aligned;
पूर्ण;

अटल स्थिर काष्ठा nvmem_cell_info adm1266_nvmem_cells[] = अणु
	अणु
		.name           = "blackbox",
		.offset         = ADM1266_BLACKBOX_OFFSET,
		.bytes          = 2048,
	पूर्ण,
पूर्ण;

DECLARE_CRC8_TABLE(pmbus_crc_table);

/*
 * Dअगरferent from Block Read as it sends data and रुकोs क्रम the slave to
 * वापस a value dependent on that data. The protocol is simply a Write Block
 * followed by a Read Block without the Read-Block command field and the
 * Write-Block STOP bit.
 */
अटल पूर्णांक adm1266_pmbus_block_xfer(काष्ठा adm1266_data *data, u8 cmd, u8 w_len, u8 *data_w,
				    u8 *data_r)
अणु
	काष्ठा i2c_client *client = data->client;
	काष्ठा i2c_msg msgs[2] = अणु
		अणु
			.addr = client->addr,
			.flags = I2C_M_DMA_SAFE,
			.buf = data->ग_लिखो_buf,
			.len = w_len + 2,
		पूर्ण,
		अणु
			.addr = client->addr,
			.flags = I2C_M_RD | I2C_M_DMA_SAFE,
			.buf = data->पढ़ो_buf,
			.len = ADM1266_PMBUS_BLOCK_MAX + 2,
		पूर्ण
	पूर्ण;
	u8 addr;
	u8 crc;
	पूर्णांक ret;

	mutex_lock(&data->buf_mutex);

	msgs[0].buf[0] = cmd;
	msgs[0].buf[1] = w_len;
	स_नकल(&msgs[0].buf[2], data_w, w_len);

	ret = i2c_transfer(client->adapter, msgs, 2);
	अगर (ret != 2) अणु
		अगर (ret >= 0)
			ret = -EPROTO;

		mutex_unlock(&data->buf_mutex);

		वापस ret;
	पूर्ण

	अगर (client->flags & I2C_CLIENT_PEC) अणु
		addr = i2c_8bit_addr_from_msg(&msgs[0]);
		crc = crc8(pmbus_crc_table, &addr, 1, 0);
		crc = crc8(pmbus_crc_table, msgs[0].buf,  msgs[0].len, crc);

		addr = i2c_8bit_addr_from_msg(&msgs[1]);
		crc = crc8(pmbus_crc_table, &addr, 1, crc);
		crc = crc8(pmbus_crc_table, msgs[1].buf,  msgs[1].buf[0] + 1, crc);

		अगर (crc != msgs[1].buf[msgs[1].buf[0] + 1]) अणु
			mutex_unlock(&data->buf_mutex);
			वापस -EBADMSG;
		पूर्ण
	पूर्ण

	स_नकल(data_r, &msgs[1].buf[1], msgs[1].buf[0]);

	ret = msgs[1].buf[0];
	mutex_unlock(&data->buf_mutex);

	वापस ret;
पूर्ण

अटल स्थिर अचिन्हित पूर्णांक adm1266_gpio_mapping[ADM1266_GPIO_NR][2] = अणु
	अणु1, 0पूर्ण,
	अणु2, 1पूर्ण,
	अणु3, 2पूर्ण,
	अणु4, 8पूर्ण,
	अणु5, 9पूर्ण,
	अणु6, 10पूर्ण,
	अणु7, 11पूर्ण,
	अणु8, 6पूर्ण,
	अणु9, 7पूर्ण,
पूर्ण;

अटल स्थिर अक्षर *adm1266_names[ADM1266_GPIO_NR + ADM1266_PDIO_NR] = अणु
	"GPIO1", "GPIO2", "GPIO3", "GPIO4", "GPIO5", "GPIO6", "GPIO7", "GPIO8",
	"GPIO9", "PDIO1", "PDIO2", "PDIO3", "PDIO4", "PDIO5", "PDIO6",
	"PDIO7", "PDIO8", "PDIO9", "PDIO10", "PDIO11", "PDIO12", "PDIO13",
	"PDIO14", "PDIO15", "PDIO16",
पूर्ण;

अटल पूर्णांक adm1266_gpio_get(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset)
अणु
	काष्ठा adm1266_data *data = gpiochip_get_data(chip);
	u8 पढ़ो_buf[I2C_SMBUS_BLOCK_MAX + 1];
	अचिन्हित दीर्घ pins_status;
	अचिन्हित पूर्णांक pmbus_cmd;
	पूर्णांक ret;

	अगर (offset < ADM1266_GPIO_NR)
		pmbus_cmd = ADM1266_GPIO_STATUS;
	अन्यथा
		pmbus_cmd = ADM1266_PDIO_STATUS;

	ret = i2c_smbus_पढ़ो_block_data(data->client, pmbus_cmd, पढ़ो_buf);
	अगर (ret < 0)
		वापस ret;

	pins_status = पढ़ो_buf[0] + (पढ़ो_buf[1] << 8);
	अगर (offset < ADM1266_GPIO_NR)
		वापस test_bit(adm1266_gpio_mapping[offset][1], &pins_status);

	वापस test_bit(offset - ADM1266_GPIO_NR, &pins_status);
पूर्ण

अटल पूर्णांक adm1266_gpio_get_multiple(काष्ठा gpio_chip *chip, अचिन्हित दीर्घ *mask,
				     अचिन्हित दीर्घ *bits)
अणु
	काष्ठा adm1266_data *data = gpiochip_get_data(chip);
	u8 पढ़ो_buf[ADM1266_PMBUS_BLOCK_MAX + 1];
	अचिन्हित दीर्घ status;
	अचिन्हित पूर्णांक gpio_nr;
	पूर्णांक ret;

	ret = i2c_smbus_पढ़ो_block_data(data->client, ADM1266_GPIO_STATUS, पढ़ो_buf);
	अगर (ret < 0)
		वापस ret;

	status = पढ़ो_buf[0] + (पढ़ो_buf[1] << 8);

	*bits = 0;
	क्रम_each_set_bit(gpio_nr, mask, ADM1266_GPIO_NR) अणु
		अगर (test_bit(adm1266_gpio_mapping[gpio_nr][1], &status))
			set_bit(gpio_nr, bits);
	पूर्ण

	ret = i2c_smbus_पढ़ो_block_data(data->client, ADM1266_PDIO_STATUS, पढ़ो_buf);
	अगर (ret < 0)
		वापस ret;

	status = पढ़ो_buf[0] + (पढ़ो_buf[1] << 8);

	*bits = 0;
	क्रम_each_set_bit_from(gpio_nr, mask, ADM1266_GPIO_NR + ADM1266_PDIO_STATUS) अणु
		अगर (test_bit(gpio_nr - ADM1266_GPIO_NR, &status))
			set_bit(gpio_nr, bits);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम adm1266_gpio_dbg_show(काष्ठा seq_file *s, काष्ठा gpio_chip *chip)
अणु
	काष्ठा adm1266_data *data = gpiochip_get_data(chip);
	u8 पढ़ो_buf[ADM1266_PMBUS_BLOCK_MAX + 1];
	अचिन्हित दीर्घ gpio_config;
	अचिन्हित दीर्घ pdio_config;
	अचिन्हित दीर्घ pin_cfg;
	u8 ग_लिखो_cmd;
	पूर्णांक ret;
	पूर्णांक i;

	क्रम (i = 0; i < ADM1266_GPIO_NR; i++) अणु
		ग_लिखो_cmd = adm1266_gpio_mapping[i][1];
		ret = adm1266_pmbus_block_xfer(data, ADM1266_GPIO_CONFIG, 1, &ग_लिखो_cmd, पढ़ो_buf);
		अगर (ret != 2)
			वापस;

		gpio_config = पढ़ो_buf[0];
		seq_माला_दो(s, adm1266_names[i]);

		seq_माला_दो(s, " ( ");
		अगर (!ADM1266_GPIO_FUNCTIONS(gpio_config)) अणु
			seq_माला_दो(s, "high-Z )\n");
			जारी;
		पूर्ण
		अगर (ADM1266_GPIO_INPUT_EN(gpio_config))
			seq_माला_दो(s, "input ");
		अगर (ADM1266_GPIO_OUTPUT_EN(gpio_config))
			seq_माला_दो(s, "output ");
		अगर (ADM1266_GPIO_OPEN_DRAIN(gpio_config))
			seq_माला_दो(s, "open-drain )\n");
		अन्यथा
			seq_माला_दो(s, "push-pull )\n");
	पूर्ण

	ग_लिखो_cmd = 0xFF;
	ret = adm1266_pmbus_block_xfer(data, ADM1266_PDIO_CONFIG, 1, &ग_लिखो_cmd, पढ़ो_buf);
	अगर (ret != 32)
		वापस;

	क्रम (i = 0; i < ADM1266_PDIO_NR; i++) अणु
		seq_माला_दो(s, adm1266_names[ADM1266_GPIO_NR + i]);

		pdio_config = पढ़ो_buf[2 * i];
		pdio_config += (पढ़ो_buf[2 * i + 1] << 8);
		pin_cfg = ADM1266_PDIO_PIN_CFG(pdio_config);

		seq_माला_दो(s, " ( ");
		अगर (!pin_cfg || pin_cfg > 5) अणु
			seq_माला_दो(s, "high-Z )\n");
			जारी;
		पूर्ण

		अगर (pin_cfg & BIT(0))
			seq_माला_दो(s, "output ");

		अगर (pin_cfg & BIT(1))
			seq_माला_दो(s, "input ");

		seq_माला_दो(s, ")\n");
	पूर्ण
पूर्ण

अटल पूर्णांक adm1266_config_gpio(काष्ठा adm1266_data *data)
अणु
	स्थिर अक्षर *name = dev_name(&data->client->dev);
	अक्षर *gpio_name;
	पूर्णांक ret;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(data->gpio_names); i++) अणु
		gpio_name = devm_kaप्र_लिखो(&data->client->dev, GFP_KERNEL, "adm1266-%x-%s",
					   data->client->addr, adm1266_names[i]);
		अगर (!gpio_name)
			वापस -ENOMEM;

		data->gpio_names[i] = gpio_name;
	पूर्ण

	data->gc.label = name;
	data->gc.parent = &data->client->dev;
	data->gc.owner = THIS_MODULE;
	data->gc.base = -1;
	data->gc.names = data->gpio_names;
	data->gc.ngpio = ARRAY_SIZE(data->gpio_names);
	data->gc.get = adm1266_gpio_get;
	data->gc.get_multiple = adm1266_gpio_get_multiple;
	data->gc.dbg_show = adm1266_gpio_dbg_show;

	ret = devm_gpiochip_add_data(&data->client->dev, &data->gc, data);
	अगर (ret)
		dev_err(&data->client->dev, "GPIO registering failed (%d)\n", ret);

	वापस ret;
पूर्ण

अटल पूर्णांक adm1266_state_पढ़ो(काष्ठा seq_file *s, व्योम *pdata)
अणु
	काष्ठा device *dev = s->निजी;
	काष्ठा i2c_client *client = to_i2c_client(dev);
	पूर्णांक ret;

	ret = i2c_smbus_पढ़ो_word_data(client, ADM1266_READ_STATE);
	अगर (ret < 0)
		वापस ret;

	seq_म_लिखो(s, "%d\n", ret);

	वापस 0;
पूर्ण

अटल व्योम adm1266_init_debugfs(काष्ठा adm1266_data *data)
अणु
	काष्ठा dentry *root;

	root = pmbus_get_debugfs_dir(data->client);
	अगर (!root)
		वापस;

	data->debugfs_dir = debugfs_create_dir(data->client->name, root);
	अगर (!data->debugfs_dir)
		वापस;

	debugfs_create_devm_seqfile(&data->client->dev, "sequencer_state", data->debugfs_dir,
				    adm1266_state_पढ़ो);
पूर्ण

अटल पूर्णांक adm1266_nvmem_पढ़ो_blackbox(काष्ठा adm1266_data *data, u8 *पढ़ो_buff)
अणु
	पूर्णांक record_count;
	अक्षर index;
	u8 buf[5];
	पूर्णांक ret;

	ret = i2c_smbus_पढ़ो_block_data(data->client, ADM1266_BLACKBOX_INFO, buf);
	अगर (ret < 0)
		वापस ret;

	अगर (ret != 4)
		वापस -EIO;

	record_count = buf[3];

	क्रम (index = 0; index < record_count; index++) अणु
		ret = adm1266_pmbus_block_xfer(data, ADM1266_READ_BLACKBOX, 1, &index, पढ़ो_buff);
		अगर (ret < 0)
			वापस ret;

		अगर (ret != ADM1266_BLACKBOX_SIZE)
			वापस -EIO;

		पढ़ो_buff += ADM1266_BLACKBOX_SIZE;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक adm1266_nvmem_पढ़ो(व्योम *priv, अचिन्हित पूर्णांक offset, व्योम *val, माप_प्रकार bytes)
अणु
	काष्ठा adm1266_data *data = priv;
	पूर्णांक ret;

	अगर (offset + bytes > data->nvmem_config.size)
		वापस -EINVAL;

	अगर (offset == 0) अणु
		स_रखो(data->dev_mem, 0, data->nvmem_config.size);

		ret = adm1266_nvmem_पढ़ो_blackbox(data, data->dev_mem);
		अगर (ret) अणु
			dev_err(&data->client->dev, "Could not read blackbox!");
			वापस ret;
		पूर्ण
	पूर्ण

	स_नकल(val, data->dev_mem + offset, bytes);

	वापस 0;
पूर्ण

अटल पूर्णांक adm1266_config_nvmem(काष्ठा adm1266_data *data)
अणु
	data->nvmem_config.name = dev_name(&data->client->dev);
	data->nvmem_config.dev = &data->client->dev;
	data->nvmem_config.root_only = true;
	data->nvmem_config.पढ़ो_only = true;
	data->nvmem_config.owner = THIS_MODULE;
	data->nvmem_config.reg_पढ़ो = adm1266_nvmem_पढ़ो;
	data->nvmem_config.cells = adm1266_nvmem_cells;
	data->nvmem_config.ncells = ARRAY_SIZE(adm1266_nvmem_cells);
	data->nvmem_config.priv = data;
	data->nvmem_config.stride = 1;
	data->nvmem_config.word_size = 1;
	data->nvmem_config.size = adm1266_nvmem_cells[0].bytes;

	data->dev_mem = devm_kzalloc(&data->client->dev, data->nvmem_config.size, GFP_KERNEL);
	अगर (!data->dev_mem)
		वापस -ENOMEM;

	data->nvmem = devm_nvmem_रेजिस्टर(&data->client->dev, &data->nvmem_config);
	अगर (IS_ERR(data->nvmem)) अणु
		dev_err(&data->client->dev, "Could not register nvmem!");
		वापस PTR_ERR(data->nvmem);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक adm1266_set_rtc(काष्ठा adm1266_data *data)
अणु
	समय64_t kt;
	अक्षर ग_लिखो_buf[6];
	पूर्णांक i;

	kt = kसमय_get_seconds();

	स_रखो(ग_लिखो_buf, 0, माप(ग_लिखो_buf));

	क्रम (i = 0; i < 4; i++)
		ग_लिखो_buf[2 + i] = (kt >> (i * 8)) & 0xFF;

	वापस i2c_smbus_ग_लिखो_block_data(data->client, ADM1266_SET_RTC, माप(ग_लिखो_buf),
					  ग_लिखो_buf);
पूर्ण

अटल पूर्णांक adm1266_probe(काष्ठा i2c_client *client)
अणु
	काष्ठा adm1266_data *data;
	पूर्णांक ret;
	पूर्णांक i;

	data = devm_kzalloc(&client->dev, माप(काष्ठा adm1266_data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	data->client = client;
	data->info.pages = 17;
	data->info.क्रमmat[PSC_VOLTAGE_OUT] = linear;
	क्रम (i = 0; i < data->info.pages; i++)
		data->info.func[i] = PMBUS_HAVE_VOUT | PMBUS_HAVE_STATUS_VOUT;

	crc8_populate_msb(pmbus_crc_table, 0x7);
	mutex_init(&data->buf_mutex);

	ret = adm1266_config_gpio(data);
	अगर (ret < 0)
		वापस ret;

	ret = adm1266_set_rtc(data);
	अगर (ret < 0)
		वापस ret;

	ret = adm1266_config_nvmem(data);
	अगर (ret < 0)
		वापस ret;

	ret = pmbus_करो_probe(client, &data->info);
	अगर (ret)
		वापस ret;

	adm1266_init_debugfs(data);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id adm1266_of_match[] = अणु
	अणु .compatible = "adi,adm1266" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, adm1266_of_match);

अटल स्थिर काष्ठा i2c_device_id adm1266_id[] = अणु
	अणु "adm1266", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, adm1266_id);

अटल काष्ठा i2c_driver adm1266_driver = अणु
	.driver = अणु
		   .name = "adm1266",
		   .of_match_table = adm1266_of_match,
		  पूर्ण,
	.probe_new = adm1266_probe,
	.id_table = adm1266_id,
पूर्ण;

module_i2c_driver(adm1266_driver);

MODULE_AUTHOR("Alexandru Tachici <alexandru.tachici@analog.com>");
MODULE_DESCRIPTION("PMBus driver for Analog Devices ADM1266");
MODULE_LICENSE("GPL v2");
MODULE_IMPORT_NS(PMBUS);
