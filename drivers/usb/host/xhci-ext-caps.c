<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * XHCI extended capability handling
 *
 * Copyright (c) 2017 Hans de Goede <hdegoede@redhat.com>
 */

#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/property.h>
#समावेश <linux/pci.h>
#समावेश "xhci.h"

#घोषणा USB_SW_DRV_NAME		"intel_xhci_usb_sw"
#घोषणा USB_SW_RESOURCE_SIZE	0x400

#घोषणा PCI_DEVICE_ID_INTEL_CHERRYVIEW_XHCI	0x22b5

अटल स्थिर काष्ठा property_entry role_चयन_props[] = अणु
	PROPERTY_ENTRY_BOOL("sw_switch_disable"),
	अणुपूर्ण,
पूर्ण;

अटल व्योम xhci_पूर्णांकel_unरेजिस्टर_pdev(व्योम *arg)
अणु
	platक्रमm_device_unरेजिस्टर(arg);
पूर्ण

अटल पूर्णांक xhci_create_पूर्णांकel_xhci_sw_pdev(काष्ठा xhci_hcd *xhci, u32 cap_offset)
अणु
	काष्ठा usb_hcd *hcd = xhci_to_hcd(xhci);
	काष्ठा device *dev = hcd->self.controller;
	काष्ठा platक्रमm_device *pdev;
	काष्ठा pci_dev *pci = to_pci_dev(dev);
	काष्ठा resource	res = अणु 0, पूर्ण;
	पूर्णांक ret;

	pdev = platक्रमm_device_alloc(USB_SW_DRV_NAME, PLATFORM_DEVID_NONE);
	अगर (!pdev) अणु
		xhci_err(xhci, "couldn't allocate %s platform device\n",
			 USB_SW_DRV_NAME);
		वापस -ENOMEM;
	पूर्ण

	res.start = hcd->rsrc_start + cap_offset;
	res.end	  = res.start + USB_SW_RESOURCE_SIZE - 1;
	res.name  = USB_SW_DRV_NAME;
	res.flags = IORESOURCE_MEM;

	ret = platक्रमm_device_add_resources(pdev, &res, 1);
	अगर (ret) अणु
		dev_err(dev, "couldn't add resources to intel_xhci_usb_sw pdev\n");
		platक्रमm_device_put(pdev);
		वापस ret;
	पूर्ण

	अगर (pci->device == PCI_DEVICE_ID_INTEL_CHERRYVIEW_XHCI) अणु
		ret = device_create_managed_software_node(&pdev->dev, role_चयन_props,
							  शून्य);
		अगर (ret) अणु
			dev_err(dev, "failed to register device properties\n");
			platक्रमm_device_put(pdev);
			वापस ret;
		पूर्ण
	पूर्ण

	pdev->dev.parent = dev;

	ret = platक्रमm_device_add(pdev);
	अगर (ret) अणु
		dev_err(dev, "couldn't register intel_xhci_usb_sw pdev\n");
		platक्रमm_device_put(pdev);
		वापस ret;
	पूर्ण

	ret = devm_add_action_or_reset(dev, xhci_पूर्णांकel_unरेजिस्टर_pdev, pdev);
	अगर (ret) अणु
		dev_err(dev, "couldn't add unregister action for intel_xhci_usb_sw pdev\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक xhci_ext_cap_init(काष्ठा xhci_hcd *xhci)
अणु
	व्योम __iomem *base = &xhci->cap_regs->hc_capbase;
	u32 offset, val;
	पूर्णांक ret;

	offset = xhci_find_next_ext_cap(base, 0, 0);

	जबतक (offset) अणु
		val = पढ़ोl(base + offset);

		चयन (XHCI_EXT_CAPS_ID(val)) अणु
		हाल XHCI_EXT_CAPS_VENDOR_INTEL:
			अगर (xhci->quirks & XHCI_INTEL_USB_ROLE_SW) अणु
				ret = xhci_create_पूर्णांकel_xhci_sw_pdev(xhci,
								     offset);
				अगर (ret)
					वापस ret;
			पूर्ण
			अवरोध;
		पूर्ण
		offset = xhci_find_next_ext_cap(base, offset, 0);
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(xhci_ext_cap_init);
