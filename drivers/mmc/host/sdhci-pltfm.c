<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * sdhci-pltfm.c Support क्रम SDHCI platक्रमm devices
 * Copyright (c) 2009 Intel Corporation
 *
 * Copyright (c) 2007, 2011 Freescale Semiconductor, Inc.
 * Copyright (c) 2009 MontaVista Software, Inc.
 *
 * Authors: Xiaobo Xie <X.Xie@मुक्तscale.com>
 *	    Anton Vorontsov <avorontsov@ru.mvista.com>
 */

/* Supports:
 * SDHCI platक्रमm devices
 *
 * Inspired by sdhci-pci.c, by Pierre Ossman
 */

#समावेश <linux/err.h>
#समावेश <linux/module.h>
#समावेश <linux/property.h>
#समावेश <linux/of.h>
#अगर_घोषित CONFIG_PPC
#समावेश <यंत्र/machdep.h>
#पूर्ण_अगर
#समावेश "sdhci-pltfm.h"

अचिन्हित पूर्णांक sdhci_pltfm_clk_get_max_घड़ी(काष्ठा sdhci_host *host)
अणु
	काष्ठा sdhci_pltfm_host *pltfm_host = sdhci_priv(host);

	वापस clk_get_rate(pltfm_host->clk);
पूर्ण
EXPORT_SYMBOL_GPL(sdhci_pltfm_clk_get_max_घड़ी);

अटल स्थिर काष्ठा sdhci_ops sdhci_pltfm_ops = अणु
	.set_घड़ी = sdhci_set_घड़ी,
	.set_bus_width = sdhci_set_bus_width,
	.reset = sdhci_reset,
	.set_uhs_संकेतing = sdhci_set_uhs_संकेतing,
पूर्ण;

अटल bool sdhci_wp_inverted(काष्ठा device *dev)
अणु
	अगर (device_property_present(dev, "sdhci,wp-inverted") ||
	    device_property_present(dev, "wp-inverted"))
		वापस true;

	/* Old device trees करोn't have the wp-inverted property. */
#अगर_घोषित CONFIG_PPC
	वापस machine_is(mpc837x_rdb) || machine_is(mpc837x_mds);
#अन्यथा
	वापस false;
#पूर्ण_अगर /* CONFIG_PPC */
पूर्ण

#अगर_घोषित CONFIG_OF
अटल व्योम sdhci_get_compatibility(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sdhci_host *host = platक्रमm_get_drvdata(pdev);
	काष्ठा device_node *np = pdev->dev.of_node;

	अगर (!np)
		वापस;

	अगर (of_device_is_compatible(np, "fsl,p2020-rev1-esdhc"))
		host->quirks |= SDHCI_QUIRK_BROKEN_DMA;

	अगर (of_device_is_compatible(np, "fsl,p2020-esdhc") ||
	    of_device_is_compatible(np, "fsl,p1010-esdhc") ||
	    of_device_is_compatible(np, "fsl,t4240-esdhc") ||
	    of_device_is_compatible(np, "fsl,mpc8536-esdhc"))
		host->quirks |= SDHCI_QUIRK_BROKEN_TIMEOUT_VAL;
पूर्ण
#अन्यथा
व्योम sdhci_get_compatibility(काष्ठा platक्रमm_device *pdev) अणुपूर्ण
#पूर्ण_अगर /* CONFIG_OF */

व्योम sdhci_get_property(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा sdhci_host *host = platक्रमm_get_drvdata(pdev);
	काष्ठा sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	u32 bus_width;

	अगर (device_property_present(dev, "sdhci,auto-cmd12"))
		host->quirks |= SDHCI_QUIRK_MULTIBLOCK_READ_ACMD12;

	अगर (device_property_present(dev, "sdhci,1-bit-only") ||
	    (device_property_पढ़ो_u32(dev, "bus-width", &bus_width) == 0 &&
	    bus_width == 1))
		host->quirks |= SDHCI_QUIRK_FORCE_1_BIT_DATA;

	अगर (sdhci_wp_inverted(dev))
		host->quirks |= SDHCI_QUIRK_INVERTED_WRITE_PROTECT;

	अगर (device_property_present(dev, "broken-cd"))
		host->quirks |= SDHCI_QUIRK_BROKEN_CARD_DETECTION;

	अगर (device_property_present(dev, "no-1-8-v"))
		host->quirks2 |= SDHCI_QUIRK2_NO_1_8_V;

	sdhci_get_compatibility(pdev);

	device_property_पढ़ो_u32(dev, "clock-frequency", &pltfm_host->घड़ी);

	अगर (device_property_present(dev, "keep-power-in-suspend"))
		host->mmc->pm_caps |= MMC_PM_KEEP_POWER;

	अगर (device_property_पढ़ो_bool(dev, "wakeup-source") ||
	    device_property_पढ़ो_bool(dev, "enable-sdio-wakeup")) /* legacy */
		host->mmc->pm_caps |= MMC_PM_WAKE_SDIO_IRQ;
पूर्ण
EXPORT_SYMBOL_GPL(sdhci_get_property);

काष्ठा sdhci_host *sdhci_pltfm_init(काष्ठा platक्रमm_device *pdev,
				    स्थिर काष्ठा sdhci_pltfm_data *pdata,
				    माप_प्रकार priv_size)
अणु
	काष्ठा sdhci_host *host;
	व्योम __iomem *ioaddr;
	पूर्णांक irq, ret;

	ioaddr = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(ioaddr)) अणु
		ret = PTR_ERR(ioaddr);
		जाओ err;
	पूर्ण

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0) अणु
		ret = irq;
		जाओ err;
	पूर्ण

	host = sdhci_alloc_host(&pdev->dev,
		माप(काष्ठा sdhci_pltfm_host) + priv_size);

	अगर (IS_ERR(host)) अणु
		ret = PTR_ERR(host);
		जाओ err;
	पूर्ण

	host->ioaddr = ioaddr;
	host->irq = irq;
	host->hw_name = dev_name(&pdev->dev);
	अगर (pdata && pdata->ops)
		host->ops = pdata->ops;
	अन्यथा
		host->ops = &sdhci_pltfm_ops;
	अगर (pdata) अणु
		host->quirks = pdata->quirks;
		host->quirks2 = pdata->quirks2;
	पूर्ण

	platक्रमm_set_drvdata(pdev, host);

	वापस host;
err:
	dev_err(&pdev->dev, "%s failed %d\n", __func__, ret);
	वापस ERR_PTR(ret);
पूर्ण
EXPORT_SYMBOL_GPL(sdhci_pltfm_init);

व्योम sdhci_pltfm_मुक्त(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sdhci_host *host = platक्रमm_get_drvdata(pdev);

	sdhci_मुक्त_host(host);
पूर्ण
EXPORT_SYMBOL_GPL(sdhci_pltfm_मुक्त);

पूर्णांक sdhci_pltfm_रेजिस्टर(काष्ठा platक्रमm_device *pdev,
			स्थिर काष्ठा sdhci_pltfm_data *pdata,
			माप_प्रकार priv_size)
अणु
	काष्ठा sdhci_host *host;
	पूर्णांक ret = 0;

	host = sdhci_pltfm_init(pdev, pdata, priv_size);
	अगर (IS_ERR(host))
		वापस PTR_ERR(host);

	sdhci_get_property(pdev);

	ret = sdhci_add_host(host);
	अगर (ret)
		sdhci_pltfm_मुक्त(pdev);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(sdhci_pltfm_रेजिस्टर);

पूर्णांक sdhci_pltfm_unरेजिस्टर(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sdhci_host *host = platक्रमm_get_drvdata(pdev);
	काष्ठा sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	पूर्णांक dead = (पढ़ोl(host->ioaddr + SDHCI_INT_STATUS) == 0xffffffff);

	sdhci_हटाओ_host(host, dead);
	clk_disable_unprepare(pltfm_host->clk);
	sdhci_pltfm_मुक्त(pdev);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(sdhci_pltfm_unरेजिस्टर);

#अगर_घोषित CONFIG_PM_SLEEP
पूर्णांक sdhci_pltfm_suspend(काष्ठा device *dev)
अणु
	काष्ठा sdhci_host *host = dev_get_drvdata(dev);
	काष्ठा sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	पूर्णांक ret;

	अगर (host->tuning_mode != SDHCI_TUNING_MODE_3)
		mmc_retune_needed(host->mmc);

	ret = sdhci_suspend_host(host);
	अगर (ret)
		वापस ret;

	clk_disable_unprepare(pltfm_host->clk);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(sdhci_pltfm_suspend);

पूर्णांक sdhci_pltfm_resume(काष्ठा device *dev)
अणु
	काष्ठा sdhci_host *host = dev_get_drvdata(dev);
	काष्ठा sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	पूर्णांक ret;

	ret = clk_prepare_enable(pltfm_host->clk);
	अगर (ret)
		वापस ret;

	ret = sdhci_resume_host(host);
	अगर (ret)
		clk_disable_unprepare(pltfm_host->clk);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(sdhci_pltfm_resume);
#पूर्ण_अगर

स्थिर काष्ठा dev_pm_ops sdhci_pltfm_pmops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(sdhci_pltfm_suspend, sdhci_pltfm_resume)
पूर्ण;
EXPORT_SYMBOL_GPL(sdhci_pltfm_pmops);

अटल पूर्णांक __init sdhci_pltfm_drv_init(व्योम)
अणु
	pr_info("sdhci-pltfm: SDHCI platform and OF driver helper\n");

	वापस 0;
पूर्ण
module_init(sdhci_pltfm_drv_init);

अटल व्योम __निकास sdhci_pltfm_drv_निकास(व्योम)
अणु
पूर्ण
module_निकास(sdhci_pltfm_drv_निकास);

MODULE_DESCRIPTION("SDHCI platform and OF driver helper");
MODULE_AUTHOR("Intel Corporation");
MODULE_LICENSE("GPL v2");
