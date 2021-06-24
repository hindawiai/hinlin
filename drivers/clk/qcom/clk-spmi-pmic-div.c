<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Copyright (c) 2017, The Linux Foundation. All rights reserved.
 */

#समावेश <linux/bitops.h>
#समावेश <linux/clk.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/delay.h>
#समावेश <linux/err.h>
#समावेश <linux/log2.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/slab.h>
#समावेश <linux/types.h>

#घोषणा REG_DIV_CTL1			0x43
#घोषणा DIV_CTL1_DIV_FACTOR_MASK	GENMASK(2, 0)

#घोषणा REG_EN_CTL			0x46
#घोषणा REG_EN_MASK			BIT(7)

काष्ठा clkभाग अणु
	काष्ठा regmap		*regmap;
	u16			base;
	spinlock_t		lock;

	काष्ठा clk_hw		hw;
	अचिन्हित पूर्णांक		cxo_period_ns;
पूर्ण;

अटल अंतरभूत काष्ठा clkभाग *to_clkभाग(काष्ठा clk_hw *hw)
अणु
	वापस container_of(hw, काष्ठा clkभाग, hw);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक भाग_factor_to_भाग(अचिन्हित पूर्णांक भाग_factor)
अणु
	अगर (!भाग_factor)
		भाग_factor = 1;

	वापस 1 << (भाग_factor - 1);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक भाग_प्रकारo_भाग_factor(अचिन्हित पूर्णांक भाग)
अणु
	वापस min(ilog2(भाग) + 1, 7);
पूर्ण

अटल bool is_spmi_pmic_clkभाग_enabled(काष्ठा clkभाग *clkभाग)
अणु
	अचिन्हित पूर्णांक val = 0;

	regmap_पढ़ो(clkभाग->regmap, clkभाग->base + REG_EN_CTL, &val);

	वापस val & REG_EN_MASK;
पूर्ण

अटल पूर्णांक
__spmi_pmic_clkभाग_set_enable_state(काष्ठा clkभाग *clkभाग, bool enable,
				    अचिन्हित पूर्णांक भाग_factor)
अणु
	पूर्णांक ret;
	अचिन्हित पूर्णांक ns = clkभाग->cxo_period_ns;
	अचिन्हित पूर्णांक भाग = भाग_factor_to_भाग(भाग_factor);

	ret = regmap_update_bits(clkभाग->regmap, clkभाग->base + REG_EN_CTL,
				 REG_EN_MASK, enable ? REG_EN_MASK : 0);
	अगर (ret)
		वापस ret;

	अगर (enable)
		ndelay((2 + 3 * भाग) * ns);
	अन्यथा
		ndelay(3 * भाग * ns);

	वापस 0;
पूर्ण

अटल पूर्णांक spmi_pmic_clkभाग_set_enable_state(काष्ठा clkभाग *clkभाग, bool enable)
अणु
	अचिन्हित पूर्णांक भाग_factor;

	regmap_पढ़ो(clkभाग->regmap, clkभाग->base + REG_DIV_CTL1, &भाग_factor);
	भाग_factor &= DIV_CTL1_DIV_FACTOR_MASK;

	वापस __spmi_pmic_clkभाग_set_enable_state(clkभाग, enable, भाग_factor);
पूर्ण

अटल पूर्णांक clk_spmi_pmic_भाग_enable(काष्ठा clk_hw *hw)
अणु
	काष्ठा clkभाग *clkभाग = to_clkभाग(hw);
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	spin_lock_irqsave(&clkभाग->lock, flags);
	ret = spmi_pmic_clkभाग_set_enable_state(clkभाग, true);
	spin_unlock_irqrestore(&clkभाग->lock, flags);

	वापस ret;
पूर्ण

अटल व्योम clk_spmi_pmic_भाग_disable(काष्ठा clk_hw *hw)
अणु
	काष्ठा clkभाग *clkभाग = to_clkभाग(hw);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&clkभाग->lock, flags);
	spmi_pmic_clkभाग_set_enable_state(clkभाग, false);
	spin_unlock_irqrestore(&clkभाग->lock, flags);
पूर्ण

अटल दीर्घ clk_spmi_pmic_भाग_round_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
					 अचिन्हित दीर्घ *parent_rate)
अणु
	अचिन्हित पूर्णांक भाग, भाग_factor;

	भाग = DIV_ROUND_UP(*parent_rate, rate);
	भाग_factor = भाग_प्रकारo_भाग_factor(भाग);
	भाग = भाग_factor_to_भाग(भाग_factor);

	वापस *parent_rate / भाग;
पूर्ण

अटल अचिन्हित दीर्घ
clk_spmi_pmic_भाग_recalc_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा clkभाग *clkभाग = to_clkभाग(hw);
	अचिन्हित पूर्णांक भाग_factor;

	regmap_पढ़ो(clkभाग->regmap, clkभाग->base + REG_DIV_CTL1, &भाग_factor);
	भाग_factor &= DIV_CTL1_DIV_FACTOR_MASK;

	वापस parent_rate / भाग_factor_to_भाग(भाग_factor);
पूर्ण

अटल पूर्णांक clk_spmi_pmic_भाग_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				      अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा clkभाग *clkभाग = to_clkभाग(hw);
	अचिन्हित पूर्णांक भाग_factor = भाग_प्रकारo_भाग_factor(parent_rate / rate);
	अचिन्हित दीर्घ flags;
	bool enabled;
	पूर्णांक ret;

	spin_lock_irqsave(&clkभाग->lock, flags);
	enabled = is_spmi_pmic_clkभाग_enabled(clkभाग);
	अगर (enabled) अणु
		ret = spmi_pmic_clkभाग_set_enable_state(clkभाग, false);
		अगर (ret)
			जाओ unlock;
	पूर्ण

	ret = regmap_update_bits(clkभाग->regmap, clkभाग->base + REG_DIV_CTL1,
				 DIV_CTL1_DIV_FACTOR_MASK, भाग_factor);
	अगर (ret)
		जाओ unlock;

	अगर (enabled)
		ret = __spmi_pmic_clkभाग_set_enable_state(clkभाग, true,
							  भाग_factor);

unlock:
	spin_unlock_irqrestore(&clkभाग->lock, flags);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा clk_ops clk_spmi_pmic_भाग_ops = अणु
	.enable = clk_spmi_pmic_भाग_enable,
	.disable = clk_spmi_pmic_भाग_disable,
	.set_rate = clk_spmi_pmic_भाग_set_rate,
	.recalc_rate = clk_spmi_pmic_भाग_recalc_rate,
	.round_rate = clk_spmi_pmic_भाग_round_rate,
पूर्ण;

काष्ठा spmi_pmic_भाग_clk_cc अणु
	पूर्णांक		nclks;
	काष्ठा clkभाग	clks[];
पूर्ण;

अटल काष्ठा clk_hw *
spmi_pmic_भाग_clk_hw_get(काष्ठा of_phandle_args *clkspec, व्योम *data)
अणु
	काष्ठा spmi_pmic_भाग_clk_cc *cc = data;
	पूर्णांक idx = clkspec->args[0] - 1; /* Start at 1 instead of 0 */

	अगर (idx < 0 || idx >= cc->nclks) अणु
		pr_err("%s: index value %u is invalid; allowed range [1, %d]\n",
		       __func__, clkspec->args[0], cc->nclks);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	वापस &cc->clks[idx].hw;
पूर्ण

अटल पूर्णांक spmi_pmic_clkभाग_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा spmi_pmic_भाग_clk_cc *cc;
	काष्ठा clk_init_data init = अणुपूर्ण;
	काष्ठा clkभाग *clkभाग;
	काष्ठा clk *cxo;
	काष्ठा regmap *regmap;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *of_node = dev->of_node;
	स्थिर अक्षर *parent_name;
	पूर्णांक nclks, i, ret, cxo_hz;
	अक्षर name[20];
	u32 start;

	ret = of_property_पढ़ो_u32(of_node, "reg", &start);
	अगर (ret < 0) अणु
		dev_err(dev, "reg property reading failed\n");
		वापस ret;
	पूर्ण

	regmap = dev_get_regmap(dev->parent, शून्य);
	अगर (!regmap) अणु
		dev_err(dev, "Couldn't get parent's regmap\n");
		वापस -EINVAL;
	पूर्ण

	ret = of_property_पढ़ो_u32(of_node, "qcom,num-clkdivs", &nclks);
	अगर (ret < 0) अणु
		dev_err(dev, "qcom,num-clkdivs property reading failed, ret=%d\n",
			ret);
		वापस ret;
	पूर्ण

	अगर (!nclks)
		वापस -EINVAL;

	cc = devm_kzalloc(dev, काष्ठा_size(cc, clks, nclks), GFP_KERNEL);
	अगर (!cc)
		वापस -ENOMEM;
	cc->nclks = nclks;

	cxo = clk_get(dev, "xo");
	अगर (IS_ERR(cxo)) अणु
		ret = PTR_ERR(cxo);
		अगर (ret != -EPROBE_DEFER)
			dev_err(dev, "failed to get xo clock\n");
		वापस ret;
	पूर्ण
	cxo_hz = clk_get_rate(cxo);
	clk_put(cxo);

	parent_name = of_clk_get_parent_name(of_node, 0);
	अगर (!parent_name) अणु
		dev_err(dev, "missing parent clock\n");
		वापस -ENODEV;
	पूर्ण

	init.name = name;
	init.parent_names = &parent_name;
	init.num_parents = 1;
	init.ops = &clk_spmi_pmic_भाग_ops;

	क्रम (i = 0, clkभाग = cc->clks; i < nclks; i++) अणु
		snम_लिखो(name, माप(name), "div_clk%d", i + 1);

		spin_lock_init(&clkभाग[i].lock);
		clkभाग[i].base = start + i * 0x100;
		clkभाग[i].regmap = regmap;
		clkभाग[i].cxo_period_ns = NSEC_PER_SEC / cxo_hz;
		clkभाग[i].hw.init = &init;

		ret = devm_clk_hw_रेजिस्टर(dev, &clkभाग[i].hw);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस devm_of_clk_add_hw_provider(dev, spmi_pmic_भाग_clk_hw_get, cc);
पूर्ण

अटल स्थिर काष्ठा of_device_id spmi_pmic_clkभाग_match_table[] = अणु
	अणु .compatible = "qcom,spmi-clkdiv" पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, spmi_pmic_clkभाग_match_table);

अटल काष्ठा platक्रमm_driver spmi_pmic_clkभाग_driver = अणु
	.driver		= अणु
		.name	= "qcom,spmi-pmic-clkdiv",
		.of_match_table = spmi_pmic_clkभाग_match_table,
	पूर्ण,
	.probe		= spmi_pmic_clkभाग_probe,
पूर्ण;
module_platक्रमm_driver(spmi_pmic_clkभाग_driver);

MODULE_DESCRIPTION("QCOM SPMI PMIC clkdiv driver");
MODULE_LICENSE("GPL v2");
