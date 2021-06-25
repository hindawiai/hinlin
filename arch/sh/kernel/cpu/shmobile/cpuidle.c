<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * arch/sh/kernel/cpu/shmobile/cpuidle.c
 *
 * Cpuidle support code क्रम SuperH Mobile
 *
 *  Copyright (C) 2009 Magnus Damm
 */
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/पन.स>
#समावेश <linux/suspend.h>
#समावेश <linux/cpuidle.h>
#समावेश <linux/export.h>
#समावेश <यंत्र/suspend.h>
#समावेश <linux/uaccess.h>

अटल अचिन्हित दीर्घ cpuidle_mode[] = अणु
	SUSP_SH_SLEEP, /* regular sleep mode */
	SUSP_SH_SLEEP | SUSP_SH_SF, /* sleep mode + self refresh */
	SUSP_SH_STANDBY | SUSP_SH_SF, /* software standby mode + self refresh */
पूर्ण;

अटल पूर्णांक cpuidle_sleep_enter(काष्ठा cpuidle_device *dev,
				काष्ठा cpuidle_driver *drv,
				पूर्णांक index)
अणु
	अचिन्हित दीर्घ allowed_mode = SUSP_SH_SLEEP;
	पूर्णांक requested_state = index;
	पूर्णांक allowed_state;
	पूर्णांक k;

	/* convert allowed mode to allowed state */
	क्रम (k = ARRAY_SIZE(cpuidle_mode) - 1; k > 0; k--)
		अगर (cpuidle_mode[k] == allowed_mode)
			अवरोध;

	allowed_state = k;

	/* take the following पूर्णांकo account क्रम sleep mode selection:
	 * - allowed_state: best mode allowed by hardware (घड़ी deps)
	 * - requested_state: best mode allowed by software (latencies)
	 */
	k = min_t(पूर्णांक, allowed_state, requested_state);

	sh_mobile_call_standby(cpuidle_mode[k]);

	वापस k;
पूर्ण

अटल काष्ठा cpuidle_driver cpuidle_driver = अणु
	.name   = "sh_idle",
	.owner  = THIS_MODULE,
	.states = अणु
		अणु
			.निकास_latency = 1,
			.target_residency = 1 * 2,
			.घातer_usage = 3,
			.enter = cpuidle_sleep_enter,
			.name = "C1",
			.desc = "SuperH Sleep Mode",
		पूर्ण,
		अणु
			.निकास_latency = 100,
			.target_residency = 1 * 2,
			.घातer_usage = 1,
			.enter = cpuidle_sleep_enter,
			.name = "C2",
			.desc = "SuperH Sleep Mode [SF]",
			.flags = CPUIDLE_FLAG_UNUSABLE,
		पूर्ण,
		अणु
			.निकास_latency = 2300,
			.target_residency = 1 * 2,
			.घातer_usage = 1,
			.enter = cpuidle_sleep_enter,
			.name = "C3",
			.desc = "SuperH Mobile Standby Mode [SF]",
			.flags = CPUIDLE_FLAG_UNUSABLE,
		पूर्ण,
	पूर्ण,
	.safe_state_index = 0,
	.state_count = 3,
पूर्ण;

पूर्णांक __init sh_mobile_setup_cpuidle(व्योम)
अणु
	अगर (sh_mobile_sleep_supported & SUSP_SH_SF)
		cpuidle_driver.states[1].flags = CPUIDLE_FLAG_NONE;

	अगर (sh_mobile_sleep_supported & SUSP_SH_STANDBY)
		cpuidle_driver.states[2].flags = CPUIDLE_FLAG_NONE;

	वापस cpuidle_रेजिस्टर(&cpuidle_driver, शून्य);
पूर्ण
