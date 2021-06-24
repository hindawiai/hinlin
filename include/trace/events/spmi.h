<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM spmi

#अगर !defined(_TRACE_SPMI_H) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा _TRACE_SPMI_H

#समावेश <linux/spmi.h>
#समावेश <linux/tracepoपूर्णांक.h>

/*
 * drivers/spmi/spmi.c
 */

TRACE_EVENT(spmi_ग_लिखो_begin,
	TP_PROTO(u8 opcode, u8 sid, u16 addr, u8 len, स्थिर u8 *buf),
	TP_ARGS(opcode, sid, addr, len, buf),

	TP_STRUCT__entry(
		__field		( u8,         opcode    )
		__field		( u8,         sid       )
		__field		( u16,        addr      )
		__field		( u8,         len       )
		__dynamic_array	( u8,   buf,  len + 1   )
	),

	TP_fast_assign(
		__entry->opcode = opcode;
		__entry->sid    = sid;
		__entry->addr   = addr;
		__entry->len    = len + 1;
		स_नकल(__get_dynamic_array(buf), buf, len + 1);
	),

	TP_prपूर्णांकk("opc=%d sid=%02d addr=0x%04x len=%d buf=0x[%*phD]",
		  (पूर्णांक)__entry->opcode, (पूर्णांक)__entry->sid,
		  (पूर्णांक)__entry->addr, (पूर्णांक)__entry->len,
		  (पूर्णांक)__entry->len, __get_dynamic_array(buf))
);

TRACE_EVENT(spmi_ग_लिखो_end,
	TP_PROTO(u8 opcode, u8 sid, u16 addr, पूर्णांक ret),
	TP_ARGS(opcode, sid, addr, ret),

	TP_STRUCT__entry(
		__field		( u8,         opcode    )
		__field		( u8,         sid       )
		__field		( u16,        addr      )
		__field		( पूर्णांक,        ret       )
	),

	TP_fast_assign(
		__entry->opcode = opcode;
		__entry->sid    = sid;
		__entry->addr   = addr;
		__entry->ret    = ret;
	),

	TP_prपूर्णांकk("opc=%d sid=%02d addr=0x%04x ret=%d",
		  (पूर्णांक)__entry->opcode, (पूर्णांक)__entry->sid,
		  (पूर्णांक)__entry->addr, __entry->ret)
);

TRACE_EVENT(spmi_पढ़ो_begin,
	TP_PROTO(u8 opcode, u8 sid, u16 addr),
	TP_ARGS(opcode, sid, addr),

	TP_STRUCT__entry(
		__field		( u8,         opcode    )
		__field		( u8,         sid       )
		__field		( u16,        addr      )
	),

	TP_fast_assign(
		__entry->opcode = opcode;
		__entry->sid    = sid;
		__entry->addr   = addr;
	),

	TP_prपूर्णांकk("opc=%d sid=%02d addr=0x%04x",
		  (पूर्णांक)__entry->opcode, (पूर्णांक)__entry->sid,
		  (पूर्णांक)__entry->addr)
);

TRACE_EVENT(spmi_पढ़ो_end,
	TP_PROTO(u8 opcode, u8 sid, u16 addr, पूर्णांक ret, u8 len, स्थिर u8 *buf),
	TP_ARGS(opcode, sid, addr, ret, len, buf),

	TP_STRUCT__entry(
		__field		( u8,         opcode    )
		__field		( u8,         sid       )
		__field		( u16,        addr      )
		__field		( पूर्णांक,        ret       )
		__field		( u8,         len       )
		__dynamic_array	( u8,   buf,  len + 1   )
	),

	TP_fast_assign(
		__entry->opcode = opcode;
		__entry->sid    = sid;
		__entry->addr   = addr;
		__entry->ret    = ret;
		__entry->len    = len + 1;
		स_नकल(__get_dynamic_array(buf), buf, len + 1);
	),

	TP_prपूर्णांकk("opc=%d sid=%02d addr=0x%04x ret=%d len=%02d buf=0x[%*phD]",
		  (पूर्णांक)__entry->opcode, (पूर्णांक)__entry->sid,
		  (पूर्णांक)__entry->addr, __entry->ret, (पूर्णांक)__entry->len,
		  (पूर्णांक)__entry->len, __get_dynamic_array(buf))
);

TRACE_EVENT(spmi_cmd,
	TP_PROTO(u8 opcode, u8 sid, पूर्णांक ret),
	TP_ARGS(opcode, sid, ret),

	TP_STRUCT__entry(
		__field		( u8,         opcode    )
		__field		( u8,         sid       )
		__field		( पूर्णांक,        ret       )
	),

	TP_fast_assign(
		__entry->opcode = opcode;
		__entry->sid    = sid;
		__entry->ret    = ret;
	),

	TP_prपूर्णांकk("opc=%d sid=%02d ret=%d", (पूर्णांक)__entry->opcode,
		  (पूर्णांक)__entry->sid, ret)
);

#पूर्ण_अगर /* _TRACE_SPMI_H */

/* This part must be outside protection */
#समावेश <trace/define_trace.h>
