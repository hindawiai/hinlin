<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2013-2014 Renesas Electronics Europe Ltd.
 * Author: Guennadi Liakhovetski <g.liakhovetski@gmx.de>
 */

#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/dmaengine.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/log2.h>
#समावेश <linux/mmc/host.h>
#समावेश <linux/mmc/mmc.h>
#समावेश <linux/mmc/sd.h>
#समावेश <linux/mmc/sdपन.स>
#समावेश <linux/module.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/pinctrl/consumer.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/scatterlist.h>
#समावेश <linux/माला.स>
#समावेश <linux/समय.स>
#समावेश <linux/virtपन.स>
#समावेश <linux/workqueue.h>

#घोषणा USDHI6_SD_CMD		0x0000
#घोषणा USDHI6_SD_PORT_SEL	0x0004
#घोषणा USDHI6_SD_ARG		0x0008
#घोषणा USDHI6_SD_STOP		0x0010
#घोषणा USDHI6_SD_SECCNT	0x0014
#घोषणा USDHI6_SD_RSP10		0x0018
#घोषणा USDHI6_SD_RSP32		0x0020
#घोषणा USDHI6_SD_RSP54		0x0028
#घोषणा USDHI6_SD_RSP76		0x0030
#घोषणा USDHI6_SD_INFO1		0x0038
#घोषणा USDHI6_SD_INFO2		0x003c
#घोषणा USDHI6_SD_INFO1_MASK	0x0040
#घोषणा USDHI6_SD_INFO2_MASK	0x0044
#घोषणा USDHI6_SD_CLK_CTRL	0x0048
#घोषणा USDHI6_SD_SIZE		0x004c
#घोषणा USDHI6_SD_OPTION	0x0050
#घोषणा USDHI6_SD_ERR_STS1	0x0058
#घोषणा USDHI6_SD_ERR_STS2	0x005c
#घोषणा USDHI6_SD_BUF0		0x0060
#घोषणा USDHI6_SDIO_MODE	0x0068
#घोषणा USDHI6_SDIO_INFO1	0x006c
#घोषणा USDHI6_SDIO_INFO1_MASK	0x0070
#घोषणा USDHI6_CC_EXT_MODE	0x01b0
#घोषणा USDHI6_SOFT_RST		0x01c0
#घोषणा USDHI6_VERSION		0x01c4
#घोषणा USDHI6_HOST_MODE	0x01c8
#घोषणा USDHI6_SDIF_MODE	0x01cc

#घोषणा USDHI6_SD_CMD_APP		0x0040
#घोषणा USDHI6_SD_CMD_MODE_RSP_AUTO	0x0000
#घोषणा USDHI6_SD_CMD_MODE_RSP_NONE	0x0300
#घोषणा USDHI6_SD_CMD_MODE_RSP_R1	0x0400	/* Also R5, R6, R7 */
#घोषणा USDHI6_SD_CMD_MODE_RSP_R1B	0x0500	/* R1b */
#घोषणा USDHI6_SD_CMD_MODE_RSP_R2	0x0600
#घोषणा USDHI6_SD_CMD_MODE_RSP_R3	0x0700	/* Also R4 */
#घोषणा USDHI6_SD_CMD_DATA		0x0800
#घोषणा USDHI6_SD_CMD_READ		0x1000
#घोषणा USDHI6_SD_CMD_MULTI		0x2000
#घोषणा USDHI6_SD_CMD_CMD12_AUTO_OFF	0x4000

#घोषणा USDHI6_CC_EXT_MODE_SDRW		BIT(1)

#घोषणा USDHI6_SD_INFO1_RSP_END		BIT(0)
#घोषणा USDHI6_SD_INFO1_ACCESS_END	BIT(2)
#घोषणा USDHI6_SD_INFO1_CARD_OUT	BIT(3)
#घोषणा USDHI6_SD_INFO1_CARD_IN		BIT(4)
#घोषणा USDHI6_SD_INFO1_CD		BIT(5)
#घोषणा USDHI6_SD_INFO1_WP		BIT(7)
#घोषणा USDHI6_SD_INFO1_D3_CARD_OUT	BIT(8)
#घोषणा USDHI6_SD_INFO1_D3_CARD_IN	BIT(9)

#घोषणा USDHI6_SD_INFO2_CMD_ERR		BIT(0)
#घोषणा USDHI6_SD_INFO2_CRC_ERR		BIT(1)
#घोषणा USDHI6_SD_INFO2_END_ERR		BIT(2)
#घोषणा USDHI6_SD_INFO2_TOUT		BIT(3)
#घोषणा USDHI6_SD_INFO2_IWA_ERR		BIT(4)
#घोषणा USDHI6_SD_INFO2_IRA_ERR		BIT(5)
#घोषणा USDHI6_SD_INFO2_RSP_TOUT	BIT(6)
#घोषणा USDHI6_SD_INFO2_SDDAT0		BIT(7)
#घोषणा USDHI6_SD_INFO2_BRE		BIT(8)
#घोषणा USDHI6_SD_INFO2_BWE		BIT(9)
#घोषणा USDHI6_SD_INFO2_SCLKDIVEN	BIT(13)
#घोषणा USDHI6_SD_INFO2_CBSY		BIT(14)
#घोषणा USDHI6_SD_INFO2_ILA		BIT(15)

#घोषणा USDHI6_SD_INFO1_CARD_INSERT (USDHI6_SD_INFO1_CARD_IN | USDHI6_SD_INFO1_D3_CARD_IN)
#घोषणा USDHI6_SD_INFO1_CARD_EJECT (USDHI6_SD_INFO1_CARD_OUT | USDHI6_SD_INFO1_D3_CARD_OUT)
#घोषणा USDHI6_SD_INFO1_CARD (USDHI6_SD_INFO1_CARD_INSERT | USDHI6_SD_INFO1_CARD_EJECT)
#घोषणा USDHI6_SD_INFO1_CARD_CD (USDHI6_SD_INFO1_CARD_IN | USDHI6_SD_INFO1_CARD_OUT)

#घोषणा USDHI6_SD_INFO2_ERR	(USDHI6_SD_INFO2_CMD_ERR |	\
	USDHI6_SD_INFO2_CRC_ERR | USDHI6_SD_INFO2_END_ERR |	\
	USDHI6_SD_INFO2_TOUT | USDHI6_SD_INFO2_IWA_ERR |	\
	USDHI6_SD_INFO2_IRA_ERR | USDHI6_SD_INFO2_RSP_TOUT |	\
	USDHI6_SD_INFO2_ILA)

#घोषणा USDHI6_SD_INFO1_IRQ	(USDHI6_SD_INFO1_RSP_END | USDHI6_SD_INFO1_ACCESS_END | \
				 USDHI6_SD_INFO1_CARD)

#घोषणा USDHI6_SD_INFO2_IRQ	(USDHI6_SD_INFO2_ERR | USDHI6_SD_INFO2_BRE | \
				 USDHI6_SD_INFO2_BWE | 0x0800 | USDHI6_SD_INFO2_ILA)

#घोषणा USDHI6_SD_CLK_CTRL_SCLKEN	BIT(8)

#घोषणा USDHI6_SD_STOP_STP		BIT(0)
#घोषणा USDHI6_SD_STOP_SEC		BIT(8)

#घोषणा USDHI6_SDIO_INFO1_IOIRQ		BIT(0)
#घोषणा USDHI6_SDIO_INFO1_EXPUB52	BIT(14)
#घोषणा USDHI6_SDIO_INFO1_EXWT		BIT(15)

#घोषणा USDHI6_SD_ERR_STS1_CRC_NO_ERROR	BIT(13)

#घोषणा USDHI6_SOFT_RST_RESERVED	(BIT(1) | BIT(2))
#घोषणा USDHI6_SOFT_RST_RESET		BIT(0)

#घोषणा USDHI6_SD_OPTION_TIMEOUT_SHIFT	4
#घोषणा USDHI6_SD_OPTION_TIMEOUT_MASK	(0xf << USDHI6_SD_OPTION_TIMEOUT_SHIFT)
#घोषणा USDHI6_SD_OPTION_WIDTH_1	BIT(15)

#घोषणा USDHI6_SD_PORT_SEL_PORTS_SHIFT	8

#घोषणा USDHI6_SD_CLK_CTRL_DIV_MASK	0xff

#घोषणा USDHI6_SDIO_INFO1_IRQ	(USDHI6_SDIO_INFO1_IOIRQ | 3 | \
				 USDHI6_SDIO_INFO1_EXPUB52 | USDHI6_SDIO_INFO1_EXWT)

#घोषणा USDHI6_MIN_DMA 64

#घोषणा USDHI6_REQ_TIMEOUT_MS 4000

क्रमागत usdhi6_रुको_क्रम अणु
	USDHI6_WAIT_FOR_REQUEST,
	USDHI6_WAIT_FOR_CMD,
	USDHI6_WAIT_FOR_MREAD,
	USDHI6_WAIT_FOR_MWRITE,
	USDHI6_WAIT_FOR_READ,
	USDHI6_WAIT_FOR_WRITE,
	USDHI6_WAIT_FOR_DATA_END,
	USDHI6_WAIT_FOR_STOP,
	USDHI6_WAIT_FOR_DMA,
पूर्ण;

काष्ठा usdhi6_page अणु
	काष्ठा page *page;
	व्योम *mapped;		/* mapped page */
पूर्ण;

काष्ठा usdhi6_host अणु
	काष्ठा mmc_host *mmc;
	काष्ठा mmc_request *mrq;
	व्योम __iomem *base;
	काष्ठा clk *clk;

	/* SG memory handling */

	/* Common क्रम multiple and single block requests */
	काष्ठा usdhi6_page pg;	/* current page from an SG */
	व्योम *blk_page;		/* either a mapped page, or the bounce buffer */
	माप_प्रकार offset;		/* offset within a page, including sg->offset */

	/* Blocks, crossing a page boundary */
	माप_प्रकार head_len;
	काष्ठा usdhi6_page head_pg;

	/* A bounce buffer क्रम unaligned blocks or blocks, crossing a page boundary */
	काष्ठा scatterlist bounce_sg;
	u8 bounce_buf[512];

	/* Multiple block requests only */
	काष्ठा scatterlist *sg;	/* current SG segment */
	पूर्णांक page_idx;		/* page index within an SG segment */

	क्रमागत usdhi6_रुको_क्रम रुको;
	u32 status_mask;
	u32 status2_mask;
	u32 sdio_mask;
	u32 io_error;
	u32 irq_status;
	अचिन्हित दीर्घ imclk;
	अचिन्हित दीर्घ rate;
	bool app_cmd;

	/* Timeout handling */
	काष्ठा delayed_work समयout_work;
	अचिन्हित दीर्घ समयout;

	/* DMA support */
	काष्ठा dma_chan *chan_rx;
	काष्ठा dma_chan *chan_tx;
	bool dma_active;

	/* Pin control */
	काष्ठा pinctrl *pinctrl;
	काष्ठा pinctrl_state *pins_uhs;
पूर्ण;

/*			I/O primitives					*/

अटल व्योम usdhi6_ग_लिखो(काष्ठा usdhi6_host *host, u32 reg, u32 data)
अणु
	ioग_लिखो32(data, host->base + reg);
	dev_vdbg(mmc_dev(host->mmc), "%s(0x%p + 0x%x) = 0x%x\n", __func__,
		host->base, reg, data);
पूर्ण

अटल व्योम usdhi6_ग_लिखो16(काष्ठा usdhi6_host *host, u32 reg, u16 data)
अणु
	ioग_लिखो16(data, host->base + reg);
	dev_vdbg(mmc_dev(host->mmc), "%s(0x%p + 0x%x) = 0x%x\n", __func__,
		host->base, reg, data);
पूर्ण

अटल u32 usdhi6_पढ़ो(काष्ठा usdhi6_host *host, u32 reg)
अणु
	u32 data = ioपढ़ो32(host->base + reg);
	dev_vdbg(mmc_dev(host->mmc), "%s(0x%p + 0x%x) = 0x%x\n", __func__,
		host->base, reg, data);
	वापस data;
पूर्ण

अटल u16 usdhi6_पढ़ो16(काष्ठा usdhi6_host *host, u32 reg)
अणु
	u16 data = ioपढ़ो16(host->base + reg);
	dev_vdbg(mmc_dev(host->mmc), "%s(0x%p + 0x%x) = 0x%x\n", __func__,
		host->base, reg, data);
	वापस data;
पूर्ण

अटल व्योम usdhi6_irq_enable(काष्ठा usdhi6_host *host, u32 info1, u32 info2)
अणु
	host->status_mask = USDHI6_SD_INFO1_IRQ & ~info1;
	host->status2_mask = USDHI6_SD_INFO2_IRQ & ~info2;
	usdhi6_ग_लिखो(host, USDHI6_SD_INFO1_MASK, host->status_mask);
	usdhi6_ग_लिखो(host, USDHI6_SD_INFO2_MASK, host->status2_mask);
पूर्ण

अटल व्योम usdhi6_रुको_क्रम_resp(काष्ठा usdhi6_host *host)
अणु
	usdhi6_irq_enable(host, USDHI6_SD_INFO1_RSP_END |
			  USDHI6_SD_INFO1_ACCESS_END | USDHI6_SD_INFO1_CARD_CD,
			  USDHI6_SD_INFO2_ERR);
पूर्ण

अटल व्योम usdhi6_रुको_क्रम_brwe(काष्ठा usdhi6_host *host, bool पढ़ो)
अणु
	usdhi6_irq_enable(host, USDHI6_SD_INFO1_ACCESS_END |
			  USDHI6_SD_INFO1_CARD_CD, USDHI6_SD_INFO2_ERR |
			  (पढ़ो ? USDHI6_SD_INFO2_BRE : USDHI6_SD_INFO2_BWE));
पूर्ण

अटल व्योम usdhi6_only_cd(काष्ठा usdhi6_host *host)
अणु
	/* Mask all except card hotplug */
	usdhi6_irq_enable(host, USDHI6_SD_INFO1_CARD_CD, 0);
पूर्ण

अटल व्योम usdhi6_mask_all(काष्ठा usdhi6_host *host)
अणु
	usdhi6_irq_enable(host, 0, 0);
पूर्ण

अटल पूर्णांक usdhi6_error_code(काष्ठा usdhi6_host *host)
अणु
	u32 err;

	usdhi6_ग_लिखो(host, USDHI6_SD_STOP, USDHI6_SD_STOP_STP);

	अगर (host->io_error &
	    (USDHI6_SD_INFO2_RSP_TOUT | USDHI6_SD_INFO2_TOUT)) अणु
		u32 rsp54 = usdhi6_पढ़ो(host, USDHI6_SD_RSP54);
		पूर्णांक opc = host->mrq ? host->mrq->cmd->opcode : -1;

		err = usdhi6_पढ़ो(host, USDHI6_SD_ERR_STS2);
		/* Response समयout is often normal, करोn't spam the log */
		अगर (host->रुको == USDHI6_WAIT_FOR_CMD)
			dev_dbg(mmc_dev(host->mmc),
				"T-out sts 0x%x, resp 0x%x, state %u, CMD%d\n",
				err, rsp54, host->रुको, opc);
		अन्यथा
			dev_warn(mmc_dev(host->mmc),
				 "T-out sts 0x%x, resp 0x%x, state %u, CMD%d\n",
				 err, rsp54, host->रुको, opc);
		वापस -ETIMEDOUT;
	पूर्ण

	err = usdhi6_पढ़ो(host, USDHI6_SD_ERR_STS1);
	अगर (err != USDHI6_SD_ERR_STS1_CRC_NO_ERROR)
		dev_warn(mmc_dev(host->mmc), "Err sts 0x%x, state %u, CMD%d\n",
			 err, host->रुको, host->mrq ? host->mrq->cmd->opcode : -1);
	अगर (host->io_error & USDHI6_SD_INFO2_ILA)
		वापस -EILSEQ;

	वापस -EIO;
पूर्ण

/*			Scatter-Gather management			*/

/*
 * In PIO mode we have to map each page separately, using kmap(). That way
 * adjacent pages are mapped to non-adjacent भव addresses. That's why we
 * have to use a bounce buffer क्रम blocks, crossing page boundaries. Such blocks
 * have been observed with an SDIO WiFi card (b43 driver).
 */
अटल व्योम usdhi6_blk_bounce(काष्ठा usdhi6_host *host,
			      काष्ठा scatterlist *sg)
अणु
	काष्ठा mmc_data *data = host->mrq->data;
	माप_प्रकार blk_head = host->head_len;

	dev_dbg(mmc_dev(host->mmc), "%s(): CMD%u of %u SG: %ux%u @ 0x%x\n",
		__func__, host->mrq->cmd->opcode, data->sg_len,
		data->blksz, data->blocks, sg->offset);

	host->head_pg.page	= host->pg.page;
	host->head_pg.mapped	= host->pg.mapped;
	host->pg.page		= nth_page(host->pg.page, 1);
	host->pg.mapped		= kmap(host->pg.page);

	host->blk_page = host->bounce_buf;
	host->offset = 0;

	अगर (data->flags & MMC_DATA_READ)
		वापस;

	स_नकल(host->bounce_buf, host->head_pg.mapped + PAGE_SIZE - blk_head,
	       blk_head);
	स_नकल(host->bounce_buf + blk_head, host->pg.mapped,
	       data->blksz - blk_head);
पूर्ण

/* Only called क्रम multiple block IO */
अटल व्योम usdhi6_sg_prep(काष्ठा usdhi6_host *host)
अणु
	काष्ठा mmc_request *mrq = host->mrq;
	काष्ठा mmc_data *data = mrq->data;

	usdhi6_ग_लिखो(host, USDHI6_SD_SECCNT, data->blocks);

	host->sg = data->sg;
	/* TODO: अगर we always map, this is redundant */
	host->offset = host->sg->offset;
पूर्ण

/* Map the first page in an SG segment: common क्रम multiple and single block IO */
अटल व्योम *usdhi6_sg_map(काष्ठा usdhi6_host *host)
अणु
	काष्ठा mmc_data *data = host->mrq->data;
	काष्ठा scatterlist *sg = data->sg_len > 1 ? host->sg : data->sg;
	माप_प्रकार head = PAGE_SIZE - sg->offset;
	माप_प्रकार blk_head = head % data->blksz;

	WARN(host->pg.page, "%p not properly unmapped!\n", host->pg.page);
	अगर (WARN(sg_dma_len(sg) % data->blksz,
		 "SG size %u isn't a multiple of block size %u\n",
		 sg_dma_len(sg), data->blksz))
		वापस शून्य;

	host->pg.page = sg_page(sg);
	host->pg.mapped = kmap(host->pg.page);
	host->offset = sg->offset;

	/*
	 * Block size must be a घातer of 2 क्रम multi-block transfers,
	 * thereक्रमe blk_head is equal क्रम all pages in this SG
	 */
	host->head_len = blk_head;

	अगर (head < data->blksz)
		/*
		 * The first block in the SG crosses a page boundary.
		 * Max blksz = 512, so blocks can only span 2 pages
		 */
		usdhi6_blk_bounce(host, sg);
	अन्यथा
		host->blk_page = host->pg.mapped;

	dev_dbg(mmc_dev(host->mmc), "Mapped %p (%lx) at %p + %u for CMD%u @ 0x%p\n",
		host->pg.page, page_to_pfn(host->pg.page), host->pg.mapped,
		sg->offset, host->mrq->cmd->opcode, host->mrq);

	वापस host->blk_page + host->offset;
पूर्ण

/* Unmap the current page: common क्रम multiple and single block IO */
अटल व्योम usdhi6_sg_unmap(काष्ठा usdhi6_host *host, bool क्रमce)
अणु
	काष्ठा mmc_data *data = host->mrq->data;
	काष्ठा page *page = host->head_pg.page;

	अगर (page) अणु
		/* Previous block was cross-page boundary */
		काष्ठा scatterlist *sg = data->sg_len > 1 ?
			host->sg : data->sg;
		माप_प्रकार blk_head = host->head_len;

		अगर (!data->error && data->flags & MMC_DATA_READ) अणु
			स_नकल(host->head_pg.mapped + PAGE_SIZE - blk_head,
			       host->bounce_buf, blk_head);
			स_नकल(host->pg.mapped, host->bounce_buf + blk_head,
			       data->blksz - blk_head);
		पूर्ण

		flush_dcache_page(page);
		kunmap(page);

		host->head_pg.page = शून्य;

		अगर (!क्रमce && sg_dma_len(sg) + sg->offset >
		    (host->page_idx << PAGE_SHIFT) + data->blksz - blk_head)
			/* More blocks in this SG, करोn't unmap the next page */
			वापस;
	पूर्ण

	page = host->pg.page;
	अगर (!page)
		वापस;

	flush_dcache_page(page);
	kunmap(page);

	host->pg.page = शून्य;
पूर्ण

/* Called from MMC_WRITE_MULTIPLE_BLOCK or MMC_READ_MULTIPLE_BLOCK */
अटल व्योम usdhi6_sg_advance(काष्ठा usdhi6_host *host)
अणु
	काष्ठा mmc_data *data = host->mrq->data;
	माप_प्रकार करोne, total;

	/* New offset: set at the end of the previous block */
	अगर (host->head_pg.page) अणु
		/* Finished a cross-page block, jump to the new page */
		host->page_idx++;
		host->offset = data->blksz - host->head_len;
		host->blk_page = host->pg.mapped;
		usdhi6_sg_unmap(host, false);
	पूर्ण अन्यथा अणु
		host->offset += data->blksz;
		/* The completed block didn't cross a page boundary */
		अगर (host->offset == PAGE_SIZE) अणु
			/* If required, we'll map the page below */
			host->offset = 0;
			host->page_idx++;
		पूर्ण
	पूर्ण

	/*
	 * Now host->blk_page + host->offset poपूर्णांक at the end of our last block
	 * and host->page_idx is the index of the page, in which our new block
	 * is located, अगर any
	 */

	करोne = (host->page_idx << PAGE_SHIFT) + host->offset;
	total = host->sg->offset + sg_dma_len(host->sg);

	dev_dbg(mmc_dev(host->mmc), "%s(): %zu of %zu @ %zu\n", __func__,
		करोne, total, host->offset);

	अगर (करोne < total && host->offset) अणु
		/* More blocks in this page */
		अगर (host->offset + data->blksz > PAGE_SIZE)
			/* We approached at a block, that spans 2 pages */
			usdhi6_blk_bounce(host, host->sg);

		वापस;
	पूर्ण

	/* Finished current page or an SG segment */
	usdhi6_sg_unmap(host, false);

	अगर (करोne == total) अणु
		/*
		 * End of an SG segment or the complete SG: jump to the next
		 * segment, we'll map it later in usdhi6_blk_पढ़ो() or
		 * usdhi6_blk_ग_लिखो()
		 */
		काष्ठा scatterlist *next = sg_next(host->sg);

		host->page_idx = 0;

		अगर (!next)
			host->रुको = USDHI6_WAIT_FOR_DATA_END;
		host->sg = next;

		अगर (WARN(next && sg_dma_len(next) % data->blksz,
			 "SG size %u isn't a multiple of block size %u\n",
			 sg_dma_len(next), data->blksz))
			data->error = -EINVAL;

		वापस;
	पूर्ण

	/* We cannot get here after crossing a page border */

	/* Next page in the same SG */
	host->pg.page = nth_page(sg_page(host->sg), host->page_idx);
	host->pg.mapped = kmap(host->pg.page);
	host->blk_page = host->pg.mapped;

	dev_dbg(mmc_dev(host->mmc), "Mapped %p (%lx) at %p for CMD%u @ 0x%p\n",
		host->pg.page, page_to_pfn(host->pg.page), host->pg.mapped,
		host->mrq->cmd->opcode, host->mrq);
पूर्ण

/*			DMA handling					*/

अटल व्योम usdhi6_dma_release(काष्ठा usdhi6_host *host)
अणु
	host->dma_active = false;
	अगर (host->chan_tx) अणु
		काष्ठा dma_chan *chan = host->chan_tx;
		host->chan_tx = शून्य;
		dma_release_channel(chan);
	पूर्ण
	अगर (host->chan_rx) अणु
		काष्ठा dma_chan *chan = host->chan_rx;
		host->chan_rx = शून्य;
		dma_release_channel(chan);
	पूर्ण
पूर्ण

अटल व्योम usdhi6_dma_stop_unmap(काष्ठा usdhi6_host *host)
अणु
	काष्ठा mmc_data *data = host->mrq->data;

	अगर (!host->dma_active)
		वापस;

	usdhi6_ग_लिखो(host, USDHI6_CC_EXT_MODE, 0);
	host->dma_active = false;

	अगर (data->flags & MMC_DATA_READ)
		dma_unmap_sg(host->chan_rx->device->dev, data->sg,
			     data->sg_len, DMA_FROM_DEVICE);
	अन्यथा
		dma_unmap_sg(host->chan_tx->device->dev, data->sg,
			     data->sg_len, DMA_TO_DEVICE);
पूर्ण

अटल व्योम usdhi6_dma_complete(व्योम *arg)
अणु
	काष्ठा usdhi6_host *host = arg;
	काष्ठा mmc_request *mrq = host->mrq;

	अगर (WARN(!mrq || !mrq->data, "%s: NULL data in DMA completion for %p!\n",
		 dev_name(mmc_dev(host->mmc)), mrq))
		वापस;

	dev_dbg(mmc_dev(host->mmc), "%s(): CMD%u DMA completed\n", __func__,
		mrq->cmd->opcode);

	usdhi6_dma_stop_unmap(host);
	usdhi6_रुको_क्रम_brwe(host, mrq->data->flags & MMC_DATA_READ);
पूर्ण

अटल पूर्णांक usdhi6_dma_setup(काष्ठा usdhi6_host *host, काष्ठा dma_chan *chan,
			    क्रमागत dma_transfer_direction dir)
अणु
	काष्ठा mmc_data *data = host->mrq->data;
	काष्ठा scatterlist *sg = data->sg;
	काष्ठा dma_async_tx_descriptor *desc = शून्य;
	dma_cookie_t cookie = -EINVAL;
	क्रमागत dma_data_direction data_dir;
	पूर्णांक ret;

	चयन (dir) अणु
	हाल DMA_MEM_TO_DEV:
		data_dir = DMA_TO_DEVICE;
		अवरोध;
	हाल DMA_DEV_TO_MEM:
		data_dir = DMA_FROM_DEVICE;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	ret = dma_map_sg(chan->device->dev, sg, data->sg_len, data_dir);
	अगर (ret > 0) अणु
		host->dma_active = true;
		desc = dmaengine_prep_slave_sg(chan, sg, ret, dir,
					DMA_PREP_INTERRUPT | DMA_CTRL_ACK);
	पूर्ण

	अगर (desc) अणु
		desc->callback = usdhi6_dma_complete;
		desc->callback_param = host;
		cookie = dmaengine_submit(desc);
	पूर्ण

	dev_dbg(mmc_dev(host->mmc), "%s(): mapped %d -> %d, cookie %d @ %p\n",
		__func__, data->sg_len, ret, cookie, desc);

	अगर (cookie < 0) अणु
		/* DMA failed, fall back to PIO */
		अगर (ret >= 0)
			ret = cookie;
		usdhi6_dma_release(host);
		dev_warn(mmc_dev(host->mmc),
			 "DMA failed: %d, falling back to PIO\n", ret);
	पूर्ण

	वापस cookie;
पूर्ण

अटल पूर्णांक usdhi6_dma_start(काष्ठा usdhi6_host *host)
अणु
	अगर (!host->chan_rx || !host->chan_tx)
		वापस -ENODEV;

	अगर (host->mrq->data->flags & MMC_DATA_READ)
		वापस usdhi6_dma_setup(host, host->chan_rx, DMA_DEV_TO_MEM);

	वापस usdhi6_dma_setup(host, host->chan_tx, DMA_MEM_TO_DEV);
पूर्ण

अटल व्योम usdhi6_dma_समाप्त(काष्ठा usdhi6_host *host)
अणु
	काष्ठा mmc_data *data = host->mrq->data;

	dev_dbg(mmc_dev(host->mmc), "%s(): SG of %u: %ux%u\n",
		__func__, data->sg_len, data->blocks, data->blksz);
	/* Abort DMA */
	अगर (data->flags & MMC_DATA_READ)
		dmaengine_terminate_all(host->chan_rx);
	अन्यथा
		dmaengine_terminate_all(host->chan_tx);
पूर्ण

अटल व्योम usdhi6_dma_check_error(काष्ठा usdhi6_host *host)
अणु
	काष्ठा mmc_data *data = host->mrq->data;

	dev_dbg(mmc_dev(host->mmc), "%s(): IO error %d, status 0x%x\n",
		__func__, host->io_error, usdhi6_पढ़ो(host, USDHI6_SD_INFO1));

	अगर (host->io_error) अणु
		data->error = usdhi6_error_code(host);
		data->bytes_xfered = 0;
		usdhi6_dma_समाप्त(host);
		usdhi6_dma_release(host);
		dev_warn(mmc_dev(host->mmc),
			 "DMA failed: %d, falling back to PIO\n", data->error);
		वापस;
	पूर्ण

	/*
	 * The datasheet tells us to check a response from the card, whereas
	 * responses only come after the command phase, not after the data
	 * phase. Let's check anyway.
	 */
	अगर (host->irq_status & USDHI6_SD_INFO1_RSP_END)
		dev_warn(mmc_dev(host->mmc), "Unexpected response received!\n");
पूर्ण

अटल व्योम usdhi6_dma_kick(काष्ठा usdhi6_host *host)
अणु
	अगर (host->mrq->data->flags & MMC_DATA_READ)
		dma_async_issue_pending(host->chan_rx);
	अन्यथा
		dma_async_issue_pending(host->chan_tx);
पूर्ण

अटल व्योम usdhi6_dma_request(काष्ठा usdhi6_host *host, phys_addr_t start)
अणु
	काष्ठा dma_slave_config cfg = अणु
		.src_addr_width = DMA_SLAVE_BUSWIDTH_4_BYTES,
		.dst_addr_width = DMA_SLAVE_BUSWIDTH_4_BYTES,
	पूर्ण;
	पूर्णांक ret;

	host->chan_tx = dma_request_chan(mmc_dev(host->mmc), "tx");
	dev_dbg(mmc_dev(host->mmc), "%s: TX: got channel %p\n", __func__,
		host->chan_tx);

	अगर (IS_ERR(host->chan_tx)) अणु
		host->chan_tx = शून्य;
		वापस;
	पूर्ण

	cfg.direction = DMA_MEM_TO_DEV;
	cfg.dst_addr = start + USDHI6_SD_BUF0;
	cfg.dst_maxburst = 128;	/* 128 words * 4 bytes = 512 bytes */
	cfg.src_addr = 0;
	ret = dmaengine_slave_config(host->chan_tx, &cfg);
	अगर (ret < 0)
		जाओ e_release_tx;

	host->chan_rx = dma_request_chan(mmc_dev(host->mmc), "rx");
	dev_dbg(mmc_dev(host->mmc), "%s: RX: got channel %p\n", __func__,
		host->chan_rx);

	अगर (IS_ERR(host->chan_rx)) अणु
		host->chan_rx = शून्य;
		जाओ e_release_tx;
	पूर्ण

	cfg.direction = DMA_DEV_TO_MEM;
	cfg.src_addr = cfg.dst_addr;
	cfg.src_maxburst = 128;	/* 128 words * 4 bytes = 512 bytes */
	cfg.dst_addr = 0;
	ret = dmaengine_slave_config(host->chan_rx, &cfg);
	अगर (ret < 0)
		जाओ e_release_rx;

	वापस;

e_release_rx:
	dma_release_channel(host->chan_rx);
	host->chan_rx = शून्य;
e_release_tx:
	dma_release_channel(host->chan_tx);
	host->chan_tx = शून्य;
पूर्ण

/*			API helpers					*/

अटल व्योम usdhi6_clk_set(काष्ठा usdhi6_host *host, काष्ठा mmc_ios *ios)
अणु
	अचिन्हित दीर्घ rate = ios->घड़ी;
	u32 val;
	अचिन्हित पूर्णांक i;

	क्रम (i = 1000; i; i--) अणु
		अगर (usdhi6_पढ़ो(host, USDHI6_SD_INFO2) & USDHI6_SD_INFO2_SCLKDIVEN)
			अवरोध;
		usleep_range(10, 100);
	पूर्ण

	अगर (!i) अणु
		dev_err(mmc_dev(host->mmc), "SD bus busy, clock set aborted\n");
		वापस;
	पूर्ण

	val = usdhi6_पढ़ो(host, USDHI6_SD_CLK_CTRL) & ~USDHI6_SD_CLK_CTRL_DIV_MASK;

	अगर (rate) अणु
		अचिन्हित दीर्घ new_rate;

		अगर (host->imclk <= rate) अणु
			अगर (ios->timing != MMC_TIMING_UHS_DDR50) अणु
				/* Cannot have 1-to-1 घड़ी in DDR mode */
				new_rate = host->imclk;
				val |= 0xff;
			पूर्ण अन्यथा अणु
				new_rate = host->imclk / 2;
			पूर्ण
		पूर्ण अन्यथा अणु
			अचिन्हित दीर्घ भाग =
				roundup_घात_of_two(DIV_ROUND_UP(host->imclk, rate));
			val |= भाग >> 2;
			new_rate = host->imclk / भाग;
		पूर्ण

		अगर (host->rate == new_rate)
			वापस;

		host->rate = new_rate;

		dev_dbg(mmc_dev(host->mmc), "target %lu, div %u, set %lu\n",
			rate, (val & 0xff) << 2, new_rate);
	पूर्ण

	/*
	 * अगर old or new rate is equal to input rate, have to चयन the घड़ी
	 * off beक्रमe changing and on after
	 */
	अगर (host->imclk == rate || host->imclk == host->rate || !rate)
		usdhi6_ग_लिखो(host, USDHI6_SD_CLK_CTRL,
			     val & ~USDHI6_SD_CLK_CTRL_SCLKEN);

	अगर (!rate) अणु
		host->rate = 0;
		वापस;
	पूर्ण

	usdhi6_ग_लिखो(host, USDHI6_SD_CLK_CTRL, val);

	अगर (host->imclk == rate || host->imclk == host->rate ||
	    !(val & USDHI6_SD_CLK_CTRL_SCLKEN))
		usdhi6_ग_लिखो(host, USDHI6_SD_CLK_CTRL,
			     val | USDHI6_SD_CLK_CTRL_SCLKEN);
पूर्ण

अटल व्योम usdhi6_set_घातer(काष्ठा usdhi6_host *host, काष्ठा mmc_ios *ios)
अणु
	काष्ठा mmc_host *mmc = host->mmc;

	अगर (!IS_ERR(mmc->supply.vmmc))
		/* Errors ignored... */
		mmc_regulator_set_ocr(mmc, mmc->supply.vmmc,
				      ios->घातer_mode ? ios->vdd : 0);
पूर्ण

अटल पूर्णांक usdhi6_reset(काष्ठा usdhi6_host *host)
अणु
	पूर्णांक i;

	usdhi6_ग_लिखो(host, USDHI6_SOFT_RST, USDHI6_SOFT_RST_RESERVED);
	cpu_relax();
	usdhi6_ग_लिखो(host, USDHI6_SOFT_RST, USDHI6_SOFT_RST_RESERVED | USDHI6_SOFT_RST_RESET);
	क्रम (i = 1000; i; i--)
		अगर (usdhi6_पढ़ो(host, USDHI6_SOFT_RST) & USDHI6_SOFT_RST_RESET)
			अवरोध;

	वापस i ? 0 : -ETIMEDOUT;
पूर्ण

अटल व्योम usdhi6_set_ios(काष्ठा mmc_host *mmc, काष्ठा mmc_ios *ios)
अणु
	काष्ठा usdhi6_host *host = mmc_priv(mmc);
	u32 option, mode;
	पूर्णांक ret;

	dev_dbg(mmc_dev(mmc), "%uHz, OCR: %u, power %u, bus-width %u, timing %u\n",
		ios->घड़ी, ios->vdd, ios->घातer_mode, ios->bus_width, ios->timing);

	चयन (ios->घातer_mode) अणु
	हाल MMC_POWER_OFF:
		usdhi6_set_घातer(host, ios);
		usdhi6_only_cd(host);
		अवरोध;
	हाल MMC_POWER_UP:
		/*
		 * We only also touch USDHI6_SD_OPTION from .request(), which
		 * cannot race with MMC_POWER_UP
		 */
		ret = usdhi6_reset(host);
		अगर (ret < 0) अणु
			dev_err(mmc_dev(mmc), "Cannot reset the interface!\n");
		पूर्ण अन्यथा अणु
			usdhi6_set_घातer(host, ios);
			usdhi6_only_cd(host);
		पूर्ण
		अवरोध;
	हाल MMC_POWER_ON:
		option = usdhi6_पढ़ो(host, USDHI6_SD_OPTION);
		/*
		 * The eMMC standard only allows 4 or 8 bits in the DDR mode,
		 * the same probably holds क्रम SD cards. We check here anyway,
		 * since the datasheet explicitly requires 4 bits क्रम DDR.
		 */
		अगर (ios->bus_width == MMC_BUS_WIDTH_1) अणु
			अगर (ios->timing == MMC_TIMING_UHS_DDR50)
				dev_err(mmc_dev(mmc),
					"4 bits are required for DDR\n");
			option |= USDHI6_SD_OPTION_WIDTH_1;
			mode = 0;
		पूर्ण अन्यथा अणु
			option &= ~USDHI6_SD_OPTION_WIDTH_1;
			mode = ios->timing == MMC_TIMING_UHS_DDR50;
		पूर्ण
		usdhi6_ग_लिखो(host, USDHI6_SD_OPTION, option);
		usdhi6_ग_लिखो(host, USDHI6_SDIF_MODE, mode);
		अवरोध;
	पूर्ण

	अगर (host->rate != ios->घड़ी)
		usdhi6_clk_set(host, ios);
पूर्ण

/* This is data समयout. Response समयout is fixed to 640 घड़ी cycles */
अटल व्योम usdhi6_समयout_set(काष्ठा usdhi6_host *host)
अणु
	काष्ठा mmc_request *mrq = host->mrq;
	u32 val;
	अचिन्हित दीर्घ ticks;

	अगर (!mrq->data)
		ticks = host->rate / 1000 * mrq->cmd->busy_समयout;
	अन्यथा
		ticks = host->rate / 1000000 * (mrq->data->समयout_ns / 1000) +
			mrq->data->समयout_clks;

	अगर (!ticks || ticks > 1 << 27)
		/* Max समयout */
		val = 14;
	अन्यथा अगर (ticks < 1 << 13)
		/* Min समयout */
		val = 0;
	अन्यथा
		val = order_base_2(ticks) - 13;

	dev_dbg(mmc_dev(host->mmc), "Set %s timeout %lu ticks @ %lu Hz\n",
		mrq->data ? "data" : "cmd", ticks, host->rate);

	/* Timeout Counter mask: 0xf0 */
	usdhi6_ग_लिखो(host, USDHI6_SD_OPTION, (val << USDHI6_SD_OPTION_TIMEOUT_SHIFT) |
		     (usdhi6_पढ़ो(host, USDHI6_SD_OPTION) & ~USDHI6_SD_OPTION_TIMEOUT_MASK));
पूर्ण

अटल व्योम usdhi6_request_करोne(काष्ठा usdhi6_host *host)
अणु
	काष्ठा mmc_request *mrq = host->mrq;
	काष्ठा mmc_data *data = mrq->data;

	अगर (WARN(host->pg.page || host->head_pg.page,
		 "Page %p or %p not unmapped: wait %u, CMD%d(%c) @ +0x%zx %ux%u in SG%u!\n",
		 host->pg.page, host->head_pg.page, host->रुको, mrq->cmd->opcode,
		 data ? (data->flags & MMC_DATA_READ ? 'R' : 'W') : '-',
		 data ? host->offset : 0, data ? data->blocks : 0,
		 data ? data->blksz : 0, data ? data->sg_len : 0))
		usdhi6_sg_unmap(host, true);

	अगर (mrq->cmd->error ||
	    (data && data->error) ||
	    (mrq->stop && mrq->stop->error))
		dev_dbg(mmc_dev(host->mmc), "%s(CMD%d: %ux%u): err %d %d %d\n",
			__func__, mrq->cmd->opcode, data ? data->blocks : 0,
			data ? data->blksz : 0,
			mrq->cmd->error,
			data ? data->error : 1,
			mrq->stop ? mrq->stop->error : 1);

	/* Disable DMA */
	usdhi6_ग_लिखो(host, USDHI6_CC_EXT_MODE, 0);
	host->रुको = USDHI6_WAIT_FOR_REQUEST;
	host->mrq = शून्य;

	mmc_request_करोne(host->mmc, mrq);
पूर्ण

अटल पूर्णांक usdhi6_cmd_flags(काष्ठा usdhi6_host *host)
अणु
	काष्ठा mmc_request *mrq = host->mrq;
	काष्ठा mmc_command *cmd = mrq->cmd;
	u16 opc = cmd->opcode;

	अगर (host->app_cmd) अणु
		host->app_cmd = false;
		opc |= USDHI6_SD_CMD_APP;
	पूर्ण

	अगर (mrq->data) अणु
		opc |= USDHI6_SD_CMD_DATA;

		अगर (mrq->data->flags & MMC_DATA_READ)
			opc |= USDHI6_SD_CMD_READ;

		अगर (cmd->opcode == MMC_READ_MULTIPLE_BLOCK ||
		    cmd->opcode == MMC_WRITE_MULTIPLE_BLOCK ||
		    (cmd->opcode == SD_IO_RW_EXTENDED &&
		     mrq->data->blocks > 1)) अणु
			opc |= USDHI6_SD_CMD_MULTI;
			अगर (!mrq->stop)
				opc |= USDHI6_SD_CMD_CMD12_AUTO_OFF;
		पूर्ण

		चयन (mmc_resp_type(cmd)) अणु
		हाल MMC_RSP_NONE:
			opc |= USDHI6_SD_CMD_MODE_RSP_NONE;
			अवरोध;
		हाल MMC_RSP_R1:
			opc |= USDHI6_SD_CMD_MODE_RSP_R1;
			अवरोध;
		हाल MMC_RSP_R1B:
			opc |= USDHI6_SD_CMD_MODE_RSP_R1B;
			अवरोध;
		हाल MMC_RSP_R2:
			opc |= USDHI6_SD_CMD_MODE_RSP_R2;
			अवरोध;
		हाल MMC_RSP_R3:
			opc |= USDHI6_SD_CMD_MODE_RSP_R3;
			अवरोध;
		शेष:
			dev_warn(mmc_dev(host->mmc),
				 "Unknown response type %d\n",
				 mmc_resp_type(cmd));
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	वापस opc;
पूर्ण

अटल पूर्णांक usdhi6_rq_start(काष्ठा usdhi6_host *host)
अणु
	काष्ठा mmc_request *mrq = host->mrq;
	काष्ठा mmc_command *cmd = mrq->cmd;
	काष्ठा mmc_data *data = mrq->data;
	पूर्णांक opc = usdhi6_cmd_flags(host);
	पूर्णांक i;

	अगर (opc < 0)
		वापस opc;

	क्रम (i = 1000; i; i--) अणु
		अगर (!(usdhi6_पढ़ो(host, USDHI6_SD_INFO2) & USDHI6_SD_INFO2_CBSY))
			अवरोध;
		usleep_range(10, 100);
	पूर्ण

	अगर (!i) अणु
		dev_dbg(mmc_dev(host->mmc), "Command active, request aborted\n");
		वापस -EAGAIN;
	पूर्ण

	अगर (data) अणु
		bool use_dma;
		पूर्णांक ret = 0;

		host->page_idx = 0;

		अगर (cmd->opcode == SD_IO_RW_EXTENDED && data->blocks > 1) अणु
			चयन (data->blksz) अणु
			हाल 512:
				अवरोध;
			हाल 32:
			हाल 64:
			हाल 128:
			हाल 256:
				अगर (mrq->stop)
					ret = -EINVAL;
				अवरोध;
			शेष:
				ret = -EINVAL;
			पूर्ण
		पूर्ण अन्यथा अगर ((cmd->opcode == MMC_READ_MULTIPLE_BLOCK ||
			    cmd->opcode == MMC_WRITE_MULTIPLE_BLOCK) &&
			   data->blksz != 512) अणु
			ret = -EINVAL;
		पूर्ण

		अगर (ret < 0) अणु
			dev_warn(mmc_dev(host->mmc), "%s(): %u blocks of %u bytes\n",
				 __func__, data->blocks, data->blksz);
			वापस -EINVAL;
		पूर्ण

		अगर (cmd->opcode == MMC_READ_MULTIPLE_BLOCK ||
		    cmd->opcode == MMC_WRITE_MULTIPLE_BLOCK ||
		    (cmd->opcode == SD_IO_RW_EXTENDED &&
		     data->blocks > 1))
			usdhi6_sg_prep(host);

		usdhi6_ग_लिखो(host, USDHI6_SD_SIZE, data->blksz);

		अगर ((data->blksz >= USDHI6_MIN_DMA ||
		     data->blocks > 1) &&
		    (data->blksz % 4 ||
		     data->sg->offset % 4))
			dev_dbg(mmc_dev(host->mmc),
				"Bad SG of %u: %ux%u @ %u\n", data->sg_len,
				data->blksz, data->blocks, data->sg->offset);

		/* Enable DMA क्रम USDHI6_MIN_DMA bytes or more */
		use_dma = data->blksz >= USDHI6_MIN_DMA &&
			!(data->blksz % 4) &&
			usdhi6_dma_start(host) >= DMA_MIN_COOKIE;

		अगर (use_dma)
			usdhi6_ग_लिखो(host, USDHI6_CC_EXT_MODE, USDHI6_CC_EXT_MODE_SDRW);

		dev_dbg(mmc_dev(host->mmc),
			"%s(): request opcode %u, %u blocks of %u bytes in %u segments, %s %s @+0x%x%s\n",
			__func__, cmd->opcode, data->blocks, data->blksz,
			data->sg_len, use_dma ? "DMA" : "PIO",
			data->flags & MMC_DATA_READ ? "read" : "write",
			data->sg->offset, mrq->stop ? " + stop" : "");
	पूर्ण अन्यथा अणु
		dev_dbg(mmc_dev(host->mmc), "%s(): request opcode %u\n",
			__func__, cmd->opcode);
	पूर्ण

	/* We have to get a command completion पूर्णांकerrupt with DMA too */
	usdhi6_रुको_क्रम_resp(host);

	host->रुको = USDHI6_WAIT_FOR_CMD;
	schedule_delayed_work(&host->समयout_work, host->समयout);

	/* SEC bit is required to enable block counting by the core */
	usdhi6_ग_लिखो(host, USDHI6_SD_STOP,
		     data && data->blocks > 1 ? USDHI6_SD_STOP_SEC : 0);
	usdhi6_ग_लिखो(host, USDHI6_SD_ARG, cmd->arg);

	/* Kick command execution */
	usdhi6_ग_लिखो(host, USDHI6_SD_CMD, opc);

	वापस 0;
पूर्ण

अटल व्योम usdhi6_request(काष्ठा mmc_host *mmc, काष्ठा mmc_request *mrq)
अणु
	काष्ठा usdhi6_host *host = mmc_priv(mmc);
	पूर्णांक ret;

	cancel_delayed_work_sync(&host->समयout_work);

	host->mrq = mrq;
	host->sg = शून्य;

	usdhi6_समयout_set(host);
	ret = usdhi6_rq_start(host);
	अगर (ret < 0) अणु
		mrq->cmd->error = ret;
		usdhi6_request_करोne(host);
	पूर्ण
पूर्ण

अटल पूर्णांक usdhi6_get_cd(काष्ठा mmc_host *mmc)
अणु
	काष्ठा usdhi6_host *host = mmc_priv(mmc);
	/* Read is atomic, no need to lock */
	u32 status = usdhi6_पढ़ो(host, USDHI6_SD_INFO1) & USDHI6_SD_INFO1_CD;

/*
 *	level	status.CD	CD_ACTIVE_HIGH	card present
 *	1	0		0		0
 *	1	0		1		1
 *	0	1		0		1
 *	0	1		1		0
 */
	वापस !status ^ !(mmc->caps2 & MMC_CAP2_CD_ACTIVE_HIGH);
पूर्ण

अटल पूर्णांक usdhi6_get_ro(काष्ठा mmc_host *mmc)
अणु
	काष्ठा usdhi6_host *host = mmc_priv(mmc);
	/* No locking as above */
	u32 status = usdhi6_पढ़ो(host, USDHI6_SD_INFO1) & USDHI6_SD_INFO1_WP;

/*
 *	level	status.WP	RO_ACTIVE_HIGH	card पढ़ो-only
 *	1	0		0		0
 *	1	0		1		1
 *	0	1		0		1
 *	0	1		1		0
 */
	वापस !status ^ !(mmc->caps2 & MMC_CAP2_RO_ACTIVE_HIGH);
पूर्ण

अटल व्योम usdhi6_enable_sdio_irq(काष्ठा mmc_host *mmc, पूर्णांक enable)
अणु
	काष्ठा usdhi6_host *host = mmc_priv(mmc);

	dev_dbg(mmc_dev(mmc), "%s(): %sable\n", __func__, enable ? "en" : "dis");

	अगर (enable) अणु
		host->sdio_mask = USDHI6_SDIO_INFO1_IRQ & ~USDHI6_SDIO_INFO1_IOIRQ;
		usdhi6_ग_लिखो(host, USDHI6_SDIO_INFO1_MASK, host->sdio_mask);
		usdhi6_ग_लिखो(host, USDHI6_SDIO_MODE, 1);
	पूर्ण अन्यथा अणु
		usdhi6_ग_लिखो(host, USDHI6_SDIO_MODE, 0);
		usdhi6_ग_लिखो(host, USDHI6_SDIO_INFO1_MASK, USDHI6_SDIO_INFO1_IRQ);
		host->sdio_mask = USDHI6_SDIO_INFO1_IRQ;
	पूर्ण
पूर्ण

अटल पूर्णांक usdhi6_set_pinstates(काष्ठा usdhi6_host *host, पूर्णांक voltage)
अणु
	अगर (IS_ERR(host->pins_uhs))
		वापस 0;

	चयन (voltage) अणु
	हाल MMC_SIGNAL_VOLTAGE_180:
	हाल MMC_SIGNAL_VOLTAGE_120:
		वापस pinctrl_select_state(host->pinctrl,
					    host->pins_uhs);

	शेष:
		वापस pinctrl_select_शेष_state(mmc_dev(host->mmc));
	पूर्ण
पूर्ण

अटल पूर्णांक usdhi6_sig_volt_चयन(काष्ठा mmc_host *mmc, काष्ठा mmc_ios *ios)
अणु
	पूर्णांक ret;

	ret = mmc_regulator_set_vqmmc(mmc, ios);
	अगर (ret < 0)
		वापस ret;

	ret = usdhi6_set_pinstates(mmc_priv(mmc), ios->संकेत_voltage);
	अगर (ret)
		dev_warn_once(mmc_dev(mmc),
			      "Failed to set pinstate err=%d\n", ret);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा mmc_host_ops usdhi6_ops = अणु
	.request	= usdhi6_request,
	.set_ios	= usdhi6_set_ios,
	.get_cd		= usdhi6_get_cd,
	.get_ro		= usdhi6_get_ro,
	.enable_sdio_irq = usdhi6_enable_sdio_irq,
	.start_संकेत_voltage_चयन = usdhi6_sig_volt_चयन,
पूर्ण;

/*			State machine handlers				*/

अटल व्योम usdhi6_resp_cmd12(काष्ठा usdhi6_host *host)
अणु
	काष्ठा mmc_command *cmd = host->mrq->stop;
	cmd->resp[0] = usdhi6_पढ़ो(host, USDHI6_SD_RSP10);
पूर्ण

अटल व्योम usdhi6_resp_पढ़ो(काष्ठा usdhi6_host *host)
अणु
	काष्ठा mmc_command *cmd = host->mrq->cmd;
	u32 *rsp = cmd->resp, पंचांगp = 0;
	पूर्णांक i;

/*
 * RSP10	39-8
 * RSP32	71-40
 * RSP54	103-72
 * RSP76	127-104
 * R2-type response:
 * resp[0]	= r[127..96]
 * resp[1]	= r[95..64]
 * resp[2]	= r[63..32]
 * resp[3]	= r[31..0]
 * Other responses:
 * resp[0]	= r[39..8]
 */

	अगर (mmc_resp_type(cmd) == MMC_RSP_NONE)
		वापस;

	अगर (!(host->irq_status & USDHI6_SD_INFO1_RSP_END)) अणु
		dev_err(mmc_dev(host->mmc),
			"CMD%d: response expected but is missing!\n", cmd->opcode);
		वापस;
	पूर्ण

	अगर (mmc_resp_type(cmd) & MMC_RSP_136)
		क्रम (i = 0; i < 4; i++) अणु
			अगर (i)
				rsp[3 - i] = पंचांगp >> 24;
			पंचांगp = usdhi6_पढ़ो(host, USDHI6_SD_RSP10 + i * 8);
			rsp[3 - i] |= पंचांगp << 8;
		पूर्ण
	अन्यथा अगर (cmd->opcode == MMC_READ_MULTIPLE_BLOCK ||
		 cmd->opcode == MMC_WRITE_MULTIPLE_BLOCK)
		/* Read RSP54 to aव्योम conflict with स्वतः CMD12 */
		rsp[0] = usdhi6_पढ़ो(host, USDHI6_SD_RSP54);
	अन्यथा
		rsp[0] = usdhi6_पढ़ो(host, USDHI6_SD_RSP10);

	dev_dbg(mmc_dev(host->mmc), "Response 0x%x\n", rsp[0]);
पूर्ण

अटल पूर्णांक usdhi6_blk_पढ़ो(काष्ठा usdhi6_host *host)
अणु
	काष्ठा mmc_data *data = host->mrq->data;
	u32 *p;
	पूर्णांक i, rest;

	अगर (host->io_error) अणु
		data->error = usdhi6_error_code(host);
		जाओ error;
	पूर्ण

	अगर (host->pg.page) अणु
		p = host->blk_page + host->offset;
	पूर्ण अन्यथा अणु
		p = usdhi6_sg_map(host);
		अगर (!p) अणु
			data->error = -ENOMEM;
			जाओ error;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < data->blksz / 4; i++, p++)
		*p = usdhi6_पढ़ो(host, USDHI6_SD_BUF0);

	rest = data->blksz % 4;
	क्रम (i = 0; i < (rest + 1) / 2; i++) अणु
		u16 d = usdhi6_पढ़ो16(host, USDHI6_SD_BUF0);
		((u8 *)p)[2 * i] = ((u8 *)&d)[0];
		अगर (rest > 1 && !i)
			((u8 *)p)[2 * i + 1] = ((u8 *)&d)[1];
	पूर्ण

	वापस 0;

error:
	dev_dbg(mmc_dev(host->mmc), "%s(): %d\n", __func__, data->error);
	host->रुको = USDHI6_WAIT_FOR_REQUEST;
	वापस data->error;
पूर्ण

अटल पूर्णांक usdhi6_blk_ग_लिखो(काष्ठा usdhi6_host *host)
अणु
	काष्ठा mmc_data *data = host->mrq->data;
	u32 *p;
	पूर्णांक i, rest;

	अगर (host->io_error) अणु
		data->error = usdhi6_error_code(host);
		जाओ error;
	पूर्ण

	अगर (host->pg.page) अणु
		p = host->blk_page + host->offset;
	पूर्ण अन्यथा अणु
		p = usdhi6_sg_map(host);
		अगर (!p) अणु
			data->error = -ENOMEM;
			जाओ error;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < data->blksz / 4; i++, p++)
		usdhi6_ग_लिखो(host, USDHI6_SD_BUF0, *p);

	rest = data->blksz % 4;
	क्रम (i = 0; i < (rest + 1) / 2; i++) अणु
		u16 d;
		((u8 *)&d)[0] = ((u8 *)p)[2 * i];
		अगर (rest > 1 && !i)
			((u8 *)&d)[1] = ((u8 *)p)[2 * i + 1];
		अन्यथा
			((u8 *)&d)[1] = 0;
		usdhi6_ग_लिखो16(host, USDHI6_SD_BUF0, d);
	पूर्ण

	वापस 0;

error:
	dev_dbg(mmc_dev(host->mmc), "%s(): %d\n", __func__, data->error);
	host->रुको = USDHI6_WAIT_FOR_REQUEST;
	वापस data->error;
पूर्ण

अटल पूर्णांक usdhi6_stop_cmd(काष्ठा usdhi6_host *host)
अणु
	काष्ठा mmc_request *mrq = host->mrq;

	चयन (mrq->cmd->opcode) अणु
	हाल MMC_READ_MULTIPLE_BLOCK:
	हाल MMC_WRITE_MULTIPLE_BLOCK:
		अगर (mrq->stop->opcode == MMC_STOP_TRANSMISSION) अणु
			host->रुको = USDHI6_WAIT_FOR_STOP;
			वापस 0;
		पूर्ण
		fallthrough;	/* Unsupported STOP command */
	शेष:
		dev_err(mmc_dev(host->mmc),
			"unsupported stop CMD%d for CMD%d\n",
			mrq->stop->opcode, mrq->cmd->opcode);
		mrq->stop->error = -EOPNOTSUPP;
	पूर्ण

	वापस -EOPNOTSUPP;
पूर्ण

अटल bool usdhi6_end_cmd(काष्ठा usdhi6_host *host)
अणु
	काष्ठा mmc_request *mrq = host->mrq;
	काष्ठा mmc_command *cmd = mrq->cmd;

	अगर (host->io_error) अणु
		cmd->error = usdhi6_error_code(host);
		वापस false;
	पूर्ण

	usdhi6_resp_पढ़ो(host);

	अगर (!mrq->data)
		वापस false;

	अगर (host->dma_active) अणु
		usdhi6_dma_kick(host);
		अगर (!mrq->stop)
			host->रुको = USDHI6_WAIT_FOR_DMA;
		अन्यथा अगर (usdhi6_stop_cmd(host) < 0)
			वापस false;
	पूर्ण अन्यथा अगर (mrq->data->flags & MMC_DATA_READ) अणु
		अगर (cmd->opcode == MMC_READ_MULTIPLE_BLOCK ||
		    (cmd->opcode == SD_IO_RW_EXTENDED &&
		     mrq->data->blocks > 1))
			host->रुको = USDHI6_WAIT_FOR_MREAD;
		अन्यथा
			host->रुको = USDHI6_WAIT_FOR_READ;
	पूर्ण अन्यथा अणु
		अगर (cmd->opcode == MMC_WRITE_MULTIPLE_BLOCK ||
		    (cmd->opcode == SD_IO_RW_EXTENDED &&
		     mrq->data->blocks > 1))
			host->रुको = USDHI6_WAIT_FOR_MWRITE;
		अन्यथा
			host->रुको = USDHI6_WAIT_FOR_WRITE;
	पूर्ण

	वापस true;
पूर्ण

अटल bool usdhi6_पढ़ो_block(काष्ठा usdhi6_host *host)
अणु
	/* ACCESS_END IRQ is alपढ़ोy unmasked */
	पूर्णांक ret = usdhi6_blk_पढ़ो(host);

	/*
	 * Have to क्रमce unmapping both pages: the single block could have been
	 * cross-page, in which हाल क्रम single-block IO host->page_idx == 0.
	 * So, अगर we करोn't force, the second page won't be unmapped.
	 */
	usdhi6_sg_unmap(host, true);

	अगर (ret < 0)
		वापस false;

	host->रुको = USDHI6_WAIT_FOR_DATA_END;
	वापस true;
पूर्ण

अटल bool usdhi6_mपढ़ो_block(काष्ठा usdhi6_host *host)
अणु
	पूर्णांक ret = usdhi6_blk_पढ़ो(host);

	अगर (ret < 0)
		वापस false;

	usdhi6_sg_advance(host);

	वापस !host->mrq->data->error &&
		(host->रुको != USDHI6_WAIT_FOR_DATA_END || !host->mrq->stop);
पूर्ण

अटल bool usdhi6_ग_लिखो_block(काष्ठा usdhi6_host *host)
अणु
	पूर्णांक ret = usdhi6_blk_ग_लिखो(host);

	/* See comment in usdhi6_पढ़ो_block() */
	usdhi6_sg_unmap(host, true);

	अगर (ret < 0)
		वापस false;

	host->रुको = USDHI6_WAIT_FOR_DATA_END;
	वापस true;
पूर्ण

अटल bool usdhi6_mग_लिखो_block(काष्ठा usdhi6_host *host)
अणु
	पूर्णांक ret = usdhi6_blk_ग_लिखो(host);

	अगर (ret < 0)
		वापस false;

	usdhi6_sg_advance(host);

	वापस !host->mrq->data->error &&
		(host->रुको != USDHI6_WAIT_FOR_DATA_END || !host->mrq->stop);
पूर्ण

/*			Interrupt & समयout handlers			*/

अटल irqवापस_t usdhi6_sd_bh(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा usdhi6_host *host = dev_id;
	काष्ठा mmc_request *mrq;
	काष्ठा mmc_command *cmd;
	काष्ठा mmc_data *data;
	bool io_रुको = false;

	cancel_delayed_work_sync(&host->समयout_work);

	mrq = host->mrq;
	अगर (!mrq)
		वापस IRQ_HANDLED;

	cmd = mrq->cmd;
	data = mrq->data;

	चयन (host->रुको) अणु
	हाल USDHI6_WAIT_FOR_REQUEST:
		/* We're too late, the समयout has alपढ़ोy kicked in */
		वापस IRQ_HANDLED;
	हाल USDHI6_WAIT_FOR_CMD:
		/* Wait क्रम data? */
		io_रुको = usdhi6_end_cmd(host);
		अवरोध;
	हाल USDHI6_WAIT_FOR_MREAD:
		/* Wait क्रम more data? */
		io_रुको = usdhi6_mपढ़ो_block(host);
		अवरोध;
	हाल USDHI6_WAIT_FOR_READ:
		/* Wait क्रम data end? */
		io_रुको = usdhi6_पढ़ो_block(host);
		अवरोध;
	हाल USDHI6_WAIT_FOR_MWRITE:
		/* Wait data to ग_लिखो? */
		io_रुको = usdhi6_mग_लिखो_block(host);
		अवरोध;
	हाल USDHI6_WAIT_FOR_WRITE:
		/* Wait क्रम data end? */
		io_रुको = usdhi6_ग_लिखो_block(host);
		अवरोध;
	हाल USDHI6_WAIT_FOR_DMA:
		usdhi6_dma_check_error(host);
		अवरोध;
	हाल USDHI6_WAIT_FOR_STOP:
		usdhi6_ग_लिखो(host, USDHI6_SD_STOP, 0);
		अगर (host->io_error) अणु
			पूर्णांक ret = usdhi6_error_code(host);
			अगर (mrq->stop)
				mrq->stop->error = ret;
			अन्यथा
				mrq->data->error = ret;
			dev_warn(mmc_dev(host->mmc), "%s(): %d\n", __func__, ret);
			अवरोध;
		पूर्ण
		usdhi6_resp_cmd12(host);
		mrq->stop->error = 0;
		अवरोध;
	हाल USDHI6_WAIT_FOR_DATA_END:
		अगर (host->io_error) अणु
			mrq->data->error = usdhi6_error_code(host);
			dev_warn(mmc_dev(host->mmc), "%s(): %d\n", __func__,
				 mrq->data->error);
		पूर्ण
		अवरोध;
	शेष:
		cmd->error = -EFAULT;
		dev_err(mmc_dev(host->mmc), "Invalid state %u\n", host->रुको);
		usdhi6_request_करोne(host);
		वापस IRQ_HANDLED;
	पूर्ण

	अगर (io_रुको) अणु
		schedule_delayed_work(&host->समयout_work, host->समयout);
		/* Wait क्रम more data or ACCESS_END */
		अगर (!host->dma_active)
			usdhi6_रुको_क्रम_brwe(host, mrq->data->flags & MMC_DATA_READ);
		वापस IRQ_HANDLED;
	पूर्ण

	अगर (!cmd->error) अणु
		अगर (data) अणु
			अगर (!data->error) अणु
				अगर (host->रुको != USDHI6_WAIT_FOR_STOP &&
				    host->mrq->stop &&
				    !host->mrq->stop->error &&
				    !usdhi6_stop_cmd(host)) अणु
					/* Sending STOP */
					usdhi6_रुको_क्रम_resp(host);

					schedule_delayed_work(&host->समयout_work,
							      host->समयout);

					वापस IRQ_HANDLED;
				पूर्ण

				data->bytes_xfered = data->blocks * data->blksz;
			पूर्ण अन्यथा अणु
				/* Data error: might need to unmap the last page */
				dev_warn(mmc_dev(host->mmc), "%s(): data error %d\n",
					 __func__, data->error);
				usdhi6_sg_unmap(host, true);
			पूर्ण
		पूर्ण अन्यथा अगर (cmd->opcode == MMC_APP_CMD) अणु
			host->app_cmd = true;
		पूर्ण
	पूर्ण

	usdhi6_request_करोne(host);

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t usdhi6_sd(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा usdhi6_host *host = dev_id;
	u16 status, status2, error;

	status = usdhi6_पढ़ो(host, USDHI6_SD_INFO1) & ~host->status_mask &
		~USDHI6_SD_INFO1_CARD;
	status2 = usdhi6_पढ़ो(host, USDHI6_SD_INFO2) & ~host->status2_mask;

	usdhi6_only_cd(host);

	dev_dbg(mmc_dev(host->mmc),
		"IRQ status = 0x%08x, status2 = 0x%08x\n", status, status2);

	अगर (!status && !status2)
		वापस IRQ_NONE;

	error = status2 & USDHI6_SD_INFO2_ERR;

	/* Ack / clear पूर्णांकerrupts */
	अगर (USDHI6_SD_INFO1_IRQ & status)
		usdhi6_ग_लिखो(host, USDHI6_SD_INFO1,
			     0xffff & ~(USDHI6_SD_INFO1_IRQ & status));

	अगर (USDHI6_SD_INFO2_IRQ & status2) अणु
		अगर (error)
			/* In error हालs BWE and BRE aren't cleared स्वतःmatically */
			status2 |= USDHI6_SD_INFO2_BWE | USDHI6_SD_INFO2_BRE;

		usdhi6_ग_लिखो(host, USDHI6_SD_INFO2,
			     0xffff & ~(USDHI6_SD_INFO2_IRQ & status2));
	पूर्ण

	host->io_error = error;
	host->irq_status = status;

	अगर (error) अणु
		/* Don't pollute the log with unsupported command समयouts */
		अगर (host->रुको != USDHI6_WAIT_FOR_CMD ||
		    error != USDHI6_SD_INFO2_RSP_TOUT)
			dev_warn(mmc_dev(host->mmc),
				 "%s(): INFO2 error bits 0x%08x\n",
				 __func__, error);
		अन्यथा
			dev_dbg(mmc_dev(host->mmc),
				"%s(): INFO2 error bits 0x%08x\n",
				__func__, error);
	पूर्ण

	वापस IRQ_WAKE_THREAD;
पूर्ण

अटल irqवापस_t usdhi6_sdio(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा usdhi6_host *host = dev_id;
	u32 status = usdhi6_पढ़ो(host, USDHI6_SDIO_INFO1) & ~host->sdio_mask;

	dev_dbg(mmc_dev(host->mmc), "%s(): status 0x%x\n", __func__, status);

	अगर (!status)
		वापस IRQ_NONE;

	usdhi6_ग_लिखो(host, USDHI6_SDIO_INFO1, ~status);

	mmc_संकेत_sdio_irq(host->mmc);

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t usdhi6_cd(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा usdhi6_host *host = dev_id;
	काष्ठा mmc_host *mmc = host->mmc;
	u16 status;

	/* We're only पूर्णांकerested in hotplug events here */
	status = usdhi6_पढ़ो(host, USDHI6_SD_INFO1) & ~host->status_mask &
		USDHI6_SD_INFO1_CARD;

	अगर (!status)
		वापस IRQ_NONE;

	/* Ack */
	usdhi6_ग_लिखो(host, USDHI6_SD_INFO1, ~status);

	अगर (!work_pending(&mmc->detect.work) &&
	    (((status & USDHI6_SD_INFO1_CARD_INSERT) &&
	      !mmc->card) ||
	     ((status & USDHI6_SD_INFO1_CARD_EJECT) &&
	      mmc->card)))
		mmc_detect_change(mmc, msecs_to_jअगरfies(100));

	वापस IRQ_HANDLED;
पूर्ण

/*
 * Actually this should not be needed, अगर the built-in समयout works reliably in
 * the both PIO हालs and DMA never fails. But अगर DMA करोes fail, a समयout
 * handler might be the only way to catch the error.
 */
अटल व्योम usdhi6_समयout_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा delayed_work *d = to_delayed_work(work);
	काष्ठा usdhi6_host *host = container_of(d, काष्ठा usdhi6_host, समयout_work);
	काष्ठा mmc_request *mrq = host->mrq;
	काष्ठा mmc_data *data = mrq ? mrq->data : शून्य;
	काष्ठा scatterlist *sg;

	dev_warn(mmc_dev(host->mmc),
		 "%s timeout wait %u CMD%d: IRQ 0x%08x:0x%08x, last IRQ 0x%08x\n",
		 host->dma_active ? "DMA" : "PIO",
		 host->रुको, mrq ? mrq->cmd->opcode : -1,
		 usdhi6_पढ़ो(host, USDHI6_SD_INFO1),
		 usdhi6_पढ़ो(host, USDHI6_SD_INFO2), host->irq_status);

	अगर (host->dma_active) अणु
		usdhi6_dma_समाप्त(host);
		usdhi6_dma_stop_unmap(host);
	पूर्ण

	चयन (host->रुको) अणु
	शेष:
		dev_err(mmc_dev(host->mmc), "Invalid state %u\n", host->रुको);
		fallthrough;	/* mrq can be शून्य, but is impossible */
	हाल USDHI6_WAIT_FOR_CMD:
		usdhi6_error_code(host);
		अगर (mrq)
			mrq->cmd->error = -ETIMEDOUT;
		अवरोध;
	हाल USDHI6_WAIT_FOR_STOP:
		usdhi6_error_code(host);
		mrq->stop->error = -ETIMEDOUT;
		अवरोध;
	हाल USDHI6_WAIT_FOR_DMA:
	हाल USDHI6_WAIT_FOR_MREAD:
	हाल USDHI6_WAIT_FOR_MWRITE:
	हाल USDHI6_WAIT_FOR_READ:
	हाल USDHI6_WAIT_FOR_WRITE:
		sg = host->sg ?: data->sg;
		dev_dbg(mmc_dev(host->mmc),
			"%c: page #%u @ +0x%zx %ux%u in SG%u. Current SG %u bytes @ %u\n",
			data->flags & MMC_DATA_READ ? 'R' : 'W', host->page_idx,
			host->offset, data->blocks, data->blksz, data->sg_len,
			sg_dma_len(sg), sg->offset);
		usdhi6_sg_unmap(host, true);
		fallthrough;	/* page unmapped in USDHI6_WAIT_FOR_DATA_END */
	हाल USDHI6_WAIT_FOR_DATA_END:
		usdhi6_error_code(host);
		data->error = -ETIMEDOUT;
	पूर्ण

	अगर (mrq)
		usdhi6_request_करोne(host);
पूर्ण

/*			 Probe / release				*/

अटल स्थिर काष्ठा of_device_id usdhi6_of_match[] = अणु
	अणु.compatible = "renesas,usdhi6rol0"पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, usdhi6_of_match);

अटल पूर्णांक usdhi6_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा mmc_host *mmc;
	काष्ठा usdhi6_host *host;
	काष्ठा resource *res;
	पूर्णांक irq_cd, irq_sd, irq_sdio;
	u32 version;
	पूर्णांक ret;

	अगर (!dev->of_node)
		वापस -ENODEV;

	irq_cd = platक्रमm_get_irq_byname(pdev, "card detect");
	irq_sd = platक्रमm_get_irq_byname(pdev, "data");
	irq_sdio = platक्रमm_get_irq_byname(pdev, "SDIO");
	अगर (irq_sd < 0 || irq_sdio < 0)
		वापस -ENODEV;

	mmc = mmc_alloc_host(माप(काष्ठा usdhi6_host), dev);
	अगर (!mmc)
		वापस -ENOMEM;

	ret = mmc_regulator_get_supply(mmc);
	अगर (ret)
		जाओ e_मुक्त_mmc;

	ret = mmc_of_parse(mmc);
	अगर (ret < 0)
		जाओ e_मुक्त_mmc;

	host		= mmc_priv(mmc);
	host->mmc	= mmc;
	host->रुको	= USDHI6_WAIT_FOR_REQUEST;
	host->समयout	= msecs_to_jअगरfies(USDHI6_REQ_TIMEOUT_MS);
	/*
	 * We use a fixed समयout of 4s, hence inक्रमm the core about it. A
	 * future improvement should instead respect the cmd->busy_समयout.
	 */
	mmc->max_busy_समयout = USDHI6_REQ_TIMEOUT_MS;

	host->pinctrl = devm_pinctrl_get(&pdev->dev);
	अगर (IS_ERR(host->pinctrl)) अणु
		ret = PTR_ERR(host->pinctrl);
		जाओ e_मुक्त_mmc;
	पूर्ण

	host->pins_uhs = pinctrl_lookup_state(host->pinctrl, "state_uhs");

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	host->base = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(host->base)) अणु
		ret = PTR_ERR(host->base);
		जाओ e_मुक्त_mmc;
	पूर्ण

	host->clk = devm_clk_get(dev, शून्य);
	अगर (IS_ERR(host->clk)) अणु
		ret = PTR_ERR(host->clk);
		जाओ e_मुक्त_mmc;
	पूर्ण

	host->imclk = clk_get_rate(host->clk);

	ret = clk_prepare_enable(host->clk);
	अगर (ret < 0)
		जाओ e_मुक्त_mmc;

	version = usdhi6_पढ़ो(host, USDHI6_VERSION);
	अगर ((version & 0xfff) != 0xa0d) अणु
		dev_err(dev, "Version not recognized %x\n", version);
		जाओ e_clk_off;
	पूर्ण

	dev_info(dev, "A USDHI6ROL0 SD host detected with %d ports\n",
		 usdhi6_पढ़ो(host, USDHI6_SD_PORT_SEL) >> USDHI6_SD_PORT_SEL_PORTS_SHIFT);

	usdhi6_mask_all(host);

	अगर (irq_cd >= 0) अणु
		ret = devm_request_irq(dev, irq_cd, usdhi6_cd, 0,
				       dev_name(dev), host);
		अगर (ret < 0)
			जाओ e_clk_off;
	पूर्ण अन्यथा अणु
		mmc->caps |= MMC_CAP_NEEDS_POLL;
	पूर्ण

	ret = devm_request_thपढ़ोed_irq(dev, irq_sd, usdhi6_sd, usdhi6_sd_bh, 0,
			       dev_name(dev), host);
	अगर (ret < 0)
		जाओ e_clk_off;

	ret = devm_request_irq(dev, irq_sdio, usdhi6_sdio, 0,
			       dev_name(dev), host);
	अगर (ret < 0)
		जाओ e_clk_off;

	INIT_DELAYED_WORK(&host->समयout_work, usdhi6_समयout_work);

	usdhi6_dma_request(host, res->start);

	mmc->ops = &usdhi6_ops;
	mmc->caps |= MMC_CAP_SD_HIGHSPEED | MMC_CAP_MMC_HIGHSPEED |
		     MMC_CAP_SDIO_IRQ;
	/* Set .max_segs to some अक्रमom number. Feel मुक्त to adjust. */
	mmc->max_segs = 32;
	mmc->max_blk_size = 512;
	mmc->max_req_size = PAGE_SIZE * mmc->max_segs;
	mmc->max_blk_count = mmc->max_req_size / mmc->max_blk_size;
	/*
	 * Setting .max_seg_size to 1 page would simplअगरy our page-mapping code,
	 * But OTOH, having large segments makes DMA more efficient. We could
	 * check, whether we managed to get DMA and fall back to 1 page
	 * segments, but अगर we करो manage to obtain DMA and then it fails at
	 * run-समय and we fall back to PIO, we will जारी getting large
	 * segments. So, we wouldn't be able to get rid of the code anyway.
	 */
	mmc->max_seg_size = mmc->max_req_size;
	अगर (!mmc->f_max)
		mmc->f_max = host->imclk;
	mmc->f_min = host->imclk / 512;

	platक्रमm_set_drvdata(pdev, host);

	ret = mmc_add_host(mmc);
	अगर (ret < 0)
		जाओ e_release_dma;

	वापस 0;

e_release_dma:
	usdhi6_dma_release(host);
e_clk_off:
	clk_disable_unprepare(host->clk);
e_मुक्त_mmc:
	mmc_मुक्त_host(mmc);

	वापस ret;
पूर्ण

अटल पूर्णांक usdhi6_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा usdhi6_host *host = platक्रमm_get_drvdata(pdev);

	mmc_हटाओ_host(host->mmc);

	usdhi6_mask_all(host);
	cancel_delayed_work_sync(&host->समयout_work);
	usdhi6_dma_release(host);
	clk_disable_unprepare(host->clk);
	mmc_मुक्त_host(host->mmc);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver usdhi6_driver = अणु
	.probe		= usdhi6_probe,
	.हटाओ		= usdhi6_हटाओ,
	.driver		= अणु
		.name	= "usdhi6rol0",
		.probe_type = PROBE_PREFER_ASYNCHRONOUS,
		.of_match_table = usdhi6_of_match,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(usdhi6_driver);

MODULE_DESCRIPTION("Renesas usdhi6rol0 SD/SDIO host driver");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:usdhi6rol0");
MODULE_AUTHOR("Guennadi Liakhovetski <g.liakhovetski@gmx.de>");
