<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0 OR MIT)
/*
 * Copyright (c) 2019 BayLibre, SAS.
 * Author: Neil Armstrong <narmstrong@baylibre.com>
 */

#समावेश <linux/clk-provider.h>
#समावेश <linux/module.h>

#समावेश "clk-regmap.h"
#समावेश "clk-cpu-dyndiv.h"

अटल अंतरभूत काष्ठा meson_clk_cpu_dynभाग_data *
meson_clk_cpu_dynभाग_data(काष्ठा clk_regmap *clk)
अणु
	वापस (काष्ठा meson_clk_cpu_dynभाग_data *)clk->data;
पूर्ण

अटल अचिन्हित दीर्घ meson_clk_cpu_dynभाग_recalc_rate(काष्ठा clk_hw *hw,
						      अचिन्हित दीर्घ prate)
अणु
	काष्ठा clk_regmap *clk = to_clk_regmap(hw);
	काष्ठा meson_clk_cpu_dynभाग_data *data = meson_clk_cpu_dynभाग_data(clk);

	वापस भागider_recalc_rate(hw, prate,
				   meson_parm_पढ़ो(clk->map, &data->भाग),
				   शून्य, 0, data->भाग.width);
पूर्ण

अटल दीर्घ meson_clk_cpu_dynभाग_round_rate(काष्ठा clk_hw *hw,
					    अचिन्हित दीर्घ rate,
					    अचिन्हित दीर्घ *prate)
अणु
	काष्ठा clk_regmap *clk = to_clk_regmap(hw);
	काष्ठा meson_clk_cpu_dynभाग_data *data = meson_clk_cpu_dynभाग_data(clk);

	वापस भागider_round_rate(hw, rate, prate, शून्य, data->भाग.width, 0);
पूर्ण

अटल पूर्णांक meson_clk_cpu_dynभाग_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
					  अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा clk_regmap *clk = to_clk_regmap(hw);
	काष्ठा meson_clk_cpu_dynभाग_data *data = meson_clk_cpu_dynभाग_data(clk);
	अचिन्हित पूर्णांक val;
	पूर्णांक ret;

	ret = भागider_get_val(rate, parent_rate, शून्य, data->भाग.width, 0);
	अगर (ret < 0)
		वापस ret;

	val = (अचिन्हित पूर्णांक)ret << data->भाग.shअगरt;

	/* Write the SYS_CPU_DYN_ENABLE bit beक्रमe changing the भागider */
	meson_parm_ग_लिखो(clk->map, &data->dyn, 1);

	/* Update the भागider जबतक removing the SYS_CPU_DYN_ENABLE bit */
	वापस regmap_update_bits(clk->map, data->भाग.reg_off,
				  SETPMASK(data->भाग.width, data->भाग.shअगरt) |
				  SETPMASK(data->dyn.width, data->dyn.shअगरt),
				  val);
पूर्ण;

स्थिर काष्ठा clk_ops meson_clk_cpu_dynभाग_ops = अणु
	.recalc_rate = meson_clk_cpu_dynभाग_recalc_rate,
	.round_rate = meson_clk_cpu_dynभाग_round_rate,
	.set_rate = meson_clk_cpu_dynभाग_set_rate,
पूर्ण;
EXPORT_SYMBOL_GPL(meson_clk_cpu_dynभाग_ops);

MODULE_DESCRIPTION("Amlogic CPU Dynamic Clock divider");
MODULE_AUTHOR("Neil Armstrong <narmstrong@baylibre.com>");
MODULE_LICENSE("GPL v2");
