<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2016-2018 Broadcom
 */

#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/of.h>
#समावेश <linux/phy/phy.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>

/* we have up to 8 PAXB based RC. The 9th one is always PAXC */
#घोषणा SR_NR_PCIE_PHYS               9
#घोषणा SR_PAXC_PHY_IDX               (SR_NR_PCIE_PHYS - 1)

#घोषणा PCIE_PIPEMUX_CFG_OFFSET       0x10c
#घोषणा PCIE_PIPEMUX_SELECT_STRAP     0xf

#घोषणा CDRU_STRAP_DATA_LSW_OFFSET    0x5c
#घोषणा PCIE_PIPEMUX_SHIFT            19
#घोषणा PCIE_PIPEMUX_MASK             0xf

#घोषणा MHB_MEM_PW_PAXC_OFFSET        0x1c0
#घोषणा MHB_PWR_ARR_POWERON           0x8
#घोषणा MHB_PWR_ARR_POWEROK           0x4
#घोषणा MHB_PWR_POWERON               0x2
#घोषणा MHB_PWR_POWEROK               0x1
#घोषणा MHB_PWR_STATUS_MASK           (MHB_PWR_ARR_POWERON | \
				       MHB_PWR_ARR_POWEROK | \
				       MHB_PWR_POWERON | \
				       MHB_PWR_POWEROK)

काष्ठा sr_pcie_phy_core;

/**
 * काष्ठा sr_pcie_phy - Stingray PCIe PHY
 *
 * @core: poपूर्णांकer to the Stingray PCIe PHY core control
 * @index: PHY index
 * @phy: poपूर्णांकer to the kernel PHY device
 */
काष्ठा sr_pcie_phy अणु
	काष्ठा sr_pcie_phy_core *core;
	अचिन्हित पूर्णांक index;
	काष्ठा phy *phy;
पूर्ण;

/**
 * काष्ठा sr_pcie_phy_core - Stingray PCIe PHY core control
 *
 * @dev: poपूर्णांकer to device
 * @base: base रेजिस्टर of PCIe SS
 * @cdru: regmap to the CDRU device
 * @mhb: regmap to the MHB device
 * @pipemux: pipemuex strap
 * @phys: array of PCIe PHYs
 */
काष्ठा sr_pcie_phy_core अणु
	काष्ठा device *dev;
	व्योम __iomem *base;
	काष्ठा regmap *cdru;
	काष्ठा regmap *mhb;
	u32 pipemux;
	काष्ठा sr_pcie_phy phys[SR_NR_PCIE_PHYS];
पूर्ण;

/*
 * PCIe PIPEMUX lookup table
 *
 * Each array index represents a PIPEMUX strap setting
 * The array element represents a biपंचांगap where a set bit means the PCIe
 * core and associated serdes has been enabled as RC and is available क्रम use
 */
अटल स्थिर u8 pipemux_table[] = अणु
	/* PIPEMUX = 0, EP 1x16 */
	0x00,
	/* PIPEMUX = 1, EP 1x8 + RC 1x8, core 7 */
	0x80,
	/* PIPEMUX = 2, EP 4x4 */
	0x00,
	/* PIPEMUX = 3, RC 2x8, cores 0, 7 */
	0x81,
	/* PIPEMUX = 4, RC 4x4, cores 0, 1, 6, 7 */
	0xc3,
	/* PIPEMUX = 5, RC 8x2, all 8 cores */
	0xff,
	/* PIPEMUX = 6, RC 3x4 + 2x2, cores 0, 2, 3, 6, 7 */
	0xcd,
	/* PIPEMUX = 7, RC 1x4 + 6x2, cores 0, 2, 3, 4, 5, 6, 7 */
	0xfd,
	/* PIPEMUX = 8, EP 1x8 + RC 4x2, cores 4, 5, 6, 7 */
	0xf0,
	/* PIPEMUX = 9, EP 1x8 + RC 2x4, cores 6, 7 */
	0xc0,
	/* PIPEMUX = 10, EP 2x4 + RC 2x4, cores 1, 6 */
	0x42,
	/* PIPEMUX = 11, EP 2x4 + RC 4x2, cores 2, 3, 4, 5 */
	0x3c,
	/* PIPEMUX = 12, EP 1x4 + RC 6x2, cores 2, 3, 4, 5, 6, 7 */
	0xfc,
	/* PIPEMUX = 13, RC 2x4 + RC 1x4 + 2x2, cores 2, 3, 6 */
	0x4c,
पूर्ण;

/*
 * Return true अगर the strap setting is valid
 */
अटल bool pipemux_strap_is_valid(u32 pipemux)
अणु
	वापस !!(pipemux < ARRAY_SIZE(pipemux_table));
पूर्ण

/*
 * Read the PCIe PIPEMUX from strap
 */
अटल u32 pipemux_strap_पढ़ो(काष्ठा sr_pcie_phy_core *core)
अणु
	u32 pipemux;

	/*
	 * Read PIPEMUX configuration रेजिस्टर to determine the pipemux setting
	 *
	 * In the हाल when the value indicates using HW strap, fall back to
	 * use HW strap
	 */
	pipemux = पढ़ोl(core->base + PCIE_PIPEMUX_CFG_OFFSET);
	pipemux &= PCIE_PIPEMUX_MASK;
	अगर (pipemux == PCIE_PIPEMUX_SELECT_STRAP) अणु
		regmap_पढ़ो(core->cdru, CDRU_STRAP_DATA_LSW_OFFSET, &pipemux);
		pipemux >>= PCIE_PIPEMUX_SHIFT;
		pipemux &= PCIE_PIPEMUX_MASK;
	पूर्ण

	वापस pipemux;
पूर्ण

/*
 * Given a PIPEMUX strap and PCIe core index, this function वापसs true अगर the
 * PCIe core needs to be enabled
 */
अटल bool pcie_core_is_क्रम_rc(काष्ठा sr_pcie_phy *phy)
अणु
	काष्ठा sr_pcie_phy_core *core = phy->core;
	अचिन्हित पूर्णांक core_idx = phy->index;

	वापस !!((pipemux_table[core->pipemux] >> core_idx) & 0x1);
पूर्ण

अटल पूर्णांक sr_pcie_phy_init(काष्ठा phy *p)
अणु
	काष्ठा sr_pcie_phy *phy = phy_get_drvdata(p);

	/*
	 * Check whether this PHY is क्रम root complex or not. If yes, वापस
	 * zero so the host driver can proceed to क्रमागतeration. If not, वापस
	 * an error and that will क्रमce the host driver to bail out
	 */
	अगर (pcie_core_is_क्रम_rc(phy))
		वापस 0;

	वापस -ENODEV;
पूर्ण

अटल पूर्णांक sr_paxc_phy_init(काष्ठा phy *p)
अणु
	काष्ठा sr_pcie_phy *phy = phy_get_drvdata(p);
	काष्ठा sr_pcie_phy_core *core = phy->core;
	अचिन्हित पूर्णांक core_idx = phy->index;
	u32 val;

	अगर (core_idx != SR_PAXC_PHY_IDX)
		वापस -EINVAL;

	regmap_पढ़ो(core->mhb, MHB_MEM_PW_PAXC_OFFSET, &val);
	अगर ((val & MHB_PWR_STATUS_MASK) != MHB_PWR_STATUS_MASK) अणु
		dev_err(core->dev, "PAXC is not powered up\n");
		वापस -ENODEV;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा phy_ops sr_pcie_phy_ops = अणु
	.init = sr_pcie_phy_init,
	.owner = THIS_MODULE,
पूर्ण;

अटल स्थिर काष्ठा phy_ops sr_paxc_phy_ops = अणु
	.init = sr_paxc_phy_init,
	.owner = THIS_MODULE,
पूर्ण;

अटल काष्ठा phy *sr_pcie_phy_xlate(काष्ठा device *dev,
				     काष्ठा of_phandle_args *args)
अणु
	काष्ठा sr_pcie_phy_core *core;
	पूर्णांक phy_idx;

	core = dev_get_drvdata(dev);
	अगर (!core)
		वापस ERR_PTR(-EINVAL);

	phy_idx = args->args[0];

	अगर (WARN_ON(phy_idx >= SR_NR_PCIE_PHYS))
		वापस ERR_PTR(-ENODEV);

	वापस core->phys[phy_idx].phy;
पूर्ण

अटल पूर्णांक sr_pcie_phy_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *node = dev->of_node;
	काष्ठा sr_pcie_phy_core *core;
	काष्ठा phy_provider *provider;
	अचिन्हित पूर्णांक phy_idx = 0;

	core = devm_kzalloc(dev, माप(*core), GFP_KERNEL);
	अगर (!core)
		वापस -ENOMEM;

	core->dev = dev;
	core->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(core->base))
		वापस PTR_ERR(core->base);

	core->cdru = syscon_regmap_lookup_by_phandle(node, "brcm,sr-cdru");
	अगर (IS_ERR(core->cdru)) अणु
		dev_err(core->dev, "unable to find CDRU device\n");
		वापस PTR_ERR(core->cdru);
	पूर्ण

	core->mhb = syscon_regmap_lookup_by_phandle(node, "brcm,sr-mhb");
	अगर (IS_ERR(core->mhb)) अणु
		dev_err(core->dev, "unable to find MHB device\n");
		वापस PTR_ERR(core->mhb);
	पूर्ण

	/* पढ़ो the PCIe PIPEMUX strap setting */
	core->pipemux = pipemux_strap_पढ़ो(core);
	अगर (!pipemux_strap_is_valid(core->pipemux)) अणु
		dev_err(core->dev, "invalid PCIe PIPEMUX strap %u\n",
			core->pipemux);
		वापस -EIO;
	पूर्ण

	क्रम (phy_idx = 0; phy_idx < SR_NR_PCIE_PHYS; phy_idx++) अणु
		काष्ठा sr_pcie_phy *p = &core->phys[phy_idx];
		स्थिर काष्ठा phy_ops *ops;

		अगर (phy_idx == SR_PAXC_PHY_IDX)
			ops = &sr_paxc_phy_ops;
		अन्यथा
			ops = &sr_pcie_phy_ops;

		p->phy = devm_phy_create(dev, शून्य, ops);
		अगर (IS_ERR(p->phy)) अणु
			dev_err(dev, "failed to create PCIe PHY\n");
			वापस PTR_ERR(p->phy);
		पूर्ण

		p->core = core;
		p->index = phy_idx;
		phy_set_drvdata(p->phy, p);
	पूर्ण

	dev_set_drvdata(dev, core);

	provider = devm_of_phy_provider_रेजिस्टर(dev, sr_pcie_phy_xlate);
	अगर (IS_ERR(provider)) अणु
		dev_err(dev, "failed to register PHY provider\n");
		वापस PTR_ERR(provider);
	पूर्ण

	dev_info(dev, "Stingray PCIe PHY driver initialized\n");

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id sr_pcie_phy_match_table[] = अणु
	अणु .compatible = "brcm,sr-pcie-phy" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, sr_pcie_phy_match_table);

अटल काष्ठा platक्रमm_driver sr_pcie_phy_driver = अणु
	.driver = अणु
		.name		= "sr-pcie-phy",
		.of_match_table	= sr_pcie_phy_match_table,
	पूर्ण,
	.probe	= sr_pcie_phy_probe,
पूर्ण;
module_platक्रमm_driver(sr_pcie_phy_driver);

MODULE_AUTHOR("Ray Jui <ray.jui@broadcom.com>");
MODULE_DESCRIPTION("Broadcom Stingray PCIe PHY driver");
MODULE_LICENSE("GPL v2");
