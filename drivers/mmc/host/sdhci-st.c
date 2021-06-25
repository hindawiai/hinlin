<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Support क्रम SDHCI on STMicroelectronics SoCs
 *
 * Copyright (C) 2014 STMicroelectronics Ltd
 * Author: Giuseppe Cavallaro <peppe.cavallaro@st.com>
 * Contributors: Peter Grअगरfin <peter.grअगरfin@linaro.org>
 *
 * Based on sdhci-cns3xxx.c
 */

#समावेश <linux/पन.स>
#समावेश <linux/of.h>
#समावेश <linux/module.h>
#समावेश <linux/err.h>
#समावेश <linux/mmc/host.h>
#समावेश <linux/reset.h>
#समावेश "sdhci-pltfm.h"

काष्ठा st_mmc_platक्रमm_data अणु
	काष्ठा  reset_control *rstc;
	काष्ठा  clk *icnclk;
	व्योम __iomem *top_ioaddr;
पूर्ण;

/* MMCSS glue logic to setup the HC on some ST SoCs (e.g. STiH407 family) */

#घोषणा ST_MMC_CCONFIG_REG_1		0x400
#घोषणा ST_MMC_CCONFIG_TIMEOUT_CLK_UNIT	BIT(24)
#घोषणा ST_MMC_CCONFIG_TIMEOUT_CLK_FREQ	BIT(12)
#घोषणा ST_MMC_CCONFIG_TUNING_COUNT_DEFAULT	BIT(8)
#घोषणा ST_MMC_CCONFIG_ASYNC_WAKEUP	BIT(0)
#घोषणा ST_MMC_CCONFIG_1_DEFAULT	\
				((ST_MMC_CCONFIG_TIMEOUT_CLK_UNIT) | \
				 (ST_MMC_CCONFIG_TIMEOUT_CLK_FREQ) | \
				 (ST_MMC_CCONFIG_TUNING_COUNT_DEFAULT))

#घोषणा ST_MMC_CCONFIG_REG_2		0x404
#घोषणा ST_MMC_CCONFIG_HIGH_SPEED	BIT(28)
#घोषणा ST_MMC_CCONFIG_ADMA2		BIT(24)
#घोषणा ST_MMC_CCONFIG_8BIT		BIT(20)
#घोषणा ST_MMC_CCONFIG_MAX_BLK_LEN	16
#घोषणा  MAX_BLK_LEN_1024		1
#घोषणा  MAX_BLK_LEN_2048		2
#घोषणा BASE_CLK_FREQ_200		0xc8
#घोषणा BASE_CLK_FREQ_100		0x64
#घोषणा BASE_CLK_FREQ_50		0x32
#घोषणा ST_MMC_CCONFIG_2_DEFAULT \
	(ST_MMC_CCONFIG_HIGH_SPEED | ST_MMC_CCONFIG_ADMA2 | \
	 ST_MMC_CCONFIG_8BIT | \
	 (MAX_BLK_LEN_1024 << ST_MMC_CCONFIG_MAX_BLK_LEN))

#घोषणा ST_MMC_CCONFIG_REG_3			0x408
#घोषणा ST_MMC_CCONFIG_EMMC_SLOT_TYPE		BIT(28)
#घोषणा ST_MMC_CCONFIG_64BIT			BIT(24)
#घोषणा ST_MMC_CCONFIG_ASYNCH_INTR_SUPPORT	BIT(20)
#घोषणा ST_MMC_CCONFIG_1P8_VOLT			BIT(16)
#घोषणा ST_MMC_CCONFIG_3P0_VOLT			BIT(12)
#घोषणा ST_MMC_CCONFIG_3P3_VOLT			BIT(8)
#घोषणा ST_MMC_CCONFIG_SUSP_RES_SUPPORT		BIT(4)
#घोषणा ST_MMC_CCONFIG_SDMA			BIT(0)
#घोषणा ST_MMC_CCONFIG_3_DEFAULT	\
			 (ST_MMC_CCONFIG_ASYNCH_INTR_SUPPORT	| \
			  ST_MMC_CCONFIG_3P3_VOLT		| \
			  ST_MMC_CCONFIG_SUSP_RES_SUPPORT	| \
			  ST_MMC_CCONFIG_SDMA)

#घोषणा ST_MMC_CCONFIG_REG_4	0x40c
#घोषणा ST_MMC_CCONFIG_D_DRIVER	BIT(20)
#घोषणा ST_MMC_CCONFIG_C_DRIVER	BIT(16)
#घोषणा ST_MMC_CCONFIG_A_DRIVER	BIT(12)
#घोषणा ST_MMC_CCONFIG_DDR50	BIT(8)
#घोषणा ST_MMC_CCONFIG_SDR104	BIT(4)
#घोषणा ST_MMC_CCONFIG_SDR50	BIT(0)
#घोषणा ST_MMC_CCONFIG_4_DEFAULT	0

#घोषणा ST_MMC_CCONFIG_REG_5		0x410
#घोषणा ST_MMC_CCONFIG_TUNING_FOR_SDR50	BIT(8)
#घोषणा RETUNING_TIMER_CNT_MAX		0xf
#घोषणा ST_MMC_CCONFIG_5_DEFAULT	0

/* I/O configuration क्रम Arasan IP */
#घोषणा ST_MMC_GP_OUTPUT	0x450
#घोषणा ST_MMC_GP_OUTPUT_CD	BIT(12)

#घोषणा ST_MMC_STATUS_R		0x460

#घोषणा ST_TOP_MMC_DLY_FIX_OFF(x)	(x - 0x8)

/* TOP config रेजिस्टरs to manage अटल and dynamic delay */
#घोषणा ST_TOP_MMC_TX_CLK_DLY			ST_TOP_MMC_DLY_FIX_OFF(0x8)
#घोषणा ST_TOP_MMC_RX_CLK_DLY			ST_TOP_MMC_DLY_FIX_OFF(0xc)
/* MMC delay control रेजिस्टर */
#घोषणा ST_TOP_MMC_DLY_CTRL			ST_TOP_MMC_DLY_FIX_OFF(0x18)
#घोषणा ST_TOP_MMC_DLY_CTRL_DLL_BYPASS_CMD	BIT(0)
#घोषणा ST_TOP_MMC_DLY_CTRL_DLL_BYPASS_PH_SEL	BIT(1)
#घोषणा ST_TOP_MMC_DLY_CTRL_TX_DLL_ENABLE	BIT(8)
#घोषणा ST_TOP_MMC_DLY_CTRL_RX_DLL_ENABLE	BIT(9)
#घोषणा ST_TOP_MMC_DLY_CTRL_ATUNE_NOT_CFG_DLY	BIT(10)
#घोषणा ST_TOP_MMC_START_DLL_LOCK		BIT(11)

/* रेजिस्टर to provide the phase-shअगरt value क्रम DLL */
#घोषणा ST_TOP_MMC_TX_DLL_STEP_DLY		ST_TOP_MMC_DLY_FIX_OFF(0x1c)
#घोषणा ST_TOP_MMC_RX_DLL_STEP_DLY		ST_TOP_MMC_DLY_FIX_OFF(0x20)
#घोषणा ST_TOP_MMC_RX_CMD_STEP_DLY		ST_TOP_MMC_DLY_FIX_OFF(0x24)

/* phase shअगरt delay on the tx clk 2.188ns */
#घोषणा ST_TOP_MMC_TX_DLL_STEP_DLY_VALID	0x6

#घोषणा ST_TOP_MMC_DLY_MAX			0xf

#घोषणा ST_TOP_MMC_DYN_DLY_CONF	\
		(ST_TOP_MMC_DLY_CTRL_TX_DLL_ENABLE | \
		 ST_TOP_MMC_DLY_CTRL_ATUNE_NOT_CFG_DLY | \
		 ST_TOP_MMC_START_DLL_LOCK)

/*
 * For घड़ी speeds greater than 90MHz, we need to check that the
 * DLL procedure has finished beक्रमe चयनing to ultra-speed modes.
 */
#घोषणा	CLK_TO_CHECK_DLL_LOCK	90000000

अटल अंतरभूत व्योम st_mmcss_set_अटल_delay(व्योम __iomem *ioaddr)
अणु
	अगर (!ioaddr)
		वापस;

	ग_लिखोl_relaxed(0x0, ioaddr + ST_TOP_MMC_DLY_CTRL);
	ग_लिखोl_relaxed(ST_TOP_MMC_DLY_MAX,
			ioaddr + ST_TOP_MMC_TX_CLK_DLY);
पूर्ण

/**
 * st_mmcss_cconfig: configure the Arasan HC inside the flashSS.
 * @np: dt device node.
 * @host: sdhci host
 * Description: this function is to configure the Arasan host controller.
 * On some ST SoCs, i.e. STiH407 family, the MMC devices inside a dedicated
 * flashSS sub-प्रणाली which needs to be configured to be compliant to eMMC 4.5
 * or eMMC4.3.  This has to be करोne beक्रमe रेजिस्टरing the sdhci host.
 */
अटल व्योम st_mmcss_cconfig(काष्ठा device_node *np, काष्ठा sdhci_host *host)
अणु
	काष्ठा sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	काष्ठा mmc_host *mhost = host->mmc;
	u32 cconf2, cconf3, cconf4, cconf5;

	अगर (!of_device_is_compatible(np, "st,sdhci-stih407"))
		वापस;

	cconf2 = ST_MMC_CCONFIG_2_DEFAULT;
	cconf3 = ST_MMC_CCONFIG_3_DEFAULT;
	cconf4 = ST_MMC_CCONFIG_4_DEFAULT;
	cconf5 = ST_MMC_CCONFIG_5_DEFAULT;

	ग_लिखोl_relaxed(ST_MMC_CCONFIG_1_DEFAULT,
			host->ioaddr + ST_MMC_CCONFIG_REG_1);

	/* Set घड़ी frequency, शेष to 50MHz अगर max-frequency is not
	 * provided */

	चयन (mhost->f_max) अणु
	हाल 200000000:
		clk_set_rate(pltfm_host->clk, mhost->f_max);
		cconf2 |= BASE_CLK_FREQ_200;
		अवरोध;
	हाल 100000000:
		clk_set_rate(pltfm_host->clk, mhost->f_max);
		cconf2 |= BASE_CLK_FREQ_100;
		अवरोध;
	शेष:
		clk_set_rate(pltfm_host->clk, 50000000);
		cconf2 |= BASE_CLK_FREQ_50;
	पूर्ण

	ग_लिखोl_relaxed(cconf2, host->ioaddr + ST_MMC_CCONFIG_REG_2);

	अगर (!mmc_card_is_removable(mhost))
		cconf3 |= ST_MMC_CCONFIG_EMMC_SLOT_TYPE;
	अन्यथा
		/* CARD _D ET_CTRL */
		ग_लिखोl_relaxed(ST_MMC_GP_OUTPUT_CD,
				host->ioaddr + ST_MMC_GP_OUTPUT);

	अगर (mhost->caps & MMC_CAP_UHS_SDR50) अणु
		/* use 1.8V */
		cconf3 |= ST_MMC_CCONFIG_1P8_VOLT;
		cconf4 |= ST_MMC_CCONFIG_SDR50;
		/* Use tuning */
		cconf5 |= ST_MMC_CCONFIG_TUNING_FOR_SDR50;
		/* Max समयout क्रम retuning */
		cconf5 |= RETUNING_TIMER_CNT_MAX;
	पूर्ण

	अगर (mhost->caps & MMC_CAP_UHS_SDR104) अणु
		/*
		 * SDR104 implies the HC can support HS200 mode, so
		 * it's mandatory to use 1.8V
		 */
		cconf3 |= ST_MMC_CCONFIG_1P8_VOLT;
		cconf4 |= ST_MMC_CCONFIG_SDR104;
		/* Max समयout क्रम retuning */
		cconf5 |= RETUNING_TIMER_CNT_MAX;
	पूर्ण

	अगर (mhost->caps & MMC_CAP_UHS_DDR50)
		cconf4 |= ST_MMC_CCONFIG_DDR50;

	ग_लिखोl_relaxed(cconf3, host->ioaddr + ST_MMC_CCONFIG_REG_3);
	ग_लिखोl_relaxed(cconf4, host->ioaddr + ST_MMC_CCONFIG_REG_4);
	ग_लिखोl_relaxed(cconf5, host->ioaddr + ST_MMC_CCONFIG_REG_5);
पूर्ण

अटल अंतरभूत व्योम st_mmcss_set_dll(व्योम __iomem *ioaddr)
अणु
	अगर (!ioaddr)
		वापस;

	ग_लिखोl_relaxed(ST_TOP_MMC_DYN_DLY_CONF,	ioaddr + ST_TOP_MMC_DLY_CTRL);
	ग_लिखोl_relaxed(ST_TOP_MMC_TX_DLL_STEP_DLY_VALID,
			ioaddr + ST_TOP_MMC_TX_DLL_STEP_DLY);
पूर्ण

अटल पूर्णांक st_mmcss_lock_dll(व्योम __iomem *ioaddr)
अणु
	अचिन्हित दीर्घ curr, value;
	अचिन्हित दीर्घ finish = jअगरfies + HZ;

	/* Checks अगर the DLL procedure is finished */
	करो अणु
		curr = jअगरfies;
		value = पढ़ोl(ioaddr + ST_MMC_STATUS_R);
		अगर (value & 0x1)
			वापस 0;

		cpu_relax();
	पूर्ण जबतक (!समय_after_eq(curr, finish));

	वापस -EBUSY;
पूर्ण

अटल पूर्णांक sdhci_st_set_dll_क्रम_घड़ी(काष्ठा sdhci_host *host)
अणु
	पूर्णांक ret = 0;
	काष्ठा sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	काष्ठा st_mmc_platक्रमm_data *pdata = sdhci_pltfm_priv(pltfm_host);

	अगर (host->घड़ी > CLK_TO_CHECK_DLL_LOCK) अणु
		st_mmcss_set_dll(pdata->top_ioaddr);
		ret = st_mmcss_lock_dll(host->ioaddr);
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम sdhci_st_set_uhs_संकेतing(काष्ठा sdhci_host *host,
					अचिन्हित पूर्णांक uhs)
अणु
	काष्ठा sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	काष्ठा st_mmc_platक्रमm_data *pdata = sdhci_pltfm_priv(pltfm_host);
	u16 ctrl_2 = sdhci_पढ़ोw(host, SDHCI_HOST_CONTROL2);
	पूर्णांक ret = 0;

	/* Select Bus Speed Mode क्रम host */
	ctrl_2 &= ~SDHCI_CTRL_UHS_MASK;
	चयन (uhs) अणु
	/*
	 * Set V18_EN -- UHS modes करो not work without this.
	 * करोes not change संकेतing voltage
	 */

	हाल MMC_TIMING_UHS_SDR12:
		st_mmcss_set_अटल_delay(pdata->top_ioaddr);
		ctrl_2 |= SDHCI_CTRL_UHS_SDR12 | SDHCI_CTRL_VDD_180;
		अवरोध;
	हाल MMC_TIMING_UHS_SDR25:
		st_mmcss_set_अटल_delay(pdata->top_ioaddr);
		ctrl_2 |= SDHCI_CTRL_UHS_SDR25 | SDHCI_CTRL_VDD_180;
		अवरोध;
	हाल MMC_TIMING_UHS_SDR50:
		st_mmcss_set_अटल_delay(pdata->top_ioaddr);
		ctrl_2 |= SDHCI_CTRL_UHS_SDR50 | SDHCI_CTRL_VDD_180;
		ret = sdhci_st_set_dll_क्रम_घड़ी(host);
		अवरोध;
	हाल MMC_TIMING_UHS_SDR104:
	हाल MMC_TIMING_MMC_HS200:
		st_mmcss_set_अटल_delay(pdata->top_ioaddr);
		ctrl_2 |= SDHCI_CTRL_UHS_SDR104 | SDHCI_CTRL_VDD_180;
		ret =  sdhci_st_set_dll_क्रम_घड़ी(host);
		अवरोध;
	हाल MMC_TIMING_UHS_DDR50:
	हाल MMC_TIMING_MMC_DDR52:
		st_mmcss_set_अटल_delay(pdata->top_ioaddr);
		ctrl_2 |= SDHCI_CTRL_UHS_DDR50 | SDHCI_CTRL_VDD_180;
		अवरोध;
	पूर्ण

	अगर (ret)
		dev_warn(mmc_dev(host->mmc), "Error setting dll for clock "
						"(uhs %d)\n", uhs);

	dev_dbg(mmc_dev(host->mmc), "uhs %d, ctrl_2 %04X\n", uhs, ctrl_2);

	sdhci_ग_लिखोw(host, ctrl_2, SDHCI_HOST_CONTROL2);
पूर्ण

अटल u32 sdhci_st_पढ़ोl(काष्ठा sdhci_host *host, पूर्णांक reg)
अणु
	u32 ret;

	चयन (reg) अणु
	हाल SDHCI_CAPABILITIES:
		ret = पढ़ोl_relaxed(host->ioaddr + reg);
		/* Support 3.3V and 1.8V */
		ret &= ~SDHCI_CAN_VDD_300;
		अवरोध;
	शेष:
		ret = पढ़ोl_relaxed(host->ioaddr + reg);
	पूर्ण
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा sdhci_ops sdhci_st_ops = अणु
	.get_max_घड़ी = sdhci_pltfm_clk_get_max_घड़ी,
	.set_घड़ी = sdhci_set_घड़ी,
	.set_bus_width = sdhci_set_bus_width,
	.पढ़ो_l = sdhci_st_पढ़ोl,
	.reset = sdhci_reset,
	.set_uhs_संकेतing = sdhci_st_set_uhs_संकेतing,
पूर्ण;

अटल स्थिर काष्ठा sdhci_pltfm_data sdhci_st_pdata = अणु
	.ops = &sdhci_st_ops,
	.quirks = SDHCI_QUIRK_NO_ENDATTR_IN_NOPDESC |
		SDHCI_QUIRK_CAP_CLOCK_BASE_BROKEN |
		SDHCI_QUIRK_NO_HISPD_BIT,
	.quirks2 = SDHCI_QUIRK2_PRESET_VALUE_BROKEN |
		SDHCI_QUIRK2_STOP_WITH_TC,
पूर्ण;


अटल पूर्णांक sdhci_st_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा sdhci_host *host;
	काष्ठा st_mmc_platक्रमm_data *pdata;
	काष्ठा sdhci_pltfm_host *pltfm_host;
	काष्ठा clk *clk, *icnclk;
	पूर्णांक ret = 0;
	u16 host_version;
	काष्ठा resource *res;
	काष्ठा reset_control *rstc;

	clk =  devm_clk_get(&pdev->dev, "mmc");
	अगर (IS_ERR(clk)) अणु
		dev_err(&pdev->dev, "Peripheral clk not found\n");
		वापस PTR_ERR(clk);
	पूर्ण

	/* ICN घड़ी isn't compulsory, but use it if it's provided. */
	icnclk = devm_clk_get(&pdev->dev, "icn");
	अगर (IS_ERR(icnclk))
		icnclk = शून्य;

	rstc = devm_reset_control_get_optional_exclusive(&pdev->dev, शून्य);
	अगर (IS_ERR(rstc))
		वापस PTR_ERR(rstc);
	reset_control_deनिश्चित(rstc);

	host = sdhci_pltfm_init(pdev, &sdhci_st_pdata, माप(*pdata));
	अगर (IS_ERR(host)) अणु
		dev_err(&pdev->dev, "Failed sdhci_pltfm_init\n");
		ret = PTR_ERR(host);
		जाओ err_pltfm_init;
	पूर्ण

	pltfm_host = sdhci_priv(host);
	pdata = sdhci_pltfm_priv(pltfm_host);
	pdata->rstc = rstc;

	ret = mmc_of_parse(host->mmc);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Failed mmc_of_parse\n");
		जाओ err_of;
	पूर्ण

	ret = clk_prepare_enable(clk);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Failed to prepare clock\n");
		जाओ err_of;
	पूर्ण

	ret = clk_prepare_enable(icnclk);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Failed to prepare icn clock\n");
		जाओ err_icnclk;
	पूर्ण

	/* Configure the FlashSS Top रेजिस्टरs क्रम setting eMMC TX/RX delay */
	res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM,
					   "top-mmc-delay");
	pdata->top_ioaddr = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(pdata->top_ioaddr))
		pdata->top_ioaddr = शून्य;

	pltfm_host->clk = clk;
	pdata->icnclk = icnclk;

	/* Configure the Arasan HC inside the flashSS */
	st_mmcss_cconfig(np, host);

	ret = sdhci_add_host(host);
	अगर (ret)
		जाओ err_out;

	host_version = पढ़ोw_relaxed((host->ioaddr + SDHCI_HOST_VERSION));

	dev_info(&pdev->dev, "SDHCI ST Initialised: Host Version: 0x%x Vendor Version 0x%x\n",
		((host_version & SDHCI_SPEC_VER_MASK) >> SDHCI_SPEC_VER_SHIFT),
		((host_version & SDHCI_VENDOR_VER_MASK) >>
		SDHCI_VENDOR_VER_SHIFT));

	वापस 0;

err_out:
	clk_disable_unprepare(icnclk);
err_icnclk:
	clk_disable_unprepare(clk);
err_of:
	sdhci_pltfm_मुक्त(pdev);
err_pltfm_init:
	reset_control_निश्चित(rstc);

	वापस ret;
पूर्ण

अटल पूर्णांक sdhci_st_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sdhci_host *host = platक्रमm_get_drvdata(pdev);
	काष्ठा sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	काष्ठा st_mmc_platक्रमm_data *pdata = sdhci_pltfm_priv(pltfm_host);
	काष्ठा reset_control *rstc = pdata->rstc;
	पूर्णांक ret;

	ret = sdhci_pltfm_unरेजिस्टर(pdev);

	clk_disable_unprepare(pdata->icnclk);

	reset_control_निश्चित(rstc);

	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक sdhci_st_suspend(काष्ठा device *dev)
अणु
	काष्ठा sdhci_host *host = dev_get_drvdata(dev);
	काष्ठा sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	काष्ठा st_mmc_platक्रमm_data *pdata = sdhci_pltfm_priv(pltfm_host);
	पूर्णांक ret;

	अगर (host->tuning_mode != SDHCI_TUNING_MODE_3)
		mmc_retune_needed(host->mmc);

	ret = sdhci_suspend_host(host);
	अगर (ret)
		जाओ out;

	reset_control_निश्चित(pdata->rstc);

	clk_disable_unprepare(pdata->icnclk);
	clk_disable_unprepare(pltfm_host->clk);
out:
	वापस ret;
पूर्ण

अटल पूर्णांक sdhci_st_resume(काष्ठा device *dev)
अणु
	काष्ठा sdhci_host *host = dev_get_drvdata(dev);
	काष्ठा sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	काष्ठा st_mmc_platक्रमm_data *pdata = sdhci_pltfm_priv(pltfm_host);
	काष्ठा device_node *np = dev->of_node;
	पूर्णांक ret;

	ret = clk_prepare_enable(pltfm_host->clk);
	अगर (ret)
		वापस ret;

	ret = clk_prepare_enable(pdata->icnclk);
	अगर (ret) अणु
		clk_disable_unprepare(pltfm_host->clk);
		वापस ret;
	पूर्ण

	reset_control_deनिश्चित(pdata->rstc);

	st_mmcss_cconfig(np, host);

	वापस sdhci_resume_host(host);
पूर्ण
#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(sdhci_st_pmops, sdhci_st_suspend, sdhci_st_resume);

अटल स्थिर काष्ठा of_device_id st_sdhci_match[] = अणु
	अणु .compatible = "st,sdhci" पूर्ण,
	अणुपूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(of, st_sdhci_match);

अटल काष्ठा platक्रमm_driver sdhci_st_driver = अणु
	.probe = sdhci_st_probe,
	.हटाओ = sdhci_st_हटाओ,
	.driver = अणु
		   .name = "sdhci-st",
		   .probe_type = PROBE_PREFER_ASYNCHRONOUS,
		   .pm = &sdhci_st_pmops,
		   .of_match_table = st_sdhci_match,
		  पूर्ण,
पूर्ण;

module_platक्रमm_driver(sdhci_st_driver);

MODULE_DESCRIPTION("SDHCI driver for STMicroelectronics SoCs");
MODULE_AUTHOR("Giuseppe Cavallaro <peppe.cavallaro@st.com>");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:sdhci-st");
