<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  max517.c - Support क्रम Maxim MAX517, MAX518 and MAX519
 *
 *  Copyright (C) 2010, 2011 Roland Stigge <stigge@antcom.de>
 */

#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/i2c.h>
#समावेश <linux/err.h>

#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/sysfs.h>
#समावेश <linux/iio/dac/max517.h>

#घोषणा MAX517_DRV_NAME	"max517"

/* Commands */
#घोषणा COMMAND_CHANNEL0	0x00
#घोषणा COMMAND_CHANNEL1	0x01 /* क्रम MAX518 and MAX519 */
#घोषणा COMMAND_PD		0x08 /* Power Down */

क्रमागत max517_device_ids अणु
	ID_MAX517,
	ID_MAX518,
	ID_MAX519,
	ID_MAX520,
	ID_MAX521,
पूर्ण;

काष्ठा max517_data अणु
	काष्ठा i2c_client	*client;
	अचिन्हित लघु		vref_mv[8];
पूर्ण;

/*
 * channel: bit 0: channel 1
 *          bit 1: channel 2
 * (this way, it's possible to set both channels at once)
 */
अटल पूर्णांक max517_set_value(काष्ठा iio_dev *indio_dev,
	दीर्घ val, पूर्णांक channel)
अणु
	काष्ठा max517_data *data = iio_priv(indio_dev);
	काष्ठा i2c_client *client = data->client;
	u8 outbuf[2];
	पूर्णांक res;

	अगर (val < 0 || val > 255)
		वापस -EINVAL;

	outbuf[0] = channel;
	outbuf[1] = val;

	res = i2c_master_send(client, outbuf, 2);
	अगर (res < 0)
		वापस res;
	अन्यथा अगर (res != 2)
		वापस -EIO;
	अन्यथा
		वापस 0;
पूर्ण

अटल पूर्णांक max517_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			   काष्ठा iio_chan_spec स्थिर *chan,
			   पूर्णांक *val,
			   पूर्णांक *val2,
			   दीर्घ m)
अणु
	काष्ठा max517_data *data = iio_priv(indio_dev);

	चयन (m) अणु
	हाल IIO_CHAN_INFO_SCALE:
		/* Corresponds to Vref / 2^(bits) */
		*val = data->vref_mv[chan->channel];
		*val2 = 8;
		वापस IIO_VAL_FRACTIONAL_LOG2;
	शेष:
		अवरोध;
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक max517_ग_लिखो_raw(काष्ठा iio_dev *indio_dev,
	काष्ठा iio_chan_spec स्थिर *chan, पूर्णांक val, पूर्णांक val2, दीर्घ mask)
अणु
	पूर्णांक ret;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		ret = max517_set_value(indio_dev, val, chan->channel);
		अवरोध;
	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक __maybe_unused max517_suspend(काष्ठा device *dev)
अणु
	u8 outbuf = COMMAND_PD;

	वापस i2c_master_send(to_i2c_client(dev), &outbuf, 1);
पूर्ण

अटल पूर्णांक __maybe_unused max517_resume(काष्ठा device *dev)
अणु
	u8 outbuf = 0;

	वापस i2c_master_send(to_i2c_client(dev), &outbuf, 1);
पूर्ण

अटल SIMPLE_DEV_PM_OPS(max517_pm_ops, max517_suspend, max517_resume);

अटल स्थिर काष्ठा iio_info max517_info = अणु
	.पढ़ो_raw = max517_पढ़ो_raw,
	.ग_लिखो_raw = max517_ग_लिखो_raw,
पूर्ण;

#घोषणा MAX517_CHANNEL(chan) अणु				\
	.type = IIO_VOLTAGE,				\
	.indexed = 1,					\
	.output = 1,					\
	.channel = (chan),				\
	.info_mask_separate = BIT(IIO_CHAN_INFO_RAW) |	\
	BIT(IIO_CHAN_INFO_SCALE),			\
पूर्ण

अटल स्थिर काष्ठा iio_chan_spec max517_channels[] = अणु
	MAX517_CHANNEL(0),
	MAX517_CHANNEL(1),
	MAX517_CHANNEL(2),
	MAX517_CHANNEL(3),
	MAX517_CHANNEL(4),
	MAX517_CHANNEL(5),
	MAX517_CHANNEL(6),
	MAX517_CHANNEL(7),
पूर्ण;

अटल पूर्णांक max517_probe(काष्ठा i2c_client *client,
			स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा max517_data *data;
	काष्ठा iio_dev *indio_dev;
	काष्ठा max517_platक्रमm_data *platक्रमm_data = client->dev.platक्रमm_data;
	पूर्णांक chan;

	indio_dev = devm_iio_device_alloc(&client->dev, माप(*data));
	अगर (!indio_dev)
		वापस -ENOMEM;
	data = iio_priv(indio_dev);
	data->client = client;

	चयन (id->driver_data) अणु
	हाल ID_MAX521:
		indio_dev->num_channels = 8;
		अवरोध;
	हाल ID_MAX520:
		indio_dev->num_channels = 4;
		अवरोध;
	हाल ID_MAX519:
	हाल ID_MAX518:
		indio_dev->num_channels = 2;
		अवरोध;
	शेष:  /* single channel क्रम MAX517 */
		indio_dev->num_channels = 1;
		अवरोध;
	पूर्ण
	indio_dev->channels = max517_channels;
	indio_dev->modes = INDIO_सूचीECT_MODE;
	indio_dev->info = &max517_info;

	/*
	 * Reference voltage on MAX518 and शेष is 5V, अन्यथा take vref_mv
	 * from platक्रमm_data
	 */
	क्रम (chan = 0; chan < indio_dev->num_channels; chan++) अणु
		अगर (id->driver_data == ID_MAX518 || !platक्रमm_data)
			data->vref_mv[chan] = 5000; /* mV */
		अन्यथा
			data->vref_mv[chan] = platक्रमm_data->vref_mv[chan];
	पूर्ण

	वापस devm_iio_device_रेजिस्टर(&client->dev, indio_dev);
पूर्ण

अटल स्थिर काष्ठा i2c_device_id max517_id[] = अणु
	अणु "max517", ID_MAX517 पूर्ण,
	अणु "max518", ID_MAX518 पूर्ण,
	अणु "max519", ID_MAX519 पूर्ण,
	अणु "max520", ID_MAX520 पूर्ण,
	अणु "max521", ID_MAX521 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, max517_id);

अटल काष्ठा i2c_driver max517_driver = अणु
	.driver = अणु
		.name	= MAX517_DRV_NAME,
		.pm	= &max517_pm_ops,
	पूर्ण,
	.probe		= max517_probe,
	.id_table	= max517_id,
पूर्ण;
module_i2c_driver(max517_driver);

MODULE_AUTHOR("Roland Stigge <stigge@antcom.de>");
MODULE_DESCRIPTION("MAX517/518/519/520/521 8-bit DAC");
MODULE_LICENSE("GPL");
