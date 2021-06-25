<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * pci-j721e - PCIe controller driver क्रम TI's J721E SoCs
 *
 * Copyright (C) 2020 Texas Instruments Incorporated - http://www.ti.com
 * Author: Kishon Vijay Abraham I <kishon@ti.com>
 */

#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/पन.स>
#समावेश <linux/irqchip/chained_irq.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/pci.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/regmap.h>

#समावेश "../../pci.h"
#समावेश "pcie-cadence.h"

#घोषणा ENABLE_REG_SYS_2	0x108
#घोषणा STATUS_REG_SYS_2	0x508
#घोषणा STATUS_CLR_REG_SYS_2	0x708
#घोषणा LINK_DOWN		BIT(1)

#घोषणा J721E_PCIE_USER_CMD_STATUS	0x4
#घोषणा LINK_TRAINING_ENABLE		BIT(0)

#घोषणा J721E_PCIE_USER_LINKSTATUS	0x14
#घोषणा LINK_STATUS			GENMASK(1, 0)

क्रमागत link_status अणु
	NO_RECEIVERS_DETECTED,
	LINK_TRAINING_IN_PROGRESS,
	LINK_UP_DL_IN_PROGRESS,
	LINK_UP_DL_COMPLETED,
पूर्ण;

#घोषणा J721E_MODE_RC			BIT(7)
#घोषणा LANE_COUNT_MASK			BIT(8)
#घोषणा LANE_COUNT(n)			((n) << 8)

#घोषणा GENERATION_SEL_MASK		GENMASK(1, 0)

#घोषणा MAX_LANES			2

काष्ठा j721e_pcie अणु
	काष्ठा device		*dev;
	काष्ठा clk		*refclk;
	u32			mode;
	u32			num_lanes;
	काष्ठा cdns_pcie	*cdns_pcie;
	व्योम __iomem		*user_cfg_base;
	व्योम __iomem		*पूर्णांकd_cfg_base;
पूर्ण;

क्रमागत j721e_pcie_mode अणु
	PCI_MODE_RC,
	PCI_MODE_EP,
पूर्ण;

काष्ठा j721e_pcie_data अणु
	क्रमागत j721e_pcie_mode	mode;
	bool quirk_retrain_flag;
पूर्ण;

अटल अंतरभूत u32 j721e_pcie_user_पढ़ोl(काष्ठा j721e_pcie *pcie, u32 offset)
अणु
	वापस पढ़ोl(pcie->user_cfg_base + offset);
पूर्ण

अटल अंतरभूत व्योम j721e_pcie_user_ग_लिखोl(काष्ठा j721e_pcie *pcie, u32 offset,
					  u32 value)
अणु
	ग_लिखोl(value, pcie->user_cfg_base + offset);
पूर्ण

अटल अंतरभूत u32 j721e_pcie_पूर्णांकd_पढ़ोl(काष्ठा j721e_pcie *pcie, u32 offset)
अणु
	वापस पढ़ोl(pcie->पूर्णांकd_cfg_base + offset);
पूर्ण

अटल अंतरभूत व्योम j721e_pcie_पूर्णांकd_ग_लिखोl(काष्ठा j721e_pcie *pcie, u32 offset,
					  u32 value)
अणु
	ग_लिखोl(value, pcie->पूर्णांकd_cfg_base + offset);
पूर्ण

अटल irqवापस_t j721e_pcie_link_irq_handler(पूर्णांक irq, व्योम *priv)
अणु
	काष्ठा j721e_pcie *pcie = priv;
	काष्ठा device *dev = pcie->dev;
	u32 reg;

	reg = j721e_pcie_पूर्णांकd_पढ़ोl(pcie, STATUS_REG_SYS_2);
	अगर (!(reg & LINK_DOWN))
		वापस IRQ_NONE;

	dev_err(dev, "LINK DOWN!\n");

	j721e_pcie_पूर्णांकd_ग_लिखोl(pcie, STATUS_CLR_REG_SYS_2, LINK_DOWN);
	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम j721e_pcie_config_link_irq(काष्ठा j721e_pcie *pcie)
अणु
	u32 reg;

	reg = j721e_pcie_पूर्णांकd_पढ़ोl(pcie, ENABLE_REG_SYS_2);
	reg |= LINK_DOWN;
	j721e_pcie_पूर्णांकd_ग_लिखोl(pcie, ENABLE_REG_SYS_2, reg);
पूर्ण

अटल पूर्णांक j721e_pcie_start_link(काष्ठा cdns_pcie *cdns_pcie)
अणु
	काष्ठा j721e_pcie *pcie = dev_get_drvdata(cdns_pcie->dev);
	u32 reg;

	reg = j721e_pcie_user_पढ़ोl(pcie, J721E_PCIE_USER_CMD_STATUS);
	reg |= LINK_TRAINING_ENABLE;
	j721e_pcie_user_ग_लिखोl(pcie, J721E_PCIE_USER_CMD_STATUS, reg);

	वापस 0;
पूर्ण

अटल व्योम j721e_pcie_stop_link(काष्ठा cdns_pcie *cdns_pcie)
अणु
	काष्ठा j721e_pcie *pcie = dev_get_drvdata(cdns_pcie->dev);
	u32 reg;

	reg = j721e_pcie_user_पढ़ोl(pcie, J721E_PCIE_USER_CMD_STATUS);
	reg &= ~LINK_TRAINING_ENABLE;
	j721e_pcie_user_ग_लिखोl(pcie, J721E_PCIE_USER_CMD_STATUS, reg);
पूर्ण

अटल bool j721e_pcie_link_up(काष्ठा cdns_pcie *cdns_pcie)
अणु
	काष्ठा j721e_pcie *pcie = dev_get_drvdata(cdns_pcie->dev);
	u32 reg;

	reg = j721e_pcie_user_पढ़ोl(pcie, J721E_PCIE_USER_LINKSTATUS);
	reg &= LINK_STATUS;
	अगर (reg == LINK_UP_DL_COMPLETED)
		वापस true;

	वापस false;
पूर्ण

अटल स्थिर काष्ठा cdns_pcie_ops j721e_pcie_ops = अणु
	.start_link = j721e_pcie_start_link,
	.stop_link = j721e_pcie_stop_link,
	.link_up = j721e_pcie_link_up,
पूर्ण;

अटल पूर्णांक j721e_pcie_set_mode(काष्ठा j721e_pcie *pcie, काष्ठा regmap *syscon,
			       अचिन्हित पूर्णांक offset)
अणु
	काष्ठा device *dev = pcie->dev;
	u32 mask = J721E_MODE_RC;
	u32 mode = pcie->mode;
	u32 val = 0;
	पूर्णांक ret = 0;

	अगर (mode == PCI_MODE_RC)
		val = J721E_MODE_RC;

	ret = regmap_update_bits(syscon, offset, mask, val);
	अगर (ret)
		dev_err(dev, "failed to set pcie mode\n");

	वापस ret;
पूर्ण

अटल पूर्णांक j721e_pcie_set_link_speed(काष्ठा j721e_pcie *pcie,
				     काष्ठा regmap *syscon, अचिन्हित पूर्णांक offset)
अणु
	काष्ठा device *dev = pcie->dev;
	काष्ठा device_node *np = dev->of_node;
	पूर्णांक link_speed;
	u32 val = 0;
	पूर्णांक ret;

	link_speed = of_pci_get_max_link_speed(np);
	अगर (link_speed < 2)
		link_speed = 2;

	val = link_speed - 1;
	ret = regmap_update_bits(syscon, offset, GENERATION_SEL_MASK, val);
	अगर (ret)
		dev_err(dev, "failed to set link speed\n");

	वापस ret;
पूर्ण

अटल पूर्णांक j721e_pcie_set_lane_count(काष्ठा j721e_pcie *pcie,
				     काष्ठा regmap *syscon, अचिन्हित पूर्णांक offset)
अणु
	काष्ठा device *dev = pcie->dev;
	u32 lanes = pcie->num_lanes;
	u32 val = 0;
	पूर्णांक ret;

	val = LANE_COUNT(lanes - 1);
	ret = regmap_update_bits(syscon, offset, LANE_COUNT_MASK, val);
	अगर (ret)
		dev_err(dev, "failed to set link count\n");

	वापस ret;
पूर्ण

अटल पूर्णांक j721e_pcie_ctrl_init(काष्ठा j721e_pcie *pcie)
अणु
	काष्ठा device *dev = pcie->dev;
	काष्ठा device_node *node = dev->of_node;
	काष्ठा of_phandle_args args;
	अचिन्हित पूर्णांक offset = 0;
	काष्ठा regmap *syscon;
	पूर्णांक ret;

	syscon = syscon_regmap_lookup_by_phandle(node, "ti,syscon-pcie-ctrl");
	अगर (IS_ERR(syscon)) अणु
		dev_err(dev, "Unable to get ti,syscon-pcie-ctrl regmap\n");
		वापस PTR_ERR(syscon);
	पूर्ण

	/* Do not error out to मुख्यtain old DT compatibility */
	ret = of_parse_phandle_with_fixed_args(node, "ti,syscon-pcie-ctrl", 1,
					       0, &args);
	अगर (!ret)
		offset = args.args[0];

	ret = j721e_pcie_set_mode(pcie, syscon, offset);
	अगर (ret < 0) अणु
		dev_err(dev, "Failed to set pci mode\n");
		वापस ret;
	पूर्ण

	ret = j721e_pcie_set_link_speed(pcie, syscon, offset);
	अगर (ret < 0) अणु
		dev_err(dev, "Failed to set link speed\n");
		वापस ret;
	पूर्ण

	ret = j721e_pcie_set_lane_count(pcie, syscon, offset);
	अगर (ret < 0) अणु
		dev_err(dev, "Failed to set num-lanes\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cdns_ti_pcie_config_पढ़ो(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn,
				    पूर्णांक where, पूर्णांक size, u32 *value)
अणु
	अगर (pci_is_root_bus(bus))
		वापस pci_generic_config_पढ़ो32(bus, devfn, where, size,
						 value);

	वापस pci_generic_config_पढ़ो(bus, devfn, where, size, value);
पूर्ण

अटल पूर्णांक cdns_ti_pcie_config_ग_लिखो(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn,
				     पूर्णांक where, पूर्णांक size, u32 value)
अणु
	अगर (pci_is_root_bus(bus))
		वापस pci_generic_config_ग_लिखो32(bus, devfn, where, size,
						  value);

	वापस pci_generic_config_ग_लिखो(bus, devfn, where, size, value);
पूर्ण

अटल काष्ठा pci_ops cdns_ti_pcie_host_ops = अणु
	.map_bus	= cdns_pci_map_bus,
	.पढ़ो		= cdns_ti_pcie_config_पढ़ो,
	.ग_लिखो		= cdns_ti_pcie_config_ग_लिखो,
पूर्ण;

अटल स्थिर काष्ठा j721e_pcie_data j721e_pcie_rc_data = अणु
	.mode = PCI_MODE_RC,
	.quirk_retrain_flag = true,
पूर्ण;

अटल स्थिर काष्ठा j721e_pcie_data j721e_pcie_ep_data = अणु
	.mode = PCI_MODE_EP,
पूर्ण;

अटल स्थिर काष्ठा of_device_id of_j721e_pcie_match[] = अणु
	अणु
		.compatible = "ti,j721e-pcie-host",
		.data = &j721e_pcie_rc_data,
	पूर्ण,
	अणु
		.compatible = "ti,j721e-pcie-ep",
		.data = &j721e_pcie_ep_data,
	पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल पूर्णांक j721e_pcie_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *node = dev->of_node;
	काष्ठा pci_host_bridge *bridge;
	काष्ठा j721e_pcie_data *data;
	काष्ठा cdns_pcie *cdns_pcie;
	काष्ठा j721e_pcie *pcie;
	काष्ठा cdns_pcie_rc *rc;
	काष्ठा cdns_pcie_ep *ep;
	काष्ठा gpio_desc *gpiod;
	व्योम __iomem *base;
	काष्ठा clk *clk;
	u32 num_lanes;
	u32 mode;
	पूर्णांक ret;
	पूर्णांक irq;

	data = (काष्ठा j721e_pcie_data *)of_device_get_match_data(dev);
	अगर (!data)
		वापस -EINVAL;

	mode = (u32)data->mode;

	pcie = devm_kzalloc(dev, माप(*pcie), GFP_KERNEL);
	अगर (!pcie)
		वापस -ENOMEM;

	pcie->dev = dev;
	pcie->mode = mode;

	base = devm_platक्रमm_ioremap_resource_byname(pdev, "intd_cfg");
	अगर (IS_ERR(base))
		वापस PTR_ERR(base);
	pcie->पूर्णांकd_cfg_base = base;

	base = devm_platक्रमm_ioremap_resource_byname(pdev, "user_cfg");
	अगर (IS_ERR(base))
		वापस PTR_ERR(base);
	pcie->user_cfg_base = base;

	ret = of_property_पढ़ो_u32(node, "num-lanes", &num_lanes);
	अगर (ret || num_lanes > MAX_LANES)
		num_lanes = 1;
	pcie->num_lanes = num_lanes;

	अगर (dma_set_mask_and_coherent(dev, DMA_BIT_MASK(48)))
		वापस -EINVAL;

	irq = platक्रमm_get_irq_byname(pdev, "link_state");
	अगर (irq < 0)
		वापस irq;

	dev_set_drvdata(dev, pcie);
	pm_runसमय_enable(dev);
	ret = pm_runसमय_get_sync(dev);
	अगर (ret < 0) अणु
		dev_err(dev, "pm_runtime_get_sync failed\n");
		जाओ err_get_sync;
	पूर्ण

	ret = j721e_pcie_ctrl_init(pcie);
	अगर (ret < 0) अणु
		dev_err(dev, "pm_runtime_get_sync failed\n");
		जाओ err_get_sync;
	पूर्ण

	ret = devm_request_irq(dev, irq, j721e_pcie_link_irq_handler, 0,
			       "j721e-pcie-link-down-irq", pcie);
	अगर (ret < 0) अणु
		dev_err(dev, "failed to request link state IRQ %d\n", irq);
		जाओ err_get_sync;
	पूर्ण

	j721e_pcie_config_link_irq(pcie);

	चयन (mode) अणु
	हाल PCI_MODE_RC:
		अगर (!IS_ENABLED(CONFIG_PCIE_CADENCE_HOST)) अणु
			ret = -ENODEV;
			जाओ err_get_sync;
		पूर्ण

		bridge = devm_pci_alloc_host_bridge(dev, माप(*rc));
		अगर (!bridge) अणु
			ret = -ENOMEM;
			जाओ err_get_sync;
		पूर्ण

		bridge->ops = &cdns_ti_pcie_host_ops;
		rc = pci_host_bridge_priv(bridge);
		rc->quirk_retrain_flag = data->quirk_retrain_flag;

		cdns_pcie = &rc->pcie;
		cdns_pcie->dev = dev;
		cdns_pcie->ops = &j721e_pcie_ops;
		pcie->cdns_pcie = cdns_pcie;

		gpiod = devm_gpiod_get_optional(dev, "reset", GPIOD_OUT_LOW);
		अगर (IS_ERR(gpiod)) अणु
			ret = PTR_ERR(gpiod);
			अगर (ret != -EPROBE_DEFER)
				dev_err(dev, "Failed to get reset GPIO\n");
			जाओ err_get_sync;
		पूर्ण

		ret = cdns_pcie_init_phy(dev, cdns_pcie);
		अगर (ret) अणु
			dev_err(dev, "Failed to init phy\n");
			जाओ err_get_sync;
		पूर्ण

		clk = devm_clk_get_optional(dev, "pcie_refclk");
		अगर (IS_ERR(clk)) अणु
			ret = PTR_ERR(clk);
			dev_err(dev, "failed to get pcie_refclk\n");
			जाओ err_pcie_setup;
		पूर्ण

		ret = clk_prepare_enable(clk);
		अगर (ret) अणु
			dev_err(dev, "failed to enable pcie_refclk\n");
			जाओ err_get_sync;
		पूर्ण
		pcie->refclk = clk;

		/*
		 * "Power Sequencing and Reset Signal Timings" table in
		 * PCI EXPRESS CARD ELECTROMECHANICAL SPECIFICATION, REV. 3.0
		 * indicates PERST# should be deनिश्चितed after minimum of 100us
		 * once REFCLK is stable. The REFCLK to the connector in RC
		 * mode is selected जबतक enabling the PHY. So deनिश्चित PERST#
		 * after 100 us.
		 */
		अगर (gpiod) अणु
			usleep_range(100, 200);
			gpiod_set_value_cansleep(gpiod, 1);
		पूर्ण

		ret = cdns_pcie_host_setup(rc);
		अगर (ret < 0) अणु
			clk_disable_unprepare(pcie->refclk);
			जाओ err_pcie_setup;
		पूर्ण

		अवरोध;
	हाल PCI_MODE_EP:
		अगर (!IS_ENABLED(CONFIG_PCIE_CADENCE_EP)) अणु
			ret = -ENODEV;
			जाओ err_get_sync;
		पूर्ण

		ep = devm_kzalloc(dev, माप(*ep), GFP_KERNEL);
		अगर (!ep) अणु
			ret = -ENOMEM;
			जाओ err_get_sync;
		पूर्ण

		cdns_pcie = &ep->pcie;
		cdns_pcie->dev = dev;
		cdns_pcie->ops = &j721e_pcie_ops;
		pcie->cdns_pcie = cdns_pcie;

		ret = cdns_pcie_init_phy(dev, cdns_pcie);
		अगर (ret) अणु
			dev_err(dev, "Failed to init phy\n");
			जाओ err_get_sync;
		पूर्ण

		ret = cdns_pcie_ep_setup(ep);
		अगर (ret < 0)
			जाओ err_pcie_setup;

		अवरोध;
	शेष:
		dev_err(dev, "INVALID device type %d\n", mode);
	पूर्ण

	वापस 0;

err_pcie_setup:
	cdns_pcie_disable_phy(cdns_pcie);

err_get_sync:
	pm_runसमय_put(dev);
	pm_runसमय_disable(dev);

	वापस ret;
पूर्ण

अटल पूर्णांक j721e_pcie_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा j721e_pcie *pcie = platक्रमm_get_drvdata(pdev);
	काष्ठा cdns_pcie *cdns_pcie = pcie->cdns_pcie;
	काष्ठा device *dev = &pdev->dev;

	clk_disable_unprepare(pcie->refclk);
	cdns_pcie_disable_phy(cdns_pcie);
	pm_runसमय_put(dev);
	pm_runसमय_disable(dev);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver j721e_pcie_driver = अणु
	.probe  = j721e_pcie_probe,
	.हटाओ = j721e_pcie_हटाओ,
	.driver = अणु
		.name	= "j721e-pcie",
		.of_match_table = of_j721e_pcie_match,
		.suppress_bind_attrs = true,
	पूर्ण,
पूर्ण;
builtin_platक्रमm_driver(j721e_pcie_driver);
