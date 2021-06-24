<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2003-2015 Broadcom Corporation
 * All Rights Reserved
 */
#समावेश <linux/acpi.h>
#समावेश <linux/clk.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/of.h>
#समावेश <linux/पूर्णांकerrupt.h>

/* SPI Configuration Register */
#घोषणा XLP_SPI_CONFIG			0x00
#घोषणा XLP_SPI_CPHA			BIT(0)
#घोषणा XLP_SPI_CPOL			BIT(1)
#घोषणा XLP_SPI_CS_POL			BIT(2)
#घोषणा XLP_SPI_TXMISO_EN		BIT(3)
#घोषणा XLP_SPI_TXMOSI_EN		BIT(4)
#घोषणा XLP_SPI_RXMISO_EN		BIT(5)
#घोषणा XLP_SPI_CS_LSBFE		BIT(10)
#घोषणा XLP_SPI_RXCAP_EN		BIT(11)

/* SPI Frequency Divider Register */
#घोषणा XLP_SPI_FDIV			0x04

/* SPI Command Register */
#घोषणा XLP_SPI_CMD			0x08
#घोषणा XLP_SPI_CMD_IDLE_MASK		0x0
#घोषणा XLP_SPI_CMD_TX_MASK		0x1
#घोषणा XLP_SPI_CMD_RX_MASK		0x2
#घोषणा XLP_SPI_CMD_TXRX_MASK		0x3
#घोषणा XLP_SPI_CMD_CONT		BIT(4)
#घोषणा XLP_SPI_XFR_BITCNT_SHIFT	16

/* SPI Status Register */
#घोषणा XLP_SPI_STATUS			0x0c
#घोषणा XLP_SPI_XFR_PENDING		BIT(0)
#घोषणा XLP_SPI_XFR_DONE		BIT(1)
#घोषणा XLP_SPI_TX_INT			BIT(2)
#घोषणा XLP_SPI_RX_INT			BIT(3)
#घोषणा XLP_SPI_TX_UF			BIT(4)
#घोषणा XLP_SPI_RX_OF			BIT(5)
#घोषणा XLP_SPI_STAT_MASK		0x3f

/* SPI Interrupt Enable Register */
#घोषणा XLP_SPI_INTR_EN			0x10
#घोषणा XLP_SPI_INTR_DONE		BIT(0)
#घोषणा XLP_SPI_INTR_TXTH		BIT(1)
#घोषणा XLP_SPI_INTR_RXTH		BIT(2)
#घोषणा XLP_SPI_INTR_TXUF		BIT(3)
#घोषणा XLP_SPI_INTR_RXOF		BIT(4)

/* SPI FIFO Threshold Register */
#घोषणा XLP_SPI_FIFO_THRESH		0x14

/* SPI FIFO Word Count Register */
#घोषणा XLP_SPI_FIFO_WCNT		0x18
#घोषणा XLP_SPI_RXFIFO_WCNT_MASK	0xf
#घोषणा XLP_SPI_TXFIFO_WCNT_MASK	0xf0
#घोषणा XLP_SPI_TXFIFO_WCNT_SHIFT	4

/* SPI Transmit Data FIFO Register */
#घोषणा XLP_SPI_TXDATA_FIFO		0x1c

/* SPI Receive Data FIFO Register */
#घोषणा XLP_SPI_RXDATA_FIFO		0x20

/* SPI System Control Register */
#घोषणा XLP_SPI_SYSCTRL			0x100
#घोषणा XLP_SPI_SYS_RESET		BIT(0)
#घोषणा XLP_SPI_SYS_CLKDIS		BIT(1)
#घोषणा XLP_SPI_SYS_PMEN		BIT(8)

#घोषणा SPI_CS_OFFSET			0x40
#घोषणा XLP_SPI_TXRXTH			0x80
#घोषणा XLP_SPI_FIFO_SIZE		8
#घोषणा XLP_SPI_MAX_CS			4
#घोषणा XLP_SPI_DEFAULT_FREQ		133333333
#घोषणा XLP_SPI_FDIV_MIN		4
#घोषणा XLP_SPI_FDIV_MAX		65535
/*
 * SPI can transfer only 28 bytes properly at a समय. So split the
 * transfer पूर्णांकo 28 bytes size.
 */
#घोषणा XLP_SPI_XFER_SIZE		28

काष्ठा xlp_spi_priv अणु
	काष्ठा device		dev;		/* device काष्ठाure */
	व्योम __iomem		*base;		/* spi रेजिस्टरs base address */
	स्थिर u8		*tx_buf;	/* tx data buffer */
	u8			*rx_buf;	/* rx data buffer */
	पूर्णांक			tx_len;		/* tx xfer length */
	पूर्णांक			rx_len;		/* rx xfer length */
	पूर्णांक			txerrors;	/* TXFIFO underflow count */
	पूर्णांक			rxerrors;	/* RXFIFO overflow count */
	पूर्णांक			cs;		/* slave device chip select */
	u32			spi_clk;	/* spi घड़ी frequency */
	bool			cmd_cont;	/* cs active */
	काष्ठा completion	करोne;		/* completion notअगरication */
पूर्ण;

अटल अंतरभूत u32 xlp_spi_reg_पढ़ो(काष्ठा xlp_spi_priv *priv,
				पूर्णांक cs, पूर्णांक regoff)
अणु
	वापस पढ़ोl(priv->base + regoff + cs * SPI_CS_OFFSET);
पूर्ण

अटल अंतरभूत व्योम xlp_spi_reg_ग_लिखो(काष्ठा xlp_spi_priv *priv, पूर्णांक cs,
				पूर्णांक regoff, u32 val)
अणु
	ग_लिखोl(val, priv->base + regoff + cs * SPI_CS_OFFSET);
पूर्ण

अटल अंतरभूत व्योम xlp_spi_sysctl_ग_लिखो(काष्ठा xlp_spi_priv *priv,
				पूर्णांक regoff, u32 val)
अणु
	ग_लिखोl(val, priv->base + regoff);
पूर्ण

/*
 * Setup global SPI_SYSCTRL रेजिस्टर क्रम all SPI channels.
 */
अटल व्योम xlp_spi_sysctl_setup(काष्ठा xlp_spi_priv *xspi)
अणु
	पूर्णांक cs;

	क्रम (cs = 0; cs < XLP_SPI_MAX_CS; cs++)
		xlp_spi_sysctl_ग_लिखो(xspi, XLP_SPI_SYSCTRL,
				XLP_SPI_SYS_RESET << cs);
	xlp_spi_sysctl_ग_लिखो(xspi, XLP_SPI_SYSCTRL, XLP_SPI_SYS_PMEN);
पूर्ण

अटल पूर्णांक xlp_spi_setup(काष्ठा spi_device *spi)
अणु
	काष्ठा xlp_spi_priv *xspi;
	u32 fभाग, cfg;
	पूर्णांक cs;

	xspi = spi_master_get_devdata(spi->master);
	cs = spi->chip_select;
	/*
	 * The value of fभाग must be between 4 and 65535.
	 */
	fभाग = DIV_ROUND_UP(xspi->spi_clk, spi->max_speed_hz);
	अगर (fभाग > XLP_SPI_FDIV_MAX)
		fभाग = XLP_SPI_FDIV_MAX;
	अन्यथा अगर (fभाग < XLP_SPI_FDIV_MIN)
		fभाग = XLP_SPI_FDIV_MIN;

	xlp_spi_reg_ग_लिखो(xspi, cs, XLP_SPI_FDIV, fभाग);
	xlp_spi_reg_ग_लिखो(xspi, cs, XLP_SPI_FIFO_THRESH, XLP_SPI_TXRXTH);
	cfg = xlp_spi_reg_पढ़ो(xspi, cs, XLP_SPI_CONFIG);
	अगर (spi->mode & SPI_CPHA)
		cfg |= XLP_SPI_CPHA;
	अन्यथा
		cfg &= ~XLP_SPI_CPHA;
	अगर (spi->mode & SPI_CPOL)
		cfg |= XLP_SPI_CPOL;
	अन्यथा
		cfg &= ~XLP_SPI_CPOL;
	अगर (!(spi->mode & SPI_CS_HIGH))
		cfg |= XLP_SPI_CS_POL;
	अन्यथा
		cfg &= ~XLP_SPI_CS_POL;
	अगर (spi->mode & SPI_LSB_FIRST)
		cfg |= XLP_SPI_CS_LSBFE;
	अन्यथा
		cfg &= ~XLP_SPI_CS_LSBFE;

	cfg |= XLP_SPI_TXMOSI_EN | XLP_SPI_RXMISO_EN;
	अगर (fभाग == 4)
		cfg |= XLP_SPI_RXCAP_EN;
	xlp_spi_reg_ग_लिखो(xspi, cs, XLP_SPI_CONFIG, cfg);

	वापस 0;
पूर्ण

अटल व्योम xlp_spi_पढ़ो_rxfअगरo(काष्ठा xlp_spi_priv *xspi)
अणु
	u32 rx_data, rxfअगरo_cnt;
	पूर्णांक i, j, nbytes;

	rxfअगरo_cnt = xlp_spi_reg_पढ़ो(xspi, xspi->cs, XLP_SPI_FIFO_WCNT);
	rxfअगरo_cnt &= XLP_SPI_RXFIFO_WCNT_MASK;
	जबतक (rxfअगरo_cnt) अणु
		rx_data = xlp_spi_reg_पढ़ो(xspi, xspi->cs, XLP_SPI_RXDATA_FIFO);
		j = 0;
		nbytes = min(xspi->rx_len, 4);
		क्रम (i = nbytes - 1; i >= 0; i--, j++)
			xspi->rx_buf[i] = (rx_data >> (j * 8)) & 0xff;

		xspi->rx_len -= nbytes;
		xspi->rx_buf += nbytes;
		rxfअगरo_cnt--;
	पूर्ण
पूर्ण

अटल व्योम xlp_spi_fill_txfअगरo(काष्ठा xlp_spi_priv *xspi)
अणु
	u32 tx_data, txfअगरo_cnt;
	पूर्णांक i, j, nbytes;

	txfअगरo_cnt = xlp_spi_reg_पढ़ो(xspi, xspi->cs, XLP_SPI_FIFO_WCNT);
	txfअगरo_cnt &= XLP_SPI_TXFIFO_WCNT_MASK;
	txfअगरo_cnt >>= XLP_SPI_TXFIFO_WCNT_SHIFT;
	जबतक (xspi->tx_len && (txfअगरo_cnt < XLP_SPI_FIFO_SIZE)) अणु
		j = 0;
		tx_data = 0;
		nbytes = min(xspi->tx_len, 4);
		क्रम (i = nbytes - 1; i >= 0; i--, j++)
			tx_data |= xspi->tx_buf[i] << (j * 8);

		xlp_spi_reg_ग_लिखो(xspi, xspi->cs, XLP_SPI_TXDATA_FIFO, tx_data);
		xspi->tx_len -= nbytes;
		xspi->tx_buf += nbytes;
		txfअगरo_cnt++;
	पूर्ण
पूर्ण

अटल irqवापस_t xlp_spi_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा xlp_spi_priv *xspi = dev_id;
	u32 stat;

	stat = xlp_spi_reg_पढ़ो(xspi, xspi->cs, XLP_SPI_STATUS) &
		XLP_SPI_STAT_MASK;
	अगर (!stat)
		वापस IRQ_NONE;

	अगर (stat & XLP_SPI_TX_INT) अणु
		अगर (xspi->tx_len)
			xlp_spi_fill_txfअगरo(xspi);
		अगर (stat & XLP_SPI_TX_UF)
			xspi->txerrors++;
	पूर्ण

	अगर (stat & XLP_SPI_RX_INT) अणु
		अगर (xspi->rx_len)
			xlp_spi_पढ़ो_rxfअगरo(xspi);
		अगर (stat & XLP_SPI_RX_OF)
			xspi->rxerrors++;
	पूर्ण

	/* ग_लिखो status back to clear पूर्णांकerrupts */
	xlp_spi_reg_ग_लिखो(xspi, xspi->cs, XLP_SPI_STATUS, stat);
	अगर (stat & XLP_SPI_XFR_DONE)
		complete(&xspi->करोne);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम xlp_spi_send_cmd(काष्ठा xlp_spi_priv *xspi, पूर्णांक xfer_len,
			पूर्णांक cmd_cont)
अणु
	u32 cmd = 0;

	अगर (xspi->tx_buf)
		cmd |= XLP_SPI_CMD_TX_MASK;
	अगर (xspi->rx_buf)
		cmd |= XLP_SPI_CMD_RX_MASK;
	अगर (cmd_cont)
		cmd |= XLP_SPI_CMD_CONT;
	cmd |= ((xfer_len * 8 - 1) << XLP_SPI_XFR_BITCNT_SHIFT);
	xlp_spi_reg_ग_लिखो(xspi, xspi->cs, XLP_SPI_CMD, cmd);
पूर्ण

अटल पूर्णांक xlp_spi_xfer_block(काष्ठा  xlp_spi_priv *xs,
		स्थिर अचिन्हित अक्षर *tx_buf,
		अचिन्हित अक्षर *rx_buf, पूर्णांक xfer_len, पूर्णांक cmd_cont)
अणु
	पूर्णांक समयout;
	u32 पूर्णांकr_mask = 0;

	xs->tx_buf = tx_buf;
	xs->rx_buf = rx_buf;
	xs->tx_len = (xs->tx_buf == शून्य) ? 0 : xfer_len;
	xs->rx_len = (xs->rx_buf == शून्य) ? 0 : xfer_len;
	xs->txerrors = xs->rxerrors = 0;

	/* fill TXDATA_FIFO, then send the CMD */
	अगर (xs->tx_len)
		xlp_spi_fill_txfअगरo(xs);

	xlp_spi_send_cmd(xs, xfer_len, cmd_cont);

	/*
	 * We are getting some spurious tx पूर्णांकerrupts, so aव्योम enabling
	 * tx पूर्णांकerrupts when only rx is in process.
	 * Enable all the पूर्णांकerrupts in tx हाल.
	 */
	अगर (xs->tx_len)
		पूर्णांकr_mask |= XLP_SPI_INTR_TXTH | XLP_SPI_INTR_TXUF |
				XLP_SPI_INTR_RXTH | XLP_SPI_INTR_RXOF;
	अन्यथा
		पूर्णांकr_mask |= XLP_SPI_INTR_RXTH | XLP_SPI_INTR_RXOF;

	पूर्णांकr_mask |= XLP_SPI_INTR_DONE;
	xlp_spi_reg_ग_लिखो(xs, xs->cs, XLP_SPI_INTR_EN, पूर्णांकr_mask);

	समयout = रुको_क्रम_completion_समयout(&xs->करोne,
				msecs_to_jअगरfies(1000));
	/* Disable पूर्णांकerrupts */
	xlp_spi_reg_ग_लिखो(xs, xs->cs, XLP_SPI_INTR_EN, 0x0);
	अगर (!समयout) अणु
		dev_err(&xs->dev, "xfer timedout!\n");
		जाओ out;
	पूर्ण
	अगर (xs->txerrors || xs->rxerrors)
		dev_err(&xs->dev, "Over/Underflow rx %d tx %d xfer %d!\n",
				xs->rxerrors, xs->txerrors, xfer_len);

	वापस xfer_len;
out:
	वापस -ETIMEDOUT;
पूर्ण

अटल पूर्णांक xlp_spi_txrx_bufs(काष्ठा xlp_spi_priv *xs, काष्ठा spi_transfer *t)
अणु
	पूर्णांक bytesleft, sz;
	अचिन्हित अक्षर *rx_buf;
	स्थिर अचिन्हित अक्षर *tx_buf;

	tx_buf = t->tx_buf;
	rx_buf = t->rx_buf;
	bytesleft = t->len;
	जबतक (bytesleft) अणु
		अगर (bytesleft > XLP_SPI_XFER_SIZE)
			sz = xlp_spi_xfer_block(xs, tx_buf, rx_buf,
					XLP_SPI_XFER_SIZE, 1);
		अन्यथा
			sz = xlp_spi_xfer_block(xs, tx_buf, rx_buf,
					bytesleft, xs->cmd_cont);
		अगर (sz < 0)
			वापस sz;
		bytesleft -= sz;
		अगर (tx_buf)
			tx_buf += sz;
		अगर (rx_buf)
			rx_buf += sz;
	पूर्ण
	वापस bytesleft;
पूर्ण

अटल पूर्णांक xlp_spi_transfer_one(काष्ठा spi_master *master,
					काष्ठा spi_device *spi,
					काष्ठा spi_transfer *t)
अणु
	काष्ठा xlp_spi_priv *xspi = spi_master_get_devdata(master);
	पूर्णांक ret = 0;

	xspi->cs = spi->chip_select;
	xspi->dev = spi->dev;

	अगर (spi_transfer_is_last(master, t))
		xspi->cmd_cont = 0;
	अन्यथा
		xspi->cmd_cont = 1;

	अगर (xlp_spi_txrx_bufs(xspi, t))
		ret = -EIO;

	spi_finalize_current_transfer(master);
	वापस ret;
पूर्ण

अटल पूर्णांक xlp_spi_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा spi_master *master;
	काष्ठा xlp_spi_priv *xspi;
	काष्ठा clk *clk;
	पूर्णांक irq, err;

	xspi = devm_kzalloc(&pdev->dev, माप(*xspi), GFP_KERNEL);
	अगर (!xspi)
		वापस -ENOMEM;

	xspi->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(xspi->base))
		वापस PTR_ERR(xspi->base);

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस irq;
	err = devm_request_irq(&pdev->dev, irq, xlp_spi_पूर्णांकerrupt, 0,
			pdev->name, xspi);
	अगर (err) अणु
		dev_err(&pdev->dev, "unable to request irq %d\n", irq);
		वापस err;
	पूर्ण

	clk = devm_clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(clk)) अणु
		dev_err(&pdev->dev, "could not get spi clock\n");
		वापस PTR_ERR(clk);
	पूर्ण

	xspi->spi_clk = clk_get_rate(clk);

	master = spi_alloc_master(&pdev->dev, 0);
	अगर (!master) अणु
		dev_err(&pdev->dev, "could not alloc master\n");
		वापस -ENOMEM;
	पूर्ण

	master->bus_num = 0;
	master->num_chipselect = XLP_SPI_MAX_CS;
	master->mode_bits = SPI_CPOL | SPI_CPHA | SPI_CS_HIGH;
	master->setup = xlp_spi_setup;
	master->transfer_one = xlp_spi_transfer_one;
	master->dev.of_node = pdev->dev.of_node;

	init_completion(&xspi->करोne);
	spi_master_set_devdata(master, xspi);
	xlp_spi_sysctl_setup(xspi);

	/* रेजिस्टर spi controller */
	err = devm_spi_रेजिस्टर_master(&pdev->dev, master);
	अगर (err) अणु
		dev_err(&pdev->dev, "spi register master failed!\n");
		spi_master_put(master);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_ACPI
अटल स्थिर काष्ठा acpi_device_id xlp_spi_acpi_match[] = अणु
	अणु "BRCM900D", 0 पूर्ण,
	अणु "CAV900D",  0 पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(acpi, xlp_spi_acpi_match);
#पूर्ण_अगर

अटल स्थिर काष्ठा of_device_id xlp_spi_dt_id[] = अणु
	अणु .compatible = "netlogic,xlp832-spi" पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, xlp_spi_dt_id);

अटल काष्ठा platक्रमm_driver xlp_spi_driver = अणु
	.probe	= xlp_spi_probe,
	.driver = अणु
		.name	= "xlp-spi",
		.of_match_table = xlp_spi_dt_id,
		.acpi_match_table = ACPI_PTR(xlp_spi_acpi_match),
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(xlp_spi_driver);

MODULE_AUTHOR("Kamlakant Patel <kamlakant.patel@broadcom.com>");
MODULE_DESCRIPTION("Netlogic XLP SPI controller driver");
MODULE_LICENSE("GPL v2");
