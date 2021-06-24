<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (c) 2014 Samsung Electronics Co., Ltd.
 *
 * Common Clock Framework support क्रम all PLL's in Samsung platक्रमms
*/

#अगर_अघोषित __SAMSUNG_CLK_CPU_H
#घोषणा __SAMSUNG_CLK_CPU_H

#समावेश "clk.h"

/**
 * काष्ठा exynos_cpuclk_data: config data to setup cpu घड़ीs.
 * @prate: frequency of the primary parent घड़ी (in KHz).
 * @भाग0: value to be programmed in the भाग_cpu0 रेजिस्टर.
 * @भाग1: value to be programmed in the भाग_cpu1 रेजिस्टर.
 *
 * This काष्ठाure holds the भागider configuration data क्रम भागiders in the CPU
 * घड़ी करोमुख्य. The parent frequency at which these भागider values are valid is
 * specअगरied in @prate. The @prate is the frequency of the primary parent घड़ी.
 * For CPU घड़ी करोमुख्यs that करो not have a DIV1 रेजिस्टर, the @भाग1 member
 * value is not used.
 */
काष्ठा exynos_cpuclk_cfg_data अणु
	अचिन्हित दीर्घ	prate;
	अचिन्हित दीर्घ	भाग0;
	अचिन्हित दीर्घ	भाग1;
पूर्ण;

/**
 * काष्ठा exynos_cpuclk: inक्रमmation about घड़ी supplied to a CPU core.
 * @hw:	handle between CCF and CPU घड़ी.
 * @alt_parent: alternate parent घड़ी to use when चयनing the speed
 *	of the primary parent घड़ी.
 * @ctrl_base:	base address of the घड़ी controller.
 * @lock: cpu घड़ी करोमुख्य रेजिस्टर access lock.
 * @cfg: cpu घड़ी rate configuration data.
 * @num_cfgs: number of array elements in @cfg array.
 * @clk_nb: घड़ी notअगरier रेजिस्टरed क्रम changes in घड़ी speed of the
 *	primary parent घड़ी.
 * @flags: configuration flags क्रम the CPU घड़ी.
 *
 * This काष्ठाure holds inक्रमmation required क्रम programming the CPU घड़ी क्रम
 * various घड़ी speeds.
 */
काष्ठा exynos_cpuclk अणु
	काष्ठा clk_hw				hw;
	स्थिर काष्ठा clk_hw			*alt_parent;
	व्योम __iomem				*ctrl_base;
	spinlock_t				*lock;
	स्थिर काष्ठा exynos_cpuclk_cfg_data	*cfg;
	स्थिर अचिन्हित दीर्घ			num_cfgs;
	काष्ठा notअगरier_block			clk_nb;
	अचिन्हित दीर्घ				flags;

/* The CPU घड़ी रेजिस्टरs have DIV1 configuration रेजिस्टर */
#घोषणा CLK_CPU_HAS_DIV1		(1 << 0)
/* When ALT parent is active, debug घड़ीs need safe भागider values */
#घोषणा CLK_CPU_NEEDS_DEBUG_ALT_DIV	(1 << 1)
/* The CPU घड़ी रेजिस्टरs have Exynos5433-compatible layout */
#घोषणा CLK_CPU_HAS_E5433_REGS_LAYOUT	(1 << 2)
पूर्ण;

पूर्णांक __init exynos_रेजिस्टर_cpu_घड़ी(काष्ठा samsung_clk_provider *ctx,
			अचिन्हित पूर्णांक lookup_id, स्थिर अक्षर *name,
			स्थिर काष्ठा clk_hw *parent, स्थिर काष्ठा clk_hw *alt_parent,
			अचिन्हित दीर्घ offset,
			स्थिर काष्ठा exynos_cpuclk_cfg_data *cfg,
			अचिन्हित दीर्घ num_cfgs, अचिन्हित दीर्घ flags);

#पूर्ण_अगर /* __SAMSUNG_CLK_CPU_H */
