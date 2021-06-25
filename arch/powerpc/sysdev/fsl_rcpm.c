<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * RCPM(Run Control/Power Management) support
 *
 * Copyright 2012-2015 Freescale Semiconductor Inc.
 *
 * Author: Chenhui Zhao <chenhui.zhao@मुक्तscale.com>
 */

#घोषणा pr_fmt(fmt) "%s: " fmt, __func__

#समावेश <linux/types.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/of_address.h>
#समावेश <linux/export.h>

#समावेश <यंत्र/पन.स>
#समावेश <linux/fsl/guts.h>
#समावेश <यंत्र/cputhपढ़ोs.h>
#समावेश <यंत्र/fsl_pm.h>
#समावेश <यंत्र/smp.h>

अटल काष्ठा ccsr_rcpm_v1 __iomem *rcpm_v1_regs;
अटल काष्ठा ccsr_rcpm_v2 __iomem *rcpm_v2_regs;
अटल अचिन्हित पूर्णांक fsl_supported_pm_modes;

अटल व्योम rcpm_v1_irq_mask(पूर्णांक cpu)
अणु
	पूर्णांक hw_cpu = get_hard_smp_processor_id(cpu);
	अचिन्हित पूर्णांक mask = 1 << hw_cpu;

	setbits32(&rcpm_v1_regs->cpmimr, mask);
	setbits32(&rcpm_v1_regs->cpmcimr, mask);
	setbits32(&rcpm_v1_regs->cpmmcmr, mask);
	setbits32(&rcpm_v1_regs->cpmnmimr, mask);
पूर्ण

अटल व्योम rcpm_v2_irq_mask(पूर्णांक cpu)
अणु
	पूर्णांक hw_cpu = get_hard_smp_processor_id(cpu);
	अचिन्हित पूर्णांक mask = 1 << hw_cpu;

	setbits32(&rcpm_v2_regs->tpmimr0, mask);
	setbits32(&rcpm_v2_regs->tpmcimr0, mask);
	setbits32(&rcpm_v2_regs->tpmmcmr0, mask);
	setbits32(&rcpm_v2_regs->tpmnmimr0, mask);
पूर्ण

अटल व्योम rcpm_v1_irq_unmask(पूर्णांक cpu)
अणु
	पूर्णांक hw_cpu = get_hard_smp_processor_id(cpu);
	अचिन्हित पूर्णांक mask = 1 << hw_cpu;

	clrbits32(&rcpm_v1_regs->cpmimr, mask);
	clrbits32(&rcpm_v1_regs->cpmcimr, mask);
	clrbits32(&rcpm_v1_regs->cpmmcmr, mask);
	clrbits32(&rcpm_v1_regs->cpmnmimr, mask);
पूर्ण

अटल व्योम rcpm_v2_irq_unmask(पूर्णांक cpu)
अणु
	पूर्णांक hw_cpu = get_hard_smp_processor_id(cpu);
	अचिन्हित पूर्णांक mask = 1 << hw_cpu;

	clrbits32(&rcpm_v2_regs->tpmimr0, mask);
	clrbits32(&rcpm_v2_regs->tpmcimr0, mask);
	clrbits32(&rcpm_v2_regs->tpmmcmr0, mask);
	clrbits32(&rcpm_v2_regs->tpmnmimr0, mask);
पूर्ण

अटल व्योम rcpm_v1_set_ip_घातer(bool enable, u32 mask)
अणु
	अगर (enable)
		setbits32(&rcpm_v1_regs->ippdexpcr, mask);
	अन्यथा
		clrbits32(&rcpm_v1_regs->ippdexpcr, mask);
पूर्ण

अटल व्योम rcpm_v2_set_ip_घातer(bool enable, u32 mask)
अणु
	अगर (enable)
		setbits32(&rcpm_v2_regs->ippdexpcr[0], mask);
	अन्यथा
		clrbits32(&rcpm_v2_regs->ippdexpcr[0], mask);
पूर्ण

अटल व्योम rcpm_v1_cpu_enter_state(पूर्णांक cpu, पूर्णांक state)
अणु
	पूर्णांक hw_cpu = get_hard_smp_processor_id(cpu);
	अचिन्हित पूर्णांक mask = 1 << hw_cpu;

	चयन (state) अणु
	हाल E500_PM_PH10:
		setbits32(&rcpm_v1_regs->cकरोzcr, mask);
		अवरोध;
	हाल E500_PM_PH15:
		setbits32(&rcpm_v1_regs->cnapcr, mask);
		अवरोध;
	शेष:
		pr_warn("Unknown cpu PM state (%d)\n", state);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम rcpm_v2_cpu_enter_state(पूर्णांक cpu, पूर्णांक state)
अणु
	पूर्णांक hw_cpu = get_hard_smp_processor_id(cpu);
	u32 mask = 1 << cpu_core_index_of_thपढ़ो(cpu);

	चयन (state) अणु
	हाल E500_PM_PH10:
		/* one bit corresponds to one thपढ़ो क्रम PH10 of 6500 */
		setbits32(&rcpm_v2_regs->tph10setr0, 1 << hw_cpu);
		अवरोध;
	हाल E500_PM_PH15:
		setbits32(&rcpm_v2_regs->pcph15setr, mask);
		अवरोध;
	हाल E500_PM_PH20:
		setbits32(&rcpm_v2_regs->pcph20setr, mask);
		अवरोध;
	हाल E500_PM_PH30:
		setbits32(&rcpm_v2_regs->pcph30setr, mask);
		अवरोध;
	शेष:
		pr_warn("Unknown cpu PM state (%d)\n", state);
	पूर्ण
पूर्ण

अटल व्योम rcpm_v1_cpu_die(पूर्णांक cpu)
अणु
	rcpm_v1_cpu_enter_state(cpu, E500_PM_PH15);
पूर्ण

#अगर_घोषित CONFIG_PPC64
अटल व्योम qoriq_disable_thपढ़ो(पूर्णांक cpu)
अणु
	पूर्णांक thपढ़ो = cpu_thपढ़ो_in_core(cpu);

	book3e_stop_thपढ़ो(thपढ़ो);
पूर्ण
#पूर्ण_अगर

अटल व्योम rcpm_v2_cpu_die(पूर्णांक cpu)
अणु
#अगर_घोषित CONFIG_PPC64
	पूर्णांक primary;

	अगर (thपढ़ोs_per_core == 2) अणु
		primary = cpu_first_thपढ़ो_sibling(cpu);
		अगर (cpu_is_offline(primary) && cpu_is_offline(primary + 1)) अणु
			/* अगर both thपढ़ोs are offline, put the cpu in PH20 */
			rcpm_v2_cpu_enter_state(cpu, E500_PM_PH20);
		पूर्ण अन्यथा अणु
			/* अगर only one thपढ़ो is offline, disable the thपढ़ो */
			qoriq_disable_thपढ़ो(cpu);
		पूर्ण
	पूर्ण
#पूर्ण_अगर

	अगर (thपढ़ोs_per_core == 1)
		rcpm_v2_cpu_enter_state(cpu, E500_PM_PH20);
पूर्ण

अटल व्योम rcpm_v1_cpu_निकास_state(पूर्णांक cpu, पूर्णांक state)
अणु
	पूर्णांक hw_cpu = get_hard_smp_processor_id(cpu);
	अचिन्हित पूर्णांक mask = 1 << hw_cpu;

	चयन (state) अणु
	हाल E500_PM_PH10:
		clrbits32(&rcpm_v1_regs->cकरोzcr, mask);
		अवरोध;
	हाल E500_PM_PH15:
		clrbits32(&rcpm_v1_regs->cnapcr, mask);
		अवरोध;
	शेष:
		pr_warn("Unknown cpu PM state (%d)\n", state);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम rcpm_v1_cpu_up_prepare(पूर्णांक cpu)
अणु
	rcpm_v1_cpu_निकास_state(cpu, E500_PM_PH15);
	rcpm_v1_irq_unmask(cpu);
पूर्ण

अटल व्योम rcpm_v2_cpu_निकास_state(पूर्णांक cpu, पूर्णांक state)
अणु
	पूर्णांक hw_cpu = get_hard_smp_processor_id(cpu);
	u32 mask = 1 << cpu_core_index_of_thपढ़ो(cpu);

	चयन (state) अणु
	हाल E500_PM_PH10:
		setbits32(&rcpm_v2_regs->tph10clrr0, 1 << hw_cpu);
		अवरोध;
	हाल E500_PM_PH15:
		setbits32(&rcpm_v2_regs->pcph15clrr, mask);
		अवरोध;
	हाल E500_PM_PH20:
		setbits32(&rcpm_v2_regs->pcph20clrr, mask);
		अवरोध;
	हाल E500_PM_PH30:
		setbits32(&rcpm_v2_regs->pcph30clrr, mask);
		अवरोध;
	शेष:
		pr_warn("Unknown cpu PM state (%d)\n", state);
	पूर्ण
पूर्ण

अटल व्योम rcpm_v2_cpu_up_prepare(पूर्णांक cpu)
अणु
	rcpm_v2_cpu_निकास_state(cpu, E500_PM_PH20);
	rcpm_v2_irq_unmask(cpu);
पूर्ण

अटल पूर्णांक rcpm_v1_plat_enter_state(पूर्णांक state)
अणु
	u32 *pmcsr_reg = &rcpm_v1_regs->घातmgtcsr;
	पूर्णांक ret = 0;
	पूर्णांक result;

	चयन (state) अणु
	हाल PLAT_PM_SLEEP:
		setbits32(pmcsr_reg, RCPM_POWMGTCSR_SLP);

		/* Upon resume, रुको क्रम RCPM_POWMGTCSR_SLP bit to be clear. */
		result = spin_event_समयout(
		  !(in_be32(pmcsr_reg) & RCPM_POWMGTCSR_SLP), 10000, 10);
		अगर (!result) अणु
			pr_err("timeout waiting for SLP bit to be cleared\n");
			ret = -ETIMEDOUT;
		पूर्ण
		अवरोध;
	शेष:
		pr_warn("Unknown platform PM state (%d)", state);
		ret = -EINVAL;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक rcpm_v2_plat_enter_state(पूर्णांक state)
अणु
	u32 *pmcsr_reg = &rcpm_v2_regs->घातmgtcsr;
	पूर्णांक ret = 0;
	पूर्णांक result;

	चयन (state) अणु
	हाल PLAT_PM_LPM20:
		/* clear previous LPM20 status */
		setbits32(pmcsr_reg, RCPM_POWMGTCSR_P_LPM20_ST);
		/* enter LPM20 status */
		setbits32(pmcsr_reg, RCPM_POWMGTCSR_LPM20_RQ);

		/* At this poपूर्णांक, the device is in LPM20 status. */

		/* resume ... */
		result = spin_event_समयout(
		  !(in_be32(pmcsr_reg) & RCPM_POWMGTCSR_LPM20_ST), 10000, 10);
		अगर (!result) अणु
			pr_err("timeout waiting for LPM20 bit to be cleared\n");
			ret = -ETIMEDOUT;
		पूर्ण
		अवरोध;
	शेष:
		pr_warn("Unknown platform PM state (%d)\n", state);
		ret = -EINVAL;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक rcpm_v1_plat_enter_sleep(व्योम)
अणु
	वापस rcpm_v1_plat_enter_state(PLAT_PM_SLEEP);
पूर्ण

अटल पूर्णांक rcpm_v2_plat_enter_sleep(व्योम)
अणु
	वापस rcpm_v2_plat_enter_state(PLAT_PM_LPM20);
पूर्ण

अटल व्योम rcpm_common_मुक्तze_समय_base(u32 *tben_reg, पूर्णांक मुक्तze)
अणु
	अटल u32 mask;

	अगर (मुक्तze) अणु
		mask = in_be32(tben_reg);
		clrbits32(tben_reg, mask);
	पूर्ण अन्यथा अणु
		setbits32(tben_reg, mask);
	पूर्ण

	/* पढ़ो back to push the previous ग_लिखो */
	in_be32(tben_reg);
पूर्ण

अटल व्योम rcpm_v1_मुक्तze_समय_base(bool मुक्तze)
अणु
	rcpm_common_मुक्तze_समय_base(&rcpm_v1_regs->ctbenr, मुक्तze);
पूर्ण

अटल व्योम rcpm_v2_मुक्तze_समय_base(bool मुक्तze)
अणु
	rcpm_common_मुक्तze_समय_base(&rcpm_v2_regs->pctbenr, मुक्तze);
पूर्ण

अटल अचिन्हित पूर्णांक rcpm_get_pm_modes(व्योम)
अणु
	वापस fsl_supported_pm_modes;
पूर्ण

अटल स्थिर काष्ठा fsl_pm_ops qoriq_rcpm_v1_ops = अणु
	.irq_mask = rcpm_v1_irq_mask,
	.irq_unmask = rcpm_v1_irq_unmask,
	.cpu_enter_state = rcpm_v1_cpu_enter_state,
	.cpu_निकास_state = rcpm_v1_cpu_निकास_state,
	.cpu_up_prepare = rcpm_v1_cpu_up_prepare,
	.cpu_die = rcpm_v1_cpu_die,
	.plat_enter_sleep = rcpm_v1_plat_enter_sleep,
	.set_ip_घातer = rcpm_v1_set_ip_घातer,
	.मुक्तze_समय_base = rcpm_v1_मुक्तze_समय_base,
	.get_pm_modes = rcpm_get_pm_modes,
पूर्ण;

अटल स्थिर काष्ठा fsl_pm_ops qoriq_rcpm_v2_ops = अणु
	.irq_mask = rcpm_v2_irq_mask,
	.irq_unmask = rcpm_v2_irq_unmask,
	.cpu_enter_state = rcpm_v2_cpu_enter_state,
	.cpu_निकास_state = rcpm_v2_cpu_निकास_state,
	.cpu_up_prepare = rcpm_v2_cpu_up_prepare,
	.cpu_die = rcpm_v2_cpu_die,
	.plat_enter_sleep = rcpm_v2_plat_enter_sleep,
	.set_ip_घातer = rcpm_v2_set_ip_घातer,
	.मुक्तze_समय_base = rcpm_v2_मुक्तze_समय_base,
	.get_pm_modes = rcpm_get_pm_modes,
पूर्ण;

अटल स्थिर काष्ठा of_device_id rcpm_matches[] = अणु
	अणु
		.compatible = "fsl,qoriq-rcpm-1.0",
		.data = &qoriq_rcpm_v1_ops,
	पूर्ण,
	अणु
		.compatible = "fsl,qoriq-rcpm-2.0",
		.data = &qoriq_rcpm_v2_ops,
	पूर्ण,
	अणु
		.compatible = "fsl,qoriq-rcpm-2.1",
		.data = &qoriq_rcpm_v2_ops,
	पूर्ण,
	अणुपूर्ण,
पूर्ण;

पूर्णांक __init fsl_rcpm_init(व्योम)
अणु
	काष्ठा device_node *np;
	स्थिर काष्ठा of_device_id *match;
	व्योम __iomem *base;

	np = of_find_matching_node_and_match(शून्य, rcpm_matches, &match);
	अगर (!np)
		वापस 0;

	base = of_iomap(np, 0);
	of_node_put(np);
	अगर (!base) अणु
		pr_err("of_iomap() error.\n");
		वापस -ENOMEM;
	पूर्ण

	rcpm_v1_regs = base;
	rcpm_v2_regs = base;

	/* support sleep by शेष */
	fsl_supported_pm_modes = FSL_PM_SLEEP;

	qoriq_pm_ops = match->data;

	वापस 0;
पूर्ण
