<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Aपंचांगel SDMMC controller driver.
 *
 * Copyright (C) 2015 Aपंचांगel,
 *		 2015 Luकरोvic Desroches <luकरोvic.desroches@aपंचांगel.com>
 */

#समावेश <linux/bitfield.h>
#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/mmc/host.h>
#समावेश <linux/mmc/slot-gpपन.स>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/pm.h>
#समावेश <linux/pm_runसमय.स>

#समावेश "sdhci-pltfm.h"

#घोषणा SDMMC_MC1R	0x204
#घोषणा		SDMMC_MC1R_DDR		BIT(3)
#घोषणा		SDMMC_MC1R_FCD		BIT(7)
#घोषणा SDMMC_CACR	0x230
#घोषणा		SDMMC_CACR_CAPWREN	BIT(0)
#घोषणा		SDMMC_CACR_KEY		(0x46 << 8)
#घोषणा SDMMC_CALCR	0x240
#घोषणा		SDMMC_CALCR_EN		BIT(0)
#घोषणा		SDMMC_CALCR_ALWYSON	BIT(4)

#घोषणा SDHCI_AT91_PRESET_COMMON_CONF	0x400 /* drv type B, programmable घड़ी mode */

काष्ठा sdhci_at91_soc_data अणु
	स्थिर काष्ठा sdhci_pltfm_data *pdata;
	bool baseclk_is_generated_पूर्णांकernally;
	अचिन्हित पूर्णांक भागider_क्रम_baseclk;
पूर्ण;

काष्ठा sdhci_at91_priv अणु
	स्थिर काष्ठा sdhci_at91_soc_data *soc_data;
	काष्ठा clk *hघड़ी;
	काष्ठा clk *gck;
	काष्ठा clk *मुख्यck;
	bool restore_needed;
	bool cal_always_on;
पूर्ण;

अटल व्योम sdhci_at91_set_क्रमce_card_detect(काष्ठा sdhci_host *host)
अणु
	u8 mc1r;

	mc1r = पढ़ोb(host->ioaddr + SDMMC_MC1R);
	mc1r |= SDMMC_MC1R_FCD;
	ग_लिखोb(mc1r, host->ioaddr + SDMMC_MC1R);
पूर्ण

अटल व्योम sdhci_at91_set_घड़ी(काष्ठा sdhci_host *host, अचिन्हित पूर्णांक घड़ी)
अणु
	u16 clk;
	अचिन्हित दीर्घ समयout;

	host->mmc->actual_घड़ी = 0;

	/*
	 * There is no requirement to disable the पूर्णांकernal घड़ी beक्रमe
	 * changing the SD घड़ी configuration. Moreover, disabling the
	 * पूर्णांकernal घड़ी, changing the configuration and re-enabling the
	 * पूर्णांकernal घड़ी causes some bugs. It can prevent to get the पूर्णांकernal
	 * घड़ी stable flag पढ़ोy and an unexpected चयन to the base घड़ी
	 * when using presets.
	 */
	clk = sdhci_पढ़ोw(host, SDHCI_CLOCK_CONTROL);
	clk &= SDHCI_CLOCK_INT_EN;
	sdhci_ग_लिखोw(host, clk, SDHCI_CLOCK_CONTROL);

	अगर (घड़ी == 0)
		वापस;

	clk = sdhci_calc_clk(host, घड़ी, &host->mmc->actual_घड़ी);

	clk |= SDHCI_CLOCK_INT_EN;
	sdhci_ग_लिखोw(host, clk, SDHCI_CLOCK_CONTROL);

	/* Wait max 20 ms */
	समयout = 20;
	जबतक (!((clk = sdhci_पढ़ोw(host, SDHCI_CLOCK_CONTROL))
		& SDHCI_CLOCK_INT_STABLE)) अणु
		अगर (समयout == 0) अणु
			pr_err("%s: Internal clock never stabilised.\n",
			       mmc_hostname(host->mmc));
			वापस;
		पूर्ण
		समयout--;
		mdelay(1);
	पूर्ण

	clk |= SDHCI_CLOCK_CARD_EN;
	sdhci_ग_लिखोw(host, clk, SDHCI_CLOCK_CONTROL);
पूर्ण

अटल व्योम sdhci_at91_set_uhs_संकेतing(काष्ठा sdhci_host *host,
					 अचिन्हित पूर्णांक timing)
अणु
	अगर (timing == MMC_TIMING_MMC_DDR52)
		sdhci_ग_लिखोb(host, SDMMC_MC1R_DDR, SDMMC_MC1R);
	sdhci_set_uhs_संकेतing(host, timing);
पूर्ण

अटल व्योम sdhci_at91_reset(काष्ठा sdhci_host *host, u8 mask)
अणु
	काष्ठा sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	काष्ठा sdhci_at91_priv *priv = sdhci_pltfm_priv(pltfm_host);

	sdhci_reset(host, mask);

	अगर ((host->mmc->caps & MMC_CAP_NONREMOVABLE)
	    || mmc_gpio_get_cd(host->mmc) >= 0)
		sdhci_at91_set_क्रमce_card_detect(host);

	अगर (priv->cal_always_on && (mask & SDHCI_RESET_ALL)) अणु
		u32 calcr = sdhci_पढ़ोl(host, SDMMC_CALCR);

		sdhci_ग_लिखोl(host, calcr | SDMMC_CALCR_ALWYSON | SDMMC_CALCR_EN,
			     SDMMC_CALCR);
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा sdhci_ops sdhci_at91_sama5d2_ops = अणु
	.set_घड़ी		= sdhci_at91_set_घड़ी,
	.set_bus_width		= sdhci_set_bus_width,
	.reset			= sdhci_at91_reset,
	.set_uhs_संकेतing	= sdhci_at91_set_uhs_संकेतing,
	.set_घातer		= sdhci_set_घातer_and_bus_voltage,
पूर्ण;

अटल स्थिर काष्ठा sdhci_pltfm_data sdhci_sama5d2_pdata = अणु
	.ops = &sdhci_at91_sama5d2_ops,
पूर्ण;

अटल स्थिर काष्ठा sdhci_at91_soc_data soc_data_sama5d2 = अणु
	.pdata = &sdhci_sama5d2_pdata,
	.baseclk_is_generated_पूर्णांकernally = false,
पूर्ण;

अटल स्थिर काष्ठा sdhci_at91_soc_data soc_data_sam9x60 = अणु
	.pdata = &sdhci_sama5d2_pdata,
	.baseclk_is_generated_पूर्णांकernally = true,
	.भागider_क्रम_baseclk = 2,
पूर्ण;

अटल स्थिर काष्ठा of_device_id sdhci_at91_dt_match[] = अणु
	अणु .compatible = "atmel,sama5d2-sdhci", .data = &soc_data_sama5d2 पूर्ण,
	अणु .compatible = "microchip,sam9x60-sdhci", .data = &soc_data_sam9x60 पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, sdhci_at91_dt_match);

अटल पूर्णांक sdhci_at91_set_clks_presets(काष्ठा device *dev)
अणु
	काष्ठा sdhci_host *host = dev_get_drvdata(dev);
	काष्ठा sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	काष्ठा sdhci_at91_priv *priv = sdhci_pltfm_priv(pltfm_host);
	अचिन्हित पूर्णांक			caps0, caps1;
	अचिन्हित पूर्णांक			clk_base, clk_mul;
	अचिन्हित पूर्णांक			gck_rate, clk_base_rate;
	अचिन्हित पूर्णांक			preset_भाग;

	clk_prepare_enable(priv->hघड़ी);
	caps0 = पढ़ोl(host->ioaddr + SDHCI_CAPABILITIES);
	caps1 = पढ़ोl(host->ioaddr + SDHCI_CAPABILITIES_1);

	gck_rate = clk_get_rate(priv->gck);
	अगर (priv->soc_data->baseclk_is_generated_पूर्णांकernally)
		clk_base_rate = gck_rate / priv->soc_data->भागider_क्रम_baseclk;
	अन्यथा
		clk_base_rate = clk_get_rate(priv->मुख्यck);

	clk_base = clk_base_rate / 1000000;
	clk_mul = gck_rate / clk_base_rate - 1;

	caps0 &= ~SDHCI_CLOCK_V3_BASE_MASK;
	caps0 |= FIELD_PREP(SDHCI_CLOCK_V3_BASE_MASK, clk_base);
	caps1 &= ~SDHCI_CLOCK_MUL_MASK;
	caps1 |= FIELD_PREP(SDHCI_CLOCK_MUL_MASK, clk_mul);
	/* Set capabilities in r/w mode. */
	ग_लिखोl(SDMMC_CACR_KEY | SDMMC_CACR_CAPWREN, host->ioaddr + SDMMC_CACR);
	ग_लिखोl(caps0, host->ioaddr + SDHCI_CAPABILITIES);
	ग_लिखोl(caps1, host->ioaddr + SDHCI_CAPABILITIES_1);
	/* Set capabilities in ro mode. */
	ग_लिखोl(0, host->ioaddr + SDMMC_CACR);

	dev_dbg(dev, "update clk mul to %u as gck rate is %u Hz and clk base is %u Hz\n",
		clk_mul, gck_rate, clk_base_rate);

	/*
	 * We have to set preset values because it depends on the clk_mul
	 * value. Moreover, SDR104 is supported in a degraded mode since the
	 * maximum sd घड़ी value is 120 MHz instead of 208 MHz. For that
	 * reason, we need to use presets to support SDR104.
	 */
	preset_भाग = DIV_ROUND_UP(gck_rate, 24000000) - 1;
	ग_लिखोw(SDHCI_AT91_PRESET_COMMON_CONF | preset_भाग,
	       host->ioaddr + SDHCI_PRESET_FOR_SDR12);
	preset_भाग = DIV_ROUND_UP(gck_rate, 50000000) - 1;
	ग_लिखोw(SDHCI_AT91_PRESET_COMMON_CONF | preset_भाग,
	       host->ioaddr + SDHCI_PRESET_FOR_SDR25);
	preset_भाग = DIV_ROUND_UP(gck_rate, 100000000) - 1;
	ग_लिखोw(SDHCI_AT91_PRESET_COMMON_CONF | preset_भाग,
	       host->ioaddr + SDHCI_PRESET_FOR_SDR50);
	preset_भाग = DIV_ROUND_UP(gck_rate, 120000000) - 1;
	ग_लिखोw(SDHCI_AT91_PRESET_COMMON_CONF | preset_भाग,
	       host->ioaddr + SDHCI_PRESET_FOR_SDR104);
	preset_भाग = DIV_ROUND_UP(gck_rate, 50000000) - 1;
	ग_लिखोw(SDHCI_AT91_PRESET_COMMON_CONF | preset_भाग,
	       host->ioaddr + SDHCI_PRESET_FOR_DDR50);

	clk_prepare_enable(priv->मुख्यck);
	clk_prepare_enable(priv->gck);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक sdhci_at91_suspend(काष्ठा device *dev)
अणु
	काष्ठा sdhci_host *host = dev_get_drvdata(dev);
	काष्ठा sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	काष्ठा sdhci_at91_priv *priv = sdhci_pltfm_priv(pltfm_host);
	पूर्णांक ret;

	ret = pm_runसमय_क्रमce_suspend(dev);

	priv->restore_needed = true;

	वापस ret;
पूर्ण
#पूर्ण_अगर /* CONFIG_PM_SLEEP */

#अगर_घोषित CONFIG_PM
अटल पूर्णांक sdhci_at91_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा sdhci_host *host = dev_get_drvdata(dev);
	काष्ठा sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	काष्ठा sdhci_at91_priv *priv = sdhci_pltfm_priv(pltfm_host);
	पूर्णांक ret;

	ret = sdhci_runसमय_suspend_host(host);

	अगर (host->tuning_mode != SDHCI_TUNING_MODE_3)
		mmc_retune_needed(host->mmc);

	clk_disable_unprepare(priv->gck);
	clk_disable_unprepare(priv->hघड़ी);
	clk_disable_unprepare(priv->मुख्यck);

	वापस ret;
पूर्ण

अटल पूर्णांक sdhci_at91_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा sdhci_host *host = dev_get_drvdata(dev);
	काष्ठा sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	काष्ठा sdhci_at91_priv *priv = sdhci_pltfm_priv(pltfm_host);
	पूर्णांक ret;

	अगर (priv->restore_needed) अणु
		ret = sdhci_at91_set_clks_presets(dev);
		अगर (ret)
			वापस ret;

		priv->restore_needed = false;
		जाओ out;
	पूर्ण

	ret = clk_prepare_enable(priv->मुख्यck);
	अगर (ret) अणु
		dev_err(dev, "can't enable mainck\n");
		वापस ret;
	पूर्ण

	ret = clk_prepare_enable(priv->hघड़ी);
	अगर (ret) अणु
		dev_err(dev, "can't enable hclock\n");
		वापस ret;
	पूर्ण

	ret = clk_prepare_enable(priv->gck);
	अगर (ret) अणु
		dev_err(dev, "can't enable gck\n");
		वापस ret;
	पूर्ण

out:
	वापस sdhci_runसमय_resume_host(host, 0);
पूर्ण
#पूर्ण_अगर /* CONFIG_PM */

अटल स्थिर काष्ठा dev_pm_ops sdhci_at91_dev_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(sdhci_at91_suspend, pm_runसमय_क्रमce_resume)
	SET_RUNTIME_PM_OPS(sdhci_at91_runसमय_suspend,
			   sdhci_at91_runसमय_resume,
			   शून्य)
पूर्ण;

अटल पूर्णांक sdhci_at91_probe(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा of_device_id	*match;
	स्थिर काष्ठा sdhci_at91_soc_data	*soc_data;
	काष्ठा sdhci_host		*host;
	काष्ठा sdhci_pltfm_host		*pltfm_host;
	काष्ठा sdhci_at91_priv		*priv;
	पूर्णांक				ret;

	match = of_match_device(sdhci_at91_dt_match, &pdev->dev);
	अगर (!match)
		वापस -EINVAL;
	soc_data = match->data;

	host = sdhci_pltfm_init(pdev, soc_data->pdata, माप(*priv));
	अगर (IS_ERR(host))
		वापस PTR_ERR(host);

	pltfm_host = sdhci_priv(host);
	priv = sdhci_pltfm_priv(pltfm_host);
	priv->soc_data = soc_data;

	priv->मुख्यck = devm_clk_get(&pdev->dev, "baseclk");
	अगर (IS_ERR(priv->मुख्यck)) अणु
		अगर (soc_data->baseclk_is_generated_पूर्णांकernally) अणु
			priv->मुख्यck = शून्य;
		पूर्ण अन्यथा अणु
			dev_err(&pdev->dev, "failed to get baseclk\n");
			ret = PTR_ERR(priv->मुख्यck);
			जाओ sdhci_pltfm_मुक्त;
		पूर्ण
	पूर्ण

	priv->hघड़ी = devm_clk_get(&pdev->dev, "hclock");
	अगर (IS_ERR(priv->hघड़ी)) अणु
		dev_err(&pdev->dev, "failed to get hclock\n");
		ret = PTR_ERR(priv->hघड़ी);
		जाओ sdhci_pltfm_मुक्त;
	पूर्ण

	priv->gck = devm_clk_get(&pdev->dev, "multclk");
	अगर (IS_ERR(priv->gck)) अणु
		dev_err(&pdev->dev, "failed to get multclk\n");
		ret = PTR_ERR(priv->gck);
		जाओ sdhci_pltfm_मुक्त;
	पूर्ण

	ret = sdhci_at91_set_clks_presets(&pdev->dev);
	अगर (ret)
		जाओ sdhci_pltfm_मुक्त;

	priv->restore_needed = false;

	/*
	 * अगर SDCAL pin is wrongly connected, we must enable
	 * the analog calibration cell permanently.
	 */
	priv->cal_always_on =
		device_property_पढ़ो_bool(&pdev->dev,
					  "microchip,sdcal-inverted");

	ret = mmc_of_parse(host->mmc);
	अगर (ret)
		जाओ घड़ीs_disable_unprepare;

	sdhci_get_of_property(pdev);

	pm_runसमय_get_noresume(&pdev->dev);
	pm_runसमय_set_active(&pdev->dev);
	pm_runसमय_enable(&pdev->dev);
	pm_runसमय_set_स्वतःsuspend_delay(&pdev->dev, 50);
	pm_runसमय_use_स्वतःsuspend(&pdev->dev);

	/* HS200 is broken at this moment */
	host->quirks2 |= SDHCI_QUIRK2_BROKEN_HS200;

	ret = sdhci_add_host(host);
	अगर (ret)
		जाओ pm_runसमय_disable;

	/*
	 * When calling sdhci_runसमय_suspend_host(), the sdhci layer makes
	 * the assumption that all the घड़ीs of the controller are disabled.
	 * It means we can't get irq from it when it is runसमय suspended.
	 * For that reason, it is not planned to wake-up on a card detect irq
	 * from the controller.
	 * If we want to use runसमय PM and to be able to wake-up on card
	 * insertion, we have to use a GPIO क्रम the card detection or we can
	 * use polling. Be aware that using polling will resume/suspend the
	 * controller between each attempt.
	 * Disable SDHCI_QUIRK_BROKEN_CARD_DETECTION to be sure nobody tries
	 * to enable polling via device tree with broken-cd property.
	 */
	अगर (mmc_card_is_removable(host->mmc) &&
	    mmc_gpio_get_cd(host->mmc) < 0) अणु
		host->mmc->caps |= MMC_CAP_NEEDS_POLL;
		host->quirks &= ~SDHCI_QUIRK_BROKEN_CARD_DETECTION;
	पूर्ण

	/*
	 * If the device attached to the MMC bus is not removable, it is safer
	 * to set the Force Card Detect bit. People often करोn't connect the
	 * card detect संकेत and use this pin क्रम another purpose. If the card
	 * detect pin is not muxed to SDHCI controller, a शेष value is
	 * used. This value can be dअगरferent from a SoC revision to another
	 * one. Problems come when this शेष value is not card present. To
	 * aव्योम this हाल, अगर the device is non removable then the card
	 * detection procedure using the SDMCC_CD संकेत is bypassed.
	 * This bit is reset when a software reset क्रम all command is perक्रमmed
	 * so we need to implement our own reset function to set back this bit.
	 *
	 * WA: SAMA5D2 करोesn't drive CMD अगर using CD GPIO line.
	 */
	अगर ((host->mmc->caps & MMC_CAP_NONREMOVABLE)
	    || mmc_gpio_get_cd(host->mmc) >= 0)
		sdhci_at91_set_क्रमce_card_detect(host);

	pm_runसमय_put_स्वतःsuspend(&pdev->dev);

	वापस 0;

pm_runसमय_disable:
	pm_runसमय_disable(&pdev->dev);
	pm_runसमय_set_suspended(&pdev->dev);
	pm_runसमय_put_noidle(&pdev->dev);
घड़ीs_disable_unprepare:
	clk_disable_unprepare(priv->gck);
	clk_disable_unprepare(priv->मुख्यck);
	clk_disable_unprepare(priv->hघड़ी);
sdhci_pltfm_मुक्त:
	sdhci_pltfm_मुक्त(pdev);
	वापस ret;
पूर्ण

अटल पूर्णांक sdhci_at91_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sdhci_host	*host = platक्रमm_get_drvdata(pdev);
	काष्ठा sdhci_pltfm_host	*pltfm_host = sdhci_priv(host);
	काष्ठा sdhci_at91_priv	*priv = sdhci_pltfm_priv(pltfm_host);
	काष्ठा clk *gck = priv->gck;
	काष्ठा clk *hघड़ी = priv->hघड़ी;
	काष्ठा clk *मुख्यck = priv->मुख्यck;

	pm_runसमय_get_sync(&pdev->dev);
	pm_runसमय_disable(&pdev->dev);
	pm_runसमय_put_noidle(&pdev->dev);

	sdhci_pltfm_unरेजिस्टर(pdev);

	clk_disable_unprepare(gck);
	clk_disable_unprepare(hघड़ी);
	clk_disable_unprepare(मुख्यck);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver sdhci_at91_driver = अणु
	.driver		= अणु
		.name	= "sdhci-at91",
		.probe_type = PROBE_PREFER_ASYNCHRONOUS,
		.of_match_table = sdhci_at91_dt_match,
		.pm	= &sdhci_at91_dev_pm_ops,
	पूर्ण,
	.probe		= sdhci_at91_probe,
	.हटाओ		= sdhci_at91_हटाओ,
पूर्ण;

module_platक्रमm_driver(sdhci_at91_driver);

MODULE_DESCRIPTION("SDHCI driver for at91");
MODULE_AUTHOR("Ludovic Desroches <ludovic.desroches@atmel.com>");
MODULE_LICENSE("GPL v2");
