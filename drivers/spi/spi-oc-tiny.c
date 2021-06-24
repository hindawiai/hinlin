<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * OpenCores tiny SPI master driver
 *
 * https://खोलोcores.org/project,tiny_spi
 *
 * Copyright (C) 2011 Thomas Chou <thomas@wytron.com.tw>
 *
 * Based on spi_s3c24xx.c, which is:
 * Copyright (c) 2006 Ben Dooks
 * Copyright (c) 2006 Simtec Electronics
 *	Ben Dooks <ben@simtec.co.uk>
 */

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/spi/spi_bitbang.h>
#समावेश <linux/spi/spi_oc_tiny.h>
#समावेश <linux/पन.स>
#समावेश <linux/of.h>

#घोषणा DRV_NAME "spi_oc_tiny"

#घोषणा TINY_SPI_RXDATA 0
#घोषणा TINY_SPI_TXDATA 4
#घोषणा TINY_SPI_STATUS 8
#घोषणा TINY_SPI_CONTROL 12
#घोषणा TINY_SPI_BAUD 16

#घोषणा TINY_SPI_STATUS_TXE 0x1
#घोषणा TINY_SPI_STATUS_TXR 0x2

काष्ठा tiny_spi अणु
	/* bitbang has to be first */
	काष्ठा spi_bitbang bitbang;
	काष्ठा completion करोne;

	व्योम __iomem *base;
	पूर्णांक irq;
	अचिन्हित पूर्णांक freq;
	अचिन्हित पूर्णांक baudwidth;
	अचिन्हित पूर्णांक baud;
	अचिन्हित पूर्णांक speed_hz;
	अचिन्हित पूर्णांक mode;
	अचिन्हित पूर्णांक len;
	अचिन्हित पूर्णांक txc, rxc;
	स्थिर u8 *txp;
	u8 *rxp;
पूर्ण;

अटल अंतरभूत काष्ठा tiny_spi *tiny_spi_to_hw(काष्ठा spi_device *sdev)
अणु
	वापस spi_master_get_devdata(sdev->master);
पूर्ण

अटल अचिन्हित पूर्णांक tiny_spi_baud(काष्ठा spi_device *spi, अचिन्हित पूर्णांक hz)
अणु
	काष्ठा tiny_spi *hw = tiny_spi_to_hw(spi);

	वापस min(DIV_ROUND_UP(hw->freq, hz * 2), (1U << hw->baudwidth)) - 1;
पूर्ण

अटल पूर्णांक tiny_spi_setup_transfer(काष्ठा spi_device *spi,
				   काष्ठा spi_transfer *t)
अणु
	काष्ठा tiny_spi *hw = tiny_spi_to_hw(spi);
	अचिन्हित पूर्णांक baud = hw->baud;

	अगर (t) अणु
		अगर (t->speed_hz && t->speed_hz != hw->speed_hz)
			baud = tiny_spi_baud(spi, t->speed_hz);
	पूर्ण
	ग_लिखोl(baud, hw->base + TINY_SPI_BAUD);
	ग_लिखोl(hw->mode, hw->base + TINY_SPI_CONTROL);
	वापस 0;
पूर्ण

अटल पूर्णांक tiny_spi_setup(काष्ठा spi_device *spi)
अणु
	काष्ठा tiny_spi *hw = tiny_spi_to_hw(spi);

	अगर (spi->max_speed_hz != hw->speed_hz) अणु
		hw->speed_hz = spi->max_speed_hz;
		hw->baud = tiny_spi_baud(spi, hw->speed_hz);
	पूर्ण
	hw->mode = spi->mode & (SPI_CPOL | SPI_CPHA);
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम tiny_spi_रुको_txr(काष्ठा tiny_spi *hw)
अणु
	जबतक (!(पढ़ोb(hw->base + TINY_SPI_STATUS) &
		 TINY_SPI_STATUS_TXR))
		cpu_relax();
पूर्ण

अटल अंतरभूत व्योम tiny_spi_रुको_txe(काष्ठा tiny_spi *hw)
अणु
	जबतक (!(पढ़ोb(hw->base + TINY_SPI_STATUS) &
		 TINY_SPI_STATUS_TXE))
		cpu_relax();
पूर्ण

अटल पूर्णांक tiny_spi_txrx_bufs(काष्ठा spi_device *spi, काष्ठा spi_transfer *t)
अणु
	काष्ठा tiny_spi *hw = tiny_spi_to_hw(spi);
	स्थिर u8 *txp = t->tx_buf;
	u8 *rxp = t->rx_buf;
	अचिन्हित पूर्णांक i;

	अगर (hw->irq >= 0) अणु
		/* use पूर्णांकerrupt driven data transfer */
		hw->len = t->len;
		hw->txp = t->tx_buf;
		hw->rxp = t->rx_buf;
		hw->txc = 0;
		hw->rxc = 0;

		/* send the first byte */
		अगर (t->len > 1) अणु
			ग_लिखोb(hw->txp ? *hw->txp++ : 0,
			       hw->base + TINY_SPI_TXDATA);
			hw->txc++;
			ग_लिखोb(hw->txp ? *hw->txp++ : 0,
			       hw->base + TINY_SPI_TXDATA);
			hw->txc++;
			ग_लिखोb(TINY_SPI_STATUS_TXR, hw->base + TINY_SPI_STATUS);
		पूर्ण अन्यथा अणु
			ग_लिखोb(hw->txp ? *hw->txp++ : 0,
			       hw->base + TINY_SPI_TXDATA);
			hw->txc++;
			ग_लिखोb(TINY_SPI_STATUS_TXE, hw->base + TINY_SPI_STATUS);
		पूर्ण

		रुको_क्रम_completion(&hw->करोne);
	पूर्ण अन्यथा अणु
		/* we need to tighten the transfer loop */
		ग_लिखोb(txp ? *txp++ : 0, hw->base + TINY_SPI_TXDATA);
		क्रम (i = 1; i < t->len; i++) अणु
			ग_लिखोb(txp ? *txp++ : 0, hw->base + TINY_SPI_TXDATA);

			अगर (rxp || (i != t->len - 1))
				tiny_spi_रुको_txr(hw);
			अगर (rxp)
				*rxp++ = पढ़ोb(hw->base + TINY_SPI_TXDATA);
		पूर्ण
		tiny_spi_रुको_txe(hw);
		अगर (rxp)
			*rxp++ = पढ़ोb(hw->base + TINY_SPI_RXDATA);
	पूर्ण

	वापस t->len;
पूर्ण

अटल irqवापस_t tiny_spi_irq(पूर्णांक irq, व्योम *dev)
अणु
	काष्ठा tiny_spi *hw = dev;

	ग_लिखोb(0, hw->base + TINY_SPI_STATUS);
	अगर (hw->rxc + 1 == hw->len) अणु
		अगर (hw->rxp)
			*hw->rxp++ = पढ़ोb(hw->base + TINY_SPI_RXDATA);
		hw->rxc++;
		complete(&hw->करोne);
	पूर्ण अन्यथा अणु
		अगर (hw->rxp)
			*hw->rxp++ = पढ़ोb(hw->base + TINY_SPI_TXDATA);
		hw->rxc++;
		अगर (hw->txc < hw->len) अणु
			ग_लिखोb(hw->txp ? *hw->txp++ : 0,
			       hw->base + TINY_SPI_TXDATA);
			hw->txc++;
			ग_लिखोb(TINY_SPI_STATUS_TXR,
			       hw->base + TINY_SPI_STATUS);
		पूर्ण अन्यथा अणु
			ग_लिखोb(TINY_SPI_STATUS_TXE,
			       hw->base + TINY_SPI_STATUS);
		पूर्ण
	पूर्ण
	वापस IRQ_HANDLED;
पूर्ण

#अगर_घोषित CONFIG_OF
#समावेश <linux/of_gpपन.स>

अटल पूर्णांक tiny_spi_of_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा tiny_spi *hw = platक्रमm_get_drvdata(pdev);
	काष्ठा device_node *np = pdev->dev.of_node;
	u32 val;

	अगर (!np)
		वापस 0;
	hw->bitbang.master->dev.of_node = pdev->dev.of_node;
	अगर (!of_property_पढ़ो_u32(np, "clock-frequency", &val))
		hw->freq = val;
	अगर (!of_property_पढ़ो_u32(np, "baud-width", &val))
		hw->baudwidth = val;
	वापस 0;
पूर्ण
#अन्यथा /* !CONFIG_OF */
अटल पूर्णांक tiny_spi_of_probe(काष्ठा platक्रमm_device *pdev)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_OF */

अटल पूर्णांक tiny_spi_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा tiny_spi_platक्रमm_data *platp = dev_get_platdata(&pdev->dev);
	काष्ठा tiny_spi *hw;
	काष्ठा spi_master *master;
	पूर्णांक err = -ENODEV;

	master = spi_alloc_master(&pdev->dev, माप(काष्ठा tiny_spi));
	अगर (!master)
		वापस err;

	/* setup the master state. */
	master->bus_num = pdev->id;
	master->mode_bits = SPI_CPOL | SPI_CPHA | SPI_CS_HIGH;
	master->setup = tiny_spi_setup;
	master->use_gpio_descriptors = true;

	hw = spi_master_get_devdata(master);
	platक्रमm_set_drvdata(pdev, hw);

	/* setup the state क्रम the bitbang driver */
	hw->bitbang.master = master;
	hw->bitbang.setup_transfer = tiny_spi_setup_transfer;
	hw->bitbang.txrx_bufs = tiny_spi_txrx_bufs;

	/* find and map our resources */
	hw->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(hw->base)) अणु
		err = PTR_ERR(hw->base);
		जाओ निकास;
	पूर्ण
	/* irq is optional */
	hw->irq = platक्रमm_get_irq(pdev, 0);
	अगर (hw->irq >= 0) अणु
		init_completion(&hw->करोne);
		err = devm_request_irq(&pdev->dev, hw->irq, tiny_spi_irq, 0,
				       pdev->name, hw);
		अगर (err)
			जाओ निकास;
	पूर्ण
	/* find platक्रमm data */
	अगर (platp) अणु
		hw->freq = platp->freq;
		hw->baudwidth = platp->baudwidth;
	पूर्ण अन्यथा अणु
		err = tiny_spi_of_probe(pdev);
		अगर (err)
			जाओ निकास;
	पूर्ण

	/* रेजिस्टर our spi controller */
	err = spi_bitbang_start(&hw->bitbang);
	अगर (err)
		जाओ निकास;
	dev_info(&pdev->dev, "base %p, irq %d\n", hw->base, hw->irq);

	वापस 0;

निकास:
	spi_master_put(master);
	वापस err;
पूर्ण

अटल पूर्णांक tiny_spi_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा tiny_spi *hw = platक्रमm_get_drvdata(pdev);
	काष्ठा spi_master *master = hw->bitbang.master;

	spi_bitbang_stop(&hw->bitbang);
	spi_master_put(master);
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id tiny_spi_match[] = अणु
	अणु .compatible = "opencores,tiny-spi-rtlsvn2", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, tiny_spi_match);
#पूर्ण_अगर /* CONFIG_OF */

अटल काष्ठा platक्रमm_driver tiny_spi_driver = अणु
	.probe = tiny_spi_probe,
	.हटाओ = tiny_spi_हटाओ,
	.driver = अणु
		.name = DRV_NAME,
		.pm = शून्य,
		.of_match_table = of_match_ptr(tiny_spi_match),
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(tiny_spi_driver);

MODULE_DESCRIPTION("OpenCores tiny SPI driver");
MODULE_AUTHOR("Thomas Chou <thomas@wytron.com.tw>");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:" DRV_NAME);
