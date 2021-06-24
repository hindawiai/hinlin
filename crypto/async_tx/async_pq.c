<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright(c) 2007 Yuri Tikhonov <yur@emcraft.com>
 * Copyright(c) 2009 Intel Corporation
 */
#समावेश <linux/kernel.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/raid/pq.h>
#समावेश <linux/async_tx.h>
#समावेश <linux/gfp.h>

/**
 * pq_scribble_page - space to hold throwaway P or Q buffer क्रम
 * synchronous gen_syndrome
 */
अटल काष्ठा page *pq_scribble_page;

/* the काष्ठा page *blocks[] parameter passed to async_gen_syndrome()
 * and async_syndrome_val() contains the 'P' destination address at
 * blocks[disks-2] and the 'Q' destination address at blocks[disks-1]
 *
 * note: these are macros as they are used as lvalues
 */
#घोषणा P(b, d) (b[d-2])
#घोषणा Q(b, d) (b[d-1])

#घोषणा MAX_DISKS 255

/**
 * करो_async_gen_syndrome - asynchronously calculate P and/or Q
 */
अटल __async_अंतरभूत काष्ठा dma_async_tx_descriptor *
करो_async_gen_syndrome(काष्ठा dma_chan *chan,
		      स्थिर अचिन्हित अक्षर *scfs, पूर्णांक disks,
		      काष्ठा dmaengine_unmap_data *unmap,
		      क्रमागत dma_ctrl_flags dma_flags,
		      काष्ठा async_submit_ctl *submit)
अणु
	काष्ठा dma_async_tx_descriptor *tx = शून्य;
	काष्ठा dma_device *dma = chan->device;
	क्रमागत async_tx_flags flags_orig = submit->flags;
	dma_async_tx_callback cb_fn_orig = submit->cb_fn;
	dma_async_tx_callback cb_param_orig = submit->cb_param;
	पूर्णांक src_cnt = disks - 2;
	अचिन्हित लघु pq_src_cnt;
	dma_addr_t dma_dest[2];
	पूर्णांक src_off = 0;

	जबतक (src_cnt > 0) अणु
		submit->flags = flags_orig;
		pq_src_cnt = min(src_cnt, dma_maxpq(dma, dma_flags));
		/* अगर we are submitting additional pqs, leave the chain खोलो,
		 * clear the callback parameters, and leave the destination
		 * buffers mapped
		 */
		अगर (src_cnt > pq_src_cnt) अणु
			submit->flags &= ~ASYNC_TX_ACK;
			submit->flags |= ASYNC_TX_FENCE;
			submit->cb_fn = शून्य;
			submit->cb_param = शून्य;
		पूर्ण अन्यथा अणु
			submit->cb_fn = cb_fn_orig;
			submit->cb_param = cb_param_orig;
			अगर (cb_fn_orig)
				dma_flags |= DMA_PREP_INTERRUPT;
		पूर्ण
		अगर (submit->flags & ASYNC_TX_FENCE)
			dma_flags |= DMA_PREP_FENCE;

		/* Drivers क्रमce क्रमward progress in हाल they can not provide
		 * a descriptor
		 */
		क्रम (;;) अणु
			dma_dest[0] = unmap->addr[disks - 2];
			dma_dest[1] = unmap->addr[disks - 1];
			tx = dma->device_prep_dma_pq(chan, dma_dest,
						     &unmap->addr[src_off],
						     pq_src_cnt,
						     &scfs[src_off], unmap->len,
						     dma_flags);
			अगर (likely(tx))
				अवरोध;
			async_tx_quiesce(&submit->depend_tx);
			dma_async_issue_pending(chan);
		पूर्ण

		dma_set_unmap(tx, unmap);
		async_tx_submit(chan, tx, submit);
		submit->depend_tx = tx;

		/* drop completed sources */
		src_cnt -= pq_src_cnt;
		src_off += pq_src_cnt;

		dma_flags |= DMA_PREP_CONTINUE;
	पूर्ण

	वापस tx;
पूर्ण

/**
 * करो_sync_gen_syndrome - synchronously calculate a raid6 syndrome
 */
अटल व्योम
करो_sync_gen_syndrome(काष्ठा page **blocks, अचिन्हित पूर्णांक *offsets, पूर्णांक disks,
		     माप_प्रकार len, काष्ठा async_submit_ctl *submit)
अणु
	व्योम **srcs;
	पूर्णांक i;
	पूर्णांक start = -1, stop = disks - 3;

	अगर (submit->scribble)
		srcs = submit->scribble;
	अन्यथा
		srcs = (व्योम **) blocks;

	क्रम (i = 0; i < disks; i++) अणु
		अगर (blocks[i] == शून्य) अणु
			BUG_ON(i > disks - 3); /* P or Q can't be zero */
			srcs[i] = (व्योम*)raid6_empty_zero_page;
		पूर्ण अन्यथा अणु
			srcs[i] = page_address(blocks[i]) + offsets[i];

			अगर (i < disks - 2) अणु
				stop = i;
				अगर (start == -1)
					start = i;
			पूर्ण
		पूर्ण
	पूर्ण
	अगर (submit->flags & ASYNC_TX_PQ_XOR_DST) अणु
		BUG_ON(!raid6_call.xor_syndrome);
		अगर (start >= 0)
			raid6_call.xor_syndrome(disks, start, stop, len, srcs);
	पूर्ण अन्यथा
		raid6_call.gen_syndrome(disks, len, srcs);
	async_tx_sync_epilog(submit);
पूर्ण

अटल अंतरभूत bool
is_dma_pq_aligned_offs(काष्ठा dma_device *dev, अचिन्हित पूर्णांक *offs,
				     पूर्णांक src_cnt, माप_प्रकार len)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < src_cnt; i++) अणु
		अगर (!is_dma_pq_aligned(dev, offs[i], 0, len))
			वापस false;
	पूर्ण
	वापस true;
पूर्ण

/**
 * async_gen_syndrome - asynchronously calculate a raid6 syndrome
 * @blocks: source blocks from idx 0..disks-3, P @ disks-2 and Q @ disks-1
 * @offsets: offset array पूर्णांकo each block (src and dest) to start transaction
 * @disks: number of blocks (including missing P or Q, see below)
 * @len: length of operation in bytes
 * @submit: submission/completion modअगरiers
 *
 * General note: This routine assumes a field of GF(2^8) with a
 * primitive polynomial of 0x11d and a generator of अणु02पूर्ण.
 *
 * 'disks' note: callers can optionally omit either P or Q (but not
 * both) from the calculation by setting blocks[disks-2] or
 * blocks[disks-1] to शून्य.  When P or Q is omitted 'len' must be <=
 * PAGE_SIZE as a temporary buffer of this size is used in the
 * synchronous path.  'disks' always accounts क्रम both destination
 * buffers.  If any source buffers (blocks[i] where i < disks - 2) are
 * set to शून्य those buffers will be replaced with the raid6_zero_page
 * in the synchronous path and omitted in the hardware-asynchronous
 * path.
 */
काष्ठा dma_async_tx_descriptor *
async_gen_syndrome(काष्ठा page **blocks, अचिन्हित पूर्णांक *offsets, पूर्णांक disks,
		   माप_प्रकार len, काष्ठा async_submit_ctl *submit)
अणु
	पूर्णांक src_cnt = disks - 2;
	काष्ठा dma_chan *chan = async_tx_find_channel(submit, DMA_PQ,
						      &P(blocks, disks), 2,
						      blocks, src_cnt, len);
	काष्ठा dma_device *device = chan ? chan->device : शून्य;
	काष्ठा dmaengine_unmap_data *unmap = शून्य;

	BUG_ON(disks > MAX_DISKS || !(P(blocks, disks) || Q(blocks, disks)));

	अगर (device)
		unmap = dmaengine_get_unmap_data(device->dev, disks, GFP_NOWAIT);

	/* XORing P/Q is only implemented in software */
	अगर (unmap && !(submit->flags & ASYNC_TX_PQ_XOR_DST) &&
	    (src_cnt <= dma_maxpq(device, 0) ||
	     dma_maxpq(device, DMA_PREP_CONTINUE) > 0) &&
	    is_dma_pq_aligned_offs(device, offsets, disks, len)) अणु
		काष्ठा dma_async_tx_descriptor *tx;
		क्रमागत dma_ctrl_flags dma_flags = 0;
		अचिन्हित अक्षर coefs[MAX_DISKS];
		पूर्णांक i, j;

		/* run the p+q asynchronously */
		pr_debug("%s: (async) disks: %d len: %zu\n",
			 __func__, disks, len);

		/* convert source addresses being careful to collapse 'empty'
		 * sources and update the coefficients accordingly
		 */
		unmap->len = len;
		क्रम (i = 0, j = 0; i < src_cnt; i++) अणु
			अगर (blocks[i] == शून्य)
				जारी;
			unmap->addr[j] = dma_map_page(device->dev, blocks[i],
						offsets[i], len, DMA_TO_DEVICE);
			coefs[j] = raid6_gfexp[i];
			unmap->to_cnt++;
			j++;
		पूर्ण

		/*
		 * DMAs use destinations as sources,
		 * so use BIसूचीECTIONAL mapping
		 */
		unmap->bidi_cnt++;
		अगर (P(blocks, disks))
			unmap->addr[j++] = dma_map_page(device->dev, P(blocks, disks),
							P(offsets, disks),
							len, DMA_BIसूचीECTIONAL);
		अन्यथा अणु
			unmap->addr[j++] = 0;
			dma_flags |= DMA_PREP_PQ_DISABLE_P;
		पूर्ण

		unmap->bidi_cnt++;
		अगर (Q(blocks, disks))
			unmap->addr[j++] = dma_map_page(device->dev, Q(blocks, disks),
							Q(offsets, disks),
							len, DMA_BIसूचीECTIONAL);
		अन्यथा अणु
			unmap->addr[j++] = 0;
			dma_flags |= DMA_PREP_PQ_DISABLE_Q;
		पूर्ण

		tx = करो_async_gen_syndrome(chan, coefs, j, unmap, dma_flags, submit);
		dmaengine_unmap_put(unmap);
		वापस tx;
	पूर्ण

	dmaengine_unmap_put(unmap);

	/* run the pq synchronously */
	pr_debug("%s: (sync) disks: %d len: %zu\n", __func__, disks, len);

	/* रुको क्रम any prerequisite operations */
	async_tx_quiesce(&submit->depend_tx);

	अगर (!P(blocks, disks)) अणु
		P(blocks, disks) = pq_scribble_page;
		P(offsets, disks) = 0;
	पूर्ण
	अगर (!Q(blocks, disks)) अणु
		Q(blocks, disks) = pq_scribble_page;
		Q(offsets, disks) = 0;
	पूर्ण
	करो_sync_gen_syndrome(blocks, offsets, disks, len, submit);

	वापस शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(async_gen_syndrome);

अटल अंतरभूत काष्ठा dma_chan *
pq_val_chan(काष्ठा async_submit_ctl *submit, काष्ठा page **blocks, पूर्णांक disks, माप_प्रकार len)
अणु
	#अगर_घोषित CONFIG_ASYNC_TX_DISABLE_PQ_VAL_DMA
	वापस शून्य;
	#पूर्ण_अगर
	वापस async_tx_find_channel(submit, DMA_PQ_VAL, शून्य, 0,  blocks,
				     disks, len);
पूर्ण

/**
 * async_syndrome_val - asynchronously validate a raid6 syndrome
 * @blocks: source blocks from idx 0..disks-3, P @ disks-2 and Q @ disks-1
 * @offset: common offset पूर्णांकo each block (src and dest) to start transaction
 * @disks: number of blocks (including missing P or Q, see below)
 * @len: length of operation in bytes
 * @pqres: on val failure SUM_CHECK_P_RESULT and/or SUM_CHECK_Q_RESULT are set
 * @spare: temporary result buffer क्रम the synchronous हाल
 * @s_off: spare buffer page offset
 * @submit: submission / completion modअगरiers
 *
 * The same notes from async_gen_syndrome apply to the 'blocks',
 * and 'disks' parameters of this routine.  The synchronous path
 * requires a temporary result buffer and submit->scribble to be
 * specअगरied.
 */
काष्ठा dma_async_tx_descriptor *
async_syndrome_val(काष्ठा page **blocks, अचिन्हित पूर्णांक *offsets, पूर्णांक disks,
		   माप_प्रकार len, क्रमागत sum_check_flags *pqres, काष्ठा page *spare,
		   अचिन्हित पूर्णांक s_off, काष्ठा async_submit_ctl *submit)
अणु
	काष्ठा dma_chan *chan = pq_val_chan(submit, blocks, disks, len);
	काष्ठा dma_device *device = chan ? chan->device : शून्य;
	काष्ठा dma_async_tx_descriptor *tx;
	अचिन्हित अक्षर coefs[MAX_DISKS];
	क्रमागत dma_ctrl_flags dma_flags = submit->cb_fn ? DMA_PREP_INTERRUPT : 0;
	काष्ठा dmaengine_unmap_data *unmap = शून्य;

	BUG_ON(disks < 4 || disks > MAX_DISKS);

	अगर (device)
		unmap = dmaengine_get_unmap_data(device->dev, disks, GFP_NOWAIT);

	अगर (unmap && disks <= dma_maxpq(device, 0) &&
	    is_dma_pq_aligned_offs(device, offsets, disks, len)) अणु
		काष्ठा device *dev = device->dev;
		dma_addr_t pq[2];
		पूर्णांक i, j = 0, src_cnt = 0;

		pr_debug("%s: (async) disks: %d len: %zu\n",
			 __func__, disks, len);

		unmap->len = len;
		क्रम (i = 0; i < disks-2; i++)
			अगर (likely(blocks[i])) अणु
				unmap->addr[j] = dma_map_page(dev, blocks[i],
							      offsets[i], len,
							      DMA_TO_DEVICE);
				coefs[j] = raid6_gfexp[i];
				unmap->to_cnt++;
				src_cnt++;
				j++;
			पूर्ण

		अगर (!P(blocks, disks)) अणु
			pq[0] = 0;
			dma_flags |= DMA_PREP_PQ_DISABLE_P;
		पूर्ण अन्यथा अणु
			pq[0] = dma_map_page(dev, P(blocks, disks),
					     P(offsets, disks), len,
					     DMA_TO_DEVICE);
			unmap->addr[j++] = pq[0];
			unmap->to_cnt++;
		पूर्ण
		अगर (!Q(blocks, disks)) अणु
			pq[1] = 0;
			dma_flags |= DMA_PREP_PQ_DISABLE_Q;
		पूर्ण अन्यथा अणु
			pq[1] = dma_map_page(dev, Q(blocks, disks),
					     Q(offsets, disks), len,
					     DMA_TO_DEVICE);
			unmap->addr[j++] = pq[1];
			unmap->to_cnt++;
		पूर्ण

		अगर (submit->flags & ASYNC_TX_FENCE)
			dma_flags |= DMA_PREP_FENCE;
		क्रम (;;) अणु
			tx = device->device_prep_dma_pq_val(chan, pq,
							    unmap->addr,
							    src_cnt,
							    coefs,
							    len, pqres,
							    dma_flags);
			अगर (likely(tx))
				अवरोध;
			async_tx_quiesce(&submit->depend_tx);
			dma_async_issue_pending(chan);
		पूर्ण

		dma_set_unmap(tx, unmap);
		async_tx_submit(chan, tx, submit);
	पूर्ण अन्यथा अणु
		काष्ठा page *p_src = P(blocks, disks);
		अचिन्हित पूर्णांक p_off = P(offsets, disks);
		काष्ठा page *q_src = Q(blocks, disks);
		अचिन्हित पूर्णांक q_off = Q(offsets, disks);
		क्रमागत async_tx_flags flags_orig = submit->flags;
		dma_async_tx_callback cb_fn_orig = submit->cb_fn;
		व्योम *scribble = submit->scribble;
		व्योम *cb_param_orig = submit->cb_param;
		व्योम *p, *q, *s;

		pr_debug("%s: (sync) disks: %d len: %zu\n",
			 __func__, disks, len);

		/* caller must provide a temporary result buffer and
		 * allow the input parameters to be preserved
		 */
		BUG_ON(!spare || !scribble);

		/* रुको क्रम any prerequisite operations */
		async_tx_quiesce(&submit->depend_tx);

		/* recompute p and/or q पूर्णांकo the temporary buffer and then
		 * check to see the result matches the current value
		 */
		tx = शून्य;
		*pqres = 0;
		अगर (p_src) अणु
			init_async_submit(submit, ASYNC_TX_XOR_ZERO_DST, शून्य,
					  शून्य, शून्य, scribble);
			tx = async_xor_offs(spare, s_off,
					blocks, offsets, disks-2, len, submit);
			async_tx_quiesce(&tx);
			p = page_address(p_src) + p_off;
			s = page_address(spare) + s_off;
			*pqres |= !!स_भेद(p, s, len) << SUM_CHECK_P;
		पूर्ण

		अगर (q_src) अणु
			P(blocks, disks) = शून्य;
			Q(blocks, disks) = spare;
			Q(offsets, disks) = s_off;
			init_async_submit(submit, 0, शून्य, शून्य, शून्य, scribble);
			tx = async_gen_syndrome(blocks, offsets, disks,
					len, submit);
			async_tx_quiesce(&tx);
			q = page_address(q_src) + q_off;
			s = page_address(spare) + s_off;
			*pqres |= !!स_भेद(q, s, len) << SUM_CHECK_Q;
		पूर्ण

		/* restore P, Q and submit */
		P(blocks, disks) = p_src;
		P(offsets, disks) = p_off;
		Q(blocks, disks) = q_src;
		Q(offsets, disks) = q_off;

		submit->cb_fn = cb_fn_orig;
		submit->cb_param = cb_param_orig;
		submit->flags = flags_orig;
		async_tx_sync_epilog(submit);
		tx = शून्य;
	पूर्ण
	dmaengine_unmap_put(unmap);

	वापस tx;
पूर्ण
EXPORT_SYMBOL_GPL(async_syndrome_val);

अटल पूर्णांक __init async_pq_init(व्योम)
अणु
	pq_scribble_page = alloc_page(GFP_KERNEL);

	अगर (pq_scribble_page)
		वापस 0;

	pr_err("%s: failed to allocate required spare page\n", __func__);

	वापस -ENOMEM;
पूर्ण

अटल व्योम __निकास async_pq_निकास(व्योम)
अणु
	__मुक्त_page(pq_scribble_page);
पूर्ण

module_init(async_pq_init);
module_निकास(async_pq_निकास);

MODULE_DESCRIPTION("asynchronous raid6 syndrome generation/validation");
MODULE_LICENSE("GPL");
