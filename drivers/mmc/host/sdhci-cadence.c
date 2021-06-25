<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2016 Socionext Inc.
 *   Author: Masahiro Yamada <yamada.masahiro@socionext.com>
 */

#समावेश <linux/bitfield.h>
#समावेश <linux/bits.h>
#समावेश <linux/iopoll.h>
#समावेश <linux/module.h>
#समावेश <linux/mmc/host.h>
#समावेश <linux/mmc/mmc.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>

#समावेश "sdhci-pltfm.h"

/* HRS - Host Register Set (specअगरic to Cadence) */
#घोषणा SDHCI_CDNS_HRS04		0x10		/* PHY access port */
#घोषणा   SDHCI_CDNS_HRS04_ACK			BIT(26)
#घोषणा   SDHCI_CDNS_HRS04_RD			BIT(25)
#घोषणा   SDHCI_CDNS_HRS04_WR			BIT(24)
#घोषणा   SDHCI_CDNS_HRS04_RDATA		GENMASK(23, 16)
#घोषणा   SDHCI_CDNS_HRS04_WDATA		GENMASK(15, 8)
#घोषणा   SDHCI_CDNS_HRS04_ADDR			GENMASK(5, 0)

#घोषणा SDHCI_CDNS_HRS06		0x18		/* eMMC control */
#घोषणा   SDHCI_CDNS_HRS06_TUNE_UP		BIT(15)
#घोषणा   SDHCI_CDNS_HRS06_TUNE			GENMASK(13, 8)
#घोषणा   SDHCI_CDNS_HRS06_MODE			GENMASK(2, 0)
#घोषणा   SDHCI_CDNS_HRS06_MODE_SD		0x0
#घोषणा   SDHCI_CDNS_HRS06_MODE_MMC_SDR		0x2
#घोषणा   SDHCI_CDNS_HRS06_MODE_MMC_DDR		0x3
#घोषणा   SDHCI_CDNS_HRS06_MODE_MMC_HS200	0x4
#घोषणा   SDHCI_CDNS_HRS06_MODE_MMC_HS400	0x5
#घोषणा   SDHCI_CDNS_HRS06_MODE_MMC_HS400ES	0x6

/* SRS - Slot Register Set (SDHCI-compatible) */
#घोषणा SDHCI_CDNS_SRS_BASE		0x200

/* PHY */
#घोषणा SDHCI_CDNS_PHY_DLY_SD_HS	0x00
#घोषणा SDHCI_CDNS_PHY_DLY_SD_DEFAULT	0x01
#घोषणा SDHCI_CDNS_PHY_DLY_UHS_SDR12	0x02
#घोषणा SDHCI_CDNS_PHY_DLY_UHS_SDR25	0x03
#घोषणा SDHCI_CDNS_PHY_DLY_UHS_SDR50	0x04
#घोषणा SDHCI_CDNS_PHY_DLY_UHS_DDR50	0x05
#घोषणा SDHCI_CDNS_PHY_DLY_EMMC_LEGACY	0x06
#घोषणा SDHCI_CDNS_PHY_DLY_EMMC_SDR	0x07
#घोषणा SDHCI_CDNS_PHY_DLY_EMMC_DDR	0x08
#घोषणा SDHCI_CDNS_PHY_DLY_SDCLK	0x0b
#घोषणा SDHCI_CDNS_PHY_DLY_HSMMC	0x0c
#घोषणा SDHCI_CDNS_PHY_DLY_STROBE	0x0d

/*
 * The tuned val रेजिस्टर is 6 bit-wide, but not the whole of the range is
 * available.  The range 0-42 seems to be available (then 43 wraps around to 0)
 * but I am not quite sure अगर it is official.  Use only 0 to 39 क्रम safety.
 */
#घोषणा SDHCI_CDNS_MAX_TUNING_LOOP	40

काष्ठा sdhci_cdns_phy_param अणु
	u8 addr;
	u8 data;
पूर्ण;

काष्ठा sdhci_cdns_priv अणु
	व्योम __iomem *hrs_addr;
	bool enhanced_strobe;
	अचिन्हित पूर्णांक nr_phy_params;
	काष्ठा sdhci_cdns_phy_param phy_params[];
पूर्ण;

काष्ठा sdhci_cdns_phy_cfg अणु
	स्थिर अक्षर *property;
	u8 addr;
पूर्ण;

अटल स्थिर काष्ठा sdhci_cdns_phy_cfg sdhci_cdns_phy_cfgs[] = अणु
	अणु "cdns,phy-input-delay-sd-highspeed", SDHCI_CDNS_PHY_DLY_SD_HS, पूर्ण,
	अणु "cdns,phy-input-delay-legacy", SDHCI_CDNS_PHY_DLY_SD_DEFAULT, पूर्ण,
	अणु "cdns,phy-input-delay-sd-uhs-sdr12", SDHCI_CDNS_PHY_DLY_UHS_SDR12, पूर्ण,
	अणु "cdns,phy-input-delay-sd-uhs-sdr25", SDHCI_CDNS_PHY_DLY_UHS_SDR25, पूर्ण,
	अणु "cdns,phy-input-delay-sd-uhs-sdr50", SDHCI_CDNS_PHY_DLY_UHS_SDR50, पूर्ण,
	अणु "cdns,phy-input-delay-sd-uhs-ddr50", SDHCI_CDNS_PHY_DLY_UHS_DDR50, पूर्ण,
	अणु "cdns,phy-input-delay-mmc-highspeed", SDHCI_CDNS_PHY_DLY_EMMC_SDR, पूर्ण,
	अणु "cdns,phy-input-delay-mmc-ddr", SDHCI_CDNS_PHY_DLY_EMMC_DDR, पूर्ण,
	अणु "cdns,phy-dll-delay-sdclk", SDHCI_CDNS_PHY_DLY_SDCLK, पूर्ण,
	अणु "cdns,phy-dll-delay-sdclk-hsmmc", SDHCI_CDNS_PHY_DLY_HSMMC, पूर्ण,
	अणु "cdns,phy-dll-delay-strobe", SDHCI_CDNS_PHY_DLY_STROBE, पूर्ण,
पूर्ण;

अटल पूर्णांक sdhci_cdns_ग_लिखो_phy_reg(काष्ठा sdhci_cdns_priv *priv,
				    u8 addr, u8 data)
अणु
	व्योम __iomem *reg = priv->hrs_addr + SDHCI_CDNS_HRS04;
	u32 पंचांगp;
	पूर्णांक ret;

	ret = पढ़ोl_poll_समयout(reg, पंचांगp, !(पंचांगp & SDHCI_CDNS_HRS04_ACK),
				 0, 10);
	अगर (ret)
		वापस ret;

	पंचांगp = FIELD_PREP(SDHCI_CDNS_HRS04_WDATA, data) |
	      FIELD_PREP(SDHCI_CDNS_HRS04_ADDR, addr);
	ग_लिखोl(पंचांगp, reg);

	पंचांगp |= SDHCI_CDNS_HRS04_WR;
	ग_लिखोl(पंचांगp, reg);

	ret = पढ़ोl_poll_समयout(reg, पंचांगp, पंचांगp & SDHCI_CDNS_HRS04_ACK, 0, 10);
	अगर (ret)
		वापस ret;

	पंचांगp &= ~SDHCI_CDNS_HRS04_WR;
	ग_लिखोl(पंचांगp, reg);

	ret = पढ़ोl_poll_समयout(reg, पंचांगp, !(पंचांगp & SDHCI_CDNS_HRS04_ACK),
				 0, 10);

	वापस ret;
पूर्ण

अटल अचिन्हित पूर्णांक sdhci_cdns_phy_param_count(काष्ठा device_node *np)
अणु
	अचिन्हित पूर्णांक count = 0;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(sdhci_cdns_phy_cfgs); i++)
		अगर (of_property_पढ़ो_bool(np, sdhci_cdns_phy_cfgs[i].property))
			count++;

	वापस count;
पूर्ण

अटल व्योम sdhci_cdns_phy_param_parse(काष्ठा device_node *np,
				       काष्ठा sdhci_cdns_priv *priv)
अणु
	काष्ठा sdhci_cdns_phy_param *p = priv->phy_params;
	u32 val;
	पूर्णांक ret, i;

	क्रम (i = 0; i < ARRAY_SIZE(sdhci_cdns_phy_cfgs); i++) अणु
		ret = of_property_पढ़ो_u32(np, sdhci_cdns_phy_cfgs[i].property,
					   &val);
		अगर (ret)
			जारी;

		p->addr = sdhci_cdns_phy_cfgs[i].addr;
		p->data = val;
		p++;
	पूर्ण
पूर्ण

अटल पूर्णांक sdhci_cdns_phy_init(काष्ठा sdhci_cdns_priv *priv)
अणु
	पूर्णांक ret, i;

	क्रम (i = 0; i < priv->nr_phy_params; i++) अणु
		ret = sdhci_cdns_ग_लिखो_phy_reg(priv, priv->phy_params[i].addr,
					       priv->phy_params[i].data);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम *sdhci_cdns_priv(काष्ठा sdhci_host *host)
अणु
	काष्ठा sdhci_pltfm_host *pltfm_host = sdhci_priv(host);

	वापस sdhci_pltfm_priv(pltfm_host);
पूर्ण

अटल अचिन्हित पूर्णांक sdhci_cdns_get_समयout_घड़ी(काष्ठा sdhci_host *host)
अणु
	/*
	 * Cadence's spec says the Timeout Clock Frequency is the same as the
	 * Base Clock Frequency.
	 */
	वापस host->max_clk;
पूर्ण

अटल व्योम sdhci_cdns_set_emmc_mode(काष्ठा sdhci_cdns_priv *priv, u32 mode)
अणु
	u32 पंचांगp;

	/* The speed mode क्रम eMMC is selected by HRS06 रेजिस्टर */
	पंचांगp = पढ़ोl(priv->hrs_addr + SDHCI_CDNS_HRS06);
	पंचांगp &= ~SDHCI_CDNS_HRS06_MODE;
	पंचांगp |= FIELD_PREP(SDHCI_CDNS_HRS06_MODE, mode);
	ग_लिखोl(पंचांगp, priv->hrs_addr + SDHCI_CDNS_HRS06);
पूर्ण

अटल u32 sdhci_cdns_get_emmc_mode(काष्ठा sdhci_cdns_priv *priv)
अणु
	u32 पंचांगp;

	पंचांगp = पढ़ोl(priv->hrs_addr + SDHCI_CDNS_HRS06);
	वापस FIELD_GET(SDHCI_CDNS_HRS06_MODE, पंचांगp);
पूर्ण

अटल पूर्णांक sdhci_cdns_set_tune_val(काष्ठा sdhci_host *host, अचिन्हित पूर्णांक val)
अणु
	काष्ठा sdhci_cdns_priv *priv = sdhci_cdns_priv(host);
	व्योम __iomem *reg = priv->hrs_addr + SDHCI_CDNS_HRS06;
	u32 पंचांगp;
	पूर्णांक i, ret;

	अगर (WARN_ON(!FIELD_FIT(SDHCI_CDNS_HRS06_TUNE, val)))
		वापस -EINVAL;

	पंचांगp = पढ़ोl(reg);
	पंचांगp &= ~SDHCI_CDNS_HRS06_TUNE;
	पंचांगp |= FIELD_PREP(SDHCI_CDNS_HRS06_TUNE, val);

	/*
	 * Workaround क्रम IP errata:
	 * The IP6116 SD/eMMC PHY design has a timing issue on receive data
	 * path. Send tune request twice.
	 */
	क्रम (i = 0; i < 2; i++) अणु
		पंचांगp |= SDHCI_CDNS_HRS06_TUNE_UP;
		ग_लिखोl(पंचांगp, reg);

		ret = पढ़ोl_poll_समयout(reg, पंचांगp,
					 !(पंचांगp & SDHCI_CDNS_HRS06_TUNE_UP),
					 0, 1);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * In SD mode, software must not use the hardware tuning and instead perक्रमm
 * an almost identical procedure to eMMC.
 */
अटल पूर्णांक sdhci_cdns_execute_tuning(काष्ठा sdhci_host *host, u32 opcode)
अणु
	पूर्णांक cur_streak = 0;
	पूर्णांक max_streak = 0;
	पूर्णांक end_of_streak = 0;
	पूर्णांक i;

	/*
	 * Do not execute tuning क्रम UHS_SDR50 or UHS_DDR50.
	 * The delay is set by probe, based on the DT properties.
	 */
	अगर (host->timing != MMC_TIMING_MMC_HS200 &&
	    host->timing != MMC_TIMING_UHS_SDR104)
		वापस 0;

	क्रम (i = 0; i < SDHCI_CDNS_MAX_TUNING_LOOP; i++) अणु
		अगर (sdhci_cdns_set_tune_val(host, i) ||
		    mmc_send_tuning(host->mmc, opcode, शून्य)) अणु /* bad */
			cur_streak = 0;
		पूर्ण अन्यथा अणु /* good */
			cur_streak++;
			अगर (cur_streak > max_streak) अणु
				max_streak = cur_streak;
				end_of_streak = i;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (!max_streak) अणु
		dev_err(mmc_dev(host->mmc), "no tuning point found\n");
		वापस -EIO;
	पूर्ण

	वापस sdhci_cdns_set_tune_val(host, end_of_streak - max_streak / 2);
पूर्ण

अटल व्योम sdhci_cdns_set_uhs_संकेतing(काष्ठा sdhci_host *host,
					 अचिन्हित पूर्णांक timing)
अणु
	काष्ठा sdhci_cdns_priv *priv = sdhci_cdns_priv(host);
	u32 mode;

	चयन (timing) अणु
	हाल MMC_TIMING_MMC_HS:
		mode = SDHCI_CDNS_HRS06_MODE_MMC_SDR;
		अवरोध;
	हाल MMC_TIMING_MMC_DDR52:
		mode = SDHCI_CDNS_HRS06_MODE_MMC_DDR;
		अवरोध;
	हाल MMC_TIMING_MMC_HS200:
		mode = SDHCI_CDNS_HRS06_MODE_MMC_HS200;
		अवरोध;
	हाल MMC_TIMING_MMC_HS400:
		अगर (priv->enhanced_strobe)
			mode = SDHCI_CDNS_HRS06_MODE_MMC_HS400ES;
		अन्यथा
			mode = SDHCI_CDNS_HRS06_MODE_MMC_HS400;
		अवरोध;
	शेष:
		mode = SDHCI_CDNS_HRS06_MODE_SD;
		अवरोध;
	पूर्ण

	sdhci_cdns_set_emmc_mode(priv, mode);

	/* For SD, fall back to the शेष handler */
	अगर (mode == SDHCI_CDNS_HRS06_MODE_SD)
		sdhci_set_uhs_संकेतing(host, timing);
पूर्ण

अटल स्थिर काष्ठा sdhci_ops sdhci_cdns_ops = अणु
	.set_घड़ी = sdhci_set_घड़ी,
	.get_समयout_घड़ी = sdhci_cdns_get_समयout_घड़ी,
	.set_bus_width = sdhci_set_bus_width,
	.reset = sdhci_reset,
	.platक्रमm_execute_tuning = sdhci_cdns_execute_tuning,
	.set_uhs_संकेतing = sdhci_cdns_set_uhs_संकेतing,
पूर्ण;

अटल स्थिर काष्ठा sdhci_pltfm_data sdhci_cdns_uniphier_pltfm_data = अणु
	.ops = &sdhci_cdns_ops,
	.quirks2 = SDHCI_QUIRK2_PRESET_VALUE_BROKEN,
पूर्ण;

अटल स्थिर काष्ठा sdhci_pltfm_data sdhci_cdns_pltfm_data = अणु
	.ops = &sdhci_cdns_ops,
पूर्ण;

अटल व्योम sdhci_cdns_hs400_enhanced_strobe(काष्ठा mmc_host *mmc,
					     काष्ठा mmc_ios *ios)
अणु
	काष्ठा sdhci_host *host = mmc_priv(mmc);
	काष्ठा sdhci_cdns_priv *priv = sdhci_cdns_priv(host);
	u32 mode;

	priv->enhanced_strobe = ios->enhanced_strobe;

	mode = sdhci_cdns_get_emmc_mode(priv);

	अगर (mode == SDHCI_CDNS_HRS06_MODE_MMC_HS400 && ios->enhanced_strobe)
		sdhci_cdns_set_emmc_mode(priv,
					 SDHCI_CDNS_HRS06_MODE_MMC_HS400ES);

	अगर (mode == SDHCI_CDNS_HRS06_MODE_MMC_HS400ES && !ios->enhanced_strobe)
		sdhci_cdns_set_emmc_mode(priv,
					 SDHCI_CDNS_HRS06_MODE_MMC_HS400);
पूर्ण

अटल पूर्णांक sdhci_cdns_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sdhci_host *host;
	स्थिर काष्ठा sdhci_pltfm_data *data;
	काष्ठा sdhci_pltfm_host *pltfm_host;
	काष्ठा sdhci_cdns_priv *priv;
	काष्ठा clk *clk;
	अचिन्हित पूर्णांक nr_phy_params;
	पूर्णांक ret;
	काष्ठा device *dev = &pdev->dev;
	अटल स्थिर u16 version = SDHCI_SPEC_400 << SDHCI_SPEC_VER_SHIFT;

	clk = devm_clk_get(dev, शून्य);
	अगर (IS_ERR(clk))
		वापस PTR_ERR(clk);

	ret = clk_prepare_enable(clk);
	अगर (ret)
		वापस ret;

	data = of_device_get_match_data(dev);
	अगर (!data)
		data = &sdhci_cdns_pltfm_data;

	nr_phy_params = sdhci_cdns_phy_param_count(dev->of_node);
	host = sdhci_pltfm_init(pdev, data,
				काष्ठा_size(priv, phy_params, nr_phy_params));
	अगर (IS_ERR(host)) अणु
		ret = PTR_ERR(host);
		जाओ disable_clk;
	पूर्ण

	pltfm_host = sdhci_priv(host);
	pltfm_host->clk = clk;

	priv = sdhci_pltfm_priv(pltfm_host);
	priv->nr_phy_params = nr_phy_params;
	priv->hrs_addr = host->ioaddr;
	priv->enhanced_strobe = false;
	host->ioaddr += SDHCI_CDNS_SRS_BASE;
	host->mmc_host_ops.hs400_enhanced_strobe =
				sdhci_cdns_hs400_enhanced_strobe;
	sdhci_enable_v4_mode(host);
	__sdhci_पढ़ो_caps(host, &version, शून्य, शून्य);

	sdhci_get_of_property(pdev);

	ret = mmc_of_parse(host->mmc);
	अगर (ret)
		जाओ मुक्त;

	sdhci_cdns_phy_param_parse(dev->of_node, priv);

	ret = sdhci_cdns_phy_init(priv);
	अगर (ret)
		जाओ मुक्त;

	ret = sdhci_add_host(host);
	अगर (ret)
		जाओ मुक्त;

	वापस 0;
मुक्त:
	sdhci_pltfm_मुक्त(pdev);
disable_clk:
	clk_disable_unprepare(clk);

	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक sdhci_cdns_resume(काष्ठा device *dev)
अणु
	काष्ठा sdhci_host *host = dev_get_drvdata(dev);
	काष्ठा sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	काष्ठा sdhci_cdns_priv *priv = sdhci_pltfm_priv(pltfm_host);
	पूर्णांक ret;

	ret = clk_prepare_enable(pltfm_host->clk);
	अगर (ret)
		वापस ret;

	ret = sdhci_cdns_phy_init(priv);
	अगर (ret)
		जाओ disable_clk;

	ret = sdhci_resume_host(host);
	अगर (ret)
		जाओ disable_clk;

	वापस 0;

disable_clk:
	clk_disable_unprepare(pltfm_host->clk);

	वापस ret;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा dev_pm_ops sdhci_cdns_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(sdhci_pltfm_suspend, sdhci_cdns_resume)
पूर्ण;

अटल स्थिर काष्ठा of_device_id sdhci_cdns_match[] = अणु
	अणु
		.compatible = "socionext,uniphier-sd4hc",
		.data = &sdhci_cdns_uniphier_pltfm_data,
	पूर्ण,
	अणु .compatible = "cdns,sd4hc" पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, sdhci_cdns_match);

अटल काष्ठा platक्रमm_driver sdhci_cdns_driver = अणु
	.driver = अणु
		.name = "sdhci-cdns",
		.probe_type = PROBE_PREFER_ASYNCHRONOUS,
		.pm = &sdhci_cdns_pm_ops,
		.of_match_table = sdhci_cdns_match,
	पूर्ण,
	.probe = sdhci_cdns_probe,
	.हटाओ = sdhci_pltfm_unरेजिस्टर,
पूर्ण;
module_platक्रमm_driver(sdhci_cdns_driver);

MODULE_AUTHOR("Masahiro Yamada <yamada.masahiro@socionext.com>");
MODULE_DESCRIPTION("Cadence SD/SDIO/eMMC Host Controller Driver");
MODULE_LICENSE("GPL");
