<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * copy offload engine support
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
#समावेश <linux/highस्मृति.स>
#समावेश <linux/module.h>
#समावेश <linux/mm.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/async_tx.h>

/**
 * async_स_नकल - attempt to copy memory with a dma engine.
 * @dest: destination page
 * @src: src page
 * @dest_offset: offset पूर्णांकo 'dest' to start transaction
 * @src_offset: offset पूर्णांकo 'src' to start transaction
 * @len: length in bytes
 * @submit: submission / completion modअगरiers
 *
 * honored flags: ASYNC_TX_ACK
 */
काष्ठा dma_async_tx_descriptor *
async_स_नकल(काष्ठा page *dest, काष्ठा page *src, अचिन्हित पूर्णांक dest_offset,
	     अचिन्हित पूर्णांक src_offset, माप_प्रकार len,
	     काष्ठा async_submit_ctl *submit)
अणु
	काष्ठा dma_chan *chan = async_tx_find_channel(submit, DMA_MEMCPY,
						      &dest, 1, &src, 1, len);
	काष्ठा dma_device *device = chan ? chan->device : शून्य;
	काष्ठा dma_async_tx_descriptor *tx = शून्य;
	काष्ठा dmaengine_unmap_data *unmap = शून्य;

	अगर (device)
		unmap = dmaengine_get_unmap_data(device->dev, 2, GFP_NOWAIT);

	अगर (unmap && is_dma_copy_aligned(device, src_offset, dest_offset, len)) अणु
		अचिन्हित दीर्घ dma_prep_flags = 0;

		अगर (submit->cb_fn)
			dma_prep_flags |= DMA_PREP_INTERRUPT;
		अगर (submit->flags & ASYNC_TX_FENCE)
			dma_prep_flags |= DMA_PREP_FENCE;

		unmap->to_cnt = 1;
		unmap->addr[0] = dma_map_page(device->dev, src, src_offset, len,
					      DMA_TO_DEVICE);
		unmap->from_cnt = 1;
		unmap->addr[1] = dma_map_page(device->dev, dest, dest_offset, len,
					      DMA_FROM_DEVICE);
		unmap->len = len;

		tx = device->device_prep_dma_स_नकल(chan, unmap->addr[1],
						    unmap->addr[0], len,
						    dma_prep_flags);
	पूर्ण

	अगर (tx) अणु
		pr_debug("%s: (async) len: %zu\n", __func__, len);

		dma_set_unmap(tx, unmap);
		async_tx_submit(chan, tx, submit);
	पूर्ण अन्यथा अणु
		व्योम *dest_buf, *src_buf;
		pr_debug("%s: (sync) len: %zu\n", __func__, len);

		/* रुको क्रम any prerequisite operations */
		async_tx_quiesce(&submit->depend_tx);

		dest_buf = kmap_atomic(dest) + dest_offset;
		src_buf = kmap_atomic(src) + src_offset;

		स_नकल(dest_buf, src_buf, len);

		kunmap_atomic(src_buf);
		kunmap_atomic(dest_buf);

		async_tx_sync_epilog(submit);
	पूर्ण

	dmaengine_unmap_put(unmap);

	वापस tx;
पूर्ण
EXPORT_SYMBOL_GPL(async_स_नकल);

MODULE_AUTHOR("Intel Corporation");
MODULE_DESCRIPTION("asynchronous memcpy api");
MODULE_LICENSE("GPL");
