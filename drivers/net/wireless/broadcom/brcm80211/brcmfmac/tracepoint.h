<शैली गुरु>
// SPDX-License-Identअगरier: ISC
/*
 * Copyright (c) 2013 Broadcom Corporation
 */
#अगर !defined(BRCMF_TRACEPOINT_H_) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा BRCMF_TRACEPOINT_H_

#समावेश <linux/types.h>
#समावेश <linux/tracepoपूर्णांक.h>

#अगर_अघोषित CONFIG_BRCM_TRACING

#अघोषित TRACE_EVENT
#घोषणा TRACE_EVENT(name, proto, ...) \
अटल अंतरभूत व्योम trace_ ## name(proto) अणुपूर्ण

#अघोषित DECLARE_EVENT_CLASS
#घोषणा DECLARE_EVENT_CLASS(...)

#अघोषित DEFINE_EVENT
#घोषणा DEFINE_EVENT(evt_class, name, proto, ...) \
अटल अंतरभूत व्योम trace_ ## name(proto) अणुपूर्ण

#पूर्ण_अगर /* CONFIG_BRCM_TRACING */

#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM	brcmfmac

#घोषणा MAX_MSG_LEN		100

TRACE_EVENT(brcmf_err,
	TP_PROTO(स्थिर अक्षर *func, काष्ठा va_क्रमmat *vaf),
	TP_ARGS(func, vaf),
	TP_STRUCT__entry(
		__string(func, func)
		__dynamic_array(अक्षर, msg, MAX_MSG_LEN)
	),
	TP_fast_assign(
		__assign_str(func, func);
		WARN_ON_ONCE(vsnम_लिखो(__get_dynamic_array(msg),
				       MAX_MSG_LEN, vaf->fmt,
				       *vaf->va) >= MAX_MSG_LEN);
	),
	TP_prपूर्णांकk("%s: %s", __get_str(func), __get_str(msg))
);

TRACE_EVENT(brcmf_dbg,
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

TRACE_EVENT(brcmf_hexdump,
	TP_PROTO(व्योम *data, माप_प्रकार len),
	TP_ARGS(data, len),
	TP_STRUCT__entry(
		__field(अचिन्हित दीर्घ, len)
		__field(अचिन्हित दीर्घ, addr)
		__dynamic_array(u8, hdata, len)
	),
	TP_fast_assign(
		__entry->len = len;
		__entry->addr = (अचिन्हित दीर्घ)data;
		स_नकल(__get_dynamic_array(hdata), data, len);
	),
	TP_prपूर्णांकk("hexdump [addr=%lx, length=%lu]", __entry->addr, __entry->len)
);

TRACE_EVENT(brcmf_bcdchdr,
	TP_PROTO(व्योम *data),
	TP_ARGS(data),
	TP_STRUCT__entry(
		__field(u8, flags)
		__field(u8, prio)
		__field(u8, flags2)
		__field(u32, siglen)
		__dynamic_array(u8, संकेत, *((u8 *)data + 3) * 4)
	),
	TP_fast_assign(
		__entry->flags = *(u8 *)data;
		__entry->prio = *((u8 *)data + 1);
		__entry->flags2 = *((u8 *)data + 2);
		__entry->siglen = *((u8 *)data + 3) * 4;
		स_नकल(__get_dynamic_array(संकेत),
		       (u8 *)data + 4, __entry->siglen);
	),
	TP_prपूर्णांकk("bcdc: prio=%d siglen=%d", __entry->prio, __entry->siglen)
);

#अगर_अघोषित SDPCM_RX
#घोषणा SDPCM_RX	0
#पूर्ण_अगर
#अगर_अघोषित SDPCM_TX
#घोषणा SDPCM_TX	1
#पूर्ण_अगर
#अगर_अघोषित SDPCM_GLOM
#घोषणा SDPCM_GLOM	2
#पूर्ण_अगर

TRACE_EVENT(brcmf_sdpcm_hdr,
	TP_PROTO(u8 dir, व्योम *data),
	TP_ARGS(dir, data),
	TP_STRUCT__entry(
		__field(u8, dir)
		__field(u16, len)
		__dynamic_array(u8, hdr, dir == SDPCM_GLOM ? 20 : 12)
	),
	TP_fast_assign(
		स_नकल(__get_dynamic_array(hdr), data, dir == SDPCM_GLOM ? 20 : 12);
		__entry->len = *(u8 *)data | (*((u8 *)data + 1) << 8);
		__entry->dir = dir;
	),
	TP_prपूर्णांकk("sdpcm: %s len %u, seq %d",
		  __entry->dir == SDPCM_RX ? "RX" : "TX",
		  __entry->len, ((u8 *)__get_dynamic_array(hdr))[4])
);

#अगर_घोषित CONFIG_BRCM_TRACING

#अघोषित TRACE_INCLUDE_PATH
#घोषणा TRACE_INCLUDE_PATH .
#अघोषित TRACE_INCLUDE_खाता
#घोषणा TRACE_INCLUDE_खाता tracepoपूर्णांक

#समावेश <trace/define_trace.h>

#पूर्ण_अगर /* CONFIG_BRCM_TRACING */

#पूर्ण_अगर /* BRCMF_TRACEPOINT_H_ */
