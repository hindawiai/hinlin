<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * sdhci_am654.c - SDHCI driver क्रम TI's AM654 SOCs
 *
 * Copyright (C) 2018 Texas Instruments Incorporated - https://www.ti.com
 *
 */
#समावेश <linux/clk.h>
#समावेश <linux/iopoll.h>
#समावेश <linux/of.h>
#समावेश <linux/module.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/property.h>
#समावेश <linux/regmap.h>
#समावेश <linux/sys_soc.h>

#समावेश "cqhci.h"
#समावेश "sdhci-pltfm.h"

/* CTL_CFG Registers */
#घोषणा CTL_CFG_2		0x14
#घोषणा CTL_CFG_3		0x18

#घोषणा SLOTTYPE_MASK		GENMASK(31, 30)
#घोषणा SLOTTYPE_EMBEDDED	BIT(30)
#घोषणा TUNINGFORSDR50_MASK	BIT(13)

/* PHY Registers */
#घोषणा PHY_CTRL1	0x100
#घोषणा PHY_CTRL2	0x104
#घोषणा PHY_CTRL3	0x108
#घोषणा PHY_CTRL4	0x10C
#घोषणा PHY_CTRL5	0x110
#घोषणा PHY_CTRL6	0x114
#घोषणा PHY_STAT1	0x130
#घोषणा PHY_STAT2	0x134

#घोषणा IOMUX_ENABLE_SHIFT	31
#घोषणा IOMUX_ENABLE_MASK	BIT(IOMUX_ENABLE_SHIFT)
#घोषणा OTAPDLYENA_SHIFT	20
#घोषणा OTAPDLYENA_MASK		BIT(OTAPDLYENA_SHIFT)
#घोषणा OTAPDLYSEL_SHIFT	12
#घोषणा OTAPDLYSEL_MASK		GENMASK(15, 12)
#घोषणा STRBSEL_SHIFT		24
#घोषणा STRBSEL_4BIT_MASK	GENMASK(27, 24)
#घोषणा STRBSEL_8BIT_MASK	GENMASK(31, 24)
#घोषणा SEL50_SHIFT		8
#घोषणा SEL50_MASK		BIT(SEL50_SHIFT)
#घोषणा SEL100_SHIFT		9
#घोषणा SEL100_MASK		BIT(SEL100_SHIFT)
#घोषणा FREQSEL_SHIFT		8
#घोषणा FREQSEL_MASK		GENMASK(10, 8)
#घोषणा CLKBUFSEL_SHIFT		0
#घोषणा CLKBUFSEL_MASK		GENMASK(2, 0)
#घोषणा DLL_TRIM_ICP_SHIFT	4
#घोषणा DLL_TRIM_ICP_MASK	GENMASK(7, 4)
#घोषणा DR_TY_SHIFT		20
#घोषणा DR_TY_MASK		GENMASK(22, 20)
#घोषणा ENDLL_SHIFT		1
#घोषणा ENDLL_MASK		BIT(ENDLL_SHIFT)
#घोषणा DLLRDY_SHIFT		0
#घोषणा DLLRDY_MASK		BIT(DLLRDY_SHIFT)
#घोषणा PDB_SHIFT		0
#घोषणा PDB_MASK		BIT(PDB_SHIFT)
#घोषणा CALDONE_SHIFT		1
#घोषणा CALDONE_MASK		BIT(CALDONE_SHIFT)
#घोषणा RETRIM_SHIFT		17
#घोषणा RETRIM_MASK		BIT(RETRIM_SHIFT)
#घोषणा SELDLYTXCLK_SHIFT	17
#घोषणा SELDLYTXCLK_MASK	BIT(SELDLYTXCLK_SHIFT)
#घोषणा SELDLYRXCLK_SHIFT	16
#घोषणा SELDLYRXCLK_MASK	BIT(SELDLYRXCLK_SHIFT)
#घोषणा ITAPDLYSEL_SHIFT	0
#घोषणा ITAPDLYSEL_MASK		GENMASK(4, 0)
#घोषणा ITAPDLYENA_SHIFT	8
#घोषणा ITAPDLYENA_MASK		BIT(ITAPDLYENA_SHIFT)
#घोषणा ITAPCHGWIN_SHIFT	9
#घोषणा ITAPCHGWIN_MASK		BIT(ITAPCHGWIN_SHIFT)

#घोषणा DRIVER_STRENGTH_50_OHM	0x0
#घोषणा DRIVER_STRENGTH_33_OHM	0x1
#घोषणा DRIVER_STRENGTH_66_OHM	0x2
#घोषणा DRIVER_STRENGTH_100_OHM	0x3
#घोषणा DRIVER_STRENGTH_40_OHM	0x4

#घोषणा CLOCK_TOO_SLOW_HZ	50000000

/* Command Queue Host Controller Interface Base address */
#घोषणा SDHCI_AM654_CQE_BASE_ADDR 0x200

अटल काष्ठा regmap_config sdhci_am654_regmap_config = अणु
	.reg_bits = 32,
	.val_bits = 32,
	.reg_stride = 4,
	.fast_io = true,
पूर्ण;

काष्ठा timing_data अणु
	स्थिर अक्षर *otap_binding;
	स्थिर अक्षर *itap_binding;
	u32 capability;
पूर्ण;

अटल स्थिर काष्ठा timing_data td[] = अणु
	[MMC_TIMING_LEGACY]	= अणु"ti,otap-del-sel-legacy",
				   "ti,itap-del-sel-legacy",
				   0पूर्ण,
	[MMC_TIMING_MMC_HS]	= अणु"ti,otap-del-sel-mmc-hs",
				   "ti,itap-del-sel-mmc-hs",
				   MMC_CAP_MMC_HIGHSPEEDपूर्ण,
	[MMC_TIMING_SD_HS]	= अणु"ti,otap-del-sel-sd-hs",
				   "ti,itap-del-sel-sd-hs",
				   MMC_CAP_SD_HIGHSPEEDपूर्ण,
	[MMC_TIMING_UHS_SDR12]	= अणु"ti,otap-del-sel-sdr12",
				   "ti,itap-del-sel-sdr12",
				   MMC_CAP_UHS_SDR12पूर्ण,
	[MMC_TIMING_UHS_SDR25]	= अणु"ti,otap-del-sel-sdr25",
				   "ti,itap-del-sel-sdr25",
				   MMC_CAP_UHS_SDR25पूर्ण,
	[MMC_TIMING_UHS_SDR50]	= अणु"ti,otap-del-sel-sdr50",
				   शून्य,
				   MMC_CAP_UHS_SDR50पूर्ण,
	[MMC_TIMING_UHS_SDR104]	= अणु"ti,otap-del-sel-sdr104",
				   शून्य,
				   MMC_CAP_UHS_SDR104पूर्ण,
	[MMC_TIMING_UHS_DDR50]	= अणु"ti,otap-del-sel-ddr50",
				   शून्य,
				   MMC_CAP_UHS_DDR50पूर्ण,
	[MMC_TIMING_MMC_DDR52]	= अणु"ti,otap-del-sel-ddr52",
				   "ti,itap-del-sel-ddr52",
				   MMC_CAP_DDRपूर्ण,
	[MMC_TIMING_MMC_HS200]	= अणु"ti,otap-del-sel-hs200",
				   शून्य,
				   MMC_CAP2_HS200पूर्ण,
	[MMC_TIMING_MMC_HS400]	= अणु"ti,otap-del-sel-hs400",
				   शून्य,
				   MMC_CAP2_HS400पूर्ण,
पूर्ण;

काष्ठा sdhci_am654_data अणु
	काष्ठा regmap *base;
	bool legacy_otapdly;
	पूर्णांक otap_del_sel[ARRAY_SIZE(td)];
	पूर्णांक itap_del_sel[ARRAY_SIZE(td)];
	पूर्णांक clkbuf_sel;
	पूर्णांक trm_icp;
	पूर्णांक drv_strength;
	पूर्णांक strb_sel;
	u32 flags;
पूर्ण;

काष्ठा sdhci_am654_driver_data अणु
	स्थिर काष्ठा sdhci_pltfm_data *pdata;
	u32 flags;
#घोषणा IOMUX_PRESENT	(1 << 0)
#घोषणा FREQSEL_2_BIT	(1 << 1)
#घोषणा STRBSEL_4_BIT	(1 << 2)
#घोषणा DLL_PRESENT	(1 << 3)
#घोषणा DLL_CALIB	(1 << 4)
पूर्ण;

अटल व्योम sdhci_am654_setup_dll(काष्ठा sdhci_host *host, अचिन्हित पूर्णांक घड़ी)
अणु
	काष्ठा sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	काष्ठा sdhci_am654_data *sdhci_am654 = sdhci_pltfm_priv(pltfm_host);
	पूर्णांक sel50, sel100, freqsel;
	u32 mask, val;
	पूर्णांक ret;

	/* Disable delay chain mode */
	regmap_update_bits(sdhci_am654->base, PHY_CTRL5,
			   SELDLYTXCLK_MASK | SELDLYRXCLK_MASK, 0);

	अगर (sdhci_am654->flags & FREQSEL_2_BIT) अणु
		चयन (घड़ी) अणु
		हाल 200000000:
			sel50 = 0;
			sel100 = 0;
			अवरोध;
		हाल 100000000:
			sel50 = 0;
			sel100 = 1;
			अवरोध;
		शेष:
			sel50 = 1;
			sel100 = 0;
		पूर्ण

		/* Configure PHY DLL frequency */
		mask = SEL50_MASK | SEL100_MASK;
		val = (sel50 << SEL50_SHIFT) | (sel100 << SEL100_SHIFT);
		regmap_update_bits(sdhci_am654->base, PHY_CTRL5, mask, val);

	पूर्ण अन्यथा अणु
		चयन (घड़ी) अणु
		हाल 200000000:
			freqsel = 0x0;
			अवरोध;
		शेष:
			freqsel = 0x4;
		पूर्ण

		regmap_update_bits(sdhci_am654->base, PHY_CTRL5, FREQSEL_MASK,
				   freqsel << FREQSEL_SHIFT);
	पूर्ण
	/* Configure DLL TRIM */
	mask = DLL_TRIM_ICP_MASK;
	val = sdhci_am654->trm_icp << DLL_TRIM_ICP_SHIFT;

	/* Configure DLL driver strength */
	mask |= DR_TY_MASK;
	val |= sdhci_am654->drv_strength << DR_TY_SHIFT;
	regmap_update_bits(sdhci_am654->base, PHY_CTRL1, mask, val);

	/* Enable DLL */
	regmap_update_bits(sdhci_am654->base, PHY_CTRL1, ENDLL_MASK,
			   0x1 << ENDLL_SHIFT);
	/*
	 * Poll क्रम DLL पढ़ोy. Use a one second समयout.
	 * Works in all experiments करोne so far
	 */
	ret = regmap_पढ़ो_poll_समयout(sdhci_am654->base, PHY_STAT1, val,
				       val & DLLRDY_MASK, 1000, 1000000);
	अगर (ret) अणु
		dev_err(mmc_dev(host->mmc), "DLL failed to relock\n");
		वापस;
	पूर्ण
पूर्ण

अटल व्योम sdhci_am654_ग_लिखो_itapdly(काष्ठा sdhci_am654_data *sdhci_am654,
				      u32 itapdly)
अणु
	/* Set ITAPCHGWIN beक्रमe writing to ITAPDLY */
	regmap_update_bits(sdhci_am654->base, PHY_CTRL4, ITAPCHGWIN_MASK,
			   1 << ITAPCHGWIN_SHIFT);
	regmap_update_bits(sdhci_am654->base, PHY_CTRL4, ITAPDLYSEL_MASK,
			   itapdly << ITAPDLYSEL_SHIFT);
	regmap_update_bits(sdhci_am654->base, PHY_CTRL4, ITAPCHGWIN_MASK, 0);
पूर्ण

अटल व्योम sdhci_am654_setup_delay_chain(काष्ठा sdhci_am654_data *sdhci_am654,
					  अचिन्हित अक्षर timing)
अणु
	u32 mask, val;

	regmap_update_bits(sdhci_am654->base, PHY_CTRL1, ENDLL_MASK, 0);

	val = 1 << SELDLYTXCLK_SHIFT | 1 << SELDLYRXCLK_SHIFT;
	mask = SELDLYTXCLK_MASK | SELDLYRXCLK_MASK;
	regmap_update_bits(sdhci_am654->base, PHY_CTRL5, mask, val);

	sdhci_am654_ग_लिखो_itapdly(sdhci_am654,
				  sdhci_am654->itap_del_sel[timing]);
पूर्ण

अटल व्योम sdhci_am654_set_घड़ी(काष्ठा sdhci_host *host, अचिन्हित पूर्णांक घड़ी)
अणु
	काष्ठा sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	काष्ठा sdhci_am654_data *sdhci_am654 = sdhci_pltfm_priv(pltfm_host);
	अचिन्हित अक्षर timing = host->mmc->ios.timing;
	u32 otap_del_sel;
	u32 otap_del_ena;
	u32 mask, val;

	regmap_update_bits(sdhci_am654->base, PHY_CTRL1, ENDLL_MASK, 0);

	sdhci_set_घड़ी(host, घड़ी);

	/* Setup DLL Output TAP delay */
	अगर (sdhci_am654->legacy_otapdly)
		otap_del_sel = sdhci_am654->otap_del_sel[0];
	अन्यथा
		otap_del_sel = sdhci_am654->otap_del_sel[timing];

	otap_del_ena = (timing > MMC_TIMING_UHS_SDR25) ? 1 : 0;

	mask = OTAPDLYENA_MASK | OTAPDLYSEL_MASK;
	val = (otap_del_ena << OTAPDLYENA_SHIFT) |
	      (otap_del_sel << OTAPDLYSEL_SHIFT);

	/* Write to STRBSEL क्रम HS400 speed mode */
	अगर (timing == MMC_TIMING_MMC_HS400) अणु
		अगर (sdhci_am654->flags & STRBSEL_4_BIT)
			mask |= STRBSEL_4BIT_MASK;
		अन्यथा
			mask |= STRBSEL_8BIT_MASK;

		val |= sdhci_am654->strb_sel << STRBSEL_SHIFT;
	पूर्ण

	regmap_update_bits(sdhci_am654->base, PHY_CTRL4, mask, val);

	अगर (timing > MMC_TIMING_UHS_SDR25 && घड़ी >= CLOCK_TOO_SLOW_HZ)
		sdhci_am654_setup_dll(host, घड़ी);
	अन्यथा
		sdhci_am654_setup_delay_chain(sdhci_am654, timing);

	regmap_update_bits(sdhci_am654->base, PHY_CTRL5, CLKBUFSEL_MASK,
			   sdhci_am654->clkbuf_sel);
पूर्ण

अटल व्योम sdhci_j721e_4bit_set_घड़ी(काष्ठा sdhci_host *host,
				       अचिन्हित पूर्णांक घड़ी)
अणु
	काष्ठा sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	काष्ठा sdhci_am654_data *sdhci_am654 = sdhci_pltfm_priv(pltfm_host);
	अचिन्हित अक्षर timing = host->mmc->ios.timing;
	u32 otap_del_sel;
	u32 mask, val;

	/* Setup DLL Output TAP delay */
	अगर (sdhci_am654->legacy_otapdly)
		otap_del_sel = sdhci_am654->otap_del_sel[0];
	अन्यथा
		otap_del_sel = sdhci_am654->otap_del_sel[timing];

	mask = OTAPDLYENA_MASK | OTAPDLYSEL_MASK;
	val = (0x1 << OTAPDLYENA_SHIFT) |
	      (otap_del_sel << OTAPDLYSEL_SHIFT);
	regmap_update_bits(sdhci_am654->base, PHY_CTRL4, mask, val);

	regmap_update_bits(sdhci_am654->base, PHY_CTRL5, CLKBUFSEL_MASK,
			   sdhci_am654->clkbuf_sel);

	sdhci_set_घड़ी(host, घड़ी);
पूर्ण

अटल u8 sdhci_am654_ग_लिखो_घातer_on(काष्ठा sdhci_host *host, u8 val, पूर्णांक reg)
अणु
	ग_लिखोb(val, host->ioaddr + reg);
	usleep_range(1000, 10000);
	वापस पढ़ोb(host->ioaddr + reg);
पूर्ण

#घोषणा MAX_POWER_ON_TIMEOUT	1500000 /* us */
अटल व्योम sdhci_am654_ग_लिखो_b(काष्ठा sdhci_host *host, u8 val, पूर्णांक reg)
अणु
	अचिन्हित अक्षर timing = host->mmc->ios.timing;
	u8 pwr;
	पूर्णांक ret;

	अगर (reg == SDHCI_HOST_CONTROL) अणु
		चयन (timing) अणु
		/*
		 * According to the data manual, HISPD bit
		 * should not be set in these speed modes.
		 */
		हाल MMC_TIMING_SD_HS:
		हाल MMC_TIMING_MMC_HS:
		हाल MMC_TIMING_UHS_SDR12:
		हाल MMC_TIMING_UHS_SDR25:
			val &= ~SDHCI_CTRL_HISPD;
		पूर्ण
	पूर्ण

	ग_लिखोb(val, host->ioaddr + reg);
	अगर (reg == SDHCI_POWER_CONTROL && (val & SDHCI_POWER_ON)) अणु
		/*
		 * Power on will not happen until the card detect debounce
		 * समयr expires. Wait at least 1.5 seconds क्रम the घातer on
		 * bit to be set
		 */
		ret = पढ़ो_poll_समयout(sdhci_am654_ग_लिखो_घातer_on, pwr,
					pwr & SDHCI_POWER_ON, 0,
					MAX_POWER_ON_TIMEOUT, false, host, val,
					reg);
		अगर (ret)
			dev_warn(mmc_dev(host->mmc), "Power on failed\n");
	पूर्ण
पूर्ण

अटल पूर्णांक sdhci_am654_execute_tuning(काष्ठा mmc_host *mmc, u32 opcode)
अणु
	काष्ठा sdhci_host *host = mmc_priv(mmc);
	पूर्णांक err = sdhci_execute_tuning(mmc, opcode);

	अगर (err)
		वापस err;
	/*
	 * Tuning data reमुख्यs in the buffer after tuning.
	 * Do a command and data reset to get rid of it
	 */
	sdhci_reset(host, SDHCI_RESET_CMD | SDHCI_RESET_DATA);

	वापस 0;
पूर्ण

अटल u32 sdhci_am654_cqhci_irq(काष्ठा sdhci_host *host, u32 पूर्णांकmask)
अणु
	पूर्णांक cmd_error = 0;
	पूर्णांक data_error = 0;

	अगर (!sdhci_cqe_irq(host, पूर्णांकmask, &cmd_error, &data_error))
		वापस पूर्णांकmask;

	cqhci_irq(host->mmc, पूर्णांकmask, cmd_error, data_error);

	वापस 0;
पूर्ण

#घोषणा ITAP_MAX	32
अटल पूर्णांक sdhci_am654_platक्रमm_execute_tuning(काष्ठा sdhci_host *host,
					       u32 opcode)
अणु
	काष्ठा sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	काष्ठा sdhci_am654_data *sdhci_am654 = sdhci_pltfm_priv(pltfm_host);
	पूर्णांक cur_val, prev_val = 1, fail_len = 0, pass_winकरोw = 0, pass_len;
	u32 itap;

	/* Enable ITAPDLY */
	regmap_update_bits(sdhci_am654->base, PHY_CTRL4, ITAPDLYENA_MASK,
			   1 << ITAPDLYENA_SHIFT);

	क्रम (itap = 0; itap < ITAP_MAX; itap++) अणु
		sdhci_am654_ग_लिखो_itapdly(sdhci_am654, itap);

		cur_val = !mmc_send_tuning(host->mmc, opcode, शून्य);
		अगर (cur_val && !prev_val)
			pass_winकरोw = itap;

		अगर (!cur_val)
			fail_len++;

		prev_val = cur_val;
	पूर्ण
	/*
	 * Having determined the length of the failing winकरोw and start of
	 * the passing winकरोw calculate the length of the passing winकरोw and
	 * set the final value halfway through it considering the range as a
	 * circular buffer
	 */
	pass_len = ITAP_MAX - fail_len;
	itap = (pass_winकरोw + (pass_len >> 1)) % ITAP_MAX;
	sdhci_am654_ग_लिखो_itapdly(sdhci_am654, itap);

	वापस 0;
पूर्ण

अटल काष्ठा sdhci_ops sdhci_am654_ops = अणु
	.platक्रमm_execute_tuning = sdhci_am654_platक्रमm_execute_tuning,
	.get_max_घड़ी = sdhci_pltfm_clk_get_max_घड़ी,
	.get_समयout_घड़ी = sdhci_pltfm_clk_get_max_घड़ी,
	.set_uhs_संकेतing = sdhci_set_uhs_संकेतing,
	.set_bus_width = sdhci_set_bus_width,
	.set_घातer = sdhci_set_घातer_and_bus_voltage,
	.set_घड़ी = sdhci_am654_set_घड़ी,
	.ग_लिखो_b = sdhci_am654_ग_लिखो_b,
	.irq = sdhci_am654_cqhci_irq,
	.reset = sdhci_reset,
पूर्ण;

अटल स्थिर काष्ठा sdhci_pltfm_data sdhci_am654_pdata = अणु
	.ops = &sdhci_am654_ops,
	.quirks = SDHCI_QUIRK_MULTIBLOCK_READ_ACMD12,
	.quirks2 = SDHCI_QUIRK2_PRESET_VALUE_BROKEN,
पूर्ण;

अटल स्थिर काष्ठा sdhci_am654_driver_data sdhci_am654_sr1_drvdata = अणु
	.pdata = &sdhci_am654_pdata,
	.flags = IOMUX_PRESENT | FREQSEL_2_BIT | STRBSEL_4_BIT | DLL_PRESENT |
		 DLL_CALIB,
पूर्ण;

अटल स्थिर काष्ठा sdhci_am654_driver_data sdhci_am654_drvdata = अणु
	.pdata = &sdhci_am654_pdata,
	.flags = IOMUX_PRESENT | FREQSEL_2_BIT | STRBSEL_4_BIT | DLL_PRESENT,
पूर्ण;

अटल काष्ठा sdhci_ops sdhci_j721e_8bit_ops = अणु
	.platक्रमm_execute_tuning = sdhci_am654_platक्रमm_execute_tuning,
	.get_max_घड़ी = sdhci_pltfm_clk_get_max_घड़ी,
	.get_समयout_घड़ी = sdhci_pltfm_clk_get_max_घड़ी,
	.set_uhs_संकेतing = sdhci_set_uhs_संकेतing,
	.set_bus_width = sdhci_set_bus_width,
	.set_घातer = sdhci_set_घातer_and_bus_voltage,
	.set_घड़ी = sdhci_am654_set_घड़ी,
	.ग_लिखो_b = sdhci_am654_ग_लिखो_b,
	.irq = sdhci_am654_cqhci_irq,
	.reset = sdhci_reset,
पूर्ण;

अटल स्थिर काष्ठा sdhci_pltfm_data sdhci_j721e_8bit_pdata = अणु
	.ops = &sdhci_j721e_8bit_ops,
	.quirks = SDHCI_QUIRK_MULTIBLOCK_READ_ACMD12,
	.quirks2 = SDHCI_QUIRK2_PRESET_VALUE_BROKEN,
पूर्ण;

अटल स्थिर काष्ठा sdhci_am654_driver_data sdhci_j721e_8bit_drvdata = अणु
	.pdata = &sdhci_j721e_8bit_pdata,
	.flags = DLL_PRESENT | DLL_CALIB,
पूर्ण;

अटल काष्ठा sdhci_ops sdhci_j721e_4bit_ops = अणु
	.platक्रमm_execute_tuning = sdhci_am654_platक्रमm_execute_tuning,
	.get_max_घड़ी = sdhci_pltfm_clk_get_max_घड़ी,
	.get_समयout_घड़ी = sdhci_pltfm_clk_get_max_घड़ी,
	.set_uhs_संकेतing = sdhci_set_uhs_संकेतing,
	.set_bus_width = sdhci_set_bus_width,
	.set_घातer = sdhci_set_घातer_and_bus_voltage,
	.set_घड़ी = sdhci_j721e_4bit_set_घड़ी,
	.ग_लिखो_b = sdhci_am654_ग_लिखो_b,
	.irq = sdhci_am654_cqhci_irq,
	.reset = sdhci_reset,
पूर्ण;

अटल स्थिर काष्ठा sdhci_pltfm_data sdhci_j721e_4bit_pdata = अणु
	.ops = &sdhci_j721e_4bit_ops,
	.quirks = SDHCI_QUIRK_MULTIBLOCK_READ_ACMD12,
	.quirks2 = SDHCI_QUIRK2_PRESET_VALUE_BROKEN,
पूर्ण;

अटल स्थिर काष्ठा sdhci_am654_driver_data sdhci_j721e_4bit_drvdata = अणु
	.pdata = &sdhci_j721e_4bit_pdata,
	.flags = IOMUX_PRESENT,
पूर्ण;

अटल स्थिर काष्ठा sdhci_pltfm_data sdhci_am64_8bit_pdata = अणु
	.ops = &sdhci_j721e_8bit_ops,
	.quirks2 = SDHCI_QUIRK2_PRESET_VALUE_BROKEN,
पूर्ण;

अटल स्थिर काष्ठा sdhci_am654_driver_data sdhci_am64_8bit_drvdata = अणु
	.pdata = &sdhci_am64_8bit_pdata,
	.flags = DLL_PRESENT | DLL_CALIB,
पूर्ण;

अटल स्थिर काष्ठा sdhci_pltfm_data sdhci_am64_4bit_pdata = अणु
	.ops = &sdhci_j721e_4bit_ops,
	.quirks2 = SDHCI_QUIRK2_PRESET_VALUE_BROKEN,
पूर्ण;

अटल स्थिर काष्ठा sdhci_am654_driver_data sdhci_am64_4bit_drvdata = अणु
	.pdata = &sdhci_am64_4bit_pdata,
	.flags = IOMUX_PRESENT,
पूर्ण;

अटल स्थिर काष्ठा soc_device_attribute sdhci_am654_devices[] = अणु
	अणु .family = "AM65X",
	  .revision = "SR1.0",
	  .data = &sdhci_am654_sr1_drvdata
	पूर्ण,
	अणु/* sentinel */पूर्ण
पूर्ण;

अटल व्योम sdhci_am654_dumpregs(काष्ठा mmc_host *mmc)
अणु
	sdhci_dumpregs(mmc_priv(mmc));
पूर्ण

अटल स्थिर काष्ठा cqhci_host_ops sdhci_am654_cqhci_ops = अणु
	.enable		= sdhci_cqe_enable,
	.disable	= sdhci_cqe_disable,
	.dumpregs	= sdhci_am654_dumpregs,
पूर्ण;

अटल पूर्णांक sdhci_am654_cqe_add_host(काष्ठा sdhci_host *host)
अणु
	काष्ठा cqhci_host *cq_host;
	पूर्णांक ret;

	cq_host = devm_kzalloc(mmc_dev(host->mmc), माप(काष्ठा cqhci_host),
			       GFP_KERNEL);
	अगर (!cq_host)
		वापस -ENOMEM;

	cq_host->mmio = host->ioaddr + SDHCI_AM654_CQE_BASE_ADDR;
	cq_host->quirks |= CQHCI_QUIRK_SHORT_TXFR_DESC_SZ;
	cq_host->caps |= CQHCI_TASK_DESC_SZ_128;
	cq_host->ops = &sdhci_am654_cqhci_ops;

	host->mmc->caps2 |= MMC_CAP2_CQE;

	ret = cqhci_init(cq_host, host->mmc, 1);

	वापस ret;
पूर्ण

अटल पूर्णांक sdhci_am654_get_otap_delay(काष्ठा sdhci_host *host,
				      काष्ठा sdhci_am654_data *sdhci_am654)
अणु
	काष्ठा device *dev = mmc_dev(host->mmc);
	पूर्णांक i;
	पूर्णांक ret;

	ret = device_property_पढ़ो_u32(dev, td[MMC_TIMING_LEGACY].otap_binding,
				 &sdhci_am654->otap_del_sel[MMC_TIMING_LEGACY]);
	अगर (ret) अणु
		/*
		 * ti,otap-del-sel-legacy is mandatory, look क्रम old binding
		 * अगर not found.
		 */
		ret = device_property_पढ़ो_u32(dev, "ti,otap-del-sel",
					       &sdhci_am654->otap_del_sel[0]);
		अगर (ret) अणु
			dev_err(dev, "Couldn't find otap-del-sel\n");

			वापस ret;
		पूर्ण

		dev_info(dev, "Using legacy binding ti,otap-del-sel\n");
		sdhci_am654->legacy_otapdly = true;

		वापस 0;
	पूर्ण

	क्रम (i = MMC_TIMING_MMC_HS; i <= MMC_TIMING_MMC_HS400; i++) अणु

		ret = device_property_पढ़ो_u32(dev, td[i].otap_binding,
					       &sdhci_am654->otap_del_sel[i]);
		अगर (ret) अणु
			dev_dbg(dev, "Couldn't find %s\n",
				td[i].otap_binding);
			/*
			 * Remove the corresponding capability
			 * अगर an otap-del-sel value is not found
			 */
			अगर (i <= MMC_TIMING_MMC_DDR52)
				host->mmc->caps &= ~td[i].capability;
			अन्यथा
				host->mmc->caps2 &= ~td[i].capability;
		पूर्ण

		अगर (td[i].itap_binding)
			device_property_पढ़ो_u32(dev, td[i].itap_binding,
						 &sdhci_am654->itap_del_sel[i]);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक sdhci_am654_init(काष्ठा sdhci_host *host)
अणु
	काष्ठा sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	काष्ठा sdhci_am654_data *sdhci_am654 = sdhci_pltfm_priv(pltfm_host);
	u32 ctl_cfg_2 = 0;
	u32 mask;
	u32 val;
	पूर्णांक ret;

	/* Reset OTAP to शेष value */
	mask = OTAPDLYENA_MASK | OTAPDLYSEL_MASK;
	regmap_update_bits(sdhci_am654->base, PHY_CTRL4, mask, 0x0);

	अगर (sdhci_am654->flags & DLL_CALIB) अणु
		regmap_पढ़ो(sdhci_am654->base, PHY_STAT1, &val);
		अगर (~val & CALDONE_MASK) अणु
			/* Calibrate IO lines */
			regmap_update_bits(sdhci_am654->base, PHY_CTRL1,
					   PDB_MASK, PDB_MASK);
			ret = regmap_पढ़ो_poll_समयout(sdhci_am654->base,
						       PHY_STAT1, val,
						       val & CALDONE_MASK,
						       1, 20);
			अगर (ret)
				वापस ret;
		पूर्ण
	पूर्ण

	/* Enable pins by setting IO mux to 0 */
	अगर (sdhci_am654->flags & IOMUX_PRESENT)
		regmap_update_bits(sdhci_am654->base, PHY_CTRL1,
				   IOMUX_ENABLE_MASK, 0);

	/* Set slot type based on SD or eMMC */
	अगर (host->mmc->caps & MMC_CAP_NONREMOVABLE)
		ctl_cfg_2 = SLOTTYPE_EMBEDDED;

	regmap_update_bits(sdhci_am654->base, CTL_CFG_2, SLOTTYPE_MASK,
			   ctl_cfg_2);

	/* Enable tuning क्रम SDR50 */
	regmap_update_bits(sdhci_am654->base, CTL_CFG_3, TUNINGFORSDR50_MASK,
			   TUNINGFORSDR50_MASK);

	ret = sdhci_setup_host(host);
	अगर (ret)
		वापस ret;

	ret = sdhci_am654_cqe_add_host(host);
	अगर (ret)
		जाओ err_cleanup_host;

	ret = sdhci_am654_get_otap_delay(host, sdhci_am654);
	अगर (ret)
		जाओ err_cleanup_host;

	ret = __sdhci_add_host(host);
	अगर (ret)
		जाओ err_cleanup_host;

	वापस 0;

err_cleanup_host:
	sdhci_cleanup_host(host);
	वापस ret;
पूर्ण

अटल पूर्णांक sdhci_am654_get_of_property(काष्ठा platक्रमm_device *pdev,
					काष्ठा sdhci_am654_data *sdhci_am654)
अणु
	काष्ठा device *dev = &pdev->dev;
	पूर्णांक drv_strength;
	पूर्णांक ret;

	अगर (sdhci_am654->flags & DLL_PRESENT) अणु
		ret = device_property_पढ़ो_u32(dev, "ti,trm-icp",
					       &sdhci_am654->trm_icp);
		अगर (ret)
			वापस ret;

		ret = device_property_पढ़ो_u32(dev, "ti,driver-strength-ohm",
					       &drv_strength);
		अगर (ret)
			वापस ret;

		चयन (drv_strength) अणु
		हाल 50:
			sdhci_am654->drv_strength = DRIVER_STRENGTH_50_OHM;
			अवरोध;
		हाल 33:
			sdhci_am654->drv_strength = DRIVER_STRENGTH_33_OHM;
			अवरोध;
		हाल 66:
			sdhci_am654->drv_strength = DRIVER_STRENGTH_66_OHM;
			अवरोध;
		हाल 100:
			sdhci_am654->drv_strength = DRIVER_STRENGTH_100_OHM;
			अवरोध;
		हाल 40:
			sdhci_am654->drv_strength = DRIVER_STRENGTH_40_OHM;
			अवरोध;
		शेष:
			dev_err(dev, "Invalid driver strength\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	device_property_पढ़ो_u32(dev, "ti,strobe-sel", &sdhci_am654->strb_sel);
	device_property_पढ़ो_u32(dev, "ti,clkbuf-sel",
				 &sdhci_am654->clkbuf_sel);

	sdhci_get_of_property(pdev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id sdhci_am654_of_match[] = अणु
	अणु
		.compatible = "ti,am654-sdhci-5.1",
		.data = &sdhci_am654_drvdata,
	पूर्ण,
	अणु
		.compatible = "ti,j721e-sdhci-8bit",
		.data = &sdhci_j721e_8bit_drvdata,
	पूर्ण,
	अणु
		.compatible = "ti,j721e-sdhci-4bit",
		.data = &sdhci_j721e_4bit_drvdata,
	पूर्ण,
	अणु
		.compatible = "ti,am64-sdhci-8bit",
		.data = &sdhci_am64_8bit_drvdata,
	पूर्ण,
	अणु
		.compatible = "ti,am64-sdhci-4bit",
		.data = &sdhci_am64_4bit_drvdata,
	पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, sdhci_am654_of_match);

अटल पूर्णांक sdhci_am654_probe(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा sdhci_am654_driver_data *drvdata;
	स्थिर काष्ठा soc_device_attribute *soc;
	काष्ठा sdhci_pltfm_host *pltfm_host;
	काष्ठा sdhci_am654_data *sdhci_am654;
	स्थिर काष्ठा of_device_id *match;
	काष्ठा sdhci_host *host;
	काष्ठा clk *clk_xin;
	काष्ठा device *dev = &pdev->dev;
	व्योम __iomem *base;
	पूर्णांक ret;

	match = of_match_node(sdhci_am654_of_match, pdev->dev.of_node);
	drvdata = match->data;

	/* Update drvdata based on SoC revision */
	soc = soc_device_match(sdhci_am654_devices);
	अगर (soc && soc->data)
		drvdata = soc->data;

	host = sdhci_pltfm_init(pdev, drvdata->pdata, माप(*sdhci_am654));
	अगर (IS_ERR(host))
		वापस PTR_ERR(host);

	pltfm_host = sdhci_priv(host);
	sdhci_am654 = sdhci_pltfm_priv(pltfm_host);
	sdhci_am654->flags = drvdata->flags;

	clk_xin = devm_clk_get(dev, "clk_xin");
	अगर (IS_ERR(clk_xin)) अणु
		dev_err(dev, "clk_xin clock not found.\n");
		ret = PTR_ERR(clk_xin);
		जाओ err_pltfm_मुक्त;
	पूर्ण

	pltfm_host->clk = clk_xin;

	/* Clocks are enabled using pm_runसमय */
	pm_runसमय_enable(dev);
	ret = pm_runसमय_get_sync(dev);
	अगर (ret < 0) अणु
		pm_runसमय_put_noidle(dev);
		जाओ pm_runसमय_disable;
	पूर्ण

	base = devm_platक्रमm_ioremap_resource(pdev, 1);
	अगर (IS_ERR(base)) अणु
		ret = PTR_ERR(base);
		जाओ pm_runसमय_put;
	पूर्ण

	sdhci_am654->base = devm_regmap_init_mmio(dev, base,
						  &sdhci_am654_regmap_config);
	अगर (IS_ERR(sdhci_am654->base)) अणु
		dev_err(dev, "Failed to initialize regmap\n");
		ret = PTR_ERR(sdhci_am654->base);
		जाओ pm_runसमय_put;
	पूर्ण

	ret = sdhci_am654_get_of_property(pdev, sdhci_am654);
	अगर (ret)
		जाओ pm_runसमय_put;

	ret = mmc_of_parse(host->mmc);
	अगर (ret) अणु
		dev_err(dev, "parsing dt failed (%d)\n", ret);
		जाओ pm_runसमय_put;
	पूर्ण

	host->mmc_host_ops.execute_tuning = sdhci_am654_execute_tuning;

	ret = sdhci_am654_init(host);
	अगर (ret)
		जाओ pm_runसमय_put;

	वापस 0;

pm_runसमय_put:
	pm_runसमय_put_sync(dev);
pm_runसमय_disable:
	pm_runसमय_disable(dev);
err_pltfm_मुक्त:
	sdhci_pltfm_मुक्त(pdev);
	वापस ret;
पूर्ण

अटल पूर्णांक sdhci_am654_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sdhci_host *host = platक्रमm_get_drvdata(pdev);
	पूर्णांक ret;

	sdhci_हटाओ_host(host, true);
	ret = pm_runसमय_put_sync(&pdev->dev);
	अगर (ret < 0)
		वापस ret;

	pm_runसमय_disable(&pdev->dev);
	sdhci_pltfm_मुक्त(pdev);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver sdhci_am654_driver = अणु
	.driver = अणु
		.name = "sdhci-am654",
		.probe_type = PROBE_PREFER_ASYNCHRONOUS,
		.of_match_table = sdhci_am654_of_match,
	पूर्ण,
	.probe = sdhci_am654_probe,
	.हटाओ = sdhci_am654_हटाओ,
पूर्ण;

module_platक्रमm_driver(sdhci_am654_driver);

MODULE_DESCRIPTION("Driver for SDHCI Controller on TI's AM654 devices");
MODULE_AUTHOR("Faiz Abbas <faiz_abbas@ti.com>");
MODULE_LICENSE("GPL");
