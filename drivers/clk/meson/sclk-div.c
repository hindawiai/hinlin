<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0 OR MIT)
/*
 * Copyright (c) 2018 BayLibre, SAS.
 * Author: Jerome Brunet <jbrunet@baylibre.com>
 *
 * Sample घड़ी generator भागider:
 * This HW भागider gates with value 0 but is otherwise a zero based भागider:
 *
 * val >= 1
 * भागider = val + 1
 *
 * The duty cycle may also be set क्रम the LR घड़ी variant. The duty cycle
 * ratio is:
 *
 * hi = [0 - val]
 * duty_cycle = (1 + hi) / (1 + val)
 */

#समावेश <linux/clk-provider.h>
#समावेश <linux/module.h>

#समावेश "clk-regmap.h"
#समावेश "sclk-div.h"

अटल अंतरभूत काष्ठा meson_sclk_भाग_data *
meson_sclk_भाग_data(काष्ठा clk_regmap *clk)
अणु
	वापस (काष्ठा meson_sclk_भाग_data *)clk->data;
पूर्ण

अटल पूर्णांक sclk_भाग_maxval(काष्ठा meson_sclk_भाग_data *sclk)
अणु
	वापस (1 << sclk->भाग.width) - 1;
पूर्ण

अटल पूर्णांक sclk_भाग_maxभाग(काष्ठा meson_sclk_भाग_data *sclk)
अणु
	वापस sclk_भाग_maxval(sclk) + 1;
पूर्ण

अटल पूर्णांक sclk_भाग_getभाग(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
			   अचिन्हित दीर्घ prate, पूर्णांक maxभाग)
अणु
	पूर्णांक भाग = DIV_ROUND_CLOSEST_ULL((u64)prate, rate);

	वापस clamp(भाग, 2, maxभाग);
पूर्ण

अटल पूर्णांक sclk_भाग_bestभाग(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
			    अचिन्हित दीर्घ *prate,
			    काष्ठा meson_sclk_भाग_data *sclk)
अणु
	काष्ठा clk_hw *parent = clk_hw_get_parent(hw);
	पूर्णांक bestभाग = 0, i;
	अचिन्हित दीर्घ maxभाग, now, parent_now;
	अचिन्हित दीर्घ best = 0, best_parent = 0;

	अगर (!rate)
		rate = 1;

	maxभाग = sclk_भाग_maxभाग(sclk);

	अगर (!(clk_hw_get_flags(hw) & CLK_SET_RATE_PARENT))
		वापस sclk_भाग_getभाग(hw, rate, *prate, maxभाग);

	/*
	 * The maximum भागider we can use without overflowing
	 * अचिन्हित दीर्घ in rate * i below
	 */
	maxभाग = min(अच_दीर्घ_उच्च / rate, maxभाग);

	क्रम (i = 2; i <= maxभाग; i++) अणु
		/*
		 * It's the most ideal हाल अगर the requested rate can be
		 * भागided from parent घड़ी without needing to change
		 * parent rate, so वापस the भागider immediately.
		 */
		अगर (rate * i == *prate)
			वापस i;

		parent_now = clk_hw_round_rate(parent, rate * i);
		now = DIV_ROUND_UP_ULL((u64)parent_now, i);

		अगर (असल(rate - now) < असल(rate - best)) अणु
			bestभाग = i;
			best = now;
			best_parent = parent_now;
		पूर्ण
	पूर्ण

	अगर (!bestभाग)
		bestभाग = sclk_भाग_maxभाग(sclk);
	अन्यथा
		*prate = best_parent;

	वापस bestभाग;
पूर्ण

अटल दीर्घ sclk_भाग_round_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				अचिन्हित दीर्घ *prate)
अणु
	काष्ठा clk_regmap *clk = to_clk_regmap(hw);
	काष्ठा meson_sclk_भाग_data *sclk = meson_sclk_भाग_data(clk);
	पूर्णांक भाग;

	भाग = sclk_भाग_bestभाग(hw, rate, prate, sclk);

	वापस DIV_ROUND_UP_ULL((u64)*prate, भाग);
पूर्ण

अटल व्योम sclk_apply_ratio(काष्ठा clk_regmap *clk,
			     काष्ठा meson_sclk_भाग_data *sclk)
अणु
	अचिन्हित पूर्णांक hi = DIV_ROUND_CLOSEST(sclk->cached_भाग *
					    sclk->cached_duty.num,
					    sclk->cached_duty.den);

	अगर (hi)
		hi -= 1;

	meson_parm_ग_लिखो(clk->map, &sclk->hi, hi);
पूर्ण

अटल पूर्णांक sclk_भाग_set_duty_cycle(काष्ठा clk_hw *hw,
				   काष्ठा clk_duty *duty)
अणु
	काष्ठा clk_regmap *clk = to_clk_regmap(hw);
	काष्ठा meson_sclk_भाग_data *sclk = meson_sclk_भाग_data(clk);

	अगर (MESON_PARM_APPLICABLE(&sclk->hi)) अणु
		स_नकल(&sclk->cached_duty, duty, माप(*duty));
		sclk_apply_ratio(clk, sclk);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक sclk_भाग_get_duty_cycle(काष्ठा clk_hw *hw,
				   काष्ठा clk_duty *duty)
अणु
	काष्ठा clk_regmap *clk = to_clk_regmap(hw);
	काष्ठा meson_sclk_भाग_data *sclk = meson_sclk_भाग_data(clk);
	पूर्णांक hi;

	अगर (!MESON_PARM_APPLICABLE(&sclk->hi)) अणु
		duty->num = 1;
		duty->den = 2;
		वापस 0;
	पूर्ण

	hi = meson_parm_पढ़ो(clk->map, &sclk->hi);
	duty->num = hi + 1;
	duty->den = sclk->cached_भाग;
	वापस 0;
पूर्ण

अटल व्योम sclk_apply_भागider(काष्ठा clk_regmap *clk,
			       काष्ठा meson_sclk_भाग_data *sclk)
अणु
	अगर (MESON_PARM_APPLICABLE(&sclk->hi))
		sclk_apply_ratio(clk, sclk);

	meson_parm_ग_लिखो(clk->map, &sclk->भाग, sclk->cached_भाग - 1);
पूर्ण

अटल पूर्णांक sclk_भाग_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
			     अचिन्हित दीर्घ prate)
अणु
	काष्ठा clk_regmap *clk = to_clk_regmap(hw);
	काष्ठा meson_sclk_भाग_data *sclk = meson_sclk_भाग_data(clk);
	अचिन्हित दीर्घ maxभाग = sclk_भाग_maxभाग(sclk);

	sclk->cached_भाग = sclk_भाग_getभाग(hw, rate, prate, maxभाग);

	अगर (clk_hw_is_enabled(hw))
		sclk_apply_भागider(clk, sclk);

	वापस 0;
पूर्ण

अटल अचिन्हित दीर्घ sclk_भाग_recalc_rate(काष्ठा clk_hw *hw,
					  अचिन्हित दीर्घ prate)
अणु
	काष्ठा clk_regmap *clk = to_clk_regmap(hw);
	काष्ठा meson_sclk_भाग_data *sclk = meson_sclk_भाग_data(clk);

	वापस DIV_ROUND_UP_ULL((u64)prate, sclk->cached_भाग);
पूर्ण

अटल पूर्णांक sclk_भाग_enable(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_regmap *clk = to_clk_regmap(hw);
	काष्ठा meson_sclk_भाग_data *sclk = meson_sclk_भाग_data(clk);

	sclk_apply_भागider(clk, sclk);

	वापस 0;
पूर्ण

अटल व्योम sclk_भाग_disable(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_regmap *clk = to_clk_regmap(hw);
	काष्ठा meson_sclk_भाग_data *sclk = meson_sclk_भाग_data(clk);

	meson_parm_ग_लिखो(clk->map, &sclk->भाग, 0);
पूर्ण

अटल पूर्णांक sclk_भाग_is_enabled(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_regmap *clk = to_clk_regmap(hw);
	काष्ठा meson_sclk_भाग_data *sclk = meson_sclk_भाग_data(clk);

	अगर (meson_parm_पढ़ो(clk->map, &sclk->भाग))
		वापस 1;

	वापस 0;
पूर्ण

अटल पूर्णांक sclk_भाग_init(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_regmap *clk = to_clk_regmap(hw);
	काष्ठा meson_sclk_भाग_data *sclk = meson_sclk_भाग_data(clk);
	अचिन्हित पूर्णांक val;

	val = meson_parm_पढ़ो(clk->map, &sclk->भाग);

	/* अगर the भागider is initially disabled, assume max */
	अगर (!val)
		sclk->cached_भाग = sclk_भाग_maxभाग(sclk);
	अन्यथा
		sclk->cached_भाग = val + 1;

	sclk_भाग_get_duty_cycle(hw, &sclk->cached_duty);

	वापस 0;
पूर्ण

स्थिर काष्ठा clk_ops meson_sclk_भाग_ops = अणु
	.recalc_rate	= sclk_भाग_recalc_rate,
	.round_rate	= sclk_भाग_round_rate,
	.set_rate	= sclk_भाग_set_rate,
	.enable		= sclk_भाग_enable,
	.disable	= sclk_भाग_disable,
	.is_enabled	= sclk_भाग_is_enabled,
	.get_duty_cycle	= sclk_भाग_get_duty_cycle,
	.set_duty_cycle = sclk_भाग_set_duty_cycle,
	.init		= sclk_भाग_init,
पूर्ण;
EXPORT_SYMBOL_GPL(meson_sclk_भाग_ops);

MODULE_DESCRIPTION("Amlogic Sample divider driver");
MODULE_AUTHOR("Jerome Brunet <jbrunet@baylibre.com>");
MODULE_LICENSE("GPL v2");
