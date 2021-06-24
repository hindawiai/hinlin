<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright 2012 Marvell International Ltd.
 */

#समावेश <linux/err.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/types.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/slab.h>
#समावेश <linux/dmaengine.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/device.h>
#समावेश <linux/platक्रमm_data/mmp_dma.h>
#समावेश <linux/dmapool.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_dma.h>
#समावेश <linux/of.h>

#समावेश "dmaengine.h"

#घोषणा DCSR		0x0000
#घोषणा DALGN		0x00a0
#घोषणा DINT		0x00f0
#घोषणा DDADR		0x0200
#घोषणा DSADR(n)	(0x0204 + ((n) << 4))
#घोषणा DTADR(n)	(0x0208 + ((n) << 4))
#घोषणा DCMD		0x020c

#घोषणा DCSR_RUN	BIT(31)	/* Run Bit (पढ़ो / ग_लिखो) */
#घोषणा DCSR_NODESC	BIT(30)	/* No-Descriptor Fetch (पढ़ो / ग_लिखो) */
#घोषणा DCSR_STOPIRQEN	BIT(29)	/* Stop Interrupt Enable (पढ़ो / ग_लिखो) */
#घोषणा DCSR_REQPEND	BIT(8)	/* Request Pending (पढ़ो-only) */
#घोषणा DCSR_STOPSTATE	BIT(3)	/* Stop State (पढ़ो-only) */
#घोषणा DCSR_ENDINTR	BIT(2)	/* End Interrupt (पढ़ो / ग_लिखो) */
#घोषणा DCSR_STARTINTR	BIT(1)	/* Start Interrupt (पढ़ो / ग_लिखो) */
#घोषणा DCSR_BUSERR	BIT(0)	/* Bus Error Interrupt (पढ़ो / ग_लिखो) */

#घोषणा DCSR_EORIRQEN	BIT(28)	/* End of Receive Interrupt Enable (R/W) */
#घोषणा DCSR_EORJMPEN	BIT(27)	/* Jump to next descriptor on EOR */
#घोषणा DCSR_EORSTOPEN	BIT(26)	/* STOP on an EOR */
#घोषणा DCSR_SETCMPST	BIT(25)	/* Set Descriptor Compare Status */
#घोषणा DCSR_CLRCMPST	BIT(24)	/* Clear Descriptor Compare Status */
#घोषणा DCSR_CMPST	BIT(10)	/* The Descriptor Compare Status */
#घोषणा DCSR_EORINTR	BIT(9)	/* The end of Receive */

#घोषणा DRCMR(n)	((((n) < 64) ? 0x0100 : 0x1100) + (((n) & 0x3f) << 2))
#घोषणा DRCMR_MAPVLD	BIT(7)	/* Map Valid (पढ़ो / ग_लिखो) */
#घोषणा DRCMR_CHLNUM	0x1f	/* mask क्रम Channel Number (पढ़ो / ग_लिखो) */

#घोषणा DDADR_DESCADDR	0xfffffff0	/* Address of next descriptor (mask) */
#घोषणा DDADR_STOP	BIT(0)	/* Stop (पढ़ो / ग_लिखो) */

#घोषणा DCMD_INCSRCADDR	BIT(31)	/* Source Address Increment Setting. */
#घोषणा DCMD_INCTRGADDR	BIT(30)	/* Target Address Increment Setting. */
#घोषणा DCMD_FLOWSRC	BIT(29)	/* Flow Control by the source. */
#घोषणा DCMD_FLOWTRG	BIT(28)	/* Flow Control by the target. */
#घोषणा DCMD_STARTIRQEN	BIT(22)	/* Start Interrupt Enable */
#घोषणा DCMD_ENसूचीQEN	BIT(21)	/* End Interrupt Enable */
#घोषणा DCMD_ENDIAN	BIT(18)	/* Device Endian-ness. */
#घोषणा DCMD_BURST8	(1 << 16)	/* 8 byte burst */
#घोषणा DCMD_BURST16	(2 << 16)	/* 16 byte burst */
#घोषणा DCMD_BURST32	(3 << 16)	/* 32 byte burst */
#घोषणा DCMD_WIDTH1	(1 << 14)	/* 1 byte width */
#घोषणा DCMD_WIDTH2	(2 << 14)	/* 2 byte width (HalfWord) */
#घोषणा DCMD_WIDTH4	(3 << 14)	/* 4 byte width (Word) */
#घोषणा DCMD_LENGTH	0x01fff		/* length mask (max = 8K - 1) */

#घोषणा PDMA_MAX_DESC_BYTES	DCMD_LENGTH

काष्ठा mmp_pdma_desc_hw अणु
	u32 ddadr;	/* Poपूर्णांकs to the next descriptor + flags */
	u32 dsadr;	/* DSADR value क्रम the current transfer */
	u32 dtadr;	/* DTADR value क्रम the current transfer */
	u32 dcmd;	/* DCMD value क्रम the current transfer */
पूर्ण __aligned(32);

काष्ठा mmp_pdma_desc_sw अणु
	काष्ठा mmp_pdma_desc_hw desc;
	काष्ठा list_head node;
	काष्ठा list_head tx_list;
	काष्ठा dma_async_tx_descriptor async_tx;
पूर्ण;

काष्ठा mmp_pdma_phy;

काष्ठा mmp_pdma_chan अणु
	काष्ठा device *dev;
	काष्ठा dma_chan chan;
	काष्ठा dma_async_tx_descriptor desc;
	काष्ठा mmp_pdma_phy *phy;
	क्रमागत dma_transfer_direction dir;
	काष्ठा dma_slave_config slave_config;

	काष्ठा mmp_pdma_desc_sw *cyclic_first;	/* first desc_sw अगर channel
						 * is in cyclic mode */

	/* channel's basic info */
	काष्ठा tasklet_काष्ठा tasklet;
	u32 dcmd;
	u32 drcmr;
	u32 dev_addr;

	/* list क्रम desc */
	spinlock_t desc_lock;		/* Descriptor list lock */
	काष्ठा list_head chain_pending;	/* Link descriptors queue क्रम pending */
	काष्ठा list_head chain_running;	/* Link descriptors queue क्रम running */
	bool idle;			/* channel statue machine */
	bool byte_align;

	काष्ठा dma_pool *desc_pool;	/* Descriptors pool */
पूर्ण;

काष्ठा mmp_pdma_phy अणु
	पूर्णांक idx;
	व्योम __iomem *base;
	काष्ठा mmp_pdma_chan *vchan;
पूर्ण;

काष्ठा mmp_pdma_device अणु
	पूर्णांक				dma_channels;
	व्योम __iomem			*base;
	काष्ठा device			*dev;
	काष्ठा dma_device		device;
	काष्ठा mmp_pdma_phy		*phy;
	spinlock_t phy_lock; /* protect alloc/मुक्त phy channels */
पूर्ण;

#घोषणा tx_to_mmp_pdma_desc(tx)					\
	container_of(tx, काष्ठा mmp_pdma_desc_sw, async_tx)
#घोषणा to_mmp_pdma_desc(lh)					\
	container_of(lh, काष्ठा mmp_pdma_desc_sw, node)
#घोषणा to_mmp_pdma_chan(dchan)					\
	container_of(dchan, काष्ठा mmp_pdma_chan, chan)
#घोषणा to_mmp_pdma_dev(dmadev)					\
	container_of(dmadev, काष्ठा mmp_pdma_device, device)

अटल पूर्णांक mmp_pdma_config_ग_लिखो(काष्ठा dma_chan *dchan,
			   काष्ठा dma_slave_config *cfg,
			   क्रमागत dma_transfer_direction direction);

अटल व्योम set_desc(काष्ठा mmp_pdma_phy *phy, dma_addr_t addr)
अणु
	u32 reg = (phy->idx << 4) + DDADR;

	ग_लिखोl(addr, phy->base + reg);
पूर्ण

अटल व्योम enable_chan(काष्ठा mmp_pdma_phy *phy)
अणु
	u32 reg, dalgn;

	अगर (!phy->vchan)
		वापस;

	reg = DRCMR(phy->vchan->drcmr);
	ग_लिखोl(DRCMR_MAPVLD | phy->idx, phy->base + reg);

	dalgn = पढ़ोl(phy->base + DALGN);
	अगर (phy->vchan->byte_align)
		dalgn |= 1 << phy->idx;
	अन्यथा
		dalgn &= ~(1 << phy->idx);
	ग_लिखोl(dalgn, phy->base + DALGN);

	reg = (phy->idx << 2) + DCSR;
	ग_लिखोl(पढ़ोl(phy->base + reg) | DCSR_RUN, phy->base + reg);
पूर्ण

अटल व्योम disable_chan(काष्ठा mmp_pdma_phy *phy)
अणु
	u32 reg;

	अगर (!phy)
		वापस;

	reg = (phy->idx << 2) + DCSR;
	ग_लिखोl(पढ़ोl(phy->base + reg) & ~DCSR_RUN, phy->base + reg);
पूर्ण

अटल पूर्णांक clear_chan_irq(काष्ठा mmp_pdma_phy *phy)
अणु
	u32 dcsr;
	u32 dपूर्णांक = पढ़ोl(phy->base + DINT);
	u32 reg = (phy->idx << 2) + DCSR;

	अगर (!(dपूर्णांक & BIT(phy->idx)))
		वापस -EAGAIN;

	/* clear irq */
	dcsr = पढ़ोl(phy->base + reg);
	ग_लिखोl(dcsr, phy->base + reg);
	अगर ((dcsr & DCSR_BUSERR) && (phy->vchan))
		dev_warn(phy->vchan->dev, "DCSR_BUSERR\n");

	वापस 0;
पूर्ण

अटल irqवापस_t mmp_pdma_chan_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा mmp_pdma_phy *phy = dev_id;

	अगर (clear_chan_irq(phy) != 0)
		वापस IRQ_NONE;

	tasklet_schedule(&phy->vchan->tasklet);
	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t mmp_pdma_पूर्णांक_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा mmp_pdma_device *pdev = dev_id;
	काष्ठा mmp_pdma_phy *phy;
	u32 dपूर्णांक = पढ़ोl(pdev->base + DINT);
	पूर्णांक i, ret;
	पूर्णांक irq_num = 0;

	जबतक (dपूर्णांक) अणु
		i = __ffs(dपूर्णांक);
		/* only handle पूर्णांकerrupts beदीर्घing to pdma driver*/
		अगर (i >= pdev->dma_channels)
			अवरोध;
		dपूर्णांक &= (dपूर्णांक - 1);
		phy = &pdev->phy[i];
		ret = mmp_pdma_chan_handler(irq, phy);
		अगर (ret == IRQ_HANDLED)
			irq_num++;
	पूर्ण

	अगर (irq_num)
		वापस IRQ_HANDLED;

	वापस IRQ_NONE;
पूर्ण

/* lookup मुक्त phy channel as descending priority */
अटल काष्ठा mmp_pdma_phy *lookup_phy(काष्ठा mmp_pdma_chan *pchan)
अणु
	पूर्णांक prio, i;
	काष्ठा mmp_pdma_device *pdev = to_mmp_pdma_dev(pchan->chan.device);
	काष्ठा mmp_pdma_phy *phy, *found = शून्य;
	अचिन्हित दीर्घ flags;

	/*
	 * dma channel priorities
	 * ch 0 - 3,  16 - 19  <--> (0)
	 * ch 4 - 7,  20 - 23  <--> (1)
	 * ch 8 - 11, 24 - 27  <--> (2)
	 * ch 12 - 15, 28 - 31  <--> (3)
	 */

	spin_lock_irqsave(&pdev->phy_lock, flags);
	क्रम (prio = 0; prio <= ((pdev->dma_channels - 1) & 0xf) >> 2; prio++) अणु
		क्रम (i = 0; i < pdev->dma_channels; i++) अणु
			अगर (prio != (i & 0xf) >> 2)
				जारी;
			phy = &pdev->phy[i];
			अगर (!phy->vchan) अणु
				phy->vchan = pchan;
				found = phy;
				जाओ out_unlock;
			पूर्ण
		पूर्ण
	पूर्ण

out_unlock:
	spin_unlock_irqrestore(&pdev->phy_lock, flags);
	वापस found;
पूर्ण

अटल व्योम mmp_pdma_मुक्त_phy(काष्ठा mmp_pdma_chan *pchan)
अणु
	काष्ठा mmp_pdma_device *pdev = to_mmp_pdma_dev(pchan->chan.device);
	अचिन्हित दीर्घ flags;
	u32 reg;

	अगर (!pchan->phy)
		वापस;

	/* clear the channel mapping in DRCMR */
	reg = DRCMR(pchan->drcmr);
	ग_लिखोl(0, pchan->phy->base + reg);

	spin_lock_irqsave(&pdev->phy_lock, flags);
	pchan->phy->vchan = शून्य;
	pchan->phy = शून्य;
	spin_unlock_irqrestore(&pdev->phy_lock, flags);
पूर्ण

/*
 * start_pending_queue - transfer any pending transactions
 * pending list ==> running list
 */
अटल व्योम start_pending_queue(काष्ठा mmp_pdma_chan *chan)
अणु
	काष्ठा mmp_pdma_desc_sw *desc;

	/* still in running, irq will start the pending list */
	अगर (!chan->idle) अणु
		dev_dbg(chan->dev, "DMA controller still busy\n");
		वापस;
	पूर्ण

	अगर (list_empty(&chan->chain_pending)) अणु
		/* chance to re-fetch phy channel with higher prio */
		mmp_pdma_मुक्त_phy(chan);
		dev_dbg(chan->dev, "no pending list\n");
		वापस;
	पूर्ण

	अगर (!chan->phy) अणु
		chan->phy = lookup_phy(chan);
		अगर (!chan->phy) अणु
			dev_dbg(chan->dev, "no free dma channel\n");
			वापस;
		पूर्ण
	पूर्ण

	/*
	 * pending -> running
	 * reपूर्णांकilize pending list
	 */
	desc = list_first_entry(&chan->chain_pending,
				काष्ठा mmp_pdma_desc_sw, node);
	list_splice_tail_init(&chan->chain_pending, &chan->chain_running);

	/*
	 * Program the descriptor's address पूर्णांकo the DMA controller,
	 * then start the DMA transaction
	 */
	set_desc(chan->phy, desc->async_tx.phys);
	enable_chan(chan->phy);
	chan->idle = false;
पूर्ण


/* desc->tx_list ==> pending list */
अटल dma_cookie_t mmp_pdma_tx_submit(काष्ठा dma_async_tx_descriptor *tx)
अणु
	काष्ठा mmp_pdma_chan *chan = to_mmp_pdma_chan(tx->chan);
	काष्ठा mmp_pdma_desc_sw *desc = tx_to_mmp_pdma_desc(tx);
	काष्ठा mmp_pdma_desc_sw *child;
	अचिन्हित दीर्घ flags;
	dma_cookie_t cookie = -EBUSY;

	spin_lock_irqsave(&chan->desc_lock, flags);

	list_क्रम_each_entry(child, &desc->tx_list, node) अणु
		cookie = dma_cookie_assign(&child->async_tx);
	पूर्ण

	/* softly link to pending list - desc->tx_list ==> pending list */
	list_splice_tail_init(&desc->tx_list, &chan->chain_pending);

	spin_unlock_irqrestore(&chan->desc_lock, flags);

	वापस cookie;
पूर्ण

अटल काष्ठा mmp_pdma_desc_sw *
mmp_pdma_alloc_descriptor(काष्ठा mmp_pdma_chan *chan)
अणु
	काष्ठा mmp_pdma_desc_sw *desc;
	dma_addr_t pdesc;

	desc = dma_pool_zalloc(chan->desc_pool, GFP_ATOMIC, &pdesc);
	अगर (!desc) अणु
		dev_err(chan->dev, "out of memory for link descriptor\n");
		वापस शून्य;
	पूर्ण

	INIT_LIST_HEAD(&desc->tx_list);
	dma_async_tx_descriptor_init(&desc->async_tx, &chan->chan);
	/* each desc has submit */
	desc->async_tx.tx_submit = mmp_pdma_tx_submit;
	desc->async_tx.phys = pdesc;

	वापस desc;
पूर्ण

/*
 * mmp_pdma_alloc_chan_resources - Allocate resources क्रम DMA channel.
 *
 * This function will create a dma pool क्रम descriptor allocation.
 * Request irq only when channel is requested
 * Return - The number of allocated descriptors.
 */

अटल पूर्णांक mmp_pdma_alloc_chan_resources(काष्ठा dma_chan *dchan)
अणु
	काष्ठा mmp_pdma_chan *chan = to_mmp_pdma_chan(dchan);

	अगर (chan->desc_pool)
		वापस 1;

	chan->desc_pool = dma_pool_create(dev_name(&dchan->dev->device),
					  chan->dev,
					  माप(काष्ठा mmp_pdma_desc_sw),
					  __alignof__(काष्ठा mmp_pdma_desc_sw),
					  0);
	अगर (!chan->desc_pool) अणु
		dev_err(chan->dev, "unable to allocate descriptor pool\n");
		वापस -ENOMEM;
	पूर्ण

	mmp_pdma_मुक्त_phy(chan);
	chan->idle = true;
	chan->dev_addr = 0;
	वापस 1;
पूर्ण

अटल व्योम mmp_pdma_मुक्त_desc_list(काष्ठा mmp_pdma_chan *chan,
				    काष्ठा list_head *list)
अणु
	काष्ठा mmp_pdma_desc_sw *desc, *_desc;

	list_क्रम_each_entry_safe(desc, _desc, list, node) अणु
		list_del(&desc->node);
		dma_pool_मुक्त(chan->desc_pool, desc, desc->async_tx.phys);
	पूर्ण
पूर्ण

अटल व्योम mmp_pdma_मुक्त_chan_resources(काष्ठा dma_chan *dchan)
अणु
	काष्ठा mmp_pdma_chan *chan = to_mmp_pdma_chan(dchan);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&chan->desc_lock, flags);
	mmp_pdma_मुक्त_desc_list(chan, &chan->chain_pending);
	mmp_pdma_मुक्त_desc_list(chan, &chan->chain_running);
	spin_unlock_irqrestore(&chan->desc_lock, flags);

	dma_pool_destroy(chan->desc_pool);
	chan->desc_pool = शून्य;
	chan->idle = true;
	chan->dev_addr = 0;
	mmp_pdma_मुक्त_phy(chan);
	वापस;
पूर्ण

अटल काष्ठा dma_async_tx_descriptor *
mmp_pdma_prep_स_नकल(काष्ठा dma_chan *dchan,
		     dma_addr_t dma_dst, dma_addr_t dma_src,
		     माप_प्रकार len, अचिन्हित दीर्घ flags)
अणु
	काष्ठा mmp_pdma_chan *chan;
	काष्ठा mmp_pdma_desc_sw *first = शून्य, *prev = शून्य, *new;
	माप_प्रकार copy = 0;

	अगर (!dchan)
		वापस शून्य;

	अगर (!len)
		वापस शून्य;

	chan = to_mmp_pdma_chan(dchan);
	chan->byte_align = false;

	अगर (!chan->dir) अणु
		chan->dir = DMA_MEM_TO_MEM;
		chan->dcmd = DCMD_INCTRGADDR | DCMD_INCSRCADDR;
		chan->dcmd |= DCMD_BURST32;
	पूर्ण

	करो अणु
		/* Allocate the link descriptor from DMA pool */
		new = mmp_pdma_alloc_descriptor(chan);
		अगर (!new) अणु
			dev_err(chan->dev, "no memory for desc\n");
			जाओ fail;
		पूर्ण

		copy = min_t(माप_प्रकार, len, PDMA_MAX_DESC_BYTES);
		अगर (dma_src & 0x7 || dma_dst & 0x7)
			chan->byte_align = true;

		new->desc.dcmd = chan->dcmd | (DCMD_LENGTH & copy);
		new->desc.dsadr = dma_src;
		new->desc.dtadr = dma_dst;

		अगर (!first)
			first = new;
		अन्यथा
			prev->desc.ddadr = new->async_tx.phys;

		new->async_tx.cookie = 0;
		async_tx_ack(&new->async_tx);

		prev = new;
		len -= copy;

		अगर (chan->dir == DMA_MEM_TO_DEV) अणु
			dma_src += copy;
		पूर्ण अन्यथा अगर (chan->dir == DMA_DEV_TO_MEM) अणु
			dma_dst += copy;
		पूर्ण अन्यथा अगर (chan->dir == DMA_MEM_TO_MEM) अणु
			dma_src += copy;
			dma_dst += copy;
		पूर्ण

		/* Insert the link descriptor to the LD ring */
		list_add_tail(&new->node, &first->tx_list);
	पूर्ण जबतक (len);

	first->async_tx.flags = flags; /* client is in control of this ack */
	first->async_tx.cookie = -EBUSY;

	/* last desc and fire IRQ */
	new->desc.ddadr = DDADR_STOP;
	new->desc.dcmd |= DCMD_ENसूचीQEN;

	chan->cyclic_first = शून्य;

	वापस &first->async_tx;

fail:
	अगर (first)
		mmp_pdma_मुक्त_desc_list(chan, &first->tx_list);
	वापस शून्य;
पूर्ण

अटल काष्ठा dma_async_tx_descriptor *
mmp_pdma_prep_slave_sg(काष्ठा dma_chan *dchan, काष्ठा scatterlist *sgl,
		       अचिन्हित पूर्णांक sg_len, क्रमागत dma_transfer_direction dir,
		       अचिन्हित दीर्घ flags, व्योम *context)
अणु
	काष्ठा mmp_pdma_chan *chan = to_mmp_pdma_chan(dchan);
	काष्ठा mmp_pdma_desc_sw *first = शून्य, *prev = शून्य, *new = शून्य;
	माप_प्रकार len, avail;
	काष्ठा scatterlist *sg;
	dma_addr_t addr;
	पूर्णांक i;

	अगर ((sgl == शून्य) || (sg_len == 0))
		वापस शून्य;

	chan->byte_align = false;

	mmp_pdma_config_ग_लिखो(dchan, &chan->slave_config, dir);

	क्रम_each_sg(sgl, sg, sg_len, i) अणु
		addr = sg_dma_address(sg);
		avail = sg_dma_len(sgl);

		करो अणु
			len = min_t(माप_प्रकार, avail, PDMA_MAX_DESC_BYTES);
			अगर (addr & 0x7)
				chan->byte_align = true;

			/* allocate and populate the descriptor */
			new = mmp_pdma_alloc_descriptor(chan);
			अगर (!new) अणु
				dev_err(chan->dev, "no memory for desc\n");
				जाओ fail;
			पूर्ण

			new->desc.dcmd = chan->dcmd | (DCMD_LENGTH & len);
			अगर (dir == DMA_MEM_TO_DEV) अणु
				new->desc.dsadr = addr;
				new->desc.dtadr = chan->dev_addr;
			पूर्ण अन्यथा अणु
				new->desc.dsadr = chan->dev_addr;
				new->desc.dtadr = addr;
			पूर्ण

			अगर (!first)
				first = new;
			अन्यथा
				prev->desc.ddadr = new->async_tx.phys;

			new->async_tx.cookie = 0;
			async_tx_ack(&new->async_tx);
			prev = new;

			/* Insert the link descriptor to the LD ring */
			list_add_tail(&new->node, &first->tx_list);

			/* update metadata */
			addr += len;
			avail -= len;
		पूर्ण जबतक (avail);
	पूर्ण

	first->async_tx.cookie = -EBUSY;
	first->async_tx.flags = flags;

	/* last desc and fire IRQ */
	new->desc.ddadr = DDADR_STOP;
	new->desc.dcmd |= DCMD_ENसूचीQEN;

	chan->dir = dir;
	chan->cyclic_first = शून्य;

	वापस &first->async_tx;

fail:
	अगर (first)
		mmp_pdma_मुक्त_desc_list(chan, &first->tx_list);
	वापस शून्य;
पूर्ण

अटल काष्ठा dma_async_tx_descriptor *
mmp_pdma_prep_dma_cyclic(काष्ठा dma_chan *dchan,
			 dma_addr_t buf_addr, माप_प्रकार len, माप_प्रकार period_len,
			 क्रमागत dma_transfer_direction direction,
			 अचिन्हित दीर्घ flags)
अणु
	काष्ठा mmp_pdma_chan *chan;
	काष्ठा mmp_pdma_desc_sw *first = शून्य, *prev = शून्य, *new;
	dma_addr_t dma_src, dma_dst;

	अगर (!dchan || !len || !period_len)
		वापस शून्य;

	/* the buffer length must be a multiple of period_len */
	अगर (len % period_len != 0)
		वापस शून्य;

	अगर (period_len > PDMA_MAX_DESC_BYTES)
		वापस शून्य;

	chan = to_mmp_pdma_chan(dchan);
	mmp_pdma_config_ग_लिखो(dchan, &chan->slave_config, direction);

	चयन (direction) अणु
	हाल DMA_MEM_TO_DEV:
		dma_src = buf_addr;
		dma_dst = chan->dev_addr;
		अवरोध;
	हाल DMA_DEV_TO_MEM:
		dma_dst = buf_addr;
		dma_src = chan->dev_addr;
		अवरोध;
	शेष:
		dev_err(chan->dev, "Unsupported direction for cyclic DMA\n");
		वापस शून्य;
	पूर्ण

	chan->dir = direction;

	करो अणु
		/* Allocate the link descriptor from DMA pool */
		new = mmp_pdma_alloc_descriptor(chan);
		अगर (!new) अणु
			dev_err(chan->dev, "no memory for desc\n");
			जाओ fail;
		पूर्ण

		new->desc.dcmd = (chan->dcmd | DCMD_ENसूचीQEN |
				  (DCMD_LENGTH & period_len));
		new->desc.dsadr = dma_src;
		new->desc.dtadr = dma_dst;

		अगर (!first)
			first = new;
		अन्यथा
			prev->desc.ddadr = new->async_tx.phys;

		new->async_tx.cookie = 0;
		async_tx_ack(&new->async_tx);

		prev = new;
		len -= period_len;

		अगर (chan->dir == DMA_MEM_TO_DEV)
			dma_src += period_len;
		अन्यथा
			dma_dst += period_len;

		/* Insert the link descriptor to the LD ring */
		list_add_tail(&new->node, &first->tx_list);
	पूर्ण जबतक (len);

	first->async_tx.flags = flags; /* client is in control of this ack */
	first->async_tx.cookie = -EBUSY;

	/* make the cyclic link */
	new->desc.ddadr = first->async_tx.phys;
	chan->cyclic_first = first;

	वापस &first->async_tx;

fail:
	अगर (first)
		mmp_pdma_मुक्त_desc_list(chan, &first->tx_list);
	वापस शून्य;
पूर्ण

अटल पूर्णांक mmp_pdma_config_ग_लिखो(काष्ठा dma_chan *dchan,
			   काष्ठा dma_slave_config *cfg,
			   क्रमागत dma_transfer_direction direction)
अणु
	काष्ठा mmp_pdma_chan *chan = to_mmp_pdma_chan(dchan);
	u32 maxburst = 0, addr = 0;
	क्रमागत dma_slave_buswidth width = DMA_SLAVE_BUSWIDTH_UNDEFINED;

	अगर (!dchan)
		वापस -EINVAL;

	अगर (direction == DMA_DEV_TO_MEM) अणु
		chan->dcmd = DCMD_INCTRGADDR | DCMD_FLOWSRC;
		maxburst = cfg->src_maxburst;
		width = cfg->src_addr_width;
		addr = cfg->src_addr;
	पूर्ण अन्यथा अगर (direction == DMA_MEM_TO_DEV) अणु
		chan->dcmd = DCMD_INCSRCADDR | DCMD_FLOWTRG;
		maxburst = cfg->dst_maxburst;
		width = cfg->dst_addr_width;
		addr = cfg->dst_addr;
	पूर्ण

	अगर (width == DMA_SLAVE_BUSWIDTH_1_BYTE)
		chan->dcmd |= DCMD_WIDTH1;
	अन्यथा अगर (width == DMA_SLAVE_BUSWIDTH_2_BYTES)
		chan->dcmd |= DCMD_WIDTH2;
	अन्यथा अगर (width == DMA_SLAVE_BUSWIDTH_4_BYTES)
		chan->dcmd |= DCMD_WIDTH4;

	अगर (maxburst == 8)
		chan->dcmd |= DCMD_BURST8;
	अन्यथा अगर (maxburst == 16)
		chan->dcmd |= DCMD_BURST16;
	अन्यथा अगर (maxburst == 32)
		chan->dcmd |= DCMD_BURST32;

	chan->dir = direction;
	chan->dev_addr = addr;
	/* FIXME: drivers should be ported over to use the filter
	 * function. Once that's करोne, the following two lines can
	 * be हटाओd.
	 */
	अगर (cfg->slave_id)
		chan->drcmr = cfg->slave_id;

	वापस 0;
पूर्ण

अटल पूर्णांक mmp_pdma_config(काष्ठा dma_chan *dchan,
			   काष्ठा dma_slave_config *cfg)
अणु
	काष्ठा mmp_pdma_chan *chan = to_mmp_pdma_chan(dchan);

	स_नकल(&chan->slave_config, cfg, माप(*cfg));
	वापस 0;
पूर्ण

अटल पूर्णांक mmp_pdma_terminate_all(काष्ठा dma_chan *dchan)
अणु
	काष्ठा mmp_pdma_chan *chan = to_mmp_pdma_chan(dchan);
	अचिन्हित दीर्घ flags;

	अगर (!dchan)
		वापस -EINVAL;

	disable_chan(chan->phy);
	mmp_pdma_मुक्त_phy(chan);
	spin_lock_irqsave(&chan->desc_lock, flags);
	mmp_pdma_मुक्त_desc_list(chan, &chan->chain_pending);
	mmp_pdma_मुक्त_desc_list(chan, &chan->chain_running);
	spin_unlock_irqrestore(&chan->desc_lock, flags);
	chan->idle = true;

	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक mmp_pdma_residue(काष्ठा mmp_pdma_chan *chan,
				     dma_cookie_t cookie)
अणु
	काष्ठा mmp_pdma_desc_sw *sw;
	u32 curr, residue = 0;
	bool passed = false;
	bool cyclic = chan->cyclic_first != शून्य;

	/*
	 * If the channel करोes not have a phy poपूर्णांकer anymore, it has alपढ़ोy
	 * been completed. Thereक्रमe, its residue is 0.
	 */
	अगर (!chan->phy)
		वापस 0;

	अगर (chan->dir == DMA_DEV_TO_MEM)
		curr = पढ़ोl(chan->phy->base + DTADR(chan->phy->idx));
	अन्यथा
		curr = पढ़ोl(chan->phy->base + DSADR(chan->phy->idx));

	list_क्रम_each_entry(sw, &chan->chain_running, node) अणु
		u32 start, end, len;

		अगर (chan->dir == DMA_DEV_TO_MEM)
			start = sw->desc.dtadr;
		अन्यथा
			start = sw->desc.dsadr;

		len = sw->desc.dcmd & DCMD_LENGTH;
		end = start + len;

		/*
		 * 'passed' will be latched once we found the descriptor which
		 * lies inside the boundaries of the curr poपूर्णांकer. All
		 * descriptors that occur in the list _after_ we found that
		 * partially handled descriptor are still to be processed and
		 * are hence added to the residual bytes counter.
		 */

		अगर (passed) अणु
			residue += len;
		पूर्ण अन्यथा अगर (curr >= start && curr <= end) अणु
			residue += end - curr;
			passed = true;
		पूर्ण

		/*
		 * Descriptors that have the ENसूचीQEN bit set mark the end of a
		 * transaction chain, and the cookie asचिन्हित with it has been
		 * वापसed previously from mmp_pdma_tx_submit().
		 *
		 * In हाल we have multiple transactions in the running chain,
		 * and the cookie करोes not match the one the user asked us
		 * about, reset the state variables and start over.
		 *
		 * This logic करोes not apply to cyclic transactions, where all
		 * descriptors have the ENसूचीQEN bit set, and क्रम which we
		 * can't have multiple transactions on one channel anyway.
		 */
		अगर (cyclic || !(sw->desc.dcmd & DCMD_ENसूचीQEN))
			जारी;

		अगर (sw->async_tx.cookie == cookie) अणु
			वापस residue;
		पूर्ण अन्यथा अणु
			residue = 0;
			passed = false;
		पूर्ण
	पूर्ण

	/* We should only get here in हाल of cyclic transactions */
	वापस residue;
पूर्ण

अटल क्रमागत dma_status mmp_pdma_tx_status(काष्ठा dma_chan *dchan,
					  dma_cookie_t cookie,
					  काष्ठा dma_tx_state *txstate)
अणु
	काष्ठा mmp_pdma_chan *chan = to_mmp_pdma_chan(dchan);
	क्रमागत dma_status ret;

	ret = dma_cookie_status(dchan, cookie, txstate);
	अगर (likely(ret != DMA_ERROR))
		dma_set_residue(txstate, mmp_pdma_residue(chan, cookie));

	वापस ret;
पूर्ण

/*
 * mmp_pdma_issue_pending - Issue the DMA start command
 * pending list ==> running list
 */
अटल व्योम mmp_pdma_issue_pending(काष्ठा dma_chan *dchan)
अणु
	काष्ठा mmp_pdma_chan *chan = to_mmp_pdma_chan(dchan);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&chan->desc_lock, flags);
	start_pending_queue(chan);
	spin_unlock_irqrestore(&chan->desc_lock, flags);
पूर्ण

/*
 * dma_करो_tasklet
 * Do call back
 * Start pending list
 */
अटल व्योम dma_करो_tasklet(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा mmp_pdma_chan *chan = from_tasklet(chan, t, tasklet);
	काष्ठा mmp_pdma_desc_sw *desc, *_desc;
	LIST_HEAD(chain_cleanup);
	अचिन्हित दीर्घ flags;
	काष्ठा dmaengine_desc_callback cb;

	अगर (chan->cyclic_first) अणु
		spin_lock_irqsave(&chan->desc_lock, flags);
		desc = chan->cyclic_first;
		dmaengine_desc_get_callback(&desc->async_tx, &cb);
		spin_unlock_irqrestore(&chan->desc_lock, flags);

		dmaengine_desc_callback_invoke(&cb, शून्य);

		वापस;
	पूर्ण

	/* submit pending list; callback क्रम each desc; मुक्त desc */
	spin_lock_irqsave(&chan->desc_lock, flags);

	list_क्रम_each_entry_safe(desc, _desc, &chan->chain_running, node) अणु
		/*
		 * move the descriptors to a temporary list so we can drop
		 * the lock during the entire cleanup operation
		 */
		list_move(&desc->node, &chain_cleanup);

		/*
		 * Look क्रम the first list entry which has the ENसूचीQEN flag
		 * set. That is the descriptor we got an पूर्णांकerrupt क्रम, so
		 * complete that transaction and its cookie.
		 */
		अगर (desc->desc.dcmd & DCMD_ENसूचीQEN) अणु
			dma_cookie_t cookie = desc->async_tx.cookie;
			dma_cookie_complete(&desc->async_tx);
			dev_dbg(chan->dev, "completed_cookie=%d\n", cookie);
			अवरोध;
		पूर्ण
	पूर्ण

	/*
	 * The hardware is idle and पढ़ोy क्रम more when the
	 * chain_running list is empty.
	 */
	chan->idle = list_empty(&chan->chain_running);

	/* Start any pending transactions स्वतःmatically */
	start_pending_queue(chan);
	spin_unlock_irqrestore(&chan->desc_lock, flags);

	/* Run the callback क्रम each descriptor, in order */
	list_क्रम_each_entry_safe(desc, _desc, &chain_cleanup, node) अणु
		काष्ठा dma_async_tx_descriptor *txd = &desc->async_tx;

		/* Remove from the list of transactions */
		list_del(&desc->node);
		/* Run the link descriptor callback function */
		dmaengine_desc_get_callback(txd, &cb);
		dmaengine_desc_callback_invoke(&cb, शून्य);

		dma_pool_मुक्त(chan->desc_pool, desc, txd->phys);
	पूर्ण
पूर्ण

अटल पूर्णांक mmp_pdma_हटाओ(काष्ठा platक्रमm_device *op)
अणु
	काष्ठा mmp_pdma_device *pdev = platक्रमm_get_drvdata(op);
	काष्ठा mmp_pdma_phy *phy;
	पूर्णांक i, irq = 0, irq_num = 0;

	अगर (op->dev.of_node)
		of_dma_controller_मुक्त(op->dev.of_node);

	क्रम (i = 0; i < pdev->dma_channels; i++) अणु
		अगर (platक्रमm_get_irq(op, i) > 0)
			irq_num++;
	पूर्ण

	अगर (irq_num != pdev->dma_channels) अणु
		irq = platक्रमm_get_irq(op, 0);
		devm_मुक्त_irq(&op->dev, irq, pdev);
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < pdev->dma_channels; i++) अणु
			phy = &pdev->phy[i];
			irq = platक्रमm_get_irq(op, i);
			devm_मुक्त_irq(&op->dev, irq, phy);
		पूर्ण
	पूर्ण

	dma_async_device_unरेजिस्टर(&pdev->device);
	वापस 0;
पूर्ण

अटल पूर्णांक mmp_pdma_chan_init(काष्ठा mmp_pdma_device *pdev, पूर्णांक idx, पूर्णांक irq)
अणु
	काष्ठा mmp_pdma_phy *phy  = &pdev->phy[idx];
	काष्ठा mmp_pdma_chan *chan;
	पूर्णांक ret;

	chan = devm_kzalloc(pdev->dev, माप(*chan), GFP_KERNEL);
	अगर (chan == शून्य)
		वापस -ENOMEM;

	phy->idx = idx;
	phy->base = pdev->base;

	अगर (irq) अणु
		ret = devm_request_irq(pdev->dev, irq, mmp_pdma_chan_handler,
				       IRQF_SHARED, "pdma", phy);
		अगर (ret) अणु
			dev_err(pdev->dev, "channel request irq fail!\n");
			वापस ret;
		पूर्ण
	पूर्ण

	spin_lock_init(&chan->desc_lock);
	chan->dev = pdev->dev;
	chan->chan.device = &pdev->device;
	tasklet_setup(&chan->tasklet, dma_करो_tasklet);
	INIT_LIST_HEAD(&chan->chain_pending);
	INIT_LIST_HEAD(&chan->chain_running);

	/* रेजिस्टर virt channel to dma engine */
	list_add_tail(&chan->chan.device_node, &pdev->device.channels);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id mmp_pdma_dt_ids[] = अणु
	अणु .compatible = "marvell,pdma-1.0", पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, mmp_pdma_dt_ids);

अटल काष्ठा dma_chan *mmp_pdma_dma_xlate(काष्ठा of_phandle_args *dma_spec,
					   काष्ठा of_dma *ofdma)
अणु
	काष्ठा mmp_pdma_device *d = ofdma->of_dma_data;
	काष्ठा dma_chan *chan;

	chan = dma_get_any_slave_channel(&d->device);
	अगर (!chan)
		वापस शून्य;

	to_mmp_pdma_chan(chan)->drcmr = dma_spec->args[0];

	वापस chan;
पूर्ण

अटल पूर्णांक mmp_pdma_probe(काष्ठा platक्रमm_device *op)
अणु
	काष्ठा mmp_pdma_device *pdev;
	स्थिर काष्ठा of_device_id *of_id;
	काष्ठा mmp_dma_platdata *pdata = dev_get_platdata(&op->dev);
	काष्ठा resource *iores;
	पूर्णांक i, ret, irq = 0;
	पूर्णांक dma_channels = 0, irq_num = 0;
	स्थिर क्रमागत dma_slave_buswidth widths =
		DMA_SLAVE_BUSWIDTH_1_BYTE   | DMA_SLAVE_BUSWIDTH_2_BYTES |
		DMA_SLAVE_BUSWIDTH_4_BYTES;

	pdev = devm_kzalloc(&op->dev, माप(*pdev), GFP_KERNEL);
	अगर (!pdev)
		वापस -ENOMEM;

	pdev->dev = &op->dev;

	spin_lock_init(&pdev->phy_lock);

	iores = platक्रमm_get_resource(op, IORESOURCE_MEM, 0);
	pdev->base = devm_ioremap_resource(pdev->dev, iores);
	अगर (IS_ERR(pdev->base))
		वापस PTR_ERR(pdev->base);

	of_id = of_match_device(mmp_pdma_dt_ids, pdev->dev);
	अगर (of_id)
		of_property_पढ़ो_u32(pdev->dev->of_node, "#dma-channels",
				     &dma_channels);
	अन्यथा अगर (pdata && pdata->dma_channels)
		dma_channels = pdata->dma_channels;
	अन्यथा
		dma_channels = 32;	/* शेष 32 channel */
	pdev->dma_channels = dma_channels;

	क्रम (i = 0; i < dma_channels; i++) अणु
		अगर (platक्रमm_get_irq_optional(op, i) > 0)
			irq_num++;
	पूर्ण

	pdev->phy = devm_kसुस्मृति(pdev->dev, dma_channels, माप(*pdev->phy),
				 GFP_KERNEL);
	अगर (pdev->phy == शून्य)
		वापस -ENOMEM;

	INIT_LIST_HEAD(&pdev->device.channels);

	अगर (irq_num != dma_channels) अणु
		/* all chan share one irq, demux inside */
		irq = platक्रमm_get_irq(op, 0);
		ret = devm_request_irq(pdev->dev, irq, mmp_pdma_पूर्णांक_handler,
				       IRQF_SHARED, "pdma", pdev);
		अगर (ret)
			वापस ret;
	पूर्ण

	क्रम (i = 0; i < dma_channels; i++) अणु
		irq = (irq_num != dma_channels) ? 0 : platक्रमm_get_irq(op, i);
		ret = mmp_pdma_chan_init(pdev, i, irq);
		अगर (ret)
			वापस ret;
	पूर्ण

	dma_cap_set(DMA_SLAVE, pdev->device.cap_mask);
	dma_cap_set(DMA_MEMCPY, pdev->device.cap_mask);
	dma_cap_set(DMA_CYCLIC, pdev->device.cap_mask);
	dma_cap_set(DMA_PRIVATE, pdev->device.cap_mask);
	pdev->device.dev = &op->dev;
	pdev->device.device_alloc_chan_resources = mmp_pdma_alloc_chan_resources;
	pdev->device.device_मुक्त_chan_resources = mmp_pdma_मुक्त_chan_resources;
	pdev->device.device_tx_status = mmp_pdma_tx_status;
	pdev->device.device_prep_dma_स_नकल = mmp_pdma_prep_स_नकल;
	pdev->device.device_prep_slave_sg = mmp_pdma_prep_slave_sg;
	pdev->device.device_prep_dma_cyclic = mmp_pdma_prep_dma_cyclic;
	pdev->device.device_issue_pending = mmp_pdma_issue_pending;
	pdev->device.device_config = mmp_pdma_config;
	pdev->device.device_terminate_all = mmp_pdma_terminate_all;
	pdev->device.copy_align = DMAENGINE_ALIGN_8_BYTES;
	pdev->device.src_addr_widths = widths;
	pdev->device.dst_addr_widths = widths;
	pdev->device.directions = BIT(DMA_MEM_TO_DEV) | BIT(DMA_DEV_TO_MEM);
	pdev->device.residue_granularity = DMA_RESIDUE_GRANULARITY_DESCRIPTOR;

	अगर (pdev->dev->coherent_dma_mask)
		dma_set_mask(pdev->dev, pdev->dev->coherent_dma_mask);
	अन्यथा
		dma_set_mask(pdev->dev, DMA_BIT_MASK(64));

	ret = dma_async_device_रेजिस्टर(&pdev->device);
	अगर (ret) अणु
		dev_err(pdev->device.dev, "unable to register\n");
		वापस ret;
	पूर्ण

	अगर (op->dev.of_node) अणु
		/* Device-tree DMA controller registration */
		ret = of_dma_controller_रेजिस्टर(op->dev.of_node,
						 mmp_pdma_dma_xlate, pdev);
		अगर (ret < 0) अणु
			dev_err(&op->dev, "of_dma_controller_register failed\n");
			वापस ret;
		पूर्ण
	पूर्ण

	platक्रमm_set_drvdata(op, pdev);
	dev_info(pdev->device.dev, "initialized %d channels\n", dma_channels);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा platक्रमm_device_id mmp_pdma_id_table[] = अणु
	अणु "mmp-pdma", पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver mmp_pdma_driver = अणु
	.driver		= अणु
		.name	= "mmp-pdma",
		.of_match_table = mmp_pdma_dt_ids,
	पूर्ण,
	.id_table	= mmp_pdma_id_table,
	.probe		= mmp_pdma_probe,
	.हटाओ		= mmp_pdma_हटाओ,
पूर्ण;

module_platक्रमm_driver(mmp_pdma_driver);

MODULE_DESCRIPTION("MARVELL MMP Peripheral DMA Driver");
MODULE_AUTHOR("Marvell International Ltd.");
MODULE_LICENSE("GPL v2");
