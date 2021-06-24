<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * SPI controller driver क्रम the Mikrotik RB4xx boards
 *
 * Copyright (C) 2010 Gabor Juhos <juhosg@खोलोwrt.org>
 * Copyright (C) 2015 Bert Vermeulen <bert@biot.com>
 *
 * This file was based on the patches क्रम Linux 2.6.27.39 published by
 * MikroTik क्रम their RouterBoard 4xx series devices.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/clk.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/of.h>

#समावेश <यंत्र/mach-ath79/ar71xx_regs.h>

काष्ठा rb4xx_spi अणु
	व्योम __iomem *base;
	काष्ठा clk *clk;
पूर्ण;

अटल अंतरभूत u32 rb4xx_पढ़ो(काष्ठा rb4xx_spi *rbspi, u32 reg)
अणु
	वापस __raw_पढ़ोl(rbspi->base + reg);
पूर्ण

अटल अंतरभूत व्योम rb4xx_ग_लिखो(काष्ठा rb4xx_spi *rbspi, u32 reg, u32 value)
अणु
	__raw_ग_लिखोl(value, rbspi->base + reg);
पूर्ण

अटल अंतरभूत व्योम करो_spi_clk(काष्ठा rb4xx_spi *rbspi, u32 spi_ioc, पूर्णांक value)
अणु
	u32 regval;

	regval = spi_ioc;
	अगर (value & BIT(0))
		regval |= AR71XX_SPI_IOC_DO;

	rb4xx_ग_लिखो(rbspi, AR71XX_SPI_REG_IOC, regval);
	rb4xx_ग_लिखो(rbspi, AR71XX_SPI_REG_IOC, regval | AR71XX_SPI_IOC_CLK);
पूर्ण

अटल व्योम करो_spi_byte(काष्ठा rb4xx_spi *rbspi, u32 spi_ioc, u8 byte)
अणु
	पूर्णांक i;

	क्रम (i = 7; i >= 0; i--)
		करो_spi_clk(rbspi, spi_ioc, byte >> i);
पूर्ण

/* The CS2 pin is used to घड़ी in a second bit per घड़ी cycle. */
अटल अंतरभूत व्योम करो_spi_clk_two(काष्ठा rb4xx_spi *rbspi, u32 spi_ioc,
				   u8 value)
अणु
	u32 regval;

	regval = spi_ioc;
	अगर (value & BIT(1))
		regval |= AR71XX_SPI_IOC_DO;
	अगर (value & BIT(0))
		regval |= AR71XX_SPI_IOC_CS2;

	rb4xx_ग_लिखो(rbspi, AR71XX_SPI_REG_IOC, regval);
	rb4xx_ग_लिखो(rbspi, AR71XX_SPI_REG_IOC, regval | AR71XX_SPI_IOC_CLK);
पूर्ण

/* Two bits at a समय, msb first */
अटल व्योम करो_spi_byte_two(काष्ठा rb4xx_spi *rbspi, u32 spi_ioc, u8 byte)
अणु
	करो_spi_clk_two(rbspi, spi_ioc, byte >> 6);
	करो_spi_clk_two(rbspi, spi_ioc, byte >> 4);
	करो_spi_clk_two(rbspi, spi_ioc, byte >> 2);
	करो_spi_clk_two(rbspi, spi_ioc, byte >> 0);
पूर्ण

अटल व्योम rb4xx_set_cs(काष्ठा spi_device *spi, bool enable)
अणु
	काष्ठा rb4xx_spi *rbspi = spi_master_get_devdata(spi->master);

	/*
	 * Setting CS is करोne aदीर्घ with bitbanging the actual values,
	 * since it's all on the same hardware रेजिस्टर. However the
	 * CPLD needs CS deselected after every command.
	 */
	अगर (enable)
		rb4xx_ग_लिखो(rbspi, AR71XX_SPI_REG_IOC,
			    AR71XX_SPI_IOC_CS0 | AR71XX_SPI_IOC_CS1);
पूर्ण

अटल पूर्णांक rb4xx_transfer_one(काष्ठा spi_master *master,
			      काष्ठा spi_device *spi, काष्ठा spi_transfer *t)
अणु
	काष्ठा rb4xx_spi *rbspi = spi_master_get_devdata(master);
	पूर्णांक i;
	u32 spi_ioc;
	u8 *rx_buf;
	स्थिर u8 *tx_buf;

	/*
	 * Prime the SPI रेजिस्टर with the SPI device selected. The m25p80 boot
	 * flash and CPLD share the CS0 pin. This works because the CPLD's
	 * command set was deचिन्हित to almost not clash with that of the
	 * boot flash.
	 */
	अगर (spi->chip_select == 2)
		/* MMC */
		spi_ioc = AR71XX_SPI_IOC_CS0;
	अन्यथा
		/* Boot flash and CPLD */
		spi_ioc = AR71XX_SPI_IOC_CS1;

	tx_buf = t->tx_buf;
	rx_buf = t->rx_buf;
	क्रम (i = 0; i < t->len; ++i) अणु
		अगर (t->tx_nbits == SPI_NBITS_DUAL)
			/* CPLD can use two-wire transfers */
			करो_spi_byte_two(rbspi, spi_ioc, tx_buf[i]);
		अन्यथा
			करो_spi_byte(rbspi, spi_ioc, tx_buf[i]);
		अगर (!rx_buf)
			जारी;
		rx_buf[i] = rb4xx_पढ़ो(rbspi, AR71XX_SPI_REG_RDS);
	पूर्ण
	spi_finalize_current_transfer(master);

	वापस 0;
पूर्ण

अटल पूर्णांक rb4xx_spi_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा spi_master *master;
	काष्ठा clk *ahb_clk;
	काष्ठा rb4xx_spi *rbspi;
	पूर्णांक err;
	व्योम __iomem *spi_base;

	spi_base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(spi_base))
		वापस PTR_ERR(spi_base);

	master = devm_spi_alloc_master(&pdev->dev, माप(*rbspi));
	अगर (!master)
		वापस -ENOMEM;

	ahb_clk = devm_clk_get(&pdev->dev, "ahb");
	अगर (IS_ERR(ahb_clk))
		वापस PTR_ERR(ahb_clk);

	master->dev.of_node = pdev->dev.of_node;
	master->bus_num = 0;
	master->num_chipselect = 3;
	master->mode_bits = SPI_TX_DUAL;
	master->bits_per_word_mask = SPI_BPW_MASK(8);
	master->flags = SPI_MASTER_MUST_TX;
	master->transfer_one = rb4xx_transfer_one;
	master->set_cs = rb4xx_set_cs;

	rbspi = spi_master_get_devdata(master);
	rbspi->base = spi_base;
	rbspi->clk = ahb_clk;
	platक्रमm_set_drvdata(pdev, rbspi);

	err = devm_spi_रेजिस्टर_master(&pdev->dev, master);
	अगर (err) अणु
		dev_err(&pdev->dev, "failed to register SPI master\n");
		वापस err;
	पूर्ण

	err = clk_prepare_enable(ahb_clk);
	अगर (err)
		वापस err;

	/* Enable SPI */
	rb4xx_ग_लिखो(rbspi, AR71XX_SPI_REG_FS, AR71XX_SPI_FS_GPIO);

	वापस 0;
पूर्ण

अटल पूर्णांक rb4xx_spi_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा rb4xx_spi *rbspi = platक्रमm_get_drvdata(pdev);

	clk_disable_unprepare(rbspi->clk);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id rb4xx_spi_dt_match[] = अणु
	अणु .compatible = "mikrotik,rb4xx-spi" पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, rb4xx_spi_dt_match);

अटल काष्ठा platक्रमm_driver rb4xx_spi_drv = अणु
	.probe = rb4xx_spi_probe,
	.हटाओ = rb4xx_spi_हटाओ,
	.driver = अणु
		.name = "rb4xx-spi",
		.of_match_table = of_match_ptr(rb4xx_spi_dt_match),
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(rb4xx_spi_drv);

MODULE_DESCRIPTION("Mikrotik RB4xx SPI controller driver");
MODULE_AUTHOR("Gabor Juhos <juhosg@openwrt.org>");
MODULE_AUTHOR("Bert Vermeulen <bert@biot.com>");
MODULE_LICENSE("GPL v2");
