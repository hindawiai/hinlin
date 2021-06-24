<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2013, The Linux Foundation. All rights reserved.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/bitops.h>
#समावेश <linux/err.h>
#समावेश <linux/bug.h>
#समावेश <linux/delay.h>
#समावेश <linux/export.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/regmap.h>

#समावेश <यंत्र/भाग64.h>

#समावेश "clk-pll.h"
#समावेश "common.h"

#घोषणा PLL_OUTCTRL		BIT(0)
#घोषणा PLL_BYPASSNL		BIT(1)
#घोषणा PLL_RESET_N		BIT(2)

अटल पूर्णांक clk_pll_enable(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_pll *pll = to_clk_pll(hw);
	पूर्णांक ret;
	u32 mask, val;

	mask = PLL_OUTCTRL | PLL_RESET_N | PLL_BYPASSNL;
	ret = regmap_पढ़ो(pll->clkr.regmap, pll->mode_reg, &val);
	अगर (ret)
		वापस ret;

	/* Skip अगर alपढ़ोy enabled or in FSM mode */
	अगर ((val & mask) == mask || val & PLL_VOTE_FSM_ENA)
		वापस 0;

	/* Disable PLL bypass mode. */
	ret = regmap_update_bits(pll->clkr.regmap, pll->mode_reg, PLL_BYPASSNL,
				 PLL_BYPASSNL);
	अगर (ret)
		वापस ret;

	/*
	 * H/W requires a 5us delay between disabling the bypass and
	 * de-निश्चितing the reset. Delay 10us just to be safe.
	 */
	udelay(10);

	/* De-निश्चित active-low PLL reset. */
	ret = regmap_update_bits(pll->clkr.regmap, pll->mode_reg, PLL_RESET_N,
				 PLL_RESET_N);
	अगर (ret)
		वापस ret;

	/* Wait until PLL is locked. */
	udelay(50);

	/* Enable PLL output. */
	वापस regmap_update_bits(pll->clkr.regmap, pll->mode_reg, PLL_OUTCTRL,
				 PLL_OUTCTRL);
पूर्ण

अटल व्योम clk_pll_disable(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_pll *pll = to_clk_pll(hw);
	u32 mask;
	u32 val;

	regmap_पढ़ो(pll->clkr.regmap, pll->mode_reg, &val);
	/* Skip अगर in FSM mode */
	अगर (val & PLL_VOTE_FSM_ENA)
		वापस;
	mask = PLL_OUTCTRL | PLL_RESET_N | PLL_BYPASSNL;
	regmap_update_bits(pll->clkr.regmap, pll->mode_reg, mask, 0);
पूर्ण

अटल अचिन्हित दीर्घ
clk_pll_recalc_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा clk_pll *pll = to_clk_pll(hw);
	u32 l, m, n, config;
	अचिन्हित दीर्घ rate;
	u64 पंचांगp;

	regmap_पढ़ो(pll->clkr.regmap, pll->l_reg, &l);
	regmap_पढ़ो(pll->clkr.regmap, pll->m_reg, &m);
	regmap_पढ़ो(pll->clkr.regmap, pll->n_reg, &n);

	l &= 0x3ff;
	m &= 0x7ffff;
	n &= 0x7ffff;

	rate = parent_rate * l;
	अगर (n) अणु
		पंचांगp = parent_rate;
		पंचांगp *= m;
		करो_भाग(पंचांगp, n);
		rate += पंचांगp;
	पूर्ण
	अगर (pll->post_भाग_width) अणु
		regmap_पढ़ो(pll->clkr.regmap, pll->config_reg, &config);
		config >>= pll->post_भाग_shअगरt;
		config &= BIT(pll->post_भाग_width) - 1;
		rate /= config + 1;
	पूर्ण

	वापस rate;
पूर्ण

अटल स्थिर
काष्ठा pll_freq_tbl *find_freq(स्थिर काष्ठा pll_freq_tbl *f, अचिन्हित दीर्घ rate)
अणु
	अगर (!f)
		वापस शून्य;

	क्रम (; f->freq; f++)
		अगर (rate <= f->freq)
			वापस f;

	वापस शून्य;
पूर्ण

अटल पूर्णांक
clk_pll_determine_rate(काष्ठा clk_hw *hw, काष्ठा clk_rate_request *req)
अणु
	काष्ठा clk_pll *pll = to_clk_pll(hw);
	स्थिर काष्ठा pll_freq_tbl *f;

	f = find_freq(pll->freq_tbl, req->rate);
	अगर (!f)
		req->rate = clk_pll_recalc_rate(hw, req->best_parent_rate);
	अन्यथा
		req->rate = f->freq;

	वापस 0;
पूर्ण

अटल पूर्णांक
clk_pll_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate, अचिन्हित दीर्घ p_rate)
अणु
	काष्ठा clk_pll *pll = to_clk_pll(hw);
	स्थिर काष्ठा pll_freq_tbl *f;
	bool enabled;
	u32 mode;
	u32 enable_mask = PLL_OUTCTRL | PLL_BYPASSNL | PLL_RESET_N;

	f = find_freq(pll->freq_tbl, rate);
	अगर (!f)
		वापस -EINVAL;

	regmap_पढ़ो(pll->clkr.regmap, pll->mode_reg, &mode);
	enabled = (mode & enable_mask) == enable_mask;

	अगर (enabled)
		clk_pll_disable(hw);

	regmap_update_bits(pll->clkr.regmap, pll->l_reg, 0x3ff, f->l);
	regmap_update_bits(pll->clkr.regmap, pll->m_reg, 0x7ffff, f->m);
	regmap_update_bits(pll->clkr.regmap, pll->n_reg, 0x7ffff, f->n);
	regmap_ग_लिखो(pll->clkr.regmap, pll->config_reg, f->ibits);

	अगर (enabled)
		clk_pll_enable(hw);

	वापस 0;
पूर्ण

स्थिर काष्ठा clk_ops clk_pll_ops = अणु
	.enable = clk_pll_enable,
	.disable = clk_pll_disable,
	.recalc_rate = clk_pll_recalc_rate,
	.determine_rate = clk_pll_determine_rate,
	.set_rate = clk_pll_set_rate,
पूर्ण;
EXPORT_SYMBOL_GPL(clk_pll_ops);

अटल पूर्णांक रुको_क्रम_pll(काष्ठा clk_pll *pll)
अणु
	u32 val;
	पूर्णांक count;
	पूर्णांक ret;
	स्थिर अक्षर *name = clk_hw_get_name(&pll->clkr.hw);

	/* Wait क्रम pll to enable. */
	क्रम (count = 200; count > 0; count--) अणु
		ret = regmap_पढ़ो(pll->clkr.regmap, pll->status_reg, &val);
		अगर (ret)
			वापस ret;
		अगर (val & BIT(pll->status_bit))
			वापस 0;
		udelay(1);
	पूर्ण

	WARN(1, "%s didn't enable after voting for it!\n", name);
	वापस -ETIMEDOUT;
पूर्ण

अटल पूर्णांक clk_pll_vote_enable(काष्ठा clk_hw *hw)
अणु
	पूर्णांक ret;
	काष्ठा clk_pll *p = to_clk_pll(clk_hw_get_parent(hw));

	ret = clk_enable_regmap(hw);
	अगर (ret)
		वापस ret;

	वापस रुको_क्रम_pll(p);
पूर्ण

स्थिर काष्ठा clk_ops clk_pll_vote_ops = अणु
	.enable = clk_pll_vote_enable,
	.disable = clk_disable_regmap,
पूर्ण;
EXPORT_SYMBOL_GPL(clk_pll_vote_ops);

अटल व्योम clk_pll_configure(काष्ठा clk_pll *pll, काष्ठा regmap *regmap,
	स्थिर काष्ठा pll_config *config)
अणु
	u32 val;
	u32 mask;

	regmap_ग_लिखो(regmap, pll->l_reg, config->l);
	regmap_ग_लिखो(regmap, pll->m_reg, config->m);
	regmap_ग_लिखो(regmap, pll->n_reg, config->n);

	val = config->vco_val;
	val |= config->pre_भाग_val;
	val |= config->post_भाग_val;
	val |= config->mn_ena_mask;
	val |= config->मुख्य_output_mask;
	val |= config->aux_output_mask;

	mask = config->vco_mask;
	mask |= config->pre_भाग_mask;
	mask |= config->post_भाग_mask;
	mask |= config->mn_ena_mask;
	mask |= config->मुख्य_output_mask;
	mask |= config->aux_output_mask;

	regmap_update_bits(regmap, pll->config_reg, mask, val);
पूर्ण

व्योम clk_pll_configure_sr(काष्ठा clk_pll *pll, काष्ठा regmap *regmap,
		स्थिर काष्ठा pll_config *config, bool fsm_mode)
अणु
	clk_pll_configure(pll, regmap, config);
	अगर (fsm_mode)
		qcom_pll_set_fsm_mode(regmap, pll->mode_reg, 1, 8);
पूर्ण
EXPORT_SYMBOL_GPL(clk_pll_configure_sr);

व्योम clk_pll_configure_sr_hpm_lp(काष्ठा clk_pll *pll, काष्ठा regmap *regmap,
		स्थिर काष्ठा pll_config *config, bool fsm_mode)
अणु
	clk_pll_configure(pll, regmap, config);
	अगर (fsm_mode)
		qcom_pll_set_fsm_mode(regmap, pll->mode_reg, 1, 0);
पूर्ण
EXPORT_SYMBOL_GPL(clk_pll_configure_sr_hpm_lp);

अटल पूर्णांक clk_pll_sr2_enable(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_pll *pll = to_clk_pll(hw);
	पूर्णांक ret;
	u32 mode;

	ret = regmap_पढ़ो(pll->clkr.regmap, pll->mode_reg, &mode);
	अगर (ret)
		वापस ret;

	/* Disable PLL bypass mode. */
	ret = regmap_update_bits(pll->clkr.regmap, pll->mode_reg, PLL_BYPASSNL,
				 PLL_BYPASSNL);
	अगर (ret)
		वापस ret;

	/*
	 * H/W requires a 5us delay between disabling the bypass and
	 * de-निश्चितing the reset. Delay 10us just to be safe.
	 */
	udelay(10);

	/* De-निश्चित active-low PLL reset. */
	ret = regmap_update_bits(pll->clkr.regmap, pll->mode_reg, PLL_RESET_N,
				 PLL_RESET_N);
	अगर (ret)
		वापस ret;

	ret = रुको_क्रम_pll(pll);
	अगर (ret)
		वापस ret;

	/* Enable PLL output. */
	वापस regmap_update_bits(pll->clkr.regmap, pll->mode_reg, PLL_OUTCTRL,
				 PLL_OUTCTRL);
पूर्ण

अटल पूर्णांक
clk_pll_sr2_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate, अचिन्हित दीर्घ prate)
अणु
	काष्ठा clk_pll *pll = to_clk_pll(hw);
	स्थिर काष्ठा pll_freq_tbl *f;
	bool enabled;
	u32 mode;
	u32 enable_mask = PLL_OUTCTRL | PLL_BYPASSNL | PLL_RESET_N;

	f = find_freq(pll->freq_tbl, rate);
	अगर (!f)
		वापस -EINVAL;

	regmap_पढ़ो(pll->clkr.regmap, pll->mode_reg, &mode);
	enabled = (mode & enable_mask) == enable_mask;

	अगर (enabled)
		clk_pll_disable(hw);

	regmap_update_bits(pll->clkr.regmap, pll->l_reg, 0x3ff, f->l);
	regmap_update_bits(pll->clkr.regmap, pll->m_reg, 0x7ffff, f->m);
	regmap_update_bits(pll->clkr.regmap, pll->n_reg, 0x7ffff, f->n);

	अगर (enabled)
		clk_pll_sr2_enable(hw);

	वापस 0;
पूर्ण

स्थिर काष्ठा clk_ops clk_pll_sr2_ops = अणु
	.enable = clk_pll_sr2_enable,
	.disable = clk_pll_disable,
	.set_rate = clk_pll_sr2_set_rate,
	.recalc_rate = clk_pll_recalc_rate,
	.determine_rate = clk_pll_determine_rate,
पूर्ण;
EXPORT_SYMBOL_GPL(clk_pll_sr2_ops);
