<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * JSA1212 Ambient Light & Proximity Sensor Driver
 *
 * Copyright (c) 2014, Intel Corporation.
 *
 * JSA1212 I2C slave address: 0x44(ADDR tied to GND), 0x45(ADDR tied to VDD)
 *
 * TODO: Interrupt support, thresholds, range support.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/delay.h>
#समावेश <linux/i2c.h>
#समावेश <linux/mutex.h>
#समावेश <linux/acpi.h>
#समावेश <linux/regmap.h>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/sysfs.h>

/* JSA1212 reg address */
#घोषणा JSA1212_CONF_REG		0x01
#घोषणा JSA1212_INT_REG			0x02
#घोषणा JSA1212_PXS_LT_REG		0x03
#घोषणा JSA1212_PXS_HT_REG		0x04
#घोषणा JSA1212_ALS_TH1_REG		0x05
#घोषणा JSA1212_ALS_TH2_REG		0x06
#घोषणा JSA1212_ALS_TH3_REG		0x07
#घोषणा JSA1212_PXS_DATA_REG		0x08
#घोषणा JSA1212_ALS_DT1_REG		0x09
#घोषणा JSA1212_ALS_DT2_REG		0x0A
#घोषणा JSA1212_ALS_RNG_REG		0x0B
#घोषणा JSA1212_MAX_REG			0x0C

/* JSA1212 reg masks */
#घोषणा JSA1212_CONF_MASK		0xFF
#घोषणा JSA1212_INT_MASK		0xFF
#घोषणा JSA1212_PXS_LT_MASK		0xFF
#घोषणा JSA1212_PXS_HT_MASK		0xFF
#घोषणा JSA1212_ALS_TH1_MASK		0xFF
#घोषणा JSA1212_ALS_TH2_LT_MASK		0x0F
#घोषणा JSA1212_ALS_TH2_HT_MASK		0xF0
#घोषणा JSA1212_ALS_TH3_MASK		0xFF
#घोषणा JSA1212_PXS_DATA_MASK		0xFF
#घोषणा JSA1212_ALS_DATA_MASK		0x0FFF
#घोषणा JSA1212_ALS_DT1_MASK		0xFF
#घोषणा JSA1212_ALS_DT2_MASK		0x0F
#घोषणा JSA1212_ALS_RNG_MASK		0x07

/* JSA1212 CONF REG bits */
#घोषणा JSA1212_CONF_PXS_MASK		0x80
#घोषणा JSA1212_CONF_PXS_ENABLE		0x80
#घोषणा JSA1212_CONF_PXS_DISABLE	0x00
#घोषणा JSA1212_CONF_ALS_MASK		0x04
#घोषणा JSA1212_CONF_ALS_ENABLE		0x04
#घोषणा JSA1212_CONF_ALS_DISABLE	0x00
#घोषणा JSA1212_CONF_IRDR_MASK		0x08
/* Proxmity sensing IRDR current sink settings */
#घोषणा JSA1212_CONF_IRDR_200MA		0x08
#घोषणा JSA1212_CONF_IRDR_100MA		0x00
#घोषणा JSA1212_CONF_PXS_SLP_MASK	0x70
#घोषणा JSA1212_CONF_PXS_SLP_0MS	0x70
#घोषणा JSA1212_CONF_PXS_SLP_12MS	0x60
#घोषणा JSA1212_CONF_PXS_SLP_50MS	0x50
#घोषणा JSA1212_CONF_PXS_SLP_75MS	0x40
#घोषणा JSA1212_CONF_PXS_SLP_100MS	0x30
#घोषणा JSA1212_CONF_PXS_SLP_200MS	0x20
#घोषणा JSA1212_CONF_PXS_SLP_400MS	0x10
#घोषणा JSA1212_CONF_PXS_SLP_800MS	0x00

/* JSA1212 INT REG bits */
#घोषणा JSA1212_INT_CTRL_MASK		0x01
#घोषणा JSA1212_INT_CTRL_EITHER		0x00
#घोषणा JSA1212_INT_CTRL_BOTH		0x01
#घोषणा JSA1212_INT_ALS_PRST_MASK	0x06
#घोषणा JSA1212_INT_ALS_PRST_1CONV	0x00
#घोषणा JSA1212_INT_ALS_PRST_4CONV	0x02
#घोषणा JSA1212_INT_ALS_PRST_8CONV	0x04
#घोषणा JSA1212_INT_ALS_PRST_16CONV	0x06
#घोषणा JSA1212_INT_ALS_FLAG_MASK	0x08
#घोषणा JSA1212_INT_ALS_FLAG_CLR	0x00
#घोषणा JSA1212_INT_PXS_PRST_MASK	0x60
#घोषणा JSA1212_INT_PXS_PRST_1CONV	0x00
#घोषणा JSA1212_INT_PXS_PRST_4CONV	0x20
#घोषणा JSA1212_INT_PXS_PRST_8CONV	0x40
#घोषणा JSA1212_INT_PXS_PRST_16CONV	0x60
#घोषणा JSA1212_INT_PXS_FLAG_MASK	0x80
#घोषणा JSA1212_INT_PXS_FLAG_CLR	0x00

/* JSA1212 ALS RNG REG bits */
#घोषणा JSA1212_ALS_RNG_0_2048		0x00
#घोषणा JSA1212_ALS_RNG_0_1024		0x01
#घोषणा JSA1212_ALS_RNG_0_512		0x02
#घोषणा JSA1212_ALS_RNG_0_256		0x03
#घोषणा JSA1212_ALS_RNG_0_128		0x04

/* JSA1212 INT threshold range */
#घोषणा JSA1212_ALS_TH_MIN	0x0000
#घोषणा JSA1212_ALS_TH_MAX	0x0FFF
#घोषणा JSA1212_PXS_TH_MIN	0x00
#घोषणा JSA1212_PXS_TH_MAX	0xFF

#घोषणा JSA1212_ALS_DELAY_MS	200
#घोषणा JSA1212_PXS_DELAY_MS	100

#घोषणा JSA1212_DRIVER_NAME	"jsa1212"
#घोषणा JSA1212_REGMAP_NAME	"jsa1212_regmap"

क्रमागत jsa1212_op_mode अणु
	JSA1212_OPMODE_ALS_EN,
	JSA1212_OPMODE_PXS_EN,
पूर्ण;

काष्ठा jsa1212_data अणु
	काष्ठा i2c_client *client;
	काष्ठा mutex lock;
	u8 als_rng_idx;
	bool als_en; /* ALS enable status */
	bool pxs_en; /* proximity enable status */
	काष्ठा regmap *regmap;
पूर्ण;

/* ALS range idx to val mapping */
अटल स्थिर पूर्णांक jsa1212_als_range_val[] = अणु2048, 1024, 512, 256, 128,
						128, 128, 128पूर्ण;

/* Enables or disables ALS function based on status */
अटल पूर्णांक jsa1212_als_enable(काष्ठा jsa1212_data *data, u8 status)
अणु
	पूर्णांक ret;

	ret = regmap_update_bits(data->regmap, JSA1212_CONF_REG,
				JSA1212_CONF_ALS_MASK,
				status);
	अगर (ret < 0)
		वापस ret;

	data->als_en = !!status;

	वापस 0;
पूर्ण

/* Enables or disables PXS function based on status */
अटल पूर्णांक jsa1212_pxs_enable(काष्ठा jsa1212_data *data, u8 status)
अणु
	पूर्णांक ret;

	ret = regmap_update_bits(data->regmap, JSA1212_CONF_REG,
				JSA1212_CONF_PXS_MASK,
				status);
	अगर (ret < 0)
		वापस ret;

	data->pxs_en = !!status;

	वापस 0;
पूर्ण

अटल पूर्णांक jsa1212_पढ़ो_als_data(काष्ठा jsa1212_data *data,
				अचिन्हित पूर्णांक *val)
अणु
	पूर्णांक ret;
	__le16 als_data;

	ret = jsa1212_als_enable(data, JSA1212_CONF_ALS_ENABLE);
	अगर (ret < 0)
		वापस ret;

	/* Delay क्रम data output */
	msleep(JSA1212_ALS_DELAY_MS);

	/* Read 12 bit data */
	ret = regmap_bulk_पढ़ो(data->regmap, JSA1212_ALS_DT1_REG, &als_data, 2);
	अगर (ret < 0) अणु
		dev_err(&data->client->dev, "als data read err\n");
		जाओ als_data_पढ़ो_err;
	पूर्ण

	*val = le16_to_cpu(als_data);

als_data_पढ़ो_err:
	वापस jsa1212_als_enable(data, JSA1212_CONF_ALS_DISABLE);
पूर्ण

अटल पूर्णांक jsa1212_पढ़ो_pxs_data(काष्ठा jsa1212_data *data,
				अचिन्हित पूर्णांक *val)
अणु
	पूर्णांक ret;
	अचिन्हित पूर्णांक pxs_data;

	ret = jsa1212_pxs_enable(data, JSA1212_CONF_PXS_ENABLE);
	अगर (ret < 0)
		वापस ret;

	/* Delay क्रम data output */
	msleep(JSA1212_PXS_DELAY_MS);

	/* Read out all data */
	ret = regmap_पढ़ो(data->regmap, JSA1212_PXS_DATA_REG, &pxs_data);
	अगर (ret < 0) अणु
		dev_err(&data->client->dev, "pxs data read err\n");
		जाओ pxs_data_पढ़ो_err;
	पूर्ण

	*val = pxs_data & JSA1212_PXS_DATA_MASK;

pxs_data_पढ़ो_err:
	वापस jsa1212_pxs_enable(data, JSA1212_CONF_PXS_DISABLE);
पूर्ण

अटल पूर्णांक jsa1212_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
				काष्ठा iio_chan_spec स्थिर *chan,
				पूर्णांक *val, पूर्णांक *val2, दीर्घ mask)
अणु
	पूर्णांक ret;
	काष्ठा jsa1212_data *data = iio_priv(indio_dev);

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		mutex_lock(&data->lock);
		चयन (chan->type) अणु
		हाल IIO_LIGHT:
			ret = jsa1212_पढ़ो_als_data(data, val);
			अवरोध;
		हाल IIO_PROXIMITY:
			ret = jsa1212_पढ़ो_pxs_data(data, val);
			अवरोध;
		शेष:
			ret = -EINVAL;
			अवरोध;
		पूर्ण
		mutex_unlock(&data->lock);
		वापस ret < 0 ? ret : IIO_VAL_INT;
	हाल IIO_CHAN_INFO_SCALE:
		चयन (chan->type) अणु
		हाल IIO_LIGHT:
			*val = jsa1212_als_range_val[data->als_rng_idx];
			*val2 = BIT(12); /* Max 12 bit value */
			वापस IIO_VAL_FRACTIONAL;
		शेष:
			अवरोध;
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल स्थिर काष्ठा iio_chan_spec jsa1212_channels[] = अणु
	अणु
		.type = IIO_LIGHT,
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW) |
			BIT(IIO_CHAN_INFO_SCALE),
	पूर्ण,
	अणु
		.type = IIO_PROXIMITY,
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW),
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा iio_info jsa1212_info = अणु
	.पढ़ो_raw		= &jsa1212_पढ़ो_raw,
पूर्ण;

अटल पूर्णांक jsa1212_chip_init(काष्ठा jsa1212_data *data)
अणु
	पूर्णांक ret;

	ret = regmap_ग_लिखो(data->regmap, JSA1212_CONF_REG,
				(JSA1212_CONF_PXS_SLP_50MS |
				JSA1212_CONF_IRDR_200MA));
	अगर (ret < 0)
		वापस ret;

	ret = regmap_ग_लिखो(data->regmap, JSA1212_INT_REG,
				JSA1212_INT_ALS_PRST_4CONV);
	अगर (ret < 0)
		वापस ret;

	data->als_rng_idx = JSA1212_ALS_RNG_0_2048;

	वापस 0;
पूर्ण

अटल bool jsa1212_is_अस्थिर_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल JSA1212_PXS_DATA_REG:
	हाल JSA1212_ALS_DT1_REG:
	हाल JSA1212_ALS_DT2_REG:
	हाल JSA1212_INT_REG:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा regmap_config jsa1212_regmap_config = अणु
	.name =  JSA1212_REGMAP_NAME,
	.reg_bits = 8,
	.val_bits = 8,
	.max_रेजिस्टर = JSA1212_MAX_REG,
	.cache_type = REGCACHE_RBTREE,
	.अस्थिर_reg = jsa1212_is_अस्थिर_reg,
पूर्ण;

अटल पूर्णांक jsa1212_probe(काष्ठा i2c_client *client,
			 स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा jsa1212_data *data;
	काष्ठा iio_dev *indio_dev;
	काष्ठा regmap *regmap;
	पूर्णांक ret;

	indio_dev = devm_iio_device_alloc(&client->dev, माप(*data));
	अगर (!indio_dev)
		वापस -ENOMEM;

	regmap = devm_regmap_init_i2c(client, &jsa1212_regmap_config);
	अगर (IS_ERR(regmap)) अणु
		dev_err(&client->dev, "Regmap initialization failed.\n");
		वापस PTR_ERR(regmap);
	पूर्ण

	data = iio_priv(indio_dev);

	i2c_set_clientdata(client, indio_dev);
	data->client = client;
	data->regmap = regmap;

	mutex_init(&data->lock);

	ret = jsa1212_chip_init(data);
	अगर (ret < 0)
		वापस ret;

	indio_dev->channels = jsa1212_channels;
	indio_dev->num_channels = ARRAY_SIZE(jsa1212_channels);
	indio_dev->name = JSA1212_DRIVER_NAME;
	indio_dev->modes = INDIO_सूचीECT_MODE;

	indio_dev->info = &jsa1212_info;

	ret = iio_device_रेजिस्टर(indio_dev);
	अगर (ret < 0)
		dev_err(&client->dev, "%s: register device failed\n", __func__);

	वापस ret;
पूर्ण

 /* घातer off the device */
अटल पूर्णांक jsa1212_घातer_off(काष्ठा jsa1212_data *data)
अणु
	पूर्णांक ret;

	mutex_lock(&data->lock);

	ret = regmap_update_bits(data->regmap, JSA1212_CONF_REG,
				JSA1212_CONF_ALS_MASK |
				JSA1212_CONF_PXS_MASK,
				JSA1212_CONF_ALS_DISABLE |
				JSA1212_CONF_PXS_DISABLE);

	अगर (ret < 0)
		dev_err(&data->client->dev, "power off cmd failed\n");

	mutex_unlock(&data->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक jsa1212_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा iio_dev *indio_dev = i2c_get_clientdata(client);
	काष्ठा jsa1212_data *data = iio_priv(indio_dev);

	iio_device_unरेजिस्टर(indio_dev);

	वापस jsa1212_घातer_off(data);
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक jsa1212_suspend(काष्ठा device *dev)
अणु
	काष्ठा jsa1212_data *data;

	data = iio_priv(i2c_get_clientdata(to_i2c_client(dev)));

	वापस jsa1212_घातer_off(data);
पूर्ण

अटल पूर्णांक jsa1212_resume(काष्ठा device *dev)
अणु
	पूर्णांक ret = 0;
	काष्ठा jsa1212_data *data;

	data = iio_priv(i2c_get_clientdata(to_i2c_client(dev)));

	mutex_lock(&data->lock);

	अगर (data->als_en) अणु
		ret = jsa1212_als_enable(data, JSA1212_CONF_ALS_ENABLE);
		अगर (ret < 0) अणु
			dev_err(dev, "als resume failed\n");
			जाओ unlock_and_ret;
		पूर्ण
	पूर्ण

	अगर (data->pxs_en) अणु
		ret = jsa1212_pxs_enable(data, JSA1212_CONF_PXS_ENABLE);
		अगर (ret < 0)
			dev_err(dev, "pxs resume failed\n");
	पूर्ण

unlock_and_ret:
	mutex_unlock(&data->lock);
	वापस ret;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(jsa1212_pm_ops, jsa1212_suspend, jsa1212_resume);

#घोषणा JSA1212_PM_OPS (&jsa1212_pm_ops)
#अन्यथा
#घोषणा JSA1212_PM_OPS शून्य
#पूर्ण_अगर

अटल स्थिर काष्ठा acpi_device_id jsa1212_acpi_match[] = अणु
	अणु"JSA1212", 0पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(acpi, jsa1212_acpi_match);

अटल स्थिर काष्ठा i2c_device_id jsa1212_id[] = अणु
	अणु JSA1212_DRIVER_NAME, 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, jsa1212_id);

अटल काष्ठा i2c_driver jsa1212_driver = अणु
	.driver = अणु
		.name	= JSA1212_DRIVER_NAME,
		.pm	= JSA1212_PM_OPS,
		.acpi_match_table = ACPI_PTR(jsa1212_acpi_match),
	पूर्ण,
	.probe		= jsa1212_probe,
	.हटाओ		= jsa1212_हटाओ,
	.id_table	= jsa1212_id,
पूर्ण;
module_i2c_driver(jsa1212_driver);

MODULE_AUTHOR("Sathya Kuppuswamy <sathyanarayanan.kuppuswamy@linux.intel.com>");
MODULE_DESCRIPTION("JSA1212 proximity/ambient light sensor driver");
MODULE_LICENSE("GPL v2");
