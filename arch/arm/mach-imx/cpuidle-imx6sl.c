<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2014 Freescale Semiconductor, Inc.
 */

#समावेश <linux/clk/imx.h>
#समावेश <linux/cpuidle.h>
#समावेश <linux/module.h>
#समावेश <यंत्र/cpuidle.h>

#समावेश "common.h"
#समावेश "cpuidle.h"

अटल पूर्णांक imx6sl_enter_रुको(काष्ठा cpuidle_device *dev,
			    काष्ठा cpuidle_driver *drv, पूर्णांक index)
अणु
	imx6_set_lpm(WAIT_UNCLOCKED);
	/*
	 * Software workaround क्रम ERR005311, see function
	 * description क्रम details.
	 */
	imx6sl_set_रुको_clk(true);
	cpu_करो_idle();
	imx6sl_set_रुको_clk(false);
	imx6_set_lpm(WAIT_CLOCKED);

	वापस index;
पूर्ण

अटल काष्ठा cpuidle_driver imx6sl_cpuidle_driver = अणु
	.name = "imx6sl_cpuidle",
	.owner = THIS_MODULE,
	.states = अणु
		/* WFI */
		ARM_CPUIDLE_WFI_STATE,
		/* WAIT */
		अणु
			.निकास_latency = 50,
			.target_residency = 75,
			.flags = CPUIDLE_FLAG_TIMER_STOP,
			.enter = imx6sl_enter_रुको,
			.name = "WAIT",
			.desc = "Clock off",
		पूर्ण,
	पूर्ण,
	.state_count = 2,
	.safe_state_index = 0,
पूर्ण;

पूर्णांक __init imx6sl_cpuidle_init(व्योम)
अणु
	वापस cpuidle_रेजिस्टर(&imx6sl_cpuidle_driver, शून्य);
पूर्ण
