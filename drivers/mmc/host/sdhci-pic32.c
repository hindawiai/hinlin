<शैली गुरु>
/*
 * Support of SDHCI platक्रमm devices क्रम Microchip PIC32.
 *
 * Copyright (C) 2015 Microchip
 * Andrei Pistirica, Paul Thacker
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
#समावेश <linux/पन.स>
#समावेश "sdhci.h"
#समावेश "sdhci-pltfm.h"
#समावेश <linux/platक्रमm_data/sdhci-pic32.h>

#घोषणा SDH_SHARED_BUS_CTRL		0x000000E0
#घोषणा SDH_SHARED_BUS_NR_CLK_PINS_MASK	0x7
#घोषणा SDH_SHARED_BUS_NR_IRQ_PINS_MASK	0x30
#घोषणा SDH_SHARED_BUS_CLK_PINS		0x10
#घोषणा SDH_SHARED_BUS_IRQ_PINS		0x14
#घोषणा SDH_CAPS_SDH_SLOT_TYPE_MASK	0xC0000000
#घोषणा SDH_SLOT_TYPE_REMOVABLE		0x0
#घोषणा SDH_SLOT_TYPE_EMBEDDED		0x1
#घोषणा SDH_SLOT_TYPE_SHARED_BUS	0x2
#घोषणा SDHCI_CTRL_CDSSEL		0x80
#घोषणा SDHCI_CTRL_CDTLVL		0x40

#घोषणा ADMA_FIFO_RD_THSHLD	512
#घोषणा ADMA_FIFO_WR_THSHLD	512

काष्ठा pic32_sdhci_priv अणु
	काष्ठा platक्रमm_device	*pdev;
	काष्ठा clk *sys_clk;
	काष्ठा clk *base_clk;
पूर्ण;

अटल अचिन्हित पूर्णांक pic32_sdhci_get_max_घड़ी(काष्ठा sdhci_host *host)
अणु
	काष्ठा pic32_sdhci_priv *sdhci_pdata = sdhci_priv(host);

	वापस clk_get_rate(sdhci_pdata->base_clk);
पूर्ण

अटल व्योम pic32_sdhci_set_bus_width(काष्ठा sdhci_host *host, पूर्णांक width)
अणु
	u8 ctrl;

	ctrl = sdhci_पढ़ोb(host, SDHCI_HOST_CONTROL);
	अगर (width == MMC_BUS_WIDTH_8) अणु
		ctrl &= ~SDHCI_CTRL_4BITBUS;
		अगर (host->version >= SDHCI_SPEC_300)
			ctrl |= SDHCI_CTRL_8BITBUS;
	पूर्ण अन्यथा अणु
		अगर (host->version >= SDHCI_SPEC_300)
			ctrl &= ~SDHCI_CTRL_8BITBUS;
		अगर (width == MMC_BUS_WIDTH_4)
			ctrl |= SDHCI_CTRL_4BITBUS;
		अन्यथा
			ctrl &= ~SDHCI_CTRL_4BITBUS;
	पूर्ण

	/* CD select and test bits must be set क्रम errata workaround. */
	ctrl &= ~SDHCI_CTRL_CDTLVL;
	ctrl |= SDHCI_CTRL_CDSSEL;
	sdhci_ग_लिखोb(host, ctrl, SDHCI_HOST_CONTROL);
पूर्ण

अटल अचिन्हित पूर्णांक pic32_sdhci_get_ro(काष्ठा sdhci_host *host)
अणु
	/*
	 * The SDHCI_WRITE_PROTECT bit is unstable on current hardware so we
	 * can't depend on its value in any way.
	 */
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा sdhci_ops pic32_sdhci_ops = अणु
	.get_max_घड़ी = pic32_sdhci_get_max_घड़ी,
	.set_घड़ी = sdhci_set_घड़ी,
	.set_bus_width = pic32_sdhci_set_bus_width,
	.reset = sdhci_reset,
	.set_uhs_संकेतing = sdhci_set_uhs_संकेतing,
	.get_ro = pic32_sdhci_get_ro,
पूर्ण;

अटल स्थिर काष्ठा sdhci_pltfm_data sdhci_pic32_pdata = अणु
	.ops = &pic32_sdhci_ops,
	.quirks = SDHCI_QUIRK_NO_HISPD_BIT,
	.quirks2 = SDHCI_QUIRK2_NO_1_8_V,
पूर्ण;

अटल व्योम pic32_sdhci_shared_bus(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sdhci_host *host = platक्रमm_get_drvdata(pdev);
	u32 bus = पढ़ोl(host->ioaddr + SDH_SHARED_BUS_CTRL);
	u32 clk_pins = (bus & SDH_SHARED_BUS_NR_CLK_PINS_MASK) >> 0;
	u32 irq_pins = (bus & SDH_SHARED_BUS_NR_IRQ_PINS_MASK) >> 4;

	/* select first घड़ी */
	अगर (clk_pins & 1)
		bus |= (1 << SDH_SHARED_BUS_CLK_PINS);

	/* select first पूर्णांकerrupt */
	अगर (irq_pins & 1)
		bus |= (1 << SDH_SHARED_BUS_IRQ_PINS);

	ग_लिखोl(bus, host->ioaddr + SDH_SHARED_BUS_CTRL);
पूर्ण

अटल व्योम pic32_sdhci_probe_platक्रमm(काष्ठा platक्रमm_device *pdev,
				      काष्ठा pic32_sdhci_priv *pdata)
अणु
	u32 caps_slot_type;
	काष्ठा sdhci_host *host = platक्रमm_get_drvdata(pdev);

	/* Check card slot connected on shared bus. */
	host->caps = पढ़ोl(host->ioaddr + SDHCI_CAPABILITIES);
	caps_slot_type = (host->caps & SDH_CAPS_SDH_SLOT_TYPE_MASK) >> 30;
	अगर (caps_slot_type == SDH_SLOT_TYPE_SHARED_BUS)
		pic32_sdhci_shared_bus(pdev);
पूर्ण

अटल पूर्णांक pic32_sdhci_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sdhci_host *host;
	काष्ठा sdhci_pltfm_host *pltfm_host;
	काष्ठा pic32_sdhci_priv *sdhci_pdata;
	काष्ठा pic32_sdhci_platक्रमm_data *plat_data;
	पूर्णांक ret;

	host = sdhci_pltfm_init(pdev, &sdhci_pic32_pdata,
				माप(काष्ठा pic32_sdhci_priv));
	अगर (IS_ERR(host)) अणु
		ret = PTR_ERR(host);
		जाओ err;
	पूर्ण

	pltfm_host = sdhci_priv(host);
	sdhci_pdata = sdhci_pltfm_priv(pltfm_host);

	plat_data = pdev->dev.platक्रमm_data;
	अगर (plat_data && plat_data->setup_dma) अणु
		ret = plat_data->setup_dma(ADMA_FIFO_RD_THSHLD,
					   ADMA_FIFO_WR_THSHLD);
		अगर (ret)
			जाओ err_host;
	पूर्ण

	sdhci_pdata->sys_clk = devm_clk_get(&pdev->dev, "sys_clk");
	अगर (IS_ERR(sdhci_pdata->sys_clk)) अणु
		ret = PTR_ERR(sdhci_pdata->sys_clk);
		dev_err(&pdev->dev, "Error getting clock\n");
		जाओ err_host;
	पूर्ण

	ret = clk_prepare_enable(sdhci_pdata->sys_clk);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Error enabling clock\n");
		जाओ err_host;
	पूर्ण

	sdhci_pdata->base_clk = devm_clk_get(&pdev->dev, "base_clk");
	अगर (IS_ERR(sdhci_pdata->base_clk)) अणु
		ret = PTR_ERR(sdhci_pdata->base_clk);
		dev_err(&pdev->dev, "Error getting clock\n");
		जाओ err_sys_clk;
	पूर्ण

	ret = clk_prepare_enable(sdhci_pdata->base_clk);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Error enabling clock\n");
		जाओ err_base_clk;
	पूर्ण

	ret = mmc_of_parse(host->mmc);
	अगर (ret)
		जाओ err_base_clk;

	pic32_sdhci_probe_platक्रमm(pdev, sdhci_pdata);

	ret = sdhci_add_host(host);
	अगर (ret)
		जाओ err_base_clk;

	dev_info(&pdev->dev, "Successfully added sdhci host\n");
	वापस 0;

err_base_clk:
	clk_disable_unprepare(sdhci_pdata->base_clk);
err_sys_clk:
	clk_disable_unprepare(sdhci_pdata->sys_clk);
err_host:
	sdhci_pltfm_मुक्त(pdev);
err:
	dev_err(&pdev->dev, "pic32-sdhci probe failed: %d\n", ret);
	वापस ret;
पूर्ण

अटल पूर्णांक pic32_sdhci_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sdhci_host *host = platक्रमm_get_drvdata(pdev);
	काष्ठा pic32_sdhci_priv *sdhci_pdata = sdhci_priv(host);
	u32 scratch;

	scratch = पढ़ोl(host->ioaddr + SDHCI_INT_STATUS);
	sdhci_हटाओ_host(host, scratch == (u32)~0);
	clk_disable_unprepare(sdhci_pdata->base_clk);
	clk_disable_unprepare(sdhci_pdata->sys_clk);
	sdhci_pltfm_मुक्त(pdev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id pic32_sdhci_id_table[] = अणु
	अणु .compatible = "microchip,pic32mzda-sdhci" पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, pic32_sdhci_id_table);

अटल काष्ठा platक्रमm_driver pic32_sdhci_driver = अणु
	.driver = अणु
		.name	= "pic32-sdhci",
		.probe_type = PROBE_PREFER_ASYNCHRONOUS,
		.of_match_table = of_match_ptr(pic32_sdhci_id_table),
	पूर्ण,
	.probe		= pic32_sdhci_probe,
	.हटाओ		= pic32_sdhci_हटाओ,
पूर्ण;

module_platक्रमm_driver(pic32_sdhci_driver);

MODULE_DESCRIPTION("Microchip PIC32 SDHCI driver");
MODULE_AUTHOR("Pistirica Sorin Andrei & Sandeep Sheriker");
MODULE_LICENSE("GPL v2");
