<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2010 Marvell International Ltd.
 *		Zhangfei Gao <zhangfei.gao@marvell.com>
 *		Kevin Wang <dwang4@marvell.com>
 *		Jun Nie <njun@marvell.com>
 *		Qiming Wu <wuqm@marvell.com>
 *		Philip Rakity <prakity@marvell.com>
 */

#समावेश <linux/err.h>
#समावेश <linux/init.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/clk.h>
#समावेश <linux/module.h>
#समावेश <linux/पन.स>
#समावेश <linux/mmc/card.h>
#समावेश <linux/mmc/host.h>
#समावेश <linux/platक्रमm_data/pxa_sdhci.h>
#समावेश <linux/slab.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>

#समावेश "sdhci.h"
#समावेश "sdhci-pltfm.h"

#घोषणा SD_FIFO_PARAM		0xe0
#घोषणा DIS_PAD_SD_CLK_GATE	0x0400 /* Turn on/off Dynamic SD Clock Gating */
#घोषणा CLK_GATE_ON		0x0200 /* Disable/enable Clock Gate */
#घोषणा CLK_GATE_CTL		0x0100 /* Clock Gate Control */
#घोषणा CLK_GATE_SETTING_BITS	(DIS_PAD_SD_CLK_GATE | \
		CLK_GATE_ON | CLK_GATE_CTL)

#घोषणा SD_CLOCK_BURST_SIZE_SETUP	0xe6
#घोषणा SDCLK_SEL_SHIFT		8
#घोषणा SDCLK_SEL_MASK		0x3
#घोषणा SDCLK_DELAY_SHIFT	10
#घोषणा SDCLK_DELAY_MASK	0x3c

#घोषणा SD_CE_ATA_2		0xea
#घोषणा MMC_CARD		0x1000
#घोषणा MMC_WIDTH		0x0100

अटल व्योम pxav2_reset(काष्ठा sdhci_host *host, u8 mask)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(mmc_dev(host->mmc));
	काष्ठा sdhci_pxa_platdata *pdata = pdev->dev.platक्रमm_data;

	sdhci_reset(host, mask);

	अगर (mask == SDHCI_RESET_ALL) अणु
		u16 पंचांगp = 0;

		/*
		 * tune timing of पढ़ो data/command when crc error happen
		 * no perक्रमmance impact
		 */
		अगर (pdata && pdata->clk_delay_sel == 1) अणु
			पंचांगp = पढ़ोw(host->ioaddr + SD_CLOCK_BURST_SIZE_SETUP);

			पंचांगp &= ~(SDCLK_DELAY_MASK << SDCLK_DELAY_SHIFT);
			पंचांगp |= (pdata->clk_delay_cycles & SDCLK_DELAY_MASK)
				<< SDCLK_DELAY_SHIFT;
			पंचांगp &= ~(SDCLK_SEL_MASK << SDCLK_SEL_SHIFT);
			पंचांगp |= (1 & SDCLK_SEL_MASK) << SDCLK_SEL_SHIFT;

			ग_लिखोw(पंचांगp, host->ioaddr + SD_CLOCK_BURST_SIZE_SETUP);
		पूर्ण

		अगर (pdata && (pdata->flags & PXA_FLAG_ENABLE_CLOCK_GATING)) अणु
			पंचांगp = पढ़ोw(host->ioaddr + SD_FIFO_PARAM);
			पंचांगp &= ~CLK_GATE_SETTING_BITS;
			ग_लिखोw(पंचांगp, host->ioaddr + SD_FIFO_PARAM);
		पूर्ण अन्यथा अणु
			पंचांगp = पढ़ोw(host->ioaddr + SD_FIFO_PARAM);
			पंचांगp &= ~CLK_GATE_SETTING_BITS;
			पंचांगp |= CLK_GATE_SETTING_BITS;
			ग_लिखोw(पंचांगp, host->ioaddr + SD_FIFO_PARAM);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम pxav2_mmc_set_bus_width(काष्ठा sdhci_host *host, पूर्णांक width)
अणु
	u8 ctrl;
	u16 पंचांगp;

	ctrl = पढ़ोb(host->ioaddr + SDHCI_HOST_CONTROL);
	पंचांगp = पढ़ोw(host->ioaddr + SD_CE_ATA_2);
	अगर (width == MMC_BUS_WIDTH_8) अणु
		ctrl &= ~SDHCI_CTRL_4BITBUS;
		पंचांगp |= MMC_CARD | MMC_WIDTH;
	पूर्ण अन्यथा अणु
		पंचांगp &= ~(MMC_CARD | MMC_WIDTH);
		अगर (width == MMC_BUS_WIDTH_4)
			ctrl |= SDHCI_CTRL_4BITBUS;
		अन्यथा
			ctrl &= ~SDHCI_CTRL_4BITBUS;
	पूर्ण
	ग_लिखोw(पंचांगp, host->ioaddr + SD_CE_ATA_2);
	ग_लिखोb(ctrl, host->ioaddr + SDHCI_HOST_CONTROL);
पूर्ण

अटल स्थिर काष्ठा sdhci_ops pxav2_sdhci_ops = अणु
	.set_घड़ी     = sdhci_set_घड़ी,
	.get_max_घड़ी = sdhci_pltfm_clk_get_max_घड़ी,
	.set_bus_width = pxav2_mmc_set_bus_width,
	.reset         = pxav2_reset,
	.set_uhs_संकेतing = sdhci_set_uhs_संकेतing,
पूर्ण;

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id sdhci_pxav2_of_match[] = अणु
	अणु
		.compatible = "mrvl,pxav2-mmc",
	पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, sdhci_pxav2_of_match);

अटल काष्ठा sdhci_pxa_platdata *pxav2_get_mmc_pdata(काष्ठा device *dev)
अणु
	काष्ठा sdhci_pxa_platdata *pdata;
	काष्ठा device_node *np = dev->of_node;
	u32 bus_width;
	u32 clk_delay_cycles;

	pdata = devm_kzalloc(dev, माप(*pdata), GFP_KERNEL);
	अगर (!pdata)
		वापस शून्य;

	अगर (of_find_property(np, "non-removable", शून्य))
		pdata->flags |= PXA_FLAG_CARD_PERMANENT;

	of_property_पढ़ो_u32(np, "bus-width", &bus_width);
	अगर (bus_width == 8)
		pdata->flags |= PXA_FLAG_SD_8_BIT_CAPABLE_SLOT;

	of_property_पढ़ो_u32(np, "mrvl,clk-delay-cycles", &clk_delay_cycles);
	अगर (clk_delay_cycles > 0) अणु
		pdata->clk_delay_sel = 1;
		pdata->clk_delay_cycles = clk_delay_cycles;
	पूर्ण

	वापस pdata;
पूर्ण
#अन्यथा
अटल अंतरभूत काष्ठा sdhci_pxa_platdata *pxav2_get_mmc_pdata(काष्ठा device *dev)
अणु
	वापस शून्य;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक sdhci_pxav2_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sdhci_pltfm_host *pltfm_host;
	काष्ठा sdhci_pxa_platdata *pdata = pdev->dev.platक्रमm_data;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा sdhci_host *host = शून्य;
	स्थिर काष्ठा of_device_id *match;

	पूर्णांक ret;
	काष्ठा clk *clk;

	host = sdhci_pltfm_init(pdev, शून्य, 0);
	अगर (IS_ERR(host))
		वापस PTR_ERR(host);

	pltfm_host = sdhci_priv(host);

	clk = devm_clk_get(dev, "PXA-SDHCLK");
	अगर (IS_ERR(clk)) अणु
		dev_err(dev, "failed to get io clock\n");
		ret = PTR_ERR(clk);
		जाओ मुक्त;
	पूर्ण
	pltfm_host->clk = clk;
	ret = clk_prepare_enable(clk);
	अगर (ret) अणु
		dev_err(&pdev->dev, "failed to enable io clock\n");
		जाओ मुक्त;
	पूर्ण

	host->quirks = SDHCI_QUIRK_BROKEN_ADMA
		| SDHCI_QUIRK_BROKEN_TIMEOUT_VAL
		| SDHCI_QUIRK_CAP_CLOCK_BASE_BROKEN;

	match = of_match_device(of_match_ptr(sdhci_pxav2_of_match), &pdev->dev);
	अगर (match) अणु
		pdata = pxav2_get_mmc_pdata(dev);
	पूर्ण
	अगर (pdata) अणु
		अगर (pdata->flags & PXA_FLAG_CARD_PERMANENT) अणु
			/* on-chip device */
			host->quirks |= SDHCI_QUIRK_BROKEN_CARD_DETECTION;
			host->mmc->caps |= MMC_CAP_NONREMOVABLE;
		पूर्ण

		/* If slot design supports 8 bit data, indicate this to MMC. */
		अगर (pdata->flags & PXA_FLAG_SD_8_BIT_CAPABLE_SLOT)
			host->mmc->caps |= MMC_CAP_8_BIT_DATA;

		अगर (pdata->quirks)
			host->quirks |= pdata->quirks;
		अगर (pdata->host_caps)
			host->mmc->caps |= pdata->host_caps;
		अगर (pdata->pm_caps)
			host->mmc->pm_caps |= pdata->pm_caps;
	पूर्ण

	host->ops = &pxav2_sdhci_ops;

	ret = sdhci_add_host(host);
	अगर (ret)
		जाओ disable_clk;

	वापस 0;

disable_clk:
	clk_disable_unprepare(clk);
मुक्त:
	sdhci_pltfm_मुक्त(pdev);
	वापस ret;
पूर्ण

अटल काष्ठा platक्रमm_driver sdhci_pxav2_driver = अणु
	.driver		= अणु
		.name	= "sdhci-pxav2",
		.probe_type = PROBE_PREFER_ASYNCHRONOUS,
		.of_match_table = of_match_ptr(sdhci_pxav2_of_match),
		.pm	= &sdhci_pltfm_pmops,
	पूर्ण,
	.probe		= sdhci_pxav2_probe,
	.हटाओ		= sdhci_pltfm_unरेजिस्टर,
पूर्ण;

module_platक्रमm_driver(sdhci_pxav2_driver);

MODULE_DESCRIPTION("SDHCI driver for pxav2");
MODULE_AUTHOR("Marvell International Ltd.");
MODULE_LICENSE("GPL v2");

