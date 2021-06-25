<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2020 Texas Instruments Incorporated - https://www.ti.com/
 */

#समावेश <linux/clk-provider.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>

काष्ठा ti_syscon_gate_clk_priv अणु
	काष्ठा clk_hw hw;
	काष्ठा regmap *regmap;
	u32 reg;
	u32 idx;
पूर्ण;

काष्ठा ti_syscon_gate_clk_data अणु
	अक्षर *name;
	u32 offset;
	u32 bit_idx;
पूर्ण;

अटल काष्ठा
ti_syscon_gate_clk_priv *to_ti_syscon_gate_clk_priv(काष्ठा clk_hw *hw)
अणु
	वापस container_of(hw, काष्ठा ti_syscon_gate_clk_priv, hw);
पूर्ण

अटल पूर्णांक ti_syscon_gate_clk_enable(काष्ठा clk_hw *hw)
अणु
	काष्ठा ti_syscon_gate_clk_priv *priv = to_ti_syscon_gate_clk_priv(hw);

	वापस regmap_ग_लिखो_bits(priv->regmap, priv->reg, priv->idx,
				 priv->idx);
पूर्ण

अटल व्योम ti_syscon_gate_clk_disable(काष्ठा clk_hw *hw)
अणु
	काष्ठा ti_syscon_gate_clk_priv *priv = to_ti_syscon_gate_clk_priv(hw);

	regmap_ग_लिखो_bits(priv->regmap, priv->reg, priv->idx, 0);
पूर्ण

अटल पूर्णांक ti_syscon_gate_clk_is_enabled(काष्ठा clk_hw *hw)
अणु
	अचिन्हित पूर्णांक val;
	काष्ठा ti_syscon_gate_clk_priv *priv = to_ti_syscon_gate_clk_priv(hw);

	regmap_पढ़ो(priv->regmap, priv->reg, &val);

	वापस !!(val & priv->idx);
पूर्ण

अटल स्थिर काष्ठा clk_ops ti_syscon_gate_clk_ops = अणु
	.enable		= ti_syscon_gate_clk_enable,
	.disable	= ti_syscon_gate_clk_disable,
	.is_enabled	= ti_syscon_gate_clk_is_enabled,
पूर्ण;

अटल काष्ठा clk_hw
*ti_syscon_gate_clk_रेजिस्टर(काष्ठा device *dev, काष्ठा regmap *regmap,
			     स्थिर काष्ठा ti_syscon_gate_clk_data *data)
अणु
	काष्ठा ti_syscon_gate_clk_priv *priv;
	काष्ठा clk_init_data init;
	पूर्णांक ret;

	priv = devm_kzalloc(dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस ERR_PTR(-ENOMEM);

	init.name = data->name;
	init.ops = &ti_syscon_gate_clk_ops;
	init.parent_names = शून्य;
	init.num_parents = 0;
	init.flags = 0;

	priv->regmap = regmap;
	priv->reg = data->offset;
	priv->idx = BIT(data->bit_idx);
	priv->hw.init = &init;

	ret = devm_clk_hw_रेजिस्टर(dev, &priv->hw);
	अगर (ret)
		वापस ERR_PTR(ret);

	वापस &priv->hw;
पूर्ण

अटल पूर्णांक ti_syscon_gate_clk_probe(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा ti_syscon_gate_clk_data *data, *p;
	काष्ठा clk_hw_onecell_data *hw_data;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा regmap *regmap;
	पूर्णांक num_clks, i;

	data = device_get_match_data(dev);
	अगर (!data)
		वापस -EINVAL;

	regmap = syscon_node_to_regmap(dev->of_node);
	अगर (IS_ERR(regmap)) अणु
		अगर (PTR_ERR(regmap) == -EPROBE_DEFER)
			वापस -EPROBE_DEFER;
		dev_err(dev, "failed to find parent regmap\n");
		वापस PTR_ERR(regmap);
	पूर्ण

	num_clks = 0;
	क्रम (p = data; p->name; p++)
		num_clks++;

	hw_data = devm_kzalloc(dev, काष्ठा_size(hw_data, hws, num_clks),
			       GFP_KERNEL);
	अगर (!hw_data)
		वापस -ENOMEM;

	hw_data->num = num_clks;

	क्रम (i = 0; i < num_clks; i++) अणु
		hw_data->hws[i] = ti_syscon_gate_clk_रेजिस्टर(dev, regmap,
							      &data[i]);
		अगर (IS_ERR(hw_data->hws[i]))
			dev_warn(dev, "failed to register %s\n",
				 data[i].name);
	पूर्ण

	वापस devm_of_clk_add_hw_provider(dev, of_clk_hw_onecell_get,
					   hw_data);
पूर्ण

#घोषणा TI_SYSCON_CLK_GATE(_name, _offset, _bit_idx)	\
	अणु						\
		.name = _name,				\
		.offset = (_offset),			\
		.bit_idx = (_bit_idx),			\
	पूर्ण

अटल स्थिर काष्ठा ti_syscon_gate_clk_data am654_clk_data[] = अणु
	TI_SYSCON_CLK_GATE("ehrpwm_tbclk0", 0x0, 0),
	TI_SYSCON_CLK_GATE("ehrpwm_tbclk1", 0x4, 0),
	TI_SYSCON_CLK_GATE("ehrpwm_tbclk2", 0x8, 0),
	TI_SYSCON_CLK_GATE("ehrpwm_tbclk3", 0xc, 0),
	TI_SYSCON_CLK_GATE("ehrpwm_tbclk4", 0x10, 0),
	TI_SYSCON_CLK_GATE("ehrpwm_tbclk5", 0x14, 0),
	अणु /* Sentinel */ पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा of_device_id ti_syscon_gate_clk_ids[] = अणु
	अणु
		.compatible = "ti,am654-ehrpwm-tbclk",
		.data = &am654_clk_data,
	पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, ti_syscon_gate_clk_ids);

अटल काष्ठा platक्रमm_driver ti_syscon_gate_clk_driver = अणु
	.probe = ti_syscon_gate_clk_probe,
	.driver = अणु
		.name = "ti-syscon-gate-clk",
		.of_match_table = ti_syscon_gate_clk_ids,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(ti_syscon_gate_clk_driver);

MODULE_AUTHOR("Vignesh Raghavendra <vigneshr@ti.com>");
MODULE_DESCRIPTION("Syscon backed gate-clock driver");
MODULE_LICENSE("GPL");
