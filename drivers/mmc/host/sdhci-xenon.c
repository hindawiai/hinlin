<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Driver क्रम Marvell Xenon SDHC as a platक्रमm device
 *
 * Copyright (C) 2016 Marvell, All Rights Reserved.
 *
 * Author:	Hu Ziji <huziji@marvell.com>
 * Date:	2016-8-24
 *
 * Inspired by Jisheng Zhang <jszhang@marvell.com>
 * Special thanks to Video BG4 project team.
 */

#समावेश <linux/acpi.h>
#समावेश <linux/delay.h>
#समावेश <linux/kसमय.स>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/pm.h>
#समावेश <linux/pm_runसमय.स>

#समावेश "sdhci-pltfm.h"
#समावेश "sdhci-xenon.h"

अटल पूर्णांक xenon_enable_पूर्णांकernal_clk(काष्ठा sdhci_host *host)
अणु
	u32 reg;
	kसमय_प्रकार समयout;

	reg = sdhci_पढ़ोl(host, SDHCI_CLOCK_CONTROL);
	reg |= SDHCI_CLOCK_INT_EN;
	sdhci_ग_लिखोl(host, reg, SDHCI_CLOCK_CONTROL);
	/* Wait max 20 ms */
	समयout = kसमय_add_ms(kसमय_get(), 20);
	जबतक (1) अणु
		bool समयकरोut = kसमय_after(kसमय_get(), समयout);

		reg = sdhci_पढ़ोw(host, SDHCI_CLOCK_CONTROL);
		अगर (reg & SDHCI_CLOCK_INT_STABLE)
			अवरोध;
		अगर (समयकरोut) अणु
			dev_err(mmc_dev(host->mmc), "Internal clock never stabilised.\n");
			वापस -ETIMEDOUT;
		पूर्ण
		usleep_range(900, 1100);
	पूर्ण

	वापस 0;
पूर्ण

/* Set SDCLK-off-जबतक-idle */
अटल व्योम xenon_set_sdclk_off_idle(काष्ठा sdhci_host *host,
				     अचिन्हित अक्षर sdhc_id, bool enable)
अणु
	u32 reg;
	u32 mask;

	reg = sdhci_पढ़ोl(host, XENON_SYS_OP_CTRL);
	/* Get the bit shअगरt basing on the SDHC index */
	mask = (0x1 << (XENON_SDCLK_IDLखातापूर्णF_ENABLE_SHIFT + sdhc_id));
	अगर (enable)
		reg |= mask;
	अन्यथा
		reg &= ~mask;

	sdhci_ग_लिखोl(host, reg, XENON_SYS_OP_CTRL);
पूर्ण

/* Enable/Disable the Auto Clock Gating function */
अटल व्योम xenon_set_acg(काष्ठा sdhci_host *host, bool enable)
अणु
	u32 reg;

	reg = sdhci_पढ़ोl(host, XENON_SYS_OP_CTRL);
	अगर (enable)
		reg &= ~XENON_AUTO_CLKGATE_DISABLE_MASK;
	अन्यथा
		reg |= XENON_AUTO_CLKGATE_DISABLE_MASK;
	sdhci_ग_लिखोl(host, reg, XENON_SYS_OP_CTRL);
पूर्ण

/* Enable this SDHC */
अटल व्योम xenon_enable_sdhc(काष्ठा sdhci_host *host,
			      अचिन्हित अक्षर sdhc_id)
अणु
	u32 reg;

	reg = sdhci_पढ़ोl(host, XENON_SYS_OP_CTRL);
	reg |= (BIT(sdhc_id) << XENON_SLOT_ENABLE_SHIFT);
	sdhci_ग_लिखोl(host, reg, XENON_SYS_OP_CTRL);

	host->mmc->caps |= MMC_CAP_WAIT_WHILE_BUSY;
	/*
	 * Force to clear BUS_TEST to
	 * skip bus_test_pre and bus_test_post
	 */
	host->mmc->caps &= ~MMC_CAP_BUS_WIDTH_TEST;
पूर्ण

/* Disable this SDHC */
अटल व्योम xenon_disable_sdhc(काष्ठा sdhci_host *host,
			       अचिन्हित अक्षर sdhc_id)
अणु
	u32 reg;

	reg = sdhci_पढ़ोl(host, XENON_SYS_OP_CTRL);
	reg &= ~(BIT(sdhc_id) << XENON_SLOT_ENABLE_SHIFT);
	sdhci_ग_लिखोl(host, reg, XENON_SYS_OP_CTRL);
पूर्ण

/* Enable Parallel Transfer Mode */
अटल व्योम xenon_enable_sdhc_parallel_tran(काष्ठा sdhci_host *host,
					    अचिन्हित अक्षर sdhc_id)
अणु
	u32 reg;

	reg = sdhci_पढ़ोl(host, XENON_SYS_EXT_OP_CTRL);
	reg |= BIT(sdhc_id);
	sdhci_ग_लिखोl(host, reg, XENON_SYS_EXT_OP_CTRL);
पूर्ण

/* Mask command conflict error */
अटल व्योम xenon_mask_cmd_conflict_err(काष्ठा sdhci_host *host)
अणु
	u32  reg;

	reg = sdhci_पढ़ोl(host, XENON_SYS_EXT_OP_CTRL);
	reg |= XENON_MASK_CMD_CONFLICT_ERR;
	sdhci_ग_लिखोl(host, reg, XENON_SYS_EXT_OP_CTRL);
पूर्ण

अटल व्योम xenon_retune_setup(काष्ठा sdhci_host *host)
अणु
	काष्ठा sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	काष्ठा xenon_priv *priv = sdhci_pltfm_priv(pltfm_host);
	u32 reg;

	/* Disable the Re-Tuning Request functionality */
	reg = sdhci_पढ़ोl(host, XENON_SLOT_RETUNING_REQ_CTRL);
	reg &= ~XENON_RETUNING_COMPATIBLE;
	sdhci_ग_लिखोl(host, reg, XENON_SLOT_RETUNING_REQ_CTRL);

	/* Disable the Re-tuning Interrupt */
	reg = sdhci_पढ़ोl(host, SDHCI_SIGNAL_ENABLE);
	reg &= ~SDHCI_INT_RETUNE;
	sdhci_ग_लिखोl(host, reg, SDHCI_SIGNAL_ENABLE);
	reg = sdhci_पढ़ोl(host, SDHCI_INT_ENABLE);
	reg &= ~SDHCI_INT_RETUNE;
	sdhci_ग_लिखोl(host, reg, SDHCI_INT_ENABLE);

	/* Force to use Tuning Mode 1 */
	host->tuning_mode = SDHCI_TUNING_MODE_1;
	/* Set re-tuning period */
	host->tuning_count = 1 << (priv->tuning_count - 1);
पूर्ण

/*
 * Operations inside काष्ठा sdhci_ops
 */
/* Recover the Register Setting cleared during SOFTWARE_RESET_ALL */
अटल व्योम xenon_reset_निकास(काष्ठा sdhci_host *host,
			     अचिन्हित अक्षर sdhc_id, u8 mask)
अणु
	/* Only SOFTWARE RESET ALL will clear the रेजिस्टर setting */
	अगर (!(mask & SDHCI_RESET_ALL))
		वापस;

	/* Disable tuning request and स्वतः-retuning again */
	xenon_retune_setup(host);

	/*
	 * The ACG should be turned off at the early init समय, in order
	 * to solve a possible issues with the 1.8V regulator stabilization.
	 * The feature is enabled in later stage.
	 */
	xenon_set_acg(host, false);

	xenon_set_sdclk_off_idle(host, sdhc_id, false);

	xenon_mask_cmd_conflict_err(host);
पूर्ण

अटल व्योम xenon_reset(काष्ठा sdhci_host *host, u8 mask)
अणु
	काष्ठा sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	काष्ठा xenon_priv *priv = sdhci_pltfm_priv(pltfm_host);

	sdhci_reset(host, mask);
	xenon_reset_निकास(host, priv->sdhc_id, mask);
पूर्ण

/*
 * Xenon defines dअगरferent values क्रम HS200 and HS400
 * in Host_Control_2
 */
अटल व्योम xenon_set_uhs_संकेतing(काष्ठा sdhci_host *host,
				    अचिन्हित पूर्णांक timing)
अणु
	u16 ctrl_2;

	ctrl_2 = sdhci_पढ़ोw(host, SDHCI_HOST_CONTROL2);
	/* Select Bus Speed Mode क्रम host */
	ctrl_2 &= ~SDHCI_CTRL_UHS_MASK;
	अगर (timing == MMC_TIMING_MMC_HS200)
		ctrl_2 |= XENON_CTRL_HS200;
	अन्यथा अगर (timing == MMC_TIMING_UHS_SDR104)
		ctrl_2 |= SDHCI_CTRL_UHS_SDR104;
	अन्यथा अगर (timing == MMC_TIMING_UHS_SDR12)
		ctrl_2 |= SDHCI_CTRL_UHS_SDR12;
	अन्यथा अगर (timing == MMC_TIMING_UHS_SDR25)
		ctrl_2 |= SDHCI_CTRL_UHS_SDR25;
	अन्यथा अगर (timing == MMC_TIMING_UHS_SDR50)
		ctrl_2 |= SDHCI_CTRL_UHS_SDR50;
	अन्यथा अगर ((timing == MMC_TIMING_UHS_DDR50) ||
		 (timing == MMC_TIMING_MMC_DDR52))
		ctrl_2 |= SDHCI_CTRL_UHS_DDR50;
	अन्यथा अगर (timing == MMC_TIMING_MMC_HS400)
		ctrl_2 |= XENON_CTRL_HS400;
	sdhci_ग_लिखोw(host, ctrl_2, SDHCI_HOST_CONTROL2);
पूर्ण

अटल व्योम xenon_set_घातer(काष्ठा sdhci_host *host, अचिन्हित अक्षर mode,
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

अटल व्योम xenon_voltage_चयन(काष्ठा sdhci_host *host)
अणु
	/* Wait क्रम 5ms after set 1.8V संकेत enable bit */
	usleep_range(5000, 5500);

	/*
	 * For some reason the controller's Host Control2 रेजिस्टर reports
	 * the bit representing 1.8V संकेतing as 0 when पढ़ो after it was
	 * written as 1. Subsequent पढ़ो reports 1.
	 *
	 * Since this may cause some issues, करो an empty पढ़ो of the Host
	 * Control2 रेजिस्टर here to circumvent this.
	 */
	sdhci_पढ़ोw(host, SDHCI_HOST_CONTROL2);
पूर्ण

अटल अचिन्हित पूर्णांक xenon_get_max_घड़ी(काष्ठा sdhci_host *host)
अणु
	काष्ठा sdhci_pltfm_host *pltfm_host = sdhci_priv(host);

	अगर (pltfm_host->clk)
		वापस sdhci_pltfm_clk_get_max_घड़ी(host);
	अन्यथा
		वापस pltfm_host->घड़ी;
पूर्ण

अटल स्थिर काष्ठा sdhci_ops sdhci_xenon_ops = अणु
	.voltage_चयन		= xenon_voltage_चयन,
	.set_घड़ी		= sdhci_set_घड़ी,
	.set_घातer		= xenon_set_घातer,
	.set_bus_width		= sdhci_set_bus_width,
	.reset			= xenon_reset,
	.set_uhs_संकेतing	= xenon_set_uhs_संकेतing,
	.get_max_घड़ी		= xenon_get_max_घड़ी,
पूर्ण;

अटल स्थिर काष्ठा sdhci_pltfm_data sdhci_xenon_pdata = अणु
	.ops = &sdhci_xenon_ops,
	.quirks = SDHCI_QUIRK_NO_ENDATTR_IN_NOPDESC |
		  SDHCI_QUIRK_NO_SIMULT_VDD_AND_POWER |
		  SDHCI_QUIRK_CAP_CLOCK_BASE_BROKEN,
पूर्ण;

/*
 * Xenon Specअगरic Operations in mmc_host_ops
 */
अटल व्योम xenon_set_ios(काष्ठा mmc_host *mmc, काष्ठा mmc_ios *ios)
अणु
	काष्ठा sdhci_host *host = mmc_priv(mmc);
	काष्ठा sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	काष्ठा xenon_priv *priv = sdhci_pltfm_priv(pltfm_host);
	u32 reg;

	/*
	 * HS400/HS200/eMMC HS करोesn't have Preset Value रेजिस्टर.
	 * However, sdhci_set_ios will पढ़ो HS400/HS200 Preset रेजिस्टर.
	 * Disable Preset Value रेजिस्टर क्रम HS400/HS200.
	 * eMMC HS with preset_enabled set will trigger a bug in
	 * get_preset_value().
	 */
	अगर ((ios->timing == MMC_TIMING_MMC_HS400) ||
	    (ios->timing == MMC_TIMING_MMC_HS200) ||
	    (ios->timing == MMC_TIMING_MMC_HS)) अणु
		host->preset_enabled = false;
		host->quirks2 |= SDHCI_QUIRK2_PRESET_VALUE_BROKEN;
		host->flags &= ~SDHCI_PV_ENABLED;

		reg = sdhci_पढ़ोw(host, SDHCI_HOST_CONTROL2);
		reg &= ~SDHCI_CTRL_PRESET_VAL_ENABLE;
		sdhci_ग_लिखोw(host, reg, SDHCI_HOST_CONTROL2);
	पूर्ण अन्यथा अणु
		host->quirks2 &= ~SDHCI_QUIRK2_PRESET_VALUE_BROKEN;
	पूर्ण

	sdhci_set_ios(mmc, ios);
	xenon_phy_adj(host, ios);

	अगर (host->घड़ी > XENON_DEFAULT_SDCLK_FREQ)
		xenon_set_sdclk_off_idle(host, priv->sdhc_id, true);
पूर्ण

अटल पूर्णांक xenon_start_संकेत_voltage_चयन(काष्ठा mmc_host *mmc,
					     काष्ठा mmc_ios *ios)
अणु
	काष्ठा sdhci_host *host = mmc_priv(mmc);

	/*
	 * Beक्रमe SD/SDIO set संकेत voltage, SD bus घड़ी should be
	 * disabled. However, sdhci_set_घड़ी will also disable the Internal
	 * घड़ी in mmc_set_संकेत_voltage().
	 * If Internal घड़ी is disabled, the 3.3V/1.8V bit can not be updated.
	 * Thus here manually enable पूर्णांकernal घड़ी.
	 *
	 * After चयन completes, it is unnecessary to disable पूर्णांकernal घड़ी,
	 * since keeping पूर्णांकernal घड़ी active obeys SD spec.
	 */
	xenon_enable_पूर्णांकernal_clk(host);

	xenon_soc_pad_ctrl(host, ios->संकेत_voltage);

	/*
	 * If Vqmmc is fixed on platक्रमm, vqmmc regulator should be unavailable.
	 * Thus SDHCI_CTRL_VDD_180 bit might not work then.
	 * Skip the standard voltage चयन to aव्योम any issue.
	 */
	अगर (PTR_ERR(mmc->supply.vqmmc) == -ENODEV)
		वापस 0;

	वापस sdhci_start_संकेत_voltage_चयन(mmc, ios);
पूर्ण

/*
 * Update card type.
 * priv->init_card_type will be used in PHY timing adjusपंचांगent.
 */
अटल व्योम xenon_init_card(काष्ठा mmc_host *mmc, काष्ठा mmc_card *card)
अणु
	काष्ठा sdhci_host *host = mmc_priv(mmc);
	काष्ठा sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	काष्ठा xenon_priv *priv = sdhci_pltfm_priv(pltfm_host);

	/* Update card type*/
	priv->init_card_type = card->type;
पूर्ण

अटल पूर्णांक xenon_execute_tuning(काष्ठा mmc_host *mmc, u32 opcode)
अणु
	काष्ठा sdhci_host *host = mmc_priv(mmc);

	अगर (host->timing == MMC_TIMING_UHS_DDR50 ||
		host->timing == MMC_TIMING_MMC_DDR52)
		वापस 0;

	/*
	 * Currently क्रमce Xenon driver back to support mode 1 only,
	 * even though Xenon might claim to support mode 2 or mode 3.
	 * It requires more समय to test mode 2/mode 3 on more platक्रमms.
	 */
	अगर (host->tuning_mode != SDHCI_TUNING_MODE_1)
		xenon_retune_setup(host);

	वापस sdhci_execute_tuning(mmc, opcode);
पूर्ण

अटल व्योम xenon_enable_sdio_irq(काष्ठा mmc_host *mmc, पूर्णांक enable)
अणु
	काष्ठा sdhci_host *host = mmc_priv(mmc);
	काष्ठा sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	काष्ठा xenon_priv *priv = sdhci_pltfm_priv(pltfm_host);
	u32 reg;
	u8 sdhc_id = priv->sdhc_id;

	sdhci_enable_sdio_irq(mmc, enable);

	अगर (enable) अणु
		/*
		 * Set SDIO Card Inserted indication
		 * to enable detecting SDIO async irq.
		 */
		reg = sdhci_पढ़ोl(host, XENON_SYS_CFG_INFO);
		reg |= (1 << (sdhc_id + XENON_SLOT_TYPE_SDIO_SHIFT));
		sdhci_ग_लिखोl(host, reg, XENON_SYS_CFG_INFO);
	पूर्ण अन्यथा अणु
		/* Clear SDIO Card Inserted indication */
		reg = sdhci_पढ़ोl(host, XENON_SYS_CFG_INFO);
		reg &= ~(1 << (sdhc_id + XENON_SLOT_TYPE_SDIO_SHIFT));
		sdhci_ग_लिखोl(host, reg, XENON_SYS_CFG_INFO);
	पूर्ण
पूर्ण

अटल व्योम xenon_replace_mmc_host_ops(काष्ठा sdhci_host *host)
अणु
	host->mmc_host_ops.set_ios = xenon_set_ios;
	host->mmc_host_ops.start_संकेत_voltage_चयन =
			xenon_start_संकेत_voltage_चयन;
	host->mmc_host_ops.init_card = xenon_init_card;
	host->mmc_host_ops.execute_tuning = xenon_execute_tuning;
	host->mmc_host_ops.enable_sdio_irq = xenon_enable_sdio_irq;
पूर्ण

/*
 * Parse Xenon specअगरic DT properties:
 * sdhc-id: the index of current SDHC.
 *	    Refer to XENON_SYS_CFG_INFO रेजिस्टर
 * tun-count: the पूर्णांकerval between re-tuning
 */
अटल पूर्णांक xenon_probe_params(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा sdhci_host *host = platक्रमm_get_drvdata(pdev);
	काष्ठा mmc_host *mmc = host->mmc;
	काष्ठा sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	काष्ठा xenon_priv *priv = sdhci_pltfm_priv(pltfm_host);
	u32 sdhc_id, nr_sdhc;
	u32 tuning_count;

	/* Disable HS200 on Armada AP806 */
	अगर (priv->hw_version == XENON_AP806)
		host->quirks2 |= SDHCI_QUIRK2_BROKEN_HS200;

	sdhc_id = 0x0;
	अगर (!device_property_पढ़ो_u32(dev, "marvell,xenon-sdhc-id", &sdhc_id)) अणु
		nr_sdhc = sdhci_पढ़ोl(host, XENON_SYS_CFG_INFO);
		nr_sdhc &= XENON_NR_SUPPORTED_SLOT_MASK;
		अगर (unlikely(sdhc_id > nr_sdhc)) अणु
			dev_err(mmc_dev(mmc), "SDHC Index %d exceeds Number of SDHCs %d\n",
				sdhc_id, nr_sdhc);
			वापस -EINVAL;
		पूर्ण
	पूर्ण
	priv->sdhc_id = sdhc_id;

	tuning_count = XENON_DEF_TUNING_COUNT;
	अगर (!device_property_पढ़ो_u32(dev, "marvell,xenon-tun-count",
				      &tuning_count)) अणु
		अगर (unlikely(tuning_count >= XENON_TMR_RETUN_NO_PRESENT)) अणु
			dev_err(mmc_dev(mmc), "Wrong Re-tuning Count. Set default value %d\n",
				XENON_DEF_TUNING_COUNT);
			tuning_count = XENON_DEF_TUNING_COUNT;
		पूर्ण
	पूर्ण
	priv->tuning_count = tuning_count;

	वापस xenon_phy_parse_params(dev, host);
पूर्ण

अटल पूर्णांक xenon_sdhc_prepare(काष्ठा sdhci_host *host)
अणु
	काष्ठा sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	काष्ठा xenon_priv *priv = sdhci_pltfm_priv(pltfm_host);
	u8 sdhc_id = priv->sdhc_id;

	/* Enable SDHC */
	xenon_enable_sdhc(host, sdhc_id);

	/* Enable ACG */
	xenon_set_acg(host, true);

	/* Enable Parallel Transfer Mode */
	xenon_enable_sdhc_parallel_tran(host, sdhc_id);

	/* Disable SDCLK-Off-While-Idle beक्रमe card init */
	xenon_set_sdclk_off_idle(host, sdhc_id, false);

	xenon_mask_cmd_conflict_err(host);

	वापस 0;
पूर्ण

अटल व्योम xenon_sdhc_unprepare(काष्ठा sdhci_host *host)
अणु
	काष्ठा sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	काष्ठा xenon_priv *priv = sdhci_pltfm_priv(pltfm_host);
	u8 sdhc_id = priv->sdhc_id;

	/* disable SDHC */
	xenon_disable_sdhc(host, sdhc_id);
पूर्ण

अटल पूर्णांक xenon_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sdhci_pltfm_host *pltfm_host;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा sdhci_host *host;
	काष्ठा xenon_priv *priv;
	पूर्णांक err;

	host = sdhci_pltfm_init(pdev, &sdhci_xenon_pdata,
				माप(काष्ठा xenon_priv));
	अगर (IS_ERR(host))
		वापस PTR_ERR(host);

	pltfm_host = sdhci_priv(host);
	priv = sdhci_pltfm_priv(pltfm_host);

	priv->hw_version = (अचिन्हित दीर्घ)device_get_match_data(&pdev->dev);

	/*
	 * Link Xenon specअगरic mmc_host_ops function,
	 * to replace standard ones in sdhci_ops.
	 */
	xenon_replace_mmc_host_ops(host);

	अगर (dev->of_node) अणु
		pltfm_host->clk = devm_clk_get(&pdev->dev, "core");
		अगर (IS_ERR(pltfm_host->clk)) अणु
			err = PTR_ERR(pltfm_host->clk);
			dev_err(&pdev->dev, "Failed to setup input clk: %d\n", err);
			जाओ मुक्त_pltfm;
		पूर्ण
		err = clk_prepare_enable(pltfm_host->clk);
		अगर (err)
			जाओ मुक्त_pltfm;

		priv->axi_clk = devm_clk_get(&pdev->dev, "axi");
		अगर (IS_ERR(priv->axi_clk)) अणु
			err = PTR_ERR(priv->axi_clk);
			अगर (err == -EPROBE_DEFER)
				जाओ err_clk;
		पूर्ण अन्यथा अणु
			err = clk_prepare_enable(priv->axi_clk);
			अगर (err)
				जाओ err_clk;
		पूर्ण
	पूर्ण

	err = mmc_of_parse(host->mmc);
	अगर (err)
		जाओ err_clk_axi;

	sdhci_get_property(pdev);

	xenon_set_acg(host, false);

	/* Xenon specअगरic parameters parse */
	err = xenon_probe_params(pdev);
	अगर (err)
		जाओ err_clk_axi;

	err = xenon_sdhc_prepare(host);
	अगर (err)
		जाओ err_clk_axi;

	pm_runसमय_get_noresume(&pdev->dev);
	pm_runसमय_set_active(&pdev->dev);
	pm_runसमय_set_स्वतःsuspend_delay(&pdev->dev, 50);
	pm_runसमय_use_स्वतःsuspend(&pdev->dev);
	pm_runसमय_enable(&pdev->dev);
	pm_suspend_ignore_children(&pdev->dev, 1);

	err = sdhci_add_host(host);
	अगर (err)
		जाओ हटाओ_sdhc;

	pm_runसमय_put_स्वतःsuspend(&pdev->dev);

	वापस 0;

हटाओ_sdhc:
	pm_runसमय_disable(&pdev->dev);
	pm_runसमय_put_noidle(&pdev->dev);
	xenon_sdhc_unprepare(host);
err_clk_axi:
	clk_disable_unprepare(priv->axi_clk);
err_clk:
	clk_disable_unprepare(pltfm_host->clk);
मुक्त_pltfm:
	sdhci_pltfm_मुक्त(pdev);
	वापस err;
पूर्ण

अटल पूर्णांक xenon_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sdhci_host *host = platक्रमm_get_drvdata(pdev);
	काष्ठा sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	काष्ठा xenon_priv *priv = sdhci_pltfm_priv(pltfm_host);

	pm_runसमय_get_sync(&pdev->dev);
	pm_runसमय_disable(&pdev->dev);
	pm_runसमय_put_noidle(&pdev->dev);

	sdhci_हटाओ_host(host, 0);

	xenon_sdhc_unprepare(host);
	clk_disable_unprepare(priv->axi_clk);
	clk_disable_unprepare(pltfm_host->clk);

	sdhci_pltfm_मुक्त(pdev);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक xenon_suspend(काष्ठा device *dev)
अणु
	काष्ठा sdhci_host *host = dev_get_drvdata(dev);
	काष्ठा sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	काष्ठा xenon_priv *priv = sdhci_pltfm_priv(pltfm_host);
	पूर्णांक ret;

	ret = pm_runसमय_क्रमce_suspend(dev);

	priv->restore_needed = true;
	वापस ret;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_PM
अटल पूर्णांक xenon_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा sdhci_host *host = dev_get_drvdata(dev);
	काष्ठा sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	काष्ठा xenon_priv *priv = sdhci_pltfm_priv(pltfm_host);
	पूर्णांक ret;

	ret = sdhci_runसमय_suspend_host(host);
	अगर (ret)
		वापस ret;

	अगर (host->tuning_mode != SDHCI_TUNING_MODE_3)
		mmc_retune_needed(host->mmc);

	clk_disable_unprepare(pltfm_host->clk);
	/*
	 * Need to update the priv->घड़ी here, or when runसमय resume
	 * back, phy करोn't aware the clock change and won't adjust phy
	 * which will cause cmd err
	 */
	priv->घड़ी = 0;
	वापस 0;
पूर्ण

अटल पूर्णांक xenon_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा sdhci_host *host = dev_get_drvdata(dev);
	काष्ठा sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	काष्ठा xenon_priv *priv = sdhci_pltfm_priv(pltfm_host);
	पूर्णांक ret;

	ret = clk_prepare_enable(pltfm_host->clk);
	अगर (ret) अणु
		dev_err(dev, "can't enable mainck\n");
		वापस ret;
	पूर्ण

	अगर (priv->restore_needed) अणु
		ret = xenon_sdhc_prepare(host);
		अगर (ret)
			जाओ out;
		priv->restore_needed = false;
	पूर्ण

	ret = sdhci_runसमय_resume_host(host, 0);
	अगर (ret)
		जाओ out;
	वापस 0;
out:
	clk_disable_unprepare(pltfm_host->clk);
	वापस ret;
पूर्ण
#पूर्ण_अगर /* CONFIG_PM */

अटल स्थिर काष्ठा dev_pm_ops sdhci_xenon_dev_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(xenon_suspend,
				pm_runसमय_क्रमce_resume)
	SET_RUNTIME_PM_OPS(xenon_runसमय_suspend,
			   xenon_runसमय_resume,
			   शून्य)
पूर्ण;

अटल स्थिर काष्ठा of_device_id sdhci_xenon_dt_ids[] = अणु
	अणु .compatible = "marvell,armada-ap806-sdhci", .data = (व्योम *)XENON_AP806पूर्ण,
	अणु .compatible = "marvell,armada-ap807-sdhci", .data = (व्योम *)XENON_AP807पूर्ण,
	अणु .compatible = "marvell,armada-cp110-sdhci", .data =  (व्योम *)XENON_CP110पूर्ण,
	अणु .compatible = "marvell,armada-3700-sdhci", .data =  (व्योम *)XENON_A3700पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, sdhci_xenon_dt_ids);

#अगर_घोषित CONFIG_ACPI
अटल स्थिर काष्ठा acpi_device_id sdhci_xenon_acpi_ids[] = अणु
	अणु .id = "MRVL0002", XENON_AP806पूर्ण,
	अणु .id = "MRVL0003", XENON_AP807पूर्ण,
	अणु .id = "MRVL0004", XENON_CP110पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(acpi, sdhci_xenon_acpi_ids);
#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver sdhci_xenon_driver = अणु
	.driver	= अणु
		.name	= "xenon-sdhci",
		.probe_type = PROBE_PREFER_ASYNCHRONOUS,
		.of_match_table = sdhci_xenon_dt_ids,
		.acpi_match_table = ACPI_PTR(sdhci_xenon_acpi_ids),
		.pm = &sdhci_xenon_dev_pm_ops,
	पूर्ण,
	.probe	= xenon_probe,
	.हटाओ	= xenon_हटाओ,
पूर्ण;

module_platक्रमm_driver(sdhci_xenon_driver);

MODULE_DESCRIPTION("SDHCI platform driver for Marvell Xenon SDHC");
MODULE_AUTHOR("Hu Ziji <huziji@marvell.com>");
MODULE_LICENSE("GPL v2");
