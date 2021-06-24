<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Rockchip AXI PCIe host controller driver
 *
 * Copyright (c) 2016 Rockchip, Inc.
 *
 * Author: Shawn Lin <shawn.lin@rock-chips.com>
 *         Wenrui Li <wenrui.li@rock-chips.com>
 *
 * Bits taken from Synopsys DesignWare Host controller driver and
 * ARM PCI Host generic driver.
 */

#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/of_pci.h>
#समावेश <linux/phy/phy.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/reset.h>

#समावेश "../pci.h"
#समावेश "pcie-rockchip.h"

पूर्णांक rockchip_pcie_parse_dt(काष्ठा rockchip_pcie *rockchip)
अणु
	काष्ठा device *dev = rockchip->dev;
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	काष्ठा device_node *node = dev->of_node;
	काष्ठा resource *regs;
	पूर्णांक err;

	अगर (rockchip->is_rc) अणु
		regs = platक्रमm_get_resource_byname(pdev,
						    IORESOURCE_MEM,
						    "axi-base");
		rockchip->reg_base = devm_pci_remap_cfg_resource(dev, regs);
		अगर (IS_ERR(rockchip->reg_base))
			वापस PTR_ERR(rockchip->reg_base);
	पूर्ण अन्यथा अणु
		rockchip->mem_res =
			platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM,
						     "mem-base");
		अगर (!rockchip->mem_res)
			वापस -EINVAL;
	पूर्ण

	rockchip->apb_base =
		devm_platक्रमm_ioremap_resource_byname(pdev, "apb-base");
	अगर (IS_ERR(rockchip->apb_base))
		वापस PTR_ERR(rockchip->apb_base);

	err = rockchip_pcie_get_phys(rockchip);
	अगर (err)
		वापस err;

	rockchip->lanes = 1;
	err = of_property_पढ़ो_u32(node, "num-lanes", &rockchip->lanes);
	अगर (!err && (rockchip->lanes == 0 ||
		     rockchip->lanes == 3 ||
		     rockchip->lanes > 4)) अणु
		dev_warn(dev, "invalid num-lanes, default to use one lane\n");
		rockchip->lanes = 1;
	पूर्ण

	rockchip->link_gen = of_pci_get_max_link_speed(node);
	अगर (rockchip->link_gen < 0 || rockchip->link_gen > 2)
		rockchip->link_gen = 2;

	rockchip->core_rst = devm_reset_control_get_exclusive(dev, "core");
	अगर (IS_ERR(rockchip->core_rst)) अणु
		अगर (PTR_ERR(rockchip->core_rst) != -EPROBE_DEFER)
			dev_err(dev, "missing core reset property in node\n");
		वापस PTR_ERR(rockchip->core_rst);
	पूर्ण

	rockchip->mgmt_rst = devm_reset_control_get_exclusive(dev, "mgmt");
	अगर (IS_ERR(rockchip->mgmt_rst)) अणु
		अगर (PTR_ERR(rockchip->mgmt_rst) != -EPROBE_DEFER)
			dev_err(dev, "missing mgmt reset property in node\n");
		वापस PTR_ERR(rockchip->mgmt_rst);
	पूर्ण

	rockchip->mgmt_sticky_rst = devm_reset_control_get_exclusive(dev,
								"mgmt-sticky");
	अगर (IS_ERR(rockchip->mgmt_sticky_rst)) अणु
		अगर (PTR_ERR(rockchip->mgmt_sticky_rst) != -EPROBE_DEFER)
			dev_err(dev, "missing mgmt-sticky reset property in node\n");
		वापस PTR_ERR(rockchip->mgmt_sticky_rst);
	पूर्ण

	rockchip->pipe_rst = devm_reset_control_get_exclusive(dev, "pipe");
	अगर (IS_ERR(rockchip->pipe_rst)) अणु
		अगर (PTR_ERR(rockchip->pipe_rst) != -EPROBE_DEFER)
			dev_err(dev, "missing pipe reset property in node\n");
		वापस PTR_ERR(rockchip->pipe_rst);
	पूर्ण

	rockchip->pm_rst = devm_reset_control_get_exclusive(dev, "pm");
	अगर (IS_ERR(rockchip->pm_rst)) अणु
		अगर (PTR_ERR(rockchip->pm_rst) != -EPROBE_DEFER)
			dev_err(dev, "missing pm reset property in node\n");
		वापस PTR_ERR(rockchip->pm_rst);
	पूर्ण

	rockchip->pclk_rst = devm_reset_control_get_exclusive(dev, "pclk");
	अगर (IS_ERR(rockchip->pclk_rst)) अणु
		अगर (PTR_ERR(rockchip->pclk_rst) != -EPROBE_DEFER)
			dev_err(dev, "missing pclk reset property in node\n");
		वापस PTR_ERR(rockchip->pclk_rst);
	पूर्ण

	rockchip->aclk_rst = devm_reset_control_get_exclusive(dev, "aclk");
	अगर (IS_ERR(rockchip->aclk_rst)) अणु
		अगर (PTR_ERR(rockchip->aclk_rst) != -EPROBE_DEFER)
			dev_err(dev, "missing aclk reset property in node\n");
		वापस PTR_ERR(rockchip->aclk_rst);
	पूर्ण

	अगर (rockchip->is_rc) अणु
		rockchip->ep_gpio = devm_gpiod_get_optional(dev, "ep",
							    GPIOD_OUT_HIGH);
		अगर (IS_ERR(rockchip->ep_gpio))
			वापस dev_err_probe(dev, PTR_ERR(rockchip->ep_gpio),
					     "failed to get ep GPIO\n");
	पूर्ण

	rockchip->aclk_pcie = devm_clk_get(dev, "aclk");
	अगर (IS_ERR(rockchip->aclk_pcie)) अणु
		dev_err(dev, "aclk clock not found\n");
		वापस PTR_ERR(rockchip->aclk_pcie);
	पूर्ण

	rockchip->aclk_perf_pcie = devm_clk_get(dev, "aclk-perf");
	अगर (IS_ERR(rockchip->aclk_perf_pcie)) अणु
		dev_err(dev, "aclk_perf clock not found\n");
		वापस PTR_ERR(rockchip->aclk_perf_pcie);
	पूर्ण

	rockchip->hclk_pcie = devm_clk_get(dev, "hclk");
	अगर (IS_ERR(rockchip->hclk_pcie)) अणु
		dev_err(dev, "hclk clock not found\n");
		वापस PTR_ERR(rockchip->hclk_pcie);
	पूर्ण

	rockchip->clk_pcie_pm = devm_clk_get(dev, "pm");
	अगर (IS_ERR(rockchip->clk_pcie_pm)) अणु
		dev_err(dev, "pm clock not found\n");
		वापस PTR_ERR(rockchip->clk_pcie_pm);
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(rockchip_pcie_parse_dt);

पूर्णांक rockchip_pcie_init_port(काष्ठा rockchip_pcie *rockchip)
अणु
	काष्ठा device *dev = rockchip->dev;
	पूर्णांक err, i;
	u32 regs;

	err = reset_control_निश्चित(rockchip->aclk_rst);
	अगर (err) अणु
		dev_err(dev, "assert aclk_rst err %d\n", err);
		वापस err;
	पूर्ण

	err = reset_control_निश्चित(rockchip->pclk_rst);
	अगर (err) अणु
		dev_err(dev, "assert pclk_rst err %d\n", err);
		वापस err;
	पूर्ण

	err = reset_control_निश्चित(rockchip->pm_rst);
	अगर (err) अणु
		dev_err(dev, "assert pm_rst err %d\n", err);
		वापस err;
	पूर्ण

	क्रम (i = 0; i < MAX_LANE_NUM; i++) अणु
		err = phy_init(rockchip->phys[i]);
		अगर (err) अणु
			dev_err(dev, "init phy%d err %d\n", i, err);
			जाओ err_निकास_phy;
		पूर्ण
	पूर्ण

	err = reset_control_निश्चित(rockchip->core_rst);
	अगर (err) अणु
		dev_err(dev, "assert core_rst err %d\n", err);
		जाओ err_निकास_phy;
	पूर्ण

	err = reset_control_निश्चित(rockchip->mgmt_rst);
	अगर (err) अणु
		dev_err(dev, "assert mgmt_rst err %d\n", err);
		जाओ err_निकास_phy;
	पूर्ण

	err = reset_control_निश्चित(rockchip->mgmt_sticky_rst);
	अगर (err) अणु
		dev_err(dev, "assert mgmt_sticky_rst err %d\n", err);
		जाओ err_निकास_phy;
	पूर्ण

	err = reset_control_निश्चित(rockchip->pipe_rst);
	अगर (err) अणु
		dev_err(dev, "assert pipe_rst err %d\n", err);
		जाओ err_निकास_phy;
	पूर्ण

	udelay(10);

	err = reset_control_deनिश्चित(rockchip->pm_rst);
	अगर (err) अणु
		dev_err(dev, "deassert pm_rst err %d\n", err);
		जाओ err_निकास_phy;
	पूर्ण

	err = reset_control_deनिश्चित(rockchip->aclk_rst);
	अगर (err) अणु
		dev_err(dev, "deassert aclk_rst err %d\n", err);
		जाओ err_निकास_phy;
	पूर्ण

	err = reset_control_deनिश्चित(rockchip->pclk_rst);
	अगर (err) अणु
		dev_err(dev, "deassert pclk_rst err %d\n", err);
		जाओ err_निकास_phy;
	पूर्ण

	अगर (rockchip->link_gen == 2)
		rockchip_pcie_ग_लिखो(rockchip, PCIE_CLIENT_GEN_SEL_2,
				    PCIE_CLIENT_CONFIG);
	अन्यथा
		rockchip_pcie_ग_लिखो(rockchip, PCIE_CLIENT_GEN_SEL_1,
				    PCIE_CLIENT_CONFIG);

	regs = PCIE_CLIENT_LINK_TRAIN_ENABLE | PCIE_CLIENT_ARI_ENABLE |
	       PCIE_CLIENT_CONF_LANE_NUM(rockchip->lanes);

	अगर (rockchip->is_rc)
		regs |= PCIE_CLIENT_CONF_ENABLE | PCIE_CLIENT_MODE_RC;
	अन्यथा
		regs |= PCIE_CLIENT_CONF_DISABLE | PCIE_CLIENT_MODE_EP;

	rockchip_pcie_ग_लिखो(rockchip, regs, PCIE_CLIENT_CONFIG);

	क्रम (i = 0; i < MAX_LANE_NUM; i++) अणु
		err = phy_घातer_on(rockchip->phys[i]);
		अगर (err) अणु
			dev_err(dev, "power on phy%d err %d\n", i, err);
			जाओ err_घातer_off_phy;
		पूर्ण
	पूर्ण

	/*
	 * Please करोn't reorder the deनिश्चित sequence of the following
	 * four reset pins.
	 */
	err = reset_control_deनिश्चित(rockchip->mgmt_sticky_rst);
	अगर (err) अणु
		dev_err(dev, "deassert mgmt_sticky_rst err %d\n", err);
		जाओ err_घातer_off_phy;
	पूर्ण

	err = reset_control_deनिश्चित(rockchip->core_rst);
	अगर (err) अणु
		dev_err(dev, "deassert core_rst err %d\n", err);
		जाओ err_घातer_off_phy;
	पूर्ण

	err = reset_control_deनिश्चित(rockchip->mgmt_rst);
	अगर (err) अणु
		dev_err(dev, "deassert mgmt_rst err %d\n", err);
		जाओ err_घातer_off_phy;
	पूर्ण

	err = reset_control_deनिश्चित(rockchip->pipe_rst);
	अगर (err) अणु
		dev_err(dev, "deassert pipe_rst err %d\n", err);
		जाओ err_घातer_off_phy;
	पूर्ण

	वापस 0;
err_घातer_off_phy:
	जबतक (i--)
		phy_घातer_off(rockchip->phys[i]);
	i = MAX_LANE_NUM;
err_निकास_phy:
	जबतक (i--)
		phy_निकास(rockchip->phys[i]);
	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(rockchip_pcie_init_port);

पूर्णांक rockchip_pcie_get_phys(काष्ठा rockchip_pcie *rockchip)
अणु
	काष्ठा device *dev = rockchip->dev;
	काष्ठा phy *phy;
	अक्षर *name;
	u32 i;

	phy = devm_phy_get(dev, "pcie-phy");
	अगर (!IS_ERR(phy)) अणु
		rockchip->legacy_phy = true;
		rockchip->phys[0] = phy;
		dev_warn(dev, "legacy phy model is deprecated!\n");
		वापस 0;
	पूर्ण

	अगर (PTR_ERR(phy) == -EPROBE_DEFER)
		वापस PTR_ERR(phy);

	dev_dbg(dev, "missing legacy phy; search for per-lane PHY\n");

	क्रम (i = 0; i < MAX_LANE_NUM; i++) अणु
		name = kaप्र_लिखो(GFP_KERNEL, "pcie-phy-%u", i);
		अगर (!name)
			वापस -ENOMEM;

		phy = devm_of_phy_get(dev, dev->of_node, name);
		kमुक्त(name);

		अगर (IS_ERR(phy)) अणु
			अगर (PTR_ERR(phy) != -EPROBE_DEFER)
				dev_err(dev, "missing phy for lane %d: %ld\n",
					i, PTR_ERR(phy));
			वापस PTR_ERR(phy);
		पूर्ण

		rockchip->phys[i] = phy;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(rockchip_pcie_get_phys);

व्योम rockchip_pcie_deinit_phys(काष्ठा rockchip_pcie *rockchip)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < MAX_LANE_NUM; i++) अणु
		/* inactive lanes are alपढ़ोy घातered off */
		अगर (rockchip->lanes_map & BIT(i))
			phy_घातer_off(rockchip->phys[i]);
		phy_निकास(rockchip->phys[i]);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(rockchip_pcie_deinit_phys);

पूर्णांक rockchip_pcie_enable_घड़ीs(काष्ठा rockchip_pcie *rockchip)
अणु
	काष्ठा device *dev = rockchip->dev;
	पूर्णांक err;

	err = clk_prepare_enable(rockchip->aclk_pcie);
	अगर (err) अणु
		dev_err(dev, "unable to enable aclk_pcie clock\n");
		वापस err;
	पूर्ण

	err = clk_prepare_enable(rockchip->aclk_perf_pcie);
	अगर (err) अणु
		dev_err(dev, "unable to enable aclk_perf_pcie clock\n");
		जाओ err_aclk_perf_pcie;
	पूर्ण

	err = clk_prepare_enable(rockchip->hclk_pcie);
	अगर (err) अणु
		dev_err(dev, "unable to enable hclk_pcie clock\n");
		जाओ err_hclk_pcie;
	पूर्ण

	err = clk_prepare_enable(rockchip->clk_pcie_pm);
	अगर (err) अणु
		dev_err(dev, "unable to enable clk_pcie_pm clock\n");
		जाओ err_clk_pcie_pm;
	पूर्ण

	वापस 0;

err_clk_pcie_pm:
	clk_disable_unprepare(rockchip->hclk_pcie);
err_hclk_pcie:
	clk_disable_unprepare(rockchip->aclk_perf_pcie);
err_aclk_perf_pcie:
	clk_disable_unprepare(rockchip->aclk_pcie);
	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(rockchip_pcie_enable_घड़ीs);

व्योम rockchip_pcie_disable_घड़ीs(व्योम *data)
अणु
	काष्ठा rockchip_pcie *rockchip = data;

	clk_disable_unprepare(rockchip->clk_pcie_pm);
	clk_disable_unprepare(rockchip->hclk_pcie);
	clk_disable_unprepare(rockchip->aclk_perf_pcie);
	clk_disable_unprepare(rockchip->aclk_pcie);
पूर्ण
EXPORT_SYMBOL_GPL(rockchip_pcie_disable_घड़ीs);

व्योम rockchip_pcie_cfg_configuration_accesses(
		काष्ठा rockchip_pcie *rockchip, u32 type)
अणु
	u32 ob_desc_0;

	/* Configuration Accesses क्रम region 0 */
	rockchip_pcie_ग_लिखो(rockchip, 0x0, PCIE_RC_BAR_CONF);

	rockchip_pcie_ग_लिखो(rockchip,
			    (RC_REGION_0_ADDR_TRANS_L + RC_REGION_0_PASS_BITS),
			    PCIE_CORE_OB_REGION_ADDR0);
	rockchip_pcie_ग_लिखो(rockchip, RC_REGION_0_ADDR_TRANS_H,
			    PCIE_CORE_OB_REGION_ADDR1);
	ob_desc_0 = rockchip_pcie_पढ़ो(rockchip, PCIE_CORE_OB_REGION_DESC0);
	ob_desc_0 &= ~(RC_REGION_0_TYPE_MASK);
	ob_desc_0 |= (type | (0x1 << 23));
	rockchip_pcie_ग_लिखो(rockchip, ob_desc_0, PCIE_CORE_OB_REGION_DESC0);
	rockchip_pcie_ग_लिखो(rockchip, 0x0, PCIE_CORE_OB_REGION_DESC1);
पूर्ण
EXPORT_SYMBOL_GPL(rockchip_pcie_cfg_configuration_accesses);
