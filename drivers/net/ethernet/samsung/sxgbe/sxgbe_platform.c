<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* 10G controller driver क्रम Samsung SoCs
 *
 * Copyright (C) 2013 Samsung Electronics Co., Ltd.
 *		http://www.samsung.com
 *
 * Author: Siva Reddy Kallam <siva.kallam@samsung.com>
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/etherdevice.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/of.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/of_net.h>
#समावेश <linux/phy.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/sxgbe_platक्रमm.h>

#समावेश "sxgbe_common.h"
#समावेश "sxgbe_reg.h"

#अगर_घोषित CONFIG_OF
अटल पूर्णांक sxgbe_probe_config_dt(काष्ठा platक्रमm_device *pdev,
				 काष्ठा sxgbe_plat_data *plat)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा sxgbe_dma_cfg *dma_cfg;
	पूर्णांक err;

	अगर (!np)
		वापस -ENODEV;

	err = of_get_phy_mode(np, &plat->पूर्णांकerface);
	अगर (err && err != -ENODEV)
		वापस err;

	plat->bus_id = of_alias_get_id(np, "ethernet");
	अगर (plat->bus_id < 0)
		plat->bus_id = 0;

	plat->mdio_bus_data = devm_kzalloc(&pdev->dev,
					   माप(*plat->mdio_bus_data),
					   GFP_KERNEL);
	अगर (!plat->mdio_bus_data)
		वापस -ENOMEM;

	dma_cfg = devm_kzalloc(&pdev->dev, माप(*dma_cfg), GFP_KERNEL);
	अगर (!dma_cfg)
		वापस -ENOMEM;

	plat->dma_cfg = dma_cfg;
	of_property_पढ़ो_u32(np, "samsung,pbl", &dma_cfg->pbl);
	अगर (of_property_पढ़ो_u32(np, "samsung,burst-map", &dma_cfg->burst_map) == 0)
		dma_cfg->fixed_burst = true;

	वापस 0;
पूर्ण
#अन्यथा
अटल पूर्णांक sxgbe_probe_config_dt(काष्ठा platक्रमm_device *pdev,
				 काष्ठा sxgbe_plat_data *plat)
अणु
	वापस -ENOSYS;
पूर्ण
#पूर्ण_अगर /* CONFIG_OF */

/**
 * sxgbe_platक्रमm_probe
 * @pdev: platक्रमm device poपूर्णांकer
 * Description: platक्रमm_device probe function. It allocates
 * the necessary resources and invokes the मुख्य to init
 * the net device, रेजिस्टर the mdio bus etc.
 */
अटल पूर्णांक sxgbe_platक्रमm_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक ret;
	पूर्णांक i, chan;
	काष्ठा device *dev = &pdev->dev;
	व्योम __iomem *addr;
	काष्ठा sxgbe_priv_data *priv = शून्य;
	काष्ठा sxgbe_plat_data *plat_dat = शून्य;
	काष्ठा net_device *ndev = platक्रमm_get_drvdata(pdev);
	काष्ठा device_node *node = dev->of_node;

	/* Get memory resource */
	addr = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(addr))
		वापस PTR_ERR(addr);

	अगर (pdev->dev.of_node) अणु
		plat_dat = devm_kzalloc(&pdev->dev,
					माप(काष्ठा sxgbe_plat_data),
					GFP_KERNEL);
		अगर (!plat_dat)
			वापस  -ENOMEM;

		ret = sxgbe_probe_config_dt(pdev, plat_dat);
		अगर (ret) अणु
			pr_err("%s: main dt probe failed\n", __func__);
			वापस ret;
		पूर्ण
	पूर्ण

	priv = sxgbe_drv_probe(&(pdev->dev), plat_dat, addr);
	अगर (!priv) अणु
		pr_err("%s: main driver probe failed\n", __func__);
		जाओ err_out;
	पूर्ण

	/* Get the SXGBE common INT inक्रमmation */
	priv->irq  = irq_of_parse_and_map(node, 0);
	अगर (priv->irq <= 0) अणु
		dev_err(dev, "sxgbe common irq parsing failed\n");
		जाओ err_drv_हटाओ;
	पूर्ण

	/* Get MAC address अगर available (DT) */
	of_get_mac_address(node, priv->dev->dev_addr);

	/* Get the TX/RX IRQ numbers */
	क्रम (i = 0, chan = 1; i < SXGBE_TX_QUEUES; i++) अणु
		priv->txq[i]->irq_no = irq_of_parse_and_map(node, chan++);
		अगर (priv->txq[i]->irq_no <= 0) अणु
			dev_err(dev, "sxgbe tx irq parsing failed\n");
			जाओ err_tx_irq_unmap;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < SXGBE_RX_QUEUES; i++) अणु
		priv->rxq[i]->irq_no = irq_of_parse_and_map(node, chan++);
		अगर (priv->rxq[i]->irq_no <= 0) अणु
			dev_err(dev, "sxgbe rx irq parsing failed\n");
			जाओ err_rx_irq_unmap;
		पूर्ण
	पूर्ण

	priv->lpi_irq = irq_of_parse_and_map(node, chan);
	अगर (priv->lpi_irq <= 0) अणु
		dev_err(dev, "sxgbe lpi irq parsing failed\n");
		जाओ err_rx_irq_unmap;
	पूर्ण

	platक्रमm_set_drvdata(pdev, priv->dev);

	pr_debug("platform driver registration completed\n");

	वापस 0;

err_rx_irq_unmap:
	जबतक (i--)
		irq_dispose_mapping(priv->rxq[i]->irq_no);
	i = SXGBE_TX_QUEUES;
err_tx_irq_unmap:
	जबतक (i--)
		irq_dispose_mapping(priv->txq[i]->irq_no);
	irq_dispose_mapping(priv->irq);
err_drv_हटाओ:
	sxgbe_drv_हटाओ(ndev);
err_out:
	वापस -ENODEV;
पूर्ण

/**
 * sxgbe_platक्रमm_हटाओ
 * @pdev: platक्रमm device poपूर्णांकer
 * Description: this function calls the मुख्य to मुक्त the net resources
 * and calls the platक्रमms hook and release the resources (e.g. mem).
 */
अटल पूर्णांक sxgbe_platक्रमm_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा net_device *ndev = platक्रमm_get_drvdata(pdev);
	पूर्णांक ret = sxgbe_drv_हटाओ(ndev);

	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक sxgbe_platक्रमm_suspend(काष्ठा device *dev)
अणु
	काष्ठा net_device *ndev = dev_get_drvdata(dev);

	वापस sxgbe_suspend(ndev);
पूर्ण

अटल पूर्णांक sxgbe_platक्रमm_resume(काष्ठा device *dev)
अणु
	काष्ठा net_device *ndev = dev_get_drvdata(dev);

	वापस sxgbe_resume(ndev);
पूर्ण

अटल पूर्णांक sxgbe_platक्रमm_मुक्तze(काष्ठा device *dev)
अणु
	काष्ठा net_device *ndev = dev_get_drvdata(dev);

	वापस sxgbe_मुक्तze(ndev);
पूर्ण

अटल पूर्णांक sxgbe_platक्रमm_restore(काष्ठा device *dev)
अणु
	काष्ठा net_device *ndev = dev_get_drvdata(dev);

	वापस sxgbe_restore(ndev);
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops sxgbe_platक्रमm_pm_ops = अणु
	.suspend	= sxgbe_platक्रमm_suspend,
	.resume		= sxgbe_platक्रमm_resume,
	.मुक्तze		= sxgbe_platक्रमm_मुक्तze,
	.thaw		= sxgbe_platक्रमm_restore,
	.restore	= sxgbe_platक्रमm_restore,
पूर्ण;
#अन्यथा
अटल स्थिर काष्ठा dev_pm_ops sxgbe_platक्रमm_pm_ops;
#पूर्ण_अगर /* CONFIG_PM */

अटल स्थिर काष्ठा of_device_id sxgbe_dt_ids[] = अणु
	अणु .compatible = "samsung,sxgbe-v2.0a"पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, sxgbe_dt_ids);

अटल काष्ठा platक्रमm_driver sxgbe_platक्रमm_driver = अणु
	.probe	= sxgbe_platक्रमm_probe,
	.हटाओ	= sxgbe_platक्रमm_हटाओ,
	.driver	= अणु
		.name		= SXGBE_RESOURCE_NAME,
		.pm		= &sxgbe_platक्रमm_pm_ops,
		.of_match_table	= of_match_ptr(sxgbe_dt_ids),
	पूर्ण,
पूर्ण;

पूर्णांक sxgbe_रेजिस्टर_platक्रमm(व्योम)
अणु
	पूर्णांक err;

	err = platक्रमm_driver_रेजिस्टर(&sxgbe_platक्रमm_driver);
	अगर (err)
		pr_err("failed to register the platform driver\n");

	वापस err;
पूर्ण

व्योम sxgbe_unरेजिस्टर_platक्रमm(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&sxgbe_platक्रमm_driver);
पूर्ण
