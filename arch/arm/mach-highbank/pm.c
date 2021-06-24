<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright 2011 Calxeda, Inc.
 */

#समावेश <linux/cpu_pm.h>
#समावेश <linux/init.h>
#समावेश <linux/psci.h>
#समावेश <linux/suspend.h>

#समावेश <यंत्र/suspend.h>

#समावेश <uapi/linux/psci.h>

#घोषणा HIGHBANK_SUSPEND_PARAM \
	((0 << PSCI_0_2_POWER_STATE_ID_SHIFT) | \
	 (1 << PSCI_0_2_POWER_STATE_AFFL_SHIFT) | \
	 (PSCI_POWER_STATE_TYPE_POWER_DOWN << PSCI_0_2_POWER_STATE_TYPE_SHIFT))

अटल पूर्णांक highbank_suspend_finish(अचिन्हित दीर्घ val)
अणु
	वापस psci_ops.cpu_suspend(HIGHBANK_SUSPEND_PARAM, __pa(cpu_resume));
पूर्ण

अटल पूर्णांक highbank_pm_enter(suspend_state_t state)
अणु
	cpu_pm_enter();
	cpu_cluster_pm_enter();

	cpu_suspend(0, highbank_suspend_finish);

	cpu_cluster_pm_निकास();
	cpu_pm_निकास();

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा platक्रमm_suspend_ops highbank_pm_ops = अणु
	.enter = highbank_pm_enter,
	.valid = suspend_valid_only_mem,
पूर्ण;

व्योम __init highbank_pm_init(व्योम)
अणु
	अगर (!psci_ops.cpu_suspend)
		वापस;

	suspend_set_ops(&highbank_pm_ops);
पूर्ण
