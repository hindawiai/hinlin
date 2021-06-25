<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright (C) 2016 Freescale Semiconductor, Inc.
 * Copyright 2017-2018 NXP
 *   Anson Huang <Anson.Huang@nxp.com>
 */

#समावेश <linux/cpuidle.h>
#समावेश <linux/module.h>
#समावेश <यंत्र/cpuidle.h>

#समावेश "common.h"
#समावेश "cpuidle.h"

अटल पूर्णांक imx7ulp_enter_रुको(काष्ठा cpuidle_device *dev,
			    काष्ठा cpuidle_driver *drv, पूर्णांक index)
अणु
	अगर (index == 1)
		imx7ulp_set_lpm(ULP_PM_WAIT);
	अन्यथा
		imx7ulp_set_lpm(ULP_PM_STOP);

	cpu_करो_idle();

	imx7ulp_set_lpm(ULP_PM_RUN);

	वापस index;
पूर्ण

अटल काष्ठा cpuidle_driver imx7ulp_cpuidle_driver = अणु
	.name = "imx7ulp_cpuidle",
	.owner = THIS_MODULE,
	.states = अणु
		/* WFI */
		ARM_CPUIDLE_WFI_STATE,
		/* WAIT */
		अणु
			.निकास_latency = 50,
			.target_residency = 75,
			.enter = imx7ulp_enter_रुको,
			.name = "WAIT",
			.desc = "PSTOP2",
		पूर्ण,
		/* STOP */
		अणु
			.निकास_latency = 100,
			.target_residency = 150,
			.enter = imx7ulp_enter_रुको,
			.name = "STOP",
			.desc = "PSTOP1",
		पूर्ण,
	पूर्ण,
	.state_count = 3,
	.safe_state_index = 0,
पूर्ण;

पूर्णांक __init imx7ulp_cpuidle_init(व्योम)
अणु
	वापस cpuidle_रेजिस्टर(&imx7ulp_cpuidle_driver, शून्य);
पूर्ण
