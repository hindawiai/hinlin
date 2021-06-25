<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Industrial I/O driver क्रम Microchip digital potentiometers
 *
 * Copyright (c) 2016 Slawomir Stepien
 * Based on: Peter Rosin's code from mcp4531.c
 *
 * Datasheet: https://ww1.microchip.com/करोwnloads/en/DeviceDoc/22060b.pdf
 *
 * DEVID	#Wipers	#Positions	Resistor Opts (kOhm)
 * mcp4131	1	129		5, 10, 50, 100
 * mcp4132	1	129		5, 10, 50, 100
 * mcp4141	1	129		5, 10, 50, 100
 * mcp4142	1	129		5, 10, 50, 100
 * mcp4151	1	257		5, 10, 50, 100
 * mcp4152	1	257		5, 10, 50, 100
 * mcp4161	1	257		5, 10, 50, 100
 * mcp4162	1	257		5, 10, 50, 100
 * mcp4231	2	129		5, 10, 50, 100
 * mcp4232	2	129		5, 10, 50, 100
 * mcp4241	2	129		5, 10, 50, 100
 * mcp4242	2	129		5, 10, 50, 100
 * mcp4251	2	257		5, 10, 50, 100
 * mcp4252	2	257		5, 10, 50, 100
 * mcp4261	2	257		5, 10, 50, 100
 * mcp4262	2	257		5, 10, 50, 100
 */

/*
 * TODO:
 * 1. Write wiper setting to EEPROM क्रम EEPROM capable models.
 */

#समावेश <linux/cache.h>
#समावेश <linux/err.h>
#समावेश <linux/export.h>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/types.h>
#समावेश <linux/module.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/mutex.h>
#समावेश <linux/property.h>
#समावेश <linux/spi/spi.h>

#घोषणा MCP4131_WRITE		(0x00 << 2)
#घोषणा MCP4131_READ		(0x03 << 2)

#घोषणा MCP4131_WIPER_SHIFT	4
#घोषणा MCP4131_CMDERR(r)	((r[0]) & 0x02)
#घोषणा MCP4131_RAW(r)		((r[0]) == 0xff ? 0x100 : (r[1]))

काष्ठा mcp4131_cfg अणु
	पूर्णांक wipers;
	पूर्णांक max_pos;
	पूर्णांक kohms;
पूर्ण;

क्रमागत mcp4131_type अणु
	MCP413x_502 = 0,
	MCP413x_103,
	MCP413x_503,
	MCP413x_104,
	MCP414x_502,
	MCP414x_103,
	MCP414x_503,
	MCP414x_104,
	MCP415x_502,
	MCP415x_103,
	MCP415x_503,
	MCP415x_104,
	MCP416x_502,
	MCP416x_103,
	MCP416x_503,
	MCP416x_104,
	MCP423x_502,
	MCP423x_103,
	MCP423x_503,
	MCP423x_104,
	MCP424x_502,
	MCP424x_103,
	MCP424x_503,
	MCP424x_104,
	MCP425x_502,
	MCP425x_103,
	MCP425x_503,
	MCP425x_104,
	MCP426x_502,
	MCP426x_103,
	MCP426x_503,
	MCP426x_104,
पूर्ण;

अटल स्थिर काष्ठा mcp4131_cfg mcp4131_cfg[] = अणु
	[MCP413x_502] = अणु .wipers = 1, .max_pos = 128, .kohms =   5, पूर्ण,
	[MCP413x_103] = अणु .wipers = 1, .max_pos = 128, .kohms =  10, पूर्ण,
	[MCP413x_503] = अणु .wipers = 1, .max_pos = 128, .kohms =  50, पूर्ण,
	[MCP413x_104] = अणु .wipers = 1, .max_pos = 128, .kohms = 100, पूर्ण,
	[MCP414x_502] = अणु .wipers = 1, .max_pos = 128, .kohms =   5, पूर्ण,
	[MCP414x_103] = अणु .wipers = 1, .max_pos = 128, .kohms =  10, पूर्ण,
	[MCP414x_503] = अणु .wipers = 1, .max_pos = 128, .kohms =  50, पूर्ण,
	[MCP414x_104] = अणु .wipers = 1, .max_pos = 128, .kohms = 100, पूर्ण,
	[MCP415x_502] = अणु .wipers = 1, .max_pos = 256, .kohms =   5, पूर्ण,
	[MCP415x_103] = अणु .wipers = 1, .max_pos = 256, .kohms =  10, पूर्ण,
	[MCP415x_503] = अणु .wipers = 1, .max_pos = 256, .kohms =  50, पूर्ण,
	[MCP415x_104] = अणु .wipers = 1, .max_pos = 256, .kohms = 100, पूर्ण,
	[MCP416x_502] = अणु .wipers = 1, .max_pos = 256, .kohms =   5, पूर्ण,
	[MCP416x_103] = अणु .wipers = 1, .max_pos = 256, .kohms =  10, पूर्ण,
	[MCP416x_503] = अणु .wipers = 1, .max_pos = 256, .kohms =  50, पूर्ण,
	[MCP416x_104] = अणु .wipers = 1, .max_pos = 256, .kohms = 100, पूर्ण,
	[MCP423x_502] = अणु .wipers = 2, .max_pos = 128, .kohms =   5, पूर्ण,
	[MCP423x_103] = अणु .wipers = 2, .max_pos = 128, .kohms =  10, पूर्ण,
	[MCP423x_503] = अणु .wipers = 2, .max_pos = 128, .kohms =  50, पूर्ण,
	[MCP423x_104] = अणु .wipers = 2, .max_pos = 128, .kohms = 100, पूर्ण,
	[MCP424x_502] = अणु .wipers = 2, .max_pos = 128, .kohms =   5, पूर्ण,
	[MCP424x_103] = अणु .wipers = 2, .max_pos = 128, .kohms =  10, पूर्ण,
	[MCP424x_503] = अणु .wipers = 2, .max_pos = 128, .kohms =  50, पूर्ण,
	[MCP424x_104] = अणु .wipers = 2, .max_pos = 128, .kohms = 100, पूर्ण,
	[MCP425x_502] = अणु .wipers = 2, .max_pos = 256, .kohms =   5, पूर्ण,
	[MCP425x_103] = अणु .wipers = 2, .max_pos = 256, .kohms =  10, पूर्ण,
	[MCP425x_503] = अणु .wipers = 2, .max_pos = 256, .kohms =  50, पूर्ण,
	[MCP425x_104] = अणु .wipers = 2, .max_pos = 256, .kohms = 100, पूर्ण,
	[MCP426x_502] = अणु .wipers = 2, .max_pos = 256, .kohms =   5, पूर्ण,
	[MCP426x_103] = अणु .wipers = 2, .max_pos = 256, .kohms =  10, पूर्ण,
	[MCP426x_503] = अणु .wipers = 2, .max_pos = 256, .kohms =  50, पूर्ण,
	[MCP426x_104] = अणु .wipers = 2, .max_pos = 256, .kohms = 100, पूर्ण,
पूर्ण;

काष्ठा mcp4131_data अणु
	काष्ठा spi_device *spi;
	स्थिर काष्ठा mcp4131_cfg *cfg;
	काष्ठा mutex lock;
	u8 buf[2] ____cacheline_aligned;
पूर्ण;

#घोषणा MCP4131_CHANNEL(ch) अणु					\
	.type = IIO_RESISTANCE,					\
	.indexed = 1,						\
	.output = 1,						\
	.channel = (ch),					\
	.info_mask_separate = BIT(IIO_CHAN_INFO_RAW),		\
	.info_mask_shared_by_type = BIT(IIO_CHAN_INFO_SCALE),	\
पूर्ण

अटल स्थिर काष्ठा iio_chan_spec mcp4131_channels[] = अणु
	MCP4131_CHANNEL(0),
	MCP4131_CHANNEL(1),
पूर्ण;

अटल पूर्णांक mcp4131_पढ़ो(काष्ठा spi_device *spi, व्योम *buf, माप_प्रकार len)
अणु
	काष्ठा spi_transfer t = अणु
		.tx_buf = buf, /* We need to send addr, cmd and 12 bits */
		.rx_buf	= buf,
		.len = len,
	पूर्ण;
	काष्ठा spi_message m;

	spi_message_init(&m);
	spi_message_add_tail(&t, &m);

	वापस spi_sync(spi, &m);
पूर्ण

अटल पूर्णांक mcp4131_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			    काष्ठा iio_chan_spec स्थिर *chan,
			    पूर्णांक *val, पूर्णांक *val2, दीर्घ mask)
अणु
	पूर्णांक err;
	काष्ठा mcp4131_data *data = iio_priv(indio_dev);
	पूर्णांक address = chan->channel;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		mutex_lock(&data->lock);

		data->buf[0] = (address << MCP4131_WIPER_SHIFT) | MCP4131_READ;
		data->buf[1] = 0;

		err = mcp4131_पढ़ो(data->spi, data->buf, 2);
		अगर (err) अणु
			mutex_unlock(&data->lock);
			वापस err;
		पूर्ण

		/* Error, bad address/command combination */
		अगर (!MCP4131_CMDERR(data->buf)) अणु
			mutex_unlock(&data->lock);
			वापस -EIO;
		पूर्ण

		*val = MCP4131_RAW(data->buf);
		mutex_unlock(&data->lock);

		वापस IIO_VAL_INT;

	हाल IIO_CHAN_INFO_SCALE:
		*val = 1000 * data->cfg->kohms;
		*val2 = data->cfg->max_pos;
		वापस IIO_VAL_FRACTIONAL;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक mcp4131_ग_लिखो_raw(काष्ठा iio_dev *indio_dev,
			     काष्ठा iio_chan_spec स्थिर *chan,
			     पूर्णांक val, पूर्णांक val2, दीर्घ mask)
अणु
	पूर्णांक err;
	काष्ठा mcp4131_data *data = iio_priv(indio_dev);
	पूर्णांक address = chan->channel << MCP4131_WIPER_SHIFT;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		अगर (val > data->cfg->max_pos || val < 0)
			वापस -EINVAL;
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	mutex_lock(&data->lock);

	data->buf[0] = address << MCP4131_WIPER_SHIFT;
	data->buf[0] |= MCP4131_WRITE | (val >> 8);
	data->buf[1] = val & 0xFF; /* 8 bits here */

	err = spi_ग_लिखो(data->spi, data->buf, 2);
	mutex_unlock(&data->lock);

	वापस err;
पूर्ण

अटल स्थिर काष्ठा iio_info mcp4131_info = अणु
	.पढ़ो_raw = mcp4131_पढ़ो_raw,
	.ग_लिखो_raw = mcp4131_ग_लिखो_raw,
पूर्ण;

अटल पूर्णांक mcp4131_probe(काष्ठा spi_device *spi)
अणु
	पूर्णांक err;
	काष्ठा device *dev = &spi->dev;
	अचिन्हित दीर्घ devid;
	काष्ठा mcp4131_data *data;
	काष्ठा iio_dev *indio_dev;

	indio_dev = devm_iio_device_alloc(dev, माप(*data));
	अगर (!indio_dev)
		वापस -ENOMEM;

	data = iio_priv(indio_dev);
	spi_set_drvdata(spi, indio_dev);
	data->spi = spi;
	data->cfg = device_get_match_data(&spi->dev);
	अगर (!data->cfg) अणु
		devid = spi_get_device_id(spi)->driver_data;
		data->cfg = &mcp4131_cfg[devid];
	पूर्ण

	mutex_init(&data->lock);

	indio_dev->info = &mcp4131_info;
	indio_dev->channels = mcp4131_channels;
	indio_dev->num_channels = data->cfg->wipers;
	indio_dev->name = spi_get_device_id(spi)->name;

	err = devm_iio_device_रेजिस्टर(dev, indio_dev);
	अगर (err) अणु
		dev_info(&spi->dev, "Unable to register %s\n", indio_dev->name);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id mcp4131_dt_ids[] = अणु
	अणु .compatible = "microchip,mcp4131-502",
		.data = &mcp4131_cfg[MCP413x_502] पूर्ण,
	अणु .compatible = "microchip,mcp4131-103",
		.data = &mcp4131_cfg[MCP413x_103] पूर्ण,
	अणु .compatible = "microchip,mcp4131-503",
		.data = &mcp4131_cfg[MCP413x_503] पूर्ण,
	अणु .compatible = "microchip,mcp4131-104",
		.data = &mcp4131_cfg[MCP413x_104] पूर्ण,
	अणु .compatible = "microchip,mcp4132-502",
		.data = &mcp4131_cfg[MCP413x_502] पूर्ण,
	अणु .compatible = "microchip,mcp4132-103",
		.data = &mcp4131_cfg[MCP413x_103] पूर्ण,
	अणु .compatible = "microchip,mcp4132-503",
		.data = &mcp4131_cfg[MCP413x_503] पूर्ण,
	अणु .compatible = "microchip,mcp4132-104",
		.data = &mcp4131_cfg[MCP413x_104] पूर्ण,
	अणु .compatible = "microchip,mcp4141-502",
		.data = &mcp4131_cfg[MCP414x_502] पूर्ण,
	अणु .compatible = "microchip,mcp4141-103",
		.data = &mcp4131_cfg[MCP414x_103] पूर्ण,
	अणु .compatible = "microchip,mcp4141-503",
		.data = &mcp4131_cfg[MCP414x_503] पूर्ण,
	अणु .compatible = "microchip,mcp4141-104",
		.data = &mcp4131_cfg[MCP414x_104] पूर्ण,
	अणु .compatible = "microchip,mcp4142-502",
		.data = &mcp4131_cfg[MCP414x_502] पूर्ण,
	अणु .compatible = "microchip,mcp4142-103",
		.data = &mcp4131_cfg[MCP414x_103] पूर्ण,
	अणु .compatible = "microchip,mcp4142-503",
		.data = &mcp4131_cfg[MCP414x_503] पूर्ण,
	अणु .compatible = "microchip,mcp4142-104",
		.data = &mcp4131_cfg[MCP414x_104] पूर्ण,
	अणु .compatible = "microchip,mcp4151-502",
		.data = &mcp4131_cfg[MCP415x_502] पूर्ण,
	अणु .compatible = "microchip,mcp4151-103",
		.data = &mcp4131_cfg[MCP415x_103] पूर्ण,
	अणु .compatible = "microchip,mcp4151-503",
		.data = &mcp4131_cfg[MCP415x_503] पूर्ण,
	अणु .compatible = "microchip,mcp4151-104",
		.data = &mcp4131_cfg[MCP415x_104] पूर्ण,
	अणु .compatible = "microchip,mcp4152-502",
		.data = &mcp4131_cfg[MCP415x_502] पूर्ण,
	अणु .compatible = "microchip,mcp4152-103",
		.data = &mcp4131_cfg[MCP415x_103] पूर्ण,
	अणु .compatible = "microchip,mcp4152-503",
		.data = &mcp4131_cfg[MCP415x_503] पूर्ण,
	अणु .compatible = "microchip,mcp4152-104",
		.data = &mcp4131_cfg[MCP415x_104] पूर्ण,
	अणु .compatible = "microchip,mcp4161-502",
		.data = &mcp4131_cfg[MCP416x_502] पूर्ण,
	अणु .compatible = "microchip,mcp4161-103",
		.data = &mcp4131_cfg[MCP416x_103] पूर्ण,
	अणु .compatible = "microchip,mcp4161-503",
		.data = &mcp4131_cfg[MCP416x_503] पूर्ण,
	अणु .compatible = "microchip,mcp4161-104",
		.data = &mcp4131_cfg[MCP416x_104] पूर्ण,
	अणु .compatible = "microchip,mcp4162-502",
		.data = &mcp4131_cfg[MCP416x_502] पूर्ण,
	अणु .compatible = "microchip,mcp4162-103",
		.data = &mcp4131_cfg[MCP416x_103] पूर्ण,
	अणु .compatible = "microchip,mcp4162-503",
		.data = &mcp4131_cfg[MCP416x_503] पूर्ण,
	अणु .compatible = "microchip,mcp4162-104",
		.data = &mcp4131_cfg[MCP416x_104] पूर्ण,
	अणु .compatible = "microchip,mcp4231-502",
		.data = &mcp4131_cfg[MCP423x_502] पूर्ण,
	अणु .compatible = "microchip,mcp4231-103",
		.data = &mcp4131_cfg[MCP423x_103] पूर्ण,
	अणु .compatible = "microchip,mcp4231-503",
		.data = &mcp4131_cfg[MCP423x_503] पूर्ण,
	अणु .compatible = "microchip,mcp4231-104",
		.data = &mcp4131_cfg[MCP423x_104] पूर्ण,
	अणु .compatible = "microchip,mcp4232-502",
		.data = &mcp4131_cfg[MCP423x_502] पूर्ण,
	अणु .compatible = "microchip,mcp4232-103",
		.data = &mcp4131_cfg[MCP423x_103] पूर्ण,
	अणु .compatible = "microchip,mcp4232-503",
		.data = &mcp4131_cfg[MCP423x_503] पूर्ण,
	अणु .compatible = "microchip,mcp4232-104",
		.data = &mcp4131_cfg[MCP423x_104] पूर्ण,
	अणु .compatible = "microchip,mcp4241-502",
		.data = &mcp4131_cfg[MCP424x_502] पूर्ण,
	अणु .compatible = "microchip,mcp4241-103",
		.data = &mcp4131_cfg[MCP424x_103] पूर्ण,
	अणु .compatible = "microchip,mcp4241-503",
		.data = &mcp4131_cfg[MCP424x_503] पूर्ण,
	अणु .compatible = "microchip,mcp4241-104",
		.data = &mcp4131_cfg[MCP424x_104] पूर्ण,
	अणु .compatible = "microchip,mcp4242-502",
		.data = &mcp4131_cfg[MCP424x_502] पूर्ण,
	अणु .compatible = "microchip,mcp4242-103",
		.data = &mcp4131_cfg[MCP424x_103] पूर्ण,
	अणु .compatible = "microchip,mcp4242-503",
		.data = &mcp4131_cfg[MCP424x_503] पूर्ण,
	अणु .compatible = "microchip,mcp4242-104",
		.data = &mcp4131_cfg[MCP424x_104] पूर्ण,
	अणु .compatible = "microchip,mcp4251-502",
		.data = &mcp4131_cfg[MCP425x_502] पूर्ण,
	अणु .compatible = "microchip,mcp4251-103",
		.data = &mcp4131_cfg[MCP425x_103] पूर्ण,
	अणु .compatible = "microchip,mcp4251-503",
		.data = &mcp4131_cfg[MCP425x_503] पूर्ण,
	अणु .compatible = "microchip,mcp4251-104",
		.data = &mcp4131_cfg[MCP425x_104] पूर्ण,
	अणु .compatible = "microchip,mcp4252-502",
		.data = &mcp4131_cfg[MCP425x_502] पूर्ण,
	अणु .compatible = "microchip,mcp4252-103",
		.data = &mcp4131_cfg[MCP425x_103] पूर्ण,
	अणु .compatible = "microchip,mcp4252-503",
		.data = &mcp4131_cfg[MCP425x_503] पूर्ण,
	अणु .compatible = "microchip,mcp4252-104",
		.data = &mcp4131_cfg[MCP425x_104] पूर्ण,
	अणु .compatible = "microchip,mcp4261-502",
		.data = &mcp4131_cfg[MCP426x_502] पूर्ण,
	अणु .compatible = "microchip,mcp4261-103",
		.data = &mcp4131_cfg[MCP426x_103] पूर्ण,
	अणु .compatible = "microchip,mcp4261-503",
		.data = &mcp4131_cfg[MCP426x_503] पूर्ण,
	अणु .compatible = "microchip,mcp4261-104",
		.data = &mcp4131_cfg[MCP426x_104] पूर्ण,
	अणु .compatible = "microchip,mcp4262-502",
		.data = &mcp4131_cfg[MCP426x_502] पूर्ण,
	अणु .compatible = "microchip,mcp4262-103",
		.data = &mcp4131_cfg[MCP426x_103] पूर्ण,
	अणु .compatible = "microchip,mcp4262-503",
		.data = &mcp4131_cfg[MCP426x_503] पूर्ण,
	अणु .compatible = "microchip,mcp4262-104",
		.data = &mcp4131_cfg[MCP426x_104] पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, mcp4131_dt_ids);

अटल स्थिर काष्ठा spi_device_id mcp4131_id[] = अणु
	अणु "mcp4131-502", MCP413x_502 पूर्ण,
	अणु "mcp4131-103", MCP413x_103 पूर्ण,
	अणु "mcp4131-503", MCP413x_503 पूर्ण,
	अणु "mcp4131-104", MCP413x_104 पूर्ण,
	अणु "mcp4132-502", MCP413x_502 पूर्ण,
	अणु "mcp4132-103", MCP413x_103 पूर्ण,
	अणु "mcp4132-503", MCP413x_503 पूर्ण,
	अणु "mcp4132-104", MCP413x_104 पूर्ण,
	अणु "mcp4141-502", MCP414x_502 पूर्ण,
	अणु "mcp4141-103", MCP414x_103 पूर्ण,
	अणु "mcp4141-503", MCP414x_503 पूर्ण,
	अणु "mcp4141-104", MCP414x_104 पूर्ण,
	अणु "mcp4142-502", MCP414x_502 पूर्ण,
	अणु "mcp4142-103", MCP414x_103 पूर्ण,
	अणु "mcp4142-503", MCP414x_503 पूर्ण,
	अणु "mcp4142-104", MCP414x_104 पूर्ण,
	अणु "mcp4151-502", MCP415x_502 पूर्ण,
	अणु "mcp4151-103", MCP415x_103 पूर्ण,
	अणु "mcp4151-503", MCP415x_503 पूर्ण,
	अणु "mcp4151-104", MCP415x_104 पूर्ण,
	अणु "mcp4152-502", MCP415x_502 पूर्ण,
	अणु "mcp4152-103", MCP415x_103 पूर्ण,
	अणु "mcp4152-503", MCP415x_503 पूर्ण,
	अणु "mcp4152-104", MCP415x_104 पूर्ण,
	अणु "mcp4161-502", MCP416x_502 पूर्ण,
	अणु "mcp4161-103", MCP416x_103 पूर्ण,
	अणु "mcp4161-503", MCP416x_503 पूर्ण,
	अणु "mcp4161-104", MCP416x_104 पूर्ण,
	अणु "mcp4162-502", MCP416x_502 पूर्ण,
	अणु "mcp4162-103", MCP416x_103 पूर्ण,
	अणु "mcp4162-503", MCP416x_503 पूर्ण,
	अणु "mcp4162-104", MCP416x_104 पूर्ण,
	अणु "mcp4231-502", MCP423x_502 पूर्ण,
	अणु "mcp4231-103", MCP423x_103 पूर्ण,
	अणु "mcp4231-503", MCP423x_503 पूर्ण,
	अणु "mcp4231-104", MCP423x_104 पूर्ण,
	अणु "mcp4232-502", MCP423x_502 पूर्ण,
	अणु "mcp4232-103", MCP423x_103 पूर्ण,
	अणु "mcp4232-503", MCP423x_503 पूर्ण,
	अणु "mcp4232-104", MCP423x_104 पूर्ण,
	अणु "mcp4241-502", MCP424x_502 पूर्ण,
	अणु "mcp4241-103", MCP424x_103 पूर्ण,
	अणु "mcp4241-503", MCP424x_503 पूर्ण,
	अणु "mcp4241-104", MCP424x_104 पूर्ण,
	अणु "mcp4242-502", MCP424x_502 पूर्ण,
	अणु "mcp4242-103", MCP424x_103 पूर्ण,
	अणु "mcp4242-503", MCP424x_503 पूर्ण,
	अणु "mcp4242-104", MCP424x_104 पूर्ण,
	अणु "mcp4251-502", MCP425x_502 पूर्ण,
	अणु "mcp4251-103", MCP425x_103 पूर्ण,
	अणु "mcp4251-503", MCP425x_503 पूर्ण,
	अणु "mcp4251-104", MCP425x_104 पूर्ण,
	अणु "mcp4252-502", MCP425x_502 पूर्ण,
	अणु "mcp4252-103", MCP425x_103 पूर्ण,
	अणु "mcp4252-503", MCP425x_503 पूर्ण,
	अणु "mcp4252-104", MCP425x_104 पूर्ण,
	अणु "mcp4261-502", MCP426x_502 पूर्ण,
	अणु "mcp4261-103", MCP426x_103 पूर्ण,
	अणु "mcp4261-503", MCP426x_503 पूर्ण,
	अणु "mcp4261-104", MCP426x_104 पूर्ण,
	अणु "mcp4262-502", MCP426x_502 पूर्ण,
	अणु "mcp4262-103", MCP426x_103 पूर्ण,
	अणु "mcp4262-503", MCP426x_503 पूर्ण,
	अणु "mcp4262-104", MCP426x_104 पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(spi, mcp4131_id);

अटल काष्ठा spi_driver mcp4131_driver = अणु
	.driver = अणु
		.name	= "mcp4131",
		.of_match_table = mcp4131_dt_ids,
	पूर्ण,
	.probe		= mcp4131_probe,
	.id_table	= mcp4131_id,
पूर्ण;

module_spi_driver(mcp4131_driver);

MODULE_AUTHOR("Slawomir Stepien <sst@poczta.fm>");
MODULE_DESCRIPTION("MCP4131 digital potentiometer");
MODULE_LICENSE("GPL v2");
