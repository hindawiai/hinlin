<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Renesas R-Car Gen3 PCIe PHY driver
 *
 * Copyright (C) 2018 Cogent Embedded, Inc.
 */

#समावेश <linux/clk.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/phy/phy.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/spinlock.h>

#घोषणा PHY_CTRL		0x4000		/* R8A77980 only */

/* PHY control रेजिस्टर (PHY_CTRL) */
#घोषणा PHY_CTRL_PHY_PWDN	BIT(2)

काष्ठा rcar_gen3_phy अणु
	काष्ठा phy *phy;
	spinlock_t lock;
	व्योम __iomem *base;
पूर्ण;

अटल व्योम rcar_gen3_phy_pcie_modअगरy_reg(काष्ठा phy *p, अचिन्हित पूर्णांक reg,
					  u32 clear, u32 set)
अणु
	काष्ठा rcar_gen3_phy *phy = phy_get_drvdata(p);
	व्योम __iomem *base = phy->base;
	अचिन्हित दीर्घ flags;
	u32 value;

	spin_lock_irqsave(&phy->lock, flags);

	value = पढ़ोl(base + reg);
	value &= ~clear;
	value |= set;
	ग_लिखोl(value, base + reg);

	spin_unlock_irqrestore(&phy->lock, flags);
पूर्ण

अटल पूर्णांक r8a77980_phy_pcie_घातer_on(काष्ठा phy *p)
अणु
	/* Power on the PCIe PHY */
	rcar_gen3_phy_pcie_modअगरy_reg(p, PHY_CTRL, PHY_CTRL_PHY_PWDN, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक r8a77980_phy_pcie_घातer_off(काष्ठा phy *p)
अणु
	/* Power off the PCIe PHY */
	rcar_gen3_phy_pcie_modअगरy_reg(p, PHY_CTRL, 0, PHY_CTRL_PHY_PWDN);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा phy_ops r8a77980_phy_pcie_ops = अणु
	.घातer_on	= r8a77980_phy_pcie_घातer_on,
	.घातer_off	= r8a77980_phy_pcie_घातer_off,
	.owner		= THIS_MODULE,
पूर्ण;

अटल स्थिर काष्ठा of_device_id rcar_gen3_phy_pcie_match_table[] = अणु
	अणु .compatible = "renesas,r8a77980-pcie-phy" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, rcar_gen3_phy_pcie_match_table);

अटल पूर्णांक rcar_gen3_phy_pcie_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा phy_provider *provider;
	काष्ठा rcar_gen3_phy *phy;
	व्योम __iomem *base;
	पूर्णांक error;

	अगर (!dev->of_node) अणु
		dev_err(dev,
			"This driver must only be instantiated from the device tree\n");
		वापस -EINVAL;
	पूर्ण

	base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(base))
		वापस PTR_ERR(base);

	phy = devm_kzalloc(dev, माप(*phy), GFP_KERNEL);
	अगर (!phy)
		वापस -ENOMEM;

	spin_lock_init(&phy->lock);

	phy->base = base;

	/*
	 * devm_phy_create() will call pm_runसमय_enable(&phy->dev);
	 * And then, phy-core will manage runसमय PM क्रम this device.
	 */
	pm_runसमय_enable(dev);

	phy->phy = devm_phy_create(dev, शून्य, &r8a77980_phy_pcie_ops);
	अगर (IS_ERR(phy->phy)) अणु
		dev_err(dev, "Failed to create PCIe PHY\n");
		error = PTR_ERR(phy->phy);
		जाओ error;
	पूर्ण
	phy_set_drvdata(phy->phy, phy);

	provider = devm_of_phy_provider_रेजिस्टर(dev, of_phy_simple_xlate);
	अगर (IS_ERR(provider)) अणु
		dev_err(dev, "Failed to register PHY provider\n");
		error = PTR_ERR(provider);
		जाओ error;
	पूर्ण

	वापस 0;

error:
	pm_runसमय_disable(dev);

	वापस error;
पूर्ण

अटल पूर्णांक rcar_gen3_phy_pcie_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	pm_runसमय_disable(&pdev->dev);

	वापस 0;
पूर्ण;

अटल काष्ठा platक्रमm_driver rcar_gen3_phy_driver = अणु
	.driver = अणु
		.name		= "phy_rcar_gen3_pcie",
		.of_match_table	= rcar_gen3_phy_pcie_match_table,
	पूर्ण,
	.probe	= rcar_gen3_phy_pcie_probe,
	.हटाओ = rcar_gen3_phy_pcie_हटाओ,
पूर्ण;

module_platक्रमm_driver(rcar_gen3_phy_driver);

MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("Renesas R-Car Gen3 PCIe PHY");
MODULE_AUTHOR("Sergei Shtylyov <sergei.shtylyov@cogentembedded.com>");
