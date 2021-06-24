<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Cadence PCI Glue driver.
 *
 * Copyright (C) 2019 Cadence.
 *
 * Author: Pawel Laszczak <pawell@cadence.com>
 *
 */

#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/pci.h>

#समावेश "core.h"
#समावेश "gadget-export.h"

#घोषणा PCI_BAR_HOST		0
#घोषणा PCI_BAR_OTG		0
#घोषणा PCI_BAR_DEV		2

#घोषणा PCI_DEV_FN_HOST_DEVICE	0
#घोषणा PCI_DEV_FN_OTG		1

#घोषणा PCI_DRIVER_NAME		"cdns-pci-usbssp"
#घोषणा PLAT_DRIVER_NAME	"cdns-usbssp"

#घोषणा CDNS_VENDOR_ID		0x17cd
#घोषणा CDNS_DEVICE_ID		0x0100
#घोषणा CDNS_DRD_IF		(PCI_CLASS_SERIAL_USB << 8 | 0x80)

अटल काष्ठा pci_dev *cdnsp_get_second_fun(काष्ठा pci_dev *pdev)
अणु
	काष्ठा pci_dev *func;

	/*
	 * Gets the second function.
	 * It's little tricky, but this platक्रमm has two function.
	 * The fist keeps resources क्रम Host/Device जबतक the second
	 * keeps resources क्रम DRD/OTG.
	 */
	func = pci_get_device(pdev->venकरोr, pdev->device, शून्य);
	अगर (!func)
		वापस शून्य;

	अगर (func->devfn == pdev->devfn) अणु
		func = pci_get_device(pdev->venकरोr, pdev->device, func);
		अगर (!func)
			वापस शून्य;
	पूर्ण

	वापस func;
पूर्ण

अटल पूर्णांक cdnsp_pci_probe(काष्ठा pci_dev *pdev,
			   स्थिर काष्ठा pci_device_id *id)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा pci_dev *func;
	काष्ठा resource *res;
	काष्ठा cdns *cdnsp;
	पूर्णांक ret;

	/*
	 * For GADGET/HOST PCI (devfn) function number is 0,
	 * क्रम OTG PCI (devfn) function number is 1.
	 */
	अगर (!id || (pdev->devfn != PCI_DEV_FN_HOST_DEVICE &&
		    pdev->devfn != PCI_DEV_FN_OTG))
		वापस -EINVAL;

	func = cdnsp_get_second_fun(pdev);
	अगर (!func)
		वापस -EINVAL;

	अगर (func->class == PCI_CLASS_SERIAL_USB_XHCI ||
	    pdev->class == PCI_CLASS_SERIAL_USB_XHCI) अणु
		ret = -EINVAL;
		जाओ put_pci;
	पूर्ण

	ret = pcim_enable_device(pdev);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Enabling PCI device has failed %d\n", ret);
		जाओ put_pci;
	पूर्ण

	pci_set_master(pdev);
	अगर (pci_is_enabled(func)) अणु
		cdnsp = pci_get_drvdata(func);
	पूर्ण अन्यथा अणु
		cdnsp = kzalloc(माप(*cdnsp), GFP_KERNEL);
		अगर (!cdnsp) अणु
			ret = -ENOMEM;
			जाओ disable_pci;
		पूर्ण
	पूर्ण

	/* For GADGET device function number is 0. */
	अगर (pdev->devfn == 0) अणु
		resource_माप_प्रकार rsrc_start, rsrc_len;

		/* Function 0: host(BAR_0) + device(BAR_1).*/
		dev_dbg(dev, "Initialize resources\n");
		rsrc_start = pci_resource_start(pdev, PCI_BAR_DEV);
		rsrc_len = pci_resource_len(pdev, PCI_BAR_DEV);
		res = devm_request_mem_region(dev, rsrc_start, rsrc_len, "dev");
		अगर (!res) अणु
			dev_dbg(dev, "controller already in use\n");
			ret = -EBUSY;
			जाओ मुक्त_cdnsp;
		पूर्ण

		cdnsp->dev_regs = devm_ioremap(dev, rsrc_start, rsrc_len);
		अगर (!cdnsp->dev_regs) अणु
			dev_dbg(dev, "error mapping memory\n");
			ret = -EFAULT;
			जाओ मुक्त_cdnsp;
		पूर्ण

		cdnsp->dev_irq = pdev->irq;
		dev_dbg(dev, "USBSS-DEV physical base addr: %pa\n",
			&rsrc_start);

		res = &cdnsp->xhci_res[0];
		res->start = pci_resource_start(pdev, PCI_BAR_HOST);
		res->end = pci_resource_end(pdev, PCI_BAR_HOST);
		res->name = "xhci";
		res->flags = IORESOURCE_MEM;
		dev_dbg(dev, "USBSS-XHCI physical base addr: %pa\n",
			&res->start);

		/* Interrupt क्रम XHCI, */
		res = &cdnsp->xhci_res[1];
		res->start = pdev->irq;
		res->name = "host";
		res->flags = IORESOURCE_IRQ;
	पूर्ण अन्यथा अणु
		res = &cdnsp->otg_res;
		res->start = pci_resource_start(pdev, PCI_BAR_OTG);
		res->end =   pci_resource_end(pdev, PCI_BAR_OTG);
		res->name = "otg";
		res->flags = IORESOURCE_MEM;
		dev_dbg(dev, "CDNSP-DRD physical base addr: %pa\n",
			&res->start);

		/* Interrupt क्रम OTG/DRD. */
		cdnsp->otg_irq = pdev->irq;
	पूर्ण

	अगर (pci_is_enabled(func)) अणु
		cdnsp->dev = dev;
		cdnsp->gadget_init = cdnsp_gadget_init;

		ret = cdns_init(cdnsp);
		अगर (ret)
			जाओ मुक्त_cdnsp;
	पूर्ण

	pci_set_drvdata(pdev, cdnsp);

	device_wakeup_enable(&pdev->dev);
	अगर (pci_dev_run_wake(pdev))
		pm_runसमय_put_noidle(&pdev->dev);

	वापस 0;

मुक्त_cdnsp:
	अगर (!pci_is_enabled(func))
		kमुक्त(cdnsp);

disable_pci:
	pci_disable_device(pdev);

put_pci:
	pci_dev_put(func);

	वापस ret;
पूर्ण

अटल व्योम cdnsp_pci_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा cdns *cdnsp;
	काष्ठा pci_dev *func;

	func = cdnsp_get_second_fun(pdev);
	cdnsp = (काष्ठा cdns *)pci_get_drvdata(pdev);

	अगर (pci_dev_run_wake(pdev))
		pm_runसमय_get_noresume(&pdev->dev);

	अगर (!pci_is_enabled(func)) अणु
		kमुक्त(cdnsp);
		जाओ pci_put;
	पूर्ण

	cdns_हटाओ(cdnsp);

pci_put:
	pci_dev_put(func);
पूर्ण

अटल पूर्णांक __maybe_unused cdnsp_pci_suspend(काष्ठा device *dev)
अणु
	काष्ठा cdns *cdns = dev_get_drvdata(dev);

	वापस cdns_suspend(cdns);
पूर्ण

अटल पूर्णांक __maybe_unused cdnsp_pci_resume(काष्ठा device *dev)
अणु
	काष्ठा cdns *cdns = dev_get_drvdata(dev);
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	spin_lock_irqsave(&cdns->lock, flags);
	ret = cdns_resume(cdns, 1);
	spin_unlock_irqrestore(&cdns->lock, flags);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops cdnsp_pci_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(cdnsp_pci_suspend, cdnsp_pci_resume)
पूर्ण;

अटल स्थिर काष्ठा pci_device_id cdnsp_pci_ids[] = अणु
	अणु PCI_VENDOR_ID_CDNS, CDNS_DEVICE_ID, PCI_ANY_ID, PCI_ANY_ID,
	  PCI_CLASS_SERIAL_USB_DEVICE, PCI_ANY_ID पूर्ण,
	अणु PCI_VENDOR_ID_CDNS, CDNS_DEVICE_ID, PCI_ANY_ID, PCI_ANY_ID,
	  CDNS_DRD_IF, PCI_ANY_ID पूर्ण,
	अणु 0, पूर्ण
पूर्ण;

अटल काष्ठा pci_driver cdnsp_pci_driver = अणु
	.name = "cdnsp-pci",
	.id_table = &cdnsp_pci_ids[0],
	.probe = cdnsp_pci_probe,
	.हटाओ = cdnsp_pci_हटाओ,
	.driver = अणु
		.pm = &cdnsp_pci_pm_ops,
	पूर्ण
पूर्ण;

module_pci_driver(cdnsp_pci_driver);
MODULE_DEVICE_TABLE(pci, cdnsp_pci_ids);

MODULE_ALIAS("pci:cdnsp");
MODULE_AUTHOR("Pawel Laszczak <pawell@cadence.com>");
MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("Cadence CDNSP PCI driver");
