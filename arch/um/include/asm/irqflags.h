<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __UM_IRQFLAGS_H
#घोषणा __UM_IRQFLAGS_H

बाह्य पूर्णांक get_संकेतs(व्योम);
बाह्य पूर्णांक set_संकेतs(पूर्णांक enable);
बाह्य व्योम block_संकेतs(व्योम);
बाह्य व्योम unblock_संकेतs(व्योम);

#घोषणा arch_local_save_flags arch_local_save_flags
अटल अंतरभूत अचिन्हित दीर्घ arch_local_save_flags(व्योम)
अणु
	वापस get_संकेतs();
पूर्ण

#घोषणा arch_local_irq_restore arch_local_irq_restore
अटल अंतरभूत व्योम arch_local_irq_restore(अचिन्हित दीर्घ flags)
अणु
	set_संकेतs(flags);
पूर्ण

#घोषणा arch_local_irq_enable arch_local_irq_enable
अटल अंतरभूत व्योम arch_local_irq_enable(व्योम)
अणु
	unblock_संकेतs();
पूर्ण

#घोषणा arch_local_irq_disable arch_local_irq_disable
अटल अंतरभूत व्योम arch_local_irq_disable(व्योम)
अणु
	block_संकेतs();
पूर्ण

#घोषणा ARCH_IRQ_DISABLED	0

#समावेश <यंत्र-generic/irqflags.h>

#पूर्ण_अगर
