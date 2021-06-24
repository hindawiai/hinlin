<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Driver क्रम the Analog Devices digital potentiometers (SPI bus)
 *
 * Copyright (C) 2010-2011 Michael Hennerich, Analog Devices Inc.
 */

#समावेश <linux/spi/spi.h>
#समावेश <linux/module.h>

#समावेश "ad525x_dpot.h"

/* SPI bus functions */
अटल पूर्णांक ग_लिखो8(व्योम *client, u8 val)
अणु
	u8 data = val;

	वापस spi_ग_लिखो(client, &data, 1);
पूर्ण

अटल पूर्णांक ग_लिखो16(व्योम *client, u8 reg, u8 val)
अणु
	u8 data[2] = अणुreg, valपूर्ण;

	वापस spi_ग_लिखो(client, data, 2);
पूर्ण

अटल पूर्णांक ग_लिखो24(व्योम *client, u8 reg, u16 val)
अणु
	u8 data[3] = अणुreg, val >> 8, valपूर्ण;

	वापस spi_ग_लिखो(client, data, 3);
पूर्ण

अटल पूर्णांक पढ़ो8(व्योम *client)
अणु
	पूर्णांक ret;
	u8 data;

	ret = spi_पढ़ो(client, &data, 1);
	अगर (ret < 0)
		वापस ret;

	वापस data;
पूर्ण

अटल पूर्णांक पढ़ो16(व्योम *client, u8 reg)
अणु
	पूर्णांक ret;
	u8 buf_rx[2];

	ग_लिखो16(client, reg, 0);
	ret = spi_पढ़ो(client, buf_rx, 2);
	अगर (ret < 0)
		वापस ret;

	वापस (buf_rx[0] << 8) |  buf_rx[1];
पूर्ण

अटल पूर्णांक पढ़ो24(व्योम *client, u8 reg)
अणु
	पूर्णांक ret;
	u8 buf_rx[3];

	ग_लिखो24(client, reg, 0);
	ret = spi_पढ़ो(client, buf_rx, 3);
	अगर (ret < 0)
		वापस ret;

	वापस (buf_rx[1] << 8) |  buf_rx[2];
पूर्ण

अटल स्थिर काष्ठा ad_dpot_bus_ops bops = अणु
	.पढ़ो_d8	= पढ़ो8,
	.पढ़ो_r8d8	= पढ़ो16,
	.पढ़ो_r8d16	= पढ़ो24,
	.ग_लिखो_d8	= ग_लिखो8,
	.ग_लिखो_r8d8	= ग_लिखो16,
	.ग_लिखो_r8d16	= ग_लिखो24,
पूर्ण;
अटल पूर्णांक ad_dpot_spi_probe(काष्ठा spi_device *spi)
अणु
	काष्ठा ad_dpot_bus_data bdata = अणु
		.client = spi,
		.bops = &bops,
	पूर्ण;

	वापस ad_dpot_probe(&spi->dev, &bdata,
			     spi_get_device_id(spi)->driver_data,
			     spi_get_device_id(spi)->name);
पूर्ण

अटल पूर्णांक ad_dpot_spi_हटाओ(काष्ठा spi_device *spi)
अणु
	वापस ad_dpot_हटाओ(&spi->dev);
पूर्ण

अटल स्थिर काष्ठा spi_device_id ad_dpot_spi_id[] = अणु
	अणु"ad5160", AD5160_IDपूर्ण,
	अणु"ad5161", AD5161_IDपूर्ण,
	अणु"ad5162", AD5162_IDपूर्ण,
	अणु"ad5165", AD5165_IDपूर्ण,
	अणु"ad5200", AD5200_IDपूर्ण,
	अणु"ad5201", AD5201_IDपूर्ण,
	अणु"ad5203", AD5203_IDपूर्ण,
	अणु"ad5204", AD5204_IDपूर्ण,
	अणु"ad5206", AD5206_IDपूर्ण,
	अणु"ad5207", AD5207_IDपूर्ण,
	अणु"ad5231", AD5231_IDपूर्ण,
	अणु"ad5232", AD5232_IDपूर्ण,
	अणु"ad5233", AD5233_IDपूर्ण,
	अणु"ad5235", AD5235_IDपूर्ण,
	अणु"ad5260", AD5260_IDपूर्ण,
	अणु"ad5262", AD5262_IDपूर्ण,
	अणु"ad5263", AD5263_IDपूर्ण,
	अणु"ad5290", AD5290_IDपूर्ण,
	अणु"ad5291", AD5291_IDपूर्ण,
	अणु"ad5292", AD5292_IDपूर्ण,
	अणु"ad5293", AD5293_IDपूर्ण,
	अणु"ad7376", AD7376_IDपूर्ण,
	अणु"ad8400", AD8400_IDपूर्ण,
	अणु"ad8402", AD8402_IDपूर्ण,
	अणु"ad8403", AD8403_IDपूर्ण,
	अणु"adn2850", ADN2850_IDपूर्ण,
	अणु"ad5270", AD5270_IDपूर्ण,
	अणु"ad5271", AD5271_IDपूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(spi, ad_dpot_spi_id);

अटल काष्ठा spi_driver ad_dpot_spi_driver = अणु
	.driver = अणु
		.name	= "ad_dpot",
	पूर्ण,
	.probe		= ad_dpot_spi_probe,
	.हटाओ		= ad_dpot_spi_हटाओ,
	.id_table	= ad_dpot_spi_id,
पूर्ण;

module_spi_driver(ad_dpot_spi_driver);

MODULE_AUTHOR("Michael Hennerich <michael.hennerich@analog.com>");
MODULE_DESCRIPTION("digital potentiometer SPI bus driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("spi:ad_dpot");
