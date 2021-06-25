<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * r8a7778 processor support
 *
 * Copyright (C) 2013  Renesas Solutions Corp.
 * Copyright (C) 2013  Kuninori Morimoto <kuninori.morimoto.gx@renesas.com>
 * Copyright (C) 2013  Cogent Embedded, Inc.
 */

#समावेश <linux/पन.स>
#समावेश <linux/irqchip.h>

#समावेश <यंत्र/mach/arch.h>

#समावेश "common.h"

#घोषणा HPBREG_BASE	0xfe700000

#घोषणा INT2SMSKCR0	0x82288 /* 0xfe782288 */
#घोषणा INT2SMSKCR1	0x8228c /* 0xfe78228c */

#घोषणा INT2NTSR0	0x00018 /* 0xfe700018 */
#घोषणा INT2NTSR1	0x0002c /* 0xfe70002c */

अटल व्योम __init r8a7778_init_irq_dt(व्योम)
अणु
	व्योम __iomem *base = ioremap(HPBREG_BASE, 0x00100000);

	BUG_ON(!base);

	irqchip_init();

	/* route all पूर्णांकerrupts to ARM */
	ग_लिखोl(0x73ffffff, base + INT2NTSR0);
	ग_लिखोl(0xffffffff, base + INT2NTSR1);

	/* unmask all known पूर्णांकerrupts in INTCS2 */
	ग_लिखोl(0x08330773, base + INT2SMSKCR0);
	ग_लिखोl(0x00311110, base + INT2SMSKCR1);

	iounmap(base);
पूर्ण

अटल स्थिर अक्षर *स्थिर r8a7778_compat_dt[] __initस्थिर = अणु
	"renesas,r8a7778",
	शून्य,
पूर्ण;

DT_MACHINE_START(R8A7778_DT, "Generic R8A7778 (Flattened Device Tree)")
	.init_early	= shmobile_init_delay,
	.init_irq	= r8a7778_init_irq_dt,
	.init_late	= shmobile_init_late,
	.dt_compat	= r8a7778_compat_dt,
MACHINE_END
