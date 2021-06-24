<शैली गुरु>
/*
 * Generic DWMAC platक्रमm driver
 *
 * Copyright (C) 2007-2011  STMicroelectronics Ltd
 * Copyright (C) 2015 Joachim Eastwood <manabian@gmail.com>
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2. This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश "stmmac.h"
#समावेश "stmmac_platform.h"

अटल पूर्णांक dwmac_generic_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा plat_sपंचांगmacenet_data *plat_dat;
	काष्ठा sपंचांगmac_resources sपंचांगmac_res;
	पूर्णांक ret;

	ret = sपंचांगmac_get_platक्रमm_resources(pdev, &sपंचांगmac_res);
	अगर (ret)
		वापस ret;

	अगर (pdev->dev.of_node) अणु
		plat_dat = sपंचांगmac_probe_config_dt(pdev, sपंचांगmac_res.mac);
		अगर (IS_ERR(plat_dat)) अणु
			dev_err(&pdev->dev, "dt configuration failed\n");
			वापस PTR_ERR(plat_dat);
		पूर्ण
	पूर्ण अन्यथा अणु
		plat_dat = dev_get_platdata(&pdev->dev);
		अगर (!plat_dat) अणु
			dev_err(&pdev->dev, "no platform data provided\n");
			वापस  -EINVAL;
		पूर्ण

		/* Set शेष value क्रम multicast hash bins */
		plat_dat->multicast_filter_bins = HASH_TABLE_SIZE;

		/* Set शेष value क्रम unicast filter entries */
		plat_dat->unicast_filter_entries = 1;
	पूर्ण

	/* Custom initialisation (अगर needed) */
	अगर (plat_dat->init) अणु
		ret = plat_dat->init(pdev, plat_dat->bsp_priv);
		अगर (ret)
			जाओ err_हटाओ_config_dt;
	पूर्ण

	ret = sपंचांगmac_dvr_probe(&pdev->dev, plat_dat, &sपंचांगmac_res);
	अगर (ret)
		जाओ err_निकास;

	वापस 0;

err_निकास:
	अगर (plat_dat->निकास)
		plat_dat->निकास(pdev, plat_dat->bsp_priv);
err_हटाओ_config_dt:
	अगर (pdev->dev.of_node)
		sपंचांगmac_हटाओ_config_dt(pdev, plat_dat);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा of_device_id dwmac_generic_match[] = अणु
	अणु .compatible = "st,spear600-gmac"पूर्ण,
	अणु .compatible = "snps,dwmac-3.50a"पूर्ण,
	अणु .compatible = "snps,dwmac-3.610"पूर्ण,
	अणु .compatible = "snps,dwmac-3.70a"पूर्ण,
	अणु .compatible = "snps,dwmac-3.710"पूर्ण,
	अणु .compatible = "snps,dwmac-4.00"पूर्ण,
	अणु .compatible = "snps,dwmac-4.10a"पूर्ण,
	अणु .compatible = "snps,dwmac"पूर्ण,
	अणु .compatible = "snps,dwxgmac-2.10"पूर्ण,
	अणु .compatible = "snps,dwxgmac"पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, dwmac_generic_match);

अटल काष्ठा platक्रमm_driver dwmac_generic_driver = अणु
	.probe  = dwmac_generic_probe,
	.हटाओ = sपंचांगmac_pltfr_हटाओ,
	.driver = अणु
		.name           = STMMAC_RESOURCE_NAME,
		.pm		= &sपंचांगmac_pltfr_pm_ops,
		.of_match_table = of_match_ptr(dwmac_generic_match),
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(dwmac_generic_driver);

MODULE_DESCRIPTION("Generic dwmac driver");
MODULE_LICENSE("GPL v2");
