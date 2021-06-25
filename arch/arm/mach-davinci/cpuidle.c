<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * CPU idle क्रम DaVinci SoCs
 *
 * Copyright (C) 2009 Texas Instruments Incorporated. https://www.ti.com/
 *
 * Derived from Marvell Kirkwood CPU idle code
 * (arch/arm/mach-kirkwood/cpuidle.c)
 */

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/cpuidle.h>
#समावेश <linux/पन.स>
#समावेश <linux/export.h>
#समावेश <यंत्र/cpuidle.h>

#समावेश "cpuidle.h"
#समावेश "ddr2.h"

#घोषणा DAVINCI_CPUIDLE_MAX_STATES	2

अटल व्योम __iomem *ddr2_reg_base;
अटल bool ddr2_pकरोwn;

अटल व्योम davinci_save_ddr_घातer(पूर्णांक enter, bool pकरोwn)
अणु
	u32 val;

	val = __raw_पढ़ोl(ddr2_reg_base + DDR2_SDRCR_OFFSET);

	अगर (enter) अणु
		अगर (pकरोwn)
			val |= DDR2_SRPD_BIT;
		अन्यथा
			val &= ~DDR2_SRPD_BIT;
		val |= DDR2_LPMODEN_BIT;
	पूर्ण अन्यथा अणु
		val &= ~(DDR2_SRPD_BIT | DDR2_LPMODEN_BIT);
	पूर्ण

	__raw_ग_लिखोl(val, ddr2_reg_base + DDR2_SDRCR_OFFSET);
पूर्ण

/* Actual code that माला_दो the SoC in dअगरferent idle states */
अटल पूर्णांक davinci_enter_idle(काष्ठा cpuidle_device *dev,
			      काष्ठा cpuidle_driver *drv, पूर्णांक index)
अणु
	davinci_save_ddr_घातer(1, ddr2_pकरोwn);
	cpu_करो_idle();
	davinci_save_ddr_घातer(0, ddr2_pकरोwn);

	वापस index;
पूर्ण

अटल काष्ठा cpuidle_driver davinci_idle_driver = अणु
	.name			= "cpuidle-davinci",
	.owner			= THIS_MODULE,
	.states[0]		= ARM_CPUIDLE_WFI_STATE,
	.states[1]		= अणु
		.enter			= davinci_enter_idle,
		.निकास_latency		= 10,
		.target_residency	= 10000,
		.name			= "DDR SR",
		.desc			= "WFI and DDR Self Refresh",
	पूर्ण,
	.state_count = DAVINCI_CPUIDLE_MAX_STATES,
पूर्ण;

अटल पूर्णांक __init davinci_cpuidle_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा davinci_cpuidle_config *pdata = pdev->dev.platक्रमm_data;

	अगर (!pdata) अणु
		dev_err(&pdev->dev, "cannot get platform data\n");
		वापस -ENOENT;
	पूर्ण

	ddr2_reg_base = pdata->ddr2_ctlr_base;

	ddr2_pकरोwn = pdata->ddr2_pकरोwn;

	वापस cpuidle_रेजिस्टर(&davinci_idle_driver, शून्य);
पूर्ण

अटल काष्ठा platक्रमm_driver davinci_cpuidle_driver = अणु
	.driver = अणु
		.name	= "cpuidle-davinci",
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init davinci_cpuidle_init(व्योम)
अणु
	वापस platक्रमm_driver_probe(&davinci_cpuidle_driver,
						davinci_cpuidle_probe);
पूर्ण
device_initcall(davinci_cpuidle_init);

