<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
//
// clk-max77686.c - Clock driver क्रम Maxim 77686/MAX77802
//
// Copyright (C) 2012 Samsung Electornics
// Jonghwa Lee <jonghwa3.lee@samsung.com>

#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/err.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/mfd/max77620.h>
#समावेश <linux/mfd/max77686.h>
#समावेश <linux/mfd/max77686-निजी.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/mutex.h>
#समावेश <linux/clkdev.h>
#समावेश <linux/of.h>
#समावेश <linux/regmap.h>

#समावेश <dt-bindings/घड़ी/maxim,max77686.h>
#समावेश <dt-bindings/घड़ी/maxim,max77802.h>
#समावेश <dt-bindings/घड़ी/maxim,max77620.h>

#घोषणा MAX77802_CLOCK_LOW_JITTER_SHIFT 0x3

क्रमागत max77686_chip_name अणु
	CHIP_MAX77686,
	CHIP_MAX77802,
	CHIP_MAX77620,
पूर्ण;

काष्ठा max77686_hw_clk_info अणु
	स्थिर अक्षर *name;
	u32 clk_reg;
	u32 clk_enable_mask;
	u32 flags;
पूर्ण;

काष्ठा max77686_clk_init_data अणु
	काष्ठा regmap *regmap;
	काष्ठा clk_hw hw;
	काष्ठा clk_init_data clk_idata;
	स्थिर काष्ठा max77686_hw_clk_info *clk_info;
पूर्ण;

काष्ठा max77686_clk_driver_data अणु
	क्रमागत max77686_chip_name chip;
	काष्ठा max77686_clk_init_data *max_clk_data;
	माप_प्रकार num_clks;
पूर्ण;

अटल स्थिर काष्ठा
max77686_hw_clk_info max77686_hw_clks_info[MAX77686_CLKS_NUM] = अणु
	[MAX77686_CLK_AP] = अणु
		.name = "32khz_ap",
		.clk_reg = MAX77686_REG_32KHZ,
		.clk_enable_mask = BIT(MAX77686_CLK_AP),
	पूर्ण,
	[MAX77686_CLK_CP] = अणु
		.name = "32khz_cp",
		.clk_reg = MAX77686_REG_32KHZ,
		.clk_enable_mask = BIT(MAX77686_CLK_CP),
	पूर्ण,
	[MAX77686_CLK_PMIC] = अणु
		.name = "32khz_pmic",
		.clk_reg = MAX77686_REG_32KHZ,
		.clk_enable_mask = BIT(MAX77686_CLK_PMIC),
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा
max77686_hw_clk_info max77802_hw_clks_info[MAX77802_CLKS_NUM] = अणु
	[MAX77802_CLK_32K_AP] = अणु
		.name = "32khz_ap",
		.clk_reg = MAX77802_REG_32KHZ,
		.clk_enable_mask = BIT(MAX77802_CLK_32K_AP),
	पूर्ण,
	[MAX77802_CLK_32K_CP] = अणु
		.name = "32khz_cp",
		.clk_reg = MAX77802_REG_32KHZ,
		.clk_enable_mask = BIT(MAX77802_CLK_32K_CP),
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा
max77686_hw_clk_info max77620_hw_clks_info[MAX77620_CLKS_NUM] = अणु
	[MAX77620_CLK_32K_OUT0] = अणु
		.name = "32khz_out0",
		.clk_reg = MAX77620_REG_CNFG1_32K,
		.clk_enable_mask = MAX77620_CNFG1_32K_OUT0_EN,
	पूर्ण,
पूर्ण;

अटल काष्ठा max77686_clk_init_data *to_max77686_clk_init_data(
				काष्ठा clk_hw *hw)
अणु
	वापस container_of(hw, काष्ठा max77686_clk_init_data, hw);
पूर्ण

अटल पूर्णांक max77686_clk_prepare(काष्ठा clk_hw *hw)
अणु
	काष्ठा max77686_clk_init_data *max77686 = to_max77686_clk_init_data(hw);

	वापस regmap_update_bits(max77686->regmap, max77686->clk_info->clk_reg,
				  max77686->clk_info->clk_enable_mask,
				  max77686->clk_info->clk_enable_mask);
पूर्ण

अटल व्योम max77686_clk_unprepare(काष्ठा clk_hw *hw)
अणु
	काष्ठा max77686_clk_init_data *max77686 = to_max77686_clk_init_data(hw);

	regmap_update_bits(max77686->regmap, max77686->clk_info->clk_reg,
			   max77686->clk_info->clk_enable_mask,
			   ~max77686->clk_info->clk_enable_mask);
पूर्ण

अटल पूर्णांक max77686_clk_is_prepared(काष्ठा clk_hw *hw)
अणु
	काष्ठा max77686_clk_init_data *max77686 = to_max77686_clk_init_data(hw);
	पूर्णांक ret;
	u32 val;

	ret = regmap_पढ़ो(max77686->regmap, max77686->clk_info->clk_reg, &val);

	अगर (ret < 0)
		वापस -EINVAL;

	वापस val & max77686->clk_info->clk_enable_mask;
पूर्ण

अटल अचिन्हित दीर्घ max77686_recalc_rate(काष्ठा clk_hw *hw,
					  अचिन्हित दीर्घ parent_rate)
अणु
	वापस 32768;
पूर्ण

अटल स्थिर काष्ठा clk_ops max77686_clk_ops = अणु
	.prepare	= max77686_clk_prepare,
	.unprepare	= max77686_clk_unprepare,
	.is_prepared	= max77686_clk_is_prepared,
	.recalc_rate	= max77686_recalc_rate,
पूर्ण;

अटल काष्ठा clk_hw *
of_clk_max77686_get(काष्ठा of_phandle_args *clkspec, व्योम *data)
अणु
	काष्ठा max77686_clk_driver_data *drv_data = data;
	अचिन्हित पूर्णांक idx = clkspec->args[0];

	अगर (idx >= drv_data->num_clks) अणु
		pr_err("%s: invalid index %u\n", __func__, idx);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	वापस &drv_data->max_clk_data[idx].hw;
पूर्ण

अटल पूर्णांक max77686_clk_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device *parent = dev->parent;
	स्थिर काष्ठा platक्रमm_device_id *id = platक्रमm_get_device_id(pdev);
	काष्ठा max77686_clk_driver_data *drv_data;
	स्थिर काष्ठा max77686_hw_clk_info *hw_clks;
	काष्ठा regmap *regmap;
	पूर्णांक i, ret, num_clks;

	drv_data = devm_kzalloc(dev, माप(*drv_data), GFP_KERNEL);
	अगर (!drv_data)
		वापस -ENOMEM;

	regmap = dev_get_regmap(parent, शून्य);
	अगर (!regmap) अणु
		dev_err(dev, "Failed to get rtc regmap\n");
		वापस -ENODEV;
	पूर्ण

	drv_data->chip = id->driver_data;

	चयन (drv_data->chip) अणु
	हाल CHIP_MAX77686:
		num_clks = MAX77686_CLKS_NUM;
		hw_clks = max77686_hw_clks_info;
		अवरोध;

	हाल CHIP_MAX77802:
		num_clks = MAX77802_CLKS_NUM;
		hw_clks = max77802_hw_clks_info;
		अवरोध;

	हाल CHIP_MAX77620:
		num_clks = MAX77620_CLKS_NUM;
		hw_clks = max77620_hw_clks_info;
		अवरोध;

	शेष:
		dev_err(dev, "Unknown Chip ID\n");
		वापस -EINVAL;
	पूर्ण

	drv_data->num_clks = num_clks;
	drv_data->max_clk_data = devm_kसुस्मृति(dev, num_clks,
					      माप(*drv_data->max_clk_data),
					      GFP_KERNEL);
	अगर (!drv_data->max_clk_data)
		वापस -ENOMEM;

	क्रम (i = 0; i < num_clks; i++) अणु
		काष्ठा max77686_clk_init_data *max_clk_data;
		स्थिर अक्षर *clk_name;

		max_clk_data = &drv_data->max_clk_data[i];

		max_clk_data->regmap = regmap;
		max_clk_data->clk_info = &hw_clks[i];
		max_clk_data->clk_idata.flags = hw_clks[i].flags;
		max_clk_data->clk_idata.ops = &max77686_clk_ops;

		अगर (parent->of_node &&
		    !of_property_पढ़ो_string_index(parent->of_node,
						   "clock-output-names",
						   i, &clk_name))
			max_clk_data->clk_idata.name = clk_name;
		अन्यथा
			max_clk_data->clk_idata.name = hw_clks[i].name;

		max_clk_data->hw.init = &max_clk_data->clk_idata;

		ret = devm_clk_hw_रेजिस्टर(dev, &max_clk_data->hw);
		अगर (ret) अणु
			dev_err(dev, "Failed to clock register: %d\n", ret);
			वापस ret;
		पूर्ण

		ret = devm_clk_hw_रेजिस्टर_clkdev(dev, &max_clk_data->hw,
						  max_clk_data->clk_idata.name,
						  शून्य);
		अगर (ret < 0) अणु
			dev_err(dev, "Failed to clkdev register: %d\n", ret);
			वापस ret;
		पूर्ण
	पूर्ण

	अगर (parent->of_node) अणु
		ret = devm_of_clk_add_hw_provider(dev, of_clk_max77686_get,
						  drv_data);

		अगर (ret < 0) अणु
			dev_err(dev, "Failed to register OF clock provider: %d\n",
				ret);
			वापस ret;
		पूर्ण
	पूर्ण

	/* MAX77802: Enable low-jitter mode on the 32khz घड़ीs. */
	अगर (drv_data->chip == CHIP_MAX77802) अणु
		ret = regmap_update_bits(regmap, MAX77802_REG_32KHZ,
					 1 << MAX77802_CLOCK_LOW_JITTER_SHIFT,
					 1 << MAX77802_CLOCK_LOW_JITTER_SHIFT);
		अगर (ret < 0) अणु
			dev_err(dev, "Failed to config low-jitter: %d\n", ret);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा platक्रमm_device_id max77686_clk_id[] = अणु
	अणु "max77686-clk", .driver_data = CHIP_MAX77686, पूर्ण,
	अणु "max77802-clk", .driver_data = CHIP_MAX77802, पूर्ण,
	अणु "max77620-clock", .driver_data = CHIP_MAX77620, पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(platक्रमm, max77686_clk_id);

अटल काष्ठा platक्रमm_driver max77686_clk_driver = अणु
	.driver = अणु
		.name  = "max77686-clk",
	पूर्ण,
	.probe = max77686_clk_probe,
	.id_table = max77686_clk_id,
पूर्ण;

module_platक्रमm_driver(max77686_clk_driver);

MODULE_DESCRIPTION("MAXIM 77686 Clock Driver");
MODULE_AUTHOR("Jonghwa Lee <jonghwa3.lee@samsung.com>");
MODULE_LICENSE("GPL");
