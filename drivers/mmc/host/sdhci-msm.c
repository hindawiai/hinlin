<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * drivers/mmc/host/sdhci-msm.c - Qualcomm SDHCI Platक्रमm driver
 *
 * Copyright (c) 2013-2014, The Linux Foundation. All rights reserved.
 */

#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/delay.h>
#समावेश <linux/mmc/mmc.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/pm_opp.h>
#समावेश <linux/slab.h>
#समावेश <linux/iopoll.h>
#समावेश <linux/qcom_scm.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/पूर्णांकerconnect.h>
#समावेश <linux/pinctrl/consumer.h>

#समावेश "sdhci-pltfm.h"
#समावेश "cqhci.h"

#घोषणा CORE_MCI_VERSION		0x50
#घोषणा CORE_VERSION_MAJOR_SHIFT	28
#घोषणा CORE_VERSION_MAJOR_MASK		(0xf << CORE_VERSION_MAJOR_SHIFT)
#घोषणा CORE_VERSION_MINOR_MASK		0xff

#घोषणा CORE_MCI_GENERICS		0x70
#घोषणा SWITCHABLE_SIGNALING_VOLTAGE	BIT(29)

#घोषणा HC_MODE_EN		0x1
#घोषणा CORE_POWER		0x0
#घोषणा CORE_SW_RST		BIT(7)
#घोषणा FF_CLK_SW_RST_DIS	BIT(13)

#घोषणा CORE_PWRCTL_BUS_OFF	BIT(0)
#घोषणा CORE_PWRCTL_BUS_ON	BIT(1)
#घोषणा CORE_PWRCTL_IO_LOW	BIT(2)
#घोषणा CORE_PWRCTL_IO_HIGH	BIT(3)
#घोषणा CORE_PWRCTL_BUS_SUCCESS BIT(0)
#घोषणा CORE_PWRCTL_BUS_FAIL    BIT(1)
#घोषणा CORE_PWRCTL_IO_SUCCESS	BIT(2)
#घोषणा CORE_PWRCTL_IO_FAIL     BIT(3)
#घोषणा REQ_BUS_OFF		BIT(0)
#घोषणा REQ_BUS_ON		BIT(1)
#घोषणा REQ_IO_LOW		BIT(2)
#घोषणा REQ_IO_HIGH		BIT(3)
#घोषणा INT_MASK		0xf
#घोषणा MAX_PHASES		16
#घोषणा CORE_DLL_LOCK		BIT(7)
#घोषणा CORE_DDR_DLL_LOCK	BIT(11)
#घोषणा CORE_DLL_EN		BIT(16)
#घोषणा CORE_CDR_EN		BIT(17)
#घोषणा CORE_CK_OUT_EN		BIT(18)
#घोषणा CORE_CDR_EXT_EN		BIT(19)
#घोषणा CORE_DLL_PDN		BIT(29)
#घोषणा CORE_DLL_RST		BIT(30)
#घोषणा CORE_CMD_DAT_TRACK_SEL	BIT(0)

#घोषणा CORE_DDR_CAL_EN		BIT(0)
#घोषणा CORE_FLL_CYCLE_CNT	BIT(18)
#घोषणा CORE_DLL_CLOCK_DISABLE	BIT(21)

#घोषणा DLL_USR_CTL_POR_VAL	0x10800
#घोषणा ENABLE_DLL_LOCK_STATUS	BIT(26)
#घोषणा FINE_TUNE_MODE_EN	BIT(27)
#घोषणा BIAS_OK_SIGNAL		BIT(29)

#घोषणा DLL_CONFIG_3_LOW_FREQ_VAL	0x08
#घोषणा DLL_CONFIG_3_HIGH_FREQ_VAL	0x10

#घोषणा CORE_VENDOR_SPEC_POR_VAL 0xa9c
#घोषणा CORE_CLK_PWRSAVE	BIT(1)
#घोषणा CORE_HC_MCLK_SEL_DFLT	(2 << 8)
#घोषणा CORE_HC_MCLK_SEL_HS400	(3 << 8)
#घोषणा CORE_HC_MCLK_SEL_MASK	(3 << 8)
#घोषणा CORE_IO_PAD_PWR_SWITCH_EN	BIT(15)
#घोषणा CORE_IO_PAD_PWR_SWITCH	BIT(16)
#घोषणा CORE_HC_SELECT_IN_EN	BIT(18)
#घोषणा CORE_HC_SELECT_IN_HS400	(6 << 19)
#घोषणा CORE_HC_SELECT_IN_MASK	(7 << 19)

#घोषणा CORE_3_0V_SUPPORT	BIT(25)
#घोषणा CORE_1_8V_SUPPORT	BIT(26)
#घोषणा CORE_VOLT_SUPPORT	(CORE_3_0V_SUPPORT | CORE_1_8V_SUPPORT)

#घोषणा CORE_CSR_CDC_CTLR_CFG0		0x130
#घोषणा CORE_SW_TRIG_FULL_CALIB		BIT(16)
#घोषणा CORE_HW_AUTOCAL_ENA		BIT(17)

#घोषणा CORE_CSR_CDC_CTLR_CFG1		0x134
#घोषणा CORE_CSR_CDC_CAL_TIMER_CFG0	0x138
#घोषणा CORE_TIMER_ENA			BIT(16)

#घोषणा CORE_CSR_CDC_CAL_TIMER_CFG1	0x13C
#घोषणा CORE_CSR_CDC_REFCOUNT_CFG	0x140
#घोषणा CORE_CSR_CDC_COARSE_CAL_CFG	0x144
#घोषणा CORE_CDC_OFFSET_CFG		0x14C
#घोषणा CORE_CSR_CDC_DELAY_CFG		0x150
#घोषणा CORE_CDC_SLAVE_DDA_CFG		0x160
#घोषणा CORE_CSR_CDC_STATUS0		0x164
#घोषणा CORE_CALIBRATION_DONE		BIT(0)

#घोषणा CORE_CDC_ERROR_CODE_MASK	0x7000000

#घोषणा CORE_CSR_CDC_GEN_CFG		0x178
#घोषणा CORE_CDC_SWITCH_BYPASS_OFF	BIT(0)
#घोषणा CORE_CDC_SWITCH_RC_EN		BIT(1)

#घोषणा CORE_CDC_T4_DLY_SEL		BIT(0)
#घोषणा CORE_CMDIN_RCLK_EN		BIT(1)
#घोषणा CORE_START_CDC_TRAFFIC		BIT(6)

#घोषणा CORE_PWRSAVE_DLL	BIT(3)

#घोषणा DDR_CONFIG_POR_VAL	0x80040873


#घोषणा INVALID_TUNING_PHASE	-1
#घोषणा SDHCI_MSM_MIN_CLOCK	400000
#घोषणा CORE_FREQ_100MHZ	(100 * 1000 * 1000)

#घोषणा CDR_SELEXT_SHIFT	20
#घोषणा CDR_SELEXT_MASK		(0xf << CDR_SELEXT_SHIFT)
#घोषणा CMUX_SHIFT_PHASE_SHIFT	24
#घोषणा CMUX_SHIFT_PHASE_MASK	(7 << CMUX_SHIFT_PHASE_SHIFT)

#घोषणा MSM_MMC_AUTOSUSPEND_DELAY_MS	50

/* Timeout value to aव्योम infinite रुकोing क्रम pwr_irq */
#घोषणा MSM_PWR_IRQ_TIMEOUT_MS 5000

/* Max load क्रम eMMC Vdd-io supply */
#घोषणा MMC_VQMMC_MAX_LOAD_UA	325000

#घोषणा msm_host_पढ़ोl(msm_host, host, offset) \
	msm_host->var_ops->msm_पढ़ोl_relaxed(host, offset)

#घोषणा msm_host_ग_लिखोl(msm_host, val, host, offset) \
	msm_host->var_ops->msm_ग_लिखोl_relaxed(val, host, offset)

/* CQHCI venकरोr specअगरic रेजिस्टरs */
#घोषणा CQHCI_VENDOR_CFG1	0xA00
#घोषणा CQHCI_VENDOR_DIS_RST_ON_CQ_EN	(0x3 << 13)

काष्ठा sdhci_msm_offset अणु
	u32 core_hc_mode;
	u32 core_mci_data_cnt;
	u32 core_mci_status;
	u32 core_mci_fअगरo_cnt;
	u32 core_mci_version;
	u32 core_generics;
	u32 core_testbus_config;
	u32 core_testbus_sel2_bit;
	u32 core_testbus_ena;
	u32 core_testbus_sel2;
	u32 core_pwrctl_status;
	u32 core_pwrctl_mask;
	u32 core_pwrctl_clear;
	u32 core_pwrctl_ctl;
	u32 core_sdcc_debug_reg;
	u32 core_dll_config;
	u32 core_dll_status;
	u32 core_venकरोr_spec;
	u32 core_venकरोr_spec_adma_err_addr0;
	u32 core_venकरोr_spec_adma_err_addr1;
	u32 core_venकरोr_spec_func2;
	u32 core_venकरोr_spec_capabilities0;
	u32 core_ddr_200_cfg;
	u32 core_venकरोr_spec3;
	u32 core_dll_config_2;
	u32 core_dll_config_3;
	u32 core_ddr_config_old; /* Applicable to sdcc minor ver < 0x49 */
	u32 core_ddr_config;
	u32 core_dll_usr_ctl; /* Present on SDCC5.1 onwards */
पूर्ण;

अटल स्थिर काष्ठा sdhci_msm_offset sdhci_msm_v5_offset = अणु
	.core_mci_data_cnt = 0x35c,
	.core_mci_status = 0x324,
	.core_mci_fअगरo_cnt = 0x308,
	.core_mci_version = 0x318,
	.core_generics = 0x320,
	.core_testbus_config = 0x32c,
	.core_testbus_sel2_bit = 3,
	.core_testbus_ena = (1 << 31),
	.core_testbus_sel2 = (1 << 3),
	.core_pwrctl_status = 0x240,
	.core_pwrctl_mask = 0x244,
	.core_pwrctl_clear = 0x248,
	.core_pwrctl_ctl = 0x24c,
	.core_sdcc_debug_reg = 0x358,
	.core_dll_config = 0x200,
	.core_dll_status = 0x208,
	.core_venकरोr_spec = 0x20c,
	.core_venकरोr_spec_adma_err_addr0 = 0x214,
	.core_venकरोr_spec_adma_err_addr1 = 0x218,
	.core_venकरोr_spec_func2 = 0x210,
	.core_venकरोr_spec_capabilities0 = 0x21c,
	.core_ddr_200_cfg = 0x224,
	.core_venकरोr_spec3 = 0x250,
	.core_dll_config_2 = 0x254,
	.core_dll_config_3 = 0x258,
	.core_ddr_config = 0x25c,
	.core_dll_usr_ctl = 0x388,
पूर्ण;

अटल स्थिर काष्ठा sdhci_msm_offset sdhci_msm_mci_offset = अणु
	.core_hc_mode = 0x78,
	.core_mci_data_cnt = 0x30,
	.core_mci_status = 0x34,
	.core_mci_fअगरo_cnt = 0x44,
	.core_mci_version = 0x050,
	.core_generics = 0x70,
	.core_testbus_config = 0x0cc,
	.core_testbus_sel2_bit = 4,
	.core_testbus_ena = (1 << 3),
	.core_testbus_sel2 = (1 << 4),
	.core_pwrctl_status = 0xdc,
	.core_pwrctl_mask = 0xe0,
	.core_pwrctl_clear = 0xe4,
	.core_pwrctl_ctl = 0xe8,
	.core_sdcc_debug_reg = 0x124,
	.core_dll_config = 0x100,
	.core_dll_status = 0x108,
	.core_venकरोr_spec = 0x10c,
	.core_venकरोr_spec_adma_err_addr0 = 0x114,
	.core_venकरोr_spec_adma_err_addr1 = 0x118,
	.core_venकरोr_spec_func2 = 0x110,
	.core_venकरोr_spec_capabilities0 = 0x11c,
	.core_ddr_200_cfg = 0x184,
	.core_venकरोr_spec3 = 0x1b0,
	.core_dll_config_2 = 0x1b4,
	.core_ddr_config_old = 0x1b8,
	.core_ddr_config = 0x1bc,
पूर्ण;

काष्ठा sdhci_msm_variant_ops अणु
	u32 (*msm_पढ़ोl_relaxed)(काष्ठा sdhci_host *host, u32 offset);
	व्योम (*msm_ग_लिखोl_relaxed)(u32 val, काष्ठा sdhci_host *host,
			u32 offset);
पूर्ण;

/*
 * From V5, रेजिस्टर spaces have changed. Wrap this info in a काष्ठाure
 * and choose the data_काष्ठाure based on version info mentioned in DT.
 */
काष्ठा sdhci_msm_variant_info अणु
	bool mci_हटाओd;
	bool restore_dll_config;
	स्थिर काष्ठा sdhci_msm_variant_ops *var_ops;
	स्थिर काष्ठा sdhci_msm_offset *offset;
पूर्ण;

काष्ठा sdhci_msm_host अणु
	काष्ठा platक्रमm_device *pdev;
	व्योम __iomem *core_mem;	/* MSM SDCC mapped address */
	व्योम __iomem *ice_mem;	/* MSM ICE mapped address (अगर available) */
	पूर्णांक pwr_irq;		/* घातer irq */
	काष्ठा clk *bus_clk;	/* SDHC bus voter घड़ी */
	काष्ठा clk *xo_clk;	/* TCXO clk needed क्रम FLL feature of cm_dll*/
	/* core, अगरace, cal, sleep, and ice घड़ीs */
	काष्ठा clk_bulk_data bulk_clks[5];
	अचिन्हित दीर्घ clk_rate;
	काष्ठा mmc_host *mmc;
	bool use_14lpp_dll_reset;
	bool tuning_करोne;
	bool calibration_करोne;
	u8 saved_tuning_phase;
	bool use_cdclp533;
	u32 curr_pwr_state;
	u32 curr_io_level;
	रुको_queue_head_t pwr_irq_रुको;
	bool pwr_irq_flag;
	u32 caps_0;
	bool mci_हटाओd;
	bool restore_dll_config;
	स्थिर काष्ठा sdhci_msm_variant_ops *var_ops;
	स्थिर काष्ठा sdhci_msm_offset *offset;
	bool use_cdr;
	u32 transfer_mode;
	bool updated_ddr_cfg;
	bool uses_tassadar_dll;
	u32 dll_config;
	u32 ddr_config;
	bool vqmmc_enabled;
पूर्ण;

अटल स्थिर काष्ठा sdhci_msm_offset *sdhci_priv_msm_offset(काष्ठा sdhci_host *host)
अणु
	काष्ठा sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	काष्ठा sdhci_msm_host *msm_host = sdhci_pltfm_priv(pltfm_host);

	वापस msm_host->offset;
पूर्ण

/*
 * APIs to पढ़ो/ग_लिखो to venकरोr specअगरic रेजिस्टरs which were there in the
 * core_mem region beक्रमe MCI was हटाओd.
 */
अटल u32 sdhci_msm_mci_variant_पढ़ोl_relaxed(काष्ठा sdhci_host *host,
		u32 offset)
अणु
	काष्ठा sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	काष्ठा sdhci_msm_host *msm_host = sdhci_pltfm_priv(pltfm_host);

	वापस पढ़ोl_relaxed(msm_host->core_mem + offset);
पूर्ण

अटल u32 sdhci_msm_v5_variant_पढ़ोl_relaxed(काष्ठा sdhci_host *host,
		u32 offset)
अणु
	वापस पढ़ोl_relaxed(host->ioaddr + offset);
पूर्ण

अटल व्योम sdhci_msm_mci_variant_ग_लिखोl_relaxed(u32 val,
		काष्ठा sdhci_host *host, u32 offset)
अणु
	काष्ठा sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	काष्ठा sdhci_msm_host *msm_host = sdhci_pltfm_priv(pltfm_host);

	ग_लिखोl_relaxed(val, msm_host->core_mem + offset);
पूर्ण

अटल व्योम sdhci_msm_v5_variant_ग_लिखोl_relaxed(u32 val,
		काष्ठा sdhci_host *host, u32 offset)
अणु
	ग_लिखोl_relaxed(val, host->ioaddr + offset);
पूर्ण

अटल अचिन्हित पूर्णांक msm_get_घड़ी_mult_क्रम_bus_mode(काष्ठा sdhci_host *host)
अणु
	काष्ठा mmc_ios ios = host->mmc->ios;
	/*
	 * The SDHC requires पूर्णांकernal घड़ी frequency to be द्विगुन the
	 * actual घड़ी that will be set क्रम DDR mode. The controller
	 * uses the faster घड़ी(100/400MHz) क्रम some of its parts and
	 * send the actual required घड़ी (50/200MHz) to the card.
	 */
	अगर (ios.timing == MMC_TIMING_UHS_DDR50 ||
	    ios.timing == MMC_TIMING_MMC_DDR52 ||
	    ios.timing == MMC_TIMING_MMC_HS400 ||
	    host->flags & SDHCI_HS400_TUNING)
		वापस 2;
	वापस 1;
पूर्ण

अटल व्योम msm_set_घड़ी_rate_क्रम_bus_mode(काष्ठा sdhci_host *host,
					    अचिन्हित पूर्णांक घड़ी)
अणु
	काष्ठा sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	काष्ठा sdhci_msm_host *msm_host = sdhci_pltfm_priv(pltfm_host);
	काष्ठा mmc_ios curr_ios = host->mmc->ios;
	काष्ठा clk *core_clk = msm_host->bulk_clks[0].clk;
	अचिन्हित दीर्घ achieved_rate;
	अचिन्हित पूर्णांक desired_rate;
	अचिन्हित पूर्णांक mult;
	पूर्णांक rc;

	mult = msm_get_घड़ी_mult_क्रम_bus_mode(host);
	desired_rate = घड़ी * mult;
	rc = dev_pm_opp_set_rate(mmc_dev(host->mmc), desired_rate);
	अगर (rc) अणु
		pr_err("%s: Failed to set clock at rate %u at timing %d\n",
		       mmc_hostname(host->mmc), desired_rate, curr_ios.timing);
		वापस;
	पूर्ण

	/*
	 * Qualcomm घड़ी drivers by शेष round घड़ी _up_ अगर they can't
	 * make the requested rate.  This is not good क्रम SD.  Yell अगर we
	 * encounter it.
	 */
	achieved_rate = clk_get_rate(core_clk);
	अगर (achieved_rate > desired_rate)
		pr_warn("%s: Card appears overclocked; req %u Hz, actual %lu Hz\n",
			mmc_hostname(host->mmc), desired_rate, achieved_rate);
	host->mmc->actual_घड़ी = achieved_rate / mult;

	/* Stash the rate we requested to use in sdhci_msm_runसमय_resume() */
	msm_host->clk_rate = desired_rate;

	pr_debug("%s: Setting clock at rate %lu at timing %d\n",
		 mmc_hostname(host->mmc), achieved_rate, curr_ios.timing);
पूर्ण

/* Platक्रमm specअगरic tuning */
अटल अंतरभूत पूर्णांक msm_dll_poll_ck_out_en(काष्ठा sdhci_host *host, u8 poll)
अणु
	u32 रुको_cnt = 50;
	u8 ck_out_en;
	काष्ठा mmc_host *mmc = host->mmc;
	स्थिर काष्ठा sdhci_msm_offset *msm_offset =
					sdhci_priv_msm_offset(host);

	/* Poll क्रम CK_OUT_EN bit.  max. poll समय = 50us */
	ck_out_en = !!(पढ़ोl_relaxed(host->ioaddr +
			msm_offset->core_dll_config) & CORE_CK_OUT_EN);

	जबतक (ck_out_en != poll) अणु
		अगर (--रुको_cnt == 0) अणु
			dev_err(mmc_dev(mmc), "%s: CK_OUT_EN bit is not %d\n",
			       mmc_hostname(mmc), poll);
			वापस -ETIMEDOUT;
		पूर्ण
		udelay(1);

		ck_out_en = !!(पढ़ोl_relaxed(host->ioaddr +
			msm_offset->core_dll_config) & CORE_CK_OUT_EN);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक msm_config_cm_dll_phase(काष्ठा sdhci_host *host, u8 phase)
अणु
	पूर्णांक rc;
	अटल स्थिर u8 grey_coded_phase_table[] = अणु
		0x0, 0x1, 0x3, 0x2, 0x6, 0x7, 0x5, 0x4,
		0xc, 0xd, 0xf, 0xe, 0xa, 0xb, 0x9, 0x8
	पूर्ण;
	अचिन्हित दीर्घ flags;
	u32 config;
	काष्ठा mmc_host *mmc = host->mmc;
	स्थिर काष्ठा sdhci_msm_offset *msm_offset =
					sdhci_priv_msm_offset(host);

	अगर (phase > 0xf)
		वापस -EINVAL;

	spin_lock_irqsave(&host->lock, flags);

	config = पढ़ोl_relaxed(host->ioaddr + msm_offset->core_dll_config);
	config &= ~(CORE_CDR_EN | CORE_CK_OUT_EN);
	config |= (CORE_CDR_EXT_EN | CORE_DLL_EN);
	ग_लिखोl_relaxed(config, host->ioaddr + msm_offset->core_dll_config);

	/* Wait until CK_OUT_EN bit of DLL_CONFIG रेजिस्टर becomes '0' */
	rc = msm_dll_poll_ck_out_en(host, 0);
	अगर (rc)
		जाओ err_out;

	/*
	 * Write the selected DLL घड़ी output phase (0 ... 15)
	 * to CDR_SELEXT bit field of DLL_CONFIG रेजिस्टर.
	 */
	config = पढ़ोl_relaxed(host->ioaddr + msm_offset->core_dll_config);
	config &= ~CDR_SELEXT_MASK;
	config |= grey_coded_phase_table[phase] << CDR_SELEXT_SHIFT;
	ग_लिखोl_relaxed(config, host->ioaddr + msm_offset->core_dll_config);

	config = पढ़ोl_relaxed(host->ioaddr + msm_offset->core_dll_config);
	config |= CORE_CK_OUT_EN;
	ग_लिखोl_relaxed(config, host->ioaddr + msm_offset->core_dll_config);

	/* Wait until CK_OUT_EN bit of DLL_CONFIG रेजिस्टर becomes '1' */
	rc = msm_dll_poll_ck_out_en(host, 1);
	अगर (rc)
		जाओ err_out;

	config = पढ़ोl_relaxed(host->ioaddr + msm_offset->core_dll_config);
	config |= CORE_CDR_EN;
	config &= ~CORE_CDR_EXT_EN;
	ग_लिखोl_relaxed(config, host->ioaddr + msm_offset->core_dll_config);
	जाओ out;

err_out:
	dev_err(mmc_dev(mmc), "%s: Failed to set DLL phase: %d\n",
	       mmc_hostname(mmc), phase);
out:
	spin_unlock_irqrestore(&host->lock, flags);
	वापस rc;
पूर्ण

/*
 * Find out the greatest range of consecuitive selected
 * DLL घड़ी output phases that can be used as sampling
 * setting क्रम SD3.0 UHS-I card पढ़ो operation (in SDR104
 * timing mode) or क्रम eMMC4.5 card पढ़ो operation (in
 * HS400/HS200 timing mode).
 * Select the 3/4 of the range and configure the DLL with the
 * selected DLL घड़ी output phase.
 */

अटल पूर्णांक msm_find_most_appropriate_phase(काष्ठा sdhci_host *host,
					   u8 *phase_table, u8 total_phases)
अणु
	पूर्णांक ret;
	u8 ranges[MAX_PHASES][MAX_PHASES] = अणु अणु0पूर्ण, अणु0पूर्ण पूर्ण;
	u8 phases_per_row[MAX_PHASES] = अणु 0 पूर्ण;
	पूर्णांक row_index = 0, col_index = 0, selected_row_index = 0, curr_max = 0;
	पूर्णांक i, cnt, phase_0_raw_index = 0, phase_15_raw_index = 0;
	bool phase_0_found = false, phase_15_found = false;
	काष्ठा mmc_host *mmc = host->mmc;

	अगर (!total_phases || (total_phases > MAX_PHASES)) अणु
		dev_err(mmc_dev(mmc), "%s: Invalid argument: total_phases=%d\n",
		       mmc_hostname(mmc), total_phases);
		वापस -EINVAL;
	पूर्ण

	क्रम (cnt = 0; cnt < total_phases; cnt++) अणु
		ranges[row_index][col_index] = phase_table[cnt];
		phases_per_row[row_index] += 1;
		col_index++;

		अगर ((cnt + 1) == total_phases) अणु
			जारी;
		/* check अगर next phase in phase_table is consecutive or not */
		पूर्ण अन्यथा अगर ((phase_table[cnt] + 1) != phase_table[cnt + 1]) अणु
			row_index++;
			col_index = 0;
		पूर्ण
	पूर्ण

	अगर (row_index >= MAX_PHASES)
		वापस -EINVAL;

	/* Check अगर phase-0 is present in first valid winकरोw? */
	अगर (!ranges[0][0]) अणु
		phase_0_found = true;
		phase_0_raw_index = 0;
		/* Check अगर cycle exist between 2 valid winकरोws */
		क्रम (cnt = 1; cnt <= row_index; cnt++) अणु
			अगर (phases_per_row[cnt]) अणु
				क्रम (i = 0; i < phases_per_row[cnt]; i++) अणु
					अगर (ranges[cnt][i] == 15) अणु
						phase_15_found = true;
						phase_15_raw_index = cnt;
						अवरोध;
					पूर्ण
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	/* If 2 valid winकरोws क्रमm cycle then merge them as single winकरोw */
	अगर (phase_0_found && phase_15_found) अणु
		/* number of phases in raw where phase 0 is present */
		u8 phases_0 = phases_per_row[phase_0_raw_index];
		/* number of phases in raw where phase 15 is present */
		u8 phases_15 = phases_per_row[phase_15_raw_index];

		अगर (phases_0 + phases_15 >= MAX_PHASES)
			/*
			 * If there are more than 1 phase winकरोws then total
			 * number of phases in both the winकरोws should not be
			 * more than or equal to MAX_PHASES.
			 */
			वापस -EINVAL;

		/* Merge 2 cyclic winकरोws */
		i = phases_15;
		क्रम (cnt = 0; cnt < phases_0; cnt++) अणु
			ranges[phase_15_raw_index][i] =
			    ranges[phase_0_raw_index][cnt];
			अगर (++i >= MAX_PHASES)
				अवरोध;
		पूर्ण

		phases_per_row[phase_0_raw_index] = 0;
		phases_per_row[phase_15_raw_index] = phases_15 + phases_0;
	पूर्ण

	क्रम (cnt = 0; cnt <= row_index; cnt++) अणु
		अगर (phases_per_row[cnt] > curr_max) अणु
			curr_max = phases_per_row[cnt];
			selected_row_index = cnt;
		पूर्ण
	पूर्ण

	i = (curr_max * 3) / 4;
	अगर (i)
		i--;

	ret = ranges[selected_row_index][i];

	अगर (ret >= MAX_PHASES) अणु
		ret = -EINVAL;
		dev_err(mmc_dev(mmc), "%s: Invalid phase selected=%d\n",
		       mmc_hostname(mmc), ret);
	पूर्ण

	वापस ret;
पूर्ण

अटल अंतरभूत व्योम msm_cm_dll_set_freq(काष्ठा sdhci_host *host)
अणु
	u32 mclk_freq = 0, config;
	स्थिर काष्ठा sdhci_msm_offset *msm_offset =
					sdhci_priv_msm_offset(host);

	/* Program the MCLK value to MCLK_FREQ bit field */
	अगर (host->घड़ी <= 112000000)
		mclk_freq = 0;
	अन्यथा अगर (host->घड़ी <= 125000000)
		mclk_freq = 1;
	अन्यथा अगर (host->घड़ी <= 137000000)
		mclk_freq = 2;
	अन्यथा अगर (host->घड़ी <= 150000000)
		mclk_freq = 3;
	अन्यथा अगर (host->घड़ी <= 162000000)
		mclk_freq = 4;
	अन्यथा अगर (host->घड़ी <= 175000000)
		mclk_freq = 5;
	अन्यथा अगर (host->घड़ी <= 187000000)
		mclk_freq = 6;
	अन्यथा अगर (host->घड़ी <= 200000000)
		mclk_freq = 7;

	config = पढ़ोl_relaxed(host->ioaddr + msm_offset->core_dll_config);
	config &= ~CMUX_SHIFT_PHASE_MASK;
	config |= mclk_freq << CMUX_SHIFT_PHASE_SHIFT;
	ग_लिखोl_relaxed(config, host->ioaddr + msm_offset->core_dll_config);
पूर्ण

/* Initialize the DLL (Programmable Delay Line) */
अटल पूर्णांक msm_init_cm_dll(काष्ठा sdhci_host *host)
अणु
	काष्ठा mmc_host *mmc = host->mmc;
	काष्ठा sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	काष्ठा sdhci_msm_host *msm_host = sdhci_pltfm_priv(pltfm_host);
	पूर्णांक रुको_cnt = 50;
	अचिन्हित दीर्घ flags, xo_clk = 0;
	u32 config;
	स्थिर काष्ठा sdhci_msm_offset *msm_offset =
					msm_host->offset;

	अगर (msm_host->use_14lpp_dll_reset && !IS_ERR_OR_शून्य(msm_host->xo_clk))
		xo_clk = clk_get_rate(msm_host->xo_clk);

	spin_lock_irqsave(&host->lock, flags);

	/*
	 * Make sure that घड़ी is always enabled when DLL
	 * tuning is in progress. Keeping PWRSAVE ON may
	 * turn off the घड़ी.
	 */
	config = पढ़ोl_relaxed(host->ioaddr + msm_offset->core_venकरोr_spec);
	config &= ~CORE_CLK_PWRSAVE;
	ग_लिखोl_relaxed(config, host->ioaddr + msm_offset->core_venकरोr_spec);

	अगर (msm_host->dll_config)
		ग_लिखोl_relaxed(msm_host->dll_config,
				host->ioaddr + msm_offset->core_dll_config);

	अगर (msm_host->use_14lpp_dll_reset) अणु
		config = पढ़ोl_relaxed(host->ioaddr +
				msm_offset->core_dll_config);
		config &= ~CORE_CK_OUT_EN;
		ग_लिखोl_relaxed(config, host->ioaddr +
				msm_offset->core_dll_config);

		config = पढ़ोl_relaxed(host->ioaddr +
				msm_offset->core_dll_config_2);
		config |= CORE_DLL_CLOCK_DISABLE;
		ग_लिखोl_relaxed(config, host->ioaddr +
				msm_offset->core_dll_config_2);
	पूर्ण

	config = पढ़ोl_relaxed(host->ioaddr +
			msm_offset->core_dll_config);
	config |= CORE_DLL_RST;
	ग_लिखोl_relaxed(config, host->ioaddr +
			msm_offset->core_dll_config);

	config = पढ़ोl_relaxed(host->ioaddr +
			msm_offset->core_dll_config);
	config |= CORE_DLL_PDN;
	ग_लिखोl_relaxed(config, host->ioaddr +
			msm_offset->core_dll_config);

	अगर (!msm_host->dll_config)
		msm_cm_dll_set_freq(host);

	अगर (msm_host->use_14lpp_dll_reset &&
	    !IS_ERR_OR_शून्य(msm_host->xo_clk)) अणु
		u32 mclk_freq = 0;

		config = पढ़ोl_relaxed(host->ioaddr +
				msm_offset->core_dll_config_2);
		config &= CORE_FLL_CYCLE_CNT;
		अगर (config)
			mclk_freq = DIV_ROUND_CLOSEST_ULL((host->घड़ी * 8),
					xo_clk);
		अन्यथा
			mclk_freq = DIV_ROUND_CLOSEST_ULL((host->घड़ी * 4),
					xo_clk);

		config = पढ़ोl_relaxed(host->ioaddr +
				msm_offset->core_dll_config_2);
		config &= ~(0xFF << 10);
		config |= mclk_freq << 10;

		ग_लिखोl_relaxed(config, host->ioaddr +
				msm_offset->core_dll_config_2);
		/* रुको क्रम 5us beक्रमe enabling DLL घड़ी */
		udelay(5);
	पूर्ण

	config = पढ़ोl_relaxed(host->ioaddr +
			msm_offset->core_dll_config);
	config &= ~CORE_DLL_RST;
	ग_लिखोl_relaxed(config, host->ioaddr +
			msm_offset->core_dll_config);

	config = पढ़ोl_relaxed(host->ioaddr +
			msm_offset->core_dll_config);
	config &= ~CORE_DLL_PDN;
	ग_लिखोl_relaxed(config, host->ioaddr +
			msm_offset->core_dll_config);

	अगर (msm_host->use_14lpp_dll_reset) अणु
		अगर (!msm_host->dll_config)
			msm_cm_dll_set_freq(host);
		config = पढ़ोl_relaxed(host->ioaddr +
				msm_offset->core_dll_config_2);
		config &= ~CORE_DLL_CLOCK_DISABLE;
		ग_लिखोl_relaxed(config, host->ioaddr +
				msm_offset->core_dll_config_2);
	पूर्ण

	/*
	 * Configure DLL user control रेजिस्टर to enable DLL status.
	 * This setting is applicable to SDCC v5.1 onwards only.
	 */
	अगर (msm_host->uses_tassadar_dll) अणु
		config = DLL_USR_CTL_POR_VAL | FINE_TUNE_MODE_EN |
			ENABLE_DLL_LOCK_STATUS | BIAS_OK_SIGNAL;
		ग_लिखोl_relaxed(config, host->ioaddr +
				msm_offset->core_dll_usr_ctl);

		config = पढ़ोl_relaxed(host->ioaddr +
				msm_offset->core_dll_config_3);
		config &= ~0xFF;
		अगर (msm_host->clk_rate < 150000000)
			config |= DLL_CONFIG_3_LOW_FREQ_VAL;
		अन्यथा
			config |= DLL_CONFIG_3_HIGH_FREQ_VAL;
		ग_लिखोl_relaxed(config, host->ioaddr +
			msm_offset->core_dll_config_3);
	पूर्ण

	config = पढ़ोl_relaxed(host->ioaddr +
			msm_offset->core_dll_config);
	config |= CORE_DLL_EN;
	ग_लिखोl_relaxed(config, host->ioaddr +
			msm_offset->core_dll_config);

	config = पढ़ोl_relaxed(host->ioaddr +
			msm_offset->core_dll_config);
	config |= CORE_CK_OUT_EN;
	ग_लिखोl_relaxed(config, host->ioaddr +
			msm_offset->core_dll_config);

	/* Wait until DLL_LOCK bit of DLL_STATUS रेजिस्टर becomes '1' */
	जबतक (!(पढ़ोl_relaxed(host->ioaddr + msm_offset->core_dll_status) &
		 CORE_DLL_LOCK)) अणु
		/* max. रुको क्रम 50us sec क्रम LOCK bit to be set */
		अगर (--रुको_cnt == 0) अणु
			dev_err(mmc_dev(mmc), "%s: DLL failed to LOCK\n",
			       mmc_hostname(mmc));
			spin_unlock_irqrestore(&host->lock, flags);
			वापस -ETIMEDOUT;
		पूर्ण
		udelay(1);
	पूर्ण

	spin_unlock_irqrestore(&host->lock, flags);
	वापस 0;
पूर्ण

अटल व्योम msm_hc_select_शेष(काष्ठा sdhci_host *host)
अणु
	काष्ठा sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	काष्ठा sdhci_msm_host *msm_host = sdhci_pltfm_priv(pltfm_host);
	u32 config;
	स्थिर काष्ठा sdhci_msm_offset *msm_offset =
					msm_host->offset;

	अगर (!msm_host->use_cdclp533) अणु
		config = पढ़ोl_relaxed(host->ioaddr +
				msm_offset->core_venकरोr_spec3);
		config &= ~CORE_PWRSAVE_DLL;
		ग_लिखोl_relaxed(config, host->ioaddr +
				msm_offset->core_venकरोr_spec3);
	पूर्ण

	config = पढ़ोl_relaxed(host->ioaddr + msm_offset->core_venकरोr_spec);
	config &= ~CORE_HC_MCLK_SEL_MASK;
	config |= CORE_HC_MCLK_SEL_DFLT;
	ग_लिखोl_relaxed(config, host->ioaddr + msm_offset->core_venकरोr_spec);

	/*
	 * Disable HC_SELECT_IN to be able to use the UHS mode select
	 * configuration from Host Control2 रेजिस्टर क्रम all other
	 * modes.
	 * Write 0 to HC_SELECT_IN and HC_SELECT_IN_EN field
	 * in VENDOR_SPEC_FUNC
	 */
	config = पढ़ोl_relaxed(host->ioaddr + msm_offset->core_venकरोr_spec);
	config &= ~CORE_HC_SELECT_IN_EN;
	config &= ~CORE_HC_SELECT_IN_MASK;
	ग_लिखोl_relaxed(config, host->ioaddr + msm_offset->core_venकरोr_spec);

	/*
	 * Make sure above ग_लिखोs impacting मुक्त running MCLK are completed
	 * beक्रमe changing the clk_rate at GCC.
	 */
	wmb();
पूर्ण

अटल व्योम msm_hc_select_hs400(काष्ठा sdhci_host *host)
अणु
	काष्ठा sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	काष्ठा sdhci_msm_host *msm_host = sdhci_pltfm_priv(pltfm_host);
	काष्ठा mmc_ios ios = host->mmc->ios;
	u32 config, dll_lock;
	पूर्णांक rc;
	स्थिर काष्ठा sdhci_msm_offset *msm_offset =
					msm_host->offset;

	/* Select the भागided घड़ी (मुक्त running MCLK/2) */
	config = पढ़ोl_relaxed(host->ioaddr + msm_offset->core_venकरोr_spec);
	config &= ~CORE_HC_MCLK_SEL_MASK;
	config |= CORE_HC_MCLK_SEL_HS400;

	ग_लिखोl_relaxed(config, host->ioaddr + msm_offset->core_venकरोr_spec);
	/*
	 * Select HS400 mode using the HC_SELECT_IN from VENDOR SPEC
	 * रेजिस्टर
	 */
	अगर ((msm_host->tuning_करोne || ios.enhanced_strobe) &&
	    !msm_host->calibration_करोne) अणु
		config = पढ़ोl_relaxed(host->ioaddr +
				msm_offset->core_venकरोr_spec);
		config |= CORE_HC_SELECT_IN_HS400;
		config |= CORE_HC_SELECT_IN_EN;
		ग_लिखोl_relaxed(config, host->ioaddr +
				msm_offset->core_venकरोr_spec);
	पूर्ण
	अगर (!msm_host->clk_rate && !msm_host->use_cdclp533) अणु
		/*
		 * Poll on DLL_LOCK or DDR_DLL_LOCK bits in
		 * core_dll_status to be set. This should get set
		 * within 15 us at 200 MHz.
		 */
		rc = पढ़ोl_relaxed_poll_समयout(host->ioaddr +
						msm_offset->core_dll_status,
						dll_lock,
						(dll_lock &
						(CORE_DLL_LOCK |
						CORE_DDR_DLL_LOCK)), 10,
						1000);
		अगर (rc == -ETIMEDOUT)
			pr_err("%s: Unable to get DLL_LOCK/DDR_DLL_LOCK, dll_status: 0x%08x\n",
			       mmc_hostname(host->mmc), dll_lock);
	पूर्ण
	/*
	 * Make sure above ग_लिखोs impacting मुक्त running MCLK are completed
	 * beक्रमe changing the clk_rate at GCC.
	 */
	wmb();
पूर्ण

/*
 * sdhci_msm_hc_select_mode :- In general all timing modes are
 * controlled via UHS mode select in Host Control2 रेजिस्टर.
 * eMMC specअगरic HS200/HS400 करोesn't have their respective modes
 * defined here, hence we use these values.
 *
 * HS200 - SDR104 (Since they both are equivalent in functionality)
 * HS400 - This involves multiple configurations
 *		Initially SDR104 - when tuning is required as HS200
 *		Then when चयनing to DDR @ 400MHz (HS400) we use
 *		the venकरोr specअगरic HC_SELECT_IN to control the mode.
 *
 * In addition to controlling the modes we also need to select the
 * correct input घड़ी क्रम DLL depending on the mode.
 *
 * HS400 - भागided घड़ी (मुक्त running MCLK/2)
 * All other modes - शेष (मुक्त running MCLK)
 */
अटल व्योम sdhci_msm_hc_select_mode(काष्ठा sdhci_host *host)
अणु
	काष्ठा mmc_ios ios = host->mmc->ios;

	अगर (ios.timing == MMC_TIMING_MMC_HS400 ||
	    host->flags & SDHCI_HS400_TUNING)
		msm_hc_select_hs400(host);
	अन्यथा
		msm_hc_select_शेष(host);
पूर्ण

अटल पूर्णांक sdhci_msm_cdclp533_calibration(काष्ठा sdhci_host *host)
अणु
	काष्ठा sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	काष्ठा sdhci_msm_host *msm_host = sdhci_pltfm_priv(pltfm_host);
	u32 config, calib_करोne;
	पूर्णांक ret;
	स्थिर काष्ठा sdhci_msm_offset *msm_offset =
					msm_host->offset;

	pr_debug("%s: %s: Enter\n", mmc_hostname(host->mmc), __func__);

	/*
	 * Retuning in HS400 (DDR mode) will fail, just reset the
	 * tuning block and restore the saved tuning phase.
	 */
	ret = msm_init_cm_dll(host);
	अगर (ret)
		जाओ out;

	/* Set the selected phase in delay line hw block */
	ret = msm_config_cm_dll_phase(host, msm_host->saved_tuning_phase);
	अगर (ret)
		जाओ out;

	config = पढ़ोl_relaxed(host->ioaddr + msm_offset->core_dll_config);
	config |= CORE_CMD_DAT_TRACK_SEL;
	ग_लिखोl_relaxed(config, host->ioaddr + msm_offset->core_dll_config);

	config = पढ़ोl_relaxed(host->ioaddr + msm_offset->core_ddr_200_cfg);
	config &= ~CORE_CDC_T4_DLY_SEL;
	ग_लिखोl_relaxed(config, host->ioaddr + msm_offset->core_ddr_200_cfg);

	config = पढ़ोl_relaxed(host->ioaddr + CORE_CSR_CDC_GEN_CFG);
	config &= ~CORE_CDC_SWITCH_BYPASS_OFF;
	ग_लिखोl_relaxed(config, host->ioaddr + CORE_CSR_CDC_GEN_CFG);

	config = पढ़ोl_relaxed(host->ioaddr + CORE_CSR_CDC_GEN_CFG);
	config |= CORE_CDC_SWITCH_RC_EN;
	ग_लिखोl_relaxed(config, host->ioaddr + CORE_CSR_CDC_GEN_CFG);

	config = पढ़ोl_relaxed(host->ioaddr + msm_offset->core_ddr_200_cfg);
	config &= ~CORE_START_CDC_TRAFFIC;
	ग_लिखोl_relaxed(config, host->ioaddr + msm_offset->core_ddr_200_cfg);

	/* Perक्रमm CDC Register Initialization Sequence */

	ग_लिखोl_relaxed(0x11800EC, host->ioaddr + CORE_CSR_CDC_CTLR_CFG0);
	ग_लिखोl_relaxed(0x3011111, host->ioaddr + CORE_CSR_CDC_CTLR_CFG1);
	ग_लिखोl_relaxed(0x1201000, host->ioaddr + CORE_CSR_CDC_CAL_TIMER_CFG0);
	ग_लिखोl_relaxed(0x4, host->ioaddr + CORE_CSR_CDC_CAL_TIMER_CFG1);
	ग_लिखोl_relaxed(0xCB732020, host->ioaddr + CORE_CSR_CDC_REFCOUNT_CFG);
	ग_लिखोl_relaxed(0xB19, host->ioaddr + CORE_CSR_CDC_COARSE_CAL_CFG);
	ग_लिखोl_relaxed(0x4E2, host->ioaddr + CORE_CSR_CDC_DELAY_CFG);
	ग_लिखोl_relaxed(0x0, host->ioaddr + CORE_CDC_OFFSET_CFG);
	ग_लिखोl_relaxed(0x16334, host->ioaddr + CORE_CDC_SLAVE_DDA_CFG);

	/* CDC HW Calibration */

	config = पढ़ोl_relaxed(host->ioaddr + CORE_CSR_CDC_CTLR_CFG0);
	config |= CORE_SW_TRIG_FULL_CALIB;
	ग_लिखोl_relaxed(config, host->ioaddr + CORE_CSR_CDC_CTLR_CFG0);

	config = पढ़ोl_relaxed(host->ioaddr + CORE_CSR_CDC_CTLR_CFG0);
	config &= ~CORE_SW_TRIG_FULL_CALIB;
	ग_लिखोl_relaxed(config, host->ioaddr + CORE_CSR_CDC_CTLR_CFG0);

	config = पढ़ोl_relaxed(host->ioaddr + CORE_CSR_CDC_CTLR_CFG0);
	config |= CORE_HW_AUTOCAL_ENA;
	ग_लिखोl_relaxed(config, host->ioaddr + CORE_CSR_CDC_CTLR_CFG0);

	config = पढ़ोl_relaxed(host->ioaddr + CORE_CSR_CDC_CAL_TIMER_CFG0);
	config |= CORE_TIMER_ENA;
	ग_लिखोl_relaxed(config, host->ioaddr + CORE_CSR_CDC_CAL_TIMER_CFG0);

	ret = पढ़ोl_relaxed_poll_समयout(host->ioaddr + CORE_CSR_CDC_STATUS0,
					 calib_करोne,
					 (calib_करोne & CORE_CALIBRATION_DONE),
					 1, 50);

	अगर (ret == -ETIMEDOUT) अणु
		pr_err("%s: %s: CDC calibration was not completed\n",
		       mmc_hostname(host->mmc), __func__);
		जाओ out;
	पूर्ण

	ret = पढ़ोl_relaxed(host->ioaddr + CORE_CSR_CDC_STATUS0)
			& CORE_CDC_ERROR_CODE_MASK;
	अगर (ret) अणु
		pr_err("%s: %s: CDC error code %d\n",
		       mmc_hostname(host->mmc), __func__, ret);
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	config = पढ़ोl_relaxed(host->ioaddr + msm_offset->core_ddr_200_cfg);
	config |= CORE_START_CDC_TRAFFIC;
	ग_लिखोl_relaxed(config, host->ioaddr + msm_offset->core_ddr_200_cfg);
out:
	pr_debug("%s: %s: Exit, ret %d\n", mmc_hostname(host->mmc),
		 __func__, ret);
	वापस ret;
पूर्ण

अटल पूर्णांक sdhci_msm_cm_dll_sdc4_calibration(काष्ठा sdhci_host *host)
अणु
	काष्ठा mmc_host *mmc = host->mmc;
	u32 dll_status, config, ddr_cfg_offset;
	पूर्णांक ret;
	काष्ठा sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	काष्ठा sdhci_msm_host *msm_host = sdhci_pltfm_priv(pltfm_host);
	स्थिर काष्ठा sdhci_msm_offset *msm_offset =
					sdhci_priv_msm_offset(host);

	pr_debug("%s: %s: Enter\n", mmc_hostname(host->mmc), __func__);

	/*
	 * Currently the core_ddr_config रेजिस्टर शेषs to desired
	 * configuration on reset. Currently reprogramming the घातer on
	 * reset (POR) value in हाल it might have been modअगरied by
	 * bootloaders. In the future, अगर this changes, then the desired
	 * values will need to be programmed appropriately.
	 */
	अगर (msm_host->updated_ddr_cfg)
		ddr_cfg_offset = msm_offset->core_ddr_config;
	अन्यथा
		ddr_cfg_offset = msm_offset->core_ddr_config_old;
	ग_लिखोl_relaxed(msm_host->ddr_config, host->ioaddr + ddr_cfg_offset);

	अगर (mmc->ios.enhanced_strobe) अणु
		config = पढ़ोl_relaxed(host->ioaddr +
				msm_offset->core_ddr_200_cfg);
		config |= CORE_CMDIN_RCLK_EN;
		ग_लिखोl_relaxed(config, host->ioaddr +
				msm_offset->core_ddr_200_cfg);
	पूर्ण

	config = पढ़ोl_relaxed(host->ioaddr + msm_offset->core_dll_config_2);
	config |= CORE_DDR_CAL_EN;
	ग_लिखोl_relaxed(config, host->ioaddr + msm_offset->core_dll_config_2);

	ret = पढ़ोl_relaxed_poll_समयout(host->ioaddr +
					msm_offset->core_dll_status,
					dll_status,
					(dll_status & CORE_DDR_DLL_LOCK),
					10, 1000);

	अगर (ret == -ETIMEDOUT) अणु
		pr_err("%s: %s: CM_DLL_SDC4 calibration was not completed\n",
		       mmc_hostname(host->mmc), __func__);
		जाओ out;
	पूर्ण

	/*
	 * Set CORE_PWRSAVE_DLL bit in CORE_VENDOR_SPEC3.
	 * When MCLK is gated OFF, it is not gated क्रम less than 0.5us
	 * and MCLK must be चयनed on क्रम at-least 1us beक्रमe DATA
	 * starts coming. Controllers with 14lpp and later tech DLL cannot
	 * guarantee above requirement. So PWRSAVE_DLL should not be
	 * turned on क्रम host controllers using this DLL.
	 */
	अगर (!msm_host->use_14lpp_dll_reset) अणु
		config = पढ़ोl_relaxed(host->ioaddr +
				msm_offset->core_venकरोr_spec3);
		config |= CORE_PWRSAVE_DLL;
		ग_लिखोl_relaxed(config, host->ioaddr +
				msm_offset->core_venकरोr_spec3);
	पूर्ण

	/*
	 * Drain ग_लिखोbuffer to ensure above DLL calibration
	 * and PWRSAVE DLL is enabled.
	 */
	wmb();
out:
	pr_debug("%s: %s: Exit, ret %d\n", mmc_hostname(host->mmc),
		 __func__, ret);
	वापस ret;
पूर्ण

अटल पूर्णांक sdhci_msm_hs400_dll_calibration(काष्ठा sdhci_host *host)
अणु
	काष्ठा sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	काष्ठा sdhci_msm_host *msm_host = sdhci_pltfm_priv(pltfm_host);
	काष्ठा mmc_host *mmc = host->mmc;
	पूर्णांक ret;
	u32 config;
	स्थिर काष्ठा sdhci_msm_offset *msm_offset =
					msm_host->offset;

	pr_debug("%s: %s: Enter\n", mmc_hostname(host->mmc), __func__);

	/*
	 * Retuning in HS400 (DDR mode) will fail, just reset the
	 * tuning block and restore the saved tuning phase.
	 */
	ret = msm_init_cm_dll(host);
	अगर (ret)
		जाओ out;

	अगर (!mmc->ios.enhanced_strobe) अणु
		/* Set the selected phase in delay line hw block */
		ret = msm_config_cm_dll_phase(host,
					      msm_host->saved_tuning_phase);
		अगर (ret)
			जाओ out;
		config = पढ़ोl_relaxed(host->ioaddr +
				msm_offset->core_dll_config);
		config |= CORE_CMD_DAT_TRACK_SEL;
		ग_लिखोl_relaxed(config, host->ioaddr +
				msm_offset->core_dll_config);
	पूर्ण

	अगर (msm_host->use_cdclp533)
		ret = sdhci_msm_cdclp533_calibration(host);
	अन्यथा
		ret = sdhci_msm_cm_dll_sdc4_calibration(host);
out:
	pr_debug("%s: %s: Exit, ret %d\n", mmc_hostname(host->mmc),
		 __func__, ret);
	वापस ret;
पूर्ण

अटल bool sdhci_msm_is_tuning_needed(काष्ठा sdhci_host *host)
अणु
	काष्ठा mmc_ios *ios = &host->mmc->ios;

	/*
	 * Tuning is required क्रम SDR104, HS200 and HS400 cards and
	 * अगर घड़ी frequency is greater than 100MHz in these modes.
	 */
	अगर (host->घड़ी <= CORE_FREQ_100MHZ ||
	    !(ios->timing == MMC_TIMING_MMC_HS400 ||
	    ios->timing == MMC_TIMING_MMC_HS200 ||
	    ios->timing == MMC_TIMING_UHS_SDR104) ||
	    ios->enhanced_strobe)
		वापस false;

	वापस true;
पूर्ण

अटल पूर्णांक sdhci_msm_restore_sdr_dll_config(काष्ठा sdhci_host *host)
अणु
	काष्ठा sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	काष्ठा sdhci_msm_host *msm_host = sdhci_pltfm_priv(pltfm_host);
	पूर्णांक ret;

	/*
	 * SDR DLL comes पूर्णांकo picture only क्रम timing modes which needs
	 * tuning.
	 */
	अगर (!sdhci_msm_is_tuning_needed(host))
		वापस 0;

	/* Reset the tuning block */
	ret = msm_init_cm_dll(host);
	अगर (ret)
		वापस ret;

	/* Restore the tuning block */
	ret = msm_config_cm_dll_phase(host, msm_host->saved_tuning_phase);

	वापस ret;
पूर्ण

अटल व्योम sdhci_msm_set_cdr(काष्ठा sdhci_host *host, bool enable)
अणु
	स्थिर काष्ठा sdhci_msm_offset *msm_offset = sdhci_priv_msm_offset(host);
	u32 config, oldconfig = पढ़ोl_relaxed(host->ioaddr +
					      msm_offset->core_dll_config);

	config = oldconfig;
	अगर (enable) अणु
		config |= CORE_CDR_EN;
		config &= ~CORE_CDR_EXT_EN;
	पूर्ण अन्यथा अणु
		config &= ~CORE_CDR_EN;
		config |= CORE_CDR_EXT_EN;
	पूर्ण

	अगर (config != oldconfig) अणु
		ग_लिखोl_relaxed(config, host->ioaddr +
			       msm_offset->core_dll_config);
	पूर्ण
पूर्ण

अटल पूर्णांक sdhci_msm_execute_tuning(काष्ठा mmc_host *mmc, u32 opcode)
अणु
	काष्ठा sdhci_host *host = mmc_priv(mmc);
	पूर्णांक tuning_seq_cnt = 10;
	u8 phase, tuned_phases[16], tuned_phase_cnt = 0;
	पूर्णांक rc;
	काष्ठा mmc_ios ios = host->mmc->ios;
	काष्ठा sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	काष्ठा sdhci_msm_host *msm_host = sdhci_pltfm_priv(pltfm_host);

	अगर (!sdhci_msm_is_tuning_needed(host)) अणु
		msm_host->use_cdr = false;
		sdhci_msm_set_cdr(host, false);
		वापस 0;
	पूर्ण

	/* Clock-Data-Recovery used to dynamically adjust RX sampling poपूर्णांक */
	msm_host->use_cdr = true;

	/*
	 * Clear tuning_करोne flag beक्रमe tuning to ensure proper
	 * HS400 settings.
	 */
	msm_host->tuning_करोne = 0;

	/*
	 * For HS400 tuning in HS200 timing requires:
	 * - select MCLK/2 in VENDOR_SPEC
	 * - program MCLK to 400MHz (or nearest supported) in GCC
	 */
	अगर (host->flags & SDHCI_HS400_TUNING) अणु
		sdhci_msm_hc_select_mode(host);
		msm_set_घड़ी_rate_क्रम_bus_mode(host, ios.घड़ी);
		host->flags &= ~SDHCI_HS400_TUNING;
	पूर्ण

retry:
	/* First of all reset the tuning block */
	rc = msm_init_cm_dll(host);
	अगर (rc)
		वापस rc;

	phase = 0;
	करो अणु
		/* Set the phase in delay line hw block */
		rc = msm_config_cm_dll_phase(host, phase);
		अगर (rc)
			वापस rc;

		rc = mmc_send_tuning(mmc, opcode, शून्य);
		अगर (!rc) अणु
			/* Tuning is successful at this tuning poपूर्णांक */
			tuned_phases[tuned_phase_cnt++] = phase;
			dev_dbg(mmc_dev(mmc), "%s: Found good phase = %d\n",
				 mmc_hostname(mmc), phase);
		पूर्ण
	पूर्ण जबतक (++phase < ARRAY_SIZE(tuned_phases));

	अगर (tuned_phase_cnt) अणु
		अगर (tuned_phase_cnt == ARRAY_SIZE(tuned_phases)) अणु
			/*
			 * All phases valid is _almost_ as bad as no phases
			 * valid.  Probably all phases are not really reliable
			 * but we didn't detect where the unreliable place is.
			 * That means we'll essentially be guessing and hoping
			 * we get a good phase.  Better to try a few बार.
			 */
			dev_dbg(mmc_dev(mmc), "%s: All phases valid; try again\n",
				mmc_hostname(mmc));
			अगर (--tuning_seq_cnt) अणु
				tuned_phase_cnt = 0;
				जाओ retry;
			पूर्ण
		पूर्ण

		rc = msm_find_most_appropriate_phase(host, tuned_phases,
						     tuned_phase_cnt);
		अगर (rc < 0)
			वापस rc;
		अन्यथा
			phase = rc;

		/*
		 * Finally set the selected phase in delay
		 * line hw block.
		 */
		rc = msm_config_cm_dll_phase(host, phase);
		अगर (rc)
			वापस rc;
		msm_host->saved_tuning_phase = phase;
		dev_dbg(mmc_dev(mmc), "%s: Setting the tuning phase to %d\n",
			 mmc_hostname(mmc), phase);
	पूर्ण अन्यथा अणु
		अगर (--tuning_seq_cnt)
			जाओ retry;
		/* Tuning failed */
		dev_dbg(mmc_dev(mmc), "%s: No tuning point found\n",
		       mmc_hostname(mmc));
		rc = -EIO;
	पूर्ण

	अगर (!rc)
		msm_host->tuning_करोne = true;
	वापस rc;
पूर्ण

/*
 * sdhci_msm_hs400 - Calibrate the DLL क्रम HS400 bus speed mode operation.
 * This needs to be करोne क्रम both tuning and enhanced_strobe mode.
 * DLL operation is only needed क्रम घड़ी > 100MHz. For घड़ी <= 100MHz
 * fixed feedback घड़ी is used.
 */
अटल व्योम sdhci_msm_hs400(काष्ठा sdhci_host *host, काष्ठा mmc_ios *ios)
अणु
	काष्ठा sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	काष्ठा sdhci_msm_host *msm_host = sdhci_pltfm_priv(pltfm_host);
	पूर्णांक ret;

	अगर (host->घड़ी > CORE_FREQ_100MHZ &&
	    (msm_host->tuning_करोne || ios->enhanced_strobe) &&
	    !msm_host->calibration_करोne) अणु
		ret = sdhci_msm_hs400_dll_calibration(host);
		अगर (!ret)
			msm_host->calibration_करोne = true;
		अन्यथा
			pr_err("%s: Failed to calibrate DLL for hs400 mode (%d)\n",
			       mmc_hostname(host->mmc), ret);
	पूर्ण
पूर्ण

अटल व्योम sdhci_msm_set_uhs_संकेतing(काष्ठा sdhci_host *host,
					अचिन्हित पूर्णांक uhs)
अणु
	काष्ठा mmc_host *mmc = host->mmc;
	काष्ठा sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	काष्ठा sdhci_msm_host *msm_host = sdhci_pltfm_priv(pltfm_host);
	u16 ctrl_2;
	u32 config;
	स्थिर काष्ठा sdhci_msm_offset *msm_offset =
					msm_host->offset;

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
		ctrl_2 |= SDHCI_CTRL_UHS_SDR50;
		अवरोध;
	हाल MMC_TIMING_MMC_HS400:
	हाल MMC_TIMING_MMC_HS200:
	हाल MMC_TIMING_UHS_SDR104:
		ctrl_2 |= SDHCI_CTRL_UHS_SDR104;
		अवरोध;
	हाल MMC_TIMING_UHS_DDR50:
	हाल MMC_TIMING_MMC_DDR52:
		ctrl_2 |= SDHCI_CTRL_UHS_DDR50;
		अवरोध;
	पूर्ण

	/*
	 * When घड़ी frequency is less than 100MHz, the feedback घड़ी must be
	 * provided and DLL must not be used so that tuning can be skipped. To
	 * provide feedback घड़ी, the mode selection can be any value less
	 * than 3'b011 in bits [2:0] of HOST CONTROL2 रेजिस्टर.
	 */
	अगर (host->घड़ी <= CORE_FREQ_100MHZ) अणु
		अगर (uhs == MMC_TIMING_MMC_HS400 ||
		    uhs == MMC_TIMING_MMC_HS200 ||
		    uhs == MMC_TIMING_UHS_SDR104)
			ctrl_2 &= ~SDHCI_CTRL_UHS_MASK;
		/*
		 * DLL is not required क्रम घड़ी <= 100MHz
		 * Thus, make sure DLL it is disabled when not required
		 */
		config = पढ़ोl_relaxed(host->ioaddr +
				msm_offset->core_dll_config);
		config |= CORE_DLL_RST;
		ग_लिखोl_relaxed(config, host->ioaddr +
				msm_offset->core_dll_config);

		config = पढ़ोl_relaxed(host->ioaddr +
				msm_offset->core_dll_config);
		config |= CORE_DLL_PDN;
		ग_लिखोl_relaxed(config, host->ioaddr +
				msm_offset->core_dll_config);

		/*
		 * The DLL needs to be restored and CDCLP533 recalibrated
		 * when the घड़ी frequency is set back to 400MHz.
		 */
		msm_host->calibration_करोne = false;
	पूर्ण

	dev_dbg(mmc_dev(mmc), "%s: clock=%u uhs=%u ctrl_2=0x%x\n",
		mmc_hostname(host->mmc), host->घड़ी, uhs, ctrl_2);
	sdhci_ग_लिखोw(host, ctrl_2, SDHCI_HOST_CONTROL2);

	अगर (mmc->ios.timing == MMC_TIMING_MMC_HS400)
		sdhci_msm_hs400(host, &mmc->ios);
पूर्ण

अटल पूर्णांक sdhci_msm_set_pincfg(काष्ठा sdhci_msm_host *msm_host, bool level)
अणु
	काष्ठा platक्रमm_device *pdev = msm_host->pdev;
	पूर्णांक ret;

	अगर (level)
		ret = pinctrl_pm_select_शेष_state(&pdev->dev);
	अन्यथा
		ret = pinctrl_pm_select_sleep_state(&pdev->dev);

	वापस ret;
पूर्ण

अटल पूर्णांक sdhci_msm_set_vmmc(काष्ठा mmc_host *mmc)
अणु
	अगर (IS_ERR(mmc->supply.vmmc))
		वापस 0;

	वापस mmc_regulator_set_ocr(mmc, mmc->supply.vmmc, mmc->ios.vdd);
पूर्ण

अटल पूर्णांक msm_toggle_vqmmc(काष्ठा sdhci_msm_host *msm_host,
			      काष्ठा mmc_host *mmc, bool level)
अणु
	पूर्णांक ret;
	काष्ठा mmc_ios ios;

	अगर (msm_host->vqmmc_enabled == level)
		वापस 0;

	अगर (level) अणु
		/* Set the IO voltage regulator to शेष voltage level */
		अगर (msm_host->caps_0 & CORE_3_0V_SUPPORT)
			ios.संकेत_voltage = MMC_SIGNAL_VOLTAGE_330;
		अन्यथा अगर (msm_host->caps_0 & CORE_1_8V_SUPPORT)
			ios.संकेत_voltage = MMC_SIGNAL_VOLTAGE_180;

		अगर (msm_host->caps_0 & CORE_VOLT_SUPPORT) अणु
			ret = mmc_regulator_set_vqmmc(mmc, &ios);
			अगर (ret < 0) अणु
				dev_err(mmc_dev(mmc), "%s: vqmmc set volgate failed: %d\n",
					mmc_hostname(mmc), ret);
				जाओ out;
			पूर्ण
		पूर्ण
		ret = regulator_enable(mmc->supply.vqmmc);
	पूर्ण अन्यथा अणु
		ret = regulator_disable(mmc->supply.vqmmc);
	पूर्ण

	अगर (ret)
		dev_err(mmc_dev(mmc), "%s: vqmm %sable failed: %d\n",
			mmc_hostname(mmc), level ? "en":"dis", ret);
	अन्यथा
		msm_host->vqmmc_enabled = level;
out:
	वापस ret;
पूर्ण

अटल पूर्णांक msm_config_vqmmc_mode(काष्ठा sdhci_msm_host *msm_host,
			      काष्ठा mmc_host *mmc, bool hpm)
अणु
	पूर्णांक load, ret;

	load = hpm ? MMC_VQMMC_MAX_LOAD_UA : 0;
	ret = regulator_set_load(mmc->supply.vqmmc, load);
	अगर (ret)
		dev_err(mmc_dev(mmc), "%s: vqmmc set load failed: %d\n",
			mmc_hostname(mmc), ret);
	वापस ret;
पूर्ण

अटल पूर्णांक sdhci_msm_set_vqmmc(काष्ठा sdhci_msm_host *msm_host,
			      काष्ठा mmc_host *mmc, bool level)
अणु
	पूर्णांक ret;
	bool always_on;

	अगर (IS_ERR(mmc->supply.vqmmc) ||
			(mmc->ios.घातer_mode == MMC_POWER_UNDEFINED))
		वापस 0;
	/*
	 * For eMMC करोn't turn off Vqmmc, Instead just configure it in LPM
	 * and HPM modes by setting the corresponding load.
	 *
	 * Till eMMC is initialized (i.e. always_on == 0), just turn on/off
	 * Vqmmc. Vqmmc माला_लो turned off only अगर init fails and mmc_घातer_off
	 * माला_लो invoked. Once eMMC is initialized (i.e. always_on == 1),
	 * Vqmmc should reमुख्य ON, So just set the load instead of turning it
	 * off/on.
	 */
	always_on = !mmc_card_is_removable(mmc) &&
			mmc->card && mmc_card_mmc(mmc->card);

	अगर (always_on)
		ret = msm_config_vqmmc_mode(msm_host, mmc, level);
	अन्यथा
		ret = msm_toggle_vqmmc(msm_host, mmc, level);

	वापस ret;
पूर्ण

अटल अंतरभूत व्योम sdhci_msm_init_pwr_irq_रुको(काष्ठा sdhci_msm_host *msm_host)
अणु
	init_रुकोqueue_head(&msm_host->pwr_irq_रुको);
पूर्ण

अटल अंतरभूत व्योम sdhci_msm_complete_pwr_irq_रुको(
		काष्ठा sdhci_msm_host *msm_host)
अणु
	wake_up(&msm_host->pwr_irq_रुको);
पूर्ण

/*
 * sdhci_msm_check_घातer_status API should be called when रेजिस्टरs ग_लिखोs
 * which can toggle sdhci IO bus ON/OFF or change IO lines HIGH/LOW happens.
 * To what state the रेजिस्टर ग_लिखोs will change the IO lines should be passed
 * as the argument req_type. This API will check whether the IO line's state
 * is alपढ़ोy the expected state and will रुको क्रम घातer irq only अगर
 * घातer irq is expected to be triggered based on the current IO line state
 * and expected IO line state.
 */
अटल व्योम sdhci_msm_check_घातer_status(काष्ठा sdhci_host *host, u32 req_type)
अणु
	काष्ठा sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	काष्ठा sdhci_msm_host *msm_host = sdhci_pltfm_priv(pltfm_host);
	bool करोne = false;
	u32 val = SWITCHABLE_SIGNALING_VOLTAGE;
	स्थिर काष्ठा sdhci_msm_offset *msm_offset =
					msm_host->offset;

	pr_debug("%s: %s: request %d curr_pwr_state %x curr_io_level %x\n",
			mmc_hostname(host->mmc), __func__, req_type,
			msm_host->curr_pwr_state, msm_host->curr_io_level);

	/*
	 * The घातer पूर्णांकerrupt will not be generated क्रम संकेत voltage
	 * चयनes अगर SWITCHABLE_SIGNALING_VOLTAGE in MCI_GENERICS is not set.
	 * Since sdhci-msm-v5, this bit has been हटाओd and SW must consider
	 * it as always set.
	 */
	अगर (!msm_host->mci_हटाओd)
		val = msm_host_पढ़ोl(msm_host, host,
				msm_offset->core_generics);
	अगर ((req_type & REQ_IO_HIGH || req_type & REQ_IO_LOW) &&
	    !(val & SWITCHABLE_SIGNALING_VOLTAGE)) अणु
		वापस;
	पूर्ण

	/*
	 * The IRQ क्रम request type IO High/LOW will be generated when -
	 * there is a state change in 1.8V enable bit (bit 3) of
	 * SDHCI_HOST_CONTROL2 रेजिस्टर. The reset state of that bit is 0
	 * which indicates 3.3V IO voltage. So, when MMC core layer tries
	 * to set it to 3.3V beक्रमe card detection happens, the
	 * IRQ करोesn't get triggered as there is no state change in this bit.
	 * The driver alपढ़ोy handles this हाल by changing the IO voltage
	 * level to high as part of controller घातer up sequence. Hence, check
	 * क्रम host->pwr to handle a हाल where IO voltage high request is
	 * issued even beक्रमe controller घातer up.
	 */
	अगर ((req_type & REQ_IO_HIGH) && !host->pwr) अणु
		pr_debug("%s: do not wait for power IRQ that never comes, req_type: %d\n",
				mmc_hostname(host->mmc), req_type);
		वापस;
	पूर्ण
	अगर ((req_type & msm_host->curr_pwr_state) ||
			(req_type & msm_host->curr_io_level))
		करोne = true;
	/*
	 * This is needed here to handle हालs where रेजिस्टर ग_लिखोs will
	 * not change the current bus state or io level of the controller.
	 * In this हाल, no घातer irq will be triggerred and we should
	 * not रुको.
	 */
	अगर (!करोne) अणु
		अगर (!रुको_event_समयout(msm_host->pwr_irq_रुको,
				msm_host->pwr_irq_flag,
				msecs_to_jअगरfies(MSM_PWR_IRQ_TIMEOUT_MS)))
			dev_warn(&msm_host->pdev->dev,
				 "%s: pwr_irq for req: (%d) timed out\n",
				 mmc_hostname(host->mmc), req_type);
	पूर्ण
	pr_debug("%s: %s: request %d done\n", mmc_hostname(host->mmc),
			__func__, req_type);
पूर्ण

अटल व्योम sdhci_msm_dump_pwr_ctrl_regs(काष्ठा sdhci_host *host)
अणु
	काष्ठा sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	काष्ठा sdhci_msm_host *msm_host = sdhci_pltfm_priv(pltfm_host);
	स्थिर काष्ठा sdhci_msm_offset *msm_offset =
					msm_host->offset;

	pr_err("%s: PWRCTL_STATUS: 0x%08x | PWRCTL_MASK: 0x%08x | PWRCTL_CTL: 0x%08x\n",
		mmc_hostname(host->mmc),
		msm_host_पढ़ोl(msm_host, host, msm_offset->core_pwrctl_status),
		msm_host_पढ़ोl(msm_host, host, msm_offset->core_pwrctl_mask),
		msm_host_पढ़ोl(msm_host, host, msm_offset->core_pwrctl_ctl));
पूर्ण

अटल व्योम sdhci_msm_handle_pwr_irq(काष्ठा sdhci_host *host, पूर्णांक irq)
अणु
	काष्ठा sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	काष्ठा sdhci_msm_host *msm_host = sdhci_pltfm_priv(pltfm_host);
	काष्ठा mmc_host *mmc = host->mmc;
	u32 irq_status, irq_ack = 0;
	पूर्णांक retry = 10, ret;
	u32 pwr_state = 0, io_level = 0;
	u32 config;
	स्थिर काष्ठा sdhci_msm_offset *msm_offset = msm_host->offset;

	irq_status = msm_host_पढ़ोl(msm_host, host,
			msm_offset->core_pwrctl_status);
	irq_status &= INT_MASK;

	msm_host_ग_लिखोl(msm_host, irq_status, host,
			msm_offset->core_pwrctl_clear);

	/*
	 * There is a rare HW scenario where the first clear pulse could be
	 * lost when actual reset and clear/पढ़ो of status रेजिस्टर is
	 * happening at a समय. Hence, retry क्रम at least 10 बार to make
	 * sure status रेजिस्टर is cleared. Otherwise, this will result in
	 * a spurious घातer IRQ resulting in प्रणाली instability.
	 */
	जबतक (irq_status & msm_host_पढ़ोl(msm_host, host,
				msm_offset->core_pwrctl_status)) अणु
		अगर (retry == 0) अणु
			pr_err("%s: Timedout clearing (0x%x) pwrctl status register\n",
					mmc_hostname(host->mmc), irq_status);
			sdhci_msm_dump_pwr_ctrl_regs(host);
			WARN_ON(1);
			अवरोध;
		पूर्ण
		msm_host_ग_लिखोl(msm_host, irq_status, host,
			msm_offset->core_pwrctl_clear);
		retry--;
		udelay(10);
	पूर्ण

	/* Handle BUS ON/OFF*/
	अगर (irq_status & CORE_PWRCTL_BUS_ON) अणु
		pwr_state = REQ_BUS_ON;
		io_level = REQ_IO_HIGH;
	पूर्ण
	अगर (irq_status & CORE_PWRCTL_BUS_OFF) अणु
		pwr_state = REQ_BUS_OFF;
		io_level = REQ_IO_LOW;
	पूर्ण

	अगर (pwr_state) अणु
		ret = sdhci_msm_set_vmmc(mmc);
		अगर (!ret)
			ret = sdhci_msm_set_vqmmc(msm_host, mmc,
					pwr_state & REQ_BUS_ON);
		अगर (!ret)
			ret = sdhci_msm_set_pincfg(msm_host,
					pwr_state & REQ_BUS_ON);
		अगर (!ret)
			irq_ack |= CORE_PWRCTL_BUS_SUCCESS;
		अन्यथा
			irq_ack |= CORE_PWRCTL_BUS_FAIL;
	पूर्ण

	/* Handle IO LOW/HIGH */
	अगर (irq_status & CORE_PWRCTL_IO_LOW)
		io_level = REQ_IO_LOW;

	अगर (irq_status & CORE_PWRCTL_IO_HIGH)
		io_level = REQ_IO_HIGH;

	अगर (io_level)
		irq_ack |= CORE_PWRCTL_IO_SUCCESS;

	अगर (io_level && !IS_ERR(mmc->supply.vqmmc) && !pwr_state) अणु
		ret = mmc_regulator_set_vqmmc(mmc, &mmc->ios);
		अगर (ret < 0) अणु
			dev_err(mmc_dev(mmc), "%s: IO_level setting failed(%d). signal_voltage: %d, vdd: %d irq_status: 0x%08x\n",
					mmc_hostname(mmc), ret,
					mmc->ios.संकेत_voltage, mmc->ios.vdd,
					irq_status);
			irq_ack |= CORE_PWRCTL_IO_FAIL;
		पूर्ण
	पूर्ण

	/*
	 * The driver has to acknowledge the पूर्णांकerrupt, चयन voltages and
	 * report back अगर it succeded or not to this रेजिस्टर. The voltage
	 * चयनes are handled by the sdhci core, so just report success.
	 */
	msm_host_ग_लिखोl(msm_host, irq_ack, host,
			msm_offset->core_pwrctl_ctl);

	/*
	 * If we करोn't have info regarding the voltage levels supported by
	 * regulators, करोn't change the IO PAD PWR SWITCH.
	 */
	अगर (msm_host->caps_0 & CORE_VOLT_SUPPORT) अणु
		u32 new_config;
		/*
		 * We should unset IO PAD PWR चयन only अगर the रेजिस्टर ग_लिखो
		 * can set IO lines high and the regulator also चयनes to 3 V.
		 * Else, we should keep the IO PAD PWR चयन set.
		 * This is applicable to certain tarमाला_लो where eMMC vccq supply
		 * is only 1.8V. In such tarमाला_लो, even during REQ_IO_HIGH, the
		 * IO PAD PWR चयन must be kept set to reflect actual
		 * regulator voltage. This way, during initialization of
		 * controllers with only 1.8V, we will set the IO PAD bit
		 * without रुकोing क्रम a REQ_IO_LOW.
		 */
		config = पढ़ोl_relaxed(host->ioaddr +
				msm_offset->core_venकरोr_spec);
		new_config = config;

		अगर ((io_level & REQ_IO_HIGH) &&
				(msm_host->caps_0 & CORE_3_0V_SUPPORT))
			new_config &= ~CORE_IO_PAD_PWR_SWITCH;
		अन्यथा अगर ((io_level & REQ_IO_LOW) ||
				(msm_host->caps_0 & CORE_1_8V_SUPPORT))
			new_config |= CORE_IO_PAD_PWR_SWITCH;

		अगर (config ^ new_config)
			ग_लिखोl_relaxed(new_config, host->ioaddr +
					msm_offset->core_venकरोr_spec);
	पूर्ण

	अगर (pwr_state)
		msm_host->curr_pwr_state = pwr_state;
	अगर (io_level)
		msm_host->curr_io_level = io_level;

	dev_dbg(mmc_dev(mmc), "%s: %s: Handled IRQ(%d), irq_status=0x%x, ack=0x%x\n",
		mmc_hostname(msm_host->mmc), __func__, irq, irq_status,
		irq_ack);
पूर्ण

अटल irqवापस_t sdhci_msm_pwr_irq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा sdhci_host *host = (काष्ठा sdhci_host *)data;
	काष्ठा sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	काष्ठा sdhci_msm_host *msm_host = sdhci_pltfm_priv(pltfm_host);

	sdhci_msm_handle_pwr_irq(host, irq);
	msm_host->pwr_irq_flag = 1;
	sdhci_msm_complete_pwr_irq_रुको(msm_host);


	वापस IRQ_HANDLED;
पूर्ण

अटल अचिन्हित पूर्णांक sdhci_msm_get_max_घड़ी(काष्ठा sdhci_host *host)
अणु
	काष्ठा sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	काष्ठा sdhci_msm_host *msm_host = sdhci_pltfm_priv(pltfm_host);
	काष्ठा clk *core_clk = msm_host->bulk_clks[0].clk;

	वापस clk_round_rate(core_clk, अच_दीर्घ_उच्च);
पूर्ण

अटल अचिन्हित पूर्णांक sdhci_msm_get_min_घड़ी(काष्ठा sdhci_host *host)
अणु
	वापस SDHCI_MSM_MIN_CLOCK;
पूर्ण

/*
 * __sdhci_msm_set_घड़ी - sdhci_msm घड़ी control.
 *
 * Description:
 * MSM controller करोes not use पूर्णांकernal भागider and
 * instead directly control the GCC घड़ी as per
 * HW recommendation.
 **/
अटल व्योम __sdhci_msm_set_घड़ी(काष्ठा sdhci_host *host, अचिन्हित पूर्णांक घड़ी)
अणु
	u16 clk;

	sdhci_ग_लिखोw(host, 0, SDHCI_CLOCK_CONTROL);

	अगर (घड़ी == 0)
		वापस;

	/*
	 * MSM controller करो not use घड़ी भागider.
	 * Thus पढ़ो SDHCI_CLOCK_CONTROL and only enable
	 * घड़ी with no भागider value programmed.
	 */
	clk = sdhci_पढ़ोw(host, SDHCI_CLOCK_CONTROL);
	sdhci_enable_clk(host, clk);
पूर्ण

/* sdhci_msm_set_घड़ी - Called with (host->lock) spinlock held. */
अटल व्योम sdhci_msm_set_घड़ी(काष्ठा sdhci_host *host, अचिन्हित पूर्णांक घड़ी)
अणु
	काष्ठा sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	काष्ठा sdhci_msm_host *msm_host = sdhci_pltfm_priv(pltfm_host);

	अगर (!घड़ी) अणु
		host->mmc->actual_घड़ी = msm_host->clk_rate = 0;
		जाओ out;
	पूर्ण

	sdhci_msm_hc_select_mode(host);

	msm_set_घड़ी_rate_क्रम_bus_mode(host, घड़ी);
out:
	__sdhci_msm_set_घड़ी(host, घड़ी);
पूर्ण

/*****************************************************************************\
 *                                                                           *
 * Inline Crypto Engine (ICE) support                                        *
 *                                                                           *
\*****************************************************************************/

#अगर_घोषित CONFIG_MMC_CRYPTO

#घोषणा AES_256_XTS_KEY_SIZE			64

/* QCOM ICE रेजिस्टरs */

#घोषणा QCOM_ICE_REG_VERSION			0x0008

#घोषणा QCOM_ICE_REG_FUSE_SETTING		0x0010
#घोषणा QCOM_ICE_FUSE_SETTING_MASK		0x1
#घोषणा QCOM_ICE_FORCE_HW_KEY0_SETTING_MASK	0x2
#घोषणा QCOM_ICE_FORCE_HW_KEY1_SETTING_MASK	0x4

#घोषणा QCOM_ICE_REG_BIST_STATUS		0x0070
#घोषणा QCOM_ICE_BIST_STATUS_MASK		0xF0000000

#घोषणा QCOM_ICE_REG_ADVANCED_CONTROL		0x1000

#घोषणा sdhci_msm_ice_ग_लिखोl(host, val, reg)	\
	ग_लिखोl((val), (host)->ice_mem + (reg))
#घोषणा sdhci_msm_ice_पढ़ोl(host, reg)	\
	पढ़ोl((host)->ice_mem + (reg))

अटल bool sdhci_msm_ice_supported(काष्ठा sdhci_msm_host *msm_host)
अणु
	काष्ठा device *dev = mmc_dev(msm_host->mmc);
	u32 regval = sdhci_msm_ice_पढ़ोl(msm_host, QCOM_ICE_REG_VERSION);
	पूर्णांक major = regval >> 24;
	पूर्णांक minor = (regval >> 16) & 0xFF;
	पूर्णांक step = regval & 0xFFFF;

	/* For now this driver only supports ICE version 3. */
	अगर (major != 3) अणु
		dev_warn(dev, "Unsupported ICE version: v%d.%d.%d\n",
			 major, minor, step);
		वापस false;
	पूर्ण

	dev_info(dev, "Found QC Inline Crypto Engine (ICE) v%d.%d.%d\n",
		 major, minor, step);

	/* If fuses are blown, ICE might not work in the standard way. */
	regval = sdhci_msm_ice_पढ़ोl(msm_host, QCOM_ICE_REG_FUSE_SETTING);
	अगर (regval & (QCOM_ICE_FUSE_SETTING_MASK |
		      QCOM_ICE_FORCE_HW_KEY0_SETTING_MASK |
		      QCOM_ICE_FORCE_HW_KEY1_SETTING_MASK)) अणु
		dev_warn(dev, "Fuses are blown; ICE is unusable!\n");
		वापस false;
	पूर्ण
	वापस true;
पूर्ण

अटल अंतरभूत काष्ठा clk *sdhci_msm_ice_get_clk(काष्ठा device *dev)
अणु
	वापस devm_clk_get(dev, "ice");
पूर्ण

अटल पूर्णांक sdhci_msm_ice_init(काष्ठा sdhci_msm_host *msm_host,
			      काष्ठा cqhci_host *cq_host)
अणु
	काष्ठा mmc_host *mmc = msm_host->mmc;
	काष्ठा device *dev = mmc_dev(mmc);
	काष्ठा resource *res;

	अगर (!(cqhci_पढ़ोl(cq_host, CQHCI_CAP) & CQHCI_CAP_CS))
		वापस 0;

	res = platक्रमm_get_resource_byname(msm_host->pdev, IORESOURCE_MEM,
					   "ice");
	अगर (!res) अणु
		dev_warn(dev, "ICE registers not found\n");
		जाओ disable;
	पूर्ण

	अगर (!qcom_scm_ice_available()) अणु
		dev_warn(dev, "ICE SCM interface not found\n");
		जाओ disable;
	पूर्ण

	msm_host->ice_mem = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(msm_host->ice_mem))
		वापस PTR_ERR(msm_host->ice_mem);

	अगर (!sdhci_msm_ice_supported(msm_host))
		जाओ disable;

	mmc->caps2 |= MMC_CAP2_CRYPTO;
	वापस 0;

disable:
	dev_warn(dev, "Disabling inline encryption support\n");
	वापस 0;
पूर्ण

अटल व्योम sdhci_msm_ice_low_घातer_mode_enable(काष्ठा sdhci_msm_host *msm_host)
अणु
	u32 regval;

	regval = sdhci_msm_ice_पढ़ोl(msm_host, QCOM_ICE_REG_ADVANCED_CONTROL);
	/*
	 * Enable low घातer mode sequence
	 * [0]-0, [1]-0, [2]-0, [3]-E, [4]-0, [5]-0, [6]-0, [7]-0
	 */
	regval |= 0x7000;
	sdhci_msm_ice_ग_लिखोl(msm_host, regval, QCOM_ICE_REG_ADVANCED_CONTROL);
पूर्ण

अटल व्योम sdhci_msm_ice_optimization_enable(काष्ठा sdhci_msm_host *msm_host)
अणु
	u32 regval;

	/* ICE Optimizations Enable Sequence */
	regval = sdhci_msm_ice_पढ़ोl(msm_host, QCOM_ICE_REG_ADVANCED_CONTROL);
	regval |= 0xD807100;
	/* ICE HPG requires delay beक्रमe writing */
	udelay(5);
	sdhci_msm_ice_ग_लिखोl(msm_host, regval, QCOM_ICE_REG_ADVANCED_CONTROL);
	udelay(5);
पूर्ण

/*
 * Wait until the ICE BIST (built-in self-test) has completed.
 *
 * This may be necessary beक्रमe ICE can be used.
 *
 * Note that we करोn't really care whether the BIST passed or failed; we really
 * just want to make sure that it isn't still running.  This is because (a) the
 * BIST is a FIPS compliance thing that never fails in practice, (b) ICE is
 * करोcumented to reject crypto requests अगर the BIST fails, so we needn't करो it
 * in software too, and (c) properly testing storage encryption requires testing
 * the full storage stack anyway, and not relying on hardware-level self-tests.
 */
अटल पूर्णांक sdhci_msm_ice_रुको_bist_status(काष्ठा sdhci_msm_host *msm_host)
अणु
	u32 regval;
	पूर्णांक err;

	err = पढ़ोl_poll_समयout(msm_host->ice_mem + QCOM_ICE_REG_BIST_STATUS,
				 regval, !(regval & QCOM_ICE_BIST_STATUS_MASK),
				 50, 5000);
	अगर (err)
		dev_err(mmc_dev(msm_host->mmc),
			"Timed out waiting for ICE self-test to complete\n");
	वापस err;
पूर्ण

अटल व्योम sdhci_msm_ice_enable(काष्ठा sdhci_msm_host *msm_host)
अणु
	अगर (!(msm_host->mmc->caps2 & MMC_CAP2_CRYPTO))
		वापस;
	sdhci_msm_ice_low_घातer_mode_enable(msm_host);
	sdhci_msm_ice_optimization_enable(msm_host);
	sdhci_msm_ice_रुको_bist_status(msm_host);
पूर्ण

अटल पूर्णांक __maybe_unused sdhci_msm_ice_resume(काष्ठा sdhci_msm_host *msm_host)
अणु
	अगर (!(msm_host->mmc->caps2 & MMC_CAP2_CRYPTO))
		वापस 0;
	वापस sdhci_msm_ice_रुको_bist_status(msm_host);
पूर्ण

/*
 * Program a key पूर्णांकo a QC ICE keyslot, or evict a keyslot.  QC ICE requires
 * venकरोr-specअगरic SCM calls क्रम this; it करोesn't support the standard way.
 */
अटल पूर्णांक sdhci_msm_program_key(काष्ठा cqhci_host *cq_host,
				 स्थिर जोड़ cqhci_crypto_cfg_entry *cfg,
				 पूर्णांक slot)
अणु
	काष्ठा device *dev = mmc_dev(cq_host->mmc);
	जोड़ cqhci_crypto_cap_entry cap;
	जोड़ अणु
		u8 bytes[AES_256_XTS_KEY_SIZE];
		u32 words[AES_256_XTS_KEY_SIZE / माप(u32)];
	पूर्ण key;
	पूर्णांक i;
	पूर्णांक err;

	अगर (!(cfg->config_enable & CQHCI_CRYPTO_CONFIGURATION_ENABLE))
		वापस qcom_scm_ice_invalidate_key(slot);

	/* Only AES-256-XTS has been tested so far. */
	cap = cq_host->crypto_cap_array[cfg->crypto_cap_idx];
	अगर (cap.algorithm_id != CQHCI_CRYPTO_ALG_AES_XTS ||
	    cap.key_size != CQHCI_CRYPTO_KEY_SIZE_256) अणु
		dev_err_ratelimited(dev,
				    "Unhandled crypto capability; algorithm_id=%d, key_size=%d\n",
				    cap.algorithm_id, cap.key_size);
		वापस -EINVAL;
	पूर्ण

	स_नकल(key.bytes, cfg->crypto_key, AES_256_XTS_KEY_SIZE);

	/*
	 * The SCM call byte-swaps the 32-bit words of the key.  So we have to
	 * करो the same, in order क्रम the final key be correct.
	 */
	क्रम (i = 0; i < ARRAY_SIZE(key.words); i++)
		__cpu_to_be32s(&key.words[i]);

	err = qcom_scm_ice_set_key(slot, key.bytes, AES_256_XTS_KEY_SIZE,
				   QCOM_SCM_ICE_CIPHER_AES_256_XTS,
				   cfg->data_unit_size);
	memzero_explicit(&key, माप(key));
	वापस err;
पूर्ण
#अन्यथा /* CONFIG_MMC_CRYPTO */
अटल अंतरभूत काष्ठा clk *sdhci_msm_ice_get_clk(काष्ठा device *dev)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत पूर्णांक sdhci_msm_ice_init(काष्ठा sdhci_msm_host *msm_host,
				     काष्ठा cqhci_host *cq_host)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम sdhci_msm_ice_enable(काष्ठा sdhci_msm_host *msm_host)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक __maybe_unused
sdhci_msm_ice_resume(काष्ठा sdhci_msm_host *msm_host)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर /* !CONFIG_MMC_CRYPTO */

/*****************************************************************************\
 *                                                                           *
 * MSM Command Queue Engine (CQE)                                            *
 *                                                                           *
\*****************************************************************************/

अटल u32 sdhci_msm_cqe_irq(काष्ठा sdhci_host *host, u32 पूर्णांकmask)
अणु
	पूर्णांक cmd_error = 0;
	पूर्णांक data_error = 0;

	अगर (!sdhci_cqe_irq(host, पूर्णांकmask, &cmd_error, &data_error))
		वापस पूर्णांकmask;

	cqhci_irq(host->mmc, पूर्णांकmask, cmd_error, data_error);
	वापस 0;
पूर्ण

अटल व्योम sdhci_msm_cqe_enable(काष्ठा mmc_host *mmc)
अणु
	काष्ठा sdhci_host *host = mmc_priv(mmc);
	काष्ठा sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	काष्ठा sdhci_msm_host *msm_host = sdhci_pltfm_priv(pltfm_host);

	sdhci_cqe_enable(mmc);
	sdhci_msm_ice_enable(msm_host);
पूर्ण

अटल व्योम sdhci_msm_cqe_disable(काष्ठा mmc_host *mmc, bool recovery)
अणु
	काष्ठा sdhci_host *host = mmc_priv(mmc);
	अचिन्हित दीर्घ flags;
	u32 ctrl;

	/*
	 * When CQE is halted, the legacy SDHCI path operates only
	 * on 16-byte descriptors in 64bit mode.
	 */
	अगर (host->flags & SDHCI_USE_64_BIT_DMA)
		host->desc_sz = 16;

	spin_lock_irqsave(&host->lock, flags);

	/*
	 * During CQE command transfers, command complete bit माला_लो latched.
	 * So s/w should clear command complete पूर्णांकerrupt status when CQE is
	 * either halted or disabled. Otherwise unexpected SDCHI legacy
	 * पूर्णांकerrupt माला_लो triggered when CQE is halted/disabled.
	 */
	ctrl = sdhci_पढ़ोl(host, SDHCI_INT_ENABLE);
	ctrl |= SDHCI_INT_RESPONSE;
	sdhci_ग_लिखोl(host,  ctrl, SDHCI_INT_ENABLE);
	sdhci_ग_लिखोl(host, SDHCI_INT_RESPONSE, SDHCI_INT_STATUS);

	spin_unlock_irqrestore(&host->lock, flags);

	sdhci_cqe_disable(mmc, recovery);
पूर्ण

अटल स्थिर काष्ठा cqhci_host_ops sdhci_msm_cqhci_ops = अणु
	.enable		= sdhci_msm_cqe_enable,
	.disable	= sdhci_msm_cqe_disable,
#अगर_घोषित CONFIG_MMC_CRYPTO
	.program_key	= sdhci_msm_program_key,
#पूर्ण_अगर
पूर्ण;

अटल पूर्णांक sdhci_msm_cqe_add_host(काष्ठा sdhci_host *host,
				काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	काष्ठा sdhci_msm_host *msm_host = sdhci_pltfm_priv(pltfm_host);
	काष्ठा cqhci_host *cq_host;
	bool dma64;
	u32 cqcfg;
	पूर्णांक ret;

	/*
	 * When CQE is halted, SDHC operates only on 16byte ADMA descriptors.
	 * So ensure ADMA table is allocated क्रम 16byte descriptors.
	 */
	अगर (host->caps & SDHCI_CAN_64BIT)
		host->alloc_desc_sz = 16;

	ret = sdhci_setup_host(host);
	अगर (ret)
		वापस ret;

	cq_host = cqhci_pltfm_init(pdev);
	अगर (IS_ERR(cq_host)) अणु
		ret = PTR_ERR(cq_host);
		dev_err(&pdev->dev, "cqhci-pltfm init: failed: %d\n", ret);
		जाओ cleanup;
	पूर्ण

	msm_host->mmc->caps2 |= MMC_CAP2_CQE | MMC_CAP2_CQE_DCMD;
	cq_host->ops = &sdhci_msm_cqhci_ops;

	dma64 = host->flags & SDHCI_USE_64_BIT_DMA;

	ret = sdhci_msm_ice_init(msm_host, cq_host);
	अगर (ret)
		जाओ cleanup;

	ret = cqhci_init(cq_host, host->mmc, dma64);
	अगर (ret) अणु
		dev_err(&pdev->dev, "%s: CQE init: failed (%d)\n",
				mmc_hostname(host->mmc), ret);
		जाओ cleanup;
	पूर्ण

	/* Disable cqe reset due to cqe enable संकेत */
	cqcfg = cqhci_पढ़ोl(cq_host, CQHCI_VENDOR_CFG1);
	cqcfg |= CQHCI_VENDOR_DIS_RST_ON_CQ_EN;
	cqhci_ग_लिखोl(cq_host, cqcfg, CQHCI_VENDOR_CFG1);

	/*
	 * SDHC expects 12byte ADMA descriptors till CQE is enabled.
	 * So limit desc_sz to 12 so that the data commands that are sent
	 * during card initialization (beक्रमe CQE माला_लो enabled) would
	 * get executed without any issues.
	 */
	अगर (host->flags & SDHCI_USE_64_BIT_DMA)
		host->desc_sz = 12;

	ret = __sdhci_add_host(host);
	अगर (ret)
		जाओ cleanup;

	dev_info(&pdev->dev, "%s: CQE init: success\n",
			mmc_hostname(host->mmc));
	वापस ret;

cleanup:
	sdhci_cleanup_host(host);
	वापस ret;
पूर्ण

/*
 * Platक्रमm specअगरic रेजिस्टर ग_लिखो functions. This is so that, अगर any
 * रेजिस्टर ग_लिखो needs to be followed up by platक्रमm specअगरic actions,
 * they can be added here. These functions can go to sleep when ग_लिखोs
 * to certain रेजिस्टरs are करोne.
 * These functions are relying on sdhci_set_ios not using spinlock.
 */
अटल पूर्णांक __sdhci_msm_check_ग_लिखो(काष्ठा sdhci_host *host, u16 val, पूर्णांक reg)
अणु
	काष्ठा sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	काष्ठा sdhci_msm_host *msm_host = sdhci_pltfm_priv(pltfm_host);
	u32 req_type = 0;

	चयन (reg) अणु
	हाल SDHCI_HOST_CONTROL2:
		req_type = (val & SDHCI_CTRL_VDD_180) ? REQ_IO_LOW :
			REQ_IO_HIGH;
		अवरोध;
	हाल SDHCI_SOFTWARE_RESET:
		अगर (host->pwr && (val & SDHCI_RESET_ALL))
			req_type = REQ_BUS_OFF;
		अवरोध;
	हाल SDHCI_POWER_CONTROL:
		req_type = !val ? REQ_BUS_OFF : REQ_BUS_ON;
		अवरोध;
	हाल SDHCI_TRANSFER_MODE:
		msm_host->transfer_mode = val;
		अवरोध;
	हाल SDHCI_COMMAND:
		अगर (!msm_host->use_cdr)
			अवरोध;
		अगर ((msm_host->transfer_mode & SDHCI_TRNS_READ) &&
		    SDHCI_GET_CMD(val) != MMC_SEND_TUNING_BLOCK_HS200 &&
		    SDHCI_GET_CMD(val) != MMC_SEND_TUNING_BLOCK)
			sdhci_msm_set_cdr(host, true);
		अन्यथा
			sdhci_msm_set_cdr(host, false);
		अवरोध;
	पूर्ण

	अगर (req_type) अणु
		msm_host->pwr_irq_flag = 0;
		/*
		 * Since this रेजिस्टर ग_लिखो may trigger a घातer irq, ensure
		 * all previous रेजिस्टर ग_लिखोs are complete by this poपूर्णांक.
		 */
		mb();
	पूर्ण
	वापस req_type;
पूर्ण

/* This function may sleep*/
अटल व्योम sdhci_msm_ग_लिखोw(काष्ठा sdhci_host *host, u16 val, पूर्णांक reg)
अणु
	u32 req_type = 0;

	req_type = __sdhci_msm_check_ग_लिखो(host, val, reg);
	ग_लिखोw_relaxed(val, host->ioaddr + reg);

	अगर (req_type)
		sdhci_msm_check_घातer_status(host, req_type);
पूर्ण

/* This function may sleep*/
अटल व्योम sdhci_msm_ग_लिखोb(काष्ठा sdhci_host *host, u8 val, पूर्णांक reg)
अणु
	u32 req_type = 0;

	req_type = __sdhci_msm_check_ग_लिखो(host, val, reg);

	ग_लिखोb_relaxed(val, host->ioaddr + reg);

	अगर (req_type)
		sdhci_msm_check_घातer_status(host, req_type);
पूर्ण

अटल व्योम sdhci_msm_set_regulator_caps(काष्ठा sdhci_msm_host *msm_host)
अणु
	काष्ठा mmc_host *mmc = msm_host->mmc;
	काष्ठा regulator *supply = mmc->supply.vqmmc;
	u32 caps = 0, config;
	काष्ठा sdhci_host *host = mmc_priv(mmc);
	स्थिर काष्ठा sdhci_msm_offset *msm_offset = msm_host->offset;

	अगर (!IS_ERR(mmc->supply.vqmmc)) अणु
		अगर (regulator_is_supported_voltage(supply, 1700000, 1950000))
			caps |= CORE_1_8V_SUPPORT;
		अगर (regulator_is_supported_voltage(supply, 2700000, 3600000))
			caps |= CORE_3_0V_SUPPORT;

		अगर (!caps)
			pr_warn("%s: 1.8/3V not supported for vqmmc\n",
					mmc_hostname(mmc));
	पूर्ण

	अगर (caps) अणु
		/*
		 * Set the PAD_PWR_SWITCH_EN bit so that the PAD_PWR_SWITCH
		 * bit can be used as required later on.
		 */
		u32 io_level = msm_host->curr_io_level;

		config = पढ़ोl_relaxed(host->ioaddr +
				msm_offset->core_venकरोr_spec);
		config |= CORE_IO_PAD_PWR_SWITCH_EN;

		अगर ((io_level & REQ_IO_HIGH) && (caps &	CORE_3_0V_SUPPORT))
			config &= ~CORE_IO_PAD_PWR_SWITCH;
		अन्यथा अगर ((io_level & REQ_IO_LOW) || (caps & CORE_1_8V_SUPPORT))
			config |= CORE_IO_PAD_PWR_SWITCH;

		ग_लिखोl_relaxed(config,
				host->ioaddr + msm_offset->core_venकरोr_spec);
	पूर्ण
	msm_host->caps_0 |= caps;
	pr_debug("%s: supported caps: 0x%08x\n", mmc_hostname(mmc), caps);
पूर्ण

अटल व्योम sdhci_msm_reset(काष्ठा sdhci_host *host, u8 mask)
अणु
	अगर ((host->mmc->caps2 & MMC_CAP2_CQE) && (mask & SDHCI_RESET_ALL))
		cqhci_deactivate(host->mmc);
	sdhci_reset(host, mask);
पूर्ण

अटल पूर्णांक sdhci_msm_रेजिस्टर_vreg(काष्ठा sdhci_msm_host *msm_host)
अणु
	पूर्णांक ret;

	ret = mmc_regulator_get_supply(msm_host->mmc);
	अगर (ret)
		वापस ret;

	sdhci_msm_set_regulator_caps(msm_host);

	वापस 0;
पूर्ण

अटल पूर्णांक sdhci_msm_start_संकेत_voltage_चयन(काष्ठा mmc_host *mmc,
				      काष्ठा mmc_ios *ios)
अणु
	काष्ठा sdhci_host *host = mmc_priv(mmc);
	u16 ctrl, status;

	/*
	 * Signal Voltage Switching is only applicable क्रम Host Controllers
	 * v3.00 and above.
	 */
	अगर (host->version < SDHCI_SPEC_300)
		वापस 0;

	ctrl = sdhci_पढ़ोw(host, SDHCI_HOST_CONTROL2);

	चयन (ios->संकेत_voltage) अणु
	हाल MMC_SIGNAL_VOLTAGE_330:
		अगर (!(host->flags & SDHCI_SIGNALING_330))
			वापस -EINVAL;

		/* Set 1.8V Signal Enable in the Host Control2 रेजिस्टर to 0 */
		ctrl &= ~SDHCI_CTRL_VDD_180;
		अवरोध;
	हाल MMC_SIGNAL_VOLTAGE_180:
		अगर (!(host->flags & SDHCI_SIGNALING_180))
			वापस -EINVAL;

		/* Enable 1.8V Signal Enable in the Host Control2 रेजिस्टर */
		ctrl |= SDHCI_CTRL_VDD_180;
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	sdhci_ग_लिखोw(host, ctrl, SDHCI_HOST_CONTROL2);

	/* Wait क्रम 5ms */
	usleep_range(5000, 5500);

	/* regulator output should be stable within 5 ms */
	status = ctrl & SDHCI_CTRL_VDD_180;
	ctrl = sdhci_पढ़ोw(host, SDHCI_HOST_CONTROL2);
	अगर ((ctrl & SDHCI_CTRL_VDD_180) == status)
		वापस 0;

	dev_warn(mmc_dev(mmc), "%s: Regulator output did not became stable\n",
		mmc_hostname(mmc));

	वापस -EAGAIN;
पूर्ण

#घोषणा DRIVER_NAME "sdhci_msm"
#घोषणा SDHCI_MSM_DUMP(f, x...) \
	pr_err("%s: " DRIVER_NAME ": " f, mmc_hostname(host->mmc), ## x)

अटल व्योम sdhci_msm_dump_venकरोr_regs(काष्ठा sdhci_host *host)
अणु
	काष्ठा sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	काष्ठा sdhci_msm_host *msm_host = sdhci_pltfm_priv(pltfm_host);
	स्थिर काष्ठा sdhci_msm_offset *msm_offset = msm_host->offset;

	SDHCI_MSM_DUMP("----------- VENDOR REGISTER DUMP -----------\n");

	SDHCI_MSM_DUMP(
			"DLL sts: 0x%08x | DLL cfg:  0x%08x | DLL cfg2: 0x%08x\n",
		पढ़ोl_relaxed(host->ioaddr + msm_offset->core_dll_status),
		पढ़ोl_relaxed(host->ioaddr + msm_offset->core_dll_config),
		पढ़ोl_relaxed(host->ioaddr + msm_offset->core_dll_config_2));
	SDHCI_MSM_DUMP(
			"DLL cfg3: 0x%08x | DLL usr ctl:  0x%08x | DDR cfg: 0x%08x\n",
		पढ़ोl_relaxed(host->ioaddr + msm_offset->core_dll_config_3),
		पढ़ोl_relaxed(host->ioaddr + msm_offset->core_dll_usr_ctl),
		पढ़ोl_relaxed(host->ioaddr + msm_offset->core_ddr_config));
	SDHCI_MSM_DUMP(
			"Vndr func: 0x%08x | Vndr func2 : 0x%08x Vndr func3: 0x%08x\n",
		पढ़ोl_relaxed(host->ioaddr + msm_offset->core_venकरोr_spec),
		पढ़ोl_relaxed(host->ioaddr +
			msm_offset->core_venकरोr_spec_func2),
		पढ़ोl_relaxed(host->ioaddr + msm_offset->core_venकरोr_spec3));
पूर्ण

अटल स्थिर काष्ठा sdhci_msm_variant_ops mci_var_ops = अणु
	.msm_पढ़ोl_relaxed = sdhci_msm_mci_variant_पढ़ोl_relaxed,
	.msm_ग_लिखोl_relaxed = sdhci_msm_mci_variant_ग_लिखोl_relaxed,
पूर्ण;

अटल स्थिर काष्ठा sdhci_msm_variant_ops v5_var_ops = अणु
	.msm_पढ़ोl_relaxed = sdhci_msm_v5_variant_पढ़ोl_relaxed,
	.msm_ग_लिखोl_relaxed = sdhci_msm_v5_variant_ग_लिखोl_relaxed,
पूर्ण;

अटल स्थिर काष्ठा sdhci_msm_variant_info sdhci_msm_mci_var = अणु
	.var_ops = &mci_var_ops,
	.offset = &sdhci_msm_mci_offset,
पूर्ण;

अटल स्थिर काष्ठा sdhci_msm_variant_info sdhci_msm_v5_var = अणु
	.mci_हटाओd = true,
	.var_ops = &v5_var_ops,
	.offset = &sdhci_msm_v5_offset,
पूर्ण;

अटल स्थिर काष्ठा sdhci_msm_variant_info sdm845_sdhci_var = अणु
	.mci_हटाओd = true,
	.restore_dll_config = true,
	.var_ops = &v5_var_ops,
	.offset = &sdhci_msm_v5_offset,
पूर्ण;

अटल स्थिर काष्ठा of_device_id sdhci_msm_dt_match[] = अणु
	अणु.compatible = "qcom,sdhci-msm-v4", .data = &sdhci_msm_mci_varपूर्ण,
	अणु.compatible = "qcom,sdhci-msm-v5", .data = &sdhci_msm_v5_varपूर्ण,
	अणु.compatible = "qcom,sdm845-sdhci", .data = &sdm845_sdhci_varपूर्ण,
	अणु.compatible = "qcom,sc7180-sdhci", .data = &sdm845_sdhci_varपूर्ण,
	अणुपूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(of, sdhci_msm_dt_match);

अटल स्थिर काष्ठा sdhci_ops sdhci_msm_ops = अणु
	.reset = sdhci_msm_reset,
	.set_घड़ी = sdhci_msm_set_घड़ी,
	.get_min_घड़ी = sdhci_msm_get_min_घड़ी,
	.get_max_घड़ी = sdhci_msm_get_max_घड़ी,
	.set_bus_width = sdhci_set_bus_width,
	.set_uhs_संकेतing = sdhci_msm_set_uhs_संकेतing,
	.ग_लिखो_w = sdhci_msm_ग_लिखोw,
	.ग_लिखो_b = sdhci_msm_ग_लिखोb,
	.irq	= sdhci_msm_cqe_irq,
	.dump_venकरोr_regs = sdhci_msm_dump_venकरोr_regs,
	.set_घातer = sdhci_set_घातer_noreg,
पूर्ण;

अटल स्थिर काष्ठा sdhci_pltfm_data sdhci_msm_pdata = अणु
	.quirks = SDHCI_QUIRK_BROKEN_CARD_DETECTION |
		  SDHCI_QUIRK_SINGLE_POWER_WRITE |
		  SDHCI_QUIRK_CAP_CLOCK_BASE_BROKEN |
		  SDHCI_QUIRK_MULTIBLOCK_READ_ACMD12,

	.quirks2 = SDHCI_QUIRK2_PRESET_VALUE_BROKEN,
	.ops = &sdhci_msm_ops,
पूर्ण;

अटल अंतरभूत व्योम sdhci_msm_get_of_property(काष्ठा platक्रमm_device *pdev,
		काष्ठा sdhci_host *host)
अणु
	काष्ठा device_node *node = pdev->dev.of_node;
	काष्ठा sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	काष्ठा sdhci_msm_host *msm_host = sdhci_pltfm_priv(pltfm_host);

	अगर (of_property_पढ़ो_u32(node, "qcom,ddr-config",
				&msm_host->ddr_config))
		msm_host->ddr_config = DDR_CONFIG_POR_VAL;

	of_property_पढ़ो_u32(node, "qcom,dll-config", &msm_host->dll_config);
पूर्ण


अटल पूर्णांक sdhci_msm_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sdhci_host *host;
	काष्ठा sdhci_pltfm_host *pltfm_host;
	काष्ठा sdhci_msm_host *msm_host;
	काष्ठा clk *clk;
	पूर्णांक ret;
	u16 host_version, core_minor;
	u32 core_version, config;
	u8 core_major;
	स्थिर काष्ठा sdhci_msm_offset *msm_offset;
	स्थिर काष्ठा sdhci_msm_variant_info *var_info;
	काष्ठा device_node *node = pdev->dev.of_node;

	host = sdhci_pltfm_init(pdev, &sdhci_msm_pdata, माप(*msm_host));
	अगर (IS_ERR(host))
		वापस PTR_ERR(host);

	host->sdma_boundary = 0;
	pltfm_host = sdhci_priv(host);
	msm_host = sdhci_pltfm_priv(pltfm_host);
	msm_host->mmc = host->mmc;
	msm_host->pdev = pdev;

	ret = mmc_of_parse(host->mmc);
	अगर (ret)
		जाओ pltfm_मुक्त;

	/*
	 * Based on the compatible string, load the required msm host info from
	 * the data associated with the version info.
	 */
	var_info = of_device_get_match_data(&pdev->dev);

	msm_host->mci_हटाओd = var_info->mci_हटाओd;
	msm_host->restore_dll_config = var_info->restore_dll_config;
	msm_host->var_ops = var_info->var_ops;
	msm_host->offset = var_info->offset;

	msm_offset = msm_host->offset;

	sdhci_get_of_property(pdev);
	sdhci_msm_get_of_property(pdev, host);

	msm_host->saved_tuning_phase = INVALID_TUNING_PHASE;

	/* Setup SDCC bus voter घड़ी. */
	msm_host->bus_clk = devm_clk_get(&pdev->dev, "bus");
	अगर (!IS_ERR(msm_host->bus_clk)) अणु
		/* Vote क्रम max. clk rate क्रम max. perक्रमmance */
		ret = clk_set_rate(msm_host->bus_clk, पूर्णांक_उच्च);
		अगर (ret)
			जाओ pltfm_मुक्त;
		ret = clk_prepare_enable(msm_host->bus_clk);
		अगर (ret)
			जाओ pltfm_मुक्त;
	पूर्ण

	/* Setup मुख्य peripheral bus घड़ी */
	clk = devm_clk_get(&pdev->dev, "iface");
	अगर (IS_ERR(clk)) अणु
		ret = PTR_ERR(clk);
		dev_err(&pdev->dev, "Peripheral clk setup failed (%d)\n", ret);
		जाओ bus_clk_disable;
	पूर्ण
	msm_host->bulk_clks[1].clk = clk;

	/* Setup SDC MMC घड़ी */
	clk = devm_clk_get(&pdev->dev, "core");
	अगर (IS_ERR(clk)) अणु
		ret = PTR_ERR(clk);
		dev_err(&pdev->dev, "SDC MMC clk setup failed (%d)\n", ret);
		जाओ bus_clk_disable;
	पूर्ण
	msm_host->bulk_clks[0].clk = clk;

	 /* Check क्रम optional पूर्णांकerconnect paths */
	ret = dev_pm_opp_of_find_icc_paths(&pdev->dev, शून्य);
	अगर (ret)
		जाओ bus_clk_disable;

	ret = devm_pm_opp_set_clkname(&pdev->dev, "core");
	अगर (ret)
		जाओ bus_clk_disable;

	/* OPP table is optional */
	ret = devm_pm_opp_of_add_table(&pdev->dev);
	अगर (ret && ret != -ENODEV) अणु
		dev_err(&pdev->dev, "Invalid OPP table in Device tree\n");
		जाओ bus_clk_disable;
	पूर्ण

	/* Vote क्रम maximum घड़ी rate क्रम maximum perक्रमmance */
	ret = dev_pm_opp_set_rate(&pdev->dev, पूर्णांक_उच्च);
	अगर (ret)
		dev_warn(&pdev->dev, "core clock boost failed\n");

	clk = devm_clk_get(&pdev->dev, "cal");
	अगर (IS_ERR(clk))
		clk = शून्य;
	msm_host->bulk_clks[2].clk = clk;

	clk = devm_clk_get(&pdev->dev, "sleep");
	अगर (IS_ERR(clk))
		clk = शून्य;
	msm_host->bulk_clks[3].clk = clk;

	clk = sdhci_msm_ice_get_clk(&pdev->dev);
	अगर (IS_ERR(clk))
		clk = शून्य;
	msm_host->bulk_clks[4].clk = clk;

	ret = clk_bulk_prepare_enable(ARRAY_SIZE(msm_host->bulk_clks),
				      msm_host->bulk_clks);
	अगर (ret)
		जाओ bus_clk_disable;

	/*
	 * xo घड़ी is needed क्रम FLL feature of cm_dll.
	 * In हाल अगर xo घड़ी is not mentioned in DT, warn and proceed.
	 */
	msm_host->xo_clk = devm_clk_get(&pdev->dev, "xo");
	अगर (IS_ERR(msm_host->xo_clk)) अणु
		ret = PTR_ERR(msm_host->xo_clk);
		dev_warn(&pdev->dev, "TCXO clk not present (%d)\n", ret);
	पूर्ण

	अगर (!msm_host->mci_हटाओd) अणु
		msm_host->core_mem = devm_platक्रमm_ioremap_resource(pdev, 1);
		अगर (IS_ERR(msm_host->core_mem)) अणु
			ret = PTR_ERR(msm_host->core_mem);
			जाओ clk_disable;
		पूर्ण
	पूर्ण

	/* Reset the venकरोr spec रेजिस्टर to घातer on reset state */
	ग_लिखोl_relaxed(CORE_VENDOR_SPEC_POR_VAL,
			host->ioaddr + msm_offset->core_venकरोr_spec);

	अगर (!msm_host->mci_हटाओd) अणु
		/* Set HC_MODE_EN bit in HC_MODE रेजिस्टर */
		msm_host_ग_लिखोl(msm_host, HC_MODE_EN, host,
				msm_offset->core_hc_mode);
		config = msm_host_पढ़ोl(msm_host, host,
				msm_offset->core_hc_mode);
		config |= FF_CLK_SW_RST_DIS;
		msm_host_ग_लिखोl(msm_host, config, host,
				msm_offset->core_hc_mode);
	पूर्ण

	host_version = पढ़ोw_relaxed((host->ioaddr + SDHCI_HOST_VERSION));
	dev_dbg(&pdev->dev, "Host Version: 0x%x Vendor Version 0x%x\n",
		host_version, ((host_version & SDHCI_VENDOR_VER_MASK) >>
			       SDHCI_VENDOR_VER_SHIFT));

	core_version = msm_host_पढ़ोl(msm_host, host,
			msm_offset->core_mci_version);
	core_major = (core_version & CORE_VERSION_MAJOR_MASK) >>
		      CORE_VERSION_MAJOR_SHIFT;
	core_minor = core_version & CORE_VERSION_MINOR_MASK;
	dev_dbg(&pdev->dev, "MCI Version: 0x%08x, major: 0x%04x, minor: 0x%02x\n",
		core_version, core_major, core_minor);

	अगर (core_major == 1 && core_minor >= 0x42)
		msm_host->use_14lpp_dll_reset = true;

	/*
	 * SDCC 5 controller with major version 1, minor version 0x34 and later
	 * with HS 400 mode support will use CM DLL instead of CDC LP 533 DLL.
	 */
	अगर (core_major == 1 && core_minor < 0x34)
		msm_host->use_cdclp533 = true;

	/*
	 * Support क्रम some capabilities is not advertised by newer
	 * controller versions and must be explicitly enabled.
	 */
	अगर (core_major >= 1 && core_minor != 0x11 && core_minor != 0x12) अणु
		config = पढ़ोl_relaxed(host->ioaddr + SDHCI_CAPABILITIES);
		config |= SDHCI_CAN_VDD_300 | SDHCI_CAN_DO_8BIT;
		ग_लिखोl_relaxed(config, host->ioaddr +
				msm_offset->core_venकरोr_spec_capabilities0);
	पूर्ण

	अगर (core_major == 1 && core_minor >= 0x49)
		msm_host->updated_ddr_cfg = true;

	अगर (core_major == 1 && core_minor >= 0x71)
		msm_host->uses_tassadar_dll = true;

	ret = sdhci_msm_रेजिस्टर_vreg(msm_host);
	अगर (ret)
		जाओ clk_disable;

	/*
	 * Power on reset state may trigger घातer irq अगर previous status of
	 * PWRCTL was either BUS_ON or IO_HIGH_V. So beक्रमe enabling pwr irq
	 * पूर्णांकerrupt in GIC, any pending घातer irq पूर्णांकerrupt should be
	 * acknowledged. Otherwise घातer irq पूर्णांकerrupt handler would be
	 * fired prematurely.
	 */
	sdhci_msm_handle_pwr_irq(host, 0);

	/*
	 * Ensure that above ग_लिखोs are propogated beक्रमe पूर्णांकerrupt enablement
	 * in GIC.
	 */
	mb();

	/* Setup IRQ क्रम handling घातer/voltage tasks with PMIC */
	msm_host->pwr_irq = platक्रमm_get_irq_byname(pdev, "pwr_irq");
	अगर (msm_host->pwr_irq < 0) अणु
		ret = msm_host->pwr_irq;
		जाओ clk_disable;
	पूर्ण

	sdhci_msm_init_pwr_irq_रुको(msm_host);
	/* Enable pwr irq पूर्णांकerrupts */
	msm_host_ग_लिखोl(msm_host, INT_MASK, host,
		msm_offset->core_pwrctl_mask);

	ret = devm_request_thपढ़ोed_irq(&pdev->dev, msm_host->pwr_irq, शून्य,
					sdhci_msm_pwr_irq, IRQF_ONESHOT,
					dev_name(&pdev->dev), host);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Request IRQ failed (%d)\n", ret);
		जाओ clk_disable;
	पूर्ण

	msm_host->mmc->caps |= MMC_CAP_WAIT_WHILE_BUSY | MMC_CAP_NEED_RSP_BUSY;

	pm_runसमय_get_noresume(&pdev->dev);
	pm_runसमय_set_active(&pdev->dev);
	pm_runसमय_enable(&pdev->dev);
	pm_runसमय_set_स्वतःsuspend_delay(&pdev->dev,
					 MSM_MMC_AUTOSUSPEND_DELAY_MS);
	pm_runसमय_use_स्वतःsuspend(&pdev->dev);

	host->mmc_host_ops.start_संकेत_voltage_चयन =
		sdhci_msm_start_संकेत_voltage_चयन;
	host->mmc_host_ops.execute_tuning = sdhci_msm_execute_tuning;
	अगर (of_property_पढ़ो_bool(node, "supports-cqe"))
		ret = sdhci_msm_cqe_add_host(host, pdev);
	अन्यथा
		ret = sdhci_add_host(host);
	अगर (ret)
		जाओ pm_runसमय_disable;

	pm_runसमय_mark_last_busy(&pdev->dev);
	pm_runसमय_put_स्वतःsuspend(&pdev->dev);

	वापस 0;

pm_runसमय_disable:
	pm_runसमय_disable(&pdev->dev);
	pm_runसमय_set_suspended(&pdev->dev);
	pm_runसमय_put_noidle(&pdev->dev);
clk_disable:
	clk_bulk_disable_unprepare(ARRAY_SIZE(msm_host->bulk_clks),
				   msm_host->bulk_clks);
bus_clk_disable:
	अगर (!IS_ERR(msm_host->bus_clk))
		clk_disable_unprepare(msm_host->bus_clk);
pltfm_मुक्त:
	sdhci_pltfm_मुक्त(pdev);
	वापस ret;
पूर्ण

अटल पूर्णांक sdhci_msm_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sdhci_host *host = platक्रमm_get_drvdata(pdev);
	काष्ठा sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	काष्ठा sdhci_msm_host *msm_host = sdhci_pltfm_priv(pltfm_host);
	पूर्णांक dead = (पढ़ोl_relaxed(host->ioaddr + SDHCI_INT_STATUS) ==
		    0xffffffff);

	sdhci_हटाओ_host(host, dead);

	pm_runसमय_get_sync(&pdev->dev);
	pm_runसमय_disable(&pdev->dev);
	pm_runसमय_put_noidle(&pdev->dev);

	clk_bulk_disable_unprepare(ARRAY_SIZE(msm_host->bulk_clks),
				   msm_host->bulk_clks);
	अगर (!IS_ERR(msm_host->bus_clk))
		clk_disable_unprepare(msm_host->bus_clk);
	sdhci_pltfm_मुक्त(pdev);
	वापस 0;
पूर्ण

अटल __maybe_unused पूर्णांक sdhci_msm_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा sdhci_host *host = dev_get_drvdata(dev);
	काष्ठा sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	काष्ठा sdhci_msm_host *msm_host = sdhci_pltfm_priv(pltfm_host);

	/* Drop the perक्रमmance vote */
	dev_pm_opp_set_rate(dev, 0);
	clk_bulk_disable_unprepare(ARRAY_SIZE(msm_host->bulk_clks),
				   msm_host->bulk_clks);

	वापस 0;
पूर्ण

अटल __maybe_unused पूर्णांक sdhci_msm_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा sdhci_host *host = dev_get_drvdata(dev);
	काष्ठा sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	काष्ठा sdhci_msm_host *msm_host = sdhci_pltfm_priv(pltfm_host);
	पूर्णांक ret;

	ret = clk_bulk_prepare_enable(ARRAY_SIZE(msm_host->bulk_clks),
				       msm_host->bulk_clks);
	अगर (ret)
		वापस ret;
	/*
	 * Whenever core-घड़ी is gated dynamically, it's needed to
	 * restore the SDR DLL settings when the घड़ी is ungated.
	 */
	अगर (msm_host->restore_dll_config && msm_host->clk_rate) अणु
		ret = sdhci_msm_restore_sdr_dll_config(host);
		अगर (ret)
			वापस ret;
	पूर्ण

	dev_pm_opp_set_rate(dev, msm_host->clk_rate);

	वापस sdhci_msm_ice_resume(msm_host);
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops sdhci_msm_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(pm_runसमय_क्रमce_suspend,
				pm_runसमय_क्रमce_resume)
	SET_RUNTIME_PM_OPS(sdhci_msm_runसमय_suspend,
			   sdhci_msm_runसमय_resume,
			   शून्य)
पूर्ण;

अटल काष्ठा platक्रमm_driver sdhci_msm_driver = अणु
	.probe = sdhci_msm_probe,
	.हटाओ = sdhci_msm_हटाओ,
	.driver = अणु
		   .name = "sdhci_msm",
		   .of_match_table = sdhci_msm_dt_match,
		   .pm = &sdhci_msm_pm_ops,
		   .probe_type = PROBE_PREFER_ASYNCHRONOUS,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(sdhci_msm_driver);

MODULE_DESCRIPTION("Qualcomm Secure Digital Host Controller Interface driver");
MODULE_LICENSE("GPL v2");
