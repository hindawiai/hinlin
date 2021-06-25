<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* ti-dac7311.c - Texas Instruments 8/10/12-bit 1-channel DAC driver
 *
 * Copyright (C) 2018 CMC NV
 *
 * https://www.ti.com/lit/ds/symlink/dac7311.pdf
 */

#समावेश <linux/iio/iपन.स>
#समावेश <linux/module.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/spi/spi.h>

क्रमागत अणु
	ID_DAC5311 = 0,
	ID_DAC6311,
	ID_DAC7311,
पूर्ण;

क्रमागत अणु
	POWER_1KOHM_TO_GND = 0,
	POWER_100KOHM_TO_GND,
	POWER_TRI_STATE,
पूर्ण;

काष्ठा ti_dac_spec अणु
	u8 resolution;
पूर्ण;

अटल स्थिर काष्ठा ti_dac_spec ti_dac_spec[] = अणु
	[ID_DAC5311] = अणु .resolution = 8 पूर्ण,
	[ID_DAC6311] = अणु .resolution = 10 पूर्ण,
	[ID_DAC7311] = अणु .resolution = 12 पूर्ण,
पूर्ण;

/**
 * काष्ठा ti_dac_chip - TI DAC chip
 * @lock: protects ग_लिखो sequences
 * @vref: regulator generating Vref
 * @spi: SPI device to send data to the device
 * @val: cached value
 * @घातerकरोwn: whether the chip is घातered करोwn
 * @घातerकरोwn_mode: selected by the user
 * @resolution: resolution of the chip
 * @buf: buffer क्रम transfer data
 */
काष्ठा ti_dac_chip अणु
	काष्ठा mutex lock;
	काष्ठा regulator *vref;
	काष्ठा spi_device *spi;
	u16 val;
	bool घातerकरोwn;
	u8 घातerकरोwn_mode;
	u8 resolution;
	u8 buf[2] ____cacheline_aligned;
पूर्ण;

अटल u8 ti_dac_get_घातer(काष्ठा ti_dac_chip *ti_dac, bool घातerकरोwn)
अणु
	अगर (घातerकरोwn)
		वापस ti_dac->घातerकरोwn_mode + 1;

	वापस 0;
पूर्ण

अटल पूर्णांक ti_dac_cmd(काष्ठा ti_dac_chip *ti_dac, u8 घातer, u16 val)
अणु
	u8 shअगरt = 14 - ti_dac->resolution;

	ti_dac->buf[0] = (val << shअगरt) & 0xFF;
	ti_dac->buf[1] = (घातer << 6) | (val >> (8 - shअगरt));
	वापस spi_ग_लिखो(ti_dac->spi, ti_dac->buf, 2);
पूर्ण

अटल स्थिर अक्षर * स्थिर ti_dac_घातerकरोwn_modes[] = अणु
	"1kohm_to_gnd",
	"100kohm_to_gnd",
	"three_state",
पूर्ण;

अटल पूर्णांक ti_dac_get_घातerकरोwn_mode(काष्ठा iio_dev *indio_dev,
				     स्थिर काष्ठा iio_chan_spec *chan)
अणु
	काष्ठा ti_dac_chip *ti_dac = iio_priv(indio_dev);

	वापस ti_dac->घातerकरोwn_mode;
पूर्ण

अटल पूर्णांक ti_dac_set_घातerकरोwn_mode(काष्ठा iio_dev *indio_dev,
				     स्थिर काष्ठा iio_chan_spec *chan,
				     अचिन्हित पूर्णांक mode)
अणु
	काष्ठा ti_dac_chip *ti_dac = iio_priv(indio_dev);

	ti_dac->घातerकरोwn_mode = mode;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा iio_क्रमागत ti_dac_घातerकरोwn_mode = अणु
	.items = ti_dac_घातerकरोwn_modes,
	.num_items = ARRAY_SIZE(ti_dac_घातerकरोwn_modes),
	.get = ti_dac_get_घातerकरोwn_mode,
	.set = ti_dac_set_घातerकरोwn_mode,
पूर्ण;

अटल sमाप_प्रकार ti_dac_पढ़ो_घातerकरोwn(काष्ठा iio_dev *indio_dev,
				     uपूर्णांकptr_t निजी,
				     स्थिर काष्ठा iio_chan_spec *chan,
				     अक्षर *buf)
अणु
	काष्ठा ti_dac_chip *ti_dac = iio_priv(indio_dev);

	वापस sysfs_emit(buf, "%d\n", ti_dac->घातerकरोwn);
पूर्ण

अटल sमाप_प्रकार ti_dac_ग_लिखो_घातerकरोwn(काष्ठा iio_dev *indio_dev,
				      uपूर्णांकptr_t निजी,
				      स्थिर काष्ठा iio_chan_spec *chan,
				      स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	काष्ठा ti_dac_chip *ti_dac = iio_priv(indio_dev);
	bool घातerकरोwn;
	u8 घातer;
	पूर्णांक ret;

	ret = strtobool(buf, &घातerकरोwn);
	अगर (ret)
		वापस ret;

	घातer = ti_dac_get_घातer(ti_dac, घातerकरोwn);

	mutex_lock(&ti_dac->lock);
	ret = ti_dac_cmd(ti_dac, घातer, 0);
	अगर (!ret)
		ti_dac->घातerकरोwn = घातerकरोwn;
	mutex_unlock(&ti_dac->lock);

	वापस ret ? ret : len;
पूर्ण

अटल स्थिर काष्ठा iio_chan_spec_ext_info ti_dac_ext_info[] = अणु
	अणु
		.name	   = "powerdown",
		.पढ़ो	   = ti_dac_पढ़ो_घातerकरोwn,
		.ग_लिखो	   = ti_dac_ग_लिखो_घातerकरोwn,
		.shared	   = IIO_SHARED_BY_TYPE,
	पूर्ण,
	IIO_ENUM("powerdown_mode", IIO_SHARED_BY_TYPE, &ti_dac_घातerकरोwn_mode),
	IIO_ENUM_AVAILABLE("powerdown_mode", &ti_dac_घातerकरोwn_mode),
	अणु पूर्ण,
पूर्ण;

#घोषणा TI_DAC_CHANNEL(chan) अणु					\
	.type = IIO_VOLTAGE,					\
	.channel = (chan),					\
	.output = true,						\
	.info_mask_separate = BIT(IIO_CHAN_INFO_RAW),		\
	.info_mask_shared_by_type = BIT(IIO_CHAN_INFO_SCALE),	\
	.ext_info = ti_dac_ext_info,				\
पूर्ण

अटल स्थिर काष्ठा iio_chan_spec ti_dac_channels[] = अणु
	TI_DAC_CHANNEL(0),
पूर्ण;

अटल पूर्णांक ti_dac_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			   काष्ठा iio_chan_spec स्थिर *chan,
			   पूर्णांक *val, पूर्णांक *val2, दीर्घ mask)
अणु
	काष्ठा ti_dac_chip *ti_dac = iio_priv(indio_dev);
	पूर्णांक ret;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		*val = ti_dac->val;
		वापस IIO_VAL_INT;

	हाल IIO_CHAN_INFO_SCALE:
		ret = regulator_get_voltage(ti_dac->vref);
		अगर (ret < 0)
			वापस ret;

		*val = ret / 1000;
		*val2 = ti_dac->resolution;
		वापस IIO_VAL_FRACTIONAL_LOG2;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक ti_dac_ग_लिखो_raw(काष्ठा iio_dev *indio_dev,
			    काष्ठा iio_chan_spec स्थिर *chan,
			    पूर्णांक val, पूर्णांक val2, दीर्घ mask)
अणु
	काष्ठा ti_dac_chip *ti_dac = iio_priv(indio_dev);
	u8 घातer = ti_dac_get_घातer(ti_dac, ti_dac->घातerकरोwn);
	पूर्णांक ret;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		अगर (ti_dac->val == val)
			वापस 0;

		अगर (val >= (1 << ti_dac->resolution) || val < 0)
			वापस -EINVAL;

		अगर (ti_dac->घातerकरोwn)
			वापस -EBUSY;

		mutex_lock(&ti_dac->lock);
		ret = ti_dac_cmd(ti_dac, घातer, val);
		अगर (!ret)
			ti_dac->val = val;
		mutex_unlock(&ti_dac->lock);
		अवरोध;

	शेष:
		ret = -EINVAL;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक ti_dac_ग_लिखो_raw_get_fmt(काष्ठा iio_dev *indio_dev,
				    काष्ठा iio_chan_spec स्थिर *chan, दीर्घ mask)
अणु
	वापस IIO_VAL_INT;
पूर्ण

अटल स्थिर काष्ठा iio_info ti_dac_info = अणु
	.पढ़ो_raw	   = ti_dac_पढ़ो_raw,
	.ग_लिखो_raw	   = ti_dac_ग_लिखो_raw,
	.ग_लिखो_raw_get_fmt = ti_dac_ग_लिखो_raw_get_fmt,
पूर्ण;

अटल पूर्णांक ti_dac_probe(काष्ठा spi_device *spi)
अणु
	काष्ठा device *dev = &spi->dev;
	स्थिर काष्ठा ti_dac_spec *spec;
	काष्ठा ti_dac_chip *ti_dac;
	काष्ठा iio_dev *indio_dev;
	पूर्णांक ret;

	indio_dev = devm_iio_device_alloc(dev, माप(*ti_dac));
	अगर (!indio_dev) अणु
		dev_err(dev, "can not allocate iio device\n");
		वापस -ENOMEM;
	पूर्ण

	spi->mode = SPI_MODE_1;
	spi->bits_per_word = 16;
	spi_setup(spi);

	indio_dev->info = &ti_dac_info;
	indio_dev->name = spi_get_device_id(spi)->name;
	indio_dev->modes = INDIO_सूचीECT_MODE;
	indio_dev->channels = ti_dac_channels;
	spi_set_drvdata(spi, indio_dev);

	ti_dac = iio_priv(indio_dev);
	ti_dac->घातerकरोwn = false;
	ti_dac->spi = spi;

	spec = &ti_dac_spec[spi_get_device_id(spi)->driver_data];
	indio_dev->num_channels = 1;
	ti_dac->resolution = spec->resolution;

	ti_dac->vref = devm_regulator_get(dev, "vref");
	अगर (IS_ERR(ti_dac->vref)) अणु
		dev_err(dev, "error to get regulator\n");
		वापस PTR_ERR(ti_dac->vref);
	पूर्ण

	ret = regulator_enable(ti_dac->vref);
	अगर (ret < 0) अणु
		dev_err(dev, "can not enable regulator\n");
		वापस ret;
	पूर्ण

	mutex_init(&ti_dac->lock);

	ret = iio_device_रेजिस्टर(indio_dev);
	अगर (ret) अणु
		dev_err(dev, "fail to register iio device: %d\n", ret);
		जाओ err;
	पूर्ण

	वापस 0;

err:
	mutex_destroy(&ti_dac->lock);
	regulator_disable(ti_dac->vref);
	वापस ret;
पूर्ण

अटल पूर्णांक ti_dac_हटाओ(काष्ठा spi_device *spi)
अणु
	काष्ठा iio_dev *indio_dev = spi_get_drvdata(spi);
	काष्ठा ti_dac_chip *ti_dac = iio_priv(indio_dev);

	iio_device_unरेजिस्टर(indio_dev);
	mutex_destroy(&ti_dac->lock);
	regulator_disable(ti_dac->vref);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id ti_dac_of_id[] = अणु
	अणु .compatible = "ti,dac5311" पूर्ण,
	अणु .compatible = "ti,dac6311" पूर्ण,
	अणु .compatible = "ti,dac7311" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, ti_dac_of_id);

अटल स्थिर काष्ठा spi_device_id ti_dac_spi_id[] = अणु
	अणु "dac5311", ID_DAC5311  पूर्ण,
	अणु "dac6311", ID_DAC6311 पूर्ण,
	अणु "dac7311", ID_DAC7311 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(spi, ti_dac_spi_id);

अटल काष्ठा spi_driver ti_dac_driver = अणु
	.driver = अणु
		.name		= "ti-dac7311",
		.of_match_table	= ti_dac_of_id,
	पूर्ण,
	.probe	  = ti_dac_probe,
	.हटाओ   = ti_dac_हटाओ,
	.id_table = ti_dac_spi_id,
पूर्ण;
module_spi_driver(ti_dac_driver);

MODULE_AUTHOR("Charles-Antoine Couret <charles-antoine.couret@essensium.com>");
MODULE_DESCRIPTION("Texas Instruments 8/10/12-bit 1-channel DAC driver");
MODULE_LICENSE("GPL v2");
