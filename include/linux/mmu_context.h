<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_MMU_CONTEXT_H
#घोषणा _LINUX_MMU_CONTEXT_H

#समावेश <यंत्र/mmu_context.h>
#समावेश <यंत्र/mmu.h>

/* Architectures that care about IRQ state in चयन_mm can override this. */
#अगर_अघोषित चयन_mm_irqs_off
# define चयन_mm_irqs_off चयन_mm
#पूर्ण_अगर

#अगर_अघोषित leave_mm
अटल अंतरभूत व्योम leave_mm(पूर्णांक cpu) अणु पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर
