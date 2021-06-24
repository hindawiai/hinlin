<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (C) 2018 Hangzhou C-SKY Microप्रणालीs co.,ltd.

#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/irqchip.h>
#समावेश <यंत्र/traps.h>
#समावेश <यंत्र/smp.h>

व्योम __init init_IRQ(व्योम)
अणु
	irqchip_init();
#अगर_घोषित CONFIG_SMP
	setup_smp_ipi();
#पूर्ण_अगर
पूर्ण

यंत्रlinkage व्योम __irq_entry csky_करो_IRQ(काष्ठा pt_regs *regs)
अणु
	handle_arch_irq(regs);
पूर्ण
