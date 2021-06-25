<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/**
 * DOC: emac_arc.c - ARC EMAC specअगरic glue layer
 *
 * Copyright (C) 2014 Roमुख्य Perier
 *
 * Roमुख्य Perier  <roमुख्य.perier@gmail.com>
 */

#समावेश <linux/etherdevice.h>
#समावेश <linux/module.h>
#समावेश <linux/of_net.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश "emac.h"

#घोषणा DRV_NAME    "emac_arc"

अटल पूर्णांक emac_arc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा arc_emac_priv *priv;
	phy_पूर्णांकerface_t पूर्णांकerface;
	काष्ठा net_device *ndev;
	पूर्णांक err;

	अगर (!dev->of_node)
		वापस -ENODEV;

	ndev = alloc_etherdev(माप(काष्ठा arc_emac_priv));
	अगर (!ndev)
		वापस -ENOMEM;
	platक्रमm_set_drvdata(pdev, ndev);
	SET_NETDEV_DEV(ndev, dev);

	priv = netdev_priv(ndev);
	priv->drv_name = DRV_NAME;

	err = of_get_phy_mode(dev->of_node, &पूर्णांकerface);
	अगर (err) अणु
		अगर (err == -ENODEV)
			पूर्णांकerface = PHY_INTERFACE_MODE_MII;
		अन्यथा
			जाओ out_netdev;
	पूर्ण

	priv->clk = devm_clk_get(dev, "hclk");
	अगर (IS_ERR(priv->clk)) अणु
		dev_err(dev, "failed to retrieve host clock from device tree\n");
		err = -EINVAL;
		जाओ out_netdev;
	पूर्ण

	err = arc_emac_probe(ndev, पूर्णांकerface);
out_netdev:
	अगर (err)
		मुक्त_netdev(ndev);
	वापस err;
पूर्ण

अटल पूर्णांक emac_arc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा net_device *ndev = platक्रमm_get_drvdata(pdev);
	पूर्णांक err;

	err = arc_emac_हटाओ(ndev);
	मुक्त_netdev(ndev);
	वापस err;
पूर्ण

अटल स्थिर काष्ठा of_device_id emac_arc_dt_ids[] = अणु
	अणु .compatible = "snps,arc-emac" पूर्ण,
	अणु /* Sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, emac_arc_dt_ids);

अटल काष्ठा platक्रमm_driver emac_arc_driver = अणु
	.probe = emac_arc_probe,
	.हटाओ = emac_arc_हटाओ,
	.driver = अणु
		.name = DRV_NAME,
		.of_match_table  = emac_arc_dt_ids,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(emac_arc_driver);

MODULE_AUTHOR("Romain Perier <romain.perier@gmail.com>");
MODULE_DESCRIPTION("ARC EMAC platform driver");
MODULE_LICENSE("GPL");
