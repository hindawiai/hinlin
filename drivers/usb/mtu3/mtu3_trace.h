<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/**
 * mtu3_trace.h - trace support
 *
 * Copyright (C) 2019 MediaTek Inc.
 *
 * Author: Chunfeng Yun <chunfeng.yun@mediatek.com>
 */

#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM mtu3

#अगर !defined(__MTU3_TRACE_H__) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा __MTU3_TRACE_H__

#समावेश <linux/types.h>
#समावेश <linux/tracepoपूर्णांक.h>

#समावेश "mtu3.h"

#घोषणा MTU3_MSG_MAX	256

TRACE_EVENT(mtu3_log,
	TP_PROTO(काष्ठा device *dev, काष्ठा va_क्रमmat *vaf),
	TP_ARGS(dev, vaf),
	TP_STRUCT__entry(
		__string(name, dev_name(dev))
		__dynamic_array(अक्षर, msg, MTU3_MSG_MAX)
	),
	TP_fast_assign(
		__assign_str(name, dev_name(dev));
		vsnम_लिखो(__get_str(msg), MTU3_MSG_MAX, vaf->fmt, *vaf->va);
	),
	TP_prपूर्णांकk("%s: %s", __get_str(name), __get_str(msg))
);

TRACE_EVENT(mtu3_u3_ltssm_isr,
	TP_PROTO(u32 पूर्णांकr),
	TP_ARGS(पूर्णांकr),
	TP_STRUCT__entry(
		__field(u32, पूर्णांकr)
	),
	TP_fast_assign(
		__entry->पूर्णांकr = पूर्णांकr;
	),
	TP_prपूर्णांकk("(%08x) %s %s %s %s %s %s", __entry->पूर्णांकr,
		__entry->पूर्णांकr & HOT_RST_INTR ? "HOT_RST" : "",
		__entry->पूर्णांकr & WARM_RST_INTR ? "WARM_RST" : "",
		__entry->पूर्णांकr & ENTER_U3_INTR ? "ENT_U3" : "",
		__entry->पूर्णांकr & EXIT_U3_INTR ? "EXIT_U3" : "",
		__entry->पूर्णांकr & VBUS_RISE_INTR ? "VBUS_RISE" : "",
		__entry->पूर्णांकr & VBUS_FALL_INTR ? "VBUS_FALL" : ""
	)
);

TRACE_EVENT(mtu3_u2_common_isr,
	TP_PROTO(u32 पूर्णांकr),
	TP_ARGS(पूर्णांकr),
	TP_STRUCT__entry(
		__field(u32, पूर्णांकr)
	),
	TP_fast_assign(
		__entry->पूर्णांकr = पूर्णांकr;
	),
	TP_prपूर्णांकk("(%08x) %s %s %s", __entry->पूर्णांकr,
		__entry->पूर्णांकr & SUSPEND_INTR ? "SUSPEND" : "",
		__entry->पूर्णांकr & RESUME_INTR ? "RESUME" : "",
		__entry->पूर्णांकr & RESET_INTR ? "RESET" : ""
	)
);

TRACE_EVENT(mtu3_qmu_isr,
	TP_PROTO(u32 करोne_पूर्णांकr, u32 exp_पूर्णांकr),
	TP_ARGS(करोne_पूर्णांकr, exp_पूर्णांकr),
	TP_STRUCT__entry(
		__field(u32, करोne_पूर्णांकr)
		__field(u32, exp_पूर्णांकr)
	),
	TP_fast_assign(
		__entry->करोne_पूर्णांकr = करोne_पूर्णांकr;
		__entry->exp_पूर्णांकr = exp_पूर्णांकr;
	),
	TP_prपूर्णांकk("done (tx %04x, rx %04x), exp (%08x)",
		__entry->करोne_पूर्णांकr & 0xffff,
		__entry->करोne_पूर्णांकr >> 16,
		__entry->exp_पूर्णांकr
	)
);

DECLARE_EVENT_CLASS(mtu3_log_setup,
	TP_PROTO(काष्ठा usb_ctrlrequest *setup),
	TP_ARGS(setup),
	TP_STRUCT__entry(
		__field(__u8, bRequestType)
		__field(__u8, bRequest)
		__field(__u16, wValue)
		__field(__u16, wIndex)
		__field(__u16, wLength)
	),
	TP_fast_assign(
		__entry->bRequestType = setup->bRequestType;
		__entry->bRequest = setup->bRequest;
		__entry->wValue = le16_to_cpu(setup->wValue);
		__entry->wIndex = le16_to_cpu(setup->wIndex);
		__entry->wLength = le16_to_cpu(setup->wLength);
	),
	TP_prपूर्णांकk("setup - %02x %02x %04x %04x %04x",
		__entry->bRequestType, __entry->bRequest,
		__entry->wValue, __entry->wIndex, __entry->wLength
	)
);

DEFINE_EVENT(mtu3_log_setup, mtu3_handle_setup,
	TP_PROTO(काष्ठा usb_ctrlrequest *setup),
	TP_ARGS(setup)
);

DECLARE_EVENT_CLASS(mtu3_log_request,
	TP_PROTO(काष्ठा mtu3_request *mreq),
	TP_ARGS(mreq),
	TP_STRUCT__entry(
		__string(name, mreq->mep->name)
		__field(काष्ठा mtu3_request *, mreq)
		__field(काष्ठा qmu_gpd *, gpd)
		__field(अचिन्हित पूर्णांक, actual)
		__field(अचिन्हित पूर्णांक, length)
		__field(पूर्णांक, status)
		__field(पूर्णांक, zero)
		__field(पूर्णांक, no_पूर्णांकerrupt)
	),
	TP_fast_assign(
		__assign_str(name, mreq->mep->name);
		__entry->mreq = mreq;
		__entry->gpd = mreq->gpd;
		__entry->actual = mreq->request.actual;
		__entry->length = mreq->request.length;
		__entry->status = mreq->request.status;
		__entry->zero = mreq->request.zero;
		__entry->no_पूर्णांकerrupt = mreq->request.no_पूर्णांकerrupt;
	),
	TP_prपूर्णांकk("%s: req %p gpd %p len %u/%u %s%s --> %d",
		__get_str(name), __entry->mreq, __entry->gpd,
		__entry->actual, __entry->length,
		__entry->zero ? "Z" : "z",
		__entry->no_पूर्णांकerrupt ? "i" : "I",
		__entry->status
	)
);

DEFINE_EVENT(mtu3_log_request, mtu3_alloc_request,
	TP_PROTO(काष्ठा mtu3_request *req),
	TP_ARGS(req)
);

DEFINE_EVENT(mtu3_log_request, mtu3_मुक्त_request,
	TP_PROTO(काष्ठा mtu3_request *req),
	TP_ARGS(req)
);

DEFINE_EVENT(mtu3_log_request, mtu3_gadget_queue,
	TP_PROTO(काष्ठा mtu3_request *req),
	TP_ARGS(req)
);

DEFINE_EVENT(mtu3_log_request, mtu3_gadget_dequeue,
	TP_PROTO(काष्ठा mtu3_request *req),
	TP_ARGS(req)
);

DEFINE_EVENT(mtu3_log_request, mtu3_req_complete,
	TP_PROTO(काष्ठा mtu3_request *req),
	TP_ARGS(req)
);

DECLARE_EVENT_CLASS(mtu3_log_gpd,
	TP_PROTO(काष्ठा mtu3_ep *mep, काष्ठा qmu_gpd *gpd),
	TP_ARGS(mep, gpd),
	TP_STRUCT__entry(
		__string(name, mep->name)
		__field(काष्ठा qmu_gpd *, gpd)
		__field(u32, dw0)
		__field(u32, dw1)
		__field(u32, dw2)
		__field(u32, dw3)
	),
	TP_fast_assign(
		__assign_str(name, mep->name);
		__entry->gpd = gpd;
		__entry->dw0 = le32_to_cpu(gpd->dw0_info);
		__entry->dw1 = le32_to_cpu(gpd->next_gpd);
		__entry->dw2 = le32_to_cpu(gpd->buffer);
		__entry->dw3 = le32_to_cpu(gpd->dw3_info);
	),
	TP_prपूर्णांकk("%s: gpd %p - %08x %08x %08x %08x",
		__get_str(name), __entry->gpd,
		__entry->dw0, __entry->dw1,
		__entry->dw2, __entry->dw3
	)
);

DEFINE_EVENT(mtu3_log_gpd, mtu3_prepare_gpd,
	TP_PROTO(काष्ठा mtu3_ep *mep, काष्ठा qmu_gpd *gpd),
	TP_ARGS(mep, gpd)
);

DEFINE_EVENT(mtu3_log_gpd, mtu3_complete_gpd,
	TP_PROTO(काष्ठा mtu3_ep *mep, काष्ठा qmu_gpd *gpd),
	TP_ARGS(mep, gpd)
);

DEFINE_EVENT(mtu3_log_gpd, mtu3_zlp_exp_gpd,
	TP_PROTO(काष्ठा mtu3_ep *mep, काष्ठा qmu_gpd *gpd),
	TP_ARGS(mep, gpd)
);

DECLARE_EVENT_CLASS(mtu3_log_ep,
	TP_PROTO(काष्ठा mtu3_ep *mep),
	TP_ARGS(mep),
	TP_STRUCT__entry(
		__string(name, mep->name)
		__field(अचिन्हित पूर्णांक, type)
		__field(अचिन्हित पूर्णांक, slot)
		__field(अचिन्हित पूर्णांक, maxp)
		__field(अचिन्हित पूर्णांक, mult)
		__field(अचिन्हित पूर्णांक, maxburst)
		__field(अचिन्हित पूर्णांक, flags)
		__field(अचिन्हित पूर्णांक, direction)
		__field(काष्ठा mtu3_gpd_ring *, gpd_ring)
	),
	TP_fast_assign(
		__assign_str(name, mep->name);
		__entry->type = mep->type;
		__entry->slot = mep->slot;
		__entry->maxp = mep->ep.maxpacket;
		__entry->mult = mep->ep.mult;
		__entry->maxburst = mep->ep.maxburst;
		__entry->flags = mep->flags;
		__entry->direction = mep->is_in;
		__entry->gpd_ring = &mep->gpd_ring;
	),
	TP_prपूर्णांकk("%s: type %d maxp %d slot %d mult %d burst %d ring %p/%pad flags %c:%c%c%c:%c",
		__get_str(name), __entry->type,
		__entry->maxp, __entry->slot,
		__entry->mult, __entry->maxburst,
		__entry->gpd_ring, &__entry->gpd_ring->dma,
		__entry->flags & MTU3_EP_ENABLED ? 'E' : 'e',
		__entry->flags & MTU3_EP_STALL ? 'S' : 's',
		__entry->flags & MTU3_EP_WEDGE ? 'W' : 'w',
		__entry->flags & MTU3_EP_BUSY ? 'B' : 'b',
		__entry->direction ? '<' : '>'
	)
);

DEFINE_EVENT(mtu3_log_ep, mtu3_gadget_ep_enable,
	TP_PROTO(काष्ठा mtu3_ep *mep),
	TP_ARGS(mep)
);

DEFINE_EVENT(mtu3_log_ep, mtu3_gadget_ep_disable,
	TP_PROTO(काष्ठा mtu3_ep *mep),
	TP_ARGS(mep)
);

DEFINE_EVENT(mtu3_log_ep, mtu3_gadget_ep_set_halt,
	TP_PROTO(काष्ठा mtu3_ep *mep),
	TP_ARGS(mep)
);

#पूर्ण_अगर /* __MTU3_TRACE_H__ */

/* this part has to be here */

#अघोषित TRACE_INCLUDE_PATH
#घोषणा TRACE_INCLUDE_PATH .

#अघोषित TRACE_INCLUDE_खाता
#घोषणा TRACE_INCLUDE_खाता mtu3_trace

#समावेश <trace/define_trace.h>
