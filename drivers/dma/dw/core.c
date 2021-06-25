<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Core driver क्रम the Synopsys DesignWare DMA Controller
 *
 * Copyright (C) 2007-2008 Aपंचांगel Corporation
 * Copyright (C) 2010-2011 ST Microelectronics
 * Copyright (C) 2013 Intel Corporation
 */

#समावेश <linux/bitops.h>
#समावेश <linux/delay.h>
#समावेश <linux/dmaengine.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/dmapool.h>
#समावेश <linux/err.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/mm.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/pm_runसमय.स>

#समावेश "../dmaengine.h"
#समावेश "internal.h"

/*
 * This supports the Synopsys "DesignWare AHB Central DMA Controller",
 * (DW_ahb_dmac) which is used with various AMBA 2.0 प्रणालीs (not all
 * of which use ARM any more).  See the "Databook" from Synopsys क्रम
 * inक्रमmation beyond what licensees probably provide.
 *
 * The driver has been tested with the Aपंचांगel AT32AP7000, which करोes not
 * support descriptor ग_लिखोback.
 */

/* The set of bus widths supported by the DMA controller */
#घोषणा DW_DMA_BUSWIDTHS			  \
	BIT(DMA_SLAVE_BUSWIDTH_UNDEFINED)	| \
	BIT(DMA_SLAVE_BUSWIDTH_1_BYTE)		| \
	BIT(DMA_SLAVE_BUSWIDTH_2_BYTES)		| \
	BIT(DMA_SLAVE_BUSWIDTH_4_BYTES)

/*----------------------------------------------------------------------*/

अटल काष्ठा device *chan2dev(काष्ठा dma_chan *chan)
अणु
	वापस &chan->dev->device;
पूर्ण

अटल काष्ठा dw_desc *dwc_first_active(काष्ठा dw_dma_chan *dwc)
अणु
	वापस to_dw_desc(dwc->active_list.next);
पूर्ण

अटल dma_cookie_t dwc_tx_submit(काष्ठा dma_async_tx_descriptor *tx)
अणु
	काष्ठा dw_desc		*desc = txd_to_dw_desc(tx);
	काष्ठा dw_dma_chan	*dwc = to_dw_dma_chan(tx->chan);
	dma_cookie_t		cookie;
	अचिन्हित दीर्घ		flags;

	spin_lock_irqsave(&dwc->lock, flags);
	cookie = dma_cookie_assign(tx);

	/*
	 * REVISIT: We should attempt to chain as many descriptors as
	 * possible, perhaps even appending to those alपढ़ोy submitted
	 * क्रम DMA. But this is hard to करो in a race-मुक्त manner.
	 */

	list_add_tail(&desc->desc_node, &dwc->queue);
	spin_unlock_irqrestore(&dwc->lock, flags);
	dev_vdbg(chan2dev(tx->chan), "%s: queued %u\n",
		 __func__, desc->txd.cookie);

	वापस cookie;
पूर्ण

अटल काष्ठा dw_desc *dwc_desc_get(काष्ठा dw_dma_chan *dwc)
अणु
	काष्ठा dw_dma *dw = to_dw_dma(dwc->chan.device);
	काष्ठा dw_desc *desc;
	dma_addr_t phys;

	desc = dma_pool_zalloc(dw->desc_pool, GFP_ATOMIC, &phys);
	अगर (!desc)
		वापस शून्य;

	dwc->descs_allocated++;
	INIT_LIST_HEAD(&desc->tx_list);
	dma_async_tx_descriptor_init(&desc->txd, &dwc->chan);
	desc->txd.tx_submit = dwc_tx_submit;
	desc->txd.flags = DMA_CTRL_ACK;
	desc->txd.phys = phys;
	वापस desc;
पूर्ण

अटल व्योम dwc_desc_put(काष्ठा dw_dma_chan *dwc, काष्ठा dw_desc *desc)
अणु
	काष्ठा dw_dma *dw = to_dw_dma(dwc->chan.device);
	काष्ठा dw_desc *child, *_next;

	अगर (unlikely(!desc))
		वापस;

	list_क्रम_each_entry_safe(child, _next, &desc->tx_list, desc_node) अणु
		list_del(&child->desc_node);
		dma_pool_मुक्त(dw->desc_pool, child, child->txd.phys);
		dwc->descs_allocated--;
	पूर्ण

	dma_pool_मुक्त(dw->desc_pool, desc, desc->txd.phys);
	dwc->descs_allocated--;
पूर्ण

अटल व्योम dwc_initialize(काष्ठा dw_dma_chan *dwc)
अणु
	काष्ठा dw_dma *dw = to_dw_dma(dwc->chan.device);

	dw->initialize_chan(dwc);

	/* Enable पूर्णांकerrupts */
	channel_set_bit(dw, MASK.XFER, dwc->mask);
	channel_set_bit(dw, MASK.ERROR, dwc->mask);
पूर्ण

/*----------------------------------------------------------------------*/

अटल अंतरभूत व्योम dwc_dump_chan_regs(काष्ठा dw_dma_chan *dwc)
अणु
	dev_err(chan2dev(&dwc->chan),
		"  SAR: 0x%x DAR: 0x%x LLP: 0x%x CTL: 0x%x:%08x\n",
		channel_पढ़ोl(dwc, SAR),
		channel_पढ़ोl(dwc, DAR),
		channel_पढ़ोl(dwc, LLP),
		channel_पढ़ोl(dwc, CTL_HI),
		channel_पढ़ोl(dwc, CTL_LO));
पूर्ण

अटल अंतरभूत व्योम dwc_chan_disable(काष्ठा dw_dma *dw, काष्ठा dw_dma_chan *dwc)
अणु
	channel_clear_bit(dw, CH_EN, dwc->mask);
	जबतक (dma_पढ़ोl(dw, CH_EN) & dwc->mask)
		cpu_relax();
पूर्ण

/*----------------------------------------------------------------------*/

/* Perक्रमm single block transfer */
अटल अंतरभूत व्योम dwc_करो_single_block(काष्ठा dw_dma_chan *dwc,
				       काष्ठा dw_desc *desc)
अणु
	काष्ठा dw_dma	*dw = to_dw_dma(dwc->chan.device);
	u32		ctllo;

	/*
	 * Software emulation of LLP mode relies on पूर्णांकerrupts to जारी
	 * multi block transfer.
	 */
	ctllo = lli_पढ़ो(desc, ctllo) | DWC_CTLL_INT_EN;

	channel_ग_लिखोl(dwc, SAR, lli_पढ़ो(desc, sar));
	channel_ग_लिखोl(dwc, DAR, lli_पढ़ो(desc, dar));
	channel_ग_लिखोl(dwc, CTL_LO, ctllo);
	channel_ग_लिखोl(dwc, CTL_HI, lli_पढ़ो(desc, ctlhi));
	channel_set_bit(dw, CH_EN, dwc->mask);

	/* Move poपूर्णांकer to next descriptor */
	dwc->tx_node_active = dwc->tx_node_active->next;
पूर्ण

/* Called with dwc->lock held and bh disabled */
अटल व्योम dwc_करोstart(काष्ठा dw_dma_chan *dwc, काष्ठा dw_desc *first)
अणु
	काष्ठा dw_dma	*dw = to_dw_dma(dwc->chan.device);
	u8		lms = DWC_LLP_LMS(dwc->dws.m_master);
	अचिन्हित दीर्घ	was_soft_llp;

	/* ASSERT:  channel is idle */
	अगर (dma_पढ़ोl(dw, CH_EN) & dwc->mask) अणु
		dev_err(chan2dev(&dwc->chan),
			"%s: BUG: Attempted to start non-idle channel\n",
			__func__);
		dwc_dump_chan_regs(dwc);

		/* The tasklet will hopefully advance the queue... */
		वापस;
	पूर्ण

	अगर (dwc->nollp) अणु
		was_soft_llp = test_and_set_bit(DW_DMA_IS_SOFT_LLP,
						&dwc->flags);
		अगर (was_soft_llp) अणु
			dev_err(chan2dev(&dwc->chan),
				"BUG: Attempted to start new LLP transfer inside ongoing one\n");
			वापस;
		पूर्ण

		dwc_initialize(dwc);

		first->residue = first->total_len;
		dwc->tx_node_active = &first->tx_list;

		/* Submit first block */
		dwc_करो_single_block(dwc, first);

		वापस;
	पूर्ण

	dwc_initialize(dwc);

	channel_ग_लिखोl(dwc, LLP, first->txd.phys | lms);
	channel_ग_लिखोl(dwc, CTL_LO, DWC_CTLL_LLP_D_EN | DWC_CTLL_LLP_S_EN);
	channel_ग_लिखोl(dwc, CTL_HI, 0);
	channel_set_bit(dw, CH_EN, dwc->mask);
पूर्ण

अटल व्योम dwc_करोstart_first_queued(काष्ठा dw_dma_chan *dwc)
अणु
	काष्ठा dw_desc *desc;

	अगर (list_empty(&dwc->queue))
		वापस;

	list_move(dwc->queue.next, &dwc->active_list);
	desc = dwc_first_active(dwc);
	dev_vdbg(chan2dev(&dwc->chan), "%s: started %u\n", __func__, desc->txd.cookie);
	dwc_करोstart(dwc, desc);
पूर्ण

/*----------------------------------------------------------------------*/

अटल व्योम
dwc_descriptor_complete(काष्ठा dw_dma_chan *dwc, काष्ठा dw_desc *desc,
		bool callback_required)
अणु
	काष्ठा dma_async_tx_descriptor	*txd = &desc->txd;
	काष्ठा dw_desc			*child;
	अचिन्हित दीर्घ			flags;
	काष्ठा dmaengine_desc_callback	cb;

	dev_vdbg(chan2dev(&dwc->chan), "descriptor %u complete\n", txd->cookie);

	spin_lock_irqsave(&dwc->lock, flags);
	dma_cookie_complete(txd);
	अगर (callback_required)
		dmaengine_desc_get_callback(txd, &cb);
	अन्यथा
		स_रखो(&cb, 0, माप(cb));

	/* async_tx_ack */
	list_क्रम_each_entry(child, &desc->tx_list, desc_node)
		async_tx_ack(&child->txd);
	async_tx_ack(&desc->txd);
	dwc_desc_put(dwc, desc);
	spin_unlock_irqrestore(&dwc->lock, flags);

	dmaengine_desc_callback_invoke(&cb, शून्य);
पूर्ण

अटल व्योम dwc_complete_all(काष्ठा dw_dma *dw, काष्ठा dw_dma_chan *dwc)
अणु
	काष्ठा dw_desc *desc, *_desc;
	LIST_HEAD(list);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&dwc->lock, flags);
	अगर (dma_पढ़ोl(dw, CH_EN) & dwc->mask) अणु
		dev_err(chan2dev(&dwc->chan),
			"BUG: XFER bit set, but channel not idle!\n");

		/* Try to जारी after resetting the channel... */
		dwc_chan_disable(dw, dwc);
	पूर्ण

	/*
	 * Submit queued descriptors ASAP, i.e. beक्रमe we go through
	 * the completed ones.
	 */
	list_splice_init(&dwc->active_list, &list);
	dwc_करोstart_first_queued(dwc);

	spin_unlock_irqrestore(&dwc->lock, flags);

	list_क्रम_each_entry_safe(desc, _desc, &list, desc_node)
		dwc_descriptor_complete(dwc, desc, true);
पूर्ण

/* Returns how many bytes were alपढ़ोy received from source */
अटल अंतरभूत u32 dwc_get_sent(काष्ठा dw_dma_chan *dwc)
अणु
	काष्ठा dw_dma *dw = to_dw_dma(dwc->chan.device);
	u32 ctlhi = channel_पढ़ोl(dwc, CTL_HI);
	u32 ctllo = channel_पढ़ोl(dwc, CTL_LO);

	वापस dw->block2bytes(dwc, ctlhi, ctllo >> 4 & 7);
पूर्ण

अटल व्योम dwc_scan_descriptors(काष्ठा dw_dma *dw, काष्ठा dw_dma_chan *dwc)
अणु
	dma_addr_t llp;
	काष्ठा dw_desc *desc, *_desc;
	काष्ठा dw_desc *child;
	u32 status_xfer;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&dwc->lock, flags);
	llp = channel_पढ़ोl(dwc, LLP);
	status_xfer = dma_पढ़ोl(dw, RAW.XFER);

	अगर (status_xfer & dwc->mask) अणु
		/* Everything we've submitted is करोne */
		dma_ग_लिखोl(dw, CLEAR.XFER, dwc->mask);

		अगर (test_bit(DW_DMA_IS_SOFT_LLP, &dwc->flags)) अणु
			काष्ठा list_head *head, *active = dwc->tx_node_active;

			/*
			 * We are inside first active descriptor.
			 * Otherwise something is really wrong.
			 */
			desc = dwc_first_active(dwc);

			head = &desc->tx_list;
			अगर (active != head) अणु
				/* Update residue to reflect last sent descriptor */
				अगर (active == head->next)
					desc->residue -= desc->len;
				अन्यथा
					desc->residue -= to_dw_desc(active->prev)->len;

				child = to_dw_desc(active);

				/* Submit next block */
				dwc_करो_single_block(dwc, child);

				spin_unlock_irqrestore(&dwc->lock, flags);
				वापस;
			पूर्ण

			/* We are करोne here */
			clear_bit(DW_DMA_IS_SOFT_LLP, &dwc->flags);
		पूर्ण

		spin_unlock_irqrestore(&dwc->lock, flags);

		dwc_complete_all(dw, dwc);
		वापस;
	पूर्ण

	अगर (list_empty(&dwc->active_list)) अणु
		spin_unlock_irqrestore(&dwc->lock, flags);
		वापस;
	पूर्ण

	अगर (test_bit(DW_DMA_IS_SOFT_LLP, &dwc->flags)) अणु
		dev_vdbg(chan2dev(&dwc->chan), "%s: soft LLP mode\n", __func__);
		spin_unlock_irqrestore(&dwc->lock, flags);
		वापस;
	पूर्ण

	dev_vdbg(chan2dev(&dwc->chan), "%s: llp=%pad\n", __func__, &llp);

	list_क्रम_each_entry_safe(desc, _desc, &dwc->active_list, desc_node) अणु
		/* Initial residue value */
		desc->residue = desc->total_len;

		/* Check first descriptors addr */
		अगर (desc->txd.phys == DWC_LLP_LOC(llp)) अणु
			spin_unlock_irqrestore(&dwc->lock, flags);
			वापस;
		पूर्ण

		/* Check first descriptors llp */
		अगर (lli_पढ़ो(desc, llp) == llp) अणु
			/* This one is currently in progress */
			desc->residue -= dwc_get_sent(dwc);
			spin_unlock_irqrestore(&dwc->lock, flags);
			वापस;
		पूर्ण

		desc->residue -= desc->len;
		list_क्रम_each_entry(child, &desc->tx_list, desc_node) अणु
			अगर (lli_पढ़ो(child, llp) == llp) अणु
				/* Currently in progress */
				desc->residue -= dwc_get_sent(dwc);
				spin_unlock_irqrestore(&dwc->lock, flags);
				वापस;
			पूर्ण
			desc->residue -= child->len;
		पूर्ण

		/*
		 * No descriptors so far seem to be in progress, i.e.
		 * this one must be करोne.
		 */
		spin_unlock_irqrestore(&dwc->lock, flags);
		dwc_descriptor_complete(dwc, desc, true);
		spin_lock_irqsave(&dwc->lock, flags);
	पूर्ण

	dev_err(chan2dev(&dwc->chan),
		"BUG: All descriptors done, but channel not idle!\n");

	/* Try to जारी after resetting the channel... */
	dwc_chan_disable(dw, dwc);

	dwc_करोstart_first_queued(dwc);
	spin_unlock_irqrestore(&dwc->lock, flags);
पूर्ण

अटल अंतरभूत व्योम dwc_dump_lli(काष्ठा dw_dma_chan *dwc, काष्ठा dw_desc *desc)
अणु
	dev_crit(chan2dev(&dwc->chan), "  desc: s0x%x d0x%x l0x%x c0x%x:%x\n",
		 lli_पढ़ो(desc, sar),
		 lli_पढ़ो(desc, dar),
		 lli_पढ़ो(desc, llp),
		 lli_पढ़ो(desc, ctlhi),
		 lli_पढ़ो(desc, ctllo));
पूर्ण

अटल व्योम dwc_handle_error(काष्ठा dw_dma *dw, काष्ठा dw_dma_chan *dwc)
अणु
	काष्ठा dw_desc *bad_desc;
	काष्ठा dw_desc *child;
	अचिन्हित दीर्घ flags;

	dwc_scan_descriptors(dw, dwc);

	spin_lock_irqsave(&dwc->lock, flags);

	/*
	 * The descriptor currently at the head of the active list is
	 * borked. Since we करोn't have any way to report errors, we'll
	 * just have to scream loudly and try to carry on.
	 */
	bad_desc = dwc_first_active(dwc);
	list_del_init(&bad_desc->desc_node);
	list_move(dwc->queue.next, dwc->active_list.prev);

	/* Clear the error flag and try to restart the controller */
	dma_ग_लिखोl(dw, CLEAR.ERROR, dwc->mask);
	अगर (!list_empty(&dwc->active_list))
		dwc_करोstart(dwc, dwc_first_active(dwc));

	/*
	 * WARN may seem harsh, but since this only happens
	 * when someone submits a bad physical address in a
	 * descriptor, we should consider ourselves lucky that the
	 * controller flagged an error instead of scribbling over
	 * अक्रमom memory locations.
	 */
	dev_WARN(chan2dev(&dwc->chan), "Bad descriptor submitted for DMA!\n"
				       "  cookie: %d\n", bad_desc->txd.cookie);
	dwc_dump_lli(dwc, bad_desc);
	list_क्रम_each_entry(child, &bad_desc->tx_list, desc_node)
		dwc_dump_lli(dwc, child);

	spin_unlock_irqrestore(&dwc->lock, flags);

	/* Pretend the descriptor completed successfully */
	dwc_descriptor_complete(dwc, bad_desc, true);
पूर्ण

अटल व्योम dw_dma_tasklet(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा dw_dma *dw = from_tasklet(dw, t, tasklet);
	काष्ठा dw_dma_chan *dwc;
	u32 status_xfer;
	u32 status_err;
	अचिन्हित पूर्णांक i;

	status_xfer = dma_पढ़ोl(dw, RAW.XFER);
	status_err = dma_पढ़ोl(dw, RAW.ERROR);

	dev_vdbg(dw->dma.dev, "%s: status_err=%x\n", __func__, status_err);

	क्रम (i = 0; i < dw->dma.chancnt; i++) अणु
		dwc = &dw->chan[i];
		अगर (test_bit(DW_DMA_IS_CYCLIC, &dwc->flags))
			dev_vdbg(dw->dma.dev, "Cyclic xfer is not implemented\n");
		अन्यथा अगर (status_err & (1 << i))
			dwc_handle_error(dw, dwc);
		अन्यथा अगर (status_xfer & (1 << i))
			dwc_scan_descriptors(dw, dwc);
	पूर्ण

	/* Re-enable पूर्णांकerrupts */
	channel_set_bit(dw, MASK.XFER, dw->all_chan_mask);
	channel_set_bit(dw, MASK.ERROR, dw->all_chan_mask);
पूर्ण

अटल irqवापस_t dw_dma_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा dw_dma *dw = dev_id;
	u32 status;

	/* Check अगर we have any पूर्णांकerrupt from the DMAC which is not in use */
	अगर (!dw->in_use)
		वापस IRQ_NONE;

	status = dma_पढ़ोl(dw, STATUS_INT);
	dev_vdbg(dw->dma.dev, "%s: status=0x%x\n", __func__, status);

	/* Check अगर we have any पूर्णांकerrupt from the DMAC */
	अगर (!status)
		वापस IRQ_NONE;

	/*
	 * Just disable the पूर्णांकerrupts. We'll turn them back on in the
	 * softirq handler.
	 */
	channel_clear_bit(dw, MASK.XFER, dw->all_chan_mask);
	channel_clear_bit(dw, MASK.BLOCK, dw->all_chan_mask);
	channel_clear_bit(dw, MASK.ERROR, dw->all_chan_mask);

	status = dma_पढ़ोl(dw, STATUS_INT);
	अगर (status) अणु
		dev_err(dw->dma.dev,
			"BUG: Unexpected interrupts pending: 0x%x\n",
			status);

		/* Try to recover */
		channel_clear_bit(dw, MASK.XFER, (1 << 8) - 1);
		channel_clear_bit(dw, MASK.BLOCK, (1 << 8) - 1);
		channel_clear_bit(dw, MASK.SRC_TRAN, (1 << 8) - 1);
		channel_clear_bit(dw, MASK.DST_TRAN, (1 << 8) - 1);
		channel_clear_bit(dw, MASK.ERROR, (1 << 8) - 1);
	पूर्ण

	tasklet_schedule(&dw->tasklet);

	वापस IRQ_HANDLED;
पूर्ण

/*----------------------------------------------------------------------*/

अटल काष्ठा dma_async_tx_descriptor *
dwc_prep_dma_स_नकल(काष्ठा dma_chan *chan, dma_addr_t dest, dma_addr_t src,
		माप_प्रकार len, अचिन्हित दीर्घ flags)
अणु
	काष्ठा dw_dma_chan	*dwc = to_dw_dma_chan(chan);
	काष्ठा dw_dma		*dw = to_dw_dma(chan->device);
	काष्ठा dw_desc		*desc;
	काष्ठा dw_desc		*first;
	काष्ठा dw_desc		*prev;
	माप_प्रकार			xfer_count;
	माप_प्रकार			offset;
	u8			m_master = dwc->dws.m_master;
	अचिन्हित पूर्णांक		src_width;
	अचिन्हित पूर्णांक		dst_width;
	अचिन्हित पूर्णांक		data_width = dw->pdata->data_width[m_master];
	u32			ctllo, ctlhi;
	u8			lms = DWC_LLP_LMS(m_master);

	dev_vdbg(chan2dev(chan),
			"%s: d%pad s%pad l0x%zx f0x%lx\n", __func__,
			&dest, &src, len, flags);

	अगर (unlikely(!len)) अणु
		dev_dbg(chan2dev(chan), "%s: length is zero!\n", __func__);
		वापस शून्य;
	पूर्ण

	dwc->direction = DMA_MEM_TO_MEM;

	src_width = dst_width = __ffs(data_width | src | dest | len);

	ctllo = dw->prepare_ctllo(dwc)
			| DWC_CTLL_DST_WIDTH(dst_width)
			| DWC_CTLL_SRC_WIDTH(src_width)
			| DWC_CTLL_DST_INC
			| DWC_CTLL_SRC_INC
			| DWC_CTLL_FC_M2M;
	prev = first = शून्य;

	क्रम (offset = 0; offset < len; offset += xfer_count) अणु
		desc = dwc_desc_get(dwc);
		अगर (!desc)
			जाओ err_desc_get;

		ctlhi = dw->bytes2block(dwc, len - offset, src_width, &xfer_count);

		lli_ग_लिखो(desc, sar, src + offset);
		lli_ग_लिखो(desc, dar, dest + offset);
		lli_ग_लिखो(desc, ctllo, ctllo);
		lli_ग_लिखो(desc, ctlhi, ctlhi);
		desc->len = xfer_count;

		अगर (!first) अणु
			first = desc;
		पूर्ण अन्यथा अणु
			lli_ग_लिखो(prev, llp, desc->txd.phys | lms);
			list_add_tail(&desc->desc_node, &first->tx_list);
		पूर्ण
		prev = desc;
	पूर्ण

	अगर (flags & DMA_PREP_INTERRUPT)
		/* Trigger पूर्णांकerrupt after last block */
		lli_set(prev, ctllo, DWC_CTLL_INT_EN);

	prev->lli.llp = 0;
	lli_clear(prev, ctllo, DWC_CTLL_LLP_D_EN | DWC_CTLL_LLP_S_EN);
	first->txd.flags = flags;
	first->total_len = len;

	वापस &first->txd;

err_desc_get:
	dwc_desc_put(dwc, first);
	वापस शून्य;
पूर्ण

अटल काष्ठा dma_async_tx_descriptor *
dwc_prep_slave_sg(काष्ठा dma_chan *chan, काष्ठा scatterlist *sgl,
		अचिन्हित पूर्णांक sg_len, क्रमागत dma_transfer_direction direction,
		अचिन्हित दीर्घ flags, व्योम *context)
अणु
	काष्ठा dw_dma_chan	*dwc = to_dw_dma_chan(chan);
	काष्ठा dw_dma		*dw = to_dw_dma(chan->device);
	काष्ठा dma_slave_config	*sconfig = &dwc->dma_sconfig;
	काष्ठा dw_desc		*prev;
	काष्ठा dw_desc		*first;
	u32			ctllo, ctlhi;
	u8			m_master = dwc->dws.m_master;
	u8			lms = DWC_LLP_LMS(m_master);
	dma_addr_t		reg;
	अचिन्हित पूर्णांक		reg_width;
	अचिन्हित पूर्णांक		mem_width;
	अचिन्हित पूर्णांक		data_width = dw->pdata->data_width[m_master];
	अचिन्हित पूर्णांक		i;
	काष्ठा scatterlist	*sg;
	माप_प्रकार			total_len = 0;

	dev_vdbg(chan2dev(chan), "%s\n", __func__);

	अगर (unlikely(!is_slave_direction(direction) || !sg_len))
		वापस शून्य;

	dwc->direction = direction;

	prev = first = शून्य;

	चयन (direction) अणु
	हाल DMA_MEM_TO_DEV:
		reg_width = __ffs(sconfig->dst_addr_width);
		reg = sconfig->dst_addr;
		ctllo = dw->prepare_ctllo(dwc)
				| DWC_CTLL_DST_WIDTH(reg_width)
				| DWC_CTLL_DST_FIX
				| DWC_CTLL_SRC_INC;

		ctllo |= sconfig->device_fc ? DWC_CTLL_FC(DW_DMA_FC_P_M2P) :
			DWC_CTLL_FC(DW_DMA_FC_D_M2P);

		क्रम_each_sg(sgl, sg, sg_len, i) अणु
			काष्ठा dw_desc	*desc;
			u32		len, mem;
			माप_प्रकार		dlen;

			mem = sg_dma_address(sg);
			len = sg_dma_len(sg);

			mem_width = __ffs(data_width | mem | len);

slave_sg_todev_fill_desc:
			desc = dwc_desc_get(dwc);
			अगर (!desc)
				जाओ err_desc_get;

			ctlhi = dw->bytes2block(dwc, len, mem_width, &dlen);

			lli_ग_लिखो(desc, sar, mem);
			lli_ग_लिखो(desc, dar, reg);
			lli_ग_लिखो(desc, ctlhi, ctlhi);
			lli_ग_लिखो(desc, ctllo, ctllo | DWC_CTLL_SRC_WIDTH(mem_width));
			desc->len = dlen;

			अगर (!first) अणु
				first = desc;
			पूर्ण अन्यथा अणु
				lli_ग_लिखो(prev, llp, desc->txd.phys | lms);
				list_add_tail(&desc->desc_node, &first->tx_list);
			पूर्ण
			prev = desc;

			mem += dlen;
			len -= dlen;
			total_len += dlen;

			अगर (len)
				जाओ slave_sg_todev_fill_desc;
		पूर्ण
		अवरोध;
	हाल DMA_DEV_TO_MEM:
		reg_width = __ffs(sconfig->src_addr_width);
		reg = sconfig->src_addr;
		ctllo = dw->prepare_ctllo(dwc)
				| DWC_CTLL_SRC_WIDTH(reg_width)
				| DWC_CTLL_DST_INC
				| DWC_CTLL_SRC_FIX;

		ctllo |= sconfig->device_fc ? DWC_CTLL_FC(DW_DMA_FC_P_P2M) :
			DWC_CTLL_FC(DW_DMA_FC_D_P2M);

		क्रम_each_sg(sgl, sg, sg_len, i) अणु
			काष्ठा dw_desc	*desc;
			u32		len, mem;
			माप_प्रकार		dlen;

			mem = sg_dma_address(sg);
			len = sg_dma_len(sg);

slave_sg_fromdev_fill_desc:
			desc = dwc_desc_get(dwc);
			अगर (!desc)
				जाओ err_desc_get;

			ctlhi = dw->bytes2block(dwc, len, reg_width, &dlen);

			lli_ग_लिखो(desc, sar, reg);
			lli_ग_लिखो(desc, dar, mem);
			lli_ग_लिखो(desc, ctlhi, ctlhi);
			mem_width = __ffs(data_width | mem);
			lli_ग_लिखो(desc, ctllo, ctllo | DWC_CTLL_DST_WIDTH(mem_width));
			desc->len = dlen;

			अगर (!first) अणु
				first = desc;
			पूर्ण अन्यथा अणु
				lli_ग_लिखो(prev, llp, desc->txd.phys | lms);
				list_add_tail(&desc->desc_node, &first->tx_list);
			पूर्ण
			prev = desc;

			mem += dlen;
			len -= dlen;
			total_len += dlen;

			अगर (len)
				जाओ slave_sg_fromdev_fill_desc;
		पूर्ण
		अवरोध;
	शेष:
		वापस शून्य;
	पूर्ण

	अगर (flags & DMA_PREP_INTERRUPT)
		/* Trigger पूर्णांकerrupt after last block */
		lli_set(prev, ctllo, DWC_CTLL_INT_EN);

	prev->lli.llp = 0;
	lli_clear(prev, ctllo, DWC_CTLL_LLP_D_EN | DWC_CTLL_LLP_S_EN);
	first->total_len = total_len;

	वापस &first->txd;

err_desc_get:
	dev_err(chan2dev(chan),
		"not enough descriptors available. Direction %d\n", direction);
	dwc_desc_put(dwc, first);
	वापस शून्य;
पूर्ण

bool dw_dma_filter(काष्ठा dma_chan *chan, व्योम *param)
अणु
	काष्ठा dw_dma_chan *dwc = to_dw_dma_chan(chan);
	काष्ठा dw_dma_slave *dws = param;

	अगर (dws->dma_dev != chan->device->dev)
		वापस false;

	/* permit channels in accordance with the channels mask */
	अगर (dws->channels && !(dws->channels & dwc->mask))
		वापस false;

	/* We have to copy data since dws can be temporary storage */
	स_नकल(&dwc->dws, dws, माप(काष्ठा dw_dma_slave));

	वापस true;
पूर्ण
EXPORT_SYMBOL_GPL(dw_dma_filter);

अटल पूर्णांक dwc_config(काष्ठा dma_chan *chan, काष्ठा dma_slave_config *sconfig)
अणु
	काष्ठा dw_dma_chan *dwc = to_dw_dma_chan(chan);
	काष्ठा dw_dma *dw = to_dw_dma(chan->device);

	स_नकल(&dwc->dma_sconfig, sconfig, माप(*sconfig));

	dwc->dma_sconfig.src_maxburst =
		clamp(dwc->dma_sconfig.src_maxburst, 0U, dwc->max_burst);
	dwc->dma_sconfig.dst_maxburst =
		clamp(dwc->dma_sconfig.dst_maxburst, 0U, dwc->max_burst);

	dw->encode_maxburst(dwc, &dwc->dma_sconfig.src_maxburst);
	dw->encode_maxburst(dwc, &dwc->dma_sconfig.dst_maxburst);

	वापस 0;
पूर्ण

अटल व्योम dwc_chan_छोड़ो(काष्ठा dw_dma_chan *dwc, bool drain)
अणु
	काष्ठा dw_dma *dw = to_dw_dma(dwc->chan.device);
	अचिन्हित पूर्णांक		count = 20;	/* समयout iterations */

	dw->suspend_chan(dwc, drain);

	जबतक (!(channel_पढ़ोl(dwc, CFG_LO) & DWC_CFGL_FIFO_EMPTY) && count--)
		udelay(2);

	set_bit(DW_DMA_IS_PAUSED, &dwc->flags);
पूर्ण

अटल पूर्णांक dwc_छोड़ो(काष्ठा dma_chan *chan)
अणु
	काष्ठा dw_dma_chan	*dwc = to_dw_dma_chan(chan);
	अचिन्हित दीर्घ		flags;

	spin_lock_irqsave(&dwc->lock, flags);
	dwc_chan_छोड़ो(dwc, false);
	spin_unlock_irqrestore(&dwc->lock, flags);

	वापस 0;
पूर्ण

अटल अंतरभूत व्योम dwc_chan_resume(काष्ठा dw_dma_chan *dwc, bool drain)
अणु
	काष्ठा dw_dma *dw = to_dw_dma(dwc->chan.device);

	dw->resume_chan(dwc, drain);

	clear_bit(DW_DMA_IS_PAUSED, &dwc->flags);
पूर्ण

अटल पूर्णांक dwc_resume(काष्ठा dma_chan *chan)
अणु
	काष्ठा dw_dma_chan	*dwc = to_dw_dma_chan(chan);
	अचिन्हित दीर्घ		flags;

	spin_lock_irqsave(&dwc->lock, flags);

	अगर (test_bit(DW_DMA_IS_PAUSED, &dwc->flags))
		dwc_chan_resume(dwc, false);

	spin_unlock_irqrestore(&dwc->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक dwc_terminate_all(काष्ठा dma_chan *chan)
अणु
	काष्ठा dw_dma_chan	*dwc = to_dw_dma_chan(chan);
	काष्ठा dw_dma		*dw = to_dw_dma(chan->device);
	काष्ठा dw_desc		*desc, *_desc;
	अचिन्हित दीर्घ		flags;
	LIST_HEAD(list);

	spin_lock_irqsave(&dwc->lock, flags);

	clear_bit(DW_DMA_IS_SOFT_LLP, &dwc->flags);

	dwc_chan_छोड़ो(dwc, true);

	dwc_chan_disable(dw, dwc);

	dwc_chan_resume(dwc, true);

	/* active_list entries will end up beक्रमe queued entries */
	list_splice_init(&dwc->queue, &list);
	list_splice_init(&dwc->active_list, &list);

	spin_unlock_irqrestore(&dwc->lock, flags);

	/* Flush all pending and queued descriptors */
	list_क्रम_each_entry_safe(desc, _desc, &list, desc_node)
		dwc_descriptor_complete(dwc, desc, false);

	वापस 0;
पूर्ण

अटल काष्ठा dw_desc *dwc_find_desc(काष्ठा dw_dma_chan *dwc, dma_cookie_t c)
अणु
	काष्ठा dw_desc *desc;

	list_क्रम_each_entry(desc, &dwc->active_list, desc_node)
		अगर (desc->txd.cookie == c)
			वापस desc;

	वापस शून्य;
पूर्ण

अटल u32 dwc_get_residue(काष्ठा dw_dma_chan *dwc, dma_cookie_t cookie)
अणु
	काष्ठा dw_desc *desc;
	अचिन्हित दीर्घ flags;
	u32 residue;

	spin_lock_irqsave(&dwc->lock, flags);

	desc = dwc_find_desc(dwc, cookie);
	अगर (desc) अणु
		अगर (desc == dwc_first_active(dwc)) अणु
			residue = desc->residue;
			अगर (test_bit(DW_DMA_IS_SOFT_LLP, &dwc->flags) && residue)
				residue -= dwc_get_sent(dwc);
		पूर्ण अन्यथा अणु
			residue = desc->total_len;
		पूर्ण
	पूर्ण अन्यथा अणु
		residue = 0;
	पूर्ण

	spin_unlock_irqrestore(&dwc->lock, flags);
	वापस residue;
पूर्ण

अटल क्रमागत dma_status
dwc_tx_status(काष्ठा dma_chan *chan,
	      dma_cookie_t cookie,
	      काष्ठा dma_tx_state *txstate)
अणु
	काष्ठा dw_dma_chan	*dwc = to_dw_dma_chan(chan);
	क्रमागत dma_status		ret;

	ret = dma_cookie_status(chan, cookie, txstate);
	अगर (ret == DMA_COMPLETE)
		वापस ret;

	dwc_scan_descriptors(to_dw_dma(chan->device), dwc);

	ret = dma_cookie_status(chan, cookie, txstate);
	अगर (ret == DMA_COMPLETE)
		वापस ret;

	dma_set_residue(txstate, dwc_get_residue(dwc, cookie));

	अगर (test_bit(DW_DMA_IS_PAUSED, &dwc->flags) && ret == DMA_IN_PROGRESS)
		वापस DMA_PAUSED;

	वापस ret;
पूर्ण

अटल व्योम dwc_issue_pending(काष्ठा dma_chan *chan)
अणु
	काष्ठा dw_dma_chan	*dwc = to_dw_dma_chan(chan);
	अचिन्हित दीर्घ		flags;

	spin_lock_irqsave(&dwc->lock, flags);
	अगर (list_empty(&dwc->active_list))
		dwc_करोstart_first_queued(dwc);
	spin_unlock_irqrestore(&dwc->lock, flags);
पूर्ण

/*----------------------------------------------------------------------*/

व्योम करो_dw_dma_off(काष्ठा dw_dma *dw)
अणु
	dma_ग_लिखोl(dw, CFG, 0);

	channel_clear_bit(dw, MASK.XFER, dw->all_chan_mask);
	channel_clear_bit(dw, MASK.BLOCK, dw->all_chan_mask);
	channel_clear_bit(dw, MASK.SRC_TRAN, dw->all_chan_mask);
	channel_clear_bit(dw, MASK.DST_TRAN, dw->all_chan_mask);
	channel_clear_bit(dw, MASK.ERROR, dw->all_chan_mask);

	जबतक (dma_पढ़ोl(dw, CFG) & DW_CFG_DMA_EN)
		cpu_relax();
पूर्ण

व्योम करो_dw_dma_on(काष्ठा dw_dma *dw)
अणु
	dma_ग_लिखोl(dw, CFG, DW_CFG_DMA_EN);
पूर्ण

अटल पूर्णांक dwc_alloc_chan_resources(काष्ठा dma_chan *chan)
अणु
	काष्ठा dw_dma_chan	*dwc = to_dw_dma_chan(chan);
	काष्ठा dw_dma		*dw = to_dw_dma(chan->device);

	dev_vdbg(chan2dev(chan), "%s\n", __func__);

	/* ASSERT:  channel is idle */
	अगर (dma_पढ़ोl(dw, CH_EN) & dwc->mask) अणु
		dev_dbg(chan2dev(chan), "DMA channel not idle?\n");
		वापस -EIO;
	पूर्ण

	dma_cookie_init(chan);

	/*
	 * NOTE: some controllers may have additional features that we
	 * need to initialize here, like "scatter-gather" (which
	 * करोesn't mean what you think it means), and status ग_लिखोback.
	 */

	/*
	 * We need controller-specअगरic data to set up slave transfers.
	 */
	अगर (chan->निजी && !dw_dma_filter(chan, chan->निजी)) अणु
		dev_warn(chan2dev(chan), "Wrong controller-specific data\n");
		वापस -EINVAL;
	पूर्ण

	/* Enable controller here अगर needed */
	अगर (!dw->in_use)
		करो_dw_dma_on(dw);
	dw->in_use |= dwc->mask;

	वापस 0;
पूर्ण

अटल व्योम dwc_मुक्त_chan_resources(काष्ठा dma_chan *chan)
अणु
	काष्ठा dw_dma_chan	*dwc = to_dw_dma_chan(chan);
	काष्ठा dw_dma		*dw = to_dw_dma(chan->device);
	अचिन्हित दीर्घ		flags;

	dev_dbg(chan2dev(chan), "%s: descs allocated=%u\n", __func__,
			dwc->descs_allocated);

	/* ASSERT:  channel is idle */
	BUG_ON(!list_empty(&dwc->active_list));
	BUG_ON(!list_empty(&dwc->queue));
	BUG_ON(dma_पढ़ोl(to_dw_dma(chan->device), CH_EN) & dwc->mask);

	spin_lock_irqsave(&dwc->lock, flags);

	/* Clear custom channel configuration */
	स_रखो(&dwc->dws, 0, माप(काष्ठा dw_dma_slave));

	/* Disable पूर्णांकerrupts */
	channel_clear_bit(dw, MASK.XFER, dwc->mask);
	channel_clear_bit(dw, MASK.BLOCK, dwc->mask);
	channel_clear_bit(dw, MASK.ERROR, dwc->mask);

	spin_unlock_irqrestore(&dwc->lock, flags);

	/* Disable controller in हाल it was a last user */
	dw->in_use &= ~dwc->mask;
	अगर (!dw->in_use)
		करो_dw_dma_off(dw);

	dev_vdbg(chan2dev(chan), "%s: done\n", __func__);
पूर्ण

अटल व्योम dwc_caps(काष्ठा dma_chan *chan, काष्ठा dma_slave_caps *caps)
अणु
	काष्ठा dw_dma_chan *dwc = to_dw_dma_chan(chan);

	caps->max_burst = dwc->max_burst;

	/*
	 * It might be crucial क्रम some devices to have the hardware
	 * accelerated multi-block transfers supported, aka LLPs in DW DMAC
	 * notation. So अगर LLPs are supported then max_sg_burst is set to
	 * zero which means unlimited number of SG entries can be handled in a
	 * single DMA transaction, otherwise it's just one SG entry.
	 */
	अगर (dwc->nollp)
		caps->max_sg_burst = 1;
	अन्यथा
		caps->max_sg_burst = 0;
पूर्ण

पूर्णांक करो_dma_probe(काष्ठा dw_dma_chip *chip)
अणु
	काष्ठा dw_dma *dw = chip->dw;
	काष्ठा dw_dma_platक्रमm_data *pdata;
	bool			स्वतःcfg = false;
	अचिन्हित पूर्णांक		dw_params;
	अचिन्हित पूर्णांक		i;
	पूर्णांक			err;

	dw->pdata = devm_kzalloc(chip->dev, माप(*dw->pdata), GFP_KERNEL);
	अगर (!dw->pdata)
		वापस -ENOMEM;

	dw->regs = chip->regs;

	pm_runसमय_get_sync(chip->dev);

	अगर (!chip->pdata) अणु
		dw_params = dma_पढ़ोl(dw, DW_PARAMS);
		dev_dbg(chip->dev, "DW_PARAMS: 0x%08x\n", dw_params);

		स्वतःcfg = dw_params >> DW_PARAMS_EN & 1;
		अगर (!स्वतःcfg) अणु
			err = -EINVAL;
			जाओ err_pdata;
		पूर्ण

		/* Reassign the platक्रमm data poपूर्णांकer */
		pdata = dw->pdata;

		/* Get hardware configuration parameters */
		pdata->nr_channels = (dw_params >> DW_PARAMS_NR_CHAN & 7) + 1;
		pdata->nr_masters = (dw_params >> DW_PARAMS_NR_MASTER & 3) + 1;
		क्रम (i = 0; i < pdata->nr_masters; i++) अणु
			pdata->data_width[i] =
				4 << (dw_params >> DW_PARAMS_DATA_WIDTH(i) & 3);
		पूर्ण
		pdata->block_size = dma_पढ़ोl(dw, MAX_BLK_SIZE);

		/* Fill platक्रमm data with the शेष values */
		pdata->chan_allocation_order = CHAN_ALLOCATION_ASCENDING;
		pdata->chan_priority = CHAN_PRIORITY_ASCENDING;
	पूर्ण अन्यथा अगर (chip->pdata->nr_channels > DW_DMA_MAX_NR_CHANNELS) अणु
		err = -EINVAL;
		जाओ err_pdata;
	पूर्ण अन्यथा अणु
		स_नकल(dw->pdata, chip->pdata, माप(*dw->pdata));

		/* Reassign the platक्रमm data poपूर्णांकer */
		pdata = dw->pdata;
	पूर्ण

	dw->chan = devm_kसुस्मृति(chip->dev, pdata->nr_channels, माप(*dw->chan),
				GFP_KERNEL);
	अगर (!dw->chan) अणु
		err = -ENOMEM;
		जाओ err_pdata;
	पूर्ण

	/* Calculate all channel mask beक्रमe DMA setup */
	dw->all_chan_mask = (1 << pdata->nr_channels) - 1;

	/* Force dma off, just in हाल */
	dw->disable(dw);

	/* Device and instance ID क्रम IRQ and DMA pool */
	dw->set_device_name(dw, chip->id);

	/* Create a pool of consistent memory blocks क्रम hardware descriptors */
	dw->desc_pool = dmam_pool_create(dw->name, chip->dev,
					 माप(काष्ठा dw_desc), 4, 0);
	अगर (!dw->desc_pool) अणु
		dev_err(chip->dev, "No memory for descriptors dma pool\n");
		err = -ENOMEM;
		जाओ err_pdata;
	पूर्ण

	tasklet_setup(&dw->tasklet, dw_dma_tasklet);

	err = request_irq(chip->irq, dw_dma_पूर्णांकerrupt, IRQF_SHARED,
			  dw->name, dw);
	अगर (err)
		जाओ err_pdata;

	INIT_LIST_HEAD(&dw->dma.channels);
	क्रम (i = 0; i < pdata->nr_channels; i++) अणु
		काष्ठा dw_dma_chan	*dwc = &dw->chan[i];

		dwc->chan.device = &dw->dma;
		dma_cookie_init(&dwc->chan);
		अगर (pdata->chan_allocation_order == CHAN_ALLOCATION_ASCENDING)
			list_add_tail(&dwc->chan.device_node,
					&dw->dma.channels);
		अन्यथा
			list_add(&dwc->chan.device_node, &dw->dma.channels);

		/* 7 is highest priority & 0 is lowest. */
		अगर (pdata->chan_priority == CHAN_PRIORITY_ASCENDING)
			dwc->priority = pdata->nr_channels - i - 1;
		अन्यथा
			dwc->priority = i;

		dwc->ch_regs = &__dw_regs(dw)->CHAN[i];
		spin_lock_init(&dwc->lock);
		dwc->mask = 1 << i;

		INIT_LIST_HEAD(&dwc->active_list);
		INIT_LIST_HEAD(&dwc->queue);

		channel_clear_bit(dw, CH_EN, dwc->mask);

		dwc->direction = DMA_TRANS_NONE;

		/* Hardware configuration */
		अगर (स्वतःcfg) अणु
			अचिन्हित पूर्णांक r = DW_DMA_MAX_NR_CHANNELS - i - 1;
			व्योम __iomem *addr = &__dw_regs(dw)->DWC_PARAMS[r];
			अचिन्हित पूर्णांक dwc_params = पढ़ोl(addr);

			dev_dbg(chip->dev, "DWC_PARAMS[%d]: 0x%08x\n", i,
					   dwc_params);

			/*
			 * Decode maximum block size क्रम given channel. The
			 * stored 4 bit value represents blocks from 0x00 क्रम 3
			 * up to 0x0a क्रम 4095.
			 */
			dwc->block_size =
				(4 << ((pdata->block_size >> 4 * i) & 0xf)) - 1;

			/*
			 * According to the DW DMA databook the true scatter-
			 * gether LLPs aren't available अगर either multi-block
			 * config is disabled (CHx_MULTI_BLK_EN == 0) or the
			 * LLP रेजिस्टर is hard-coded to zeros
			 * (CHx_HC_LLP == 1).
			 */
			dwc->nollp =
				(dwc_params >> DWC_PARAMS_MBLK_EN & 0x1) == 0 ||
				(dwc_params >> DWC_PARAMS_HC_LLP & 0x1) == 1;
			dwc->max_burst =
				(0x4 << (dwc_params >> DWC_PARAMS_MSIZE & 0x7));
		पूर्ण अन्यथा अणु
			dwc->block_size = pdata->block_size;
			dwc->nollp = !pdata->multi_block[i];
			dwc->max_burst = pdata->max_burst[i] ?: DW_DMA_MAX_BURST;
		पूर्ण
	पूर्ण

	/* Clear all पूर्णांकerrupts on all channels. */
	dma_ग_लिखोl(dw, CLEAR.XFER, dw->all_chan_mask);
	dma_ग_लिखोl(dw, CLEAR.BLOCK, dw->all_chan_mask);
	dma_ग_लिखोl(dw, CLEAR.SRC_TRAN, dw->all_chan_mask);
	dma_ग_लिखोl(dw, CLEAR.DST_TRAN, dw->all_chan_mask);
	dma_ग_लिखोl(dw, CLEAR.ERROR, dw->all_chan_mask);

	/* Set capabilities */
	dma_cap_set(DMA_SLAVE, dw->dma.cap_mask);
	dma_cap_set(DMA_PRIVATE, dw->dma.cap_mask);
	dma_cap_set(DMA_MEMCPY, dw->dma.cap_mask);

	dw->dma.dev = chip->dev;
	dw->dma.device_alloc_chan_resources = dwc_alloc_chan_resources;
	dw->dma.device_मुक्त_chan_resources = dwc_मुक्त_chan_resources;

	dw->dma.device_prep_dma_स_नकल = dwc_prep_dma_स_नकल;
	dw->dma.device_prep_slave_sg = dwc_prep_slave_sg;

	dw->dma.device_caps = dwc_caps;
	dw->dma.device_config = dwc_config;
	dw->dma.device_छोड़ो = dwc_छोड़ो;
	dw->dma.device_resume = dwc_resume;
	dw->dma.device_terminate_all = dwc_terminate_all;

	dw->dma.device_tx_status = dwc_tx_status;
	dw->dma.device_issue_pending = dwc_issue_pending;

	/* DMA capabilities */
	dw->dma.min_burst = DW_DMA_MIN_BURST;
	dw->dma.max_burst = DW_DMA_MAX_BURST;
	dw->dma.src_addr_widths = DW_DMA_BUSWIDTHS;
	dw->dma.dst_addr_widths = DW_DMA_BUSWIDTHS;
	dw->dma.directions = BIT(DMA_DEV_TO_MEM) | BIT(DMA_MEM_TO_DEV) |
			     BIT(DMA_MEM_TO_MEM);
	dw->dma.residue_granularity = DMA_RESIDUE_GRANULARITY_BURST;

	/*
	 * For now there is no hardware with non unअगरorm maximum block size
	 * across all of the device channels, so we set the maximum segment
	 * size as the block size found क्रम the very first channel.
	 */
	dma_set_max_seg_size(dw->dma.dev, dw->chan[0].block_size);

	err = dma_async_device_रेजिस्टर(&dw->dma);
	अगर (err)
		जाओ err_dma_रेजिस्टर;

	dev_info(chip->dev, "DesignWare DMA Controller, %d channels\n",
		 pdata->nr_channels);

	pm_runसमय_put_sync_suspend(chip->dev);

	वापस 0;

err_dma_रेजिस्टर:
	मुक्त_irq(chip->irq, dw);
err_pdata:
	pm_runसमय_put_sync_suspend(chip->dev);
	वापस err;
पूर्ण

पूर्णांक करो_dma_हटाओ(काष्ठा dw_dma_chip *chip)
अणु
	काष्ठा dw_dma		*dw = chip->dw;
	काष्ठा dw_dma_chan	*dwc, *_dwc;

	pm_runसमय_get_sync(chip->dev);

	करो_dw_dma_off(dw);
	dma_async_device_unरेजिस्टर(&dw->dma);

	मुक्त_irq(chip->irq, dw);
	tasklet_समाप्त(&dw->tasklet);

	list_क्रम_each_entry_safe(dwc, _dwc, &dw->dma.channels,
			chan.device_node) अणु
		list_del(&dwc->chan.device_node);
		channel_clear_bit(dw, CH_EN, dwc->mask);
	पूर्ण

	pm_runसमय_put_sync_suspend(chip->dev);
	वापस 0;
पूर्ण

पूर्णांक करो_dw_dma_disable(काष्ठा dw_dma_chip *chip)
अणु
	काष्ठा dw_dma *dw = chip->dw;

	dw->disable(dw);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(करो_dw_dma_disable);

पूर्णांक करो_dw_dma_enable(काष्ठा dw_dma_chip *chip)
अणु
	काष्ठा dw_dma *dw = chip->dw;

	dw->enable(dw);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(करो_dw_dma_enable);

MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("Synopsys DesignWare DMA Controller core driver");
MODULE_AUTHOR("Haavard Skinnemoen (Atmel)");
MODULE_AUTHOR("Viresh Kumar <vireshk@kernel.org>");
