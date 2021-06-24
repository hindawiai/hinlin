<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *
 * Copyright (C) 2014 Broadcom Corporation
 * Author: Kevin Cernekee <cernekee@gmail.com>
 */

#समावेश <linux/of.h>
#समावेश <linux/irqchip.h>

#समावेश <यंत्र/bmips.h>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/irq_cpu.h>
#समावेश <यंत्र/समय.स>

अटल स्थिर काष्ठा of_device_id smp_पूर्णांकc_dt_match[] = अणु
	अणु .compatible = "brcm,bcm7038-l1-intc" पूर्ण,
	अणु .compatible = "brcm,bcm6345-l1-intc" पूर्ण,
	अणुपूर्ण
पूर्ण;

अचिन्हित पूर्णांक get_c0_compare_पूर्णांक(व्योम)
अणु
	वापस CP0_LEGACY_COMPARE_IRQ;
पूर्ण

व्योम __init arch_init_irq(व्योम)
अणु
	काष्ठा device_node *dn;

	/* Only these controllers support SMP IRQ affinity */
	dn = of_find_matching_node(शून्य, smp_पूर्णांकc_dt_match);
	अगर (dn)
		of_node_put(dn);
	अन्यथा
		bmips_tp1_irqs = 0;

	irqchip_init();
पूर्ण

IRQCHIP_DECLARE(mips_cpu_पूर्णांकc, "mti,cpu-interrupt-controller",
	     mips_cpu_irq_of_init);
