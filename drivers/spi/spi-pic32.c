<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Microchip PIC32 SPI controller driver.
 *
 * Purna Chandra Mandal <purna.mandal@microchip.com>
 * Copyright (c) 2016, Microchip Technology Inc.
 */

#समावेश <linux/clk.h>
#समावेश <linux/clkdev.h>
#समावेश <linux/delay.h>
#समावेश <linux/dmaengine.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/module.h>
#समावेश <linux/पन.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/of.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/of_gpपन.स>
#समावेश <linux/of_address.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/spi/spi.h>

/* SPI controller रेजिस्टरs */
काष्ठा pic32_spi_regs अणु
	u32 ctrl;
	u32 ctrl_clr;
	u32 ctrl_set;
	u32 ctrl_inv;
	u32 status;
	u32 status_clr;
	u32 status_set;
	u32 status_inv;
	u32 buf;
	u32 करोntuse[3];
	u32 baud;
	u32 करोntuse2[3];
	u32 ctrl2;
	u32 ctrl2_clr;
	u32 ctrl2_set;
	u32 ctrl2_inv;
पूर्ण;

/* Bit fields of SPI Control Register */
#घोषणा CTRL_RX_INT_SHIFT	0  /* Rx पूर्णांकerrupt generation */
#घोषणा  RX_FIFO_EMPTY		0
#घोषणा  RX_FIFO_NOT_EMPTY	1 /* not empty */
#घोषणा  RX_FIFO_HALF_FULL	2 /* full by half or more */
#घोषणा  RX_FIFO_FULL		3 /* completely full */

#घोषणा CTRL_TX_INT_SHIFT	2  /* TX पूर्णांकerrupt generation */
#घोषणा  TX_FIFO_ALL_EMPTY	0 /* completely empty */
#घोषणा  TX_FIFO_EMPTY		1 /* empty */
#घोषणा  TX_FIFO_HALF_EMPTY	2 /* empty by half or more */
#घोषणा  TX_FIFO_NOT_FULL	3 /* atleast one empty */

#घोषणा CTRL_MSTEN	BIT(5) /* enable master mode */
#घोषणा CTRL_CKP	BIT(6) /* active low */
#घोषणा CTRL_CKE	BIT(8) /* Tx on falling edge */
#घोषणा CTRL_SMP	BIT(9) /* Rx at middle or end of tx */
#घोषणा CTRL_BPW_MASK	0x03   /* bits per word/sample */
#घोषणा CTRL_BPW_SHIFT	10
#घोषणा  PIC32_BPW_8	0
#घोषणा  PIC32_BPW_16	1
#घोषणा  PIC32_BPW_32	2
#घोषणा CTRL_SIDL	BIT(13) /* sleep when idle */
#घोषणा CTRL_ON		BIT(15) /* enable macro */
#घोषणा CTRL_ENHBUF	BIT(16) /* enable enhanced buffering */
#घोषणा CTRL_MCLKSEL	BIT(23) /* select घड़ी source */
#घोषणा CTRL_MSSEN	BIT(28) /* macro driven /SS */
#घोषणा CTRL_FRMEN	BIT(31) /* enable framing mode */

/* Bit fields of SPI Status Register */
#घोषणा STAT_RF_EMPTY	BIT(5) /* RX Fअगरo empty */
#घोषणा STAT_RX_OV	BIT(6) /* err, s/w needs to clear */
#घोषणा STAT_TX_UR	BIT(8) /* UR in Framed SPI modes */
#घोषणा STAT_FRM_ERR	BIT(12) /* Multiple Frame Sync pulse */
#घोषणा STAT_TF_LVL_MASK	0x1F
#घोषणा STAT_TF_LVL_SHIFT	16
#घोषणा STAT_RF_LVL_MASK	0x1F
#घोषणा STAT_RF_LVL_SHIFT	24

/* Bit fields of SPI Baud Register */
#घोषणा BAUD_MASK		0x1ff

/* Bit fields of SPI Control2 Register */
#घोषणा CTRL2_TX_UR_EN		BIT(10) /* Enable पूर्णांक on Tx under-run */
#घोषणा CTRL2_RX_OV_EN		BIT(11) /* Enable पूर्णांक on Rx over-run */
#घोषणा CTRL2_FRM_ERR_EN	BIT(12) /* Enable frame err पूर्णांक */

/* Minimum DMA transfer size */
#घोषणा PIC32_DMA_LEN_MIN	64

काष्ठा pic32_spi अणु
	dma_addr_t		dma_base;
	काष्ठा pic32_spi_regs __iomem *regs;
	पूर्णांक			fault_irq;
	पूर्णांक			rx_irq;
	पूर्णांक			tx_irq;
	u32			fअगरo_n_byte; /* FIFO depth in bytes */
	काष्ठा clk		*clk;
	काष्ठा spi_master	*master;
	/* Current controller setting */
	u32			speed_hz; /* spi-clk rate */
	u32			mode;
	u32			bits_per_word;
	u32			fअगरo_n_elm; /* FIFO depth in words */
#घोषणा PIC32F_DMA_PREP		0 /* DMA chnls configured */
	अचिन्हित दीर्घ		flags;
	/* Current transfer state */
	काष्ठा completion	xfer_करोne;
	/* PIO transfer specअगरic */
	स्थिर व्योम		*tx;
	स्थिर व्योम		*tx_end;
	स्थिर व्योम		*rx;
	स्थिर व्योम		*rx_end;
	पूर्णांक			len;
	व्योम (*rx_fअगरo)(काष्ठा pic32_spi *);
	व्योम (*tx_fअगरo)(काष्ठा pic32_spi *);
पूर्ण;

अटल अंतरभूत व्योम pic32_spi_enable(काष्ठा pic32_spi *pic32s)
अणु
	ग_लिखोl(CTRL_ON | CTRL_SIDL, &pic32s->regs->ctrl_set);
पूर्ण

अटल अंतरभूत व्योम pic32_spi_disable(काष्ठा pic32_spi *pic32s)
अणु
	ग_लिखोl(CTRL_ON | CTRL_SIDL, &pic32s->regs->ctrl_clr);

	/* aव्योम SPI रेजिस्टरs पढ़ो/ग_लिखो at immediate next CPU घड़ी */
	ndelay(20);
पूर्ण

अटल व्योम pic32_spi_set_clk_rate(काष्ठा pic32_spi *pic32s, u32 spi_ck)
अणु
	u32 भाग;

	/* भाग = (clk_in / 2 * spi_ck) - 1 */
	भाग = DIV_ROUND_CLOSEST(clk_get_rate(pic32s->clk), 2 * spi_ck) - 1;

	ग_लिखोl(भाग & BAUD_MASK, &pic32s->regs->baud);
पूर्ण

अटल अंतरभूत u32 pic32_rx_fअगरo_level(काष्ठा pic32_spi *pic32s)
अणु
	u32 sr = पढ़ोl(&pic32s->regs->status);

	वापस (sr >> STAT_RF_LVL_SHIFT) & STAT_RF_LVL_MASK;
पूर्ण

अटल अंतरभूत u32 pic32_tx_fअगरo_level(काष्ठा pic32_spi *pic32s)
अणु
	u32 sr = पढ़ोl(&pic32s->regs->status);

	वापस (sr >> STAT_TF_LVL_SHIFT) & STAT_TF_LVL_MASK;
पूर्ण

/* Return the max entries we can fill पूर्णांकo tx fअगरo */
अटल u32 pic32_tx_max(काष्ठा pic32_spi *pic32s, पूर्णांक n_bytes)
अणु
	u32 tx_left, tx_room, rxtx_gap;

	tx_left = (pic32s->tx_end - pic32s->tx) / n_bytes;
	tx_room = pic32s->fअगरo_n_elm - pic32_tx_fअगरo_level(pic32s);

	/*
	 * Another concern is about the tx/rx mismatch, we
	 * though to use (pic32s->fअगरo_n_byte - rxfl - txfl) as
	 * one maximum value क्रम tx, but it करोesn't cover the
	 * data which is out of tx/rx fअगरo and inside the
	 * shअगरt रेजिस्टरs. So a ctrl from sw poपूर्णांक of
	 * view is taken.
	 */
	rxtx_gap = ((pic32s->rx_end - pic32s->rx) -
		    (pic32s->tx_end - pic32s->tx)) / n_bytes;
	वापस min3(tx_left, tx_room, (u32)(pic32s->fअगरo_n_elm - rxtx_gap));
पूर्ण

/* Return the max entries we should पढ़ो out of rx fअगरo */
अटल u32 pic32_rx_max(काष्ठा pic32_spi *pic32s, पूर्णांक n_bytes)
अणु
	u32 rx_left = (pic32s->rx_end - pic32s->rx) / n_bytes;

	वापस min_t(u32, rx_left, pic32_rx_fअगरo_level(pic32s));
पूर्ण

#घोषणा BUILD_SPI_FIFO_RW(__name, __type, __bwl)		\
अटल व्योम pic32_spi_rx_##__name(काष्ठा pic32_spi *pic32s)	\
अणु								\
	__type v;						\
	u32 mx = pic32_rx_max(pic32s, माप(__type));		\
	क्रम (; mx; mx--) अणु					\
		v = पढ़ो##__bwl(&pic32s->regs->buf);		\
		अगर (pic32s->rx_end - pic32s->len)		\
			*(__type *)(pic32s->rx) = v;		\
		pic32s->rx += माप(__type);			\
	पूर्ण							\
पूर्ण								\
								\
अटल व्योम pic32_spi_tx_##__name(काष्ठा pic32_spi *pic32s)	\
अणु								\
	__type v;						\
	u32 mx = pic32_tx_max(pic32s, माप(__type));		\
	क्रम (; mx ; mx--) अणु					\
		v = (__type)~0U;				\
		अगर (pic32s->tx_end - pic32s->len)		\
			v = *(__type *)(pic32s->tx);		\
		ग_लिखो##__bwl(v, &pic32s->regs->buf);		\
		pic32s->tx += माप(__type);			\
	पूर्ण							\
पूर्ण

BUILD_SPI_FIFO_RW(byte, u8, b);
BUILD_SPI_FIFO_RW(word, u16, w);
BUILD_SPI_FIFO_RW(dword, u32, l);

अटल व्योम pic32_err_stop(काष्ठा pic32_spi *pic32s, स्थिर अक्षर *msg)
अणु
	/* disable all पूर्णांकerrupts */
	disable_irq_nosync(pic32s->fault_irq);
	disable_irq_nosync(pic32s->rx_irq);
	disable_irq_nosync(pic32s->tx_irq);

	/* Show err message and पात xfer with err */
	dev_err(&pic32s->master->dev, "%s\n", msg);
	अगर (pic32s->master->cur_msg)
		pic32s->master->cur_msg->status = -EIO;
	complete(&pic32s->xfer_करोne);
पूर्ण

अटल irqवापस_t pic32_spi_fault_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा pic32_spi *pic32s = dev_id;
	u32 status;

	status = पढ़ोl(&pic32s->regs->status);

	/* Error handling */
	अगर (status & (STAT_RX_OV | STAT_TX_UR)) अणु
		ग_लिखोl(STAT_RX_OV, &pic32s->regs->status_clr);
		ग_लिखोl(STAT_TX_UR, &pic32s->regs->status_clr);
		pic32_err_stop(pic32s, "err_irq: fifo ov/ur-run\n");
		वापस IRQ_HANDLED;
	पूर्ण

	अगर (status & STAT_FRM_ERR) अणु
		pic32_err_stop(pic32s, "err_irq: frame error");
		वापस IRQ_HANDLED;
	पूर्ण

	अगर (!pic32s->master->cur_msg) अणु
		pic32_err_stop(pic32s, "err_irq: no mesg");
		वापस IRQ_NONE;
	पूर्ण

	वापस IRQ_NONE;
पूर्ण

अटल irqवापस_t pic32_spi_rx_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा pic32_spi *pic32s = dev_id;

	pic32s->rx_fअगरo(pic32s);

	/* rx complete ? */
	अगर (pic32s->rx_end == pic32s->rx) अणु
		/* disable all पूर्णांकerrupts */
		disable_irq_nosync(pic32s->fault_irq);
		disable_irq_nosync(pic32s->rx_irq);

		/* complete current xfer */
		complete(&pic32s->xfer_करोne);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t pic32_spi_tx_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा pic32_spi *pic32s = dev_id;

	pic32s->tx_fअगरo(pic32s);

	/* tx complete? disable tx पूर्णांकerrupt */
	अगर (pic32s->tx_end == pic32s->tx)
		disable_irq_nosync(pic32s->tx_irq);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम pic32_spi_dma_rx_notअगरy(व्योम *data)
अणु
	काष्ठा pic32_spi *pic32s = data;

	complete(&pic32s->xfer_करोne);
पूर्ण

अटल पूर्णांक pic32_spi_dma_transfer(काष्ठा pic32_spi *pic32s,
				  काष्ठा spi_transfer *xfer)
अणु
	काष्ठा spi_master *master = pic32s->master;
	काष्ठा dma_async_tx_descriptor *desc_rx;
	काष्ठा dma_async_tx_descriptor *desc_tx;
	dma_cookie_t cookie;
	पूर्णांक ret;

	अगर (!master->dma_rx || !master->dma_tx)
		वापस -ENODEV;

	desc_rx = dmaengine_prep_slave_sg(master->dma_rx,
					  xfer->rx_sg.sgl,
					  xfer->rx_sg.nents,
					  DMA_DEV_TO_MEM,
					  DMA_PREP_INTERRUPT | DMA_CTRL_ACK);
	अगर (!desc_rx) अणु
		ret = -EINVAL;
		जाओ err_dma;
	पूर्ण

	desc_tx = dmaengine_prep_slave_sg(master->dma_tx,
					  xfer->tx_sg.sgl,
					  xfer->tx_sg.nents,
					  DMA_MEM_TO_DEV,
					  DMA_PREP_INTERRUPT | DMA_CTRL_ACK);
	अगर (!desc_tx) अणु
		ret = -EINVAL;
		जाओ err_dma;
	पूर्ण

	/* Put callback on the RX transfer, that should finish last */
	desc_rx->callback = pic32_spi_dma_rx_notअगरy;
	desc_rx->callback_param = pic32s;

	cookie = dmaengine_submit(desc_rx);
	ret = dma_submit_error(cookie);
	अगर (ret)
		जाओ err_dma;

	cookie = dmaengine_submit(desc_tx);
	ret = dma_submit_error(cookie);
	अगर (ret)
		जाओ err_dma_tx;

	dma_async_issue_pending(master->dma_rx);
	dma_async_issue_pending(master->dma_tx);

	वापस 0;

err_dma_tx:
	dmaengine_terminate_all(master->dma_rx);
err_dma:
	वापस ret;
पूर्ण

अटल पूर्णांक pic32_spi_dma_config(काष्ठा pic32_spi *pic32s, u32 dma_width)
अणु
	पूर्णांक buf_offset = दुरत्व(काष्ठा pic32_spi_regs, buf);
	काष्ठा spi_master *master = pic32s->master;
	काष्ठा dma_slave_config cfg;
	पूर्णांक ret;

	cfg.device_fc = true;
	cfg.src_addr = pic32s->dma_base + buf_offset;
	cfg.dst_addr = pic32s->dma_base + buf_offset;
	cfg.src_maxburst = pic32s->fअगरo_n_elm / 2; /* fill one-half */
	cfg.dst_maxburst = pic32s->fअगरo_n_elm / 2; /* drain one-half */
	cfg.src_addr_width = dma_width;
	cfg.dst_addr_width = dma_width;
	/* tx channel */
	cfg.slave_id = pic32s->tx_irq;
	cfg.direction = DMA_MEM_TO_DEV;
	ret = dmaengine_slave_config(master->dma_tx, &cfg);
	अगर (ret) अणु
		dev_err(&master->dev, "tx channel setup failed\n");
		वापस ret;
	पूर्ण
	/* rx channel */
	cfg.slave_id = pic32s->rx_irq;
	cfg.direction = DMA_DEV_TO_MEM;
	ret = dmaengine_slave_config(master->dma_rx, &cfg);
	अगर (ret)
		dev_err(&master->dev, "rx channel setup failed\n");

	वापस ret;
पूर्ण

अटल पूर्णांक pic32_spi_set_word_size(काष्ठा pic32_spi *pic32s, u8 bits_per_word)
अणु
	क्रमागत dma_slave_buswidth dmawidth;
	u32 buswidth, v;

	चयन (bits_per_word) अणु
	हाल 8:
		pic32s->rx_fअगरo = pic32_spi_rx_byte;
		pic32s->tx_fअगरo = pic32_spi_tx_byte;
		buswidth = PIC32_BPW_8;
		dmawidth = DMA_SLAVE_BUSWIDTH_1_BYTE;
		अवरोध;
	हाल 16:
		pic32s->rx_fअगरo = pic32_spi_rx_word;
		pic32s->tx_fअगरo = pic32_spi_tx_word;
		buswidth = PIC32_BPW_16;
		dmawidth = DMA_SLAVE_BUSWIDTH_2_BYTES;
		अवरोध;
	हाल 32:
		pic32s->rx_fअगरo = pic32_spi_rx_dword;
		pic32s->tx_fअगरo = pic32_spi_tx_dword;
		buswidth = PIC32_BPW_32;
		dmawidth = DMA_SLAVE_BUSWIDTH_4_BYTES;
		अवरोध;
	शेष:
		/* not supported */
		वापस -EINVAL;
	पूर्ण

	/* calculate maximum number of words fअगरos can hold */
	pic32s->fअगरo_n_elm = DIV_ROUND_UP(pic32s->fअगरo_n_byte,
					  bits_per_word / 8);
	/* set word size */
	v = पढ़ोl(&pic32s->regs->ctrl);
	v &= ~(CTRL_BPW_MASK << CTRL_BPW_SHIFT);
	v |= buswidth << CTRL_BPW_SHIFT;
	ग_लिखोl(v, &pic32s->regs->ctrl);

	/* re-configure dma width, अगर required */
	अगर (test_bit(PIC32F_DMA_PREP, &pic32s->flags))
		pic32_spi_dma_config(pic32s, dmawidth);

	वापस 0;
पूर्ण

अटल पूर्णांक pic32_spi_prepare_hardware(काष्ठा spi_master *master)
अणु
	काष्ठा pic32_spi *pic32s = spi_master_get_devdata(master);

	pic32_spi_enable(pic32s);

	वापस 0;
पूर्ण

अटल पूर्णांक pic32_spi_prepare_message(काष्ठा spi_master *master,
				     काष्ठा spi_message *msg)
अणु
	काष्ठा pic32_spi *pic32s = spi_master_get_devdata(master);
	काष्ठा spi_device *spi = msg->spi;
	u32 val;

	/* set device specअगरic bits_per_word */
	अगर (pic32s->bits_per_word != spi->bits_per_word) अणु
		pic32_spi_set_word_size(pic32s, spi->bits_per_word);
		pic32s->bits_per_word = spi->bits_per_word;
	पूर्ण

	/* device specअगरic speed change */
	अगर (pic32s->speed_hz != spi->max_speed_hz) अणु
		pic32_spi_set_clk_rate(pic32s, spi->max_speed_hz);
		pic32s->speed_hz = spi->max_speed_hz;
	पूर्ण

	/* device specअगरic mode change */
	अगर (pic32s->mode != spi->mode) अणु
		val = पढ़ोl(&pic32s->regs->ctrl);
		/* active low */
		अगर (spi->mode & SPI_CPOL)
			val |= CTRL_CKP;
		अन्यथा
			val &= ~CTRL_CKP;
		/* tx on rising edge */
		अगर (spi->mode & SPI_CPHA)
			val &= ~CTRL_CKE;
		अन्यथा
			val |= CTRL_CKE;

		/* rx at end of tx */
		val |= CTRL_SMP;
		ग_लिखोl(val, &pic32s->regs->ctrl);
		pic32s->mode = spi->mode;
	पूर्ण

	वापस 0;
पूर्ण

अटल bool pic32_spi_can_dma(काष्ठा spi_master *master,
			      काष्ठा spi_device *spi,
			      काष्ठा spi_transfer *xfer)
अणु
	काष्ठा pic32_spi *pic32s = spi_master_get_devdata(master);

	/* skip using DMA on small size transfer to aव्योम overhead.*/
	वापस (xfer->len >= PIC32_DMA_LEN_MIN) &&
	       test_bit(PIC32F_DMA_PREP, &pic32s->flags);
पूर्ण

अटल पूर्णांक pic32_spi_one_transfer(काष्ठा spi_master *master,
				  काष्ठा spi_device *spi,
				  काष्ठा spi_transfer *transfer)
अणु
	काष्ठा pic32_spi *pic32s;
	bool dma_issued = false;
	अचिन्हित दीर्घ समयout;
	पूर्णांक ret;

	pic32s = spi_master_get_devdata(master);

	/* handle transfer specअगरic word size change */
	अगर (transfer->bits_per_word &&
	    (transfer->bits_per_word != pic32s->bits_per_word)) अणु
		ret = pic32_spi_set_word_size(pic32s, transfer->bits_per_word);
		अगर (ret)
			वापस ret;
		pic32s->bits_per_word = transfer->bits_per_word;
	पूर्ण

	/* handle transfer specअगरic speed change */
	अगर (transfer->speed_hz && (transfer->speed_hz != pic32s->speed_hz)) अणु
		pic32_spi_set_clk_rate(pic32s, transfer->speed_hz);
		pic32s->speed_hz = transfer->speed_hz;
	पूर्ण

	reinit_completion(&pic32s->xfer_करोne);

	/* transact by DMA mode */
	अगर (transfer->rx_sg.nents && transfer->tx_sg.nents) अणु
		ret = pic32_spi_dma_transfer(pic32s, transfer);
		अगर (ret) अणु
			dev_err(&spi->dev, "dma submit error\n");
			वापस ret;
		पूर्ण

		/* DMA issued */
		dma_issued = true;
	पूर्ण अन्यथा अणु
		/* set current transfer inक्रमmation */
		pic32s->tx = (स्थिर व्योम *)transfer->tx_buf;
		pic32s->rx = (स्थिर व्योम *)transfer->rx_buf;
		pic32s->tx_end = pic32s->tx + transfer->len;
		pic32s->rx_end = pic32s->rx + transfer->len;
		pic32s->len = transfer->len;

		/* transact by पूर्णांकerrupt driven PIO */
		enable_irq(pic32s->fault_irq);
		enable_irq(pic32s->rx_irq);
		enable_irq(pic32s->tx_irq);
	पूर्ण

	/* रुको क्रम completion */
	समयout = रुको_क्रम_completion_समयout(&pic32s->xfer_करोne, 2 * HZ);
	अगर (समयout == 0) अणु
		dev_err(&spi->dev, "wait error/timedout\n");
		अगर (dma_issued) अणु
			dmaengine_terminate_all(master->dma_rx);
			dmaengine_terminate_all(master->dma_tx);
		पूर्ण
		ret = -ETIMEDOUT;
	पूर्ण अन्यथा अणु
		ret = 0;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक pic32_spi_unprepare_message(काष्ठा spi_master *master,
				       काष्ठा spi_message *msg)
अणु
	/* nothing to करो */
	वापस 0;
पूर्ण

अटल पूर्णांक pic32_spi_unprepare_hardware(काष्ठा spi_master *master)
अणु
	काष्ठा pic32_spi *pic32s = spi_master_get_devdata(master);

	pic32_spi_disable(pic32s);

	वापस 0;
पूर्ण

/* This may be called multiple बार by same spi dev */
अटल पूर्णांक pic32_spi_setup(काष्ठा spi_device *spi)
अणु
	अगर (!spi->max_speed_hz) अणु
		dev_err(&spi->dev, "No max speed HZ parameter\n");
		वापस -EINVAL;
	पूर्ण

	/* PIC32 spi controller can drive /CS during transfer depending
	 * on tx fअगरo fill-level. /CS will stay निश्चितed as दीर्घ as TX
	 * fअगरo is non-empty, अन्यथा will be deनिश्चितed indicating
	 * completion of the ongoing transfer. This might result पूर्णांकo
	 * unreliable/erroneous SPI transactions.
	 * To aव्योम that we will always handle /CS by toggling GPIO.
	 */
	अगर (!gpio_is_valid(spi->cs_gpio))
		वापस -EINVAL;

	gpio_direction_output(spi->cs_gpio, !(spi->mode & SPI_CS_HIGH));

	वापस 0;
पूर्ण

अटल व्योम pic32_spi_cleanup(काष्ठा spi_device *spi)
अणु
	/* de-activate cs-gpio */
	gpio_direction_output(spi->cs_gpio, !(spi->mode & SPI_CS_HIGH));
पूर्ण

अटल पूर्णांक pic32_spi_dma_prep(काष्ठा pic32_spi *pic32s, काष्ठा device *dev)
अणु
	काष्ठा spi_master *master = pic32s->master;
	पूर्णांक ret = 0;

	master->dma_rx = dma_request_chan(dev, "spi-rx");
	अगर (IS_ERR(master->dma_rx)) अणु
		अगर (PTR_ERR(master->dma_rx) == -EPROBE_DEFER)
			ret = -EPROBE_DEFER;
		अन्यथा
			dev_warn(dev, "RX channel not found.\n");

		master->dma_rx = शून्य;
		जाओ out_err;
	पूर्ण

	master->dma_tx = dma_request_chan(dev, "spi-tx");
	अगर (IS_ERR(master->dma_tx)) अणु
		अगर (PTR_ERR(master->dma_tx) == -EPROBE_DEFER)
			ret = -EPROBE_DEFER;
		अन्यथा
			dev_warn(dev, "TX channel not found.\n");

		master->dma_tx = शून्य;
		जाओ out_err;
	पूर्ण

	अगर (pic32_spi_dma_config(pic32s, DMA_SLAVE_BUSWIDTH_1_BYTE))
		जाओ out_err;

	/* DMA chnls allocated and prepared */
	set_bit(PIC32F_DMA_PREP, &pic32s->flags);

	वापस 0;

out_err:
	अगर (master->dma_rx) अणु
		dma_release_channel(master->dma_rx);
		master->dma_rx = शून्य;
	पूर्ण

	अगर (master->dma_tx) अणु
		dma_release_channel(master->dma_tx);
		master->dma_tx = शून्य;
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम pic32_spi_dma_unprep(काष्ठा pic32_spi *pic32s)
अणु
	अगर (!test_bit(PIC32F_DMA_PREP, &pic32s->flags))
		वापस;

	clear_bit(PIC32F_DMA_PREP, &pic32s->flags);
	अगर (pic32s->master->dma_rx)
		dma_release_channel(pic32s->master->dma_rx);

	अगर (pic32s->master->dma_tx)
		dma_release_channel(pic32s->master->dma_tx);
पूर्ण

अटल व्योम pic32_spi_hw_init(काष्ठा pic32_spi *pic32s)
अणु
	u32 ctrl;

	/* disable hardware */
	pic32_spi_disable(pic32s);

	ctrl = पढ़ोl(&pic32s->regs->ctrl);
	/* enable enhanced fअगरo of 128bit deep */
	ctrl |= CTRL_ENHBUF;
	pic32s->fअगरo_n_byte = 16;

	/* disable framing mode */
	ctrl &= ~CTRL_FRMEN;

	/* enable master mode जबतक disabled */
	ctrl |= CTRL_MSTEN;

	/* set tx fअगरo threshold पूर्णांकerrupt */
	ctrl &= ~(0x3 << CTRL_TX_INT_SHIFT);
	ctrl |= (TX_FIFO_HALF_EMPTY << CTRL_TX_INT_SHIFT);

	/* set rx fअगरo threshold पूर्णांकerrupt */
	ctrl &= ~(0x3 << CTRL_RX_INT_SHIFT);
	ctrl |= (RX_FIFO_NOT_EMPTY << CTRL_RX_INT_SHIFT);

	/* select clk source */
	ctrl &= ~CTRL_MCLKSEL;

	/* set manual /CS mode */
	ctrl &= ~CTRL_MSSEN;

	ग_लिखोl(ctrl, &pic32s->regs->ctrl);

	/* enable error reporting */
	ctrl = CTRL2_TX_UR_EN | CTRL2_RX_OV_EN | CTRL2_FRM_ERR_EN;
	ग_लिखोl(ctrl, &pic32s->regs->ctrl2_set);
पूर्ण

अटल पूर्णांक pic32_spi_hw_probe(काष्ठा platक्रमm_device *pdev,
			      काष्ठा pic32_spi *pic32s)
अणु
	काष्ठा resource *mem;
	पूर्णांक ret;

	mem = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	pic32s->regs = devm_ioremap_resource(&pdev->dev, mem);
	अगर (IS_ERR(pic32s->regs))
		वापस PTR_ERR(pic32s->regs);

	pic32s->dma_base = mem->start;

	/* get irq resources: err-irq, rx-irq, tx-irq */
	pic32s->fault_irq = platक्रमm_get_irq_byname(pdev, "fault");
	अगर (pic32s->fault_irq < 0)
		वापस pic32s->fault_irq;

	pic32s->rx_irq = platक्रमm_get_irq_byname(pdev, "rx");
	अगर (pic32s->rx_irq < 0)
		वापस pic32s->rx_irq;

	pic32s->tx_irq = platक्रमm_get_irq_byname(pdev, "tx");
	अगर (pic32s->tx_irq < 0)
		वापस pic32s->tx_irq;

	/* get घड़ी */
	pic32s->clk = devm_clk_get(&pdev->dev, "mck0");
	अगर (IS_ERR(pic32s->clk)) अणु
		dev_err(&pdev->dev, "clk not found\n");
		ret = PTR_ERR(pic32s->clk);
		जाओ err_unmap_mem;
	पूर्ण

	ret = clk_prepare_enable(pic32s->clk);
	अगर (ret)
		जाओ err_unmap_mem;

	pic32_spi_hw_init(pic32s);

	वापस 0;

err_unmap_mem:
	dev_err(&pdev->dev, "%s failed, err %d\n", __func__, ret);
	वापस ret;
पूर्ण

अटल पूर्णांक pic32_spi_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा spi_master *master;
	काष्ठा pic32_spi *pic32s;
	पूर्णांक ret;

	master = spi_alloc_master(&pdev->dev, माप(*pic32s));
	अगर (!master)
		वापस -ENOMEM;

	pic32s = spi_master_get_devdata(master);
	pic32s->master = master;

	ret = pic32_spi_hw_probe(pdev, pic32s);
	अगर (ret)
		जाओ err_master;

	master->dev.of_node	= pdev->dev.of_node;
	master->mode_bits	= SPI_MODE_3 | SPI_MODE_0 | SPI_CS_HIGH;
	master->num_chipselect	= 1; /* single chip-select */
	master->max_speed_hz	= clk_get_rate(pic32s->clk);
	master->setup		= pic32_spi_setup;
	master->cleanup		= pic32_spi_cleanup;
	master->flags		= SPI_MASTER_MUST_TX | SPI_MASTER_MUST_RX;
	master->bits_per_word_mask	= SPI_BPW_MASK(8) | SPI_BPW_MASK(16) |
					  SPI_BPW_MASK(32);
	master->transfer_one		= pic32_spi_one_transfer;
	master->prepare_message		= pic32_spi_prepare_message;
	master->unprepare_message	= pic32_spi_unprepare_message;
	master->prepare_transfer_hardware	= pic32_spi_prepare_hardware;
	master->unprepare_transfer_hardware	= pic32_spi_unprepare_hardware;

	/* optional DMA support */
	ret = pic32_spi_dma_prep(pic32s, &pdev->dev);
	अगर (ret)
		जाओ err_bailout;

	अगर (test_bit(PIC32F_DMA_PREP, &pic32s->flags))
		master->can_dma	= pic32_spi_can_dma;

	init_completion(&pic32s->xfer_करोne);
	pic32s->mode = -1;

	/* install irq handlers (with irq-disabled) */
	irq_set_status_flags(pic32s->fault_irq, IRQ_NOAUTOEN);
	ret = devm_request_irq(&pdev->dev, pic32s->fault_irq,
			       pic32_spi_fault_irq, IRQF_NO_THREAD,
			       dev_name(&pdev->dev), pic32s);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "request fault-irq %d\n", pic32s->rx_irq);
		जाओ err_bailout;
	पूर्ण

	/* receive पूर्णांकerrupt handler */
	irq_set_status_flags(pic32s->rx_irq, IRQ_NOAUTOEN);
	ret = devm_request_irq(&pdev->dev, pic32s->rx_irq,
			       pic32_spi_rx_irq, IRQF_NO_THREAD,
			       dev_name(&pdev->dev), pic32s);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "request rx-irq %d\n", pic32s->rx_irq);
		जाओ err_bailout;
	पूर्ण

	/* transmit पूर्णांकerrupt handler */
	irq_set_status_flags(pic32s->tx_irq, IRQ_NOAUTOEN);
	ret = devm_request_irq(&pdev->dev, pic32s->tx_irq,
			       pic32_spi_tx_irq, IRQF_NO_THREAD,
			       dev_name(&pdev->dev), pic32s);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "request tx-irq %d\n", pic32s->tx_irq);
		जाओ err_bailout;
	पूर्ण

	/* रेजिस्टर master */
	ret = devm_spi_रेजिस्टर_master(&pdev->dev, master);
	अगर (ret) अणु
		dev_err(&master->dev, "failed registering spi master\n");
		जाओ err_bailout;
	पूर्ण

	platक्रमm_set_drvdata(pdev, pic32s);

	वापस 0;

err_bailout:
	pic32_spi_dma_unprep(pic32s);
	clk_disable_unprepare(pic32s->clk);
err_master:
	spi_master_put(master);
	वापस ret;
पूर्ण

अटल पूर्णांक pic32_spi_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा pic32_spi *pic32s;

	pic32s = platक्रमm_get_drvdata(pdev);
	pic32_spi_disable(pic32s);
	clk_disable_unprepare(pic32s->clk);
	pic32_spi_dma_unprep(pic32s);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id pic32_spi_of_match[] = अणु
	अणु.compatible = "microchip,pic32mzda-spi",पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, pic32_spi_of_match);

अटल काष्ठा platक्रमm_driver pic32_spi_driver = अणु
	.driver = अणु
		.name = "spi-pic32",
		.of_match_table = of_match_ptr(pic32_spi_of_match),
	पूर्ण,
	.probe = pic32_spi_probe,
	.हटाओ = pic32_spi_हटाओ,
पूर्ण;

module_platक्रमm_driver(pic32_spi_driver);

MODULE_AUTHOR("Purna Chandra Mandal <purna.mandal@microchip.com>");
MODULE_DESCRIPTION("Microchip SPI driver for PIC32 SPI controller.");
MODULE_LICENSE("GPL v2");
