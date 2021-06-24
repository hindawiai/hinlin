<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * MediaTek AHCI SATA driver
 *
 * Copyright (c) 2017 MediaTek Inc.
 * Author: Ryder Lee <ryder.lee@mediatek.com>
 */

#समावेश <linux/ahci_platक्रमm.h>
#समावेश <linux/kernel.h>
#समावेश <linux/libata.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm.h>
#समावेश <linux/regmap.h>
#समावेश <linux/reset.h>
#समावेश "ahci.h"

#घोषणा DRV_NAME		"ahci-mtk"

#घोषणा SYS_CFG			0x14
#घोषणा SYS_CFG_SATA_MSK	GENMASK(31, 30)
#घोषणा SYS_CFG_SATA_EN		BIT(31)

काष्ठा mtk_ahci_plat अणु
	काष्ठा regmap *mode;
	काष्ठा reset_control *axi_rst;
	काष्ठा reset_control *sw_rst;
	काष्ठा reset_control *reg_rst;
पूर्ण;

अटल स्थिर काष्ठा ata_port_info ahci_port_info = अणु
	.flags		= AHCI_FLAG_COMMON,
	.pio_mask	= ATA_PIO4,
	.udma_mask	= ATA_UDMA6,
	.port_ops	= &ahci_platक्रमm_ops,
पूर्ण;

अटल काष्ठा scsi_host_ढाँचा ahci_platक्रमm_sht = अणु
	AHCI_SHT(DRV_NAME),
पूर्ण;

अटल पूर्णांक mtk_ahci_platक्रमm_resets(काष्ठा ahci_host_priv *hpriv,
				    काष्ठा device *dev)
अणु
	काष्ठा mtk_ahci_plat *plat = hpriv->plat_data;
	पूर्णांक err;

	/* reset AXI bus and PHY part */
	plat->axi_rst = devm_reset_control_get_optional_exclusive(dev, "axi");
	अगर (PTR_ERR(plat->axi_rst) == -EPROBE_DEFER)
		वापस PTR_ERR(plat->axi_rst);

	plat->sw_rst = devm_reset_control_get_optional_exclusive(dev, "sw");
	अगर (PTR_ERR(plat->sw_rst) == -EPROBE_DEFER)
		वापस PTR_ERR(plat->sw_rst);

	plat->reg_rst = devm_reset_control_get_optional_exclusive(dev, "reg");
	अगर (PTR_ERR(plat->reg_rst) == -EPROBE_DEFER)
		वापस PTR_ERR(plat->reg_rst);

	err = reset_control_निश्चित(plat->axi_rst);
	अगर (err) अणु
		dev_err(dev, "failed to assert AXI bus\n");
		वापस err;
	पूर्ण

	err = reset_control_निश्चित(plat->sw_rst);
	अगर (err) अणु
		dev_err(dev, "failed to assert PHY digital part\n");
		वापस err;
	पूर्ण

	err = reset_control_निश्चित(plat->reg_rst);
	अगर (err) अणु
		dev_err(dev, "failed to assert PHY register part\n");
		वापस err;
	पूर्ण

	err = reset_control_deनिश्चित(plat->reg_rst);
	अगर (err) अणु
		dev_err(dev, "failed to deassert PHY register part\n");
		वापस err;
	पूर्ण

	err = reset_control_deनिश्चित(plat->sw_rst);
	अगर (err) अणु
		dev_err(dev, "failed to deassert PHY digital part\n");
		वापस err;
	पूर्ण

	err = reset_control_deनिश्चित(plat->axi_rst);
	अगर (err) अणु
		dev_err(dev, "failed to deassert AXI bus\n");
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mtk_ahci_parse_property(काष्ठा ahci_host_priv *hpriv,
				   काष्ठा device *dev)
अणु
	काष्ठा mtk_ahci_plat *plat = hpriv->plat_data;
	काष्ठा device_node *np = dev->of_node;

	/* enable SATA function अगर needed */
	अगर (of_find_property(np, "mediatek,phy-mode", शून्य)) अणु
		plat->mode = syscon_regmap_lookup_by_phandle(
					np, "mediatek,phy-mode");
		अगर (IS_ERR(plat->mode)) अणु
			dev_err(dev, "missing phy-mode phandle\n");
			वापस PTR_ERR(plat->mode);
		पूर्ण

		regmap_update_bits(plat->mode, SYS_CFG, SYS_CFG_SATA_MSK,
				   SYS_CFG_SATA_EN);
	पूर्ण

	of_property_पढ़ो_u32(np, "ports-implemented", &hpriv->क्रमce_port_map);

	वापस 0;
पूर्ण

अटल पूर्णांक mtk_ahci_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा mtk_ahci_plat *plat;
	काष्ठा ahci_host_priv *hpriv;
	पूर्णांक err;

	plat = devm_kzalloc(dev, माप(*plat), GFP_KERNEL);
	अगर (!plat)
		वापस -ENOMEM;

	hpriv = ahci_platक्रमm_get_resources(pdev, 0);
	अगर (IS_ERR(hpriv))
		वापस PTR_ERR(hpriv);

	hpriv->plat_data = plat;

	err = mtk_ahci_parse_property(hpriv, dev);
	अगर (err)
		वापस err;

	err = mtk_ahci_platक्रमm_resets(hpriv, dev);
	अगर (err)
		वापस err;

	err = ahci_platक्रमm_enable_resources(hpriv);
	अगर (err)
		वापस err;

	err = ahci_platक्रमm_init_host(pdev, hpriv, &ahci_port_info,
				      &ahci_platक्रमm_sht);
	अगर (err)
		जाओ disable_resources;

	वापस 0;

disable_resources:
	ahci_platक्रमm_disable_resources(hpriv);
	वापस err;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(ahci_pm_ops, ahci_platक्रमm_suspend,
			 ahci_platक्रमm_resume);

अटल स्थिर काष्ठा of_device_id ahci_of_match[] = अणु
	अणु .compatible = "mediatek,mtk-ahci", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, ahci_of_match);

अटल काष्ठा platक्रमm_driver mtk_ahci_driver = अणु
	.probe = mtk_ahci_probe,
	.हटाओ = ata_platक्रमm_हटाओ_one,
	.driver = अणु
		.name = DRV_NAME,
		.of_match_table = ahci_of_match,
		.pm = &ahci_pm_ops,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(mtk_ahci_driver);

MODULE_DESCRIPTION("MediaTek SATA AHCI Driver");
MODULE_LICENSE("GPL v2");
