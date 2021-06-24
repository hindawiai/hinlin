<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * linux/drivers/mmc/host/sdhci_f_sdh30.c
 *
 * Copyright (C) 2013 - 2015 Fujitsu Semiconductor, Ltd
 *              Vincent Yang <vincent.yang@tw.fujitsu.com>
 * Copyright (C) 2015 Linaro Ltd  Andy Green <andy.green@linaro.org>
 */

#समावेश <linux/acpi.h>
#समावेश <linux/err.h>
#समावेश <linux/delay.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/property.h>
#समावेश <linux/clk.h>

#समावेश "sdhci-pltfm.h"
#समावेश "sdhci_f_sdh30.h"

काष्ठा f_sdhost_priv अणु
	काष्ठा clk *clk_अगरace;
	काष्ठा clk *clk;
	u32 venकरोr_hs200;
	काष्ठा device *dev;
	bool enable_cmd_dat_delay;
पूर्ण;

अटल व्योम sdhci_f_sdh30_soft_voltage_चयन(काष्ठा sdhci_host *host)
अणु
	काष्ठा f_sdhost_priv *priv = sdhci_priv(host);
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

	अगर (priv->venकरोr_hs200) अणु
		dev_info(priv->dev, "%s: setting hs200\n", __func__);
		ctrl = sdhci_पढ़ोl(host, F_SDH30_ESD_CONTROL);
		ctrl |= priv->venकरोr_hs200;
		sdhci_ग_लिखोl(host, ctrl, F_SDH30_ESD_CONTROL);
	पूर्ण

	ctrl = sdhci_पढ़ोl(host, F_SDH30_TUNING_SETTING);
	ctrl |= F_SDH30_CMD_CHK_DIS;
	sdhci_ग_लिखोl(host, ctrl, F_SDH30_TUNING_SETTING);
पूर्ण

अटल अचिन्हित पूर्णांक sdhci_f_sdh30_get_min_घड़ी(काष्ठा sdhci_host *host)
अणु
	वापस F_SDH30_MIN_CLOCK;
पूर्ण

अटल व्योम sdhci_f_sdh30_reset(काष्ठा sdhci_host *host, u8 mask)
अणु
	काष्ठा f_sdhost_priv *priv = sdhci_priv(host);
	u32 ctl;

	अगर (sdhci_पढ़ोw(host, SDHCI_CLOCK_CONTROL) == 0)
		sdhci_ग_लिखोw(host, 0xBC01, SDHCI_CLOCK_CONTROL);

	sdhci_reset(host, mask);

	अगर (priv->enable_cmd_dat_delay) अणु
		ctl = sdhci_पढ़ोl(host, F_SDH30_ESD_CONTROL);
		ctl |= F_SDH30_CMD_DAT_DELAY;
		sdhci_ग_लिखोl(host, ctl, F_SDH30_ESD_CONTROL);
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा sdhci_ops sdhci_f_sdh30_ops = अणु
	.voltage_चयन = sdhci_f_sdh30_soft_voltage_चयन,
	.get_min_घड़ी = sdhci_f_sdh30_get_min_घड़ी,
	.reset = sdhci_f_sdh30_reset,
	.set_घड़ी = sdhci_set_घड़ी,
	.set_bus_width = sdhci_set_bus_width,
	.set_uhs_संकेतing = sdhci_set_uhs_संकेतing,
पूर्ण;

अटल पूर्णांक sdhci_f_sdh30_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sdhci_host *host;
	काष्ठा device *dev = &pdev->dev;
	पूर्णांक irq, ctrl = 0, ret = 0;
	काष्ठा f_sdhost_priv *priv;
	u32 reg = 0;

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस irq;

	host = sdhci_alloc_host(dev, माप(काष्ठा f_sdhost_priv));
	अगर (IS_ERR(host))
		वापस PTR_ERR(host);

	priv = sdhci_priv(host);
	priv->dev = dev;

	host->quirks = SDHCI_QUIRK_NO_ENDATTR_IN_NOPDESC |
		       SDHCI_QUIRK_INVERTED_WRITE_PROTECT;
	host->quirks2 = SDHCI_QUIRK2_SUPPORT_SINGLE |
			SDHCI_QUIRK2_TUNING_WORK_AROUND;

	priv->enable_cmd_dat_delay = device_property_पढ़ो_bool(dev,
						"fujitsu,cmd-dat-delay-select");

	ret = mmc_of_parse(host->mmc);
	अगर (ret)
		जाओ err;

	platक्रमm_set_drvdata(pdev, host);

	host->hw_name = "f_sdh30";
	host->ops = &sdhci_f_sdh30_ops;
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

	/* init venकरोr specअगरic regs */
	ctrl = sdhci_पढ़ोw(host, F_SDH30_AHB_CONFIG);
	ctrl |= F_SDH30_SIN | F_SDH30_AHB_INCR_16 | F_SDH30_AHB_INCR_8 |
		F_SDH30_AHB_INCR_4;
	ctrl &= ~(F_SDH30_AHB_BIGED | F_SDH30_BUSLOCK_EN);
	sdhci_ग_लिखोw(host, ctrl, F_SDH30_AHB_CONFIG);

	reg = sdhci_पढ़ोl(host, F_SDH30_ESD_CONTROL);
	sdhci_ग_लिखोl(host, reg & ~F_SDH30_EMMC_RST, F_SDH30_ESD_CONTROL);
	msleep(20);
	sdhci_ग_लिखोl(host, reg | F_SDH30_EMMC_RST, F_SDH30_ESD_CONTROL);

	reg = sdhci_पढ़ोl(host, SDHCI_CAPABILITIES);
	अगर (reg & SDHCI_CAN_DO_8BIT)
		priv->venकरोr_hs200 = F_SDH30_EMMC_HS200;

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

अटल पूर्णांक sdhci_f_sdh30_हटाओ(काष्ठा platक्रमm_device *pdev)
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

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id f_sdh30_dt_ids[] = अणु
	अणु .compatible = "fujitsu,mb86s70-sdhci-3.0" पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, f_sdh30_dt_ids);
#पूर्ण_अगर

#अगर_घोषित CONFIG_ACPI
अटल स्थिर काष्ठा acpi_device_id f_sdh30_acpi_ids[] = अणु
	अणु "SCX0002" पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(acpi, f_sdh30_acpi_ids);
#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver sdhci_f_sdh30_driver = अणु
	.driver = अणु
		.name = "f_sdh30",
		.probe_type = PROBE_PREFER_ASYNCHRONOUS,
		.of_match_table = of_match_ptr(f_sdh30_dt_ids),
		.acpi_match_table = ACPI_PTR(f_sdh30_acpi_ids),
		.pm	= &sdhci_pltfm_pmops,
	पूर्ण,
	.probe	= sdhci_f_sdh30_probe,
	.हटाओ	= sdhci_f_sdh30_हटाओ,
पूर्ण;

module_platक्रमm_driver(sdhci_f_sdh30_driver);

MODULE_DESCRIPTION("F_SDH30 SD Card Controller driver");
MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("FUJITSU SEMICONDUCTOR LTD.");
MODULE_ALIAS("platform:f_sdh30");
