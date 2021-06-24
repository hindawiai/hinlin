<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2018 BayLibre, SAS.
 * Author: Neil Armstrong <narmstrong@baylibre.com>
 */

#समावेश <linux/clk-provider.h>
#समावेश <linux/module.h>

#समावेश "clk-regmap.h"
#समावेश "vid-pll-div.h"

अटल अंतरभूत काष्ठा meson_vid_pll_भाग_data *
meson_vid_pll_भाग_data(काष्ठा clk_regmap *clk)
अणु
	वापस (काष्ठा meson_vid_pll_भाग_data *)clk->data;
पूर्ण

/*
 * This vid_pll भागided is a fully programmable fractionnal भागider to
 * achieve complex video घड़ी rates.
 *
 * Here are provided the commonly used fraction values provided by Amlogic.
 */

काष्ठा vid_pll_भाग अणु
	अचिन्हित पूर्णांक shअगरt_val;
	अचिन्हित पूर्णांक shअगरt_sel;
	अचिन्हित पूर्णांक भागider;
	अचिन्हित पूर्णांक multiplier;
पूर्ण;

#घोषणा VID_PLL_DIV(_val, _sel, _ft, _fb)				\
	अणु								\
		.shअगरt_val = (_val),					\
		.shअगरt_sel = (_sel),					\
		.भागider = (_ft),					\
		.multiplier = (_fb),					\
	पूर्ण

अटल स्थिर काष्ठा vid_pll_भाग vid_pll_भाग_प्रकारable[] = अणु
	VID_PLL_DIV(0x0aaa, 0, 2, 1),	/* 2/1  => /2 */
	VID_PLL_DIV(0x5294, 2, 5, 2),	/* 5/2  => /2.5 */
	VID_PLL_DIV(0x0db6, 0, 3, 1),	/* 3/1  => /3 */
	VID_PLL_DIV(0x36cc, 1, 7, 2),	/* 7/2  => /3.5 */
	VID_PLL_DIV(0x6666, 2, 15, 4),	/* 15/4 => /3.75 */
	VID_PLL_DIV(0x0ccc, 0, 4, 1),	/* 4/1  => /4 */
	VID_PLL_DIV(0x739c, 2, 5, 1),	/* 5/1  => /5 */
	VID_PLL_DIV(0x0e38, 0, 6, 1),	/* 6/1  => /6 */
	VID_PLL_DIV(0x0000, 3, 25, 4),	/* 25/4 => /6.25 */
	VID_PLL_DIV(0x3c78, 1, 7, 1),	/* 7/1  => /7 */
	VID_PLL_DIV(0x78f0, 2, 15, 2),	/* 15/2 => /7.5 */
	VID_PLL_DIV(0x0fc0, 0, 12, 1),	/* 12/1 => /12 */
	VID_PLL_DIV(0x3f80, 1, 14, 1),	/* 14/1 => /14 */
	VID_PLL_DIV(0x7f80, 2, 15, 1),	/* 15/1 => /15 */
पूर्ण;

#घोषणा to_meson_vid_pll_भाग(_hw) \
	container_of(_hw, काष्ठा meson_vid_pll_भाग, hw)

अटल स्थिर काष्ठा vid_pll_भाग *_get_table_val(अचिन्हित पूर्णांक shअगरt_val,
						अचिन्हित पूर्णांक shअगरt_sel)
अणु
	पूर्णांक i;

	क्रम (i = 0 ; i < ARRAY_SIZE(vid_pll_भाग_प्रकारable) ; ++i) अणु
		अगर (vid_pll_भाग_प्रकारable[i].shअगरt_val == shअगरt_val &&
		    vid_pll_भाग_प्रकारable[i].shअगरt_sel == shअगरt_sel)
			वापस &vid_pll_भाग_प्रकारable[i];
	पूर्ण

	वापस शून्य;
पूर्ण

अटल अचिन्हित दीर्घ meson_vid_pll_भाग_recalc_rate(काष्ठा clk_hw *hw,
						   अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा clk_regmap *clk = to_clk_regmap(hw);
	काष्ठा meson_vid_pll_भाग_data *pll_भाग = meson_vid_pll_भाग_data(clk);
	स्थिर काष्ठा vid_pll_भाग *भाग;

	भाग = _get_table_val(meson_parm_पढ़ो(clk->map, &pll_भाग->val),
			     meson_parm_पढ़ो(clk->map, &pll_भाग->sel));
	अगर (!भाग || !भाग->भागider) अणु
		pr_debug("%s: Invalid config value for vid_pll_div\n", __func__);
		वापस 0;
	पूर्ण

	वापस DIV_ROUND_UP_ULL(parent_rate * भाग->multiplier, भाग->भागider);
पूर्ण

स्थिर काष्ठा clk_ops meson_vid_pll_भाग_ro_ops = अणु
	.recalc_rate	= meson_vid_pll_भाग_recalc_rate,
पूर्ण;
EXPORT_SYMBOL_GPL(meson_vid_pll_भाग_ro_ops);

MODULE_DESCRIPTION("Amlogic video pll divider driver");
MODULE_AUTHOR("Neil Armstrong <narmstrong@baylibre.com>");
MODULE_LICENSE("GPL v2");
