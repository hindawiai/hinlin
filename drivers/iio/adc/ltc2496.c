<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * ltc2496.c - Driver क्रम Analog Devices/Linear Technology LTC2496 ADC
 *
 * Based on ltc2497.c which has
 * Copyright (C) 2017 Analog Devices Inc.
 *
 * Licensed under the GPL-2.
 *
 * Datasheet: https://www.analog.com/media/en/technical-करोcumentation/data-sheets/2496fc.pdf
 */

#समावेश <linux/spi/spi.h>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/driver.h>
#समावेश <linux/module.h>
#समावेश <linux/mod_devicetable.h>

#समावेश "ltc2497.h"

काष्ठा ltc2496_driverdata अणु
	/* this must be the first member */
	काष्ठा ltc2497core_driverdata common_ddata;
	काष्ठा spi_device *spi;

	/*
	 * DMA (thus cache coherency मुख्यtenance) requires the
	 * transfer buffers to live in their own cache lines.
	 */
	अचिन्हित अक्षर rxbuf[3] ____cacheline_aligned;
	अचिन्हित अक्षर txbuf[3];
पूर्ण;

अटल पूर्णांक ltc2496_result_and_measure(काष्ठा ltc2497core_driverdata *ddata,
				      u8 address, पूर्णांक *val)
अणु
	काष्ठा ltc2496_driverdata *st =
		container_of(ddata, काष्ठा ltc2496_driverdata, common_ddata);
	काष्ठा spi_transfer t = अणु
		.tx_buf = st->txbuf,
		.rx_buf = st->rxbuf,
		.len = माप(st->txbuf),
	पूर्ण;
	पूर्णांक ret;

	st->txbuf[0] = LTC2497_ENABLE | address;

	ret = spi_sync_transfer(st->spi, &t, 1);
	अगर (ret < 0)  अणु
		dev_err(&st->spi->dev, "spi_sync_transfer failed: %pe\n",
			ERR_PTR(ret));
		वापस ret;
	पूर्ण

	अगर (val)
		*val = ((st->rxbuf[0] & 0x3f) << 12 |
			st->rxbuf[1] << 4 | st->rxbuf[2] >> 4) -
			(1 << 17);

	वापस 0;
पूर्ण

अटल पूर्णांक ltc2496_probe(काष्ठा spi_device *spi)
अणु
	काष्ठा iio_dev *indio_dev;
	काष्ठा ltc2496_driverdata *st;
	काष्ठा device *dev = &spi->dev;

	indio_dev = devm_iio_device_alloc(dev, माप(*st));
	अगर (!indio_dev)
		वापस -ENOMEM;

	st = iio_priv(indio_dev);
	spi_set_drvdata(spi, indio_dev);
	st->spi = spi;
	st->common_ddata.result_and_measure = ltc2496_result_and_measure;

	वापस ltc2497core_probe(dev, indio_dev);
पूर्ण

अटल पूर्णांक ltc2496_हटाओ(काष्ठा spi_device *spi)
अणु
	काष्ठा iio_dev *indio_dev = spi_get_drvdata(spi);

	ltc2497core_हटाओ(indio_dev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id ltc2496_of_match[] = अणु
	अणु .compatible = "lltc,ltc2496", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, ltc2496_of_match);

अटल काष्ठा spi_driver ltc2496_driver = अणु
	.driver = अणु
		.name = "ltc2496",
		.of_match_table = ltc2496_of_match,
	पूर्ण,
	.probe = ltc2496_probe,
	.हटाओ = ltc2496_हटाओ,
पूर्ण;
module_spi_driver(ltc2496_driver);

MODULE_AUTHOR("Uwe Kleine-Kथघnig <u.kleine-kथघnig@pengutronix.de>");
MODULE_DESCRIPTION("Linear Technology LTC2496 ADC driver");
MODULE_LICENSE("GPL v2");
