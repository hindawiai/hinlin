<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2013 BayHub Technology Ltd.
 *
 * Authors: Peter Guo <peter.guo@bayhubtech.com>
 *          Adam Lee <adam.lee@canonical.com>
 *          Ernest Zhang <ernest.zhang@bayhubtech.com>
 */

#समावेश <linux/pci.h>
#समावेश <linux/mmc/host.h>
#समावेश <linux/mmc/mmc.h>
#समावेश <linux/delay.h>
#समावेश <linux/iopoll.h>

#समावेश "sdhci.h"
#समावेश "sdhci-pci.h"

/*
 * O2Micro device रेजिस्टरs
 */

#घोषणा O2_SD_MISC_REG5		0x64
#घोषणा O2_SD_LD0_CTRL		0x68
#घोषणा O2_SD_DEV_CTRL		0x88
#घोषणा O2_SD_LOCK_WP		0xD3
#घोषणा O2_SD_TEST_REG		0xD4
#घोषणा O2_SD_FUNC_REG0		0xDC
#घोषणा O2_SD_MULTI_VCC3V	0xEE
#घोषणा O2_SD_CLKREQ		0xEC
#घोषणा O2_SD_CAPS		0xE0
#घोषणा O2_SD_ADMA1		0xE2
#घोषणा O2_SD_ADMA2		0xE7
#घोषणा O2_SD_INF_MOD		0xF1
#घोषणा O2_SD_MISC_CTRL4	0xFC
#घोषणा O2_SD_MISC_CTRL		0x1C0
#घोषणा O2_SD_PWR_FORCE_L0	0x0002
#घोषणा O2_SD_TUNING_CTRL	0x300
#घोषणा O2_SD_PLL_SETTING	0x304
#घोषणा O2_SD_MISC_SETTING	0x308
#घोषणा O2_SD_CLK_SETTING	0x328
#घोषणा O2_SD_CAP_REG2		0x330
#घोषणा O2_SD_CAP_REG0		0x334
#घोषणा O2_SD_UHS1_CAP_SETTING	0x33C
#घोषणा O2_SD_DELAY_CTRL	0x350
#घोषणा O2_SD_UHS2_L1_CTRL	0x35C
#घोषणा O2_SD_FUNC_REG3		0x3E0
#घोषणा O2_SD_FUNC_REG4		0x3E4
#घोषणा O2_SD_LED_ENABLE	BIT(6)
#घोषणा O2_SD_FREG0_LEDOFF	BIT(13)
#घोषणा O2_SD_FREG4_ENABLE_CLK_SET	BIT(22)

#घोषणा O2_SD_VENDOR_SETTING	0x110
#घोषणा O2_SD_VENDOR_SETTING2	0x1C8
#घोषणा O2_SD_HW_TUNING_DISABLE	BIT(4)

#घोषणा O2_PLL_DLL_WDT_CONTROL1	0x1CC
#घोषणा  O2_PLL_FORCE_ACTIVE	BIT(18)
#घोषणा  O2_PLL_LOCK_STATUS	BIT(14)
#घोषणा  O2_PLL_SOFT_RESET	BIT(12)
#घोषणा  O2_DLL_LOCK_STATUS	BIT(11)

#घोषणा O2_SD_DETECT_SETTING 0x324

अटल स्थिर u32 dmdn_table[] = अणु0x2B1C0000,
	0x2C1A0000, 0x371B0000, 0x35100000पूर्ण;
#घोषणा DMDN_SZ ARRAY_SIZE(dmdn_table)

काष्ठा o2_host अणु
	u8 dll_adjust_count;
पूर्ण;

अटल व्योम sdhci_o2_रुको_card_detect_stable(काष्ठा sdhci_host *host)
अणु
	kसमय_प्रकार समयout;
	u32 scratch32;

	/* Wait max 50 ms */
	समयout = kसमय_add_ms(kसमय_get(), 50);
	जबतक (1) अणु
		bool समयकरोut = kसमय_after(kसमय_get(), समयout);

		scratch32 = sdhci_पढ़ोl(host, SDHCI_PRESENT_STATE);
		अगर ((scratch32 & SDHCI_CARD_PRESENT) >> SDHCI_CARD_PRES_SHIFT
		    == (scratch32 & SDHCI_CD_LVL) >> SDHCI_CD_LVL_SHIFT)
			अवरोध;

		अगर (समयकरोut) अणु
			pr_err("%s: Card Detect debounce never finished.\n",
			       mmc_hostname(host->mmc));
			sdhci_dumpregs(host);
			वापस;
		पूर्ण
		udelay(10);
	पूर्ण
पूर्ण

अटल व्योम sdhci_o2_enable_पूर्णांकernal_घड़ी(काष्ठा sdhci_host *host)
अणु
	kसमय_प्रकार समयout;
	u16 scratch;
	u32 scratch32;

	/* PLL software reset */
	scratch32 = sdhci_पढ़ोl(host, O2_PLL_DLL_WDT_CONTROL1);
	scratch32 |= O2_PLL_SOFT_RESET;
	sdhci_ग_लिखोl(host, scratch32, O2_PLL_DLL_WDT_CONTROL1);
	udelay(1);
	scratch32 &= ~(O2_PLL_SOFT_RESET);
	sdhci_ग_लिखोl(host, scratch32, O2_PLL_DLL_WDT_CONTROL1);

	/* PLL क्रमce active */
	scratch32 |= O2_PLL_FORCE_ACTIVE;
	sdhci_ग_लिखोl(host, scratch32, O2_PLL_DLL_WDT_CONTROL1);

	/* Wait max 20 ms */
	समयout = kसमय_add_ms(kसमय_get(), 20);
	जबतक (1) अणु
		bool समयकरोut = kसमय_after(kसमय_get(), समयout);

		scratch = sdhci_पढ़ोw(host, O2_PLL_DLL_WDT_CONTROL1);
		अगर (scratch & O2_PLL_LOCK_STATUS)
			अवरोध;
		अगर (समयकरोut) अणु
			pr_err("%s: Internal clock never stabilised.\n",
			       mmc_hostname(host->mmc));
			sdhci_dumpregs(host);
			जाओ out;
		पूर्ण
		udelay(10);
	पूर्ण

	/* Wait क्रम card detect finish */
	udelay(1);
	sdhci_o2_रुको_card_detect_stable(host);

out:
	/* Cancel PLL क्रमce active */
	scratch32 = sdhci_पढ़ोl(host, O2_PLL_DLL_WDT_CONTROL1);
	scratch32 &= ~O2_PLL_FORCE_ACTIVE;
	sdhci_ग_लिखोl(host, scratch32, O2_PLL_DLL_WDT_CONTROL1);
पूर्ण

अटल पूर्णांक sdhci_o2_get_cd(काष्ठा mmc_host *mmc)
अणु
	काष्ठा sdhci_host *host = mmc_priv(mmc);

	अगर (!(sdhci_पढ़ोw(host, O2_PLL_DLL_WDT_CONTROL1) & O2_PLL_LOCK_STATUS))
		sdhci_o2_enable_पूर्णांकernal_घड़ी(host);

	वापस !!(sdhci_पढ़ोl(host, SDHCI_PRESENT_STATE) & SDHCI_CARD_PRESENT);
पूर्ण

अटल व्योम o2_pci_set_baseclk(काष्ठा sdhci_pci_chip *chip, u32 value)
अणु
	u32 scratch_32;

	pci_पढ़ो_config_dword(chip->pdev,
			      O2_SD_PLL_SETTING, &scratch_32);

	scratch_32 &= 0x0000FFFF;
	scratch_32 |= value;

	pci_ग_लिखो_config_dword(chip->pdev,
			       O2_SD_PLL_SETTING, scratch_32);
पूर्ण

अटल u32 sdhci_o2_pll_dll_wdt_control(काष्ठा sdhci_host *host)
अणु
	वापस sdhci_पढ़ोl(host, O2_PLL_DLL_WDT_CONTROL1);
पूर्ण

/*
 * This function is used to detect dll lock status.
 * Since the dll lock status bit will toggle अक्रमomly
 * with very लघु पूर्णांकerval which needs to be polled
 * as fast as possible. Set sleep_us as 1 microsecond.
 */
अटल पूर्णांक sdhci_o2_रुको_dll_detect_lock(काष्ठा sdhci_host *host)
अणु
	u32	scratch32 = 0;

	वापस पढ़ोx_poll_समयout(sdhci_o2_pll_dll_wdt_control, host,
		scratch32, !(scratch32 & O2_DLL_LOCK_STATUS), 1, 1000000);
पूर्ण

अटल व्योम sdhci_o2_set_tuning_mode(काष्ठा sdhci_host *host)
अणु
	u16 reg;

	/* enable hardware tuning */
	reg = sdhci_पढ़ोw(host, O2_SD_VENDOR_SETTING);
	reg &= ~O2_SD_HW_TUNING_DISABLE;
	sdhci_ग_लिखोw(host, reg, O2_SD_VENDOR_SETTING);
पूर्ण

अटल व्योम __sdhci_o2_execute_tuning(काष्ठा sdhci_host *host, u32 opcode)
अणु
	पूर्णांक i;

	sdhci_send_tuning(host, opcode);

	क्रम (i = 0; i < 150; i++) अणु
		u16 ctrl = sdhci_पढ़ोw(host, SDHCI_HOST_CONTROL2);

		अगर (!(ctrl & SDHCI_CTRL_EXEC_TUNING)) अणु
			अगर (ctrl & SDHCI_CTRL_TUNED_CLK) अणु
				host->tuning_करोne = true;
				वापस;
			पूर्ण
			pr_warn("%s: HW tuning failed !\n",
				mmc_hostname(host->mmc));
			अवरोध;
		पूर्ण

		mdelay(1);
	पूर्ण

	pr_info("%s: Tuning failed, falling back to fixed sampling clock\n",
		mmc_hostname(host->mmc));
	sdhci_reset_tuning(host);
पूर्ण

/*
 * This function is used to fix o2 dll shअगरt issue.
 * It isn't necessary to detect card present beक्रमe recovery.
 * Firstly, it is used by bht emmc card, which is embedded.
 * Second, beक्रमe call recovery card present will be detected
 * outside of the execute tuning function.
 */
अटल पूर्णांक sdhci_o2_dll_recovery(काष्ठा sdhci_host *host)
अणु
	पूर्णांक ret = 0;
	u8 scratch_8 = 0;
	u32 scratch_32 = 0;
	काष्ठा sdhci_pci_slot *slot = sdhci_priv(host);
	काष्ठा sdhci_pci_chip *chip = slot->chip;
	काष्ठा o2_host *o2_host = sdhci_pci_priv(slot);

	/* UnLock WP */
	pci_पढ़ो_config_byte(chip->pdev,
			O2_SD_LOCK_WP, &scratch_8);
	scratch_8 &= 0x7f;
	pci_ग_लिखो_config_byte(chip->pdev, O2_SD_LOCK_WP, scratch_8);
	जबतक (o2_host->dll_adjust_count < DMDN_SZ && !ret) अणु
		/* Disable घड़ी */
		sdhci_ग_लिखोb(host, 0, SDHCI_CLOCK_CONTROL);

		/* PLL software reset */
		scratch_32 = sdhci_पढ़ोl(host, O2_PLL_DLL_WDT_CONTROL1);
		scratch_32 |= O2_PLL_SOFT_RESET;
		sdhci_ग_लिखोl(host, scratch_32, O2_PLL_DLL_WDT_CONTROL1);

		pci_पढ़ो_config_dword(chip->pdev,
					    O2_SD_FUNC_REG4,
					    &scratch_32);
		/* Enable Base Clk setting change */
		scratch_32 |= O2_SD_FREG4_ENABLE_CLK_SET;
		pci_ग_लिखो_config_dword(chip->pdev, O2_SD_FUNC_REG4, scratch_32);
		o2_pci_set_baseclk(chip, dmdn_table[o2_host->dll_adjust_count]);

		/* Enable पूर्णांकernal घड़ी */
		scratch_8 = SDHCI_CLOCK_INT_EN;
		sdhci_ग_लिखोb(host, scratch_8, SDHCI_CLOCK_CONTROL);

		अगर (sdhci_o2_get_cd(host->mmc)) अणु
			/*
			 * need रुको at least 5ms क्रम dll status stable,
			 * after enable पूर्णांकernal घड़ी
			 */
			usleep_range(5000, 6000);
			अगर (sdhci_o2_रुको_dll_detect_lock(host)) अणु
				scratch_8 |= SDHCI_CLOCK_CARD_EN;
				sdhci_ग_लिखोb(host, scratch_8,
					SDHCI_CLOCK_CONTROL);
				ret = 1;
			पूर्ण अन्यथा अणु
				pr_warn("%s: DLL unlocked when dll_adjust_count is %d.\n",
					mmc_hostname(host->mmc),
					o2_host->dll_adjust_count);
			पूर्ण
		पूर्ण अन्यथा अणु
			pr_err("%s: card present detect failed.\n",
				mmc_hostname(host->mmc));
			अवरोध;
		पूर्ण

		o2_host->dll_adjust_count++;
	पूर्ण
	अगर (!ret && o2_host->dll_adjust_count == DMDN_SZ)
		pr_err("%s: DLL adjust over max times\n",
		mmc_hostname(host->mmc));
	/* Lock WP */
	pci_पढ़ो_config_byte(chip->pdev,
				   O2_SD_LOCK_WP, &scratch_8);
	scratch_8 |= 0x80;
	pci_ग_लिखो_config_byte(chip->pdev, O2_SD_LOCK_WP, scratch_8);
	वापस ret;
पूर्ण

अटल पूर्णांक sdhci_o2_execute_tuning(काष्ठा mmc_host *mmc, u32 opcode)
अणु
	काष्ठा sdhci_host *host = mmc_priv(mmc);
	पूर्णांक current_bus_width = 0;
	u32 scratch32 = 0;
	u16 scratch = 0;

	/*
	 * This handler only implements the eMMC tuning that is specअगरic to
	 * this controller.  Fall back to the standard method क्रम other TIMING.
	 */
	अगर ((host->timing != MMC_TIMING_MMC_HS200) &&
		(host->timing != MMC_TIMING_UHS_SDR104))
		वापस sdhci_execute_tuning(mmc, opcode);

	अगर (WARN_ON((opcode != MMC_SEND_TUNING_BLOCK_HS200) &&
			(opcode != MMC_SEND_TUNING_BLOCK)))
		वापस -EINVAL;

	/* Force घातer mode enter L0 */
	scratch = sdhci_पढ़ोw(host, O2_SD_MISC_CTRL);
	scratch |= O2_SD_PWR_FORCE_L0;
	sdhci_ग_लिखोw(host, scratch, O2_SD_MISC_CTRL);

	/* रुको DLL lock, समयout value 5ms */
	अगर (पढ़ोx_poll_समयout(sdhci_o2_pll_dll_wdt_control, host,
		scratch32, (scratch32 & O2_DLL_LOCK_STATUS), 1, 5000))
		pr_warn("%s: DLL can't lock in 5ms after force L0 during tuning.\n",
				mmc_hostname(host->mmc));
	/*
	 * Judge the tuning reason, whether caused by dll shअगरt
	 * If cause by dll shअगरt, should call sdhci_o2_dll_recovery
	 */
	अगर (!sdhci_o2_रुको_dll_detect_lock(host))
		अगर (!sdhci_o2_dll_recovery(host)) अणु
			pr_err("%s: o2 dll recovery failed\n",
				mmc_hostname(host->mmc));
			वापस -EINVAL;
		पूर्ण
	/*
	 * o2 sdhci host didn't support 8bit emmc tuning
	 */
	अगर (mmc->ios.bus_width == MMC_BUS_WIDTH_8) अणु
		current_bus_width = mmc->ios.bus_width;
		mmc->ios.bus_width = MMC_BUS_WIDTH_4;
		sdhci_set_bus_width(host, MMC_BUS_WIDTH_4);
	पूर्ण

	sdhci_o2_set_tuning_mode(host);

	sdhci_start_tuning(host);

	__sdhci_o2_execute_tuning(host, opcode);

	sdhci_end_tuning(host);

	अगर (current_bus_width == MMC_BUS_WIDTH_8) अणु
		mmc->ios.bus_width = MMC_BUS_WIDTH_8;
		sdhci_set_bus_width(host, current_bus_width);
	पूर्ण

	/* Cancel क्रमce घातer mode enter L0 */
	scratch = sdhci_पढ़ोw(host, O2_SD_MISC_CTRL);
	scratch &= ~(O2_SD_PWR_FORCE_L0);
	sdhci_ग_लिखोw(host, scratch, O2_SD_MISC_CTRL);

	sdhci_reset(host, SDHCI_RESET_CMD);
	sdhci_reset(host, SDHCI_RESET_DATA);

	host->flags &= ~SDHCI_HS400_TUNING;
	वापस 0;
पूर्ण

अटल व्योम o2_pci_led_enable(काष्ठा sdhci_pci_chip *chip)
अणु
	पूर्णांक ret;
	u32 scratch_32;

	/* Set led of SD host function enable */
	ret = pci_पढ़ो_config_dword(chip->pdev,
				    O2_SD_FUNC_REG0, &scratch_32);
	अगर (ret)
		वापस;

	scratch_32 &= ~O2_SD_FREG0_LEDOFF;
	pci_ग_लिखो_config_dword(chip->pdev,
			       O2_SD_FUNC_REG0, scratch_32);

	ret = pci_पढ़ो_config_dword(chip->pdev,
				    O2_SD_TEST_REG, &scratch_32);
	अगर (ret)
		वापस;

	scratch_32 |= O2_SD_LED_ENABLE;
	pci_ग_लिखो_config_dword(chip->pdev,
			       O2_SD_TEST_REG, scratch_32);
पूर्ण

अटल व्योम sdhci_pci_o2_fujin2_pci_init(काष्ठा sdhci_pci_chip *chip)
अणु
	u32 scratch_32;
	पूर्णांक ret;
	/* Improve ग_लिखो perक्रमmance क्रम SD3.0 */
	ret = pci_पढ़ो_config_dword(chip->pdev, O2_SD_DEV_CTRL, &scratch_32);
	अगर (ret)
		वापस;
	scratch_32 &= ~((1 << 12) | (1 << 13) | (1 << 14));
	pci_ग_लिखो_config_dword(chip->pdev, O2_SD_DEV_CTRL, scratch_32);

	/* Enable Link abnormal reset generating Reset */
	ret = pci_पढ़ो_config_dword(chip->pdev, O2_SD_MISC_REG5, &scratch_32);
	अगर (ret)
		वापस;
	scratch_32 &= ~((1 << 19) | (1 << 11));
	scratch_32 |= (1 << 10);
	pci_ग_लिखो_config_dword(chip->pdev, O2_SD_MISC_REG5, scratch_32);

	/* set card घातer over current protection */
	ret = pci_पढ़ो_config_dword(chip->pdev, O2_SD_TEST_REG, &scratch_32);
	अगर (ret)
		वापस;
	scratch_32 |= (1 << 4);
	pci_ग_लिखो_config_dword(chip->pdev, O2_SD_TEST_REG, scratch_32);

	/* adjust the output delay क्रम SD mode */
	pci_ग_लिखो_config_dword(chip->pdev, O2_SD_DELAY_CTRL, 0x00002492);

	/* Set the output voltage setting of Aux 1.2v LDO */
	ret = pci_पढ़ो_config_dword(chip->pdev, O2_SD_LD0_CTRL, &scratch_32);
	अगर (ret)
		वापस;
	scratch_32 &= ~(3 << 12);
	pci_ग_लिखो_config_dword(chip->pdev, O2_SD_LD0_CTRL, scratch_32);

	/* Set Max घातer supply capability of SD host */
	ret = pci_पढ़ो_config_dword(chip->pdev, O2_SD_CAP_REG0, &scratch_32);
	अगर (ret)
		वापस;
	scratch_32 &= ~(0x01FE);
	scratch_32 |= 0x00CC;
	pci_ग_लिखो_config_dword(chip->pdev, O2_SD_CAP_REG0, scratch_32);
	/* Set DLL Tuning Winकरोw */
	ret = pci_पढ़ो_config_dword(chip->pdev,
				    O2_SD_TUNING_CTRL, &scratch_32);
	अगर (ret)
		वापस;
	scratch_32 &= ~(0x000000FF);
	scratch_32 |= 0x00000066;
	pci_ग_लिखो_config_dword(chip->pdev, O2_SD_TUNING_CTRL, scratch_32);

	/* Set UHS2 T_EIDLE */
	ret = pci_पढ़ो_config_dword(chip->pdev,
				    O2_SD_UHS2_L1_CTRL, &scratch_32);
	अगर (ret)
		वापस;
	scratch_32 &= ~(0x000000FC);
	scratch_32 |= 0x00000084;
	pci_ग_लिखो_config_dword(chip->pdev, O2_SD_UHS2_L1_CTRL, scratch_32);

	/* Set UHS2 Termination */
	ret = pci_पढ़ो_config_dword(chip->pdev, O2_SD_FUNC_REG3, &scratch_32);
	अगर (ret)
		वापस;
	scratch_32 &= ~((1 << 21) | (1 << 30));

	pci_ग_लिखो_config_dword(chip->pdev, O2_SD_FUNC_REG3, scratch_32);

	/* Set L1 Entrance Timer */
	ret = pci_पढ़ो_config_dword(chip->pdev, O2_SD_CAPS, &scratch_32);
	अगर (ret)
		वापस;
	scratch_32 &= ~(0xf0000000);
	scratch_32 |= 0x30000000;
	pci_ग_लिखो_config_dword(chip->pdev, O2_SD_CAPS, scratch_32);

	ret = pci_पढ़ो_config_dword(chip->pdev,
				    O2_SD_MISC_CTRL4, &scratch_32);
	अगर (ret)
		वापस;
	scratch_32 &= ~(0x000f0000);
	scratch_32 |= 0x00080000;
	pci_ग_लिखो_config_dword(chip->pdev, O2_SD_MISC_CTRL4, scratch_32);
पूर्ण

अटल व्योम sdhci_pci_o2_enable_msi(काष्ठा sdhci_pci_chip *chip,
				    काष्ठा sdhci_host *host)
अणु
	पूर्णांक ret;

	ret = pci_find_capability(chip->pdev, PCI_CAP_ID_MSI);
	अगर (!ret) अणु
		pr_info("%s: unsupport msi, use INTx irq\n",
			mmc_hostname(host->mmc));
		वापस;
	पूर्ण

	ret = pci_alloc_irq_vectors(chip->pdev, 1, 1,
				    PCI_IRQ_MSI | PCI_IRQ_MSIX);
	अगर (ret < 0) अणु
		pr_err("%s: enable PCI MSI failed, err=%d\n",
		       mmc_hostname(host->mmc), ret);
		वापस;
	पूर्ण

	host->irq = pci_irq_vector(chip->pdev, 0);
पूर्ण

अटल व्योम sdhci_o2_enable_clk(काष्ठा sdhci_host *host, u16 clk)
अणु
	/* Enable पूर्णांकernal घड़ी */
	clk |= SDHCI_CLOCK_INT_EN;
	sdhci_ग_लिखोw(host, clk, SDHCI_CLOCK_CONTROL);

	sdhci_o2_enable_पूर्णांकernal_घड़ी(host);
	अगर (sdhci_o2_get_cd(host->mmc)) अणु
		clk |= SDHCI_CLOCK_CARD_EN;
		sdhci_ग_लिखोw(host, clk, SDHCI_CLOCK_CONTROL);
	पूर्ण
पूर्ण

अटल व्योम sdhci_pci_o2_set_घड़ी(काष्ठा sdhci_host *host, अचिन्हित पूर्णांक घड़ी)
अणु
	u16 clk;
	u8 scratch;
	u32 scratch_32;
	काष्ठा sdhci_pci_slot *slot = sdhci_priv(host);
	काष्ठा sdhci_pci_chip *chip = slot->chip;

	host->mmc->actual_घड़ी = 0;

	sdhci_ग_लिखोw(host, 0, SDHCI_CLOCK_CONTROL);

	अगर (घड़ी == 0)
		वापस;

	अगर ((host->timing == MMC_TIMING_UHS_SDR104) && (घड़ी == 200000000)) अणु
		pci_पढ़ो_config_byte(chip->pdev, O2_SD_LOCK_WP, &scratch);

		scratch &= 0x7f;
		pci_ग_लिखो_config_byte(chip->pdev, O2_SD_LOCK_WP, scratch);

		pci_पढ़ो_config_dword(chip->pdev, O2_SD_PLL_SETTING, &scratch_32);

		अगर ((scratch_32 & 0xFFFF0000) != 0x2c280000)
			o2_pci_set_baseclk(chip, 0x2c280000);

		pci_पढ़ो_config_byte(chip->pdev, O2_SD_LOCK_WP, &scratch);

		scratch |= 0x80;
		pci_ग_लिखो_config_byte(chip->pdev, O2_SD_LOCK_WP, scratch);
	पूर्ण

	clk = sdhci_calc_clk(host, घड़ी, &host->mmc->actual_घड़ी);
	sdhci_o2_enable_clk(host, clk);
पूर्ण

अटल पूर्णांक sdhci_pci_o2_probe_slot(काष्ठा sdhci_pci_slot *slot)
अणु
	काष्ठा sdhci_pci_chip *chip;
	काष्ठा sdhci_host *host;
	काष्ठा o2_host *o2_host = sdhci_pci_priv(slot);
	u32 reg, caps;
	पूर्णांक ret;

	chip = slot->chip;
	host = slot->host;

	o2_host->dll_adjust_count = 0;
	caps = sdhci_पढ़ोl(host, SDHCI_CAPABILITIES);

	/*
	 * mmc_select_bus_width() will test the bus to determine the actual bus
	 * width.
	 */
	अगर (caps & SDHCI_CAN_DO_8BIT)
		host->mmc->caps |= MMC_CAP_8_BIT_DATA;

	चयन (chip->pdev->device) अणु
	हाल PCI_DEVICE_ID_O2_SDS0:
	हाल PCI_DEVICE_ID_O2_SEABIRD0:
	हाल PCI_DEVICE_ID_O2_SEABIRD1:
	हाल PCI_DEVICE_ID_O2_SDS1:
	हाल PCI_DEVICE_ID_O2_FUJIN2:
		reg = sdhci_पढ़ोl(host, O2_SD_VENDOR_SETTING);
		अगर (reg & 0x1)
			host->quirks |= SDHCI_QUIRK_MULTIBLOCK_READ_ACMD12;

		sdhci_pci_o2_enable_msi(chip, host);

		अगर (chip->pdev->device == PCI_DEVICE_ID_O2_SEABIRD0) अणु
			ret = pci_पढ़ो_config_dword(chip->pdev,
						    O2_SD_MISC_SETTING, &reg);
			अगर (ret)
				वापस -EIO;
			अगर (reg & (1 << 4)) अणु
				pr_info("%s: emmc 1.8v flag is set, force 1.8v signaling voltage\n",
					mmc_hostname(host->mmc));
				host->flags &= ~SDHCI_SIGNALING_330;
				host->flags |= SDHCI_SIGNALING_180;
				host->mmc->caps2 |= MMC_CAP2_NO_SD;
				host->mmc->caps2 |= MMC_CAP2_NO_SDIO;
				pci_ग_लिखो_config_dword(chip->pdev,
						       O2_SD_DETECT_SETTING, 3);
			पूर्ण

			slot->host->mmc_host_ops.get_cd = sdhci_o2_get_cd;
		पूर्ण

		अगर (chip->pdev->device == PCI_DEVICE_ID_O2_SEABIRD1) अणु
			slot->host->mmc_host_ops.get_cd = sdhci_o2_get_cd;
			host->mmc->caps2 |= MMC_CAP2_NO_SDIO;
			host->quirks2 |= SDHCI_QUIRK2_PRESET_VALUE_BROKEN;
		पूर्ण

		host->mmc_host_ops.execute_tuning = sdhci_o2_execute_tuning;

		अगर (chip->pdev->device != PCI_DEVICE_ID_O2_FUJIN2)
			अवरोध;
		/* set dll watch करोg समयr */
		reg = sdhci_पढ़ोl(host, O2_SD_VENDOR_SETTING2);
		reg |= (1 << 12);
		sdhci_ग_लिखोl(host, reg, O2_SD_VENDOR_SETTING2);

		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक sdhci_pci_o2_probe(काष्ठा sdhci_pci_chip *chip)
अणु
	पूर्णांक ret;
	u8 scratch;
	u32 scratch_32;

	चयन (chip->pdev->device) अणु
	हाल PCI_DEVICE_ID_O2_8220:
	हाल PCI_DEVICE_ID_O2_8221:
	हाल PCI_DEVICE_ID_O2_8320:
	हाल PCI_DEVICE_ID_O2_8321:
		/* This extra setup is required due to broken ADMA. */
		ret = pci_पढ़ो_config_byte(chip->pdev,
				O2_SD_LOCK_WP, &scratch);
		अगर (ret)
			वापस ret;
		scratch &= 0x7f;
		pci_ग_लिखो_config_byte(chip->pdev, O2_SD_LOCK_WP, scratch);

		/* Set Multi 3 to VCC3V# */
		pci_ग_लिखो_config_byte(chip->pdev, O2_SD_MULTI_VCC3V, 0x08);

		/* Disable CLK_REQ# support after media DET */
		ret = pci_पढ़ो_config_byte(chip->pdev,
				O2_SD_CLKREQ, &scratch);
		अगर (ret)
			वापस ret;
		scratch |= 0x20;
		pci_ग_लिखो_config_byte(chip->pdev, O2_SD_CLKREQ, scratch);

		/* Choose capabilities, enable SDMA.  We have to ग_लिखो 0x01
		 * to the capabilities रेजिस्टर first to unlock it.
		 */
		ret = pci_पढ़ो_config_byte(chip->pdev, O2_SD_CAPS, &scratch);
		अगर (ret)
			वापस ret;
		scratch |= 0x01;
		pci_ग_लिखो_config_byte(chip->pdev, O2_SD_CAPS, scratch);
		pci_ग_लिखो_config_byte(chip->pdev, O2_SD_CAPS, 0x73);

		/* Disable ADMA1/2 */
		pci_ग_लिखो_config_byte(chip->pdev, O2_SD_ADMA1, 0x39);
		pci_ग_लिखो_config_byte(chip->pdev, O2_SD_ADMA2, 0x08);

		/* Disable the infinite transfer mode */
		ret = pci_पढ़ो_config_byte(chip->pdev,
				O2_SD_INF_MOD, &scratch);
		अगर (ret)
			वापस ret;
		scratch |= 0x08;
		pci_ग_लिखो_config_byte(chip->pdev, O2_SD_INF_MOD, scratch);

		/* Lock WP */
		ret = pci_पढ़ो_config_byte(chip->pdev,
				O2_SD_LOCK_WP, &scratch);
		अगर (ret)
			वापस ret;
		scratch |= 0x80;
		pci_ग_लिखो_config_byte(chip->pdev, O2_SD_LOCK_WP, scratch);
		अवरोध;
	हाल PCI_DEVICE_ID_O2_SDS0:
	हाल PCI_DEVICE_ID_O2_SDS1:
	हाल PCI_DEVICE_ID_O2_FUJIN2:
		/* UnLock WP */
		ret = pci_पढ़ो_config_byte(chip->pdev,
				O2_SD_LOCK_WP, &scratch);
		अगर (ret)
			वापस ret;

		scratch &= 0x7f;
		pci_ग_लिखो_config_byte(chip->pdev, O2_SD_LOCK_WP, scratch);

		/* DevId=8520 subId= 0x11 or 0x12  Type Chip support */
		अगर (chip->pdev->device == PCI_DEVICE_ID_O2_FUJIN2) अणु
			ret = pci_पढ़ो_config_dword(chip->pdev,
						    O2_SD_FUNC_REG0,
						    &scratch_32);
			अगर (ret)
				वापस ret;
			scratch_32 = ((scratch_32 & 0xFF000000) >> 24);

			/* Check Whether subId is 0x11 or 0x12 */
			अगर ((scratch_32 == 0x11) || (scratch_32 == 0x12)) अणु
				scratch_32 = 0x25100000;

				o2_pci_set_baseclk(chip, scratch_32);
				ret = pci_पढ़ो_config_dword(chip->pdev,
							    O2_SD_FUNC_REG4,
							    &scratch_32);
				अगर (ret)
					वापस ret;

				/* Enable Base Clk setting change */
				scratch_32 |= O2_SD_FREG4_ENABLE_CLK_SET;
				pci_ग_लिखो_config_dword(chip->pdev,
						       O2_SD_FUNC_REG4,
						       scratch_32);

				/* Set Tuning Winकरोw to 4 */
				pci_ग_लिखो_config_byte(chip->pdev,
						      O2_SD_TUNING_CTRL, 0x44);

				अवरोध;
			पूर्ण
		पूर्ण

		/* Enable 8520 led function */
		o2_pci_led_enable(chip);

		/* Set समयout CLK */
		ret = pci_पढ़ो_config_dword(chip->pdev,
					    O2_SD_CLK_SETTING, &scratch_32);
		अगर (ret)
			वापस ret;

		scratch_32 &= ~(0xFF00);
		scratch_32 |= 0x07E0C800;
		pci_ग_लिखो_config_dword(chip->pdev,
				       O2_SD_CLK_SETTING, scratch_32);

		ret = pci_पढ़ो_config_dword(chip->pdev,
					    O2_SD_CLKREQ, &scratch_32);
		अगर (ret)
			वापस ret;
		scratch_32 |= 0x3;
		pci_ग_लिखो_config_dword(chip->pdev, O2_SD_CLKREQ, scratch_32);

		ret = pci_पढ़ो_config_dword(chip->pdev,
					    O2_SD_PLL_SETTING, &scratch_32);
		अगर (ret)
			वापस ret;

		scratch_32 &= ~(0x1F3F070E);
		scratch_32 |= 0x18270106;
		pci_ग_लिखो_config_dword(chip->pdev,
				       O2_SD_PLL_SETTING, scratch_32);

		/* Disable UHS1 funciton */
		ret = pci_पढ़ो_config_dword(chip->pdev,
					    O2_SD_CAP_REG2, &scratch_32);
		अगर (ret)
			वापस ret;
		scratch_32 &= ~(0xE0);
		pci_ग_लिखो_config_dword(chip->pdev,
				       O2_SD_CAP_REG2, scratch_32);

		अगर (chip->pdev->device == PCI_DEVICE_ID_O2_FUJIN2)
			sdhci_pci_o2_fujin2_pci_init(chip);

		/* Lock WP */
		ret = pci_पढ़ो_config_byte(chip->pdev,
					   O2_SD_LOCK_WP, &scratch);
		अगर (ret)
			वापस ret;
		scratch |= 0x80;
		pci_ग_लिखो_config_byte(chip->pdev, O2_SD_LOCK_WP, scratch);
		अवरोध;
	हाल PCI_DEVICE_ID_O2_SEABIRD0:
	हाल PCI_DEVICE_ID_O2_SEABIRD1:
		/* UnLock WP */
		ret = pci_पढ़ो_config_byte(chip->pdev,
				O2_SD_LOCK_WP, &scratch);
		अगर (ret)
			वापस ret;

		scratch &= 0x7f;
		pci_ग_लिखो_config_byte(chip->pdev, O2_SD_LOCK_WP, scratch);

		ret = pci_पढ़ो_config_dword(chip->pdev,
					    O2_SD_PLL_SETTING, &scratch_32);
		अगर (ret)
			वापस ret;

		अगर ((scratch_32 & 0xff000000) == 0x01000000) अणु
			scratch_32 &= 0x0000FFFF;
			scratch_32 |= 0x1F340000;

			pci_ग_लिखो_config_dword(chip->pdev,
					       O2_SD_PLL_SETTING, scratch_32);
		पूर्ण अन्यथा अणु
			scratch_32 &= 0x0000FFFF;
			scratch_32 |= 0x25100000;

			pci_ग_लिखो_config_dword(chip->pdev,
					       O2_SD_PLL_SETTING, scratch_32);

			ret = pci_पढ़ो_config_dword(chip->pdev,
						    O2_SD_FUNC_REG4,
						    &scratch_32);
			अगर (ret)
				वापस ret;
			scratch_32 |= (1 << 22);
			pci_ग_लिखो_config_dword(chip->pdev,
					       O2_SD_FUNC_REG4, scratch_32);
		पूर्ण

		/* Set Tuning Winकरोws to 5 */
		pci_ग_लिखो_config_byte(chip->pdev,
				O2_SD_TUNING_CTRL, 0x55);
		/* Lock WP */
		ret = pci_पढ़ो_config_byte(chip->pdev,
					   O2_SD_LOCK_WP, &scratch);
		अगर (ret)
			वापस ret;
		scratch |= 0x80;
		pci_ग_लिखो_config_byte(chip->pdev, O2_SD_LOCK_WP, scratch);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक sdhci_pci_o2_resume(काष्ठा sdhci_pci_chip *chip)
अणु
	sdhci_pci_o2_probe(chip);
	वापस sdhci_pci_resume_host(chip);
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा sdhci_ops sdhci_pci_o2_ops = अणु
	.set_घड़ी = sdhci_pci_o2_set_घड़ी,
	.enable_dma = sdhci_pci_enable_dma,
	.set_bus_width = sdhci_set_bus_width,
	.reset = sdhci_reset,
	.set_uhs_संकेतing = sdhci_set_uhs_संकेतing,
पूर्ण;

स्थिर काष्ठा sdhci_pci_fixes sdhci_o2 = अणु
	.probe = sdhci_pci_o2_probe,
	.quirks = SDHCI_QUIRK_NO_ENDATTR_IN_NOPDESC,
	.quirks2 = SDHCI_QUIRK2_CLEAR_TRANSFERMODE_REG_BEFORE_CMD,
	.probe_slot = sdhci_pci_o2_probe_slot,
#अगर_घोषित CONFIG_PM_SLEEP
	.resume = sdhci_pci_o2_resume,
#पूर्ण_अगर
	.ops = &sdhci_pci_o2_ops,
	.priv_size = माप(काष्ठा o2_host),
पूर्ण;
