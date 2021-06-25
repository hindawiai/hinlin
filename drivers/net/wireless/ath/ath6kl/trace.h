<शैली गुरु>
/* SPDX-License-Identअगरier: ISC */
#अगर !defined(_ATH6KL_TRACE_H) || defined(TRACE_HEADER_MULTI_READ)

#समावेश <net/cfg80211.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/tracepoपूर्णांक.h>
#समावेश "wmi.h"
#समावेश "hif.h"

#अगर !defined(_ATH6KL_TRACE_H)
अटल अंतरभूत अचिन्हित पूर्णांक ath6kl_get_wmi_id(व्योम *buf, माप_प्रकार buf_len)
अणु
	काष्ठा wmi_cmd_hdr *hdr = buf;

	अगर (buf_len < माप(*hdr))
		वापस 0;

	वापस le16_to_cpu(hdr->cmd_id);
पूर्ण
#पूर्ण_अगर /* __ATH6KL_TRACE_H */

#घोषणा _ATH6KL_TRACE_H

/* create empty functions when tracing is disabled */
#अगर !defined(CONFIG_ATH6KL_TRACING)
#अघोषित TRACE_EVENT
#घोषणा TRACE_EVENT(name, proto, ...) \
अटल अंतरभूत व्योम trace_ ## name(proto) अणुपूर्ण
#अघोषित DECLARE_EVENT_CLASS
#घोषणा DECLARE_EVENT_CLASS(...)
#अघोषित DEFINE_EVENT
#घोषणा DEFINE_EVENT(evt_class, name, proto, ...) \
अटल अंतरभूत व्योम trace_ ## name(proto) अणुपूर्ण
#पूर्ण_अगर /* !CONFIG_ATH6KL_TRACING || __CHECKER__ */

#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM ath6kl

TRACE_EVENT(ath6kl_wmi_cmd,
	TP_PROTO(व्योम *buf, माप_प्रकार buf_len),

	TP_ARGS(buf, buf_len),

	TP_STRUCT__entry(
		__field(अचिन्हित पूर्णांक, id)
		__field(माप_प्रकार, buf_len)
		__dynamic_array(u8, buf, buf_len)
	),

	TP_fast_assign(
		__entry->id = ath6kl_get_wmi_id(buf, buf_len);
		__entry->buf_len = buf_len;
		स_नकल(__get_dynamic_array(buf), buf, buf_len);
	),

	TP_prपूर्णांकk(
		"id %d len %zd",
		__entry->id, __entry->buf_len
	)
);

TRACE_EVENT(ath6kl_wmi_event,
	TP_PROTO(व्योम *buf, माप_प्रकार buf_len),

	TP_ARGS(buf, buf_len),

	TP_STRUCT__entry(
		__field(अचिन्हित पूर्णांक, id)
		__field(माप_प्रकार, buf_len)
		__dynamic_array(u8, buf, buf_len)
	),

	TP_fast_assign(
		__entry->id = ath6kl_get_wmi_id(buf, buf_len);
		__entry->buf_len = buf_len;
		स_नकल(__get_dynamic_array(buf), buf, buf_len);
	),

	TP_prपूर्णांकk(
		"id %d len %zd",
		__entry->id, __entry->buf_len
	)
);

TRACE_EVENT(ath6kl_sdio,
	TP_PROTO(अचिन्हित पूर्णांक addr, पूर्णांक flags,
		 व्योम *buf, माप_प्रकार buf_len),

	TP_ARGS(addr, flags, buf, buf_len),

	TP_STRUCT__entry(
		__field(अचिन्हित पूर्णांक, tx)
		__field(अचिन्हित पूर्णांक, addr)
		__field(पूर्णांक, flags)
		__field(माप_प्रकार, buf_len)
		__dynamic_array(u8, buf, buf_len)
	),

	TP_fast_assign(
		__entry->addr = addr;
		__entry->flags = flags;
		__entry->buf_len = buf_len;
		स_नकल(__get_dynamic_array(buf), buf, buf_len);

		अगर (flags & HIF_WRITE)
			__entry->tx = 1;
		अन्यथा
			__entry->tx = 0;
	),

	TP_prपूर्णांकk(
		"%s addr 0x%x flags 0x%x len %zd\n",
		__entry->tx ? "tx" : "rx",
		__entry->addr,
		__entry->flags,
		__entry->buf_len
	)
);

TRACE_EVENT(ath6kl_sdio_scat,
	TP_PROTO(अचिन्हित पूर्णांक addr, पूर्णांक flags, अचिन्हित पूर्णांक total_len,
		 अचिन्हित पूर्णांक entries, काष्ठा hअगर_scatter_item *list),

	TP_ARGS(addr, flags, total_len, entries, list),

	TP_STRUCT__entry(
		__field(अचिन्हित पूर्णांक, tx)
		__field(अचिन्हित पूर्णांक, addr)
		__field(पूर्णांक, flags)
		__field(अचिन्हित पूर्णांक, entries)
		__field(माप_प्रकार, total_len)
		__dynamic_array(अचिन्हित पूर्णांक, len_array, entries)
		__dynamic_array(u8, data, total_len)
	),

	TP_fast_assign(
		अचिन्हित पूर्णांक *len_array;
		पूर्णांक i, offset = 0;
		माप_प्रकार len;

		__entry->addr = addr;
		__entry->flags = flags;
		__entry->entries = entries;
		__entry->total_len = total_len;

		अगर (flags & HIF_WRITE)
			__entry->tx = 1;
		अन्यथा
			__entry->tx = 0;

		len_array = __get_dynamic_array(len_array);

		क्रम (i = 0; i < entries; i++) अणु
			len = list[i].len;

			स_नकल((u8 *) __get_dynamic_array(data) + offset,
			       list[i].buf, len);

			len_array[i] = len;
			offset += len;
		पूर्ण
	),

	TP_prपूर्णांकk(
		"%s addr 0x%x flags 0x%x entries %d total_len %zd\n",
		__entry->tx ? "tx" : "rx",
		__entry->addr,
		__entry->flags,
		__entry->entries,
		__entry->total_len
	)
);

TRACE_EVENT(ath6kl_sdio_irq,
	TP_PROTO(व्योम *buf, माप_प्रकार buf_len),

	TP_ARGS(buf, buf_len),

	TP_STRUCT__entry(
		__field(माप_प्रकार, buf_len)
		__dynamic_array(u8, buf, buf_len)
	),

	TP_fast_assign(
		__entry->buf_len = buf_len;
		स_नकल(__get_dynamic_array(buf), buf, buf_len);
	),

	TP_prपूर्णांकk(
		"irq len %zd\n", __entry->buf_len
	)
);

TRACE_EVENT(ath6kl_htc_rx,
	TP_PROTO(पूर्णांक status, पूर्णांक endpoपूर्णांक, व्योम *buf,
		 माप_प्रकार buf_len),

	TP_ARGS(status, endpoपूर्णांक, buf, buf_len),

	TP_STRUCT__entry(
		__field(पूर्णांक, status)
		__field(पूर्णांक, endpoपूर्णांक)
		__field(माप_प्रकार, buf_len)
		__dynamic_array(u8, buf, buf_len)
	),

	TP_fast_assign(
		__entry->status = status;
		__entry->endpoपूर्णांक = endpoपूर्णांक;
		__entry->buf_len = buf_len;
		स_नकल(__get_dynamic_array(buf), buf, buf_len);
	),

	TP_prपूर्णांकk(
		"status %d endpoint %d len %zd\n",
		__entry->status,
		__entry->endpoपूर्णांक,
		__entry->buf_len
	)
);

TRACE_EVENT(ath6kl_htc_tx,
	TP_PROTO(पूर्णांक status, पूर्णांक endpoपूर्णांक, व्योम *buf,
		 माप_प्रकार buf_len),

	TP_ARGS(status, endpoपूर्णांक, buf, buf_len),

	TP_STRUCT__entry(
		__field(पूर्णांक, status)
		__field(पूर्णांक, endpoपूर्णांक)
		__field(माप_प्रकार, buf_len)
		__dynamic_array(u8, buf, buf_len)
	),

	TP_fast_assign(
		__entry->status = status;
		__entry->endpoपूर्णांक = endpoपूर्णांक;
		__entry->buf_len = buf_len;
		स_नकल(__get_dynamic_array(buf), buf, buf_len);
	),

	TP_prपूर्णांकk(
		"status %d endpoint %d len %zd\n",
		__entry->status,
		__entry->endpoपूर्णांक,
		__entry->buf_len
	)
);

#घोषणा ATH6KL_MSG_MAX 200

DECLARE_EVENT_CLASS(ath6kl_log_event,
	TP_PROTO(काष्ठा va_क्रमmat *vaf),
	TP_ARGS(vaf),
	TP_STRUCT__entry(
		__dynamic_array(अक्षर, msg, ATH6KL_MSG_MAX)
	),
	TP_fast_assign(
		WARN_ON_ONCE(vsnम_लिखो(__get_dynamic_array(msg),
				       ATH6KL_MSG_MAX,
				       vaf->fmt,
				       *vaf->va) >= ATH6KL_MSG_MAX);
	),
	TP_prपूर्णांकk("%s", __get_str(msg))
);

DEFINE_EVENT(ath6kl_log_event, ath6kl_log_err,
	     TP_PROTO(काष्ठा va_क्रमmat *vaf),
	     TP_ARGS(vaf)
);

DEFINE_EVENT(ath6kl_log_event, ath6kl_log_warn,
	     TP_PROTO(काष्ठा va_क्रमmat *vaf),
	     TP_ARGS(vaf)
);

DEFINE_EVENT(ath6kl_log_event, ath6kl_log_info,
	     TP_PROTO(काष्ठा va_क्रमmat *vaf),
	     TP_ARGS(vaf)
);

TRACE_EVENT(ath6kl_log_dbg,
	TP_PROTO(अचिन्हित पूर्णांक level, काष्ठा va_क्रमmat *vaf),
	TP_ARGS(level, vaf),
	TP_STRUCT__entry(
		__field(अचिन्हित पूर्णांक, level)
		__dynamic_array(अक्षर, msg, ATH6KL_MSG_MAX)
	),
	TP_fast_assign(
		__entry->level = level;
		WARN_ON_ONCE(vsnम_लिखो(__get_dynamic_array(msg),
				       ATH6KL_MSG_MAX,
				       vaf->fmt,
				       *vaf->va) >= ATH6KL_MSG_MAX);
	),
	TP_prपूर्णांकk("%s", __get_str(msg))
);

TRACE_EVENT(ath6kl_log_dbg_dump,
	TP_PROTO(स्थिर अक्षर *msg, स्थिर अक्षर *prefix,
		 स्थिर व्योम *buf, माप_प्रकार buf_len),

	TP_ARGS(msg, prefix, buf, buf_len),

	TP_STRUCT__entry(
		__string(msg, msg)
		__string(prefix, prefix)
		__field(माप_प्रकार, buf_len)
		__dynamic_array(u8, buf, buf_len)
	),

	TP_fast_assign(
		__assign_str(msg, msg);
		__assign_str(prefix, prefix);
		__entry->buf_len = buf_len;
		स_नकल(__get_dynamic_array(buf), buf, buf_len);
	),

	TP_prपूर्णांकk(
		"%s/%s\n", __get_str(prefix), __get_str(msg)
	)
);

#पूर्ण_अगर /* _ ATH6KL_TRACE_H || TRACE_HEADER_MULTI_READ*/

/* we करोn't want to use include/trace/events */
#अघोषित TRACE_INCLUDE_PATH
#घोषणा TRACE_INCLUDE_PATH .
#अघोषित TRACE_INCLUDE_खाता
#घोषणा TRACE_INCLUDE_खाता trace

/* This part must be outside protection */
#समावेश <trace/define_trace.h>
