<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2018, The Linux Foundation. All rights reserved.
 */

#समावेश <linux/spinlock.h>
#समावेश <यंत्र/barrier.h>
#समावेश <यंत्र/sysreg.h>
#समावेश <soc/qcom/kryo-l2-accessors.h>

#घोषणा L2CPUSRSELR_EL1         sys_reg(3, 3, 15, 0, 6)
#घोषणा L2CPUSRDR_EL1           sys_reg(3, 3, 15, 0, 7)

अटल DEFINE_RAW_SPINLOCK(l2_access_lock);

/**
 * kryo_l2_set_indirect_reg() - ग_लिखो value to an L2 रेजिस्टर
 * @reg: Address of L2 रेजिस्टर.
 * @val: Value to be written to रेजिस्टर.
 *
 * Use architecturally required barriers क्रम ordering between प्रणाली रेजिस्टर
 * accesses, and प्रणाली रेजिस्टरs with respect to device memory
 */
व्योम kryo_l2_set_indirect_reg(u64 reg, u64 val)
अणु
	अचिन्हित दीर्घ flags;

	raw_spin_lock_irqsave(&l2_access_lock, flags);
	ग_लिखो_sysreg_s(reg, L2CPUSRSELR_EL1);
	isb();
	ग_लिखो_sysreg_s(val, L2CPUSRDR_EL1);
	isb();
	raw_spin_unlock_irqrestore(&l2_access_lock, flags);
पूर्ण
EXPORT_SYMBOL(kryo_l2_set_indirect_reg);

/**
 * kryo_l2_get_indirect_reg() - पढ़ो an L2 रेजिस्टर value
 * @reg: Address of L2 रेजिस्टर.
 *
 * Use architecturally required barriers क्रम ordering between प्रणाली रेजिस्टर
 * accesses, and प्रणाली रेजिस्टरs with respect to device memory
 */
u64 kryo_l2_get_indirect_reg(u64 reg)
अणु
	u64 val;
	अचिन्हित दीर्घ flags;

	raw_spin_lock_irqsave(&l2_access_lock, flags);
	ग_लिखो_sysreg_s(reg, L2CPUSRSELR_EL1);
	isb();
	val = पढ़ो_sysreg_s(L2CPUSRDR_EL1);
	raw_spin_unlock_irqrestore(&l2_access_lock, flags);

	वापस val;
पूर्ण
EXPORT_SYMBOL(kryo_l2_get_indirect_reg);
