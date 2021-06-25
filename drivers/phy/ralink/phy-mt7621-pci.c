<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Mediatek MT7621 PCI PHY Driver
 * Author: Sergio Paracuellos <sergio.paracuellos@gmail.com>
 */

#समावेश <dt-bindings/phy/phy.h>
#समावेश <linux/bitfield.h>
#समावेश <linux/bitops.h>
#समावेश <linux/module.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_device.h>
#समावेश <linux/phy/phy.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/sys_soc.h>
#समावेश <mt7621.h>
#समावेश <ralink_regs.h>

#घोषणा RG_PE1_PIPE_REG				0x02c
#घोषणा RG_PE1_PIPE_RST				BIT(12)
#घोषणा RG_PE1_PIPE_CMD_FRC			BIT(4)

#घोषणा RG_P0_TO_P1_WIDTH			0x100
#घोषणा RG_PE1_H_LCDDS_REG			0x49c
#घोषणा RG_PE1_H_LCDDS_PCW			GENMASK(30, 0)

#घोषणा RG_PE1_FRC_H_XTAL_REG			0x400
#घोषणा RG_PE1_FRC_H_XTAL_TYPE			BIT(8)
#घोषणा RG_PE1_H_XTAL_TYPE			GENMASK(10, 9)

#घोषणा RG_PE1_FRC_PHY_REG			0x000
#घोषणा RG_PE1_FRC_PHY_EN			BIT(4)
#घोषणा RG_PE1_PHY_EN				BIT(5)

#घोषणा RG_PE1_H_PLL_REG			0x490
#घोषणा RG_PE1_H_PLL_BC				GENMASK(23, 22)
#घोषणा RG_PE1_H_PLL_BP				GENMASK(21, 18)
#घोषणा RG_PE1_H_PLL_IR				GENMASK(15, 12)
#घोषणा RG_PE1_H_PLL_IC				GENMASK(11, 8)
#घोषणा RG_PE1_H_PLL_PREDIV			GENMASK(7, 6)
#घोषणा RG_PE1_PLL_DIVEN			GENMASK(3, 1)

#घोषणा RG_PE1_H_PLL_FBKSEL_REG			0x4bc
#घोषणा RG_PE1_H_PLL_FBKSEL			GENMASK(5, 4)

#घोषणा	RG_PE1_H_LCDDS_SSC_PRD_REG		0x4a4
#घोषणा RG_PE1_H_LCDDS_SSC_PRD			GENMASK(15, 0)

#घोषणा RG_PE1_H_LCDDS_SSC_DELTA_REG		0x4a8
#घोषणा RG_PE1_H_LCDDS_SSC_DELTA		GENMASK(11, 0)
#घोषणा RG_PE1_H_LCDDS_SSC_DELTA1		GENMASK(27, 16)

#घोषणा RG_PE1_LCDDS_CLK_PH_INV_REG		0x4a0
#घोषणा RG_PE1_LCDDS_CLK_PH_INV			BIT(5)

#घोषणा RG_PE1_H_PLL_BR_REG			0x4ac
#घोषणा RG_PE1_H_PLL_BR				GENMASK(18, 16)

#घोषणा	RG_PE1_MSTCKDIV_REG			0x414
#घोषणा RG_PE1_MSTCKDIV				GENMASK(7, 6)

#घोषणा RG_PE1_FRC_MSTCKDIV			BIT(5)

#घोषणा XTAL_MASK				GENMASK(8, 6)

#घोषणा MAX_PHYS	2

/**
 * काष्ठा mt7621_pci_phy - Mt7621 Pcie PHY core
 * @dev: poपूर्णांकer to device
 * @regmap: kernel regmap poपूर्णांकer
 * @phy: poपूर्णांकer to the kernel PHY device
 * @port_base: base रेजिस्टर
 * @has_dual_port: अगर the phy has dual ports.
 * @bypass_pipe_rst: mark अगर 'mt7621_bypass_pipe_rst'
 * needs to be executed. Depends on chip revision.
 */
काष्ठा mt7621_pci_phy अणु
	काष्ठा device *dev;
	काष्ठा regmap *regmap;
	काष्ठा phy *phy;
	व्योम __iomem *port_base;
	bool has_dual_port;
	bool bypass_pipe_rst;
पूर्ण;

अटल अंतरभूत व्योम mt7621_phy_rmw(काष्ठा mt7621_pci_phy *phy,
				  u32 reg, u32 clr, u32 set)
अणु
	u32 val;

	/*
	 * We cannot use 'regmap_write_bits' here because पूर्णांकernally
	 * 'set' is masked beक्रमe is set to the value that will be
	 * written to the रेजिस्टर. That way results in no reliable
	 * pci setup. Aव्योम to mask 'set' before set value to 'val'
	 * completely aव्योम the problem.
	 */
	regmap_पढ़ो(phy->regmap, reg, &val);
	val &= ~clr;
	val |= set;
	regmap_ग_लिखो(phy->regmap, reg, val);
पूर्ण

अटल व्योम mt7621_bypass_pipe_rst(काष्ठा mt7621_pci_phy *phy)
अणु
	mt7621_phy_rmw(phy, RG_PE1_PIPE_REG, 0, RG_PE1_PIPE_RST);
	mt7621_phy_rmw(phy, RG_PE1_PIPE_REG, 0, RG_PE1_PIPE_CMD_FRC);

	अगर (phy->has_dual_port) अणु
		mt7621_phy_rmw(phy, RG_PE1_PIPE_REG + RG_P0_TO_P1_WIDTH,
			       0, RG_PE1_PIPE_RST);
		mt7621_phy_rmw(phy, RG_PE1_PIPE_REG + RG_P0_TO_P1_WIDTH,
			       0, RG_PE1_PIPE_CMD_FRC);
	पूर्ण
पूर्ण

अटल व्योम mt7621_set_phy_क्रम_ssc(काष्ठा mt7621_pci_phy *phy)
अणु
	काष्ठा device *dev = phy->dev;
	u32 xtal_mode;

	xtal_mode = FIELD_GET(XTAL_MASK, rt_sysc_r32(SYSC_REG_SYSTEM_CONFIG0));

	/* Set PCIe Port PHY to disable SSC */
	/* Debug Xtal Type */
	mt7621_phy_rmw(phy, RG_PE1_FRC_H_XTAL_REG,
		       RG_PE1_FRC_H_XTAL_TYPE | RG_PE1_H_XTAL_TYPE,
		       RG_PE1_FRC_H_XTAL_TYPE |
		       FIELD_PREP(RG_PE1_H_XTAL_TYPE, 0x00));

	/* disable port */
	mt7621_phy_rmw(phy, RG_PE1_FRC_PHY_REG, RG_PE1_PHY_EN,
		       RG_PE1_FRC_PHY_EN);

	अगर (phy->has_dual_port) अणु
		mt7621_phy_rmw(phy, RG_PE1_FRC_PHY_REG + RG_P0_TO_P1_WIDTH,
			       RG_PE1_PHY_EN, RG_PE1_FRC_PHY_EN);
	पूर्ण

	अगर (xtal_mode <= 5 && xtal_mode >= 3) अणु /* 40MHz Xtal */
		/* Set Pre-भागider ratio (क्रम host mode) */
		mt7621_phy_rmw(phy, RG_PE1_H_PLL_REG, RG_PE1_H_PLL_PREDIV,
			       FIELD_PREP(RG_PE1_H_PLL_PREDIV, 0x01));

		dev_dbg(dev, "Xtal is 40MHz\n");
	पूर्ण अन्यथा अगर (xtal_mode >= 6) अणु /* 25MHz Xal */
		mt7621_phy_rmw(phy, RG_PE1_H_PLL_REG, RG_PE1_H_PLL_PREDIV,
			       FIELD_PREP(RG_PE1_H_PLL_PREDIV, 0x00));

		/* Select feedback घड़ी */
		mt7621_phy_rmw(phy, RG_PE1_H_PLL_FBKSEL_REG,
			       RG_PE1_H_PLL_FBKSEL,
			       FIELD_PREP(RG_PE1_H_PLL_FBKSEL, 0x01));

		/* DDS NCPO PCW (क्रम host mode) */
		mt7621_phy_rmw(phy, RG_PE1_H_LCDDS_SSC_PRD_REG,
			       RG_PE1_H_LCDDS_SSC_PRD,
			       FIELD_PREP(RG_PE1_H_LCDDS_SSC_PRD, 0x00));

		/* DDS SSC dither period control */
		mt7621_phy_rmw(phy, RG_PE1_H_LCDDS_SSC_PRD_REG,
			       RG_PE1_H_LCDDS_SSC_PRD,
			       FIELD_PREP(RG_PE1_H_LCDDS_SSC_PRD, 0x18d));

		/* DDS SSC dither amplitude control */
		mt7621_phy_rmw(phy, RG_PE1_H_LCDDS_SSC_DELTA_REG,
			       RG_PE1_H_LCDDS_SSC_DELTA |
			       RG_PE1_H_LCDDS_SSC_DELTA1,
			       FIELD_PREP(RG_PE1_H_LCDDS_SSC_DELTA, 0x4a) |
			       FIELD_PREP(RG_PE1_H_LCDDS_SSC_DELTA1, 0x4a));

		dev_dbg(dev, "Xtal is 25MHz\n");
	पूर्ण अन्यथा अणु /* 20MHz Xtal */
		mt7621_phy_rmw(phy, RG_PE1_H_PLL_REG, RG_PE1_H_PLL_PREDIV,
			       FIELD_PREP(RG_PE1_H_PLL_PREDIV, 0x00));

		dev_dbg(dev, "Xtal is 20MHz\n");
	पूर्ण

	/* DDS घड़ी inversion */
	mt7621_phy_rmw(phy, RG_PE1_LCDDS_CLK_PH_INV_REG,
		       RG_PE1_LCDDS_CLK_PH_INV, RG_PE1_LCDDS_CLK_PH_INV);

	/* Set PLL bits */
	mt7621_phy_rmw(phy, RG_PE1_H_PLL_REG,
		       RG_PE1_H_PLL_BC | RG_PE1_H_PLL_BP | RG_PE1_H_PLL_IR |
		       RG_PE1_H_PLL_IC | RG_PE1_PLL_DIVEN,
		       FIELD_PREP(RG_PE1_H_PLL_BC, 0x02) |
		       FIELD_PREP(RG_PE1_H_PLL_BP, 0x06) |
		       FIELD_PREP(RG_PE1_H_PLL_IR, 0x02) |
		       FIELD_PREP(RG_PE1_H_PLL_IC, 0x01) |
		       FIELD_PREP(RG_PE1_PLL_DIVEN, 0x02));

	mt7621_phy_rmw(phy, RG_PE1_H_PLL_BR_REG, RG_PE1_H_PLL_BR,
		       FIELD_PREP(RG_PE1_H_PLL_BR, 0x00));

	अगर (xtal_mode <= 5 && xtal_mode >= 3) अणु /* 40MHz Xtal */
		/* set क्रमce mode enable of da_pe1_mstckभाग */
		mt7621_phy_rmw(phy, RG_PE1_MSTCKDIV_REG,
			       RG_PE1_MSTCKDIV | RG_PE1_FRC_MSTCKDIV,
			       FIELD_PREP(RG_PE1_MSTCKDIV, 0x01) |
			       RG_PE1_FRC_MSTCKDIV);
	पूर्ण
पूर्ण

अटल पूर्णांक mt7621_pci_phy_init(काष्ठा phy *phy)
अणु
	काष्ठा mt7621_pci_phy *mphy = phy_get_drvdata(phy);

	अगर (mphy->bypass_pipe_rst)
		mt7621_bypass_pipe_rst(mphy);

	mt7621_set_phy_क्रम_ssc(mphy);

	वापस 0;
पूर्ण

अटल पूर्णांक mt7621_pci_phy_घातer_on(काष्ठा phy *phy)
अणु
	काष्ठा mt7621_pci_phy *mphy = phy_get_drvdata(phy);

	/* Enable PHY and disable क्रमce mode */
	mt7621_phy_rmw(mphy, RG_PE1_FRC_PHY_REG,
		       RG_PE1_FRC_PHY_EN, RG_PE1_PHY_EN);

	अगर (mphy->has_dual_port) अणु
		mt7621_phy_rmw(mphy, RG_PE1_FRC_PHY_REG + RG_P0_TO_P1_WIDTH,
			       RG_PE1_FRC_PHY_EN, RG_PE1_PHY_EN);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mt7621_pci_phy_घातer_off(काष्ठा phy *phy)
अणु
	काष्ठा mt7621_pci_phy *mphy = phy_get_drvdata(phy);

	/* Disable PHY */
	mt7621_phy_rmw(mphy, RG_PE1_FRC_PHY_REG,
		       RG_PE1_PHY_EN, RG_PE1_FRC_PHY_EN);

	अगर (mphy->has_dual_port) अणु
		mt7621_phy_rmw(mphy, RG_PE1_FRC_PHY_REG + RG_P0_TO_P1_WIDTH,
			       RG_PE1_PHY_EN, RG_PE1_FRC_PHY_EN);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mt7621_pci_phy_निकास(काष्ठा phy *phy)
अणु
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा phy_ops mt7621_pci_phy_ops = अणु
	.init		= mt7621_pci_phy_init,
	.निकास		= mt7621_pci_phy_निकास,
	.घातer_on	= mt7621_pci_phy_घातer_on,
	.घातer_off	= mt7621_pci_phy_घातer_off,
	.owner		= THIS_MODULE,
पूर्ण;

अटल काष्ठा phy *mt7621_pcie_phy_of_xlate(काष्ठा device *dev,
					    काष्ठा of_phandle_args *args)
अणु
	काष्ठा mt7621_pci_phy *mt7621_phy = dev_get_drvdata(dev);

	अगर (WARN_ON(args->args[0] >= MAX_PHYS))
		वापस ERR_PTR(-ENODEV);

	mt7621_phy->has_dual_port = args->args[0];

	dev_info(dev, "PHY for 0x%08x (dual port = %d)\n",
		 (अचिन्हित पूर्णांक)mt7621_phy->port_base, mt7621_phy->has_dual_port);

	वापस mt7621_phy->phy;
पूर्ण

अटल स्थिर काष्ठा soc_device_attribute mt7621_pci_quirks_match[] = अणु
	अणु .soc_id = "mt7621", .revision = "E2" पूर्ण
पूर्ण;

अटल स्थिर काष्ठा regmap_config mt7621_pci_phy_regmap_config = अणु
	.reg_bits = 32,
	.val_bits = 32,
	.reg_stride = 4,
	.max_रेजिस्टर = 0x700,
पूर्ण;

अटल पूर्णांक mt7621_pci_phy_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	स्थिर काष्ठा soc_device_attribute *attr;
	काष्ठा phy_provider *provider;
	काष्ठा mt7621_pci_phy *phy;

	phy = devm_kzalloc(dev, माप(*phy), GFP_KERNEL);
	अगर (!phy)
		वापस -ENOMEM;

	attr = soc_device_match(mt7621_pci_quirks_match);
	अगर (attr)
		phy->bypass_pipe_rst = true;

	phy->dev = dev;
	platक्रमm_set_drvdata(pdev, phy);

	phy->port_base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(phy->port_base)) अणु
		dev_err(dev, "failed to remap phy regs\n");
		वापस PTR_ERR(phy->port_base);
	पूर्ण

	phy->regmap = devm_regmap_init_mmio(phy->dev, phy->port_base,
					    &mt7621_pci_phy_regmap_config);
	अगर (IS_ERR(phy->regmap))
		वापस PTR_ERR(phy->regmap);

	phy->phy = devm_phy_create(dev, dev->of_node, &mt7621_pci_phy_ops);
	अगर (IS_ERR(phy->phy)) अणु
		dev_err(dev, "failed to create phy\n");
		वापस PTR_ERR(phy->phy);
	पूर्ण

	phy_set_drvdata(phy->phy, phy);

	provider = devm_of_phy_provider_रेजिस्टर(dev, mt7621_pcie_phy_of_xlate);

	वापस PTR_ERR_OR_ZERO(provider);
पूर्ण

अटल स्थिर काष्ठा of_device_id mt7621_pci_phy_ids[] = अणु
	अणु .compatible = "mediatek,mt7621-pci-phy" पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, mt7621_pci_phy_ids);

अटल काष्ठा platक्रमm_driver mt7621_pci_phy_driver = अणु
	.probe = mt7621_pci_phy_probe,
	.driver = अणु
		.name = "mt7621-pci-phy",
		.of_match_table = mt7621_pci_phy_ids,
	पूर्ण,
पूर्ण;

builtin_platक्रमm_driver(mt7621_pci_phy_driver);

MODULE_AUTHOR("Sergio Paracuellos <sergio.paracuellos@gmail.com>");
MODULE_DESCRIPTION("MediaTek MT7621 PCIe PHY driver");
MODULE_LICENSE("GPL v2");
