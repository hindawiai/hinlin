<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2012 Freescale Semiconductor, Inc.
 */

#समावेश <linux/cpuidle.h>
#समावेश <linux/module.h>
#समावेश <यंत्र/प्रणाली_misc.h>
#समावेश "cpuidle.h"

अटल पूर्णांक imx5_cpuidle_enter(काष्ठा cpuidle_device *dev,
			      काष्ठा cpuidle_driver *drv, पूर्णांक index)
अणु
	arm_pm_idle();
	वापस index;
पूर्ण

अटल काष्ठा cpuidle_driver imx5_cpuidle_driver = अणु
	.name             = "imx5_cpuidle",
	.owner            = THIS_MODULE,
	.states[0] = अणु
		.enter            = imx5_cpuidle_enter,
		.निकास_latency     = 2,
		.target_residency = 1,
		.name             = "IMX5 SRPG",
		.desc             = "CPU state retained,powered off",
	पूर्ण,
	.state_count = 1,
पूर्ण;

पूर्णांक __init imx5_cpuidle_init(व्योम)
अणु
	वापस cpuidle_रेजिस्टर(&imx5_cpuidle_driver, शून्य);
पूर्ण
