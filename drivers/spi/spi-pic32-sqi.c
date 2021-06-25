<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * PIC32 Quad SPI controller driver.
 *
 * Purna Chandra Mandal <purna.mandal@microchip.com>
 * Copyright (c) 2016, Microchip Technology Inc.
 */

#समावेश <linux/clk.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/iopoll.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/spi/spi.h>

/* SQI रेजिस्टरs */
#घोषणा PESQI_XIP_CONF1_REG	0x00
#घोषणा PESQI_XIP_CONF2_REG	0x04
#घोषणा PESQI_CONF_REG		0x08
#घोषणा PESQI_CTRL_REG		0x0C
#घोषणा PESQI_CLK_CTRL_REG	0x10
#घोषणा PESQI_CMD_THRES_REG	0x14
#घोषणा PESQI_INT_THRES_REG	0x18
#घोषणा PESQI_INT_ENABLE_REG	0x1C
#घोषणा PESQI_INT_STAT_REG	0x20
#घोषणा PESQI_TX_DATA_REG	0x24
#घोषणा PESQI_RX_DATA_REG	0x28
#घोषणा PESQI_STAT1_REG		0x2C
#घोषणा PESQI_STAT2_REG		0x30
#घोषणा PESQI_BD_CTRL_REG	0x34
#घोषणा PESQI_BD_CUR_ADDR_REG	0x38
#घोषणा PESQI_BD_BASE_ADDR_REG	0x40
#घोषणा PESQI_BD_STAT_REG	0x44
#घोषणा PESQI_BD_POLL_CTRL_REG	0x48
#घोषणा PESQI_BD_TX_DMA_STAT_REG	0x4C
#घोषणा PESQI_BD_RX_DMA_STAT_REG	0x50
#घोषणा PESQI_THRES_REG		0x54
#घोषणा PESQI_INT_SIGEN_REG	0x58

/* PESQI_CONF_REG fields */
#घोषणा PESQI_MODE		0x7
#घोषणा  PESQI_MODE_BOOT	0
#घोषणा  PESQI_MODE_PIO		1
#घोषणा  PESQI_MODE_DMA		2
#घोषणा  PESQI_MODE_XIP		3
#घोषणा PESQI_MODE_SHIFT	0
#घोषणा PESQI_CPHA		BIT(3)
#घोषणा PESQI_CPOL		BIT(4)
#घोषणा PESQI_LSBF		BIT(5)
#घोषणा PESQI_RXLATCH		BIT(7)
#घोषणा PESQI_SERMODE		BIT(8)
#घोषणा PESQI_WP_EN		BIT(9)
#घोषणा PESQI_HOLD_EN		BIT(10)
#घोषणा PESQI_BURST_EN		BIT(12)
#घोषणा PESQI_CS_CTRL_HW	BIT(15)
#घोषणा PESQI_SOFT_RESET	BIT(16)
#घोषणा PESQI_LANES_SHIFT	20
#घोषणा  PESQI_SINGLE_LANE	0
#घोषणा  PESQI_DUAL_LANE	1
#घोषणा  PESQI_QUAD_LANE	2
#घोषणा PESQI_CSEN_SHIFT	24
#घोषणा PESQI_EN		BIT(23)

/* PESQI_CLK_CTRL_REG fields */
#घोषणा PESQI_CLK_EN		BIT(0)
#घोषणा PESQI_CLK_STABLE	BIT(1)
#घोषणा PESQI_CLKDIV_SHIFT	8
#घोषणा PESQI_CLKDIV		0xff

/* PESQI_INT_THR/CMD_THR_REG */
#घोषणा PESQI_TXTHR_MASK	0x1f
#घोषणा PESQI_TXTHR_SHIFT	8
#घोषणा PESQI_RXTHR_MASK	0x1f
#घोषणा PESQI_RXTHR_SHIFT	0

/* PESQI_INT_EN/INT_STAT/INT_SIG_EN_REG */
#घोषणा PESQI_TXEMPTY		BIT(0)
#घोषणा PESQI_TXFULL		BIT(1)
#घोषणा PESQI_TXTHR		BIT(2)
#घोषणा PESQI_RXEMPTY		BIT(3)
#घोषणा PESQI_RXFULL		BIT(4)
#घोषणा PESQI_RXTHR		BIT(5)
#घोषणा PESQI_BDDONE		BIT(9)  /* BD processing complete */
#घोषणा PESQI_PKTCOMP		BIT(10) /* packet processing complete */
#घोषणा PESQI_DMAERR		BIT(11) /* error */

/* PESQI_BD_CTRL_REG */
#घोषणा PESQI_DMA_EN		BIT(0) /* enable DMA engine */
#घोषणा PESQI_POLL_EN		BIT(1) /* enable polling */
#घोषणा PESQI_BDP_START		BIT(2) /* start BD processor */

/* PESQI controller buffer descriptor */
काष्ठा buf_desc अणु
	u32 bd_ctrl;	/* control */
	u32 bd_status;	/* reserved */
	u32 bd_addr;	/* DMA buffer addr */
	u32 bd_nextp;	/* next item in chain */
पूर्ण;

/* bd_ctrl */
#घोषणा BD_BUFLEN		0x1ff
#घोषणा BD_CBD_INT_EN		BIT(16)	/* Current BD is processed */
#घोषणा BD_PKT_INT_EN		BIT(17) /* All BDs of PKT processed */
#घोषणा BD_LIFM			BIT(18) /* last data of pkt */
#घोषणा BD_LAST			BIT(19) /* end of list */
#घोषणा BD_DATA_RECV		BIT(20) /* receive data */
#घोषणा BD_DDR			BIT(21) /* DDR mode */
#घोषणा BD_DUAL			BIT(22)	/* Dual SPI */
#घोषणा BD_QUAD			BIT(23) /* Quad SPI */
#घोषणा BD_LSBF			BIT(25)	/* LSB First */
#घोषणा BD_STAT_CHECK		BIT(27) /* Status poll */
#घोषणा BD_DEVSEL_SHIFT		28	/* CS */
#घोषणा BD_CS_DEASSERT		BIT(30) /* de-निश्चित CS after current BD */
#घोषणा BD_EN			BIT(31) /* BD owned by H/W */

/**
 * काष्ठा ring_desc - Representation of SQI ring descriptor
 * @list:	list element to add to मुक्त or used list.
 * @bd:		PESQI controller buffer descriptor
 * @bd_dma:	DMA address of PESQI controller buffer descriptor
 * @xfer_len:	transfer length
 */
काष्ठा ring_desc अणु
	काष्ठा list_head list;
	काष्ठा buf_desc *bd;
	dma_addr_t bd_dma;
	u32 xfer_len;
पूर्ण;

/* Global स्थिरants */
#घोषणा PESQI_BD_BUF_LEN_MAX	256
#घोषणा PESQI_BD_COUNT		256 /* max 64KB data per spi message */

काष्ठा pic32_sqi अणु
	व्योम __iomem		*regs;
	काष्ठा clk		*sys_clk;
	काष्ठा clk		*base_clk; /* drives spi घड़ी */
	काष्ठा spi_master	*master;
	पूर्णांक			irq;
	काष्ठा completion	xfer_करोne;
	काष्ठा ring_desc	*ring;
	व्योम			*bd;
	dma_addr_t		bd_dma;
	काष्ठा list_head	bd_list_मुक्त; /* मुक्त */
	काष्ठा list_head	bd_list_used; /* allocated */
	काष्ठा spi_device	*cur_spi;
	u32			cur_speed;
	u8			cur_mode;
पूर्ण;

अटल अंतरभूत व्योम pic32_setbits(व्योम __iomem *reg, u32 set)
अणु
	ग_लिखोl(पढ़ोl(reg) | set, reg);
पूर्ण

अटल अंतरभूत व्योम pic32_clrbits(व्योम __iomem *reg, u32 clr)
अणु
	ग_लिखोl(पढ़ोl(reg) & ~clr, reg);
पूर्ण

अटल पूर्णांक pic32_sqi_set_clk_rate(काष्ठा pic32_sqi *sqi, u32 sck)
अणु
	u32 val, भाग;

	/* भाग = base_clk / (2 * spi_clk) */
	भाग = clk_get_rate(sqi->base_clk) / (2 * sck);
	भाग &= PESQI_CLKDIV;

	val = पढ़ोl(sqi->regs + PESQI_CLK_CTRL_REG);
	/* apply new भागider */
	val &= ~(PESQI_CLK_STABLE | (PESQI_CLKDIV << PESQI_CLKDIV_SHIFT));
	val |= भाग << PESQI_CLKDIV_SHIFT;
	ग_लिखोl(val, sqi->regs + PESQI_CLK_CTRL_REG);

	/* रुको क्रम stability */
	वापस पढ़ोl_poll_समयout(sqi->regs + PESQI_CLK_CTRL_REG, val,
				  val & PESQI_CLK_STABLE, 1, 5000);
पूर्ण

अटल अंतरभूत व्योम pic32_sqi_enable_पूर्णांक(काष्ठा pic32_sqi *sqi)
अणु
	u32 mask = PESQI_DMAERR | PESQI_BDDONE | PESQI_PKTCOMP;

	ग_लिखोl(mask, sqi->regs + PESQI_INT_ENABLE_REG);
	/* INT_SIGEN works as पूर्णांकerrupt-gate to INTR line */
	ग_लिखोl(mask, sqi->regs + PESQI_INT_SIGEN_REG);
पूर्ण

अटल अंतरभूत व्योम pic32_sqi_disable_पूर्णांक(काष्ठा pic32_sqi *sqi)
अणु
	ग_लिखोl(0, sqi->regs + PESQI_INT_ENABLE_REG);
	ग_लिखोl(0, sqi->regs + PESQI_INT_SIGEN_REG);
पूर्ण

अटल irqवापस_t pic32_sqi_isr(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा pic32_sqi *sqi = dev_id;
	u32 enable, status;

	enable = पढ़ोl(sqi->regs + PESQI_INT_ENABLE_REG);
	status = पढ़ोl(sqi->regs + PESQI_INT_STAT_REG);

	/* check spurious पूर्णांकerrupt */
	अगर (!status)
		वापस IRQ_NONE;

	अगर (status & PESQI_DMAERR) अणु
		enable = 0;
		जाओ irq_करोne;
	पूर्ण

	अगर (status & PESQI_TXTHR)
		enable &= ~(PESQI_TXTHR | PESQI_TXFULL | PESQI_TXEMPTY);

	अगर (status & PESQI_RXTHR)
		enable &= ~(PESQI_RXTHR | PESQI_RXFULL | PESQI_RXEMPTY);

	अगर (status & PESQI_BDDONE)
		enable &= ~PESQI_BDDONE;

	/* packet processing completed */
	अगर (status & PESQI_PKTCOMP) अणु
		/* mask all पूर्णांकerrupts */
		enable = 0;
		/* complete trasaction */
		complete(&sqi->xfer_करोne);
	पूर्ण

irq_करोne:
	/* पूर्णांकerrupts are sticky, so mask when handled */
	ग_लिखोl(enable, sqi->regs + PESQI_INT_ENABLE_REG);

	वापस IRQ_HANDLED;
पूर्ण

अटल काष्ठा ring_desc *ring_desc_get(काष्ठा pic32_sqi *sqi)
अणु
	काष्ठा ring_desc *rdesc;

	अगर (list_empty(&sqi->bd_list_मुक्त))
		वापस शून्य;

	rdesc = list_first_entry(&sqi->bd_list_मुक्त, काष्ठा ring_desc, list);
	list_move_tail(&rdesc->list, &sqi->bd_list_used);
	वापस rdesc;
पूर्ण

अटल व्योम ring_desc_put(काष्ठा pic32_sqi *sqi, काष्ठा ring_desc *rdesc)
अणु
	list_move(&rdesc->list, &sqi->bd_list_मुक्त);
पूर्ण

अटल पूर्णांक pic32_sqi_one_transfer(काष्ठा pic32_sqi *sqi,
				  काष्ठा spi_message *mesg,
				  काष्ठा spi_transfer *xfer)
अणु
	काष्ठा spi_device *spi = mesg->spi;
	काष्ठा scatterlist *sg, *sgl;
	काष्ठा ring_desc *rdesc;
	काष्ठा buf_desc *bd;
	पूर्णांक nents, i;
	u32 bd_ctrl;
	u32 nbits;

	/* Device selection */
	bd_ctrl = spi->chip_select << BD_DEVSEL_SHIFT;

	/* half-duplex: select transfer buffer, direction and lane */
	अगर (xfer->rx_buf) अणु
		bd_ctrl |= BD_DATA_RECV;
		nbits = xfer->rx_nbits;
		sgl = xfer->rx_sg.sgl;
		nents = xfer->rx_sg.nents;
	पूर्ण अन्यथा अणु
		nbits = xfer->tx_nbits;
		sgl = xfer->tx_sg.sgl;
		nents = xfer->tx_sg.nents;
	पूर्ण

	अगर (nbits & SPI_NBITS_QUAD)
		bd_ctrl |= BD_QUAD;
	अन्यथा अगर (nbits & SPI_NBITS_DUAL)
		bd_ctrl |= BD_DUAL;

	/* LSB first */
	अगर (spi->mode & SPI_LSB_FIRST)
		bd_ctrl |= BD_LSBF;

	/* ownership to hardware */
	bd_ctrl |= BD_EN;

	क्रम_each_sg(sgl, sg, nents, i) अणु
		/* get ring descriptor */
		rdesc = ring_desc_get(sqi);
		अगर (!rdesc)
			अवरोध;

		bd = rdesc->bd;

		/* BD CTRL: length */
		rdesc->xfer_len = sg_dma_len(sg);
		bd->bd_ctrl = bd_ctrl;
		bd->bd_ctrl |= rdesc->xfer_len;

		/* BD STAT */
		bd->bd_status = 0;

		/* BD BUFFER ADDRESS */
		bd->bd_addr = sg->dma_address;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक pic32_sqi_prepare_hardware(काष्ठा spi_master *master)
अणु
	काष्ठा pic32_sqi *sqi = spi_master_get_devdata(master);

	/* enable spi पूर्णांकerface */
	pic32_setbits(sqi->regs + PESQI_CONF_REG, PESQI_EN);
	/* enable spi clk */
	pic32_setbits(sqi->regs + PESQI_CLK_CTRL_REG, PESQI_CLK_EN);

	वापस 0;
पूर्ण

अटल bool pic32_sqi_can_dma(काष्ठा spi_master *master,
			      काष्ठा spi_device *spi,
			      काष्ठा spi_transfer *x)
अणु
	/* Do DMA irrespective of transfer size */
	वापस true;
पूर्ण

अटल पूर्णांक pic32_sqi_one_message(काष्ठा spi_master *master,
				 काष्ठा spi_message *msg)
अणु
	काष्ठा spi_device *spi = msg->spi;
	काष्ठा ring_desc *rdesc, *next;
	काष्ठा spi_transfer *xfer;
	काष्ठा pic32_sqi *sqi;
	पूर्णांक ret = 0, mode;
	अचिन्हित दीर्घ समयout;
	u32 val;

	sqi = spi_master_get_devdata(master);

	reinit_completion(&sqi->xfer_करोne);
	msg->actual_length = 0;

	/* We can't handle spi_transfer specअगरic "speed_hz", "bits_per_word"
	 * and "delay_usecs". But spi_device specअगरic speed and mode change
	 * can be handled at best during spi chip-select चयन.
	 */
	अगर (sqi->cur_spi != spi) अणु
		/* set spi speed */
		अगर (sqi->cur_speed != spi->max_speed_hz) अणु
			sqi->cur_speed = spi->max_speed_hz;
			ret = pic32_sqi_set_clk_rate(sqi, spi->max_speed_hz);
			अगर (ret)
				dev_warn(&spi->dev, "set_clk, %d\n", ret);
		पूर्ण

		/* set spi mode */
		mode = spi->mode & (SPI_MODE_3 | SPI_LSB_FIRST);
		अगर (sqi->cur_mode != mode) अणु
			val = पढ़ोl(sqi->regs + PESQI_CONF_REG);
			val &= ~(PESQI_CPOL | PESQI_CPHA | PESQI_LSBF);
			अगर (mode & SPI_CPOL)
				val |= PESQI_CPOL;
			अगर (mode & SPI_LSB_FIRST)
				val |= PESQI_LSBF;
			val |= PESQI_CPHA;
			ग_लिखोl(val, sqi->regs + PESQI_CONF_REG);

			sqi->cur_mode = mode;
		पूर्ण
		sqi->cur_spi = spi;
	पूर्ण

	/* prepare hardware desc-list(BD) क्रम transfer(s) */
	list_क्रम_each_entry(xfer, &msg->transfers, transfer_list) अणु
		ret = pic32_sqi_one_transfer(sqi, msg, xfer);
		अगर (ret) अणु
			dev_err(&spi->dev, "xfer %p err\n", xfer);
			जाओ xfer_out;
		पूर्ण
	पूर्ण

	/* BDs are prepared and chained. Now mark LAST_BD, CS_DEASSERT at last
	 * element of the list.
	 */
	rdesc = list_last_entry(&sqi->bd_list_used, काष्ठा ring_desc, list);
	rdesc->bd->bd_ctrl |= BD_LAST | BD_CS_DEASSERT |
			      BD_LIFM | BD_PKT_INT_EN;

	/* set base address BD list क्रम DMA engine */
	rdesc = list_first_entry(&sqi->bd_list_used, काष्ठा ring_desc, list);
	ग_लिखोl(rdesc->bd_dma, sqi->regs + PESQI_BD_BASE_ADDR_REG);

	/* enable पूर्णांकerrupt */
	pic32_sqi_enable_पूर्णांक(sqi);

	/* enable DMA engine */
	val = PESQI_DMA_EN | PESQI_POLL_EN | PESQI_BDP_START;
	ग_लिखोl(val, sqi->regs + PESQI_BD_CTRL_REG);

	/* रुको क्रम xfer completion */
	समयout = रुको_क्रम_completion_समयout(&sqi->xfer_करोne, 5 * HZ);
	अगर (समयout == 0) अणु
		dev_err(&sqi->master->dev, "wait timedout/interrupted\n");
		ret = -ETIMEDOUT;
		msg->status = ret;
	पूर्ण अन्यथा अणु
		/* success */
		msg->status = 0;
		ret = 0;
	पूर्ण

	/* disable DMA */
	ग_लिखोl(0, sqi->regs + PESQI_BD_CTRL_REG);

	pic32_sqi_disable_पूर्णांक(sqi);

xfer_out:
	list_क्रम_each_entry_safe_reverse(rdesc, next,
					 &sqi->bd_list_used, list) अणु
		/* Update total byte transferred */
		msg->actual_length += rdesc->xfer_len;
		/* release ring descr */
		ring_desc_put(sqi, rdesc);
	पूर्ण
	spi_finalize_current_message(spi->master);

	वापस ret;
पूर्ण

अटल पूर्णांक pic32_sqi_unprepare_hardware(काष्ठा spi_master *master)
अणु
	काष्ठा pic32_sqi *sqi = spi_master_get_devdata(master);

	/* disable clk */
	pic32_clrbits(sqi->regs + PESQI_CLK_CTRL_REG, PESQI_CLK_EN);
	/* disable spi */
	pic32_clrbits(sqi->regs + PESQI_CONF_REG, PESQI_EN);

	वापस 0;
पूर्ण

अटल पूर्णांक ring_desc_ring_alloc(काष्ठा pic32_sqi *sqi)
अणु
	काष्ठा ring_desc *rdesc;
	काष्ठा buf_desc *bd;
	पूर्णांक i;

	/* allocate coherent DMAable memory क्रम hardware buffer descriptors. */
	sqi->bd = dma_alloc_coherent(&sqi->master->dev,
				     माप(*bd) * PESQI_BD_COUNT,
				     &sqi->bd_dma, GFP_KERNEL);
	अगर (!sqi->bd) अणु
		dev_err(&sqi->master->dev, "failed allocating dma buffer\n");
		वापस -ENOMEM;
	पूर्ण

	/* allocate software ring descriptors */
	sqi->ring = kसुस्मृति(PESQI_BD_COUNT, माप(*rdesc), GFP_KERNEL);
	अगर (!sqi->ring) अणु
		dma_मुक्त_coherent(&sqi->master->dev,
				  माप(*bd) * PESQI_BD_COUNT,
				  sqi->bd, sqi->bd_dma);
		वापस -ENOMEM;
	पूर्ण

	bd = (काष्ठा buf_desc *)sqi->bd;

	INIT_LIST_HEAD(&sqi->bd_list_मुक्त);
	INIT_LIST_HEAD(&sqi->bd_list_used);

	/* initialize ring-desc */
	क्रम (i = 0, rdesc = sqi->ring; i < PESQI_BD_COUNT; i++, rdesc++) अणु
		INIT_LIST_HEAD(&rdesc->list);
		rdesc->bd = &bd[i];
		rdesc->bd_dma = sqi->bd_dma + (व्योम *)&bd[i] - (व्योम *)bd;
		list_add_tail(&rdesc->list, &sqi->bd_list_मुक्त);
	पूर्ण

	/* Prepare BD: chain to next BD(s) */
	क्रम (i = 0, rdesc = sqi->ring; i < PESQI_BD_COUNT - 1; i++)
		bd[i].bd_nextp = rdesc[i + 1].bd_dma;
	bd[PESQI_BD_COUNT - 1].bd_nextp = 0;

	वापस 0;
पूर्ण

अटल व्योम ring_desc_ring_मुक्त(काष्ठा pic32_sqi *sqi)
अणु
	dma_मुक्त_coherent(&sqi->master->dev,
			  माप(काष्ठा buf_desc) * PESQI_BD_COUNT,
			  sqi->bd, sqi->bd_dma);
	kमुक्त(sqi->ring);
पूर्ण

अटल व्योम pic32_sqi_hw_init(काष्ठा pic32_sqi *sqi)
अणु
	अचिन्हित दीर्घ flags;
	u32 val;

	/* Soft-reset of PESQI controller triggers पूर्णांकerrupt.
	 * We are not yet पढ़ोy to handle them so disable CPU
	 * पूर्णांकerrupt क्रम the समय being.
	 */
	local_irq_save(flags);

	/* निश्चित soft-reset */
	ग_लिखोl(PESQI_SOFT_RESET, sqi->regs + PESQI_CONF_REG);

	/* रुको until clear */
	पढ़ोl_poll_समयout_atomic(sqi->regs + PESQI_CONF_REG, val,
				  !(val & PESQI_SOFT_RESET), 1, 5000);

	/* disable all पूर्णांकerrupts */
	pic32_sqi_disable_पूर्णांक(sqi);

	/* Now it is safe to enable back CPU पूर्णांकerrupt */
	local_irq_restore(flags);

	/* tx and rx fअगरo पूर्णांकerrupt threshold */
	val = पढ़ोl(sqi->regs + PESQI_CMD_THRES_REG);
	val &= ~(PESQI_TXTHR_MASK << PESQI_TXTHR_SHIFT);
	val &= ~(PESQI_RXTHR_MASK << PESQI_RXTHR_SHIFT);
	val |= (1U << PESQI_TXTHR_SHIFT) | (1U << PESQI_RXTHR_SHIFT);
	ग_लिखोl(val, sqi->regs + PESQI_CMD_THRES_REG);

	val = पढ़ोl(sqi->regs + PESQI_INT_THRES_REG);
	val &= ~(PESQI_TXTHR_MASK << PESQI_TXTHR_SHIFT);
	val &= ~(PESQI_RXTHR_MASK << PESQI_RXTHR_SHIFT);
	val |= (1U << PESQI_TXTHR_SHIFT) | (1U << PESQI_RXTHR_SHIFT);
	ग_लिखोl(val, sqi->regs + PESQI_INT_THRES_REG);

	/* शेष configuration */
	val = पढ़ोl(sqi->regs + PESQI_CONF_REG);

	/* set mode: DMA */
	val &= ~PESQI_MODE;
	val |= PESQI_MODE_DMA << PESQI_MODE_SHIFT;
	ग_लिखोl(val, sqi->regs + PESQI_CONF_REG);

	/* DATAEN - SQIID0-ID3 */
	val |= PESQI_QUAD_LANE << PESQI_LANES_SHIFT;

	/* burst/INCR4 enable */
	val |= PESQI_BURST_EN;

	/* CSEN - all CS */
	val |= 3U << PESQI_CSEN_SHIFT;
	ग_लिखोl(val, sqi->regs + PESQI_CONF_REG);

	/* ग_लिखो poll count */
	ग_लिखोl(0, sqi->regs + PESQI_BD_POLL_CTRL_REG);

	sqi->cur_speed = 0;
	sqi->cur_mode = -1;
पूर्ण

अटल पूर्णांक pic32_sqi_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा spi_master *master;
	काष्ठा pic32_sqi *sqi;
	पूर्णांक ret;

	master = spi_alloc_master(&pdev->dev, माप(*sqi));
	अगर (!master)
		वापस -ENOMEM;

	sqi = spi_master_get_devdata(master);
	sqi->master = master;

	sqi->regs = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(sqi->regs)) अणु
		ret = PTR_ERR(sqi->regs);
		जाओ err_मुक्त_master;
	पूर्ण

	/* irq */
	sqi->irq = platक्रमm_get_irq(pdev, 0);
	अगर (sqi->irq < 0) अणु
		ret = sqi->irq;
		जाओ err_मुक्त_master;
	पूर्ण

	/* घड़ीs */
	sqi->sys_clk = devm_clk_get(&pdev->dev, "reg_ck");
	अगर (IS_ERR(sqi->sys_clk)) अणु
		ret = PTR_ERR(sqi->sys_clk);
		dev_err(&pdev->dev, "no sys_clk ?\n");
		जाओ err_मुक्त_master;
	पूर्ण

	sqi->base_clk = devm_clk_get(&pdev->dev, "spi_ck");
	अगर (IS_ERR(sqi->base_clk)) अणु
		ret = PTR_ERR(sqi->base_clk);
		dev_err(&pdev->dev, "no base clk ?\n");
		जाओ err_मुक्त_master;
	पूर्ण

	ret = clk_prepare_enable(sqi->sys_clk);
	अगर (ret) अणु
		dev_err(&pdev->dev, "sys clk enable failed\n");
		जाओ err_मुक्त_master;
	पूर्ण

	ret = clk_prepare_enable(sqi->base_clk);
	अगर (ret) अणु
		dev_err(&pdev->dev, "base clk enable failed\n");
		clk_disable_unprepare(sqi->sys_clk);
		जाओ err_मुक्त_master;
	पूर्ण

	init_completion(&sqi->xfer_करोne);

	/* initialize hardware */
	pic32_sqi_hw_init(sqi);

	/* allocate buffers & descriptors */
	ret = ring_desc_ring_alloc(sqi);
	अगर (ret) अणु
		dev_err(&pdev->dev, "ring alloc failed\n");
		जाओ err_disable_clk;
	पूर्ण

	/* install irq handlers */
	ret = request_irq(sqi->irq, pic32_sqi_isr, 0,
			  dev_name(&pdev->dev), sqi);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "request_irq(%d), failed\n", sqi->irq);
		जाओ err_मुक्त_ring;
	पूर्ण

	/* रेजिस्टर master */
	master->num_chipselect	= 2;
	master->max_speed_hz	= clk_get_rate(sqi->base_clk);
	master->dma_alignment	= 32;
	master->max_dma_len	= PESQI_BD_BUF_LEN_MAX;
	master->dev.of_node	= pdev->dev.of_node;
	master->mode_bits	= SPI_MODE_3 | SPI_MODE_0 | SPI_TX_DUAL |
				  SPI_RX_DUAL | SPI_TX_QUAD | SPI_RX_QUAD;
	master->flags		= SPI_MASTER_HALF_DUPLEX;
	master->can_dma		= pic32_sqi_can_dma;
	master->bits_per_word_mask	= SPI_BPW_RANGE_MASK(8, 32);
	master->transfer_one_message	= pic32_sqi_one_message;
	master->prepare_transfer_hardware	= pic32_sqi_prepare_hardware;
	master->unprepare_transfer_hardware	= pic32_sqi_unprepare_hardware;

	ret = devm_spi_रेजिस्टर_master(&pdev->dev, master);
	अगर (ret) अणु
		dev_err(&master->dev, "failed registering spi master\n");
		मुक्त_irq(sqi->irq, sqi);
		जाओ err_मुक्त_ring;
	पूर्ण

	platक्रमm_set_drvdata(pdev, sqi);

	वापस 0;

err_मुक्त_ring:
	ring_desc_ring_मुक्त(sqi);

err_disable_clk:
	clk_disable_unprepare(sqi->base_clk);
	clk_disable_unprepare(sqi->sys_clk);

err_मुक्त_master:
	spi_master_put(master);
	वापस ret;
पूर्ण

अटल पूर्णांक pic32_sqi_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा pic32_sqi *sqi = platक्रमm_get_drvdata(pdev);

	/* release resources */
	मुक्त_irq(sqi->irq, sqi);
	ring_desc_ring_मुक्त(sqi);

	/* disable clk */
	clk_disable_unprepare(sqi->base_clk);
	clk_disable_unprepare(sqi->sys_clk);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id pic32_sqi_of_ids[] = अणु
	अणु.compatible = "microchip,pic32mzda-sqi",पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, pic32_sqi_of_ids);

अटल काष्ठा platक्रमm_driver pic32_sqi_driver = अणु
	.driver = अणु
		.name = "sqi-pic32",
		.of_match_table = of_match_ptr(pic32_sqi_of_ids),
	पूर्ण,
	.probe = pic32_sqi_probe,
	.हटाओ = pic32_sqi_हटाओ,
पूर्ण;

module_platक्रमm_driver(pic32_sqi_driver);

MODULE_AUTHOR("Purna Chandra Mandal <purna.mandal@microchip.com>");
MODULE_DESCRIPTION("Microchip SPI driver for PIC32 SQI controller.");
MODULE_LICENSE("GPL v2");
