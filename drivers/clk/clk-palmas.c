<शैली गुरु>
/*
 * Clock driver क्रम Palmas device.
 *
 * Copyright (c) 2013, NVIDIA Corporation.
 * Copyright (c) 2013-2014 Texas Instruments, Inc.
 *
 * Author:	Laxman Dewangan <ldewangan@nvidia.com>
 *		Peter Ujfalusi <peter.ujfalusi@ti.com>
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License as
 * published by the Free Software Foundation version 2.
 *
 * This program is distributed "as is" WITHOUT ANY WARRANTY of any kind,
 * whether express or implied; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License क्रम more details.
 */

#समावेश <linux/clk.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/mfd/palmas.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>

#घोषणा PALMAS_CLOCK_DT_EXT_CONTROL_ENABLE1	1
#घोषणा PALMAS_CLOCK_DT_EXT_CONTROL_ENABLE2	2
#घोषणा PALMAS_CLOCK_DT_EXT_CONTROL_NSLEEP	3

काष्ठा palmas_clk32k_desc अणु
	स्थिर अक्षर *clk_name;
	अचिन्हित पूर्णांक control_reg;
	अचिन्हित पूर्णांक enable_mask;
	अचिन्हित पूर्णांक sleep_mask;
	अचिन्हित पूर्णांक sleep_reqstr_id;
	पूर्णांक delay;
पूर्ण;

काष्ठा palmas_घड़ी_info अणु
	काष्ठा device *dev;
	काष्ठा clk_hw hw;
	काष्ठा palmas *palmas;
	स्थिर काष्ठा palmas_clk32k_desc *clk_desc;
	पूर्णांक ext_control_pin;
पूर्ण;

अटल अंतरभूत काष्ठा palmas_घड़ी_info *to_palmas_clks_info(काष्ठा clk_hw *hw)
अणु
	वापस container_of(hw, काष्ठा palmas_घड़ी_info, hw);
पूर्ण

अटल अचिन्हित दीर्घ palmas_clks_recalc_rate(काष्ठा clk_hw *hw,
					     अचिन्हित दीर्घ parent_rate)
अणु
	वापस 32768;
पूर्ण

अटल पूर्णांक palmas_clks_prepare(काष्ठा clk_hw *hw)
अणु
	काष्ठा palmas_घड़ी_info *cinfo = to_palmas_clks_info(hw);
	पूर्णांक ret;

	ret = palmas_update_bits(cinfo->palmas, PALMAS_RESOURCE_BASE,
				 cinfo->clk_desc->control_reg,
				 cinfo->clk_desc->enable_mask,
				 cinfo->clk_desc->enable_mask);
	अगर (ret < 0)
		dev_err(cinfo->dev, "Reg 0x%02x update failed, %d\n",
			cinfo->clk_desc->control_reg, ret);
	अन्यथा अगर (cinfo->clk_desc->delay)
		udelay(cinfo->clk_desc->delay);

	वापस ret;
पूर्ण

अटल व्योम palmas_clks_unprepare(काष्ठा clk_hw *hw)
अणु
	काष्ठा palmas_घड़ी_info *cinfo = to_palmas_clks_info(hw);
	पूर्णांक ret;

	/*
	 * Clock can be disabled through बाह्यal pin अगर it is बाह्यally
	 * controlled.
	 */
	अगर (cinfo->ext_control_pin)
		वापस;

	ret = palmas_update_bits(cinfo->palmas, PALMAS_RESOURCE_BASE,
				 cinfo->clk_desc->control_reg,
				 cinfo->clk_desc->enable_mask, 0);
	अगर (ret < 0)
		dev_err(cinfo->dev, "Reg 0x%02x update failed, %d\n",
			cinfo->clk_desc->control_reg, ret);
पूर्ण

अटल पूर्णांक palmas_clks_is_prepared(काष्ठा clk_hw *hw)
अणु
	काष्ठा palmas_घड़ी_info *cinfo = to_palmas_clks_info(hw);
	पूर्णांक ret;
	u32 val;

	अगर (cinfo->ext_control_pin)
		वापस 1;

	ret = palmas_पढ़ो(cinfo->palmas, PALMAS_RESOURCE_BASE,
			  cinfo->clk_desc->control_reg, &val);
	अगर (ret < 0) अणु
		dev_err(cinfo->dev, "Reg 0x%02x read failed, %d\n",
			cinfo->clk_desc->control_reg, ret);
		वापस ret;
	पूर्ण
	वापस !!(val & cinfo->clk_desc->enable_mask);
पूर्ण

अटल स्थिर काष्ठा clk_ops palmas_clks_ops = अणु
	.prepare	= palmas_clks_prepare,
	.unprepare	= palmas_clks_unprepare,
	.is_prepared	= palmas_clks_is_prepared,
	.recalc_rate	= palmas_clks_recalc_rate,
पूर्ण;

काष्ठा palmas_clks_of_match_data अणु
	काष्ठा clk_init_data init;
	स्थिर काष्ठा palmas_clk32k_desc desc;
पूर्ण;

अटल स्थिर काष्ठा palmas_clks_of_match_data palmas_of_clk32kg = अणु
	.init = अणु
		.name = "clk32kg",
		.ops = &palmas_clks_ops,
		.flags = CLK_IGNORE_UNUSED,
	पूर्ण,
	.desc = अणु
		.clk_name = "clk32kg",
		.control_reg = PALMAS_CLK32KG_CTRL,
		.enable_mask = PALMAS_CLK32KG_CTRL_MODE_ACTIVE,
		.sleep_mask = PALMAS_CLK32KG_CTRL_MODE_SLEEP,
		.sleep_reqstr_id = PALMAS_EXTERNAL_REQSTR_ID_CLK32KG,
		.delay = 200,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा palmas_clks_of_match_data palmas_of_clk32kgaudio = अणु
	.init = अणु
		.name = "clk32kgaudio",
		.ops = &palmas_clks_ops,
		.flags = CLK_IGNORE_UNUSED,
	पूर्ण,
	.desc = अणु
		.clk_name = "clk32kgaudio",
		.control_reg = PALMAS_CLK32KGAUDIO_CTRL,
		.enable_mask = PALMAS_CLK32KG_CTRL_MODE_ACTIVE,
		.sleep_mask = PALMAS_CLK32KG_CTRL_MODE_SLEEP,
		.sleep_reqstr_id = PALMAS_EXTERNAL_REQSTR_ID_CLK32KGAUDIO,
		.delay = 200,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा of_device_id palmas_clks_of_match[] = अणु
	अणु
		.compatible = "ti,palmas-clk32kg",
		.data = &palmas_of_clk32kg,
	पूर्ण,
	अणु
		.compatible = "ti,palmas-clk32kgaudio",
		.data = &palmas_of_clk32kgaudio,
	पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, palmas_clks_of_match);

अटल व्योम palmas_clks_get_clk_data(काष्ठा platक्रमm_device *pdev,
				     काष्ठा palmas_घड़ी_info *cinfo)
अणु
	काष्ठा device_node *node = pdev->dev.of_node;
	अचिन्हित पूर्णांक prop;
	पूर्णांक ret;

	ret = of_property_पढ़ो_u32(node, "ti,external-sleep-control",
				   &prop);
	अगर (ret)
		वापस;

	चयन (prop) अणु
	हाल PALMAS_CLOCK_DT_EXT_CONTROL_ENABLE1:
		prop = PALMAS_EXT_CONTROL_ENABLE1;
		अवरोध;
	हाल PALMAS_CLOCK_DT_EXT_CONTROL_ENABLE2:
		prop = PALMAS_EXT_CONTROL_ENABLE2;
		अवरोध;
	हाल PALMAS_CLOCK_DT_EXT_CONTROL_NSLEEP:
		prop = PALMAS_EXT_CONTROL_NSLEEP;
		अवरोध;
	शेष:
		dev_warn(&pdev->dev, "%pOFn: Invalid ext control option: %u\n",
			 node, prop);
		prop = 0;
		अवरोध;
	पूर्ण
	cinfo->ext_control_pin = prop;
पूर्ण

अटल पूर्णांक palmas_clks_init_configure(काष्ठा palmas_घड़ी_info *cinfo)
अणु
	पूर्णांक ret;

	ret = palmas_update_bits(cinfo->palmas, PALMAS_RESOURCE_BASE,
				 cinfo->clk_desc->control_reg,
				 cinfo->clk_desc->sleep_mask, 0);
	अगर (ret < 0) अणु
		dev_err(cinfo->dev, "Reg 0x%02x update failed, %d\n",
			cinfo->clk_desc->control_reg, ret);
		वापस ret;
	पूर्ण

	अगर (cinfo->ext_control_pin) अणु
		ret = clk_prepare(cinfo->hw.clk);
		अगर (ret < 0) अणु
			dev_err(cinfo->dev, "Clock prep failed, %d\n", ret);
			वापस ret;
		पूर्ण

		ret = palmas_ext_control_req_config(cinfo->palmas,
					cinfo->clk_desc->sleep_reqstr_id,
					cinfo->ext_control_pin, true);
		अगर (ret < 0) अणु
			dev_err(cinfo->dev, "Ext config for %s failed, %d\n",
				cinfo->clk_desc->clk_name, ret);
			clk_unprepare(cinfo->hw.clk);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण
अटल पूर्णांक palmas_clks_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा palmas *palmas = dev_get_drvdata(pdev->dev.parent);
	काष्ठा device_node *node = pdev->dev.of_node;
	स्थिर काष्ठा palmas_clks_of_match_data *match_data;
	काष्ठा palmas_घड़ी_info *cinfo;
	पूर्णांक ret;

	match_data = of_device_get_match_data(&pdev->dev);
	अगर (!match_data)
		वापस 1;

	cinfo = devm_kzalloc(&pdev->dev, माप(*cinfo), GFP_KERNEL);
	अगर (!cinfo)
		वापस -ENOMEM;

	palmas_clks_get_clk_data(pdev, cinfo);
	platक्रमm_set_drvdata(pdev, cinfo);

	cinfo->dev = &pdev->dev;
	cinfo->palmas = palmas;

	cinfo->clk_desc = &match_data->desc;
	cinfo->hw.init = &match_data->init;
	ret = devm_clk_hw_रेजिस्टर(&pdev->dev, &cinfo->hw);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Fail to register clock %s, %d\n",
			match_data->desc.clk_name, ret);
		वापस ret;
	पूर्ण

	ret = palmas_clks_init_configure(cinfo);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "Clock config failed, %d\n", ret);
		वापस ret;
	पूर्ण

	ret = of_clk_add_hw_provider(node, of_clk_hw_simple_get, &cinfo->hw);
	अगर (ret < 0)
		dev_err(&pdev->dev, "Fail to add clock driver, %d\n", ret);
	वापस ret;
पूर्ण

अटल पूर्णांक palmas_clks_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	of_clk_del_provider(pdev->dev.of_node);
	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver palmas_clks_driver = अणु
	.driver = अणु
		.name = "palmas-clk",
		.of_match_table = palmas_clks_of_match,
	पूर्ण,
	.probe = palmas_clks_probe,
	.हटाओ = palmas_clks_हटाओ,
पूर्ण;

module_platक्रमm_driver(palmas_clks_driver);

MODULE_DESCRIPTION("Clock driver for Palmas Series Devices");
MODULE_ALIAS("platform:palmas-clk");
MODULE_AUTHOR("Peter Ujfalusi <peter.ujfalusi@ti.com>");
MODULE_LICENSE("GPL v2");
