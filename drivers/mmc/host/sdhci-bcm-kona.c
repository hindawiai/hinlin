<शैली गुरु>
/*
 * Copyright (C) 2013 Broadcom Corporation
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License as
 * published by the Free Software Foundation version 2.
 *
 * This program is distributed "as is" WITHOUT ANY WARRANTY of any
 * kind, whether express or implied; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/delay.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/mmc/host.h>
#समावेश <linux/पन.स>
#समावेश <linux/clk.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/mmc/slot-gpपन.स>

#समावेश "sdhci-pltfm.h"
#समावेश "sdhci.h"

#घोषणा SDHCI_SOFT_RESET			0x01000000
#घोषणा KONA_SDHOST_CORECTRL			0x8000
#घोषणा KONA_SDHOST_CD_PINCTRL			0x00000008
#घोषणा KONA_SDHOST_STOP_HCLK			0x00000004
#घोषणा KONA_SDHOST_RESET			0x00000002
#घोषणा KONA_SDHOST_EN				0x00000001

#घोषणा KONA_SDHOST_CORESTAT			0x8004
#घोषणा KONA_SDHOST_WP				0x00000002
#घोषणा KONA_SDHOST_CD_SW			0x00000001

#घोषणा KONA_SDHOST_COREIMR			0x8008
#घोषणा KONA_SDHOST_IP				0x00000001

#घोषणा KONA_SDHOST_COREISR			0x800C
#घोषणा KONA_SDHOST_COREIMSR			0x8010
#घोषणा KONA_SDHOST_COREDBG1			0x8014
#घोषणा KONA_SDHOST_COREGPO_MASK		0x8018

#घोषणा SD_DETECT_GPIO_DEBOUNCE_128MS		128

#घोषणा KONA_MMC_AUTOSUSPEND_DELAY		(50)

काष्ठा sdhci_bcm_kona_dev अणु
	काष्ठा mutex	ग_लिखो_lock; /* protect back to back ग_लिखोs */
पूर्ण;


अटल पूर्णांक sdhci_bcm_kona_sd_reset(काष्ठा sdhci_host *host)
अणु
	अचिन्हित पूर्णांक val;
	अचिन्हित दीर्घ समयout;

	/* This समयout should be sufficent क्रम core to reset */
	समयout = jअगरfies + msecs_to_jअगरfies(100);

	/* reset the host using the top level reset */
	val = sdhci_पढ़ोl(host, KONA_SDHOST_CORECTRL);
	val |= KONA_SDHOST_RESET;
	sdhci_ग_लिखोl(host, val, KONA_SDHOST_CORECTRL);

	जबतक (!(sdhci_पढ़ोl(host, KONA_SDHOST_CORECTRL) & KONA_SDHOST_RESET)) अणु
		अगर (समय_is_beक्रमe_jअगरfies(समयout)) अणु
			pr_err("Error: sd host is stuck in reset!!!\n");
			वापस -EFAULT;
		पूर्ण
	पूर्ण

	/* bring the host out of reset */
	val = sdhci_पढ़ोl(host, KONA_SDHOST_CORECTRL);
	val &= ~KONA_SDHOST_RESET;

	/*
	 * Back-to-Back रेजिस्टर ग_लिखो needs a delay of 1ms at bootup (min 10uS)
	 * Back-to-Back ग_लिखोs to same रेजिस्टर needs delay when SD bus घड़ी
	 * is very low w.r.t AHB घड़ी, मुख्यly during boot-समय and during card
	 * insert-removal.
	 */
	usleep_range(1000, 5000);
	sdhci_ग_लिखोl(host, val, KONA_SDHOST_CORECTRL);

	वापस 0;
पूर्ण

अटल व्योम sdhci_bcm_kona_sd_init(काष्ठा sdhci_host *host)
अणु
	अचिन्हित पूर्णांक val;

	/* enable the पूर्णांकerrupt from the IP core */
	val = sdhci_पढ़ोl(host, KONA_SDHOST_COREIMR);
	val |= KONA_SDHOST_IP;
	sdhci_ग_लिखोl(host, val, KONA_SDHOST_COREIMR);

	/* Enable the AHB घड़ी gating module to the host */
	val = sdhci_पढ़ोl(host, KONA_SDHOST_CORECTRL);
	val |= KONA_SDHOST_EN;

	/*
	 * Back-to-Back रेजिस्टर ग_लिखो needs a delay of 1ms at bootup (min 10uS)
	 * Back-to-Back ग_लिखोs to same रेजिस्टर needs delay when SD bus घड़ी
	 * is very low w.r.t AHB घड़ी, मुख्यly during boot-समय and during card
	 * insert-removal.
	 */
	usleep_range(1000, 5000);
	sdhci_ग_लिखोl(host, val, KONA_SDHOST_CORECTRL);
पूर्ण

/*
 * Software emulation of the SD card insertion/removal. Set insert=1 क्रम insert
 * and insert=0 क्रम removal. The card detection is करोne by GPIO. For Broadcom
 * IP to function properly the bit 0 of CORESTAT रेजिस्टर needs to be set/reset
 * to generate the CD IRQ handled in sdhci.c which schedules card_tasklet.
 */
अटल पूर्णांक sdhci_bcm_kona_sd_card_emulate(काष्ठा sdhci_host *host, पूर्णांक insert)
अणु
	काष्ठा sdhci_pltfm_host *pltfm_priv = sdhci_priv(host);
	काष्ठा sdhci_bcm_kona_dev *kona_dev = sdhci_pltfm_priv(pltfm_priv);
	u32 val;

	/*
	 * Back-to-Back रेजिस्टर ग_लिखो needs a delay of min 10uS.
	 * Back-to-Back ग_लिखोs to same रेजिस्टर needs delay when SD bus घड़ी
	 * is very low w.r.t AHB घड़ी, मुख्यly during boot-समय and during card
	 * insert-removal.
	 * We keep 20uS
	 */
	mutex_lock(&kona_dev->ग_लिखो_lock);
	udelay(20);
	val = sdhci_पढ़ोl(host, KONA_SDHOST_CORESTAT);

	अगर (insert) अणु
		पूर्णांक ret;

		ret = mmc_gpio_get_ro(host->mmc);
		अगर (ret >= 0)
			val = (val & ~KONA_SDHOST_WP) |
				((ret) ? KONA_SDHOST_WP : 0);

		val |= KONA_SDHOST_CD_SW;
		sdhci_ग_लिखोl(host, val, KONA_SDHOST_CORESTAT);
	पूर्ण अन्यथा अणु
		val &= ~KONA_SDHOST_CD_SW;
		sdhci_ग_लिखोl(host, val, KONA_SDHOST_CORESTAT);
	पूर्ण
	mutex_unlock(&kona_dev->ग_लिखो_lock);

	वापस 0;
पूर्ण

/*
 * SD card पूर्णांकerrupt event callback
 */
अटल व्योम sdhci_bcm_kona_card_event(काष्ठा sdhci_host *host)
अणु
	अगर (mmc_gpio_get_cd(host->mmc) > 0) अणु
		dev_dbg(mmc_dev(host->mmc),
			"card inserted\n");
		sdhci_bcm_kona_sd_card_emulate(host, 1);
	पूर्ण अन्यथा अणु
		dev_dbg(mmc_dev(host->mmc),
			"card removed\n");
		sdhci_bcm_kona_sd_card_emulate(host, 0);
	पूर्ण
पूर्ण

अटल व्योम sdhci_bcm_kona_init_74_घड़ीs(काष्ठा sdhci_host *host,
				u8 घातer_mode)
अणु
	/*
	 *  JEDEC and SD spec specअगरy supplying 74 continuous घड़ीs to
	 * device after घातer up. With minimum bus (100KHz) that
	 * that translates to 740us
	 */
	अगर (घातer_mode != MMC_POWER_OFF)
		udelay(740);
पूर्ण

अटल स्थिर काष्ठा sdhci_ops sdhci_bcm_kona_ops = अणु
	.set_घड़ी = sdhci_set_घड़ी,
	.get_max_घड़ी = sdhci_pltfm_clk_get_max_घड़ी,
	.get_समयout_घड़ी = sdhci_pltfm_clk_get_max_घड़ी,
	.platक्रमm_send_init_74_घड़ीs = sdhci_bcm_kona_init_74_घड़ीs,
	.set_bus_width = sdhci_set_bus_width,
	.reset = sdhci_reset,
	.set_uhs_संकेतing = sdhci_set_uhs_संकेतing,
	.card_event = sdhci_bcm_kona_card_event,
पूर्ण;

अटल स्थिर काष्ठा sdhci_pltfm_data sdhci_pltfm_data_kona = अणु
	.ops    = &sdhci_bcm_kona_ops,
	.quirks = SDHCI_QUIRK_NO_CARD_NO_RESET |
		SDHCI_QUIRK_BROKEN_TIMEOUT_VAL | SDHCI_QUIRK_32BIT_DMA_ADDR |
		SDHCI_QUIRK_32BIT_DMA_SIZE | SDHCI_QUIRK_32BIT_ADMA_SIZE |
		SDHCI_QUIRK_FORCE_BLK_SZ_2048 |
		SDHCI_QUIRK_CAP_CLOCK_BASE_BROKEN,
पूर्ण;

अटल स्थिर काष्ठा of_device_id sdhci_bcm_kona_of_match[] = अणु
	अणु .compatible = "brcm,kona-sdhci"पूर्ण,
	अणु .compatible = "bcm,kona-sdhci"पूर्ण, /* deprecated name */
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, sdhci_bcm_kona_of_match);

अटल पूर्णांक sdhci_bcm_kona_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sdhci_bcm_kona_dev *kona_dev = शून्य;
	काष्ठा sdhci_pltfm_host *pltfm_priv;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा sdhci_host *host;
	पूर्णांक ret;

	ret = 0;

	host = sdhci_pltfm_init(pdev, &sdhci_pltfm_data_kona,
			माप(*kona_dev));
	अगर (IS_ERR(host))
		वापस PTR_ERR(host);

	dev_dbg(dev, "%s: inited. IOADDR=%p\n", __func__, host->ioaddr);

	pltfm_priv = sdhci_priv(host);

	kona_dev = sdhci_pltfm_priv(pltfm_priv);
	mutex_init(&kona_dev->ग_लिखो_lock);

	ret = mmc_of_parse(host->mmc);
	अगर (ret)
		जाओ err_pltfm_मुक्त;

	अगर (!host->mmc->f_max) अणु
		dev_err(&pdev->dev, "Missing max-freq for SDHCI cfg\n");
		ret = -ENXIO;
		जाओ err_pltfm_मुक्त;
	पूर्ण

	/* Get and enable the core घड़ी */
	pltfm_priv->clk = devm_clk_get(dev, शून्य);
	अगर (IS_ERR(pltfm_priv->clk)) अणु
		dev_err(dev, "Failed to get core clock\n");
		ret = PTR_ERR(pltfm_priv->clk);
		जाओ err_pltfm_मुक्त;
	पूर्ण

	ret = clk_set_rate(pltfm_priv->clk, host->mmc->f_max);
	अगर (ret) अणु
		dev_err(dev, "Failed to set rate core clock\n");
		जाओ err_pltfm_मुक्त;
	पूर्ण

	ret = clk_prepare_enable(pltfm_priv->clk);
	अगर (ret) अणु
		dev_err(dev, "Failed to enable core clock\n");
		जाओ err_pltfm_मुक्त;
	पूर्ण

	dev_dbg(dev, "non-removable=%c\n",
		mmc_card_is_removable(host->mmc) ? 'N' : 'Y');
	dev_dbg(dev, "cd_gpio %c, wp_gpio %c\n",
		(mmc_gpio_get_cd(host->mmc) != -ENOSYS) ? 'Y' : 'N',
		(mmc_gpio_get_ro(host->mmc) != -ENOSYS) ? 'Y' : 'N');

	अगर (!mmc_card_is_removable(host->mmc))
		host->quirks |= SDHCI_QUIRK_BROKEN_CARD_DETECTION;

	dev_dbg(dev, "is_8bit=%c\n",
		(host->mmc->caps & MMC_CAP_8_BIT_DATA) ? 'Y' : 'N');

	ret = sdhci_bcm_kona_sd_reset(host);
	अगर (ret)
		जाओ err_clk_disable;

	sdhci_bcm_kona_sd_init(host);

	ret = sdhci_add_host(host);
	अगर (ret)
		जाओ err_reset;

	/* अगर device is eMMC, emulate card insert right here */
	अगर (!mmc_card_is_removable(host->mmc)) अणु
		ret = sdhci_bcm_kona_sd_card_emulate(host, 1);
		अगर (ret) अणु
			dev_err(dev,
				"unable to emulate card insertion\n");
			जाओ err_हटाओ_host;
		पूर्ण
	पूर्ण
	/*
	 * Since the card detection GPIO पूर्णांकerrupt is configured to be
	 * edge sensitive, check the initial GPIO value here, emulate
	 * only अगर the card is present
	 */
	अगर (mmc_gpio_get_cd(host->mmc) > 0)
		sdhci_bcm_kona_sd_card_emulate(host, 1);

	dev_dbg(dev, "initialized properly\n");
	वापस 0;

err_हटाओ_host:
	sdhci_हटाओ_host(host, 0);

err_reset:
	sdhci_bcm_kona_sd_reset(host);

err_clk_disable:
	clk_disable_unprepare(pltfm_priv->clk);

err_pltfm_मुक्त:
	sdhci_pltfm_मुक्त(pdev);

	dev_err(dev, "Probing of sdhci-pltfm failed: %d\n", ret);
	वापस ret;
पूर्ण

अटल काष्ठा platक्रमm_driver sdhci_bcm_kona_driver = अणु
	.driver		= अणु
		.name	= "sdhci-kona",
		.probe_type = PROBE_PREFER_ASYNCHRONOUS,
		.pm	= &sdhci_pltfm_pmops,
		.of_match_table = sdhci_bcm_kona_of_match,
	पूर्ण,
	.probe		= sdhci_bcm_kona_probe,
	.हटाओ		= sdhci_pltfm_unरेजिस्टर,
पूर्ण;
module_platक्रमm_driver(sdhci_bcm_kona_driver);

MODULE_DESCRIPTION("SDHCI driver for Broadcom Kona platform");
MODULE_AUTHOR("Broadcom");
MODULE_LICENSE("GPL v2");
