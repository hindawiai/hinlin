<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2012 Freescale Semiconductor, Inc.
 */

#समावेश <linux/cpuidle.h>
#समावेश <linux/module.h>
#समावेश <यंत्र/cpuidle.h>

#समावेश <soc/imx/cpuidle.h>

#समावेश "common.h"
#समावेश "cpuidle.h"
#समावेश "hardware.h"

अटल पूर्णांक num_idle_cpus = 0;
अटल DEFINE_RAW_SPINLOCK(cpuidle_lock);

अटल पूर्णांक imx6q_enter_रुको(काष्ठा cpuidle_device *dev,
			    काष्ठा cpuidle_driver *drv, पूर्णांक index)
अणु
	raw_spin_lock(&cpuidle_lock);
	अगर (++num_idle_cpus == num_online_cpus())
		imx6_set_lpm(WAIT_UNCLOCKED);
	raw_spin_unlock(&cpuidle_lock);

	rcu_idle_enter();
	cpu_करो_idle();
	rcu_idle_निकास();

	raw_spin_lock(&cpuidle_lock);
	अगर (num_idle_cpus-- == num_online_cpus())
		imx6_set_lpm(WAIT_CLOCKED);
	raw_spin_unlock(&cpuidle_lock);

	वापस index;
पूर्ण

अटल काष्ठा cpuidle_driver imx6q_cpuidle_driver = अणु
	.name = "imx6q_cpuidle",
	.owner = THIS_MODULE,
	.states = अणु
		/* WFI */
		ARM_CPUIDLE_WFI_STATE,
		/* WAIT */
		अणु
			.निकास_latency = 50,
			.target_residency = 75,
			.flags = CPUIDLE_FLAG_TIMER_STOP | CPUIDLE_FLAG_RCU_IDLE,
			.enter = imx6q_enter_रुको,
			.name = "WAIT",
			.desc = "Clock off",
		पूर्ण,
	पूर्ण,
	.state_count = 2,
	.safe_state_index = 0,
पूर्ण;

/*
 * i.MX6 Q/DL has an erratum (ERR006687) that prevents the FEC from waking the
 * CPUs when they are in रुको(unघड़ीed) state. As the hardware workaround isn't
 * applicable to all boards, disable the deeper idle state when the workaround
 * isn't present and the FEC is in use.
 */
व्योम imx6q_cpuidle_fec_irqs_used(व्योम)
अणु
	cpuidle_driver_state_disabled(&imx6q_cpuidle_driver, 1, true);
पूर्ण
EXPORT_SYMBOL_GPL(imx6q_cpuidle_fec_irqs_used);

व्योम imx6q_cpuidle_fec_irqs_unused(व्योम)
अणु
	cpuidle_driver_state_disabled(&imx6q_cpuidle_driver, 1, false);
पूर्ण
EXPORT_SYMBOL_GPL(imx6q_cpuidle_fec_irqs_unused);

पूर्णांक __init imx6q_cpuidle_init(व्योम)
अणु
	/* Set INT_MEM_CLK_LPM bit to get a reliable WAIT mode support */
	imx6_set_पूर्णांक_mem_clk_lpm(true);

	वापस cpuidle_रेजिस्टर(&imx6q_cpuidle_driver, शून्य);
पूर्ण
