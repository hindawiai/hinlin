<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Pistachio IRQ setup
 *
 * Copyright (C) 2014 Google, Inc.
 */

#समावेश <linux/init.h>
#समावेश <linux/irqchip.h>
#समावेश <linux/kernel.h>

#समावेश <यंत्र/cpu-features.h>
#समावेश <यंत्र/irq_cpu.h>

व्योम __init arch_init_irq(व्योम)
अणु
	pr_info("EIC is %s\n", cpu_has_veic ? "on" : "off");
	pr_info("VINT is %s\n", cpu_has_vपूर्णांक ? "on" : "off");

	अगर (!cpu_has_veic)
		mips_cpu_irq_init();

	irqchip_init();
पूर्ण
