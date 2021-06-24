<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Power Management driver क्रम Marvell Kirkwood SoCs
 *
 * Copyright (C) 2013 Ezequiel Garcia <ezequiel@मुक्त-electrons.com>
 * Copyright (C) 2010 Simon Guinot <sguinot@lacie.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/suspend.h>
#समावेश <linux/पन.स>
#समावेश "kirkwood.h"
#समावेश "kirkwood-pm.h"

अटल व्योम __iomem *ddr_operation_base;
अटल व्योम __iomem *memory_pm_ctrl;

अटल व्योम kirkwood_low_घातer(व्योम)
अणु
	u32 mem_pm_ctrl;

	mem_pm_ctrl = पढ़ोl(memory_pm_ctrl);

	/* Set peripherals to low-घातer mode */
	ग_लिखोl_relaxed(~0, memory_pm_ctrl);

	/* Set DDR in self-refresh */
	ग_लिखोl_relaxed(0x7, ddr_operation_base);

	/*
	 * Set CPU in रुको-क्रम-पूर्णांकerrupt state.
	 * This disables the CPU core घड़ीs,
	 * the array घड़ीs, and also the L2 controller.
	 */
	cpu_करो_idle();

	ग_लिखोl_relaxed(mem_pm_ctrl, memory_pm_ctrl);
पूर्ण

अटल पूर्णांक kirkwood_suspend_enter(suspend_state_t state)
अणु
	चयन (state) अणु
	हाल PM_SUSPEND_STANDBY:
		kirkwood_low_घातer();
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक kirkwood_pm_valid_standby(suspend_state_t state)
अणु
	वापस state == PM_SUSPEND_STANDBY;
पूर्ण

अटल स्थिर काष्ठा platक्रमm_suspend_ops kirkwood_suspend_ops = अणु
	.enter = kirkwood_suspend_enter,
	.valid = kirkwood_pm_valid_standby,
पूर्ण;

व्योम __init kirkwood_pm_init(व्योम)
अणु
	ddr_operation_base = ioremap(DDR_OPERATION_BASE, 4);
	memory_pm_ctrl = ioremap(MEMORY_PM_CTRL_PHYS, 4);

	suspend_set_ops(&kirkwood_suspend_ops);
पूर्ण
