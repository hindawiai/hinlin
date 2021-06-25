<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (c) 2014 Samsung Electronics Co., Ltd.
 *		http://www.samsung.com
 *
 * Header क्रम Exynos PMU Driver support
 */

#अगर_अघोषित __LINUX_SOC_EXYNOS_PMU_H
#घोषणा __LINUX_SOC_EXYNOS_PMU_H

काष्ठा regmap;

क्रमागत sys_घातerकरोwn अणु
	SYS_AFTR,
	SYS_LPA,
	SYS_SLEEP,
	NUM_SYS_POWERDOWN,
पूर्ण;

बाह्य व्योम exynos_sys_घातerकरोwn_conf(क्रमागत sys_घातerकरोwn mode);
#अगर_घोषित CONFIG_EXYNOS_PMU
बाह्य काष्ठा regmap *exynos_get_pmu_regmap(व्योम);
#अन्यथा
अटल अंतरभूत काष्ठा regmap *exynos_get_pmu_regmap(व्योम)
अणु
	वापस ERR_PTR(-ENODEV);
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* __LINUX_SOC_EXYNOS_PMU_H */
