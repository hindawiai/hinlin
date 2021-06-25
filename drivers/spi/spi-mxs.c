<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
//
// Freescale MXS SPI master driver
//
// Copyright 2012 DENX Software Engineering, GmbH.
// Copyright 2012 Freescale Semiconductor, Inc.
// Copyright 2008 Embedded Alley Solutions, Inc All Rights Reserved.
//
// Rework and transition to new API by:
// Marek Vasut <marex@denx.de>
//
// Based on previous attempt by:
// Fabio Estevam <fabio.estevam@मुक्तscale.com>
//
// Based on code from U-Boot bootloader by:
// Marek Vasut <marex@denx.de>
//
// Based on spi-sपंचांगp.c, which is:
// Author: Dmitry Pervushin <dimka@embeddedalley.com>

#समावेश <linux/kernel.h>
#समावेश <linux/ioport.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/dmaengine.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/clk.h>
#समावेश <linux/err.h>
#समावेश <linux/completion.h>
#समावेश <linux/pinctrl/consumer.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/module.h>
#समावेश <linux/sपंचांगp_device.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/spi/mxs-spi.h>
#समावेश <trace/events/spi.h>

#घोषणा DRIVER_NAME		"mxs-spi"

/* Use 10S समयout क्रम very दीर्घ transfers, it should suffice. */
#घोषणा SSP_TIMEOUT		10000

#घोषणा SG_MAXLEN		0xff00

/*
 * Flags क्रम txrx functions.  More efficient that using an argument रेजिस्टर क्रम
 * each one.
 */
#घोषणा TXRX_WRITE		(1<<0)	/* This is a ग_लिखो */
#घोषणा TXRX_DEASSERT_CS	(1<<1)	/* De-निश्चित CS at end of txrx */

काष्ठा mxs_spi अणु
	काष्ठा mxs_ssp		ssp;
	काष्ठा completion	c;
	अचिन्हित पूर्णांक		sck;	/* Rate requested (vs actual) */
पूर्ण;

अटल पूर्णांक mxs_spi_setup_transfer(काष्ठा spi_device *dev,
				  स्थिर काष्ठा spi_transfer *t)
अणु
	काष्ठा mxs_spi *spi = spi_master_get_devdata(dev->master);
	काष्ठा mxs_ssp *ssp = &spi->ssp;
	स्थिर अचिन्हित पूर्णांक hz = min(dev->max_speed_hz, t->speed_hz);

	अगर (hz == 0) अणु
		dev_err(&dev->dev, "SPI clock rate of zero not allowed\n");
		वापस -EINVAL;
	पूर्ण

	अगर (hz != spi->sck) अणु
		mxs_ssp_set_clk_rate(ssp, hz);
		/*
		 * Save requested rate, hz, rather than the actual rate,
		 * ssp->clk_rate.  Otherwise we would set the rate every transfer
		 * when the actual rate is not quite the same as requested rate.
		 */
		spi->sck = hz;
		/*
		 * Perhaps we should वापस an error अगर the actual घड़ी is
		 * nowhere बंद to what was requested?
		 */
	पूर्ण

	ग_लिखोl(BM_SSP_CTRL0_LOCK_CS,
		ssp->base + HW_SSP_CTRL0 + STMP_OFFSET_REG_SET);

	ग_लिखोl(BF_SSP_CTRL1_SSP_MODE(BV_SSP_CTRL1_SSP_MODE__SPI) |
	       BF_SSP_CTRL1_WORD_LENGTH(BV_SSP_CTRL1_WORD_LENGTH__EIGHT_BITS) |
	       ((dev->mode & SPI_CPOL) ? BM_SSP_CTRL1_POLARITY : 0) |
	       ((dev->mode & SPI_CPHA) ? BM_SSP_CTRL1_PHASE : 0),
	       ssp->base + HW_SSP_CTRL1(ssp));

	ग_लिखोl(0x0, ssp->base + HW_SSP_CMD0);
	ग_लिखोl(0x0, ssp->base + HW_SSP_CMD1);

	वापस 0;
पूर्ण

अटल u32 mxs_spi_cs_to_reg(अचिन्हित cs)
अणु
	u32 select = 0;

	/*
	 * i.MX28 Datasheet: 17.10.1: HW_SSP_CTRL0
	 *
	 * The bits BM_SSP_CTRL0_WAIT_FOR_CMD and BM_SSP_CTRL0_WAIT_FOR_IRQ
	 * in HW_SSP_CTRL0 रेजिस्टर करो have multiple usage, please refer to
	 * the datasheet क्रम further details. In SPI mode, they are used to
	 * toggle the chip-select lines (nCS pins).
	 */
	अगर (cs & 1)
		select |= BM_SSP_CTRL0_WAIT_FOR_CMD;
	अगर (cs & 2)
		select |= BM_SSP_CTRL0_WAIT_FOR_IRQ;

	वापस select;
पूर्ण

अटल पूर्णांक mxs_ssp_रुको(काष्ठा mxs_spi *spi, पूर्णांक offset, पूर्णांक mask, bool set)
अणु
	स्थिर अचिन्हित दीर्घ समयout = jअगरfies + msecs_to_jअगरfies(SSP_TIMEOUT);
	काष्ठा mxs_ssp *ssp = &spi->ssp;
	u32 reg;

	करो अणु
		reg = पढ़ोl_relaxed(ssp->base + offset);

		अगर (!set)
			reg = ~reg;

		reg &= mask;

		अगर (reg == mask)
			वापस 0;
	पूर्ण जबतक (समय_beक्रमe(jअगरfies, समयout));

	वापस -ETIMEDOUT;
पूर्ण

अटल व्योम mxs_ssp_dma_irq_callback(व्योम *param)
अणु
	काष्ठा mxs_spi *spi = param;

	complete(&spi->c);
पूर्ण

अटल irqवापस_t mxs_ssp_irq_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा mxs_ssp *ssp = dev_id;

	dev_err(ssp->dev, "%s[%i] CTRL1=%08x STATUS=%08x\n",
		__func__, __LINE__,
		पढ़ोl(ssp->base + HW_SSP_CTRL1(ssp)),
		पढ़ोl(ssp->base + HW_SSP_STATUS(ssp)));
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक mxs_spi_txrx_dma(काष्ठा mxs_spi *spi,
			    अचिन्हित अक्षर *buf, पूर्णांक len,
			    अचिन्हित पूर्णांक flags)
अणु
	काष्ठा mxs_ssp *ssp = &spi->ssp;
	काष्ठा dma_async_tx_descriptor *desc = शून्य;
	स्थिर bool vदो_स्मृतिed_buf = is_vदो_स्मृति_addr(buf);
	स्थिर पूर्णांक desc_len = vदो_स्मृतिed_buf ? PAGE_SIZE : SG_MAXLEN;
	स्थिर पूर्णांक sgs = DIV_ROUND_UP(len, desc_len);
	पूर्णांक sg_count;
	पूर्णांक min, ret;
	u32 ctrl0;
	काष्ठा page *vm_page;
	काष्ठा अणु
		u32			pio[4];
		काष्ठा scatterlist	sg;
	पूर्ण *dma_xfer;

	अगर (!len)
		वापस -EINVAL;

	dma_xfer = kसुस्मृति(sgs, माप(*dma_xfer), GFP_KERNEL);
	अगर (!dma_xfer)
		वापस -ENOMEM;

	reinit_completion(&spi->c);

	/* Chip select was alपढ़ोy programmed पूर्णांकo CTRL0 */
	ctrl0 = पढ़ोl(ssp->base + HW_SSP_CTRL0);
	ctrl0 &= ~(BM_SSP_CTRL0_XFER_COUNT | BM_SSP_CTRL0_IGNORE_CRC |
		 BM_SSP_CTRL0_READ);
	ctrl0 |= BM_SSP_CTRL0_DATA_XFER;

	अगर (!(flags & TXRX_WRITE))
		ctrl0 |= BM_SSP_CTRL0_READ;

	/* Queue the DMA data transfer. */
	क्रम (sg_count = 0; sg_count < sgs; sg_count++) अणु
		/* Prepare the transfer descriptor. */
		min = min(len, desc_len);

		/*
		 * De-निश्चित CS on last segment अगर flag is set (i.e., no more
		 * transfers will follow)
		 */
		अगर ((sg_count + 1 == sgs) && (flags & TXRX_DEASSERT_CS))
			ctrl0 |= BM_SSP_CTRL0_IGNORE_CRC;

		अगर (ssp->devid == IMX23_SSP) अणु
			ctrl0 &= ~BM_SSP_CTRL0_XFER_COUNT;
			ctrl0 |= min;
		पूर्ण

		dma_xfer[sg_count].pio[0] = ctrl0;
		dma_xfer[sg_count].pio[3] = min;

		अगर (vदो_स्मृतिed_buf) अणु
			vm_page = vदो_स्मृति_to_page(buf);
			अगर (!vm_page) अणु
				ret = -ENOMEM;
				जाओ err_vदो_स्मृति;
			पूर्ण

			sg_init_table(&dma_xfer[sg_count].sg, 1);
			sg_set_page(&dma_xfer[sg_count].sg, vm_page,
				    min, offset_in_page(buf));
		पूर्ण अन्यथा अणु
			sg_init_one(&dma_xfer[sg_count].sg, buf, min);
		पूर्ण

		ret = dma_map_sg(ssp->dev, &dma_xfer[sg_count].sg, 1,
			(flags & TXRX_WRITE) ? DMA_TO_DEVICE : DMA_FROM_DEVICE);

		len -= min;
		buf += min;

		/* Queue the PIO रेजिस्टर ग_लिखो transfer. */
		desc = dmaengine_prep_slave_sg(ssp->dmach,
				(काष्ठा scatterlist *)dma_xfer[sg_count].pio,
				(ssp->devid == IMX23_SSP) ? 1 : 4,
				DMA_TRANS_NONE,
				sg_count ? DMA_PREP_INTERRUPT : 0);
		अगर (!desc) अणु
			dev_err(ssp->dev,
				"Failed to get PIO reg. write descriptor.\n");
			ret = -EINVAL;
			जाओ err_mapped;
		पूर्ण

		desc = dmaengine_prep_slave_sg(ssp->dmach,
				&dma_xfer[sg_count].sg, 1,
				(flags & TXRX_WRITE) ? DMA_MEM_TO_DEV : DMA_DEV_TO_MEM,
				DMA_PREP_INTERRUPT | DMA_CTRL_ACK);

		अगर (!desc) अणु
			dev_err(ssp->dev,
				"Failed to get DMA data write descriptor.\n");
			ret = -EINVAL;
			जाओ err_mapped;
		पूर्ण
	पूर्ण

	/*
	 * The last descriptor must have this callback,
	 * to finish the DMA transaction.
	 */
	desc->callback = mxs_ssp_dma_irq_callback;
	desc->callback_param = spi;

	/* Start the transfer. */
	dmaengine_submit(desc);
	dma_async_issue_pending(ssp->dmach);

	अगर (!रुको_क्रम_completion_समयout(&spi->c,
					 msecs_to_jअगरfies(SSP_TIMEOUT))) अणु
		dev_err(ssp->dev, "DMA transfer timeout\n");
		ret = -ETIMEDOUT;
		dmaengine_terminate_all(ssp->dmach);
		जाओ err_vदो_स्मृति;
	पूर्ण

	ret = 0;

err_vदो_स्मृति:
	जबतक (--sg_count >= 0) अणु
err_mapped:
		dma_unmap_sg(ssp->dev, &dma_xfer[sg_count].sg, 1,
			(flags & TXRX_WRITE) ? DMA_TO_DEVICE : DMA_FROM_DEVICE);
	पूर्ण

	kमुक्त(dma_xfer);

	वापस ret;
पूर्ण

अटल पूर्णांक mxs_spi_txrx_pio(काष्ठा mxs_spi *spi,
			    अचिन्हित अक्षर *buf, पूर्णांक len,
			    अचिन्हित पूर्णांक flags)
अणु
	काष्ठा mxs_ssp *ssp = &spi->ssp;

	ग_लिखोl(BM_SSP_CTRL0_IGNORE_CRC,
	       ssp->base + HW_SSP_CTRL0 + STMP_OFFSET_REG_CLR);

	जबतक (len--) अणु
		अगर (len == 0 && (flags & TXRX_DEASSERT_CS))
			ग_लिखोl(BM_SSP_CTRL0_IGNORE_CRC,
			       ssp->base + HW_SSP_CTRL0 + STMP_OFFSET_REG_SET);

		अगर (ssp->devid == IMX23_SSP) अणु
			ग_लिखोl(BM_SSP_CTRL0_XFER_COUNT,
				ssp->base + HW_SSP_CTRL0 + STMP_OFFSET_REG_CLR);
			ग_लिखोl(1,
				ssp->base + HW_SSP_CTRL0 + STMP_OFFSET_REG_SET);
		पूर्ण अन्यथा अणु
			ग_लिखोl(1, ssp->base + HW_SSP_XFER_SIZE);
		पूर्ण

		अगर (flags & TXRX_WRITE)
			ग_लिखोl(BM_SSP_CTRL0_READ,
				ssp->base + HW_SSP_CTRL0 + STMP_OFFSET_REG_CLR);
		अन्यथा
			ग_लिखोl(BM_SSP_CTRL0_READ,
				ssp->base + HW_SSP_CTRL0 + STMP_OFFSET_REG_SET);

		ग_लिखोl(BM_SSP_CTRL0_RUN,
				ssp->base + HW_SSP_CTRL0 + STMP_OFFSET_REG_SET);

		अगर (mxs_ssp_रुको(spi, HW_SSP_CTRL0, BM_SSP_CTRL0_RUN, 1))
			वापस -ETIMEDOUT;

		अगर (flags & TXRX_WRITE)
			ग_लिखोl(*buf, ssp->base + HW_SSP_DATA(ssp));

		ग_लिखोl(BM_SSP_CTRL0_DATA_XFER,
			     ssp->base + HW_SSP_CTRL0 + STMP_OFFSET_REG_SET);

		अगर (!(flags & TXRX_WRITE)) अणु
			अगर (mxs_ssp_रुको(spi, HW_SSP_STATUS(ssp),
						BM_SSP_STATUS_FIFO_EMPTY, 0))
				वापस -ETIMEDOUT;

			*buf = (पढ़ोl(ssp->base + HW_SSP_DATA(ssp)) & 0xff);
		पूर्ण

		अगर (mxs_ssp_रुको(spi, HW_SSP_CTRL0, BM_SSP_CTRL0_RUN, 0))
			वापस -ETIMEDOUT;

		buf++;
	पूर्ण

	अगर (len <= 0)
		वापस 0;

	वापस -ETIMEDOUT;
पूर्ण

अटल पूर्णांक mxs_spi_transfer_one(काष्ठा spi_master *master,
				काष्ठा spi_message *m)
अणु
	काष्ठा mxs_spi *spi = spi_master_get_devdata(master);
	काष्ठा mxs_ssp *ssp = &spi->ssp;
	काष्ठा spi_transfer *t;
	अचिन्हित पूर्णांक flag;
	पूर्णांक status = 0;

	/* Program CS रेजिस्टर bits here, it will be used क्रम all transfers. */
	ग_लिखोl(BM_SSP_CTRL0_WAIT_FOR_CMD | BM_SSP_CTRL0_WAIT_FOR_IRQ,
	       ssp->base + HW_SSP_CTRL0 + STMP_OFFSET_REG_CLR);
	ग_लिखोl(mxs_spi_cs_to_reg(m->spi->chip_select),
	       ssp->base + HW_SSP_CTRL0 + STMP_OFFSET_REG_SET);

	list_क्रम_each_entry(t, &m->transfers, transfer_list) अणु

		trace_spi_transfer_start(m, t);

		status = mxs_spi_setup_transfer(m->spi, t);
		अगर (status)
			अवरोध;

		/* De-निश्चित on last transfer, inverted by cs_change flag */
		flag = (&t->transfer_list == m->transfers.prev) ^ t->cs_change ?
		       TXRX_DEASSERT_CS : 0;

		/*
		 * Small blocks can be transfered via PIO.
		 * Measured by empiric means:
		 *
		 * dd अगर=/dev/mtdblock0 of=/dev/null bs=1024k count=1
		 *
		 * DMA only: 2.164808 seconds, 473.0KB/s
		 * Combined: 1.676276 seconds, 610.9KB/s
		 */
		अगर (t->len < 32) अणु
			ग_लिखोl(BM_SSP_CTRL1_DMA_ENABLE,
				ssp->base + HW_SSP_CTRL1(ssp) +
				STMP_OFFSET_REG_CLR);

			अगर (t->tx_buf)
				status = mxs_spi_txrx_pio(spi,
						(व्योम *)t->tx_buf,
						t->len, flag | TXRX_WRITE);
			अगर (t->rx_buf)
				status = mxs_spi_txrx_pio(spi,
						t->rx_buf, t->len,
						flag);
		पूर्ण अन्यथा अणु
			ग_लिखोl(BM_SSP_CTRL1_DMA_ENABLE,
				ssp->base + HW_SSP_CTRL1(ssp) +
				STMP_OFFSET_REG_SET);

			अगर (t->tx_buf)
				status = mxs_spi_txrx_dma(spi,
						(व्योम *)t->tx_buf, t->len,
						flag | TXRX_WRITE);
			अगर (t->rx_buf)
				status = mxs_spi_txrx_dma(spi,
						t->rx_buf, t->len,
						flag);
		पूर्ण

		trace_spi_transfer_stop(m, t);

		अगर (status) अणु
			sपंचांगp_reset_block(ssp->base);
			अवरोध;
		पूर्ण

		m->actual_length += t->len;
	पूर्ण

	m->status = status;
	spi_finalize_current_message(master);

	वापस status;
पूर्ण

अटल पूर्णांक mxs_spi_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा spi_master *master = dev_get_drvdata(dev);
	काष्ठा mxs_spi *spi = spi_master_get_devdata(master);
	काष्ठा mxs_ssp *ssp = &spi->ssp;
	पूर्णांक ret;

	clk_disable_unprepare(ssp->clk);

	ret = pinctrl_pm_select_idle_state(dev);
	अगर (ret) अणु
		पूर्णांक ret2 = clk_prepare_enable(ssp->clk);

		अगर (ret2)
			dev_warn(dev, "Failed to reenable clock after failing pinctrl request (pinctrl: %d, clk: %d)\n",
				 ret, ret2);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक mxs_spi_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा spi_master *master = dev_get_drvdata(dev);
	काष्ठा mxs_spi *spi = spi_master_get_devdata(master);
	काष्ठा mxs_ssp *ssp = &spi->ssp;
	पूर्णांक ret;

	ret = pinctrl_pm_select_शेष_state(dev);
	अगर (ret)
		वापस ret;

	ret = clk_prepare_enable(ssp->clk);
	अगर (ret)
		pinctrl_pm_select_idle_state(dev);

	वापस ret;
पूर्ण

अटल पूर्णांक __maybe_unused mxs_spi_suspend(काष्ठा device *dev)
अणु
	काष्ठा spi_master *master = dev_get_drvdata(dev);
	पूर्णांक ret;

	ret = spi_master_suspend(master);
	अगर (ret)
		वापस ret;

	अगर (!pm_runसमय_suspended(dev))
		वापस mxs_spi_runसमय_suspend(dev);
	अन्यथा
		वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused mxs_spi_resume(काष्ठा device *dev)
अणु
	काष्ठा spi_master *master = dev_get_drvdata(dev);
	पूर्णांक ret;

	अगर (!pm_runसमय_suspended(dev))
		ret = mxs_spi_runसमय_resume(dev);
	अन्यथा
		ret = 0;
	अगर (ret)
		वापस ret;

	ret = spi_master_resume(master);
	अगर (ret < 0 && !pm_runसमय_suspended(dev))
		mxs_spi_runसमय_suspend(dev);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops mxs_spi_pm = अणु
	SET_RUNTIME_PM_OPS(mxs_spi_runसमय_suspend,
			   mxs_spi_runसमय_resume, शून्य)
	SET_SYSTEM_SLEEP_PM_OPS(mxs_spi_suspend, mxs_spi_resume)
पूर्ण;

अटल स्थिर काष्ठा of_device_id mxs_spi_dt_ids[] = अणु
	अणु .compatible = "fsl,imx23-spi", .data = (व्योम *) IMX23_SSP, पूर्ण,
	अणु .compatible = "fsl,imx28-spi", .data = (व्योम *) IMX28_SSP, पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, mxs_spi_dt_ids);

अटल पूर्णांक mxs_spi_probe(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा of_device_id *of_id =
			of_match_device(mxs_spi_dt_ids, &pdev->dev);
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा spi_master *master;
	काष्ठा mxs_spi *spi;
	काष्ठा mxs_ssp *ssp;
	काष्ठा clk *clk;
	व्योम __iomem *base;
	पूर्णांक devid, clk_freq;
	पूर्णांक ret = 0, irq_err;

	/*
	 * Default घड़ी speed क्रम the SPI core. 160MHz seems to
	 * work reasonably well with most SPI flashes, so use this
	 * as a शेष. Override with "clock-frequency" DT prop.
	 */
	स्थिर पूर्णांक clk_freq_शेष = 160000000;

	irq_err = platक्रमm_get_irq(pdev, 0);
	अगर (irq_err < 0)
		वापस irq_err;

	base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(base))
		वापस PTR_ERR(base);

	clk = devm_clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(clk))
		वापस PTR_ERR(clk);

	devid = (क्रमागत mxs_ssp_id) of_id->data;
	ret = of_property_पढ़ो_u32(np, "clock-frequency",
				   &clk_freq);
	अगर (ret)
		clk_freq = clk_freq_शेष;

	master = spi_alloc_master(&pdev->dev, माप(*spi));
	अगर (!master)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, master);

	master->transfer_one_message = mxs_spi_transfer_one;
	master->bits_per_word_mask = SPI_BPW_MASK(8);
	master->mode_bits = SPI_CPOL | SPI_CPHA;
	master->num_chipselect = 3;
	master->dev.of_node = np;
	master->flags = SPI_MASTER_HALF_DUPLEX;
	master->स्वतः_runसमय_pm = true;

	spi = spi_master_get_devdata(master);
	ssp = &spi->ssp;
	ssp->dev = &pdev->dev;
	ssp->clk = clk;
	ssp->base = base;
	ssp->devid = devid;

	init_completion(&spi->c);

	ret = devm_request_irq(&pdev->dev, irq_err, mxs_ssp_irq_handler, 0,
			       dev_name(&pdev->dev), ssp);
	अगर (ret)
		जाओ out_master_मुक्त;

	ssp->dmach = dma_request_chan(&pdev->dev, "rx-tx");
	अगर (IS_ERR(ssp->dmach)) अणु
		dev_err(ssp->dev, "Failed to request DMA\n");
		ret = PTR_ERR(ssp->dmach);
		जाओ out_master_मुक्त;
	पूर्ण

	pm_runसमय_enable(ssp->dev);
	अगर (!pm_runसमय_enabled(ssp->dev)) अणु
		ret = mxs_spi_runसमय_resume(ssp->dev);
		अगर (ret < 0) अणु
			dev_err(ssp->dev, "runtime resume failed\n");
			जाओ out_dma_release;
		पूर्ण
	पूर्ण

	ret = pm_runसमय_get_sync(ssp->dev);
	अगर (ret < 0) अणु
		pm_runसमय_put_noidle(ssp->dev);
		dev_err(ssp->dev, "runtime_get_sync failed\n");
		जाओ out_pm_runसमय_disable;
	पूर्ण

	clk_set_rate(ssp->clk, clk_freq);

	ret = sपंचांगp_reset_block(ssp->base);
	अगर (ret)
		जाओ out_pm_runसमय_put;

	ret = devm_spi_रेजिस्टर_master(&pdev->dev, master);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Cannot register SPI master, %d\n", ret);
		जाओ out_pm_runसमय_put;
	पूर्ण

	pm_runसमय_put(ssp->dev);

	वापस 0;

out_pm_runसमय_put:
	pm_runसमय_put(ssp->dev);
out_pm_runसमय_disable:
	pm_runसमय_disable(ssp->dev);
out_dma_release:
	dma_release_channel(ssp->dmach);
out_master_मुक्त:
	spi_master_put(master);
	वापस ret;
पूर्ण

अटल पूर्णांक mxs_spi_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा spi_master *master;
	काष्ठा mxs_spi *spi;
	काष्ठा mxs_ssp *ssp;

	master = platक्रमm_get_drvdata(pdev);
	spi = spi_master_get_devdata(master);
	ssp = &spi->ssp;

	pm_runसमय_disable(&pdev->dev);
	अगर (!pm_runसमय_status_suspended(&pdev->dev))
		mxs_spi_runसमय_suspend(&pdev->dev);

	dma_release_channel(ssp->dmach);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver mxs_spi_driver = अणु
	.probe	= mxs_spi_probe,
	.हटाओ	= mxs_spi_हटाओ,
	.driver	= अणु
		.name	= DRIVER_NAME,
		.of_match_table = mxs_spi_dt_ids,
		.pm = &mxs_spi_pm,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(mxs_spi_driver);

MODULE_AUTHOR("Marek Vasut <marex@denx.de>");
MODULE_DESCRIPTION("MXS SPI master driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:mxs-spi");
