<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright (C) 2010 Thomas Chou <thomas@wytron.com.tw>
 */
#अगर_अघोषित _ASM_IRQFLAGS_H
#घोषणा _ASM_IRQFLAGS_H

#समावेश <यंत्र/रेजिस्टरs.h>

अटल अंतरभूत अचिन्हित दीर्घ arch_local_save_flags(व्योम)
अणु
	वापस RDCTL(CTL_STATUS);
पूर्ण

/*
 * This will restore ALL status रेजिस्टर flags, not only the पूर्णांकerrupt
 * mask flag.
 */
अटल अंतरभूत व्योम arch_local_irq_restore(अचिन्हित दीर्घ flags)
अणु
	WRCTL(CTL_STATUS, flags);
पूर्ण

अटल अंतरभूत व्योम arch_local_irq_disable(व्योम)
अणु
	अचिन्हित दीर्घ flags;

	flags = arch_local_save_flags();
	arch_local_irq_restore(flags & ~STATUS_PIE);
पूर्ण

अटल अंतरभूत व्योम arch_local_irq_enable(व्योम)
अणु
	अचिन्हित दीर्घ flags;

	flags = arch_local_save_flags();
	arch_local_irq_restore(flags | STATUS_PIE);
पूर्ण

अटल अंतरभूत पूर्णांक arch_irqs_disabled_flags(अचिन्हित दीर्घ flags)
अणु
	वापस (flags & STATUS_PIE) == 0;
पूर्ण

अटल अंतरभूत पूर्णांक arch_irqs_disabled(व्योम)
अणु
	वापस arch_irqs_disabled_flags(arch_local_save_flags());
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ arch_local_irq_save(व्योम)
अणु
	अचिन्हित दीर्घ flags;

	flags = arch_local_save_flags();
	arch_local_irq_restore(flags & ~STATUS_PIE);
	वापस flags;
पूर्ण

#पूर्ण_अगर /* _ASM_IRQFLAGS_H */
