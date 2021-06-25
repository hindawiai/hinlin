<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  PS3 OHCI Host Controller driver
 *
 *  Copyright (C) 2006 Sony Computer Entertainment Inc.
 *  Copyright 2006 Sony Corp.
 */

#समावेश <यंत्र/firmware.h>
#समावेश <यंत्र/ps3.h>

अटल पूर्णांक ps3_ohci_hc_reset(काष्ठा usb_hcd *hcd)
अणु
	काष्ठा ohci_hcd *ohci = hcd_to_ohci(hcd);

	ohci->flags |= OHCI_QUIRK_BE_MMIO;
	ohci_hcd_init(ohci);
	वापस ohci_init(ohci);
पूर्ण

अटल पूर्णांक ps3_ohci_hc_start(काष्ठा usb_hcd *hcd)
अणु
	पूर्णांक result;
	काष्ठा ohci_hcd *ohci = hcd_to_ohci(hcd);

	/* Handle root hub init quirk in spider south bridge. */
	/* Also set PwrOn2PwrGood to 0x7f (254ms). */

	ohci_ग_लिखोl(ohci, 0x7f000000 | RH_A_PSM | RH_A_OCPM,
		&ohci->regs->roothub.a);
	ohci_ग_लिखोl(ohci, 0x00060000, &ohci->regs->roothub.b);

	result = ohci_run(ohci);

	अगर (result < 0) अणु
		dev_err(hcd->self.controller, "can't start %s\n",
			hcd->self.bus_name);
		ohci_stop(hcd);
	पूर्ण

	वापस result;
पूर्ण

अटल स्थिर काष्ठा hc_driver ps3_ohci_hc_driver = अणु
	.description		= hcd_name,
	.product_desc		= "PS3 OHCI Host Controller",
	.hcd_priv_size		= माप(काष्ठा ohci_hcd),
	.irq			= ohci_irq,
	.flags			= HCD_MEMORY | HCD_DMA | HCD_USB11,
	.reset			= ps3_ohci_hc_reset,
	.start			= ps3_ohci_hc_start,
	.stop			= ohci_stop,
	.shutकरोwn		= ohci_shutकरोwn,
	.urb_enqueue		= ohci_urb_enqueue,
	.urb_dequeue		= ohci_urb_dequeue,
	.endpoपूर्णांक_disable	= ohci_endpoपूर्णांक_disable,
	.get_frame_number	= ohci_get_frame,
	.hub_status_data	= ohci_hub_status_data,
	.hub_control		= ohci_hub_control,
	.start_port_reset	= ohci_start_port_reset,
#अगर defined(CONFIG_PM)
	.bus_suspend 		= ohci_bus_suspend,
	.bus_resume 		= ohci_bus_resume,
#पूर्ण_अगर
पूर्ण;

अटल पूर्णांक ps3_ohci_probe(काष्ठा ps3_प्रणाली_bus_device *dev)
अणु
	पूर्णांक result;
	काष्ठा usb_hcd *hcd;
	अचिन्हित पूर्णांक virq;
	अटल u64 dummy_mask;

	अगर (usb_disabled()) अणु
		result = -ENODEV;
		जाओ fail_start;
	पूर्ण

	result = ps3_खोलो_hv_device(dev);

	अगर (result) अणु
		dev_dbg(&dev->core, "%s:%d: ps3_open_hv_device failed: %s\n",
			__func__, __LINE__, ps3_result(result));
		result = -EPERM;
		जाओ fail_खोलो;
	पूर्ण

	result = ps3_dma_region_create(dev->d_region);

	अगर (result) अणु
		dev_dbg(&dev->core, "%s:%d: ps3_dma_region_create failed: "
			"(%d)\n", __func__, __LINE__, result);
		BUG_ON("check region type");
		जाओ fail_dma_region;
	पूर्ण

	result = ps3_mmio_region_create(dev->m_region);

	अगर (result) अणु
		dev_dbg(&dev->core, "%s:%d: ps3_map_mmio_region failed\n",
			__func__, __LINE__);
		result = -EPERM;
		जाओ fail_mmio_region;
	पूर्ण

	dev_dbg(&dev->core, "%s:%d: mmio mapped_addr %lxh\n", __func__,
		__LINE__, dev->m_region->lpar_addr);

	result = ps3_io_irq_setup(PS3_BINDING_CPU_ANY, dev->पूर्णांकerrupt_id, &virq);

	अगर (result) अणु
		dev_dbg(&dev->core, "%s:%d: ps3_construct_io_irq(%d) failed.\n",
			__func__, __LINE__, virq);
		result = -EPERM;
		जाओ fail_irq;
	पूर्ण

	dummy_mask = DMA_BIT_MASK(32);
	dev->core.dma_mask = &dummy_mask;
	dma_set_coherent_mask(&dev->core, dummy_mask);

	hcd = usb_create_hcd(&ps3_ohci_hc_driver, &dev->core, dev_name(&dev->core));

	अगर (!hcd) अणु
		dev_dbg(&dev->core, "%s:%d: usb_create_hcd failed\n", __func__,
			__LINE__);
		result = -ENOMEM;
		जाओ fail_create_hcd;
	पूर्ण

	hcd->rsrc_start = dev->m_region->lpar_addr;
	hcd->rsrc_len = dev->m_region->len;

	अगर (!request_mem_region(hcd->rsrc_start, hcd->rsrc_len, hcd_name))
		dev_dbg(&dev->core, "%s:%d: request_mem_region failed\n",
			__func__, __LINE__);

	hcd->regs = ioremap(dev->m_region->lpar_addr, dev->m_region->len);

	अगर (!hcd->regs) अणु
		dev_dbg(&dev->core, "%s:%d: ioremap failed\n", __func__,
			__LINE__);
		result = -EPERM;
		जाओ fail_ioremap;
	पूर्ण

	dev_dbg(&dev->core, "%s:%d: hcd->rsrc_start %lxh\n", __func__, __LINE__,
		(अचिन्हित दीर्घ)hcd->rsrc_start);
	dev_dbg(&dev->core, "%s:%d: hcd->rsrc_len   %lxh\n", __func__, __LINE__,
		(अचिन्हित दीर्घ)hcd->rsrc_len);
	dev_dbg(&dev->core, "%s:%d: hcd->regs       %lxh\n", __func__, __LINE__,
		(अचिन्हित दीर्घ)hcd->regs);
	dev_dbg(&dev->core, "%s:%d: virq            %lu\n", __func__, __LINE__,
		(अचिन्हित दीर्घ)virq);

	ps3_प्रणाली_bus_set_drvdata(dev, hcd);

	result = usb_add_hcd(hcd, virq, 0);

	अगर (result) अणु
		dev_dbg(&dev->core, "%s:%d: usb_add_hcd failed (%d)\n",
			__func__, __LINE__, result);
		जाओ fail_add_hcd;
	पूर्ण

	device_wakeup_enable(hcd->self.controller);
	वापस result;

fail_add_hcd:
	iounmap(hcd->regs);
fail_ioremap:
	release_mem_region(hcd->rsrc_start, hcd->rsrc_len);
	usb_put_hcd(hcd);
fail_create_hcd:
	ps3_io_irq_destroy(virq);
fail_irq:
	ps3_मुक्त_mmio_region(dev->m_region);
fail_mmio_region:
	ps3_dma_region_मुक्त(dev->d_region);
fail_dma_region:
	ps3_बंद_hv_device(dev);
fail_खोलो:
fail_start:
	वापस result;
पूर्ण

अटल व्योम ps3_ohci_हटाओ(काष्ठा ps3_प्रणाली_bus_device *dev)
अणु
	अचिन्हित पूर्णांक पंचांगp;
	काष्ठा usb_hcd *hcd = ps3_प्रणाली_bus_get_drvdata(dev);

	BUG_ON(!hcd);

	dev_dbg(&dev->core, "%s:%d: regs %p\n", __func__, __LINE__, hcd->regs);
	dev_dbg(&dev->core, "%s:%d: irq %u\n", __func__, __LINE__, hcd->irq);

	पंचांगp = hcd->irq;

	ohci_shutकरोwn(hcd);
	usb_हटाओ_hcd(hcd);

	ps3_प्रणाली_bus_set_drvdata(dev, शून्य);

	BUG_ON(!hcd->regs);
	iounmap(hcd->regs);

	release_mem_region(hcd->rsrc_start, hcd->rsrc_len);
	usb_put_hcd(hcd);

	ps3_io_irq_destroy(पंचांगp);
	ps3_मुक्त_mmio_region(dev->m_region);

	ps3_dma_region_मुक्त(dev->d_region);
	ps3_बंद_hv_device(dev);
पूर्ण

अटल पूर्णांक __init ps3_ohci_driver_रेजिस्टर(काष्ठा ps3_प्रणाली_bus_driver *drv)
अणु
	वापस firmware_has_feature(FW_FEATURE_PS3_LV1)
		? ps3_प्रणाली_bus_driver_रेजिस्टर(drv)
		: 0;
पूर्ण

अटल व्योम ps3_ohci_driver_unरेजिस्टर(काष्ठा ps3_प्रणाली_bus_driver *drv)
अणु
	अगर (firmware_has_feature(FW_FEATURE_PS3_LV1))
		ps3_प्रणाली_bus_driver_unरेजिस्टर(drv);
पूर्ण

MODULE_ALIAS(PS3_MODULE_ALIAS_OHCI);

अटल काष्ठा ps3_प्रणाली_bus_driver ps3_ohci_driver = अणु
	.core.name = "ps3-ohci-driver",
	.core.owner = THIS_MODULE,
	.match_id = PS3_MATCH_ID_OHCI,
	.probe = ps3_ohci_probe,
	.हटाओ = ps3_ohci_हटाओ,
	.shutकरोwn = ps3_ohci_हटाओ,
पूर्ण;
