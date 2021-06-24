<शैली गुरु>
// SPDX-License-Identअगरier: GPL-1.0+
/*
 * OHCI HCD (Host Controller Driver) क्रम USB.
 *
 * (C) Copyright 1999 Roman Weissgaerber <weissg@vienna.at>
 * (C) Copyright 2000-2005 David Brownell
 * (C) Copyright 2002 Hewlett-Packard Company
 * (C) Copyright 2008 Magnus Damm
 *
 * SM501 Bus Glue - based on ohci-omap.c
 *
 * This file is licenced under the GPL.
 */

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/sm501.h>
#समावेश <linux/sm501-regs.h>

अटल पूर्णांक ohci_sm501_init(काष्ठा usb_hcd *hcd)
अणु
	वापस ohci_init(hcd_to_ohci(hcd));
पूर्ण

अटल पूर्णांक ohci_sm501_start(काष्ठा usb_hcd *hcd)
अणु
	काष्ठा device *dev = hcd->self.controller;
	पूर्णांक ret;

	ret = ohci_run(hcd_to_ohci(hcd));
	अगर (ret < 0) अणु
		dev_err(dev, "can't start %s", hcd->self.bus_name);
		ohci_stop(hcd);
	पूर्ण

	वापस ret;
पूर्ण

/*-------------------------------------------------------------------------*/

अटल स्थिर काष्ठा hc_driver ohci_sm501_hc_driver = अणु
	.description =		hcd_name,
	.product_desc =		"SM501 OHCI",
	.hcd_priv_size =	माप(काष्ठा ohci_hcd),

	/*
	 * generic hardware linkage
	 */
	.irq =			ohci_irq,
	.flags =		HCD_USB11 | HCD_MEMORY,

	/*
	 * basic lअगरecycle operations
	 */
	.reset =		ohci_sm501_init,
	.start =		ohci_sm501_start,
	.stop =			ohci_stop,
	.shutकरोwn =		ohci_shutकरोwn,

	/*
	 * managing i/o requests and associated device resources
	 */
	.urb_enqueue =		ohci_urb_enqueue,
	.urb_dequeue =		ohci_urb_dequeue,
	.endpoपूर्णांक_disable =	ohci_endpoपूर्णांक_disable,

	/*
	 * scheduling support
	 */
	.get_frame_number =	ohci_get_frame,

	/*
	 * root hub support
	 */
	.hub_status_data =	ohci_hub_status_data,
	.hub_control =		ohci_hub_control,
#अगर_घोषित	CONFIG_PM
	.bus_suspend =		ohci_bus_suspend,
	.bus_resume =		ohci_bus_resume,
#पूर्ण_अगर
	.start_port_reset =	ohci_start_port_reset,
पूर्ण;

/*-------------------------------------------------------------------------*/

अटल पूर्णांक ohci_hcd_sm501_drv_probe(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा hc_driver *driver = &ohci_sm501_hc_driver;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा resource	*res, *mem;
	पूर्णांक retval, irq;
	काष्ठा usb_hcd *hcd = शून्य;

	irq = retval = platक्रमm_get_irq(pdev, 0);
	अगर (retval < 0)
		जाओ err0;

	mem = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 1);
	अगर (mem == शून्य) अणु
		dev_err(dev, "no resource definition for memory\n");
		retval = -ENOENT;
		जाओ err0;
	पूर्ण

	अगर (!request_mem_region(mem->start, resource_size(mem), pdev->name)) अणु
		dev_err(dev, "request_mem_region failed\n");
		retval = -EBUSY;
		जाओ err0;
	पूर्ण

	/* allocate, reserve and remap resources क्रम रेजिस्टरs */
	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (res == शून्य) अणु
		dev_err(dev, "no resource definition for registers\n");
		retval = -ENOENT;
		जाओ err1;
	पूर्ण

	hcd = usb_create_hcd(driver, &pdev->dev, dev_name(&pdev->dev));
	अगर (!hcd) अणु
		retval = -ENOMEM;
		जाओ err1;
	पूर्ण

	hcd->rsrc_start = res->start;
	hcd->rsrc_len = resource_size(res);

	अगर (!request_mem_region(hcd->rsrc_start, hcd->rsrc_len,	pdev->name)) अणु
		dev_err(dev, "request_mem_region failed\n");
		retval = -EBUSY;
		जाओ err3;
	पूर्ण

	hcd->regs = ioremap(hcd->rsrc_start, hcd->rsrc_len);
	अगर (hcd->regs == शून्य) अणु
		dev_err(dev, "cannot remap registers\n");
		retval = -ENXIO;
		जाओ err4;
	पूर्ण

	ohci_hcd_init(hcd_to_ohci(hcd));

	/* The sm501 chip is equipped with local memory that may be used
	 * by on-chip devices such as the video controller and the usb host.
	 * This driver uses genalloc so that usb allocations with
	 * gen_pool_dma_alloc() allocate from this local memory. The dma_handle
	 * वापसed by gen_pool_dma_alloc() will be an offset starting from 0
	 * क्रम the first local memory byte.
	 *
	 * So as दीर्घ as data is allocated using gen_pool_dma_alloc() all is
	 * fine. This is however not always the हाल - buffers may be allocated
	 * using kदो_स्मृति() - so the usb core needs to be told that it must copy
	 * data पूर्णांकo our local memory अगर the buffers happen to be placed in
	 * regular memory. A non-null hcd->localmem_pool initialized by the
	 * the call to usb_hcd_setup_local_mem() below करोes just that.
	 */

	retval = usb_hcd_setup_local_mem(hcd, mem->start,
					 mem->start - mem->parent->start,
					 resource_size(mem));
	अगर (retval < 0)
		जाओ err5;
	retval = usb_add_hcd(hcd, irq, IRQF_SHARED);
	अगर (retval)
		जाओ err5;
	device_wakeup_enable(hcd->self.controller);

	/* enable घातer and unmask पूर्णांकerrupts */

	sm501_unit_घातer(dev->parent, SM501_GATE_USB_HOST, 1);
	sm501_modअगरy_reg(dev->parent, SM501_IRQ_MASK, 1 << 6, 0);

	वापस 0;
err5:
	iounmap(hcd->regs);
err4:
	release_mem_region(hcd->rsrc_start, hcd->rsrc_len);
err3:
	usb_put_hcd(hcd);
err1:
	release_mem_region(mem->start, resource_size(mem));
err0:
	वापस retval;
पूर्ण

अटल पूर्णांक ohci_hcd_sm501_drv_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा usb_hcd *hcd = platक्रमm_get_drvdata(pdev);
	काष्ठा resource	*mem;

	usb_हटाओ_hcd(hcd);
	iounmap(hcd->regs);
	release_mem_region(hcd->rsrc_start, hcd->rsrc_len);
	usb_put_hcd(hcd);
	mem = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 1);
	अगर (mem)
		release_mem_region(mem->start, resource_size(mem));

	/* mask पूर्णांकerrupts and disable घातer */

	sm501_modअगरy_reg(pdev->dev.parent, SM501_IRQ_MASK, 0, 1 << 6);
	sm501_unit_घातer(pdev->dev.parent, SM501_GATE_USB_HOST, 0);

	वापस 0;
पूर्ण

/*-------------------------------------------------------------------------*/

#अगर_घोषित CONFIG_PM
अटल पूर्णांक ohci_sm501_suspend(काष्ठा platक्रमm_device *pdev, pm_message_t msg)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा usb_hcd  *hcd = platक्रमm_get_drvdata(pdev);
	काष्ठा ohci_hcd	*ohci = hcd_to_ohci(hcd);
	bool करो_wakeup = device_may_wakeup(dev);
	पूर्णांक ret;

	अगर (समय_beक्रमe(jअगरfies, ohci->next_statechange))
		msleep(5);
	ohci->next_statechange = jअगरfies;

	ret = ohci_suspend(hcd, करो_wakeup);
	अगर (ret)
		वापस ret;

	sm501_unit_घातer(dev->parent, SM501_GATE_USB_HOST, 0);
	वापस ret;
पूर्ण

अटल पूर्णांक ohci_sm501_resume(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा usb_hcd	*hcd = platक्रमm_get_drvdata(pdev);
	काष्ठा ohci_hcd	*ohci = hcd_to_ohci(hcd);

	अगर (समय_beक्रमe(jअगरfies, ohci->next_statechange))
		msleep(5);
	ohci->next_statechange = jअगरfies;

	sm501_unit_घातer(dev->parent, SM501_GATE_USB_HOST, 1);
	ohci_resume(hcd, false);
	वापस 0;
पूर्ण
#अन्यथा
#घोषणा ohci_sm501_suspend शून्य
#घोषणा ohci_sm501_resume शून्य
#पूर्ण_अगर

/*-------------------------------------------------------------------------*/

/*
 * Driver definition to रेजिस्टर with the SM501 bus
 */
अटल काष्ठा platक्रमm_driver ohci_hcd_sm501_driver = अणु
	.probe		= ohci_hcd_sm501_drv_probe,
	.हटाओ		= ohci_hcd_sm501_drv_हटाओ,
	.shutकरोwn	= usb_hcd_platक्रमm_shutकरोwn,
	.suspend	= ohci_sm501_suspend,
	.resume		= ohci_sm501_resume,
	.driver		= अणु
		.name	= "sm501-usb",
	पूर्ण,
पूर्ण;
MODULE_ALIAS("platform:sm501-usb");
