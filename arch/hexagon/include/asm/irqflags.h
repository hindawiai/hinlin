<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * IRQ support क्रम the Hexagon architecture
 *
 * Copyright (c) 2010-2011, The Linux Foundation. All rights reserved.
 */

#अगर_अघोषित _ASM_IRQFLAGS_H
#घोषणा _ASM_IRQFLAGS_H

#समावेश <यंत्र/hexagon_vm.h>
#समावेश <linux/types.h>

अटल अंतरभूत अचिन्हित दीर्घ arch_local_save_flags(व्योम)
अणु
	वापस __vmgetie();
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ arch_local_irq_save(व्योम)
अणु
	वापस __vmsetie(VM_INT_DISABLE);
पूर्ण

अटल अंतरभूत bool arch_irqs_disabled_flags(अचिन्हित दीर्घ flags)
अणु
	वापस !flags;
पूर्ण

अटल अंतरभूत bool arch_irqs_disabled(व्योम)
अणु
	वापस !__vmgetie();
पूर्ण

अटल अंतरभूत व्योम arch_local_irq_enable(व्योम)
अणु
	__vmsetie(VM_INT_ENABLE);
पूर्ण

अटल अंतरभूत व्योम arch_local_irq_disable(व्योम)
अणु
	__vmsetie(VM_INT_DISABLE);
पूर्ण

अटल अंतरभूत व्योम arch_local_irq_restore(अचिन्हित दीर्घ flags)
अणु
	__vmsetie(flags);
पूर्ण

#पूर्ण_अगर
