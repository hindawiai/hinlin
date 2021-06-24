<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (c) 2019 Samsung Electronics Co., Ltd.
 *	      http://www.samsung.com/
 *
 * Samsung Exynos 5422 SoC Adaptive Supply Voltage support
 */

#अगर_अघोषित __LINUX_SOC_EXYNOS5422_ASV_H
#घोषणा __LINUX_SOC_EXYNOS5422_ASV_H

#समावेश <linux/त्रुटिसं.स>

क्रमागत अणु
	EXYNOS_ASV_SUBSYS_ID_ARM,
	EXYNOS_ASV_SUBSYS_ID_KFC,
	EXYNOS_ASV_SUBSYS_ID_MAX
पूर्ण;

काष्ठा exynos_asv;

#अगर_घोषित CONFIG_EXYNOS_ASV_ARM
पूर्णांक exynos5422_asv_init(काष्ठा exynos_asv *asv);
#अन्यथा
अटल अंतरभूत पूर्णांक exynos5422_asv_init(काष्ठा exynos_asv *asv)
अणु
	वापस -ENOTSUPP;
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* __LINUX_SOC_EXYNOS5422_ASV_H */
