<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright 2012 Calxeda, Inc.
 *
 * Based on arch/arm/plat-mxc/cpuidle.c: #v3.7
 * Copyright 2012 Freescale Semiconductor, Inc.
 * Copyright 2012 Linaro Ltd.
 *
 * Maपूर्णांकainer: Rob Herring <rob.herring@calxeda.com>
 */

#समावेश <linux/cpuidle.h>
#समावेश <linux/cpu_pm.h>
#समावेश <linux/init.h>
#समावेश <linux/mm.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/psci.h>

#समावेश <यंत्र/cpuidle.h>
#समावेश <यंत्र/suspend.h>

#समावेश <uapi/linux/psci.h>

#घोषणा CALXEDA_IDLE_PARAM \
	((0 << PSCI_0_2_POWER_STATE_ID_SHIFT) | \
	 (0 << PSCI_0_2_POWER_STATE_AFFL_SHIFT) | \
	 (PSCI_POWER_STATE_TYPE_POWER_DOWN << PSCI_0_2_POWER_STATE_TYPE_SHIFT))

अटल पूर्णांक calxeda_idle_finish(अचिन्हित दीर्घ val)
अणु
	वापस psci_ops.cpu_suspend(CALXEDA_IDLE_PARAM, __pa(cpu_resume));
पूर्ण

अटल पूर्णांक calxeda_pwrकरोwn_idle(काष्ठा cpuidle_device *dev,
				काष्ठा cpuidle_driver *drv,
				पूर्णांक index)
अणु
	cpu_pm_enter();
	cpu_suspend(0, calxeda_idle_finish);
	cpu_pm_निकास();

	वापस index;
पूर्ण

अटल काष्ठा cpuidle_driver calxeda_idle_driver = अणु
	.name = "calxeda_idle",
	.states = अणु
		ARM_CPUIDLE_WFI_STATE,
		अणु
			.name = "PG",
			.desc = "Power Gate",
			.निकास_latency = 30,
			.घातer_usage = 50,
			.target_residency = 200,
			.enter = calxeda_pwrकरोwn_idle,
		पूर्ण,
	पूर्ण,
	.state_count = 2,
पूर्ण;

अटल पूर्णांक calxeda_cpuidle_probe(काष्ठा platक्रमm_device *pdev)
अणु
	वापस cpuidle_रेजिस्टर(&calxeda_idle_driver, शून्य);
पूर्ण

अटल काष्ठा platक्रमm_driver calxeda_cpuidle_plat_driver = अणु
        .driver = अणु
                .name = "cpuidle-calxeda",
        पूर्ण,
        .probe = calxeda_cpuidle_probe,
पूर्ण;
builtin_platक्रमm_driver(calxeda_cpuidle_plat_driver);
