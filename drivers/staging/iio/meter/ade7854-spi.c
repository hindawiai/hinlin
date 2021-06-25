<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * ADE7854/58/68/78 Polyphase Multअगरunction Energy Metering IC Driver (SPI Bus)
 *
 * Copyright 2010 Analog Devices Inc.
 */

#समावेश <linux/device.h>
#समावेश <linux/kernel.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>

#समावेश <linux/iio/iपन.स>
#समावेश "ade7854.h"

अटल पूर्णांक ade7854_spi_ग_लिखो_reg(काष्ठा device *dev,
				 u16 reg_address,
				 u32 val,
				 पूर्णांक bits)
अणु
	पूर्णांक ret;
	काष्ठा iio_dev *indio_dev = dev_to_iio_dev(dev);
	काष्ठा ade7854_state *st = iio_priv(indio_dev);
	काष्ठा spi_transfer xfer = अणु
		.tx_buf = st->tx,
		.bits_per_word = 8,
		.len = 4,
	पूर्ण;

	mutex_lock(&st->buf_lock);
	st->tx[0] = ADE7854_WRITE_REG;
	st->tx[1] = (reg_address >> 8) & 0xFF;
	st->tx[2] = reg_address & 0xFF;
	चयन (bits) अणु
	हाल 8:
		st->tx[3] = val & 0xFF;
		अवरोध;
	हाल 16:
		xfer.len = 5;
		st->tx[3] = (val >> 8) & 0xFF;
		st->tx[4] = val & 0xFF;
		अवरोध;
	हाल 24:
		xfer.len = 6;
		st->tx[3] = (val >> 16) & 0xFF;
		st->tx[4] = (val >> 8) & 0xFF;
		st->tx[5] = val & 0xFF;
		अवरोध;
	हाल 32:
		xfer.len = 7;
		st->tx[3] = (val >> 24) & 0xFF;
		st->tx[4] = (val >> 16) & 0xFF;
		st->tx[5] = (val >> 8) & 0xFF;
		st->tx[6] = val & 0xFF;
		अवरोध;
	शेष:
		ret = -EINVAL;
		जाओ unlock;
	पूर्ण

	ret = spi_sync_transfer(st->spi, &xfer, 1);
unlock:
	mutex_unlock(&st->buf_lock);

	वापस ret;
पूर्ण

अटल पूर्णांक ade7854_spi_पढ़ो_reg(काष्ठा device *dev,
				u16 reg_address,
				u32 *val,
				पूर्णांक bits)
अणु
	काष्ठा iio_dev *indio_dev = dev_to_iio_dev(dev);
	काष्ठा ade7854_state *st = iio_priv(indio_dev);
	पूर्णांक ret;
	काष्ठा spi_transfer xfers[] = अणु
		अणु
			.tx_buf = st->tx,
			.bits_per_word = 8,
			.len = 3,
		पूर्ण, अणु
			.rx_buf = st->rx,
			.bits_per_word = 8,
			.len = bits,
		पूर्ण
	पूर्ण;

	mutex_lock(&st->buf_lock);

	st->tx[0] = ADE7854_READ_REG;
	st->tx[1] = (reg_address >> 8) & 0xFF;
	st->tx[2] = reg_address & 0xFF;

	ret = spi_sync_transfer(st->spi, xfers, ARRAY_SIZE(xfers));
	अगर (ret < 0) अणु
		dev_err(&st->spi->dev, "problem when reading register 0x%02X",
			reg_address);
		जाओ unlock;
	पूर्ण

	चयन (bits) अणु
	हाल 8:
		*val = st->rx[0];
		अवरोध;
	हाल 16:
		*val = be16_to_cpup((स्थिर __be16 *)st->rx);
		अवरोध;
	हाल 24:
		*val = (st->rx[0] << 16) | (st->rx[1] << 8) | st->rx[2];
		अवरोध;
	हाल 32:
		*val = be32_to_cpup((स्थिर __be32 *)st->rx);
		अवरोध;
	पूर्ण

unlock:
	mutex_unlock(&st->buf_lock);
	वापस ret;
पूर्ण

अटल पूर्णांक ade7854_spi_probe(काष्ठा spi_device *spi)
अणु
	काष्ठा ade7854_state *st;
	काष्ठा iio_dev *indio_dev;

	indio_dev = devm_iio_device_alloc(&spi->dev, माप(*st));
	अगर (!indio_dev)
		वापस -ENOMEM;
	st = iio_priv(indio_dev);
	spi_set_drvdata(spi, indio_dev);
	st->पढ़ो_reg = ade7854_spi_पढ़ो_reg;
	st->ग_लिखो_reg = ade7854_spi_ग_लिखो_reg;
	st->irq = spi->irq;
	st->spi = spi;

	वापस ade7854_probe(indio_dev, &spi->dev);
पूर्ण

अटल स्थिर काष्ठा spi_device_id ade7854_id[] = अणु
	अणु "ade7854", 0 पूर्ण,
	अणु "ade7858", 0 पूर्ण,
	अणु "ade7868", 0 पूर्ण,
	अणु "ade7878", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(spi, ade7854_id);

अटल काष्ठा spi_driver ade7854_driver = अणु
	.driver = अणु
		.name = "ade7854",
	पूर्ण,
	.probe = ade7854_spi_probe,
	.id_table = ade7854_id,
पूर्ण;
module_spi_driver(ade7854_driver);

MODULE_AUTHOR("Barry Song <21cnbao@gmail.com>");
MODULE_DESCRIPTION("Analog Devices ADE7854/58/68/78 SPI Driver");
MODULE_LICENSE("GPL v2");
