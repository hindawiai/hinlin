<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Exynos Specअगरic Extensions क्रम Synopsys DW Mulसमयdia Card Interface driver
 *
 * Copyright (C) 2012, Samsung Electronics Co., Ltd.
 */

#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/clk.h>
#समावेश <linux/mmc/host.h>
#समावेश <linux/mmc/mmc.h>
#समावेश <linux/of.h>
#समावेश <linux/of_gpपन.स>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/slab.h>

#समावेश "dw_mmc.h"
#समावेश "dw_mmc-pltfm.h"
#समावेश "dw_mmc-exynos.h"

/* Variations in Exynos specअगरic dw-mshc controller */
क्रमागत dw_mci_exynos_type अणु
	DW_MCI_TYPE_EXYNOS4210,
	DW_MCI_TYPE_EXYNOS4412,
	DW_MCI_TYPE_EXYNOS5250,
	DW_MCI_TYPE_EXYNOS5420,
	DW_MCI_TYPE_EXYNOS5420_SMU,
	DW_MCI_TYPE_EXYNOS7,
	DW_MCI_TYPE_EXYNOS7_SMU,
पूर्ण;

/* Exynos implementation specअगरic driver निजी data */
काष्ठा dw_mci_exynos_priv_data अणु
	क्रमागत dw_mci_exynos_type		ctrl_type;
	u8				ciu_भाग;
	u32				sdr_timing;
	u32				ddr_timing;
	u32				hs400_timing;
	u32				tuned_sample;
	u32				cur_speed;
	u32				dqs_delay;
	u32				saved_dqs_en;
	u32				saved_strobe_ctrl;
पूर्ण;

अटल काष्ठा dw_mci_exynos_compatible अणु
	अक्षर				*compatible;
	क्रमागत dw_mci_exynos_type		ctrl_type;
पूर्ण exynos_compat[] = अणु
	अणु
		.compatible	= "samsung,exynos4210-dw-mshc",
		.ctrl_type	= DW_MCI_TYPE_EXYNOS4210,
	पूर्ण, अणु
		.compatible	= "samsung,exynos4412-dw-mshc",
		.ctrl_type	= DW_MCI_TYPE_EXYNOS4412,
	पूर्ण, अणु
		.compatible	= "samsung,exynos5250-dw-mshc",
		.ctrl_type	= DW_MCI_TYPE_EXYNOS5250,
	पूर्ण, अणु
		.compatible	= "samsung,exynos5420-dw-mshc",
		.ctrl_type	= DW_MCI_TYPE_EXYNOS5420,
	पूर्ण, अणु
		.compatible	= "samsung,exynos5420-dw-mshc-smu",
		.ctrl_type	= DW_MCI_TYPE_EXYNOS5420_SMU,
	पूर्ण, अणु
		.compatible	= "samsung,exynos7-dw-mshc",
		.ctrl_type	= DW_MCI_TYPE_EXYNOS7,
	पूर्ण, अणु
		.compatible	= "samsung,exynos7-dw-mshc-smu",
		.ctrl_type	= DW_MCI_TYPE_EXYNOS7_SMU,
	पूर्ण,
पूर्ण;

अटल अंतरभूत u8 dw_mci_exynos_get_ciu_भाग(काष्ठा dw_mci *host)
अणु
	काष्ठा dw_mci_exynos_priv_data *priv = host->priv;

	अगर (priv->ctrl_type == DW_MCI_TYPE_EXYNOS4412)
		वापस EXYNOS4412_FIXED_CIU_CLK_DIV;
	अन्यथा अगर (priv->ctrl_type == DW_MCI_TYPE_EXYNOS4210)
		वापस EXYNOS4210_FIXED_CIU_CLK_DIV;
	अन्यथा अगर (priv->ctrl_type == DW_MCI_TYPE_EXYNOS7 ||
			priv->ctrl_type == DW_MCI_TYPE_EXYNOS7_SMU)
		वापस SDMMC_CLKSEL_GET_DIV(mci_पढ़ोl(host, CLKSEL64)) + 1;
	अन्यथा
		वापस SDMMC_CLKSEL_GET_DIV(mci_पढ़ोl(host, CLKSEL)) + 1;
पूर्ण

अटल व्योम dw_mci_exynos_config_smu(काष्ठा dw_mci *host)
अणु
	काष्ठा dw_mci_exynos_priv_data *priv = host->priv;

	/*
	 * If Exynos is provided the Security management,
	 * set क्रम non-ecryption mode at this समय.
	 */
	अगर (priv->ctrl_type == DW_MCI_TYPE_EXYNOS5420_SMU ||
		priv->ctrl_type == DW_MCI_TYPE_EXYNOS7_SMU) अणु
		mci_ग_लिखोl(host, MPSBEGIN0, 0);
		mci_ग_लिखोl(host, MPSEND0, SDMMC_ENDING_SEC_NR_MAX);
		mci_ग_लिखोl(host, MPSCTRL0, SDMMC_MPSCTRL_SECURE_WRITE_BIT |
			   SDMMC_MPSCTRL_NON_SECURE_READ_BIT |
			   SDMMC_MPSCTRL_VALID |
			   SDMMC_MPSCTRL_NON_SECURE_WRITE_BIT);
	पूर्ण
पूर्ण

अटल पूर्णांक dw_mci_exynos_priv_init(काष्ठा dw_mci *host)
अणु
	काष्ठा dw_mci_exynos_priv_data *priv = host->priv;

	dw_mci_exynos_config_smu(host);

	अगर (priv->ctrl_type >= DW_MCI_TYPE_EXYNOS5420) अणु
		priv->saved_strobe_ctrl = mci_पढ़ोl(host, HS400_DLINE_CTRL);
		priv->saved_dqs_en = mci_पढ़ोl(host, HS400_DQS_EN);
		priv->saved_dqs_en |= AXI_NON_BLOCKING_WR;
		mci_ग_लिखोl(host, HS400_DQS_EN, priv->saved_dqs_en);
		अगर (!priv->dqs_delay)
			priv->dqs_delay =
				DQS_CTRL_GET_RD_DELAY(priv->saved_strobe_ctrl);
	पूर्ण

	host->bus_hz /= (priv->ciu_भाग + 1);

	वापस 0;
पूर्ण

अटल व्योम dw_mci_exynos_set_clksel_timing(काष्ठा dw_mci *host, u32 timing)
अणु
	काष्ठा dw_mci_exynos_priv_data *priv = host->priv;
	u32 clksel;

	अगर (priv->ctrl_type == DW_MCI_TYPE_EXYNOS7 ||
		priv->ctrl_type == DW_MCI_TYPE_EXYNOS7_SMU)
		clksel = mci_पढ़ोl(host, CLKSEL64);
	अन्यथा
		clksel = mci_पढ़ोl(host, CLKSEL);

	clksel = (clksel & ~SDMMC_CLKSEL_TIMING_MASK) | timing;

	अगर (priv->ctrl_type == DW_MCI_TYPE_EXYNOS7 ||
		priv->ctrl_type == DW_MCI_TYPE_EXYNOS7_SMU)
		mci_ग_लिखोl(host, CLKSEL64, clksel);
	अन्यथा
		mci_ग_लिखोl(host, CLKSEL, clksel);

	/*
	 * Exynos4412 and Exynos5250 extends the use of CMD रेजिस्टर with the
	 * use of bit 29 (which is reserved on standard MSHC controllers) क्रम
	 * optionally bypassing the HOLD रेजिस्टर क्रम command and data. The
	 * HOLD रेजिस्टर should be bypassed in हाल there is no phase shअगरt
	 * applied on CMD/DATA that is sent to the card.
	 */
	अगर (!SDMMC_CLKSEL_GET_DRV_WD3(clksel) && host->slot)
		set_bit(DW_MMC_CARD_NO_USE_HOLD, &host->slot->flags);
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक dw_mci_exynos_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा dw_mci *host = dev_get_drvdata(dev);
	पूर्णांक ret;

	ret = dw_mci_runसमय_resume(dev);
	अगर (ret)
		वापस ret;

	dw_mci_exynos_config_smu(host);

	वापस ret;
पूर्ण
#पूर्ण_अगर /* CONFIG_PM */

#अगर_घोषित CONFIG_PM_SLEEP
/**
 * dw_mci_exynos_suspend_noirq - Exynos-specअगरic suspend code
 * @dev: Device to suspend (this device)
 *
 * This ensures that device will be in runसमय active state in
 * dw_mci_exynos_resume_noirq after calling pm_runसमय_क्रमce_resume()
 */
अटल पूर्णांक dw_mci_exynos_suspend_noirq(काष्ठा device *dev)
अणु
	pm_runसमय_get_noresume(dev);
	वापस pm_runसमय_क्रमce_suspend(dev);
पूर्ण

/**
 * dw_mci_exynos_resume_noirq - Exynos-specअगरic resume code
 * @dev: Device to resume (this device)
 *
 * On exynos5420 there is a silicon errata that will someबार leave the
 * WAKEUP_INT bit in the CLKSEL रेजिस्टर निश्चितed.  This bit is 1 to indicate
 * that it fired and we can clear it by writing a 1 back.  Clear it to prevent
 * पूर्णांकerrupts from going off स्थिरantly.
 *
 * We run this code on all exynos variants because it करोesn't hurt.
 */
अटल पूर्णांक dw_mci_exynos_resume_noirq(काष्ठा device *dev)
अणु
	काष्ठा dw_mci *host = dev_get_drvdata(dev);
	काष्ठा dw_mci_exynos_priv_data *priv = host->priv;
	u32 clksel;
	पूर्णांक ret;

	ret = pm_runसमय_क्रमce_resume(dev);
	अगर (ret)
		वापस ret;

	अगर (priv->ctrl_type == DW_MCI_TYPE_EXYNOS7 ||
		priv->ctrl_type == DW_MCI_TYPE_EXYNOS7_SMU)
		clksel = mci_पढ़ोl(host, CLKSEL64);
	अन्यथा
		clksel = mci_पढ़ोl(host, CLKSEL);

	अगर (clksel & SDMMC_CLKSEL_WAKEUP_INT) अणु
		अगर (priv->ctrl_type == DW_MCI_TYPE_EXYNOS7 ||
			priv->ctrl_type == DW_MCI_TYPE_EXYNOS7_SMU)
			mci_ग_लिखोl(host, CLKSEL64, clksel);
		अन्यथा
			mci_ग_लिखोl(host, CLKSEL, clksel);
	पूर्ण

	pm_runसमय_put(dev);

	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_PM_SLEEP */

अटल व्योम dw_mci_exynos_config_hs400(काष्ठा dw_mci *host, u32 timing)
अणु
	काष्ठा dw_mci_exynos_priv_data *priv = host->priv;
	u32 dqs, strobe;

	/*
	 * Not supported to configure रेजिस्टर
	 * related to HS400
	 */
	अगर (priv->ctrl_type < DW_MCI_TYPE_EXYNOS5420) अणु
		अगर (timing == MMC_TIMING_MMC_HS400)
			dev_warn(host->dev,
				 "cannot configure HS400, unsupported chipset\n");
		वापस;
	पूर्ण

	dqs = priv->saved_dqs_en;
	strobe = priv->saved_strobe_ctrl;

	अगर (timing == MMC_TIMING_MMC_HS400) अणु
		dqs |= DATA_STROBE_EN;
		strobe = DQS_CTRL_RD_DELAY(strobe, priv->dqs_delay);
	पूर्ण अन्यथा अगर (timing == MMC_TIMING_UHS_SDR104) अणु
		dqs &= 0xffffff00;
	पूर्ण अन्यथा अणु
		dqs &= ~DATA_STROBE_EN;
	पूर्ण

	mci_ग_लिखोl(host, HS400_DQS_EN, dqs);
	mci_ग_लिखोl(host, HS400_DLINE_CTRL, strobe);
पूर्ण

अटल व्योम dw_mci_exynos_adjust_घड़ी(काष्ठा dw_mci *host, अचिन्हित पूर्णांक wanted)
अणु
	काष्ठा dw_mci_exynos_priv_data *priv = host->priv;
	अचिन्हित दीर्घ actual;
	u8 भाग;
	पूर्णांक ret;
	/*
	 * Don't care अगर wanted घड़ी is zero or
	 * ciu घड़ी is unavailable
	 */
	अगर (!wanted || IS_ERR(host->ciu_clk))
		वापस;

	/* Guaranteed minimum frequency क्रम cclkin */
	अगर (wanted < EXYNOS_CCLKIN_MIN)
		wanted = EXYNOS_CCLKIN_MIN;

	अगर (wanted == priv->cur_speed)
		वापस;

	भाग = dw_mci_exynos_get_ciu_भाग(host);
	ret = clk_set_rate(host->ciu_clk, wanted * भाग);
	अगर (ret)
		dev_warn(host->dev,
			"failed to set clk-rate %u error: %d\n",
			wanted * भाग, ret);
	actual = clk_get_rate(host->ciu_clk);
	host->bus_hz = actual / भाग;
	priv->cur_speed = wanted;
	host->current_speed = 0;
पूर्ण

अटल व्योम dw_mci_exynos_set_ios(काष्ठा dw_mci *host, काष्ठा mmc_ios *ios)
अणु
	काष्ठा dw_mci_exynos_priv_data *priv = host->priv;
	अचिन्हित पूर्णांक wanted = ios->घड़ी;
	u32 timing = ios->timing, clksel;

	चयन (timing) अणु
	हाल MMC_TIMING_MMC_HS400:
		/* Update tuned sample timing */
		clksel = SDMMC_CLKSEL_UP_SAMPLE(
				priv->hs400_timing, priv->tuned_sample);
		wanted <<= 1;
		अवरोध;
	हाल MMC_TIMING_MMC_DDR52:
		clksel = priv->ddr_timing;
		/* Should be द्विगुन rate क्रम DDR mode */
		अगर (ios->bus_width == MMC_BUS_WIDTH_8)
			wanted <<= 1;
		अवरोध;
	हाल MMC_TIMING_UHS_SDR104:
	हाल MMC_TIMING_UHS_SDR50:
		clksel = (priv->sdr_timing & 0xfff8ffff) |
			(priv->ciu_भाग << 16);
		अवरोध;
	हाल MMC_TIMING_UHS_DDR50:
		clksel = (priv->ddr_timing & 0xfff8ffff) |
			(priv->ciu_भाग << 16);
		अवरोध;
	शेष:
		clksel = priv->sdr_timing;
	पूर्ण

	/* Set घड़ी timing क्रम the requested speed mode*/
	dw_mci_exynos_set_clksel_timing(host, clksel);

	/* Configure setting क्रम HS400 */
	dw_mci_exynos_config_hs400(host, timing);

	/* Configure घड़ी rate */
	dw_mci_exynos_adjust_घड़ी(host, wanted);
पूर्ण

अटल पूर्णांक dw_mci_exynos_parse_dt(काष्ठा dw_mci *host)
अणु
	काष्ठा dw_mci_exynos_priv_data *priv;
	काष्ठा device_node *np = host->dev->of_node;
	u32 timing[2];
	u32 भाग = 0;
	पूर्णांक idx;
	पूर्णांक ret;

	priv = devm_kzalloc(host->dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	क्रम (idx = 0; idx < ARRAY_SIZE(exynos_compat); idx++) अणु
		अगर (of_device_is_compatible(np, exynos_compat[idx].compatible))
			priv->ctrl_type = exynos_compat[idx].ctrl_type;
	पूर्ण

	अगर (priv->ctrl_type == DW_MCI_TYPE_EXYNOS4412)
		priv->ciu_भाग = EXYNOS4412_FIXED_CIU_CLK_DIV - 1;
	अन्यथा अगर (priv->ctrl_type == DW_MCI_TYPE_EXYNOS4210)
		priv->ciu_भाग = EXYNOS4210_FIXED_CIU_CLK_DIV - 1;
	अन्यथा अणु
		of_property_पढ़ो_u32(np, "samsung,dw-mshc-ciu-div", &भाग);
		priv->ciu_भाग = भाग;
	पूर्ण

	ret = of_property_पढ़ो_u32_array(np,
			"samsung,dw-mshc-sdr-timing", timing, 2);
	अगर (ret)
		वापस ret;

	priv->sdr_timing = SDMMC_CLKSEL_TIMING(timing[0], timing[1], भाग);

	ret = of_property_पढ़ो_u32_array(np,
			"samsung,dw-mshc-ddr-timing", timing, 2);
	अगर (ret)
		वापस ret;

	priv->ddr_timing = SDMMC_CLKSEL_TIMING(timing[0], timing[1], भाग);

	ret = of_property_पढ़ो_u32_array(np,
			"samsung,dw-mshc-hs400-timing", timing, 2);
	अगर (!ret && of_property_पढ़ो_u32(np,
				"samsung,read-strobe-delay", &priv->dqs_delay))
		dev_dbg(host->dev,
			"read-strobe-delay is not found, assuming usage of default value\n");

	priv->hs400_timing = SDMMC_CLKSEL_TIMING(timing[0], timing[1],
						HS400_FIXED_CIU_CLK_DIV);
	host->priv = priv;
	वापस 0;
पूर्ण

अटल अंतरभूत u8 dw_mci_exynos_get_clksmpl(काष्ठा dw_mci *host)
अणु
	काष्ठा dw_mci_exynos_priv_data *priv = host->priv;

	अगर (priv->ctrl_type == DW_MCI_TYPE_EXYNOS7 ||
		priv->ctrl_type == DW_MCI_TYPE_EXYNOS7_SMU)
		वापस SDMMC_CLKSEL_CCLK_SAMPLE(mci_पढ़ोl(host, CLKSEL64));
	अन्यथा
		वापस SDMMC_CLKSEL_CCLK_SAMPLE(mci_पढ़ोl(host, CLKSEL));
पूर्ण

अटल अंतरभूत व्योम dw_mci_exynos_set_clksmpl(काष्ठा dw_mci *host, u8 sample)
अणु
	u32 clksel;
	काष्ठा dw_mci_exynos_priv_data *priv = host->priv;

	अगर (priv->ctrl_type == DW_MCI_TYPE_EXYNOS7 ||
		priv->ctrl_type == DW_MCI_TYPE_EXYNOS7_SMU)
		clksel = mci_पढ़ोl(host, CLKSEL64);
	अन्यथा
		clksel = mci_पढ़ोl(host, CLKSEL);
	clksel = SDMMC_CLKSEL_UP_SAMPLE(clksel, sample);
	अगर (priv->ctrl_type == DW_MCI_TYPE_EXYNOS7 ||
		priv->ctrl_type == DW_MCI_TYPE_EXYNOS7_SMU)
		mci_ग_लिखोl(host, CLKSEL64, clksel);
	अन्यथा
		mci_ग_लिखोl(host, CLKSEL, clksel);
पूर्ण

अटल अंतरभूत u8 dw_mci_exynos_move_next_clksmpl(काष्ठा dw_mci *host)
अणु
	काष्ठा dw_mci_exynos_priv_data *priv = host->priv;
	u32 clksel;
	u8 sample;

	अगर (priv->ctrl_type == DW_MCI_TYPE_EXYNOS7 ||
		priv->ctrl_type == DW_MCI_TYPE_EXYNOS7_SMU)
		clksel = mci_पढ़ोl(host, CLKSEL64);
	अन्यथा
		clksel = mci_पढ़ोl(host, CLKSEL);

	sample = (clksel + 1) & 0x7;
	clksel = SDMMC_CLKSEL_UP_SAMPLE(clksel, sample);

	अगर (priv->ctrl_type == DW_MCI_TYPE_EXYNOS7 ||
		priv->ctrl_type == DW_MCI_TYPE_EXYNOS7_SMU)
		mci_ग_लिखोl(host, CLKSEL64, clksel);
	अन्यथा
		mci_ग_लिखोl(host, CLKSEL, clksel);

	वापस sample;
पूर्ण

अटल s8 dw_mci_exynos_get_best_clksmpl(u8 candiates)
अणु
	स्थिर u8 iter = 8;
	u8 __c;
	s8 i, loc = -1;

	क्रम (i = 0; i < iter; i++) अणु
		__c = ror8(candiates, i);
		अगर ((__c & 0xc7) == 0xc7) अणु
			loc = i;
			जाओ out;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < iter; i++) अणु
		__c = ror8(candiates, i);
		अगर ((__c & 0x83) == 0x83) अणु
			loc = i;
			जाओ out;
		पूर्ण
	पूर्ण

out:
	वापस loc;
पूर्ण

अटल पूर्णांक dw_mci_exynos_execute_tuning(काष्ठा dw_mci_slot *slot, u32 opcode)
अणु
	काष्ठा dw_mci *host = slot->host;
	काष्ठा dw_mci_exynos_priv_data *priv = host->priv;
	काष्ठा mmc_host *mmc = slot->mmc;
	u8 start_smpl, smpl, candiates = 0;
	s8 found;
	पूर्णांक ret = 0;

	start_smpl = dw_mci_exynos_get_clksmpl(host);

	करो अणु
		mci_ग_लिखोl(host, TMOUT, ~0);
		smpl = dw_mci_exynos_move_next_clksmpl(host);

		अगर (!mmc_send_tuning(mmc, opcode, शून्य))
			candiates |= (1 << smpl);

	पूर्ण जबतक (start_smpl != smpl);

	found = dw_mci_exynos_get_best_clksmpl(candiates);
	अगर (found >= 0) अणु
		dw_mci_exynos_set_clksmpl(host, found);
		priv->tuned_sample = found;
	पूर्ण अन्यथा अणु
		ret = -EIO;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक dw_mci_exynos_prepare_hs400_tuning(काष्ठा dw_mci *host,
					काष्ठा mmc_ios *ios)
अणु
	काष्ठा dw_mci_exynos_priv_data *priv = host->priv;

	dw_mci_exynos_set_clksel_timing(host, priv->hs400_timing);
	dw_mci_exynos_adjust_घड़ी(host, (ios->घड़ी) << 1);

	वापस 0;
पूर्ण

/* Common capabilities of Exynos4/Exynos5 SoC */
अटल अचिन्हित दीर्घ exynos_dwmmc_caps[4] = अणु
	MMC_CAP_1_8V_DDR | MMC_CAP_8_BIT_DATA | MMC_CAP_CMD23,
	MMC_CAP_CMD23,
	MMC_CAP_CMD23,
	MMC_CAP_CMD23,
पूर्ण;

अटल स्थिर काष्ठा dw_mci_drv_data exynos_drv_data = अणु
	.caps			= exynos_dwmmc_caps,
	.num_caps		= ARRAY_SIZE(exynos_dwmmc_caps),
	.init			= dw_mci_exynos_priv_init,
	.set_ios		= dw_mci_exynos_set_ios,
	.parse_dt		= dw_mci_exynos_parse_dt,
	.execute_tuning		= dw_mci_exynos_execute_tuning,
	.prepare_hs400_tuning	= dw_mci_exynos_prepare_hs400_tuning,
पूर्ण;

अटल स्थिर काष्ठा of_device_id dw_mci_exynos_match[] = अणु
	अणु .compatible = "samsung,exynos4412-dw-mshc",
			.data = &exynos_drv_data, पूर्ण,
	अणु .compatible = "samsung,exynos5250-dw-mshc",
			.data = &exynos_drv_data, पूर्ण,
	अणु .compatible = "samsung,exynos5420-dw-mshc",
			.data = &exynos_drv_data, पूर्ण,
	अणु .compatible = "samsung,exynos5420-dw-mshc-smu",
			.data = &exynos_drv_data, पूर्ण,
	अणु .compatible = "samsung,exynos7-dw-mshc",
			.data = &exynos_drv_data, पूर्ण,
	अणु .compatible = "samsung,exynos7-dw-mshc-smu",
			.data = &exynos_drv_data, पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, dw_mci_exynos_match);

अटल पूर्णांक dw_mci_exynos_probe(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा dw_mci_drv_data *drv_data;
	स्थिर काष्ठा of_device_id *match;
	पूर्णांक ret;

	match = of_match_node(dw_mci_exynos_match, pdev->dev.of_node);
	drv_data = match->data;

	pm_runसमय_get_noresume(&pdev->dev);
	pm_runसमय_set_active(&pdev->dev);
	pm_runसमय_enable(&pdev->dev);

	ret = dw_mci_pltfm_रेजिस्टर(pdev, drv_data);
	अगर (ret) अणु
		pm_runसमय_disable(&pdev->dev);
		pm_runसमय_set_suspended(&pdev->dev);
		pm_runसमय_put_noidle(&pdev->dev);

		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक dw_mci_exynos_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	pm_runसमय_disable(&pdev->dev);
	pm_runसमय_set_suspended(&pdev->dev);
	pm_runसमय_put_noidle(&pdev->dev);

	वापस dw_mci_pltfm_हटाओ(pdev);
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops dw_mci_exynos_pmops = अणु
	SET_NOIRQ_SYSTEM_SLEEP_PM_OPS(dw_mci_exynos_suspend_noirq,
				      dw_mci_exynos_resume_noirq)
	SET_RUNTIME_PM_OPS(dw_mci_runसमय_suspend,
			   dw_mci_exynos_runसमय_resume,
			   शून्य)
पूर्ण;

अटल काष्ठा platक्रमm_driver dw_mci_exynos_pltfm_driver = अणु
	.probe		= dw_mci_exynos_probe,
	.हटाओ		= dw_mci_exynos_हटाओ,
	.driver		= अणु
		.name		= "dwmmc_exynos",
		.probe_type	= PROBE_PREFER_ASYNCHRONOUS,
		.of_match_table	= dw_mci_exynos_match,
		.pm		= &dw_mci_exynos_pmops,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(dw_mci_exynos_pltfm_driver);

MODULE_DESCRIPTION("Samsung Specific DW-MSHC Driver Extension");
MODULE_AUTHOR("Thomas Abraham <thomas.ab@samsung.com");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:dwmmc_exynos");
