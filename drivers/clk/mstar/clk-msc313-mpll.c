<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * MStar MSC313 MPLL driver
 *
 * Copyright (C) 2020 Daniel Palmer <daniel@thingy.jp>
 */

#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/of_address.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/regmap.h>

#घोषणा REG_CONFIG1	0x8
#घोषणा REG_CONFIG2	0xc

अटल स्थिर काष्ठा regmap_config msc313_mpll_regmap_config = अणु
	.reg_bits = 16,
	.val_bits = 16,
	.reg_stride = 4,
पूर्ण;

अटल स्थिर काष्ठा reg_field config1_loop_भाग_first = REG_FIELD(REG_CONFIG1, 8, 9);
अटल स्थिर काष्ठा reg_field config1_input_भाग_first = REG_FIELD(REG_CONFIG1, 4, 5);
अटल स्थिर काष्ठा reg_field config2_output_भाग_first = REG_FIELD(REG_CONFIG2, 12, 13);
अटल स्थिर काष्ठा reg_field config2_loop_भाग_second = REG_FIELD(REG_CONFIG2, 0, 7);

अटल स्थिर अचिन्हित पूर्णांक output_भागiders[] = अणु
	2, 3, 4, 5, 6, 7, 10
पूर्ण;

#घोषणा NUMOUTPUTS (ARRAY_SIZE(output_भागiders) + 1)

काष्ठा msc313_mpll अणु
	काष्ठा clk_hw clk_hw;
	काष्ठा regmap_field *input_भाग;
	काष्ठा regmap_field *loop_भाग_first;
	काष्ठा regmap_field *loop_भाग_second;
	काष्ठा regmap_field *output_भाग;
	काष्ठा clk_hw_onecell_data *clk_data;
पूर्ण;

#घोषणा to_mpll(_hw) container_of(_hw, काष्ठा msc313_mpll, clk_hw)

अटल अचिन्हित दीर्घ msc313_mpll_recalc_rate(काष्ठा clk_hw *hw,
		अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा msc313_mpll *mpll = to_mpll(hw);
	अचिन्हित पूर्णांक input_भाग, output_भाग, loop_first, loop_second;
	अचिन्हित दीर्घ output_rate;

	regmap_field_पढ़ो(mpll->input_भाग, &input_भाग);
	regmap_field_पढ़ो(mpll->output_भाग, &output_भाग);
	regmap_field_पढ़ो(mpll->loop_भाग_first, &loop_first);
	regmap_field_पढ़ो(mpll->loop_भाग_second, &loop_second);

	output_rate = parent_rate / (1 << input_भाग);
	output_rate *= (1 << loop_first) * max(loop_second, 1U);
	output_rate /= max(output_भाग, 1U);

	वापस output_rate;
पूर्ण

अटल स्थिर काष्ठा clk_ops msc313_mpll_ops = अणु
	.recalc_rate = msc313_mpll_recalc_rate,
पूर्ण;

अटल स्थिर काष्ठा clk_parent_data mpll_parent = अणु
	.index	= 0,
पूर्ण;

अटल पूर्णांक msc313_mpll_probe(काष्ठा platक्रमm_device *pdev)
अणु
	व्योम __iomem *base;
	काष्ठा msc313_mpll *mpll;
	काष्ठा clk_init_data clk_init = अणु पूर्ण;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा regmap *regmap;
	अक्षर *outputname;
	काष्ठा clk_hw *भागhw;
	पूर्णांक ret, i;

	mpll = devm_kzalloc(dev, माप(*mpll), GFP_KERNEL);
	अगर (!mpll)
		वापस -ENOMEM;

	base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(base))
		वापस PTR_ERR(base);

	regmap = devm_regmap_init_mmio(dev, base, &msc313_mpll_regmap_config);
	अगर (IS_ERR(regmap))
		वापस PTR_ERR(regmap);

	mpll->input_भाग = devm_regmap_field_alloc(dev, regmap, config1_input_भाग_first);
	अगर (IS_ERR(mpll->input_भाग))
		वापस PTR_ERR(mpll->input_भाग);
	mpll->output_भाग = devm_regmap_field_alloc(dev, regmap, config2_output_भाग_first);
	अगर (IS_ERR(mpll->output_भाग))
		वापस PTR_ERR(mpll->output_भाग);
	mpll->loop_भाग_first = devm_regmap_field_alloc(dev, regmap, config1_loop_भाग_first);
	अगर (IS_ERR(mpll->loop_भाग_first))
		वापस PTR_ERR(mpll->loop_भाग_first);
	mpll->loop_भाग_second = devm_regmap_field_alloc(dev, regmap, config2_loop_भाग_second);
	अगर (IS_ERR(mpll->loop_भाग_second))
		वापस PTR_ERR(mpll->loop_भाग_second);

	mpll->clk_data = devm_kzalloc(dev, काष्ठा_size(mpll->clk_data, hws,
			ARRAY_SIZE(output_भागiders)), GFP_KERNEL);
	अगर (!mpll->clk_data)
		वापस -ENOMEM;

	clk_init.name = dev_name(dev);
	clk_init.ops = &msc313_mpll_ops;
	clk_init.parent_data = &mpll_parent;
	clk_init.num_parents = 1;
	mpll->clk_hw.init = &clk_init;

	ret = devm_clk_hw_रेजिस्टर(dev, &mpll->clk_hw);
	अगर (ret)
		वापस ret;

	mpll->clk_data->num = NUMOUTPUTS;
	mpll->clk_data->hws[0] = &mpll->clk_hw;

	क्रम (i = 0; i < ARRAY_SIZE(output_भागiders); i++) अणु
		outputname = devm_kaप्र_लिखो(dev, GFP_KERNEL, "%s_div_%u",
				clk_init.name, output_भागiders[i]);
		अगर (!outputname)
			वापस -ENOMEM;
		भागhw = devm_clk_hw_रेजिस्टर_fixed_factor(dev, outputname,
				clk_init.name, 0, 1, output_भागiders[i]);
		अगर (IS_ERR(भागhw))
			वापस PTR_ERR(भागhw);
		mpll->clk_data->hws[i + 1] = भागhw;
	पूर्ण

	platक्रमm_set_drvdata(pdev, mpll);

	वापस devm_of_clk_add_hw_provider(&pdev->dev, of_clk_hw_onecell_get,
			mpll->clk_data);
पूर्ण

अटल स्थिर काष्ठा of_device_id msc313_mpll_of_match[] = अणु
	अणु .compatible = "mstar,msc313-mpll", पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_driver msc313_mpll_driver = अणु
	.driver = अणु
		.name = "mstar-msc313-mpll",
		.of_match_table = msc313_mpll_of_match,
	पूर्ण,
	.probe = msc313_mpll_probe,
पूर्ण;
builtin_platक्रमm_driver(msc313_mpll_driver);
