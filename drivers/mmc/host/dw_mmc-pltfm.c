<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Synopsys DesignWare Mulसमयdia Card Interface driver
 *
 * Copyright (C) 2009 NXP Semiconductors
 * Copyright (C) 2009, 2010 Imagination Technologies Ltd.
 */

#समावेश <linux/err.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/पन.स>
#समावेश <linux/irq.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/slab.h>
#समावेश <linux/mmc/host.h>
#समावेश <linux/mmc/mmc.h>
#समावेश <linux/of.h>
#समावेश <linux/clk.h>

#समावेश "dw_mmc.h"
#समावेश "dw_mmc-pltfm.h"

पूर्णांक dw_mci_pltfm_रेजिस्टर(काष्ठा platक्रमm_device *pdev,
			  स्थिर काष्ठा dw_mci_drv_data *drv_data)
अणु
	काष्ठा dw_mci *host;
	काष्ठा resource	*regs;

	host = devm_kzalloc(&pdev->dev, माप(काष्ठा dw_mci), GFP_KERNEL);
	अगर (!host)
		वापस -ENOMEM;

	host->irq = platक्रमm_get_irq(pdev, 0);
	अगर (host->irq < 0)
		वापस host->irq;

	host->drv_data = drv_data;
	host->dev = &pdev->dev;
	host->irq_flags = 0;
	host->pdata = pdev->dev.platक्रमm_data;

	regs = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	host->regs = devm_ioremap_resource(&pdev->dev, regs);
	अगर (IS_ERR(host->regs))
		वापस PTR_ERR(host->regs);

	/* Get रेजिस्टरs' physical base address */
	host->phy_regs = regs->start;

	platक्रमm_set_drvdata(pdev, host);
	वापस dw_mci_probe(host);
पूर्ण
EXPORT_SYMBOL_GPL(dw_mci_pltfm_रेजिस्टर);

स्थिर काष्ठा dev_pm_ops dw_mci_pltfm_pmops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(pm_runसमय_क्रमce_suspend,
				pm_runसमय_क्रमce_resume)
	SET_RUNTIME_PM_OPS(dw_mci_runसमय_suspend,
			   dw_mci_runसमय_resume,
			   शून्य)
पूर्ण;
EXPORT_SYMBOL_GPL(dw_mci_pltfm_pmops);

अटल स्थिर काष्ठा of_device_id dw_mci_pltfm_match[] = अणु
	अणु .compatible = "snps,dw-mshc", पूर्ण,
	अणु .compatible = "altr,socfpga-dw-mshc", पूर्ण,
	अणु .compatible = "img,pistachio-dw-mshc", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, dw_mci_pltfm_match);

अटल पूर्णांक dw_mci_pltfm_probe(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा dw_mci_drv_data *drv_data = शून्य;
	स्थिर काष्ठा of_device_id *match;

	अगर (pdev->dev.of_node) अणु
		match = of_match_node(dw_mci_pltfm_match, pdev->dev.of_node);
		drv_data = match->data;
	पूर्ण

	वापस dw_mci_pltfm_रेजिस्टर(pdev, drv_data);
पूर्ण

पूर्णांक dw_mci_pltfm_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा dw_mci *host = platक्रमm_get_drvdata(pdev);

	dw_mci_हटाओ(host);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(dw_mci_pltfm_हटाओ);

अटल काष्ठा platक्रमm_driver dw_mci_pltfm_driver = अणु
	.probe		= dw_mci_pltfm_probe,
	.हटाओ		= dw_mci_pltfm_हटाओ,
	.driver		= अणु
		.name		= "dw_mmc",
		.probe_type	= PROBE_PREFER_ASYNCHRONOUS,
		.of_match_table	= dw_mci_pltfm_match,
		.pm		= &dw_mci_pltfm_pmops,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(dw_mci_pltfm_driver);

MODULE_DESCRIPTION("DW Multimedia Card Interface driver");
MODULE_AUTHOR("NXP Semiconductor VietNam");
MODULE_AUTHOR("Imagination Technologies Ltd");
MODULE_LICENSE("GPL v2");
