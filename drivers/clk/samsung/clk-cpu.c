<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2014 Samsung Electronics Co., Ltd.
 * Author: Thomas Abraham <thomas.ab@samsung.com>
 *
 * Copyright (c) 2015 Samsung Electronics Co., Ltd.
 * Bartlomiej Zolnierkiewicz <b.zolnierkie@samsung.com>
 *
 * This file contains the utility function to रेजिस्टर CPU घड़ी क्रम Samsung
 * Exynos platक्रमms. A CPU घड़ी is defined as a घड़ी supplied to a CPU or a
 * group of CPUs. The CPU घड़ी is typically derived from a hierarchy of घड़ी
 * blocks which includes mux and भागider blocks. There are a number of other
 * auxiliary घड़ीs supplied to the CPU करोमुख्य such as the debug blocks and AXI
 * घड़ी क्रम CPU करोमुख्य. The rates of these auxiliary घड़ीs are related to the
 * CPU घड़ी rate and this relation is usually specअगरied in the hardware manual
 * of the SoC or supplied after the SoC अक्षरacterization.
 *
 * The below implementation of the CPU घड़ी allows the rate changes of the CPU
 * घड़ी and the corresponding rate changes of the auxillary घड़ीs of the CPU
 * करोमुख्य. The platक्रमm घड़ी driver provides a घड़ी रेजिस्टर configuration
 * क्रम each configurable rate which is then used to program the घड़ी hardware
 * रेजिस्टरs to acheive a fast co-oridinated rate change क्रम all the CPU करोमुख्य
 * घड़ीs.
 *
 * On a rate change request क्रम the CPU घड़ी, the rate change is propagated
 * upto the PLL supplying the घड़ी to the CPU करोमुख्य घड़ी blocks. While the
 * CPU करोमुख्य PLL is reconfigured, the CPU करोमुख्य घड़ीs are driven using an
 * alternate घड़ी source. If required, the alternate घड़ी source is भागided
 * करोwn in order to keep the output घड़ी rate within the previous OPP limits.
*/

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/पन.स>
#समावेश <linux/slab.h>
#समावेश <linux/clk.h>
#समावेश <linux/clk-provider.h>
#समावेश "clk-cpu.h"

#घोषणा E4210_SRC_CPU		0x0
#घोषणा E4210_STAT_CPU		0x200
#घोषणा E4210_DIV_CPU0		0x300
#घोषणा E4210_DIV_CPU1		0x304
#घोषणा E4210_DIV_STAT_CPU0	0x400
#घोषणा E4210_DIV_STAT_CPU1	0x404

#घोषणा E5433_MUX_SEL2		0x008
#घोषणा E5433_MUX_STAT2		0x208
#घोषणा E5433_DIV_CPU0		0x400
#घोषणा E5433_DIV_CPU1		0x404
#घोषणा E5433_DIV_STAT_CPU0	0x500
#घोषणा E5433_DIV_STAT_CPU1	0x504

#घोषणा E4210_DIV0_RATIO0_MASK	0x7
#घोषणा E4210_DIV1_HPM_MASK	(0x7 << 4)
#घोषणा E4210_DIV1_COPY_MASK	(0x7 << 0)
#घोषणा E4210_MUX_HPM_MASK	(1 << 20)
#घोषणा E4210_DIV0_ATB_SHIFT	16
#घोषणा E4210_DIV0_ATB_MASK	(DIV_MASK << E4210_DIV0_ATB_SHIFT)

#घोषणा MAX_DIV			8
#घोषणा DIV_MASK		7
#घोषणा DIV_MASK_ALL		0xffffffff
#घोषणा MUX_MASK		7

/*
 * Helper function to रुको until भागider(s) have stabilized after the भागider
 * value has changed.
 */
अटल व्योम रुको_until_भागider_stable(व्योम __iomem *भाग_reg, अचिन्हित दीर्घ mask)
अणु
	अचिन्हित दीर्घ समयout = jअगरfies + msecs_to_jअगरfies(10);

	करो अणु
		अगर (!(पढ़ोl(भाग_reg) & mask))
			वापस;
	पूर्ण जबतक (समय_beक्रमe(jअगरfies, समयout));

	अगर (!(पढ़ोl(भाग_reg) & mask))
		वापस;

	pr_err("%s: timeout in divider stablization\n", __func__);
पूर्ण

/*
 * Helper function to रुको until mux has stabilized after the mux selection
 * value was changed.
 */
अटल व्योम रुको_until_mux_stable(व्योम __iomem *mux_reg, u32 mux_pos,
					अचिन्हित दीर्घ mux_value)
अणु
	अचिन्हित दीर्घ समयout = jअगरfies + msecs_to_jअगरfies(10);

	करो अणु
		अगर (((पढ़ोl(mux_reg) >> mux_pos) & MUX_MASK) == mux_value)
			वापस;
	पूर्ण जबतक (समय_beक्रमe(jअगरfies, समयout));

	अगर (((पढ़ोl(mux_reg) >> mux_pos) & MUX_MASK) == mux_value)
		वापस;

	pr_err("%s: re-parenting mux timed-out\n", __func__);
पूर्ण

/* common round rate callback useable क्रम all types of CPU घड़ीs */
अटल दीर्घ exynos_cpuclk_round_rate(काष्ठा clk_hw *hw,
			अचिन्हित दीर्घ drate, अचिन्हित दीर्घ *prate)
अणु
	काष्ठा clk_hw *parent = clk_hw_get_parent(hw);
	*prate = clk_hw_round_rate(parent, drate);
	वापस *prate;
पूर्ण

/* common recalc rate callback useable क्रम all types of CPU घड़ीs */
अटल अचिन्हित दीर्घ exynos_cpuclk_recalc_rate(काष्ठा clk_hw *hw,
			अचिन्हित दीर्घ parent_rate)
अणु
	/*
	 * The CPU घड़ी output (armclk) rate is the same as its parent
	 * rate. Although there exist certain भागiders inside the CPU
	 * घड़ी block that could be used to भागide the parent घड़ी,
	 * the driver करोes not make use of them currently, except during
	 * frequency transitions.
	 */
	वापस parent_rate;
पूर्ण

अटल स्थिर काष्ठा clk_ops exynos_cpuclk_clk_ops = अणु
	.recalc_rate = exynos_cpuclk_recalc_rate,
	.round_rate = exynos_cpuclk_round_rate,
पूर्ण;

/*
 * Helper function to set the 'safe' भागiders क्रम the CPU घड़ी. The parameters
 * भाग and mask contain the भागider value and the रेजिस्टर bit mask of the
 * भागiders to be programmed.
 */
अटल व्योम exynos_set_safe_भाग(व्योम __iomem *base, अचिन्हित दीर्घ भाग,
					अचिन्हित दीर्घ mask)
अणु
	अचिन्हित दीर्घ भाग0;

	भाग0 = पढ़ोl(base + E4210_DIV_CPU0);
	भाग0 = (भाग0 & ~mask) | (भाग & mask);
	ग_लिखोl(भाग0, base + E4210_DIV_CPU0);
	रुको_until_भागider_stable(base + E4210_DIV_STAT_CPU0, mask);
पूर्ण

/* handler क्रम pre-rate change notअगरication from parent घड़ी */
अटल पूर्णांक exynos_cpuclk_pre_rate_change(काष्ठा clk_notअगरier_data *ndata,
			काष्ठा exynos_cpuclk *cpuclk, व्योम __iomem *base)
अणु
	स्थिर काष्ठा exynos_cpuclk_cfg_data *cfg_data = cpuclk->cfg;
	अचिन्हित दीर्घ alt_prate = clk_hw_get_rate(cpuclk->alt_parent);
	अचिन्हित दीर्घ alt_भाग = 0, alt_भाग_mask = DIV_MASK;
	अचिन्हित दीर्घ भाग0, भाग1 = 0, mux_reg;
	अचिन्हित दीर्घ flags;

	/* find out the भागider values to use क्रम घड़ी data */
	जबतक ((cfg_data->prate * 1000) != ndata->new_rate) अणु
		अगर (cfg_data->prate == 0)
			वापस -EINVAL;
		cfg_data++;
	पूर्ण

	spin_lock_irqsave(cpuclk->lock, flags);

	/*
	 * For the selected PLL घड़ी frequency, get the pre-defined भागider
	 * values. If the घड़ी क्रम sclk_hpm is not sourced from apll, then
	 * the values क्रम DIV_COPY and DIV_HPM भागiders need not be set.
	 */
	भाग0 = cfg_data->भाग0;
	अगर (cpuclk->flags & CLK_CPU_HAS_DIV1) अणु
		भाग1 = cfg_data->भाग1;
		अगर (पढ़ोl(base + E4210_SRC_CPU) & E4210_MUX_HPM_MASK)
			भाग1 = पढ़ोl(base + E4210_DIV_CPU1) &
				(E4210_DIV1_HPM_MASK | E4210_DIV1_COPY_MASK);
	पूर्ण

	/*
	 * If the old parent घड़ी speed is less than the घड़ी speed of
	 * the alternate parent, then it should be ensured that at no poपूर्णांक
	 * the armclk speed is more than the old_prate until the भागiders are
	 * set.  Also workaround the issue of the भागiders being set to lower
	 * values beक्रमe the parent घड़ी speed is set to new lower speed
	 * (this can result in too high speed of armclk output घड़ीs).
	 */
	अगर (alt_prate > ndata->old_rate || ndata->old_rate > ndata->new_rate) अणु
		अचिन्हित दीर्घ पंचांगp_rate = min(ndata->old_rate, ndata->new_rate);

		alt_भाग = DIV_ROUND_UP(alt_prate, पंचांगp_rate) - 1;
		WARN_ON(alt_भाग >= MAX_DIV);

		अगर (cpuclk->flags & CLK_CPU_NEEDS_DEBUG_ALT_DIV) अणु
			/*
			 * In Exynos4210, ATB घड़ी parent is also mout_core. So
			 * ATB घड़ी also needs to be mantained at safe speed.
			 */
			alt_भाग |= E4210_DIV0_ATB_MASK;
			alt_भाग_mask |= E4210_DIV0_ATB_MASK;
		पूर्ण
		exynos_set_safe_भाग(base, alt_भाग, alt_भाग_mask);
		भाग0 |= alt_भाग;
	पूर्ण

	/* select sclk_mpll as the alternate parent */
	mux_reg = पढ़ोl(base + E4210_SRC_CPU);
	ग_लिखोl(mux_reg | (1 << 16), base + E4210_SRC_CPU);
	रुको_until_mux_stable(base + E4210_STAT_CPU, 16, 2);

	/* alternate parent is active now. set the भागiders */
	ग_लिखोl(भाग0, base + E4210_DIV_CPU0);
	रुको_until_भागider_stable(base + E4210_DIV_STAT_CPU0, DIV_MASK_ALL);

	अगर (cpuclk->flags & CLK_CPU_HAS_DIV1) अणु
		ग_लिखोl(भाग1, base + E4210_DIV_CPU1);
		रुको_until_भागider_stable(base + E4210_DIV_STAT_CPU1,
				DIV_MASK_ALL);
	पूर्ण

	spin_unlock_irqrestore(cpuclk->lock, flags);
	वापस 0;
पूर्ण

/* handler क्रम post-rate change notअगरication from parent घड़ी */
अटल पूर्णांक exynos_cpuclk_post_rate_change(काष्ठा clk_notअगरier_data *ndata,
			काष्ठा exynos_cpuclk *cpuclk, व्योम __iomem *base)
अणु
	स्थिर काष्ठा exynos_cpuclk_cfg_data *cfg_data = cpuclk->cfg;
	अचिन्हित दीर्घ भाग = 0, भाग_mask = DIV_MASK;
	अचिन्हित दीर्घ mux_reg;
	अचिन्हित दीर्घ flags;

	/* find out the भागider values to use क्रम घड़ी data */
	अगर (cpuclk->flags & CLK_CPU_NEEDS_DEBUG_ALT_DIV) अणु
		जबतक ((cfg_data->prate * 1000) != ndata->new_rate) अणु
			अगर (cfg_data->prate == 0)
				वापस -EINVAL;
			cfg_data++;
		पूर्ण
	पूर्ण

	spin_lock_irqsave(cpuclk->lock, flags);

	/* select mout_apll as the alternate parent */
	mux_reg = पढ़ोl(base + E4210_SRC_CPU);
	ग_लिखोl(mux_reg & ~(1 << 16), base + E4210_SRC_CPU);
	रुको_until_mux_stable(base + E4210_STAT_CPU, 16, 1);

	अगर (cpuclk->flags & CLK_CPU_NEEDS_DEBUG_ALT_DIV) अणु
		भाग |= (cfg_data->भाग0 & E4210_DIV0_ATB_MASK);
		भाग_mask |= E4210_DIV0_ATB_MASK;
	पूर्ण

	exynos_set_safe_भाग(base, भाग, भाग_mask);
	spin_unlock_irqrestore(cpuclk->lock, flags);
	वापस 0;
पूर्ण

/*
 * Helper function to set the 'safe' भागiders क्रम the CPU घड़ी. The parameters
 * भाग and mask contain the भागider value and the रेजिस्टर bit mask of the
 * भागiders to be programmed.
 */
अटल व्योम exynos5433_set_safe_भाग(व्योम __iomem *base, अचिन्हित दीर्घ भाग,
					अचिन्हित दीर्घ mask)
अणु
	अचिन्हित दीर्घ भाग0;

	भाग0 = पढ़ोl(base + E5433_DIV_CPU0);
	भाग0 = (भाग0 & ~mask) | (भाग & mask);
	ग_लिखोl(भाग0, base + E5433_DIV_CPU0);
	रुको_until_भागider_stable(base + E5433_DIV_STAT_CPU0, mask);
पूर्ण

/* handler क्रम pre-rate change notअगरication from parent घड़ी */
अटल पूर्णांक exynos5433_cpuclk_pre_rate_change(काष्ठा clk_notअगरier_data *ndata,
			काष्ठा exynos_cpuclk *cpuclk, व्योम __iomem *base)
अणु
	स्थिर काष्ठा exynos_cpuclk_cfg_data *cfg_data = cpuclk->cfg;
	अचिन्हित दीर्घ alt_prate = clk_hw_get_rate(cpuclk->alt_parent);
	अचिन्हित दीर्घ alt_भाग = 0, alt_भाग_mask = DIV_MASK;
	अचिन्हित दीर्घ भाग0, भाग1 = 0, mux_reg;
	अचिन्हित दीर्घ flags;

	/* find out the भागider values to use क्रम घड़ी data */
	जबतक ((cfg_data->prate * 1000) != ndata->new_rate) अणु
		अगर (cfg_data->prate == 0)
			वापस -EINVAL;
		cfg_data++;
	पूर्ण

	spin_lock_irqsave(cpuclk->lock, flags);

	/*
	 * For the selected PLL घड़ी frequency, get the pre-defined भागider
	 * values.
	 */
	भाग0 = cfg_data->भाग0;
	भाग1 = cfg_data->भाग1;

	/*
	 * If the old parent घड़ी speed is less than the घड़ी speed of
	 * the alternate parent, then it should be ensured that at no poपूर्णांक
	 * the armclk speed is more than the old_prate until the भागiders are
	 * set.  Also workaround the issue of the भागiders being set to lower
	 * values beक्रमe the parent घड़ी speed is set to new lower speed
	 * (this can result in too high speed of armclk output घड़ीs).
	 */
	अगर (alt_prate > ndata->old_rate || ndata->old_rate > ndata->new_rate) अणु
		अचिन्हित दीर्घ पंचांगp_rate = min(ndata->old_rate, ndata->new_rate);

		alt_भाग = DIV_ROUND_UP(alt_prate, पंचांगp_rate) - 1;
		WARN_ON(alt_भाग >= MAX_DIV);

		exynos5433_set_safe_भाग(base, alt_भाग, alt_भाग_mask);
		भाग0 |= alt_भाग;
	पूर्ण

	/* select the alternate parent */
	mux_reg = पढ़ोl(base + E5433_MUX_SEL2);
	ग_लिखोl(mux_reg | 1, base + E5433_MUX_SEL2);
	रुको_until_mux_stable(base + E5433_MUX_STAT2, 0, 2);

	/* alternate parent is active now. set the भागiders */
	ग_लिखोl(भाग0, base + E5433_DIV_CPU0);
	रुको_until_भागider_stable(base + E5433_DIV_STAT_CPU0, DIV_MASK_ALL);

	ग_लिखोl(भाग1, base + E5433_DIV_CPU1);
	रुको_until_भागider_stable(base + E5433_DIV_STAT_CPU1, DIV_MASK_ALL);

	spin_unlock_irqrestore(cpuclk->lock, flags);
	वापस 0;
पूर्ण

/* handler क्रम post-rate change notअगरication from parent घड़ी */
अटल पूर्णांक exynos5433_cpuclk_post_rate_change(काष्ठा clk_notअगरier_data *ndata,
			काष्ठा exynos_cpuclk *cpuclk, व्योम __iomem *base)
अणु
	अचिन्हित दीर्घ भाग = 0, भाग_mask = DIV_MASK;
	अचिन्हित दीर्घ mux_reg;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(cpuclk->lock, flags);

	/* select apll as the alternate parent */
	mux_reg = पढ़ोl(base + E5433_MUX_SEL2);
	ग_लिखोl(mux_reg & ~1, base + E5433_MUX_SEL2);
	रुको_until_mux_stable(base + E5433_MUX_STAT2, 0, 1);

	exynos5433_set_safe_भाग(base, भाग, भाग_mask);
	spin_unlock_irqrestore(cpuclk->lock, flags);
	वापस 0;
पूर्ण

/*
 * This notअगरier function is called क्रम the pre-rate and post-rate change
 * notअगरications of the parent घड़ी of cpuclk.
 */
अटल पूर्णांक exynos_cpuclk_notअगरier_cb(काष्ठा notअगरier_block *nb,
				अचिन्हित दीर्घ event, व्योम *data)
अणु
	काष्ठा clk_notअगरier_data *ndata = data;
	काष्ठा exynos_cpuclk *cpuclk;
	व्योम __iomem *base;
	पूर्णांक err = 0;

	cpuclk = container_of(nb, काष्ठा exynos_cpuclk, clk_nb);
	base = cpuclk->ctrl_base;

	अगर (event == PRE_RATE_CHANGE)
		err = exynos_cpuclk_pre_rate_change(ndata, cpuclk, base);
	अन्यथा अगर (event == POST_RATE_CHANGE)
		err = exynos_cpuclk_post_rate_change(ndata, cpuclk, base);

	वापस notअगरier_from_त्रुटि_सं(err);
पूर्ण

/*
 * This notअगरier function is called क्रम the pre-rate and post-rate change
 * notअगरications of the parent घड़ी of cpuclk.
 */
अटल पूर्णांक exynos5433_cpuclk_notअगरier_cb(काष्ठा notअगरier_block *nb,
				अचिन्हित दीर्घ event, व्योम *data)
अणु
	काष्ठा clk_notअगरier_data *ndata = data;
	काष्ठा exynos_cpuclk *cpuclk;
	व्योम __iomem *base;
	पूर्णांक err = 0;

	cpuclk = container_of(nb, काष्ठा exynos_cpuclk, clk_nb);
	base = cpuclk->ctrl_base;

	अगर (event == PRE_RATE_CHANGE)
		err = exynos5433_cpuclk_pre_rate_change(ndata, cpuclk, base);
	अन्यथा अगर (event == POST_RATE_CHANGE)
		err = exynos5433_cpuclk_post_rate_change(ndata, cpuclk, base);

	वापस notअगरier_from_त्रुटि_सं(err);
पूर्ण

/* helper function to रेजिस्टर a CPU घड़ी */
पूर्णांक __init exynos_रेजिस्टर_cpu_घड़ी(काष्ठा samsung_clk_provider *ctx,
		अचिन्हित पूर्णांक lookup_id, स्थिर अक्षर *name,
		स्थिर काष्ठा clk_hw *parent, स्थिर काष्ठा clk_hw *alt_parent,
		अचिन्हित दीर्घ offset, स्थिर काष्ठा exynos_cpuclk_cfg_data *cfg,
		अचिन्हित दीर्घ num_cfgs, अचिन्हित दीर्घ flags)
अणु
	काष्ठा exynos_cpuclk *cpuclk;
	काष्ठा clk_init_data init;
	स्थिर अक्षर *parent_name;
	पूर्णांक ret = 0;

	अगर (IS_ERR(parent) || IS_ERR(alt_parent)) अणु
		pr_err("%s: invalid parent clock(s)\n", __func__);
		वापस -EINVAL;
	पूर्ण

	cpuclk = kzalloc(माप(*cpuclk), GFP_KERNEL);
	अगर (!cpuclk)
		वापस -ENOMEM;

	parent_name = clk_hw_get_name(parent);

	init.name = name;
	init.flags = CLK_SET_RATE_PARENT;
	init.parent_names = &parent_name;
	init.num_parents = 1;
	init.ops = &exynos_cpuclk_clk_ops;

	cpuclk->alt_parent = alt_parent;
	cpuclk->hw.init = &init;
	cpuclk->ctrl_base = ctx->reg_base + offset;
	cpuclk->lock = &ctx->lock;
	cpuclk->flags = flags;
	अगर (flags & CLK_CPU_HAS_E5433_REGS_LAYOUT)
		cpuclk->clk_nb.notअगरier_call = exynos5433_cpuclk_notअगरier_cb;
	अन्यथा
		cpuclk->clk_nb.notअगरier_call = exynos_cpuclk_notअगरier_cb;


	ret = clk_notअगरier_रेजिस्टर(parent->clk, &cpuclk->clk_nb);
	अगर (ret) अणु
		pr_err("%s: failed to register clock notifier for %s\n",
				__func__, name);
		जाओ मुक्त_cpuclk;
	पूर्ण

	cpuclk->cfg = kmemdup(cfg, माप(*cfg) * num_cfgs, GFP_KERNEL);
	अगर (!cpuclk->cfg) अणु
		ret = -ENOMEM;
		जाओ unरेजिस्टर_clk_nb;
	पूर्ण

	ret = clk_hw_रेजिस्टर(शून्य, &cpuclk->hw);
	अगर (ret) अणु
		pr_err("%s: could not register cpuclk %s\n", __func__,	name);
		जाओ मुक्त_cpuclk_data;
	पूर्ण

	samsung_clk_add_lookup(ctx, &cpuclk->hw, lookup_id);
	वापस 0;

मुक्त_cpuclk_data:
	kमुक्त(cpuclk->cfg);
unरेजिस्टर_clk_nb:
	clk_notअगरier_unरेजिस्टर(parent->clk, &cpuclk->clk_nb);
मुक्त_cpuclk:
	kमुक्त(cpuclk);
	वापस ret;
पूर्ण
