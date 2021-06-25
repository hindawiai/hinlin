<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * ti-dac082s085.c - Texas Instruments 8/10/12-bit 2/4-channel DAC driver
 *
 * Copyright (C) 2017 KUNBUS GmbH
 *
 * https://www.ti.com/lit/ds/symlink/dac082s085.pdf
 * https://www.ti.com/lit/ds/symlink/dac102s085.pdf
 * https://www.ti.com/lit/ds/symlink/dac122s085.pdf
 * https://www.ti.com/lit/ds/symlink/dac084s085.pdf
 * https://www.ti.com/lit/ds/symlink/dac104s085.pdf
 * https://www.ti.com/lit/ds/symlink/dac124s085.pdf
 */

#समावेश <linux/iio/iपन.स>
#समावेश <linux/module.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/spi/spi.h>

क्रमागत अणु dual_8bit, dual_10bit, dual_12bit, quad_8bit, quad_10bit, quad_12bit पूर्ण;

काष्ठा ti_dac_spec अणु
	u8 num_channels;
	u8 resolution;
पूर्ण;

अटल स्थिर काष्ठा ti_dac_spec ti_dac_spec[] = अणु
	[dual_8bit]  = अणु .num_channels = 2, .resolution = 8  पूर्ण,
	[dual_10bit] = अणु .num_channels = 2, .resolution = 10 पूर्ण,
	[dual_12bit] = अणु .num_channels = 2, .resolution = 12 पूर्ण,
	[quad_8bit]  = अणु .num_channels = 4, .resolution = 8  पूर्ण,
	[quad_10bit] = अणु .num_channels = 4, .resolution = 10 पूर्ण,
	[quad_12bit] = अणु .num_channels = 4, .resolution = 12 पूर्ण,
पूर्ण;

/**
 * काष्ठा ti_dac_chip - TI DAC chip
 * @lock: protects ग_लिखो sequences
 * @vref: regulator generating Vref
 * @mesg: SPI message to perक्रमm a ग_लिखो
 * @xfer: SPI transfer used by @mesg
 * @val: cached value of each output
 * @घातerकरोwn: whether the chip is घातered करोwn
 * @घातerकरोwn_mode: selected by the user
 * @resolution: resolution of the chip
 * @buf: buffer क्रम @xfer
 */
काष्ठा ti_dac_chip अणु
	काष्ठा mutex lock;
	काष्ठा regulator *vref;
	काष्ठा spi_message mesg;
	काष्ठा spi_transfer xfer;
	u16 val[4];
	bool घातerकरोwn;
	u8 घातerकरोwn_mode;
	u8 resolution;
	u8 buf[2] ____cacheline_aligned;
पूर्ण;

#घोषणा WRITE_NOT_UPDATE(chan)	(0x00 | (chan) << 6)
#घोषणा WRITE_AND_UPDATE(chan)	(0x10 | (chan) << 6)
#घोषणा WRITE_ALL_UPDATE	 0x20
#घोषणा POWERDOWN(mode) 	(0x30 | ((mode) + 1) << 6)

अटल पूर्णांक ti_dac_cmd(काष्ठा ti_dac_chip *ti_dac, u8 cmd, u16 val)
अणु
	u8 shअगरt = 12 - ti_dac->resolution;

	ti_dac->buf[0] = cmd | (val >> (8 - shअगरt));
	ti_dac->buf[1] = (val << shअगरt) & 0xff;
	वापस spi_sync(ti_dac->mesg.spi, &ti_dac->mesg);
पूर्ण

अटल स्थिर अक्षर * स्थिर ti_dac_घातerकरोwn_modes[] = अणु
	"2.5kohm_to_gnd", "100kohm_to_gnd", "three_state",
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
	पूर्णांक ret = 0;

	अगर (ti_dac->घातerकरोwn_mode == mode)
		वापस 0;

	mutex_lock(&ti_dac->lock);
	अगर (ti_dac->घातerकरोwn) अणु
		ret = ti_dac_cmd(ti_dac, POWERDOWN(mode), 0);
		अगर (ret)
			जाओ out;
	पूर्ण
	ti_dac->घातerकरोwn_mode = mode;

out:
	mutex_unlock(&ti_dac->lock);
	वापस ret;
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
	पूर्णांक ret;

	ret = strtobool(buf, &घातerकरोwn);
	अगर (ret)
		वापस ret;

	अगर (ti_dac->घातerकरोwn == घातerकरोwn)
		वापस len;

	mutex_lock(&ti_dac->lock);
	अगर (घातerकरोwn)
		ret = ti_dac_cmd(ti_dac, POWERDOWN(ti_dac->घातerकरोwn_mode), 0);
	अन्यथा
		ret = ti_dac_cmd(ti_dac, WRITE_AND_UPDATE(0), ti_dac->val[0]);
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
	.address = (chan),					\
	.indexed = true,					\
	.output = true,						\
	.datasheet_name = (स्थिर अक्षर[])अणु 'A' + (chan), 0 पूर्ण,	\
	.info_mask_separate = BIT(IIO_CHAN_INFO_RAW),		\
	.info_mask_shared_by_type = BIT(IIO_CHAN_INFO_SCALE),	\
	.ext_info = ti_dac_ext_info,				\
पूर्ण

अटल स्थिर काष्ठा iio_chan_spec ti_dac_channels[] = अणु
	TI_DAC_CHANNEL(0),
	TI_DAC_CHANNEL(1),
	TI_DAC_CHANNEL(2),
	TI_DAC_CHANNEL(3),
पूर्ण;

अटल पूर्णांक ti_dac_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			   काष्ठा iio_chan_spec स्थिर *chan,
			   पूर्णांक *val, पूर्णांक *val2, दीर्घ mask)
अणु
	काष्ठा ti_dac_chip *ti_dac = iio_priv(indio_dev);
	पूर्णांक ret;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		*val = ti_dac->val[chan->channel];
		ret = IIO_VAL_INT;
		अवरोध;

	हाल IIO_CHAN_INFO_SCALE:
		ret = regulator_get_voltage(ti_dac->vref);
		अगर (ret < 0)
			वापस ret;

		*val = ret / 1000;
		*val2 = ti_dac->resolution;
		ret = IIO_VAL_FRACTIONAL_LOG2;
		अवरोध;

	शेष:
		ret = -EINVAL;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक ti_dac_ग_लिखो_raw(काष्ठा iio_dev *indio_dev,
			    काष्ठा iio_chan_spec स्थिर *chan,
			    पूर्णांक val, पूर्णांक val2, दीर्घ mask)
अणु
	काष्ठा ti_dac_chip *ti_dac = iio_priv(indio_dev);
	पूर्णांक ret;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		अगर (ti_dac->val[chan->channel] == val)
			वापस 0;

		अगर (val >= (1 << ti_dac->resolution) || val < 0)
			वापस -EINVAL;

		अगर (ti_dac->घातerकरोwn)
			वापस -EBUSY;

		mutex_lock(&ti_dac->lock);
		ret = ti_dac_cmd(ti_dac, WRITE_AND_UPDATE(chan->channel), val);
		अगर (!ret)
			ti_dac->val[chan->channel] = val;
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
	अगर (!indio_dev)
		वापस -ENOMEM;

	indio_dev->info = &ti_dac_info;
	indio_dev->name = spi->modalias;
	indio_dev->modes = INDIO_सूचीECT_MODE;
	indio_dev->channels = ti_dac_channels;
	spi_set_drvdata(spi, indio_dev);

	ti_dac = iio_priv(indio_dev);
	ti_dac->xfer.tx_buf = &ti_dac->buf;
	ti_dac->xfer.len = माप(ti_dac->buf);
	spi_message_init_with_transfers(&ti_dac->mesg, &ti_dac->xfer, 1);
	ti_dac->mesg.spi = spi;

	spec = &ti_dac_spec[spi_get_device_id(spi)->driver_data];
	indio_dev->num_channels = spec->num_channels;
	ti_dac->resolution = spec->resolution;

	ti_dac->vref = devm_regulator_get(dev, "vref");
	अगर (IS_ERR(ti_dac->vref))
		वापस PTR_ERR(ti_dac->vref);

	ret = regulator_enable(ti_dac->vref);
	अगर (ret < 0)
		वापस ret;

	mutex_init(&ti_dac->lock);

	ret = ti_dac_cmd(ti_dac, WRITE_ALL_UPDATE, 0);
	अगर (ret) अणु
		dev_err(dev, "failed to initialize outputs to 0\n");
		जाओ err;
	पूर्ण

	ret = iio_device_रेजिस्टर(indio_dev);
	अगर (ret)
		जाओ err;

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
	अणु .compatible = "ti,dac082s085" पूर्ण,
	अणु .compatible = "ti,dac102s085" पूर्ण,
	अणु .compatible = "ti,dac122s085" पूर्ण,
	अणु .compatible = "ti,dac084s085" पूर्ण,
	अणु .compatible = "ti,dac104s085" पूर्ण,
	अणु .compatible = "ti,dac124s085" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, ti_dac_of_id);

अटल स्थिर काष्ठा spi_device_id ti_dac_spi_id[] = अणु
	अणु "dac082s085", dual_8bit  पूर्ण,
	अणु "dac102s085", dual_10bit पूर्ण,
	अणु "dac122s085", dual_12bit पूर्ण,
	अणु "dac084s085", quad_8bit  पूर्ण,
	अणु "dac104s085", quad_10bit पूर्ण,
	अणु "dac124s085", quad_12bit पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(spi, ti_dac_spi_id);

अटल काष्ठा spi_driver ti_dac_driver = अणु
	.driver = अणु
		.name		= "ti-dac082s085",
		.of_match_table	= ti_dac_of_id,
	पूर्ण,
	.probe	  = ti_dac_probe,
	.हटाओ   = ti_dac_हटाओ,
	.id_table = ti_dac_spi_id,
पूर्ण;
module_spi_driver(ti_dac_driver);

MODULE_AUTHOR("Lukas Wunner <lukas@wunner.de>");
MODULE_DESCRIPTION("Texas Instruments 8/10/12-bit 2/4-channel DAC driver");
MODULE_LICENSE("GPL v2");
