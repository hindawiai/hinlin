<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_ARM_XEN_EVENTS_H
#घोषणा _ASM_ARM_XEN_EVENTS_H

#समावेश <यंत्र/ptrace.h>
#समावेश <यंत्र/atomic.h>

क्रमागत ipi_vector अणु
	XEN_PLACEHOLDER_VECTOR,

	/* Xen IPIs go here */
	XEN_NR_IPIS,
पूर्ण;

अटल अंतरभूत पूर्णांक xen_irqs_disabled(काष्ठा pt_regs *regs)
अणु
	वापस raw_irqs_disabled_flags(regs->ARM_cpsr);
पूर्ण

#घोषणा xchg_xen_uदीर्घ(ptr, val) atomic64_xchg(container_of((दीर्घ दीर्घ*)(ptr),\
							    atomic64_t,	\
							    counter), (val))

/* Rebind event channel is supported by शेष */
अटल अंतरभूत bool xen_support_evtchn_rebind(व्योम)
अणु
	वापस true;
पूर्ण

#पूर्ण_अगर /* _ASM_ARM_XEN_EVENTS_H */
