<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0 OR BSD-3-Clause)
/*
 * Copyright (c) 2016 AmLogic, Inc.
 * Author: Michael Turquette <mturquette@baylibre.com>
 */

/*
 * MultiPhase Locked Loops are outमाला_दो from a PLL with additional frequency
 * scaling capabilities. MPLL rates are calculated as:
 *
 * f(N2_पूर्णांकeger, SDM_IN ) = 2.0G/(N2_पूर्णांकeger + SDM_IN/16384)
 */

#समावेश <linux/clk-provider.h>
#समावेश <linux/module.h>
#समावेश <linux/spinlock.h>

#समावेश "clk-regmap.h"
#समावेश "clk-mpll.h"

#घोषणा SDM_DEN 16384
#घोषणा N2_MIN	4
#घोषणा N2_MAX	511

अटल अंतरभूत काष्ठा meson_clk_mpll_data *
meson_clk_mpll_data(काष्ठा clk_regmap *clk)
अणु
	वापस (काष्ठा meson_clk_mpll_data *)clk->data;
पूर्ण

अटल दीर्घ rate_from_params(अचिन्हित दीर्घ parent_rate,
			     अचिन्हित पूर्णांक sdm,
			     अचिन्हित पूर्णांक n2)
अणु
	अचिन्हित दीर्घ भागisor = (SDM_DEN * n2) + sdm;

	अगर (n2 < N2_MIN)
		वापस -EINVAL;

	वापस DIV_ROUND_UP_ULL((u64)parent_rate * SDM_DEN, भागisor);
पूर्ण

अटल व्योम params_from_rate(अचिन्हित दीर्घ requested_rate,
			     अचिन्हित दीर्घ parent_rate,
			     अचिन्हित पूर्णांक *sdm,
			     अचिन्हित पूर्णांक *n2,
			     u8 flags)
अणु
	uपूर्णांक64_t भाग = parent_rate;
	uपूर्णांक64_t frac = करो_भाग(भाग, requested_rate);

	frac *= SDM_DEN;

	अगर (flags & CLK_MESON_MPLL_ROUND_CLOSEST)
		*sdm = DIV_ROUND_CLOSEST_ULL(frac, requested_rate);
	अन्यथा
		*sdm = DIV_ROUND_UP_ULL(frac, requested_rate);

	अगर (*sdm == SDM_DEN) अणु
		*sdm = 0;
		भाग += 1;
	पूर्ण

	अगर (भाग < N2_MIN) अणु
		*n2 = N2_MIN;
		*sdm = 0;
	पूर्ण अन्यथा अगर (भाग > N2_MAX) अणु
		*n2 = N2_MAX;
		*sdm = SDM_DEN - 1;
	पूर्ण अन्यथा अणु
		*n2 = भाग;
	पूर्ण
पूर्ण

अटल अचिन्हित दीर्घ mpll_recalc_rate(काष्ठा clk_hw *hw,
		अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा clk_regmap *clk = to_clk_regmap(hw);
	काष्ठा meson_clk_mpll_data *mpll = meson_clk_mpll_data(clk);
	अचिन्हित पूर्णांक sdm, n2;
	दीर्घ rate;

	sdm = meson_parm_पढ़ो(clk->map, &mpll->sdm);
	n2 = meson_parm_पढ़ो(clk->map, &mpll->n2);

	rate = rate_from_params(parent_rate, sdm, n2);
	वापस rate < 0 ? 0 : rate;
पूर्ण

अटल दीर्घ mpll_round_rate(काष्ठा clk_hw *hw,
			    अचिन्हित दीर्घ rate,
			    अचिन्हित दीर्घ *parent_rate)
अणु
	काष्ठा clk_regmap *clk = to_clk_regmap(hw);
	काष्ठा meson_clk_mpll_data *mpll = meson_clk_mpll_data(clk);
	अचिन्हित पूर्णांक sdm, n2;

	params_from_rate(rate, *parent_rate, &sdm, &n2, mpll->flags);
	वापस rate_from_params(*parent_rate, sdm, n2);
पूर्ण

अटल पूर्णांक mpll_set_rate(काष्ठा clk_hw *hw,
			 अचिन्हित दीर्घ rate,
			 अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा clk_regmap *clk = to_clk_regmap(hw);
	काष्ठा meson_clk_mpll_data *mpll = meson_clk_mpll_data(clk);
	अचिन्हित पूर्णांक sdm, n2;
	अचिन्हित दीर्घ flags = 0;

	params_from_rate(rate, parent_rate, &sdm, &n2, mpll->flags);

	अगर (mpll->lock)
		spin_lock_irqsave(mpll->lock, flags);
	अन्यथा
		__acquire(mpll->lock);

	/* Set the fractional part */
	meson_parm_ग_लिखो(clk->map, &mpll->sdm, sdm);

	/* Set the पूर्णांकeger भागider part */
	meson_parm_ग_लिखो(clk->map, &mpll->n2, n2);

	अगर (mpll->lock)
		spin_unlock_irqrestore(mpll->lock, flags);
	अन्यथा
		__release(mpll->lock);

	वापस 0;
पूर्ण

अटल पूर्णांक mpll_init(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_regmap *clk = to_clk_regmap(hw);
	काष्ठा meson_clk_mpll_data *mpll = meson_clk_mpll_data(clk);

	अगर (mpll->init_count)
		regmap_multi_reg_ग_लिखो(clk->map, mpll->init_regs,
				       mpll->init_count);

	/* Enable the fractional part */
	meson_parm_ग_लिखो(clk->map, &mpll->sdm_en, 1);

	/* Set spपढ़ो spectrum अगर possible */
	अगर (MESON_PARM_APPLICABLE(&mpll->ssen)) अणु
		अचिन्हित पूर्णांक ss =
			mpll->flags & CLK_MESON_MPLL_SPREAD_SPECTRUM ? 1 : 0;
		meson_parm_ग_लिखो(clk->map, &mpll->ssen, ss);
	पूर्ण

	/* Set the magic misc bit अगर required */
	अगर (MESON_PARM_APPLICABLE(&mpll->misc))
		meson_parm_ग_लिखो(clk->map, &mpll->misc, 1);

	वापस 0;
पूर्ण

स्थिर काष्ठा clk_ops meson_clk_mpll_ro_ops = अणु
	.recalc_rate	= mpll_recalc_rate,
	.round_rate	= mpll_round_rate,
पूर्ण;
EXPORT_SYMBOL_GPL(meson_clk_mpll_ro_ops);

स्थिर काष्ठा clk_ops meson_clk_mpll_ops = अणु
	.recalc_rate	= mpll_recalc_rate,
	.round_rate	= mpll_round_rate,
	.set_rate	= mpll_set_rate,
	.init		= mpll_init,
पूर्ण;
EXPORT_SYMBOL_GPL(meson_clk_mpll_ops);

MODULE_DESCRIPTION("Amlogic MPLL driver");
MODULE_AUTHOR("Michael Turquette <mturquette@baylibre.com>");
MODULE_LICENSE("GPL v2");
