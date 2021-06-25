<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर !defined(_TRACE_KVM_MAIN_H) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा _TRACE_KVM_MAIN_H

#समावेश <linux/tracepoपूर्णांक.h>

#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM kvm

#घोषणा ERSN(x) अणु KVM_EXIT_##x, "KVM_EXIT_" #x पूर्ण

#घोषणा kvm_trace_निकास_reason						\
	ERSN(UNKNOWN), ERSN(EXCEPTION), ERSN(IO), ERSN(HYPERCALL),	\
	ERSN(DEBUG), ERSN(HLT), ERSN(MMIO), ERSN(IRQ_WINDOW_OPEN),	\
	ERSN(SHUTDOWN), ERSN(FAIL_ENTRY), ERSN(INTR), ERSN(SET_TPR),	\
	ERSN(TPR_ACCESS), ERSN(S390_SIEIC), ERSN(S390_RESET), ERSN(DCR),\
	ERSN(NMI), ERSN(INTERNAL_ERROR), ERSN(OSI), ERSN(PAPR_HCALL),	\
	ERSN(S390_UCONTROL), ERSN(WATCHDOG), ERSN(S390_TSCH), ERSN(EPR),\
	ERSN(SYSTEM_EVENT), ERSN(S390_STSI), ERSN(IOAPIC_EOI),          \
	ERSN(HYPERV), ERSN(ARM_NISV), ERSN(X86_RDMSR), ERSN(X86_WRMSR)

TRACE_EVENT(kvm_userspace_निकास,
	    TP_PROTO(__u32 reason, पूर्णांक त्रुटि_सं),
	    TP_ARGS(reason, त्रुटि_सं),

	TP_STRUCT__entry(
		__field(	__u32,		reason		)
		__field(	पूर्णांक,		त्रुटि_सं		)
	),

	TP_fast_assign(
		__entry->reason		= reason;
		__entry->त्रुटि_सं		= त्रुटि_सं;
	),

	TP_prपूर्णांकk("reason %s (%d)",
		  __entry->त्रुटि_सं < 0 ?
		  (__entry->त्रुटि_सं == -EINTR ? "restart" : "error") :
		  __prपूर्णांक_symbolic(__entry->reason, kvm_trace_निकास_reason),
		  __entry->त्रुटि_सं < 0 ? -__entry->त्रुटि_सं : __entry->reason)
);

TRACE_EVENT(kvm_vcpu_wakeup,
	    TP_PROTO(__u64 ns, bool रुकोed, bool valid),
	    TP_ARGS(ns, रुकोed, valid),

	TP_STRUCT__entry(
		__field(	__u64,		ns		)
		__field(	bool,		रुकोed		)
		__field(	bool,		valid		)
	),

	TP_fast_assign(
		__entry->ns		= ns;
		__entry->रुकोed		= रुकोed;
		__entry->valid		= valid;
	),

	TP_prपूर्णांकk("%s time %lld ns, polling %s",
		  __entry->रुकोed ? "wait" : "poll",
		  __entry->ns,
		  __entry->valid ? "valid" : "invalid")
);

#अगर defined(CONFIG_HAVE_KVM_IRQFD)
TRACE_EVENT(kvm_set_irq,
	TP_PROTO(अचिन्हित पूर्णांक gsi, पूर्णांक level, पूर्णांक irq_source_id),
	TP_ARGS(gsi, level, irq_source_id),

	TP_STRUCT__entry(
		__field(	अचिन्हित पूर्णांक,	gsi		)
		__field(	पूर्णांक,		level		)
		__field(	पूर्णांक,		irq_source_id	)
	),

	TP_fast_assign(
		__entry->gsi		= gsi;
		__entry->level		= level;
		__entry->irq_source_id	= irq_source_id;
	),

	TP_prपूर्णांकk("gsi %u level %d source %d",
		  __entry->gsi, __entry->level, __entry->irq_source_id)
);
#पूर्ण_अगर /* defined(CONFIG_HAVE_KVM_IRQFD) */

#अगर defined(__KVM_HAVE_IOAPIC)
#घोषणा kvm_deliver_mode		\
	अणु0x0, "Fixed"पूर्ण,			\
	अणु0x1, "LowPrio"पूर्ण,		\
	अणु0x2, "SMI"पूर्ण,			\
	अणु0x3, "Res3"पूर्ण,			\
	अणु0x4, "NMI"पूर्ण,			\
	अणु0x5, "INIT"पूर्ण,			\
	अणु0x6, "SIPI"पूर्ण,			\
	अणु0x7, "ExtINT"पूर्ण

TRACE_EVENT(kvm_ioapic_set_irq,
	    TP_PROTO(__u64 e, पूर्णांक pin, bool coalesced),
	    TP_ARGS(e, pin, coalesced),

	TP_STRUCT__entry(
		__field(	__u64,		e		)
		__field(	पूर्णांक,		pin		)
		__field(	bool,		coalesced	)
	),

	TP_fast_assign(
		__entry->e		= e;
		__entry->pin		= pin;
		__entry->coalesced	= coalesced;
	),

	TP_prपूर्णांकk("pin %u dst %x vec %u (%s|%s|%s%s)%s",
		  __entry->pin, (u8)(__entry->e >> 56), (u8)__entry->e,
		  __prपूर्णांक_symbolic((__entry->e >> 8 & 0x7), kvm_deliver_mode),
		  (__entry->e & (1<<11)) ? "logical" : "physical",
		  (__entry->e & (1<<15)) ? "level" : "edge",
		  (__entry->e & (1<<16)) ? "|masked" : "",
		  __entry->coalesced ? " (coalesced)" : "")
);

TRACE_EVENT(kvm_ioapic_delayed_eoi_inj,
	    TP_PROTO(__u64 e),
	    TP_ARGS(e),

	TP_STRUCT__entry(
		__field(	__u64,		e		)
	),

	TP_fast_assign(
		__entry->e		= e;
	),

	TP_prपूर्णांकk("dst %x vec %u (%s|%s|%s%s)",
		  (u8)(__entry->e >> 56), (u8)__entry->e,
		  __prपूर्णांक_symbolic((__entry->e >> 8 & 0x7), kvm_deliver_mode),
		  (__entry->e & (1<<11)) ? "logical" : "physical",
		  (__entry->e & (1<<15)) ? "level" : "edge",
		  (__entry->e & (1<<16)) ? "|masked" : "")
);

TRACE_EVENT(kvm_msi_set_irq,
	    TP_PROTO(__u64 address, __u64 data),
	    TP_ARGS(address, data),

	TP_STRUCT__entry(
		__field(	__u64,		address		)
		__field(	__u64,		data		)
	),

	TP_fast_assign(
		__entry->address	= address;
		__entry->data		= data;
	),

	TP_prपूर्णांकk("dst %llx vec %u (%s|%s|%s%s)",
		  (u8)(__entry->address >> 12) | ((__entry->address >> 32) & 0xffffff00),
		  (u8)__entry->data,
		  __prपूर्णांक_symbolic((__entry->data >> 8 & 0x7), kvm_deliver_mode),
		  (__entry->address & (1<<2)) ? "logical" : "physical",
		  (__entry->data & (1<<15)) ? "level" : "edge",
		  (__entry->address & (1<<3)) ? "|rh" : "")
);

#घोषणा kvm_irqchips						\
	अणुKVM_IRQCHIP_PIC_MASTER,	"PIC master"पूर्ण,		\
	अणुKVM_IRQCHIP_PIC_SLAVE,		"PIC slave"पूर्ण,		\
	अणुKVM_IRQCHIP_IOAPIC,		"IOAPIC"पूर्ण

#पूर्ण_अगर /* defined(__KVM_HAVE_IOAPIC) */

#अगर defined(CONFIG_HAVE_KVM_IRQFD)

#अगर_घोषित kvm_irqchips
#घोषणा kvm_ack_irq_string "irqchip %s pin %u"
#घोषणा kvm_ack_irq_parm  __prपूर्णांक_symbolic(__entry->irqchip, kvm_irqchips), __entry->pin
#अन्यथा
#घोषणा kvm_ack_irq_string "irqchip %d pin %u"
#घोषणा kvm_ack_irq_parm  __entry->irqchip, __entry->pin
#पूर्ण_अगर

TRACE_EVENT(kvm_ack_irq,
	TP_PROTO(अचिन्हित पूर्णांक irqchip, अचिन्हित पूर्णांक pin),
	TP_ARGS(irqchip, pin),

	TP_STRUCT__entry(
		__field(	अचिन्हित पूर्णांक,	irqchip		)
		__field(	अचिन्हित पूर्णांक,	pin		)
	),

	TP_fast_assign(
		__entry->irqchip	= irqchip;
		__entry->pin		= pin;
	),

	TP_prपूर्णांकk(kvm_ack_irq_string, kvm_ack_irq_parm)
);

#पूर्ण_अगर /* defined(CONFIG_HAVE_KVM_IRQFD) */



#घोषणा KVM_TRACE_MMIO_READ_UNSATISFIED 0
#घोषणा KVM_TRACE_MMIO_READ 1
#घोषणा KVM_TRACE_MMIO_WRITE 2

#घोषणा kvm_trace_symbol_mmio \
	अणु KVM_TRACE_MMIO_READ_UNSATISFIED, "unsatisfied-read" पूर्ण, \
	अणु KVM_TRACE_MMIO_READ, "read" पूर्ण, \
	अणु KVM_TRACE_MMIO_WRITE, "write" पूर्ण

TRACE_EVENT(kvm_mmio,
	TP_PROTO(पूर्णांक type, पूर्णांक len, u64 gpa, व्योम *val),
	TP_ARGS(type, len, gpa, val),

	TP_STRUCT__entry(
		__field(	u32,	type		)
		__field(	u32,	len		)
		__field(	u64,	gpa		)
		__field(	u64,	val		)
	),

	TP_fast_assign(
		__entry->type		= type;
		__entry->len		= len;
		__entry->gpa		= gpa;
		__entry->val		= 0;
		अगर (val)
			स_नकल(&__entry->val, val,
			       min_t(u32, माप(__entry->val), len));
	),

	TP_prपूर्णांकk("mmio %s len %u gpa 0x%llx val 0x%llx",
		  __prपूर्णांक_symbolic(__entry->type, kvm_trace_symbol_mmio),
		  __entry->len, __entry->gpa, __entry->val)
);

#घोषणा kvm_fpu_load_symbol	\
	अणु0, "unload"पूर्ण,		\
	अणु1, "load"पूर्ण

TRACE_EVENT(kvm_fpu,
	TP_PROTO(पूर्णांक load),
	TP_ARGS(load),

	TP_STRUCT__entry(
		__field(	u32,	        load		)
	),

	TP_fast_assign(
		__entry->load		= load;
	),

	TP_prपूर्णांकk("%s", __prपूर्णांक_symbolic(__entry->load, kvm_fpu_load_symbol))
);

#अगर_घोषित CONFIG_KVM_ASYNC_PF
DECLARE_EVENT_CLASS(kvm_async_get_page_class,

	TP_PROTO(u64 gva, u64 gfn),

	TP_ARGS(gva, gfn),

	TP_STRUCT__entry(
		__field(__u64, gva)
		__field(u64, gfn)
	),

	TP_fast_assign(
		__entry->gva = gva;
		__entry->gfn = gfn;
	),

	TP_prपूर्णांकk("gva = %#llx, gfn = %#llx", __entry->gva, __entry->gfn)
);

DEFINE_EVENT(kvm_async_get_page_class, kvm_try_async_get_page,

	TP_PROTO(u64 gva, u64 gfn),

	TP_ARGS(gva, gfn)
);

DEFINE_EVENT(kvm_async_get_page_class, kvm_async_pf_द्विगुनfault,

	TP_PROTO(u64 gva, u64 gfn),

	TP_ARGS(gva, gfn)
);

DECLARE_EVENT_CLASS(kvm_async_pf_nopresent_पढ़ोy,

	TP_PROTO(u64 token, u64 gva),

	TP_ARGS(token, gva),

	TP_STRUCT__entry(
		__field(__u64, token)
		__field(__u64, gva)
	),

	TP_fast_assign(
		__entry->token = token;
		__entry->gva = gva;
	),

	TP_prपूर्णांकk("token %#llx gva %#llx", __entry->token, __entry->gva)

);

DEFINE_EVENT(kvm_async_pf_nopresent_पढ़ोy, kvm_async_pf_not_present,

	TP_PROTO(u64 token, u64 gva),

	TP_ARGS(token, gva)
);

DEFINE_EVENT(kvm_async_pf_nopresent_पढ़ोy, kvm_async_pf_पढ़ोy,

	TP_PROTO(u64 token, u64 gva),

	TP_ARGS(token, gva)
);

TRACE_EVENT(
	kvm_async_pf_completed,
	TP_PROTO(अचिन्हित दीर्घ address, u64 gva),
	TP_ARGS(address, gva),

	TP_STRUCT__entry(
		__field(अचिन्हित दीर्घ, address)
		__field(u64, gva)
		),

	TP_fast_assign(
		__entry->address = address;
		__entry->gva = gva;
		),

	TP_prपूर्णांकk("gva %#llx address %#lx",  __entry->gva,
		  __entry->address)
);

#पूर्ण_अगर

TRACE_EVENT(kvm_halt_poll_ns,
	TP_PROTO(bool grow, अचिन्हित पूर्णांक vcpu_id, अचिन्हित पूर्णांक new,
		 अचिन्हित पूर्णांक old),
	TP_ARGS(grow, vcpu_id, new, old),

	TP_STRUCT__entry(
		__field(bool, grow)
		__field(अचिन्हित पूर्णांक, vcpu_id)
		__field(अचिन्हित पूर्णांक, new)
		__field(अचिन्हित पूर्णांक, old)
	),

	TP_fast_assign(
		__entry->grow           = grow;
		__entry->vcpu_id        = vcpu_id;
		__entry->new            = new;
		__entry->old            = old;
	),

	TP_prपूर्णांकk("vcpu %u: halt_poll_ns %u (%s %u)",
			__entry->vcpu_id,
			__entry->new,
			__entry->grow ? "grow" : "shrink",
			__entry->old)
);

#घोषणा trace_kvm_halt_poll_ns_grow(vcpu_id, new, old) \
	trace_kvm_halt_poll_ns(true, vcpu_id, new, old)
#घोषणा trace_kvm_halt_poll_ns_shrink(vcpu_id, new, old) \
	trace_kvm_halt_poll_ns(false, vcpu_id, new, old)

TRACE_EVENT(kvm_dirty_ring_push,
	TP_PROTO(काष्ठा kvm_dirty_ring *ring, u32 slot, u64 offset),
	TP_ARGS(ring, slot, offset),

	TP_STRUCT__entry(
		__field(पूर्णांक, index)
		__field(u32, dirty_index)
		__field(u32, reset_index)
		__field(u32, slot)
		__field(u64, offset)
	),

	TP_fast_assign(
		__entry->index          = ring->index;
		__entry->dirty_index    = ring->dirty_index;
		__entry->reset_index    = ring->reset_index;
		__entry->slot           = slot;
		__entry->offset         = offset;
	),

	TP_prपूर्णांकk("ring %d: dirty 0x%x reset 0x%x "
		  "slot %u offset 0x%llx (used %u)",
		  __entry->index, __entry->dirty_index,
		  __entry->reset_index,  __entry->slot, __entry->offset,
		  __entry->dirty_index - __entry->reset_index)
);

TRACE_EVENT(kvm_dirty_ring_reset,
	TP_PROTO(काष्ठा kvm_dirty_ring *ring),
	TP_ARGS(ring),

	TP_STRUCT__entry(
		__field(पूर्णांक, index)
		__field(u32, dirty_index)
		__field(u32, reset_index)
	),

	TP_fast_assign(
		__entry->index          = ring->index;
		__entry->dirty_index    = ring->dirty_index;
		__entry->reset_index    = ring->reset_index;
	),

	TP_prपूर्णांकk("ring %d: dirty 0x%x reset 0x%x (used %u)",
		  __entry->index, __entry->dirty_index, __entry->reset_index,
		  __entry->dirty_index - __entry->reset_index)
);

TRACE_EVENT(kvm_dirty_ring_निकास,
	TP_PROTO(काष्ठा kvm_vcpu *vcpu),
	TP_ARGS(vcpu),

	TP_STRUCT__entry(
	    __field(पूर्णांक, vcpu_id)
	),

	TP_fast_assign(
	    __entry->vcpu_id = vcpu->vcpu_id;
	),

	TP_prपूर्णांकk("vcpu %d", __entry->vcpu_id)
);

TRACE_EVENT(kvm_unmap_hva_range,
	TP_PROTO(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end),
	TP_ARGS(start, end),

	TP_STRUCT__entry(
		__field(	अचिन्हित दीर्घ,	start		)
		__field(	अचिन्हित दीर्घ,	end		)
	),

	TP_fast_assign(
		__entry->start		= start;
		__entry->end		= end;
	),

	TP_prपूर्णांकk("mmu notifier unmap range: %#016lx -- %#016lx",
		  __entry->start, __entry->end)
);

TRACE_EVENT(kvm_set_spte_hva,
	TP_PROTO(अचिन्हित दीर्घ hva),
	TP_ARGS(hva),

	TP_STRUCT__entry(
		__field(	अचिन्हित दीर्घ,	hva		)
	),

	TP_fast_assign(
		__entry->hva		= hva;
	),

	TP_prपूर्णांकk("mmu notifier set pte hva: %#016lx", __entry->hva)
);

TRACE_EVENT(kvm_age_hva,
	TP_PROTO(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end),
	TP_ARGS(start, end),

	TP_STRUCT__entry(
		__field(	अचिन्हित दीर्घ,	start		)
		__field(	अचिन्हित दीर्घ,	end		)
	),

	TP_fast_assign(
		__entry->start		= start;
		__entry->end		= end;
	),

	TP_prपूर्णांकk("mmu notifier age hva: %#016lx -- %#016lx",
		  __entry->start, __entry->end)
);

TRACE_EVENT(kvm_test_age_hva,
	TP_PROTO(अचिन्हित दीर्घ hva),
	TP_ARGS(hva),

	TP_STRUCT__entry(
		__field(	अचिन्हित दीर्घ,	hva		)
	),

	TP_fast_assign(
		__entry->hva		= hva;
	),

	TP_prपूर्णांकk("mmu notifier test age hva: %#016lx", __entry->hva)
);

#पूर्ण_अगर /* _TRACE_KVM_MAIN_H */

/* This part must be outside protection */
#समावेश <trace/define_trace.h>
