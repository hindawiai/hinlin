<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM emulation

#अगर !defined(_TRACE_EMULATION_H) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा _TRACE_EMULATION_H

#समावेश <linux/tracepoपूर्णांक.h>

TRACE_EVENT(inकाष्ठाion_emulation,

	TP_PROTO(स्थिर अक्षर *instr, u64 addr),
	TP_ARGS(instr, addr),

	TP_STRUCT__entry(
		__string(instr, instr)
		__field(u64, addr)
	),

	TP_fast_assign(
		__assign_str(instr, instr);
		__entry->addr = addr;
	),

	TP_prपूर्णांकk("instr=\"%s\" addr=0x%llx", __get_str(instr), __entry->addr)
);

#पूर्ण_अगर /* _TRACE_EMULATION_H */

/* This part must be outside protection */
#अघोषित TRACE_INCLUDE_PATH
#अघोषित TRACE_INCLUDE_खाता
#घोषणा TRACE_INCLUDE_PATH .

#घोषणा TRACE_INCLUDE_खाता trace-events-emulation
#समावेश <trace/define_trace.h>
