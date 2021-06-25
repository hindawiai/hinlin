<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Amlogic Meson6 and Meson8 DWMAC glue layer
 *
 * Copyright (C) 2014 Beniamino Galvani <b.galvani@gmail.com>
 */

#समावेश <linux/device.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/पन.स>
#समावेश <linux/ioport.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/sपंचांगmac.h>

#समावेश "stmmac_platform.h"

#घोषणा ETHMAC_SPEED_100	BIT(1)

काष्ठा meson_dwmac अणु
	काष्ठा device	*dev;
	व्योम __iomem	*reg;
पूर्ण;

अटल व्योम meson6_dwmac_fix_mac_speed(व्योम *priv, अचिन्हित पूर्णांक speed)
अणु
	काष्ठा meson_dwmac *dwmac = priv;
	अचिन्हित पूर्णांक val;

	val = पढ़ोl(dwmac->reg);

	चयन (speed) अणु
	हाल SPEED_10:
		val &= ~ETHMAC_SPEED_100;
		अवरोध;
	हाल SPEED_100:
		val |= ETHMAC_SPEED_100;
		अवरोध;
	पूर्ण

	ग_लिखोl(val, dwmac->reg);
पूर्ण

अटल पूर्णांक meson6_dwmac_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा plat_sपंचांगmacenet_data *plat_dat;
	काष्ठा sपंचांगmac_resources sपंचांगmac_res;
	काष्ठा meson_dwmac *dwmac;
	पूर्णांक ret;

	ret = sपंचांगmac_get_platक्रमm_resources(pdev, &sपंचांगmac_res);
	अगर (ret)
		वापस ret;

	plat_dat = sपंचांगmac_probe_config_dt(pdev, sपंचांगmac_res.mac);
	अगर (IS_ERR(plat_dat))
		वापस PTR_ERR(plat_dat);

	dwmac = devm_kzalloc(&pdev->dev, माप(*dwmac), GFP_KERNEL);
	अगर (!dwmac) अणु
		ret = -ENOMEM;
		जाओ err_हटाओ_config_dt;
	पूर्ण

	dwmac->reg = devm_platक्रमm_ioremap_resource(pdev, 1);
	अगर (IS_ERR(dwmac->reg)) अणु
		ret = PTR_ERR(dwmac->reg);
		जाओ err_हटाओ_config_dt;
	पूर्ण

	plat_dat->bsp_priv = dwmac;
	plat_dat->fix_mac_speed = meson6_dwmac_fix_mac_speed;

	ret = sपंचांगmac_dvr_probe(&pdev->dev, plat_dat, &sपंचांगmac_res);
	अगर (ret)
		जाओ err_हटाओ_config_dt;

	वापस 0;

err_हटाओ_config_dt:
	sपंचांगmac_हटाओ_config_dt(pdev, plat_dat);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा of_device_id meson6_dwmac_match[] = अणु
	अणु .compatible = "amlogic,meson6-dwmac" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, meson6_dwmac_match);

अटल काष्ठा platक्रमm_driver meson6_dwmac_driver = अणु
	.probe  = meson6_dwmac_probe,
	.हटाओ = sपंचांगmac_pltfr_हटाओ,
	.driver = अणु
		.name           = "meson6-dwmac",
		.pm		= &sपंचांगmac_pltfr_pm_ops,
		.of_match_table = meson6_dwmac_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(meson6_dwmac_driver);

MODULE_AUTHOR("Beniamino Galvani <b.galvani@gmail.com>");
MODULE_DESCRIPTION("Amlogic Meson6 and Meson8 DWMAC glue layer");
MODULE_LICENSE("GPL v2");
