<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * offload engine driver क्रम the Marvell XOR engine
 * Copyright (C) 2007, 2008, Marvell International Ltd.
 */

#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/delay.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/memory.h>
#समावेश <linux/clk.h>
#समावेश <linux/of.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/cpumask.h>
#समावेश <linux/platक्रमm_data/dma-mv_xor.h>

#समावेश "dmaengine.h"
#समावेश "mv_xor.h"

क्रमागत mv_xor_type अणु
	XOR_ORION,
	XOR_ARMADA_38X,
	XOR_ARMADA_37XX,
पूर्ण;

क्रमागत mv_xor_mode अणु
	XOR_MODE_IN_REG,
	XOR_MODE_IN_DESC,
पूर्ण;

अटल व्योम mv_xor_issue_pending(काष्ठा dma_chan *chan);

#घोषणा to_mv_xor_chan(chan)		\
	container_of(chan, काष्ठा mv_xor_chan, dmachan)

#घोषणा to_mv_xor_slot(tx)		\
	container_of(tx, काष्ठा mv_xor_desc_slot, async_tx)

#घोषणा mv_chan_to_devp(chan)           \
	((chan)->dmadev.dev)

अटल व्योम mv_desc_init(काष्ठा mv_xor_desc_slot *desc,
			 dma_addr_t addr, u32 byte_count,
			 क्रमागत dma_ctrl_flags flags)
अणु
	काष्ठा mv_xor_desc *hw_desc = desc->hw_desc;

	hw_desc->status = XOR_DESC_DMA_OWNED;
	hw_desc->phy_next_desc = 0;
	/* Enable end-of-descriptor पूर्णांकerrupts only क्रम DMA_PREP_INTERRUPT */
	hw_desc->desc_command = (flags & DMA_PREP_INTERRUPT) ?
				XOR_DESC_EOD_INT_EN : 0;
	hw_desc->phy_dest_addr = addr;
	hw_desc->byte_count = byte_count;
पूर्ण

अटल व्योम mv_desc_set_mode(काष्ठा mv_xor_desc_slot *desc)
अणु
	काष्ठा mv_xor_desc *hw_desc = desc->hw_desc;

	चयन (desc->type) अणु
	हाल DMA_XOR:
	हाल DMA_INTERRUPT:
		hw_desc->desc_command |= XOR_DESC_OPERATION_XOR;
		अवरोध;
	हाल DMA_MEMCPY:
		hw_desc->desc_command |= XOR_DESC_OPERATION_MEMCPY;
		अवरोध;
	शेष:
		BUG();
		वापस;
	पूर्ण
पूर्ण

अटल व्योम mv_desc_set_next_desc(काष्ठा mv_xor_desc_slot *desc,
				  u32 next_desc_addr)
अणु
	काष्ठा mv_xor_desc *hw_desc = desc->hw_desc;
	BUG_ON(hw_desc->phy_next_desc);
	hw_desc->phy_next_desc = next_desc_addr;
पूर्ण

अटल व्योम mv_desc_set_src_addr(काष्ठा mv_xor_desc_slot *desc,
				 पूर्णांक index, dma_addr_t addr)
अणु
	काष्ठा mv_xor_desc *hw_desc = desc->hw_desc;
	hw_desc->phy_src_addr[mv_phy_src_idx(index)] = addr;
	अगर (desc->type == DMA_XOR)
		hw_desc->desc_command |= (1 << index);
पूर्ण

अटल u32 mv_chan_get_current_desc(काष्ठा mv_xor_chan *chan)
अणु
	वापस पढ़ोl_relaxed(XOR_CURR_DESC(chan));
पूर्ण

अटल व्योम mv_chan_set_next_descriptor(काष्ठा mv_xor_chan *chan,
					u32 next_desc_addr)
अणु
	ग_लिखोl_relaxed(next_desc_addr, XOR_NEXT_DESC(chan));
पूर्ण

अटल व्योम mv_chan_unmask_पूर्णांकerrupts(काष्ठा mv_xor_chan *chan)
अणु
	u32 val = पढ़ोl_relaxed(XOR_INTR_MASK(chan));
	val |= XOR_INTR_MASK_VALUE << (chan->idx * 16);
	ग_लिखोl_relaxed(val, XOR_INTR_MASK(chan));
पूर्ण

अटल u32 mv_chan_get_पूर्णांकr_cause(काष्ठा mv_xor_chan *chan)
अणु
	u32 पूर्णांकr_cause = पढ़ोl_relaxed(XOR_INTR_CAUSE(chan));
	पूर्णांकr_cause = (पूर्णांकr_cause >> (chan->idx * 16)) & 0xFFFF;
	वापस पूर्णांकr_cause;
पूर्ण

अटल व्योम mv_chan_clear_eoc_cause(काष्ठा mv_xor_chan *chan)
अणु
	u32 val;

	val = XOR_INT_END_OF_DESC | XOR_INT_END_OF_CHAIN | XOR_INT_STOPPED;
	val = ~(val << (chan->idx * 16));
	dev_dbg(mv_chan_to_devp(chan), "%s, val 0x%08x\n", __func__, val);
	ग_लिखोl_relaxed(val, XOR_INTR_CAUSE(chan));
पूर्ण

अटल व्योम mv_chan_clear_err_status(काष्ठा mv_xor_chan *chan)
अणु
	u32 val = 0xFFFF0000 >> (chan->idx * 16);
	ग_लिखोl_relaxed(val, XOR_INTR_CAUSE(chan));
पूर्ण

अटल व्योम mv_chan_set_mode(काष्ठा mv_xor_chan *chan,
			     u32 op_mode)
अणु
	u32 config = पढ़ोl_relaxed(XOR_CONFIG(chan));

	config &= ~0x7;
	config |= op_mode;

#अगर defined(__BIG_ENDIAN)
	config |= XOR_DESCRIPTOR_SWAP;
#अन्यथा
	config &= ~XOR_DESCRIPTOR_SWAP;
#पूर्ण_अगर

	ग_लिखोl_relaxed(config, XOR_CONFIG(chan));
पूर्ण

अटल व्योम mv_chan_activate(काष्ठा mv_xor_chan *chan)
अणु
	dev_dbg(mv_chan_to_devp(chan), " activate chan.\n");

	/* ग_लिखोl ensures all descriptors are flushed beक्रमe activation */
	ग_लिखोl(BIT(0), XOR_ACTIVATION(chan));
पूर्ण

अटल अक्षर mv_chan_is_busy(काष्ठा mv_xor_chan *chan)
अणु
	u32 state = पढ़ोl_relaxed(XOR_ACTIVATION(chan));

	state = (state >> 4) & 0x3;

	वापस (state == 1) ? 1 : 0;
पूर्ण

/*
 * mv_chan_start_new_chain - program the engine to operate on new
 * chain headed by sw_desc
 * Caller must hold &mv_chan->lock जबतक calling this function
 */
अटल व्योम mv_chan_start_new_chain(काष्ठा mv_xor_chan *mv_chan,
				    काष्ठा mv_xor_desc_slot *sw_desc)
अणु
	dev_dbg(mv_chan_to_devp(mv_chan), "%s %d: sw_desc %p\n",
		__func__, __LINE__, sw_desc);

	/* set the hardware chain */
	mv_chan_set_next_descriptor(mv_chan, sw_desc->async_tx.phys);

	mv_chan->pending++;
	mv_xor_issue_pending(&mv_chan->dmachan);
पूर्ण

अटल dma_cookie_t
mv_desc_run_tx_complete_actions(काष्ठा mv_xor_desc_slot *desc,
				काष्ठा mv_xor_chan *mv_chan,
				dma_cookie_t cookie)
अणु
	BUG_ON(desc->async_tx.cookie < 0);

	अगर (desc->async_tx.cookie > 0) अणु
		cookie = desc->async_tx.cookie;

		dma_descriptor_unmap(&desc->async_tx);
		/* call the callback (must not sleep or submit new
		 * operations to this channel)
		 */
		dmaengine_desc_get_callback_invoke(&desc->async_tx, शून्य);
	पूर्ण

	/* run dependent operations */
	dma_run_dependencies(&desc->async_tx);

	वापस cookie;
पूर्ण

अटल पूर्णांक
mv_chan_clean_completed_slots(काष्ठा mv_xor_chan *mv_chan)
अणु
	काष्ठा mv_xor_desc_slot *iter, *_iter;

	dev_dbg(mv_chan_to_devp(mv_chan), "%s %d\n", __func__, __LINE__);
	list_क्रम_each_entry_safe(iter, _iter, &mv_chan->completed_slots,
				 node) अणु

		अगर (async_tx_test_ack(&iter->async_tx)) अणु
			list_move_tail(&iter->node, &mv_chan->मुक्त_slots);
			अगर (!list_empty(&iter->sg_tx_list)) अणु
				list_splice_tail_init(&iter->sg_tx_list,
							&mv_chan->मुक्त_slots);
			पूर्ण
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक
mv_desc_clean_slot(काष्ठा mv_xor_desc_slot *desc,
		   काष्ठा mv_xor_chan *mv_chan)
अणु
	dev_dbg(mv_chan_to_devp(mv_chan), "%s %d: desc %p flags %d\n",
		__func__, __LINE__, desc, desc->async_tx.flags);

	/* the client is allowed to attach dependent operations
	 * until 'ack' is set
	 */
	अगर (!async_tx_test_ack(&desc->async_tx)) अणु
		/* move this slot to the completed_slots */
		list_move_tail(&desc->node, &mv_chan->completed_slots);
		अगर (!list_empty(&desc->sg_tx_list)) अणु
			list_splice_tail_init(&desc->sg_tx_list,
					      &mv_chan->completed_slots);
		पूर्ण
	पूर्ण अन्यथा अणु
		list_move_tail(&desc->node, &mv_chan->मुक्त_slots);
		अगर (!list_empty(&desc->sg_tx_list)) अणु
			list_splice_tail_init(&desc->sg_tx_list,
					      &mv_chan->मुक्त_slots);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/* This function must be called with the mv_xor_chan spinlock held */
अटल व्योम mv_chan_slot_cleanup(काष्ठा mv_xor_chan *mv_chan)
अणु
	काष्ठा mv_xor_desc_slot *iter, *_iter;
	dma_cookie_t cookie = 0;
	पूर्णांक busy = mv_chan_is_busy(mv_chan);
	u32 current_desc = mv_chan_get_current_desc(mv_chan);
	पूर्णांक current_cleaned = 0;
	काष्ठा mv_xor_desc *hw_desc;

	dev_dbg(mv_chan_to_devp(mv_chan), "%s %d\n", __func__, __LINE__);
	dev_dbg(mv_chan_to_devp(mv_chan), "current_desc %x\n", current_desc);
	mv_chan_clean_completed_slots(mv_chan);

	/* मुक्त completed slots from the chain starting with
	 * the oldest descriptor
	 */

	list_क्रम_each_entry_safe(iter, _iter, &mv_chan->chain,
				 node) अणु

		/* clean finished descriptors */
		hw_desc = iter->hw_desc;
		अगर (hw_desc->status & XOR_DESC_SUCCESS) अणु
			cookie = mv_desc_run_tx_complete_actions(iter, mv_chan,
								 cookie);

			/* करोne processing desc, clean slot */
			mv_desc_clean_slot(iter, mv_chan);

			/* अवरोध अगर we did cleaned the current */
			अगर (iter->async_tx.phys == current_desc) अणु
				current_cleaned = 1;
				अवरोध;
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (iter->async_tx.phys == current_desc) अणु
				current_cleaned = 0;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर ((busy == 0) && !list_empty(&mv_chan->chain)) अणु
		अगर (current_cleaned) अणु
			/*
			 * current descriptor cleaned and हटाओd, run
			 * from list head
			 */
			iter = list_entry(mv_chan->chain.next,
					  काष्ठा mv_xor_desc_slot,
					  node);
			mv_chan_start_new_chain(mv_chan, iter);
		पूर्ण अन्यथा अणु
			अगर (!list_is_last(&iter->node, &mv_chan->chain)) अणु
				/*
				 * descriptors are still रुकोing after
				 * current, trigger them
				 */
				iter = list_entry(iter->node.next,
						  काष्ठा mv_xor_desc_slot,
						  node);
				mv_chan_start_new_chain(mv_chan, iter);
			पूर्ण अन्यथा अणु
				/*
				 * some descriptors are still रुकोing
				 * to be cleaned
				 */
				tasklet_schedule(&mv_chan->irq_tasklet);
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (cookie > 0)
		mv_chan->dmachan.completed_cookie = cookie;
पूर्ण

अटल व्योम mv_xor_tasklet(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा mv_xor_chan *chan = from_tasklet(chan, t, irq_tasklet);

	spin_lock(&chan->lock);
	mv_chan_slot_cleanup(chan);
	spin_unlock(&chan->lock);
पूर्ण

अटल काष्ठा mv_xor_desc_slot *
mv_chan_alloc_slot(काष्ठा mv_xor_chan *mv_chan)
अणु
	काष्ठा mv_xor_desc_slot *iter;

	spin_lock_bh(&mv_chan->lock);

	अगर (!list_empty(&mv_chan->मुक्त_slots)) अणु
		iter = list_first_entry(&mv_chan->मुक्त_slots,
					काष्ठा mv_xor_desc_slot,
					node);

		list_move_tail(&iter->node, &mv_chan->allocated_slots);

		spin_unlock_bh(&mv_chan->lock);

		/* pre-ack descriptor */
		async_tx_ack(&iter->async_tx);
		iter->async_tx.cookie = -EBUSY;

		वापस iter;

	पूर्ण

	spin_unlock_bh(&mv_chan->lock);

	/* try to मुक्त some slots अगर the allocation fails */
	tasklet_schedule(&mv_chan->irq_tasklet);

	वापस शून्य;
पूर्ण

/************************ DMA engine API functions ****************************/
अटल dma_cookie_t
mv_xor_tx_submit(काष्ठा dma_async_tx_descriptor *tx)
अणु
	काष्ठा mv_xor_desc_slot *sw_desc = to_mv_xor_slot(tx);
	काष्ठा mv_xor_chan *mv_chan = to_mv_xor_chan(tx->chan);
	काष्ठा mv_xor_desc_slot *old_chain_tail;
	dma_cookie_t cookie;
	पूर्णांक new_hw_chain = 1;

	dev_dbg(mv_chan_to_devp(mv_chan),
		"%s sw_desc %p: async_tx %p\n",
		__func__, sw_desc, &sw_desc->async_tx);

	spin_lock_bh(&mv_chan->lock);
	cookie = dma_cookie_assign(tx);

	अगर (list_empty(&mv_chan->chain))
		list_move_tail(&sw_desc->node, &mv_chan->chain);
	अन्यथा अणु
		new_hw_chain = 0;

		old_chain_tail = list_entry(mv_chan->chain.prev,
					    काष्ठा mv_xor_desc_slot,
					    node);
		list_move_tail(&sw_desc->node, &mv_chan->chain);

		dev_dbg(mv_chan_to_devp(mv_chan), "Append to last desc %pa\n",
			&old_chain_tail->async_tx.phys);

		/* fix up the hardware chain */
		mv_desc_set_next_desc(old_chain_tail, sw_desc->async_tx.phys);

		/* अगर the channel is not busy */
		अगर (!mv_chan_is_busy(mv_chan)) अणु
			u32 current_desc = mv_chan_get_current_desc(mv_chan);
			/*
			 * and the curren desc is the end of the chain beक्रमe
			 * the append, then we need to start the channel
			 */
			अगर (current_desc == old_chain_tail->async_tx.phys)
				new_hw_chain = 1;
		पूर्ण
	पूर्ण

	अगर (new_hw_chain)
		mv_chan_start_new_chain(mv_chan, sw_desc);

	spin_unlock_bh(&mv_chan->lock);

	वापस cookie;
पूर्ण

/* वापसs the number of allocated descriptors */
अटल पूर्णांक mv_xor_alloc_chan_resources(काष्ठा dma_chan *chan)
अणु
	व्योम *virt_desc;
	dma_addr_t dma_desc;
	पूर्णांक idx;
	काष्ठा mv_xor_chan *mv_chan = to_mv_xor_chan(chan);
	काष्ठा mv_xor_desc_slot *slot = शून्य;
	पूर्णांक num_descs_in_pool = MV_XOR_POOL_SIZE/MV_XOR_SLOT_SIZE;

	/* Allocate descriptor slots */
	idx = mv_chan->slots_allocated;
	जबतक (idx < num_descs_in_pool) अणु
		slot = kzalloc(माप(*slot), GFP_KERNEL);
		अगर (!slot) अणु
			dev_info(mv_chan_to_devp(mv_chan),
				 "channel only initialized %d descriptor slots",
				 idx);
			अवरोध;
		पूर्ण
		virt_desc = mv_chan->dma_desc_pool_virt;
		slot->hw_desc = virt_desc + idx * MV_XOR_SLOT_SIZE;

		dma_async_tx_descriptor_init(&slot->async_tx, chan);
		slot->async_tx.tx_submit = mv_xor_tx_submit;
		INIT_LIST_HEAD(&slot->node);
		INIT_LIST_HEAD(&slot->sg_tx_list);
		dma_desc = mv_chan->dma_desc_pool;
		slot->async_tx.phys = dma_desc + idx * MV_XOR_SLOT_SIZE;
		slot->idx = idx++;

		spin_lock_bh(&mv_chan->lock);
		mv_chan->slots_allocated = idx;
		list_add_tail(&slot->node, &mv_chan->मुक्त_slots);
		spin_unlock_bh(&mv_chan->lock);
	पूर्ण

	dev_dbg(mv_chan_to_devp(mv_chan),
		"allocated %d descriptor slots\n",
		mv_chan->slots_allocated);

	वापस mv_chan->slots_allocated ? : -ENOMEM;
पूर्ण

/*
 * Check अगर source or destination is an PCIe/IO address (non-SDRAM) and add
 * a new MBus winकरोw अगर necessary. Use a cache क्रम these check so that
 * the MMIO mapped रेजिस्टरs करोn't have to be accessed क्रम this check
 * to speed up this process.
 */
अटल पूर्णांक mv_xor_add_io_win(काष्ठा mv_xor_chan *mv_chan, u32 addr)
अणु
	काष्ठा mv_xor_device *xordev = mv_chan->xordev;
	व्योम __iomem *base = mv_chan->mmr_high_base;
	u32 win_enable;
	u32 size;
	u8 target, attr;
	पूर्णांक ret;
	पूर्णांक i;

	/* Nothing needs to get करोne क्रम the Armada 3700 */
	अगर (xordev->xor_type == XOR_ARMADA_37XX)
		वापस 0;

	/*
	 * Loop over the cached winकरोws to check, अगर the requested area
	 * is alपढ़ोy mapped. If this the हाल, nothing needs to be करोne
	 * and we can वापस.
	 */
	क्रम (i = 0; i < WINDOW_COUNT; i++) अणु
		अगर (addr >= xordev->win_start[i] &&
		    addr <= xordev->win_end[i]) अणु
			/* Winकरोw is alपढ़ोy mapped */
			वापस 0;
		पूर्ण
	पूर्ण

	/*
	 * The winकरोw is not mapped, so we need to create the new mapping
	 */

	/* If no IO winकरोw is found that addr has to be located in SDRAM */
	ret = mvebu_mbus_get_io_win_info(addr, &size, &target, &attr);
	अगर (ret < 0)
		वापस 0;

	/*
	 * Mask the base addr 'addr' according to 'size' पढ़ो back from the
	 * MBus winकरोw. Otherwise we might end up with an address located
	 * somewhere in the middle of this area here.
	 */
	size -= 1;
	addr &= ~size;

	/*
	 * Reading one of both enabled रेजिस्टर is enough, as they are always
	 * programmed to the identical values
	 */
	win_enable = पढ़ोl(base + WINDOW_BAR_ENABLE(0));

	/* Set 'i' to the first मुक्त winकरोw to ग_लिखो the new values to */
	i = ffs(~win_enable) - 1;
	अगर (i >= WINDOW_COUNT)
		वापस -ENOMEM;

	ग_लिखोl((addr & 0xffff0000) | (attr << 8) | target,
	       base + WINDOW_BASE(i));
	ग_लिखोl(size & 0xffff0000, base + WINDOW_SIZE(i));

	/* Fill the caching variables क्रम later use */
	xordev->win_start[i] = addr;
	xordev->win_end[i] = addr + size;

	win_enable |= (1 << i);
	win_enable |= 3 << (16 + (2 * i));
	ग_लिखोl(win_enable, base + WINDOW_BAR_ENABLE(0));
	ग_लिखोl(win_enable, base + WINDOW_BAR_ENABLE(1));

	वापस 0;
पूर्ण

अटल काष्ठा dma_async_tx_descriptor *
mv_xor_prep_dma_xor(काष्ठा dma_chan *chan, dma_addr_t dest, dma_addr_t *src,
		    अचिन्हित पूर्णांक src_cnt, माप_प्रकार len, अचिन्हित दीर्घ flags)
अणु
	काष्ठा mv_xor_chan *mv_chan = to_mv_xor_chan(chan);
	काष्ठा mv_xor_desc_slot *sw_desc;
	पूर्णांक ret;

	अगर (unlikely(len < MV_XOR_MIN_BYTE_COUNT))
		वापस शून्य;

	BUG_ON(len > MV_XOR_MAX_BYTE_COUNT);

	dev_dbg(mv_chan_to_devp(mv_chan),
		"%s src_cnt: %d len: %zu dest %pad flags: %ld\n",
		__func__, src_cnt, len, &dest, flags);

	/* Check अगर a new winकरोw needs to get added क्रम 'dest' */
	ret = mv_xor_add_io_win(mv_chan, dest);
	अगर (ret)
		वापस शून्य;

	sw_desc = mv_chan_alloc_slot(mv_chan);
	अगर (sw_desc) अणु
		sw_desc->type = DMA_XOR;
		sw_desc->async_tx.flags = flags;
		mv_desc_init(sw_desc, dest, len, flags);
		अगर (mv_chan->op_in_desc == XOR_MODE_IN_DESC)
			mv_desc_set_mode(sw_desc);
		जबतक (src_cnt--) अणु
			/* Check अगर a new winकरोw needs to get added क्रम 'src' */
			ret = mv_xor_add_io_win(mv_chan, src[src_cnt]);
			अगर (ret)
				वापस शून्य;
			mv_desc_set_src_addr(sw_desc, src_cnt, src[src_cnt]);
		पूर्ण
	पूर्ण

	dev_dbg(mv_chan_to_devp(mv_chan),
		"%s sw_desc %p async_tx %p \n",
		__func__, sw_desc, &sw_desc->async_tx);
	वापस sw_desc ? &sw_desc->async_tx : शून्य;
पूर्ण

अटल काष्ठा dma_async_tx_descriptor *
mv_xor_prep_dma_स_नकल(काष्ठा dma_chan *chan, dma_addr_t dest, dma_addr_t src,
		माप_प्रकार len, अचिन्हित दीर्घ flags)
अणु
	/*
	 * A MEMCPY operation is identical to an XOR operation with only
	 * a single source address.
	 */
	वापस mv_xor_prep_dma_xor(chan, dest, &src, 1, len, flags);
पूर्ण

अटल काष्ठा dma_async_tx_descriptor *
mv_xor_prep_dma_पूर्णांकerrupt(काष्ठा dma_chan *chan, अचिन्हित दीर्घ flags)
अणु
	काष्ठा mv_xor_chan *mv_chan = to_mv_xor_chan(chan);
	dma_addr_t src, dest;
	माप_प्रकार len;

	src = mv_chan->dummy_src_addr;
	dest = mv_chan->dummy_dst_addr;
	len = MV_XOR_MIN_BYTE_COUNT;

	/*
	 * We implement the DMA_INTERRUPT operation as a minimum sized
	 * XOR operation with a single dummy source address.
	 */
	वापस mv_xor_prep_dma_xor(chan, dest, &src, 1, len, flags);
पूर्ण

अटल व्योम mv_xor_मुक्त_chan_resources(काष्ठा dma_chan *chan)
अणु
	काष्ठा mv_xor_chan *mv_chan = to_mv_xor_chan(chan);
	काष्ठा mv_xor_desc_slot *iter, *_iter;
	पूर्णांक in_use_descs = 0;

	spin_lock_bh(&mv_chan->lock);

	mv_chan_slot_cleanup(mv_chan);

	list_क्रम_each_entry_safe(iter, _iter, &mv_chan->chain,
					node) अणु
		in_use_descs++;
		list_move_tail(&iter->node, &mv_chan->मुक्त_slots);
	पूर्ण
	list_क्रम_each_entry_safe(iter, _iter, &mv_chan->completed_slots,
				 node) अणु
		in_use_descs++;
		list_move_tail(&iter->node, &mv_chan->मुक्त_slots);
	पूर्ण
	list_क्रम_each_entry_safe(iter, _iter, &mv_chan->allocated_slots,
				 node) अणु
		in_use_descs++;
		list_move_tail(&iter->node, &mv_chan->मुक्त_slots);
	पूर्ण
	list_क्रम_each_entry_safe_reverse(
		iter, _iter, &mv_chan->मुक्त_slots, node) अणु
		list_del(&iter->node);
		kमुक्त(iter);
		mv_chan->slots_allocated--;
	पूर्ण

	dev_dbg(mv_chan_to_devp(mv_chan), "%s slots_allocated %d\n",
		__func__, mv_chan->slots_allocated);
	spin_unlock_bh(&mv_chan->lock);

	अगर (in_use_descs)
		dev_err(mv_chan_to_devp(mv_chan),
			"freeing %d in use descriptors!\n", in_use_descs);
पूर्ण

/**
 * mv_xor_status - poll the status of an XOR transaction
 * @chan: XOR channel handle
 * @cookie: XOR transaction identअगरier
 * @txstate: XOR transactions state holder (or शून्य)
 */
अटल क्रमागत dma_status mv_xor_status(काष्ठा dma_chan *chan,
					  dma_cookie_t cookie,
					  काष्ठा dma_tx_state *txstate)
अणु
	काष्ठा mv_xor_chan *mv_chan = to_mv_xor_chan(chan);
	क्रमागत dma_status ret;

	ret = dma_cookie_status(chan, cookie, txstate);
	अगर (ret == DMA_COMPLETE)
		वापस ret;

	spin_lock_bh(&mv_chan->lock);
	mv_chan_slot_cleanup(mv_chan);
	spin_unlock_bh(&mv_chan->lock);

	वापस dma_cookie_status(chan, cookie, txstate);
पूर्ण

अटल व्योम mv_chan_dump_regs(काष्ठा mv_xor_chan *chan)
अणु
	u32 val;

	val = पढ़ोl_relaxed(XOR_CONFIG(chan));
	dev_err(mv_chan_to_devp(chan), "config       0x%08x\n", val);

	val = पढ़ोl_relaxed(XOR_ACTIVATION(chan));
	dev_err(mv_chan_to_devp(chan), "activation   0x%08x\n", val);

	val = पढ़ोl_relaxed(XOR_INTR_CAUSE(chan));
	dev_err(mv_chan_to_devp(chan), "intr cause   0x%08x\n", val);

	val = पढ़ोl_relaxed(XOR_INTR_MASK(chan));
	dev_err(mv_chan_to_devp(chan), "intr mask    0x%08x\n", val);

	val = पढ़ोl_relaxed(XOR_ERROR_CAUSE(chan));
	dev_err(mv_chan_to_devp(chan), "error cause  0x%08x\n", val);

	val = पढ़ोl_relaxed(XOR_ERROR_ADDR(chan));
	dev_err(mv_chan_to_devp(chan), "error addr   0x%08x\n", val);
पूर्ण

अटल व्योम mv_chan_err_पूर्णांकerrupt_handler(काष्ठा mv_xor_chan *chan,
					  u32 पूर्णांकr_cause)
अणु
	अगर (पूर्णांकr_cause & XOR_INT_ERR_DECODE) अणु
		dev_dbg(mv_chan_to_devp(chan), "ignoring address decode error\n");
		वापस;
	पूर्ण

	dev_err(mv_chan_to_devp(chan), "error on chan %d. intr cause 0x%08x\n",
		chan->idx, पूर्णांकr_cause);

	mv_chan_dump_regs(chan);
	WARN_ON(1);
पूर्ण

अटल irqवापस_t mv_xor_पूर्णांकerrupt_handler(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा mv_xor_chan *chan = data;
	u32 पूर्णांकr_cause = mv_chan_get_पूर्णांकr_cause(chan);

	dev_dbg(mv_chan_to_devp(chan), "intr cause %x\n", पूर्णांकr_cause);

	अगर (पूर्णांकr_cause & XOR_INTR_ERRORS)
		mv_chan_err_पूर्णांकerrupt_handler(chan, पूर्णांकr_cause);

	tasklet_schedule(&chan->irq_tasklet);

	mv_chan_clear_eoc_cause(chan);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम mv_xor_issue_pending(काष्ठा dma_chan *chan)
अणु
	काष्ठा mv_xor_chan *mv_chan = to_mv_xor_chan(chan);

	अगर (mv_chan->pending >= MV_XOR_THRESHOLD) अणु
		mv_chan->pending = 0;
		mv_chan_activate(mv_chan);
	पूर्ण
पूर्ण

/*
 * Perक्रमm a transaction to verअगरy the HW works.
 */

अटल पूर्णांक mv_chan_स_नकल_self_test(काष्ठा mv_xor_chan *mv_chan)
अणु
	पूर्णांक i, ret;
	व्योम *src, *dest;
	dma_addr_t src_dma, dest_dma;
	काष्ठा dma_chan *dma_chan;
	dma_cookie_t cookie;
	काष्ठा dma_async_tx_descriptor *tx;
	काष्ठा dmaengine_unmap_data *unmap;
	पूर्णांक err = 0;

	src = kदो_स्मृति(PAGE_SIZE, GFP_KERNEL);
	अगर (!src)
		वापस -ENOMEM;

	dest = kzalloc(PAGE_SIZE, GFP_KERNEL);
	अगर (!dest) अणु
		kमुक्त(src);
		वापस -ENOMEM;
	पूर्ण

	/* Fill in src buffer */
	क्रम (i = 0; i < PAGE_SIZE; i++)
		((u8 *) src)[i] = (u8)i;

	dma_chan = &mv_chan->dmachan;
	अगर (mv_xor_alloc_chan_resources(dma_chan) < 1) अणु
		err = -ENODEV;
		जाओ out;
	पूर्ण

	unmap = dmaengine_get_unmap_data(dma_chan->device->dev, 2, GFP_KERNEL);
	अगर (!unmap) अणु
		err = -ENOMEM;
		जाओ मुक्त_resources;
	पूर्ण

	src_dma = dma_map_page(dma_chan->device->dev, virt_to_page(src),
			       offset_in_page(src), PAGE_SIZE,
			       DMA_TO_DEVICE);
	unmap->addr[0] = src_dma;

	ret = dma_mapping_error(dma_chan->device->dev, src_dma);
	अगर (ret) अणु
		err = -ENOMEM;
		जाओ मुक्त_resources;
	पूर्ण
	unmap->to_cnt = 1;

	dest_dma = dma_map_page(dma_chan->device->dev, virt_to_page(dest),
				offset_in_page(dest), PAGE_SIZE,
				DMA_FROM_DEVICE);
	unmap->addr[1] = dest_dma;

	ret = dma_mapping_error(dma_chan->device->dev, dest_dma);
	अगर (ret) अणु
		err = -ENOMEM;
		जाओ मुक्त_resources;
	पूर्ण
	unmap->from_cnt = 1;
	unmap->len = PAGE_SIZE;

	tx = mv_xor_prep_dma_स_नकल(dma_chan, dest_dma, src_dma,
				    PAGE_SIZE, 0);
	अगर (!tx) अणु
		dev_err(dma_chan->device->dev,
			"Self-test cannot prepare operation, disabling\n");
		err = -ENODEV;
		जाओ मुक्त_resources;
	पूर्ण

	cookie = mv_xor_tx_submit(tx);
	अगर (dma_submit_error(cookie)) अणु
		dev_err(dma_chan->device->dev,
			"Self-test submit error, disabling\n");
		err = -ENODEV;
		जाओ मुक्त_resources;
	पूर्ण

	mv_xor_issue_pending(dma_chan);
	async_tx_ack(tx);
	msleep(1);

	अगर (mv_xor_status(dma_chan, cookie, शून्य) !=
	    DMA_COMPLETE) अणु
		dev_err(dma_chan->device->dev,
			"Self-test copy timed out, disabling\n");
		err = -ENODEV;
		जाओ मुक्त_resources;
	पूर्ण

	dma_sync_single_क्रम_cpu(dma_chan->device->dev, dest_dma,
				PAGE_SIZE, DMA_FROM_DEVICE);
	अगर (स_भेद(src, dest, PAGE_SIZE)) अणु
		dev_err(dma_chan->device->dev,
			"Self-test copy failed compare, disabling\n");
		err = -ENODEV;
		जाओ मुक्त_resources;
	पूर्ण

मुक्त_resources:
	dmaengine_unmap_put(unmap);
	mv_xor_मुक्त_chan_resources(dma_chan);
out:
	kमुक्त(src);
	kमुक्त(dest);
	वापस err;
पूर्ण

#घोषणा MV_XOR_NUM_SRC_TEST 4 /* must be <= 15 */
अटल पूर्णांक
mv_chan_xor_self_test(काष्ठा mv_xor_chan *mv_chan)
अणु
	पूर्णांक i, src_idx, ret;
	काष्ठा page *dest;
	काष्ठा page *xor_srcs[MV_XOR_NUM_SRC_TEST];
	dma_addr_t dma_srcs[MV_XOR_NUM_SRC_TEST];
	dma_addr_t dest_dma;
	काष्ठा dma_async_tx_descriptor *tx;
	काष्ठा dmaengine_unmap_data *unmap;
	काष्ठा dma_chan *dma_chan;
	dma_cookie_t cookie;
	u8 cmp_byte = 0;
	u32 cmp_word;
	पूर्णांक err = 0;
	पूर्णांक src_count = MV_XOR_NUM_SRC_TEST;

	क्रम (src_idx = 0; src_idx < src_count; src_idx++) अणु
		xor_srcs[src_idx] = alloc_page(GFP_KERNEL);
		अगर (!xor_srcs[src_idx]) अणु
			जबतक (src_idx--)
				__मुक्त_page(xor_srcs[src_idx]);
			वापस -ENOMEM;
		पूर्ण
	पूर्ण

	dest = alloc_page(GFP_KERNEL);
	अगर (!dest) अणु
		जबतक (src_idx--)
			__मुक्त_page(xor_srcs[src_idx]);
		वापस -ENOMEM;
	पूर्ण

	/* Fill in src buffers */
	क्रम (src_idx = 0; src_idx < src_count; src_idx++) अणु
		u8 *ptr = page_address(xor_srcs[src_idx]);
		क्रम (i = 0; i < PAGE_SIZE; i++)
			ptr[i] = (1 << src_idx);
	पूर्ण

	क्रम (src_idx = 0; src_idx < src_count; src_idx++)
		cmp_byte ^= (u8) (1 << src_idx);

	cmp_word = (cmp_byte << 24) | (cmp_byte << 16) |
		(cmp_byte << 8) | cmp_byte;

	स_रखो(page_address(dest), 0, PAGE_SIZE);

	dma_chan = &mv_chan->dmachan;
	अगर (mv_xor_alloc_chan_resources(dma_chan) < 1) अणु
		err = -ENODEV;
		जाओ out;
	पूर्ण

	unmap = dmaengine_get_unmap_data(dma_chan->device->dev, src_count + 1,
					 GFP_KERNEL);
	अगर (!unmap) अणु
		err = -ENOMEM;
		जाओ मुक्त_resources;
	पूर्ण

	/* test xor */
	क्रम (i = 0; i < src_count; i++) अणु
		unmap->addr[i] = dma_map_page(dma_chan->device->dev, xor_srcs[i],
					      0, PAGE_SIZE, DMA_TO_DEVICE);
		dma_srcs[i] = unmap->addr[i];
		ret = dma_mapping_error(dma_chan->device->dev, unmap->addr[i]);
		अगर (ret) अणु
			err = -ENOMEM;
			जाओ मुक्त_resources;
		पूर्ण
		unmap->to_cnt++;
	पूर्ण

	unmap->addr[src_count] = dma_map_page(dma_chan->device->dev, dest, 0, PAGE_SIZE,
				      DMA_FROM_DEVICE);
	dest_dma = unmap->addr[src_count];
	ret = dma_mapping_error(dma_chan->device->dev, unmap->addr[src_count]);
	अगर (ret) अणु
		err = -ENOMEM;
		जाओ मुक्त_resources;
	पूर्ण
	unmap->from_cnt = 1;
	unmap->len = PAGE_SIZE;

	tx = mv_xor_prep_dma_xor(dma_chan, dest_dma, dma_srcs,
				 src_count, PAGE_SIZE, 0);
	अगर (!tx) अणु
		dev_err(dma_chan->device->dev,
			"Self-test cannot prepare operation, disabling\n");
		err = -ENODEV;
		जाओ मुक्त_resources;
	पूर्ण

	cookie = mv_xor_tx_submit(tx);
	अगर (dma_submit_error(cookie)) अणु
		dev_err(dma_chan->device->dev,
			"Self-test submit error, disabling\n");
		err = -ENODEV;
		जाओ मुक्त_resources;
	पूर्ण

	mv_xor_issue_pending(dma_chan);
	async_tx_ack(tx);
	msleep(8);

	अगर (mv_xor_status(dma_chan, cookie, शून्य) !=
	    DMA_COMPLETE) अणु
		dev_err(dma_chan->device->dev,
			"Self-test xor timed out, disabling\n");
		err = -ENODEV;
		जाओ मुक्त_resources;
	पूर्ण

	dma_sync_single_क्रम_cpu(dma_chan->device->dev, dest_dma,
				PAGE_SIZE, DMA_FROM_DEVICE);
	क्रम (i = 0; i < (PAGE_SIZE / माप(u32)); i++) अणु
		u32 *ptr = page_address(dest);
		अगर (ptr[i] != cmp_word) अणु
			dev_err(dma_chan->device->dev,
				"Self-test xor failed compare, disabling. index %d, data %x, expected %x\n",
				i, ptr[i], cmp_word);
			err = -ENODEV;
			जाओ मुक्त_resources;
		पूर्ण
	पूर्ण

मुक्त_resources:
	dmaengine_unmap_put(unmap);
	mv_xor_मुक्त_chan_resources(dma_chan);
out:
	src_idx = src_count;
	जबतक (src_idx--)
		__मुक्त_page(xor_srcs[src_idx]);
	__मुक्त_page(dest);
	वापस err;
पूर्ण

अटल पूर्णांक mv_xor_channel_हटाओ(काष्ठा mv_xor_chan *mv_chan)
अणु
	काष्ठा dma_chan *chan, *_chan;
	काष्ठा device *dev = mv_chan->dmadev.dev;

	dma_async_device_unरेजिस्टर(&mv_chan->dmadev);

	dma_मुक्त_coherent(dev, MV_XOR_POOL_SIZE,
			  mv_chan->dma_desc_pool_virt, mv_chan->dma_desc_pool);
	dma_unmap_single(dev, mv_chan->dummy_src_addr,
			 MV_XOR_MIN_BYTE_COUNT, DMA_FROM_DEVICE);
	dma_unmap_single(dev, mv_chan->dummy_dst_addr,
			 MV_XOR_MIN_BYTE_COUNT, DMA_TO_DEVICE);

	list_क्रम_each_entry_safe(chan, _chan, &mv_chan->dmadev.channels,
				 device_node) अणु
		list_del(&chan->device_node);
	पूर्ण

	मुक्त_irq(mv_chan->irq, mv_chan);

	वापस 0;
पूर्ण

अटल काष्ठा mv_xor_chan *
mv_xor_channel_add(काष्ठा mv_xor_device *xordev,
		   काष्ठा platक्रमm_device *pdev,
		   पूर्णांक idx, dma_cap_mask_t cap_mask, पूर्णांक irq)
अणु
	पूर्णांक ret = 0;
	काष्ठा mv_xor_chan *mv_chan;
	काष्ठा dma_device *dma_dev;

	mv_chan = devm_kzalloc(&pdev->dev, माप(*mv_chan), GFP_KERNEL);
	अगर (!mv_chan)
		वापस ERR_PTR(-ENOMEM);

	mv_chan->idx = idx;
	mv_chan->irq = irq;
	अगर (xordev->xor_type == XOR_ORION)
		mv_chan->op_in_desc = XOR_MODE_IN_REG;
	अन्यथा
		mv_chan->op_in_desc = XOR_MODE_IN_DESC;

	dma_dev = &mv_chan->dmadev;
	dma_dev->dev = &pdev->dev;
	mv_chan->xordev = xordev;

	/*
	 * These source and destination dummy buffers are used to implement
	 * a DMA_INTERRUPT operation as a minimum-sized XOR operation.
	 * Hence, we only need to map the buffers at initialization-समय.
	 */
	mv_chan->dummy_src_addr = dma_map_single(dma_dev->dev,
		mv_chan->dummy_src, MV_XOR_MIN_BYTE_COUNT, DMA_FROM_DEVICE);
	mv_chan->dummy_dst_addr = dma_map_single(dma_dev->dev,
		mv_chan->dummy_dst, MV_XOR_MIN_BYTE_COUNT, DMA_TO_DEVICE);

	/* allocate coherent memory क्रम hardware descriptors
	 * note: ग_लिखोcombine gives slightly better perक्रमmance, but
	 * requires that we explicitly flush the ग_लिखोs
	 */
	mv_chan->dma_desc_pool_virt =
	  dma_alloc_wc(&pdev->dev, MV_XOR_POOL_SIZE, &mv_chan->dma_desc_pool,
		       GFP_KERNEL);
	अगर (!mv_chan->dma_desc_pool_virt)
		वापस ERR_PTR(-ENOMEM);

	/* discover transaction capabilites from the platक्रमm data */
	dma_dev->cap_mask = cap_mask;

	INIT_LIST_HEAD(&dma_dev->channels);

	/* set base routines */
	dma_dev->device_alloc_chan_resources = mv_xor_alloc_chan_resources;
	dma_dev->device_मुक्त_chan_resources = mv_xor_मुक्त_chan_resources;
	dma_dev->device_tx_status = mv_xor_status;
	dma_dev->device_issue_pending = mv_xor_issue_pending;

	/* set prep routines based on capability */
	अगर (dma_has_cap(DMA_INTERRUPT, dma_dev->cap_mask))
		dma_dev->device_prep_dma_पूर्णांकerrupt = mv_xor_prep_dma_पूर्णांकerrupt;
	अगर (dma_has_cap(DMA_MEMCPY, dma_dev->cap_mask))
		dma_dev->device_prep_dma_स_नकल = mv_xor_prep_dma_स_नकल;
	अगर (dma_has_cap(DMA_XOR, dma_dev->cap_mask)) अणु
		dma_dev->max_xor = 8;
		dma_dev->device_prep_dma_xor = mv_xor_prep_dma_xor;
	पूर्ण

	mv_chan->mmr_base = xordev->xor_base;
	mv_chan->mmr_high_base = xordev->xor_high_base;
	tasklet_setup(&mv_chan->irq_tasklet, mv_xor_tasklet);

	/* clear errors beक्रमe enabling पूर्णांकerrupts */
	mv_chan_clear_err_status(mv_chan);

	ret = request_irq(mv_chan->irq, mv_xor_पूर्णांकerrupt_handler,
			  0, dev_name(&pdev->dev), mv_chan);
	अगर (ret)
		जाओ err_मुक्त_dma;

	mv_chan_unmask_पूर्णांकerrupts(mv_chan);

	अगर (mv_chan->op_in_desc == XOR_MODE_IN_DESC)
		mv_chan_set_mode(mv_chan, XOR_OPERATION_MODE_IN_DESC);
	अन्यथा
		mv_chan_set_mode(mv_chan, XOR_OPERATION_MODE_XOR);

	spin_lock_init(&mv_chan->lock);
	INIT_LIST_HEAD(&mv_chan->chain);
	INIT_LIST_HEAD(&mv_chan->completed_slots);
	INIT_LIST_HEAD(&mv_chan->मुक्त_slots);
	INIT_LIST_HEAD(&mv_chan->allocated_slots);
	mv_chan->dmachan.device = dma_dev;
	dma_cookie_init(&mv_chan->dmachan);

	list_add_tail(&mv_chan->dmachan.device_node, &dma_dev->channels);

	अगर (dma_has_cap(DMA_MEMCPY, dma_dev->cap_mask)) अणु
		ret = mv_chan_स_नकल_self_test(mv_chan);
		dev_dbg(&pdev->dev, "memcpy self test returned %d\n", ret);
		अगर (ret)
			जाओ err_मुक्त_irq;
	पूर्ण

	अगर (dma_has_cap(DMA_XOR, dma_dev->cap_mask)) अणु
		ret = mv_chan_xor_self_test(mv_chan);
		dev_dbg(&pdev->dev, "xor self test returned %d\n", ret);
		अगर (ret)
			जाओ err_मुक्त_irq;
	पूर्ण

	dev_info(&pdev->dev, "Marvell XOR (%s): ( %s%s%s)\n",
		 mv_chan->op_in_desc ? "Descriptor Mode" : "Registers Mode",
		 dma_has_cap(DMA_XOR, dma_dev->cap_mask) ? "xor " : "",
		 dma_has_cap(DMA_MEMCPY, dma_dev->cap_mask) ? "cpy " : "",
		 dma_has_cap(DMA_INTERRUPT, dma_dev->cap_mask) ? "intr " : "");

	ret = dma_async_device_रेजिस्टर(dma_dev);
	अगर (ret)
		जाओ err_मुक्त_irq;

	वापस mv_chan;

err_मुक्त_irq:
	मुक्त_irq(mv_chan->irq, mv_chan);
err_मुक्त_dma:
	dma_मुक्त_coherent(&pdev->dev, MV_XOR_POOL_SIZE,
			  mv_chan->dma_desc_pool_virt, mv_chan->dma_desc_pool);
	वापस ERR_PTR(ret);
पूर्ण

अटल व्योम
mv_xor_conf_mbus_winकरोws(काष्ठा mv_xor_device *xordev,
			 स्थिर काष्ठा mbus_dram_target_info *dram)
अणु
	व्योम __iomem *base = xordev->xor_high_base;
	u32 win_enable = 0;
	पूर्णांक i;

	क्रम (i = 0; i < 8; i++) अणु
		ग_लिखोl(0, base + WINDOW_BASE(i));
		ग_लिखोl(0, base + WINDOW_SIZE(i));
		अगर (i < 4)
			ग_लिखोl(0, base + WINDOW_REMAP_HIGH(i));
	पूर्ण

	क्रम (i = 0; i < dram->num_cs; i++) अणु
		स्थिर काष्ठा mbus_dram_winकरोw *cs = dram->cs + i;

		ग_लिखोl((cs->base & 0xffff0000) |
		       (cs->mbus_attr << 8) |
		       dram->mbus_dram_target_id, base + WINDOW_BASE(i));
		ग_लिखोl((cs->size - 1) & 0xffff0000, base + WINDOW_SIZE(i));

		/* Fill the caching variables क्रम later use */
		xordev->win_start[i] = cs->base;
		xordev->win_end[i] = cs->base + cs->size - 1;

		win_enable |= (1 << i);
		win_enable |= 3 << (16 + (2 * i));
	पूर्ण

	ग_लिखोl(win_enable, base + WINDOW_BAR_ENABLE(0));
	ग_लिखोl(win_enable, base + WINDOW_BAR_ENABLE(1));
	ग_लिखोl(0, base + WINDOW_OVERRIDE_CTRL(0));
	ग_लिखोl(0, base + WINDOW_OVERRIDE_CTRL(1));
पूर्ण

अटल व्योम
mv_xor_conf_mbus_winकरोws_a3700(काष्ठा mv_xor_device *xordev)
अणु
	व्योम __iomem *base = xordev->xor_high_base;
	u32 win_enable = 0;
	पूर्णांक i;

	क्रम (i = 0; i < 8; i++) अणु
		ग_लिखोl(0, base + WINDOW_BASE(i));
		ग_लिखोl(0, base + WINDOW_SIZE(i));
		अगर (i < 4)
			ग_लिखोl(0, base + WINDOW_REMAP_HIGH(i));
	पूर्ण
	/*
	 * For Armada3700 खोलो शेष 4GB Mbus winकरोw. The dram
	 * related configuration are करोne at AXIS level.
	 */
	ग_लिखोl(0xffff0000, base + WINDOW_SIZE(0));
	win_enable |= 1;
	win_enable |= 3 << 16;

	ग_लिखोl(win_enable, base + WINDOW_BAR_ENABLE(0));
	ग_लिखोl(win_enable, base + WINDOW_BAR_ENABLE(1));
	ग_लिखोl(0, base + WINDOW_OVERRIDE_CTRL(0));
	ग_लिखोl(0, base + WINDOW_OVERRIDE_CTRL(1));
पूर्ण

/*
 * Since this XOR driver is basically used only क्रम RAID5, we करोn't
 * need to care about synchronizing ->suspend with DMA activity,
 * because the DMA engine will naturally be quiet due to the block
 * devices being suspended.
 */
अटल पूर्णांक mv_xor_suspend(काष्ठा platक्रमm_device *pdev, pm_message_t state)
अणु
	काष्ठा mv_xor_device *xordev = platक्रमm_get_drvdata(pdev);
	पूर्णांक i;

	क्रम (i = 0; i < MV_XOR_MAX_CHANNELS; i++) अणु
		काष्ठा mv_xor_chan *mv_chan = xordev->channels[i];

		अगर (!mv_chan)
			जारी;

		mv_chan->saved_config_reg =
			पढ़ोl_relaxed(XOR_CONFIG(mv_chan));
		mv_chan->saved_पूर्णांक_mask_reg =
			पढ़ोl_relaxed(XOR_INTR_MASK(mv_chan));
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mv_xor_resume(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा mv_xor_device *xordev = platक्रमm_get_drvdata(dev);
	स्थिर काष्ठा mbus_dram_target_info *dram;
	पूर्णांक i;

	क्रम (i = 0; i < MV_XOR_MAX_CHANNELS; i++) अणु
		काष्ठा mv_xor_chan *mv_chan = xordev->channels[i];

		अगर (!mv_chan)
			जारी;

		ग_लिखोl_relaxed(mv_chan->saved_config_reg,
			       XOR_CONFIG(mv_chan));
		ग_लिखोl_relaxed(mv_chan->saved_पूर्णांक_mask_reg,
			       XOR_INTR_MASK(mv_chan));
	पूर्ण

	अगर (xordev->xor_type == XOR_ARMADA_37XX) अणु
		mv_xor_conf_mbus_winकरोws_a3700(xordev);
		वापस 0;
	पूर्ण

	dram = mv_mbus_dram_info();
	अगर (dram)
		mv_xor_conf_mbus_winकरोws(xordev, dram);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id mv_xor_dt_ids[] = अणु
	अणु .compatible = "marvell,orion-xor", .data = (व्योम *)XOR_ORION पूर्ण,
	अणु .compatible = "marvell,armada-380-xor", .data = (व्योम *)XOR_ARMADA_38X पूर्ण,
	अणु .compatible = "marvell,armada-3700-xor", .data = (व्योम *)XOR_ARMADA_37XX पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल अचिन्हित पूर्णांक mv_xor_engine_count;

अटल पूर्णांक mv_xor_probe(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा mbus_dram_target_info *dram;
	काष्ठा mv_xor_device *xordev;
	काष्ठा mv_xor_platक्रमm_data *pdata = dev_get_platdata(&pdev->dev);
	काष्ठा resource *res;
	अचिन्हित पूर्णांक max_engines, max_channels;
	पूर्णांक i, ret;

	dev_notice(&pdev->dev, "Marvell shared XOR driver\n");

	xordev = devm_kzalloc(&pdev->dev, माप(*xordev), GFP_KERNEL);
	अगर (!xordev)
		वापस -ENOMEM;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!res)
		वापस -ENODEV;

	xordev->xor_base = devm_ioremap(&pdev->dev, res->start,
					resource_size(res));
	अगर (!xordev->xor_base)
		वापस -EBUSY;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 1);
	अगर (!res)
		वापस -ENODEV;

	xordev->xor_high_base = devm_ioremap(&pdev->dev, res->start,
					     resource_size(res));
	अगर (!xordev->xor_high_base)
		वापस -EBUSY;

	platक्रमm_set_drvdata(pdev, xordev);


	/*
	 * We need to know which type of XOR device we use beक्रमe
	 * setting up. In non-dt हाल it can only be the legacy one.
	 */
	xordev->xor_type = XOR_ORION;
	अगर (pdev->dev.of_node) अणु
		स्थिर काष्ठा of_device_id *of_id =
			of_match_device(mv_xor_dt_ids,
					&pdev->dev);

		xordev->xor_type = (uपूर्णांकptr_t)of_id->data;
	पूर्ण

	/*
	 * (Re-)program MBUS remapping winकरोws अगर we are asked to.
	 */
	अगर (xordev->xor_type == XOR_ARMADA_37XX) अणु
		mv_xor_conf_mbus_winकरोws_a3700(xordev);
	पूर्ण अन्यथा अणु
		dram = mv_mbus_dram_info();
		अगर (dram)
			mv_xor_conf_mbus_winकरोws(xordev, dram);
	पूर्ण

	/* Not all platक्रमms can gate the घड़ी, so it is not
	 * an error अगर the घड़ी करोes not exists.
	 */
	xordev->clk = clk_get(&pdev->dev, शून्य);
	अगर (!IS_ERR(xordev->clk))
		clk_prepare_enable(xordev->clk);

	/*
	 * We करोn't want to have more than one channel per CPU in
	 * order क्रम async_tx to perक्रमm well. So we limit the number
	 * of engines and channels so that we take पूर्णांकo account this
	 * स्थिरraपूर्णांक. Note that we also want to use channels from
	 * separate engines when possible.  For dual-CPU Armada 3700
	 * SoC with single XOR engine allow using its both channels.
	 */
	max_engines = num_present_cpus();
	अगर (xordev->xor_type == XOR_ARMADA_37XX)
		max_channels =	num_present_cpus();
	अन्यथा
		max_channels = min_t(अचिन्हित पूर्णांक,
				     MV_XOR_MAX_CHANNELS,
				     DIV_ROUND_UP(num_present_cpus(), 2));

	अगर (mv_xor_engine_count >= max_engines)
		वापस 0;

	अगर (pdev->dev.of_node) अणु
		काष्ठा device_node *np;
		पूर्णांक i = 0;

		क्रम_each_child_of_node(pdev->dev.of_node, np) अणु
			काष्ठा mv_xor_chan *chan;
			dma_cap_mask_t cap_mask;
			पूर्णांक irq;

			अगर (i >= max_channels)
				जारी;

			dma_cap_zero(cap_mask);
			dma_cap_set(DMA_MEMCPY, cap_mask);
			dma_cap_set(DMA_XOR, cap_mask);
			dma_cap_set(DMA_INTERRUPT, cap_mask);

			irq = irq_of_parse_and_map(np, 0);
			अगर (!irq) अणु
				ret = -ENODEV;
				जाओ err_channel_add;
			पूर्ण

			chan = mv_xor_channel_add(xordev, pdev, i,
						  cap_mask, irq);
			अगर (IS_ERR(chan)) अणु
				ret = PTR_ERR(chan);
				irq_dispose_mapping(irq);
				जाओ err_channel_add;
			पूर्ण

			xordev->channels[i] = chan;
			i++;
		पूर्ण
	पूर्ण अन्यथा अगर (pdata && pdata->channels) अणु
		क्रम (i = 0; i < max_channels; i++) अणु
			काष्ठा mv_xor_channel_data *cd;
			काष्ठा mv_xor_chan *chan;
			पूर्णांक irq;

			cd = &pdata->channels[i];
			irq = platक्रमm_get_irq(pdev, i);
			अगर (irq < 0) अणु
				ret = irq;
				जाओ err_channel_add;
			पूर्ण

			chan = mv_xor_channel_add(xordev, pdev, i,
						  cd->cap_mask, irq);
			अगर (IS_ERR(chan)) अणु
				ret = PTR_ERR(chan);
				जाओ err_channel_add;
			पूर्ण

			xordev->channels[i] = chan;
		पूर्ण
	पूर्ण

	वापस 0;

err_channel_add:
	क्रम (i = 0; i < MV_XOR_MAX_CHANNELS; i++)
		अगर (xordev->channels[i]) अणु
			mv_xor_channel_हटाओ(xordev->channels[i]);
			अगर (pdev->dev.of_node)
				irq_dispose_mapping(xordev->channels[i]->irq);
		पूर्ण

	अगर (!IS_ERR(xordev->clk)) अणु
		clk_disable_unprepare(xordev->clk);
		clk_put(xordev->clk);
	पूर्ण

	वापस ret;
पूर्ण

अटल काष्ठा platक्रमm_driver mv_xor_driver = अणु
	.probe		= mv_xor_probe,
	.suspend        = mv_xor_suspend,
	.resume         = mv_xor_resume,
	.driver		= अणु
		.name	        = MV_XOR_NAME,
		.of_match_table = mv_xor_dt_ids,
	पूर्ण,
पूर्ण;

builtin_platक्रमm_driver(mv_xor_driver);

/*
MODULE_AUTHOR("Saeed Bishara <saeed@marvell.com>");
MODULE_DESCRIPTION("DMA engine driver for Marvell's XOR engine");
MODULE_LICENSE("GPL");
*/
