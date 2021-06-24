<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Driver क्रम Synopsys DesignWare Cores Mobile Storage Host Controller
 *
 * Copyright (C) 2018 Synaptics Incorporated
 *
 * Author: Jisheng Zhang <jszhang@kernel.org>
 */

#समावेश <linux/acpi.h>
#समावेश <linux/clk.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/iopoll.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/sizes.h>

#समावेश "sdhci-pltfm.h"

#घोषणा SDHCI_DWCMSHC_ARG2_STUFF	GENMASK(31, 16)

/* DWCMSHC specअगरic Mode Select value */
#घोषणा DWCMSHC_CTRL_HS400		0x7

/* DWC IP venकरोr area 1 poपूर्णांकer */
#घोषणा DWCMSHC_P_VENDOR_AREA1		0xe8
#घोषणा DWCMSHC_AREA1_MASK		GENMASK(11, 0)
/* Offset inside the  venकरोr area 1 */
#घोषणा DWCMSHC_HOST_CTRL3		0x8
#घोषणा DWCMSHC_EMMC_CONTROL		0x2c
#घोषणा DWCMSHC_ENHANCED_STROBE		BIT(8)
#घोषणा DWCMSHC_EMMC_ATCTRL		0x40

/* Rockchip specअगरic Registers */
#घोषणा DWCMSHC_EMMC_DLL_CTRL		0x800
#घोषणा DWCMSHC_EMMC_DLL_RXCLK		0x804
#घोषणा DWCMSHC_EMMC_DLL_TXCLK		0x808
#घोषणा DWCMSHC_EMMC_DLL_STRBIN		0x80c
#घोषणा DLL_STRBIN_TAPNUM_FROM_SW	BIT(24)
#घोषणा DWCMSHC_EMMC_DLL_STATUS0	0x840
#घोषणा DWCMSHC_EMMC_DLL_START		BIT(0)
#घोषणा DWCMSHC_EMMC_DLL_LOCKED		BIT(8)
#घोषणा DWCMSHC_EMMC_DLL_TIMEOUT	BIT(9)
#घोषणा DWCMSHC_EMMC_DLL_RXCLK_SRCSEL	29
#घोषणा DWCMSHC_EMMC_DLL_START_POINT	16
#घोषणा DWCMSHC_EMMC_DLL_INC		8
#घोषणा DWCMSHC_EMMC_DLL_DLYENA		BIT(27)
#घोषणा DLL_TXCLK_TAPNUM_DEFAULT	0x8
#घोषणा DLL_STRBIN_TAPNUM_DEFAULT	0x8
#घोषणा DLL_TXCLK_TAPNUM_FROM_SW	BIT(24)
#घोषणा DLL_RXCLK_NO_INVERTER		1
#घोषणा DLL_RXCLK_INVERTER		0
#घोषणा DLL_LOCK_WO_TMOUT(x) \
	((((x) & DWCMSHC_EMMC_DLL_LOCKED) == DWCMSHC_EMMC_DLL_LOCKED) && \
	(((x) & DWCMSHC_EMMC_DLL_TIMEOUT) == 0))
#घोषणा RK3568_MAX_CLKS 3

#घोषणा BOUNDARY_OK(addr, len) \
	((addr | (SZ_128M - 1)) == ((addr + len - 1) | (SZ_128M - 1)))

काष्ठा rk3568_priv अणु
	/* Rockchip specअगरied optional घड़ीs */
	काष्ठा clk_bulk_data rockchip_clks[RK3568_MAX_CLKS];
	u8 txclk_tapnum;
पूर्ण;

काष्ठा dwcmshc_priv अणु
	काष्ठा clk	*bus_clk;
	पूर्णांक venकरोr_specअगरic_area1; /* P_VENDOR_SPECIFIC_AREA reg */
	व्योम *priv; /* poपूर्णांकer to SoC निजी stuff */
पूर्ण;

/*
 * If DMA addr spans 128MB boundary, we split the DMA transfer पूर्णांकo two
 * so that each DMA transfer करोesn't exceed the boundary.
 */
अटल व्योम dwcmshc_adma_ग_लिखो_desc(काष्ठा sdhci_host *host, व्योम **desc,
				    dma_addr_t addr, पूर्णांक len, अचिन्हित पूर्णांक cmd)
अणु
	पूर्णांक पंचांगplen, offset;

	अगर (likely(!len || BOUNDARY_OK(addr, len))) अणु
		sdhci_adma_ग_लिखो_desc(host, desc, addr, len, cmd);
		वापस;
	पूर्ण

	offset = addr & (SZ_128M - 1);
	पंचांगplen = SZ_128M - offset;
	sdhci_adma_ग_लिखो_desc(host, desc, addr, पंचांगplen, cmd);

	addr += पंचांगplen;
	len -= पंचांगplen;
	sdhci_adma_ग_लिखो_desc(host, desc, addr, len, cmd);
पूर्ण

अटल अचिन्हित पूर्णांक dwcmshc_get_max_घड़ी(काष्ठा sdhci_host *host)
अणु
	काष्ठा sdhci_pltfm_host *pltfm_host = sdhci_priv(host);

	अगर (pltfm_host->clk)
		वापस sdhci_pltfm_clk_get_max_घड़ी(host);
	अन्यथा
		वापस pltfm_host->घड़ी;
पूर्ण

अटल व्योम dwcmshc_check_स्वतः_cmd23(काष्ठा mmc_host *mmc,
				     काष्ठा mmc_request *mrq)
अणु
	काष्ठा sdhci_host *host = mmc_priv(mmc);

	/*
	 * No matter V4 is enabled or not, ARGUMENT2 रेजिस्टर is 32-bit
	 * block count रेजिस्टर which करोesn't support stuff bits of
	 * CMD23 argument on dwcmsch host controller.
	 */
	अगर (mrq->sbc && (mrq->sbc->arg & SDHCI_DWCMSHC_ARG2_STUFF))
		host->flags &= ~SDHCI_AUTO_CMD23;
	अन्यथा
		host->flags |= SDHCI_AUTO_CMD23;
पूर्ण

अटल व्योम dwcmshc_request(काष्ठा mmc_host *mmc, काष्ठा mmc_request *mrq)
अणु
	dwcmshc_check_स्वतः_cmd23(mmc, mrq);

	sdhci_request(mmc, mrq);
पूर्ण

अटल व्योम dwcmshc_set_uhs_संकेतing(काष्ठा sdhci_host *host,
				      अचिन्हित पूर्णांक timing)
अणु
	u16 ctrl_2;

	ctrl_2 = sdhci_पढ़ोw(host, SDHCI_HOST_CONTROL2);
	/* Select Bus Speed Mode क्रम host */
	ctrl_2 &= ~SDHCI_CTRL_UHS_MASK;
	अगर ((timing == MMC_TIMING_MMC_HS200) ||
	    (timing == MMC_TIMING_UHS_SDR104))
		ctrl_2 |= SDHCI_CTRL_UHS_SDR104;
	अन्यथा अगर (timing == MMC_TIMING_UHS_SDR12)
		ctrl_2 |= SDHCI_CTRL_UHS_SDR12;
	अन्यथा अगर ((timing == MMC_TIMING_UHS_SDR25) ||
		 (timing == MMC_TIMING_MMC_HS))
		ctrl_2 |= SDHCI_CTRL_UHS_SDR25;
	अन्यथा अगर (timing == MMC_TIMING_UHS_SDR50)
		ctrl_2 |= SDHCI_CTRL_UHS_SDR50;
	अन्यथा अगर ((timing == MMC_TIMING_UHS_DDR50) ||
		 (timing == MMC_TIMING_MMC_DDR52))
		ctrl_2 |= SDHCI_CTRL_UHS_DDR50;
	अन्यथा अगर (timing == MMC_TIMING_MMC_HS400)
		ctrl_2 |= DWCMSHC_CTRL_HS400;
	sdhci_ग_लिखोw(host, ctrl_2, SDHCI_HOST_CONTROL2);
पूर्ण

अटल व्योम dwcmshc_hs400_enhanced_strobe(काष्ठा mmc_host *mmc,
					  काष्ठा mmc_ios *ios)
अणु
	u32 venकरोr;
	काष्ठा sdhci_host *host = mmc_priv(mmc);
	काष्ठा sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	काष्ठा dwcmshc_priv *priv = sdhci_pltfm_priv(pltfm_host);
	पूर्णांक reg = priv->venकरोr_specअगरic_area1 + DWCMSHC_EMMC_CONTROL;

	venकरोr = sdhci_पढ़ोl(host, reg);
	अगर (ios->enhanced_strobe)
		venकरोr |= DWCMSHC_ENHANCED_STROBE;
	अन्यथा
		venकरोr &= ~DWCMSHC_ENHANCED_STROBE;

	sdhci_ग_लिखोl(host, venकरोr, reg);
पूर्ण

अटल व्योम dwcmshc_rk3568_set_घड़ी(काष्ठा sdhci_host *host, अचिन्हित पूर्णांक घड़ी)
अणु
	काष्ठा sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	काष्ठा dwcmshc_priv *dwc_priv = sdhci_pltfm_priv(pltfm_host);
	काष्ठा rk3568_priv *priv = dwc_priv->priv;
	u8 txclk_tapnum = DLL_TXCLK_TAPNUM_DEFAULT;
	u32 extra, reg;
	पूर्णांक err;

	host->mmc->actual_घड़ी = 0;

	/*
	 * DO NOT TOUCH THIS SETTING. RX clk inverter unit is enabled
	 * by शेष, but it shouldn't be enabled. We should anyway
	 * disable it beक्रमe issuing any cmds.
	 */
	extra = DWCMSHC_EMMC_DLL_DLYENA |
		DLL_RXCLK_NO_INVERTER << DWCMSHC_EMMC_DLL_RXCLK_SRCSEL;
	sdhci_ग_लिखोl(host, extra, DWCMSHC_EMMC_DLL_RXCLK);

	अगर (घड़ी == 0)
		वापस;

	/* Rockchip platक्रमm only support 375KHz क्रम identअगरy mode */
	अगर (घड़ी <= 400000)
		घड़ी = 375000;

	err = clk_set_rate(pltfm_host->clk, घड़ी);
	अगर (err)
		dev_err(mmc_dev(host->mmc), "fail to set clock %d", घड़ी);

	sdhci_set_घड़ी(host, घड़ी);

	/* Disable cmd conflict check */
	reg = dwc_priv->venकरोr_specअगरic_area1 + DWCMSHC_HOST_CTRL3;
	extra = sdhci_पढ़ोl(host, reg);
	extra &= ~BIT(0);
	sdhci_ग_लिखोl(host, extra, reg);

	अगर (घड़ी <= 400000) अणु
		/* Disable DLL to reset sample घड़ी */
		sdhci_ग_लिखोl(host, 0, DWCMSHC_EMMC_DLL_CTRL);
		वापस;
	पूर्ण

	/* Reset DLL */
	sdhci_ग_लिखोl(host, BIT(1), DWCMSHC_EMMC_DLL_CTRL);
	udelay(1);
	sdhci_ग_लिखोl(host, 0x0, DWCMSHC_EMMC_DLL_CTRL);

	/* Init DLL settings */
	extra = 0x5 << DWCMSHC_EMMC_DLL_START_POINT |
		0x2 << DWCMSHC_EMMC_DLL_INC |
		DWCMSHC_EMMC_DLL_START;
	sdhci_ग_लिखोl(host, extra, DWCMSHC_EMMC_DLL_CTRL);
	err = पढ़ोl_poll_समयout(host->ioaddr + DWCMSHC_EMMC_DLL_STATUS0,
				 extra, DLL_LOCK_WO_TMOUT(extra), 1,
				 500 * USEC_PER_MSEC);
	अगर (err) अणु
		dev_err(mmc_dev(host->mmc), "DLL lock timeout!\n");
		वापस;
	पूर्ण

	extra = 0x1 << 16 | /* tune घड़ी stop en */
		0x2 << 17 | /* pre-change delay */
		0x3 << 19;  /* post-change delay */
	sdhci_ग_लिखोl(host, extra, dwc_priv->venकरोr_specअगरic_area1 + DWCMSHC_EMMC_ATCTRL);

	अगर (host->mmc->ios.timing == MMC_TIMING_MMC_HS200 ||
	    host->mmc->ios.timing == MMC_TIMING_MMC_HS400)
		txclk_tapnum = priv->txclk_tapnum;

	extra = DWCMSHC_EMMC_DLL_DLYENA |
		DLL_TXCLK_TAPNUM_FROM_SW |
		txclk_tapnum;
	sdhci_ग_लिखोl(host, extra, DWCMSHC_EMMC_DLL_TXCLK);

	extra = DWCMSHC_EMMC_DLL_DLYENA |
		DLL_STRBIN_TAPNUM_DEFAULT |
		DLL_STRBIN_TAPNUM_FROM_SW;
	sdhci_ग_लिखोl(host, extra, DWCMSHC_EMMC_DLL_STRBIN);
पूर्ण

अटल स्थिर काष्ठा sdhci_ops sdhci_dwcmshc_ops = अणु
	.set_घड़ी		= sdhci_set_घड़ी,
	.set_bus_width		= sdhci_set_bus_width,
	.set_uhs_संकेतing	= dwcmshc_set_uhs_संकेतing,
	.get_max_घड़ी		= dwcmshc_get_max_घड़ी,
	.reset			= sdhci_reset,
	.adma_ग_लिखो_desc	= dwcmshc_adma_ग_लिखो_desc,
पूर्ण;

अटल स्थिर काष्ठा sdhci_ops sdhci_dwcmshc_rk3568_ops = अणु
	.set_घड़ी		= dwcmshc_rk3568_set_घड़ी,
	.set_bus_width		= sdhci_set_bus_width,
	.set_uhs_संकेतing	= dwcmshc_set_uhs_संकेतing,
	.get_max_घड़ी		= sdhci_pltfm_clk_get_max_घड़ी,
	.reset			= sdhci_reset,
	.adma_ग_लिखो_desc	= dwcmshc_adma_ग_लिखो_desc,
पूर्ण;

अटल स्थिर काष्ठा sdhci_pltfm_data sdhci_dwcmshc_pdata = अणु
	.ops = &sdhci_dwcmshc_ops,
	.quirks = SDHCI_QUIRK_CAP_CLOCK_BASE_BROKEN,
	.quirks2 = SDHCI_QUIRK2_PRESET_VALUE_BROKEN,
पूर्ण;

अटल स्थिर काष्ठा sdhci_pltfm_data sdhci_dwcmshc_rk3568_pdata = अणु
	.ops = &sdhci_dwcmshc_rk3568_ops,
	.quirks = SDHCI_QUIRK_CAP_CLOCK_BASE_BROKEN |
		  SDHCI_QUIRK_BROKEN_TIMEOUT_VAL,
	.quirks2 = SDHCI_QUIRK2_PRESET_VALUE_BROKEN |
		   SDHCI_QUIRK2_CLOCK_DIV_ZERO_BROKEN,
पूर्ण;

अटल पूर्णांक dwcmshc_rk3568_init(काष्ठा sdhci_host *host, काष्ठा dwcmshc_priv *dwc_priv)
अणु
	पूर्णांक err;
	काष्ठा rk3568_priv *priv = dwc_priv->priv;

	priv->rockchip_clks[0].id = "axi";
	priv->rockchip_clks[1].id = "block";
	priv->rockchip_clks[2].id = "timer";
	err = devm_clk_bulk_get_optional(mmc_dev(host->mmc), RK3568_MAX_CLKS,
					 priv->rockchip_clks);
	अगर (err) अणु
		dev_err(mmc_dev(host->mmc), "failed to get clocks %d\n", err);
		वापस err;
	पूर्ण

	err = clk_bulk_prepare_enable(RK3568_MAX_CLKS, priv->rockchip_clks);
	अगर (err) अणु
		dev_err(mmc_dev(host->mmc), "failed to enable clocks %d\n", err);
		वापस err;
	पूर्ण

	अगर (of_property_पढ़ो_u8(mmc_dev(host->mmc)->of_node, "rockchip,txclk-tapnum",
				&priv->txclk_tapnum))
		priv->txclk_tapnum = DLL_TXCLK_TAPNUM_DEFAULT;

	/* Disable cmd conflict check */
	sdhci_ग_लिखोl(host, 0x0, dwc_priv->venकरोr_specअगरic_area1 + DWCMSHC_HOST_CTRL3);
	/* Reset previous settings */
	sdhci_ग_लिखोl(host, 0, DWCMSHC_EMMC_DLL_TXCLK);
	sdhci_ग_लिखोl(host, 0, DWCMSHC_EMMC_DLL_STRBIN);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id sdhci_dwcmshc_dt_ids[] = अणु
	अणु
		.compatible = "rockchip,rk3568-dwcmshc",
		.data = &sdhci_dwcmshc_rk3568_pdata,
	पूर्ण,
	अणु
		.compatible = "snps,dwcmshc-sdhci",
		.data = &sdhci_dwcmshc_pdata,
	पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, sdhci_dwcmshc_dt_ids);

#अगर_घोषित CONFIG_ACPI
अटल स्थिर काष्ठा acpi_device_id sdhci_dwcmshc_acpi_ids[] = अणु
	अणु .id = "MLNXBF30" पूर्ण,
	अणुपूर्ण
पूर्ण;
#पूर्ण_अगर

अटल पूर्णांक dwcmshc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा sdhci_pltfm_host *pltfm_host;
	काष्ठा sdhci_host *host;
	काष्ठा dwcmshc_priv *priv;
	काष्ठा rk3568_priv *rk_priv = शून्य;
	स्थिर काष्ठा sdhci_pltfm_data *pltfm_data;
	पूर्णांक err;
	u32 extra;

	pltfm_data = of_device_get_match_data(&pdev->dev);
	अगर (!pltfm_data) अणु
		dev_err(&pdev->dev, "Error: No device match data found\n");
		वापस -ENODEV;
	पूर्ण

	host = sdhci_pltfm_init(pdev, pltfm_data,
				माप(काष्ठा dwcmshc_priv));
	अगर (IS_ERR(host))
		वापस PTR_ERR(host);

	/*
	 * extra adma table cnt क्रम cross 128M boundary handling.
	 */
	extra = DIV_ROUND_UP_ULL(dma_get_required_mask(dev), SZ_128M);
	अगर (extra > SDHCI_MAX_SEGS)
		extra = SDHCI_MAX_SEGS;
	host->adma_table_cnt += extra;

	pltfm_host = sdhci_priv(host);
	priv = sdhci_pltfm_priv(pltfm_host);

	अगर (dev->of_node) अणु
		pltfm_host->clk = devm_clk_get(dev, "core");
		अगर (IS_ERR(pltfm_host->clk)) अणु
			err = PTR_ERR(pltfm_host->clk);
			dev_err(dev, "failed to get core clk: %d\n", err);
			जाओ मुक्त_pltfm;
		पूर्ण
		err = clk_prepare_enable(pltfm_host->clk);
		अगर (err)
			जाओ मुक्त_pltfm;

		priv->bus_clk = devm_clk_get(dev, "bus");
		अगर (!IS_ERR(priv->bus_clk))
			clk_prepare_enable(priv->bus_clk);
	पूर्ण

	err = mmc_of_parse(host->mmc);
	अगर (err)
		जाओ err_clk;

	sdhci_get_of_property(pdev);

	priv->venकरोr_specअगरic_area1 =
		sdhci_पढ़ोl(host, DWCMSHC_P_VENDOR_AREA1) & DWCMSHC_AREA1_MASK;

	host->mmc_host_ops.request = dwcmshc_request;
	host->mmc_host_ops.hs400_enhanced_strobe = dwcmshc_hs400_enhanced_strobe;

	अगर (pltfm_data == &sdhci_dwcmshc_rk3568_pdata) अणु
		rk_priv = devm_kzalloc(&pdev->dev, माप(काष्ठा rk3568_priv), GFP_KERNEL);
		अगर (!rk_priv) अणु
			err = -ENOMEM;
			जाओ err_clk;
		पूर्ण

		priv->priv = rk_priv;

		err = dwcmshc_rk3568_init(host, priv);
		अगर (err)
			जाओ err_clk;
	पूर्ण

	host->mmc->caps |= MMC_CAP_WAIT_WHILE_BUSY;

	err = sdhci_add_host(host);
	अगर (err)
		जाओ err_clk;

	वापस 0;

err_clk:
	clk_disable_unprepare(pltfm_host->clk);
	clk_disable_unprepare(priv->bus_clk);
	अगर (rk_priv)
		clk_bulk_disable_unprepare(RK3568_MAX_CLKS,
					   rk_priv->rockchip_clks);
मुक्त_pltfm:
	sdhci_pltfm_मुक्त(pdev);
	वापस err;
पूर्ण

अटल पूर्णांक dwcmshc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sdhci_host *host = platक्रमm_get_drvdata(pdev);
	काष्ठा sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	काष्ठा dwcmshc_priv *priv = sdhci_pltfm_priv(pltfm_host);
	काष्ठा rk3568_priv *rk_priv = priv->priv;

	sdhci_हटाओ_host(host, 0);

	clk_disable_unprepare(pltfm_host->clk);
	clk_disable_unprepare(priv->bus_clk);
	अगर (rk_priv)
		clk_bulk_disable_unprepare(RK3568_MAX_CLKS,
					   rk_priv->rockchip_clks);
	sdhci_pltfm_मुक्त(pdev);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक dwcmshc_suspend(काष्ठा device *dev)
अणु
	काष्ठा sdhci_host *host = dev_get_drvdata(dev);
	काष्ठा sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	काष्ठा dwcmshc_priv *priv = sdhci_pltfm_priv(pltfm_host);
	काष्ठा rk3568_priv *rk_priv = priv->priv;
	पूर्णांक ret;

	ret = sdhci_suspend_host(host);
	अगर (ret)
		वापस ret;

	clk_disable_unprepare(pltfm_host->clk);
	अगर (!IS_ERR(priv->bus_clk))
		clk_disable_unprepare(priv->bus_clk);

	अगर (rk_priv)
		clk_bulk_disable_unprepare(RK3568_MAX_CLKS,
					   rk_priv->rockchip_clks);

	वापस ret;
पूर्ण

अटल पूर्णांक dwcmshc_resume(काष्ठा device *dev)
अणु
	काष्ठा sdhci_host *host = dev_get_drvdata(dev);
	काष्ठा sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	काष्ठा dwcmshc_priv *priv = sdhci_pltfm_priv(pltfm_host);
	काष्ठा rk3568_priv *rk_priv = priv->priv;
	पूर्णांक ret;

	ret = clk_prepare_enable(pltfm_host->clk);
	अगर (ret)
		वापस ret;

	अगर (!IS_ERR(priv->bus_clk)) अणु
		ret = clk_prepare_enable(priv->bus_clk);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (rk_priv) अणु
		ret = clk_bulk_prepare_enable(RK3568_MAX_CLKS,
					      rk_priv->rockchip_clks);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस sdhci_resume_host(host);
पूर्ण
#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(dwcmshc_pmops, dwcmshc_suspend, dwcmshc_resume);

अटल काष्ठा platक्रमm_driver sdhci_dwcmshc_driver = अणु
	.driver	= अणु
		.name	= "sdhci-dwcmshc",
		.probe_type = PROBE_PREFER_ASYNCHRONOUS,
		.of_match_table = sdhci_dwcmshc_dt_ids,
		.acpi_match_table = ACPI_PTR(sdhci_dwcmshc_acpi_ids),
		.pm = &dwcmshc_pmops,
	पूर्ण,
	.probe	= dwcmshc_probe,
	.हटाओ	= dwcmshc_हटाओ,
पूर्ण;
module_platक्रमm_driver(sdhci_dwcmshc_driver);

MODULE_DESCRIPTION("SDHCI platform driver for Synopsys DWC MSHC");
MODULE_AUTHOR("Jisheng Zhang <jszhang@kernel.org>");
MODULE_LICENSE("GPL v2");
