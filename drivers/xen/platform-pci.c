<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/******************************************************************************
 * platक्रमm-pci.c
 *
 * Xen platक्रमm PCI device driver
 *
 * Authors: ssmith@xensource.com and stefano.stabellini@eu.citrix.com
 *
 * Copyright (c) 2005, Intel Corporation.
 * Copyright (c) 2007, XenSource Inc.
 * Copyright (c) 2010, Citrix
 */


#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/init.h>
#समावेश <linux/pci.h>

#समावेश <xen/platक्रमm_pci.h>
#समावेश <xen/grant_table.h>
#समावेश <xen/xenbus.h>
#समावेश <xen/events.h>
#समावेश <xen/hvm.h>
#समावेश <xen/xen-ops.h>

#घोषणा DRV_NAME    "xen-platform-pci"

अटल अचिन्हित दीर्घ platक्रमm_mmio;
अटल अचिन्हित दीर्घ platक्रमm_mmio_alloc;
अटल अचिन्हित दीर्घ platक्रमm_mmiolen;
अटल uपूर्णांक64_t callback_via;

अटल अचिन्हित दीर्घ alloc_xen_mmio(अचिन्हित दीर्घ len)
अणु
	अचिन्हित दीर्घ addr;

	addr = platक्रमm_mmio + platक्रमm_mmio_alloc;
	platक्रमm_mmio_alloc += len;
	BUG_ON(platक्रमm_mmio_alloc > platक्रमm_mmiolen);

	वापस addr;
पूर्ण

अटल uपूर्णांक64_t get_callback_via(काष्ठा pci_dev *pdev)
अणु
	u8 pin;
	पूर्णांक irq;

	irq = pdev->irq;
	अगर (irq < 16)
		वापस irq; /* ISA IRQ */

	pin = pdev->pin;

	/* We करोn't know the GSI. Specअगरy the PCI INTx line instead. */
	वापस ((uपूर्णांक64_t)0x01 << HVM_CALLBACK_VIA_TYPE_SHIFT) | /* PCI INTx identअगरier */
		((uपूर्णांक64_t)pci_करोमुख्य_nr(pdev->bus) << 32) |
		((uपूर्णांक64_t)pdev->bus->number << 16) |
		((uपूर्णांक64_t)(pdev->devfn & 0xff) << 8) |
		((uपूर्णांक64_t)(pin - 1) & 3);
पूर्ण

अटल irqवापस_t करो_hvm_evtchn_पूर्णांकr(पूर्णांक irq, व्योम *dev_id)
अणु
	xen_hvm_evtchn_करो_upcall();
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक xen_allocate_irq(काष्ठा pci_dev *pdev)
अणु
	वापस request_irq(pdev->irq, करो_hvm_evtchn_पूर्णांकr,
			IRQF_NOBALANCING | IRQF_TRIGGER_RISING,
			"xen-platform-pci", pdev);
पूर्ण

अटल पूर्णांक platक्रमm_pci_resume(काष्ठा device *dev)
अणु
	पूर्णांक err;

	अगर (xen_have_vector_callback)
		वापस 0;

	err = xen_set_callback_via(callback_via);
	अगर (err) अणु
		dev_err(dev, "platform_pci_resume failure!\n");
		वापस err;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक platक्रमm_pci_probe(काष्ठा pci_dev *pdev,
			      स्थिर काष्ठा pci_device_id *ent)
अणु
	पूर्णांक i, ret;
	दीर्घ ioaddr;
	दीर्घ mmio_addr, mmio_len;
	अचिन्हित पूर्णांक max_nr_gframes;
	अचिन्हित दीर्घ grant_frames;

	अगर (!xen_करोमुख्य())
		वापस -ENODEV;

	i = pci_enable_device(pdev);
	अगर (i)
		वापस i;

	ioaddr = pci_resource_start(pdev, 0);

	mmio_addr = pci_resource_start(pdev, 1);
	mmio_len = pci_resource_len(pdev, 1);

	अगर (mmio_addr == 0 || ioaddr == 0) अणु
		dev_err(&pdev->dev, "no resources found\n");
		ret = -ENOENT;
		जाओ pci_out;
	पूर्ण

	ret = pci_request_region(pdev, 1, DRV_NAME);
	अगर (ret < 0)
		जाओ pci_out;

	ret = pci_request_region(pdev, 0, DRV_NAME);
	अगर (ret < 0)
		जाओ mem_out;

	platक्रमm_mmio = mmio_addr;
	platक्रमm_mmiolen = mmio_len;
	अगर (!xen_have_vector_callback) अणु
		ret = xen_allocate_irq(pdev);
		अगर (ret) अणु
			dev_warn(&pdev->dev, "request_irq failed err=%d\n", ret);
			जाओ out;
		पूर्ण
		/*
		 * It करोesn't strictly *have* to run on CPU0 but it sure
		 * as hell better process the event channel ports delivered
		 * to CPU0.
		 */
		irq_set_affinity(pdev->irq, cpumask_of(0));

		callback_via = get_callback_via(pdev);
		ret = xen_set_callback_via(callback_via);
		अगर (ret) अणु
			dev_warn(&pdev->dev, "Unable to set the evtchn callback "
					 "err=%d\n", ret);
			जाओ out;
		पूर्ण
	पूर्ण

	max_nr_gframes = gnttab_max_grant_frames();
	grant_frames = alloc_xen_mmio(PAGE_SIZE * max_nr_gframes);
	ret = gnttab_setup_स्वतः_xlat_frames(grant_frames);
	अगर (ret)
		जाओ out;
	ret = gnttab_init();
	अगर (ret)
		जाओ grant_out;
	वापस 0;
grant_out:
	gnttab_मुक्त_स्वतः_xlat_frames();
out:
	pci_release_region(pdev, 0);
mem_out:
	pci_release_region(pdev, 1);
pci_out:
	pci_disable_device(pdev);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा pci_device_id platक्रमm_pci_tbl[] = अणु
	अणुPCI_VENDOR_ID_XEN, PCI_DEVICE_ID_XEN_PLATFORM,
		PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0पूर्ण,
	अणु0,पूर्ण
पूर्ण;

अटल स्थिर काष्ठा dev_pm_ops platक्रमm_pm_ops = अणु
	.resume_noirq =   platक्रमm_pci_resume,
पूर्ण;

अटल काष्ठा pci_driver platक्रमm_driver = अणु
	.name =           DRV_NAME,
	.probe =          platक्रमm_pci_probe,
	.id_table =       platक्रमm_pci_tbl,
	.driver = अणु
		.pm =     &platक्रमm_pm_ops,
	पूर्ण,
पूर्ण;

builtin_pci_driver(platक्रमm_driver);
