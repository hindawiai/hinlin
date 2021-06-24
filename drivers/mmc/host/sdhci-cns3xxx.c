<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * SDHCI support क्रम CNS3xxx SoC
 *
 * Copyright 2008 Cavium Networks
 * Copyright 2010 MontaVista Software, LLC.
 *
 * Authors: Scott Shu
 *	    Anton Vorontsov <avorontsov@mvista.com>
 */

#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/mmc/host.h>
#समावेश <linux/module.h>
#समावेश "sdhci-pltfm.h"

अटल अचिन्हित पूर्णांक sdhci_cns3xxx_get_max_clk(काष्ठा sdhci_host *host)
अणु
	वापस 150000000;
पूर्ण

अटल व्योम sdhci_cns3xxx_set_घड़ी(काष्ठा sdhci_host *host, अचिन्हित पूर्णांक घड़ी)
अणु
	काष्ठा device *dev = mmc_dev(host->mmc);
	पूर्णांक भाग = 1;
	u16 clk;
	अचिन्हित दीर्घ समयout;

	host->mmc->actual_घड़ी = 0;

	sdhci_ग_लिखोw(host, 0, SDHCI_CLOCK_CONTROL);

	अगर (घड़ी == 0)
		वापस;

	जबतक (host->max_clk / भाग > घड़ी) अणु
		/*
		 * On CNS3xxx भागider grows linearly up to 4, and then
		 * exponentially up to 256.
		 */
		अगर (भाग < 4)
			भाग += 1;
		अन्यथा अगर (भाग < 256)
			भाग *= 2;
		अन्यथा
			अवरोध;
	पूर्ण

	dev_dbg(dev, "desired SD clock: %d, actual: %d\n",
		घड़ी, host->max_clk / भाग);

	/* Divide by 3 is special. */
	अगर (भाग != 3)
		भाग >>= 1;

	clk = भाग << SDHCI_DIVIDER_SHIFT;
	clk |= SDHCI_CLOCK_INT_EN;
	sdhci_ग_लिखोw(host, clk, SDHCI_CLOCK_CONTROL);

	समयout = 20;
	जबतक (!((clk = sdhci_पढ़ोw(host, SDHCI_CLOCK_CONTROL))
			& SDHCI_CLOCK_INT_STABLE)) अणु
		अगर (समयout == 0) अणु
			dev_warn(dev, "clock is unstable");
			अवरोध;
		पूर्ण
		समयout--;
		mdelay(1);
	पूर्ण

	clk |= SDHCI_CLOCK_CARD_EN;
	sdhci_ग_लिखोw(host, clk, SDHCI_CLOCK_CONTROL);
पूर्ण

अटल स्थिर काष्ठा sdhci_ops sdhci_cns3xxx_ops = अणु
	.get_max_घड़ी	= sdhci_cns3xxx_get_max_clk,
	.set_घड़ी	= sdhci_cns3xxx_set_घड़ी,
	.set_bus_width	= sdhci_set_bus_width,
	.reset          = sdhci_reset,
	.set_uhs_संकेतing = sdhci_set_uhs_संकेतing,
पूर्ण;

अटल स्थिर काष्ठा sdhci_pltfm_data sdhci_cns3xxx_pdata = अणु
	.ops = &sdhci_cns3xxx_ops,
	.quirks = SDHCI_QUIRK_BROKEN_DMA |
		  SDHCI_QUIRK_DATA_TIMEOUT_USES_SDCLK |
		  SDHCI_QUIRK_INVERTED_WRITE_PROTECT |
		  SDHCI_QUIRK_CAP_CLOCK_BASE_BROKEN |
		  SDHCI_QUIRK_BROKEN_TIMEOUT_VAL,
पूर्ण;

अटल पूर्णांक sdhci_cns3xxx_probe(काष्ठा platक्रमm_device *pdev)
अणु
	वापस sdhci_pltfm_रेजिस्टर(pdev, &sdhci_cns3xxx_pdata, 0);
पूर्ण

अटल काष्ठा platक्रमm_driver sdhci_cns3xxx_driver = अणु
	.driver		= अणु
		.name	= "sdhci-cns3xxx",
		.probe_type = PROBE_PREFER_ASYNCHRONOUS,
		.pm	= &sdhci_pltfm_pmops,
	पूर्ण,
	.probe		= sdhci_cns3xxx_probe,
	.हटाओ		= sdhci_pltfm_unरेजिस्टर,
पूर्ण;

module_platक्रमm_driver(sdhci_cns3xxx_driver);

MODULE_DESCRIPTION("SDHCI driver for CNS3xxx");
MODULE_AUTHOR("Scott Shu, "
	      "Anton Vorontsov <avorontsov@mvista.com>");
MODULE_LICENSE("GPL v2");
