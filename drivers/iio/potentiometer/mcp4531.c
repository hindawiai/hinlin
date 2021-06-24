<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Industrial I/O driver क्रम Microchip digital potentiometers
 * Copyright (c) 2015  Axentia Technologies AB
 * Author: Peter Rosin <peda@axentia.se>
 *
 * Datasheet: http://www.microchip.com/करोwnloads/en/DeviceDoc/22096b.pdf
 *
 * DEVID	#Wipers	#Positions	Resistor Opts (kOhm)	i2c address
 * mcp4531	1	129		5, 10, 50, 100          010111x
 * mcp4532	1	129		5, 10, 50, 100          01011xx
 * mcp4541	1	129		5, 10, 50, 100          010111x
 * mcp4542	1	129		5, 10, 50, 100          01011xx
 * mcp4551	1	257		5, 10, 50, 100          010111x
 * mcp4552	1	257		5, 10, 50, 100          01011xx
 * mcp4561	1	257		5, 10, 50, 100          010111x
 * mcp4562	1	257		5, 10, 50, 100          01011xx
 * mcp4631	2	129		5, 10, 50, 100          0101xxx
 * mcp4632	2	129		5, 10, 50, 100          01011xx
 * mcp4641	2	129		5, 10, 50, 100          0101xxx
 * mcp4642	2	129		5, 10, 50, 100          01011xx
 * mcp4651	2	257		5, 10, 50, 100          0101xxx
 * mcp4652	2	257		5, 10, 50, 100          01011xx
 * mcp4661	2	257		5, 10, 50, 100          0101xxx
 * mcp4662	2	257		5, 10, 50, 100          01011xx
 */

#समावेश <linux/module.h>
#समावेश <linux/i2c.h>
#समावेश <linux/err.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/property.h>

#समावेश <linux/iio/iपन.स>

काष्ठा mcp4531_cfg अणु
	पूर्णांक wipers;
	पूर्णांक avail[3];
	पूर्णांक kohms;
पूर्ण;

क्रमागत mcp4531_type अणु
	MCP453x_502,
	MCP453x_103,
	MCP453x_503,
	MCP453x_104,
	MCP454x_502,
	MCP454x_103,
	MCP454x_503,
	MCP454x_104,
	MCP455x_502,
	MCP455x_103,
	MCP455x_503,
	MCP455x_104,
	MCP456x_502,
	MCP456x_103,
	MCP456x_503,
	MCP456x_104,
	MCP463x_502,
	MCP463x_103,
	MCP463x_503,
	MCP463x_104,
	MCP464x_502,
	MCP464x_103,
	MCP464x_503,
	MCP464x_104,
	MCP465x_502,
	MCP465x_103,
	MCP465x_503,
	MCP465x_104,
	MCP466x_502,
	MCP466x_103,
	MCP466x_503,
	MCP466x_104,
पूर्ण;

अटल स्थिर काष्ठा mcp4531_cfg mcp4531_cfg[] = अणु
	[MCP453x_502] = अणु .wipers = 1, .avail = अणु 0, 1, 128 पूर्ण, .kohms =   5, पूर्ण,
	[MCP453x_103] = अणु .wipers = 1, .avail = अणु 0, 1, 128 पूर्ण, .kohms =  10, पूर्ण,
	[MCP453x_503] = अणु .wipers = 1, .avail = अणु 0, 1, 128 पूर्ण, .kohms =  50, पूर्ण,
	[MCP453x_104] = अणु .wipers = 1, .avail = अणु 0, 1, 128 पूर्ण, .kohms = 100, पूर्ण,
	[MCP454x_502] = अणु .wipers = 1, .avail = अणु 0, 1, 128 पूर्ण, .kohms =   5, पूर्ण,
	[MCP454x_103] = अणु .wipers = 1, .avail = अणु 0, 1, 128 पूर्ण, .kohms =  10, पूर्ण,
	[MCP454x_503] = अणु .wipers = 1, .avail = अणु 0, 1, 128 पूर्ण, .kohms =  50, पूर्ण,
	[MCP454x_104] = अणु .wipers = 1, .avail = अणु 0, 1, 128 पूर्ण, .kohms = 100, पूर्ण,
	[MCP455x_502] = अणु .wipers = 1, .avail = अणु 0, 1, 256 पूर्ण, .kohms =   5, पूर्ण,
	[MCP455x_103] = अणु .wipers = 1, .avail = अणु 0, 1, 256 पूर्ण, .kohms =  10, पूर्ण,
	[MCP455x_503] = अणु .wipers = 1, .avail = अणु 0, 1, 256 पूर्ण, .kohms =  50, पूर्ण,
	[MCP455x_104] = अणु .wipers = 1, .avail = अणु 0, 1, 256 पूर्ण, .kohms = 100, पूर्ण,
	[MCP456x_502] = अणु .wipers = 1, .avail = अणु 0, 1, 256 पूर्ण, .kohms =   5, पूर्ण,
	[MCP456x_103] = अणु .wipers = 1, .avail = अणु 0, 1, 256 पूर्ण, .kohms =  10, पूर्ण,
	[MCP456x_503] = अणु .wipers = 1, .avail = अणु 0, 1, 256 पूर्ण, .kohms =  50, पूर्ण,
	[MCP456x_104] = अणु .wipers = 1, .avail = अणु 0, 1, 256 पूर्ण, .kohms = 100, पूर्ण,
	[MCP463x_502] = अणु .wipers = 2, .avail = अणु 0, 1, 128 पूर्ण, .kohms =   5, पूर्ण,
	[MCP463x_103] = अणु .wipers = 2, .avail = अणु 0, 1, 128 पूर्ण, .kohms =  10, पूर्ण,
	[MCP463x_503] = अणु .wipers = 2, .avail = अणु 0, 1, 128 पूर्ण, .kohms =  50, पूर्ण,
	[MCP463x_104] = अणु .wipers = 2, .avail = अणु 0, 1, 128 पूर्ण, .kohms = 100, पूर्ण,
	[MCP464x_502] = अणु .wipers = 2, .avail = अणु 0, 1, 128 पूर्ण, .kohms =   5, पूर्ण,
	[MCP464x_103] = अणु .wipers = 2, .avail = अणु 0, 1, 128 पूर्ण, .kohms =  10, पूर्ण,
	[MCP464x_503] = अणु .wipers = 2, .avail = अणु 0, 1, 128 पूर्ण, .kohms =  50, पूर्ण,
	[MCP464x_104] = अणु .wipers = 2, .avail = अणु 0, 1, 128 पूर्ण, .kohms = 100, पूर्ण,
	[MCP465x_502] = अणु .wipers = 2, .avail = अणु 0, 1, 256 पूर्ण, .kohms =   5, पूर्ण,
	[MCP465x_103] = अणु .wipers = 2, .avail = अणु 0, 1, 256 पूर्ण, .kohms =  10, पूर्ण,
	[MCP465x_503] = अणु .wipers = 2, .avail = अणु 0, 1, 256 पूर्ण, .kohms =  50, पूर्ण,
	[MCP465x_104] = अणु .wipers = 2, .avail = अणु 0, 1, 256 पूर्ण, .kohms = 100, पूर्ण,
	[MCP466x_502] = अणु .wipers = 2, .avail = अणु 0, 1, 256 पूर्ण, .kohms =   5, पूर्ण,
	[MCP466x_103] = अणु .wipers = 2, .avail = अणु 0, 1, 256 पूर्ण, .kohms =  10, पूर्ण,
	[MCP466x_503] = अणु .wipers = 2, .avail = अणु 0, 1, 256 पूर्ण, .kohms =  50, पूर्ण,
	[MCP466x_104] = अणु .wipers = 2, .avail = अणु 0, 1, 256 पूर्ण, .kohms = 100, पूर्ण,
पूर्ण;

#घोषणा MCP4531_WRITE (0 << 2)
#घोषणा MCP4531_INCR  (1 << 2)
#घोषणा MCP4531_DECR  (2 << 2)
#घोषणा MCP4531_READ  (3 << 2)

#घोषणा MCP4531_WIPER_SHIFT (4)

काष्ठा mcp4531_data अणु
	काष्ठा i2c_client *client;
	स्थिर काष्ठा mcp4531_cfg *cfg;
पूर्ण;

#घोषणा MCP4531_CHANNEL(ch) अणु						\
	.type = IIO_RESISTANCE,						\
	.indexed = 1,							\
	.output = 1,							\
	.channel = (ch),						\
	.info_mask_separate = BIT(IIO_CHAN_INFO_RAW),			\
	.info_mask_shared_by_type = BIT(IIO_CHAN_INFO_SCALE),		\
	.info_mask_shared_by_type_available = BIT(IIO_CHAN_INFO_RAW),	\
पूर्ण

अटल स्थिर काष्ठा iio_chan_spec mcp4531_channels[] = अणु
	MCP4531_CHANNEL(0),
	MCP4531_CHANNEL(1),
पूर्ण;

अटल पूर्णांक mcp4531_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			    काष्ठा iio_chan_spec स्थिर *chan,
			    पूर्णांक *val, पूर्णांक *val2, दीर्घ mask)
अणु
	काष्ठा mcp4531_data *data = iio_priv(indio_dev);
	पूर्णांक address = chan->channel << MCP4531_WIPER_SHIFT;
	s32 ret;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		ret = i2c_smbus_पढ़ो_word_swapped(data->client,
						  MCP4531_READ | address);
		अगर (ret < 0)
			वापस ret;
		*val = ret;
		वापस IIO_VAL_INT;
	हाल IIO_CHAN_INFO_SCALE:
		*val = 1000 * data->cfg->kohms;
		*val2 = data->cfg->avail[2];
		वापस IIO_VAL_FRACTIONAL;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक mcp4531_पढ़ो_avail(काष्ठा iio_dev *indio_dev,
			      काष्ठा iio_chan_spec स्थिर *chan,
			      स्थिर पूर्णांक **vals, पूर्णांक *type, पूर्णांक *length,
			      दीर्घ mask)
अणु
	काष्ठा mcp4531_data *data = iio_priv(indio_dev);

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		*length = ARRAY_SIZE(data->cfg->avail);
		*vals = data->cfg->avail;
		*type = IIO_VAL_INT;
		वापस IIO_AVAIL_RANGE;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक mcp4531_ग_लिखो_raw(काष्ठा iio_dev *indio_dev,
			     काष्ठा iio_chan_spec स्थिर *chan,
			     पूर्णांक val, पूर्णांक val2, दीर्घ mask)
अणु
	काष्ठा mcp4531_data *data = iio_priv(indio_dev);
	पूर्णांक address = chan->channel << MCP4531_WIPER_SHIFT;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		अगर (val > data->cfg->avail[2] || val < 0)
			वापस -EINVAL;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस i2c_smbus_ग_लिखो_byte_data(data->client,
					 MCP4531_WRITE | address | (val >> 8),
					 val & 0xff);
पूर्ण

अटल स्थिर काष्ठा iio_info mcp4531_info = अणु
	.पढ़ो_raw = mcp4531_पढ़ो_raw,
	.पढ़ो_avail = mcp4531_पढ़ो_avail,
	.ग_लिखो_raw = mcp4531_ग_लिखो_raw,
पूर्ण;

अटल स्थिर काष्ठा i2c_device_id mcp4531_id[] = अणु
	अणु "mcp4531-502", MCP453x_502 पूर्ण,
	अणु "mcp4531-103", MCP453x_103 पूर्ण,
	अणु "mcp4531-503", MCP453x_503 पूर्ण,
	अणु "mcp4531-104", MCP453x_104 पूर्ण,
	अणु "mcp4532-502", MCP453x_502 पूर्ण,
	अणु "mcp4532-103", MCP453x_103 पूर्ण,
	अणु "mcp4532-503", MCP453x_503 पूर्ण,
	अणु "mcp4532-104", MCP453x_104 पूर्ण,
	अणु "mcp4541-502", MCP454x_502 पूर्ण,
	अणु "mcp4541-103", MCP454x_103 पूर्ण,
	अणु "mcp4541-503", MCP454x_503 पूर्ण,
	अणु "mcp4541-104", MCP454x_104 पूर्ण,
	अणु "mcp4542-502", MCP454x_502 पूर्ण,
	अणु "mcp4542-103", MCP454x_103 पूर्ण,
	अणु "mcp4542-503", MCP454x_503 पूर्ण,
	अणु "mcp4542-104", MCP454x_104 पूर्ण,
	अणु "mcp4551-502", MCP455x_502 पूर्ण,
	अणु "mcp4551-103", MCP455x_103 पूर्ण,
	अणु "mcp4551-503", MCP455x_503 पूर्ण,
	अणु "mcp4551-104", MCP455x_104 पूर्ण,
	अणु "mcp4552-502", MCP455x_502 पूर्ण,
	अणु "mcp4552-103", MCP455x_103 पूर्ण,
	अणु "mcp4552-503", MCP455x_503 पूर्ण,
	अणु "mcp4552-104", MCP455x_104 पूर्ण,
	अणु "mcp4561-502", MCP456x_502 पूर्ण,
	अणु "mcp4561-103", MCP456x_103 पूर्ण,
	अणु "mcp4561-503", MCP456x_503 पूर्ण,
	अणु "mcp4561-104", MCP456x_104 पूर्ण,
	अणु "mcp4562-502", MCP456x_502 पूर्ण,
	अणु "mcp4562-103", MCP456x_103 पूर्ण,
	अणु "mcp4562-503", MCP456x_503 पूर्ण,
	अणु "mcp4562-104", MCP456x_104 पूर्ण,
	अणु "mcp4631-502", MCP463x_502 पूर्ण,
	अणु "mcp4631-103", MCP463x_103 पूर्ण,
	अणु "mcp4631-503", MCP463x_503 पूर्ण,
	अणु "mcp4631-104", MCP463x_104 पूर्ण,
	अणु "mcp4632-502", MCP463x_502 पूर्ण,
	अणु "mcp4632-103", MCP463x_103 पूर्ण,
	अणु "mcp4632-503", MCP463x_503 पूर्ण,
	अणु "mcp4632-104", MCP463x_104 पूर्ण,
	अणु "mcp4641-502", MCP464x_502 पूर्ण,
	अणु "mcp4641-103", MCP464x_103 पूर्ण,
	अणु "mcp4641-503", MCP464x_503 पूर्ण,
	अणु "mcp4641-104", MCP464x_104 पूर्ण,
	अणु "mcp4642-502", MCP464x_502 पूर्ण,
	अणु "mcp4642-103", MCP464x_103 पूर्ण,
	अणु "mcp4642-503", MCP464x_503 पूर्ण,
	अणु "mcp4642-104", MCP464x_104 पूर्ण,
	अणु "mcp4651-502", MCP465x_502 पूर्ण,
	अणु "mcp4651-103", MCP465x_103 पूर्ण,
	अणु "mcp4651-503", MCP465x_503 पूर्ण,
	अणु "mcp4651-104", MCP465x_104 पूर्ण,
	अणु "mcp4652-502", MCP465x_502 पूर्ण,
	अणु "mcp4652-103", MCP465x_103 पूर्ण,
	अणु "mcp4652-503", MCP465x_503 पूर्ण,
	अणु "mcp4652-104", MCP465x_104 पूर्ण,
	अणु "mcp4661-502", MCP466x_502 पूर्ण,
	अणु "mcp4661-103", MCP466x_103 पूर्ण,
	अणु "mcp4661-503", MCP466x_503 पूर्ण,
	अणु "mcp4661-104", MCP466x_104 पूर्ण,
	अणु "mcp4662-502", MCP466x_502 पूर्ण,
	अणु "mcp4662-103", MCP466x_103 पूर्ण,
	अणु "mcp4662-503", MCP466x_503 पूर्ण,
	अणु "mcp4662-104", MCP466x_104 पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, mcp4531_id);

#घोषणा MCP4531_COMPATIBLE(of_compatible, cfg) अणु	\
			.compatible = of_compatible,	\
			.data = &mcp4531_cfg[cfg],	\
पूर्ण

अटल स्थिर काष्ठा of_device_id mcp4531_of_match[] = अणु
	MCP4531_COMPATIBLE("microchip,mcp4531-502", MCP453x_502),
	MCP4531_COMPATIBLE("microchip,mcp4531-103", MCP453x_103),
	MCP4531_COMPATIBLE("microchip,mcp4531-503", MCP453x_503),
	MCP4531_COMPATIBLE("microchip,mcp4531-104", MCP453x_104),
	MCP4531_COMPATIBLE("microchip,mcp4532-502", MCP453x_502),
	MCP4531_COMPATIBLE("microchip,mcp4532-103", MCP453x_103),
	MCP4531_COMPATIBLE("microchip,mcp4532-503", MCP453x_503),
	MCP4531_COMPATIBLE("microchip,mcp4532-104", MCP453x_104),
	MCP4531_COMPATIBLE("microchip,mcp4541-502", MCP454x_502),
	MCP4531_COMPATIBLE("microchip,mcp4541-103", MCP454x_103),
	MCP4531_COMPATIBLE("microchip,mcp4541-503", MCP454x_503),
	MCP4531_COMPATIBLE("microchip,mcp4541-104", MCP454x_104),
	MCP4531_COMPATIBLE("microchip,mcp4542-502", MCP454x_502),
	MCP4531_COMPATIBLE("microchip,mcp4542-103", MCP454x_103),
	MCP4531_COMPATIBLE("microchip,mcp4542-503", MCP454x_503),
	MCP4531_COMPATIBLE("microchip,mcp4542-104", MCP454x_104),
	MCP4531_COMPATIBLE("microchip,mcp4551-502", MCP455x_502),
	MCP4531_COMPATIBLE("microchip,mcp4551-103", MCP455x_103),
	MCP4531_COMPATIBLE("microchip,mcp4551-503", MCP455x_503),
	MCP4531_COMPATIBLE("microchip,mcp4551-104", MCP455x_104),
	MCP4531_COMPATIBLE("microchip,mcp4552-502", MCP455x_502),
	MCP4531_COMPATIBLE("microchip,mcp4552-103", MCP455x_103),
	MCP4531_COMPATIBLE("microchip,mcp4552-503", MCP455x_503),
	MCP4531_COMPATIBLE("microchip,mcp4552-104", MCP455x_104),
	MCP4531_COMPATIBLE("microchip,mcp4561-502", MCP456x_502),
	MCP4531_COMPATIBLE("microchip,mcp4561-103", MCP456x_103),
	MCP4531_COMPATIBLE("microchip,mcp4561-503", MCP456x_503),
	MCP4531_COMPATIBLE("microchip,mcp4561-104", MCP456x_104),
	MCP4531_COMPATIBLE("microchip,mcp4562-502", MCP456x_502),
	MCP4531_COMPATIBLE("microchip,mcp4562-103", MCP456x_103),
	MCP4531_COMPATIBLE("microchip,mcp4562-503", MCP456x_503),
	MCP4531_COMPATIBLE("microchip,mcp4562-104", MCP456x_104),
	MCP4531_COMPATIBLE("microchip,mcp4631-502", MCP463x_502),
	MCP4531_COMPATIBLE("microchip,mcp4631-103", MCP463x_103),
	MCP4531_COMPATIBLE("microchip,mcp4631-503", MCP463x_503),
	MCP4531_COMPATIBLE("microchip,mcp4631-104", MCP463x_104),
	MCP4531_COMPATIBLE("microchip,mcp4632-502", MCP463x_502),
	MCP4531_COMPATIBLE("microchip,mcp4632-103", MCP463x_103),
	MCP4531_COMPATIBLE("microchip,mcp4632-503", MCP463x_503),
	MCP4531_COMPATIBLE("microchip,mcp4632-104", MCP463x_104),
	MCP4531_COMPATIBLE("microchip,mcp4641-502", MCP464x_502),
	MCP4531_COMPATIBLE("microchip,mcp4641-103", MCP464x_103),
	MCP4531_COMPATIBLE("microchip,mcp4641-503", MCP464x_503),
	MCP4531_COMPATIBLE("microchip,mcp4641-104", MCP464x_104),
	MCP4531_COMPATIBLE("microchip,mcp4642-502", MCP464x_502),
	MCP4531_COMPATIBLE("microchip,mcp4642-103", MCP464x_103),
	MCP4531_COMPATIBLE("microchip,mcp4642-503", MCP464x_503),
	MCP4531_COMPATIBLE("microchip,mcp4642-104", MCP464x_104),
	MCP4531_COMPATIBLE("microchip,mcp4651-502", MCP465x_502),
	MCP4531_COMPATIBLE("microchip,mcp4651-103", MCP465x_103),
	MCP4531_COMPATIBLE("microchip,mcp4651-503", MCP465x_503),
	MCP4531_COMPATIBLE("microchip,mcp4651-104", MCP465x_104),
	MCP4531_COMPATIBLE("microchip,mcp4652-502", MCP465x_502),
	MCP4531_COMPATIBLE("microchip,mcp4652-103", MCP465x_103),
	MCP4531_COMPATIBLE("microchip,mcp4652-503", MCP465x_503),
	MCP4531_COMPATIBLE("microchip,mcp4652-104", MCP465x_104),
	MCP4531_COMPATIBLE("microchip,mcp4661-502", MCP466x_502),
	MCP4531_COMPATIBLE("microchip,mcp4661-103", MCP466x_103),
	MCP4531_COMPATIBLE("microchip,mcp4661-503", MCP466x_503),
	MCP4531_COMPATIBLE("microchip,mcp4661-104", MCP466x_104),
	MCP4531_COMPATIBLE("microchip,mcp4662-502", MCP466x_502),
	MCP4531_COMPATIBLE("microchip,mcp4662-103", MCP466x_103),
	MCP4531_COMPATIBLE("microchip,mcp4662-503", MCP466x_503),
	MCP4531_COMPATIBLE("microchip,mcp4662-104", MCP466x_104),
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, mcp4531_of_match);

अटल पूर्णांक mcp4531_probe(काष्ठा i2c_client *client)
अणु
	काष्ठा device *dev = &client->dev;
	काष्ठा mcp4531_data *data;
	काष्ठा iio_dev *indio_dev;

	अगर (!i2c_check_functionality(client->adapter,
				     I2C_FUNC_SMBUS_WORD_DATA)) अणु
		dev_err(dev, "SMBUS Word Data not supported\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	indio_dev = devm_iio_device_alloc(dev, माप(*data));
	अगर (!indio_dev)
		वापस -ENOMEM;
	data = iio_priv(indio_dev);
	i2c_set_clientdata(client, indio_dev);
	data->client = client;

	data->cfg = device_get_match_data(dev);
	अगर (!data->cfg)
		data->cfg = &mcp4531_cfg[i2c_match_id(mcp4531_id, client)->driver_data];

	indio_dev->info = &mcp4531_info;
	indio_dev->channels = mcp4531_channels;
	indio_dev->num_channels = data->cfg->wipers;
	indio_dev->name = client->name;

	वापस devm_iio_device_रेजिस्टर(dev, indio_dev);
पूर्ण

अटल काष्ठा i2c_driver mcp4531_driver = अणु
	.driver = अणु
		.name	= "mcp4531",
		.of_match_table = mcp4531_of_match,
	पूर्ण,
	.probe_new	= mcp4531_probe,
	.id_table	= mcp4531_id,
पूर्ण;

module_i2c_driver(mcp4531_driver);

MODULE_AUTHOR("Peter Rosin <peda@axentia.se>");
MODULE_DESCRIPTION("MCP4531 digital potentiometer");
MODULE_LICENSE("GPL v2");
