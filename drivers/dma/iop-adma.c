<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * offload engine driver क्रम the Intel Xscale series of i/o processors
 * Copyright तऊ 2006, Intel Corporation.
 */

/*
 * This driver supports the asynchrounous DMA copy and RAID engines available
 * on the Intel Xscale(R) family of I/O Processors (IOP 32x, 33x, 134x)
 */

#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/delay.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/prefetch.h>
#समावेश <linux/memory.h>
#समावेश <linux/ioport.h>
#समावेश <linux/raid/pq.h>
#समावेश <linux/slab.h>

#समावेश "iop-adma.h"
#समावेश "dmaengine.h"

#घोषणा to_iop_adma_chan(chan) container_of(chan, काष्ठा iop_adma_chan, common)
#घोषणा to_iop_adma_device(dev) \
	container_of(dev, काष्ठा iop_adma_device, common)
#घोषणा tx_to_iop_adma_slot(tx) \
	container_of(tx, काष्ठा iop_adma_desc_slot, async_tx)

/**
 * iop_adma_मुक्त_slots - flags descriptor slots क्रम reuse
 * @slot: Slot to मुक्त
 * Caller must hold &iop_chan->lock जबतक calling this function
 */
अटल व्योम iop_adma_मुक्त_slots(काष्ठा iop_adma_desc_slot *slot)
अणु
	पूर्णांक stride = slot->slots_per_op;

	जबतक (stride--) अणु
		slot->slots_per_op = 0;
		slot = list_entry(slot->slot_node.next,
				काष्ठा iop_adma_desc_slot,
				slot_node);
	पूर्ण
पूर्ण

अटल dma_cookie_t
iop_adma_run_tx_complete_actions(काष्ठा iop_adma_desc_slot *desc,
	काष्ठा iop_adma_chan *iop_chan, dma_cookie_t cookie)
अणु
	काष्ठा dma_async_tx_descriptor *tx = &desc->async_tx;

	BUG_ON(tx->cookie < 0);
	अगर (tx->cookie > 0) अणु
		cookie = tx->cookie;
		tx->cookie = 0;

		/* call the callback (must not sleep or submit new
		 * operations to this channel)
		 */
		dmaengine_desc_get_callback_invoke(tx, शून्य);

		dma_descriptor_unmap(tx);
		अगर (desc->group_head)
			desc->group_head = शून्य;
	पूर्ण

	/* run dependent operations */
	dma_run_dependencies(tx);

	वापस cookie;
पूर्ण

अटल पूर्णांक
iop_adma_clean_slot(काष्ठा iop_adma_desc_slot *desc,
	काष्ठा iop_adma_chan *iop_chan)
अणु
	/* the client is allowed to attach dependent operations
	 * until 'ack' is set
	 */
	अगर (!async_tx_test_ack(&desc->async_tx))
		वापस 0;

	/* leave the last descriptor in the chain
	 * so we can append to it
	 */
	अगर (desc->chain_node.next == &iop_chan->chain)
		वापस 1;

	dev_dbg(iop_chan->device->common.dev,
		"\tfree slot: %d slots_per_op: %d\n",
		desc->idx, desc->slots_per_op);

	list_del(&desc->chain_node);
	iop_adma_मुक्त_slots(desc);

	वापस 0;
पूर्ण

अटल व्योम __iop_adma_slot_cleanup(काष्ठा iop_adma_chan *iop_chan)
अणु
	काष्ठा iop_adma_desc_slot *iter, *_iter, *grp_start = शून्य;
	dma_cookie_t cookie = 0;
	u32 current_desc = iop_chan_get_current_descriptor(iop_chan);
	पूर्णांक busy = iop_chan_is_busy(iop_chan);
	पूर्णांक seen_current = 0, slot_cnt = 0, slots_per_op = 0;

	dev_dbg(iop_chan->device->common.dev, "%s\n", __func__);
	/* मुक्त completed slots from the chain starting with
	 * the oldest descriptor
	 */
	list_क्रम_each_entry_safe(iter, _iter, &iop_chan->chain,
					chain_node) अणु
		pr_debug("\tcookie: %d slot: %d busy: %d "
			"this_desc: %pad next_desc: %#llx ack: %d\n",
			iter->async_tx.cookie, iter->idx, busy,
			&iter->async_tx.phys, (u64)iop_desc_get_next_desc(iter),
			async_tx_test_ack(&iter->async_tx));
		prefetch(_iter);
		prefetch(&_iter->async_tx);

		/* करो not advance past the current descriptor loaded पूर्णांकo the
		 * hardware channel, subsequent descriptors are either in
		 * process or have not been submitted
		 */
		अगर (seen_current)
			अवरोध;

		/* stop the search अगर we reach the current descriptor and the
		 * channel is busy, or अगर it appears that the current descriptor
		 * needs to be re-पढ़ो (i.e. has been appended to)
		 */
		अगर (iter->async_tx.phys == current_desc) अणु
			BUG_ON(seen_current++);
			अगर (busy || iop_desc_get_next_desc(iter))
				अवरोध;
		पूर्ण

		/* detect the start of a group transaction */
		अगर (!slot_cnt && !slots_per_op) अणु
			slot_cnt = iter->slot_cnt;
			slots_per_op = iter->slots_per_op;
			अगर (slot_cnt <= slots_per_op) अणु
				slot_cnt = 0;
				slots_per_op = 0;
			पूर्ण
		पूर्ण

		अगर (slot_cnt) अणु
			pr_debug("\tgroup++\n");
			अगर (!grp_start)
				grp_start = iter;
			slot_cnt -= slots_per_op;
		पूर्ण

		/* all the members of a group are complete */
		अगर (slots_per_op != 0 && slot_cnt == 0) अणु
			काष्ठा iop_adma_desc_slot *grp_iter, *_grp_iter;
			पूर्णांक end_of_chain = 0;
			pr_debug("\tgroup end\n");

			/* collect the total results */
			अगर (grp_start->xor_check_result) अणु
				u32 zero_sum_result = 0;
				slot_cnt = grp_start->slot_cnt;
				grp_iter = grp_start;

				list_क्रम_each_entry_from(grp_iter,
					&iop_chan->chain, chain_node) अणु
					zero_sum_result |=
					    iop_desc_get_zero_result(grp_iter);
					pr_debug("\titer%d result: %d\n",
					    grp_iter->idx, zero_sum_result);
					slot_cnt -= slots_per_op;
					अगर (slot_cnt == 0)
						अवरोध;
				पूर्ण
				pr_debug("\tgrp_start->xor_check_result: %p\n",
					grp_start->xor_check_result);
				*grp_start->xor_check_result = zero_sum_result;
			पूर्ण

			/* clean up the group */
			slot_cnt = grp_start->slot_cnt;
			grp_iter = grp_start;
			list_क्रम_each_entry_safe_from(grp_iter, _grp_iter,
				&iop_chan->chain, chain_node) अणु
				cookie = iop_adma_run_tx_complete_actions(
					grp_iter, iop_chan, cookie);

				slot_cnt -= slots_per_op;
				end_of_chain = iop_adma_clean_slot(grp_iter,
					iop_chan);

				अगर (slot_cnt == 0 || end_of_chain)
					अवरोध;
			पूर्ण

			/* the group should be complete at this poपूर्णांक */
			BUG_ON(slot_cnt);

			slots_per_op = 0;
			grp_start = शून्य;
			अगर (end_of_chain)
				अवरोध;
			अन्यथा
				जारी;
		पूर्ण अन्यथा अगर (slots_per_op) /* रुको क्रम group completion */
			जारी;

		/* ग_लिखो back zero sum results (single descriptor हाल) */
		अगर (iter->xor_check_result && iter->async_tx.cookie)
			*iter->xor_check_result =
				iop_desc_get_zero_result(iter);

		cookie = iop_adma_run_tx_complete_actions(
					iter, iop_chan, cookie);

		अगर (iop_adma_clean_slot(iter, iop_chan))
			अवरोध;
	पूर्ण

	अगर (cookie > 0) अणु
		iop_chan->common.completed_cookie = cookie;
		pr_debug("\tcompleted cookie %d\n", cookie);
	पूर्ण
पूर्ण

अटल व्योम
iop_adma_slot_cleanup(काष्ठा iop_adma_chan *iop_chan)
अणु
	spin_lock_bh(&iop_chan->lock);
	__iop_adma_slot_cleanup(iop_chan);
	spin_unlock_bh(&iop_chan->lock);
पूर्ण

अटल व्योम iop_adma_tasklet(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा iop_adma_chan *iop_chan = from_tasklet(iop_chan, t,
						      irq_tasklet);

	/* lockdep will flag depedency submissions as potentially
	 * recursive locking, this is not the हाल as a dependency
	 * submission will never recurse a channels submit routine.
	 * There are checks in async_tx.c to prevent this.
	 */
	spin_lock_nested(&iop_chan->lock, SINGLE_DEPTH_NESTING);
	__iop_adma_slot_cleanup(iop_chan);
	spin_unlock(&iop_chan->lock);
पूर्ण

अटल काष्ठा iop_adma_desc_slot *
iop_adma_alloc_slots(काष्ठा iop_adma_chan *iop_chan, पूर्णांक num_slots,
			पूर्णांक slots_per_op)
अणु
	काष्ठा iop_adma_desc_slot *iter, *_iter, *alloc_start = शून्य;
	LIST_HEAD(chain);
	पूर्णांक slots_found, retry = 0;

	/* start search from the last allocated descrtiptor
	 * अगर a contiguous allocation can not be found start searching
	 * from the beginning of the list
	 */
retry:
	slots_found = 0;
	अगर (retry == 0)
		iter = iop_chan->last_used;
	अन्यथा
		iter = list_entry(&iop_chan->all_slots,
			काष्ठा iop_adma_desc_slot,
			slot_node);

	list_क्रम_each_entry_safe_जारी(
		iter, _iter, &iop_chan->all_slots, slot_node) अणु
		prefetch(_iter);
		prefetch(&_iter->async_tx);
		अगर (iter->slots_per_op) अणु
			/* give up after finding the first busy slot
			 * on the second pass through the list
			 */
			अगर (retry)
				अवरोध;

			slots_found = 0;
			जारी;
		पूर्ण

		/* start the allocation अगर the slot is correctly aligned */
		अगर (!slots_found++) अणु
			अगर (iop_desc_is_aligned(iter, slots_per_op))
				alloc_start = iter;
			अन्यथा अणु
				slots_found = 0;
				जारी;
			पूर्ण
		पूर्ण

		अगर (slots_found == num_slots) अणु
			काष्ठा iop_adma_desc_slot *alloc_tail = शून्य;
			काष्ठा iop_adma_desc_slot *last_used = शून्य;
			iter = alloc_start;
			जबतक (num_slots) अणु
				पूर्णांक i;
				dev_dbg(iop_chan->device->common.dev,
					"allocated slot: %d "
					"(desc %p phys: %#llx) slots_per_op %d\n",
					iter->idx, iter->hw_desc,
					(u64)iter->async_tx.phys, slots_per_op);

				/* pre-ack all but the last descriptor */
				अगर (num_slots != slots_per_op)
					async_tx_ack(&iter->async_tx);

				list_add_tail(&iter->chain_node, &chain);
				alloc_tail = iter;
				iter->async_tx.cookie = 0;
				iter->slot_cnt = num_slots;
				iter->xor_check_result = शून्य;
				क्रम (i = 0; i < slots_per_op; i++) अणु
					iter->slots_per_op = slots_per_op - i;
					last_used = iter;
					iter = list_entry(iter->slot_node.next,
						काष्ठा iop_adma_desc_slot,
						slot_node);
				पूर्ण
				num_slots -= slots_per_op;
			पूर्ण
			alloc_tail->group_head = alloc_start;
			alloc_tail->async_tx.cookie = -EBUSY;
			list_splice(&chain, &alloc_tail->tx_list);
			iop_chan->last_used = last_used;
			iop_desc_clear_next_desc(alloc_start);
			iop_desc_clear_next_desc(alloc_tail);
			वापस alloc_tail;
		पूर्ण
	पूर्ण
	अगर (!retry++)
		जाओ retry;

	/* perक्रमm direct reclaim अगर the allocation fails */
	__iop_adma_slot_cleanup(iop_chan);

	वापस शून्य;
पूर्ण

अटल व्योम iop_adma_check_threshold(काष्ठा iop_adma_chan *iop_chan)
अणु
	dev_dbg(iop_chan->device->common.dev, "pending: %d\n",
		iop_chan->pending);

	अगर (iop_chan->pending >= IOP_ADMA_THRESHOLD) अणु
		iop_chan->pending = 0;
		iop_chan_append(iop_chan);
	पूर्ण
पूर्ण

अटल dma_cookie_t
iop_adma_tx_submit(काष्ठा dma_async_tx_descriptor *tx)
अणु
	काष्ठा iop_adma_desc_slot *sw_desc = tx_to_iop_adma_slot(tx);
	काष्ठा iop_adma_chan *iop_chan = to_iop_adma_chan(tx->chan);
	काष्ठा iop_adma_desc_slot *grp_start, *old_chain_tail;
	पूर्णांक slot_cnt;
	dma_cookie_t cookie;
	dma_addr_t next_dma;

	grp_start = sw_desc->group_head;
	slot_cnt = grp_start->slot_cnt;

	spin_lock_bh(&iop_chan->lock);
	cookie = dma_cookie_assign(tx);

	old_chain_tail = list_entry(iop_chan->chain.prev,
		काष्ठा iop_adma_desc_slot, chain_node);
	list_splice_init(&sw_desc->tx_list,
			 &old_chain_tail->chain_node);

	/* fix up the hardware chain */
	next_dma = grp_start->async_tx.phys;
	iop_desc_set_next_desc(old_chain_tail, next_dma);
	BUG_ON(iop_desc_get_next_desc(old_chain_tail) != next_dma); /* flush */

	/* check क्रम pre-chained descriptors */
	iop_paranoia(iop_desc_get_next_desc(sw_desc));

	/* increment the pending count by the number of slots
	 * स_नकल operations have a 1:1 (slot:operation) relation
	 * other operations are heavier and will pop the threshold
	 * more often.
	 */
	iop_chan->pending += slot_cnt;
	iop_adma_check_threshold(iop_chan);
	spin_unlock_bh(&iop_chan->lock);

	dev_dbg(iop_chan->device->common.dev, "%s cookie: %d slot: %d\n",
		__func__, sw_desc->async_tx.cookie, sw_desc->idx);

	वापस cookie;
पूर्ण

अटल व्योम iop_chan_start_null_स_नकल(काष्ठा iop_adma_chan *iop_chan);
अटल व्योम iop_chan_start_null_xor(काष्ठा iop_adma_chan *iop_chan);

/**
 * iop_adma_alloc_chan_resources -  वापसs the number of allocated descriptors
 * @chan: allocate descriptor resources क्रम this channel
 *
 * Note: We keep the slots क्रम 1 operation on iop_chan->chain at all बार.  To
 * aव्योम deadlock, via async_xor, num_descs_in_pool must at a minimum be
 * greater than 2x the number slots needed to satisfy a device->max_xor
 * request.
 * */
अटल पूर्णांक iop_adma_alloc_chan_resources(काष्ठा dma_chan *chan)
अणु
	अक्षर *hw_desc;
	dma_addr_t dma_desc;
	पूर्णांक idx;
	काष्ठा iop_adma_chan *iop_chan = to_iop_adma_chan(chan);
	काष्ठा iop_adma_desc_slot *slot = शून्य;
	पूर्णांक init = iop_chan->slots_allocated ? 0 : 1;
	काष्ठा iop_adma_platक्रमm_data *plat_data =
		dev_get_platdata(&iop_chan->device->pdev->dev);
	पूर्णांक num_descs_in_pool = plat_data->pool_size/IOP_ADMA_SLOT_SIZE;

	/* Allocate descriptor slots */
	करो अणु
		idx = iop_chan->slots_allocated;
		अगर (idx == num_descs_in_pool)
			अवरोध;

		slot = kzalloc(माप(*slot), GFP_KERNEL);
		अगर (!slot) अणु
			prपूर्णांकk(KERN_INFO "IOP ADMA Channel only initialized"
				" %d descriptor slots", idx);
			अवरोध;
		पूर्ण
		hw_desc = (अक्षर *) iop_chan->device->dma_desc_pool_virt;
		slot->hw_desc = (व्योम *) &hw_desc[idx * IOP_ADMA_SLOT_SIZE];

		dma_async_tx_descriptor_init(&slot->async_tx, chan);
		slot->async_tx.tx_submit = iop_adma_tx_submit;
		INIT_LIST_HEAD(&slot->tx_list);
		INIT_LIST_HEAD(&slot->chain_node);
		INIT_LIST_HEAD(&slot->slot_node);
		dma_desc = iop_chan->device->dma_desc_pool;
		slot->async_tx.phys = dma_desc + idx * IOP_ADMA_SLOT_SIZE;
		slot->idx = idx;

		spin_lock_bh(&iop_chan->lock);
		iop_chan->slots_allocated++;
		list_add_tail(&slot->slot_node, &iop_chan->all_slots);
		spin_unlock_bh(&iop_chan->lock);
	पूर्ण जबतक (iop_chan->slots_allocated < num_descs_in_pool);

	अगर (idx && !iop_chan->last_used)
		iop_chan->last_used = list_entry(iop_chan->all_slots.next,
					काष्ठा iop_adma_desc_slot,
					slot_node);

	dev_dbg(iop_chan->device->common.dev,
		"allocated %d descriptor slots last_used: %p\n",
		iop_chan->slots_allocated, iop_chan->last_used);

	/* initialize the channel and the chain with a null operation */
	अगर (init) अणु
		अगर (dma_has_cap(DMA_MEMCPY,
			iop_chan->device->common.cap_mask))
			iop_chan_start_null_स_नकल(iop_chan);
		अन्यथा अगर (dma_has_cap(DMA_XOR,
			iop_chan->device->common.cap_mask))
			iop_chan_start_null_xor(iop_chan);
		अन्यथा
			BUG();
	पूर्ण

	वापस (idx > 0) ? idx : -ENOMEM;
पूर्ण

अटल काष्ठा dma_async_tx_descriptor *
iop_adma_prep_dma_पूर्णांकerrupt(काष्ठा dma_chan *chan, अचिन्हित दीर्घ flags)
अणु
	काष्ठा iop_adma_chan *iop_chan = to_iop_adma_chan(chan);
	काष्ठा iop_adma_desc_slot *sw_desc, *grp_start;
	पूर्णांक slot_cnt, slots_per_op;

	dev_dbg(iop_chan->device->common.dev, "%s\n", __func__);

	spin_lock_bh(&iop_chan->lock);
	slot_cnt = iop_chan_पूर्णांकerrupt_slot_count(&slots_per_op, iop_chan);
	sw_desc = iop_adma_alloc_slots(iop_chan, slot_cnt, slots_per_op);
	अगर (sw_desc) अणु
		grp_start = sw_desc->group_head;
		iop_desc_init_पूर्णांकerrupt(grp_start, iop_chan);
		sw_desc->async_tx.flags = flags;
	पूर्ण
	spin_unlock_bh(&iop_chan->lock);

	वापस sw_desc ? &sw_desc->async_tx : शून्य;
पूर्ण

अटल काष्ठा dma_async_tx_descriptor *
iop_adma_prep_dma_स_नकल(काष्ठा dma_chan *chan, dma_addr_t dma_dest,
			 dma_addr_t dma_src, माप_प्रकार len, अचिन्हित दीर्घ flags)
अणु
	काष्ठा iop_adma_chan *iop_chan = to_iop_adma_chan(chan);
	काष्ठा iop_adma_desc_slot *sw_desc, *grp_start;
	पूर्णांक slot_cnt, slots_per_op;

	अगर (unlikely(!len))
		वापस शून्य;
	BUG_ON(len > IOP_ADMA_MAX_BYTE_COUNT);

	dev_dbg(iop_chan->device->common.dev, "%s len: %zu\n",
		__func__, len);

	spin_lock_bh(&iop_chan->lock);
	slot_cnt = iop_chan_स_नकल_slot_count(len, &slots_per_op);
	sw_desc = iop_adma_alloc_slots(iop_chan, slot_cnt, slots_per_op);
	अगर (sw_desc) अणु
		grp_start = sw_desc->group_head;
		iop_desc_init_स_नकल(grp_start, flags);
		iop_desc_set_byte_count(grp_start, iop_chan, len);
		iop_desc_set_dest_addr(grp_start, iop_chan, dma_dest);
		iop_desc_set_स_नकल_src_addr(grp_start, dma_src);
		sw_desc->async_tx.flags = flags;
	पूर्ण
	spin_unlock_bh(&iop_chan->lock);

	वापस sw_desc ? &sw_desc->async_tx : शून्य;
पूर्ण

अटल काष्ठा dma_async_tx_descriptor *
iop_adma_prep_dma_xor(काष्ठा dma_chan *chan, dma_addr_t dma_dest,
		      dma_addr_t *dma_src, अचिन्हित पूर्णांक src_cnt, माप_प्रकार len,
		      अचिन्हित दीर्घ flags)
अणु
	काष्ठा iop_adma_chan *iop_chan = to_iop_adma_chan(chan);
	काष्ठा iop_adma_desc_slot *sw_desc, *grp_start;
	पूर्णांक slot_cnt, slots_per_op;

	अगर (unlikely(!len))
		वापस शून्य;
	BUG_ON(len > IOP_ADMA_XOR_MAX_BYTE_COUNT);

	dev_dbg(iop_chan->device->common.dev,
		"%s src_cnt: %d len: %zu flags: %lx\n",
		__func__, src_cnt, len, flags);

	spin_lock_bh(&iop_chan->lock);
	slot_cnt = iop_chan_xor_slot_count(len, src_cnt, &slots_per_op);
	sw_desc = iop_adma_alloc_slots(iop_chan, slot_cnt, slots_per_op);
	अगर (sw_desc) अणु
		grp_start = sw_desc->group_head;
		iop_desc_init_xor(grp_start, src_cnt, flags);
		iop_desc_set_byte_count(grp_start, iop_chan, len);
		iop_desc_set_dest_addr(grp_start, iop_chan, dma_dest);
		sw_desc->async_tx.flags = flags;
		जबतक (src_cnt--)
			iop_desc_set_xor_src_addr(grp_start, src_cnt,
						  dma_src[src_cnt]);
	पूर्ण
	spin_unlock_bh(&iop_chan->lock);

	वापस sw_desc ? &sw_desc->async_tx : शून्य;
पूर्ण

अटल काष्ठा dma_async_tx_descriptor *
iop_adma_prep_dma_xor_val(काष्ठा dma_chan *chan, dma_addr_t *dma_src,
			  अचिन्हित पूर्णांक src_cnt, माप_प्रकार len, u32 *result,
			  अचिन्हित दीर्घ flags)
अणु
	काष्ठा iop_adma_chan *iop_chan = to_iop_adma_chan(chan);
	काष्ठा iop_adma_desc_slot *sw_desc, *grp_start;
	पूर्णांक slot_cnt, slots_per_op;

	अगर (unlikely(!len))
		वापस शून्य;

	dev_dbg(iop_chan->device->common.dev, "%s src_cnt: %d len: %zu\n",
		__func__, src_cnt, len);

	spin_lock_bh(&iop_chan->lock);
	slot_cnt = iop_chan_zero_sum_slot_count(len, src_cnt, &slots_per_op);
	sw_desc = iop_adma_alloc_slots(iop_chan, slot_cnt, slots_per_op);
	अगर (sw_desc) अणु
		grp_start = sw_desc->group_head;
		iop_desc_init_zero_sum(grp_start, src_cnt, flags);
		iop_desc_set_zero_sum_byte_count(grp_start, len);
		grp_start->xor_check_result = result;
		pr_debug("\t%s: grp_start->xor_check_result: %p\n",
			__func__, grp_start->xor_check_result);
		sw_desc->async_tx.flags = flags;
		जबतक (src_cnt--)
			iop_desc_set_zero_sum_src_addr(grp_start, src_cnt,
						       dma_src[src_cnt]);
	पूर्ण
	spin_unlock_bh(&iop_chan->lock);

	वापस sw_desc ? &sw_desc->async_tx : शून्य;
पूर्ण

अटल काष्ठा dma_async_tx_descriptor *
iop_adma_prep_dma_pq(काष्ठा dma_chan *chan, dma_addr_t *dst, dma_addr_t *src,
		     अचिन्हित पूर्णांक src_cnt, स्थिर अचिन्हित अक्षर *scf, माप_प्रकार len,
		     अचिन्हित दीर्घ flags)
अणु
	काष्ठा iop_adma_chan *iop_chan = to_iop_adma_chan(chan);
	काष्ठा iop_adma_desc_slot *sw_desc, *g;
	पूर्णांक slot_cnt, slots_per_op;
	पूर्णांक जारी_srcs;

	अगर (unlikely(!len))
		वापस शून्य;
	BUG_ON(len > IOP_ADMA_XOR_MAX_BYTE_COUNT);

	dev_dbg(iop_chan->device->common.dev,
		"%s src_cnt: %d len: %zu flags: %lx\n",
		__func__, src_cnt, len, flags);

	अगर (dmaf_p_disabled_जारी(flags))
		जारी_srcs = 1+src_cnt;
	अन्यथा अगर (dmaf_जारी(flags))
		जारी_srcs = 3+src_cnt;
	अन्यथा
		जारी_srcs = 0+src_cnt;

	spin_lock_bh(&iop_chan->lock);
	slot_cnt = iop_chan_pq_slot_count(len, जारी_srcs, &slots_per_op);
	sw_desc = iop_adma_alloc_slots(iop_chan, slot_cnt, slots_per_op);
	अगर (sw_desc) अणु
		पूर्णांक i;

		g = sw_desc->group_head;
		iop_desc_set_byte_count(g, iop_chan, len);

		/* even अगर P is disabled its destination address (bits
		 * [3:0]) must match Q.  It is ok अगर P poपूर्णांकs to an
		 * invalid address, it won't be written.
		 */
		अगर (flags & DMA_PREP_PQ_DISABLE_P)
			dst[0] = dst[1] & 0x7;

		iop_desc_set_pq_addr(g, dst);
		sw_desc->async_tx.flags = flags;
		क्रम (i = 0; i < src_cnt; i++)
			iop_desc_set_pq_src_addr(g, i, src[i], scf[i]);

		/* अगर we are continuing a previous operation factor in
		 * the old p and q values, see the comment क्रम dma_maxpq
		 * in include/linux/dmaengine.h
		 */
		अगर (dmaf_p_disabled_जारी(flags))
			iop_desc_set_pq_src_addr(g, i++, dst[1], 1);
		अन्यथा अगर (dmaf_जारी(flags)) अणु
			iop_desc_set_pq_src_addr(g, i++, dst[0], 0);
			iop_desc_set_pq_src_addr(g, i++, dst[1], 1);
			iop_desc_set_pq_src_addr(g, i++, dst[1], 0);
		पूर्ण
		iop_desc_init_pq(g, i, flags);
	पूर्ण
	spin_unlock_bh(&iop_chan->lock);

	वापस sw_desc ? &sw_desc->async_tx : शून्य;
पूर्ण

अटल काष्ठा dma_async_tx_descriptor *
iop_adma_prep_dma_pq_val(काष्ठा dma_chan *chan, dma_addr_t *pq, dma_addr_t *src,
			 अचिन्हित पूर्णांक src_cnt, स्थिर अचिन्हित अक्षर *scf,
			 माप_प्रकार len, क्रमागत sum_check_flags *pqres,
			 अचिन्हित दीर्घ flags)
अणु
	काष्ठा iop_adma_chan *iop_chan = to_iop_adma_chan(chan);
	काष्ठा iop_adma_desc_slot *sw_desc, *g;
	पूर्णांक slot_cnt, slots_per_op;

	अगर (unlikely(!len))
		वापस शून्य;
	BUG_ON(len > IOP_ADMA_XOR_MAX_BYTE_COUNT);

	dev_dbg(iop_chan->device->common.dev, "%s src_cnt: %d len: %zu\n",
		__func__, src_cnt, len);

	spin_lock_bh(&iop_chan->lock);
	slot_cnt = iop_chan_pq_zero_sum_slot_count(len, src_cnt + 2, &slots_per_op);
	sw_desc = iop_adma_alloc_slots(iop_chan, slot_cnt, slots_per_op);
	अगर (sw_desc) अणु
		/* क्रम validate operations p and q are tagged onto the
		 * end of the source list
		 */
		पूर्णांक pq_idx = src_cnt;

		g = sw_desc->group_head;
		iop_desc_init_pq_zero_sum(g, src_cnt+2, flags);
		iop_desc_set_pq_zero_sum_byte_count(g, len);
		g->pq_check_result = pqres;
		pr_debug("\t%s: g->pq_check_result: %p\n",
			__func__, g->pq_check_result);
		sw_desc->async_tx.flags = flags;
		जबतक (src_cnt--)
			iop_desc_set_pq_zero_sum_src_addr(g, src_cnt,
							  src[src_cnt],
							  scf[src_cnt]);
		iop_desc_set_pq_zero_sum_addr(g, pq_idx, src);
	पूर्ण
	spin_unlock_bh(&iop_chan->lock);

	वापस sw_desc ? &sw_desc->async_tx : शून्य;
पूर्ण

अटल व्योम iop_adma_मुक्त_chan_resources(काष्ठा dma_chan *chan)
अणु
	काष्ठा iop_adma_chan *iop_chan = to_iop_adma_chan(chan);
	काष्ठा iop_adma_desc_slot *iter, *_iter;
	पूर्णांक in_use_descs = 0;

	iop_adma_slot_cleanup(iop_chan);

	spin_lock_bh(&iop_chan->lock);
	list_क्रम_each_entry_safe(iter, _iter, &iop_chan->chain,
					chain_node) अणु
		in_use_descs++;
		list_del(&iter->chain_node);
	पूर्ण
	list_क्रम_each_entry_safe_reverse(
		iter, _iter, &iop_chan->all_slots, slot_node) अणु
		list_del(&iter->slot_node);
		kमुक्त(iter);
		iop_chan->slots_allocated--;
	पूर्ण
	iop_chan->last_used = शून्य;

	dev_dbg(iop_chan->device->common.dev, "%s slots_allocated %d\n",
		__func__, iop_chan->slots_allocated);
	spin_unlock_bh(&iop_chan->lock);

	/* one is ok since we left it on there on purpose */
	अगर (in_use_descs > 1)
		prपूर्णांकk(KERN_ERR "IOP: Freeing %d in use descriptors!\n",
			in_use_descs - 1);
पूर्ण

/**
 * iop_adma_status - poll the status of an ADMA transaction
 * @chan: ADMA channel handle
 * @cookie: ADMA transaction identअगरier
 * @txstate: a holder क्रम the current state of the channel or शून्य
 */
अटल क्रमागत dma_status iop_adma_status(काष्ठा dma_chan *chan,
					dma_cookie_t cookie,
					काष्ठा dma_tx_state *txstate)
अणु
	काष्ठा iop_adma_chan *iop_chan = to_iop_adma_chan(chan);
	पूर्णांक ret;

	ret = dma_cookie_status(chan, cookie, txstate);
	अगर (ret == DMA_COMPLETE)
		वापस ret;

	iop_adma_slot_cleanup(iop_chan);

	वापस dma_cookie_status(chan, cookie, txstate);
पूर्ण

अटल irqवापस_t iop_adma_eot_handler(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा iop_adma_chan *chan = data;

	dev_dbg(chan->device->common.dev, "%s\n", __func__);

	tasklet_schedule(&chan->irq_tasklet);

	iop_adma_device_clear_eot_status(chan);

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t iop_adma_eoc_handler(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा iop_adma_chan *chan = data;

	dev_dbg(chan->device->common.dev, "%s\n", __func__);

	tasklet_schedule(&chan->irq_tasklet);

	iop_adma_device_clear_eoc_status(chan);

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t iop_adma_err_handler(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा iop_adma_chan *chan = data;
	अचिन्हित दीर्घ status = iop_chan_get_status(chan);

	dev_err(chan->device->common.dev,
		"error ( %s%s%s%s%s%s%s)\n",
		iop_is_err_पूर्णांक_parity(status, chan) ? "int_parity " : "",
		iop_is_err_mcu_पात(status, chan) ? "mcu_abort " : "",
		iop_is_err_पूर्णांक_tपात(status, chan) ? "int_tabort " : "",
		iop_is_err_पूर्णांक_mपात(status, chan) ? "int_mabort " : "",
		iop_is_err_pci_tपात(status, chan) ? "pci_tabort " : "",
		iop_is_err_pci_mपात(status, chan) ? "pci_mabort " : "",
		iop_is_err_split_tx(status, chan) ? "split_tx " : "");

	iop_adma_device_clear_err_status(chan);

	BUG();

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम iop_adma_issue_pending(काष्ठा dma_chan *chan)
अणु
	काष्ठा iop_adma_chan *iop_chan = to_iop_adma_chan(chan);

	अगर (iop_chan->pending) अणु
		iop_chan->pending = 0;
		iop_chan_append(iop_chan);
	पूर्ण
पूर्ण

/*
 * Perक्रमm a transaction to verअगरy the HW works.
 */
#घोषणा IOP_ADMA_TEST_SIZE 2000

अटल पूर्णांक iop_adma_स_नकल_self_test(काष्ठा iop_adma_device *device)
अणु
	पूर्णांक i;
	व्योम *src, *dest;
	dma_addr_t src_dma, dest_dma;
	काष्ठा dma_chan *dma_chan;
	dma_cookie_t cookie;
	काष्ठा dma_async_tx_descriptor *tx;
	पूर्णांक err = 0;
	काष्ठा iop_adma_chan *iop_chan;

	dev_dbg(device->common.dev, "%s\n", __func__);

	src = kदो_स्मृति(IOP_ADMA_TEST_SIZE, GFP_KERNEL);
	अगर (!src)
		वापस -ENOMEM;
	dest = kzalloc(IOP_ADMA_TEST_SIZE, GFP_KERNEL);
	अगर (!dest) अणु
		kमुक्त(src);
		वापस -ENOMEM;
	पूर्ण

	/* Fill in src buffer */
	क्रम (i = 0; i < IOP_ADMA_TEST_SIZE; i++)
		((u8 *) src)[i] = (u8)i;

	/* Start copy, using first DMA channel */
	dma_chan = container_of(device->common.channels.next,
				काष्ठा dma_chan,
				device_node);
	अगर (iop_adma_alloc_chan_resources(dma_chan) < 1) अणु
		err = -ENODEV;
		जाओ out;
	पूर्ण

	dest_dma = dma_map_single(dma_chan->device->dev, dest,
				IOP_ADMA_TEST_SIZE, DMA_FROM_DEVICE);
	src_dma = dma_map_single(dma_chan->device->dev, src,
				IOP_ADMA_TEST_SIZE, DMA_TO_DEVICE);
	tx = iop_adma_prep_dma_स_नकल(dma_chan, dest_dma, src_dma,
				      IOP_ADMA_TEST_SIZE,
				      DMA_PREP_INTERRUPT | DMA_CTRL_ACK);

	cookie = iop_adma_tx_submit(tx);
	iop_adma_issue_pending(dma_chan);
	msleep(1);

	अगर (iop_adma_status(dma_chan, cookie, शून्य) !=
			DMA_COMPLETE) अणु
		dev_err(dma_chan->device->dev,
			"Self-test copy timed out, disabling\n");
		err = -ENODEV;
		जाओ मुक्त_resources;
	पूर्ण

	iop_chan = to_iop_adma_chan(dma_chan);
	dma_sync_single_क्रम_cpu(&iop_chan->device->pdev->dev, dest_dma,
		IOP_ADMA_TEST_SIZE, DMA_FROM_DEVICE);
	अगर (स_भेद(src, dest, IOP_ADMA_TEST_SIZE)) अणु
		dev_err(dma_chan->device->dev,
			"Self-test copy failed compare, disabling\n");
		err = -ENODEV;
		जाओ मुक्त_resources;
	पूर्ण

मुक्त_resources:
	iop_adma_मुक्त_chan_resources(dma_chan);
out:
	kमुक्त(src);
	kमुक्त(dest);
	वापस err;
पूर्ण

#घोषणा IOP_ADMA_NUM_SRC_TEST 4 /* must be <= 15 */
अटल पूर्णांक
iop_adma_xor_val_self_test(काष्ठा iop_adma_device *device)
अणु
	पूर्णांक i, src_idx;
	काष्ठा page *dest;
	काष्ठा page *xor_srcs[IOP_ADMA_NUM_SRC_TEST];
	काष्ठा page *zero_sum_srcs[IOP_ADMA_NUM_SRC_TEST + 1];
	dma_addr_t dma_srcs[IOP_ADMA_NUM_SRC_TEST + 1];
	dma_addr_t dest_dma;
	काष्ठा dma_async_tx_descriptor *tx;
	काष्ठा dma_chan *dma_chan;
	dma_cookie_t cookie;
	u8 cmp_byte = 0;
	u32 cmp_word;
	u32 zero_sum_result;
	पूर्णांक err = 0;
	काष्ठा iop_adma_chan *iop_chan;

	dev_dbg(device->common.dev, "%s\n", __func__);

	क्रम (src_idx = 0; src_idx < IOP_ADMA_NUM_SRC_TEST; src_idx++) अणु
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
	क्रम (src_idx = 0; src_idx < IOP_ADMA_NUM_SRC_TEST; src_idx++) अणु
		u8 *ptr = page_address(xor_srcs[src_idx]);
		क्रम (i = 0; i < PAGE_SIZE; i++)
			ptr[i] = (1 << src_idx);
	पूर्ण

	क्रम (src_idx = 0; src_idx < IOP_ADMA_NUM_SRC_TEST; src_idx++)
		cmp_byte ^= (u8) (1 << src_idx);

	cmp_word = (cmp_byte << 24) | (cmp_byte << 16) |
			(cmp_byte << 8) | cmp_byte;

	स_रखो(page_address(dest), 0, PAGE_SIZE);

	dma_chan = container_of(device->common.channels.next,
				काष्ठा dma_chan,
				device_node);
	अगर (iop_adma_alloc_chan_resources(dma_chan) < 1) अणु
		err = -ENODEV;
		जाओ out;
	पूर्ण

	/* test xor */
	dest_dma = dma_map_page(dma_chan->device->dev, dest, 0,
				PAGE_SIZE, DMA_FROM_DEVICE);
	क्रम (i = 0; i < IOP_ADMA_NUM_SRC_TEST; i++)
		dma_srcs[i] = dma_map_page(dma_chan->device->dev, xor_srcs[i],
					   0, PAGE_SIZE, DMA_TO_DEVICE);
	tx = iop_adma_prep_dma_xor(dma_chan, dest_dma, dma_srcs,
				   IOP_ADMA_NUM_SRC_TEST, PAGE_SIZE,
				   DMA_PREP_INTERRUPT | DMA_CTRL_ACK);

	cookie = iop_adma_tx_submit(tx);
	iop_adma_issue_pending(dma_chan);
	msleep(8);

	अगर (iop_adma_status(dma_chan, cookie, शून्य) !=
		DMA_COMPLETE) अणु
		dev_err(dma_chan->device->dev,
			"Self-test xor timed out, disabling\n");
		err = -ENODEV;
		जाओ मुक्त_resources;
	पूर्ण

	iop_chan = to_iop_adma_chan(dma_chan);
	dma_sync_single_क्रम_cpu(&iop_chan->device->pdev->dev, dest_dma,
		PAGE_SIZE, DMA_FROM_DEVICE);
	क्रम (i = 0; i < (PAGE_SIZE / माप(u32)); i++) अणु
		u32 *ptr = page_address(dest);
		अगर (ptr[i] != cmp_word) अणु
			dev_err(dma_chan->device->dev,
				"Self-test xor failed compare, disabling\n");
			err = -ENODEV;
			जाओ मुक्त_resources;
		पूर्ण
	पूर्ण
	dma_sync_single_क्रम_device(&iop_chan->device->pdev->dev, dest_dma,
		PAGE_SIZE, DMA_TO_DEVICE);

	/* skip zero sum अगर the capability is not present */
	अगर (!dma_has_cap(DMA_XOR_VAL, dma_chan->device->cap_mask))
		जाओ मुक्त_resources;

	/* zero sum the sources with the destपूर्णांकation page */
	क्रम (i = 0; i < IOP_ADMA_NUM_SRC_TEST; i++)
		zero_sum_srcs[i] = xor_srcs[i];
	zero_sum_srcs[i] = dest;

	zero_sum_result = 1;

	क्रम (i = 0; i < IOP_ADMA_NUM_SRC_TEST + 1; i++)
		dma_srcs[i] = dma_map_page(dma_chan->device->dev,
					   zero_sum_srcs[i], 0, PAGE_SIZE,
					   DMA_TO_DEVICE);
	tx = iop_adma_prep_dma_xor_val(dma_chan, dma_srcs,
				       IOP_ADMA_NUM_SRC_TEST + 1, PAGE_SIZE,
				       &zero_sum_result,
				       DMA_PREP_INTERRUPT | DMA_CTRL_ACK);

	cookie = iop_adma_tx_submit(tx);
	iop_adma_issue_pending(dma_chan);
	msleep(8);

	अगर (iop_adma_status(dma_chan, cookie, शून्य) != DMA_COMPLETE) अणु
		dev_err(dma_chan->device->dev,
			"Self-test zero sum timed out, disabling\n");
		err = -ENODEV;
		जाओ मुक्त_resources;
	पूर्ण

	अगर (zero_sum_result != 0) अणु
		dev_err(dma_chan->device->dev,
			"Self-test zero sum failed compare, disabling\n");
		err = -ENODEV;
		जाओ मुक्त_resources;
	पूर्ण

	/* test क्रम non-zero parity sum */
	zero_sum_result = 0;
	क्रम (i = 0; i < IOP_ADMA_NUM_SRC_TEST + 1; i++)
		dma_srcs[i] = dma_map_page(dma_chan->device->dev,
					   zero_sum_srcs[i], 0, PAGE_SIZE,
					   DMA_TO_DEVICE);
	tx = iop_adma_prep_dma_xor_val(dma_chan, dma_srcs,
				       IOP_ADMA_NUM_SRC_TEST + 1, PAGE_SIZE,
				       &zero_sum_result,
				       DMA_PREP_INTERRUPT | DMA_CTRL_ACK);

	cookie = iop_adma_tx_submit(tx);
	iop_adma_issue_pending(dma_chan);
	msleep(8);

	अगर (iop_adma_status(dma_chan, cookie, शून्य) != DMA_COMPLETE) अणु
		dev_err(dma_chan->device->dev,
			"Self-test non-zero sum timed out, disabling\n");
		err = -ENODEV;
		जाओ मुक्त_resources;
	पूर्ण

	अगर (zero_sum_result != 1) अणु
		dev_err(dma_chan->device->dev,
			"Self-test non-zero sum failed compare, disabling\n");
		err = -ENODEV;
		जाओ मुक्त_resources;
	पूर्ण

मुक्त_resources:
	iop_adma_मुक्त_chan_resources(dma_chan);
out:
	src_idx = IOP_ADMA_NUM_SRC_TEST;
	जबतक (src_idx--)
		__मुक्त_page(xor_srcs[src_idx]);
	__मुक्त_page(dest);
	वापस err;
पूर्ण

#अगर_घोषित CONFIG_RAID6_PQ
अटल पूर्णांक
iop_adma_pq_zero_sum_self_test(काष्ठा iop_adma_device *device)
अणु
	/* combined sources, software pq results, and extra hw pq results */
	काष्ठा page *pq[IOP_ADMA_NUM_SRC_TEST+2+2];
	/* ptr to the extra hw pq buffers defined above */
	काष्ठा page **pq_hw = &pq[IOP_ADMA_NUM_SRC_TEST+2];
	/* address conversion buffers (dma_map / page_address) */
	व्योम *pq_sw[IOP_ADMA_NUM_SRC_TEST+2];
	dma_addr_t pq_src[IOP_ADMA_NUM_SRC_TEST+2];
	dma_addr_t *pq_dest = &pq_src[IOP_ADMA_NUM_SRC_TEST];

	पूर्णांक i;
	काष्ठा dma_async_tx_descriptor *tx;
	काष्ठा dma_chan *dma_chan;
	dma_cookie_t cookie;
	u32 zero_sum_result;
	पूर्णांक err = 0;
	काष्ठा device *dev;

	dev_dbg(device->common.dev, "%s\n", __func__);

	क्रम (i = 0; i < ARRAY_SIZE(pq); i++) अणु
		pq[i] = alloc_page(GFP_KERNEL);
		अगर (!pq[i]) अणु
			जबतक (i--)
				__मुक्त_page(pq[i]);
			वापस -ENOMEM;
		पूर्ण
	पूर्ण

	/* Fill in src buffers */
	क्रम (i = 0; i < IOP_ADMA_NUM_SRC_TEST; i++) अणु
		pq_sw[i] = page_address(pq[i]);
		स_रखो(pq_sw[i], 0x11111111 * (1<<i), PAGE_SIZE);
	पूर्ण
	pq_sw[i] = page_address(pq[i]);
	pq_sw[i+1] = page_address(pq[i+1]);

	dma_chan = container_of(device->common.channels.next,
				काष्ठा dma_chan,
				device_node);
	अगर (iop_adma_alloc_chan_resources(dma_chan) < 1) अणु
		err = -ENODEV;
		जाओ out;
	पूर्ण

	dev = dma_chan->device->dev;

	/* initialize the dests */
	स_रखो(page_address(pq_hw[0]), 0 , PAGE_SIZE);
	स_रखो(page_address(pq_hw[1]), 0 , PAGE_SIZE);

	/* test pq */
	pq_dest[0] = dma_map_page(dev, pq_hw[0], 0, PAGE_SIZE, DMA_FROM_DEVICE);
	pq_dest[1] = dma_map_page(dev, pq_hw[1], 0, PAGE_SIZE, DMA_FROM_DEVICE);
	क्रम (i = 0; i < IOP_ADMA_NUM_SRC_TEST; i++)
		pq_src[i] = dma_map_page(dev, pq[i], 0, PAGE_SIZE,
					 DMA_TO_DEVICE);

	tx = iop_adma_prep_dma_pq(dma_chan, pq_dest, pq_src,
				  IOP_ADMA_NUM_SRC_TEST, (u8 *)raid6_gfexp,
				  PAGE_SIZE,
				  DMA_PREP_INTERRUPT |
				  DMA_CTRL_ACK);

	cookie = iop_adma_tx_submit(tx);
	iop_adma_issue_pending(dma_chan);
	msleep(8);

	अगर (iop_adma_status(dma_chan, cookie, शून्य) !=
		DMA_COMPLETE) अणु
		dev_err(dev, "Self-test pq timed out, disabling\n");
		err = -ENODEV;
		जाओ मुक्त_resources;
	पूर्ण

	raid6_call.gen_syndrome(IOP_ADMA_NUM_SRC_TEST+2, PAGE_SIZE, pq_sw);

	अगर (स_भेद(pq_sw[IOP_ADMA_NUM_SRC_TEST],
		   page_address(pq_hw[0]), PAGE_SIZE) != 0) अणु
		dev_err(dev, "Self-test p failed compare, disabling\n");
		err = -ENODEV;
		जाओ मुक्त_resources;
	पूर्ण
	अगर (स_भेद(pq_sw[IOP_ADMA_NUM_SRC_TEST+1],
		   page_address(pq_hw[1]), PAGE_SIZE) != 0) अणु
		dev_err(dev, "Self-test q failed compare, disabling\n");
		err = -ENODEV;
		जाओ मुक्त_resources;
	पूर्ण

	/* test correct zero sum using the software generated pq values */
	क्रम (i = 0; i < IOP_ADMA_NUM_SRC_TEST + 2; i++)
		pq_src[i] = dma_map_page(dev, pq[i], 0, PAGE_SIZE,
					 DMA_TO_DEVICE);

	zero_sum_result = ~0;
	tx = iop_adma_prep_dma_pq_val(dma_chan, &pq_src[IOP_ADMA_NUM_SRC_TEST],
				      pq_src, IOP_ADMA_NUM_SRC_TEST,
				      raid6_gfexp, PAGE_SIZE, &zero_sum_result,
				      DMA_PREP_INTERRUPT|DMA_CTRL_ACK);

	cookie = iop_adma_tx_submit(tx);
	iop_adma_issue_pending(dma_chan);
	msleep(8);

	अगर (iop_adma_status(dma_chan, cookie, शून्य) !=
		DMA_COMPLETE) अणु
		dev_err(dev, "Self-test pq-zero-sum timed out, disabling\n");
		err = -ENODEV;
		जाओ मुक्त_resources;
	पूर्ण

	अगर (zero_sum_result != 0) अणु
		dev_err(dev, "Self-test pq-zero-sum failed to validate: %x\n",
			zero_sum_result);
		err = -ENODEV;
		जाओ मुक्त_resources;
	पूर्ण

	/* test incorrect zero sum */
	i = IOP_ADMA_NUM_SRC_TEST;
	स_रखो(pq_sw[i] + 100, 0, 100);
	स_रखो(pq_sw[i+1] + 200, 0, 200);
	क्रम (i = 0; i < IOP_ADMA_NUM_SRC_TEST + 2; i++)
		pq_src[i] = dma_map_page(dev, pq[i], 0, PAGE_SIZE,
					 DMA_TO_DEVICE);

	zero_sum_result = 0;
	tx = iop_adma_prep_dma_pq_val(dma_chan, &pq_src[IOP_ADMA_NUM_SRC_TEST],
				      pq_src, IOP_ADMA_NUM_SRC_TEST,
				      raid6_gfexp, PAGE_SIZE, &zero_sum_result,
				      DMA_PREP_INTERRUPT|DMA_CTRL_ACK);

	cookie = iop_adma_tx_submit(tx);
	iop_adma_issue_pending(dma_chan);
	msleep(8);

	अगर (iop_adma_status(dma_chan, cookie, शून्य) !=
		DMA_COMPLETE) अणु
		dev_err(dev, "Self-test !pq-zero-sum timed out, disabling\n");
		err = -ENODEV;
		जाओ मुक्त_resources;
	पूर्ण

	अगर (zero_sum_result != (SUM_CHECK_P_RESULT | SUM_CHECK_Q_RESULT)) अणु
		dev_err(dev, "Self-test !pq-zero-sum failed to validate: %x\n",
			zero_sum_result);
		err = -ENODEV;
		जाओ मुक्त_resources;
	पूर्ण

मुक्त_resources:
	iop_adma_मुक्त_chan_resources(dma_chan);
out:
	i = ARRAY_SIZE(pq);
	जबतक (i--)
		__मुक्त_page(pq[i]);
	वापस err;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक iop_adma_हटाओ(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा iop_adma_device *device = platक्रमm_get_drvdata(dev);
	काष्ठा dma_chan *chan, *_chan;
	काष्ठा iop_adma_chan *iop_chan;
	काष्ठा iop_adma_platक्रमm_data *plat_data = dev_get_platdata(&dev->dev);

	dma_async_device_unरेजिस्टर(&device->common);

	dma_मुक्त_coherent(&dev->dev, plat_data->pool_size,
			device->dma_desc_pool_virt, device->dma_desc_pool);

	list_क्रम_each_entry_safe(chan, _chan, &device->common.channels,
				device_node) अणु
		iop_chan = to_iop_adma_chan(chan);
		list_del(&chan->device_node);
		kमुक्त(iop_chan);
	पूर्ण
	kमुक्त(device);

	वापस 0;
पूर्ण

अटल पूर्णांक iop_adma_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा resource *res;
	पूर्णांक ret = 0, i;
	काष्ठा iop_adma_device *adev;
	काष्ठा iop_adma_chan *iop_chan;
	काष्ठा dma_device *dma_dev;
	काष्ठा iop_adma_platक्रमm_data *plat_data = dev_get_platdata(&pdev->dev);

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!res)
		वापस -ENODEV;

	अगर (!devm_request_mem_region(&pdev->dev, res->start,
				resource_size(res), pdev->name))
		वापस -EBUSY;

	adev = kzalloc(माप(*adev), GFP_KERNEL);
	अगर (!adev)
		वापस -ENOMEM;
	dma_dev = &adev->common;

	/* allocate coherent memory क्रम hardware descriptors
	 * note: ग_लिखोcombine gives slightly better perक्रमmance, but
	 * requires that we explicitly flush the ग_लिखोs
	 */
	adev->dma_desc_pool_virt = dma_alloc_wc(&pdev->dev,
						plat_data->pool_size,
						&adev->dma_desc_pool,
						GFP_KERNEL);
	अगर (!adev->dma_desc_pool_virt) अणु
		ret = -ENOMEM;
		जाओ err_मुक्त_adev;
	पूर्ण

	dev_dbg(&pdev->dev, "%s: allocated descriptor pool virt %p phys %pad\n",
		__func__, adev->dma_desc_pool_virt, &adev->dma_desc_pool);

	adev->id = plat_data->hw_id;

	/* discover transaction capabilites from the platक्रमm data */
	dma_dev->cap_mask = plat_data->cap_mask;

	adev->pdev = pdev;
	platक्रमm_set_drvdata(pdev, adev);

	INIT_LIST_HEAD(&dma_dev->channels);

	/* set base routines */
	dma_dev->device_alloc_chan_resources = iop_adma_alloc_chan_resources;
	dma_dev->device_मुक्त_chan_resources = iop_adma_मुक्त_chan_resources;
	dma_dev->device_tx_status = iop_adma_status;
	dma_dev->device_issue_pending = iop_adma_issue_pending;
	dma_dev->dev = &pdev->dev;

	/* set prep routines based on capability */
	अगर (dma_has_cap(DMA_MEMCPY, dma_dev->cap_mask))
		dma_dev->device_prep_dma_स_नकल = iop_adma_prep_dma_स_नकल;
	अगर (dma_has_cap(DMA_XOR, dma_dev->cap_mask)) अणु
		dma_dev->max_xor = iop_adma_get_max_xor();
		dma_dev->device_prep_dma_xor = iop_adma_prep_dma_xor;
	पूर्ण
	अगर (dma_has_cap(DMA_XOR_VAL, dma_dev->cap_mask))
		dma_dev->device_prep_dma_xor_val =
			iop_adma_prep_dma_xor_val;
	अगर (dma_has_cap(DMA_PQ, dma_dev->cap_mask)) अणु
		dma_set_maxpq(dma_dev, iop_adma_get_max_pq(), 0);
		dma_dev->device_prep_dma_pq = iop_adma_prep_dma_pq;
	पूर्ण
	अगर (dma_has_cap(DMA_PQ_VAL, dma_dev->cap_mask))
		dma_dev->device_prep_dma_pq_val =
			iop_adma_prep_dma_pq_val;
	अगर (dma_has_cap(DMA_INTERRUPT, dma_dev->cap_mask))
		dma_dev->device_prep_dma_पूर्णांकerrupt =
			iop_adma_prep_dma_पूर्णांकerrupt;

	iop_chan = kzalloc(माप(*iop_chan), GFP_KERNEL);
	अगर (!iop_chan) अणु
		ret = -ENOMEM;
		जाओ err_मुक्त_dma;
	पूर्ण
	iop_chan->device = adev;

	iop_chan->mmr_base = devm_ioremap(&pdev->dev, res->start,
					resource_size(res));
	अगर (!iop_chan->mmr_base) अणु
		ret = -ENOMEM;
		जाओ err_मुक्त_iop_chan;
	पूर्ण
	tasklet_setup(&iop_chan->irq_tasklet, iop_adma_tasklet);

	/* clear errors beक्रमe enabling पूर्णांकerrupts */
	iop_adma_device_clear_err_status(iop_chan);

	क्रम (i = 0; i < 3; i++) अणु
		अटल स्थिर irq_handler_t handler[] = अणु
			iop_adma_eot_handler,
			iop_adma_eoc_handler,
			iop_adma_err_handler
		पूर्ण;
		पूर्णांक irq = platक्रमm_get_irq(pdev, i);
		अगर (irq < 0) अणु
			ret = -ENXIO;
			जाओ err_मुक्त_iop_chan;
		पूर्ण अन्यथा अणु
			ret = devm_request_irq(&pdev->dev, irq,
					handler[i], 0, pdev->name, iop_chan);
			अगर (ret)
				जाओ err_मुक्त_iop_chan;
		पूर्ण
	पूर्ण

	spin_lock_init(&iop_chan->lock);
	INIT_LIST_HEAD(&iop_chan->chain);
	INIT_LIST_HEAD(&iop_chan->all_slots);
	iop_chan->common.device = dma_dev;
	dma_cookie_init(&iop_chan->common);
	list_add_tail(&iop_chan->common.device_node, &dma_dev->channels);

	अगर (dma_has_cap(DMA_MEMCPY, dma_dev->cap_mask)) अणु
		ret = iop_adma_स_नकल_self_test(adev);
		dev_dbg(&pdev->dev, "memcpy self test returned %d\n", ret);
		अगर (ret)
			जाओ err_मुक्त_iop_chan;
	पूर्ण

	अगर (dma_has_cap(DMA_XOR, dma_dev->cap_mask)) अणु
		ret = iop_adma_xor_val_self_test(adev);
		dev_dbg(&pdev->dev, "xor self test returned %d\n", ret);
		अगर (ret)
			जाओ err_मुक्त_iop_chan;
	पूर्ण

	अगर (dma_has_cap(DMA_PQ, dma_dev->cap_mask) &&
	    dma_has_cap(DMA_PQ_VAL, dma_dev->cap_mask)) अणु
		#अगर_घोषित CONFIG_RAID6_PQ
		ret = iop_adma_pq_zero_sum_self_test(adev);
		dev_dbg(&pdev->dev, "pq self test returned %d\n", ret);
		#अन्यथा
		/* can not test raid6, so करो not publish capability */
		dma_cap_clear(DMA_PQ, dma_dev->cap_mask);
		dma_cap_clear(DMA_PQ_VAL, dma_dev->cap_mask);
		ret = 0;
		#पूर्ण_अगर
		अगर (ret)
			जाओ err_मुक्त_iop_chan;
	पूर्ण

	dev_info(&pdev->dev, "Intel(R) IOP: ( %s%s%s%s%s%s)\n",
		 dma_has_cap(DMA_PQ, dma_dev->cap_mask) ? "pq " : "",
		 dma_has_cap(DMA_PQ_VAL, dma_dev->cap_mask) ? "pq_val " : "",
		 dma_has_cap(DMA_XOR, dma_dev->cap_mask) ? "xor " : "",
		 dma_has_cap(DMA_XOR_VAL, dma_dev->cap_mask) ? "xor_val " : "",
		 dma_has_cap(DMA_MEMCPY, dma_dev->cap_mask) ? "cpy " : "",
		 dma_has_cap(DMA_INTERRUPT, dma_dev->cap_mask) ? "intr " : "");

	dma_async_device_रेजिस्टर(dma_dev);
	जाओ out;

 err_मुक्त_iop_chan:
	kमुक्त(iop_chan);
 err_मुक्त_dma:
	dma_मुक्त_coherent(&adev->pdev->dev, plat_data->pool_size,
			adev->dma_desc_pool_virt, adev->dma_desc_pool);
 err_मुक्त_adev:
	kमुक्त(adev);
 out:
	वापस ret;
पूर्ण

अटल व्योम iop_chan_start_null_स_नकल(काष्ठा iop_adma_chan *iop_chan)
अणु
	काष्ठा iop_adma_desc_slot *sw_desc, *grp_start;
	dma_cookie_t cookie;
	पूर्णांक slot_cnt, slots_per_op;

	dev_dbg(iop_chan->device->common.dev, "%s\n", __func__);

	spin_lock_bh(&iop_chan->lock);
	slot_cnt = iop_chan_स_नकल_slot_count(0, &slots_per_op);
	sw_desc = iop_adma_alloc_slots(iop_chan, slot_cnt, slots_per_op);
	अगर (sw_desc) अणु
		grp_start = sw_desc->group_head;

		list_splice_init(&sw_desc->tx_list, &iop_chan->chain);
		async_tx_ack(&sw_desc->async_tx);
		iop_desc_init_स_नकल(grp_start, 0);
		iop_desc_set_byte_count(grp_start, iop_chan, 0);
		iop_desc_set_dest_addr(grp_start, iop_chan, 0);
		iop_desc_set_स_नकल_src_addr(grp_start, 0);

		cookie = dma_cookie_assign(&sw_desc->async_tx);

		/* initialize the completed cookie to be less than
		 * the most recently used cookie
		 */
		iop_chan->common.completed_cookie = cookie - 1;

		/* channel should not be busy */
		BUG_ON(iop_chan_is_busy(iop_chan));

		/* clear any prior error-status bits */
		iop_adma_device_clear_err_status(iop_chan);

		/* disable operation */
		iop_chan_disable(iop_chan);

		/* set the descriptor address */
		iop_chan_set_next_descriptor(iop_chan, sw_desc->async_tx.phys);

		/* 1/ करोn't add pre-chained descriptors
		 * 2/ dummy पढ़ो to flush next_desc ग_लिखो
		 */
		BUG_ON(iop_desc_get_next_desc(sw_desc));

		/* run the descriptor */
		iop_chan_enable(iop_chan);
	पूर्ण अन्यथा
		dev_err(iop_chan->device->common.dev,
			"failed to allocate null descriptor\n");
	spin_unlock_bh(&iop_chan->lock);
पूर्ण

अटल व्योम iop_chan_start_null_xor(काष्ठा iop_adma_chan *iop_chan)
अणु
	काष्ठा iop_adma_desc_slot *sw_desc, *grp_start;
	dma_cookie_t cookie;
	पूर्णांक slot_cnt, slots_per_op;

	dev_dbg(iop_chan->device->common.dev, "%s\n", __func__);

	spin_lock_bh(&iop_chan->lock);
	slot_cnt = iop_chan_xor_slot_count(0, 2, &slots_per_op);
	sw_desc = iop_adma_alloc_slots(iop_chan, slot_cnt, slots_per_op);
	अगर (sw_desc) अणु
		grp_start = sw_desc->group_head;
		list_splice_init(&sw_desc->tx_list, &iop_chan->chain);
		async_tx_ack(&sw_desc->async_tx);
		iop_desc_init_null_xor(grp_start, 2, 0);
		iop_desc_set_byte_count(grp_start, iop_chan, 0);
		iop_desc_set_dest_addr(grp_start, iop_chan, 0);
		iop_desc_set_xor_src_addr(grp_start, 0, 0);
		iop_desc_set_xor_src_addr(grp_start, 1, 0);

		cookie = dma_cookie_assign(&sw_desc->async_tx);

		/* initialize the completed cookie to be less than
		 * the most recently used cookie
		 */
		iop_chan->common.completed_cookie = cookie - 1;

		/* channel should not be busy */
		BUG_ON(iop_chan_is_busy(iop_chan));

		/* clear any prior error-status bits */
		iop_adma_device_clear_err_status(iop_chan);

		/* disable operation */
		iop_chan_disable(iop_chan);

		/* set the descriptor address */
		iop_chan_set_next_descriptor(iop_chan, sw_desc->async_tx.phys);

		/* 1/ करोn't add pre-chained descriptors
		 * 2/ dummy पढ़ो to flush next_desc ग_लिखो
		 */
		BUG_ON(iop_desc_get_next_desc(sw_desc));

		/* run the descriptor */
		iop_chan_enable(iop_chan);
	पूर्ण अन्यथा
		dev_err(iop_chan->device->common.dev,
			"failed to allocate null descriptor\n");
	spin_unlock_bh(&iop_chan->lock);
पूर्ण

अटल काष्ठा platक्रमm_driver iop_adma_driver = अणु
	.probe		= iop_adma_probe,
	.हटाओ		= iop_adma_हटाओ,
	.driver		= अणु
		.name	= "iop-adma",
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(iop_adma_driver);

MODULE_AUTHOR("Intel Corporation");
MODULE_DESCRIPTION("IOP ADMA Engine Driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:iop-adma");
