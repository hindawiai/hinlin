<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Isochronous I/O functionality:
 *   - Isochronous DMA context management
 *   - Isochronous bus resource management (channels, bandwidth), client side
 *
 * Copyright (C) 2006 Kristian Hoegsberg <krh@bitplanet.net>
 */

#समावेश <linux/dma-mapping.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/firewire.h>
#समावेश <linux/firewire-स्थिरants.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mm.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/export.h>

#समावेश <यंत्र/byteorder.h>

#समावेश "core.h"

/*
 * Isochronous DMA context management
 */

पूर्णांक fw_iso_buffer_alloc(काष्ठा fw_iso_buffer *buffer, पूर्णांक page_count)
अणु
	पूर्णांक i;

	buffer->page_count = 0;
	buffer->page_count_mapped = 0;
	buffer->pages = kदो_स्मृति_array(page_count, माप(buffer->pages[0]),
				      GFP_KERNEL);
	अगर (buffer->pages == शून्य)
		वापस -ENOMEM;

	क्रम (i = 0; i < page_count; i++) अणु
		buffer->pages[i] = alloc_page(GFP_KERNEL | GFP_DMA32 | __GFP_ZERO);
		अगर (buffer->pages[i] == शून्य)
			अवरोध;
	पूर्ण
	buffer->page_count = i;
	अगर (i < page_count) अणु
		fw_iso_buffer_destroy(buffer, शून्य);
		वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक fw_iso_buffer_map_dma(काष्ठा fw_iso_buffer *buffer, काष्ठा fw_card *card,
			  क्रमागत dma_data_direction direction)
अणु
	dma_addr_t address;
	पूर्णांक i;

	buffer->direction = direction;

	क्रम (i = 0; i < buffer->page_count; i++) अणु
		address = dma_map_page(card->device, buffer->pages[i],
				       0, PAGE_SIZE, direction);
		अगर (dma_mapping_error(card->device, address))
			अवरोध;

		set_page_निजी(buffer->pages[i], address);
	पूर्ण
	buffer->page_count_mapped = i;
	अगर (i < buffer->page_count)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

पूर्णांक fw_iso_buffer_init(काष्ठा fw_iso_buffer *buffer, काष्ठा fw_card *card,
		       पूर्णांक page_count, क्रमागत dma_data_direction direction)
अणु
	पूर्णांक ret;

	ret = fw_iso_buffer_alloc(buffer, page_count);
	अगर (ret < 0)
		वापस ret;

	ret = fw_iso_buffer_map_dma(buffer, card, direction);
	अगर (ret < 0)
		fw_iso_buffer_destroy(buffer, card);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(fw_iso_buffer_init);

व्योम fw_iso_buffer_destroy(काष्ठा fw_iso_buffer *buffer,
			   काष्ठा fw_card *card)
अणु
	पूर्णांक i;
	dma_addr_t address;

	क्रम (i = 0; i < buffer->page_count_mapped; i++) अणु
		address = page_निजी(buffer->pages[i]);
		dma_unmap_page(card->device, address,
			       PAGE_SIZE, buffer->direction);
	पूर्ण
	क्रम (i = 0; i < buffer->page_count; i++)
		__मुक्त_page(buffer->pages[i]);

	kमुक्त(buffer->pages);
	buffer->pages = शून्य;
	buffer->page_count = 0;
	buffer->page_count_mapped = 0;
पूर्ण
EXPORT_SYMBOL(fw_iso_buffer_destroy);

/* Convert DMA address to offset पूर्णांकo भवly contiguous buffer. */
माप_प्रकार fw_iso_buffer_lookup(काष्ठा fw_iso_buffer *buffer, dma_addr_t completed)
अणु
	माप_प्रकार i;
	dma_addr_t address;
	sमाप_प्रकार offset;

	क्रम (i = 0; i < buffer->page_count; i++) अणु
		address = page_निजी(buffer->pages[i]);
		offset = (sमाप_प्रकार)completed - (sमाप_प्रकार)address;
		अगर (offset > 0 && offset <= PAGE_SIZE)
			वापस (i << PAGE_SHIFT) + offset;
	पूर्ण

	वापस 0;
पूर्ण

काष्ठा fw_iso_context *fw_iso_context_create(काष्ठा fw_card *card,
		पूर्णांक type, पूर्णांक channel, पूर्णांक speed, माप_प्रकार header_size,
		fw_iso_callback_t callback, व्योम *callback_data)
अणु
	काष्ठा fw_iso_context *ctx;

	ctx = card->driver->allocate_iso_context(card,
						 type, channel, header_size);
	अगर (IS_ERR(ctx))
		वापस ctx;

	ctx->card = card;
	ctx->type = type;
	ctx->channel = channel;
	ctx->speed = speed;
	ctx->header_size = header_size;
	ctx->callback.sc = callback;
	ctx->callback_data = callback_data;

	वापस ctx;
पूर्ण
EXPORT_SYMBOL(fw_iso_context_create);

व्योम fw_iso_context_destroy(काष्ठा fw_iso_context *ctx)
अणु
	ctx->card->driver->मुक्त_iso_context(ctx);
पूर्ण
EXPORT_SYMBOL(fw_iso_context_destroy);

पूर्णांक fw_iso_context_start(काष्ठा fw_iso_context *ctx,
			 पूर्णांक cycle, पूर्णांक sync, पूर्णांक tags)
अणु
	वापस ctx->card->driver->start_iso(ctx, cycle, sync, tags);
पूर्ण
EXPORT_SYMBOL(fw_iso_context_start);

पूर्णांक fw_iso_context_set_channels(काष्ठा fw_iso_context *ctx, u64 *channels)
अणु
	वापस ctx->card->driver->set_iso_channels(ctx, channels);
पूर्ण

पूर्णांक fw_iso_context_queue(काष्ठा fw_iso_context *ctx,
			 काष्ठा fw_iso_packet *packet,
			 काष्ठा fw_iso_buffer *buffer,
			 अचिन्हित दीर्घ payload)
अणु
	वापस ctx->card->driver->queue_iso(ctx, packet, buffer, payload);
पूर्ण
EXPORT_SYMBOL(fw_iso_context_queue);

व्योम fw_iso_context_queue_flush(काष्ठा fw_iso_context *ctx)
अणु
	ctx->card->driver->flush_queue_iso(ctx);
पूर्ण
EXPORT_SYMBOL(fw_iso_context_queue_flush);

पूर्णांक fw_iso_context_flush_completions(काष्ठा fw_iso_context *ctx)
अणु
	वापस ctx->card->driver->flush_iso_completions(ctx);
पूर्ण
EXPORT_SYMBOL(fw_iso_context_flush_completions);

पूर्णांक fw_iso_context_stop(काष्ठा fw_iso_context *ctx)
अणु
	वापस ctx->card->driver->stop_iso(ctx);
पूर्ण
EXPORT_SYMBOL(fw_iso_context_stop);

/*
 * Isochronous bus resource management (channels, bandwidth), client side
 */

अटल पूर्णांक manage_bandwidth(काष्ठा fw_card *card, पूर्णांक irm_id, पूर्णांक generation,
			    पूर्णांक bandwidth, bool allocate)
अणु
	पूर्णांक try, new, old = allocate ? BANDWIDTH_AVAILABLE_INITIAL : 0;
	__be32 data[2];

	/*
	 * On a 1394a IRM with low contention, try < 1 is enough.
	 * On a 1394-1995 IRM, we need at least try < 2.
	 * Let's just करो try < 5.
	 */
	क्रम (try = 0; try < 5; try++) अणु
		new = allocate ? old - bandwidth : old + bandwidth;
		अगर (new < 0 || new > BANDWIDTH_AVAILABLE_INITIAL)
			वापस -EBUSY;

		data[0] = cpu_to_be32(old);
		data[1] = cpu_to_be32(new);
		चयन (fw_run_transaction(card, TCODE_LOCK_COMPARE_SWAP,
				irm_id, generation, SCODE_100,
				CSR_REGISTER_BASE + CSR_BANDWIDTH_AVAILABLE,
				data, 8)) अणु
		हाल RCODE_GENERATION:
			/* A generation change मुक्तs all bandwidth. */
			वापस allocate ? -EAGAIN : bandwidth;

		हाल RCODE_COMPLETE:
			अगर (be32_to_cpup(data) == old)
				वापस bandwidth;

			old = be32_to_cpup(data);
			/* Fall through. */
		पूर्ण
	पूर्ण

	वापस -EIO;
पूर्ण

अटल पूर्णांक manage_channel(काष्ठा fw_card *card, पूर्णांक irm_id, पूर्णांक generation,
		u32 channels_mask, u64 offset, bool allocate)
अणु
	__be32 bit, all, old;
	__be32 data[2];
	पूर्णांक channel, ret = -EIO, retry = 5;

	old = all = allocate ? cpu_to_be32(~0) : 0;

	क्रम (channel = 0; channel < 32; channel++) अणु
		अगर (!(channels_mask & 1 << channel))
			जारी;

		ret = -EBUSY;

		bit = cpu_to_be32(1 << (31 - channel));
		अगर ((old & bit) != (all & bit))
			जारी;

		data[0] = old;
		data[1] = old ^ bit;
		चयन (fw_run_transaction(card, TCODE_LOCK_COMPARE_SWAP,
					   irm_id, generation, SCODE_100,
					   offset, data, 8)) अणु
		हाल RCODE_GENERATION:
			/* A generation change मुक्तs all channels. */
			वापस allocate ? -EAGAIN : channel;

		हाल RCODE_COMPLETE:
			अगर (data[0] == old)
				वापस channel;

			old = data[0];

			/* Is the IRM 1394a-2000 compliant? */
			अगर ((data[0] & bit) == (data[1] & bit))
				जारी;

			fallthrough;	/* It's a 1394-1995 IRM, retry */
		शेष:
			अगर (retry) अणु
				retry--;
				channel--;
			पूर्ण अन्यथा अणु
				ret = -EIO;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम deallocate_channel(काष्ठा fw_card *card, पूर्णांक irm_id,
			       पूर्णांक generation, पूर्णांक channel)
अणु
	u32 mask;
	u64 offset;

	mask = channel < 32 ? 1 << channel : 1 << (channel - 32);
	offset = channel < 32 ? CSR_REGISTER_BASE + CSR_CHANNELS_AVAILABLE_HI :
				CSR_REGISTER_BASE + CSR_CHANNELS_AVAILABLE_LO;

	manage_channel(card, irm_id, generation, mask, offset, false);
पूर्ण

/**
 * fw_iso_resource_manage() - Allocate or deallocate a channel and/or bandwidth
 * @card: card पूर्णांकerface क्रम this action
 * @generation: bus generation
 * @channels_mask: biपंचांगask क्रम channel allocation
 * @channel: poपूर्णांकer क्रम वापसing channel allocation result
 * @bandwidth: poपूर्णांकer क्रम वापसing bandwidth allocation result
 * @allocate: whether to allocate (true) or deallocate (false)
 *
 * In parameters: card, generation, channels_mask, bandwidth, allocate
 * Out parameters: channel, bandwidth
 *
 * This function blocks (sleeps) during communication with the IRM.
 *
 * Allocates or deallocates at most one channel out of channels_mask.
 * channels_mask is a bitfield with MSB क्रम channel 63 and LSB क्रम channel 0.
 * (Note, the IRM's CHANNELS_AVAILABLE is a big-endian bitfield with MSB क्रम
 * channel 0 and LSB क्रम channel 63.)
 * Allocates or deallocates as many bandwidth allocation units as specअगरied.
 *
 * Returns channel < 0 अगर no channel was allocated or deallocated.
 * Returns bandwidth = 0 अगर no bandwidth was allocated or deallocated.
 *
 * If generation is stale, deallocations succeed but allocations fail with
 * channel = -EAGAIN.
 *
 * If channel allocation fails, no bandwidth will be allocated either.
 * If bandwidth allocation fails, no channel will be allocated either.
 * But deallocations of channel and bandwidth are tried independently
 * of each other's success.
 */
व्योम fw_iso_resource_manage(काष्ठा fw_card *card, पूर्णांक generation,
			    u64 channels_mask, पूर्णांक *channel, पूर्णांक *bandwidth,
			    bool allocate)
अणु
	u32 channels_hi = channels_mask;	/* channels 31...0 */
	u32 channels_lo = channels_mask >> 32;	/* channels 63...32 */
	पूर्णांक irm_id, ret, c = -EINVAL;

	spin_lock_irq(&card->lock);
	irm_id = card->irm_node->node_id;
	spin_unlock_irq(&card->lock);

	अगर (channels_hi)
		c = manage_channel(card, irm_id, generation, channels_hi,
				CSR_REGISTER_BASE + CSR_CHANNELS_AVAILABLE_HI,
				allocate);
	अगर (channels_lo && c < 0) अणु
		c = manage_channel(card, irm_id, generation, channels_lo,
				CSR_REGISTER_BASE + CSR_CHANNELS_AVAILABLE_LO,
				allocate);
		अगर (c >= 0)
			c += 32;
	पूर्ण
	*channel = c;

	अगर (allocate && channels_mask != 0 && c < 0)
		*bandwidth = 0;

	अगर (*bandwidth == 0)
		वापस;

	ret = manage_bandwidth(card, irm_id, generation, *bandwidth, allocate);
	अगर (ret < 0)
		*bandwidth = 0;

	अगर (allocate && ret < 0) अणु
		अगर (c >= 0)
			deallocate_channel(card, irm_id, generation, c);
		*channel = ret;
	पूर्ण
पूर्ण
EXPORT_SYMBOL(fw_iso_resource_manage);
