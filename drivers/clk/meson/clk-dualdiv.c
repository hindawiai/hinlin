<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2017 BayLibre, SAS
 * Author: Neil Armstrong <narmstrong@baylibre.com>
 * Author: Jerome Brunet <jbrunet@baylibre.com>
 */

/*
 * The AO Doमुख्य embeds a dual/भागider to generate a more precise
 * 32,768KHz घड़ी क्रम low-घातer suspend mode and CEC.
 *     ______   ______
 *    |      | |      |
 *    | Div1 |-| Cnt1 |
 *   /|______| |______|\
 * -|  ______   ______  X--> Out
 *   \|      | |      |/
 *    | Div2 |-| Cnt2 |
 *    |______| |______|
 *
 * The भागiding can be चयनed to single or dual, with a counter
 * क्रम each भागider to set when the चयनing is करोne.
 */

#समावेश <linux/clk-provider.h>
#समावेश <linux/module.h>

#समावेश "clk-regmap.h"
#समावेश "clk-dualdiv.h"

अटल अंतरभूत काष्ठा meson_clk_duaद_भाग_data *
meson_clk_duaद_भाग_data(काष्ठा clk_regmap *clk)
अणु
	वापस (काष्ठा meson_clk_duaद_भाग_data *)clk->data;
पूर्ण

अटल अचिन्हित दीर्घ
__duaद_भाग_param_to_rate(अचिन्हित दीर्घ parent_rate,
			स्थिर काष्ठा meson_clk_duaद_भाग_param *p)
अणु
	अगर (!p->dual)
		वापस DIV_ROUND_CLOSEST(parent_rate, p->n1);

	वापस DIV_ROUND_CLOSEST(parent_rate * (p->m1 + p->m2),
				 p->n1 * p->m1 + p->n2 * p->m2);
पूर्ण

अटल अचिन्हित दीर्घ meson_clk_duaद_भाग_recalc_rate(काष्ठा clk_hw *hw,
						   अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा clk_regmap *clk = to_clk_regmap(hw);
	काष्ठा meson_clk_duaद_भाग_data *duaद_भाग = meson_clk_duaद_भाग_data(clk);
	काष्ठा meson_clk_duaद_भाग_param setting;

	setting.dual = meson_parm_पढ़ो(clk->map, &duaद_भाग->dual);
	setting.n1 = meson_parm_पढ़ो(clk->map, &duaद_भाग->n1) + 1;
	setting.m1 = meson_parm_पढ़ो(clk->map, &duaद_भाग->m1) + 1;
	setting.n2 = meson_parm_पढ़ो(clk->map, &duaद_भाग->n2) + 1;
	setting.m2 = meson_parm_पढ़ो(clk->map, &duaद_भाग->m2) + 1;

	वापस __duaद_भाग_param_to_rate(parent_rate, &setting);
पूर्ण

अटल स्थिर काष्ठा meson_clk_duaद_भाग_param *
__duaद_भाग_get_setting(अचिन्हित दीर्घ rate, अचिन्हित दीर्घ parent_rate,
		      काष्ठा meson_clk_duaद_भाग_data *duaद_भाग)
अणु
	स्थिर काष्ठा meson_clk_duaद_भाग_param *table = duaद_भाग->table;
	अचिन्हित दीर्घ best = 0, now = 0;
	अचिन्हित पूर्णांक i, best_i = 0;

	अगर (!table)
		वापस शून्य;

	क्रम (i = 0; table[i].n1; i++) अणु
		now = __duaद_भाग_param_to_rate(parent_rate, &table[i]);

		/* If we get an exact match, करोn't bother any further */
		अगर (now == rate) अणु
			वापस &table[i];
		पूर्ण अन्यथा अगर (असल(now - rate) < असल(best - rate)) अणु
			best = now;
			best_i = i;
		पूर्ण
	पूर्ण

	वापस (काष्ठा meson_clk_duaद_भाग_param *)&table[best_i];
पूर्ण

अटल दीर्घ meson_clk_duaद_भाग_round_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
					 अचिन्हित दीर्घ *parent_rate)
अणु
	काष्ठा clk_regmap *clk = to_clk_regmap(hw);
	काष्ठा meson_clk_duaद_भाग_data *duaद_भाग = meson_clk_duaद_भाग_data(clk);
	स्थिर काष्ठा meson_clk_duaद_भाग_param *setting =
		__duaद_भाग_get_setting(rate, *parent_rate, duaद_भाग);

	अगर (!setting)
		वापस meson_clk_duaद_भाग_recalc_rate(hw, *parent_rate);

	वापस __duaद_भाग_param_to_rate(*parent_rate, setting);
पूर्ण

अटल पूर्णांक meson_clk_duaद_भाग_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				      अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा clk_regmap *clk = to_clk_regmap(hw);
	काष्ठा meson_clk_duaद_भाग_data *duaद_भाग = meson_clk_duaद_भाग_data(clk);
	स्थिर काष्ठा meson_clk_duaद_भाग_param *setting =
		__duaद_भाग_get_setting(rate, parent_rate, duaद_भाग);

	अगर (!setting)
		वापस -EINVAL;

	meson_parm_ग_लिखो(clk->map, &duaद_भाग->dual, setting->dual);
	meson_parm_ग_लिखो(clk->map, &duaद_भाग->n1, setting->n1 - 1);
	meson_parm_ग_लिखो(clk->map, &duaद_भाग->m1, setting->m1 - 1);
	meson_parm_ग_लिखो(clk->map, &duaद_भाग->n2, setting->n2 - 1);
	meson_parm_ग_लिखो(clk->map, &duaद_भाग->m2, setting->m2 - 1);

	वापस 0;
पूर्ण

स्थिर काष्ठा clk_ops meson_clk_duaद_भाग_ops = अणु
	.recalc_rate	= meson_clk_duaद_भाग_recalc_rate,
	.round_rate	= meson_clk_duaद_भाग_round_rate,
	.set_rate	= meson_clk_duaद_भाग_set_rate,
पूर्ण;
EXPORT_SYMBOL_GPL(meson_clk_duaद_भाग_ops);

स्थिर काष्ठा clk_ops meson_clk_duaद_भाग_ro_ops = अणु
	.recalc_rate	= meson_clk_duaद_भाग_recalc_rate,
पूर्ण;
EXPORT_SYMBOL_GPL(meson_clk_duaद_भाग_ro_ops);

MODULE_DESCRIPTION("Amlogic dual divider driver");
MODULE_AUTHOR("Neil Armstrong <narmstrong@baylibre.com>");
MODULE_AUTHOR("Jerome Brunet <jbrunet@baylibre.com>");
MODULE_LICENSE("GPL v2");
