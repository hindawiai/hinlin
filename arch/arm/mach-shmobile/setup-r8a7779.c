<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * r8a7779 processor support
 *
 * Copyright (C) 2011, 2013  Renesas Solutions Corp.
 * Copyright (C) 2011  Magnus Damm
 * Copyright (C) 2013  Cogent Embedded, Inc.
 */
#समावेश <linux/init.h>
#समावेश <linux/irqchip.h>

#समावेश <यंत्र/mach/arch.h>
#समावेश <यंत्र/mach/map.h>

#समावेश "common.h"
#समावेश "r8a7779.h"

#घोषणा HPBREG_BASE	0xfe700000

/* IRQ */
#घोषणा INT2SMSKCR0	0x822a0	/* Interrupt Submask Clear Register 0 */
#घोषणा INT2SMSKCR1	0x822a4	/* Interrupt Submask Clear Register 1 */
#घोषणा INT2SMSKCR2	0x822a8	/* Interrupt Submask Clear Register 2 */
#घोषणा INT2SMSKCR3	0x822ac	/* Interrupt Submask Clear Register 3 */
#घोषणा INT2SMSKCR4	0x822b0	/* Interrupt Submask Clear Register 4 */

#घोषणा INT2NTSR0	0x00060	/* Interrupt Notअगरication Select Register 0 */
#घोषणा INT2NTSR1	0x00064	/* Interrupt Notअगरication Select Register 1 */

अटल व्योम __init r8a7779_init_irq_dt(व्योम)
अणु
	व्योम __iomem *base = ioremap(HPBREG_BASE, 0x00100000);

	irqchip_init();

	/* route all पूर्णांकerrupts to ARM */
	ग_लिखोl(0xffffffff, base + INT2NTSR0);
	ग_लिखोl(0x3fffffff, base + INT2NTSR1);

	/* unmask all known पूर्णांकerrupts in INTCS2 */
	ग_लिखोl(0xfffffff0, base + INT2SMSKCR0);
	ग_लिखोl(0xfff7ffff, base + INT2SMSKCR1);
	ग_लिखोl(0xfffbffdf, base + INT2SMSKCR2);
	ग_लिखोl(0xbffffffc, base + INT2SMSKCR3);
	ग_लिखोl(0x003fee3f, base + INT2SMSKCR4);

	iounmap(base);
पूर्ण

अटल स्थिर अक्षर *स्थिर r8a7779_compat_dt[] __initस्थिर = अणु
	"renesas,r8a7779",
	शून्य,
पूर्ण;

DT_MACHINE_START(R8A7779_DT, "Generic R8A7779 (Flattened Device Tree)")
	.smp		= smp_ops(r8a7779_smp_ops),
	.init_irq	= r8a7779_init_irq_dt,
	.init_late	= shmobile_init_late,
	.dt_compat	= r8a7779_compat_dt,
MACHINE_END
