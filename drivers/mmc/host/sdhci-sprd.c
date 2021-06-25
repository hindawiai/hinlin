<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Secure Digital Host Controller
//
// Copyright (C) 2018 Spपढ़ोtrum, Inc.
// Author: Chunyan Zhang <chunyan.zhang@unisoc.com>

#समावेश <linux/delay.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_gpपन.स>
#समावेश <linux/pinctrl/consumer.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/slab.h>

#समावेश "sdhci-pltfm.h"
#समावेश "mmc_hsq.h"

/* SDHCI_ARGUMENT2 रेजिस्टर high 16bit */
#घोषणा SDHCI_SPRD_ARG2_STUFF		GENMASK(31, 16)

#घोषणा SDHCI_SPRD_REG_32_DLL_CFG	0x200
#घोषणा  SDHCI_SPRD_DLL_ALL_CPST_EN	(BIT(18) | BIT(24) | BIT(25) | BIT(26) | BIT(27))
#घोषणा  SDHCI_SPRD_DLL_EN		BIT(21)
#घोषणा  SDHCI_SPRD_DLL_SEARCH_MODE	BIT(16)
#घोषणा  SDHCI_SPRD_DLL_INIT_COUNT	0xc00
#घोषणा  SDHCI_SPRD_DLL_PHASE_INTERNAL	0x3

#घोषणा SDHCI_SPRD_REG_32_DLL_DLY	0x204

#घोषणा SDHCI_SPRD_REG_32_DLL_DLY_OFFSET	0x208
#घोषणा  SDHCIBSPRD_IT_WR_DLY_INV		BIT(5)
#घोषणा  SDHCI_SPRD_BIT_CMD_DLY_INV		BIT(13)
#घोषणा  SDHCI_SPRD_BIT_POSRD_DLY_INV		BIT(21)
#घोषणा  SDHCI_SPRD_BIT_NEGRD_DLY_INV		BIT(29)

#घोषणा SDHCI_SPRD_REG_32_BUSY_POSI		0x250
#घोषणा  SDHCI_SPRD_BIT_OUTR_CLK_AUTO_EN	BIT(25)
#घोषणा  SDHCI_SPRD_BIT_INNR_CLK_AUTO_EN	BIT(24)

#घोषणा SDHCI_SPRD_REG_DEBOUNCE		0x28C
#घोषणा  SDHCI_SPRD_BIT_DLL_BAK		BIT(0)
#घोषणा  SDHCI_SPRD_BIT_DLL_VAL		BIT(1)

#घोषणा  SDHCI_SPRD_INT_SIGNAL_MASK	0x1B7F410B

/* SDHCI_HOST_CONTROL2 */
#घोषणा  SDHCI_SPRD_CTRL_HS200		0x0005
#घोषणा  SDHCI_SPRD_CTRL_HS400		0x0006
#घोषणा  SDHCI_SPRD_CTRL_HS400ES	0x0007

/*
 * According to the standard specअगरication, BIT(3) of SDHCI_SOFTWARE_RESET is
 * reserved, and only used on Spपढ़ोtrum's design, the hardware cannot work
 * अगर this bit is cleared.
 * 1 : normal work
 * 0 : hardware reset
 */
#घोषणा  SDHCI_HW_RESET_CARD		BIT(3)

#घोषणा SDHCI_SPRD_MAX_CUR		0xFFFFFF
#घोषणा SDHCI_SPRD_CLK_MAX_DIV		1023

#घोषणा SDHCI_SPRD_CLK_DEF_RATE		26000000
#घोषणा SDHCI_SPRD_PHY_DLL_CLK		52000000

काष्ठा sdhci_sprd_host अणु
	u32 version;
	काष्ठा clk *clk_sdio;
	काष्ठा clk *clk_enable;
	काष्ठा clk *clk_2x_enable;
	काष्ठा pinctrl *pinctrl;
	काष्ठा pinctrl_state *pins_uhs;
	काष्ठा pinctrl_state *pins_शेष;
	u32 base_rate;
	पूर्णांक flags; /* backup of host attribute */
	u32 phy_delay[MMC_TIMING_MMC_HS400 + 2];
पूर्ण;

काष्ठा sdhci_sprd_phy_cfg अणु
	स्थिर अक्षर *property;
	u8 timing;
पूर्ण;

अटल स्थिर काष्ठा sdhci_sprd_phy_cfg sdhci_sprd_phy_cfgs[] = अणु
	अणु "sprd,phy-delay-legacy", MMC_TIMING_LEGACY, पूर्ण,
	अणु "sprd,phy-delay-sd-highspeed", MMC_TIMING_SD_HS, पूर्ण,
	अणु "sprd,phy-delay-sd-uhs-sdr50", MMC_TIMING_UHS_SDR50, पूर्ण,
	अणु "sprd,phy-delay-sd-uhs-sdr104", MMC_TIMING_UHS_SDR104, पूर्ण,
	अणु "sprd,phy-delay-mmc-highspeed", MMC_TIMING_MMC_HS, पूर्ण,
	अणु "sprd,phy-delay-mmc-ddr52", MMC_TIMING_MMC_DDR52, पूर्ण,
	अणु "sprd,phy-delay-mmc-hs200", MMC_TIMING_MMC_HS200, पूर्ण,
	अणु "sprd,phy-delay-mmc-hs400", MMC_TIMING_MMC_HS400, पूर्ण,
	अणु "sprd,phy-delay-mmc-hs400es", MMC_TIMING_MMC_HS400 + 1, पूर्ण,
पूर्ण;

#घोषणा TO_SPRD_HOST(host) sdhci_pltfm_priv(sdhci_priv(host))

अटल व्योम sdhci_sprd_init_config(काष्ठा sdhci_host *host)
अणु
	u16 val;

	/* set dll backup mode */
	val = sdhci_पढ़ोl(host, SDHCI_SPRD_REG_DEBOUNCE);
	val |= SDHCI_SPRD_BIT_DLL_BAK | SDHCI_SPRD_BIT_DLL_VAL;
	sdhci_ग_लिखोl(host, val, SDHCI_SPRD_REG_DEBOUNCE);
पूर्ण

अटल अंतरभूत u32 sdhci_sprd_पढ़ोl(काष्ठा sdhci_host *host, पूर्णांक reg)
अणु
	अगर (unlikely(reg == SDHCI_MAX_CURRENT))
		वापस SDHCI_SPRD_MAX_CUR;

	वापस पढ़ोl_relaxed(host->ioaddr + reg);
पूर्ण

अटल अंतरभूत व्योम sdhci_sprd_ग_लिखोl(काष्ठा sdhci_host *host, u32 val, पूर्णांक reg)
अणु
	/* SDHCI_MAX_CURRENT is reserved on Spपढ़ोtrum's platक्रमm */
	अगर (unlikely(reg == SDHCI_MAX_CURRENT))
		वापस;

	अगर (unlikely(reg == SDHCI_SIGNAL_ENABLE || reg == SDHCI_INT_ENABLE))
		val = val & SDHCI_SPRD_INT_SIGNAL_MASK;

	ग_लिखोl_relaxed(val, host->ioaddr + reg);
पूर्ण

अटल अंतरभूत व्योम sdhci_sprd_ग_लिखोw(काष्ठा sdhci_host *host, u16 val, पूर्णांक reg)
अणु
	/* SDHCI_BLOCK_COUNT is Read Only on Spपढ़ोtrum's platक्रमm */
	अगर (unlikely(reg == SDHCI_BLOCK_COUNT))
		वापस;

	ग_लिखोw_relaxed(val, host->ioaddr + reg);
पूर्ण

अटल अंतरभूत व्योम sdhci_sprd_ग_लिखोb(काष्ठा sdhci_host *host, u8 val, पूर्णांक reg)
अणु
	/*
	 * Since BIT(3) of SDHCI_SOFTWARE_RESET is reserved according to the
	 * standard specअगरication, sdhci_reset() ग_लिखो this रेजिस्टर directly
	 * without checking other reserved bits, that will clear BIT(3) which
	 * is defined as hardware reset on Spपढ़ोtrum's platक्रमm and clearing
	 * it by mistake will lead the card not work. So here we need to work
	 * around it.
	 */
	अगर (unlikely(reg == SDHCI_SOFTWARE_RESET)) अणु
		अगर (पढ़ोb_relaxed(host->ioaddr + reg) & SDHCI_HW_RESET_CARD)
			val |= SDHCI_HW_RESET_CARD;
	पूर्ण

	ग_लिखोb_relaxed(val, host->ioaddr + reg);
पूर्ण

अटल अंतरभूत व्योम sdhci_sprd_sd_clk_off(काष्ठा sdhci_host *host)
अणु
	u16 ctrl = sdhci_पढ़ोw(host, SDHCI_CLOCK_CONTROL);

	ctrl &= ~SDHCI_CLOCK_CARD_EN;
	sdhci_ग_लिखोw(host, ctrl, SDHCI_CLOCK_CONTROL);
पूर्ण

अटल अंतरभूत व्योम sdhci_sprd_sd_clk_on(काष्ठा sdhci_host *host)
अणु
	u16 ctrl;

	ctrl = sdhci_पढ़ोw(host, SDHCI_CLOCK_CONTROL);
	ctrl |= SDHCI_CLOCK_CARD_EN;
	sdhci_ग_लिखोw(host, ctrl, SDHCI_CLOCK_CONTROL);
पूर्ण

अटल अंतरभूत व्योम
sdhci_sprd_set_dll_invert(काष्ठा sdhci_host *host, u32 mask, bool en)
अणु
	u32 dll_dly_offset;

	dll_dly_offset = sdhci_पढ़ोl(host, SDHCI_SPRD_REG_32_DLL_DLY_OFFSET);
	अगर (en)
		dll_dly_offset |= mask;
	अन्यथा
		dll_dly_offset &= ~mask;
	sdhci_ग_लिखोl(host, dll_dly_offset, SDHCI_SPRD_REG_32_DLL_DLY_OFFSET);
पूर्ण

अटल अंतरभूत u32 sdhci_sprd_calc_भाग(u32 base_clk, u32 clk)
अणु
	u32 भाग;

	/* select 2x घड़ी source */
	अगर (base_clk <= clk * 2)
		वापस 0;

	भाग = (u32) (base_clk / (clk * 2));

	अगर ((base_clk / भाग) > (clk * 2))
		भाग++;

	अगर (भाग > SDHCI_SPRD_CLK_MAX_DIV)
		भाग = SDHCI_SPRD_CLK_MAX_DIV;

	अगर (भाग % 2)
		भाग = (भाग + 1) / 2;
	अन्यथा
		भाग = भाग / 2;

	वापस भाग;
पूर्ण

अटल अंतरभूत व्योम _sdhci_sprd_set_घड़ी(काष्ठा sdhci_host *host,
					अचिन्हित पूर्णांक clk)
अणु
	काष्ठा sdhci_sprd_host *sprd_host = TO_SPRD_HOST(host);
	u32 भाग, val, mask;

	sdhci_ग_लिखोw(host, 0, SDHCI_CLOCK_CONTROL);

	भाग = sdhci_sprd_calc_भाग(sprd_host->base_rate, clk);
	भाग = ((भाग & 0x300) >> 2) | ((भाग & 0xFF) << 8);
	sdhci_enable_clk(host, भाग);

	/* enable स्वतः gate sdhc_enable_स्वतः_gate */
	val = sdhci_पढ़ोl(host, SDHCI_SPRD_REG_32_BUSY_POSI);
	mask = SDHCI_SPRD_BIT_OUTR_CLK_AUTO_EN |
	       SDHCI_SPRD_BIT_INNR_CLK_AUTO_EN;
	अगर (mask != (val & mask)) अणु
		val |= mask;
		sdhci_ग_लिखोl(host, val, SDHCI_SPRD_REG_32_BUSY_POSI);
	पूर्ण
पूर्ण

अटल व्योम sdhci_sprd_enable_phy_dll(काष्ठा sdhci_host *host)
अणु
	u32 पंचांगp;

	पंचांगp = sdhci_पढ़ोl(host, SDHCI_SPRD_REG_32_DLL_CFG);
	पंचांगp &= ~(SDHCI_SPRD_DLL_EN | SDHCI_SPRD_DLL_ALL_CPST_EN);
	sdhci_ग_लिखोl(host, पंचांगp, SDHCI_SPRD_REG_32_DLL_CFG);
	/* रुको 1ms */
	usleep_range(1000, 1250);

	पंचांगp = sdhci_पढ़ोl(host, SDHCI_SPRD_REG_32_DLL_CFG);
	पंचांगp |= SDHCI_SPRD_DLL_ALL_CPST_EN | SDHCI_SPRD_DLL_SEARCH_MODE |
		SDHCI_SPRD_DLL_INIT_COUNT | SDHCI_SPRD_DLL_PHASE_INTERNAL;
	sdhci_ग_लिखोl(host, पंचांगp, SDHCI_SPRD_REG_32_DLL_CFG);
	/* रुको 1ms */
	usleep_range(1000, 1250);

	पंचांगp = sdhci_पढ़ोl(host, SDHCI_SPRD_REG_32_DLL_CFG);
	पंचांगp |= SDHCI_SPRD_DLL_EN;
	sdhci_ग_लिखोl(host, पंचांगp, SDHCI_SPRD_REG_32_DLL_CFG);
	/* रुको 1ms */
	usleep_range(1000, 1250);
पूर्ण

अटल व्योम sdhci_sprd_set_घड़ी(काष्ठा sdhci_host *host, अचिन्हित पूर्णांक घड़ी)
अणु
	bool en = false, clk_changed = false;

	अगर (घड़ी == 0) अणु
		sdhci_ग_लिखोw(host, 0, SDHCI_CLOCK_CONTROL);
	पूर्ण अन्यथा अगर (घड़ी != host->घड़ी) अणु
		sdhci_sprd_sd_clk_off(host);
		_sdhci_sprd_set_घड़ी(host, घड़ी);

		अगर (घड़ी <= 400000)
			en = true;
		sdhci_sprd_set_dll_invert(host, SDHCI_SPRD_BIT_CMD_DLY_INV |
					  SDHCI_SPRD_BIT_POSRD_DLY_INV, en);
		clk_changed = true;
	पूर्ण अन्यथा अणु
		_sdhci_sprd_set_घड़ी(host, घड़ी);
	पूर्ण

	/*
	 * According to the Spपढ़ोtrum SD host specअगरication, when we changed
	 * the घड़ी to be more than 52M, we should enable the PHY DLL which
	 * is used to track the घड़ी frequency to make the घड़ी work more
	 * stable. Otherwise deviation may occur of the higher घड़ी.
	 */
	अगर (clk_changed && घड़ी > SDHCI_SPRD_PHY_DLL_CLK)
		sdhci_sprd_enable_phy_dll(host);
पूर्ण

अटल अचिन्हित पूर्णांक sdhci_sprd_get_max_घड़ी(काष्ठा sdhci_host *host)
अणु
	काष्ठा sdhci_sprd_host *sprd_host = TO_SPRD_HOST(host);

	वापस clk_round_rate(sprd_host->clk_sdio, अच_दीर्घ_उच्च);
पूर्ण

अटल अचिन्हित पूर्णांक sdhci_sprd_get_min_घड़ी(काष्ठा sdhci_host *host)
अणु
	वापस 400000;
पूर्ण

अटल व्योम sdhci_sprd_set_uhs_संकेतing(काष्ठा sdhci_host *host,
					 अचिन्हित पूर्णांक timing)
अणु
	काष्ठा sdhci_sprd_host *sprd_host = TO_SPRD_HOST(host);
	काष्ठा mmc_host *mmc = host->mmc;
	u32 *p = sprd_host->phy_delay;
	u16 ctrl_2;

	अगर (timing == host->timing)
		वापस;

	ctrl_2 = sdhci_पढ़ोw(host, SDHCI_HOST_CONTROL2);
	/* Select Bus Speed Mode क्रम host */
	ctrl_2 &= ~SDHCI_CTRL_UHS_MASK;
	चयन (timing) अणु
	हाल MMC_TIMING_UHS_SDR12:
		ctrl_2 |= SDHCI_CTRL_UHS_SDR12;
		अवरोध;
	हाल MMC_TIMING_MMC_HS:
	हाल MMC_TIMING_SD_HS:
	हाल MMC_TIMING_UHS_SDR25:
		ctrl_2 |= SDHCI_CTRL_UHS_SDR25;
		अवरोध;
	हाल MMC_TIMING_UHS_SDR50:
		ctrl_2 |= SDHCI_CTRL_UHS_SDR50;
		अवरोध;
	हाल MMC_TIMING_UHS_SDR104:
		ctrl_2 |= SDHCI_CTRL_UHS_SDR104;
		अवरोध;
	हाल MMC_TIMING_UHS_DDR50:
	हाल MMC_TIMING_MMC_DDR52:
		ctrl_2 |= SDHCI_CTRL_UHS_DDR50;
		अवरोध;
	हाल MMC_TIMING_MMC_HS200:
		ctrl_2 |= SDHCI_SPRD_CTRL_HS200;
		अवरोध;
	हाल MMC_TIMING_MMC_HS400:
		ctrl_2 |= SDHCI_SPRD_CTRL_HS400;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	sdhci_ग_लिखोw(host, ctrl_2, SDHCI_HOST_CONTROL2);

	अगर (!mmc->ios.enhanced_strobe)
		sdhci_ग_लिखोl(host, p[timing], SDHCI_SPRD_REG_32_DLL_DLY);
पूर्ण

अटल व्योम sdhci_sprd_hw_reset(काष्ठा sdhci_host *host)
अणु
	पूर्णांक val;

	/*
	 * Note: करोn't use sdhci_ग_लिखोb() API here since it is redirected to
	 * sdhci_sprd_ग_लिखोb() in which we have a workaround क्रम
	 * SDHCI_SOFTWARE_RESET which would make bit SDHCI_HW_RESET_CARD can
	 * not be cleared.
	 */
	val = पढ़ोb_relaxed(host->ioaddr + SDHCI_SOFTWARE_RESET);
	val &= ~SDHCI_HW_RESET_CARD;
	ग_लिखोb_relaxed(val, host->ioaddr + SDHCI_SOFTWARE_RESET);
	/* रुको क्रम 10 us */
	usleep_range(10, 20);

	val |= SDHCI_HW_RESET_CARD;
	ग_लिखोb_relaxed(val, host->ioaddr + SDHCI_SOFTWARE_RESET);
	usleep_range(300, 500);
पूर्ण

अटल अचिन्हित पूर्णांक sdhci_sprd_get_max_समयout_count(काष्ठा sdhci_host *host)
अणु
	/* The Spredtrum controller actual maximum समयout count is 1 << 31 */
	वापस 1 << 31;
पूर्ण

अटल अचिन्हित पूर्णांक sdhci_sprd_get_ro(काष्ठा sdhci_host *host)
अणु
	वापस 0;
पूर्ण

अटल व्योम sdhci_sprd_request_करोne(काष्ठा sdhci_host *host,
				    काष्ठा mmc_request *mrq)
अणु
	/* Validate अगर the request was from software queue firstly. */
	अगर (mmc_hsq_finalize_request(host->mmc, mrq))
		वापस;

	mmc_request_करोne(host->mmc, mrq);
पूर्ण

अटल काष्ठा sdhci_ops sdhci_sprd_ops = अणु
	.पढ़ो_l = sdhci_sprd_पढ़ोl,
	.ग_लिखो_l = sdhci_sprd_ग_लिखोl,
	.ग_लिखो_b = sdhci_sprd_ग_लिखोb,
	.set_घड़ी = sdhci_sprd_set_घड़ी,
	.get_max_घड़ी = sdhci_sprd_get_max_घड़ी,
	.get_min_घड़ी = sdhci_sprd_get_min_घड़ी,
	.set_bus_width = sdhci_set_bus_width,
	.reset = sdhci_reset,
	.set_uhs_संकेतing = sdhci_sprd_set_uhs_संकेतing,
	.hw_reset = sdhci_sprd_hw_reset,
	.get_max_समयout_count = sdhci_sprd_get_max_समयout_count,
	.get_ro = sdhci_sprd_get_ro,
	.request_करोne = sdhci_sprd_request_करोne,
पूर्ण;

अटल व्योम sdhci_sprd_check_स्वतः_cmd23(काष्ठा mmc_host *mmc,
					काष्ठा mmc_request *mrq)
अणु
	काष्ठा sdhci_host *host = mmc_priv(mmc);
	काष्ठा sdhci_sprd_host *sprd_host = TO_SPRD_HOST(host);

	host->flags |= sprd_host->flags & SDHCI_AUTO_CMD23;

	/*
	 * From version 4.10 onward, ARGUMENT2 रेजिस्टर is also as 32-bit
	 * block count रेजिस्टर which करोesn't support stuff bits of
	 * CMD23 argument on Spपढ़ोtrum's sd host controller.
	 */
	अगर (host->version >= SDHCI_SPEC_410 &&
	    mrq->sbc && (mrq->sbc->arg & SDHCI_SPRD_ARG2_STUFF) &&
	    (host->flags & SDHCI_AUTO_CMD23))
		host->flags &= ~SDHCI_AUTO_CMD23;
पूर्ण

अटल व्योम sdhci_sprd_request(काष्ठा mmc_host *mmc, काष्ठा mmc_request *mrq)
अणु
	sdhci_sprd_check_स्वतः_cmd23(mmc, mrq);

	sdhci_request(mmc, mrq);
पूर्ण

अटल पूर्णांक sdhci_sprd_request_atomic(काष्ठा mmc_host *mmc,
				     काष्ठा mmc_request *mrq)
अणु
	sdhci_sprd_check_स्वतः_cmd23(mmc, mrq);

	वापस sdhci_request_atomic(mmc, mrq);
पूर्ण

अटल पूर्णांक sdhci_sprd_voltage_चयन(काष्ठा mmc_host *mmc, काष्ठा mmc_ios *ios)
अणु
	काष्ठा sdhci_host *host = mmc_priv(mmc);
	काष्ठा sdhci_sprd_host *sprd_host = TO_SPRD_HOST(host);
	पूर्णांक ret;

	अगर (!IS_ERR(mmc->supply.vqmmc)) अणु
		ret = mmc_regulator_set_vqmmc(mmc, ios);
		अगर (ret < 0) अणु
			pr_err("%s: Switching signalling voltage failed\n",
			       mmc_hostname(mmc));
			वापस ret;
		पूर्ण
	पूर्ण

	अगर (IS_ERR(sprd_host->pinctrl))
		वापस 0;

	चयन (ios->संकेत_voltage) अणु
	हाल MMC_SIGNAL_VOLTAGE_180:
		ret = pinctrl_select_state(sprd_host->pinctrl,
					   sprd_host->pins_uhs);
		अगर (ret) अणु
			pr_err("%s: failed to select uhs pin state\n",
			       mmc_hostname(mmc));
			वापस ret;
		पूर्ण
		अवरोध;

	शेष:
		fallthrough;
	हाल MMC_SIGNAL_VOLTAGE_330:
		ret = pinctrl_select_state(sprd_host->pinctrl,
					   sprd_host->pins_शेष);
		अगर (ret) अणु
			pr_err("%s: failed to select default pin state\n",
			       mmc_hostname(mmc));
			वापस ret;
		पूर्ण
		अवरोध;
	पूर्ण

	/* Wait क्रम 300 ~ 500 us क्रम pin state stable */
	usleep_range(300, 500);
	sdhci_reset(host, SDHCI_RESET_CMD | SDHCI_RESET_DATA);

	वापस 0;
पूर्ण

अटल व्योम sdhci_sprd_hs400_enhanced_strobe(काष्ठा mmc_host *mmc,
					     काष्ठा mmc_ios *ios)
अणु
	काष्ठा sdhci_host *host = mmc_priv(mmc);
	काष्ठा sdhci_sprd_host *sprd_host = TO_SPRD_HOST(host);
	u32 *p = sprd_host->phy_delay;
	u16 ctrl_2;

	अगर (!ios->enhanced_strobe)
		वापस;

	sdhci_sprd_sd_clk_off(host);

	/* Set HS400 enhanced strobe mode */
	ctrl_2 = sdhci_पढ़ोw(host, SDHCI_HOST_CONTROL2);
	ctrl_2 &= ~SDHCI_CTRL_UHS_MASK;
	ctrl_2 |= SDHCI_SPRD_CTRL_HS400ES;
	sdhci_ग_लिखोw(host, ctrl_2, SDHCI_HOST_CONTROL2);

	sdhci_sprd_sd_clk_on(host);

	/* Set the PHY DLL delay value क्रम HS400 enhanced strobe mode */
	sdhci_ग_लिखोl(host, p[MMC_TIMING_MMC_HS400 + 1],
		     SDHCI_SPRD_REG_32_DLL_DLY);
पूर्ण

अटल व्योम sdhci_sprd_phy_param_parse(काष्ठा sdhci_sprd_host *sprd_host,
				       काष्ठा device_node *np)
अणु
	u32 *p = sprd_host->phy_delay;
	पूर्णांक ret, i, index;
	u32 val[4];

	क्रम (i = 0; i < ARRAY_SIZE(sdhci_sprd_phy_cfgs); i++) अणु
		ret = of_property_पढ़ो_u32_array(np,
				sdhci_sprd_phy_cfgs[i].property, val, 4);
		अगर (ret)
			जारी;

		index = sdhci_sprd_phy_cfgs[i].timing;
		p[index] = val[0] | (val[1] << 8) | (val[2] << 16) | (val[3] << 24);
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा sdhci_pltfm_data sdhci_sprd_pdata = अणु
	.quirks = SDHCI_QUIRK_BROKEN_CARD_DETECTION |
		  SDHCI_QUIRK_DATA_TIMEOUT_USES_SDCLK |
		  SDHCI_QUIRK_MISSING_CAPS,
	.quirks2 = SDHCI_QUIRK2_BROKEN_HS200 |
		   SDHCI_QUIRK2_USE_32BIT_BLK_CNT |
		   SDHCI_QUIRK2_PRESET_VALUE_BROKEN,
	.ops = &sdhci_sprd_ops,
पूर्ण;

अटल पूर्णांक sdhci_sprd_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sdhci_host *host;
	काष्ठा sdhci_sprd_host *sprd_host;
	काष्ठा mmc_hsq *hsq;
	काष्ठा clk *clk;
	पूर्णांक ret = 0;

	host = sdhci_pltfm_init(pdev, &sdhci_sprd_pdata, माप(*sprd_host));
	अगर (IS_ERR(host))
		वापस PTR_ERR(host);

	host->dma_mask = DMA_BIT_MASK(64);
	pdev->dev.dma_mask = &host->dma_mask;
	host->mmc_host_ops.request = sdhci_sprd_request;
	host->mmc_host_ops.hs400_enhanced_strobe =
		sdhci_sprd_hs400_enhanced_strobe;
	/*
	 * We can not use the standard ops to change and detect the voltage
	 * संकेत क्रम Spपढ़ोtrum SD host controller, since our voltage regulator
	 * क्रम I/O is fixed in hardware, that means we करो not need control
	 * the standard SD host controller to change the I/O voltage.
	 */
	host->mmc_host_ops.start_संकेत_voltage_चयन =
		sdhci_sprd_voltage_चयन;

	host->mmc->caps = MMC_CAP_SD_HIGHSPEED | MMC_CAP_MMC_HIGHSPEED |
		MMC_CAP_WAIT_WHILE_BUSY;

	ret = mmc_of_parse(host->mmc);
	अगर (ret)
		जाओ pltfm_मुक्त;

	अगर (!mmc_card_is_removable(host->mmc))
		host->mmc_host_ops.request_atomic = sdhci_sprd_request_atomic;
	अन्यथा
		host->always_defer_करोne = true;

	sprd_host = TO_SPRD_HOST(host);
	sdhci_sprd_phy_param_parse(sprd_host, pdev->dev.of_node);

	sprd_host->pinctrl = devm_pinctrl_get(&pdev->dev);
	अगर (!IS_ERR(sprd_host->pinctrl)) अणु
		sprd_host->pins_uhs =
			pinctrl_lookup_state(sprd_host->pinctrl, "state_uhs");
		अगर (IS_ERR(sprd_host->pins_uhs)) अणु
			ret = PTR_ERR(sprd_host->pins_uhs);
			जाओ pltfm_मुक्त;
		पूर्ण

		sprd_host->pins_शेष =
			pinctrl_lookup_state(sprd_host->pinctrl, "default");
		अगर (IS_ERR(sprd_host->pins_शेष)) अणु
			ret = PTR_ERR(sprd_host->pins_शेष);
			जाओ pltfm_मुक्त;
		पूर्ण
	पूर्ण

	clk = devm_clk_get(&pdev->dev, "sdio");
	अगर (IS_ERR(clk)) अणु
		ret = PTR_ERR(clk);
		जाओ pltfm_मुक्त;
	पूर्ण
	sprd_host->clk_sdio = clk;
	sprd_host->base_rate = clk_get_rate(sprd_host->clk_sdio);
	अगर (!sprd_host->base_rate)
		sprd_host->base_rate = SDHCI_SPRD_CLK_DEF_RATE;

	clk = devm_clk_get(&pdev->dev, "enable");
	अगर (IS_ERR(clk)) अणु
		ret = PTR_ERR(clk);
		जाओ pltfm_मुक्त;
	पूर्ण
	sprd_host->clk_enable = clk;

	clk = devm_clk_get(&pdev->dev, "2x_enable");
	अगर (!IS_ERR(clk))
		sprd_host->clk_2x_enable = clk;

	ret = clk_prepare_enable(sprd_host->clk_sdio);
	अगर (ret)
		जाओ pltfm_मुक्त;

	ret = clk_prepare_enable(sprd_host->clk_enable);
	अगर (ret)
		जाओ clk_disable;

	ret = clk_prepare_enable(sprd_host->clk_2x_enable);
	अगर (ret)
		जाओ clk_disable2;

	sdhci_sprd_init_config(host);
	host->version = sdhci_पढ़ोw(host, SDHCI_HOST_VERSION);
	sprd_host->version = ((host->version & SDHCI_VENDOR_VER_MASK) >>
			       SDHCI_VENDOR_VER_SHIFT);

	pm_runसमय_get_noresume(&pdev->dev);
	pm_runसमय_set_active(&pdev->dev);
	pm_runसमय_enable(&pdev->dev);
	pm_runसमय_set_स्वतःsuspend_delay(&pdev->dev, 50);
	pm_runसमय_use_स्वतःsuspend(&pdev->dev);
	pm_suspend_ignore_children(&pdev->dev, 1);

	sdhci_enable_v4_mode(host);

	/*
	 * Supply the existing CAPS, but clear the UHS-I modes. This
	 * will allow these modes to be specअगरied only by device
	 * tree properties through mmc_of_parse().
	 */
	host->caps = sdhci_पढ़ोl(host, SDHCI_CAPABILITIES);
	host->caps1 = sdhci_पढ़ोl(host, SDHCI_CAPABILITIES_1);
	host->caps1 &= ~(SDHCI_SUPPORT_SDR50 | SDHCI_SUPPORT_SDR104 |
			 SDHCI_SUPPORT_DDR50);

	ret = sdhci_setup_host(host);
	अगर (ret)
		जाओ pm_runसमय_disable;

	sprd_host->flags = host->flags;

	hsq = devm_kzalloc(&pdev->dev, माप(*hsq), GFP_KERNEL);
	अगर (!hsq) अणु
		ret = -ENOMEM;
		जाओ err_cleanup_host;
	पूर्ण

	ret = mmc_hsq_init(hsq, host->mmc);
	अगर (ret)
		जाओ err_cleanup_host;

	ret = __sdhci_add_host(host);
	अगर (ret)
		जाओ err_cleanup_host;

	pm_runसमय_mark_last_busy(&pdev->dev);
	pm_runसमय_put_स्वतःsuspend(&pdev->dev);

	वापस 0;

err_cleanup_host:
	sdhci_cleanup_host(host);

pm_runसमय_disable:
	pm_runसमय_put_noidle(&pdev->dev);
	pm_runसमय_disable(&pdev->dev);
	pm_runसमय_set_suspended(&pdev->dev);

	clk_disable_unprepare(sprd_host->clk_2x_enable);

clk_disable2:
	clk_disable_unprepare(sprd_host->clk_enable);

clk_disable:
	clk_disable_unprepare(sprd_host->clk_sdio);

pltfm_मुक्त:
	sdhci_pltfm_मुक्त(pdev);
	वापस ret;
पूर्ण

अटल पूर्णांक sdhci_sprd_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sdhci_host *host = platक्रमm_get_drvdata(pdev);
	काष्ठा sdhci_sprd_host *sprd_host = TO_SPRD_HOST(host);

	sdhci_हटाओ_host(host, 0);

	clk_disable_unprepare(sprd_host->clk_sdio);
	clk_disable_unprepare(sprd_host->clk_enable);
	clk_disable_unprepare(sprd_host->clk_2x_enable);

	sdhci_pltfm_मुक्त(pdev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id sdhci_sprd_of_match[] = अणु
	अणु .compatible = "sprd,sdhci-r11", पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, sdhci_sprd_of_match);

#अगर_घोषित CONFIG_PM
अटल पूर्णांक sdhci_sprd_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा sdhci_host *host = dev_get_drvdata(dev);
	काष्ठा sdhci_sprd_host *sprd_host = TO_SPRD_HOST(host);

	mmc_hsq_suspend(host->mmc);
	sdhci_runसमय_suspend_host(host);

	clk_disable_unprepare(sprd_host->clk_sdio);
	clk_disable_unprepare(sprd_host->clk_enable);
	clk_disable_unprepare(sprd_host->clk_2x_enable);

	वापस 0;
पूर्ण

अटल पूर्णांक sdhci_sprd_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा sdhci_host *host = dev_get_drvdata(dev);
	काष्ठा sdhci_sprd_host *sprd_host = TO_SPRD_HOST(host);
	पूर्णांक ret;

	ret = clk_prepare_enable(sprd_host->clk_2x_enable);
	अगर (ret)
		वापस ret;

	ret = clk_prepare_enable(sprd_host->clk_enable);
	अगर (ret)
		जाओ clk_2x_disable;

	ret = clk_prepare_enable(sprd_host->clk_sdio);
	अगर (ret)
		जाओ clk_disable;

	sdhci_runसमय_resume_host(host, 1);
	mmc_hsq_resume(host->mmc);

	वापस 0;

clk_disable:
	clk_disable_unprepare(sprd_host->clk_enable);

clk_2x_disable:
	clk_disable_unprepare(sprd_host->clk_2x_enable);

	वापस ret;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा dev_pm_ops sdhci_sprd_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(pm_runसमय_क्रमce_suspend,
				pm_runसमय_क्रमce_resume)
	SET_RUNTIME_PM_OPS(sdhci_sprd_runसमय_suspend,
			   sdhci_sprd_runसमय_resume, शून्य)
पूर्ण;

अटल काष्ठा platक्रमm_driver sdhci_sprd_driver = अणु
	.probe = sdhci_sprd_probe,
	.हटाओ = sdhci_sprd_हटाओ,
	.driver = अणु
		.name = "sdhci_sprd_r11",
		.probe_type = PROBE_PREFER_ASYNCHRONOUS,
		.of_match_table = sdhci_sprd_of_match,
		.pm = &sdhci_sprd_pm_ops,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(sdhci_sprd_driver);

MODULE_DESCRIPTION("Spreadtrum sdio host controller r11 driver");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:sdhci-sprd-r11");
