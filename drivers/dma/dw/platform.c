<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Platक्रमm driver क्रम the Synopsys DesignWare DMA Controller
 *
 * Copyright (C) 2007-2008 Aपंचांगel Corporation
 * Copyright (C) 2010-2011 ST Microelectronics
 * Copyright (C) 2013 Intel Corporation
 *
 * Some parts of this driver are derived from the original dw_dmac.
 */

#समावेश <linux/module.h>
#समावेश <linux/device.h>
#समावेश <linux/clk.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/dmaengine.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/of.h>
#समावेश <linux/acpi.h>

#समावेश "internal.h"

#घोषणा DRV_NAME	"dw_dmac"

अटल पूर्णांक dw_probe(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा dw_dma_chip_pdata *match;
	काष्ठा dw_dma_chip_pdata *data;
	काष्ठा dw_dma_chip *chip;
	काष्ठा device *dev = &pdev->dev;
	पूर्णांक err;

	match = device_get_match_data(dev);
	अगर (!match)
		वापस -ENODEV;

	data = devm_kmemdup(&pdev->dev, match, माप(*match), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	chip = devm_kzalloc(dev, माप(*chip), GFP_KERNEL);
	अगर (!chip)
		वापस -ENOMEM;

	chip->irq = platक्रमm_get_irq(pdev, 0);
	अगर (chip->irq < 0)
		वापस chip->irq;

	chip->regs = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(chip->regs))
		वापस PTR_ERR(chip->regs);

	err = dma_coerce_mask_and_coherent(&pdev->dev, DMA_BIT_MASK(32));
	अगर (err)
		वापस err;

	अगर (!data->pdata)
		data->pdata = dev_get_platdata(dev);
	अगर (!data->pdata)
		data->pdata = dw_dma_parse_dt(pdev);

	chip->dev = dev;
	chip->id = pdev->id;
	chip->pdata = data->pdata;

	data->chip = chip;

	chip->clk = devm_clk_get_optional(chip->dev, "hclk");
	अगर (IS_ERR(chip->clk))
		वापस PTR_ERR(chip->clk);
	err = clk_prepare_enable(chip->clk);
	अगर (err)
		वापस err;

	pm_runसमय_enable(&pdev->dev);

	err = data->probe(chip);
	अगर (err)
		जाओ err_dw_dma_probe;

	platक्रमm_set_drvdata(pdev, data);

	dw_dma_of_controller_रेजिस्टर(chip->dw);

	dw_dma_acpi_controller_रेजिस्टर(chip->dw);

	वापस 0;

err_dw_dma_probe:
	pm_runसमय_disable(&pdev->dev);
	clk_disable_unprepare(chip->clk);
	वापस err;
पूर्ण

अटल पूर्णांक dw_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा dw_dma_chip_pdata *data = platक्रमm_get_drvdata(pdev);
	काष्ठा dw_dma_chip *chip = data->chip;
	पूर्णांक ret;

	dw_dma_acpi_controller_मुक्त(chip->dw);

	dw_dma_of_controller_मुक्त(chip->dw);

	ret = data->हटाओ(chip);
	अगर (ret)
		dev_warn(chip->dev, "can't remove device properly: %d\n", ret);

	pm_runसमय_disable(&pdev->dev);
	clk_disable_unprepare(chip->clk);

	वापस 0;
पूर्ण

अटल व्योम dw_shutकरोwn(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा dw_dma_chip_pdata *data = platक्रमm_get_drvdata(pdev);
	काष्ठा dw_dma_chip *chip = data->chip;

	/*
	 * We have to call करो_dw_dma_disable() to stop any ongoing transfer. On
	 * some platक्रमms we can't करो that since DMA device is घातered off.
	 * Moreover we have no possibility to check अगर the platक्रमm is affected
	 * or not. That's why we call pm_runसमय_get_sync() / pm_runसमय_put()
	 * unconditionally. On the other hand we can't use
	 * pm_runसमय_suspended() because runसमय PM framework is not fully
	 * used by the driver.
	 */
	pm_runसमय_get_sync(chip->dev);
	करो_dw_dma_disable(chip);
	pm_runसमय_put_sync_suspend(chip->dev);

	clk_disable_unprepare(chip->clk);
पूर्ण

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id dw_dma_of_id_table[] = अणु
	अणु .compatible = "snps,dma-spear1340", .data = &dw_dma_chip_pdata पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, dw_dma_of_id_table);
#पूर्ण_अगर

#अगर_घोषित CONFIG_ACPI
अटल स्थिर काष्ठा acpi_device_id dw_dma_acpi_id_table[] = अणु
	अणु "INTL9C60", (kernel_uदीर्घ_t)&dw_dma_chip_pdata पूर्ण,
	अणु "80862286", (kernel_uदीर्घ_t)&dw_dma_chip_pdata पूर्ण,
	अणु "808622C0", (kernel_uदीर्घ_t)&dw_dma_chip_pdata पूर्ण,

	/* Elkhart Lake iDMA 32-bit (PSE DMA) */
	अणु "80864BB4", (kernel_uदीर्घ_t)&idma32_chip_pdata पूर्ण,
	अणु "80864BB5", (kernel_uदीर्घ_t)&idma32_chip_pdata पूर्ण,
	अणु "80864BB6", (kernel_uदीर्घ_t)&idma32_chip_pdata पूर्ण,

	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(acpi, dw_dma_acpi_id_table);
#पूर्ण_अगर

#अगर_घोषित CONFIG_PM_SLEEP

अटल पूर्णांक dw_suspend_late(काष्ठा device *dev)
अणु
	काष्ठा dw_dma_chip_pdata *data = dev_get_drvdata(dev);
	काष्ठा dw_dma_chip *chip = data->chip;

	करो_dw_dma_disable(chip);
	clk_disable_unprepare(chip->clk);

	वापस 0;
पूर्ण

अटल पूर्णांक dw_resume_early(काष्ठा device *dev)
अणु
	काष्ठा dw_dma_chip_pdata *data = dev_get_drvdata(dev);
	काष्ठा dw_dma_chip *chip = data->chip;
	पूर्णांक ret;

	ret = clk_prepare_enable(chip->clk);
	अगर (ret)
		वापस ret;

	वापस करो_dw_dma_enable(chip);
पूर्ण

#पूर्ण_अगर /* CONFIG_PM_SLEEP */

अटल स्थिर काष्ठा dev_pm_ops dw_dev_pm_ops = अणु
	SET_LATE_SYSTEM_SLEEP_PM_OPS(dw_suspend_late, dw_resume_early)
पूर्ण;

अटल काष्ठा platक्रमm_driver dw_driver = अणु
	.probe		= dw_probe,
	.हटाओ		= dw_हटाओ,
	.shutकरोwn       = dw_shutकरोwn,
	.driver = अणु
		.name	= DRV_NAME,
		.pm	= &dw_dev_pm_ops,
		.of_match_table = of_match_ptr(dw_dma_of_id_table),
		.acpi_match_table = ACPI_PTR(dw_dma_acpi_id_table),
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init dw_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&dw_driver);
पूर्ण
subsys_initcall(dw_init);

अटल व्योम __निकास dw_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&dw_driver);
पूर्ण
module_निकास(dw_निकास);

MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("Synopsys DesignWare DMA Controller platform driver");
MODULE_ALIAS("platform:" DRV_NAME);
