<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2002  David McCullough <davidm@snapgear.com>
 * Copyright (C) 2003  Paul Mundt <lethal@linux-sh.org>
 *
 * Based on files with the following comments:
 *
 *           Copyright (C) 2000  Kazumoto Kojima
 *
 *           Modअगरied क्रम 7751 Solution Engine by
 *           Ian da Silva and Jeremy Siegel, 2001.
 */
#समावेश <linux/init.h>
#समावेश <linux/irq.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/समयr.h>
#समावेश <linux/delay.h>
#समावेश <linux/sched.h>
#समावेश <यंत्र/machvec.h>
#समावेश <mach/secureedge5410.h>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/पन.स>
#समावेश <cpu/समयr.h>

अचिन्हित लघु secureedge5410_ioport;

/*
 * EraseConfig handling functions
 */
अटल irqवापस_t eraseconfig_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	prपूर्णांकk("SnapGear: erase switch interrupt!\n");

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक __init eraseconfig_init(व्योम)
अणु
	अचिन्हित पूर्णांक irq = evt2irq(0x240);

	prपूर्णांकk("SnapGear: EraseConfig init\n");

	/* Setup "EraseConfig" चयन on बाह्यal IRQ 0 */
	अगर (request_irq(irq, eraseconfig_पूर्णांकerrupt, 0, "Erase Config", शून्य))
		prपूर्णांकk("SnapGear: failed to register IRQ%d for Reset witch\n",
				irq);
	अन्यथा
		prपूर्णांकk("SnapGear: registered EraseConfig switch on IRQ%d\n",
				irq);
	वापस 0;
पूर्ण
device_initcall(eraseconfig_init);

/*
 * Initialize IRQ setting
 *
 * IRL0 = erase चयन
 * IRL1 = eth0
 * IRL2 = eth1
 * IRL3 = crypto
 */
अटल व्योम __init init_snapgear_IRQ(व्योम)
अणु
	prपूर्णांकk("Setup SnapGear IRQ/IPR ...\n");
	/* enable inभागidual पूर्णांकerrupt mode क्रम बाह्यals */
	plat_irq_setup_pins(IRQ_MODE_IRQ);
पूर्ण

/*
 * The Machine Vector
 */
अटल काष्ठा sh_machine_vector mv_snapgear __iniपंचांगv = अणु
	.mv_name		= "SnapGear SecureEdge5410",
	.mv_init_irq		= init_snapgear_IRQ,
पूर्ण;
