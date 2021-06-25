<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * sdhci-brcmstb.c Support क्रम SDHCI on Broadcom BRCMSTB SoC's
 *
 * Copyright (C) 2015 Broadcom Corporation
 */

#समावेश <linux/पन.स>
#समावेश <linux/mmc/host.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/bitops.h>
#समावेश <linux/delay.h>

#समावेश "sdhci-pltfm.h"
#समावेश "cqhci.h"

#घोषणा SDHCI_VENDOR 0x78
#घोषणा  SDHCI_VENDOR_ENHANCED_STRB 0x1

#घोषणा BRCMSTB_PRIV_FLAGS_NO_64BIT		BIT(0)
#घोषणा BRCMSTB_PRIV_FLAGS_BROKEN_TIMEOUT	BIT(1)

#घोषणा SDHCI_ARASAN_CQE_BASE_ADDR		0x200

काष्ठा sdhci_brcmstb_priv अणु
	व्योम __iomem *cfg_regs;
	bool has_cqe;
पूर्ण;

काष्ठा brcmstb_match_priv अणु
	व्योम (*hs400es)(काष्ठा mmc_host *mmc, काष्ठा mmc_ios *ios);
	काष्ठा sdhci_ops *ops;
	अचिन्हित पूर्णांक flags;
पूर्ण;

अटल व्योम sdhci_brcmstb_hs400es(काष्ठा mmc_host *mmc, काष्ठा mmc_ios *ios)
अणु
	काष्ठा sdhci_host *host = mmc_priv(mmc);

	u32 reg;

	dev_dbg(mmc_dev(mmc), "%s(): Setting HS400-Enhanced-Strobe mode\n",
		__func__);
	reg = पढ़ोl(host->ioaddr + SDHCI_VENDOR);
	अगर (ios->enhanced_strobe)
		reg |= SDHCI_VENDOR_ENHANCED_STRB;
	अन्यथा
		reg &= ~SDHCI_VENDOR_ENHANCED_STRB;
	ग_लिखोl(reg, host->ioaddr + SDHCI_VENDOR);
पूर्ण

अटल व्योम sdhci_brcmstb_set_घड़ी(काष्ठा sdhci_host *host, अचिन्हित पूर्णांक घड़ी)
अणु
	u16 clk;

	host->mmc->actual_घड़ी = 0;

	clk = sdhci_calc_clk(host, घड़ी, &host->mmc->actual_घड़ी);
	sdhci_ग_लिखोw(host, clk, SDHCI_CLOCK_CONTROL);

	अगर (घड़ी == 0)
		वापस;

	sdhci_enable_clk(host, clk);
पूर्ण

अटल व्योम sdhci_brcmstb_set_uhs_संकेतing(काष्ठा sdhci_host *host,
					    अचिन्हित पूर्णांक timing)
अणु
	u16 ctrl_2;

	dev_dbg(mmc_dev(host->mmc), "%s: Setting UHS signaling for %d timing\n",
		__func__, timing);
	ctrl_2 = sdhci_पढ़ोw(host, SDHCI_HOST_CONTROL2);
	/* Select Bus Speed Mode क्रम host */
	ctrl_2 &= ~SDHCI_CTRL_UHS_MASK;
	अगर ((timing == MMC_TIMING_MMC_HS200) ||
	    (timing == MMC_TIMING_UHS_SDR104))
		ctrl_2 |= SDHCI_CTRL_UHS_SDR104;
	अन्यथा अगर (timing == MMC_TIMING_UHS_SDR12)
		ctrl_2 |= SDHCI_CTRL_UHS_SDR12;
	अन्यथा अगर (timing == MMC_TIMING_SD_HS ||
		 timing == MMC_TIMING_MMC_HS ||
		 timing == MMC_TIMING_UHS_SDR25)
		ctrl_2 |= SDHCI_CTRL_UHS_SDR25;
	अन्यथा अगर (timing == MMC_TIMING_UHS_SDR50)
		ctrl_2 |= SDHCI_CTRL_UHS_SDR50;
	अन्यथा अगर ((timing == MMC_TIMING_UHS_DDR50) ||
		 (timing == MMC_TIMING_MMC_DDR52))
		ctrl_2 |= SDHCI_CTRL_UHS_DDR50;
	अन्यथा अगर (timing == MMC_TIMING_MMC_HS400)
		ctrl_2 |= SDHCI_CTRL_HS400; /* Non-standard */
	sdhci_ग_लिखोw(host, ctrl_2, SDHCI_HOST_CONTROL2);
पूर्ण

अटल व्योम sdhci_brcmstb_dumpregs(काष्ठा mmc_host *mmc)
अणु
	sdhci_dumpregs(mmc_priv(mmc));
पूर्ण

अटल व्योम sdhci_brcmstb_cqe_enable(काष्ठा mmc_host *mmc)
अणु
	काष्ठा sdhci_host *host = mmc_priv(mmc);
	u32 reg;

	reg = sdhci_पढ़ोl(host, SDHCI_PRESENT_STATE);
	जबतक (reg & SDHCI_DATA_AVAILABLE) अणु
		sdhci_पढ़ोl(host, SDHCI_BUFFER);
		reg = sdhci_पढ़ोl(host, SDHCI_PRESENT_STATE);
	पूर्ण

	sdhci_cqe_enable(mmc);
पूर्ण

अटल स्थिर काष्ठा cqhci_host_ops sdhci_brcmstb_cqhci_ops = अणु
	.enable         = sdhci_brcmstb_cqe_enable,
	.disable        = sdhci_cqe_disable,
	.dumpregs       = sdhci_brcmstb_dumpregs,
पूर्ण;

अटल काष्ठा sdhci_ops sdhci_brcmstb_ops = अणु
	.set_घड़ी = sdhci_set_घड़ी,
	.set_bus_width = sdhci_set_bus_width,
	.reset = sdhci_reset,
	.set_uhs_संकेतing = sdhci_set_uhs_संकेतing,
पूर्ण;

अटल काष्ठा sdhci_ops sdhci_brcmstb_ops_7216 = अणु
	.set_घड़ी = sdhci_brcmstb_set_घड़ी,
	.set_bus_width = sdhci_set_bus_width,
	.reset = sdhci_reset,
	.set_uhs_संकेतing = sdhci_brcmstb_set_uhs_संकेतing,
पूर्ण;

अटल काष्ठा brcmstb_match_priv match_priv_7425 = अणु
	.flags = BRCMSTB_PRIV_FLAGS_NO_64BIT |
	BRCMSTB_PRIV_FLAGS_BROKEN_TIMEOUT,
	.ops = &sdhci_brcmstb_ops,
पूर्ण;

अटल काष्ठा brcmstb_match_priv match_priv_7445 = अणु
	.flags = BRCMSTB_PRIV_FLAGS_BROKEN_TIMEOUT,
	.ops = &sdhci_brcmstb_ops,
पूर्ण;

अटल स्थिर काष्ठा brcmstb_match_priv match_priv_7216 = अणु
	.hs400es = sdhci_brcmstb_hs400es,
	.ops = &sdhci_brcmstb_ops_7216,
पूर्ण;

अटल स्थिर काष्ठा of_device_id sdhci_brcm_of_match[] = अणु
	अणु .compatible = "brcm,bcm7425-sdhci", .data = &match_priv_7425 पूर्ण,
	अणु .compatible = "brcm,bcm7445-sdhci", .data = &match_priv_7445 पूर्ण,
	अणु .compatible = "brcm,bcm7216-sdhci", .data = &match_priv_7216 पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल u32 sdhci_brcmstb_cqhci_irq(काष्ठा sdhci_host *host, u32 पूर्णांकmask)
अणु
	पूर्णांक cmd_error = 0;
	पूर्णांक data_error = 0;

	अगर (!sdhci_cqe_irq(host, पूर्णांकmask, &cmd_error, &data_error))
		वापस पूर्णांकmask;

	cqhci_irq(host->mmc, पूर्णांकmask, cmd_error, data_error);

	वापस 0;
पूर्ण

अटल पूर्णांक sdhci_brcmstb_add_host(काष्ठा sdhci_host *host,
				  काष्ठा sdhci_brcmstb_priv *priv)
अणु
	काष्ठा cqhci_host *cq_host;
	bool dma64;
	पूर्णांक ret;

	अगर (!priv->has_cqe)
		वापस sdhci_add_host(host);

	dev_dbg(mmc_dev(host->mmc), "CQE is enabled\n");
	host->mmc->caps2 |= MMC_CAP2_CQE | MMC_CAP2_CQE_DCMD;
	ret = sdhci_setup_host(host);
	अगर (ret)
		वापस ret;

	cq_host = devm_kzalloc(mmc_dev(host->mmc),
			       माप(*cq_host), GFP_KERNEL);
	अगर (!cq_host) अणु
		ret = -ENOMEM;
		जाओ cleanup;
	पूर्ण

	cq_host->mmio = host->ioaddr + SDHCI_ARASAN_CQE_BASE_ADDR;
	cq_host->ops = &sdhci_brcmstb_cqhci_ops;

	dma64 = host->flags & SDHCI_USE_64_BIT_DMA;
	अगर (dma64) अणु
		dev_dbg(mmc_dev(host->mmc), "Using 64 bit DMA\n");
		cq_host->caps |= CQHCI_TASK_DESC_SZ_128;
	पूर्ण

	ret = cqhci_init(cq_host, host->mmc, dma64);
	अगर (ret)
		जाओ cleanup;

	ret = __sdhci_add_host(host);
	अगर (ret)
		जाओ cleanup;

	वापस 0;

cleanup:
	sdhci_cleanup_host(host);
	वापस ret;
पूर्ण

अटल पूर्णांक sdhci_brcmstb_probe(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा brcmstb_match_priv *match_priv;
	काष्ठा sdhci_pltfm_data brcmstb_pdata;
	काष्ठा sdhci_pltfm_host *pltfm_host;
	स्थिर काष्ठा of_device_id *match;
	काष्ठा sdhci_brcmstb_priv *priv;
	काष्ठा sdhci_host *host;
	काष्ठा resource *iomem;
	bool has_cqe = false;
	काष्ठा clk *clk;
	पूर्णांक res;

	match = of_match_node(sdhci_brcm_of_match, pdev->dev.of_node);
	match_priv = match->data;

	dev_dbg(&pdev->dev, "Probe found match for %s\n",  match->compatible);

	clk = devm_clk_get_optional(&pdev->dev, शून्य);
	अगर (IS_ERR(clk))
		वापस dev_err_probe(&pdev->dev, PTR_ERR(clk),
				     "Failed to get clock from Device Tree\n");

	res = clk_prepare_enable(clk);
	अगर (res)
		वापस res;

	स_रखो(&brcmstb_pdata, 0, माप(brcmstb_pdata));
	अगर (device_property_पढ़ो_bool(&pdev->dev, "supports-cqe")) अणु
		has_cqe = true;
		match_priv->ops->irq = sdhci_brcmstb_cqhci_irq;
	पूर्ण
	brcmstb_pdata.ops = match_priv->ops;
	host = sdhci_pltfm_init(pdev, &brcmstb_pdata,
				माप(काष्ठा sdhci_brcmstb_priv));
	अगर (IS_ERR(host)) अणु
		res = PTR_ERR(host);
		जाओ err_clk;
	पूर्ण

	pltfm_host = sdhci_priv(host);
	priv = sdhci_pltfm_priv(pltfm_host);
	priv->has_cqe = has_cqe;

	/* Map in the non-standard CFG रेजिस्टरs */
	iomem = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 1);
	priv->cfg_regs = devm_ioremap_resource(&pdev->dev, iomem);
	अगर (IS_ERR(priv->cfg_regs)) अणु
		res = PTR_ERR(priv->cfg_regs);
		जाओ err;
	पूर्ण

	sdhci_get_of_property(pdev);
	res = mmc_of_parse(host->mmc);
	अगर (res)
		जाओ err;

	/*
	 * If the chip has enhanced strobe and it's enabled, add
	 * callback
	 */
	अगर (match_priv->hs400es &&
	    (host->mmc->caps2 & MMC_CAP2_HS400_ES))
		host->mmc_host_ops.hs400_enhanced_strobe = match_priv->hs400es;

	/*
	 * Supply the existing CAPS, but clear the UHS modes. This
	 * will allow these modes to be specअगरied by device tree
	 * properties through mmc_of_parse().
	 */
	host->caps = sdhci_पढ़ोl(host, SDHCI_CAPABILITIES);
	अगर (match_priv->flags & BRCMSTB_PRIV_FLAGS_NO_64BIT)
		host->caps &= ~SDHCI_CAN_64BIT;
	host->caps1 = sdhci_पढ़ोl(host, SDHCI_CAPABILITIES_1);
	host->caps1 &= ~(SDHCI_SUPPORT_SDR50 | SDHCI_SUPPORT_SDR104 |
			 SDHCI_SUPPORT_DDR50);
	host->quirks |= SDHCI_QUIRK_MISSING_CAPS;

	अगर (match_priv->flags & BRCMSTB_PRIV_FLAGS_BROKEN_TIMEOUT)
		host->quirks |= SDHCI_QUIRK_BROKEN_TIMEOUT_VAL;

	res = sdhci_brcmstb_add_host(host, priv);
	अगर (res)
		जाओ err;

	pltfm_host->clk = clk;
	वापस res;

err:
	sdhci_pltfm_मुक्त(pdev);
err_clk:
	clk_disable_unprepare(clk);
	वापस res;
पूर्ण

अटल व्योम sdhci_brcmstb_shutकरोwn(काष्ठा platक्रमm_device *pdev)
अणु
	sdhci_pltfm_suspend(&pdev->dev);
पूर्ण

MODULE_DEVICE_TABLE(of, sdhci_brcm_of_match);

अटल काष्ठा platक्रमm_driver sdhci_brcmstb_driver = अणु
	.driver		= अणु
		.name	= "sdhci-brcmstb",
		.probe_type = PROBE_PREFER_ASYNCHRONOUS,
		.pm	= &sdhci_pltfm_pmops,
		.of_match_table = of_match_ptr(sdhci_brcm_of_match),
	पूर्ण,
	.probe		= sdhci_brcmstb_probe,
	.हटाओ		= sdhci_pltfm_unरेजिस्टर,
	.shutकरोwn	= sdhci_brcmstb_shutकरोwn,
पूर्ण;

module_platक्रमm_driver(sdhci_brcmstb_driver);

MODULE_DESCRIPTION("SDHCI driver for Broadcom BRCMSTB SoCs");
MODULE_AUTHOR("Broadcom");
MODULE_LICENSE("GPL v2");
