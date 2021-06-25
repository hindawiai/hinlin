<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Cadence USBSS PCI Glue driver
 *
 * Copyright (C) 2018-2019 Cadence.
 *
 * Author: Pawel Laszczak <pawell@cadence.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/slab.h>

काष्ठा cdns3_wrap अणु
	काष्ठा platक्रमm_device *plat_dev;
	काष्ठा resource dev_res[6];
	पूर्णांक devfn;
पूर्ण;

#घोषणा RES_IRQ_HOST_ID		0
#घोषणा RES_IRQ_PERIPHERAL_ID	1
#घोषणा RES_IRQ_OTG_ID		2
#घोषणा RES_HOST_ID		3
#घोषणा RES_DEV_ID		4
#घोषणा RES_DRD_ID		5

#घोषणा PCI_BAR_HOST		0
#घोषणा PCI_BAR_DEV		2
#घोषणा PCI_BAR_OTG		0

#घोषणा PCI_DEV_FN_HOST_DEVICE	0
#घोषणा PCI_DEV_FN_OTG		1

#घोषणा PCI_DRIVER_NAME		"cdns3-pci-usbss"
#घोषणा PLAT_DRIVER_NAME	"cdns-usb3"

#घोषणा CDNS_VENDOR_ID		0x17cd
#घोषणा CDNS_DEVICE_ID		0x0100

अटल काष्ठा pci_dev *cdns3_get_second_fun(काष्ठा pci_dev *pdev)
अणु
	काष्ठा pci_dev *func;

	/*
	 * Gets the second function.
	 * It's little tricky, but this platक्रमm has two function.
	 * The fist keeps resources क्रम Host/Device जबतक the second
	 * keeps resources क्रम DRD/OTG.
	 */
	func = pci_get_device(pdev->venकरोr, pdev->device, शून्य);
	अगर (unlikely(!func))
		वापस शून्य;

	अगर (func->devfn == pdev->devfn) अणु
		func = pci_get_device(pdev->venकरोr, pdev->device, func);
		अगर (unlikely(!func))
			वापस शून्य;
	पूर्ण

	वापस func;
पूर्ण

अटल पूर्णांक cdns3_pci_probe(काष्ठा pci_dev *pdev,
			   स्थिर काष्ठा pci_device_id *id)
अणु
	काष्ठा platक्रमm_device_info plat_info;
	काष्ठा cdns3_wrap *wrap;
	काष्ठा resource *res;
	काष्ठा pci_dev *func;
	पूर्णांक err;

	/*
	 * क्रम GADGET/HOST PCI (devfn) function number is 0,
	 * क्रम OTG PCI (devfn) function number is 1
	 */
	अगर (!id || (pdev->devfn != PCI_DEV_FN_HOST_DEVICE &&
		    pdev->devfn != PCI_DEV_FN_OTG))
		वापस -EINVAL;

	func = cdns3_get_second_fun(pdev);
	अगर (unlikely(!func))
		वापस -EINVAL;

	err = pcim_enable_device(pdev);
	अगर (err) अणु
		dev_err(&pdev->dev, "Enabling PCI device has failed %d\n", err);
		वापस err;
	पूर्ण

	pci_set_master(pdev);

	अगर (pci_is_enabled(func)) अणु
		wrap = pci_get_drvdata(func);
	पूर्ण अन्यथा अणु
		wrap = kzalloc(माप(*wrap), GFP_KERNEL);
		अगर (!wrap) अणु
			pci_disable_device(pdev);
			वापस -ENOMEM;
		पूर्ण
	पूर्ण

	res = wrap->dev_res;

	अगर (pdev->devfn == PCI_DEV_FN_HOST_DEVICE) अणु
		/* function 0: host(BAR_0) + device(BAR_1).*/
		dev_dbg(&pdev->dev, "Initialize Device resources\n");
		res[RES_DEV_ID].start = pci_resource_start(pdev, PCI_BAR_DEV);
		res[RES_DEV_ID].end =   pci_resource_end(pdev, PCI_BAR_DEV);
		res[RES_DEV_ID].name = "dev";
		res[RES_DEV_ID].flags = IORESOURCE_MEM;
		dev_dbg(&pdev->dev, "USBSS-DEV physical base addr: %pa\n",
			&res[RES_DEV_ID].start);

		res[RES_HOST_ID].start = pci_resource_start(pdev, PCI_BAR_HOST);
		res[RES_HOST_ID].end = pci_resource_end(pdev, PCI_BAR_HOST);
		res[RES_HOST_ID].name = "xhci";
		res[RES_HOST_ID].flags = IORESOURCE_MEM;
		dev_dbg(&pdev->dev, "USBSS-XHCI physical base addr: %pa\n",
			&res[RES_HOST_ID].start);

		/* Interrupt क्रम XHCI */
		wrap->dev_res[RES_IRQ_HOST_ID].start = pdev->irq;
		wrap->dev_res[RES_IRQ_HOST_ID].name = "host";
		wrap->dev_res[RES_IRQ_HOST_ID].flags = IORESOURCE_IRQ;

		/* Interrupt device. It's the same as क्रम HOST. */
		wrap->dev_res[RES_IRQ_PERIPHERAL_ID].start = pdev->irq;
		wrap->dev_res[RES_IRQ_PERIPHERAL_ID].name = "peripheral";
		wrap->dev_res[RES_IRQ_PERIPHERAL_ID].flags = IORESOURCE_IRQ;
	पूर्ण अन्यथा अणु
		res[RES_DRD_ID].start = pci_resource_start(pdev, PCI_BAR_OTG);
		res[RES_DRD_ID].end =   pci_resource_end(pdev, PCI_BAR_OTG);
		res[RES_DRD_ID].name = "otg";
		res[RES_DRD_ID].flags = IORESOURCE_MEM;
		dev_dbg(&pdev->dev, "USBSS-DRD physical base addr: %pa\n",
			&res[RES_DRD_ID].start);

		/* Interrupt क्रम OTG/DRD. */
		wrap->dev_res[RES_IRQ_OTG_ID].start = pdev->irq;
		wrap->dev_res[RES_IRQ_OTG_ID].name = "otg";
		wrap->dev_res[RES_IRQ_OTG_ID].flags = IORESOURCE_IRQ;
	पूर्ण

	अगर (pci_is_enabled(func)) अणु
		/* set up platक्रमm device info */
		स_रखो(&plat_info, 0, माप(plat_info));
		plat_info.parent = &pdev->dev;
		plat_info.fwnode = pdev->dev.fwnode;
		plat_info.name = PLAT_DRIVER_NAME;
		plat_info.id = pdev->devfn;
		wrap->devfn  = pdev->devfn;
		plat_info.res = wrap->dev_res;
		plat_info.num_res = ARRAY_SIZE(wrap->dev_res);
		plat_info.dma_mask = pdev->dma_mask;
		/* रेजिस्टर platक्रमm device */
		wrap->plat_dev = platक्रमm_device_रेजिस्टर_full(&plat_info);
		अगर (IS_ERR(wrap->plat_dev)) अणु
			pci_disable_device(pdev);
			err = PTR_ERR(wrap->plat_dev);
			kमुक्त(wrap);
			वापस err;
		पूर्ण
	पूर्ण

	pci_set_drvdata(pdev, wrap);
	वापस err;
पूर्ण

अटल व्योम cdns3_pci_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा cdns3_wrap *wrap;
	काष्ठा pci_dev *func;

	func = cdns3_get_second_fun(pdev);

	wrap = (काष्ठा cdns3_wrap *)pci_get_drvdata(pdev);
	अगर (wrap->devfn == pdev->devfn)
		platक्रमm_device_unरेजिस्टर(wrap->plat_dev);

	अगर (!pci_is_enabled(func))
		kमुक्त(wrap);
पूर्ण

अटल स्थिर काष्ठा pci_device_id cdns3_pci_ids[] = अणु
	अणु PCI_DEVICE(CDNS_VENDOR_ID, CDNS_DEVICE_ID), पूर्ण,
	अणु 0, पूर्ण
पूर्ण;

अटल काष्ठा pci_driver cdns3_pci_driver = अणु
	.name = PCI_DRIVER_NAME,
	.id_table = cdns3_pci_ids,
	.probe = cdns3_pci_probe,
	.हटाओ = cdns3_pci_हटाओ,
पूर्ण;

module_pci_driver(cdns3_pci_driver);
MODULE_DEVICE_TABLE(pci, cdns3_pci_ids);

MODULE_AUTHOR("Pawel Laszczak <pawell@cadence.com>");
MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("Cadence USBSS PCI wrapper");
