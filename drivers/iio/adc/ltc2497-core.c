<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * ltc2497-core.c - Common code क्रम Analog Devices/Linear Technology
 * LTC2496 and LTC2497 ADCs
 *
 * Copyright (C) 2017 Analog Devices Inc.
 */

#समावेश <linux/delay.h>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/driver.h>
#समावेश <linux/module.h>
#समावेश <linux/regulator/consumer.h>

#समावेश "ltc2497.h"

#घोषणा LTC2497_SGL			BIT(4)
#घोषणा LTC2497_DIFF			0
#घोषणा LTC2497_SIGN			BIT(3)

अटल पूर्णांक ltc2497core_रुको_conv(काष्ठा ltc2497core_driverdata *ddata)
अणु
	s64 समय_elapsed;

	समय_elapsed = kसमय_ms_delta(kसमय_get(), ddata->समय_prev);

	अगर (समय_elapsed < LTC2497_CONVERSION_TIME_MS) अणु
		/* delay अगर conversion समय not passed
		 * since last पढ़ो or ग_लिखो
		 */
		अगर (msleep_पूर्णांकerruptible(
		    LTC2497_CONVERSION_TIME_MS - समय_elapsed))
			वापस -ERESTARTSYS;

		वापस 0;
	पूर्ण

	अगर (समय_elapsed - LTC2497_CONVERSION_TIME_MS <= 0) अणु
		/* We're in स्वतःmatic mode -
		 * so the last पढ़ोing is still not outdated
		 */
		वापस 0;
	पूर्ण

	वापस 1;
पूर्ण

अटल पूर्णांक ltc2497core_पढ़ो(काष्ठा ltc2497core_driverdata *ddata, u8 address, पूर्णांक *val)
अणु
	पूर्णांक ret;

	ret = ltc2497core_रुको_conv(ddata);
	अगर (ret < 0)
		वापस ret;

	अगर (ret || ddata->addr_prev != address) अणु
		ret = ddata->result_and_measure(ddata, address, शून्य);
		अगर (ret < 0)
			वापस ret;
		ddata->addr_prev = address;

		अगर (msleep_पूर्णांकerruptible(LTC2497_CONVERSION_TIME_MS))
			वापस -ERESTARTSYS;
	पूर्ण

	ret = ddata->result_and_measure(ddata, address, val);
	अगर (ret < 0)
		वापस ret;

	ddata->समय_prev = kसमय_get();

	वापस ret;
पूर्ण

अटल पूर्णांक ltc2497core_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			    काष्ठा iio_chan_spec स्थिर *chan,
			    पूर्णांक *val, पूर्णांक *val2, दीर्घ mask)
अणु
	काष्ठा ltc2497core_driverdata *ddata = iio_priv(indio_dev);
	पूर्णांक ret;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		mutex_lock(&indio_dev->mlock);
		ret = ltc2497core_पढ़ो(ddata, chan->address, val);
		mutex_unlock(&indio_dev->mlock);
		अगर (ret < 0)
			वापस ret;

		वापस IIO_VAL_INT;

	हाल IIO_CHAN_INFO_SCALE:
		ret = regulator_get_voltage(ddata->ref);
		अगर (ret < 0)
			वापस ret;

		*val = ret / 1000;
		*val2 = 17;

		वापस IIO_VAL_FRACTIONAL_LOG2;

	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

#घोषणा LTC2497_CHAN(_chan, _addr, _ds_name) अणु \
	.type = IIO_VOLTAGE, \
	.indexed = 1, \
	.channel = (_chan), \
	.address = (_addr | (_chan / 2) | ((_chan & 1) ? LTC2497_SIGN : 0)), \
	.info_mask_separate = BIT(IIO_CHAN_INFO_RAW), \
	.info_mask_shared_by_type = BIT(IIO_CHAN_INFO_SCALE), \
	.datasheet_name = (_ds_name), \
पूर्ण

#घोषणा LTC2497_CHAN_DIFF(_chan, _addr) अणु \
	.type = IIO_VOLTAGE, \
	.indexed = 1, \
	.channel = (_chan) * 2 + ((_addr) & LTC2497_SIGN ? 1 : 0), \
	.channel2 = (_chan) * 2 + ((_addr) & LTC2497_SIGN ? 0 : 1),\
	.address = (_addr | _chan), \
	.info_mask_separate = BIT(IIO_CHAN_INFO_RAW), \
	.info_mask_shared_by_type = BIT(IIO_CHAN_INFO_SCALE), \
	.dअगरferential = 1, \
पूर्ण

अटल स्थिर काष्ठा iio_chan_spec ltc2497core_channel[] = अणु
	LTC2497_CHAN(0, LTC2497_SGL, "CH0"),
	LTC2497_CHAN(1, LTC2497_SGL, "CH1"),
	LTC2497_CHAN(2, LTC2497_SGL, "CH2"),
	LTC2497_CHAN(3, LTC2497_SGL, "CH3"),
	LTC2497_CHAN(4, LTC2497_SGL, "CH4"),
	LTC2497_CHAN(5, LTC2497_SGL, "CH5"),
	LTC2497_CHAN(6, LTC2497_SGL, "CH6"),
	LTC2497_CHAN(7, LTC2497_SGL, "CH7"),
	LTC2497_CHAN(8, LTC2497_SGL, "CH8"),
	LTC2497_CHAN(9, LTC2497_SGL, "CH9"),
	LTC2497_CHAN(10, LTC2497_SGL, "CH10"),
	LTC2497_CHAN(11, LTC2497_SGL, "CH11"),
	LTC2497_CHAN(12, LTC2497_SGL, "CH12"),
	LTC2497_CHAN(13, LTC2497_SGL, "CH13"),
	LTC2497_CHAN(14, LTC2497_SGL, "CH14"),
	LTC2497_CHAN(15, LTC2497_SGL, "CH15"),
	LTC2497_CHAN_DIFF(0, LTC2497_DIFF),
	LTC2497_CHAN_DIFF(1, LTC2497_DIFF),
	LTC2497_CHAN_DIFF(2, LTC2497_DIFF),
	LTC2497_CHAN_DIFF(3, LTC2497_DIFF),
	LTC2497_CHAN_DIFF(4, LTC2497_DIFF),
	LTC2497_CHAN_DIFF(5, LTC2497_DIFF),
	LTC2497_CHAN_DIFF(6, LTC2497_DIFF),
	LTC2497_CHAN_DIFF(7, LTC2497_DIFF),
	LTC2497_CHAN_DIFF(0, LTC2497_DIFF | LTC2497_SIGN),
	LTC2497_CHAN_DIFF(1, LTC2497_DIFF | LTC2497_SIGN),
	LTC2497_CHAN_DIFF(2, LTC2497_DIFF | LTC2497_SIGN),
	LTC2497_CHAN_DIFF(3, LTC2497_DIFF | LTC2497_SIGN),
	LTC2497_CHAN_DIFF(4, LTC2497_DIFF | LTC2497_SIGN),
	LTC2497_CHAN_DIFF(5, LTC2497_DIFF | LTC2497_SIGN),
	LTC2497_CHAN_DIFF(6, LTC2497_DIFF | LTC2497_SIGN),
	LTC2497_CHAN_DIFF(7, LTC2497_DIFF | LTC2497_SIGN),
पूर्ण;

अटल स्थिर काष्ठा iio_info ltc2497core_info = अणु
	.पढ़ो_raw = ltc2497core_पढ़ो_raw,
पूर्ण;

पूर्णांक ltc2497core_probe(काष्ठा device *dev, काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा ltc2497core_driverdata *ddata = iio_priv(indio_dev);
	पूर्णांक ret;

	indio_dev->name = dev_name(dev);
	indio_dev->info = &ltc2497core_info;
	indio_dev->modes = INDIO_सूचीECT_MODE;
	indio_dev->channels = ltc2497core_channel;
	indio_dev->num_channels = ARRAY_SIZE(ltc2497core_channel);

	ret = ddata->result_and_measure(ddata, LTC2497_CONFIG_DEFAULT, शून्य);
	अगर (ret < 0)
		वापस ret;

	ddata->ref = devm_regulator_get(dev, "vref");
	अगर (IS_ERR(ddata->ref))
		वापस dev_err_probe(dev, PTR_ERR(ddata->ref),
				     "Failed to get vref regulator\n");

	ret = regulator_enable(ddata->ref);
	अगर (ret < 0) अणु
		dev_err(dev, "Failed to enable vref regulator: %pe\n",
			ERR_PTR(ret));
		वापस ret;
	पूर्ण

	अगर (dev->platक्रमm_data) अणु
		काष्ठा iio_map *plat_data;

		plat_data = (काष्ठा iio_map *)dev->platक्रमm_data;

		ret = iio_map_array_रेजिस्टर(indio_dev, plat_data);
		अगर (ret) अणु
			dev_err(&indio_dev->dev, "iio map err: %d\n", ret);
			जाओ err_regulator_disable;
		पूर्ण
	पूर्ण

	ddata->addr_prev = LTC2497_CONFIG_DEFAULT;
	ddata->समय_prev = kसमय_get();

	ret = iio_device_रेजिस्टर(indio_dev);
	अगर (ret < 0)
		जाओ err_array_unरेजिस्टर;

	वापस 0;

err_array_unरेजिस्टर:
	iio_map_array_unरेजिस्टर(indio_dev);

err_regulator_disable:
	regulator_disable(ddata->ref);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_NS(ltc2497core_probe, LTC2497);

व्योम ltc2497core_हटाओ(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा ltc2497core_driverdata *ddata = iio_priv(indio_dev);

	iio_device_unरेजिस्टर(indio_dev);

	iio_map_array_unरेजिस्टर(indio_dev);

	regulator_disable(ddata->ref);
पूर्ण
EXPORT_SYMBOL_NS(ltc2497core_हटाओ, LTC2497);

MODULE_DESCRIPTION("common code for LTC2496/LTC2497 drivers");
MODULE_LICENSE("GPL v2");
