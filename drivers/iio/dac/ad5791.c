<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * AD5760, AD5780, AD5781, AD5790, AD5791 Voltage Output Digital to Analog
 * Converter
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
#समावेश <linux/iio/dac/ad5791.h>

#घोषणा AD5791_DAC_MASK			GENMASK(19, 0)

#घोषणा AD5791_CMD_READ			BIT(23)
#घोषणा AD5791_CMD_WRITE		0
#घोषणा AD5791_ADDR(addr)		((addr) << 20)

/* Registers */
#घोषणा AD5791_ADDR_NOOP		0
#घोषणा AD5791_ADDR_DAC0		1
#घोषणा AD5791_ADDR_CTRL		2
#घोषणा AD5791_ADDR_CLRCODE		3
#घोषणा AD5791_ADDR_SW_CTRL		4

/* Control Register */
#घोषणा AD5791_CTRL_RBUF		BIT(1)
#घोषणा AD5791_CTRL_OPGND		BIT(2)
#घोषणा AD5791_CTRL_DACTRI		BIT(3)
#घोषणा AD5791_CTRL_BIN2SC		BIT(4)
#घोषणा AD5791_CTRL_SDODIS		BIT(5)
#घोषणा AD5761_CTRL_LINCOMP(x)		((x) << 6)

#घोषणा AD5791_LINCOMP_0_10		0
#घोषणा AD5791_LINCOMP_10_12		1
#घोषणा AD5791_LINCOMP_12_16		2
#घोषणा AD5791_LINCOMP_16_19		3
#घोषणा AD5791_LINCOMP_19_20		12

#घोषणा AD5780_LINCOMP_0_10		0
#घोषणा AD5780_LINCOMP_10_20		12

/* Software Control Register */
#घोषणा AD5791_SWCTRL_LDAC		BIT(0)
#घोषणा AD5791_SWCTRL_CLR		BIT(1)
#घोषणा AD5791_SWCTRL_RESET		BIT(2)

#घोषणा AD5791_DAC_PWRDN_6K		0
#घोषणा AD5791_DAC_PWRDN_3STATE		1

/**
 * काष्ठा ad5791_chip_info - chip specअगरic inक्रमmation
 * @get_lin_comp:	function poपूर्णांकer to the device specअगरic function
 */

काष्ठा ad5791_chip_info अणु
	पूर्णांक (*get_lin_comp)	(अचिन्हित पूर्णांक span);
पूर्ण;

/**
 * काष्ठा ad5791_state - driver instance specअगरic data
 * @spi:			spi_device
 * @reg_vdd:		positive supply regulator
 * @reg_vss:		negative supply regulator
 * @chip_info:		chip model specअगरic स्थिरants
 * @vref_mv:		actual reference voltage used
 * @vref_neg_mv:	voltage of the negative supply
 * @ctrl:		control रेजिस्टर cache
 * @pwr_करोwn_mode:	current घातer करोwn mode
 * @pwr_करोwn:		true अगर device is घातered करोwn
 * @data:		spi transfer buffers
 */
काष्ठा ad5791_state अणु
	काष्ठा spi_device		*spi;
	काष्ठा regulator		*reg_vdd;
	काष्ठा regulator		*reg_vss;
	स्थिर काष्ठा ad5791_chip_info	*chip_info;
	अचिन्हित लघु			vref_mv;
	अचिन्हित पूर्णांक			vref_neg_mv;
	अचिन्हित			ctrl;
	अचिन्हित			pwr_करोwn_mode;
	bool				pwr_करोwn;

	जोड़ अणु
		__be32 d32;
		u8 d8[4];
	पूर्ण data[3] ____cacheline_aligned;
पूर्ण;

क्रमागत ad5791_supported_device_ids अणु
	ID_AD5760,
	ID_AD5780,
	ID_AD5781,
	ID_AD5791,
पूर्ण;

अटल पूर्णांक ad5791_spi_ग_लिखो(काष्ठा ad5791_state *st, u8 addr, u32 val)
अणु
	st->data[0].d32 = cpu_to_be32(AD5791_CMD_WRITE |
			      AD5791_ADDR(addr) |
			      (val & AD5791_DAC_MASK));

	वापस spi_ग_लिखो(st->spi, &st->data[0].d8[1], 3);
पूर्ण

अटल पूर्णांक ad5791_spi_पढ़ो(काष्ठा ad5791_state *st, u8 addr, u32 *val)
अणु
	पूर्णांक ret;
	काष्ठा spi_transfer xfers[] = अणु
		अणु
			.tx_buf = &st->data[0].d8[1],
			.bits_per_word = 8,
			.len = 3,
			.cs_change = 1,
		पूर्ण, अणु
			.tx_buf = &st->data[1].d8[1],
			.rx_buf = &st->data[2].d8[1],
			.bits_per_word = 8,
			.len = 3,
		पूर्ण,
	पूर्ण;

	st->data[0].d32 = cpu_to_be32(AD5791_CMD_READ |
			      AD5791_ADDR(addr));
	st->data[1].d32 = cpu_to_be32(AD5791_ADDR(AD5791_ADDR_NOOP));

	ret = spi_sync_transfer(st->spi, xfers, ARRAY_SIZE(xfers));

	*val = be32_to_cpu(st->data[2].d32);

	वापस ret;
पूर्ण

अटल स्थिर अक्षर * स्थिर ad5791_घातerकरोwn_modes[] = अणु
	"6kohm_to_gnd",
	"three_state",
पूर्ण;

अटल पूर्णांक ad5791_get_घातerकरोwn_mode(काष्ठा iio_dev *indio_dev,
	स्थिर काष्ठा iio_chan_spec *chan)
अणु
	काष्ठा ad5791_state *st = iio_priv(indio_dev);

	वापस st->pwr_करोwn_mode;
पूर्ण

अटल पूर्णांक ad5791_set_घातerकरोwn_mode(काष्ठा iio_dev *indio_dev,
	स्थिर काष्ठा iio_chan_spec *chan, अचिन्हित पूर्णांक mode)
अणु
	काष्ठा ad5791_state *st = iio_priv(indio_dev);

	st->pwr_करोwn_mode = mode;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा iio_क्रमागत ad5791_घातerकरोwn_mode_क्रमागत = अणु
	.items = ad5791_घातerकरोwn_modes,
	.num_items = ARRAY_SIZE(ad5791_घातerकरोwn_modes),
	.get = ad5791_get_घातerकरोwn_mode,
	.set = ad5791_set_घातerकरोwn_mode,
पूर्ण;

अटल sमाप_प्रकार ad5791_पढ़ो_dac_घातerकरोwn(काष्ठा iio_dev *indio_dev,
	uपूर्णांकptr_t निजी, स्थिर काष्ठा iio_chan_spec *chan, अक्षर *buf)
अणु
	काष्ठा ad5791_state *st = iio_priv(indio_dev);

	वापस sysfs_emit(buf, "%d\n", st->pwr_करोwn);
पूर्ण

अटल sमाप_प्रकार ad5791_ग_लिखो_dac_घातerकरोwn(काष्ठा iio_dev *indio_dev,
	 uपूर्णांकptr_t निजी, स्थिर काष्ठा iio_chan_spec *chan, स्थिर अक्षर *buf,
	 माप_प्रकार len)
अणु
	bool pwr_करोwn;
	पूर्णांक ret;
	काष्ठा ad5791_state *st = iio_priv(indio_dev);

	ret = strtobool(buf, &pwr_करोwn);
	अगर (ret)
		वापस ret;

	अगर (!pwr_करोwn) अणु
		st->ctrl &= ~(AD5791_CTRL_OPGND | AD5791_CTRL_DACTRI);
	पूर्ण अन्यथा अणु
		अगर (st->pwr_करोwn_mode == AD5791_DAC_PWRDN_6K)
			st->ctrl |= AD5791_CTRL_OPGND;
		अन्यथा अगर (st->pwr_करोwn_mode == AD5791_DAC_PWRDN_3STATE)
			st->ctrl |= AD5791_CTRL_DACTRI;
	पूर्ण
	st->pwr_करोwn = pwr_करोwn;

	ret = ad5791_spi_ग_लिखो(st, AD5791_ADDR_CTRL, st->ctrl);

	वापस ret ? ret : len;
पूर्ण

अटल पूर्णांक ad5791_get_lin_comp(अचिन्हित पूर्णांक span)
अणु
	अगर (span <= 10000)
		वापस AD5791_LINCOMP_0_10;
	अन्यथा अगर (span <= 12000)
		वापस AD5791_LINCOMP_10_12;
	अन्यथा अगर (span <= 16000)
		वापस AD5791_LINCOMP_12_16;
	अन्यथा अगर (span <= 19000)
		वापस AD5791_LINCOMP_16_19;
	अन्यथा
		वापस AD5791_LINCOMP_19_20;
पूर्ण

अटल पूर्णांक ad5780_get_lin_comp(अचिन्हित पूर्णांक span)
अणु
	अगर (span <= 10000)
		वापस AD5780_LINCOMP_0_10;
	अन्यथा
		वापस AD5780_LINCOMP_10_20;
पूर्ण
अटल स्थिर काष्ठा ad5791_chip_info ad5791_chip_info_tbl[] = अणु
	[ID_AD5760] = अणु
		.get_lin_comp = ad5780_get_lin_comp,
	पूर्ण,
	[ID_AD5780] = अणु
		.get_lin_comp = ad5780_get_lin_comp,
	पूर्ण,
	[ID_AD5781] = अणु
		.get_lin_comp = ad5791_get_lin_comp,
	पूर्ण,
	[ID_AD5791] = अणु
		.get_lin_comp = ad5791_get_lin_comp,
	पूर्ण,
पूर्ण;

अटल पूर्णांक ad5791_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			   काष्ठा iio_chan_spec स्थिर *chan,
			   पूर्णांक *val,
			   पूर्णांक *val2,
			   दीर्घ m)
अणु
	काष्ठा ad5791_state *st = iio_priv(indio_dev);
	u64 val64;
	पूर्णांक ret;

	चयन (m) अणु
	हाल IIO_CHAN_INFO_RAW:
		ret = ad5791_spi_पढ़ो(st, chan->address, val);
		अगर (ret)
			वापस ret;
		*val &= AD5791_DAC_MASK;
		*val >>= chan->scan_type.shअगरt;
		वापस IIO_VAL_INT;
	हाल IIO_CHAN_INFO_SCALE:
		*val = st->vref_mv;
		*val2 = (1 << chan->scan_type.realbits) - 1;
		वापस IIO_VAL_FRACTIONAL;
	हाल IIO_CHAN_INFO_OFFSET:
		val64 = (((u64)st->vref_neg_mv) << chan->scan_type.realbits);
		करो_भाग(val64, st->vref_mv);
		*val = -val64;
		वापस IIO_VAL_INT;
	शेष:
		वापस -EINVAL;
	पूर्ण

पूर्ण;

अटल स्थिर काष्ठा iio_chan_spec_ext_info ad5791_ext_info[] = अणु
	अणु
		.name = "powerdown",
		.shared = IIO_SHARED_BY_TYPE,
		.पढ़ो = ad5791_पढ़ो_dac_घातerकरोwn,
		.ग_लिखो = ad5791_ग_लिखो_dac_घातerकरोwn,
	पूर्ण,
	IIO_ENUM("powerdown_mode", IIO_SHARED_BY_TYPE,
		 &ad5791_घातerकरोwn_mode_क्रमागत),
	IIO_ENUM_AVAILABLE("powerdown_mode", &ad5791_घातerकरोwn_mode_क्रमागत),
	अणु पूर्ण,
पूर्ण;

#घोषणा AD5791_CHAN(bits, _shअगरt) अणु			\
	.type = IIO_VOLTAGE,				\
	.output = 1,					\
	.indexed = 1,					\
	.address = AD5791_ADDR_DAC0,			\
	.channel = 0,					\
	.info_mask_separate = BIT(IIO_CHAN_INFO_RAW),	\
	.info_mask_shared_by_type = BIT(IIO_CHAN_INFO_SCALE) |	\
		BIT(IIO_CHAN_INFO_OFFSET),		\
	.scan_type = अणु					\
		.sign = 'u',				\
		.realbits = (bits),			\
		.storagebits = 24,			\
		.shअगरt = (_shअगरt),			\
	पूर्ण,						\
	.ext_info = ad5791_ext_info,			\
पूर्ण

अटल स्थिर काष्ठा iio_chan_spec ad5791_channels[] = अणु
	[ID_AD5760] = AD5791_CHAN(16, 4),
	[ID_AD5780] = AD5791_CHAN(18, 2),
	[ID_AD5781] = AD5791_CHAN(18, 2),
	[ID_AD5791] = AD5791_CHAN(20, 0)
पूर्ण;

अटल पूर्णांक ad5791_ग_लिखो_raw(काष्ठा iio_dev *indio_dev,
			    काष्ठा iio_chan_spec स्थिर *chan,
			    पूर्णांक val,
			    पूर्णांक val2,
			    दीर्घ mask)
अणु
	काष्ठा ad5791_state *st = iio_priv(indio_dev);

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		val &= GENMASK(chan->scan_type.realbits - 1, 0);
		val <<= chan->scan_type.shअगरt;

		वापस ad5791_spi_ग_लिखो(st, chan->address, val);

	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा iio_info ad5791_info = अणु
	.पढ़ो_raw = &ad5791_पढ़ो_raw,
	.ग_लिखो_raw = &ad5791_ग_लिखो_raw,
पूर्ण;

अटल पूर्णांक ad5791_probe(काष्ठा spi_device *spi)
अणु
	काष्ठा ad5791_platक्रमm_data *pdata = spi->dev.platक्रमm_data;
	काष्ठा iio_dev *indio_dev;
	काष्ठा ad5791_state *st;
	पूर्णांक ret, pos_voltage_uv = 0, neg_voltage_uv = 0;

	indio_dev = devm_iio_device_alloc(&spi->dev, माप(*st));
	अगर (!indio_dev)
		वापस -ENOMEM;
	st = iio_priv(indio_dev);
	st->reg_vdd = devm_regulator_get(&spi->dev, "vdd");
	अगर (!IS_ERR(st->reg_vdd)) अणु
		ret = regulator_enable(st->reg_vdd);
		अगर (ret)
			वापस ret;

		ret = regulator_get_voltage(st->reg_vdd);
		अगर (ret < 0)
			जाओ error_disable_reg_pos;

		pos_voltage_uv = ret;
	पूर्ण

	st->reg_vss = devm_regulator_get(&spi->dev, "vss");
	अगर (!IS_ERR(st->reg_vss)) अणु
		ret = regulator_enable(st->reg_vss);
		अगर (ret)
			जाओ error_disable_reg_pos;

		ret = regulator_get_voltage(st->reg_vss);
		अगर (ret < 0)
			जाओ error_disable_reg_neg;

		neg_voltage_uv = ret;
	पूर्ण

	st->pwr_करोwn = true;
	st->spi = spi;

	अगर (!IS_ERR(st->reg_vss) && !IS_ERR(st->reg_vdd)) अणु
		st->vref_mv = (pos_voltage_uv + neg_voltage_uv) / 1000;
		st->vref_neg_mv = neg_voltage_uv / 1000;
	पूर्ण अन्यथा अगर (pdata) अणु
		st->vref_mv = pdata->vref_pos_mv + pdata->vref_neg_mv;
		st->vref_neg_mv = pdata->vref_neg_mv;
	पूर्ण अन्यथा अणु
		dev_warn(&spi->dev, "reference voltage unspecified\n");
	पूर्ण

	ret = ad5791_spi_ग_लिखो(st, AD5791_ADDR_SW_CTRL, AD5791_SWCTRL_RESET);
	अगर (ret)
		जाओ error_disable_reg_neg;

	st->chip_info =	&ad5791_chip_info_tbl[spi_get_device_id(spi)
					      ->driver_data];


	st->ctrl = AD5761_CTRL_LINCOMP(st->chip_info->get_lin_comp(st->vref_mv))
		  | ((pdata && pdata->use_rbuf_gain2) ? 0 : AD5791_CTRL_RBUF) |
		  AD5791_CTRL_BIN2SC;

	ret = ad5791_spi_ग_लिखो(st, AD5791_ADDR_CTRL, st->ctrl |
		AD5791_CTRL_OPGND | AD5791_CTRL_DACTRI);
	अगर (ret)
		जाओ error_disable_reg_neg;

	spi_set_drvdata(spi, indio_dev);
	indio_dev->info = &ad5791_info;
	indio_dev->modes = INDIO_सूचीECT_MODE;
	indio_dev->channels
		= &ad5791_channels[spi_get_device_id(spi)->driver_data];
	indio_dev->num_channels = 1;
	indio_dev->name = spi_get_device_id(st->spi)->name;
	ret = iio_device_रेजिस्टर(indio_dev);
	अगर (ret)
		जाओ error_disable_reg_neg;

	वापस 0;

error_disable_reg_neg:
	अगर (!IS_ERR(st->reg_vss))
		regulator_disable(st->reg_vss);
error_disable_reg_pos:
	अगर (!IS_ERR(st->reg_vdd))
		regulator_disable(st->reg_vdd);
	वापस ret;
पूर्ण

अटल पूर्णांक ad5791_हटाओ(काष्ठा spi_device *spi)
अणु
	काष्ठा iio_dev *indio_dev = spi_get_drvdata(spi);
	काष्ठा ad5791_state *st = iio_priv(indio_dev);

	iio_device_unरेजिस्टर(indio_dev);
	अगर (!IS_ERR(st->reg_vdd))
		regulator_disable(st->reg_vdd);

	अगर (!IS_ERR(st->reg_vss))
		regulator_disable(st->reg_vss);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा spi_device_id ad5791_id[] = अणु
	अणु"ad5760", ID_AD5760पूर्ण,
	अणु"ad5780", ID_AD5780पूर्ण,
	अणु"ad5781", ID_AD5781पूर्ण,
	अणु"ad5790", ID_AD5791पूर्ण,
	अणु"ad5791", ID_AD5791पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(spi, ad5791_id);

अटल काष्ठा spi_driver ad5791_driver = अणु
	.driver = अणु
		   .name = "ad5791",
		   पूर्ण,
	.probe = ad5791_probe,
	.हटाओ = ad5791_हटाओ,
	.id_table = ad5791_id,
पूर्ण;
module_spi_driver(ad5791_driver);

MODULE_AUTHOR("Michael Hennerich <michael.hennerich@analog.com>");
MODULE_DESCRIPTION("Analog Devices AD5760/AD5780/AD5781/AD5790/AD5791 DAC");
MODULE_LICENSE("GPL v2");
