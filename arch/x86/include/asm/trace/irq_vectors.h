<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM irq_vectors

#अगर !defined(_TRACE_IRQ_VECTORS_H) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा _TRACE_IRQ_VECTORS_H

#समावेश <linux/tracepoपूर्णांक.h>
#समावेश <यंत्र/trace/common.h>

#अगर_घोषित CONFIG_X86_LOCAL_APIC

DECLARE_EVENT_CLASS(x86_irq_vector,

	TP_PROTO(पूर्णांक vector),

	TP_ARGS(vector),

	TP_STRUCT__entry(
		__field(		पूर्णांक,	vector	)
	),

	TP_fast_assign(
		__entry->vector = vector;
	),

	TP_prपूर्णांकk("vector=%d", __entry->vector) );

#घोषणा DEFINE_IRQ_VECTOR_EVENT(name)		\
DEFINE_EVENT_FN(x86_irq_vector, name##_entry,	\
	TP_PROTO(पूर्णांक vector),			\
	TP_ARGS(vector), शून्य, शून्य);		\
DEFINE_EVENT_FN(x86_irq_vector, name##_निकास,	\
	TP_PROTO(पूर्णांक vector),			\
	TP_ARGS(vector), शून्य, शून्य);

/*
 * local_समयr - called when entering/निकासing a local समयr पूर्णांकerrupt
 * vector handler
 */
DEFINE_IRQ_VECTOR_EVENT(local_समयr);

/*
 * spurious_apic - called when entering/निकासing a spurious apic vector handler
 */
DEFINE_IRQ_VECTOR_EVENT(spurious_apic);

/*
 * error_apic - called when entering/निकासing an error apic vector handler
 */
DEFINE_IRQ_VECTOR_EVENT(error_apic);

/*
 * x86_platक्रमm_ipi - called when entering/निकासing a x86 platक्रमm ipi पूर्णांकerrupt
 * vector handler
 */
DEFINE_IRQ_VECTOR_EVENT(x86_platक्रमm_ipi);

#अगर_घोषित CONFIG_IRQ_WORK
/*
 * irq_work - called when entering/निकासing a irq work पूर्णांकerrupt
 * vector handler
 */
DEFINE_IRQ_VECTOR_EVENT(irq_work);

/*
 * We must dis-allow sampling irq_work_निकास() because perf event sampling
 * itself can cause irq_work, which would lead to an infinite loop;
 *
 *  1) irq_work_निकास happens
 *  2) generates perf sample
 *  3) generates irq_work
 *  4) जाओ 1
 */
TRACE_EVENT_PERF_PERM(irq_work_निकास, is_sampling_event(p_event) ? -EPERM : 0);
#पूर्ण_अगर

/*
 * The अगरdef is required because that tracepoपूर्णांक macro hell emits tracepoपूर्णांक
 * code in files which include this header even अगर the tracepoपूर्णांक is not
 * enabled. Brilliant stuff that.
 */
#अगर_घोषित CONFIG_SMP
/*
 * reschedule - called when entering/निकासing a reschedule vector handler
 */
DEFINE_IRQ_VECTOR_EVENT(reschedule);

/*
 * call_function - called when entering/निकासing a call function पूर्णांकerrupt
 * vector handler
 */
DEFINE_IRQ_VECTOR_EVENT(call_function);

/*
 * call_function_single - called when entering/निकासing a call function
 * single पूर्णांकerrupt vector handler
 */
DEFINE_IRQ_VECTOR_EVENT(call_function_single);
#पूर्ण_अगर

#अगर_घोषित CONFIG_X86_MCE_THRESHOLD
/*
 * threshold_apic - called when entering/निकासing a threshold apic पूर्णांकerrupt
 * vector handler
 */
DEFINE_IRQ_VECTOR_EVENT(threshold_apic);
#पूर्ण_अगर

#अगर_घोषित CONFIG_X86_MCE_AMD
/*
 * deferred_error_apic - called when entering/निकासing a deferred apic पूर्णांकerrupt
 * vector handler
 */
DEFINE_IRQ_VECTOR_EVENT(deferred_error_apic);
#पूर्ण_अगर

#अगर_घोषित CONFIG_X86_THERMAL_VECTOR
/*
 * thermal_apic - called when entering/निकासing a thermal apic पूर्णांकerrupt
 * vector handler
 */
DEFINE_IRQ_VECTOR_EVENT(thermal_apic);
#पूर्ण_अगर

TRACE_EVENT(vector_config,

	TP_PROTO(अचिन्हित पूर्णांक irq, अचिन्हित पूर्णांक vector,
		 अचिन्हित पूर्णांक cpu, अचिन्हित पूर्णांक apicdest),

	TP_ARGS(irq, vector, cpu, apicdest),

	TP_STRUCT__entry(
		__field(	अचिन्हित पूर्णांक,	irq		)
		__field(	अचिन्हित पूर्णांक,	vector		)
		__field(	अचिन्हित पूर्णांक,	cpu		)
		__field(	अचिन्हित पूर्णांक,	apicdest	)
	),

	TP_fast_assign(
		__entry->irq		= irq;
		__entry->vector		= vector;
		__entry->cpu		= cpu;
		__entry->apicdest	= apicdest;
	),

	TP_prपूर्णांकk("irq=%u vector=%u cpu=%u apicdest=0x%08x",
		  __entry->irq, __entry->vector, __entry->cpu,
		  __entry->apicdest)
);

DECLARE_EVENT_CLASS(vector_mod,

	TP_PROTO(अचिन्हित पूर्णांक irq, अचिन्हित पूर्णांक vector,
		 अचिन्हित पूर्णांक cpu, अचिन्हित पूर्णांक prev_vector,
		 अचिन्हित पूर्णांक prev_cpu),

	TP_ARGS(irq, vector, cpu, prev_vector, prev_cpu),

	TP_STRUCT__entry(
		__field(	अचिन्हित पूर्णांक,	irq		)
		__field(	अचिन्हित पूर्णांक,	vector		)
		__field(	अचिन्हित पूर्णांक,	cpu		)
		__field(	अचिन्हित पूर्णांक,	prev_vector	)
		__field(	अचिन्हित पूर्णांक,	prev_cpu	)
	),

	TP_fast_assign(
		__entry->irq		= irq;
		__entry->vector		= vector;
		__entry->cpu		= cpu;
		__entry->prev_vector	= prev_vector;
		__entry->prev_cpu	= prev_cpu;

	),

	TP_prपूर्णांकk("irq=%u vector=%u cpu=%u prev_vector=%u prev_cpu=%u",
		  __entry->irq, __entry->vector, __entry->cpu,
		  __entry->prev_vector, __entry->prev_cpu)
);

#घोषणा DEFINE_IRQ_VECTOR_MOD_EVENT(name)				\
DEFINE_EVENT_FN(vector_mod, name,					\
	TP_PROTO(अचिन्हित पूर्णांक irq, अचिन्हित पूर्णांक vector,			\
		 अचिन्हित पूर्णांक cpu, अचिन्हित पूर्णांक prev_vector,		\
		 अचिन्हित पूर्णांक prev_cpu),				\
	TP_ARGS(irq, vector, cpu, prev_vector, prev_cpu), शून्य, शून्य);	\

DEFINE_IRQ_VECTOR_MOD_EVENT(vector_update);
DEFINE_IRQ_VECTOR_MOD_EVENT(vector_clear);

DECLARE_EVENT_CLASS(vector_reserve,

	TP_PROTO(अचिन्हित पूर्णांक irq, पूर्णांक ret),

	TP_ARGS(irq, ret),

	TP_STRUCT__entry(
		__field(	अचिन्हित पूर्णांक,	irq	)
		__field(	पूर्णांक,		ret	)
	),

	TP_fast_assign(
		__entry->irq = irq;
		__entry->ret = ret;
	),

	TP_prपूर्णांकk("irq=%u ret=%d", __entry->irq, __entry->ret)
);

#घोषणा DEFINE_IRQ_VECTOR_RESERVE_EVENT(name)	\
DEFINE_EVENT_FN(vector_reserve, name,	\
	TP_PROTO(अचिन्हित पूर्णांक irq, पूर्णांक ret),	\
	TP_ARGS(irq, ret), शून्य, शून्य);		\

DEFINE_IRQ_VECTOR_RESERVE_EVENT(vector_reserve_managed);
DEFINE_IRQ_VECTOR_RESERVE_EVENT(vector_reserve);

TRACE_EVENT(vector_alloc,

	TP_PROTO(अचिन्हित पूर्णांक irq, अचिन्हित पूर्णांक vector, bool reserved,
		 पूर्णांक ret),

	TP_ARGS(irq, vector, reserved, ret),

	TP_STRUCT__entry(
		__field(	अचिन्हित पूर्णांक,	irq		)
		__field(	अचिन्हित पूर्णांक,	vector		)
		__field(	bool,		reserved	)
		__field(	पूर्णांक,		ret		)
	),

	TP_fast_assign(
		__entry->irq		= irq;
		__entry->vector		= ret < 0 ? 0 : vector;
		__entry->reserved	= reserved;
		__entry->ret		= ret > 0 ? 0 : ret;
	),

	TP_prपूर्णांकk("irq=%u vector=%u reserved=%d ret=%d",
		  __entry->irq, __entry->vector,
		  __entry->reserved, __entry->ret)
);

TRACE_EVENT(vector_alloc_managed,

	TP_PROTO(अचिन्हित पूर्णांक irq, अचिन्हित पूर्णांक vector,
		 पूर्णांक ret),

	TP_ARGS(irq, vector, ret),

	TP_STRUCT__entry(
		__field(	अचिन्हित पूर्णांक,	irq		)
		__field(	अचिन्हित पूर्णांक,	vector		)
		__field(	पूर्णांक,		ret		)
	),

	TP_fast_assign(
		__entry->irq		= irq;
		__entry->vector		= ret < 0 ? 0 : vector;
		__entry->ret		= ret > 0 ? 0 : ret;
	),

	TP_prपूर्णांकk("irq=%u vector=%u ret=%d",
		  __entry->irq, __entry->vector, __entry->ret)
);

DECLARE_EVENT_CLASS(vector_activate,

	TP_PROTO(अचिन्हित पूर्णांक irq, bool is_managed, bool can_reserve,
		 bool reserve),

	TP_ARGS(irq, is_managed, can_reserve, reserve),

	TP_STRUCT__entry(
		__field(	अचिन्हित पूर्णांक,	irq		)
		__field(	bool,		is_managed	)
		__field(	bool,		can_reserve	)
		__field(	bool,		reserve		)
	),

	TP_fast_assign(
		__entry->irq		= irq;
		__entry->is_managed	= is_managed;
		__entry->can_reserve	= can_reserve;
		__entry->reserve	= reserve;
	),

	TP_prपूर्णांकk("irq=%u is_managed=%d can_reserve=%d reserve=%d",
		  __entry->irq, __entry->is_managed, __entry->can_reserve,
		  __entry->reserve)
);

#घोषणा DEFINE_IRQ_VECTOR_ACTIVATE_EVENT(name)				\
DEFINE_EVENT_FN(vector_activate, name,					\
	TP_PROTO(अचिन्हित पूर्णांक irq, bool is_managed,			\
		 bool can_reserve, bool reserve),			\
	TP_ARGS(irq, is_managed, can_reserve, reserve), शून्य, शून्य);	\

DEFINE_IRQ_VECTOR_ACTIVATE_EVENT(vector_activate);
DEFINE_IRQ_VECTOR_ACTIVATE_EVENT(vector_deactivate);

TRACE_EVENT(vector_tearकरोwn,

	TP_PROTO(अचिन्हित पूर्णांक irq, bool is_managed, bool has_reserved),

	TP_ARGS(irq, is_managed, has_reserved),

	TP_STRUCT__entry(
		__field(	अचिन्हित पूर्णांक,	irq		)
		__field(	bool,		is_managed	)
		__field(	bool,		has_reserved	)
	),

	TP_fast_assign(
		__entry->irq		= irq;
		__entry->is_managed	= is_managed;
		__entry->has_reserved	= has_reserved;
	),

	TP_prपूर्णांकk("irq=%u is_managed=%d has_reserved=%d",
		  __entry->irq, __entry->is_managed, __entry->has_reserved)
);

TRACE_EVENT(vector_setup,

	TP_PROTO(अचिन्हित पूर्णांक irq, bool is_legacy, पूर्णांक ret),

	TP_ARGS(irq, is_legacy, ret),

	TP_STRUCT__entry(
		__field(	अचिन्हित पूर्णांक,	irq		)
		__field(	bool,		is_legacy	)
		__field(	पूर्णांक,		ret		)
	),

	TP_fast_assign(
		__entry->irq		= irq;
		__entry->is_legacy	= is_legacy;
		__entry->ret		= ret;
	),

	TP_prपूर्णांकk("irq=%u is_legacy=%d ret=%d",
		  __entry->irq, __entry->is_legacy, __entry->ret)
);

TRACE_EVENT(vector_मुक्त_moved,

	TP_PROTO(अचिन्हित पूर्णांक irq, अचिन्हित पूर्णांक cpu, अचिन्हित पूर्णांक vector,
		 bool is_managed),

	TP_ARGS(irq, cpu, vector, is_managed),

	TP_STRUCT__entry(
		__field(	अचिन्हित पूर्णांक,	irq		)
		__field(	अचिन्हित पूर्णांक,	cpu		)
		__field(	अचिन्हित पूर्णांक,	vector		)
		__field(	bool,		is_managed	)
	),

	TP_fast_assign(
		__entry->irq		= irq;
		__entry->cpu		= cpu;
		__entry->vector		= vector;
		__entry->is_managed	= is_managed;
	),

	TP_prपूर्णांकk("irq=%u cpu=%u vector=%u is_managed=%d",
		  __entry->irq, __entry->cpu, __entry->vector,
		  __entry->is_managed)
);


#पूर्ण_अगर /* CONFIG_X86_LOCAL_APIC */

#अघोषित TRACE_INCLUDE_PATH
#अघोषित TRACE_INCLUDE_खाता
#घोषणा TRACE_INCLUDE_PATH .
#घोषणा TRACE_INCLUDE_खाता irq_vectors
#पूर्ण_अगर /*  _TRACE_IRQ_VECTORS_H */

/* This part must be outside protection */
#समावेश <trace/define_trace.h>
