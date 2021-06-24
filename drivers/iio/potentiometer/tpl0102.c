<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * tpl0102.c - Support क्रम Texas Instruments digital potentiometers
 *
 * Copyright (C) 2016, 2018
 * Author: Matt Ranostay <matt.ranostay@konsulko.com>
 *
 * TODO: enable/disable hi-z output control
 */

#समावेश <linux/module.h>
#समावेश <linux/i2c.h>
#समावेश <linux/regmap.h>
#समावेश <linux/iio/iपन.स>

काष्ठा tpl0102_cfg अणु
	पूर्णांक wipers;
	पूर्णांक avail[3];
	पूर्णांक kohms;
पूर्ण;

क्रमागत tpl0102_type अणु
	CAT5140_503,
	CAT5140_104,
	TPL0102_104,
	TPL0401_103,
पूर्ण;

अटल स्थिर काष्ठा tpl0102_cfg tpl0102_cfg[] = अणु
	/* on-semiconductor parts */
	[CAT5140_503] = अणु .wipers = 1, .avail = अणु 0, 1, 255 पूर्ण, .kohms = 50, पूर्ण,
	[CAT5140_104] = अणु .wipers = 1, .avail = अणु 0, 1, 255 पूर्ण, .kohms = 100, पूर्ण,
	/* ti parts */
	[TPL0102_104] = अणु .wipers = 2, .avail = अणु 0, 1, 255 पूर्ण, .kohms = 100 पूर्ण,
	[TPL0401_103] = अणु .wipers = 1, .avail = अणु 0, 1, 127 पूर्ण, .kohms = 10, पूर्ण,
पूर्ण;

काष्ठा tpl0102_data अणु
	काष्ठा regmap *regmap;
	स्थिर काष्ठा tpl0102_cfg *cfg;
पूर्ण;

अटल स्थिर काष्ठा regmap_config tpl0102_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 8,
पूर्ण;

#घोषणा TPL0102_CHANNEL(ch) अणु					\
	.type = IIO_RESISTANCE,					\
	.indexed = 1,						\
	.output = 1,						\
	.channel = (ch),					\
	.info_mask_separate = BIT(IIO_CHAN_INFO_RAW),		\
	.info_mask_shared_by_type = BIT(IIO_CHAN_INFO_SCALE),	\
	.info_mask_separate_available = BIT(IIO_CHAN_INFO_RAW),	\
पूर्ण

अटल स्थिर काष्ठा iio_chan_spec tpl0102_channels[] = अणु
	TPL0102_CHANNEL(0),
	TPL0102_CHANNEL(1),
पूर्ण;

अटल पूर्णांक tpl0102_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			    काष्ठा iio_chan_spec स्थिर *chan,
			    पूर्णांक *val, पूर्णांक *val2, दीर्घ mask)
अणु
	काष्ठा tpl0102_data *data = iio_priv(indio_dev);

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW: अणु
		पूर्णांक ret = regmap_पढ़ो(data->regmap, chan->channel, val);

		वापस ret ? ret : IIO_VAL_INT;
	पूर्ण
	हाल IIO_CHAN_INFO_SCALE:
		*val = 1000 * data->cfg->kohms;
		*val2 = data->cfg->avail[2] + 1;
		वापस IIO_VAL_FRACTIONAL;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक tpl0102_पढ़ो_avail(काष्ठा iio_dev *indio_dev,
			      काष्ठा iio_chan_spec स्थिर *chan,
			      स्थिर पूर्णांक **vals, पूर्णांक *type, पूर्णांक *length,
			      दीर्घ mask)
अणु
	काष्ठा tpl0102_data *data = iio_priv(indio_dev);

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		*length = ARRAY_SIZE(data->cfg->avail);
		*vals = data->cfg->avail;
		*type = IIO_VAL_INT;
		वापस IIO_AVAIL_RANGE;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक tpl0102_ग_लिखो_raw(काष्ठा iio_dev *indio_dev,
			     काष्ठा iio_chan_spec स्थिर *chan,
			     पूर्णांक val, पूर्णांक val2, दीर्घ mask)
अणु
	काष्ठा tpl0102_data *data = iio_priv(indio_dev);

	अगर (mask != IIO_CHAN_INFO_RAW)
		वापस -EINVAL;

	अगर (val > data->cfg->avail[2] || val < 0)
		वापस -EINVAL;

	वापस regmap_ग_लिखो(data->regmap, chan->channel, val);
पूर्ण

अटल स्थिर काष्ठा iio_info tpl0102_info = अणु
	.पढ़ो_raw = tpl0102_पढ़ो_raw,
	.पढ़ो_avail = tpl0102_पढ़ो_avail,
	.ग_लिखो_raw = tpl0102_ग_लिखो_raw,
पूर्ण;

अटल पूर्णांक tpl0102_probe(काष्ठा i2c_client *client,
			 स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा device *dev = &client->dev;
	काष्ठा tpl0102_data *data;
	काष्ठा iio_dev *indio_dev;

	indio_dev = devm_iio_device_alloc(dev, माप(*data));
	अगर (!indio_dev)
		वापस -ENOMEM;
	data = iio_priv(indio_dev);
	i2c_set_clientdata(client, indio_dev);

	data->cfg = &tpl0102_cfg[id->driver_data];
	data->regmap = devm_regmap_init_i2c(client, &tpl0102_regmap_config);
	अगर (IS_ERR(data->regmap)) अणु
		dev_err(dev, "regmap initialization failed\n");
		वापस PTR_ERR(data->regmap);
	पूर्ण

	indio_dev->info = &tpl0102_info;
	indio_dev->channels = tpl0102_channels;
	indio_dev->num_channels = data->cfg->wipers;
	indio_dev->name = client->name;

	वापस devm_iio_device_रेजिस्टर(dev, indio_dev);
पूर्ण

अटल स्थिर काष्ठा i2c_device_id tpl0102_id[] = अणु
	अणु "cat5140-503", CAT5140_503 पूर्ण,
	अणु "cat5140-104", CAT5140_104 पूर्ण,
	अणु "tpl0102-104", TPL0102_104 पूर्ण,
	अणु "tpl0401-103", TPL0401_103 पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, tpl0102_id);

अटल काष्ठा i2c_driver tpl0102_driver = अणु
	.driver = अणु
		.name = "tpl0102",
	पूर्ण,
	.probe = tpl0102_probe,
	.id_table = tpl0102_id,
पूर्ण;

module_i2c_driver(tpl0102_driver);

MODULE_AUTHOR("Matt Ranostay <matt.ranostay@konsulko.com>");
MODULE_DESCRIPTION("TPL0102 digital potentiometer");
MODULE_LICENSE("GPL");
