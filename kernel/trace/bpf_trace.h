<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM bpf_trace

#अगर !defined(_TRACE_BPF_TRACE_H) || defined(TRACE_HEADER_MULTI_READ)

#घोषणा _TRACE_BPF_TRACE_H

#समावेश <linux/tracepoपूर्णांक.h>

TRACE_EVENT(bpf_trace_prपूर्णांकk,

	TP_PROTO(स्थिर अक्षर *bpf_string),

	TP_ARGS(bpf_string),

	TP_STRUCT__entry(
		__string(bpf_string, bpf_string)
	),

	TP_fast_assign(
		__assign_str(bpf_string, bpf_string);
	),

	TP_prपूर्णांकk("%s", __get_str(bpf_string))
);

#पूर्ण_अगर /* _TRACE_BPF_TRACE_H */

#अघोषित TRACE_INCLUDE_PATH
#घोषणा TRACE_INCLUDE_PATH .
#घोषणा TRACE_INCLUDE_खाता bpf_trace

#समावेश <trace/define_trace.h>
