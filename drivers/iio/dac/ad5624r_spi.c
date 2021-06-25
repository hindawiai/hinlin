<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * AD5624R, AD5644R, AD5664R Digital to analog convertors spi driver
 *
 * Copyright 2010-2011 Analog Devices Inc.
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

#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/sysfs.h>

#समावेश <यंत्र/unaligned.h>

#समावेश "ad5624r.h"

अटल पूर्णांक ad5624r_spi_ग_लिखो(काष्ठा spi_device *spi,
			     u8 cmd, u8 addr, u16 val, u8 shअगरt)
अणु
	u32 data;
	u8 msg[3];

	/*
	 * The input shअगरt रेजिस्टर is 24 bits wide. The first two bits are
	 * करोn't care bits. The next three are the command bits, C2 to C0,
	 * followed by the 3-bit DAC address, A2 to A0, and then the
	 * 16-, 14-, 12-bit data-word. The data-word comprises the 16-,
	 * 14-, 12-bit input code followed by 0, 2, or 4 करोn't care bits,
	 * क्रम the AD5664R, AD5644R, and AD5624R, respectively.
	 */
	data = (0 << 22) | (cmd << 19) | (addr << 16) | (val << shअगरt);
	put_unaligned_be24(data, &msg[0]);

	वापस spi_ग_लिखो(spi, msg, माप(msg));
पूर्ण

अटल पूर्णांक ad5624r_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			   काष्ठा iio_chan_spec स्थिर *chan,
			   पूर्णांक *val,
			   पूर्णांक *val2,
			   दीर्घ m)
अणु
	काष्ठा ad5624r_state *st = iio_priv(indio_dev);

	चयन (m) अणु
	हाल IIO_CHAN_INFO_SCALE:
		*val = st->vref_mv;
		*val2 = chan->scan_type.realbits;
		वापस IIO_VAL_FRACTIONAL_LOG2;
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक ad5624r_ग_लिखो_raw(काष्ठा iio_dev *indio_dev,
			       काष्ठा iio_chan_spec स्थिर *chan,
			       पूर्णांक val,
			       पूर्णांक val2,
			       दीर्घ mask)
अणु
	काष्ठा ad5624r_state *st = iio_priv(indio_dev);

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		अगर (val >= (1 << chan->scan_type.realbits) || val < 0)
			वापस -EINVAL;

		वापस ad5624r_spi_ग_लिखो(st->us,
				AD5624R_CMD_WRITE_INPUT_N_UPDATE_N,
				chan->address, val,
				chan->scan_type.shअगरt);
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल स्थिर अक्षर * स्थिर ad5624r_घातerकरोwn_modes[] = अणु
	"1kohm_to_gnd",
	"100kohm_to_gnd",
	"three_state"
पूर्ण;

अटल पूर्णांक ad5624r_get_घातerकरोwn_mode(काष्ठा iio_dev *indio_dev,
	स्थिर काष्ठा iio_chan_spec *chan)
अणु
	काष्ठा ad5624r_state *st = iio_priv(indio_dev);

	वापस st->pwr_करोwn_mode;
पूर्ण

अटल पूर्णांक ad5624r_set_घातerकरोwn_mode(काष्ठा iio_dev *indio_dev,
	स्थिर काष्ठा iio_chan_spec *chan, अचिन्हित पूर्णांक mode)
अणु
	काष्ठा ad5624r_state *st = iio_priv(indio_dev);

	st->pwr_करोwn_mode = mode;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा iio_क्रमागत ad5624r_घातerकरोwn_mode_क्रमागत = अणु
	.items = ad5624r_घातerकरोwn_modes,
	.num_items = ARRAY_SIZE(ad5624r_घातerकरोwn_modes),
	.get = ad5624r_get_घातerकरोwn_mode,
	.set = ad5624r_set_घातerकरोwn_mode,
पूर्ण;

अटल sमाप_प्रकार ad5624r_पढ़ो_dac_घातerकरोwn(काष्ठा iio_dev *indio_dev,
	uपूर्णांकptr_t निजी, स्थिर काष्ठा iio_chan_spec *chan, अक्षर *buf)
अणु
	काष्ठा ad5624r_state *st = iio_priv(indio_dev);

	वापस sysfs_emit(buf, "%d\n",
			  !!(st->pwr_करोwn_mask & (1 << chan->channel)));
पूर्ण

अटल sमाप_प्रकार ad5624r_ग_लिखो_dac_घातerकरोwn(काष्ठा iio_dev *indio_dev,
	uपूर्णांकptr_t निजी, स्थिर काष्ठा iio_chan_spec *chan, स्थिर अक्षर *buf,
	माप_प्रकार len)
अणु
	bool pwr_करोwn;
	पूर्णांक ret;
	काष्ठा ad5624r_state *st = iio_priv(indio_dev);

	ret = strtobool(buf, &pwr_करोwn);
	अगर (ret)
		वापस ret;

	अगर (pwr_करोwn)
		st->pwr_करोwn_mask |= (1 << chan->channel);
	अन्यथा
		st->pwr_करोwn_mask &= ~(1 << chan->channel);

	ret = ad5624r_spi_ग_लिखो(st->us, AD5624R_CMD_POWERDOWN_DAC, 0,
				(st->pwr_करोwn_mode << 4) |
				st->pwr_करोwn_mask, 16);

	वापस ret ? ret : len;
पूर्ण

अटल स्थिर काष्ठा iio_info ad5624r_info = अणु
	.ग_लिखो_raw = ad5624r_ग_लिखो_raw,
	.पढ़ो_raw = ad5624r_पढ़ो_raw,
पूर्ण;

अटल स्थिर काष्ठा iio_chan_spec_ext_info ad5624r_ext_info[] = अणु
	अणु
		.name = "powerdown",
		.पढ़ो = ad5624r_पढ़ो_dac_घातerकरोwn,
		.ग_लिखो = ad5624r_ग_लिखो_dac_घातerकरोwn,
		.shared = IIO_SEPARATE,
	पूर्ण,
	IIO_ENUM("powerdown_mode", IIO_SHARED_BY_TYPE,
		 &ad5624r_घातerकरोwn_mode_क्रमागत),
	IIO_ENUM_AVAILABLE("powerdown_mode", &ad5624r_घातerकरोwn_mode_क्रमागत),
	अणु पूर्ण,
पूर्ण;

#घोषणा AD5624R_CHANNEL(_chan, _bits) अणु \
	.type = IIO_VOLTAGE, \
	.indexed = 1, \
	.output = 1, \
	.channel = (_chan), \
	.info_mask_separate = BIT(IIO_CHAN_INFO_RAW), \
	.info_mask_shared_by_type = BIT(IIO_CHAN_INFO_SCALE), \
	.address = (_chan), \
	.scan_type = अणु \
		.sign = 'u', \
		.realbits = (_bits), \
		.storagebits = 16, \
		.shअगरt = 16 - (_bits), \
	पूर्ण, \
	.ext_info = ad5624r_ext_info, \
पूर्ण

#घोषणा DECLARE_AD5624R_CHANNELS(_name, _bits) \
	स्थिर काष्ठा iio_chan_spec _name##_channels[] = अणु \
		AD5624R_CHANNEL(0, _bits), \
		AD5624R_CHANNEL(1, _bits), \
		AD5624R_CHANNEL(2, _bits), \
		AD5624R_CHANNEL(3, _bits), \
पूर्ण

अटल DECLARE_AD5624R_CHANNELS(ad5624r, 12);
अटल DECLARE_AD5624R_CHANNELS(ad5644r, 14);
अटल DECLARE_AD5624R_CHANNELS(ad5664r, 16);

अटल स्थिर काष्ठा ad5624r_chip_info ad5624r_chip_info_tbl[] = अणु
	[ID_AD5624R3] = अणु
		.channels = ad5624r_channels,
		.पूर्णांक_vref_mv = 1250,
	पूर्ण,
	[ID_AD5624R5] = अणु
		.channels = ad5624r_channels,
		.पूर्णांक_vref_mv = 2500,
	पूर्ण,
	[ID_AD5644R3] = अणु
		.channels = ad5644r_channels,
		.पूर्णांक_vref_mv = 1250,
	पूर्ण,
	[ID_AD5644R5] = अणु
		.channels = ad5644r_channels,
		.पूर्णांक_vref_mv = 2500,
	पूर्ण,
	[ID_AD5664R3] = अणु
		.channels = ad5664r_channels,
		.पूर्णांक_vref_mv = 1250,
	पूर्ण,
	[ID_AD5664R5] = अणु
		.channels = ad5664r_channels,
		.पूर्णांक_vref_mv = 2500,
	पूर्ण,
पूर्ण;

अटल पूर्णांक ad5624r_probe(काष्ठा spi_device *spi)
अणु
	काष्ठा ad5624r_state *st;
	काष्ठा iio_dev *indio_dev;
	पूर्णांक ret, voltage_uv = 0;

	indio_dev = devm_iio_device_alloc(&spi->dev, माप(*st));
	अगर (!indio_dev)
		वापस -ENOMEM;
	st = iio_priv(indio_dev);
	st->reg = devm_regulator_get(&spi->dev, "vcc");
	अगर (!IS_ERR(st->reg)) अणु
		ret = regulator_enable(st->reg);
		अगर (ret)
			वापस ret;

		ret = regulator_get_voltage(st->reg);
		अगर (ret < 0)
			जाओ error_disable_reg;

		voltage_uv = ret;
	पूर्ण

	spi_set_drvdata(spi, indio_dev);
	st->chip_info =
		&ad5624r_chip_info_tbl[spi_get_device_id(spi)->driver_data];

	अगर (voltage_uv)
		st->vref_mv = voltage_uv / 1000;
	अन्यथा
		st->vref_mv = st->chip_info->पूर्णांक_vref_mv;

	st->us = spi;

	indio_dev->name = spi_get_device_id(spi)->name;
	indio_dev->info = &ad5624r_info;
	indio_dev->modes = INDIO_सूचीECT_MODE;
	indio_dev->channels = st->chip_info->channels;
	indio_dev->num_channels = AD5624R_DAC_CHANNELS;

	ret = ad5624r_spi_ग_लिखो(spi, AD5624R_CMD_INTERNAL_REFER_SETUP, 0,
				!!voltage_uv, 16);
	अगर (ret)
		जाओ error_disable_reg;

	ret = iio_device_रेजिस्टर(indio_dev);
	अगर (ret)
		जाओ error_disable_reg;

	वापस 0;

error_disable_reg:
	अगर (!IS_ERR(st->reg))
		regulator_disable(st->reg);

	वापस ret;
पूर्ण

अटल पूर्णांक ad5624r_हटाओ(काष्ठा spi_device *spi)
अणु
	काष्ठा iio_dev *indio_dev = spi_get_drvdata(spi);
	काष्ठा ad5624r_state *st = iio_priv(indio_dev);

	iio_device_unरेजिस्टर(indio_dev);
	अगर (!IS_ERR(st->reg))
		regulator_disable(st->reg);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा spi_device_id ad5624r_id[] = अणु
	अणु"ad5624r3", ID_AD5624R3पूर्ण,
	अणु"ad5644r3", ID_AD5644R3पूर्ण,
	अणु"ad5664r3", ID_AD5664R3पूर्ण,
	अणु"ad5624r5", ID_AD5624R5पूर्ण,
	अणु"ad5644r5", ID_AD5644R5पूर्ण,
	अणु"ad5664r5", ID_AD5664R5पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(spi, ad5624r_id);

अटल काष्ठा spi_driver ad5624r_driver = अणु
	.driver = अणु
		   .name = "ad5624r",
		   पूर्ण,
	.probe = ad5624r_probe,
	.हटाओ = ad5624r_हटाओ,
	.id_table = ad5624r_id,
पूर्ण;
module_spi_driver(ad5624r_driver);

MODULE_AUTHOR("Barry Song <21cnbao@gmail.com>");
MODULE_DESCRIPTION("Analog Devices AD5624/44/64R DAC spi driver");
MODULE_LICENSE("GPL v2");
