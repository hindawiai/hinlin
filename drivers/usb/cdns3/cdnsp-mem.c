<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Cadence CDNSP DRD Driver.
 *
 * Copyright (C) 2020 Cadence.
 *
 * Author: Pawel Laszczak <pawell@cadence.com>
 *
 * Code based on Linux XHCI driver.
 * Origin: Copyright (C) 2008 Intel Corp.
 */

#समावेश <linux/dma-mapping.h>
#समावेश <linux/dmapool.h>
#समावेश <linux/slab.h>
#समावेश <linux/usb.h>

#समावेश "cdnsp-gadget.h"
#समावेश "cdnsp-trace.h"

अटल व्योम cdnsp_मुक्त_stream_info(काष्ठा cdnsp_device *pdev,
				   काष्ठा cdnsp_ep *pep);
/*
 * Allocates a generic ring segment from the ring pool, sets the dma address,
 * initializes the segment to zero, and sets the निजी next poपूर्णांकer to शून्य.
 *
 * "All components of all Command and Transfer TRBs shall be initialized to '0'"
 */
अटल काष्ठा cdnsp_segment *cdnsp_segment_alloc(काष्ठा cdnsp_device *pdev,
						 अचिन्हित पूर्णांक cycle_state,
						 अचिन्हित पूर्णांक max_packet,
						 gfp_t flags)
अणु
	काष्ठा cdnsp_segment *seg;
	dma_addr_t dma;
	पूर्णांक i;

	seg = kzalloc(माप(*seg), flags);
	अगर (!seg)
		वापस शून्य;

	seg->trbs = dma_pool_zalloc(pdev->segment_pool, flags, &dma);
	अगर (!seg->trbs) अणु
		kमुक्त(seg);
		वापस शून्य;
	पूर्ण

	अगर (max_packet) अणु
		seg->bounce_buf = kzalloc(max_packet, flags | GFP_DMA);
		अगर (!seg->bounce_buf)
			जाओ मुक्त_dma;
	पूर्ण

	/* If the cycle state is 0, set the cycle bit to 1 क्रम all the TRBs. */
	अगर (cycle_state == 0) अणु
		क्रम (i = 0; i < TRBS_PER_SEGMENT; i++)
			seg->trbs[i].link.control |= cpu_to_le32(TRB_CYCLE);
	पूर्ण
	seg->dma = dma;
	seg->next = शून्य;

	वापस seg;

मुक्त_dma:
	dma_pool_मुक्त(pdev->segment_pool, seg->trbs, dma);
	kमुक्त(seg);

	वापस शून्य;
पूर्ण

अटल व्योम cdnsp_segment_मुक्त(काष्ठा cdnsp_device *pdev,
			       काष्ठा cdnsp_segment *seg)
अणु
	अगर (seg->trbs)
		dma_pool_मुक्त(pdev->segment_pool, seg->trbs, seg->dma);

	kमुक्त(seg->bounce_buf);
	kमुक्त(seg);
पूर्ण

अटल व्योम cdnsp_मुक्त_segments_क्रम_ring(काष्ठा cdnsp_device *pdev,
					 काष्ठा cdnsp_segment *first)
अणु
	काष्ठा cdnsp_segment *seg;

	seg = first->next;

	जबतक (seg != first) अणु
		काष्ठा cdnsp_segment *next = seg->next;

		cdnsp_segment_मुक्त(pdev, seg);
		seg = next;
	पूर्ण

	cdnsp_segment_मुक्त(pdev, first);
पूर्ण

/*
 * Make the prev segment poपूर्णांक to the next segment.
 *
 * Change the last TRB in the prev segment to be a Link TRB which poपूर्णांकs to the
 * DMA address of the next segment. The caller needs to set any Link TRB
 * related flags, such as End TRB, Toggle Cycle, and no snoop.
 */
अटल व्योम cdnsp_link_segments(काष्ठा cdnsp_device *pdev,
				काष्ठा cdnsp_segment *prev,
				काष्ठा cdnsp_segment *next,
				क्रमागत cdnsp_ring_type type)
अणु
	काष्ठा cdnsp_link_trb *link;
	u32 val;

	अगर (!prev || !next)
		वापस;

	prev->next = next;
	अगर (type != TYPE_EVENT) अणु
		link = &prev->trbs[TRBS_PER_SEGMENT - 1].link;
		link->segment_ptr = cpu_to_le64(next->dma);

		/*
		 * Set the last TRB in the segment to have a TRB type ID
		 * of Link TRB
		 */
		val = le32_to_cpu(link->control);
		val &= ~TRB_TYPE_BITMASK;
		val |= TRB_TYPE(TRB_LINK);
		link->control = cpu_to_le32(val);
	पूर्ण
पूर्ण

/*
 * Link the ring to the new segments.
 * Set Toggle Cycle क्रम the new ring अगर needed.
 */
अटल व्योम cdnsp_link_rings(काष्ठा cdnsp_device *pdev,
			     काष्ठा cdnsp_ring *ring,
			     काष्ठा cdnsp_segment *first,
			     काष्ठा cdnsp_segment *last,
			     अचिन्हित पूर्णांक num_segs)
अणु
	काष्ठा cdnsp_segment *next;

	अगर (!ring || !first || !last)
		वापस;

	next = ring->enq_seg->next;
	cdnsp_link_segments(pdev, ring->enq_seg, first, ring->type);
	cdnsp_link_segments(pdev, last, next, ring->type);
	ring->num_segs += num_segs;
	ring->num_trbs_मुक्त += (TRBS_PER_SEGMENT - 1) * num_segs;

	अगर (ring->type != TYPE_EVENT && ring->enq_seg == ring->last_seg) अणु
		ring->last_seg->trbs[TRBS_PER_SEGMENT - 1].link.control &=
			~cpu_to_le32(LINK_TOGGLE);
		last->trbs[TRBS_PER_SEGMENT - 1].link.control |=
			cpu_to_le32(LINK_TOGGLE);
		ring->last_seg = last;
	पूर्ण
पूर्ण

/*
 * We need a radix tree क्रम mapping physical addresses of TRBs to which stream
 * ID they beदीर्घ to. We need to करो this because the device controller won't
 * tell us which stream ring the TRB came from. We could store the stream ID
 * in an event data TRB, but that करोesn't help us क्रम the cancellation हाल,
 * since the endpoपूर्णांक may stop beक्रमe it reaches that event data TRB.
 *
 * The radix tree maps the upper portion of the TRB DMA address to a ring
 * segment that has the same upper portion of DMA addresses. For example,
 * say I have segments of size 1KB, that are always 1KB aligned. A segment may
 * start at 0x10c91000 and end at 0x10c913f0. If I use the upper 10 bits, the
 * key to the stream ID is 0x43244. I can use the DMA address of the TRB to
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
 * The radix tree uses an अचिन्हित दीर्घ as a key pair. On 32-bit प्रणालीs, an
 * अचिन्हित दीर्घ will be 32-bits; on a 64-bit प्रणाली an अचिन्हित दीर्घ will be
 * 64-bits. Since we only request 32-bit DMA addresses, we can use that as the
 * key on 32-bit or 64-bit प्रणालीs (it would also be fine अगर we asked क्रम 64-bit
 * PCI DMA addresses on a 64-bit प्रणाली). There might be a problem on 32-bit
 * extended प्रणालीs (where the DMA address can be bigger than 32-bits),
 * अगर we allow the PCI dma mask to be bigger than 32-bits. So करोn't करो that.
 */
अटल पूर्णांक cdnsp_insert_segment_mapping(काष्ठा radix_tree_root *trb_address_map,
					काष्ठा cdnsp_ring *ring,
					काष्ठा cdnsp_segment *seg,
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

	ret = radix_tree_insert(trb_address_map, key, ring);
	radix_tree_preload_end();

	वापस ret;
पूर्ण

अटल व्योम cdnsp_हटाओ_segment_mapping(काष्ठा radix_tree_root *trb_address_map,
					 काष्ठा cdnsp_segment *seg)
अणु
	अचिन्हित दीर्घ key;

	key = (अचिन्हित दीर्घ)(seg->dma >> TRB_SEGMENT_SHIFT);
	अगर (radix_tree_lookup(trb_address_map, key))
		radix_tree_delete(trb_address_map, key);
पूर्ण

अटल पूर्णांक cdnsp_update_stream_segment_mapping(काष्ठा radix_tree_root *trb_address_map,
					       काष्ठा cdnsp_ring *ring,
					       काष्ठा cdnsp_segment *first_seg,
					       काष्ठा cdnsp_segment *last_seg,
					       gfp_t mem_flags)
अणु
	काष्ठा cdnsp_segment *failed_seg;
	काष्ठा cdnsp_segment *seg;
	पूर्णांक ret;

	seg = first_seg;
	करो अणु
		ret = cdnsp_insert_segment_mapping(trb_address_map, ring, seg,
						   mem_flags);
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
		cdnsp_हटाओ_segment_mapping(trb_address_map, seg);
		अगर (seg == failed_seg)
			वापस ret;
		seg = seg->next;
	पूर्ण जबतक (seg != first_seg);

	वापस ret;
पूर्ण

अटल व्योम cdnsp_हटाओ_stream_mapping(काष्ठा cdnsp_ring *ring)
अणु
	काष्ठा cdnsp_segment *seg;

	seg = ring->first_seg;
	करो अणु
		cdnsp_हटाओ_segment_mapping(ring->trb_address_map, seg);
		seg = seg->next;
	पूर्ण जबतक (seg != ring->first_seg);
पूर्ण

अटल पूर्णांक cdnsp_update_stream_mapping(काष्ठा cdnsp_ring *ring)
अणु
	वापस cdnsp_update_stream_segment_mapping(ring->trb_address_map, ring,
			ring->first_seg, ring->last_seg, GFP_ATOMIC);
पूर्ण

अटल व्योम cdnsp_ring_मुक्त(काष्ठा cdnsp_device *pdev, काष्ठा cdnsp_ring *ring)
अणु
	अगर (!ring)
		वापस;

	trace_cdnsp_ring_मुक्त(ring);

	अगर (ring->first_seg) अणु
		अगर (ring->type == TYPE_STREAM)
			cdnsp_हटाओ_stream_mapping(ring);

		cdnsp_मुक्त_segments_क्रम_ring(pdev, ring->first_seg);
	पूर्ण

	kमुक्त(ring);
पूर्ण

व्योम cdnsp_initialize_ring_info(काष्ठा cdnsp_ring *ring)
अणु
	ring->enqueue = ring->first_seg->trbs;
	ring->enq_seg = ring->first_seg;
	ring->dequeue = ring->enqueue;
	ring->deq_seg = ring->first_seg;

	/*
	 * The ring is initialized to 0. The producer must ग_लिखो 1 to the cycle
	 * bit to hanकरोver ownership of the TRB, so PCS = 1. The consumer must
	 * compare CCS to the cycle bit to check ownership, so CCS = 1.
	 *
	 * New rings are initialized with cycle state equal to 1; अगर we are
	 * handling ring expansion, set the cycle state equal to the old ring.
	 */
	ring->cycle_state = 1;

	/*
	 * Each segment has a link TRB, and leave an extra TRB क्रम SW
	 * accounting purpose
	 */
	ring->num_trbs_मुक्त = ring->num_segs * (TRBS_PER_SEGMENT - 1) - 1;
पूर्ण

/* Allocate segments and link them क्रम a ring. */
अटल पूर्णांक cdnsp_alloc_segments_क्रम_ring(काष्ठा cdnsp_device *pdev,
					 काष्ठा cdnsp_segment **first,
					 काष्ठा cdnsp_segment **last,
					 अचिन्हित पूर्णांक num_segs,
					 अचिन्हित पूर्णांक cycle_state,
					 क्रमागत cdnsp_ring_type type,
					 अचिन्हित पूर्णांक max_packet,
					 gfp_t flags)
अणु
	काष्ठा cdnsp_segment *prev;

	/* Allocate first segment. */
	prev = cdnsp_segment_alloc(pdev, cycle_state, max_packet, flags);
	अगर (!prev)
		वापस -ENOMEM;

	num_segs--;
	*first = prev;

	/* Allocate all other segments. */
	जबतक (num_segs > 0) अणु
		काष्ठा cdnsp_segment	*next;

		next = cdnsp_segment_alloc(pdev, cycle_state,
					   max_packet, flags);
		अगर (!next) अणु
			cdnsp_मुक्त_segments_क्रम_ring(pdev, *first);
			वापस -ENOMEM;
		पूर्ण

		cdnsp_link_segments(pdev, prev, next, type);

		prev = next;
		num_segs--;
	पूर्ण

	cdnsp_link_segments(pdev, prev, *first, type);
	*last = prev;

	वापस 0;
पूर्ण

/*
 * Create a new ring with zero or more segments.
 *
 * Link each segment together पूर्णांकo a ring.
 * Set the end flag and the cycle toggle bit on the last segment.
 */
अटल काष्ठा cdnsp_ring *cdnsp_ring_alloc(काष्ठा cdnsp_device *pdev,
					   अचिन्हित पूर्णांक num_segs,
					   क्रमागत cdnsp_ring_type type,
					   अचिन्हित पूर्णांक max_packet,
					   gfp_t flags)
अणु
	काष्ठा cdnsp_ring *ring;
	पूर्णांक ret;

	ring = kzalloc(माप *(ring), flags);
	अगर (!ring)
		वापस शून्य;

	ring->num_segs = num_segs;
	ring->bounce_buf_len = max_packet;
	INIT_LIST_HEAD(&ring->td_list);
	ring->type = type;

	अगर (num_segs == 0)
		वापस ring;

	ret = cdnsp_alloc_segments_क्रम_ring(pdev, &ring->first_seg,
					    &ring->last_seg, num_segs,
					    1, type, max_packet, flags);
	अगर (ret)
		जाओ fail;

	/* Only event ring करोes not use link TRB. */
	अगर (type != TYPE_EVENT)
		ring->last_seg->trbs[TRBS_PER_SEGMENT - 1].link.control |=
			cpu_to_le32(LINK_TOGGLE);

	cdnsp_initialize_ring_info(ring);
	trace_cdnsp_ring_alloc(ring);
	वापस ring;
fail:
	kमुक्त(ring);
	वापस शून्य;
पूर्ण

व्योम cdnsp_मुक्त_endpoपूर्णांक_rings(काष्ठा cdnsp_device *pdev, काष्ठा cdnsp_ep *pep)
अणु
	cdnsp_ring_मुक्त(pdev, pep->ring);
	pep->ring = शून्य;
	cdnsp_मुक्त_stream_info(pdev, pep);
पूर्ण

/*
 * Expand an existing ring.
 * Allocate a new ring which has same segment numbers and link the two rings.
 */
पूर्णांक cdnsp_ring_expansion(काष्ठा cdnsp_device *pdev,
			 काष्ठा cdnsp_ring *ring,
			 अचिन्हित पूर्णांक num_trbs,
			 gfp_t flags)
अणु
	अचिन्हित पूर्णांक num_segs_needed;
	काष्ठा cdnsp_segment *first;
	काष्ठा cdnsp_segment *last;
	अचिन्हित पूर्णांक num_segs;
	पूर्णांक ret;

	num_segs_needed = (num_trbs + (TRBS_PER_SEGMENT - 1) - 1) /
			(TRBS_PER_SEGMENT - 1);

	/* Allocate number of segments we needed, or द्विगुन the ring size. */
	num_segs = max(ring->num_segs, num_segs_needed);

	ret = cdnsp_alloc_segments_क्रम_ring(pdev, &first, &last, num_segs,
					    ring->cycle_state, ring->type,
					    ring->bounce_buf_len, flags);
	अगर (ret)
		वापस -ENOMEM;

	अगर (ring->type == TYPE_STREAM)
		ret = cdnsp_update_stream_segment_mapping(ring->trb_address_map,
							  ring, first,
							  last, flags);

	अगर (ret) अणु
		cdnsp_मुक्त_segments_क्रम_ring(pdev, first);

		वापस ret;
	पूर्ण

	cdnsp_link_rings(pdev, ring, first, last, num_segs);
	trace_cdnsp_ring_expansion(ring);

	वापस 0;
पूर्ण

अटल पूर्णांक cdnsp_init_device_ctx(काष्ठा cdnsp_device *pdev)
अणु
	पूर्णांक size = HCC_64BYTE_CONTEXT(pdev->hcc_params) ? 2048 : 1024;

	pdev->out_ctx.type = CDNSP_CTX_TYPE_DEVICE;
	pdev->out_ctx.size = size;
	pdev->out_ctx.ctx_size = CTX_SIZE(pdev->hcc_params);
	pdev->out_ctx.bytes = dma_pool_zalloc(pdev->device_pool, GFP_ATOMIC,
					      &pdev->out_ctx.dma);

	अगर (!pdev->out_ctx.bytes)
		वापस -ENOMEM;

	pdev->in_ctx.type = CDNSP_CTX_TYPE_INPUT;
	pdev->in_ctx.ctx_size = pdev->out_ctx.ctx_size;
	pdev->in_ctx.size = size + pdev->out_ctx.ctx_size;
	pdev->in_ctx.bytes = dma_pool_zalloc(pdev->device_pool, GFP_ATOMIC,
					     &pdev->in_ctx.dma);

	अगर (!pdev->in_ctx.bytes) अणु
		dma_pool_मुक्त(pdev->device_pool, pdev->out_ctx.bytes,
			      pdev->out_ctx.dma);
		वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

काष्ठा cdnsp_input_control_ctx
	*cdnsp_get_input_control_ctx(काष्ठा cdnsp_container_ctx *ctx)
अणु
	अगर (ctx->type != CDNSP_CTX_TYPE_INPUT)
		वापस शून्य;

	वापस (काष्ठा cdnsp_input_control_ctx *)ctx->bytes;
पूर्ण

काष्ठा cdnsp_slot_ctx *cdnsp_get_slot_ctx(काष्ठा cdnsp_container_ctx *ctx)
अणु
	अगर (ctx->type == CDNSP_CTX_TYPE_DEVICE)
		वापस (काष्ठा cdnsp_slot_ctx *)ctx->bytes;

	वापस (काष्ठा cdnsp_slot_ctx *)(ctx->bytes + ctx->ctx_size);
पूर्ण

काष्ठा cdnsp_ep_ctx *cdnsp_get_ep_ctx(काष्ठा cdnsp_container_ctx *ctx,
				      अचिन्हित पूर्णांक ep_index)
अणु
	/* Increment ep index by offset of start of ep ctx array. */
	ep_index++;
	अगर (ctx->type == CDNSP_CTX_TYPE_INPUT)
		ep_index++;

	वापस (काष्ठा cdnsp_ep_ctx *)(ctx->bytes + (ep_index * ctx->ctx_size));
पूर्ण

अटल व्योम cdnsp_मुक्त_stream_ctx(काष्ठा cdnsp_device *pdev,
				  काष्ठा cdnsp_ep *pep)
अणु
	dma_pool_मुक्त(pdev->device_pool, pep->stream_info.stream_ctx_array,
		      pep->stream_info.ctx_array_dma);
पूर्ण

/* The stream context array must be a घातer of 2. */
अटल काष्ठा cdnsp_stream_ctx
	*cdnsp_alloc_stream_ctx(काष्ठा cdnsp_device *pdev, काष्ठा cdnsp_ep *pep)
अणु
	माप_प्रकार size = माप(काष्ठा cdnsp_stream_ctx) *
		      pep->stream_info.num_stream_ctxs;

	अगर (size > CDNSP_CTX_SIZE)
		वापस शून्य;

	/**
	 * Driver uses पूर्णांकentionally the device_pool to allocated stream
	 * context array. Device Pool has 2048 bytes of size what gives us
	 * 128 entries.
	 */
	वापस dma_pool_zalloc(pdev->device_pool, GFP_DMA32 | GFP_ATOMIC,
			       &pep->stream_info.ctx_array_dma);
पूर्ण

काष्ठा cdnsp_ring *cdnsp_dma_to_transfer_ring(काष्ठा cdnsp_ep *pep, u64 address)
अणु
	अगर (pep->ep_state & EP_HAS_STREAMS)
		वापस radix_tree_lookup(&pep->stream_info.trb_address_map,
					 address >> TRB_SEGMENT_SHIFT);

	वापस pep->ring;
पूर्ण

/*
 * Change an endpoपूर्णांक's पूर्णांकernal काष्ठाure so it supports stream IDs.
 * The number of requested streams includes stream 0, which cannot be used by
 * driver.
 *
 * The number of stream contexts in the stream context array may be bigger than
 * the number of streams the driver wants to use. This is because the number of
 * stream context array entries must be a घातer of two.
 */
पूर्णांक cdnsp_alloc_stream_info(काष्ठा cdnsp_device *pdev,
			    काष्ठा cdnsp_ep *pep,
			    अचिन्हित पूर्णांक num_stream_ctxs,
			    अचिन्हित पूर्णांक num_streams)
अणु
	काष्ठा cdnsp_stream_info *stream_info;
	काष्ठा cdnsp_ring *cur_ring;
	u32 cur_stream;
	u64 addr;
	पूर्णांक ret;
	पूर्णांक mps;

	stream_info = &pep->stream_info;
	stream_info->num_streams = num_streams;
	stream_info->num_stream_ctxs = num_stream_ctxs;

	/* Initialize the array of भव poपूर्णांकers to stream rings. */
	stream_info->stream_rings = kसुस्मृति(num_streams,
					    माप(काष्ठा cdnsp_ring *),
					    GFP_ATOMIC);
	अगर (!stream_info->stream_rings)
		वापस -ENOMEM;

	/* Initialize the array of DMA addresses क्रम stream rings क्रम the HW. */
	stream_info->stream_ctx_array = cdnsp_alloc_stream_ctx(pdev, pep);
	अगर (!stream_info->stream_ctx_array)
		जाओ cleanup_stream_rings;

	स_रखो(stream_info->stream_ctx_array, 0,
	       माप(काष्ठा cdnsp_stream_ctx) * num_stream_ctxs);
	INIT_RADIX_TREE(&stream_info->trb_address_map, GFP_ATOMIC);
	mps = usb_endpoपूर्णांक_maxp(pep->endpoपूर्णांक.desc);

	/*
	 * Allocate rings क्रम all the streams that the driver will use,
	 * and add their segment DMA addresses to the radix tree.
	 * Stream 0 is reserved.
	 */
	क्रम (cur_stream = 1; cur_stream < num_streams; cur_stream++) अणु
		cur_ring = cdnsp_ring_alloc(pdev, 2, TYPE_STREAM, mps,
					    GFP_ATOMIC);
		stream_info->stream_rings[cur_stream] = cur_ring;

		अगर (!cur_ring)
			जाओ cleanup_rings;

		cur_ring->stream_id = cur_stream;
		cur_ring->trb_address_map = &stream_info->trb_address_map;

		/* Set deq ptr, cycle bit, and stream context type. */
		addr = cur_ring->first_seg->dma | SCT_FOR_CTX(SCT_PRI_TR) |
		       cur_ring->cycle_state;

		stream_info->stream_ctx_array[cur_stream].stream_ring =
			cpu_to_le64(addr);

		trace_cdnsp_set_stream_ring(cur_ring);

		ret = cdnsp_update_stream_mapping(cur_ring);
		अगर (ret)
			जाओ cleanup_rings;
	पूर्ण

	वापस 0;

cleanup_rings:
	क्रम (cur_stream = 1; cur_stream < num_streams; cur_stream++) अणु
		cur_ring = stream_info->stream_rings[cur_stream];
		अगर (cur_ring) अणु
			cdnsp_ring_मुक्त(pdev, cur_ring);
			stream_info->stream_rings[cur_stream] = शून्य;
		पूर्ण
	पूर्ण

cleanup_stream_rings:
	kमुक्त(pep->stream_info.stream_rings);

	वापस -ENOMEM;
पूर्ण

/* Frees all stream contexts associated with the endpoपूर्णांक. */
अटल व्योम cdnsp_मुक्त_stream_info(काष्ठा cdnsp_device *pdev,
				   काष्ठा cdnsp_ep *pep)
अणु
	काष्ठा cdnsp_stream_info *stream_info = &pep->stream_info;
	काष्ठा cdnsp_ring *cur_ring;
	पूर्णांक cur_stream;

	अगर (!(pep->ep_state & EP_HAS_STREAMS))
		वापस;

	क्रम (cur_stream = 1; cur_stream < stream_info->num_streams;
	     cur_stream++) अणु
		cur_ring = stream_info->stream_rings[cur_stream];
		अगर (cur_ring) अणु
			cdnsp_ring_मुक्त(pdev, cur_ring);
			stream_info->stream_rings[cur_stream] = शून्य;
		पूर्ण
	पूर्ण

	अगर (stream_info->stream_ctx_array)
		cdnsp_मुक्त_stream_ctx(pdev, pep);

	kमुक्त(stream_info->stream_rings);
	pep->ep_state &= ~EP_HAS_STREAMS;
पूर्ण

/* All the cdnsp_tds in the ring's TD list should be मुक्तd at this poपूर्णांक.*/
अटल व्योम cdnsp_मुक्त_priv_device(काष्ठा cdnsp_device *pdev)
अणु
	pdev->dcbaa->dev_context_ptrs[1] = 0;

	cdnsp_मुक्त_endpoपूर्णांक_rings(pdev, &pdev->eps[0]);

	अगर (pdev->in_ctx.bytes)
		dma_pool_मुक्त(pdev->device_pool, pdev->in_ctx.bytes,
			      pdev->in_ctx.dma);

	अगर (pdev->out_ctx.bytes)
		dma_pool_मुक्त(pdev->device_pool, pdev->out_ctx.bytes,
			      pdev->out_ctx.dma);

	pdev->in_ctx.bytes = शून्य;
	pdev->out_ctx.bytes = शून्य;
पूर्ण

अटल पूर्णांक cdnsp_alloc_priv_device(काष्ठा cdnsp_device *pdev)
अणु
	पूर्णांक ret;

	ret = cdnsp_init_device_ctx(pdev);
	अगर (ret)
		वापस ret;

	/* Allocate endpoपूर्णांक 0 ring. */
	pdev->eps[0].ring = cdnsp_ring_alloc(pdev, 2, TYPE_CTRL, 0, GFP_ATOMIC);
	अगर (!pdev->eps[0].ring)
		जाओ fail;

	/* Poपूर्णांक to output device context in dcbaa. */
	pdev->dcbaa->dev_context_ptrs[1] = cpu_to_le64(pdev->out_ctx.dma);
	pdev->cmd.in_ctx = &pdev->in_ctx;

	trace_cdnsp_alloc_priv_device(pdev);
	वापस 0;
fail:
	dma_pool_मुक्त(pdev->device_pool, pdev->out_ctx.bytes,
		      pdev->out_ctx.dma);
	dma_pool_मुक्त(pdev->device_pool, pdev->in_ctx.bytes,
		      pdev->in_ctx.dma);

	वापस ret;
पूर्ण

व्योम cdnsp_copy_ep0_dequeue_पूर्णांकo_input_ctx(काष्ठा cdnsp_device *pdev)
अणु
	काष्ठा cdnsp_ep_ctx *ep0_ctx = pdev->eps[0].in_ctx;
	काष्ठा cdnsp_ring *ep_ring = pdev->eps[0].ring;
	dma_addr_t dma;

	dma = cdnsp_trb_virt_to_dma(ep_ring->enq_seg, ep_ring->enqueue);
	ep0_ctx->deq = cpu_to_le64(dma | ep_ring->cycle_state);
पूर्ण

/* Setup an controller निजी device क्रम a Set Address command. */
पूर्णांक cdnsp_setup_addressable_priv_dev(काष्ठा cdnsp_device *pdev)
अणु
	काष्ठा cdnsp_slot_ctx *slot_ctx;
	काष्ठा cdnsp_ep_ctx *ep0_ctx;
	u32 max_packets, port;

	ep0_ctx = cdnsp_get_ep_ctx(&pdev->in_ctx, 0);
	slot_ctx = cdnsp_get_slot_ctx(&pdev->in_ctx);

	/* Only the control endpoपूर्णांक is valid - one endpoपूर्णांक context. */
	slot_ctx->dev_info |= cpu_to_le32(LAST_CTX(1));

	चयन (pdev->gadget.speed) अणु
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
	हाल USB_SPEED_FULL:
		slot_ctx->dev_info |= cpu_to_le32(SLOT_SPEED_FS);
		max_packets = MAX_PACKET(64);
		अवरोध;
	शेष:
		/* Speed was not set , this shouldn't happen. */
		वापस -EINVAL;
	पूर्ण

	port = DEV_PORT(pdev->active_port->port_num);
	slot_ctx->dev_port |= cpu_to_le32(port);
	slot_ctx->dev_state = cpu_to_le32((pdev->device_address &
					   DEV_ADDR_MASK));
	ep0_ctx->tx_info = cpu_to_le32(EP_AVG_TRB_LENGTH(0x8));
	ep0_ctx->ep_info2 = cpu_to_le32(EP_TYPE(CTRL_EP));
	ep0_ctx->ep_info2 |= cpu_to_le32(MAX_BURST(0) | ERROR_COUNT(3) |
					 max_packets);

	ep0_ctx->deq = cpu_to_le64(pdev->eps[0].ring->first_seg->dma |
				   pdev->eps[0].ring->cycle_state);

	trace_cdnsp_setup_addressable_priv_device(pdev);

	वापस 0;
पूर्ण

/*
 * Convert पूर्णांकerval expressed as 2^(bInterval - 1) == पूर्णांकerval पूर्णांकo
 * straight exponent value 2^n == पूर्णांकerval.
 */
अटल अचिन्हित पूर्णांक cdnsp_parse_exponent_पूर्णांकerval(काष्ठा usb_gadget *g,
						  काष्ठा cdnsp_ep *pep)
अणु
	अचिन्हित पूर्णांक पूर्णांकerval;

	पूर्णांकerval = clamp_val(pep->endpoपूर्णांक.desc->bInterval, 1, 16) - 1;
	अगर (पूर्णांकerval != pep->endpoपूर्णांक.desc->bInterval - 1)
		dev_warn(&g->dev, "ep %s - rounding interval to %d %sframes\n",
			 pep->name, 1 << पूर्णांकerval,
			 g->speed == USB_SPEED_FULL ? "" : "micro");

	/*
	 * Full speed isoc endpoपूर्णांकs specअगरy पूर्णांकerval in frames,
	 * not microframes. We are using microframes everywhere,
	 * so adjust accordingly.
	 */
	अगर (g->speed == USB_SPEED_FULL)
		पूर्णांकerval += 3;	/* 1 frame = 2^3 uframes */

	/* Controller handles only up to 512ms (2^12). */
	अगर (पूर्णांकerval > 12)
		पूर्णांकerval = 12;

	वापस पूर्णांकerval;
पूर्ण

/*
 * Convert bInterval expressed in microframes (in 1-255 range) to exponent of
 * microframes, rounded करोwn to nearest घातer of 2.
 */
अटल अचिन्हित पूर्णांक cdnsp_microframes_to_exponent(काष्ठा usb_gadget *g,
						  काष्ठा cdnsp_ep *pep,
						  अचिन्हित पूर्णांक desc_पूर्णांकerval,
						  अचिन्हित पूर्णांक min_exponent,
						  अचिन्हित पूर्णांक max_exponent)
अणु
	अचिन्हित पूर्णांक पूर्णांकerval;

	पूर्णांकerval = fls(desc_पूर्णांकerval) - 1;
	वापस clamp_val(पूर्णांकerval, min_exponent, max_exponent);
पूर्ण

/*
 * Return the polling पूर्णांकerval.
 *
 * The polling पूर्णांकerval is expressed in "microframes". If controllers's Interval
 * field is set to N, it will service the endpoपूर्णांक every 2^(Interval)*125us.
 */
अटल अचिन्हित पूर्णांक cdnsp_get_endpoपूर्णांक_पूर्णांकerval(काष्ठा usb_gadget *g,
						काष्ठा cdnsp_ep *pep)
अणु
	अचिन्हित पूर्णांक पूर्णांकerval = 0;

	चयन (g->speed) अणु
	हाल USB_SPEED_HIGH:
	हाल USB_SPEED_SUPER_PLUS:
	हाल USB_SPEED_SUPER:
		अगर (usb_endpoपूर्णांक_xfer_पूर्णांक(pep->endpoपूर्णांक.desc) ||
		    usb_endpoपूर्णांक_xfer_isoc(pep->endpoपूर्णांक.desc))
			पूर्णांकerval = cdnsp_parse_exponent_पूर्णांकerval(g, pep);
		अवरोध;
	हाल USB_SPEED_FULL:
		अगर (usb_endpoपूर्णांक_xfer_isoc(pep->endpoपूर्णांक.desc)) अणु
			पूर्णांकerval = cdnsp_parse_exponent_पूर्णांकerval(g, pep);
		पूर्ण अन्यथा अगर (usb_endpoपूर्णांक_xfer_पूर्णांक(pep->endpoपूर्णांक.desc)) अणु
			पूर्णांकerval = pep->endpoपूर्णांक.desc->bInterval << 3;
			पूर्णांकerval = cdnsp_microframes_to_exponent(g, pep,
								 पूर्णांकerval,
								 3, 10);
		पूर्ण

		अवरोध;
	शेष:
		WARN_ON(1);
	पूर्ण

	वापस पूर्णांकerval;
पूर्ण

/*
 * The "Mult" field in the endpoपूर्णांक context is only set क्रम SuperSpeed isoc eps.
 * High speed endpoपूर्णांक descriptors can define "the number of additional
 * transaction opportunities per microframe", but that goes in the Max Burst
 * endpoपूर्णांक context field.
 */
अटल u32 cdnsp_get_endpoपूर्णांक_mult(काष्ठा usb_gadget *g, काष्ठा cdnsp_ep *pep)
अणु
	अगर (g->speed < USB_SPEED_SUPER ||
	    !usb_endpoपूर्णांक_xfer_isoc(pep->endpoपूर्णांक.desc))
		वापस 0;

	वापस pep->endpoपूर्णांक.comp_desc->bmAttributes;
पूर्ण

अटल u32 cdnsp_get_endpoपूर्णांक_max_burst(काष्ठा usb_gadget *g,
					काष्ठा cdnsp_ep *pep)
अणु
	/* Super speed and Plus have max burst in ep companion desc */
	अगर (g->speed >= USB_SPEED_SUPER)
		वापस pep->endpoपूर्णांक.comp_desc->bMaxBurst;

	अगर (g->speed == USB_SPEED_HIGH &&
	    (usb_endpoपूर्णांक_xfer_isoc(pep->endpoपूर्णांक.desc) ||
	     usb_endpoपूर्णांक_xfer_पूर्णांक(pep->endpoपूर्णांक.desc)))
		वापस (usb_endpoपूर्णांक_maxp(pep->endpoपूर्णांक.desc) & 0x1800) >> 11;

	वापस 0;
पूर्ण

अटल u32 cdnsp_get_endpoपूर्णांक_type(स्थिर काष्ठा usb_endpoपूर्णांक_descriptor *desc)
अणु
	पूर्णांक in;

	in = usb_endpoपूर्णांक_dir_in(desc);

	चयन (usb_endpoपूर्णांक_type(desc)) अणु
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

/*
 * Return the maximum endpoपूर्णांक service पूर्णांकerval समय (ESIT) payload.
 * Basically, this is the maxpacket size, multiplied by the burst size
 * and mult size.
 */
अटल u32 cdnsp_get_max_esit_payload(काष्ठा usb_gadget *g,
				      काष्ठा cdnsp_ep *pep)
अणु
	पूर्णांक max_packet;
	पूर्णांक max_burst;

	/* Only applies क्रम पूर्णांकerrupt or isochronous endpoपूर्णांकs*/
	अगर (usb_endpoपूर्णांक_xfer_control(pep->endpoपूर्णांक.desc) ||
	    usb_endpoपूर्णांक_xfer_bulk(pep->endpoपूर्णांक.desc))
		वापस 0;

	/* SuperSpeedPlus Isoc ep sending over 48k per EIST. */
	अगर (g->speed >= USB_SPEED_SUPER_PLUS &&
	    USB_SS_SSP_ISOC_COMP(pep->endpoपूर्णांक.desc->bmAttributes))
		वापस le16_to_cpu(pep->endpoपूर्णांक.comp_desc->wBytesPerInterval);
	/* SuperSpeed or SuperSpeedPlus Isoc ep with less than 48k per esit */
	अन्यथा अगर (g->speed >= USB_SPEED_SUPER)
		वापस le16_to_cpu(pep->endpoपूर्णांक.comp_desc->wBytesPerInterval);

	max_packet = usb_endpoपूर्णांक_maxp(pep->endpoपूर्णांक.desc);
	max_burst = usb_endpoपूर्णांक_maxp_mult(pep->endpoपूर्णांक.desc);

	/* A 0 in max burst means 1 transfer per ESIT */
	वापस max_packet * max_burst;
पूर्ण

पूर्णांक cdnsp_endpoपूर्णांक_init(काष्ठा cdnsp_device *pdev,
			काष्ठा cdnsp_ep *pep,
			gfp_t mem_flags)
अणु
	क्रमागत cdnsp_ring_type ring_type;
	काष्ठा cdnsp_ep_ctx *ep_ctx;
	अचिन्हित पूर्णांक err_count = 0;
	अचिन्हित पूर्णांक avg_trb_len;
	अचिन्हित पूर्णांक max_packet;
	अचिन्हित पूर्णांक max_burst;
	अचिन्हित पूर्णांक पूर्णांकerval;
	u32 max_esit_payload;
	अचिन्हित पूर्णांक mult;
	u32 endpoपूर्णांक_type;
	पूर्णांक ret;

	ep_ctx = pep->in_ctx;

	endpoपूर्णांक_type = cdnsp_get_endpoपूर्णांक_type(pep->endpoपूर्णांक.desc);
	अगर (!endpoपूर्णांक_type)
		वापस -EINVAL;

	ring_type = usb_endpoपूर्णांक_type(pep->endpoपूर्णांक.desc);

	/*
	 * Get values to fill the endpoपूर्णांक context, mostly from ep descriptor.
	 * The average TRB buffer length क्रम bulk endpoपूर्णांकs is unclear as we
	 * have no clue on scatter gather list entry size. For Isoc and Int,
	 * set it to max available.
	 */
	max_esit_payload = cdnsp_get_max_esit_payload(&pdev->gadget, pep);
	पूर्णांकerval = cdnsp_get_endpoपूर्णांक_पूर्णांकerval(&pdev->gadget, pep);
	mult = cdnsp_get_endpoपूर्णांक_mult(&pdev->gadget, pep);
	max_packet = usb_endpoपूर्णांक_maxp(pep->endpoपूर्णांक.desc);
	max_burst = cdnsp_get_endpoपूर्णांक_max_burst(&pdev->gadget, pep);
	avg_trb_len = max_esit_payload;

	/* Allow 3 retries क्रम everything but isoc, set CErr = 3. */
	अगर (!usb_endpoपूर्णांक_xfer_isoc(pep->endpoपूर्णांक.desc))
		err_count = 3;
	अगर (usb_endpoपूर्णांक_xfer_bulk(pep->endpoपूर्णांक.desc) &&
	    pdev->gadget.speed == USB_SPEED_HIGH)
		max_packet = 512;
	/* Controller spec indicates that ctrl ep avg TRB Length should be 8. */
	अगर (usb_endpoपूर्णांक_xfer_control(pep->endpoपूर्णांक.desc))
		avg_trb_len = 8;

	/* Set up the endpoपूर्णांक ring. */
	pep->ring = cdnsp_ring_alloc(pdev, 2, ring_type, max_packet, mem_flags);
	pep->skip = false;

	/* Fill the endpoपूर्णांक context */
	ep_ctx->ep_info = cpu_to_le32(EP_MAX_ESIT_PAYLOAD_HI(max_esit_payload) |
				EP_INTERVAL(पूर्णांकerval) | EP_MULT(mult));
	ep_ctx->ep_info2 = cpu_to_le32(EP_TYPE(endpoपूर्णांक_type) |
				MAX_PACKET(max_packet) | MAX_BURST(max_burst) |
				ERROR_COUNT(err_count));
	ep_ctx->deq = cpu_to_le64(pep->ring->first_seg->dma |
				  pep->ring->cycle_state);

	ep_ctx->tx_info = cpu_to_le32(EP_MAX_ESIT_PAYLOAD_LO(max_esit_payload) |
				EP_AVG_TRB_LENGTH(avg_trb_len));

	अगर (usb_endpoपूर्णांक_xfer_bulk(pep->endpoपूर्णांक.desc) &&
	    pdev->gadget.speed > USB_SPEED_HIGH) अणु
		ret = cdnsp_alloc_streams(pdev, pep);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

व्योम cdnsp_endpoपूर्णांक_zero(काष्ठा cdnsp_device *pdev, काष्ठा cdnsp_ep *pep)
अणु
	pep->in_ctx->ep_info = 0;
	pep->in_ctx->ep_info2 = 0;
	pep->in_ctx->deq = 0;
	pep->in_ctx->tx_info = 0;
पूर्ण

अटल पूर्णांक cdnsp_alloc_erst(काष्ठा cdnsp_device *pdev,
			    काष्ठा cdnsp_ring *evt_ring,
			    काष्ठा cdnsp_erst *erst)
अणु
	काष्ठा cdnsp_erst_entry *entry;
	काष्ठा cdnsp_segment *seg;
	अचिन्हित पूर्णांक val;
	माप_प्रकार size;

	size = माप(काष्ठा cdnsp_erst_entry) * evt_ring->num_segs;
	erst->entries = dma_alloc_coherent(pdev->dev, size,
					   &erst->erst_dma_addr, GFP_KERNEL);
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

अटल व्योम cdnsp_मुक्त_erst(काष्ठा cdnsp_device *pdev, काष्ठा cdnsp_erst *erst)
अणु
	माप_प्रकार size = माप(काष्ठा cdnsp_erst_entry) * (erst->num_entries);
	काष्ठा device *dev = pdev->dev;

	अगर (erst->entries)
		dma_मुक्त_coherent(dev, size, erst->entries,
				  erst->erst_dma_addr);

	erst->entries = शून्य;
पूर्ण

व्योम cdnsp_mem_cleanup(काष्ठा cdnsp_device *pdev)
अणु
	काष्ठा device *dev = pdev->dev;

	cdnsp_मुक्त_priv_device(pdev);
	cdnsp_मुक्त_erst(pdev, &pdev->erst);

	अगर (pdev->event_ring)
		cdnsp_ring_मुक्त(pdev, pdev->event_ring);

	pdev->event_ring = शून्य;

	अगर (pdev->cmd_ring)
		cdnsp_ring_मुक्त(pdev, pdev->cmd_ring);

	pdev->cmd_ring = शून्य;

	dma_pool_destroy(pdev->segment_pool);
	pdev->segment_pool = शून्य;
	dma_pool_destroy(pdev->device_pool);
	pdev->device_pool = शून्य;

	अगर (pdev->dcbaa)
		dma_मुक्त_coherent(dev, माप(*pdev->dcbaa),
				  pdev->dcbaa, pdev->dcbaa->dma);

	pdev->dcbaa = शून्य;

	pdev->usb2_port.exist = 0;
	pdev->usb3_port.exist = 0;
	pdev->usb2_port.port_num = 0;
	pdev->usb3_port.port_num = 0;
	pdev->active_port = शून्य;
पूर्ण

अटल व्योम cdnsp_set_event_deq(काष्ठा cdnsp_device *pdev)
अणु
	dma_addr_t deq;
	u64 temp;

	deq = cdnsp_trb_virt_to_dma(pdev->event_ring->deq_seg,
				    pdev->event_ring->dequeue);

	/* Update controller event ring dequeue poपूर्णांकer */
	temp = cdnsp_पढ़ो_64(&pdev->ir_set->erst_dequeue);
	temp &= ERST_PTR_MASK;

	/*
	 * Don't clear the EHB bit (which is RW1C) because
	 * there might be more events to service.
	 */
	temp &= ~ERST_EHB;

	cdnsp_ग_लिखो_64(((u64)deq & (u64)~ERST_PTR_MASK) | temp,
		       &pdev->ir_set->erst_dequeue);
पूर्ण

अटल व्योम cdnsp_add_in_port(काष्ठा cdnsp_device *pdev,
			      काष्ठा cdnsp_port *port,
			      __le32 __iomem *addr)
अणु
	u32 temp, port_offset, port_count;

	temp = पढ़ोl(addr);
	port->maj_rev = CDNSP_EXT_PORT_MAJOR(temp);
	port->min_rev = CDNSP_EXT_PORT_MINOR(temp);

	/* Port offset and count in the third dword.*/
	temp = पढ़ोl(addr + 2);
	port_offset = CDNSP_EXT_PORT_OFF(temp);
	port_count = CDNSP_EXT_PORT_COUNT(temp);

	trace_cdnsp_port_info(addr, port_offset, port_count, port->maj_rev);

	port->port_num = port_offset;
	port->exist = 1;
पूर्ण

/*
 * Scan the Extended Capabilities क्रम the "Supported Protocol Capabilities" that
 * specअगरy what speeds each port is supposed to be.
 */
अटल पूर्णांक cdnsp_setup_port_arrays(काष्ठा cdnsp_device *pdev)
अणु
	व्योम __iomem *base;
	u32 offset;
	पूर्णांक i;

	base = &pdev->cap_regs->hc_capbase;
	offset = cdnsp_find_next_ext_cap(base, 0,
					 EXT_CAP_CFG_DEV_20PORT_CAP_ID);
	pdev->port20_regs = base + offset;

	offset = cdnsp_find_next_ext_cap(base, 0, D_XEC_CFG_3XPORT_CAP);
	pdev->port3x_regs =  base + offset;

	offset = 0;
	base = &pdev->cap_regs->hc_capbase;

	/* Driver expects max 2 extended protocol capability. */
	क्रम (i = 0; i < 2; i++) अणु
		u32 temp;

		offset = cdnsp_find_next_ext_cap(base, offset,
						 EXT_CAPS_PROTOCOL);
		temp = पढ़ोl(base + offset);

		अगर (CDNSP_EXT_PORT_MAJOR(temp) == 0x03 &&
		    !pdev->usb3_port.port_num)
			cdnsp_add_in_port(pdev, &pdev->usb3_port,
					  base + offset);

		अगर (CDNSP_EXT_PORT_MAJOR(temp) == 0x02 &&
		    !pdev->usb2_port.port_num)
			cdnsp_add_in_port(pdev, &pdev->usb2_port,
					  base + offset);
	पूर्ण

	अगर (!pdev->usb2_port.exist || !pdev->usb3_port.exist) अणु
		dev_err(pdev->dev, "Error: Only one port detected\n");
		वापस -ENODEV;
	पूर्ण

	trace_cdnsp_init("Found USB 2.0 ports and  USB 3.0 ports.");

	pdev->usb2_port.regs = (काष्ठा cdnsp_port_regs __iomem *)
			       (&pdev->op_regs->port_reg_base + NUM_PORT_REGS *
				(pdev->usb2_port.port_num - 1));

	pdev->usb3_port.regs = (काष्ठा cdnsp_port_regs __iomem *)
			       (&pdev->op_regs->port_reg_base + NUM_PORT_REGS *
				(pdev->usb3_port.port_num - 1));

	वापस 0;
पूर्ण

/*
 * Initialize memory क्रम CDNSP (one-समय init).
 *
 * Program the PAGESIZE रेजिस्टर, initialize the device context array, create
 * device contexts, set up a command ring segment, create event
 * ring (one क्रम now).
 */
पूर्णांक cdnsp_mem_init(काष्ठा cdnsp_device *pdev)
अणु
	काष्ठा device *dev = pdev->dev;
	पूर्णांक ret = -ENOMEM;
	अचिन्हित पूर्णांक val;
	dma_addr_t dma;
	u32 page_size;
	u64 val_64;

	/*
	 * Use 4K pages, since that's common and the minimum the
	 * controller supports
	 */
	page_size = 1 << 12;

	val = पढ़ोl(&pdev->op_regs->config_reg);
	val |= ((val & ~MAX_DEVS) | CDNSP_DEV_MAX_SLOTS) | CONFIG_U3E;
	ग_लिखोl(val, &pdev->op_regs->config_reg);

	/*
	 * Doorbell array must be physically contiguous
	 * and 64-byte (cache line) aligned.
	 */
	pdev->dcbaa = dma_alloc_coherent(dev, माप(*pdev->dcbaa),
					 &dma, GFP_KERNEL);
	अगर (!pdev->dcbaa)
		वापस -ENOMEM;

	pdev->dcbaa->dma = dma;

	cdnsp_ग_लिखो_64(dma, &pdev->op_regs->dcbaa_ptr);

	/*
	 * Initialize the ring segment pool.  The ring must be a contiguous
	 * काष्ठाure comprised of TRBs. The TRBs must be 16 byte aligned,
	 * however, the command ring segment needs 64-byte aligned segments
	 * and our use of dma addresses in the trb_address_map radix tree needs
	 * TRB_SEGMENT_SIZE alignment, so driver pick the greater alignment
	 * need.
	 */
	pdev->segment_pool = dma_pool_create("CDNSP ring segments", dev,
					     TRB_SEGMENT_SIZE, TRB_SEGMENT_SIZE,
					     page_size);
	अगर (!pdev->segment_pool)
		जाओ release_dcbaa;

	pdev->device_pool = dma_pool_create("CDNSP input/output contexts", dev,
					    CDNSP_CTX_SIZE, 64, page_size);
	अगर (!pdev->device_pool)
		जाओ destroy_segment_pool;


	/* Set up the command ring to have one segments क्रम now. */
	pdev->cmd_ring = cdnsp_ring_alloc(pdev, 1, TYPE_COMMAND, 0, GFP_KERNEL);
	अगर (!pdev->cmd_ring)
		जाओ destroy_device_pool;

	/* Set the address in the Command Ring Control रेजिस्टर */
	val_64 = cdnsp_पढ़ो_64(&pdev->op_regs->cmd_ring);
	val_64 = (val_64 & (u64)CMD_RING_RSVD_BITS) |
		 (pdev->cmd_ring->first_seg->dma & (u64)~CMD_RING_RSVD_BITS) |
		 pdev->cmd_ring->cycle_state;
	cdnsp_ग_लिखो_64(val_64, &pdev->op_regs->cmd_ring);

	val = पढ़ोl(&pdev->cap_regs->db_off);
	val &= DBOFF_MASK;
	pdev->dba = (व्योम __iomem *)pdev->cap_regs + val;

	/* Set ir_set to पूर्णांकerrupt रेजिस्टर set 0 */
	pdev->ir_set = &pdev->run_regs->ir_set[0];

	/*
	 * Event ring setup: Allocate a normal ring, but also setup
	 * the event ring segment table (ERST).
	 */
	pdev->event_ring = cdnsp_ring_alloc(pdev, ERST_NUM_SEGS, TYPE_EVENT,
					    0, GFP_KERNEL);
	अगर (!pdev->event_ring)
		जाओ मुक्त_cmd_ring;

	ret = cdnsp_alloc_erst(pdev, pdev->event_ring, &pdev->erst);
	अगर (ret)
		जाओ मुक्त_event_ring;

	/* Set ERST count with the number of entries in the segment table. */
	val = पढ़ोl(&pdev->ir_set->erst_size);
	val &= ERST_SIZE_MASK;
	val |= ERST_NUM_SEGS;
	ग_लिखोl(val, &pdev->ir_set->erst_size);

	/* Set the segment table base address. */
	val_64 = cdnsp_पढ़ो_64(&pdev->ir_set->erst_base);
	val_64 &= ERST_PTR_MASK;
	val_64 |= (pdev->erst.erst_dma_addr & (u64)~ERST_PTR_MASK);
	cdnsp_ग_लिखो_64(val_64, &pdev->ir_set->erst_base);

	/* Set the event ring dequeue address. */
	cdnsp_set_event_deq(pdev);

	ret = cdnsp_setup_port_arrays(pdev);
	अगर (ret)
		जाओ मुक्त_erst;

	ret = cdnsp_alloc_priv_device(pdev);
	अगर (ret) अणु
		dev_err(pdev->dev,
			"Could not allocate cdnsp_device data structures\n");
		जाओ मुक्त_erst;
	पूर्ण

	वापस 0;

मुक्त_erst:
	cdnsp_मुक्त_erst(pdev, &pdev->erst);
मुक्त_event_ring:
	cdnsp_ring_मुक्त(pdev, pdev->event_ring);
मुक्त_cmd_ring:
	cdnsp_ring_मुक्त(pdev, pdev->cmd_ring);
destroy_device_pool:
	dma_pool_destroy(pdev->device_pool);
destroy_segment_pool:
	dma_pool_destroy(pdev->segment_pool);
release_dcbaa:
	dma_मुक्त_coherent(dev, माप(*pdev->dcbaa), pdev->dcbaa,
			  pdev->dcbaa->dma);

	cdnsp_reset(pdev);

	वापस ret;
पूर्ण
