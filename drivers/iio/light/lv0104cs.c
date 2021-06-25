<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * lv0104cs.c: LV0104CS Ambient Light Sensor Driver
 *
 * Copyright (C) 2018
 * Author: Jeff LaBundy <jeff@labundy.com>
 *
 * 7-bit I2C slave address: 0x13
 *
 * Link to data sheet: https://www.onsemi.com/pub/Collateral/LV0104CS-D.PDF
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/i2c.h>
#समावेश <linux/err.h>
#समावेश <linux/mutex.h>
#समावेश <linux/delay.h>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/sysfs.h>

#घोषणा LV0104CS_REGVAL_MEASURE		0xE0
#घोषणा LV0104CS_REGVAL_SLEEP		0x00

#घोषणा LV0104CS_SCALE_0_25X		0
#घोषणा LV0104CS_SCALE_1X		1
#घोषणा LV0104CS_SCALE_2X		2
#घोषणा LV0104CS_SCALE_8X		3
#घोषणा LV0104CS_SCALE_SHIFT		3

#घोषणा LV0104CS_INTEG_12_5MS		0
#घोषणा LV0104CS_INTEG_100MS		1
#घोषणा LV0104CS_INTEG_200MS		2
#घोषणा LV0104CS_INTEG_SHIFT		1

#घोषणा LV0104CS_CALIBSCALE_UNITY	31

काष्ठा lv0104cs_निजी अणु
	काष्ठा i2c_client *client;
	काष्ठा mutex lock;
	u8 calibscale;
	u8 scale;
	u8 पूर्णांक_समय;
पूर्ण;

काष्ठा lv0104cs_mapping अणु
	पूर्णांक val;
	पूर्णांक val2;
	u8 regval;
पूर्ण;

अटल स्थिर काष्ठा lv0104cs_mapping lv0104cs_calibscales[] = अणु
	अणु 0, 666666, 0x81 पूर्ण,
	अणु 0, 800000, 0x82 पूर्ण,
	अणु 0, 857142, 0x83 पूर्ण,
	अणु 0, 888888, 0x84 पूर्ण,
	अणु 0, 909090, 0x85 पूर्ण,
	अणु 0, 923076, 0x86 पूर्ण,
	अणु 0, 933333, 0x87 पूर्ण,
	अणु 0, 941176, 0x88 पूर्ण,
	अणु 0, 947368, 0x89 पूर्ण,
	अणु 0, 952380, 0x8A पूर्ण,
	अणु 0, 956521, 0x8B पूर्ण,
	अणु 0, 960000, 0x8C पूर्ण,
	अणु 0, 962962, 0x8D पूर्ण,
	अणु 0, 965517, 0x8E पूर्ण,
	अणु 0, 967741, 0x8F पूर्ण,
	अणु 0, 969696, 0x90 पूर्ण,
	अणु 0, 971428, 0x91 पूर्ण,
	अणु 0, 972972, 0x92 पूर्ण,
	अणु 0, 974358, 0x93 पूर्ण,
	अणु 0, 975609, 0x94 पूर्ण,
	अणु 0, 976744, 0x95 पूर्ण,
	अणु 0, 977777, 0x96 पूर्ण,
	अणु 0, 978723, 0x97 पूर्ण,
	अणु 0, 979591, 0x98 पूर्ण,
	अणु 0, 980392, 0x99 पूर्ण,
	अणु 0, 981132, 0x9A पूर्ण,
	अणु 0, 981818, 0x9B पूर्ण,
	अणु 0, 982456, 0x9C पूर्ण,
	अणु 0, 983050, 0x9D पूर्ण,
	अणु 0, 983606, 0x9E पूर्ण,
	अणु 0, 984126, 0x9F पूर्ण,
	अणु 1, 0, 0x80 पूर्ण,
	अणु 1, 16129, 0xBF पूर्ण,
	अणु 1, 16666, 0xBE पूर्ण,
	अणु 1, 17241, 0xBD पूर्ण,
	अणु 1, 17857, 0xBC पूर्ण,
	अणु 1, 18518, 0xBB पूर्ण,
	अणु 1, 19230, 0xBA पूर्ण,
	अणु 1, 20000, 0xB9 पूर्ण,
	अणु 1, 20833, 0xB8 पूर्ण,
	अणु 1, 21739, 0xB7 पूर्ण,
	अणु 1, 22727, 0xB6 पूर्ण,
	अणु 1, 23809, 0xB5 पूर्ण,
	अणु 1, 24999, 0xB4 पूर्ण,
	अणु 1, 26315, 0xB3 पूर्ण,
	अणु 1, 27777, 0xB2 पूर्ण,
	अणु 1, 29411, 0xB1 पूर्ण,
	अणु 1, 31250, 0xB0 पूर्ण,
	अणु 1, 33333, 0xAF पूर्ण,
	अणु 1, 35714, 0xAE पूर्ण,
	अणु 1, 38461, 0xAD पूर्ण,
	अणु 1, 41666, 0xAC पूर्ण,
	अणु 1, 45454, 0xAB पूर्ण,
	अणु 1, 50000, 0xAA पूर्ण,
	अणु 1, 55555, 0xA9 पूर्ण,
	अणु 1, 62500, 0xA8 पूर्ण,
	अणु 1, 71428, 0xA7 पूर्ण,
	अणु 1, 83333, 0xA6 पूर्ण,
	अणु 1, 100000, 0xA5 पूर्ण,
	अणु 1, 125000, 0xA4 पूर्ण,
	अणु 1, 166666, 0xA3 पूर्ण,
	अणु 1, 250000, 0xA2 पूर्ण,
	अणु 1, 500000, 0xA1 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा lv0104cs_mapping lv0104cs_scales[] = अणु
	अणु 0, 250000, LV0104CS_SCALE_0_25X << LV0104CS_SCALE_SHIFT पूर्ण,
	अणु 1, 0, LV0104CS_SCALE_1X << LV0104CS_SCALE_SHIFT पूर्ण,
	अणु 2, 0, LV0104CS_SCALE_2X << LV0104CS_SCALE_SHIFT पूर्ण,
	अणु 8, 0, LV0104CS_SCALE_8X << LV0104CS_SCALE_SHIFT पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा lv0104cs_mapping lv0104cs_पूर्णांक_बार[] = अणु
	अणु 0, 12500, LV0104CS_INTEG_12_5MS << LV0104CS_INTEG_SHIFT पूर्ण,
	अणु 0, 100000, LV0104CS_INTEG_100MS << LV0104CS_INTEG_SHIFT पूर्ण,
	अणु 0, 200000, LV0104CS_INTEG_200MS << LV0104CS_INTEG_SHIFT पूर्ण,
पूर्ण;

अटल पूर्णांक lv0104cs_ग_लिखो_reg(काष्ठा i2c_client *client, u8 regval)
अणु
	पूर्णांक ret;

	ret = i2c_master_send(client, (अक्षर *)&regval, माप(regval));
	अगर (ret < 0)
		वापस ret;
	अगर (ret != माप(regval))
		वापस -EIO;

	वापस 0;
पूर्ण

अटल पूर्णांक lv0104cs_पढ़ो_adc(काष्ठा i2c_client *client, u16 *adc_output)
अणु
	__be16 regval;
	पूर्णांक ret;

	ret = i2c_master_recv(client, (अक्षर *)&regval, माप(regval));
	अगर (ret < 0)
		वापस ret;
	अगर (ret != माप(regval))
		वापस -EIO;

	*adc_output = be16_to_cpu(regval);

	वापस 0;
पूर्ण

अटल पूर्णांक lv0104cs_get_lux(काष्ठा lv0104cs_निजी *lv0104cs,
				पूर्णांक *val, पूर्णांक *val2)
अणु
	u8 regval = LV0104CS_REGVAL_MEASURE;
	u16 adc_output;
	पूर्णांक ret;

	regval |= lv0104cs_scales[lv0104cs->scale].regval;
	regval |= lv0104cs_पूर्णांक_बार[lv0104cs->पूर्णांक_समय].regval;
	ret = lv0104cs_ग_लिखो_reg(lv0104cs->client, regval);
	अगर (ret)
		वापस ret;

	/* रुको क्रम पूर्णांकegration समय to pass (with margin) */
	चयन (lv0104cs->पूर्णांक_समय) अणु
	हाल LV0104CS_INTEG_12_5MS:
		msleep(50);
		अवरोध;

	हाल LV0104CS_INTEG_100MS:
		msleep(150);
		अवरोध;

	हाल LV0104CS_INTEG_200MS:
		msleep(250);
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	ret = lv0104cs_पढ़ो_adc(lv0104cs->client, &adc_output);
	अगर (ret)
		वापस ret;

	ret = lv0104cs_ग_लिखो_reg(lv0104cs->client, LV0104CS_REGVAL_SLEEP);
	अगर (ret)
		वापस ret;

	/* convert ADC output to lux */
	चयन (lv0104cs->scale) अणु
	हाल LV0104CS_SCALE_0_25X:
		*val = adc_output * 4;
		*val2 = 0;
		वापस 0;

	हाल LV0104CS_SCALE_1X:
		*val = adc_output;
		*val2 = 0;
		वापस 0;

	हाल LV0104CS_SCALE_2X:
		*val = adc_output / 2;
		*val2 = (adc_output % 2) * 500000;
		वापस 0;

	हाल LV0104CS_SCALE_8X:
		*val = adc_output / 8;
		*val2 = (adc_output % 8) * 125000;
		वापस 0;

	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक lv0104cs_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
				काष्ठा iio_chan_spec स्थिर *chan,
				पूर्णांक *val, पूर्णांक *val2, दीर्घ mask)
अणु
	काष्ठा lv0104cs_निजी *lv0104cs = iio_priv(indio_dev);
	पूर्णांक ret;

	अगर (chan->type != IIO_LIGHT)
		वापस -EINVAL;

	mutex_lock(&lv0104cs->lock);

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_PROCESSED:
		ret = lv0104cs_get_lux(lv0104cs, val, val2);
		अगर (ret)
			जाओ err_mutex;
		ret = IIO_VAL_INT_PLUS_MICRO;
		अवरोध;

	हाल IIO_CHAN_INFO_CALIBSCALE:
		*val = lv0104cs_calibscales[lv0104cs->calibscale].val;
		*val2 = lv0104cs_calibscales[lv0104cs->calibscale].val2;
		ret = IIO_VAL_INT_PLUS_MICRO;
		अवरोध;

	हाल IIO_CHAN_INFO_SCALE:
		*val = lv0104cs_scales[lv0104cs->scale].val;
		*val2 = lv0104cs_scales[lv0104cs->scale].val2;
		ret = IIO_VAL_INT_PLUS_MICRO;
		अवरोध;

	हाल IIO_CHAN_INFO_INT_TIME:
		*val = lv0104cs_पूर्णांक_बार[lv0104cs->पूर्णांक_समय].val;
		*val2 = lv0104cs_पूर्णांक_बार[lv0104cs->पूर्णांक_समय].val2;
		ret = IIO_VAL_INT_PLUS_MICRO;
		अवरोध;

	शेष:
		ret = -EINVAL;
	पूर्ण

err_mutex:
	mutex_unlock(&lv0104cs->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक lv0104cs_set_calibscale(काष्ठा lv0104cs_निजी *lv0104cs,
				पूर्णांक val, पूर्णांक val2)
अणु
	पूर्णांक calibscale = val * 1000000 + val2;
	पूर्णांक न्यूनमान, उच्चमान, mid;
	पूर्णांक ret, i, index;

	/* round to nearest quantized calibscale (sensitivity) */
	क्रम (i = 0; i < ARRAY_SIZE(lv0104cs_calibscales) - 1; i++) अणु
		न्यूनमान = lv0104cs_calibscales[i].val * 1000000
				+ lv0104cs_calibscales[i].val2;
		उच्चमान = lv0104cs_calibscales[i + 1].val * 1000000
				+ lv0104cs_calibscales[i + 1].val2;
		mid = (न्यूनमान + उच्चमान) / 2;

		/* round करोwn */
		अगर (calibscale >= न्यूनमान && calibscale < mid) अणु
			index = i;
			अवरोध;
		पूर्ण

		/* round up */
		अगर (calibscale >= mid && calibscale <= उच्चमान) अणु
			index = i + 1;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (i == ARRAY_SIZE(lv0104cs_calibscales) - 1)
		वापस -EINVAL;

	mutex_lock(&lv0104cs->lock);

	/* set calibscale (sensitivity) */
	ret = lv0104cs_ग_लिखो_reg(lv0104cs->client,
			lv0104cs_calibscales[index].regval);
	अगर (ret)
		जाओ err_mutex;

	lv0104cs->calibscale = index;

err_mutex:
	mutex_unlock(&lv0104cs->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक lv0104cs_set_scale(काष्ठा lv0104cs_निजी *lv0104cs,
				पूर्णांक val, पूर्णांक val2)
अणु
	पूर्णांक i;

	/* hard matching */
	क्रम (i = 0; i < ARRAY_SIZE(lv0104cs_scales); i++) अणु
		अगर (val != lv0104cs_scales[i].val)
			जारी;

		अगर (val2 == lv0104cs_scales[i].val2)
			अवरोध;
	पूर्ण

	अगर (i == ARRAY_SIZE(lv0104cs_scales))
		वापस -EINVAL;

	mutex_lock(&lv0104cs->lock);
	lv0104cs->scale = i;
	mutex_unlock(&lv0104cs->lock);

	वापस 0;
पूर्ण

अटल पूर्णांक lv0104cs_set_पूर्णांक_समय(काष्ठा lv0104cs_निजी *lv0104cs,
				पूर्णांक val, पूर्णांक val2)
अणु
	पूर्णांक i;

	/* hard matching */
	क्रम (i = 0; i < ARRAY_SIZE(lv0104cs_पूर्णांक_बार); i++) अणु
		अगर (val != lv0104cs_पूर्णांक_बार[i].val)
			जारी;

		अगर (val2 == lv0104cs_पूर्णांक_बार[i].val2)
			अवरोध;
	पूर्ण

	अगर (i == ARRAY_SIZE(lv0104cs_पूर्णांक_बार))
		वापस -EINVAL;

	mutex_lock(&lv0104cs->lock);
	lv0104cs->पूर्णांक_समय = i;
	mutex_unlock(&lv0104cs->lock);

	वापस 0;
पूर्ण

अटल पूर्णांक lv0104cs_ग_लिखो_raw(काष्ठा iio_dev *indio_dev,
				काष्ठा iio_chan_spec स्थिर *chan,
				पूर्णांक val, पूर्णांक val2, दीर्घ mask)
अणु
	काष्ठा lv0104cs_निजी *lv0104cs = iio_priv(indio_dev);

	अगर (chan->type != IIO_LIGHT)
		वापस -EINVAL;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_CALIBSCALE:
		वापस lv0104cs_set_calibscale(lv0104cs, val, val2);

	हाल IIO_CHAN_INFO_SCALE:
		वापस lv0104cs_set_scale(lv0104cs, val, val2);

	हाल IIO_CHAN_INFO_INT_TIME:
		वापस lv0104cs_set_पूर्णांक_समय(lv0104cs, val, val2);

	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल sमाप_प्रकार lv0104cs_show_calibscale_avail(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	sमाप_प्रकार len = 0;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(lv0104cs_calibscales); i++) अणु
		len += scnम_लिखो(buf + len, PAGE_SIZE - len, "%d.%06d ",
				lv0104cs_calibscales[i].val,
				lv0104cs_calibscales[i].val2);
	पूर्ण

	buf[len - 1] = '\n';

	वापस len;
पूर्ण

अटल sमाप_प्रकार lv0104cs_show_scale_avail(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	sमाप_प्रकार len = 0;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(lv0104cs_scales); i++) अणु
		len += scnम_लिखो(buf + len, PAGE_SIZE - len, "%d.%06d ",
				lv0104cs_scales[i].val,
				lv0104cs_scales[i].val2);
	पूर्ण

	buf[len - 1] = '\n';

	वापस len;
पूर्ण

अटल sमाप_प्रकार lv0104cs_show_पूर्णांक_समय_avail(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	sमाप_प्रकार len = 0;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(lv0104cs_पूर्णांक_बार); i++) अणु
		len += scnम_लिखो(buf + len, PAGE_SIZE - len, "%d.%06d ",
				lv0104cs_पूर्णांक_बार[i].val,
				lv0104cs_पूर्णांक_बार[i].val2);
	पूर्ण

	buf[len - 1] = '\n';

	वापस len;
पूर्ण

अटल IIO_DEVICE_ATTR(calibscale_available, 0444,
				lv0104cs_show_calibscale_avail, शून्य, 0);
अटल IIO_DEVICE_ATTR(scale_available, 0444,
				lv0104cs_show_scale_avail, शून्य, 0);
अटल IIO_DEV_ATTR_INT_TIME_AVAIL(lv0104cs_show_पूर्णांक_समय_avail);

अटल काष्ठा attribute *lv0104cs_attributes[] = अणु
	&iio_dev_attr_calibscale_available.dev_attr.attr,
	&iio_dev_attr_scale_available.dev_attr.attr,
	&iio_dev_attr_पूर्णांकegration_समय_available.dev_attr.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group lv0104cs_attribute_group = अणु
	.attrs = lv0104cs_attributes,
पूर्ण;

अटल स्थिर काष्ठा iio_info lv0104cs_info = अणु
	.attrs = &lv0104cs_attribute_group,
	.पढ़ो_raw = &lv0104cs_पढ़ो_raw,
	.ग_लिखो_raw = &lv0104cs_ग_लिखो_raw,
पूर्ण;

अटल स्थिर काष्ठा iio_chan_spec lv0104cs_channels[] = अणु
	अणु
		.type = IIO_LIGHT,
		.info_mask_separate = BIT(IIO_CHAN_INFO_PROCESSED) |
				      BIT(IIO_CHAN_INFO_CALIBSCALE) |
				      BIT(IIO_CHAN_INFO_SCALE) |
				      BIT(IIO_CHAN_INFO_INT_TIME),
	पूर्ण,
पूर्ण;

अटल पूर्णांक lv0104cs_probe(काष्ठा i2c_client *client,
				स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा iio_dev *indio_dev;
	काष्ठा lv0104cs_निजी *lv0104cs;
	पूर्णांक ret;

	indio_dev = devm_iio_device_alloc(&client->dev, माप(*lv0104cs));
	अगर (!indio_dev)
		वापस -ENOMEM;

	lv0104cs = iio_priv(indio_dev);

	i2c_set_clientdata(client, lv0104cs);
	lv0104cs->client = client;

	mutex_init(&lv0104cs->lock);

	lv0104cs->calibscale = LV0104CS_CALIBSCALE_UNITY;
	lv0104cs->scale = LV0104CS_SCALE_1X;
	lv0104cs->पूर्णांक_समय = LV0104CS_INTEG_200MS;

	ret = lv0104cs_ग_लिखो_reg(lv0104cs->client,
			lv0104cs_calibscales[LV0104CS_CALIBSCALE_UNITY].regval);
	अगर (ret)
		वापस ret;

	indio_dev->modes = INDIO_सूचीECT_MODE;
	indio_dev->channels = lv0104cs_channels;
	indio_dev->num_channels = ARRAY_SIZE(lv0104cs_channels);
	indio_dev->name = client->name;
	indio_dev->info = &lv0104cs_info;

	वापस devm_iio_device_रेजिस्टर(&client->dev, indio_dev);
पूर्ण

अटल स्थिर काष्ठा i2c_device_id lv0104cs_id[] = अणु
	अणु "lv0104cs", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, lv0104cs_id);

अटल काष्ठा i2c_driver lv0104cs_i2c_driver = अणु
	.driver = अणु
		.name	= "lv0104cs",
	पूर्ण,
	.id_table	= lv0104cs_id,
	.probe		= lv0104cs_probe,
पूर्ण;
module_i2c_driver(lv0104cs_i2c_driver);

MODULE_AUTHOR("Jeff LaBundy <jeff@labundy.com>");
MODULE_DESCRIPTION("LV0104CS Ambient Light Sensor Driver");
MODULE_LICENSE("GPL");
