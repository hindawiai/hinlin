<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Driver क्रम the Aपंचांगel AHB DMA Controller (aka HDMA or DMAC on AT91 प्रणालीs)
 *
 * Copyright (C) 2008 Aपंचांगel Corporation
 *
 * This supports the Aपंचांगel AHB DMA Controller found in several Aपंचांगel SoCs.
 * The only Aपंचांगel DMA Controller that is not covered by this driver is the one
 * found on AT91SAM9263.
 */

#समावेश <dt-bindings/dma/at91.h>
#समावेश <linux/clk.h>
#समावेश <linux/dmaengine.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/dmapool.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_dma.h>

#समावेश "at_hdmac_regs.h"
#समावेश "dmaengine.h"

/*
 * Glossary
 * --------
 *
 * at_hdmac		: Name of the ATmel AHB DMA Controller
 * at_dma_ / atdma	: ATmel DMA controller entity related
 * atc_	/ atchan	: ATmel DMA Channel entity related
 */

#घोषणा	ATC_DEFAULT_CFG		(ATC_FIFOCFG_HALFFIFO)
#घोषणा	ATC_DEFAULT_CTRLB	(ATC_SIF(AT_DMA_MEM_IF) \
				|ATC_DIF(AT_DMA_MEM_IF))
#घोषणा ATC_DMA_BUSWIDTHS\
	(BIT(DMA_SLAVE_BUSWIDTH_UNDEFINED) |\
	BIT(DMA_SLAVE_BUSWIDTH_1_BYTE) |\
	BIT(DMA_SLAVE_BUSWIDTH_2_BYTES) |\
	BIT(DMA_SLAVE_BUSWIDTH_4_BYTES))

#घोषणा ATC_MAX_DSCR_TRIALS	10

/*
 * Initial number of descriptors to allocate क्रम each channel. This could
 * be increased during dma usage.
 */
अटल अचिन्हित पूर्णांक init_nr_desc_per_channel = 64;
module_param(init_nr_desc_per_channel, uपूर्णांक, 0644);
MODULE_PARM_DESC(init_nr_desc_per_channel,
		 "initial descriptors per channel (default: 64)");

/**
 * काष्ठा at_dma_platक्रमm_data - Controller configuration parameters
 * @nr_channels: Number of channels supported by hardware (max 8)
 * @cap_mask: dma_capability flags supported by the platक्रमm
 */
काष्ठा at_dma_platक्रमm_data अणु
	अचिन्हित पूर्णांक	nr_channels;
	dma_cap_mask_t  cap_mask;
पूर्ण;

/**
 * काष्ठा at_dma_slave - Controller-specअगरic inक्रमmation about a slave
 * @dma_dev: required DMA master device
 * @cfg: Platक्रमm-specअगरic initializer क्रम the CFG रेजिस्टर
 */
काष्ठा at_dma_slave अणु
	काष्ठा device		*dma_dev;
	u32			cfg;
पूर्ण;

/* prototypes */
अटल dma_cookie_t atc_tx_submit(काष्ठा dma_async_tx_descriptor *tx);
अटल व्योम atc_issue_pending(काष्ठा dma_chan *chan);


/*----------------------------------------------------------------------*/

अटल अंतरभूत अचिन्हित पूर्णांक atc_get_xfer_width(dma_addr_t src, dma_addr_t dst,
						माप_प्रकार len)
अणु
	अचिन्हित पूर्णांक width;

	अगर (!((src | dst  | len) & 3))
		width = 2;
	अन्यथा अगर (!((src | dst | len) & 1))
		width = 1;
	अन्यथा
		width = 0;

	वापस width;
पूर्ण

अटल काष्ठा at_desc *atc_first_active(काष्ठा at_dma_chan *atchan)
अणु
	वापस list_first_entry(&atchan->active_list,
				काष्ठा at_desc, desc_node);
पूर्ण

अटल काष्ठा at_desc *atc_first_queued(काष्ठा at_dma_chan *atchan)
अणु
	वापस list_first_entry(&atchan->queue,
				काष्ठा at_desc, desc_node);
पूर्ण

/**
 * atc_alloc_descriptor - allocate and वापस an initialized descriptor
 * @chan: the channel to allocate descriptors क्रम
 * @gfp_flags: GFP allocation flags
 *
 * Note: The ack-bit is positioned in the descriptor flag at creation समय
 *       to make initial allocation more convenient. This bit will be cleared
 *       and control will be given to client at usage समय (during
 *       preparation functions).
 */
अटल काष्ठा at_desc *atc_alloc_descriptor(काष्ठा dma_chan *chan,
					    gfp_t gfp_flags)
अणु
	काष्ठा at_desc	*desc = शून्य;
	काष्ठा at_dma	*atdma = to_at_dma(chan->device);
	dma_addr_t phys;

	desc = dma_pool_zalloc(atdma->dma_desc_pool, gfp_flags, &phys);
	अगर (desc) अणु
		INIT_LIST_HEAD(&desc->tx_list);
		dma_async_tx_descriptor_init(&desc->txd, chan);
		/* txd.flags will be overwritten in prep functions */
		desc->txd.flags = DMA_CTRL_ACK;
		desc->txd.tx_submit = atc_tx_submit;
		desc->txd.phys = phys;
	पूर्ण

	वापस desc;
पूर्ण

/**
 * atc_desc_get - get an unused descriptor from मुक्त_list
 * @atchan: channel we want a new descriptor क्रम
 */
अटल काष्ठा at_desc *atc_desc_get(काष्ठा at_dma_chan *atchan)
अणु
	काष्ठा at_desc *desc, *_desc;
	काष्ठा at_desc *ret = शून्य;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक i = 0;

	spin_lock_irqsave(&atchan->lock, flags);
	list_क्रम_each_entry_safe(desc, _desc, &atchan->मुक्त_list, desc_node) अणु
		i++;
		अगर (async_tx_test_ack(&desc->txd)) अणु
			list_del(&desc->desc_node);
			ret = desc;
			अवरोध;
		पूर्ण
		dev_dbg(chan2dev(&atchan->chan_common),
				"desc %p not ACKed\n", desc);
	पूर्ण
	spin_unlock_irqrestore(&atchan->lock, flags);
	dev_vdbg(chan2dev(&atchan->chan_common),
		"scanned %u descriptors on freelist\n", i);

	/* no more descriptor available in initial pool: create one more */
	अगर (!ret)
		ret = atc_alloc_descriptor(&atchan->chan_common, GFP_NOWAIT);

	वापस ret;
पूर्ण

/**
 * atc_desc_put - move a descriptor, including any children, to the मुक्त list
 * @atchan: channel we work on
 * @desc: descriptor, at the head of a chain, to move to मुक्त list
 */
अटल व्योम atc_desc_put(काष्ठा at_dma_chan *atchan, काष्ठा at_desc *desc)
अणु
	अगर (desc) अणु
		काष्ठा at_desc *child;
		अचिन्हित दीर्घ flags;

		spin_lock_irqsave(&atchan->lock, flags);
		list_क्रम_each_entry(child, &desc->tx_list, desc_node)
			dev_vdbg(chan2dev(&atchan->chan_common),
					"moving child desc %p to freelist\n",
					child);
		list_splice_init(&desc->tx_list, &atchan->मुक्त_list);
		dev_vdbg(chan2dev(&atchan->chan_common),
			 "moving desc %p to freelist\n", desc);
		list_add(&desc->desc_node, &atchan->मुक्त_list);
		spin_unlock_irqrestore(&atchan->lock, flags);
	पूर्ण
पूर्ण

/**
 * atc_desc_chain - build chain adding a descriptor
 * @first: address of first descriptor of the chain
 * @prev: address of previous descriptor of the chain
 * @desc: descriptor to queue
 *
 * Called from prep_* functions
 */
अटल व्योम atc_desc_chain(काष्ठा at_desc **first, काष्ठा at_desc **prev,
			   काष्ठा at_desc *desc)
अणु
	अगर (!(*first)) अणु
		*first = desc;
	पूर्ण अन्यथा अणु
		/* inक्रमm the HW lli about chaining */
		(*prev)->lli.dscr = desc->txd.phys;
		/* insert the link descriptor to the LD ring */
		list_add_tail(&desc->desc_node,
				&(*first)->tx_list);
	पूर्ण
	*prev = desc;
पूर्ण

/**
 * atc_करोstart - starts the DMA engine क्रम real
 * @atchan: the channel we want to start
 * @first: first descriptor in the list we want to begin with
 *
 * Called with atchan->lock held and bh disabled
 */
अटल व्योम atc_करोstart(काष्ठा at_dma_chan *atchan, काष्ठा at_desc *first)
अणु
	काष्ठा at_dma	*atdma = to_at_dma(atchan->chan_common.device);

	/* ASSERT:  channel is idle */
	अगर (atc_chan_is_enabled(atchan)) अणु
		dev_err(chan2dev(&atchan->chan_common),
			"BUG: Attempted to start non-idle channel\n");
		dev_err(chan2dev(&atchan->chan_common),
			"  channel: s0x%x d0x%x ctrl0x%x:0x%x l0x%x\n",
			channel_पढ़ोl(atchan, SADDR),
			channel_पढ़ोl(atchan, DADDR),
			channel_पढ़ोl(atchan, CTRLA),
			channel_पढ़ोl(atchan, CTRLB),
			channel_पढ़ोl(atchan, DSCR));

		/* The tasklet will hopefully advance the queue... */
		वापस;
	पूर्ण

	vdbg_dump_regs(atchan);

	channel_ग_लिखोl(atchan, SADDR, 0);
	channel_ग_लिखोl(atchan, DADDR, 0);
	channel_ग_लिखोl(atchan, CTRLA, 0);
	channel_ग_लिखोl(atchan, CTRLB, 0);
	channel_ग_लिखोl(atchan, DSCR, first->txd.phys);
	channel_ग_लिखोl(atchan, SPIP, ATC_SPIP_HOLE(first->src_hole) |
		       ATC_SPIP_BOUNDARY(first->boundary));
	channel_ग_लिखोl(atchan, DPIP, ATC_DPIP_HOLE(first->dst_hole) |
		       ATC_DPIP_BOUNDARY(first->boundary));
	dma_ग_लिखोl(atdma, CHER, atchan->mask);

	vdbg_dump_regs(atchan);
पूर्ण

/*
 * atc_get_desc_by_cookie - get the descriptor of a cookie
 * @atchan: the DMA channel
 * @cookie: the cookie to get the descriptor क्रम
 */
अटल काष्ठा at_desc *atc_get_desc_by_cookie(काष्ठा at_dma_chan *atchan,
						dma_cookie_t cookie)
अणु
	काष्ठा at_desc *desc, *_desc;

	list_क्रम_each_entry_safe(desc, _desc, &atchan->queue, desc_node) अणु
		अगर (desc->txd.cookie == cookie)
			वापस desc;
	पूर्ण

	list_क्रम_each_entry_safe(desc, _desc, &atchan->active_list, desc_node) अणु
		अगर (desc->txd.cookie == cookie)
			वापस desc;
	पूर्ण

	वापस शून्य;
पूर्ण

/**
 * atc_calc_bytes_left - calculates the number of bytes left according to the
 * value पढ़ो from CTRLA.
 *
 * @current_len: the number of bytes left beक्रमe पढ़ोing CTRLA
 * @ctrla: the value of CTRLA
 */
अटल अंतरभूत पूर्णांक atc_calc_bytes_left(पूर्णांक current_len, u32 ctrla)
अणु
	u32 btsize = (ctrla & ATC_BTSIZE_MAX);
	u32 src_width = ATC_REG_TO_SRC_WIDTH(ctrla);

	/*
	 * According to the datasheet, when पढ़ोing the Control A Register
	 * (ctrla), the Buffer Transfer Size (btsize) bitfield refers to the
	 * number of transfers completed on the Source Interface.
	 * So btsize is always a number of source width transfers.
	 */
	वापस current_len - (btsize << src_width);
पूर्ण

/**
 * atc_get_bytes_left - get the number of bytes residue क्रम a cookie
 * @chan: DMA channel
 * @cookie: transaction identअगरier to check status of
 */
अटल पूर्णांक atc_get_bytes_left(काष्ठा dma_chan *chan, dma_cookie_t cookie)
अणु
	काष्ठा at_dma_chan      *atchan = to_at_dma_chan(chan);
	काष्ठा at_desc *desc_first = atc_first_active(atchan);
	काष्ठा at_desc *desc;
	पूर्णांक ret;
	u32 ctrla, dscr, trials;

	/*
	 * If the cookie करोesn't match to the currently running transfer then
	 * we can वापस the total length of the associated DMA transfer,
	 * because it is still queued.
	 */
	desc = atc_get_desc_by_cookie(atchan, cookie);
	अगर (desc == शून्य)
		वापस -EINVAL;
	अन्यथा अगर (desc != desc_first)
		वापस desc->total_len;

	/* cookie matches to the currently running transfer */
	ret = desc_first->total_len;

	अगर (desc_first->lli.dscr) अणु
		/* hardware linked list transfer */

		/*
		 * Calculate the residue by removing the length of the child
		 * descriptors alपढ़ोy transferred from the total length.
		 * To get the current child descriptor we can use the value of
		 * the channel's DSCR रेजिस्टर and compare it against the value
		 * of the hardware linked list काष्ठाure of each child
		 * descriptor.
		 *
		 * The CTRLA रेजिस्टर provides us with the amount of data
		 * alपढ़ोy पढ़ो from the source क्रम the current child
		 * descriptor. So we can compute a more accurate residue by also
		 * removing the number of bytes corresponding to this amount of
		 * data.
		 *
		 * However, the DSCR and CTRLA रेजिस्टरs cannot be पढ़ो both
		 * atomically. Hence a race condition may occur: the first पढ़ो
		 * रेजिस्टर may refer to one child descriptor whereas the second
		 * पढ़ो may refer to a later child descriptor in the list
		 * because of the DMA transfer progression inbetween the two
		 * पढ़ोs.
		 *
		 * One solution could have been to छोड़ो the DMA transfer, पढ़ो
		 * the DSCR and CTRLA then resume the DMA transfer. Nonetheless,
		 * this approach presents some drawbacks:
		 * - If the DMA transfer is छोड़ोd, RX overruns or TX underruns
		 *   are more likey to occur depending on the प्रणाली latency.
		 *   Taking the USART driver as an example, it uses a cyclic DMA
		 *   transfer to पढ़ो data from the Receive Holding Register
		 *   (RHR) to aव्योम RX overruns since the RHR is not रक्षित
		 *   by any FIFO on most Aपंचांगel SoCs. So pausing the DMA transfer
		 *   to compute the residue would अवरोध the USART driver design.
		 * - The atc_छोड़ो() function masks पूर्णांकerrupts but we'd rather
		 *   aव्योम to करो so क्रम प्रणाली latency purpose.
		 *
		 * Then we'd rather use another solution: the DSCR is पढ़ो a
		 * first समय, the CTRLA is पढ़ो in turn, next the DSCR is पढ़ो
		 * a second समय. If the two consecutive पढ़ो values of the DSCR
		 * are the same then we assume both refers to the very same
		 * child descriptor as well as the CTRLA value पढ़ो inbetween
		 * करोes. For cyclic tranfers, the assumption is that a full loop
		 * is "not so fast".
		 * If the two DSCR values are dअगरferent, we पढ़ो again the CTRLA
		 * then the DSCR till two consecutive पढ़ो values from DSCR are
		 * equal or till the maxium trials is reach.
		 * This algorithm is very unlikely not to find a stable value क्रम
		 * DSCR.
		 */

		dscr = channel_पढ़ोl(atchan, DSCR);
		rmb(); /* ensure DSCR is पढ़ो beक्रमe CTRLA */
		ctrla = channel_पढ़ोl(atchan, CTRLA);
		क्रम (trials = 0; trials < ATC_MAX_DSCR_TRIALS; ++trials) अणु
			u32 new_dscr;

			rmb(); /* ensure DSCR is पढ़ो after CTRLA */
			new_dscr = channel_पढ़ोl(atchan, DSCR);

			/*
			 * If the DSCR रेजिस्टर value has not changed inside the
			 * DMA controller since the previous पढ़ो, we assume
			 * that both the dscr and ctrla values refers to the
			 * very same descriptor.
			 */
			अगर (likely(new_dscr == dscr))
				अवरोध;

			/*
			 * DSCR has changed inside the DMA controller, so the
			 * previouly पढ़ो value of CTRLA may refer to an alपढ़ोy
			 * processed descriptor hence could be outdated.
			 * We need to update ctrla to match the current
			 * descriptor.
			 */
			dscr = new_dscr;
			rmb(); /* ensure DSCR is पढ़ो beक्रमe CTRLA */
			ctrla = channel_पढ़ोl(atchan, CTRLA);
		पूर्ण
		अगर (unlikely(trials >= ATC_MAX_DSCR_TRIALS))
			वापस -ETIMEDOUT;

		/* क्रम the first descriptor we can be more accurate */
		अगर (desc_first->lli.dscr == dscr)
			वापस atc_calc_bytes_left(ret, ctrla);

		ret -= desc_first->len;
		list_क्रम_each_entry(desc, &desc_first->tx_list, desc_node) अणु
			अगर (desc->lli.dscr == dscr)
				अवरोध;

			ret -= desc->len;
		पूर्ण

		/*
		 * For the current descriptor in the chain we can calculate
		 * the reमुख्यing bytes using the channel's रेजिस्टर.
		 */
		ret = atc_calc_bytes_left(ret, ctrla);
	पूर्ण अन्यथा अणु
		/* single transfer */
		ctrla = channel_पढ़ोl(atchan, CTRLA);
		ret = atc_calc_bytes_left(ret, ctrla);
	पूर्ण

	वापस ret;
पूर्ण

/**
 * atc_chain_complete - finish work क्रम one transaction chain
 * @atchan: channel we work on
 * @desc: descriptor at the head of the chain we want करो complete
 */
अटल व्योम
atc_chain_complete(काष्ठा at_dma_chan *atchan, काष्ठा at_desc *desc)
अणु
	काष्ठा dma_async_tx_descriptor	*txd = &desc->txd;
	काष्ठा at_dma			*atdma = to_at_dma(atchan->chan_common.device);
	अचिन्हित दीर्घ flags;

	dev_vdbg(chan2dev(&atchan->chan_common),
		"descriptor %u complete\n", txd->cookie);

	spin_lock_irqsave(&atchan->lock, flags);

	/* mark the descriptor as complete क्रम non cyclic हालs only */
	अगर (!atc_chan_is_cyclic(atchan))
		dma_cookie_complete(txd);

	/* If the transfer was a स_रखो, मुक्त our temporary buffer */
	अगर (desc->स_रखो_buffer) अणु
		dma_pool_मुक्त(atdma->स_रखो_pool, desc->स_रखो_vaddr,
			      desc->स_रखो_paddr);
		desc->स_रखो_buffer = false;
	पूर्ण

	/* move children to मुक्त_list */
	list_splice_init(&desc->tx_list, &atchan->मुक्त_list);
	/* move myself to मुक्त_list */
	list_move(&desc->desc_node, &atchan->मुक्त_list);

	spin_unlock_irqrestore(&atchan->lock, flags);

	dma_descriptor_unmap(txd);
	/* क्रम cyclic transfers,
	 * no need to replay callback function जबतक stopping */
	अगर (!atc_chan_is_cyclic(atchan))
		dmaengine_desc_get_callback_invoke(txd, शून्य);

	dma_run_dependencies(txd);
पूर्ण

/**
 * atc_complete_all - finish work क्रम all transactions
 * @atchan: channel to complete transactions क्रम
 *
 * Eventually submit queued descriptors अगर any
 *
 * Assume channel is idle जबतक calling this function
 * Called with atchan->lock held and bh disabled
 */
अटल व्योम atc_complete_all(काष्ठा at_dma_chan *atchan)
अणु
	काष्ठा at_desc *desc, *_desc;
	LIST_HEAD(list);
	अचिन्हित दीर्घ flags;

	dev_vdbg(chan2dev(&atchan->chan_common), "complete all\n");

	spin_lock_irqsave(&atchan->lock, flags);

	/*
	 * Submit queued descriptors ASAP, i.e. beक्रमe we go through
	 * the completed ones.
	 */
	अगर (!list_empty(&atchan->queue))
		atc_करोstart(atchan, atc_first_queued(atchan));
	/* empty active_list now it is completed */
	list_splice_init(&atchan->active_list, &list);
	/* empty queue list by moving descriptors (अगर any) to active_list */
	list_splice_init(&atchan->queue, &atchan->active_list);

	spin_unlock_irqrestore(&atchan->lock, flags);

	list_क्रम_each_entry_safe(desc, _desc, &list, desc_node)
		atc_chain_complete(atchan, desc);
पूर्ण

/**
 * atc_advance_work - at the end of a transaction, move क्रमward
 * @atchan: channel where the transaction ended
 */
अटल व्योम atc_advance_work(काष्ठा at_dma_chan *atchan)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	dev_vdbg(chan2dev(&atchan->chan_common), "advance_work\n");

	spin_lock_irqsave(&atchan->lock, flags);
	ret = atc_chan_is_enabled(atchan);
	spin_unlock_irqrestore(&atchan->lock, flags);
	अगर (ret)
		वापस;

	अगर (list_empty(&atchan->active_list) ||
	    list_is_singular(&atchan->active_list))
		वापस atc_complete_all(atchan);

	atc_chain_complete(atchan, atc_first_active(atchan));

	/* advance work */
	spin_lock_irqsave(&atchan->lock, flags);
	atc_करोstart(atchan, atc_first_active(atchan));
	spin_unlock_irqrestore(&atchan->lock, flags);
पूर्ण


/**
 * atc_handle_error - handle errors reported by DMA controller
 * @atchan: channel where error occurs
 */
अटल व्योम atc_handle_error(काष्ठा at_dma_chan *atchan)
अणु
	काष्ठा at_desc *bad_desc;
	काष्ठा at_desc *child;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&atchan->lock, flags);
	/*
	 * The descriptor currently at the head of the active list is
	 * broked. Since we करोn't have any way to report errors, we'll
	 * just have to scream loudly and try to carry on.
	 */
	bad_desc = atc_first_active(atchan);
	list_del_init(&bad_desc->desc_node);

	/* As we are stopped, take advantage to push queued descriptors
	 * in active_list */
	list_splice_init(&atchan->queue, atchan->active_list.prev);

	/* Try to restart the controller */
	अगर (!list_empty(&atchan->active_list))
		atc_करोstart(atchan, atc_first_active(atchan));

	/*
	 * KERN_CRITICAL may seem harsh, but since this only happens
	 * when someone submits a bad physical address in a
	 * descriptor, we should consider ourselves lucky that the
	 * controller flagged an error instead of scribbling over
	 * अक्रमom memory locations.
	 */
	dev_crit(chan2dev(&atchan->chan_common),
			"Bad descriptor submitted for DMA!\n");
	dev_crit(chan2dev(&atchan->chan_common),
			"  cookie: %d\n", bad_desc->txd.cookie);
	atc_dump_lli(atchan, &bad_desc->lli);
	list_क्रम_each_entry(child, &bad_desc->tx_list, desc_node)
		atc_dump_lli(atchan, &child->lli);

	spin_unlock_irqrestore(&atchan->lock, flags);

	/* Pretend the descriptor completed successfully */
	atc_chain_complete(atchan, bad_desc);
पूर्ण

/**
 * atc_handle_cyclic - at the end of a period, run callback function
 * @atchan: channel used क्रम cyclic operations
 */
अटल व्योम atc_handle_cyclic(काष्ठा at_dma_chan *atchan)
अणु
	काष्ठा at_desc			*first = atc_first_active(atchan);
	काष्ठा dma_async_tx_descriptor	*txd = &first->txd;

	dev_vdbg(chan2dev(&atchan->chan_common),
			"new cyclic period llp 0x%08x\n",
			channel_पढ़ोl(atchan, DSCR));

	dmaengine_desc_get_callback_invoke(txd, शून्य);
पूर्ण

/*--  IRQ & Tasklet  ---------------------------------------------------*/

अटल व्योम atc_tasklet(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा at_dma_chan *atchan = from_tasklet(atchan, t, tasklet);

	अगर (test_and_clear_bit(ATC_IS_ERROR, &atchan->status))
		वापस atc_handle_error(atchan);

	अगर (atc_chan_is_cyclic(atchan))
		वापस atc_handle_cyclic(atchan);

	atc_advance_work(atchan);
पूर्ण

अटल irqवापस_t at_dma_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा at_dma		*atdma = (काष्ठा at_dma *)dev_id;
	काष्ठा at_dma_chan	*atchan;
	पूर्णांक			i;
	u32			status, pending, imr;
	पूर्णांक			ret = IRQ_NONE;

	करो अणु
		imr = dma_पढ़ोl(atdma, EBCIMR);
		status = dma_पढ़ोl(atdma, EBCISR);
		pending = status & imr;

		अगर (!pending)
			अवरोध;

		dev_vdbg(atdma->dma_common.dev,
			"interrupt: status = 0x%08x, 0x%08x, 0x%08x\n",
			 status, imr, pending);

		क्रम (i = 0; i < atdma->dma_common.chancnt; i++) अणु
			atchan = &atdma->chan[i];
			अगर (pending & (AT_DMA_BTC(i) | AT_DMA_ERR(i))) अणु
				अगर (pending & AT_DMA_ERR(i)) अणु
					/* Disable channel on AHB error */
					dma_ग_लिखोl(atdma, CHDR,
						AT_DMA_RES(i) | atchan->mask);
					/* Give inक्रमmation to tasklet */
					set_bit(ATC_IS_ERROR, &atchan->status);
				पूर्ण
				tasklet_schedule(&atchan->tasklet);
				ret = IRQ_HANDLED;
			पूर्ण
		पूर्ण

	पूर्ण जबतक (pending);

	वापस ret;
पूर्ण


/*--  DMA Engine API  --------------------------------------------------*/

/**
 * atc_tx_submit - set the prepared descriptor(s) to be executed by the engine
 * @tx: descriptor at the head of the transaction chain
 *
 * Queue chain अगर DMA engine is working alपढ़ोy
 *
 * Cookie increment and adding to active_list or queue must be atomic
 */
अटल dma_cookie_t atc_tx_submit(काष्ठा dma_async_tx_descriptor *tx)
अणु
	काष्ठा at_desc		*desc = txd_to_at_desc(tx);
	काष्ठा at_dma_chan	*atchan = to_at_dma_chan(tx->chan);
	dma_cookie_t		cookie;
	अचिन्हित दीर्घ		flags;

	spin_lock_irqsave(&atchan->lock, flags);
	cookie = dma_cookie_assign(tx);

	अगर (list_empty(&atchan->active_list)) अणु
		dev_vdbg(chan2dev(tx->chan), "tx_submit: started %u\n",
				desc->txd.cookie);
		atc_करोstart(atchan, desc);
		list_add_tail(&desc->desc_node, &atchan->active_list);
	पूर्ण अन्यथा अणु
		dev_vdbg(chan2dev(tx->chan), "tx_submit: queued %u\n",
				desc->txd.cookie);
		list_add_tail(&desc->desc_node, &atchan->queue);
	पूर्ण

	spin_unlock_irqrestore(&atchan->lock, flags);

	वापस cookie;
पूर्ण

/**
 * atc_prep_dma_पूर्णांकerleaved - prepare memory to memory पूर्णांकerleaved operation
 * @chan: the channel to prepare operation on
 * @xt: Interleaved transfer ढाँचा
 * @flags: tx descriptor status flags
 */
अटल काष्ठा dma_async_tx_descriptor *
atc_prep_dma_पूर्णांकerleaved(काष्ठा dma_chan *chan,
			 काष्ठा dma_पूर्णांकerleaved_ढाँचा *xt,
			 अचिन्हित दीर्घ flags)
अणु
	काष्ठा at_dma_chan	*atchan = to_at_dma_chan(chan);
	काष्ठा data_chunk	*first;
	काष्ठा at_desc		*desc = शून्य;
	माप_प्रकार			xfer_count;
	अचिन्हित पूर्णांक		dwidth;
	u32			ctrla;
	u32			ctrlb;
	माप_प्रकार			len = 0;
	पूर्णांक			i;

	अगर (unlikely(!xt || xt->numf != 1 || !xt->frame_size))
		वापस शून्य;

	first = xt->sgl;

	dev_info(chan2dev(chan),
		 "%s: src=%pad, dest=%pad, numf=%d, frame_size=%d, flags=0x%lx\n",
		__func__, &xt->src_start, &xt->dst_start, xt->numf,
		xt->frame_size, flags);

	/*
	 * The controller can only "skip" X bytes every Y bytes, so we
	 * need to make sure we are given a ढाँचा that fit that
	 * description, ie a ढाँचा with chunks that always have the
	 * same size, with the same ICGs.
	 */
	क्रम (i = 0; i < xt->frame_size; i++) अणु
		काष्ठा data_chunk *chunk = xt->sgl + i;

		अगर ((chunk->size != xt->sgl->size) ||
		    (dmaengine_get_dst_icg(xt, chunk) != dmaengine_get_dst_icg(xt, first)) ||
		    (dmaengine_get_src_icg(xt, chunk) != dmaengine_get_src_icg(xt, first))) अणु
			dev_err(chan2dev(chan),
				"%s: the controller can transfer only identical chunks\n",
				__func__);
			वापस शून्य;
		पूर्ण

		len += chunk->size;
	पूर्ण

	dwidth = atc_get_xfer_width(xt->src_start,
				    xt->dst_start, len);

	xfer_count = len >> dwidth;
	अगर (xfer_count > ATC_BTSIZE_MAX) अणु
		dev_err(chan2dev(chan), "%s: buffer is too big\n", __func__);
		वापस शून्य;
	पूर्ण

	ctrla = ATC_SRC_WIDTH(dwidth) |
		ATC_DST_WIDTH(dwidth);

	ctrlb =   ATC_DEFAULT_CTRLB | ATC_IEN
		| ATC_SRC_ADDR_MODE_INCR
		| ATC_DST_ADDR_MODE_INCR
		| ATC_SRC_PIP
		| ATC_DST_PIP
		| ATC_FC_MEM2MEM;

	/* create the transfer */
	desc = atc_desc_get(atchan);
	अगर (!desc) अणु
		dev_err(chan2dev(chan),
			"%s: couldn't allocate our descriptor\n", __func__);
		वापस शून्य;
	पूर्ण

	desc->lli.saddr = xt->src_start;
	desc->lli.daddr = xt->dst_start;
	desc->lli.ctrla = ctrla | xfer_count;
	desc->lli.ctrlb = ctrlb;

	desc->boundary = first->size >> dwidth;
	desc->dst_hole = (dmaengine_get_dst_icg(xt, first) >> dwidth) + 1;
	desc->src_hole = (dmaengine_get_src_icg(xt, first) >> dwidth) + 1;

	desc->txd.cookie = -EBUSY;
	desc->total_len = desc->len = len;

	/* set end-of-link to the last link descriptor of list*/
	set_desc_eol(desc);

	desc->txd.flags = flags; /* client is in control of this ack */

	वापस &desc->txd;
पूर्ण

/**
 * atc_prep_dma_स_नकल - prepare a स_नकल operation
 * @chan: the channel to prepare operation on
 * @dest: operation भव destination address
 * @src: operation भव source address
 * @len: operation length
 * @flags: tx descriptor status flags
 */
अटल काष्ठा dma_async_tx_descriptor *
atc_prep_dma_स_नकल(काष्ठा dma_chan *chan, dma_addr_t dest, dma_addr_t src,
		माप_प्रकार len, अचिन्हित दीर्घ flags)
अणु
	काष्ठा at_dma_chan	*atchan = to_at_dma_chan(chan);
	काष्ठा at_desc		*desc = शून्य;
	काष्ठा at_desc		*first = शून्य;
	काष्ठा at_desc		*prev = शून्य;
	माप_प्रकार			xfer_count;
	माप_प्रकार			offset;
	अचिन्हित पूर्णांक		src_width;
	अचिन्हित पूर्णांक		dst_width;
	u32			ctrla;
	u32			ctrlb;

	dev_vdbg(chan2dev(chan), "prep_dma_memcpy: d%pad s%pad l0x%zx f0x%lx\n",
			&dest, &src, len, flags);

	अगर (unlikely(!len)) अणु
		dev_dbg(chan2dev(chan), "prep_dma_memcpy: length is zero!\n");
		वापस शून्य;
	पूर्ण

	ctrlb =   ATC_DEFAULT_CTRLB | ATC_IEN
		| ATC_SRC_ADDR_MODE_INCR
		| ATC_DST_ADDR_MODE_INCR
		| ATC_FC_MEM2MEM;

	/*
	 * We can be a lot more clever here, but this should take care
	 * of the most common optimization.
	 */
	src_width = dst_width = atc_get_xfer_width(src, dest, len);

	ctrla = ATC_SRC_WIDTH(src_width) |
		ATC_DST_WIDTH(dst_width);

	क्रम (offset = 0; offset < len; offset += xfer_count << src_width) अणु
		xfer_count = min_t(माप_प्रकार, (len - offset) >> src_width,
				ATC_BTSIZE_MAX);

		desc = atc_desc_get(atchan);
		अगर (!desc)
			जाओ err_desc_get;

		desc->lli.saddr = src + offset;
		desc->lli.daddr = dest + offset;
		desc->lli.ctrla = ctrla | xfer_count;
		desc->lli.ctrlb = ctrlb;

		desc->txd.cookie = 0;
		desc->len = xfer_count << src_width;

		atc_desc_chain(&first, &prev, desc);
	पूर्ण

	/* First descriptor of the chain embedds additional inक्रमmation */
	first->txd.cookie = -EBUSY;
	first->total_len = len;

	/* set end-of-link to the last link descriptor of list*/
	set_desc_eol(desc);

	first->txd.flags = flags; /* client is in control of this ack */

	वापस &first->txd;

err_desc_get:
	atc_desc_put(atchan, first);
	वापस शून्य;
पूर्ण

अटल काष्ठा at_desc *atc_create_स_रखो_desc(काष्ठा dma_chan *chan,
					      dma_addr_t psrc,
					      dma_addr_t pdst,
					      माप_प्रकार len)
अणु
	काष्ठा at_dma_chan *atchan = to_at_dma_chan(chan);
	काष्ठा at_desc *desc;
	माप_प्रकार xfer_count;

	u32 ctrla = ATC_SRC_WIDTH(2) | ATC_DST_WIDTH(2);
	u32 ctrlb = ATC_DEFAULT_CTRLB | ATC_IEN |
		ATC_SRC_ADDR_MODE_FIXED |
		ATC_DST_ADDR_MODE_INCR |
		ATC_FC_MEM2MEM;

	xfer_count = len >> 2;
	अगर (xfer_count > ATC_BTSIZE_MAX) अणु
		dev_err(chan2dev(chan), "%s: buffer is too big\n",
			__func__);
		वापस शून्य;
	पूर्ण

	desc = atc_desc_get(atchan);
	अगर (!desc) अणु
		dev_err(chan2dev(chan), "%s: can't get a descriptor\n",
			__func__);
		वापस शून्य;
	पूर्ण

	desc->lli.saddr = psrc;
	desc->lli.daddr = pdst;
	desc->lli.ctrla = ctrla | xfer_count;
	desc->lli.ctrlb = ctrlb;

	desc->txd.cookie = 0;
	desc->len = len;

	वापस desc;
पूर्ण

/**
 * atc_prep_dma_स_रखो - prepare a स_नकल operation
 * @chan: the channel to prepare operation on
 * @dest: operation भव destination address
 * @value: value to set memory buffer to
 * @len: operation length
 * @flags: tx descriptor status flags
 */
अटल काष्ठा dma_async_tx_descriptor *
atc_prep_dma_स_रखो(काष्ठा dma_chan *chan, dma_addr_t dest, पूर्णांक value,
		    माप_प्रकार len, अचिन्हित दीर्घ flags)
अणु
	काष्ठा at_dma		*atdma = to_at_dma(chan->device);
	काष्ठा at_desc		*desc;
	व्योम __iomem		*vaddr;
	dma_addr_t		paddr;

	dev_vdbg(chan2dev(chan), "%s: d%pad v0x%x l0x%zx f0x%lx\n", __func__,
		&dest, value, len, flags);

	अगर (unlikely(!len)) अणु
		dev_dbg(chan2dev(chan), "%s: length is zero!\n", __func__);
		वापस शून्य;
	पूर्ण

	अगर (!is_dma_fill_aligned(chan->device, dest, 0, len)) अणु
		dev_dbg(chan2dev(chan), "%s: buffer is not aligned\n",
			__func__);
		वापस शून्य;
	पूर्ण

	vaddr = dma_pool_alloc(atdma->स_रखो_pool, GFP_NOWAIT, &paddr);
	अगर (!vaddr) अणु
		dev_err(chan2dev(chan), "%s: couldn't allocate buffer\n",
			__func__);
		वापस शून्य;
	पूर्ण
	*(u32*)vaddr = value;

	desc = atc_create_स_रखो_desc(chan, paddr, dest, len);
	अगर (!desc) अणु
		dev_err(chan2dev(chan), "%s: couldn't get a descriptor\n",
			__func__);
		जाओ err_मुक्त_buffer;
	पूर्ण

	desc->स_रखो_paddr = paddr;
	desc->स_रखो_vaddr = vaddr;
	desc->स_रखो_buffer = true;

	desc->txd.cookie = -EBUSY;
	desc->total_len = len;

	/* set end-of-link on the descriptor */
	set_desc_eol(desc);

	desc->txd.flags = flags;

	वापस &desc->txd;

err_मुक्त_buffer:
	dma_pool_मुक्त(atdma->स_रखो_pool, vaddr, paddr);
	वापस शून्य;
पूर्ण

अटल काष्ठा dma_async_tx_descriptor *
atc_prep_dma_स_रखो_sg(काष्ठा dma_chan *chan,
		       काष्ठा scatterlist *sgl,
		       अचिन्हित पूर्णांक sg_len, पूर्णांक value,
		       अचिन्हित दीर्घ flags)
अणु
	काष्ठा at_dma_chan	*atchan = to_at_dma_chan(chan);
	काष्ठा at_dma		*atdma = to_at_dma(chan->device);
	काष्ठा at_desc		*desc = शून्य, *first = शून्य, *prev = शून्य;
	काष्ठा scatterlist	*sg;
	व्योम __iomem		*vaddr;
	dma_addr_t		paddr;
	माप_प्रकार			total_len = 0;
	पूर्णांक			i;

	dev_vdbg(chan2dev(chan), "%s: v0x%x l0x%zx f0x%lx\n", __func__,
		 value, sg_len, flags);

	अगर (unlikely(!sgl || !sg_len)) अणु
		dev_dbg(chan2dev(chan), "%s: scatterlist is empty!\n",
			__func__);
		वापस शून्य;
	पूर्ण

	vaddr = dma_pool_alloc(atdma->स_रखो_pool, GFP_NOWAIT, &paddr);
	अगर (!vaddr) अणु
		dev_err(chan2dev(chan), "%s: couldn't allocate buffer\n",
			__func__);
		वापस शून्य;
	पूर्ण
	*(u32*)vaddr = value;

	क्रम_each_sg(sgl, sg, sg_len, i) अणु
		dma_addr_t dest = sg_dma_address(sg);
		माप_प्रकार len = sg_dma_len(sg);

		dev_vdbg(chan2dev(chan), "%s: d%pad, l0x%zx\n",
			 __func__, &dest, len);

		अगर (!is_dma_fill_aligned(chan->device, dest, 0, len)) अणु
			dev_err(chan2dev(chan), "%s: buffer is not aligned\n",
				__func__);
			जाओ err_put_desc;
		पूर्ण

		desc = atc_create_स_रखो_desc(chan, paddr, dest, len);
		अगर (!desc)
			जाओ err_put_desc;

		atc_desc_chain(&first, &prev, desc);

		total_len += len;
	पूर्ण

	/*
	 * Only set the buffer poपूर्णांकers on the last descriptor to
	 * aव्योम मुक्त'ing जबतक we have our transfer still going
	 */
	desc->स_रखो_paddr = paddr;
	desc->स_रखो_vaddr = vaddr;
	desc->स_रखो_buffer = true;

	first->txd.cookie = -EBUSY;
	first->total_len = total_len;

	/* set end-of-link on the descriptor */
	set_desc_eol(desc);

	first->txd.flags = flags;

	वापस &first->txd;

err_put_desc:
	atc_desc_put(atchan, first);
	वापस शून्य;
पूर्ण

/**
 * atc_prep_slave_sg - prepare descriptors क्रम a DMA_SLAVE transaction
 * @chan: DMA channel
 * @sgl: scatterlist to transfer to/from
 * @sg_len: number of entries in @scatterlist
 * @direction: DMA direction
 * @flags: tx descriptor status flags
 * @context: transaction context (ignored)
 */
अटल काष्ठा dma_async_tx_descriptor *
atc_prep_slave_sg(काष्ठा dma_chan *chan, काष्ठा scatterlist *sgl,
		अचिन्हित पूर्णांक sg_len, क्रमागत dma_transfer_direction direction,
		अचिन्हित दीर्घ flags, व्योम *context)
अणु
	काष्ठा at_dma_chan	*atchan = to_at_dma_chan(chan);
	काष्ठा at_dma_slave	*atslave = chan->निजी;
	काष्ठा dma_slave_config	*sconfig = &atchan->dma_sconfig;
	काष्ठा at_desc		*first = शून्य;
	काष्ठा at_desc		*prev = शून्य;
	u32			ctrla;
	u32			ctrlb;
	dma_addr_t		reg;
	अचिन्हित पूर्णांक		reg_width;
	अचिन्हित पूर्णांक		mem_width;
	अचिन्हित पूर्णांक		i;
	काष्ठा scatterlist	*sg;
	माप_प्रकार			total_len = 0;

	dev_vdbg(chan2dev(chan), "prep_slave_sg (%d): %s f0x%lx\n",
			sg_len,
			direction == DMA_MEM_TO_DEV ? "TO DEVICE" : "FROM DEVICE",
			flags);

	अगर (unlikely(!atslave || !sg_len)) अणु
		dev_dbg(chan2dev(chan), "prep_slave_sg: sg length is zero!\n");
		वापस शून्य;
	पूर्ण

	ctrla =   ATC_SCSIZE(sconfig->src_maxburst)
		| ATC_DCSIZE(sconfig->dst_maxburst);
	ctrlb = ATC_IEN;

	चयन (direction) अणु
	हाल DMA_MEM_TO_DEV:
		reg_width = convert_buswidth(sconfig->dst_addr_width);
		ctrla |=  ATC_DST_WIDTH(reg_width);
		ctrlb |=  ATC_DST_ADDR_MODE_FIXED
			| ATC_SRC_ADDR_MODE_INCR
			| ATC_FC_MEM2PER
			| ATC_SIF(atchan->mem_अगर) | ATC_DIF(atchan->per_अगर);
		reg = sconfig->dst_addr;
		क्रम_each_sg(sgl, sg, sg_len, i) अणु
			काष्ठा at_desc	*desc;
			u32		len;
			u32		mem;

			desc = atc_desc_get(atchan);
			अगर (!desc)
				जाओ err_desc_get;

			mem = sg_dma_address(sg);
			len = sg_dma_len(sg);
			अगर (unlikely(!len)) अणु
				dev_dbg(chan2dev(chan),
					"prep_slave_sg: sg(%d) data length is zero\n", i);
				जाओ err;
			पूर्ण
			mem_width = 2;
			अगर (unlikely(mem & 3 || len & 3))
				mem_width = 0;

			desc->lli.saddr = mem;
			desc->lli.daddr = reg;
			desc->lli.ctrla = ctrla
					| ATC_SRC_WIDTH(mem_width)
					| len >> mem_width;
			desc->lli.ctrlb = ctrlb;
			desc->len = len;

			atc_desc_chain(&first, &prev, desc);
			total_len += len;
		पूर्ण
		अवरोध;
	हाल DMA_DEV_TO_MEM:
		reg_width = convert_buswidth(sconfig->src_addr_width);
		ctrla |=  ATC_SRC_WIDTH(reg_width);
		ctrlb |=  ATC_DST_ADDR_MODE_INCR
			| ATC_SRC_ADDR_MODE_FIXED
			| ATC_FC_PER2MEM
			| ATC_SIF(atchan->per_अगर) | ATC_DIF(atchan->mem_अगर);

		reg = sconfig->src_addr;
		क्रम_each_sg(sgl, sg, sg_len, i) अणु
			काष्ठा at_desc	*desc;
			u32		len;
			u32		mem;

			desc = atc_desc_get(atchan);
			अगर (!desc)
				जाओ err_desc_get;

			mem = sg_dma_address(sg);
			len = sg_dma_len(sg);
			अगर (unlikely(!len)) अणु
				dev_dbg(chan2dev(chan),
					"prep_slave_sg: sg(%d) data length is zero\n", i);
				जाओ err;
			पूर्ण
			mem_width = 2;
			अगर (unlikely(mem & 3 || len & 3))
				mem_width = 0;

			desc->lli.saddr = reg;
			desc->lli.daddr = mem;
			desc->lli.ctrla = ctrla
					| ATC_DST_WIDTH(mem_width)
					| len >> reg_width;
			desc->lli.ctrlb = ctrlb;
			desc->len = len;

			atc_desc_chain(&first, &prev, desc);
			total_len += len;
		पूर्ण
		अवरोध;
	शेष:
		वापस शून्य;
	पूर्ण

	/* set end-of-link to the last link descriptor of list*/
	set_desc_eol(prev);

	/* First descriptor of the chain embedds additional inक्रमmation */
	first->txd.cookie = -EBUSY;
	first->total_len = total_len;

	/* first link descriptor of list is responsible of flags */
	first->txd.flags = flags; /* client is in control of this ack */

	वापस &first->txd;

err_desc_get:
	dev_err(chan2dev(chan), "not enough descriptors available\n");
err:
	atc_desc_put(atchan, first);
	वापस शून्य;
पूर्ण

/*
 * atc_dma_cyclic_check_values
 * Check क्रम too big/unaligned periods and unaligned DMA buffer
 */
अटल पूर्णांक
atc_dma_cyclic_check_values(अचिन्हित पूर्णांक reg_width, dma_addr_t buf_addr,
		माप_प्रकार period_len)
अणु
	अगर (period_len > (ATC_BTSIZE_MAX << reg_width))
		जाओ err_out;
	अगर (unlikely(period_len & ((1 << reg_width) - 1)))
		जाओ err_out;
	अगर (unlikely(buf_addr & ((1 << reg_width) - 1)))
		जाओ err_out;

	वापस 0;

err_out:
	वापस -EINVAL;
पूर्ण

/*
 * atc_dma_cyclic_fill_desc - Fill one period descriptor
 */
अटल पूर्णांक
atc_dma_cyclic_fill_desc(काष्ठा dma_chan *chan, काष्ठा at_desc *desc,
		अचिन्हित पूर्णांक period_index, dma_addr_t buf_addr,
		अचिन्हित पूर्णांक reg_width, माप_प्रकार period_len,
		क्रमागत dma_transfer_direction direction)
अणु
	काष्ठा at_dma_chan	*atchan = to_at_dma_chan(chan);
	काष्ठा dma_slave_config	*sconfig = &atchan->dma_sconfig;
	u32			ctrla;

	/* prepare common CRTLA value */
	ctrla =   ATC_SCSIZE(sconfig->src_maxburst)
		| ATC_DCSIZE(sconfig->dst_maxburst)
		| ATC_DST_WIDTH(reg_width)
		| ATC_SRC_WIDTH(reg_width)
		| period_len >> reg_width;

	चयन (direction) अणु
	हाल DMA_MEM_TO_DEV:
		desc->lli.saddr = buf_addr + (period_len * period_index);
		desc->lli.daddr = sconfig->dst_addr;
		desc->lli.ctrla = ctrla;
		desc->lli.ctrlb = ATC_DST_ADDR_MODE_FIXED
				| ATC_SRC_ADDR_MODE_INCR
				| ATC_FC_MEM2PER
				| ATC_SIF(atchan->mem_अगर)
				| ATC_DIF(atchan->per_अगर);
		desc->len = period_len;
		अवरोध;

	हाल DMA_DEV_TO_MEM:
		desc->lli.saddr = sconfig->src_addr;
		desc->lli.daddr = buf_addr + (period_len * period_index);
		desc->lli.ctrla = ctrla;
		desc->lli.ctrlb = ATC_DST_ADDR_MODE_INCR
				| ATC_SRC_ADDR_MODE_FIXED
				| ATC_FC_PER2MEM
				| ATC_SIF(atchan->per_अगर)
				| ATC_DIF(atchan->mem_अगर);
		desc->len = period_len;
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * atc_prep_dma_cyclic - prepare the cyclic DMA transfer
 * @chan: the DMA channel to prepare
 * @buf_addr: physical DMA address where the buffer starts
 * @buf_len: total number of bytes क्रम the entire buffer
 * @period_len: number of bytes क्रम each period
 * @direction: transfer direction, to or from device
 * @flags: tx descriptor status flags
 */
अटल काष्ठा dma_async_tx_descriptor *
atc_prep_dma_cyclic(काष्ठा dma_chan *chan, dma_addr_t buf_addr, माप_प्रकार buf_len,
		माप_प्रकार period_len, क्रमागत dma_transfer_direction direction,
		अचिन्हित दीर्घ flags)
अणु
	काष्ठा at_dma_chan	*atchan = to_at_dma_chan(chan);
	काष्ठा at_dma_slave	*atslave = chan->निजी;
	काष्ठा dma_slave_config	*sconfig = &atchan->dma_sconfig;
	काष्ठा at_desc		*first = शून्य;
	काष्ठा at_desc		*prev = शून्य;
	अचिन्हित दीर्घ		was_cyclic;
	अचिन्हित पूर्णांक		reg_width;
	अचिन्हित पूर्णांक		periods = buf_len / period_len;
	अचिन्हित पूर्णांक		i;

	dev_vdbg(chan2dev(chan), "prep_dma_cyclic: %s buf@%pad - %d (%d/%d)\n",
			direction == DMA_MEM_TO_DEV ? "TO DEVICE" : "FROM DEVICE",
			&buf_addr,
			periods, buf_len, period_len);

	अगर (unlikely(!atslave || !buf_len || !period_len)) अणु
		dev_dbg(chan2dev(chan), "prep_dma_cyclic: length is zero!\n");
		वापस शून्य;
	पूर्ण

	was_cyclic = test_and_set_bit(ATC_IS_CYCLIC, &atchan->status);
	अगर (was_cyclic) अणु
		dev_dbg(chan2dev(chan), "prep_dma_cyclic: channel in use!\n");
		वापस शून्य;
	पूर्ण

	अगर (unlikely(!is_slave_direction(direction)))
		जाओ err_out;

	अगर (direction == DMA_MEM_TO_DEV)
		reg_width = convert_buswidth(sconfig->dst_addr_width);
	अन्यथा
		reg_width = convert_buswidth(sconfig->src_addr_width);

	/* Check क्रम too big/unaligned periods and unaligned DMA buffer */
	अगर (atc_dma_cyclic_check_values(reg_width, buf_addr, period_len))
		जाओ err_out;

	/* build cyclic linked list */
	क्रम (i = 0; i < periods; i++) अणु
		काष्ठा at_desc	*desc;

		desc = atc_desc_get(atchan);
		अगर (!desc)
			जाओ err_desc_get;

		अगर (atc_dma_cyclic_fill_desc(chan, desc, i, buf_addr,
					     reg_width, period_len, direction))
			जाओ err_desc_get;

		atc_desc_chain(&first, &prev, desc);
	पूर्ण

	/* lets make a cyclic list */
	prev->lli.dscr = first->txd.phys;

	/* First descriptor of the chain embedds additional inक्रमmation */
	first->txd.cookie = -EBUSY;
	first->total_len = buf_len;

	वापस &first->txd;

err_desc_get:
	dev_err(chan2dev(chan), "not enough descriptors available\n");
	atc_desc_put(atchan, first);
err_out:
	clear_bit(ATC_IS_CYCLIC, &atchan->status);
	वापस शून्य;
पूर्ण

अटल पूर्णांक atc_config(काष्ठा dma_chan *chan,
		      काष्ठा dma_slave_config *sconfig)
अणु
	काष्ठा at_dma_chan	*atchan = to_at_dma_chan(chan);

	dev_vdbg(chan2dev(chan), "%s\n", __func__);

	/* Check अगर it is chan is configured क्रम slave transfers */
	अगर (!chan->निजी)
		वापस -EINVAL;

	स_नकल(&atchan->dma_sconfig, sconfig, माप(*sconfig));

	convert_burst(&atchan->dma_sconfig.src_maxburst);
	convert_burst(&atchan->dma_sconfig.dst_maxburst);

	वापस 0;
पूर्ण

अटल पूर्णांक atc_छोड़ो(काष्ठा dma_chan *chan)
अणु
	काष्ठा at_dma_chan	*atchan = to_at_dma_chan(chan);
	काष्ठा at_dma		*atdma = to_at_dma(chan->device);
	पूर्णांक			chan_id = atchan->chan_common.chan_id;
	अचिन्हित दीर्घ		flags;

	dev_vdbg(chan2dev(chan), "%s\n", __func__);

	spin_lock_irqsave(&atchan->lock, flags);

	dma_ग_लिखोl(atdma, CHER, AT_DMA_SUSP(chan_id));
	set_bit(ATC_IS_PAUSED, &atchan->status);

	spin_unlock_irqrestore(&atchan->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक atc_resume(काष्ठा dma_chan *chan)
अणु
	काष्ठा at_dma_chan	*atchan = to_at_dma_chan(chan);
	काष्ठा at_dma		*atdma = to_at_dma(chan->device);
	पूर्णांक			chan_id = atchan->chan_common.chan_id;
	अचिन्हित दीर्घ		flags;

	dev_vdbg(chan2dev(chan), "%s\n", __func__);

	अगर (!atc_chan_is_छोड़ोd(atchan))
		वापस 0;

	spin_lock_irqsave(&atchan->lock, flags);

	dma_ग_लिखोl(atdma, CHDR, AT_DMA_RES(chan_id));
	clear_bit(ATC_IS_PAUSED, &atchan->status);

	spin_unlock_irqrestore(&atchan->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक atc_terminate_all(काष्ठा dma_chan *chan)
अणु
	काष्ठा at_dma_chan	*atchan = to_at_dma_chan(chan);
	काष्ठा at_dma		*atdma = to_at_dma(chan->device);
	पूर्णांक			chan_id = atchan->chan_common.chan_id;
	काष्ठा at_desc		*desc, *_desc;
	अचिन्हित दीर्घ		flags;

	LIST_HEAD(list);

	dev_vdbg(chan2dev(chan), "%s\n", __func__);

	/*
	 * This is only called when something went wrong अन्यथाwhere, so
	 * we करोn't really care about the data. Just disable the
	 * channel. We still have to poll the channel enable bit due
	 * to AHB/HSB limitations.
	 */
	spin_lock_irqsave(&atchan->lock, flags);

	/* disabling channel: must also हटाओ suspend state */
	dma_ग_लिखोl(atdma, CHDR, AT_DMA_RES(chan_id) | atchan->mask);

	/* confirm that this channel is disabled */
	जबतक (dma_पढ़ोl(atdma, CHSR) & atchan->mask)
		cpu_relax();

	/* active_list entries will end up beक्रमe queued entries */
	list_splice_init(&atchan->queue, &list);
	list_splice_init(&atchan->active_list, &list);

	spin_unlock_irqrestore(&atchan->lock, flags);

	/* Flush all pending and queued descriptors */
	list_क्रम_each_entry_safe(desc, _desc, &list, desc_node)
		atc_chain_complete(atchan, desc);

	clear_bit(ATC_IS_PAUSED, &atchan->status);
	/* अगर channel dedicated to cyclic operations, मुक्त it */
	clear_bit(ATC_IS_CYCLIC, &atchan->status);

	वापस 0;
पूर्ण

/**
 * atc_tx_status - poll क्रम transaction completion
 * @chan: DMA channel
 * @cookie: transaction identअगरier to check status of
 * @txstate: अगर not %शून्य updated with transaction state
 *
 * If @txstate is passed in, upon वापस it reflect the driver
 * पूर्णांकernal state and can be used with dma_async_is_complete() to check
 * the status of multiple cookies without re-checking hardware state.
 */
अटल क्रमागत dma_status
atc_tx_status(काष्ठा dma_chan *chan,
		dma_cookie_t cookie,
		काष्ठा dma_tx_state *txstate)
अणु
	काष्ठा at_dma_chan	*atchan = to_at_dma_chan(chan);
	अचिन्हित दीर्घ		flags;
	क्रमागत dma_status		ret;
	पूर्णांक bytes = 0;

	ret = dma_cookie_status(chan, cookie, txstate);
	अगर (ret == DMA_COMPLETE)
		वापस ret;
	/*
	 * There's no point calculating the residue if there's
	 * no txstate to store the value.
	 */
	अगर (!txstate)
		वापस DMA_ERROR;

	spin_lock_irqsave(&atchan->lock, flags);

	/*  Get number of bytes left in the active transactions */
	bytes = atc_get_bytes_left(chan, cookie);

	spin_unlock_irqrestore(&atchan->lock, flags);

	अगर (unlikely(bytes < 0)) अणु
		dev_vdbg(chan2dev(chan), "get residual bytes error\n");
		वापस DMA_ERROR;
	पूर्ण अन्यथा अणु
		dma_set_residue(txstate, bytes);
	पूर्ण

	dev_vdbg(chan2dev(chan), "tx_status %d: cookie = %d residue = %d\n",
		 ret, cookie, bytes);

	वापस ret;
पूर्ण

/**
 * atc_issue_pending - try to finish work
 * @chan: target DMA channel
 */
अटल व्योम atc_issue_pending(काष्ठा dma_chan *chan)
अणु
	काष्ठा at_dma_chan	*atchan = to_at_dma_chan(chan);

	dev_vdbg(chan2dev(chan), "issue_pending\n");

	/* Not needed क्रम cyclic transfers */
	अगर (atc_chan_is_cyclic(atchan))
		वापस;

	atc_advance_work(atchan);
पूर्ण

/**
 * atc_alloc_chan_resources - allocate resources क्रम DMA channel
 * @chan: allocate descriptor resources क्रम this channel
 *
 * वापस - the number of allocated descriptors
 */
अटल पूर्णांक atc_alloc_chan_resources(काष्ठा dma_chan *chan)
अणु
	काष्ठा at_dma_chan	*atchan = to_at_dma_chan(chan);
	काष्ठा at_dma		*atdma = to_at_dma(chan->device);
	काष्ठा at_desc		*desc;
	काष्ठा at_dma_slave	*atslave;
	पूर्णांक			i;
	u32			cfg;

	dev_vdbg(chan2dev(chan), "alloc_chan_resources\n");

	/* ASSERT:  channel is idle */
	अगर (atc_chan_is_enabled(atchan)) अणु
		dev_dbg(chan2dev(chan), "DMA channel not idle ?\n");
		वापस -EIO;
	पूर्ण

	अगर (!list_empty(&atchan->मुक्त_list)) अणु
		dev_dbg(chan2dev(chan), "can't allocate channel resources (channel not freed from a previous use)\n");
		वापस -EIO;
	पूर्ण

	cfg = ATC_DEFAULT_CFG;

	atslave = chan->निजी;
	अगर (atslave) अणु
		/*
		 * We need controller-specअगरic data to set up slave
		 * transfers.
		 */
		BUG_ON(!atslave->dma_dev || atslave->dma_dev != atdma->dma_common.dev);

		/* अगर cfg configuration specअगरied take it instead of शेष */
		अगर (atslave->cfg)
			cfg = atslave->cfg;
	पूर्ण

	/* Allocate initial pool of descriptors */
	क्रम (i = 0; i < init_nr_desc_per_channel; i++) अणु
		desc = atc_alloc_descriptor(chan, GFP_KERNEL);
		अगर (!desc) अणु
			dev_err(atdma->dma_common.dev,
				"Only %d initial descriptors\n", i);
			अवरोध;
		पूर्ण
		list_add_tail(&desc->desc_node, &atchan->मुक्त_list);
	पूर्ण

	dma_cookie_init(chan);

	/* channel parameters */
	channel_ग_लिखोl(atchan, CFG, cfg);

	dev_dbg(chan2dev(chan),
		"alloc_chan_resources: allocated %d descriptors\n", i);

	वापस i;
पूर्ण

/**
 * atc_मुक्त_chan_resources - मुक्त all channel resources
 * @chan: DMA channel
 */
अटल व्योम atc_मुक्त_chan_resources(काष्ठा dma_chan *chan)
अणु
	काष्ठा at_dma_chan	*atchan = to_at_dma_chan(chan);
	काष्ठा at_dma		*atdma = to_at_dma(chan->device);
	काष्ठा at_desc		*desc, *_desc;
	LIST_HEAD(list);

	/* ASSERT:  channel is idle */
	BUG_ON(!list_empty(&atchan->active_list));
	BUG_ON(!list_empty(&atchan->queue));
	BUG_ON(atc_chan_is_enabled(atchan));

	list_क्रम_each_entry_safe(desc, _desc, &atchan->मुक्त_list, desc_node) अणु
		dev_vdbg(chan2dev(chan), "  freeing descriptor %p\n", desc);
		list_del(&desc->desc_node);
		/* मुक्त link descriptor */
		dma_pool_मुक्त(atdma->dma_desc_pool, desc, desc->txd.phys);
	पूर्ण
	list_splice_init(&atchan->मुक्त_list, &list);
	atchan->status = 0;

	/*
	 * Free atslave allocated in at_dma_xlate()
	 */
	kमुक्त(chan->निजी);
	chan->निजी = शून्य;

	dev_vdbg(chan2dev(chan), "free_chan_resources: done\n");
पूर्ण

#अगर_घोषित CONFIG_OF
अटल bool at_dma_filter(काष्ठा dma_chan *chan, व्योम *slave)
अणु
	काष्ठा at_dma_slave *atslave = slave;

	अगर (atslave->dma_dev == chan->device->dev) अणु
		chan->निजी = atslave;
		वापस true;
	पूर्ण अन्यथा अणु
		वापस false;
	पूर्ण
पूर्ण

अटल काष्ठा dma_chan *at_dma_xlate(काष्ठा of_phandle_args *dma_spec,
				     काष्ठा of_dma *of_dma)
अणु
	काष्ठा dma_chan *chan;
	काष्ठा at_dma_chan *atchan;
	काष्ठा at_dma_slave *atslave;
	dma_cap_mask_t mask;
	अचिन्हित पूर्णांक per_id;
	काष्ठा platक्रमm_device *dmac_pdev;

	अगर (dma_spec->args_count != 2)
		वापस शून्य;

	dmac_pdev = of_find_device_by_node(dma_spec->np);
	अगर (!dmac_pdev)
		वापस शून्य;

	dma_cap_zero(mask);
	dma_cap_set(DMA_SLAVE, mask);

	atslave = kदो_स्मृति(माप(*atslave), GFP_KERNEL);
	अगर (!atslave) अणु
		put_device(&dmac_pdev->dev);
		वापस शून्य;
	पूर्ण

	atslave->cfg = ATC_DST_H2SEL_HW | ATC_SRC_H2SEL_HW;
	/*
	 * We can fill both SRC_PER and DST_PER, one of these fields will be
	 * ignored depending on DMA transfer direction.
	 */
	per_id = dma_spec->args[1] & AT91_DMA_CFG_PER_ID_MASK;
	atslave->cfg |= ATC_DST_PER_MSB(per_id) | ATC_DST_PER(per_id)
		     | ATC_SRC_PER_MSB(per_id) | ATC_SRC_PER(per_id);
	/*
	 * We have to translate the value we get from the device tree since
	 * the half FIFO configuration value had to be 0 to keep backward
	 * compatibility.
	 */
	चयन (dma_spec->args[1] & AT91_DMA_CFG_FIFOCFG_MASK) अणु
	हाल AT91_DMA_CFG_FIFOCFG_ALAP:
		atslave->cfg |= ATC_FIFOCFG_LARGESTBURST;
		अवरोध;
	हाल AT91_DMA_CFG_FIFOCFG_ASAP:
		atslave->cfg |= ATC_FIFOCFG_ENOUGHSPACE;
		अवरोध;
	हाल AT91_DMA_CFG_FIFOCFG_HALF:
	शेष:
		atslave->cfg |= ATC_FIFOCFG_HALFFIFO;
	पूर्ण
	atslave->dma_dev = &dmac_pdev->dev;

	chan = dma_request_channel(mask, at_dma_filter, atslave);
	अगर (!chan) अणु
		put_device(&dmac_pdev->dev);
		kमुक्त(atslave);
		वापस शून्य;
	पूर्ण

	atchan = to_at_dma_chan(chan);
	atchan->per_अगर = dma_spec->args[0] & 0xff;
	atchan->mem_अगर = (dma_spec->args[0] >> 16) & 0xff;

	वापस chan;
पूर्ण
#अन्यथा
अटल काष्ठा dma_chan *at_dma_xlate(काष्ठा of_phandle_args *dma_spec,
				     काष्ठा of_dma *of_dma)
अणु
	वापस शून्य;
पूर्ण
#पूर्ण_अगर

/*--  Module Management  -----------------------------------------------*/

/* cap_mask is a multi-u32 bitfield, fill it with proper C code. */
अटल काष्ठा at_dma_platक्रमm_data at91sam9rl_config = अणु
	.nr_channels = 2,
पूर्ण;
अटल काष्ठा at_dma_platक्रमm_data at91sam9g45_config = अणु
	.nr_channels = 8,
पूर्ण;

#अगर defined(CONFIG_OF)
अटल स्थिर काष्ठा of_device_id aपंचांगel_dma_dt_ids[] = अणु
	अणु
		.compatible = "atmel,at91sam9rl-dma",
		.data = &at91sam9rl_config,
	पूर्ण, अणु
		.compatible = "atmel,at91sam9g45-dma",
		.data = &at91sam9g45_config,
	पूर्ण, अणु
		/* sentinel */
	पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(of, aपंचांगel_dma_dt_ids);
#पूर्ण_अगर

अटल स्थिर काष्ठा platक्रमm_device_id atdma_devtypes[] = अणु
	अणु
		.name = "at91sam9rl_dma",
		.driver_data = (अचिन्हित दीर्घ) &at91sam9rl_config,
	पूर्ण, अणु
		.name = "at91sam9g45_dma",
		.driver_data = (अचिन्हित दीर्घ) &at91sam9g45_config,
	पूर्ण, अणु
		/* sentinel */
	पूर्ण
पूर्ण;

अटल अंतरभूत स्थिर काष्ठा at_dma_platक्रमm_data * __init at_dma_get_driver_data(
						काष्ठा platक्रमm_device *pdev)
अणु
	अगर (pdev->dev.of_node) अणु
		स्थिर काष्ठा of_device_id *match;
		match = of_match_node(aपंचांगel_dma_dt_ids, pdev->dev.of_node);
		अगर (match == शून्य)
			वापस शून्य;
		वापस match->data;
	पूर्ण
	वापस (काष्ठा at_dma_platक्रमm_data *)
			platक्रमm_get_device_id(pdev)->driver_data;
पूर्ण

/**
 * at_dma_off - disable DMA controller
 * @atdma: the Aपंचांगel HDAMC device
 */
अटल व्योम at_dma_off(काष्ठा at_dma *atdma)
अणु
	dma_ग_लिखोl(atdma, EN, 0);

	/* disable all पूर्णांकerrupts */
	dma_ग_लिखोl(atdma, EBCIDR, -1L);

	/* confirm that all channels are disabled */
	जबतक (dma_पढ़ोl(atdma, CHSR) & atdma->all_chan_mask)
		cpu_relax();
पूर्ण

अटल पूर्णांक __init at_dma_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा resource		*io;
	काष्ठा at_dma		*atdma;
	माप_प्रकार			size;
	पूर्णांक			irq;
	पूर्णांक			err;
	पूर्णांक			i;
	स्थिर काष्ठा at_dma_platक्रमm_data *plat_dat;

	/* setup platक्रमm data क्रम each SoC */
	dma_cap_set(DMA_MEMCPY, at91sam9rl_config.cap_mask);
	dma_cap_set(DMA_INTERLEAVE, at91sam9g45_config.cap_mask);
	dma_cap_set(DMA_MEMCPY, at91sam9g45_config.cap_mask);
	dma_cap_set(DMA_MEMSET, at91sam9g45_config.cap_mask);
	dma_cap_set(DMA_MEMSET_SG, at91sam9g45_config.cap_mask);
	dma_cap_set(DMA_PRIVATE, at91sam9g45_config.cap_mask);
	dma_cap_set(DMA_SLAVE, at91sam9g45_config.cap_mask);

	/* get DMA parameters from controller type */
	plat_dat = at_dma_get_driver_data(pdev);
	अगर (!plat_dat)
		वापस -ENODEV;

	io = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!io)
		वापस -EINVAL;

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस irq;

	size = माप(काष्ठा at_dma);
	size += plat_dat->nr_channels * माप(काष्ठा at_dma_chan);
	atdma = kzalloc(size, GFP_KERNEL);
	अगर (!atdma)
		वापस -ENOMEM;

	/* discover transaction capabilities */
	atdma->dma_common.cap_mask = plat_dat->cap_mask;
	atdma->all_chan_mask = (1 << plat_dat->nr_channels) - 1;

	size = resource_size(io);
	अगर (!request_mem_region(io->start, size, pdev->dev.driver->name)) अणु
		err = -EBUSY;
		जाओ err_kमुक्त;
	पूर्ण

	atdma->regs = ioremap(io->start, size);
	अगर (!atdma->regs) अणु
		err = -ENOMEM;
		जाओ err_release_r;
	पूर्ण

	atdma->clk = clk_get(&pdev->dev, "dma_clk");
	अगर (IS_ERR(atdma->clk)) अणु
		err = PTR_ERR(atdma->clk);
		जाओ err_clk;
	पूर्ण
	err = clk_prepare_enable(atdma->clk);
	अगर (err)
		जाओ err_clk_prepare;

	/* क्रमce dma off, just in हाल */
	at_dma_off(atdma);

	err = request_irq(irq, at_dma_पूर्णांकerrupt, 0, "at_hdmac", atdma);
	अगर (err)
		जाओ err_irq;

	platक्रमm_set_drvdata(pdev, atdma);

	/* create a pool of consistent memory blocks क्रम hardware descriptors */
	atdma->dma_desc_pool = dma_pool_create("at_hdmac_desc_pool",
			&pdev->dev, माप(काष्ठा at_desc),
			4 /* word alignment */, 0);
	अगर (!atdma->dma_desc_pool) अणु
		dev_err(&pdev->dev, "No memory for descriptors dma pool\n");
		err = -ENOMEM;
		जाओ err_desc_pool_create;
	पूर्ण

	/* create a pool of consistent memory blocks क्रम स_रखो blocks */
	atdma->स_रखो_pool = dma_pool_create("at_hdmac_memset_pool",
					     &pdev->dev, माप(पूर्णांक), 4, 0);
	अगर (!atdma->स_रखो_pool) अणु
		dev_err(&pdev->dev, "No memory for memset dma pool\n");
		err = -ENOMEM;
		जाओ err_स_रखो_pool_create;
	पूर्ण

	/* clear any pending पूर्णांकerrupt */
	जबतक (dma_पढ़ोl(atdma, EBCISR))
		cpu_relax();

	/* initialize channels related values */
	INIT_LIST_HEAD(&atdma->dma_common.channels);
	क्रम (i = 0; i < plat_dat->nr_channels; i++) अणु
		काष्ठा at_dma_chan	*atchan = &atdma->chan[i];

		atchan->mem_अगर = AT_DMA_MEM_IF;
		atchan->per_अगर = AT_DMA_PER_IF;
		atchan->chan_common.device = &atdma->dma_common;
		dma_cookie_init(&atchan->chan_common);
		list_add_tail(&atchan->chan_common.device_node,
				&atdma->dma_common.channels);

		atchan->ch_regs = atdma->regs + ch_regs(i);
		spin_lock_init(&atchan->lock);
		atchan->mask = 1 << i;

		INIT_LIST_HEAD(&atchan->active_list);
		INIT_LIST_HEAD(&atchan->queue);
		INIT_LIST_HEAD(&atchan->मुक्त_list);

		tasklet_setup(&atchan->tasklet, atc_tasklet);
		atc_enable_chan_irq(atdma, i);
	पूर्ण

	/* set base routines */
	atdma->dma_common.device_alloc_chan_resources = atc_alloc_chan_resources;
	atdma->dma_common.device_मुक्त_chan_resources = atc_मुक्त_chan_resources;
	atdma->dma_common.device_tx_status = atc_tx_status;
	atdma->dma_common.device_issue_pending = atc_issue_pending;
	atdma->dma_common.dev = &pdev->dev;

	/* set prep routines based on capability */
	अगर (dma_has_cap(DMA_INTERLEAVE, atdma->dma_common.cap_mask))
		atdma->dma_common.device_prep_पूर्णांकerleaved_dma = atc_prep_dma_पूर्णांकerleaved;

	अगर (dma_has_cap(DMA_MEMCPY, atdma->dma_common.cap_mask))
		atdma->dma_common.device_prep_dma_स_नकल = atc_prep_dma_स_नकल;

	अगर (dma_has_cap(DMA_MEMSET, atdma->dma_common.cap_mask)) अणु
		atdma->dma_common.device_prep_dma_स_रखो = atc_prep_dma_स_रखो;
		atdma->dma_common.device_prep_dma_स_रखो_sg = atc_prep_dma_स_रखो_sg;
		atdma->dma_common.fill_align = DMAENGINE_ALIGN_4_BYTES;
	पूर्ण

	अगर (dma_has_cap(DMA_SLAVE, atdma->dma_common.cap_mask)) अणु
		atdma->dma_common.device_prep_slave_sg = atc_prep_slave_sg;
		/* controller can करो slave DMA: can trigger cyclic transfers */
		dma_cap_set(DMA_CYCLIC, atdma->dma_common.cap_mask);
		atdma->dma_common.device_prep_dma_cyclic = atc_prep_dma_cyclic;
		atdma->dma_common.device_config = atc_config;
		atdma->dma_common.device_छोड़ो = atc_छोड़ो;
		atdma->dma_common.device_resume = atc_resume;
		atdma->dma_common.device_terminate_all = atc_terminate_all;
		atdma->dma_common.src_addr_widths = ATC_DMA_BUSWIDTHS;
		atdma->dma_common.dst_addr_widths = ATC_DMA_BUSWIDTHS;
		atdma->dma_common.directions = BIT(DMA_DEV_TO_MEM) | BIT(DMA_MEM_TO_DEV);
		atdma->dma_common.residue_granularity = DMA_RESIDUE_GRANULARITY_BURST;
	पूर्ण

	dma_ग_लिखोl(atdma, EN, AT_DMA_ENABLE);

	dev_info(&pdev->dev, "Atmel AHB DMA Controller ( %s%s%s), %d channels\n",
	  dma_has_cap(DMA_MEMCPY, atdma->dma_common.cap_mask) ? "cpy " : "",
	  dma_has_cap(DMA_MEMSET, atdma->dma_common.cap_mask) ? "set " : "",
	  dma_has_cap(DMA_SLAVE, atdma->dma_common.cap_mask)  ? "slave " : "",
	  plat_dat->nr_channels);

	dma_async_device_रेजिस्टर(&atdma->dma_common);

	/*
	 * Do not वापस an error अगर the dmac node is not present in order to
	 * not अवरोध the existing way of requesting channel with
	 * dma_request_channel().
	 */
	अगर (pdev->dev.of_node) अणु
		err = of_dma_controller_रेजिस्टर(pdev->dev.of_node,
						 at_dma_xlate, atdma);
		अगर (err) अणु
			dev_err(&pdev->dev, "could not register of_dma_controller\n");
			जाओ err_of_dma_controller_रेजिस्टर;
		पूर्ण
	पूर्ण

	वापस 0;

err_of_dma_controller_रेजिस्टर:
	dma_async_device_unरेजिस्टर(&atdma->dma_common);
	dma_pool_destroy(atdma->स_रखो_pool);
err_स_रखो_pool_create:
	dma_pool_destroy(atdma->dma_desc_pool);
err_desc_pool_create:
	मुक्त_irq(platक्रमm_get_irq(pdev, 0), atdma);
err_irq:
	clk_disable_unprepare(atdma->clk);
err_clk_prepare:
	clk_put(atdma->clk);
err_clk:
	iounmap(atdma->regs);
	atdma->regs = शून्य;
err_release_r:
	release_mem_region(io->start, size);
err_kमुक्त:
	kमुक्त(atdma);
	वापस err;
पूर्ण

अटल पूर्णांक at_dma_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा at_dma		*atdma = platक्रमm_get_drvdata(pdev);
	काष्ठा dma_chan		*chan, *_chan;
	काष्ठा resource		*io;

	at_dma_off(atdma);
	अगर (pdev->dev.of_node)
		of_dma_controller_मुक्त(pdev->dev.of_node);
	dma_async_device_unरेजिस्टर(&atdma->dma_common);

	dma_pool_destroy(atdma->स_रखो_pool);
	dma_pool_destroy(atdma->dma_desc_pool);
	मुक्त_irq(platक्रमm_get_irq(pdev, 0), atdma);

	list_क्रम_each_entry_safe(chan, _chan, &atdma->dma_common.channels,
			device_node) अणु
		काष्ठा at_dma_chan	*atchan = to_at_dma_chan(chan);

		/* Disable पूर्णांकerrupts */
		atc_disable_chan_irq(atdma, chan->chan_id);

		tasklet_समाप्त(&atchan->tasklet);
		list_del(&chan->device_node);
	पूर्ण

	clk_disable_unprepare(atdma->clk);
	clk_put(atdma->clk);

	iounmap(atdma->regs);
	atdma->regs = शून्य;

	io = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	release_mem_region(io->start, resource_size(io));

	kमुक्त(atdma);

	वापस 0;
पूर्ण

अटल व्योम at_dma_shutकरोwn(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा at_dma	*atdma = platक्रमm_get_drvdata(pdev);

	at_dma_off(platक्रमm_get_drvdata(pdev));
	clk_disable_unprepare(atdma->clk);
पूर्ण

अटल पूर्णांक at_dma_prepare(काष्ठा device *dev)
अणु
	काष्ठा at_dma *atdma = dev_get_drvdata(dev);
	काष्ठा dma_chan *chan, *_chan;

	list_क्रम_each_entry_safe(chan, _chan, &atdma->dma_common.channels,
			device_node) अणु
		काष्ठा at_dma_chan *atchan = to_at_dma_chan(chan);
		/* रुको क्रम transaction completion (except in cyclic हाल) */
		अगर (atc_chan_is_enabled(atchan) && !atc_chan_is_cyclic(atchan))
			वापस -EAGAIN;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम atc_suspend_cyclic(काष्ठा at_dma_chan *atchan)
अणु
	काष्ठा dma_chan	*chan = &atchan->chan_common;

	/* Channel should be छोड़ोd by user
	 * करो it anyway even अगर it is not करोne alपढ़ोy */
	अगर (!atc_chan_is_छोड़ोd(atchan)) अणु
		dev_warn(chan2dev(chan),
		"cyclic channel not paused, should be done by channel user\n");
		atc_छोड़ो(chan);
	पूर्ण

	/* now preserve additional data क्रम cyclic operations */
	/* next descriptor address in the cyclic list */
	atchan->save_dscr = channel_पढ़ोl(atchan, DSCR);

	vdbg_dump_regs(atchan);
पूर्ण

अटल पूर्णांक at_dma_suspend_noirq(काष्ठा device *dev)
अणु
	काष्ठा at_dma *atdma = dev_get_drvdata(dev);
	काष्ठा dma_chan *chan, *_chan;

	/* preserve data */
	list_क्रम_each_entry_safe(chan, _chan, &atdma->dma_common.channels,
			device_node) अणु
		काष्ठा at_dma_chan *atchan = to_at_dma_chan(chan);

		अगर (atc_chan_is_cyclic(atchan))
			atc_suspend_cyclic(atchan);
		atchan->save_cfg = channel_पढ़ोl(atchan, CFG);
	पूर्ण
	atdma->save_imr = dma_पढ़ोl(atdma, EBCIMR);

	/* disable DMA controller */
	at_dma_off(atdma);
	clk_disable_unprepare(atdma->clk);
	वापस 0;
पूर्ण

अटल व्योम atc_resume_cyclic(काष्ठा at_dma_chan *atchan)
अणु
	काष्ठा at_dma	*atdma = to_at_dma(atchan->chan_common.device);

	/* restore channel status क्रम cyclic descriptors list:
	 * next descriptor in the cyclic list at the समय of suspend */
	channel_ग_लिखोl(atchan, SADDR, 0);
	channel_ग_लिखोl(atchan, DADDR, 0);
	channel_ग_लिखोl(atchan, CTRLA, 0);
	channel_ग_लिखोl(atchan, CTRLB, 0);
	channel_ग_लिखोl(atchan, DSCR, atchan->save_dscr);
	dma_ग_लिखोl(atdma, CHER, atchan->mask);

	/* channel छोड़ो status should be हटाओd by channel user
	 * We cannot take the initiative to करो it here */

	vdbg_dump_regs(atchan);
पूर्ण

अटल पूर्णांक at_dma_resume_noirq(काष्ठा device *dev)
अणु
	काष्ठा at_dma *atdma = dev_get_drvdata(dev);
	काष्ठा dma_chan *chan, *_chan;

	/* bring back DMA controller */
	clk_prepare_enable(atdma->clk);
	dma_ग_लिखोl(atdma, EN, AT_DMA_ENABLE);

	/* clear any pending पूर्णांकerrupt */
	जबतक (dma_पढ़ोl(atdma, EBCISR))
		cpu_relax();

	/* restore saved data */
	dma_ग_लिखोl(atdma, EBCIER, atdma->save_imr);
	list_क्रम_each_entry_safe(chan, _chan, &atdma->dma_common.channels,
			device_node) अणु
		काष्ठा at_dma_chan *atchan = to_at_dma_chan(chan);

		channel_ग_लिखोl(atchan, CFG, atchan->save_cfg);
		अगर (atc_chan_is_cyclic(atchan))
			atc_resume_cyclic(atchan);
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops at_dma_dev_pm_ops = अणु
	.prepare = at_dma_prepare,
	.suspend_noirq = at_dma_suspend_noirq,
	.resume_noirq = at_dma_resume_noirq,
पूर्ण;

अटल काष्ठा platक्रमm_driver at_dma_driver = अणु
	.हटाओ		= at_dma_हटाओ,
	.shutकरोwn	= at_dma_shutकरोwn,
	.id_table	= atdma_devtypes,
	.driver = अणु
		.name	= "at_hdmac",
		.pm	= &at_dma_dev_pm_ops,
		.of_match_table	= of_match_ptr(aपंचांगel_dma_dt_ids),
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init at_dma_init(व्योम)
अणु
	वापस platक्रमm_driver_probe(&at_dma_driver, at_dma_probe);
पूर्ण
subsys_initcall(at_dma_init);

अटल व्योम __निकास at_dma_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&at_dma_driver);
पूर्ण
module_निकास(at_dma_निकास);

MODULE_DESCRIPTION("Atmel AHB DMA Controller driver");
MODULE_AUTHOR("Nicolas Ferre <nicolas.ferre@atmel.com>");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:at_hdmac");
