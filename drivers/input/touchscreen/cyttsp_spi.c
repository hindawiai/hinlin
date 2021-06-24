<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Source क्रम:
 * Cypress TrueTouch(TM) Standard Product (TTSP) SPI touchscreen driver.
 * For use with Cypress Txx3xx parts.
 * Supported parts include:
 * CY8CTST341
 * CY8CTMA340
 *
 * Copyright (C) 2009, 2010, 2011 Cypress Semiconductor, Inc.
 * Copyright (C) 2012 Javier Martinez Canillas <javier@करोजबतक0.org>
 * Copyright (C) 2013 Cypress Semiconductor
 *
 * Contact Cypress Semiconductor at www.cypress.com <ttdrivers@cypress.com>
 */

#समावेश "cyttsp_core.h"

#समावेश <linux/delay.h>
#समावेश <linux/input.h>
#समावेश <linux/spi/spi.h>

#घोषणा CY_SPI_WR_OP		0x00 /* r/~w */
#घोषणा CY_SPI_RD_OP		0x01
#घोषणा CY_SPI_CMD_BYTES	4
#घोषणा CY_SPI_SYNC_BYTE	2
#घोषणा CY_SPI_SYNC_ACK1	0x62 /* from protocol v.2 */
#घोषणा CY_SPI_SYNC_ACK2	0x9D /* from protocol v.2 */
#घोषणा CY_SPI_DATA_SIZE	128
#घोषणा CY_SPI_DATA_BUF_SIZE	(CY_SPI_CMD_BYTES + CY_SPI_DATA_SIZE)
#घोषणा CY_SPI_BITS_PER_WORD	8

अटल पूर्णांक cyttsp_spi_xfer(काष्ठा device *dev, u8 *xfer_buf,
			   u8 op, u16 reg, u8 *buf, पूर्णांक length)
अणु
	काष्ठा spi_device *spi = to_spi_device(dev);
	काष्ठा spi_message msg;
	काष्ठा spi_transfer xfer[2];
	u8 *wr_buf = &xfer_buf[0];
	u8 *rd_buf = &xfer_buf[CY_SPI_DATA_BUF_SIZE];
	पूर्णांक retval;
	पूर्णांक i;

	अगर (length > CY_SPI_DATA_SIZE) अणु
		dev_err(dev, "%s: length %d is too big.\n",
			__func__, length);
		वापस -EINVAL;
	पूर्ण

	स_रखो(wr_buf, 0, CY_SPI_DATA_BUF_SIZE);
	स_रखो(rd_buf, 0, CY_SPI_DATA_BUF_SIZE);

	wr_buf[0] = 0x00; /* header byte 0 */
	wr_buf[1] = 0xFF; /* header byte 1 */
	wr_buf[2] = reg;  /* reg index */
	wr_buf[3] = op;   /* r/~w */
	अगर (op == CY_SPI_WR_OP)
		स_नकल(wr_buf + CY_SPI_CMD_BYTES, buf, length);

	स_रखो(xfer, 0, माप(xfer));
	spi_message_init(&msg);

	/*
	  We set both TX and RX buffers because Cypress TTSP
	  requires full duplex operation.
	*/
	xfer[0].tx_buf = wr_buf;
	xfer[0].rx_buf = rd_buf;
	चयन (op) अणु
	हाल CY_SPI_WR_OP:
		xfer[0].len = length + CY_SPI_CMD_BYTES;
		spi_message_add_tail(&xfer[0], &msg);
		अवरोध;

	हाल CY_SPI_RD_OP:
		xfer[0].len = CY_SPI_CMD_BYTES;
		spi_message_add_tail(&xfer[0], &msg);

		xfer[1].rx_buf = buf;
		xfer[1].len = length;
		spi_message_add_tail(&xfer[1], &msg);
		अवरोध;

	शेष:
		dev_err(dev, "%s: bad operation code=%d\n", __func__, op);
		वापस -EINVAL;
	पूर्ण

	retval = spi_sync(spi, &msg);
	अगर (retval < 0) अणु
		dev_dbg(dev, "%s: spi_sync() error %d, len=%d, op=%d\n",
			__func__, retval, xfer[1].len, op);

		/*
		 * करो not वापस here since was a bad ACK sequence
		 * let the following ACK check handle any errors and
		 * allow silent retries
		 */
	पूर्ण

	अगर (rd_buf[CY_SPI_SYNC_BYTE] != CY_SPI_SYNC_ACK1 ||
	    rd_buf[CY_SPI_SYNC_BYTE + 1] != CY_SPI_SYNC_ACK2) अणु
		dev_dbg(dev, "%s: operation %d failed\n", __func__, op);

		क्रम (i = 0; i < CY_SPI_CMD_BYTES; i++)
			dev_dbg(dev, "%s: test rd_buf[%d]:0x%02x\n",
				__func__, i, rd_buf[i]);
		क्रम (i = 0; i < length; i++)
			dev_dbg(dev, "%s: test buf[%d]:0x%02x\n",
				__func__, i, buf[i]);

		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cyttsp_spi_पढ़ो_block_data(काष्ठा device *dev, u8 *xfer_buf,
				      u16 addr, u8 length, व्योम *data)
अणु
	वापस cyttsp_spi_xfer(dev, xfer_buf, CY_SPI_RD_OP, addr, data,
			length);
पूर्ण

अटल पूर्णांक cyttsp_spi_ग_लिखो_block_data(काष्ठा device *dev, u8 *xfer_buf,
				       u16 addr, u8 length, स्थिर व्योम *data)
अणु
	वापस cyttsp_spi_xfer(dev, xfer_buf, CY_SPI_WR_OP, addr, (व्योम *)data,
			length);
पूर्ण

अटल स्थिर काष्ठा cyttsp_bus_ops cyttsp_spi_bus_ops = अणु
	.bustype	= BUS_SPI,
	.ग_लिखो		= cyttsp_spi_ग_लिखो_block_data,
	.पढ़ो		= cyttsp_spi_पढ़ो_block_data,
पूर्ण;

अटल पूर्णांक cyttsp_spi_probe(काष्ठा spi_device *spi)
अणु
	काष्ठा cyttsp *ts;
	पूर्णांक error;

	/* Set up SPI*/
	spi->bits_per_word = CY_SPI_BITS_PER_WORD;
	spi->mode = SPI_MODE_0;
	error = spi_setup(spi);
	अगर (error < 0) अणु
		dev_err(&spi->dev, "%s: SPI setup error %d\n",
			__func__, error);
		वापस error;
	पूर्ण

	ts = cyttsp_probe(&cyttsp_spi_bus_ops, &spi->dev, spi->irq,
			  CY_SPI_DATA_BUF_SIZE * 2);
	अगर (IS_ERR(ts))
		वापस PTR_ERR(ts);

	spi_set_drvdata(spi, ts);

	वापस 0;
पूर्ण

अटल काष्ठा spi_driver cyttsp_spi_driver = अणु
	.driver = अणु
		.name	= CY_SPI_NAME,
		.pm	= &cyttsp_pm_ops,
	पूर्ण,
	.probe  = cyttsp_spi_probe,
पूर्ण;

module_spi_driver(cyttsp_spi_driver);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Cypress TrueTouch(R) Standard Product (TTSP) SPI driver");
MODULE_AUTHOR("Cypress");
MODULE_ALIAS("spi:cyttsp");
