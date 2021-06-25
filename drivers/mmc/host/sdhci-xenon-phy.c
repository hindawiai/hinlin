<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * PHY support क्रम Xenon SDHC
 *
 * Copyright (C) 2016 Marvell, All Rights Reserved.
 *
 * Author:	Hu Ziji <huziji@marvell.com>
 * Date:	2016-8-24
 */

#समावेश <linux/slab.h>
#समावेश <linux/delay.h>
#समावेश <linux/kसमय.स>
#समावेश <linux/of_address.h>

#समावेश "sdhci-pltfm.h"
#समावेश "sdhci-xenon.h"

/* Register base क्रम eMMC PHY 5.0 Version */
#घोषणा XENON_EMMC_5_0_PHY_REG_BASE		0x0160
/* Register base क्रम eMMC PHY 5.1 Version */
#घोषणा XENON_EMMC_PHY_REG_BASE			0x0170

#घोषणा XENON_EMMC_PHY_TIMING_ADJUST		XENON_EMMC_PHY_REG_BASE
#घोषणा XENON_EMMC_5_0_PHY_TIMING_ADJUST	XENON_EMMC_5_0_PHY_REG_BASE
#घोषणा XENON_TIMING_ADJUST_SLOW_MODE		BIT(29)
#घोषणा XENON_TIMING_ADJUST_SDIO_MODE		BIT(28)
#घोषणा XENON_SAMPL_INV_QSP_PHASE_SELECT	BIT(18)
#घोषणा XENON_SAMPL_INV_QSP_PHASE_SELECT_SHIFT	18
#घोषणा XENON_PHY_INITIALIZAION			BIT(31)
#घोषणा XENON_WAIT_CYCLE_BEFORE_USING_MASK	0xF
#घोषणा XENON_WAIT_CYCLE_BEFORE_USING_SHIFT	12
#घोषणा XENON_FC_SYNC_EN_DURATION_MASK		0xF
#घोषणा XENON_FC_SYNC_EN_DURATION_SHIFT		8
#घोषणा XENON_FC_SYNC_RST_EN_DURATION_MASK	0xF
#घोषणा XENON_FC_SYNC_RST_EN_DURATION_SHIFT	4
#घोषणा XENON_FC_SYNC_RST_DURATION_MASK		0xF
#घोषणा XENON_FC_SYNC_RST_DURATION_SHIFT	0

#घोषणा XENON_EMMC_PHY_FUNC_CONTROL		(XENON_EMMC_PHY_REG_BASE + 0x4)
#घोषणा XENON_EMMC_5_0_PHY_FUNC_CONTROL		\
	(XENON_EMMC_5_0_PHY_REG_BASE + 0x4)
#घोषणा XENON_ASYNC_DDRMODE_MASK		BIT(23)
#घोषणा XENON_ASYNC_DDRMODE_SHIFT		23
#घोषणा XENON_CMD_DDR_MODE			BIT(16)
#घोषणा XENON_DQ_DDR_MODE_SHIFT			8
#घोषणा XENON_DQ_DDR_MODE_MASK			0xFF
#घोषणा XENON_DQ_ASYNC_MODE			BIT(4)

#घोषणा XENON_EMMC_PHY_PAD_CONTROL		(XENON_EMMC_PHY_REG_BASE + 0x8)
#घोषणा XENON_EMMC_5_0_PHY_PAD_CONTROL		\
	(XENON_EMMC_5_0_PHY_REG_BASE + 0x8)
#घोषणा XENON_REC_EN_SHIFT			24
#घोषणा XENON_REC_EN_MASK			0xF
#घोषणा XENON_FC_DQ_RECEN			BIT(24)
#घोषणा XENON_FC_CMD_RECEN			BIT(25)
#घोषणा XENON_FC_QSP_RECEN			BIT(26)
#घोषणा XENON_FC_QSN_RECEN			BIT(27)
#घोषणा XENON_OEN_QSN				BIT(28)
#घोषणा XENON_AUTO_RECEN_CTRL			BIT(30)
#घोषणा XENON_FC_ALL_CMOS_RECEIVER		0xF000

#घोषणा XENON_EMMC5_FC_QSP_PD			BIT(18)
#घोषणा XENON_EMMC5_FC_QSP_PU			BIT(22)
#घोषणा XENON_EMMC5_FC_CMD_PD			BIT(17)
#घोषणा XENON_EMMC5_FC_CMD_PU			BIT(21)
#घोषणा XENON_EMMC5_FC_DQ_PD			BIT(16)
#घोषणा XENON_EMMC5_FC_DQ_PU			BIT(20)

#घोषणा XENON_EMMC_PHY_PAD_CONTROL1		(XENON_EMMC_PHY_REG_BASE + 0xC)
#घोषणा XENON_EMMC5_1_FC_QSP_PD			BIT(9)
#घोषणा XENON_EMMC5_1_FC_QSP_PU			BIT(25)
#घोषणा XENON_EMMC5_1_FC_CMD_PD			BIT(8)
#घोषणा XENON_EMMC5_1_FC_CMD_PU			BIT(24)
#घोषणा XENON_EMMC5_1_FC_DQ_PD			0xFF
#घोषणा XENON_EMMC5_1_FC_DQ_PU			(0xFF << 16)

#घोषणा XENON_EMMC_PHY_PAD_CONTROL2		(XENON_EMMC_PHY_REG_BASE + 0x10)
#घोषणा XENON_EMMC_5_0_PHY_PAD_CONTROL2		\
	(XENON_EMMC_5_0_PHY_REG_BASE + 0xC)
#घोषणा XENON_ZNR_MASK				0x1F
#घोषणा XENON_ZNR_SHIFT				8
#घोषणा XENON_ZPR_MASK				0x1F
/* Preferred ZNR and ZPR value vary between dअगरferent boards.
 * The specअगरic ZNR and ZPR value should be defined here
 * according to board actual timing.
 */
#घोषणा XENON_ZNR_DEF_VALUE			0xF
#घोषणा XENON_ZPR_DEF_VALUE			0xF

#घोषणा XENON_EMMC_PHY_DLL_CONTROL		(XENON_EMMC_PHY_REG_BASE + 0x14)
#घोषणा XENON_EMMC_5_0_PHY_DLL_CONTROL		\
	(XENON_EMMC_5_0_PHY_REG_BASE + 0x10)
#घोषणा XENON_DLL_ENABLE			BIT(31)
#घोषणा XENON_DLL_UPDATE_STROBE_5_0		BIT(30)
#घोषणा XENON_DLL_REFCLK_SEL			BIT(30)
#घोषणा XENON_DLL_UPDATE			BIT(23)
#घोषणा XENON_DLL_PHSEL1_SHIFT			24
#घोषणा XENON_DLL_PHSEL0_SHIFT			16
#घोषणा XENON_DLL_PHASE_MASK			0x3F
#घोषणा XENON_DLL_PHASE_90_DEGREE		0x1F
#घोषणा XENON_DLL_FAST_LOCK			BIT(5)
#घोषणा XENON_DLL_GAIN2X			BIT(3)
#घोषणा XENON_DLL_BYPASS_EN			BIT(0)

#घोषणा XENON_EMMC_5_0_PHY_LOGIC_TIMING_ADJUST	\
	(XENON_EMMC_5_0_PHY_REG_BASE + 0x14)
#घोषणा XENON_EMMC_5_0_PHY_LOGIC_TIMING_VALUE	0x5A54
#घोषणा XENON_EMMC_PHY_LOGIC_TIMING_ADJUST	(XENON_EMMC_PHY_REG_BASE + 0x18)
#घोषणा XENON_LOGIC_TIMING_VALUE		0x00AA8977

/*
 * List offset of PHY रेजिस्टरs and some special रेजिस्टर values
 * in eMMC PHY 5.0 or eMMC PHY 5.1
 */
काष्ठा xenon_emmc_phy_regs अणु
	/* Offset of Timing Adjust रेजिस्टर */
	u16 timing_adj;
	/* Offset of Func Control रेजिस्टर */
	u16 func_ctrl;
	/* Offset of Pad Control रेजिस्टर */
	u16 pad_ctrl;
	/* Offset of Pad Control रेजिस्टर 2 */
	u16 pad_ctrl2;
	/* Offset of DLL Control रेजिस्टर */
	u16 dll_ctrl;
	/* Offset of Logic Timing Adjust रेजिस्टर */
	u16 logic_timing_adj;
	/* DLL Update Enable bit */
	u32 dll_update;
	/* value in Logic Timing Adjusपंचांगent रेजिस्टर */
	u32 logic_timing_val;
पूर्ण;

अटल स्थिर अक्षर * स्थिर phy_types[] = अणु
	"emmc 5.0 phy",
	"emmc 5.1 phy"
पूर्ण;

क्रमागत xenon_phy_type_क्रमागत अणु
	EMMC_5_0_PHY,
	EMMC_5_1_PHY,
	NR_PHY_TYPES
पूर्ण;

क्रमागत soc_pad_ctrl_type अणु
	SOC_PAD_SD,
	SOC_PAD_FIXED_1_8V,
पूर्ण;

काष्ठा soc_pad_ctrl अणु
	/* Register address of SoC PHY PAD ctrl */
	व्योम __iomem	*reg;
	/* SoC PHY PAD ctrl type */
	क्रमागत soc_pad_ctrl_type pad_type;
	/* SoC specअगरic operation to set SoC PHY PAD */
	व्योम (*set_soc_pad)(काष्ठा sdhci_host *host,
			    अचिन्हित अक्षर संकेत_voltage);
पूर्ण;

अटल काष्ठा xenon_emmc_phy_regs xenon_emmc_5_0_phy_regs = अणु
	.timing_adj	= XENON_EMMC_5_0_PHY_TIMING_ADJUST,
	.func_ctrl	= XENON_EMMC_5_0_PHY_FUNC_CONTROL,
	.pad_ctrl	= XENON_EMMC_5_0_PHY_PAD_CONTROL,
	.pad_ctrl2	= XENON_EMMC_5_0_PHY_PAD_CONTROL2,
	.dll_ctrl	= XENON_EMMC_5_0_PHY_DLL_CONTROL,
	.logic_timing_adj = XENON_EMMC_5_0_PHY_LOGIC_TIMING_ADJUST,
	.dll_update	= XENON_DLL_UPDATE_STROBE_5_0,
	.logic_timing_val = XENON_EMMC_5_0_PHY_LOGIC_TIMING_VALUE,
पूर्ण;

अटल काष्ठा xenon_emmc_phy_regs xenon_emmc_5_1_phy_regs = अणु
	.timing_adj	= XENON_EMMC_PHY_TIMING_ADJUST,
	.func_ctrl	= XENON_EMMC_PHY_FUNC_CONTROL,
	.pad_ctrl	= XENON_EMMC_PHY_PAD_CONTROL,
	.pad_ctrl2	= XENON_EMMC_PHY_PAD_CONTROL2,
	.dll_ctrl	= XENON_EMMC_PHY_DLL_CONTROL,
	.logic_timing_adj = XENON_EMMC_PHY_LOGIC_TIMING_ADJUST,
	.dll_update	= XENON_DLL_UPDATE,
	.logic_timing_val = XENON_LOGIC_TIMING_VALUE,
पूर्ण;

/*
 * eMMC PHY configuration and operations
 */
काष्ठा xenon_emmc_phy_params अणु
	bool	slow_mode;

	u8	znr;
	u8	zpr;

	/* Nr of consecutive Sampling Poपूर्णांकs of a Valid Sampling Winकरोw */
	u8	nr_tun_बार;
	/* Divider क्रम calculating Tuning Step */
	u8	tun_step_भागider;

	काष्ठा soc_pad_ctrl pad_ctrl;
पूर्ण;

अटल पूर्णांक xenon_alloc_emmc_phy(काष्ठा sdhci_host *host)
अणु
	काष्ठा sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	काष्ठा xenon_priv *priv = sdhci_pltfm_priv(pltfm_host);
	काष्ठा xenon_emmc_phy_params *params;

	params = devm_kzalloc(mmc_dev(host->mmc), माप(*params), GFP_KERNEL);
	अगर (!params)
		वापस -ENOMEM;

	priv->phy_params = params;
	अगर (priv->phy_type == EMMC_5_0_PHY)
		priv->emmc_phy_regs = &xenon_emmc_5_0_phy_regs;
	अन्यथा
		priv->emmc_phy_regs = &xenon_emmc_5_1_phy_regs;

	वापस 0;
पूर्ण

/*
 * eMMC 5.0/5.1 PHY init/re-init.
 * eMMC PHY init should be executed after:
 * 1. SDCLK frequency changes.
 * 2. SDCLK is stopped and re-enabled.
 * 3. config in emmc_phy_regs->timing_adj and emmc_phy_regs->func_ctrl
 * are changed
 */
अटल पूर्णांक xenon_emmc_phy_init(काष्ठा sdhci_host *host)
अणु
	u32 reg;
	u32 रुको, घड़ी;
	काष्ठा sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	काष्ठा xenon_priv *priv = sdhci_pltfm_priv(pltfm_host);
	काष्ठा xenon_emmc_phy_regs *phy_regs = priv->emmc_phy_regs;

	reg = sdhci_पढ़ोl(host, phy_regs->timing_adj);
	reg |= XENON_PHY_INITIALIZAION;
	sdhci_ग_लिखोl(host, reg, phy_regs->timing_adj);

	/* Add duration of FC_SYNC_RST */
	रुको = ((reg >> XENON_FC_SYNC_RST_DURATION_SHIFT) &
			XENON_FC_SYNC_RST_DURATION_MASK);
	/* Add पूर्णांकerval between FC_SYNC_EN and FC_SYNC_RST */
	रुको += ((reg >> XENON_FC_SYNC_RST_EN_DURATION_SHIFT) &
			XENON_FC_SYNC_RST_EN_DURATION_MASK);
	/* Add duration of निश्चितing FC_SYNC_EN */
	रुको += ((reg >> XENON_FC_SYNC_EN_DURATION_SHIFT) &
			XENON_FC_SYNC_EN_DURATION_MASK);
	/* Add duration of रुकोing क्रम PHY */
	रुको += ((reg >> XENON_WAIT_CYCLE_BEFORE_USING_SHIFT) &
			XENON_WAIT_CYCLE_BEFORE_USING_MASK);
	/* 4 additional bus घड़ी and 4 AXI bus घड़ी are required */
	रुको += 8;
	रुको <<= 20;

	घड़ी = host->घड़ी;
	अगर (!घड़ी)
		/* Use the possibly slowest bus frequency value */
		घड़ी = XENON_LOWEST_SDCLK_FREQ;
	/* get the रुको समय */
	रुको /= घड़ी;
	रुको++;
	/* रुको क्रम host eMMC PHY init completes */
	udelay(रुको);

	reg = sdhci_पढ़ोl(host, phy_regs->timing_adj);
	reg &= XENON_PHY_INITIALIZAION;
	अगर (reg) अणु
		dev_err(mmc_dev(host->mmc), "eMMC PHY init cannot complete after %d us\n",
			रुको);
		वापस -ETIMEDOUT;
	पूर्ण

	वापस 0;
पूर्ण

#घोषणा ARMADA_3700_SOC_PAD_1_8V	0x1
#घोषणा ARMADA_3700_SOC_PAD_3_3V	0x0

अटल व्योम armada_3700_soc_pad_voltage_set(काष्ठा sdhci_host *host,
					    अचिन्हित अक्षर संकेत_voltage)
अणु
	काष्ठा sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	काष्ठा xenon_priv *priv = sdhci_pltfm_priv(pltfm_host);
	काष्ठा xenon_emmc_phy_params *params = priv->phy_params;

	अगर (params->pad_ctrl.pad_type == SOC_PAD_FIXED_1_8V) अणु
		ग_लिखोl(ARMADA_3700_SOC_PAD_1_8V, params->pad_ctrl.reg);
	पूर्ण अन्यथा अगर (params->pad_ctrl.pad_type == SOC_PAD_SD) अणु
		अगर (संकेत_voltage == MMC_SIGNAL_VOLTAGE_180)
			ग_लिखोl(ARMADA_3700_SOC_PAD_1_8V, params->pad_ctrl.reg);
		अन्यथा अगर (संकेत_voltage == MMC_SIGNAL_VOLTAGE_330)
			ग_लिखोl(ARMADA_3700_SOC_PAD_3_3V, params->pad_ctrl.reg);
	पूर्ण
पूर्ण

/*
 * Set SoC PHY voltage PAD control रेजिस्टर,
 * according to the operation voltage on PAD.
 * The detailed operation depends on SoC implementation.
 */
अटल व्योम xenon_emmc_phy_set_soc_pad(काष्ठा sdhci_host *host,
				       अचिन्हित अक्षर संकेत_voltage)
अणु
	काष्ठा sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	काष्ठा xenon_priv *priv = sdhci_pltfm_priv(pltfm_host);
	काष्ठा xenon_emmc_phy_params *params = priv->phy_params;

	अगर (!params->pad_ctrl.reg)
		वापस;

	अगर (params->pad_ctrl.set_soc_pad)
		params->pad_ctrl.set_soc_pad(host, संकेत_voltage);
पूर्ण

/*
 * Enable eMMC PHY HW DLL
 * DLL should be enabled and stable beक्रमe HS200/SDR104 tuning,
 * and beक्रमe HS400 data strobe setting.
 */
अटल पूर्णांक xenon_emmc_phy_enable_dll(काष्ठा sdhci_host *host)
अणु
	u32 reg;
	काष्ठा sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	काष्ठा xenon_priv *priv = sdhci_pltfm_priv(pltfm_host);
	काष्ठा xenon_emmc_phy_regs *phy_regs = priv->emmc_phy_regs;
	kसमय_प्रकार समयout;

	अगर (WARN_ON(host->घड़ी <= MMC_HIGH_52_MAX_DTR))
		वापस -EINVAL;

	reg = sdhci_पढ़ोl(host, phy_regs->dll_ctrl);
	अगर (reg & XENON_DLL_ENABLE)
		वापस 0;

	/* Enable DLL */
	reg = sdhci_पढ़ोl(host, phy_regs->dll_ctrl);
	reg |= (XENON_DLL_ENABLE | XENON_DLL_FAST_LOCK);

	/*
	 * Set Phase as 90 degree, which is most common value.
	 * Might set another value अगर necessary.
	 * The granularity is 1 degree.
	 */
	reg &= ~((XENON_DLL_PHASE_MASK << XENON_DLL_PHSEL0_SHIFT) |
		 (XENON_DLL_PHASE_MASK << XENON_DLL_PHSEL1_SHIFT));
	reg |= ((XENON_DLL_PHASE_90_DEGREE << XENON_DLL_PHSEL0_SHIFT) |
		(XENON_DLL_PHASE_90_DEGREE << XENON_DLL_PHSEL1_SHIFT));

	reg &= ~XENON_DLL_BYPASS_EN;
	reg |= phy_regs->dll_update;
	अगर (priv->phy_type == EMMC_5_1_PHY)
		reg &= ~XENON_DLL_REFCLK_SEL;
	sdhci_ग_लिखोl(host, reg, phy_regs->dll_ctrl);

	/* Wait max 32 ms */
	समयout = kसमय_add_ms(kसमय_get(), 32);
	जबतक (1) अणु
		bool समयकरोut = kसमय_after(kसमय_get(), समयout);

		अगर (sdhci_पढ़ोw(host, XENON_SLOT_EXT_PRESENT_STATE) &
		    XENON_DLL_LOCK_STATE)
			अवरोध;
		अगर (समयकरोut) अणु
			dev_err(mmc_dev(host->mmc), "Wait for DLL Lock time-out\n");
			वापस -ETIMEDOUT;
		पूर्ण
		udelay(100);
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Config to eMMC PHY to prepare क्रम tuning.
 * Enable HW DLL and set the TUNING_STEP
 */
अटल पूर्णांक xenon_emmc_phy_config_tuning(काष्ठा sdhci_host *host)
अणु
	काष्ठा sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	काष्ठा xenon_priv *priv = sdhci_pltfm_priv(pltfm_host);
	काष्ठा xenon_emmc_phy_params *params = priv->phy_params;
	u32 reg, tuning_step;
	पूर्णांक ret;

	अगर (host->घड़ी <= MMC_HIGH_52_MAX_DTR)
		वापस -EINVAL;

	ret = xenon_emmc_phy_enable_dll(host);
	अगर (ret)
		वापस ret;

	/* Achieve TUNING_STEP with HW DLL help */
	reg = sdhci_पढ़ोl(host, XENON_SLOT_DLL_CUR_DLY_VAL);
	tuning_step = reg / params->tun_step_भागider;
	अगर (unlikely(tuning_step > XENON_TUNING_STEP_MASK)) अणु
		dev_warn(mmc_dev(host->mmc),
			 "HS200 TUNING_STEP %d is larger than MAX value\n",
			 tuning_step);
		tuning_step = XENON_TUNING_STEP_MASK;
	पूर्ण

	/* Set TUNING_STEP क्रम later tuning */
	reg = sdhci_पढ़ोl(host, XENON_SLOT_OP_STATUS_CTRL);
	reg &= ~(XENON_TUN_CONSECUTIVE_TIMES_MASK <<
		 XENON_TUN_CONSECUTIVE_TIMES_SHIFT);
	reg |= (params->nr_tun_बार << XENON_TUN_CONSECUTIVE_TIMES_SHIFT);
	reg &= ~(XENON_TUNING_STEP_MASK << XENON_TUNING_STEP_SHIFT);
	reg |= (tuning_step << XENON_TUNING_STEP_SHIFT);
	sdhci_ग_लिखोl(host, reg, XENON_SLOT_OP_STATUS_CTRL);

	वापस 0;
पूर्ण

अटल व्योम xenon_emmc_phy_disable_strobe(काष्ठा sdhci_host *host)
अणु
	काष्ठा sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	काष्ठा xenon_priv *priv = sdhci_pltfm_priv(pltfm_host);
	u32 reg;

	/* Disable both SDHC Data Strobe and Enhanced Strobe */
	reg = sdhci_पढ़ोl(host, XENON_SLOT_EMMC_CTRL);
	reg &= ~(XENON_ENABLE_DATA_STROBE | XENON_ENABLE_RESP_STROBE);
	sdhci_ग_लिखोl(host, reg, XENON_SLOT_EMMC_CTRL);

	/* Clear Strobe line Pull करोwn or Pull up */
	अगर (priv->phy_type == EMMC_5_0_PHY) अणु
		reg = sdhci_पढ़ोl(host, XENON_EMMC_5_0_PHY_PAD_CONTROL);
		reg &= ~(XENON_EMMC5_FC_QSP_PD | XENON_EMMC5_FC_QSP_PU);
		sdhci_ग_लिखोl(host, reg, XENON_EMMC_5_0_PHY_PAD_CONTROL);
	पूर्ण अन्यथा अणु
		reg = sdhci_पढ़ोl(host, XENON_EMMC_PHY_PAD_CONTROL1);
		reg &= ~(XENON_EMMC5_1_FC_QSP_PD | XENON_EMMC5_1_FC_QSP_PU);
		sdhci_ग_लिखोl(host, reg, XENON_EMMC_PHY_PAD_CONTROL1);
	पूर्ण
पूर्ण

/* Set HS400 Data Strobe and Enhanced Strobe */
अटल व्योम xenon_emmc_phy_strobe_delay_adj(काष्ठा sdhci_host *host)
अणु
	काष्ठा sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	काष्ठा xenon_priv *priv = sdhci_pltfm_priv(pltfm_host);
	u32 reg;

	अगर (WARN_ON(host->timing != MMC_TIMING_MMC_HS400))
		वापस;

	अगर (host->घड़ी <= MMC_HIGH_52_MAX_DTR)
		वापस;

	dev_dbg(mmc_dev(host->mmc), "starts HS400 strobe delay adjustment\n");

	xenon_emmc_phy_enable_dll(host);

	/* Enable SDHC Data Strobe */
	reg = sdhci_पढ़ोl(host, XENON_SLOT_EMMC_CTRL);
	reg |= XENON_ENABLE_DATA_STROBE;
	/*
	 * Enable SDHC Enhanced Strobe अगर supported
	 * Xenon Enhanced Strobe should be enabled only when
	 * 1. card is in HS400 mode and
	 * 2. SDCLK is higher than 52MHz
	 * 3. DLL is enabled
	 */
	अगर (host->mmc->ios.enhanced_strobe)
		reg |= XENON_ENABLE_RESP_STROBE;
	sdhci_ग_लिखोl(host, reg, XENON_SLOT_EMMC_CTRL);

	/* Set Data Strobe Pull करोwn */
	अगर (priv->phy_type == EMMC_5_0_PHY) अणु
		reg = sdhci_पढ़ोl(host, XENON_EMMC_5_0_PHY_PAD_CONTROL);
		reg |= XENON_EMMC5_FC_QSP_PD;
		reg &= ~XENON_EMMC5_FC_QSP_PU;
		sdhci_ग_लिखोl(host, reg, XENON_EMMC_5_0_PHY_PAD_CONTROL);
	पूर्ण अन्यथा अणु
		reg = sdhci_पढ़ोl(host, XENON_EMMC_PHY_PAD_CONTROL1);
		reg |= XENON_EMMC5_1_FC_QSP_PD;
		reg &= ~XENON_EMMC5_1_FC_QSP_PU;
		sdhci_ग_लिखोl(host, reg, XENON_EMMC_PHY_PAD_CONTROL1);
	पूर्ण
पूर्ण

/*
 * If eMMC PHY Slow Mode is required in lower speed mode (SDCLK < 55MHz)
 * in SDR mode, enable Slow Mode to bypass eMMC PHY.
 * SDIO slower SDR mode also requires Slow Mode.
 *
 * If Slow Mode is enabled, वापस true.
 * Otherwise, वापस false.
 */
अटल bool xenon_emmc_phy_slow_mode(काष्ठा sdhci_host *host,
				     अचिन्हित अक्षर timing)
अणु
	काष्ठा sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	काष्ठा xenon_priv *priv = sdhci_pltfm_priv(pltfm_host);
	काष्ठा xenon_emmc_phy_params *params = priv->phy_params;
	काष्ठा xenon_emmc_phy_regs *phy_regs = priv->emmc_phy_regs;
	u32 reg;
	पूर्णांक ret;

	अगर (host->घड़ी > MMC_HIGH_52_MAX_DTR)
		वापस false;

	reg = sdhci_पढ़ोl(host, phy_regs->timing_adj);
	/* When in slower SDR mode, enable Slow Mode क्रम SDIO
	 * or when Slow Mode flag is set
	 */
	चयन (timing) अणु
	हाल MMC_TIMING_LEGACY:
		/*
		 * If Slow Mode is required, enable Slow Mode by शेष
		 * in early init phase to aव्योम any potential issue.
		 */
		अगर (params->slow_mode) अणु
			reg |= XENON_TIMING_ADJUST_SLOW_MODE;
			ret = true;
		पूर्ण अन्यथा अणु
			reg &= ~XENON_TIMING_ADJUST_SLOW_MODE;
			ret = false;
		पूर्ण
		अवरोध;
	हाल MMC_TIMING_UHS_SDR25:
	हाल MMC_TIMING_UHS_SDR12:
	हाल MMC_TIMING_SD_HS:
	हाल MMC_TIMING_MMC_HS:
		अगर ((priv->init_card_type == MMC_TYPE_SDIO) ||
		    params->slow_mode) अणु
			reg |= XENON_TIMING_ADJUST_SLOW_MODE;
			ret = true;
			अवरोध;
		पूर्ण
		fallthrough;
	शेष:
		reg &= ~XENON_TIMING_ADJUST_SLOW_MODE;
		ret = false;
	पूर्ण

	sdhci_ग_लिखोl(host, reg, phy_regs->timing_adj);
	वापस ret;
पूर्ण

/*
 * Set-up eMMC 5.0/5.1 PHY.
 * Specअगरic configuration depends on the current speed mode in use.
 */
अटल व्योम xenon_emmc_phy_set(काष्ठा sdhci_host *host,
			       अचिन्हित अक्षर timing)
अणु
	u32 reg;
	काष्ठा sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	काष्ठा xenon_priv *priv = sdhci_pltfm_priv(pltfm_host);
	काष्ठा xenon_emmc_phy_params *params = priv->phy_params;
	काष्ठा xenon_emmc_phy_regs *phy_regs = priv->emmc_phy_regs;

	dev_dbg(mmc_dev(host->mmc), "eMMC PHY setting starts\n");

	/* Setup pad, set bit[28] and bits[26:24] */
	reg = sdhci_पढ़ोl(host, phy_regs->pad_ctrl);
	reg |= (XENON_FC_DQ_RECEN | XENON_FC_CMD_RECEN |
		XENON_FC_QSP_RECEN | XENON_OEN_QSN);
	/* All FC_XX_RECEIVCE should be set as CMOS Type */
	reg |= XENON_FC_ALL_CMOS_RECEIVER;
	sdhci_ग_लिखोl(host, reg, phy_regs->pad_ctrl);

	/* Set CMD and DQ Pull Up */
	अगर (priv->phy_type == EMMC_5_0_PHY) अणु
		reg = sdhci_पढ़ोl(host, XENON_EMMC_5_0_PHY_PAD_CONTROL);
		reg |= (XENON_EMMC5_FC_CMD_PU | XENON_EMMC5_FC_DQ_PU);
		reg &= ~(XENON_EMMC5_FC_CMD_PD | XENON_EMMC5_FC_DQ_PD);
		sdhci_ग_लिखोl(host, reg, XENON_EMMC_5_0_PHY_PAD_CONTROL);
	पूर्ण अन्यथा अणु
		reg = sdhci_पढ़ोl(host, XENON_EMMC_PHY_PAD_CONTROL1);
		reg |= (XENON_EMMC5_1_FC_CMD_PU | XENON_EMMC5_1_FC_DQ_PU);
		reg &= ~(XENON_EMMC5_1_FC_CMD_PD | XENON_EMMC5_1_FC_DQ_PD);
		sdhci_ग_लिखोl(host, reg, XENON_EMMC_PHY_PAD_CONTROL1);
	पूर्ण

	अगर (timing == MMC_TIMING_LEGACY) अणु
		xenon_emmc_phy_slow_mode(host, timing);
		जाओ phy_init;
	पूर्ण

	/*
	 * If SDIO card, set SDIO Mode
	 * Otherwise, clear SDIO Mode
	 */
	reg = sdhci_पढ़ोl(host, phy_regs->timing_adj);
	अगर (priv->init_card_type == MMC_TYPE_SDIO)
		reg |= XENON_TIMING_ADJUST_SDIO_MODE;
	अन्यथा
		reg &= ~XENON_TIMING_ADJUST_SDIO_MODE;
	sdhci_ग_लिखोl(host, reg, phy_regs->timing_adj);

	अगर (xenon_emmc_phy_slow_mode(host, timing))
		जाओ phy_init;

	/*
	 * Set preferred ZNR and ZPR value
	 * The ZNR and ZPR value vary between dअगरferent boards.
	 * Define them both in sdhci-xenon-emmc-phy.h.
	 */
	reg = sdhci_पढ़ोl(host, phy_regs->pad_ctrl2);
	reg &= ~((XENON_ZNR_MASK << XENON_ZNR_SHIFT) | XENON_ZPR_MASK);
	reg |= ((params->znr << XENON_ZNR_SHIFT) | params->zpr);
	sdhci_ग_लिखोl(host, reg, phy_regs->pad_ctrl2);

	/*
	 * When setting EMMC_PHY_FUNC_CONTROL रेजिस्टर,
	 * SD घड़ी should be disabled
	 */
	reg = sdhci_पढ़ोl(host, SDHCI_CLOCK_CONTROL);
	reg &= ~SDHCI_CLOCK_CARD_EN;
	sdhci_ग_लिखोw(host, reg, SDHCI_CLOCK_CONTROL);

	reg = sdhci_पढ़ोl(host, phy_regs->func_ctrl);
	चयन (timing) अणु
	हाल MMC_TIMING_MMC_HS400:
		reg |= (XENON_DQ_DDR_MODE_MASK << XENON_DQ_DDR_MODE_SHIFT) |
		       XENON_CMD_DDR_MODE;
		reg &= ~XENON_DQ_ASYNC_MODE;
		अवरोध;
	हाल MMC_TIMING_UHS_DDR50:
	हाल MMC_TIMING_MMC_DDR52:
		reg |= (XENON_DQ_DDR_MODE_MASK << XENON_DQ_DDR_MODE_SHIFT) |
		       XENON_CMD_DDR_MODE | XENON_DQ_ASYNC_MODE;
		अवरोध;
	शेष:
		reg &= ~((XENON_DQ_DDR_MODE_MASK << XENON_DQ_DDR_MODE_SHIFT) |
			 XENON_CMD_DDR_MODE);
		reg |= XENON_DQ_ASYNC_MODE;
	पूर्ण
	sdhci_ग_लिखोl(host, reg, phy_regs->func_ctrl);

	/* Enable bus घड़ी */
	reg = sdhci_पढ़ोl(host, SDHCI_CLOCK_CONTROL);
	reg |= SDHCI_CLOCK_CARD_EN;
	sdhci_ग_लिखोw(host, reg, SDHCI_CLOCK_CONTROL);

	अगर (timing == MMC_TIMING_MMC_HS400)
		/* Hardware team recommend a value क्रम HS400 */
		sdhci_ग_लिखोl(host, phy_regs->logic_timing_val,
			     phy_regs->logic_timing_adj);
	अन्यथा
		xenon_emmc_phy_disable_strobe(host);

phy_init:
	xenon_emmc_phy_init(host);

	dev_dbg(mmc_dev(host->mmc), "eMMC PHY setting completes\n");
पूर्ण

अटल पूर्णांक get_dt_pad_ctrl_data(काष्ठा sdhci_host *host,
				काष्ठा device_node *np,
				काष्ठा xenon_emmc_phy_params *params)
अणु
	काष्ठा sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	काष्ठा xenon_priv *priv = sdhci_pltfm_priv(pltfm_host);
	पूर्णांक ret = 0;
	स्थिर अक्षर *name;
	काष्ठा resource iomem;

	अगर (priv->hw_version == XENON_A3700)
		params->pad_ctrl.set_soc_pad = armada_3700_soc_pad_voltage_set;
	अन्यथा
		वापस 0;

	अगर (of_address_to_resource(np, 1, &iomem)) अणु
		dev_err(mmc_dev(host->mmc), "Unable to find SoC PAD ctrl register address for %pOFn\n",
			np);
		वापस -EINVAL;
	पूर्ण

	params->pad_ctrl.reg = devm_ioremap_resource(mmc_dev(host->mmc),
						     &iomem);
	अगर (IS_ERR(params->pad_ctrl.reg))
		वापस PTR_ERR(params->pad_ctrl.reg);

	ret = of_property_पढ़ो_string(np, "marvell,pad-type", &name);
	अगर (ret) अणु
		dev_err(mmc_dev(host->mmc), "Unable to determine SoC PHY PAD ctrl type\n");
		वापस ret;
	पूर्ण
	अगर (!म_भेद(name, "sd")) अणु
		params->pad_ctrl.pad_type = SOC_PAD_SD;
	पूर्ण अन्यथा अगर (!म_भेद(name, "fixed-1-8v")) अणु
		params->pad_ctrl.pad_type = SOC_PAD_FIXED_1_8V;
	पूर्ण अन्यथा अणु
		dev_err(mmc_dev(host->mmc), "Unsupported SoC PHY PAD ctrl type %s\n",
			name);
		वापस -EINVAL;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक xenon_emmc_phy_parse_params(काष्ठा sdhci_host *host,
				       काष्ठा device *dev,
				       काष्ठा xenon_emmc_phy_params *params)
अणु
	u32 value;

	params->slow_mode = false;
	अगर (device_property_पढ़ो_bool(dev, "marvell,xenon-phy-slow-mode"))
		params->slow_mode = true;

	params->znr = XENON_ZNR_DEF_VALUE;
	अगर (!device_property_पढ़ो_u32(dev, "marvell,xenon-phy-znr", &value))
		params->znr = value & XENON_ZNR_MASK;

	params->zpr = XENON_ZPR_DEF_VALUE;
	अगर (!device_property_पढ़ो_u32(dev, "marvell,xenon-phy-zpr", &value))
		params->zpr = value & XENON_ZPR_MASK;

	params->nr_tun_बार = XENON_TUN_CONSECUTIVE_TIMES;
	अगर (!device_property_पढ़ो_u32(dev, "marvell,xenon-phy-nr-success-tun",
				      &value))
		params->nr_tun_बार = value & XENON_TUN_CONSECUTIVE_TIMES_MASK;

	params->tun_step_भागider = XENON_TUNING_STEP_DIVIDER;
	अगर (!device_property_पढ़ो_u32(dev, "marvell,xenon-phy-tun-step-divider",
				      &value))
		params->tun_step_भागider = value & 0xFF;

	अगर (dev->of_node)
		वापस get_dt_pad_ctrl_data(host, dev->of_node, params);
	वापस 0;
पूर्ण

/* Set SoC PHY Voltage PAD */
व्योम xenon_soc_pad_ctrl(काष्ठा sdhci_host *host,
			अचिन्हित अक्षर संकेत_voltage)
अणु
	xenon_emmc_phy_set_soc_pad(host, संकेत_voltage);
पूर्ण

/*
 * Setting PHY when card is working in High Speed Mode.
 * HS400 set Data Strobe and Enhanced Strobe अगर it is supported.
 * HS200/SDR104 set tuning config to prepare क्रम tuning.
 */
अटल पूर्णांक xenon_hs_delay_adj(काष्ठा sdhci_host *host)
अणु
	पूर्णांक ret = 0;

	अगर (WARN_ON(host->घड़ी <= XENON_DEFAULT_SDCLK_FREQ))
		वापस -EINVAL;

	चयन (host->timing) अणु
	हाल MMC_TIMING_MMC_HS400:
		xenon_emmc_phy_strobe_delay_adj(host);
		वापस 0;
	हाल MMC_TIMING_MMC_HS200:
	हाल MMC_TIMING_UHS_SDR104:
		वापस xenon_emmc_phy_config_tuning(host);
	हाल MMC_TIMING_MMC_DDR52:
	हाल MMC_TIMING_UHS_DDR50:
		/*
		 * DDR Mode requires driver to scan Sampling Fixed Delay Line,
		 * to find out a perfect operation sampling poपूर्णांक.
		 * It is hard to implement such a scan in host driver
		 * since initiating commands by host driver is not safe.
		 * Thus so far just keep PHY Sampling Fixed Delay in
		 * शेष value of DDR mode.
		 *
		 * If any timing issue occurs in DDR mode on Marvell products,
		 * please contact मुख्यtainer क्रम पूर्णांकernal support in Marvell.
		 */
		dev_warn_once(mmc_dev(host->mmc), "Timing issue might occur in DDR mode\n");
		वापस 0;
	पूर्ण

	वापस ret;
पूर्ण

/*
 * Adjust PHY setting.
 * PHY setting should be adjusted when SDCLK frequency, Bus Width
 * or Speed Mode is changed.
 * Additional config are required when card is working in High Speed mode,
 * after leaving Legacy Mode.
 */
पूर्णांक xenon_phy_adj(काष्ठा sdhci_host *host, काष्ठा mmc_ios *ios)
अणु
	काष्ठा sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	काष्ठा xenon_priv *priv = sdhci_pltfm_priv(pltfm_host);
	पूर्णांक ret = 0;

	अगर (!host->घड़ी) अणु
		priv->घड़ी = 0;
		वापस 0;
	पूर्ण

	/*
	 * The timing, frequency or bus width is changed,
	 * better to set eMMC PHY based on current setting
	 * and adjust Xenon SDHC delay.
	 */
	अगर ((host->घड़ी == priv->घड़ी) &&
	    (ios->bus_width == priv->bus_width) &&
	    (ios->timing == priv->timing))
		वापस 0;

	xenon_emmc_phy_set(host, ios->timing);

	/* Update the record */
	priv->bus_width = ios->bus_width;

	priv->timing = ios->timing;
	priv->घड़ी = host->घड़ी;

	/* Legacy mode is a special हाल */
	अगर (ios->timing == MMC_TIMING_LEGACY)
		वापस 0;

	अगर (host->घड़ी > XENON_DEFAULT_SDCLK_FREQ)
		ret = xenon_hs_delay_adj(host);
	वापस ret;
पूर्ण

अटल पूर्णांक xenon_add_phy(काष्ठा device *dev, काष्ठा sdhci_host *host,
			 स्थिर अक्षर *phy_name)
अणु
	काष्ठा sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	काष्ठा xenon_priv *priv = sdhci_pltfm_priv(pltfm_host);
	पूर्णांक ret;

	priv->phy_type = match_string(phy_types, NR_PHY_TYPES, phy_name);
	अगर (priv->phy_type < 0) अणु
		dev_err(mmc_dev(host->mmc),
			"Unable to determine PHY name %s. Use default eMMC 5.1 PHY\n",
			phy_name);
		priv->phy_type = EMMC_5_1_PHY;
	पूर्ण

	ret = xenon_alloc_emmc_phy(host);
	अगर (ret)
		वापस ret;

	वापस xenon_emmc_phy_parse_params(host, dev, priv->phy_params);
पूर्ण

पूर्णांक xenon_phy_parse_params(काष्ठा device *dev, काष्ठा sdhci_host *host)
अणु
	स्थिर अक्षर *phy_type = शून्य;

	अगर (!device_property_पढ़ो_string(dev, "marvell,xenon-phy-type", &phy_type))
		वापस xenon_add_phy(dev, host, phy_type);

	वापस xenon_add_phy(dev, host, "emmc 5.1 phy");
पूर्ण
