<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  linux/arch/arm/mach-pxa/ssp.c
 *
 *  based on linux/arch/arm/mach-sa1100/ssp.c by Russell King
 *
 *  Copyright (C) 2003 Russell King.
 *  Copyright (C) 2003 Wolfson Microelectronics PLC
 *
 *  PXA2xx SSP driver.  This provides the generic core क्रम simple
 *  IO-based SSP applications and allows easy port setup क्रम DMA access.
 *
 *  Author: Liam Girdwood <liam.girdwood@wolfsonmicro.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/ioport.h>
#समावेश <linux/init.h>
#समावेश <linux/mutex.h>
#समावेश <linux/clk.h>
#समावेश <linux/err.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/spi/pxa2xx_spi.h>
#समावेश <linux/पन.स>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>

#समावेश <यंत्र/irq.h>

अटल DEFINE_MUTEX(ssp_lock);
अटल LIST_HEAD(ssp_list);

काष्ठा ssp_device *pxa_ssp_request(पूर्णांक port, स्थिर अक्षर *label)
अणु
	काष्ठा ssp_device *ssp = शून्य;

	mutex_lock(&ssp_lock);

	list_क्रम_each_entry(ssp, &ssp_list, node) अणु
		अगर (ssp->port_id == port && ssp->use_count == 0) अणु
			ssp->use_count++;
			ssp->label = label;
			अवरोध;
		पूर्ण
	पूर्ण

	mutex_unlock(&ssp_lock);

	अगर (&ssp->node == &ssp_list)
		वापस शून्य;

	वापस ssp;
पूर्ण
EXPORT_SYMBOL(pxa_ssp_request);

काष्ठा ssp_device *pxa_ssp_request_of(स्थिर काष्ठा device_node *of_node,
				      स्थिर अक्षर *label)
अणु
	काष्ठा ssp_device *ssp = शून्य;

	mutex_lock(&ssp_lock);

	list_क्रम_each_entry(ssp, &ssp_list, node) अणु
		अगर (ssp->of_node == of_node && ssp->use_count == 0) अणु
			ssp->use_count++;
			ssp->label = label;
			अवरोध;
		पूर्ण
	पूर्ण

	mutex_unlock(&ssp_lock);

	अगर (&ssp->node == &ssp_list)
		वापस शून्य;

	वापस ssp;
पूर्ण
EXPORT_SYMBOL(pxa_ssp_request_of);

व्योम pxa_ssp_मुक्त(काष्ठा ssp_device *ssp)
अणु
	mutex_lock(&ssp_lock);
	अगर (ssp->use_count) अणु
		ssp->use_count--;
		ssp->label = शून्य;
	पूर्ण अन्यथा
		dev_err(ssp->dev, "device already free\n");
	mutex_unlock(&ssp_lock);
पूर्ण
EXPORT_SYMBOL(pxa_ssp_मुक्त);

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id pxa_ssp_of_ids[] = अणु
	अणु .compatible = "mrvl,pxa25x-ssp",	.data = (व्योम *) PXA25x_SSP पूर्ण,
	अणु .compatible = "mvrl,pxa25x-nssp",	.data = (व्योम *) PXA25x_NSSP पूर्ण,
	अणु .compatible = "mrvl,pxa27x-ssp",	.data = (व्योम *) PXA27x_SSP पूर्ण,
	अणु .compatible = "mrvl,pxa3xx-ssp",	.data = (व्योम *) PXA3xx_SSP पूर्ण,
	अणु .compatible = "mvrl,pxa168-ssp",	.data = (व्योम *) PXA168_SSP पूर्ण,
	अणु .compatible = "mrvl,pxa910-ssp",	.data = (व्योम *) PXA910_SSP पूर्ण,
	अणु .compatible = "mrvl,ce4100-ssp",	.data = (व्योम *) CE4100_SSP पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, pxa_ssp_of_ids);
#पूर्ण_अगर

अटल पूर्णांक pxa_ssp_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा resource *res;
	काष्ठा ssp_device *ssp;
	काष्ठा device *dev = &pdev->dev;

	ssp = devm_kzalloc(dev, माप(काष्ठा ssp_device), GFP_KERNEL);
	अगर (ssp == शून्य)
		वापस -ENOMEM;

	ssp->dev = dev;

	ssp->clk = devm_clk_get(dev, शून्य);
	अगर (IS_ERR(ssp->clk))
		वापस PTR_ERR(ssp->clk);

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (res == शून्य) अणु
		dev_err(dev, "no memory resource defined\n");
		वापस -ENODEV;
	पूर्ण

	res = devm_request_mem_region(dev, res->start, resource_size(res),
				      pdev->name);
	अगर (res == शून्य) अणु
		dev_err(dev, "failed to request memory resource\n");
		वापस -EBUSY;
	पूर्ण

	ssp->phys_base = res->start;

	ssp->mmio_base = devm_ioremap(dev, res->start, resource_size(res));
	अगर (ssp->mmio_base == शून्य) अणु
		dev_err(dev, "failed to ioremap() registers\n");
		वापस -ENODEV;
	पूर्ण

	ssp->irq = platक्रमm_get_irq(pdev, 0);
	अगर (ssp->irq < 0) अणु
		dev_err(dev, "no IRQ resource defined\n");
		वापस -ENODEV;
	पूर्ण

	अगर (dev->of_node) अणु
		स्थिर काष्ठा of_device_id *id =
			of_match_device(of_match_ptr(pxa_ssp_of_ids), dev);
		ssp->type = (पूर्णांक) id->data;
	पूर्ण अन्यथा अणु
		स्थिर काष्ठा platक्रमm_device_id *id =
			platक्रमm_get_device_id(pdev);
		ssp->type = (पूर्णांक) id->driver_data;

		/* PXA2xx/3xx SSP ports starts from 1 and the पूर्णांकernal pdev->id
		 * starts from 0, करो a translation here
		 */
		ssp->port_id = pdev->id + 1;
	पूर्ण

	ssp->use_count = 0;
	ssp->of_node = dev->of_node;

	mutex_lock(&ssp_lock);
	list_add(&ssp->node, &ssp_list);
	mutex_unlock(&ssp_lock);

	platक्रमm_set_drvdata(pdev, ssp);

	वापस 0;
पूर्ण

अटल पूर्णांक pxa_ssp_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा ssp_device *ssp;

	ssp = platक्रमm_get_drvdata(pdev);
	अगर (ssp == शून्य)
		वापस -ENODEV;

	mutex_lock(&ssp_lock);
	list_del(&ssp->node);
	mutex_unlock(&ssp_lock);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा platक्रमm_device_id ssp_id_table[] = अणु
	अणु "pxa25x-ssp",		PXA25x_SSP पूर्ण,
	अणु "pxa25x-nssp",	PXA25x_NSSP पूर्ण,
	अणु "pxa27x-ssp",		PXA27x_SSP पूर्ण,
	अणु "pxa3xx-ssp",		PXA3xx_SSP पूर्ण,
	अणु "pxa168-ssp",		PXA168_SSP पूर्ण,
	अणु "pxa910-ssp",		PXA910_SSP पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver pxa_ssp_driver = अणु
	.probe		= pxa_ssp_probe,
	.हटाओ		= pxa_ssp_हटाओ,
	.driver		= अणु
		.name		= "pxa2xx-ssp",
		.of_match_table	= of_match_ptr(pxa_ssp_of_ids),
	पूर्ण,
	.id_table	= ssp_id_table,
पूर्ण;

अटल पूर्णांक __init pxa_ssp_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&pxa_ssp_driver);
पूर्ण

अटल व्योम __निकास pxa_ssp_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&pxa_ssp_driver);
पूर्ण

arch_initcall(pxa_ssp_init);
module_निकास(pxa_ssp_निकास);

MODULE_DESCRIPTION("PXA SSP driver");
MODULE_AUTHOR("Liam Girdwood");
MODULE_LICENSE("GPL");
