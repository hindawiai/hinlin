<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Xtensa xtfpga SPI controller driver
 *
 * Copyright (c) 2014 Cadence Design Systems Inc.
 */

#समावेश <linux/delay.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/spi/spi_bitbang.h>

#घोषणा XTFPGA_SPI_NAME "xtfpga_spi"

#घोषणा XTFPGA_SPI_START	0x0
#घोषणा XTFPGA_SPI_BUSY		0x4
#घोषणा XTFPGA_SPI_DATA		0x8

#घोषणा BUSY_WAIT_US		100

काष्ठा xtfpga_spi अणु
	काष्ठा spi_bitbang bitbang;
	व्योम __iomem *regs;
	u32 data;
	अचिन्हित data_sz;
पूर्ण;

अटल अंतरभूत व्योम xtfpga_spi_ग_लिखो32(स्थिर काष्ठा xtfpga_spi *spi,
				      अचिन्हित addr, u32 val)
अणु
	__raw_ग_लिखोl(val, spi->regs + addr);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक xtfpga_spi_पढ़ो32(स्थिर काष्ठा xtfpga_spi *spi,
					     अचिन्हित addr)
अणु
	वापस __raw_पढ़ोl(spi->regs + addr);
पूर्ण

अटल अंतरभूत व्योम xtfpga_spi_रुको_busy(काष्ठा xtfpga_spi *xspi)
अणु
	अचिन्हित i;

	क्रम (i = 0; xtfpga_spi_पढ़ो32(xspi, XTFPGA_SPI_BUSY) &&
	     i < BUSY_WAIT_US; ++i)
		udelay(1);
	WARN_ON_ONCE(i == BUSY_WAIT_US);
पूर्ण

अटल u32 xtfpga_spi_txrx_word(काष्ठा spi_device *spi, अचिन्हित nsecs,
				u32 v, u8 bits, अचिन्हित flags)
अणु
	काष्ठा xtfpga_spi *xspi = spi_master_get_devdata(spi->master);

	xspi->data = (xspi->data << bits) | (v & GENMASK(bits - 1, 0));
	xspi->data_sz += bits;
	अगर (xspi->data_sz >= 16) अणु
		xtfpga_spi_ग_लिखो32(xspi, XTFPGA_SPI_DATA,
				   xspi->data >> (xspi->data_sz - 16));
		xspi->data_sz -= 16;
		xtfpga_spi_ग_लिखो32(xspi, XTFPGA_SPI_START, 1);
		xtfpga_spi_रुको_busy(xspi);
		xtfpga_spi_ग_लिखो32(xspi, XTFPGA_SPI_START, 0);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम xtfpga_spi_chipselect(काष्ठा spi_device *spi, पूर्णांक is_on)
अणु
	काष्ठा xtfpga_spi *xspi = spi_master_get_devdata(spi->master);

	WARN_ON(xspi->data_sz != 0);
	xspi->data_sz = 0;
पूर्ण

अटल पूर्णांक xtfpga_spi_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा xtfpga_spi *xspi;
	पूर्णांक ret;
	काष्ठा spi_master *master;

	master = spi_alloc_master(&pdev->dev, माप(काष्ठा xtfpga_spi));
	अगर (!master)
		वापस -ENOMEM;

	master->flags = SPI_MASTER_NO_RX;
	master->bits_per_word_mask = SPI_BPW_RANGE_MASK(1, 16);
	master->bus_num = pdev->dev.id;
	master->dev.of_node = pdev->dev.of_node;

	xspi = spi_master_get_devdata(master);
	xspi->bitbang.master = master;
	xspi->bitbang.chipselect = xtfpga_spi_chipselect;
	xspi->bitbang.txrx_word[SPI_MODE_0] = xtfpga_spi_txrx_word;
	xspi->regs = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(xspi->regs)) अणु
		ret = PTR_ERR(xspi->regs);
		जाओ err;
	पूर्ण

	xtfpga_spi_ग_लिखो32(xspi, XTFPGA_SPI_START, 0);
	usleep_range(1000, 2000);
	अगर (xtfpga_spi_पढ़ो32(xspi, XTFPGA_SPI_BUSY)) अणु
		dev_err(&pdev->dev, "Device stuck in busy state\n");
		ret = -EBUSY;
		जाओ err;
	पूर्ण

	ret = spi_bitbang_start(&xspi->bitbang);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "spi_bitbang_start failed\n");
		जाओ err;
	पूर्ण

	platक्रमm_set_drvdata(pdev, master);
	वापस 0;
err:
	spi_master_put(master);
	वापस ret;
पूर्ण

अटल पूर्णांक xtfpga_spi_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा spi_master *master = platक्रमm_get_drvdata(pdev);
	काष्ठा xtfpga_spi *xspi = spi_master_get_devdata(master);

	spi_bitbang_stop(&xspi->bitbang);
	spi_master_put(master);

	वापस 0;
पूर्ण

MODULE_ALIAS("platform:" XTFPGA_SPI_NAME);

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id xtfpga_spi_of_match[] = अणु
	अणु .compatible = "cdns,xtfpga-spi", पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, xtfpga_spi_of_match);
#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver xtfpga_spi_driver = अणु
	.probe = xtfpga_spi_probe,
	.हटाओ = xtfpga_spi_हटाओ,
	.driver = अणु
		.name = XTFPGA_SPI_NAME,
		.of_match_table = of_match_ptr(xtfpga_spi_of_match),
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(xtfpga_spi_driver);

MODULE_AUTHOR("Max Filippov <jcmvbkbc@gmail.com>");
MODULE_DESCRIPTION("xtensa xtfpga SPI driver");
MODULE_LICENSE("GPL");
