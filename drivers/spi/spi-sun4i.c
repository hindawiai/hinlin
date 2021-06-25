<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2012 - 2014 Allwinner Tech
 * Pan Nan <pannan@allwinnertech.com>
 *
 * Copyright (C) 2014 Maxime Ripard
 * Maxime Ripard <maxime.ripard@मुक्त-electrons.com>
 */

#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>

#समावेश <linux/spi/spi.h>

#घोषणा SUN4I_FIFO_DEPTH		64

#घोषणा SUN4I_RXDATA_REG		0x00

#घोषणा SUN4I_TXDATA_REG		0x04

#घोषणा SUN4I_CTL_REG			0x08
#घोषणा SUN4I_CTL_ENABLE			BIT(0)
#घोषणा SUN4I_CTL_MASTER			BIT(1)
#घोषणा SUN4I_CTL_CPHA				BIT(2)
#घोषणा SUN4I_CTL_CPOL				BIT(3)
#घोषणा SUN4I_CTL_CS_ACTIVE_LOW			BIT(4)
#घोषणा SUN4I_CTL_LMTF				BIT(6)
#घोषणा SUN4I_CTL_TF_RST			BIT(8)
#घोषणा SUN4I_CTL_RF_RST			BIT(9)
#घोषणा SUN4I_CTL_XCH				BIT(10)
#घोषणा SUN4I_CTL_CS_MASK			0x3000
#घोषणा SUN4I_CTL_CS(cs)			(((cs) << 12) & SUN4I_CTL_CS_MASK)
#घोषणा SUN4I_CTL_DHB				BIT(15)
#घोषणा SUN4I_CTL_CS_MANUAL			BIT(16)
#घोषणा SUN4I_CTL_CS_LEVEL			BIT(17)
#घोषणा SUN4I_CTL_TP				BIT(18)

#घोषणा SUN4I_INT_CTL_REG		0x0c
#घोषणा SUN4I_INT_CTL_RF_F34			BIT(4)
#घोषणा SUN4I_INT_CTL_TF_E34			BIT(12)
#घोषणा SUN4I_INT_CTL_TC			BIT(16)

#घोषणा SUN4I_INT_STA_REG		0x10

#घोषणा SUN4I_DMA_CTL_REG		0x14

#घोषणा SUN4I_WAIT_REG			0x18

#घोषणा SUN4I_CLK_CTL_REG		0x1c
#घोषणा SUN4I_CLK_CTL_CDR2_MASK			0xff
#घोषणा SUN4I_CLK_CTL_CDR2(भाग)			((भाग) & SUN4I_CLK_CTL_CDR2_MASK)
#घोषणा SUN4I_CLK_CTL_CDR1_MASK			0xf
#घोषणा SUN4I_CLK_CTL_CDR1(भाग)			(((भाग) & SUN4I_CLK_CTL_CDR1_MASK) << 8)
#घोषणा SUN4I_CLK_CTL_DRS			BIT(12)

#घोषणा SUN4I_MAX_XFER_SIZE			0xffffff

#घोषणा SUN4I_BURST_CNT_REG		0x20
#घोषणा SUN4I_BURST_CNT(cnt)			((cnt) & SUN4I_MAX_XFER_SIZE)

#घोषणा SUN4I_XMIT_CNT_REG		0x24
#घोषणा SUN4I_XMIT_CNT(cnt)			((cnt) & SUN4I_MAX_XFER_SIZE)


#घोषणा SUN4I_FIFO_STA_REG		0x28
#घोषणा SUN4I_FIFO_STA_RF_CNT_MASK		0x7f
#घोषणा SUN4I_FIFO_STA_RF_CNT_BITS		0
#घोषणा SUN4I_FIFO_STA_TF_CNT_MASK		0x7f
#घोषणा SUN4I_FIFO_STA_TF_CNT_BITS		16

काष्ठा sun4i_spi अणु
	काष्ठा spi_master	*master;
	व्योम __iomem		*base_addr;
	काष्ठा clk		*hclk;
	काष्ठा clk		*mclk;

	काष्ठा completion	करोne;

	स्थिर u8		*tx_buf;
	u8			*rx_buf;
	पूर्णांक			len;
पूर्ण;

अटल अंतरभूत u32 sun4i_spi_पढ़ो(काष्ठा sun4i_spi *sspi, u32 reg)
अणु
	वापस पढ़ोl(sspi->base_addr + reg);
पूर्ण

अटल अंतरभूत व्योम sun4i_spi_ग_लिखो(काष्ठा sun4i_spi *sspi, u32 reg, u32 value)
अणु
	ग_लिखोl(value, sspi->base_addr + reg);
पूर्ण

अटल अंतरभूत u32 sun4i_spi_get_tx_fअगरo_count(काष्ठा sun4i_spi *sspi)
अणु
	u32 reg = sun4i_spi_पढ़ो(sspi, SUN4I_FIFO_STA_REG);

	reg >>= SUN4I_FIFO_STA_TF_CNT_BITS;

	वापस reg & SUN4I_FIFO_STA_TF_CNT_MASK;
पूर्ण

अटल अंतरभूत व्योम sun4i_spi_enable_पूर्णांकerrupt(काष्ठा sun4i_spi *sspi, u32 mask)
अणु
	u32 reg = sun4i_spi_पढ़ो(sspi, SUN4I_INT_CTL_REG);

	reg |= mask;
	sun4i_spi_ग_लिखो(sspi, SUN4I_INT_CTL_REG, reg);
पूर्ण

अटल अंतरभूत व्योम sun4i_spi_disable_पूर्णांकerrupt(काष्ठा sun4i_spi *sspi, u32 mask)
अणु
	u32 reg = sun4i_spi_पढ़ो(sspi, SUN4I_INT_CTL_REG);

	reg &= ~mask;
	sun4i_spi_ग_लिखो(sspi, SUN4I_INT_CTL_REG, reg);
पूर्ण

अटल अंतरभूत व्योम sun4i_spi_drain_fअगरo(काष्ठा sun4i_spi *sspi, पूर्णांक len)
अणु
	u32 reg, cnt;
	u8 byte;

	/* See how much data is available */
	reg = sun4i_spi_पढ़ो(sspi, SUN4I_FIFO_STA_REG);
	reg &= SUN4I_FIFO_STA_RF_CNT_MASK;
	cnt = reg >> SUN4I_FIFO_STA_RF_CNT_BITS;

	अगर (len > cnt)
		len = cnt;

	जबतक (len--) अणु
		byte = पढ़ोb(sspi->base_addr + SUN4I_RXDATA_REG);
		अगर (sspi->rx_buf)
			*sspi->rx_buf++ = byte;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम sun4i_spi_fill_fअगरo(काष्ठा sun4i_spi *sspi, पूर्णांक len)
अणु
	u32 cnt;
	u8 byte;

	/* See how much data we can fit */
	cnt = SUN4I_FIFO_DEPTH - sun4i_spi_get_tx_fअगरo_count(sspi);

	len = min3(len, (पूर्णांक)cnt, sspi->len);

	जबतक (len--) अणु
		byte = sspi->tx_buf ? *sspi->tx_buf++ : 0;
		ग_लिखोb(byte, sspi->base_addr + SUN4I_TXDATA_REG);
		sspi->len--;
	पूर्ण
पूर्ण

अटल व्योम sun4i_spi_set_cs(काष्ठा spi_device *spi, bool enable)
अणु
	काष्ठा sun4i_spi *sspi = spi_master_get_devdata(spi->master);
	u32 reg;

	reg = sun4i_spi_पढ़ो(sspi, SUN4I_CTL_REG);

	reg &= ~SUN4I_CTL_CS_MASK;
	reg |= SUN4I_CTL_CS(spi->chip_select);

	/* We want to control the chip select manually */
	reg |= SUN4I_CTL_CS_MANUAL;

	अगर (enable)
		reg |= SUN4I_CTL_CS_LEVEL;
	अन्यथा
		reg &= ~SUN4I_CTL_CS_LEVEL;

	/*
	 * Even though this looks irrelevant since we are supposed to
	 * be controlling the chip select manually, this bit also
	 * controls the levels of the chip select क्रम inactive
	 * devices.
	 *
	 * If we करोn't set it, the chip select level will go low by
	 * शेष when the device is idle, which is not really
	 * expected in the common हाल where the chip select is active
	 * low.
	 */
	अगर (spi->mode & SPI_CS_HIGH)
		reg &= ~SUN4I_CTL_CS_ACTIVE_LOW;
	अन्यथा
		reg |= SUN4I_CTL_CS_ACTIVE_LOW;

	sun4i_spi_ग_लिखो(sspi, SUN4I_CTL_REG, reg);
पूर्ण

अटल माप_प्रकार sun4i_spi_max_transfer_size(काष्ठा spi_device *spi)
अणु
	वापस SUN4I_MAX_XFER_SIZE - 1;
पूर्ण

अटल पूर्णांक sun4i_spi_transfer_one(काष्ठा spi_master *master,
				  काष्ठा spi_device *spi,
				  काष्ठा spi_transfer *tfr)
अणु
	काष्ठा sun4i_spi *sspi = spi_master_get_devdata(master);
	अचिन्हित पूर्णांक mclk_rate, भाग, समयout;
	अचिन्हित पूर्णांक start, end, tx_समय;
	अचिन्हित पूर्णांक tx_len = 0;
	पूर्णांक ret = 0;
	u32 reg;

	/* We करोn't support transfer larger than the FIFO */
	अगर (tfr->len > SUN4I_MAX_XFER_SIZE)
		वापस -EMSGSIZE;

	अगर (tfr->tx_buf && tfr->len >= SUN4I_MAX_XFER_SIZE)
		वापस -EMSGSIZE;

	reinit_completion(&sspi->करोne);
	sspi->tx_buf = tfr->tx_buf;
	sspi->rx_buf = tfr->rx_buf;
	sspi->len = tfr->len;

	/* Clear pending पूर्णांकerrupts */
	sun4i_spi_ग_लिखो(sspi, SUN4I_INT_STA_REG, ~0);


	reg = sun4i_spi_पढ़ो(sspi, SUN4I_CTL_REG);

	/* Reset FIFOs */
	sun4i_spi_ग_लिखो(sspi, SUN4I_CTL_REG,
			reg | SUN4I_CTL_RF_RST | SUN4I_CTL_TF_RST);

	/*
	 * Setup the transfer control रेजिस्टर: Chip Select,
	 * polarities, etc.
	 */
	अगर (spi->mode & SPI_CPOL)
		reg |= SUN4I_CTL_CPOL;
	अन्यथा
		reg &= ~SUN4I_CTL_CPOL;

	अगर (spi->mode & SPI_CPHA)
		reg |= SUN4I_CTL_CPHA;
	अन्यथा
		reg &= ~SUN4I_CTL_CPHA;

	अगर (spi->mode & SPI_LSB_FIRST)
		reg |= SUN4I_CTL_LMTF;
	अन्यथा
		reg &= ~SUN4I_CTL_LMTF;


	/*
	 * If it's a TX only transfer, we don't want to fill the RX
	 * FIFO with bogus data
	 */
	अगर (sspi->rx_buf)
		reg &= ~SUN4I_CTL_DHB;
	अन्यथा
		reg |= SUN4I_CTL_DHB;

	sun4i_spi_ग_लिखो(sspi, SUN4I_CTL_REG, reg);

	/* Ensure that we have a parent घड़ी fast enough */
	mclk_rate = clk_get_rate(sspi->mclk);
	अगर (mclk_rate < (2 * tfr->speed_hz)) अणु
		clk_set_rate(sspi->mclk, 2 * tfr->speed_hz);
		mclk_rate = clk_get_rate(sspi->mclk);
	पूर्ण

	/*
	 * Setup घड़ी भागider.
	 *
	 * We have two choices there. Either we can use the घड़ी
	 * भागide rate 1, which is calculated thanks to this क्रमmula:
	 * SPI_CLK = MOD_CLK / (2 ^ (cdr + 1))
	 * Or we can use CDR2, which is calculated with the क्रमmula:
	 * SPI_CLK = MOD_CLK / (2 * (cdr + 1))
	 * Wether we use the क्रमmer or the latter is set through the
	 * DRS bit.
	 *
	 * First try CDR2, and अगर we can't reach the expected
	 * frequency, fall back to CDR1.
	 */
	भाग = mclk_rate / (2 * tfr->speed_hz);
	अगर (भाग <= (SUN4I_CLK_CTL_CDR2_MASK + 1)) अणु
		अगर (भाग > 0)
			भाग--;

		reg = SUN4I_CLK_CTL_CDR2(भाग) | SUN4I_CLK_CTL_DRS;
	पूर्ण अन्यथा अणु
		भाग = ilog2(mclk_rate) - ilog2(tfr->speed_hz);
		reg = SUN4I_CLK_CTL_CDR1(भाग);
	पूर्ण

	sun4i_spi_ग_लिखो(sspi, SUN4I_CLK_CTL_REG, reg);

	/* Setup the transfer now... */
	अगर (sspi->tx_buf)
		tx_len = tfr->len;

	/* Setup the counters */
	sun4i_spi_ग_लिखो(sspi, SUN4I_BURST_CNT_REG, SUN4I_BURST_CNT(tfr->len));
	sun4i_spi_ग_लिखो(sspi, SUN4I_XMIT_CNT_REG, SUN4I_XMIT_CNT(tx_len));

	/*
	 * Fill the TX FIFO
	 * Filling the FIFO fully causes समयout क्रम some reason
	 * at least on spi2 on A10s
	 */
	sun4i_spi_fill_fअगरo(sspi, SUN4I_FIFO_DEPTH - 1);

	/* Enable the पूर्णांकerrupts */
	sun4i_spi_enable_पूर्णांकerrupt(sspi, SUN4I_INT_CTL_TC |
					 SUN4I_INT_CTL_RF_F34);
	/* Only enable Tx FIFO पूर्णांकerrupt अगर we really need it */
	अगर (tx_len > SUN4I_FIFO_DEPTH)
		sun4i_spi_enable_पूर्णांकerrupt(sspi, SUN4I_INT_CTL_TF_E34);

	/* Start the transfer */
	reg = sun4i_spi_पढ़ो(sspi, SUN4I_CTL_REG);
	sun4i_spi_ग_लिखो(sspi, SUN4I_CTL_REG, reg | SUN4I_CTL_XCH);

	tx_समय = max(tfr->len * 8 * 2 / (tfr->speed_hz / 1000), 100U);
	start = jअगरfies;
	समयout = रुको_क्रम_completion_समयout(&sspi->करोne,
					      msecs_to_jअगरfies(tx_समय));
	end = jअगरfies;
	अगर (!समयout) अणु
		dev_warn(&master->dev,
			 "%s: timeout transferring %u bytes@%iHz for %i(%i)ms",
			 dev_name(&spi->dev), tfr->len, tfr->speed_hz,
			 jअगरfies_to_msecs(end - start), tx_समय);
		ret = -ETIMEDOUT;
		जाओ out;
	पूर्ण


out:
	sun4i_spi_ग_लिखो(sspi, SUN4I_INT_CTL_REG, 0);

	वापस ret;
पूर्ण

अटल irqवापस_t sun4i_spi_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा sun4i_spi *sspi = dev_id;
	u32 status = sun4i_spi_पढ़ो(sspi, SUN4I_INT_STA_REG);

	/* Transfer complete */
	अगर (status & SUN4I_INT_CTL_TC) अणु
		sun4i_spi_ग_लिखो(sspi, SUN4I_INT_STA_REG, SUN4I_INT_CTL_TC);
		sun4i_spi_drain_fअगरo(sspi, SUN4I_FIFO_DEPTH);
		complete(&sspi->करोne);
		वापस IRQ_HANDLED;
	पूर्ण

	/* Receive FIFO 3/4 full */
	अगर (status & SUN4I_INT_CTL_RF_F34) अणु
		sun4i_spi_drain_fअगरo(sspi, SUN4I_FIFO_DEPTH);
		/* Only clear the पूर्णांकerrupt _after_ draining the FIFO */
		sun4i_spi_ग_लिखो(sspi, SUN4I_INT_STA_REG, SUN4I_INT_CTL_RF_F34);
		वापस IRQ_HANDLED;
	पूर्ण

	/* Transmit FIFO 3/4 empty */
	अगर (status & SUN4I_INT_CTL_TF_E34) अणु
		sun4i_spi_fill_fअगरo(sspi, SUN4I_FIFO_DEPTH);

		अगर (!sspi->len)
			/* nothing left to transmit */
			sun4i_spi_disable_पूर्णांकerrupt(sspi, SUN4I_INT_CTL_TF_E34);

		/* Only clear the पूर्णांकerrupt _after_ re-seeding the FIFO */
		sun4i_spi_ग_लिखो(sspi, SUN4I_INT_STA_REG, SUN4I_INT_CTL_TF_E34);

		वापस IRQ_HANDLED;
	पूर्ण

	वापस IRQ_NONE;
पूर्ण

अटल पूर्णांक sun4i_spi_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा spi_master *master = dev_get_drvdata(dev);
	काष्ठा sun4i_spi *sspi = spi_master_get_devdata(master);
	पूर्णांक ret;

	ret = clk_prepare_enable(sspi->hclk);
	अगर (ret) अणु
		dev_err(dev, "Couldn't enable AHB clock\n");
		जाओ out;
	पूर्ण

	ret = clk_prepare_enable(sspi->mclk);
	अगर (ret) अणु
		dev_err(dev, "Couldn't enable module clock\n");
		जाओ err;
	पूर्ण

	sun4i_spi_ग_लिखो(sspi, SUN4I_CTL_REG,
			SUN4I_CTL_ENABLE | SUN4I_CTL_MASTER | SUN4I_CTL_TP);

	वापस 0;

err:
	clk_disable_unprepare(sspi->hclk);
out:
	वापस ret;
पूर्ण

अटल पूर्णांक sun4i_spi_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा spi_master *master = dev_get_drvdata(dev);
	काष्ठा sun4i_spi *sspi = spi_master_get_devdata(master);

	clk_disable_unprepare(sspi->mclk);
	clk_disable_unprepare(sspi->hclk);

	वापस 0;
पूर्ण

अटल पूर्णांक sun4i_spi_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा spi_master *master;
	काष्ठा sun4i_spi *sspi;
	पूर्णांक ret = 0, irq;

	master = spi_alloc_master(&pdev->dev, माप(काष्ठा sun4i_spi));
	अगर (!master) अणु
		dev_err(&pdev->dev, "Unable to allocate SPI Master\n");
		वापस -ENOMEM;
	पूर्ण

	platक्रमm_set_drvdata(pdev, master);
	sspi = spi_master_get_devdata(master);

	sspi->base_addr = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(sspi->base_addr)) अणु
		ret = PTR_ERR(sspi->base_addr);
		जाओ err_मुक्त_master;
	पूर्ण

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0) अणु
		ret = -ENXIO;
		जाओ err_मुक्त_master;
	पूर्ण

	ret = devm_request_irq(&pdev->dev, irq, sun4i_spi_handler,
			       0, "sun4i-spi", sspi);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Cannot request IRQ\n");
		जाओ err_मुक्त_master;
	पूर्ण

	sspi->master = master;
	master->max_speed_hz = 100 * 1000 * 1000;
	master->min_speed_hz = 3 * 1000;
	master->set_cs = sun4i_spi_set_cs;
	master->transfer_one = sun4i_spi_transfer_one;
	master->num_chipselect = 4;
	master->mode_bits = SPI_CPOL | SPI_CPHA | SPI_CS_HIGH | SPI_LSB_FIRST;
	master->bits_per_word_mask = SPI_BPW_MASK(8);
	master->dev.of_node = pdev->dev.of_node;
	master->स्वतः_runसमय_pm = true;
	master->max_transfer_size = sun4i_spi_max_transfer_size;

	sspi->hclk = devm_clk_get(&pdev->dev, "ahb");
	अगर (IS_ERR(sspi->hclk)) अणु
		dev_err(&pdev->dev, "Unable to acquire AHB clock\n");
		ret = PTR_ERR(sspi->hclk);
		जाओ err_मुक्त_master;
	पूर्ण

	sspi->mclk = devm_clk_get(&pdev->dev, "mod");
	अगर (IS_ERR(sspi->mclk)) अणु
		dev_err(&pdev->dev, "Unable to acquire module clock\n");
		ret = PTR_ERR(sspi->mclk);
		जाओ err_मुक्त_master;
	पूर्ण

	init_completion(&sspi->करोne);

	/*
	 * This wake-up/shutकरोwn pattern is to be able to have the
	 * device woken up, even अगर runसमय_pm is disabled
	 */
	ret = sun4i_spi_runसमय_resume(&pdev->dev);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Couldn't resume the device\n");
		जाओ err_मुक्त_master;
	पूर्ण

	pm_runसमय_set_active(&pdev->dev);
	pm_runसमय_enable(&pdev->dev);
	pm_runसमय_idle(&pdev->dev);

	ret = devm_spi_रेजिस्टर_master(&pdev->dev, master);
	अगर (ret) अणु
		dev_err(&pdev->dev, "cannot register SPI master\n");
		जाओ err_pm_disable;
	पूर्ण

	वापस 0;

err_pm_disable:
	pm_runसमय_disable(&pdev->dev);
	sun4i_spi_runसमय_suspend(&pdev->dev);
err_मुक्त_master:
	spi_master_put(master);
	वापस ret;
पूर्ण

अटल पूर्णांक sun4i_spi_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	pm_runसमय_क्रमce_suspend(&pdev->dev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id sun4i_spi_match[] = अणु
	अणु .compatible = "allwinner,sun4i-a10-spi", पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, sun4i_spi_match);

अटल स्थिर काष्ठा dev_pm_ops sun4i_spi_pm_ops = अणु
	.runसमय_resume		= sun4i_spi_runसमय_resume,
	.runसमय_suspend	= sun4i_spi_runसमय_suspend,
पूर्ण;

अटल काष्ठा platक्रमm_driver sun4i_spi_driver = अणु
	.probe	= sun4i_spi_probe,
	.हटाओ	= sun4i_spi_हटाओ,
	.driver	= अणु
		.name		= "sun4i-spi",
		.of_match_table	= sun4i_spi_match,
		.pm		= &sun4i_spi_pm_ops,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(sun4i_spi_driver);

MODULE_AUTHOR("Pan Nan <pannan@allwinnertech.com>");
MODULE_AUTHOR("Maxime Ripard <maxime.ripard@free-electrons.com>");
MODULE_DESCRIPTION("Allwinner A1X/A20 SPI controller driver");
MODULE_LICENSE("GPL");
