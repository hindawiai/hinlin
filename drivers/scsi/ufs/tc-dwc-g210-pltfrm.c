<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Synopsys G210 Test Chip driver
 *
 * Copyright (C) 2015-2016 Synopsys, Inc. (www.synopsys.com)
 *
 * Authors: Joao Pपूर्णांकo <jpपूर्णांकo@synopsys.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/of.h>
#समावेश <linux/delay.h>

#समावेश "ufshcd-pltfrm.h"
#समावेश "ufshcd-dwc.h"
#समावेश "tc-dwc-g210.h"

/*
 * UFS DWC specअगरic variant operations
 */
अटल काष्ठा ufs_hba_variant_ops tc_dwc_g210_20bit_pltfm_hba_vops = अणु
	.name                   = "tc-dwc-g210-pltfm",
	.link_startup_notअगरy	= ufshcd_dwc_link_startup_notअगरy,
	.phy_initialization = tc_dwc_g210_config_20_bit,
पूर्ण;

अटल काष्ठा ufs_hba_variant_ops tc_dwc_g210_40bit_pltfm_hba_vops = अणु
	.name                   = "tc-dwc-g210-pltfm",
	.link_startup_notअगरy	= ufshcd_dwc_link_startup_notअगरy,
	.phy_initialization = tc_dwc_g210_config_40_bit,
पूर्ण;

अटल स्थिर काष्ठा of_device_id tc_dwc_g210_pltfm_match[] = अणु
	अणु
		.compatible = "snps,g210-tc-6.00-20bit",
		.data = &tc_dwc_g210_20bit_pltfm_hba_vops,
	पूर्ण,
	अणु
		.compatible = "snps,g210-tc-6.00-40bit",
		.data = &tc_dwc_g210_40bit_pltfm_hba_vops,
	पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, tc_dwc_g210_pltfm_match);

/**
 * tc_dwc_g210_pltfm_probe()
 * @pdev: poपूर्णांकer to platक्रमm device काष्ठाure
 *
 */
अटल पूर्णांक tc_dwc_g210_pltfm_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक err;
	स्थिर काष्ठा of_device_id *of_id;
	काष्ठा ufs_hba_variant_ops *vops;
	काष्ठा device *dev = &pdev->dev;

	of_id = of_match_node(tc_dwc_g210_pltfm_match, dev->of_node);
	vops = (काष्ठा ufs_hba_variant_ops *)of_id->data;

	/* Perक्रमm generic probe */
	err = ufshcd_pltfrm_init(pdev, vops);
	अगर (err)
		dev_err(dev, "ufshcd_pltfrm_init() failed %d\n", err);

	वापस err;
पूर्ण

/**
 * tc_dwc_g210_pltfm_हटाओ()
 * @pdev: poपूर्णांकer to platक्रमm device काष्ठाure
 *
 */
अटल पूर्णांक tc_dwc_g210_pltfm_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा ufs_hba *hba =  platक्रमm_get_drvdata(pdev);

	pm_runसमय_get_sync(&(pdev)->dev);
	ufshcd_हटाओ(hba);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops tc_dwc_g210_pltfm_pm_ops = अणु
	.suspend	= ufshcd_pltfrm_suspend,
	.resume		= ufshcd_pltfrm_resume,
	.runसमय_suspend = ufshcd_pltfrm_runसमय_suspend,
	.runसमय_resume  = ufshcd_pltfrm_runसमय_resume,
	.runसमय_idle    = ufshcd_pltfrm_runसमय_idle,
पूर्ण;

अटल काष्ठा platक्रमm_driver tc_dwc_g210_pltfm_driver = अणु
	.probe		= tc_dwc_g210_pltfm_probe,
	.हटाओ		= tc_dwc_g210_pltfm_हटाओ,
	.shutकरोwn = ufshcd_pltfrm_shutकरोwn,
	.driver		= अणु
		.name	= "tc-dwc-g210-pltfm",
		.pm	= &tc_dwc_g210_pltfm_pm_ops,
		.of_match_table	= of_match_ptr(tc_dwc_g210_pltfm_match),
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(tc_dwc_g210_pltfm_driver);

MODULE_ALIAS("platform:tc-dwc-g210-pltfm");
MODULE_DESCRIPTION("Synopsys Test Chip G210 platform glue driver");
MODULE_AUTHOR("Joao Pinto <Joao.Pinto@synopsys.com>");
MODULE_LICENSE("Dual BSD/GPL");
