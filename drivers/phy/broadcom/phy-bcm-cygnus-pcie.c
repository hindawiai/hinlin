<शैली गुरु>
/*
 * Copyright (C) 2015 Broadcom Corporation
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License as
 * published by the Free Software Foundation version 2.
 *
 * This program is distributed "as is" WITHOUT ANY WARRANTY of any
 * kind, whether express or implied; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 */

#समावेश <linux/delay.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/phy/phy.h>
#समावेश <linux/platक्रमm_device.h>

#घोषणा PCIE_CFG_OFFSET         0x00
#घोषणा PCIE1_PHY_IDDQ_SHIFT    10
#घोषणा PCIE0_PHY_IDDQ_SHIFT    2

क्रमागत cygnus_pcie_phy_id अणु
	CYGNUS_PHY_PCIE0 = 0,
	CYGNUS_PHY_PCIE1,
	MAX_NUM_PHYS,
पूर्ण;

काष्ठा cygnus_pcie_phy_core;

/**
 * काष्ठा cygnus_pcie_phy - Cygnus PCIe PHY device
 * @core: poपूर्णांकer to the Cygnus PCIe PHY core control
 * @id: पूर्णांकernal ID to identअगरy the Cygnus PCIe PHY
 * @phy: poपूर्णांकer to the kernel PHY device
 */
काष्ठा cygnus_pcie_phy अणु
	काष्ठा cygnus_pcie_phy_core *core;
	क्रमागत cygnus_pcie_phy_id id;
	काष्ठा phy *phy;
पूर्ण;

/**
 * काष्ठा cygnus_pcie_phy_core - Cygnus PCIe PHY core control
 * @dev: poपूर्णांकer to device
 * @base: base रेजिस्टर
 * @lock: mutex to protect access to inभागidual PHYs
 * @phys: poपूर्णांकer to Cygnus PHY device
 */
काष्ठा cygnus_pcie_phy_core अणु
	काष्ठा device *dev;
	व्योम __iomem *base;
	काष्ठा mutex lock;
	काष्ठा cygnus_pcie_phy phys[MAX_NUM_PHYS];
पूर्ण;

अटल पूर्णांक cygnus_pcie_घातer_config(काष्ठा cygnus_pcie_phy *phy, bool enable)
अणु
	काष्ठा cygnus_pcie_phy_core *core = phy->core;
	अचिन्हित shअगरt;
	u32 val;

	mutex_lock(&core->lock);

	चयन (phy->id) अणु
	हाल CYGNUS_PHY_PCIE0:
		shअगरt = PCIE0_PHY_IDDQ_SHIFT;
		अवरोध;

	हाल CYGNUS_PHY_PCIE1:
		shअगरt = PCIE1_PHY_IDDQ_SHIFT;
		अवरोध;

	शेष:
		mutex_unlock(&core->lock);
		dev_err(core->dev, "PCIe PHY %d invalid\n", phy->id);
		वापस -EINVAL;
	पूर्ण

	अगर (enable) अणु
		val = पढ़ोl(core->base + PCIE_CFG_OFFSET);
		val &= ~BIT(shअगरt);
		ग_लिखोl(val, core->base + PCIE_CFG_OFFSET);
		/*
		 * Wait 50 ms क्रम the PCIe Serdes to stabilize after the analog
		 * front end is brought up
		 */
		msleep(50);
	पूर्ण अन्यथा अणु
		val = पढ़ोl(core->base + PCIE_CFG_OFFSET);
		val |= BIT(shअगरt);
		ग_लिखोl(val, core->base + PCIE_CFG_OFFSET);
	पूर्ण

	mutex_unlock(&core->lock);
	dev_dbg(core->dev, "PCIe PHY %d %s\n", phy->id,
		enable ? "enabled" : "disabled");
	वापस 0;
पूर्ण

अटल पूर्णांक cygnus_pcie_phy_घातer_on(काष्ठा phy *p)
अणु
	काष्ठा cygnus_pcie_phy *phy = phy_get_drvdata(p);

	वापस cygnus_pcie_घातer_config(phy, true);
पूर्ण

अटल पूर्णांक cygnus_pcie_phy_घातer_off(काष्ठा phy *p)
अणु
	काष्ठा cygnus_pcie_phy *phy = phy_get_drvdata(p);

	वापस cygnus_pcie_घातer_config(phy, false);
पूर्ण

अटल स्थिर काष्ठा phy_ops cygnus_pcie_phy_ops = अणु
	.घातer_on = cygnus_pcie_phy_घातer_on,
	.घातer_off = cygnus_pcie_phy_घातer_off,
	.owner = THIS_MODULE,
पूर्ण;

अटल पूर्णांक cygnus_pcie_phy_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *node = dev->of_node, *child;
	काष्ठा cygnus_pcie_phy_core *core;
	काष्ठा phy_provider *provider;
	अचिन्हित cnt = 0;
	पूर्णांक ret;

	अगर (of_get_child_count(node) == 0) अणु
		dev_err(dev, "PHY no child node\n");
		वापस -ENODEV;
	पूर्ण

	core = devm_kzalloc(dev, माप(*core), GFP_KERNEL);
	अगर (!core)
		वापस -ENOMEM;

	core->dev = dev;

	core->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(core->base))
		वापस PTR_ERR(core->base);

	mutex_init(&core->lock);

	क्रम_each_available_child_of_node(node, child) अणु
		अचिन्हित पूर्णांक id;
		काष्ठा cygnus_pcie_phy *p;

		अगर (of_property_पढ़ो_u32(child, "reg", &id)) अणु
			dev_err(dev, "missing reg property for %pOFn\n",
				child);
			ret = -EINVAL;
			जाओ put_child;
		पूर्ण

		अगर (id >= MAX_NUM_PHYS) अणु
			dev_err(dev, "invalid PHY id: %u\n", id);
			ret = -EINVAL;
			जाओ put_child;
		पूर्ण

		अगर (core->phys[id].phy) अणु
			dev_err(dev, "duplicated PHY id: %u\n", id);
			ret = -EINVAL;
			जाओ put_child;
		पूर्ण

		p = &core->phys[id];
		p->phy = devm_phy_create(dev, child, &cygnus_pcie_phy_ops);
		अगर (IS_ERR(p->phy)) अणु
			dev_err(dev, "failed to create PHY\n");
			ret = PTR_ERR(p->phy);
			जाओ put_child;
		पूर्ण

		p->core = core;
		p->id = id;
		phy_set_drvdata(p->phy, p);
		cnt++;
	पूर्ण

	dev_set_drvdata(dev, core);

	provider = devm_of_phy_provider_रेजिस्टर(dev, of_phy_simple_xlate);
	अगर (IS_ERR(provider)) अणु
		dev_err(dev, "failed to register PHY provider\n");
		वापस PTR_ERR(provider);
	पूर्ण

	dev_dbg(dev, "registered %u PCIe PHY(s)\n", cnt);

	वापस 0;
put_child:
	of_node_put(child);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा of_device_id cygnus_pcie_phy_match_table[] = अणु
	अणु .compatible = "brcm,cygnus-pcie-phy" पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, cygnus_pcie_phy_match_table);

अटल काष्ठा platक्रमm_driver cygnus_pcie_phy_driver = अणु
	.driver = अणु
		.name = "cygnus-pcie-phy",
		.of_match_table = cygnus_pcie_phy_match_table,
	पूर्ण,
	.probe = cygnus_pcie_phy_probe,
पूर्ण;
module_platक्रमm_driver(cygnus_pcie_phy_driver);

MODULE_AUTHOR("Ray Jui <rjui@broadcom.com>");
MODULE_DESCRIPTION("Broadcom Cygnus PCIe PHY driver");
MODULE_LICENSE("GPL v2");
