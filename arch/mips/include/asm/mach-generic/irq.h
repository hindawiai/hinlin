<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2003 by Ralf Baechle
 */
#अगर_अघोषित __ASM_MACH_GENERIC_IRQ_H
#घोषणा __ASM_MACH_GENERIC_IRQ_H

#अगर_अघोषित NR_IRQS
#घोषणा NR_IRQS 256
#पूर्ण_अगर

#अगर_घोषित CONFIG_I8259
#अगर_अघोषित I8259A_IRQ_BASE
#घोषणा I8259A_IRQ_BASE 0
#पूर्ण_अगर
#पूर्ण_अगर

#अगर_घोषित CONFIG_IRQ_MIPS_CPU

#अगर_अघोषित MIPS_CPU_IRQ_BASE
#अगर_घोषित CONFIG_I8259
#घोषणा MIPS_CPU_IRQ_BASE 16
#अन्यथा
#घोषणा MIPS_CPU_IRQ_BASE 0
#पूर्ण_अगर /* CONFIG_I8259 */
#पूर्ण_अगर

#पूर्ण_अगर /* CONFIG_IRQ_MIPS_CPU */

#पूर्ण_अगर /* __ASM_MACH_GENERIC_IRQ_H */
