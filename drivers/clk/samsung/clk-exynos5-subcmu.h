<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

#अगर_अघोषित __CLK_EXYNOS5_SUBCMU_H
#घोषणा __CLK_EXYNOS5_SUBCMU_H

काष्ठा exynos5_subcmu_reg_dump अणु
	u32 offset;
	u32 value;
	u32 mask;
	u32 save;
पूर्ण;

काष्ठा exynos5_subcmu_info अणु
	स्थिर काष्ठा samsung_भाग_घड़ी *भाग_clks;
	अचिन्हित पूर्णांक nr_भाग_clks;
	स्थिर काष्ठा samsung_gate_घड़ी *gate_clks;
	अचिन्हित पूर्णांक nr_gate_clks;
	काष्ठा exynos5_subcmu_reg_dump *suspend_regs;
	अचिन्हित पूर्णांक nr_suspend_regs;
	स्थिर अक्षर *pd_name;
पूर्ण;

व्योम exynos5_subcmus_init(काष्ठा samsung_clk_provider *ctx, पूर्णांक nr_cmus,
			  स्थिर काष्ठा exynos5_subcmu_info **cmu);

#पूर्ण_अगर
