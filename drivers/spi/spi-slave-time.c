<शैली गुरु>
/*
 * SPI slave handler reporting upसमय at reception of previous SPI message
 *
 * This SPI slave handler sends the समय of reception of the last SPI message
 * as two 32-bit अचिन्हित पूर्णांकegers in binary क्रमmat and in network byte order,
 * representing the number of seconds and fractional seconds (in microseconds)
 * since boot up.
 *
 * Copyright (C) 2016-2017 Glider bvba
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Usage (assuming /dev/spidev2.0 corresponds to the SPI master on the remote
 * प्रणाली):
 *
 *   # spidev_test -D /dev/spidev2.0 -p dummy-8B
 *   spi mode: 0x0
 *   bits per word: 8
 *   max speed: 500000 Hz (500 KHz)
 *   RX | 00 00 04 6D 00 09 5B BB ...
 *		^^^^^    ^^^^^^^^
 *		seconds  microseconds
 */

#समावेश <linux/completion.h>
#समावेश <linux/module.h>
#समावेश <linux/sched/घड़ी.h>
#समावेश <linux/spi/spi.h>


काष्ठा spi_slave_समय_priv अणु
	काष्ठा spi_device *spi;
	काष्ठा completion finished;
	काष्ठा spi_transfer xfer;
	काष्ठा spi_message msg;
	__be32 buf[2];
पूर्ण;

अटल पूर्णांक spi_slave_समय_submit(काष्ठा spi_slave_समय_priv *priv);

अटल व्योम spi_slave_समय_complete(व्योम *arg)
अणु
	काष्ठा spi_slave_समय_priv *priv = arg;
	पूर्णांक ret;

	ret = priv->msg.status;
	अगर (ret)
		जाओ terminate;

	ret = spi_slave_समय_submit(priv);
	अगर (ret)
		जाओ terminate;

	वापस;

terminate:
	dev_info(&priv->spi->dev, "Terminating\n");
	complete(&priv->finished);
पूर्ण

अटल पूर्णांक spi_slave_समय_submit(काष्ठा spi_slave_समय_priv *priv)
अणु
	u32 rem_us;
	पूर्णांक ret;
	u64 ts;

	ts = local_घड़ी();
	rem_us = करो_भाग(ts, 1000000000) / 1000;

	priv->buf[0] = cpu_to_be32(ts);
	priv->buf[1] = cpu_to_be32(rem_us);

	spi_message_init_with_transfers(&priv->msg, &priv->xfer, 1);

	priv->msg.complete = spi_slave_समय_complete;
	priv->msg.context = priv;

	ret = spi_async(priv->spi, &priv->msg);
	अगर (ret)
		dev_err(&priv->spi->dev, "spi_async() failed %d\n", ret);

	वापस ret;
पूर्ण

अटल पूर्णांक spi_slave_समय_probe(काष्ठा spi_device *spi)
अणु
	काष्ठा spi_slave_समय_priv *priv;
	पूर्णांक ret;

	priv = devm_kzalloc(&spi->dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	priv->spi = spi;
	init_completion(&priv->finished);
	priv->xfer.tx_buf = priv->buf;
	priv->xfer.len = माप(priv->buf);

	ret = spi_slave_समय_submit(priv);
	अगर (ret)
		वापस ret;

	spi_set_drvdata(spi, priv);
	वापस 0;
पूर्ण

अटल पूर्णांक spi_slave_समय_हटाओ(काष्ठा spi_device *spi)
अणु
	काष्ठा spi_slave_समय_priv *priv = spi_get_drvdata(spi);

	spi_slave_पात(spi);
	रुको_क्रम_completion(&priv->finished);
	वापस 0;
पूर्ण

अटल काष्ठा spi_driver spi_slave_समय_driver = अणु
	.driver = अणु
		.name	= "spi-slave-time",
	पूर्ण,
	.probe		= spi_slave_समय_probe,
	.हटाओ		= spi_slave_समय_हटाओ,
पूर्ण;
module_spi_driver(spi_slave_समय_driver);

MODULE_AUTHOR("Geert Uytterhoeven <geert+renesas@glider.be>");
MODULE_DESCRIPTION("SPI slave reporting uptime at previous SPI message");
MODULE_LICENSE("GPL v2");
