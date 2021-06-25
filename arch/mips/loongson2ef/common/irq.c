<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2007 Lemote Inc. & Institute of Computing Technology
 * Author: Fuxin Zhang, zhangfx@lemote.com
 */
#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>

#समावेश <loongson.h>
/*
 * the first level पूर्णांक-handler will jump here अगर it is a bonito irq
 */
व्योम bonito_irqdispatch(व्योम)
अणु
	u32 पूर्णांक_status;
	पूर्णांक i;

	/* workaround the IO dma problem: let cpu looping to allow DMA finish */
	पूर्णांक_status = LOONGSON_INTISR;
	जबतक (पूर्णांक_status & (1 << 10)) अणु
		udelay(1);
		पूर्णांक_status = LOONGSON_INTISR;
	पूर्ण

	/* Get pending sources, masked by current enables */
	पूर्णांक_status = LOONGSON_INTISR & LOONGSON_INTEN;

	अगर (पूर्णांक_status) अणु
		i = __ffs(पूर्णांक_status);
		करो_IRQ(LOONGSON_IRQ_BASE + i);
	पूर्ण
पूर्ण

यंत्रlinkage व्योम plat_irq_dispatch(व्योम)
अणु
	अचिन्हित पूर्णांक pending;

	pending = पढ़ो_c0_cause() & पढ़ो_c0_status() & ST0_IM;

	/* machine-specअगरic plat_irq_dispatch */
	mach_irq_dispatch(pending);
पूर्ण

व्योम __init arch_init_irq(व्योम)
अणु
	/*
	 * Clear all of the पूर्णांकerrupts जबतक we change the able around a bit.
	 * पूर्णांक-handler is not on bootstrap
	 */
	clear_c0_status(ST0_IM | ST0_BEV);

	/* no steer */
	LOONGSON_INTSTEER = 0;

	/*
	 * Mask out all पूर्णांकerrupt by writing "1" to all bit position in
	 * the पूर्णांकerrupt reset reg.
	 */
	LOONGSON_INTENCLR = ~0;

	/* machine specअगरic irq init */
	mach_init_irq();
पूर्ण
