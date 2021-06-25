<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * DMA driver क्रम Nvidia's Tegra20 APB DMA controller.
 *
 * Copyright (c) 2012-2013, NVIDIA CORPORATION.  All rights reserved.
 */

#समावेश <linux/bitops.h>
#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/dmaengine.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/err.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/mm.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_dma.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/reset.h>
#समावेश <linux/slab.h>
#समावेश <linux/रुको.h>

#समावेश "dmaengine.h"

#घोषणा CREATE_TRACE_POINTS
#समावेश <trace/events/tegra_apb_dma.h>

#घोषणा TEGRA_APBDMA_GENERAL			0x0
#घोषणा TEGRA_APBDMA_GENERAL_ENABLE		BIT(31)

#घोषणा TEGRA_APBDMA_CONTROL			0x010
#घोषणा TEGRA_APBDMA_IRQ_MASK			0x01c
#घोषणा TEGRA_APBDMA_IRQ_MASK_SET		0x020

/* CSR रेजिस्टर */
#घोषणा TEGRA_APBDMA_CHAN_CSR			0x00
#घोषणा TEGRA_APBDMA_CSR_ENB			BIT(31)
#घोषणा TEGRA_APBDMA_CSR_IE_EOC			BIT(30)
#घोषणा TEGRA_APBDMA_CSR_HOLD			BIT(29)
#घोषणा TEGRA_APBDMA_CSR_सूची			BIT(28)
#घोषणा TEGRA_APBDMA_CSR_ONCE			BIT(27)
#घोषणा TEGRA_APBDMA_CSR_FLOW			BIT(21)
#घोषणा TEGRA_APBDMA_CSR_REQ_SEL_SHIFT		16
#घोषणा TEGRA_APBDMA_CSR_REQ_SEL_MASK		0x1F
#घोषणा TEGRA_APBDMA_CSR_WCOUNT_MASK		0xFFFC

/* STATUS रेजिस्टर */
#घोषणा TEGRA_APBDMA_CHAN_STATUS		0x004
#घोषणा TEGRA_APBDMA_STATUS_BUSY		BIT(31)
#घोषणा TEGRA_APBDMA_STATUS_ISE_EOC		BIT(30)
#घोषणा TEGRA_APBDMA_STATUS_HALT		BIT(29)
#घोषणा TEGRA_APBDMA_STATUS_PING_PONG		BIT(28)
#घोषणा TEGRA_APBDMA_STATUS_COUNT_SHIFT		2
#घोषणा TEGRA_APBDMA_STATUS_COUNT_MASK		0xFFFC

#घोषणा TEGRA_APBDMA_CHAN_CSRE			0x00C
#घोषणा TEGRA_APBDMA_CHAN_CSRE_PAUSE		BIT(31)

/* AHB memory address */
#घोषणा TEGRA_APBDMA_CHAN_AHBPTR		0x010

/* AHB sequence रेजिस्टर */
#घोषणा TEGRA_APBDMA_CHAN_AHBSEQ		0x14
#घोषणा TEGRA_APBDMA_AHBSEQ_INTR_ENB		BIT(31)
#घोषणा TEGRA_APBDMA_AHBSEQ_BUS_WIDTH_8		(0 << 28)
#घोषणा TEGRA_APBDMA_AHBSEQ_BUS_WIDTH_16	(1 << 28)
#घोषणा TEGRA_APBDMA_AHBSEQ_BUS_WIDTH_32	(2 << 28)
#घोषणा TEGRA_APBDMA_AHBSEQ_BUS_WIDTH_64	(3 << 28)
#घोषणा TEGRA_APBDMA_AHBSEQ_BUS_WIDTH_128	(4 << 28)
#घोषणा TEGRA_APBDMA_AHBSEQ_DATA_SWAP		BIT(27)
#घोषणा TEGRA_APBDMA_AHBSEQ_BURST_1		(4 << 24)
#घोषणा TEGRA_APBDMA_AHBSEQ_BURST_4		(5 << 24)
#घोषणा TEGRA_APBDMA_AHBSEQ_BURST_8		(6 << 24)
#घोषणा TEGRA_APBDMA_AHBSEQ_DBL_BUF		BIT(19)
#घोषणा TEGRA_APBDMA_AHBSEQ_WRAP_SHIFT		16
#घोषणा TEGRA_APBDMA_AHBSEQ_WRAP_NONE		0

/* APB address */
#घोषणा TEGRA_APBDMA_CHAN_APBPTR		0x018

/* APB sequence रेजिस्टर */
#घोषणा TEGRA_APBDMA_CHAN_APBSEQ		0x01c
#घोषणा TEGRA_APBDMA_APBSEQ_BUS_WIDTH_8		(0 << 28)
#घोषणा TEGRA_APBDMA_APBSEQ_BUS_WIDTH_16	(1 << 28)
#घोषणा TEGRA_APBDMA_APBSEQ_BUS_WIDTH_32	(2 << 28)
#घोषणा TEGRA_APBDMA_APBSEQ_BUS_WIDTH_64	(3 << 28)
#घोषणा TEGRA_APBDMA_APBSEQ_BUS_WIDTH_128	(4 << 28)
#घोषणा TEGRA_APBDMA_APBSEQ_DATA_SWAP		BIT(27)
#घोषणा TEGRA_APBDMA_APBSEQ_WRAP_WORD_1		(1 << 16)

/* Tegra148 specअगरic रेजिस्टरs */
#घोषणा TEGRA_APBDMA_CHAN_WCOUNT		0x20

#घोषणा TEGRA_APBDMA_CHAN_WORD_TRANSFER		0x24

/*
 * If any burst is in flight and DMA छोड़ोd then this is the समय to complete
 * on-flight burst and update DMA status रेजिस्टर.
 */
#घोषणा TEGRA_APBDMA_BURST_COMPLETE_TIME	20

/* Channel base address offset from APBDMA base address */
#घोषणा TEGRA_APBDMA_CHANNEL_BASE_ADD_OFFSET	0x1000

#घोषणा TEGRA_APBDMA_SLAVE_ID_INVALID	(TEGRA_APBDMA_CSR_REQ_SEL_MASK + 1)

काष्ठा tegra_dma;

/*
 * tegra_dma_chip_data Tegra chip specअगरic DMA data
 * @nr_channels: Number of channels available in the controller.
 * @channel_reg_size: Channel रेजिस्टर size/stride.
 * @max_dma_count: Maximum DMA transfer count supported by DMA controller.
 * @support_channel_छोड़ो: Support channel wise छोड़ो of dma.
 * @support_separate_wcount_reg: Support separate word count रेजिस्टर.
 */
काष्ठा tegra_dma_chip_data अणु
	अचिन्हित पूर्णांक nr_channels;
	अचिन्हित पूर्णांक channel_reg_size;
	अचिन्हित पूर्णांक max_dma_count;
	bool support_channel_छोड़ो;
	bool support_separate_wcount_reg;
पूर्ण;

/* DMA channel रेजिस्टरs */
काष्ठा tegra_dma_channel_regs अणु
	u32 csr;
	u32 ahb_ptr;
	u32 apb_ptr;
	u32 ahb_seq;
	u32 apb_seq;
	u32 wcount;
पूर्ण;

/*
 * tegra_dma_sg_req: DMA request details to configure hardware. This
 * contains the details क्रम one transfer to configure DMA hw.
 * The client's request क्रम data transfer can be broken पूर्णांकo multiple
 * sub-transfer as per requester details and hw support.
 * This sub transfer get added in the list of transfer and poपूर्णांक to Tegra
 * DMA descriptor which manages the transfer details.
 */
काष्ठा tegra_dma_sg_req अणु
	काष्ठा tegra_dma_channel_regs	ch_regs;
	अचिन्हित पूर्णांक			req_len;
	bool				configured;
	bool				last_sg;
	काष्ठा list_head		node;
	काष्ठा tegra_dma_desc		*dma_desc;
	अचिन्हित पूर्णांक			words_xferred;
पूर्ण;

/*
 * tegra_dma_desc: Tegra DMA descriptors which manages the client requests.
 * This descriptor keep track of transfer status, callbacks and request
 * counts etc.
 */
काष्ठा tegra_dma_desc अणु
	काष्ठा dma_async_tx_descriptor	txd;
	अचिन्हित पूर्णांक			bytes_requested;
	अचिन्हित पूर्णांक			bytes_transferred;
	क्रमागत dma_status			dma_status;
	काष्ठा list_head		node;
	काष्ठा list_head		tx_list;
	काष्ठा list_head		cb_node;
	अचिन्हित पूर्णांक			cb_count;
पूर्ण;

काष्ठा tegra_dma_channel;

प्रकार व्योम (*dma_isr_handler)(काष्ठा tegra_dma_channel *tdc,
				bool to_terminate);

/* tegra_dma_channel: Channel specअगरic inक्रमmation */
काष्ठा tegra_dma_channel अणु
	काष्ठा dma_chan		dma_chan;
	अक्षर			name[12];
	bool			config_init;
	अचिन्हित पूर्णांक		id;
	व्योम __iomem		*chan_addr;
	spinlock_t		lock;
	bool			busy;
	काष्ठा tegra_dma	*tdma;
	bool			cyclic;

	/* Dअगरferent lists क्रम managing the requests */
	काष्ठा list_head	मुक्त_sg_req;
	काष्ठा list_head	pending_sg_req;
	काष्ठा list_head	मुक्त_dma_desc;
	काष्ठा list_head	cb_desc;

	/* ISR handler and tasklet क्रम bottom half of isr handling */
	dma_isr_handler		isr_handler;
	काष्ठा tasklet_काष्ठा	tasklet;

	/* Channel-slave specअगरic configuration */
	अचिन्हित पूर्णांक slave_id;
	काष्ठा dma_slave_config dma_sconfig;
	काष्ठा tegra_dma_channel_regs channel_reg;

	काष्ठा रुको_queue_head wq;
पूर्ण;

/* tegra_dma: Tegra DMA specअगरic inक्रमmation */
काष्ठा tegra_dma अणु
	काष्ठा dma_device		dma_dev;
	काष्ठा device			*dev;
	काष्ठा clk			*dma_clk;
	काष्ठा reset_control		*rst;
	spinlock_t			global_lock;
	व्योम __iomem			*base_addr;
	स्थिर काष्ठा tegra_dma_chip_data *chip_data;

	/*
	 * Counter क्रम managing global pausing of the DMA controller.
	 * Only applicable क्रम devices that करोn't support inभागidual
	 * channel pausing.
	 */
	u32				global_छोड़ो_count;

	/* Last member of the काष्ठाure */
	काष्ठा tegra_dma_channel channels[];
पूर्ण;

अटल अंतरभूत व्योम tdma_ग_लिखो(काष्ठा tegra_dma *tdma, u32 reg, u32 val)
अणु
	ग_लिखोl(val, tdma->base_addr + reg);
पूर्ण

अटल अंतरभूत u32 tdma_पढ़ो(काष्ठा tegra_dma *tdma, u32 reg)
अणु
	वापस पढ़ोl(tdma->base_addr + reg);
पूर्ण

अटल अंतरभूत व्योम tdc_ग_लिखो(काष्ठा tegra_dma_channel *tdc,
			     u32 reg, u32 val)
अणु
	ग_लिखोl(val, tdc->chan_addr + reg);
पूर्ण

अटल अंतरभूत u32 tdc_पढ़ो(काष्ठा tegra_dma_channel *tdc, u32 reg)
अणु
	वापस पढ़ोl(tdc->chan_addr + reg);
पूर्ण

अटल अंतरभूत काष्ठा tegra_dma_channel *to_tegra_dma_chan(काष्ठा dma_chan *dc)
अणु
	वापस container_of(dc, काष्ठा tegra_dma_channel, dma_chan);
पूर्ण

अटल अंतरभूत काष्ठा tegra_dma_desc *
txd_to_tegra_dma_desc(काष्ठा dma_async_tx_descriptor *td)
अणु
	वापस container_of(td, काष्ठा tegra_dma_desc, txd);
पूर्ण

अटल अंतरभूत काष्ठा device *tdc2dev(काष्ठा tegra_dma_channel *tdc)
अणु
	वापस &tdc->dma_chan.dev->device;
पूर्ण

अटल dma_cookie_t tegra_dma_tx_submit(काष्ठा dma_async_tx_descriptor *tx);

/* Get DMA desc from मुक्त list, अगर not there then allocate it.  */
अटल काष्ठा tegra_dma_desc *tegra_dma_desc_get(काष्ठा tegra_dma_channel *tdc)
अणु
	काष्ठा tegra_dma_desc *dma_desc;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&tdc->lock, flags);

	/* Do not allocate अगर desc are रुकोing क्रम ack */
	list_क्रम_each_entry(dma_desc, &tdc->मुक्त_dma_desc, node) अणु
		अगर (async_tx_test_ack(&dma_desc->txd) && !dma_desc->cb_count) अणु
			list_del(&dma_desc->node);
			spin_unlock_irqrestore(&tdc->lock, flags);
			dma_desc->txd.flags = 0;
			वापस dma_desc;
		पूर्ण
	पूर्ण

	spin_unlock_irqrestore(&tdc->lock, flags);

	/* Allocate DMA desc */
	dma_desc = kzalloc(माप(*dma_desc), GFP_NOWAIT);
	अगर (!dma_desc)
		वापस शून्य;

	dma_async_tx_descriptor_init(&dma_desc->txd, &tdc->dma_chan);
	dma_desc->txd.tx_submit = tegra_dma_tx_submit;
	dma_desc->txd.flags = 0;

	वापस dma_desc;
पूर्ण

अटल व्योम tegra_dma_desc_put(काष्ठा tegra_dma_channel *tdc,
			       काष्ठा tegra_dma_desc *dma_desc)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&tdc->lock, flags);
	अगर (!list_empty(&dma_desc->tx_list))
		list_splice_init(&dma_desc->tx_list, &tdc->मुक्त_sg_req);
	list_add_tail(&dma_desc->node, &tdc->मुक्त_dma_desc);
	spin_unlock_irqrestore(&tdc->lock, flags);
पूर्ण

अटल काष्ठा tegra_dma_sg_req *
tegra_dma_sg_req_get(काष्ठा tegra_dma_channel *tdc)
अणु
	काष्ठा tegra_dma_sg_req *sg_req;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&tdc->lock, flags);
	अगर (!list_empty(&tdc->मुक्त_sg_req)) अणु
		sg_req = list_first_entry(&tdc->मुक्त_sg_req, typeof(*sg_req),
					  node);
		list_del(&sg_req->node);
		spin_unlock_irqrestore(&tdc->lock, flags);
		वापस sg_req;
	पूर्ण
	spin_unlock_irqrestore(&tdc->lock, flags);

	sg_req = kzalloc(माप(*sg_req), GFP_NOWAIT);

	वापस sg_req;
पूर्ण

अटल पूर्णांक tegra_dma_slave_config(काष्ठा dma_chan *dc,
				  काष्ठा dma_slave_config *sconfig)
अणु
	काष्ठा tegra_dma_channel *tdc = to_tegra_dma_chan(dc);

	अगर (!list_empty(&tdc->pending_sg_req)) अणु
		dev_err(tdc2dev(tdc), "Configuration not allowed\n");
		वापस -EBUSY;
	पूर्ण

	स_नकल(&tdc->dma_sconfig, sconfig, माप(*sconfig));
	अगर (tdc->slave_id == TEGRA_APBDMA_SLAVE_ID_INVALID &&
	    sconfig->device_fc) अणु
		अगर (sconfig->slave_id > TEGRA_APBDMA_CSR_REQ_SEL_MASK)
			वापस -EINVAL;
		tdc->slave_id = sconfig->slave_id;
	पूर्ण
	tdc->config_init = true;

	वापस 0;
पूर्ण

अटल व्योम tegra_dma_global_छोड़ो(काष्ठा tegra_dma_channel *tdc,
				   bool रुको_क्रम_burst_complete)
अणु
	काष्ठा tegra_dma *tdma = tdc->tdma;

	spin_lock(&tdma->global_lock);

	अगर (tdc->tdma->global_छोड़ो_count == 0) अणु
		tdma_ग_लिखो(tdma, TEGRA_APBDMA_GENERAL, 0);
		अगर (रुको_क्रम_burst_complete)
			udelay(TEGRA_APBDMA_BURST_COMPLETE_TIME);
	पूर्ण

	tdc->tdma->global_छोड़ो_count++;

	spin_unlock(&tdma->global_lock);
पूर्ण

अटल व्योम tegra_dma_global_resume(काष्ठा tegra_dma_channel *tdc)
अणु
	काष्ठा tegra_dma *tdma = tdc->tdma;

	spin_lock(&tdma->global_lock);

	अगर (WARN_ON(tdc->tdma->global_छोड़ो_count == 0))
		जाओ out;

	अगर (--tdc->tdma->global_छोड़ो_count == 0)
		tdma_ग_लिखो(tdma, TEGRA_APBDMA_GENERAL,
			   TEGRA_APBDMA_GENERAL_ENABLE);

out:
	spin_unlock(&tdma->global_lock);
पूर्ण

अटल व्योम tegra_dma_छोड़ो(काष्ठा tegra_dma_channel *tdc,
			    bool रुको_क्रम_burst_complete)
अणु
	काष्ठा tegra_dma *tdma = tdc->tdma;

	अगर (tdma->chip_data->support_channel_छोड़ो) अणु
		tdc_ग_लिखो(tdc, TEGRA_APBDMA_CHAN_CSRE,
			  TEGRA_APBDMA_CHAN_CSRE_PAUSE);
		अगर (रुको_क्रम_burst_complete)
			udelay(TEGRA_APBDMA_BURST_COMPLETE_TIME);
	पूर्ण अन्यथा अणु
		tegra_dma_global_छोड़ो(tdc, रुको_क्रम_burst_complete);
	पूर्ण
पूर्ण

अटल व्योम tegra_dma_resume(काष्ठा tegra_dma_channel *tdc)
अणु
	काष्ठा tegra_dma *tdma = tdc->tdma;

	अगर (tdma->chip_data->support_channel_छोड़ो)
		tdc_ग_लिखो(tdc, TEGRA_APBDMA_CHAN_CSRE, 0);
	अन्यथा
		tegra_dma_global_resume(tdc);
पूर्ण

अटल व्योम tegra_dma_stop(काष्ठा tegra_dma_channel *tdc)
अणु
	u32 csr, status;

	/* Disable पूर्णांकerrupts */
	csr = tdc_पढ़ो(tdc, TEGRA_APBDMA_CHAN_CSR);
	csr &= ~TEGRA_APBDMA_CSR_IE_EOC;
	tdc_ग_लिखो(tdc, TEGRA_APBDMA_CHAN_CSR, csr);

	/* Disable DMA */
	csr &= ~TEGRA_APBDMA_CSR_ENB;
	tdc_ग_लिखो(tdc, TEGRA_APBDMA_CHAN_CSR, csr);

	/* Clear पूर्णांकerrupt status अगर it is there */
	status = tdc_पढ़ो(tdc, TEGRA_APBDMA_CHAN_STATUS);
	अगर (status & TEGRA_APBDMA_STATUS_ISE_EOC) अणु
		dev_dbg(tdc2dev(tdc), "%s():clearing interrupt\n", __func__);
		tdc_ग_लिखो(tdc, TEGRA_APBDMA_CHAN_STATUS, status);
	पूर्ण
	tdc->busy = false;
पूर्ण

अटल व्योम tegra_dma_start(काष्ठा tegra_dma_channel *tdc,
			    काष्ठा tegra_dma_sg_req *sg_req)
अणु
	काष्ठा tegra_dma_channel_regs *ch_regs = &sg_req->ch_regs;

	tdc_ग_लिखो(tdc, TEGRA_APBDMA_CHAN_CSR, ch_regs->csr);
	tdc_ग_लिखो(tdc, TEGRA_APBDMA_CHAN_APBSEQ, ch_regs->apb_seq);
	tdc_ग_लिखो(tdc, TEGRA_APBDMA_CHAN_APBPTR, ch_regs->apb_ptr);
	tdc_ग_लिखो(tdc, TEGRA_APBDMA_CHAN_AHBSEQ, ch_regs->ahb_seq);
	tdc_ग_लिखो(tdc, TEGRA_APBDMA_CHAN_AHBPTR, ch_regs->ahb_ptr);
	अगर (tdc->tdma->chip_data->support_separate_wcount_reg)
		tdc_ग_लिखो(tdc, TEGRA_APBDMA_CHAN_WCOUNT, ch_regs->wcount);

	/* Start DMA */
	tdc_ग_लिखो(tdc, TEGRA_APBDMA_CHAN_CSR,
		  ch_regs->csr | TEGRA_APBDMA_CSR_ENB);
पूर्ण

अटल व्योम tegra_dma_configure_क्रम_next(काष्ठा tegra_dma_channel *tdc,
					 काष्ठा tegra_dma_sg_req *nsg_req)
अणु
	अचिन्हित दीर्घ status;

	/*
	 * The DMA controller reloads the new configuration क्रम next transfer
	 * after last burst of current transfer completes.
	 * If there is no IEC status then this makes sure that last burst
	 * has not be completed. There may be हाल that last burst is on
	 * flight and so it can complete but because DMA is छोड़ोd, it
	 * will not generates पूर्णांकerrupt as well as not reload the new
	 * configuration.
	 * If there is alपढ़ोy IEC status then पूर्णांकerrupt handler need to
	 * load new configuration.
	 */
	tegra_dma_छोड़ो(tdc, false);
	status = tdc_पढ़ो(tdc, TEGRA_APBDMA_CHAN_STATUS);

	/*
	 * If पूर्णांकerrupt is pending then करो nothing as the ISR will handle
	 * the programing क्रम new request.
	 */
	अगर (status & TEGRA_APBDMA_STATUS_ISE_EOC) अणु
		dev_err(tdc2dev(tdc),
			"Skipping new configuration as interrupt is pending\n");
		tegra_dma_resume(tdc);
		वापस;
	पूर्ण

	/* Safe to program new configuration */
	tdc_ग_लिखो(tdc, TEGRA_APBDMA_CHAN_APBPTR, nsg_req->ch_regs.apb_ptr);
	tdc_ग_लिखो(tdc, TEGRA_APBDMA_CHAN_AHBPTR, nsg_req->ch_regs.ahb_ptr);
	अगर (tdc->tdma->chip_data->support_separate_wcount_reg)
		tdc_ग_लिखो(tdc, TEGRA_APBDMA_CHAN_WCOUNT,
			  nsg_req->ch_regs.wcount);
	tdc_ग_लिखो(tdc, TEGRA_APBDMA_CHAN_CSR,
		  nsg_req->ch_regs.csr | TEGRA_APBDMA_CSR_ENB);
	nsg_req->configured = true;
	nsg_req->words_xferred = 0;

	tegra_dma_resume(tdc);
पूर्ण

अटल व्योम tdc_start_head_req(काष्ठा tegra_dma_channel *tdc)
अणु
	काष्ठा tegra_dma_sg_req *sg_req;

	sg_req = list_first_entry(&tdc->pending_sg_req, typeof(*sg_req), node);
	tegra_dma_start(tdc, sg_req);
	sg_req->configured = true;
	sg_req->words_xferred = 0;
	tdc->busy = true;
पूर्ण

अटल व्योम tdc_configure_next_head_desc(काष्ठा tegra_dma_channel *tdc)
अणु
	काष्ठा tegra_dma_sg_req *hsgreq, *hnsgreq;

	hsgreq = list_first_entry(&tdc->pending_sg_req, typeof(*hsgreq), node);
	अगर (!list_is_last(&hsgreq->node, &tdc->pending_sg_req)) अणु
		hnsgreq = list_first_entry(&hsgreq->node, typeof(*hnsgreq),
					   node);
		tegra_dma_configure_क्रम_next(tdc, hnsgreq);
	पूर्ण
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक
get_current_xferred_count(काष्ठा tegra_dma_channel *tdc,
			  काष्ठा tegra_dma_sg_req *sg_req,
			  अचिन्हित दीर्घ status)
अणु
	वापस sg_req->req_len - (status & TEGRA_APBDMA_STATUS_COUNT_MASK) - 4;
पूर्ण

अटल व्योम tegra_dma_पात_all(काष्ठा tegra_dma_channel *tdc)
अणु
	काष्ठा tegra_dma_desc *dma_desc;
	काष्ठा tegra_dma_sg_req *sgreq;

	जबतक (!list_empty(&tdc->pending_sg_req)) अणु
		sgreq = list_first_entry(&tdc->pending_sg_req, typeof(*sgreq),
					 node);
		list_move_tail(&sgreq->node, &tdc->मुक्त_sg_req);
		अगर (sgreq->last_sg) अणु
			dma_desc = sgreq->dma_desc;
			dma_desc->dma_status = DMA_ERROR;
			list_add_tail(&dma_desc->node, &tdc->मुक्त_dma_desc);

			/* Add in cb list अगर it is not there. */
			अगर (!dma_desc->cb_count)
				list_add_tail(&dma_desc->cb_node,
					      &tdc->cb_desc);
			dma_desc->cb_count++;
		पूर्ण
	पूर्ण
	tdc->isr_handler = शून्य;
पूर्ण

अटल bool handle_continuous_head_request(काष्ठा tegra_dma_channel *tdc,
					   bool to_terminate)
अणु
	काष्ठा tegra_dma_sg_req *hsgreq;

	/*
	 * Check that head req on list should be in flight.
	 * If it is not in flight then पात transfer as
	 * looping of transfer can not जारी.
	 */
	hsgreq = list_first_entry(&tdc->pending_sg_req, typeof(*hsgreq), node);
	अगर (!hsgreq->configured) अणु
		tegra_dma_stop(tdc);
		pm_runसमय_put(tdc->tdma->dev);
		dev_err(tdc2dev(tdc), "DMA transfer underflow, aborting DMA\n");
		tegra_dma_पात_all(tdc);
		वापस false;
	पूर्ण

	/* Configure next request */
	अगर (!to_terminate)
		tdc_configure_next_head_desc(tdc);

	वापस true;
पूर्ण

अटल व्योम handle_once_dma_करोne(काष्ठा tegra_dma_channel *tdc,
				 bool to_terminate)
अणु
	काष्ठा tegra_dma_desc *dma_desc;
	काष्ठा tegra_dma_sg_req *sgreq;

	tdc->busy = false;
	sgreq = list_first_entry(&tdc->pending_sg_req, typeof(*sgreq), node);
	dma_desc = sgreq->dma_desc;
	dma_desc->bytes_transferred += sgreq->req_len;

	list_del(&sgreq->node);
	अगर (sgreq->last_sg) अणु
		dma_desc->dma_status = DMA_COMPLETE;
		dma_cookie_complete(&dma_desc->txd);
		अगर (!dma_desc->cb_count)
			list_add_tail(&dma_desc->cb_node, &tdc->cb_desc);
		dma_desc->cb_count++;
		list_add_tail(&dma_desc->node, &tdc->मुक्त_dma_desc);
	पूर्ण
	list_add_tail(&sgreq->node, &tdc->मुक्त_sg_req);

	/* Do not start DMA अगर it is going to be terminate */
	अगर (to_terminate)
		वापस;

	अगर (list_empty(&tdc->pending_sg_req)) अणु
		pm_runसमय_put(tdc->tdma->dev);
		वापस;
	पूर्ण

	tdc_start_head_req(tdc);
पूर्ण

अटल व्योम handle_cont_sngl_cycle_dma_करोne(काष्ठा tegra_dma_channel *tdc,
					    bool to_terminate)
अणु
	काष्ठा tegra_dma_desc *dma_desc;
	काष्ठा tegra_dma_sg_req *sgreq;
	bool st;

	sgreq = list_first_entry(&tdc->pending_sg_req, typeof(*sgreq), node);
	dma_desc = sgreq->dma_desc;
	/* अगर we dma क्रम दीर्घ enough the transfer count will wrap */
	dma_desc->bytes_transferred =
		(dma_desc->bytes_transferred + sgreq->req_len) %
		dma_desc->bytes_requested;

	/* Callback need to be call */
	अगर (!dma_desc->cb_count)
		list_add_tail(&dma_desc->cb_node, &tdc->cb_desc);
	dma_desc->cb_count++;

	sgreq->words_xferred = 0;

	/* If not last req then put at end of pending list */
	अगर (!list_is_last(&sgreq->node, &tdc->pending_sg_req)) अणु
		list_move_tail(&sgreq->node, &tdc->pending_sg_req);
		sgreq->configured = false;
		st = handle_continuous_head_request(tdc, to_terminate);
		अगर (!st)
			dma_desc->dma_status = DMA_ERROR;
	पूर्ण
पूर्ण

अटल व्योम tegra_dma_tasklet(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा tegra_dma_channel *tdc = from_tasklet(tdc, t, tasklet);
	काष्ठा dmaengine_desc_callback cb;
	काष्ठा tegra_dma_desc *dma_desc;
	अचिन्हित पूर्णांक cb_count;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&tdc->lock, flags);
	जबतक (!list_empty(&tdc->cb_desc)) अणु
		dma_desc = list_first_entry(&tdc->cb_desc, typeof(*dma_desc),
					    cb_node);
		list_del(&dma_desc->cb_node);
		dmaengine_desc_get_callback(&dma_desc->txd, &cb);
		cb_count = dma_desc->cb_count;
		dma_desc->cb_count = 0;
		trace_tegra_dma_complete_cb(&tdc->dma_chan, cb_count,
					    cb.callback);
		spin_unlock_irqrestore(&tdc->lock, flags);
		जबतक (cb_count--)
			dmaengine_desc_callback_invoke(&cb, शून्य);
		spin_lock_irqsave(&tdc->lock, flags);
	पूर्ण
	spin_unlock_irqrestore(&tdc->lock, flags);
पूर्ण

अटल irqवापस_t tegra_dma_isr(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा tegra_dma_channel *tdc = dev_id;
	u32 status;

	spin_lock(&tdc->lock);

	trace_tegra_dma_isr(&tdc->dma_chan, irq);
	status = tdc_पढ़ो(tdc, TEGRA_APBDMA_CHAN_STATUS);
	अगर (status & TEGRA_APBDMA_STATUS_ISE_EOC) अणु
		tdc_ग_लिखो(tdc, TEGRA_APBDMA_CHAN_STATUS, status);
		tdc->isr_handler(tdc, false);
		tasklet_schedule(&tdc->tasklet);
		wake_up_all(&tdc->wq);
		spin_unlock(&tdc->lock);
		वापस IRQ_HANDLED;
	पूर्ण

	spin_unlock(&tdc->lock);
	dev_info(tdc2dev(tdc), "Interrupt already served status 0x%08x\n",
		 status);

	वापस IRQ_NONE;
पूर्ण

अटल dma_cookie_t tegra_dma_tx_submit(काष्ठा dma_async_tx_descriptor *txd)
अणु
	काष्ठा tegra_dma_desc *dma_desc = txd_to_tegra_dma_desc(txd);
	काष्ठा tegra_dma_channel *tdc = to_tegra_dma_chan(txd->chan);
	अचिन्हित दीर्घ flags;
	dma_cookie_t cookie;

	spin_lock_irqsave(&tdc->lock, flags);
	dma_desc->dma_status = DMA_IN_PROGRESS;
	cookie = dma_cookie_assign(&dma_desc->txd);
	list_splice_tail_init(&dma_desc->tx_list, &tdc->pending_sg_req);
	spin_unlock_irqrestore(&tdc->lock, flags);

	वापस cookie;
पूर्ण

अटल व्योम tegra_dma_issue_pending(काष्ठा dma_chan *dc)
अणु
	काष्ठा tegra_dma_channel *tdc = to_tegra_dma_chan(dc);
	अचिन्हित दीर्घ flags;
	पूर्णांक err;

	spin_lock_irqsave(&tdc->lock, flags);
	अगर (list_empty(&tdc->pending_sg_req)) अणु
		dev_err(tdc2dev(tdc), "No DMA request\n");
		जाओ end;
	पूर्ण
	अगर (!tdc->busy) अणु
		err = pm_runसमय_resume_and_get(tdc->tdma->dev);
		अगर (err < 0) अणु
			dev_err(tdc2dev(tdc), "Failed to enable DMA\n");
			जाओ end;
		पूर्ण

		tdc_start_head_req(tdc);

		/* Continuous single mode: Configure next req */
		अगर (tdc->cyclic) अणु
			/*
			 * Wait क्रम 1 burst समय क्रम configure DMA क्रम
			 * next transfer.
			 */
			udelay(TEGRA_APBDMA_BURST_COMPLETE_TIME);
			tdc_configure_next_head_desc(tdc);
		पूर्ण
	पूर्ण
end:
	spin_unlock_irqrestore(&tdc->lock, flags);
पूर्ण

अटल पूर्णांक tegra_dma_terminate_all(काष्ठा dma_chan *dc)
अणु
	काष्ठा tegra_dma_channel *tdc = to_tegra_dma_chan(dc);
	काष्ठा tegra_dma_desc *dma_desc;
	काष्ठा tegra_dma_sg_req *sgreq;
	अचिन्हित दीर्घ flags;
	u32 status, wcount;
	bool was_busy;

	spin_lock_irqsave(&tdc->lock, flags);

	अगर (!tdc->busy)
		जाओ skip_dma_stop;

	/* Pause DMA beक्रमe checking the queue status */
	tegra_dma_छोड़ो(tdc, true);

	status = tdc_पढ़ो(tdc, TEGRA_APBDMA_CHAN_STATUS);
	अगर (status & TEGRA_APBDMA_STATUS_ISE_EOC) अणु
		dev_dbg(tdc2dev(tdc), "%s():handling isr\n", __func__);
		tdc->isr_handler(tdc, true);
		status = tdc_पढ़ो(tdc, TEGRA_APBDMA_CHAN_STATUS);
	पूर्ण
	अगर (tdc->tdma->chip_data->support_separate_wcount_reg)
		wcount = tdc_पढ़ो(tdc, TEGRA_APBDMA_CHAN_WORD_TRANSFER);
	अन्यथा
		wcount = status;

	was_busy = tdc->busy;
	tegra_dma_stop(tdc);

	अगर (!list_empty(&tdc->pending_sg_req) && was_busy) अणु
		sgreq = list_first_entry(&tdc->pending_sg_req, typeof(*sgreq),
					 node);
		sgreq->dma_desc->bytes_transferred +=
				get_current_xferred_count(tdc, sgreq, wcount);
	पूर्ण
	tegra_dma_resume(tdc);

	pm_runसमय_put(tdc->tdma->dev);
	wake_up_all(&tdc->wq);

skip_dma_stop:
	tegra_dma_पात_all(tdc);

	जबतक (!list_empty(&tdc->cb_desc)) अणु
		dma_desc = list_first_entry(&tdc->cb_desc, typeof(*dma_desc),
					    cb_node);
		list_del(&dma_desc->cb_node);
		dma_desc->cb_count = 0;
	पूर्ण
	spin_unlock_irqrestore(&tdc->lock, flags);

	वापस 0;
पूर्ण

अटल bool tegra_dma_eoc_पूर्णांकerrupt_deनिश्चितed(काष्ठा tegra_dma_channel *tdc)
अणु
	अचिन्हित दीर्घ flags;
	u32 status;

	spin_lock_irqsave(&tdc->lock, flags);
	status = tdc_पढ़ो(tdc, TEGRA_APBDMA_CHAN_STATUS);
	spin_unlock_irqrestore(&tdc->lock, flags);

	वापस !(status & TEGRA_APBDMA_STATUS_ISE_EOC);
पूर्ण

अटल व्योम tegra_dma_synchronize(काष्ठा dma_chan *dc)
अणु
	काष्ठा tegra_dma_channel *tdc = to_tegra_dma_chan(dc);
	पूर्णांक err;

	err = pm_runसमय_resume_and_get(tdc->tdma->dev);
	अगर (err < 0) अणु
		dev_err(tdc2dev(tdc), "Failed to synchronize DMA: %d\n", err);
		वापस;
	पूर्ण

	/*
	 * CPU, which handles पूर्णांकerrupt, could be busy in
	 * unपूर्णांकerruptible state, in this हाल sibling CPU
	 * should रुको until पूर्णांकerrupt is handled.
	 */
	रुको_event(tdc->wq, tegra_dma_eoc_पूर्णांकerrupt_deनिश्चितed(tdc));

	tasklet_समाप्त(&tdc->tasklet);

	pm_runसमय_put(tdc->tdma->dev);
पूर्ण

अटल अचिन्हित पूर्णांक tegra_dma_sg_bytes_xferred(काष्ठा tegra_dma_channel *tdc,
					       काष्ठा tegra_dma_sg_req *sg_req)
अणु
	u32 status, wcount = 0;

	अगर (!list_is_first(&sg_req->node, &tdc->pending_sg_req))
		वापस 0;

	अगर (tdc->tdma->chip_data->support_separate_wcount_reg)
		wcount = tdc_पढ़ो(tdc, TEGRA_APBDMA_CHAN_WORD_TRANSFER);

	status = tdc_पढ़ो(tdc, TEGRA_APBDMA_CHAN_STATUS);

	अगर (!tdc->tdma->chip_data->support_separate_wcount_reg)
		wcount = status;

	अगर (status & TEGRA_APBDMA_STATUS_ISE_EOC)
		वापस sg_req->req_len;

	wcount = get_current_xferred_count(tdc, sg_req, wcount);

	अगर (!wcount) अणु
		/*
		 * If wcount wasn't ever polled क्रम this SG beक्रमe, then
		 * simply assume that transfer hasn't started yet.
		 *
		 * Otherwise it's the end of the transfer.
		 *
		 * The alternative would be to poll the status रेजिस्टर
		 * until EOC bit is set or wcount goes UP. That's so
		 * because EOC bit is getting set only after the last
		 * burst's completion and counter is less than the actual
		 * transfer size by 4 bytes. The counter value wraps around
		 * in a cyclic mode beक्रमe EOC is set(!), so we can't easily
		 * distinguish start of transfer from its end.
		 */
		अगर (sg_req->words_xferred)
			wcount = sg_req->req_len - 4;

	पूर्ण अन्यथा अगर (wcount < sg_req->words_xferred) अणु
		/*
		 * This हाल will never happen क्रम a non-cyclic transfer.
		 *
		 * For a cyclic transfer, although it is possible क्रम the
		 * next transfer to have alपढ़ोy started (resetting the word
		 * count), this हाल should still not happen because we should
		 * have detected that the EOC bit is set and hence the transfer
		 * was completed.
		 */
		WARN_ON_ONCE(1);

		wcount = sg_req->req_len - 4;
	पूर्ण अन्यथा अणु
		sg_req->words_xferred = wcount;
	पूर्ण

	वापस wcount;
पूर्ण

अटल क्रमागत dma_status tegra_dma_tx_status(काष्ठा dma_chan *dc,
					   dma_cookie_t cookie,
					   काष्ठा dma_tx_state *txstate)
अणु
	काष्ठा tegra_dma_channel *tdc = to_tegra_dma_chan(dc);
	काष्ठा tegra_dma_desc *dma_desc;
	काष्ठा tegra_dma_sg_req *sg_req;
	क्रमागत dma_status ret;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक residual;
	अचिन्हित पूर्णांक bytes = 0;

	ret = dma_cookie_status(dc, cookie, txstate);
	अगर (ret == DMA_COMPLETE)
		वापस ret;

	spin_lock_irqsave(&tdc->lock, flags);

	/* Check on रुको_ack desc status */
	list_क्रम_each_entry(dma_desc, &tdc->मुक्त_dma_desc, node) अणु
		अगर (dma_desc->txd.cookie == cookie) अणु
			ret = dma_desc->dma_status;
			जाओ found;
		पूर्ण
	पूर्ण

	/* Check in pending list */
	list_क्रम_each_entry(sg_req, &tdc->pending_sg_req, node) अणु
		dma_desc = sg_req->dma_desc;
		अगर (dma_desc->txd.cookie == cookie) अणु
			bytes = tegra_dma_sg_bytes_xferred(tdc, sg_req);
			ret = dma_desc->dma_status;
			जाओ found;
		पूर्ण
	पूर्ण

	dev_dbg(tdc2dev(tdc), "cookie %d not found\n", cookie);
	dma_desc = शून्य;

found:
	अगर (dma_desc && txstate) अणु
		residual = dma_desc->bytes_requested -
			   ((dma_desc->bytes_transferred + bytes) %
			    dma_desc->bytes_requested);
		dma_set_residue(txstate, residual);
	पूर्ण

	trace_tegra_dma_tx_status(&tdc->dma_chan, cookie, txstate);
	spin_unlock_irqrestore(&tdc->lock, flags);

	वापस ret;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक get_bus_width(काष्ठा tegra_dma_channel *tdc,
					 क्रमागत dma_slave_buswidth slave_bw)
अणु
	चयन (slave_bw) अणु
	हाल DMA_SLAVE_BUSWIDTH_1_BYTE:
		वापस TEGRA_APBDMA_APBSEQ_BUS_WIDTH_8;
	हाल DMA_SLAVE_BUSWIDTH_2_BYTES:
		वापस TEGRA_APBDMA_APBSEQ_BUS_WIDTH_16;
	हाल DMA_SLAVE_BUSWIDTH_4_BYTES:
		वापस TEGRA_APBDMA_APBSEQ_BUS_WIDTH_32;
	हाल DMA_SLAVE_BUSWIDTH_8_BYTES:
		वापस TEGRA_APBDMA_APBSEQ_BUS_WIDTH_64;
	शेष:
		dev_warn(tdc2dev(tdc),
			 "slave bw is not supported, using 32bits\n");
		वापस TEGRA_APBDMA_APBSEQ_BUS_WIDTH_32;
	पूर्ण
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक get_burst_size(काष्ठा tegra_dma_channel *tdc,
					  u32 burst_size,
					  क्रमागत dma_slave_buswidth slave_bw,
					  u32 len)
अणु
	अचिन्हित पूर्णांक burst_byte, burst_ahb_width;

	/*
	 * burst_size from client is in terms of the bus_width.
	 * convert them पूर्णांकo AHB memory width which is 4 byte.
	 */
	burst_byte = burst_size * slave_bw;
	burst_ahb_width = burst_byte / 4;

	/* If burst size is 0 then calculate the burst size based on length */
	अगर (!burst_ahb_width) अणु
		अगर (len & 0xF)
			वापस TEGRA_APBDMA_AHBSEQ_BURST_1;
		अन्यथा अगर ((len >> 4) & 0x1)
			वापस TEGRA_APBDMA_AHBSEQ_BURST_4;
		अन्यथा
			वापस TEGRA_APBDMA_AHBSEQ_BURST_8;
	पूर्ण
	अगर (burst_ahb_width < 4)
		वापस TEGRA_APBDMA_AHBSEQ_BURST_1;
	अन्यथा अगर (burst_ahb_width < 8)
		वापस TEGRA_APBDMA_AHBSEQ_BURST_4;
	अन्यथा
		वापस TEGRA_APBDMA_AHBSEQ_BURST_8;
पूर्ण

अटल पूर्णांक get_transfer_param(काष्ठा tegra_dma_channel *tdc,
			      क्रमागत dma_transfer_direction direction,
			      u32 *apb_addr,
			      u32 *apb_seq,
			      u32 *csr,
			      अचिन्हित पूर्णांक *burst_size,
			      क्रमागत dma_slave_buswidth *slave_bw)
अणु
	चयन (direction) अणु
	हाल DMA_MEM_TO_DEV:
		*apb_addr = tdc->dma_sconfig.dst_addr;
		*apb_seq = get_bus_width(tdc, tdc->dma_sconfig.dst_addr_width);
		*burst_size = tdc->dma_sconfig.dst_maxburst;
		*slave_bw = tdc->dma_sconfig.dst_addr_width;
		*csr = TEGRA_APBDMA_CSR_सूची;
		वापस 0;

	हाल DMA_DEV_TO_MEM:
		*apb_addr = tdc->dma_sconfig.src_addr;
		*apb_seq = get_bus_width(tdc, tdc->dma_sconfig.src_addr_width);
		*burst_size = tdc->dma_sconfig.src_maxburst;
		*slave_bw = tdc->dma_sconfig.src_addr_width;
		*csr = 0;
		वापस 0;

	शेष:
		dev_err(tdc2dev(tdc), "DMA direction is not supported\n");
		अवरोध;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल व्योम tegra_dma_prep_wcount(काष्ठा tegra_dma_channel *tdc,
				  काष्ठा tegra_dma_channel_regs *ch_regs,
				  u32 len)
अणु
	u32 len_field = (len - 4) & 0xFFFC;

	अगर (tdc->tdma->chip_data->support_separate_wcount_reg)
		ch_regs->wcount = len_field;
	अन्यथा
		ch_regs->csr |= len_field;
पूर्ण

अटल काष्ठा dma_async_tx_descriptor *
tegra_dma_prep_slave_sg(काष्ठा dma_chan *dc,
			काष्ठा scatterlist *sgl,
			अचिन्हित पूर्णांक sg_len,
			क्रमागत dma_transfer_direction direction,
			अचिन्हित दीर्घ flags,
			व्योम *context)
अणु
	काष्ठा tegra_dma_channel *tdc = to_tegra_dma_chan(dc);
	काष्ठा tegra_dma_sg_req *sg_req = शून्य;
	u32 csr, ahb_seq, apb_ptr, apb_seq;
	क्रमागत dma_slave_buswidth slave_bw;
	काष्ठा tegra_dma_desc *dma_desc;
	काष्ठा list_head req_list;
	काष्ठा scatterlist *sg;
	अचिन्हित पूर्णांक burst_size;
	अचिन्हित पूर्णांक i;

	अगर (!tdc->config_init) अणु
		dev_err(tdc2dev(tdc), "DMA channel is not configured\n");
		वापस शून्य;
	पूर्ण
	अगर (sg_len < 1) अणु
		dev_err(tdc2dev(tdc), "Invalid segment length %d\n", sg_len);
		वापस शून्य;
	पूर्ण

	अगर (get_transfer_param(tdc, direction, &apb_ptr, &apb_seq, &csr,
			       &burst_size, &slave_bw) < 0)
		वापस शून्य;

	INIT_LIST_HEAD(&req_list);

	ahb_seq = TEGRA_APBDMA_AHBSEQ_INTR_ENB;
	ahb_seq |= TEGRA_APBDMA_AHBSEQ_WRAP_NONE <<
					TEGRA_APBDMA_AHBSEQ_WRAP_SHIFT;
	ahb_seq |= TEGRA_APBDMA_AHBSEQ_BUS_WIDTH_32;

	csr |= TEGRA_APBDMA_CSR_ONCE;

	अगर (tdc->slave_id != TEGRA_APBDMA_SLAVE_ID_INVALID) अणु
		csr |= TEGRA_APBDMA_CSR_FLOW;
		csr |= tdc->slave_id << TEGRA_APBDMA_CSR_REQ_SEL_SHIFT;
	पूर्ण

	अगर (flags & DMA_PREP_INTERRUPT) अणु
		csr |= TEGRA_APBDMA_CSR_IE_EOC;
	पूर्ण अन्यथा अणु
		WARN_ON_ONCE(1);
		वापस शून्य;
	पूर्ण

	apb_seq |= TEGRA_APBDMA_APBSEQ_WRAP_WORD_1;

	dma_desc = tegra_dma_desc_get(tdc);
	अगर (!dma_desc) अणु
		dev_err(tdc2dev(tdc), "DMA descriptors not available\n");
		वापस शून्य;
	पूर्ण
	INIT_LIST_HEAD(&dma_desc->tx_list);
	INIT_LIST_HEAD(&dma_desc->cb_node);
	dma_desc->cb_count = 0;
	dma_desc->bytes_requested = 0;
	dma_desc->bytes_transferred = 0;
	dma_desc->dma_status = DMA_IN_PROGRESS;

	/* Make transfer requests */
	क्रम_each_sg(sgl, sg, sg_len, i) अणु
		u32 len, mem;

		mem = sg_dma_address(sg);
		len = sg_dma_len(sg);

		अगर ((len & 3) || (mem & 3) ||
		    len > tdc->tdma->chip_data->max_dma_count) अणु
			dev_err(tdc2dev(tdc),
				"DMA length/memory address is not supported\n");
			tegra_dma_desc_put(tdc, dma_desc);
			वापस शून्य;
		पूर्ण

		sg_req = tegra_dma_sg_req_get(tdc);
		अगर (!sg_req) अणु
			dev_err(tdc2dev(tdc), "DMA sg-req not available\n");
			tegra_dma_desc_put(tdc, dma_desc);
			वापस शून्य;
		पूर्ण

		ahb_seq |= get_burst_size(tdc, burst_size, slave_bw, len);
		dma_desc->bytes_requested += len;

		sg_req->ch_regs.apb_ptr = apb_ptr;
		sg_req->ch_regs.ahb_ptr = mem;
		sg_req->ch_regs.csr = csr;
		tegra_dma_prep_wcount(tdc, &sg_req->ch_regs, len);
		sg_req->ch_regs.apb_seq = apb_seq;
		sg_req->ch_regs.ahb_seq = ahb_seq;
		sg_req->configured = false;
		sg_req->last_sg = false;
		sg_req->dma_desc = dma_desc;
		sg_req->req_len = len;

		list_add_tail(&sg_req->node, &dma_desc->tx_list);
	पूर्ण
	sg_req->last_sg = true;
	अगर (flags & DMA_CTRL_ACK)
		dma_desc->txd.flags = DMA_CTRL_ACK;

	/*
	 * Make sure that mode should not be conflicting with currently
	 * configured mode.
	 */
	अगर (!tdc->isr_handler) अणु
		tdc->isr_handler = handle_once_dma_करोne;
		tdc->cyclic = false;
	पूर्ण अन्यथा अणु
		अगर (tdc->cyclic) अणु
			dev_err(tdc2dev(tdc), "DMA configured in cyclic mode\n");
			tegra_dma_desc_put(tdc, dma_desc);
			वापस शून्य;
		पूर्ण
	पूर्ण

	वापस &dma_desc->txd;
पूर्ण

अटल काष्ठा dma_async_tx_descriptor *
tegra_dma_prep_dma_cyclic(काष्ठा dma_chan *dc, dma_addr_t buf_addr,
			  माप_प्रकार buf_len,
			  माप_प्रकार period_len,
			  क्रमागत dma_transfer_direction direction,
			  अचिन्हित दीर्घ flags)
अणु
	काष्ठा tegra_dma_channel *tdc = to_tegra_dma_chan(dc);
	काष्ठा tegra_dma_sg_req *sg_req = शून्य;
	u32 csr, ahb_seq, apb_ptr, apb_seq;
	क्रमागत dma_slave_buswidth slave_bw;
	काष्ठा tegra_dma_desc *dma_desc;
	dma_addr_t mem = buf_addr;
	अचिन्हित पूर्णांक burst_size;
	माप_प्रकार len, reमुख्य_len;

	अगर (!buf_len || !period_len) अणु
		dev_err(tdc2dev(tdc), "Invalid buffer/period len\n");
		वापस शून्य;
	पूर्ण

	अगर (!tdc->config_init) अणु
		dev_err(tdc2dev(tdc), "DMA slave is not configured\n");
		वापस शून्य;
	पूर्ण

	/*
	 * We allow to take more number of requests till DMA is
	 * not started. The driver will loop over all requests.
	 * Once DMA is started then new requests can be queued only after
	 * terminating the DMA.
	 */
	अगर (tdc->busy) अणु
		dev_err(tdc2dev(tdc), "Request not allowed when DMA running\n");
		वापस शून्य;
	पूर्ण

	/*
	 * We only support cycle transfer when buf_len is multiple of
	 * period_len.
	 */
	अगर (buf_len % period_len) अणु
		dev_err(tdc2dev(tdc), "buf_len is not multiple of period_len\n");
		वापस शून्य;
	पूर्ण

	len = period_len;
	अगर ((len & 3) || (buf_addr & 3) ||
	    len > tdc->tdma->chip_data->max_dma_count) अणु
		dev_err(tdc2dev(tdc), "Req len/mem address is not correct\n");
		वापस शून्य;
	पूर्ण

	अगर (get_transfer_param(tdc, direction, &apb_ptr, &apb_seq, &csr,
			       &burst_size, &slave_bw) < 0)
		वापस शून्य;

	ahb_seq = TEGRA_APBDMA_AHBSEQ_INTR_ENB;
	ahb_seq |= TEGRA_APBDMA_AHBSEQ_WRAP_NONE <<
					TEGRA_APBDMA_AHBSEQ_WRAP_SHIFT;
	ahb_seq |= TEGRA_APBDMA_AHBSEQ_BUS_WIDTH_32;

	अगर (tdc->slave_id != TEGRA_APBDMA_SLAVE_ID_INVALID) अणु
		csr |= TEGRA_APBDMA_CSR_FLOW;
		csr |= tdc->slave_id << TEGRA_APBDMA_CSR_REQ_SEL_SHIFT;
	पूर्ण

	अगर (flags & DMA_PREP_INTERRUPT) अणु
		csr |= TEGRA_APBDMA_CSR_IE_EOC;
	पूर्ण अन्यथा अणु
		WARN_ON_ONCE(1);
		वापस शून्य;
	पूर्ण

	apb_seq |= TEGRA_APBDMA_APBSEQ_WRAP_WORD_1;

	dma_desc = tegra_dma_desc_get(tdc);
	अगर (!dma_desc) अणु
		dev_err(tdc2dev(tdc), "not enough descriptors available\n");
		वापस शून्य;
	पूर्ण

	INIT_LIST_HEAD(&dma_desc->tx_list);
	INIT_LIST_HEAD(&dma_desc->cb_node);
	dma_desc->cb_count = 0;

	dma_desc->bytes_transferred = 0;
	dma_desc->bytes_requested = buf_len;
	reमुख्य_len = buf_len;

	/* Split transfer equal to period size */
	जबतक (reमुख्य_len) अणु
		sg_req = tegra_dma_sg_req_get(tdc);
		अगर (!sg_req) अणु
			dev_err(tdc2dev(tdc), "DMA sg-req not available\n");
			tegra_dma_desc_put(tdc, dma_desc);
			वापस शून्य;
		पूर्ण

		ahb_seq |= get_burst_size(tdc, burst_size, slave_bw, len);
		sg_req->ch_regs.apb_ptr = apb_ptr;
		sg_req->ch_regs.ahb_ptr = mem;
		sg_req->ch_regs.csr = csr;
		tegra_dma_prep_wcount(tdc, &sg_req->ch_regs, len);
		sg_req->ch_regs.apb_seq = apb_seq;
		sg_req->ch_regs.ahb_seq = ahb_seq;
		sg_req->configured = false;
		sg_req->last_sg = false;
		sg_req->dma_desc = dma_desc;
		sg_req->req_len = len;

		list_add_tail(&sg_req->node, &dma_desc->tx_list);
		reमुख्य_len -= len;
		mem += len;
	पूर्ण
	sg_req->last_sg = true;
	अगर (flags & DMA_CTRL_ACK)
		dma_desc->txd.flags = DMA_CTRL_ACK;

	/*
	 * Make sure that mode should not be conflicting with currently
	 * configured mode.
	 */
	अगर (!tdc->isr_handler) अणु
		tdc->isr_handler = handle_cont_sngl_cycle_dma_करोne;
		tdc->cyclic = true;
	पूर्ण अन्यथा अणु
		अगर (!tdc->cyclic) अणु
			dev_err(tdc2dev(tdc), "DMA configuration conflict\n");
			tegra_dma_desc_put(tdc, dma_desc);
			वापस शून्य;
		पूर्ण
	पूर्ण

	वापस &dma_desc->txd;
पूर्ण

अटल पूर्णांक tegra_dma_alloc_chan_resources(काष्ठा dma_chan *dc)
अणु
	काष्ठा tegra_dma_channel *tdc = to_tegra_dma_chan(dc);

	dma_cookie_init(&tdc->dma_chan);

	वापस 0;
पूर्ण

अटल व्योम tegra_dma_मुक्त_chan_resources(काष्ठा dma_chan *dc)
अणु
	काष्ठा tegra_dma_channel *tdc = to_tegra_dma_chan(dc);
	काष्ठा tegra_dma_desc *dma_desc;
	काष्ठा tegra_dma_sg_req *sg_req;
	काष्ठा list_head dma_desc_list;
	काष्ठा list_head sg_req_list;

	INIT_LIST_HEAD(&dma_desc_list);
	INIT_LIST_HEAD(&sg_req_list);

	dev_dbg(tdc2dev(tdc), "Freeing channel %d\n", tdc->id);

	tegra_dma_terminate_all(dc);
	tasklet_समाप्त(&tdc->tasklet);

	list_splice_init(&tdc->pending_sg_req, &sg_req_list);
	list_splice_init(&tdc->मुक्त_sg_req, &sg_req_list);
	list_splice_init(&tdc->मुक्त_dma_desc, &dma_desc_list);
	INIT_LIST_HEAD(&tdc->cb_desc);
	tdc->config_init = false;
	tdc->isr_handler = शून्य;

	जबतक (!list_empty(&dma_desc_list)) अणु
		dma_desc = list_first_entry(&dma_desc_list, typeof(*dma_desc),
					    node);
		list_del(&dma_desc->node);
		kमुक्त(dma_desc);
	पूर्ण

	जबतक (!list_empty(&sg_req_list)) अणु
		sg_req = list_first_entry(&sg_req_list, typeof(*sg_req), node);
		list_del(&sg_req->node);
		kमुक्त(sg_req);
	पूर्ण

	tdc->slave_id = TEGRA_APBDMA_SLAVE_ID_INVALID;
पूर्ण

अटल काष्ठा dma_chan *tegra_dma_of_xlate(काष्ठा of_phandle_args *dma_spec,
					   काष्ठा of_dma *ofdma)
अणु
	काष्ठा tegra_dma *tdma = ofdma->of_dma_data;
	काष्ठा tegra_dma_channel *tdc;
	काष्ठा dma_chan *chan;

	अगर (dma_spec->args[0] > TEGRA_APBDMA_CSR_REQ_SEL_MASK) अणु
		dev_err(tdma->dev, "Invalid slave id: %d\n", dma_spec->args[0]);
		वापस शून्य;
	पूर्ण

	chan = dma_get_any_slave_channel(&tdma->dma_dev);
	अगर (!chan)
		वापस शून्य;

	tdc = to_tegra_dma_chan(chan);
	tdc->slave_id = dma_spec->args[0];

	वापस chan;
पूर्ण

/* Tegra20 specअगरic DMA controller inक्रमmation */
अटल स्थिर काष्ठा tegra_dma_chip_data tegra20_dma_chip_data = अणु
	.nr_channels		= 16,
	.channel_reg_size	= 0x20,
	.max_dma_count		= 1024UL * 64,
	.support_channel_छोड़ो	= false,
	.support_separate_wcount_reg = false,
पूर्ण;

/* Tegra30 specअगरic DMA controller inक्रमmation */
अटल स्थिर काष्ठा tegra_dma_chip_data tegra30_dma_chip_data = अणु
	.nr_channels		= 32,
	.channel_reg_size	= 0x20,
	.max_dma_count		= 1024UL * 64,
	.support_channel_छोड़ो	= false,
	.support_separate_wcount_reg = false,
पूर्ण;

/* Tegra114 specअगरic DMA controller inक्रमmation */
अटल स्थिर काष्ठा tegra_dma_chip_data tegra114_dma_chip_data = अणु
	.nr_channels		= 32,
	.channel_reg_size	= 0x20,
	.max_dma_count		= 1024UL * 64,
	.support_channel_छोड़ो	= true,
	.support_separate_wcount_reg = false,
पूर्ण;

/* Tegra148 specअगरic DMA controller inक्रमmation */
अटल स्थिर काष्ठा tegra_dma_chip_data tegra148_dma_chip_data = अणु
	.nr_channels		= 32,
	.channel_reg_size	= 0x40,
	.max_dma_count		= 1024UL * 64,
	.support_channel_छोड़ो	= true,
	.support_separate_wcount_reg = true,
पूर्ण;

अटल पूर्णांक tegra_dma_init_hw(काष्ठा tegra_dma *tdma)
अणु
	पूर्णांक err;

	err = reset_control_निश्चित(tdma->rst);
	अगर (err) अणु
		dev_err(tdma->dev, "failed to assert reset: %d\n", err);
		वापस err;
	पूर्ण

	err = clk_enable(tdma->dma_clk);
	अगर (err) अणु
		dev_err(tdma->dev, "failed to enable clk: %d\n", err);
		वापस err;
	पूर्ण

	/* reset DMA controller */
	udelay(2);
	reset_control_deनिश्चित(tdma->rst);

	/* enable global DMA रेजिस्टरs */
	tdma_ग_लिखो(tdma, TEGRA_APBDMA_GENERAL, TEGRA_APBDMA_GENERAL_ENABLE);
	tdma_ग_लिखो(tdma, TEGRA_APBDMA_CONTROL, 0);
	tdma_ग_लिखो(tdma, TEGRA_APBDMA_IRQ_MASK_SET, 0xFFFFFFFF);

	clk_disable(tdma->dma_clk);

	वापस 0;
पूर्ण

अटल पूर्णांक tegra_dma_probe(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा tegra_dma_chip_data *cdata;
	काष्ठा tegra_dma *tdma;
	अचिन्हित पूर्णांक i;
	माप_प्रकार size;
	पूर्णांक ret;

	cdata = of_device_get_match_data(&pdev->dev);
	size = काष्ठा_size(tdma, channels, cdata->nr_channels);

	tdma = devm_kzalloc(&pdev->dev, size, GFP_KERNEL);
	अगर (!tdma)
		वापस -ENOMEM;

	tdma->dev = &pdev->dev;
	tdma->chip_data = cdata;
	platक्रमm_set_drvdata(pdev, tdma);

	tdma->base_addr = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(tdma->base_addr))
		वापस PTR_ERR(tdma->base_addr);

	tdma->dma_clk = devm_clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(tdma->dma_clk)) अणु
		dev_err(&pdev->dev, "Error: Missing controller clock\n");
		वापस PTR_ERR(tdma->dma_clk);
	पूर्ण

	tdma->rst = devm_reset_control_get(&pdev->dev, "dma");
	अगर (IS_ERR(tdma->rst)) अणु
		dev_err(&pdev->dev, "Error: Missing reset\n");
		वापस PTR_ERR(tdma->rst);
	पूर्ण

	spin_lock_init(&tdma->global_lock);

	ret = clk_prepare(tdma->dma_clk);
	अगर (ret)
		वापस ret;

	ret = tegra_dma_init_hw(tdma);
	अगर (ret)
		जाओ err_clk_unprepare;

	pm_runसमय_irq_safe(&pdev->dev);
	pm_runसमय_enable(&pdev->dev);

	INIT_LIST_HEAD(&tdma->dma_dev.channels);
	क्रम (i = 0; i < cdata->nr_channels; i++) अणु
		काष्ठा tegra_dma_channel *tdc = &tdma->channels[i];
		पूर्णांक irq;

		tdc->chan_addr = tdma->base_addr +
				 TEGRA_APBDMA_CHANNEL_BASE_ADD_OFFSET +
				 (i * cdata->channel_reg_size);

		irq = platक्रमm_get_irq(pdev, i);
		अगर (irq < 0) अणु
			ret = irq;
			जाओ err_pm_disable;
		पूर्ण

		snम_लिखो(tdc->name, माप(tdc->name), "apbdma.%d", i);
		ret = devm_request_irq(&pdev->dev, irq, tegra_dma_isr, 0,
				       tdc->name, tdc);
		अगर (ret) अणु
			dev_err(&pdev->dev,
				"request_irq failed with err %d channel %d\n",
				ret, i);
			जाओ err_pm_disable;
		पूर्ण

		tdc->dma_chan.device = &tdma->dma_dev;
		dma_cookie_init(&tdc->dma_chan);
		list_add_tail(&tdc->dma_chan.device_node,
			      &tdma->dma_dev.channels);
		tdc->tdma = tdma;
		tdc->id = i;
		tdc->slave_id = TEGRA_APBDMA_SLAVE_ID_INVALID;

		tasklet_setup(&tdc->tasklet, tegra_dma_tasklet);
		spin_lock_init(&tdc->lock);
		init_रुकोqueue_head(&tdc->wq);

		INIT_LIST_HEAD(&tdc->pending_sg_req);
		INIT_LIST_HEAD(&tdc->मुक्त_sg_req);
		INIT_LIST_HEAD(&tdc->मुक्त_dma_desc);
		INIT_LIST_HEAD(&tdc->cb_desc);
	पूर्ण

	dma_cap_set(DMA_SLAVE, tdma->dma_dev.cap_mask);
	dma_cap_set(DMA_PRIVATE, tdma->dma_dev.cap_mask);
	dma_cap_set(DMA_CYCLIC, tdma->dma_dev.cap_mask);

	tdma->global_छोड़ो_count = 0;
	tdma->dma_dev.dev = &pdev->dev;
	tdma->dma_dev.device_alloc_chan_resources =
					tegra_dma_alloc_chan_resources;
	tdma->dma_dev.device_मुक्त_chan_resources =
					tegra_dma_मुक्त_chan_resources;
	tdma->dma_dev.device_prep_slave_sg = tegra_dma_prep_slave_sg;
	tdma->dma_dev.device_prep_dma_cyclic = tegra_dma_prep_dma_cyclic;
	tdma->dma_dev.src_addr_widths = BIT(DMA_SLAVE_BUSWIDTH_1_BYTE) |
		BIT(DMA_SLAVE_BUSWIDTH_2_BYTES) |
		BIT(DMA_SLAVE_BUSWIDTH_4_BYTES) |
		BIT(DMA_SLAVE_BUSWIDTH_8_BYTES);
	tdma->dma_dev.dst_addr_widths = BIT(DMA_SLAVE_BUSWIDTH_1_BYTE) |
		BIT(DMA_SLAVE_BUSWIDTH_2_BYTES) |
		BIT(DMA_SLAVE_BUSWIDTH_4_BYTES) |
		BIT(DMA_SLAVE_BUSWIDTH_8_BYTES);
	tdma->dma_dev.directions = BIT(DMA_DEV_TO_MEM) | BIT(DMA_MEM_TO_DEV);
	tdma->dma_dev.residue_granularity = DMA_RESIDUE_GRANULARITY_BURST;
	tdma->dma_dev.device_config = tegra_dma_slave_config;
	tdma->dma_dev.device_terminate_all = tegra_dma_terminate_all;
	tdma->dma_dev.device_synchronize = tegra_dma_synchronize;
	tdma->dma_dev.device_tx_status = tegra_dma_tx_status;
	tdma->dma_dev.device_issue_pending = tegra_dma_issue_pending;

	ret = dma_async_device_रेजिस्टर(&tdma->dma_dev);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev,
			"Tegra20 APB DMA driver registration failed %d\n", ret);
		जाओ err_pm_disable;
	पूर्ण

	ret = of_dma_controller_रेजिस्टर(pdev->dev.of_node,
					 tegra_dma_of_xlate, tdma);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev,
			"Tegra20 APB DMA OF registration failed %d\n", ret);
		जाओ err_unरेजिस्टर_dma_dev;
	पूर्ण

	dev_info(&pdev->dev, "Tegra20 APB DMA driver registered %u channels\n",
		 cdata->nr_channels);

	वापस 0;

err_unरेजिस्टर_dma_dev:
	dma_async_device_unरेजिस्टर(&tdma->dma_dev);

err_pm_disable:
	pm_runसमय_disable(&pdev->dev);

err_clk_unprepare:
	clk_unprepare(tdma->dma_clk);

	वापस ret;
पूर्ण

अटल पूर्णांक tegra_dma_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा tegra_dma *tdma = platक्रमm_get_drvdata(pdev);

	of_dma_controller_मुक्त(pdev->dev.of_node);
	dma_async_device_unरेजिस्टर(&tdma->dma_dev);
	pm_runसमय_disable(&pdev->dev);
	clk_unprepare(tdma->dma_clk);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused tegra_dma_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा tegra_dma *tdma = dev_get_drvdata(dev);

	clk_disable(tdma->dma_clk);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused tegra_dma_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा tegra_dma *tdma = dev_get_drvdata(dev);

	वापस clk_enable(tdma->dma_clk);
पूर्ण

अटल पूर्णांक __maybe_unused tegra_dma_dev_suspend(काष्ठा device *dev)
अणु
	काष्ठा tegra_dma *tdma = dev_get_drvdata(dev);
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक i;
	bool busy;

	क्रम (i = 0; i < tdma->chip_data->nr_channels; i++) अणु
		काष्ठा tegra_dma_channel *tdc = &tdma->channels[i];

		tasklet_समाप्त(&tdc->tasklet);

		spin_lock_irqsave(&tdc->lock, flags);
		busy = tdc->busy;
		spin_unlock_irqrestore(&tdc->lock, flags);

		अगर (busy) अणु
			dev_err(tdma->dev, "channel %u busy\n", i);
			वापस -EBUSY;
		पूर्ण
	पूर्ण

	वापस pm_runसमय_क्रमce_suspend(dev);
पूर्ण

अटल पूर्णांक __maybe_unused tegra_dma_dev_resume(काष्ठा device *dev)
अणु
	काष्ठा tegra_dma *tdma = dev_get_drvdata(dev);
	पूर्णांक err;

	err = tegra_dma_init_hw(tdma);
	अगर (err)
		वापस err;

	वापस pm_runसमय_क्रमce_resume(dev);
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops tegra_dma_dev_pm_ops = अणु
	SET_RUNTIME_PM_OPS(tegra_dma_runसमय_suspend, tegra_dma_runसमय_resume,
			   शून्य)
	SET_SYSTEM_SLEEP_PM_OPS(tegra_dma_dev_suspend, tegra_dma_dev_resume)
पूर्ण;

अटल स्थिर काष्ठा of_device_id tegra_dma_of_match[] = अणु
	अणु
		.compatible = "nvidia,tegra148-apbdma",
		.data = &tegra148_dma_chip_data,
	पूर्ण, अणु
		.compatible = "nvidia,tegra114-apbdma",
		.data = &tegra114_dma_chip_data,
	पूर्ण, अणु
		.compatible = "nvidia,tegra30-apbdma",
		.data = &tegra30_dma_chip_data,
	पूर्ण, अणु
		.compatible = "nvidia,tegra20-apbdma",
		.data = &tegra20_dma_chip_data,
	पूर्ण, अणु
	पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, tegra_dma_of_match);

अटल काष्ठा platक्रमm_driver tegra_dmac_driver = अणु
	.driver = अणु
		.name	= "tegra-apbdma",
		.pm	= &tegra_dma_dev_pm_ops,
		.of_match_table = tegra_dma_of_match,
	पूर्ण,
	.probe		= tegra_dma_probe,
	.हटाओ		= tegra_dma_हटाओ,
पूर्ण;

module_platक्रमm_driver(tegra_dmac_driver);

MODULE_DESCRIPTION("NVIDIA Tegra APB DMA Controller driver");
MODULE_AUTHOR("Laxman Dewangan <ldewangan@nvidia.com>");
MODULE_LICENSE("GPL v2");
