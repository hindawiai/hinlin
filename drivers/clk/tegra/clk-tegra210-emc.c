<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2015-2020, NVIDIA CORPORATION.  All rights reserved.
 */

#समावेश <linux/bitfield.h>
#समावेश <linux/clk.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/clk/tegra.h>
#समावेश <linux/device.h>
#समावेश <linux/module.h>
#समावेश <linux/पन.स>
#समावेश <linux/slab.h>

#समावेश "clk.h"

#घोषणा CLK_SOURCE_EMC 0x19c
#घोषणा  CLK_SOURCE_EMC_2X_CLK_SRC GENMASK(31, 29)
#घोषणा  CLK_SOURCE_EMC_MC_EMC_SAME_FREQ BIT(16)
#घोषणा  CLK_SOURCE_EMC_2X_CLK_DIVISOR GENMASK(7, 0)

#घोषणा CLK_SRC_PLLM 0
#घोषणा CLK_SRC_PLLC 1
#घोषणा CLK_SRC_PLLP 2
#घोषणा CLK_SRC_CLK_M 3
#घोषणा CLK_SRC_PLLM_UD 4
#घोषणा CLK_SRC_PLLMB_UD 5
#घोषणा CLK_SRC_PLLMB 6
#घोषणा CLK_SRC_PLLP_UD 7

काष्ठा tegra210_clk_emc अणु
	काष्ठा clk_hw hw;
	व्योम __iomem *regs;

	काष्ठा tegra210_clk_emc_provider *provider;

	काष्ठा clk *parents[8];
पूर्ण;

अटल अंतरभूत काष्ठा tegra210_clk_emc *
to_tegra210_clk_emc(काष्ठा clk_hw *hw)
अणु
	वापस container_of(hw, काष्ठा tegra210_clk_emc, hw);
पूर्ण

अटल स्थिर अक्षर *tegra210_clk_emc_parents[] = अणु
	"pll_m", "pll_c", "pll_p", "clk_m", "pll_m_ud", "pll_mb_ud",
	"pll_mb", "pll_p_ud",
पूर्ण;

अटल u8 tegra210_clk_emc_get_parent(काष्ठा clk_hw *hw)
अणु
	काष्ठा tegra210_clk_emc *emc = to_tegra210_clk_emc(hw);
	u32 value;
	u8 src;

	value = पढ़ोl_relaxed(emc->regs + CLK_SOURCE_EMC);
	src = FIELD_GET(CLK_SOURCE_EMC_2X_CLK_SRC, value);

	वापस src;
पूर्ण

अटल अचिन्हित दीर्घ tegra210_clk_emc_recalc_rate(काष्ठा clk_hw *hw,
						  अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा tegra210_clk_emc *emc = to_tegra210_clk_emc(hw);
	u32 value, भाग;

	/*
	 * CCF assumes that neither the parent nor its rate will change during
	 * ->set_rate(), so the parent rate passed in here was cached from the
	 * parent beक्रमe the ->set_rate() call.
	 *
	 * This can lead to wrong results being reported क्रम the EMC घड़ी अगर
	 * the parent and/or parent rate have changed as part of the EMC rate
	 * change sequence. Fix this by overriding the parent घड़ी with what
	 * we know to be the correct value after the rate change.
	 */
	parent_rate = clk_hw_get_rate(clk_hw_get_parent(hw));

	value = पढ़ोl_relaxed(emc->regs + CLK_SOURCE_EMC);

	भाग = FIELD_GET(CLK_SOURCE_EMC_2X_CLK_DIVISOR, value);
	भाग += 2;

	वापस DIV_ROUND_UP(parent_rate * 2, भाग);
पूर्ण

अटल दीर्घ tegra210_clk_emc_round_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
					अचिन्हित दीर्घ *prate)
अणु
	काष्ठा tegra210_clk_emc *emc = to_tegra210_clk_emc(hw);
	काष्ठा tegra210_clk_emc_provider *provider = emc->provider;
	अचिन्हित पूर्णांक i;

	अगर (!provider || !provider->configs || provider->num_configs == 0)
		वापस clk_hw_get_rate(hw);

	क्रम (i = 0; i < provider->num_configs; i++) अणु
		अगर (provider->configs[i].rate >= rate)
			वापस provider->configs[i].rate;
	पूर्ण

	वापस provider->configs[i - 1].rate;
पूर्ण

अटल काष्ठा clk *tegra210_clk_emc_find_parent(काष्ठा tegra210_clk_emc *emc,
						u8 index)
अणु
	काष्ठा clk_hw *parent = clk_hw_get_parent_by_index(&emc->hw, index);
	स्थिर अक्षर *name = clk_hw_get_name(parent);

	/* XXX implement cache? */

	वापस __clk_lookup(name);
पूर्ण

अटल पूर्णांक tegra210_clk_emc_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				     अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा tegra210_clk_emc *emc = to_tegra210_clk_emc(hw);
	काष्ठा tegra210_clk_emc_provider *provider = emc->provider;
	काष्ठा tegra210_clk_emc_config *config;
	काष्ठा device *dev = provider->dev;
	काष्ठा clk_hw *old, *new, *parent;
	u8 old_idx, new_idx, index;
	काष्ठा clk *clk;
	अचिन्हित पूर्णांक i;
	पूर्णांक err;

	अगर (!provider->configs || provider->num_configs == 0)
		वापस -EINVAL;

	क्रम (i = 0; i < provider->num_configs; i++) अणु
		अगर (provider->configs[i].rate >= rate) अणु
			config = &provider->configs[i];
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (i == provider->num_configs)
		config = &provider->configs[i - 1];

	old_idx = tegra210_clk_emc_get_parent(hw);
	new_idx = FIELD_GET(CLK_SOURCE_EMC_2X_CLK_SRC, config->value);

	old = clk_hw_get_parent_by_index(hw, old_idx);
	new = clk_hw_get_parent_by_index(hw, new_idx);

	/* अगर the rate has changed... */
	अगर (config->parent_rate != clk_hw_get_rate(old)) अणु
		/* ... but the घड़ी source reमुख्यs the same ... */
		अगर (new_idx == old_idx) अणु
			/* ... चयन to the alternative घड़ी source. */
			चयन (new_idx) अणु
			हाल CLK_SRC_PLLM:
				new_idx = CLK_SRC_PLLMB;
				अवरोध;

			हाल CLK_SRC_PLLM_UD:
				new_idx = CLK_SRC_PLLMB_UD;
				अवरोध;

			हाल CLK_SRC_PLLMB_UD:
				new_idx = CLK_SRC_PLLM_UD;
				अवरोध;

			हाल CLK_SRC_PLLMB:
				new_idx = CLK_SRC_PLLM;
				अवरोध;
			पूर्ण

			/*
			 * This should never happen because we can't deal with
			 * it.
			 */
			अगर (WARN_ON(new_idx == old_idx))
				वापस -EINVAL;

			new = clk_hw_get_parent_by_index(hw, new_idx);
		पूर्ण

		index = new_idx;
		parent = new;
	पूर्ण अन्यथा अणु
		index = old_idx;
		parent = old;
	पूर्ण

	clk = tegra210_clk_emc_find_parent(emc, index);
	अगर (IS_ERR(clk)) अणु
		err = PTR_ERR(clk);
		dev_err(dev, "failed to get parent clock for index %u: %d\n",
			index, err);
		वापस err;
	पूर्ण

	/* set the new parent घड़ी to the required rate */
	अगर (clk_get_rate(clk) != config->parent_rate) अणु
		err = clk_set_rate(clk, config->parent_rate);
		अगर (err < 0) अणु
			dev_err(dev, "failed to set rate %lu Hz for %pC: %d\n",
				config->parent_rate, clk, err);
			वापस err;
		पूर्ण
	पूर्ण

	/* enable the new parent घड़ी */
	अगर (parent != old) अणु
		err = clk_prepare_enable(clk);
		अगर (err < 0) अणु
			dev_err(dev, "failed to enable parent clock %pC: %d\n",
				clk, err);
			वापस err;
		पूर्ण
	पूर्ण

	/* update the EMC source configuration to reflect the new parent */
	config->value &= ~CLK_SOURCE_EMC_2X_CLK_SRC;
	config->value |= FIELD_PREP(CLK_SOURCE_EMC_2X_CLK_SRC, index);

	/*
	 * Finally, चयन the EMC programming with both old and new parent
	 * घड़ीs enabled.
	 */
	err = provider->set_rate(dev, config);
	अगर (err < 0) अणु
		dev_err(dev, "failed to set EMC rate to %lu Hz: %d\n", rate,
			err);

		/*
		 * If we're unable to चयन to the new EMC frequency, we no
		 * दीर्घer need the new parent to be enabled.
		 */
		अगर (parent != old)
			clk_disable_unprepare(clk);

		वापस err;
	पूर्ण

	/* reparent to new parent घड़ी and disable the old parent घड़ी */
	अगर (parent != old) अणु
		clk = tegra210_clk_emc_find_parent(emc, old_idx);
		अगर (IS_ERR(clk)) अणु
			err = PTR_ERR(clk);
			dev_err(dev,
				"failed to get parent clock for index %u: %d\n",
				old_idx, err);
			वापस err;
		पूर्ण

		clk_hw_reparent(hw, parent);
		clk_disable_unprepare(clk);
	पूर्ण

	वापस err;
पूर्ण

अटल स्थिर काष्ठा clk_ops tegra210_clk_emc_ops = अणु
	.get_parent = tegra210_clk_emc_get_parent,
	.recalc_rate = tegra210_clk_emc_recalc_rate,
	.round_rate = tegra210_clk_emc_round_rate,
	.set_rate = tegra210_clk_emc_set_rate,
पूर्ण;

काष्ठा clk *tegra210_clk_रेजिस्टर_emc(काष्ठा device_node *np,
				      व्योम __iomem *regs)
अणु
	काष्ठा tegra210_clk_emc *emc;
	काष्ठा clk_init_data init;
	काष्ठा clk *clk;

	emc = kzalloc(माप(*emc), GFP_KERNEL);
	अगर (!emc)
		वापस ERR_PTR(-ENOMEM);

	emc->regs = regs;

	init.name = "emc";
	init.ops = &tegra210_clk_emc_ops;
	init.flags = CLK_IS_CRITICAL | CLK_GET_RATE_NOCACHE;
	init.parent_names = tegra210_clk_emc_parents;
	init.num_parents = ARRAY_SIZE(tegra210_clk_emc_parents);
	emc->hw.init = &init;

	clk = clk_रेजिस्टर(शून्य, &emc->hw);
	अगर (IS_ERR(clk)) अणु
		kमुक्त(emc);
		वापस clk;
	पूर्ण

	वापस clk;
पूर्ण

पूर्णांक tegra210_clk_emc_attach(काष्ठा clk *clk,
			    काष्ठा tegra210_clk_emc_provider *provider)
अणु
	काष्ठा clk_hw *hw = __clk_get_hw(clk);
	काष्ठा tegra210_clk_emc *emc = to_tegra210_clk_emc(hw);
	काष्ठा device *dev = provider->dev;
	अचिन्हित पूर्णांक i;
	पूर्णांक err;

	अगर (!try_module_get(provider->owner))
		वापस -ENODEV;

	क्रम (i = 0; i < provider->num_configs; i++) अणु
		काष्ठा tegra210_clk_emc_config *config = &provider->configs[i];
		काष्ठा clk_hw *parent;
		bool same_freq;
		u8 भाग, src;

		भाग = FIELD_GET(CLK_SOURCE_EMC_2X_CLK_DIVISOR, config->value);
		src = FIELD_GET(CLK_SOURCE_EMC_2X_CLK_SRC, config->value);

		/* करो basic sanity checking on the EMC timings */
		अगर (भाग & 0x1) अणु
			dev_err(dev, "invalid odd divider %u for rate %lu Hz\n",
				भाग, config->rate);
			err = -EINVAL;
			जाओ put;
		पूर्ण

		same_freq = config->value & CLK_SOURCE_EMC_MC_EMC_SAME_FREQ;

		अगर (same_freq != config->same_freq) अणु
			dev_err(dev,
				"ambiguous EMC to MC ratio for rate %lu Hz\n",
				config->rate);
			err = -EINVAL;
			जाओ put;
		पूर्ण

		parent = clk_hw_get_parent_by_index(hw, src);
		config->parent = src;

		अगर (src == CLK_SRC_PLLM || src == CLK_SRC_PLLM_UD) अणु
			config->parent_rate = config->rate * (1 + भाग / 2);
		पूर्ण अन्यथा अणु
			अचिन्हित दीर्घ rate = config->rate * (1 + भाग / 2);

			config->parent_rate = clk_hw_get_rate(parent);

			अगर (config->parent_rate != rate) अणु
				dev_err(dev,
					"rate %lu Hz does not match input\n",
					config->rate);
				err = -EINVAL;
				जाओ put;
			पूर्ण
		पूर्ण
	पूर्ण

	emc->provider = provider;

	वापस 0;

put:
	module_put(provider->owner);
	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(tegra210_clk_emc_attach);

व्योम tegra210_clk_emc_detach(काष्ठा clk *clk)
अणु
	काष्ठा tegra210_clk_emc *emc = to_tegra210_clk_emc(__clk_get_hw(clk));

	module_put(emc->provider->owner);
	emc->provider = शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(tegra210_clk_emc_detach);
