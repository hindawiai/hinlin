<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * of.c		The helpers क्रम hcd device tree support
 *
 * Copyright (C) 2016 Freescale Semiconductor, Inc.
 *	Author: Peter Chen <peter.chen@मुक्तscale.com>
 * Copyright (C) 2017 Johan Hovold <johan@kernel.org>
 */

#समावेश <linux/of.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/usb/of.h>

/**
 * usb_of_get_device_node() - get a USB device node
 * @hub: hub to which device is connected
 * @port1: one-based index of port
 *
 * Look up the node of a USB device given its parent hub device and one-based
 * port number.
 *
 * Return: A poपूर्णांकer to the node with incremented refcount अगर found, or
 * %शून्य otherwise.
 */
काष्ठा device_node *usb_of_get_device_node(काष्ठा usb_device *hub, पूर्णांक port1)
अणु
	काष्ठा device_node *node;
	u32 reg;

	क्रम_each_child_of_node(hub->dev.of_node, node) अणु
		अगर (of_property_पढ़ो_u32(node, "reg", &reg))
			जारी;

		अगर (reg == port1)
			वापस node;
	पूर्ण

	वापस शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(usb_of_get_device_node);

/**
 * usb_of_has_combined_node() - determine whether a device has a combined node
 * @udev: USB device
 *
 * Determine whether a USB device has a so called combined node which is
 * shared with its sole पूर्णांकerface. This is the हाल अगर and only अगर the device
 * has a node and its descriptors report the following:
 *
 *	1) bDeviceClass is 0 or 9, and
 *	2) bNumConfigurations is 1, and
 *	3) bNumInterfaces is 1.
 *
 * Return: True अगरf the device has a device node and its descriptors match the
 * criteria क्रम a combined node.
 */
bool usb_of_has_combined_node(काष्ठा usb_device *udev)
अणु
	काष्ठा usb_device_descriptor *ddesc = &udev->descriptor;
	काष्ठा usb_config_descriptor *cdesc;

	अगर (!udev->dev.of_node)
		वापस false;

	चयन (ddesc->bDeviceClass) अणु
	हाल USB_CLASS_PER_INTERFACE:
	हाल USB_CLASS_HUB:
		अगर (ddesc->bNumConfigurations == 1) अणु
			cdesc = &udev->config->desc;
			अगर (cdesc->bNumInterfaces == 1)
				वापस true;
		पूर्ण
	पूर्ण

	वापस false;
पूर्ण
EXPORT_SYMBOL_GPL(usb_of_has_combined_node);

/**
 * usb_of_get_पूर्णांकerface_node() - get a USB पूर्णांकerface node
 * @udev: USB device of पूर्णांकerface
 * @config: configuration value
 * @अगरnum: पूर्णांकerface number
 *
 * Look up the node of a USB पूर्णांकerface given its USB device, configuration
 * value and पूर्णांकerface number.
 *
 * Return: A poपूर्णांकer to the node with incremented refcount अगर found, or
 * %शून्य otherwise.
 */
काष्ठा device_node *
usb_of_get_पूर्णांकerface_node(काष्ठा usb_device *udev, u8 config, u8 अगरnum)
अणु
	काष्ठा device_node *node;
	u32 reg[2];

	क्रम_each_child_of_node(udev->dev.of_node, node) अणु
		अगर (of_property_पढ़ो_u32_array(node, "reg", reg, 2))
			जारी;

		अगर (reg[0] == अगरnum && reg[1] == config)
			वापस node;
	पूर्ण

	वापस शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(usb_of_get_पूर्णांकerface_node);
