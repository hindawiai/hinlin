<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * xHCI host controller driver
 *
 * Copyright (C) 2008 Intel Corp.
 *
 * Author: Sarah Sharp
 * Some code borrowed from the Linux EHCI driver.
 */

#समावेश <linux/usb.h>
#समावेश <linux/pci.h>
#समावेश <linux/slab.h>
#समावेश <linux/dmapool.h>
#समावेश <linux/dma-mapping.h>

#समावेश "xhci.h"
#समावेश "xhci-trace.h"
#समावेश "xhci-debugfs.h"

/*
 * Allocates a generic ring segment from the ring pool, sets the dma address,
 * initializes the segment to zero, and sets the निजी next poपूर्णांकer to शून्य.
 *
 * Section 4.11.1.1:
 * "All components of all Command and Transfer TRBs shall be initialized to '0'"
 */
अटल काष्ठा xhci_segment *xhci_segment_alloc(काष्ठा xhci_hcd *xhci,
					       अचिन्हित पूर्णांक cycle_state,
					       अचिन्हित पूर्णांक max_packet,
					       gfp_t flags)
अणु
	काष्ठा xhci_segment *seg;
	dma_addr_t	dma;
	पूर्णांक		i;
	काष्ठा device *dev = xhci_to_hcd(xhci)->self.sysdev;

	seg = kzalloc_node(माप(*seg), flags, dev_to_node(dev));
	अगर (!seg)
		वापस शून्य;

	seg->trbs = dma_pool_zalloc(xhci->segment_pool, flags, &dma);
	अगर (!seg->trbs) अणु
		kमुक्त(seg);
		वापस शून्य;
	पूर्ण

	अगर (max_packet) अणु
		seg->bounce_buf = kzalloc_node(max_packet, flags,
					dev_to_node(dev));
		अगर (!seg->bounce_buf) अणु
			dma_pool_मुक्त(xhci->segment_pool, seg->trbs, dma);
			kमुक्त(seg);
			वापस शून्य;
		पूर्ण
	पूर्ण
	/* If the cycle state is 0, set the cycle bit to 1 क्रम all the TRBs */
	अगर (cycle_state == 0) अणु
		क्रम (i = 0; i < TRBS_PER_SEGMENT; i++)
			seg->trbs[i].link.control |= cpu_to_le32(TRB_CYCLE);
	पूर्ण
	seg->dma = dma;
	seg->next = शून्य;

	वापस seg;
पूर्ण

अटल व्योम xhci_segment_मुक्त(काष्ठा xhci_hcd *xhci, काष्ठा xhci_segment *seg)
अणु
	अगर (seg->trbs) अणु
		dma_pool_मुक्त(xhci->segment_pool, seg->trbs, seg->dma);
		seg->trbs = शून्य;
	पूर्ण
	kमुक्त(seg->bounce_buf);
	kमुक्त(seg);
पूर्ण

अटल व्योम xhci_मुक्त_segments_क्रम_ring(काष्ठा xhci_hcd *xhci,
				काष्ठा xhci_segment *first)
अणु
	काष्ठा xhci_segment *seg;

	seg = first->next;
	जबतक (seg != first) अणु
		काष्ठा xhci_segment *next = seg->next;
		xhci_segment_मुक्त(xhci, seg);
		seg = next;
	पूर्ण
	xhci_segment_मुक्त(xhci, first);
पूर्ण

/*
 * Make the prev segment poपूर्णांक to the next segment.
 *
 * Change the last TRB in the prev segment to be a Link TRB which poपूर्णांकs to the
 * DMA address of the next segment.  The caller needs to set any Link TRB
 * related flags, such as End TRB, Toggle Cycle, and no snoop.
 */
अटल व्योम xhci_link_segments(काष्ठा xhci_segment *prev,
			       काष्ठा xhci_segment *next,
			       क्रमागत xhci_ring_type type, bool chain_links)
अणु
	u32 val;

	अगर (!prev || !next)
		वापस;
	prev->next = next;
	अगर (type != TYPE_EVENT) अणु
		prev->trbs[TRBS_PER_SEGMENT-1].link.segment_ptr =
			cpu_to_le64(next->dma);

		/* Set the last TRB in the segment to have a TRB type ID of Link TRB */
		val = le32_to_cpu(prev->trbs[TRBS_PER_SEGMENT-1].link.control);
		val &= ~TRB_TYPE_BITMASK;
		val |= TRB_TYPE(TRB_LINK);
		अगर (chain_links)
			val |= TRB_CHAIN;
		prev->trbs[TRBS_PER_SEGMENT-1].link.control = cpu_to_le32(val);
	पूर्ण
पूर्ण

/*
 * Link the ring to the new segments.
 * Set Toggle Cycle क्रम the new ring अगर needed.
 */
अटल व्योम xhci_link_rings(काष्ठा xhci_hcd *xhci, काष्ठा xhci_ring *ring,
		काष्ठा xhci_segment *first, काष्ठा xhci_segment *last,
		अचिन्हित पूर्णांक num_segs)
अणु
	काष्ठा xhci_segment *next;
	bool chain_links;

	अगर (!ring || !first || !last)
		वापस;

	/* Set chain bit क्रम 0.95 hosts, and क्रम isoc rings on AMD 0.96 host */
	chain_links = !!(xhci_link_trb_quirk(xhci) ||
			 (ring->type == TYPE_ISOC &&
			  (xhci->quirks & XHCI_AMD_0x96_HOST)));

	next = ring->enq_seg->next;
	xhci_link_segments(ring->enq_seg, first, ring->type, chain_links);
	xhci_link_segments(last, next, ring->type, chain_links);
	ring->num_segs += num_segs;
	ring->num_trbs_मुक्त += (TRBS_PER_SEGMENT - 1) * num_segs;

	अगर (ring->type != TYPE_EVENT && ring->enq_seg == ring->last_seg) अणु
		ring->last_seg->trbs[TRBS_PER_SEGMENT-1].link.control
			&= ~cpu_to_le32(LINK_TOGGLE);
		last->trbs[TRBS_PER_SEGMENT-1].link.control
			|= cpu_to_le32(LINK_TOGGLE);
		ring->last_seg = last;
	पूर्ण
पूर्ण

/*
 * We need a radix tree क्रम mapping physical addresses of TRBs to which stream
 * ID they beदीर्घ to.  We need to करो this because the host controller won't tell
 * us which stream ring the TRB came from.  We could store the stream ID in an
 * event data TRB, but that करोesn't help us क्रम the cancellation हाल, since the
 * endpoपूर्णांक may stop beक्रमe it reaches that event data TRB.
 *
 * The radix tree maps the upper portion of the TRB DMA address to a ring
 * segment that has the same upper portion of DMA addresses.  For example, say I
 * have segments of size 1KB, that are always 1KB aligned.  A segment may
 * start at 0x10c91000 and end at 0x10c913f0.  If I use the upper 10 bits, the
 * key to the stream ID is 0x43244.  I can use the DMA address of the TRB to
 * pass the radix tree a key to get the right stream ID:
 *
 *	0x10c90fff >> 10 = 0x43243
 *	0x10c912c0 >> 10 = 0x43244
 *	0x10c91400 >> 10 = 0x43245
 *
 * Obviously, only those TRBs with DMA addresses that are within the segment
 * will make the radix tree वापस the stream ID क्रम that ring.
 *
 * Caveats क्रम the radix tree:
 *
 * The radix tree uses an अचिन्हित दीर्घ as a key pair.  On 32-bit प्रणालीs, an
 * अचिन्हित दीर्घ will be 32-bits; on a 64-bit प्रणाली an अचिन्हित दीर्घ will be
 * 64-bits.  Since we only request 32-bit DMA addresses, we can use that as the
 * key on 32-bit or 64-bit प्रणालीs (it would also be fine अगर we asked क्रम 64-bit
 * PCI DMA addresses on a 64-bit प्रणाली).  There might be a problem on 32-bit
 * extended प्रणालीs (where the DMA address can be bigger than 32-bits),
 * अगर we allow the PCI dma mask to be bigger than 32-bits.  So करोn't करो that.
 */
अटल पूर्णांक xhci_insert_segment_mapping(काष्ठा radix_tree_root *trb_address_map,
		काष्ठा xhci_ring *ring,
		काष्ठा xhci_segment *seg,
		gfp_t mem_flags)
अणु
	अचिन्हित दीर्घ key;
	पूर्णांक ret;

	key = (अचिन्हित दीर्घ)(seg->dma >> TRB_SEGMENT_SHIFT);
	/* Skip any segments that were alपढ़ोy added. */
	अगर (radix_tree_lookup(trb_address_map, key))
		वापस 0;

	ret = radix_tree_maybe_preload(mem_flags);
	अगर (ret)
		वापस ret;
	ret = radix_tree_insert(trb_address_map,
			key, ring);
	radix_tree_preload_end();
	वापस ret;
पूर्ण

अटल व्योम xhci_हटाओ_segment_mapping(काष्ठा radix_tree_root *trb_address_map,
		काष्ठा xhci_segment *seg)
अणु
	अचिन्हित दीर्घ key;

	key = (अचिन्हित दीर्घ)(seg->dma >> TRB_SEGMENT_SHIFT);
	अगर (radix_tree_lookup(trb_address_map, key))
		radix_tree_delete(trb_address_map, key);
पूर्ण

अटल पूर्णांक xhci_update_stream_segment_mapping(
		काष्ठा radix_tree_root *trb_address_map,
		काष्ठा xhci_ring *ring,
		काष्ठा xhci_segment *first_seg,
		काष्ठा xhci_segment *last_seg,
		gfp_t mem_flags)
अणु
	काष्ठा xhci_segment *seg;
	काष्ठा xhci_segment *failed_seg;
	पूर्णांक ret;

	अगर (WARN_ON_ONCE(trb_address_map == शून्य))
		वापस 0;

	seg = first_seg;
	करो अणु
		ret = xhci_insert_segment_mapping(trb_address_map,
				ring, seg, mem_flags);
		अगर (ret)
			जाओ हटाओ_streams;
		अगर (seg == last_seg)
			वापस 0;
		seg = seg->next;
	पूर्ण जबतक (seg != first_seg);

	वापस 0;

हटाओ_streams:
	failed_seg = seg;
	seg = first_seg;
	करो अणु
		xhci_हटाओ_segment_mapping(trb_address_map, seg);
		अगर (seg == failed_seg)
			वापस ret;
		seg = seg->next;
	पूर्ण जबतक (seg != first_seg);

	वापस ret;
पूर्ण

अटल व्योम xhci_हटाओ_stream_mapping(काष्ठा xhci_ring *ring)
अणु
	काष्ठा xhci_segment *seg;

	अगर (WARN_ON_ONCE(ring->trb_address_map == शून्य))
		वापस;

	seg = ring->first_seg;
	करो अणु
		xhci_हटाओ_segment_mapping(ring->trb_address_map, seg);
		seg = seg->next;
	पूर्ण जबतक (seg != ring->first_seg);
पूर्ण

अटल पूर्णांक xhci_update_stream_mapping(काष्ठा xhci_ring *ring, gfp_t mem_flags)
अणु
	वापस xhci_update_stream_segment_mapping(ring->trb_address_map, ring,
			ring->first_seg, ring->last_seg, mem_flags);
पूर्ण

/* XXX: Do we need the hcd काष्ठाure in all these functions? */
व्योम xhci_ring_मुक्त(काष्ठा xhci_hcd *xhci, काष्ठा xhci_ring *ring)
अणु
	अगर (!ring)
		वापस;

	trace_xhci_ring_मुक्त(ring);

	अगर (ring->first_seg) अणु
		अगर (ring->type == TYPE_STREAM)
			xhci_हटाओ_stream_mapping(ring);
		xhci_मुक्त_segments_क्रम_ring(xhci, ring->first_seg);
	पूर्ण

	kमुक्त(ring);
पूर्ण

व्योम xhci_initialize_ring_info(काष्ठा xhci_ring *ring,
			       अचिन्हित पूर्णांक cycle_state)
अणु
	/* The ring is empty, so the enqueue poपूर्णांकer == dequeue poपूर्णांकer */
	ring->enqueue = ring->first_seg->trbs;
	ring->enq_seg = ring->first_seg;
	ring->dequeue = ring->enqueue;
	ring->deq_seg = ring->first_seg;
	/* The ring is initialized to 0. The producer must ग_लिखो 1 to the cycle
	 * bit to hanकरोver ownership of the TRB, so PCS = 1.  The consumer must
	 * compare CCS to the cycle bit to check ownership, so CCS = 1.
	 *
	 * New rings are initialized with cycle state equal to 1; अगर we are
	 * handling ring expansion, set the cycle state equal to the old ring.
	 */
	ring->cycle_state = cycle_state;

	/*
	 * Each segment has a link TRB, and leave an extra TRB क्रम SW
	 * accounting purpose
	 */
	ring->num_trbs_मुक्त = ring->num_segs * (TRBS_PER_SEGMENT - 1) - 1;
पूर्ण

/* Allocate segments and link them क्रम a ring */
अटल पूर्णांक xhci_alloc_segments_क्रम_ring(काष्ठा xhci_hcd *xhci,
		काष्ठा xhci_segment **first, काष्ठा xhci_segment **last,
		अचिन्हित पूर्णांक num_segs, अचिन्हित पूर्णांक cycle_state,
		क्रमागत xhci_ring_type type, अचिन्हित पूर्णांक max_packet, gfp_t flags)
अणु
	काष्ठा xhci_segment *prev;
	bool chain_links;

	/* Set chain bit क्रम 0.95 hosts, and क्रम isoc rings on AMD 0.96 host */
	chain_links = !!(xhci_link_trb_quirk(xhci) ||
			 (type == TYPE_ISOC &&
			  (xhci->quirks & XHCI_AMD_0x96_HOST)));

	prev = xhci_segment_alloc(xhci, cycle_state, max_packet, flags);
	अगर (!prev)
		वापस -ENOMEM;
	num_segs--;

	*first = prev;
	जबतक (num_segs > 0) अणु
		काष्ठा xhci_segment	*next;

		next = xhci_segment_alloc(xhci, cycle_state, max_packet, flags);
		अगर (!next) अणु
			prev = *first;
			जबतक (prev) अणु
				next = prev->next;
				xhci_segment_मुक्त(xhci, prev);
				prev = next;
			पूर्ण
			वापस -ENOMEM;
		पूर्ण
		xhci_link_segments(prev, next, type, chain_links);

		prev = next;
		num_segs--;
	पूर्ण
	xhci_link_segments(prev, *first, type, chain_links);
	*last = prev;

	वापस 0;
पूर्ण

/*
 * Create a new ring with zero or more segments.
 *
 * Link each segment together पूर्णांकo a ring.
 * Set the end flag and the cycle toggle bit on the last segment.
 * See section 4.9.1 and figures 15 and 16.
 */
काष्ठा xhci_ring *xhci_ring_alloc(काष्ठा xhci_hcd *xhci,
		अचिन्हित पूर्णांक num_segs, अचिन्हित पूर्णांक cycle_state,
		क्रमागत xhci_ring_type type, अचिन्हित पूर्णांक max_packet, gfp_t flags)
अणु
	काष्ठा xhci_ring	*ring;
	पूर्णांक ret;
	काष्ठा device *dev = xhci_to_hcd(xhci)->self.sysdev;

	ring = kzalloc_node(माप(*ring), flags, dev_to_node(dev));
	अगर (!ring)
		वापस शून्य;

	ring->num_segs = num_segs;
	ring->bounce_buf_len = max_packet;
	INIT_LIST_HEAD(&ring->td_list);
	ring->type = type;
	अगर (num_segs == 0)
		वापस ring;

	ret = xhci_alloc_segments_क्रम_ring(xhci, &ring->first_seg,
			&ring->last_seg, num_segs, cycle_state, type,
			max_packet, flags);
	अगर (ret)
		जाओ fail;

	/* Only event ring करोes not use link TRB */
	अगर (type != TYPE_EVENT) अणु
		/* See section 4.9.2.1 and 6.4.4.1 */
		ring->last_seg->trbs[TRBS_PER_SEGMENT - 1].link.control |=
			cpu_to_le32(LINK_TOGGLE);
	पूर्ण
	xhci_initialize_ring_info(ring, cycle_state);
	trace_xhci_ring_alloc(ring);
	वापस ring;

fail:
	kमुक्त(ring);
	वापस शून्य;
पूर्ण

व्योम xhci_मुक्त_endpoपूर्णांक_ring(काष्ठा xhci_hcd *xhci,
		काष्ठा xhci_virt_device *virt_dev,
		अचिन्हित पूर्णांक ep_index)
अणु
	xhci_ring_मुक्त(xhci, virt_dev->eps[ep_index].ring);
	virt_dev->eps[ep_index].ring = शून्य;
पूर्ण

/*
 * Expand an existing ring.
 * Allocate a new ring which has same segment numbers and link the two rings.
 */
पूर्णांक xhci_ring_expansion(काष्ठा xhci_hcd *xhci, काष्ठा xhci_ring *ring,
				अचिन्हित पूर्णांक num_trbs, gfp_t flags)
अणु
	काष्ठा xhci_segment	*first;
	काष्ठा xhci_segment	*last;
	अचिन्हित पूर्णांक		num_segs;
	अचिन्हित पूर्णांक		num_segs_needed;
	पूर्णांक			ret;

	num_segs_needed = (num_trbs + (TRBS_PER_SEGMENT - 1) - 1) /
				(TRBS_PER_SEGMENT - 1);

	/* Allocate number of segments we needed, or द्विगुन the ring size */
	num_segs = ring->num_segs > num_segs_needed ?
			ring->num_segs : num_segs_needed;

	ret = xhci_alloc_segments_क्रम_ring(xhci, &first, &last,
			num_segs, ring->cycle_state, ring->type,
			ring->bounce_buf_len, flags);
	अगर (ret)
		वापस -ENOMEM;

	अगर (ring->type == TYPE_STREAM)
		ret = xhci_update_stream_segment_mapping(ring->trb_address_map,
						ring, first, last, flags);
	अगर (ret) अणु
		काष्ठा xhci_segment *next;
		करो अणु
			next = first->next;
			xhci_segment_मुक्त(xhci, first);
			अगर (first == last)
				अवरोध;
			first = next;
		पूर्ण जबतक (true);
		वापस ret;
	पूर्ण

	xhci_link_rings(xhci, ring, first, last, num_segs);
	trace_xhci_ring_expansion(ring);
	xhci_dbg_trace(xhci, trace_xhci_dbg_ring_expansion,
			"ring expansion succeed, now has %d segments",
			ring->num_segs);

	वापस 0;
पूर्ण

काष्ठा xhci_container_ctx *xhci_alloc_container_ctx(काष्ठा xhci_hcd *xhci,
						    पूर्णांक type, gfp_t flags)
अणु
	काष्ठा xhci_container_ctx *ctx;
	काष्ठा device *dev = xhci_to_hcd(xhci)->self.sysdev;

	अगर ((type != XHCI_CTX_TYPE_DEVICE) && (type != XHCI_CTX_TYPE_INPUT))
		वापस शून्य;

	ctx = kzalloc_node(माप(*ctx), flags, dev_to_node(dev));
	अगर (!ctx)
		वापस शून्य;

	ctx->type = type;
	ctx->size = HCC_64BYTE_CONTEXT(xhci->hcc_params) ? 2048 : 1024;
	अगर (type == XHCI_CTX_TYPE_INPUT)
		ctx->size += CTX_SIZE(xhci->hcc_params);

	ctx->bytes = dma_pool_zalloc(xhci->device_pool, flags, &ctx->dma);
	अगर (!ctx->bytes) अणु
		kमुक्त(ctx);
		वापस शून्य;
	पूर्ण
	वापस ctx;
पूर्ण

व्योम xhci_मुक्त_container_ctx(काष्ठा xhci_hcd *xhci,
			     काष्ठा xhci_container_ctx *ctx)
अणु
	अगर (!ctx)
		वापस;
	dma_pool_मुक्त(xhci->device_pool, ctx->bytes, ctx->dma);
	kमुक्त(ctx);
पूर्ण

काष्ठा xhci_input_control_ctx *xhci_get_input_control_ctx(
					      काष्ठा xhci_container_ctx *ctx)
अणु
	अगर (ctx->type != XHCI_CTX_TYPE_INPUT)
		वापस शून्य;

	वापस (काष्ठा xhci_input_control_ctx *)ctx->bytes;
पूर्ण

काष्ठा xhci_slot_ctx *xhci_get_slot_ctx(काष्ठा xhci_hcd *xhci,
					काष्ठा xhci_container_ctx *ctx)
अणु
	अगर (ctx->type == XHCI_CTX_TYPE_DEVICE)
		वापस (काष्ठा xhci_slot_ctx *)ctx->bytes;

	वापस (काष्ठा xhci_slot_ctx *)
		(ctx->bytes + CTX_SIZE(xhci->hcc_params));
पूर्ण

काष्ठा xhci_ep_ctx *xhci_get_ep_ctx(काष्ठा xhci_hcd *xhci,
				    काष्ठा xhci_container_ctx *ctx,
				    अचिन्हित पूर्णांक ep_index)
अणु
	/* increment ep index by offset of start of ep ctx array */
	ep_index++;
	अगर (ctx->type == XHCI_CTX_TYPE_INPUT)
		ep_index++;

	वापस (काष्ठा xhci_ep_ctx *)
		(ctx->bytes + (ep_index * CTX_SIZE(xhci->hcc_params)));
पूर्ण
EXPORT_SYMBOL_GPL(xhci_get_ep_ctx);

/***************** Streams काष्ठाures manipulation *************************/

अटल व्योम xhci_मुक्त_stream_ctx(काष्ठा xhci_hcd *xhci,
		अचिन्हित पूर्णांक num_stream_ctxs,
		काष्ठा xhci_stream_ctx *stream_ctx, dma_addr_t dma)
अणु
	काष्ठा device *dev = xhci_to_hcd(xhci)->self.sysdev;
	माप_प्रकार size = माप(काष्ठा xhci_stream_ctx) * num_stream_ctxs;

	अगर (size > MEDIUM_STREAM_ARRAY_SIZE)
		dma_मुक्त_coherent(dev, size,
				stream_ctx, dma);
	अन्यथा अगर (size <= SMALL_STREAM_ARRAY_SIZE)
		वापस dma_pool_मुक्त(xhci->small_streams_pool,
				stream_ctx, dma);
	अन्यथा
		वापस dma_pool_मुक्त(xhci->medium_streams_pool,
				stream_ctx, dma);
पूर्ण

/*
 * The stream context array क्रम each endpoपूर्णांक with bulk streams enabled can
 * vary in size, based on:
 *  - how many streams the endpoपूर्णांक supports,
 *  - the maximum primary stream array size the host controller supports,
 *  - and how many streams the device driver asks क्रम.
 *
 * The stream context array must be a घातer of 2, and can be as small as
 * 64 bytes or as large as 1MB.
 */
अटल काष्ठा xhci_stream_ctx *xhci_alloc_stream_ctx(काष्ठा xhci_hcd *xhci,
		अचिन्हित पूर्णांक num_stream_ctxs, dma_addr_t *dma,
		gfp_t mem_flags)
अणु
	काष्ठा device *dev = xhci_to_hcd(xhci)->self.sysdev;
	माप_प्रकार size = माप(काष्ठा xhci_stream_ctx) * num_stream_ctxs;

	अगर (size > MEDIUM_STREAM_ARRAY_SIZE)
		वापस dma_alloc_coherent(dev, size,
				dma, mem_flags);
	अन्यथा अगर (size <= SMALL_STREAM_ARRAY_SIZE)
		वापस dma_pool_alloc(xhci->small_streams_pool,
				mem_flags, dma);
	अन्यथा
		वापस dma_pool_alloc(xhci->medium_streams_pool,
				mem_flags, dma);
पूर्ण

काष्ठा xhci_ring *xhci_dma_to_transfer_ring(
		काष्ठा xhci_virt_ep *ep,
		u64 address)
अणु
	अगर (ep->ep_state & EP_HAS_STREAMS)
		वापस radix_tree_lookup(&ep->stream_info->trb_address_map,
				address >> TRB_SEGMENT_SHIFT);
	वापस ep->ring;
पूर्ण

/*
 * Change an endpoपूर्णांक's पूर्णांकernal काष्ठाure so it supports stream IDs.  The
 * number of requested streams includes stream 0, which cannot be used by device
 * drivers.
 *
 * The number of stream contexts in the stream context array may be bigger than
 * the number of streams the driver wants to use.  This is because the number of
 * stream context array entries must be a घातer of two.
 */
काष्ठा xhci_stream_info *xhci_alloc_stream_info(काष्ठा xhci_hcd *xhci,
		अचिन्हित पूर्णांक num_stream_ctxs,
		अचिन्हित पूर्णांक num_streams,
		अचिन्हित पूर्णांक max_packet, gfp_t mem_flags)
अणु
	काष्ठा xhci_stream_info *stream_info;
	u32 cur_stream;
	काष्ठा xhci_ring *cur_ring;
	u64 addr;
	पूर्णांक ret;
	काष्ठा device *dev = xhci_to_hcd(xhci)->self.sysdev;

	xhci_dbg(xhci, "Allocating %u streams and %u "
			"stream context array entries.\n",
			num_streams, num_stream_ctxs);
	अगर (xhci->cmd_ring_reserved_trbs == MAX_RSVD_CMD_TRBS) अणु
		xhci_dbg(xhci, "Command ring has no reserved TRBs available\n");
		वापस शून्य;
	पूर्ण
	xhci->cmd_ring_reserved_trbs++;

	stream_info = kzalloc_node(माप(*stream_info), mem_flags,
			dev_to_node(dev));
	अगर (!stream_info)
		जाओ cleanup_trbs;

	stream_info->num_streams = num_streams;
	stream_info->num_stream_ctxs = num_stream_ctxs;

	/* Initialize the array of भव poपूर्णांकers to stream rings. */
	stream_info->stream_rings = kसुस्मृति_node(
			num_streams, माप(काष्ठा xhci_ring *), mem_flags,
			dev_to_node(dev));
	अगर (!stream_info->stream_rings)
		जाओ cleanup_info;

	/* Initialize the array of DMA addresses क्रम stream rings क्रम the HW. */
	stream_info->stream_ctx_array = xhci_alloc_stream_ctx(xhci,
			num_stream_ctxs, &stream_info->ctx_array_dma,
			mem_flags);
	अगर (!stream_info->stream_ctx_array)
		जाओ cleanup_ctx;
	स_रखो(stream_info->stream_ctx_array, 0,
			माप(काष्ठा xhci_stream_ctx)*num_stream_ctxs);

	/* Allocate everything needed to मुक्त the stream rings later */
	stream_info->मुक्त_streams_command =
		xhci_alloc_command_with_ctx(xhci, true, mem_flags);
	अगर (!stream_info->मुक्त_streams_command)
		जाओ cleanup_ctx;

	INIT_RADIX_TREE(&stream_info->trb_address_map, GFP_ATOMIC);

	/* Allocate rings क्रम all the streams that the driver will use,
	 * and add their segment DMA addresses to the radix tree.
	 * Stream 0 is reserved.
	 */

	क्रम (cur_stream = 1; cur_stream < num_streams; cur_stream++) अणु
		stream_info->stream_rings[cur_stream] =
			xhci_ring_alloc(xhci, 2, 1, TYPE_STREAM, max_packet,
					mem_flags);
		cur_ring = stream_info->stream_rings[cur_stream];
		अगर (!cur_ring)
			जाओ cleanup_rings;
		cur_ring->stream_id = cur_stream;
		cur_ring->trb_address_map = &stream_info->trb_address_map;
		/* Set deq ptr, cycle bit, and stream context type */
		addr = cur_ring->first_seg->dma |
			SCT_FOR_CTX(SCT_PRI_TR) |
			cur_ring->cycle_state;
		stream_info->stream_ctx_array[cur_stream].stream_ring =
			cpu_to_le64(addr);
		xhci_dbg(xhci, "Setting stream %d ring ptr to 0x%08llx\n",
				cur_stream, (अचिन्हित दीर्घ दीर्घ) addr);

		ret = xhci_update_stream_mapping(cur_ring, mem_flags);
		अगर (ret) अणु
			xhci_ring_मुक्त(xhci, cur_ring);
			stream_info->stream_rings[cur_stream] = शून्य;
			जाओ cleanup_rings;
		पूर्ण
	पूर्ण
	/* Leave the other unused stream ring poपूर्णांकers in the stream context
	 * array initialized to zero.  This will cause the xHC to give us an
	 * error अगर the device asks क्रम a stream ID we करोn't have setup (अगर it
	 * was any other way, the host controller would assume the ring is
	 * "empty" and रुको क्रमever क्रम data to be queued to that stream ID).
	 */

	वापस stream_info;

cleanup_rings:
	क्रम (cur_stream = 1; cur_stream < num_streams; cur_stream++) अणु
		cur_ring = stream_info->stream_rings[cur_stream];
		अगर (cur_ring) अणु
			xhci_ring_मुक्त(xhci, cur_ring);
			stream_info->stream_rings[cur_stream] = शून्य;
		पूर्ण
	पूर्ण
	xhci_मुक्त_command(xhci, stream_info->मुक्त_streams_command);
cleanup_ctx:
	kमुक्त(stream_info->stream_rings);
cleanup_info:
	kमुक्त(stream_info);
cleanup_trbs:
	xhci->cmd_ring_reserved_trbs--;
	वापस शून्य;
पूर्ण
/*
 * Sets the MaxPStreams field and the Linear Stream Array field.
 * Sets the dequeue poपूर्णांकer to the stream context array.
 */
व्योम xhci_setup_streams_ep_input_ctx(काष्ठा xhci_hcd *xhci,
		काष्ठा xhci_ep_ctx *ep_ctx,
		काष्ठा xhci_stream_info *stream_info)
अणु
	u32 max_primary_streams;
	/* MaxPStreams is the number of stream context array entries, not the
	 * number we're actually using.  Must be in 2^(MaxPstreams + 1) क्रमmat.
	 * fls(0) = 0, fls(0x1) = 1, fls(0x10) = 2, fls(0x100) = 3, etc.
	 */
	max_primary_streams = fls(stream_info->num_stream_ctxs) - 2;
	xhci_dbg_trace(xhci,  trace_xhci_dbg_context_change,
			"Setting number of stream ctx array entries to %u",
			1 << (max_primary_streams + 1));
	ep_ctx->ep_info &= cpu_to_le32(~EP_MAXPSTREAMS_MASK);
	ep_ctx->ep_info |= cpu_to_le32(EP_MAXPSTREAMS(max_primary_streams)
				       | EP_HAS_LSA);
	ep_ctx->deq  = cpu_to_le64(stream_info->ctx_array_dma);
पूर्ण

/*
 * Sets the MaxPStreams field and the Linear Stream Array field to 0.
 * Reinstalls the "normal" endpoपूर्णांक ring (at its previous dequeue mark,
 * not at the beginning of the ring).
 */
व्योम xhci_setup_no_streams_ep_input_ctx(काष्ठा xhci_ep_ctx *ep_ctx,
		काष्ठा xhci_virt_ep *ep)
अणु
	dma_addr_t addr;
	ep_ctx->ep_info &= cpu_to_le32(~(EP_MAXPSTREAMS_MASK | EP_HAS_LSA));
	addr = xhci_trb_virt_to_dma(ep->ring->deq_seg, ep->ring->dequeue);
	ep_ctx->deq  = cpu_to_le64(addr | ep->ring->cycle_state);
पूर्ण

/* Frees all stream contexts associated with the endpoपूर्णांक,
 *
 * Caller should fix the endpoपूर्णांक context streams fields.
 */
व्योम xhci_मुक्त_stream_info(काष्ठा xhci_hcd *xhci,
		काष्ठा xhci_stream_info *stream_info)
अणु
	पूर्णांक cur_stream;
	काष्ठा xhci_ring *cur_ring;

	अगर (!stream_info)
		वापस;

	क्रम (cur_stream = 1; cur_stream < stream_info->num_streams;
			cur_stream++) अणु
		cur_ring = stream_info->stream_rings[cur_stream];
		अगर (cur_ring) अणु
			xhci_ring_मुक्त(xhci, cur_ring);
			stream_info->stream_rings[cur_stream] = शून्य;
		पूर्ण
	पूर्ण
	xhci_मुक्त_command(xhci, stream_info->मुक्त_streams_command);
	xhci->cmd_ring_reserved_trbs--;
	अगर (stream_info->stream_ctx_array)
		xhci_मुक्त_stream_ctx(xhci,
				stream_info->num_stream_ctxs,
				stream_info->stream_ctx_array,
				stream_info->ctx_array_dma);

	kमुक्त(stream_info->stream_rings);
	kमुक्त(stream_info);
पूर्ण


/***************** Device context manipulation *************************/

अटल व्योम xhci_init_endpoपूर्णांक_समयr(काष्ठा xhci_hcd *xhci,
		काष्ठा xhci_virt_ep *ep)
अणु
	समयr_setup(&ep->stop_cmd_समयr, xhci_stop_endpoपूर्णांक_command_watchकरोg,
		    0);
	ep->xhci = xhci;
पूर्ण

अटल व्योम xhci_मुक्त_tt_info(काष्ठा xhci_hcd *xhci,
		काष्ठा xhci_virt_device *virt_dev,
		पूर्णांक slot_id)
अणु
	काष्ठा list_head *tt_list_head;
	काष्ठा xhci_tt_bw_info *tt_info, *next;
	bool slot_found = false;

	/* If the device never made it past the Set Address stage,
	 * it may not have the real_port set correctly.
	 */
	अगर (virt_dev->real_port == 0 ||
			virt_dev->real_port > HCS_MAX_PORTS(xhci->hcs_params1)) अणु
		xhci_dbg(xhci, "Bad real port.\n");
		वापस;
	पूर्ण

	tt_list_head = &(xhci->rh_bw[virt_dev->real_port - 1].tts);
	list_क्रम_each_entry_safe(tt_info, next, tt_list_head, tt_list) अणु
		/* Multi-TT hubs will have more than one entry */
		अगर (tt_info->slot_id == slot_id) अणु
			slot_found = true;
			list_del(&tt_info->tt_list);
			kमुक्त(tt_info);
		पूर्ण अन्यथा अगर (slot_found) अणु
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

पूर्णांक xhci_alloc_tt_info(काष्ठा xhci_hcd *xhci,
		काष्ठा xhci_virt_device *virt_dev,
		काष्ठा usb_device *hdev,
		काष्ठा usb_tt *tt, gfp_t mem_flags)
अणु
	काष्ठा xhci_tt_bw_info		*tt_info;
	अचिन्हित पूर्णांक			num_ports;
	पूर्णांक				i, j;
	काष्ठा device *dev = xhci_to_hcd(xhci)->self.sysdev;

	अगर (!tt->multi)
		num_ports = 1;
	अन्यथा
		num_ports = hdev->maxchild;

	क्रम (i = 0; i < num_ports; i++, tt_info++) अणु
		काष्ठा xhci_पूर्णांकerval_bw_table *bw_table;

		tt_info = kzalloc_node(माप(*tt_info), mem_flags,
				dev_to_node(dev));
		अगर (!tt_info)
			जाओ मुक्त_tts;
		INIT_LIST_HEAD(&tt_info->tt_list);
		list_add(&tt_info->tt_list,
				&xhci->rh_bw[virt_dev->real_port - 1].tts);
		tt_info->slot_id = virt_dev->udev->slot_id;
		अगर (tt->multi)
			tt_info->ttport = i+1;
		bw_table = &tt_info->bw_table;
		क्रम (j = 0; j < XHCI_MAX_INTERVAL; j++)
			INIT_LIST_HEAD(&bw_table->पूर्णांकerval_bw[j].endpoपूर्णांकs);
	पूर्ण
	वापस 0;

मुक्त_tts:
	xhci_मुक्त_tt_info(xhci, virt_dev, virt_dev->udev->slot_id);
	वापस -ENOMEM;
पूर्ण


/* All the xhci_tds in the ring's TD list should be मुक्तd at this poपूर्णांक.
 * Should be called with xhci->lock held अगर there is any chance the TT lists
 * will be manipulated by the configure endpoपूर्णांक, allocate device, or update
 * hub functions जबतक this function is removing the TT entries from the list.
 */
व्योम xhci_मुक्त_virt_device(काष्ठा xhci_hcd *xhci, पूर्णांक slot_id)
अणु
	काष्ठा xhci_virt_device *dev;
	पूर्णांक i;
	पूर्णांक old_active_eps = 0;

	/* Slot ID 0 is reserved */
	अगर (slot_id == 0 || !xhci->devs[slot_id])
		वापस;

	dev = xhci->devs[slot_id];

	xhci->dcbaa->dev_context_ptrs[slot_id] = 0;
	अगर (!dev)
		वापस;

	trace_xhci_मुक्त_virt_device(dev);

	अगर (dev->tt_info)
		old_active_eps = dev->tt_info->active_eps;

	क्रम (i = 0; i < 31; i++) अणु
		अगर (dev->eps[i].ring)
			xhci_ring_मुक्त(xhci, dev->eps[i].ring);
		अगर (dev->eps[i].stream_info)
			xhci_मुक्त_stream_info(xhci,
					dev->eps[i].stream_info);
		/* Endpoपूर्णांकs on the TT/root port lists should have been हटाओd
		 * when usb_disable_device() was called क्रम the device.
		 * We can't drop them anyway, because the udev might have gone
		 * away by this poपूर्णांक, and we can't tell what speed it was.
		 */
		अगर (!list_empty(&dev->eps[i].bw_endpoपूर्णांक_list))
			xhci_warn(xhci, "Slot %u endpoint %u "
					"not removed from BW list!\n",
					slot_id, i);
	पूर्ण
	/* If this is a hub, मुक्त the TT(s) from the TT list */
	xhci_मुक्त_tt_info(xhci, dev, slot_id);
	/* If necessary, update the number of active TTs on this root port */
	xhci_update_tt_active_eps(xhci, dev, old_active_eps);

	अगर (dev->in_ctx)
		xhci_मुक्त_container_ctx(xhci, dev->in_ctx);
	अगर (dev->out_ctx)
		xhci_मुक्त_container_ctx(xhci, dev->out_ctx);

	अगर (dev->udev && dev->udev->slot_id)
		dev->udev->slot_id = 0;
	kमुक्त(xhci->devs[slot_id]);
	xhci->devs[slot_id] = शून्य;
पूर्ण

/*
 * Free a virt_device काष्ठाure.
 * If the virt_device added a tt_info (a hub) and has children poपूर्णांकing to
 * that tt_info, then मुक्त the child first. Recursive.
 * We can't rely on udev at this poपूर्णांक to find child-parent relationships.
 */
अटल व्योम xhci_मुक्त_virt_devices_depth_first(काष्ठा xhci_hcd *xhci, पूर्णांक slot_id)
अणु
	काष्ठा xhci_virt_device *vdev;
	काष्ठा list_head *tt_list_head;
	काष्ठा xhci_tt_bw_info *tt_info, *next;
	पूर्णांक i;

	vdev = xhci->devs[slot_id];
	अगर (!vdev)
		वापस;

	अगर (vdev->real_port == 0 ||
			vdev->real_port > HCS_MAX_PORTS(xhci->hcs_params1)) अणु
		xhci_dbg(xhci, "Bad vdev->real_port.\n");
		जाओ out;
	पूर्ण

	tt_list_head = &(xhci->rh_bw[vdev->real_port - 1].tts);
	list_क्रम_each_entry_safe(tt_info, next, tt_list_head, tt_list) अणु
		/* is this a hub device that added a tt_info to the tts list */
		अगर (tt_info->slot_id == slot_id) अणु
			/* are any devices using this tt_info? */
			क्रम (i = 1; i < HCS_MAX_SLOTS(xhci->hcs_params1); i++) अणु
				vdev = xhci->devs[i];
				अगर (vdev && (vdev->tt_info == tt_info))
					xhci_मुक्त_virt_devices_depth_first(
						xhci, i);
			पूर्ण
		पूर्ण
	पूर्ण
out:
	/* we are now at a leaf device */
	xhci_debugfs_हटाओ_slot(xhci, slot_id);
	xhci_मुक्त_virt_device(xhci, slot_id);
पूर्ण

पूर्णांक xhci_alloc_virt_device(काष्ठा xhci_hcd *xhci, पूर्णांक slot_id,
		काष्ठा usb_device *udev, gfp_t flags)
अणु
	काष्ठा xhci_virt_device *dev;
	पूर्णांक i;

	/* Slot ID 0 is reserved */
	अगर (slot_id == 0 || xhci->devs[slot_id]) अणु
		xhci_warn(xhci, "Bad Slot ID %d\n", slot_id);
		वापस 0;
	पूर्ण

	dev = kzalloc(माप(*dev), flags);
	अगर (!dev)
		वापस 0;

	dev->slot_id = slot_id;

	/* Allocate the (output) device context that will be used in the HC. */
	dev->out_ctx = xhci_alloc_container_ctx(xhci, XHCI_CTX_TYPE_DEVICE, flags);
	अगर (!dev->out_ctx)
		जाओ fail;

	xhci_dbg(xhci, "Slot %d output ctx = 0x%llx (dma)\n", slot_id,
			(अचिन्हित दीर्घ दीर्घ)dev->out_ctx->dma);

	/* Allocate the (input) device context क्रम address device command */
	dev->in_ctx = xhci_alloc_container_ctx(xhci, XHCI_CTX_TYPE_INPUT, flags);
	अगर (!dev->in_ctx)
		जाओ fail;

	xhci_dbg(xhci, "Slot %d input ctx = 0x%llx (dma)\n", slot_id,
			(अचिन्हित दीर्घ दीर्घ)dev->in_ctx->dma);

	/* Initialize the cancellation list and watchकरोg समयrs क्रम each ep */
	क्रम (i = 0; i < 31; i++) अणु
		dev->eps[i].ep_index = i;
		dev->eps[i].vdev = dev;
		xhci_init_endpoपूर्णांक_समयr(xhci, &dev->eps[i]);
		INIT_LIST_HEAD(&dev->eps[i].cancelled_td_list);
		INIT_LIST_HEAD(&dev->eps[i].bw_endpoपूर्णांक_list);
	पूर्ण

	/* Allocate endpoपूर्णांक 0 ring */
	dev->eps[0].ring = xhci_ring_alloc(xhci, 2, 1, TYPE_CTRL, 0, flags);
	अगर (!dev->eps[0].ring)
		जाओ fail;

	dev->udev = udev;

	/* Poपूर्णांक to output device context in dcbaa. */
	xhci->dcbaa->dev_context_ptrs[slot_id] = cpu_to_le64(dev->out_ctx->dma);
	xhci_dbg(xhci, "Set slot id %d dcbaa entry %p to 0x%llx\n",
		 slot_id,
		 &xhci->dcbaa->dev_context_ptrs[slot_id],
		 le64_to_cpu(xhci->dcbaa->dev_context_ptrs[slot_id]));

	trace_xhci_alloc_virt_device(dev);

	xhci->devs[slot_id] = dev;

	वापस 1;
fail:

	अगर (dev->in_ctx)
		xhci_मुक्त_container_ctx(xhci, dev->in_ctx);
	अगर (dev->out_ctx)
		xhci_मुक्त_container_ctx(xhci, dev->out_ctx);
	kमुक्त(dev);

	वापस 0;
पूर्ण

व्योम xhci_copy_ep0_dequeue_पूर्णांकo_input_ctx(काष्ठा xhci_hcd *xhci,
		काष्ठा usb_device *udev)
अणु
	काष्ठा xhci_virt_device *virt_dev;
	काष्ठा xhci_ep_ctx	*ep0_ctx;
	काष्ठा xhci_ring	*ep_ring;

	virt_dev = xhci->devs[udev->slot_id];
	ep0_ctx = xhci_get_ep_ctx(xhci, virt_dev->in_ctx, 0);
	ep_ring = virt_dev->eps[0].ring;
	/*
	 * FIXME we करोn't keep track of the dequeue poपूर्णांकer very well after a
	 * Set TR dequeue poपूर्णांकer, so we're setting the dequeue poपूर्णांकer of the
	 * host to our enqueue poपूर्णांकer.  This should only be called after a
	 * configured device has reset, so all control transfers should have
	 * been completed or cancelled beक्रमe the reset.
	 */
	ep0_ctx->deq = cpu_to_le64(xhci_trb_virt_to_dma(ep_ring->enq_seg,
							ep_ring->enqueue)
				   | ep_ring->cycle_state);
पूर्ण

/*
 * The xHCI roothub may have ports of dअगरfering speeds in any order in the port
 * status रेजिस्टरs.
 *
 * The xHCI hardware wants to know the roothub port number that the USB device
 * is attached to (or the roothub port its ancestor hub is attached to).  All we
 * know is the index of that port under either the USB 2.0 or the USB 3.0
 * roothub, but that करोesn't give us the real index पूर्णांकo the HW port status
 * रेजिस्टरs. Call xhci_find_raw_port_number() to get real index.
 */
अटल u32 xhci_find_real_port_number(काष्ठा xhci_hcd *xhci,
		काष्ठा usb_device *udev)
अणु
	काष्ठा usb_device *top_dev;
	काष्ठा usb_hcd *hcd;

	अगर (udev->speed >= USB_SPEED_SUPER)
		hcd = xhci->shared_hcd;
	अन्यथा
		hcd = xhci->मुख्य_hcd;

	क्रम (top_dev = udev; top_dev->parent && top_dev->parent->parent;
			top_dev = top_dev->parent)
		/* Found device below root hub */;

	वापस	xhci_find_raw_port_number(hcd, top_dev->portnum);
पूर्ण

/* Setup an xHCI भव device क्रम a Set Address command */
पूर्णांक xhci_setup_addressable_virt_dev(काष्ठा xhci_hcd *xhci, काष्ठा usb_device *udev)
अणु
	काष्ठा xhci_virt_device *dev;
	काष्ठा xhci_ep_ctx	*ep0_ctx;
	काष्ठा xhci_slot_ctx    *slot_ctx;
	u32			port_num;
	u32			max_packets;
	काष्ठा usb_device *top_dev;

	dev = xhci->devs[udev->slot_id];
	/* Slot ID 0 is reserved */
	अगर (udev->slot_id == 0 || !dev) अणु
		xhci_warn(xhci, "Slot ID %d is not assigned to this device\n",
				udev->slot_id);
		वापस -EINVAL;
	पूर्ण
	ep0_ctx = xhci_get_ep_ctx(xhci, dev->in_ctx, 0);
	slot_ctx = xhci_get_slot_ctx(xhci, dev->in_ctx);

	/* 3) Only the control endpoपूर्णांक is valid - one endpoपूर्णांक context */
	slot_ctx->dev_info |= cpu_to_le32(LAST_CTX(1) | udev->route);
	चयन (udev->speed) अणु
	हाल USB_SPEED_SUPER_PLUS:
		slot_ctx->dev_info |= cpu_to_le32(SLOT_SPEED_SSP);
		max_packets = MAX_PACKET(512);
		अवरोध;
	हाल USB_SPEED_SUPER:
		slot_ctx->dev_info |= cpu_to_le32(SLOT_SPEED_SS);
		max_packets = MAX_PACKET(512);
		अवरोध;
	हाल USB_SPEED_HIGH:
		slot_ctx->dev_info |= cpu_to_le32(SLOT_SPEED_HS);
		max_packets = MAX_PACKET(64);
		अवरोध;
	/* USB core guesses at a 64-byte max packet first क्रम FS devices */
	हाल USB_SPEED_FULL:
		slot_ctx->dev_info |= cpu_to_le32(SLOT_SPEED_FS);
		max_packets = MAX_PACKET(64);
		अवरोध;
	हाल USB_SPEED_LOW:
		slot_ctx->dev_info |= cpu_to_le32(SLOT_SPEED_LS);
		max_packets = MAX_PACKET(8);
		अवरोध;
	हाल USB_SPEED_WIRELESS:
		xhci_dbg(xhci, "FIXME xHCI doesn't support wireless speeds\n");
		वापस -EINVAL;
	शेष:
		/* Speed was set earlier, this shouldn't happen. */
		वापस -EINVAL;
	पूर्ण
	/* Find the root hub port this device is under */
	port_num = xhci_find_real_port_number(xhci, udev);
	अगर (!port_num)
		वापस -EINVAL;
	slot_ctx->dev_info2 |= cpu_to_le32(ROOT_HUB_PORT(port_num));
	/* Set the port number in the भव_device to the faked port number */
	क्रम (top_dev = udev; top_dev->parent && top_dev->parent->parent;
			top_dev = top_dev->parent)
		/* Found device below root hub */;
	dev->fake_port = top_dev->portnum;
	dev->real_port = port_num;
	xhci_dbg(xhci, "Set root hub portnum to %d\n", port_num);
	xhci_dbg(xhci, "Set fake root hub portnum to %d\n", dev->fake_port);

	/* Find the right bandwidth table that this device will be a part of.
	 * If this is a full speed device attached directly to a root port (or a
	 * decendent of one), it counts as a primary bandwidth करोमुख्य, not a
	 * secondary bandwidth करोमुख्य under a TT.  An xhci_tt_info काष्ठाure
	 * will never be created क्रम the HS root hub.
	 */
	अगर (!udev->tt || !udev->tt->hub->parent) अणु
		dev->bw_table = &xhci->rh_bw[port_num - 1].bw_table;
	पूर्ण अन्यथा अणु
		काष्ठा xhci_root_port_bw_info *rh_bw;
		काष्ठा xhci_tt_bw_info *tt_bw;

		rh_bw = &xhci->rh_bw[port_num - 1];
		/* Find the right TT. */
		list_क्रम_each_entry(tt_bw, &rh_bw->tts, tt_list) अणु
			अगर (tt_bw->slot_id != udev->tt->hub->slot_id)
				जारी;

			अगर (!dev->udev->tt->multi ||
					(udev->tt->multi &&
					 tt_bw->ttport == dev->udev->ttport)) अणु
				dev->bw_table = &tt_bw->bw_table;
				dev->tt_info = tt_bw;
				अवरोध;
			पूर्ण
		पूर्ण
		अगर (!dev->tt_info)
			xhci_warn(xhci, "WARN: Didn't find a matching TT\n");
	पूर्ण

	/* Is this a LS/FS device under an बाह्यal HS hub? */
	अगर (udev->tt && udev->tt->hub->parent) अणु
		slot_ctx->tt_info = cpu_to_le32(udev->tt->hub->slot_id |
						(udev->ttport << 8));
		अगर (udev->tt->multi)
			slot_ctx->dev_info |= cpu_to_le32(DEV_MTT);
	पूर्ण
	xhci_dbg(xhci, "udev->tt = %p\n", udev->tt);
	xhci_dbg(xhci, "udev->ttport = 0x%x\n", udev->ttport);

	/* Step 4 - ring alपढ़ोy allocated */
	/* Step 5 */
	ep0_ctx->ep_info2 = cpu_to_le32(EP_TYPE(CTRL_EP));

	/* EP 0 can handle "burst" sizes of 1, so Max Burst Size field is 0 */
	ep0_ctx->ep_info2 |= cpu_to_le32(MAX_BURST(0) | ERROR_COUNT(3) |
					 max_packets);

	ep0_ctx->deq = cpu_to_le64(dev->eps[0].ring->first_seg->dma |
				   dev->eps[0].ring->cycle_state);

	trace_xhci_setup_addressable_virt_device(dev);

	/* Steps 7 and 8 were करोne in xhci_alloc_virt_device() */

	वापस 0;
पूर्ण

/*
 * Convert पूर्णांकerval expressed as 2^(bInterval - 1) == पूर्णांकerval पूर्णांकo
 * straight exponent value 2^n == पूर्णांकerval.
 *
 */
अटल अचिन्हित पूर्णांक xhci_parse_exponent_पूर्णांकerval(काष्ठा usb_device *udev,
		काष्ठा usb_host_endpoपूर्णांक *ep)
अणु
	अचिन्हित पूर्णांक पूर्णांकerval;

	पूर्णांकerval = clamp_val(ep->desc.bInterval, 1, 16) - 1;
	अगर (पूर्णांकerval != ep->desc.bInterval - 1)
		dev_warn(&udev->dev,
			 "ep %#x - rounding interval to %d %sframes\n",
			 ep->desc.bEndpoपूर्णांकAddress,
			 1 << पूर्णांकerval,
			 udev->speed == USB_SPEED_FULL ? "" : "micro");

	अगर (udev->speed == USB_SPEED_FULL) अणु
		/*
		 * Full speed isoc endpoपूर्णांकs specअगरy पूर्णांकerval in frames,
		 * not microframes. We are using microframes everywhere,
		 * so adjust accordingly.
		 */
		पूर्णांकerval += 3;	/* 1 frame = 2^3 uframes */
	पूर्ण

	वापस पूर्णांकerval;
पूर्ण

/*
 * Convert bInterval expressed in microframes (in 1-255 range) to exponent of
 * microframes, rounded करोwn to nearest घातer of 2.
 */
अटल अचिन्हित पूर्णांक xhci_microframes_to_exponent(काष्ठा usb_device *udev,
		काष्ठा usb_host_endpoपूर्णांक *ep, अचिन्हित पूर्णांक desc_पूर्णांकerval,
		अचिन्हित पूर्णांक min_exponent, अचिन्हित पूर्णांक max_exponent)
अणु
	अचिन्हित पूर्णांक पूर्णांकerval;

	पूर्णांकerval = fls(desc_पूर्णांकerval) - 1;
	पूर्णांकerval = clamp_val(पूर्णांकerval, min_exponent, max_exponent);
	अगर ((1 << पूर्णांकerval) != desc_पूर्णांकerval)
		dev_dbg(&udev->dev,
			 "ep %#x - rounding interval to %d microframes, ep desc says %d microframes\n",
			 ep->desc.bEndpoपूर्णांकAddress,
			 1 << पूर्णांकerval,
			 desc_पूर्णांकerval);

	वापस पूर्णांकerval;
पूर्ण

अटल अचिन्हित पूर्णांक xhci_parse_microframe_पूर्णांकerval(काष्ठा usb_device *udev,
		काष्ठा usb_host_endpoपूर्णांक *ep)
अणु
	अगर (ep->desc.bInterval == 0)
		वापस 0;
	वापस xhci_microframes_to_exponent(udev, ep,
			ep->desc.bInterval, 0, 15);
पूर्ण


अटल अचिन्हित पूर्णांक xhci_parse_frame_पूर्णांकerval(काष्ठा usb_device *udev,
		काष्ठा usb_host_endpoपूर्णांक *ep)
अणु
	वापस xhci_microframes_to_exponent(udev, ep,
			ep->desc.bInterval * 8, 3, 10);
पूर्ण

/* Return the polling or NAK पूर्णांकerval.
 *
 * The polling पूर्णांकerval is expressed in "microframes".  If xHCI's Interval field
 * is set to N, it will service the endpoपूर्णांक every 2^(Interval)*125us.
 *
 * The NAK पूर्णांकerval is one NAK per 1 to 255 microframes, or no NAKs अगर पूर्णांकerval
 * is set to 0.
 */
अटल अचिन्हित पूर्णांक xhci_get_endpoपूर्णांक_पूर्णांकerval(काष्ठा usb_device *udev,
		काष्ठा usb_host_endpoपूर्णांक *ep)
अणु
	अचिन्हित पूर्णांक पूर्णांकerval = 0;

	चयन (udev->speed) अणु
	हाल USB_SPEED_HIGH:
		/* Max NAK rate */
		अगर (usb_endpoपूर्णांक_xfer_control(&ep->desc) ||
		    usb_endpoपूर्णांक_xfer_bulk(&ep->desc)) अणु
			पूर्णांकerval = xhci_parse_microframe_पूर्णांकerval(udev, ep);
			अवरोध;
		पूर्ण
		fallthrough;	/* SS and HS isoc/पूर्णांक have same decoding */

	हाल USB_SPEED_SUPER_PLUS:
	हाल USB_SPEED_SUPER:
		अगर (usb_endpoपूर्णांक_xfer_पूर्णांक(&ep->desc) ||
		    usb_endpoपूर्णांक_xfer_isoc(&ep->desc)) अणु
			पूर्णांकerval = xhci_parse_exponent_पूर्णांकerval(udev, ep);
		पूर्ण
		अवरोध;

	हाल USB_SPEED_FULL:
		अगर (usb_endpoपूर्णांक_xfer_isoc(&ep->desc)) अणु
			पूर्णांकerval = xhci_parse_exponent_पूर्णांकerval(udev, ep);
			अवरोध;
		पूर्ण
		/*
		 * Fall through क्रम पूर्णांकerrupt endpoपूर्णांक पूर्णांकerval decoding
		 * since it uses the same rules as low speed पूर्णांकerrupt
		 * endpoपूर्णांकs.
		 */
		fallthrough;

	हाल USB_SPEED_LOW:
		अगर (usb_endpoपूर्णांक_xfer_पूर्णांक(&ep->desc) ||
		    usb_endpoपूर्णांक_xfer_isoc(&ep->desc)) अणु

			पूर्णांकerval = xhci_parse_frame_पूर्णांकerval(udev, ep);
		पूर्ण
		अवरोध;

	शेष:
		BUG();
	पूर्ण
	वापस पूर्णांकerval;
पूर्ण

/* The "Mult" field in the endpoपूर्णांक context is only set क्रम SuperSpeed isoc eps.
 * High speed endpoपूर्णांक descriptors can define "the number of additional
 * transaction opportunities per microframe", but that goes in the Max Burst
 * endpoपूर्णांक context field.
 */
अटल u32 xhci_get_endpoपूर्णांक_mult(काष्ठा usb_device *udev,
		काष्ठा usb_host_endpoपूर्णांक *ep)
अणु
	अगर (udev->speed < USB_SPEED_SUPER ||
			!usb_endpoपूर्णांक_xfer_isoc(&ep->desc))
		वापस 0;
	वापस ep->ss_ep_comp.bmAttributes;
पूर्ण

अटल u32 xhci_get_endpoपूर्णांक_max_burst(काष्ठा usb_device *udev,
				       काष्ठा usb_host_endpoपूर्णांक *ep)
अणु
	/* Super speed and Plus have max burst in ep companion desc */
	अगर (udev->speed >= USB_SPEED_SUPER)
		वापस ep->ss_ep_comp.bMaxBurst;

	अगर (udev->speed == USB_SPEED_HIGH &&
	    (usb_endpoपूर्णांक_xfer_isoc(&ep->desc) ||
	     usb_endpoपूर्णांक_xfer_पूर्णांक(&ep->desc)))
		वापस usb_endpoपूर्णांक_maxp_mult(&ep->desc) - 1;

	वापस 0;
पूर्ण

अटल u32 xhci_get_endpoपूर्णांक_type(काष्ठा usb_host_endpoपूर्णांक *ep)
अणु
	पूर्णांक in;

	in = usb_endpoपूर्णांक_dir_in(&ep->desc);

	चयन (usb_endpoपूर्णांक_type(&ep->desc)) अणु
	हाल USB_ENDPOINT_XFER_CONTROL:
		वापस CTRL_EP;
	हाल USB_ENDPOINT_XFER_BULK:
		वापस in ? BULK_IN_EP : BULK_OUT_EP;
	हाल USB_ENDPOINT_XFER_ISOC:
		वापस in ? ISOC_IN_EP : ISOC_OUT_EP;
	हाल USB_ENDPOINT_XFER_INT:
		वापस in ? INT_IN_EP : INT_OUT_EP;
	पूर्ण
	वापस 0;
पूर्ण

/* Return the maximum endpoपूर्णांक service पूर्णांकerval समय (ESIT) payload.
 * Basically, this is the maxpacket size, multiplied by the burst size
 * and mult size.
 */
अटल u32 xhci_get_max_esit_payload(काष्ठा usb_device *udev,
		काष्ठा usb_host_endpoपूर्णांक *ep)
अणु
	पूर्णांक max_burst;
	पूर्णांक max_packet;

	/* Only applies क्रम पूर्णांकerrupt or isochronous endpoपूर्णांकs */
	अगर (usb_endpoपूर्णांक_xfer_control(&ep->desc) ||
			usb_endpoपूर्णांक_xfer_bulk(&ep->desc))
		वापस 0;

	/* SuperSpeedPlus Isoc ep sending over 48k per esit */
	अगर ((udev->speed >= USB_SPEED_SUPER_PLUS) &&
	    USB_SS_SSP_ISOC_COMP(ep->ss_ep_comp.bmAttributes))
		वापस le32_to_cpu(ep->ssp_isoc_ep_comp.dwBytesPerInterval);
	/* SuperSpeed or SuperSpeedPlus Isoc ep with less than 48k per esit */
	अन्यथा अगर (udev->speed >= USB_SPEED_SUPER)
		वापस le16_to_cpu(ep->ss_ep_comp.wBytesPerInterval);

	max_packet = usb_endpoपूर्णांक_maxp(&ep->desc);
	max_burst = usb_endpoपूर्णांक_maxp_mult(&ep->desc);
	/* A 0 in max burst means 1 transfer per ESIT */
	वापस max_packet * max_burst;
पूर्ण

/* Set up an endpoपूर्णांक with one ring segment.  Do not allocate stream rings.
 * Drivers will have to call usb_alloc_streams() to करो that.
 */
पूर्णांक xhci_endpoपूर्णांक_init(काष्ठा xhci_hcd *xhci,
		काष्ठा xhci_virt_device *virt_dev,
		काष्ठा usb_device *udev,
		काष्ठा usb_host_endpoपूर्णांक *ep,
		gfp_t mem_flags)
अणु
	अचिन्हित पूर्णांक ep_index;
	काष्ठा xhci_ep_ctx *ep_ctx;
	काष्ठा xhci_ring *ep_ring;
	अचिन्हित पूर्णांक max_packet;
	क्रमागत xhci_ring_type ring_type;
	u32 max_esit_payload;
	u32 endpoपूर्णांक_type;
	अचिन्हित पूर्णांक max_burst;
	अचिन्हित पूर्णांक पूर्णांकerval;
	अचिन्हित पूर्णांक mult;
	अचिन्हित पूर्णांक avg_trb_len;
	अचिन्हित पूर्णांक err_count = 0;

	ep_index = xhci_get_endpoपूर्णांक_index(&ep->desc);
	ep_ctx = xhci_get_ep_ctx(xhci, virt_dev->in_ctx, ep_index);

	endpoपूर्णांक_type = xhci_get_endpoपूर्णांक_type(ep);
	अगर (!endpoपूर्णांक_type)
		वापस -EINVAL;

	ring_type = usb_endpoपूर्णांक_type(&ep->desc);

	/*
	 * Get values to fill the endpoपूर्णांक context, mostly from ep descriptor.
	 * The average TRB buffer lengt क्रम bulk endpoपूर्णांकs is unclear as we
	 * have no clue on scatter gather list entry size. For Isoc and Int,
	 * set it to max available. See xHCI 1.1 spec 4.14.1.1 क्रम details.
	 */
	max_esit_payload = xhci_get_max_esit_payload(udev, ep);
	पूर्णांकerval = xhci_get_endpoपूर्णांक_पूर्णांकerval(udev, ep);

	/* Periodic endpoपूर्णांक bInterval limit quirk */
	अगर (usb_endpoपूर्णांक_xfer_पूर्णांक(&ep->desc) ||
	    usb_endpoपूर्णांक_xfer_isoc(&ep->desc)) अणु
		अगर ((xhci->quirks & XHCI_LIMIT_ENDPOINT_INTERVAL_7) &&
		    udev->speed >= USB_SPEED_HIGH &&
		    पूर्णांकerval >= 7) अणु
			पूर्णांकerval = 6;
		पूर्ण
	पूर्ण

	mult = xhci_get_endpoपूर्णांक_mult(udev, ep);
	max_packet = usb_endpoपूर्णांक_maxp(&ep->desc);
	max_burst = xhci_get_endpoपूर्णांक_max_burst(udev, ep);
	avg_trb_len = max_esit_payload;

	/* FIXME dig Mult and streams info out of ep companion desc */

	/* Allow 3 retries क्रम everything but isoc, set CErr = 3 */
	अगर (!usb_endpoपूर्णांक_xfer_isoc(&ep->desc))
		err_count = 3;
	/* HS bulk max packet should be 512, FS bulk supports 8, 16, 32 or 64 */
	अगर (usb_endpoपूर्णांक_xfer_bulk(&ep->desc)) अणु
		अगर (udev->speed == USB_SPEED_HIGH)
			max_packet = 512;
		अगर (udev->speed == USB_SPEED_FULL) अणु
			max_packet = roundकरोwn_घात_of_two(max_packet);
			max_packet = clamp_val(max_packet, 8, 64);
		पूर्ण
	पूर्ण
	/* xHCI 1.0 and 1.1 indicates that ctrl ep avg TRB Length should be 8 */
	अगर (usb_endpoपूर्णांक_xfer_control(&ep->desc) && xhci->hci_version >= 0x100)
		avg_trb_len = 8;
	/* xhci 1.1 with LEC support करोesn't use mult field, use RsvdZ */
	अगर ((xhci->hci_version > 0x100) && HCC2_LEC(xhci->hcc_params2))
		mult = 0;

	/* Set up the endpoपूर्णांक ring */
	virt_dev->eps[ep_index].new_ring =
		xhci_ring_alloc(xhci, 2, 1, ring_type, max_packet, mem_flags);
	अगर (!virt_dev->eps[ep_index].new_ring)
		वापस -ENOMEM;

	virt_dev->eps[ep_index].skip = false;
	ep_ring = virt_dev->eps[ep_index].new_ring;

	/* Fill the endpoपूर्णांक context */
	ep_ctx->ep_info = cpu_to_le32(EP_MAX_ESIT_PAYLOAD_HI(max_esit_payload) |
				      EP_INTERVAL(पूर्णांकerval) |
				      EP_MULT(mult));
	ep_ctx->ep_info2 = cpu_to_le32(EP_TYPE(endpoपूर्णांक_type) |
				       MAX_PACKET(max_packet) |
				       MAX_BURST(max_burst) |
				       ERROR_COUNT(err_count));
	ep_ctx->deq = cpu_to_le64(ep_ring->first_seg->dma |
				  ep_ring->cycle_state);

	ep_ctx->tx_info = cpu_to_le32(EP_MAX_ESIT_PAYLOAD_LO(max_esit_payload) |
				      EP_AVG_TRB_LENGTH(avg_trb_len));

	वापस 0;
पूर्ण

व्योम xhci_endpoपूर्णांक_zero(काष्ठा xhci_hcd *xhci,
		काष्ठा xhci_virt_device *virt_dev,
		काष्ठा usb_host_endpoपूर्णांक *ep)
अणु
	अचिन्हित पूर्णांक ep_index;
	काष्ठा xhci_ep_ctx *ep_ctx;

	ep_index = xhci_get_endpoपूर्णांक_index(&ep->desc);
	ep_ctx = xhci_get_ep_ctx(xhci, virt_dev->in_ctx, ep_index);

	ep_ctx->ep_info = 0;
	ep_ctx->ep_info2 = 0;
	ep_ctx->deq = 0;
	ep_ctx->tx_info = 0;
	/* Don't मुक्त the endpoपूर्णांक ring until the set पूर्णांकerface or configuration
	 * request succeeds.
	 */
पूर्ण

व्योम xhci_clear_endpoपूर्णांक_bw_info(काष्ठा xhci_bw_info *bw_info)
अणु
	bw_info->ep_पूर्णांकerval = 0;
	bw_info->mult = 0;
	bw_info->num_packets = 0;
	bw_info->max_packet_size = 0;
	bw_info->type = 0;
	bw_info->max_esit_payload = 0;
पूर्ण

व्योम xhci_update_bw_info(काष्ठा xhci_hcd *xhci,
		काष्ठा xhci_container_ctx *in_ctx,
		काष्ठा xhci_input_control_ctx *ctrl_ctx,
		काष्ठा xhci_virt_device *virt_dev)
अणु
	काष्ठा xhci_bw_info *bw_info;
	काष्ठा xhci_ep_ctx *ep_ctx;
	अचिन्हित पूर्णांक ep_type;
	पूर्णांक i;

	क्रम (i = 1; i < 31; i++) अणु
		bw_info = &virt_dev->eps[i].bw_info;

		/* We can't tell what endpoपूर्णांक type is being dropped, but
		 * unconditionally clearing the bandwidth info क्रम non-periodic
		 * endpoपूर्णांकs should be harmless because the info will never be
		 * set in the first place.
		 */
		अगर (!EP_IS_ADDED(ctrl_ctx, i) && EP_IS_DROPPED(ctrl_ctx, i)) अणु
			/* Dropped endpoपूर्णांक */
			xhci_clear_endpoपूर्णांक_bw_info(bw_info);
			जारी;
		पूर्ण

		अगर (EP_IS_ADDED(ctrl_ctx, i)) अणु
			ep_ctx = xhci_get_ep_ctx(xhci, in_ctx, i);
			ep_type = CTX_TO_EP_TYPE(le32_to_cpu(ep_ctx->ep_info2));

			/* Ignore non-periodic endpoपूर्णांकs */
			अगर (ep_type != ISOC_OUT_EP && ep_type != INT_OUT_EP &&
					ep_type != ISOC_IN_EP &&
					ep_type != INT_IN_EP)
				जारी;

			/* Added or changed endpoपूर्णांक */
			bw_info->ep_पूर्णांकerval = CTX_TO_EP_INTERVAL(
					le32_to_cpu(ep_ctx->ep_info));
			/* Number of packets and mult are zero-based in the
			 * input context, but we want one-based क्रम the
			 * पूर्णांकerval table.
			 */
			bw_info->mult = CTX_TO_EP_MULT(
					le32_to_cpu(ep_ctx->ep_info)) + 1;
			bw_info->num_packets = CTX_TO_MAX_BURST(
					le32_to_cpu(ep_ctx->ep_info2)) + 1;
			bw_info->max_packet_size = MAX_PACKET_DECODED(
					le32_to_cpu(ep_ctx->ep_info2));
			bw_info->type = ep_type;
			bw_info->max_esit_payload = CTX_TO_MAX_ESIT_PAYLOAD(
					le32_to_cpu(ep_ctx->tx_info));
		पूर्ण
	पूर्ण
पूर्ण

/* Copy output xhci_ep_ctx to the input xhci_ep_ctx copy.
 * Useful when you want to change one particular aspect of the endpoपूर्णांक and then
 * issue a configure endpoपूर्णांक command.
 */
व्योम xhci_endpoपूर्णांक_copy(काष्ठा xhci_hcd *xhci,
		काष्ठा xhci_container_ctx *in_ctx,
		काष्ठा xhci_container_ctx *out_ctx,
		अचिन्हित पूर्णांक ep_index)
अणु
	काष्ठा xhci_ep_ctx *out_ep_ctx;
	काष्ठा xhci_ep_ctx *in_ep_ctx;

	out_ep_ctx = xhci_get_ep_ctx(xhci, out_ctx, ep_index);
	in_ep_ctx = xhci_get_ep_ctx(xhci, in_ctx, ep_index);

	in_ep_ctx->ep_info = out_ep_ctx->ep_info;
	in_ep_ctx->ep_info2 = out_ep_ctx->ep_info2;
	in_ep_ctx->deq = out_ep_ctx->deq;
	in_ep_ctx->tx_info = out_ep_ctx->tx_info;
	अगर (xhci->quirks & XHCI_MTK_HOST) अणु
		in_ep_ctx->reserved[0] = out_ep_ctx->reserved[0];
		in_ep_ctx->reserved[1] = out_ep_ctx->reserved[1];
	पूर्ण
पूर्ण

/* Copy output xhci_slot_ctx to the input xhci_slot_ctx.
 * Useful when you want to change one particular aspect of the endpoपूर्णांक and then
 * issue a configure endpoपूर्णांक command.  Only the context entries field matters,
 * but we'll copy the whole thing anyway.
 */
व्योम xhci_slot_copy(काष्ठा xhci_hcd *xhci,
		काष्ठा xhci_container_ctx *in_ctx,
		काष्ठा xhci_container_ctx *out_ctx)
अणु
	काष्ठा xhci_slot_ctx *in_slot_ctx;
	काष्ठा xhci_slot_ctx *out_slot_ctx;

	in_slot_ctx = xhci_get_slot_ctx(xhci, in_ctx);
	out_slot_ctx = xhci_get_slot_ctx(xhci, out_ctx);

	in_slot_ctx->dev_info = out_slot_ctx->dev_info;
	in_slot_ctx->dev_info2 = out_slot_ctx->dev_info2;
	in_slot_ctx->tt_info = out_slot_ctx->tt_info;
	in_slot_ctx->dev_state = out_slot_ctx->dev_state;
पूर्ण

/* Set up the scratchpad buffer array and scratchpad buffers, अगर needed. */
अटल पूर्णांक scratchpad_alloc(काष्ठा xhci_hcd *xhci, gfp_t flags)
अणु
	पूर्णांक i;
	काष्ठा device *dev = xhci_to_hcd(xhci)->self.sysdev;
	पूर्णांक num_sp = HCS_MAX_SCRATCHPAD(xhci->hcs_params2);

	xhci_dbg_trace(xhci, trace_xhci_dbg_init,
			"Allocating %d scratchpad buffers", num_sp);

	अगर (!num_sp)
		वापस 0;

	xhci->scratchpad = kzalloc_node(माप(*xhci->scratchpad), flags,
				dev_to_node(dev));
	अगर (!xhci->scratchpad)
		जाओ fail_sp;

	xhci->scratchpad->sp_array = dma_alloc_coherent(dev,
				     num_sp * माप(u64),
				     &xhci->scratchpad->sp_dma, flags);
	अगर (!xhci->scratchpad->sp_array)
		जाओ fail_sp2;

	xhci->scratchpad->sp_buffers = kसुस्मृति_node(num_sp, माप(व्योम *),
					flags, dev_to_node(dev));
	अगर (!xhci->scratchpad->sp_buffers)
		जाओ fail_sp3;

	xhci->dcbaa->dev_context_ptrs[0] = cpu_to_le64(xhci->scratchpad->sp_dma);
	क्रम (i = 0; i < num_sp; i++) अणु
		dma_addr_t dma;
		व्योम *buf = dma_alloc_coherent(dev, xhci->page_size, &dma,
					       flags);
		अगर (!buf)
			जाओ fail_sp4;

		xhci->scratchpad->sp_array[i] = dma;
		xhci->scratchpad->sp_buffers[i] = buf;
	पूर्ण

	वापस 0;

 fail_sp4:
	क्रम (i = i - 1; i >= 0; i--) अणु
		dma_मुक्त_coherent(dev, xhci->page_size,
				    xhci->scratchpad->sp_buffers[i],
				    xhci->scratchpad->sp_array[i]);
	पूर्ण

	kमुक्त(xhci->scratchpad->sp_buffers);

 fail_sp3:
	dma_मुक्त_coherent(dev, num_sp * माप(u64),
			    xhci->scratchpad->sp_array,
			    xhci->scratchpad->sp_dma);

 fail_sp2:
	kमुक्त(xhci->scratchpad);
	xhci->scratchpad = शून्य;

 fail_sp:
	वापस -ENOMEM;
पूर्ण

अटल व्योम scratchpad_मुक्त(काष्ठा xhci_hcd *xhci)
अणु
	पूर्णांक num_sp;
	पूर्णांक i;
	काष्ठा device *dev = xhci_to_hcd(xhci)->self.sysdev;

	अगर (!xhci->scratchpad)
		वापस;

	num_sp = HCS_MAX_SCRATCHPAD(xhci->hcs_params2);

	क्रम (i = 0; i < num_sp; i++) अणु
		dma_मुक्त_coherent(dev, xhci->page_size,
				    xhci->scratchpad->sp_buffers[i],
				    xhci->scratchpad->sp_array[i]);
	पूर्ण
	kमुक्त(xhci->scratchpad->sp_buffers);
	dma_मुक्त_coherent(dev, num_sp * माप(u64),
			    xhci->scratchpad->sp_array,
			    xhci->scratchpad->sp_dma);
	kमुक्त(xhci->scratchpad);
	xhci->scratchpad = शून्य;
पूर्ण

काष्ठा xhci_command *xhci_alloc_command(काष्ठा xhci_hcd *xhci,
		bool allocate_completion, gfp_t mem_flags)
अणु
	काष्ठा xhci_command *command;
	काष्ठा device *dev = xhci_to_hcd(xhci)->self.sysdev;

	command = kzalloc_node(माप(*command), mem_flags, dev_to_node(dev));
	अगर (!command)
		वापस शून्य;

	अगर (allocate_completion) अणु
		command->completion =
			kzalloc_node(माप(काष्ठा completion), mem_flags,
				dev_to_node(dev));
		अगर (!command->completion) अणु
			kमुक्त(command);
			वापस शून्य;
		पूर्ण
		init_completion(command->completion);
	पूर्ण

	command->status = 0;
	INIT_LIST_HEAD(&command->cmd_list);
	वापस command;
पूर्ण

काष्ठा xhci_command *xhci_alloc_command_with_ctx(काष्ठा xhci_hcd *xhci,
		bool allocate_completion, gfp_t mem_flags)
अणु
	काष्ठा xhci_command *command;

	command = xhci_alloc_command(xhci, allocate_completion, mem_flags);
	अगर (!command)
		वापस शून्य;

	command->in_ctx = xhci_alloc_container_ctx(xhci, XHCI_CTX_TYPE_INPUT,
						   mem_flags);
	अगर (!command->in_ctx) अणु
		kमुक्त(command->completion);
		kमुक्त(command);
		वापस शून्य;
	पूर्ण
	वापस command;
पूर्ण

व्योम xhci_urb_मुक्त_priv(काष्ठा urb_priv *urb_priv)
अणु
	kमुक्त(urb_priv);
पूर्ण

व्योम xhci_मुक्त_command(काष्ठा xhci_hcd *xhci,
		काष्ठा xhci_command *command)
अणु
	xhci_मुक्त_container_ctx(xhci,
			command->in_ctx);
	kमुक्त(command->completion);
	kमुक्त(command);
पूर्ण

पूर्णांक xhci_alloc_erst(काष्ठा xhci_hcd *xhci,
		    काष्ठा xhci_ring *evt_ring,
		    काष्ठा xhci_erst *erst,
		    gfp_t flags)
अणु
	माप_प्रकार size;
	अचिन्हित पूर्णांक val;
	काष्ठा xhci_segment *seg;
	काष्ठा xhci_erst_entry *entry;

	size = माप(काष्ठा xhci_erst_entry) * evt_ring->num_segs;
	erst->entries = dma_alloc_coherent(xhci_to_hcd(xhci)->self.sysdev,
					   size, &erst->erst_dma_addr, flags);
	अगर (!erst->entries)
		वापस -ENOMEM;

	erst->num_entries = evt_ring->num_segs;

	seg = evt_ring->first_seg;
	क्रम (val = 0; val < evt_ring->num_segs; val++) अणु
		entry = &erst->entries[val];
		entry->seg_addr = cpu_to_le64(seg->dma);
		entry->seg_size = cpu_to_le32(TRBS_PER_SEGMENT);
		entry->rsvd = 0;
		seg = seg->next;
	पूर्ण

	वापस 0;
पूर्ण

व्योम xhci_मुक्त_erst(काष्ठा xhci_hcd *xhci, काष्ठा xhci_erst *erst)
अणु
	माप_प्रकार size;
	काष्ठा device *dev = xhci_to_hcd(xhci)->self.sysdev;

	size = माप(काष्ठा xhci_erst_entry) * (erst->num_entries);
	अगर (erst->entries)
		dma_मुक्त_coherent(dev, size,
				erst->entries,
				erst->erst_dma_addr);
	erst->entries = शून्य;
पूर्ण

व्योम xhci_mem_cleanup(काष्ठा xhci_hcd *xhci)
अणु
	काष्ठा device	*dev = xhci_to_hcd(xhci)->self.sysdev;
	पूर्णांक i, j, num_ports;

	cancel_delayed_work_sync(&xhci->cmd_समयr);

	xhci_मुक्त_erst(xhci, &xhci->erst);

	अगर (xhci->event_ring)
		xhci_ring_मुक्त(xhci, xhci->event_ring);
	xhci->event_ring = शून्य;
	xhci_dbg_trace(xhci, trace_xhci_dbg_init, "Freed event ring");

	अगर (xhci->lpm_command)
		xhci_मुक्त_command(xhci, xhci->lpm_command);
	xhci->lpm_command = शून्य;
	अगर (xhci->cmd_ring)
		xhci_ring_मुक्त(xhci, xhci->cmd_ring);
	xhci->cmd_ring = शून्य;
	xhci_dbg_trace(xhci, trace_xhci_dbg_init, "Freed command ring");
	xhci_cleanup_command_queue(xhci);

	num_ports = HCS_MAX_PORTS(xhci->hcs_params1);
	क्रम (i = 0; i < num_ports && xhci->rh_bw; i++) अणु
		काष्ठा xhci_पूर्णांकerval_bw_table *bwt = &xhci->rh_bw[i].bw_table;
		क्रम (j = 0; j < XHCI_MAX_INTERVAL; j++) अणु
			काष्ठा list_head *ep = &bwt->पूर्णांकerval_bw[j].endpoपूर्णांकs;
			जबतक (!list_empty(ep))
				list_del_init(ep->next);
		पूर्ण
	पूर्ण

	क्रम (i = HCS_MAX_SLOTS(xhci->hcs_params1); i > 0; i--)
		xhci_मुक्त_virt_devices_depth_first(xhci, i);

	dma_pool_destroy(xhci->segment_pool);
	xhci->segment_pool = शून्य;
	xhci_dbg_trace(xhci, trace_xhci_dbg_init, "Freed segment pool");

	dma_pool_destroy(xhci->device_pool);
	xhci->device_pool = शून्य;
	xhci_dbg_trace(xhci, trace_xhci_dbg_init, "Freed device context pool");

	dma_pool_destroy(xhci->small_streams_pool);
	xhci->small_streams_pool = शून्य;
	xhci_dbg_trace(xhci, trace_xhci_dbg_init,
			"Freed small stream array pool");

	dma_pool_destroy(xhci->medium_streams_pool);
	xhci->medium_streams_pool = शून्य;
	xhci_dbg_trace(xhci, trace_xhci_dbg_init,
			"Freed medium stream array pool");

	अगर (xhci->dcbaa)
		dma_मुक्त_coherent(dev, माप(*xhci->dcbaa),
				xhci->dcbaa, xhci->dcbaa->dma);
	xhci->dcbaa = शून्य;

	scratchpad_मुक्त(xhci);

	अगर (!xhci->rh_bw)
		जाओ no_bw;

	क्रम (i = 0; i < num_ports; i++) अणु
		काष्ठा xhci_tt_bw_info *tt, *n;
		list_क्रम_each_entry_safe(tt, n, &xhci->rh_bw[i].tts, tt_list) अणु
			list_del(&tt->tt_list);
			kमुक्त(tt);
		पूर्ण
	पूर्ण

no_bw:
	xhci->cmd_ring_reserved_trbs = 0;
	xhci->usb2_rhub.num_ports = 0;
	xhci->usb3_rhub.num_ports = 0;
	xhci->num_active_eps = 0;
	kमुक्त(xhci->usb2_rhub.ports);
	kमुक्त(xhci->usb3_rhub.ports);
	kमुक्त(xhci->hw_ports);
	kमुक्त(xhci->rh_bw);
	kमुक्त(xhci->ext_caps);
	क्रम (i = 0; i < xhci->num_port_caps; i++)
		kमुक्त(xhci->port_caps[i].psi);
	kमुक्त(xhci->port_caps);
	xhci->num_port_caps = 0;

	xhci->usb2_rhub.ports = शून्य;
	xhci->usb3_rhub.ports = शून्य;
	xhci->hw_ports = शून्य;
	xhci->rh_bw = शून्य;
	xhci->ext_caps = शून्य;

	xhci->page_size = 0;
	xhci->page_shअगरt = 0;
	xhci->usb2_rhub.bus_state.bus_suspended = 0;
	xhci->usb3_rhub.bus_state.bus_suspended = 0;
पूर्ण

अटल पूर्णांक xhci_test_trb_in_td(काष्ठा xhci_hcd *xhci,
		काष्ठा xhci_segment *input_seg,
		जोड़ xhci_trb *start_trb,
		जोड़ xhci_trb *end_trb,
		dma_addr_t input_dma,
		काष्ठा xhci_segment *result_seg,
		अक्षर *test_name, पूर्णांक test_number)
अणु
	अचिन्हित दीर्घ दीर्घ start_dma;
	अचिन्हित दीर्घ दीर्घ end_dma;
	काष्ठा xhci_segment *seg;

	start_dma = xhci_trb_virt_to_dma(input_seg, start_trb);
	end_dma = xhci_trb_virt_to_dma(input_seg, end_trb);

	seg = trb_in_td(xhci, input_seg, start_trb, end_trb, input_dma, false);
	अगर (seg != result_seg) अणु
		xhci_warn(xhci, "WARN: %s TRB math test %d failed!\n",
				test_name, test_number);
		xhci_warn(xhci, "Tested TRB math w/ seg %p and "
				"input DMA 0x%llx\n",
				input_seg,
				(अचिन्हित दीर्घ दीर्घ) input_dma);
		xhci_warn(xhci, "starting TRB %p (0x%llx DMA), "
				"ending TRB %p (0x%llx DMA)\n",
				start_trb, start_dma,
				end_trb, end_dma);
		xhci_warn(xhci, "Expected seg %p, got seg %p\n",
				result_seg, seg);
		trb_in_td(xhci, input_seg, start_trb, end_trb, input_dma,
			  true);
		वापस -1;
	पूर्ण
	वापस 0;
पूर्ण

/* TRB math checks क्रम xhci_trb_in_td(), using the command and event rings. */
अटल पूर्णांक xhci_check_trb_in_td_math(काष्ठा xhci_hcd *xhci)
अणु
	काष्ठा अणु
		dma_addr_t		input_dma;
		काष्ठा xhci_segment	*result_seg;
	पूर्ण simple_test_vector [] = अणु
		/* A zeroed DMA field should fail */
		अणु 0, शून्य पूर्ण,
		/* One TRB beक्रमe the ring start should fail */
		अणु xhci->event_ring->first_seg->dma - 16, शून्य पूर्ण,
		/* One byte beक्रमe the ring start should fail */
		अणु xhci->event_ring->first_seg->dma - 1, शून्य पूर्ण,
		/* Starting TRB should succeed */
		अणु xhci->event_ring->first_seg->dma, xhci->event_ring->first_seg पूर्ण,
		/* Ending TRB should succeed */
		अणु xhci->event_ring->first_seg->dma + (TRBS_PER_SEGMENT - 1)*16,
			xhci->event_ring->first_seg पूर्ण,
		/* One byte after the ring end should fail */
		अणु xhci->event_ring->first_seg->dma + (TRBS_PER_SEGMENT - 1)*16 + 1, शून्य पूर्ण,
		/* One TRB after the ring end should fail */
		अणु xhci->event_ring->first_seg->dma + (TRBS_PER_SEGMENT)*16, शून्य पूर्ण,
		/* An address of all ones should fail */
		अणु (dma_addr_t) (~0), शून्य पूर्ण,
	पूर्ण;
	काष्ठा अणु
		काष्ठा xhci_segment	*input_seg;
		जोड़ xhci_trb		*start_trb;
		जोड़ xhci_trb		*end_trb;
		dma_addr_t		input_dma;
		काष्ठा xhci_segment	*result_seg;
	पूर्ण complex_test_vector [] = अणु
		/* Test feeding a valid DMA address from a dअगरferent ring */
		अणु	.input_seg = xhci->event_ring->first_seg,
			.start_trb = xhci->event_ring->first_seg->trbs,
			.end_trb = &xhci->event_ring->first_seg->trbs[TRBS_PER_SEGMENT - 1],
			.input_dma = xhci->cmd_ring->first_seg->dma,
			.result_seg = शून्य,
		पूर्ण,
		/* Test feeding a valid end TRB from a dअगरferent ring */
		अणु	.input_seg = xhci->event_ring->first_seg,
			.start_trb = xhci->event_ring->first_seg->trbs,
			.end_trb = &xhci->cmd_ring->first_seg->trbs[TRBS_PER_SEGMENT - 1],
			.input_dma = xhci->cmd_ring->first_seg->dma,
			.result_seg = शून्य,
		पूर्ण,
		/* Test feeding a valid start and end TRB from a dअगरferent ring */
		अणु	.input_seg = xhci->event_ring->first_seg,
			.start_trb = xhci->cmd_ring->first_seg->trbs,
			.end_trb = &xhci->cmd_ring->first_seg->trbs[TRBS_PER_SEGMENT - 1],
			.input_dma = xhci->cmd_ring->first_seg->dma,
			.result_seg = शून्य,
		पूर्ण,
		/* TRB in this ring, but after this TD */
		अणु	.input_seg = xhci->event_ring->first_seg,
			.start_trb = &xhci->event_ring->first_seg->trbs[0],
			.end_trb = &xhci->event_ring->first_seg->trbs[3],
			.input_dma = xhci->event_ring->first_seg->dma + 4*16,
			.result_seg = शून्य,
		पूर्ण,
		/* TRB in this ring, but beक्रमe this TD */
		अणु	.input_seg = xhci->event_ring->first_seg,
			.start_trb = &xhci->event_ring->first_seg->trbs[3],
			.end_trb = &xhci->event_ring->first_seg->trbs[6],
			.input_dma = xhci->event_ring->first_seg->dma + 2*16,
			.result_seg = शून्य,
		पूर्ण,
		/* TRB in this ring, but after this wrapped TD */
		अणु	.input_seg = xhci->event_ring->first_seg,
			.start_trb = &xhci->event_ring->first_seg->trbs[TRBS_PER_SEGMENT - 3],
			.end_trb = &xhci->event_ring->first_seg->trbs[1],
			.input_dma = xhci->event_ring->first_seg->dma + 2*16,
			.result_seg = शून्य,
		पूर्ण,
		/* TRB in this ring, but beक्रमe this wrapped TD */
		अणु	.input_seg = xhci->event_ring->first_seg,
			.start_trb = &xhci->event_ring->first_seg->trbs[TRBS_PER_SEGMENT - 3],
			.end_trb = &xhci->event_ring->first_seg->trbs[1],
			.input_dma = xhci->event_ring->first_seg->dma + (TRBS_PER_SEGMENT - 4)*16,
			.result_seg = शून्य,
		पूर्ण,
		/* TRB not in this ring, and we have a wrapped TD */
		अणु	.input_seg = xhci->event_ring->first_seg,
			.start_trb = &xhci->event_ring->first_seg->trbs[TRBS_PER_SEGMENT - 3],
			.end_trb = &xhci->event_ring->first_seg->trbs[1],
			.input_dma = xhci->cmd_ring->first_seg->dma + 2*16,
			.result_seg = शून्य,
		पूर्ण,
	पूर्ण;

	अचिन्हित पूर्णांक num_tests;
	पूर्णांक i, ret;

	num_tests = ARRAY_SIZE(simple_test_vector);
	क्रम (i = 0; i < num_tests; i++) अणु
		ret = xhci_test_trb_in_td(xhci,
				xhci->event_ring->first_seg,
				xhci->event_ring->first_seg->trbs,
				&xhci->event_ring->first_seg->trbs[TRBS_PER_SEGMENT - 1],
				simple_test_vector[i].input_dma,
				simple_test_vector[i].result_seg,
				"Simple", i);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	num_tests = ARRAY_SIZE(complex_test_vector);
	क्रम (i = 0; i < num_tests; i++) अणु
		ret = xhci_test_trb_in_td(xhci,
				complex_test_vector[i].input_seg,
				complex_test_vector[i].start_trb,
				complex_test_vector[i].end_trb,
				complex_test_vector[i].input_dma,
				complex_test_vector[i].result_seg,
				"Complex", i);
		अगर (ret < 0)
			वापस ret;
	पूर्ण
	xhci_dbg(xhci, "TRB math tests passed.\n");
	वापस 0;
पूर्ण

अटल व्योम xhci_set_hc_event_deq(काष्ठा xhci_hcd *xhci)
अणु
	u64 temp;
	dma_addr_t deq;

	deq = xhci_trb_virt_to_dma(xhci->event_ring->deq_seg,
			xhci->event_ring->dequeue);
	अगर (!deq)
		xhci_warn(xhci, "WARN something wrong with SW event ring "
				"dequeue ptr.\n");
	/* Update HC event ring dequeue poपूर्णांकer */
	temp = xhci_पढ़ो_64(xhci, &xhci->ir_set->erst_dequeue);
	temp &= ERST_PTR_MASK;
	/* Don't clear the EHB bit (which is RW1C) because
	 * there might be more events to service.
	 */
	temp &= ~ERST_EHB;
	xhci_dbg_trace(xhci, trace_xhci_dbg_init,
			"// Write event ring dequeue pointer, "
			"preserving EHB bit");
	xhci_ग_लिखो_64(xhci, ((u64) deq & (u64) ~ERST_PTR_MASK) | temp,
			&xhci->ir_set->erst_dequeue);
पूर्ण

अटल व्योम xhci_add_in_port(काष्ठा xhci_hcd *xhci, अचिन्हित पूर्णांक num_ports,
		__le32 __iomem *addr, पूर्णांक max_caps)
अणु
	u32 temp, port_offset, port_count;
	पूर्णांक i;
	u8 major_revision, minor_revision;
	काष्ठा xhci_hub *rhub;
	काष्ठा device *dev = xhci_to_hcd(xhci)->self.sysdev;
	काष्ठा xhci_port_cap *port_cap;

	temp = पढ़ोl(addr);
	major_revision = XHCI_EXT_PORT_MAJOR(temp);
	minor_revision = XHCI_EXT_PORT_MINOR(temp);

	अगर (major_revision == 0x03) अणु
		rhub = &xhci->usb3_rhub;
		/*
		 * Some hosts incorrectly use sub-minor version क्रम minor
		 * version (i.e. 0x02 instead of 0x20 क्रम bcdUSB 0x320 and 0x01
		 * क्रम bcdUSB 0x310). Since there is no USB release with sub
		 * minor version 0x301 to 0x309, we can assume that they are
		 * incorrect and fix it here.
		 */
		अगर (minor_revision > 0x00 && minor_revision < 0x10)
			minor_revision <<= 4;
	पूर्ण अन्यथा अगर (major_revision <= 0x02) अणु
		rhub = &xhci->usb2_rhub;
	पूर्ण अन्यथा अणु
		xhci_warn(xhci, "Ignoring unknown port speed, "
				"Ext Cap %p, revision = 0x%x\n",
				addr, major_revision);
		/* Ignoring port protocol we can't understand. FIXME */
		वापस;
	पूर्ण
	rhub->maj_rev = XHCI_EXT_PORT_MAJOR(temp);

	अगर (rhub->min_rev < minor_revision)
		rhub->min_rev = minor_revision;

	/* Port offset and count in the third dword, see section 7.2 */
	temp = पढ़ोl(addr + 2);
	port_offset = XHCI_EXT_PORT_OFF(temp);
	port_count = XHCI_EXT_PORT_COUNT(temp);
	xhci_dbg_trace(xhci, trace_xhci_dbg_init,
			"Ext Cap %p, port offset = %u, "
			"count = %u, revision = 0x%x",
			addr, port_offset, port_count, major_revision);
	/* Port count includes the current port offset */
	अगर (port_offset == 0 || (port_offset + port_count - 1) > num_ports)
		/* WTF? "Valid values are ै 1ै  to MaxPorts" */
		वापस;

	port_cap = &xhci->port_caps[xhci->num_port_caps++];
	अगर (xhci->num_port_caps > max_caps)
		वापस;

	port_cap->maj_rev = major_revision;
	port_cap->min_rev = minor_revision;
	port_cap->psi_count = XHCI_EXT_PORT_PSIC(temp);

	अगर (port_cap->psi_count) अणु
		port_cap->psi = kसुस्मृति_node(port_cap->psi_count,
					     माप(*port_cap->psi),
					     GFP_KERNEL, dev_to_node(dev));
		अगर (!port_cap->psi)
			port_cap->psi_count = 0;

		port_cap->psi_uid_count++;
		क्रम (i = 0; i < port_cap->psi_count; i++) अणु
			port_cap->psi[i] = पढ़ोl(addr + 4 + i);

			/* count unique ID values, two consecutive entries can
			 * have the same ID अगर link is assymetric
			 */
			अगर (i && (XHCI_EXT_PORT_PSIV(port_cap->psi[i]) !=
				  XHCI_EXT_PORT_PSIV(port_cap->psi[i - 1])))
				port_cap->psi_uid_count++;

			xhci_dbg(xhci, "PSIV:%d PSIE:%d PLT:%d PFD:%d LP:%d PSIM:%d\n",
				  XHCI_EXT_PORT_PSIV(port_cap->psi[i]),
				  XHCI_EXT_PORT_PSIE(port_cap->psi[i]),
				  XHCI_EXT_PORT_PLT(port_cap->psi[i]),
				  XHCI_EXT_PORT_PFD(port_cap->psi[i]),
				  XHCI_EXT_PORT_LP(port_cap->psi[i]),
				  XHCI_EXT_PORT_PSIM(port_cap->psi[i]));
		पूर्ण
	पूर्ण
	/* cache usb2 port capabilities */
	अगर (major_revision < 0x03 && xhci->num_ext_caps < max_caps)
		xhci->ext_caps[xhci->num_ext_caps++] = temp;

	अगर ((xhci->hci_version >= 0x100) && (major_revision != 0x03) &&
		 (temp & XHCI_HLC)) अणु
		xhci_dbg_trace(xhci, trace_xhci_dbg_init,
			       "xHCI 1.0: support USB2 hardware lpm");
		xhci->hw_lpm_support = 1;
	पूर्ण

	port_offset--;
	क्रम (i = port_offset; i < (port_offset + port_count); i++) अणु
		काष्ठा xhci_port *hw_port = &xhci->hw_ports[i];
		/* Duplicate entry.  Ignore the port अगर the revisions dअगरfer. */
		अगर (hw_port->rhub) अणु
			xhci_warn(xhci, "Duplicate port entry, Ext Cap %p,"
					" port %u\n", addr, i);
			xhci_warn(xhci, "Port was marked as USB %u, "
					"duplicated as USB %u\n",
					hw_port->rhub->maj_rev, major_revision);
			/* Only adjust the roothub port counts अगर we haven't
			 * found a similar duplicate.
			 */
			अगर (hw_port->rhub != rhub &&
				 hw_port->hcd_portnum != DUPLICATE_ENTRY) अणु
				hw_port->rhub->num_ports--;
				hw_port->hcd_portnum = DUPLICATE_ENTRY;
			पूर्ण
			जारी;
		पूर्ण
		hw_port->rhub = rhub;
		hw_port->port_cap = port_cap;
		rhub->num_ports++;
	पूर्ण
	/* FIXME: Should we disable ports not in the Extended Capabilities? */
पूर्ण

अटल व्योम xhci_create_rhub_port_array(काष्ठा xhci_hcd *xhci,
					काष्ठा xhci_hub *rhub, gfp_t flags)
अणु
	पूर्णांक port_index = 0;
	पूर्णांक i;
	काष्ठा device *dev = xhci_to_hcd(xhci)->self.sysdev;

	अगर (!rhub->num_ports)
		वापस;
	rhub->ports = kसुस्मृति_node(rhub->num_ports, माप(*rhub->ports),
			flags, dev_to_node(dev));
	अगर (!rhub->ports)
		वापस;

	क्रम (i = 0; i < HCS_MAX_PORTS(xhci->hcs_params1); i++) अणु
		अगर (xhci->hw_ports[i].rhub != rhub ||
		    xhci->hw_ports[i].hcd_portnum == DUPLICATE_ENTRY)
			जारी;
		xhci->hw_ports[i].hcd_portnum = port_index;
		rhub->ports[port_index] = &xhci->hw_ports[i];
		port_index++;
		अगर (port_index == rhub->num_ports)
			अवरोध;
	पूर्ण
पूर्ण

/*
 * Scan the Extended Capabilities क्रम the "Supported Protocol Capabilities" that
 * specअगरy what speeds each port is supposed to be.  We can't count on the port
 * speed bits in the PORTSC रेजिस्टर being correct until a device is connected,
 * but we need to set up the two fake roothubs with the correct number of USB
 * 3.0 and USB 2.0 ports at host controller initialization समय.
 */
अटल पूर्णांक xhci_setup_port_arrays(काष्ठा xhci_hcd *xhci, gfp_t flags)
अणु
	व्योम __iomem *base;
	u32 offset;
	अचिन्हित पूर्णांक num_ports;
	पूर्णांक i, j;
	पूर्णांक cap_count = 0;
	u32 cap_start;
	काष्ठा device *dev = xhci_to_hcd(xhci)->self.sysdev;

	num_ports = HCS_MAX_PORTS(xhci->hcs_params1);
	xhci->hw_ports = kसुस्मृति_node(num_ports, माप(*xhci->hw_ports),
				flags, dev_to_node(dev));
	अगर (!xhci->hw_ports)
		वापस -ENOMEM;

	क्रम (i = 0; i < num_ports; i++) अणु
		xhci->hw_ports[i].addr = &xhci->op_regs->port_status_base +
			NUM_PORT_REGS * i;
		xhci->hw_ports[i].hw_portnum = i;
	पूर्ण

	xhci->rh_bw = kसुस्मृति_node(num_ports, माप(*xhci->rh_bw), flags,
				   dev_to_node(dev));
	अगर (!xhci->rh_bw)
		वापस -ENOMEM;
	क्रम (i = 0; i < num_ports; i++) अणु
		काष्ठा xhci_पूर्णांकerval_bw_table *bw_table;

		INIT_LIST_HEAD(&xhci->rh_bw[i].tts);
		bw_table = &xhci->rh_bw[i].bw_table;
		क्रम (j = 0; j < XHCI_MAX_INTERVAL; j++)
			INIT_LIST_HEAD(&bw_table->पूर्णांकerval_bw[j].endpoपूर्णांकs);
	पूर्ण
	base = &xhci->cap_regs->hc_capbase;

	cap_start = xhci_find_next_ext_cap(base, 0, XHCI_EXT_CAPS_PROTOCOL);
	अगर (!cap_start) अणु
		xhci_err(xhci, "No Extended Capability registers, unable to set up roothub\n");
		वापस -ENODEV;
	पूर्ण

	offset = cap_start;
	/* count extended protocol capability entries क्रम later caching */
	जबतक (offset) अणु
		cap_count++;
		offset = xhci_find_next_ext_cap(base, offset,
						      XHCI_EXT_CAPS_PROTOCOL);
	पूर्ण

	xhci->ext_caps = kसुस्मृति_node(cap_count, माप(*xhci->ext_caps),
				flags, dev_to_node(dev));
	अगर (!xhci->ext_caps)
		वापस -ENOMEM;

	xhci->port_caps = kसुस्मृति_node(cap_count, माप(*xhci->port_caps),
				flags, dev_to_node(dev));
	अगर (!xhci->port_caps)
		वापस -ENOMEM;

	offset = cap_start;

	जबतक (offset) अणु
		xhci_add_in_port(xhci, num_ports, base + offset, cap_count);
		अगर (xhci->usb2_rhub.num_ports + xhci->usb3_rhub.num_ports ==
		    num_ports)
			अवरोध;
		offset = xhci_find_next_ext_cap(base, offset,
						XHCI_EXT_CAPS_PROTOCOL);
	पूर्ण
	अगर (xhci->usb2_rhub.num_ports == 0 && xhci->usb3_rhub.num_ports == 0) अणु
		xhci_warn(xhci, "No ports on the roothubs?\n");
		वापस -ENODEV;
	पूर्ण
	xhci_dbg_trace(xhci, trace_xhci_dbg_init,
		       "Found %u USB 2.0 ports and %u USB 3.0 ports.",
		       xhci->usb2_rhub.num_ports, xhci->usb3_rhub.num_ports);

	/* Place limits on the number of roothub ports so that the hub
	 * descriptors aren't दीर्घer than the USB core will allocate.
	 */
	अगर (xhci->usb3_rhub.num_ports > USB_SS_MAXPORTS) अणु
		xhci_dbg_trace(xhci, trace_xhci_dbg_init,
				"Limiting USB 3.0 roothub ports to %u.",
				USB_SS_MAXPORTS);
		xhci->usb3_rhub.num_ports = USB_SS_MAXPORTS;
	पूर्ण
	अगर (xhci->usb2_rhub.num_ports > USB_MAXCHILDREN) अणु
		xhci_dbg_trace(xhci, trace_xhci_dbg_init,
				"Limiting USB 2.0 roothub ports to %u.",
				USB_MAXCHILDREN);
		xhci->usb2_rhub.num_ports = USB_MAXCHILDREN;
	पूर्ण

	/*
	 * Note we could have all USB 3.0 ports, or all USB 2.0 ports.
	 * Not sure how the USB core will handle a hub with no ports...
	 */

	xhci_create_rhub_port_array(xhci, &xhci->usb2_rhub, flags);
	xhci_create_rhub_port_array(xhci, &xhci->usb3_rhub, flags);

	वापस 0;
पूर्ण

पूर्णांक xhci_mem_init(काष्ठा xhci_hcd *xhci, gfp_t flags)
अणु
	dma_addr_t	dma;
	काष्ठा device	*dev = xhci_to_hcd(xhci)->self.sysdev;
	अचिन्हित पूर्णांक	val, val2;
	u64		val_64;
	u32		page_size, temp;
	पूर्णांक		i, ret;

	INIT_LIST_HEAD(&xhci->cmd_list);

	/* init command समयout work */
	INIT_DELAYED_WORK(&xhci->cmd_समयr, xhci_handle_command_समयout);
	init_completion(&xhci->cmd_ring_stop_completion);

	page_size = पढ़ोl(&xhci->op_regs->page_size);
	xhci_dbg_trace(xhci, trace_xhci_dbg_init,
			"Supported page size register = 0x%x", page_size);
	क्रम (i = 0; i < 16; i++) अणु
		अगर ((0x1 & page_size) != 0)
			अवरोध;
		page_size = page_size >> 1;
	पूर्ण
	अगर (i < 16)
		xhci_dbg_trace(xhci, trace_xhci_dbg_init,
			"Supported page size of %iK", (1 << (i+12)) / 1024);
	अन्यथा
		xhci_warn(xhci, "WARN: no supported page size\n");
	/* Use 4K pages, since that's common and the minimum the HC supports */
	xhci->page_shअगरt = 12;
	xhci->page_size = 1 << xhci->page_shअगरt;
	xhci_dbg_trace(xhci, trace_xhci_dbg_init,
			"HCD page size set to %iK", xhci->page_size / 1024);

	/*
	 * Program the Number of Device Slots Enabled field in the CONFIG
	 * रेजिस्टर with the max value of slots the HC can handle.
	 */
	val = HCS_MAX_SLOTS(पढ़ोl(&xhci->cap_regs->hcs_params1));
	xhci_dbg_trace(xhci, trace_xhci_dbg_init,
			"// xHC can handle at most %d device slots.", val);
	val2 = पढ़ोl(&xhci->op_regs->config_reg);
	val |= (val2 & ~HCS_SLOTS_MASK);
	xhci_dbg_trace(xhci, trace_xhci_dbg_init,
			"// Setting Max device slots reg = 0x%x.", val);
	ग_लिखोl(val, &xhci->op_regs->config_reg);

	/*
	 * xHCI section 5.4.6 - करोorbell array must be
	 * "physically contiguous and 64-byte (cache line) aligned".
	 */
	xhci->dcbaa = dma_alloc_coherent(dev, माप(*xhci->dcbaa), &dma,
			flags);
	अगर (!xhci->dcbaa)
		जाओ fail;
	xhci->dcbaa->dma = dma;
	xhci_dbg_trace(xhci, trace_xhci_dbg_init,
			"// Device context base array address = 0x%llx (DMA), %p (virt)",
			(अचिन्हित दीर्घ दीर्घ)xhci->dcbaa->dma, xhci->dcbaa);
	xhci_ग_लिखो_64(xhci, dma, &xhci->op_regs->dcbaa_ptr);

	/*
	 * Initialize the ring segment pool.  The ring must be a contiguous
	 * काष्ठाure comprised of TRBs.  The TRBs must be 16 byte aligned,
	 * however, the command ring segment needs 64-byte aligned segments
	 * and our use of dma addresses in the trb_address_map radix tree needs
	 * TRB_SEGMENT_SIZE alignment, so we pick the greater alignment need.
	 */
	xhci->segment_pool = dma_pool_create("xHCI ring segments", dev,
			TRB_SEGMENT_SIZE, TRB_SEGMENT_SIZE, xhci->page_size);

	/* See Table 46 and Note on Figure 55 */
	xhci->device_pool = dma_pool_create("xHCI input/output contexts", dev,
			2112, 64, xhci->page_size);
	अगर (!xhci->segment_pool || !xhci->device_pool)
		जाओ fail;

	/* Linear stream context arrays करोn't have any boundary restrictions,
	 * and only need to be 16-byte aligned.
	 */
	xhci->small_streams_pool =
		dma_pool_create("xHCI 256 byte stream ctx arrays",
			dev, SMALL_STREAM_ARRAY_SIZE, 16, 0);
	xhci->medium_streams_pool =
		dma_pool_create("xHCI 1KB stream ctx arrays",
			dev, MEDIUM_STREAM_ARRAY_SIZE, 16, 0);
	/* Any stream context array bigger than MEDIUM_STREAM_ARRAY_SIZE
	 * will be allocated with dma_alloc_coherent()
	 */

	अगर (!xhci->small_streams_pool || !xhci->medium_streams_pool)
		जाओ fail;

	/* Set up the command ring to have one segments क्रम now. */
	xhci->cmd_ring = xhci_ring_alloc(xhci, 1, 1, TYPE_COMMAND, 0, flags);
	अगर (!xhci->cmd_ring)
		जाओ fail;
	xhci_dbg_trace(xhci, trace_xhci_dbg_init,
			"Allocated command ring at %p", xhci->cmd_ring);
	xhci_dbg_trace(xhci, trace_xhci_dbg_init, "First segment DMA is 0x%llx",
			(अचिन्हित दीर्घ दीर्घ)xhci->cmd_ring->first_seg->dma);

	/* Set the address in the Command Ring Control रेजिस्टर */
	val_64 = xhci_पढ़ो_64(xhci, &xhci->op_regs->cmd_ring);
	val_64 = (val_64 & (u64) CMD_RING_RSVD_BITS) |
		(xhci->cmd_ring->first_seg->dma & (u64) ~CMD_RING_RSVD_BITS) |
		xhci->cmd_ring->cycle_state;
	xhci_dbg_trace(xhci, trace_xhci_dbg_init,
			"// Setting command ring address to 0x%016llx", val_64);
	xhci_ग_लिखो_64(xhci, val_64, &xhci->op_regs->cmd_ring);

	xhci->lpm_command = xhci_alloc_command_with_ctx(xhci, true, flags);
	अगर (!xhci->lpm_command)
		जाओ fail;

	/* Reserve one command ring TRB क्रम disabling LPM.
	 * Since the USB core grअसल the shared usb_bus bandwidth mutex beक्रमe
	 * disabling LPM, we only need to reserve one TRB क्रम all devices.
	 */
	xhci->cmd_ring_reserved_trbs++;

	val = पढ़ोl(&xhci->cap_regs->db_off);
	val &= DBOFF_MASK;
	xhci_dbg_trace(xhci, trace_xhci_dbg_init,
			"// Doorbell array is located at offset 0x%x"
			" from cap regs base addr", val);
	xhci->dba = (व्योम __iomem *) xhci->cap_regs + val;
	/* Set ir_set to पूर्णांकerrupt रेजिस्टर set 0 */
	xhci->ir_set = &xhci->run_regs->ir_set[0];

	/*
	 * Event ring setup: Allocate a normal ring, but also setup
	 * the event ring segment table (ERST).  Section 4.9.3.
	 */
	xhci_dbg_trace(xhci, trace_xhci_dbg_init, "// Allocating event ring");
	xhci->event_ring = xhci_ring_alloc(xhci, ERST_NUM_SEGS, 1, TYPE_EVENT,
					0, flags);
	अगर (!xhci->event_ring)
		जाओ fail;
	अगर (xhci_check_trb_in_td_math(xhci) < 0)
		जाओ fail;

	ret = xhci_alloc_erst(xhci, xhci->event_ring, &xhci->erst, flags);
	अगर (ret)
		जाओ fail;

	/* set ERST count with the number of entries in the segment table */
	val = पढ़ोl(&xhci->ir_set->erst_size);
	val &= ERST_SIZE_MASK;
	val |= ERST_NUM_SEGS;
	xhci_dbg_trace(xhci, trace_xhci_dbg_init,
			"// Write ERST size = %i to ir_set 0 (some bits preserved)",
			val);
	ग_लिखोl(val, &xhci->ir_set->erst_size);

	xhci_dbg_trace(xhci, trace_xhci_dbg_init,
			"// Set ERST entries to point to event ring.");
	/* set the segment table base address */
	xhci_dbg_trace(xhci, trace_xhci_dbg_init,
			"// Set ERST base address for ir_set 0 = 0x%llx",
			(अचिन्हित दीर्घ दीर्घ)xhci->erst.erst_dma_addr);
	val_64 = xhci_पढ़ो_64(xhci, &xhci->ir_set->erst_base);
	val_64 &= ERST_PTR_MASK;
	val_64 |= (xhci->erst.erst_dma_addr & (u64) ~ERST_PTR_MASK);
	xhci_ग_लिखो_64(xhci, val_64, &xhci->ir_set->erst_base);

	/* Set the event ring dequeue address */
	xhci_set_hc_event_deq(xhci);
	xhci_dbg_trace(xhci, trace_xhci_dbg_init,
			"Wrote ERST address to ir_set 0.");

	/*
	 * XXX: Might need to set the Interrupter Moderation Register to
	 * something other than the शेष (~1ms minimum between पूर्णांकerrupts).
	 * See section 5.5.1.2.
	 */
	क्रम (i = 0; i < MAX_HC_SLOTS; i++)
		xhci->devs[i] = शून्य;
	क्रम (i = 0; i < USB_MAXCHILDREN; i++) अणु
		xhci->usb2_rhub.bus_state.resume_करोne[i] = 0;
		xhci->usb3_rhub.bus_state.resume_करोne[i] = 0;
		/* Only the USB 2.0 completions will ever be used. */
		init_completion(&xhci->usb2_rhub.bus_state.rनिकास_करोne[i]);
		init_completion(&xhci->usb3_rhub.bus_state.u3निकास_करोne[i]);
	पूर्ण

	अगर (scratchpad_alloc(xhci, flags))
		जाओ fail;
	अगर (xhci_setup_port_arrays(xhci, flags))
		जाओ fail;

	/* Enable USB 3.0 device notअगरications क्रम function remote wake, which
	 * is necessary क्रम allowing USB 3.0 devices to करो remote wakeup from
	 * U3 (device suspend).
	 */
	temp = पढ़ोl(&xhci->op_regs->dev_notअगरication);
	temp &= ~DEV_NOTE_MASK;
	temp |= DEV_NOTE_FWAKE;
	ग_लिखोl(temp, &xhci->op_regs->dev_notअगरication);

	वापस 0;

fail:
	xhci_halt(xhci);
	xhci_reset(xhci);
	xhci_mem_cleanup(xhci);
	वापस -ENOMEM;
पूर्ण
