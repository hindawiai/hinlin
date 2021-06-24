<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * musb_trace.h - MUSB Controller Trace Support
 *
 * Copyright (C) 2015 Texas Instruments Incorporated - http://www.ti.com
 *
 * Author: Bin Liu <b-liu@ti.com>
 */

#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM musb

#अगर !defined(__MUSB_TRACE_H) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा __MUSB_TRACE_H

#समावेश <linux/types.h>
#समावेश <linux/tracepoपूर्णांक.h>
#समावेश <linux/usb.h>
#समावेश "musb_core.h"
#अगर_घोषित CONFIG_USB_TI_CPPI41_DMA
#समावेश "cppi_dma.h"
#पूर्ण_अगर

#घोषणा MUSB_MSG_MAX   500

TRACE_EVENT(musb_log,
	TP_PROTO(काष्ठा musb *musb, काष्ठा va_क्रमmat *vaf),
	TP_ARGS(musb, vaf),
	TP_STRUCT__entry(
		__string(name, dev_name(musb->controller))
		__dynamic_array(अक्षर, msg, MUSB_MSG_MAX)
	),
	TP_fast_assign(
		__assign_str(name, dev_name(musb->controller));
		vsnम_लिखो(__get_str(msg), MUSB_MSG_MAX, vaf->fmt, *vaf->va);
	),
	TP_prपूर्णांकk("%s: %s", __get_str(name), __get_str(msg))
);

DECLARE_EVENT_CLASS(musb_regb,
	TP_PROTO(व्योम *caller, स्थिर व्योम  __iomem *addr,
		 अचिन्हित पूर्णांक offset, u8 data),
	TP_ARGS(caller, addr, offset, data),
	TP_STRUCT__entry(
		__field(व्योम *, caller)
		__field(स्थिर व्योम __iomem *, addr)
		__field(अचिन्हित पूर्णांक, offset)
		__field(u8, data)
	),
	TP_fast_assign(
		__entry->caller = caller;
		__entry->addr = addr;
		__entry->offset = offset;
		__entry->data = data;
	),
	TP_prपूर्णांकk("%pS: %p + %04x: %02x",
		__entry->caller, __entry->addr, __entry->offset, __entry->data)
);

DEFINE_EVENT(musb_regb, musb_पढ़ोb,
	TP_PROTO(व्योम *caller, स्थिर व्योम __iomem *addr,
		 अचिन्हित पूर्णांक offset, u8 data),
	TP_ARGS(caller, addr, offset, data)
);

DEFINE_EVENT(musb_regb, musb_ग_लिखोb,
	TP_PROTO(व्योम *caller, स्थिर व्योम __iomem *addr,
		 अचिन्हित पूर्णांक offset, u8 data),
	TP_ARGS(caller, addr, offset, data)
);

DECLARE_EVENT_CLASS(musb_regw,
	TP_PROTO(व्योम *caller, स्थिर व्योम __iomem *addr,
		 अचिन्हित पूर्णांक offset, u16 data),
	TP_ARGS(caller, addr, offset, data),
	TP_STRUCT__entry(
		__field(व्योम *, caller)
		__field(स्थिर व्योम __iomem *, addr)
		__field(अचिन्हित पूर्णांक, offset)
		__field(u16, data)
	),
	TP_fast_assign(
		__entry->caller = caller;
		__entry->addr = addr;
		__entry->offset = offset;
		__entry->data = data;
	),
	TP_prपूर्णांकk("%pS: %p + %04x: %04x",
		__entry->caller, __entry->addr, __entry->offset, __entry->data)
);

DEFINE_EVENT(musb_regw, musb_पढ़ोw,
	TP_PROTO(व्योम *caller, स्थिर व्योम __iomem *addr,
		 अचिन्हित पूर्णांक offset, u16 data),
	TP_ARGS(caller, addr, offset, data)
);

DEFINE_EVENT(musb_regw, musb_ग_लिखोw,
	TP_PROTO(व्योम *caller, स्थिर व्योम __iomem *addr,
		 अचिन्हित पूर्णांक offset, u16 data),
	TP_ARGS(caller, addr, offset, data)
);

DECLARE_EVENT_CLASS(musb_regl,
	TP_PROTO(व्योम *caller, स्थिर व्योम __iomem *addr,
		 अचिन्हित पूर्णांक offset, u32 data),
	TP_ARGS(caller, addr, offset, data),
	TP_STRUCT__entry(
		__field(व्योम *, caller)
		__field(स्थिर व्योम __iomem *, addr)
		__field(अचिन्हित पूर्णांक, offset)
		__field(u32, data)
	),
	TP_fast_assign(
		__entry->caller = caller;
		__entry->addr = addr;
		__entry->offset = offset;
		__entry->data = data;
	),
	TP_prपूर्णांकk("%pS: %p + %04x: %08x",
		__entry->caller, __entry->addr, __entry->offset, __entry->data)
);

DEFINE_EVENT(musb_regl, musb_पढ़ोl,
	TP_PROTO(व्योम *caller, स्थिर व्योम __iomem *addr,
		 अचिन्हित पूर्णांक offset, u32 data),
	TP_ARGS(caller, addr, offset, data)
);

DEFINE_EVENT(musb_regl, musb_ग_लिखोl,
	TP_PROTO(व्योम *caller, स्थिर व्योम __iomem *addr,
		 अचिन्हित पूर्णांक offset, u32 data),
	TP_ARGS(caller, addr, offset, data)
);

TRACE_EVENT(musb_isr,
	TP_PROTO(काष्ठा musb *musb),
	TP_ARGS(musb),
	TP_STRUCT__entry(
		__string(name, dev_name(musb->controller))
		__field(u8, पूर्णांक_usb)
		__field(u16, पूर्णांक_tx)
		__field(u16, पूर्णांक_rx)
	),
	TP_fast_assign(
		__assign_str(name, dev_name(musb->controller));
		__entry->पूर्णांक_usb = musb->पूर्णांक_usb;
		__entry->पूर्णांक_tx = musb->पूर्णांक_tx;
		__entry->पूर्णांक_rx = musb->पूर्णांक_rx;
	),
	TP_prपूर्णांकk("%s: usb %02x, tx %04x, rx %04x",
		__get_str(name), __entry->पूर्णांक_usb,
		__entry->पूर्णांक_tx, __entry->पूर्णांक_rx
	)
);

DECLARE_EVENT_CLASS(musb_urb,
	TP_PROTO(काष्ठा musb *musb, काष्ठा urb *urb),
	TP_ARGS(musb, urb),
	TP_STRUCT__entry(
		__string(name, dev_name(musb->controller))
		__field(काष्ठा urb *, urb)
		__field(अचिन्हित पूर्णांक, pipe)
		__field(पूर्णांक, status)
		__field(अचिन्हित पूर्णांक, flag)
		__field(u32, buf_len)
		__field(u32, actual_len)
	),
	TP_fast_assign(
		__assign_str(name, dev_name(musb->controller));
		__entry->urb = urb;
		__entry->pipe = urb->pipe;
		__entry->status = urb->status;
		__entry->flag = urb->transfer_flags;
		__entry->buf_len = urb->transfer_buffer_length;
		__entry->actual_len = urb->actual_length;
	),
	TP_prपूर्णांकk("%s: %p, dev%d ep%d%s, flag 0x%x, len %d/%d, status %d",
			__get_str(name), __entry->urb,
			usb_pipedevice(__entry->pipe),
			usb_pipeendpoपूर्णांक(__entry->pipe),
			usb_pipein(__entry->pipe) ? "in" : "out",
			__entry->flag,
			__entry->actual_len, __entry->buf_len,
			__entry->status
	)
);

DEFINE_EVENT(musb_urb, musb_urb_start,
	TP_PROTO(काष्ठा musb *musb, काष्ठा urb *urb),
	TP_ARGS(musb, urb)
);

DEFINE_EVENT(musb_urb, musb_urb_gb,
	TP_PROTO(काष्ठा musb *musb, काष्ठा urb *urb),
	TP_ARGS(musb, urb)
);

DEFINE_EVENT(musb_urb, musb_urb_rx,
	TP_PROTO(काष्ठा musb *musb, काष्ठा urb *urb),
	TP_ARGS(musb, urb)
);

DEFINE_EVENT(musb_urb, musb_urb_tx,
	TP_PROTO(काष्ठा musb *musb, काष्ठा urb *urb),
	TP_ARGS(musb, urb)
);

DEFINE_EVENT(musb_urb, musb_urb_enq,
	TP_PROTO(काष्ठा musb *musb, काष्ठा urb *urb),
	TP_ARGS(musb, urb)
);

DEFINE_EVENT(musb_urb, musb_urb_deq,
	TP_PROTO(काष्ठा musb *musb, काष्ठा urb *urb),
	TP_ARGS(musb, urb)
);

DECLARE_EVENT_CLASS(musb_req,
	TP_PROTO(काष्ठा musb_request *req),
	TP_ARGS(req),
	TP_STRUCT__entry(
		__field(काष्ठा usb_request *, req)
		__field(u8, is_tx)
		__field(u8, epnum)
		__field(पूर्णांक, status)
		__field(अचिन्हित पूर्णांक, buf_len)
		__field(अचिन्हित पूर्णांक, actual_len)
		__field(अचिन्हित पूर्णांक, zero)
		__field(अचिन्हित पूर्णांक, लघु_not_ok)
		__field(अचिन्हित पूर्णांक, no_पूर्णांकerrupt)
	),
	TP_fast_assign(
		__entry->req = &req->request;
		__entry->is_tx = req->tx;
		__entry->epnum = req->epnum;
		__entry->status = req->request.status;
		__entry->buf_len = req->request.length;
		__entry->actual_len = req->request.actual;
		__entry->zero = req->request.zero;
		__entry->लघु_not_ok = req->request.लघु_not_ok;
		__entry->no_पूर्णांकerrupt = req->request.no_पूर्णांकerrupt;
	),
	TP_prपूर्णांकk("%p, ep%d %s, %s%s%s, len %d/%d, status %d",
			__entry->req, __entry->epnum,
			__entry->is_tx ? "tx/IN" : "rx/OUT",
			__entry->zero ? "Z" : "z",
			__entry->लघु_not_ok ? "S" : "s",
			__entry->no_पूर्णांकerrupt ? "I" : "i",
			__entry->actual_len, __entry->buf_len,
			__entry->status
	)
);

DEFINE_EVENT(musb_req, musb_req_gb,
	TP_PROTO(काष्ठा musb_request *req),
	TP_ARGS(req)
);

DEFINE_EVENT(musb_req, musb_req_tx,
	TP_PROTO(काष्ठा musb_request *req),
	TP_ARGS(req)
);

DEFINE_EVENT(musb_req, musb_req_rx,
	TP_PROTO(काष्ठा musb_request *req),
	TP_ARGS(req)
);

DEFINE_EVENT(musb_req, musb_req_alloc,
	TP_PROTO(काष्ठा musb_request *req),
	TP_ARGS(req)
);

DEFINE_EVENT(musb_req, musb_req_मुक्त,
	TP_PROTO(काष्ठा musb_request *req),
	TP_ARGS(req)
);

DEFINE_EVENT(musb_req, musb_req_start,
	TP_PROTO(काष्ठा musb_request *req),
	TP_ARGS(req)
);

DEFINE_EVENT(musb_req, musb_req_enq,
	TP_PROTO(काष्ठा musb_request *req),
	TP_ARGS(req)
);

DEFINE_EVENT(musb_req, musb_req_deq,
	TP_PROTO(काष्ठा musb_request *req),
	TP_ARGS(req)
);

#अगर_घोषित CONFIG_USB_TI_CPPI41_DMA
DECLARE_EVENT_CLASS(musb_cppi41,
	TP_PROTO(काष्ठा cppi41_dma_channel *ch),
	TP_ARGS(ch),
	TP_STRUCT__entry(
		__field(काष्ठा cppi41_dma_channel *, ch)
		__string(name, dev_name(ch->hw_ep->musb->controller))
		__field(u8, hwep)
		__field(u8, port)
		__field(u8, is_tx)
		__field(u32, len)
		__field(u32, prog_len)
		__field(u32, xferred)
	),
	TP_fast_assign(
		__entry->ch = ch;
		__assign_str(name, dev_name(ch->hw_ep->musb->controller));
		__entry->hwep = ch->hw_ep->epnum;
		__entry->port = ch->port_num;
		__entry->is_tx = ch->is_tx;
		__entry->len = ch->total_len;
		__entry->prog_len = ch->prog_len;
		__entry->xferred = ch->transferred;
	),
	TP_prपूर्णांकk("%s: %p, hwep%d ch%d%s, prog_len %d, len %d/%d",
			__get_str(name), __entry->ch, __entry->hwep,
			__entry->port, __entry->is_tx ? "tx" : "rx",
			__entry->prog_len, __entry->xferred, __entry->len
	)
);

DEFINE_EVENT(musb_cppi41, musb_cppi41_करोne,
	TP_PROTO(काष्ठा cppi41_dma_channel *ch),
	TP_ARGS(ch)
);

DEFINE_EVENT(musb_cppi41, musb_cppi41_gb,
	TP_PROTO(काष्ठा cppi41_dma_channel *ch),
	TP_ARGS(ch)
);

DEFINE_EVENT(musb_cppi41, musb_cppi41_config,
	TP_PROTO(काष्ठा cppi41_dma_channel *ch),
	TP_ARGS(ch)
);

DEFINE_EVENT(musb_cppi41, musb_cppi41_cont,
	TP_PROTO(काष्ठा cppi41_dma_channel *ch),
	TP_ARGS(ch)
);

DEFINE_EVENT(musb_cppi41, musb_cppi41_alloc,
	TP_PROTO(काष्ठा cppi41_dma_channel *ch),
	TP_ARGS(ch)
);

DEFINE_EVENT(musb_cppi41, musb_cppi41_पात,
	TP_PROTO(काष्ठा cppi41_dma_channel *ch),
	TP_ARGS(ch)
);

DEFINE_EVENT(musb_cppi41, musb_cppi41_मुक्त,
	TP_PROTO(काष्ठा cppi41_dma_channel *ch),
	TP_ARGS(ch)
);
#पूर्ण_अगर /* CONFIG_USB_TI_CPPI41_DMA */

#पूर्ण_अगर /* __MUSB_TRACE_H */

/* this part has to be here */

#अघोषित TRACE_INCLUDE_PATH
#घोषणा TRACE_INCLUDE_PATH .

#अघोषित TRACE_INCLUDE_खाता
#घोषणा TRACE_INCLUDE_खाता musb_trace

#समावेश <trace/define_trace.h>
