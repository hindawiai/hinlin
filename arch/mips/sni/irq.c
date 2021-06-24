<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 1992 Linus Torvalds
 * Copyright (C) 1994 - 2000 Ralf Baechle
 * Copyright (C) 2006 Thomas Bogenकरोerfer
 */
#समावेश <linux/delay.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/kernel.h>

#समावेश <यंत्र/i8259.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/sni.h>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/irq_cpu.h>

व्योम (*sni_hwपूर्णांक)(व्योम);

यंत्रlinkage व्योम plat_irq_dispatch(व्योम)
अणु
	sni_hwपूर्णांक();
पूर्ण

/* ISA irq handler */
irqवापस_t sni_isa_irq_handler(पूर्णांक dummy, व्योम *p)
अणु
	पूर्णांक irq;

	irq = i8259_irq();
	अगर (unlikely(irq < 0))
		वापस IRQ_NONE;

	generic_handle_irq(irq);
	वापस IRQ_HANDLED;
पूर्ण

/*
 * On प्रणालीs with i8259-style पूर्णांकerrupt controllers we assume क्रम
 * driver compatibility reasons पूर्णांकerrupts 0 - 15 to be the i8295
 * पूर्णांकerrupts even अगर the hardware uses a dअगरferent पूर्णांकerrupt numbering.
 */
व्योम __init arch_init_irq(व्योम)
अणु
	init_i8259_irqs();			/* Integrated i8259  */
	चयन (sni_brd_type) अणु
	हाल SNI_BRD_10:
	हाल SNI_BRD_10NEW:
	हाल SNI_BRD_TOWER_OASIC:
	हाल SNI_BRD_MINITOWER:
		sni_a20r_irq_init();
		अवरोध;

	हाल SNI_BRD_PCI_TOWER:
		sni_pcit_irq_init();
		अवरोध;

	हाल SNI_BRD_PCI_TOWER_CPLUS:
		sni_pcit_cplus_irq_init();
		अवरोध;

	हाल SNI_BRD_RM200:
		sni_rm200_irq_init();
		अवरोध;

	हाल SNI_BRD_PCI_MTOWER:
	हाल SNI_BRD_PCI_DESKTOP:
	हाल SNI_BRD_PCI_MTOWER_CPLUS:
		sni_pcimt_irq_init();
		अवरोध;
	पूर्ण
पूर्ण
