<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/**
 * udc.c - Core UDC Framework
 *
 * Copyright (C) 2016 Intel Corporation
 * Author: Felipe Balbi <felipe.balbi@linux.पूर्णांकel.com>
 */

#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM gadget

#अगर !defined(__UDC_TRACE_H) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा __UDC_TRACE_H

#समावेश <linux/types.h>
#समावेश <linux/tracepoपूर्णांक.h>
#समावेश <यंत्र/byteorder.h>
#समावेश <linux/usb/gadget.h>

DECLARE_EVENT_CLASS(udc_log_gadget,
	TP_PROTO(काष्ठा usb_gadget *g, पूर्णांक ret),
	TP_ARGS(g, ret),
	TP_STRUCT__entry(
		__field(क्रमागत usb_device_speed, speed)
		__field(क्रमागत usb_device_speed, max_speed)
		__field(क्रमागत usb_device_state, state)
		__field(अचिन्हित, mA)
		__field(अचिन्हित, sg_supported)
		__field(अचिन्हित, is_otg)
		__field(अचिन्हित, is_a_peripheral)
		__field(अचिन्हित, b_hnp_enable)
		__field(अचिन्हित, a_hnp_support)
		__field(अचिन्हित, hnp_polling_support)
		__field(अचिन्हित, host_request_flag)
		__field(अचिन्हित, quirk_ep_out_aligned_size)
		__field(अचिन्हित, quirk_altset_not_supp)
		__field(अचिन्हित, quirk_stall_not_supp)
		__field(अचिन्हित, quirk_zlp_not_supp)
		__field(अचिन्हित, is_selfघातered)
		__field(अचिन्हित, deactivated)
		__field(अचिन्हित, connected)
		__field(पूर्णांक, ret)
	),
	TP_fast_assign(
		__entry->speed = g->speed;
		__entry->max_speed = g->max_speed;
		__entry->state = g->state;
		__entry->mA = g->mA;
		__entry->sg_supported = g->sg_supported;
		__entry->is_otg = g->is_otg;
		__entry->is_a_peripheral = g->is_a_peripheral;
		__entry->b_hnp_enable = g->b_hnp_enable;
		__entry->a_hnp_support = g->a_hnp_support;
		__entry->hnp_polling_support = g->hnp_polling_support;
		__entry->host_request_flag = g->host_request_flag;
		__entry->quirk_ep_out_aligned_size = g->quirk_ep_out_aligned_size;
		__entry->quirk_altset_not_supp = g->quirk_altset_not_supp;
		__entry->quirk_stall_not_supp = g->quirk_stall_not_supp;
		__entry->quirk_zlp_not_supp = g->quirk_zlp_not_supp;
		__entry->is_selfघातered = g->is_selfघातered;
		__entry->deactivated = g->deactivated;
		__entry->connected = g->connected;
		__entry->ret = ret;
	),
	TP_prपूर्णांकk("speed %d/%d state %d %dmA [%s%s%s%s%s%s%s%s%s%s%s%s%s%s] --> %d",
		__entry->speed, __entry->max_speed, __entry->state, __entry->mA,
		__entry->sg_supported ? "sg:" : "",
		__entry->is_otg ? "OTG:" : "",
		__entry->is_a_peripheral ? "a_peripheral:" : "",
		__entry->b_hnp_enable ? "b_hnp:" : "",
		__entry->a_hnp_support ? "a_hnp:" : "",
		__entry->hnp_polling_support ? "hnp_poll:" : "",
		__entry->host_request_flag ? "hostreq:" : "",
		__entry->quirk_ep_out_aligned_size ? "out_aligned:" : "",
		__entry->quirk_altset_not_supp ? "no_altset:" : "",
		__entry->quirk_stall_not_supp ? "no_stall:" : "",
		__entry->quirk_zlp_not_supp ? "no_zlp" : "",
		__entry->is_selfघातered ? "self-powered:" : "bus-powered:",
		__entry->deactivated ? "deactivated:" : "activated:",
		__entry->connected ? "connected" : "disconnected",
		__entry->ret)
);

DEFINE_EVENT(udc_log_gadget, usb_gadget_frame_number,
	TP_PROTO(काष्ठा usb_gadget *g, पूर्णांक ret),
	TP_ARGS(g, ret)
);

DEFINE_EVENT(udc_log_gadget, usb_gadget_wakeup,
	TP_PROTO(काष्ठा usb_gadget *g, पूर्णांक ret),
	TP_ARGS(g, ret)
);

DEFINE_EVENT(udc_log_gadget, usb_gadget_set_selfघातered,
	TP_PROTO(काष्ठा usb_gadget *g, पूर्णांक ret),
	TP_ARGS(g, ret)
);

DEFINE_EVENT(udc_log_gadget, usb_gadget_clear_selfघातered,
	TP_PROTO(काष्ठा usb_gadget *g, पूर्णांक ret),
	TP_ARGS(g, ret)
);

DEFINE_EVENT(udc_log_gadget, usb_gadget_vbus_connect,
	TP_PROTO(काष्ठा usb_gadget *g, पूर्णांक ret),
	TP_ARGS(g, ret)
);

DEFINE_EVENT(udc_log_gadget, usb_gadget_vbus_draw,
	TP_PROTO(काष्ठा usb_gadget *g, पूर्णांक ret),
	TP_ARGS(g, ret)
);

DEFINE_EVENT(udc_log_gadget, usb_gadget_vbus_disconnect,
	TP_PROTO(काष्ठा usb_gadget *g, पूर्णांक ret),
	TP_ARGS(g, ret)
);

DEFINE_EVENT(udc_log_gadget, usb_gadget_connect,
	TP_PROTO(काष्ठा usb_gadget *g, पूर्णांक ret),
	TP_ARGS(g, ret)
);

DEFINE_EVENT(udc_log_gadget, usb_gadget_disconnect,
	TP_PROTO(काष्ठा usb_gadget *g, पूर्णांक ret),
	TP_ARGS(g, ret)
);

DEFINE_EVENT(udc_log_gadget, usb_gadget_deactivate,
	TP_PROTO(काष्ठा usb_gadget *g, पूर्णांक ret),
	TP_ARGS(g, ret)
);

DEFINE_EVENT(udc_log_gadget, usb_gadget_activate,
	TP_PROTO(काष्ठा usb_gadget *g, पूर्णांक ret),
	TP_ARGS(g, ret)
);

DECLARE_EVENT_CLASS(udc_log_ep,
	TP_PROTO(काष्ठा usb_ep *ep, पूर्णांक ret),
	TP_ARGS(ep, ret),
	TP_STRUCT__entry(
		__dynamic_array(अक्षर, name, UDC_TRACE_STR_MAX)
		__field(अचिन्हित, maxpacket)
		__field(अचिन्हित, maxpacket_limit)
		__field(अचिन्हित, max_streams)
		__field(अचिन्हित, mult)
		__field(अचिन्हित, maxburst)
		__field(u8, address)
		__field(bool, claimed)
		__field(bool, enabled)
		__field(पूर्णांक, ret)
	),
	TP_fast_assign(
		snम_लिखो(__get_str(name), UDC_TRACE_STR_MAX, "%s", ep->name);
		__entry->maxpacket = ep->maxpacket;
		__entry->maxpacket_limit = ep->maxpacket_limit;
		__entry->max_streams = ep->max_streams;
		__entry->mult = ep->mult;
		__entry->maxburst = ep->maxburst;
		__entry->address = ep->address,
		__entry->claimed = ep->claimed;
		__entry->enabled = ep->enabled;
		__entry->ret = ret;
	),
	TP_prपूर्णांकk("%s: mps %d/%d streams %d mult %d burst %d addr %02x %s%s --> %d",
		__get_str(name), __entry->maxpacket, __entry->maxpacket_limit,
		__entry->max_streams, __entry->mult, __entry->maxburst,
		__entry->address, __entry->claimed ? "claimed:" : "released:",
		__entry->enabled ? "enabled" : "disabled", ret)
);

DEFINE_EVENT(udc_log_ep, usb_ep_set_maxpacket_limit,
	TP_PROTO(काष्ठा usb_ep *ep, पूर्णांक ret),
	TP_ARGS(ep, ret)
);

DEFINE_EVENT(udc_log_ep, usb_ep_enable,
	TP_PROTO(काष्ठा usb_ep *ep, पूर्णांक ret),
	TP_ARGS(ep, ret)
);

DEFINE_EVENT(udc_log_ep, usb_ep_disable,
	TP_PROTO(काष्ठा usb_ep *ep, पूर्णांक ret),
	TP_ARGS(ep, ret)
);

DEFINE_EVENT(udc_log_ep, usb_ep_set_halt,
	TP_PROTO(काष्ठा usb_ep *ep, पूर्णांक ret),
	TP_ARGS(ep, ret)
);

DEFINE_EVENT(udc_log_ep, usb_ep_clear_halt,
	TP_PROTO(काष्ठा usb_ep *ep, पूर्णांक ret),
	TP_ARGS(ep, ret)
);

DEFINE_EVENT(udc_log_ep, usb_ep_set_wedge,
	TP_PROTO(काष्ठा usb_ep *ep, पूर्णांक ret),
	TP_ARGS(ep, ret)
);

DEFINE_EVENT(udc_log_ep, usb_ep_fअगरo_status,
	TP_PROTO(काष्ठा usb_ep *ep, पूर्णांक ret),
	TP_ARGS(ep, ret)
);

DEFINE_EVENT(udc_log_ep, usb_ep_fअगरo_flush,
	TP_PROTO(काष्ठा usb_ep *ep, पूर्णांक ret),
	TP_ARGS(ep, ret)
);

DECLARE_EVENT_CLASS(udc_log_req,
	TP_PROTO(काष्ठा usb_ep *ep, काष्ठा usb_request *req, पूर्णांक ret),
	TP_ARGS(ep, req, ret),
	TP_STRUCT__entry(
		__dynamic_array(अक्षर, name, UDC_TRACE_STR_MAX)
		__field(अचिन्हित, length)
		__field(अचिन्हित, actual)
		__field(अचिन्हित, num_sgs)
		__field(अचिन्हित, num_mapped_sgs)
		__field(अचिन्हित, stream_id)
		__field(अचिन्हित, no_पूर्णांकerrupt)
		__field(अचिन्हित, zero)
		__field(अचिन्हित, लघु_not_ok)
		__field(पूर्णांक, status)
		__field(पूर्णांक, ret)
		__field(काष्ठा usb_request *, req)
	),
	TP_fast_assign(
		snम_लिखो(__get_str(name), UDC_TRACE_STR_MAX, "%s", ep->name);
		__entry->length = req->length;
		__entry->actual = req->actual;
		__entry->num_sgs = req->num_sgs;
		__entry->num_mapped_sgs = req->num_mapped_sgs;
		__entry->stream_id = req->stream_id;
		__entry->no_पूर्णांकerrupt = req->no_पूर्णांकerrupt;
		__entry->zero = req->zero;
		__entry->लघु_not_ok = req->लघु_not_ok;
		__entry->status = req->status;
		__entry->ret = ret;
		__entry->req = req;
	),
	TP_prपूर्णांकk("%s: req %p length %d/%d sgs %d/%d stream %d %s%s%s status %d --> %d",
		__get_str(name),__entry->req,  __entry->actual, __entry->length,
		__entry->num_mapped_sgs, __entry->num_sgs, __entry->stream_id,
		__entry->zero ? "Z" : "z",
		__entry->लघु_not_ok ? "S" : "s",
		__entry->no_पूर्णांकerrupt ? "i" : "I",
		__entry->status, __entry->ret
	)
);

DEFINE_EVENT(udc_log_req, usb_ep_alloc_request,
	TP_PROTO(काष्ठा usb_ep *ep, काष्ठा usb_request *req, पूर्णांक ret),
	TP_ARGS(ep, req, ret)
);

DEFINE_EVENT(udc_log_req, usb_ep_मुक्त_request,
	TP_PROTO(काष्ठा usb_ep *ep, काष्ठा usb_request *req, पूर्णांक ret),
	TP_ARGS(ep, req, ret)
);

DEFINE_EVENT(udc_log_req, usb_ep_queue,
	TP_PROTO(काष्ठा usb_ep *ep, काष्ठा usb_request *req, पूर्णांक ret),
	TP_ARGS(ep, req, ret)
);

DEFINE_EVENT(udc_log_req, usb_ep_dequeue,
	TP_PROTO(काष्ठा usb_ep *ep, काष्ठा usb_request *req, पूर्णांक ret),
	TP_ARGS(ep, req, ret)
);

DEFINE_EVENT(udc_log_req, usb_gadget_giveback_request,
	TP_PROTO(काष्ठा usb_ep *ep, काष्ठा usb_request *req, पूर्णांक ret),
	TP_ARGS(ep, req, ret)
);

#पूर्ण_अगर /* __UDC_TRACE_H */

/* this part has to be here */

#अघोषित TRACE_INCLUDE_PATH
#घोषणा TRACE_INCLUDE_PATH .

#अघोषित TRACE_INCLUDE_खाता
#घोषणा TRACE_INCLUDE_खाता trace

#समावेश <trace/define_trace.h>
