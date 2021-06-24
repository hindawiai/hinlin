<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2014 Freescale Semiconductor, Inc.
 */

#समावेश <linux/cpuidle.h>
#समावेश <linux/cpu_pm.h>
#समावेश <linux/module.h>
#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/cpuidle.h>
#समावेश <यंत्र/suspend.h>

#समावेश "common.h"
#समावेश "cpuidle.h"
#समावेश "hardware.h"

अटल पूर्णांक imx6sx_idle_finish(अचिन्हित दीर्घ val)
अणु
	/*
	 * क्रम Cortex-A7 which has an पूर्णांकernal L2
	 * cache, need to flush it beक्रमe घातering
	 * करोwn ARM platक्रमm, since flushing L1 cache
	 * here again has very small overhead, compared
	 * to adding conditional code क्रम L2 cache type,
	 * just call flush_cache_all() is fine.
	 */
	flush_cache_all();
	cpu_करो_idle();

	वापस 0;
पूर्ण

अटल पूर्णांक imx6sx_enter_रुको(काष्ठा cpuidle_device *dev,
			    काष्ठा cpuidle_driver *drv, पूर्णांक index)
अणु
	imx6_set_lpm(WAIT_UNCLOCKED);

	चयन (index) अणु
	हाल 1:
		cpu_करो_idle();
		अवरोध;
	हाल 2:
		imx6_enable_rbc(true);
		imx_gpc_set_arm_घातer_in_lpm(true);
		imx_set_cpu_jump(0, v7_cpu_resume);
		/* Need to notअगरy there is a cpu pm operation. */
		cpu_pm_enter();
		cpu_cluster_pm_enter();

		cpu_suspend(0, imx6sx_idle_finish);

		cpu_cluster_pm_निकास();
		cpu_pm_निकास();
		imx_gpc_set_arm_घातer_in_lpm(false);
		imx6_enable_rbc(false);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	imx6_set_lpm(WAIT_CLOCKED);

	वापस index;
पूर्ण

अटल काष्ठा cpuidle_driver imx6sx_cpuidle_driver = अणु
	.name = "imx6sx_cpuidle",
	.owner = THIS_MODULE,
	.states = अणु
		/* WFI */
		ARM_CPUIDLE_WFI_STATE,
		/* WAIT */
		अणु
			.निकास_latency = 50,
			.target_residency = 75,
			.flags = CPUIDLE_FLAG_TIMER_STOP,
			.enter = imx6sx_enter_रुको,
			.name = "WAIT",
			.desc = "Clock off",
		पूर्ण,
		/* WAIT + ARM घातer off  */
		अणु
			/*
			 * ARM gating 31us * 5 + RBC clear 65us
			 * and some margin क्रम SW execution, here set it
			 * to 300us.
			 */
			.निकास_latency = 300,
			.target_residency = 500,
			.flags = CPUIDLE_FLAG_TIMER_STOP,
			.enter = imx6sx_enter_रुको,
			.name = "LOW-POWER-IDLE",
			.desc = "ARM power off",
		पूर्ण,
	पूर्ण,
	.state_count = 3,
	.safe_state_index = 0,
पूर्ण;

पूर्णांक __init imx6sx_cpuidle_init(व्योम)
अणु
	imx6_set_पूर्णांक_mem_clk_lpm(true);
	imx6_enable_rbc(false);
	imx_gpc_set_l2_mem_घातer_in_lpm(false);
	/*
	 * set ARM घातer up/करोwn timing to the fastest,
	 * sw2iso and sw can be set to one 32K cycle = 31us
	 * except क्रम घातer up sw2iso which need to be
	 * larger than LDO ramp up समय.
	 */
	imx_gpc_set_arm_घातer_up_timing(cpu_is_imx6sx() ? 0xf : 0x2, 1);
	imx_gpc_set_arm_घातer_करोwn_timing(1, 1);

	वापस cpuidle_रेजिस्टर(&imx6sx_cpuidle_driver, शून्य);
पूर्ण
