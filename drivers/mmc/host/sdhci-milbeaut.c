<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2013 - 2015 Fujitsu Semiconductor, Ltd
 *              Vincent Yang <vincent.yang@tw.fujitsu.com>
 * Copyright (C) 2015 Linaro Ltd  Andy Green <andy.green@linaro.org>
 * Copyright (C) 2019 Socionext Inc.
 *              Takao Orito <orito.takao@socionext.com>
 */

#समावेश <linux/bits.h>
#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/err.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/property.h>

#समावेश "sdhci-pltfm.h"
#समावेश "sdhci_f_sdh30.h"

/* milbeaut bridge controller रेजिस्टर */
#घोषणा MLB_SOFT_RESET		0x0200
#घोषणा  MLB_SOFT_RESET_RSTX		BIT(0)

#घोषणा MLB_WP_CD_LED_SET	0x0210
#घोषणा  MLB_WP_CD_LED_SET_LED_INV  BIT(2)

#घोषणा MLB_CR_SET			0x0220
#घोषणा  MLB_CR_SET_CR_TOCLKUNIT       BIT(24)
#घोषणा  MLB_CR_SET_CR_TOCLKFREQ_SFT   (16)
#घोषणा  MLB_CR_SET_CR_TOCLKFREQ_MASK  (0x3F << MLB_CR_SET_CR_TOCLKFREQ_SFT)
#घोषणा  MLB_CR_SET_CR_BCLKFREQ_SFT    (8)
#घोषणा  MLB_CR_SET_CR_BCLKFREQ_MASK   (0xFF << MLB_CR_SET_CR_BCLKFREQ_SFT)
#घोषणा  MLB_CR_SET_CR_RTUNTIMER_SFT   (4)
#घोषणा  MLB_CR_SET_CR_RTUNTIMER_MASK  (0xF << MLB_CR_SET_CR_RTUNTIMER_SFT)

#घोषणा MLB_SD_TOCLK_I_DIV  16
#घोषणा MLB_TOCLKFREQ_UNIT_THRES    16000000
#घोषणा MLB_CAL_TOCLKFREQ_MHZ(rate) (rate / MLB_SD_TOCLK_I_DIV / 1000000)
#घोषणा MLB_CAL_TOCLKFREQ_KHZ(rate) (rate / MLB_SD_TOCLK_I_DIV / 1000)
#घोषणा MLB_TOCLKFREQ_MAX   63
#घोषणा MLB_TOCLKFREQ_MIN    1

#घोषणा MLB_SD_BCLK_I_DIV   4
#घोषणा MLB_CAL_BCLKFREQ(rate)  (rate / MLB_SD_BCLK_I_DIV / 1000000)
#घोषणा MLB_BCLKFREQ_MAX        255
#घोषणा MLB_BCLKFREQ_MIN          1

#घोषणा MLB_CDR_SET			0x0230
#घोषणा MLB_CDR_SET_CLK2POW16	3

काष्ठा f_sdhost_priv अणु
	काष्ठा clk *clk_अगरace;
	काष्ठा clk *clk;
	काष्ठा device *dev;
	bool enable_cmd_dat_delay;
पूर्ण;

अटल व्योम sdhci_milbeaut_soft_voltage_चयन(काष्ठा sdhci_host *host)
अणु
	u32 ctrl = 0;

	usleep_range(2500, 3000);
	ctrl = sdhci_पढ़ोl(host, F_SDH30_IO_CONTROL2);
	ctrl |= F_SDH30_CRES_O_DN;
	sdhci_ग_लिखोl(host, ctrl, F_SDH30_IO_CONTROL2);
	ctrl |= F_SDH30_MSEL_O_1_8;
	sdhci_ग_लिखोl(host, ctrl, F_SDH30_IO_CONTROL2);

	ctrl &= ~F_SDH30_CRES_O_DN;
	sdhci_ग_लिखोl(host, ctrl, F_SDH30_IO_CONTROL2);
	usleep_range(2500, 3000);

	ctrl = sdhci_पढ़ोl(host, F_SDH30_TUNING_SETTING);
	ctrl |= F_SDH30_CMD_CHK_DIS;
	sdhci_ग_लिखोl(host, ctrl, F_SDH30_TUNING_SETTING);
पूर्ण

अटल अचिन्हित पूर्णांक sdhci_milbeaut_get_min_घड़ी(काष्ठा sdhci_host *host)
अणु
	वापस F_SDH30_MIN_CLOCK;
पूर्ण

अटल व्योम sdhci_milbeaut_reset(काष्ठा sdhci_host *host, u8 mask)
अणु
	काष्ठा f_sdhost_priv *priv = sdhci_priv(host);
	u16 clk;
	u32 ctl;
	kसमय_प्रकार समयout;

	clk = sdhci_पढ़ोw(host, SDHCI_CLOCK_CONTROL);
	clk = (clk & ~SDHCI_CLOCK_CARD_EN) | SDHCI_CLOCK_INT_EN;
	sdhci_ग_लिखोw(host, clk, SDHCI_CLOCK_CONTROL);

	sdhci_reset(host, mask);

	clk |= SDHCI_CLOCK_CARD_EN;
	sdhci_ग_लिखोw(host, clk, SDHCI_CLOCK_CONTROL);

	समयout = kसमय_add_ms(kसमय_get(), 10);
	जबतक (1) अणु
		bool समयकरोut = kसमय_after(kसमय_get(), समयout);

		clk = sdhci_पढ़ोw(host, SDHCI_CLOCK_CONTROL);
		अगर (clk & SDHCI_CLOCK_INT_STABLE)
			अवरोध;
		अगर (समयकरोut) अणु
			pr_err("%s: Internal clock never stabilised.\n",
				mmc_hostname(host->mmc));
			sdhci_dumpregs(host);
			वापस;
		पूर्ण
		udelay(10);
	पूर्ण

	अगर (priv->enable_cmd_dat_delay) अणु
		ctl = sdhci_पढ़ोl(host, F_SDH30_ESD_CONTROL);
		ctl |= F_SDH30_CMD_DAT_DELAY;
		sdhci_ग_लिखोl(host, ctl, F_SDH30_ESD_CONTROL);
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा sdhci_ops sdhci_milbeaut_ops = अणु
	.voltage_चयन = sdhci_milbeaut_soft_voltage_चयन,
	.get_min_घड़ी = sdhci_milbeaut_get_min_घड़ी,
	.reset = sdhci_milbeaut_reset,
	.set_घड़ी = sdhci_set_घड़ी,
	.set_bus_width = sdhci_set_bus_width,
	.set_uhs_संकेतing = sdhci_set_uhs_संकेतing,
	.set_घातer = sdhci_set_घातer_and_bus_voltage,
पूर्ण;

अटल व्योम sdhci_milbeaut_bridge_reset(काष्ठा sdhci_host *host,
						पूर्णांक reset_flag)
अणु
	अगर (reset_flag)
		sdhci_ग_लिखोl(host, 0, MLB_SOFT_RESET);
	अन्यथा
		sdhci_ग_लिखोl(host, MLB_SOFT_RESET_RSTX, MLB_SOFT_RESET);
पूर्ण

अटल व्योम sdhci_milbeaut_bridge_init(काष्ठा sdhci_host *host,
						पूर्णांक rate)
अणु
	u32 val, clk;

	/* IO_SDIO_CR_SET should be set जबतक reset */
	val = sdhci_पढ़ोl(host, MLB_CR_SET);
	val &= ~(MLB_CR_SET_CR_TOCLKFREQ_MASK | MLB_CR_SET_CR_TOCLKUNIT |
			MLB_CR_SET_CR_BCLKFREQ_MASK);
	अगर (rate >= MLB_TOCLKFREQ_UNIT_THRES) अणु
		clk = MLB_CAL_TOCLKFREQ_MHZ(rate);
		clk = min_t(u32, MLB_TOCLKFREQ_MAX, clk);
		val |= MLB_CR_SET_CR_TOCLKUNIT |
			(clk << MLB_CR_SET_CR_TOCLKFREQ_SFT);
	पूर्ण अन्यथा अणु
		clk = MLB_CAL_TOCLKFREQ_KHZ(rate);
		clk = min_t(u32, MLB_TOCLKFREQ_MAX, clk);
		clk = max_t(u32, MLB_TOCLKFREQ_MIN, clk);
		val |= clk << MLB_CR_SET_CR_TOCLKFREQ_SFT;
	पूर्ण

	clk = MLB_CAL_BCLKFREQ(rate);
	clk = min_t(u32, MLB_BCLKFREQ_MAX, clk);
	clk = max_t(u32, MLB_BCLKFREQ_MIN, clk);
	val |=  clk << MLB_CR_SET_CR_BCLKFREQ_SFT;
	val &= ~MLB_CR_SET_CR_RTUNTIMER_MASK;
	sdhci_ग_लिखोl(host, val, MLB_CR_SET);

	sdhci_ग_लिखोl(host, MLB_CDR_SET_CLK2POW16, MLB_CDR_SET);

	sdhci_ग_लिखोl(host, MLB_WP_CD_LED_SET_LED_INV, MLB_WP_CD_LED_SET);
पूर्ण

अटल व्योम sdhci_milbeaut_venकरोr_init(काष्ठा sdhci_host *host)
अणु
	काष्ठा f_sdhost_priv *priv = sdhci_priv(host);
	u32 ctl;

	ctl = sdhci_पढ़ोl(host, F_SDH30_IO_CONTROL2);
	ctl |= F_SDH30_CRES_O_DN;
	sdhci_ग_लिखोl(host, ctl, F_SDH30_IO_CONTROL2);
	ctl &= ~F_SDH30_MSEL_O_1_8;
	sdhci_ग_लिखोl(host, ctl, F_SDH30_IO_CONTROL2);
	ctl &= ~F_SDH30_CRES_O_DN;
	sdhci_ग_लिखोl(host, ctl, F_SDH30_IO_CONTROL2);

	ctl = sdhci_पढ़ोw(host, F_SDH30_AHB_CONFIG);
	ctl |= F_SDH30_SIN | F_SDH30_AHB_INCR_16 | F_SDH30_AHB_INCR_8 |
	       F_SDH30_AHB_INCR_4;
	ctl &= ~(F_SDH30_AHB_BIGED | F_SDH30_BUSLOCK_EN);
	sdhci_ग_लिखोw(host, ctl, F_SDH30_AHB_CONFIG);

	अगर (priv->enable_cmd_dat_delay) अणु
		ctl = sdhci_पढ़ोl(host, F_SDH30_ESD_CONTROL);
		ctl |= F_SDH30_CMD_DAT_DELAY;
		sdhci_ग_लिखोl(host, ctl, F_SDH30_ESD_CONTROL);
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा of_device_id mlb_dt_ids[] = अणु
	अणु
		.compatible = "socionext,milbeaut-m10v-sdhci-3.0",
	पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, mlb_dt_ids);

अटल व्योम sdhci_milbeaut_init(काष्ठा sdhci_host *host)
अणु
	काष्ठा f_sdhost_priv *priv = sdhci_priv(host);
	पूर्णांक rate = clk_get_rate(priv->clk);
	u16 ctl;

	sdhci_milbeaut_bridge_reset(host, 0);

	ctl = sdhci_पढ़ोw(host, SDHCI_CLOCK_CONTROL);
	ctl &= ~(SDHCI_CLOCK_CARD_EN | SDHCI_CLOCK_INT_EN);
	sdhci_ग_लिखोw(host, ctl, SDHCI_CLOCK_CONTROL);

	sdhci_milbeaut_bridge_reset(host, 1);

	sdhci_milbeaut_bridge_init(host, rate);
	sdhci_milbeaut_bridge_reset(host, 0);

	sdhci_milbeaut_venकरोr_init(host);
पूर्ण

अटल पूर्णांक sdhci_milbeaut_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sdhci_host *host;
	काष्ठा device *dev = &pdev->dev;
	पूर्णांक irq, ret = 0;
	काष्ठा f_sdhost_priv *priv;

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस irq;

	host = sdhci_alloc_host(dev, माप(काष्ठा f_sdhost_priv));
	अगर (IS_ERR(host))
		वापस PTR_ERR(host);

	priv = sdhci_priv(host);
	priv->dev = dev;

	host->quirks = SDHCI_QUIRK_NO_ENDATTR_IN_NOPDESC |
			   SDHCI_QUIRK_INVERTED_WRITE_PROTECT |
			   SDHCI_QUIRK_CLOCK_BEFORE_RESET |
			   SDHCI_QUIRK_DELAY_AFTER_POWER;
	host->quirks2 = SDHCI_QUIRK2_SUPPORT_SINGLE |
			SDHCI_QUIRK2_TUNING_WORK_AROUND |
			SDHCI_QUIRK2_PRESET_VALUE_BROKEN;

	priv->enable_cmd_dat_delay = device_property_पढ़ो_bool(dev,
						"fujitsu,cmd-dat-delay-select");

	ret = mmc_of_parse(host->mmc);
	अगर (ret)
		जाओ err;

	platक्रमm_set_drvdata(pdev, host);

	host->hw_name = "f_sdh30";
	host->ops = &sdhci_milbeaut_ops;
	host->irq = irq;

	host->ioaddr = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(host->ioaddr)) अणु
		ret = PTR_ERR(host->ioaddr);
		जाओ err;
	पूर्ण

	अगर (dev_of_node(dev)) अणु
		sdhci_get_of_property(pdev);

		priv->clk_अगरace = devm_clk_get(&pdev->dev, "iface");
		अगर (IS_ERR(priv->clk_अगरace)) अणु
			ret = PTR_ERR(priv->clk_अगरace);
			जाओ err;
		पूर्ण

		ret = clk_prepare_enable(priv->clk_अगरace);
		अगर (ret)
			जाओ err;

		priv->clk = devm_clk_get(&pdev->dev, "core");
		अगर (IS_ERR(priv->clk)) अणु
			ret = PTR_ERR(priv->clk);
			जाओ err_clk;
		पूर्ण

		ret = clk_prepare_enable(priv->clk);
		अगर (ret)
			जाओ err_clk;
	पूर्ण

	sdhci_milbeaut_init(host);

	ret = sdhci_add_host(host);
	अगर (ret)
		जाओ err_add_host;

	वापस 0;

err_add_host:
	clk_disable_unprepare(priv->clk);
err_clk:
	clk_disable_unprepare(priv->clk_अगरace);
err:
	sdhci_मुक्त_host(host);
	वापस ret;
पूर्ण

अटल पूर्णांक sdhci_milbeaut_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sdhci_host *host = platक्रमm_get_drvdata(pdev);
	काष्ठा f_sdhost_priv *priv = sdhci_priv(host);

	sdhci_हटाओ_host(host, पढ़ोl(host->ioaddr + SDHCI_INT_STATUS) ==
			  0xffffffff);

	clk_disable_unprepare(priv->clk_अगरace);
	clk_disable_unprepare(priv->clk);

	sdhci_मुक्त_host(host);
	platक्रमm_set_drvdata(pdev, शून्य);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver sdhci_milbeaut_driver = अणु
	.driver = अणु
		.name = "sdhci-milbeaut",
		.probe_type = PROBE_PREFER_ASYNCHRONOUS,
		.of_match_table = of_match_ptr(mlb_dt_ids),
	पूर्ण,
	.probe	= sdhci_milbeaut_probe,
	.हटाओ	= sdhci_milbeaut_हटाओ,
पूर्ण;

module_platक्रमm_driver(sdhci_milbeaut_driver);

MODULE_DESCRIPTION("MILBEAUT SD Card Controller driver");
MODULE_AUTHOR("Takao Orito <orito.takao@socionext.com>");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:sdhci-milbeaut");
