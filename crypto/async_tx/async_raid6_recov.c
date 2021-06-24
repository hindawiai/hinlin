<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Asynchronous RAID-6 recovery calculations ASYNC_TX API.
 * Copyright(c) 2009 Intel Corporation
 *
 * based on raid6recov.c:
 *   Copyright 2002 H. Peter Anvin
 */
#समावेश <linux/kernel.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/raid/pq.h>
#समावेश <linux/async_tx.h>
#समावेश <linux/dmaengine.h>

अटल काष्ठा dma_async_tx_descriptor *
async_sum_product(काष्ठा page *dest, अचिन्हित पूर्णांक d_off,
		काष्ठा page **srcs, अचिन्हित पूर्णांक *src_offs, अचिन्हित अक्षर *coef,
		माप_प्रकार len, काष्ठा async_submit_ctl *submit)
अणु
	काष्ठा dma_chan *chan = async_tx_find_channel(submit, DMA_PQ,
						      &dest, 1, srcs, 2, len);
	काष्ठा dma_device *dma = chan ? chan->device : शून्य;
	काष्ठा dmaengine_unmap_data *unmap = शून्य;
	स्थिर u8 *amul, *bmul;
	u8 ax, bx;
	u8 *a, *b, *c;

	अगर (dma)
		unmap = dmaengine_get_unmap_data(dma->dev, 3, GFP_NOWAIT);

	अगर (unmap) अणु
		काष्ठा device *dev = dma->dev;
		dma_addr_t pq[2];
		काष्ठा dma_async_tx_descriptor *tx;
		क्रमागत dma_ctrl_flags dma_flags = DMA_PREP_PQ_DISABLE_P;

		अगर (submit->flags & ASYNC_TX_FENCE)
			dma_flags |= DMA_PREP_FENCE;
		unmap->addr[0] = dma_map_page(dev, srcs[0], src_offs[0],
						len, DMA_TO_DEVICE);
		unmap->addr[1] = dma_map_page(dev, srcs[1], src_offs[1],
						len, DMA_TO_DEVICE);
		unmap->to_cnt = 2;

		unmap->addr[2] = dma_map_page(dev, dest, d_off,
						len, DMA_BIसूचीECTIONAL);
		unmap->bidi_cnt = 1;
		/* engine only looks at Q, but expects it to follow P */
		pq[1] = unmap->addr[2];

		unmap->len = len;
		tx = dma->device_prep_dma_pq(chan, pq, unmap->addr, 2, coef,
					     len, dma_flags);
		अगर (tx) अणु
			dma_set_unmap(tx, unmap);
			async_tx_submit(chan, tx, submit);
			dmaengine_unmap_put(unmap);
			वापस tx;
		पूर्ण

		/* could not get a descriptor, unmap and fall through to
		 * the synchronous path
		 */
		dmaengine_unmap_put(unmap);
	पूर्ण

	/* run the operation synchronously */
	async_tx_quiesce(&submit->depend_tx);
	amul = raid6_gfmul[coef[0]];
	bmul = raid6_gfmul[coef[1]];
	a = page_address(srcs[0]) + src_offs[0];
	b = page_address(srcs[1]) + src_offs[1];
	c = page_address(dest) + d_off;

	जबतक (len--) अणु
		ax    = amul[*a++];
		bx    = bmul[*b++];
		*c++ = ax ^ bx;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल काष्ठा dma_async_tx_descriptor *
async_mult(काष्ठा page *dest, अचिन्हित पूर्णांक d_off, काष्ठा page *src,
		अचिन्हित पूर्णांक s_off, u8 coef, माप_प्रकार len,
		काष्ठा async_submit_ctl *submit)
अणु
	काष्ठा dma_chan *chan = async_tx_find_channel(submit, DMA_PQ,
						      &dest, 1, &src, 1, len);
	काष्ठा dma_device *dma = chan ? chan->device : शून्य;
	काष्ठा dmaengine_unmap_data *unmap = शून्य;
	स्थिर u8 *qmul; /* Q multiplier table */
	u8 *d, *s;

	अगर (dma)
		unmap = dmaengine_get_unmap_data(dma->dev, 3, GFP_NOWAIT);

	अगर (unmap) अणु
		dma_addr_t dma_dest[2];
		काष्ठा device *dev = dma->dev;
		काष्ठा dma_async_tx_descriptor *tx;
		क्रमागत dma_ctrl_flags dma_flags = DMA_PREP_PQ_DISABLE_P;

		अगर (submit->flags & ASYNC_TX_FENCE)
			dma_flags |= DMA_PREP_FENCE;
		unmap->addr[0] = dma_map_page(dev, src, s_off,
						len, DMA_TO_DEVICE);
		unmap->to_cnt++;
		unmap->addr[1] = dma_map_page(dev, dest, d_off,
						len, DMA_BIसूचीECTIONAL);
		dma_dest[1] = unmap->addr[1];
		unmap->bidi_cnt++;
		unmap->len = len;

		/* this looks funny, but the engine looks क्रम Q at
		 * dma_dest[1] and ignores dma_dest[0] as a dest
		 * due to DMA_PREP_PQ_DISABLE_P
		 */
		tx = dma->device_prep_dma_pq(chan, dma_dest, unmap->addr,
					     1, &coef, len, dma_flags);

		अगर (tx) अणु
			dma_set_unmap(tx, unmap);
			dmaengine_unmap_put(unmap);
			async_tx_submit(chan, tx, submit);
			वापस tx;
		पूर्ण

		/* could not get a descriptor, unmap and fall through to
		 * the synchronous path
		 */
		dmaengine_unmap_put(unmap);
	पूर्ण

	/* no channel available, or failed to allocate a descriptor, so
	 * perक्रमm the operation synchronously
	 */
	async_tx_quiesce(&submit->depend_tx);
	qmul  = raid6_gfmul[coef];
	d = page_address(dest) + d_off;
	s = page_address(src) + s_off;

	जबतक (len--)
		*d++ = qmul[*s++];

	वापस शून्य;
पूर्ण

अटल काष्ठा dma_async_tx_descriptor *
__2data_recov_4(पूर्णांक disks, माप_प्रकार bytes, पूर्णांक faila, पूर्णांक failb,
		काष्ठा page **blocks, अचिन्हित पूर्णांक *offs,
		काष्ठा async_submit_ctl *submit)
अणु
	काष्ठा dma_async_tx_descriptor *tx = शून्य;
	काष्ठा page *p, *q, *a, *b;
	अचिन्हित पूर्णांक p_off, q_off, a_off, b_off;
	काष्ठा page *srcs[2];
	अचिन्हित पूर्णांक src_offs[2];
	अचिन्हित अक्षर coef[2];
	क्रमागत async_tx_flags flags = submit->flags;
	dma_async_tx_callback cb_fn = submit->cb_fn;
	व्योम *cb_param = submit->cb_param;
	व्योम *scribble = submit->scribble;

	p = blocks[disks-2];
	p_off = offs[disks-2];
	q = blocks[disks-1];
	q_off = offs[disks-1];

	a = blocks[faila];
	a_off = offs[faila];
	b = blocks[failb];
	b_off = offs[failb];

	/* in the 4 disk हाल P + Pxy == P and Q + Qxy == Q */
	/* Dx = A*(P+Pxy) + B*(Q+Qxy) */
	srcs[0] = p;
	src_offs[0] = p_off;
	srcs[1] = q;
	src_offs[1] = q_off;
	coef[0] = raid6_gfexi[failb-faila];
	coef[1] = raid6_gfinv[raid6_gfexp[faila]^raid6_gfexp[failb]];
	init_async_submit(submit, ASYNC_TX_FENCE, tx, शून्य, शून्य, scribble);
	tx = async_sum_product(b, b_off, srcs, src_offs, coef, bytes, submit);

	/* Dy = P+Pxy+Dx */
	srcs[0] = p;
	src_offs[0] = p_off;
	srcs[1] = b;
	src_offs[1] = b_off;
	init_async_submit(submit, flags | ASYNC_TX_XOR_ZERO_DST, tx, cb_fn,
			  cb_param, scribble);
	tx = async_xor_offs(a, a_off, srcs, src_offs, 2, bytes, submit);

	वापस tx;

पूर्ण

अटल काष्ठा dma_async_tx_descriptor *
__2data_recov_5(पूर्णांक disks, माप_प्रकार bytes, पूर्णांक faila, पूर्णांक failb,
		काष्ठा page **blocks, अचिन्हित पूर्णांक *offs,
		काष्ठा async_submit_ctl *submit)
अणु
	काष्ठा dma_async_tx_descriptor *tx = शून्य;
	काष्ठा page *p, *q, *g, *dp, *dq;
	अचिन्हित पूर्णांक p_off, q_off, g_off, dp_off, dq_off;
	काष्ठा page *srcs[2];
	अचिन्हित पूर्णांक src_offs[2];
	अचिन्हित अक्षर coef[2];
	क्रमागत async_tx_flags flags = submit->flags;
	dma_async_tx_callback cb_fn = submit->cb_fn;
	व्योम *cb_param = submit->cb_param;
	व्योम *scribble = submit->scribble;
	पूर्णांक good_srcs, good, i;

	good_srcs = 0;
	good = -1;
	क्रम (i = 0; i < disks-2; i++) अणु
		अगर (blocks[i] == शून्य)
			जारी;
		अगर (i == faila || i == failb)
			जारी;
		good = i;
		good_srcs++;
	पूर्ण
	BUG_ON(good_srcs > 1);

	p = blocks[disks-2];
	p_off = offs[disks-2];
	q = blocks[disks-1];
	q_off = offs[disks-1];
	g = blocks[good];
	g_off = offs[good];

	/* Compute syndrome with zero क्रम the missing data pages
	 * Use the dead data pages as temporary storage क्रम delta p and
	 * delta q
	 */
	dp = blocks[faila];
	dp_off = offs[faila];
	dq = blocks[failb];
	dq_off = offs[failb];

	init_async_submit(submit, ASYNC_TX_FENCE, tx, शून्य, शून्य, scribble);
	tx = async_स_नकल(dp, g, dp_off, g_off, bytes, submit);
	init_async_submit(submit, ASYNC_TX_FENCE, tx, शून्य, शून्य, scribble);
	tx = async_mult(dq, dq_off, g, g_off,
			raid6_gfexp[good], bytes, submit);

	/* compute P + Pxy */
	srcs[0] = dp;
	src_offs[0] = dp_off;
	srcs[1] = p;
	src_offs[1] = p_off;
	init_async_submit(submit, ASYNC_TX_FENCE|ASYNC_TX_XOR_DROP_DST, tx,
			  शून्य, शून्य, scribble);
	tx = async_xor_offs(dp, dp_off, srcs, src_offs, 2, bytes, submit);

	/* compute Q + Qxy */
	srcs[0] = dq;
	src_offs[0] = dq_off;
	srcs[1] = q;
	src_offs[1] = q_off;
	init_async_submit(submit, ASYNC_TX_FENCE|ASYNC_TX_XOR_DROP_DST, tx,
			  शून्य, शून्य, scribble);
	tx = async_xor_offs(dq, dq_off, srcs, src_offs, 2, bytes, submit);

	/* Dx = A*(P+Pxy) + B*(Q+Qxy) */
	srcs[0] = dp;
	src_offs[0] = dp_off;
	srcs[1] = dq;
	src_offs[1] = dq_off;
	coef[0] = raid6_gfexi[failb-faila];
	coef[1] = raid6_gfinv[raid6_gfexp[faila]^raid6_gfexp[failb]];
	init_async_submit(submit, ASYNC_TX_FENCE, tx, शून्य, शून्य, scribble);
	tx = async_sum_product(dq, dq_off, srcs, src_offs, coef, bytes, submit);

	/* Dy = P+Pxy+Dx */
	srcs[0] = dp;
	src_offs[0] = dp_off;
	srcs[1] = dq;
	src_offs[1] = dq_off;
	init_async_submit(submit, flags | ASYNC_TX_XOR_DROP_DST, tx, cb_fn,
			  cb_param, scribble);
	tx = async_xor_offs(dp, dp_off, srcs, src_offs, 2, bytes, submit);

	वापस tx;
पूर्ण

अटल काष्ठा dma_async_tx_descriptor *
__2data_recov_n(पूर्णांक disks, माप_प्रकार bytes, पूर्णांक faila, पूर्णांक failb,
	      काष्ठा page **blocks, अचिन्हित पूर्णांक *offs,
		  काष्ठा async_submit_ctl *submit)
अणु
	काष्ठा dma_async_tx_descriptor *tx = शून्य;
	काष्ठा page *p, *q, *dp, *dq;
	अचिन्हित पूर्णांक p_off, q_off, dp_off, dq_off;
	काष्ठा page *srcs[2];
	अचिन्हित पूर्णांक src_offs[2];
	अचिन्हित अक्षर coef[2];
	क्रमागत async_tx_flags flags = submit->flags;
	dma_async_tx_callback cb_fn = submit->cb_fn;
	व्योम *cb_param = submit->cb_param;
	व्योम *scribble = submit->scribble;

	p = blocks[disks-2];
	p_off = offs[disks-2];
	q = blocks[disks-1];
	q_off = offs[disks-1];

	/* Compute syndrome with zero क्रम the missing data pages
	 * Use the dead data pages as temporary storage क्रम
	 * delta p and delta q
	 */
	dp = blocks[faila];
	dp_off = offs[faila];
	blocks[faila] = शून्य;
	blocks[disks-2] = dp;
	offs[disks-2] = dp_off;
	dq = blocks[failb];
	dq_off = offs[failb];
	blocks[failb] = शून्य;
	blocks[disks-1] = dq;
	offs[disks-1] = dq_off;

	init_async_submit(submit, ASYNC_TX_FENCE, tx, शून्य, शून्य, scribble);
	tx = async_gen_syndrome(blocks, offs, disks, bytes, submit);

	/* Restore poपूर्णांकer table */
	blocks[faila]   = dp;
	offs[faila] = dp_off;
	blocks[failb]   = dq;
	offs[failb] = dq_off;
	blocks[disks-2] = p;
	offs[disks-2] = p_off;
	blocks[disks-1] = q;
	offs[disks-1] = q_off;

	/* compute P + Pxy */
	srcs[0] = dp;
	src_offs[0] = dp_off;
	srcs[1] = p;
	src_offs[1] = p_off;
	init_async_submit(submit, ASYNC_TX_FENCE|ASYNC_TX_XOR_DROP_DST, tx,
			  शून्य, शून्य, scribble);
	tx = async_xor_offs(dp, dp_off, srcs, src_offs, 2, bytes, submit);

	/* compute Q + Qxy */
	srcs[0] = dq;
	src_offs[0] = dq_off;
	srcs[1] = q;
	src_offs[1] = q_off;
	init_async_submit(submit, ASYNC_TX_FENCE|ASYNC_TX_XOR_DROP_DST, tx,
			  शून्य, शून्य, scribble);
	tx = async_xor_offs(dq, dq_off, srcs, src_offs, 2, bytes, submit);

	/* Dx = A*(P+Pxy) + B*(Q+Qxy) */
	srcs[0] = dp;
	src_offs[0] = dp_off;
	srcs[1] = dq;
	src_offs[1] = dq_off;
	coef[0] = raid6_gfexi[failb-faila];
	coef[1] = raid6_gfinv[raid6_gfexp[faila]^raid6_gfexp[failb]];
	init_async_submit(submit, ASYNC_TX_FENCE, tx, शून्य, शून्य, scribble);
	tx = async_sum_product(dq, dq_off, srcs, src_offs, coef, bytes, submit);

	/* Dy = P+Pxy+Dx */
	srcs[0] = dp;
	src_offs[0] = dp_off;
	srcs[1] = dq;
	src_offs[1] = dq_off;
	init_async_submit(submit, flags | ASYNC_TX_XOR_DROP_DST, tx, cb_fn,
			  cb_param, scribble);
	tx = async_xor_offs(dp, dp_off, srcs, src_offs, 2, bytes, submit);

	वापस tx;
पूर्ण

/**
 * async_raid6_2data_recov - asynchronously calculate two missing data blocks
 * @disks: number of disks in the RAID-6 array
 * @bytes: block size
 * @faila: first failed drive index
 * @failb: second failed drive index
 * @blocks: array of source poपूर्णांकers where the last two entries are p and q
 * @offs: array of offset क्रम pages in blocks
 * @submit: submission/completion modअगरiers
 */
काष्ठा dma_async_tx_descriptor *
async_raid6_2data_recov(पूर्णांक disks, माप_प्रकार bytes, पूर्णांक faila, पूर्णांक failb,
			काष्ठा page **blocks, अचिन्हित पूर्णांक *offs,
			काष्ठा async_submit_ctl *submit)
अणु
	व्योम *scribble = submit->scribble;
	पूर्णांक non_zero_srcs, i;

	BUG_ON(faila == failb);
	अगर (failb < faila)
		swap(faila, failb);

	pr_debug("%s: disks: %d len: %zu\n", __func__, disks, bytes);

	/* अगर a dma resource is not available or a scribble buffer is not
	 * available punt to the synchronous path.  In the 'dma not
	 * available' हाल be sure to use the scribble buffer to
	 * preserve the content of 'blocks' as the caller पूर्णांकended.
	 */
	अगर (!async_dma_find_channel(DMA_PQ) || !scribble) अणु
		व्योम **ptrs = scribble ? scribble : (व्योम **) blocks;

		async_tx_quiesce(&submit->depend_tx);
		क्रम (i = 0; i < disks; i++)
			अगर (blocks[i] == शून्य)
				ptrs[i] = (व्योम *) raid6_empty_zero_page;
			अन्यथा
				ptrs[i] = page_address(blocks[i]) + offs[i];

		raid6_2data_recov(disks, bytes, faila, failb, ptrs);

		async_tx_sync_epilog(submit);

		वापस शून्य;
	पूर्ण

	non_zero_srcs = 0;
	क्रम (i = 0; i < disks-2 && non_zero_srcs < 4; i++)
		अगर (blocks[i])
			non_zero_srcs++;
	चयन (non_zero_srcs) अणु
	हाल 0:
	हाल 1:
		/* There must be at least 2 sources - the failed devices. */
		BUG();

	हाल 2:
		/* dma devices करो not unअगरormly understand a zero source pq
		 * operation (in contrast to the synchronous हाल), so
		 * explicitly handle the special हाल of a 4 disk array with
		 * both data disks missing.
		 */
		वापस __2data_recov_4(disks, bytes, faila, failb,
				blocks, offs, submit);
	हाल 3:
		/* dma devices करो not unअगरormly understand a single
		 * source pq operation (in contrast to the synchronous
		 * हाल), so explicitly handle the special हाल of a 5 disk
		 * array with 2 of 3 data disks missing.
		 */
		वापस __2data_recov_5(disks, bytes, faila, failb,
				blocks, offs, submit);
	शेष:
		वापस __2data_recov_n(disks, bytes, faila, failb,
				blocks, offs, submit);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(async_raid6_2data_recov);

/**
 * async_raid6_datap_recov - asynchronously calculate a data and the 'p' block
 * @disks: number of disks in the RAID-6 array
 * @bytes: block size
 * @faila: failed drive index
 * @blocks: array of source poपूर्णांकers where the last two entries are p and q
 * @offs: array of offset क्रम pages in blocks
 * @submit: submission/completion modअगरiers
 */
काष्ठा dma_async_tx_descriptor *
async_raid6_datap_recov(पूर्णांक disks, माप_प्रकार bytes, पूर्णांक faila,
			काष्ठा page **blocks, अचिन्हित पूर्णांक *offs,
			काष्ठा async_submit_ctl *submit)
अणु
	काष्ठा dma_async_tx_descriptor *tx = शून्य;
	काष्ठा page *p, *q, *dq;
	अचिन्हित पूर्णांक p_off, q_off, dq_off;
	u8 coef;
	क्रमागत async_tx_flags flags = submit->flags;
	dma_async_tx_callback cb_fn = submit->cb_fn;
	व्योम *cb_param = submit->cb_param;
	व्योम *scribble = submit->scribble;
	पूर्णांक good_srcs, good, i;
	काष्ठा page *srcs[2];
	अचिन्हित पूर्णांक src_offs[2];

	pr_debug("%s: disks: %d len: %zu\n", __func__, disks, bytes);

	/* अगर a dma resource is not available or a scribble buffer is not
	 * available punt to the synchronous path.  In the 'dma not
	 * available' हाल be sure to use the scribble buffer to
	 * preserve the content of 'blocks' as the caller पूर्णांकended.
	 */
	अगर (!async_dma_find_channel(DMA_PQ) || !scribble) अणु
		व्योम **ptrs = scribble ? scribble : (व्योम **) blocks;

		async_tx_quiesce(&submit->depend_tx);
		क्रम (i = 0; i < disks; i++)
			अगर (blocks[i] == शून्य)
				ptrs[i] = (व्योम*)raid6_empty_zero_page;
			अन्यथा
				ptrs[i] = page_address(blocks[i]) + offs[i];

		raid6_datap_recov(disks, bytes, faila, ptrs);

		async_tx_sync_epilog(submit);

		वापस शून्य;
	पूर्ण

	good_srcs = 0;
	good = -1;
	क्रम (i = 0; i < disks-2; i++) अणु
		अगर (i == faila)
			जारी;
		अगर (blocks[i]) अणु
			good = i;
			good_srcs++;
			अगर (good_srcs > 1)
				अवरोध;
		पूर्ण
	पूर्ण
	BUG_ON(good_srcs == 0);

	p = blocks[disks-2];
	p_off = offs[disks-2];
	q = blocks[disks-1];
	q_off = offs[disks-1];

	/* Compute syndrome with zero क्रम the missing data page
	 * Use the dead data page as temporary storage क्रम delta q
	 */
	dq = blocks[faila];
	dq_off = offs[faila];
	blocks[faila] = शून्य;
	blocks[disks-1] = dq;
	offs[disks-1] = dq_off;

	/* in the 4-disk हाल we only need to perक्रमm a single source
	 * multiplication with the one good data block.
	 */
	अगर (good_srcs == 1) अणु
		काष्ठा page *g = blocks[good];
		अचिन्हित पूर्णांक g_off = offs[good];

		init_async_submit(submit, ASYNC_TX_FENCE, tx, शून्य, शून्य,
				  scribble);
		tx = async_स_नकल(p, g, p_off, g_off, bytes, submit);

		init_async_submit(submit, ASYNC_TX_FENCE, tx, शून्य, शून्य,
				  scribble);
		tx = async_mult(dq, dq_off, g, g_off,
				raid6_gfexp[good], bytes, submit);
	पूर्ण अन्यथा अणु
		init_async_submit(submit, ASYNC_TX_FENCE, tx, शून्य, शून्य,
				  scribble);
		tx = async_gen_syndrome(blocks, offs, disks, bytes, submit);
	पूर्ण

	/* Restore poपूर्णांकer table */
	blocks[faila]   = dq;
	offs[faila] = dq_off;
	blocks[disks-1] = q;
	offs[disks-1] = q_off;

	/* calculate g^अणु-failaपूर्ण */
	coef = raid6_gfinv[raid6_gfexp[faila]];

	srcs[0] = dq;
	src_offs[0] = dq_off;
	srcs[1] = q;
	src_offs[1] = q_off;
	init_async_submit(submit, ASYNC_TX_FENCE|ASYNC_TX_XOR_DROP_DST, tx,
			  शून्य, शून्य, scribble);
	tx = async_xor_offs(dq, dq_off, srcs, src_offs, 2, bytes, submit);

	init_async_submit(submit, ASYNC_TX_FENCE, tx, शून्य, शून्य, scribble);
	tx = async_mult(dq, dq_off, dq, dq_off, coef, bytes, submit);

	srcs[0] = p;
	src_offs[0] = p_off;
	srcs[1] = dq;
	src_offs[1] = dq_off;
	init_async_submit(submit, flags | ASYNC_TX_XOR_DROP_DST, tx, cb_fn,
			  cb_param, scribble);
	tx = async_xor_offs(p, p_off, srcs, src_offs, 2, bytes, submit);

	वापस tx;
पूर्ण
EXPORT_SYMBOL_GPL(async_raid6_datap_recov);

MODULE_AUTHOR("Dan Williams <dan.j.williams@intel.com>");
MODULE_DESCRIPTION("asynchronous RAID-6 recovery api");
MODULE_LICENSE("GPL");
