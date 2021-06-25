<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2015 Endless Mobile, Inc.
 * Author: Carlo Caione <carlo@endlessm.com>
 *
 * Copyright (c) 2018 Baylibre, SAS.
 * Author: Jerome Brunet <jbrunet@baylibre.com>
 */

/*
 * In the most basic क्रमm, a Meson PLL is composed as follows:
 *
 *                     PLL
 *        +--------------------------------+
 *        |                                |
 *        |             +--+               |
 *  in >>-----[ /N ]--->|  |      +-----+  |
 *        |             |  |------| DCO |---->> out
 *        |  +--------->|  |      +--v--+  |
 *        |  |          +--+         |     |
 *        |  |                       |     |
 *        |  +--[ *(M + (F/Fmax) ]<--+     |
 *        |                                |
 *        +--------------------------------+
 *
 * out = in * (m + frac / frac_max) / n
 */

#समावेश <linux/clk-provider.h>
#समावेश <linux/delay.h>
#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/math64.h>
#समावेश <linux/module.h>
#समावेश <linux/rational.h>

#समावेश "clk-regmap.h"
#समावेश "clk-pll.h"

अटल अंतरभूत काष्ठा meson_clk_pll_data *
meson_clk_pll_data(काष्ठा clk_regmap *clk)
अणु
	वापस (काष्ठा meson_clk_pll_data *)clk->data;
पूर्ण

अटल पूर्णांक __pll_round_बंदst_mult(काष्ठा meson_clk_pll_data *pll)
अणु
	अगर ((pll->flags & CLK_MESON_PLL_ROUND_CLOSEST) &&
	    !MESON_PARM_APPLICABLE(&pll->frac))
		वापस 1;

	वापस 0;
पूर्ण

अटल अचिन्हित दीर्घ __pll_params_to_rate(अचिन्हित दीर्घ parent_rate,
					  अचिन्हित पूर्णांक m, अचिन्हित पूर्णांक n,
					  अचिन्हित पूर्णांक frac,
					  काष्ठा meson_clk_pll_data *pll)
अणु
	u64 rate = (u64)parent_rate * m;

	अगर (frac && MESON_PARM_APPLICABLE(&pll->frac)) अणु
		u64 frac_rate = (u64)parent_rate * frac;

		rate += DIV_ROUND_UP_ULL(frac_rate,
					 (1 << pll->frac.width));
	पूर्ण

	वापस DIV_ROUND_UP_ULL(rate, n);
पूर्ण

अटल अचिन्हित दीर्घ meson_clk_pll_recalc_rate(काष्ठा clk_hw *hw,
						अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा clk_regmap *clk = to_clk_regmap(hw);
	काष्ठा meson_clk_pll_data *pll = meson_clk_pll_data(clk);
	अचिन्हित पूर्णांक m, n, frac;

	n = meson_parm_पढ़ो(clk->map, &pll->n);

	/*
	 * On some HW, N is set to zero on init. This value is invalid as
	 * it would result in a भागision by zero. The rate can't be
	 * calculated in this हाल
	 */
	अगर (n == 0)
		वापस 0;

	m = meson_parm_पढ़ो(clk->map, &pll->m);

	frac = MESON_PARM_APPLICABLE(&pll->frac) ?
		meson_parm_पढ़ो(clk->map, &pll->frac) :
		0;

	वापस __pll_params_to_rate(parent_rate, m, n, frac, pll);
पूर्ण

अटल अचिन्हित पूर्णांक __pll_params_with_frac(अचिन्हित दीर्घ rate,
					   अचिन्हित दीर्घ parent_rate,
					   अचिन्हित पूर्णांक m,
					   अचिन्हित पूर्णांक n,
					   काष्ठा meson_clk_pll_data *pll)
अणु
	अचिन्हित पूर्णांक frac_max = (1 << pll->frac.width);
	u64 val = (u64)rate * n;

	/* Bail out अगर we are alपढ़ोy over the requested rate */
	अगर (rate < parent_rate * m / n)
		वापस 0;

	अगर (pll->flags & CLK_MESON_PLL_ROUND_CLOSEST)
		val = DIV_ROUND_CLOSEST_ULL(val * frac_max, parent_rate);
	अन्यथा
		val = भाग_u64(val * frac_max, parent_rate);

	val -= m * frac_max;

	वापस min((अचिन्हित पूर्णांक)val, (frac_max - 1));
पूर्ण

अटल bool meson_clk_pll_is_better(अचिन्हित दीर्घ rate,
				    अचिन्हित दीर्घ best,
				    अचिन्हित दीर्घ now,
				    काष्ठा meson_clk_pll_data *pll)
अणु
	अगर (__pll_round_बंदst_mult(pll)) अणु
		/* Round Closest */
		अगर (असल(now - rate) < असल(best - rate))
			वापस true;
	पूर्ण अन्यथा अणु
		/* Round करोwn */
		अगर (now <= rate && best < now)
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल पूर्णांक meson_clk_get_pll_table_index(अचिन्हित पूर्णांक index,
					 अचिन्हित पूर्णांक *m,
					 अचिन्हित पूर्णांक *n,
					 काष्ठा meson_clk_pll_data *pll)
अणु
	अगर (!pll->table[index].n)
		वापस -EINVAL;

	*m = pll->table[index].m;
	*n = pll->table[index].n;

	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक meson_clk_get_pll_range_m(अचिन्हित दीर्घ rate,
					      अचिन्हित दीर्घ parent_rate,
					      अचिन्हित पूर्णांक n,
					      काष्ठा meson_clk_pll_data *pll)
अणु
	u64 val = (u64)rate * n;

	अगर (__pll_round_बंदst_mult(pll))
		वापस DIV_ROUND_CLOSEST_ULL(val, parent_rate);

	वापस भाग_u64(val,  parent_rate);
पूर्ण

अटल पूर्णांक meson_clk_get_pll_range_index(अचिन्हित दीर्घ rate,
					 अचिन्हित दीर्घ parent_rate,
					 अचिन्हित पूर्णांक index,
					 अचिन्हित पूर्णांक *m,
					 अचिन्हित पूर्णांक *n,
					 काष्ठा meson_clk_pll_data *pll)
अणु
	*n = index + 1;

	/* Check the preभागider range */
	अगर (*n >= (1 << pll->n.width))
		वापस -EINVAL;

	अगर (*n == 1) अणु
		/* Get the boundaries out the way */
		अगर (rate <= pll->range->min * parent_rate) अणु
			*m = pll->range->min;
			वापस -ENODATA;
		पूर्ण अन्यथा अगर (rate >= pll->range->max * parent_rate) अणु
			*m = pll->range->max;
			वापस -ENODATA;
		पूर्ण
	पूर्ण

	*m = meson_clk_get_pll_range_m(rate, parent_rate, *n, pll);

	/* the pre-भागider gives a multiplier too big - stop */
	अगर (*m >= (1 << pll->m.width))
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक meson_clk_get_pll_get_index(अचिन्हित दीर्घ rate,
				       अचिन्हित दीर्घ parent_rate,
				       अचिन्हित पूर्णांक index,
				       अचिन्हित पूर्णांक *m,
				       अचिन्हित पूर्णांक *n,
				       काष्ठा meson_clk_pll_data *pll)
अणु
	अगर (pll->range)
		वापस meson_clk_get_pll_range_index(rate, parent_rate,
						     index, m, n, pll);
	अन्यथा अगर (pll->table)
		वापस meson_clk_get_pll_table_index(index, m, n, pll);

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक meson_clk_get_pll_settings(अचिन्हित दीर्घ rate,
				      अचिन्हित दीर्घ parent_rate,
				      अचिन्हित पूर्णांक *best_m,
				      अचिन्हित पूर्णांक *best_n,
				      काष्ठा meson_clk_pll_data *pll)
अणु
	अचिन्हित दीर्घ best = 0, now = 0;
	अचिन्हित पूर्णांक i, m, n;
	पूर्णांक ret;

	क्रम (i = 0, ret = 0; !ret; i++) अणु
		ret = meson_clk_get_pll_get_index(rate, parent_rate,
						  i, &m, &n, pll);
		अगर (ret == -EINVAL)
			अवरोध;

		now = __pll_params_to_rate(parent_rate, m, n, 0, pll);
		अगर (meson_clk_pll_is_better(rate, best, now, pll)) अणु
			best = now;
			*best_m = m;
			*best_n = n;

			अगर (now == rate)
				अवरोध;
		पूर्ण
	पूर्ण

	वापस best ? 0 : -EINVAL;
पूर्ण

अटल दीर्घ meson_clk_pll_round_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				     अचिन्हित दीर्घ *parent_rate)
अणु
	काष्ठा clk_regmap *clk = to_clk_regmap(hw);
	काष्ठा meson_clk_pll_data *pll = meson_clk_pll_data(clk);
	अचिन्हित पूर्णांक m, n, frac;
	अचिन्हित दीर्घ round;
	पूर्णांक ret;

	ret = meson_clk_get_pll_settings(rate, *parent_rate, &m, &n, pll);
	अगर (ret)
		वापस meson_clk_pll_recalc_rate(hw, *parent_rate);

	round = __pll_params_to_rate(*parent_rate, m, n, 0, pll);

	अगर (!MESON_PARM_APPLICABLE(&pll->frac) || rate == round)
		वापस round;

	/*
	 * The rate provided by the setting is not an exact match, let's
	 * try to improve the result using the fractional parameter
	 */
	frac = __pll_params_with_frac(rate, *parent_rate, m, n, pll);

	वापस __pll_params_to_rate(*parent_rate, m, n, frac, pll);
पूर्ण

अटल पूर्णांक meson_clk_pll_रुको_lock(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_regmap *clk = to_clk_regmap(hw);
	काष्ठा meson_clk_pll_data *pll = meson_clk_pll_data(clk);
	पूर्णांक delay = 24000000;

	करो अणु
		/* Is the घड़ी locked now ? */
		अगर (meson_parm_पढ़ो(clk->map, &pll->l))
			वापस 0;

		delay--;
	पूर्ण जबतक (delay > 0);

	वापस -ETIMEDOUT;
पूर्ण

अटल पूर्णांक meson_clk_pll_init(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_regmap *clk = to_clk_regmap(hw);
	काष्ठा meson_clk_pll_data *pll = meson_clk_pll_data(clk);

	अगर (pll->init_count) अणु
		meson_parm_ग_लिखो(clk->map, &pll->rst, 1);
		regmap_multi_reg_ग_लिखो(clk->map, pll->init_regs,
				       pll->init_count);
		meson_parm_ग_लिखो(clk->map, &pll->rst, 0);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक meson_clk_pll_is_enabled(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_regmap *clk = to_clk_regmap(hw);
	काष्ठा meson_clk_pll_data *pll = meson_clk_pll_data(clk);

	अगर (meson_parm_पढ़ो(clk->map, &pll->rst) ||
	    !meson_parm_पढ़ो(clk->map, &pll->en) ||
	    !meson_parm_पढ़ो(clk->map, &pll->l))
		वापस 0;

	वापस 1;
पूर्ण

अटल पूर्णांक meson_clk_pcie_pll_enable(काष्ठा clk_hw *hw)
अणु
	meson_clk_pll_init(hw);

	अगर (meson_clk_pll_रुको_lock(hw))
		वापस -EIO;

	वापस 0;
पूर्ण

अटल पूर्णांक meson_clk_pll_enable(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_regmap *clk = to_clk_regmap(hw);
	काष्ठा meson_clk_pll_data *pll = meson_clk_pll_data(clk);

	/* करो nothing अगर the PLL is alपढ़ोy enabled */
	अगर (clk_hw_is_enabled(hw))
		वापस 0;

	/* Make sure the pll is in reset */
	meson_parm_ग_लिखो(clk->map, &pll->rst, 1);

	/* Enable the pll */
	meson_parm_ग_लिखो(clk->map, &pll->en, 1);

	/* Take the pll out reset */
	meson_parm_ग_लिखो(clk->map, &pll->rst, 0);

	अगर (meson_clk_pll_रुको_lock(hw))
		वापस -EIO;

	वापस 0;
पूर्ण

अटल व्योम meson_clk_pll_disable(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_regmap *clk = to_clk_regmap(hw);
	काष्ठा meson_clk_pll_data *pll = meson_clk_pll_data(clk);

	/* Put the pll is in reset */
	meson_parm_ग_लिखो(clk->map, &pll->rst, 1);

	/* Disable the pll */
	meson_parm_ग_लिखो(clk->map, &pll->en, 0);
पूर्ण

अटल पूर्णांक meson_clk_pll_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				  अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा clk_regmap *clk = to_clk_regmap(hw);
	काष्ठा meson_clk_pll_data *pll = meson_clk_pll_data(clk);
	अचिन्हित पूर्णांक enabled, m, n, frac = 0;
	अचिन्हित दीर्घ old_rate;
	पूर्णांक ret;

	अगर (parent_rate == 0 || rate == 0)
		वापस -EINVAL;

	old_rate = clk_hw_get_rate(hw);

	ret = meson_clk_get_pll_settings(rate, parent_rate, &m, &n, pll);
	अगर (ret)
		वापस ret;

	enabled = meson_parm_पढ़ो(clk->map, &pll->en);
	अगर (enabled)
		meson_clk_pll_disable(hw);

	meson_parm_ग_लिखो(clk->map, &pll->n, n);
	meson_parm_ग_लिखो(clk->map, &pll->m, m);

	अगर (MESON_PARM_APPLICABLE(&pll->frac)) अणु
		frac = __pll_params_with_frac(rate, parent_rate, m, n, pll);
		meson_parm_ग_लिखो(clk->map, &pll->frac, frac);
	पूर्ण

	/* If the pll is stopped, bail out now */
	अगर (!enabled)
		वापस 0;

	ret = meson_clk_pll_enable(hw);
	अगर (ret) अणु
		pr_warn("%s: pll did not lock, trying to restore old rate %lu\n",
			__func__, old_rate);
		/*
		 * FIXME: Do we really need/want this HACK ?
		 * It looks unsafe. what happens अगर the घड़ी माला_लो पूर्णांकo a
		 * broken state and we can't lock back on the old_rate ? Looks
		 * like an infinite recursion is possible
		 */
		meson_clk_pll_set_rate(hw, old_rate, parent_rate);
	पूर्ण

	वापस ret;
पूर्ण

/*
 * The Meson G12A PCIE PLL is fined tuned to deliver a very precise
 * 100MHz reference घड़ी क्रम the PCIe Analog PHY, and thus requires
 * a strict रेजिस्टर sequence to enable the PLL.
 * To simplअगरy, re-use the _init() op to enable the PLL and keep
 * the other ops except set_rate since the rate is fixed.
 */
स्थिर काष्ठा clk_ops meson_clk_pcie_pll_ops = अणु
	.recalc_rate	= meson_clk_pll_recalc_rate,
	.round_rate	= meson_clk_pll_round_rate,
	.is_enabled	= meson_clk_pll_is_enabled,
	.enable		= meson_clk_pcie_pll_enable,
	.disable	= meson_clk_pll_disable
पूर्ण;
EXPORT_SYMBOL_GPL(meson_clk_pcie_pll_ops);

स्थिर काष्ठा clk_ops meson_clk_pll_ops = अणु
	.init		= meson_clk_pll_init,
	.recalc_rate	= meson_clk_pll_recalc_rate,
	.round_rate	= meson_clk_pll_round_rate,
	.set_rate	= meson_clk_pll_set_rate,
	.is_enabled	= meson_clk_pll_is_enabled,
	.enable		= meson_clk_pll_enable,
	.disable	= meson_clk_pll_disable
पूर्ण;
EXPORT_SYMBOL_GPL(meson_clk_pll_ops);

स्थिर काष्ठा clk_ops meson_clk_pll_ro_ops = अणु
	.recalc_rate	= meson_clk_pll_recalc_rate,
	.is_enabled	= meson_clk_pll_is_enabled,
पूर्ण;
EXPORT_SYMBOL_GPL(meson_clk_pll_ro_ops);

MODULE_DESCRIPTION("Amlogic PLL driver");
MODULE_AUTHOR("Carlo Caione <carlo@endlessm.com>");
MODULE_AUTHOR("Jerome Brunet <jbrunet@baylibre.com>");
MODULE_LICENSE("GPL v2");
