<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM bpf_test_run

#अगर !defined(_TRACE_BPF_TEST_RUN_H) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा _TRACE_BPF_TEST_RUN_H

#समावेश <linux/tracepoपूर्णांक.h>

DECLARE_EVENT_CLASS(bpf_test_finish,

	TP_PROTO(पूर्णांक *err),

	TP_ARGS(err),

	TP_STRUCT__entry(
		__field(पूर्णांक, err)
	),

	TP_fast_assign(
		__entry->err = *err;
	),

	TP_prपूर्णांकk("bpf_test_finish with err=%d", __entry->err)
);

#अगर_घोषित DEFINE_EVENT_WRITABLE
#अघोषित BPF_TEST_RUN_DEFINE_EVENT
#घोषणा BPF_TEST_RUN_DEFINE_EVENT(ढाँचा, call, proto, args, size)	\
	DEFINE_EVENT_WRITABLE(ढाँचा, call, PARAMS(proto),		\
			      PARAMS(args), size)
#अन्यथा
#अघोषित BPF_TEST_RUN_DEFINE_EVENT
#घोषणा BPF_TEST_RUN_DEFINE_EVENT(ढाँचा, call, proto, args, size)	\
	DEFINE_EVENT(ढाँचा, call, PARAMS(proto), PARAMS(args))
#पूर्ण_अगर

BPF_TEST_RUN_DEFINE_EVENT(bpf_test_finish, bpf_test_finish,

	TP_PROTO(पूर्णांक *err),

	TP_ARGS(err),

	माप(पूर्णांक)
);

#पूर्ण_अगर

/* This part must be outside protection */
#समावेश <trace/define_trace.h>
