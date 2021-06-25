<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (c) 2018, The Linux Foundation. All rights reserved.

#समावेश <linux/kernel.h>
#समावेश <linux/export.h>
#समावेश <linux/regmap.h>
#समावेश <linux/delay.h>
#समावेश <linux/err.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/spinlock.h>

#समावेश "clk-regmap.h"
#समावेश "clk-hfpll.h"

#घोषणा PLL_OUTCTRL	BIT(0)
#घोषणा PLL_BYPASSNL	BIT(1)
#घोषणा PLL_RESET_N	BIT(2)

/* Initialize a HFPLL at a given rate and enable it. */
अटल व्योम __clk_hfpll_init_once(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_hfpll *h = to_clk_hfpll(hw);
	काष्ठा hfpll_data स्थिर *hd = h->d;
	काष्ठा regmap *regmap = h->clkr.regmap;

	अगर (likely(h->init_करोne))
		वापस;

	/* Configure PLL parameters क्रम पूर्णांकeger mode. */
	अगर (hd->config_val)
		regmap_ग_लिखो(regmap, hd->config_reg, hd->config_val);
	regmap_ग_लिखो(regmap, hd->m_reg, 0);
	regmap_ग_लिखो(regmap, hd->n_reg, 1);

	अगर (hd->user_reg) अणु
		u32 regval = hd->user_val;
		अचिन्हित दीर्घ rate;

		rate = clk_hw_get_rate(hw);

		/* Pick the right VCO. */
		अगर (hd->user_vco_mask && rate > hd->low_vco_max_rate)
			regval |= hd->user_vco_mask;
		regmap_ग_लिखो(regmap, hd->user_reg, regval);
	पूर्ण

	अगर (hd->droop_reg)
		regmap_ग_लिखो(regmap, hd->droop_reg, hd->droop_val);

	h->init_करोne = true;
पूर्ण

अटल व्योम __clk_hfpll_enable(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_hfpll *h = to_clk_hfpll(hw);
	काष्ठा hfpll_data स्थिर *hd = h->d;
	काष्ठा regmap *regmap = h->clkr.regmap;
	u32 val;

	__clk_hfpll_init_once(hw);

	/* Disable PLL bypass mode. */
	regmap_update_bits(regmap, hd->mode_reg, PLL_BYPASSNL, PLL_BYPASSNL);

	/*
	 * H/W requires a 5us delay between disabling the bypass and
	 * de-निश्चितing the reset. Delay 10us just to be safe.
	 */
	udelay(10);

	/* De-निश्चित active-low PLL reset. */
	regmap_update_bits(regmap, hd->mode_reg, PLL_RESET_N, PLL_RESET_N);

	/* Wait क्रम PLL to lock. */
	अगर (hd->status_reg) अणु
		करो अणु
			regmap_पढ़ो(regmap, hd->status_reg, &val);
		पूर्ण जबतक (!(val & BIT(hd->lock_bit)));
	पूर्ण अन्यथा अणु
		udelay(60);
	पूर्ण

	/* Enable PLL output. */
	regmap_update_bits(regmap, hd->mode_reg, PLL_OUTCTRL, PLL_OUTCTRL);
पूर्ण

/* Enable an alपढ़ोy-configured HFPLL. */
अटल पूर्णांक clk_hfpll_enable(काष्ठा clk_hw *hw)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा clk_hfpll *h = to_clk_hfpll(hw);
	काष्ठा hfpll_data स्थिर *hd = h->d;
	काष्ठा regmap *regmap = h->clkr.regmap;
	u32 mode;

	spin_lock_irqsave(&h->lock, flags);
	regmap_पढ़ो(regmap, hd->mode_reg, &mode);
	अगर (!(mode & (PLL_BYPASSNL | PLL_RESET_N | PLL_OUTCTRL)))
		__clk_hfpll_enable(hw);
	spin_unlock_irqrestore(&h->lock, flags);

	वापस 0;
पूर्ण

अटल व्योम __clk_hfpll_disable(काष्ठा clk_hfpll *h)
अणु
	काष्ठा hfpll_data स्थिर *hd = h->d;
	काष्ठा regmap *regmap = h->clkr.regmap;

	/*
	 * Disable the PLL output, disable test mode, enable the bypass mode,
	 * and निश्चित the reset.
	 */
	regmap_update_bits(regmap, hd->mode_reg,
			   PLL_BYPASSNL | PLL_RESET_N | PLL_OUTCTRL, 0);
पूर्ण

अटल व्योम clk_hfpll_disable(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_hfpll *h = to_clk_hfpll(hw);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&h->lock, flags);
	__clk_hfpll_disable(h);
	spin_unlock_irqrestore(&h->lock, flags);
पूर्ण

अटल दीर्घ clk_hfpll_round_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				 अचिन्हित दीर्घ *parent_rate)
अणु
	काष्ठा clk_hfpll *h = to_clk_hfpll(hw);
	काष्ठा hfpll_data स्थिर *hd = h->d;
	अचिन्हित दीर्घ rrate;

	rate = clamp(rate, hd->min_rate, hd->max_rate);

	rrate = DIV_ROUND_UP(rate, *parent_rate) * *parent_rate;
	अगर (rrate > hd->max_rate)
		rrate -= *parent_rate;

	वापस rrate;
पूर्ण

/*
 * For optimization reasons, assumes no करोwnstream घड़ीs are actively using
 * it.
 */
अटल पूर्णांक clk_hfpll_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
			      अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा clk_hfpll *h = to_clk_hfpll(hw);
	काष्ठा hfpll_data स्थिर *hd = h->d;
	काष्ठा regmap *regmap = h->clkr.regmap;
	अचिन्हित दीर्घ flags;
	u32 l_val, val;
	bool enabled;

	l_val = rate / parent_rate;

	spin_lock_irqsave(&h->lock, flags);

	enabled = __clk_is_enabled(hw->clk);
	अगर (enabled)
		__clk_hfpll_disable(h);

	/* Pick the right VCO. */
	अगर (hd->user_reg && hd->user_vco_mask) अणु
		regmap_पढ़ो(regmap, hd->user_reg, &val);
		अगर (rate <= hd->low_vco_max_rate)
			val &= ~hd->user_vco_mask;
		अन्यथा
			val |= hd->user_vco_mask;
		regmap_ग_लिखो(regmap, hd->user_reg, val);
	पूर्ण

	regmap_ग_लिखो(regmap, hd->l_reg, l_val);

	अगर (enabled)
		__clk_hfpll_enable(hw);

	spin_unlock_irqrestore(&h->lock, flags);

	वापस 0;
पूर्ण

अटल अचिन्हित दीर्घ clk_hfpll_recalc_rate(काष्ठा clk_hw *hw,
					   अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा clk_hfpll *h = to_clk_hfpll(hw);
	काष्ठा hfpll_data स्थिर *hd = h->d;
	काष्ठा regmap *regmap = h->clkr.regmap;
	u32 l_val;

	regmap_पढ़ो(regmap, hd->l_reg, &l_val);

	वापस l_val * parent_rate;
पूर्ण

अटल पूर्णांक clk_hfpll_init(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_hfpll *h = to_clk_hfpll(hw);
	काष्ठा hfpll_data स्थिर *hd = h->d;
	काष्ठा regmap *regmap = h->clkr.regmap;
	u32 mode, status;

	regmap_पढ़ो(regmap, hd->mode_reg, &mode);
	अगर (mode != (PLL_BYPASSNL | PLL_RESET_N | PLL_OUTCTRL)) अणु
		__clk_hfpll_init_once(hw);
		वापस 0;
	पूर्ण

	अगर (hd->status_reg) अणु
		regmap_पढ़ो(regmap, hd->status_reg, &status);
		अगर (!(status & BIT(hd->lock_bit))) अणु
			WARN(1, "HFPLL %s is ON, but not locked!\n",
			     __clk_get_name(hw->clk));
			clk_hfpll_disable(hw);
			__clk_hfpll_init_once(hw);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक hfpll_is_enabled(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_hfpll *h = to_clk_hfpll(hw);
	काष्ठा hfpll_data स्थिर *hd = h->d;
	काष्ठा regmap *regmap = h->clkr.regmap;
	u32 mode;

	regmap_पढ़ो(regmap, hd->mode_reg, &mode);
	mode &= 0x7;
	वापस mode == (PLL_BYPASSNL | PLL_RESET_N | PLL_OUTCTRL);
पूर्ण

स्थिर काष्ठा clk_ops clk_ops_hfpll = अणु
	.enable = clk_hfpll_enable,
	.disable = clk_hfpll_disable,
	.is_enabled = hfpll_is_enabled,
	.round_rate = clk_hfpll_round_rate,
	.set_rate = clk_hfpll_set_rate,
	.recalc_rate = clk_hfpll_recalc_rate,
	.init = clk_hfpll_init,
पूर्ण;
EXPORT_SYMBOL_GPL(clk_ops_hfpll);
