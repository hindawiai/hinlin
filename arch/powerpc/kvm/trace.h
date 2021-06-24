<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर !defined(_TRACE_KVM_H) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा _TRACE_KVM_H

#समावेश <linux/tracepoपूर्णांक.h>

#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM kvm

/*
 * Tracepoपूर्णांक क्रम guest mode entry.
 */
TRACE_EVENT(kvm_ppc_instr,
	TP_PROTO(अचिन्हित पूर्णांक inst, अचिन्हित दीर्घ _pc, अचिन्हित पूर्णांक emulate),
	TP_ARGS(inst, _pc, emulate),

	TP_STRUCT__entry(
		__field(	अचिन्हित पूर्णांक,	inst		)
		__field(	अचिन्हित दीर्घ,	pc		)
		__field(	अचिन्हित पूर्णांक,	emulate		)
	),

	TP_fast_assign(
		__entry->inst		= inst;
		__entry->pc		= _pc;
		__entry->emulate	= emulate;
	),

	TP_prपूर्णांकk("inst %u pc 0x%lx emulate %u\n",
		  __entry->inst, __entry->pc, __entry->emulate)
);

TRACE_EVENT(kvm_stlb_inval,
	TP_PROTO(अचिन्हित पूर्णांक stlb_index),
	TP_ARGS(stlb_index),

	TP_STRUCT__entry(
		__field(	अचिन्हित पूर्णांक,	stlb_index	)
	),

	TP_fast_assign(
		__entry->stlb_index	= stlb_index;
	),

	TP_prपूर्णांकk("stlb_index %u", __entry->stlb_index)
);

TRACE_EVENT(kvm_stlb_ग_लिखो,
	TP_PROTO(अचिन्हित पूर्णांक victim, अचिन्हित पूर्णांक tid, अचिन्हित पूर्णांक word0,
		 अचिन्हित पूर्णांक word1, अचिन्हित पूर्णांक word2),
	TP_ARGS(victim, tid, word0, word1, word2),

	TP_STRUCT__entry(
		__field(	अचिन्हित पूर्णांक,	victim		)
		__field(	अचिन्हित पूर्णांक,	tid		)
		__field(	अचिन्हित पूर्णांक,	word0		)
		__field(	अचिन्हित पूर्णांक,	word1		)
		__field(	अचिन्हित पूर्णांक,	word2		)
	),

	TP_fast_assign(
		__entry->victim		= victim;
		__entry->tid		= tid;
		__entry->word0		= word0;
		__entry->word1		= word1;
		__entry->word2		= word2;
	),

	TP_prपूर्णांकk("victim %u tid %u w0 %u w1 %u w2 %u",
		__entry->victim, __entry->tid, __entry->word0,
		__entry->word1, __entry->word2)
);

TRACE_EVENT(kvm_gtlb_ग_लिखो,
	TP_PROTO(अचिन्हित पूर्णांक gtlb_index, अचिन्हित पूर्णांक tid, अचिन्हित पूर्णांक word0,
		 अचिन्हित पूर्णांक word1, अचिन्हित पूर्णांक word2),
	TP_ARGS(gtlb_index, tid, word0, word1, word2),

	TP_STRUCT__entry(
		__field(	अचिन्हित पूर्णांक,	gtlb_index	)
		__field(	अचिन्हित पूर्णांक,	tid		)
		__field(	अचिन्हित पूर्णांक,	word0		)
		__field(	अचिन्हित पूर्णांक,	word1		)
		__field(	अचिन्हित पूर्णांक,	word2		)
	),

	TP_fast_assign(
		__entry->gtlb_index	= gtlb_index;
		__entry->tid		= tid;
		__entry->word0		= word0;
		__entry->word1		= word1;
		__entry->word2		= word2;
	),

	TP_prपूर्णांकk("gtlb_index %u tid %u w0 %u w1 %u w2 %u",
		__entry->gtlb_index, __entry->tid, __entry->word0,
		__entry->word1, __entry->word2)
);

TRACE_EVENT(kvm_check_requests,
	TP_PROTO(काष्ठा kvm_vcpu *vcpu),
	TP_ARGS(vcpu),

	TP_STRUCT__entry(
		__field(	__u32,	cpu_nr		)
		__field(	__u32,	requests	)
	),

	TP_fast_assign(
		__entry->cpu_nr		= vcpu->vcpu_id;
		__entry->requests	= vcpu->requests;
	),

	TP_prपूर्णांकk("vcpu=%x requests=%x",
		__entry->cpu_nr, __entry->requests)
);

#पूर्ण_अगर /* _TRACE_KVM_H */

/* This part must be outside protection */
#अघोषित TRACE_INCLUDE_PATH
#अघोषित TRACE_INCLUDE_खाता

#घोषणा TRACE_INCLUDE_PATH .
#घोषणा TRACE_INCLUDE_खाता trace

#समावेश <trace/define_trace.h>
