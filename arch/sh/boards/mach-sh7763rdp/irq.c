<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * linux/arch/sh/boards/renesas/sh7763rdp/irq.c
 *
 * Renesas Solutions SH7763RDP Support.
 *
 * Copyright (C) 2008 Renesas Solutions Corp.
 * Copyright (C) 2008  Nobuhiro Iwamatsu <iwamatsu.nobuhiro@renesas.com>
 */

#समावेश <linux/init.h>
#समावेश <linux/irq.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/irq.h>
#समावेश <mach/sh7763rdp.h>

#घोषणा INTC_BASE		(0xFFD00000)
#घोषणा INTC_INT2PRI7   (INTC_BASE+0x4001C)
#घोषणा INTC_INT2MSKCR	(INTC_BASE+0x4003C)
#घोषणा INTC_INT2MSKCR1	(INTC_BASE+0x400D4)

/*
 * Initialize IRQ setting
 */
व्योम __init init_sh7763rdp_IRQ(व्योम)
अणु
	/* GPIO enabled */
	__raw_ग_लिखोl(1 << 25, INTC_INT2MSKCR);

	/* enable GPIO पूर्णांकerrupts */
	__raw_ग_लिखोl((__raw_पढ़ोl(INTC_INT2PRI7) & 0xFF00FFFF) | 0x000F0000,
		  INTC_INT2PRI7);

	/* USBH enabled */
	__raw_ग_लिखोl(1 << 17, INTC_INT2MSKCR1);

	/* GETHER enabled */
	__raw_ग_लिखोl(1 << 16, INTC_INT2MSKCR1);

	/* DMAC enabled */
	__raw_ग_लिखोl(1 << 8, INTC_INT2MSKCR);
पूर्ण
