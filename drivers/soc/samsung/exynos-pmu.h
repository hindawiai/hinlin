<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (c) 2015 Samsung Electronics Co., Ltd.
 *		http://www.samsung.com
 *
 * Header क्रम Exynos PMU Driver support
 */

#अगर_अघोषित __EXYNOS_PMU_H
#घोषणा __EXYNOS_PMU_H

#समावेश <linux/पन.स>

#घोषणा PMU_TABLE_END	(-1U)

काष्ठा exynos_pmu_conf अणु
	अचिन्हित पूर्णांक offset;
	u8 val[NUM_SYS_POWERDOWN];
पूर्ण;

काष्ठा exynos_pmu_data अणु
	स्थिर काष्ठा exynos_pmu_conf *pmu_config;

	व्योम (*pmu_init)(व्योम);
	व्योम (*घातerकरोwn_conf)(क्रमागत sys_घातerकरोwn);
	व्योम (*घातerकरोwn_conf_extra)(क्रमागत sys_घातerकरोwn);
पूर्ण;

बाह्य व्योम __iomem *pmu_base_addr;

#अगर_घोषित CONFIG_EXYNOS_PMU_ARM_DRIVERS
/* list of all exported SoC specअगरic data */
बाह्य स्थिर काष्ठा exynos_pmu_data exynos3250_pmu_data;
बाह्य स्थिर काष्ठा exynos_pmu_data exynos4210_pmu_data;
बाह्य स्थिर काष्ठा exynos_pmu_data exynos4412_pmu_data;
बाह्य स्थिर काष्ठा exynos_pmu_data exynos5250_pmu_data;
बाह्य स्थिर काष्ठा exynos_pmu_data exynos5420_pmu_data;
#पूर्ण_अगर

बाह्य व्योम pmu_raw_ग_लिखोl(u32 val, u32 offset);
बाह्य u32 pmu_raw_पढ़ोl(u32 offset);
#पूर्ण_अगर /* __EXYNOS_PMU_H */
