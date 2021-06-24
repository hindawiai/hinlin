<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Freescale MPL115A1 pressure/temperature sensor
 *
 * Copyright (c) 2016 Akinobu Mita <akinobu.mita@gmail.com>
 *
 * Datasheet: http://www.nxp.com/files/sensors/करोc/data_sheet/MPL115A1.pdf
 */

#समावेश <linux/module.h>
#समावेश <linux/spi/spi.h>

#समावेश "mpl115.h"

#घोषणा MPL115_SPI_WRITE(address)	((address) << 1)
#घोषणा MPL115_SPI_READ(address)	(0x80 | (address) << 1)

काष्ठा mpl115_spi_buf अणु
	u8 tx[4];
	u8 rx[4];
पूर्ण;

अटल पूर्णांक mpl115_spi_init(काष्ठा device *dev)
अणु
	काष्ठा spi_device *spi = to_spi_device(dev);
	काष्ठा mpl115_spi_buf *buf;

	buf = devm_kzalloc(dev, माप(*buf), GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	spi_set_drvdata(spi, buf);

	वापस 0;
पूर्ण

अटल पूर्णांक mpl115_spi_पढ़ो(काष्ठा device *dev, u8 address)
अणु
	काष्ठा spi_device *spi = to_spi_device(dev);
	काष्ठा mpl115_spi_buf *buf = spi_get_drvdata(spi);
	काष्ठा spi_transfer xfer = अणु
		.tx_buf = buf->tx,
		.rx_buf = buf->rx,
		.len = 4,
	पूर्ण;
	पूर्णांक ret;

	buf->tx[0] = MPL115_SPI_READ(address);
	buf->tx[2] = MPL115_SPI_READ(address + 1);

	ret = spi_sync_transfer(spi, &xfer, 1);
	अगर (ret)
		वापस ret;

	वापस (buf->rx[1] << 8) | buf->rx[3];
पूर्ण

अटल पूर्णांक mpl115_spi_ग_लिखो(काष्ठा device *dev, u8 address, u8 value)
अणु
	काष्ठा spi_device *spi = to_spi_device(dev);
	काष्ठा mpl115_spi_buf *buf = spi_get_drvdata(spi);
	काष्ठा spi_transfer xfer = अणु
		.tx_buf = buf->tx,
		.len = 2,
	पूर्ण;

	buf->tx[0] = MPL115_SPI_WRITE(address);
	buf->tx[1] = value;

	वापस spi_sync_transfer(spi, &xfer, 1);
पूर्ण

अटल स्थिर काष्ठा mpl115_ops mpl115_spi_ops = अणु
	.init = mpl115_spi_init,
	.पढ़ो = mpl115_spi_पढ़ो,
	.ग_लिखो = mpl115_spi_ग_लिखो,
पूर्ण;

अटल पूर्णांक mpl115_spi_probe(काष्ठा spi_device *spi)
अणु
	स्थिर काष्ठा spi_device_id *id = spi_get_device_id(spi);

	वापस mpl115_probe(&spi->dev, id->name, &mpl115_spi_ops);
पूर्ण

अटल स्थिर काष्ठा spi_device_id mpl115_spi_ids[] = अणु
	अणु "mpl115", 0 पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(spi, mpl115_spi_ids);

अटल काष्ठा spi_driver mpl115_spi_driver = अणु
	.driver = अणु
		.name   = "mpl115",
	पूर्ण,
	.probe = mpl115_spi_probe,
	.id_table = mpl115_spi_ids,
पूर्ण;
module_spi_driver(mpl115_spi_driver);

MODULE_AUTHOR("Akinobu Mita <akinobu.mita@gmail.com>");
MODULE_DESCRIPTION("Freescale MPL115A1 pressure/temperature driver");
MODULE_LICENSE("GPL");
