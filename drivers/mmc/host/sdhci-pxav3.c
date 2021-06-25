<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2010 Marvell International Ltd.
 *		Zhangfei Gao <zhangfei.gao@marvell.com>
 *		Kevin Wang <dwang4@marvell.com>
 *		Mingwei Wang <mwwang@marvell.com>
 *		Philip Rakity <prakity@marvell.com>
 *		Mark Brown <markb@marvell.com>
 */
#समावेश <linux/err.h>
#समावेश <linux/init.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/clk.h>
#समावेश <linux/पन.स>
#समावेश <linux/mmc/card.h>
#समावेश <linux/mmc/host.h>
#समावेश <linux/platक्रमm_data/pxa_sdhci.h>
#समावेश <linux/slab.h>
#समावेश <linux/delay.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/pm.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/mbus.h>

#समावेश "sdhci.h"
#समावेश "sdhci-pltfm.h"

#घोषणा PXAV3_RPM_DELAY_MS     50

#घोषणा SD_CLOCK_BURST_SIZE_SETUP		0x10A
#घोषणा SDCLK_SEL	0x100
#घोषणा SDCLK_DELAY_SHIFT	9
#घोषणा SDCLK_DELAY_MASK	0x1f

#घोषणा SD_CFG_FIFO_PARAM       0x100
#घोषणा SDCFG_GEN_PAD_CLK_ON	(1<<6)
#घोषणा SDCFG_GEN_PAD_CLK_CNT_MASK	0xFF
#घोषणा SDCFG_GEN_PAD_CLK_CNT_SHIFT	24

#घोषणा SD_SPI_MODE          0x108
#घोषणा SD_CE_ATA_1          0x10C

#घोषणा SD_CE_ATA_2          0x10E
#घोषणा SDCE_MISC_INT		(1<<2)
#घोषणा SDCE_MISC_INT_EN	(1<<1)

काष्ठा sdhci_pxa अणु
	काष्ठा clk *clk_core;
	काष्ठा clk *clk_io;
	u8	घातer_mode;
	व्योम __iomem *sdio3_conf_reg;
पूर्ण;

/*
 * These रेजिस्टरs are relative to the second रेजिस्टर region, क्रम the
 * MBus bridge.
 */
#घोषणा SDHCI_WINDOW_CTRL(i)	(0x80 + ((i) << 3))
#घोषणा SDHCI_WINDOW_BASE(i)	(0x84 + ((i) << 3))
#घोषणा SDHCI_MAX_WIN_NUM	8

/*
 * Fields below beदीर्घ to SDIO3 Configuration Register (third रेजिस्टर
 * region क्रम the Armada 38x flavor)
 */

#घोषणा SDIO3_CONF_CLK_INV	BIT(0)
#घोषणा SDIO3_CONF_SD_FB_CLK	BIT(2)

अटल पूर्णांक mv_conf_mbus_winकरोws(काष्ठा platक्रमm_device *pdev,
				स्थिर काष्ठा mbus_dram_target_info *dram)
अणु
	पूर्णांक i;
	व्योम __iomem *regs;
	काष्ठा resource *res;

	अगर (!dram) अणु
		dev_err(&pdev->dev, "no mbus dram info\n");
		वापस -EINVAL;
	पूर्ण

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 1);
	अगर (!res) अणु
		dev_err(&pdev->dev, "cannot get mbus registers\n");
		वापस -EINVAL;
	पूर्ण

	regs = ioremap(res->start, resource_size(res));
	अगर (!regs) अणु
		dev_err(&pdev->dev, "cannot map mbus registers\n");
		वापस -ENOMEM;
	पूर्ण

	क्रम (i = 0; i < SDHCI_MAX_WIN_NUM; i++) अणु
		ग_लिखोl(0, regs + SDHCI_WINDOW_CTRL(i));
		ग_लिखोl(0, regs + SDHCI_WINDOW_BASE(i));
	पूर्ण

	क्रम (i = 0; i < dram->num_cs; i++) अणु
		स्थिर काष्ठा mbus_dram_winकरोw *cs = dram->cs + i;

		/* Write size, attributes and target id to control रेजिस्टर */
		ग_लिखोl(((cs->size - 1) & 0xffff0000) |
			(cs->mbus_attr << 8) |
			(dram->mbus_dram_target_id << 4) | 1,
			regs + SDHCI_WINDOW_CTRL(i));
		/* Write base address to base रेजिस्टर */
		ग_लिखोl(cs->base, regs + SDHCI_WINDOW_BASE(i));
	पूर्ण

	iounmap(regs);

	वापस 0;
पूर्ण

अटल पूर्णांक armada_38x_quirks(काष्ठा platक्रमm_device *pdev,
			     काष्ठा sdhci_host *host)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	काष्ठा sdhci_pxa *pxa = sdhci_pltfm_priv(pltfm_host);
	काष्ठा resource *res;

	host->quirks &= ~SDHCI_QUIRK_CAP_CLOCK_BASE_BROKEN;
	host->quirks |= SDHCI_QUIRK_MISSING_CAPS;

	host->caps = sdhci_पढ़ोl(host, SDHCI_CAPABILITIES);
	host->caps1 = sdhci_पढ़ोl(host, SDHCI_CAPABILITIES_1);

	res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM,
					   "conf-sdio3");
	अगर (res) अणु
		pxa->sdio3_conf_reg = devm_ioremap_resource(&pdev->dev, res);
		अगर (IS_ERR(pxa->sdio3_conf_reg))
			वापस PTR_ERR(pxa->sdio3_conf_reg);
	पूर्ण अन्यथा अणु
		/*
		 * According to erratum 'FE-2946959' both SDR50 and DDR50
		 * modes require specअगरic घड़ी adjusपंचांगents in SDIO3
		 * Configuration रेजिस्टर, अगर the adjusपंचांगent is not करोne,
		 * हटाओ them from the capabilities.
		 */
		host->caps1 &= ~(SDHCI_SUPPORT_SDR50 | SDHCI_SUPPORT_DDR50);

		dev_warn(&pdev->dev, "conf-sdio3 register not found: disabling SDR50 and DDR50 modes.\nConsider updating your dtb\n");
	पूर्ण

	/*
	 * According to erratum 'ERR-7878951' Armada 38x SDHCI
	 * controller has dअगरferent capabilities than the ones shown
	 * in its रेजिस्टरs
	 */
	अगर (of_property_पढ़ो_bool(np, "no-1-8-v")) अणु
		host->caps &= ~SDHCI_CAN_VDD_180;
		host->mmc->caps &= ~MMC_CAP_1_8V_DDR;
	पूर्ण अन्यथा अणु
		host->caps &= ~SDHCI_CAN_VDD_330;
	पूर्ण
	host->caps1 &= ~(SDHCI_SUPPORT_SDR104 | SDHCI_USE_SDR50_TUNING);

	वापस 0;
पूर्ण

अटल व्योम pxav3_reset(काष्ठा sdhci_host *host, u8 mask)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(mmc_dev(host->mmc));
	काष्ठा sdhci_pxa_platdata *pdata = pdev->dev.platक्रमm_data;

	sdhci_reset(host, mask);

	अगर (mask == SDHCI_RESET_ALL) अणु
		/*
		 * tune timing of पढ़ो data/command when crc error happen
		 * no perक्रमmance impact
		 */
		अगर (pdata && 0 != pdata->clk_delay_cycles) अणु
			u16 पंचांगp;

			पंचांगp = पढ़ोw(host->ioaddr + SD_CLOCK_BURST_SIZE_SETUP);
			पंचांगp |= (pdata->clk_delay_cycles & SDCLK_DELAY_MASK)
				<< SDCLK_DELAY_SHIFT;
			पंचांगp |= SDCLK_SEL;
			ग_लिखोw(पंचांगp, host->ioaddr + SD_CLOCK_BURST_SIZE_SETUP);
		पूर्ण
	पूर्ण
पूर्ण

#घोषणा MAX_WAIT_COUNT 5
अटल व्योम pxav3_gen_init_74_घड़ीs(काष्ठा sdhci_host *host, u8 घातer_mode)
अणु
	काष्ठा sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	काष्ठा sdhci_pxa *pxa = sdhci_pltfm_priv(pltfm_host);
	u16 पंचांगp;
	पूर्णांक count;

	अगर (pxa->घातer_mode == MMC_POWER_UP
			&& घातer_mode == MMC_POWER_ON) अणु

		dev_dbg(mmc_dev(host->mmc),
				"%s: slot->power_mode = %d,"
				"ios->power_mode = %d\n",
				__func__,
				pxa->घातer_mode,
				घातer_mode);

		/* set we want notice of when 74 घड़ीs are sent */
		पंचांगp = पढ़ोw(host->ioaddr + SD_CE_ATA_2);
		पंचांगp |= SDCE_MISC_INT_EN;
		ग_लिखोw(पंचांगp, host->ioaddr + SD_CE_ATA_2);

		/* start sending the 74 घड़ीs */
		पंचांगp = पढ़ोw(host->ioaddr + SD_CFG_FIFO_PARAM);
		पंचांगp |= SDCFG_GEN_PAD_CLK_ON;
		ग_लिखोw(पंचांगp, host->ioaddr + SD_CFG_FIFO_PARAM);

		/* slowest speed is about 100KHz or 10usec per घड़ी */
		udelay(740);
		count = 0;

		जबतक (count++ < MAX_WAIT_COUNT) अणु
			अगर ((पढ़ोw(host->ioaddr + SD_CE_ATA_2)
						& SDCE_MISC_INT) == 0)
				अवरोध;
			udelay(10);
		पूर्ण

		अगर (count == MAX_WAIT_COUNT)
			dev_warn(mmc_dev(host->mmc), "74 clock interrupt not cleared\n");

		/* clear the पूर्णांकerrupt bit अगर posted */
		पंचांगp = पढ़ोw(host->ioaddr + SD_CE_ATA_2);
		पंचांगp |= SDCE_MISC_INT;
		ग_लिखोw(पंचांगp, host->ioaddr + SD_CE_ATA_2);
	पूर्ण
	pxa->घातer_mode = घातer_mode;
पूर्ण

अटल व्योम pxav3_set_uhs_संकेतing(काष्ठा sdhci_host *host, अचिन्हित पूर्णांक uhs)
अणु
	काष्ठा sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	काष्ठा sdhci_pxa *pxa = sdhci_pltfm_priv(pltfm_host);
	u16 ctrl_2;

	/*
	 * Set V18_EN -- UHS modes करो not work without this.
	 * करोes not change संकेतing voltage
	 */
	ctrl_2 = sdhci_पढ़ोw(host, SDHCI_HOST_CONTROL2);

	/* Select Bus Speed Mode क्रम host */
	ctrl_2 &= ~SDHCI_CTRL_UHS_MASK;
	चयन (uhs) अणु
	हाल MMC_TIMING_UHS_SDR12:
		ctrl_2 |= SDHCI_CTRL_UHS_SDR12;
		अवरोध;
	हाल MMC_TIMING_UHS_SDR25:
		ctrl_2 |= SDHCI_CTRL_UHS_SDR25;
		अवरोध;
	हाल MMC_TIMING_UHS_SDR50:
		ctrl_2 |= SDHCI_CTRL_UHS_SDR50 | SDHCI_CTRL_VDD_180;
		अवरोध;
	हाल MMC_TIMING_UHS_SDR104:
		ctrl_2 |= SDHCI_CTRL_UHS_SDR104 | SDHCI_CTRL_VDD_180;
		अवरोध;
	हाल MMC_TIMING_MMC_DDR52:
	हाल MMC_TIMING_UHS_DDR50:
		ctrl_2 |= SDHCI_CTRL_UHS_DDR50 | SDHCI_CTRL_VDD_180;
		अवरोध;
	पूर्ण

	/*
	 * Update SDIO3 Configuration रेजिस्टर according to erratum
	 * FE-2946959
	 */
	अगर (pxa->sdio3_conf_reg) अणु
		u8 reg_val  = पढ़ोb(pxa->sdio3_conf_reg);

		अगर (uhs == MMC_TIMING_UHS_SDR50 ||
		    uhs == MMC_TIMING_UHS_DDR50) अणु
			reg_val &= ~SDIO3_CONF_CLK_INV;
			reg_val |= SDIO3_CONF_SD_FB_CLK;
		पूर्ण अन्यथा अगर (uhs == MMC_TIMING_MMC_HS) अणु
			reg_val &= ~SDIO3_CONF_CLK_INV;
			reg_val &= ~SDIO3_CONF_SD_FB_CLK;
		पूर्ण अन्यथा अणु
			reg_val |= SDIO3_CONF_CLK_INV;
			reg_val &= ~SDIO3_CONF_SD_FB_CLK;
		पूर्ण
		ग_लिखोb(reg_val, pxa->sdio3_conf_reg);
	पूर्ण

	sdhci_ग_लिखोw(host, ctrl_2, SDHCI_HOST_CONTROL2);
	dev_dbg(mmc_dev(host->mmc),
		"%s uhs = %d, ctrl_2 = %04X\n",
		__func__, uhs, ctrl_2);
पूर्ण

अटल व्योम pxav3_set_घातer(काष्ठा sdhci_host *host, अचिन्हित अक्षर mode,
			    अचिन्हित लघु vdd)
अणु
	काष्ठा mmc_host *mmc = host->mmc;
	u8 pwr = host->pwr;

	sdhci_set_घातer_noreg(host, mode, vdd);

	अगर (host->pwr == pwr)
		वापस;

	अगर (host->pwr == 0)
		vdd = 0;

	अगर (!IS_ERR(mmc->supply.vmmc))
		mmc_regulator_set_ocr(mmc, mmc->supply.vmmc, vdd);
पूर्ण

अटल स्थिर काष्ठा sdhci_ops pxav3_sdhci_ops = अणु
	.set_घड़ी = sdhci_set_घड़ी,
	.set_घातer = pxav3_set_घातer,
	.platक्रमm_send_init_74_घड़ीs = pxav3_gen_init_74_घड़ीs,
	.get_max_घड़ी = sdhci_pltfm_clk_get_max_घड़ी,
	.set_bus_width = sdhci_set_bus_width,
	.reset = pxav3_reset,
	.set_uhs_संकेतing = pxav3_set_uhs_संकेतing,
पूर्ण;

अटल स्थिर काष्ठा sdhci_pltfm_data sdhci_pxav3_pdata = अणु
	.quirks = SDHCI_QUIRK_DATA_TIMEOUT_USES_SDCLK
		| SDHCI_QUIRK_NO_ENDATTR_IN_NOPDESC
		| SDHCI_QUIRK_32BIT_ADMA_SIZE
		| SDHCI_QUIRK_CAP_CLOCK_BASE_BROKEN,
	.ops = &pxav3_sdhci_ops,
पूर्ण;

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id sdhci_pxav3_of_match[] = अणु
	अणु
		.compatible = "mrvl,pxav3-mmc",
	पूर्ण,
	अणु
		.compatible = "marvell,armada-380-sdhci",
	पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, sdhci_pxav3_of_match);

अटल काष्ठा sdhci_pxa_platdata *pxav3_get_mmc_pdata(काष्ठा device *dev)
अणु
	काष्ठा sdhci_pxa_platdata *pdata;
	काष्ठा device_node *np = dev->of_node;
	u32 clk_delay_cycles;

	pdata = devm_kzalloc(dev, माप(*pdata), GFP_KERNEL);
	अगर (!pdata)
		वापस शून्य;

	अगर (!of_property_पढ़ो_u32(np, "mrvl,clk-delay-cycles",
				  &clk_delay_cycles))
		pdata->clk_delay_cycles = clk_delay_cycles;

	वापस pdata;
पूर्ण
#अन्यथा
अटल अंतरभूत काष्ठा sdhci_pxa_platdata *pxav3_get_mmc_pdata(काष्ठा device *dev)
अणु
	वापस शून्य;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक sdhci_pxav3_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sdhci_pltfm_host *pltfm_host;
	काष्ठा sdhci_pxa_platdata *pdata = pdev->dev.platक्रमm_data;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा sdhci_host *host = शून्य;
	काष्ठा sdhci_pxa *pxa = शून्य;
	स्थिर काष्ठा of_device_id *match;
	पूर्णांक ret;

	host = sdhci_pltfm_init(pdev, &sdhci_pxav3_pdata, माप(*pxa));
	अगर (IS_ERR(host))
		वापस PTR_ERR(host);

	pltfm_host = sdhci_priv(host);
	pxa = sdhci_pltfm_priv(pltfm_host);

	pxa->clk_io = devm_clk_get(dev, "io");
	अगर (IS_ERR(pxa->clk_io))
		pxa->clk_io = devm_clk_get(dev, शून्य);
	अगर (IS_ERR(pxa->clk_io)) अणु
		dev_err(dev, "failed to get io clock\n");
		ret = PTR_ERR(pxa->clk_io);
		जाओ err_clk_get;
	पूर्ण
	pltfm_host->clk = pxa->clk_io;
	clk_prepare_enable(pxa->clk_io);

	pxa->clk_core = devm_clk_get(dev, "core");
	अगर (!IS_ERR(pxa->clk_core))
		clk_prepare_enable(pxa->clk_core);

	/* enable 1/8V DDR capable */
	host->mmc->caps |= MMC_CAP_1_8V_DDR;

	अगर (of_device_is_compatible(np, "marvell,armada-380-sdhci")) अणु
		ret = armada_38x_quirks(pdev, host);
		अगर (ret < 0)
			जाओ err_mbus_win;
		ret = mv_conf_mbus_winकरोws(pdev, mv_mbus_dram_info());
		अगर (ret < 0)
			जाओ err_mbus_win;
	पूर्ण

	match = of_match_device(of_match_ptr(sdhci_pxav3_of_match), &pdev->dev);
	अगर (match) अणु
		ret = mmc_of_parse(host->mmc);
		अगर (ret)
			जाओ err_of_parse;
		sdhci_get_of_property(pdev);
		pdata = pxav3_get_mmc_pdata(dev);
		pdev->dev.platक्रमm_data = pdata;
	पूर्ण अन्यथा अगर (pdata) अणु
		/* on-chip device */
		अगर (pdata->flags & PXA_FLAG_CARD_PERMANENT)
			host->mmc->caps |= MMC_CAP_NONREMOVABLE;

		/* If slot design supports 8 bit data, indicate this to MMC. */
		अगर (pdata->flags & PXA_FLAG_SD_8_BIT_CAPABLE_SLOT)
			host->mmc->caps |= MMC_CAP_8_BIT_DATA;

		अगर (pdata->quirks)
			host->quirks |= pdata->quirks;
		अगर (pdata->quirks2)
			host->quirks2 |= pdata->quirks2;
		अगर (pdata->host_caps)
			host->mmc->caps |= pdata->host_caps;
		अगर (pdata->host_caps2)
			host->mmc->caps2 |= pdata->host_caps2;
		अगर (pdata->pm_caps)
			host->mmc->pm_caps |= pdata->pm_caps;
	पूर्ण

	pm_runसमय_get_noresume(&pdev->dev);
	pm_runसमय_set_active(&pdev->dev);
	pm_runसमय_set_स्वतःsuspend_delay(&pdev->dev, PXAV3_RPM_DELAY_MS);
	pm_runसमय_use_स्वतःsuspend(&pdev->dev);
	pm_runसमय_enable(&pdev->dev);
	pm_suspend_ignore_children(&pdev->dev, 1);

	ret = sdhci_add_host(host);
	अगर (ret)
		जाओ err_add_host;

	अगर (host->mmc->pm_caps & MMC_PM_WAKE_SDIO_IRQ)
		device_init_wakeup(&pdev->dev, 1);

	pm_runसमय_put_स्वतःsuspend(&pdev->dev);

	वापस 0;

err_add_host:
	pm_runसमय_disable(&pdev->dev);
	pm_runसमय_put_noidle(&pdev->dev);
err_of_parse:
err_mbus_win:
	clk_disable_unprepare(pxa->clk_io);
	clk_disable_unprepare(pxa->clk_core);
err_clk_get:
	sdhci_pltfm_मुक्त(pdev);
	वापस ret;
पूर्ण

अटल पूर्णांक sdhci_pxav3_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sdhci_host *host = platक्रमm_get_drvdata(pdev);
	काष्ठा sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	काष्ठा sdhci_pxa *pxa = sdhci_pltfm_priv(pltfm_host);

	pm_runसमय_get_sync(&pdev->dev);
	pm_runसमय_disable(&pdev->dev);
	pm_runसमय_put_noidle(&pdev->dev);

	sdhci_हटाओ_host(host, 1);

	clk_disable_unprepare(pxa->clk_io);
	clk_disable_unprepare(pxa->clk_core);

	sdhci_pltfm_मुक्त(pdev);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक sdhci_pxav3_suspend(काष्ठा device *dev)
अणु
	पूर्णांक ret;
	काष्ठा sdhci_host *host = dev_get_drvdata(dev);

	pm_runसमय_get_sync(dev);
	अगर (host->tuning_mode != SDHCI_TUNING_MODE_3)
		mmc_retune_needed(host->mmc);
	ret = sdhci_suspend_host(host);
	pm_runसमय_mark_last_busy(dev);
	pm_runसमय_put_स्वतःsuspend(dev);

	वापस ret;
पूर्ण

अटल पूर्णांक sdhci_pxav3_resume(काष्ठा device *dev)
अणु
	पूर्णांक ret;
	काष्ठा sdhci_host *host = dev_get_drvdata(dev);

	pm_runसमय_get_sync(dev);
	ret = sdhci_resume_host(host);
	pm_runसमय_mark_last_busy(dev);
	pm_runसमय_put_स्वतःsuspend(dev);

	वापस ret;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_PM
अटल पूर्णांक sdhci_pxav3_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा sdhci_host *host = dev_get_drvdata(dev);
	काष्ठा sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	काष्ठा sdhci_pxa *pxa = sdhci_pltfm_priv(pltfm_host);
	पूर्णांक ret;

	ret = sdhci_runसमय_suspend_host(host);
	अगर (ret)
		वापस ret;

	अगर (host->tuning_mode != SDHCI_TUNING_MODE_3)
		mmc_retune_needed(host->mmc);

	clk_disable_unprepare(pxa->clk_io);
	अगर (!IS_ERR(pxa->clk_core))
		clk_disable_unprepare(pxa->clk_core);

	वापस 0;
पूर्ण

अटल पूर्णांक sdhci_pxav3_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा sdhci_host *host = dev_get_drvdata(dev);
	काष्ठा sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	काष्ठा sdhci_pxa *pxa = sdhci_pltfm_priv(pltfm_host);

	clk_prepare_enable(pxa->clk_io);
	अगर (!IS_ERR(pxa->clk_core))
		clk_prepare_enable(pxa->clk_core);

	वापस sdhci_runसमय_resume_host(host, 0);
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा dev_pm_ops sdhci_pxav3_pmops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(sdhci_pxav3_suspend, sdhci_pxav3_resume)
	SET_RUNTIME_PM_OPS(sdhci_pxav3_runसमय_suspend,
		sdhci_pxav3_runसमय_resume, शून्य)
पूर्ण;

अटल काष्ठा platक्रमm_driver sdhci_pxav3_driver = अणु
	.driver		= अणु
		.name	= "sdhci-pxav3",
		.probe_type = PROBE_PREFER_ASYNCHRONOUS,
		.of_match_table = of_match_ptr(sdhci_pxav3_of_match),
		.pm	= &sdhci_pxav3_pmops,
	पूर्ण,
	.probe		= sdhci_pxav3_probe,
	.हटाओ		= sdhci_pxav3_हटाओ,
पूर्ण;

module_platक्रमm_driver(sdhci_pxav3_driver);

MODULE_DESCRIPTION("SDHCI driver for pxav3");
MODULE_AUTHOR("Marvell International Ltd.");
MODULE_LICENSE("GPL v2");

