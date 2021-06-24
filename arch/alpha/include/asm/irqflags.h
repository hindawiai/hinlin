<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ALPHA_IRQFLAGS_H
#घोषणा __ALPHA_IRQFLAGS_H

#समावेश <यंत्र/pal.h>

#घोषणा IPL_MIN		0
#घोषणा IPL_SW0		1
#घोषणा IPL_SW1		2
#घोषणा IPL_DEV0	3
#घोषणा IPL_DEV1	4
#घोषणा IPL_TIMER	5
#घोषणा IPL_PERF	6
#घोषणा IPL_POWERFAIL	6
#घोषणा IPL_MCHECK	7
#घोषणा IPL_MAX		7

#अगर_घोषित CONFIG_ALPHA_BROKEN_IRQ_MASK
#अघोषित IPL_MIN
#घोषणा IPL_MIN		__min_ipl
बाह्य पूर्णांक __min_ipl;
#पूर्ण_अगर

#घोषणा getipl()		(rdps() & 7)
#घोषणा setipl(ipl)		((व्योम) swpipl(ipl))

अटल अंतरभूत अचिन्हित दीर्घ arch_local_save_flags(व्योम)
अणु
	वापस rdps();
पूर्ण

अटल अंतरभूत व्योम arch_local_irq_disable(व्योम)
अणु
	setipl(IPL_MAX);
	barrier();
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ arch_local_irq_save(व्योम)
अणु
	अचिन्हित दीर्घ flags = swpipl(IPL_MAX);
	barrier();
	वापस flags;
पूर्ण

अटल अंतरभूत व्योम arch_local_irq_enable(व्योम)
अणु
	barrier();
	setipl(IPL_MIN);
पूर्ण

अटल अंतरभूत व्योम arch_local_irq_restore(अचिन्हित दीर्घ flags)
अणु
	barrier();
	setipl(flags);
	barrier();
पूर्ण

अटल अंतरभूत bool arch_irqs_disabled_flags(अचिन्हित दीर्घ flags)
अणु
	वापस flags == IPL_MAX;
पूर्ण

अटल अंतरभूत bool arch_irqs_disabled(व्योम)
अणु
	वापस arch_irqs_disabled_flags(getipl());
पूर्ण

#पूर्ण_अगर /* __ALPHA_IRQFLAGS_H */
