<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2016 Golden Delicious Comp. GmbH&Co. KG
 *	Nikolaus Schaller <hns@goldelico.com>
 */

#समावेश <linux/i2c.h>
#समावेश <linux/iio/iपन.स>
#समावेश "tsc2007.h"

काष्ठा tsc2007_iio अणु
	काष्ठा tsc2007 *ts;
पूर्ण;

#घोषणा TSC2007_CHAN_IIO(_chan, _name, _type, _chan_info) \
अणु \
	.datasheet_name = _name, \
	.type = _type, \
	.info_mask_separate = BIT(IIO_CHAN_INFO_RAW) |	\
			BIT(_chan_info), \
	.indexed = 1, \
	.channel = _chan, \
पूर्ण

अटल स्थिर काष्ठा iio_chan_spec tsc2007_iio_channel[] = अणु
	TSC2007_CHAN_IIO(0, "x", IIO_VOLTAGE, IIO_CHAN_INFO_RAW),
	TSC2007_CHAN_IIO(1, "y", IIO_VOLTAGE, IIO_CHAN_INFO_RAW),
	TSC2007_CHAN_IIO(2, "z1", IIO_VOLTAGE, IIO_CHAN_INFO_RAW),
	TSC2007_CHAN_IIO(3, "z2", IIO_VOLTAGE, IIO_CHAN_INFO_RAW),
	TSC2007_CHAN_IIO(4, "adc", IIO_VOLTAGE, IIO_CHAN_INFO_RAW),
	TSC2007_CHAN_IIO(5, "rt", IIO_VOLTAGE, IIO_CHAN_INFO_RAW), /* Ohms? */
	TSC2007_CHAN_IIO(6, "pen", IIO_PRESSURE, IIO_CHAN_INFO_RAW),
	TSC2007_CHAN_IIO(7, "temp0", IIO_TEMP, IIO_CHAN_INFO_RAW),
	TSC2007_CHAN_IIO(8, "temp1", IIO_TEMP, IIO_CHAN_INFO_RAW),
पूर्ण;

अटल पूर्णांक tsc2007_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			    काष्ठा iio_chan_spec स्थिर *chan,
			    पूर्णांक *val, पूर्णांक *val2, दीर्घ mask)
अणु
	काष्ठा tsc2007_iio *iio = iio_priv(indio_dev);
	काष्ठा tsc2007 *tsc = iio->ts;
	पूर्णांक adc_chan = chan->channel;
	पूर्णांक ret = 0;

	अगर (adc_chan >= ARRAY_SIZE(tsc2007_iio_channel))
		वापस -EINVAL;

	अगर (mask != IIO_CHAN_INFO_RAW)
		वापस -EINVAL;

	mutex_lock(&tsc->mlock);

	चयन (chan->channel) अणु
	हाल 0:
		*val = tsc2007_xfer(tsc, READ_X);
		अवरोध;
	हाल 1:
		*val = tsc2007_xfer(tsc, READ_Y);
		अवरोध;
	हाल 2:
		*val = tsc2007_xfer(tsc, READ_Z1);
		अवरोध;
	हाल 3:
		*val = tsc2007_xfer(tsc, READ_Z2);
		अवरोध;
	हाल 4:
		*val = tsc2007_xfer(tsc, (ADC_ON_12BIT | TSC2007_MEASURE_AUX));
		अवरोध;
	हाल 5: अणु
		काष्ठा ts_event tc;

		tc.x = tsc2007_xfer(tsc, READ_X);
		tc.z1 = tsc2007_xfer(tsc, READ_Z1);
		tc.z2 = tsc2007_xfer(tsc, READ_Z2);
		*val = tsc2007_calculate_resistance(tsc, &tc);
		अवरोध;
	पूर्ण
	हाल 6:
		*val = tsc2007_is_pen_करोwn(tsc);
		अवरोध;
	हाल 7:
		*val = tsc2007_xfer(tsc,
				    (ADC_ON_12BIT | TSC2007_MEASURE_TEMP0));
		अवरोध;
	हाल 8:
		*val = tsc2007_xfer(tsc,
				    (ADC_ON_12BIT | TSC2007_MEASURE_TEMP1));
		अवरोध;
	पूर्ण

	/* Prepare क्रम next touch पढ़ोing - घातer करोwn ADC, enable PENIRQ */
	tsc2007_xfer(tsc, PWRDOWN);

	mutex_unlock(&tsc->mlock);

	ret = IIO_VAL_INT;

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा iio_info tsc2007_iio_info = अणु
	.पढ़ो_raw = tsc2007_पढ़ो_raw,
पूर्ण;

पूर्णांक tsc2007_iio_configure(काष्ठा tsc2007 *ts)
अणु
	काष्ठा iio_dev *indio_dev;
	काष्ठा tsc2007_iio *iio;
	पूर्णांक error;

	indio_dev = devm_iio_device_alloc(&ts->client->dev, माप(*iio));
	अगर (!indio_dev) अणु
		dev_err(&ts->client->dev, "iio_device_alloc failed\n");
		वापस -ENOMEM;
	पूर्ण

	iio = iio_priv(indio_dev);
	iio->ts = ts;

	indio_dev->name = "tsc2007";
	indio_dev->info = &tsc2007_iio_info;
	indio_dev->modes = INDIO_सूचीECT_MODE;
	indio_dev->channels = tsc2007_iio_channel;
	indio_dev->num_channels = ARRAY_SIZE(tsc2007_iio_channel);

	error = devm_iio_device_रेजिस्टर(&ts->client->dev, indio_dev);
	अगर (error) अणु
		dev_err(&ts->client->dev,
			"iio_device_register() failed: %d\n", error);
		वापस error;
	पूर्ण

	वापस 0;
पूर्ण
