<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * c67x00-drv.c: Cypress C67X00 USB Common infraकाष्ठाure
 *
 * Copyright (C) 2006-2008 Barco N.V.
 *    Derived from the Cypress cy7c67200/300 ezusb linux driver and
 *    based on multiple host controller drivers inside the linux kernel.
 */

/*
 * This file implements the common infraकाष्ठाure क्रम using the c67x00.
 * It is both the link between the platक्रमm configuration and subdrivers and
 * the link between the common hardware parts and the subdrivers (e.g.
 * पूर्णांकerrupt handling).
 *
 * The c67x00 has 2 SIE's (serial पूर्णांकerface engine) which can be configured
 * to be host, device or OTG (with some limitations, E.G. only SIE1 can be OTG).
 *
 * Depending on the platक्रमm configuration, the SIE's are created and
 * the corresponding subdriver is initialized (c67x00_probe_sie).
 */

#समावेश <linux/device.h>
#समावेश <linux/पन.स>
#समावेश <linux/list.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/usb.h>
#समावेश <linux/usb/c67x00.h>

#समावेश "c67x00.h"
#समावेश "c67x00-hcd.h"

अटल व्योम c67x00_probe_sie(काष्ठा c67x00_sie *sie,
			     काष्ठा c67x00_device *dev, पूर्णांक sie_num)
अणु
	spin_lock_init(&sie->lock);
	sie->dev = dev;
	sie->sie_num = sie_num;
	sie->mode = c67x00_sie_config(dev->pdata->sie_config, sie_num);

	चयन (sie->mode) अणु
	हाल C67X00_SIE_HOST:
		c67x00_hcd_probe(sie);
		अवरोध;

	हाल C67X00_SIE_UNUSED:
		dev_info(sie_dev(sie),
			 "Not using SIE %d as requested\n", sie->sie_num);
		अवरोध;

	शेष:
		dev_err(sie_dev(sie),
			"Unsupported configuration: 0x%x for SIE %d\n",
			sie->mode, sie->sie_num);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम c67x00_हटाओ_sie(काष्ठा c67x00_sie *sie)
अणु
	चयन (sie->mode) अणु
	हाल C67X00_SIE_HOST:
		c67x00_hcd_हटाओ(sie);
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल irqवापस_t c67x00_irq(पूर्णांक irq, व्योम *__dev)
अणु
	काष्ठा c67x00_device *c67x00 = __dev;
	काष्ठा c67x00_sie *sie;
	u16 msg, पूर्णांक_status;
	पूर्णांक i, count = 8;

	पूर्णांक_status = c67x00_ll_hpi_status(c67x00);
	अगर (!पूर्णांक_status)
		वापस IRQ_NONE;

	जबतक (पूर्णांक_status != 0 && (count-- >= 0)) अणु
		c67x00_ll_irq(c67x00, पूर्णांक_status);
		क्रम (i = 0; i < C67X00_SIES; i++) अणु
			sie = &c67x00->sie[i];
			msg = 0;
			अगर (पूर्णांक_status & SIEMSG_FLG(i))
				msg = c67x00_ll_fetch_siemsg(c67x00, i);
			अगर (sie->irq)
				sie->irq(sie, पूर्णांक_status, msg);
		पूर्ण
		पूर्णांक_status = c67x00_ll_hpi_status(c67x00);
	पूर्ण

	अगर (पूर्णांक_status)
		dev_warn(&c67x00->pdev->dev, "Not all interrupts handled! "
			 "status = 0x%04x\n", पूर्णांक_status);

	वापस IRQ_HANDLED;
पूर्ण

/* ------------------------------------------------------------------------- */

अटल पूर्णांक c67x00_drv_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा c67x00_device *c67x00;
	काष्ठा c67x00_platक्रमm_data *pdata;
	काष्ठा resource *res, *res2;
	पूर्णांक ret, i;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!res)
		वापस -ENODEV;

	res2 = platक्रमm_get_resource(pdev, IORESOURCE_IRQ, 0);
	अगर (!res2)
		वापस -ENODEV;

	pdata = dev_get_platdata(&pdev->dev);
	अगर (!pdata)
		वापस -ENODEV;

	c67x00 = kzalloc(माप(*c67x00), GFP_KERNEL);
	अगर (!c67x00)
		वापस -ENOMEM;

	अगर (!request_mem_region(res->start, resource_size(res),
				pdev->name)) अणु
		dev_err(&pdev->dev, "Memory region busy\n");
		ret = -EBUSY;
		जाओ request_mem_failed;
	पूर्ण
	c67x00->hpi.base = ioremap(res->start, resource_size(res));
	अगर (!c67x00->hpi.base) अणु
		dev_err(&pdev->dev, "Unable to map HPI registers\n");
		ret = -EIO;
		जाओ map_failed;
	पूर्ण

	spin_lock_init(&c67x00->hpi.lock);
	c67x00->hpi.regstep = pdata->hpi_regstep;
	c67x00->pdata = dev_get_platdata(&pdev->dev);
	c67x00->pdev = pdev;

	c67x00_ll_init(c67x00);
	c67x00_ll_hpi_reg_init(c67x00);

	ret = request_irq(res2->start, c67x00_irq, 0, pdev->name, c67x00);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Cannot claim IRQ\n");
		जाओ request_irq_failed;
	पूर्ण

	ret = c67x00_ll_reset(c67x00);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Device reset failed\n");
		जाओ reset_failed;
	पूर्ण

	क्रम (i = 0; i < C67X00_SIES; i++)
		c67x00_probe_sie(&c67x00->sie[i], c67x00, i);

	platक्रमm_set_drvdata(pdev, c67x00);

	वापस 0;

 reset_failed:
	मुक्त_irq(res2->start, c67x00);
 request_irq_failed:
	iounmap(c67x00->hpi.base);
 map_failed:
	release_mem_region(res->start, resource_size(res));
 request_mem_failed:
	kमुक्त(c67x00);

	वापस ret;
पूर्ण

अटल पूर्णांक c67x00_drv_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा c67x00_device *c67x00 = platक्रमm_get_drvdata(pdev);
	काष्ठा resource *res;
	पूर्णांक i;

	क्रम (i = 0; i < C67X00_SIES; i++)
		c67x00_हटाओ_sie(&c67x00->sie[i]);

	c67x00_ll_release(c67x00);

	res = platक्रमm_get_resource(pdev, IORESOURCE_IRQ, 0);
	अगर (res)
		मुक्त_irq(res->start, c67x00);

	iounmap(c67x00->hpi.base);

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (res)
		release_mem_region(res->start, resource_size(res));

	kमुक्त(c67x00);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver c67x00_driver = अणु
	.probe	= c67x00_drv_probe,
	.हटाओ	= c67x00_drv_हटाओ,
	.driver	= अणु
		.name = "c67x00",
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(c67x00_driver);

MODULE_AUTHOR("Peter Korsgaard, Jan Veldeman, Grant Likely");
MODULE_DESCRIPTION("Cypress C67X00 USB Controller Driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:c67x00");
