<शैली गुरु>
/*
 * Copyright (c) 2011 Broadcom Corporation
 *
 * Permission to use, copy, modअगरy, and/or distribute this software क्रम any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY
 * SPECIAL, सूचीECT, INसूचीECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION
 * OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN
 * CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#अगर !defined(__TRACE_BRCMSMAC_MSG_H) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा __TRACE_BRCMSMAC_MSG_H

#समावेश <linux/tracepoपूर्णांक.h>

#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM brcmsmac_msg

#घोषणा MAX_MSG_LEN	100

DECLARE_EVENT_CLASS(brcms_msg_event,
	TP_PROTO(काष्ठा va_क्रमmat *vaf),
	TP_ARGS(vaf),
	TP_STRUCT__entry(
		__dynamic_array(अक्षर, msg, MAX_MSG_LEN)
	),
	TP_fast_assign(
		WARN_ON_ONCE(vsnम_लिखो(__get_dynamic_array(msg),
				       MAX_MSG_LEN, vaf->fmt,
				       *vaf->va) >= MAX_MSG_LEN);
	),
	TP_prपूर्णांकk("%s", __get_str(msg))
);

DEFINE_EVENT(brcms_msg_event, brcms_info,
	TP_PROTO(काष्ठा va_क्रमmat *vaf),
	TP_ARGS(vaf)
);

DEFINE_EVENT(brcms_msg_event, brcms_warn,
	TP_PROTO(काष्ठा va_क्रमmat *vaf),
	TP_ARGS(vaf)
);

DEFINE_EVENT(brcms_msg_event, brcms_err,
	TP_PROTO(काष्ठा va_क्रमmat *vaf),
	TP_ARGS(vaf)
);

DEFINE_EVENT(brcms_msg_event, brcms_crit,
	TP_PROTO(काष्ठा va_क्रमmat *vaf),
	TP_ARGS(vaf)
);

TRACE_EVENT(brcms_dbg,
	TP_PROTO(u32 level, स्थिर अक्षर *func, काष्ठा va_क्रमmat *vaf),
	TP_ARGS(level, func, vaf),
	TP_STRUCT__entry(
		__field(u32, level)
		__string(func, func)
		__dynamic_array(अक्षर, msg, MAX_MSG_LEN)
	),
	TP_fast_assign(
		__entry->level = level;
		__assign_str(func, func);
		WARN_ON_ONCE(vsnम_लिखो(__get_dynamic_array(msg),
				       MAX_MSG_LEN, vaf->fmt,
				       *vaf->va) >= MAX_MSG_LEN);
	),
	TP_prपूर्णांकk("%s: %s", __get_str(func), __get_str(msg))
);
#पूर्ण_अगर /* __TRACE_BRCMSMAC_MSG_H */

#अगर_घोषित CONFIG_BRCM_TRACING

#अघोषित TRACE_INCLUDE_PATH
#घोषणा TRACE_INCLUDE_PATH .
#अघोषित TRACE_INCLUDE_खाता
#घोषणा TRACE_INCLUDE_खाता brcms_trace_brcmsmac_msg
#समावेश <trace/define_trace.h>

#पूर्ण_अगर /* CONFIG_BRCM_TRACING */
