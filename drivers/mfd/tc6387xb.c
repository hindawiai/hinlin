<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Toshiba TC6387XB support
 * Copyright (c) 2005 Ian Molton
 *
 * This file contains TC6387XB base support.
 */

#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/clk.h>
#समावेश <linux/err.h>
#समावेश <linux/mfd/core.h>
#समावेश <linux/mfd/पंचांगपन.स>
#समावेश <linux/mfd/tc6387xb.h>
#समावेश <linux/slab.h>

क्रमागत अणु
	TC6387XB_CELL_MMC,
पूर्ण;

काष्ठा tc6387xb अणु
	व्योम __iomem *scr;
	काष्ठा clk *clk32k;
	काष्ठा resource rscr;
पूर्ण;

अटल स्थिर काष्ठा resource tc6387xb_mmc_resources[] = अणु
	अणु
		.start = 0x800,
		.end   = 0x9ff,
		.flags = IORESOURCE_MEM,
	पूर्ण,
	अणु
		.start = 0,
		.end   = 0,
		.flags = IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

/*--------------------------------------------------------------------------*/

#अगर_घोषित CONFIG_PM
अटल पूर्णांक tc6387xb_suspend(काष्ठा platक्रमm_device *dev, pm_message_t state)
अणु
	काष्ठा tc6387xb *tc6387xb = platक्रमm_get_drvdata(dev);
	काष्ठा tc6387xb_platक्रमm_data *pdata = dev_get_platdata(&dev->dev);

	अगर (pdata && pdata->suspend)
		pdata->suspend(dev);
	clk_disable_unprepare(tc6387xb->clk32k);

	वापस 0;
पूर्ण

अटल पूर्णांक tc6387xb_resume(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा tc6387xb *tc6387xb = platक्रमm_get_drvdata(dev);
	काष्ठा tc6387xb_platक्रमm_data *pdata = dev_get_platdata(&dev->dev);

	clk_prepare_enable(tc6387xb->clk32k);
	अगर (pdata && pdata->resume)
		pdata->resume(dev);

	पंचांगio_core_mmc_resume(tc6387xb->scr + 0x200, 0,
		tc6387xb_mmc_resources[0].start & 0xfffe);

	वापस 0;
पूर्ण
#अन्यथा
#घोषणा tc6387xb_suspend  शून्य
#घोषणा tc6387xb_resume   शून्य
#पूर्ण_अगर

/*--------------------------------------------------------------------------*/

अटल व्योम tc6387xb_mmc_pwr(काष्ठा platक्रमm_device *mmc, पूर्णांक state)
अणु
	काष्ठा tc6387xb *tc6387xb = dev_get_drvdata(mmc->dev.parent);

	पंचांगio_core_mmc_pwr(tc6387xb->scr + 0x200, 0, state);
पूर्ण

अटल व्योम tc6387xb_mmc_clk_भाग(काष्ठा platक्रमm_device *mmc, पूर्णांक state)
अणु
	काष्ठा tc6387xb *tc6387xb = dev_get_drvdata(mmc->dev.parent);

	पंचांगio_core_mmc_clk_भाग(tc6387xb->scr + 0x200, 0, state);
पूर्ण


अटल पूर्णांक tc6387xb_mmc_enable(काष्ठा platक्रमm_device *mmc)
अणु
	काष्ठा tc6387xb *tc6387xb = dev_get_drvdata(mmc->dev.parent);

	clk_prepare_enable(tc6387xb->clk32k);

	पंचांगio_core_mmc_enable(tc6387xb->scr + 0x200, 0,
		tc6387xb_mmc_resources[0].start & 0xfffe);

	वापस 0;
पूर्ण

अटल पूर्णांक tc6387xb_mmc_disable(काष्ठा platक्रमm_device *mmc)
अणु
	काष्ठा tc6387xb *tc6387xb = dev_get_drvdata(mmc->dev.parent);

	clk_disable_unprepare(tc6387xb->clk32k);

	वापस 0;
पूर्ण

अटल काष्ठा पंचांगio_mmc_data tc6387xb_mmc_data = अणु
	.hclk = 24000000,
	.set_pwr = tc6387xb_mmc_pwr,
	.set_clk_भाग = tc6387xb_mmc_clk_भाग,
पूर्ण;

/*--------------------------------------------------------------------------*/

अटल स्थिर काष्ठा mfd_cell tc6387xb_cells[] = अणु
	[TC6387XB_CELL_MMC] = अणु
		.name = "tmio-mmc",
		.enable = tc6387xb_mmc_enable,
		.disable = tc6387xb_mmc_disable,
		.platक्रमm_data = &tc6387xb_mmc_data,
		.pdata_size    = माप(tc6387xb_mmc_data),
		.num_resources = ARRAY_SIZE(tc6387xb_mmc_resources),
		.resources = tc6387xb_mmc_resources,
	पूर्ण,
पूर्ण;

अटल पूर्णांक tc6387xb_probe(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा tc6387xb_platक्रमm_data *pdata = dev_get_platdata(&dev->dev);
	काष्ठा resource *iomem, *rscr;
	काष्ठा clk *clk32k;
	काष्ठा tc6387xb *tc6387xb;
	पूर्णांक irq, ret;

	iomem = platक्रमm_get_resource(dev, IORESOURCE_MEM, 0);
	अगर (!iomem)
		वापस -EINVAL;

	tc6387xb = kzalloc(माप(*tc6387xb), GFP_KERNEL);
	अगर (!tc6387xb)
		वापस -ENOMEM;

	ret  = platक्रमm_get_irq(dev, 0);
	अगर (ret >= 0)
		irq = ret;
	अन्यथा
		जाओ err_no_irq;

	clk32k = clk_get(&dev->dev, "CLK_CK32K");
	अगर (IS_ERR(clk32k)) अणु
		ret = PTR_ERR(clk32k);
		जाओ err_no_clk;
	पूर्ण

	rscr = &tc6387xb->rscr;
	rscr->name = "tc6387xb-core";
	rscr->start = iomem->start;
	rscr->end = iomem->start + 0xff;
	rscr->flags = IORESOURCE_MEM;

	ret = request_resource(iomem, rscr);
	अगर (ret)
		जाओ err_resource;

	tc6387xb->scr = ioremap(rscr->start, resource_size(rscr));
	अगर (!tc6387xb->scr) अणु
		ret = -ENOMEM;
		जाओ err_ioremap;
	पूर्ण

	tc6387xb->clk32k = clk32k;
	platक्रमm_set_drvdata(dev, tc6387xb);

	अगर (pdata && pdata->enable)
		pdata->enable(dev);

	dev_info(&dev->dev, "Toshiba tc6387xb initialised\n");

	ret = mfd_add_devices(&dev->dev, dev->id, tc6387xb_cells,
			      ARRAY_SIZE(tc6387xb_cells), iomem, irq, शून्य);

	अगर (!ret)
		वापस 0;

	iounmap(tc6387xb->scr);
err_ioremap:
	release_resource(&tc6387xb->rscr);
err_resource:
	clk_put(clk32k);
err_no_clk:
err_no_irq:
	kमुक्त(tc6387xb);
	वापस ret;
पूर्ण

अटल पूर्णांक tc6387xb_हटाओ(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा tc6387xb *tc6387xb = platक्रमm_get_drvdata(dev);

	mfd_हटाओ_devices(&dev->dev);
	iounmap(tc6387xb->scr);
	release_resource(&tc6387xb->rscr);
	clk_disable_unprepare(tc6387xb->clk32k);
	clk_put(tc6387xb->clk32k);
	kमुक्त(tc6387xb);

	वापस 0;
पूर्ण


अटल काष्ठा platक्रमm_driver tc6387xb_platक्रमm_driver = अणु
	.driver = अणु
		.name		= "tc6387xb",
	पूर्ण,
	.probe		= tc6387xb_probe,
	.हटाओ		= tc6387xb_हटाओ,
	.suspend        = tc6387xb_suspend,
	.resume         = tc6387xb_resume,
पूर्ण;

module_platक्रमm_driver(tc6387xb_platक्रमm_driver);

MODULE_DESCRIPTION("Toshiba TC6387XB core driver");
MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Ian Molton");
MODULE_ALIAS("platform:tc6387xb");

