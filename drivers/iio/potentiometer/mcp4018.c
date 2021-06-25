<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Industrial I/O driver क्रम Microchip digital potentiometers
 * Copyright (c) 2018  Axentia Technologies AB
 * Author: Peter Rosin <peda@axentia.se>
 *
 * Datasheet: http://www.microchip.com/करोwnloads/en/DeviceDoc/22147a.pdf
 *
 * DEVID	#Wipers	#Positions	Resistor Opts (kOhm)
 * mcp4017	1	128		5, 10, 50, 100
 * mcp4018	1	128		5, 10, 50, 100
 * mcp4019	1	128		5, 10, 50, 100
 */

#समावेश <linux/err.h>
#समावेश <linux/i2c.h>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/module.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/property.h>

#घोषणा MCP4018_WIPER_MAX 127

काष्ठा mcp4018_cfg अणु
	पूर्णांक kohms;
पूर्ण;

क्रमागत mcp4018_type अणु
	MCP4018_502,
	MCP4018_103,
	MCP4018_503,
	MCP4018_104,
पूर्ण;

अटल स्थिर काष्ठा mcp4018_cfg mcp4018_cfg[] = अणु
	[MCP4018_502] = अणु .kohms =   5, पूर्ण,
	[MCP4018_103] = अणु .kohms =  10, पूर्ण,
	[MCP4018_503] = अणु .kohms =  50, पूर्ण,
	[MCP4018_104] = अणु .kohms = 100, पूर्ण,
पूर्ण;

काष्ठा mcp4018_data अणु
	काष्ठा i2c_client *client;
	स्थिर काष्ठा mcp4018_cfg *cfg;
पूर्ण;

अटल स्थिर काष्ठा iio_chan_spec mcp4018_channel = अणु
	.type = IIO_RESISTANCE,
	.indexed = 1,
	.output = 1,
	.channel = 0,
	.info_mask_separate = BIT(IIO_CHAN_INFO_RAW),
	.info_mask_shared_by_type = BIT(IIO_CHAN_INFO_SCALE),
पूर्ण;

अटल पूर्णांक mcp4018_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			    काष्ठा iio_chan_spec स्थिर *chan,
			    पूर्णांक *val, पूर्णांक *val2, दीर्घ mask)
अणु
	काष्ठा mcp4018_data *data = iio_priv(indio_dev);
	s32 ret;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		ret = i2c_smbus_पढ़ो_byte(data->client);
		अगर (ret < 0)
			वापस ret;
		*val = ret;
		वापस IIO_VAL_INT;
	हाल IIO_CHAN_INFO_SCALE:
		*val = 1000 * data->cfg->kohms;
		*val2 = MCP4018_WIPER_MAX;
		वापस IIO_VAL_FRACTIONAL;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक mcp4018_ग_लिखो_raw(काष्ठा iio_dev *indio_dev,
			     काष्ठा iio_chan_spec स्थिर *chan,
			     पूर्णांक val, पूर्णांक val2, दीर्घ mask)
अणु
	काष्ठा mcp4018_data *data = iio_priv(indio_dev);

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		अगर (val > MCP4018_WIPER_MAX || val < 0)
			वापस -EINVAL;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस i2c_smbus_ग_लिखो_byte(data->client, val);
पूर्ण

अटल स्थिर काष्ठा iio_info mcp4018_info = अणु
	.पढ़ो_raw = mcp4018_पढ़ो_raw,
	.ग_लिखो_raw = mcp4018_ग_लिखो_raw,
पूर्ण;

अटल स्थिर काष्ठा i2c_device_id mcp4018_id[] = अणु
	अणु "mcp4017-502", MCP4018_502 पूर्ण,
	अणु "mcp4017-103", MCP4018_103 पूर्ण,
	अणु "mcp4017-503", MCP4018_503 पूर्ण,
	अणु "mcp4017-104", MCP4018_104 पूर्ण,
	अणु "mcp4018-502", MCP4018_502 पूर्ण,
	अणु "mcp4018-103", MCP4018_103 पूर्ण,
	अणु "mcp4018-503", MCP4018_503 पूर्ण,
	अणु "mcp4018-104", MCP4018_104 पूर्ण,
	अणु "mcp4019-502", MCP4018_502 पूर्ण,
	अणु "mcp4019-103", MCP4018_103 पूर्ण,
	अणु "mcp4019-503", MCP4018_503 पूर्ण,
	अणु "mcp4019-104", MCP4018_104 पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, mcp4018_id);

#घोषणा MCP4018_COMPATIBLE(of_compatible, cfg) अणु	\
	.compatible = of_compatible,			\
	.data = &mcp4018_cfg[cfg],			\
पूर्ण

अटल स्थिर काष्ठा of_device_id mcp4018_of_match[] = अणु
	MCP4018_COMPATIBLE("microchip,mcp4017-502", MCP4018_502),
	MCP4018_COMPATIBLE("microchip,mcp4017-103", MCP4018_103),
	MCP4018_COMPATIBLE("microchip,mcp4017-503", MCP4018_503),
	MCP4018_COMPATIBLE("microchip,mcp4017-104", MCP4018_104),
	MCP4018_COMPATIBLE("microchip,mcp4018-502", MCP4018_502),
	MCP4018_COMPATIBLE("microchip,mcp4018-103", MCP4018_103),
	MCP4018_COMPATIBLE("microchip,mcp4018-503", MCP4018_503),
	MCP4018_COMPATIBLE("microchip,mcp4018-104", MCP4018_104),
	MCP4018_COMPATIBLE("microchip,mcp4019-502", MCP4018_502),
	MCP4018_COMPATIBLE("microchip,mcp4019-103", MCP4018_103),
	MCP4018_COMPATIBLE("microchip,mcp4019-503", MCP4018_503),
	MCP4018_COMPATIBLE("microchip,mcp4019-104", MCP4018_104),
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, mcp4018_of_match);

अटल पूर्णांक mcp4018_probe(काष्ठा i2c_client *client)
अणु
	काष्ठा device *dev = &client->dev;
	काष्ठा mcp4018_data *data;
	काष्ठा iio_dev *indio_dev;

	अगर (!i2c_check_functionality(client->adapter,
				     I2C_FUNC_SMBUS_BYTE)) अणु
		dev_err(dev, "SMBUS Byte transfers not supported\n");
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
		data->cfg = &mcp4018_cfg[i2c_match_id(mcp4018_id, client)->driver_data];

	indio_dev->info = &mcp4018_info;
	indio_dev->channels = &mcp4018_channel;
	indio_dev->num_channels = 1;
	indio_dev->name = client->name;

	वापस devm_iio_device_रेजिस्टर(dev, indio_dev);
पूर्ण

अटल काष्ठा i2c_driver mcp4018_driver = अणु
	.driver = अणु
		.name	= "mcp4018",
		.of_match_table = mcp4018_of_match,
	पूर्ण,
	.probe_new	= mcp4018_probe,
	.id_table	= mcp4018_id,
पूर्ण;

module_i2c_driver(mcp4018_driver);

MODULE_AUTHOR("Peter Rosin <peda@axentia.se>");
MODULE_DESCRIPTION("MCP4018 digital potentiometer");
MODULE_LICENSE("GPL v2");
