<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2011-12 Synopsys, Inc. (www.synopsys.com)
 */

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irqchip.h>
#समावेश <यंत्र/mach_desc.h>
#समावेश <यंत्र/smp.h>

/*
 * Late Interrupt प्रणाली init called from start_kernel क्रम Boot CPU only
 *
 * Since slab must alपढ़ोy be initialized, platक्रमms can start करोing any
 * needed request_irq( )s
 */
व्योम __init init_IRQ(व्योम)
अणु
	/*
	 * process the entire पूर्णांकerrupt tree in one go
	 * Any बाह्यal पूर्णांकc will be setup provided DT chains them
	 * properly
	 */
	irqchip_init();

#अगर_घोषित CONFIG_SMP
	/* a SMP H/w block could करो IPI IRQ request here */
	अगर (plat_smp_ops.init_per_cpu)
		plat_smp_ops.init_per_cpu(smp_processor_id());
#पूर्ण_अगर

	अगर (machine_desc->init_per_cpu)
		machine_desc->init_per_cpu(smp_processor_id());
पूर्ण

/*
 * "C" Entry poपूर्णांक क्रम any ARC ISR, called from low level vector handler
 * @irq is the vector number पढ़ो from ICAUSE reg of on-chip पूर्णांकc
 */
व्योम arch_करो_IRQ(अचिन्हित पूर्णांक hwirq, काष्ठा pt_regs *regs)
अणु
	handle_करोमुख्य_irq(शून्य, hwirq, regs);
पूर्ण
