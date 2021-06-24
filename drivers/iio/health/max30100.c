<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * max30100.c - Support क्रम MAX30100 heart rate and pulse oximeter sensor
 *
 * Copyright (C) 2015, 2018
 * Author: Matt Ranostay <matt.ranostay@konsulko.com>
 *
 * TODO: enable pulse length controls via device tree properties
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/delay.h>
#समावेश <linux/err.h>
#समावेश <linux/irq.h>
#समावेश <linux/i2c.h>
#समावेश <linux/mutex.h>
#समावेश <linux/property.h>
#समावेश <linux/regmap.h>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/buffer.h>
#समावेश <linux/iio/kfअगरo_buf.h>

#घोषणा MAX30100_REGMAP_NAME	"max30100_regmap"
#घोषणा MAX30100_DRV_NAME	"max30100"

#घोषणा MAX30100_REG_INT_STATUS			0x00
#घोषणा MAX30100_REG_INT_STATUS_PWR_RDY		BIT(0)
#घोषणा MAX30100_REG_INT_STATUS_SPO2_RDY	BIT(4)
#घोषणा MAX30100_REG_INT_STATUS_HR_RDY		BIT(5)
#घोषणा MAX30100_REG_INT_STATUS_FIFO_RDY	BIT(7)

#घोषणा MAX30100_REG_INT_ENABLE			0x01
#घोषणा MAX30100_REG_INT_ENABLE_SPO2_EN		BIT(0)
#घोषणा MAX30100_REG_INT_ENABLE_HR_EN		BIT(1)
#घोषणा MAX30100_REG_INT_ENABLE_FIFO_EN		BIT(3)
#घोषणा MAX30100_REG_INT_ENABLE_MASK		0xf0
#घोषणा MAX30100_REG_INT_ENABLE_MASK_SHIFT	4

#घोषणा MAX30100_REG_FIFO_WR_PTR		0x02
#घोषणा MAX30100_REG_FIFO_OVR_CTR		0x03
#घोषणा MAX30100_REG_FIFO_RD_PTR		0x04
#घोषणा MAX30100_REG_FIFO_DATA			0x05
#घोषणा MAX30100_REG_FIFO_DATA_ENTRY_COUNT	16
#घोषणा MAX30100_REG_FIFO_DATA_ENTRY_LEN	4

#घोषणा MAX30100_REG_MODE_CONFIG		0x06
#घोषणा MAX30100_REG_MODE_CONFIG_MODE_SPO2_EN	BIT(0)
#घोषणा MAX30100_REG_MODE_CONFIG_MODE_HR_EN	BIT(1)
#घोषणा MAX30100_REG_MODE_CONFIG_MODE_MASK	0x03
#घोषणा MAX30100_REG_MODE_CONFIG_TEMP_EN	BIT(3)
#घोषणा MAX30100_REG_MODE_CONFIG_PWR		BIT(7)

#घोषणा MAX30100_REG_SPO2_CONFIG		0x07
#घोषणा MAX30100_REG_SPO2_CONFIG_100HZ		BIT(2)
#घोषणा MAX30100_REG_SPO2_CONFIG_HI_RES_EN	BIT(6)
#घोषणा MAX30100_REG_SPO2_CONFIG_1600US		0x3

#घोषणा MAX30100_REG_LED_CONFIG			0x09
#घोषणा MAX30100_REG_LED_CONFIG_LED_MASK	0x0f
#घोषणा MAX30100_REG_LED_CONFIG_RED_LED_SHIFT	4

#घोषणा MAX30100_REG_LED_CONFIG_24MA		0x07
#घोषणा MAX30100_REG_LED_CONFIG_50MA		0x0f

#घोषणा MAX30100_REG_TEMP_INTEGER		0x16
#घोषणा MAX30100_REG_TEMP_FRACTION		0x17

काष्ठा max30100_data अणु
	काष्ठा i2c_client *client;
	काष्ठा iio_dev *indio_dev;
	काष्ठा mutex lock;
	काष्ठा regmap *regmap;

	__be16 buffer[2]; /* 2 16-bit channels */
पूर्ण;

अटल bool max30100_is_अस्थिर_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल MAX30100_REG_INT_STATUS:
	हाल MAX30100_REG_MODE_CONFIG:
	हाल MAX30100_REG_FIFO_WR_PTR:
	हाल MAX30100_REG_FIFO_OVR_CTR:
	हाल MAX30100_REG_FIFO_RD_PTR:
	हाल MAX30100_REG_FIFO_DATA:
	हाल MAX30100_REG_TEMP_INTEGER:
	हाल MAX30100_REG_TEMP_FRACTION:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा regmap_config max30100_regmap_config = अणु
	.name = MAX30100_REGMAP_NAME,

	.reg_bits = 8,
	.val_bits = 8,

	.max_रेजिस्टर = MAX30100_REG_TEMP_FRACTION,
	.cache_type = REGCACHE_FLAT,

	.अस्थिर_reg = max30100_is_अस्थिर_reg,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक max30100_led_current_mapping[] = अणु
	4400, 7600, 11000, 14200, 17400,
	20800, 24000, 27100, 30600, 33800,
	37000, 40200, 43600, 46800, 50000
पूर्ण;

अटल स्थिर अचिन्हित दीर्घ max30100_scan_masks[] = अणु0x3, 0पूर्ण;

अटल स्थिर काष्ठा iio_chan_spec max30100_channels[] = अणु
	अणु
		.type = IIO_INTENSITY,
		.channel2 = IIO_MOD_LIGHT_IR,
		.modअगरied = 1,

		.scan_index = 0,
		.scan_type = अणु
			.sign = 'u',
			.realbits = 16,
			.storagebits = 16,
			.endianness = IIO_BE,
		पूर्ण,
	पूर्ण,
	अणु
		.type = IIO_INTENSITY,
		.channel2 = IIO_MOD_LIGHT_RED,
		.modअगरied = 1,

		.scan_index = 1,
		.scan_type = अणु
			.sign = 'u',
			.realbits = 16,
			.storagebits = 16,
			.endianness = IIO_BE,
		पूर्ण,
	पूर्ण,
	अणु
		.type = IIO_TEMP,
		.info_mask_separate =
			BIT(IIO_CHAN_INFO_RAW) | BIT(IIO_CHAN_INFO_SCALE),
		.scan_index = -1,
	पूर्ण,
पूर्ण;

अटल पूर्णांक max30100_set_घातermode(काष्ठा max30100_data *data, bool state)
अणु
	वापस regmap_update_bits(data->regmap, MAX30100_REG_MODE_CONFIG,
				  MAX30100_REG_MODE_CONFIG_PWR,
				  state ? 0 : MAX30100_REG_MODE_CONFIG_PWR);
पूर्ण

अटल पूर्णांक max30100_clear_fअगरo(काष्ठा max30100_data *data)
अणु
	पूर्णांक ret;

	ret = regmap_ग_लिखो(data->regmap, MAX30100_REG_FIFO_WR_PTR, 0);
	अगर (ret)
		वापस ret;

	ret = regmap_ग_लिखो(data->regmap, MAX30100_REG_FIFO_OVR_CTR, 0);
	अगर (ret)
		वापस ret;

	वापस regmap_ग_लिखो(data->regmap, MAX30100_REG_FIFO_RD_PTR, 0);
पूर्ण

अटल पूर्णांक max30100_buffer_postenable(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा max30100_data *data = iio_priv(indio_dev);
	पूर्णांक ret;

	ret = max30100_set_घातermode(data, true);
	अगर (ret)
		वापस ret;

	वापस max30100_clear_fअगरo(data);
पूर्ण

अटल पूर्णांक max30100_buffer_predisable(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा max30100_data *data = iio_priv(indio_dev);

	वापस max30100_set_घातermode(data, false);
पूर्ण

अटल स्थिर काष्ठा iio_buffer_setup_ops max30100_buffer_setup_ops = अणु
	.postenable = max30100_buffer_postenable,
	.predisable = max30100_buffer_predisable,
पूर्ण;

अटल अंतरभूत पूर्णांक max30100_fअगरo_count(काष्ठा max30100_data *data)
अणु
	अचिन्हित पूर्णांक val;
	पूर्णांक ret;

	ret = regmap_पढ़ो(data->regmap, MAX30100_REG_INT_STATUS, &val);
	अगर (ret)
		वापस ret;

	/* FIFO is almost full */
	अगर (val & MAX30100_REG_INT_STATUS_FIFO_RDY)
		वापस MAX30100_REG_FIFO_DATA_ENTRY_COUNT - 1;

	वापस 0;
पूर्ण

अटल पूर्णांक max30100_पढ़ो_measurement(काष्ठा max30100_data *data)
अणु
	पूर्णांक ret;

	ret = i2c_smbus_पढ़ो_i2c_block_data(data->client,
					    MAX30100_REG_FIFO_DATA,
					    MAX30100_REG_FIFO_DATA_ENTRY_LEN,
					    (u8 *) &data->buffer);

	वापस (ret == MAX30100_REG_FIFO_DATA_ENTRY_LEN) ? 0 : ret;
पूर्ण

अटल irqवापस_t max30100_पूर्णांकerrupt_handler(पूर्णांक irq, व्योम *निजी)
अणु
	काष्ठा iio_dev *indio_dev = निजी;
	काष्ठा max30100_data *data = iio_priv(indio_dev);
	पूर्णांक ret, cnt = 0;

	mutex_lock(&data->lock);

	जबतक (cnt || (cnt = max30100_fअगरo_count(data)) > 0) अणु
		ret = max30100_पढ़ो_measurement(data);
		अगर (ret)
			अवरोध;

		iio_push_to_buffers(data->indio_dev, data->buffer);
		cnt--;
	पूर्ण

	mutex_unlock(&data->lock);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक max30100_get_current_idx(अचिन्हित पूर्णांक val, पूर्णांक *reg)
अणु
	पूर्णांक idx;

	/* LED turned off */
	अगर (val == 0) अणु
		*reg = 0;
		वापस 0;
	पूर्ण

	क्रम (idx = 0; idx < ARRAY_SIZE(max30100_led_current_mapping); idx++) अणु
		अगर (max30100_led_current_mapping[idx] == val) अणु
			*reg = idx + 1;
			वापस 0;
		पूर्ण
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक max30100_led_init(काष्ठा max30100_data *data)
अणु
	काष्ठा device *dev = &data->client->dev;
	अचिन्हित पूर्णांक val[2];
	पूर्णांक reg, ret;

	ret = device_property_पढ़ो_u32_array(dev, "maxim,led-current-microamp",
					(अचिन्हित पूर्णांक *) &val, 2);
	अगर (ret) अणु
		/* Default to 24 mA RED LED, 50 mA IR LED */
		reg = (MAX30100_REG_LED_CONFIG_24MA <<
			MAX30100_REG_LED_CONFIG_RED_LED_SHIFT) |
			MAX30100_REG_LED_CONFIG_50MA;
		dev_warn(dev, "no led-current-microamp set");

		वापस regmap_ग_लिखो(data->regmap, MAX30100_REG_LED_CONFIG, reg);
	पूर्ण

	/* RED LED current */
	ret = max30100_get_current_idx(val[0], &reg);
	अगर (ret) अणु
		dev_err(dev, "invalid RED current setting %d", val[0]);
		वापस ret;
	पूर्ण

	ret = regmap_update_bits(data->regmap, MAX30100_REG_LED_CONFIG,
		MAX30100_REG_LED_CONFIG_LED_MASK <<
		MAX30100_REG_LED_CONFIG_RED_LED_SHIFT,
		reg << MAX30100_REG_LED_CONFIG_RED_LED_SHIFT);
	अगर (ret)
		वापस ret;

	/* IR LED current */
	ret = max30100_get_current_idx(val[1], &reg);
	अगर (ret) अणु
		dev_err(dev, "invalid IR current setting %d", val[1]);
		वापस ret;
	पूर्ण

	वापस regmap_update_bits(data->regmap, MAX30100_REG_LED_CONFIG,
		MAX30100_REG_LED_CONFIG_LED_MASK, reg);
पूर्ण

अटल पूर्णांक max30100_chip_init(काष्ठा max30100_data *data)
अणु
	पूर्णांक ret;

	/* setup LED current settings */
	ret = max30100_led_init(data);
	अगर (ret)
		वापस ret;

	/* enable hi-res SPO2 पढ़ोings at 100Hz */
	ret = regmap_ग_लिखो(data->regmap, MAX30100_REG_SPO2_CONFIG,
				 MAX30100_REG_SPO2_CONFIG_HI_RES_EN |
				 MAX30100_REG_SPO2_CONFIG_100HZ);
	अगर (ret)
		वापस ret;

	/* enable SPO2 mode */
	ret = regmap_update_bits(data->regmap, MAX30100_REG_MODE_CONFIG,
				 MAX30100_REG_MODE_CONFIG_MODE_MASK,
				 MAX30100_REG_MODE_CONFIG_MODE_HR_EN |
				 MAX30100_REG_MODE_CONFIG_MODE_SPO2_EN);
	अगर (ret)
		वापस ret;

	/* enable FIFO पूर्णांकerrupt */
	वापस regmap_update_bits(data->regmap, MAX30100_REG_INT_ENABLE,
				 MAX30100_REG_INT_ENABLE_MASK,
				 MAX30100_REG_INT_ENABLE_FIFO_EN
				 << MAX30100_REG_INT_ENABLE_MASK_SHIFT);
पूर्ण

अटल पूर्णांक max30100_पढ़ो_temp(काष्ठा max30100_data *data, पूर्णांक *val)
अणु
	पूर्णांक ret;
	अचिन्हित पूर्णांक reg;

	ret = regmap_पढ़ो(data->regmap, MAX30100_REG_TEMP_INTEGER, &reg);
	अगर (ret < 0)
		वापस ret;
	*val = reg << 4;

	ret = regmap_पढ़ो(data->regmap, MAX30100_REG_TEMP_FRACTION, &reg);
	अगर (ret < 0)
		वापस ret;

	*val |= reg & 0xf;
	*val = sign_extend32(*val, 11);

	वापस 0;
पूर्ण

अटल पूर्णांक max30100_get_temp(काष्ठा max30100_data *data, पूर्णांक *val)
अणु
	पूर्णांक ret;

	/* start acquisition */
	ret = regmap_update_bits(data->regmap, MAX30100_REG_MODE_CONFIG,
				 MAX30100_REG_MODE_CONFIG_TEMP_EN,
				 MAX30100_REG_MODE_CONFIG_TEMP_EN);
	अगर (ret)
		वापस ret;

	msleep(35);

	वापस max30100_पढ़ो_temp(data, val);
पूर्ण

अटल पूर्णांक max30100_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			     काष्ठा iio_chan_spec स्थिर *chan,
			     पूर्णांक *val, पूर्णांक *val2, दीर्घ mask)
अणु
	काष्ठा max30100_data *data = iio_priv(indio_dev);
	पूर्णांक ret = -EINVAL;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		/*
		 * Temperature पढ़ोing can only be acquired जबतक engine
		 * is running
		 */
		mutex_lock(&indio_dev->mlock);

		अगर (!iio_buffer_enabled(indio_dev))
			ret = -EAGAIN;
		अन्यथा अणु
			ret = max30100_get_temp(data, val);
			अगर (!ret)
				ret = IIO_VAL_INT;

		पूर्ण

		mutex_unlock(&indio_dev->mlock);
		अवरोध;
	हाल IIO_CHAN_INFO_SCALE:
		*val = 1;  /* 0.0625 */
		*val2 = 16;
		ret = IIO_VAL_FRACTIONAL;
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा iio_info max30100_info = अणु
	.पढ़ो_raw = max30100_पढ़ो_raw,
पूर्ण;

अटल पूर्णांक max30100_probe(काष्ठा i2c_client *client,
			  स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा max30100_data *data;
	काष्ठा iio_dev *indio_dev;
	पूर्णांक ret;

	indio_dev = devm_iio_device_alloc(&client->dev, माप(*data));
	अगर (!indio_dev)
		वापस -ENOMEM;

	indio_dev->name = MAX30100_DRV_NAME;
	indio_dev->channels = max30100_channels;
	indio_dev->info = &max30100_info;
	indio_dev->num_channels = ARRAY_SIZE(max30100_channels);
	indio_dev->available_scan_masks = max30100_scan_masks;
	indio_dev->modes = INDIO_सूचीECT_MODE;

	ret = devm_iio_kfअगरo_buffer_setup(&client->dev, indio_dev,
					  INDIO_BUFFER_SOFTWARE,
					  &max30100_buffer_setup_ops);
	अगर (ret)
		वापस ret;

	data = iio_priv(indio_dev);
	data->indio_dev = indio_dev;
	data->client = client;

	mutex_init(&data->lock);
	i2c_set_clientdata(client, indio_dev);

	data->regmap = devm_regmap_init_i2c(client, &max30100_regmap_config);
	अगर (IS_ERR(data->regmap)) अणु
		dev_err(&client->dev, "regmap initialization failed.\n");
		वापस PTR_ERR(data->regmap);
	पूर्ण
	max30100_set_घातermode(data, false);

	ret = max30100_chip_init(data);
	अगर (ret)
		वापस ret;

	अगर (client->irq <= 0) अणु
		dev_err(&client->dev, "no valid irq defined\n");
		वापस -EINVAL;
	पूर्ण
	ret = devm_request_thपढ़ोed_irq(&client->dev, client->irq,
					शून्य, max30100_पूर्णांकerrupt_handler,
					IRQF_TRIGGER_FALLING | IRQF_ONESHOT,
					"max30100_irq", indio_dev);
	अगर (ret) अणु
		dev_err(&client->dev, "request irq (%d) failed\n", client->irq);
		वापस ret;
	पूर्ण

	वापस iio_device_रेजिस्टर(indio_dev);
पूर्ण

अटल पूर्णांक max30100_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा iio_dev *indio_dev = i2c_get_clientdata(client);
	काष्ठा max30100_data *data = iio_priv(indio_dev);

	iio_device_unरेजिस्टर(indio_dev);
	max30100_set_घातermode(data, false);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id max30100_id[] = अणु
	अणु "max30100", 0 पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, max30100_id);

अटल स्थिर काष्ठा of_device_id max30100_dt_ids[] = अणु
	अणु .compatible = "maxim,max30100" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, max30100_dt_ids);

अटल काष्ठा i2c_driver max30100_driver = अणु
	.driver = अणु
		.name	= MAX30100_DRV_NAME,
		.of_match_table	= max30100_dt_ids,
	पूर्ण,
	.probe		= max30100_probe,
	.हटाओ		= max30100_हटाओ,
	.id_table	= max30100_id,
पूर्ण;
module_i2c_driver(max30100_driver);

MODULE_AUTHOR("Matt Ranostay <matt.ranostay@konsulko.com>");
MODULE_DESCRIPTION("MAX30100 heart rate and pulse oximeter sensor");
MODULE_LICENSE("GPL");
