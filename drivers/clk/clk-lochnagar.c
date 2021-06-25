<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Lochnagar घड़ी control
 *
 * Copyright (c) 2017-2018 Cirrus Logic, Inc. and
 *                         Cirrus Logic International Semiconductor Ltd.
 *
 * Author: Charles Keepax <ckeepax@खोलोsource.cirrus.com>
 */

#समावेश <linux/clk-provider.h>
#समावेश <linux/device.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>

#समावेश <linux/mfd/lochnagar1_regs.h>
#समावेश <linux/mfd/lochnagar2_regs.h>

#समावेश <dt-bindings/clk/lochnagar.h>

#घोषणा LOCHNAGAR_NUM_CLOCKS	(LOCHNAGAR_SPDIF_CLKOUT + 1)

काष्ठा lochnagar_clk अणु
	स्थिर अक्षर * स्थिर name;
	काष्ठा clk_hw hw;

	काष्ठा lochnagar_clk_priv *priv;

	u16 cfg_reg;
	u16 ena_mask;

	u16 src_reg;
	u16 src_mask;
पूर्ण;

काष्ठा lochnagar_clk_priv अणु
	काष्ठा device *dev;
	काष्ठा regmap *regmap;

	काष्ठा lochnagar_clk lclks[LOCHNAGAR_NUM_CLOCKS];
पूर्ण;

#घोषणा LN_PARENT(NAME) अणु .name = NAME, .fw_name = NAME पूर्ण

अटल स्थिर काष्ठा clk_parent_data lochnagar1_clk_parents[] = अणु
	LN_PARENT("ln-none"),
	LN_PARENT("ln-spdif-mclk"),
	LN_PARENT("ln-psia1-mclk"),
	LN_PARENT("ln-psia2-mclk"),
	LN_PARENT("ln-cdc-clkout"),
	LN_PARENT("ln-dsp-clkout"),
	LN_PARENT("ln-pmic-32k"),
	LN_PARENT("ln-gf-mclk1"),
	LN_PARENT("ln-gf-mclk3"),
	LN_PARENT("ln-gf-mclk2"),
	LN_PARENT("ln-gf-mclk4"),
पूर्ण;

अटल स्थिर काष्ठा clk_parent_data lochnagar2_clk_parents[] = अणु
	LN_PARENT("ln-none"),
	LN_PARENT("ln-cdc-clkout"),
	LN_PARENT("ln-dsp-clkout"),
	LN_PARENT("ln-pmic-32k"),
	LN_PARENT("ln-spdif-mclk"),
	LN_PARENT("ln-clk-12m"),
	LN_PARENT("ln-clk-11m"),
	LN_PARENT("ln-clk-24m"),
	LN_PARENT("ln-clk-22m"),
	LN_PARENT("ln-clk-8m"),
	LN_PARENT("ln-usb-clk-24m"),
	LN_PARENT("ln-gf-mclk1"),
	LN_PARENT("ln-gf-mclk3"),
	LN_PARENT("ln-gf-mclk2"),
	LN_PARENT("ln-psia1-mclk"),
	LN_PARENT("ln-psia2-mclk"),
	LN_PARENT("ln-spdif-clkout"),
	LN_PARENT("ln-adat-mclk"),
	LN_PARENT("ln-usb-clk-12m"),
पूर्ण;

#घोषणा LN1_CLK(ID, NAME, REG) \
	[LOCHNAGAR_##ID] = अणु \
		.name = NAME, \
		.cfg_reg = LOCHNAGAR1_##REG, \
		.ena_mask = LOCHNAGAR1_##ID##_ENA_MASK, \
		.src_reg = LOCHNAGAR1_##ID##_SEL, \
		.src_mask = LOCHNAGAR1_SRC_MASK, \
	पूर्ण

#घोषणा LN2_CLK(ID, NAME) \
	[LOCHNAGAR_##ID] = अणु \
		.name = NAME, \
		.cfg_reg = LOCHNAGAR2_##ID##_CTRL, \
		.src_reg = LOCHNAGAR2_##ID##_CTRL, \
		.ena_mask = LOCHNAGAR2_CLK_ENA_MASK, \
		.src_mask = LOCHNAGAR2_CLK_SRC_MASK, \
	पूर्ण

अटल स्थिर काष्ठा lochnagar_clk lochnagar1_clks[LOCHNAGAR_NUM_CLOCKS] = अणु
	LN1_CLK(CDC_MCLK1,      "ln-cdc-mclk1",  CDC_AIF_CTRL2),
	LN1_CLK(CDC_MCLK2,      "ln-cdc-mclk2",  CDC_AIF_CTRL2),
	LN1_CLK(DSP_CLKIN,      "ln-dsp-clkin",  DSP_AIF),
	LN1_CLK(GF_CLKOUT1,     "ln-gf-clkout1", GF_AIF1),
पूर्ण;

अटल स्थिर काष्ठा lochnagar_clk lochnagar2_clks[LOCHNAGAR_NUM_CLOCKS] = अणु
	LN2_CLK(CDC_MCLK1,      "ln-cdc-mclk1"),
	LN2_CLK(CDC_MCLK2,      "ln-cdc-mclk2"),
	LN2_CLK(DSP_CLKIN,      "ln-dsp-clkin"),
	LN2_CLK(GF_CLKOUT1,     "ln-gf-clkout1"),
	LN2_CLK(GF_CLKOUT2,     "ln-gf-clkout2"),
	LN2_CLK(PSIA1_MCLK,     "ln-psia1-mclk"),
	LN2_CLK(PSIA2_MCLK,     "ln-psia2-mclk"),
	LN2_CLK(SPDIF_MCLK,     "ln-spdif-mclk"),
	LN2_CLK(ADAT_MCLK,      "ln-adat-mclk"),
	LN2_CLK(SOUNDCARD_MCLK, "ln-soundcard-mclk"),
पूर्ण;

काष्ठा lochnagar_config अणु
	स्थिर काष्ठा clk_parent_data *parents;
	पूर्णांक nparents;
	स्थिर काष्ठा lochnagar_clk *clks;
पूर्ण;

अटल स्थिर काष्ठा lochnagar_config lochnagar1_conf = अणु
	.parents = lochnagar1_clk_parents,
	.nparents = ARRAY_SIZE(lochnagar1_clk_parents),
	.clks = lochnagar1_clks,
पूर्ण;

अटल स्थिर काष्ठा lochnagar_config lochnagar2_conf = अणु
	.parents = lochnagar2_clk_parents,
	.nparents = ARRAY_SIZE(lochnagar2_clk_parents),
	.clks = lochnagar2_clks,
पूर्ण;

अटल अंतरभूत काष्ठा lochnagar_clk *lochnagar_hw_to_lclk(काष्ठा clk_hw *hw)
अणु
	वापस container_of(hw, काष्ठा lochnagar_clk, hw);
पूर्ण

अटल पूर्णांक lochnagar_clk_prepare(काष्ठा clk_hw *hw)
अणु
	काष्ठा lochnagar_clk *lclk = lochnagar_hw_to_lclk(hw);
	काष्ठा lochnagar_clk_priv *priv = lclk->priv;
	काष्ठा regmap *regmap = priv->regmap;
	पूर्णांक ret;

	ret = regmap_update_bits(regmap, lclk->cfg_reg,
				 lclk->ena_mask, lclk->ena_mask);
	अगर (ret < 0)
		dev_dbg(priv->dev, "Failed to prepare %s: %d\n",
			lclk->name, ret);

	वापस ret;
पूर्ण

अटल व्योम lochnagar_clk_unprepare(काष्ठा clk_hw *hw)
अणु
	काष्ठा lochnagar_clk *lclk = lochnagar_hw_to_lclk(hw);
	काष्ठा lochnagar_clk_priv *priv = lclk->priv;
	काष्ठा regmap *regmap = priv->regmap;
	पूर्णांक ret;

	ret = regmap_update_bits(regmap, lclk->cfg_reg, lclk->ena_mask, 0);
	अगर (ret < 0)
		dev_dbg(priv->dev, "Failed to unprepare %s: %d\n",
			lclk->name, ret);
पूर्ण

अटल पूर्णांक lochnagar_clk_set_parent(काष्ठा clk_hw *hw, u8 index)
अणु
	काष्ठा lochnagar_clk *lclk = lochnagar_hw_to_lclk(hw);
	काष्ठा lochnagar_clk_priv *priv = lclk->priv;
	काष्ठा regmap *regmap = priv->regmap;
	पूर्णांक ret;

	ret = regmap_update_bits(regmap, lclk->src_reg, lclk->src_mask, index);
	अगर (ret < 0)
		dev_dbg(priv->dev, "Failed to reparent %s: %d\n",
			lclk->name, ret);

	वापस ret;
पूर्ण

अटल u8 lochnagar_clk_get_parent(काष्ठा clk_hw *hw)
अणु
	काष्ठा lochnagar_clk *lclk = lochnagar_hw_to_lclk(hw);
	काष्ठा lochnagar_clk_priv *priv = lclk->priv;
	काष्ठा regmap *regmap = priv->regmap;
	अचिन्हित पूर्णांक val;
	पूर्णांक ret;

	ret = regmap_पढ़ो(regmap, lclk->src_reg, &val);
	अगर (ret < 0) अणु
		dev_dbg(priv->dev, "Failed to read parent of %s: %d\n",
			lclk->name, ret);
		वापस clk_hw_get_num_parents(hw);
	पूर्ण

	val &= lclk->src_mask;

	वापस val;
पूर्ण

अटल स्थिर काष्ठा clk_ops lochnagar_clk_ops = अणु
	.prepare = lochnagar_clk_prepare,
	.unprepare = lochnagar_clk_unprepare,
	.set_parent = lochnagar_clk_set_parent,
	.get_parent = lochnagar_clk_get_parent,
पूर्ण;

अटल काष्ठा clk_hw *
lochnagar_of_clk_hw_get(काष्ठा of_phandle_args *clkspec, व्योम *data)
अणु
	काष्ठा lochnagar_clk_priv *priv = data;
	अचिन्हित पूर्णांक idx = clkspec->args[0];

	अगर (idx >= ARRAY_SIZE(priv->lclks)) अणु
		dev_err(priv->dev, "Invalid index %u\n", idx);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	वापस &priv->lclks[idx].hw;
पूर्ण

अटल स्थिर काष्ठा of_device_id lochnagar_of_match[] = अणु
	अणु .compatible = "cirrus,lochnagar1-clk", .data = &lochnagar1_conf पूर्ण,
	अणु .compatible = "cirrus,lochnagar2-clk", .data = &lochnagar2_conf पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, lochnagar_of_match);

अटल पूर्णांक lochnagar_clk_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा clk_init_data clk_init = अणु
		.ops = &lochnagar_clk_ops,
	पूर्ण;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा lochnagar_clk_priv *priv;
	स्थिर काष्ठा of_device_id *of_id;
	काष्ठा lochnagar_clk *lclk;
	काष्ठा lochnagar_config *conf;
	पूर्णांक ret, i;

	of_id = of_match_device(lochnagar_of_match, dev);
	अगर (!of_id)
		वापस -EINVAL;

	priv = devm_kzalloc(dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	priv->dev = dev;
	priv->regmap = dev_get_regmap(dev->parent, शून्य);
	conf = (काष्ठा lochnagar_config *)of_id->data;

	स_नकल(priv->lclks, conf->clks, माप(priv->lclks));

	clk_init.parent_data = conf->parents;
	clk_init.num_parents = conf->nparents;

	क्रम (i = 0; i < ARRAY_SIZE(priv->lclks); i++) अणु
		lclk = &priv->lclks[i];

		अगर (!lclk->name)
			जारी;

		clk_init.name = lclk->name;

		lclk->priv = priv;
		lclk->hw.init = &clk_init;

		ret = devm_clk_hw_रेजिस्टर(dev, &lclk->hw);
		अगर (ret) अणु
			dev_err(dev, "Failed to register %s: %d\n",
				lclk->name, ret);
			वापस ret;
		पूर्ण
	पूर्ण

	ret = devm_of_clk_add_hw_provider(dev, lochnagar_of_clk_hw_get, priv);
	अगर (ret < 0)
		dev_err(dev, "Failed to register provider: %d\n", ret);

	वापस ret;
पूर्ण

अटल काष्ठा platक्रमm_driver lochnagar_clk_driver = अणु
	.driver = अणु
		.name = "lochnagar-clk",
		.of_match_table = lochnagar_of_match,
	पूर्ण,
	.probe = lochnagar_clk_probe,
पूर्ण;
module_platक्रमm_driver(lochnagar_clk_driver);

MODULE_AUTHOR("Charles Keepax <ckeepax@opensource.cirrus.com>");
MODULE_DESCRIPTION("Clock driver for Cirrus Logic Lochnagar Board");
MODULE_LICENSE("GPL v2");
