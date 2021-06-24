<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * TSC2005 touchscreen driver
 *
 * Copyright (C) 2006-2010 Nokia Corporation
 * Copyright (C) 2015 QWERTY Embedded Design
 * Copyright (C) 2015 EMAC Inc.
 *
 * Based on original tsc2005.c by Lauri Leukkunen <lauri.leukkunen@nokia.com>
 */

#समावेश <linux/input.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/regmap.h>
#समावेश "tsc200x-core.h"

अटल स्थिर काष्ठा input_id tsc2005_input_id = अणु
	.bustype = BUS_SPI,
	.product = 2005,
पूर्ण;

अटल पूर्णांक tsc2005_cmd(काष्ठा device *dev, u8 cmd)
अणु
	u8 tx = TSC200X_CMD | TSC200X_CMD_12BIT | cmd;
	काष्ठा spi_transfer xfer = अणु
		.tx_buf         = &tx,
		.len            = 1,
		.bits_per_word  = 8,
	पूर्ण;
	काष्ठा spi_message msg;
	काष्ठा spi_device *spi = to_spi_device(dev);
	पूर्णांक error;

	spi_message_init(&msg);
	spi_message_add_tail(&xfer, &msg);

	error = spi_sync(spi, &msg);
	अगर (error) अणु
		dev_err(dev, "%s: failed, command: %x, spi error: %d\n",
			__func__, cmd, error);
		वापस error;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक tsc2005_probe(काष्ठा spi_device *spi)
अणु
	पूर्णांक error;

	spi->mode = SPI_MODE_0;
	spi->bits_per_word = 8;
	अगर (!spi->max_speed_hz)
		spi->max_speed_hz = TSC2005_SPI_MAX_SPEED_HZ;

	error = spi_setup(spi);
	अगर (error)
		वापस error;

	वापस tsc200x_probe(&spi->dev, spi->irq, &tsc2005_input_id,
			     devm_regmap_init_spi(spi, &tsc200x_regmap_config),
			     tsc2005_cmd);
पूर्ण

अटल पूर्णांक tsc2005_हटाओ(काष्ठा spi_device *spi)
अणु
	वापस tsc200x_हटाओ(&spi->dev);
पूर्ण

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id tsc2005_of_match[] = अणु
	अणु .compatible = "ti,tsc2005" पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, tsc2005_of_match);
#पूर्ण_अगर

अटल काष्ठा spi_driver tsc2005_driver = अणु
	.driver	= अणु
		.name	= "tsc2005",
		.of_match_table = of_match_ptr(tsc2005_of_match),
		.pm	= &tsc200x_pm_ops,
	पूर्ण,
	.probe	= tsc2005_probe,
	.हटाओ	= tsc2005_हटाओ,
पूर्ण;
module_spi_driver(tsc2005_driver);

MODULE_AUTHOR("Michael Welling <mwelling@ieee.org>");
MODULE_DESCRIPTION("TSC2005 Touchscreen Driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("spi:tsc2005");
