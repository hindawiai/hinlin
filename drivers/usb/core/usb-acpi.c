<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * USB-ACPI glue code
 *
 * Copyright 2012 Red Hat <mjg@redhat.com>
 */
#समावेश <linux/module.h>
#समावेश <linux/usb.h>
#समावेश <linux/device.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kernel.h>
#समावेश <linux/acpi.h>
#समावेश <linux/pci.h>
#समावेश <linux/usb/hcd.h>

#समावेश "hub.h"

/**
 * usb_acpi_घातer_manageable - check whether usb port has
 * acpi घातer resource.
 * @hdev: USB device beदीर्घing to the usb hub
 * @index: port index based zero
 *
 * Return true अगर the port has acpi घातer resource and false अगर no.
 */
bool usb_acpi_घातer_manageable(काष्ठा usb_device *hdev, पूर्णांक index)
अणु
	acpi_handle port_handle;
	पूर्णांक port1 = index + 1;

	port_handle = usb_get_hub_port_acpi_handle(hdev,
		port1);
	अगर (port_handle)
		वापस acpi_bus_घातer_manageable(port_handle);
	अन्यथा
		वापस false;
पूर्ण
EXPORT_SYMBOL_GPL(usb_acpi_घातer_manageable);

/**
 * usb_acpi_set_घातer_state - control usb port's घातer via acpi घातer
 * resource
 * @hdev: USB device beदीर्घing to the usb hub
 * @index: port index based zero
 * @enable: घातer state expected to be set
 *
 * Notice to use usb_acpi_घातer_manageable() to check whether the usb port
 * has acpi घातer resource beक्रमe invoking this function.
 *
 * Returns 0 on success, अन्यथा negative त्रुटि_सं.
 */
पूर्णांक usb_acpi_set_घातer_state(काष्ठा usb_device *hdev, पूर्णांक index, bool enable)
अणु
	काष्ठा usb_hub *hub = usb_hub_to_काष्ठा_hub(hdev);
	काष्ठा usb_port *port_dev;
	acpi_handle port_handle;
	अचिन्हित अक्षर state;
	पूर्णांक port1 = index + 1;
	पूर्णांक error = -EINVAL;

	अगर (!hub)
		वापस -ENODEV;
	port_dev = hub->ports[port1 - 1];

	port_handle = (acpi_handle) usb_get_hub_port_acpi_handle(hdev, port1);
	अगर (!port_handle)
		वापस error;

	अगर (enable)
		state = ACPI_STATE_D0;
	अन्यथा
		state = ACPI_STATE_D3_COLD;

	error = acpi_bus_set_घातer(port_handle, state);
	अगर (!error)
		dev_dbg(&port_dev->dev, "acpi: power was set to %d\n", enable);
	अन्यथा
		dev_dbg(&port_dev->dev, "acpi: power failed to be set\n");

	वापस error;
पूर्ण
EXPORT_SYMBOL_GPL(usb_acpi_set_घातer_state);

अटल क्रमागत usb_port_connect_type usb_acpi_get_connect_type(acpi_handle handle,
		काष्ठा acpi_pld_info *pld)
अणु
	क्रमागत usb_port_connect_type connect_type = USB_PORT_CONNECT_TYPE_UNKNOWN;
	काष्ठा acpi_buffer buffer = अणु ACPI_ALLOCATE_BUFFER, शून्य पूर्ण;
	जोड़ acpi_object *upc = शून्य;
	acpi_status status;

	/*
	 * According to 9.14 in ACPI Spec 6.2. _PLD indicates whether usb port
	 * is user visible and _UPC indicates whether it is connectable. If
	 * the port was visible and connectable, it could be मुक्तly connected
	 * and disconnected with USB devices. If no visible and connectable,
	 * a usb device is directly hard-wired to the port. If no visible and
	 * no connectable, the port would be not used.
	 */
	status = acpi_evaluate_object(handle, "_UPC", शून्य, &buffer);
	अगर (ACPI_FAILURE(status))
		जाओ out;

	upc = buffer.poपूर्णांकer;
	अगर (!upc || (upc->type != ACPI_TYPE_PACKAGE) || upc->package.count != 4)
		जाओ out;

	अगर (upc->package.elements[0].पूर्णांकeger.value)
		अगर (pld->user_visible)
			connect_type = USB_PORT_CONNECT_TYPE_HOT_PLUG;
		अन्यथा
			connect_type = USB_PORT_CONNECT_TYPE_HARD_WIRED;
	अन्यथा अगर (!pld->user_visible)
		connect_type = USB_PORT_NOT_USED;
out:
	kमुक्त(upc);
	वापस connect_type;
पूर्ण


/*
 * Private to usb-acpi, all the core needs to know is that
 * port_dev->location is non-zero when it has been set by the firmware.
 */
#घोषणा USB_ACPI_LOCATION_VALID (1 << 31)

अटल काष्ठा acpi_device *usb_acpi_find_port(काष्ठा acpi_device *parent,
					      पूर्णांक raw)
अणु
	काष्ठा acpi_device *adev;

	अगर (!parent)
		वापस शून्य;

	list_क्रम_each_entry(adev, &parent->children, node) अणु
		अगर (acpi_device_adr(adev) == raw)
			वापस adev;
	पूर्ण

	वापस acpi_find_child_device(parent, raw, false);
पूर्ण

अटल काष्ठा acpi_device *
usb_acpi_get_companion_क्रम_port(काष्ठा usb_port *port_dev)
अणु
	काष्ठा usb_device *udev;
	काष्ठा acpi_device *adev;
	acpi_handle *parent_handle;
	पूर्णांक port1;

	/* Get the काष्ठा usb_device poपूर्णांक of port's hub */
	udev = to_usb_device(port_dev->dev.parent->parent);

	/*
	 * The root hub ports' parent is the root hub. The non-root-hub
	 * ports' parent is the parent hub port which the hub is
	 * connected to.
	 */
	अगर (!udev->parent) अणु
		adev = ACPI_COMPANION(&udev->dev);
		port1 = usb_hcd_find_raw_port_number(bus_to_hcd(udev->bus),
						     port_dev->portnum);
	पूर्ण अन्यथा अणु
		parent_handle = usb_get_hub_port_acpi_handle(udev->parent,
							     udev->portnum);
		अगर (!parent_handle)
			वापस शून्य;

		acpi_bus_get_device(parent_handle, &adev);
		port1 = port_dev->portnum;
	पूर्ण

	वापस usb_acpi_find_port(adev, port1);
पूर्ण

अटल काष्ठा acpi_device *
usb_acpi_find_companion_क्रम_port(काष्ठा usb_port *port_dev)
अणु
	काष्ठा acpi_device *adev;
	काष्ठा acpi_pld_info *pld;
	acpi_handle *handle;
	acpi_status status;

	adev = usb_acpi_get_companion_क्रम_port(port_dev);
	अगर (!adev)
		वापस शून्य;

	handle = adev->handle;
	status = acpi_get_physical_device_location(handle, &pld);
	अगर (ACPI_SUCCESS(status) && pld) अणु
		port_dev->location = USB_ACPI_LOCATION_VALID
			| pld->group_token << 8 | pld->group_position;
		port_dev->connect_type = usb_acpi_get_connect_type(handle, pld);
		ACPI_FREE(pld);
	पूर्ण

	वापस adev;
पूर्ण

अटल काष्ठा acpi_device *
usb_acpi_find_companion_क्रम_device(काष्ठा usb_device *udev)
अणु
	काष्ठा acpi_device *adev;
	काष्ठा usb_port *port_dev;
	काष्ठा usb_hub *hub;

	अगर (!udev->parent) अणु
		/* root hub is only child (_ADR=0) under its parent, the HC */
		adev = ACPI_COMPANION(udev->dev.parent);
		वापस acpi_find_child_device(adev, 0, false);
	पूर्ण

	hub = usb_hub_to_काष्ठा_hub(udev->parent);
	अगर (!hub)
		वापस शून्य;

	/*
	 * This is an embedded USB device connected to a port and such
	 * devices share port's ACPI companion.
	 */
	port_dev = hub->ports[udev->portnum - 1];
	वापस usb_acpi_get_companion_क्रम_port(port_dev);
पूर्ण

अटल काष्ठा acpi_device *usb_acpi_find_companion(काष्ठा device *dev)
अणु
	/*
	 * The USB hierarchy like following:
	 *
	 * Device (EHC1)
	 *	Device (HUBN)
	 *		Device (PR01)
	 *			Device (PR11)
	 *			Device (PR12)
	 *				Device (FN12)
	 *				Device (FN13)
	 *			Device (PR13)
	 *			...
	 * where HUBN is root hub, and PRNN are USB ports and devices
	 * connected to them, and FNNN are inभागidualk functions क्रम
	 * connected composite USB devices. PRNN and FNNN may contain
	 * _CRS and other methods describing sideband resources क्रम
	 * the connected device.
	 *
	 * On the kernel side both root hub and embedded USB devices are
	 * represented as instances of usb_device काष्ठाure, and ports
	 * are represented as usb_port काष्ठाures, so the whole process
	 * is split पूर्णांकo 2 parts: finding companions क्रम devices and
	 * finding companions क्रम ports.
	 *
	 * Note that we करो not handle inभागidual functions of composite
	 * devices yet, क्रम that we would need to assign companions to
	 * devices corresponding to USB पूर्णांकerfaces.
	 */
	अगर (is_usb_device(dev))
		वापस usb_acpi_find_companion_क्रम_device(to_usb_device(dev));
	अन्यथा अगर (is_usb_port(dev))
		वापस usb_acpi_find_companion_क्रम_port(to_usb_port(dev));

	वापस शून्य;
पूर्ण

अटल bool usb_acpi_bus_match(काष्ठा device *dev)
अणु
	वापस is_usb_device(dev) || is_usb_port(dev);
पूर्ण

अटल काष्ठा acpi_bus_type usb_acpi_bus = अणु
	.name = "USB",
	.match = usb_acpi_bus_match,
	.find_companion = usb_acpi_find_companion,
पूर्ण;

पूर्णांक usb_acpi_रेजिस्टर(व्योम)
अणु
	वापस रेजिस्टर_acpi_bus_type(&usb_acpi_bus);
पूर्ण

व्योम usb_acpi_unरेजिस्टर(व्योम)
अणु
	unरेजिस्टर_acpi_bus_type(&usb_acpi_bus);
पूर्ण
