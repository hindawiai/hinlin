<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * LTC2632 Digital to analog convertors spi driver
 *
 * Copyright 2017 Maxime Roussin-Bथऊlanger
 * expanded by Silvan Murer <silvan.murer@gmail.com>
 */

#समावेश <linux/device.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/module.h>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/regulator/consumer.h>

#समावेश <यंत्र/unaligned.h>

#घोषणा LTC2632_CMD_WRITE_INPUT_N               0x0
#घोषणा LTC2632_CMD_UPDATE_DAC_N                0x1
#घोषणा LTC2632_CMD_WRITE_INPUT_N_UPDATE_ALL    0x2
#घोषणा LTC2632_CMD_WRITE_INPUT_N_UPDATE_N      0x3
#घोषणा LTC2632_CMD_POWERDOWN_DAC_N             0x4
#घोषणा LTC2632_CMD_POWERDOWN_CHIP              0x5
#घोषणा LTC2632_CMD_INTERNAL_REFER              0x6
#घोषणा LTC2632_CMD_EXTERNAL_REFER              0x7

/**
 * काष्ठा ltc2632_chip_info - chip specअगरic inक्रमmation
 * @channels:		channel spec क्रम the DAC
 * @num_channels:	DAC channel count of the chip
 * @vref_mv:		पूर्णांकernal reference voltage
 */
काष्ठा ltc2632_chip_info अणु
	स्थिर काष्ठा iio_chan_spec *channels;
	स्थिर माप_प्रकार num_channels;
	स्थिर पूर्णांक vref_mv;
पूर्ण;

/**
 * काष्ठा ltc2632_state - driver instance specअगरic data
 * @spi_dev:			poपूर्णांकer to the spi_device काष्ठा
 * @घातerकरोwn_cache_mask:	used to show current channel घातerकरोwn state
 * @vref_mv:			used reference voltage (पूर्णांकernal or बाह्यal)
 * @vref_reg:		regulator क्रम the reference voltage
 */
काष्ठा ltc2632_state अणु
	काष्ठा spi_device *spi_dev;
	अचिन्हित पूर्णांक घातerकरोwn_cache_mask;
	पूर्णांक vref_mv;
	काष्ठा regulator *vref_reg;
पूर्ण;

क्रमागत ltc2632_supported_device_ids अणु
	ID_LTC2632L12,
	ID_LTC2632L10,
	ID_LTC2632L8,
	ID_LTC2632H12,
	ID_LTC2632H10,
	ID_LTC2632H8,
	ID_LTC2634L12,
	ID_LTC2634L10,
	ID_LTC2634L8,
	ID_LTC2634H12,
	ID_LTC2634H10,
	ID_LTC2634H8,
	ID_LTC2636L12,
	ID_LTC2636L10,
	ID_LTC2636L8,
	ID_LTC2636H12,
	ID_LTC2636H10,
	ID_LTC2636H8,
पूर्ण;

अटल पूर्णांक ltc2632_spi_ग_लिखो(काष्ठा spi_device *spi,
			     u8 cmd, u8 addr, u16 val, u8 shअगरt)
अणु
	u32 data;
	u8 msg[3];

	/*
	 * The input shअगरt रेजिस्टर is 24 bits wide.
	 * The next four are the command bits, C3 to C0,
	 * followed by the 4-bit DAC address, A3 to A0, and then the
	 * 12-, 10-, 8-bit data-word. The data-word comprises the 12-,
	 * 10-, 8-bit input code followed by 4, 6, or 8 करोn't care bits.
	 */
	data = (cmd << 20) | (addr << 16) | (val << shअगरt);
	put_unaligned_be24(data, &msg[0]);

	वापस spi_ग_लिखो(spi, msg, माप(msg));
पूर्ण

अटल पूर्णांक ltc2632_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			    काष्ठा iio_chan_spec स्थिर *chan,
			    पूर्णांक *val,
			    पूर्णांक *val2,
			    दीर्घ m)
अणु
	स्थिर काष्ठा ltc2632_state *st = iio_priv(indio_dev);

	चयन (m) अणु
	हाल IIO_CHAN_INFO_SCALE:
		*val = st->vref_mv;
		*val2 = chan->scan_type.realbits;
		वापस IIO_VAL_FRACTIONAL_LOG2;
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक ltc2632_ग_लिखो_raw(काष्ठा iio_dev *indio_dev,
			     काष्ठा iio_chan_spec स्थिर *chan,
			     पूर्णांक val,
			     पूर्णांक val2,
			     दीर्घ mask)
अणु
	काष्ठा ltc2632_state *st = iio_priv(indio_dev);

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		अगर (val >= (1 << chan->scan_type.realbits) || val < 0)
			वापस -EINVAL;

		वापस ltc2632_spi_ग_लिखो(st->spi_dev,
					 LTC2632_CMD_WRITE_INPUT_N_UPDATE_N,
					 chan->address, val,
					 chan->scan_type.shअगरt);
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल sमाप_प्रकार ltc2632_पढ़ो_dac_घातerकरोwn(काष्ठा iio_dev *indio_dev,
					  uपूर्णांकptr_t निजी,
					  स्थिर काष्ठा iio_chan_spec *chan,
					  अक्षर *buf)
अणु
	काष्ठा ltc2632_state *st = iio_priv(indio_dev);

	वापस sysfs_emit(buf, "%d\n",
			  !!(st->घातerकरोwn_cache_mask & (1 << chan->channel)));
पूर्ण

अटल sमाप_प्रकार ltc2632_ग_लिखो_dac_घातerकरोwn(काष्ठा iio_dev *indio_dev,
					   uपूर्णांकptr_t निजी,
					   स्थिर काष्ठा iio_chan_spec *chan,
					   स्थिर अक्षर *buf,
					   माप_प्रकार len)
अणु
	bool pwr_करोwn;
	पूर्णांक ret;
	काष्ठा ltc2632_state *st = iio_priv(indio_dev);

	ret = strtobool(buf, &pwr_करोwn);
	अगर (ret)
		वापस ret;

	अगर (pwr_करोwn)
		st->घातerकरोwn_cache_mask |= (1 << chan->channel);
	अन्यथा
		st->घातerकरोwn_cache_mask &= ~(1 << chan->channel);

	ret = ltc2632_spi_ग_लिखो(st->spi_dev,
				LTC2632_CMD_POWERDOWN_DAC_N,
				chan->channel, 0, 0);

	वापस ret ? ret : len;
पूर्ण

अटल स्थिर काष्ठा iio_info ltc2632_info = अणु
	.ग_लिखो_raw	= ltc2632_ग_लिखो_raw,
	.पढ़ो_raw	= ltc2632_पढ़ो_raw,
पूर्ण;

अटल स्थिर काष्ठा iio_chan_spec_ext_info ltc2632_ext_info[] = अणु
	अणु
		.name = "powerdown",
		.पढ़ो = ltc2632_पढ़ो_dac_घातerकरोwn,
		.ग_लिखो = ltc2632_ग_लिखो_dac_घातerकरोwn,
		.shared = IIO_SEPARATE,
	पूर्ण,
	अणु पूर्ण,
पूर्ण;

#घोषणा LTC2632_CHANNEL(_chan, _bits) अणु \
		.type = IIO_VOLTAGE, \
		.indexed = 1, \
		.output = 1, \
		.channel = (_chan), \
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW), \
		.info_mask_shared_by_type = BIT(IIO_CHAN_INFO_SCALE), \
		.address = (_chan), \
		.scan_type = अणु \
			.realbits	= (_bits), \
			.shअगरt		= 16 - (_bits), \
		पूर्ण, \
		.ext_info = ltc2632_ext_info, \
पूर्ण

#घोषणा DECLARE_LTC2632_CHANNELS(_name, _bits) \
	स्थिर काष्ठा iio_chan_spec _name ## _channels[] = अणु \
		LTC2632_CHANNEL(0, _bits), \
		LTC2632_CHANNEL(1, _bits), \
		LTC2632_CHANNEL(2, _bits), \
		LTC2632_CHANNEL(3, _bits), \
		LTC2632_CHANNEL(4, _bits), \
		LTC2632_CHANNEL(5, _bits), \
		LTC2632_CHANNEL(6, _bits), \
		LTC2632_CHANNEL(7, _bits), \
	पूर्ण

अटल DECLARE_LTC2632_CHANNELS(ltc2632x12, 12);
अटल DECLARE_LTC2632_CHANNELS(ltc2632x10, 10);
अटल DECLARE_LTC2632_CHANNELS(ltc2632x8, 8);

अटल स्थिर काष्ठा ltc2632_chip_info ltc2632_chip_info_tbl[] = अणु
	[ID_LTC2632L12] = अणु
		.channels	= ltc2632x12_channels,
		.num_channels	= 2,
		.vref_mv	= 2500,
	पूर्ण,
	[ID_LTC2632L10] = अणु
		.channels	= ltc2632x10_channels,
		.num_channels	= 2,
		.vref_mv	= 2500,
	पूर्ण,
	[ID_LTC2632L8] =  अणु
		.channels	= ltc2632x8_channels,
		.num_channels	= 2,
		.vref_mv	= 2500,
	पूर्ण,
	[ID_LTC2632H12] = अणु
		.channels	= ltc2632x12_channels,
		.num_channels	= 2,
		.vref_mv	= 4096,
	पूर्ण,
	[ID_LTC2632H10] = अणु
		.channels	= ltc2632x10_channels,
		.num_channels	= 2,
		.vref_mv	= 4096,
	पूर्ण,
	[ID_LTC2632H8] =  अणु
		.channels	= ltc2632x8_channels,
		.num_channels	= 2,
		.vref_mv	= 4096,
	पूर्ण,
	[ID_LTC2634L12] = अणु
		.channels	= ltc2632x12_channels,
		.num_channels	= 4,
		.vref_mv	= 2500,
	पूर्ण,
	[ID_LTC2634L10] = अणु
		.channels	= ltc2632x10_channels,
		.num_channels	= 4,
		.vref_mv	= 2500,
	पूर्ण,
	[ID_LTC2634L8] =  अणु
		.channels	= ltc2632x8_channels,
		.num_channels	= 4,
		.vref_mv	= 2500,
	पूर्ण,
	[ID_LTC2634H12] = अणु
		.channels	= ltc2632x12_channels,
		.num_channels	= 4,
		.vref_mv	= 4096,
	पूर्ण,
	[ID_LTC2634H10] = अणु
		.channels	= ltc2632x10_channels,
		.num_channels	= 4,
		.vref_mv	= 4096,
	पूर्ण,
	[ID_LTC2634H8] =  अणु
		.channels	= ltc2632x8_channels,
		.num_channels	= 4,
		.vref_mv	= 4096,
	पूर्ण,
	[ID_LTC2636L12] = अणु
		.channels	= ltc2632x12_channels,
		.num_channels	= 8,
		.vref_mv	= 2500,
	पूर्ण,
	[ID_LTC2636L10] = अणु
		.channels	= ltc2632x10_channels,
		.num_channels	= 8,
		.vref_mv	= 2500,
	पूर्ण,
	[ID_LTC2636L8] =  अणु
		.channels	= ltc2632x8_channels,
		.num_channels	= 8,
		.vref_mv	= 2500,
	पूर्ण,
	[ID_LTC2636H12] = अणु
		.channels	= ltc2632x12_channels,
		.num_channels	= 8,
		.vref_mv	= 4096,
	पूर्ण,
	[ID_LTC2636H10] = अणु
		.channels	= ltc2632x10_channels,
		.num_channels	= 8,
		.vref_mv	= 4096,
	पूर्ण,
	[ID_LTC2636H8] =  अणु
		.channels	= ltc2632x8_channels,
		.num_channels	= 8,
		.vref_mv	= 4096,
	पूर्ण,
पूर्ण;

अटल पूर्णांक ltc2632_probe(काष्ठा spi_device *spi)
अणु
	काष्ठा ltc2632_state *st;
	काष्ठा iio_dev *indio_dev;
	काष्ठा ltc2632_chip_info *chip_info;
	पूर्णांक ret;

	indio_dev = devm_iio_device_alloc(&spi->dev, माप(*st));
	अगर (!indio_dev)
		वापस -ENOMEM;

	st = iio_priv(indio_dev);

	spi_set_drvdata(spi, indio_dev);
	st->spi_dev = spi;

	chip_info = (काष्ठा ltc2632_chip_info *)
			spi_get_device_id(spi)->driver_data;

	st->vref_reg = devm_regulator_get_optional(&spi->dev, "vref");
	अगर (PTR_ERR(st->vref_reg) == -ENODEV) अणु
		/* use पूर्णांकernal reference voltage */
		st->vref_reg = शून्य;
		st->vref_mv = chip_info->vref_mv;

		ret = ltc2632_spi_ग_लिखो(spi, LTC2632_CMD_INTERNAL_REFER,
				0, 0, 0);
		अगर (ret) अणु
			dev_err(&spi->dev,
				"Set internal reference command failed, %d\n",
				ret);
			वापस ret;
		पूर्ण
	पूर्ण अन्यथा अगर (IS_ERR(st->vref_reg)) अणु
		dev_err(&spi->dev,
				"Error getting voltage reference regulator\n");
		वापस PTR_ERR(st->vref_reg);
	पूर्ण अन्यथा अणु
		/* use बाह्यal reference voltage */
		ret = regulator_enable(st->vref_reg);
		अगर (ret) अणु
			dev_err(&spi->dev,
				"enable reference regulator failed, %d\n",
				ret);
			वापस ret;
		पूर्ण
		st->vref_mv = regulator_get_voltage(st->vref_reg) / 1000;

		ret = ltc2632_spi_ग_लिखो(spi, LTC2632_CMD_EXTERNAL_REFER,
				0, 0, 0);
		अगर (ret) अणु
			dev_err(&spi->dev,
				"Set external reference command failed, %d\n",
				ret);
			वापस ret;
		पूर्ण
	पूर्ण

	indio_dev->name = dev_of_node(&spi->dev) ? dev_of_node(&spi->dev)->name
						 : spi_get_device_id(spi)->name;
	indio_dev->info = &ltc2632_info;
	indio_dev->modes = INDIO_सूचीECT_MODE;
	indio_dev->channels = chip_info->channels;
	indio_dev->num_channels = chip_info->num_channels;

	वापस iio_device_रेजिस्टर(indio_dev);
पूर्ण

अटल पूर्णांक ltc2632_हटाओ(काष्ठा spi_device *spi)
अणु
	काष्ठा iio_dev *indio_dev = spi_get_drvdata(spi);
	काष्ठा ltc2632_state *st = iio_priv(indio_dev);

	iio_device_unरेजिस्टर(indio_dev);

	अगर (st->vref_reg)
		regulator_disable(st->vref_reg);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा spi_device_id ltc2632_id[] = अणु
	अणु "ltc2632-l12", (kernel_uदीर्घ_t)&ltc2632_chip_info_tbl[ID_LTC2632L12] पूर्ण,
	अणु "ltc2632-l10", (kernel_uदीर्घ_t)&ltc2632_chip_info_tbl[ID_LTC2632L10] पूर्ण,
	अणु "ltc2632-l8", (kernel_uदीर्घ_t)&ltc2632_chip_info_tbl[ID_LTC2632L8] पूर्ण,
	अणु "ltc2632-h12", (kernel_uदीर्घ_t)&ltc2632_chip_info_tbl[ID_LTC2632H12] पूर्ण,
	अणु "ltc2632-h10", (kernel_uदीर्घ_t)&ltc2632_chip_info_tbl[ID_LTC2632H10] पूर्ण,
	अणु "ltc2632-h8", (kernel_uदीर्घ_t)&ltc2632_chip_info_tbl[ID_LTC2632H8] पूर्ण,
	अणु "ltc2634-l12", (kernel_uदीर्घ_t)&ltc2632_chip_info_tbl[ID_LTC2634L12] पूर्ण,
	अणु "ltc2634-l10", (kernel_uदीर्घ_t)&ltc2632_chip_info_tbl[ID_LTC2634L10] पूर्ण,
	अणु "ltc2634-l8", (kernel_uदीर्घ_t)&ltc2632_chip_info_tbl[ID_LTC2634L8] पूर्ण,
	अणु "ltc2634-h12", (kernel_uदीर्घ_t)&ltc2632_chip_info_tbl[ID_LTC2634H12] पूर्ण,
	अणु "ltc2634-h10", (kernel_uदीर्घ_t)&ltc2632_chip_info_tbl[ID_LTC2634H10] पूर्ण,
	अणु "ltc2634-h8", (kernel_uदीर्घ_t)&ltc2632_chip_info_tbl[ID_LTC2634H8] पूर्ण,
	अणु "ltc2636-l12", (kernel_uदीर्घ_t)&ltc2632_chip_info_tbl[ID_LTC2636L12] पूर्ण,
	अणु "ltc2636-l10", (kernel_uदीर्घ_t)&ltc2632_chip_info_tbl[ID_LTC2636L10] पूर्ण,
	अणु "ltc2636-l8", (kernel_uदीर्घ_t)&ltc2632_chip_info_tbl[ID_LTC2636L8] पूर्ण,
	अणु "ltc2636-h12", (kernel_uदीर्घ_t)&ltc2632_chip_info_tbl[ID_LTC2636H12] पूर्ण,
	अणु "ltc2636-h10", (kernel_uदीर्घ_t)&ltc2632_chip_info_tbl[ID_LTC2636H10] पूर्ण,
	अणु "ltc2636-h8", (kernel_uदीर्घ_t)&ltc2632_chip_info_tbl[ID_LTC2636H8] पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(spi, ltc2632_id);

अटल स्थिर काष्ठा of_device_id ltc2632_of_match[] = अणु
	अणु
		.compatible = "lltc,ltc2632-l12",
		.data = &ltc2632_chip_info_tbl[ID_LTC2632L12]
	पूर्ण, अणु
		.compatible = "lltc,ltc2632-l10",
		.data = &ltc2632_chip_info_tbl[ID_LTC2632L10]
	पूर्ण, अणु
		.compatible = "lltc,ltc2632-l8",
		.data = &ltc2632_chip_info_tbl[ID_LTC2632L8]
	पूर्ण, अणु
		.compatible = "lltc,ltc2632-h12",
		.data = &ltc2632_chip_info_tbl[ID_LTC2632H12]
	पूर्ण, अणु
		.compatible = "lltc,ltc2632-h10",
		.data = &ltc2632_chip_info_tbl[ID_LTC2632H10]
	पूर्ण, अणु
		.compatible = "lltc,ltc2632-h8",
		.data = &ltc2632_chip_info_tbl[ID_LTC2632H8]
	पूर्ण, अणु
		.compatible = "lltc,ltc2634-l12",
		.data = &ltc2632_chip_info_tbl[ID_LTC2634L12]
	पूर्ण, अणु
		.compatible = "lltc,ltc2634-l10",
		.data = &ltc2632_chip_info_tbl[ID_LTC2634L10]
	पूर्ण, अणु
		.compatible = "lltc,ltc2634-l8",
		.data = &ltc2632_chip_info_tbl[ID_LTC2634L8]
	पूर्ण, अणु
		.compatible = "lltc,ltc2634-h12",
		.data = &ltc2632_chip_info_tbl[ID_LTC2634H12]
	पूर्ण, अणु
		.compatible = "lltc,ltc2634-h10",
		.data = &ltc2632_chip_info_tbl[ID_LTC2634H10]
	पूर्ण, अणु
		.compatible = "lltc,ltc2634-h8",
		.data = &ltc2632_chip_info_tbl[ID_LTC2634H8]
	पूर्ण, अणु
		.compatible = "lltc,ltc2636-l12",
		.data = &ltc2632_chip_info_tbl[ID_LTC2636L12]
	पूर्ण, अणु
		.compatible = "lltc,ltc2636-l10",
		.data = &ltc2632_chip_info_tbl[ID_LTC2636L10]
	पूर्ण, अणु
		.compatible = "lltc,ltc2636-l8",
		.data = &ltc2632_chip_info_tbl[ID_LTC2636L8]
	पूर्ण, अणु
		.compatible = "lltc,ltc2636-h12",
		.data = &ltc2632_chip_info_tbl[ID_LTC2636H12]
	पूर्ण, अणु
		.compatible = "lltc,ltc2636-h10",
		.data = &ltc2632_chip_info_tbl[ID_LTC2636H10]
	पूर्ण, अणु
		.compatible = "lltc,ltc2636-h8",
		.data = &ltc2632_chip_info_tbl[ID_LTC2636H8]
	पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, ltc2632_of_match);

अटल काष्ठा spi_driver ltc2632_driver = अणु
	.driver		= अणु
		.name	= "ltc2632",
		.of_match_table = of_match_ptr(ltc2632_of_match),
	पूर्ण,
	.probe		= ltc2632_probe,
	.हटाओ		= ltc2632_हटाओ,
	.id_table	= ltc2632_id,
पूर्ण;
module_spi_driver(ltc2632_driver);

MODULE_AUTHOR("Maxime Roussin-Belanger <maxime.roussinbelanger@gmail.com>");
MODULE_DESCRIPTION("LTC2632 DAC SPI driver");
MODULE_LICENSE("GPL v2");
