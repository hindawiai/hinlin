<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * IMG SPFI controller driver
 *
 * Copyright (C) 2007,2008,2013 Imagination Technologies Ltd.
 * Copyright (C) 2014 Google, Inc.
 */

#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/dmaengine.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/irq.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/scatterlist.h>
#समावेश <linux/slab.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/spinlock.h>

#घोषणा SPFI_DEVICE_PARAMETER(x)		(0x00 + 0x4 * (x))
#घोषणा SPFI_DEVICE_PARAMETER_BITCLK_SHIFT	24
#घोषणा SPFI_DEVICE_PARAMETER_BITCLK_MASK	0xff
#घोषणा SPFI_DEVICE_PARAMETER_CSSETUP_SHIFT	16
#घोषणा SPFI_DEVICE_PARAMETER_CSSETUP_MASK	0xff
#घोषणा SPFI_DEVICE_PARAMETER_CSHOLD_SHIFT	8
#घोषणा SPFI_DEVICE_PARAMETER_CSHOLD_MASK	0xff
#घोषणा SPFI_DEVICE_PARAMETER_CSDELAY_SHIFT	0
#घोषणा SPFI_DEVICE_PARAMETER_CSDELAY_MASK	0xff

#घोषणा SPFI_CONTROL				0x14
#घोषणा SPFI_CONTROL_CONTINUE			BIT(12)
#घोषणा SPFI_CONTROL_SOFT_RESET			BIT(11)
#घोषणा SPFI_CONTROL_SEND_DMA			BIT(10)
#घोषणा SPFI_CONTROL_GET_DMA			BIT(9)
#घोषणा SPFI_CONTROL_SE			BIT(8)
#घोषणा SPFI_CONTROL_TMODE_SHIFT		5
#घोषणा SPFI_CONTROL_TMODE_MASK			0x7
#घोषणा SPFI_CONTROL_TMODE_SINGLE		0
#घोषणा SPFI_CONTROL_TMODE_DUAL			1
#घोषणा SPFI_CONTROL_TMODE_QUAD			2
#घोषणा SPFI_CONTROL_SPFI_EN			BIT(0)

#घोषणा SPFI_TRANSACTION			0x18
#घोषणा SPFI_TRANSACTION_TSIZE_SHIFT		16
#घोषणा SPFI_TRANSACTION_TSIZE_MASK		0xffff

#घोषणा SPFI_PORT_STATE				0x1c
#घोषणा SPFI_PORT_STATE_DEV_SEL_SHIFT		20
#घोषणा SPFI_PORT_STATE_DEV_SEL_MASK		0x7
#घोषणा SPFI_PORT_STATE_CK_POL(x)		BIT(19 - (x))
#घोषणा SPFI_PORT_STATE_CK_PHASE(x)		BIT(14 - (x))

#घोषणा SPFI_TX_32BIT_VALID_DATA		0x20
#घोषणा SPFI_TX_8BIT_VALID_DATA			0x24
#घोषणा SPFI_RX_32BIT_VALID_DATA		0x28
#घोषणा SPFI_RX_8BIT_VALID_DATA			0x2c

#घोषणा SPFI_INTERRUPT_STATUS			0x30
#घोषणा SPFI_INTERRUPT_ENABLE			0x34
#घोषणा SPFI_INTERRUPT_CLEAR			0x38
#घोषणा SPFI_INTERRUPT_IACCESS			BIT(12)
#घोषणा SPFI_INTERRUPT_GDEX8BIT			BIT(11)
#घोषणा SPFI_INTERRUPT_ALLDONETRIG		BIT(9)
#घोषणा SPFI_INTERRUPT_GDFUL			BIT(8)
#घोषणा SPFI_INTERRUPT_GDHF			BIT(7)
#घोषणा SPFI_INTERRUPT_GDEX32BIT		BIT(6)
#घोषणा SPFI_INTERRUPT_GDTRIG			BIT(5)
#घोषणा SPFI_INTERRUPT_SDFUL			BIT(3)
#घोषणा SPFI_INTERRUPT_SDHF			BIT(2)
#घोषणा SPFI_INTERRUPT_SDE			BIT(1)
#घोषणा SPFI_INTERRUPT_SDTRIG			BIT(0)

/*
 * There are four parallel FIFOs of 16 bytes each.  The word buffer
 * (*_32BIT_VALID_DATA) accesses all four FIFOs at once, resulting in an
 * effective FIFO size of 64 bytes.  The byte buffer (*_8BIT_VALID_DATA)
 * accesses only a single FIFO, resulting in an effective FIFO size of
 * 16 bytes.
 */
#घोषणा SPFI_32BIT_FIFO_SIZE			64
#घोषणा SPFI_8BIT_FIFO_SIZE			16

काष्ठा img_spfi अणु
	काष्ठा device *dev;
	काष्ठा spi_master *master;
	spinlock_t lock;

	व्योम __iomem *regs;
	phys_addr_t phys;
	पूर्णांक irq;
	काष्ठा clk *spfi_clk;
	काष्ठा clk *sys_clk;

	काष्ठा dma_chan *rx_ch;
	काष्ठा dma_chan *tx_ch;
	bool tx_dma_busy;
	bool rx_dma_busy;
पूर्ण;

अटल अंतरभूत u32 spfi_पढ़ोl(काष्ठा img_spfi *spfi, u32 reg)
अणु
	वापस पढ़ोl(spfi->regs + reg);
पूर्ण

अटल अंतरभूत व्योम spfi_ग_लिखोl(काष्ठा img_spfi *spfi, u32 val, u32 reg)
अणु
	ग_लिखोl(val, spfi->regs + reg);
पूर्ण

अटल अंतरभूत व्योम spfi_start(काष्ठा img_spfi *spfi)
अणु
	u32 val;

	val = spfi_पढ़ोl(spfi, SPFI_CONTROL);
	val |= SPFI_CONTROL_SPFI_EN;
	spfi_ग_लिखोl(spfi, val, SPFI_CONTROL);
पूर्ण

अटल अंतरभूत व्योम spfi_reset(काष्ठा img_spfi *spfi)
अणु
	spfi_ग_लिखोl(spfi, SPFI_CONTROL_SOFT_RESET, SPFI_CONTROL);
	spfi_ग_लिखोl(spfi, 0, SPFI_CONTROL);
पूर्ण

अटल पूर्णांक spfi_रुको_all_करोne(काष्ठा img_spfi *spfi)
अणु
	अचिन्हित दीर्घ समयout = jअगरfies + msecs_to_jअगरfies(50);

	जबतक (समय_beक्रमe(jअगरfies, समयout)) अणु
		u32 status = spfi_पढ़ोl(spfi, SPFI_INTERRUPT_STATUS);

		अगर (status & SPFI_INTERRUPT_ALLDONETRIG) अणु
			spfi_ग_लिखोl(spfi, SPFI_INTERRUPT_ALLDONETRIG,
				    SPFI_INTERRUPT_CLEAR);
			वापस 0;
		पूर्ण
		cpu_relax();
	पूर्ण

	dev_err(spfi->dev, "Timed out waiting for transaction to complete\n");
	spfi_reset(spfi);

	वापस -ETIMEDOUT;
पूर्ण

अटल अचिन्हित पूर्णांक spfi_pio_ग_लिखो32(काष्ठा img_spfi *spfi, स्थिर u32 *buf,
				     अचिन्हित पूर्णांक max)
अणु
	अचिन्हित पूर्णांक count = 0;
	u32 status;

	जबतक (count < max / 4) अणु
		spfi_ग_लिखोl(spfi, SPFI_INTERRUPT_SDFUL, SPFI_INTERRUPT_CLEAR);
		status = spfi_पढ़ोl(spfi, SPFI_INTERRUPT_STATUS);
		अगर (status & SPFI_INTERRUPT_SDFUL)
			अवरोध;
		spfi_ग_लिखोl(spfi, buf[count], SPFI_TX_32BIT_VALID_DATA);
		count++;
	पूर्ण

	वापस count * 4;
पूर्ण

अटल अचिन्हित पूर्णांक spfi_pio_ग_लिखो8(काष्ठा img_spfi *spfi, स्थिर u8 *buf,
				    अचिन्हित पूर्णांक max)
अणु
	अचिन्हित पूर्णांक count = 0;
	u32 status;

	जबतक (count < max) अणु
		spfi_ग_लिखोl(spfi, SPFI_INTERRUPT_SDFUL, SPFI_INTERRUPT_CLEAR);
		status = spfi_पढ़ोl(spfi, SPFI_INTERRUPT_STATUS);
		अगर (status & SPFI_INTERRUPT_SDFUL)
			अवरोध;
		spfi_ग_लिखोl(spfi, buf[count], SPFI_TX_8BIT_VALID_DATA);
		count++;
	पूर्ण

	वापस count;
पूर्ण

अटल अचिन्हित पूर्णांक spfi_pio_पढ़ो32(काष्ठा img_spfi *spfi, u32 *buf,
				    अचिन्हित पूर्णांक max)
अणु
	अचिन्हित पूर्णांक count = 0;
	u32 status;

	जबतक (count < max / 4) अणु
		spfi_ग_लिखोl(spfi, SPFI_INTERRUPT_GDEX32BIT,
			    SPFI_INTERRUPT_CLEAR);
		status = spfi_पढ़ोl(spfi, SPFI_INTERRUPT_STATUS);
		अगर (!(status & SPFI_INTERRUPT_GDEX32BIT))
			अवरोध;
		buf[count] = spfi_पढ़ोl(spfi, SPFI_RX_32BIT_VALID_DATA);
		count++;
	पूर्ण

	वापस count * 4;
पूर्ण

अटल अचिन्हित पूर्णांक spfi_pio_पढ़ो8(काष्ठा img_spfi *spfi, u8 *buf,
				   अचिन्हित पूर्णांक max)
अणु
	अचिन्हित पूर्णांक count = 0;
	u32 status;

	जबतक (count < max) अणु
		spfi_ग_लिखोl(spfi, SPFI_INTERRUPT_GDEX8BIT,
			    SPFI_INTERRUPT_CLEAR);
		status = spfi_पढ़ोl(spfi, SPFI_INTERRUPT_STATUS);
		अगर (!(status & SPFI_INTERRUPT_GDEX8BIT))
			अवरोध;
		buf[count] = spfi_पढ़ोl(spfi, SPFI_RX_8BIT_VALID_DATA);
		count++;
	पूर्ण

	वापस count;
पूर्ण

अटल पूर्णांक img_spfi_start_pio(काष्ठा spi_master *master,
			       काष्ठा spi_device *spi,
			       काष्ठा spi_transfer *xfer)
अणु
	काष्ठा img_spfi *spfi = spi_master_get_devdata(spi->master);
	अचिन्हित पूर्णांक tx_bytes = 0, rx_bytes = 0;
	स्थिर व्योम *tx_buf = xfer->tx_buf;
	व्योम *rx_buf = xfer->rx_buf;
	अचिन्हित दीर्घ समयout;
	पूर्णांक ret;

	अगर (tx_buf)
		tx_bytes = xfer->len;
	अगर (rx_buf)
		rx_bytes = xfer->len;

	spfi_start(spfi);

	समयout = jअगरfies +
		msecs_to_jअगरfies(xfer->len * 8 * 1000 / xfer->speed_hz + 100);
	जबतक ((tx_bytes > 0 || rx_bytes > 0) &&
	       समय_beक्रमe(jअगरfies, समयout)) अणु
		अचिन्हित पूर्णांक tx_count, rx_count;

		अगर (tx_bytes >= 4)
			tx_count = spfi_pio_ग_लिखो32(spfi, tx_buf, tx_bytes);
		अन्यथा
			tx_count = spfi_pio_ग_लिखो8(spfi, tx_buf, tx_bytes);

		अगर (rx_bytes >= 4)
			rx_count = spfi_pio_पढ़ो32(spfi, rx_buf, rx_bytes);
		अन्यथा
			rx_count = spfi_pio_पढ़ो8(spfi, rx_buf, rx_bytes);

		tx_buf += tx_count;
		rx_buf += rx_count;
		tx_bytes -= tx_count;
		rx_bytes -= rx_count;

		cpu_relax();
	पूर्ण

	अगर (rx_bytes > 0 || tx_bytes > 0) अणु
		dev_err(spfi->dev, "PIO transfer timed out\n");
		वापस -ETIMEDOUT;
	पूर्ण

	ret = spfi_रुको_all_करोne(spfi);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

अटल व्योम img_spfi_dma_rx_cb(व्योम *data)
अणु
	काष्ठा img_spfi *spfi = data;
	अचिन्हित दीर्घ flags;

	spfi_रुको_all_करोne(spfi);

	spin_lock_irqsave(&spfi->lock, flags);
	spfi->rx_dma_busy = false;
	अगर (!spfi->tx_dma_busy)
		spi_finalize_current_transfer(spfi->master);
	spin_unlock_irqrestore(&spfi->lock, flags);
पूर्ण

अटल व्योम img_spfi_dma_tx_cb(व्योम *data)
अणु
	काष्ठा img_spfi *spfi = data;
	अचिन्हित दीर्घ flags;

	spfi_रुको_all_करोne(spfi);

	spin_lock_irqsave(&spfi->lock, flags);
	spfi->tx_dma_busy = false;
	अगर (!spfi->rx_dma_busy)
		spi_finalize_current_transfer(spfi->master);
	spin_unlock_irqrestore(&spfi->lock, flags);
पूर्ण

अटल पूर्णांक img_spfi_start_dma(काष्ठा spi_master *master,
			      काष्ठा spi_device *spi,
			      काष्ठा spi_transfer *xfer)
अणु
	काष्ठा img_spfi *spfi = spi_master_get_devdata(spi->master);
	काष्ठा dma_async_tx_descriptor *rxdesc = शून्य, *txdesc = शून्य;
	काष्ठा dma_slave_config rxconf, txconf;

	spfi->rx_dma_busy = false;
	spfi->tx_dma_busy = false;

	अगर (xfer->rx_buf) अणु
		rxconf.direction = DMA_DEV_TO_MEM;
		अगर (xfer->len % 4 == 0) अणु
			rxconf.src_addr = spfi->phys + SPFI_RX_32BIT_VALID_DATA;
			rxconf.src_addr_width = 4;
			rxconf.src_maxburst = 4;
		पूर्ण अन्यथा अणु
			rxconf.src_addr = spfi->phys + SPFI_RX_8BIT_VALID_DATA;
			rxconf.src_addr_width = 1;
			rxconf.src_maxburst = 4;
		पूर्ण
		dmaengine_slave_config(spfi->rx_ch, &rxconf);

		rxdesc = dmaengine_prep_slave_sg(spfi->rx_ch, xfer->rx_sg.sgl,
						 xfer->rx_sg.nents,
						 DMA_DEV_TO_MEM,
						 DMA_PREP_INTERRUPT);
		अगर (!rxdesc)
			जाओ stop_dma;

		rxdesc->callback = img_spfi_dma_rx_cb;
		rxdesc->callback_param = spfi;
	पूर्ण

	अगर (xfer->tx_buf) अणु
		txconf.direction = DMA_MEM_TO_DEV;
		अगर (xfer->len % 4 == 0) अणु
			txconf.dst_addr = spfi->phys + SPFI_TX_32BIT_VALID_DATA;
			txconf.dst_addr_width = 4;
			txconf.dst_maxburst = 4;
		पूर्ण अन्यथा अणु
			txconf.dst_addr = spfi->phys + SPFI_TX_8BIT_VALID_DATA;
			txconf.dst_addr_width = 1;
			txconf.dst_maxburst = 4;
		पूर्ण
		dmaengine_slave_config(spfi->tx_ch, &txconf);

		txdesc = dmaengine_prep_slave_sg(spfi->tx_ch, xfer->tx_sg.sgl,
						 xfer->tx_sg.nents,
						 DMA_MEM_TO_DEV,
						 DMA_PREP_INTERRUPT);
		अगर (!txdesc)
			जाओ stop_dma;

		txdesc->callback = img_spfi_dma_tx_cb;
		txdesc->callback_param = spfi;
	पूर्ण

	अगर (xfer->rx_buf) अणु
		spfi->rx_dma_busy = true;
		dmaengine_submit(rxdesc);
		dma_async_issue_pending(spfi->rx_ch);
	पूर्ण

	spfi_start(spfi);

	अगर (xfer->tx_buf) अणु
		spfi->tx_dma_busy = true;
		dmaengine_submit(txdesc);
		dma_async_issue_pending(spfi->tx_ch);
	पूर्ण

	वापस 1;

stop_dma:
	dmaengine_terminate_all(spfi->rx_ch);
	dmaengine_terminate_all(spfi->tx_ch);
	वापस -EIO;
पूर्ण

अटल व्योम img_spfi_handle_err(काष्ठा spi_master *master,
				काष्ठा spi_message *msg)
अणु
	काष्ठा img_spfi *spfi = spi_master_get_devdata(master);
	अचिन्हित दीर्घ flags;

	/*
	 * Stop all DMA and reset the controller अगर the previous transaction
	 * समयd-out and never completed it's DMA.
	 */
	spin_lock_irqsave(&spfi->lock, flags);
	अगर (spfi->tx_dma_busy || spfi->rx_dma_busy) अणु
		spfi->tx_dma_busy = false;
		spfi->rx_dma_busy = false;

		dmaengine_terminate_all(spfi->tx_ch);
		dmaengine_terminate_all(spfi->rx_ch);
	पूर्ण
	spin_unlock_irqrestore(&spfi->lock, flags);
पूर्ण

अटल पूर्णांक img_spfi_prepare(काष्ठा spi_master *master, काष्ठा spi_message *msg)
अणु
	काष्ठा img_spfi *spfi = spi_master_get_devdata(master);
	u32 val;

	val = spfi_पढ़ोl(spfi, SPFI_PORT_STATE);
	val &= ~(SPFI_PORT_STATE_DEV_SEL_MASK <<
		 SPFI_PORT_STATE_DEV_SEL_SHIFT);
	val |= msg->spi->chip_select << SPFI_PORT_STATE_DEV_SEL_SHIFT;
	अगर (msg->spi->mode & SPI_CPHA)
		val |= SPFI_PORT_STATE_CK_PHASE(msg->spi->chip_select);
	अन्यथा
		val &= ~SPFI_PORT_STATE_CK_PHASE(msg->spi->chip_select);
	अगर (msg->spi->mode & SPI_CPOL)
		val |= SPFI_PORT_STATE_CK_POL(msg->spi->chip_select);
	अन्यथा
		val &= ~SPFI_PORT_STATE_CK_POL(msg->spi->chip_select);
	spfi_ग_लिखोl(spfi, val, SPFI_PORT_STATE);

	वापस 0;
पूर्ण

अटल पूर्णांक img_spfi_unprepare(काष्ठा spi_master *master,
			      काष्ठा spi_message *msg)
अणु
	काष्ठा img_spfi *spfi = spi_master_get_devdata(master);

	spfi_reset(spfi);

	वापस 0;
पूर्ण

अटल व्योम img_spfi_config(काष्ठा spi_master *master, काष्ठा spi_device *spi,
			    काष्ठा spi_transfer *xfer)
अणु
	काष्ठा img_spfi *spfi = spi_master_get_devdata(spi->master);
	u32 val, भाग;

	/*
	 * output = spfi_clk * (BITCLK / 512), where BITCLK must be a
	 * घातer of 2 up to 128
	 */
	भाग = DIV_ROUND_UP(clk_get_rate(spfi->spfi_clk), xfer->speed_hz);
	भाग = clamp(512 / (1 << get_count_order(भाग)), 1, 128);

	val = spfi_पढ़ोl(spfi, SPFI_DEVICE_PARAMETER(spi->chip_select));
	val &= ~(SPFI_DEVICE_PARAMETER_BITCLK_MASK <<
		 SPFI_DEVICE_PARAMETER_BITCLK_SHIFT);
	val |= भाग << SPFI_DEVICE_PARAMETER_BITCLK_SHIFT;
	spfi_ग_लिखोl(spfi, val, SPFI_DEVICE_PARAMETER(spi->chip_select));

	spfi_ग_लिखोl(spfi, xfer->len << SPFI_TRANSACTION_TSIZE_SHIFT,
		    SPFI_TRANSACTION);

	val = spfi_पढ़ोl(spfi, SPFI_CONTROL);
	val &= ~(SPFI_CONTROL_SEND_DMA | SPFI_CONTROL_GET_DMA);
	अगर (xfer->tx_buf)
		val |= SPFI_CONTROL_SEND_DMA;
	अगर (xfer->rx_buf)
		val |= SPFI_CONTROL_GET_DMA;
	val &= ~(SPFI_CONTROL_TMODE_MASK << SPFI_CONTROL_TMODE_SHIFT);
	अगर (xfer->tx_nbits == SPI_NBITS_DUAL &&
	    xfer->rx_nbits == SPI_NBITS_DUAL)
		val |= SPFI_CONTROL_TMODE_DUAL << SPFI_CONTROL_TMODE_SHIFT;
	अन्यथा अगर (xfer->tx_nbits == SPI_NBITS_QUAD &&
		 xfer->rx_nbits == SPI_NBITS_QUAD)
		val |= SPFI_CONTROL_TMODE_QUAD << SPFI_CONTROL_TMODE_SHIFT;
	val |= SPFI_CONTROL_SE;
	spfi_ग_लिखोl(spfi, val, SPFI_CONTROL);
पूर्ण

अटल पूर्णांक img_spfi_transfer_one(काष्ठा spi_master *master,
				 काष्ठा spi_device *spi,
				 काष्ठा spi_transfer *xfer)
अणु
	काष्ठा img_spfi *spfi = spi_master_get_devdata(spi->master);
	पूर्णांक ret;

	अगर (xfer->len > SPFI_TRANSACTION_TSIZE_MASK) अणु
		dev_err(spfi->dev,
			"Transfer length (%d) is greater than the max supported (%d)",
			xfer->len, SPFI_TRANSACTION_TSIZE_MASK);
		वापस -EINVAL;
	पूर्ण

	img_spfi_config(master, spi, xfer);
	अगर (master->can_dma && master->can_dma(master, spi, xfer))
		ret = img_spfi_start_dma(master, spi, xfer);
	अन्यथा
		ret = img_spfi_start_pio(master, spi, xfer);

	वापस ret;
पूर्ण

अटल bool img_spfi_can_dma(काष्ठा spi_master *master, काष्ठा spi_device *spi,
			     काष्ठा spi_transfer *xfer)
अणु
	अगर (xfer->len > SPFI_32BIT_FIFO_SIZE)
		वापस true;
	वापस false;
पूर्ण

अटल irqवापस_t img_spfi_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा img_spfi *spfi = (काष्ठा img_spfi *)dev_id;
	u32 status;

	status = spfi_पढ़ोl(spfi, SPFI_INTERRUPT_STATUS);
	अगर (status & SPFI_INTERRUPT_IACCESS) अणु
		spfi_ग_लिखोl(spfi, SPFI_INTERRUPT_IACCESS, SPFI_INTERRUPT_CLEAR);
		dev_err(spfi->dev, "Illegal access interrupt");
		वापस IRQ_HANDLED;
	पूर्ण

	वापस IRQ_NONE;
पूर्ण

अटल पूर्णांक img_spfi_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा spi_master *master;
	काष्ठा img_spfi *spfi;
	काष्ठा resource *res;
	पूर्णांक ret;
	u32 max_speed_hz;

	master = spi_alloc_master(&pdev->dev, माप(*spfi));
	अगर (!master)
		वापस -ENOMEM;
	platक्रमm_set_drvdata(pdev, master);

	spfi = spi_master_get_devdata(master);
	spfi->dev = &pdev->dev;
	spfi->master = master;
	spin_lock_init(&spfi->lock);

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	spfi->regs = devm_ioremap_resource(spfi->dev, res);
	अगर (IS_ERR(spfi->regs)) अणु
		ret = PTR_ERR(spfi->regs);
		जाओ put_spi;
	पूर्ण
	spfi->phys = res->start;

	spfi->irq = platक्रमm_get_irq(pdev, 0);
	अगर (spfi->irq < 0) अणु
		ret = spfi->irq;
		जाओ put_spi;
	पूर्ण
	ret = devm_request_irq(spfi->dev, spfi->irq, img_spfi_irq,
			       IRQ_TYPE_LEVEL_HIGH, dev_name(spfi->dev), spfi);
	अगर (ret)
		जाओ put_spi;

	spfi->sys_clk = devm_clk_get(spfi->dev, "sys");
	अगर (IS_ERR(spfi->sys_clk)) अणु
		ret = PTR_ERR(spfi->sys_clk);
		जाओ put_spi;
	पूर्ण
	spfi->spfi_clk = devm_clk_get(spfi->dev, "spfi");
	अगर (IS_ERR(spfi->spfi_clk)) अणु
		ret = PTR_ERR(spfi->spfi_clk);
		जाओ put_spi;
	पूर्ण

	ret = clk_prepare_enable(spfi->sys_clk);
	अगर (ret)
		जाओ put_spi;
	ret = clk_prepare_enable(spfi->spfi_clk);
	अगर (ret)
		जाओ disable_pclk;

	spfi_reset(spfi);
	/*
	 * Only enable the error (IACCESS) पूर्णांकerrupt.  In PIO mode we'll
	 * poll the status of the FIFOs.
	 */
	spfi_ग_लिखोl(spfi, SPFI_INTERRUPT_IACCESS, SPFI_INTERRUPT_ENABLE);

	master->स्वतः_runसमय_pm = true;
	master->bus_num = pdev->id;
	master->mode_bits = SPI_CPOL | SPI_CPHA | SPI_TX_DUAL | SPI_RX_DUAL;
	अगर (of_property_पढ़ो_bool(spfi->dev->of_node, "img,supports-quad-mode"))
		master->mode_bits |= SPI_TX_QUAD | SPI_RX_QUAD;
	master->dev.of_node = pdev->dev.of_node;
	master->bits_per_word_mask = SPI_BPW_MASK(32) | SPI_BPW_MASK(8);
	master->max_speed_hz = clk_get_rate(spfi->spfi_clk) / 4;
	master->min_speed_hz = clk_get_rate(spfi->spfi_clk) / 512;

	/*
	 * Maximum speed supported by spfi is limited to the lower value
	 * between 1/4 of the SPFI घड़ी or to "spfi-max-frequency"
	 * defined in the device tree.
	 * If no value is defined in the device tree assume the maximum
	 * speed supported to be 1/4 of the SPFI घड़ी.
	 */
	अगर (!of_property_पढ़ो_u32(spfi->dev->of_node, "spfi-max-frequency",
				  &max_speed_hz)) अणु
		अगर (master->max_speed_hz > max_speed_hz)
			master->max_speed_hz = max_speed_hz;
	पूर्ण

	master->transfer_one = img_spfi_transfer_one;
	master->prepare_message = img_spfi_prepare;
	master->unprepare_message = img_spfi_unprepare;
	master->handle_err = img_spfi_handle_err;
	master->use_gpio_descriptors = true;

	spfi->tx_ch = dma_request_chan(spfi->dev, "tx");
	अगर (IS_ERR(spfi->tx_ch)) अणु
		ret = PTR_ERR(spfi->tx_ch);
		spfi->tx_ch = शून्य;
		अगर (ret == -EPROBE_DEFER)
			जाओ disable_pm;
	पूर्ण

	spfi->rx_ch = dma_request_chan(spfi->dev, "rx");
	अगर (IS_ERR(spfi->rx_ch)) अणु
		ret = PTR_ERR(spfi->rx_ch);
		spfi->rx_ch = शून्य;
		अगर (ret == -EPROBE_DEFER)
			जाओ disable_pm;
	पूर्ण

	अगर (!spfi->tx_ch || !spfi->rx_ch) अणु
		अगर (spfi->tx_ch)
			dma_release_channel(spfi->tx_ch);
		अगर (spfi->rx_ch)
			dma_release_channel(spfi->rx_ch);
		spfi->tx_ch = शून्य;
		spfi->rx_ch = शून्य;
		dev_warn(spfi->dev, "Failed to get DMA channels, falling back to PIO mode\n");
	पूर्ण अन्यथा अणु
		master->dma_tx = spfi->tx_ch;
		master->dma_rx = spfi->rx_ch;
		master->can_dma = img_spfi_can_dma;
	पूर्ण

	pm_runसमय_set_active(spfi->dev);
	pm_runसमय_enable(spfi->dev);

	ret = devm_spi_रेजिस्टर_master(spfi->dev, master);
	अगर (ret)
		जाओ disable_pm;

	वापस 0;

disable_pm:
	pm_runसमय_disable(spfi->dev);
	अगर (spfi->rx_ch)
		dma_release_channel(spfi->rx_ch);
	अगर (spfi->tx_ch)
		dma_release_channel(spfi->tx_ch);
	clk_disable_unprepare(spfi->spfi_clk);
disable_pclk:
	clk_disable_unprepare(spfi->sys_clk);
put_spi:
	spi_master_put(master);

	वापस ret;
पूर्ण

अटल पूर्णांक img_spfi_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा spi_master *master = platक्रमm_get_drvdata(pdev);
	काष्ठा img_spfi *spfi = spi_master_get_devdata(master);

	अगर (spfi->tx_ch)
		dma_release_channel(spfi->tx_ch);
	अगर (spfi->rx_ch)
		dma_release_channel(spfi->rx_ch);

	pm_runसमय_disable(spfi->dev);
	अगर (!pm_runसमय_status_suspended(spfi->dev)) अणु
		clk_disable_unprepare(spfi->spfi_clk);
		clk_disable_unprepare(spfi->sys_clk);
	पूर्ण

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक img_spfi_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा spi_master *master = dev_get_drvdata(dev);
	काष्ठा img_spfi *spfi = spi_master_get_devdata(master);

	clk_disable_unprepare(spfi->spfi_clk);
	clk_disable_unprepare(spfi->sys_clk);

	वापस 0;
पूर्ण

अटल पूर्णांक img_spfi_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा spi_master *master = dev_get_drvdata(dev);
	काष्ठा img_spfi *spfi = spi_master_get_devdata(master);
	पूर्णांक ret;

	ret = clk_prepare_enable(spfi->sys_clk);
	अगर (ret)
		वापस ret;
	ret = clk_prepare_enable(spfi->spfi_clk);
	अगर (ret) अणु
		clk_disable_unprepare(spfi->sys_clk);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_PM */

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक img_spfi_suspend(काष्ठा device *dev)
अणु
	काष्ठा spi_master *master = dev_get_drvdata(dev);

	वापस spi_master_suspend(master);
पूर्ण

अटल पूर्णांक img_spfi_resume(काष्ठा device *dev)
अणु
	काष्ठा spi_master *master = dev_get_drvdata(dev);
	काष्ठा img_spfi *spfi = spi_master_get_devdata(master);
	पूर्णांक ret;

	ret = pm_runसमय_get_sync(dev);
	अगर (ret) अणु
		pm_runसमय_put_noidle(dev);
		वापस ret;
	पूर्ण
	spfi_reset(spfi);
	pm_runसमय_put(dev);

	वापस spi_master_resume(master);
पूर्ण
#पूर्ण_अगर /* CONFIG_PM_SLEEP */

अटल स्थिर काष्ठा dev_pm_ops img_spfi_pm_ops = अणु
	SET_RUNTIME_PM_OPS(img_spfi_runसमय_suspend, img_spfi_runसमय_resume,
			   शून्य)
	SET_SYSTEM_SLEEP_PM_OPS(img_spfi_suspend, img_spfi_resume)
पूर्ण;

अटल स्थिर काष्ठा of_device_id img_spfi_of_match[] = अणु
	अणु .compatible = "img,spfi", पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, img_spfi_of_match);

अटल काष्ठा platक्रमm_driver img_spfi_driver = अणु
	.driver = अणु
		.name = "img-spfi",
		.pm = &img_spfi_pm_ops,
		.of_match_table = of_match_ptr(img_spfi_of_match),
	पूर्ण,
	.probe = img_spfi_probe,
	.हटाओ = img_spfi_हटाओ,
पूर्ण;
module_platक्रमm_driver(img_spfi_driver);

MODULE_DESCRIPTION("IMG SPFI controller driver");
MODULE_AUTHOR("Andrew Bresticker <abrestic@chromium.org>");
MODULE_LICENSE("GPL v2");
