<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * MS5611 pressure and temperature sensor driver
 *
 * Copyright (c) Tomasz Duszynski <tduszyns@gmail.com>
 *
 * Data sheet:
 *  http://www.meas-spec.com/करोwnloads/MS5611-01BA03.pdf
 *  http://www.meas-spec.com/करोwnloads/MS5607-02BA03.pdf
 *
 */

#समावेश <linux/module.h>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/delay.h>
#समावेश <linux/regulator/consumer.h>

#समावेश <linux/iio/sysfs.h>
#समावेश <linux/iio/buffer.h>
#समावेश <linux/iio/triggered_buffer.h>
#समावेश <linux/iio/trigger_consumer.h>
#समावेश "ms5611.h"

#घोषणा MS5611_INIT_OSR(_cmd, _conv_usec, _rate) \
	अणु .cmd = _cmd, .conv_usec = _conv_usec, .rate = _rate पूर्ण

अटल स्थिर काष्ठा ms5611_osr ms5611_avail_pressure_osr[] = अणु
	MS5611_INIT_OSR(0x40, 600,  256),
	MS5611_INIT_OSR(0x42, 1170, 512),
	MS5611_INIT_OSR(0x44, 2280, 1024),
	MS5611_INIT_OSR(0x46, 4540, 2048),
	MS5611_INIT_OSR(0x48, 9040, 4096)
पूर्ण;

अटल स्थिर काष्ठा ms5611_osr ms5611_avail_temp_osr[] = अणु
	MS5611_INIT_OSR(0x50, 600,  256),
	MS5611_INIT_OSR(0x52, 1170, 512),
	MS5611_INIT_OSR(0x54, 2280, 1024),
	MS5611_INIT_OSR(0x56, 4540, 2048),
	MS5611_INIT_OSR(0x58, 9040, 4096)
पूर्ण;

अटल स्थिर अक्षर ms5611_show_osr[] = "256 512 1024 2048 4096";

अटल IIO_CONST_ATTR(oversampling_ratio_available, ms5611_show_osr);

अटल काष्ठा attribute *ms5611_attributes[] = अणु
	&iio_स्थिर_attr_oversampling_ratio_available.dev_attr.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group ms5611_attribute_group = अणु
	.attrs = ms5611_attributes,
पूर्ण;

अटल bool ms5611_prom_is_valid(u16 *prom, माप_प्रकार len)
अणु
	पूर्णांक i, j;
	uपूर्णांक16_t crc = 0, crc_orig = prom[7] & 0x000F;

	prom[7] &= 0xFF00;

	क्रम (i = 0; i < len * 2; i++) अणु
		अगर (i % 2 == 1)
			crc ^= prom[i >> 1] & 0x00FF;
		अन्यथा
			crc ^= prom[i >> 1] >> 8;

		क्रम (j = 0; j < 8; j++) अणु
			अगर (crc & 0x8000)
				crc = (crc << 1) ^ 0x3000;
			अन्यथा
				crc <<= 1;
		पूर्ण
	पूर्ण

	crc = (crc >> 12) & 0x000F;

	वापस crc_orig != 0x0000 && crc == crc_orig;
पूर्ण

अटल पूर्णांक ms5611_पढ़ो_prom(काष्ठा iio_dev *indio_dev)
अणु
	पूर्णांक ret, i;
	काष्ठा ms5611_state *st = iio_priv(indio_dev);

	क्रम (i = 0; i < MS5611_PROM_WORDS_NB; i++) अणु
		ret = st->पढ़ो_prom_word(&indio_dev->dev,
					 i, &st->chip_info->prom[i]);
		अगर (ret < 0) अणु
			dev_err(&indio_dev->dev,
				"failed to read prom at %d\n", i);
			वापस ret;
		पूर्ण
	पूर्ण

	अगर (!ms5611_prom_is_valid(st->chip_info->prom, MS5611_PROM_WORDS_NB)) अणु
		dev_err(&indio_dev->dev, "PROM integrity check failed\n");
		वापस -ENODEV;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ms5611_पढ़ो_temp_and_pressure(काष्ठा iio_dev *indio_dev,
					 s32 *temp, s32 *pressure)
अणु
	पूर्णांक ret;
	काष्ठा ms5611_state *st = iio_priv(indio_dev);

	ret = st->पढ़ो_adc_temp_and_pressure(&indio_dev->dev, temp, pressure);
	अगर (ret < 0) अणु
		dev_err(&indio_dev->dev,
			"failed to read temperature and pressure\n");
		वापस ret;
	पूर्ण

	वापस st->chip_info->temp_and_pressure_compensate(st->chip_info,
							   temp, pressure);
पूर्ण

अटल पूर्णांक ms5611_temp_and_pressure_compensate(काष्ठा ms5611_chip_info *chip_info,
					       s32 *temp, s32 *pressure)
अणु
	s32 t = *temp, p = *pressure;
	s64 off, sens, dt;

	dt = t - (chip_info->prom[5] << 8);
	off = ((s64)chip_info->prom[2] << 16) + ((chip_info->prom[4] * dt) >> 7);
	sens = ((s64)chip_info->prom[1] << 15) + ((chip_info->prom[3] * dt) >> 8);

	t = 2000 + ((chip_info->prom[6] * dt) >> 23);
	अगर (t < 2000) अणु
		s64 off2, sens2, t2;

		t2 = (dt * dt) >> 31;
		off2 = (5 * (t - 2000) * (t - 2000)) >> 1;
		sens2 = off2 >> 1;

		अगर (t < -1500) अणु
			s64 पंचांगp = (t + 1500) * (t + 1500);

			off2 += 7 * पंचांगp;
			sens2 += (11 * पंचांगp) >> 1;
		पूर्ण

		t -= t2;
		off -= off2;
		sens -= sens2;
	पूर्ण

	*temp = t;
	*pressure = (((p * sens) >> 21) - off) >> 15;

	वापस 0;
पूर्ण

अटल पूर्णांक ms5607_temp_and_pressure_compensate(काष्ठा ms5611_chip_info *chip_info,
					       s32 *temp, s32 *pressure)
अणु
	s32 t = *temp, p = *pressure;
	s64 off, sens, dt;

	dt = t - (chip_info->prom[5] << 8);
	off = ((s64)chip_info->prom[2] << 17) + ((chip_info->prom[4] * dt) >> 6);
	sens = ((s64)chip_info->prom[1] << 16) + ((chip_info->prom[3] * dt) >> 7);

	t = 2000 + ((chip_info->prom[6] * dt) >> 23);
	अगर (t < 2000) अणु
		s64 off2, sens2, t2, पंचांगp;

		t2 = (dt * dt) >> 31;
		पंचांगp = (t - 2000) * (t - 2000);
		off2 = (61 * पंचांगp) >> 4;
		sens2 = पंचांगp << 1;

		अगर (t < -1500) अणु
			पंचांगp = (t + 1500) * (t + 1500);
			off2 += 15 * पंचांगp;
			sens2 += 8 * पंचांगp;
		पूर्ण

		t -= t2;
		off -= off2;
		sens -= sens2;
	पूर्ण

	*temp = t;
	*pressure = (((p * sens) >> 21) - off) >> 15;

	वापस 0;
पूर्ण

अटल पूर्णांक ms5611_reset(काष्ठा iio_dev *indio_dev)
अणु
	पूर्णांक ret;
	काष्ठा ms5611_state *st = iio_priv(indio_dev);

	ret = st->reset(&indio_dev->dev);
	अगर (ret < 0) अणु
		dev_err(&indio_dev->dev, "failed to reset device\n");
		वापस ret;
	पूर्ण

	usleep_range(3000, 4000);

	वापस 0;
पूर्ण

अटल irqवापस_t ms5611_trigger_handler(पूर्णांक irq, व्योम *p)
अणु
	काष्ठा iio_poll_func *pf = p;
	काष्ठा iio_dev *indio_dev = pf->indio_dev;
	काष्ठा ms5611_state *st = iio_priv(indio_dev);
	/* Ensure buffer elements are naturally aligned */
	काष्ठा अणु
		s32 channels[2];
		s64 ts __aligned(8);
	पूर्ण scan;
	पूर्णांक ret;

	mutex_lock(&st->lock);
	ret = ms5611_पढ़ो_temp_and_pressure(indio_dev, &scan.channels[1],
					    &scan.channels[0]);
	mutex_unlock(&st->lock);
	अगर (ret < 0)
		जाओ err;

	iio_push_to_buffers_with_बारtamp(indio_dev, &scan,
					   iio_get_समय_ns(indio_dev));

err:
	iio_trigger_notअगरy_करोne(indio_dev->trig);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक ms5611_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			   काष्ठा iio_chan_spec स्थिर *chan,
			   पूर्णांक *val, पूर्णांक *val2, दीर्घ mask)
अणु
	पूर्णांक ret;
	s32 temp, pressure;
	काष्ठा ms5611_state *st = iio_priv(indio_dev);

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_PROCESSED:
		mutex_lock(&st->lock);
		ret = ms5611_पढ़ो_temp_and_pressure(indio_dev,
						    &temp, &pressure);
		mutex_unlock(&st->lock);
		अगर (ret < 0)
			वापस ret;

		चयन (chan->type) अणु
		हाल IIO_TEMP:
			*val = temp * 10;
			वापस IIO_VAL_INT;
		हाल IIO_PRESSURE:
			*val = pressure / 1000;
			*val2 = (pressure % 1000) * 1000;
			वापस IIO_VAL_INT_PLUS_MICRO;
		शेष:
			वापस -EINVAL;
		पूर्ण
	हाल IIO_CHAN_INFO_SCALE:
		चयन (chan->type) अणु
		हाल IIO_TEMP:
			*val = 10;
			वापस IIO_VAL_INT;
		हाल IIO_PRESSURE:
			*val = 0;
			*val2 = 1000;
			वापस IIO_VAL_INT_PLUS_MICRO;
		शेष:
			वापस -EINVAL;
		पूर्ण
	हाल IIO_CHAN_INFO_OVERSAMPLING_RATIO:
		अगर (chan->type != IIO_TEMP && chan->type != IIO_PRESSURE)
			अवरोध;
		mutex_lock(&st->lock);
		अगर (chan->type == IIO_TEMP)
			*val = (पूर्णांक)st->temp_osr->rate;
		अन्यथा
			*val = (पूर्णांक)st->pressure_osr->rate;
		mutex_unlock(&st->lock);
		वापस IIO_VAL_INT;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल स्थिर काष्ठा ms5611_osr *ms5611_find_osr(पूर्णांक rate,
						स्थिर काष्ठा ms5611_osr *osr,
						माप_प्रकार count)
अणु
	अचिन्हित पूर्णांक r;

	क्रम (r = 0; r < count; r++)
		अगर ((अचिन्हित लघु)rate == osr[r].rate)
			अवरोध;
	अगर (r >= count)
		वापस शून्य;
	वापस &osr[r];
पूर्ण

अटल पूर्णांक ms5611_ग_लिखो_raw(काष्ठा iio_dev *indio_dev,
			    काष्ठा iio_chan_spec स्थिर *chan,
			    पूर्णांक val, पूर्णांक val2, दीर्घ mask)
अणु
	काष्ठा ms5611_state *st = iio_priv(indio_dev);
	स्थिर काष्ठा ms5611_osr *osr = शून्य;
	पूर्णांक ret;

	अगर (mask != IIO_CHAN_INFO_OVERSAMPLING_RATIO)
		वापस -EINVAL;

	अगर (chan->type == IIO_TEMP)
		osr = ms5611_find_osr(val, ms5611_avail_temp_osr,
				      ARRAY_SIZE(ms5611_avail_temp_osr));
	अन्यथा अगर (chan->type == IIO_PRESSURE)
		osr = ms5611_find_osr(val, ms5611_avail_pressure_osr,
				      ARRAY_SIZE(ms5611_avail_pressure_osr));
	अगर (!osr)
		वापस -EINVAL;

	ret = iio_device_claim_direct_mode(indio_dev);
	अगर (ret)
		वापस ret;

	mutex_lock(&st->lock);

	अगर (chan->type == IIO_TEMP)
		st->temp_osr = osr;
	अन्यथा
		st->pressure_osr = osr;

	mutex_unlock(&st->lock);
	iio_device_release_direct_mode(indio_dev);

	वापस 0;
पूर्ण

अटल स्थिर अचिन्हित दीर्घ ms5611_scan_masks[] = अणु0x3, 0पूर्ण;

अटल काष्ठा ms5611_chip_info chip_info_tbl[] = अणु
	[MS5611] = अणु
		.temp_and_pressure_compensate = ms5611_temp_and_pressure_compensate,
	पूर्ण,
	[MS5607] = अणु
		.temp_and_pressure_compensate = ms5607_temp_and_pressure_compensate,
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा iio_chan_spec ms5611_channels[] = अणु
	अणु
		.type = IIO_PRESSURE,
		.info_mask_separate = BIT(IIO_CHAN_INFO_PROCESSED) |
			BIT(IIO_CHAN_INFO_SCALE) |
			BIT(IIO_CHAN_INFO_OVERSAMPLING_RATIO),
		.scan_index = 0,
		.scan_type = अणु
			.sign = 's',
			.realbits = 32,
			.storagebits = 32,
			.endianness = IIO_CPU,
		पूर्ण,
	पूर्ण,
	अणु
		.type = IIO_TEMP,
		.info_mask_separate = BIT(IIO_CHAN_INFO_PROCESSED) |
			BIT(IIO_CHAN_INFO_SCALE) |
			BIT(IIO_CHAN_INFO_OVERSAMPLING_RATIO),
		.scan_index = 1,
		.scan_type = अणु
			.sign = 's',
			.realbits = 32,
			.storagebits = 32,
			.endianness = IIO_CPU,
		पूर्ण,
	पूर्ण,
	IIO_CHAN_SOFT_TIMESTAMP(2),
पूर्ण;

अटल स्थिर काष्ठा iio_info ms5611_info = अणु
	.पढ़ो_raw = &ms5611_पढ़ो_raw,
	.ग_लिखो_raw = &ms5611_ग_लिखो_raw,
	.attrs = &ms5611_attribute_group,
पूर्ण;

अटल पूर्णांक ms5611_init(काष्ठा iio_dev *indio_dev)
अणु
	पूर्णांक ret;
	काष्ठा ms5611_state *st = iio_priv(indio_dev);

	/* Enable attached regulator अगर any. */
	st->vdd = devm_regulator_get(indio_dev->dev.parent, "vdd");
	अगर (IS_ERR(st->vdd))
		वापस PTR_ERR(st->vdd);

	ret = regulator_enable(st->vdd);
	अगर (ret) अणु
		dev_err(indio_dev->dev.parent,
			"failed to enable Vdd supply: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = ms5611_reset(indio_dev);
	अगर (ret < 0)
		जाओ err_regulator_disable;

	ret = ms5611_पढ़ो_prom(indio_dev);
	अगर (ret < 0)
		जाओ err_regulator_disable;

	वापस 0;

err_regulator_disable:
	regulator_disable(st->vdd);
	वापस ret;
पूर्ण

अटल व्योम ms5611_fini(स्थिर काष्ठा iio_dev *indio_dev)
अणु
	स्थिर काष्ठा ms5611_state *st = iio_priv(indio_dev);

	regulator_disable(st->vdd);
पूर्ण

पूर्णांक ms5611_probe(काष्ठा iio_dev *indio_dev, काष्ठा device *dev,
		 स्थिर अक्षर *name, पूर्णांक type)
अणु
	पूर्णांक ret;
	काष्ठा ms5611_state *st = iio_priv(indio_dev);

	mutex_init(&st->lock);
	st->chip_info = &chip_info_tbl[type];
	st->temp_osr =
		&ms5611_avail_temp_osr[ARRAY_SIZE(ms5611_avail_temp_osr) - 1];
	st->pressure_osr =
		&ms5611_avail_pressure_osr[ARRAY_SIZE(ms5611_avail_pressure_osr)
					   - 1];
	indio_dev->name = name;
	indio_dev->info = &ms5611_info;
	indio_dev->channels = ms5611_channels;
	indio_dev->num_channels = ARRAY_SIZE(ms5611_channels);
	indio_dev->modes = INDIO_सूचीECT_MODE;
	indio_dev->available_scan_masks = ms5611_scan_masks;

	ret = ms5611_init(indio_dev);
	अगर (ret < 0)
		वापस ret;

	ret = iio_triggered_buffer_setup(indio_dev, शून्य,
					 ms5611_trigger_handler, शून्य);
	अगर (ret < 0) अणु
		dev_err(dev, "iio triggered buffer setup failed\n");
		जाओ err_fini;
	पूर्ण

	ret = iio_device_रेजिस्टर(indio_dev);
	अगर (ret < 0) अणु
		dev_err(dev, "unable to register iio device\n");
		जाओ err_buffer_cleanup;
	पूर्ण

	वापस 0;

err_buffer_cleanup:
	iio_triggered_buffer_cleanup(indio_dev);
err_fini:
	ms5611_fini(indio_dev);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(ms5611_probe);

पूर्णांक ms5611_हटाओ(काष्ठा iio_dev *indio_dev)
अणु
	iio_device_unरेजिस्टर(indio_dev);
	iio_triggered_buffer_cleanup(indio_dev);
	ms5611_fini(indio_dev);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(ms5611_हटाओ);

MODULE_AUTHOR("Tomasz Duszynski <tduszyns@gmail.com>");
MODULE_DESCRIPTION("MS5611 core driver");
MODULE_LICENSE("GPL v2");
