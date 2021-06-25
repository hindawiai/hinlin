<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Copyright (C) 2009-2010, Lars-Peter Clausen <lars@metafoo.de>
 *  Copyright (C) 2013, Imagination Technologies
 *
 *  JZ4740 SD/MMC controller driver
 */

#समावेश <linux/bitops.h>
#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/dmaengine.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/err.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/irq.h>
#समावेश <linux/mmc/host.h>
#समावेश <linux/mmc/slot-gpपन.स>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/pinctrl/consumer.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/scatterlist.h>

#समावेश <यंत्र/cacheflush.h>

#घोषणा JZ_REG_MMC_STRPCL	0x00
#घोषणा JZ_REG_MMC_STATUS	0x04
#घोषणा JZ_REG_MMC_CLKRT	0x08
#घोषणा JZ_REG_MMC_CMDAT	0x0C
#घोषणा JZ_REG_MMC_RESTO	0x10
#घोषणा JZ_REG_MMC_RDTO		0x14
#घोषणा JZ_REG_MMC_BLKLEN	0x18
#घोषणा JZ_REG_MMC_NOB		0x1C
#घोषणा JZ_REG_MMC_SNOB		0x20
#घोषणा JZ_REG_MMC_IMASK	0x24
#घोषणा JZ_REG_MMC_IREG		0x28
#घोषणा JZ_REG_MMC_CMD		0x2C
#घोषणा JZ_REG_MMC_ARG		0x30
#घोषणा JZ_REG_MMC_RESP_FIFO	0x34
#घोषणा JZ_REG_MMC_RXFIFO	0x38
#घोषणा JZ_REG_MMC_TXFIFO	0x3C
#घोषणा JZ_REG_MMC_LPM		0x40
#घोषणा JZ_REG_MMC_DMAC		0x44

#घोषणा JZ_MMC_STRPCL_EXIT_MULTIPLE BIT(7)
#घोषणा JZ_MMC_STRPCL_EXIT_TRANSFER BIT(6)
#घोषणा JZ_MMC_STRPCL_START_READWAIT BIT(5)
#घोषणा JZ_MMC_STRPCL_STOP_READWAIT BIT(4)
#घोषणा JZ_MMC_STRPCL_RESET BIT(3)
#घोषणा JZ_MMC_STRPCL_START_OP BIT(2)
#घोषणा JZ_MMC_STRPCL_CLOCK_CONTROL (BIT(1) | BIT(0))
#घोषणा JZ_MMC_STRPCL_CLOCK_STOP BIT(0)
#घोषणा JZ_MMC_STRPCL_CLOCK_START BIT(1)


#घोषणा JZ_MMC_STATUS_IS_RESETTING BIT(15)
#घोषणा JZ_MMC_STATUS_SDIO_INT_ACTIVE BIT(14)
#घोषणा JZ_MMC_STATUS_PRG_DONE BIT(13)
#घोषणा JZ_MMC_STATUS_DATA_TRAN_DONE BIT(12)
#घोषणा JZ_MMC_STATUS_END_CMD_RES BIT(11)
#घोषणा JZ_MMC_STATUS_DATA_FIFO_AFULL BIT(10)
#घोषणा JZ_MMC_STATUS_IS_READWAIT BIT(9)
#घोषणा JZ_MMC_STATUS_CLK_EN BIT(8)
#घोषणा JZ_MMC_STATUS_DATA_FIFO_FULL BIT(7)
#घोषणा JZ_MMC_STATUS_DATA_FIFO_EMPTY BIT(6)
#घोषणा JZ_MMC_STATUS_CRC_RES_ERR BIT(5)
#घोषणा JZ_MMC_STATUS_CRC_READ_ERROR BIT(4)
#घोषणा JZ_MMC_STATUS_TIMEOUT_WRITE BIT(3)
#घोषणा JZ_MMC_STATUS_CRC_WRITE_ERROR BIT(2)
#घोषणा JZ_MMC_STATUS_TIMEOUT_RES BIT(1)
#घोषणा JZ_MMC_STATUS_TIMEOUT_READ BIT(0)

#घोषणा JZ_MMC_STATUS_READ_ERROR_MASK (BIT(4) | BIT(0))
#घोषणा JZ_MMC_STATUS_WRITE_ERROR_MASK (BIT(3) | BIT(2))


#घोषणा JZ_MMC_CMDAT_IO_ABORT BIT(11)
#घोषणा JZ_MMC_CMDAT_BUS_WIDTH_4BIT BIT(10)
#घोषणा JZ_MMC_CMDAT_BUS_WIDTH_8BIT (BIT(10) | BIT(9))
#घोषणा	JZ_MMC_CMDAT_BUS_WIDTH_MASK (BIT(10) | BIT(9))
#घोषणा JZ_MMC_CMDAT_DMA_EN BIT(8)
#घोषणा JZ_MMC_CMDAT_INIT BIT(7)
#घोषणा JZ_MMC_CMDAT_BUSY BIT(6)
#घोषणा JZ_MMC_CMDAT_STREAM BIT(5)
#घोषणा JZ_MMC_CMDAT_WRITE BIT(4)
#घोषणा JZ_MMC_CMDAT_DATA_EN BIT(3)
#घोषणा JZ_MMC_CMDAT_RESPONSE_FORMAT (BIT(2) | BIT(1) | BIT(0))
#घोषणा JZ_MMC_CMDAT_RSP_R1 1
#घोषणा JZ_MMC_CMDAT_RSP_R2 2
#घोषणा JZ_MMC_CMDAT_RSP_R3 3

#घोषणा JZ_MMC_IRQ_SDIO BIT(7)
#घोषणा JZ_MMC_IRQ_TXFIFO_WR_REQ BIT(6)
#घोषणा JZ_MMC_IRQ_RXFIFO_RD_REQ BIT(5)
#घोषणा JZ_MMC_IRQ_END_CMD_RES BIT(2)
#घोषणा JZ_MMC_IRQ_PRG_DONE BIT(1)
#घोषणा JZ_MMC_IRQ_DATA_TRAN_DONE BIT(0)

#घोषणा JZ_MMC_DMAC_DMA_SEL BIT(1)
#घोषणा JZ_MMC_DMAC_DMA_EN BIT(0)

#घोषणा	JZ_MMC_LPM_DRV_RISING BIT(31)
#घोषणा	JZ_MMC_LPM_DRV_RISING_QTR_PHASE_DLY BIT(31)
#घोषणा	JZ_MMC_LPM_DRV_RISING_1NS_DLY BIT(30)
#घोषणा	JZ_MMC_LPM_SMP_RISING_QTR_OR_HALF_PHASE_DLY BIT(29)
#घोषणा	JZ_MMC_LPM_LOW_POWER_MODE_EN BIT(0)

#घोषणा JZ_MMC_CLK_RATE 24000000
#घोषणा JZ_MMC_REQ_TIMEOUT_MS 5000

क्रमागत jz4740_mmc_version अणु
	JZ_MMC_JZ4740,
	JZ_MMC_JZ4725B,
	JZ_MMC_JZ4760,
	JZ_MMC_JZ4780,
	JZ_MMC_X1000,
पूर्ण;

क्रमागत jz4740_mmc_state अणु
	JZ4740_MMC_STATE_READ_RESPONSE,
	JZ4740_MMC_STATE_TRANSFER_DATA,
	JZ4740_MMC_STATE_SEND_STOP,
	JZ4740_MMC_STATE_DONE,
पूर्ण;

/*
 * The MMC core allows to prepare a mmc_request जबतक another mmc_request
 * is in-flight. This is used via the pre_req/post_req hooks.
 * This driver uses the pre_req/post_req hooks to map/unmap the mmc_request.
 * Following what other drivers करो (sdhci, dw_mmc) we use the following cookie
 * flags to keep track of the mmc_request mapping state.
 *
 * COOKIE_UNMAPPED: the request is not mapped.
 * COOKIE_PREMAPPED: the request was mapped in pre_req,
 * and should be unmapped in post_req.
 * COOKIE_MAPPED: the request was mapped in the irq handler,
 * and should be unmapped beक्रमe mmc_request_करोne is called..
 */
क्रमागत jz4780_cookie अणु
	COOKIE_UNMAPPED = 0,
	COOKIE_PREMAPPED,
	COOKIE_MAPPED,
पूर्ण;

काष्ठा jz4740_mmc_host अणु
	काष्ठा mmc_host *mmc;
	काष्ठा platक्रमm_device *pdev;
	काष्ठा clk *clk;

	क्रमागत jz4740_mmc_version version;

	पूर्णांक irq;

	व्योम __iomem *base;
	काष्ठा resource *mem_res;
	काष्ठा mmc_request *req;
	काष्ठा mmc_command *cmd;

	अचिन्हित दीर्घ रुकोing;

	uपूर्णांक32_t cmdat;

	uपूर्णांक32_t irq_mask;

	spinlock_t lock;

	काष्ठा समयr_list समयout_समयr;
	काष्ठा sg_mapping_iter miter;
	क्रमागत jz4740_mmc_state state;

	/* DMA support */
	काष्ठा dma_chan *dma_rx;
	काष्ठा dma_chan *dma_tx;
	bool use_dma;

/* The DMA trigger level is 8 words, that is to say, the DMA पढ़ो
 * trigger is when data words in MSC_RXFIFO is >= 8 and the DMA ग_लिखो
 * trigger is when data words in MSC_TXFIFO is < 8.
 */
#घोषणा JZ4740_MMC_FIFO_HALF_SIZE 8
पूर्ण;

अटल व्योम jz4740_mmc_ग_लिखो_irq_mask(काष्ठा jz4740_mmc_host *host,
				      uपूर्णांक32_t val)
अणु
	अगर (host->version >= JZ_MMC_JZ4725B)
		वापस ग_लिखोl(val, host->base + JZ_REG_MMC_IMASK);
	अन्यथा
		वापस ग_लिखोw(val, host->base + JZ_REG_MMC_IMASK);
पूर्ण

अटल व्योम jz4740_mmc_ग_लिखो_irq_reg(काष्ठा jz4740_mmc_host *host,
				     uपूर्णांक32_t val)
अणु
	अगर (host->version >= JZ_MMC_JZ4780)
		ग_लिखोl(val, host->base + JZ_REG_MMC_IREG);
	अन्यथा
		ग_लिखोw(val, host->base + JZ_REG_MMC_IREG);
पूर्ण

अटल uपूर्णांक32_t jz4740_mmc_पढ़ो_irq_reg(काष्ठा jz4740_mmc_host *host)
अणु
	अगर (host->version >= JZ_MMC_JZ4780)
		वापस पढ़ोl(host->base + JZ_REG_MMC_IREG);
	अन्यथा
		वापस पढ़ोw(host->base + JZ_REG_MMC_IREG);
पूर्ण

/*----------------------------------------------------------------------------*/
/* DMA infraकाष्ठाure */

अटल व्योम jz4740_mmc_release_dma_channels(काष्ठा jz4740_mmc_host *host)
अणु
	अगर (!host->use_dma)
		वापस;

	dma_release_channel(host->dma_tx);
	dma_release_channel(host->dma_rx);
पूर्ण

अटल पूर्णांक jz4740_mmc_acquire_dma_channels(काष्ठा jz4740_mmc_host *host)
अणु
	host->dma_tx = dma_request_chan(mmc_dev(host->mmc), "tx");
	अगर (IS_ERR(host->dma_tx)) अणु
		dev_err(mmc_dev(host->mmc), "Failed to get dma_tx channel\n");
		वापस PTR_ERR(host->dma_tx);
	पूर्ण

	host->dma_rx = dma_request_chan(mmc_dev(host->mmc), "rx");
	अगर (IS_ERR(host->dma_rx)) अणु
		dev_err(mmc_dev(host->mmc), "Failed to get dma_rx channel\n");
		dma_release_channel(host->dma_tx);
		वापस PTR_ERR(host->dma_rx);
	पूर्ण

	वापस 0;
पूर्ण

अटल अंतरभूत काष्ठा dma_chan *jz4740_mmc_get_dma_chan(काष्ठा jz4740_mmc_host *host,
						       काष्ठा mmc_data *data)
अणु
	वापस (data->flags & MMC_DATA_READ) ? host->dma_rx : host->dma_tx;
पूर्ण

अटल व्योम jz4740_mmc_dma_unmap(काष्ठा jz4740_mmc_host *host,
				 काष्ठा mmc_data *data)
अणु
	काष्ठा dma_chan *chan = jz4740_mmc_get_dma_chan(host, data);
	क्रमागत dma_data_direction dir = mmc_get_dma_dir(data);

	dma_unmap_sg(chan->device->dev, data->sg, data->sg_len, dir);
	data->host_cookie = COOKIE_UNMAPPED;
पूर्ण

/* Prepares DMA data क्रम current or next transfer.
 * A request can be in-flight when this is called.
 */
अटल पूर्णांक jz4740_mmc_prepare_dma_data(काष्ठा jz4740_mmc_host *host,
				       काष्ठा mmc_data *data,
				       पूर्णांक cookie)
अणु
	काष्ठा dma_chan *chan = jz4740_mmc_get_dma_chan(host, data);
	क्रमागत dma_data_direction dir = mmc_get_dma_dir(data);
	पूर्णांक sg_count;

	अगर (data->host_cookie == COOKIE_PREMAPPED)
		वापस data->sg_count;

	sg_count = dma_map_sg(chan->device->dev,
			data->sg,
			data->sg_len,
			dir);

	अगर (sg_count <= 0) अणु
		dev_err(mmc_dev(host->mmc),
			"Failed to map scatterlist for DMA operation\n");
		वापस -EINVAL;
	पूर्ण

	data->sg_count = sg_count;
	data->host_cookie = cookie;

	वापस data->sg_count;
पूर्ण

अटल पूर्णांक jz4740_mmc_start_dma_transfer(काष्ठा jz4740_mmc_host *host,
					 काष्ठा mmc_data *data)
अणु
	काष्ठा dma_chan *chan = jz4740_mmc_get_dma_chan(host, data);
	काष्ठा dma_async_tx_descriptor *desc;
	काष्ठा dma_slave_config conf = अणु
		.src_addr_width = DMA_SLAVE_BUSWIDTH_4_BYTES,
		.dst_addr_width = DMA_SLAVE_BUSWIDTH_4_BYTES,
		.src_maxburst = JZ4740_MMC_FIFO_HALF_SIZE,
		.dst_maxburst = JZ4740_MMC_FIFO_HALF_SIZE,
	पूर्ण;
	पूर्णांक sg_count;

	अगर (data->flags & MMC_DATA_WRITE) अणु
		conf.direction = DMA_MEM_TO_DEV;
		conf.dst_addr = host->mem_res->start + JZ_REG_MMC_TXFIFO;
	पूर्ण अन्यथा अणु
		conf.direction = DMA_DEV_TO_MEM;
		conf.src_addr = host->mem_res->start + JZ_REG_MMC_RXFIFO;
	पूर्ण

	sg_count = jz4740_mmc_prepare_dma_data(host, data, COOKIE_MAPPED);
	अगर (sg_count < 0)
		वापस sg_count;

	dmaengine_slave_config(chan, &conf);
	desc = dmaengine_prep_slave_sg(chan, data->sg, sg_count,
			conf.direction,
			DMA_PREP_INTERRUPT | DMA_CTRL_ACK);
	अगर (!desc) अणु
		dev_err(mmc_dev(host->mmc),
			"Failed to allocate DMA %s descriptor",
			 conf.direction == DMA_MEM_TO_DEV ? "TX" : "RX");
		जाओ dma_unmap;
	पूर्ण

	dmaengine_submit(desc);
	dma_async_issue_pending(chan);

	वापस 0;

dma_unmap:
	अगर (data->host_cookie == COOKIE_MAPPED)
		jz4740_mmc_dma_unmap(host, data);
	वापस -ENOMEM;
पूर्ण

अटल व्योम jz4740_mmc_pre_request(काष्ठा mmc_host *mmc,
				   काष्ठा mmc_request *mrq)
अणु
	काष्ठा jz4740_mmc_host *host = mmc_priv(mmc);
	काष्ठा mmc_data *data = mrq->data;

	अगर (!host->use_dma)
		वापस;

	data->host_cookie = COOKIE_UNMAPPED;
	अगर (jz4740_mmc_prepare_dma_data(host, data, COOKIE_PREMAPPED) < 0)
		data->host_cookie = COOKIE_UNMAPPED;
पूर्ण

अटल व्योम jz4740_mmc_post_request(काष्ठा mmc_host *mmc,
				    काष्ठा mmc_request *mrq,
				    पूर्णांक err)
अणु
	काष्ठा jz4740_mmc_host *host = mmc_priv(mmc);
	काष्ठा mmc_data *data = mrq->data;

	अगर (data && data->host_cookie != COOKIE_UNMAPPED)
		jz4740_mmc_dma_unmap(host, data);

	अगर (err) अणु
		काष्ठा dma_chan *chan = jz4740_mmc_get_dma_chan(host, data);

		dmaengine_terminate_all(chan);
	पूर्ण
पूर्ण

/*----------------------------------------------------------------------------*/

अटल व्योम jz4740_mmc_set_irq_enabled(काष्ठा jz4740_mmc_host *host,
	अचिन्हित पूर्णांक irq, bool enabled)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&host->lock, flags);
	अगर (enabled)
		host->irq_mask &= ~irq;
	अन्यथा
		host->irq_mask |= irq;

	jz4740_mmc_ग_लिखो_irq_mask(host, host->irq_mask);
	spin_unlock_irqrestore(&host->lock, flags);
पूर्ण

अटल व्योम jz4740_mmc_घड़ी_enable(काष्ठा jz4740_mmc_host *host,
	bool start_transfer)
अणु
	uपूर्णांक16_t val = JZ_MMC_STRPCL_CLOCK_START;

	अगर (start_transfer)
		val |= JZ_MMC_STRPCL_START_OP;

	ग_लिखोw(val, host->base + JZ_REG_MMC_STRPCL);
पूर्ण

अटल व्योम jz4740_mmc_घड़ी_disable(काष्ठा jz4740_mmc_host *host)
अणु
	uपूर्णांक32_t status;
	अचिन्हित पूर्णांक समयout = 1000;

	ग_लिखोw(JZ_MMC_STRPCL_CLOCK_STOP, host->base + JZ_REG_MMC_STRPCL);
	करो अणु
		status = पढ़ोl(host->base + JZ_REG_MMC_STATUS);
	पूर्ण जबतक (status & JZ_MMC_STATUS_CLK_EN && --समयout);
पूर्ण

अटल व्योम jz4740_mmc_reset(काष्ठा jz4740_mmc_host *host)
अणु
	uपूर्णांक32_t status;
	अचिन्हित पूर्णांक समयout = 1000;

	ग_लिखोw(JZ_MMC_STRPCL_RESET, host->base + JZ_REG_MMC_STRPCL);
	udelay(10);
	करो अणु
		status = पढ़ोl(host->base + JZ_REG_MMC_STATUS);
	पूर्ण जबतक (status & JZ_MMC_STATUS_IS_RESETTING && --समयout);
पूर्ण

अटल व्योम jz4740_mmc_request_करोne(काष्ठा jz4740_mmc_host *host)
अणु
	काष्ठा mmc_request *req;
	काष्ठा mmc_data *data;

	req = host->req;
	data = req->data;
	host->req = शून्य;

	अगर (data && data->host_cookie == COOKIE_MAPPED)
		jz4740_mmc_dma_unmap(host, data);
	mmc_request_करोne(host->mmc, req);
पूर्ण

अटल अचिन्हित पूर्णांक jz4740_mmc_poll_irq(काष्ठा jz4740_mmc_host *host,
	अचिन्हित पूर्णांक irq)
अणु
	अचिन्हित पूर्णांक समयout = 0x800;
	uपूर्णांक32_t status;

	करो अणु
		status = jz4740_mmc_पढ़ो_irq_reg(host);
	पूर्ण जबतक (!(status & irq) && --समयout);

	अगर (समयout == 0) अणु
		set_bit(0, &host->रुकोing);
		mod_समयr(&host->समयout_समयr,
			  jअगरfies + msecs_to_jअगरfies(JZ_MMC_REQ_TIMEOUT_MS));
		jz4740_mmc_set_irq_enabled(host, irq, true);
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल व्योम jz4740_mmc_transfer_check_state(काष्ठा jz4740_mmc_host *host,
	काष्ठा mmc_data *data)
अणु
	पूर्णांक status;

	status = पढ़ोl(host->base + JZ_REG_MMC_STATUS);
	अगर (status & JZ_MMC_STATUS_WRITE_ERROR_MASK) अणु
		अगर (status & (JZ_MMC_STATUS_TIMEOUT_WRITE)) अणु
			host->req->cmd->error = -ETIMEDOUT;
			data->error = -ETIMEDOUT;
		पूर्ण अन्यथा अणु
			host->req->cmd->error = -EIO;
			data->error = -EIO;
		पूर्ण
	पूर्ण अन्यथा अगर (status & JZ_MMC_STATUS_READ_ERROR_MASK) अणु
		अगर (status & (JZ_MMC_STATUS_TIMEOUT_READ)) अणु
			host->req->cmd->error = -ETIMEDOUT;
			data->error = -ETIMEDOUT;
		पूर्ण अन्यथा अणु
			host->req->cmd->error = -EIO;
			data->error = -EIO;
		पूर्ण
	पूर्ण
पूर्ण

अटल bool jz4740_mmc_ग_लिखो_data(काष्ठा jz4740_mmc_host *host,
	काष्ठा mmc_data *data)
अणु
	काष्ठा sg_mapping_iter *miter = &host->miter;
	व्योम __iomem *fअगरo_addr = host->base + JZ_REG_MMC_TXFIFO;
	uपूर्णांक32_t *buf;
	bool समयout;
	माप_प्रकार i, j;

	जबतक (sg_miter_next(miter)) अणु
		buf = miter->addr;
		i = miter->length / 4;
		j = i / 8;
		i = i & 0x7;
		जबतक (j) अणु
			समयout = jz4740_mmc_poll_irq(host, JZ_MMC_IRQ_TXFIFO_WR_REQ);
			अगर (unlikely(समयout))
				जाओ poll_समयout;

			ग_लिखोl(buf[0], fअगरo_addr);
			ग_लिखोl(buf[1], fअगरo_addr);
			ग_लिखोl(buf[2], fअगरo_addr);
			ग_लिखोl(buf[3], fअगरo_addr);
			ग_लिखोl(buf[4], fअगरo_addr);
			ग_लिखोl(buf[5], fअगरo_addr);
			ग_लिखोl(buf[6], fअगरo_addr);
			ग_लिखोl(buf[7], fअगरo_addr);
			buf += 8;
			--j;
		पूर्ण
		अगर (unlikely(i)) अणु
			समयout = jz4740_mmc_poll_irq(host, JZ_MMC_IRQ_TXFIFO_WR_REQ);
			अगर (unlikely(समयout))
				जाओ poll_समयout;

			जबतक (i) अणु
				ग_लिखोl(*buf, fअगरo_addr);
				++buf;
				--i;
			पूर्ण
		पूर्ण
		data->bytes_xfered += miter->length;
	पूर्ण
	sg_miter_stop(miter);

	वापस false;

poll_समयout:
	miter->consumed = (व्योम *)buf - miter->addr;
	data->bytes_xfered += miter->consumed;
	sg_miter_stop(miter);

	वापस true;
पूर्ण

अटल bool jz4740_mmc_पढ़ो_data(काष्ठा jz4740_mmc_host *host,
				काष्ठा mmc_data *data)
अणु
	काष्ठा sg_mapping_iter *miter = &host->miter;
	व्योम __iomem *fअगरo_addr = host->base + JZ_REG_MMC_RXFIFO;
	uपूर्णांक32_t *buf;
	uपूर्णांक32_t d;
	uपूर्णांक32_t status;
	माप_प्रकार i, j;
	अचिन्हित पूर्णांक समयout;

	जबतक (sg_miter_next(miter)) अणु
		buf = miter->addr;
		i = miter->length;
		j = i / 32;
		i = i & 0x1f;
		जबतक (j) अणु
			समयout = jz4740_mmc_poll_irq(host, JZ_MMC_IRQ_RXFIFO_RD_REQ);
			अगर (unlikely(समयout))
				जाओ poll_समयout;

			buf[0] = पढ़ोl(fअगरo_addr);
			buf[1] = पढ़ोl(fअगरo_addr);
			buf[2] = पढ़ोl(fअगरo_addr);
			buf[3] = पढ़ोl(fअगरo_addr);
			buf[4] = पढ़ोl(fअगरo_addr);
			buf[5] = पढ़ोl(fअगरo_addr);
			buf[6] = पढ़ोl(fअगरo_addr);
			buf[7] = पढ़ोl(fअगरo_addr);

			buf += 8;
			--j;
		पूर्ण

		अगर (unlikely(i)) अणु
			समयout = jz4740_mmc_poll_irq(host, JZ_MMC_IRQ_RXFIFO_RD_REQ);
			अगर (unlikely(समयout))
				जाओ poll_समयout;

			जबतक (i >= 4) अणु
				*buf++ = पढ़ोl(fअगरo_addr);
				i -= 4;
			पूर्ण
			अगर (unlikely(i > 0)) अणु
				d = पढ़ोl(fअगरo_addr);
				स_नकल(buf, &d, i);
			पूर्ण
		पूर्ण
		data->bytes_xfered += miter->length;

		/* This can go away once MIPS implements
		 * flush_kernel_dcache_page */
		flush_dcache_page(miter->page);
	पूर्ण
	sg_miter_stop(miter);

	/* For whatever reason there is someसमय one word more in the fअगरo then
	 * requested */
	समयout = 1000;
	status = पढ़ोl(host->base + JZ_REG_MMC_STATUS);
	जबतक (!(status & JZ_MMC_STATUS_DATA_FIFO_EMPTY) && --समयout) अणु
		d = पढ़ोl(fअगरo_addr);
		status = पढ़ोl(host->base + JZ_REG_MMC_STATUS);
	पूर्ण

	वापस false;

poll_समयout:
	miter->consumed = (व्योम *)buf - miter->addr;
	data->bytes_xfered += miter->consumed;
	sg_miter_stop(miter);

	वापस true;
पूर्ण

अटल व्योम jz4740_mmc_समयout(काष्ठा समयr_list *t)
अणु
	काष्ठा jz4740_mmc_host *host = from_समयr(host, t, समयout_समयr);

	अगर (!test_and_clear_bit(0, &host->रुकोing))
		वापस;

	jz4740_mmc_set_irq_enabled(host, JZ_MMC_IRQ_END_CMD_RES, false);

	host->req->cmd->error = -ETIMEDOUT;
	jz4740_mmc_request_करोne(host);
पूर्ण

अटल व्योम jz4740_mmc_पढ़ो_response(काष्ठा jz4740_mmc_host *host,
	काष्ठा mmc_command *cmd)
अणु
	पूर्णांक i;
	uपूर्णांक16_t पंचांगp;
	व्योम __iomem *fअगरo_addr = host->base + JZ_REG_MMC_RESP_FIFO;

	अगर (cmd->flags & MMC_RSP_136) अणु
		पंचांगp = पढ़ोw(fअगरo_addr);
		क्रम (i = 0; i < 4; ++i) अणु
			cmd->resp[i] = पंचांगp << 24;
			पंचांगp = पढ़ोw(fअगरo_addr);
			cmd->resp[i] |= पंचांगp << 8;
			पंचांगp = पढ़ोw(fअगरo_addr);
			cmd->resp[i] |= पंचांगp >> 8;
		पूर्ण
	पूर्ण अन्यथा अणु
		cmd->resp[0] = पढ़ोw(fअगरo_addr) << 24;
		cmd->resp[0] |= पढ़ोw(fअगरo_addr) << 8;
		cmd->resp[0] |= पढ़ोw(fअगरo_addr) & 0xff;
	पूर्ण
पूर्ण

अटल व्योम jz4740_mmc_send_command(काष्ठा jz4740_mmc_host *host,
	काष्ठा mmc_command *cmd)
अणु
	uपूर्णांक32_t cmdat = host->cmdat;

	host->cmdat &= ~JZ_MMC_CMDAT_INIT;
	jz4740_mmc_घड़ी_disable(host);

	host->cmd = cmd;

	अगर (cmd->flags & MMC_RSP_BUSY)
		cmdat |= JZ_MMC_CMDAT_BUSY;

	चयन (mmc_resp_type(cmd)) अणु
	हाल MMC_RSP_R1B:
	हाल MMC_RSP_R1:
		cmdat |= JZ_MMC_CMDAT_RSP_R1;
		अवरोध;
	हाल MMC_RSP_R2:
		cmdat |= JZ_MMC_CMDAT_RSP_R2;
		अवरोध;
	हाल MMC_RSP_R3:
		cmdat |= JZ_MMC_CMDAT_RSP_R3;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	अगर (cmd->data) अणु
		cmdat |= JZ_MMC_CMDAT_DATA_EN;
		अगर (cmd->data->flags & MMC_DATA_WRITE)
			cmdat |= JZ_MMC_CMDAT_WRITE;
		अगर (host->use_dma) अणु
			/*
			 * The 4780's MMC controller has पूर्णांकegrated DMA ability
			 * in addition to being able to use the बाह्यal DMA
			 * controller. It moves DMA control bits to a separate
			 * रेजिस्टर. The DMA_SEL bit chooses the बाह्यal
			 * controller over the पूर्णांकegrated one. Earlier SoCs
			 * can only use the बाह्यal controller, and have a
			 * single DMA enable bit in CMDAT.
			 */
			अगर (host->version >= JZ_MMC_JZ4780) अणु
				ग_लिखोl(JZ_MMC_DMAC_DMA_EN | JZ_MMC_DMAC_DMA_SEL,
				       host->base + JZ_REG_MMC_DMAC);
			पूर्ण अन्यथा अणु
				cmdat |= JZ_MMC_CMDAT_DMA_EN;
			पूर्ण
		पूर्ण अन्यथा अगर (host->version >= JZ_MMC_JZ4780) अणु
			ग_लिखोl(0, host->base + JZ_REG_MMC_DMAC);
		पूर्ण

		ग_लिखोw(cmd->data->blksz, host->base + JZ_REG_MMC_BLKLEN);
		ग_लिखोw(cmd->data->blocks, host->base + JZ_REG_MMC_NOB);
	पूर्ण

	ग_लिखोb(cmd->opcode, host->base + JZ_REG_MMC_CMD);
	ग_लिखोl(cmd->arg, host->base + JZ_REG_MMC_ARG);
	ग_लिखोl(cmdat, host->base + JZ_REG_MMC_CMDAT);

	jz4740_mmc_घड़ी_enable(host, 1);
पूर्ण

अटल व्योम jz_mmc_prepare_data_transfer(काष्ठा jz4740_mmc_host *host)
अणु
	काष्ठा mmc_command *cmd = host->req->cmd;
	काष्ठा mmc_data *data = cmd->data;
	पूर्णांक direction;

	अगर (data->flags & MMC_DATA_READ)
		direction = SG_MITER_TO_SG;
	अन्यथा
		direction = SG_MITER_FROM_SG;

	sg_miter_start(&host->miter, data->sg, data->sg_len, direction);
पूर्ण


अटल irqवापस_t jz_mmc_irq_worker(पूर्णांक irq, व्योम *devid)
अणु
	काष्ठा jz4740_mmc_host *host = (काष्ठा jz4740_mmc_host *)devid;
	काष्ठा mmc_command *cmd = host->req->cmd;
	काष्ठा mmc_request *req = host->req;
	काष्ठा mmc_data *data = cmd->data;
	bool समयout = false;

	अगर (cmd->error)
		host->state = JZ4740_MMC_STATE_DONE;

	चयन (host->state) अणु
	हाल JZ4740_MMC_STATE_READ_RESPONSE:
		अगर (cmd->flags & MMC_RSP_PRESENT)
			jz4740_mmc_पढ़ो_response(host, cmd);

		अगर (!data)
			अवरोध;

		jz_mmc_prepare_data_transfer(host);
		fallthrough;

	हाल JZ4740_MMC_STATE_TRANSFER_DATA:
		अगर (host->use_dma) अणु
			/* Use DMA अगर enabled.
			 * Data transfer direction is defined later by
			 * relying on data flags in
			 * jz4740_mmc_prepare_dma_data() and
			 * jz4740_mmc_start_dma_transfer().
			 */
			समयout = jz4740_mmc_start_dma_transfer(host, data);
			data->bytes_xfered = data->blocks * data->blksz;
		पूर्ण अन्यथा अगर (data->flags & MMC_DATA_READ)
			/* Use PIO अगर DMA is not enabled.
			 * Data transfer direction was defined beक्रमe
			 * by relying on data flags in
			 * jz_mmc_prepare_data_transfer().
			 */
			समयout = jz4740_mmc_पढ़ो_data(host, data);
		अन्यथा
			समयout = jz4740_mmc_ग_लिखो_data(host, data);

		अगर (unlikely(समयout)) अणु
			host->state = JZ4740_MMC_STATE_TRANSFER_DATA;
			अवरोध;
		पूर्ण

		jz4740_mmc_transfer_check_state(host, data);

		समयout = jz4740_mmc_poll_irq(host, JZ_MMC_IRQ_DATA_TRAN_DONE);
		अगर (unlikely(समयout)) अणु
			host->state = JZ4740_MMC_STATE_SEND_STOP;
			अवरोध;
		पूर्ण
		jz4740_mmc_ग_लिखो_irq_reg(host, JZ_MMC_IRQ_DATA_TRAN_DONE);
		fallthrough;

	हाल JZ4740_MMC_STATE_SEND_STOP:
		अगर (!req->stop)
			अवरोध;

		jz4740_mmc_send_command(host, req->stop);

		अगर (mmc_resp_type(req->stop) & MMC_RSP_BUSY) अणु
			समयout = jz4740_mmc_poll_irq(host,
						      JZ_MMC_IRQ_PRG_DONE);
			अगर (समयout) अणु
				host->state = JZ4740_MMC_STATE_DONE;
				अवरोध;
			पूर्ण
		पूर्ण
	हाल JZ4740_MMC_STATE_DONE:
		अवरोध;
	पूर्ण

	अगर (!समयout)
		jz4740_mmc_request_करोne(host);

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t jz_mmc_irq(पूर्णांक irq, व्योम *devid)
अणु
	काष्ठा jz4740_mmc_host *host = devid;
	काष्ठा mmc_command *cmd = host->cmd;
	uपूर्णांक32_t irq_reg, status, पंचांगp;

	status = पढ़ोl(host->base + JZ_REG_MMC_STATUS);
	irq_reg = jz4740_mmc_पढ़ो_irq_reg(host);

	पंचांगp = irq_reg;
	irq_reg &= ~host->irq_mask;

	पंचांगp &= ~(JZ_MMC_IRQ_TXFIFO_WR_REQ | JZ_MMC_IRQ_RXFIFO_RD_REQ |
		JZ_MMC_IRQ_PRG_DONE | JZ_MMC_IRQ_DATA_TRAN_DONE);

	अगर (पंचांगp != irq_reg)
		jz4740_mmc_ग_लिखो_irq_reg(host, पंचांगp & ~irq_reg);

	अगर (irq_reg & JZ_MMC_IRQ_SDIO) अणु
		jz4740_mmc_ग_लिखो_irq_reg(host, JZ_MMC_IRQ_SDIO);
		mmc_संकेत_sdio_irq(host->mmc);
		irq_reg &= ~JZ_MMC_IRQ_SDIO;
	पूर्ण

	अगर (host->req && cmd && irq_reg) अणु
		अगर (test_and_clear_bit(0, &host->रुकोing)) अणु
			del_समयr(&host->समयout_समयr);

			अगर (status & JZ_MMC_STATUS_TIMEOUT_RES) अणु
				cmd->error = -ETIMEDOUT;
			पूर्ण अन्यथा अगर (status & JZ_MMC_STATUS_CRC_RES_ERR) अणु
				cmd->error = -EIO;
			पूर्ण अन्यथा अगर (status & (JZ_MMC_STATUS_CRC_READ_ERROR |
				    JZ_MMC_STATUS_CRC_WRITE_ERROR)) अणु
				अगर (cmd->data)
					cmd->data->error = -EIO;
				cmd->error = -EIO;
			पूर्ण

			jz4740_mmc_set_irq_enabled(host, irq_reg, false);
			jz4740_mmc_ग_लिखो_irq_reg(host, irq_reg);

			वापस IRQ_WAKE_THREAD;
		पूर्ण
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक jz4740_mmc_set_घड़ी_rate(काष्ठा jz4740_mmc_host *host, पूर्णांक rate)
अणु
	पूर्णांक भाग = 0;
	पूर्णांक real_rate;

	jz4740_mmc_घड़ी_disable(host);
	clk_set_rate(host->clk, host->mmc->f_max);

	real_rate = clk_get_rate(host->clk);

	जबतक (real_rate > rate && भाग < 7) अणु
		++भाग;
		real_rate >>= 1;
	पूर्ण

	ग_लिखोw(भाग, host->base + JZ_REG_MMC_CLKRT);

	अगर (real_rate > 25000000) अणु
		अगर (host->version >= JZ_MMC_X1000) अणु
			ग_लिखोl(JZ_MMC_LPM_DRV_RISING_QTR_PHASE_DLY |
				   JZ_MMC_LPM_SMP_RISING_QTR_OR_HALF_PHASE_DLY |
				   JZ_MMC_LPM_LOW_POWER_MODE_EN,
				   host->base + JZ_REG_MMC_LPM);
		पूर्ण अन्यथा अगर (host->version >= JZ_MMC_JZ4760) अणु
			ग_लिखोl(JZ_MMC_LPM_DRV_RISING |
				   JZ_MMC_LPM_LOW_POWER_MODE_EN,
				   host->base + JZ_REG_MMC_LPM);
		पूर्ण अन्यथा अगर (host->version >= JZ_MMC_JZ4725B)
			ग_लिखोl(JZ_MMC_LPM_LOW_POWER_MODE_EN,
				   host->base + JZ_REG_MMC_LPM);
	पूर्ण

	वापस real_rate;
पूर्ण

अटल व्योम jz4740_mmc_request(काष्ठा mmc_host *mmc, काष्ठा mmc_request *req)
अणु
	काष्ठा jz4740_mmc_host *host = mmc_priv(mmc);

	host->req = req;

	jz4740_mmc_ग_लिखो_irq_reg(host, ~0);
	jz4740_mmc_set_irq_enabled(host, JZ_MMC_IRQ_END_CMD_RES, true);

	host->state = JZ4740_MMC_STATE_READ_RESPONSE;
	set_bit(0, &host->रुकोing);
	mod_समयr(&host->समयout_समयr,
		  jअगरfies + msecs_to_jअगरfies(JZ_MMC_REQ_TIMEOUT_MS));
	jz4740_mmc_send_command(host, req->cmd);
पूर्ण

अटल व्योम jz4740_mmc_set_ios(काष्ठा mmc_host *mmc, काष्ठा mmc_ios *ios)
अणु
	काष्ठा jz4740_mmc_host *host = mmc_priv(mmc);
	अगर (ios->घड़ी)
		jz4740_mmc_set_घड़ी_rate(host, ios->घड़ी);

	चयन (ios->घातer_mode) अणु
	हाल MMC_POWER_UP:
		jz4740_mmc_reset(host);
		अगर (!IS_ERR(mmc->supply.vmmc))
			mmc_regulator_set_ocr(mmc, mmc->supply.vmmc, ios->vdd);
		host->cmdat |= JZ_MMC_CMDAT_INIT;
		clk_prepare_enable(host->clk);
		अवरोध;
	हाल MMC_POWER_ON:
		अवरोध;
	शेष:
		अगर (!IS_ERR(mmc->supply.vmmc))
			mmc_regulator_set_ocr(mmc, mmc->supply.vmmc, 0);
		clk_disable_unprepare(host->clk);
		अवरोध;
	पूर्ण

	चयन (ios->bus_width) अणु
	हाल MMC_BUS_WIDTH_1:
		host->cmdat &= ~JZ_MMC_CMDAT_BUS_WIDTH_MASK;
		अवरोध;
	हाल MMC_BUS_WIDTH_4:
		host->cmdat &= ~JZ_MMC_CMDAT_BUS_WIDTH_MASK;
		host->cmdat |= JZ_MMC_CMDAT_BUS_WIDTH_4BIT;
		अवरोध;
	हाल MMC_BUS_WIDTH_8:
		host->cmdat &= ~JZ_MMC_CMDAT_BUS_WIDTH_MASK;
		host->cmdat |= JZ_MMC_CMDAT_BUS_WIDTH_8BIT;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम jz4740_mmc_enable_sdio_irq(काष्ठा mmc_host *mmc, पूर्णांक enable)
अणु
	काष्ठा jz4740_mmc_host *host = mmc_priv(mmc);
	jz4740_mmc_set_irq_enabled(host, JZ_MMC_IRQ_SDIO, enable);
पूर्ण

अटल स्थिर काष्ठा mmc_host_ops jz4740_mmc_ops = अणु
	.request	= jz4740_mmc_request,
	.pre_req	= jz4740_mmc_pre_request,
	.post_req	= jz4740_mmc_post_request,
	.set_ios	= jz4740_mmc_set_ios,
	.get_ro		= mmc_gpio_get_ro,
	.get_cd		= mmc_gpio_get_cd,
	.enable_sdio_irq = jz4740_mmc_enable_sdio_irq,
पूर्ण;

अटल स्थिर काष्ठा of_device_id jz4740_mmc_of_match[] = अणु
	अणु .compatible = "ingenic,jz4740-mmc", .data = (व्योम *) JZ_MMC_JZ4740 पूर्ण,
	अणु .compatible = "ingenic,jz4725b-mmc", .data = (व्योम *)JZ_MMC_JZ4725B पूर्ण,
	अणु .compatible = "ingenic,jz4760-mmc", .data = (व्योम *) JZ_MMC_JZ4760 पूर्ण,
	अणु .compatible = "ingenic,jz4780-mmc", .data = (व्योम *) JZ_MMC_JZ4780 पूर्ण,
	अणु .compatible = "ingenic,x1000-mmc", .data = (व्योम *) JZ_MMC_X1000 पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, jz4740_mmc_of_match);

अटल पूर्णांक jz4740_mmc_probe(काष्ठा platक्रमm_device* pdev)
अणु
	पूर्णांक ret;
	काष्ठा mmc_host *mmc;
	काष्ठा jz4740_mmc_host *host;
	स्थिर काष्ठा of_device_id *match;

	mmc = mmc_alloc_host(माप(काष्ठा jz4740_mmc_host), &pdev->dev);
	अगर (!mmc) अणु
		dev_err(&pdev->dev, "Failed to alloc mmc host structure\n");
		वापस -ENOMEM;
	पूर्ण

	host = mmc_priv(mmc);

	match = of_match_device(jz4740_mmc_of_match, &pdev->dev);
	अगर (match) अणु
		host->version = (क्रमागत jz4740_mmc_version)match->data;
	पूर्ण अन्यथा अणु
		/* JZ4740 should be the only one using legacy probe */
		host->version = JZ_MMC_JZ4740;
	पूर्ण

	ret = mmc_of_parse(mmc);
	अगर (ret) अणु
		dev_err_probe(&pdev->dev, ret, "could not parse device properties\n");
		जाओ err_मुक्त_host;
	पूर्ण

	mmc_regulator_get_supply(mmc);

	host->irq = platक्रमm_get_irq(pdev, 0);
	अगर (host->irq < 0) अणु
		ret = host->irq;
		जाओ err_मुक्त_host;
	पूर्ण

	host->clk = devm_clk_get(&pdev->dev, "mmc");
	अगर (IS_ERR(host->clk)) अणु
		ret = PTR_ERR(host->clk);
		dev_err(&pdev->dev, "Failed to get mmc clock\n");
		जाओ err_मुक्त_host;
	पूर्ण

	host->mem_res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	host->base = devm_ioremap_resource(&pdev->dev, host->mem_res);
	अगर (IS_ERR(host->base)) अणु
		ret = PTR_ERR(host->base);
		dev_err(&pdev->dev, "Failed to ioremap base memory\n");
		जाओ err_मुक्त_host;
	पूर्ण

	mmc->ops = &jz4740_mmc_ops;
	अगर (!mmc->f_max)
		mmc->f_max = JZ_MMC_CLK_RATE;
	mmc->f_min = mmc->f_max / 128;
	mmc->ocr_avail = MMC_VDD_32_33 | MMC_VDD_33_34;

	/*
	 * We use a fixed समयout of 5s, hence inक्रमm the core about it. A
	 * future improvement should instead respect the cmd->busy_समयout.
	 */
	mmc->max_busy_समयout = JZ_MMC_REQ_TIMEOUT_MS;

	mmc->max_blk_size = (1 << 10) - 1;
	mmc->max_blk_count = (1 << 15) - 1;
	mmc->max_req_size = mmc->max_blk_size * mmc->max_blk_count;

	mmc->max_segs = 128;
	mmc->max_seg_size = mmc->max_req_size;

	host->mmc = mmc;
	host->pdev = pdev;
	spin_lock_init(&host->lock);
	host->irq_mask = ~0;

	jz4740_mmc_reset(host);

	ret = request_thपढ़ोed_irq(host->irq, jz_mmc_irq, jz_mmc_irq_worker, 0,
			dev_name(&pdev->dev), host);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Failed to request irq: %d\n", ret);
		जाओ err_मुक्त_host;
	पूर्ण

	jz4740_mmc_घड़ी_disable(host);
	समयr_setup(&host->समयout_समयr, jz4740_mmc_समयout, 0);

	ret = jz4740_mmc_acquire_dma_channels(host);
	अगर (ret == -EPROBE_DEFER)
		जाओ err_मुक्त_irq;
	host->use_dma = !ret;

	platक्रमm_set_drvdata(pdev, host);
	ret = mmc_add_host(mmc);

	अगर (ret) अणु
		dev_err(&pdev->dev, "Failed to add mmc host: %d\n", ret);
		जाओ err_release_dma;
	पूर्ण
	dev_info(&pdev->dev, "Ingenic SD/MMC card driver registered\n");

	dev_info(&pdev->dev, "Using %s, %d-bit mode\n",
		 host->use_dma ? "DMA" : "PIO",
		 (mmc->caps & MMC_CAP_8_BIT_DATA) ? 8 :
		 ((mmc->caps & MMC_CAP_4_BIT_DATA) ? 4 : 1));

	वापस 0;

err_release_dma:
	अगर (host->use_dma)
		jz4740_mmc_release_dma_channels(host);
err_मुक्त_irq:
	मुक्त_irq(host->irq, host);
err_मुक्त_host:
	mmc_मुक्त_host(mmc);

	वापस ret;
पूर्ण

अटल पूर्णांक jz4740_mmc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा jz4740_mmc_host *host = platक्रमm_get_drvdata(pdev);

	del_समयr_sync(&host->समयout_समयr);
	jz4740_mmc_set_irq_enabled(host, 0xff, false);
	jz4740_mmc_reset(host);

	mmc_हटाओ_host(host->mmc);

	मुक्त_irq(host->irq, host);

	अगर (host->use_dma)
		jz4740_mmc_release_dma_channels(host);

	mmc_मुक्त_host(host->mmc);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused jz4740_mmc_suspend(काष्ठा device *dev)
अणु
	वापस pinctrl_pm_select_sleep_state(dev);
पूर्ण

अटल पूर्णांक __maybe_unused jz4740_mmc_resume(काष्ठा device *dev)
अणु
	वापस pinctrl_select_शेष_state(dev);
पूर्ण

अटल SIMPLE_DEV_PM_OPS(jz4740_mmc_pm_ops, jz4740_mmc_suspend,
	jz4740_mmc_resume);

अटल काष्ठा platक्रमm_driver jz4740_mmc_driver = अणु
	.probe = jz4740_mmc_probe,
	.हटाओ = jz4740_mmc_हटाओ,
	.driver = अणु
		.name = "jz4740-mmc",
		.probe_type = PROBE_PREFER_ASYNCHRONOUS,
		.of_match_table = of_match_ptr(jz4740_mmc_of_match),
		.pm = pm_ptr(&jz4740_mmc_pm_ops),
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(jz4740_mmc_driver);

MODULE_DESCRIPTION("JZ4740 SD/MMC controller driver");
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Lars-Peter Clausen <lars@metafoo.de>");
