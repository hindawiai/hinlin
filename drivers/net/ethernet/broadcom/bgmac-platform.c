<शैली गुरु>
/*
 * Copyright (C) 2016 Broadcom
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

#घोषणा pr_fmt(fmt)		KBUILD_MODNAME ": " fmt

#समावेश <linux/bcma/bcma.h>
#समावेश <linux/brcmphy.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_mdपन.स>
#समावेश <linux/of_net.h>
#समावेश "bgmac.h"

#घोषणा NICPM_PADRING_CFG		0x00000004
#घोषणा NICPM_IOMUX_CTRL		0x00000008

#घोषणा NICPM_PADRING_CFG_INIT_VAL	0x74000000
#घोषणा NICPM_IOMUX_CTRL_INIT_VAL_AX	0x21880000

#घोषणा NICPM_IOMUX_CTRL_INIT_VAL	0x3196e000
#घोषणा NICPM_IOMUX_CTRL_SPD_SHIFT	10
#घोषणा NICPM_IOMUX_CTRL_SPD_10M	0
#घोषणा NICPM_IOMUX_CTRL_SPD_100M	1
#घोषणा NICPM_IOMUX_CTRL_SPD_1000M	2

अटल u32 platक्रमm_bgmac_पढ़ो(काष्ठा bgmac *bgmac, u16 offset)
अणु
	वापस पढ़ोl(bgmac->plat.base + offset);
पूर्ण

अटल व्योम platक्रमm_bgmac_ग_लिखो(काष्ठा bgmac *bgmac, u16 offset, u32 value)
अणु
	ग_लिखोl(value, bgmac->plat.base + offset);
पूर्ण

अटल u32 platक्रमm_bgmac_idm_पढ़ो(काष्ठा bgmac *bgmac, u16 offset)
अणु
	वापस पढ़ोl(bgmac->plat.idm_base + offset);
पूर्ण

अटल व्योम platक्रमm_bgmac_idm_ग_लिखो(काष्ठा bgmac *bgmac, u16 offset, u32 value)
अणु
	ग_लिखोl(value, bgmac->plat.idm_base + offset);
पूर्ण

अटल bool platक्रमm_bgmac_clk_enabled(काष्ठा bgmac *bgmac)
अणु
	अगर (!bgmac->plat.idm_base)
		वापस true;

	अगर ((bgmac_idm_पढ़ो(bgmac, BCMA_IOCTL) & BGMAC_CLK_EN) != BGMAC_CLK_EN)
		वापस false;
	अगर (bgmac_idm_पढ़ो(bgmac, BCMA_RESET_CTL) & BCMA_RESET_CTL_RESET)
		वापस false;
	वापस true;
पूर्ण

अटल व्योम platक्रमm_bgmac_clk_enable(काष्ठा bgmac *bgmac, u32 flags)
अणु
	u32 val;

	अगर (!bgmac->plat.idm_base)
		वापस;

	/* The Reset Control रेजिस्टर only contains a single bit to show अगर the
	 * controller is currently in reset.  Do a sanity check here, just in
	 * हाल the bootloader happened to leave the device in reset.
	 */
	val = bgmac_idm_पढ़ो(bgmac, BCMA_RESET_CTL);
	अगर (val) अणु
		bgmac_idm_ग_लिखो(bgmac, BCMA_RESET_CTL, 0);
		bgmac_idm_पढ़ो(bgmac, BCMA_RESET_CTL);
		udelay(1);
	पूर्ण

	val = bgmac_idm_पढ़ो(bgmac, BCMA_IOCTL);
	/* Some bits of BCMA_IOCTL set by HW/ATF and should not change */
	val |= flags & ~(BGMAC_AWCACHE | BGMAC_ARCACHE | BGMAC_AWUSER |
			 BGMAC_ARUSER);
	val |= BGMAC_CLK_EN;
	bgmac_idm_ग_लिखो(bgmac, BCMA_IOCTL, val);
	bgmac_idm_पढ़ो(bgmac, BCMA_IOCTL);
	udelay(1);
पूर्ण

अटल व्योम platक्रमm_bgmac_cco_ctl_maskset(काष्ठा bgmac *bgmac, u32 offset,
					   u32 mask, u32 set)
अणु
	/* This shouldn't be encountered */
	WARN_ON(1);
पूर्ण

अटल u32 platक्रमm_bgmac_get_bus_घड़ी(काष्ठा bgmac *bgmac)
अणु
	/* This shouldn't be encountered */
	WARN_ON(1);

	वापस 0;
पूर्ण

अटल व्योम platक्रमm_bgmac_cmn_maskset32(काष्ठा bgmac *bgmac, u16 offset,
					 u32 mask, u32 set)
अणु
	/* This shouldn't be encountered */
	WARN_ON(1);
पूर्ण

अटल व्योम bgmac_nicpm_speed_set(काष्ठा net_device *net_dev)
अणु
	काष्ठा bgmac *bgmac = netdev_priv(net_dev);
	u32 val;

	अगर (!bgmac->plat.nicpm_base)
		वापस;

	/* SET RGMII IO CONFIG */
	ग_लिखोl(NICPM_PADRING_CFG_INIT_VAL,
	       bgmac->plat.nicpm_base + NICPM_PADRING_CFG);

	val = NICPM_IOMUX_CTRL_INIT_VAL;
	चयन (bgmac->net_dev->phydev->speed) अणु
	शेष:
		netdev_err(net_dev, "Unsupported speed. Defaulting to 1000Mb\n");
		fallthrough;
	हाल SPEED_1000:
		val |= NICPM_IOMUX_CTRL_SPD_1000M << NICPM_IOMUX_CTRL_SPD_SHIFT;
		अवरोध;
	हाल SPEED_100:
		val |= NICPM_IOMUX_CTRL_SPD_100M << NICPM_IOMUX_CTRL_SPD_SHIFT;
		अवरोध;
	हाल SPEED_10:
		val |= NICPM_IOMUX_CTRL_SPD_10M << NICPM_IOMUX_CTRL_SPD_SHIFT;
		अवरोध;
	पूर्ण

	ग_लिखोl(val, bgmac->plat.nicpm_base + NICPM_IOMUX_CTRL);

	bgmac_adjust_link(bgmac->net_dev);
पूर्ण

अटल पूर्णांक platक्रमm_phy_connect(काष्ठा bgmac *bgmac)
अणु
	काष्ठा phy_device *phy_dev;

	अगर (bgmac->plat.nicpm_base)
		phy_dev = of_phy_get_and_connect(bgmac->net_dev,
						 bgmac->dev->of_node,
						 bgmac_nicpm_speed_set);
	अन्यथा
		phy_dev = of_phy_get_and_connect(bgmac->net_dev,
						 bgmac->dev->of_node,
						 bgmac_adjust_link);
	अगर (!phy_dev) अणु
		dev_err(bgmac->dev, "PHY connection failed\n");
		वापस -ENODEV;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक bgmac_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा bgmac *bgmac;
	काष्ठा resource *regs;
	पूर्णांक ret;

	bgmac = bgmac_alloc(&pdev->dev);
	अगर (!bgmac)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, bgmac);

	/* Set the features of the 4707 family */
	bgmac->feature_flags |= BGMAC_FEAT_CLKCTLST;
	bgmac->feature_flags |= BGMAC_FEAT_NO_RESET;
	bgmac->feature_flags |= BGMAC_FEAT_CMDCFG_SR_REV4;
	bgmac->feature_flags |= BGMAC_FEAT_TX_MASK_SETUP;
	bgmac->feature_flags |= BGMAC_FEAT_RX_MASK_SETUP;
	bgmac->feature_flags |= BGMAC_FEAT_IDM_MASK;

	bgmac->dev = &pdev->dev;
	bgmac->dma_dev = &pdev->dev;

	ret = of_get_mac_address(np, bgmac->net_dev->dev_addr);
	अगर (ret)
		dev_warn(&pdev->dev,
			 "MAC address not present in device tree\n");

	bgmac->irq = platक्रमm_get_irq(pdev, 0);
	अगर (bgmac->irq < 0)
		वापस bgmac->irq;

	bgmac->plat.base =
		devm_platक्रमm_ioremap_resource_byname(pdev, "amac_base");
	अगर (IS_ERR(bgmac->plat.base))
		वापस PTR_ERR(bgmac->plat.base);

	regs = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, "idm_base");
	अगर (regs) अणु
		bgmac->plat.idm_base = devm_ioremap_resource(&pdev->dev, regs);
		अगर (IS_ERR(bgmac->plat.idm_base))
			वापस PTR_ERR(bgmac->plat.idm_base);
		bgmac->feature_flags &= ~BGMAC_FEAT_IDM_MASK;
	पूर्ण

	regs = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, "nicpm_base");
	अगर (regs) अणु
		bgmac->plat.nicpm_base = devm_ioremap_resource(&pdev->dev,
							       regs);
		अगर (IS_ERR(bgmac->plat.nicpm_base))
			वापस PTR_ERR(bgmac->plat.nicpm_base);
	पूर्ण

	bgmac->पढ़ो = platक्रमm_bgmac_पढ़ो;
	bgmac->ग_लिखो = platक्रमm_bgmac_ग_लिखो;
	bgmac->idm_पढ़ो = platक्रमm_bgmac_idm_पढ़ो;
	bgmac->idm_ग_लिखो = platक्रमm_bgmac_idm_ग_लिखो;
	bgmac->clk_enabled = platक्रमm_bgmac_clk_enabled;
	bgmac->clk_enable = platक्रमm_bgmac_clk_enable;
	bgmac->cco_ctl_maskset = platक्रमm_bgmac_cco_ctl_maskset;
	bgmac->get_bus_घड़ी = platक्रमm_bgmac_get_bus_घड़ी;
	bgmac->cmn_maskset32 = platक्रमm_bgmac_cmn_maskset32;
	अगर (of_parse_phandle(np, "phy-handle", 0)) अणु
		bgmac->phy_connect = platक्रमm_phy_connect;
	पूर्ण अन्यथा अणु
		bgmac->phy_connect = bgmac_phy_connect_direct;
		bgmac->feature_flags |= BGMAC_FEAT_FORCE_SPEED_2500;
	पूर्ण

	वापस bgmac_enet_probe(bgmac);
पूर्ण

अटल पूर्णांक bgmac_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा bgmac *bgmac = platक्रमm_get_drvdata(pdev);

	bgmac_enet_हटाओ(bgmac);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक bgmac_suspend(काष्ठा device *dev)
अणु
	काष्ठा bgmac *bgmac = dev_get_drvdata(dev);

	वापस bgmac_enet_suspend(bgmac);
पूर्ण

अटल पूर्णांक bgmac_resume(काष्ठा device *dev)
अणु
	काष्ठा bgmac *bgmac = dev_get_drvdata(dev);

	वापस bgmac_enet_resume(bgmac);
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops bgmac_pm_ops = अणु
	.suspend = bgmac_suspend,
	.resume = bgmac_resume
पूर्ण;

#घोषणा BGMAC_PM_OPS (&bgmac_pm_ops)
#अन्यथा
#घोषणा BGMAC_PM_OPS शून्य
#पूर्ण_अगर /* CONFIG_PM */

अटल स्थिर काष्ठा of_device_id bgmac_of_enet_match[] = अणु
	अणु.compatible = "brcm,amac",पूर्ण,
	अणु.compatible = "brcm,nsp-amac",पूर्ण,
	अणु.compatible = "brcm,ns2-amac",पूर्ण,
	अणुपूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(of, bgmac_of_enet_match);

अटल काष्ठा platक्रमm_driver bgmac_enet_driver = अणु
	.driver = अणु
		.name  = "bgmac-enet",
		.of_match_table = bgmac_of_enet_match,
		.pm = BGMAC_PM_OPS
	पूर्ण,
	.probe = bgmac_probe,
	.हटाओ = bgmac_हटाओ,
पूर्ण;

module_platक्रमm_driver(bgmac_enet_driver);
MODULE_LICENSE("GPL");
