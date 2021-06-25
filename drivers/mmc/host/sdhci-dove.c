<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * sdhci-करोve.c Support क्रम SDHCI on Marvell's Dove SoC
 *
 * Author: Saeed Bishara <saeed@marvell.com>
 *	   Mike Rapoport <mike@compulab.co.il>
 * Based on sdhci-cns3xxx.c
 */

#समावेश <linux/clk.h>
#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/mmc/host.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>

#समावेश "sdhci-pltfm.h"

अटल u16 sdhci_करोve_पढ़ोw(काष्ठा sdhci_host *host, पूर्णांक reg)
अणु
	u16 ret;

	चयन (reg) अणु
	हाल SDHCI_HOST_VERSION:
	हाल SDHCI_SLOT_INT_STATUS:
		/* those रेजिस्टरs करोn't exist */
		वापस 0;
	शेष:
		ret = पढ़ोw(host->ioaddr + reg);
	पूर्ण
	वापस ret;
पूर्ण

अटल u32 sdhci_करोve_पढ़ोl(काष्ठा sdhci_host *host, पूर्णांक reg)
अणु
	u32 ret;

	ret = पढ़ोl(host->ioaddr + reg);

	चयन (reg) अणु
	हाल SDHCI_CAPABILITIES:
		/* Mask the support क्रम 3.0V */
		ret &= ~SDHCI_CAN_VDD_300;
		अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा sdhci_ops sdhci_करोve_ops = अणु
	.पढ़ो_w	= sdhci_करोve_पढ़ोw,
	.पढ़ो_l	= sdhci_करोve_पढ़ोl,
	.set_घड़ी = sdhci_set_घड़ी,
	.set_bus_width = sdhci_set_bus_width,
	.reset = sdhci_reset,
	.set_uhs_संकेतing = sdhci_set_uhs_संकेतing,
पूर्ण;

अटल स्थिर काष्ठा sdhci_pltfm_data sdhci_करोve_pdata = अणु
	.ops	= &sdhci_करोve_ops,
	.quirks	= SDHCI_QUIRK_NO_SIMULT_VDD_AND_POWER |
		  SDHCI_QUIRK_NO_BUSY_IRQ |
		  SDHCI_QUIRK_BROKEN_TIMEOUT_VAL |
		  SDHCI_QUIRK_FORCE_DMA |
		  SDHCI_QUIRK_NO_HISPD_BIT,
पूर्ण;

अटल पूर्णांक sdhci_करोve_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sdhci_host *host;
	काष्ठा sdhci_pltfm_host *pltfm_host;
	पूर्णांक ret;

	host = sdhci_pltfm_init(pdev, &sdhci_करोve_pdata, 0);
	अगर (IS_ERR(host))
		वापस PTR_ERR(host);

	pltfm_host = sdhci_priv(host);
	pltfm_host->clk = devm_clk_get(&pdev->dev, शून्य);

	अगर (!IS_ERR(pltfm_host->clk))
		clk_prepare_enable(pltfm_host->clk);

	ret = mmc_of_parse(host->mmc);
	अगर (ret)
		जाओ err_sdhci_add;

	ret = sdhci_add_host(host);
	अगर (ret)
		जाओ err_sdhci_add;

	वापस 0;

err_sdhci_add:
	clk_disable_unprepare(pltfm_host->clk);
	sdhci_pltfm_मुक्त(pdev);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा of_device_id sdhci_करोve_of_match_table[] = अणु
	अणु .compatible = "marvell,dove-sdhci", पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, sdhci_करोve_of_match_table);

अटल काष्ठा platक्रमm_driver sdhci_करोve_driver = अणु
	.driver		= अणु
		.name	= "sdhci-dove",
		.probe_type = PROBE_PREFER_ASYNCHRONOUS,
		.pm	= &sdhci_pltfm_pmops,
		.of_match_table = sdhci_करोve_of_match_table,
	पूर्ण,
	.probe		= sdhci_करोve_probe,
	.हटाओ		= sdhci_pltfm_unरेजिस्टर,
पूर्ण;

module_platक्रमm_driver(sdhci_करोve_driver);

MODULE_DESCRIPTION("SDHCI driver for Dove");
MODULE_AUTHOR("Saeed Bishara <saeed@marvell.com>, "
	      "Mike Rapoport <mike@compulab.co.il>");
MODULE_LICENSE("GPL v2");
