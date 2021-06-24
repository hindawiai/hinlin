<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Marvell Armada CP110 System Controller
 *
 * Copyright (C) 2016 Marvell
 *
 * Thomas Petazzoni <thomas.petazzoni@मुक्त-electrons.com>
 *
 */

/*
 * CP110 has 6 core घड़ीs:
 *
 *  - PLL0		(1 Ghz)
 *    - PPv2 core	(1/3 PLL0)
 *    - x2 Core		(1/2 PLL0)
 *	- Core		(1/2 x2 Core)
 *    - SDIO		(2/5 PLL0)
 *
 *  - न_अंकD घड़ी, which is either:
 *    - Equal to SDIO घड़ी
 *    - 2/5 PLL0
 *
 * CP110 has 32 gateable घड़ीs, क्रम the various peripherals in the IP.
 */

#घोषणा pr_fmt(fmt) "cp110-system-controller: " fmt

#समावेश "armada_ap_cp_helper.h"
#समावेश <linux/clk-provider.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/init.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/slab.h>

#घोषणा CP110_PM_CLOCK_GATING_REG	0x220
#घोषणा CP110_न_अंकD_FLASH_CLK_CTRL_REG	0x700
#घोषणा    NF_CLOCK_SEL_400_MASK	BIT(0)

क्रमागत अणु
	CP110_CLK_TYPE_CORE,
	CP110_CLK_TYPE_GATABLE,
पूर्ण;

#घोषणा CP110_MAX_CORE_CLOCKS		6
#घोषणा CP110_MAX_GATABLE_CLOCKS	32

#घोषणा CP110_CLK_NUM \
	(CP110_MAX_CORE_CLOCKS + CP110_MAX_GATABLE_CLOCKS)

#घोषणा CP110_CORE_PLL0			0
#घोषणा CP110_CORE_PPV2			1
#घोषणा CP110_CORE_X2CORE		2
#घोषणा CP110_CORE_CORE			3
#घोषणा CP110_CORE_न_अंकD			4
#घोषणा CP110_CORE_SDIO			5

/* A number of gateable घड़ीs need special handling */
#घोषणा CP110_GATE_AUDIO		0
#घोषणा CP110_GATE_COMM_UNIT		1
#घोषणा CP110_GATE_न_अंकD			2
#घोषणा CP110_GATE_PPV2			3
#घोषणा CP110_GATE_SDIO			4
#घोषणा CP110_GATE_MG			5
#घोषणा CP110_GATE_MG_CORE		6
#घोषणा CP110_GATE_XOR1			7
#घोषणा CP110_GATE_XOR0			8
#घोषणा CP110_GATE_GOP_DP		9
#घोषणा CP110_GATE_PCIE_X1_0		11
#घोषणा CP110_GATE_PCIE_X1_1		12
#घोषणा CP110_GATE_PCIE_X4		13
#घोषणा CP110_GATE_PCIE_XOR		14
#घोषणा CP110_GATE_SATA			15
#घोषणा CP110_GATE_SATA_USB		16
#घोषणा CP110_GATE_MAIN			17
#घोषणा CP110_GATE_SDMMC_GOP		18
#घोषणा CP110_GATE_SLOW_IO		21
#घोषणा CP110_GATE_USB3H0		22
#घोषणा CP110_GATE_USB3H1		23
#घोषणा CP110_GATE_USB3DEV		24
#घोषणा CP110_GATE_EIP150		25
#घोषणा CP110_GATE_EIP197		26

अटल स्थिर अक्षर * स्थिर gate_base_names[] = अणु
	[CP110_GATE_AUDIO]	= "audio",
	[CP110_GATE_COMM_UNIT]	= "communit",
	[CP110_GATE_न_अंकD]	= "nand",
	[CP110_GATE_PPV2]	= "ppv2",
	[CP110_GATE_SDIO]	= "sdio",
	[CP110_GATE_MG]		= "mg-domain",
	[CP110_GATE_MG_CORE]	= "mg-core",
	[CP110_GATE_XOR1]	= "xor1",
	[CP110_GATE_XOR0]	= "xor0",
	[CP110_GATE_GOP_DP]	= "gop-dp",
	[CP110_GATE_PCIE_X1_0]	= "pcie_x10",
	[CP110_GATE_PCIE_X1_1]	= "pcie_x11",
	[CP110_GATE_PCIE_X4]	= "pcie_x4",
	[CP110_GATE_PCIE_XOR]	= "pcie-xor",
	[CP110_GATE_SATA]	= "sata",
	[CP110_GATE_SATA_USB]	= "sata-usb",
	[CP110_GATE_MAIN]	= "main",
	[CP110_GATE_SDMMC_GOP]	= "sd-mmc-gop",
	[CP110_GATE_SLOW_IO]	= "slow-io",
	[CP110_GATE_USB3H0]	= "usb3h0",
	[CP110_GATE_USB3H1]	= "usb3h1",
	[CP110_GATE_USB3DEV]	= "usb3dev",
	[CP110_GATE_EIP150]	= "eip150",
	[CP110_GATE_EIP197]	= "eip197"
पूर्ण;

काष्ठा cp110_gate_clk अणु
	काष्ठा clk_hw hw;
	काष्ठा regmap *regmap;
	u8 bit_idx;
पूर्ण;

#घोषणा to_cp110_gate_clk(hw) container_of(hw, काष्ठा cp110_gate_clk, hw)

अटल पूर्णांक cp110_gate_enable(काष्ठा clk_hw *hw)
अणु
	काष्ठा cp110_gate_clk *gate = to_cp110_gate_clk(hw);

	regmap_update_bits(gate->regmap, CP110_PM_CLOCK_GATING_REG,
			   BIT(gate->bit_idx), BIT(gate->bit_idx));

	वापस 0;
पूर्ण

अटल व्योम cp110_gate_disable(काष्ठा clk_hw *hw)
अणु
	काष्ठा cp110_gate_clk *gate = to_cp110_gate_clk(hw);

	regmap_update_bits(gate->regmap, CP110_PM_CLOCK_GATING_REG,
			   BIT(gate->bit_idx), 0);
पूर्ण

अटल पूर्णांक cp110_gate_is_enabled(काष्ठा clk_hw *hw)
अणु
	काष्ठा cp110_gate_clk *gate = to_cp110_gate_clk(hw);
	u32 val;

	regmap_पढ़ो(gate->regmap, CP110_PM_CLOCK_GATING_REG, &val);

	वापस val & BIT(gate->bit_idx);
पूर्ण

अटल स्थिर काष्ठा clk_ops cp110_gate_ops = अणु
	.enable = cp110_gate_enable,
	.disable = cp110_gate_disable,
	.is_enabled = cp110_gate_is_enabled,
पूर्ण;

अटल काष्ठा clk_hw *cp110_रेजिस्टर_gate(स्थिर अक्षर *name,
					  स्थिर अक्षर *parent_name,
					  काष्ठा regmap *regmap, u8 bit_idx)
अणु
	काष्ठा cp110_gate_clk *gate;
	काष्ठा clk_hw *hw;
	काष्ठा clk_init_data init;
	पूर्णांक ret;

	gate = kzalloc(माप(*gate), GFP_KERNEL);
	अगर (!gate)
		वापस ERR_PTR(-ENOMEM);

	स_रखो(&init, 0, माप(init));

	init.name = name;
	init.ops = &cp110_gate_ops;
	init.parent_names = &parent_name;
	init.num_parents = 1;

	gate->regmap = regmap;
	gate->bit_idx = bit_idx;
	gate->hw.init = &init;

	hw = &gate->hw;
	ret = clk_hw_रेजिस्टर(शून्य, hw);
	अगर (ret) अणु
		kमुक्त(gate);
		hw = ERR_PTR(ret);
	पूर्ण

	वापस hw;
पूर्ण

अटल व्योम cp110_unरेजिस्टर_gate(काष्ठा clk_hw *hw)
अणु
	clk_hw_unरेजिस्टर(hw);
	kमुक्त(to_cp110_gate_clk(hw));
पूर्ण

अटल काष्ठा clk_hw *cp110_of_clk_get(काष्ठा of_phandle_args *clkspec,
				       व्योम *data)
अणु
	काष्ठा clk_hw_onecell_data *clk_data = data;
	अचिन्हित पूर्णांक type = clkspec->args[0];
	अचिन्हित पूर्णांक idx = clkspec->args[1];

	अगर (type == CP110_CLK_TYPE_CORE) अणु
		अगर (idx >= CP110_MAX_CORE_CLOCKS)
			वापस ERR_PTR(-EINVAL);
		वापस clk_data->hws[idx];
	पूर्ण अन्यथा अगर (type == CP110_CLK_TYPE_GATABLE) अणु
		अगर (idx >= CP110_MAX_GATABLE_CLOCKS)
			वापस ERR_PTR(-EINVAL);
		वापस clk_data->hws[CP110_MAX_CORE_CLOCKS + idx];
	पूर्ण

	वापस ERR_PTR(-EINVAL);
पूर्ण

अटल पूर्णांक cp110_syscon_common_probe(काष्ठा platक्रमm_device *pdev,
				     काष्ठा device_node *syscon_node)
अणु
	काष्ठा regmap *regmap;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *np = dev->of_node;
	स्थिर अक्षर *ppv2_name, *pll0_name, *core_name, *x2core_name, *nand_name,
		*sdio_name;
	काष्ठा clk_hw_onecell_data *cp110_clk_data;
	काष्ठा clk_hw *hw, **cp110_clks;
	u32 nand_clk_ctrl;
	पूर्णांक i, ret;
	अक्षर *gate_name[ARRAY_SIZE(gate_base_names)];

	regmap = syscon_node_to_regmap(syscon_node);
	अगर (IS_ERR(regmap))
		वापस PTR_ERR(regmap);

	ret = regmap_पढ़ो(regmap, CP110_न_अंकD_FLASH_CLK_CTRL_REG,
			  &nand_clk_ctrl);
	अगर (ret)
		वापस ret;

	cp110_clk_data = devm_kzalloc(dev, काष्ठा_size(cp110_clk_data, hws,
						       CP110_CLK_NUM),
				      GFP_KERNEL);
	अगर (!cp110_clk_data)
		वापस -ENOMEM;

	cp110_clks = cp110_clk_data->hws;
	cp110_clk_data->num = CP110_CLK_NUM;

	/* Register the PLL0 which is the root of the hw tree */
	pll0_name = ap_cp_unique_name(dev, syscon_node, "pll0");
	hw = clk_hw_रेजिस्टर_fixed_rate(शून्य, pll0_name, शून्य, 0,
					1000 * 1000 * 1000);
	अगर (IS_ERR(hw)) अणु
		ret = PTR_ERR(hw);
		जाओ fail_pll0;
	पूर्ण

	cp110_clks[CP110_CORE_PLL0] = hw;

	/* PPv2 is PLL0/3 */
	ppv2_name = ap_cp_unique_name(dev, syscon_node, "ppv2-core");
	hw = clk_hw_रेजिस्टर_fixed_factor(शून्य, ppv2_name, pll0_name, 0, 1, 3);
	अगर (IS_ERR(hw)) अणु
		ret = PTR_ERR(hw);
		जाओ fail_ppv2;
	पूर्ण

	cp110_clks[CP110_CORE_PPV2] = hw;

	/* X2CORE घड़ी is PLL0/2 */
	x2core_name = ap_cp_unique_name(dev, syscon_node, "x2core");
	hw = clk_hw_रेजिस्टर_fixed_factor(शून्य, x2core_name, pll0_name,
					  0, 1, 2);
	अगर (IS_ERR(hw)) अणु
		ret = PTR_ERR(hw);
		जाओ fail_eip;
	पूर्ण

	cp110_clks[CP110_CORE_X2CORE] = hw;

	/* Core घड़ी is X2CORE/2 */
	core_name = ap_cp_unique_name(dev, syscon_node, "core");
	hw = clk_hw_रेजिस्टर_fixed_factor(शून्य, core_name, x2core_name,
					  0, 1, 2);
	अगर (IS_ERR(hw)) अणु
		ret = PTR_ERR(hw);
		जाओ fail_core;
	पूर्ण

	cp110_clks[CP110_CORE_CORE] = hw;
	/* न_अंकD can be either PLL0/2.5 or core घड़ी */
	nand_name = ap_cp_unique_name(dev, syscon_node, "nand-core");
	अगर (nand_clk_ctrl & NF_CLOCK_SEL_400_MASK)
		hw = clk_hw_रेजिस्टर_fixed_factor(शून्य, nand_name,
						   pll0_name, 0, 2, 5);
	अन्यथा
		hw = clk_hw_रेजिस्टर_fixed_factor(शून्य, nand_name,
						   core_name, 0, 1, 1);
	अगर (IS_ERR(hw)) अणु
		ret = PTR_ERR(hw);
		जाओ fail_nand;
	पूर्ण

	cp110_clks[CP110_CORE_न_अंकD] = hw;

	/* SDIO घड़ी is PLL0/2.5 */
	sdio_name = ap_cp_unique_name(dev, syscon_node, "sdio-core");
	hw = clk_hw_रेजिस्टर_fixed_factor(शून्य, sdio_name,
					  pll0_name, 0, 2, 5);
	अगर (IS_ERR(hw)) अणु
		ret = PTR_ERR(hw);
		जाओ fail_sdio;
	पूर्ण

	cp110_clks[CP110_CORE_SDIO] = hw;

	/* create the unique name क्रम all the gate घड़ीs */
	क्रम (i = 0; i < ARRAY_SIZE(gate_base_names); i++)
		gate_name[i] =	ap_cp_unique_name(dev, syscon_node,
						  gate_base_names[i]);

	क्रम (i = 0; i < ARRAY_SIZE(gate_base_names); i++) अणु
		स्थिर अक्षर *parent;

		अगर (gate_name[i] == शून्य)
			जारी;

		चयन (i) अणु
		हाल CP110_GATE_न_अंकD:
			parent = nand_name;
			अवरोध;
		हाल CP110_GATE_MG:
		हाल CP110_GATE_GOP_DP:
		हाल CP110_GATE_PPV2:
			parent = ppv2_name;
			अवरोध;
		हाल CP110_GATE_SDIO:
			parent = sdio_name;
			अवरोध;
		हाल CP110_GATE_MAIN:
		हाल CP110_GATE_PCIE_XOR:
		हाल CP110_GATE_PCIE_X4:
		हाल CP110_GATE_EIP150:
		हाल CP110_GATE_EIP197:
			parent = x2core_name;
			अवरोध;
		शेष:
			parent = core_name;
			अवरोध;
		पूर्ण
		hw = cp110_रेजिस्टर_gate(gate_name[i], parent, regmap, i);

		अगर (IS_ERR(hw)) अणु
			ret = PTR_ERR(hw);
			जाओ fail_gate;
		पूर्ण

		cp110_clks[CP110_MAX_CORE_CLOCKS + i] = hw;
	पूर्ण

	ret = of_clk_add_hw_provider(np, cp110_of_clk_get, cp110_clk_data);
	अगर (ret)
		जाओ fail_clk_add;

	platक्रमm_set_drvdata(pdev, cp110_clks);

	वापस 0;

fail_clk_add:
fail_gate:
	क्रम (i = 0; i < CP110_MAX_GATABLE_CLOCKS; i++) अणु
		hw = cp110_clks[CP110_MAX_CORE_CLOCKS + i];

		अगर (hw)
			cp110_unरेजिस्टर_gate(hw);
	पूर्ण

	clk_hw_unरेजिस्टर_fixed_factor(cp110_clks[CP110_CORE_SDIO]);
fail_sdio:
	clk_hw_unरेजिस्टर_fixed_factor(cp110_clks[CP110_CORE_न_अंकD]);
fail_nand:
	clk_hw_unरेजिस्टर_fixed_factor(cp110_clks[CP110_CORE_CORE]);
fail_core:
	clk_hw_unरेजिस्टर_fixed_factor(cp110_clks[CP110_CORE_X2CORE]);
fail_eip:
	clk_hw_unरेजिस्टर_fixed_factor(cp110_clks[CP110_CORE_PPV2]);
fail_ppv2:
	clk_hw_unरेजिस्टर_fixed_rate(cp110_clks[CP110_CORE_PLL0]);
fail_pll0:
	वापस ret;
पूर्ण

अटल पूर्णांक cp110_syscon_legacy_clk_probe(काष्ठा platक्रमm_device *pdev)
अणु
	dev_warn(&pdev->dev, FW_WARN "Using legacy device tree binding\n");
	dev_warn(&pdev->dev, FW_WARN "Update your device tree:\n");
	dev_warn(&pdev->dev, FW_WARN
		 "This binding won't be supported in future kernels\n");

	वापस cp110_syscon_common_probe(pdev, pdev->dev.of_node);
पूर्ण

अटल पूर्णांक cp110_clk_probe(काष्ठा platक्रमm_device *pdev)
अणु
	वापस cp110_syscon_common_probe(pdev, pdev->dev.of_node->parent);
पूर्ण

अटल स्थिर काष्ठा of_device_id cp110_syscon_legacy_of_match[] = अणु
	अणु .compatible = "marvell,cp110-system-controller0", पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_driver cp110_syscon_legacy_driver = अणु
	.probe = cp110_syscon_legacy_clk_probe,
	.driver		= अणु
		.name	= "marvell-cp110-system-controller0",
		.of_match_table = cp110_syscon_legacy_of_match,
		.suppress_bind_attrs = true,
	पूर्ण,
पूर्ण;
builtin_platक्रमm_driver(cp110_syscon_legacy_driver);

अटल स्थिर काष्ठा of_device_id cp110_घड़ी_of_match[] = अणु
	अणु .compatible = "marvell,cp110-clock", पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_driver cp110_घड़ी_driver = अणु
	.probe = cp110_clk_probe,
	.driver		= अणु
		.name	= "marvell-cp110-clock",
		.of_match_table = cp110_घड़ी_of_match,
		.suppress_bind_attrs = true,
	पूर्ण,
पूर्ण;
builtin_platक्रमm_driver(cp110_घड़ी_driver);
