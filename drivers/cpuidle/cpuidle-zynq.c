<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2012-2013 Xilinx
 *
 * CPU idle support क्रम Xilinx Zynq
 *
 * based on arch/arm/mach-at91/cpuidle.c
 *
 * The cpu idle uses रुको-क्रम-पूर्णांकerrupt and RAM self refresh in order
 * to implement two idle states -
 * #1 रुको-क्रम-पूर्णांकerrupt
 * #2 रुको-क्रम-पूर्णांकerrupt and RAM self refresh
 *
 * Maपूर्णांकainer: Michal Simek <michal.simek@xilinx.com>
 */

#समावेश <linux/init.h>
#समावेश <linux/cpuidle.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <यंत्र/cpuidle.h>

#घोषणा ZYNQ_MAX_STATES		2

/* Actual code that माला_दो the SoC in dअगरferent idle states */
अटल पूर्णांक zynq_enter_idle(काष्ठा cpuidle_device *dev,
			   काष्ठा cpuidle_driver *drv, पूर्णांक index)
अणु
	/* Add code क्रम DDR self refresh start */
	cpu_करो_idle();

	वापस index;
पूर्ण

अटल काष्ठा cpuidle_driver zynq_idle_driver = अणु
	.name = "zynq_idle",
	.owner = THIS_MODULE,
	.states = अणु
		ARM_CPUIDLE_WFI_STATE,
		अणु
			.enter			= zynq_enter_idle,
			.निकास_latency		= 10,
			.target_residency	= 10000,
			.name			= "RAM_SR",
			.desc			= "WFI and RAM Self Refresh",
		पूर्ण,
	पूर्ण,
	.safe_state_index = 0,
	.state_count = ZYNQ_MAX_STATES,
पूर्ण;

/* Initialize CPU idle by रेजिस्टरing the idle states */
अटल पूर्णांक zynq_cpuidle_probe(काष्ठा platक्रमm_device *pdev)
अणु
	pr_info("Xilinx Zynq CpuIdle Driver started\n");

	वापस cpuidle_रेजिस्टर(&zynq_idle_driver, शून्य);
पूर्ण

अटल काष्ठा platक्रमm_driver zynq_cpuidle_driver = अणु
	.driver = अणु
		.name = "cpuidle-zynq",
	पूर्ण,
	.probe = zynq_cpuidle_probe,
पूर्ण;
builtin_platक्रमm_driver(zynq_cpuidle_driver);
