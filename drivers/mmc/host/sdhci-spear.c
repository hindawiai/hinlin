<शैली गुरु>
/*
 * drivers/mmc/host/sdhci-spear.c
 *
 * Support of SDHCI platक्रमm devices क्रम spear soc family
 *
 * Copyright (C) 2010 ST Microelectronics
 * Viresh Kumar <vireshk@kernel.org>
 *
 * Inspired by sdhci-pltfm.c
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2. This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/module.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm.h>
#समावेश <linux/slab.h>
#समावेश <linux/mmc/host.h>
#समावेश <linux/mmc/slot-gpपन.स>
#समावेश <linux/पन.स>
#समावेश "sdhci.h"

काष्ठा spear_sdhci अणु
	काष्ठा clk *clk;
पूर्ण;

/* sdhci ops */
अटल स्थिर काष्ठा sdhci_ops sdhci_pltfm_ops = अणु
	.set_घड़ी = sdhci_set_घड़ी,
	.set_bus_width = sdhci_set_bus_width,
	.reset = sdhci_reset,
	.set_uhs_संकेतing = sdhci_set_uhs_संकेतing,
पूर्ण;

अटल पूर्णांक sdhci_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sdhci_host *host;
	काष्ठा spear_sdhci *sdhci;
	काष्ठा device *dev;
	पूर्णांक ret;

	dev = pdev->dev.parent ? pdev->dev.parent : &pdev->dev;
	host = sdhci_alloc_host(dev, माप(*sdhci));
	अगर (IS_ERR(host)) अणु
		ret = PTR_ERR(host);
		dev_dbg(&pdev->dev, "cannot allocate memory for sdhci\n");
		जाओ err;
	पूर्ण

	host->ioaddr = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(host->ioaddr)) अणु
		ret = PTR_ERR(host->ioaddr);
		dev_dbg(&pdev->dev, "unable to map iomem: %d\n", ret);
		जाओ err_host;
	पूर्ण

	host->hw_name = "sdhci";
	host->ops = &sdhci_pltfm_ops;
	host->irq = platक्रमm_get_irq(pdev, 0);
	अगर (host->irq <= 0) अणु
		ret = -EINVAL;
		जाओ err_host;
	पूर्ण
	host->quirks = SDHCI_QUIRK_BROKEN_ADMA;

	sdhci = sdhci_priv(host);

	/* clk enable */
	sdhci->clk = devm_clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(sdhci->clk)) अणु
		ret = PTR_ERR(sdhci->clk);
		dev_dbg(&pdev->dev, "Error getting clock\n");
		जाओ err_host;
	पूर्ण

	ret = clk_prepare_enable(sdhci->clk);
	अगर (ret) अणु
		dev_dbg(&pdev->dev, "Error enabling clock\n");
		जाओ err_host;
	पूर्ण

	ret = clk_set_rate(sdhci->clk, 50000000);
	अगर (ret)
		dev_dbg(&pdev->dev, "Error setting desired clk, clk=%lu\n",
				clk_get_rate(sdhci->clk));

	/*
	 * It is optional to use GPIOs क्रम sdhci card detection. If we
	 * find a descriptor using slot GPIO, we use it.
	 */
	ret = mmc_gpiod_request_cd(host->mmc, "cd", 0, false, 0);
	अगर (ret == -EPROBE_DEFER)
		जाओ disable_clk;

	ret = sdhci_add_host(host);
	अगर (ret)
		जाओ disable_clk;

	platक्रमm_set_drvdata(pdev, host);

	वापस 0;

disable_clk:
	clk_disable_unprepare(sdhci->clk);
err_host:
	sdhci_मुक्त_host(host);
err:
	dev_err(&pdev->dev, "spear-sdhci probe failed: %d\n", ret);
	वापस ret;
पूर्ण

अटल पूर्णांक sdhci_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sdhci_host *host = platक्रमm_get_drvdata(pdev);
	काष्ठा spear_sdhci *sdhci = sdhci_priv(host);
	पूर्णांक dead = 0;
	u32 scratch;

	scratch = पढ़ोl(host->ioaddr + SDHCI_INT_STATUS);
	अगर (scratch == (u32)-1)
		dead = 1;

	sdhci_हटाओ_host(host, dead);
	clk_disable_unprepare(sdhci->clk);
	sdhci_मुक्त_host(host);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक sdhci_suspend(काष्ठा device *dev)
अणु
	काष्ठा sdhci_host *host = dev_get_drvdata(dev);
	काष्ठा spear_sdhci *sdhci = sdhci_priv(host);
	पूर्णांक ret;

	अगर (host->tuning_mode != SDHCI_TUNING_MODE_3)
		mmc_retune_needed(host->mmc);

	ret = sdhci_suspend_host(host);
	अगर (!ret)
		clk_disable(sdhci->clk);

	वापस ret;
पूर्ण

अटल पूर्णांक sdhci_resume(काष्ठा device *dev)
अणु
	काष्ठा sdhci_host *host = dev_get_drvdata(dev);
	काष्ठा spear_sdhci *sdhci = sdhci_priv(host);
	पूर्णांक ret;

	ret = clk_enable(sdhci->clk);
	अगर (ret) अणु
		dev_dbg(dev, "Resume: Error enabling clock\n");
		वापस ret;
	पूर्ण

	वापस sdhci_resume_host(host);
पूर्ण
#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(sdhci_pm_ops, sdhci_suspend, sdhci_resume);

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id sdhci_spear_id_table[] = अणु
	अणु .compatible = "st,spear300-sdhci" पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, sdhci_spear_id_table);
#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver sdhci_driver = अणु
	.driver = अणु
		.name	= "sdhci",
		.probe_type = PROBE_PREFER_ASYNCHRONOUS,
		.pm	= &sdhci_pm_ops,
		.of_match_table = of_match_ptr(sdhci_spear_id_table),
	पूर्ण,
	.probe		= sdhci_probe,
	.हटाओ		= sdhci_हटाओ,
पूर्ण;

module_platक्रमm_driver(sdhci_driver);

MODULE_DESCRIPTION("SPEAr Secure Digital Host Controller Interface driver");
MODULE_AUTHOR("Viresh Kumar <vireshk@kernel.org>");
MODULE_LICENSE("GPL v2");
