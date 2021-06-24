<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * host.c - DesignWare USB3 DRD Controller Host Glue
 *
 * Copyright (C) 2011 Texas Instruments Incorporated - https://www.ti.com
 *
 * Authors: Felipe Balbi <balbi@ti.com>,
 */

#समावेश <linux/acpi.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश "core.h"

अटल पूर्णांक dwc3_host_get_irq(काष्ठा dwc3 *dwc)
अणु
	काष्ठा platक्रमm_device	*dwc3_pdev = to_platक्रमm_device(dwc->dev);
	पूर्णांक irq;

	irq = platक्रमm_get_irq_byname_optional(dwc3_pdev, "host");
	अगर (irq > 0)
		जाओ out;

	अगर (irq == -EPROBE_DEFER)
		जाओ out;

	irq = platक्रमm_get_irq_byname_optional(dwc3_pdev, "dwc_usb3");
	अगर (irq > 0)
		जाओ out;

	अगर (irq == -EPROBE_DEFER)
		जाओ out;

	irq = platक्रमm_get_irq(dwc3_pdev, 0);
	अगर (irq > 0)
		जाओ out;

	अगर (!irq)
		irq = -EINVAL;

out:
	वापस irq;
पूर्ण

पूर्णांक dwc3_host_init(काष्ठा dwc3 *dwc)
अणु
	काष्ठा property_entry	props[4];
	काष्ठा platक्रमm_device	*xhci;
	पूर्णांक			ret, irq;
	काष्ठा resource		*res;
	काष्ठा platक्रमm_device	*dwc3_pdev = to_platक्रमm_device(dwc->dev);
	पूर्णांक			prop_idx = 0;

	irq = dwc3_host_get_irq(dwc);
	अगर (irq < 0)
		वापस irq;

	res = platक्रमm_get_resource_byname(dwc3_pdev, IORESOURCE_IRQ, "host");
	अगर (!res)
		res = platक्रमm_get_resource_byname(dwc3_pdev, IORESOURCE_IRQ,
				"dwc_usb3");
	अगर (!res)
		res = platक्रमm_get_resource(dwc3_pdev, IORESOURCE_IRQ, 0);
	अगर (!res)
		वापस -ENOMEM;

	dwc->xhci_resources[1].start = irq;
	dwc->xhci_resources[1].end = irq;
	dwc->xhci_resources[1].flags = res->flags;
	dwc->xhci_resources[1].name = res->name;

	xhci = platक्रमm_device_alloc("xhci-hcd", PLATFORM_DEVID_AUTO);
	अगर (!xhci) अणु
		dev_err(dwc->dev, "couldn't allocate xHCI device\n");
		वापस -ENOMEM;
	पूर्ण

	xhci->dev.parent	= dwc->dev;
	ACPI_COMPANION_SET(&xhci->dev, ACPI_COMPANION(dwc->dev));

	dwc->xhci = xhci;

	ret = platक्रमm_device_add_resources(xhci, dwc->xhci_resources,
						DWC3_XHCI_RESOURCES_NUM);
	अगर (ret) अणु
		dev_err(dwc->dev, "couldn't add resources to xHCI device\n");
		जाओ err;
	पूर्ण

	स_रखो(props, 0, माप(काष्ठा property_entry) * ARRAY_SIZE(props));

	अगर (dwc->usb3_lpm_capable)
		props[prop_idx++] = PROPERTY_ENTRY_BOOL("usb3-lpm-capable");

	अगर (dwc->usb2_lpm_disable)
		props[prop_idx++] = PROPERTY_ENTRY_BOOL("usb2-lpm-disable");

	/**
	 * WORKAROUND: dwc3 revisions <=3.00a have a limitation
	 * where Port Disable command करोesn't work.
	 *
	 * The suggested workaround is that we aव्योम Port Disable
	 * completely.
	 *
	 * This following flag tells XHCI to करो just that.
	 */
	अगर (DWC3_VER_IS_WITHIN(DWC3, ANY, 300A))
		props[prop_idx++] = PROPERTY_ENTRY_BOOL("quirk-broken-port-ped");

	अगर (prop_idx) अणु
		ret = device_create_managed_software_node(&xhci->dev, props, शून्य);
		अगर (ret) अणु
			dev_err(dwc->dev, "failed to add properties to xHCI\n");
			जाओ err;
		पूर्ण
	पूर्ण

	ret = platक्रमm_device_add(xhci);
	अगर (ret) अणु
		dev_err(dwc->dev, "failed to register xHCI device\n");
		जाओ err;
	पूर्ण

	वापस 0;
err:
	platक्रमm_device_put(xhci);
	वापस ret;
पूर्ण

व्योम dwc3_host_निकास(काष्ठा dwc3 *dwc)
अणु
	platक्रमm_device_unरेजिस्टर(dwc->xhci);
पूर्ण
