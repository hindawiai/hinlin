<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Cadence USBSS DRD Driver - gadget side.
 *
 * Copyright (C) 2018-2019 Cadence Design Systems.
 * Copyright (C) 2017-2018 NXP
 *
 * Authors: Pawel Jez <pjez@cadence.com>,
 *          Pawel Laszczak <pawell@cadence.com>
 *          Peter Chen <peter.chen@nxp.com>
 */

/*
 * Work around 1:
 * At some situations, the controller may get stale data address in TRB
 * at below sequences:
 * 1. Controller पढ़ो TRB includes data address
 * 2. Software updates TRBs includes data address and Cycle bit
 * 3. Controller पढ़ो TRB which includes Cycle bit
 * 4. DMA run with stale data address
 *
 * To fix this problem, driver needs to make the first TRB in TD as invalid.
 * After preparing all TRBs driver needs to check the position of DMA and
 * अगर the DMA poपूर्णांक to the first just added TRB and करोorbell is 1,
 * then driver must defer making this TRB as valid. This TRB will be make
 * as valid during adding next TRB only अगर DMA is stopped or at TRBERR
 * पूर्णांकerrupt.
 *
 * Issue has been fixed in DEV_VER_V3 version of controller.
 *
 * Work around 2:
 * Controller क्रम OUT endpoपूर्णांकs has shared on-chip buffers क्रम all incoming
 * packets, including ep0out. It's FIFO buffer, so packets must be handle by DMA
 * in correct order. If the first packet in the buffer will not be handled,
 * then the following packets directed क्रम other endpoपूर्णांकs and  functions
 * will be blocked.
 * Additionally the packets directed to one endpoपूर्णांक can block entire on-chip
 * buffers. In this हाल transfer to other endpoपूर्णांकs also will blocked.
 *
 * To resolve this issue after raising the descriptor missing पूर्णांकerrupt
 * driver prepares पूर्णांकernal usb_request object and use it to arm DMA transfer.
 *
 * The problematic situation was observed in हाल when endpoपूर्णांक has been enabled
 * but no usb_request were queued. Driver try detects such endpoपूर्णांकs and will
 * use this workaround only क्रम these endpoपूर्णांक.
 *
 * Driver use limited number of buffer. This number can be set by macro
 * CDNS3_WA2_NUM_BUFFERS.
 *
 * Such blocking situation was observed on ACM gadget. For this function
 * host send OUT data packet but ACM function is not prepared क्रम this packet.
 * It's cause that buffer placed in on chip memory block transfer to other
 * endpoपूर्णांकs.
 *
 * Issue has been fixed in DEV_VER_V2 version of controller.
 *
 */

#समावेश <linux/dma-mapping.h>
#समावेश <linux/usb/gadget.h>
#समावेश <linux/module.h>
#समावेश <linux/dmapool.h>
#समावेश <linux/iopoll.h>

#समावेश "core.h"
#समावेश "gadget-export.h"
#समावेश "cdns3-gadget.h"
#समावेश "cdns3-trace.h"
#समावेश "drd.h"

अटल पूर्णांक __cdns3_gadget_ep_queue(काष्ठा usb_ep *ep,
				   काष्ठा usb_request *request,
				   gfp_t gfp_flags);

अटल पूर्णांक cdns3_ep_run_transfer(काष्ठा cdns3_endpoपूर्णांक *priv_ep,
				 काष्ठा usb_request *request);

अटल पूर्णांक cdns3_ep_run_stream_transfer(काष्ठा cdns3_endpoपूर्णांक *priv_ep,
					काष्ठा usb_request *request);

/**
 * cdns3_clear_रेजिस्टर_bit - clear bit in given रेजिस्टर.
 * @ptr: address of device controller रेजिस्टर to be पढ़ो and changed
 * @mask: bits requested to clar
 */
अटल व्योम cdns3_clear_रेजिस्टर_bit(व्योम __iomem *ptr, u32 mask)
अणु
	mask = पढ़ोl(ptr) & ~mask;
	ग_लिखोl(mask, ptr);
पूर्ण

/**
 * cdns3_set_रेजिस्टर_bit - set bit in given रेजिस्टर.
 * @ptr: address of device controller रेजिस्टर to be पढ़ो and changed
 * @mask: bits requested to set
 */
व्योम cdns3_set_रेजिस्टर_bit(व्योम __iomem *ptr, u32 mask)
अणु
	mask = पढ़ोl(ptr) | mask;
	ग_लिखोl(mask, ptr);
पूर्ण

/**
 * cdns3_ep_addr_to_index - Macro converts endpoपूर्णांक address to
 * index of endpoपूर्णांक object in cdns3_device.eps[] container
 * @ep_addr: endpoपूर्णांक address क्रम which endpoपूर्णांक object is required
 *
 */
u8 cdns3_ep_addr_to_index(u8 ep_addr)
अणु
	वापस (((ep_addr & 0x7F)) + ((ep_addr & USB_सूची_IN) ? 16 : 0));
पूर्ण

अटल पूर्णांक cdns3_get_dma_pos(काष्ठा cdns3_device *priv_dev,
			     काष्ठा cdns3_endpoपूर्णांक *priv_ep)
अणु
	पूर्णांक dma_index;

	dma_index = पढ़ोl(&priv_dev->regs->ep_traddr) - priv_ep->trb_pool_dma;

	वापस dma_index / TRB_SIZE;
पूर्ण

/**
 * cdns3_next_request - वापसs next request from list
 * @list: list containing requests
 *
 * Returns request or शून्य अगर no requests in list
 */
काष्ठा usb_request *cdns3_next_request(काष्ठा list_head *list)
अणु
	वापस list_first_entry_or_null(list, काष्ठा usb_request, list);
पूर्ण

/**
 * cdns3_next_align_buf - वापसs next buffer from list
 * @list: list containing buffers
 *
 * Returns buffer or शून्य अगर no buffers in list
 */
अटल काष्ठा cdns3_aligned_buf *cdns3_next_align_buf(काष्ठा list_head *list)
अणु
	वापस list_first_entry_or_null(list, काष्ठा cdns3_aligned_buf, list);
पूर्ण

/**
 * cdns3_next_priv_request - वापसs next request from list
 * @list: list containing requests
 *
 * Returns request or शून्य अगर no requests in list
 */
अटल काष्ठा cdns3_request *cdns3_next_priv_request(काष्ठा list_head *list)
अणु
	वापस list_first_entry_or_null(list, काष्ठा cdns3_request, list);
पूर्ण

/**
 * select_ep - selects endpoपूर्णांक
 * @priv_dev:  extended gadget object
 * @ep: endpoपूर्णांक address
 */
व्योम cdns3_select_ep(काष्ठा cdns3_device *priv_dev, u32 ep)
अणु
	अगर (priv_dev->selected_ep == ep)
		वापस;

	priv_dev->selected_ep = ep;
	ग_लिखोl(ep, &priv_dev->regs->ep_sel);
पूर्ण

/**
 * cdns3_get_tdl - माला_लो current tdl क्रम selected endpoपूर्णांक.
 * @priv_dev:  extended gadget object
 *
 * Beक्रमe calling this function the appropriate endpoपूर्णांक must
 * be selected by means of cdns3_select_ep function.
 */
अटल पूर्णांक cdns3_get_tdl(काष्ठा cdns3_device *priv_dev)
अणु
	अगर (priv_dev->dev_ver < DEV_VER_V3)
		वापस EP_CMD_TDL_GET(पढ़ोl(&priv_dev->regs->ep_cmd));
	अन्यथा
		वापस पढ़ोl(&priv_dev->regs->ep_tdl);
पूर्ण

dma_addr_t cdns3_trb_virt_to_dma(काष्ठा cdns3_endpoपूर्णांक *priv_ep,
				 काष्ठा cdns3_trb *trb)
अणु
	u32 offset = (अक्षर *)trb - (अक्षर *)priv_ep->trb_pool;

	वापस priv_ep->trb_pool_dma + offset;
पूर्ण

अटल व्योम cdns3_मुक्त_trb_pool(काष्ठा cdns3_endpoपूर्णांक *priv_ep)
अणु
	काष्ठा cdns3_device *priv_dev = priv_ep->cdns3_dev;

	अगर (priv_ep->trb_pool) अणु
		dma_pool_मुक्त(priv_dev->eps_dma_pool,
			      priv_ep->trb_pool, priv_ep->trb_pool_dma);
		priv_ep->trb_pool = शून्य;
	पूर्ण
पूर्ण

/**
 * cdns3_allocate_trb_pool - Allocates TRB's pool क्रम selected endpoपूर्णांक
 * @priv_ep:  endpoपूर्णांक object
 *
 * Function will वापस 0 on success or -ENOMEM on allocation error
 */
पूर्णांक cdns3_allocate_trb_pool(काष्ठा cdns3_endpoपूर्णांक *priv_ep)
अणु
	काष्ठा cdns3_device *priv_dev = priv_ep->cdns3_dev;
	पूर्णांक ring_size = TRB_RING_SIZE;
	पूर्णांक num_trbs = ring_size / TRB_SIZE;
	काष्ठा cdns3_trb *link_trb;

	अगर (priv_ep->trb_pool && priv_ep->alloc_ring_size < ring_size)
		cdns3_मुक्त_trb_pool(priv_ep);

	अगर (!priv_ep->trb_pool) अणु
		priv_ep->trb_pool = dma_pool_alloc(priv_dev->eps_dma_pool,
						   GFP_DMA32 | GFP_ATOMIC,
						   &priv_ep->trb_pool_dma);

		अगर (!priv_ep->trb_pool)
			वापस -ENOMEM;

		priv_ep->alloc_ring_size = ring_size;
	पूर्ण

	स_रखो(priv_ep->trb_pool, 0, ring_size);

	priv_ep->num_trbs = num_trbs;

	अगर (!priv_ep->num)
		वापस 0;

	/* Initialize the last TRB as Link TRB */
	link_trb = (priv_ep->trb_pool + (priv_ep->num_trbs - 1));

	अगर (priv_ep->use_streams) अणु
		/*
		 * For stream capable endpoपूर्णांकs driver use single correct TRB.
		 * The last trb has zeroed cycle bit
		 */
		link_trb->control = 0;
	पूर्ण अन्यथा अणु
		link_trb->buffer = cpu_to_le32(TRB_BUFFER(priv_ep->trb_pool_dma));
		link_trb->control = cpu_to_le32(TRB_CYCLE | TRB_TYPE(TRB_LINK) | TRB_TOGGLE);
	पूर्ण
	वापस 0;
पूर्ण

/**
 * cdns3_ep_stall_flush - Stalls and flushes selected endpoपूर्णांक
 * @priv_ep: endpoपूर्णांक object
 *
 * Endpoपूर्णांक must be selected beक्रमe call to this function
 */
अटल व्योम cdns3_ep_stall_flush(काष्ठा cdns3_endpoपूर्णांक *priv_ep)
अणु
	काष्ठा cdns3_device *priv_dev = priv_ep->cdns3_dev;
	पूर्णांक val;

	trace_cdns3_halt(priv_ep, 1, 1);

	ग_लिखोl(EP_CMD_DFLUSH | EP_CMD_ERDY | EP_CMD_SSTALL,
	       &priv_dev->regs->ep_cmd);

	/* रुको क्रम DFLUSH cleared */
	पढ़ोl_poll_समयout_atomic(&priv_dev->regs->ep_cmd, val,
				  !(val & EP_CMD_DFLUSH), 1, 1000);
	priv_ep->flags |= EP_STALLED;
	priv_ep->flags &= ~EP_STALL_PENDING;
पूर्ण

/**
 * cdns3_hw_reset_eps_config - reset endpoपूर्णांकs configuration kept by controller.
 * @priv_dev: extended gadget object
 */
व्योम cdns3_hw_reset_eps_config(काष्ठा cdns3_device *priv_dev)
अणु
	पूर्णांक i;

	ग_लिखोl(USB_CONF_CFGRST, &priv_dev->regs->usb_conf);

	cdns3_allow_enable_l1(priv_dev, 0);
	priv_dev->hw_configured_flag = 0;
	priv_dev->onchip_used_size = 0;
	priv_dev->out_mem_is_allocated = 0;
	priv_dev->रुको_क्रम_setup = 0;
	priv_dev->using_streams = 0;

	क्रम (i = 0; i < CDNS3_ENDPOINTS_MAX_COUNT; i++)
		अगर (priv_dev->eps[i])
			priv_dev->eps[i]->flags &= ~EP_CONFIGURED;
पूर्ण

/**
 * cdns3_ep_inc_trb - increment a trb index.
 * @index: Poपूर्णांकer to the TRB index to increment.
 * @cs: Cycle state
 * @trb_in_seg: number of TRBs in segment
 *
 * The index should never poपूर्णांक to the link TRB. After incrementing,
 * अगर it is poपूर्णांक to the link TRB, wrap around to the beginning and revert
 * cycle state bit The
 * link TRB is always at the last TRB entry.
 */
अटल व्योम cdns3_ep_inc_trb(पूर्णांक *index, u8 *cs, पूर्णांक trb_in_seg)
अणु
	(*index)++;
	अगर (*index == (trb_in_seg - 1)) अणु
		*index = 0;
		*cs ^=  1;
	पूर्ण
पूर्ण

/**
 * cdns3_ep_inc_enq - increment endpoपूर्णांक's enqueue poपूर्णांकer
 * @priv_ep: The endpoपूर्णांक whose enqueue poपूर्णांकer we're incrementing
 */
अटल व्योम cdns3_ep_inc_enq(काष्ठा cdns3_endpoपूर्णांक *priv_ep)
अणु
	priv_ep->मुक्त_trbs--;
	cdns3_ep_inc_trb(&priv_ep->enqueue, &priv_ep->pcs, priv_ep->num_trbs);
पूर्ण

/**
 * cdns3_ep_inc_deq - increment endpoपूर्णांक's dequeue poपूर्णांकer
 * @priv_ep: The endpoपूर्णांक whose dequeue poपूर्णांकer we're incrementing
 */
अटल व्योम cdns3_ep_inc_deq(काष्ठा cdns3_endpoपूर्णांक *priv_ep)
अणु
	priv_ep->मुक्त_trbs++;
	cdns3_ep_inc_trb(&priv_ep->dequeue, &priv_ep->ccs, priv_ep->num_trbs);
पूर्ण

अटल व्योम cdns3_move_deq_to_next_trb(काष्ठा cdns3_request *priv_req)
अणु
	काष्ठा cdns3_endpoपूर्णांक *priv_ep = priv_req->priv_ep;
	पूर्णांक current_trb = priv_req->start_trb;

	जबतक (current_trb != priv_req->end_trb) अणु
		cdns3_ep_inc_deq(priv_ep);
		current_trb = priv_ep->dequeue;
	पूर्ण

	cdns3_ep_inc_deq(priv_ep);
पूर्ण

/**
 * cdns3_allow_enable_l1 - enable/disable permits to transition to L1.
 * @priv_dev: Extended gadget object
 * @enable: Enable/disable permit to transition to L1.
 *
 * If bit USB_CONF_L1EN is set and device receive Extended Token packet,
 * then controller answer with ACK handshake.
 * If bit USB_CONF_L1DS is set and device receive Extended Token packet,
 * then controller answer with NYET handshake.
 */
व्योम cdns3_allow_enable_l1(काष्ठा cdns3_device *priv_dev, पूर्णांक enable)
अणु
	अगर (enable)
		ग_लिखोl(USB_CONF_L1EN, &priv_dev->regs->usb_conf);
	अन्यथा
		ग_लिखोl(USB_CONF_L1DS, &priv_dev->regs->usb_conf);
पूर्ण

क्रमागत usb_device_speed cdns3_get_speed(काष्ठा cdns3_device *priv_dev)
अणु
	u32 reg;

	reg = पढ़ोl(&priv_dev->regs->usb_sts);

	अगर (DEV_SUPERSPEED(reg))
		वापस USB_SPEED_SUPER;
	अन्यथा अगर (DEV_HIGHSPEED(reg))
		वापस USB_SPEED_HIGH;
	अन्यथा अगर (DEV_FULLSPEED(reg))
		वापस USB_SPEED_FULL;
	अन्यथा अगर (DEV_LOWSPEED(reg))
		वापस USB_SPEED_LOW;
	वापस USB_SPEED_UNKNOWN;
पूर्ण

/**
 * cdns3_start_all_request - add to ring all request not started
 * @priv_dev: Extended gadget object
 * @priv_ep: The endpoपूर्णांक क्रम whom request will be started.
 *
 * Returns वापस ENOMEM अगर transfer ring i not enough TRBs to start
 *         all requests.
 */
अटल पूर्णांक cdns3_start_all_request(काष्ठा cdns3_device *priv_dev,
				   काष्ठा cdns3_endpoपूर्णांक *priv_ep)
अणु
	काष्ठा usb_request *request;
	पूर्णांक ret = 0;
	u8 pending_empty = list_empty(&priv_ep->pending_req_list);

	/*
	 * If the last pending transfer is INTERNAL
	 * OR streams are enabled क्रम this endpoपूर्णांक
	 * करो NOT start new transfer till the last one is pending
	 */
	अगर (!pending_empty) अणु
		काष्ठा cdns3_request *priv_req;

		request = cdns3_next_request(&priv_ep->pending_req_list);
		priv_req = to_cdns3_request(request);
		अगर ((priv_req->flags & REQUEST_INTERNAL) ||
		    (priv_ep->flags & EP_TDLCHK_EN) ||
			priv_ep->use_streams) अणु
			dev_dbg(priv_dev->dev, "Blocking external request\n");
			वापस ret;
		पूर्ण
	पूर्ण

	जबतक (!list_empty(&priv_ep->deferred_req_list)) अणु
		request = cdns3_next_request(&priv_ep->deferred_req_list);

		अगर (!priv_ep->use_streams) अणु
			ret = cdns3_ep_run_transfer(priv_ep, request);
		पूर्ण अन्यथा अणु
			priv_ep->stream_sg_idx = 0;
			ret = cdns3_ep_run_stream_transfer(priv_ep, request);
		पूर्ण
		अगर (ret)
			वापस ret;

		list_del(&request->list);
		list_add_tail(&request->list,
			      &priv_ep->pending_req_list);
		अगर (request->stream_id != 0 || (priv_ep->flags & EP_TDLCHK_EN))
			अवरोध;
	पूर्ण

	priv_ep->flags &= ~EP_RING_FULL;
	वापस ret;
पूर्ण

/*
 * WA2: Set flag क्रम all not ISOC OUT endpoपूर्णांकs. If this flag is set
 * driver try to detect whether endpoपूर्णांक need additional पूर्णांकernal
 * buffer क्रम unblocking on-chip FIFO buffer. This flag will be cleared
 * अगर beक्रमe first DESCMISS पूर्णांकerrupt the DMA will be armed.
 */
#घोषणा cdns3_wa2_enable_detection(priv_dev, priv_ep, reg) करो अणु \
	अगर (!priv_ep->dir && priv_ep->type != USB_ENDPOINT_XFER_ISOC) अणु \
		priv_ep->flags |= EP_QUIRK_EXTRA_BUF_DET; \
		(reg) |= EP_STS_EN_DESCMISEN; \
	पूर्ण पूर्ण जबतक (0)

अटल व्योम __cdns3_descmiss_copy_data(काष्ठा usb_request *request,
	काष्ठा usb_request *descmiss_req)
अणु
	पूर्णांक length = request->actual + descmiss_req->actual;
	काष्ठा scatterlist *s = request->sg;

	अगर (!s) अणु
		अगर (length <= request->length) अणु
			स_नकल(&((u8 *)request->buf)[request->actual],
			       descmiss_req->buf,
			       descmiss_req->actual);
			request->actual = length;
		पूर्ण अन्यथा अणु
			/* It should never occures */
			request->status = -ENOMEM;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (length <= sg_dma_len(s)) अणु
			व्योम *p = phys_to_virt(sg_dma_address(s));

			स_नकल(&((u8 *)p)[request->actual],
				descmiss_req->buf,
				descmiss_req->actual);
			request->actual = length;
		पूर्ण अन्यथा अणु
			request->status = -ENOMEM;
		पूर्ण
	पूर्ण
पूर्ण

/**
 * cdns3_wa2_descmiss_copy_data copy data from पूर्णांकernal requests to
 * request queued by class driver.
 * @priv_ep: extended endpoपूर्णांक object
 * @request: request object
 */
अटल व्योम cdns3_wa2_descmiss_copy_data(काष्ठा cdns3_endpoपूर्णांक *priv_ep,
					 काष्ठा usb_request *request)
अणु
	काष्ठा usb_request *descmiss_req;
	काष्ठा cdns3_request *descmiss_priv_req;

	जबतक (!list_empty(&priv_ep->wa2_descmiss_req_list)) अणु
		पूर्णांक chunk_end;

		descmiss_priv_req =
			cdns3_next_priv_request(&priv_ep->wa2_descmiss_req_list);
		descmiss_req = &descmiss_priv_req->request;

		/* driver can't touch pending request */
		अगर (descmiss_priv_req->flags & REQUEST_PENDING)
			अवरोध;

		chunk_end = descmiss_priv_req->flags & REQUEST_INTERNAL_CH;
		request->status = descmiss_req->status;
		__cdns3_descmiss_copy_data(request, descmiss_req);
		list_del_init(&descmiss_priv_req->list);
		kमुक्त(descmiss_req->buf);
		cdns3_gadget_ep_मुक्त_request(&priv_ep->endpoपूर्णांक, descmiss_req);
		--priv_ep->wa2_counter;

		अगर (!chunk_end)
			अवरोध;
	पूर्ण
पूर्ण

अटल काष्ठा usb_request *cdns3_wa2_gadget_giveback(काष्ठा cdns3_device *priv_dev,
						     काष्ठा cdns3_endpoपूर्णांक *priv_ep,
						     काष्ठा cdns3_request *priv_req)
अणु
	अगर (priv_ep->flags & EP_QUIRK_EXTRA_BUF_EN &&
	    priv_req->flags & REQUEST_INTERNAL) अणु
		काष्ठा usb_request *req;

		req = cdns3_next_request(&priv_ep->deferred_req_list);

		priv_ep->descmis_req = शून्य;

		अगर (!req)
			वापस शून्य;

		/* unmap the gadget request beक्रमe copying data */
		usb_gadget_unmap_request_by_dev(priv_dev->sysdev, req,
						priv_ep->dir);

		cdns3_wa2_descmiss_copy_data(priv_ep, req);
		अगर (!(priv_ep->flags & EP_QUIRK_END_TRANSFER) &&
		    req->length != req->actual) अणु
			/* रुको क्रम next part of transfer */
			/* re-map the gadget request buffer*/
			usb_gadget_map_request_by_dev(priv_dev->sysdev, req,
				usb_endpoपूर्णांक_dir_in(priv_ep->endpoपूर्णांक.desc));
			वापस शून्य;
		पूर्ण

		अगर (req->status == -EINPROGRESS)
			req->status = 0;

		list_del_init(&req->list);
		cdns3_start_all_request(priv_dev, priv_ep);
		वापस req;
	पूर्ण

	वापस &priv_req->request;
पूर्ण

अटल पूर्णांक cdns3_wa2_gadget_ep_queue(काष्ठा cdns3_device *priv_dev,
				     काष्ठा cdns3_endpoपूर्णांक *priv_ep,
				     काष्ठा cdns3_request *priv_req)
अणु
	पूर्णांक deferred = 0;

	/*
	 * If transfer was queued beक्रमe DESCMISS appear than we
	 * can disable handling of DESCMISS पूर्णांकerrupt. Driver assumes that it
	 * can disable special treaपंचांगent क्रम this endpoपूर्णांक.
	 */
	अगर (priv_ep->flags & EP_QUIRK_EXTRA_BUF_DET) अणु
		u32 reg;

		cdns3_select_ep(priv_dev, priv_ep->num | priv_ep->dir);
		priv_ep->flags &= ~EP_QUIRK_EXTRA_BUF_DET;
		reg = पढ़ोl(&priv_dev->regs->ep_sts_en);
		reg &= ~EP_STS_EN_DESCMISEN;
		trace_cdns3_wa2(priv_ep, "workaround disabled\n");
		ग_लिखोl(reg, &priv_dev->regs->ep_sts_en);
	पूर्ण

	अगर (priv_ep->flags & EP_QUIRK_EXTRA_BUF_EN) अणु
		u8 pending_empty = list_empty(&priv_ep->pending_req_list);
		u8 descmiss_empty = list_empty(&priv_ep->wa2_descmiss_req_list);

		/*
		 *  DESCMISS transfer has been finished, so data will be
		 *  directly copied from पूर्णांकernal allocated usb_request
		 *  objects.
		 */
		अगर (pending_empty && !descmiss_empty &&
		    !(priv_req->flags & REQUEST_INTERNAL)) अणु
			cdns3_wa2_descmiss_copy_data(priv_ep,
						     &priv_req->request);

			trace_cdns3_wa2(priv_ep, "get internal stored data");

			list_add_tail(&priv_req->request.list,
				      &priv_ep->pending_req_list);
			cdns3_gadget_giveback(priv_ep, priv_req,
					      priv_req->request.status);

			/*
			 * Intentionally driver वापसs positive value as
			 * correct value. It inक्रमms that transfer has
			 * been finished.
			 */
			वापस EINPROGRESS;
		पूर्ण

		/*
		 * Driver will रुको क्रम completion DESCMISS transfer,
		 * beक्रमe starts new, not DESCMISS transfer.
		 */
		अगर (!pending_empty && !descmiss_empty) अणु
			trace_cdns3_wa2(priv_ep, "wait for pending transfer\n");
			deferred = 1;
		पूर्ण

		अगर (priv_req->flags & REQUEST_INTERNAL)
			list_add_tail(&priv_req->list,
				      &priv_ep->wa2_descmiss_req_list);
	पूर्ण

	वापस deferred;
पूर्ण

अटल व्योम cdns3_wa2_हटाओ_old_request(काष्ठा cdns3_endpoपूर्णांक *priv_ep)
अणु
	काष्ठा cdns3_request *priv_req;

	जबतक (!list_empty(&priv_ep->wa2_descmiss_req_list)) अणु
		u8 chain;

		priv_req = cdns3_next_priv_request(&priv_ep->wa2_descmiss_req_list);
		chain = !!(priv_req->flags & REQUEST_INTERNAL_CH);

		trace_cdns3_wa2(priv_ep, "removes eldest request");

		kमुक्त(priv_req->request.buf);
		cdns3_gadget_ep_मुक्त_request(&priv_ep->endpoपूर्णांक,
					     &priv_req->request);
		list_del_init(&priv_req->list);
		--priv_ep->wa2_counter;

		अगर (!chain)
			अवरोध;
	पूर्ण
पूर्ण

/**
 * cdns3_wa2_descmissing_packet - handles descriptor missing event.
 * @priv_ep: extended gadget object
 *
 * This function is used only क्रम WA2. For more inक्रमmation see Work around 2
 * description.
 */
अटल व्योम cdns3_wa2_descmissing_packet(काष्ठा cdns3_endpoपूर्णांक *priv_ep)
अणु
	काष्ठा cdns3_request *priv_req;
	काष्ठा usb_request *request;
	u8 pending_empty = list_empty(&priv_ep->pending_req_list);

	/* check क्रम pending transfer */
	अगर (!pending_empty) अणु
		trace_cdns3_wa2(priv_ep, "Ignoring Descriptor missing IRQ\n");
		वापस;
	पूर्ण

	अगर (priv_ep->flags & EP_QUIRK_EXTRA_BUF_DET) अणु
		priv_ep->flags &= ~EP_QUIRK_EXTRA_BUF_DET;
		priv_ep->flags |= EP_QUIRK_EXTRA_BUF_EN;
	पूर्ण

	trace_cdns3_wa2(priv_ep, "Description Missing detected\n");

	अगर (priv_ep->wa2_counter >= CDNS3_WA2_NUM_BUFFERS) अणु
		trace_cdns3_wa2(priv_ep, "WA2 overflow\n");
		cdns3_wa2_हटाओ_old_request(priv_ep);
	पूर्ण

	request = cdns3_gadget_ep_alloc_request(&priv_ep->endpoपूर्णांक,
						GFP_ATOMIC);
	अगर (!request)
		जाओ err;

	priv_req = to_cdns3_request(request);
	priv_req->flags |= REQUEST_INTERNAL;

	/* अगर this field is still asचिन्हित it indicate that transfer related
	 * with this request has not been finished yet. Driver in this
	 * हाल simply allocate next request and assign flag REQUEST_INTERNAL_CH
	 * flag to previous one. It will indicate that current request is
	 * part of the previous one.
	 */
	अगर (priv_ep->descmis_req)
		priv_ep->descmis_req->flags |= REQUEST_INTERNAL_CH;

	priv_req->request.buf = kzalloc(CDNS3_DESCMIS_BUF_SIZE,
					GFP_ATOMIC);
	priv_ep->wa2_counter++;

	अगर (!priv_req->request.buf) अणु
		cdns3_gadget_ep_मुक्त_request(&priv_ep->endpoपूर्णांक, request);
		जाओ err;
	पूर्ण

	priv_req->request.length = CDNS3_DESCMIS_BUF_SIZE;
	priv_ep->descmis_req = priv_req;

	__cdns3_gadget_ep_queue(&priv_ep->endpoपूर्णांक,
				&priv_ep->descmis_req->request,
				GFP_ATOMIC);

	वापस;

err:
	dev_err(priv_ep->cdns3_dev->dev,
		"Failed: No sufficient memory for DESCMIS\n");
पूर्ण

अटल व्योम cdns3_wa2_reset_tdl(काष्ठा cdns3_device *priv_dev)
अणु
	u16 tdl = EP_CMD_TDL_GET(पढ़ोl(&priv_dev->regs->ep_cmd));

	अगर (tdl) अणु
		u16 reset_val = EP_CMD_TDL_MAX + 1 - tdl;

		ग_लिखोl(EP_CMD_TDL_SET(reset_val) | EP_CMD_STDL,
		       &priv_dev->regs->ep_cmd);
	पूर्ण
पूर्ण

अटल व्योम cdns3_wa2_check_outq_status(काष्ठा cdns3_device *priv_dev)
अणु
	u32 ep_sts_reg;

	/* select EP0-out */
	cdns3_select_ep(priv_dev, 0);

	ep_sts_reg = पढ़ोl(&priv_dev->regs->ep_sts);

	अगर (EP_STS_OUTQ_VAL(ep_sts_reg)) अणु
		u32 outq_ep_num = EP_STS_OUTQ_NO(ep_sts_reg);
		काष्ठा cdns3_endpoपूर्णांक *outq_ep = priv_dev->eps[outq_ep_num];

		अगर ((outq_ep->flags & EP_ENABLED) && !(outq_ep->use_streams) &&
		    outq_ep->type != USB_ENDPOINT_XFER_ISOC && outq_ep_num) अणु
			u8 pending_empty = list_empty(&outq_ep->pending_req_list);

			अगर ((outq_ep->flags & EP_QUIRK_EXTRA_BUF_DET) ||
			    (outq_ep->flags & EP_QUIRK_EXTRA_BUF_EN) ||
			    !pending_empty) अणु
			पूर्ण अन्यथा अणु
				u32 ep_sts_en_reg;
				u32 ep_cmd_reg;

				cdns3_select_ep(priv_dev, outq_ep->num |
						outq_ep->dir);
				ep_sts_en_reg = पढ़ोl(&priv_dev->regs->ep_sts_en);
				ep_cmd_reg = पढ़ोl(&priv_dev->regs->ep_cmd);

				outq_ep->flags |= EP_TDLCHK_EN;
				cdns3_set_रेजिस्टर_bit(&priv_dev->regs->ep_cfg,
						       EP_CFG_TDL_CHK);

				cdns3_wa2_enable_detection(priv_dev, outq_ep,
							   ep_sts_en_reg);
				ग_लिखोl(ep_sts_en_reg,
				       &priv_dev->regs->ep_sts_en);
				/* reset tdl value to zero */
				cdns3_wa2_reset_tdl(priv_dev);
				/*
				 * Memory barrier - Reset tdl beक्रमe ringing the
				 * करोorbell.
				 */
				wmb();
				अगर (EP_CMD_DRDY & ep_cmd_reg) अणु
					trace_cdns3_wa2(outq_ep, "Enabling WA2 skipping doorbell\n");

				पूर्ण अन्यथा अणु
					trace_cdns3_wa2(outq_ep, "Enabling WA2 ringing doorbell\n");
					/*
					 * ring करोorbell to generate DESCMIS irq
					 */
					ग_लिखोl(EP_CMD_DRDY,
					       &priv_dev->regs->ep_cmd);
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

/**
 * cdns3_gadget_giveback - call काष्ठा usb_request's ->complete callback
 * @priv_ep: The endpoपूर्णांक to whom the request beदीर्घs to
 * @priv_req: The request we're giving back
 * @status: completion code क्रम the request
 *
 * Must be called with controller's lock held and पूर्णांकerrupts disabled. This
 * function will unmap @req and call its ->complete() callback to notअगरy upper
 * layers that it has completed.
 */
व्योम cdns3_gadget_giveback(काष्ठा cdns3_endpoपूर्णांक *priv_ep,
			   काष्ठा cdns3_request *priv_req,
			   पूर्णांक status)
अणु
	काष्ठा cdns3_device *priv_dev = priv_ep->cdns3_dev;
	काष्ठा usb_request *request = &priv_req->request;

	list_del_init(&request->list);

	अगर (request->status == -EINPROGRESS)
		request->status = status;

	usb_gadget_unmap_request_by_dev(priv_dev->sysdev, request,
					priv_ep->dir);

	अगर ((priv_req->flags & REQUEST_UNALIGNED) &&
	    priv_ep->dir == USB_सूची_OUT && !request->status) अणु
		/* Make DMA buffer CPU accessible */
		dma_sync_single_क्रम_cpu(priv_dev->sysdev,
			priv_req->aligned_buf->dma,
			priv_req->aligned_buf->size,
			priv_req->aligned_buf->dir);
		स_नकल(request->buf, priv_req->aligned_buf->buf,
		       request->length);
	पूर्ण

	priv_req->flags &= ~(REQUEST_PENDING | REQUEST_UNALIGNED);
	/* All TRBs have finished, clear the counter */
	priv_req->finished_trb = 0;
	trace_cdns3_gadget_giveback(priv_req);

	अगर (priv_dev->dev_ver < DEV_VER_V2) अणु
		request = cdns3_wa2_gadget_giveback(priv_dev, priv_ep,
						    priv_req);
		अगर (!request)
			वापस;
	पूर्ण

	अगर (request->complete) अणु
		spin_unlock(&priv_dev->lock);
		usb_gadget_giveback_request(&priv_ep->endpoपूर्णांक,
					    request);
		spin_lock(&priv_dev->lock);
	पूर्ण

	अगर (request->buf == priv_dev->zlp_buf)
		cdns3_gadget_ep_मुक्त_request(&priv_ep->endpoपूर्णांक, request);
पूर्ण

अटल व्योम cdns3_wa1_restore_cycle_bit(काष्ठा cdns3_endpoपूर्णांक *priv_ep)
अणु
	/* Work around क्रम stale data address in TRB*/
	अगर (priv_ep->wa1_set) अणु
		trace_cdns3_wa1(priv_ep, "restore cycle bit");

		priv_ep->wa1_set = 0;
		priv_ep->wa1_trb_index = 0xFFFF;
		अगर (priv_ep->wa1_cycle_bit) अणु
			priv_ep->wa1_trb->control =
				priv_ep->wa1_trb->control | cpu_to_le32(0x1);
		पूर्ण अन्यथा अणु
			priv_ep->wa1_trb->control =
				priv_ep->wa1_trb->control & cpu_to_le32(~0x1);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम cdns3_मुक्त_aligned_request_buf(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा cdns3_device *priv_dev = container_of(work, काष्ठा cdns3_device,
					aligned_buf_wq);
	काष्ठा cdns3_aligned_buf *buf, *पंचांगp;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&priv_dev->lock, flags);

	list_क्रम_each_entry_safe(buf, पंचांगp, &priv_dev->aligned_buf_list, list) अणु
		अगर (!buf->in_use) अणु
			list_del(&buf->list);

			/*
			 * Re-enable पूर्णांकerrupts to मुक्त DMA capable memory.
			 * Driver can't मुक्त this memory with disabled
			 * पूर्णांकerrupts.
			 */
			spin_unlock_irqrestore(&priv_dev->lock, flags);
			dma_मुक्त_noncoherent(priv_dev->sysdev, buf->size,
					  buf->buf, buf->dma, buf->dir);
			kमुक्त(buf);
			spin_lock_irqsave(&priv_dev->lock, flags);
		पूर्ण
	पूर्ण

	spin_unlock_irqrestore(&priv_dev->lock, flags);
पूर्ण

अटल पूर्णांक cdns3_prepare_aligned_request_buf(काष्ठा cdns3_request *priv_req)
अणु
	काष्ठा cdns3_endpoपूर्णांक *priv_ep = priv_req->priv_ep;
	काष्ठा cdns3_device *priv_dev = priv_ep->cdns3_dev;
	काष्ठा cdns3_aligned_buf *buf;

	/* check अगर buffer is aligned to 8. */
	अगर (!((uपूर्णांकptr_t)priv_req->request.buf & 0x7))
		वापस 0;

	buf = priv_req->aligned_buf;

	अगर (!buf || priv_req->request.length > buf->size) अणु
		buf = kzalloc(माप(*buf), GFP_ATOMIC);
		अगर (!buf)
			वापस -ENOMEM;

		buf->size = priv_req->request.length;
		buf->dir = usb_endpoपूर्णांक_dir_in(priv_ep->endpoपूर्णांक.desc) ?
			DMA_TO_DEVICE : DMA_FROM_DEVICE;

		buf->buf = dma_alloc_noncoherent(priv_dev->sysdev,
					      buf->size,
					      &buf->dma,
					      buf->dir,
					      GFP_ATOMIC);
		अगर (!buf->buf) अणु
			kमुक्त(buf);
			वापस -ENOMEM;
		पूर्ण

		अगर (priv_req->aligned_buf) अणु
			trace_cdns3_मुक्त_aligned_request(priv_req);
			priv_req->aligned_buf->in_use = 0;
			queue_work(प्रणाली_मुक्तzable_wq,
				   &priv_dev->aligned_buf_wq);
		पूर्ण

		buf->in_use = 1;
		priv_req->aligned_buf = buf;

		list_add_tail(&buf->list,
			      &priv_dev->aligned_buf_list);
	पूर्ण

	अगर (priv_ep->dir == USB_सूची_IN) अणु
		/* Make DMA buffer CPU accessible */
		dma_sync_single_क्रम_cpu(priv_dev->sysdev,
			buf->dma, buf->size, buf->dir);
		स_नकल(buf->buf, priv_req->request.buf,
		       priv_req->request.length);
	पूर्ण

	/* Transfer DMA buffer ownership back to device */
	dma_sync_single_क्रम_device(priv_dev->sysdev,
			buf->dma, buf->size, buf->dir);

	priv_req->flags |= REQUEST_UNALIGNED;
	trace_cdns3_prepare_aligned_request(priv_req);

	वापस 0;
पूर्ण

अटल पूर्णांक cdns3_wa1_update_guard(काष्ठा cdns3_endpoपूर्णांक *priv_ep,
				  काष्ठा cdns3_trb *trb)
अणु
	काष्ठा cdns3_device *priv_dev = priv_ep->cdns3_dev;

	अगर (!priv_ep->wa1_set) अणु
		u32 करोorbell;

		करोorbell = !!(पढ़ोl(&priv_dev->regs->ep_cmd) & EP_CMD_DRDY);

		अगर (करोorbell) अणु
			priv_ep->wa1_cycle_bit = priv_ep->pcs ? TRB_CYCLE : 0;
			priv_ep->wa1_set = 1;
			priv_ep->wa1_trb = trb;
			priv_ep->wa1_trb_index = priv_ep->enqueue;
			trace_cdns3_wa1(priv_ep, "set guard");
			वापस 0;
		पूर्ण
	पूर्ण
	वापस 1;
पूर्ण

अटल व्योम cdns3_wa1_tray_restore_cycle_bit(काष्ठा cdns3_device *priv_dev,
					     काष्ठा cdns3_endpoपूर्णांक *priv_ep)
अणु
	पूर्णांक dma_index;
	u32 करोorbell;

	करोorbell = !!(पढ़ोl(&priv_dev->regs->ep_cmd) & EP_CMD_DRDY);
	dma_index = cdns3_get_dma_pos(priv_dev, priv_ep);

	अगर (!करोorbell || dma_index != priv_ep->wa1_trb_index)
		cdns3_wa1_restore_cycle_bit(priv_ep);
पूर्ण

अटल पूर्णांक cdns3_ep_run_stream_transfer(काष्ठा cdns3_endpoपूर्णांक *priv_ep,
					काष्ठा usb_request *request)
अणु
	काष्ठा cdns3_device *priv_dev = priv_ep->cdns3_dev;
	काष्ठा cdns3_request *priv_req;
	काष्ठा cdns3_trb *trb;
	dma_addr_t trb_dma;
	पूर्णांक address;
	u32 control;
	u32 length;
	u32 tdl;
	अचिन्हित पूर्णांक sg_idx = priv_ep->stream_sg_idx;

	priv_req = to_cdns3_request(request);
	address = priv_ep->endpoपूर्णांक.desc->bEndpoपूर्णांकAddress;

	priv_ep->flags |= EP_PENDING_REQUEST;

	/* must allocate buffer aligned to 8 */
	अगर (priv_req->flags & REQUEST_UNALIGNED)
		trb_dma = priv_req->aligned_buf->dma;
	अन्यथा
		trb_dma = request->dma;

	/*  For stream capable endpoपूर्णांकs driver use only single TD. */
	trb = priv_ep->trb_pool + priv_ep->enqueue;
	priv_req->start_trb = priv_ep->enqueue;
	priv_req->end_trb = priv_req->start_trb;
	priv_req->trb = trb;

	cdns3_select_ep(priv_ep->cdns3_dev, address);

	control = TRB_TYPE(TRB_NORMAL) | TRB_CYCLE |
		  TRB_STREAM_ID(priv_req->request.stream_id) | TRB_ISP;

	अगर (!request->num_sgs) अणु
		trb->buffer = cpu_to_le32(TRB_BUFFER(trb_dma));
		length = request->length;
	पूर्ण अन्यथा अणु
		trb->buffer = cpu_to_le32(TRB_BUFFER(request->sg[sg_idx].dma_address));
		length = request->sg[sg_idx].length;
	पूर्ण

	tdl = DIV_ROUND_UP(length, priv_ep->endpoपूर्णांक.maxpacket);

	trb->length = cpu_to_le32(TRB_BURST_LEN(16) | TRB_LEN(length));

	/*
	 * For DEV_VER_V2 controller version we have enabled
	 * USB_CONF2_EN_TDL_TRB in DMULT configuration.
	 * This enables TDL calculation based on TRB, hence setting TDL in TRB.
	 */
	अगर (priv_dev->dev_ver >= DEV_VER_V2) अणु
		अगर (priv_dev->gadget.speed == USB_SPEED_SUPER)
			trb->length |= cpu_to_le32(TRB_TDL_SS_SIZE(tdl));
	पूर्ण
	priv_req->flags |= REQUEST_PENDING;

	trb->control = cpu_to_le32(control);

	trace_cdns3_prepare_trb(priv_ep, priv_req->trb);

	/*
	 * Memory barrier - Cycle Bit must be set beक्रमe trb->length  and
	 * trb->buffer fields.
	 */
	wmb();

	/* always first element */
	ग_लिखोl(EP_TRADDR_TRADDR(priv_ep->trb_pool_dma),
	       &priv_dev->regs->ep_traddr);

	अगर (!(priv_ep->flags & EP_STALLED)) अणु
		trace_cdns3_ring(priv_ep);
		/*clearing TRBERR and EP_STS_DESCMIS beक्रमe seting DRDY*/
		ग_लिखोl(EP_STS_TRBERR | EP_STS_DESCMIS, &priv_dev->regs->ep_sts);

		priv_ep->prime_flag = false;

		/*
		 * Controller version DEV_VER_V2 tdl calculation
		 * is based on TRB
		 */

		अगर (priv_dev->dev_ver < DEV_VER_V2)
			ग_लिखोl(EP_CMD_TDL_SET(tdl) | EP_CMD_STDL,
			       &priv_dev->regs->ep_cmd);
		अन्यथा अगर (priv_dev->dev_ver > DEV_VER_V2)
			ग_लिखोl(tdl, &priv_dev->regs->ep_tdl);

		priv_ep->last_stream_id = priv_req->request.stream_id;
		ग_लिखोl(EP_CMD_DRDY, &priv_dev->regs->ep_cmd);
		ग_लिखोl(EP_CMD_ERDY_SID(priv_req->request.stream_id) |
		       EP_CMD_ERDY, &priv_dev->regs->ep_cmd);

		trace_cdns3_करोorbell_epx(priv_ep->name,
					 पढ़ोl(&priv_dev->regs->ep_traddr));
	पूर्ण

	/* WORKAROUND क्रम transition to L0 */
	__cdns3_gadget_wakeup(priv_dev);

	वापस 0;
पूर्ण

/**
 * cdns3_ep_run_transfer - start transfer on no-शेष endpoपूर्णांक hardware
 * @priv_ep: endpoपूर्णांक object
 * @request: request object
 *
 * Returns zero on success or negative value on failure
 */
अटल पूर्णांक cdns3_ep_run_transfer(काष्ठा cdns3_endpoपूर्णांक *priv_ep,
				 काष्ठा usb_request *request)
अणु
	काष्ठा cdns3_device *priv_dev = priv_ep->cdns3_dev;
	काष्ठा cdns3_request *priv_req;
	काष्ठा cdns3_trb *trb;
	काष्ठा cdns3_trb *link_trb = शून्य;
	dma_addr_t trb_dma;
	u32 togle_pcs = 1;
	पूर्णांक sg_iter = 0;
	पूर्णांक num_trb;
	पूर्णांक address;
	u32 control;
	पूर्णांक pcs;
	u16 total_tdl = 0;
	काष्ठा scatterlist *s = शून्य;
	bool sg_supported = !!(request->num_mapped_sgs);

	अगर (priv_ep->type == USB_ENDPOINT_XFER_ISOC)
		num_trb = priv_ep->पूर्णांकerval;
	अन्यथा
		num_trb = sg_supported ? request->num_mapped_sgs : 1;

	अगर (num_trb > priv_ep->मुक्त_trbs) अणु
		priv_ep->flags |= EP_RING_FULL;
		वापस -ENOBUFS;
	पूर्ण

	priv_req = to_cdns3_request(request);
	address = priv_ep->endpoपूर्णांक.desc->bEndpoपूर्णांकAddress;

	priv_ep->flags |= EP_PENDING_REQUEST;

	/* must allocate buffer aligned to 8 */
	अगर (priv_req->flags & REQUEST_UNALIGNED)
		trb_dma = priv_req->aligned_buf->dma;
	अन्यथा
		trb_dma = request->dma;

	trb = priv_ep->trb_pool + priv_ep->enqueue;
	priv_req->start_trb = priv_ep->enqueue;
	priv_req->trb = trb;

	cdns3_select_ep(priv_ep->cdns3_dev, address);

	/* prepare ring */
	अगर ((priv_ep->enqueue + num_trb)  >= (priv_ep->num_trbs - 1)) अणु
		पूर्णांक करोorbell, dma_index;
		u32 ch_bit = 0;

		करोorbell = !!(पढ़ोl(&priv_dev->regs->ep_cmd) & EP_CMD_DRDY);
		dma_index = cdns3_get_dma_pos(priv_dev, priv_ep);

		/* Driver can't update LINK TRB अगर it is current processed. */
		अगर (करोorbell && dma_index == priv_ep->num_trbs - 1) अणु
			priv_ep->flags |= EP_DEFERRED_DRDY;
			वापस -ENOBUFS;
		पूर्ण

		/*updating C bt in  Link TRB beक्रमe starting DMA*/
		link_trb = priv_ep->trb_pool + (priv_ep->num_trbs - 1);
		/*
		 * For TRs size equal 2 enabling TRB_CHAIN क्रम epXin causes
		 * that DMA stuck at the LINK TRB.
		 * On the other hand, removing TRB_CHAIN क्रम दीर्घer TRs क्रम
		 * epXout cause that DMA stuck after handling LINK TRB.
		 * To eliminate this strange behavioral driver set TRB_CHAIN
		 * bit only क्रम TR size > 2.
		 */
		अगर (priv_ep->type == USB_ENDPOINT_XFER_ISOC ||
		    TRBS_PER_SEGMENT > 2)
			ch_bit = TRB_CHAIN;

		link_trb->control = cpu_to_le32(((priv_ep->pcs) ? TRB_CYCLE : 0) |
				    TRB_TYPE(TRB_LINK) | TRB_TOGGLE | ch_bit);
	पूर्ण

	अगर (priv_dev->dev_ver <= DEV_VER_V2)
		togle_pcs = cdns3_wa1_update_guard(priv_ep, trb);

	अगर (sg_supported)
		s = request->sg;

	/* set incorrect Cycle Bit क्रम first trb*/
	control = priv_ep->pcs ? 0 : TRB_CYCLE;
	trb->length = 0;
	अगर (priv_dev->dev_ver >= DEV_VER_V2) अणु
		u16 td_size;

		td_size = DIV_ROUND_UP(request->length,
				       priv_ep->endpoपूर्णांक.maxpacket);
		अगर (priv_dev->gadget.speed == USB_SPEED_SUPER)
			trb->length = cpu_to_le32(TRB_TDL_SS_SIZE(td_size));
		अन्यथा
			control |= TRB_TDL_HS_SIZE(td_size);
	पूर्ण

	करो अणु
		u32 length;

		/* fill TRB */
		control |= TRB_TYPE(TRB_NORMAL);
		अगर (sg_supported) अणु
			trb->buffer = cpu_to_le32(TRB_BUFFER(sg_dma_address(s)));
			length = sg_dma_len(s);
		पूर्ण अन्यथा अणु
			trb->buffer = cpu_to_le32(TRB_BUFFER(trb_dma));
			length = request->length;
		पूर्ण

		अगर (priv_ep->flags & EP_TDLCHK_EN)
			total_tdl += DIV_ROUND_UP(length,
					       priv_ep->endpoपूर्णांक.maxpacket);

		trb->length |= cpu_to_le32(TRB_BURST_LEN(priv_ep->trb_burst_size) |
					TRB_LEN(length));
		pcs = priv_ep->pcs ? TRB_CYCLE : 0;

		/*
		 * first trb should be prepared as last to aव्योम processing
		 *  transfer to early
		 */
		अगर (sg_iter != 0)
			control |= pcs;

		अगर (priv_ep->type == USB_ENDPOINT_XFER_ISOC  && !priv_ep->dir) अणु
			control |= TRB_IOC | TRB_ISP;
		पूर्ण अन्यथा अणु
			/* क्रम last element in TD or in SG list */
			अगर (sg_iter == (num_trb - 1) && sg_iter != 0)
				control |= pcs | TRB_IOC | TRB_ISP;
		पूर्ण

		अगर (sg_iter)
			trb->control = cpu_to_le32(control);
		अन्यथा
			priv_req->trb->control = cpu_to_le32(control);

		अगर (sg_supported) अणु
			trb->control |= cpu_to_le32(TRB_ISP);
			/* Don't set chain bit क्रम last TRB */
			अगर (sg_iter < num_trb - 1)
				trb->control |= cpu_to_le32(TRB_CHAIN);

			s = sg_next(s);
		पूर्ण

		control = 0;
		++sg_iter;
		priv_req->end_trb = priv_ep->enqueue;
		cdns3_ep_inc_enq(priv_ep);
		trb = priv_ep->trb_pool + priv_ep->enqueue;
		trb->length = 0;
	पूर्ण जबतक (sg_iter < num_trb);

	trb = priv_req->trb;

	priv_req->flags |= REQUEST_PENDING;
	priv_req->num_of_trb = num_trb;

	अगर (sg_iter == 1)
		trb->control |= cpu_to_le32(TRB_IOC | TRB_ISP);

	अगर (priv_dev->dev_ver < DEV_VER_V2 &&
	    (priv_ep->flags & EP_TDLCHK_EN)) अणु
		u16 tdl = total_tdl;
		u16 old_tdl = EP_CMD_TDL_GET(पढ़ोl(&priv_dev->regs->ep_cmd));

		अगर (tdl > EP_CMD_TDL_MAX) अणु
			tdl = EP_CMD_TDL_MAX;
			priv_ep->pending_tdl = total_tdl - EP_CMD_TDL_MAX;
		पूर्ण

		अगर (old_tdl < tdl) अणु
			tdl -= old_tdl;
			ग_लिखोl(EP_CMD_TDL_SET(tdl) | EP_CMD_STDL,
			       &priv_dev->regs->ep_cmd);
		पूर्ण
	पूर्ण

	/*
	 * Memory barrier - cycle bit must be set beक्रमe other filds in trb.
	 */
	wmb();

	/* give the TD to the consumer*/
	अगर (togle_pcs)
		trb->control = trb->control ^ cpu_to_le32(1);

	अगर (priv_dev->dev_ver <= DEV_VER_V2)
		cdns3_wa1_tray_restore_cycle_bit(priv_dev, priv_ep);

	अगर (num_trb > 1) अणु
		पूर्णांक i = 0;

		जबतक (i < num_trb) अणु
			trace_cdns3_prepare_trb(priv_ep, trb + i);
			अगर (trb + i == link_trb) अणु
				trb = priv_ep->trb_pool;
				num_trb = num_trb - i;
				i = 0;
			पूर्ण अन्यथा अणु
				i++;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		trace_cdns3_prepare_trb(priv_ep, priv_req->trb);
	पूर्ण

	/*
	 * Memory barrier - Cycle Bit must be set beक्रमe trb->length  and
	 * trb->buffer fields.
	 */
	wmb();

	/*
	 * For DMULT mode we can set address to transfer ring only once after
	 * enabling endpoपूर्णांक.
	 */
	अगर (priv_ep->flags & EP_UPDATE_EP_TRBADDR) अणु
		/*
		 * Until SW is not पढ़ोy to handle the OUT transfer the ISO OUT
		 * Endpoपूर्णांक should be disabled (EP_CFG.ENABLE = 0).
		 * EP_CFG_ENABLE must be set beक्रमe updating ep_traddr.
		 */
		अगर (priv_ep->type == USB_ENDPOINT_XFER_ISOC  && !priv_ep->dir &&
		    !(priv_ep->flags & EP_QUIRK_ISO_OUT_EN)) अणु
			priv_ep->flags |= EP_QUIRK_ISO_OUT_EN;
			cdns3_set_रेजिस्टर_bit(&priv_dev->regs->ep_cfg,
					       EP_CFG_ENABLE);
		पूर्ण

		ग_लिखोl(EP_TRADDR_TRADDR(priv_ep->trb_pool_dma +
					priv_req->start_trb * TRB_SIZE),
					&priv_dev->regs->ep_traddr);

		priv_ep->flags &= ~EP_UPDATE_EP_TRBADDR;
	पूर्ण

	अगर (!priv_ep->wa1_set && !(priv_ep->flags & EP_STALLED)) अणु
		trace_cdns3_ring(priv_ep);
		/*clearing TRBERR and EP_STS_DESCMIS beक्रमe seting DRDY*/
		ग_लिखोl(EP_STS_TRBERR | EP_STS_DESCMIS, &priv_dev->regs->ep_sts);
		ग_लिखोl(EP_CMD_DRDY, &priv_dev->regs->ep_cmd);
		trace_cdns3_करोorbell_epx(priv_ep->name,
					 पढ़ोl(&priv_dev->regs->ep_traddr));
	पूर्ण

	/* WORKAROUND क्रम transition to L0 */
	__cdns3_gadget_wakeup(priv_dev);

	वापस 0;
पूर्ण

व्योम cdns3_set_hw_configuration(काष्ठा cdns3_device *priv_dev)
अणु
	काष्ठा cdns3_endpoपूर्णांक *priv_ep;
	काष्ठा usb_ep *ep;

	अगर (priv_dev->hw_configured_flag)
		वापस;

	ग_लिखोl(USB_CONF_CFGSET, &priv_dev->regs->usb_conf);

	cdns3_set_रेजिस्टर_bit(&priv_dev->regs->usb_conf,
			       USB_CONF_U1EN | USB_CONF_U2EN);

	priv_dev->hw_configured_flag = 1;

	list_क्रम_each_entry(ep, &priv_dev->gadget.ep_list, ep_list) अणु
		अगर (ep->enabled) अणु
			priv_ep = ep_to_cdns3_ep(ep);
			cdns3_start_all_request(priv_dev, priv_ep);
		पूर्ण
	पूर्ण

	cdns3_allow_enable_l1(priv_dev, 1);
पूर्ण

/**
 * cdns3_trb_handled - check whether trb has been handled by DMA
 *
 * @priv_ep: extended endpoपूर्णांक object.
 * @priv_req: request object क्रम checking
 *
 * Endpoपूर्णांक must be selected beक्रमe invoking this function.
 *
 * Returns false अगर request has not been handled by DMA, अन्यथा वापसs true.
 *
 * SR - start ring
 * ER -  end ring
 * DQ = priv_ep->dequeue - dequeue position
 * EQ = priv_ep->enqueue -  enqueue position
 * ST = priv_req->start_trb - index of first TRB in transfer ring
 * ET = priv_req->end_trb - index of last TRB in transfer ring
 * CI = current_index - index of processed TRB by DMA.
 *
 * As first step, we check अगर the TRB between the ST and ET.
 * Then, we check अगर cycle bit क्रम index priv_ep->dequeue
 * is correct.
 *
 * some rules:
 * 1. priv_ep->dequeue never equals to current_index.
 * 2  priv_ep->enqueue never exceed priv_ep->dequeue
 * 3. exception: priv_ep->enqueue == priv_ep->dequeue
 *    and priv_ep->मुक्त_trbs is zero.
 *    This हाल indicate that TR is full.
 *
 * At below two हालs, the request have been handled.
 * Case 1 - priv_ep->dequeue < current_index
 *      SR ... EQ ... DQ ... CI ... ER
 *      SR ... DQ ... CI ... EQ ... ER
 *
 * Case 2 - priv_ep->dequeue > current_index
 * This situation takes place when CI go through the LINK TRB at the end of
 * transfer ring.
 *      SR ... CI ... EQ ... DQ ... ER
 */
अटल bool cdns3_trb_handled(काष्ठा cdns3_endpoपूर्णांक *priv_ep,
				  काष्ठा cdns3_request *priv_req)
अणु
	काष्ठा cdns3_device *priv_dev = priv_ep->cdns3_dev;
	काष्ठा cdns3_trb *trb;
	पूर्णांक current_index = 0;
	पूर्णांक handled = 0;
	पूर्णांक करोorbell;

	current_index = cdns3_get_dma_pos(priv_dev, priv_ep);
	करोorbell = !!(पढ़ोl(&priv_dev->regs->ep_cmd) & EP_CMD_DRDY);

	/* current trb करोesn't beदीर्घ to this request */
	अगर (priv_req->start_trb < priv_req->end_trb) अणु
		अगर (priv_ep->dequeue > priv_req->end_trb)
			जाओ finish;

		अगर (priv_ep->dequeue < priv_req->start_trb)
			जाओ finish;
	पूर्ण

	अगर ((priv_req->start_trb > priv_req->end_trb) &&
		(priv_ep->dequeue > priv_req->end_trb) &&
		(priv_ep->dequeue < priv_req->start_trb))
		जाओ finish;

	अगर ((priv_req->start_trb == priv_req->end_trb) &&
		(priv_ep->dequeue != priv_req->end_trb))
		जाओ finish;

	trb = &priv_ep->trb_pool[priv_ep->dequeue];

	अगर ((le32_to_cpu(trb->control) & TRB_CYCLE) != priv_ep->ccs)
		जाओ finish;

	अगर (करोorbell == 1 && current_index == priv_ep->dequeue)
		जाओ finish;

	/* The corner हाल क्रम TRBS_PER_SEGMENT equal 2). */
	अगर (TRBS_PER_SEGMENT == 2 && priv_ep->type != USB_ENDPOINT_XFER_ISOC) अणु
		handled = 1;
		जाओ finish;
	पूर्ण

	अगर (priv_ep->enqueue == priv_ep->dequeue &&
	    priv_ep->मुक्त_trbs == 0) अणु
		handled = 1;
	पूर्ण अन्यथा अगर (priv_ep->dequeue < current_index) अणु
		अगर ((current_index == (priv_ep->num_trbs - 1)) &&
		    !priv_ep->dequeue)
			जाओ finish;

		handled = 1;
	पूर्ण अन्यथा अगर (priv_ep->dequeue  > current_index) अणु
			handled = 1;
	पूर्ण

finish:
	trace_cdns3_request_handled(priv_req, current_index, handled);

	वापस handled;
पूर्ण

अटल व्योम cdns3_transfer_completed(काष्ठा cdns3_device *priv_dev,
				     काष्ठा cdns3_endpoपूर्णांक *priv_ep)
अणु
	काष्ठा cdns3_request *priv_req;
	काष्ठा usb_request *request;
	काष्ठा cdns3_trb *trb;
	bool request_handled = false;
	bool transfer_end = false;

	जबतक (!list_empty(&priv_ep->pending_req_list)) अणु
		request = cdns3_next_request(&priv_ep->pending_req_list);
		priv_req = to_cdns3_request(request);

		trb = priv_ep->trb_pool + priv_ep->dequeue;

		/* Request was dequeued and TRB was changed to TRB_LINK. */
		अगर (TRB_FIELD_TO_TYPE(le32_to_cpu(trb->control)) == TRB_LINK) अणु
			trace_cdns3_complete_trb(priv_ep, trb);
			cdns3_move_deq_to_next_trb(priv_req);
		पूर्ण

		अगर (!request->stream_id) अणु
			/* Re-select endpoपूर्णांक. It could be changed by other CPU
			 * during handling usb_gadget_giveback_request.
			 */
			cdns3_select_ep(priv_dev, priv_ep->endpoपूर्णांक.address);

			जबतक (cdns3_trb_handled(priv_ep, priv_req)) अणु
				priv_req->finished_trb++;
				अगर (priv_req->finished_trb >= priv_req->num_of_trb)
					request_handled = true;

				trb = priv_ep->trb_pool + priv_ep->dequeue;
				trace_cdns3_complete_trb(priv_ep, trb);

				अगर (!transfer_end)
					request->actual +=
						TRB_LEN(le32_to_cpu(trb->length));

				अगर (priv_req->num_of_trb > 1 &&
					le32_to_cpu(trb->control) & TRB_SMM)
					transfer_end = true;

				cdns3_ep_inc_deq(priv_ep);
			पूर्ण

			अगर (request_handled) अणु
				cdns3_gadget_giveback(priv_ep, priv_req, 0);
				request_handled = false;
				transfer_end = false;
			पूर्ण अन्यथा अणु
				जाओ prepare_next_td;
			पूर्ण

			अगर (priv_ep->type != USB_ENDPOINT_XFER_ISOC &&
			    TRBS_PER_SEGMENT == 2)
				अवरोध;
		पूर्ण अन्यथा अणु
			/* Re-select endpoपूर्णांक. It could be changed by other CPU
			 * during handling usb_gadget_giveback_request.
			 */
			cdns3_select_ep(priv_dev, priv_ep->endpoपूर्णांक.address);

			trb = priv_ep->trb_pool;
			trace_cdns3_complete_trb(priv_ep, trb);

			अगर (trb != priv_req->trb)
				dev_warn(priv_dev->dev,
					 "request_trb=0x%p, queue_trb=0x%p\n",
					 priv_req->trb, trb);

			request->actual += TRB_LEN(le32_to_cpu(trb->length));

			अगर (!request->num_sgs ||
			    (request->num_sgs == (priv_ep->stream_sg_idx + 1))) अणु
				priv_ep->stream_sg_idx = 0;
				cdns3_gadget_giveback(priv_ep, priv_req, 0);
			पूर्ण अन्यथा अणु
				priv_ep->stream_sg_idx++;
				cdns3_ep_run_stream_transfer(priv_ep, request);
			पूर्ण
			अवरोध;
		पूर्ण
	पूर्ण
	priv_ep->flags &= ~EP_PENDING_REQUEST;

prepare_next_td:
	अगर (!(priv_ep->flags & EP_STALLED) &&
	    !(priv_ep->flags & EP_STALL_PENDING))
		cdns3_start_all_request(priv_dev, priv_ep);
पूर्ण

व्योम cdns3_rearm_transfer(काष्ठा cdns3_endpoपूर्णांक *priv_ep, u8 rearm)
अणु
	काष्ठा cdns3_device *priv_dev = priv_ep->cdns3_dev;

	cdns3_wa1_restore_cycle_bit(priv_ep);

	अगर (rearm) अणु
		trace_cdns3_ring(priv_ep);

		/* Cycle Bit must be updated beक्रमe arming DMA. */
		wmb();
		ग_लिखोl(EP_CMD_DRDY, &priv_dev->regs->ep_cmd);

		__cdns3_gadget_wakeup(priv_dev);

		trace_cdns3_करोorbell_epx(priv_ep->name,
					 पढ़ोl(&priv_dev->regs->ep_traddr));
	पूर्ण
पूर्ण

अटल व्योम cdns3_reprogram_tdl(काष्ठा cdns3_endpoपूर्णांक *priv_ep)
अणु
	u16 tdl = priv_ep->pending_tdl;
	काष्ठा cdns3_device *priv_dev = priv_ep->cdns3_dev;

	अगर (tdl > EP_CMD_TDL_MAX) अणु
		tdl = EP_CMD_TDL_MAX;
		priv_ep->pending_tdl -= EP_CMD_TDL_MAX;
	पूर्ण अन्यथा अणु
		priv_ep->pending_tdl = 0;
	पूर्ण

	ग_लिखोl(EP_CMD_TDL_SET(tdl) | EP_CMD_STDL, &priv_dev->regs->ep_cmd);
पूर्ण

/**
 * cdns3_check_ep_पूर्णांकerrupt_proceed - Processes पूर्णांकerrupt related to endpoपूर्णांक
 * @priv_ep: endpoपूर्णांक object
 *
 * Returns 0
 */
अटल पूर्णांक cdns3_check_ep_पूर्णांकerrupt_proceed(काष्ठा cdns3_endpoपूर्णांक *priv_ep)
अणु
	काष्ठा cdns3_device *priv_dev = priv_ep->cdns3_dev;
	u32 ep_sts_reg;
	काष्ठा usb_request *deferred_request;
	काष्ठा usb_request *pending_request;
	u32 tdl = 0;

	cdns3_select_ep(priv_dev, priv_ep->endpoपूर्णांक.address);

	trace_cdns3_epx_irq(priv_dev, priv_ep);

	ep_sts_reg = पढ़ोl(&priv_dev->regs->ep_sts);
	ग_लिखोl(ep_sts_reg, &priv_dev->regs->ep_sts);

	अगर ((ep_sts_reg & EP_STS_PRIME) && priv_ep->use_streams) अणु
		bool dbusy = !!(ep_sts_reg & EP_STS_DBUSY);

		tdl = cdns3_get_tdl(priv_dev);

		/*
		 * Continue the previous transfer:
		 * There is some racing between ERDY and PRIME. The device send
		 * ERDY and almost in the same समय Host send PRIME. It cause
		 * that host ignore the ERDY packet and driver has to send it
		 * again.
		 */
		अगर (tdl && (dbusy || !EP_STS_BUFFEMPTY(ep_sts_reg) ||
		    EP_STS_HOSTPP(ep_sts_reg))) अणु
			ग_लिखोl(EP_CMD_ERDY |
			       EP_CMD_ERDY_SID(priv_ep->last_stream_id),
			       &priv_dev->regs->ep_cmd);
			ep_sts_reg &= ~(EP_STS_MD_EXIT | EP_STS_IOC);
		पूर्ण अन्यथा अणु
			priv_ep->prime_flag = true;

			pending_request = cdns3_next_request(&priv_ep->pending_req_list);
			deferred_request = cdns3_next_request(&priv_ep->deferred_req_list);

			अगर (deferred_request && !pending_request) अणु
				cdns3_start_all_request(priv_dev, priv_ep);
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (ep_sts_reg & EP_STS_TRBERR) अणु
		अगर (priv_ep->flags & EP_STALL_PENDING &&
		    !(ep_sts_reg & EP_STS_DESCMIS &&
		    priv_dev->dev_ver < DEV_VER_V2)) अणु
			cdns3_ep_stall_flush(priv_ep);
		पूर्ण

		/*
		 * For isochronous transfer driver completes request on
		 * IOC or on TRBERR. IOC appears only when device receive
		 * OUT data packet. If host disable stream or lost some packet
		 * then the only way to finish all queued transfer is to करो it
		 * on TRBERR event.
		 */
		अगर (priv_ep->type == USB_ENDPOINT_XFER_ISOC &&
		    !priv_ep->wa1_set) अणु
			अगर (!priv_ep->dir) अणु
				u32 ep_cfg = पढ़ोl(&priv_dev->regs->ep_cfg);

				ep_cfg &= ~EP_CFG_ENABLE;
				ग_लिखोl(ep_cfg, &priv_dev->regs->ep_cfg);
				priv_ep->flags &= ~EP_QUIRK_ISO_OUT_EN;
			पूर्ण
			cdns3_transfer_completed(priv_dev, priv_ep);
		पूर्ण अन्यथा अगर (!(priv_ep->flags & EP_STALLED) &&
			  !(priv_ep->flags & EP_STALL_PENDING)) अणु
			अगर (priv_ep->flags & EP_DEFERRED_DRDY) अणु
				priv_ep->flags &= ~EP_DEFERRED_DRDY;
				cdns3_start_all_request(priv_dev, priv_ep);
			पूर्ण अन्यथा अणु
				cdns3_rearm_transfer(priv_ep,
						     priv_ep->wa1_set);
			पूर्ण
		पूर्ण
	पूर्ण

	अगर ((ep_sts_reg & EP_STS_IOC) || (ep_sts_reg & EP_STS_ISP) ||
	    (ep_sts_reg & EP_STS_IOT)) अणु
		अगर (priv_ep->flags & EP_QUIRK_EXTRA_BUF_EN) अणु
			अगर (ep_sts_reg & EP_STS_ISP)
				priv_ep->flags |= EP_QUIRK_END_TRANSFER;
			अन्यथा
				priv_ep->flags &= ~EP_QUIRK_END_TRANSFER;
		पूर्ण

		अगर (!priv_ep->use_streams) अणु
			अगर ((ep_sts_reg & EP_STS_IOC) ||
			    (ep_sts_reg & EP_STS_ISP)) अणु
				cdns3_transfer_completed(priv_dev, priv_ep);
			पूर्ण अन्यथा अगर ((priv_ep->flags & EP_TDLCHK_EN) &
				   priv_ep->pending_tdl) अणु
				/* handle IOT with pending tdl */
				cdns3_reprogram_tdl(priv_ep);
			पूर्ण
		पूर्ण अन्यथा अगर (priv_ep->dir == USB_सूची_OUT) अणु
			priv_ep->ep_sts_pending |= ep_sts_reg;
		पूर्ण अन्यथा अगर (ep_sts_reg & EP_STS_IOT) अणु
			cdns3_transfer_completed(priv_dev, priv_ep);
		पूर्ण
	पूर्ण

	/*
	 * MD_EXIT पूर्णांकerrupt sets when stream capable endpoपूर्णांक निकासs
	 * from MOVE DATA state of Bulk IN/OUT stream protocol state machine
	 */
	अगर (priv_ep->dir == USB_सूची_OUT && (ep_sts_reg & EP_STS_MD_EXIT) &&
	    (priv_ep->ep_sts_pending & EP_STS_IOT) && priv_ep->use_streams) अणु
		priv_ep->ep_sts_pending = 0;
		cdns3_transfer_completed(priv_dev, priv_ep);
	पूर्ण

	/*
	 * WA2: this condition should only be meet when
	 * priv_ep->flags & EP_QUIRK_EXTRA_BUF_DET or
	 * priv_ep->flags & EP_QUIRK_EXTRA_BUF_EN.
	 * In other हालs this पूर्णांकerrupt will be disabled.
	 */
	अगर (ep_sts_reg & EP_STS_DESCMIS && priv_dev->dev_ver < DEV_VER_V2 &&
	    !(priv_ep->flags & EP_STALLED))
		cdns3_wa2_descmissing_packet(priv_ep);

	वापस 0;
पूर्ण

अटल व्योम cdns3_disconnect_gadget(काष्ठा cdns3_device *priv_dev)
अणु
	अगर (priv_dev->gadget_driver && priv_dev->gadget_driver->disconnect)
		priv_dev->gadget_driver->disconnect(&priv_dev->gadget);
पूर्ण

/**
 * cdns3_check_usb_पूर्णांकerrupt_proceed - Processes पूर्णांकerrupt related to device
 * @priv_dev: extended gadget object
 * @usb_ists: biपंचांगap representation of device's reported पूर्णांकerrupts
 * (usb_ists रेजिस्टर value)
 */
अटल व्योम cdns3_check_usb_पूर्णांकerrupt_proceed(काष्ठा cdns3_device *priv_dev,
					      u32 usb_ists)
__must_hold(&priv_dev->lock)
अणु
	पूर्णांक speed = 0;

	trace_cdns3_usb_irq(priv_dev, usb_ists);
	अगर (usb_ists & USB_ISTS_L1ENTI) अणु
		/*
		 * WORKAROUND: CDNS3 controller has issue with hardware resuming
		 * from L1. To fix it, अगर any DMA transfer is pending driver
		 * must starts driving resume संकेत immediately.
		 */
		अगर (पढ़ोl(&priv_dev->regs->drbl))
			__cdns3_gadget_wakeup(priv_dev);
	पूर्ण

	/* Connection detected */
	अगर (usb_ists & (USB_ISTS_CON2I | USB_ISTS_CONI)) अणु
		speed = cdns3_get_speed(priv_dev);
		priv_dev->gadget.speed = speed;
		usb_gadget_set_state(&priv_dev->gadget, USB_STATE_POWERED);
		cdns3_ep0_config(priv_dev);
	पूर्ण

	/* Disconnection detected */
	अगर (usb_ists & (USB_ISTS_DIS2I | USB_ISTS_DISI)) अणु
		spin_unlock(&priv_dev->lock);
		cdns3_disconnect_gadget(priv_dev);
		spin_lock(&priv_dev->lock);
		priv_dev->gadget.speed = USB_SPEED_UNKNOWN;
		usb_gadget_set_state(&priv_dev->gadget, USB_STATE_NOTATTACHED);
		cdns3_hw_reset_eps_config(priv_dev);
	पूर्ण

	अगर (usb_ists & (USB_ISTS_L2ENTI | USB_ISTS_U3ENTI)) अणु
		अगर (priv_dev->gadget_driver &&
		    priv_dev->gadget_driver->suspend) अणु
			spin_unlock(&priv_dev->lock);
			priv_dev->gadget_driver->suspend(&priv_dev->gadget);
			spin_lock(&priv_dev->lock);
		पूर्ण
	पूर्ण

	अगर (usb_ists & (USB_ISTS_L2EXTI | USB_ISTS_U3EXTI)) अणु
		अगर (priv_dev->gadget_driver &&
		    priv_dev->gadget_driver->resume) अणु
			spin_unlock(&priv_dev->lock);
			priv_dev->gadget_driver->resume(&priv_dev->gadget);
			spin_lock(&priv_dev->lock);
		पूर्ण
	पूर्ण

	/* reset*/
	अगर (usb_ists & (USB_ISTS_UWRESI | USB_ISTS_UHRESI | USB_ISTS_U2RESI)) अणु
		अगर (priv_dev->gadget_driver) अणु
			spin_unlock(&priv_dev->lock);
			usb_gadget_udc_reset(&priv_dev->gadget,
					     priv_dev->gadget_driver);
			spin_lock(&priv_dev->lock);

			/*पढ़ो again to check the actual speed*/
			speed = cdns3_get_speed(priv_dev);
			priv_dev->gadget.speed = speed;
			cdns3_hw_reset_eps_config(priv_dev);
			cdns3_ep0_config(priv_dev);
		पूर्ण
	पूर्ण
पूर्ण

/**
 * cdns3_device_irq_handler- पूर्णांकerrupt handler क्रम device part of controller
 *
 * @irq: irq number क्रम cdns3 core device
 * @data: काष्ठाure of cdns3
 *
 * Returns IRQ_HANDLED or IRQ_NONE
 */
अटल irqवापस_t cdns3_device_irq_handler(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा cdns3_device *priv_dev = data;
	काष्ठा cdns *cdns = dev_get_drvdata(priv_dev->dev);
	irqवापस_t ret = IRQ_NONE;
	u32 reg;

	अगर (cdns->in_lpm)
		वापस ret;

	/* check USB device पूर्णांकerrupt */
	reg = पढ़ोl(&priv_dev->regs->usb_ists);
	अगर (reg) अणु
		/* After masking पूर्णांकerrupts the new पूर्णांकerrupts won't be
		 * reported in usb_ists/ep_ists. In order to not lose some
		 * of them driver disables only detected पूर्णांकerrupts.
		 * They will be enabled ASAP after clearing source of
		 * पूर्णांकerrupt. This an unusual behavior only applies to
		 * usb_ists रेजिस्टर.
		 */
		reg = ~reg & पढ़ोl(&priv_dev->regs->usb_ien);
		/* mask deferred पूर्णांकerrupt. */
		ग_लिखोl(reg, &priv_dev->regs->usb_ien);
		ret = IRQ_WAKE_THREAD;
	पूर्ण

	/* check endpoपूर्णांक पूर्णांकerrupt */
	reg = पढ़ोl(&priv_dev->regs->ep_ists);
	अगर (reg) अणु
		ग_लिखोl(0, &priv_dev->regs->ep_ien);
		ret = IRQ_WAKE_THREAD;
	पूर्ण

	वापस ret;
पूर्ण

/**
 * cdns3_device_thपढ़ो_irq_handler- पूर्णांकerrupt handler क्रम device part
 * of controller
 *
 * @irq: irq number क्रम cdns3 core device
 * @data: काष्ठाure of cdns3
 *
 * Returns IRQ_HANDLED or IRQ_NONE
 */
अटल irqवापस_t cdns3_device_thपढ़ो_irq_handler(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा cdns3_device *priv_dev = data;
	irqवापस_t ret = IRQ_NONE;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक bit;
	अचिन्हित दीर्घ reg;

	spin_lock_irqsave(&priv_dev->lock, flags);

	reg = पढ़ोl(&priv_dev->regs->usb_ists);
	अगर (reg) अणु
		ग_लिखोl(reg, &priv_dev->regs->usb_ists);
		ग_लिखोl(USB_IEN_INIT, &priv_dev->regs->usb_ien);
		cdns3_check_usb_पूर्णांकerrupt_proceed(priv_dev, reg);
		ret = IRQ_HANDLED;
	पूर्ण

	reg = पढ़ोl(&priv_dev->regs->ep_ists);

	/* handle शेष endpoपूर्णांक OUT */
	अगर (reg & EP_ISTS_EP_OUT0) अणु
		cdns3_check_ep0_पूर्णांकerrupt_proceed(priv_dev, USB_सूची_OUT);
		ret = IRQ_HANDLED;
	पूर्ण

	/* handle शेष endpoपूर्णांक IN */
	अगर (reg & EP_ISTS_EP_IN0) अणु
		cdns3_check_ep0_पूर्णांकerrupt_proceed(priv_dev, USB_सूची_IN);
		ret = IRQ_HANDLED;
	पूर्ण

	/* check अगर पूर्णांकerrupt from non शेष endpoपूर्णांक, अगर no निकास */
	reg &= ~(EP_ISTS_EP_OUT0 | EP_ISTS_EP_IN0);
	अगर (!reg)
		जाओ irqend;

	क्रम_each_set_bit(bit, &reg,
			 माप(u32) * BITS_PER_BYTE) अणु
		cdns3_check_ep_पूर्णांकerrupt_proceed(priv_dev->eps[bit]);
		ret = IRQ_HANDLED;
	पूर्ण

	अगर (priv_dev->dev_ver < DEV_VER_V2 && priv_dev->using_streams)
		cdns3_wa2_check_outq_status(priv_dev);

irqend:
	ग_लिखोl(~0, &priv_dev->regs->ep_ien);
	spin_unlock_irqrestore(&priv_dev->lock, flags);

	वापस ret;
पूर्ण

/**
 * cdns3_ep_onchip_buffer_reserve - Try to reserve onchip buf क्रम EP
 *
 * The real reservation will occur during ग_लिखो to EP_CFG रेजिस्टर,
 * this function is used to check अगर the 'size' reservation is allowed.
 *
 * @priv_dev: extended gadget object
 * @size: the size (KB) क्रम EP would like to allocate
 * @is_in: endpoपूर्णांक direction
 *
 * Return 0 अगर the required size can met or negative value on failure
 */
अटल पूर्णांक cdns3_ep_onchip_buffer_reserve(काष्ठा cdns3_device *priv_dev,
					  पूर्णांक size, पूर्णांक is_in)
अणु
	पूर्णांक reमुख्यed;

	/* 2KB are reserved क्रम EP0*/
	reमुख्यed = priv_dev->onchip_buffers - priv_dev->onchip_used_size - 2;

	अगर (is_in) अणु
		अगर (reमुख्यed < size)
			वापस -EPERM;

		priv_dev->onchip_used_size += size;
	पूर्ण अन्यथा अणु
		पूर्णांक required;

		/**
		 *  ALL OUT EPs are shared the same chunk onchip memory, so
		 * driver checks अगर it alपढ़ोy has asचिन्हित enough buffers
		 */
		अगर (priv_dev->out_mem_is_allocated >= size)
			वापस 0;

		required = size - priv_dev->out_mem_is_allocated;

		अगर (required > reमुख्यed)
			वापस -EPERM;

		priv_dev->out_mem_is_allocated += required;
		priv_dev->onchip_used_size += required;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम cdns3_configure_dmult(काष्ठा cdns3_device *priv_dev,
				  काष्ठा cdns3_endpoपूर्णांक *priv_ep)
अणु
	काष्ठा cdns3_usb_regs __iomem *regs = priv_dev->regs;

	/* For dev_ver > DEV_VER_V2 DMULT is configured per endpoपूर्णांक */
	अगर (priv_dev->dev_ver <= DEV_VER_V2)
		ग_लिखोl(USB_CONF_DMULT, &regs->usb_conf);

	अगर (priv_dev->dev_ver == DEV_VER_V2)
		ग_लिखोl(USB_CONF2_EN_TDL_TRB, &regs->usb_conf2);

	अगर (priv_dev->dev_ver >= DEV_VER_V3 && priv_ep) अणु
		u32 mask;

		अगर (priv_ep->dir)
			mask = BIT(priv_ep->num + 16);
		अन्यथा
			mask = BIT(priv_ep->num);

		अगर (priv_ep->type != USB_ENDPOINT_XFER_ISOC  && !priv_ep->dir) अणु
			cdns3_set_रेजिस्टर_bit(&regs->tdl_from_trb, mask);
			cdns3_set_रेजिस्टर_bit(&regs->tdl_beh, mask);
			cdns3_set_रेजिस्टर_bit(&regs->tdl_beh2, mask);
			cdns3_set_रेजिस्टर_bit(&regs->dma_adv_td, mask);
		पूर्ण

		अगर (priv_ep->type == USB_ENDPOINT_XFER_ISOC && !priv_ep->dir)
			cdns3_set_रेजिस्टर_bit(&regs->tdl_from_trb, mask);

		cdns3_set_रेजिस्टर_bit(&regs->dtrans, mask);
	पूर्ण
पूर्ण

/**
 * cdns3_ep_config Configure hardware endpoपूर्णांक
 * @priv_ep: extended endpoपूर्णांक object
 * @enable: set EP_CFG_ENABLE bit in ep_cfg रेजिस्टर.
 */
पूर्णांक cdns3_ep_config(काष्ठा cdns3_endpoपूर्णांक *priv_ep, bool enable)
अणु
	bool is_iso_ep = (priv_ep->type == USB_ENDPOINT_XFER_ISOC);
	काष्ठा cdns3_device *priv_dev = priv_ep->cdns3_dev;
	u32 bEndpoपूर्णांकAddress = priv_ep->num | priv_ep->dir;
	u32 max_packet_size = 0;
	u8 maxburst = 0;
	u32 ep_cfg = 0;
	u8 buffering;
	u8 mult = 0;
	पूर्णांक ret;

	buffering = CDNS3_EP_BUF_SIZE - 1;

	cdns3_configure_dmult(priv_dev, priv_ep);

	चयन (priv_ep->type) अणु
	हाल USB_ENDPOINT_XFER_INT:
		ep_cfg = EP_CFG_EPTYPE(USB_ENDPOINT_XFER_INT);

		अगर (priv_dev->dev_ver >= DEV_VER_V2 && !priv_ep->dir)
			ep_cfg |= EP_CFG_TDL_CHK;
		अवरोध;
	हाल USB_ENDPOINT_XFER_BULK:
		ep_cfg = EP_CFG_EPTYPE(USB_ENDPOINT_XFER_BULK);

		अगर (priv_dev->dev_ver >= DEV_VER_V2 && !priv_ep->dir)
			ep_cfg |= EP_CFG_TDL_CHK;
		अवरोध;
	शेष:
		ep_cfg = EP_CFG_EPTYPE(USB_ENDPOINT_XFER_ISOC);
		mult = CDNS3_EP_ISO_HS_MULT - 1;
		buffering = mult + 1;
	पूर्ण

	चयन (priv_dev->gadget.speed) अणु
	हाल USB_SPEED_FULL:
		max_packet_size = is_iso_ep ? 1023 : 64;
		अवरोध;
	हाल USB_SPEED_HIGH:
		max_packet_size = is_iso_ep ? 1024 : 512;
		अवरोध;
	हाल USB_SPEED_SUPER:
		/* It's limitation that driver assumes in driver. */
		mult = 0;
		max_packet_size = 1024;
		अगर (priv_ep->type == USB_ENDPOINT_XFER_ISOC) अणु
			maxburst = CDNS3_EP_ISO_SS_BURST - 1;
			buffering = (mult + 1) *
				    (maxburst + 1);

			अगर (priv_ep->पूर्णांकerval > 1)
				buffering++;
		पूर्ण अन्यथा अणु
			maxburst = CDNS3_EP_BUF_SIZE - 1;
		पूर्ण
		अवरोध;
	शेष:
		/* all other speed are not supported */
		वापस -EINVAL;
	पूर्ण

	अगर (max_packet_size == 1024)
		priv_ep->trb_burst_size = 128;
	अन्यथा अगर (max_packet_size >= 512)
		priv_ep->trb_burst_size = 64;
	अन्यथा
		priv_ep->trb_burst_size = 16;

	/* onchip buffer is only allocated beक्रमe configuration */
	अगर (!priv_dev->hw_configured_flag) अणु
		ret = cdns3_ep_onchip_buffer_reserve(priv_dev, buffering + 1,
						     !!priv_ep->dir);
		अगर (ret) अणु
			dev_err(priv_dev->dev, "onchip mem is full, ep is invalid\n");
			वापस ret;
		पूर्ण
	पूर्ण

	अगर (enable)
		ep_cfg |= EP_CFG_ENABLE;

	अगर (priv_ep->use_streams && priv_dev->gadget.speed >= USB_SPEED_SUPER) अणु
		अगर (priv_dev->dev_ver >= DEV_VER_V3) अणु
			u32 mask = BIT(priv_ep->num + (priv_ep->dir ? 16 : 0));

			/*
			 * Stream capable endpoपूर्णांकs are handled by using ep_tdl
			 * रेजिस्टर. Other endpoपूर्णांकs use TDL from TRB feature.
			 */
			cdns3_clear_रेजिस्टर_bit(&priv_dev->regs->tdl_from_trb,
						 mask);
		पूर्ण

		/*  Enable Stream Bit TDL chk and SID chk */
		ep_cfg |=  EP_CFG_STREAM_EN | EP_CFG_TDL_CHK | EP_CFG_SID_CHK;
	पूर्ण

	ep_cfg |= EP_CFG_MAXPKTSIZE(max_packet_size) |
		  EP_CFG_MULT(mult) |
		  EP_CFG_BUFFERING(buffering) |
		  EP_CFG_MAXBURST(maxburst);

	cdns3_select_ep(priv_dev, bEndpoपूर्णांकAddress);
	ग_लिखोl(ep_cfg, &priv_dev->regs->ep_cfg);
	priv_ep->flags |= EP_CONFIGURED;

	dev_dbg(priv_dev->dev, "Configure %s: with val %08x\n",
		priv_ep->name, ep_cfg);

	वापस 0;
पूर्ण

/* Find correct direction क्रम HW endpoपूर्णांक according to description */
अटल पूर्णांक cdns3_ep_dir_is_correct(काष्ठा usb_endpoपूर्णांक_descriptor *desc,
				   काष्ठा cdns3_endpoपूर्णांक *priv_ep)
अणु
	वापस (priv_ep->endpoपूर्णांक.caps.dir_in && usb_endpoपूर्णांक_dir_in(desc)) ||
	       (priv_ep->endpoपूर्णांक.caps.dir_out && usb_endpoपूर्णांक_dir_out(desc));
पूर्ण

अटल काष्ठा
cdns3_endpoपूर्णांक *cdns3_find_available_ep(काष्ठा cdns3_device *priv_dev,
					काष्ठा usb_endpoपूर्णांक_descriptor *desc)
अणु
	काष्ठा usb_ep *ep;
	काष्ठा cdns3_endpoपूर्णांक *priv_ep;

	list_क्रम_each_entry(ep, &priv_dev->gadget.ep_list, ep_list) अणु
		अचिन्हित दीर्घ num;
		पूर्णांक ret;
		/* ep name pattern likes epXin or epXout */
		अक्षर c[2] = अणुep->name[2], '\0'पूर्ण;

		ret = kम_से_अदीर्घ(c, 10, &num);
		अगर (ret)
			वापस ERR_PTR(ret);

		priv_ep = ep_to_cdns3_ep(ep);
		अगर (cdns3_ep_dir_is_correct(desc, priv_ep)) अणु
			अगर (!(priv_ep->flags & EP_CLAIMED)) अणु
				priv_ep->num  = num;
				वापस priv_ep;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस ERR_PTR(-ENOENT);
पूर्ण

/*
 *  Cadence IP has one limitation that all endpoपूर्णांकs must be configured
 * (Type & MaxPacketSize) beक्रमe setting configuration through hardware
 * रेजिस्टर, it means we can't change endpoपूर्णांकs configuration after
 * set_configuration.
 *
 * This function set EP_CLAIMED flag which is added when the gadget driver
 * uses usb_ep_स्वतःconfig to configure specअगरic endpoपूर्णांक;
 * When the udc driver receives set_configurion request,
 * it goes through all claimed endpoपूर्णांकs, and configure all endpoपूर्णांकs
 * accordingly.
 *
 * At usb_ep_ops.enable/disable, we only enable and disable endpoपूर्णांक through
 * ep_cfg रेजिस्टर which can be changed after set_configuration, and करो
 * some software operation accordingly.
 */
अटल काष्ठा
usb_ep *cdns3_gadget_match_ep(काष्ठा usb_gadget *gadget,
			      काष्ठा usb_endpoपूर्णांक_descriptor *desc,
			      काष्ठा usb_ss_ep_comp_descriptor *comp_desc)
अणु
	काष्ठा cdns3_device *priv_dev = gadget_to_cdns3_device(gadget);
	काष्ठा cdns3_endpoपूर्णांक *priv_ep;
	अचिन्हित दीर्घ flags;

	priv_ep = cdns3_find_available_ep(priv_dev, desc);
	अगर (IS_ERR(priv_ep)) अणु
		dev_err(priv_dev->dev, "no available ep\n");
		वापस शून्य;
	पूर्ण

	dev_dbg(priv_dev->dev, "match endpoint: %s\n", priv_ep->name);

	spin_lock_irqsave(&priv_dev->lock, flags);
	priv_ep->endpoपूर्णांक.desc = desc;
	priv_ep->dir  = usb_endpoपूर्णांक_dir_in(desc) ? USB_सूची_IN : USB_सूची_OUT;
	priv_ep->type = usb_endpoपूर्णांक_type(desc);
	priv_ep->flags |= EP_CLAIMED;
	priv_ep->पूर्णांकerval = desc->bInterval ? BIT(desc->bInterval - 1) : 0;

	spin_unlock_irqrestore(&priv_dev->lock, flags);
	वापस &priv_ep->endpoपूर्णांक;
पूर्ण

/**
 * cdns3_gadget_ep_alloc_request Allocates request
 * @ep: endpoपूर्णांक object associated with request
 * @gfp_flags: gfp flags
 *
 * Returns allocated request address, शून्य on allocation error
 */
काष्ठा usb_request *cdns3_gadget_ep_alloc_request(काष्ठा usb_ep *ep,
						  gfp_t gfp_flags)
अणु
	काष्ठा cdns3_endpoपूर्णांक *priv_ep = ep_to_cdns3_ep(ep);
	काष्ठा cdns3_request *priv_req;

	priv_req = kzalloc(माप(*priv_req), gfp_flags);
	अगर (!priv_req)
		वापस शून्य;

	priv_req->priv_ep = priv_ep;

	trace_cdns3_alloc_request(priv_req);
	वापस &priv_req->request;
पूर्ण

/**
 * cdns3_gadget_ep_मुक्त_request Free memory occupied by request
 * @ep: endpoपूर्णांक object associated with request
 * @request: request to मुक्त memory
 */
व्योम cdns3_gadget_ep_मुक्त_request(काष्ठा usb_ep *ep,
				  काष्ठा usb_request *request)
अणु
	काष्ठा cdns3_request *priv_req = to_cdns3_request(request);

	अगर (priv_req->aligned_buf)
		priv_req->aligned_buf->in_use = 0;

	trace_cdns3_मुक्त_request(priv_req);
	kमुक्त(priv_req);
पूर्ण

/**
 * cdns3_gadget_ep_enable Enable endpoपूर्णांक
 * @ep: endpoपूर्णांक object
 * @desc: endpoपूर्णांक descriptor
 *
 * Returns 0 on success, error code अन्यथाwhere
 */
अटल पूर्णांक cdns3_gadget_ep_enable(काष्ठा usb_ep *ep,
				  स्थिर काष्ठा usb_endpoपूर्णांक_descriptor *desc)
अणु
	काष्ठा cdns3_endpoपूर्णांक *priv_ep;
	काष्ठा cdns3_device *priv_dev;
	स्थिर काष्ठा usb_ss_ep_comp_descriptor *comp_desc;
	u32 reg = EP_STS_EN_TRBERREN;
	u32 bEndpoपूर्णांकAddress;
	अचिन्हित दीर्घ flags;
	पूर्णांक enable = 1;
	पूर्णांक ret = 0;
	पूर्णांक val;

	priv_ep = ep_to_cdns3_ep(ep);
	priv_dev = priv_ep->cdns3_dev;
	comp_desc = priv_ep->endpoपूर्णांक.comp_desc;

	अगर (!ep || !desc || desc->bDescriptorType != USB_DT_ENDPOINT) अणु
		dev_dbg(priv_dev->dev, "usbss: invalid parameters\n");
		वापस -EINVAL;
	पूर्ण

	अगर (!desc->wMaxPacketSize) अणु
		dev_err(priv_dev->dev, "usbss: missing wMaxPacketSize\n");
		वापस -EINVAL;
	पूर्ण

	अगर (dev_WARN_ONCE(priv_dev->dev, priv_ep->flags & EP_ENABLED,
			  "%s is already enabled\n", priv_ep->name))
		वापस 0;

	spin_lock_irqsave(&priv_dev->lock, flags);

	priv_ep->endpoपूर्णांक.desc = desc;
	priv_ep->type = usb_endpoपूर्णांक_type(desc);
	priv_ep->पूर्णांकerval = desc->bInterval ? BIT(desc->bInterval - 1) : 0;

	अगर (priv_ep->पूर्णांकerval > ISO_MAX_INTERVAL &&
	    priv_ep->type == USB_ENDPOINT_XFER_ISOC) अणु
		dev_err(priv_dev->dev, "Driver is limited to %d period\n",
			ISO_MAX_INTERVAL);

		ret =  -EINVAL;
		जाओ निकास;
	पूर्ण

	bEndpoपूर्णांकAddress = priv_ep->num | priv_ep->dir;
	cdns3_select_ep(priv_dev, bEndpoपूर्णांकAddress);

	/*
	 * For some versions of controller at some poपूर्णांक during ISO OUT traffic
	 * DMA पढ़ोs Transfer Ring क्रम the EP which has never got करोorbell.
	 * This issue was detected only on simulation, but to aव्योम this issue
	 * driver add protection against it. To fix it driver enable ISO OUT
	 * endpoपूर्णांक beक्रमe setting DRBL. This special treaपंचांगent of ISO OUT
	 * endpoपूर्णांकs are recommended by controller specअगरication.
	 */
	अगर (priv_ep->type == USB_ENDPOINT_XFER_ISOC  && !priv_ep->dir)
		enable = 0;

	अगर (usb_ss_max_streams(comp_desc) && usb_endpoपूर्णांक_xfer_bulk(desc)) अणु
		/*
		 * Enable stream support (SS mode) related पूर्णांकerrupts
		 * in EP_STS_EN Register
		 */
		अगर (priv_dev->gadget.speed >= USB_SPEED_SUPER) अणु
			reg |= EP_STS_EN_IOTEN | EP_STS_EN_PRIMEEEN |
				EP_STS_EN_SIDERREN | EP_STS_EN_MD_EXITEN |
				EP_STS_EN_STREAMREN;
			priv_ep->use_streams = true;
			ret = cdns3_ep_config(priv_ep, enable);
			priv_dev->using_streams |= true;
		पूर्ण
	पूर्ण अन्यथा अणु
		ret = cdns3_ep_config(priv_ep, enable);
	पूर्ण

	अगर (ret)
		जाओ निकास;

	ret = cdns3_allocate_trb_pool(priv_ep);
	अगर (ret)
		जाओ निकास;

	bEndpoपूर्णांकAddress = priv_ep->num | priv_ep->dir;
	cdns3_select_ep(priv_dev, bEndpoपूर्णांकAddress);

	trace_cdns3_gadget_ep_enable(priv_ep);

	ग_लिखोl(EP_CMD_EPRST, &priv_dev->regs->ep_cmd);

	ret = पढ़ोl_poll_समयout_atomic(&priv_dev->regs->ep_cmd, val,
					!(val & (EP_CMD_CSTALL | EP_CMD_EPRST)),
					1, 1000);

	अगर (unlikely(ret)) अणु
		cdns3_मुक्त_trb_pool(priv_ep);
		ret =  -EINVAL;
		जाओ निकास;
	पूर्ण

	/* enable पूर्णांकerrupt क्रम selected endpoपूर्णांक */
	cdns3_set_रेजिस्टर_bit(&priv_dev->regs->ep_ien,
			       BIT(cdns3_ep_addr_to_index(bEndpoपूर्णांकAddress)));

	अगर (priv_dev->dev_ver < DEV_VER_V2)
		cdns3_wa2_enable_detection(priv_dev, priv_ep, reg);

	ग_लिखोl(reg, &priv_dev->regs->ep_sts_en);

	ep->desc = desc;
	priv_ep->flags &= ~(EP_PENDING_REQUEST | EP_STALLED | EP_STALL_PENDING |
			    EP_QUIRK_ISO_OUT_EN | EP_QUIRK_EXTRA_BUF_EN);
	priv_ep->flags |= EP_ENABLED | EP_UPDATE_EP_TRBADDR;
	priv_ep->wa1_set = 0;
	priv_ep->enqueue = 0;
	priv_ep->dequeue = 0;
	reg = पढ़ोl(&priv_dev->regs->ep_sts);
	priv_ep->pcs = !!EP_STS_CCS(reg);
	priv_ep->ccs = !!EP_STS_CCS(reg);
	/* one TRB is reserved क्रम link TRB used in DMULT mode*/
	priv_ep->मुक्त_trbs = priv_ep->num_trbs - 1;
निकास:
	spin_unlock_irqrestore(&priv_dev->lock, flags);

	वापस ret;
पूर्ण

/**
 * cdns3_gadget_ep_disable Disable endpoपूर्णांक
 * @ep: endpoपूर्णांक object
 *
 * Returns 0 on success, error code अन्यथाwhere
 */
अटल पूर्णांक cdns3_gadget_ep_disable(काष्ठा usb_ep *ep)
अणु
	काष्ठा cdns3_endpoपूर्णांक *priv_ep;
	काष्ठा cdns3_request *priv_req;
	काष्ठा cdns3_device *priv_dev;
	काष्ठा usb_request *request;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = 0;
	u32 ep_cfg;
	पूर्णांक val;

	अगर (!ep) अणु
		pr_err("usbss: invalid parameters\n");
		वापस -EINVAL;
	पूर्ण

	priv_ep = ep_to_cdns3_ep(ep);
	priv_dev = priv_ep->cdns3_dev;

	अगर (dev_WARN_ONCE(priv_dev->dev, !(priv_ep->flags & EP_ENABLED),
			  "%s is already disabled\n", priv_ep->name))
		वापस 0;

	spin_lock_irqsave(&priv_dev->lock, flags);

	trace_cdns3_gadget_ep_disable(priv_ep);

	cdns3_select_ep(priv_dev, ep->desc->bEndpoपूर्णांकAddress);

	ep_cfg = पढ़ोl(&priv_dev->regs->ep_cfg);
	ep_cfg &= ~EP_CFG_ENABLE;
	ग_लिखोl(ep_cfg, &priv_dev->regs->ep_cfg);

	/**
	 * Driver needs some समय beक्रमe resetting endpoपूर्णांक.
	 * It need रुकोs क्रम clearing DBUSY bit or क्रम समयout expired.
	 * 10us is enough समय क्रम controller to stop transfer.
	 */
	पढ़ोl_poll_समयout_atomic(&priv_dev->regs->ep_sts, val,
				  !(val & EP_STS_DBUSY), 1, 10);
	ग_लिखोl(EP_CMD_EPRST, &priv_dev->regs->ep_cmd);

	पढ़ोl_poll_समयout_atomic(&priv_dev->regs->ep_cmd, val,
				  !(val & (EP_CMD_CSTALL | EP_CMD_EPRST)),
				  1, 1000);
	अगर (unlikely(ret))
		dev_err(priv_dev->dev, "Timeout: %s resetting failed.\n",
			priv_ep->name);

	जबतक (!list_empty(&priv_ep->pending_req_list)) अणु
		request = cdns3_next_request(&priv_ep->pending_req_list);

		cdns3_gadget_giveback(priv_ep, to_cdns3_request(request),
				      -ESHUTDOWN);
	पूर्ण

	जबतक (!list_empty(&priv_ep->wa2_descmiss_req_list)) अणु
		priv_req = cdns3_next_priv_request(&priv_ep->wa2_descmiss_req_list);

		kमुक्त(priv_req->request.buf);
		cdns3_gadget_ep_मुक्त_request(&priv_ep->endpoपूर्णांक,
					     &priv_req->request);
		list_del_init(&priv_req->list);
		--priv_ep->wa2_counter;
	पूर्ण

	जबतक (!list_empty(&priv_ep->deferred_req_list)) अणु
		request = cdns3_next_request(&priv_ep->deferred_req_list);

		cdns3_gadget_giveback(priv_ep, to_cdns3_request(request),
				      -ESHUTDOWN);
	पूर्ण

	priv_ep->descmis_req = शून्य;

	ep->desc = शून्य;
	priv_ep->flags &= ~EP_ENABLED;
	priv_ep->use_streams = false;

	spin_unlock_irqrestore(&priv_dev->lock, flags);

	वापस ret;
पूर्ण

/**
 * cdns3_gadget_ep_queue Transfer data on endpoपूर्णांक
 * @ep: endpoपूर्णांक object
 * @request: request object
 * @gfp_flags: gfp flags
 *
 * Returns 0 on success, error code अन्यथाwhere
 */
अटल पूर्णांक __cdns3_gadget_ep_queue(काष्ठा usb_ep *ep,
				   काष्ठा usb_request *request,
				   gfp_t gfp_flags)
अणु
	काष्ठा cdns3_endpoपूर्णांक *priv_ep = ep_to_cdns3_ep(ep);
	काष्ठा cdns3_device *priv_dev = priv_ep->cdns3_dev;
	काष्ठा cdns3_request *priv_req;
	पूर्णांक ret = 0;

	request->actual = 0;
	request->status = -EINPROGRESS;
	priv_req = to_cdns3_request(request);
	trace_cdns3_ep_queue(priv_req);

	अगर (priv_dev->dev_ver < DEV_VER_V2) अणु
		ret = cdns3_wa2_gadget_ep_queue(priv_dev, priv_ep,
						priv_req);

		अगर (ret == EINPROGRESS)
			वापस 0;
	पूर्ण

	ret = cdns3_prepare_aligned_request_buf(priv_req);
	अगर (ret < 0)
		वापस ret;

	ret = usb_gadget_map_request_by_dev(priv_dev->sysdev, request,
					    usb_endpoपूर्णांक_dir_in(ep->desc));
	अगर (ret)
		वापस ret;

	list_add_tail(&request->list, &priv_ep->deferred_req_list);

	/*
	 * For stream capable endpoपूर्णांक अगर prime irq flag is set then only start
	 * request.
	 * If hardware endpoपूर्णांक configuration has not been set yet then
	 * just queue request in deferred list. Transfer will be started in
	 * cdns3_set_hw_configuration.
	 */
	अगर (!request->stream_id) अणु
		अगर (priv_dev->hw_configured_flag &&
		    !(priv_ep->flags & EP_STALLED) &&
		    !(priv_ep->flags & EP_STALL_PENDING))
			cdns3_start_all_request(priv_dev, priv_ep);
	पूर्ण अन्यथा अणु
		अगर (priv_dev->hw_configured_flag && priv_ep->prime_flag)
			cdns3_start_all_request(priv_dev, priv_ep);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cdns3_gadget_ep_queue(काष्ठा usb_ep *ep, काष्ठा usb_request *request,
				 gfp_t gfp_flags)
अणु
	काष्ठा usb_request *zlp_request;
	काष्ठा cdns3_endpoपूर्णांक *priv_ep;
	काष्ठा cdns3_device *priv_dev;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	अगर (!request || !ep)
		वापस -EINVAL;

	priv_ep = ep_to_cdns3_ep(ep);
	priv_dev = priv_ep->cdns3_dev;

	spin_lock_irqsave(&priv_dev->lock, flags);

	ret = __cdns3_gadget_ep_queue(ep, request, gfp_flags);

	अगर (ret == 0 && request->zero && request->length &&
	    (request->length % ep->maxpacket == 0)) अणु
		काष्ठा cdns3_request *priv_req;

		zlp_request = cdns3_gadget_ep_alloc_request(ep, GFP_ATOMIC);
		zlp_request->buf = priv_dev->zlp_buf;
		zlp_request->length = 0;

		priv_req = to_cdns3_request(zlp_request);
		priv_req->flags |= REQUEST_ZLP;

		dev_dbg(priv_dev->dev, "Queuing ZLP for endpoint: %s\n",
			priv_ep->name);
		ret = __cdns3_gadget_ep_queue(ep, zlp_request, gfp_flags);
	पूर्ण

	spin_unlock_irqrestore(&priv_dev->lock, flags);
	वापस ret;
पूर्ण

/**
 * cdns3_gadget_ep_dequeue Remove request from transfer queue
 * @ep: endpoपूर्णांक object associated with request
 * @request: request object
 *
 * Returns 0 on success, error code अन्यथाwhere
 */
पूर्णांक cdns3_gadget_ep_dequeue(काष्ठा usb_ep *ep,
			    काष्ठा usb_request *request)
अणु
	काष्ठा cdns3_endpoपूर्णांक *priv_ep = ep_to_cdns3_ep(ep);
	काष्ठा cdns3_device *priv_dev = priv_ep->cdns3_dev;
	काष्ठा usb_request *req, *req_temp;
	काष्ठा cdns3_request *priv_req;
	काष्ठा cdns3_trb *link_trb;
	u8 req_on_hw_ring = 0;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = 0;

	अगर (!ep || !request || !ep->desc)
		वापस -EINVAL;

	spin_lock_irqsave(&priv_dev->lock, flags);

	priv_req = to_cdns3_request(request);

	trace_cdns3_ep_dequeue(priv_req);

	cdns3_select_ep(priv_dev, ep->desc->bEndpoपूर्णांकAddress);

	list_क्रम_each_entry_safe(req, req_temp, &priv_ep->pending_req_list,
				 list) अणु
		अगर (request == req) अणु
			req_on_hw_ring = 1;
			जाओ found;
		पूर्ण
	पूर्ण

	list_क्रम_each_entry_safe(req, req_temp, &priv_ep->deferred_req_list,
				 list) अणु
		अगर (request == req)
			जाओ found;
	पूर्ण

	जाओ not_found;

found:
	link_trb = priv_req->trb;

	/* Update ring only अगर हटाओd request is on pending_req_list list */
	अगर (req_on_hw_ring && link_trb) अणु
		link_trb->buffer = cpu_to_le32(TRB_BUFFER(priv_ep->trb_pool_dma +
			((priv_req->end_trb + 1) * TRB_SIZE)));
		link_trb->control = cpu_to_le32((le32_to_cpu(link_trb->control) & TRB_CYCLE) |
				    TRB_TYPE(TRB_LINK) | TRB_CHAIN);

		अगर (priv_ep->wa1_trb == priv_req->trb)
			cdns3_wa1_restore_cycle_bit(priv_ep);
	पूर्ण

	cdns3_gadget_giveback(priv_ep, priv_req, -ECONNRESET);

not_found:
	spin_unlock_irqrestore(&priv_dev->lock, flags);
	वापस ret;
पूर्ण

/**
 * __cdns3_gadget_ep_set_halt Sets stall on selected endpoपूर्णांक
 * Should be called after acquiring spin_lock and selecting ep
 * @priv_ep: endpoपूर्णांक object to set stall on.
 */
व्योम __cdns3_gadget_ep_set_halt(काष्ठा cdns3_endpoपूर्णांक *priv_ep)
अणु
	काष्ठा cdns3_device *priv_dev = priv_ep->cdns3_dev;

	trace_cdns3_halt(priv_ep, 1, 0);

	अगर (!(priv_ep->flags & EP_STALLED)) अणु
		u32 ep_sts_reg = पढ़ोl(&priv_dev->regs->ep_sts);

		अगर (!(ep_sts_reg & EP_STS_DBUSY))
			cdns3_ep_stall_flush(priv_ep);
		अन्यथा
			priv_ep->flags |= EP_STALL_PENDING;
	पूर्ण
पूर्ण

/**
 * __cdns3_gadget_ep_clear_halt Clears stall on selected endpoपूर्णांक
 * Should be called after acquiring spin_lock and selecting ep
 * @priv_ep: endpoपूर्णांक object to clear stall on
 */
पूर्णांक __cdns3_gadget_ep_clear_halt(काष्ठा cdns3_endpoपूर्णांक *priv_ep)
अणु
	काष्ठा cdns3_device *priv_dev = priv_ep->cdns3_dev;
	काष्ठा usb_request *request;
	काष्ठा cdns3_request *priv_req;
	काष्ठा cdns3_trb *trb = शून्य;
	पूर्णांक ret;
	पूर्णांक val;

	trace_cdns3_halt(priv_ep, 0, 0);

	request = cdns3_next_request(&priv_ep->pending_req_list);
	अगर (request) अणु
		priv_req = to_cdns3_request(request);
		trb = priv_req->trb;
		अगर (trb)
			trb->control = trb->control ^ cpu_to_le32(TRB_CYCLE);
	पूर्ण

	ग_लिखोl(EP_CMD_CSTALL | EP_CMD_EPRST, &priv_dev->regs->ep_cmd);

	/* रुको क्रम EPRST cleared */
	ret = पढ़ोl_poll_समयout_atomic(&priv_dev->regs->ep_cmd, val,
					!(val & EP_CMD_EPRST), 1, 100);
	अगर (ret)
		वापस -EINVAL;

	priv_ep->flags &= ~(EP_STALLED | EP_STALL_PENDING);

	अगर (request) अणु
		अगर (trb)
			trb->control = trb->control ^ cpu_to_le32(TRB_CYCLE);

		cdns3_rearm_transfer(priv_ep, 1);
	पूर्ण

	cdns3_start_all_request(priv_dev, priv_ep);
	वापस ret;
पूर्ण

/**
 * cdns3_gadget_ep_set_halt Sets/clears stall on selected endpoपूर्णांक
 * @ep: endpoपूर्णांक object to set/clear stall on
 * @value: 1 क्रम set stall, 0 क्रम clear stall
 *
 * Returns 0 on success, error code अन्यथाwhere
 */
पूर्णांक cdns3_gadget_ep_set_halt(काष्ठा usb_ep *ep, पूर्णांक value)
अणु
	काष्ठा cdns3_endpoपूर्णांक *priv_ep = ep_to_cdns3_ep(ep);
	काष्ठा cdns3_device *priv_dev = priv_ep->cdns3_dev;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = 0;

	अगर (!(priv_ep->flags & EP_ENABLED))
		वापस -EPERM;

	spin_lock_irqsave(&priv_dev->lock, flags);

	cdns3_select_ep(priv_dev, ep->desc->bEndpoपूर्णांकAddress);

	अगर (!value) अणु
		priv_ep->flags &= ~EP_WEDGE;
		ret = __cdns3_gadget_ep_clear_halt(priv_ep);
	पूर्ण अन्यथा अणु
		__cdns3_gadget_ep_set_halt(priv_ep);
	पूर्ण

	spin_unlock_irqrestore(&priv_dev->lock, flags);

	वापस ret;
पूर्ण

बाह्य स्थिर काष्ठा usb_ep_ops cdns3_gadget_ep0_ops;

अटल स्थिर काष्ठा usb_ep_ops cdns3_gadget_ep_ops = अणु
	.enable = cdns3_gadget_ep_enable,
	.disable = cdns3_gadget_ep_disable,
	.alloc_request = cdns3_gadget_ep_alloc_request,
	.मुक्त_request = cdns3_gadget_ep_मुक्त_request,
	.queue = cdns3_gadget_ep_queue,
	.dequeue = cdns3_gadget_ep_dequeue,
	.set_halt = cdns3_gadget_ep_set_halt,
	.set_wedge = cdns3_gadget_ep_set_wedge,
पूर्ण;

/**
 * cdns3_gadget_get_frame Returns number of actual ITP frame
 * @gadget: gadget object
 *
 * Returns number of actual ITP frame
 */
अटल पूर्णांक cdns3_gadget_get_frame(काष्ठा usb_gadget *gadget)
अणु
	काष्ठा cdns3_device *priv_dev = gadget_to_cdns3_device(gadget);

	वापस पढ़ोl(&priv_dev->regs->usb_itpn);
पूर्ण

पूर्णांक __cdns3_gadget_wakeup(काष्ठा cdns3_device *priv_dev)
अणु
	क्रमागत usb_device_speed speed;

	speed = cdns3_get_speed(priv_dev);

	अगर (speed >= USB_SPEED_SUPER)
		वापस 0;

	/* Start driving resume संकेतing to indicate remote wakeup. */
	ग_लिखोl(USB_CONF_LGO_L0, &priv_dev->regs->usb_conf);

	वापस 0;
पूर्ण

अटल पूर्णांक cdns3_gadget_wakeup(काष्ठा usb_gadget *gadget)
अणु
	काष्ठा cdns3_device *priv_dev = gadget_to_cdns3_device(gadget);
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = 0;

	spin_lock_irqsave(&priv_dev->lock, flags);
	ret = __cdns3_gadget_wakeup(priv_dev);
	spin_unlock_irqrestore(&priv_dev->lock, flags);
	वापस ret;
पूर्ण

अटल पूर्णांक cdns3_gadget_set_selfघातered(काष्ठा usb_gadget *gadget,
					पूर्णांक is_selfघातered)
अणु
	काष्ठा cdns3_device *priv_dev = gadget_to_cdns3_device(gadget);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&priv_dev->lock, flags);
	priv_dev->is_selfघातered = !!is_selfघातered;
	spin_unlock_irqrestore(&priv_dev->lock, flags);
	वापस 0;
पूर्ण

अटल पूर्णांक cdns3_gadget_pullup(काष्ठा usb_gadget *gadget, पूर्णांक is_on)
अणु
	काष्ठा cdns3_device *priv_dev = gadget_to_cdns3_device(gadget);

	अगर (is_on) अणु
		ग_लिखोl(USB_CONF_DEVEN, &priv_dev->regs->usb_conf);
	पूर्ण अन्यथा अणु
		ग_लिखोl(~0, &priv_dev->regs->ep_ists);
		ग_लिखोl(~0, &priv_dev->regs->usb_ists);
		ग_लिखोl(USB_CONF_DEVDS, &priv_dev->regs->usb_conf);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम cdns3_gadget_config(काष्ठा cdns3_device *priv_dev)
अणु
	काष्ठा cdns3_usb_regs __iomem *regs = priv_dev->regs;
	u32 reg;

	cdns3_ep0_config(priv_dev);

	/* enable पूर्णांकerrupts क्रम endpoपूर्णांक 0 (in and out) */
	ग_लिखोl(EP_IEN_EP_OUT0 | EP_IEN_EP_IN0, &regs->ep_ien);

	/*
	 * Driver needs to modअगरy LFPS minimal U1 Exit समय क्रम DEV_VER_TI_V1
	 * revision of controller.
	 */
	अगर (priv_dev->dev_ver == DEV_VER_TI_V1) अणु
		reg = पढ़ोl(&regs->dbg_link1);

		reg &= ~DBG_LINK1_LFPS_MIN_GEN_U1_EXIT_MASK;
		reg |= DBG_LINK1_LFPS_MIN_GEN_U1_EXIT(0x55) |
		       DBG_LINK1_LFPS_MIN_GEN_U1_EXIT_SET;
		ग_लिखोl(reg, &regs->dbg_link1);
	पूर्ण

	/*
	 * By शेष some platक्रमms has set रक्षित access to memory.
	 * This cause problem with cache, so driver restore non-secure
	 * access to memory.
	 */
	reg = पढ़ोl(&regs->dma_axi_ctrl);
	reg |= DMA_AXI_CTRL_MARPROT(DMA_AXI_CTRL_NON_SECURE) |
	       DMA_AXI_CTRL_MAWPROT(DMA_AXI_CTRL_NON_SECURE);
	ग_लिखोl(reg, &regs->dma_axi_ctrl);

	/* enable generic पूर्णांकerrupt*/
	ग_लिखोl(USB_IEN_INIT, &regs->usb_ien);
	ग_लिखोl(USB_CONF_CLK2OFFDS | USB_CONF_L1DS, &regs->usb_conf);
	/*  keep Fast Access bit */
	ग_लिखोl(PUSB_PWR_FST_REG_ACCESS, &priv_dev->regs->usb_pwr);

	cdns3_configure_dmult(priv_dev, शून्य);
पूर्ण

/**
 * cdns3_gadget_udc_start Gadget start
 * @gadget: gadget object
 * @driver: driver which operates on this gadget
 *
 * Returns 0 on success, error code अन्यथाwhere
 */
अटल पूर्णांक cdns3_gadget_udc_start(काष्ठा usb_gadget *gadget,
				  काष्ठा usb_gadget_driver *driver)
अणु
	काष्ठा cdns3_device *priv_dev = gadget_to_cdns3_device(gadget);
	अचिन्हित दीर्घ flags;
	क्रमागत usb_device_speed max_speed = driver->max_speed;

	spin_lock_irqsave(&priv_dev->lock, flags);
	priv_dev->gadget_driver = driver;

	/* limit speed अगर necessary */
	max_speed = min(driver->max_speed, gadget->max_speed);

	चयन (max_speed) अणु
	हाल USB_SPEED_FULL:
		ग_लिखोl(USB_CONF_SFORCE_FS, &priv_dev->regs->usb_conf);
		ग_लिखोl(USB_CONF_USB3DIS, &priv_dev->regs->usb_conf);
		अवरोध;
	हाल USB_SPEED_HIGH:
		ग_लिखोl(USB_CONF_USB3DIS, &priv_dev->regs->usb_conf);
		अवरोध;
	हाल USB_SPEED_SUPER:
		अवरोध;
	शेष:
		dev_err(priv_dev->dev,
			"invalid maximum_speed parameter %d\n",
			max_speed);
		fallthrough;
	हाल USB_SPEED_UNKNOWN:
		/* शेष to superspeed */
		max_speed = USB_SPEED_SUPER;
		अवरोध;
	पूर्ण

	cdns3_gadget_config(priv_dev);
	spin_unlock_irqrestore(&priv_dev->lock, flags);
	वापस 0;
पूर्ण

/**
 * cdns3_gadget_udc_stop Stops gadget
 * @gadget: gadget object
 *
 * Returns 0
 */
अटल पूर्णांक cdns3_gadget_udc_stop(काष्ठा usb_gadget *gadget)
अणु
	काष्ठा cdns3_device *priv_dev = gadget_to_cdns3_device(gadget);
	काष्ठा cdns3_endpoपूर्णांक *priv_ep;
	u32 bEndpoपूर्णांकAddress;
	काष्ठा usb_ep *ep;
	पूर्णांक val;

	priv_dev->gadget_driver = शून्य;

	priv_dev->onchip_used_size = 0;
	priv_dev->out_mem_is_allocated = 0;
	priv_dev->gadget.speed = USB_SPEED_UNKNOWN;

	list_क्रम_each_entry(ep, &priv_dev->gadget.ep_list, ep_list) अणु
		priv_ep = ep_to_cdns3_ep(ep);
		bEndpoपूर्णांकAddress = priv_ep->num | priv_ep->dir;
		cdns3_select_ep(priv_dev, bEndpoपूर्णांकAddress);
		ग_लिखोl(EP_CMD_EPRST, &priv_dev->regs->ep_cmd);
		पढ़ोl_poll_समयout_atomic(&priv_dev->regs->ep_cmd, val,
					  !(val & EP_CMD_EPRST), 1, 100);

		priv_ep->flags &= ~EP_CLAIMED;
	पूर्ण

	/* disable पूर्णांकerrupt क्रम device */
	ग_लिखोl(0, &priv_dev->regs->usb_ien);
	ग_लिखोl(0, &priv_dev->regs->usb_pwr);
	ग_लिखोl(USB_CONF_DEVDS, &priv_dev->regs->usb_conf);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा usb_gadget_ops cdns3_gadget_ops = अणु
	.get_frame = cdns3_gadget_get_frame,
	.wakeup = cdns3_gadget_wakeup,
	.set_selfघातered = cdns3_gadget_set_selfघातered,
	.pullup = cdns3_gadget_pullup,
	.udc_start = cdns3_gadget_udc_start,
	.udc_stop = cdns3_gadget_udc_stop,
	.match_ep = cdns3_gadget_match_ep,
पूर्ण;

अटल व्योम cdns3_मुक्त_all_eps(काष्ठा cdns3_device *priv_dev)
अणु
	पूर्णांक i;

	/* ep0 OUT poपूर्णांक to ep0 IN. */
	priv_dev->eps[16] = शून्य;

	क्रम (i = 0; i < CDNS3_ENDPOINTS_MAX_COUNT; i++)
		अगर (priv_dev->eps[i]) अणु
			cdns3_मुक्त_trb_pool(priv_dev->eps[i]);
			devm_kमुक्त(priv_dev->dev, priv_dev->eps[i]);
		पूर्ण
पूर्ण

/**
 * cdns3_init_eps Initializes software endpoपूर्णांकs of gadget
 * @priv_dev: extended gadget object
 *
 * Returns 0 on success, error code अन्यथाwhere
 */
अटल पूर्णांक cdns3_init_eps(काष्ठा cdns3_device *priv_dev)
अणु
	u32 ep_enabled_reg, iso_ep_reg;
	काष्ठा cdns3_endpoपूर्णांक *priv_ep;
	पूर्णांक ep_dir, ep_number;
	u32 ep_mask;
	पूर्णांक ret = 0;
	पूर्णांक i;

	/* Read it from USB_CAP3 to USB_CAP5 */
	ep_enabled_reg = पढ़ोl(&priv_dev->regs->usb_cap3);
	iso_ep_reg = पढ़ोl(&priv_dev->regs->usb_cap4);

	dev_dbg(priv_dev->dev, "Initializing non-zero endpoints\n");

	क्रम (i = 0; i < CDNS3_ENDPOINTS_MAX_COUNT; i++) अणु
		ep_dir = i >> 4;	/* i भाग 16 */
		ep_number = i & 0xF;	/* i % 16 */
		ep_mask = BIT(i);

		अगर (!(ep_enabled_reg & ep_mask))
			जारी;

		अगर (ep_dir && !ep_number) अणु
			priv_dev->eps[i] = priv_dev->eps[0];
			जारी;
		पूर्ण

		priv_ep = devm_kzalloc(priv_dev->dev, माप(*priv_ep),
				       GFP_KERNEL);
		अगर (!priv_ep)
			जाओ err;

		/* set parent of endpoपूर्णांक object */
		priv_ep->cdns3_dev = priv_dev;
		priv_dev->eps[i] = priv_ep;
		priv_ep->num = ep_number;
		priv_ep->dir = ep_dir ? USB_सूची_IN : USB_सूची_OUT;

		अगर (!ep_number) अणु
			ret = cdns3_init_ep0(priv_dev, priv_ep);
			अगर (ret) अणु
				dev_err(priv_dev->dev, "Failed to init ep0\n");
				जाओ err;
			पूर्ण
		पूर्ण अन्यथा अणु
			snम_लिखो(priv_ep->name, माप(priv_ep->name), "ep%d%s",
				 ep_number, !!ep_dir ? "in" : "out");
			priv_ep->endpoपूर्णांक.name = priv_ep->name;

			usb_ep_set_maxpacket_limit(&priv_ep->endpoपूर्णांक,
						   CDNS3_EP_MAX_PACKET_LIMIT);
			priv_ep->endpoपूर्णांक.max_streams = CDNS3_EP_MAX_STREAMS;
			priv_ep->endpoपूर्णांक.ops = &cdns3_gadget_ep_ops;
			अगर (ep_dir)
				priv_ep->endpoपूर्णांक.caps.dir_in = 1;
			अन्यथा
				priv_ep->endpoपूर्णांक.caps.dir_out = 1;

			अगर (iso_ep_reg & ep_mask)
				priv_ep->endpoपूर्णांक.caps.type_iso = 1;

			priv_ep->endpoपूर्णांक.caps.type_bulk = 1;
			priv_ep->endpoपूर्णांक.caps.type_पूर्णांक = 1;

			list_add_tail(&priv_ep->endpoपूर्णांक.ep_list,
				      &priv_dev->gadget.ep_list);
		पूर्ण

		priv_ep->flags = 0;

		dev_dbg(priv_dev->dev, "Initialized  %s support: %s %s\n",
			 priv_ep->name,
			 priv_ep->endpoपूर्णांक.caps.type_bulk ? "BULK, INT" : "",
			 priv_ep->endpoपूर्णांक.caps.type_iso ? "ISO" : "");

		INIT_LIST_HEAD(&priv_ep->pending_req_list);
		INIT_LIST_HEAD(&priv_ep->deferred_req_list);
		INIT_LIST_HEAD(&priv_ep->wa2_descmiss_req_list);
	पूर्ण

	वापस 0;
err:
	cdns3_मुक्त_all_eps(priv_dev);
	वापस -ENOMEM;
पूर्ण

अटल व्योम cdns3_gadget_release(काष्ठा device *dev)
अणु
	काष्ठा cdns3_device *priv_dev = container_of(dev,
			काष्ठा cdns3_device, gadget.dev);

	kमुक्त(priv_dev);
पूर्ण

अटल व्योम cdns3_gadget_निकास(काष्ठा cdns *cdns)
अणु
	काष्ठा cdns3_device *priv_dev;

	priv_dev = cdns->gadget_dev;


	pm_runसमय_mark_last_busy(cdns->dev);
	pm_runसमय_put_स्वतःsuspend(cdns->dev);

	usb_del_gadget(&priv_dev->gadget);
	devm_मुक्त_irq(cdns->dev, cdns->dev_irq, priv_dev);

	cdns3_मुक्त_all_eps(priv_dev);

	जबतक (!list_empty(&priv_dev->aligned_buf_list)) अणु
		काष्ठा cdns3_aligned_buf *buf;

		buf = cdns3_next_align_buf(&priv_dev->aligned_buf_list);
		dma_मुक्त_noncoherent(priv_dev->sysdev, buf->size,
				  buf->buf,
				  buf->dma,
				  buf->dir);

		list_del(&buf->list);
		kमुक्त(buf);
	पूर्ण

	dma_मुक्त_coherent(priv_dev->sysdev, 8, priv_dev->setup_buf,
			  priv_dev->setup_dma);
	dma_pool_destroy(priv_dev->eps_dma_pool);

	kमुक्त(priv_dev->zlp_buf);
	usb_put_gadget(&priv_dev->gadget);
	cdns->gadget_dev = शून्य;
	cdns_drd_gadget_off(cdns);
पूर्ण

अटल पूर्णांक cdns3_gadget_start(काष्ठा cdns *cdns)
अणु
	काष्ठा cdns3_device *priv_dev;
	u32 max_speed;
	पूर्णांक ret;

	priv_dev = kzalloc(माप(*priv_dev), GFP_KERNEL);
	अगर (!priv_dev)
		वापस -ENOMEM;

	usb_initialize_gadget(cdns->dev, &priv_dev->gadget,
			cdns3_gadget_release);
	cdns->gadget_dev = priv_dev;
	priv_dev->sysdev = cdns->dev;
	priv_dev->dev = cdns->dev;
	priv_dev->regs = cdns->dev_regs;

	device_property_पढ़ो_u16(priv_dev->dev, "cdns,on-chip-buff-size",
				 &priv_dev->onchip_buffers);

	अगर (priv_dev->onchip_buffers <=  0) अणु
		u32 reg = पढ़ोl(&priv_dev->regs->usb_cap2);

		priv_dev->onchip_buffers = USB_CAP2_ACTUAL_MEM_SIZE(reg);
	पूर्ण

	अगर (!priv_dev->onchip_buffers)
		priv_dev->onchip_buffers = 256;

	max_speed = usb_get_maximum_speed(cdns->dev);

	/* Check the maximum_speed parameter */
	चयन (max_speed) अणु
	हाल USB_SPEED_FULL:
	हाल USB_SPEED_HIGH:
	हाल USB_SPEED_SUPER:
		अवरोध;
	शेष:
		dev_err(cdns->dev, "invalid maximum_speed parameter %d\n",
			max_speed);
		fallthrough;
	हाल USB_SPEED_UNKNOWN:
		/* शेष to superspeed */
		max_speed = USB_SPEED_SUPER;
		अवरोध;
	पूर्ण

	/* fill gadget fields */
	priv_dev->gadget.max_speed = max_speed;
	priv_dev->gadget.speed = USB_SPEED_UNKNOWN;
	priv_dev->gadget.ops = &cdns3_gadget_ops;
	priv_dev->gadget.name = "usb-ss-gadget";
	priv_dev->gadget.quirk_aव्योमs_skb_reserve = 1;
	priv_dev->gadget.irq = cdns->dev_irq;

	spin_lock_init(&priv_dev->lock);
	INIT_WORK(&priv_dev->pending_status_wq,
		  cdns3_pending_setup_status_handler);

	INIT_WORK(&priv_dev->aligned_buf_wq,
		  cdns3_मुक्त_aligned_request_buf);

	/* initialize endpoपूर्णांक container */
	INIT_LIST_HEAD(&priv_dev->gadget.ep_list);
	INIT_LIST_HEAD(&priv_dev->aligned_buf_list);
	priv_dev->eps_dma_pool = dma_pool_create("cdns3_eps_dma_pool",
						 priv_dev->sysdev,
						 TRB_RING_SIZE, 8, 0);
	अगर (!priv_dev->eps_dma_pool) अणु
		dev_err(priv_dev->dev, "Failed to create TRB dma pool\n");
		ret = -ENOMEM;
		जाओ err1;
	पूर्ण

	ret = cdns3_init_eps(priv_dev);
	अगर (ret) अणु
		dev_err(priv_dev->dev, "Failed to create endpoints\n");
		जाओ err1;
	पूर्ण

	/* allocate memory क्रम setup packet buffer */
	priv_dev->setup_buf = dma_alloc_coherent(priv_dev->sysdev, 8,
						 &priv_dev->setup_dma, GFP_DMA);
	अगर (!priv_dev->setup_buf) अणु
		ret = -ENOMEM;
		जाओ err2;
	पूर्ण

	priv_dev->dev_ver = पढ़ोl(&priv_dev->regs->usb_cap6);

	dev_dbg(priv_dev->dev, "Device Controller version: %08x\n",
		पढ़ोl(&priv_dev->regs->usb_cap6));
	dev_dbg(priv_dev->dev, "USB Capabilities:: %08x\n",
		पढ़ोl(&priv_dev->regs->usb_cap1));
	dev_dbg(priv_dev->dev, "On-Chip memory configuration: %08x\n",
		पढ़ोl(&priv_dev->regs->usb_cap2));

	priv_dev->dev_ver = GET_DEV_BASE_VERSION(priv_dev->dev_ver);
	अगर (priv_dev->dev_ver >= DEV_VER_V2)
		priv_dev->gadget.sg_supported = 1;

	priv_dev->zlp_buf = kzalloc(CDNS3_EP_ZLP_BUF_SIZE, GFP_KERNEL);
	अगर (!priv_dev->zlp_buf) अणु
		ret = -ENOMEM;
		जाओ err3;
	पूर्ण

	/* add USB gadget device */
	ret = usb_add_gadget(&priv_dev->gadget);
	अगर (ret < 0) अणु
		dev_err(priv_dev->dev, "Failed to add gadget\n");
		जाओ err4;
	पूर्ण

	वापस 0;
err4:
	kमुक्त(priv_dev->zlp_buf);
err3:
	dma_मुक्त_coherent(priv_dev->sysdev, 8, priv_dev->setup_buf,
			  priv_dev->setup_dma);
err2:
	cdns3_मुक्त_all_eps(priv_dev);
err1:
	dma_pool_destroy(priv_dev->eps_dma_pool);

	usb_put_gadget(&priv_dev->gadget);
	cdns->gadget_dev = शून्य;
	वापस ret;
पूर्ण

अटल पूर्णांक __cdns3_gadget_init(काष्ठा cdns *cdns)
अणु
	पूर्णांक ret = 0;

	/* Ensure 32-bit DMA Mask in हाल we चयनed back from Host mode */
	ret = dma_set_mask_and_coherent(cdns->dev, DMA_BIT_MASK(32));
	अगर (ret) अणु
		dev_err(cdns->dev, "Failed to set dma mask: %d\n", ret);
		वापस ret;
	पूर्ण

	cdns_drd_gadget_on(cdns);
	pm_runसमय_get_sync(cdns->dev);

	ret = cdns3_gadget_start(cdns);
	अगर (ret) अणु
		pm_runसमय_put_sync(cdns->dev);
		वापस ret;
	पूर्ण

	/*
	 * Because पूर्णांकerrupt line can be shared with other components in
	 * driver it can't use IRQF_ONESHOT flag here.
	 */
	ret = devm_request_thपढ़ोed_irq(cdns->dev, cdns->dev_irq,
					cdns3_device_irq_handler,
					cdns3_device_thपढ़ो_irq_handler,
					IRQF_SHARED, dev_name(cdns->dev),
					cdns->gadget_dev);

	अगर (ret)
		जाओ err0;

	वापस 0;
err0:
	cdns3_gadget_निकास(cdns);
	वापस ret;
पूर्ण

अटल पूर्णांक cdns3_gadget_suspend(काष्ठा cdns *cdns, bool करो_wakeup)
__must_hold(&cdns->lock)
अणु
	काष्ठा cdns3_device *priv_dev = cdns->gadget_dev;

	spin_unlock(&cdns->lock);
	cdns3_disconnect_gadget(priv_dev);
	spin_lock(&cdns->lock);

	priv_dev->gadget.speed = USB_SPEED_UNKNOWN;
	usb_gadget_set_state(&priv_dev->gadget, USB_STATE_NOTATTACHED);
	cdns3_hw_reset_eps_config(priv_dev);

	/* disable पूर्णांकerrupt क्रम device */
	ग_लिखोl(0, &priv_dev->regs->usb_ien);

	वापस 0;
पूर्ण

अटल पूर्णांक cdns3_gadget_resume(काष्ठा cdns *cdns, bool hibernated)
अणु
	काष्ठा cdns3_device *priv_dev = cdns->gadget_dev;

	अगर (!priv_dev->gadget_driver)
		वापस 0;

	cdns3_gadget_config(priv_dev);
	अगर (hibernated)
		ग_लिखोl(USB_CONF_DEVEN, &priv_dev->regs->usb_conf);

	वापस 0;
पूर्ण

/**
 * cdns3_gadget_init - initialize device काष्ठाure
 *
 * @cdns: cdns instance
 *
 * This function initializes the gadget.
 */
पूर्णांक cdns3_gadget_init(काष्ठा cdns *cdns)
अणु
	काष्ठा cdns_role_driver *rdrv;

	rdrv = devm_kzalloc(cdns->dev, माप(*rdrv), GFP_KERNEL);
	अगर (!rdrv)
		वापस -ENOMEM;

	rdrv->start	= __cdns3_gadget_init;
	rdrv->stop	= cdns3_gadget_निकास;
	rdrv->suspend	= cdns3_gadget_suspend;
	rdrv->resume	= cdns3_gadget_resume;
	rdrv->state	= CDNS_ROLE_STATE_INACTIVE;
	rdrv->name	= "gadget";
	cdns->roles[USB_ROLE_DEVICE] = rdrv;

	वापस 0;
पूर्ण
