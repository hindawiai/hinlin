<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Suspend/resume support
 *
 * Copyright 2009  MontaVista Software, Inc.
 *
 * Author: Anton Vorontsov <avorontsov@ru.mvista.com>
 */

#समावेश <linux/init.h>
#समावेश <linux/types.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/export.h>
#समावेश <linux/suspend.h>
#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_platक्रमm.h>

काष्ठा pmc_regs अणु
	__be32 devdisr;
	__be32 devdisr2;
	__be32 :32;
	__be32 :32;
	__be32 pmcsr;
#घोषणा PMCSR_SLP	(1 << 17)
पूर्ण;

अटल काष्ठा device *pmc_dev;
अटल काष्ठा pmc_regs __iomem *pmc_regs;

अटल पूर्णांक pmc_suspend_enter(suspend_state_t state)
अणु
	पूर्णांक ret;

	setbits32(&pmc_regs->pmcsr, PMCSR_SLP);
	/* At this poपूर्णांक, the CPU is asleep. */

	/* Upon resume, रुको क्रम SLP bit to be clear. */
	ret = spin_event_समयout((in_be32(&pmc_regs->pmcsr) & PMCSR_SLP) == 0,
				 10000, 10) ? 0 : -ETIMEDOUT;
	अगर (ret)
		dev_err(pmc_dev, "tired waiting for SLP bit to clear\n");
	वापस ret;
पूर्ण

अटल पूर्णांक pmc_suspend_valid(suspend_state_t state)
अणु
	अगर (state != PM_SUSPEND_STANDBY)
		वापस 0;
	वापस 1;
पूर्ण

अटल स्थिर काष्ठा platक्रमm_suspend_ops pmc_suspend_ops = अणु
	.valid = pmc_suspend_valid,
	.enter = pmc_suspend_enter,
पूर्ण;

अटल पूर्णांक pmc_probe(काष्ठा platक्रमm_device *ofdev)
अणु
	pmc_regs = of_iomap(ofdev->dev.of_node, 0);
	अगर (!pmc_regs)
		वापस -ENOMEM;

	pmc_dev = &ofdev->dev;
	suspend_set_ops(&pmc_suspend_ops);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id pmc_ids[] = अणु
	अणु .compatible = "fsl,mpc8548-pmc", पूर्ण,
	अणु .compatible = "fsl,mpc8641d-pmc", पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver pmc_driver = अणु
	.driver = अणु
		.name = "fsl-pmc",
		.of_match_table = pmc_ids,
	पूर्ण,
	.probe = pmc_probe,
पूर्ण;

builtin_platक्रमm_driver(pmc_driver);
