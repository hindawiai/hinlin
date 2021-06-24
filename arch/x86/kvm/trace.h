<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर !defined(_TRACE_KVM_H) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा _TRACE_KVM_H

#समावेश <linux/tracepoपूर्णांक.h>
#समावेश <यंत्र/vmx.h>
#समावेश <यंत्र/svm.h>
#समावेश <यंत्र/घड़ीsource.h>
#समावेश <यंत्र/pvघड़ी-abi.h>

#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM kvm

/*
 * Tracepoपूर्णांक क्रम guest mode entry.
 */
TRACE_EVENT(kvm_entry,
	TP_PROTO(काष्ठा kvm_vcpu *vcpu),
	TP_ARGS(vcpu),

	TP_STRUCT__entry(
		__field(	अचिन्हित पूर्णांक,	vcpu_id		)
		__field(	अचिन्हित दीर्घ,	rip		)
	),

	TP_fast_assign(
		__entry->vcpu_id        = vcpu->vcpu_id;
		__entry->rip		= kvm_rip_पढ़ो(vcpu);
	),

	TP_prपूर्णांकk("vcpu %u, rip 0x%lx", __entry->vcpu_id, __entry->rip)
);

/*
 * Tracepoपूर्णांक क्रम hypercall.
 */
TRACE_EVENT(kvm_hypercall,
	TP_PROTO(अचिन्हित दीर्घ nr, अचिन्हित दीर्घ a0, अचिन्हित दीर्घ a1,
		 अचिन्हित दीर्घ a2, अचिन्हित दीर्घ a3),
	TP_ARGS(nr, a0, a1, a2, a3),

	TP_STRUCT__entry(
		__field(	अचिन्हित दीर्घ, 	nr		)
		__field(	अचिन्हित दीर्घ,	a0		)
		__field(	अचिन्हित दीर्घ,	a1		)
		__field(	अचिन्हित दीर्घ,	a2		)
		__field(	अचिन्हित दीर्घ,	a3		)
	),

	TP_fast_assign(
		__entry->nr		= nr;
		__entry->a0		= a0;
		__entry->a1		= a1;
		__entry->a2		= a2;
		__entry->a3		= a3;
	),

	TP_prपूर्णांकk("nr 0x%lx a0 0x%lx a1 0x%lx a2 0x%lx a3 0x%lx",
		 __entry->nr, __entry->a0, __entry->a1,  __entry->a2,
		 __entry->a3)
);

/*
 * Tracepoपूर्णांक क्रम hypercall.
 */
TRACE_EVENT(kvm_hv_hypercall,
	TP_PROTO(__u16 code, bool fast, __u16 rep_cnt, __u16 rep_idx,
		 __u64 ingpa, __u64 outgpa),
	TP_ARGS(code, fast, rep_cnt, rep_idx, ingpa, outgpa),

	TP_STRUCT__entry(
		__field(	__u16,		rep_cnt		)
		__field(	__u16,		rep_idx		)
		__field(	__u64,		ingpa		)
		__field(	__u64,		outgpa		)
		__field(	__u16, 		code		)
		__field(	bool,		fast		)
	),

	TP_fast_assign(
		__entry->rep_cnt	= rep_cnt;
		__entry->rep_idx	= rep_idx;
		__entry->ingpa		= ingpa;
		__entry->outgpa		= outgpa;
		__entry->code		= code;
		__entry->fast		= fast;
	),

	TP_prपूर्णांकk("code 0x%x %s cnt 0x%x idx 0x%x in 0x%llx out 0x%llx",
		  __entry->code, __entry->fast ? "fast" : "slow",
		  __entry->rep_cnt, __entry->rep_idx,  __entry->ingpa,
		  __entry->outgpa)
);

/*
 * Tracepoपूर्णांक क्रम Xen hypercall.
 */
TRACE_EVENT(kvm_xen_hypercall,
	TP_PROTO(अचिन्हित दीर्घ nr, अचिन्हित दीर्घ a0, अचिन्हित दीर्घ a1,
		 अचिन्हित दीर्घ a2, अचिन्हित दीर्घ a3, अचिन्हित दीर्घ a4,
		 अचिन्हित दीर्घ a5),
	    TP_ARGS(nr, a0, a1, a2, a3, a4, a5),

	TP_STRUCT__entry(
		__field(अचिन्हित दीर्घ, nr)
		__field(अचिन्हित दीर्घ, a0)
		__field(अचिन्हित दीर्घ, a1)
		__field(अचिन्हित दीर्घ, a2)
		__field(अचिन्हित दीर्घ, a3)
		__field(अचिन्हित दीर्घ, a4)
		__field(अचिन्हित दीर्घ, a5)
	),

	TP_fast_assign(
		__entry->nr = nr;
		__entry->a0 = a0;
		__entry->a1 = a1;
		__entry->a2 = a2;
		__entry->a3 = a3;
		__entry->a4 = a4;
		__entry->a4 = a5;
	),

	TP_prपूर्णांकk("nr 0x%lx a0 0x%lx a1 0x%lx a2 0x%lx a3 0x%lx a4 0x%lx a5 %lx",
		  __entry->nr, __entry->a0, __entry->a1,  __entry->a2,
		  __entry->a3, __entry->a4, __entry->a5)
);



/*
 * Tracepoपूर्णांक क्रम PIO.
 */

#घोषणा KVM_PIO_IN   0
#घोषणा KVM_PIO_OUT  1

TRACE_EVENT(kvm_pio,
	TP_PROTO(अचिन्हित पूर्णांक rw, अचिन्हित पूर्णांक port, अचिन्हित पूर्णांक size,
		 अचिन्हित पूर्णांक count, व्योम *data),
	TP_ARGS(rw, port, size, count, data),

	TP_STRUCT__entry(
		__field(	अचिन्हित पूर्णांक, 	rw		)
		__field(	अचिन्हित पूर्णांक, 	port		)
		__field(	अचिन्हित पूर्णांक, 	size		)
		__field(	अचिन्हित पूर्णांक,	count		)
		__field(	अचिन्हित पूर्णांक,	val		)
	),

	TP_fast_assign(
		__entry->rw		= rw;
		__entry->port		= port;
		__entry->size		= size;
		__entry->count		= count;
		अगर (size == 1)
			__entry->val	= *(अचिन्हित अक्षर *)data;
		अन्यथा अगर (size == 2)
			__entry->val	= *(अचिन्हित लघु *)data;
		अन्यथा
			__entry->val	= *(अचिन्हित पूर्णांक *)data;
	),

	TP_prपूर्णांकk("pio_%s at 0x%x size %d count %d val 0x%x %s",
		  __entry->rw ? "write" : "read",
		  __entry->port, __entry->size, __entry->count, __entry->val,
		  __entry->count > 1 ? "(...)" : "")
);

/*
 * Tracepoपूर्णांक क्रम fast mmio.
 */
TRACE_EVENT(kvm_fast_mmio,
	TP_PROTO(u64 gpa),
	TP_ARGS(gpa),

	TP_STRUCT__entry(
		__field(u64,	gpa)
	),

	TP_fast_assign(
		__entry->gpa		= gpa;
	),

	TP_prपूर्णांकk("fast mmio at gpa 0x%llx", __entry->gpa)
);

/*
 * Tracepoपूर्णांक क्रम cpuid.
 */
TRACE_EVENT(kvm_cpuid,
	TP_PROTO(अचिन्हित पूर्णांक function, अचिन्हित पूर्णांक index, अचिन्हित दीर्घ rax,
		 अचिन्हित दीर्घ rbx, अचिन्हित दीर्घ rcx, अचिन्हित दीर्घ rdx,
		 bool found, bool used_max_basic),
	TP_ARGS(function, index, rax, rbx, rcx, rdx, found, used_max_basic),

	TP_STRUCT__entry(
		__field(	अचिन्हित पूर्णांक,	function	)
		__field(	अचिन्हित पूर्णांक,	index		)
		__field(	अचिन्हित दीर्घ,	rax		)
		__field(	अचिन्हित दीर्घ,	rbx		)
		__field(	अचिन्हित दीर्घ,	rcx		)
		__field(	अचिन्हित दीर्घ,	rdx		)
		__field(	bool,		found		)
		__field(	bool,		used_max_basic	)
	),

	TP_fast_assign(
		__entry->function	= function;
		__entry->index		= index;
		__entry->rax		= rax;
		__entry->rbx		= rbx;
		__entry->rcx		= rcx;
		__entry->rdx		= rdx;
		__entry->found		= found;
		__entry->used_max_basic	= used_max_basic;
	),

	TP_prपूर्णांकk("func %x idx %x rax %lx rbx %lx rcx %lx rdx %lx, cpuid entry %s%s",
		  __entry->function, __entry->index, __entry->rax,
		  __entry->rbx, __entry->rcx, __entry->rdx,
		  __entry->found ? "found" : "not found",
		  __entry->used_max_basic ? ", used max basic" : "")
);

#घोषणा AREG(x) अणु APIC_##x, "APIC_" #x पूर्ण

#घोषणा kvm_trace_symbol_apic						    \
	AREG(ID), AREG(LVR), AREG(TASKPRI), AREG(ARBPRI), AREG(PROCPRI),    \
	AREG(EOI), AREG(RRR), AREG(LDR), AREG(DFR), AREG(SPIV), AREG(ISR),  \
	AREG(TMR), AREG(IRR), AREG(ESR), AREG(ICR), AREG(ICR2), AREG(LVTT), \
	AREG(LVTTHMR), AREG(LVTPC), AREG(LVT0), AREG(LVT1), AREG(LVTERR),   \
	AREG(TMICT), AREG(TMCCT), AREG(TDCR), AREG(SELF_IPI), AREG(EFEAT),  \
	AREG(ECTRL)
/*
 * Tracepoपूर्णांक क्रम apic access.
 */
TRACE_EVENT(kvm_apic,
	TP_PROTO(अचिन्हित पूर्णांक rw, अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक val),
	TP_ARGS(rw, reg, val),

	TP_STRUCT__entry(
		__field(	अचिन्हित पूर्णांक,	rw		)
		__field(	अचिन्हित पूर्णांक,	reg		)
		__field(	अचिन्हित पूर्णांक,	val		)
	),

	TP_fast_assign(
		__entry->rw		= rw;
		__entry->reg		= reg;
		__entry->val		= val;
	),

	TP_prपूर्णांकk("apic_%s %s = 0x%x",
		  __entry->rw ? "write" : "read",
		  __prपूर्णांक_symbolic(__entry->reg, kvm_trace_symbol_apic),
		  __entry->val)
);

#घोषणा trace_kvm_apic_पढ़ो(reg, val)		trace_kvm_apic(0, reg, val)
#घोषणा trace_kvm_apic_ग_लिखो(reg, val)		trace_kvm_apic(1, reg, val)

#घोषणा KVM_ISA_VMX   1
#घोषणा KVM_ISA_SVM   2

#घोषणा kvm_prपूर्णांक_निकास_reason(निकास_reason, isa)				\
	(isa == KVM_ISA_VMX) ?						\
	__prपूर्णांक_symbolic(निकास_reason & 0xffff, VMX_EXIT_REASONS) :	\
	__prपूर्णांक_symbolic(निकास_reason, SVM_EXIT_REASONS),		\
	(isa == KVM_ISA_VMX && निकास_reason & ~0xffff) ? " " : "",	\
	(isa == KVM_ISA_VMX) ?						\
	__prपूर्णांक_flags(निकास_reason & ~0xffff, " ", VMX_EXIT_REASON_FLAGS) : ""

#घोषणा TRACE_EVENT_KVM_EXIT(name)					     \
TRACE_EVENT(name,							     \
	TP_PROTO(अचिन्हित पूर्णांक निकास_reason, काष्ठा kvm_vcpu *vcpu, u32 isa),  \
	TP_ARGS(निकास_reason, vcpu, isa),				     \
									     \
	TP_STRUCT__entry(						     \
		__field(	अचिन्हित पूर्णांक,	निकास_reason	)	     \
		__field(	अचिन्हित दीर्घ,	guest_rip	)	     \
		__field(	u32,	        isa             )	     \
		__field(	u64,	        info1           )	     \
		__field(	u64,	        info2           )	     \
		__field(	u32,	        पूर्णांकr_info	)	     \
		__field(	u32,	        error_code	)	     \
		__field(	अचिन्हित पूर्णांक,	vcpu_id         )	     \
	),								     \
									     \
	TP_fast_assign(							     \
		__entry->निकास_reason	= निकास_reason;			     \
		__entry->guest_rip	= kvm_rip_पढ़ो(vcpu);		     \
		__entry->isa            = isa;				     \
		__entry->vcpu_id        = vcpu->vcpu_id;		     \
		अटल_call(kvm_x86_get_निकास_info)(vcpu, &__entry->info1,    \
					  &__entry->info2,		     \
					  &__entry->पूर्णांकr_info,		     \
					  &__entry->error_code);	     \
	),								     \
									     \
	TP_prपूर्णांकk("vcpu %u reason %s%s%s rip 0x%lx info1 0x%016llx "	     \
		  "info2 0x%016llx intr_info 0x%08x error_code 0x%08x",	     \
		  __entry->vcpu_id,					     \
		  kvm_prपूर्णांक_निकास_reason(__entry->निकास_reason, __entry->isa), \
		  __entry->guest_rip, __entry->info1, __entry->info2,	     \
		  __entry->पूर्णांकr_info, __entry->error_code)		     \
)

/*
 * Tracepoपूर्णांक क्रम kvm guest निकास:
 */
TRACE_EVENT_KVM_EXIT(kvm_निकास);

/*
 * Tracepoपूर्णांक क्रम kvm पूर्णांकerrupt injection:
 */
TRACE_EVENT(kvm_inj_virq,
	TP_PROTO(अचिन्हित पूर्णांक irq),
	TP_ARGS(irq),

	TP_STRUCT__entry(
		__field(	अचिन्हित पूर्णांक,	irq		)
	),

	TP_fast_assign(
		__entry->irq		= irq;
	),

	TP_prपूर्णांकk("irq %u", __entry->irq)
);

#घोषणा EXS(x) अणु x##_VECTOR, "#" #x पूर्ण

#घोषणा kvm_trace_sym_exc						\
	EXS(DE), EXS(DB), EXS(BP), EXS(OF), EXS(BR), EXS(UD), EXS(NM),	\
	EXS(DF), EXS(TS), EXS(NP), EXS(SS), EXS(GP), EXS(PF),		\
	EXS(MF), EXS(AC), EXS(MC)

/*
 * Tracepoपूर्णांक क्रम kvm पूर्णांकerrupt injection:
 */
TRACE_EVENT(kvm_inj_exception,
	TP_PROTO(अचिन्हित exception, bool has_error, अचिन्हित error_code),
	TP_ARGS(exception, has_error, error_code),

	TP_STRUCT__entry(
		__field(	u8,	exception	)
		__field(	u8,	has_error	)
		__field(	u32,	error_code	)
	),

	TP_fast_assign(
		__entry->exception	= exception;
		__entry->has_error	= has_error;
		__entry->error_code	= error_code;
	),

	TP_prपूर्णांकk("%s (0x%x)",
		  __prपूर्णांक_symbolic(__entry->exception, kvm_trace_sym_exc),
		  /* FIXME: करोn't prपूर्णांक error_code अगर not present */
		  __entry->has_error ? __entry->error_code : 0)
);

/*
 * Tracepoपूर्णांक क्रम page fault.
 */
TRACE_EVENT(kvm_page_fault,
	TP_PROTO(अचिन्हित दीर्घ fault_address, अचिन्हित पूर्णांक error_code),
	TP_ARGS(fault_address, error_code),

	TP_STRUCT__entry(
		__field(	अचिन्हित दीर्घ,	fault_address	)
		__field(	अचिन्हित पूर्णांक,	error_code	)
	),

	TP_fast_assign(
		__entry->fault_address	= fault_address;
		__entry->error_code	= error_code;
	),

	TP_prपूर्णांकk("address %lx error_code %x",
		  __entry->fault_address, __entry->error_code)
);

/*
 * Tracepoपूर्णांक क्रम guest MSR access.
 */
TRACE_EVENT(kvm_msr,
	TP_PROTO(अचिन्हित ग_लिखो, u32 ecx, u64 data, bool exception),
	TP_ARGS(ग_लिखो, ecx, data, exception),

	TP_STRUCT__entry(
		__field(	अचिन्हित,	ग_लिखो		)
		__field(	u32,		ecx		)
		__field(	u64,		data		)
		__field(	u8,		exception	)
	),

	TP_fast_assign(
		__entry->ग_लिखो		= ग_लिखो;
		__entry->ecx		= ecx;
		__entry->data		= data;
		__entry->exception	= exception;
	),

	TP_prपूर्णांकk("msr_%s %x = 0x%llx%s",
		  __entry->ग_लिखो ? "write" : "read",
		  __entry->ecx, __entry->data,
		  __entry->exception ? " (#GP)" : "")
);

#घोषणा trace_kvm_msr_पढ़ो(ecx, data)      trace_kvm_msr(0, ecx, data, false)
#घोषणा trace_kvm_msr_ग_लिखो(ecx, data)     trace_kvm_msr(1, ecx, data, false)
#घोषणा trace_kvm_msr_पढ़ो_ex(ecx)         trace_kvm_msr(0, ecx, 0, true)
#घोषणा trace_kvm_msr_ग_लिखो_ex(ecx, data)  trace_kvm_msr(1, ecx, data, true)

/*
 * Tracepoपूर्णांक क्रम guest CR access.
 */
TRACE_EVENT(kvm_cr,
	TP_PROTO(अचिन्हित पूर्णांक rw, अचिन्हित पूर्णांक cr, अचिन्हित दीर्घ val),
	TP_ARGS(rw, cr, val),

	TP_STRUCT__entry(
		__field(	अचिन्हित पूर्णांक,	rw		)
		__field(	अचिन्हित पूर्णांक,	cr		)
		__field(	अचिन्हित दीर्घ,	val		)
	),

	TP_fast_assign(
		__entry->rw		= rw;
		__entry->cr		= cr;
		__entry->val		= val;
	),

	TP_prपूर्णांकk("cr_%s %x = 0x%lx",
		  __entry->rw ? "write" : "read",
		  __entry->cr, __entry->val)
);

#घोषणा trace_kvm_cr_पढ़ो(cr, val)		trace_kvm_cr(0, cr, val)
#घोषणा trace_kvm_cr_ग_लिखो(cr, val)		trace_kvm_cr(1, cr, val)

TRACE_EVENT(kvm_pic_set_irq,
	    TP_PROTO(__u8 chip, __u8 pin, __u8 elcr, __u8 imr, bool coalesced),
	    TP_ARGS(chip, pin, elcr, imr, coalesced),

	TP_STRUCT__entry(
		__field(	__u8,		chip		)
		__field(	__u8,		pin		)
		__field(	__u8,		elcr		)
		__field(	__u8,		imr		)
		__field(	bool,		coalesced	)
	),

	TP_fast_assign(
		__entry->chip		= chip;
		__entry->pin		= pin;
		__entry->elcr		= elcr;
		__entry->imr		= imr;
		__entry->coalesced	= coalesced;
	),

	TP_prपूर्णांकk("chip %u pin %u (%s%s)%s",
		  __entry->chip, __entry->pin,
		  (__entry->elcr & (1 << __entry->pin)) ? "level":"edge",
		  (__entry->imr & (1 << __entry->pin)) ? "|masked":"",
		  __entry->coalesced ? " (coalesced)" : "")
);

#घोषणा kvm_apic_dst_लघुhand		\
	अणु0x0, "dst"पूर्ण,			\
	अणु0x1, "self"पूर्ण,			\
	अणु0x2, "all"पूर्ण,			\
	अणु0x3, "all-but-self"पूर्ण

TRACE_EVENT(kvm_apic_ipi,
	    TP_PROTO(__u32 icr_low, __u32 dest_id),
	    TP_ARGS(icr_low, dest_id),

	TP_STRUCT__entry(
		__field(	__u32,		icr_low		)
		__field(	__u32,		dest_id		)
	),

	TP_fast_assign(
		__entry->icr_low	= icr_low;
		__entry->dest_id	= dest_id;
	),

	TP_prपूर्णांकk("dst %x vec %u (%s|%s|%s|%s|%s)",
		  __entry->dest_id, (u8)__entry->icr_low,
		  __prपूर्णांक_symbolic((__entry->icr_low >> 8 & 0x7),
				   kvm_deliver_mode),
		  (__entry->icr_low & (1<<11)) ? "logical" : "physical",
		  (__entry->icr_low & (1<<14)) ? "assert" : "de-assert",
		  (__entry->icr_low & (1<<15)) ? "level" : "edge",
		  __prपूर्णांक_symbolic((__entry->icr_low >> 18 & 0x3),
				   kvm_apic_dst_लघुhand))
);

TRACE_EVENT(kvm_apic_accept_irq,
	    TP_PROTO(__u32 apicid, __u16 dm, __u16 पंचांग, __u8 vec),
	    TP_ARGS(apicid, dm, पंचांग, vec),

	TP_STRUCT__entry(
		__field(	__u32,		apicid		)
		__field(	__u16,		dm		)
		__field(	__u16,		पंचांग		)
		__field(	__u8,		vec		)
	),

	TP_fast_assign(
		__entry->apicid		= apicid;
		__entry->dm		= dm;
		__entry->पंचांग		= पंचांग;
		__entry->vec		= vec;
	),

	TP_prपूर्णांकk("apicid %x vec %u (%s|%s)",
		  __entry->apicid, __entry->vec,
		  __prपूर्णांक_symbolic((__entry->dm >> 8 & 0x7), kvm_deliver_mode),
		  __entry->पंचांग ? "level" : "edge")
);

TRACE_EVENT(kvm_eoi,
	    TP_PROTO(काष्ठा kvm_lapic *apic, पूर्णांक vector),
	    TP_ARGS(apic, vector),

	TP_STRUCT__entry(
		__field(	__u32,		apicid		)
		__field(	पूर्णांक,		vector		)
	),

	TP_fast_assign(
		__entry->apicid		= apic->vcpu->vcpu_id;
		__entry->vector		= vector;
	),

	TP_prपूर्णांकk("apicid %x vector %d", __entry->apicid, __entry->vector)
);

TRACE_EVENT(kvm_pv_eoi,
	    TP_PROTO(काष्ठा kvm_lapic *apic, पूर्णांक vector),
	    TP_ARGS(apic, vector),

	TP_STRUCT__entry(
		__field(	__u32,		apicid		)
		__field(	पूर्णांक,		vector		)
	),

	TP_fast_assign(
		__entry->apicid		= apic->vcpu->vcpu_id;
		__entry->vector		= vector;
	),

	TP_prपूर्णांकk("apicid %x vector %d", __entry->apicid, __entry->vector)
);

/*
 * Tracepoपूर्णांक क्रम nested VMRUN
 */
TRACE_EVENT(kvm_nested_vmrun,
	    TP_PROTO(__u64 rip, __u64 vmcb, __u64 nested_rip, __u32 पूर्णांक_ctl,
		     __u32 event_inj, bool npt),
	    TP_ARGS(rip, vmcb, nested_rip, पूर्णांक_ctl, event_inj, npt),

	TP_STRUCT__entry(
		__field(	__u64,		rip		)
		__field(	__u64,		vmcb		)
		__field(	__u64,		nested_rip	)
		__field(	__u32,		पूर्णांक_ctl		)
		__field(	__u32,		event_inj	)
		__field(	bool,		npt		)
	),

	TP_fast_assign(
		__entry->rip		= rip;
		__entry->vmcb		= vmcb;
		__entry->nested_rip	= nested_rip;
		__entry->पूर्णांक_ctl	= पूर्णांक_ctl;
		__entry->event_inj	= event_inj;
		__entry->npt		= npt;
	),

	TP_prपूर्णांकk("rip: 0x%016llx vmcb: 0x%016llx nrip: 0x%016llx int_ctl: 0x%08x "
		  "event_inj: 0x%08x npt: %s",
		__entry->rip, __entry->vmcb, __entry->nested_rip,
		__entry->पूर्णांक_ctl, __entry->event_inj,
		__entry->npt ? "on" : "off")
);

TRACE_EVENT(kvm_nested_पूर्णांकercepts,
	    TP_PROTO(__u16 cr_पढ़ो, __u16 cr_ग_लिखो, __u32 exceptions,
		     __u32 पूर्णांकercept1, __u32 पूर्णांकercept2, __u32 पूर्णांकercept3),
	    TP_ARGS(cr_पढ़ो, cr_ग_लिखो, exceptions, पूर्णांकercept1,
		    पूर्णांकercept2, पूर्णांकercept3),

	TP_STRUCT__entry(
		__field(	__u16,		cr_पढ़ो		)
		__field(	__u16,		cr_ग_लिखो	)
		__field(	__u32,		exceptions	)
		__field(	__u32,		पूर्णांकercept1	)
		__field(	__u32,		पूर्णांकercept2	)
		__field(	__u32,		पूर्णांकercept3	)
	),

	TP_fast_assign(
		__entry->cr_पढ़ो	= cr_पढ़ो;
		__entry->cr_ग_लिखो	= cr_ग_लिखो;
		__entry->exceptions	= exceptions;
		__entry->पूर्णांकercept1	= पूर्णांकercept1;
		__entry->पूर्णांकercept2	= पूर्णांकercept2;
		__entry->पूर्णांकercept3	= पूर्णांकercept3;
	),

	TP_prपूर्णांकk("cr_read: %04x cr_write: %04x excp: %08x "
		  "intercepts: %08x %08x %08x",
		  __entry->cr_पढ़ो, __entry->cr_ग_लिखो, __entry->exceptions,
		  __entry->पूर्णांकercept1, __entry->पूर्णांकercept2, __entry->पूर्णांकercept3)
);
/*
 * Tracepoपूर्णांक क्रम #VMEXIT जबतक nested
 */
TRACE_EVENT_KVM_EXIT(kvm_nested_vmनिकास);

/*
 * Tracepoपूर्णांक क्रम #VMEXIT reinjected to the guest
 */
TRACE_EVENT(kvm_nested_vmनिकास_inject,
	    TP_PROTO(__u32 निकास_code,
		     __u64 निकास_info1, __u64 निकास_info2,
		     __u32 निकास_पूर्णांक_info, __u32 निकास_पूर्णांक_info_err, __u32 isa),
	    TP_ARGS(निकास_code, निकास_info1, निकास_info2,
		    निकास_पूर्णांक_info, निकास_पूर्णांक_info_err, isa),

	TP_STRUCT__entry(
		__field(	__u32,		निकास_code		)
		__field(	__u64,		निकास_info1		)
		__field(	__u64,		निकास_info2		)
		__field(	__u32,		निकास_पूर्णांक_info		)
		__field(	__u32,		निकास_पूर्णांक_info_err	)
		__field(	__u32,		isa			)
	),

	TP_fast_assign(
		__entry->निकास_code		= निकास_code;
		__entry->निकास_info1		= निकास_info1;
		__entry->निकास_info2		= निकास_info2;
		__entry->निकास_पूर्णांक_info		= निकास_पूर्णांक_info;
		__entry->निकास_पूर्णांक_info_err	= निकास_पूर्णांक_info_err;
		__entry->isa			= isa;
	),

	TP_prपूर्णांकk("reason: %s%s%s ext_inf1: 0x%016llx "
		  "ext_inf2: 0x%016llx ext_int: 0x%08x ext_int_err: 0x%08x",
		  kvm_prपूर्णांक_निकास_reason(__entry->निकास_code, __entry->isa),
		  __entry->निकास_info1, __entry->निकास_info2,
		  __entry->निकास_पूर्णांक_info, __entry->निकास_पूर्णांक_info_err)
);

/*
 * Tracepoपूर्णांक क्रम nested #vmनिकास because of पूर्णांकerrupt pending
 */
TRACE_EVENT(kvm_nested_पूर्णांकr_vmनिकास,
	    TP_PROTO(__u64 rip),
	    TP_ARGS(rip),

	TP_STRUCT__entry(
		__field(	__u64,	rip	)
	),

	TP_fast_assign(
		__entry->rip	=	rip
	),

	TP_prपूर्णांकk("rip: 0x%016llx", __entry->rip)
);

/*
 * Tracepoपूर्णांक क्रम nested #vmनिकास because of पूर्णांकerrupt pending
 */
TRACE_EVENT(kvm_invlpga,
	    TP_PROTO(__u64 rip, पूर्णांक asid, u64 address),
	    TP_ARGS(rip, asid, address),

	TP_STRUCT__entry(
		__field(	__u64,	rip	)
		__field(	पूर्णांक,	asid	)
		__field(	__u64,	address	)
	),

	TP_fast_assign(
		__entry->rip		=	rip;
		__entry->asid		=	asid;
		__entry->address	=	address;
	),

	TP_prपूर्णांकk("rip: 0x%016llx asid: %d address: 0x%016llx",
		  __entry->rip, __entry->asid, __entry->address)
);

/*
 * Tracepoपूर्णांक क्रम nested #vmनिकास because of पूर्णांकerrupt pending
 */
TRACE_EVENT(kvm_skinit,
	    TP_PROTO(__u64 rip, __u32 slb),
	    TP_ARGS(rip, slb),

	TP_STRUCT__entry(
		__field(	__u64,	rip	)
		__field(	__u32,	slb	)
	),

	TP_fast_assign(
		__entry->rip		=	rip;
		__entry->slb		=	slb;
	),

	TP_prपूर्णांकk("rip: 0x%016llx slb: 0x%08x",
		  __entry->rip, __entry->slb)
);

#घोषणा KVM_EMUL_INSN_F_CR0_PE (1 << 0)
#घोषणा KVM_EMUL_INSN_F_EFL_VM (1 << 1)
#घोषणा KVM_EMUL_INSN_F_CS_D   (1 << 2)
#घोषणा KVM_EMUL_INSN_F_CS_L   (1 << 3)

#घोषणा kvm_trace_symbol_emul_flags	                  \
	अणु 0,   			    "real" पूर्ण,		  \
	अणु KVM_EMUL_INSN_F_CR0_PE			  \
	  | KVM_EMUL_INSN_F_EFL_VM, "vm16" पूर्ण,		  \
	अणु KVM_EMUL_INSN_F_CR0_PE,   "prot16" पूर्ण,		  \
	अणु KVM_EMUL_INSN_F_CR0_PE			  \
	  | KVM_EMUL_INSN_F_CS_D,   "prot32" पूर्ण,		  \
	अणु KVM_EMUL_INSN_F_CR0_PE			  \
	  | KVM_EMUL_INSN_F_CS_L,   "prot64" पूर्ण

#घोषणा kei_decode_mode(mode) (अणु			\
	u8 flags = 0xff;				\
	चयन (mode) अणु					\
	हाल X86EMUL_MODE_REAL:				\
		flags = 0;				\
		अवरोध;					\
	हाल X86EMUL_MODE_VM86:				\
		flags = KVM_EMUL_INSN_F_EFL_VM;		\
		अवरोध;					\
	हाल X86EMUL_MODE_PROT16:			\
		flags = KVM_EMUL_INSN_F_CR0_PE;		\
		अवरोध;					\
	हाल X86EMUL_MODE_PROT32:			\
		flags = KVM_EMUL_INSN_F_CR0_PE		\
			| KVM_EMUL_INSN_F_CS_D;		\
		अवरोध;					\
	हाल X86EMUL_MODE_PROT64:			\
		flags = KVM_EMUL_INSN_F_CR0_PE		\
			| KVM_EMUL_INSN_F_CS_L;		\
		अवरोध;					\
	पूर्ण						\
	flags;						\
	पूर्ण)

TRACE_EVENT(kvm_emulate_insn,
	TP_PROTO(काष्ठा kvm_vcpu *vcpu, __u8 failed),
	TP_ARGS(vcpu, failed),

	TP_STRUCT__entry(
		__field(    __u64, rip                       )
		__field(    __u32, csbase                    )
		__field(    __u8,  len                       )
		__array(    __u8,  insn,    15	             )
		__field(    __u8,  flags       	   	     )
		__field(    __u8,  failed                    )
		),

	TP_fast_assign(
		__entry->csbase = अटल_call(kvm_x86_get_segment_base)(vcpu, VCPU_SREG_CS);
		__entry->len = vcpu->arch.emulate_ctxt->fetch.ptr
			       - vcpu->arch.emulate_ctxt->fetch.data;
		__entry->rip = vcpu->arch.emulate_ctxt->_eip - __entry->len;
		स_नकल(__entry->insn,
		       vcpu->arch.emulate_ctxt->fetch.data,
		       15);
		__entry->flags = kei_decode_mode(vcpu->arch.emulate_ctxt->mode);
		__entry->failed = failed;
		),

	TP_prपूर्णांकk("%x:%llx:%s (%s)%s",
		  __entry->csbase, __entry->rip,
		  __prपूर्णांक_hex(__entry->insn, __entry->len),
		  __prपूर्णांक_symbolic(__entry->flags,
				   kvm_trace_symbol_emul_flags),
		  __entry->failed ? " failed" : ""
		)
	);

#घोषणा trace_kvm_emulate_insn_start(vcpu) trace_kvm_emulate_insn(vcpu, 0)
#घोषणा trace_kvm_emulate_insn_failed(vcpu) trace_kvm_emulate_insn(vcpu, 1)

TRACE_EVENT(
	vcpu_match_mmio,
	TP_PROTO(gva_t gva, gpa_t gpa, bool ग_लिखो, bool gpa_match),
	TP_ARGS(gva, gpa, ग_लिखो, gpa_match),

	TP_STRUCT__entry(
		__field(gva_t, gva)
		__field(gpa_t, gpa)
		__field(bool, ग_लिखो)
		__field(bool, gpa_match)
		),

	TP_fast_assign(
		__entry->gva = gva;
		__entry->gpa = gpa;
		__entry->ग_लिखो = ग_लिखो;
		__entry->gpa_match = gpa_match
		),

	TP_prपूर्णांकk("gva %#lx gpa %#llx %s %s", __entry->gva, __entry->gpa,
		  __entry->ग_लिखो ? "Write" : "Read",
		  __entry->gpa_match ? "GPA" : "GVA")
);

TRACE_EVENT(kvm_ग_लिखो_tsc_offset,
	TP_PROTO(अचिन्हित पूर्णांक vcpu_id, __u64 previous_tsc_offset,
		 __u64 next_tsc_offset),
	TP_ARGS(vcpu_id, previous_tsc_offset, next_tsc_offset),

	TP_STRUCT__entry(
		__field( अचिन्हित पूर्णांक,	vcpu_id				)
		__field(	__u64,	previous_tsc_offset		)
		__field(	__u64,	next_tsc_offset			)
	),

	TP_fast_assign(
		__entry->vcpu_id		= vcpu_id;
		__entry->previous_tsc_offset	= previous_tsc_offset;
		__entry->next_tsc_offset	= next_tsc_offset;
	),

	TP_prपूर्णांकk("vcpu=%u prev=%llu next=%llu", __entry->vcpu_id,
		  __entry->previous_tsc_offset, __entry->next_tsc_offset)
);

#अगर_घोषित CONFIG_X86_64

#घोषणा host_घड़ीs					\
	अणुVDSO_CLOCKMODE_NONE, "none"पूर्ण,			\
	अणुVDSO_CLOCKMODE_TSC,  "tsc"पूर्ण			\

TRACE_EVENT(kvm_update_master_घड़ी,
	TP_PROTO(bool use_master_घड़ी, अचिन्हित पूर्णांक host_घड़ी, bool offset_matched),
	TP_ARGS(use_master_घड़ी, host_घड़ी, offset_matched),

	TP_STRUCT__entry(
		__field(		bool,	use_master_घड़ी	)
		__field(	अचिन्हित पूर्णांक,	host_घड़ी		)
		__field(		bool,	offset_matched		)
	),

	TP_fast_assign(
		__entry->use_master_घड़ी	= use_master_घड़ी;
		__entry->host_घड़ी		= host_घड़ी;
		__entry->offset_matched		= offset_matched;
	),

	TP_prपूर्णांकk("masterclock %d hostclock %s offsetmatched %u",
		  __entry->use_master_घड़ी,
		  __prपूर्णांक_symbolic(__entry->host_घड़ी, host_घड़ीs),
		  __entry->offset_matched)
);

TRACE_EVENT(kvm_track_tsc,
	TP_PROTO(अचिन्हित पूर्णांक vcpu_id, अचिन्हित पूर्णांक nr_matched,
		 अचिन्हित पूर्णांक online_vcpus, bool use_master_घड़ी,
		 अचिन्हित पूर्णांक host_घड़ी),
	TP_ARGS(vcpu_id, nr_matched, online_vcpus, use_master_घड़ी,
		host_घड़ी),

	TP_STRUCT__entry(
		__field(	अचिन्हित पूर्णांक,	vcpu_id			)
		__field(	अचिन्हित पूर्णांक,	nr_vcpus_matched_tsc	)
		__field(	अचिन्हित पूर्णांक,	online_vcpus		)
		__field(	bool,		use_master_घड़ी	)
		__field(	अचिन्हित पूर्णांक,	host_घड़ी		)
	),

	TP_fast_assign(
		__entry->vcpu_id		= vcpu_id;
		__entry->nr_vcpus_matched_tsc	= nr_matched;
		__entry->online_vcpus		= online_vcpus;
		__entry->use_master_घड़ी	= use_master_घड़ी;
		__entry->host_घड़ी		= host_घड़ी;
	),

	TP_prपूर्णांकk("vcpu_id %u masterclock %u offsetmatched %u nr_online %u"
		  " hostclock %s",
		  __entry->vcpu_id, __entry->use_master_घड़ी,
		  __entry->nr_vcpus_matched_tsc, __entry->online_vcpus,
		  __prपूर्णांक_symbolic(__entry->host_घड़ी, host_घड़ीs))
);

#पूर्ण_अगर /* CONFIG_X86_64 */

/*
 * Tracepoपूर्णांक क्रम PML full VMEXIT.
 */
TRACE_EVENT(kvm_pml_full,
	TP_PROTO(अचिन्हित पूर्णांक vcpu_id),
	TP_ARGS(vcpu_id),

	TP_STRUCT__entry(
		__field(	अचिन्हित पूर्णांक,	vcpu_id			)
	),

	TP_fast_assign(
		__entry->vcpu_id		= vcpu_id;
	),

	TP_prपूर्णांकk("vcpu %d: PML full", __entry->vcpu_id)
);

TRACE_EVENT(kvm_ple_winकरोw_update,
	TP_PROTO(अचिन्हित पूर्णांक vcpu_id, अचिन्हित पूर्णांक new, अचिन्हित पूर्णांक old),
	TP_ARGS(vcpu_id, new, old),

	TP_STRUCT__entry(
		__field(        अचिन्हित पूर्णांक,   vcpu_id         )
		__field(        अचिन्हित पूर्णांक,       new         )
		__field(        अचिन्हित पूर्णांक,       old         )
	),

	TP_fast_assign(
		__entry->vcpu_id        = vcpu_id;
		__entry->new            = new;
		__entry->old            = old;
	),

	TP_prपूर्णांकk("vcpu %u old %u new %u (%s)",
	          __entry->vcpu_id, __entry->old, __entry->new,
		  __entry->old < __entry->new ? "growed" : "shrinked")
);

TRACE_EVENT(kvm_pvघड़ी_update,
	TP_PROTO(अचिन्हित पूर्णांक vcpu_id, काष्ठा pvघड़ी_vcpu_समय_info *pvघड़ी),
	TP_ARGS(vcpu_id, pvघड़ी),

	TP_STRUCT__entry(
		__field(	अचिन्हित पूर्णांक,	vcpu_id			)
		__field(	__u32,		version			)
		__field(	__u64,		tsc_बारtamp		)
		__field(	__u64,		प्रणाली_समय		)
		__field(	__u32,		tsc_to_प्रणाली_mul	)
		__field(	__s8,		tsc_shअगरt		)
		__field(	__u8,		flags			)
	),

	TP_fast_assign(
		__entry->vcpu_id	   = vcpu_id;
		__entry->version	   = pvघड़ी->version;
		__entry->tsc_बारtamp	   = pvघड़ी->tsc_बारtamp;
		__entry->प्रणाली_समय	   = pvघड़ी->प्रणाली_समय;
		__entry->tsc_to_प्रणाली_mul = pvघड़ी->tsc_to_प्रणाली_mul;
		__entry->tsc_shअगरt	   = pvघड़ी->tsc_shअगरt;
		__entry->flags		   = pvघड़ी->flags;
	),

	TP_prपूर्णांकk("vcpu_id %u, pvclock { version %u, tsc_timestamp 0x%llx, "
		  "system_time 0x%llx, tsc_to_system_mul 0x%x, tsc_shift %d, "
		  "flags 0x%x }",
		  __entry->vcpu_id,
		  __entry->version,
		  __entry->tsc_बारtamp,
		  __entry->प्रणाली_समय,
		  __entry->tsc_to_प्रणाली_mul,
		  __entry->tsc_shअगरt,
		  __entry->flags)
);

TRACE_EVENT(kvm_रुको_lapic_expire,
	TP_PROTO(अचिन्हित पूर्णांक vcpu_id, s64 delta),
	TP_ARGS(vcpu_id, delta),

	TP_STRUCT__entry(
		__field(	अचिन्हित पूर्णांक,	vcpu_id		)
		__field(	s64,		delta		)
	),

	TP_fast_assign(
		__entry->vcpu_id	   = vcpu_id;
		__entry->delta             = delta;
	),

	TP_prपूर्णांकk("vcpu %u: delta %lld (%s)",
		  __entry->vcpu_id,
		  __entry->delta,
		  __entry->delta < 0 ? "early" : "late")
);

TRACE_EVENT(kvm_enter_smm,
	TP_PROTO(अचिन्हित पूर्णांक vcpu_id, u64 smbase, bool entering),
	TP_ARGS(vcpu_id, smbase, entering),

	TP_STRUCT__entry(
		__field(	अचिन्हित पूर्णांक,	vcpu_id		)
		__field(	u64,		smbase		)
		__field(	bool,		entering	)
	),

	TP_fast_assign(
		__entry->vcpu_id	= vcpu_id;
		__entry->smbase		= smbase;
		__entry->entering	= entering;
	),

	TP_prपूर्णांकk("vcpu %u: %s SMM, smbase 0x%llx",
		  __entry->vcpu_id,
		  __entry->entering ? "entering" : "leaving",
		  __entry->smbase)
);

/*
 * Tracepoपूर्णांक क्रम VT-d posted-पूर्णांकerrupts.
 */
TRACE_EVENT(kvm_pi_irte_update,
	TP_PROTO(अचिन्हित पूर्णांक host_irq, अचिन्हित पूर्णांक vcpu_id,
		 अचिन्हित पूर्णांक gsi, अचिन्हित पूर्णांक gvec,
		 u64 pi_desc_addr, bool set),
	TP_ARGS(host_irq, vcpu_id, gsi, gvec, pi_desc_addr, set),

	TP_STRUCT__entry(
		__field(	अचिन्हित पूर्णांक,	host_irq	)
		__field(	अचिन्हित पूर्णांक,	vcpu_id		)
		__field(	अचिन्हित पूर्णांक,	gsi		)
		__field(	अचिन्हित पूर्णांक,	gvec		)
		__field(	u64,		pi_desc_addr	)
		__field(	bool,		set		)
	),

	TP_fast_assign(
		__entry->host_irq	= host_irq;
		__entry->vcpu_id	= vcpu_id;
		__entry->gsi		= gsi;
		__entry->gvec		= gvec;
		__entry->pi_desc_addr	= pi_desc_addr;
		__entry->set		= set;
	),

	TP_prपूर्णांकk("VT-d PI is %s for irq %u, vcpu %u, gsi: 0x%x, "
		  "gvec: 0x%x, pi_desc_addr: 0x%llx",
		  __entry->set ? "enabled and being updated" : "disabled",
		  __entry->host_irq,
		  __entry->vcpu_id,
		  __entry->gsi,
		  __entry->gvec,
		  __entry->pi_desc_addr)
);

/*
 * Tracepoपूर्णांक क्रम kvm_hv_notअगरy_acked_sपूर्णांक.
 */
TRACE_EVENT(kvm_hv_notअगरy_acked_sपूर्णांक,
	TP_PROTO(पूर्णांक vcpu_id, u32 sपूर्णांक),
	TP_ARGS(vcpu_id, sपूर्णांक),

	TP_STRUCT__entry(
		__field(पूर्णांक, vcpu_id)
		__field(u32, sपूर्णांक)
	),

	TP_fast_assign(
		__entry->vcpu_id = vcpu_id;
		__entry->sपूर्णांक = sपूर्णांक;
	),

	TP_prपूर्णांकk("vcpu_id %d sint %u", __entry->vcpu_id, __entry->sपूर्णांक)
);

/*
 * Tracepoपूर्णांक क्रम synic_set_irq.
 */
TRACE_EVENT(kvm_hv_synic_set_irq,
	TP_PROTO(पूर्णांक vcpu_id, u32 sपूर्णांक, पूर्णांक vector, पूर्णांक ret),
	TP_ARGS(vcpu_id, sपूर्णांक, vector, ret),

	TP_STRUCT__entry(
		__field(पूर्णांक, vcpu_id)
		__field(u32, sपूर्णांक)
		__field(पूर्णांक, vector)
		__field(पूर्णांक, ret)
	),

	TP_fast_assign(
		__entry->vcpu_id = vcpu_id;
		__entry->sपूर्णांक = sपूर्णांक;
		__entry->vector = vector;
		__entry->ret = ret;
	),

	TP_prपूर्णांकk("vcpu_id %d sint %u vector %d ret %d",
		  __entry->vcpu_id, __entry->sपूर्णांक, __entry->vector,
		  __entry->ret)
);

/*
 * Tracepoपूर्णांक क्रम kvm_hv_synic_send_eoi.
 */
TRACE_EVENT(kvm_hv_synic_send_eoi,
	TP_PROTO(पूर्णांक vcpu_id, पूर्णांक vector),
	TP_ARGS(vcpu_id, vector),

	TP_STRUCT__entry(
		__field(पूर्णांक, vcpu_id)
		__field(u32, sपूर्णांक)
		__field(पूर्णांक, vector)
		__field(पूर्णांक, ret)
	),

	TP_fast_assign(
		__entry->vcpu_id = vcpu_id;
		__entry->vector	= vector;
	),

	TP_prपूर्णांकk("vcpu_id %d vector %d", __entry->vcpu_id, __entry->vector)
);

/*
 * Tracepoपूर्णांक क्रम synic_set_msr.
 */
TRACE_EVENT(kvm_hv_synic_set_msr,
	TP_PROTO(पूर्णांक vcpu_id, u32 msr, u64 data, bool host),
	TP_ARGS(vcpu_id, msr, data, host),

	TP_STRUCT__entry(
		__field(पूर्णांक, vcpu_id)
		__field(u32, msr)
		__field(u64, data)
		__field(bool, host)
	),

	TP_fast_assign(
		__entry->vcpu_id = vcpu_id;
		__entry->msr = msr;
		__entry->data = data;
		__entry->host = host
	),

	TP_prपूर्णांकk("vcpu_id %d msr 0x%x data 0x%llx host %d",
		  __entry->vcpu_id, __entry->msr, __entry->data, __entry->host)
);

/*
 * Tracepoपूर्णांक क्रम sसमयr_set_config.
 */
TRACE_EVENT(kvm_hv_sसमयr_set_config,
	TP_PROTO(पूर्णांक vcpu_id, पूर्णांक समयr_index, u64 config, bool host),
	TP_ARGS(vcpu_id, समयr_index, config, host),

	TP_STRUCT__entry(
		__field(पूर्णांक, vcpu_id)
		__field(पूर्णांक, समयr_index)
		__field(u64, config)
		__field(bool, host)
	),

	TP_fast_assign(
		__entry->vcpu_id = vcpu_id;
		__entry->समयr_index = समयr_index;
		__entry->config = config;
		__entry->host = host;
	),

	TP_prपूर्णांकk("vcpu_id %d timer %d config 0x%llx host %d",
		  __entry->vcpu_id, __entry->समयr_index, __entry->config,
		  __entry->host)
);

/*
 * Tracepoपूर्णांक क्रम sसमयr_set_count.
 */
TRACE_EVENT(kvm_hv_sसमयr_set_count,
	TP_PROTO(पूर्णांक vcpu_id, पूर्णांक समयr_index, u64 count, bool host),
	TP_ARGS(vcpu_id, समयr_index, count, host),

	TP_STRUCT__entry(
		__field(पूर्णांक, vcpu_id)
		__field(पूर्णांक, समयr_index)
		__field(u64, count)
		__field(bool, host)
	),

	TP_fast_assign(
		__entry->vcpu_id = vcpu_id;
		__entry->समयr_index = समयr_index;
		__entry->count = count;
		__entry->host = host;
	),

	TP_prपूर्णांकk("vcpu_id %d timer %d count %llu host %d",
		  __entry->vcpu_id, __entry->समयr_index, __entry->count,
		  __entry->host)
);

/*
 * Tracepoपूर्णांक क्रम sसमयr_start(periodic समयr हाल).
 */
TRACE_EVENT(kvm_hv_sसमयr_start_periodic,
	TP_PROTO(पूर्णांक vcpu_id, पूर्णांक समयr_index, u64 समय_now, u64 exp_समय),
	TP_ARGS(vcpu_id, समयr_index, समय_now, exp_समय),

	TP_STRUCT__entry(
		__field(पूर्णांक, vcpu_id)
		__field(पूर्णांक, समयr_index)
		__field(u64, समय_now)
		__field(u64, exp_समय)
	),

	TP_fast_assign(
		__entry->vcpu_id = vcpu_id;
		__entry->समयr_index = समयr_index;
		__entry->समय_now = समय_now;
		__entry->exp_समय = exp_समय;
	),

	TP_prपूर्णांकk("vcpu_id %d timer %d time_now %llu exp_time %llu",
		  __entry->vcpu_id, __entry->समयr_index, __entry->समय_now,
		  __entry->exp_समय)
);

/*
 * Tracepoपूर्णांक क्रम sसमयr_start(one-shot समयr हाल).
 */
TRACE_EVENT(kvm_hv_sसमयr_start_one_shot,
	TP_PROTO(पूर्णांक vcpu_id, पूर्णांक समयr_index, u64 समय_now, u64 count),
	TP_ARGS(vcpu_id, समयr_index, समय_now, count),

	TP_STRUCT__entry(
		__field(पूर्णांक, vcpu_id)
		__field(पूर्णांक, समयr_index)
		__field(u64, समय_now)
		__field(u64, count)
	),

	TP_fast_assign(
		__entry->vcpu_id = vcpu_id;
		__entry->समयr_index = समयr_index;
		__entry->समय_now = समय_now;
		__entry->count = count;
	),

	TP_prपूर्णांकk("vcpu_id %d timer %d time_now %llu count %llu",
		  __entry->vcpu_id, __entry->समयr_index, __entry->समय_now,
		  __entry->count)
);

/*
 * Tracepoपूर्णांक क्रम sसमयr_समयr_callback.
 */
TRACE_EVENT(kvm_hv_sसमयr_callback,
	TP_PROTO(पूर्णांक vcpu_id, पूर्णांक समयr_index),
	TP_ARGS(vcpu_id, समयr_index),

	TP_STRUCT__entry(
		__field(पूर्णांक, vcpu_id)
		__field(पूर्णांक, समयr_index)
	),

	TP_fast_assign(
		__entry->vcpu_id = vcpu_id;
		__entry->समयr_index = समयr_index;
	),

	TP_prपूर्णांकk("vcpu_id %d timer %d",
		  __entry->vcpu_id, __entry->समयr_index)
);

/*
 * Tracepoपूर्णांक क्रम sसमयr_expiration.
 */
TRACE_EVENT(kvm_hv_sसमयr_expiration,
	TP_PROTO(पूर्णांक vcpu_id, पूर्णांक समयr_index, पूर्णांक direct, पूर्णांक msg_send_result),
	TP_ARGS(vcpu_id, समयr_index, direct, msg_send_result),

	TP_STRUCT__entry(
		__field(पूर्णांक, vcpu_id)
		__field(पूर्णांक, समयr_index)
		__field(पूर्णांक, direct)
		__field(पूर्णांक, msg_send_result)
	),

	TP_fast_assign(
		__entry->vcpu_id = vcpu_id;
		__entry->समयr_index = समयr_index;
		__entry->direct = direct;
		__entry->msg_send_result = msg_send_result;
	),

	TP_prपूर्णांकk("vcpu_id %d timer %d direct %d send result %d",
		  __entry->vcpu_id, __entry->समयr_index,
		  __entry->direct, __entry->msg_send_result)
);

/*
 * Tracepoपूर्णांक क्रम sसमयr_cleanup.
 */
TRACE_EVENT(kvm_hv_sसमयr_cleanup,
	TP_PROTO(पूर्णांक vcpu_id, पूर्णांक समयr_index),
	TP_ARGS(vcpu_id, समयr_index),

	TP_STRUCT__entry(
		__field(पूर्णांक, vcpu_id)
		__field(पूर्णांक, समयr_index)
	),

	TP_fast_assign(
		__entry->vcpu_id = vcpu_id;
		__entry->समयr_index = समयr_index;
	),

	TP_prपूर्णांकk("vcpu_id %d timer %d",
		  __entry->vcpu_id, __entry->समयr_index)
);

TRACE_EVENT(kvm_apicv_update_request,
	    TP_PROTO(bool activate, अचिन्हित दीर्घ bit),
	    TP_ARGS(activate, bit),

	TP_STRUCT__entry(
		__field(bool, activate)
		__field(अचिन्हित दीर्घ, bit)
	),

	TP_fast_assign(
		__entry->activate = activate;
		__entry->bit = bit;
	),

	TP_prपूर्णांकk("%s bit=%lu",
		  __entry->activate ? "activate" : "deactivate",
		  __entry->bit)
);

/*
 * Tracepoपूर्णांक क्रम AMD AVIC
 */
TRACE_EVENT(kvm_avic_incomplete_ipi,
	    TP_PROTO(u32 vcpu, u32 icrh, u32 icrl, u32 id, u32 index),
	    TP_ARGS(vcpu, icrh, icrl, id, index),

	TP_STRUCT__entry(
		__field(u32, vcpu)
		__field(u32, icrh)
		__field(u32, icrl)
		__field(u32, id)
		__field(u32, index)
	),

	TP_fast_assign(
		__entry->vcpu = vcpu;
		__entry->icrh = icrh;
		__entry->icrl = icrl;
		__entry->id = id;
		__entry->index = index;
	),

	TP_prपूर्णांकk("vcpu=%u, icrh:icrl=%#010x:%08x, id=%u, index=%u",
		  __entry->vcpu, __entry->icrh, __entry->icrl,
		  __entry->id, __entry->index)
);

TRACE_EVENT(kvm_avic_unaccelerated_access,
	    TP_PROTO(u32 vcpu, u32 offset, bool ft, bool rw, u32 vec),
	    TP_ARGS(vcpu, offset, ft, rw, vec),

	TP_STRUCT__entry(
		__field(u32, vcpu)
		__field(u32, offset)
		__field(bool, ft)
		__field(bool, rw)
		__field(u32, vec)
	),

	TP_fast_assign(
		__entry->vcpu = vcpu;
		__entry->offset = offset;
		__entry->ft = ft;
		__entry->rw = rw;
		__entry->vec = vec;
	),

	TP_prपूर्णांकk("vcpu=%u, offset=%#x(%s), %s, %s, vec=%#x",
		  __entry->vcpu,
		  __entry->offset,
		  __prपूर्णांक_symbolic(__entry->offset, kvm_trace_symbol_apic),
		  __entry->ft ? "trap" : "fault",
		  __entry->rw ? "write" : "read",
		  __entry->vec)
);

TRACE_EVENT(kvm_avic_ga_log,
	    TP_PROTO(u32 vmid, u32 vcpuid),
	    TP_ARGS(vmid, vcpuid),

	TP_STRUCT__entry(
		__field(u32, vmid)
		__field(u32, vcpuid)
	),

	TP_fast_assign(
		__entry->vmid = vmid;
		__entry->vcpuid = vcpuid;
	),

	TP_prपूर्णांकk("vmid=%u, vcpuid=%u",
		  __entry->vmid, __entry->vcpuid)
);

TRACE_EVENT(kvm_hv_समयr_state,
		TP_PROTO(अचिन्हित पूर्णांक vcpu_id, अचिन्हित पूर्णांक hv_समयr_in_use),
		TP_ARGS(vcpu_id, hv_समयr_in_use),
		TP_STRUCT__entry(
			__field(अचिन्हित पूर्णांक, vcpu_id)
			__field(अचिन्हित पूर्णांक, hv_समयr_in_use)
			),
		TP_fast_assign(
			__entry->vcpu_id = vcpu_id;
			__entry->hv_समयr_in_use = hv_समयr_in_use;
			),
		TP_prपूर्णांकk("vcpu_id %x hv_timer %x",
			__entry->vcpu_id,
			__entry->hv_समयr_in_use)
);

/*
 * Tracepoपूर्णांक क्रम kvm_hv_flush_tlb.
 */
TRACE_EVENT(kvm_hv_flush_tlb,
	TP_PROTO(u64 processor_mask, u64 address_space, u64 flags),
	TP_ARGS(processor_mask, address_space, flags),

	TP_STRUCT__entry(
		__field(u64, processor_mask)
		__field(u64, address_space)
		__field(u64, flags)
	),

	TP_fast_assign(
		__entry->processor_mask = processor_mask;
		__entry->address_space = address_space;
		__entry->flags = flags;
	),

	TP_prपूर्णांकk("processor_mask 0x%llx address_space 0x%llx flags 0x%llx",
		  __entry->processor_mask, __entry->address_space,
		  __entry->flags)
);

/*
 * Tracepoपूर्णांक क्रम kvm_hv_flush_tlb_ex.
 */
TRACE_EVENT(kvm_hv_flush_tlb_ex,
	TP_PROTO(u64 valid_bank_mask, u64 क्रमmat, u64 address_space, u64 flags),
	TP_ARGS(valid_bank_mask, क्रमmat, address_space, flags),

	TP_STRUCT__entry(
		__field(u64, valid_bank_mask)
		__field(u64, क्रमmat)
		__field(u64, address_space)
		__field(u64, flags)
	),

	TP_fast_assign(
		__entry->valid_bank_mask = valid_bank_mask;
		__entry->क्रमmat = क्रमmat;
		__entry->address_space = address_space;
		__entry->flags = flags;
	),

	TP_prपूर्णांकk("valid_bank_mask 0x%llx format 0x%llx "
		  "address_space 0x%llx flags 0x%llx",
		  __entry->valid_bank_mask, __entry->क्रमmat,
		  __entry->address_space, __entry->flags)
);

/*
 * Tracepoपूर्णांकs क्रम kvm_hv_send_ipi.
 */
TRACE_EVENT(kvm_hv_send_ipi,
	TP_PROTO(u32 vector, u64 processor_mask),
	TP_ARGS(vector, processor_mask),

	TP_STRUCT__entry(
		__field(u32, vector)
		__field(u64, processor_mask)
	),

	TP_fast_assign(
		__entry->vector = vector;
		__entry->processor_mask = processor_mask;
	),

	TP_prपूर्णांकk("vector %x processor_mask 0x%llx",
		  __entry->vector, __entry->processor_mask)
);

TRACE_EVENT(kvm_hv_send_ipi_ex,
	TP_PROTO(u32 vector, u64 क्रमmat, u64 valid_bank_mask),
	TP_ARGS(vector, क्रमmat, valid_bank_mask),

	TP_STRUCT__entry(
		__field(u32, vector)
		__field(u64, क्रमmat)
		__field(u64, valid_bank_mask)
	),

	TP_fast_assign(
		__entry->vector = vector;
		__entry->क्रमmat = क्रमmat;
		__entry->valid_bank_mask = valid_bank_mask;
	),

	TP_prपूर्णांकk("vector %x format %llx valid_bank_mask 0x%llx",
		  __entry->vector, __entry->क्रमmat,
		  __entry->valid_bank_mask)
);

TRACE_EVENT(kvm_pv_tlb_flush,
	TP_PROTO(अचिन्हित पूर्णांक vcpu_id, bool need_flush_tlb),
	TP_ARGS(vcpu_id, need_flush_tlb),

	TP_STRUCT__entry(
		__field(	अचिन्हित पूर्णांक,	vcpu_id		)
		__field(	bool,	need_flush_tlb		)
	),

	TP_fast_assign(
		__entry->vcpu_id	= vcpu_id;
		__entry->need_flush_tlb = need_flush_tlb;
	),

	TP_prपूर्णांकk("vcpu %u need_flush_tlb %s", __entry->vcpu_id,
		__entry->need_flush_tlb ? "true" : "false")
);

/*
 * Tracepoपूर्णांक क्रम failed nested VMX VM-Enter.
 */
TRACE_EVENT(kvm_nested_vmenter_failed,
	TP_PROTO(स्थिर अक्षर *msg, u32 err),
	TP_ARGS(msg, err),

	TP_STRUCT__entry(
		__string(msg, msg)
		__field(u32, err)
	),

	TP_fast_assign(
		__assign_str(msg, msg);
		__entry->err = err;
	),

	TP_prपूर्णांकk("%s%s", __get_str(msg), !__entry->err ? "" :
		__prपूर्णांक_symbolic(__entry->err, VMX_VMENTER_INSTRUCTION_ERRORS))
);

/*
 * Tracepoपूर्णांक क्रम syndbg_set_msr.
 */
TRACE_EVENT(kvm_hv_syndbg_set_msr,
	TP_PROTO(पूर्णांक vcpu_id, u32 vp_index, u32 msr, u64 data),
	TP_ARGS(vcpu_id, vp_index, msr, data),

	TP_STRUCT__entry(
		__field(पूर्णांक, vcpu_id)
		__field(u32, vp_index)
		__field(u32, msr)
		__field(u64, data)
	),

	TP_fast_assign(
		__entry->vcpu_id = vcpu_id;
		__entry->vp_index = vp_index;
		__entry->msr = msr;
		__entry->data = data;
	),

	TP_prपूर्णांकk("vcpu_id %d vp_index %u msr 0x%x data 0x%llx",
		  __entry->vcpu_id, __entry->vp_index, __entry->msr,
		  __entry->data)
);

/*
 * Tracepoपूर्णांक क्रम syndbg_get_msr.
 */
TRACE_EVENT(kvm_hv_syndbg_get_msr,
	TP_PROTO(पूर्णांक vcpu_id, u32 vp_index, u32 msr, u64 data),
	TP_ARGS(vcpu_id, vp_index, msr, data),

	TP_STRUCT__entry(
		__field(पूर्णांक, vcpu_id)
		__field(u32, vp_index)
		__field(u32, msr)
		__field(u64, data)
	),

	TP_fast_assign(
		__entry->vcpu_id = vcpu_id;
		__entry->vp_index = vp_index;
		__entry->msr = msr;
		__entry->data = data;
	),

	TP_prपूर्णांकk("vcpu_id %d vp_index %u msr 0x%x data 0x%llx",
		  __entry->vcpu_id, __entry->vp_index, __entry->msr,
		  __entry->data)
);

/*
 * Tracepoपूर्णांक क्रम the start of VMGEXIT processing
 */
TRACE_EVENT(kvm_vmgनिकास_enter,
	TP_PROTO(अचिन्हित पूर्णांक vcpu_id, काष्ठा ghcb *ghcb),
	TP_ARGS(vcpu_id, ghcb),

	TP_STRUCT__entry(
		__field(अचिन्हित पूर्णांक, vcpu_id)
		__field(u64, निकास_reason)
		__field(u64, info1)
		__field(u64, info2)
	),

	TP_fast_assign(
		__entry->vcpu_id     = vcpu_id;
		__entry->निकास_reason = ghcb->save.sw_निकास_code;
		__entry->info1       = ghcb->save.sw_निकास_info_1;
		__entry->info2       = ghcb->save.sw_निकास_info_2;
	),

	TP_prपूर्णांकk("vcpu %u, exit_reason %llx, exit_info1 %llx, exit_info2 %llx",
		  __entry->vcpu_id, __entry->निकास_reason,
		  __entry->info1, __entry->info2)
);

/*
 * Tracepoपूर्णांक क्रम the end of VMGEXIT processing
 */
TRACE_EVENT(kvm_vmgनिकास_निकास,
	TP_PROTO(अचिन्हित पूर्णांक vcpu_id, काष्ठा ghcb *ghcb),
	TP_ARGS(vcpu_id, ghcb),

	TP_STRUCT__entry(
		__field(अचिन्हित पूर्णांक, vcpu_id)
		__field(u64, निकास_reason)
		__field(u64, info1)
		__field(u64, info2)
	),

	TP_fast_assign(
		__entry->vcpu_id     = vcpu_id;
		__entry->निकास_reason = ghcb->save.sw_निकास_code;
		__entry->info1       = ghcb->save.sw_निकास_info_1;
		__entry->info2       = ghcb->save.sw_निकास_info_2;
	),

	TP_prपूर्णांकk("vcpu %u, exit_reason %llx, exit_info1 %llx, exit_info2 %llx",
		  __entry->vcpu_id, __entry->निकास_reason,
		  __entry->info1, __entry->info2)
);

/*
 * Tracepoपूर्णांक क्रम the start of VMGEXIT MSR procotol processing
 */
TRACE_EVENT(kvm_vmgनिकास_msr_protocol_enter,
	TP_PROTO(अचिन्हित पूर्णांक vcpu_id, u64 ghcb_gpa),
	TP_ARGS(vcpu_id, ghcb_gpa),

	TP_STRUCT__entry(
		__field(अचिन्हित पूर्णांक, vcpu_id)
		__field(u64, ghcb_gpa)
	),

	TP_fast_assign(
		__entry->vcpu_id  = vcpu_id;
		__entry->ghcb_gpa = ghcb_gpa;
	),

	TP_prपूर्णांकk("vcpu %u, ghcb_gpa %016llx",
		  __entry->vcpu_id, __entry->ghcb_gpa)
);

/*
 * Tracepoपूर्णांक क्रम the end of VMGEXIT MSR procotol processing
 */
TRACE_EVENT(kvm_vmgनिकास_msr_protocol_निकास,
	TP_PROTO(अचिन्हित पूर्णांक vcpu_id, u64 ghcb_gpa, पूर्णांक result),
	TP_ARGS(vcpu_id, ghcb_gpa, result),

	TP_STRUCT__entry(
		__field(अचिन्हित पूर्णांक, vcpu_id)
		__field(u64, ghcb_gpa)
		__field(पूर्णांक, result)
	),

	TP_fast_assign(
		__entry->vcpu_id  = vcpu_id;
		__entry->ghcb_gpa = ghcb_gpa;
		__entry->result   = result;
	),

	TP_prपूर्णांकk("vcpu %u, ghcb_gpa %016llx, result %d",
		  __entry->vcpu_id, __entry->ghcb_gpa, __entry->result)
);

#पूर्ण_अगर /* _TRACE_KVM_H */

#अघोषित TRACE_INCLUDE_PATH
#घोषणा TRACE_INCLUDE_PATH ../../arch/x86/kvm
#अघोषित TRACE_INCLUDE_खाता
#घोषणा TRACE_INCLUDE_खाता trace

/* This part must be outside protection */
#समावेश <trace/define_trace.h>
