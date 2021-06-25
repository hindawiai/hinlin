<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * include/यंत्र-parisc/irq.h
 *
 * Copyright 2005 Matthew Wilcox <matthew@wil.cx>
 */

#अगर_अघोषित _ASM_PARISC_IRQ_H
#घोषणा _ASM_PARISC_IRQ_H

#समावेश <linux/cpumask.h>
#समावेश <यंत्र/types.h>

#घोषणा NO_IRQ		(-1)

#अगर_घोषित CONFIG_GSC
#घोषणा GSC_IRQ_BASE	16
#घोषणा GSC_IRQ_MAX	63
#घोषणा CPU_IRQ_BASE	64
#अन्यथा
#घोषणा CPU_IRQ_BASE	16
#पूर्ण_अगर

#घोषणा TIMER_IRQ	(CPU_IRQ_BASE + 0)
#घोषणा	IPI_IRQ		(CPU_IRQ_BASE + 1)
#घोषणा CPU_IRQ_MAX	(CPU_IRQ_BASE + (BITS_PER_LONG - 1))

#घोषणा NR_IRQS		(CPU_IRQ_MAX + 1)

अटल __अंतरभूत__ पूर्णांक irq_canonicalize(पूर्णांक irq)
अणु
	वापस (irq == 2) ? 9 : irq;
पूर्ण

काष्ठा irq_chip;
काष्ठा irq_data;

व्योम cpu_ack_irq(काष्ठा irq_data *d);
व्योम cpu_eoi_irq(काष्ठा irq_data *d);

बाह्य पूर्णांक txn_alloc_irq(अचिन्हित पूर्णांक nbits);
बाह्य पूर्णांक txn_claim_irq(पूर्णांक);
बाह्य अचिन्हित पूर्णांक txn_alloc_data(अचिन्हित पूर्णांक);
बाह्य अचिन्हित दीर्घ txn_alloc_addr(अचिन्हित पूर्णांक);
बाह्य अचिन्हित दीर्घ txn_affinity_addr(अचिन्हित पूर्णांक irq, पूर्णांक cpu);

बाह्य पूर्णांक cpu_claim_irq(अचिन्हित पूर्णांक irq, काष्ठा irq_chip *, व्योम *);
बाह्य पूर्णांक cpu_check_affinity(काष्ठा irq_data *d, स्थिर काष्ठा cpumask *dest);

#पूर्ण_अगर	/* _ASM_PARISC_IRQ_H */
