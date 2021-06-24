<शैली गुरु>
/* SPDX-License-Identअगरier: ISC */
/*
 * Copyright (c) 2005-2011 Atheros Communications Inc.
 * Copyright (c) 2011-2016 Qualcomm Atheros, Inc.
 */

#अगर !defined(_TRACE_H_) || defined(TRACE_HEADER_MULTI_READ)

#समावेश <linux/tracepoपूर्णांक.h>
#समावेश "core.h"

#अगर !defined(_TRACE_H_)
अटल अंतरभूत u32 ath10k_frm_hdr_len(स्थिर व्योम *buf, माप_प्रकार len)
अणु
	स्थिर काष्ठा ieee80211_hdr *hdr = buf;

	/* In some rare हालs (e.g. fcs error) device reports frame buffer
	 * लघुer than what frame header implies (e.g. len = 0). The buffer
	 * can still be accessed so करो a simple min() to guarantee caller
	 * करोesn't get value greater than len.
	 */
	वापस min_t(u32, len, ieee80211_hdrlen(hdr->frame_control));
पूर्ण
#पूर्ण_अगर

#घोषणा _TRACE_H_

/* create empty functions when tracing is disabled */
#अगर !defined(CONFIG_ATH10K_TRACING)
#अघोषित TRACE_EVENT
#घोषणा TRACE_EVENT(name, proto, ...) \
अटल अंतरभूत व्योम trace_ ## name(proto) अणुपूर्ण \
अटल अंतरभूत bool trace_##name##_enabled(व्योम) \
अणु						\
	वापस false;				\
पूर्ण
#अघोषित DECLARE_EVENT_CLASS
#घोषणा DECLARE_EVENT_CLASS(...)
#अघोषित DEFINE_EVENT
#घोषणा DEFINE_EVENT(evt_class, name, proto, ...) \
अटल अंतरभूत व्योम trace_ ## name(proto) अणुपूर्ण
#पूर्ण_अगर /* !CONFIG_ATH10K_TRACING || __CHECKER__ */

#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM ath10k

#घोषणा ATH10K_MSG_MAX 400

DECLARE_EVENT_CLASS(ath10k_log_event,
	TP_PROTO(काष्ठा ath10k *ar, काष्ठा va_क्रमmat *vaf),
	TP_ARGS(ar, vaf),
	TP_STRUCT__entry(
		__string(device, dev_name(ar->dev))
		__string(driver, dev_driver_string(ar->dev))
		__dynamic_array(अक्षर, msg, ATH10K_MSG_MAX)
	),
	TP_fast_assign(
		__assign_str(device, dev_name(ar->dev));
		__assign_str(driver, dev_driver_string(ar->dev));
		WARN_ON_ONCE(vsnम_लिखो(__get_dynamic_array(msg),
				       ATH10K_MSG_MAX,
				       vaf->fmt,
				       *vaf->va) >= ATH10K_MSG_MAX);
	),
	TP_prपूर्णांकk(
		"%s %s %s",
		__get_str(driver),
		__get_str(device),
		__get_str(msg)
	)
);

DEFINE_EVENT(ath10k_log_event, ath10k_log_err,
	     TP_PROTO(काष्ठा ath10k *ar, काष्ठा va_क्रमmat *vaf),
	     TP_ARGS(ar, vaf)
);

DEFINE_EVENT(ath10k_log_event, ath10k_log_warn,
	     TP_PROTO(काष्ठा ath10k *ar, काष्ठा va_क्रमmat *vaf),
	     TP_ARGS(ar, vaf)
);

DEFINE_EVENT(ath10k_log_event, ath10k_log_info,
	     TP_PROTO(काष्ठा ath10k *ar, काष्ठा va_क्रमmat *vaf),
	     TP_ARGS(ar, vaf)
);

TRACE_EVENT(ath10k_log_dbg,
	TP_PROTO(काष्ठा ath10k *ar, अचिन्हित पूर्णांक level, काष्ठा va_क्रमmat *vaf),
	TP_ARGS(ar, level, vaf),
	TP_STRUCT__entry(
		__string(device, dev_name(ar->dev))
		__string(driver, dev_driver_string(ar->dev))
		__field(अचिन्हित पूर्णांक, level)
		__dynamic_array(अक्षर, msg, ATH10K_MSG_MAX)
	),
	TP_fast_assign(
		__assign_str(device, dev_name(ar->dev));
		__assign_str(driver, dev_driver_string(ar->dev));
		__entry->level = level;
		WARN_ON_ONCE(vsnम_लिखो(__get_dynamic_array(msg),
				       ATH10K_MSG_MAX,
				       vaf->fmt,
				       *vaf->va) >= ATH10K_MSG_MAX);
	),
	TP_prपूर्णांकk(
		"%s %s %s",
		__get_str(driver),
		__get_str(device),
		__get_str(msg)
	)
);

TRACE_EVENT(ath10k_log_dbg_dump,
	TP_PROTO(काष्ठा ath10k *ar, स्थिर अक्षर *msg, स्थिर अक्षर *prefix,
		 स्थिर व्योम *buf, माप_प्रकार buf_len),

	TP_ARGS(ar, msg, prefix, buf, buf_len),

	TP_STRUCT__entry(
		__string(device, dev_name(ar->dev))
		__string(driver, dev_driver_string(ar->dev))
		__string(msg, msg)
		__string(prefix, prefix)
		__field(माप_प्रकार, buf_len)
		__dynamic_array(u8, buf, buf_len)
	),

	TP_fast_assign(
		__assign_str(device, dev_name(ar->dev));
		__assign_str(driver, dev_driver_string(ar->dev));
		__assign_str(msg, msg);
		__assign_str(prefix, prefix);
		__entry->buf_len = buf_len;
		स_नकल(__get_dynamic_array(buf), buf, buf_len);
	),

	TP_prपूर्णांकk(
		"%s %s %s/%s\n",
		__get_str(driver),
		__get_str(device),
		__get_str(prefix),
		__get_str(msg)
	)
);

TRACE_EVENT(ath10k_wmi_cmd,
	TP_PROTO(काष्ठा ath10k *ar, पूर्णांक id, स्थिर व्योम *buf, माप_प्रकार buf_len),

	TP_ARGS(ar, id, buf, buf_len),

	TP_STRUCT__entry(
		__string(device, dev_name(ar->dev))
		__string(driver, dev_driver_string(ar->dev))
		__field(अचिन्हित पूर्णांक, id)
		__field(माप_प्रकार, buf_len)
		__dynamic_array(u8, buf, buf_len)
	),

	TP_fast_assign(
		__assign_str(device, dev_name(ar->dev));
		__assign_str(driver, dev_driver_string(ar->dev));
		__entry->id = id;
		__entry->buf_len = buf_len;
		स_नकल(__get_dynamic_array(buf), buf, buf_len);
	),

	TP_prपूर्णांकk(
		"%s %s id %d len %zu",
		__get_str(driver),
		__get_str(device),
		__entry->id,
		__entry->buf_len
	)
);

TRACE_EVENT(ath10k_wmi_event,
	TP_PROTO(काष्ठा ath10k *ar, पूर्णांक id, स्थिर व्योम *buf, माप_प्रकार buf_len),

	TP_ARGS(ar, id, buf, buf_len),

	TP_STRUCT__entry(
		__string(device, dev_name(ar->dev))
		__string(driver, dev_driver_string(ar->dev))
		__field(अचिन्हित पूर्णांक, id)
		__field(माप_प्रकार, buf_len)
		__dynamic_array(u8, buf, buf_len)
	),

	TP_fast_assign(
		__assign_str(device, dev_name(ar->dev));
		__assign_str(driver, dev_driver_string(ar->dev));
		__entry->id = id;
		__entry->buf_len = buf_len;
		स_नकल(__get_dynamic_array(buf), buf, buf_len);
	),

	TP_prपूर्णांकk(
		"%s %s id %d len %zu",
		__get_str(driver),
		__get_str(device),
		__entry->id,
		__entry->buf_len
	)
);

TRACE_EVENT(ath10k_htt_stats,
	TP_PROTO(काष्ठा ath10k *ar, स्थिर व्योम *buf, माप_प्रकार buf_len),

	TP_ARGS(ar, buf, buf_len),

	TP_STRUCT__entry(
		__string(device, dev_name(ar->dev))
		__string(driver, dev_driver_string(ar->dev))
		__field(माप_प्रकार, buf_len)
		__dynamic_array(u8, buf, buf_len)
	),

	TP_fast_assign(
		__assign_str(device, dev_name(ar->dev));
		__assign_str(driver, dev_driver_string(ar->dev));
		__entry->buf_len = buf_len;
		स_नकल(__get_dynamic_array(buf), buf, buf_len);
	),

	TP_prपूर्णांकk(
		"%s %s len %zu",
		__get_str(driver),
		__get_str(device),
		__entry->buf_len
	)
);

TRACE_EVENT(ath10k_wmi_dbglog,
	TP_PROTO(काष्ठा ath10k *ar, स्थिर व्योम *buf, माप_प्रकार buf_len),

	TP_ARGS(ar, buf, buf_len),

	TP_STRUCT__entry(
		__string(device, dev_name(ar->dev))
		__string(driver, dev_driver_string(ar->dev))
		__field(u8, hw_type)
		__field(माप_प्रकार, buf_len)
		__dynamic_array(u8, buf, buf_len)
	),

	TP_fast_assign(
		__assign_str(device, dev_name(ar->dev));
		__assign_str(driver, dev_driver_string(ar->dev));
		__entry->hw_type = ar->hw_rev;
		__entry->buf_len = buf_len;
		स_नकल(__get_dynamic_array(buf), buf, buf_len);
	),

	TP_prपूर्णांकk(
		"%s %s %d len %zu",
		__get_str(driver),
		__get_str(device),
		__entry->hw_type,
		__entry->buf_len
	)
);

TRACE_EVENT(ath10k_htt_pktlog,
	    TP_PROTO(काष्ठा ath10k *ar, स्थिर व्योम *buf, u16 buf_len),

	TP_ARGS(ar, buf, buf_len),

	TP_STRUCT__entry(
		__string(device, dev_name(ar->dev))
		__string(driver, dev_driver_string(ar->dev))
		__field(u8, hw_type)
		__field(u16, buf_len)
		__dynamic_array(u8, pktlog, buf_len)
	),

	TP_fast_assign(
		__assign_str(device, dev_name(ar->dev));
		__assign_str(driver, dev_driver_string(ar->dev));
		__entry->hw_type = ar->hw_rev;
		__entry->buf_len = buf_len;
		स_नकल(__get_dynamic_array(pktlog), buf, buf_len);
	),

	TP_prपूर्णांकk(
		"%s %s %d size %u",
		__get_str(driver),
		__get_str(device),
		__entry->hw_type,
		__entry->buf_len
	 )
);

TRACE_EVENT(ath10k_htt_tx,
	    TP_PROTO(काष्ठा ath10k *ar, u16 msdu_id, u16 msdu_len,
		     u8 vdev_id, u8 tid),

	TP_ARGS(ar, msdu_id, msdu_len, vdev_id, tid),

	TP_STRUCT__entry(
		__string(device, dev_name(ar->dev))
		__string(driver, dev_driver_string(ar->dev))
		__field(u16, msdu_id)
		__field(u16, msdu_len)
		__field(u8, vdev_id)
		__field(u8, tid)
	),

	TP_fast_assign(
		__assign_str(device, dev_name(ar->dev));
		__assign_str(driver, dev_driver_string(ar->dev));
		__entry->msdu_id = msdu_id;
		__entry->msdu_len = msdu_len;
		__entry->vdev_id = vdev_id;
		__entry->tid = tid;
	),

	TP_prपूर्णांकk(
		"%s %s msdu_id %d msdu_len %d vdev_id %d tid %d",
		__get_str(driver),
		__get_str(device),
		__entry->msdu_id,
		__entry->msdu_len,
		__entry->vdev_id,
		__entry->tid
	 )
);

TRACE_EVENT(ath10k_txrx_tx_unref,
	    TP_PROTO(काष्ठा ath10k *ar, u16 msdu_id),

	TP_ARGS(ar, msdu_id),

	TP_STRUCT__entry(
		__string(device, dev_name(ar->dev))
		__string(driver, dev_driver_string(ar->dev))
		__field(u16, msdu_id)
	),

	TP_fast_assign(
		__assign_str(device, dev_name(ar->dev));
		__assign_str(driver, dev_driver_string(ar->dev));
		__entry->msdu_id = msdu_id;
	),

	TP_prपूर्णांकk(
		"%s %s msdu_id %d",
		__get_str(driver),
		__get_str(device),
		__entry->msdu_id
	 )
);

DECLARE_EVENT_CLASS(ath10k_hdr_event,
		    TP_PROTO(काष्ठा ath10k *ar, स्थिर व्योम *data, माप_प्रकार len),

	TP_ARGS(ar, data, len),

	TP_STRUCT__entry(
		__string(device, dev_name(ar->dev))
		__string(driver, dev_driver_string(ar->dev))
		__field(माप_प्रकार, len)
		__dynamic_array(u8, data, ath10k_frm_hdr_len(data, len))
	),

	TP_fast_assign(
		__assign_str(device, dev_name(ar->dev));
		__assign_str(driver, dev_driver_string(ar->dev));
		__entry->len = ath10k_frm_hdr_len(data, len);
		स_नकल(__get_dynamic_array(data), data, __entry->len);
	),

	TP_prपूर्णांकk(
		"%s %s len %zu\n",
		__get_str(driver),
		__get_str(device),
		__entry->len
	)
);

DECLARE_EVENT_CLASS(ath10k_payload_event,
		    TP_PROTO(काष्ठा ath10k *ar, स्थिर व्योम *data, माप_प्रकार len),

	TP_ARGS(ar, data, len),

	TP_STRUCT__entry(
		__string(device, dev_name(ar->dev))
		__string(driver, dev_driver_string(ar->dev))
		__field(माप_प्रकार, len)
		__dynamic_array(u8, payload, (len -
					      ath10k_frm_hdr_len(data, len)))
	),

	TP_fast_assign(
		__assign_str(device, dev_name(ar->dev));
		__assign_str(driver, dev_driver_string(ar->dev));
		__entry->len = len - ath10k_frm_hdr_len(data, len);
		स_नकल(__get_dynamic_array(payload),
		       data + ath10k_frm_hdr_len(data, len), __entry->len);
	),

	TP_prपूर्णांकk(
		"%s %s len %zu\n",
		__get_str(driver),
		__get_str(device),
		__entry->len
	)
);

DEFINE_EVENT(ath10k_hdr_event, ath10k_tx_hdr,
	     TP_PROTO(काष्ठा ath10k *ar, स्थिर व्योम *data, माप_प्रकार len),
	     TP_ARGS(ar, data, len)
);

DEFINE_EVENT(ath10k_payload_event, ath10k_tx_payload,
	     TP_PROTO(काष्ठा ath10k *ar, स्थिर व्योम *data, माप_प्रकार len),
	     TP_ARGS(ar, data, len)
);

DEFINE_EVENT(ath10k_hdr_event, ath10k_rx_hdr,
	     TP_PROTO(काष्ठा ath10k *ar, स्थिर व्योम *data, माप_प्रकार len),
	     TP_ARGS(ar, data, len)
);

DEFINE_EVENT(ath10k_payload_event, ath10k_rx_payload,
	     TP_PROTO(काष्ठा ath10k *ar, स्थिर व्योम *data, माप_प्रकार len),
	     TP_ARGS(ar, data, len)
);

TRACE_EVENT(ath10k_htt_rx_desc,
	    TP_PROTO(काष्ठा ath10k *ar, स्थिर व्योम *data, माप_प्रकार len),

	TP_ARGS(ar, data, len),

	TP_STRUCT__entry(
		__string(device, dev_name(ar->dev))
		__string(driver, dev_driver_string(ar->dev))
		__field(u8, hw_type)
		__field(u16, len)
		__dynamic_array(u8, rxdesc, len)
	),

	TP_fast_assign(
		__assign_str(device, dev_name(ar->dev));
		__assign_str(driver, dev_driver_string(ar->dev));
		__entry->hw_type = ar->hw_rev;
		__entry->len = len;
		स_नकल(__get_dynamic_array(rxdesc), data, len);
	),

	TP_prपूर्णांकk(
		"%s %s %d rxdesc len %d",
		__get_str(driver),
		__get_str(device),
		__entry->hw_type,
		__entry->len
	 )
);

TRACE_EVENT(ath10k_wmi_diag_container,
	    TP_PROTO(काष्ठा ath10k *ar,
		     u8 type,
		     u32 बारtamp,
		     u32 code,
		     u16 len,
		     स्थिर व्योम *data),

	TP_ARGS(ar, type, बारtamp, code, len, data),

	TP_STRUCT__entry(
		__string(device, dev_name(ar->dev))
		__string(driver, dev_driver_string(ar->dev))
		__field(u8, type)
		__field(u32, बारtamp)
		__field(u32, code)
		__field(u16, len)
		__dynamic_array(u8, data, len)
	),

	TP_fast_assign(
		__assign_str(device, dev_name(ar->dev));
		__assign_str(driver, dev_driver_string(ar->dev));
		__entry->type = type;
		__entry->बारtamp = बारtamp;
		__entry->code = code;
		__entry->len = len;
		स_नकल(__get_dynamic_array(data), data, len);
	),

	TP_prपूर्णांकk(
		"%s %s diag container type %u timestamp %u code %u len %d",
		__get_str(driver),
		__get_str(device),
		__entry->type,
		__entry->बारtamp,
		__entry->code,
		__entry->len
	)
);

TRACE_EVENT(ath10k_wmi_diag,
	    TP_PROTO(काष्ठा ath10k *ar, स्थिर व्योम *data, माप_प्रकार len),

	TP_ARGS(ar, data, len),

	TP_STRUCT__entry(
		__string(device, dev_name(ar->dev))
		__string(driver, dev_driver_string(ar->dev))
		__field(u16, len)
		__dynamic_array(u8, data, len)
	),

	TP_fast_assign(
		__assign_str(device, dev_name(ar->dev));
		__assign_str(driver, dev_driver_string(ar->dev));
		__entry->len = len;
		स_नकल(__get_dynamic_array(data), data, len);
	),

	TP_prपूर्णांकk(
		"%s %s tlv diag len %d",
		__get_str(driver),
		__get_str(device),
		__entry->len
	)
);

#पूर्ण_अगर /* _TRACE_H_ || TRACE_HEADER_MULTI_READ*/

/* we करोn't want to use include/trace/events */
#अघोषित TRACE_INCLUDE_PATH
#घोषणा TRACE_INCLUDE_PATH .
#अघोषित TRACE_INCLUDE_खाता
#घोषणा TRACE_INCLUDE_खाता trace

/* This part must be outside protection */
#समावेश <trace/define_trace.h>
