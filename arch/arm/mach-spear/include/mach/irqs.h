<शैली गुरु>
/*
 * IRQ helper macros क्रम spear machine family
 *
 * Copyright (C) 2009-2012 ST Microelectronics
 * Rajeev Kumar <rajeev-dlh.kumar@st.com>
 * Viresh Kumar <vireshk@kernel.org>
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2. This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#अगर_अघोषित __MACH_IRQS_H
#घोषणा __MACH_IRQS_H

#अगर_घोषित CONFIG_ARCH_SPEAR3XX
#घोषणा NR_IRQS			256
#पूर्ण_अगर

#अगर_घोषित CONFIG_ARCH_SPEAR6XX
/* IRQ definitions */
/* VIC 1 */
#घोषणा IRQ_VIC_END				64

/* GPIO pins भव irqs */
#घोषणा VIRTUAL_IRQS				24
#घोषणा NR_IRQS					(IRQ_VIC_END + VIRTUAL_IRQS)
#पूर्ण_अगर

#अगर_घोषित CONFIG_ARCH_SPEAR13XX
#घोषणा IRQ_GIC_END			160
#घोषणा NR_IRQS				IRQ_GIC_END
#पूर्ण_अगर

#पूर्ण_अगर /* __MACH_IRQS_H */
