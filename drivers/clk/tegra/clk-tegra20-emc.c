<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Based on drivers/clk/tegra/clk-emc.c
 * Copyright (c) 2014, NVIDIA CORPORATION.  All rights reserved.
 *
 * Author: Dmitry Osipenko <digetx@gmail.com>
 * Copyright (C) 2019 GRATE-DRIVER project
 */

#घोषणा pr_fmt(fmt)	"tegra-emc-clk: " fmt

#समावेश <linux/bits.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/clk/tegra.h>
#समावेश <linux/err.h>
#समावेश <linux/export.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>

#समावेश "clk.h"

#घोषणा CLK_SOURCE_EMC_2X_CLK_DIVISOR_MASK	GENMASK(7, 0)
#घोषणा CLK_SOURCE_EMC_2X_CLK_SRC_MASK		GENMASK(31, 30)
#घोषणा CLK_SOURCE_EMC_2X_CLK_SRC_SHIFT		30

#घोषणा MC_EMC_SAME_FREQ	BIT(16)
#घोषणा USE_PLLM_UD		BIT(29)

#घोषणा EMC_SRC_PLL_M		0
#घोषणा EMC_SRC_PLL_C		1
#घोषणा EMC_SRC_PLL_P		2
#घोषणा EMC_SRC_CLK_M		3

अटल स्थिर अक्षर * स्थिर emc_parent_clk_names[] = अणु
	"pll_m", "pll_c", "pll_p", "clk_m",
पूर्ण;

काष्ठा tegra_clk_emc अणु
	काष्ठा clk_hw hw;
	व्योम __iomem *reg;
	bool mc_same_freq;
	bool want_low_jitter;

	tegra20_clk_emc_round_cb *round_cb;
	व्योम *cb_arg;
पूर्ण;

अटल अंतरभूत काष्ठा tegra_clk_emc *to_tegra_clk_emc(काष्ठा clk_hw *hw)
अणु
	वापस container_of(hw, काष्ठा tegra_clk_emc, hw);
पूर्ण

अटल अचिन्हित दीर्घ emc_recalc_rate(काष्ठा clk_hw *hw,
				     अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा tegra_clk_emc *emc = to_tegra_clk_emc(hw);
	u32 val, भाग;

	val = पढ़ोl_relaxed(emc->reg);
	भाग = val & CLK_SOURCE_EMC_2X_CLK_DIVISOR_MASK;

	वापस DIV_ROUND_UP(parent_rate * 2, भाग + 2);
पूर्ण

अटल u8 emc_get_parent(काष्ठा clk_hw *hw)
अणु
	काष्ठा tegra_clk_emc *emc = to_tegra_clk_emc(hw);

	वापस पढ़ोl_relaxed(emc->reg) >> CLK_SOURCE_EMC_2X_CLK_SRC_SHIFT;
पूर्ण

अटल पूर्णांक emc_set_parent(काष्ठा clk_hw *hw, u8 index)
अणु
	काष्ठा tegra_clk_emc *emc = to_tegra_clk_emc(hw);
	u32 val, भाग;

	val = पढ़ोl_relaxed(emc->reg);
	val &= ~CLK_SOURCE_EMC_2X_CLK_SRC_MASK;
	val |= index << CLK_SOURCE_EMC_2X_CLK_SRC_SHIFT;

	भाग = val & CLK_SOURCE_EMC_2X_CLK_DIVISOR_MASK;

	अगर (index == EMC_SRC_PLL_M && भाग == 0 && emc->want_low_jitter)
		val |= USE_PLLM_UD;
	अन्यथा
		val &= ~USE_PLLM_UD;

	अगर (emc->mc_same_freq)
		val |= MC_EMC_SAME_FREQ;
	अन्यथा
		val &= ~MC_EMC_SAME_FREQ;

	ग_लिखोl_relaxed(val, emc->reg);

	fence_udelay(1, emc->reg);

	वापस 0;
पूर्ण

अटल पूर्णांक emc_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
			अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा tegra_clk_emc *emc = to_tegra_clk_emc(hw);
	अचिन्हित पूर्णांक index;
	u32 val, भाग;

	भाग = भाग_frac_get(rate, parent_rate, 8, 1, 0);

	val = पढ़ोl_relaxed(emc->reg);
	val &= ~CLK_SOURCE_EMC_2X_CLK_DIVISOR_MASK;
	val |= भाग;

	index = val >> CLK_SOURCE_EMC_2X_CLK_SRC_SHIFT;

	अगर (index == EMC_SRC_PLL_M && भाग == 0 && emc->want_low_jitter)
		val |= USE_PLLM_UD;
	अन्यथा
		val &= ~USE_PLLM_UD;

	अगर (emc->mc_same_freq)
		val |= MC_EMC_SAME_FREQ;
	अन्यथा
		val &= ~MC_EMC_SAME_FREQ;

	ग_लिखोl_relaxed(val, emc->reg);

	fence_udelay(1, emc->reg);

	वापस 0;
पूर्ण

अटल पूर्णांक emc_set_rate_and_parent(काष्ठा clk_hw *hw,
				   अचिन्हित दीर्घ rate,
				   अचिन्हित दीर्घ parent_rate,
				   u8 index)
अणु
	काष्ठा tegra_clk_emc *emc = to_tegra_clk_emc(hw);
	u32 val, भाग;

	भाग = भाग_frac_get(rate, parent_rate, 8, 1, 0);

	val = पढ़ोl_relaxed(emc->reg);

	val &= ~CLK_SOURCE_EMC_2X_CLK_SRC_MASK;
	val |= index << CLK_SOURCE_EMC_2X_CLK_SRC_SHIFT;

	val &= ~CLK_SOURCE_EMC_2X_CLK_DIVISOR_MASK;
	val |= भाग;

	अगर (index == EMC_SRC_PLL_M && भाग == 0 && emc->want_low_jitter)
		val |= USE_PLLM_UD;
	अन्यथा
		val &= ~USE_PLLM_UD;

	अगर (emc->mc_same_freq)
		val |= MC_EMC_SAME_FREQ;
	अन्यथा
		val &= ~MC_EMC_SAME_FREQ;

	ग_लिखोl_relaxed(val, emc->reg);

	fence_udelay(1, emc->reg);

	वापस 0;
पूर्ण

अटल पूर्णांक emc_determine_rate(काष्ठा clk_hw *hw, काष्ठा clk_rate_request *req)
अणु
	काष्ठा tegra_clk_emc *emc = to_tegra_clk_emc(hw);
	काष्ठा clk_hw *parent_hw;
	अचिन्हित दीर्घ भागided_rate;
	अचिन्हित दीर्घ parent_rate;
	अचिन्हित पूर्णांक i;
	दीर्घ emc_rate;
	पूर्णांक भाग;

	emc_rate = emc->round_cb(req->rate, req->min_rate, req->max_rate,
				 emc->cb_arg);
	अगर (emc_rate < 0)
		वापस emc_rate;

	क्रम (i = 0; i < ARRAY_SIZE(emc_parent_clk_names); i++) अणु
		parent_hw = clk_hw_get_parent_by_index(hw, i);

		अगर (req->best_parent_hw == parent_hw)
			parent_rate = req->best_parent_rate;
		अन्यथा
			parent_rate = clk_hw_get_rate(parent_hw);

		अगर (emc_rate > parent_rate)
			जारी;

		भाग = भाग_frac_get(emc_rate, parent_rate, 8, 1, 0);
		भागided_rate = DIV_ROUND_UP(parent_rate * 2, भाग + 2);

		अगर (भागided_rate != emc_rate)
			जारी;

		req->best_parent_rate = parent_rate;
		req->best_parent_hw = parent_hw;
		req->rate = emc_rate;
		अवरोध;
	पूर्ण

	अगर (i == ARRAY_SIZE(emc_parent_clk_names)) अणु
		pr_err_once("can't find parent for rate %lu emc_rate %lu\n",
			    req->rate, emc_rate);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा clk_ops tegra_clk_emc_ops = अणु
	.recalc_rate = emc_recalc_rate,
	.get_parent = emc_get_parent,
	.set_parent = emc_set_parent,
	.set_rate = emc_set_rate,
	.set_rate_and_parent = emc_set_rate_and_parent,
	.determine_rate = emc_determine_rate,
पूर्ण;

व्योम tegra20_clk_set_emc_round_callback(tegra20_clk_emc_round_cb *round_cb,
					व्योम *cb_arg)
अणु
	काष्ठा clk *clk = __clk_lookup("emc");
	काष्ठा tegra_clk_emc *emc;
	काष्ठा clk_hw *hw;

	अगर (clk) अणु
		hw = __clk_get_hw(clk);
		emc = to_tegra_clk_emc(hw);

		emc->round_cb = round_cb;
		emc->cb_arg = cb_arg;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(tegra20_clk_set_emc_round_callback);

bool tegra20_clk_emc_driver_available(काष्ठा clk_hw *emc_hw)
अणु
	वापस to_tegra_clk_emc(emc_hw)->round_cb != शून्य;
पूर्ण

काष्ठा clk *tegra20_clk_रेजिस्टर_emc(व्योम __iomem *ioaddr, bool low_jitter)
अणु
	काष्ठा tegra_clk_emc *emc;
	काष्ठा clk_init_data init;
	काष्ठा clk *clk;

	emc = kzalloc(माप(*emc), GFP_KERNEL);
	अगर (!emc)
		वापस शून्य;

	/*
	 * EMC stands क्रम External Memory Controller.
	 *
	 * We करोn't want EMC घड़ी to be disabled ever by gating its
	 * parent and whatnot because प्रणाली is busted immediately in that
	 * हाल, hence the घड़ी is marked as critical.
	 */
	init.name = "emc";
	init.ops = &tegra_clk_emc_ops;
	init.flags = CLK_IS_CRITICAL;
	init.parent_names = emc_parent_clk_names;
	init.num_parents = ARRAY_SIZE(emc_parent_clk_names);

	emc->reg = ioaddr;
	emc->hw.init = &init;
	emc->want_low_jitter = low_jitter;

	clk = clk_रेजिस्टर(शून्य, &emc->hw);
	अगर (IS_ERR(clk)) अणु
		kमुक्त(emc);
		वापस शून्य;
	पूर्ण

	वापस clk;
पूर्ण

पूर्णांक tegra20_clk_prepare_emc_mc_same_freq(काष्ठा clk *emc_clk, bool same)
अणु
	काष्ठा tegra_clk_emc *emc;
	काष्ठा clk_hw *hw;

	अगर (!emc_clk)
		वापस -EINVAL;

	hw = __clk_get_hw(emc_clk);
	emc = to_tegra_clk_emc(hw);
	emc->mc_same_freq = same;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(tegra20_clk_prepare_emc_mc_same_freq);
