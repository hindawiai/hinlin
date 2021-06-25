<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2010 Google, Inc.
 */

#समावेश <linux/delay.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/err.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/iopoll.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/clk.h>
#समावेश <linux/पन.स>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/pinctrl/consumer.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/reset.h>
#समावेश <linux/mmc/card.h>
#समावेश <linux/mmc/host.h>
#समावेश <linux/mmc/mmc.h>
#समावेश <linux/mmc/slot-gpपन.स>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/kसमय.स>

#समावेश "sdhci-pltfm.h"
#समावेश "cqhci.h"

/* Tegra SDHOST controller venकरोr रेजिस्टर definitions */
#घोषणा SDHCI_TEGRA_VENDOR_CLOCK_CTRL			0x100
#घोषणा SDHCI_CLOCK_CTRL_TAP_MASK			0x00ff0000
#घोषणा SDHCI_CLOCK_CTRL_TAP_SHIFT			16
#घोषणा SDHCI_CLOCK_CTRL_TRIM_MASK			0x1f000000
#घोषणा SDHCI_CLOCK_CTRL_TRIM_SHIFT			24
#घोषणा SDHCI_CLOCK_CTRL_SDR50_TUNING_OVERRIDE		BIT(5)
#घोषणा SDHCI_CLOCK_CTRL_PADPIPE_CLKEN_OVERRIDE		BIT(3)
#घोषणा SDHCI_CLOCK_CTRL_SPI_MODE_CLKEN_OVERRIDE	BIT(2)

#घोषणा SDHCI_TEGRA_VENDOR_SYS_SW_CTRL			0x104
#घोषणा SDHCI_TEGRA_SYS_SW_CTRL_ENHANCED_STROBE		BIT(31)

#घोषणा SDHCI_TEGRA_VENDOR_CAP_OVERRIDES		0x10c
#घोषणा SDHCI_TEGRA_CAP_OVERRIDES_DQS_TRIM_MASK		0x00003f00
#घोषणा SDHCI_TEGRA_CAP_OVERRIDES_DQS_TRIM_SHIFT	8

#घोषणा SDHCI_TEGRA_VENDOR_MISC_CTRL			0x120
#घोषणा SDHCI_MISC_CTRL_ERASE_TIMEOUT_LIMIT		BIT(0)
#घोषणा SDHCI_MISC_CTRL_ENABLE_SDR104			0x8
#घोषणा SDHCI_MISC_CTRL_ENABLE_SDR50			0x10
#घोषणा SDHCI_MISC_CTRL_ENABLE_SDHCI_SPEC_300		0x20
#घोषणा SDHCI_MISC_CTRL_ENABLE_DDR50			0x200

#घोषणा SDHCI_TEGRA_VENDOR_DLLCAL_CFG			0x1b0
#घोषणा SDHCI_TEGRA_DLLCAL_CALIBRATE			BIT(31)

#घोषणा SDHCI_TEGRA_VENDOR_DLLCAL_STA			0x1bc
#घोषणा SDHCI_TEGRA_DLLCAL_STA_ACTIVE			BIT(31)

#घोषणा SDHCI_VNDR_TUN_CTRL0_0				0x1c0
#घोषणा SDHCI_VNDR_TUN_CTRL0_TUN_HW_TAP			0x20000
#घोषणा SDHCI_VNDR_TUN_CTRL0_START_TAP_VAL_MASK		0x03fc0000
#घोषणा SDHCI_VNDR_TUN_CTRL0_START_TAP_VAL_SHIFT	18
#घोषणा SDHCI_VNDR_TUN_CTRL0_MUL_M_MASK			0x00001fc0
#घोषणा SDHCI_VNDR_TUN_CTRL0_MUL_M_SHIFT		6
#घोषणा SDHCI_VNDR_TUN_CTRL0_TUN_ITER_MASK		0x000e000
#घोषणा SDHCI_VNDR_TUN_CTRL0_TUN_ITER_SHIFT		13
#घोषणा TRIES_128					2
#घोषणा TRIES_256					4
#घोषणा SDHCI_VNDR_TUN_CTRL0_TUN_WORD_SEL_MASK		0x7

#घोषणा SDHCI_TEGRA_VNDR_TUN_CTRL1_0			0x1c4
#घोषणा SDHCI_TEGRA_VNDR_TUN_STATUS0			0x1C8
#घोषणा SDHCI_TEGRA_VNDR_TUN_STATUS1			0x1CC
#घोषणा SDHCI_TEGRA_VNDR_TUN_STATUS1_TAP_MASK		0xFF
#घोषणा SDHCI_TEGRA_VNDR_TUN_STATUS1_END_TAP_SHIFT	0x8
#घोषणा TUNING_WORD_BIT_SIZE				32

#घोषणा SDHCI_TEGRA_AUTO_CAL_CONFIG			0x1e4
#घोषणा SDHCI_AUTO_CAL_START				BIT(31)
#घोषणा SDHCI_AUTO_CAL_ENABLE				BIT(29)
#घोषणा SDHCI_AUTO_CAL_PDPU_OFFSET_MASK			0x0000ffff

#घोषणा SDHCI_TEGRA_SDMEM_COMP_PADCTRL			0x1e0
#घोषणा SDHCI_TEGRA_SDMEM_COMP_PADCTRL_VREF_SEL_MASK	0x0000000f
#घोषणा SDHCI_TEGRA_SDMEM_COMP_PADCTRL_VREF_SEL_VAL	0x7
#घोषणा SDHCI_TEGRA_SDMEM_COMP_PADCTRL_E_INPUT_E_PWRD	BIT(31)
#घोषणा SDHCI_COMP_PADCTRL_DRVUPDN_OFFSET_MASK		0x07FFF000

#घोषणा SDHCI_TEGRA_AUTO_CAL_STATUS			0x1ec
#घोषणा SDHCI_TEGRA_AUTO_CAL_ACTIVE			BIT(31)

#घोषणा NVQUIRK_FORCE_SDHCI_SPEC_200			BIT(0)
#घोषणा NVQUIRK_ENABLE_BLOCK_GAP_DET			BIT(1)
#घोषणा NVQUIRK_ENABLE_SDHCI_SPEC_300			BIT(2)
#घोषणा NVQUIRK_ENABLE_SDR50				BIT(3)
#घोषणा NVQUIRK_ENABLE_SDR104				BIT(4)
#घोषणा NVQUIRK_ENABLE_DDR50				BIT(5)
/*
 * HAS_PADCALIB NVQUIRK is क्रम SoC's supporting स्वतः calibration of pads
 * drive strength.
 */
#घोषणा NVQUIRK_HAS_PADCALIB				BIT(6)
/*
 * NEEDS_PAD_CONTROL NVQUIRK is क्रम SoC's having separate 3V3 and 1V8 pads.
 * 3V3/1V8 pad selection happens through pinctrl state selection depending
 * on the संकेतing mode.
 */
#घोषणा NVQUIRK_NEEDS_PAD_CONTROL			BIT(7)
#घोषणा NVQUIRK_DIS_CARD_CLK_CONFIG_TAP			BIT(8)
#घोषणा NVQUIRK_CQHCI_DCMD_R1B_CMD_TIMING		BIT(9)

/*
 * NVQUIRK_HAS_TMCLK is क्रम SoC's having separate समयout घड़ी क्रम Tegra
 * SDMMC hardware data समयout.
 */
#घोषणा NVQUIRK_HAS_TMCLK				BIT(10)

/* SDMMC CQE Base Address क्रम Tegra Host Ver 4.1 and Higher */
#घोषणा SDHCI_TEGRA_CQE_BASE_ADDR			0xF000

#घोषणा SDHCI_TEGRA_CQE_TRNS_MODE	(SDHCI_TRNS_MULTI | \
					 SDHCI_TRNS_BLK_CNT_EN | \
					 SDHCI_TRNS_DMA)

काष्ठा sdhci_tegra_soc_data अणु
	स्थिर काष्ठा sdhci_pltfm_data *pdata;
	u64 dma_mask;
	u32 nvquirks;
	u8 min_tap_delay;
	u8 max_tap_delay;
पूर्ण;

/* Magic pull up and pull करोwn pad calibration offsets */
काष्ठा sdhci_tegra_स्वतःcal_offsets अणु
	u32 pull_up_3v3;
	u32 pull_करोwn_3v3;
	u32 pull_up_3v3_समयout;
	u32 pull_करोwn_3v3_समयout;
	u32 pull_up_1v8;
	u32 pull_करोwn_1v8;
	u32 pull_up_1v8_समयout;
	u32 pull_करोwn_1v8_समयout;
	u32 pull_up_sdr104;
	u32 pull_करोwn_sdr104;
	u32 pull_up_hs400;
	u32 pull_करोwn_hs400;
पूर्ण;

काष्ठा sdhci_tegra अणु
	स्थिर काष्ठा sdhci_tegra_soc_data *soc_data;
	काष्ठा gpio_desc *घातer_gpio;
	काष्ठा clk *पंचांगclk;
	bool ddr_संकेतing;
	bool pad_calib_required;
	bool pad_control_available;

	काष्ठा reset_control *rst;
	काष्ठा pinctrl *pinctrl_sdmmc;
	काष्ठा pinctrl_state *pinctrl_state_3v3;
	काष्ठा pinctrl_state *pinctrl_state_1v8;
	काष्ठा pinctrl_state *pinctrl_state_3v3_drv;
	काष्ठा pinctrl_state *pinctrl_state_1v8_drv;

	काष्ठा sdhci_tegra_स्वतःcal_offsets स्वतःcal_offsets;
	kसमय_प्रकार last_calib;

	u32 शेष_tap;
	u32 शेष_trim;
	u32 dqs_trim;
	bool enable_hwcq;
	अचिन्हित दीर्घ curr_clk_rate;
	u8 tuned_tap_delay;
पूर्ण;

अटल u16 tegra_sdhci_पढ़ोw(काष्ठा sdhci_host *host, पूर्णांक reg)
अणु
	काष्ठा sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	काष्ठा sdhci_tegra *tegra_host = sdhci_pltfm_priv(pltfm_host);
	स्थिर काष्ठा sdhci_tegra_soc_data *soc_data = tegra_host->soc_data;

	अगर (unlikely((soc_data->nvquirks & NVQUIRK_FORCE_SDHCI_SPEC_200) &&
			(reg == SDHCI_HOST_VERSION))) अणु
		/* Erratum: Version रेजिस्टर is invalid in HW. */
		वापस SDHCI_SPEC_200;
	पूर्ण

	वापस पढ़ोw(host->ioaddr + reg);
पूर्ण

अटल व्योम tegra_sdhci_ग_लिखोw(काष्ठा sdhci_host *host, u16 val, पूर्णांक reg)
अणु
	काष्ठा sdhci_pltfm_host *pltfm_host = sdhci_priv(host);

	चयन (reg) अणु
	हाल SDHCI_TRANSFER_MODE:
		/*
		 * Postpone this ग_लिखो, we must करो it together with a
		 * command ग_लिखो that is करोwn below.
		 */
		pltfm_host->xfer_mode_shaकरोw = val;
		वापस;
	हाल SDHCI_COMMAND:
		ग_लिखोl((val << 16) | pltfm_host->xfer_mode_shaकरोw,
			host->ioaddr + SDHCI_TRANSFER_MODE);
		वापस;
	पूर्ण

	ग_लिखोw(val, host->ioaddr + reg);
पूर्ण

अटल व्योम tegra_sdhci_ग_लिखोl(काष्ठा sdhci_host *host, u32 val, पूर्णांक reg)
अणु
	काष्ठा sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	काष्ठा sdhci_tegra *tegra_host = sdhci_pltfm_priv(pltfm_host);
	स्थिर काष्ठा sdhci_tegra_soc_data *soc_data = tegra_host->soc_data;

	/* Seems like we're getting spurious समयout and crc errors, so
	 * disable संकेतling of them. In हाल of real errors software
	 * समयrs should take care of eventually detecting them.
	 */
	अगर (unlikely(reg == SDHCI_SIGNAL_ENABLE))
		val &= ~(SDHCI_INT_TIMEOUT|SDHCI_INT_CRC);

	ग_लिखोl(val, host->ioaddr + reg);

	अगर (unlikely((soc_data->nvquirks & NVQUIRK_ENABLE_BLOCK_GAP_DET) &&
			(reg == SDHCI_INT_ENABLE))) अणु
		/* Erratum: Must enable block gap पूर्णांकerrupt detection */
		u8 gap_ctrl = पढ़ोb(host->ioaddr + SDHCI_BLOCK_GAP_CONTROL);
		अगर (val & SDHCI_INT_CARD_INT)
			gap_ctrl |= 0x8;
		अन्यथा
			gap_ctrl &= ~0x8;
		ग_लिखोb(gap_ctrl, host->ioaddr + SDHCI_BLOCK_GAP_CONTROL);
	पूर्ण
पूर्ण

अटल bool tegra_sdhci_configure_card_clk(काष्ठा sdhci_host *host, bool enable)
अणु
	bool status;
	u32 reg;

	reg = sdhci_पढ़ोw(host, SDHCI_CLOCK_CONTROL);
	status = !!(reg & SDHCI_CLOCK_CARD_EN);

	अगर (status == enable)
		वापस status;

	अगर (enable)
		reg |= SDHCI_CLOCK_CARD_EN;
	अन्यथा
		reg &= ~SDHCI_CLOCK_CARD_EN;

	sdhci_ग_लिखोw(host, reg, SDHCI_CLOCK_CONTROL);

	वापस status;
पूर्ण

अटल व्योम tegra210_sdhci_ग_लिखोw(काष्ठा sdhci_host *host, u16 val, पूर्णांक reg)
अणु
	bool is_tuning_cmd = 0;
	bool clk_enabled;
	u8 cmd;

	अगर (reg == SDHCI_COMMAND) अणु
		cmd = SDHCI_GET_CMD(val);
		is_tuning_cmd = cmd == MMC_SEND_TUNING_BLOCK ||
				cmd == MMC_SEND_TUNING_BLOCK_HS200;
	पूर्ण

	अगर (is_tuning_cmd)
		clk_enabled = tegra_sdhci_configure_card_clk(host, 0);

	ग_लिखोw(val, host->ioaddr + reg);

	अगर (is_tuning_cmd) अणु
		udelay(1);
		sdhci_reset(host, SDHCI_RESET_CMD | SDHCI_RESET_DATA);
		tegra_sdhci_configure_card_clk(host, clk_enabled);
	पूर्ण
पूर्ण

अटल अचिन्हित पूर्णांक tegra_sdhci_get_ro(काष्ठा sdhci_host *host)
अणु
	/*
	 * Write-enable shall be assumed अगर GPIO is missing in a board's
	 * device-tree because SDHCI's WRITE_PROTECT bit doesn't work on
	 * Tegra.
	 */
	वापस mmc_gpio_get_ro(host->mmc);
पूर्ण

अटल bool tegra_sdhci_is_pad_and_regulator_valid(काष्ठा sdhci_host *host)
अणु
	काष्ठा sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	काष्ठा sdhci_tegra *tegra_host = sdhci_pltfm_priv(pltfm_host);
	पूर्णांक has_1v8, has_3v3;

	/*
	 * The SoCs which have NVQUIRK_NEEDS_PAD_CONTROL require software pad
	 * voltage configuration in order to perक्रमm voltage चयनing. This
	 * means that valid pinctrl info is required on SDHCI instances capable
	 * of perक्रमming voltage चयनing. Whether or not an SDHCI instance is
	 * capable of voltage चयनing is determined based on the regulator.
	 */

	अगर (!(tegra_host->soc_data->nvquirks & NVQUIRK_NEEDS_PAD_CONTROL))
		वापस true;

	अगर (IS_ERR(host->mmc->supply.vqmmc))
		वापस false;

	has_1v8 = regulator_is_supported_voltage(host->mmc->supply.vqmmc,
						 1700000, 1950000);

	has_3v3 = regulator_is_supported_voltage(host->mmc->supply.vqmmc,
						 2700000, 3600000);

	अगर (has_1v8 == 1 && has_3v3 == 1)
		वापस tegra_host->pad_control_available;

	/* Fixed voltage, no pad control required. */
	वापस true;
पूर्ण

अटल व्योम tegra_sdhci_set_tap(काष्ठा sdhci_host *host, अचिन्हित पूर्णांक tap)
अणु
	काष्ठा sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	काष्ठा sdhci_tegra *tegra_host = sdhci_pltfm_priv(pltfm_host);
	स्थिर काष्ठा sdhci_tegra_soc_data *soc_data = tegra_host->soc_data;
	bool card_clk_enabled = false;
	u32 reg;

	/*
	 * Touching the tap values is a bit tricky on some SoC generations.
	 * The quirk enables a workaround क्रम a glitch that someबार occurs अगर
	 * the tap values are changed.
	 */

	अगर (soc_data->nvquirks & NVQUIRK_DIS_CARD_CLK_CONFIG_TAP)
		card_clk_enabled = tegra_sdhci_configure_card_clk(host, false);

	reg = sdhci_पढ़ोl(host, SDHCI_TEGRA_VENDOR_CLOCK_CTRL);
	reg &= ~SDHCI_CLOCK_CTRL_TAP_MASK;
	reg |= tap << SDHCI_CLOCK_CTRL_TAP_SHIFT;
	sdhci_ग_लिखोl(host, reg, SDHCI_TEGRA_VENDOR_CLOCK_CTRL);

	अगर (soc_data->nvquirks & NVQUIRK_DIS_CARD_CLK_CONFIG_TAP &&
	    card_clk_enabled) अणु
		udelay(1);
		sdhci_reset(host, SDHCI_RESET_CMD | SDHCI_RESET_DATA);
		tegra_sdhci_configure_card_clk(host, card_clk_enabled);
	पूर्ण
पूर्ण

अटल व्योम tegra_sdhci_hs400_enhanced_strobe(काष्ठा mmc_host *mmc,
					      काष्ठा mmc_ios *ios)
अणु
	काष्ठा sdhci_host *host = mmc_priv(mmc);
	u32 val;

	val = sdhci_पढ़ोl(host, SDHCI_TEGRA_VENDOR_SYS_SW_CTRL);

	अगर (ios->enhanced_strobe)
		val |= SDHCI_TEGRA_SYS_SW_CTRL_ENHANCED_STROBE;
	अन्यथा
		val &= ~SDHCI_TEGRA_SYS_SW_CTRL_ENHANCED_STROBE;

	sdhci_ग_लिखोl(host, val, SDHCI_TEGRA_VENDOR_SYS_SW_CTRL);

पूर्ण

अटल व्योम tegra_sdhci_reset(काष्ठा sdhci_host *host, u8 mask)
अणु
	काष्ठा sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	काष्ठा sdhci_tegra *tegra_host = sdhci_pltfm_priv(pltfm_host);
	स्थिर काष्ठा sdhci_tegra_soc_data *soc_data = tegra_host->soc_data;
	u32 misc_ctrl, clk_ctrl, pad_ctrl;

	sdhci_reset(host, mask);

	अगर (!(mask & SDHCI_RESET_ALL))
		वापस;

	tegra_sdhci_set_tap(host, tegra_host->शेष_tap);

	misc_ctrl = sdhci_पढ़ोl(host, SDHCI_TEGRA_VENDOR_MISC_CTRL);
	clk_ctrl = sdhci_पढ़ोl(host, SDHCI_TEGRA_VENDOR_CLOCK_CTRL);

	misc_ctrl &= ~(SDHCI_MISC_CTRL_ENABLE_SDHCI_SPEC_300 |
		       SDHCI_MISC_CTRL_ENABLE_SDR50 |
		       SDHCI_MISC_CTRL_ENABLE_DDR50 |
		       SDHCI_MISC_CTRL_ENABLE_SDR104);

	clk_ctrl &= ~(SDHCI_CLOCK_CTRL_TRIM_MASK |
		      SDHCI_CLOCK_CTRL_SPI_MODE_CLKEN_OVERRIDE);

	अगर (tegra_sdhci_is_pad_and_regulator_valid(host)) अणु
		/* Erratum: Enable SDHCI spec v3.00 support */
		अगर (soc_data->nvquirks & NVQUIRK_ENABLE_SDHCI_SPEC_300)
			misc_ctrl |= SDHCI_MISC_CTRL_ENABLE_SDHCI_SPEC_300;
		/* Advertise UHS modes as supported by host */
		अगर (soc_data->nvquirks & NVQUIRK_ENABLE_SDR50)
			misc_ctrl |= SDHCI_MISC_CTRL_ENABLE_SDR50;
		अगर (soc_data->nvquirks & NVQUIRK_ENABLE_DDR50)
			misc_ctrl |= SDHCI_MISC_CTRL_ENABLE_DDR50;
		अगर (soc_data->nvquirks & NVQUIRK_ENABLE_SDR104)
			misc_ctrl |= SDHCI_MISC_CTRL_ENABLE_SDR104;
		अगर (soc_data->nvquirks & NVQUIRK_ENABLE_SDR50)
			clk_ctrl |= SDHCI_CLOCK_CTRL_SDR50_TUNING_OVERRIDE;
	पूर्ण

	clk_ctrl |= tegra_host->शेष_trim << SDHCI_CLOCK_CTRL_TRIM_SHIFT;

	sdhci_ग_लिखोl(host, misc_ctrl, SDHCI_TEGRA_VENDOR_MISC_CTRL);
	sdhci_ग_लिखोl(host, clk_ctrl, SDHCI_TEGRA_VENDOR_CLOCK_CTRL);

	अगर (soc_data->nvquirks & NVQUIRK_HAS_PADCALIB) अणु
		pad_ctrl = sdhci_पढ़ोl(host, SDHCI_TEGRA_SDMEM_COMP_PADCTRL);
		pad_ctrl &= ~SDHCI_TEGRA_SDMEM_COMP_PADCTRL_VREF_SEL_MASK;
		pad_ctrl |= SDHCI_TEGRA_SDMEM_COMP_PADCTRL_VREF_SEL_VAL;
		sdhci_ग_लिखोl(host, pad_ctrl, SDHCI_TEGRA_SDMEM_COMP_PADCTRL);

		tegra_host->pad_calib_required = true;
	पूर्ण

	tegra_host->ddr_संकेतing = false;
पूर्ण

अटल व्योम tegra_sdhci_configure_cal_pad(काष्ठा sdhci_host *host, bool enable)
अणु
	u32 val;

	/*
	 * Enable or disable the additional I/O pad used by the drive strength
	 * calibration process.
	 */
	val = sdhci_पढ़ोl(host, SDHCI_TEGRA_SDMEM_COMP_PADCTRL);

	अगर (enable)
		val |= SDHCI_TEGRA_SDMEM_COMP_PADCTRL_E_INPUT_E_PWRD;
	अन्यथा
		val &= ~SDHCI_TEGRA_SDMEM_COMP_PADCTRL_E_INPUT_E_PWRD;

	sdhci_ग_लिखोl(host, val, SDHCI_TEGRA_SDMEM_COMP_PADCTRL);

	अगर (enable)
		usleep_range(1, 2);
पूर्ण

अटल व्योम tegra_sdhci_set_pad_स्वतःcal_offset(काष्ठा sdhci_host *host,
					       u16 pdpu)
अणु
	u32 reg;

	reg = sdhci_पढ़ोl(host, SDHCI_TEGRA_AUTO_CAL_CONFIG);
	reg &= ~SDHCI_AUTO_CAL_PDPU_OFFSET_MASK;
	reg |= pdpu;
	sdhci_ग_लिखोl(host, reg, SDHCI_TEGRA_AUTO_CAL_CONFIG);
पूर्ण

अटल पूर्णांक tegra_sdhci_set_padctrl(काष्ठा sdhci_host *host, पूर्णांक voltage,
				   bool state_drvupdn)
अणु
	काष्ठा sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	काष्ठा sdhci_tegra *tegra_host = sdhci_pltfm_priv(pltfm_host);
	काष्ठा sdhci_tegra_स्वतःcal_offsets *offsets =
						&tegra_host->स्वतःcal_offsets;
	काष्ठा pinctrl_state *pinctrl_drvupdn = शून्य;
	पूर्णांक ret = 0;
	u8 drvup = 0, drvdn = 0;
	u32 reg;

	अगर (!state_drvupdn) अणु
		/* PADS Drive Strength */
		अगर (voltage == MMC_SIGNAL_VOLTAGE_180) अणु
			अगर (tegra_host->pinctrl_state_1v8_drv) अणु
				pinctrl_drvupdn =
					tegra_host->pinctrl_state_1v8_drv;
			पूर्ण अन्यथा अणु
				drvup = offsets->pull_up_1v8_समयout;
				drvdn = offsets->pull_करोwn_1v8_समयout;
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (tegra_host->pinctrl_state_3v3_drv) अणु
				pinctrl_drvupdn =
					tegra_host->pinctrl_state_3v3_drv;
			पूर्ण अन्यथा अणु
				drvup = offsets->pull_up_3v3_समयout;
				drvdn = offsets->pull_करोwn_3v3_समयout;
			पूर्ण
		पूर्ण

		अगर (pinctrl_drvupdn != शून्य) अणु
			ret = pinctrl_select_state(tegra_host->pinctrl_sdmmc,
							pinctrl_drvupdn);
			अगर (ret < 0)
				dev_err(mmc_dev(host->mmc),
					"failed pads drvupdn, ret: %d\n", ret);
		पूर्ण अन्यथा अगर ((drvup) || (drvdn)) अणु
			reg = sdhci_पढ़ोl(host,
					SDHCI_TEGRA_SDMEM_COMP_PADCTRL);
			reg &= ~SDHCI_COMP_PADCTRL_DRVUPDN_OFFSET_MASK;
			reg |= (drvup << 20) | (drvdn << 12);
			sdhci_ग_लिखोl(host, reg,
					SDHCI_TEGRA_SDMEM_COMP_PADCTRL);
		पूर्ण

	पूर्ण अन्यथा अणु
		/* Dual Voltage PADS Voltage selection */
		अगर (!tegra_host->pad_control_available)
			वापस 0;

		अगर (voltage == MMC_SIGNAL_VOLTAGE_180) अणु
			ret = pinctrl_select_state(tegra_host->pinctrl_sdmmc,
						tegra_host->pinctrl_state_1v8);
			अगर (ret < 0)
				dev_err(mmc_dev(host->mmc),
					"setting 1.8V failed, ret: %d\n", ret);
		पूर्ण अन्यथा अणु
			ret = pinctrl_select_state(tegra_host->pinctrl_sdmmc,
						tegra_host->pinctrl_state_3v3);
			अगर (ret < 0)
				dev_err(mmc_dev(host->mmc),
					"setting 3.3V failed, ret: %d\n", ret);
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम tegra_sdhci_pad_स्वतःcalib(काष्ठा sdhci_host *host)
अणु
	काष्ठा sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	काष्ठा sdhci_tegra *tegra_host = sdhci_pltfm_priv(pltfm_host);
	काष्ठा sdhci_tegra_स्वतःcal_offsets offsets =
			tegra_host->स्वतःcal_offsets;
	काष्ठा mmc_ios *ios = &host->mmc->ios;
	bool card_clk_enabled;
	u16 pdpu;
	u32 reg;
	पूर्णांक ret;

	चयन (ios->timing) अणु
	हाल MMC_TIMING_UHS_SDR104:
		pdpu = offsets.pull_करोwn_sdr104 << 8 | offsets.pull_up_sdr104;
		अवरोध;
	हाल MMC_TIMING_MMC_HS400:
		pdpu = offsets.pull_करोwn_hs400 << 8 | offsets.pull_up_hs400;
		अवरोध;
	शेष:
		अगर (ios->संकेत_voltage == MMC_SIGNAL_VOLTAGE_180)
			pdpu = offsets.pull_करोwn_1v8 << 8 | offsets.pull_up_1v8;
		अन्यथा
			pdpu = offsets.pull_करोwn_3v3 << 8 | offsets.pull_up_3v3;
	पूर्ण

	/* Set initial offset beक्रमe स्वतः-calibration */
	tegra_sdhci_set_pad_स्वतःcal_offset(host, pdpu);

	card_clk_enabled = tegra_sdhci_configure_card_clk(host, false);

	tegra_sdhci_configure_cal_pad(host, true);

	reg = sdhci_पढ़ोl(host, SDHCI_TEGRA_AUTO_CAL_CONFIG);
	reg |= SDHCI_AUTO_CAL_ENABLE | SDHCI_AUTO_CAL_START;
	sdhci_ग_लिखोl(host, reg, SDHCI_TEGRA_AUTO_CAL_CONFIG);

	usleep_range(1, 2);
	/* 10 ms समयout */
	ret = पढ़ोl_poll_समयout(host->ioaddr + SDHCI_TEGRA_AUTO_CAL_STATUS,
				 reg, !(reg & SDHCI_TEGRA_AUTO_CAL_ACTIVE),
				 1000, 10000);

	tegra_sdhci_configure_cal_pad(host, false);

	tegra_sdhci_configure_card_clk(host, card_clk_enabled);

	अगर (ret) अणु
		dev_err(mmc_dev(host->mmc), "Pad autocal timed out\n");

		/* Disable स्वतःmatic cal and use fixed Drive Strengths */
		reg = sdhci_पढ़ोl(host, SDHCI_TEGRA_AUTO_CAL_CONFIG);
		reg &= ~SDHCI_AUTO_CAL_ENABLE;
		sdhci_ग_लिखोl(host, reg, SDHCI_TEGRA_AUTO_CAL_CONFIG);

		ret = tegra_sdhci_set_padctrl(host, ios->संकेत_voltage, false);
		अगर (ret < 0)
			dev_err(mmc_dev(host->mmc),
				"Setting drive strengths failed: %d\n", ret);
	पूर्ण
पूर्ण

अटल व्योम tegra_sdhci_parse_pad_स्वतःcal_dt(काष्ठा sdhci_host *host)
अणु
	काष्ठा sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	काष्ठा sdhci_tegra *tegra_host = sdhci_pltfm_priv(pltfm_host);
	काष्ठा sdhci_tegra_स्वतःcal_offsets *स्वतःcal =
			&tegra_host->स्वतःcal_offsets;
	पूर्णांक err;

	err = device_property_पढ़ो_u32(mmc_dev(host->mmc),
			"nvidia,pad-autocal-pull-up-offset-3v3",
			&स्वतःcal->pull_up_3v3);
	अगर (err)
		स्वतःcal->pull_up_3v3 = 0;

	err = device_property_पढ़ो_u32(mmc_dev(host->mmc),
			"nvidia,pad-autocal-pull-down-offset-3v3",
			&स्वतःcal->pull_करोwn_3v3);
	अगर (err)
		स्वतःcal->pull_करोwn_3v3 = 0;

	err = device_property_पढ़ो_u32(mmc_dev(host->mmc),
			"nvidia,pad-autocal-pull-up-offset-1v8",
			&स्वतःcal->pull_up_1v8);
	अगर (err)
		स्वतःcal->pull_up_1v8 = 0;

	err = device_property_पढ़ो_u32(mmc_dev(host->mmc),
			"nvidia,pad-autocal-pull-down-offset-1v8",
			&स्वतःcal->pull_करोwn_1v8);
	अगर (err)
		स्वतःcal->pull_करोwn_1v8 = 0;

	err = device_property_पढ़ो_u32(mmc_dev(host->mmc),
			"nvidia,pad-autocal-pull-up-offset-sdr104",
			&स्वतःcal->pull_up_sdr104);
	अगर (err)
		स्वतःcal->pull_up_sdr104 = स्वतःcal->pull_up_1v8;

	err = device_property_पढ़ो_u32(mmc_dev(host->mmc),
			"nvidia,pad-autocal-pull-down-offset-sdr104",
			&स्वतःcal->pull_करोwn_sdr104);
	अगर (err)
		स्वतःcal->pull_करोwn_sdr104 = स्वतःcal->pull_करोwn_1v8;

	err = device_property_पढ़ो_u32(mmc_dev(host->mmc),
			"nvidia,pad-autocal-pull-up-offset-hs400",
			&स्वतःcal->pull_up_hs400);
	अगर (err)
		स्वतःcal->pull_up_hs400 = स्वतःcal->pull_up_1v8;

	err = device_property_पढ़ो_u32(mmc_dev(host->mmc),
			"nvidia,pad-autocal-pull-down-offset-hs400",
			&स्वतःcal->pull_करोwn_hs400);
	अगर (err)
		स्वतःcal->pull_करोwn_hs400 = स्वतःcal->pull_करोwn_1v8;

	/*
	 * Dअगरferent fail-safe drive strength values based on the संकेतing
	 * voltage are applicable क्रम SoCs supporting 3V3 and 1V8 pad controls.
	 * So, aव्योम पढ़ोing below device tree properties क्रम SoCs that करोn't
	 * have NVQUIRK_NEEDS_PAD_CONTROL.
	 */
	अगर (!(tegra_host->soc_data->nvquirks & NVQUIRK_NEEDS_PAD_CONTROL))
		वापस;

	err = device_property_पढ़ो_u32(mmc_dev(host->mmc),
			"nvidia,pad-autocal-pull-up-offset-3v3-timeout",
			&स्वतःcal->pull_up_3v3_समयout);
	अगर (err) अणु
		अगर (!IS_ERR(tegra_host->pinctrl_state_3v3) &&
			(tegra_host->pinctrl_state_3v3_drv == शून्य))
			pr_warn("%s: Missing autocal timeout 3v3-pad drvs\n",
				mmc_hostname(host->mmc));
		स्वतःcal->pull_up_3v3_समयout = 0;
	पूर्ण

	err = device_property_पढ़ो_u32(mmc_dev(host->mmc),
			"nvidia,pad-autocal-pull-down-offset-3v3-timeout",
			&स्वतःcal->pull_करोwn_3v3_समयout);
	अगर (err) अणु
		अगर (!IS_ERR(tegra_host->pinctrl_state_3v3) &&
			(tegra_host->pinctrl_state_3v3_drv == शून्य))
			pr_warn("%s: Missing autocal timeout 3v3-pad drvs\n",
				mmc_hostname(host->mmc));
		स्वतःcal->pull_करोwn_3v3_समयout = 0;
	पूर्ण

	err = device_property_पढ़ो_u32(mmc_dev(host->mmc),
			"nvidia,pad-autocal-pull-up-offset-1v8-timeout",
			&स्वतःcal->pull_up_1v8_समयout);
	अगर (err) अणु
		अगर (!IS_ERR(tegra_host->pinctrl_state_1v8) &&
			(tegra_host->pinctrl_state_1v8_drv == शून्य))
			pr_warn("%s: Missing autocal timeout 1v8-pad drvs\n",
				mmc_hostname(host->mmc));
		स्वतःcal->pull_up_1v8_समयout = 0;
	पूर्ण

	err = device_property_पढ़ो_u32(mmc_dev(host->mmc),
			"nvidia,pad-autocal-pull-down-offset-1v8-timeout",
			&स्वतःcal->pull_करोwn_1v8_समयout);
	अगर (err) अणु
		अगर (!IS_ERR(tegra_host->pinctrl_state_1v8) &&
			(tegra_host->pinctrl_state_1v8_drv == शून्य))
			pr_warn("%s: Missing autocal timeout 1v8-pad drvs\n",
				mmc_hostname(host->mmc));
		स्वतःcal->pull_करोwn_1v8_समयout = 0;
	पूर्ण
पूर्ण

अटल व्योम tegra_sdhci_request(काष्ठा mmc_host *mmc, काष्ठा mmc_request *mrq)
अणु
	काष्ठा sdhci_host *host = mmc_priv(mmc);
	काष्ठा sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	काष्ठा sdhci_tegra *tegra_host = sdhci_pltfm_priv(pltfm_host);
	kसमय_प्रकार since_calib = kसमय_sub(kसमय_get(), tegra_host->last_calib);

	/* 100 ms calibration पूर्णांकerval is specअगरied in the TRM */
	अगर (kसमय_प्रकारo_ms(since_calib) > 100) अणु
		tegra_sdhci_pad_स्वतःcalib(host);
		tegra_host->last_calib = kसमय_get();
	पूर्ण

	sdhci_request(mmc, mrq);
पूर्ण

अटल व्योम tegra_sdhci_parse_tap_and_trim(काष्ठा sdhci_host *host)
अणु
	काष्ठा sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	काष्ठा sdhci_tegra *tegra_host = sdhci_pltfm_priv(pltfm_host);
	पूर्णांक err;

	err = device_property_पढ़ो_u32(mmc_dev(host->mmc), "nvidia,default-tap",
				       &tegra_host->शेष_tap);
	अगर (err)
		tegra_host->शेष_tap = 0;

	err = device_property_पढ़ो_u32(mmc_dev(host->mmc), "nvidia,default-trim",
				       &tegra_host->शेष_trim);
	अगर (err)
		tegra_host->शेष_trim = 0;

	err = device_property_पढ़ो_u32(mmc_dev(host->mmc), "nvidia,dqs-trim",
				       &tegra_host->dqs_trim);
	अगर (err)
		tegra_host->dqs_trim = 0x11;
पूर्ण

अटल व्योम tegra_sdhci_parse_dt(काष्ठा sdhci_host *host)
अणु
	काष्ठा sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	काष्ठा sdhci_tegra *tegra_host = sdhci_pltfm_priv(pltfm_host);

	अगर (device_property_पढ़ो_bool(mmc_dev(host->mmc), "supports-cqe"))
		tegra_host->enable_hwcq = true;
	अन्यथा
		tegra_host->enable_hwcq = false;

	tegra_sdhci_parse_pad_स्वतःcal_dt(host);
	tegra_sdhci_parse_tap_and_trim(host);
पूर्ण

अटल व्योम tegra_sdhci_set_घड़ी(काष्ठा sdhci_host *host, अचिन्हित पूर्णांक घड़ी)
अणु
	काष्ठा sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	काष्ठा sdhci_tegra *tegra_host = sdhci_pltfm_priv(pltfm_host);
	अचिन्हित दीर्घ host_clk;

	अगर (!घड़ी)
		वापस sdhci_set_घड़ी(host, घड़ी);

	/*
	 * In DDR50/52 modes the Tegra SDHCI controllers require the SDHCI
	 * भागider to be configured to भागided the host घड़ी by two. The SDHCI
	 * घड़ी भागider is calculated as part of sdhci_set_घड़ी() by
	 * sdhci_calc_clk(). The भागider is calculated from host->max_clk and
	 * the requested घड़ी rate.
	 *
	 * By setting the host->max_clk to घड़ी * 2 the भागider calculation
	 * will always result in the correct value क्रम DDR50/52 modes,
	 * regardless of घड़ी rate rounding, which may happen अगर the value
	 * from clk_get_rate() is used.
	 */
	host_clk = tegra_host->ddr_संकेतing ? घड़ी * 2 : घड़ी;
	clk_set_rate(pltfm_host->clk, host_clk);
	tegra_host->curr_clk_rate = host_clk;
	अगर (tegra_host->ddr_संकेतing)
		host->max_clk = host_clk;
	अन्यथा
		host->max_clk = clk_get_rate(pltfm_host->clk);

	sdhci_set_घड़ी(host, घड़ी);

	अगर (tegra_host->pad_calib_required) अणु
		tegra_sdhci_pad_स्वतःcalib(host);
		tegra_host->pad_calib_required = false;
	पूर्ण
पूर्ण

अटल अचिन्हित पूर्णांक tegra_sdhci_get_max_घड़ी(काष्ठा sdhci_host *host)
अणु
	काष्ठा sdhci_pltfm_host *pltfm_host = sdhci_priv(host);

	वापस clk_round_rate(pltfm_host->clk, अच_पूर्णांक_उच्च);
पूर्ण

अटल व्योम tegra_sdhci_set_dqs_trim(काष्ठा sdhci_host *host, u8 trim)
अणु
	u32 val;

	val = sdhci_पढ़ोl(host, SDHCI_TEGRA_VENDOR_CAP_OVERRIDES);
	val &= ~SDHCI_TEGRA_CAP_OVERRIDES_DQS_TRIM_MASK;
	val |= trim << SDHCI_TEGRA_CAP_OVERRIDES_DQS_TRIM_SHIFT;
	sdhci_ग_लिखोl(host, val, SDHCI_TEGRA_VENDOR_CAP_OVERRIDES);
पूर्ण

अटल व्योम tegra_sdhci_hs400_dll_cal(काष्ठा sdhci_host *host)
अणु
	u32 reg;
	पूर्णांक err;

	reg = sdhci_पढ़ोl(host, SDHCI_TEGRA_VENDOR_DLLCAL_CFG);
	reg |= SDHCI_TEGRA_DLLCAL_CALIBRATE;
	sdhci_ग_लिखोl(host, reg, SDHCI_TEGRA_VENDOR_DLLCAL_CFG);

	/* 1 ms sleep, 5 ms समयout */
	err = पढ़ोl_poll_समयout(host->ioaddr + SDHCI_TEGRA_VENDOR_DLLCAL_STA,
				 reg, !(reg & SDHCI_TEGRA_DLLCAL_STA_ACTIVE),
				 1000, 5000);
	अगर (err)
		dev_err(mmc_dev(host->mmc),
			"HS400 delay line calibration timed out\n");
पूर्ण

अटल व्योम tegra_sdhci_tap_correction(काष्ठा sdhci_host *host, u8 thd_up,
				       u8 thd_low, u8 fixed_tap)
अणु
	काष्ठा sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	काष्ठा sdhci_tegra *tegra_host = sdhci_pltfm_priv(pltfm_host);
	u32 val, tun_status;
	u8 word, bit, edge1, tap, winकरोw;
	bool tap_result;
	bool start_fail = false;
	bool start_pass = false;
	bool end_pass = false;
	bool first_fail = false;
	bool first_pass = false;
	u8 start_pass_tap = 0;
	u8 end_pass_tap = 0;
	u8 first_fail_tap = 0;
	u8 first_pass_tap = 0;
	u8 total_tuning_words = host->tuning_loop_count / TUNING_WORD_BIT_SIZE;

	/*
	 * Read स्वतः-tuned results and extract good valid passing winकरोw by
	 * filtering out un-wanted bubble/partial/merged winकरोws.
	 */
	क्रम (word = 0; word < total_tuning_words; word++) अणु
		val = sdhci_पढ़ोl(host, SDHCI_VNDR_TUN_CTRL0_0);
		val &= ~SDHCI_VNDR_TUN_CTRL0_TUN_WORD_SEL_MASK;
		val |= word;
		sdhci_ग_लिखोl(host, val, SDHCI_VNDR_TUN_CTRL0_0);
		tun_status = sdhci_पढ़ोl(host, SDHCI_TEGRA_VNDR_TUN_STATUS0);
		bit = 0;
		जबतक (bit < TUNING_WORD_BIT_SIZE) अणु
			tap = word * TUNING_WORD_BIT_SIZE + bit;
			tap_result = tun_status & (1 << bit);
			अगर (!tap_result && !start_fail) अणु
				start_fail = true;
				अगर (!first_fail) अणु
					first_fail_tap = tap;
					first_fail = true;
				पूर्ण

			पूर्ण अन्यथा अगर (tap_result && start_fail && !start_pass) अणु
				start_pass_tap = tap;
				start_pass = true;
				अगर (!first_pass) अणु
					first_pass_tap = tap;
					first_pass = true;
				पूर्ण

			पूर्ण अन्यथा अगर (!tap_result && start_fail && start_pass &&
				   !end_pass) अणु
				end_pass_tap = tap - 1;
				end_pass = true;
			पूर्ण अन्यथा अगर (tap_result && start_pass && start_fail &&
				   end_pass) अणु
				winकरोw = end_pass_tap - start_pass_tap;
				/* discard merged winकरोw and bubble winकरोw */
				अगर (winकरोw >= thd_up || winकरोw < thd_low) अणु
					start_pass_tap = tap;
					end_pass = false;
				पूर्ण अन्यथा अणु
					/* set tap at middle of valid winकरोw */
					tap = start_pass_tap + winकरोw / 2;
					tegra_host->tuned_tap_delay = tap;
					वापस;
				पूर्ण
			पूर्ण

			bit++;
		पूर्ण
	पूर्ण

	अगर (!first_fail) अणु
		WARN(1, "no edge detected, continue with hw tuned delay.\n");
	पूर्ण अन्यथा अगर (first_pass) अणु
		/* set tap location at fixed tap relative to the first edge */
		edge1 = first_fail_tap + (first_pass_tap - first_fail_tap) / 2;
		अगर (edge1 - 1 > fixed_tap)
			tegra_host->tuned_tap_delay = edge1 - fixed_tap;
		अन्यथा
			tegra_host->tuned_tap_delay = edge1 + fixed_tap;
	पूर्ण
पूर्ण

अटल व्योम tegra_sdhci_post_tuning(काष्ठा sdhci_host *host)
अणु
	काष्ठा sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	काष्ठा sdhci_tegra *tegra_host = sdhci_pltfm_priv(pltfm_host);
	स्थिर काष्ठा sdhci_tegra_soc_data *soc_data = tegra_host->soc_data;
	u32 avg_tap_dly, val, min_tap_dly, max_tap_dly;
	u8 fixed_tap, start_tap, end_tap, winकरोw_width;
	u8 thdupper, thdlower;
	u8 num_iter;
	u32 clk_rate_mhz, period_ps, bestहाल, worstहाल;

	/* retain HW tuned tap to use inहाल अगर no correction is needed */
	val = sdhci_पढ़ोl(host, SDHCI_TEGRA_VENDOR_CLOCK_CTRL);
	tegra_host->tuned_tap_delay = (val & SDHCI_CLOCK_CTRL_TAP_MASK) >>
				      SDHCI_CLOCK_CTRL_TAP_SHIFT;
	अगर (soc_data->min_tap_delay && soc_data->max_tap_delay) अणु
		min_tap_dly = soc_data->min_tap_delay;
		max_tap_dly = soc_data->max_tap_delay;
		clk_rate_mhz = tegra_host->curr_clk_rate / USEC_PER_SEC;
		period_ps = USEC_PER_SEC / clk_rate_mhz;
		bestहाल = period_ps / min_tap_dly;
		worstहाल = period_ps / max_tap_dly;
		/*
		 * Upper and Lower bound thresholds used to detect merged and
		 * bubble winकरोws
		 */
		thdupper = (2 * worstहाल + bestहाल) / 2;
		thdlower = worstहाल / 4;
		/*
		 * fixed tap is used when HW tuning result contains single edge
		 * and tap is set at fixed tap delay relative to the first edge
		 */
		avg_tap_dly = (period_ps * 2) / (min_tap_dly + max_tap_dly);
		fixed_tap = avg_tap_dly / 2;

		val = sdhci_पढ़ोl(host, SDHCI_TEGRA_VNDR_TUN_STATUS1);
		start_tap = val & SDHCI_TEGRA_VNDR_TUN_STATUS1_TAP_MASK;
		end_tap = (val >> SDHCI_TEGRA_VNDR_TUN_STATUS1_END_TAP_SHIFT) &
			  SDHCI_TEGRA_VNDR_TUN_STATUS1_TAP_MASK;
		winकरोw_width = end_tap - start_tap;
		num_iter = host->tuning_loop_count;
		/*
		 * partial winकरोw includes edges of the tuning range.
		 * merged winकरोw includes more taps so winकरोw width is higher
		 * than upper threshold.
		 */
		अगर (start_tap == 0 || (end_tap == (num_iter - 1)) ||
		    (end_tap == num_iter - 2) || winकरोw_width >= thdupper) अणु
			pr_debug("%s: Apply tuning correction\n",
				 mmc_hostname(host->mmc));
			tegra_sdhci_tap_correction(host, thdupper, thdlower,
						   fixed_tap);
		पूर्ण
	पूर्ण

	tegra_sdhci_set_tap(host, tegra_host->tuned_tap_delay);
पूर्ण

अटल पूर्णांक tegra_sdhci_execute_hw_tuning(काष्ठा mmc_host *mmc, u32 opcode)
अणु
	काष्ठा sdhci_host *host = mmc_priv(mmc);
	पूर्णांक err;

	err = sdhci_execute_tuning(mmc, opcode);
	अगर (!err && !host->tuning_err)
		tegra_sdhci_post_tuning(host);

	वापस err;
पूर्ण

अटल व्योम tegra_sdhci_set_uhs_संकेतing(काष्ठा sdhci_host *host,
					  अचिन्हित timing)
अणु
	काष्ठा sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	काष्ठा sdhci_tegra *tegra_host = sdhci_pltfm_priv(pltfm_host);
	bool set_शेष_tap = false;
	bool set_dqs_trim = false;
	bool करो_hs400_dll_cal = false;
	u8 iter = TRIES_256;
	u32 val;

	tegra_host->ddr_संकेतing = false;
	चयन (timing) अणु
	हाल MMC_TIMING_UHS_SDR50:
		अवरोध;
	हाल MMC_TIMING_UHS_SDR104:
	हाल MMC_TIMING_MMC_HS200:
		/* Don't set शेष tap on tunable modes. */
		iter = TRIES_128;
		अवरोध;
	हाल MMC_TIMING_MMC_HS400:
		set_dqs_trim = true;
		करो_hs400_dll_cal = true;
		iter = TRIES_128;
		अवरोध;
	हाल MMC_TIMING_MMC_DDR52:
	हाल MMC_TIMING_UHS_DDR50:
		tegra_host->ddr_संकेतing = true;
		set_शेष_tap = true;
		अवरोध;
	शेष:
		set_शेष_tap = true;
		अवरोध;
	पूर्ण

	val = sdhci_पढ़ोl(host, SDHCI_VNDR_TUN_CTRL0_0);
	val &= ~(SDHCI_VNDR_TUN_CTRL0_TUN_ITER_MASK |
		 SDHCI_VNDR_TUN_CTRL0_START_TAP_VAL_MASK |
		 SDHCI_VNDR_TUN_CTRL0_MUL_M_MASK);
	val |= (iter << SDHCI_VNDR_TUN_CTRL0_TUN_ITER_SHIFT |
		0 << SDHCI_VNDR_TUN_CTRL0_START_TAP_VAL_SHIFT |
		1 << SDHCI_VNDR_TUN_CTRL0_MUL_M_SHIFT);
	sdhci_ग_लिखोl(host, val, SDHCI_VNDR_TUN_CTRL0_0);
	sdhci_ग_लिखोl(host, 0, SDHCI_TEGRA_VNDR_TUN_CTRL1_0);

	host->tuning_loop_count = (iter == TRIES_128) ? 128 : 256;

	sdhci_set_uhs_संकेतing(host, timing);

	tegra_sdhci_pad_स्वतःcalib(host);

	अगर (tegra_host->tuned_tap_delay && !set_शेष_tap)
		tegra_sdhci_set_tap(host, tegra_host->tuned_tap_delay);
	अन्यथा
		tegra_sdhci_set_tap(host, tegra_host->शेष_tap);

	अगर (set_dqs_trim)
		tegra_sdhci_set_dqs_trim(host, tegra_host->dqs_trim);

	अगर (करो_hs400_dll_cal)
		tegra_sdhci_hs400_dll_cal(host);
पूर्ण

अटल पूर्णांक tegra_sdhci_execute_tuning(काष्ठा sdhci_host *host, u32 opcode)
अणु
	अचिन्हित पूर्णांक min, max;

	/*
	 * Start search क्रम minimum tap value at 10, as smaller values are
	 * may wrongly be reported as working but fail at higher speeds,
	 * according to the TRM.
	 */
	min = 10;
	जबतक (min < 255) अणु
		tegra_sdhci_set_tap(host, min);
		अगर (!mmc_send_tuning(host->mmc, opcode, शून्य))
			अवरोध;
		min++;
	पूर्ण

	/* Find the maximum tap value that still passes. */
	max = min + 1;
	जबतक (max < 255) अणु
		tegra_sdhci_set_tap(host, max);
		अगर (mmc_send_tuning(host->mmc, opcode, शून्य)) अणु
			max--;
			अवरोध;
		पूर्ण
		max++;
	पूर्ण

	/* The TRM states the ideal tap value is at 75% in the passing range. */
	tegra_sdhci_set_tap(host, min + ((max - min) * 3 / 4));

	वापस mmc_send_tuning(host->mmc, opcode, शून्य);
पूर्ण

अटल पूर्णांक sdhci_tegra_start_संकेत_voltage_चयन(काष्ठा mmc_host *mmc,
						   काष्ठा mmc_ios *ios)
अणु
	काष्ठा sdhci_host *host = mmc_priv(mmc);
	काष्ठा sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	काष्ठा sdhci_tegra *tegra_host = sdhci_pltfm_priv(pltfm_host);
	पूर्णांक ret = 0;

	अगर (ios->संकेत_voltage == MMC_SIGNAL_VOLTAGE_330) अणु
		ret = tegra_sdhci_set_padctrl(host, ios->संकेत_voltage, true);
		अगर (ret < 0)
			वापस ret;
		ret = sdhci_start_संकेत_voltage_चयन(mmc, ios);
	पूर्ण अन्यथा अगर (ios->संकेत_voltage == MMC_SIGNAL_VOLTAGE_180) अणु
		ret = sdhci_start_संकेत_voltage_चयन(mmc, ios);
		अगर (ret < 0)
			वापस ret;
		ret = tegra_sdhci_set_padctrl(host, ios->संकेत_voltage, true);
	पूर्ण

	अगर (tegra_host->pad_calib_required)
		tegra_sdhci_pad_स्वतःcalib(host);

	वापस ret;
पूर्ण

अटल पूर्णांक tegra_sdhci_init_pinctrl_info(काष्ठा device *dev,
					 काष्ठा sdhci_tegra *tegra_host)
अणु
	tegra_host->pinctrl_sdmmc = devm_pinctrl_get(dev);
	अगर (IS_ERR(tegra_host->pinctrl_sdmmc)) अणु
		dev_dbg(dev, "No pinctrl info, err: %ld\n",
			PTR_ERR(tegra_host->pinctrl_sdmmc));
		वापस -1;
	पूर्ण

	tegra_host->pinctrl_state_1v8_drv = pinctrl_lookup_state(
				tegra_host->pinctrl_sdmmc, "sdmmc-1v8-drv");
	अगर (IS_ERR(tegra_host->pinctrl_state_1v8_drv)) अणु
		अगर (PTR_ERR(tegra_host->pinctrl_state_1v8_drv) == -ENODEV)
			tegra_host->pinctrl_state_1v8_drv = शून्य;
	पूर्ण

	tegra_host->pinctrl_state_3v3_drv = pinctrl_lookup_state(
				tegra_host->pinctrl_sdmmc, "sdmmc-3v3-drv");
	अगर (IS_ERR(tegra_host->pinctrl_state_3v3_drv)) अणु
		अगर (PTR_ERR(tegra_host->pinctrl_state_3v3_drv) == -ENODEV)
			tegra_host->pinctrl_state_3v3_drv = शून्य;
	पूर्ण

	tegra_host->pinctrl_state_3v3 =
		pinctrl_lookup_state(tegra_host->pinctrl_sdmmc, "sdmmc-3v3");
	अगर (IS_ERR(tegra_host->pinctrl_state_3v3)) अणु
		dev_warn(dev, "Missing 3.3V pad state, err: %ld\n",
			 PTR_ERR(tegra_host->pinctrl_state_3v3));
		वापस -1;
	पूर्ण

	tegra_host->pinctrl_state_1v8 =
		pinctrl_lookup_state(tegra_host->pinctrl_sdmmc, "sdmmc-1v8");
	अगर (IS_ERR(tegra_host->pinctrl_state_1v8)) अणु
		dev_warn(dev, "Missing 1.8V pad state, err: %ld\n",
			 PTR_ERR(tegra_host->pinctrl_state_1v8));
		वापस -1;
	पूर्ण

	tegra_host->pad_control_available = true;

	वापस 0;
पूर्ण

अटल व्योम tegra_sdhci_voltage_चयन(काष्ठा sdhci_host *host)
अणु
	काष्ठा sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	काष्ठा sdhci_tegra *tegra_host = sdhci_pltfm_priv(pltfm_host);
	स्थिर काष्ठा sdhci_tegra_soc_data *soc_data = tegra_host->soc_data;

	अगर (soc_data->nvquirks & NVQUIRK_HAS_PADCALIB)
		tegra_host->pad_calib_required = true;
पूर्ण

अटल व्योम tegra_cqhci_ग_लिखोl(काष्ठा cqhci_host *cq_host, u32 val, पूर्णांक reg)
अणु
	काष्ठा mmc_host *mmc = cq_host->mmc;
	काष्ठा sdhci_host *host = mmc_priv(mmc);
	u8 ctrl;
	kसमय_प्रकार समयout;
	bool समयd_out;

	/*
	 * During CQE resume/unhalt, CQHCI driver unhalts CQE prior to
	 * cqhci_host_ops enable where SDHCI DMA and BLOCK_SIZE रेजिस्टरs need
	 * to be re-configured.
	 * Tegra CQHCI/SDHCI prevents ग_लिखो access to block size रेजिस्टर when
	 * CQE is unhalted. So handling CQE resume sequence here to configure
	 * SDHCI block रेजिस्टरs prior to निकासing CQE halt state.
	 */
	अगर (reg == CQHCI_CTL && !(val & CQHCI_HALT) &&
	    cqhci_पढ़ोl(cq_host, CQHCI_CTL) & CQHCI_HALT) अणु
		sdhci_ग_लिखोw(host, SDHCI_TEGRA_CQE_TRNS_MODE, SDHCI_TRANSFER_MODE);
		sdhci_cqe_enable(mmc);
		ग_लिखोl(val, cq_host->mmio + reg);
		समयout = kसमय_add_us(kसमय_get(), 50);
		जबतक (1) अणु
			समयd_out = kसमय_compare(kसमय_get(), समयout) > 0;
			ctrl = cqhci_पढ़ोl(cq_host, CQHCI_CTL);
			अगर (!(ctrl & CQHCI_HALT) || समयd_out)
				अवरोध;
		पूर्ण
		/*
		 * CQE usually resumes very quick, but inहाल अगर Tegra CQE
		 * करोesn't resume retry unhalt.
		 */
		अगर (समयd_out)
			ग_लिखोl(val, cq_host->mmio + reg);
	पूर्ण अन्यथा अणु
		ग_लिखोl(val, cq_host->mmio + reg);
	पूर्ण
पूर्ण

अटल व्योम sdhci_tegra_update_dcmd_desc(काष्ठा mmc_host *mmc,
					 काष्ठा mmc_request *mrq, u64 *data)
अणु
	काष्ठा sdhci_pltfm_host *pltfm_host = sdhci_priv(mmc_priv(mmc));
	काष्ठा sdhci_tegra *tegra_host = sdhci_pltfm_priv(pltfm_host);
	स्थिर काष्ठा sdhci_tegra_soc_data *soc_data = tegra_host->soc_data;

	अगर (soc_data->nvquirks & NVQUIRK_CQHCI_DCMD_R1B_CMD_TIMING &&
	    mrq->cmd->flags & MMC_RSP_R1B)
		*data |= CQHCI_CMD_TIMING(1);
पूर्ण

अटल व्योम sdhci_tegra_cqe_enable(काष्ठा mmc_host *mmc)
अणु
	काष्ठा cqhci_host *cq_host = mmc->cqe_निजी;
	काष्ठा sdhci_host *host = mmc_priv(mmc);
	u32 val;

	/*
	 * Tegra CQHCI/SDMMC design prevents ग_लिखो access to sdhci block size
	 * रेजिस्टर when CQE is enabled and unhalted.
	 * CQHCI driver enables CQE prior to activation, so disable CQE beक्रमe
	 * programming block size in sdhci controller and enable it back.
	 */
	अगर (!cq_host->activated) अणु
		val = cqhci_पढ़ोl(cq_host, CQHCI_CFG);
		अगर (val & CQHCI_ENABLE)
			cqhci_ग_लिखोl(cq_host, (val & ~CQHCI_ENABLE),
				     CQHCI_CFG);
		sdhci_ग_लिखोw(host, SDHCI_TEGRA_CQE_TRNS_MODE, SDHCI_TRANSFER_MODE);
		sdhci_cqe_enable(mmc);
		अगर (val & CQHCI_ENABLE)
			cqhci_ग_लिखोl(cq_host, val, CQHCI_CFG);
	पूर्ण

	/*
	 * CMD CRC errors are seen someबार with some eMMC devices when status
	 * command is sent during transfer of last data block which is the
	 * शेष हाल as send status command block counter (CBC) is 1.
	 * Recommended fix to set CBC to 0 allowing send status command only
	 * when data lines are idle.
	 */
	val = cqhci_पढ़ोl(cq_host, CQHCI_SSC1);
	val &= ~CQHCI_SSC1_CBC_MASK;
	cqhci_ग_लिखोl(cq_host, val, CQHCI_SSC1);
पूर्ण

अटल व्योम sdhci_tegra_dumpregs(काष्ठा mmc_host *mmc)
अणु
	sdhci_dumpregs(mmc_priv(mmc));
पूर्ण

अटल u32 sdhci_tegra_cqhci_irq(काष्ठा sdhci_host *host, u32 पूर्णांकmask)
अणु
	पूर्णांक cmd_error = 0;
	पूर्णांक data_error = 0;

	अगर (!sdhci_cqe_irq(host, पूर्णांकmask, &cmd_error, &data_error))
		वापस पूर्णांकmask;

	cqhci_irq(host->mmc, पूर्णांकmask, cmd_error, data_error);

	वापस 0;
पूर्ण

अटल व्योम tegra_sdhci_set_समयout(काष्ठा sdhci_host *host,
				    काष्ठा mmc_command *cmd)
अणु
	u32 val;

	/*
	 * HW busy detection समयout is based on programmed data समयout
	 * counter and maximum supported समयout is 11s which may not be
	 * enough क्रम दीर्घ operations like cache flush, sleep awake, erase.
	 *
	 * ERASE_TIMEOUT_LIMIT bit of VENDOR_MISC_CTRL रेजिस्टर allows
	 * host controller to रुको क्रम busy state until the card is busy
	 * without HW समयout.
	 *
	 * So, use infinite busy रुको mode क्रम operations that may take
	 * more than maximum HW busy समयout of 11s otherwise use finite
	 * busy रुको mode.
	 */
	val = sdhci_पढ़ोl(host, SDHCI_TEGRA_VENDOR_MISC_CTRL);
	अगर (cmd && cmd->busy_समयout >= 11 * MSEC_PER_SEC)
		val |= SDHCI_MISC_CTRL_ERASE_TIMEOUT_LIMIT;
	अन्यथा
		val &= ~SDHCI_MISC_CTRL_ERASE_TIMEOUT_LIMIT;
	sdhci_ग_लिखोl(host, val, SDHCI_TEGRA_VENDOR_MISC_CTRL);

	__sdhci_set_समयout(host, cmd);
पूर्ण

अटल व्योम sdhci_tegra_cqe_pre_enable(काष्ठा mmc_host *mmc)
अणु
	काष्ठा cqhci_host *cq_host = mmc->cqe_निजी;
	u32 reg;

	reg = cqhci_पढ़ोl(cq_host, CQHCI_CFG);
	reg |= CQHCI_ENABLE;
	cqhci_ग_लिखोl(cq_host, reg, CQHCI_CFG);
पूर्ण

अटल व्योम sdhci_tegra_cqe_post_disable(काष्ठा mmc_host *mmc)
अणु
	काष्ठा cqhci_host *cq_host = mmc->cqe_निजी;
	काष्ठा sdhci_host *host = mmc_priv(mmc);
	u32 reg;

	reg = cqhci_पढ़ोl(cq_host, CQHCI_CFG);
	reg &= ~CQHCI_ENABLE;
	cqhci_ग_लिखोl(cq_host, reg, CQHCI_CFG);
	sdhci_ग_लिखोw(host, 0x0, SDHCI_TRANSFER_MODE);
पूर्ण

अटल स्थिर काष्ठा cqhci_host_ops sdhci_tegra_cqhci_ops = अणु
	.ग_लिखो_l    = tegra_cqhci_ग_लिखोl,
	.enable	= sdhci_tegra_cqe_enable,
	.disable = sdhci_cqe_disable,
	.dumpregs = sdhci_tegra_dumpregs,
	.update_dcmd_desc = sdhci_tegra_update_dcmd_desc,
	.pre_enable = sdhci_tegra_cqe_pre_enable,
	.post_disable = sdhci_tegra_cqe_post_disable,
पूर्ण;

अटल पूर्णांक tegra_sdhci_set_dma_mask(काष्ठा sdhci_host *host)
अणु
	काष्ठा sdhci_pltfm_host *platक्रमm = sdhci_priv(host);
	काष्ठा sdhci_tegra *tegra = sdhci_pltfm_priv(platक्रमm);
	स्थिर काष्ठा sdhci_tegra_soc_data *soc = tegra->soc_data;
	काष्ठा device *dev = mmc_dev(host->mmc);

	अगर (soc->dma_mask)
		वापस dma_set_mask_and_coherent(dev, soc->dma_mask);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा sdhci_ops tegra_sdhci_ops = अणु
	.get_ro     = tegra_sdhci_get_ro,
	.पढ़ो_w     = tegra_sdhci_पढ़ोw,
	.ग_लिखो_l    = tegra_sdhci_ग_लिखोl,
	.set_घड़ी  = tegra_sdhci_set_घड़ी,
	.set_dma_mask = tegra_sdhci_set_dma_mask,
	.set_bus_width = sdhci_set_bus_width,
	.reset      = tegra_sdhci_reset,
	.platक्रमm_execute_tuning = tegra_sdhci_execute_tuning,
	.set_uhs_संकेतing = tegra_sdhci_set_uhs_संकेतing,
	.voltage_चयन = tegra_sdhci_voltage_चयन,
	.get_max_घड़ी = tegra_sdhci_get_max_घड़ी,
पूर्ण;

अटल स्थिर काष्ठा sdhci_pltfm_data sdhci_tegra20_pdata = अणु
	.quirks = SDHCI_QUIRK_BROKEN_TIMEOUT_VAL |
		  SDHCI_QUIRK_SINGLE_POWER_WRITE |
		  SDHCI_QUIRK_NO_HISPD_BIT |
		  SDHCI_QUIRK_BROKEN_ADMA_ZEROLEN_DESC |
		  SDHCI_QUIRK_CAP_CLOCK_BASE_BROKEN,
	.ops  = &tegra_sdhci_ops,
पूर्ण;

अटल स्थिर काष्ठा sdhci_tegra_soc_data soc_data_tegra20 = अणु
	.pdata = &sdhci_tegra20_pdata,
	.dma_mask = DMA_BIT_MASK(32),
	.nvquirks = NVQUIRK_FORCE_SDHCI_SPEC_200 |
		    NVQUIRK_ENABLE_BLOCK_GAP_DET,
पूर्ण;

अटल स्थिर काष्ठा sdhci_pltfm_data sdhci_tegra30_pdata = अणु
	.quirks = SDHCI_QUIRK_BROKEN_TIMEOUT_VAL |
		  SDHCI_QUIRK_DATA_TIMEOUT_USES_SDCLK |
		  SDHCI_QUIRK_SINGLE_POWER_WRITE |
		  SDHCI_QUIRK_NO_HISPD_BIT |
		  SDHCI_QUIRK_BROKEN_ADMA_ZEROLEN_DESC |
		  SDHCI_QUIRK_CAP_CLOCK_BASE_BROKEN,
	.quirks2 = SDHCI_QUIRK2_PRESET_VALUE_BROKEN |
		   SDHCI_QUIRK2_BROKEN_HS200 |
		   /*
		    * Auto-CMD23 leads to "Got command पूर्णांकerrupt 0x00010000 even
		    * though no command operation was in progress."
		    *
		    * The exact reason is unknown, as the same hardware seems
		    * to support Auto CMD23 on a करोwnstream 3.1 kernel.
		    */
		   SDHCI_QUIRK2_ACMD23_BROKEN,
	.ops  = &tegra_sdhci_ops,
पूर्ण;

अटल स्थिर काष्ठा sdhci_tegra_soc_data soc_data_tegra30 = अणु
	.pdata = &sdhci_tegra30_pdata,
	.dma_mask = DMA_BIT_MASK(32),
	.nvquirks = NVQUIRK_ENABLE_SDHCI_SPEC_300 |
		    NVQUIRK_ENABLE_SDR50 |
		    NVQUIRK_ENABLE_SDR104 |
		    NVQUIRK_HAS_PADCALIB,
पूर्ण;

अटल स्थिर काष्ठा sdhci_ops tegra114_sdhci_ops = अणु
	.get_ro     = tegra_sdhci_get_ro,
	.पढ़ो_w     = tegra_sdhci_पढ़ोw,
	.ग_लिखो_w    = tegra_sdhci_ग_लिखोw,
	.ग_लिखो_l    = tegra_sdhci_ग_लिखोl,
	.set_घड़ी  = tegra_sdhci_set_घड़ी,
	.set_dma_mask = tegra_sdhci_set_dma_mask,
	.set_bus_width = sdhci_set_bus_width,
	.reset      = tegra_sdhci_reset,
	.platक्रमm_execute_tuning = tegra_sdhci_execute_tuning,
	.set_uhs_संकेतing = tegra_sdhci_set_uhs_संकेतing,
	.voltage_चयन = tegra_sdhci_voltage_चयन,
	.get_max_घड़ी = tegra_sdhci_get_max_घड़ी,
पूर्ण;

अटल स्थिर काष्ठा sdhci_pltfm_data sdhci_tegra114_pdata = अणु
	.quirks = SDHCI_QUIRK_BROKEN_TIMEOUT_VAL |
		  SDHCI_QUIRK_DATA_TIMEOUT_USES_SDCLK |
		  SDHCI_QUIRK_SINGLE_POWER_WRITE |
		  SDHCI_QUIRK_NO_HISPD_BIT |
		  SDHCI_QUIRK_BROKEN_ADMA_ZEROLEN_DESC |
		  SDHCI_QUIRK_CAP_CLOCK_BASE_BROKEN,
	.quirks2 = SDHCI_QUIRK2_PRESET_VALUE_BROKEN,
	.ops  = &tegra114_sdhci_ops,
पूर्ण;

अटल स्थिर काष्ठा sdhci_tegra_soc_data soc_data_tegra114 = अणु
	.pdata = &sdhci_tegra114_pdata,
	.dma_mask = DMA_BIT_MASK(32),
पूर्ण;

अटल स्थिर काष्ठा sdhci_pltfm_data sdhci_tegra124_pdata = अणु
	.quirks = SDHCI_QUIRK_BROKEN_TIMEOUT_VAL |
		  SDHCI_QUIRK_DATA_TIMEOUT_USES_SDCLK |
		  SDHCI_QUIRK_SINGLE_POWER_WRITE |
		  SDHCI_QUIRK_NO_HISPD_BIT |
		  SDHCI_QUIRK_BROKEN_ADMA_ZEROLEN_DESC |
		  SDHCI_QUIRK_CAP_CLOCK_BASE_BROKEN,
	.quirks2 = SDHCI_QUIRK2_PRESET_VALUE_BROKEN,
	.ops  = &tegra114_sdhci_ops,
पूर्ण;

अटल स्थिर काष्ठा sdhci_tegra_soc_data soc_data_tegra124 = अणु
	.pdata = &sdhci_tegra124_pdata,
	.dma_mask = DMA_BIT_MASK(34),
पूर्ण;

अटल स्थिर काष्ठा sdhci_ops tegra210_sdhci_ops = अणु
	.get_ro     = tegra_sdhci_get_ro,
	.पढ़ो_w     = tegra_sdhci_पढ़ोw,
	.ग_लिखो_w    = tegra210_sdhci_ग_लिखोw,
	.ग_लिखो_l    = tegra_sdhci_ग_लिखोl,
	.set_घड़ी  = tegra_sdhci_set_घड़ी,
	.set_dma_mask = tegra_sdhci_set_dma_mask,
	.set_bus_width = sdhci_set_bus_width,
	.reset      = tegra_sdhci_reset,
	.set_uhs_संकेतing = tegra_sdhci_set_uhs_संकेतing,
	.voltage_चयन = tegra_sdhci_voltage_चयन,
	.get_max_घड़ी = tegra_sdhci_get_max_घड़ी,
	.set_समयout = tegra_sdhci_set_समयout,
पूर्ण;

अटल स्थिर काष्ठा sdhci_pltfm_data sdhci_tegra210_pdata = अणु
	.quirks = SDHCI_QUIRK_BROKEN_TIMEOUT_VAL |
		  SDHCI_QUIRK_SINGLE_POWER_WRITE |
		  SDHCI_QUIRK_NO_HISPD_BIT |
		  SDHCI_QUIRK_BROKEN_ADMA_ZEROLEN_DESC |
		  SDHCI_QUIRK_CAP_CLOCK_BASE_BROKEN,
	.quirks2 = SDHCI_QUIRK2_PRESET_VALUE_BROKEN,
	.ops  = &tegra210_sdhci_ops,
पूर्ण;

अटल स्थिर काष्ठा sdhci_tegra_soc_data soc_data_tegra210 = अणु
	.pdata = &sdhci_tegra210_pdata,
	.dma_mask = DMA_BIT_MASK(34),
	.nvquirks = NVQUIRK_NEEDS_PAD_CONTROL |
		    NVQUIRK_HAS_PADCALIB |
		    NVQUIRK_DIS_CARD_CLK_CONFIG_TAP |
		    NVQUIRK_ENABLE_SDR50 |
		    NVQUIRK_ENABLE_SDR104 |
		    NVQUIRK_HAS_TMCLK,
	.min_tap_delay = 106,
	.max_tap_delay = 185,
पूर्ण;

अटल स्थिर काष्ठा sdhci_ops tegra186_sdhci_ops = अणु
	.get_ro     = tegra_sdhci_get_ro,
	.पढ़ो_w     = tegra_sdhci_पढ़ोw,
	.ग_लिखो_l    = tegra_sdhci_ग_लिखोl,
	.set_घड़ी  = tegra_sdhci_set_घड़ी,
	.set_dma_mask = tegra_sdhci_set_dma_mask,
	.set_bus_width = sdhci_set_bus_width,
	.reset      = tegra_sdhci_reset,
	.set_uhs_संकेतing = tegra_sdhci_set_uhs_संकेतing,
	.voltage_चयन = tegra_sdhci_voltage_चयन,
	.get_max_घड़ी = tegra_sdhci_get_max_घड़ी,
	.irq = sdhci_tegra_cqhci_irq,
	.set_समयout = tegra_sdhci_set_समयout,
पूर्ण;

अटल स्थिर काष्ठा sdhci_pltfm_data sdhci_tegra186_pdata = अणु
	.quirks = SDHCI_QUIRK_BROKEN_TIMEOUT_VAL |
		  SDHCI_QUIRK_SINGLE_POWER_WRITE |
		  SDHCI_QUIRK_NO_HISPD_BIT |
		  SDHCI_QUIRK_BROKEN_ADMA_ZEROLEN_DESC |
		  SDHCI_QUIRK_CAP_CLOCK_BASE_BROKEN,
	.quirks2 = SDHCI_QUIRK2_PRESET_VALUE_BROKEN,
	.ops  = &tegra186_sdhci_ops,
पूर्ण;

अटल स्थिर काष्ठा sdhci_tegra_soc_data soc_data_tegra186 = अणु
	.pdata = &sdhci_tegra186_pdata,
	.dma_mask = DMA_BIT_MASK(40),
	.nvquirks = NVQUIRK_NEEDS_PAD_CONTROL |
		    NVQUIRK_HAS_PADCALIB |
		    NVQUIRK_DIS_CARD_CLK_CONFIG_TAP |
		    NVQUIRK_ENABLE_SDR50 |
		    NVQUIRK_ENABLE_SDR104 |
		    NVQUIRK_HAS_TMCLK |
		    NVQUIRK_CQHCI_DCMD_R1B_CMD_TIMING,
	.min_tap_delay = 84,
	.max_tap_delay = 136,
पूर्ण;

अटल स्थिर काष्ठा sdhci_tegra_soc_data soc_data_tegra194 = अणु
	.pdata = &sdhci_tegra186_pdata,
	.dma_mask = DMA_BIT_MASK(39),
	.nvquirks = NVQUIRK_NEEDS_PAD_CONTROL |
		    NVQUIRK_HAS_PADCALIB |
		    NVQUIRK_DIS_CARD_CLK_CONFIG_TAP |
		    NVQUIRK_ENABLE_SDR50 |
		    NVQUIRK_ENABLE_SDR104 |
		    NVQUIRK_HAS_TMCLK,
	.min_tap_delay = 96,
	.max_tap_delay = 139,
पूर्ण;

अटल स्थिर काष्ठा of_device_id sdhci_tegra_dt_match[] = अणु
	अणु .compatible = "nvidia,tegra194-sdhci", .data = &soc_data_tegra194 पूर्ण,
	अणु .compatible = "nvidia,tegra186-sdhci", .data = &soc_data_tegra186 पूर्ण,
	अणु .compatible = "nvidia,tegra210-sdhci", .data = &soc_data_tegra210 पूर्ण,
	अणु .compatible = "nvidia,tegra124-sdhci", .data = &soc_data_tegra124 पूर्ण,
	अणु .compatible = "nvidia,tegra114-sdhci", .data = &soc_data_tegra114 पूर्ण,
	अणु .compatible = "nvidia,tegra30-sdhci", .data = &soc_data_tegra30 पूर्ण,
	अणु .compatible = "nvidia,tegra20-sdhci", .data = &soc_data_tegra20 पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, sdhci_tegra_dt_match);

अटल पूर्णांक sdhci_tegra_add_host(काष्ठा sdhci_host *host)
अणु
	काष्ठा sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	काष्ठा sdhci_tegra *tegra_host = sdhci_pltfm_priv(pltfm_host);
	काष्ठा cqhci_host *cq_host;
	bool dma64;
	पूर्णांक ret;

	अगर (!tegra_host->enable_hwcq)
		वापस sdhci_add_host(host);

	sdhci_enable_v4_mode(host);

	ret = sdhci_setup_host(host);
	अगर (ret)
		वापस ret;

	host->mmc->caps2 |= MMC_CAP2_CQE | MMC_CAP2_CQE_DCMD;

	cq_host = devm_kzalloc(mmc_dev(host->mmc),
				माप(*cq_host), GFP_KERNEL);
	अगर (!cq_host) अणु
		ret = -ENOMEM;
		जाओ cleanup;
	पूर्ण

	cq_host->mmio = host->ioaddr + SDHCI_TEGRA_CQE_BASE_ADDR;
	cq_host->ops = &sdhci_tegra_cqhci_ops;

	dma64 = host->flags & SDHCI_USE_64_BIT_DMA;
	अगर (dma64)
		cq_host->caps |= CQHCI_TASK_DESC_SZ_128;

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

अटल पूर्णांक sdhci_tegra_probe(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा of_device_id *match;
	स्थिर काष्ठा sdhci_tegra_soc_data *soc_data;
	काष्ठा sdhci_host *host;
	काष्ठा sdhci_pltfm_host *pltfm_host;
	काष्ठा sdhci_tegra *tegra_host;
	काष्ठा clk *clk;
	पूर्णांक rc;

	match = of_match_device(sdhci_tegra_dt_match, &pdev->dev);
	अगर (!match)
		वापस -EINVAL;
	soc_data = match->data;

	host = sdhci_pltfm_init(pdev, soc_data->pdata, माप(*tegra_host));
	अगर (IS_ERR(host))
		वापस PTR_ERR(host);
	pltfm_host = sdhci_priv(host);

	tegra_host = sdhci_pltfm_priv(pltfm_host);
	tegra_host->ddr_संकेतing = false;
	tegra_host->pad_calib_required = false;
	tegra_host->pad_control_available = false;
	tegra_host->soc_data = soc_data;

	अगर (soc_data->nvquirks & NVQUIRK_NEEDS_PAD_CONTROL) अणु
		rc = tegra_sdhci_init_pinctrl_info(&pdev->dev, tegra_host);
		अगर (rc == 0)
			host->mmc_host_ops.start_संकेत_voltage_चयन =
				sdhci_tegra_start_संकेत_voltage_चयन;
	पूर्ण

	/* Hook to periodically rerun pad calibration */
	अगर (soc_data->nvquirks & NVQUIRK_HAS_PADCALIB)
		host->mmc_host_ops.request = tegra_sdhci_request;

	host->mmc_host_ops.hs400_enhanced_strobe =
			tegra_sdhci_hs400_enhanced_strobe;

	अगर (!host->ops->platक्रमm_execute_tuning)
		host->mmc_host_ops.execute_tuning =
				tegra_sdhci_execute_hw_tuning;

	rc = mmc_of_parse(host->mmc);
	अगर (rc)
		जाओ err_parse_dt;

	अगर (tegra_host->soc_data->nvquirks & NVQUIRK_ENABLE_DDR50)
		host->mmc->caps |= MMC_CAP_1_8V_DDR;

	/* HW busy detection is supported, but R1B responses are required. */
	host->mmc->caps |= MMC_CAP_WAIT_WHILE_BUSY | MMC_CAP_NEED_RSP_BUSY;

	tegra_sdhci_parse_dt(host);

	tegra_host->घातer_gpio = devm_gpiod_get_optional(&pdev->dev, "power",
							 GPIOD_OUT_HIGH);
	अगर (IS_ERR(tegra_host->घातer_gpio)) अणु
		rc = PTR_ERR(tegra_host->घातer_gpio);
		जाओ err_घातer_req;
	पूर्ण

	/*
	 * Tegra210 has a separate SDMMC_LEGACY_TM घड़ी used क्रम host
	 * समयout घड़ी and SW can choose TMCLK or SDCLK क्रम hardware
	 * data समयout through the bit USE_TMCLK_FOR_DATA_TIMEOUT of
	 * the रेजिस्टर SDHCI_TEGRA_VENDOR_SYS_SW_CTRL.
	 *
	 * USE_TMCLK_FOR_DATA_TIMEOUT bit शेष is set to 1 and SDMMC uses
	 * 12Mhz TMCLK which is advertised in host capability रेजिस्टर.
	 * With TMCLK of 12Mhz provides maximum data समयout period that can
	 * be achieved is 11s better than using SDCLK क्रम data समयout.
	 *
	 * So, TMCLK is set to 12Mhz and kept enabled all the समय on SoC's
	 * supporting separate TMCLK.
	 */

	अगर (soc_data->nvquirks & NVQUIRK_HAS_TMCLK) अणु
		clk = devm_clk_get(&pdev->dev, "tmclk");
		अगर (IS_ERR(clk)) अणु
			rc = PTR_ERR(clk);
			अगर (rc == -EPROBE_DEFER)
				जाओ err_घातer_req;

			dev_warn(&pdev->dev, "failed to get tmclk: %d\n", rc);
			clk = शून्य;
		पूर्ण

		clk_set_rate(clk, 12000000);
		rc = clk_prepare_enable(clk);
		अगर (rc) अणु
			dev_err(&pdev->dev,
				"failed to enable tmclk: %d\n", rc);
			जाओ err_घातer_req;
		पूर्ण

		tegra_host->पंचांगclk = clk;
	पूर्ण

	clk = devm_clk_get(mmc_dev(host->mmc), शून्य);
	अगर (IS_ERR(clk)) अणु
		rc = dev_err_probe(&pdev->dev, PTR_ERR(clk),
				   "failed to get clock\n");
		जाओ err_clk_get;
	पूर्ण
	clk_prepare_enable(clk);
	pltfm_host->clk = clk;

	tegra_host->rst = devm_reset_control_get_exclusive(&pdev->dev,
							   "sdhci");
	अगर (IS_ERR(tegra_host->rst)) अणु
		rc = PTR_ERR(tegra_host->rst);
		dev_err(&pdev->dev, "failed to get reset control: %d\n", rc);
		जाओ err_rst_get;
	पूर्ण

	rc = reset_control_निश्चित(tegra_host->rst);
	अगर (rc)
		जाओ err_rst_get;

	usleep_range(2000, 4000);

	rc = reset_control_deनिश्चित(tegra_host->rst);
	अगर (rc)
		जाओ err_rst_get;

	usleep_range(2000, 4000);

	rc = sdhci_tegra_add_host(host);
	अगर (rc)
		जाओ err_add_host;

	वापस 0;

err_add_host:
	reset_control_निश्चित(tegra_host->rst);
err_rst_get:
	clk_disable_unprepare(pltfm_host->clk);
err_clk_get:
	clk_disable_unprepare(tegra_host->पंचांगclk);
err_घातer_req:
err_parse_dt:
	sdhci_pltfm_मुक्त(pdev);
	वापस rc;
पूर्ण

अटल पूर्णांक sdhci_tegra_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sdhci_host *host = platक्रमm_get_drvdata(pdev);
	काष्ठा sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	काष्ठा sdhci_tegra *tegra_host = sdhci_pltfm_priv(pltfm_host);

	sdhci_हटाओ_host(host, 0);

	reset_control_निश्चित(tegra_host->rst);
	usleep_range(2000, 4000);
	clk_disable_unprepare(pltfm_host->clk);
	clk_disable_unprepare(tegra_host->पंचांगclk);

	sdhci_pltfm_मुक्त(pdev);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक __maybe_unused sdhci_tegra_suspend(काष्ठा device *dev)
अणु
	काष्ठा sdhci_host *host = dev_get_drvdata(dev);
	काष्ठा sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	पूर्णांक ret;

	अगर (host->mmc->caps2 & MMC_CAP2_CQE) अणु
		ret = cqhci_suspend(host->mmc);
		अगर (ret)
			वापस ret;
	पूर्ण

	ret = sdhci_suspend_host(host);
	अगर (ret) अणु
		cqhci_resume(host->mmc);
		वापस ret;
	पूर्ण

	clk_disable_unprepare(pltfm_host->clk);
	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused sdhci_tegra_resume(काष्ठा device *dev)
अणु
	काष्ठा sdhci_host *host = dev_get_drvdata(dev);
	काष्ठा sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	पूर्णांक ret;

	ret = clk_prepare_enable(pltfm_host->clk);
	अगर (ret)
		वापस ret;

	ret = sdhci_resume_host(host);
	अगर (ret)
		जाओ disable_clk;

	अगर (host->mmc->caps2 & MMC_CAP2_CQE) अणु
		ret = cqhci_resume(host->mmc);
		अगर (ret)
			जाओ suspend_host;
	पूर्ण

	वापस 0;

suspend_host:
	sdhci_suspend_host(host);
disable_clk:
	clk_disable_unprepare(pltfm_host->clk);
	वापस ret;
पूर्ण
#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(sdhci_tegra_dev_pm_ops, sdhci_tegra_suspend,
			 sdhci_tegra_resume);

अटल काष्ठा platक्रमm_driver sdhci_tegra_driver = अणु
	.driver		= अणु
		.name	= "sdhci-tegra",
		.probe_type = PROBE_PREFER_ASYNCHRONOUS,
		.of_match_table = sdhci_tegra_dt_match,
		.pm	= &sdhci_tegra_dev_pm_ops,
	पूर्ण,
	.probe		= sdhci_tegra_probe,
	.हटाओ		= sdhci_tegra_हटाओ,
पूर्ण;

module_platक्रमm_driver(sdhci_tegra_driver);

MODULE_DESCRIPTION("SDHCI driver for Tegra");
MODULE_AUTHOR("Google, Inc.");
MODULE_LICENSE("GPL v2");
