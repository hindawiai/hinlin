<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_IRQ_WORK_H
#घोषणा _ASM_IRQ_WORK_H

#समावेश <यंत्र/cpufeature.h>

#अगर_घोषित CONFIG_X86_LOCAL_APIC
अटल अंतरभूत bool arch_irq_work_has_पूर्णांकerrupt(व्योम)
अणु
	वापस boot_cpu_has(X86_FEATURE_APIC);
पूर्ण
बाह्य व्योम arch_irq_work_उठाओ(व्योम);
#अन्यथा
अटल अंतरभूत bool arch_irq_work_has_पूर्णांकerrupt(व्योम)
अणु
	वापस false;
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* _ASM_IRQ_WORK_H */
