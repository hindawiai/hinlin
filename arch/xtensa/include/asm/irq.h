<शैली गुरु>
/*
 * include/यंत्र-xtensa/irq.h
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2001 - 2005 Tensilica Inc.
 */

#अगर_अघोषित _XTENSA_IRQ_H
#घोषणा _XTENSA_IRQ_H

#समावेश <linux/init.h>
#समावेश <यंत्र/core.h>

#अगर_घोषित CONFIG_PLATFORM_NR_IRQS
# define PLATFORM_NR_IRQS CONFIG_PLATFORM_NR_IRQS
#अन्यथा
# define PLATFORM_NR_IRQS 0
#पूर्ण_अगर
#घोषणा XTENSA_NR_IRQS XCHAL_NUM_INTERRUPTS
#घोषणा NR_IRQS (XTENSA_NR_IRQS + PLATFORM_NR_IRQS + 1)
#घोषणा XTENSA_PIC_LINUX_IRQ(hwirq) ((hwirq) + 1)

अटल __अंतरभूत__ पूर्णांक irq_canonicalize(पूर्णांक irq)
अणु
	वापस (irq);
पूर्ण

काष्ठा irqaction;
काष्ठा irq_करोमुख्य;

व्योम migrate_irqs(व्योम);
पूर्णांक xtensa_irq_करोमुख्य_xlate(स्थिर u32 *पूर्णांकspec, अचिन्हित पूर्णांक पूर्णांकsize,
		अचिन्हित दीर्घ पूर्णांक_irq, अचिन्हित दीर्घ ext_irq,
		अचिन्हित दीर्घ *out_hwirq, अचिन्हित पूर्णांक *out_type);
पूर्णांक xtensa_irq_map(काष्ठा irq_करोमुख्य *d, अचिन्हित पूर्णांक irq, irq_hw_number_t hw);
अचिन्हित xtensa_map_ext_irq(अचिन्हित ext_irq);
अचिन्हित xtensa_get_ext_irq_no(अचिन्हित irq);

#पूर्ण_अगर	/* _XTENSA_IRQ_H */
