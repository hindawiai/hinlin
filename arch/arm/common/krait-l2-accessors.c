<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (c) 2018, The Linux Foundation. All rights reserved.

#समावेश <linux/spinlock.h>
#समावेश <linux/export.h>

#समावेश <यंत्र/barrier.h>
#समावेश <यंत्र/krait-l2-accessors.h>

अटल DEFINE_RAW_SPINLOCK(krait_l2_lock);

व्योम krait_set_l2_indirect_reg(u32 addr, u32 val)
अणु
	अचिन्हित दीर्घ flags;

	raw_spin_lock_irqsave(&krait_l2_lock, flags);
	/*
	 * Select the L2 winकरोw by poking l2cpselr, then ग_लिखो to the winकरोw
	 * via l2cpdr.
	 */
	यंत्र अस्थिर ("mcr p15, 3, %0, c15, c0, 6 @ l2cpselr" : : "r" (addr));
	isb();
	यंत्र अस्थिर ("mcr p15, 3, %0, c15, c0, 7 @ l2cpdr" : : "r" (val));
	isb();

	raw_spin_unlock_irqrestore(&krait_l2_lock, flags);
पूर्ण
EXPORT_SYMBOL(krait_set_l2_indirect_reg);

u32 krait_get_l2_indirect_reg(u32 addr)
अणु
	u32 val;
	अचिन्हित दीर्घ flags;

	raw_spin_lock_irqsave(&krait_l2_lock, flags);
	/*
	 * Select the L2 winकरोw by poking l2cpselr, then पढ़ो from the winकरोw
	 * via l2cpdr.
	 */
	यंत्र अस्थिर ("mcr p15, 3, %0, c15, c0, 6 @ l2cpselr" : : "r" (addr));
	isb();
	यंत्र अस्थिर ("mrc p15, 3, %0, c15, c0, 7 @ l2cpdr" : "=r" (val));

	raw_spin_unlock_irqrestore(&krait_l2_lock, flags);

	वापस val;
पूर्ण
EXPORT_SYMBOL(krait_get_l2_indirect_reg);
