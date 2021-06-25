<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * xhci-dbgcap.c - xHCI debug capability support
 *
 * Copyright (C) 2017 Intel Corporation
 *
 * Author: Lu Baolu <baolu.lu@linux.पूर्णांकel.com>
 */
#समावेश <linux/dma-mapping.h>
#समावेश <linux/slab.h>
#समावेश <linux/nls.h>

#समावेश "xhci.h"
#समावेश "xhci-trace.h"
#समावेश "xhci-dbgcap.h"

अटल व्योम dbc_मुक्त_ctx(काष्ठा device *dev, काष्ठा xhci_container_ctx *ctx)
अणु
	अगर (!ctx)
		वापस;
	dma_मुक्त_coherent(dev, ctx->size, ctx->bytes, ctx->dma);
	kमुक्त(ctx);
पूर्ण

/* we use only one segment क्रम DbC rings */
अटल व्योम dbc_ring_मुक्त(काष्ठा device *dev, काष्ठा xhci_ring *ring)
अणु
	अगर (!ring)
		वापस;

	अगर (ring->first_seg && ring->first_seg->trbs) अणु
		dma_मुक्त_coherent(dev, TRB_SEGMENT_SIZE,
				  ring->first_seg->trbs,
				  ring->first_seg->dma);
		kमुक्त(ring->first_seg);
	पूर्ण
	kमुक्त(ring);
पूर्ण

अटल u32 xhci_dbc_populate_strings(काष्ठा dbc_str_descs *strings)
अणु
	काष्ठा usb_string_descriptor	*s_desc;
	u32				string_length;

	/* Serial string: */
	s_desc = (काष्ठा usb_string_descriptor *)strings->serial;
	utf8s_to_utf16s(DBC_STRING_SERIAL, म_माप(DBC_STRING_SERIAL),
			UTF16_LITTLE_ENDIAN, (ब_अक्षर_प्रकार *)s_desc->wData,
			DBC_MAX_STRING_LENGTH);

	s_desc->bLength		= (म_माप(DBC_STRING_SERIAL) + 1) * 2;
	s_desc->bDescriptorType	= USB_DT_STRING;
	string_length		= s_desc->bLength;
	string_length		<<= 8;

	/* Product string: */
	s_desc = (काष्ठा usb_string_descriptor *)strings->product;
	utf8s_to_utf16s(DBC_STRING_PRODUCT, म_माप(DBC_STRING_PRODUCT),
			UTF16_LITTLE_ENDIAN, (ब_अक्षर_प्रकार *)s_desc->wData,
			DBC_MAX_STRING_LENGTH);

	s_desc->bLength		= (म_माप(DBC_STRING_PRODUCT) + 1) * 2;
	s_desc->bDescriptorType	= USB_DT_STRING;
	string_length		+= s_desc->bLength;
	string_length		<<= 8;

	/* Manufacture string: */
	s_desc = (काष्ठा usb_string_descriptor *)strings->manufacturer;
	utf8s_to_utf16s(DBC_STRING_MANUFACTURER,
			म_माप(DBC_STRING_MANUFACTURER),
			UTF16_LITTLE_ENDIAN, (ब_अक्षर_प्रकार *)s_desc->wData,
			DBC_MAX_STRING_LENGTH);

	s_desc->bLength		= (म_माप(DBC_STRING_MANUFACTURER) + 1) * 2;
	s_desc->bDescriptorType	= USB_DT_STRING;
	string_length		+= s_desc->bLength;
	string_length		<<= 8;

	/* String0: */
	strings->string0[0]	= 4;
	strings->string0[1]	= USB_DT_STRING;
	strings->string0[2]	= 0x09;
	strings->string0[3]	= 0x04;
	string_length		+= 4;

	वापस string_length;
पूर्ण

अटल व्योम xhci_dbc_init_contexts(काष्ठा xhci_dbc *dbc, u32 string_length)
अणु
	काष्ठा dbc_info_context	*info;
	काष्ठा xhci_ep_ctx	*ep_ctx;
	u32			dev_info;
	dma_addr_t		deq, dma;
	अचिन्हित पूर्णांक		max_burst;

	अगर (!dbc)
		वापस;

	/* Populate info Context: */
	info			= (काष्ठा dbc_info_context *)dbc->ctx->bytes;
	dma			= dbc->string_dma;
	info->string0		= cpu_to_le64(dma);
	info->manufacturer	= cpu_to_le64(dma + DBC_MAX_STRING_LENGTH);
	info->product		= cpu_to_le64(dma + DBC_MAX_STRING_LENGTH * 2);
	info->serial		= cpu_to_le64(dma + DBC_MAX_STRING_LENGTH * 3);
	info->length		= cpu_to_le32(string_length);

	/* Populate bulk out endpoपूर्णांक context: */
	ep_ctx			= dbc_bulkout_ctx(dbc);
	max_burst		= DBC_CTRL_MAXBURST(पढ़ोl(&dbc->regs->control));
	deq			= dbc_bulkout_enq(dbc);
	ep_ctx->ep_info		= 0;
	ep_ctx->ep_info2	= dbc_epctx_info2(BULK_OUT_EP, 1024, max_burst);
	ep_ctx->deq		= cpu_to_le64(deq | dbc->ring_out->cycle_state);

	/* Populate bulk in endpoपूर्णांक context: */
	ep_ctx			= dbc_bulkin_ctx(dbc);
	deq			= dbc_bulkin_enq(dbc);
	ep_ctx->ep_info		= 0;
	ep_ctx->ep_info2	= dbc_epctx_info2(BULK_IN_EP, 1024, max_burst);
	ep_ctx->deq		= cpu_to_le64(deq | dbc->ring_in->cycle_state);

	/* Set DbC context and info रेजिस्टरs: */
	lo_hi_ग_लिखोq(dbc->ctx->dma, &dbc->regs->dccp);

	dev_info = cpu_to_le32((DBC_VENDOR_ID << 16) | DBC_PROTOCOL);
	ग_लिखोl(dev_info, &dbc->regs->devinfo1);

	dev_info = cpu_to_le32((DBC_DEVICE_REV << 16) | DBC_PRODUCT_ID);
	ग_लिखोl(dev_info, &dbc->regs->devinfo2);
पूर्ण

अटल व्योम xhci_dbc_giveback(काष्ठा dbc_request *req, पूर्णांक status)
	__releases(&dbc->lock)
	__acquires(&dbc->lock)
अणु
	काष्ठा xhci_dbc		*dbc = req->dbc;
	काष्ठा device		*dev = dbc->dev;

	list_del_init(&req->list_pending);
	req->trb_dma = 0;
	req->trb = शून्य;

	अगर (req->status == -EINPROGRESS)
		req->status = status;

	trace_xhci_dbc_giveback_request(req);

	dma_unmap_single(dev,
			 req->dma,
			 req->length,
			 dbc_ep_dma_direction(req));

	/* Give back the transfer request: */
	spin_unlock(&dbc->lock);
	req->complete(dbc, req);
	spin_lock(&dbc->lock);
पूर्ण

अटल व्योम xhci_dbc_flush_single_request(काष्ठा dbc_request *req)
अणु
	जोड़ xhci_trb	*trb = req->trb;

	trb->generic.field[0]	= 0;
	trb->generic.field[1]	= 0;
	trb->generic.field[2]	= 0;
	trb->generic.field[3]	&= cpu_to_le32(TRB_CYCLE);
	trb->generic.field[3]	|= cpu_to_le32(TRB_TYPE(TRB_TR_NOOP));

	xhci_dbc_giveback(req, -ESHUTDOWN);
पूर्ण

अटल व्योम xhci_dbc_flush_endpoपूर्णांक_requests(काष्ठा dbc_ep *dep)
अणु
	काष्ठा dbc_request	*req, *पंचांगp;

	list_क्रम_each_entry_safe(req, पंचांगp, &dep->list_pending, list_pending)
		xhci_dbc_flush_single_request(req);
पूर्ण

अटल व्योम xhci_dbc_flush_requests(काष्ठा xhci_dbc *dbc)
अणु
	xhci_dbc_flush_endpoपूर्णांक_requests(&dbc->eps[BULK_OUT]);
	xhci_dbc_flush_endpoपूर्णांक_requests(&dbc->eps[BULK_IN]);
पूर्ण

काष्ठा dbc_request *
dbc_alloc_request(काष्ठा xhci_dbc *dbc, अचिन्हित पूर्णांक direction, gfp_t flags)
अणु
	काष्ठा dbc_request	*req;

	अगर (direction != BULK_IN &&
	    direction != BULK_OUT)
		वापस शून्य;

	अगर (!dbc)
		वापस शून्य;

	req = kzalloc(माप(*req), flags);
	अगर (!req)
		वापस शून्य;

	req->dbc = dbc;
	INIT_LIST_HEAD(&req->list_pending);
	INIT_LIST_HEAD(&req->list_pool);
	req->direction = direction;

	trace_xhci_dbc_alloc_request(req);

	वापस req;
पूर्ण

व्योम
dbc_मुक्त_request(काष्ठा dbc_request *req)
अणु
	trace_xhci_dbc_मुक्त_request(req);

	kमुक्त(req);
पूर्ण

अटल व्योम
xhci_dbc_queue_trb(काष्ठा xhci_ring *ring, u32 field1,
		   u32 field2, u32 field3, u32 field4)
अणु
	जोड़ xhci_trb		*trb, *next;

	trb = ring->enqueue;
	trb->generic.field[0]	= cpu_to_le32(field1);
	trb->generic.field[1]	= cpu_to_le32(field2);
	trb->generic.field[2]	= cpu_to_le32(field3);
	trb->generic.field[3]	= cpu_to_le32(field4);

	trace_xhci_dbc_gadget_ep_queue(ring, &trb->generic);

	ring->num_trbs_मुक्त--;
	next = ++(ring->enqueue);
	अगर (TRB_TYPE_LINK_LE32(next->link.control)) अणु
		next->link.control ^= cpu_to_le32(TRB_CYCLE);
		ring->enqueue = ring->enq_seg->trbs;
		ring->cycle_state ^= 1;
	पूर्ण
पूर्ण

अटल पूर्णांक xhci_dbc_queue_bulk_tx(काष्ठा dbc_ep *dep,
				  काष्ठा dbc_request *req)
अणु
	u64			addr;
	जोड़ xhci_trb		*trb;
	अचिन्हित पूर्णांक		num_trbs;
	काष्ठा xhci_dbc		*dbc = req->dbc;
	काष्ठा xhci_ring	*ring = dep->ring;
	u32			length, control, cycle;

	num_trbs = count_trbs(req->dma, req->length);
	WARN_ON(num_trbs != 1);
	अगर (ring->num_trbs_मुक्त < num_trbs)
		वापस -EBUSY;

	addr	= req->dma;
	trb	= ring->enqueue;
	cycle	= ring->cycle_state;
	length	= TRB_LEN(req->length);
	control	= TRB_TYPE(TRB_NORMAL) | TRB_IOC;

	अगर (cycle)
		control &= cpu_to_le32(~TRB_CYCLE);
	अन्यथा
		control |= cpu_to_le32(TRB_CYCLE);

	req->trb = ring->enqueue;
	req->trb_dma = xhci_trb_virt_to_dma(ring->enq_seg, ring->enqueue);
	xhci_dbc_queue_trb(ring,
			   lower_32_bits(addr),
			   upper_32_bits(addr),
			   length, control);

	/*
	 * Add a barrier between ग_लिखोs of trb fields and flipping
	 * the cycle bit:
	 */
	wmb();

	अगर (cycle)
		trb->generic.field[3] |= cpu_to_le32(TRB_CYCLE);
	अन्यथा
		trb->generic.field[3] &= cpu_to_le32(~TRB_CYCLE);

	ग_लिखोl(DBC_DOOR_BELL_TARGET(dep->direction), &dbc->regs->करोorbell);

	वापस 0;
पूर्ण

अटल पूर्णांक
dbc_ep_करो_queue(काष्ठा dbc_request *req)
अणु
	पूर्णांक			ret;
	काष्ठा xhci_dbc		*dbc = req->dbc;
	काष्ठा device		*dev = dbc->dev;
	काष्ठा dbc_ep		*dep = &dbc->eps[req->direction];

	अगर (!req->length || !req->buf)
		वापस -EINVAL;

	req->actual		= 0;
	req->status		= -EINPROGRESS;

	req->dma = dma_map_single(dev,
				  req->buf,
				  req->length,
				  dbc_ep_dma_direction(dep));
	अगर (dma_mapping_error(dev, req->dma)) अणु
		dev_err(dbc->dev, "failed to map buffer\n");
		वापस -EFAULT;
	पूर्ण

	ret = xhci_dbc_queue_bulk_tx(dep, req);
	अगर (ret) अणु
		dev_err(dbc->dev, "failed to queue trbs\n");
		dma_unmap_single(dev,
				 req->dma,
				 req->length,
				 dbc_ep_dma_direction(dep));
		वापस -EFAULT;
	पूर्ण

	list_add_tail(&req->list_pending, &dep->list_pending);

	वापस 0;
पूर्ण

पूर्णांक dbc_ep_queue(काष्ठा dbc_request *req)
अणु
	अचिन्हित दीर्घ		flags;
	काष्ठा xhci_dbc		*dbc = req->dbc;
	पूर्णांक			ret = -ESHUTDOWN;

	अगर (!dbc)
		वापस -ENODEV;

	अगर (req->direction != BULK_IN &&
	    req->direction != BULK_OUT)
		वापस -EINVAL;

	spin_lock_irqsave(&dbc->lock, flags);
	अगर (dbc->state == DS_CONFIGURED)
		ret = dbc_ep_करो_queue(req);
	spin_unlock_irqrestore(&dbc->lock, flags);

	mod_delayed_work(प्रणाली_wq, &dbc->event_work, 0);

	trace_xhci_dbc_queue_request(req);

	वापस ret;
पूर्ण

अटल अंतरभूत व्योम xhci_dbc_करो_eps_init(काष्ठा xhci_dbc *dbc, bool direction)
अणु
	काष्ठा dbc_ep		*dep;

	dep			= &dbc->eps[direction];
	dep->dbc		= dbc;
	dep->direction		= direction;
	dep->ring		= direction ? dbc->ring_in : dbc->ring_out;

	INIT_LIST_HEAD(&dep->list_pending);
पूर्ण

अटल व्योम xhci_dbc_eps_init(काष्ठा xhci_dbc *dbc)
अणु
	xhci_dbc_करो_eps_init(dbc, BULK_OUT);
	xhci_dbc_करो_eps_init(dbc, BULK_IN);
पूर्ण

अटल व्योम xhci_dbc_eps_निकास(काष्ठा xhci_dbc *dbc)
अणु
	स_रखो(dbc->eps, 0, माप(काष्ठा dbc_ep) * ARRAY_SIZE(dbc->eps));
पूर्ण

अटल पूर्णांक dbc_erst_alloc(काष्ठा device *dev, काष्ठा xhci_ring *evt_ring,
		    काष्ठा xhci_erst *erst, gfp_t flags)
अणु
	erst->entries = dma_alloc_coherent(dev, माप(काष्ठा xhci_erst_entry),
					   &erst->erst_dma_addr, flags);
	अगर (!erst->entries)
		वापस -ENOMEM;

	erst->num_entries = 1;
	erst->entries[0].seg_addr = cpu_to_le64(evt_ring->first_seg->dma);
	erst->entries[0].seg_size = cpu_to_le32(TRBS_PER_SEGMENT);
	erst->entries[0].rsvd = 0;
	वापस 0;
पूर्ण

अटल व्योम dbc_erst_मुक्त(काष्ठा device *dev, काष्ठा xhci_erst *erst)
अणु
	अगर (erst->entries)
		dma_मुक्त_coherent(dev, माप(काष्ठा xhci_erst_entry),
				  erst->entries, erst->erst_dma_addr);
	erst->entries = शून्य;
पूर्ण

अटल काष्ठा xhci_container_ctx *
dbc_alloc_ctx(काष्ठा device *dev, gfp_t flags)
अणु
	काष्ठा xhci_container_ctx *ctx;

	ctx = kzalloc(माप(*ctx), flags);
	अगर (!ctx)
		वापस शून्य;

	/* xhci 7.6.9, all three contexts; info, ep-out and ep-in. Each 64 bytes*/
	ctx->size = 3 * DBC_CONTEXT_SIZE;
	ctx->bytes = dma_alloc_coherent(dev, ctx->size, &ctx->dma, flags);
	अगर (!ctx->bytes) अणु
		kमुक्त(ctx);
		वापस शून्य;
	पूर्ण
	वापस ctx;
पूर्ण

अटल काष्ठा xhci_ring *
xhci_dbc_ring_alloc(काष्ठा device *dev, क्रमागत xhci_ring_type type, gfp_t flags)
अणु
	काष्ठा xhci_ring *ring;
	काष्ठा xhci_segment *seg;
	dma_addr_t dma;

	ring = kzalloc(माप(*ring), flags);
	अगर (!ring)
		वापस शून्य;

	ring->num_segs = 1;
	ring->type = type;

	seg = kzalloc(माप(*seg), flags);
	अगर (!seg)
		जाओ seg_fail;

	ring->first_seg = seg;
	ring->last_seg = seg;
	seg->next = seg;

	seg->trbs = dma_alloc_coherent(dev, TRB_SEGMENT_SIZE, &dma, flags);
	अगर (!seg->trbs)
		जाओ dma_fail;

	seg->dma = dma;

	/* Only event ring करोes not use link TRB */
	अगर (type != TYPE_EVENT) अणु
		जोड़ xhci_trb *trb = &seg->trbs[TRBS_PER_SEGMENT - 1];

		trb->link.segment_ptr = cpu_to_le64(dma);
		trb->link.control = cpu_to_le32(LINK_TOGGLE | TRB_TYPE(TRB_LINK));
	पूर्ण
	INIT_LIST_HEAD(&ring->td_list);
	xhci_initialize_ring_info(ring, 1);
	वापस ring;
dma_fail:
	kमुक्त(seg);
seg_fail:
	kमुक्त(ring);
	वापस शून्य;
पूर्ण

अटल पूर्णांक xhci_dbc_mem_init(काष्ठा xhci_dbc *dbc, gfp_t flags)
अणु
	पूर्णांक			ret;
	dma_addr_t		deq;
	u32			string_length;
	काष्ठा device		*dev = dbc->dev;

	/* Allocate various rings क्रम events and transfers: */
	dbc->ring_evt = xhci_dbc_ring_alloc(dev, TYPE_EVENT, flags);
	अगर (!dbc->ring_evt)
		जाओ evt_fail;

	dbc->ring_in = xhci_dbc_ring_alloc(dev, TYPE_BULK, flags);
	अगर (!dbc->ring_in)
		जाओ in_fail;

	dbc->ring_out = xhci_dbc_ring_alloc(dev, TYPE_BULK, flags);
	अगर (!dbc->ring_out)
		जाओ out_fail;

	/* Allocate and populate ERST: */
	ret = dbc_erst_alloc(dev, dbc->ring_evt, &dbc->erst, flags);
	अगर (ret)
		जाओ erst_fail;

	/* Allocate context data काष्ठाure: */
	dbc->ctx = dbc_alloc_ctx(dev, flags); /* was sysdev, and is still */
	अगर (!dbc->ctx)
		जाओ ctx_fail;

	/* Allocate the string table: */
	dbc->string_size = माप(काष्ठा dbc_str_descs);
	dbc->string = dma_alloc_coherent(dev, dbc->string_size,
					 &dbc->string_dma, flags);
	अगर (!dbc->string)
		जाओ string_fail;

	/* Setup ERST रेजिस्टर: */
	ग_लिखोl(dbc->erst.erst_size, &dbc->regs->ersts);

	lo_hi_ग_लिखोq(dbc->erst.erst_dma_addr, &dbc->regs->erstba);
	deq = xhci_trb_virt_to_dma(dbc->ring_evt->deq_seg,
				   dbc->ring_evt->dequeue);
	lo_hi_ग_लिखोq(deq, &dbc->regs->erdp);

	/* Setup strings and contexts: */
	string_length = xhci_dbc_populate_strings(dbc->string);
	xhci_dbc_init_contexts(dbc, string_length);

	xhci_dbc_eps_init(dbc);
	dbc->state = DS_INITIALIZED;

	वापस 0;

string_fail:
	dbc_मुक्त_ctx(dev, dbc->ctx);
	dbc->ctx = शून्य;
ctx_fail:
	dbc_erst_मुक्त(dev, &dbc->erst);
erst_fail:
	dbc_ring_मुक्त(dev, dbc->ring_out);
	dbc->ring_out = शून्य;
out_fail:
	dbc_ring_मुक्त(dev, dbc->ring_in);
	dbc->ring_in = शून्य;
in_fail:
	dbc_ring_मुक्त(dev, dbc->ring_evt);
	dbc->ring_evt = शून्य;
evt_fail:
	वापस -ENOMEM;
पूर्ण

अटल व्योम xhci_dbc_mem_cleanup(काष्ठा xhci_dbc *dbc)
अणु
	अगर (!dbc)
		वापस;

	xhci_dbc_eps_निकास(dbc);

	अगर (dbc->string) अणु
		dma_मुक्त_coherent(dbc->dev, dbc->string_size,
				  dbc->string, dbc->string_dma);
		dbc->string = शून्य;
	पूर्ण

	dbc_मुक्त_ctx(dbc->dev, dbc->ctx);
	dbc->ctx = शून्य;

	dbc_erst_मुक्त(dbc->dev, &dbc->erst);
	dbc_ring_मुक्त(dbc->dev, dbc->ring_out);
	dbc_ring_मुक्त(dbc->dev, dbc->ring_in);
	dbc_ring_मुक्त(dbc->dev, dbc->ring_evt);
	dbc->ring_in = शून्य;
	dbc->ring_out = शून्य;
	dbc->ring_evt = शून्य;
पूर्ण

अटल पूर्णांक xhci_करो_dbc_start(काष्ठा xhci_dbc *dbc)
अणु
	पूर्णांक			ret;
	u32			ctrl;

	अगर (dbc->state != DS_DISABLED)
		वापस -EINVAL;

	ग_लिखोl(0, &dbc->regs->control);
	ret = xhci_handshake(&dbc->regs->control,
			     DBC_CTRL_DBC_ENABLE,
			     0, 1000);
	अगर (ret)
		वापस ret;

	ret = xhci_dbc_mem_init(dbc, GFP_ATOMIC);
	अगर (ret)
		वापस ret;

	ctrl = पढ़ोl(&dbc->regs->control);
	ग_लिखोl(ctrl | DBC_CTRL_DBC_ENABLE | DBC_CTRL_PORT_ENABLE,
	       &dbc->regs->control);
	ret = xhci_handshake(&dbc->regs->control,
			     DBC_CTRL_DBC_ENABLE,
			     DBC_CTRL_DBC_ENABLE, 1000);
	अगर (ret)
		वापस ret;

	dbc->state = DS_ENABLED;

	वापस 0;
पूर्ण

अटल पूर्णांक xhci_करो_dbc_stop(काष्ठा xhci_dbc *dbc)
अणु
	अगर (dbc->state == DS_DISABLED)
		वापस -1;

	ग_लिखोl(0, &dbc->regs->control);
	dbc->state = DS_DISABLED;

	वापस 0;
पूर्ण

अटल पूर्णांक xhci_dbc_start(काष्ठा xhci_dbc *dbc)
अणु
	पूर्णांक			ret;
	अचिन्हित दीर्घ		flags;

	WARN_ON(!dbc);

	pm_runसमय_get_sync(dbc->dev); /* note this was self.controller */

	spin_lock_irqsave(&dbc->lock, flags);
	ret = xhci_करो_dbc_start(dbc);
	spin_unlock_irqrestore(&dbc->lock, flags);

	अगर (ret) अणु
		pm_runसमय_put(dbc->dev); /* note this was self.controller */
		वापस ret;
	पूर्ण

	वापस mod_delayed_work(प्रणाली_wq, &dbc->event_work, 1);
पूर्ण

अटल व्योम xhci_dbc_stop(काष्ठा xhci_dbc *dbc)
अणु
	पूर्णांक ret;
	अचिन्हित दीर्घ		flags;

	WARN_ON(!dbc);

	चयन (dbc->state) अणु
	हाल DS_DISABLED:
		वापस;
	हाल DS_CONFIGURED:
	हाल DS_STALLED:
		अगर (dbc->driver->disconnect)
			dbc->driver->disconnect(dbc);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	cancel_delayed_work_sync(&dbc->event_work);

	spin_lock_irqsave(&dbc->lock, flags);
	ret = xhci_करो_dbc_stop(dbc);
	spin_unlock_irqrestore(&dbc->lock, flags);

	अगर (!ret) अणु
		xhci_dbc_mem_cleanup(dbc);
		pm_runसमय_put_sync(dbc->dev); /* note, was self.controller */
	पूर्ण
पूर्ण

अटल व्योम
dbc_handle_port_status(काष्ठा xhci_dbc *dbc, जोड़ xhci_trb *event)
अणु
	u32			portsc;

	portsc = पढ़ोl(&dbc->regs->portsc);
	अगर (portsc & DBC_PORTSC_CONN_CHANGE)
		dev_info(dbc->dev, "DbC port connect change\n");

	अगर (portsc & DBC_PORTSC_RESET_CHANGE)
		dev_info(dbc->dev, "DbC port reset change\n");

	अगर (portsc & DBC_PORTSC_LINK_CHANGE)
		dev_info(dbc->dev, "DbC port link status change\n");

	अगर (portsc & DBC_PORTSC_CONFIG_CHANGE)
		dev_info(dbc->dev, "DbC config error change\n");

	/* Port reset change bit will be cleared in other place: */
	ग_लिखोl(portsc & ~DBC_PORTSC_RESET_CHANGE, &dbc->regs->portsc);
पूर्ण

अटल व्योम dbc_handle_xfer_event(काष्ठा xhci_dbc *dbc, जोड़ xhci_trb *event)
अणु
	काष्ठा dbc_ep		*dep;
	काष्ठा xhci_ring	*ring;
	पूर्णांक			ep_id;
	पूर्णांक			status;
	u32			comp_code;
	माप_प्रकार			reमुख्य_length;
	काष्ठा dbc_request	*req = शून्य, *r;

	comp_code	= GET_COMP_CODE(le32_to_cpu(event->generic.field[2]));
	reमुख्य_length	= EVENT_TRB_LEN(le32_to_cpu(event->generic.field[2]));
	ep_id		= TRB_TO_EP_ID(le32_to_cpu(event->generic.field[3]));
	dep		= (ep_id == EPID_OUT) ?
				get_out_ep(dbc) : get_in_ep(dbc);
	ring		= dep->ring;

	चयन (comp_code) अणु
	हाल COMP_SUCCESS:
		reमुख्य_length = 0;
		fallthrough;
	हाल COMP_SHORT_PACKET:
		status = 0;
		अवरोध;
	हाल COMP_TRB_ERROR:
	हाल COMP_BABBLE_DETECTED_ERROR:
	हाल COMP_USB_TRANSACTION_ERROR:
	हाल COMP_STALL_ERROR:
		dev_warn(dbc->dev, "tx error %d detected\n", comp_code);
		status = -comp_code;
		अवरोध;
	शेष:
		dev_err(dbc->dev, "unknown tx error %d\n", comp_code);
		status = -comp_code;
		अवरोध;
	पूर्ण

	/* Match the pending request: */
	list_क्रम_each_entry(r, &dep->list_pending, list_pending) अणु
		अगर (r->trb_dma == event->trans_event.buffer) अणु
			req = r;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!req) अणु
		dev_warn(dbc->dev, "no matched request\n");
		वापस;
	पूर्ण

	trace_xhci_dbc_handle_transfer(ring, &req->trb->generic);

	ring->num_trbs_मुक्त++;
	req->actual = req->length - reमुख्य_length;
	xhci_dbc_giveback(req, status);
पूर्ण

अटल व्योम inc_evt_deq(काष्ठा xhci_ring *ring)
अणु
	/* If on the last TRB of the segment go back to the beginning */
	अगर (ring->dequeue == &ring->deq_seg->trbs[TRBS_PER_SEGMENT - 1]) अणु
		ring->cycle_state ^= 1;
		ring->dequeue = ring->deq_seg->trbs;
		वापस;
	पूर्ण
	ring->dequeue++;
पूर्ण

अटल क्रमागत evtवापस xhci_dbc_करो_handle_events(काष्ठा xhci_dbc *dbc)
अणु
	dma_addr_t		deq;
	काष्ठा dbc_ep		*dep;
	जोड़ xhci_trb		*evt;
	u32			ctrl, portsc;
	bool			update_erdp = false;

	/* DbC state machine: */
	चयन (dbc->state) अणु
	हाल DS_DISABLED:
	हाल DS_INITIALIZED:

		वापस EVT_ERR;
	हाल DS_ENABLED:
		portsc = पढ़ोl(&dbc->regs->portsc);
		अगर (portsc & DBC_PORTSC_CONN_STATUS) अणु
			dbc->state = DS_CONNECTED;
			dev_info(dbc->dev, "DbC connected\n");
		पूर्ण

		वापस EVT_DONE;
	हाल DS_CONNECTED:
		ctrl = पढ़ोl(&dbc->regs->control);
		अगर (ctrl & DBC_CTRL_DBC_RUN) अणु
			dbc->state = DS_CONFIGURED;
			dev_info(dbc->dev, "DbC configured\n");
			portsc = पढ़ोl(&dbc->regs->portsc);
			ग_लिखोl(portsc, &dbc->regs->portsc);
			वापस EVT_GSER;
		पूर्ण

		वापस EVT_DONE;
	हाल DS_CONFIGURED:
		/* Handle cable unplug event: */
		portsc = पढ़ोl(&dbc->regs->portsc);
		अगर (!(portsc & DBC_PORTSC_PORT_ENABLED) &&
		    !(portsc & DBC_PORTSC_CONN_STATUS)) अणु
			dev_info(dbc->dev, "DbC cable unplugged\n");
			dbc->state = DS_ENABLED;
			xhci_dbc_flush_requests(dbc);

			वापस EVT_DISC;
		पूर्ण

		/* Handle debug port reset event: */
		अगर (portsc & DBC_PORTSC_RESET_CHANGE) अणु
			dev_info(dbc->dev, "DbC port reset\n");
			ग_लिखोl(portsc, &dbc->regs->portsc);
			dbc->state = DS_ENABLED;
			xhci_dbc_flush_requests(dbc);

			वापस EVT_DISC;
		पूर्ण

		/* Handle endpoपूर्णांक stall event: */
		ctrl = पढ़ोl(&dbc->regs->control);
		अगर ((ctrl & DBC_CTRL_HALT_IN_TR) ||
		    (ctrl & DBC_CTRL_HALT_OUT_TR)) अणु
			dev_info(dbc->dev, "DbC Endpoint stall\n");
			dbc->state = DS_STALLED;

			अगर (ctrl & DBC_CTRL_HALT_IN_TR) अणु
				dep = get_in_ep(dbc);
				xhci_dbc_flush_endpoपूर्णांक_requests(dep);
			पूर्ण

			अगर (ctrl & DBC_CTRL_HALT_OUT_TR) अणु
				dep = get_out_ep(dbc);
				xhci_dbc_flush_endpoपूर्णांक_requests(dep);
			पूर्ण

			वापस EVT_DONE;
		पूर्ण

		/* Clear DbC run change bit: */
		अगर (ctrl & DBC_CTRL_DBC_RUN_CHANGE) अणु
			ग_लिखोl(ctrl, &dbc->regs->control);
			ctrl = पढ़ोl(&dbc->regs->control);
		पूर्ण

		अवरोध;
	हाल DS_STALLED:
		ctrl = पढ़ोl(&dbc->regs->control);
		अगर (!(ctrl & DBC_CTRL_HALT_IN_TR) &&
		    !(ctrl & DBC_CTRL_HALT_OUT_TR) &&
		    (ctrl & DBC_CTRL_DBC_RUN)) अणु
			dbc->state = DS_CONFIGURED;
			अवरोध;
		पूर्ण

		वापस EVT_DONE;
	शेष:
		dev_err(dbc->dev, "Unknown DbC state %d\n", dbc->state);
		अवरोध;
	पूर्ण

	/* Handle the events in the event ring: */
	evt = dbc->ring_evt->dequeue;
	जबतक ((le32_to_cpu(evt->event_cmd.flags) & TRB_CYCLE) ==
			dbc->ring_evt->cycle_state) अणु
		/*
		 * Add a barrier between पढ़ोing the cycle flag and any
		 * पढ़ोs of the event's flags/data below:
		 */
		rmb();

		trace_xhci_dbc_handle_event(dbc->ring_evt, &evt->generic);

		चयन (le32_to_cpu(evt->event_cmd.flags) & TRB_TYPE_BITMASK) अणु
		हाल TRB_TYPE(TRB_PORT_STATUS):
			dbc_handle_port_status(dbc, evt);
			अवरोध;
		हाल TRB_TYPE(TRB_TRANSFER):
			dbc_handle_xfer_event(dbc, evt);
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण

		inc_evt_deq(dbc->ring_evt);

		evt = dbc->ring_evt->dequeue;
		update_erdp = true;
	पूर्ण

	/* Update event ring dequeue poपूर्णांकer: */
	अगर (update_erdp) अणु
		deq = xhci_trb_virt_to_dma(dbc->ring_evt->deq_seg,
					   dbc->ring_evt->dequeue);
		lo_hi_ग_लिखोq(deq, &dbc->regs->erdp);
	पूर्ण

	वापस EVT_DONE;
पूर्ण

अटल व्योम xhci_dbc_handle_events(काष्ठा work_काष्ठा *work)
अणु
	क्रमागत evtवापस		evtr;
	काष्ठा xhci_dbc		*dbc;
	अचिन्हित दीर्घ		flags;

	dbc = container_of(to_delayed_work(work), काष्ठा xhci_dbc, event_work);

	spin_lock_irqsave(&dbc->lock, flags);
	evtr = xhci_dbc_करो_handle_events(dbc);
	spin_unlock_irqrestore(&dbc->lock, flags);

	चयन (evtr) अणु
	हाल EVT_GSER:
		अगर (dbc->driver->configure)
			dbc->driver->configure(dbc);
		अवरोध;
	हाल EVT_DISC:
		अगर (dbc->driver->disconnect)
			dbc->driver->disconnect(dbc);
		अवरोध;
	हाल EVT_DONE:
		अवरोध;
	शेष:
		dev_info(dbc->dev, "stop handling dbc events\n");
		वापस;
	पूर्ण

	mod_delayed_work(प्रणाली_wq, &dbc->event_work, 1);
पूर्ण

अटल व्योम xhci_करो_dbc_निकास(काष्ठा xhci_hcd *xhci)
अणु
	अचिन्हित दीर्घ		flags;

	spin_lock_irqsave(&xhci->lock, flags);
	kमुक्त(xhci->dbc);
	xhci->dbc = शून्य;
	spin_unlock_irqrestore(&xhci->lock, flags);
पूर्ण

अटल पूर्णांक xhci_करो_dbc_init(काष्ठा xhci_hcd *xhci)
अणु
	u32			reg;
	काष्ठा xhci_dbc		*dbc;
	अचिन्हित दीर्घ		flags;
	व्योम __iomem		*base;
	पूर्णांक			dbc_cap_offs;

	base = &xhci->cap_regs->hc_capbase;
	dbc_cap_offs = xhci_find_next_ext_cap(base, 0, XHCI_EXT_CAPS_DEBUG);
	अगर (!dbc_cap_offs)
		वापस -ENODEV;

	dbc = kzalloc(माप(*dbc), GFP_KERNEL);
	अगर (!dbc)
		वापस -ENOMEM;

	dbc->regs = base + dbc_cap_offs;

	/* We will aव्योम using DbC in xhci driver अगर it's in use. */
	reg = पढ़ोl(&dbc->regs->control);
	अगर (reg & DBC_CTRL_DBC_ENABLE) अणु
		kमुक्त(dbc);
		वापस -EBUSY;
	पूर्ण

	spin_lock_irqsave(&xhci->lock, flags);
	अगर (xhci->dbc) अणु
		spin_unlock_irqrestore(&xhci->lock, flags);
		kमुक्त(dbc);
		वापस -EBUSY;
	पूर्ण
	xhci->dbc = dbc;
	spin_unlock_irqrestore(&xhci->lock, flags);

	dbc->xhci = xhci;
	dbc->dev = xhci_to_hcd(xhci)->self.sysdev;
	INIT_DELAYED_WORK(&dbc->event_work, xhci_dbc_handle_events);
	spin_lock_init(&dbc->lock);

	वापस 0;
पूर्ण

अटल sमाप_प्रकार dbc_show(काष्ठा device *dev,
			काष्ठा device_attribute *attr,
			अक्षर *buf)
अणु
	स्थिर अक्षर		*p;
	काष्ठा xhci_dbc		*dbc;
	काष्ठा xhci_hcd		*xhci;

	xhci = hcd_to_xhci(dev_get_drvdata(dev));
	dbc = xhci->dbc;

	चयन (dbc->state) अणु
	हाल DS_DISABLED:
		p = "disabled";
		अवरोध;
	हाल DS_INITIALIZED:
		p = "initialized";
		अवरोध;
	हाल DS_ENABLED:
		p = "enabled";
		अवरोध;
	हाल DS_CONNECTED:
		p = "connected";
		अवरोध;
	हाल DS_CONFIGURED:
		p = "configured";
		अवरोध;
	हाल DS_STALLED:
		p = "stalled";
		अवरोध;
	शेष:
		p = "unknown";
	पूर्ण

	वापस प्र_लिखो(buf, "%s\n", p);
पूर्ण

अटल sमाप_प्रकार dbc_store(काष्ठा device *dev,
			 काष्ठा device_attribute *attr,
			 स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा xhci_hcd		*xhci;
	काष्ठा xhci_dbc		*dbc;

	xhci = hcd_to_xhci(dev_get_drvdata(dev));
	dbc = xhci->dbc;

	अगर (!म_भेदन(buf, "enable", 6))
		xhci_dbc_start(dbc);
	अन्यथा अगर (!म_भेदन(buf, "disable", 7))
		xhci_dbc_stop(dbc);
	अन्यथा
		वापस -EINVAL;

	वापस count;
पूर्ण

अटल DEVICE_ATTR_RW(dbc);

पूर्णांक xhci_dbc_init(काष्ठा xhci_hcd *xhci)
अणु
	पूर्णांक			ret;
	काष्ठा device		*dev = xhci_to_hcd(xhci)->self.controller;

	ret = xhci_करो_dbc_init(xhci);
	अगर (ret)
		जाओ init_err3;

	ret = xhci_dbc_tty_probe(xhci);
	अगर (ret)
		जाओ init_err2;

	ret = device_create_file(dev, &dev_attr_dbc);
	अगर (ret)
		जाओ init_err1;

	वापस 0;

init_err1:
	xhci_dbc_tty_हटाओ(xhci->dbc);
init_err2:
	xhci_करो_dbc_निकास(xhci);
init_err3:
	वापस ret;
पूर्ण

व्योम xhci_dbc_निकास(काष्ठा xhci_hcd *xhci)
अणु
	काष्ठा device		*dev = xhci_to_hcd(xhci)->self.controller;

	अगर (!xhci->dbc)
		वापस;

	device_हटाओ_file(dev, &dev_attr_dbc);
	xhci_dbc_tty_हटाओ(xhci->dbc);
	xhci_dbc_stop(xhci->dbc);
	xhci_करो_dbc_निकास(xhci);
पूर्ण

#अगर_घोषित CONFIG_PM
पूर्णांक xhci_dbc_suspend(काष्ठा xhci_hcd *xhci)
अणु
	काष्ठा xhci_dbc		*dbc = xhci->dbc;

	अगर (!dbc)
		वापस 0;

	अगर (dbc->state == DS_CONFIGURED)
		dbc->resume_required = 1;

	xhci_dbc_stop(dbc);

	वापस 0;
पूर्ण

पूर्णांक xhci_dbc_resume(काष्ठा xhci_hcd *xhci)
अणु
	पूर्णांक			ret = 0;
	काष्ठा xhci_dbc		*dbc = xhci->dbc;

	अगर (!dbc)
		वापस 0;

	अगर (dbc->resume_required) अणु
		dbc->resume_required = 0;
		xhci_dbc_start(dbc);
	पूर्ण

	वापस ret;
पूर्ण
#पूर्ण_अगर /* CONFIG_PM */
