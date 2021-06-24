<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * dwc3-haps.c - Synopsys HAPS PCI Specअगरic glue layer
 *
 * Copyright (C) 2018 Synopsys, Inc.
 *
 * Authors: Thinh Nguyen <thinhn@synopsys.com>,
 *          John Youn <johnyoun@synopsys.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/pci.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/property.h>

/**
 * काष्ठा dwc3_haps - Driver निजी काष्ठाure
 * @dwc3: child dwc3 platक्रमm_device
 * @pci: our link to PCI bus
 */
काष्ठा dwc3_haps अणु
	काष्ठा platक्रमm_device *dwc3;
	काष्ठा pci_dev *pci;
पूर्ण;

अटल स्थिर काष्ठा property_entry initial_properties[] = अणु
	PROPERTY_ENTRY_BOOL("snps,usb3_lpm_capable"),
	PROPERTY_ENTRY_BOOL("snps,has-lpm-erratum"),
	PROPERTY_ENTRY_BOOL("snps,dis_enblslpm_quirk"),
	PROPERTY_ENTRY_BOOL("linux,sysdev_is_parent"),
	अणु पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा software_node dwc3_haps_swnode = अणु
	.properties = initial_properties,
पूर्ण;

अटल पूर्णांक dwc3_haps_probe(काष्ठा pci_dev *pci,
			   स्थिर काष्ठा pci_device_id *id)
अणु
	काष्ठा dwc3_haps	*dwc;
	काष्ठा device		*dev = &pci->dev;
	काष्ठा resource		res[2];
	पूर्णांक			ret;

	ret = pcim_enable_device(pci);
	अगर (ret) अणु
		dev_err(dev, "failed to enable pci device\n");
		वापस -ENODEV;
	पूर्ण

	pci_set_master(pci);

	dwc = devm_kzalloc(dev, माप(*dwc), GFP_KERNEL);
	अगर (!dwc)
		वापस -ENOMEM;

	dwc->dwc3 = platक्रमm_device_alloc("dwc3", PLATFORM_DEVID_AUTO);
	अगर (!dwc->dwc3)
		वापस -ENOMEM;

	स_रखो(res, 0x00, माप(काष्ठा resource) * ARRAY_SIZE(res));

	res[0].start	= pci_resource_start(pci, 0);
	res[0].end	= pci_resource_end(pci, 0);
	res[0].name	= "dwc_usb3";
	res[0].flags	= IORESOURCE_MEM;

	res[1].start	= pci->irq;
	res[1].name	= "dwc_usb3";
	res[1].flags	= IORESOURCE_IRQ;

	ret = platक्रमm_device_add_resources(dwc->dwc3, res, ARRAY_SIZE(res));
	अगर (ret) अणु
		dev_err(dev, "couldn't add resources to dwc3 device\n");
		जाओ err;
	पूर्ण

	dwc->pci = pci;
	dwc->dwc3->dev.parent = dev;

	ret = device_add_software_node(&dwc->dwc3->dev, &dwc3_haps_swnode);
	अगर (ret)
		जाओ err;

	ret = platक्रमm_device_add(dwc->dwc3);
	अगर (ret) अणु
		dev_err(dev, "failed to register dwc3 device\n");
		जाओ err;
	पूर्ण

	pci_set_drvdata(pci, dwc);

	वापस 0;
err:
	device_हटाओ_software_node(&dwc->dwc3->dev);
	platक्रमm_device_put(dwc->dwc3);
	वापस ret;
पूर्ण

अटल व्योम dwc3_haps_हटाओ(काष्ठा pci_dev *pci)
अणु
	काष्ठा dwc3_haps *dwc = pci_get_drvdata(pci);

	device_हटाओ_software_node(&dwc->dwc3->dev);
	platक्रमm_device_unरेजिस्टर(dwc->dwc3);
पूर्ण

अटल स्थिर काष्ठा pci_device_id dwc3_haps_id_table[] = अणु
	अणु
		PCI_DEVICE(PCI_VENDOR_ID_SYNOPSYS,
			   PCI_DEVICE_ID_SYNOPSYS_HAPSUSB3),
		/*
		 * i.MX6QP and i.MX7D platक्रमm use a PCIe controller with the
		 * same VID and PID as this USB controller. The प्रणाली may
		 * incorrectly match this driver to that PCIe controller. To
		 * workaround this, specअगरically use class type USB to prevent
		 * incorrect driver matching.
		 */
		.class = (PCI_CLASS_SERIAL_USB << 8),
		.class_mask = 0xffff00,
	पूर्ण,
	अणु
		PCI_DEVICE(PCI_VENDOR_ID_SYNOPSYS,
			   PCI_DEVICE_ID_SYNOPSYS_HAPSUSB3_AXI),
	पूर्ण,
	अणु
		PCI_DEVICE(PCI_VENDOR_ID_SYNOPSYS,
			   PCI_DEVICE_ID_SYNOPSYS_HAPSUSB31),
	पूर्ण,
	अणु  पूर्ण	/* Terminating Entry */
पूर्ण;
MODULE_DEVICE_TABLE(pci, dwc3_haps_id_table);

अटल काष्ठा pci_driver dwc3_haps_driver = अणु
	.name		= "dwc3-haps",
	.id_table	= dwc3_haps_id_table,
	.probe		= dwc3_haps_probe,
	.हटाओ		= dwc3_haps_हटाओ,
पूर्ण;

MODULE_AUTHOR("Thinh Nguyen <thinhn@synopsys.com>");
MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("Synopsys HAPS PCI Glue Layer");

module_pci_driver(dwc3_haps_driver);
