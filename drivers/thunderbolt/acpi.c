<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * ACPI support
 *
 * Copyright (C) 2020, Intel Corporation
 * Author: Mika Westerberg <mika.westerberg@linux.पूर्णांकel.com>
 */

#समावेश <linux/acpi.h>

#समावेश "tb.h"

अटल acpi_status tb_acpi_add_link(acpi_handle handle, u32 level, व्योम *data,
				    व्योम **वापस_value)
अणु
	काष्ठा fwnode_reference_args args;
	काष्ठा fwnode_handle *fwnode;
	काष्ठा tb_nhi *nhi = data;
	काष्ठा acpi_device *adev;
	काष्ठा pci_dev *pdev;
	काष्ठा device *dev;
	पूर्णांक ret;

	अगर (acpi_bus_get_device(handle, &adev))
		वापस AE_OK;

	fwnode = acpi_fwnode_handle(adev);
	ret = fwnode_property_get_reference_args(fwnode, "usb4-host-interface",
						 शून्य, 0, 0, &args);
	अगर (ret)
		वापस AE_OK;

	/* It needs to reference this NHI */
	अगर (nhi->pdev->dev.fwnode != args.fwnode)
		जाओ out_put;

	/*
	 * Try to find physical device walking upwards to the hierarcy.
	 * We need to करो this because the xHCI driver might not yet be
	 * bound so the USB3 SuperSpeed ports are not yet created.
	 */
	dev = acpi_get_first_physical_node(adev);
	जबतक (!dev) अणु
		adev = adev->parent;
		अगर (!adev)
			अवरोध;
		dev = acpi_get_first_physical_node(adev);
	पूर्ण

	अगर (!dev)
		जाओ out_put;

	/*
	 * Check that the device is PCIe. This is because USB3
	 * SuperSpeed ports have this property and they are not घातer
	 * managed with the xHCI and the SuperSpeed hub so we create the
	 * link from xHCI instead.
	 */
	जबतक (dev && !dev_is_pci(dev))
		dev = dev->parent;

	अगर (!dev)
		जाओ out_put;

	/*
	 * Check that this actually matches the type of device we
	 * expect. It should either be xHCI or PCIe root/करोwnstream
	 * port.
	 */
	pdev = to_pci_dev(dev);
	अगर (pdev->class == PCI_CLASS_SERIAL_USB_XHCI ||
	    (pci_is_pcie(pdev) &&
		(pci_pcie_type(pdev) == PCI_EXP_TYPE_ROOT_PORT ||
		 pci_pcie_type(pdev) == PCI_EXP_TYPE_DOWNSTREAM))) अणु
		स्थिर काष्ठा device_link *link;

		link = device_link_add(&pdev->dev, &nhi->pdev->dev,
				       DL_FLAG_AUTOREMOVE_SUPPLIER |
				       DL_FLAG_PM_RUNTIME);
		अगर (link) अणु
			dev_dbg(&nhi->pdev->dev, "created link from %s\n",
				dev_name(&pdev->dev));
		पूर्ण अन्यथा अणु
			dev_warn(&nhi->pdev->dev, "device link creation from %s failed\n",
				 dev_name(&pdev->dev));
		पूर्ण
	पूर्ण

out_put:
	fwnode_handle_put(args.fwnode);
	वापस AE_OK;
पूर्ण

/**
 * tb_acpi_add_links() - Add device links based on ACPI description
 * @nhi: Poपूर्णांकer to NHI
 *
 * Goes over ACPI namespace finding tunneled ports that reference to
 * @nhi ACPI node. For each reference a device link is added. The link
 * is स्वतःmatically हटाओd by the driver core.
 */
व्योम tb_acpi_add_links(काष्ठा tb_nhi *nhi)
अणु
	acpi_status status;

	अगर (!has_acpi_companion(&nhi->pdev->dev))
		वापस;

	/*
	 * Find all devices that have usb4-host-controller पूर्णांकerface
	 * property that references to this NHI.
	 */
	status = acpi_walk_namespace(ACPI_TYPE_DEVICE, ACPI_ROOT_OBJECT, 32,
				     tb_acpi_add_link, शून्य, nhi, शून्य);
	अगर (ACPI_FAILURE(status))
		dev_warn(&nhi->pdev->dev, "failed to enumerate tunneled ports\n");
पूर्ण

/**
 * tb_acpi_is_native() - Did the platक्रमm grant native TBT/USB4 control
 *
 * Returns %true अगर the platक्रमm granted OS native control over
 * TBT/USB4. In this हाल software based connection manager can be used,
 * otherwise there is firmware based connection manager running.
 */
bool tb_acpi_is_native(व्योम)
अणु
	वापस osc_sb_native_usb4_support_confirmed &&
	       osc_sb_native_usb4_control;
पूर्ण

/**
 * tb_acpi_may_tunnel_usb3() - Is USB3 tunneling allowed by the platक्रमm
 *
 * When software based connection manager is used, this function
 * वापसs %true अगर platक्रमm allows native USB3 tunneling.
 */
bool tb_acpi_may_tunnel_usb3(व्योम)
अणु
	अगर (tb_acpi_is_native())
		वापस osc_sb_native_usb4_control & OSC_USB_USB3_TUNNELING;
	वापस true;
पूर्ण

/**
 * tb_acpi_may_tunnel_dp() - Is DisplayPort tunneling allowed by the platक्रमm
 *
 * When software based connection manager is used, this function
 * वापसs %true अगर platक्रमm allows native DP tunneling.
 */
bool tb_acpi_may_tunnel_dp(व्योम)
अणु
	अगर (tb_acpi_is_native())
		वापस osc_sb_native_usb4_control & OSC_USB_DP_TUNNELING;
	वापस true;
पूर्ण

/**
 * tb_acpi_may_tunnel_pcie() - Is PCIe tunneling allowed by the platक्रमm
 *
 * When software based connection manager is used, this function
 * वापसs %true अगर platक्रमm allows native PCIe tunneling.
 */
bool tb_acpi_may_tunnel_pcie(व्योम)
अणु
	अगर (tb_acpi_is_native())
		वापस osc_sb_native_usb4_control & OSC_USB_PCIE_TUNNELING;
	वापस true;
पूर्ण

/**
 * tb_acpi_is_xकरोमुख्य_allowed() - Are XDoमुख्य connections allowed
 *
 * When software based connection manager is used, this function
 * वापसs %true अगर platक्रमm allows XDoमुख्य connections.
 */
bool tb_acpi_is_xकरोमुख्य_allowed(व्योम)
अणु
	अगर (tb_acpi_is_native())
		वापस osc_sb_native_usb4_control & OSC_USB_XDOMAIN;
	वापस true;
पूर्ण
