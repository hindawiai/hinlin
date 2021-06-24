<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * MXC6255 - MEMSIC orientation sensing accelerometer
 *
 * Copyright (c) 2015, Intel Corporation.
 *
 * IIO driver क्रम MXC6255 (7-bit I2C slave address 0x15).
 */

#समावेश <linux/module.h>
#समावेश <linux/i2c.h>
#समावेश <linux/init.h>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/delay.h>
#समावेश <linux/acpi.h>
#समावेश <linux/regmap.h>
#समावेश <linux/iio/sysfs.h>

#घोषणा MXC6255_DRV_NAME		"mxc6255"
#घोषणा MXC6255_REGMAP_NAME		"mxc6255_regmap"

#घोषणा MXC6255_REG_XOUT		0x00
#घोषणा MXC6255_REG_YOUT		0x01
#घोषणा MXC6255_REG_CHIP_ID		0x08

#घोषणा MXC6255_CHIP_ID			0x05

/*
 * MXC6255 has only one measurement range: +/- 2G.
 * The acceleration output is an 8-bit value.
 *
 * Scale is calculated as follows:
 * (2 + 2) * 9.80665 / (2^8 - 1) = 0.153829
 *
 * Scale value क्रम +/- 2G measurement range
 */
#घोषणा MXC6255_SCALE			153829

क्रमागत mxc6255_axis अणु
	AXIS_X,
	AXIS_Y,
पूर्ण;

काष्ठा mxc6255_data अणु
	काष्ठा i2c_client *client;
	काष्ठा regmap *regmap;
पूर्ण;

अटल पूर्णांक mxc6255_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			    काष्ठा iio_chan_spec स्थिर *chan,
			    पूर्णांक *val, पूर्णांक *val2, दीर्घ mask)
अणु
	काष्ठा mxc6255_data *data = iio_priv(indio_dev);
	अचिन्हित पूर्णांक reg;
	पूर्णांक ret;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		ret = regmap_पढ़ो(data->regmap, chan->address, &reg);
		अगर (ret < 0) अणु
			dev_err(&data->client->dev,
				"Error reading reg %lu\n", chan->address);
			वापस ret;
		पूर्ण

		*val = sign_extend32(reg, 7);
		वापस IIO_VAL_INT;
	हाल IIO_CHAN_INFO_SCALE:
		*val = 0;
		*val2 = MXC6255_SCALE;
		वापस IIO_VAL_INT_PLUS_MICRO;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा iio_info mxc6255_info = अणु
	.पढ़ो_raw	= mxc6255_पढ़ो_raw,
पूर्ण;

#घोषणा MXC6255_CHANNEL(_axis, reg) अणु				\
	.type = IIO_ACCEL,					\
	.modअगरied = 1,						\
	.channel2 = IIO_MOD_##_axis,				\
	.address = reg,						\
	.info_mask_separate = BIT(IIO_CHAN_INFO_RAW),		\
	.info_mask_shared_by_type = BIT(IIO_CHAN_INFO_SCALE),	\
पूर्ण

अटल स्थिर काष्ठा iio_chan_spec mxc6255_channels[] = अणु
	MXC6255_CHANNEL(X, MXC6255_REG_XOUT),
	MXC6255_CHANNEL(Y, MXC6255_REG_YOUT),
पूर्ण;

अटल bool mxc6255_is_पढ़ोable_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल MXC6255_REG_XOUT:
	हाल MXC6255_REG_YOUT:
	हाल MXC6255_REG_CHIP_ID:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा regmap_config mxc6255_regmap_config = अणु
	.name = MXC6255_REGMAP_NAME,

	.reg_bits = 8,
	.val_bits = 8,

	.पढ़ोable_reg = mxc6255_is_पढ़ोable_reg,
पूर्ण;

अटल पूर्णांक mxc6255_probe(काष्ठा i2c_client *client,
			 स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा mxc6255_data *data;
	काष्ठा iio_dev *indio_dev;
	काष्ठा regmap *regmap;
	अचिन्हित पूर्णांक chip_id;
	पूर्णांक ret;

	indio_dev = devm_iio_device_alloc(&client->dev, माप(*data));
	अगर (!indio_dev)
		वापस -ENOMEM;

	regmap = devm_regmap_init_i2c(client, &mxc6255_regmap_config);
	अगर (IS_ERR(regmap)) अणु
		dev_err(&client->dev, "Error initializing regmap\n");
		वापस PTR_ERR(regmap);
	पूर्ण

	data = iio_priv(indio_dev);
	i2c_set_clientdata(client, indio_dev);
	data->client = client;
	data->regmap = regmap;

	indio_dev->name = MXC6255_DRV_NAME;
	indio_dev->channels = mxc6255_channels;
	indio_dev->num_channels = ARRAY_SIZE(mxc6255_channels);
	indio_dev->modes = INDIO_सूचीECT_MODE;
	indio_dev->info = &mxc6255_info;

	ret = regmap_पढ़ो(data->regmap, MXC6255_REG_CHIP_ID, &chip_id);
	अगर (ret < 0) अणु
		dev_err(&client->dev, "Error reading chip id %d\n", ret);
		वापस ret;
	पूर्ण

	अगर ((chip_id & 0x1f) != MXC6255_CHIP_ID) अणु
		dev_err(&client->dev, "Invalid chip id %x\n", chip_id);
		वापस -ENODEV;
	पूर्ण

	dev_dbg(&client->dev, "Chip id %x\n", chip_id);

	ret = devm_iio_device_रेजिस्टर(&client->dev, indio_dev);
	अगर (ret < 0) अणु
		dev_err(&client->dev, "Could not register IIO device\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा acpi_device_id mxc6255_acpi_match[] = अणु
	अणु"MXC6225",	0पूर्ण,
	अणु"MXC6255",	0पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(acpi, mxc6255_acpi_match);

अटल स्थिर काष्ठा i2c_device_id mxc6255_id[] = अणु
	अणु"mxc6225",	0पूर्ण,
	अणु"mxc6255",	0पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, mxc6255_id);

अटल काष्ठा i2c_driver mxc6255_driver = अणु
	.driver = अणु
		.name = MXC6255_DRV_NAME,
		.acpi_match_table = ACPI_PTR(mxc6255_acpi_match),
	पूर्ण,
	.probe		= mxc6255_probe,
	.id_table	= mxc6255_id,
पूर्ण;

module_i2c_driver(mxc6255_driver);

MODULE_AUTHOR("Teodora Baluta <teodora.baluta@intel.com>");
MODULE_DESCRIPTION("MEMSIC MXC6255 orientation sensing accelerometer driver");
MODULE_LICENSE("GPL v2");
