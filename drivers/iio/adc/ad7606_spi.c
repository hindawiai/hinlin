<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * AD7606 SPI ADC driver
 *
 * Copyright 2011 Analog Devices Inc.
 */

#समावेश <linux/module.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/types.h>
#समावेश <linux/err.h>

#समावेश <linux/iio/iपन.स>
#समावेश "ad7606.h"

#घोषणा MAX_SPI_FREQ_HZ		23500000	/* VDRIVE above 4.75 V */

#घोषणा AD7616_CONFIGURATION_REGISTER	0x02
#घोषणा AD7616_OS_MASK			GENMASK(4, 2)
#घोषणा AD7616_BURST_MODE		BIT(6)
#घोषणा AD7616_SEQEN_MODE		BIT(5)
#घोषणा AD7616_RANGE_CH_A_ADDR_OFF	0x04
#घोषणा AD7616_RANGE_CH_B_ADDR_OFF	0x06
/*
 * Range of channels from a group are stored in 2 रेजिस्टरs.
 * 0, 1, 2, 3 in a रेजिस्टर followed by 4, 5, 6, 7 in second रेजिस्टर.
 * For channels from second group(8-15) the order is the same, only with
 * an offset of 2 क्रम रेजिस्टर address.
 */
#घोषणा AD7616_RANGE_CH_ADDR(ch)	((ch) >> 2)
/* The range of the channel is stored in 2 bits */
#घोषणा AD7616_RANGE_CH_MSK(ch)		(0b11 << (((ch) & 0b11) * 2))
#घोषणा AD7616_RANGE_CH_MODE(ch, mode)	((mode) << ((((ch) & 0b11)) * 2))

#घोषणा AD7606_CONFIGURATION_REGISTER	0x02
#घोषणा AD7606_SINGLE_DOUT		0x00

/*
 * Range क्रम AD7606B channels are stored in रेजिस्टरs starting with address 0x3.
 * Each रेजिस्टर stores range क्रम 2 channels(4 bits per channel).
 */
#घोषणा AD7606_RANGE_CH_MSK(ch)		(GENMASK(3, 0) << (4 * ((ch) & 0x1)))
#घोषणा AD7606_RANGE_CH_MODE(ch, mode)	\
	((GENMASK(3, 0) & mode) << (4 * ((ch) & 0x1)))
#घोषणा AD7606_RANGE_CH_ADDR(ch)	(0x03 + ((ch) >> 1))
#घोषणा AD7606_OS_MODE			0x08

अटल स्थिर काष्ठा iio_chan_spec ad7616_sw_channels[] = अणु
	IIO_CHAN_SOFT_TIMESTAMP(16),
	AD7616_CHANNEL(0),
	AD7616_CHANNEL(1),
	AD7616_CHANNEL(2),
	AD7616_CHANNEL(3),
	AD7616_CHANNEL(4),
	AD7616_CHANNEL(5),
	AD7616_CHANNEL(6),
	AD7616_CHANNEL(7),
	AD7616_CHANNEL(8),
	AD7616_CHANNEL(9),
	AD7616_CHANNEL(10),
	AD7616_CHANNEL(11),
	AD7616_CHANNEL(12),
	AD7616_CHANNEL(13),
	AD7616_CHANNEL(14),
	AD7616_CHANNEL(15),
पूर्ण;

अटल स्थिर काष्ठा iio_chan_spec ad7606b_sw_channels[] = अणु
	IIO_CHAN_SOFT_TIMESTAMP(8),
	AD7616_CHANNEL(0),
	AD7616_CHANNEL(1),
	AD7616_CHANNEL(2),
	AD7616_CHANNEL(3),
	AD7616_CHANNEL(4),
	AD7616_CHANNEL(5),
	AD7616_CHANNEL(6),
	AD7616_CHANNEL(7),
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक ad7606B_oversampling_avail[9] = अणु
	1, 2, 4, 8, 16, 32, 64, 128, 256
पूर्ण;

अटल u16 ad7616_spi_rd_wr_cmd(पूर्णांक addr, अक्षर isWriteOp)
अणु
	/*
	 * The address of रेजिस्टर consist of one w/r bit
	 * 6 bits of address followed by one reserved bit.
	 */
	वापस ((addr & 0x7F) << 1) | ((isWriteOp & 0x1) << 7);
पूर्ण

अटल u16 ad7606B_spi_rd_wr_cmd(पूर्णांक addr, अक्षर is_ग_लिखो_op)
अणु
	/*
	 * The address of रेजिस्टर consists of one bit which
	 * specअगरies a पढ़ो command placed in bit 6, followed by
	 * 6 bits of address.
	 */
	वापस (addr & 0x3F) | (((~is_ग_लिखो_op) & 0x1) << 6);
पूर्ण

अटल पूर्णांक ad7606_spi_पढ़ो_block(काष्ठा device *dev,
				 पूर्णांक count, व्योम *buf)
अणु
	काष्ठा spi_device *spi = to_spi_device(dev);
	पूर्णांक i, ret;
	अचिन्हित लघु *data = buf;
	__be16 *bdata = buf;

	ret = spi_पढ़ो(spi, buf, count * 2);
	अगर (ret < 0) अणु
		dev_err(&spi->dev, "SPI read error\n");
		वापस ret;
	पूर्ण

	क्रम (i = 0; i < count; i++)
		data[i] = be16_to_cpu(bdata[i]);

	वापस 0;
पूर्ण

अटल पूर्णांक ad7606_spi_reg_पढ़ो(काष्ठा ad7606_state *st, अचिन्हित पूर्णांक addr)
अणु
	काष्ठा spi_device *spi = to_spi_device(st->dev);
	काष्ठा spi_transfer t[] = अणु
		अणु
			.tx_buf = &st->d16[0],
			.len = 2,
			.cs_change = 0,
		पूर्ण, अणु
			.rx_buf = &st->d16[1],
			.len = 2,
		पूर्ण,
	पूर्ण;
	पूर्णांक ret;

	st->d16[0] = cpu_to_be16(st->bops->rd_wr_cmd(addr, 0) << 8);

	ret = spi_sync_transfer(spi, t, ARRAY_SIZE(t));
	अगर (ret < 0)
		वापस ret;

	वापस be16_to_cpu(st->d16[1]);
पूर्ण

अटल पूर्णांक ad7606_spi_reg_ग_लिखो(काष्ठा ad7606_state *st,
				अचिन्हित पूर्णांक addr,
				अचिन्हित पूर्णांक val)
अणु
	काष्ठा spi_device *spi = to_spi_device(st->dev);

	st->d16[0] = cpu_to_be16((st->bops->rd_wr_cmd(addr, 1) << 8) |
				  (val & 0x1FF));

	वापस spi_ग_लिखो(spi, &st->d16[0], माप(st->d16[0]));
पूर्ण

अटल पूर्णांक ad7606_spi_ग_लिखो_mask(काष्ठा ad7606_state *st,
				 अचिन्हित पूर्णांक addr,
				 अचिन्हित दीर्घ mask,
				 अचिन्हित पूर्णांक val)
अणु
	पूर्णांक पढ़ोval;

	पढ़ोval = st->bops->reg_पढ़ो(st, addr);
	अगर (पढ़ोval < 0)
		वापस पढ़ोval;

	पढ़ोval &= ~mask;
	पढ़ोval |= val;

	वापस st->bops->reg_ग_लिखो(st, addr, पढ़ोval);
पूर्ण

अटल पूर्णांक ad7616_ग_लिखो_scale_sw(काष्ठा iio_dev *indio_dev, पूर्णांक ch, पूर्णांक val)
अणु
	काष्ठा ad7606_state *st = iio_priv(indio_dev);
	अचिन्हित पूर्णांक ch_addr, mode, ch_index;


	/*
	 * Ad7616 has 16 channels भागided in group A and group B.
	 * The range of channels from A are stored in रेजिस्टरs with address 4
	 * जबतक channels from B are stored in रेजिस्टर with address 6.
	 * The last bit from channels determines अगर it is from group A or B
	 * because the order of channels in iio is 0A, 0B, 1A, 1B...
	 */
	ch_index = ch >> 1;

	ch_addr = AD7616_RANGE_CH_ADDR(ch_index);

	अगर ((ch & 0x1) == 0) /* channel A */
		ch_addr += AD7616_RANGE_CH_A_ADDR_OFF;
	अन्यथा	/* channel B */
		ch_addr += AD7616_RANGE_CH_B_ADDR_OFF;

	/* 0b01 क्रम 2.5v, 0b10 क्रम 5v and 0b11 क्रम 10v */
	mode = AD7616_RANGE_CH_MODE(ch_index, ((val + 1) & 0b11));
	वापस st->bops->ग_लिखो_mask(st, ch_addr, AD7616_RANGE_CH_MSK(ch_index),
				     mode);
पूर्ण

अटल पूर्णांक ad7616_ग_लिखो_os_sw(काष्ठा iio_dev *indio_dev, पूर्णांक val)
अणु
	काष्ठा ad7606_state *st = iio_priv(indio_dev);

	वापस st->bops->ग_लिखो_mask(st, AD7616_CONFIGURATION_REGISTER,
				     AD7616_OS_MASK, val << 2);
पूर्ण

अटल पूर्णांक ad7606_ग_लिखो_scale_sw(काष्ठा iio_dev *indio_dev, पूर्णांक ch, पूर्णांक val)
अणु
	काष्ठा ad7606_state *st = iio_priv(indio_dev);

	वापस ad7606_spi_ग_लिखो_mask(st,
				     AD7606_RANGE_CH_ADDR(ch),
				     AD7606_RANGE_CH_MSK(ch),
				     AD7606_RANGE_CH_MODE(ch, val));
पूर्ण

अटल पूर्णांक ad7606_ग_लिखो_os_sw(काष्ठा iio_dev *indio_dev, पूर्णांक val)
अणु
	काष्ठा ad7606_state *st = iio_priv(indio_dev);

	वापस ad7606_spi_reg_ग_लिखो(st, AD7606_OS_MODE, val);
पूर्ण

अटल पूर्णांक ad7616_sw_mode_config(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा ad7606_state *st = iio_priv(indio_dev);

	/*
	 * Scale can be configured inभागidually क्रम each channel
	 * in software mode.
	 */
	indio_dev->channels = ad7616_sw_channels;

	st->ग_लिखो_scale = ad7616_ग_लिखो_scale_sw;
	st->ग_लिखो_os = &ad7616_ग_लिखो_os_sw;

	/* Activate Burst mode and SEQEN MODE */
	वापस st->bops->ग_लिखो_mask(st,
			      AD7616_CONFIGURATION_REGISTER,
			      AD7616_BURST_MODE | AD7616_SEQEN_MODE,
			      AD7616_BURST_MODE | AD7616_SEQEN_MODE);
पूर्ण

अटल पूर्णांक ad7606B_sw_mode_config(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा ad7606_state *st = iio_priv(indio_dev);
	अचिन्हित दीर्घ os[3] = अणु1पूर्ण;

	/*
	 * Software mode is enabled when all three oversampling
	 * pins are set to high. If oversampling gpios are defined
	 * in the device tree, then they need to be set to high,
	 * otherwise, they must be hardwired to VDD
	 */
	अगर (st->gpio_os) अणु
		gpiod_set_array_value(ARRAY_SIZE(os),
				      st->gpio_os->desc, st->gpio_os->info, os);
	पूर्ण
	/* OS of 128 and 256 are available only in software mode */
	st->oversampling_avail = ad7606B_oversampling_avail;
	st->num_os_ratios = ARRAY_SIZE(ad7606B_oversampling_avail);

	st->ग_लिखो_scale = ad7606_ग_लिखो_scale_sw;
	st->ग_लिखो_os = &ad7606_ग_लिखो_os_sw;

	/* Configure device spi to output on a single channel */
	st->bops->reg_ग_लिखो(st,
			    AD7606_CONFIGURATION_REGISTER,
			    AD7606_SINGLE_DOUT);

	/*
	 * Scale can be configured inभागidually क्रम each channel
	 * in software mode.
	 */
	indio_dev->channels = ad7606b_sw_channels;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा ad7606_bus_ops ad7606_spi_bops = अणु
	.पढ़ो_block = ad7606_spi_पढ़ो_block,
पूर्ण;

अटल स्थिर काष्ठा ad7606_bus_ops ad7616_spi_bops = अणु
	.पढ़ो_block = ad7606_spi_पढ़ो_block,
	.reg_पढ़ो = ad7606_spi_reg_पढ़ो,
	.reg_ग_लिखो = ad7606_spi_reg_ग_लिखो,
	.ग_लिखो_mask = ad7606_spi_ग_लिखो_mask,
	.rd_wr_cmd = ad7616_spi_rd_wr_cmd,
	.sw_mode_config = ad7616_sw_mode_config,
पूर्ण;

अटल स्थिर काष्ठा ad7606_bus_ops ad7606B_spi_bops = अणु
	.पढ़ो_block = ad7606_spi_पढ़ो_block,
	.reg_पढ़ो = ad7606_spi_reg_पढ़ो,
	.reg_ग_लिखो = ad7606_spi_reg_ग_लिखो,
	.ग_लिखो_mask = ad7606_spi_ग_लिखो_mask,
	.rd_wr_cmd = ad7606B_spi_rd_wr_cmd,
	.sw_mode_config = ad7606B_sw_mode_config,
पूर्ण;

अटल पूर्णांक ad7606_spi_probe(काष्ठा spi_device *spi)
अणु
	स्थिर काष्ठा spi_device_id *id = spi_get_device_id(spi);
	स्थिर काष्ठा ad7606_bus_ops *bops;

	चयन (id->driver_data) अणु
	हाल ID_AD7616:
		bops = &ad7616_spi_bops;
		अवरोध;
	हाल ID_AD7606B:
		bops = &ad7606B_spi_bops;
		अवरोध;
	शेष:
		bops = &ad7606_spi_bops;
		अवरोध;
	पूर्ण

	वापस ad7606_probe(&spi->dev, spi->irq, शून्य,
			    id->name, id->driver_data,
			    bops);
पूर्ण

अटल स्थिर काष्ठा spi_device_id ad7606_id_table[] = अणु
	अणु "ad7605-4", ID_AD7605_4 पूर्ण,
	अणु "ad7606-4", ID_AD7606_4 पूर्ण,
	अणु "ad7606-6", ID_AD7606_6 पूर्ण,
	अणु "ad7606-8", ID_AD7606_8 पूर्ण,
	अणु "ad7606b",  ID_AD7606B पूर्ण,
	अणु "ad7616",   ID_AD7616 पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(spi, ad7606_id_table);

अटल स्थिर काष्ठा of_device_id ad7606_of_match[] = अणु
	अणु .compatible = "adi,ad7605-4" पूर्ण,
	अणु .compatible = "adi,ad7606-4" पूर्ण,
	अणु .compatible = "adi,ad7606-6" पूर्ण,
	अणु .compatible = "adi,ad7606-8" पूर्ण,
	अणु .compatible = "adi,ad7606b" पूर्ण,
	अणु .compatible = "adi,ad7616" पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, ad7606_of_match);

अटल काष्ठा spi_driver ad7606_driver = अणु
	.driver = अणु
		.name = "ad7606",
		.of_match_table = ad7606_of_match,
		.pm = AD7606_PM_OPS,
	पूर्ण,
	.probe = ad7606_spi_probe,
	.id_table = ad7606_id_table,
पूर्ण;
module_spi_driver(ad7606_driver);

MODULE_AUTHOR("Michael Hennerich <michael.hennerich@analog.com>");
MODULE_DESCRIPTION("Analog Devices AD7606 ADC");
MODULE_LICENSE("GPL v2");
