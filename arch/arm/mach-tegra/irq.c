<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2011 Google, Inc.
 *
 * Author:
 *	Colin Cross <ccross@android.com>
 *
 * Copyright (C) 2010,2013, NVIDIA Corporation
 */

#समावेश <linux/cpu_pm.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/irqchip/arm-gic.h>
#समावेश <linux/irq.h>
#समावेश <linux/kernel.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of.h>
#समावेश <linux/syscore_ops.h>

#समावेश <soc/tegra/irq.h>

#समावेश "board.h"
#समावेश "iomap.h"

#घोषणा SGI_MASK 0xFFFF

#अगर_घोषित CONFIG_PM_SLEEP
अटल व्योम __iomem *tegra_gic_cpu_base;
#पूर्ण_अगर

bool tegra_pending_sgi(व्योम)
अणु
	u32 pending_set;
	व्योम __iomem *distbase = IO_ADDRESS(TEGRA_ARM_INT_DIST_BASE);

	pending_set = पढ़ोl_relaxed(distbase + GIC_DIST_PENDING_SET);

	अगर (pending_set & SGI_MASK)
		वापस true;

	वापस false;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक tegra_gic_notअगरier(काष्ठा notअगरier_block *self,
			      अचिन्हित दीर्घ cmd, व्योम *v)
अणु
	चयन (cmd) अणु
	हाल CPU_PM_ENTER:
		ग_लिखोl_relaxed(0x1E0, tegra_gic_cpu_base + GIC_CPU_CTRL);
		अवरोध;
	पूर्ण

	वापस NOTIFY_OK;
पूर्ण

अटल काष्ठा notअगरier_block tegra_gic_notअगरier_block = अणु
	.notअगरier_call = tegra_gic_notअगरier,
पूर्ण;

अटल स्थिर काष्ठा of_device_id tegra114_dt_gic_match[] __initस्थिर = अणु
	अणु .compatible = "arm,cortex-a15-gic" पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल व्योम __init tegra114_gic_cpu_pm_registration(व्योम)
अणु
	काष्ठा device_node *dn;

	dn = of_find_matching_node(शून्य, tegra114_dt_gic_match);
	अगर (!dn)
		वापस;

	tegra_gic_cpu_base = of_iomap(dn, 1);

	cpu_pm_रेजिस्टर_notअगरier(&tegra_gic_notअगरier_block);
पूर्ण
#अन्यथा
अटल व्योम __init tegra114_gic_cpu_pm_registration(व्योम) अणु पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा of_device_id tegra_ictlr_match[] __initस्थिर = अणु
	अणु .compatible = "nvidia,tegra20-ictlr" पूर्ण,
	अणु .compatible = "nvidia,tegra30-ictlr" पूर्ण,
	अणु पूर्ण
पूर्ण;

व्योम __init tegra_init_irq(व्योम)
अणु
	अगर (WARN_ON(!of_find_matching_node(शून्य, tegra_ictlr_match)))
		pr_warn("Outdated DT detected, suspend/resume will NOT work\n");

	tegra114_gic_cpu_pm_registration();
पूर्ण
