<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2014 MunकरोReader S.L.
 * Author: Heiko Stuebner <heiko@sntech.de>
 *
 * based on clk/samsung/clk-cpu.c
 * Copyright (c) 2014 Samsung Electronics Co., Ltd.
 * Author: Thomas Abraham <thomas.ab@samsung.com>
 *
 * A CPU घड़ी is defined as a घड़ी supplied to a CPU or a group of CPUs.
 * The CPU घड़ी is typically derived from a hierarchy of घड़ी
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

#समावेश <linux/of.h>
#समावेश <linux/slab.h>
#समावेश <linux/पन.स>
#समावेश <linux/clk.h>
#समावेश <linux/clk-provider.h>
#समावेश "clk.h"

/**
 * काष्ठा rockchip_cpuclk: inक्रमmation about घड़ी supplied to a CPU core.
 * @hw:		handle between ccf and cpu घड़ी.
 * @alt_parent:	alternate parent घड़ी to use when चयनing the speed
 *		of the primary parent घड़ी.
 * @reg_base:	base रेजिस्टर क्रम cpu-घड़ी values.
 * @clk_nb:	घड़ी notअगरier रेजिस्टरed क्रम changes in घड़ी speed of the
 *		primary parent घड़ी.
 * @rate_count:	number of rates in the rate_table
 * @rate_table:	pll-rates and their associated भागiders
 * @reg_data:	cpu-specअगरic रेजिस्टर settings
 * @lock:	घड़ी lock
 */
काष्ठा rockchip_cpuclk अणु
	काष्ठा clk_hw				hw;
	काष्ठा clk				*alt_parent;
	व्योम __iomem				*reg_base;
	काष्ठा notअगरier_block			clk_nb;
	अचिन्हित पूर्णांक				rate_count;
	काष्ठा rockchip_cpuclk_rate_table	*rate_table;
	स्थिर काष्ठा rockchip_cpuclk_reg_data	*reg_data;
	spinlock_t				*lock;
पूर्ण;

#घोषणा to_rockchip_cpuclk_hw(hw) container_of(hw, काष्ठा rockchip_cpuclk, hw)
#घोषणा to_rockchip_cpuclk_nb(nb) \
			container_of(nb, काष्ठा rockchip_cpuclk, clk_nb)

अटल स्थिर काष्ठा rockchip_cpuclk_rate_table *rockchip_get_cpuclk_settings(
			    काष्ठा rockchip_cpuclk *cpuclk, अचिन्हित दीर्घ rate)
अणु
	स्थिर काष्ठा rockchip_cpuclk_rate_table *rate_table =
							cpuclk->rate_table;
	पूर्णांक i;

	क्रम (i = 0; i < cpuclk->rate_count; i++) अणु
		अगर (rate == rate_table[i].prate)
			वापस &rate_table[i];
	पूर्ण

	वापस शून्य;
पूर्ण

अटल अचिन्हित दीर्घ rockchip_cpuclk_recalc_rate(काष्ठा clk_hw *hw,
					अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा rockchip_cpuclk *cpuclk = to_rockchip_cpuclk_hw(hw);
	स्थिर काष्ठा rockchip_cpuclk_reg_data *reg_data = cpuclk->reg_data;
	u32 clksel0 = पढ़ोl_relaxed(cpuclk->reg_base + reg_data->core_reg[0]);

	clksel0 >>= reg_data->भाग_core_shअगरt[0];
	clksel0 &= reg_data->भाग_core_mask[0];
	वापस parent_rate / (clksel0 + 1);
पूर्ण

अटल स्थिर काष्ठा clk_ops rockchip_cpuclk_ops = अणु
	.recalc_rate = rockchip_cpuclk_recalc_rate,
पूर्ण;

अटल व्योम rockchip_cpuclk_set_भागiders(काष्ठा rockchip_cpuclk *cpuclk,
				स्थिर काष्ठा rockchip_cpuclk_rate_table *rate)
अणु
	पूर्णांक i;

	/* alternate parent is active now. set the भागiders */
	क्रम (i = 0; i < ARRAY_SIZE(rate->भागs); i++) अणु
		स्थिर काष्ठा rockchip_cpuclk_clksel *clksel = &rate->भागs[i];

		अगर (!clksel->reg)
			जारी;

		pr_debug("%s: setting reg 0x%x to 0x%x\n",
			 __func__, clksel->reg, clksel->val);
		ग_लिखोl(clksel->val, cpuclk->reg_base + clksel->reg);
	पूर्ण
पूर्ण

अटल पूर्णांक rockchip_cpuclk_pre_rate_change(काष्ठा rockchip_cpuclk *cpuclk,
					   काष्ठा clk_notअगरier_data *ndata)
अणु
	स्थिर काष्ठा rockchip_cpuclk_reg_data *reg_data = cpuclk->reg_data;
	स्थिर काष्ठा rockchip_cpuclk_rate_table *rate;
	अचिन्हित दीर्घ alt_prate, alt_भाग;
	अचिन्हित दीर्घ flags;
	पूर्णांक i = 0;

	/* check validity of the new rate */
	rate = rockchip_get_cpuclk_settings(cpuclk, ndata->new_rate);
	अगर (!rate) अणु
		pr_err("%s: Invalid rate : %lu for cpuclk\n",
		       __func__, ndata->new_rate);
		वापस -EINVAL;
	पूर्ण

	alt_prate = clk_get_rate(cpuclk->alt_parent);

	spin_lock_irqsave(cpuclk->lock, flags);

	/*
	 * If the old parent घड़ी speed is less than the घड़ी speed
	 * of the alternate parent, then it should be ensured that at no poपूर्णांक
	 * the armclk speed is more than the old_rate until the भागiders are
	 * set.
	 */
	अगर (alt_prate > ndata->old_rate) अणु
		/* calculate भागiders */
		alt_भाग =  DIV_ROUND_UP(alt_prate, ndata->old_rate) - 1;
		अगर (alt_भाग > reg_data->भाग_core_mask[0]) अणु
			pr_warn("%s: limiting alt-divider %lu to %d\n",
				__func__, alt_भाग, reg_data->भाग_core_mask[0]);
			alt_भाग = reg_data->भाग_core_mask[0];
		पूर्ण

		/*
		 * Change parents and add भागiders in a single transaction.
		 *
		 * NOTE: we करो this in a single transaction so we're never
		 * भागiding the primary parent by the extra भागiders that were
		 * needed क्रम the alt.
		 */
		pr_debug("%s: setting div %lu as alt-rate %lu > old-rate %lu\n",
			 __func__, alt_भाग, alt_prate, ndata->old_rate);

		क्रम (i = 0; i < reg_data->num_cores; i++) अणु
			ग_लिखोl(HIWORD_UPDATE(alt_भाग, reg_data->भाग_core_mask[i],
					     reg_data->भाग_core_shअगरt[i]),
			       cpuclk->reg_base + reg_data->core_reg[i]);
		पूर्ण
	पूर्ण
	/* select alternate parent */
	ग_लिखोl(HIWORD_UPDATE(reg_data->mux_core_alt,
			     reg_data->mux_core_mask,
			     reg_data->mux_core_shअगरt),
	       cpuclk->reg_base + reg_data->core_reg[0]);

	spin_unlock_irqrestore(cpuclk->lock, flags);
	वापस 0;
पूर्ण

अटल पूर्णांक rockchip_cpuclk_post_rate_change(काष्ठा rockchip_cpuclk *cpuclk,
					    काष्ठा clk_notअगरier_data *ndata)
अणु
	स्थिर काष्ठा rockchip_cpuclk_reg_data *reg_data = cpuclk->reg_data;
	स्थिर काष्ठा rockchip_cpuclk_rate_table *rate;
	अचिन्हित दीर्घ flags;
	पूर्णांक i = 0;

	rate = rockchip_get_cpuclk_settings(cpuclk, ndata->new_rate);
	अगर (!rate) अणु
		pr_err("%s: Invalid rate : %lu for cpuclk\n",
		       __func__, ndata->new_rate);
		वापस -EINVAL;
	पूर्ण

	spin_lock_irqsave(cpuclk->lock, flags);

	अगर (ndata->old_rate < ndata->new_rate)
		rockchip_cpuclk_set_भागiders(cpuclk, rate);

	/*
	 * post-rate change event, re-mux to primary parent and हटाओ भागiders.
	 *
	 * NOTE: we करो this in a single transaction so we're never भागiding the
	 * primary parent by the extra भागiders that were needed क्रम the alt.
	 */

	ग_लिखोl(HIWORD_UPDATE(reg_data->mux_core_मुख्य,
			     reg_data->mux_core_mask,
			     reg_data->mux_core_shअगरt),
	       cpuclk->reg_base + reg_data->core_reg[0]);

	/* हटाओ भागiders */
	क्रम (i = 0; i < reg_data->num_cores; i++) अणु
		ग_लिखोl(HIWORD_UPDATE(0, reg_data->भाग_core_mask[i],
				     reg_data->भाग_core_shअगरt[i]),
		       cpuclk->reg_base + reg_data->core_reg[i]);
	पूर्ण

	अगर (ndata->old_rate > ndata->new_rate)
		rockchip_cpuclk_set_भागiders(cpuclk, rate);

	spin_unlock_irqrestore(cpuclk->lock, flags);
	वापस 0;
पूर्ण

/*
 * This घड़ी notअगरier is called when the frequency of the parent घड़ी
 * of cpuclk is to be changed. This notअगरier handles the setting up all
 * the भागider घड़ीs, remux to temporary parent and handling the safe
 * frequency levels when using temporary parent.
 */
अटल पूर्णांक rockchip_cpuclk_notअगरier_cb(काष्ठा notअगरier_block *nb,
					अचिन्हित दीर्घ event, व्योम *data)
अणु
	काष्ठा clk_notअगरier_data *ndata = data;
	काष्ठा rockchip_cpuclk *cpuclk = to_rockchip_cpuclk_nb(nb);
	पूर्णांक ret = 0;

	pr_debug("%s: event %lu, old_rate %lu, new_rate: %lu\n",
		 __func__, event, ndata->old_rate, ndata->new_rate);
	अगर (event == PRE_RATE_CHANGE)
		ret = rockchip_cpuclk_pre_rate_change(cpuclk, ndata);
	अन्यथा अगर (event == POST_RATE_CHANGE)
		ret = rockchip_cpuclk_post_rate_change(cpuclk, ndata);

	वापस notअगरier_from_त्रुटि_सं(ret);
पूर्ण

काष्ठा clk *rockchip_clk_रेजिस्टर_cpuclk(स्थिर अक्षर *name,
			स्थिर अक्षर *स्थिर *parent_names, u8 num_parents,
			स्थिर काष्ठा rockchip_cpuclk_reg_data *reg_data,
			स्थिर काष्ठा rockchip_cpuclk_rate_table *rates,
			पूर्णांक nrates, व्योम __iomem *reg_base, spinlock_t *lock)
अणु
	काष्ठा rockchip_cpuclk *cpuclk;
	काष्ठा clk_init_data init;
	काष्ठा clk *clk, *cclk;
	पूर्णांक ret;

	अगर (num_parents < 2) अणु
		pr_err("%s: needs at least two parent clocks\n", __func__);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	cpuclk = kzalloc(माप(*cpuclk), GFP_KERNEL);
	अगर (!cpuclk)
		वापस ERR_PTR(-ENOMEM);

	init.name = name;
	init.parent_names = &parent_names[reg_data->mux_core_मुख्य];
	init.num_parents = 1;
	init.ops = &rockchip_cpuclk_ops;

	/* only allow rate changes when we have a rate table */
	init.flags = (nrates > 0) ? CLK_SET_RATE_PARENT : 0;

	/* disallow स्वतःmatic parent changes by ccf */
	init.flags |= CLK_SET_RATE_NO_REPARENT;

	init.flags |= CLK_GET_RATE_NOCACHE;

	cpuclk->reg_base = reg_base;
	cpuclk->lock = lock;
	cpuclk->reg_data = reg_data;
	cpuclk->clk_nb.notअगरier_call = rockchip_cpuclk_notअगरier_cb;
	cpuclk->hw.init = &init;

	cpuclk->alt_parent = __clk_lookup(parent_names[reg_data->mux_core_alt]);
	अगर (!cpuclk->alt_parent) अणु
		pr_err("%s: could not lookup alternate parent: (%d)\n",
		       __func__, reg_data->mux_core_alt);
		ret = -EINVAL;
		जाओ मुक्त_cpuclk;
	पूर्ण

	ret = clk_prepare_enable(cpuclk->alt_parent);
	अगर (ret) अणु
		pr_err("%s: could not enable alternate parent\n",
		       __func__);
		जाओ मुक्त_cpuclk;
	पूर्ण

	clk = __clk_lookup(parent_names[reg_data->mux_core_मुख्य]);
	अगर (!clk) अणु
		pr_err("%s: could not lookup parent clock: (%d) %s\n",
		       __func__, reg_data->mux_core_मुख्य,
		       parent_names[reg_data->mux_core_मुख्य]);
		ret = -EINVAL;
		जाओ मुक्त_alt_parent;
	पूर्ण

	ret = clk_notअगरier_रेजिस्टर(clk, &cpuclk->clk_nb);
	अगर (ret) अणु
		pr_err("%s: failed to register clock notifier for %s\n",
				__func__, name);
		जाओ मुक्त_alt_parent;
	पूर्ण

	अगर (nrates > 0) अणु
		cpuclk->rate_count = nrates;
		cpuclk->rate_table = kmemdup(rates,
					     माप(*rates) * nrates,
					     GFP_KERNEL);
		अगर (!cpuclk->rate_table) अणु
			ret = -ENOMEM;
			जाओ unरेजिस्टर_notअगरier;
		पूर्ण
	पूर्ण

	cclk = clk_रेजिस्टर(शून्य, &cpuclk->hw);
	अगर (IS_ERR(cclk)) अणु
		pr_err("%s: could not register cpuclk %s\n", __func__,	name);
		ret = PTR_ERR(cclk);
		जाओ मुक्त_rate_table;
	पूर्ण

	वापस cclk;

मुक्त_rate_table:
	kमुक्त(cpuclk->rate_table);
unरेजिस्टर_notअगरier:
	clk_notअगरier_unरेजिस्टर(clk, &cpuclk->clk_nb);
मुक्त_alt_parent:
	clk_disable_unprepare(cpuclk->alt_parent);
मुक्त_cpuclk:
	kमुक्त(cpuclk);
	वापस ERR_PTR(ret);
पूर्ण
