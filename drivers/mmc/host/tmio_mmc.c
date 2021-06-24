<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Driver क्रम the MMC / SD / SDIO cell found in:
 *
 * TC6393XB TC6391XB TC6387XB T7L66XB ASIC3
 *
 * Copyright (C) 2017 Renesas Electronics Corporation
 * Copyright (C) 2017 Horms Solutions, Simon Horman
 * Copyright (C) 2007 Ian Molton
 * Copyright (C) 2004 Ian Molton
 */

#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/mfd/core.h>
#समावेश <linux/mfd/पंचांगपन.स>
#समावेश <linux/mmc/host.h>
#समावेश <linux/module.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/scatterlist.h>

#समावेश "tmio_mmc.h"

/* Registers specअगरic to this variant */
#घोषणा CTL_SDIO_REGS		0x100
#घोषणा CTL_CLK_AND_WAIT_CTL	0x138
#घोषणा CTL_RESET_SDIO		0x1e0

अटल व्योम पंचांगio_mmc_clk_start(काष्ठा पंचांगio_mmc_host *host)
अणु
	sd_ctrl_ग_लिखो16(host, CTL_SD_CARD_CLK_CTL, CLK_CTL_SCLKEN |
		sd_ctrl_पढ़ो16(host, CTL_SD_CARD_CLK_CTL));

	usleep_range(10000, 11000);
	sd_ctrl_ग_लिखो16(host, CTL_CLK_AND_WAIT_CTL, 0x0100);
	usleep_range(10000, 11000);
पूर्ण

अटल व्योम पंचांगio_mmc_clk_stop(काष्ठा पंचांगio_mmc_host *host)
अणु
	sd_ctrl_ग_लिखो16(host, CTL_CLK_AND_WAIT_CTL, 0x0000);
	usleep_range(10000, 11000);

	sd_ctrl_ग_लिखो16(host, CTL_SD_CARD_CLK_CTL, ~CLK_CTL_SCLKEN &
		sd_ctrl_पढ़ो16(host, CTL_SD_CARD_CLK_CTL));

	usleep_range(10000, 11000);
पूर्ण

अटल व्योम पंचांगio_mmc_set_घड़ी(काष्ठा पंचांगio_mmc_host *host,
			       अचिन्हित पूर्णांक new_घड़ी)
अणु
	अचिन्हित पूर्णांक भागisor;
	u32 clk = 0;
	पूर्णांक clk_sel;

	अगर (new_घड़ी == 0) अणु
		पंचांगio_mmc_clk_stop(host);
		वापस;
	पूर्ण

	भागisor = host->pdata->hclk / new_घड़ी;

	/* bit7 set: 1/512, ... bit0 set: 1/4, all bits clear: 1/2 */
	clk_sel = (भागisor <= 1);
	clk = clk_sel ? 0 : (roundup_घात_of_two(भागisor) >> 2);

	host->pdata->set_clk_भाग(host->pdev, clk_sel);

	sd_ctrl_ग_लिखो16(host, CTL_SD_CARD_CLK_CTL, ~CLK_CTL_SCLKEN &
			sd_ctrl_पढ़ो16(host, CTL_SD_CARD_CLK_CTL));
	sd_ctrl_ग_लिखो16(host, CTL_SD_CARD_CLK_CTL, clk & CLK_CTL_DIV_MASK);
	usleep_range(10000, 11000);

	पंचांगio_mmc_clk_start(host);
पूर्ण

अटल व्योम पंचांगio_mmc_reset(काष्ठा पंचांगio_mmc_host *host)
अणु
	sd_ctrl_ग_लिखो16(host, CTL_RESET_SDIO, 0x0000);
	usleep_range(10000, 11000);
	sd_ctrl_ग_लिखो16(host, CTL_RESET_SDIO, 0x0001);
	usleep_range(10000, 11000);
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक पंचांगio_mmc_suspend(काष्ठा device *dev)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	स्थिर काष्ठा mfd_cell *cell = mfd_get_cell(pdev);
	पूर्णांक ret;

	ret = pm_runसमय_क्रमce_suspend(dev);

	/* Tell MFD core it can disable us now.*/
	अगर (!ret && cell->disable)
		cell->disable(pdev);

	वापस ret;
पूर्ण

अटल पूर्णांक पंचांगio_mmc_resume(काष्ठा device *dev)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	स्थिर काष्ठा mfd_cell *cell = mfd_get_cell(pdev);
	पूर्णांक ret = 0;

	/* Tell the MFD core we are पढ़ोy to be enabled */
	अगर (cell->resume)
		ret = cell->resume(pdev);

	अगर (!ret)
		ret = pm_runसमय_क्रमce_resume(dev);

	वापस ret;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक पंचांगio_mmc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा mfd_cell *cell = mfd_get_cell(pdev);
	काष्ठा पंचांगio_mmc_data *pdata;
	काष्ठा पंचांगio_mmc_host *host;
	काष्ठा resource *res;
	पूर्णांक ret = -EINVAL, irq;

	अगर (pdev->num_resources != 2)
		जाओ out;

	pdata = pdev->dev.platक्रमm_data;
	अगर (!pdata || !pdata->hclk)
		जाओ out;

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0) अणु
		ret = irq;
		जाओ out;
	पूर्ण

	/* Tell the MFD core we are पढ़ोy to be enabled */
	अगर (cell->enable) अणु
		ret = cell->enable(pdev);
		अगर (ret)
			जाओ out;
	पूर्ण

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!res) अणु
		ret = -EINVAL;
		जाओ cell_disable;
	पूर्ण

	host = पंचांगio_mmc_host_alloc(pdev, pdata);
	अगर (IS_ERR(host)) अणु
		ret = PTR_ERR(host);
		जाओ cell_disable;
	पूर्ण

	/* SD control रेजिस्टर space size is 0x200, 0x400 क्रम bus_shअगरt=1 */
	host->bus_shअगरt = resource_size(res) >> 10;
	host->set_घड़ी = पंचांगio_mmc_set_घड़ी;
	host->reset = पंचांगio_mmc_reset;

	host->mmc->f_max = pdata->hclk;
	host->mmc->f_min = pdata->hclk / 512;

	ret = पंचांगio_mmc_host_probe(host);
	अगर (ret)
		जाओ host_मुक्त;

	ret = devm_request_irq(&pdev->dev, irq, पंचांगio_mmc_irq,
			       IRQF_TRIGGER_FALLING,
			       dev_name(&pdev->dev), host);
	अगर (ret)
		जाओ host_हटाओ;

	pr_info("%s at 0x%p irq %d\n", mmc_hostname(host->mmc), host->ctl, irq);

	वापस 0;

host_हटाओ:
	पंचांगio_mmc_host_हटाओ(host);
host_मुक्त:
	पंचांगio_mmc_host_मुक्त(host);
cell_disable:
	अगर (cell->disable)
		cell->disable(pdev);
out:
	वापस ret;
पूर्ण

अटल पूर्णांक पंचांगio_mmc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा mfd_cell *cell = mfd_get_cell(pdev);
	काष्ठा पंचांगio_mmc_host *host = platक्रमm_get_drvdata(pdev);

	पंचांगio_mmc_host_हटाओ(host);
	अगर (cell->disable)
		cell->disable(pdev);

	वापस 0;
पूर्ण

/* ------------------- device registration ----------------------- */

अटल स्थिर काष्ठा dev_pm_ops पंचांगio_mmc_dev_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(पंचांगio_mmc_suspend, पंचांगio_mmc_resume)
	SET_RUNTIME_PM_OPS(पंचांगio_mmc_host_runसमय_suspend,
			   पंचांगio_mmc_host_runसमय_resume, शून्य)
पूर्ण;

अटल काष्ठा platक्रमm_driver पंचांगio_mmc_driver = अणु
	.driver = अणु
		.name = "tmio-mmc",
		.probe_type = PROBE_PREFER_ASYNCHRONOUS,
		.pm = &पंचांगio_mmc_dev_pm_ops,
	पूर्ण,
	.probe = पंचांगio_mmc_probe,
	.हटाओ = पंचांगio_mmc_हटाओ,
पूर्ण;

module_platक्रमm_driver(पंचांगio_mmc_driver);

MODULE_DESCRIPTION("Toshiba TMIO SD/MMC driver");
MODULE_AUTHOR("Ian Molton <spyro@f2s.com>");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:tmio-mmc");
