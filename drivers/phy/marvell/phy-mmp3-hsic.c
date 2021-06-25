<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright (C) 2020 Lubomir Rपूर्णांकel <lkundrak@v3.sk>
 */

#समावेश <linux/delay.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/phy/phy.h>
#समावेश <linux/platक्रमm_device.h>

#घोषणा HSIC_CTRL	0x08
#घोषणा HSIC_ENABLE	BIT(7)
#घोषणा PLL_BYPASS	BIT(4)

अटल पूर्णांक mmp3_hsic_phy_init(काष्ठा phy *phy)
अणु
	व्योम __iomem *base = (व्योम __iomem *)phy_get_drvdata(phy);
	u32 hsic_ctrl;

	hsic_ctrl = पढ़ोl_relaxed(base + HSIC_CTRL);
	hsic_ctrl |= HSIC_ENABLE;
	hsic_ctrl |= PLL_BYPASS;
	ग_लिखोl_relaxed(hsic_ctrl, base + HSIC_CTRL);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा phy_ops mmp3_hsic_phy_ops = अणु
	.init		= mmp3_hsic_phy_init,
	.owner		= THIS_MODULE,
पूर्ण;

अटल स्थिर काष्ठा of_device_id mmp3_hsic_phy_of_match[] = अणु
	अणु .compatible = "marvell,mmp3-hsic-phy", पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, mmp3_hsic_phy_of_match);

अटल पूर्णांक mmp3_hsic_phy_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा phy_provider *provider;
	काष्ठा resource *resource;
	व्योम __iomem *base;
	काष्ठा phy *phy;

	resource = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	base = devm_ioremap_resource(dev, resource);
	अगर (IS_ERR(base)) अणु
		dev_err(dev, "failed to remap PHY regs\n");
		वापस PTR_ERR(base);
	पूर्ण

	phy = devm_phy_create(dev, शून्य, &mmp3_hsic_phy_ops);
	अगर (IS_ERR(phy)) अणु
		dev_err(dev, "failed to create PHY\n");
		वापस PTR_ERR(phy);
	पूर्ण

	phy_set_drvdata(phy, (व्योम *)base);
	provider = devm_of_phy_provider_रेजिस्टर(dev, of_phy_simple_xlate);
	अगर (IS_ERR(provider)) अणु
		dev_err(dev, "failed to register PHY provider\n");
		वापस PTR_ERR(provider);
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver mmp3_hsic_phy_driver = अणु
	.probe		= mmp3_hsic_phy_probe,
	.driver		= अणु
		.name	= "mmp3-hsic-phy",
		.of_match_table = mmp3_hsic_phy_of_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(mmp3_hsic_phy_driver);

MODULE_AUTHOR("Lubomir Rintel <lkundrak@v3.sk>");
MODULE_DESCRIPTION("Marvell MMP3 USB HSIC PHY Driver");
MODULE_LICENSE("GPL");
