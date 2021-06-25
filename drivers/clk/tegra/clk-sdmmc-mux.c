<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2018 NVIDIA CORPORATION.  All rights reserved.
 *
 * based on clk-mux.c
 *
 * Copyright (C) 2011 Sascha Hauer, Pengutronix <s.hauer@pengutronix.de>
 * Copyright (C) 2011 Riअक्षरd Zhao, Linaro <riअक्षरd.zhao@linaro.org>
 * Copyright (C) 2011-2012 Mike Turquette, Linaro Ltd <mturquette@linaro.org>
 *
 */

#समावेश <linux/clk-provider.h>
#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/types.h>

#समावेश "clk.h"

#घोषणा DIV_MASK GENMASK(7, 0)
#घोषणा MUX_SHIFT 29
#घोषणा MUX_MASK GENMASK(MUX_SHIFT + 2, MUX_SHIFT)
#घोषणा SDMMC_MUL 2

#घोषणा get_max_भाग(d) DIV_MASK
#घोषणा get_भाग_field(val) ((val) & DIV_MASK)
#घोषणा get_mux_field(val) (((val) & MUX_MASK) >> MUX_SHIFT)

अटल स्थिर अक्षर * स्थिर mux_sdmmc_parents[] = अणु
	"pll_p", "pll_c4_out2", "pll_c4_out0", "pll_c4_out1", "clk_m"
पूर्ण;

अटल स्थिर u8 mux_lj_idx[] = अणु
	[0] = 0, [1] = 1, [2] = 2, [3] = 5, [4] = 6
पूर्ण;

अटल स्थिर u8 mux_non_lj_idx[] = अणु
	[0] = 0, [1] = 3, [2] = 7, [3] = 4, [4] = 6
पूर्ण;

अटल u8 clk_sdmmc_mux_get_parent(काष्ठा clk_hw *hw)
अणु
	काष्ठा tegra_sdmmc_mux *sdmmc_mux = to_clk_sdmmc_mux(hw);
	पूर्णांक num_parents, i;
	u32 src, val;
	स्थिर u8 *mux_idx;

	num_parents = clk_hw_get_num_parents(hw);

	val = पढ़ोl_relaxed(sdmmc_mux->reg);
	src = get_mux_field(val);
	अगर (get_भाग_field(val))
		mux_idx = mux_non_lj_idx;
	अन्यथा
		mux_idx = mux_lj_idx;

	क्रम (i = 0; i < num_parents; i++) अणु
		अगर (mux_idx[i] == src)
			वापस i;
	पूर्ण

	WARN(1, "Unknown parent selector %d\n", src);

	वापस 0;
पूर्ण

अटल पूर्णांक clk_sdmmc_mux_set_parent(काष्ठा clk_hw *hw, u8 index)
अणु
	काष्ठा tegra_sdmmc_mux *sdmmc_mux = to_clk_sdmmc_mux(hw);
	u32 val;


	val = पढ़ोl_relaxed(sdmmc_mux->reg);
	अगर (get_भाग_field(val))
		index = mux_non_lj_idx[index];
	अन्यथा
		index = mux_lj_idx[index];

	val &= ~MUX_MASK;
	val |= index << MUX_SHIFT;

	ग_लिखोl(val, sdmmc_mux->reg);

	वापस 0;
पूर्ण

अटल अचिन्हित दीर्घ clk_sdmmc_mux_recalc_rate(काष्ठा clk_hw *hw,
					       अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा tegra_sdmmc_mux *sdmmc_mux = to_clk_sdmmc_mux(hw);
	u32 val;
	पूर्णांक भाग;
	u64 rate = parent_rate;

	val = पढ़ोl_relaxed(sdmmc_mux->reg);
	भाग = get_भाग_field(val);

	भाग += SDMMC_MUL;

	rate *= SDMMC_MUL;
	rate += भाग - 1;
	करो_भाग(rate, भाग);

	वापस rate;
पूर्ण

अटल पूर्णांक clk_sdmmc_mux_determine_rate(काष्ठा clk_hw *hw,
					काष्ठा clk_rate_request *req)
अणु
	काष्ठा tegra_sdmmc_mux *sdmmc_mux = to_clk_sdmmc_mux(hw);
	पूर्णांक भाग;
	अचिन्हित दीर्घ output_rate = req->best_parent_rate;

	req->rate = max(req->rate, req->min_rate);
	req->rate = min(req->rate, req->max_rate);

	अगर (!req->rate)
		वापस output_rate;

	भाग = भाग_frac_get(req->rate, output_rate, 8, 1, sdmmc_mux->भाग_flags);
	अगर (भाग < 0)
		भाग = 0;

	अगर (sdmmc_mux->भाग_flags & TEGRA_DIVIDER_ROUND_UP)
		req->rate =  DIV_ROUND_UP(output_rate * SDMMC_MUL,
					  भाग + SDMMC_MUL);
	अन्यथा
		req->rate =  output_rate * SDMMC_MUL / (भाग + SDMMC_MUL);

	वापस 0;
पूर्ण

अटल पूर्णांक clk_sdmmc_mux_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				  अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा tegra_sdmmc_mux *sdmmc_mux = to_clk_sdmmc_mux(hw);
	पूर्णांक भाग;
	अचिन्हित दीर्घ flags = 0;
	u32 val;
	u8 src;

	भाग = भाग_frac_get(rate, parent_rate, 8, 1, sdmmc_mux->भाग_flags);
	अगर (भाग < 0)
		वापस भाग;

	अगर (sdmmc_mux->lock)
		spin_lock_irqsave(sdmmc_mux->lock, flags);

	src = clk_sdmmc_mux_get_parent(hw);
	अगर (भाग)
		src = mux_non_lj_idx[src];
	अन्यथा
		src = mux_lj_idx[src];

	val = src << MUX_SHIFT;
	val |= भाग;
	ग_लिखोl(val, sdmmc_mux->reg);
	fence_udelay(2, sdmmc_mux->reg);

	अगर (sdmmc_mux->lock)
		spin_unlock_irqrestore(sdmmc_mux->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक clk_sdmmc_mux_is_enabled(काष्ठा clk_hw *hw)
अणु
	काष्ठा tegra_sdmmc_mux *sdmmc_mux = to_clk_sdmmc_mux(hw);
	स्थिर काष्ठा clk_ops *gate_ops = sdmmc_mux->gate_ops;
	काष्ठा clk_hw *gate_hw = &sdmmc_mux->gate.hw;

	__clk_hw_set_clk(gate_hw, hw);

	वापस gate_ops->is_enabled(gate_hw);
पूर्ण

अटल पूर्णांक clk_sdmmc_mux_enable(काष्ठा clk_hw *hw)
अणु
	काष्ठा tegra_sdmmc_mux *sdmmc_mux = to_clk_sdmmc_mux(hw);
	स्थिर काष्ठा clk_ops *gate_ops = sdmmc_mux->gate_ops;
	काष्ठा clk_hw *gate_hw = &sdmmc_mux->gate.hw;

	__clk_hw_set_clk(gate_hw, hw);

	वापस gate_ops->enable(gate_hw);
पूर्ण

अटल व्योम clk_sdmmc_mux_disable(काष्ठा clk_hw *hw)
अणु
	काष्ठा tegra_sdmmc_mux *sdmmc_mux = to_clk_sdmmc_mux(hw);
	स्थिर काष्ठा clk_ops *gate_ops = sdmmc_mux->gate_ops;
	काष्ठा clk_hw *gate_hw = &sdmmc_mux->gate.hw;

	gate_ops->disable(gate_hw);
पूर्ण

अटल व्योम clk_sdmmc_mux_restore_context(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_hw *parent = clk_hw_get_parent(hw);
	अचिन्हित दीर्घ parent_rate = clk_hw_get_rate(parent);
	अचिन्हित दीर्घ rate = clk_hw_get_rate(hw);
	पूर्णांक parent_id;

	parent_id = clk_hw_get_parent_index(hw);
	अगर (WARN_ON(parent_id < 0))
		वापस;

	clk_sdmmc_mux_set_parent(hw, parent_id);
	clk_sdmmc_mux_set_rate(hw, rate, parent_rate);
पूर्ण

अटल स्थिर काष्ठा clk_ops tegra_clk_sdmmc_mux_ops = अणु
	.get_parent = clk_sdmmc_mux_get_parent,
	.set_parent = clk_sdmmc_mux_set_parent,
	.determine_rate = clk_sdmmc_mux_determine_rate,
	.recalc_rate = clk_sdmmc_mux_recalc_rate,
	.set_rate = clk_sdmmc_mux_set_rate,
	.is_enabled = clk_sdmmc_mux_is_enabled,
	.enable = clk_sdmmc_mux_enable,
	.disable = clk_sdmmc_mux_disable,
	.restore_context = clk_sdmmc_mux_restore_context,
पूर्ण;

काष्ठा clk *tegra_clk_रेजिस्टर_sdmmc_mux_भाग(स्थिर अक्षर *name,
	व्योम __iomem *clk_base, u32 offset, u32 clk_num, u8 भाग_flags,
	अचिन्हित दीर्घ flags, व्योम *lock)
अणु
	काष्ठा clk *clk;
	काष्ठा clk_init_data init;
	स्थिर काष्ठा tegra_clk_periph_regs *bank;
	काष्ठा tegra_sdmmc_mux *sdmmc_mux;

	init.ops = &tegra_clk_sdmmc_mux_ops;
	init.name = name;
	init.flags = flags;
	init.parent_names = mux_sdmmc_parents;
	init.num_parents = ARRAY_SIZE(mux_sdmmc_parents);

	bank = get_reg_bank(clk_num);
	अगर (!bank)
		वापस ERR_PTR(-EINVAL);

	sdmmc_mux = kzalloc(माप(*sdmmc_mux), GFP_KERNEL);
	अगर (!sdmmc_mux)
		वापस ERR_PTR(-ENOMEM);

	/* Data in .init is copied by clk_रेजिस्टर(), so stack variable OK */
	sdmmc_mux->hw.init = &init;
	sdmmc_mux->reg = clk_base + offset;
	sdmmc_mux->lock = lock;
	sdmmc_mux->gate.clk_base = clk_base;
	sdmmc_mux->gate.regs = bank;
	sdmmc_mux->gate.enable_refcnt = periph_clk_enb_refcnt;
	sdmmc_mux->gate.clk_num = clk_num;
	sdmmc_mux->gate.flags = TEGRA_PERIPH_ON_APB;
	sdmmc_mux->भाग_flags = भाग_flags;
	sdmmc_mux->gate_ops = &tegra_clk_periph_gate_ops;

	clk = clk_रेजिस्टर(शून्य, &sdmmc_mux->hw);
	अगर (IS_ERR(clk)) अणु
		kमुक्त(sdmmc_mux);
		वापस clk;
	पूर्ण

	sdmmc_mux->gate.hw.clk = clk;

	वापस clk;
पूर्ण
