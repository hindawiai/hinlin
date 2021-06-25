<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * linux/arch/sh/boards/se/7780/irq.c
 *
 * Copyright (C) 2006,2007  Nobuhiro Iwamatsu
 *
 * Hitachi UL SolutionEngine 7780 Support.
 */
#समावेश <linux/init.h>
#समावेश <linux/irq.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <mach-se/mach/se7780.h>

#घोषणा INTC_BASE	0xffd00000
#घोषणा INTC_ICR1	(INTC_BASE+0x1c)

/*
 * Initialize IRQ setting
 */
व्योम __init init_se7780_IRQ(व्योम)
अणु
	/* enable all पूर्णांकerrupt at FPGA */
	__raw_ग_लिखोw(0, FPGA_INTMSK1);
	/* mask SM501 पूर्णांकerrupt */
	__raw_ग_लिखोw((__raw_पढ़ोw(FPGA_INTMSK1) | 0x0002), FPGA_INTMSK1);
	/* enable all पूर्णांकerrupt at FPGA */
	__raw_ग_लिखोw(0, FPGA_INTMSK2);

	/* set FPGA INTSEL रेजिस्टर */
	/* FPGA + 0x06 */
	__raw_ग_लिखोw( ((IRQPIN_SM501 << IRQPOS_SM501) |
		(IRQPIN_SMC91CX << IRQPOS_SMC91CX)), FPGA_INTSEL1);

	/* FPGA + 0x08 */
	__raw_ग_लिखोw(((IRQPIN_EXTINT4 << IRQPOS_EXTINT4) |
		(IRQPIN_EXTINT3 << IRQPOS_EXTINT3) |
		(IRQPIN_EXTINT2 << IRQPOS_EXTINT2) |
		(IRQPIN_EXTINT1 << IRQPOS_EXTINT1)), FPGA_INTSEL2);

	/* FPGA + 0x0A */
	__raw_ग_लिखोw((IRQPIN_PCCPW << IRQPOS_PCCPW), FPGA_INTSEL3);

	plat_irq_setup_pins(IRQ_MODE_IRQ); /* install handlers क्रम IRQ0-7 */

	/* ICR1: detect low level(क्रम 2ndcut) */
	__raw_ग_लिखोl(0xAAAA0000, INTC_ICR1);

	/*
	 * FPGA PCISEL रेजिस्टर initialize
	 *
	 *  CPU  || SLOT1 | SLOT2 | S-ATA | USB
	 *  -------------------------------------
	 *  INTA || INTA  | INTD  |  --   | INTB
	 *  -------------------------------------
	 *  INTB || INTB  | INTA  |  --   | INTC
	 *  -------------------------------------
	 *  INTC || INTC  | INTB  | INTA  |  --
	 *  -------------------------------------
	 *  INTD || INTD  | INTC  |  --   | INTA
	 *  -------------------------------------
	 */
	__raw_ग_लिखोw(0x0013, FPGA_PCI_INTSEL1);
	__raw_ग_लिखोw(0xE402, FPGA_PCI_INTSEL2);
पूर्ण
