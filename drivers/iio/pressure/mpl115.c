<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * mpl115.c - Support क्रम Freescale MPL115A pressure/temperature sensor
 *
 * Copyright (c) 2014 Peter Meerwald <pmeerw@pmeerw.net>
 *
 * TODO: shutकरोwn pin
 */

#समावेश <linux/module.h>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/delay.h>

#समावेश "mpl115.h"

#घोषणा MPL115_PADC 0x00 /* pressure ADC output value, MSB first, 10 bit */
#घोषणा MPL115_TADC 0x02 /* temperature ADC output value, MSB first, 10 bit */
#घोषणा MPL115_A0 0x04 /* 12 bit पूर्णांकeger, 3 bit fraction */
#घोषणा MPL115_B1 0x06 /* 2 bit पूर्णांकeger, 13 bit fraction */
#घोषणा MPL115_B2 0x08 /* 1 bit पूर्णांकeger, 14 bit fraction */
#घोषणा MPL115_C12 0x0a /* 0 bit पूर्णांकeger, 13 bit fraction */
#घोषणा MPL115_CONVERT 0x12 /* convert temperature and pressure */

काष्ठा mpl115_data अणु
	काष्ठा device *dev;
	काष्ठा mutex lock;
	s16 a0;
	s16 b1, b2;
	s16 c12;
	स्थिर काष्ठा mpl115_ops *ops;
पूर्ण;

अटल पूर्णांक mpl115_request(काष्ठा mpl115_data *data)
अणु
	पूर्णांक ret = data->ops->ग_लिखो(data->dev, MPL115_CONVERT, 0);

	अगर (ret < 0)
		वापस ret;

	usleep_range(3000, 4000);

	वापस 0;
पूर्ण

अटल पूर्णांक mpl115_comp_pressure(काष्ठा mpl115_data *data, पूर्णांक *val, पूर्णांक *val2)
अणु
	पूर्णांक ret;
	u16 padc, tadc;
	पूर्णांक a1, y1, pcomp;
	अचिन्हित kpa;

	mutex_lock(&data->lock);
	ret = mpl115_request(data);
	अगर (ret < 0)
		जाओ करोne;

	ret = data->ops->पढ़ो(data->dev, MPL115_PADC);
	अगर (ret < 0)
		जाओ करोne;
	padc = ret >> 6;

	ret = data->ops->पढ़ो(data->dev, MPL115_TADC);
	अगर (ret < 0)
		जाओ करोne;
	tadc = ret >> 6;

	/* see Freescale AN3785 */
	a1 = data->b1 + ((data->c12 * tadc) >> 11);
	y1 = (data->a0 << 10) + a1 * padc;

	/* compensated pressure with 4 fractional bits */
	pcomp = (y1 + ((data->b2 * (पूर्णांक) tadc) >> 1)) >> 9;

	kpa = pcomp * (115 - 50) / 1023 + (50 << 4);
	*val = kpa >> 4;
	*val2 = (kpa & 15) * (1000000 >> 4);
करोne:
	mutex_unlock(&data->lock);
	वापस ret;
पूर्ण

अटल पूर्णांक mpl115_पढ़ो_temp(काष्ठा mpl115_data *data)
अणु
	पूर्णांक ret;

	mutex_lock(&data->lock);
	ret = mpl115_request(data);
	अगर (ret < 0)
		जाओ करोne;
	ret = data->ops->पढ़ो(data->dev, MPL115_TADC);
करोne:
	mutex_unlock(&data->lock);
	वापस ret;
पूर्ण

अटल पूर्णांक mpl115_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			    काष्ठा iio_chan_spec स्थिर *chan,
			    पूर्णांक *val, पूर्णांक *val2, दीर्घ mask)
अणु
	काष्ठा mpl115_data *data = iio_priv(indio_dev);
	पूर्णांक ret;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_PROCESSED:
		ret = mpl115_comp_pressure(data, val, val2);
		अगर (ret < 0)
			वापस ret;
		वापस IIO_VAL_INT_PLUS_MICRO;
	हाल IIO_CHAN_INFO_RAW:
		/* temperature -5.35 C / LSB, 472 LSB is 25 C */
		ret = mpl115_पढ़ो_temp(data);
		अगर (ret < 0)
			वापस ret;
		*val = ret >> 6;
		वापस IIO_VAL_INT;
	हाल IIO_CHAN_INFO_OFFSET:
		*val = -605;
		*val2 = 750000;
		वापस IIO_VAL_INT_PLUS_MICRO;
	हाल IIO_CHAN_INFO_SCALE:
		*val = -186;
		*val2 = 915888;
		वापस IIO_VAL_INT_PLUS_MICRO;
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल स्थिर काष्ठा iio_chan_spec mpl115_channels[] = अणु
	अणु
		.type = IIO_PRESSURE,
		.info_mask_separate = BIT(IIO_CHAN_INFO_PROCESSED),
	पूर्ण,
	अणु
		.type = IIO_TEMP,
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW),
		.info_mask_shared_by_type =
			BIT(IIO_CHAN_INFO_OFFSET) | BIT(IIO_CHAN_INFO_SCALE),
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा iio_info mpl115_info = अणु
	.पढ़ो_raw = &mpl115_पढ़ो_raw,
पूर्ण;

पूर्णांक mpl115_probe(काष्ठा device *dev, स्थिर अक्षर *name,
			स्थिर काष्ठा mpl115_ops *ops)
अणु
	काष्ठा mpl115_data *data;
	काष्ठा iio_dev *indio_dev;
	पूर्णांक ret;

	indio_dev = devm_iio_device_alloc(dev, माप(*data));
	अगर (!indio_dev)
		वापस -ENOMEM;

	data = iio_priv(indio_dev);
	data->dev = dev;
	data->ops = ops;
	mutex_init(&data->lock);

	indio_dev->info = &mpl115_info;
	indio_dev->name = name;
	indio_dev->modes = INDIO_सूचीECT_MODE;
	indio_dev->channels = mpl115_channels;
	indio_dev->num_channels = ARRAY_SIZE(mpl115_channels);

	ret = data->ops->init(data->dev);
	अगर (ret)
		वापस ret;

	ret = data->ops->पढ़ो(data->dev, MPL115_A0);
	अगर (ret < 0)
		वापस ret;
	data->a0 = ret;
	ret = data->ops->पढ़ो(data->dev, MPL115_B1);
	अगर (ret < 0)
		वापस ret;
	data->b1 = ret;
	ret = data->ops->पढ़ो(data->dev, MPL115_B2);
	अगर (ret < 0)
		वापस ret;
	data->b2 = ret;
	ret = data->ops->पढ़ो(data->dev, MPL115_C12);
	अगर (ret < 0)
		वापस ret;
	data->c12 = ret;

	वापस devm_iio_device_रेजिस्टर(dev, indio_dev);
पूर्ण
EXPORT_SYMBOL_GPL(mpl115_probe);

MODULE_AUTHOR("Peter Meerwald <pmeerw@pmeerw.net>");
MODULE_DESCRIPTION("Freescale MPL115 pressure/temperature driver");
MODULE_LICENSE("GPL");
