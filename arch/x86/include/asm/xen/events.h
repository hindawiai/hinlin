<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_X86_XEN_EVENTS_H
#घोषणा _ASM_X86_XEN_EVENTS_H

#समावेश <xen/xen.h>

क्रमागत ipi_vector अणु
	XEN_RESCHEDULE_VECTOR,
	XEN_CALL_FUNCTION_VECTOR,
	XEN_CALL_FUNCTION_SINGLE_VECTOR,
	XEN_SPIN_UNLOCK_VECTOR,
	XEN_IRQ_WORK_VECTOR,
	XEN_NMI_VECTOR,

	XEN_NR_IPIS,
पूर्ण;

अटल अंतरभूत पूर्णांक xen_irqs_disabled(काष्ठा pt_regs *regs)
अणु
	वापस raw_irqs_disabled_flags(regs->flags);
पूर्ण

/* No need क्रम a barrier -- XCHG is a barrier on x86. */
#घोषणा xchg_xen_uदीर्घ(ptr, val) xchg((ptr), (val))

बाह्य पूर्णांक xen_have_vector_callback;

/*
 * Events delivered via platक्रमm PCI पूर्णांकerrupts are always
 * routed to vcpu 0 and hence cannot be rebound.
 */
अटल अंतरभूत bool xen_support_evtchn_rebind(व्योम)
अणु
	वापस (!xen_hvm_करोमुख्य() || xen_have_vector_callback);
पूर्ण

#पूर्ण_अगर /* _ASM_X86_XEN_EVENTS_H */
