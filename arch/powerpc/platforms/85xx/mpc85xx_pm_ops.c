<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * MPC85xx PM चालकs
 *
 * Copyright 2015 Freescale Semiconductor Inc.
 */

#घोषणा pr_fmt(fmt) "%s: " fmt, __func__

#समावेश <linux/kernel.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/fsl/guts.h>

#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/fsl_pm.h>

अटल काष्ठा ccsr_guts __iomem *guts;

अटल व्योम mpc85xx_irq_mask(पूर्णांक cpu)
अणु

पूर्ण

अटल व्योम mpc85xx_irq_unmask(पूर्णांक cpu)
अणु

पूर्ण

अटल व्योम mpc85xx_cpu_die(पूर्णांक cpu)
अणु
	u32 पंचांगp;

	पंचांगp = (mfspr(SPRN_HID0) & ~(HID0_DOZE|HID0_SLEEP)) | HID0_NAP;
	mtspr(SPRN_HID0, पंचांगp);

	/* Enter NAP mode. */
	पंचांगp = mfmsr();
	पंचांगp |= MSR_WE;
	यंत्र अस्थिर(
		"msync\n"
		"mtmsr %0\n"
		"isync\n"
		:
		: "r" (पंचांगp));
पूर्ण

अटल व्योम mpc85xx_cpu_up_prepare(पूर्णांक cpu)
अणु

पूर्ण

अटल व्योम mpc85xx_मुक्तze_समय_base(bool मुक्तze)
अणु
	uपूर्णांक32_t mask;

	mask = CCSR_GUTS_DEVDISR_TB0 | CCSR_GUTS_DEVDISR_TB1;
	अगर (मुक्तze)
		setbits32(&guts->devdisr, mask);
	अन्यथा
		clrbits32(&guts->devdisr, mask);

	in_be32(&guts->devdisr);
पूर्ण

अटल स्थिर काष्ठा of_device_id mpc85xx_smp_guts_ids[] = अणु
	अणु .compatible = "fsl,mpc8572-guts", पूर्ण,
	अणु .compatible = "fsl,p1020-guts", पूर्ण,
	अणु .compatible = "fsl,p1021-guts", पूर्ण,
	अणु .compatible = "fsl,p1022-guts", पूर्ण,
	अणु .compatible = "fsl,p1023-guts", पूर्ण,
	अणु .compatible = "fsl,p2020-guts", पूर्ण,
	अणु .compatible = "fsl,bsc9132-guts", पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल स्थिर काष्ठा fsl_pm_ops mpc85xx_pm_ops = अणु
	.मुक्तze_समय_base = mpc85xx_मुक्तze_समय_base,
	.irq_mask = mpc85xx_irq_mask,
	.irq_unmask = mpc85xx_irq_unmask,
	.cpu_die = mpc85xx_cpu_die,
	.cpu_up_prepare = mpc85xx_cpu_up_prepare,
पूर्ण;

पूर्णांक __init mpc85xx_setup_pmc(व्योम)
अणु
	काष्ठा device_node *np;

	np = of_find_matching_node(शून्य, mpc85xx_smp_guts_ids);
	अगर (np) अणु
		guts = of_iomap(np, 0);
		of_node_put(np);
		अगर (!guts) अणु
			pr_err("Could not map guts node address\n");
			वापस -ENOMEM;
		पूर्ण
	पूर्ण

	qoriq_pm_ops = &mpc85xx_pm_ops;

	वापस 0;
पूर्ण
