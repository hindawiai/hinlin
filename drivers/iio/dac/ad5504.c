<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * AD5504, AD5501 High Voltage Digital to Analog Converter
 *
 * Copyright 2011 Analog Devices Inc.
 */

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/fs.h>
#समावेश <linux/device.h>
#समावेश <linux/kernel.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/slab.h>
#समावेश <linux/sysfs.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/module.h>
#समावेश <linux/bitops.h>

#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/sysfs.h>
#समावेश <linux/iio/events.h>
#समावेश <linux/iio/dac/ad5504.h>

#घोषणा AD5504_RES_MASK			GENMASK(11, 0)
#घोषणा AD5504_CMD_READ			BIT(15)
#घोषणा AD5504_CMD_WRITE		0
#घोषणा AD5504_ADDR(addr)		((addr) << 12)

/* Registers */
#घोषणा AD5504_ADDR_NOOP		0
#घोषणा AD5504_ADDR_DAC(x)		((x) + 1)
#घोषणा AD5504_ADDR_ALL_DAC		5
#घोषणा AD5504_ADDR_CTRL		7

/* Control Register */
#घोषणा AD5504_DAC_PWR(ch)		((ch) << 2)
#घोषणा AD5504_DAC_PWRDWN_MODE(mode)	((mode) << 6)
#घोषणा AD5504_DAC_PWRDN_20K		0
#घोषणा AD5504_DAC_PWRDN_3STATE		1

/**
 * काष्ठा ad5504_state - driver instance specअगरic data
 * @spi:			spi_device
 * @reg:		supply regulator
 * @vref_mv:		actual reference voltage used
 * @pwr_करोwn_mask:	घातer करोwn mask
 * @pwr_करोwn_mode:	current घातer करोwn mode
 * @data:		transfer buffer
 */
काष्ठा ad5504_state अणु
	काष्ठा spi_device		*spi;
	काष्ठा regulator		*reg;
	अचिन्हित लघु			vref_mv;
	अचिन्हित			pwr_करोwn_mask;
	अचिन्हित			pwr_करोwn_mode;

	__be16				data[2] ____cacheline_aligned;
पूर्ण;

/*
 * ad5504_supported_device_ids:
 */
क्रमागत ad5504_supported_device_ids अणु
	ID_AD5504,
	ID_AD5501,
पूर्ण;

अटल पूर्णांक ad5504_spi_ग_लिखो(काष्ठा ad5504_state *st, u8 addr, u16 val)
अणु
	st->data[0] = cpu_to_be16(AD5504_CMD_WRITE | AD5504_ADDR(addr) |
			      (val & AD5504_RES_MASK));

	वापस spi_ग_लिखो(st->spi, &st->data[0], 2);
पूर्ण

अटल पूर्णांक ad5504_spi_पढ़ो(काष्ठा ad5504_state *st, u8 addr)
अणु
	पूर्णांक ret;
	काष्ठा spi_transfer t = अणु
	    .tx_buf = &st->data[0],
	    .rx_buf = &st->data[1],
	    .len = 2,
	पूर्ण;

	st->data[0] = cpu_to_be16(AD5504_CMD_READ | AD5504_ADDR(addr));
	ret = spi_sync_transfer(st->spi, &t, 1);
	अगर (ret < 0)
		वापस ret;

	वापस be16_to_cpu(st->data[1]) & AD5504_RES_MASK;
पूर्ण

अटल पूर्णांक ad5504_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			   काष्ठा iio_chan_spec स्थिर *chan,
			   पूर्णांक *val,
			   पूर्णांक *val2,
			   दीर्घ m)
अणु
	काष्ठा ad5504_state *st = iio_priv(indio_dev);
	पूर्णांक ret;

	चयन (m) अणु
	हाल IIO_CHAN_INFO_RAW:
		ret = ad5504_spi_पढ़ो(st, chan->address);
		अगर (ret < 0)
			वापस ret;

		*val = ret;

		वापस IIO_VAL_INT;
	हाल IIO_CHAN_INFO_SCALE:
		*val = st->vref_mv;
		*val2 = chan->scan_type.realbits;
		वापस IIO_VAL_FRACTIONAL_LOG2;
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक ad5504_ग_लिखो_raw(काष्ठा iio_dev *indio_dev,
			       काष्ठा iio_chan_spec स्थिर *chan,
			       पूर्णांक val,
			       पूर्णांक val2,
			       दीर्घ mask)
अणु
	काष्ठा ad5504_state *st = iio_priv(indio_dev);

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		अगर (val >= (1 << chan->scan_type.realbits) || val < 0)
			वापस -EINVAL;

		वापस ad5504_spi_ग_लिखो(st, chan->address, val);
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल स्थिर अक्षर * स्थिर ad5504_घातerकरोwn_modes[] = अणु
	"20kohm_to_gnd",
	"three_state",
पूर्ण;

अटल पूर्णांक ad5504_get_घातerकरोwn_mode(काष्ठा iio_dev *indio_dev,
	स्थिर काष्ठा iio_chan_spec *chan)
अणु
	काष्ठा ad5504_state *st = iio_priv(indio_dev);

	वापस st->pwr_करोwn_mode;
पूर्ण

अटल पूर्णांक ad5504_set_घातerकरोwn_mode(काष्ठा iio_dev *indio_dev,
	स्थिर काष्ठा iio_chan_spec *chan, अचिन्हित पूर्णांक mode)
अणु
	काष्ठा ad5504_state *st = iio_priv(indio_dev);

	st->pwr_करोwn_mode = mode;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा iio_क्रमागत ad5504_घातerकरोwn_mode_क्रमागत = अणु
	.items = ad5504_घातerकरोwn_modes,
	.num_items = ARRAY_SIZE(ad5504_घातerकरोwn_modes),
	.get = ad5504_get_घातerकरोwn_mode,
	.set = ad5504_set_घातerकरोwn_mode,
पूर्ण;

अटल sमाप_प्रकार ad5504_पढ़ो_dac_घातerकरोwn(काष्ठा iio_dev *indio_dev,
	uपूर्णांकptr_t निजी, स्थिर काष्ठा iio_chan_spec *chan, अक्षर *buf)
अणु
	काष्ठा ad5504_state *st = iio_priv(indio_dev);

	वापस sysfs_emit(buf, "%d\n",
			  !(st->pwr_करोwn_mask & (1 << chan->channel)));
पूर्ण

अटल sमाप_प्रकार ad5504_ग_लिखो_dac_घातerकरोwn(काष्ठा iio_dev *indio_dev,
	uपूर्णांकptr_t निजी, स्थिर काष्ठा iio_chan_spec *chan, स्थिर अक्षर *buf,
	माप_प्रकार len)
अणु
	bool pwr_करोwn;
	पूर्णांक ret;
	काष्ठा ad5504_state *st = iio_priv(indio_dev);

	ret = strtobool(buf, &pwr_करोwn);
	अगर (ret)
		वापस ret;

	अगर (pwr_करोwn)
		st->pwr_करोwn_mask &= ~(1 << chan->channel);
	अन्यथा
		st->pwr_करोwn_mask |= (1 << chan->channel);

	ret = ad5504_spi_ग_लिखो(st, AD5504_ADDR_CTRL,
				AD5504_DAC_PWRDWN_MODE(st->pwr_करोwn_mode) |
				AD5504_DAC_PWR(st->pwr_करोwn_mask));

	/* ग_लिखोs to the CTRL रेजिस्टर must be followed by a NOOP */
	ad5504_spi_ग_लिखो(st, AD5504_ADDR_NOOP, 0);

	वापस ret ? ret : len;
पूर्ण

अटल IIO_CONST_ATTR(temp0_thresh_rising_value, "110000");
अटल IIO_CONST_ATTR(temp0_thresh_rising_en, "1");

अटल काष्ठा attribute *ad5504_ev_attributes[] = अणु
	&iio_स्थिर_attr_temp0_thresh_rising_value.dev_attr.attr,
	&iio_स्थिर_attr_temp0_thresh_rising_en.dev_attr.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group ad5504_ev_attribute_group = अणु
	.attrs = ad5504_ev_attributes,
पूर्ण;

अटल irqवापस_t ad5504_event_handler(पूर्णांक irq, व्योम *निजी)
अणु
	iio_push_event(निजी,
		       IIO_UNMOD_EVENT_CODE(IIO_TEMP,
					    0,
					    IIO_EV_TYPE_THRESH,
					    IIO_EV_सूची_RISING),
		       iio_get_समय_ns(निजी));

	वापस IRQ_HANDLED;
पूर्ण

अटल स्थिर काष्ठा iio_info ad5504_info = अणु
	.ग_लिखो_raw = ad5504_ग_लिखो_raw,
	.पढ़ो_raw = ad5504_पढ़ो_raw,
	.event_attrs = &ad5504_ev_attribute_group,
पूर्ण;

अटल स्थिर काष्ठा iio_chan_spec_ext_info ad5504_ext_info[] = अणु
	अणु
		.name = "powerdown",
		.पढ़ो = ad5504_पढ़ो_dac_घातerकरोwn,
		.ग_लिखो = ad5504_ग_लिखो_dac_घातerकरोwn,
		.shared = IIO_SEPARATE,
	पूर्ण,
	IIO_ENUM("powerdown_mode", IIO_SHARED_BY_TYPE,
		 &ad5504_घातerकरोwn_mode_क्रमागत),
	IIO_ENUM_AVAILABLE("powerdown_mode", &ad5504_घातerकरोwn_mode_क्रमागत),
	अणु पूर्ण,
पूर्ण;

#घोषणा AD5504_CHANNEL(_chan) अणु \
	.type = IIO_VOLTAGE, \
	.indexed = 1, \
	.output = 1, \
	.channel = (_chan), \
	.info_mask_separate = BIT(IIO_CHAN_INFO_RAW), \
	.info_mask_shared_by_type = BIT(IIO_CHAN_INFO_SCALE), \
	.address = AD5504_ADDR_DAC(_chan), \
	.scan_type = अणु \
		.sign = 'u', \
		.realbits = 12, \
		.storagebits = 16, \
	पूर्ण, \
	.ext_info = ad5504_ext_info, \
पूर्ण

अटल स्थिर काष्ठा iio_chan_spec ad5504_channels[] = अणु
	AD5504_CHANNEL(0),
	AD5504_CHANNEL(1),
	AD5504_CHANNEL(2),
	AD5504_CHANNEL(3),
पूर्ण;

अटल पूर्णांक ad5504_probe(काष्ठा spi_device *spi)
अणु
	काष्ठा ad5504_platक्रमm_data *pdata = spi->dev.platक्रमm_data;
	काष्ठा iio_dev *indio_dev;
	काष्ठा ad5504_state *st;
	काष्ठा regulator *reg;
	पूर्णांक ret, voltage_uv = 0;

	indio_dev = devm_iio_device_alloc(&spi->dev, माप(*st));
	अगर (!indio_dev)
		वापस -ENOMEM;
	reg = devm_regulator_get(&spi->dev, "vcc");
	अगर (!IS_ERR(reg)) अणु
		ret = regulator_enable(reg);
		अगर (ret)
			वापस ret;

		ret = regulator_get_voltage(reg);
		अगर (ret < 0)
			जाओ error_disable_reg;

		voltage_uv = ret;
	पूर्ण

	spi_set_drvdata(spi, indio_dev);
	st = iio_priv(indio_dev);
	अगर (voltage_uv)
		st->vref_mv = voltage_uv / 1000;
	अन्यथा अगर (pdata)
		st->vref_mv = pdata->vref_mv;
	अन्यथा
		dev_warn(&spi->dev, "reference voltage unspecified\n");

	st->reg = reg;
	st->spi = spi;
	indio_dev->name = spi_get_device_id(st->spi)->name;
	indio_dev->info = &ad5504_info;
	अगर (spi_get_device_id(st->spi)->driver_data == ID_AD5501)
		indio_dev->num_channels = 1;
	अन्यथा
		indio_dev->num_channels = 4;
	indio_dev->channels = ad5504_channels;
	indio_dev->modes = INDIO_सूचीECT_MODE;

	अगर (spi->irq) अणु
		ret = devm_request_thपढ़ोed_irq(&spi->dev, spi->irq,
					   शून्य,
					   &ad5504_event_handler,
					   IRQF_TRIGGER_FALLING | IRQF_ONESHOT,
					   spi_get_device_id(st->spi)->name,
					   indio_dev);
		अगर (ret)
			जाओ error_disable_reg;
	पूर्ण

	ret = iio_device_रेजिस्टर(indio_dev);
	अगर (ret)
		जाओ error_disable_reg;

	वापस 0;

error_disable_reg:
	अगर (!IS_ERR(reg))
		regulator_disable(reg);

	वापस ret;
पूर्ण

अटल पूर्णांक ad5504_हटाओ(काष्ठा spi_device *spi)
अणु
	काष्ठा iio_dev *indio_dev = spi_get_drvdata(spi);
	काष्ठा ad5504_state *st = iio_priv(indio_dev);

	iio_device_unरेजिस्टर(indio_dev);

	अगर (!IS_ERR(st->reg))
		regulator_disable(st->reg);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा spi_device_id ad5504_id[] = अणु
	अणु"ad5504", ID_AD5504पूर्ण,
	अणु"ad5501", ID_AD5501पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(spi, ad5504_id);

अटल काष्ठा spi_driver ad5504_driver = अणु
	.driver = अणु
		   .name = "ad5504",
		   पूर्ण,
	.probe = ad5504_probe,
	.हटाओ = ad5504_हटाओ,
	.id_table = ad5504_id,
पूर्ण;
module_spi_driver(ad5504_driver);

MODULE_AUTHOR("Michael Hennerich <michael.hennerich@analog.com>");
MODULE_DESCRIPTION("Analog Devices AD5501/AD5501 DAC");
MODULE_LICENSE("GPL v2");
