<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Marvell Armada AP806 System Controller
 *
 * Copyright (C) 2016 Marvell
 *
 * Thomas Petazzoni <thomas.petazzoni@मुक्त-electrons.com>
 *
 */

#घोषणा pr_fmt(fmt) "ap806-system-controller: " fmt

#समावेश "armada_ap_cp_helper.h"
#समावेश <linux/clk-provider.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/init.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>

#घोषणा AP806_SAR_REG			0x400
#घोषणा AP806_SAR_CLKFREQ_MODE_MASK	0x1f

#घोषणा AP806_CLK_NUM			6

अटल काष्ठा clk *ap806_clks[AP806_CLK_NUM];

अटल काष्ठा clk_onecell_data ap806_clk_data = अणु
	.clks = ap806_clks,
	.clk_num = AP806_CLK_NUM,
पूर्ण;

अटल पूर्णांक ap806_get_sar_घड़ीs(अचिन्हित पूर्णांक freq_mode,
				अचिन्हित पूर्णांक *cpuclk_freq,
				अचिन्हित पूर्णांक *dclk_freq)
अणु
	चयन (freq_mode) अणु
	हाल 0x0:
		*cpuclk_freq = 2000;
		*dclk_freq = 600;
		अवरोध;
	हाल 0x1:
		*cpuclk_freq = 2000;
		*dclk_freq = 525;
		अवरोध;
	हाल 0x6:
		*cpuclk_freq = 1800;
		*dclk_freq = 600;
		अवरोध;
	हाल 0x7:
		*cpuclk_freq = 1800;
		*dclk_freq = 525;
		अवरोध;
	हाल 0x4:
		*cpuclk_freq = 1600;
		*dclk_freq = 400;
		अवरोध;
	हाल 0xB:
		*cpuclk_freq = 1600;
		*dclk_freq = 450;
		अवरोध;
	हाल 0xD:
		*cpuclk_freq = 1600;
		*dclk_freq = 525;
		अवरोध;
	हाल 0x1a:
		*cpuclk_freq = 1400;
		*dclk_freq = 400;
		अवरोध;
	हाल 0x14:
		*cpuclk_freq = 1300;
		*dclk_freq = 400;
		अवरोध;
	हाल 0x17:
		*cpuclk_freq = 1300;
		*dclk_freq = 325;
		अवरोध;
	हाल 0x19:
		*cpuclk_freq = 1200;
		*dclk_freq = 400;
		अवरोध;
	हाल 0x13:
		*cpuclk_freq = 1000;
		*dclk_freq = 325;
		अवरोध;
	हाल 0x1d:
		*cpuclk_freq = 1000;
		*dclk_freq = 400;
		अवरोध;
	हाल 0x1c:
		*cpuclk_freq = 800;
		*dclk_freq = 400;
		अवरोध;
	हाल 0x1b:
		*cpuclk_freq = 600;
		*dclk_freq = 400;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ap807_get_sar_घड़ीs(अचिन्हित पूर्णांक freq_mode,
				अचिन्हित पूर्णांक *cpuclk_freq,
				अचिन्हित पूर्णांक *dclk_freq)
अणु
	चयन (freq_mode) अणु
	हाल 0x0:
		*cpuclk_freq = 2000;
		*dclk_freq = 1200;
		अवरोध;
	हाल 0x6:
		*cpuclk_freq = 2200;
		*dclk_freq = 1200;
		अवरोध;
	हाल 0xD:
		*cpuclk_freq = 1600;
		*dclk_freq = 1200;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ap806_syscon_common_probe(काष्ठा platक्रमm_device *pdev,
				     काष्ठा device_node *syscon_node)
अणु
	अचिन्हित पूर्णांक freq_mode, cpuclk_freq, dclk_freq;
	स्थिर अक्षर *name, *fixedclk_name;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *np = dev->of_node;
	काष्ठा regmap *regmap;
	u32 reg;
	पूर्णांक ret;

	regmap = syscon_node_to_regmap(syscon_node);
	अगर (IS_ERR(regmap)) अणु
		dev_err(dev, "cannot get regmap\n");
		वापस PTR_ERR(regmap);
	पूर्ण

	ret = regmap_पढ़ो(regmap, AP806_SAR_REG, &reg);
	अगर (ret) अणु
		dev_err(dev, "cannot read from regmap\n");
		वापस ret;
	पूर्ण

	freq_mode = reg & AP806_SAR_CLKFREQ_MODE_MASK;

	अगर (of_device_is_compatible(pdev->dev.of_node,
				    "marvell,ap806-clock")) अणु
		ret = ap806_get_sar_घड़ीs(freq_mode, &cpuclk_freq, &dclk_freq);
	पूर्ण अन्यथा अगर (of_device_is_compatible(pdev->dev.of_node,
					   "marvell,ap807-clock")) अणु
		ret = ap807_get_sar_घड़ीs(freq_mode, &cpuclk_freq, &dclk_freq);
	पूर्ण अन्यथा अणु
		dev_err(dev, "compatible not supported\n");
		वापस -EINVAL;
	पूर्ण

	अगर (ret) अणु
		dev_err(dev, "invalid Sample at Reset value\n");
		वापस ret;
	पूर्ण

	/* Convert to hertz */
	cpuclk_freq *= 1000 * 1000;
	dclk_freq *= 1000 * 1000;

	/* CPU घड़ीs depend on the Sample At Reset configuration */
	name = ap_cp_unique_name(dev, syscon_node, "pll-cluster-0");
	ap806_clks[0] = clk_रेजिस्टर_fixed_rate(dev, name, शून्य,
						0, cpuclk_freq);
	अगर (IS_ERR(ap806_clks[0])) अणु
		ret = PTR_ERR(ap806_clks[0]);
		जाओ fail0;
	पूर्ण

	name = ap_cp_unique_name(dev, syscon_node, "pll-cluster-1");
	ap806_clks[1] = clk_रेजिस्टर_fixed_rate(dev, name, शून्य, 0,
						cpuclk_freq);
	अगर (IS_ERR(ap806_clks[1])) अणु
		ret = PTR_ERR(ap806_clks[1]);
		जाओ fail1;
	पूर्ण

	/* Fixed घड़ी is always 1200 Mhz */
	fixedclk_name = ap_cp_unique_name(dev, syscon_node, "fixed");
	ap806_clks[2] = clk_रेजिस्टर_fixed_rate(dev, fixedclk_name, शून्य,
						0, 1200 * 1000 * 1000);
	अगर (IS_ERR(ap806_clks[2])) अणु
		ret = PTR_ERR(ap806_clks[2]);
		जाओ fail2;
	पूर्ण

	/* MSS Clock is fixed घड़ी भागided by 6 */
	name = ap_cp_unique_name(dev, syscon_node, "mss");
	ap806_clks[3] = clk_रेजिस्टर_fixed_factor(शून्य, name, fixedclk_name,
						  0, 1, 6);
	अगर (IS_ERR(ap806_clks[3])) अणु
		ret = PTR_ERR(ap806_clks[3]);
		जाओ fail3;
	पूर्ण

	/* SDIO(/eMMC) Clock is fixed घड़ी भागided by 3 */
	name = ap_cp_unique_name(dev, syscon_node, "sdio");
	ap806_clks[4] = clk_रेजिस्टर_fixed_factor(शून्य, name,
						  fixedclk_name,
						  0, 1, 3);
	अगर (IS_ERR(ap806_clks[4])) अणु
		ret = PTR_ERR(ap806_clks[4]);
		जाओ fail4;
	पूर्ण

	/* AP-DCLK(HCLK) Clock is DDR घड़ी भागided by 2 */
	name = ap_cp_unique_name(dev, syscon_node, "ap-dclk");
	ap806_clks[5] = clk_रेजिस्टर_fixed_rate(dev, name, शून्य, 0, dclk_freq);
	अगर (IS_ERR(ap806_clks[5])) अणु
		ret = PTR_ERR(ap806_clks[5]);
		जाओ fail5;
	पूर्ण

	ret = of_clk_add_provider(np, of_clk_src_onecell_get, &ap806_clk_data);
	अगर (ret)
		जाओ fail_clk_add;

	वापस 0;

fail_clk_add:
	clk_unरेजिस्टर_fixed_factor(ap806_clks[5]);
fail5:
	clk_unरेजिस्टर_fixed_factor(ap806_clks[4]);
fail4:
	clk_unरेजिस्टर_fixed_factor(ap806_clks[3]);
fail3:
	clk_unरेजिस्टर_fixed_rate(ap806_clks[2]);
fail2:
	clk_unरेजिस्टर_fixed_rate(ap806_clks[1]);
fail1:
	clk_unरेजिस्टर_fixed_rate(ap806_clks[0]);
fail0:
	वापस ret;
पूर्ण

अटल पूर्णांक ap806_syscon_legacy_probe(काष्ठा platक्रमm_device *pdev)
अणु
	dev_warn(&pdev->dev, FW_WARN "Using legacy device tree binding\n");
	dev_warn(&pdev->dev, FW_WARN "Update your device tree:\n");
	dev_warn(&pdev->dev, FW_WARN
		 "This binding won't be supported in future kernel\n");

	वापस ap806_syscon_common_probe(pdev, pdev->dev.of_node);

पूर्ण

अटल पूर्णांक ap806_घड़ी_probe(काष्ठा platक्रमm_device *pdev)
अणु
	वापस ap806_syscon_common_probe(pdev, pdev->dev.of_node->parent);
पूर्ण

अटल स्थिर काष्ठा of_device_id ap806_syscon_legacy_of_match[] = अणु
	अणु .compatible = "marvell,ap806-system-controller", पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_driver ap806_syscon_legacy_driver = अणु
	.probe = ap806_syscon_legacy_probe,
	.driver		= अणु
		.name	= "marvell-ap806-system-controller",
		.of_match_table = ap806_syscon_legacy_of_match,
		.suppress_bind_attrs = true,
	पूर्ण,
पूर्ण;
builtin_platक्रमm_driver(ap806_syscon_legacy_driver);

अटल स्थिर काष्ठा of_device_id ap806_घड़ी_of_match[] = अणु
	अणु .compatible = "marvell,ap806-clock", पूर्ण,
	अणु .compatible = "marvell,ap807-clock", पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_driver ap806_घड़ी_driver = अणु
	.probe = ap806_घड़ी_probe,
	.driver		= अणु
		.name	= "marvell-ap806-clock",
		.of_match_table = ap806_घड़ी_of_match,
		.suppress_bind_attrs = true,
	पूर्ण,
पूर्ण;
builtin_platक्रमm_driver(ap806_घड़ी_driver);
