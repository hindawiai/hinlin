<शैली गुरु>
/* SPDX-License-Identअगरier: ISC */
/*
 * Copyright (c) 2013-2016 Qualcomm Atheros, Inc.
 * Copyright (c) 2019, The Linux Foundation. All rights reserved.
 */

#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM wil6210
#अगर !defined(WIL6210_TRACE_H) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा WIL6210_TRACE_H

#समावेश <linux/tracepoपूर्णांक.h>
#समावेश "wil6210.h"
#समावेश "txrx.h"

/* create empty functions when tracing is disabled */
#अगर !defined(CONFIG_WIL6210_TRACING) || defined(__CHECKER__)

#अघोषित TRACE_EVENT
#घोषणा TRACE_EVENT(name, proto, ...) \
अटल अंतरभूत व्योम trace_ ## name(proto) अणुपूर्ण
#अघोषित DECLARE_EVENT_CLASS
#घोषणा DECLARE_EVENT_CLASS(...)
#अघोषित DEFINE_EVENT
#घोषणा DEFINE_EVENT(evt_class, name, proto, ...) \
अटल अंतरभूत व्योम trace_ ## name(proto) अणुपूर्ण
#पूर्ण_अगर /* !CONFIG_WIL6210_TRACING || defined(__CHECKER__) */

DECLARE_EVENT_CLASS(wil6210_wmi,
	TP_PROTO(काष्ठा wmi_cmd_hdr *wmi, व्योम *buf, u16 buf_len),

	TP_ARGS(wmi, buf, buf_len),

	TP_STRUCT__entry(
		__field(u8, mid)
		__field(u16, command_id)
		__field(u32, fw_बारtamp)
		__field(u16, buf_len)
		__dynamic_array(u8, buf, buf_len)
	),

	TP_fast_assign(
		__entry->mid = wmi->mid;
		__entry->command_id = le16_to_cpu(wmi->command_id);
		__entry->fw_बारtamp = le32_to_cpu(wmi->fw_बारtamp);
		__entry->buf_len = buf_len;
		स_नकल(__get_dynamic_array(buf), buf, buf_len);
	),

	TP_prपूर्णांकk(
		"MID %d id 0x%04x len %d timestamp %d",
		__entry->mid, __entry->command_id, __entry->buf_len,
		__entry->fw_बारtamp
	)
);

DEFINE_EVENT(wil6210_wmi, wil6210_wmi_cmd,
	TP_PROTO(काष्ठा wmi_cmd_hdr *wmi, व्योम *buf, u16 buf_len),
	TP_ARGS(wmi, buf, buf_len)
);

DEFINE_EVENT(wil6210_wmi, wil6210_wmi_event,
	TP_PROTO(काष्ठा wmi_cmd_hdr *wmi, व्योम *buf, u16 buf_len),
	TP_ARGS(wmi, buf, buf_len)
);

#घोषणा WIL6210_MSG_MAX (200)

DECLARE_EVENT_CLASS(wil6210_log_event,
	TP_PROTO(काष्ठा va_क्रमmat *vaf),
	TP_ARGS(vaf),
	TP_STRUCT__entry(
		__dynamic_array(अक्षर, msg, WIL6210_MSG_MAX)
	),
	TP_fast_assign(
		WARN_ON_ONCE(vsnम_लिखो(__get_dynamic_array(msg),
				       WIL6210_MSG_MAX,
				       vaf->fmt,
				       *vaf->va) >= WIL6210_MSG_MAX);
	),
	TP_prपूर्णांकk("%s", __get_str(msg))
);

DEFINE_EVENT(wil6210_log_event, wil6210_log_err,
	TP_PROTO(काष्ठा va_क्रमmat *vaf),
	TP_ARGS(vaf)
);

DEFINE_EVENT(wil6210_log_event, wil6210_log_info,
	TP_PROTO(काष्ठा va_क्रमmat *vaf),
	TP_ARGS(vaf)
);

DEFINE_EVENT(wil6210_log_event, wil6210_log_dbg,
	TP_PROTO(काष्ठा va_क्रमmat *vaf),
	TP_ARGS(vaf)
);

#घोषणा wil_pseuकरो_irq_cause(x) __prपूर्णांक_flags(x, "|",	\
	अणुBIT_DMA_PSEUDO_CAUSE_RX,	"Rx" पूर्ण,		\
	अणुBIT_DMA_PSEUDO_CAUSE_TX,	"Tx" पूर्ण,		\
	अणुBIT_DMA_PSEUDO_CAUSE_MISC,	"Misc" पूर्ण)

TRACE_EVENT(wil6210_irq_pseuकरो,
	TP_PROTO(u32 x),
	TP_ARGS(x),
	TP_STRUCT__entry(
		__field(u32, x)
	),
	TP_fast_assign(
		__entry->x = x;
	),
	TP_prपूर्णांकk("cause 0x%08x : %s", __entry->x,
		  wil_pseuकरो_irq_cause(__entry->x))
);

DECLARE_EVENT_CLASS(wil6210_irq,
	TP_PROTO(u32 x),
	TP_ARGS(x),
	TP_STRUCT__entry(
		__field(u32, x)
	),
	TP_fast_assign(
		__entry->x = x;
	),
	TP_prपूर्णांकk("cause 0x%08x", __entry->x)
);

DEFINE_EVENT(wil6210_irq, wil6210_irq_rx,
	TP_PROTO(u32 x),
	TP_ARGS(x)
);

DEFINE_EVENT(wil6210_irq, wil6210_irq_tx,
	TP_PROTO(u32 x),
	TP_ARGS(x)
);

DEFINE_EVENT(wil6210_irq, wil6210_irq_misc,
	TP_PROTO(u32 x),
	TP_ARGS(x)
);

DEFINE_EVENT(wil6210_irq, wil6210_irq_misc_thपढ़ो,
	TP_PROTO(u32 x),
	TP_ARGS(x)
);

TRACE_EVENT(wil6210_rx,
	TP_PROTO(u16 index, काष्ठा vring_rx_desc *d),
	TP_ARGS(index, d),
	TP_STRUCT__entry(
		__field(u16, index)
		__field(अचिन्हित पूर्णांक, len)
		__field(u8, mid)
		__field(u8, cid)
		__field(u8, tid)
		__field(u8, type)
		__field(u8, subtype)
		__field(u16, seq)
		__field(u8, mcs)
	),
	TP_fast_assign(
		__entry->index = index;
		__entry->len = d->dma.length;
		__entry->mid = wil_rxdesc_mid(d);
		__entry->cid = wil_rxdesc_cid(d);
		__entry->tid = wil_rxdesc_tid(d);
		__entry->type = wil_rxdesc_ftype(d);
		__entry->subtype = wil_rxdesc_subtype(d);
		__entry->seq = wil_rxdesc_seq(d);
		__entry->mcs = wil_rxdesc_mcs(d);
	),
	TP_prपूर्णांकk("index %d len %d mid %d cid (%%8) %d tid %d mcs %d seq 0x%03x"
		  " type 0x%1x subtype 0x%1x", __entry->index, __entry->len,
		  __entry->mid, __entry->cid, __entry->tid, __entry->mcs,
		  __entry->seq, __entry->type, __entry->subtype)
);

TRACE_EVENT(wil6210_rx_status,
	    TP_PROTO(काष्ठा wil6210_priv *wil, u8 use_compressed, u16 buff_id,
		     व्योम *msg),
	    TP_ARGS(wil, use_compressed, buff_id, msg),
	    TP_STRUCT__entry(__field(u8, use_compressed)
			     __field(u16, buff_id)
			     __field(अचिन्हित पूर्णांक, len)
			     __field(u8, mid)
			     __field(u8, cid)
			     __field(u8, tid)
			     __field(u8, type)
			     __field(u8, subtype)
			     __field(u16, seq)
			     __field(u8, mcs)
	    ),
	    TP_fast_assign(__entry->use_compressed = use_compressed;
			   __entry->buff_id = buff_id;
			   __entry->len = wil_rx_status_get_length(msg);
			   __entry->mid = wil_rx_status_get_mid(msg);
			   __entry->cid = wil_rx_status_get_cid(msg);
			   __entry->tid = wil_rx_status_get_tid(msg);
			   __entry->type = wil_rx_status_get_frame_type(wil,
									msg);
			   __entry->subtype = wil_rx_status_get_fc1(wil, msg);
			   __entry->seq = wil_rx_status_get_seq(wil, msg);
			   __entry->mcs = wil_rx_status_get_mcs(msg);
	    ),
	    TP_prपूर्णांकk(
		      "compressed %d buff_id %d len %d mid %d cid %d tid %d mcs %d seq 0x%03x type 0x%1x subtype 0x%1x",
		      __entry->use_compressed, __entry->buff_id, __entry->len,
		      __entry->mid, __entry->cid, __entry->tid, __entry->mcs,
		      __entry->seq, __entry->type, __entry->subtype)
);

TRACE_EVENT(wil6210_tx,
	TP_PROTO(u8 vring, u16 index, अचिन्हित पूर्णांक len, u8 frags),
	TP_ARGS(vring, index, len, frags),
	TP_STRUCT__entry(
		__field(u8, vring)
		__field(u8, frags)
		__field(u16, index)
		__field(अचिन्हित पूर्णांक, len)
	),
	TP_fast_assign(
		__entry->vring = vring;
		__entry->frags = frags;
		__entry->index = index;
		__entry->len = len;
	),
	TP_prपूर्णांकk("vring %d index %d len %d frags %d",
		  __entry->vring, __entry->index, __entry->len, __entry->frags)
);

TRACE_EVENT(wil6210_tx_करोne,
	TP_PROTO(u8 vring, u16 index, अचिन्हित पूर्णांक len, u8 err),
	TP_ARGS(vring, index, len, err),
	TP_STRUCT__entry(
		__field(u8, vring)
		__field(u8, err)
		__field(u16, index)
		__field(अचिन्हित पूर्णांक, len)
	),
	TP_fast_assign(
		__entry->vring = vring;
		__entry->index = index;
		__entry->len = len;
		__entry->err = err;
	),
	TP_prपूर्णांकk("vring %d index %d len %d err 0x%02x",
		  __entry->vring, __entry->index, __entry->len,
		  __entry->err)
);

TRACE_EVENT(wil6210_tx_status,
	    TP_PROTO(काष्ठा wil_ring_tx_status *msg, u16 index,
		     अचिन्हित पूर्णांक len),
	    TP_ARGS(msg, index, len),
	    TP_STRUCT__entry(__field(u16, index)
			     __field(अचिन्हित पूर्णांक, len)
			     __field(u8, num_descs)
			     __field(u8, ring_id)
			     __field(u8, status)
			     __field(u8, mcs)

	    ),
	    TP_fast_assign(__entry->index = index;
			   __entry->len = len;
			   __entry->num_descs = msg->num_descriptors;
			   __entry->ring_id = msg->ring_id;
			   __entry->status = msg->status;
			   __entry->mcs = wil_tx_status_get_mcs(msg);
	    ),
	    TP_prपूर्णांकk(
		      "ring_id %d swtail 0x%x len %d num_descs %d status 0x%x mcs %d",
		      __entry->ring_id, __entry->index, __entry->len,
		      __entry->num_descs, __entry->status, __entry->mcs)
);

#पूर्ण_अगर /* WIL6210_TRACE_H || TRACE_HEADER_MULTI_READ*/

#अगर defined(CONFIG_WIL6210_TRACING) && !defined(__CHECKER__)
/* we करोn't want to use include/trace/events */
#अघोषित TRACE_INCLUDE_PATH
#घोषणा TRACE_INCLUDE_PATH .
#अघोषित TRACE_INCLUDE_खाता
#घोषणा TRACE_INCLUDE_खाता trace

/* This part must be outside protection */
#समावेश <trace/define_trace.h>
#पूर्ण_अगर /* defined(CONFIG_WIL6210_TRACING) && !defined(__CHECKER__) */
