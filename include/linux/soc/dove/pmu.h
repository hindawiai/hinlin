<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित LINUX_SOC_DOVE_PMU_H
#घोषणा LINUX_SOC_DOVE_PMU_H

#समावेश <linux/types.h>

काष्ठा करोve_pmu_करोमुख्य_initdata अणु
	u32 pwr_mask;
	u32 rst_mask;
	u32 iso_mask;
	स्थिर अक्षर *name;
पूर्ण;

काष्ठा करोve_pmu_initdata अणु
	व्योम __iomem *pmc_base;
	व्योम __iomem *pmu_base;
	पूर्णांक irq;
	पूर्णांक irq_करोमुख्य_start;
	स्थिर काष्ठा करोve_pmu_करोमुख्य_initdata *करोमुख्यs;
पूर्ण;

पूर्णांक करोve_init_pmu_legacy(स्थिर काष्ठा करोve_pmu_initdata *);

पूर्णांक करोve_init_pmu(व्योम);

#पूर्ण_अगर
