<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_SH_IRQ_H
#घोषणा __ASM_SH_IRQ_H

#समावेश <linux/cpumask.h>
#समावेश <यंत्र/machvec.h>

/*
 * Only legacy non-sparseirq platक्रमms have to set a reasonably sane
 * value here. sparseirq platक्रमms allocate their irq_descs on the fly,
 * so will expand स्वतःmatically based on the number of रेजिस्टरed IRQs.
 */
#अगर_घोषित CONFIG_SPARSE_IRQ
# define NR_IRQS		8
#अन्यथा
# define NR_IRQS		512
#पूर्ण_अगर

/*
 * This is a special IRQ number क्रम indicating that no IRQ has been
 * triggered and to simply ignore the IRQ dispatch. This is a special
 * हाल that can happen with IRQ स्वतः-distribution when multiple CPUs
 * are woken up and संकेतled in parallel.
 */
#घोषणा NO_IRQ_IGNORE		((अचिन्हित पूर्णांक)-1)

/*
 * Simple Mask Register Support
 */
बाह्य व्योम make_maskreg_irq(अचिन्हित पूर्णांक irq);
बाह्य अचिन्हित लघु *irq_mask_रेजिस्टर;

/*
 * PINT IRQs
 */
व्योम init_IRQ_pपूर्णांक(व्योम);
व्योम make_imask_irq(अचिन्हित पूर्णांक irq);

अटल अंतरभूत पूर्णांक generic_irq_demux(पूर्णांक irq)
अणु
	वापस irq;
पूर्ण

#घोषणा irq_demux(irq)		sh_mv.mv_irq_demux(irq)

व्योम init_IRQ(व्योम);
व्योम migrate_irqs(व्योम);

यंत्रlinkage पूर्णांक करो_IRQ(अचिन्हित पूर्णांक irq, काष्ठा pt_regs *regs);

#अगर_घोषित CONFIG_IRQSTACKS
बाह्य व्योम irq_ctx_init(पूर्णांक cpu);
बाह्य व्योम irq_ctx_निकास(पूर्णांक cpu);
#अन्यथा
# define irq_ctx_init(cpu) करो अणु पूर्ण जबतक (0)
# define irq_ctx_निकास(cpu) करो अणु पूर्ण जबतक (0)
#पूर्ण_अगर

#अगर_घोषित CONFIG_INTC_BALANCING
बाह्य अचिन्हित पूर्णांक irq_lookup(अचिन्हित पूर्णांक irq);
बाह्य व्योम irq_finish(अचिन्हित पूर्णांक irq);
#अन्यथा
#घोषणा irq_lookup(irq)		(irq)
#घोषणा irq_finish(irq)		करो अणु पूर्ण जबतक (0)
#पूर्ण_अगर

#समावेश <यंत्र-generic/irq.h>

#पूर्ण_अगर /* __ASM_SH_IRQ_H */
