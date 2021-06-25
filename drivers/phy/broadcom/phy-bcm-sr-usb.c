<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2016-2018 Broadcom
 */

#समावेश <linux/delay.h>
#समावेश <linux/पन.स>
#समावेश <linux/iopoll.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/phy/phy.h>
#समावेश <linux/platक्रमm_device.h>

क्रमागत bcm_usb_phy_version अणु
	BCM_SR_USB_COMBO_PHY,
	BCM_SR_USB_HS_PHY,
पूर्ण;

क्रमागत bcm_usb_phy_reg अणु
	PLL_CTRL,
	PHY_CTRL,
	PHY_PLL_CTRL,
पूर्ण;

/* USB PHY रेजिस्टरs */

अटल स्थिर u8 bcm_usb_combo_phy_ss[] = अणु
	[PLL_CTRL]		= 0x18,
	[PHY_CTRL]		= 0x14,
पूर्ण;

अटल स्थिर u8 bcm_usb_combo_phy_hs[] = अणु
	[PLL_CTRL]	= 0x0c,
	[PHY_CTRL]	= 0x10,
पूर्ण;

अटल स्थिर u8 bcm_usb_hs_phy[] = अणु
	[PLL_CTRL]	= 0x8,
	[PHY_CTRL]	= 0xc,
पूर्ण;

क्रमागत pll_ctrl_bits अणु
	PLL_RESETB,
	SSPLL_SUSPEND_EN,
	PLL_SEQ_START,
	PLL_LOCK,
पूर्ण;

अटल स्थिर u8 u3pll_ctrl[] = अणु
	[PLL_RESETB]		= 0,
	[SSPLL_SUSPEND_EN]	= 1,
	[PLL_SEQ_START]		= 2,
	[PLL_LOCK]		= 3,
पूर्ण;

#घोषणा HSPLL_PDIV_MASK		0xF
#घोषणा HSPLL_PDIV_VAL		0x1

अटल स्थिर u8 u2pll_ctrl[] = अणु
	[PLL_RESETB]	= 5,
	[PLL_LOCK]	= 6,
पूर्ण;

क्रमागत bcm_usb_phy_ctrl_bits अणु
	CORERDY,
	PHY_RESETB,
	PHY_PCTL,
पूर्ण;

#घोषणा PHY_PCTL_MASK	0xffff
#घोषणा SSPHY_PCTL_VAL	0x0006

अटल स्थिर u8 u3phy_ctrl[] = अणु
	[PHY_RESETB]	= 1,
	[PHY_PCTL]	= 2,
पूर्ण;

अटल स्थिर u8 u2phy_ctrl[] = अणु
	[CORERDY]		= 0,
	[PHY_RESETB]		= 5,
	[PHY_PCTL]		= 6,
पूर्ण;

काष्ठा bcm_usb_phy_cfg अणु
	uपूर्णांक32_t type;
	uपूर्णांक32_t version;
	व्योम __iomem *regs;
	काष्ठा phy *phy;
	स्थिर u8 *offset;
पूर्ण;

#घोषणा PLL_LOCK_RETRY_COUNT	1000

क्रमागत bcm_usb_phy_type अणु
	USB_HS_PHY,
	USB_SS_PHY,
पूर्ण;

#घोषणा NUM_BCM_SR_USB_COMBO_PHYS	2

अटल अंतरभूत व्योम bcm_usb_reg32_clrbits(व्योम __iomem *addr, uपूर्णांक32_t clear)
अणु
	ग_लिखोl(पढ़ोl(addr) & ~clear, addr);
पूर्ण

अटल अंतरभूत व्योम bcm_usb_reg32_setbits(व्योम __iomem *addr, uपूर्णांक32_t set)
अणु
	ग_लिखोl(पढ़ोl(addr) | set, addr);
पूर्ण

अटल पूर्णांक bcm_usb_pll_lock_check(व्योम __iomem *addr, u32 bit)
अणु
	u32 data;
	पूर्णांक ret;

	ret = पढ़ोl_poll_समयout_atomic(addr, data, (data & bit), 1,
					PLL_LOCK_RETRY_COUNT);
	अगर (ret)
		pr_err("%s: FAIL\n", __func__);

	वापस ret;
पूर्ण

अटल पूर्णांक bcm_usb_ss_phy_init(काष्ठा bcm_usb_phy_cfg *phy_cfg)
अणु
	पूर्णांक ret = 0;
	व्योम __iomem *regs = phy_cfg->regs;
	स्थिर u8 *offset;
	u32 rd_data;

	offset = phy_cfg->offset;

	/* Set pctl with mode and soft reset */
	rd_data = पढ़ोl(regs + offset[PHY_CTRL]);
	rd_data &= ~(PHY_PCTL_MASK << u3phy_ctrl[PHY_PCTL]);
	rd_data |= (SSPHY_PCTL_VAL << u3phy_ctrl[PHY_PCTL]);
	ग_लिखोl(rd_data, regs + offset[PHY_CTRL]);

	bcm_usb_reg32_clrbits(regs + offset[PLL_CTRL],
			      BIT(u3pll_ctrl[SSPLL_SUSPEND_EN]));
	bcm_usb_reg32_setbits(regs + offset[PLL_CTRL],
			      BIT(u3pll_ctrl[PLL_SEQ_START]));
	bcm_usb_reg32_setbits(regs + offset[PLL_CTRL],
			      BIT(u3pll_ctrl[PLL_RESETB]));

	/* Maximum समयout क्रम PLL reset करोne */
	msleep(30);

	ret = bcm_usb_pll_lock_check(regs + offset[PLL_CTRL],
				     BIT(u3pll_ctrl[PLL_LOCK]));

	वापस ret;
पूर्ण

अटल पूर्णांक bcm_usb_hs_phy_init(काष्ठा bcm_usb_phy_cfg *phy_cfg)
अणु
	पूर्णांक ret = 0;
	व्योम __iomem *regs = phy_cfg->regs;
	स्थिर u8 *offset;

	offset = phy_cfg->offset;

	bcm_usb_reg32_clrbits(regs + offset[PLL_CTRL],
			      BIT(u2pll_ctrl[PLL_RESETB]));
	bcm_usb_reg32_setbits(regs + offset[PLL_CTRL],
			      BIT(u2pll_ctrl[PLL_RESETB]));

	ret = bcm_usb_pll_lock_check(regs + offset[PLL_CTRL],
				     BIT(u2pll_ctrl[PLL_LOCK]));

	वापस ret;
पूर्ण

अटल पूर्णांक bcm_usb_phy_reset(काष्ठा phy *phy)
अणु
	काष्ठा bcm_usb_phy_cfg *phy_cfg = phy_get_drvdata(phy);
	व्योम __iomem *regs = phy_cfg->regs;
	स्थिर u8 *offset;

	offset = phy_cfg->offset;

	अगर (phy_cfg->type == USB_HS_PHY) अणु
		bcm_usb_reg32_clrbits(regs + offset[PHY_CTRL],
				      BIT(u2phy_ctrl[CORERDY]));
		bcm_usb_reg32_setbits(regs + offset[PHY_CTRL],
				      BIT(u2phy_ctrl[CORERDY]));
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक bcm_usb_phy_init(काष्ठा phy *phy)
अणु
	काष्ठा bcm_usb_phy_cfg *phy_cfg = phy_get_drvdata(phy);
	पूर्णांक ret = -EINVAL;

	अगर (phy_cfg->type == USB_SS_PHY)
		ret = bcm_usb_ss_phy_init(phy_cfg);
	अन्यथा अगर (phy_cfg->type == USB_HS_PHY)
		ret = bcm_usb_hs_phy_init(phy_cfg);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा phy_ops sr_phy_ops = अणु
	.init		= bcm_usb_phy_init,
	.reset		= bcm_usb_phy_reset,
	.owner		= THIS_MODULE,
पूर्ण;

अटल काष्ठा phy *bcm_usb_phy_xlate(काष्ठा device *dev,
				     काष्ठा of_phandle_args *args)
अणु
	काष्ठा bcm_usb_phy_cfg *phy_cfg;
	पूर्णांक phy_idx;

	phy_cfg = dev_get_drvdata(dev);
	अगर (!phy_cfg)
		वापस ERR_PTR(-EINVAL);

	अगर (phy_cfg->version == BCM_SR_USB_COMBO_PHY) अणु
		phy_idx = args->args[0];

		अगर (WARN_ON(phy_idx > 1))
			वापस ERR_PTR(-ENODEV);

		वापस phy_cfg[phy_idx].phy;
	पूर्ण अन्यथा
		वापस phy_cfg->phy;
पूर्ण

अटल पूर्णांक bcm_usb_phy_create(काष्ठा device *dev, काष्ठा device_node *node,
			      व्योम __iomem *regs, uपूर्णांक32_t version)
अणु
	काष्ठा bcm_usb_phy_cfg *phy_cfg;
	पूर्णांक idx;

	अगर (version == BCM_SR_USB_COMBO_PHY) अणु
		phy_cfg = devm_kzalloc(dev, NUM_BCM_SR_USB_COMBO_PHYS *
				       माप(काष्ठा bcm_usb_phy_cfg),
				       GFP_KERNEL);
		अगर (!phy_cfg)
			वापस -ENOMEM;

		क्रम (idx = 0; idx < NUM_BCM_SR_USB_COMBO_PHYS; idx++) अणु
			phy_cfg[idx].regs = regs;
			phy_cfg[idx].version = version;
			अगर (idx == 0) अणु
				phy_cfg[idx].offset = bcm_usb_combo_phy_hs;
				phy_cfg[idx].type = USB_HS_PHY;
			पूर्ण अन्यथा अणु
				phy_cfg[idx].offset = bcm_usb_combo_phy_ss;
				phy_cfg[idx].type = USB_SS_PHY;
			पूर्ण
			phy_cfg[idx].phy = devm_phy_create(dev, node,
							   &sr_phy_ops);
			अगर (IS_ERR(phy_cfg[idx].phy))
				वापस PTR_ERR(phy_cfg[idx].phy);

			phy_set_drvdata(phy_cfg[idx].phy, &phy_cfg[idx]);
		पूर्ण
	पूर्ण अन्यथा अगर (version == BCM_SR_USB_HS_PHY) अणु
		phy_cfg = devm_kzalloc(dev, माप(काष्ठा bcm_usb_phy_cfg),
				       GFP_KERNEL);
		अगर (!phy_cfg)
			वापस -ENOMEM;

		phy_cfg->regs = regs;
		phy_cfg->version = version;
		phy_cfg->offset = bcm_usb_hs_phy;
		phy_cfg->type = USB_HS_PHY;
		phy_cfg->phy = devm_phy_create(dev, node, &sr_phy_ops);
		अगर (IS_ERR(phy_cfg->phy))
			वापस PTR_ERR(phy_cfg->phy);

		phy_set_drvdata(phy_cfg->phy, phy_cfg);
	पूर्ण अन्यथा
		वापस -ENODEV;

	dev_set_drvdata(dev, phy_cfg);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id bcm_usb_phy_of_match[] = अणु
	अणु
		.compatible = "brcm,sr-usb-combo-phy",
		.data = (व्योम *)BCM_SR_USB_COMBO_PHY,
	पूर्ण,
	अणु
		.compatible = "brcm,sr-usb-hs-phy",
		.data = (व्योम *)BCM_SR_USB_HS_PHY,
	पूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, bcm_usb_phy_of_match);

अटल पूर्णांक bcm_usb_phy_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *dn = dev->of_node;
	स्थिर काष्ठा of_device_id *of_id;
	व्योम __iomem *regs;
	पूर्णांक ret;
	क्रमागत bcm_usb_phy_version version;
	काष्ठा phy_provider *phy_provider;

	regs = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(regs))
		वापस PTR_ERR(regs);

	of_id = of_match_node(bcm_usb_phy_of_match, dn);
	अगर (of_id)
		version = (क्रमागत bcm_usb_phy_version)of_id->data;
	अन्यथा
		वापस -ENODEV;

	ret = bcm_usb_phy_create(dev, dn, regs, version);
	अगर (ret)
		वापस ret;

	phy_provider = devm_of_phy_provider_रेजिस्टर(dev, bcm_usb_phy_xlate);

	वापस PTR_ERR_OR_ZERO(phy_provider);
पूर्ण

अटल काष्ठा platक्रमm_driver bcm_usb_phy_driver = अणु
	.driver = अणु
		.name = "phy-bcm-sr-usb",
		.of_match_table = bcm_usb_phy_of_match,
	पूर्ण,
	.probe = bcm_usb_phy_probe,
पूर्ण;
module_platक्रमm_driver(bcm_usb_phy_driver);

MODULE_AUTHOR("Broadcom");
MODULE_DESCRIPTION("Broadcom stingray USB Phy driver");
MODULE_LICENSE("GPL v2");
