<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * drivers/mmc/host/sdhci-of-sparx5.c
 *
 * MCHP Sparx5 SoC Secure Digital Host Controller Interface.
 *
 * Copyright (c) 2019 Microchip Inc.
 *
 * Author: Lars Povlsen <lars.povlsen@microchip.com>
 */

#समावेश <linux/sizes.h>
#समावेश <linux/delay.h>
#समावेश <linux/module.h>
#समावेश <linux/regmap.h>
#समावेश <linux/of_device.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/dma-mapping.h>

#समावेश "sdhci-pltfm.h"

#घोषणा CPU_REGS_GENERAL_CTRL	(0x22 * 4)
#घोषणा  MSHC_DLY_CC_MASK	GENMASK(16, 13)
#घोषणा  MSHC_DLY_CC_SHIFT	13
#घोषणा  MSHC_DLY_CC_MAX	15

#घोषणा CPU_REGS_PROC_CTRL	(0x2C * 4)
#घोषणा  ACP_CACHE_FORCE_ENA	BIT(4)
#घोषणा  ACP_AWCACHE		BIT(3)
#घोषणा  ACP_ARCACHE		BIT(2)
#घोषणा  ACP_CACHE_MASK		(ACP_CACHE_FORCE_ENA|ACP_AWCACHE|ACP_ARCACHE)

#घोषणा MSHC2_VERSION			0x500	/* Off 0x140, reg 0x0 */
#घोषणा MSHC2_TYPE			0x504	/* Off 0x140, reg 0x1 */
#घोषणा MSHC2_EMMC_CTRL			0x52c	/* Off 0x140, reg 0xB */
#घोषणा  MSHC2_EMMC_CTRL_EMMC_RST_N	BIT(2)
#घोषणा  MSHC2_EMMC_CTRL_IS_EMMC	BIT(0)

काष्ठा sdhci_sparx5_data अणु
	काष्ठा sdhci_host *host;
	काष्ठा regmap *cpu_ctrl;
	पूर्णांक delay_घड़ी;
पूर्ण;

#घोषणा BOUNDARY_OK(addr, len) \
	((addr | (SZ_128M - 1)) == ((addr + len - 1) | (SZ_128M - 1)))

/*
 * If DMA addr spans 128MB boundary, we split the DMA transfer पूर्णांकo two
 * so that each DMA transfer करोesn't exceed the boundary.
 */
अटल व्योम sdhci_sparx5_adma_ग_लिखो_desc(काष्ठा sdhci_host *host, व्योम **desc,
					  dma_addr_t addr, पूर्णांक len,
					  अचिन्हित पूर्णांक cmd)
अणु
	पूर्णांक पंचांगplen, offset;

	अगर (likely(!len || BOUNDARY_OK(addr, len))) अणु
		sdhci_adma_ग_लिखो_desc(host, desc, addr, len, cmd);
		वापस;
	पूर्ण

	pr_debug("%s: write_desc: splitting dma len %d, offset %pad\n",
		 mmc_hostname(host->mmc), len, &addr);

	offset = addr & (SZ_128M - 1);
	पंचांगplen = SZ_128M - offset;
	sdhci_adma_ग_लिखो_desc(host, desc, addr, पंचांगplen, cmd);

	addr += पंचांगplen;
	len -= पंचांगplen;
	sdhci_adma_ग_लिखो_desc(host, desc, addr, len, cmd);
पूर्ण

अटल व्योम sparx5_set_cacheable(काष्ठा sdhci_host *host, u32 value)
अणु
	काष्ठा sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	काष्ठा sdhci_sparx5_data *sdhci_sparx5 = sdhci_pltfm_priv(pltfm_host);

	pr_debug("%s: Set Cacheable = 0x%x\n", mmc_hostname(host->mmc), value);

	/* Update ACP caching attributes in HW */
	regmap_update_bits(sdhci_sparx5->cpu_ctrl,
			   CPU_REGS_PROC_CTRL, ACP_CACHE_MASK, value);
पूर्ण

अटल व्योम sparx5_set_delay(काष्ठा sdhci_host *host, u8 value)
अणु
	काष्ठा sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	काष्ठा sdhci_sparx5_data *sdhci_sparx5 = sdhci_pltfm_priv(pltfm_host);

	pr_debug("%s: Set DLY_CC = %u\n", mmc_hostname(host->mmc), value);

	/* Update DLY_CC in HW */
	regmap_update_bits(sdhci_sparx5->cpu_ctrl,
			   CPU_REGS_GENERAL_CTRL,
			   MSHC_DLY_CC_MASK,
			   (value << MSHC_DLY_CC_SHIFT));
पूर्ण

अटल व्योम sdhci_sparx5_set_emmc(काष्ठा sdhci_host *host)
अणु
	अगर (!mmc_card_is_removable(host->mmc)) अणु
		u8 value;

		value = sdhci_पढ़ोb(host, MSHC2_EMMC_CTRL);
		अगर (!(value & MSHC2_EMMC_CTRL_IS_EMMC)) अणु
			value |= MSHC2_EMMC_CTRL_IS_EMMC;
			pr_debug("%s: Set EMMC_CTRL: 0x%08x\n",
				 mmc_hostname(host->mmc), value);
			sdhci_ग_लिखोb(host, value, MSHC2_EMMC_CTRL);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम sdhci_sparx5_reset_emmc(काष्ठा sdhci_host *host)
अणु
	u8 value;

	pr_debug("%s: Toggle EMMC_CTRL.EMMC_RST_N\n", mmc_hostname(host->mmc));
	value = sdhci_पढ़ोb(host, MSHC2_EMMC_CTRL) &
		~MSHC2_EMMC_CTRL_EMMC_RST_N;
	sdhci_ग_लिखोb(host, value, MSHC2_EMMC_CTRL);
	/* For eMMC, minimum is 1us but give it 10us क्रम good measure */
	usleep_range(10, 20);
	sdhci_ग_लिखोb(host, value | MSHC2_EMMC_CTRL_EMMC_RST_N,
		     MSHC2_EMMC_CTRL);
	/* For eMMC, minimum is 200us but give it 300us क्रम good measure */
	usleep_range(300, 400);
पूर्ण

अटल व्योम sdhci_sparx5_reset(काष्ठा sdhci_host *host, u8 mask)
अणु
	pr_debug("%s: *** RESET: mask %d\n", mmc_hostname(host->mmc), mask);

	sdhci_reset(host, mask);

	/* Be sure CARD_IS_EMMC stays set */
	sdhci_sparx5_set_emmc(host);
पूर्ण

अटल स्थिर काष्ठा sdhci_ops sdhci_sparx5_ops = अणु
	.set_घड़ी		= sdhci_set_घड़ी,
	.set_bus_width		= sdhci_set_bus_width,
	.set_uhs_संकेतing	= sdhci_set_uhs_संकेतing,
	.get_max_घड़ी		= sdhci_pltfm_clk_get_max_घड़ी,
	.reset			= sdhci_sparx5_reset,
	.adma_ग_लिखो_desc	= sdhci_sparx5_adma_ग_लिखो_desc,
पूर्ण;

अटल स्थिर काष्ठा sdhci_pltfm_data sdhci_sparx5_pdata = अणु
	.quirks  = 0,
	.quirks2 = SDHCI_QUIRK2_HOST_NO_CMD23 | /* Controller issue */
		   SDHCI_QUIRK2_NO_1_8_V, /* No sdr104, ddr50, etc */
	.ops = &sdhci_sparx5_ops,
पूर्ण;

अटल पूर्णांक sdhci_sparx5_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक ret;
	स्थिर अक्षर *syscon = "microchip,sparx5-cpu-syscon";
	काष्ठा sdhci_host *host;
	काष्ठा sdhci_pltfm_host *pltfm_host;
	काष्ठा sdhci_sparx5_data *sdhci_sparx5;
	काष्ठा device_node *np = pdev->dev.of_node;
	u32 value;
	u32 extra;

	host = sdhci_pltfm_init(pdev, &sdhci_sparx5_pdata,
				माप(*sdhci_sparx5));

	अगर (IS_ERR(host))
		वापस PTR_ERR(host);

	/*
	 * extra adma table cnt क्रम cross 128M boundary handling.
	 */
	extra = DIV_ROUND_UP_ULL(dma_get_required_mask(&pdev->dev), SZ_128M);
	अगर (extra > SDHCI_MAX_SEGS)
		extra = SDHCI_MAX_SEGS;
	host->adma_table_cnt += extra;

	pltfm_host = sdhci_priv(host);
	sdhci_sparx5 = sdhci_pltfm_priv(pltfm_host);
	sdhci_sparx5->host = host;

	pltfm_host->clk = devm_clk_get(&pdev->dev, "core");
	अगर (IS_ERR(pltfm_host->clk)) अणु
		ret = PTR_ERR(pltfm_host->clk);
		dev_err(&pdev->dev, "failed to get core clk: %d\n", ret);
		जाओ मुक्त_pltfm;
	पूर्ण
	ret = clk_prepare_enable(pltfm_host->clk);
	अगर (ret)
		जाओ मुक्त_pltfm;

	अगर (!of_property_पढ़ो_u32(np, "microchip,clock-delay", &value) &&
	    (value > 0 && value <= MSHC_DLY_CC_MAX))
		sdhci_sparx5->delay_घड़ी = value;

	sdhci_get_of_property(pdev);

	ret = mmc_of_parse(host->mmc);
	अगर (ret)
		जाओ err_clk;

	sdhci_sparx5->cpu_ctrl = syscon_regmap_lookup_by_compatible(syscon);
	अगर (IS_ERR(sdhci_sparx5->cpu_ctrl)) अणु
		dev_err(&pdev->dev, "No CPU syscon regmap !\n");
		ret = PTR_ERR(sdhci_sparx5->cpu_ctrl);
		जाओ err_clk;
	पूर्ण

	अगर (sdhci_sparx5->delay_घड़ी >= 0)
		sparx5_set_delay(host, sdhci_sparx5->delay_घड़ी);

	अगर (!mmc_card_is_removable(host->mmc)) अणु
		/* Do a HW reset of eMMC card */
		sdhci_sparx5_reset_emmc(host);
		/* Update EMMC_CTRL */
		sdhci_sparx5_set_emmc(host);
		/* If eMMC, disable SD and SDIO */
		host->mmc->caps2 |= (MMC_CAP2_NO_SDIO|MMC_CAP2_NO_SD);
	पूर्ण

	ret = sdhci_add_host(host);
	अगर (ret)
		जाओ err_clk;

	/* Set AXI bus master to use un-cached access (क्रम DMA) */
	अगर (host->flags & (SDHCI_USE_SDMA | SDHCI_USE_ADMA) &&
	    IS_ENABLED(CONFIG_DMA_DECLARE_COHERENT))
		sparx5_set_cacheable(host, ACP_CACHE_FORCE_ENA);

	pr_debug("%s: SDHC version: 0x%08x\n",
		 mmc_hostname(host->mmc), sdhci_पढ़ोl(host, MSHC2_VERSION));
	pr_debug("%s: SDHC type:    0x%08x\n",
		 mmc_hostname(host->mmc), sdhci_पढ़ोl(host, MSHC2_TYPE));

	वापस ret;

err_clk:
	clk_disable_unprepare(pltfm_host->clk);
मुक्त_pltfm:
	sdhci_pltfm_मुक्त(pdev);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा of_device_id sdhci_sparx5_of_match[] = अणु
	अणु .compatible = "microchip,dw-sparx5-sdhci" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, sdhci_sparx5_of_match);

अटल काष्ठा platक्रमm_driver sdhci_sparx5_driver = अणु
	.driver = अणु
		.name = "sdhci-sparx5",
		.probe_type = PROBE_PREFER_ASYNCHRONOUS,
		.of_match_table = sdhci_sparx5_of_match,
		.pm = &sdhci_pltfm_pmops,
	पूर्ण,
	.probe = sdhci_sparx5_probe,
	.हटाओ = sdhci_pltfm_unरेजिस्टर,
पूर्ण;

module_platक्रमm_driver(sdhci_sparx5_driver);

MODULE_DESCRIPTION("Sparx5 SDHCI OF driver");
MODULE_AUTHOR("Lars Povlsen <lars.povlsen@microchip.com>");
MODULE_LICENSE("GPL v2");
