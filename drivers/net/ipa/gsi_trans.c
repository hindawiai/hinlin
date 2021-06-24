<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

/* Copyright (c) 2012-2018, The Linux Foundation. All rights reserved.
 * Copyright (C) 2019-2020 Linaro Ltd.
 */

#समावेश <linux/types.h>
#समावेश <linux/bits.h>
#समावेश <linux/bitfield.h>
#समावेश <linux/refcount.h>
#समावेश <linux/scatterlist.h>
#समावेश <linux/dma-direction.h>

#समावेश "gsi.h"
#समावेश "gsi_private.h"
#समावेश "gsi_trans.h"
#समावेश "ipa_gsi.h"
#समावेश "ipa_data.h"
#समावेश "ipa_cmd.h"

/**
 * DOC: GSI Transactions
 *
 * A GSI transaction असलtracts the behavior of a GSI channel by representing
 * everything about a related group of IPA commands in a single काष्ठाure.
 * (A "command" in this sense is either a data transfer or an IPA immediate
 * command.)  Most details of पूर्णांकeraction with the GSI hardware are managed
 * by the GSI transaction core, allowing users to simply describe commands
 * to be perक्रमmed.  When a transaction has completed a callback function
 * (dependent on the type of endpoपूर्णांक associated with the channel) allows
 * cleanup of resources associated with the transaction.
 *
 * To perक्रमm a command (or set of them), a user of the GSI transaction
 * पूर्णांकerface allocates a transaction, indicating the number of TREs required
 * (one per command).  If sufficient TREs are available, they are reserved
 * क्रम use in the transaction and the allocation succeeds.  This way
 * exhaustion of the available TREs in a channel ring is detected
 * as early as possible.  All resources required to complete a transaction
 * are allocated at transaction allocation समय.
 *
 * Commands perक्रमmed as part of a transaction are represented in an array
 * of Linux scatterlist काष्ठाures.  This array is allocated with the
 * transaction, and its entries are initialized using standard scatterlist
 * functions (such as sg_set_buf() or skb_to_sgvec()).
 *
 * Once a transaction's scatterlist काष्ठाures have been initialized, the
 * transaction is committed.  The caller is responsible क्रम mapping buffers
 * क्रम DMA अगर necessary, and this should be करोne *beक्रमe* allocating
 * the transaction.  Between a successful allocation and commit of a
 * transaction no errors should occur.
 *
 * Committing transfers ownership of the entire transaction to the GSI
 * transaction core.  The GSI transaction code क्रमmats the content of
 * the scatterlist array पूर्णांकo the channel ring buffer and inक्रमms the
 * hardware that new TREs are available to process.
 *
 * The last TRE in each transaction is marked to पूर्णांकerrupt the AP when the
 * GSI hardware has completed it.  Because transfers described by TREs are
 * perक्रमmed strictly in order, संकेतing the completion of just the last
 * TRE in the transaction is sufficient to indicate the full transaction
 * is complete.
 *
 * When a transaction is complete, ipa_gsi_trans_complete() is called by the
 * GSI code पूर्णांकo the IPA layer, allowing it to perक्रमm any final cleanup
 * required beक्रमe the transaction is मुक्तd.
 */

/* Hardware values representing a transfer element type */
क्रमागत gsi_tre_type अणु
	GSI_RE_XFER	= 0x2,
	GSI_RE_IMMD_CMD	= 0x3,
पूर्ण;

/* An entry in a channel ring */
काष्ठा gsi_tre अणु
	__le64 addr;		/* DMA address */
	__le16 len_opcode;	/* length in bytes or क्रमागत IPA_CMD_* */
	__le16 reserved;
	__le32 flags;		/* TRE_FLAGS_* */
पूर्ण;

/* gsi_tre->flags mask values (in CPU byte order) */
#घोषणा TRE_FLAGS_CHAIN_FMASK	GENMASK(0, 0)
#घोषणा TRE_FLAGS_IEOT_FMASK	GENMASK(9, 9)
#घोषणा TRE_FLAGS_BEI_FMASK	GENMASK(10, 10)
#घोषणा TRE_FLAGS_TYPE_FMASK	GENMASK(23, 16)

पूर्णांक gsi_trans_pool_init(काष्ठा gsi_trans_pool *pool, माप_प्रकार size, u32 count,
			u32 max_alloc)
अणु
	व्योम *virt;

#अगर_घोषित IPA_VALIDATE
	अगर (!size)
		वापस -EINVAL;
	अगर (count < max_alloc)
		वापस -EINVAL;
	अगर (!max_alloc)
		वापस -EINVAL;
#पूर्ण_अगर /* IPA_VALIDATE */

	/* By allocating a few extra entries in our pool (one less
	 * than the maximum number that will be requested in a
	 * single allocation), we can always satisfy requests without
	 * ever worrying about straddling the end of the pool array.
	 * If there aren't enough entries starting at the मुक्त index,
	 * we just allocate मुक्त entries from the beginning of the pool.
	 */
	virt = kसुस्मृति(count + max_alloc - 1, size, GFP_KERNEL);
	अगर (!virt)
		वापस -ENOMEM;

	pool->base = virt;
	/* If the allocator gave us any extra memory, use it */
	pool->count = ksize(pool->base) / size;
	pool->मुक्त = 0;
	pool->max_alloc = max_alloc;
	pool->size = size;
	pool->addr = 0;		/* Only used क्रम DMA pools */

	वापस 0;
पूर्ण

व्योम gsi_trans_pool_निकास(काष्ठा gsi_trans_pool *pool)
अणु
	kमुक्त(pool->base);
	स_रखो(pool, 0, माप(*pool));
पूर्ण

/* Allocate the requested number of (zeroed) entries from the pool */
/* Home-grown DMA pool.  This way we can pपुनः_स्मृतिate and use the tre_count
 * to guarantee allocations will succeed.  Even though we specअगरy max_alloc
 * (and it can be more than one), we only allow allocation of a single
 * element from a DMA pool.
 */
पूर्णांक gsi_trans_pool_init_dma(काष्ठा device *dev, काष्ठा gsi_trans_pool *pool,
			    माप_प्रकार size, u32 count, u32 max_alloc)
अणु
	माप_प्रकार total_size;
	dma_addr_t addr;
	व्योम *virt;

#अगर_घोषित IPA_VALIDATE
	अगर (!size)
		वापस -EINVAL;
	अगर (count < max_alloc)
		वापस -EINVAL;
	अगर (!max_alloc)
		वापस -EINVAL;
#पूर्ण_अगर /* IPA_VALIDATE */

	/* Don't let allocations cross a घातer-of-two boundary */
	size = __roundup_घात_of_two(size);
	total_size = (count + max_alloc - 1) * size;

	/* The allocator will give us a घातer-of-2 number of pages
	 * sufficient to satisfy our request.  Round up our requested
	 * size to aव्योम any unused space in the allocation.  This way
	 * gsi_trans_pool_निकास_dma() can assume the total allocated
	 * size is exactly (count * size).
	 */
	total_size = get_order(total_size) << PAGE_SHIFT;

	virt = dma_alloc_coherent(dev, total_size, &addr, GFP_KERNEL);
	अगर (!virt)
		वापस -ENOMEM;

	pool->base = virt;
	pool->count = total_size / size;
	pool->मुक्त = 0;
	pool->size = size;
	pool->max_alloc = max_alloc;
	pool->addr = addr;

	वापस 0;
पूर्ण

व्योम gsi_trans_pool_निकास_dma(काष्ठा device *dev, काष्ठा gsi_trans_pool *pool)
अणु
	माप_प्रकार total_size = pool->count * pool->size;

	dma_मुक्त_coherent(dev, total_size, pool->base, pool->addr);
	स_रखो(pool, 0, माप(*pool));
पूर्ण

/* Return the byte offset of the next मुक्त entry in the pool */
अटल u32 gsi_trans_pool_alloc_common(काष्ठा gsi_trans_pool *pool, u32 count)
अणु
	u32 offset;

	/* निश्चित(count > 0); */
	/* निश्चित(count <= pool->max_alloc); */

	/* Allocate from beginning अगर wrap would occur */
	अगर (count > pool->count - pool->मुक्त)
		pool->मुक्त = 0;

	offset = pool->मुक्त * pool->size;
	pool->मुक्त += count;
	स_रखो(pool->base + offset, 0, count * pool->size);

	वापस offset;
पूर्ण

/* Allocate a contiguous block of zeroed entries from a pool */
व्योम *gsi_trans_pool_alloc(काष्ठा gsi_trans_pool *pool, u32 count)
अणु
	वापस pool->base + gsi_trans_pool_alloc_common(pool, count);
पूर्ण

/* Allocate a single zeroed entry from a DMA pool */
व्योम *gsi_trans_pool_alloc_dma(काष्ठा gsi_trans_pool *pool, dma_addr_t *addr)
अणु
	u32 offset = gsi_trans_pool_alloc_common(pool, 1);

	*addr = pool->addr + offset;

	वापस pool->base + offset;
पूर्ण

/* Return the pool element that immediately follows the one given.
 * This only works करोne अगर elements are allocated one at a समय.
 */
व्योम *gsi_trans_pool_next(काष्ठा gsi_trans_pool *pool, व्योम *element)
अणु
	व्योम *end = pool->base + pool->count * pool->size;

	/* निश्चित(element >= pool->base); */
	/* निश्चित(element < end); */
	/* निश्चित(pool->max_alloc == 1); */
	element += pool->size;

	वापस element < end ? element : pool->base;
पूर्ण

/* Map a given ring entry index to the transaction associated with it */
अटल व्योम gsi_channel_trans_map(काष्ठा gsi_channel *channel, u32 index,
				  काष्ठा gsi_trans *trans)
अणु
	/* Note: index *must* be used modulo the ring count here */
	channel->trans_info.map[index % channel->tre_ring.count] = trans;
पूर्ण

/* Return the transaction mapped to a given ring entry */
काष्ठा gsi_trans *
gsi_channel_trans_mapped(काष्ठा gsi_channel *channel, u32 index)
अणु
	/* Note: index *must* be used modulo the ring count here */
	वापस channel->trans_info.map[index % channel->tre_ring.count];
पूर्ण

/* Return the oldest completed transaction क्रम a channel (or null) */
काष्ठा gsi_trans *gsi_channel_trans_complete(काष्ठा gsi_channel *channel)
अणु
	वापस list_first_entry_or_null(&channel->trans_info.complete,
					काष्ठा gsi_trans, links);
पूर्ण

/* Move a transaction from the allocated list to the pending list */
अटल व्योम gsi_trans_move_pending(काष्ठा gsi_trans *trans)
अणु
	काष्ठा gsi_channel *channel = &trans->gsi->channel[trans->channel_id];
	काष्ठा gsi_trans_info *trans_info = &channel->trans_info;

	spin_lock_bh(&trans_info->spinlock);

	list_move_tail(&trans->links, &trans_info->pending);

	spin_unlock_bh(&trans_info->spinlock);
पूर्ण

/* Move a transaction and all of its predecessors from the pending list
 * to the completed list.
 */
व्योम gsi_trans_move_complete(काष्ठा gsi_trans *trans)
अणु
	काष्ठा gsi_channel *channel = &trans->gsi->channel[trans->channel_id];
	काष्ठा gsi_trans_info *trans_info = &channel->trans_info;
	काष्ठा list_head list;

	spin_lock_bh(&trans_info->spinlock);

	/* Move this transaction and all predecessors to completed list */
	list_cut_position(&list, &trans_info->pending, &trans->links);
	list_splice_tail(&list, &trans_info->complete);

	spin_unlock_bh(&trans_info->spinlock);
पूर्ण

/* Move a transaction from the completed list to the polled list */
व्योम gsi_trans_move_polled(काष्ठा gsi_trans *trans)
अणु
	काष्ठा gsi_channel *channel = &trans->gsi->channel[trans->channel_id];
	काष्ठा gsi_trans_info *trans_info = &channel->trans_info;

	spin_lock_bh(&trans_info->spinlock);

	list_move_tail(&trans->links, &trans_info->polled);

	spin_unlock_bh(&trans_info->spinlock);
पूर्ण

/* Reserve some number of TREs on a channel.  Returns true अगर successful */
अटल bool
gsi_trans_tre_reserve(काष्ठा gsi_trans_info *trans_info, u32 tre_count)
अणु
	पूर्णांक avail = atomic_पढ़ो(&trans_info->tre_avail);
	पूर्णांक new;

	करो अणु
		new = avail - (पूर्णांक)tre_count;
		अगर (unlikely(new < 0))
			वापस false;
	पूर्ण जबतक (!atomic_try_cmpxchg(&trans_info->tre_avail, &avail, new));

	वापस true;
पूर्ण

/* Release previously-reserved TRE entries to a channel */
अटल व्योम
gsi_trans_tre_release(काष्ठा gsi_trans_info *trans_info, u32 tre_count)
अणु
	atomic_add(tre_count, &trans_info->tre_avail);
पूर्ण

/* Allocate a GSI transaction on a channel */
काष्ठा gsi_trans *gsi_channel_trans_alloc(काष्ठा gsi *gsi, u32 channel_id,
					  u32 tre_count,
					  क्रमागत dma_data_direction direction)
अणु
	काष्ठा gsi_channel *channel = &gsi->channel[channel_id];
	काष्ठा gsi_trans_info *trans_info;
	काष्ठा gsi_trans *trans;

	/* निश्चित(tre_count <= gsi_channel_trans_tre_max(gsi, channel_id)); */

	trans_info = &channel->trans_info;

	/* We reserve the TREs now, but consume them at commit समय.
	 * If there aren't enough available, we're करोne.
	 */
	अगर (!gsi_trans_tre_reserve(trans_info, tre_count))
		वापस शून्य;

	/* Allocate and initialize non-zero fields in the the transaction */
	trans = gsi_trans_pool_alloc(&trans_info->pool, 1);
	trans->gsi = gsi;
	trans->channel_id = channel_id;
	trans->tre_count = tre_count;
	init_completion(&trans->completion);

	/* Allocate the scatterlist and (अगर requested) info entries. */
	trans->sgl = gsi_trans_pool_alloc(&trans_info->sg_pool, tre_count);
	sg_init_marker(trans->sgl, tre_count);

	trans->direction = direction;

	spin_lock_bh(&trans_info->spinlock);

	list_add_tail(&trans->links, &trans_info->alloc);

	spin_unlock_bh(&trans_info->spinlock);

	refcount_set(&trans->refcount, 1);

	वापस trans;
पूर्ण

/* Free a previously-allocated transaction */
व्योम gsi_trans_मुक्त(काष्ठा gsi_trans *trans)
अणु
	refcount_t *refcount = &trans->refcount;
	काष्ठा gsi_trans_info *trans_info;
	bool last;

	/* We must hold the lock to release the last reference */
	अगर (refcount_dec_not_one(refcount))
		वापस;

	trans_info = &trans->gsi->channel[trans->channel_id].trans_info;

	spin_lock_bh(&trans_info->spinlock);

	/* Reference might have been added beक्रमe we got the lock */
	last = refcount_dec_and_test(refcount);
	अगर (last)
		list_del(&trans->links);

	spin_unlock_bh(&trans_info->spinlock);

	अगर (!last)
		वापस;

	ipa_gsi_trans_release(trans);

	/* Releasing the reserved TREs implicitly मुक्तs the sgl[] and
	 * (अगर present) info[] arrays, plus the transaction itself.
	 */
	gsi_trans_tre_release(trans_info, trans->tre_count);
पूर्ण

/* Add an immediate command to a transaction */
व्योम gsi_trans_cmd_add(काष्ठा gsi_trans *trans, व्योम *buf, u32 size,
		       dma_addr_t addr, क्रमागत dma_data_direction direction,
		       क्रमागत ipa_cmd_opcode opcode)
अणु
	काष्ठा ipa_cmd_info *info;
	u32 which = trans->used++;
	काष्ठा scatterlist *sg;

	/* निश्चित(which < trans->tre_count); */

	/* Commands are quite dअगरferent from data transfer requests.
	 * Their payloads come from a pool whose memory is allocated
	 * using dma_alloc_coherent().  We thereक्रमe करो *not* map them
	 * क्रम DMA (unlike what we करो क्रम pages and skbs).
	 *
	 * When a transaction completes, the SGL is normally unmapped.
	 * A command transaction has direction DMA_NONE, which tells
	 * gsi_trans_complete() to skip the unmapping step.
	 *
	 * The only things we use directly in a command scatter/gather
	 * entry are the DMA address and length.  We still need the SG
	 * table flags to be मुख्यtained though, so assign a शून्य page
	 * poपूर्णांकer क्रम that purpose.
	 */
	sg = &trans->sgl[which];
	sg_assign_page(sg, शून्य);
	sg_dma_address(sg) = addr;
	sg_dma_len(sg) = size;

	info = &trans->info[which];
	info->opcode = opcode;
	info->direction = direction;
पूर्ण

/* Add a page transfer to a transaction.  It will fill the only TRE. */
पूर्णांक gsi_trans_page_add(काष्ठा gsi_trans *trans, काष्ठा page *page, u32 size,
		       u32 offset)
अणु
	काष्ठा scatterlist *sg = &trans->sgl[0];
	पूर्णांक ret;

	/* निश्चित(trans->tre_count == 1); */
	/* निश्चित(!trans->used); */

	sg_set_page(sg, page, size, offset);
	ret = dma_map_sg(trans->gsi->dev, sg, 1, trans->direction);
	अगर (!ret)
		वापस -ENOMEM;

	trans->used++;	/* Transaction now owns the (DMA mapped) page */

	वापस 0;
पूर्ण

/* Add an SKB transfer to a transaction.  No other TREs will be used. */
पूर्णांक gsi_trans_skb_add(काष्ठा gsi_trans *trans, काष्ठा sk_buff *skb)
अणु
	काष्ठा scatterlist *sg = &trans->sgl[0];
	u32 used;
	पूर्णांक ret;

	/* निश्चित(trans->tre_count == 1); */
	/* निश्चित(!trans->used); */

	/* skb->len will not be 0 (checked early) */
	ret = skb_to_sgvec(skb, sg, 0, skb->len);
	अगर (ret < 0)
		वापस ret;
	used = ret;

	ret = dma_map_sg(trans->gsi->dev, sg, used, trans->direction);
	अगर (!ret)
		वापस -ENOMEM;

	trans->used += used;	/* Transaction now owns the (DMA mapped) skb */

	वापस 0;
पूर्ण

/* Compute the length/opcode value to use क्रम a TRE */
अटल __le16 gsi_tre_len_opcode(क्रमागत ipa_cmd_opcode opcode, u32 len)
अणु
	वापस opcode == IPA_CMD_NONE ? cpu_to_le16((u16)len)
				      : cpu_to_le16((u16)opcode);
पूर्ण

/* Compute the flags value to use क्रम a given TRE */
अटल __le32 gsi_tre_flags(bool last_tre, bool bei, क्रमागत ipa_cmd_opcode opcode)
अणु
	क्रमागत gsi_tre_type tre_type;
	u32 tre_flags;

	tre_type = opcode == IPA_CMD_NONE ? GSI_RE_XFER : GSI_RE_IMMD_CMD;
	tre_flags = u32_encode_bits(tre_type, TRE_FLAGS_TYPE_FMASK);

	/* Last TRE contains पूर्णांकerrupt flags */
	अगर (last_tre) अणु
		/* All transactions end in a transfer completion पूर्णांकerrupt */
		tre_flags |= TRE_FLAGS_IEOT_FMASK;
		/* Don't पूर्णांकerrupt when outbound commands are acknowledged */
		अगर (bei)
			tre_flags |= TRE_FLAGS_BEI_FMASK;
	पूर्ण अन्यथा अणु	/* All others indicate there's more to come */
		tre_flags |= TRE_FLAGS_CHAIN_FMASK;
	पूर्ण

	वापस cpu_to_le32(tre_flags);
पूर्ण

अटल व्योम gsi_trans_tre_fill(काष्ठा gsi_tre *dest_tre, dma_addr_t addr,
			       u32 len, bool last_tre, bool bei,
			       क्रमागत ipa_cmd_opcode opcode)
अणु
	काष्ठा gsi_tre tre;

	tre.addr = cpu_to_le64(addr);
	tre.len_opcode = gsi_tre_len_opcode(opcode, len);
	tre.reserved = 0;
	tre.flags = gsi_tre_flags(last_tre, bei, opcode);

	/* ARM64 can ग_लिखो 16 bytes as a unit with a single inकाष्ठाion.
	 * Doing the assignment this way is an attempt to make that happen.
	 */
	*dest_tre = tre;
पूर्ण

/**
 * __gsi_trans_commit() - Common GSI transaction commit code
 * @trans:	Transaction to commit
 * @ring_db:	Whether to tell the hardware about these queued transfers
 *
 * Formats channel ring TRE entries based on the content of the scatterlist.
 * Maps a transaction poपूर्णांकer to the last ring entry used क्रम the transaction,
 * so it can be recovered when it completes.  Moves the transaction to the
 * pending list.  Finally, updates the channel ring poपूर्णांकer and optionally
 * rings the करोorbell.
 */
अटल व्योम __gsi_trans_commit(काष्ठा gsi_trans *trans, bool ring_db)
अणु
	काष्ठा gsi_channel *channel = &trans->gsi->channel[trans->channel_id];
	काष्ठा gsi_ring *ring = &channel->tre_ring;
	क्रमागत ipa_cmd_opcode opcode = IPA_CMD_NONE;
	bool bei = channel->toward_ipa;
	काष्ठा ipa_cmd_info *info;
	काष्ठा gsi_tre *dest_tre;
	काष्ठा scatterlist *sg;
	u32 byte_count = 0;
	u32 avail;
	u32 i;

	/* निश्चित(trans->used > 0); */

	/* Consume the entries.  If we cross the end of the ring जबतक
	 * filling them we'll चयन to the beginning to finish.
	 * If there is no info array we're करोing a simple data
	 * transfer request, whose opcode is IPA_CMD_NONE.
	 */
	info = trans->info ? &trans->info[0] : शून्य;
	avail = ring->count - ring->index % ring->count;
	dest_tre = gsi_ring_virt(ring, ring->index);
	क्रम_each_sg(trans->sgl, sg, trans->used, i) अणु
		bool last_tre = i == trans->used - 1;
		dma_addr_t addr = sg_dma_address(sg);
		u32 len = sg_dma_len(sg);

		byte_count += len;
		अगर (!avail--)
			dest_tre = gsi_ring_virt(ring, 0);
		अगर (info)
			opcode = info++->opcode;

		gsi_trans_tre_fill(dest_tre, addr, len, last_tre, bei, opcode);
		dest_tre++;
	पूर्ण
	ring->index += trans->used;

	अगर (channel->toward_ipa) अणु
		/* We record TX bytes when they are sent */
		trans->len = byte_count;
		trans->trans_count = channel->trans_count;
		trans->byte_count = channel->byte_count;
		channel->trans_count++;
		channel->byte_count += byte_count;
	पूर्ण

	/* Associate the last TRE with the transaction */
	gsi_channel_trans_map(channel, ring->index - 1, trans);

	gsi_trans_move_pending(trans);

	/* Ring करोorbell अगर requested, or अगर all TREs are allocated */
	अगर (ring_db || !atomic_पढ़ो(&channel->trans_info.tre_avail)) अणु
		/* Report what we're handing off to hardware क्रम TX channels */
		अगर (channel->toward_ipa)
			gsi_channel_tx_queued(channel);
		gsi_channel_करोorbell(channel);
	पूर्ण
पूर्ण

/* Commit a GSI transaction */
व्योम gsi_trans_commit(काष्ठा gsi_trans *trans, bool ring_db)
अणु
	अगर (trans->used)
		__gsi_trans_commit(trans, ring_db);
	अन्यथा
		gsi_trans_मुक्त(trans);
पूर्ण

/* Commit a GSI transaction and रुको क्रम it to complete */
व्योम gsi_trans_commit_रुको(काष्ठा gsi_trans *trans)
अणु
	अगर (!trans->used)
		जाओ out_trans_मुक्त;

	refcount_inc(&trans->refcount);

	__gsi_trans_commit(trans, true);

	रुको_क्रम_completion(&trans->completion);

out_trans_मुक्त:
	gsi_trans_मुक्त(trans);
पूर्ण

/* Commit a GSI transaction and रुको क्रम it to complete, with समयout */
पूर्णांक gsi_trans_commit_रुको_समयout(काष्ठा gsi_trans *trans,
				  अचिन्हित दीर्घ समयout)
अणु
	अचिन्हित दीर्घ समयout_jअगरfies = msecs_to_jअगरfies(समयout);
	अचिन्हित दीर्घ reमुख्यing = 1;	/* In हाल of empty transaction */

	अगर (!trans->used)
		जाओ out_trans_मुक्त;

	refcount_inc(&trans->refcount);

	__gsi_trans_commit(trans, true);

	reमुख्यing = रुको_क्रम_completion_समयout(&trans->completion,
						समयout_jअगरfies);
out_trans_मुक्त:
	gsi_trans_मुक्त(trans);

	वापस reमुख्यing ? 0 : -ETIMEDOUT;
पूर्ण

/* Process the completion of a transaction; called जबतक polling */
व्योम gsi_trans_complete(काष्ठा gsi_trans *trans)
अणु
	/* If the entire SGL was mapped when added, unmap it now */
	अगर (trans->direction != DMA_NONE)
		dma_unmap_sg(trans->gsi->dev, trans->sgl, trans->used,
			     trans->direction);

	ipa_gsi_trans_complete(trans);

	complete(&trans->completion);

	gsi_trans_मुक्त(trans);
पूर्ण

/* Cancel a channel's pending transactions */
व्योम gsi_channel_trans_cancel_pending(काष्ठा gsi_channel *channel)
अणु
	काष्ठा gsi_trans_info *trans_info = &channel->trans_info;
	काष्ठा gsi_trans *trans;
	bool cancelled;

	/* channel->gsi->mutex is held by caller */
	spin_lock_bh(&trans_info->spinlock);

	cancelled = !list_empty(&trans_info->pending);
	list_क्रम_each_entry(trans, &trans_info->pending, links)
		trans->cancelled = true;

	list_splice_tail_init(&trans_info->pending, &trans_info->complete);

	spin_unlock_bh(&trans_info->spinlock);

	/* Schedule NAPI polling to complete the cancelled transactions */
	अगर (cancelled)
		napi_schedule(&channel->napi);
पूर्ण

/* Issue a command to पढ़ो a single byte from a channel */
पूर्णांक gsi_trans_पढ़ो_byte(काष्ठा gsi *gsi, u32 channel_id, dma_addr_t addr)
अणु
	काष्ठा gsi_channel *channel = &gsi->channel[channel_id];
	काष्ठा gsi_ring *ring = &channel->tre_ring;
	काष्ठा gsi_trans_info *trans_info;
	काष्ठा gsi_tre *dest_tre;

	trans_info = &channel->trans_info;

	/* First reserve the TRE, अगर possible */
	अगर (!gsi_trans_tre_reserve(trans_info, 1))
		वापस -EBUSY;

	/* Now fill the the reserved TRE and tell the hardware */

	dest_tre = gsi_ring_virt(ring, ring->index);
	gsi_trans_tre_fill(dest_tre, addr, 1, true, false, IPA_CMD_NONE);

	ring->index++;
	gsi_channel_करोorbell(channel);

	वापस 0;
पूर्ण

/* Mark a gsi_trans_पढ़ो_byte() request करोne */
व्योम gsi_trans_पढ़ो_byte_करोne(काष्ठा gsi *gsi, u32 channel_id)
अणु
	काष्ठा gsi_channel *channel = &gsi->channel[channel_id];

	gsi_trans_tre_release(&channel->trans_info, 1);
पूर्ण

/* Initialize a channel's GSI transaction info */
पूर्णांक gsi_channel_trans_init(काष्ठा gsi *gsi, u32 channel_id)
अणु
	काष्ठा gsi_channel *channel = &gsi->channel[channel_id];
	काष्ठा gsi_trans_info *trans_info;
	u32 tre_max;
	पूर्णांक ret;

	/* Ensure the size of a channel element is what's expected */
	BUILD_BUG_ON(माप(काष्ठा gsi_tre) != GSI_RING_ELEMENT_SIZE);

	/* The map array is used to determine what transaction is associated
	 * with a TRE that the hardware reports has completed.  We need one
	 * map entry per TRE.
	 */
	trans_info = &channel->trans_info;
	trans_info->map = kसुस्मृति(channel->tre_count, माप(*trans_info->map),
				  GFP_KERNEL);
	अगर (!trans_info->map)
		वापस -ENOMEM;

	/* We can't use more TREs than there are available in the ring.
	 * This limits the number of transactions that can be oustanding.
	 * Worst हाल is one TRE per transaction (but we actually limit
	 * it to something a little less than that).  We allocate resources
	 * क्रम transactions (including transaction काष्ठाures) based on
	 * this maximum number.
	 */
	tre_max = gsi_channel_tre_max(channel->gsi, channel_id);

	/* Transactions are allocated one at a समय. */
	ret = gsi_trans_pool_init(&trans_info->pool, माप(काष्ठा gsi_trans),
				  tre_max, 1);
	अगर (ret)
		जाओ err_kमुक्त;

	/* A transaction uses a scatterlist array to represent the data
	 * transfers implemented by the transaction.  Each scatterlist
	 * element is used to fill a single TRE when the transaction is
	 * committed.  So we need as many scatterlist elements as the
	 * maximum number of TREs that can be outstanding.
	 *
	 * All TREs in a transaction must fit within the channel's TLV FIFO.
	 * A transaction on a channel can allocate as many TREs as that but
	 * no more.
	 */
	ret = gsi_trans_pool_init(&trans_info->sg_pool,
				  माप(काष्ठा scatterlist),
				  tre_max, channel->tlv_count);
	अगर (ret)
		जाओ err_trans_pool_निकास;

	/* Finally, the tre_avail field is what ultimately limits the number
	 * of outstanding transactions and their resources.  A transaction
	 * allocation succeeds only अगर the TREs available are sufficient क्रम
	 * what the transaction might need.  Transaction resource pools are
	 * sized based on the maximum number of outstanding TREs, so there
	 * will always be resources available अगर there are TREs available.
	 */
	atomic_set(&trans_info->tre_avail, tre_max);

	spin_lock_init(&trans_info->spinlock);
	INIT_LIST_HEAD(&trans_info->alloc);
	INIT_LIST_HEAD(&trans_info->pending);
	INIT_LIST_HEAD(&trans_info->complete);
	INIT_LIST_HEAD(&trans_info->polled);

	वापस 0;

err_trans_pool_निकास:
	gsi_trans_pool_निकास(&trans_info->pool);
err_kमुक्त:
	kमुक्त(trans_info->map);

	dev_err(gsi->dev, "error %d initializing channel %u transactions\n",
		ret, channel_id);

	वापस ret;
पूर्ण

/* Inverse of gsi_channel_trans_init() */
व्योम gsi_channel_trans_निकास(काष्ठा gsi_channel *channel)
अणु
	काष्ठा gsi_trans_info *trans_info = &channel->trans_info;

	gsi_trans_pool_निकास(&trans_info->sg_pool);
	gsi_trans_pool_निकास(&trans_info->pool);
	kमुक्त(trans_info->map);
पूर्ण
