<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * AD714X CapTouch Programmable Controller driver (SPI bus)
 *
 * Copyright 2009-2011 Analog Devices Inc.
 */

#समावेश <linux/input.h>	/* BUS_SPI */
#समावेश <linux/module.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/pm.h>
#समावेश <linux/types.h>
#समावेश "ad714x.h"

#घोषणा AD714x_SPI_CMD_PREFIX      0xE000   /* bits 15:11 */
#घोषणा AD714x_SPI_READ            BIT(10)

अटल पूर्णांक __maybe_unused ad714x_spi_suspend(काष्ठा device *dev)
अणु
	वापस ad714x_disable(spi_get_drvdata(to_spi_device(dev)));
पूर्ण

अटल पूर्णांक __maybe_unused ad714x_spi_resume(काष्ठा device *dev)
अणु
	वापस ad714x_enable(spi_get_drvdata(to_spi_device(dev)));
पूर्ण

अटल SIMPLE_DEV_PM_OPS(ad714x_spi_pm, ad714x_spi_suspend, ad714x_spi_resume);

अटल पूर्णांक ad714x_spi_पढ़ो(काष्ठा ad714x_chip *chip,
			   अचिन्हित लघु reg, अचिन्हित लघु *data, माप_प्रकार len)
अणु
	काष्ठा spi_device *spi = to_spi_device(chip->dev);
	काष्ठा spi_message message;
	काष्ठा spi_transfer xfer[2];
	पूर्णांक i;
	पूर्णांक error;

	spi_message_init(&message);
	स_रखो(xfer, 0, माप(xfer));

	chip->xfer_buf[0] = cpu_to_be16(AD714x_SPI_CMD_PREFIX |
					AD714x_SPI_READ | reg);
	xfer[0].tx_buf = &chip->xfer_buf[0];
	xfer[0].len = माप(chip->xfer_buf[0]);
	spi_message_add_tail(&xfer[0], &message);

	xfer[1].rx_buf = &chip->xfer_buf[1];
	xfer[1].len = माप(chip->xfer_buf[1]) * len;
	spi_message_add_tail(&xfer[1], &message);

	error = spi_sync(spi, &message);
	अगर (unlikely(error)) अणु
		dev_err(chip->dev, "SPI read error: %d\n", error);
		वापस error;
	पूर्ण

	क्रम (i = 0; i < len; i++)
		data[i] = be16_to_cpu(chip->xfer_buf[i + 1]);

	वापस 0;
पूर्ण

अटल पूर्णांक ad714x_spi_ग_लिखो(काष्ठा ad714x_chip *chip,
			    अचिन्हित लघु reg, अचिन्हित लघु data)
अणु
	काष्ठा spi_device *spi = to_spi_device(chip->dev);
	पूर्णांक error;

	chip->xfer_buf[0] = cpu_to_be16(AD714x_SPI_CMD_PREFIX | reg);
	chip->xfer_buf[1] = cpu_to_be16(data);

	error = spi_ग_लिखो(spi, (u8 *)chip->xfer_buf,
			  2 * माप(*chip->xfer_buf));
	अगर (unlikely(error)) अणु
		dev_err(chip->dev, "SPI write error: %d\n", error);
		वापस error;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ad714x_spi_probe(काष्ठा spi_device *spi)
अणु
	काष्ठा ad714x_chip *chip;
	पूर्णांक err;

	spi->bits_per_word = 8;
	err = spi_setup(spi);
	अगर (err < 0)
		वापस err;

	chip = ad714x_probe(&spi->dev, BUS_SPI, spi->irq,
			    ad714x_spi_पढ़ो, ad714x_spi_ग_लिखो);
	अगर (IS_ERR(chip))
		वापस PTR_ERR(chip);

	spi_set_drvdata(spi, chip);

	वापस 0;
पूर्ण

अटल काष्ठा spi_driver ad714x_spi_driver = अणु
	.driver = अणु
		.name	= "ad714x_captouch",
		.pm	= &ad714x_spi_pm,
	पूर्ण,
	.probe		= ad714x_spi_probe,
पूर्ण;

module_spi_driver(ad714x_spi_driver);

MODULE_DESCRIPTION("Analog Devices AD714X Capacitance Touch Sensor SPI Bus Driver");
MODULE_AUTHOR("Barry Song <21cnbao@gmail.com>");
MODULE_LICENSE("GPL");
