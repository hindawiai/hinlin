<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2014 NVIDIA Corporation
 */

#अगर_अघोषित __SOC_TEGRA_PM_H__
#घोषणा __SOC_TEGRA_PM_H__

#समावेश <linux/त्रुटिसं.स>

क्रमागत tegra_suspend_mode अणु
	TEGRA_SUSPEND_NONE = 0,
	TEGRA_SUSPEND_LP2, /* CPU voltage off */
	TEGRA_SUSPEND_LP1, /* CPU voltage off, DRAM self-refresh */
	TEGRA_SUSPEND_LP0, /* CPU + core voltage off, DRAM self-refresh */
	TEGRA_MAX_SUSPEND_MODE,
पूर्ण;

#अगर defined(CONFIG_PM_SLEEP) && defined(CONFIG_ARM)
क्रमागत tegra_suspend_mode
tegra_pm_validate_suspend_mode(क्रमागत tegra_suspend_mode mode);

/* low-level resume entry poपूर्णांक */
व्योम tegra_resume(व्योम);

पूर्णांक tegra30_pm_secondary_cpu_suspend(अचिन्हित दीर्घ arg);
व्योम tegra_pm_clear_cpu_in_lp2(व्योम);
व्योम tegra_pm_set_cpu_in_lp2(व्योम);
पूर्णांक tegra_pm_enter_lp2(व्योम);
पूर्णांक tegra_pm_park_secondary_cpu(अचिन्हित दीर्घ cpu);
#अन्यथा
अटल अंतरभूत क्रमागत tegra_suspend_mode
tegra_pm_validate_suspend_mode(क्रमागत tegra_suspend_mode mode)
अणु
	वापस TEGRA_SUSPEND_NONE;
पूर्ण

अटल अंतरभूत व्योम tegra_resume(व्योम)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक tegra30_pm_secondary_cpu_suspend(अचिन्हित दीर्घ arg)
अणु
	वापस -ENOTSUPP;
पूर्ण

अटल अंतरभूत व्योम tegra_pm_clear_cpu_in_lp2(व्योम)
अणु
पूर्ण

अटल अंतरभूत व्योम tegra_pm_set_cpu_in_lp2(व्योम)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक tegra_pm_enter_lp2(व्योम)
अणु
	वापस -ENOTSUPP;
पूर्ण

अटल अंतरभूत पूर्णांक tegra_pm_park_secondary_cpu(अचिन्हित दीर्घ cpu)
अणु
	वापस -ENOTSUPP;
पूर्ण
#पूर्ण_अगर /* CONFIG_PM_SLEEP */

#पूर्ण_अगर /* __SOC_TEGRA_PM_H__ */
