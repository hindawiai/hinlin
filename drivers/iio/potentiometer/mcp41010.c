<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Industrial I/O driver क्रम Microchip digital potentiometers
 *
 * Copyright (c) 2018 Chris Coffey <cmc@babblebit.net>
 * Based on: Slawomir Stepien's code from mcp4131.c
 *
 * Datasheet: https://ww1.microchip.com/करोwnloads/en/deviceकरोc/11195c.pdf
 *
 * DEVID	#Wipers	#Positions	Resistance (kOhm)
 * mcp41010	1	256		10
 * mcp41050	1	256		50
 * mcp41100	1	256		100
 * mcp42010	2	256		10
 * mcp42050	2	256		50
 * mcp42100	2	256		100
 */

#समावेश <linux/cache.h>
#समावेश <linux/err.h>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/types.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/spi/spi.h>

#घोषणा MCP41010_MAX_WIPERS	2
#घोषणा MCP41010_WRITE		BIT(4)
#घोषणा MCP41010_WIPER_MAX	255
#घोषणा MCP41010_WIPER_CHANNEL	BIT(0)

काष्ठा mcp41010_cfg अणु
	अक्षर name[16];
	पूर्णांक wipers;
	पूर्णांक kohms;
पूर्ण;

क्रमागत mcp41010_type अणु
	MCP41010,
	MCP41050,
	MCP41100,
	MCP42010,
	MCP42050,
	MCP42100,
पूर्ण;

अटल स्थिर काष्ठा mcp41010_cfg mcp41010_cfg[] = अणु
	[MCP41010] = अणु .name = "mcp41010", .wipers = 1, .kohms =  10, पूर्ण,
	[MCP41050] = अणु .name = "mcp41050", .wipers = 1, .kohms =  50, पूर्ण,
	[MCP41100] = अणु .name = "mcp41100", .wipers = 1, .kohms = 100, पूर्ण,
	[MCP42010] = अणु .name = "mcp42010", .wipers = 2, .kohms =  10, पूर्ण,
	[MCP42050] = अणु .name = "mcp42050", .wipers = 2, .kohms =  50, पूर्ण,
	[MCP42100] = अणु .name = "mcp42100", .wipers = 2, .kohms = 100, पूर्ण,
पूर्ण;

काष्ठा mcp41010_data अणु
	काष्ठा spi_device *spi;
	स्थिर काष्ठा mcp41010_cfg *cfg;
	काष्ठा mutex lock; /* Protect ग_लिखो sequences */
	अचिन्हित पूर्णांक value[MCP41010_MAX_WIPERS]; /* Cache wiper values */
	u8 buf[2] ____cacheline_aligned;
पूर्ण;

#घोषणा MCP41010_CHANNEL(ch) अणु					\
	.type = IIO_RESISTANCE,					\
	.indexed = 1,						\
	.output = 1,						\
	.channel = (ch),					\
	.info_mask_separate = BIT(IIO_CHAN_INFO_RAW),		\
	.info_mask_shared_by_type = BIT(IIO_CHAN_INFO_SCALE),	\
पूर्ण

अटल स्थिर काष्ठा iio_chan_spec mcp41010_channels[] = अणु
	MCP41010_CHANNEL(0),
	MCP41010_CHANNEL(1),
पूर्ण;

अटल पूर्णांक mcp41010_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			    काष्ठा iio_chan_spec स्थिर *chan,
			    पूर्णांक *val, पूर्णांक *val2, दीर्घ mask)
अणु
	काष्ठा mcp41010_data *data = iio_priv(indio_dev);
	पूर्णांक channel = chan->channel;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		*val = data->value[channel];
		वापस IIO_VAL_INT;

	हाल IIO_CHAN_INFO_SCALE:
		*val = 1000 * data->cfg->kohms;
		*val2 = MCP41010_WIPER_MAX;
		वापस IIO_VAL_FRACTIONAL;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक mcp41010_ग_लिखो_raw(काष्ठा iio_dev *indio_dev,
			     काष्ठा iio_chan_spec स्थिर *chan,
			     पूर्णांक val, पूर्णांक val2, दीर्घ mask)
अणु
	पूर्णांक err;
	काष्ठा mcp41010_data *data = iio_priv(indio_dev);
	पूर्णांक channel = chan->channel;

	अगर (mask != IIO_CHAN_INFO_RAW)
		वापस -EINVAL;

	अगर (val > MCP41010_WIPER_MAX || val < 0)
		वापस -EINVAL;

	mutex_lock(&data->lock);

	data->buf[0] = MCP41010_WIPER_CHANNEL << channel;
	data->buf[0] |= MCP41010_WRITE;
	data->buf[1] = val & 0xff;

	err = spi_ग_लिखो(data->spi, data->buf, माप(data->buf));
	अगर (!err)
		data->value[channel] = val;

	mutex_unlock(&data->lock);

	वापस err;
पूर्ण

अटल स्थिर काष्ठा iio_info mcp41010_info = अणु
	.पढ़ो_raw = mcp41010_पढ़ो_raw,
	.ग_लिखो_raw = mcp41010_ग_लिखो_raw,
पूर्ण;

अटल पूर्णांक mcp41010_probe(काष्ठा spi_device *spi)
अणु
	पूर्णांक err;
	काष्ठा device *dev = &spi->dev;
	काष्ठा mcp41010_data *data;
	काष्ठा iio_dev *indio_dev;

	indio_dev = devm_iio_device_alloc(dev, माप(*data));
	अगर (!indio_dev)
		वापस -ENOMEM;

	data = iio_priv(indio_dev);
	spi_set_drvdata(spi, indio_dev);
	data->spi = spi;
	data->cfg = of_device_get_match_data(&spi->dev);
	अगर (!data->cfg)
		data->cfg = &mcp41010_cfg[spi_get_device_id(spi)->driver_data];

	mutex_init(&data->lock);

	indio_dev->info = &mcp41010_info;
	indio_dev->channels = mcp41010_channels;
	indio_dev->num_channels = data->cfg->wipers;
	indio_dev->name = data->cfg->name;

	err = devm_iio_device_रेजिस्टर(dev, indio_dev);
	अगर (err)
		dev_info(&spi->dev, "Unable to register %s\n", indio_dev->name);

	वापस err;
पूर्ण

अटल स्थिर काष्ठा of_device_id mcp41010_match[] = अणु
	अणु .compatible = "microchip,mcp41010", .data = &mcp41010_cfg[MCP41010] पूर्ण,
	अणु .compatible = "microchip,mcp41050", .data = &mcp41010_cfg[MCP41050] पूर्ण,
	अणु .compatible = "microchip,mcp41100", .data = &mcp41010_cfg[MCP41100] पूर्ण,
	अणु .compatible = "microchip,mcp42010", .data = &mcp41010_cfg[MCP42010] पूर्ण,
	अणु .compatible = "microchip,mcp42050", .data = &mcp41010_cfg[MCP42050] पूर्ण,
	अणु .compatible = "microchip,mcp42100", .data = &mcp41010_cfg[MCP42100] पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, mcp41010_match);

अटल स्थिर काष्ठा spi_device_id mcp41010_id[] = अणु
	अणु "mcp41010", MCP41010 पूर्ण,
	अणु "mcp41050", MCP41050 पूर्ण,
	अणु "mcp41100", MCP41100 पूर्ण,
	अणु "mcp42010", MCP42010 पूर्ण,
	अणु "mcp42050", MCP42050 पूर्ण,
	अणु "mcp42100", MCP42100 पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(spi, mcp41010_id);

अटल काष्ठा spi_driver mcp41010_driver = अणु
	.driver = अणु
		.name	= "mcp41010",
		.of_match_table = mcp41010_match,
	पूर्ण,
	.probe		= mcp41010_probe,
	.id_table	= mcp41010_id,
पूर्ण;

module_spi_driver(mcp41010_driver);

MODULE_AUTHOR("Chris Coffey <cmc@babblebit.net>");
MODULE_DESCRIPTION("MCP41010 digital potentiometer");
MODULE_LICENSE("GPL v2");
