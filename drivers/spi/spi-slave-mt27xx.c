<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
// Copyright (c) 2018 MediaTek Inc.

#समावेश <linux/clk.h>
#समावेश <linux/device.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/err.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/spi/spi.h>
#समावेश <linux/of.h>


#घोषणा SPIS_IRQ_EN_REG		0x0
#घोषणा SPIS_IRQ_CLR_REG	0x4
#घोषणा SPIS_IRQ_ST_REG		0x8
#घोषणा SPIS_IRQ_MASK_REG	0xc
#घोषणा SPIS_CFG_REG		0x10
#घोषणा SPIS_RX_DATA_REG	0x14
#घोषणा SPIS_TX_DATA_REG	0x18
#घोषणा SPIS_RX_DST_REG		0x1c
#घोषणा SPIS_TX_SRC_REG		0x20
#घोषणा SPIS_DMA_CFG_REG	0x30
#घोषणा SPIS_SOFT_RST_REG	0x40

/* SPIS_IRQ_EN_REG */
#घोषणा DMA_DONE_EN		BIT(7)
#घोषणा DATA_DONE_EN		BIT(2)
#घोषणा RSTA_DONE_EN		BIT(1)
#घोषणा CMD_INVALID_EN		BIT(0)

/* SPIS_IRQ_ST_REG */
#घोषणा DMA_DONE_ST		BIT(7)
#घोषणा DATA_DONE_ST		BIT(2)
#घोषणा RSTA_DONE_ST		BIT(1)
#घोषणा CMD_INVALID_ST		BIT(0)

/* SPIS_IRQ_MASK_REG */
#घोषणा DMA_DONE_MASK		BIT(7)
#घोषणा DATA_DONE_MASK		BIT(2)
#घोषणा RSTA_DONE_MASK		BIT(1)
#घोषणा CMD_INVALID_MASK	BIT(0)

/* SPIS_CFG_REG */
#घोषणा SPIS_TX_ENDIAN		BIT(7)
#घोषणा SPIS_RX_ENDIAN		BIT(6)
#घोषणा SPIS_TXMSBF		BIT(5)
#घोषणा SPIS_RXMSBF		BIT(4)
#घोषणा SPIS_CPHA		BIT(3)
#घोषणा SPIS_CPOL		BIT(2)
#घोषणा SPIS_TX_EN		BIT(1)
#घोषणा SPIS_RX_EN		BIT(0)

/* SPIS_DMA_CFG_REG */
#घोषणा TX_DMA_TRIG_EN		BIT(31)
#घोषणा TX_DMA_EN		BIT(30)
#घोषणा RX_DMA_EN		BIT(29)
#घोषणा TX_DMA_LEN		0xfffff

/* SPIS_SOFT_RST_REG */
#घोषणा SPIS_DMA_ADDR_EN	BIT(1)
#घोषणा SPIS_SOFT_RST		BIT(0)

काष्ठा mtk_spi_slave अणु
	काष्ठा device *dev;
	व्योम __iomem *base;
	काष्ठा clk *spi_clk;
	काष्ठा completion xfer_करोne;
	काष्ठा spi_transfer *cur_transfer;
	bool slave_पातed;
	स्थिर काष्ठा mtk_spi_compatible *dev_comp;
पूर्ण;

काष्ठा mtk_spi_compatible अणु
	स्थिर u32 max_fअगरo_size;
	bool must_rx;
पूर्ण;

अटल स्थिर काष्ठा mtk_spi_compatible mt2712_compat = अणु
	.max_fअगरo_size = 512,
पूर्ण;
अटल स्थिर काष्ठा mtk_spi_compatible mt8195_compat = अणु
	.max_fअगरo_size = 128,
	.must_rx = true,
पूर्ण;

अटल स्थिर काष्ठा of_device_id mtk_spi_slave_of_match[] = अणु
	अणु .compatible = "mediatek,mt2712-spi-slave",
	  .data = (व्योम *)&mt2712_compat,पूर्ण,
	अणु .compatible = "mediatek,mt8195-spi-slave",
	  .data = (व्योम *)&mt8195_compat,पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, mtk_spi_slave_of_match);

अटल व्योम mtk_spi_slave_disable_dma(काष्ठा mtk_spi_slave *mdata)
अणु
	u32 reg_val;

	reg_val = पढ़ोl(mdata->base + SPIS_DMA_CFG_REG);
	reg_val &= ~RX_DMA_EN;
	reg_val &= ~TX_DMA_EN;
	ग_लिखोl(reg_val, mdata->base + SPIS_DMA_CFG_REG);
पूर्ण

अटल व्योम mtk_spi_slave_disable_xfer(काष्ठा mtk_spi_slave *mdata)
अणु
	u32 reg_val;

	reg_val = पढ़ोl(mdata->base + SPIS_CFG_REG);
	reg_val &= ~SPIS_TX_EN;
	reg_val &= ~SPIS_RX_EN;
	ग_लिखोl(reg_val, mdata->base + SPIS_CFG_REG);
पूर्ण

अटल पूर्णांक mtk_spi_slave_रुको_क्रम_completion(काष्ठा mtk_spi_slave *mdata)
अणु
	अगर (रुको_क्रम_completion_पूर्णांकerruptible(&mdata->xfer_करोne) ||
	    mdata->slave_पातed) अणु
		dev_err(mdata->dev, "interrupted\n");
		वापस -EINTR;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mtk_spi_slave_prepare_message(काष्ठा spi_controller *ctlr,
					 काष्ठा spi_message *msg)
अणु
	काष्ठा mtk_spi_slave *mdata = spi_controller_get_devdata(ctlr);
	काष्ठा spi_device *spi = msg->spi;
	bool cpha, cpol;
	u32 reg_val;

	cpha = spi->mode & SPI_CPHA ? 1 : 0;
	cpol = spi->mode & SPI_CPOL ? 1 : 0;

	reg_val = पढ़ोl(mdata->base + SPIS_CFG_REG);
	अगर (cpha)
		reg_val |= SPIS_CPHA;
	अन्यथा
		reg_val &= ~SPIS_CPHA;
	अगर (cpol)
		reg_val |= SPIS_CPOL;
	अन्यथा
		reg_val &= ~SPIS_CPOL;

	अगर (spi->mode & SPI_LSB_FIRST)
		reg_val &= ~(SPIS_TXMSBF | SPIS_RXMSBF);
	अन्यथा
		reg_val |= SPIS_TXMSBF | SPIS_RXMSBF;

	reg_val &= ~SPIS_TX_ENDIAN;
	reg_val &= ~SPIS_RX_ENDIAN;
	ग_लिखोl(reg_val, mdata->base + SPIS_CFG_REG);

	वापस 0;
पूर्ण

अटल पूर्णांक mtk_spi_slave_fअगरo_transfer(काष्ठा spi_controller *ctlr,
				       काष्ठा spi_device *spi,
				       काष्ठा spi_transfer *xfer)
अणु
	काष्ठा mtk_spi_slave *mdata = spi_controller_get_devdata(ctlr);
	पूर्णांक reg_val, cnt, reमुख्यder, ret;

	ग_लिखोl(SPIS_SOFT_RST, mdata->base + SPIS_SOFT_RST_REG);

	reg_val = पढ़ोl(mdata->base + SPIS_CFG_REG);
	अगर (xfer->rx_buf)
		reg_val |= SPIS_RX_EN;
	अगर (xfer->tx_buf)
		reg_val |= SPIS_TX_EN;
	ग_लिखोl(reg_val, mdata->base + SPIS_CFG_REG);

	cnt = xfer->len / 4;
	अगर (xfer->tx_buf)
		ioग_लिखो32_rep(mdata->base + SPIS_TX_DATA_REG,
			      xfer->tx_buf, cnt);

	reमुख्यder = xfer->len % 4;
	अगर (xfer->tx_buf && reमुख्यder > 0) अणु
		reg_val = 0;
		स_नकल(&reg_val, xfer->tx_buf + cnt * 4, reमुख्यder);
		ग_लिखोl(reg_val, mdata->base + SPIS_TX_DATA_REG);
	पूर्ण

	ret = mtk_spi_slave_रुको_क्रम_completion(mdata);
	अगर (ret) अणु
		mtk_spi_slave_disable_xfer(mdata);
		ग_लिखोl(SPIS_SOFT_RST, mdata->base + SPIS_SOFT_RST_REG);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक mtk_spi_slave_dma_transfer(काष्ठा spi_controller *ctlr,
				      काष्ठा spi_device *spi,
				      काष्ठा spi_transfer *xfer)
अणु
	काष्ठा mtk_spi_slave *mdata = spi_controller_get_devdata(ctlr);
	काष्ठा device *dev = mdata->dev;
	पूर्णांक reg_val, ret;

	ग_लिखोl(SPIS_SOFT_RST, mdata->base + SPIS_SOFT_RST_REG);

	अगर (xfer->tx_buf) अणु
		/* tx_buf is a स्थिर व्योम* where we need a व्योम * क्रम
		 * the dma mapping
		 */
		व्योम *nonस्थिर_tx = (व्योम *)xfer->tx_buf;

		xfer->tx_dma = dma_map_single(dev, nonस्थिर_tx,
					      xfer->len, DMA_TO_DEVICE);
		अगर (dma_mapping_error(dev, xfer->tx_dma)) अणु
			ret = -ENOMEM;
			जाओ disable_transfer;
		पूर्ण
	पूर्ण

	अगर (xfer->rx_buf) अणु
		xfer->rx_dma = dma_map_single(dev, xfer->rx_buf,
					      xfer->len, DMA_FROM_DEVICE);
		अगर (dma_mapping_error(dev, xfer->rx_dma)) अणु
			ret = -ENOMEM;
			जाओ unmap_txdma;
		पूर्ण
	पूर्ण

	ग_लिखोl(xfer->tx_dma, mdata->base + SPIS_TX_SRC_REG);
	ग_लिखोl(xfer->rx_dma, mdata->base + SPIS_RX_DST_REG);

	ग_लिखोl(SPIS_DMA_ADDR_EN, mdata->base + SPIS_SOFT_RST_REG);

	/* enable config reg tx rx_enable */
	reg_val = पढ़ोl(mdata->base + SPIS_CFG_REG);
	अगर (xfer->tx_buf)
		reg_val |= SPIS_TX_EN;
	अगर (xfer->rx_buf)
		reg_val |= SPIS_RX_EN;
	ग_लिखोl(reg_val, mdata->base + SPIS_CFG_REG);

	/* config dma */
	reg_val = 0;
	reg_val |= (xfer->len - 1) & TX_DMA_LEN;
	ग_लिखोl(reg_val, mdata->base + SPIS_DMA_CFG_REG);

	reg_val = पढ़ोl(mdata->base + SPIS_DMA_CFG_REG);
	अगर (xfer->tx_buf)
		reg_val |= TX_DMA_EN;
	अगर (xfer->rx_buf)
		reg_val |= RX_DMA_EN;
	reg_val |= TX_DMA_TRIG_EN;
	ग_लिखोl(reg_val, mdata->base + SPIS_DMA_CFG_REG);

	ret = mtk_spi_slave_रुको_क्रम_completion(mdata);
	अगर (ret)
		जाओ unmap_rxdma;

	वापस 0;

unmap_rxdma:
	अगर (xfer->rx_buf)
		dma_unmap_single(dev, xfer->rx_dma,
				 xfer->len, DMA_FROM_DEVICE);

unmap_txdma:
	अगर (xfer->tx_buf)
		dma_unmap_single(dev, xfer->tx_dma,
				 xfer->len, DMA_TO_DEVICE);

disable_transfer:
	mtk_spi_slave_disable_dma(mdata);
	mtk_spi_slave_disable_xfer(mdata);
	ग_लिखोl(SPIS_SOFT_RST, mdata->base + SPIS_SOFT_RST_REG);

	वापस ret;
पूर्ण

अटल पूर्णांक mtk_spi_slave_transfer_one(काष्ठा spi_controller *ctlr,
				      काष्ठा spi_device *spi,
				      काष्ठा spi_transfer *xfer)
अणु
	काष्ठा mtk_spi_slave *mdata = spi_controller_get_devdata(ctlr);

	reinit_completion(&mdata->xfer_करोne);
	mdata->slave_पातed = false;
	mdata->cur_transfer = xfer;

	अगर (xfer->len > mdata->dev_comp->max_fअगरo_size)
		वापस mtk_spi_slave_dma_transfer(ctlr, spi, xfer);
	अन्यथा
		वापस mtk_spi_slave_fअगरo_transfer(ctlr, spi, xfer);
पूर्ण

अटल पूर्णांक mtk_spi_slave_setup(काष्ठा spi_device *spi)
अणु
	काष्ठा mtk_spi_slave *mdata = spi_controller_get_devdata(spi->master);
	u32 reg_val;

	reg_val = DMA_DONE_EN | DATA_DONE_EN |
		  RSTA_DONE_EN | CMD_INVALID_EN;
	ग_लिखोl(reg_val, mdata->base + SPIS_IRQ_EN_REG);

	reg_val = DMA_DONE_MASK | DATA_DONE_MASK |
		  RSTA_DONE_MASK | CMD_INVALID_MASK;
	ग_लिखोl(reg_val, mdata->base + SPIS_IRQ_MASK_REG);

	mtk_spi_slave_disable_dma(mdata);
	mtk_spi_slave_disable_xfer(mdata);

	वापस 0;
पूर्ण

अटल पूर्णांक mtk_slave_पात(काष्ठा spi_controller *ctlr)
अणु
	काष्ठा mtk_spi_slave *mdata = spi_controller_get_devdata(ctlr);

	mdata->slave_पातed = true;
	complete(&mdata->xfer_करोne);

	वापस 0;
पूर्ण

अटल irqवापस_t mtk_spi_slave_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा spi_controller *ctlr = dev_id;
	काष्ठा mtk_spi_slave *mdata = spi_controller_get_devdata(ctlr);
	काष्ठा spi_transfer *trans = mdata->cur_transfer;
	u32 पूर्णांक_status, reg_val, cnt, reमुख्यder;

	पूर्णांक_status = पढ़ोl(mdata->base + SPIS_IRQ_ST_REG);
	ग_लिखोl(पूर्णांक_status, mdata->base + SPIS_IRQ_CLR_REG);

	अगर (!trans)
		वापस IRQ_NONE;

	अगर ((पूर्णांक_status & DMA_DONE_ST) &&
	    ((पूर्णांक_status & DATA_DONE_ST) ||
	    (पूर्णांक_status & RSTA_DONE_ST))) अणु
		ग_लिखोl(SPIS_SOFT_RST, mdata->base + SPIS_SOFT_RST_REG);

		अगर (trans->tx_buf)
			dma_unmap_single(mdata->dev, trans->tx_dma,
					 trans->len, DMA_TO_DEVICE);
		अगर (trans->rx_buf)
			dma_unmap_single(mdata->dev, trans->rx_dma,
					 trans->len, DMA_FROM_DEVICE);

		mtk_spi_slave_disable_dma(mdata);
		mtk_spi_slave_disable_xfer(mdata);
	पूर्ण

	अगर ((!(पूर्णांक_status & DMA_DONE_ST)) &&
	    ((पूर्णांक_status & DATA_DONE_ST) ||
	    (पूर्णांक_status & RSTA_DONE_ST))) अणु
		cnt = trans->len / 4;
		अगर (trans->rx_buf)
			ioपढ़ो32_rep(mdata->base + SPIS_RX_DATA_REG,
				     trans->rx_buf, cnt);
		reमुख्यder = trans->len % 4;
		अगर (trans->rx_buf && reमुख्यder > 0) अणु
			reg_val = पढ़ोl(mdata->base + SPIS_RX_DATA_REG);
			स_नकल(trans->rx_buf + (cnt * 4),
			       &reg_val, reमुख्यder);
		पूर्ण

		mtk_spi_slave_disable_xfer(mdata);
	पूर्ण

	अगर (पूर्णांक_status & CMD_INVALID_ST) अणु
		dev_warn(&ctlr->dev, "cmd invalid\n");
		वापस IRQ_NONE;
	पूर्ण

	mdata->cur_transfer = शून्य;
	complete(&mdata->xfer_करोne);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक mtk_spi_slave_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा spi_controller *ctlr;
	काष्ठा mtk_spi_slave *mdata;
	पूर्णांक irq, ret;
	स्थिर काष्ठा of_device_id *of_id;

	ctlr = spi_alloc_slave(&pdev->dev, माप(*mdata));
	अगर (!ctlr) अणु
		dev_err(&pdev->dev, "failed to alloc spi slave\n");
		वापस -ENOMEM;
	पूर्ण

	ctlr->स्वतः_runसमय_pm = true;
	ctlr->dev.of_node = pdev->dev.of_node;
	ctlr->mode_bits = SPI_CPOL | SPI_CPHA;
	ctlr->mode_bits |= SPI_LSB_FIRST;

	ctlr->prepare_message = mtk_spi_slave_prepare_message;
	ctlr->transfer_one = mtk_spi_slave_transfer_one;
	ctlr->setup = mtk_spi_slave_setup;
	ctlr->slave_पात = mtk_slave_पात;

	of_id = of_match_node(mtk_spi_slave_of_match, pdev->dev.of_node);
	अगर (!of_id) अणु
		dev_err(&pdev->dev, "failed to probe of_node\n");
		ret = -EINVAL;
		जाओ err_put_ctlr;
	पूर्ण
	mdata = spi_controller_get_devdata(ctlr);
	mdata->dev_comp = of_id->data;

	अगर (mdata->dev_comp->must_rx)
		ctlr->flags = SPI_MASTER_MUST_RX;

	platक्रमm_set_drvdata(pdev, ctlr);

	init_completion(&mdata->xfer_करोne);
	mdata->dev = &pdev->dev;
	mdata->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(mdata->base)) अणु
		ret = PTR_ERR(mdata->base);
		जाओ err_put_ctlr;
	पूर्ण

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0) अणु
		ret = irq;
		जाओ err_put_ctlr;
	पूर्ण

	ret = devm_request_irq(&pdev->dev, irq, mtk_spi_slave_पूर्णांकerrupt,
			       IRQF_TRIGGER_NONE, dev_name(&pdev->dev), ctlr);
	अगर (ret) अणु
		dev_err(&pdev->dev, "failed to register irq (%d)\n", ret);
		जाओ err_put_ctlr;
	पूर्ण

	mdata->spi_clk = devm_clk_get(&pdev->dev, "spi");
	अगर (IS_ERR(mdata->spi_clk)) अणु
		ret = PTR_ERR(mdata->spi_clk);
		dev_err(&pdev->dev, "failed to get spi-clk: %d\n", ret);
		जाओ err_put_ctlr;
	पूर्ण

	ret = clk_prepare_enable(mdata->spi_clk);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "failed to enable spi_clk (%d)\n", ret);
		जाओ err_put_ctlr;
	पूर्ण

	pm_runसमय_enable(&pdev->dev);

	ret = devm_spi_रेजिस्टर_controller(&pdev->dev, ctlr);
	अगर (ret) अणु
		dev_err(&pdev->dev,
			"failed to register slave controller(%d)\n", ret);
		clk_disable_unprepare(mdata->spi_clk);
		जाओ err_disable_runसमय_pm;
	पूर्ण

	clk_disable_unprepare(mdata->spi_clk);

	वापस 0;

err_disable_runसमय_pm:
	pm_runसमय_disable(&pdev->dev);
err_put_ctlr:
	spi_controller_put(ctlr);

	वापस ret;
पूर्ण

अटल पूर्णांक mtk_spi_slave_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	pm_runसमय_disable(&pdev->dev);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक mtk_spi_slave_suspend(काष्ठा device *dev)
अणु
	काष्ठा spi_controller *ctlr = dev_get_drvdata(dev);
	काष्ठा mtk_spi_slave *mdata = spi_controller_get_devdata(ctlr);
	पूर्णांक ret;

	ret = spi_controller_suspend(ctlr);
	अगर (ret)
		वापस ret;

	अगर (!pm_runसमय_suspended(dev))
		clk_disable_unprepare(mdata->spi_clk);

	वापस ret;
पूर्ण

अटल पूर्णांक mtk_spi_slave_resume(काष्ठा device *dev)
अणु
	काष्ठा spi_controller *ctlr = dev_get_drvdata(dev);
	काष्ठा mtk_spi_slave *mdata = spi_controller_get_devdata(ctlr);
	पूर्णांक ret;

	अगर (!pm_runसमय_suspended(dev)) अणु
		ret = clk_prepare_enable(mdata->spi_clk);
		अगर (ret < 0) अणु
			dev_err(dev, "failed to enable spi_clk (%d)\n", ret);
			वापस ret;
		पूर्ण
	पूर्ण

	ret = spi_controller_resume(ctlr);
	अगर (ret < 0)
		clk_disable_unprepare(mdata->spi_clk);

	वापस ret;
पूर्ण
#पूर्ण_अगर /* CONFIG_PM_SLEEP */

#अगर_घोषित CONFIG_PM
अटल पूर्णांक mtk_spi_slave_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा spi_controller *ctlr = dev_get_drvdata(dev);
	काष्ठा mtk_spi_slave *mdata = spi_controller_get_devdata(ctlr);

	clk_disable_unprepare(mdata->spi_clk);

	वापस 0;
पूर्ण

अटल पूर्णांक mtk_spi_slave_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा spi_controller *ctlr = dev_get_drvdata(dev);
	काष्ठा mtk_spi_slave *mdata = spi_controller_get_devdata(ctlr);
	पूर्णांक ret;

	ret = clk_prepare_enable(mdata->spi_clk);
	अगर (ret < 0) अणु
		dev_err(dev, "failed to enable spi_clk (%d)\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_PM */

अटल स्थिर काष्ठा dev_pm_ops mtk_spi_slave_pm = अणु
	SET_SYSTEM_SLEEP_PM_OPS(mtk_spi_slave_suspend, mtk_spi_slave_resume)
	SET_RUNTIME_PM_OPS(mtk_spi_slave_runसमय_suspend,
			   mtk_spi_slave_runसमय_resume, शून्य)
पूर्ण;

अटल काष्ठा platक्रमm_driver mtk_spi_slave_driver = अणु
	.driver = अणु
		.name = "mtk-spi-slave",
		.pm	= &mtk_spi_slave_pm,
		.of_match_table = mtk_spi_slave_of_match,
	पूर्ण,
	.probe = mtk_spi_slave_probe,
	.हटाओ = mtk_spi_slave_हटाओ,
पूर्ण;

module_platक्रमm_driver(mtk_spi_slave_driver);

MODULE_DESCRIPTION("MTK SPI Slave Controller driver");
MODULE_AUTHOR("Leilk Liu <leilk.liu@mediatek.com>");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:mtk-spi-slave");
