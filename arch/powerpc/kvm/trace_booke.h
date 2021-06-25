<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर !defined(_TRACE_KVM_BOOKE_H) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा _TRACE_KVM_BOOKE_H

#समावेश <linux/tracepoपूर्णांक.h>

#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM kvm_booke

#घोषणा kvm_trace_symbol_निकास \
	अणु0, "CRITICAL"पूर्ण, \
	अणु1, "MACHINE_CHECK"पूर्ण, \
	अणु2, "DATA_STORAGE"पूर्ण, \
	अणु3, "INST_STORAGE"पूर्ण, \
	अणु4, "EXTERNAL"पूर्ण, \
	अणु5, "ALIGNMENT"पूर्ण, \
	अणु6, "PROGRAM"पूर्ण, \
	अणु7, "FP_UNAVAIL"पूर्ण, \
	अणु8, "SYSCALL"पूर्ण, \
	अणु9, "AP_UNAVAIL"पूर्ण, \
	अणु10, "DECREMENTER"पूर्ण, \
	अणु11, "FIT"पूर्ण, \
	अणु12, "WATCHDOG"पूर्ण, \
	अणु13, "DTLB_MISS"पूर्ण, \
	अणु14, "ITLB_MISS"पूर्ण, \
	अणु15, "DEBUG"पूर्ण, \
	अणु32, "SPE_UNAVAIL"पूर्ण, \
	अणु33, "SPE_FP_DATA"पूर्ण, \
	अणु34, "SPE_FP_ROUND"पूर्ण, \
	अणु35, "PERFORMANCE_MONITOR"पूर्ण, \
	अणु36, "DOORBELL"पूर्ण, \
	अणु37, "DOORBELL_CRITICAL"पूर्ण, \
	अणु38, "GUEST_DBELL"पूर्ण, \
	अणु39, "GUEST_DBELL_CRIT"पूर्ण, \
	अणु40, "HV_SYSCALL"पूर्ण, \
	अणु41, "HV_PRIV"पूर्ण

TRACE_EVENT(kvm_निकास,
	TP_PROTO(अचिन्हित पूर्णांक निकास_nr, काष्ठा kvm_vcpu *vcpu),
	TP_ARGS(निकास_nr, vcpu),

	TP_STRUCT__entry(
		__field(	अचिन्हित पूर्णांक,	निकास_nr		)
		__field(	अचिन्हित दीर्घ,	pc		)
		__field(	अचिन्हित दीर्घ,	msr		)
		__field(	अचिन्हित दीर्घ,	dar		)
		__field(	अचिन्हित दीर्घ,	last_inst	)
	),

	TP_fast_assign(
		__entry->निकास_nr	= निकास_nr;
		__entry->pc		= kvmppc_get_pc(vcpu);
		__entry->dar		= kvmppc_get_fault_dar(vcpu);
		__entry->msr		= vcpu->arch.shared->msr;
		__entry->last_inst	= vcpu->arch.last_inst;
	),

	TP_prपूर्णांकk("exit=%s"
		" | pc=0x%lx"
		" | msr=0x%lx"
		" | dar=0x%lx"
		" | last_inst=0x%lx"
		,
		__prपूर्णांक_symbolic(__entry->निकास_nr, kvm_trace_symbol_निकास),
		__entry->pc,
		__entry->msr,
		__entry->dar,
		__entry->last_inst
		)
);

TRACE_EVENT(kvm_booke206_stlb_ग_लिखो,
	TP_PROTO(__u32 mas0, __u32 mas8, __u32 mas1, __u64 mas2, __u64 mas7_3),
	TP_ARGS(mas0, mas8, mas1, mas2, mas7_3),

	TP_STRUCT__entry(
		__field(	__u32,	mas0		)
		__field(	__u32,	mas8		)
		__field(	__u32,	mas1		)
		__field(	__u64,	mas2		)
		__field(	__u64,	mas7_3		)
	),

	TP_fast_assign(
		__entry->mas0		= mas0;
		__entry->mas8		= mas8;
		__entry->mas1		= mas1;
		__entry->mas2		= mas2;
		__entry->mas7_3		= mas7_3;
	),

	TP_prपूर्णांकk("mas0=%x mas8=%x mas1=%x mas2=%llx mas7_3=%llx",
		__entry->mas0, __entry->mas8, __entry->mas1,
		__entry->mas2, __entry->mas7_3)
);

TRACE_EVENT(kvm_booke206_gtlb_ग_लिखो,
	TP_PROTO(__u32 mas0, __u32 mas1, __u64 mas2, __u64 mas7_3),
	TP_ARGS(mas0, mas1, mas2, mas7_3),

	TP_STRUCT__entry(
		__field(	__u32,	mas0		)
		__field(	__u32,	mas1		)
		__field(	__u64,	mas2		)
		__field(	__u64,	mas7_3		)
	),

	TP_fast_assign(
		__entry->mas0		= mas0;
		__entry->mas1		= mas1;
		__entry->mas2		= mas2;
		__entry->mas7_3		= mas7_3;
	),

	TP_prपूर्णांकk("mas0=%x mas1=%x mas2=%llx mas7_3=%llx",
		__entry->mas0, __entry->mas1,
		__entry->mas2, __entry->mas7_3)
);

TRACE_EVENT(kvm_booke206_ref_release,
	TP_PROTO(__u64 pfn, __u32 flags),
	TP_ARGS(pfn, flags),

	TP_STRUCT__entry(
		__field(	__u64,	pfn		)
		__field(	__u32,	flags		)
	),

	TP_fast_assign(
		__entry->pfn		= pfn;
		__entry->flags		= flags;
	),

	TP_prपूर्णांकk("pfn=%llx flags=%x",
		__entry->pfn, __entry->flags)
);

#अगर_घोषित CONFIG_SPE_POSSIBLE
#घोषणा kvm_trace_symbol_irqprio_spe \
	अणुBOOKE_IRQPRIO_SPE_UNAVAIL, "SPE_UNAVAIL"पूर्ण, \
	अणुBOOKE_IRQPRIO_SPE_FP_DATA, "SPE_FP_DATA"पूर्ण, \
	अणुBOOKE_IRQPRIO_SPE_FP_ROUND, "SPE_FP_ROUND"पूर्ण,
#अन्यथा
#घोषणा kvm_trace_symbol_irqprio_spe
#पूर्ण_अगर

#अगर_घोषित CONFIG_PPC_E500MC
#घोषणा kvm_trace_symbol_irqprio_e500mc \
	अणुBOOKE_IRQPRIO_ALTIVEC_UNAVAIL, "ALTIVEC_UNAVAIL"पूर्ण, \
	अणुBOOKE_IRQPRIO_ALTIVEC_ASSIST, "ALTIVEC_ASSIST"पूर्ण,
#अन्यथा
#घोषणा kvm_trace_symbol_irqprio_e500mc
#पूर्ण_अगर

#घोषणा kvm_trace_symbol_irqprio \
	kvm_trace_symbol_irqprio_spe \
	kvm_trace_symbol_irqprio_e500mc \
	अणुBOOKE_IRQPRIO_DATA_STORAGE, "DATA_STORAGE"पूर्ण, \
	अणुBOOKE_IRQPRIO_INST_STORAGE, "INST_STORAGE"पूर्ण, \
	अणुBOOKE_IRQPRIO_ALIGNMENT, "ALIGNMENT"पूर्ण, \
	अणुBOOKE_IRQPRIO_PROGRAM, "PROGRAM"पूर्ण, \
	अणुBOOKE_IRQPRIO_FP_UNAVAIL, "FP_UNAVAIL"पूर्ण, \
	अणुBOOKE_IRQPRIO_SYSCALL, "SYSCALL"पूर्ण, \
	अणुBOOKE_IRQPRIO_AP_UNAVAIL, "AP_UNAVAIL"पूर्ण, \
	अणुBOOKE_IRQPRIO_DTLB_MISS, "DTLB_MISS"पूर्ण, \
	अणुBOOKE_IRQPRIO_ITLB_MISS, "ITLB_MISS"पूर्ण, \
	अणुBOOKE_IRQPRIO_MACHINE_CHECK, "MACHINE_CHECK"पूर्ण, \
	अणुBOOKE_IRQPRIO_DEBUG, "DEBUG"पूर्ण, \
	अणुBOOKE_IRQPRIO_CRITICAL, "CRITICAL"पूर्ण, \
	अणुBOOKE_IRQPRIO_WATCHDOG, "WATCHDOG"पूर्ण, \
	अणुBOOKE_IRQPRIO_EXTERNAL, "EXTERNAL"पूर्ण, \
	अणुBOOKE_IRQPRIO_FIT, "FIT"पूर्ण, \
	अणुBOOKE_IRQPRIO_DECREMENTER, "DECREMENTER"पूर्ण, \
	अणुBOOKE_IRQPRIO_PERFORMANCE_MONITOR, "PERFORMANCE_MONITOR"पूर्ण, \
	अणुBOOKE_IRQPRIO_EXTERNAL_LEVEL, "EXTERNAL_LEVEL"पूर्ण, \
	अणुBOOKE_IRQPRIO_DBELL, "DBELL"पूर्ण, \
	अणुBOOKE_IRQPRIO_DBELL_CRIT, "DBELL_CRIT"पूर्ण \

TRACE_EVENT(kvm_booke_queue_irqprio,
	TP_PROTO(काष्ठा kvm_vcpu *vcpu, अचिन्हित पूर्णांक priority),
	TP_ARGS(vcpu, priority),

	TP_STRUCT__entry(
		__field(	__u32,	cpu_nr		)
		__field(	__u32,	priority		)
		__field(	अचिन्हित दीर्घ,	pending		)
	),

	TP_fast_assign(
		__entry->cpu_nr		= vcpu->vcpu_id;
		__entry->priority	= priority;
		__entry->pending	= vcpu->arch.pending_exceptions;
	),

	TP_prपूर्णांकk("vcpu=%x prio=%s pending=%lx",
		__entry->cpu_nr,
		__prपूर्णांक_symbolic(__entry->priority, kvm_trace_symbol_irqprio),
		__entry->pending)
);

#पूर्ण_अगर

/* This part must be outside protection */

#अघोषित TRACE_INCLUDE_PATH
#अघोषित TRACE_INCLUDE_खाता

#घोषणा TRACE_INCLUDE_PATH .
#घोषणा TRACE_INCLUDE_खाता trace_booke

#समावेश <trace/define_trace.h>
