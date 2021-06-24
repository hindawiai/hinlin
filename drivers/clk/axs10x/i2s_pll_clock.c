<शैली गुरु>
/*
 * Synopsys AXS10X SDP I2S PLL घड़ी driver
 *
 * Copyright (C) 2016 Synopsys
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2. This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/module.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/err.h>
#समावेश <linux/device.h>
#समावेश <linux/पन.स>
#समावेश <linux/of_address.h>
#समावेश <linux/slab.h>
#समावेश <linux/of.h>

/* PLL रेजिस्टरs addresses */
#घोषणा PLL_IDIV_REG	0x0
#घोषणा PLL_FBDIV_REG	0x4
#घोषणा PLL_ODIV0_REG	0x8
#घोषणा PLL_ODIV1_REG	0xC

काष्ठा i2s_pll_cfg अणु
	अचिन्हित पूर्णांक rate;
	अचिन्हित पूर्णांक iभाग;
	अचिन्हित पूर्णांक fbभाग;
	अचिन्हित पूर्णांक oभाग0;
	अचिन्हित पूर्णांक oभाग1;
पूर्ण;

अटल स्थिर काष्ठा i2s_pll_cfg i2s_pll_cfg_27m[] = अणु
	/* 27 Mhz */
	अणु 1024000, 0x104, 0x451, 0x10E38, 0x2000 पूर्ण,
	अणु 1411200, 0x104, 0x596, 0x10D35, 0x2000 पूर्ण,
	अणु 1536000, 0x208, 0xA28, 0x10B2C, 0x2000 पूर्ण,
	अणु 2048000, 0x82, 0x451, 0x10E38, 0x2000 पूर्ण,
	अणु 2822400, 0x82, 0x596, 0x10D35, 0x2000 पूर्ण,
	अणु 3072000, 0x104, 0xA28, 0x10B2C, 0x2000 पूर्ण,
	अणु 2116800, 0x82, 0x3CF, 0x10C30, 0x2000 पूर्ण,
	अणु 2304000, 0x104, 0x79E, 0x10B2C, 0x2000 पूर्ण,
	अणु 0, 0, 0, 0, 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा i2s_pll_cfg i2s_pll_cfg_28m[] = अणु
	/* 28.224 Mhz */
	अणु 1024000, 0x82, 0x105, 0x107DF, 0x2000 पूर्ण,
	अणु 1411200, 0x28A, 0x1, 0x10001, 0x2000 पूर्ण,
	अणु 1536000, 0xA28, 0x187, 0x10042, 0x2000 पूर्ण,
	अणु 2048000, 0x41, 0x105, 0x107DF, 0x2000 पूर्ण,
	अणु 2822400, 0x145, 0x1, 0x10001, 0x2000 पूर्ण,
	अणु 3072000, 0x514, 0x187, 0x10042, 0x2000 पूर्ण,
	अणु 2116800, 0x514, 0x42, 0x10001, 0x2000 पूर्ण,
	अणु 2304000, 0x619, 0x82, 0x10001, 0x2000 पूर्ण,
	अणु 0, 0, 0, 0, 0 पूर्ण,
पूर्ण;

काष्ठा i2s_pll_clk अणु
	व्योम __iomem *base;
	काष्ठा clk_hw hw;
	काष्ठा device *dev;
पूर्ण;

अटल अंतरभूत व्योम i2s_pll_ग_लिखो(काष्ठा i2s_pll_clk *clk, अचिन्हित पूर्णांक reg,
		अचिन्हित पूर्णांक val)
अणु
	ग_लिखोl_relaxed(val, clk->base + reg);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक i2s_pll_पढ़ो(काष्ठा i2s_pll_clk *clk,
		अचिन्हित पूर्णांक reg)
अणु
	वापस पढ़ोl_relaxed(clk->base + reg);
पूर्ण

अटल अंतरभूत काष्ठा i2s_pll_clk *to_i2s_pll_clk(काष्ठा clk_hw *hw)
अणु
	वापस container_of(hw, काष्ठा i2s_pll_clk, hw);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक i2s_pll_get_value(अचिन्हित पूर्णांक val)
अणु
	वापस (val & 0x3F) + ((val >> 6) & 0x3F);
पूर्ण

अटल स्थिर काष्ठा i2s_pll_cfg *i2s_pll_get_cfg(अचिन्हित दीर्घ prate)
अणु
	चयन (prate) अणु
	हाल 27000000:
		वापस i2s_pll_cfg_27m;
	हाल 28224000:
		वापस i2s_pll_cfg_28m;
	शेष:
		वापस शून्य;
	पूर्ण
पूर्ण

अटल अचिन्हित दीर्घ i2s_pll_recalc_rate(काष्ठा clk_hw *hw,
			अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा i2s_pll_clk *clk = to_i2s_pll_clk(hw);
	अचिन्हित पूर्णांक iभाग, fbभाग, oभाग;

	iभाग = i2s_pll_get_value(i2s_pll_पढ़ो(clk, PLL_IDIV_REG));
	fbभाग = i2s_pll_get_value(i2s_pll_पढ़ो(clk, PLL_FBDIV_REG));
	oभाग = i2s_pll_get_value(i2s_pll_पढ़ो(clk, PLL_ODIV0_REG));

	वापस ((parent_rate / iभाग) * fbभाग) / oभाग;
पूर्ण

अटल दीर्घ i2s_pll_round_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
			अचिन्हित दीर्घ *prate)
अणु
	काष्ठा i2s_pll_clk *clk = to_i2s_pll_clk(hw);
	स्थिर काष्ठा i2s_pll_cfg *pll_cfg = i2s_pll_get_cfg(*prate);
	पूर्णांक i;

	अगर (!pll_cfg) अणु
		dev_err(clk->dev, "invalid parent rate=%ld\n", *prate);
		वापस -EINVAL;
	पूर्ण

	क्रम (i = 0; pll_cfg[i].rate != 0; i++)
		अगर (pll_cfg[i].rate == rate)
			वापस rate;

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक i2s_pll_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
			अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा i2s_pll_clk *clk = to_i2s_pll_clk(hw);
	स्थिर काष्ठा i2s_pll_cfg *pll_cfg = i2s_pll_get_cfg(parent_rate);
	पूर्णांक i;

	अगर (!pll_cfg) अणु
		dev_err(clk->dev, "invalid parent rate=%ld\n", parent_rate);
		वापस -EINVAL;
	पूर्ण

	क्रम (i = 0; pll_cfg[i].rate != 0; i++) अणु
		अगर (pll_cfg[i].rate == rate) अणु
			i2s_pll_ग_लिखो(clk, PLL_IDIV_REG, pll_cfg[i].iभाग);
			i2s_pll_ग_लिखो(clk, PLL_FBDIV_REG, pll_cfg[i].fbभाग);
			i2s_pll_ग_लिखो(clk, PLL_ODIV0_REG, pll_cfg[i].oभाग0);
			i2s_pll_ग_लिखो(clk, PLL_ODIV1_REG, pll_cfg[i].oभाग1);
			वापस 0;
		पूर्ण
	पूर्ण

	dev_err(clk->dev, "invalid rate=%ld, parent_rate=%ld\n", rate,
			parent_rate);
	वापस -EINVAL;
पूर्ण

अटल स्थिर काष्ठा clk_ops i2s_pll_ops = अणु
	.recalc_rate = i2s_pll_recalc_rate,
	.round_rate = i2s_pll_round_rate,
	.set_rate = i2s_pll_set_rate,
पूर्ण;

अटल पूर्णांक i2s_pll_clk_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *node = dev->of_node;
	स्थिर अक्षर *clk_name;
	स्थिर अक्षर *parent_name;
	काष्ठा clk *clk;
	काष्ठा i2s_pll_clk *pll_clk;
	काष्ठा clk_init_data init;

	pll_clk = devm_kzalloc(dev, माप(*pll_clk), GFP_KERNEL);
	अगर (!pll_clk)
		वापस -ENOMEM;

	pll_clk->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(pll_clk->base))
		वापस PTR_ERR(pll_clk->base);

	स_रखो(&init, 0, माप(init));
	clk_name = node->name;
	init.name = clk_name;
	init.ops = &i2s_pll_ops;
	parent_name = of_clk_get_parent_name(node, 0);
	init.parent_names = &parent_name;
	init.num_parents = 1;
	pll_clk->hw.init = &init;
	pll_clk->dev = dev;

	clk = devm_clk_रेजिस्टर(dev, &pll_clk->hw);
	अगर (IS_ERR(clk)) अणु
		dev_err(dev, "failed to register %s clock (%ld)\n",
				clk_name, PTR_ERR(clk));
		वापस PTR_ERR(clk);
	पूर्ण

	वापस of_clk_add_provider(node, of_clk_src_simple_get, clk);
पूर्ण

अटल पूर्णांक i2s_pll_clk_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	of_clk_del_provider(pdev->dev.of_node);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id i2s_pll_clk_id[] = अणु
	अणु .compatible = "snps,axs10x-i2s-pll-clock", पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, i2s_pll_clk_id);

अटल काष्ठा platक्रमm_driver i2s_pll_clk_driver = अणु
	.driver = अणु
		.name = "axs10x-i2s-pll-clock",
		.of_match_table = i2s_pll_clk_id,
	पूर्ण,
	.probe = i2s_pll_clk_probe,
	.हटाओ = i2s_pll_clk_हटाओ,
पूर्ण;
module_platक्रमm_driver(i2s_pll_clk_driver);

MODULE_AUTHOR("Jose Abreu <joabreu@synopsys.com>");
MODULE_DESCRIPTION("Synopsys AXS10X SDP I2S PLL Clock Driver");
MODULE_LICENSE("GPL v2");
