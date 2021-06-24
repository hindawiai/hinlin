<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  PS3 EHCI Host Controller driver
 *
 *  Copyright (C) 2006 Sony Computer Entertainment Inc.
 *  Copyright 2006 Sony Corp.
 */

#समावेश <यंत्र/firmware.h>
#समावेश <यंत्र/ps3.h>

अटल व्योम ps3_ehci_setup_insnreg(काष्ठा ehci_hcd *ehci)
अणु
	/* PS3 HC पूर्णांकernal setup रेजिस्टर offsets. */

	क्रमागत ps3_ehci_hc_insnreg अणु
		ps3_ehci_hc_insnreg01 = 0x084,
		ps3_ehci_hc_insnreg02 = 0x088,
		ps3_ehci_hc_insnreg03 = 0x08c,
	पूर्ण;

	/* PS3 EHCI HC errata fix 316 - The PS3 EHCI HC will reset its
	 * पूर्णांकernal INSNREGXX setup regs back to the chip शेष values
	 * on Host Controller Reset (CMD_RESET) or Light Host Controller
	 * Reset (CMD_LRESET).  The work-around क्रम this is क्रम the HC
	 * driver to re-initialise these regs when ever the HC is reset.
	 */

	/* Set burst transfer counts to 256 out, 32 in. */

	ग_लिखोl_be(0x01000020, (व्योम __iomem *)ehci->regs +
		ps3_ehci_hc_insnreg01);

	/* Enable burst transfer counts. */

	ग_लिखोl_be(0x00000001, (व्योम __iomem *)ehci->regs +
		ps3_ehci_hc_insnreg03);
पूर्ण

अटल पूर्णांक ps3_ehci_hc_reset(काष्ठा usb_hcd *hcd)
अणु
	पूर्णांक result;
	काष्ठा ehci_hcd *ehci = hcd_to_ehci(hcd);

	ehci->big_endian_mmio = 1;
	ehci->caps = hcd->regs;

	result = ehci_setup(hcd);
	अगर (result)
		वापस result;

	ps3_ehci_setup_insnreg(ehci);

	वापस result;
पूर्ण

अटल स्थिर काष्ठा hc_driver ps3_ehci_hc_driver = अणु
	.description		= hcd_name,
	.product_desc		= "PS3 EHCI Host Controller",
	.hcd_priv_size		= माप(काष्ठा ehci_hcd),
	.irq			= ehci_irq,
	.flags			= HCD_MEMORY | HCD_DMA | HCD_USB2 | HCD_BH,
	.reset			= ps3_ehci_hc_reset,
	.start			= ehci_run,
	.stop			= ehci_stop,
	.shutकरोwn		= ehci_shutकरोwn,
	.urb_enqueue		= ehci_urb_enqueue,
	.urb_dequeue		= ehci_urb_dequeue,
	.endpoपूर्णांक_disable	= ehci_endpoपूर्णांक_disable,
	.endpoपूर्णांक_reset		= ehci_endpoपूर्णांक_reset,
	.get_frame_number	= ehci_get_frame,
	.hub_status_data	= ehci_hub_status_data,
	.hub_control		= ehci_hub_control,
#अगर defined(CONFIG_PM)
	.bus_suspend		= ehci_bus_suspend,
	.bus_resume		= ehci_bus_resume,
#पूर्ण_अगर
	.relinquish_port	= ehci_relinquish_port,
	.port_handed_over	= ehci_port_handed_over,

	.clear_tt_buffer_complete	= ehci_clear_tt_buffer_complete,
पूर्ण;

अटल पूर्णांक ps3_ehci_probe(काष्ठा ps3_प्रणाली_bus_device *dev)
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
		dev_dbg(&dev->core, "%s:%d: ps3_open_hv_device failed\n",
			__func__, __LINE__);
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

	hcd = usb_create_hcd(&ps3_ehci_hc_driver, &dev->core, dev_name(&dev->core));

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

अटल व्योम ps3_ehci_हटाओ(काष्ठा ps3_प्रणाली_bus_device *dev)
अणु
	अचिन्हित पूर्णांक पंचांगp;
	काष्ठा usb_hcd *hcd = ps3_प्रणाली_bus_get_drvdata(dev);

	BUG_ON(!hcd);

	dev_dbg(&dev->core, "%s:%d: regs %p\n", __func__, __LINE__, hcd->regs);
	dev_dbg(&dev->core, "%s:%d: irq %u\n", __func__, __LINE__, hcd->irq);

	पंचांगp = hcd->irq;

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

अटल पूर्णांक __init ps3_ehci_driver_रेजिस्टर(काष्ठा ps3_प्रणाली_bus_driver *drv)
अणु
	वापस firmware_has_feature(FW_FEATURE_PS3_LV1)
		? ps3_प्रणाली_bus_driver_रेजिस्टर(drv)
		: 0;
पूर्ण

अटल व्योम ps3_ehci_driver_unरेजिस्टर(काष्ठा ps3_प्रणाली_bus_driver *drv)
अणु
	अगर (firmware_has_feature(FW_FEATURE_PS3_LV1))
		ps3_प्रणाली_bus_driver_unरेजिस्टर(drv);
पूर्ण

MODULE_ALIAS(PS3_MODULE_ALIAS_EHCI);

अटल काष्ठा ps3_प्रणाली_bus_driver ps3_ehci_driver = अणु
	.core.name = "ps3-ehci-driver",
	.core.owner = THIS_MODULE,
	.match_id = PS3_MATCH_ID_EHCI,
	.probe = ps3_ehci_probe,
	.हटाओ = ps3_ehci_हटाओ,
	.shutकरोwn = ps3_ehci_हटाओ,
पूर्ण;
