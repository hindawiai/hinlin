<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * xor offload engine api
 *
 * Copyright तऊ 2006, Intel Corporation.
 *
 *      Dan Williams <dan.j.williams@पूर्णांकel.com>
 *
 *      with architecture considerations by:
 *      Neil Brown <neilb@suse.de>
 *      Jeff Garzik <jeff@garzik.org>
 */
#समावेश <linux/kernel.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/mm.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/raid/xor.h>
#समावेश <linux/async_tx.h>

/* करो_async_xor - dma map the pages and perक्रमm the xor with an engine */
अटल __async_अंतरभूत काष्ठा dma_async_tx_descriptor *
करो_async_xor(काष्ठा dma_chan *chan, काष्ठा dmaengine_unmap_data *unmap,
	     काष्ठा async_submit_ctl *submit)
अणु
	काष्ठा dma_device *dma = chan->device;
	काष्ठा dma_async_tx_descriptor *tx = शून्य;
	dma_async_tx_callback cb_fn_orig = submit->cb_fn;
	व्योम *cb_param_orig = submit->cb_param;
	क्रमागत async_tx_flags flags_orig = submit->flags;
	क्रमागत dma_ctrl_flags dma_flags = 0;
	पूर्णांक src_cnt = unmap->to_cnt;
	पूर्णांक xor_src_cnt;
	dma_addr_t dma_dest = unmap->addr[unmap->to_cnt];
	dma_addr_t *src_list = unmap->addr;

	जबतक (src_cnt) अणु
		dma_addr_t पंचांगp;

		submit->flags = flags_orig;
		xor_src_cnt = min(src_cnt, (पूर्णांक)dma->max_xor);
		/* अगर we are submitting additional xors, leave the chain खोलो
		 * and clear the callback parameters
		 */
		अगर (src_cnt > xor_src_cnt) अणु
			submit->flags &= ~ASYNC_TX_ACK;
			submit->flags |= ASYNC_TX_FENCE;
			submit->cb_fn = शून्य;
			submit->cb_param = शून्य;
		पूर्ण अन्यथा अणु
			submit->cb_fn = cb_fn_orig;
			submit->cb_param = cb_param_orig;
		पूर्ण
		अगर (submit->cb_fn)
			dma_flags |= DMA_PREP_INTERRUPT;
		अगर (submit->flags & ASYNC_TX_FENCE)
			dma_flags |= DMA_PREP_FENCE;

		/* Drivers क्रमce क्रमward progress in हाल they can not provide a
		 * descriptor
		 */
		पंचांगp = src_list[0];
		अगर (src_list > unmap->addr)
			src_list[0] = dma_dest;
		tx = dma->device_prep_dma_xor(chan, dma_dest, src_list,
					      xor_src_cnt, unmap->len,
					      dma_flags);

		अगर (unlikely(!tx))
			async_tx_quiesce(&submit->depend_tx);

		/* spin रुको क्रम the preceding transactions to complete */
		जबतक (unlikely(!tx)) अणु
			dma_async_issue_pending(chan);
			tx = dma->device_prep_dma_xor(chan, dma_dest,
						      src_list,
						      xor_src_cnt, unmap->len,
						      dma_flags);
		पूर्ण
		src_list[0] = पंचांगp;

		dma_set_unmap(tx, unmap);
		async_tx_submit(chan, tx, submit);
		submit->depend_tx = tx;

		अगर (src_cnt > xor_src_cnt) अणु
			/* drop completed sources */
			src_cnt -= xor_src_cnt;
			/* use the पूर्णांकermediate result a source */
			src_cnt++;
			src_list += xor_src_cnt - 1;
		पूर्ण अन्यथा
			अवरोध;
	पूर्ण

	वापस tx;
पूर्ण

अटल व्योम
करो_sync_xor_offs(काष्ठा page *dest, अचिन्हित पूर्णांक offset,
		काष्ठा page **src_list, अचिन्हित पूर्णांक *src_offs,
	    पूर्णांक src_cnt, माप_प्रकार len, काष्ठा async_submit_ctl *submit)
अणु
	पूर्णांक i;
	पूर्णांक xor_src_cnt = 0;
	पूर्णांक src_off = 0;
	व्योम *dest_buf;
	व्योम **srcs;

	अगर (submit->scribble)
		srcs = submit->scribble;
	अन्यथा
		srcs = (व्योम **) src_list;

	/* convert to buffer poपूर्णांकers */
	क्रम (i = 0; i < src_cnt; i++)
		अगर (src_list[i])
			srcs[xor_src_cnt++] = page_address(src_list[i]) +
				(src_offs ? src_offs[i] : offset);
	src_cnt = xor_src_cnt;
	/* set destination address */
	dest_buf = page_address(dest) + offset;

	अगर (submit->flags & ASYNC_TX_XOR_ZERO_DST)
		स_रखो(dest_buf, 0, len);

	जबतक (src_cnt > 0) अणु
		/* process up to 'MAX_XOR_BLOCKS' sources */
		xor_src_cnt = min(src_cnt, MAX_XOR_BLOCKS);
		xor_blocks(xor_src_cnt, len, dest_buf, &srcs[src_off]);

		/* drop completed sources */
		src_cnt -= xor_src_cnt;
		src_off += xor_src_cnt;
	पूर्ण

	async_tx_sync_epilog(submit);
पूर्ण

अटल अंतरभूत bool
dma_xor_aligned_offsets(काष्ठा dma_device *device, अचिन्हित पूर्णांक offset,
		अचिन्हित पूर्णांक *src_offs, पूर्णांक src_cnt, पूर्णांक len)
अणु
	पूर्णांक i;

	अगर (!is_dma_xor_aligned(device, offset, 0, len))
		वापस false;

	अगर (!src_offs)
		वापस true;

	क्रम (i = 0; i < src_cnt; i++) अणु
		अगर (!is_dma_xor_aligned(device, src_offs[i], 0, len))
			वापस false;
	पूर्ण
	वापस true;
पूर्ण

/**
 * async_xor_offs - attempt to xor a set of blocks with a dma engine.
 * @dest: destination page
 * @offset: dst offset to start transaction
 * @src_list: array of source pages
 * @src_offs: array of source pages offset, शून्य means common src/dst offset
 * @src_cnt: number of source pages
 * @len: length in bytes
 * @submit: submission / completion modअगरiers
 *
 * honored flags: ASYNC_TX_ACK, ASYNC_TX_XOR_ZERO_DST, ASYNC_TX_XOR_DROP_DST
 *
 * xor_blocks always uses the dest as a source so the
 * ASYNC_TX_XOR_ZERO_DST flag must be set to not include dest data in
 * the calculation.  The assumption with dma eninges is that they only
 * use the destination buffer as a source when it is explicity specअगरied
 * in the source list.
 *
 * src_list note: अगर the dest is also a source it must be at index zero.
 * The contents of this array will be overwritten अगर a scribble region
 * is not specअगरied.
 */
काष्ठा dma_async_tx_descriptor *
async_xor_offs(काष्ठा page *dest, अचिन्हित पूर्णांक offset,
		काष्ठा page **src_list, अचिन्हित पूर्णांक *src_offs,
		पूर्णांक src_cnt, माप_प्रकार len, काष्ठा async_submit_ctl *submit)
अणु
	काष्ठा dma_chan *chan = async_tx_find_channel(submit, DMA_XOR,
						      &dest, 1, src_list,
						      src_cnt, len);
	काष्ठा dma_device *device = chan ? chan->device : शून्य;
	काष्ठा dmaengine_unmap_data *unmap = शून्य;

	BUG_ON(src_cnt <= 1);

	अगर (device)
		unmap = dmaengine_get_unmap_data(device->dev, src_cnt+1, GFP_NOWAIT);

	अगर (unmap && dma_xor_aligned_offsets(device, offset,
				src_offs, src_cnt, len)) अणु
		काष्ठा dma_async_tx_descriptor *tx;
		पूर्णांक i, j;

		/* run the xor asynchronously */
		pr_debug("%s (async): len: %zu\n", __func__, len);

		unmap->len = len;
		क्रम (i = 0, j = 0; i < src_cnt; i++) अणु
			अगर (!src_list[i])
				जारी;
			unmap->to_cnt++;
			unmap->addr[j++] = dma_map_page(device->dev, src_list[i],
					src_offs ? src_offs[i] : offset,
					len, DMA_TO_DEVICE);
		पूर्ण

		/* map it bidirectional as it may be re-used as a source */
		unmap->addr[j] = dma_map_page(device->dev, dest, offset, len,
					      DMA_BIसूचीECTIONAL);
		unmap->bidi_cnt = 1;

		tx = करो_async_xor(chan, unmap, submit);
		dmaengine_unmap_put(unmap);
		वापस tx;
	पूर्ण अन्यथा अणु
		dmaengine_unmap_put(unmap);
		/* run the xor synchronously */
		pr_debug("%s (sync): len: %zu\n", __func__, len);
		WARN_ONCE(chan, "%s: no space for dma address conversion\n",
			  __func__);

		/* in the sync हाल the dest is an implied source
		 * (assumes the dest is the first source)
		 */
		अगर (submit->flags & ASYNC_TX_XOR_DROP_DST) अणु
			src_cnt--;
			src_list++;
			अगर (src_offs)
				src_offs++;
		पूर्ण

		/* रुको क्रम any prerequisite operations */
		async_tx_quiesce(&submit->depend_tx);

		करो_sync_xor_offs(dest, offset, src_list, src_offs,
				src_cnt, len, submit);

		वापस शून्य;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(async_xor_offs);

/**
 * async_xor - attempt to xor a set of blocks with a dma engine.
 * @dest: destination page
 * @src_list: array of source pages
 * @offset: common src/dst offset to start transaction
 * @src_cnt: number of source pages
 * @len: length in bytes
 * @submit: submission / completion modअगरiers
 *
 * honored flags: ASYNC_TX_ACK, ASYNC_TX_XOR_ZERO_DST, ASYNC_TX_XOR_DROP_DST
 *
 * xor_blocks always uses the dest as a source so the
 * ASYNC_TX_XOR_ZERO_DST flag must be set to not include dest data in
 * the calculation.  The assumption with dma eninges is that they only
 * use the destination buffer as a source when it is explicity specअगरied
 * in the source list.
 *
 * src_list note: अगर the dest is also a source it must be at index zero.
 * The contents of this array will be overwritten अगर a scribble region
 * is not specअगरied.
 */
काष्ठा dma_async_tx_descriptor *
async_xor(काष्ठा page *dest, काष्ठा page **src_list, अचिन्हित पूर्णांक offset,
	  पूर्णांक src_cnt, माप_प्रकार len, काष्ठा async_submit_ctl *submit)
अणु
	वापस async_xor_offs(dest, offset, src_list, शून्य,
			src_cnt, len, submit);
पूर्ण
EXPORT_SYMBOL_GPL(async_xor);

अटल पूर्णांक page_is_zero(काष्ठा page *p, अचिन्हित पूर्णांक offset, माप_प्रकार len)
अणु
	वापस !स_प्रथम_inv(page_address(p) + offset, 0, len);
पूर्ण

अटल अंतरभूत काष्ठा dma_chan *
xor_val_chan(काष्ठा async_submit_ctl *submit, काष्ठा page *dest,
		 काष्ठा page **src_list, पूर्णांक src_cnt, माप_प्रकार len)
अणु
	#अगर_घोषित CONFIG_ASYNC_TX_DISABLE_XOR_VAL_DMA
	वापस शून्य;
	#पूर्ण_अगर
	वापस async_tx_find_channel(submit, DMA_XOR_VAL, &dest, 1, src_list,
				     src_cnt, len);
पूर्ण

/**
 * async_xor_val_offs - attempt a xor parity check with a dma engine.
 * @dest: destination page used अगर the xor is perक्रमmed synchronously
 * @offset: des offset in pages to start transaction
 * @src_list: array of source pages
 * @src_offs: array of source pages offset, शून्य means common src/det offset
 * @src_cnt: number of source pages
 * @len: length in bytes
 * @result: 0 अगर sum == 0 अन्यथा non-zero
 * @submit: submission / completion modअगरiers
 *
 * honored flags: ASYNC_TX_ACK
 *
 * src_list note: अगर the dest is also a source it must be at index zero.
 * The contents of this array will be overwritten अगर a scribble region
 * is not specअगरied.
 */
काष्ठा dma_async_tx_descriptor *
async_xor_val_offs(काष्ठा page *dest, अचिन्हित पूर्णांक offset,
		काष्ठा page **src_list, अचिन्हित पूर्णांक *src_offs,
		पूर्णांक src_cnt, माप_प्रकार len, क्रमागत sum_check_flags *result,
		काष्ठा async_submit_ctl *submit)
अणु
	काष्ठा dma_chan *chan = xor_val_chan(submit, dest, src_list, src_cnt, len);
	काष्ठा dma_device *device = chan ? chan->device : शून्य;
	काष्ठा dma_async_tx_descriptor *tx = शून्य;
	काष्ठा dmaengine_unmap_data *unmap = शून्य;

	BUG_ON(src_cnt <= 1);

	अगर (device)
		unmap = dmaengine_get_unmap_data(device->dev, src_cnt, GFP_NOWAIT);

	अगर (unmap && src_cnt <= device->max_xor &&
	    dma_xor_aligned_offsets(device, offset, src_offs, src_cnt, len)) अणु
		अचिन्हित दीर्घ dma_prep_flags = 0;
		पूर्णांक i;

		pr_debug("%s: (async) len: %zu\n", __func__, len);

		अगर (submit->cb_fn)
			dma_prep_flags |= DMA_PREP_INTERRUPT;
		अगर (submit->flags & ASYNC_TX_FENCE)
			dma_prep_flags |= DMA_PREP_FENCE;

		क्रम (i = 0; i < src_cnt; i++) अणु
			unmap->addr[i] = dma_map_page(device->dev, src_list[i],
					src_offs ? src_offs[i] : offset,
					len, DMA_TO_DEVICE);
			unmap->to_cnt++;
		पूर्ण
		unmap->len = len;

		tx = device->device_prep_dma_xor_val(chan, unmap->addr, src_cnt,
						     len, result,
						     dma_prep_flags);
		अगर (unlikely(!tx)) अणु
			async_tx_quiesce(&submit->depend_tx);

			जबतक (!tx) अणु
				dma_async_issue_pending(chan);
				tx = device->device_prep_dma_xor_val(chan,
					unmap->addr, src_cnt, len, result,
					dma_prep_flags);
			पूर्ण
		पूर्ण
		dma_set_unmap(tx, unmap);
		async_tx_submit(chan, tx, submit);
	पूर्ण अन्यथा अणु
		क्रमागत async_tx_flags flags_orig = submit->flags;

		pr_debug("%s: (sync) len: %zu\n", __func__, len);
		WARN_ONCE(device && src_cnt <= device->max_xor,
			  "%s: no space for dma address conversion\n",
			  __func__);

		submit->flags |= ASYNC_TX_XOR_DROP_DST;
		submit->flags &= ~ASYNC_TX_ACK;

		tx = async_xor_offs(dest, offset, src_list, src_offs,
				src_cnt, len, submit);

		async_tx_quiesce(&tx);

		*result = !page_is_zero(dest, offset, len) << SUM_CHECK_P;

		async_tx_sync_epilog(submit);
		submit->flags = flags_orig;
	पूर्ण
	dmaengine_unmap_put(unmap);

	वापस tx;
पूर्ण
EXPORT_SYMBOL_GPL(async_xor_val_offs);

/**
 * async_xor_val - attempt a xor parity check with a dma engine.
 * @dest: destination page used अगर the xor is perक्रमmed synchronously
 * @src_list: array of source pages
 * @offset: offset in pages to start transaction
 * @src_cnt: number of source pages
 * @len: length in bytes
 * @result: 0 अगर sum == 0 अन्यथा non-zero
 * @submit: submission / completion modअगरiers
 *
 * honored flags: ASYNC_TX_ACK
 *
 * src_list note: अगर the dest is also a source it must be at index zero.
 * The contents of this array will be overwritten अगर a scribble region
 * is not specअगरied.
 */
काष्ठा dma_async_tx_descriptor *
async_xor_val(काष्ठा page *dest, काष्ठा page **src_list, अचिन्हित पूर्णांक offset,
	      पूर्णांक src_cnt, माप_प्रकार len, क्रमागत sum_check_flags *result,
	      काष्ठा async_submit_ctl *submit)
अणु
	वापस async_xor_val_offs(dest, offset, src_list, शून्य, src_cnt,
			len, result, submit);
पूर्ण
EXPORT_SYMBOL_GPL(async_xor_val);

MODULE_AUTHOR("Intel Corporation");
MODULE_DESCRIPTION("asynchronous xor/xor-zero-sum api");
MODULE_LICENSE("GPL");
