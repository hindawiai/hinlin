<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Samsung's Exynos pinctrl bindings
 *
 * Copyright (c) 2016 Samsung Electronics Co., Ltd.
 *		http://www.samsung.com
 * Author: Krzysztof Kozlowski <krzk@kernel.org>
 */

#अगर_अघोषित __DT_BINDINGS_PINCTRL_SAMSUNG_H__
#घोषणा __DT_BINDINGS_PINCTRL_SAMSUNG_H__

#घोषणा EXYNOS_PIN_PULL_NONE		0
#घोषणा EXYNOS_PIN_PULL_DOWN		1
#घोषणा EXYNOS_PIN_PULL_UP		3

#घोषणा S3C64XX_PIN_PULL_NONE		0
#घोषणा S3C64XX_PIN_PULL_DOWN		1
#घोषणा S3C64XX_PIN_PULL_UP		2

/* Pin function in घातer करोwn mode */
#घोषणा EXYNOS_PIN_PDN_OUT0		0
#घोषणा EXYNOS_PIN_PDN_OUT1		1
#घोषणा EXYNOS_PIN_PDN_INPUT		2
#घोषणा EXYNOS_PIN_PDN_PREV		3

/* Drive strengths क्रम Exynos3250, Exynos4 (all) and Exynos5250 */
#घोषणा EXYNOS4_PIN_DRV_LV1		0
#घोषणा EXYNOS4_PIN_DRV_LV2		2
#घोषणा EXYNOS4_PIN_DRV_LV3		1
#घोषणा EXYNOS4_PIN_DRV_LV4		3

/* Drive strengths क्रम Exynos5260 */
#घोषणा EXYNOS5260_PIN_DRV_LV1		0
#घोषणा EXYNOS5260_PIN_DRV_LV2		1
#घोषणा EXYNOS5260_PIN_DRV_LV4		2
#घोषणा EXYNOS5260_PIN_DRV_LV6		3

/* Drive strengths क्रम Exynos5410, Exynos542x and Exynos5800 */
#घोषणा EXYNOS5420_PIN_DRV_LV1		0
#घोषणा EXYNOS5420_PIN_DRV_LV2		1
#घोषणा EXYNOS5420_PIN_DRV_LV3		2
#घोषणा EXYNOS5420_PIN_DRV_LV4		3

/* Drive strengths क्रम Exynos5433 */
#घोषणा EXYNOS5433_PIN_DRV_FAST_SR1	0
#घोषणा EXYNOS5433_PIN_DRV_FAST_SR2	1
#घोषणा EXYNOS5433_PIN_DRV_FAST_SR3	2
#घोषणा EXYNOS5433_PIN_DRV_FAST_SR4	3
#घोषणा EXYNOS5433_PIN_DRV_FAST_SR5	4
#घोषणा EXYNOS5433_PIN_DRV_FAST_SR6	5
#घोषणा EXYNOS5433_PIN_DRV_SLOW_SR1	8
#घोषणा EXYNOS5433_PIN_DRV_SLOW_SR2	9
#घोषणा EXYNOS5433_PIN_DRV_SLOW_SR3	0xa
#घोषणा EXYNOS5433_PIN_DRV_SLOW_SR4	0xb
#घोषणा EXYNOS5433_PIN_DRV_SLOW_SR5	0xc
#घोषणा EXYNOS5433_PIN_DRV_SLOW_SR6	0xf

#घोषणा EXYNOS_PIN_FUNC_INPUT		0
#घोषणा EXYNOS_PIN_FUNC_OUTPUT		1
#घोषणा EXYNOS_PIN_FUNC_2		2
#घोषणा EXYNOS_PIN_FUNC_3		3
#घोषणा EXYNOS_PIN_FUNC_4		4
#घोषणा EXYNOS_PIN_FUNC_5		5
#घोषणा EXYNOS_PIN_FUNC_6		6
#घोषणा EXYNOS_PIN_FUNC_EINT		0xf
#घोषणा EXYNOS_PIN_FUNC_F		EXYNOS_PIN_FUNC_EINT

/* Drive strengths क्रम Exynos7 FSYS1 block */
#घोषणा EXYNOS7_FSYS1_PIN_DRV_LV1	0
#घोषणा EXYNOS7_FSYS1_PIN_DRV_LV2	4
#घोषणा EXYNOS7_FSYS1_PIN_DRV_LV3	2
#घोषणा EXYNOS7_FSYS1_PIN_DRV_LV4	6
#घोषणा EXYNOS7_FSYS1_PIN_DRV_LV5	1
#घोषणा EXYNOS7_FSYS1_PIN_DRV_LV6	5

#पूर्ण_अगर /* __DT_BINDINGS_PINCTRL_SAMSUNG_H__ */
