<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * AMD Secure Processor device driver
 *
 * Copyright (C) 2014,2018 Advanced Micro Devices, Inc.
 *
 * Author: Tom Lendacky <thomas.lendacky@amd.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/ioport.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/sched.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/delay.h>
#समावेश <linux/ccp.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/acpi.h>

#समावेश "ccp-dev.h"

काष्ठा sp_platक्रमm अणु
	पूर्णांक coherent;
	अचिन्हित पूर्णांक irq_count;
पूर्ण;

अटल स्थिर काष्ठा sp_dev_vdata dev_vdata[] = अणु
	अणु
		.bar = 0,
#अगर_घोषित CONFIG_CRYPTO_DEV_SP_CCP
		.ccp_vdata = &ccpv3_platक्रमm,
#पूर्ण_अगर
	पूर्ण,
पूर्ण;

#अगर_घोषित CONFIG_ACPI
अटल स्थिर काष्ठा acpi_device_id sp_acpi_match[] = अणु
	अणु "AMDI0C00", (kernel_uदीर्घ_t)&dev_vdata[0] पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(acpi, sp_acpi_match);
#पूर्ण_अगर

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id sp_of_match[] = अणु
	अणु .compatible = "amd,ccp-seattle-v1a",
	  .data = (स्थिर व्योम *)&dev_vdata[0] पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, sp_of_match);
#पूर्ण_अगर

अटल काष्ठा sp_dev_vdata *sp_get_of_version(काष्ठा platक्रमm_device *pdev)
अणु
#अगर_घोषित CONFIG_OF
	स्थिर काष्ठा of_device_id *match;

	match = of_match_node(sp_of_match, pdev->dev.of_node);
	अगर (match && match->data)
		वापस (काष्ठा sp_dev_vdata *)match->data;
#पूर्ण_अगर
	वापस शून्य;
पूर्ण

अटल काष्ठा sp_dev_vdata *sp_get_acpi_version(काष्ठा platक्रमm_device *pdev)
अणु
#अगर_घोषित CONFIG_ACPI
	स्थिर काष्ठा acpi_device_id *match;

	match = acpi_match_device(sp_acpi_match, &pdev->dev);
	अगर (match && match->driver_data)
		वापस (काष्ठा sp_dev_vdata *)match->driver_data;
#पूर्ण_अगर
	वापस शून्य;
पूर्ण

अटल पूर्णांक sp_get_irqs(काष्ठा sp_device *sp)
अणु
	काष्ठा sp_platक्रमm *sp_platक्रमm = sp->dev_specअगरic;
	काष्ठा device *dev = sp->dev;
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	अचिन्हित पूर्णांक i, count;
	पूर्णांक ret;

	क्रम (i = 0, count = 0; i < pdev->num_resources; i++) अणु
		काष्ठा resource *res = &pdev->resource[i];

		अगर (resource_type(res) == IORESOURCE_IRQ)
			count++;
	पूर्ण

	sp_platक्रमm->irq_count = count;

	ret = platक्रमm_get_irq(pdev, 0);
	अगर (ret < 0) अणु
		dev_notice(dev, "unable to get IRQ (%d)\n", ret);
		वापस ret;
	पूर्ण

	sp->psp_irq = ret;
	अगर (count == 1) अणु
		sp->ccp_irq = ret;
	पूर्ण अन्यथा अणु
		ret = platक्रमm_get_irq(pdev, 1);
		अगर (ret < 0) अणु
			dev_notice(dev, "unable to get IRQ (%d)\n", ret);
			वापस ret;
		पूर्ण

		sp->ccp_irq = ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक sp_platक्रमm_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sp_device *sp;
	काष्ठा sp_platक्रमm *sp_platक्रमm;
	काष्ठा device *dev = &pdev->dev;
	क्रमागत dev_dma_attr attr;
	पूर्णांक ret;

	ret = -ENOMEM;
	sp = sp_alloc_काष्ठा(dev);
	अगर (!sp)
		जाओ e_err;

	sp_platक्रमm = devm_kzalloc(dev, माप(*sp_platक्रमm), GFP_KERNEL);
	अगर (!sp_platक्रमm)
		जाओ e_err;

	sp->dev_specअगरic = sp_platक्रमm;
	sp->dev_vdata = pdev->dev.of_node ? sp_get_of_version(pdev)
					 : sp_get_acpi_version(pdev);
	अगर (!sp->dev_vdata) अणु
		ret = -ENODEV;
		dev_err(dev, "missing driver data\n");
		जाओ e_err;
	पूर्ण

	sp->io_map = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(sp->io_map)) अणु
		ret = PTR_ERR(sp->io_map);
		जाओ e_err;
	पूर्ण

	attr = device_get_dma_attr(dev);
	अगर (attr == DEV_DMA_NOT_SUPPORTED) अणु
		dev_err(dev, "DMA is not supported");
		जाओ e_err;
	पूर्ण

	sp_platक्रमm->coherent = (attr == DEV_DMA_COHERENT);
	अगर (sp_platक्रमm->coherent)
		sp->axcache = CACHE_WB_NO_ALLOC;
	अन्यथा
		sp->axcache = CACHE_NONE;

	ret = dma_set_mask_and_coherent(dev, DMA_BIT_MASK(48));
	अगर (ret) अणु
		dev_err(dev, "dma_set_mask_and_coherent failed (%d)\n", ret);
		जाओ e_err;
	पूर्ण

	ret = sp_get_irqs(sp);
	अगर (ret)
		जाओ e_err;

	dev_set_drvdata(dev, sp);

	ret = sp_init(sp);
	अगर (ret)
		जाओ e_err;

	dev_notice(dev, "enabled\n");

	वापस 0;

e_err:
	dev_notice(dev, "initialization failed\n");
	वापस ret;
पूर्ण

अटल पूर्णांक sp_platक्रमm_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा sp_device *sp = dev_get_drvdata(dev);

	sp_destroy(sp);

	dev_notice(dev, "disabled\n");

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक sp_platक्रमm_suspend(काष्ठा platक्रमm_device *pdev,
				pm_message_t state)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा sp_device *sp = dev_get_drvdata(dev);

	वापस sp_suspend(sp);
पूर्ण

अटल पूर्णांक sp_platक्रमm_resume(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा sp_device *sp = dev_get_drvdata(dev);

	वापस sp_resume(sp);
पूर्ण
#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver sp_platक्रमm_driver = अणु
	.driver = अणु
		.name = "ccp",
#अगर_घोषित CONFIG_ACPI
		.acpi_match_table = sp_acpi_match,
#पूर्ण_अगर
#अगर_घोषित CONFIG_OF
		.of_match_table = sp_of_match,
#पूर्ण_अगर
	पूर्ण,
	.probe = sp_platक्रमm_probe,
	.हटाओ = sp_platक्रमm_हटाओ,
#अगर_घोषित CONFIG_PM
	.suspend = sp_platक्रमm_suspend,
	.resume = sp_platक्रमm_resume,
#पूर्ण_अगर
पूर्ण;

पूर्णांक sp_platक्रमm_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&sp_platक्रमm_driver);
पूर्ण

व्योम sp_platक्रमm_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&sp_platक्रमm_driver);
पूर्ण
