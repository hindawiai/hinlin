<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2012 Regents of the University of Calअगरornia
 */


#अगर_अघोषित _ASM_RISCV_IRQFLAGS_H
#घोषणा _ASM_RISCV_IRQFLAGS_H

#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/csr.h>

/* पढ़ो पूर्णांकerrupt enabled status */
अटल अंतरभूत अचिन्हित दीर्घ arch_local_save_flags(व्योम)
अणु
	वापस csr_पढ़ो(CSR_STATUS);
पूर्ण

/* unconditionally enable पूर्णांकerrupts */
अटल अंतरभूत व्योम arch_local_irq_enable(व्योम)
अणु
	csr_set(CSR_STATUS, SR_IE);
पूर्ण

/* unconditionally disable पूर्णांकerrupts */
अटल अंतरभूत व्योम arch_local_irq_disable(व्योम)
अणु
	csr_clear(CSR_STATUS, SR_IE);
पूर्ण

/* get status and disable पूर्णांकerrupts */
अटल अंतरभूत अचिन्हित दीर्घ arch_local_irq_save(व्योम)
अणु
	वापस csr_पढ़ो_clear(CSR_STATUS, SR_IE);
पूर्ण

/* test flags */
अटल अंतरभूत पूर्णांक arch_irqs_disabled_flags(अचिन्हित दीर्घ flags)
अणु
	वापस !(flags & SR_IE);
पूर्ण

/* test hardware पूर्णांकerrupt enable bit */
अटल अंतरभूत पूर्णांक arch_irqs_disabled(व्योम)
अणु
	वापस arch_irqs_disabled_flags(arch_local_save_flags());
पूर्ण

/* set पूर्णांकerrupt enabled status */
अटल अंतरभूत व्योम arch_local_irq_restore(अचिन्हित दीर्घ flags)
अणु
	csr_set(CSR_STATUS, flags & SR_IE);
पूर्ण

#पूर्ण_अगर /* _ASM_RISCV_IRQFLAGS_H */
