<शैली गुरु>
/*
 * include/यंत्र-mips/txx9irq.h
 * TX39/TX49 पूर्णांकerrupt controller definitions.
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 */
#अगर_अघोषित __ASM_TXX9IRQ_H
#घोषणा __ASM_TXX9IRQ_H

#समावेश <irq.h>

#अगर_घोषित CONFIG_IRQ_MIPS_CPU
#घोषणा TXX9_IRQ_BASE	(MIPS_CPU_IRQ_BASE + 8)
#अन्यथा
#अगर_घोषित CONFIG_I8259
#घोषणा TXX9_IRQ_BASE	(I8259A_IRQ_BASE + 16)
#अन्यथा
#घोषणा TXX9_IRQ_BASE	0
#पूर्ण_अगर
#पूर्ण_अगर

#अगर_घोषित CONFIG_CPU_TX39XX
#घोषणा TXx9_MAX_IR 16
#अन्यथा
#घोषणा TXx9_MAX_IR 32
#पूर्ण_अगर

व्योम txx9_irq_init(अचिन्हित दीर्घ baseaddr);
पूर्णांक txx9_irq(व्योम);
पूर्णांक txx9_irq_set_pri(पूर्णांक irc_irq, पूर्णांक new_pri);

#पूर्ण_अगर /* __ASM_TXX9IRQ_H */
