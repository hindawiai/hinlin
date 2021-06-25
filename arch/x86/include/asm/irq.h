<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_X86_IRQ_H
#घोषणा _ASM_X86_IRQ_H
/*
 *	(C) 1992, 1993 Linus Torvalds, (C) 1997 Ingo Molnar
 *
 *	IRQ/IPI changes taken from work by Thomas Radke
 *	<tomsoft@inक्रमmatik.tu-chemnitz.de>
 */

#समावेश <यंत्र/apicdef.h>
#समावेश <यंत्र/irq_vectors.h>

/*
 * The irq entry code is in the noinstr section and the start/end of
 * __irqentry_text is emitted via labels. Make the build fail अगर
 * something moves a C function पूर्णांकo the __irq_entry section.
 */
#घोषणा __irq_entry __invalid_section

अटल अंतरभूत पूर्णांक irq_canonicalize(पूर्णांक irq)
अणु
	वापस ((irq == 2) ? 9 : irq);
पूर्ण

बाह्य पूर्णांक irq_init_percpu_irqstack(अचिन्हित पूर्णांक cpu);

काष्ठा irq_desc;

बाह्य व्योम fixup_irqs(व्योम);

#अगर_घोषित CONFIG_HAVE_KVM
बाह्य व्योम kvm_set_posted_पूर्णांकr_wakeup_handler(व्योम (*handler)(व्योम));
#पूर्ण_अगर

बाह्य व्योम (*x86_platक्रमm_ipi_callback)(व्योम);
बाह्य व्योम native_init_IRQ(व्योम);

बाह्य व्योम __handle_irq(काष्ठा irq_desc *desc, काष्ठा pt_regs *regs);

बाह्य व्योम init_ISA_irqs(व्योम);

बाह्य व्योम __init init_IRQ(व्योम);

#अगर_घोषित CONFIG_X86_LOCAL_APIC
व्योम arch_trigger_cpumask_backtrace(स्थिर काष्ठा cpumask *mask,
				    bool exclude_self);

#घोषणा arch_trigger_cpumask_backtrace arch_trigger_cpumask_backtrace
#पूर्ण_अगर

#पूर्ण_अगर /* _ASM_X86_IRQ_H */
