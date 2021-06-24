<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Driver क्रम AT91 USART Controllers as SPI
//
// Copyright (C) 2018 Microchip Technology Inc.
//
// Author: Radu Pirea <radu.pirea@microchip.com>

#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/dmaengine.h>
#समावेश <linux/dma-direction.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/of_gpपन.स>
#समावेश <linux/pinctrl/consumer.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>

#समावेश <linux/spi/spi.h>

#घोषणा US_CR			0x00
#घोषणा US_MR			0x04
#घोषणा US_IER			0x08
#घोषणा US_IDR			0x0C
#घोषणा US_CSR			0x14
#घोषणा US_RHR			0x18
#घोषणा US_THR			0x1C
#घोषणा US_BRGR			0x20
#घोषणा US_VERSION		0xFC

#घोषणा US_CR_RSTRX		BIT(2)
#घोषणा US_CR_RSTTX		BIT(3)
#घोषणा US_CR_RXEN		BIT(4)
#घोषणा US_CR_RXDIS		BIT(5)
#घोषणा US_CR_TXEN		BIT(6)
#घोषणा US_CR_TXDIS		BIT(7)

#घोषणा US_MR_SPI_MASTER	0x0E
#घोषणा US_MR_CHRL		GENMASK(7, 6)
#घोषणा US_MR_CPHA		BIT(8)
#घोषणा US_MR_CPOL		BIT(16)
#घोषणा US_MR_CLKO		BIT(18)
#घोषणा US_MR_WRDBT		BIT(20)
#घोषणा US_MR_LOOP		BIT(15)

#घोषणा US_IR_RXRDY		BIT(0)
#घोषणा US_IR_TXRDY		BIT(1)
#घोषणा US_IR_OVRE		BIT(5)

#घोषणा US_BRGR_SIZE		BIT(16)

#घोषणा US_MIN_CLK_DIV		0x06
#घोषणा US_MAX_CLK_DIV		BIT(16)

#घोषणा US_RESET		(US_CR_RSTRX | US_CR_RSTTX)
#घोषणा US_DISABLE		(US_CR_RXDIS | US_CR_TXDIS)
#घोषणा US_ENABLE		(US_CR_RXEN | US_CR_TXEN)
#घोषणा US_OVRE_RXRDY_IRQS	(US_IR_OVRE | US_IR_RXRDY)

#घोषणा US_INIT \
	(US_MR_SPI_MASTER | US_MR_CHRL | US_MR_CLKO | US_MR_WRDBT)
#घोषणा US_DMA_MIN_BYTES       16
#घोषणा US_DMA_TIMEOUT         (msecs_to_jअगरfies(1000))

/* Register access macros */
#घोषणा at91_usart_spi_पढ़ोl(port, reg) \
	पढ़ोl_relaxed((port)->regs + US_##reg)
#घोषणा at91_usart_spi_ग_लिखोl(port, reg, value) \
	ग_लिखोl_relaxed((value), (port)->regs + US_##reg)

#घोषणा at91_usart_spi_पढ़ोb(port, reg) \
	पढ़ोb_relaxed((port)->regs + US_##reg)
#घोषणा at91_usart_spi_ग_लिखोb(port, reg, value) \
	ग_लिखोb_relaxed((value), (port)->regs + US_##reg)

काष्ठा at91_usart_spi अणु
	काष्ठा platक्रमm_device  *mpdev;
	काष्ठा spi_transfer	*current_transfer;
	व्योम __iomem		*regs;
	काष्ठा device		*dev;
	काष्ठा clk		*clk;

	काष्ठा completion	xfer_completion;

	/*used in पूर्णांकerrupt to protect data पढ़ोing*/
	spinlock_t		lock;

	phys_addr_t		phybase;

	पूर्णांक			irq;
	अचिन्हित पूर्णांक		current_tx_reमुख्यing_bytes;
	अचिन्हित पूर्णांक		current_rx_reमुख्यing_bytes;

	u32			spi_clk;
	u32			status;

	bool			xfer_failed;
	bool			use_dma;
पूर्ण;

अटल व्योम dma_callback(व्योम *data)
अणु
	काष्ठा spi_controller   *ctlr = data;
	काष्ठा at91_usart_spi   *aus = spi_master_get_devdata(ctlr);

	at91_usart_spi_ग_लिखोl(aus, IER, US_IR_RXRDY);
	aus->current_rx_reमुख्यing_bytes = 0;
	complete(&aus->xfer_completion);
पूर्ण

अटल bool at91_usart_spi_can_dma(काष्ठा spi_controller *ctrl,
				   काष्ठा spi_device *spi,
				   काष्ठा spi_transfer *xfer)
अणु
	काष्ठा at91_usart_spi *aus = spi_master_get_devdata(ctrl);

	वापस aus->use_dma && xfer->len >= US_DMA_MIN_BYTES;
पूर्ण

अटल पूर्णांक at91_usart_spi_configure_dma(काष्ठा spi_controller *ctlr,
					काष्ठा at91_usart_spi *aus)
अणु
	काष्ठा dma_slave_config slave_config;
	काष्ठा device *dev = &aus->mpdev->dev;
	phys_addr_t phybase = aus->phybase;
	dma_cap_mask_t mask;
	पूर्णांक err = 0;

	dma_cap_zero(mask);
	dma_cap_set(DMA_SLAVE, mask);

	ctlr->dma_tx = dma_request_chan(dev, "tx");
	अगर (IS_ERR_OR_शून्य(ctlr->dma_tx)) अणु
		अगर (IS_ERR(ctlr->dma_tx)) अणु
			err = PTR_ERR(ctlr->dma_tx);
			जाओ at91_usart_spi_error_clear;
		पूर्ण

		dev_dbg(dev,
			"DMA TX channel not available, SPI unable to use DMA\n");
		err = -EBUSY;
		जाओ at91_usart_spi_error_clear;
	पूर्ण

	ctlr->dma_rx = dma_request_chan(dev, "rx");
	अगर (IS_ERR_OR_शून्य(ctlr->dma_rx)) अणु
		अगर (IS_ERR(ctlr->dma_rx)) अणु
			err = PTR_ERR(ctlr->dma_rx);
			जाओ at91_usart_spi_error;
		पूर्ण

		dev_dbg(dev,
			"DMA RX channel not available, SPI unable to use DMA\n");
		err = -EBUSY;
		जाओ at91_usart_spi_error;
	पूर्ण

	slave_config.dst_addr_width = DMA_SLAVE_BUSWIDTH_1_BYTE;
	slave_config.src_addr_width = DMA_SLAVE_BUSWIDTH_1_BYTE;
	slave_config.dst_addr = (dma_addr_t)phybase + US_THR;
	slave_config.src_addr = (dma_addr_t)phybase + US_RHR;
	slave_config.src_maxburst = 1;
	slave_config.dst_maxburst = 1;
	slave_config.device_fc = false;

	slave_config.direction = DMA_DEV_TO_MEM;
	अगर (dmaengine_slave_config(ctlr->dma_rx, &slave_config)) अणु
		dev_err(&ctlr->dev,
			"failed to configure rx dma channel\n");
		err = -EINVAL;
		जाओ at91_usart_spi_error;
	पूर्ण

	slave_config.direction = DMA_MEM_TO_DEV;
	अगर (dmaengine_slave_config(ctlr->dma_tx, &slave_config)) अणु
		dev_err(&ctlr->dev,
			"failed to configure tx dma channel\n");
		err = -EINVAL;
		जाओ at91_usart_spi_error;
	पूर्ण

	aus->use_dma = true;
	वापस 0;

at91_usart_spi_error:
	अगर (!IS_ERR_OR_शून्य(ctlr->dma_tx))
		dma_release_channel(ctlr->dma_tx);
	अगर (!IS_ERR_OR_शून्य(ctlr->dma_rx))
		dma_release_channel(ctlr->dma_rx);
	ctlr->dma_tx = शून्य;
	ctlr->dma_rx = शून्य;

at91_usart_spi_error_clear:
	वापस err;
पूर्ण

अटल व्योम at91_usart_spi_release_dma(काष्ठा spi_controller *ctlr)
अणु
	अगर (ctlr->dma_rx)
		dma_release_channel(ctlr->dma_rx);
	अगर (ctlr->dma_tx)
		dma_release_channel(ctlr->dma_tx);
पूर्ण

अटल व्योम at91_usart_spi_stop_dma(काष्ठा spi_controller *ctlr)
अणु
	अगर (ctlr->dma_rx)
		dmaengine_terminate_all(ctlr->dma_rx);
	अगर (ctlr->dma_tx)
		dmaengine_terminate_all(ctlr->dma_tx);
पूर्ण

अटल पूर्णांक at91_usart_spi_dma_transfer(काष्ठा spi_controller *ctlr,
				       काष्ठा spi_transfer *xfer)
अणु
	काष्ठा at91_usart_spi *aus = spi_master_get_devdata(ctlr);
	काष्ठा dma_chan	 *rxchan = ctlr->dma_rx;
	काष्ठा dma_chan *txchan = ctlr->dma_tx;
	काष्ठा dma_async_tx_descriptor *rxdesc;
	काष्ठा dma_async_tx_descriptor *txdesc;
	dma_cookie_t cookie;

	/* Disable RX पूर्णांकerrupt */
	at91_usart_spi_ग_लिखोl(aus, IDR, US_IR_RXRDY);

	rxdesc = dmaengine_prep_slave_sg(rxchan,
					 xfer->rx_sg.sgl,
					 xfer->rx_sg.nents,
					 DMA_DEV_TO_MEM,
					 DMA_PREP_INTERRUPT |
					 DMA_CTRL_ACK);
	अगर (!rxdesc)
		जाओ at91_usart_spi_err_dma;

	txdesc = dmaengine_prep_slave_sg(txchan,
					 xfer->tx_sg.sgl,
					 xfer->tx_sg.nents,
					 DMA_MEM_TO_DEV,
					 DMA_PREP_INTERRUPT |
					 DMA_CTRL_ACK);
	अगर (!txdesc)
		जाओ at91_usart_spi_err_dma;

	rxdesc->callback = dma_callback;
	rxdesc->callback_param = ctlr;

	cookie = rxdesc->tx_submit(rxdesc);
	अगर (dma_submit_error(cookie))
		जाओ at91_usart_spi_err_dma;

	cookie = txdesc->tx_submit(txdesc);
	अगर (dma_submit_error(cookie))
		जाओ at91_usart_spi_err_dma;

	rxchan->device->device_issue_pending(rxchan);
	txchan->device->device_issue_pending(txchan);

	वापस 0;

at91_usart_spi_err_dma:
	/* Enable RX पूर्णांकerrupt अगर something fails and fallback to PIO */
	at91_usart_spi_ग_लिखोl(aus, IER, US_IR_RXRDY);
	at91_usart_spi_stop_dma(ctlr);

	वापस -ENOMEM;
पूर्ण

अटल अचिन्हित दीर्घ at91_usart_spi_dma_समयout(काष्ठा at91_usart_spi *aus)
अणु
	वापस रुको_क्रम_completion_समयout(&aus->xfer_completion,
					   US_DMA_TIMEOUT);
पूर्ण

अटल अंतरभूत u32 at91_usart_spi_tx_पढ़ोy(काष्ठा at91_usart_spi *aus)
अणु
	वापस aus->status & US_IR_TXRDY;
पूर्ण

अटल अंतरभूत u32 at91_usart_spi_rx_पढ़ोy(काष्ठा at91_usart_spi *aus)
अणु
	वापस aus->status & US_IR_RXRDY;
पूर्ण

अटल अंतरभूत u32 at91_usart_spi_check_overrun(काष्ठा at91_usart_spi *aus)
अणु
	वापस aus->status & US_IR_OVRE;
पूर्ण

अटल अंतरभूत u32 at91_usart_spi_पढ़ो_status(काष्ठा at91_usart_spi *aus)
अणु
	aus->status = at91_usart_spi_पढ़ोl(aus, CSR);
	वापस aus->status;
पूर्ण

अटल अंतरभूत व्योम at91_usart_spi_tx(काष्ठा at91_usart_spi *aus)
अणु
	अचिन्हित पूर्णांक len = aus->current_transfer->len;
	अचिन्हित पूर्णांक reमुख्यing = aus->current_tx_reमुख्यing_bytes;
	स्थिर u8  *tx_buf = aus->current_transfer->tx_buf;

	अगर (!reमुख्यing)
		वापस;

	अगर (at91_usart_spi_tx_पढ़ोy(aus)) अणु
		at91_usart_spi_ग_लिखोb(aus, THR, tx_buf[len - reमुख्यing]);
		aus->current_tx_reमुख्यing_bytes--;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम at91_usart_spi_rx(काष्ठा at91_usart_spi *aus)
अणु
	पूर्णांक len = aus->current_transfer->len;
	पूर्णांक reमुख्यing = aus->current_rx_reमुख्यing_bytes;
	u8  *rx_buf = aus->current_transfer->rx_buf;

	अगर (!reमुख्यing)
		वापस;

	rx_buf[len - reमुख्यing] = at91_usart_spi_पढ़ोb(aus, RHR);
	aus->current_rx_reमुख्यing_bytes--;
पूर्ण

अटल अंतरभूत व्योम
at91_usart_spi_set_xfer_speed(काष्ठा at91_usart_spi *aus,
			      काष्ठा spi_transfer *xfer)
अणु
	at91_usart_spi_ग_लिखोl(aus, BRGR,
			      DIV_ROUND_UP(aus->spi_clk, xfer->speed_hz));
पूर्ण

अटल irqवापस_t at91_usart_spi_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा spi_controller *controller = dev_id;
	काष्ठा at91_usart_spi *aus = spi_master_get_devdata(controller);

	spin_lock(&aus->lock);
	at91_usart_spi_पढ़ो_status(aus);

	अगर (at91_usart_spi_check_overrun(aus)) अणु
		aus->xfer_failed = true;
		at91_usart_spi_ग_लिखोl(aus, IDR, US_IR_OVRE | US_IR_RXRDY);
		spin_unlock(&aus->lock);
		वापस IRQ_HANDLED;
	पूर्ण

	अगर (at91_usart_spi_rx_पढ़ोy(aus)) अणु
		at91_usart_spi_rx(aus);
		spin_unlock(&aus->lock);
		वापस IRQ_HANDLED;
	पूर्ण

	spin_unlock(&aus->lock);

	वापस IRQ_NONE;
पूर्ण

अटल पूर्णांक at91_usart_spi_setup(काष्ठा spi_device *spi)
अणु
	काष्ठा at91_usart_spi *aus = spi_master_get_devdata(spi->controller);
	u32 *ausd = spi->controller_state;
	अचिन्हित पूर्णांक mr = at91_usart_spi_पढ़ोl(aus, MR);

	अगर (spi->mode & SPI_CPOL)
		mr |= US_MR_CPOL;
	अन्यथा
		mr &= ~US_MR_CPOL;

	अगर (spi->mode & SPI_CPHA)
		mr |= US_MR_CPHA;
	अन्यथा
		mr &= ~US_MR_CPHA;

	अगर (spi->mode & SPI_LOOP)
		mr |= US_MR_LOOP;
	अन्यथा
		mr &= ~US_MR_LOOP;

	अगर (!ausd) अणु
		ausd = kzalloc(माप(*ausd), GFP_KERNEL);
		अगर (!ausd)
			वापस -ENOMEM;

		spi->controller_state = ausd;
	पूर्ण

	*ausd = mr;

	dev_dbg(&spi->dev,
		"setup: bpw %u mode 0x%x -> mr %d %08x\n",
		spi->bits_per_word, spi->mode, spi->chip_select, mr);

	वापस 0;
पूर्ण

अटल पूर्णांक at91_usart_spi_transfer_one(काष्ठा spi_controller *ctlr,
				       काष्ठा spi_device *spi,
				       काष्ठा spi_transfer *xfer)
अणु
	काष्ठा at91_usart_spi *aus = spi_master_get_devdata(ctlr);
	अचिन्हित दीर्घ dma_समयout = 0;
	पूर्णांक ret = 0;

	at91_usart_spi_set_xfer_speed(aus, xfer);
	aus->xfer_failed = false;
	aus->current_transfer = xfer;
	aus->current_tx_reमुख्यing_bytes = xfer->len;
	aus->current_rx_reमुख्यing_bytes = xfer->len;

	जबतक ((aus->current_tx_reमुख्यing_bytes ||
		aus->current_rx_reमुख्यing_bytes) && !aus->xfer_failed) अणु
		reinit_completion(&aus->xfer_completion);
		अगर (at91_usart_spi_can_dma(ctlr, spi, xfer) &&
		    !ret) अणु
			ret = at91_usart_spi_dma_transfer(ctlr, xfer);
			अगर (ret)
				जारी;

			dma_समयout = at91_usart_spi_dma_समयout(aus);

			अगर (WARN_ON(dma_समयout == 0)) अणु
				dev_err(&spi->dev, "DMA transfer timeout\n");
				वापस -EIO;
			पूर्ण
			aus->current_tx_reमुख्यing_bytes = 0;
		पूर्ण अन्यथा अणु
			at91_usart_spi_पढ़ो_status(aus);
			at91_usart_spi_tx(aus);
		पूर्ण

		cpu_relax();
	पूर्ण

	अगर (aus->xfer_failed) अणु
		dev_err(aus->dev, "Overrun!\n");
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक at91_usart_spi_prepare_message(काष्ठा spi_controller *ctlr,
					  काष्ठा spi_message *message)
अणु
	काष्ठा at91_usart_spi *aus = spi_master_get_devdata(ctlr);
	काष्ठा spi_device *spi = message->spi;
	u32 *ausd = spi->controller_state;

	at91_usart_spi_ग_लिखोl(aus, CR, US_ENABLE);
	at91_usart_spi_ग_लिखोl(aus, IER, US_OVRE_RXRDY_IRQS);
	at91_usart_spi_ग_लिखोl(aus, MR, *ausd);

	वापस 0;
पूर्ण

अटल पूर्णांक at91_usart_spi_unprepare_message(काष्ठा spi_controller *ctlr,
					    काष्ठा spi_message *message)
अणु
	काष्ठा at91_usart_spi *aus = spi_master_get_devdata(ctlr);

	at91_usart_spi_ग_लिखोl(aus, CR, US_RESET | US_DISABLE);
	at91_usart_spi_ग_लिखोl(aus, IDR, US_OVRE_RXRDY_IRQS);

	वापस 0;
पूर्ण

अटल व्योम at91_usart_spi_cleanup(काष्ठा spi_device *spi)
अणु
	काष्ठा at91_usart_spi_device *ausd = spi->controller_state;

	spi->controller_state = शून्य;
	kमुक्त(ausd);
पूर्ण

अटल व्योम at91_usart_spi_init(काष्ठा at91_usart_spi *aus)
अणु
	at91_usart_spi_ग_लिखोl(aus, MR, US_INIT);
	at91_usart_spi_ग_लिखोl(aus, CR, US_RESET | US_DISABLE);
पूर्ण

अटल पूर्णांक at91_usart_gpio_setup(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *np = pdev->dev.parent->of_node;
	पूर्णांक i;
	पूर्णांक ret;
	पूर्णांक nb;

	अगर (!np)
		वापस -EINVAL;

	nb = of_gpio_named_count(np, "cs-gpios");
	क्रम (i = 0; i < nb; i++) अणु
		पूर्णांक cs_gpio = of_get_named_gpio(np, "cs-gpios", i);

		अगर (cs_gpio < 0)
			वापस cs_gpio;

		अगर (gpio_is_valid(cs_gpio)) अणु
			ret = devm_gpio_request_one(&pdev->dev, cs_gpio,
						    GPIOF_सूची_OUT,
						    dev_name(&pdev->dev));
			अगर (ret)
				वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक at91_usart_spi_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा resource *regs;
	काष्ठा spi_controller *controller;
	काष्ठा at91_usart_spi *aus;
	काष्ठा clk *clk;
	पूर्णांक irq;
	पूर्णांक ret;

	regs = platक्रमm_get_resource(to_platक्रमm_device(pdev->dev.parent),
				     IORESOURCE_MEM, 0);
	अगर (!regs)
		वापस -EINVAL;

	irq = platक्रमm_get_irq(to_platक्रमm_device(pdev->dev.parent), 0);
	अगर (irq < 0)
		वापस irq;

	clk = devm_clk_get(pdev->dev.parent, "usart");
	अगर (IS_ERR(clk))
		वापस PTR_ERR(clk);

	ret = -ENOMEM;
	controller = spi_alloc_master(&pdev->dev, माप(*aus));
	अगर (!controller)
		जाओ at91_usart_spi_probe_fail;

	ret = at91_usart_gpio_setup(pdev);
	अगर (ret)
		जाओ at91_usart_spi_probe_fail;

	controller->mode_bits = SPI_CPOL | SPI_CPHA | SPI_LOOP | SPI_CS_HIGH;
	controller->dev.of_node = pdev->dev.parent->of_node;
	controller->bits_per_word_mask = SPI_BPW_MASK(8);
	controller->setup = at91_usart_spi_setup;
	controller->flags = SPI_MASTER_MUST_RX | SPI_MASTER_MUST_TX;
	controller->transfer_one = at91_usart_spi_transfer_one;
	controller->prepare_message = at91_usart_spi_prepare_message;
	controller->unprepare_message = at91_usart_spi_unprepare_message;
	controller->can_dma = at91_usart_spi_can_dma;
	controller->cleanup = at91_usart_spi_cleanup;
	controller->max_speed_hz = DIV_ROUND_UP(clk_get_rate(clk),
						US_MIN_CLK_DIV);
	controller->min_speed_hz = DIV_ROUND_UP(clk_get_rate(clk),
						US_MAX_CLK_DIV);
	platक्रमm_set_drvdata(pdev, controller);

	aus = spi_master_get_devdata(controller);

	aus->dev = &pdev->dev;
	aus->regs = devm_ioremap_resource(&pdev->dev, regs);
	अगर (IS_ERR(aus->regs)) अणु
		ret = PTR_ERR(aus->regs);
		जाओ at91_usart_spi_probe_fail;
	पूर्ण

	aus->irq = irq;
	aus->clk = clk;

	ret = devm_request_irq(&pdev->dev, irq, at91_usart_spi_पूर्णांकerrupt, 0,
			       dev_name(&pdev->dev), controller);
	अगर (ret)
		जाओ at91_usart_spi_probe_fail;

	ret = clk_prepare_enable(clk);
	अगर (ret)
		जाओ at91_usart_spi_probe_fail;

	aus->spi_clk = clk_get_rate(clk);
	at91_usart_spi_init(aus);

	aus->phybase = regs->start;

	aus->mpdev = to_platक्रमm_device(pdev->dev.parent);

	ret = at91_usart_spi_configure_dma(controller, aus);
	अगर (ret)
		जाओ at91_usart_fail_dma;

	spin_lock_init(&aus->lock);
	init_completion(&aus->xfer_completion);

	ret = devm_spi_रेजिस्टर_master(&pdev->dev, controller);
	अगर (ret)
		जाओ at91_usart_fail_रेजिस्टर_master;

	dev_info(&pdev->dev,
		 "AT91 USART SPI Controller version 0x%x at %pa (irq %d)\n",
		 at91_usart_spi_पढ़ोl(aus, VERSION),
		 &regs->start, irq);

	वापस 0;

at91_usart_fail_रेजिस्टर_master:
	at91_usart_spi_release_dma(controller);
at91_usart_fail_dma:
	clk_disable_unprepare(clk);
at91_usart_spi_probe_fail:
	spi_master_put(controller);
	वापस ret;
पूर्ण

__maybe_unused अटल पूर्णांक at91_usart_spi_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा spi_controller *ctlr = dev_get_drvdata(dev);
	काष्ठा at91_usart_spi *aus = spi_master_get_devdata(ctlr);

	clk_disable_unprepare(aus->clk);
	pinctrl_pm_select_sleep_state(dev);

	वापस 0;
पूर्ण

__maybe_unused अटल पूर्णांक at91_usart_spi_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा spi_controller *ctrl = dev_get_drvdata(dev);
	काष्ठा at91_usart_spi *aus = spi_master_get_devdata(ctrl);

	pinctrl_pm_select_शेष_state(dev);

	वापस clk_prepare_enable(aus->clk);
पूर्ण

__maybe_unused अटल पूर्णांक at91_usart_spi_suspend(काष्ठा device *dev)
अणु
	काष्ठा spi_controller *ctrl = dev_get_drvdata(dev);
	पूर्णांक ret;

	ret = spi_controller_suspend(ctrl);
	अगर (ret)
		वापस ret;

	अगर (!pm_runसमय_suspended(dev))
		at91_usart_spi_runसमय_suspend(dev);

	वापस 0;
पूर्ण

__maybe_unused अटल पूर्णांक at91_usart_spi_resume(काष्ठा device *dev)
अणु
	काष्ठा spi_controller *ctrl = dev_get_drvdata(dev);
	काष्ठा at91_usart_spi *aus = spi_master_get_devdata(ctrl);
	पूर्णांक ret;

	अगर (!pm_runसमय_suspended(dev)) अणु
		ret = at91_usart_spi_runसमय_resume(dev);
		अगर (ret)
			वापस ret;
	पूर्ण

	at91_usart_spi_init(aus);

	वापस spi_controller_resume(ctrl);
पूर्ण

अटल पूर्णांक at91_usart_spi_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा spi_controller *ctlr = platक्रमm_get_drvdata(pdev);
	काष्ठा at91_usart_spi *aus = spi_master_get_devdata(ctlr);

	at91_usart_spi_release_dma(ctlr);
	clk_disable_unprepare(aus->clk);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops at91_usart_spi_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(at91_usart_spi_suspend, at91_usart_spi_resume)
	SET_RUNTIME_PM_OPS(at91_usart_spi_runसमय_suspend,
			   at91_usart_spi_runसमय_resume, शून्य)
पूर्ण;

अटल काष्ठा platक्रमm_driver at91_usart_spi_driver = अणु
	.driver = अणु
		.name = "at91_usart_spi",
		.pm = &at91_usart_spi_pm_ops,
	पूर्ण,
	.probe = at91_usart_spi_probe,
	.हटाओ = at91_usart_spi_हटाओ,
पूर्ण;

module_platक्रमm_driver(at91_usart_spi_driver);

MODULE_DESCRIPTION("Microchip AT91 USART SPI Controller driver");
MODULE_AUTHOR("Radu Pirea <radu.pirea@microchip.com>");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:at91_usart_spi");
