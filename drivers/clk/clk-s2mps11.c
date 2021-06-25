<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
//
// clk-s2mps11.c - Clock driver क्रम S2MPS11.
//
// Copyright (C) 2013,2014 Samsung Electornics

#समावेश <linux/module.h>
#समावेश <linux/err.h>
#समावेश <linux/of.h>
#समावेश <linux/clkdev.h>
#समावेश <linux/regmap.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/mfd/samsung/s2mps11.h>
#समावेश <linux/mfd/samsung/s2mps13.h>
#समावेश <linux/mfd/samsung/s2mps14.h>
#समावेश <linux/mfd/samsung/s5m8767.h>
#समावेश <linux/mfd/samsung/core.h>

#समावेश <dt-bindings/घड़ी/samsung,s2mps11.h>

काष्ठा s2mps11_clk अणु
	काष्ठा sec_pmic_dev *iodev;
	काष्ठा device_node *clk_np;
	काष्ठा clk_hw hw;
	काष्ठा clk *clk;
	काष्ठा clk_lookup *lookup;
	u32 mask;
	अचिन्हित पूर्णांक reg;
पूर्ण;

अटल काष्ठा s2mps11_clk *to_s2mps11_clk(काष्ठा clk_hw *hw)
अणु
	वापस container_of(hw, काष्ठा s2mps11_clk, hw);
पूर्ण

अटल पूर्णांक s2mps11_clk_prepare(काष्ठा clk_hw *hw)
अणु
	काष्ठा s2mps11_clk *s2mps11 = to_s2mps11_clk(hw);

	वापस regmap_update_bits(s2mps11->iodev->regmap_pmic,
				 s2mps11->reg,
				 s2mps11->mask, s2mps11->mask);
पूर्ण

अटल व्योम s2mps11_clk_unprepare(काष्ठा clk_hw *hw)
अणु
	काष्ठा s2mps11_clk *s2mps11 = to_s2mps11_clk(hw);

	regmap_update_bits(s2mps11->iodev->regmap_pmic, s2mps11->reg,
			   s2mps11->mask, ~s2mps11->mask);
पूर्ण

अटल पूर्णांक s2mps11_clk_is_prepared(काष्ठा clk_hw *hw)
अणु
	पूर्णांक ret;
	u32 val;
	काष्ठा s2mps11_clk *s2mps11 = to_s2mps11_clk(hw);

	ret = regmap_पढ़ो(s2mps11->iodev->regmap_pmic,
				s2mps11->reg, &val);
	अगर (ret < 0)
		वापस -EINVAL;

	वापस val & s2mps11->mask;
पूर्ण

अटल अचिन्हित दीर्घ s2mps11_clk_recalc_rate(काष्ठा clk_hw *hw,
					     अचिन्हित दीर्घ parent_rate)
अणु
	वापस 32768;
पूर्ण

अटल स्थिर काष्ठा clk_ops s2mps11_clk_ops = अणु
	.prepare	= s2mps11_clk_prepare,
	.unprepare	= s2mps11_clk_unprepare,
	.is_prepared	= s2mps11_clk_is_prepared,
	.recalc_rate	= s2mps11_clk_recalc_rate,
पूर्ण;

/* This s2mps11_clks_init tructure is common to s2mps11, s2mps13 and s2mps14 */
अटल काष्ठा clk_init_data s2mps11_clks_init[S2MPS11_CLKS_NUM] = अणु
	[S2MPS11_CLK_AP] = अणु
		.name = "s2mps11_ap",
		.ops = &s2mps11_clk_ops,
	पूर्ण,
	[S2MPS11_CLK_CP] = अणु
		.name = "s2mps11_cp",
		.ops = &s2mps11_clk_ops,
	पूर्ण,
	[S2MPS11_CLK_BT] = अणु
		.name = "s2mps11_bt",
		.ops = &s2mps11_clk_ops,
	पूर्ण,
पूर्ण;

अटल काष्ठा device_node *s2mps11_clk_parse_dt(काष्ठा platक्रमm_device *pdev,
		काष्ठा clk_init_data *clks_init)
अणु
	काष्ठा sec_pmic_dev *iodev = dev_get_drvdata(pdev->dev.parent);
	काष्ठा device_node *clk_np;
	पूर्णांक i;

	अगर (!iodev->dev->of_node)
		वापस ERR_PTR(-EINVAL);

	clk_np = of_get_child_by_name(iodev->dev->of_node, "clocks");
	अगर (!clk_np) अणु
		dev_err(&pdev->dev, "could not find clock sub-node\n");
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	क्रम (i = 0; i < S2MPS11_CLKS_NUM; i++)
		of_property_पढ़ो_string_index(clk_np, "clock-output-names", i,
				&clks_init[i].name);

	वापस clk_np;
पूर्ण

अटल पूर्णांक s2mps11_clk_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sec_pmic_dev *iodev = dev_get_drvdata(pdev->dev.parent);
	काष्ठा s2mps11_clk *s2mps11_clks;
	काष्ठा clk_hw_onecell_data *clk_data;
	अचिन्हित पूर्णांक s2mps11_reg;
	पूर्णांक i, ret = 0;
	क्रमागत sec_device_type hwid = platक्रमm_get_device_id(pdev)->driver_data;

	s2mps11_clks = devm_kसुस्मृति(&pdev->dev, S2MPS11_CLKS_NUM,
				माप(*s2mps11_clks), GFP_KERNEL);
	अगर (!s2mps11_clks)
		वापस -ENOMEM;

	clk_data = devm_kzalloc(&pdev->dev,
				काष्ठा_size(clk_data, hws, S2MPS11_CLKS_NUM),
				GFP_KERNEL);
	अगर (!clk_data)
		वापस -ENOMEM;

	चयन (hwid) अणु
	हाल S2MPS11X:
		s2mps11_reg = S2MPS11_REG_RTC_CTRL;
		अवरोध;
	हाल S2MPS13X:
		s2mps11_reg = S2MPS13_REG_RTCCTRL;
		अवरोध;
	हाल S2MPS14X:
		s2mps11_reg = S2MPS14_REG_RTCCTRL;
		अवरोध;
	हाल S5M8767X:
		s2mps11_reg = S5M8767_REG_CTRL1;
		अवरोध;
	शेष:
		dev_err(&pdev->dev, "Invalid device type\n");
		वापस -EINVAL;
	पूर्ण

	/* Store घड़ीs of_node in first element of s2mps11_clks array */
	s2mps11_clks->clk_np = s2mps11_clk_parse_dt(pdev, s2mps11_clks_init);
	अगर (IS_ERR(s2mps11_clks->clk_np))
		वापस PTR_ERR(s2mps11_clks->clk_np);

	क्रम (i = 0; i < S2MPS11_CLKS_NUM; i++) अणु
		अगर (i == S2MPS11_CLK_CP && hwid == S2MPS14X)
			जारी; /* Skip घड़ीs not present in some devices */
		s2mps11_clks[i].iodev = iodev;
		s2mps11_clks[i].hw.init = &s2mps11_clks_init[i];
		s2mps11_clks[i].mask = 1 << i;
		s2mps11_clks[i].reg = s2mps11_reg;

		s2mps11_clks[i].clk = devm_clk_रेजिस्टर(&pdev->dev,
							&s2mps11_clks[i].hw);
		अगर (IS_ERR(s2mps11_clks[i].clk)) अणु
			dev_err(&pdev->dev, "Fail to register : %s\n",
						s2mps11_clks_init[i].name);
			ret = PTR_ERR(s2mps11_clks[i].clk);
			जाओ err_reg;
		पूर्ण

		s2mps11_clks[i].lookup = clkdev_hw_create(&s2mps11_clks[i].hw,
					s2mps11_clks_init[i].name, शून्य);
		अगर (!s2mps11_clks[i].lookup) अणु
			ret = -ENOMEM;
			जाओ err_reg;
		पूर्ण
		clk_data->hws[i] = &s2mps11_clks[i].hw;
	पूर्ण

	clk_data->num = S2MPS11_CLKS_NUM;
	of_clk_add_hw_provider(s2mps11_clks->clk_np, of_clk_hw_onecell_get,
			       clk_data);

	platक्रमm_set_drvdata(pdev, s2mps11_clks);

	वापस ret;

err_reg:
	of_node_put(s2mps11_clks[0].clk_np);
	जबतक (--i >= 0)
		clkdev_drop(s2mps11_clks[i].lookup);

	वापस ret;
पूर्ण

अटल पूर्णांक s2mps11_clk_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा s2mps11_clk *s2mps11_clks = platक्रमm_get_drvdata(pdev);
	पूर्णांक i;

	of_clk_del_provider(s2mps11_clks[0].clk_np);
	/* Drop the reference obtained in s2mps11_clk_parse_dt */
	of_node_put(s2mps11_clks[0].clk_np);

	क्रम (i = 0; i < S2MPS11_CLKS_NUM; i++) अणु
		/* Skip घड़ीs not present on S2MPS14 */
		अगर (!s2mps11_clks[i].lookup)
			जारी;
		clkdev_drop(s2mps11_clks[i].lookup);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा platक्रमm_device_id s2mps11_clk_id[] = अणु
	अणु "s2mps11-clk", S2MPS11Xपूर्ण,
	अणु "s2mps13-clk", S2MPS13Xपूर्ण,
	अणु "s2mps14-clk", S2MPS14Xपूर्ण,
	अणु "s5m8767-clk", S5M8767Xपूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(platक्रमm, s2mps11_clk_id);

#अगर_घोषित CONFIG_OF
/*
 * Device is instantiated through parent MFD device and device matching is करोne
 * through platक्रमm_device_id.
 *
 * However अगर device's DT node contains proper घड़ी compatible and driver is
 * built as a module, then the *module* matching will be करोne trough DT aliases.
 * This requires of_device_id table.  In the same समय this will not change the
 * actual *device* matching so करो not add .of_match_table.
 */
अटल स्थिर काष्ठा of_device_id s2mps11_dt_match[] __used = अणु
	अणु
		.compatible = "samsung,s2mps11-clk",
		.data = (व्योम *)S2MPS11X,
	पूर्ण, अणु
		.compatible = "samsung,s2mps13-clk",
		.data = (व्योम *)S2MPS13X,
	पूर्ण, अणु
		.compatible = "samsung,s2mps14-clk",
		.data = (व्योम *)S2MPS14X,
	पूर्ण, अणु
		.compatible = "samsung,s5m8767-clk",
		.data = (व्योम *)S5M8767X,
	पूर्ण, अणु
		/* Sentinel */
	पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, s2mps11_dt_match);
#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver s2mps11_clk_driver = अणु
	.driver = अणु
		.name  = "s2mps11-clk",
	पूर्ण,
	.probe = s2mps11_clk_probe,
	.हटाओ = s2mps11_clk_हटाओ,
	.id_table = s2mps11_clk_id,
पूर्ण;
module_platक्रमm_driver(s2mps11_clk_driver);

MODULE_DESCRIPTION("S2MPS11 Clock Driver");
MODULE_AUTHOR("Yadwinder Singh Brar <yadi.brar@samsung.com>");
MODULE_LICENSE("GPL");
