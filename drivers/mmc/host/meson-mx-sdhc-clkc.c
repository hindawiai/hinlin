<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Amlogic Meson SDHC घड़ी controller
 *
 * Copyright (C) 2020 Martin Blumenstingl <martin.blumenstingl@googlemail.com>
 */

#समावेश <linux/clk.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/device.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश "meson-mx-sdhc.h"

#घोषणा MESON_SDHC_NUM_BUILTIN_CLKS	6

काष्ठा meson_mx_sdhc_clkc अणु
	काष्ठा clk_mux			src_sel;
	काष्ठा clk_भागider		भाग;
	काष्ठा clk_gate			mod_clk_en;
	काष्ठा clk_gate			tx_clk_en;
	काष्ठा clk_gate			rx_clk_en;
	काष्ठा clk_gate			sd_clk_en;
पूर्ण;

अटल स्थिर काष्ठा clk_parent_data meson_mx_sdhc_src_sel_parents[4] = अणु
	अणु .fw_name = "clkin0" पूर्ण,
	अणु .fw_name = "clkin1" पूर्ण,
	अणु .fw_name = "clkin2" पूर्ण,
	अणु .fw_name = "clkin3" पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा clk_भाग_प्रकारable meson_mx_sdhc_भाग_प्रकारable[] = अणु
	अणु .भाग = 6, .val = 5, पूर्ण,
	अणु .भाग = 8, .val = 7, पूर्ण,
	अणु .भाग = 9, .val = 8, पूर्ण,
	अणु .भाग = 10, .val = 9, पूर्ण,
	अणु .भाग = 12, .val = 11, पूर्ण,
	अणु .भाग = 16, .val = 15, पूर्ण,
	अणु .भाग = 18, .val = 17, पूर्ण,
	अणु .भाग = 34, .val = 33, पूर्ण,
	अणु .भाग = 142, .val = 141, पूर्ण,
	अणु .भाग = 850, .val = 849, पूर्ण,
	अणु .भाग = 2126, .val = 2125, पूर्ण,
	अणु .भाग = 4096, .val = 4095, पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;

अटल पूर्णांक meson_mx_sdhc_clk_hw_रेजिस्टर(काष्ठा device *dev,
					 स्थिर अक्षर *name_suffix,
					 स्थिर काष्ठा clk_parent_data *parents,
					 अचिन्हित पूर्णांक num_parents,
					 स्थिर काष्ठा clk_ops *ops,
					 काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_init_data init = अणु पूर्ण;
	अक्षर clk_name[32];

	snम_लिखो(clk_name, माप(clk_name), "%s#%s", dev_name(dev),
		 name_suffix);

	init.name = clk_name;
	init.ops = ops;
	init.flags = CLK_SET_RATE_PARENT;
	init.parent_data = parents;
	init.num_parents = num_parents;

	hw->init = &init;

	वापस devm_clk_hw_रेजिस्टर(dev, hw);
पूर्ण

अटल पूर्णांक meson_mx_sdhc_gate_clk_hw_रेजिस्टर(काष्ठा device *dev,
					      स्थिर अक्षर *name_suffix,
					      काष्ठा clk_hw *parent,
					      काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_parent_data parent_data = अणु .hw = parent पूर्ण;

	वापस meson_mx_sdhc_clk_hw_रेजिस्टर(dev, name_suffix, &parent_data, 1,
					     &clk_gate_ops, hw);
पूर्ण

पूर्णांक meson_mx_sdhc_रेजिस्टर_clkc(काष्ठा device *dev, व्योम __iomem *base,
				काष्ठा clk_bulk_data *clk_bulk_data)
अणु
	काष्ठा clk_parent_data भाग_parent = अणु पूर्ण;
	काष्ठा meson_mx_sdhc_clkc *clkc_data;
	पूर्णांक ret;

	clkc_data = devm_kzalloc(dev, माप(*clkc_data), GFP_KERNEL);
	अगर (!clkc_data)
		वापस -ENOMEM;

	clkc_data->src_sel.reg = base + MESON_SDHC_CLKC;
	clkc_data->src_sel.mask = 0x3;
	clkc_data->src_sel.shअगरt = 16;
	ret = meson_mx_sdhc_clk_hw_रेजिस्टर(dev, "src_sel",
					    meson_mx_sdhc_src_sel_parents, 4,
					    &clk_mux_ops,
					    &clkc_data->src_sel.hw);
	अगर (ret)
		वापस ret;

	clkc_data->भाग.reg = base + MESON_SDHC_CLKC;
	clkc_data->भाग.shअगरt = 0;
	clkc_data->भाग.width = 12;
	clkc_data->भाग.table = meson_mx_sdhc_भाग_प्रकारable;
	भाग_parent.hw = &clkc_data->src_sel.hw;
	ret = meson_mx_sdhc_clk_hw_रेजिस्टर(dev, "div", &भाग_parent, 1,
					    &clk_भागider_ops,
					    &clkc_data->भाग.hw);
	अगर (ret)
		वापस ret;

	clkc_data->mod_clk_en.reg = base + MESON_SDHC_CLKC;
	clkc_data->mod_clk_en.bit_idx = 15;
	ret = meson_mx_sdhc_gate_clk_hw_रेजिस्टर(dev, "mod_clk_on",
						 &clkc_data->भाग.hw,
						 &clkc_data->mod_clk_en.hw);
	अगर (ret)
		वापस ret;

	clkc_data->tx_clk_en.reg = base + MESON_SDHC_CLKC;
	clkc_data->tx_clk_en.bit_idx = 14;
	ret = meson_mx_sdhc_gate_clk_hw_रेजिस्टर(dev, "tx_clk_on",
						 &clkc_data->भाग.hw,
						 &clkc_data->tx_clk_en.hw);
	अगर (ret)
		वापस ret;

	clkc_data->rx_clk_en.reg = base + MESON_SDHC_CLKC;
	clkc_data->rx_clk_en.bit_idx = 13;
	ret = meson_mx_sdhc_gate_clk_hw_रेजिस्टर(dev, "rx_clk_on",
						 &clkc_data->भाग.hw,
						 &clkc_data->rx_clk_en.hw);
	अगर (ret)
		वापस ret;

	clkc_data->sd_clk_en.reg = base + MESON_SDHC_CLKC;
	clkc_data->sd_clk_en.bit_idx = 12;
	ret = meson_mx_sdhc_gate_clk_hw_रेजिस्टर(dev, "sd_clk_on",
						 &clkc_data->भाग.hw,
						 &clkc_data->sd_clk_en.hw);
	अगर (ret)
		वापस ret;

	/*
	 * TODO: Replace clk_hw.clk with devm_clk_hw_get_clk() once that is
	 * available.
	 */
	clk_bulk_data[0].clk = clkc_data->mod_clk_en.hw.clk;
	clk_bulk_data[1].clk = clkc_data->sd_clk_en.hw.clk;
	clk_bulk_data[2].clk = clkc_data->tx_clk_en.hw.clk;
	clk_bulk_data[3].clk = clkc_data->rx_clk_en.hw.clk;

	वापस 0;
पूर्ण
