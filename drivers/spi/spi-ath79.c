<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * SPI controller driver क्रम the Atheros AR71XX/AR724X/AR913X SoCs
 *
 * Copyright (C) 2009-2011 Gabor Juhos <juhosg@खोलोwrt.org>
 *
 * This driver has been based on the spi-gpio.c:
 *	Copyright (C) 2006,2008 David Brownell
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/delay.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/पन.स>
#समावेश <linux/spi/spi.h>
#समावेश <linux/spi/spi_bitbang.h>
#समावेश <linux/bitops.h>
#समावेश <linux/clk.h>
#समावेश <linux/err.h>
#समावेश <linux/platक्रमm_data/spi-ath79.h>

#घोषणा DRV_NAME	"ath79-spi"

#घोषणा ATH79_SPI_RRW_DELAY_FACTOR	12000
#घोषणा MHZ				(1000 * 1000)

#घोषणा AR71XX_SPI_REG_FS		0x00	/* Function Select */
#घोषणा AR71XX_SPI_REG_CTRL		0x04	/* SPI Control */
#घोषणा AR71XX_SPI_REG_IOC		0x08	/* SPI I/O Control */
#घोषणा AR71XX_SPI_REG_RDS		0x0c	/* Read Data Shअगरt */

#घोषणा AR71XX_SPI_FS_GPIO		BIT(0)	/* Enable GPIO mode */

#घोषणा AR71XX_SPI_IOC_DO		BIT(0)	/* Data Out pin */
#घोषणा AR71XX_SPI_IOC_CLK		BIT(8)	/* CLK pin */
#घोषणा AR71XX_SPI_IOC_CS(n)		BIT(16 + (n))

काष्ठा ath79_spi अणु
	काष्ठा spi_bitbang	bitbang;
	u32			ioc_base;
	u32			reg_ctrl;
	व्योम __iomem		*base;
	काष्ठा clk		*clk;
	अचिन्हित पूर्णांक		rrw_delay;
पूर्ण;

अटल अंतरभूत u32 ath79_spi_rr(काष्ठा ath79_spi *sp, अचिन्हित पूर्णांक reg)
अणु
	वापस ioपढ़ो32(sp->base + reg);
पूर्ण

अटल अंतरभूत व्योम ath79_spi_wr(काष्ठा ath79_spi *sp, अचिन्हित पूर्णांक reg, u32 val)
अणु
	ioग_लिखो32(val, sp->base + reg);
पूर्ण

अटल अंतरभूत काष्ठा ath79_spi *ath79_spidev_to_sp(काष्ठा spi_device *spi)
अणु
	वापस spi_master_get_devdata(spi->master);
पूर्ण

अटल अंतरभूत व्योम ath79_spi_delay(काष्ठा ath79_spi *sp, अचिन्हित पूर्णांक nsecs)
अणु
	अगर (nsecs > sp->rrw_delay)
		ndelay(nsecs - sp->rrw_delay);
पूर्ण

अटल व्योम ath79_spi_chipselect(काष्ठा spi_device *spi, पूर्णांक is_active)
अणु
	काष्ठा ath79_spi *sp = ath79_spidev_to_sp(spi);
	पूर्णांक cs_high = (spi->mode & SPI_CS_HIGH) ? is_active : !is_active;
	u32 cs_bit = AR71XX_SPI_IOC_CS(spi->chip_select);

	अगर (cs_high)
		sp->ioc_base |= cs_bit;
	अन्यथा
		sp->ioc_base &= ~cs_bit;

	ath79_spi_wr(sp, AR71XX_SPI_REG_IOC, sp->ioc_base);
पूर्ण

अटल व्योम ath79_spi_enable(काष्ठा ath79_spi *sp)
अणु
	/* enable GPIO mode */
	ath79_spi_wr(sp, AR71XX_SPI_REG_FS, AR71XX_SPI_FS_GPIO);

	/* save CTRL रेजिस्टर */
	sp->reg_ctrl = ath79_spi_rr(sp, AR71XX_SPI_REG_CTRL);
	sp->ioc_base = ath79_spi_rr(sp, AR71XX_SPI_REG_IOC);

	/* clear clk and mosi in the base state */
	sp->ioc_base &= ~(AR71XX_SPI_IOC_DO | AR71XX_SPI_IOC_CLK);

	/* TODO: setup speed? */
	ath79_spi_wr(sp, AR71XX_SPI_REG_CTRL, 0x43);
पूर्ण

अटल व्योम ath79_spi_disable(काष्ठा ath79_spi *sp)
अणु
	/* restore CTRL रेजिस्टर */
	ath79_spi_wr(sp, AR71XX_SPI_REG_CTRL, sp->reg_ctrl);
	/* disable GPIO mode */
	ath79_spi_wr(sp, AR71XX_SPI_REG_FS, 0);
पूर्ण

अटल u32 ath79_spi_txrx_mode0(काष्ठा spi_device *spi, अचिन्हित पूर्णांक nsecs,
			       u32 word, u8 bits, अचिन्हित flags)
अणु
	काष्ठा ath79_spi *sp = ath79_spidev_to_sp(spi);
	u32 ioc = sp->ioc_base;

	/* घड़ी starts at inactive polarity */
	क्रम (word <<= (32 - bits); likely(bits); bits--) अणु
		u32 out;

		अगर (word & (1 << 31))
			out = ioc | AR71XX_SPI_IOC_DO;
		अन्यथा
			out = ioc & ~AR71XX_SPI_IOC_DO;

		/* setup MSB (to slave) on trailing edge */
		ath79_spi_wr(sp, AR71XX_SPI_REG_IOC, out);
		ath79_spi_delay(sp, nsecs);
		ath79_spi_wr(sp, AR71XX_SPI_REG_IOC, out | AR71XX_SPI_IOC_CLK);
		ath79_spi_delay(sp, nsecs);
		अगर (bits == 1)
			ath79_spi_wr(sp, AR71XX_SPI_REG_IOC, out);

		word <<= 1;
	पूर्ण

	वापस ath79_spi_rr(sp, AR71XX_SPI_REG_RDS);
पूर्ण

अटल पूर्णांक ath79_spi_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा spi_master *master;
	काष्ठा ath79_spi *sp;
	काष्ठा ath79_spi_platक्रमm_data *pdata;
	अचिन्हित दीर्घ rate;
	पूर्णांक ret;

	master = spi_alloc_master(&pdev->dev, माप(*sp));
	अगर (master == शून्य) अणु
		dev_err(&pdev->dev, "failed to allocate spi master\n");
		वापस -ENOMEM;
	पूर्ण

	sp = spi_master_get_devdata(master);
	master->dev.of_node = pdev->dev.of_node;
	platक्रमm_set_drvdata(pdev, sp);

	pdata = dev_get_platdata(&pdev->dev);

	master->use_gpio_descriptors = true;
	master->bits_per_word_mask = SPI_BPW_RANGE_MASK(1, 32);
	master->flags = SPI_MASTER_GPIO_SS;
	अगर (pdata) अणु
		master->bus_num = pdata->bus_num;
		master->num_chipselect = pdata->num_chipselect;
	पूर्ण

	sp->bitbang.master = master;
	sp->bitbang.chipselect = ath79_spi_chipselect;
	sp->bitbang.txrx_word[SPI_MODE_0] = ath79_spi_txrx_mode0;
	sp->bitbang.flags = SPI_CS_HIGH;

	sp->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(sp->base)) अणु
		ret = PTR_ERR(sp->base);
		जाओ err_put_master;
	पूर्ण

	sp->clk = devm_clk_get(&pdev->dev, "ahb");
	अगर (IS_ERR(sp->clk)) अणु
		ret = PTR_ERR(sp->clk);
		जाओ err_put_master;
	पूर्ण

	ret = clk_prepare_enable(sp->clk);
	अगर (ret)
		जाओ err_put_master;

	rate = DIV_ROUND_UP(clk_get_rate(sp->clk), MHZ);
	अगर (!rate) अणु
		ret = -EINVAL;
		जाओ err_clk_disable;
	पूर्ण

	sp->rrw_delay = ATH79_SPI_RRW_DELAY_FACTOR / rate;
	dev_dbg(&pdev->dev, "register read/write delay is %u nsecs\n",
		sp->rrw_delay);

	ath79_spi_enable(sp);
	ret = spi_bitbang_start(&sp->bitbang);
	अगर (ret)
		जाओ err_disable;

	वापस 0;

err_disable:
	ath79_spi_disable(sp);
err_clk_disable:
	clk_disable_unprepare(sp->clk);
err_put_master:
	spi_master_put(sp->bitbang.master);

	वापस ret;
पूर्ण

अटल पूर्णांक ath79_spi_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा ath79_spi *sp = platक्रमm_get_drvdata(pdev);

	spi_bitbang_stop(&sp->bitbang);
	ath79_spi_disable(sp);
	clk_disable_unprepare(sp->clk);
	spi_master_put(sp->bitbang.master);

	वापस 0;
पूर्ण

अटल व्योम ath79_spi_shutकरोwn(काष्ठा platक्रमm_device *pdev)
अणु
	ath79_spi_हटाओ(pdev);
पूर्ण

अटल स्थिर काष्ठा of_device_id ath79_spi_of_match[] = अणु
	अणु .compatible = "qca,ar7100-spi", पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, ath79_spi_of_match);

अटल काष्ठा platक्रमm_driver ath79_spi_driver = अणु
	.probe		= ath79_spi_probe,
	.हटाओ		= ath79_spi_हटाओ,
	.shutकरोwn	= ath79_spi_shutकरोwn,
	.driver		= अणु
		.name	= DRV_NAME,
		.of_match_table = ath79_spi_of_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(ath79_spi_driver);

MODULE_DESCRIPTION("SPI controller driver for Atheros AR71XX/AR724X/AR913X");
MODULE_AUTHOR("Gabor Juhos <juhosg@openwrt.org>");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:" DRV_NAME);
