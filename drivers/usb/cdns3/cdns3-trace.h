<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * USBSS device controller driver.
 * Trace support header file.
 *
 * Copyright (C) 2018-2019 Cadence.
 *
 * Author: Pawel Laszczak <pawell@cadence.com>
 */

#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM cdns3

#अगर !defined(__LINUX_CDNS3_TRACE) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा __LINUX_CDNS3_TRACE

#समावेश <linux/types.h>
#समावेश <linux/tracepoपूर्णांक.h>
#समावेश <यंत्र/byteorder.h>
#समावेश <linux/usb/ch9.h>
#समावेश "core.h"
#समावेश "cdns3-gadget.h"
#समावेश "cdns3-debug.h"

#घोषणा CDNS3_MSG_MAX	500

TRACE_EVENT(cdns3_halt,
	TP_PROTO(काष्ठा cdns3_endpoपूर्णांक *ep_priv, u8 halt, u8 flush),
	TP_ARGS(ep_priv, halt, flush),
	TP_STRUCT__entry(
		__string(name, ep_priv->name)
		__field(u8, halt)
		__field(u8, flush)
	),
	TP_fast_assign(
		__assign_str(name, ep_priv->name);
		__entry->halt = halt;
		__entry->flush = flush;
	),
	TP_prपूर्णांकk("Halt %s for %s: %s", __entry->flush ? " and flush" : "",
		  __get_str(name), __entry->halt ? "set" : "cleared")
);

TRACE_EVENT(cdns3_wa1,
	TP_PROTO(काष्ठा cdns3_endpoपूर्णांक *ep_priv, अक्षर *msg),
	TP_ARGS(ep_priv, msg),
	TP_STRUCT__entry(
		__string(ep_name, ep_priv->name)
		__string(msg, msg)
	),
	TP_fast_assign(
		__assign_str(ep_name, ep_priv->name);
		__assign_str(msg, msg);
	),
	TP_prपूर्णांकk("WA1: %s %s", __get_str(ep_name), __get_str(msg))
);

TRACE_EVENT(cdns3_wa2,
	TP_PROTO(काष्ठा cdns3_endpoपूर्णांक *ep_priv, अक्षर *msg),
	TP_ARGS(ep_priv, msg),
	TP_STRUCT__entry(
		__string(ep_name, ep_priv->name)
		__string(msg, msg)
	),
	TP_fast_assign(
		__assign_str(ep_name, ep_priv->name);
		__assign_str(msg, msg);
	),
	TP_prपूर्णांकk("WA2: %s %s", __get_str(ep_name), __get_str(msg))
);

DECLARE_EVENT_CLASS(cdns3_log_करोorbell,
	TP_PROTO(स्थिर अक्षर *ep_name, u32 ep_trbaddr),
	TP_ARGS(ep_name, ep_trbaddr),
	TP_STRUCT__entry(
		__string(name, ep_name)
		__field(u32, ep_trbaddr)
	),
	TP_fast_assign(
		__assign_str(name, ep_name);
		__entry->ep_trbaddr = ep_trbaddr;
	),
	TP_prपूर्णांकk("%s, ep_trbaddr %08x", __get_str(name),
		  __entry->ep_trbaddr)
);

DEFINE_EVENT(cdns3_log_करोorbell, cdns3_करोorbell_ep0,
	TP_PROTO(स्थिर अक्षर *ep_name, u32 ep_trbaddr),
	TP_ARGS(ep_name, ep_trbaddr)
);

DEFINE_EVENT(cdns3_log_करोorbell, cdns3_करोorbell_epx,
	TP_PROTO(स्थिर अक्षर *ep_name, u32 ep_trbaddr),
	TP_ARGS(ep_name, ep_trbaddr)
);

DECLARE_EVENT_CLASS(cdns3_log_usb_irq,
	TP_PROTO(काष्ठा cdns3_device *priv_dev, u32 usb_ists),
	TP_ARGS(priv_dev, usb_ists),
	TP_STRUCT__entry(
		__field(क्रमागत usb_device_speed, speed)
		__field(u32, usb_ists)
		__dynamic_array(अक्षर, str, CDNS3_MSG_MAX)
	),
	TP_fast_assign(
		__entry->speed = cdns3_get_speed(priv_dev);
		__entry->usb_ists = usb_ists;
	),
	TP_prपूर्णांकk("%s", cdns3_decode_usb_irq(__get_str(str), __entry->speed,
					     __entry->usb_ists))
);

DEFINE_EVENT(cdns3_log_usb_irq, cdns3_usb_irq,
	TP_PROTO(काष्ठा cdns3_device *priv_dev, u32 usb_ists),
	TP_ARGS(priv_dev, usb_ists)
);

DECLARE_EVENT_CLASS(cdns3_log_epx_irq,
	TP_PROTO(काष्ठा cdns3_device *priv_dev, काष्ठा cdns3_endpoपूर्णांक *priv_ep),
	TP_ARGS(priv_dev, priv_ep),
	TP_STRUCT__entry(
		__string(ep_name, priv_ep->name)
		__field(u32, ep_sts)
		__field(u32, ep_traddr)
		__field(u32, ep_last_sid)
		__field(u32, use_streams)
		__dynamic_array(अक्षर, str, CDNS3_MSG_MAX)
	),
	TP_fast_assign(
		__assign_str(ep_name, priv_ep->name);
		__entry->ep_sts = पढ़ोl(&priv_dev->regs->ep_sts);
		__entry->ep_traddr = पढ़ोl(&priv_dev->regs->ep_traddr);
		__entry->ep_last_sid = priv_ep->last_stream_id;
		__entry->use_streams = priv_ep->use_streams;
	),
	TP_prपूर्णांकk("%s, ep_traddr: %08x ep_last_sid: %08x use_streams: %d",
		  cdns3_decode_epx_irq(__get_str(str),
				       __get_str(ep_name),
				       __entry->ep_sts),
		  __entry->ep_traddr,
		  __entry->ep_last_sid,
		  __entry->use_streams)
);

DEFINE_EVENT(cdns3_log_epx_irq, cdns3_epx_irq,
	TP_PROTO(काष्ठा cdns3_device *priv_dev, काष्ठा cdns3_endpoपूर्णांक *priv_ep),
	TP_ARGS(priv_dev, priv_ep)
);

DECLARE_EVENT_CLASS(cdns3_log_ep0_irq,
	TP_PROTO(काष्ठा cdns3_device *priv_dev,  u32 ep_sts),
	TP_ARGS(priv_dev, ep_sts),
	TP_STRUCT__entry(
		__field(पूर्णांक, ep_dir)
		__field(u32, ep_sts)
		__dynamic_array(अक्षर, str, CDNS3_MSG_MAX)
	),
	TP_fast_assign(
		__entry->ep_dir = priv_dev->selected_ep;
		__entry->ep_sts = ep_sts;
	),
	TP_prपूर्णांकk("%s", cdns3_decode_ep0_irq(__get_str(str),
					     __entry->ep_dir,
					     __entry->ep_sts))
);

DEFINE_EVENT(cdns3_log_ep0_irq, cdns3_ep0_irq,
	TP_PROTO(काष्ठा cdns3_device *priv_dev, u32 ep_sts),
	TP_ARGS(priv_dev, ep_sts)
);

DECLARE_EVENT_CLASS(cdns3_log_ctrl,
	TP_PROTO(काष्ठा usb_ctrlrequest *ctrl),
	TP_ARGS(ctrl),
	TP_STRUCT__entry(
		__field(u8, bRequestType)
		__field(u8, bRequest)
		__field(u16, wValue)
		__field(u16, wIndex)
		__field(u16, wLength)
		__dynamic_array(अक्षर, str, CDNS3_MSG_MAX)
	),
	TP_fast_assign(
		__entry->bRequestType = ctrl->bRequestType;
		__entry->bRequest = ctrl->bRequest;
		__entry->wValue = le16_to_cpu(ctrl->wValue);
		__entry->wIndex = le16_to_cpu(ctrl->wIndex);
		__entry->wLength = le16_to_cpu(ctrl->wLength);
	),
	TP_prपूर्णांकk("%s", usb_decode_ctrl(__get_str(str), CDNS3_MSG_MAX,
					__entry->bRequestType,
					__entry->bRequest, __entry->wValue,
					__entry->wIndex, __entry->wLength)
	)
);

DEFINE_EVENT(cdns3_log_ctrl, cdns3_ctrl_req,
	TP_PROTO(काष्ठा usb_ctrlrequest *ctrl),
	TP_ARGS(ctrl)
);

DECLARE_EVENT_CLASS(cdns3_log_request,
	TP_PROTO(काष्ठा cdns3_request *req),
	TP_ARGS(req),
	TP_STRUCT__entry(
		__string(name, req->priv_ep->name)
		__field(काष्ठा cdns3_request *, req)
		__field(व्योम *, buf)
		__field(अचिन्हित पूर्णांक, actual)
		__field(अचिन्हित पूर्णांक, length)
		__field(पूर्णांक, status)
		__field(पूर्णांक, zero)
		__field(पूर्णांक, लघु_not_ok)
		__field(पूर्णांक, no_पूर्णांकerrupt)
		__field(पूर्णांक, start_trb)
		__field(पूर्णांक, end_trb)
		__field(पूर्णांक, flags)
		__field(अचिन्हित पूर्णांक, stream_id)
	),
	TP_fast_assign(
		__assign_str(name, req->priv_ep->name);
		__entry->req = req;
		__entry->buf = req->request.buf;
		__entry->actual = req->request.actual;
		__entry->length = req->request.length;
		__entry->status = req->request.status;
		__entry->zero = req->request.zero;
		__entry->लघु_not_ok = req->request.लघु_not_ok;
		__entry->no_पूर्णांकerrupt = req->request.no_पूर्णांकerrupt;
		__entry->start_trb = req->start_trb;
		__entry->end_trb = req->end_trb;
		__entry->flags = req->flags;
		__entry->stream_id = req->request.stream_id;
	),
	TP_prपूर्णांकk("%s: req: %p, req buff %p, length: %u/%u %s%s%s, status: %d,"
		  " trb: [start:%d, end:%d], flags:%x SID: %u",
		__get_str(name), __entry->req, __entry->buf, __entry->actual,
		__entry->length,
		__entry->zero ? "Z" : "z",
		__entry->लघु_not_ok ? "S" : "s",
		__entry->no_पूर्णांकerrupt ? "I" : "i",
		__entry->status,
		__entry->start_trb,
		__entry->end_trb,
		__entry->flags,
		__entry->stream_id
	)
);

DEFINE_EVENT(cdns3_log_request, cdns3_alloc_request,
	TP_PROTO(काष्ठा cdns3_request *req),
	TP_ARGS(req)
);

DEFINE_EVENT(cdns3_log_request, cdns3_मुक्त_request,
	TP_PROTO(काष्ठा cdns3_request *req),
	TP_ARGS(req)
);

DEFINE_EVENT(cdns3_log_request, cdns3_ep_queue,
	TP_PROTO(काष्ठा cdns3_request *req),
	TP_ARGS(req)
);

DEFINE_EVENT(cdns3_log_request, cdns3_ep_dequeue,
	TP_PROTO(काष्ठा cdns3_request *req),
	TP_ARGS(req)
);

DEFINE_EVENT(cdns3_log_request, cdns3_gadget_giveback,
	TP_PROTO(काष्ठा cdns3_request *req),
	TP_ARGS(req)
);

TRACE_EVENT(cdns3_ep0_queue,
	TP_PROTO(काष्ठा cdns3_device *dev_priv, काष्ठा usb_request *request),
	TP_ARGS(dev_priv, request),
	TP_STRUCT__entry(
		__field(पूर्णांक, dir)
		__field(पूर्णांक, length)
	),
	TP_fast_assign(
		__entry->dir = dev_priv->ep0_data_dir;
		__entry->length = request->length;
	),
	TP_prपूर्णांकk("Queue to ep0%s length: %u", __entry->dir ? "in" : "out",
		  __entry->length)
);

DECLARE_EVENT_CLASS(cdns3_stream_split_transfer_len,
	TP_PROTO(काष्ठा cdns3_request *req),
	TP_ARGS(req),
	TP_STRUCT__entry(
		__string(name, req->priv_ep->name)
		__field(काष्ठा cdns3_request *, req)
		__field(अचिन्हित पूर्णांक, length)
		__field(अचिन्हित पूर्णांक, actual)
		__field(अचिन्हित पूर्णांक, stream_id)
	),
	TP_fast_assign(
		__assign_str(name, req->priv_ep->name);
		__entry->req = req;
		__entry->actual = req->request.length;
		__entry->length = req->request.actual;
		__entry->stream_id = req->request.stream_id;
	),
	TP_prपूर्णांकk("%s: req: %p,request length: %u actual length: %u  SID: %u",
		  __get_str(name), __entry->req, __entry->length,
		  __entry->actual, __entry->stream_id)
);

DEFINE_EVENT(cdns3_stream_split_transfer_len, cdns3_stream_transfer_split,
	     TP_PROTO(काष्ठा cdns3_request *req),
	     TP_ARGS(req)
);

DEFINE_EVENT(cdns3_stream_split_transfer_len,
	     cdns3_stream_transfer_split_next_part,
	     TP_PROTO(काष्ठा cdns3_request *req),
	     TP_ARGS(req)
);

DECLARE_EVENT_CLASS(cdns3_log_aligned_request,
	TP_PROTO(काष्ठा cdns3_request *priv_req),
	TP_ARGS(priv_req),
	TP_STRUCT__entry(
		__string(name, priv_req->priv_ep->name)
		__field(काष्ठा usb_request *, req)
		__field(व्योम *, buf)
		__field(dma_addr_t, dma)
		__field(व्योम *, aligned_buf)
		__field(dma_addr_t, aligned_dma)
		__field(u32, aligned_buf_size)
	),
	TP_fast_assign(
		__assign_str(name, priv_req->priv_ep->name);
		__entry->req = &priv_req->request;
		__entry->buf = priv_req->request.buf;
		__entry->dma = priv_req->request.dma;
		__entry->aligned_buf = priv_req->aligned_buf->buf;
		__entry->aligned_dma = priv_req->aligned_buf->dma;
		__entry->aligned_buf_size = priv_req->aligned_buf->size;
	),
	TP_prपूर्णांकk("%s: req: %p, req buf %p, dma %pad a_buf %p a_dma %pad, size %d",
		__get_str(name), __entry->req, __entry->buf, &__entry->dma,
		__entry->aligned_buf, &__entry->aligned_dma,
		__entry->aligned_buf_size
	)
);

DEFINE_EVENT(cdns3_log_aligned_request, cdns3_मुक्त_aligned_request,
	TP_PROTO(काष्ठा cdns3_request *req),
	TP_ARGS(req)
);

DEFINE_EVENT(cdns3_log_aligned_request, cdns3_prepare_aligned_request,
	TP_PROTO(काष्ठा cdns3_request *req),
	TP_ARGS(req)
);

DECLARE_EVENT_CLASS(cdns3_log_map_request,
	TP_PROTO(काष्ठा cdns3_request *priv_req),
	TP_ARGS(priv_req),
	TP_STRUCT__entry(
		__string(name, priv_req->priv_ep->name)
		__field(काष्ठा usb_request *, req)
		__field(व्योम *, buf)
		__field(dma_addr_t, dma)
	),
	TP_fast_assign(
		__assign_str(name, priv_req->priv_ep->name);
		__entry->req = &priv_req->request;
		__entry->buf = priv_req->request.buf;
		__entry->dma = priv_req->request.dma;
	),
	TP_prपूर्णांकk("%s: req: %p, req buf %p, dma %p",
		  __get_str(name), __entry->req, __entry->buf, &__entry->dma
	)
);
DEFINE_EVENT(cdns3_log_map_request, cdns3_map_request,
	     TP_PROTO(काष्ठा cdns3_request *req),
	     TP_ARGS(req)
);
DEFINE_EVENT(cdns3_log_map_request, cdns3_mapped_request,
	     TP_PROTO(काष्ठा cdns3_request *req),
	     TP_ARGS(req)
);

DECLARE_EVENT_CLASS(cdns3_log_trb,
	TP_PROTO(काष्ठा cdns3_endpoपूर्णांक *priv_ep, काष्ठा cdns3_trb *trb),
	TP_ARGS(priv_ep, trb),
	TP_STRUCT__entry(
		__string(name, priv_ep->name)
		__field(काष्ठा cdns3_trb *, trb)
		__field(u32, buffer)
		__field(u32, length)
		__field(u32, control)
		__field(u32, type)
		__field(अचिन्हित पूर्णांक, last_stream_id)
	),
	TP_fast_assign(
		__assign_str(name, priv_ep->name);
		__entry->trb = trb;
		__entry->buffer = le32_to_cpu(trb->buffer);
		__entry->length = le32_to_cpu(trb->length);
		__entry->control = le32_to_cpu(trb->control);
		__entry->type = usb_endpoपूर्णांक_type(priv_ep->endpoपूर्णांक.desc);
		__entry->last_stream_id = priv_ep->last_stream_id;
	),
	TP_prपूर्णांकk("%s: trb %p, dma buf: 0x%08x, size: %ld, burst: %d ctrl: 0x%08x (%s%s%s%s%s%s%s) SID:%lu LAST_SID:%u",
		__get_str(name), __entry->trb, __entry->buffer,
		TRB_LEN(__entry->length),
		(u8)TRB_BURST_LEN_GET(__entry->length),
		__entry->control,
		__entry->control & TRB_CYCLE ? "C=1, " : "C=0, ",
		__entry->control & TRB_TOGGLE ? "T=1, " : "T=0, ",
		__entry->control & TRB_ISP ? "ISP, " : "",
		__entry->control & TRB_FIFO_MODE ? "FIFO, " : "",
		__entry->control & TRB_CHAIN ? "CHAIN, " : "",
		__entry->control & TRB_IOC ? "IOC, " : "",
		TRB_FIELD_TO_TYPE(__entry->control) == TRB_NORMAL ? "Normal" : "LINK",
		TRB_FIELD_TO_STREAMID(__entry->control),
		__entry->last_stream_id
	)
);

DEFINE_EVENT(cdns3_log_trb, cdns3_prepare_trb,
	TP_PROTO(काष्ठा cdns3_endpoपूर्णांक *priv_ep, काष्ठा cdns3_trb *trb),
	TP_ARGS(priv_ep, trb)
);

DEFINE_EVENT(cdns3_log_trb, cdns3_complete_trb,
	TP_PROTO(काष्ठा cdns3_endpoपूर्णांक *priv_ep, काष्ठा cdns3_trb *trb),
	TP_ARGS(priv_ep, trb)
);

DECLARE_EVENT_CLASS(cdns3_log_ring,
	TP_PROTO(काष्ठा cdns3_endpoपूर्णांक *priv_ep),
	TP_ARGS(priv_ep),
	TP_STRUCT__entry(
		__dynamic_array(u8, ring, TRB_RING_SIZE)
		__dynamic_array(u8, priv_ep, माप(काष्ठा cdns3_endpoपूर्णांक))
		__dynamic_array(अक्षर, buffer,
				(TRBS_PER_SEGMENT * 65) + CDNS3_MSG_MAX)
	),
	TP_fast_assign(
		स_नकल(__get_dynamic_array(priv_ep), priv_ep,
		       माप(काष्ठा cdns3_endpoपूर्णांक));
		स_नकल(__get_dynamic_array(ring), priv_ep->trb_pool,
		       TRB_RING_SIZE);
	),

	TP_prपूर्णांकk("%s",
		  cdns3_dbg_ring((काष्ठा cdns3_endpoपूर्णांक *)__get_str(priv_ep),
				 (काष्ठा cdns3_trb *)__get_str(ring),
				 __get_str(buffer)))
);

DEFINE_EVENT(cdns3_log_ring, cdns3_ring,
	TP_PROTO(काष्ठा cdns3_endpoपूर्णांक *priv_ep),
	TP_ARGS(priv_ep)
);

DECLARE_EVENT_CLASS(cdns3_log_ep,
	TP_PROTO(काष्ठा cdns3_endpoपूर्णांक *priv_ep),
	TP_ARGS(priv_ep),
	TP_STRUCT__entry(
		__string(name, priv_ep->name)
		__field(अचिन्हित पूर्णांक, maxpacket)
		__field(अचिन्हित पूर्णांक, maxpacket_limit)
		__field(अचिन्हित पूर्णांक, max_streams)
		__field(अचिन्हित पूर्णांक, use_streams)
		__field(अचिन्हित पूर्णांक, maxburst)
		__field(अचिन्हित पूर्णांक, flags)
		__field(अचिन्हित पूर्णांक, dir)
		__field(u8, enqueue)
		__field(u8, dequeue)
	),
	TP_fast_assign(
		__assign_str(name, priv_ep->name);
		__entry->maxpacket = priv_ep->endpoपूर्णांक.maxpacket;
		__entry->maxpacket_limit = priv_ep->endpoपूर्णांक.maxpacket_limit;
		__entry->max_streams = priv_ep->endpoपूर्णांक.max_streams;
		__entry->use_streams = priv_ep->use_streams;
		__entry->maxburst = priv_ep->endpoपूर्णांक.maxburst;
		__entry->flags = priv_ep->flags;
		__entry->dir = priv_ep->dir;
		__entry->enqueue = priv_ep->enqueue;
		__entry->dequeue = priv_ep->dequeue;
	),
	TP_prपूर्णांकk("%s: mps: %d/%d. streams: %d, stream enable: %d, burst: %d, "
		  "enq idx: %d, deq idx: %d, flags %s%s%s%s%s%s%s%s, dir: %s",
		__get_str(name), __entry->maxpacket,
		__entry->maxpacket_limit, __entry->max_streams,
		__entry->use_streams,
		__entry->maxburst, __entry->enqueue,
		__entry->dequeue,
		__entry->flags & EP_ENABLED ? "EN | " : "",
		__entry->flags & EP_STALLED ? "STALLED | " : "",
		__entry->flags & EP_WEDGE ? "WEDGE | " : "",
		__entry->flags & EP_TRANSFER_STARTED ? "STARTED | " : "",
		__entry->flags & EP_UPDATE_EP_TRBADDR ? "UPD TRB | " : "",
		__entry->flags & EP_PENDING_REQUEST ? "REQ PEN | " : "",
		__entry->flags & EP_RING_FULL ? "RING FULL |" : "",
		__entry->flags & EP_CLAIMED ?  "CLAIMED " : "",
		__entry->dir ? "IN" : "OUT"
	)
);

DEFINE_EVENT(cdns3_log_ep, cdns3_gadget_ep_enable,
	TP_PROTO(काष्ठा cdns3_endpoपूर्णांक *priv_ep),
	TP_ARGS(priv_ep)
);

DEFINE_EVENT(cdns3_log_ep, cdns3_gadget_ep_disable,
	TP_PROTO(काष्ठा cdns3_endpoपूर्णांक *priv_ep),
	TP_ARGS(priv_ep)
);

DECLARE_EVENT_CLASS(cdns3_log_request_handled,
	TP_PROTO(काष्ठा cdns3_request *priv_req, पूर्णांक current_index,
		 पूर्णांक handled),
	TP_ARGS(priv_req, current_index, handled),
	TP_STRUCT__entry(
		__field(काष्ठा cdns3_request *, priv_req)
		__field(अचिन्हित पूर्णांक, dma_position)
		__field(अचिन्हित पूर्णांक, handled)
		__field(अचिन्हित पूर्णांक, dequeue_idx)
		__field(अचिन्हित पूर्णांक, enqueue_idx)
		__field(अचिन्हित पूर्णांक, start_trb)
		__field(अचिन्हित पूर्णांक, end_trb)
	),
	TP_fast_assign(
		__entry->priv_req = priv_req;
		__entry->dma_position = current_index;
		__entry->handled = handled;
		__entry->dequeue_idx = priv_req->priv_ep->dequeue;
		__entry->enqueue_idx = priv_req->priv_ep->enqueue;
		__entry->start_trb = priv_req->start_trb;
		__entry->end_trb = priv_req->end_trb;
	),
	TP_prपूर्णांकk("Req: %p %s, DMA pos: %d, ep deq: %d, ep enq: %d,"
		  " start trb: %d, end trb: %d",
		__entry->priv_req,
		__entry->handled ? "handled" : "not handled",
		__entry->dma_position, __entry->dequeue_idx,
		__entry->enqueue_idx, __entry->start_trb,
		__entry->end_trb
	)
);

DEFINE_EVENT(cdns3_log_request_handled, cdns3_request_handled,
	TP_PROTO(काष्ठा cdns3_request *priv_req, पूर्णांक current_index,
		 पूर्णांक handled),
	TP_ARGS(priv_req, current_index, handled)
);
#पूर्ण_अगर /* __LINUX_CDNS3_TRACE */

/* this part must be outside header guard */

#अघोषित TRACE_INCLUDE_PATH
#घोषणा TRACE_INCLUDE_PATH .

#अघोषित TRACE_INCLUDE_खाता
#घोषणा TRACE_INCLUDE_खाता cdns3-trace

#समावेश <trace/define_trace.h>
