<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (c) 2014 MunकरोReader S.L.
 * Author: Heiko Stuebner <heiko@sntech.de>
 *
 * Copyright (c) 2015 Rockchip Electronics Co. Ltd.
 * Author: Xing Zheng <zhengxing@rock-chips.com>
 */

#समावेश <यंत्र/भाग64.h>
#समावेश <linux/slab.h>
#समावेश <linux/पन.स>
#समावेश <linux/delay.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/iopoll.h>
#समावेश <linux/regmap.h>
#समावेश <linux/clk.h>
#समावेश "clk.h"

#घोषणा PLL_MODE_MASK		0x3
#घोषणा PLL_MODE_SLOW		0x0
#घोषणा PLL_MODE_NORM		0x1
#घोषणा PLL_MODE_DEEP		0x2
#घोषणा PLL_RK3328_MODE_MASK	0x1

काष्ठा rockchip_clk_pll अणु
	काष्ठा clk_hw		hw;

	काष्ठा clk_mux		pll_mux;
	स्थिर काष्ठा clk_ops	*pll_mux_ops;

	काष्ठा notअगरier_block	clk_nb;

	व्योम __iomem		*reg_base;
	पूर्णांक			lock_offset;
	अचिन्हित पूर्णांक		lock_shअगरt;
	क्रमागत rockchip_pll_type	type;
	u8			flags;
	स्थिर काष्ठा rockchip_pll_rate_table *rate_table;
	अचिन्हित पूर्णांक		rate_count;
	spinlock_t		*lock;

	काष्ठा rockchip_clk_provider *ctx;
पूर्ण;

#घोषणा to_rockchip_clk_pll(_hw) container_of(_hw, काष्ठा rockchip_clk_pll, hw)
#घोषणा to_rockchip_clk_pll_nb(nb) \
			container_of(nb, काष्ठा rockchip_clk_pll, clk_nb)

अटल स्थिर काष्ठा rockchip_pll_rate_table *rockchip_get_pll_settings(
			    काष्ठा rockchip_clk_pll *pll, अचिन्हित दीर्घ rate)
अणु
	स्थिर काष्ठा rockchip_pll_rate_table  *rate_table = pll->rate_table;
	पूर्णांक i;

	क्रम (i = 0; i < pll->rate_count; i++) अणु
		अगर (rate == rate_table[i].rate)
			वापस &rate_table[i];
	पूर्ण

	वापस शून्य;
पूर्ण

अटल दीर्घ rockchip_pll_round_rate(काष्ठा clk_hw *hw,
			    अचिन्हित दीर्घ drate, अचिन्हित दीर्घ *prate)
अणु
	काष्ठा rockchip_clk_pll *pll = to_rockchip_clk_pll(hw);
	स्थिर काष्ठा rockchip_pll_rate_table *rate_table = pll->rate_table;
	पूर्णांक i;

	/* Assumming rate_table is in descending order */
	क्रम (i = 0; i < pll->rate_count; i++) अणु
		अगर (drate >= rate_table[i].rate)
			वापस rate_table[i].rate;
	पूर्ण

	/* वापस minimum supported value */
	वापस rate_table[i - 1].rate;
पूर्ण

/*
 * Wait क्रम the pll to reach the locked state.
 * The calling set_rate function is responsible क्रम making sure the
 * grf regmap is available.
 */
अटल पूर्णांक rockchip_pll_रुको_lock(काष्ठा rockchip_clk_pll *pll)
अणु
	काष्ठा regmap *grf = pll->ctx->grf;
	अचिन्हित पूर्णांक val;
	पूर्णांक ret;

	ret = regmap_पढ़ो_poll_समयout(grf, pll->lock_offset, val,
				       val & BIT(pll->lock_shअगरt), 0, 1000);
	अगर (ret)
		pr_err("%s: timeout waiting for pll to lock\n", __func__);

	वापस ret;
पूर्ण

/*
 * PLL used in RK3036
 */

#घोषणा RK3036_PLLCON(i)			(i * 0x4)
#घोषणा RK3036_PLLCON0_FBDIV_MASK		0xfff
#घोषणा RK3036_PLLCON0_FBDIV_SHIFT		0
#घोषणा RK3036_PLLCON0_POSTDIV1_MASK		0x7
#घोषणा RK3036_PLLCON0_POSTDIV1_SHIFT		12
#घोषणा RK3036_PLLCON1_REFDIV_MASK		0x3f
#घोषणा RK3036_PLLCON1_REFDIV_SHIFT		0
#घोषणा RK3036_PLLCON1_POSTDIV2_MASK		0x7
#घोषणा RK3036_PLLCON1_POSTDIV2_SHIFT		6
#घोषणा RK3036_PLLCON1_LOCK_STATUS		BIT(10)
#घोषणा RK3036_PLLCON1_DSMPD_MASK		0x1
#घोषणा RK3036_PLLCON1_DSMPD_SHIFT		12
#घोषणा RK3036_PLLCON1_PWRDOWN			BIT(13)
#घोषणा RK3036_PLLCON2_FRAC_MASK		0xffffff
#घोषणा RK3036_PLLCON2_FRAC_SHIFT		0

अटल पूर्णांक rockchip_rk3036_pll_रुको_lock(काष्ठा rockchip_clk_pll *pll)
अणु
	u32 pllcon;
	पूर्णांक ret;

	/*
	 * Lock समय typical 250, max 500 input घड़ी cycles @24MHz
	 * So define a very safe maximum of 1000us, meaning 24000 cycles.
	 */
	ret = पढ़ोl_relaxed_poll_समयout(pll->reg_base + RK3036_PLLCON(1),
					 pllcon,
					 pllcon & RK3036_PLLCON1_LOCK_STATUS,
					 0, 1000);
	अगर (ret)
		pr_err("%s: timeout waiting for pll to lock\n", __func__);

	वापस ret;
पूर्ण

अटल व्योम rockchip_rk3036_pll_get_params(काष्ठा rockchip_clk_pll *pll,
					काष्ठा rockchip_pll_rate_table *rate)
अणु
	u32 pllcon;

	pllcon = पढ़ोl_relaxed(pll->reg_base + RK3036_PLLCON(0));
	rate->fbभाग = ((pllcon >> RK3036_PLLCON0_FBDIV_SHIFT)
				& RK3036_PLLCON0_FBDIV_MASK);
	rate->postभाग1 = ((pllcon >> RK3036_PLLCON0_POSTDIV1_SHIFT)
				& RK3036_PLLCON0_POSTDIV1_MASK);

	pllcon = पढ़ोl_relaxed(pll->reg_base + RK3036_PLLCON(1));
	rate->refभाग = ((pllcon >> RK3036_PLLCON1_REFDIV_SHIFT)
				& RK3036_PLLCON1_REFDIV_MASK);
	rate->postभाग2 = ((pllcon >> RK3036_PLLCON1_POSTDIV2_SHIFT)
				& RK3036_PLLCON1_POSTDIV2_MASK);
	rate->dsmpd = ((pllcon >> RK3036_PLLCON1_DSMPD_SHIFT)
				& RK3036_PLLCON1_DSMPD_MASK);

	pllcon = पढ़ोl_relaxed(pll->reg_base + RK3036_PLLCON(2));
	rate->frac = ((pllcon >> RK3036_PLLCON2_FRAC_SHIFT)
				& RK3036_PLLCON2_FRAC_MASK);
पूर्ण

अटल अचिन्हित दीर्घ rockchip_rk3036_pll_recalc_rate(काष्ठा clk_hw *hw,
						     अचिन्हित दीर्घ prate)
अणु
	काष्ठा rockchip_clk_pll *pll = to_rockchip_clk_pll(hw);
	काष्ठा rockchip_pll_rate_table cur;
	u64 rate64 = prate;

	rockchip_rk3036_pll_get_params(pll, &cur);

	rate64 *= cur.fbभाग;
	करो_भाग(rate64, cur.refभाग);

	अगर (cur.dsmpd == 0) अणु
		/* fractional mode */
		u64 frac_rate64 = prate * cur.frac;

		करो_भाग(frac_rate64, cur.refभाग);
		rate64 += frac_rate64 >> 24;
	पूर्ण

	करो_भाग(rate64, cur.postभाग1);
	करो_भाग(rate64, cur.postभाग2);

	वापस (अचिन्हित दीर्घ)rate64;
पूर्ण

अटल पूर्णांक rockchip_rk3036_pll_set_params(काष्ठा rockchip_clk_pll *pll,
				स्थिर काष्ठा rockchip_pll_rate_table *rate)
अणु
	स्थिर काष्ठा clk_ops *pll_mux_ops = pll->pll_mux_ops;
	काष्ठा clk_mux *pll_mux = &pll->pll_mux;
	काष्ठा rockchip_pll_rate_table cur;
	u32 pllcon;
	पूर्णांक rate_change_remuxed = 0;
	पूर्णांक cur_parent;
	पूर्णांक ret;

	pr_debug("%s: rate settings for %lu fbdiv: %d, postdiv1: %d, refdiv: %d, postdiv2: %d, dsmpd: %d, frac: %d\n",
		__func__, rate->rate, rate->fbभाग, rate->postभाग1, rate->refभाग,
		rate->postभाग2, rate->dsmpd, rate->frac);

	rockchip_rk3036_pll_get_params(pll, &cur);
	cur.rate = 0;

	cur_parent = pll_mux_ops->get_parent(&pll_mux->hw);
	अगर (cur_parent == PLL_MODE_NORM) अणु
		pll_mux_ops->set_parent(&pll_mux->hw, PLL_MODE_SLOW);
		rate_change_remuxed = 1;
	पूर्ण

	/* update pll values */
	ग_लिखोl_relaxed(HIWORD_UPDATE(rate->fbभाग, RK3036_PLLCON0_FBDIV_MASK,
					  RK3036_PLLCON0_FBDIV_SHIFT) |
		       HIWORD_UPDATE(rate->postभाग1, RK3036_PLLCON0_POSTDIV1_MASK,
					     RK3036_PLLCON0_POSTDIV1_SHIFT),
		       pll->reg_base + RK3036_PLLCON(0));

	ग_लिखोl_relaxed(HIWORD_UPDATE(rate->refभाग, RK3036_PLLCON1_REFDIV_MASK,
						   RK3036_PLLCON1_REFDIV_SHIFT) |
		       HIWORD_UPDATE(rate->postभाग2, RK3036_PLLCON1_POSTDIV2_MASK,
						     RK3036_PLLCON1_POSTDIV2_SHIFT) |
		       HIWORD_UPDATE(rate->dsmpd, RK3036_PLLCON1_DSMPD_MASK,
						  RK3036_PLLCON1_DSMPD_SHIFT),
		       pll->reg_base + RK3036_PLLCON(1));

	/* GPLL CON2 is not HIWORD_MASK */
	pllcon = पढ़ोl_relaxed(pll->reg_base + RK3036_PLLCON(2));
	pllcon &= ~(RK3036_PLLCON2_FRAC_MASK << RK3036_PLLCON2_FRAC_SHIFT);
	pllcon |= rate->frac << RK3036_PLLCON2_FRAC_SHIFT;
	ग_लिखोl_relaxed(pllcon, pll->reg_base + RK3036_PLLCON(2));

	/* रुको क्रम the pll to lock */
	ret = rockchip_rk3036_pll_रुको_lock(pll);
	अगर (ret) अणु
		pr_warn("%s: pll update unsuccessful, trying to restore old params\n",
			__func__);
		rockchip_rk3036_pll_set_params(pll, &cur);
	पूर्ण

	अगर (rate_change_remuxed)
		pll_mux_ops->set_parent(&pll_mux->hw, PLL_MODE_NORM);

	वापस ret;
पूर्ण

अटल पूर्णांक rockchip_rk3036_pll_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ drate,
					अचिन्हित दीर्घ prate)
अणु
	काष्ठा rockchip_clk_pll *pll = to_rockchip_clk_pll(hw);
	स्थिर काष्ठा rockchip_pll_rate_table *rate;

	pr_debug("%s: changing %s to %lu with a parent rate of %lu\n",
		 __func__, __clk_get_name(hw->clk), drate, prate);

	/* Get required rate settings from table */
	rate = rockchip_get_pll_settings(pll, drate);
	अगर (!rate) अणु
		pr_err("%s: Invalid rate : %lu for pll clk %s\n", __func__,
			drate, __clk_get_name(hw->clk));
		वापस -EINVAL;
	पूर्ण

	वापस rockchip_rk3036_pll_set_params(pll, rate);
पूर्ण

अटल पूर्णांक rockchip_rk3036_pll_enable(काष्ठा clk_hw *hw)
अणु
	काष्ठा rockchip_clk_pll *pll = to_rockchip_clk_pll(hw);

	ग_लिखोl(HIWORD_UPDATE(0, RK3036_PLLCON1_PWRDOWN, 0),
	       pll->reg_base + RK3036_PLLCON(1));
	rockchip_rk3036_pll_रुको_lock(pll);

	वापस 0;
पूर्ण

अटल व्योम rockchip_rk3036_pll_disable(काष्ठा clk_hw *hw)
अणु
	काष्ठा rockchip_clk_pll *pll = to_rockchip_clk_pll(hw);

	ग_लिखोl(HIWORD_UPDATE(RK3036_PLLCON1_PWRDOWN,
			     RK3036_PLLCON1_PWRDOWN, 0),
	       pll->reg_base + RK3036_PLLCON(1));
पूर्ण

अटल पूर्णांक rockchip_rk3036_pll_is_enabled(काष्ठा clk_hw *hw)
अणु
	काष्ठा rockchip_clk_pll *pll = to_rockchip_clk_pll(hw);
	u32 pllcon = पढ़ोl(pll->reg_base + RK3036_PLLCON(1));

	वापस !(pllcon & RK3036_PLLCON1_PWRDOWN);
पूर्ण

अटल पूर्णांक rockchip_rk3036_pll_init(काष्ठा clk_hw *hw)
अणु
	काष्ठा rockchip_clk_pll *pll = to_rockchip_clk_pll(hw);
	स्थिर काष्ठा rockchip_pll_rate_table *rate;
	काष्ठा rockchip_pll_rate_table cur;
	अचिन्हित दीर्घ drate;

	अगर (!(pll->flags & ROCKCHIP_PLL_SYNC_RATE))
		वापस 0;

	drate = clk_hw_get_rate(hw);
	rate = rockchip_get_pll_settings(pll, drate);

	/* when no rate setting क्रम the current rate, rely on clk_set_rate */
	अगर (!rate)
		वापस 0;

	rockchip_rk3036_pll_get_params(pll, &cur);

	pr_debug("%s: pll %s@%lu: Hz\n", __func__, __clk_get_name(hw->clk),
		 drate);
	pr_debug("old - fbdiv: %d, postdiv1: %d, refdiv: %d, postdiv2: %d, dsmpd: %d, frac: %d\n",
		 cur.fbभाग, cur.postभाग1, cur.refभाग, cur.postभाग2,
		 cur.dsmpd, cur.frac);
	pr_debug("new - fbdiv: %d, postdiv1: %d, refdiv: %d, postdiv2: %d, dsmpd: %d, frac: %d\n",
		 rate->fbभाग, rate->postभाग1, rate->refभाग, rate->postभाग2,
		 rate->dsmpd, rate->frac);

	अगर (rate->fbभाग != cur.fbभाग || rate->postभाग1 != cur.postभाग1 ||
		rate->refभाग != cur.refभाग || rate->postभाग2 != cur.postभाग2 ||
		rate->dsmpd != cur.dsmpd ||
		(!cur.dsmpd && (rate->frac != cur.frac))) अणु
		काष्ठा clk *parent = clk_get_parent(hw->clk);

		अगर (!parent) अणु
			pr_warn("%s: parent of %s not available\n",
				__func__, __clk_get_name(hw->clk));
			वापस 0;
		पूर्ण

		pr_debug("%s: pll %s: rate params do not match rate table, adjusting\n",
			 __func__, __clk_get_name(hw->clk));
		rockchip_rk3036_pll_set_params(pll, rate);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा clk_ops rockchip_rk3036_pll_clk_norate_ops = अणु
	.recalc_rate = rockchip_rk3036_pll_recalc_rate,
	.enable = rockchip_rk3036_pll_enable,
	.disable = rockchip_rk3036_pll_disable,
	.is_enabled = rockchip_rk3036_pll_is_enabled,
पूर्ण;

अटल स्थिर काष्ठा clk_ops rockchip_rk3036_pll_clk_ops = अणु
	.recalc_rate = rockchip_rk3036_pll_recalc_rate,
	.round_rate = rockchip_pll_round_rate,
	.set_rate = rockchip_rk3036_pll_set_rate,
	.enable = rockchip_rk3036_pll_enable,
	.disable = rockchip_rk3036_pll_disable,
	.is_enabled = rockchip_rk3036_pll_is_enabled,
	.init = rockchip_rk3036_pll_init,
पूर्ण;

/*
 * PLL used in RK3066, RK3188 and RK3288
 */

#घोषणा RK3066_PLL_RESET_DELAY(nr)	((nr * 500) / 24 + 1)

#घोषणा RK3066_PLLCON(i)		(i * 0x4)
#घोषणा RK3066_PLLCON0_OD_MASK		0xf
#घोषणा RK3066_PLLCON0_OD_SHIFT		0
#घोषणा RK3066_PLLCON0_NR_MASK		0x3f
#घोषणा RK3066_PLLCON0_NR_SHIFT		8
#घोषणा RK3066_PLLCON1_NF_MASK		0x1fff
#घोषणा RK3066_PLLCON1_NF_SHIFT		0
#घोषणा RK3066_PLLCON2_NB_MASK		0xfff
#घोषणा RK3066_PLLCON2_NB_SHIFT		0
#घोषणा RK3066_PLLCON3_RESET		(1 << 5)
#घोषणा RK3066_PLLCON3_PWRDOWN		(1 << 1)
#घोषणा RK3066_PLLCON3_BYPASS		(1 << 0)

अटल व्योम rockchip_rk3066_pll_get_params(काष्ठा rockchip_clk_pll *pll,
					काष्ठा rockchip_pll_rate_table *rate)
अणु
	u32 pllcon;

	pllcon = पढ़ोl_relaxed(pll->reg_base + RK3066_PLLCON(0));
	rate->nr = ((pllcon >> RK3066_PLLCON0_NR_SHIFT)
				& RK3066_PLLCON0_NR_MASK) + 1;
	rate->no = ((pllcon >> RK3066_PLLCON0_OD_SHIFT)
				& RK3066_PLLCON0_OD_MASK) + 1;

	pllcon = पढ़ोl_relaxed(pll->reg_base + RK3066_PLLCON(1));
	rate->nf = ((pllcon >> RK3066_PLLCON1_NF_SHIFT)
				& RK3066_PLLCON1_NF_MASK) + 1;

	pllcon = पढ़ोl_relaxed(pll->reg_base + RK3066_PLLCON(2));
	rate->nb = ((pllcon >> RK3066_PLLCON2_NB_SHIFT)
				& RK3066_PLLCON2_NB_MASK) + 1;
पूर्ण

अटल अचिन्हित दीर्घ rockchip_rk3066_pll_recalc_rate(काष्ठा clk_hw *hw,
						     अचिन्हित दीर्घ prate)
अणु
	काष्ठा rockchip_clk_pll *pll = to_rockchip_clk_pll(hw);
	काष्ठा rockchip_pll_rate_table cur;
	u64 rate64 = prate;
	u32 pllcon;

	pllcon = पढ़ोl_relaxed(pll->reg_base + RK3066_PLLCON(3));
	अगर (pllcon & RK3066_PLLCON3_BYPASS) अणु
		pr_debug("%s: pll %s is bypassed\n", __func__,
			clk_hw_get_name(hw));
		वापस prate;
	पूर्ण

	rockchip_rk3066_pll_get_params(pll, &cur);

	rate64 *= cur.nf;
	करो_भाग(rate64, cur.nr);
	करो_भाग(rate64, cur.no);

	वापस (अचिन्हित दीर्घ)rate64;
पूर्ण

अटल पूर्णांक rockchip_rk3066_pll_set_params(काष्ठा rockchip_clk_pll *pll,
				स्थिर काष्ठा rockchip_pll_rate_table *rate)
अणु
	स्थिर काष्ठा clk_ops *pll_mux_ops = pll->pll_mux_ops;
	काष्ठा clk_mux *pll_mux = &pll->pll_mux;
	काष्ठा rockchip_pll_rate_table cur;
	पूर्णांक rate_change_remuxed = 0;
	पूर्णांक cur_parent;
	पूर्णांक ret;

	pr_debug("%s: rate settings for %lu (nr, no, nf): (%d, %d, %d)\n",
		 __func__, rate->rate, rate->nr, rate->no, rate->nf);

	rockchip_rk3066_pll_get_params(pll, &cur);
	cur.rate = 0;

	cur_parent = pll_mux_ops->get_parent(&pll_mux->hw);
	अगर (cur_parent == PLL_MODE_NORM) अणु
		pll_mux_ops->set_parent(&pll_mux->hw, PLL_MODE_SLOW);
		rate_change_remuxed = 1;
	पूर्ण

	/* enter reset mode */
	ग_लिखोl(HIWORD_UPDATE(RK3066_PLLCON3_RESET, RK3066_PLLCON3_RESET, 0),
	       pll->reg_base + RK3066_PLLCON(3));

	/* update pll values */
	ग_लिखोl(HIWORD_UPDATE(rate->nr - 1, RK3066_PLLCON0_NR_MASK,
					   RK3066_PLLCON0_NR_SHIFT) |
	       HIWORD_UPDATE(rate->no - 1, RK3066_PLLCON0_OD_MASK,
					   RK3066_PLLCON0_OD_SHIFT),
	       pll->reg_base + RK3066_PLLCON(0));

	ग_लिखोl_relaxed(HIWORD_UPDATE(rate->nf - 1, RK3066_PLLCON1_NF_MASK,
						   RK3066_PLLCON1_NF_SHIFT),
		       pll->reg_base + RK3066_PLLCON(1));
	ग_लिखोl_relaxed(HIWORD_UPDATE(rate->nb - 1, RK3066_PLLCON2_NB_MASK,
						   RK3066_PLLCON2_NB_SHIFT),
		       pll->reg_base + RK3066_PLLCON(2));

	/* leave reset and रुको the reset_delay */
	ग_लिखोl(HIWORD_UPDATE(0, RK3066_PLLCON3_RESET, 0),
	       pll->reg_base + RK3066_PLLCON(3));
	udelay(RK3066_PLL_RESET_DELAY(rate->nr));

	/* रुको क्रम the pll to lock */
	ret = rockchip_pll_रुको_lock(pll);
	अगर (ret) अणु
		pr_warn("%s: pll update unsuccessful, trying to restore old params\n",
			__func__);
		rockchip_rk3066_pll_set_params(pll, &cur);
	पूर्ण

	अगर (rate_change_remuxed)
		pll_mux_ops->set_parent(&pll_mux->hw, PLL_MODE_NORM);

	वापस ret;
पूर्ण

अटल पूर्णांक rockchip_rk3066_pll_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ drate,
					अचिन्हित दीर्घ prate)
अणु
	काष्ठा rockchip_clk_pll *pll = to_rockchip_clk_pll(hw);
	स्थिर काष्ठा rockchip_pll_rate_table *rate;

	pr_debug("%s: changing %s to %lu with a parent rate of %lu\n",
		 __func__, clk_hw_get_name(hw), drate, prate);

	/* Get required rate settings from table */
	rate = rockchip_get_pll_settings(pll, drate);
	अगर (!rate) अणु
		pr_err("%s: Invalid rate : %lu for pll clk %s\n", __func__,
			drate, clk_hw_get_name(hw));
		वापस -EINVAL;
	पूर्ण

	वापस rockchip_rk3066_pll_set_params(pll, rate);
पूर्ण

अटल पूर्णांक rockchip_rk3066_pll_enable(काष्ठा clk_hw *hw)
अणु
	काष्ठा rockchip_clk_pll *pll = to_rockchip_clk_pll(hw);

	ग_लिखोl(HIWORD_UPDATE(0, RK3066_PLLCON3_PWRDOWN, 0),
	       pll->reg_base + RK3066_PLLCON(3));
	rockchip_pll_रुको_lock(pll);

	वापस 0;
पूर्ण

अटल व्योम rockchip_rk3066_pll_disable(काष्ठा clk_hw *hw)
अणु
	काष्ठा rockchip_clk_pll *pll = to_rockchip_clk_pll(hw);

	ग_लिखोl(HIWORD_UPDATE(RK3066_PLLCON3_PWRDOWN,
			     RK3066_PLLCON3_PWRDOWN, 0),
	       pll->reg_base + RK3066_PLLCON(3));
पूर्ण

अटल पूर्णांक rockchip_rk3066_pll_is_enabled(काष्ठा clk_hw *hw)
अणु
	काष्ठा rockchip_clk_pll *pll = to_rockchip_clk_pll(hw);
	u32 pllcon = पढ़ोl(pll->reg_base + RK3066_PLLCON(3));

	वापस !(pllcon & RK3066_PLLCON3_PWRDOWN);
पूर्ण

अटल पूर्णांक rockchip_rk3066_pll_init(काष्ठा clk_hw *hw)
अणु
	काष्ठा rockchip_clk_pll *pll = to_rockchip_clk_pll(hw);
	स्थिर काष्ठा rockchip_pll_rate_table *rate;
	काष्ठा rockchip_pll_rate_table cur;
	अचिन्हित दीर्घ drate;

	अगर (!(pll->flags & ROCKCHIP_PLL_SYNC_RATE))
		वापस 0;

	drate = clk_hw_get_rate(hw);
	rate = rockchip_get_pll_settings(pll, drate);

	/* when no rate setting क्रम the current rate, rely on clk_set_rate */
	अगर (!rate)
		वापस 0;

	rockchip_rk3066_pll_get_params(pll, &cur);

	pr_debug("%s: pll %s@%lu: nr (%d:%d); no (%d:%d); nf(%d:%d), nb(%d:%d)\n",
		 __func__, clk_hw_get_name(hw), drate, rate->nr, cur.nr,
		 rate->no, cur.no, rate->nf, cur.nf, rate->nb, cur.nb);
	अगर (rate->nr != cur.nr || rate->no != cur.no || rate->nf != cur.nf
						     || rate->nb != cur.nb) अणु
		pr_debug("%s: pll %s: rate params do not match rate table, adjusting\n",
			 __func__, clk_hw_get_name(hw));
		rockchip_rk3066_pll_set_params(pll, rate);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा clk_ops rockchip_rk3066_pll_clk_norate_ops = अणु
	.recalc_rate = rockchip_rk3066_pll_recalc_rate,
	.enable = rockchip_rk3066_pll_enable,
	.disable = rockchip_rk3066_pll_disable,
	.is_enabled = rockchip_rk3066_pll_is_enabled,
पूर्ण;

अटल स्थिर काष्ठा clk_ops rockchip_rk3066_pll_clk_ops = अणु
	.recalc_rate = rockchip_rk3066_pll_recalc_rate,
	.round_rate = rockchip_pll_round_rate,
	.set_rate = rockchip_rk3066_pll_set_rate,
	.enable = rockchip_rk3066_pll_enable,
	.disable = rockchip_rk3066_pll_disable,
	.is_enabled = rockchip_rk3066_pll_is_enabled,
	.init = rockchip_rk3066_pll_init,
पूर्ण;

/*
 * PLL used in RK3399
 */

#घोषणा RK3399_PLLCON(i)			(i * 0x4)
#घोषणा RK3399_PLLCON0_FBDIV_MASK		0xfff
#घोषणा RK3399_PLLCON0_FBDIV_SHIFT		0
#घोषणा RK3399_PLLCON1_REFDIV_MASK		0x3f
#घोषणा RK3399_PLLCON1_REFDIV_SHIFT		0
#घोषणा RK3399_PLLCON1_POSTDIV1_MASK		0x7
#घोषणा RK3399_PLLCON1_POSTDIV1_SHIFT		8
#घोषणा RK3399_PLLCON1_POSTDIV2_MASK		0x7
#घोषणा RK3399_PLLCON1_POSTDIV2_SHIFT		12
#घोषणा RK3399_PLLCON2_FRAC_MASK		0xffffff
#घोषणा RK3399_PLLCON2_FRAC_SHIFT		0
#घोषणा RK3399_PLLCON2_LOCK_STATUS		BIT(31)
#घोषणा RK3399_PLLCON3_PWRDOWN			BIT(0)
#घोषणा RK3399_PLLCON3_DSMPD_MASK		0x1
#घोषणा RK3399_PLLCON3_DSMPD_SHIFT		3

अटल पूर्णांक rockchip_rk3399_pll_रुको_lock(काष्ठा rockchip_clk_pll *pll)
अणु
	u32 pllcon;
	पूर्णांक ret;

	/*
	 * Lock समय typical 250, max 500 input घड़ी cycles @24MHz
	 * So define a very safe maximum of 1000us, meaning 24000 cycles.
	 */
	ret = पढ़ोl_relaxed_poll_समयout(pll->reg_base + RK3399_PLLCON(2),
					 pllcon,
					 pllcon & RK3399_PLLCON2_LOCK_STATUS,
					 0, 1000);
	अगर (ret)
		pr_err("%s: timeout waiting for pll to lock\n", __func__);

	वापस ret;
पूर्ण

अटल व्योम rockchip_rk3399_pll_get_params(काष्ठा rockchip_clk_pll *pll,
					काष्ठा rockchip_pll_rate_table *rate)
अणु
	u32 pllcon;

	pllcon = पढ़ोl_relaxed(pll->reg_base + RK3399_PLLCON(0));
	rate->fbभाग = ((pllcon >> RK3399_PLLCON0_FBDIV_SHIFT)
				& RK3399_PLLCON0_FBDIV_MASK);

	pllcon = पढ़ोl_relaxed(pll->reg_base + RK3399_PLLCON(1));
	rate->refभाग = ((pllcon >> RK3399_PLLCON1_REFDIV_SHIFT)
				& RK3399_PLLCON1_REFDIV_MASK);
	rate->postभाग1 = ((pllcon >> RK3399_PLLCON1_POSTDIV1_SHIFT)
				& RK3399_PLLCON1_POSTDIV1_MASK);
	rate->postभाग2 = ((pllcon >> RK3399_PLLCON1_POSTDIV2_SHIFT)
				& RK3399_PLLCON1_POSTDIV2_MASK);

	pllcon = पढ़ोl_relaxed(pll->reg_base + RK3399_PLLCON(2));
	rate->frac = ((pllcon >> RK3399_PLLCON2_FRAC_SHIFT)
				& RK3399_PLLCON2_FRAC_MASK);

	pllcon = पढ़ोl_relaxed(pll->reg_base + RK3399_PLLCON(3));
	rate->dsmpd = ((pllcon >> RK3399_PLLCON3_DSMPD_SHIFT)
				& RK3399_PLLCON3_DSMPD_MASK);
पूर्ण

अटल अचिन्हित दीर्घ rockchip_rk3399_pll_recalc_rate(काष्ठा clk_hw *hw,
						     अचिन्हित दीर्घ prate)
अणु
	काष्ठा rockchip_clk_pll *pll = to_rockchip_clk_pll(hw);
	काष्ठा rockchip_pll_rate_table cur;
	u64 rate64 = prate;

	rockchip_rk3399_pll_get_params(pll, &cur);

	rate64 *= cur.fbभाग;
	करो_भाग(rate64, cur.refभाग);

	अगर (cur.dsmpd == 0) अणु
		/* fractional mode */
		u64 frac_rate64 = prate * cur.frac;

		करो_भाग(frac_rate64, cur.refभाग);
		rate64 += frac_rate64 >> 24;
	पूर्ण

	करो_भाग(rate64, cur.postभाग1);
	करो_भाग(rate64, cur.postभाग2);

	वापस (अचिन्हित दीर्घ)rate64;
पूर्ण

अटल पूर्णांक rockchip_rk3399_pll_set_params(काष्ठा rockchip_clk_pll *pll,
				स्थिर काष्ठा rockchip_pll_rate_table *rate)
अणु
	स्थिर काष्ठा clk_ops *pll_mux_ops = pll->pll_mux_ops;
	काष्ठा clk_mux *pll_mux = &pll->pll_mux;
	काष्ठा rockchip_pll_rate_table cur;
	u32 pllcon;
	पूर्णांक rate_change_remuxed = 0;
	पूर्णांक cur_parent;
	पूर्णांक ret;

	pr_debug("%s: rate settings for %lu fbdiv: %d, postdiv1: %d, refdiv: %d, postdiv2: %d, dsmpd: %d, frac: %d\n",
		__func__, rate->rate, rate->fbभाग, rate->postभाग1, rate->refभाग,
		rate->postभाग2, rate->dsmpd, rate->frac);

	rockchip_rk3399_pll_get_params(pll, &cur);
	cur.rate = 0;

	cur_parent = pll_mux_ops->get_parent(&pll_mux->hw);
	अगर (cur_parent == PLL_MODE_NORM) अणु
		pll_mux_ops->set_parent(&pll_mux->hw, PLL_MODE_SLOW);
		rate_change_remuxed = 1;
	पूर्ण

	/* update pll values */
	ग_लिखोl_relaxed(HIWORD_UPDATE(rate->fbभाग, RK3399_PLLCON0_FBDIV_MASK,
						  RK3399_PLLCON0_FBDIV_SHIFT),
		       pll->reg_base + RK3399_PLLCON(0));

	ग_लिखोl_relaxed(HIWORD_UPDATE(rate->refभाग, RK3399_PLLCON1_REFDIV_MASK,
						   RK3399_PLLCON1_REFDIV_SHIFT) |
		       HIWORD_UPDATE(rate->postभाग1, RK3399_PLLCON1_POSTDIV1_MASK,
						     RK3399_PLLCON1_POSTDIV1_SHIFT) |
		       HIWORD_UPDATE(rate->postभाग2, RK3399_PLLCON1_POSTDIV2_MASK,
						     RK3399_PLLCON1_POSTDIV2_SHIFT),
		       pll->reg_base + RK3399_PLLCON(1));

	/* xPLL CON2 is not HIWORD_MASK */
	pllcon = पढ़ोl_relaxed(pll->reg_base + RK3399_PLLCON(2));
	pllcon &= ~(RK3399_PLLCON2_FRAC_MASK << RK3399_PLLCON2_FRAC_SHIFT);
	pllcon |= rate->frac << RK3399_PLLCON2_FRAC_SHIFT;
	ग_लिखोl_relaxed(pllcon, pll->reg_base + RK3399_PLLCON(2));

	ग_लिखोl_relaxed(HIWORD_UPDATE(rate->dsmpd, RK3399_PLLCON3_DSMPD_MASK,
					    RK3399_PLLCON3_DSMPD_SHIFT),
		       pll->reg_base + RK3399_PLLCON(3));

	/* रुको क्रम the pll to lock */
	ret = rockchip_rk3399_pll_रुको_lock(pll);
	अगर (ret) अणु
		pr_warn("%s: pll update unsuccessful, trying to restore old params\n",
			__func__);
		rockchip_rk3399_pll_set_params(pll, &cur);
	पूर्ण

	अगर (rate_change_remuxed)
		pll_mux_ops->set_parent(&pll_mux->hw, PLL_MODE_NORM);

	वापस ret;
पूर्ण

अटल पूर्णांक rockchip_rk3399_pll_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ drate,
					अचिन्हित दीर्घ prate)
अणु
	काष्ठा rockchip_clk_pll *pll = to_rockchip_clk_pll(hw);
	स्थिर काष्ठा rockchip_pll_rate_table *rate;

	pr_debug("%s: changing %s to %lu with a parent rate of %lu\n",
		 __func__, __clk_get_name(hw->clk), drate, prate);

	/* Get required rate settings from table */
	rate = rockchip_get_pll_settings(pll, drate);
	अगर (!rate) अणु
		pr_err("%s: Invalid rate : %lu for pll clk %s\n", __func__,
			drate, __clk_get_name(hw->clk));
		वापस -EINVAL;
	पूर्ण

	वापस rockchip_rk3399_pll_set_params(pll, rate);
पूर्ण

अटल पूर्णांक rockchip_rk3399_pll_enable(काष्ठा clk_hw *hw)
अणु
	काष्ठा rockchip_clk_pll *pll = to_rockchip_clk_pll(hw);

	ग_लिखोl(HIWORD_UPDATE(0, RK3399_PLLCON3_PWRDOWN, 0),
	       pll->reg_base + RK3399_PLLCON(3));
	rockchip_rk3399_pll_रुको_lock(pll);

	वापस 0;
पूर्ण

अटल व्योम rockchip_rk3399_pll_disable(काष्ठा clk_hw *hw)
अणु
	काष्ठा rockchip_clk_pll *pll = to_rockchip_clk_pll(hw);

	ग_लिखोl(HIWORD_UPDATE(RK3399_PLLCON3_PWRDOWN,
			     RK3399_PLLCON3_PWRDOWN, 0),
	       pll->reg_base + RK3399_PLLCON(3));
पूर्ण

अटल पूर्णांक rockchip_rk3399_pll_is_enabled(काष्ठा clk_hw *hw)
अणु
	काष्ठा rockchip_clk_pll *pll = to_rockchip_clk_pll(hw);
	u32 pllcon = पढ़ोl(pll->reg_base + RK3399_PLLCON(3));

	वापस !(pllcon & RK3399_PLLCON3_PWRDOWN);
पूर्ण

अटल पूर्णांक rockchip_rk3399_pll_init(काष्ठा clk_hw *hw)
अणु
	काष्ठा rockchip_clk_pll *pll = to_rockchip_clk_pll(hw);
	स्थिर काष्ठा rockchip_pll_rate_table *rate;
	काष्ठा rockchip_pll_rate_table cur;
	अचिन्हित दीर्घ drate;

	अगर (!(pll->flags & ROCKCHIP_PLL_SYNC_RATE))
		वापस 0;

	drate = clk_hw_get_rate(hw);
	rate = rockchip_get_pll_settings(pll, drate);

	/* when no rate setting क्रम the current rate, rely on clk_set_rate */
	अगर (!rate)
		वापस 0;

	rockchip_rk3399_pll_get_params(pll, &cur);

	pr_debug("%s: pll %s@%lu: Hz\n", __func__, __clk_get_name(hw->clk),
		 drate);
	pr_debug("old - fbdiv: %d, postdiv1: %d, refdiv: %d, postdiv2: %d, dsmpd: %d, frac: %d\n",
		 cur.fbभाग, cur.postभाग1, cur.refभाग, cur.postभाग2,
		 cur.dsmpd, cur.frac);
	pr_debug("new - fbdiv: %d, postdiv1: %d, refdiv: %d, postdiv2: %d, dsmpd: %d, frac: %d\n",
		 rate->fbभाग, rate->postभाग1, rate->refभाग, rate->postभाग2,
		 rate->dsmpd, rate->frac);

	अगर (rate->fbभाग != cur.fbभाग || rate->postभाग1 != cur.postभाग1 ||
		rate->refभाग != cur.refभाग || rate->postभाग2 != cur.postभाग2 ||
		rate->dsmpd != cur.dsmpd ||
		(!cur.dsmpd && (rate->frac != cur.frac))) अणु
		काष्ठा clk *parent = clk_get_parent(hw->clk);

		अगर (!parent) अणु
			pr_warn("%s: parent of %s not available\n",
				__func__, __clk_get_name(hw->clk));
			वापस 0;
		पूर्ण

		pr_debug("%s: pll %s: rate params do not match rate table, adjusting\n",
			 __func__, __clk_get_name(hw->clk));
		rockchip_rk3399_pll_set_params(pll, rate);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा clk_ops rockchip_rk3399_pll_clk_norate_ops = अणु
	.recalc_rate = rockchip_rk3399_pll_recalc_rate,
	.enable = rockchip_rk3399_pll_enable,
	.disable = rockchip_rk3399_pll_disable,
	.is_enabled = rockchip_rk3399_pll_is_enabled,
पूर्ण;

अटल स्थिर काष्ठा clk_ops rockchip_rk3399_pll_clk_ops = अणु
	.recalc_rate = rockchip_rk3399_pll_recalc_rate,
	.round_rate = rockchip_pll_round_rate,
	.set_rate = rockchip_rk3399_pll_set_rate,
	.enable = rockchip_rk3399_pll_enable,
	.disable = rockchip_rk3399_pll_disable,
	.is_enabled = rockchip_rk3399_pll_is_enabled,
	.init = rockchip_rk3399_pll_init,
पूर्ण;

/*
 * Common रेजिस्टरing of pll घड़ीs
 */

काष्ठा clk *rockchip_clk_रेजिस्टर_pll(काष्ठा rockchip_clk_provider *ctx,
		क्रमागत rockchip_pll_type pll_type,
		स्थिर अक्षर *name, स्थिर अक्षर *स्थिर *parent_names,
		u8 num_parents, पूर्णांक con_offset, पूर्णांक grf_lock_offset,
		पूर्णांक lock_shअगरt, पूर्णांक mode_offset, पूर्णांक mode_shअगरt,
		काष्ठा rockchip_pll_rate_table *rate_table,
		अचिन्हित दीर्घ flags, u8 clk_pll_flags)
अणु
	स्थिर अक्षर *pll_parents[3];
	काष्ठा clk_init_data init;
	काष्ठा rockchip_clk_pll *pll;
	काष्ठा clk_mux *pll_mux;
	काष्ठा clk *pll_clk, *mux_clk;
	अक्षर pll_name[20];

	अगर ((pll_type != pll_rk3328 && num_parents != 2) ||
	    (pll_type == pll_rk3328 && num_parents != 1)) अणु
		pr_err("%s: needs two parent clocks\n", __func__);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	/* name the actual pll */
	snम_लिखो(pll_name, माप(pll_name), "pll_%s", name);

	pll = kzalloc(माप(*pll), GFP_KERNEL);
	अगर (!pll)
		वापस ERR_PTR(-ENOMEM);

	/* create the mux on top of the real pll */
	pll->pll_mux_ops = &clk_mux_ops;
	pll_mux = &pll->pll_mux;
	pll_mux->reg = ctx->reg_base + mode_offset;
	pll_mux->shअगरt = mode_shअगरt;
	अगर (pll_type == pll_rk3328)
		pll_mux->mask = PLL_RK3328_MODE_MASK;
	अन्यथा
		pll_mux->mask = PLL_MODE_MASK;
	pll_mux->flags = 0;
	pll_mux->lock = &ctx->lock;
	pll_mux->hw.init = &init;

	अगर (pll_type == pll_rk3036 ||
	    pll_type == pll_rk3066 ||
	    pll_type == pll_rk3328 ||
	    pll_type == pll_rk3399)
		pll_mux->flags |= CLK_MUX_HIWORD_MASK;

	/* the actual muxing is xin24m, pll-output, xin32k */
	pll_parents[0] = parent_names[0];
	pll_parents[1] = pll_name;
	pll_parents[2] = parent_names[1];

	init.name = name;
	init.flags = CLK_SET_RATE_PARENT;
	init.ops = pll->pll_mux_ops;
	init.parent_names = pll_parents;
	अगर (pll_type == pll_rk3328)
		init.num_parents = 2;
	अन्यथा
		init.num_parents = ARRAY_SIZE(pll_parents);

	mux_clk = clk_रेजिस्टर(शून्य, &pll_mux->hw);
	अगर (IS_ERR(mux_clk))
		जाओ err_mux;

	/* now create the actual pll */
	init.name = pll_name;

	/* keep all plls untouched क्रम now */
	init.flags = flags | CLK_IGNORE_UNUSED;

	init.parent_names = &parent_names[0];
	init.num_parents = 1;

	अगर (rate_table) अणु
		पूर्णांक len;

		/* find count of rates in rate_table */
		क्रम (len = 0; rate_table[len].rate != 0; )
			len++;

		pll->rate_count = len;
		pll->rate_table = kmemdup(rate_table,
					pll->rate_count *
					माप(काष्ठा rockchip_pll_rate_table),
					GFP_KERNEL);
		WARN(!pll->rate_table,
			"%s: could not allocate rate table for %s\n",
			__func__, name);
	पूर्ण

	चयन (pll_type) अणु
	हाल pll_rk3036:
	हाल pll_rk3328:
		अगर (!pll->rate_table || IS_ERR(ctx->grf))
			init.ops = &rockchip_rk3036_pll_clk_norate_ops;
		अन्यथा
			init.ops = &rockchip_rk3036_pll_clk_ops;
		अवरोध;
	हाल pll_rk3066:
		अगर (!pll->rate_table || IS_ERR(ctx->grf))
			init.ops = &rockchip_rk3066_pll_clk_norate_ops;
		अन्यथा
			init.ops = &rockchip_rk3066_pll_clk_ops;
		अवरोध;
	हाल pll_rk3399:
		अगर (!pll->rate_table)
			init.ops = &rockchip_rk3399_pll_clk_norate_ops;
		अन्यथा
			init.ops = &rockchip_rk3399_pll_clk_ops;
		अवरोध;
	शेष:
		pr_warn("%s: Unknown pll type for pll clk %s\n",
			__func__, name);
	पूर्ण

	pll->hw.init = &init;
	pll->type = pll_type;
	pll->reg_base = ctx->reg_base + con_offset;
	pll->lock_offset = grf_lock_offset;
	pll->lock_shअगरt = lock_shअगरt;
	pll->flags = clk_pll_flags;
	pll->lock = &ctx->lock;
	pll->ctx = ctx;

	pll_clk = clk_रेजिस्टर(शून्य, &pll->hw);
	अगर (IS_ERR(pll_clk)) अणु
		pr_err("%s: failed to register pll clock %s : %ld\n",
			__func__, name, PTR_ERR(pll_clk));
		जाओ err_pll;
	पूर्ण

	वापस mux_clk;

err_pll:
	clk_unरेजिस्टर(mux_clk);
	mux_clk = pll_clk;
err_mux:
	kमुक्त(pll);
	वापस mux_clk;
पूर्ण
