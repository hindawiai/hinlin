<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * USB cluster support क्रम Armada 375 platक्रमm.
 *
 * Copyright (C) 2014 Marvell
 *
 * Gregory CLEMENT <gregory.clement@मुक्त-electrons.com>
 *
 * Armada 375 comes with an USB2 host and device controller and an
 * USB3 controller. The USB cluster control रेजिस्टर allows to manage
 * common features of both USB controllers.
 */

#समावेश <dt-bindings/phy/phy.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/of_address.h>
#समावेश <linux/phy/phy.h>
#समावेश <linux/platक्रमm_device.h>

#घोषणा USB2_PHY_CONFIG_DISABLE BIT(0)

काष्ठा armada375_cluster_phy अणु
	काष्ठा phy *phy;
	व्योम __iomem *reg;
	bool use_usb3;
	पूर्णांक phy_provided;
पूर्ण;

अटल पूर्णांक armada375_usb_phy_init(काष्ठा phy *phy)
अणु
	काष्ठा armada375_cluster_phy *cluster_phy;
	u32 reg;

	cluster_phy = phy_get_drvdata(phy);
	अगर (!cluster_phy)
		वापस -ENODEV;

	reg = पढ़ोl(cluster_phy->reg);
	अगर (cluster_phy->use_usb3)
		reg |= USB2_PHY_CONFIG_DISABLE;
	अन्यथा
		reg &= ~USB2_PHY_CONFIG_DISABLE;
	ग_लिखोl(reg, cluster_phy->reg);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा phy_ops armada375_usb_phy_ops = अणु
	.init = armada375_usb_phy_init,
	.owner = THIS_MODULE,
पूर्ण;

/*
 * Only one controller can use this PHY. We shouldn't have the हाल
 * when two controllers want to use this PHY. But अगर this हाल occurs
 * then we provide a phy to the first one and वापस an error क्रम the
 * next one. This error has also to be an error वापसed by
 * devm_phy_optional_get() so dअगरferent from ENODEV क्रम USB2. In the
 * USB3 हाल it still optional and we use ENODEV.
 */
अटल काष्ठा phy *armada375_usb_phy_xlate(काष्ठा device *dev,
					काष्ठा of_phandle_args *args)
अणु
	काष्ठा armada375_cluster_phy *cluster_phy = dev_get_drvdata(dev);

	अगर (!cluster_phy)
		वापस  ERR_PTR(-ENODEV);

	/*
	 * Either the phy had never been requested and then the first
	 * usb claiming it can get it, or it had alपढ़ोy been
	 * requested in this हाल, we only allow to use it with the
	 * same configuration.
	 */
	अगर (WARN_ON((cluster_phy->phy_provided != PHY_NONE) &&
			(cluster_phy->phy_provided != args->args[0]))) अणु
		dev_err(dev, "This PHY has already been provided!\n");
		dev_err(dev, "Check your device tree, only one controller can use it\n.");
		अगर (args->args[0] == PHY_TYPE_USB2)
			वापस ERR_PTR(-EBUSY);
		अन्यथा
			वापस ERR_PTR(-ENODEV);
	पूर्ण

	अगर (args->args[0] == PHY_TYPE_USB2)
		cluster_phy->use_usb3 = false;
	अन्यथा अगर (args->args[0] == PHY_TYPE_USB3)
		cluster_phy->use_usb3 = true;
	अन्यथा अणु
		dev_err(dev, "Invalid PHY mode\n");
		वापस ERR_PTR(-ENODEV);
	पूर्ण

	/* Store which phy mode is used क्रम next test */
	cluster_phy->phy_provided = args->args[0];

	वापस cluster_phy->phy;
पूर्ण

अटल पूर्णांक armada375_usb_phy_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा phy *phy;
	काष्ठा phy_provider *phy_provider;
	व्योम __iomem *usb_cluster_base;
	काष्ठा armada375_cluster_phy *cluster_phy;

	cluster_phy = devm_kzalloc(dev, माप(*cluster_phy), GFP_KERNEL);
	अगर (!cluster_phy)
		वापस  -ENOMEM;

	usb_cluster_base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(usb_cluster_base))
		वापस PTR_ERR(usb_cluster_base);

	phy = devm_phy_create(dev, शून्य, &armada375_usb_phy_ops);
	अगर (IS_ERR(phy)) अणु
		dev_err(dev, "failed to create PHY\n");
		वापस PTR_ERR(phy);
	पूर्ण

	cluster_phy->phy = phy;
	cluster_phy->reg = usb_cluster_base;

	dev_set_drvdata(dev, cluster_phy);
	phy_set_drvdata(phy, cluster_phy);

	phy_provider = devm_of_phy_provider_रेजिस्टर(&pdev->dev,
						     armada375_usb_phy_xlate);
	वापस PTR_ERR_OR_ZERO(phy_provider);
पूर्ण

अटल स्थिर काष्ठा of_device_id of_usb_cluster_table[] = अणु
	अणु .compatible = "marvell,armada-375-usb-cluster", पूर्ण,
	अणु /* end of list */ पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver armada375_usb_phy_driver = अणु
	.probe	= armada375_usb_phy_probe,
	.driver = अणु
		.of_match_table	= of_usb_cluster_table,
		.name  = "armada-375-usb-cluster",
	पूर्ण
पूर्ण;
builtin_platक्रमm_driver(armada375_usb_phy_driver);
