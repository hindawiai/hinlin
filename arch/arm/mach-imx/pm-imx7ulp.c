<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright (C) 2016 Freescale Semiconductor, Inc.
 * Copyright 2017-2018 NXP
 *   Author: Dong Aisheng <aisheng.करोng@nxp.com>
 */

#समावेश <linux/पन.स>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>

#समावेश "common.h"

#घोषणा SMC_PMCTRL		0x10
#घोषणा BP_PMCTRL_PSTOPO        16
#घोषणा PSTOPO_PSTOP3		0x3
#घोषणा PSTOPO_PSTOP2		0x2
#घोषणा PSTOPO_PSTOP1		0x1
#घोषणा BP_PMCTRL_RUNM		8
#घोषणा RUNM_RUN		0
#घोषणा BP_PMCTRL_STOPM		0
#घोषणा STOPM_STOP		0

#घोषणा BM_PMCTRL_PSTOPO	(3 << BP_PMCTRL_PSTOPO)
#घोषणा BM_PMCTRL_RUNM		(3 << BP_PMCTRL_RUNM)
#घोषणा BM_PMCTRL_STOPM		(7 << BP_PMCTRL_STOPM)

अटल व्योम __iomem *smc1_base;

पूर्णांक imx7ulp_set_lpm(क्रमागत ulp_cpu_pwr_mode mode)
अणु
	u32 val = पढ़ोl_relaxed(smc1_base + SMC_PMCTRL);

	/* clear all */
	val &= ~(BM_PMCTRL_RUNM | BM_PMCTRL_STOPM | BM_PMCTRL_PSTOPO);

	चयन (mode) अणु
	हाल ULP_PM_RUN:
		/* प्रणाली/bus घड़ी enabled */
		val |= PSTOPO_PSTOP3 << BP_PMCTRL_PSTOPO;
		अवरोध;
	हाल ULP_PM_WAIT:
		/* प्रणाली घड़ी disabled, bus घड़ी enabled */
		val |= PSTOPO_PSTOP2 << BP_PMCTRL_PSTOPO;
		अवरोध;
	हाल ULP_PM_STOP:
		/* प्रणाली/bus घड़ी disabled */
		val |= PSTOPO_PSTOP1 << BP_PMCTRL_PSTOPO;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	ग_लिखोl_relaxed(val, smc1_base + SMC_PMCTRL);

	वापस 0;
पूर्ण

व्योम __init imx7ulp_pm_init(व्योम)
अणु
	काष्ठा device_node *np;

	np = of_find_compatible_node(शून्य, शून्य, "fsl,imx7ulp-smc1");
	smc1_base = of_iomap(np, 0);
	of_node_put(np);
	WARN_ON(!smc1_base);

	imx7ulp_set_lpm(ULP_PM_RUN);
पूर्ण
