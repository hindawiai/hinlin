<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_GENERIC_IRQFLAGS_H
#घोषणा __ASM_GENERIC_IRQFLAGS_H

/*
 * All architectures should implement at least the first two functions,
 * usually अंतरभूत assembly will be the best way.
 */
#अगर_अघोषित ARCH_IRQ_DISABLED
#घोषणा ARCH_IRQ_DISABLED 0
#घोषणा ARCH_IRQ_ENABLED 1
#पूर्ण_अगर

/* पढ़ो पूर्णांकerrupt enabled status */
#अगर_अघोषित arch_local_save_flags
अचिन्हित दीर्घ arch_local_save_flags(व्योम);
#पूर्ण_अगर

/* set पूर्णांकerrupt enabled status */
#अगर_अघोषित arch_local_irq_restore
व्योम arch_local_irq_restore(अचिन्हित दीर्घ flags);
#पूर्ण_अगर

/* get status and disable पूर्णांकerrupts */
#अगर_अघोषित arch_local_irq_save
अटल अंतरभूत अचिन्हित दीर्घ arch_local_irq_save(व्योम)
अणु
	अचिन्हित दीर्घ flags;
	flags = arch_local_save_flags();
	arch_local_irq_restore(ARCH_IRQ_DISABLED);
	वापस flags;
पूर्ण
#पूर्ण_अगर

/* test flags */
#अगर_अघोषित arch_irqs_disabled_flags
अटल अंतरभूत पूर्णांक arch_irqs_disabled_flags(अचिन्हित दीर्घ flags)
अणु
	वापस flags == ARCH_IRQ_DISABLED;
पूर्ण
#पूर्ण_अगर

/* unconditionally enable पूर्णांकerrupts */
#अगर_अघोषित arch_local_irq_enable
अटल अंतरभूत व्योम arch_local_irq_enable(व्योम)
अणु
	arch_local_irq_restore(ARCH_IRQ_ENABLED);
पूर्ण
#पूर्ण_अगर

/* unconditionally disable पूर्णांकerrupts */
#अगर_अघोषित arch_local_irq_disable
अटल अंतरभूत व्योम arch_local_irq_disable(व्योम)
अणु
	arch_local_irq_restore(ARCH_IRQ_DISABLED);
पूर्ण
#पूर्ण_अगर

/* test hardware पूर्णांकerrupt enable bit */
#अगर_अघोषित arch_irqs_disabled
अटल अंतरभूत पूर्णांक arch_irqs_disabled(व्योम)
अणु
	वापस arch_irqs_disabled_flags(arch_local_save_flags());
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* __ASM_GENERIC_IRQFLAGS_H */
