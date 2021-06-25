<शैली गुरु>
/*
 * DWMAC glue क्रम NXP LPC18xx/LPC43xx Ethernet
 *
 * Copyright (C) 2015 Joachim Eastwood <manabian@gmail.com>
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2. This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#समावेश <linux/mfd/syscon.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_net.h>
#समावेश <linux/phy.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/sपंचांगmac.h>

#समावेश "stmmac_platform.h"

/* Register defines क्रम CREG syscon */
#घोषणा LPC18XX_CREG_CREG6			0x12c
# define LPC18XX_CREG_CREG6_ETHMODE_MASK	0x7
# define LPC18XX_CREG_CREG6_ETHMODE_MII		0x0
# define LPC18XX_CREG_CREG6_ETHMODE_RMII	0x4

अटल पूर्णांक lpc18xx_dwmac_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा plat_sपंचांगmacenet_data *plat_dat;
	काष्ठा sपंचांगmac_resources sपंचांगmac_res;
	काष्ठा regmap *reg;
	u8 ethmode;
	पूर्णांक ret;

	ret = sपंचांगmac_get_platक्रमm_resources(pdev, &sपंचांगmac_res);
	अगर (ret)
		वापस ret;

	plat_dat = sपंचांगmac_probe_config_dt(pdev, sपंचांगmac_res.mac);
	अगर (IS_ERR(plat_dat))
		वापस PTR_ERR(plat_dat);

	plat_dat->has_gmac = true;

	reg = syscon_regmap_lookup_by_compatible("nxp,lpc1850-creg");
	अगर (IS_ERR(reg)) अणु
		dev_err(&pdev->dev, "syscon lookup failed\n");
		ret = PTR_ERR(reg);
		जाओ err_हटाओ_config_dt;
	पूर्ण

	अगर (plat_dat->पूर्णांकerface == PHY_INTERFACE_MODE_MII) अणु
		ethmode = LPC18XX_CREG_CREG6_ETHMODE_MII;
	पूर्ण अन्यथा अगर (plat_dat->पूर्णांकerface == PHY_INTERFACE_MODE_RMII) अणु
		ethmode = LPC18XX_CREG_CREG6_ETHMODE_RMII;
	पूर्ण अन्यथा अणु
		dev_err(&pdev->dev, "Only MII and RMII mode supported\n");
		ret = -EINVAL;
		जाओ err_हटाओ_config_dt;
	पूर्ण

	regmap_update_bits(reg, LPC18XX_CREG_CREG6,
			   LPC18XX_CREG_CREG6_ETHMODE_MASK, ethmode);

	ret = sपंचांगmac_dvr_probe(&pdev->dev, plat_dat, &sपंचांगmac_res);
	अगर (ret)
		जाओ err_हटाओ_config_dt;

	वापस 0;

err_हटाओ_config_dt:
	sपंचांगmac_हटाओ_config_dt(pdev, plat_dat);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा of_device_id lpc18xx_dwmac_match[] = अणु
	अणु .compatible = "nxp,lpc1850-dwmac" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, lpc18xx_dwmac_match);

अटल काष्ठा platक्रमm_driver lpc18xx_dwmac_driver = अणु
	.probe  = lpc18xx_dwmac_probe,
	.हटाओ = sपंचांगmac_pltfr_हटाओ,
	.driver = अणु
		.name           = "lpc18xx-dwmac",
		.pm		= &sपंचांगmac_pltfr_pm_ops,
		.of_match_table = lpc18xx_dwmac_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(lpc18xx_dwmac_driver);

MODULE_AUTHOR("Joachim Eastwood <manabian@gmail.com>");
MODULE_DESCRIPTION("DWMAC glue for LPC18xx/43xx Ethernet");
MODULE_LICENSE("GPL v2");
