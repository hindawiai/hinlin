<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * IIO driver क्रम the 3-axis accelerometer Domपूर्णांकech DMARD09.
 *
 * Copyright (c) 2016, Jelle van der Waa <jelle@vdwaa.nl>
 */

#समावेश <यंत्र/unaligned.h>
#समावेश <linux/module.h>
#समावेश <linux/i2c.h>
#समावेश <linux/iio/iपन.स>

#घोषणा DMARD09_DRV_NAME	"dmard09"

#घोषणा DMARD09_REG_CHIPID      0x18
#घोषणा DMARD09_REG_STAT	0x0A
#घोषणा DMARD09_REG_X		0x0C
#घोषणा DMARD09_REG_Y		0x0E
#घोषणा DMARD09_REG_Z		0x10
#घोषणा DMARD09_CHIPID		0x95

#घोषणा DMARD09_BUF_LEN 8
#घोषणा DMARD09_AXIS_X 0
#घोषणा DMARD09_AXIS_Y 1
#घोषणा DMARD09_AXIS_Z 2
#घोषणा DMARD09_AXIS_X_OFFSET ((DMARD09_AXIS_X + 1) * 2)
#घोषणा DMARD09_AXIS_Y_OFFSET ((DMARD09_AXIS_Y + 1 )* 2)
#घोषणा DMARD09_AXIS_Z_OFFSET ((DMARD09_AXIS_Z + 1) * 2)

काष्ठा dmard09_data अणु
	काष्ठा i2c_client *client;
पूर्ण;

#घोषणा DMARD09_CHANNEL(_axis, offset) अणु			\
	.type = IIO_ACCEL,					\
	.info_mask_separate = BIT(IIO_CHAN_INFO_RAW),		\
	.info_mask_shared_by_type = BIT(IIO_CHAN_INFO_SCALE),	\
	.modअगरied = 1,						\
	.address = offset,					\
	.channel2 = IIO_MOD_##_axis,				\
पूर्ण

अटल स्थिर काष्ठा iio_chan_spec dmard09_channels[] = अणु
	DMARD09_CHANNEL(X, DMARD09_AXIS_X_OFFSET),
	DMARD09_CHANNEL(Y, DMARD09_AXIS_Y_OFFSET),
	DMARD09_CHANNEL(Z, DMARD09_AXIS_Z_OFFSET),
पूर्ण;

अटल पूर्णांक dmard09_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			    काष्ठा iio_chan_spec स्थिर *chan,
			    पूर्णांक *val, पूर्णांक *val2, दीर्घ mask)
अणु
	काष्ठा dmard09_data *data = iio_priv(indio_dev);
	u8 buf[DMARD09_BUF_LEN];
	पूर्णांक ret;
	s16 accel;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		/*
		 * Read from the DMAR09_REG_STAT रेजिस्टर, since the chip
		 * caches पढ़ोs from the inभागidual X, Y, Z रेजिस्टरs.
		 */
		ret = i2c_smbus_पढ़ो_i2c_block_data(data->client,
						    DMARD09_REG_STAT,
						    DMARD09_BUF_LEN, buf);
		अगर (ret < 0) अणु
			dev_err(&data->client->dev, "Error reading reg %d\n",
				DMARD09_REG_STAT);
			वापस ret;
		पूर्ण

		accel = get_unaligned_le16(&buf[chan->address]);

		/* Remove lower 3 bits and sign extend */
		accel <<= 4;
		accel >>= 7;

		*val = accel;

		वापस IIO_VAL_INT;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा iio_info dmard09_info = अणु
	.पढ़ो_raw	= dmard09_पढ़ो_raw,
पूर्ण;

अटल पूर्णांक dmard09_probe(काष्ठा i2c_client *client,
			स्थिर काष्ठा i2c_device_id *id)
अणु
	पूर्णांक ret;
	काष्ठा iio_dev *indio_dev;
	काष्ठा dmard09_data *data;

	indio_dev = devm_iio_device_alloc(&client->dev, माप(*data));
	अगर (!indio_dev) अणु
		dev_err(&client->dev, "iio allocation failed\n");
		वापस -ENOMEM;
	पूर्ण

	data = iio_priv(indio_dev);
	data->client = client;

	ret = i2c_smbus_पढ़ो_byte_data(data->client, DMARD09_REG_CHIPID);
	अगर (ret < 0) अणु
		dev_err(&client->dev, "Error reading chip id %d\n", ret);
		वापस ret;
	पूर्ण

	अगर (ret != DMARD09_CHIPID) अणु
		dev_err(&client->dev, "Invalid chip id %d\n", ret);
		वापस -ENODEV;
	पूर्ण

	i2c_set_clientdata(client, indio_dev);
	indio_dev->name = DMARD09_DRV_NAME;
	indio_dev->modes = INDIO_सूचीECT_MODE;
	indio_dev->channels = dmard09_channels;
	indio_dev->num_channels = ARRAY_SIZE(dmard09_channels);
	indio_dev->info = &dmard09_info;

	वापस devm_iio_device_रेजिस्टर(&client->dev, indio_dev);
पूर्ण

अटल स्थिर काष्ठा i2c_device_id dmard09_id[] = अणु
	अणु "dmard09", 0पूर्ण,
	अणु पूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(i2c, dmard09_id);

अटल काष्ठा i2c_driver dmard09_driver = अणु
	.driver = अणु
		.name = DMARD09_DRV_NAME
	पूर्ण,
	.probe = dmard09_probe,
	.id_table = dmard09_id,
पूर्ण;

module_i2c_driver(dmard09_driver);

MODULE_AUTHOR("Jelle van der Waa <jelle@vdwaa.nl>");
MODULE_DESCRIPTION("DMARD09 3-axis accelerometer driver");
MODULE_LICENSE("GPL");
