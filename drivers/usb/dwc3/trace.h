<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * trace.h - DesignWare USB3 DRD Controller Trace Support
 *
 * Copyright (C) 2014 Texas Instruments Incorporated - https://www.ti.com
 *
 * Author: Felipe Balbi <balbi@ti.com>
 */

#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM dwc3

#अगर !defined(__DWC3_TRACE_H) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा __DWC3_TRACE_H

#समावेश <linux/types.h>
#समावेश <linux/tracepoपूर्णांक.h>
#समावेश <यंत्र/byteorder.h>
#समावेश "core.h"
#समावेश "debug.h"

DECLARE_EVENT_CLASS(dwc3_log_io,
	TP_PROTO(व्योम *base, u32 offset, u32 value),
	TP_ARGS(base, offset, value),
	TP_STRUCT__entry(
		__field(व्योम *, base)
		__field(u32, offset)
		__field(u32, value)
	),
	TP_fast_assign(
		__entry->base = base;
		__entry->offset = offset;
		__entry->value = value;
	),
	TP_prपूर्णांकk("addr %p offset %04x value %08x",
		__entry->base + __entry->offset,
		__entry->offset,
		__entry->value)
);

DEFINE_EVENT(dwc3_log_io, dwc3_पढ़ोl,
	TP_PROTO(व्योम __iomem *base, u32 offset, u32 value),
	TP_ARGS(base, offset, value)
);

DEFINE_EVENT(dwc3_log_io, dwc3_ग_लिखोl,
	TP_PROTO(व्योम __iomem *base, u32 offset, u32 value),
	TP_ARGS(base, offset, value)
);

DECLARE_EVENT_CLASS(dwc3_log_event,
	TP_PROTO(u32 event, काष्ठा dwc3 *dwc),
	TP_ARGS(event, dwc),
	TP_STRUCT__entry(
		__field(u32, event)
		__field(u32, ep0state)
		__dynamic_array(अक्षर, str, DWC3_MSG_MAX)
	),
	TP_fast_assign(
		__entry->event = event;
		__entry->ep0state = dwc->ep0state;
	),
	TP_prपूर्णांकk("event (%08x): %s", __entry->event,
			dwc3_decode_event(__get_str(str), DWC3_MSG_MAX,
					__entry->event, __entry->ep0state))
);

DEFINE_EVENT(dwc3_log_event, dwc3_event,
	TP_PROTO(u32 event, काष्ठा dwc3 *dwc),
	TP_ARGS(event, dwc)
);

DECLARE_EVENT_CLASS(dwc3_log_ctrl,
	TP_PROTO(काष्ठा usb_ctrlrequest *ctrl),
	TP_ARGS(ctrl),
	TP_STRUCT__entry(
		__field(__u8, bRequestType)
		__field(__u8, bRequest)
		__field(__u16, wValue)
		__field(__u16, wIndex)
		__field(__u16, wLength)
		__dynamic_array(अक्षर, str, DWC3_MSG_MAX)
	),
	TP_fast_assign(
		__entry->bRequestType = ctrl->bRequestType;
		__entry->bRequest = ctrl->bRequest;
		__entry->wValue = le16_to_cpu(ctrl->wValue);
		__entry->wIndex = le16_to_cpu(ctrl->wIndex);
		__entry->wLength = le16_to_cpu(ctrl->wLength);
	),
	TP_prपूर्णांकk("%s", usb_decode_ctrl(__get_str(str), DWC3_MSG_MAX,
					__entry->bRequestType,
					__entry->bRequest, __entry->wValue,
					__entry->wIndex, __entry->wLength)
	)
);

DEFINE_EVENT(dwc3_log_ctrl, dwc3_ctrl_req,
	TP_PROTO(काष्ठा usb_ctrlrequest *ctrl),
	TP_ARGS(ctrl)
);

DECLARE_EVENT_CLASS(dwc3_log_request,
	TP_PROTO(काष्ठा dwc3_request *req),
	TP_ARGS(req),
	TP_STRUCT__entry(
		__string(name, req->dep->name)
		__field(काष्ठा dwc3_request *, req)
		__field(अचिन्हित पूर्णांक, actual)
		__field(अचिन्हित पूर्णांक, length)
		__field(पूर्णांक, status)
		__field(पूर्णांक, zero)
		__field(पूर्णांक, लघु_not_ok)
		__field(पूर्णांक, no_पूर्णांकerrupt)
	),
	TP_fast_assign(
		__assign_str(name, req->dep->name);
		__entry->req = req;
		__entry->actual = req->request.actual;
		__entry->length = req->request.length;
		__entry->status = req->request.status;
		__entry->zero = req->request.zero;
		__entry->लघु_not_ok = req->request.लघु_not_ok;
		__entry->no_पूर्णांकerrupt = req->request.no_पूर्णांकerrupt;
	),
	TP_prपूर्णांकk("%s: req %p length %u/%u %s%s%s ==> %d",
		__get_str(name), __entry->req, __entry->actual, __entry->length,
		__entry->zero ? "Z" : "z",
		__entry->लघु_not_ok ? "S" : "s",
		__entry->no_पूर्णांकerrupt ? "i" : "I",
		__entry->status
	)
);

DEFINE_EVENT(dwc3_log_request, dwc3_alloc_request,
	TP_PROTO(काष्ठा dwc3_request *req),
	TP_ARGS(req)
);

DEFINE_EVENT(dwc3_log_request, dwc3_मुक्त_request,
	TP_PROTO(काष्ठा dwc3_request *req),
	TP_ARGS(req)
);

DEFINE_EVENT(dwc3_log_request, dwc3_ep_queue,
	TP_PROTO(काष्ठा dwc3_request *req),
	TP_ARGS(req)
);

DEFINE_EVENT(dwc3_log_request, dwc3_ep_dequeue,
	TP_PROTO(काष्ठा dwc3_request *req),
	TP_ARGS(req)
);

DEFINE_EVENT(dwc3_log_request, dwc3_gadget_giveback,
	TP_PROTO(काष्ठा dwc3_request *req),
	TP_ARGS(req)
);

DECLARE_EVENT_CLASS(dwc3_log_generic_cmd,
	TP_PROTO(अचिन्हित पूर्णांक cmd, u32 param, पूर्णांक status),
	TP_ARGS(cmd, param, status),
	TP_STRUCT__entry(
		__field(अचिन्हित पूर्णांक, cmd)
		__field(u32, param)
		__field(पूर्णांक, status)
	),
	TP_fast_assign(
		__entry->cmd = cmd;
		__entry->param = param;
		__entry->status = status;
	),
	TP_prपूर्णांकk("cmd '%s' [%x] param %08x --> status: %s",
		dwc3_gadget_generic_cmd_string(__entry->cmd),
		__entry->cmd, __entry->param,
		dwc3_gadget_generic_cmd_status_string(__entry->status)
	)
);

DEFINE_EVENT(dwc3_log_generic_cmd, dwc3_gadget_generic_cmd,
	TP_PROTO(अचिन्हित पूर्णांक cmd, u32 param, पूर्णांक status),
	TP_ARGS(cmd, param, status)
);

DECLARE_EVENT_CLASS(dwc3_log_gadget_ep_cmd,
	TP_PROTO(काष्ठा dwc3_ep *dep, अचिन्हित पूर्णांक cmd,
		काष्ठा dwc3_gadget_ep_cmd_params *params, पूर्णांक cmd_status),
	TP_ARGS(dep, cmd, params, cmd_status),
	TP_STRUCT__entry(
		__string(name, dep->name)
		__field(अचिन्हित पूर्णांक, cmd)
		__field(u32, param0)
		__field(u32, param1)
		__field(u32, param2)
		__field(पूर्णांक, cmd_status)
	),
	TP_fast_assign(
		__assign_str(name, dep->name);
		__entry->cmd = cmd;
		__entry->param0 = params->param0;
		__entry->param1 = params->param1;
		__entry->param2 = params->param2;
		__entry->cmd_status = cmd_status;
	),
	TP_prपूर्णांकk("%s: cmd '%s' [%x] params %08x %08x %08x --> status: %s",
		__get_str(name), dwc3_gadget_ep_cmd_string(__entry->cmd),
		__entry->cmd, __entry->param0,
		__entry->param1, __entry->param2,
		dwc3_ep_cmd_status_string(__entry->cmd_status)
	)
);

DEFINE_EVENT(dwc3_log_gadget_ep_cmd, dwc3_gadget_ep_cmd,
	TP_PROTO(काष्ठा dwc3_ep *dep, अचिन्हित पूर्णांक cmd,
		काष्ठा dwc3_gadget_ep_cmd_params *params, पूर्णांक cmd_status),
	TP_ARGS(dep, cmd, params, cmd_status)
);

DECLARE_EVENT_CLASS(dwc3_log_trb,
	TP_PROTO(काष्ठा dwc3_ep *dep, काष्ठा dwc3_trb *trb),
	TP_ARGS(dep, trb),
	TP_STRUCT__entry(
		__string(name, dep->name)
		__field(काष्ठा dwc3_trb *, trb)
		__field(u32, allocated)
		__field(u32, queued)
		__field(u32, bpl)
		__field(u32, bph)
		__field(u32, size)
		__field(u32, ctrl)
		__field(u32, type)
		__field(u32, enqueue)
		__field(u32, dequeue)
	),
	TP_fast_assign(
		__assign_str(name, dep->name);
		__entry->trb = trb;
		__entry->bpl = trb->bpl;
		__entry->bph = trb->bph;
		__entry->size = trb->size;
		__entry->ctrl = trb->ctrl;
		__entry->type = usb_endpoपूर्णांक_type(dep->endpoपूर्णांक.desc);
		__entry->enqueue = dep->trb_enqueue;
		__entry->dequeue = dep->trb_dequeue;
	),
	TP_prपूर्णांकk("%s: trb %p (E%d:D%d) buf %08x%08x size %s%d ctrl %08x (%c%c%c%c:%c%c:%s)",
		__get_str(name), __entry->trb, __entry->enqueue,
		__entry->dequeue, __entry->bph, __entry->bpl,
		(अणुअक्षर *s;
		पूर्णांक pcm = ((__entry->size >> 24) & 3) + 1;

		चयन (__entry->type) अणु
		हाल USB_ENDPOINT_XFER_INT:
		हाल USB_ENDPOINT_XFER_ISOC:
			चयन (pcm) अणु
			हाल 1:
				s = "1x ";
				अवरोध;
			हाल 2:
				s = "2x ";
				अवरोध;
			हाल 3:
			शेष:
				s = "3x ";
				अवरोध;
			पूर्ण
			अवरोध;
		शेष:
			s = "";
		पूर्ण s; पूर्ण),
		DWC3_TRB_SIZE_LENGTH(__entry->size), __entry->ctrl,
		__entry->ctrl & DWC3_TRB_CTRL_HWO ? 'H' : 'h',
		__entry->ctrl & DWC3_TRB_CTRL_LST ? 'L' : 'l',
		__entry->ctrl & DWC3_TRB_CTRL_CHN ? 'C' : 'c',
		__entry->ctrl & DWC3_TRB_CTRL_CSP ? 'S' : 's',
		__entry->ctrl & DWC3_TRB_CTRL_ISP_IMI ? 'S' : 's',
		__entry->ctrl & DWC3_TRB_CTRL_IOC ? 'C' : 'c',
		  dwc3_trb_type_string(DWC3_TRBCTL_TYPE(__entry->ctrl))
	)
);

DEFINE_EVENT(dwc3_log_trb, dwc3_prepare_trb,
	TP_PROTO(काष्ठा dwc3_ep *dep, काष्ठा dwc3_trb *trb),
	TP_ARGS(dep, trb)
);

DEFINE_EVENT(dwc3_log_trb, dwc3_complete_trb,
	TP_PROTO(काष्ठा dwc3_ep *dep, काष्ठा dwc3_trb *trb),
	TP_ARGS(dep, trb)
);

DECLARE_EVENT_CLASS(dwc3_log_ep,
	TP_PROTO(काष्ठा dwc3_ep *dep),
	TP_ARGS(dep),
	TP_STRUCT__entry(
		__string(name, dep->name)
		__field(अचिन्हित पूर्णांक, maxpacket)
		__field(अचिन्हित पूर्णांक, maxpacket_limit)
		__field(अचिन्हित पूर्णांक, max_streams)
		__field(अचिन्हित पूर्णांक, maxburst)
		__field(अचिन्हित पूर्णांक, flags)
		__field(अचिन्हित पूर्णांक, direction)
		__field(u8, trb_enqueue)
		__field(u8, trb_dequeue)
	),
	TP_fast_assign(
		__assign_str(name, dep->name);
		__entry->maxpacket = dep->endpoपूर्णांक.maxpacket;
		__entry->maxpacket_limit = dep->endpoपूर्णांक.maxpacket_limit;
		__entry->max_streams = dep->endpoपूर्णांक.max_streams;
		__entry->maxburst = dep->endpoपूर्णांक.maxburst;
		__entry->flags = dep->flags;
		__entry->direction = dep->direction;
		__entry->trb_enqueue = dep->trb_enqueue;
		__entry->trb_dequeue = dep->trb_dequeue;
	),
	TP_prपूर्णांकk("%s: mps %d/%d streams %d burst %d ring %d/%d flags %c:%c%c%c%c:%c",
		__get_str(name), __entry->maxpacket,
		__entry->maxpacket_limit, __entry->max_streams,
		__entry->maxburst, __entry->trb_enqueue,
		__entry->trb_dequeue,
		__entry->flags & DWC3_EP_ENABLED ? 'E' : 'e',
		__entry->flags & DWC3_EP_STALL ? 'S' : 's',
		__entry->flags & DWC3_EP_WEDGE ? 'W' : 'w',
		__entry->flags & DWC3_EP_TRANSFER_STARTED ? 'B' : 'b',
		__entry->flags & DWC3_EP_PENDING_REQUEST ? 'P' : 'p',
		__entry->direction ? '<' : '>'
	)
);

DEFINE_EVENT(dwc3_log_ep, dwc3_gadget_ep_enable,
	TP_PROTO(काष्ठा dwc3_ep *dep),
	TP_ARGS(dep)
);

DEFINE_EVENT(dwc3_log_ep, dwc3_gadget_ep_disable,
	TP_PROTO(काष्ठा dwc3_ep *dep),
	TP_ARGS(dep)
);

#पूर्ण_अगर /* __DWC3_TRACE_H */

/* this part has to be here */

#अघोषित TRACE_INCLUDE_PATH
#घोषणा TRACE_INCLUDE_PATH .

#अघोषित TRACE_INCLUDE_खाता
#घोषणा TRACE_INCLUDE_खाता trace

#समावेश <trace/define_trace.h>
