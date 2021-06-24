<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * HID driver क्रम Holtek keyboard
 * Copyright (c) 2012 Tom Harwood
*/

/*
 */

#समावेश <linux/device.h>
#समावेश <linux/hid.h>
#समावेश <linux/module.h>
#समावेश <linux/usb.h>

#समावेश "hid-ids.h"
#समावेश "usbhid/usbhid.h"

/* Holtek based keyboards (USB ID 04d9:a055) have the following issues:
 * - The report descriptor specअगरies an excessively large number of consumer
 *   usages (2^15), which is more than HID_MAX_USAGES. This prevents proper
 *   parsing of the report descriptor.
 * - The report descriptor reports on caps/scroll/num lock key presses, but
 *   करोesn't have an LED output usage block.
 *
 * The replacement descriptor below fixes the number of consumer usages,
 * and provides an LED output usage block. LED output events are redirected
 * to the boot पूर्णांकerface.
 */

अटल __u8 holtek_kbd_rdesc_fixed[] = अणु
	/* Original report descriptor, with reduced number of consumer usages */
	0x05, 0x01,         /*  Usage Page (Desktop),                         */
	0x09, 0x80,         /*  Usage (Sys Control),                          */
	0xA1, 0x01,         /*  Collection (Application),                     */
	0x85, 0x01,         /*      Report ID (1),                            */
	0x19, 0x81,         /*      Usage Minimum (Sys Power Down),           */
	0x29, 0x83,         /*      Usage Maximum (Sys Wake Up),              */
	0x15, 0x00,         /*      Logical Minimum (0),                      */
	0x25, 0x01,         /*      Logical Maximum (1),                      */
	0x95, 0x03,         /*      Report Count (3),                         */
	0x75, 0x01,         /*      Report Size (1),                          */
	0x81, 0x02,         /*      Input (Variable),                         */
	0x95, 0x01,         /*      Report Count (1),                         */
	0x75, 0x05,         /*      Report Size (5),                          */
	0x81, 0x01,         /*      Input (Constant),                         */
	0xC0,               /*  End Collection,                               */
	0x05, 0x0C,         /*  Usage Page (Consumer),                        */
	0x09, 0x01,         /*  Usage (Consumer Control),                     */
	0xA1, 0x01,         /*  Collection (Application),                     */
	0x85, 0x02,         /*      Report ID (2),                            */
	0x19, 0x00,         /*      Usage Minimum (00h),                      */
	0x2A, 0xFF, 0x2F,   /*      Usage Maximum (0x2FFF), previously 0x7FFF */
	0x15, 0x00,         /*      Logical Minimum (0),                      */
	0x26, 0xFF, 0x2F,   /*      Logical Maximum (0x2FFF),previously 0x7FFF*/
	0x95, 0x01,         /*      Report Count (1),                         */
	0x75, 0x10,         /*      Report Size (16),                         */
	0x81, 0x00,         /*      Input,                                    */
	0xC0,               /*  End Collection,                               */
	0x05, 0x01,         /*  Usage Page (Desktop),                         */
	0x09, 0x06,         /*  Usage (Keyboard),                             */
	0xA1, 0x01,         /*  Collection (Application),                     */
	0x85, 0x03,         /*      Report ID (3),                            */
	0x95, 0x38,         /*      Report Count (56),                        */
	0x75, 0x01,         /*      Report Size (1),                          */
	0x15, 0x00,         /*      Logical Minimum (0),                      */
	0x25, 0x01,         /*      Logical Maximum (1),                      */
	0x05, 0x07,         /*      Usage Page (Keyboard),                    */
	0x19, 0xE0,         /*      Usage Minimum (KB Leftcontrol),           */
	0x29, 0xE7,         /*      Usage Maximum (KB Right GUI),             */
	0x19, 0x00,         /*      Usage Minimum (None),                     */
	0x29, 0x2F,         /*      Usage Maximum (KB Lboxbracket And Lbrace),*/
	0x81, 0x02,         /*      Input (Variable),                         */
	0xC0,               /*  End Collection,                               */
	0x05, 0x01,         /*  Usage Page (Desktop),                         */
	0x09, 0x06,         /*  Usage (Keyboard),                             */
	0xA1, 0x01,         /*  Collection (Application),                     */
	0x85, 0x04,         /*      Report ID (4),                            */
	0x95, 0x38,         /*      Report Count (56),                        */
	0x75, 0x01,         /*      Report Size (1),                          */
	0x15, 0x00,         /*      Logical Minimum (0),                      */
	0x25, 0x01,         /*      Logical Maximum (1),                      */
	0x05, 0x07,         /*      Usage Page (Keyboard),                    */
	0x19, 0x30,         /*      Usage Minimum (KB Rboxbracket And Rbrace),*/
	0x29, 0x67,         /*      Usage Maximum (KP Equals),                */
	0x81, 0x02,         /*      Input (Variable),                         */
	0xC0,               /*  End Collection                                */

	/* LED usage क्रम the boot protocol पूर्णांकerface */
	0x05, 0x01,         /*  Usage Page (Desktop),                         */
	0x09, 0x06,         /*  Usage (Keyboard),                             */
	0xA1, 0x01,         /*  Collection (Application),                     */
	0x05, 0x08,         /*      Usage Page (LED),                         */
	0x19, 0x01,         /*      Usage Minimum (01h),                      */
	0x29, 0x03,         /*      Usage Maximum (03h),                      */
	0x15, 0x00,         /*      Logical Minimum (0),                      */
	0x25, 0x01,         /*      Logical Maximum (1),                      */
	0x75, 0x01,         /*      Report Size (1),                          */
	0x95, 0x03,         /*      Report Count (3),                         */
	0x91, 0x02,         /*      Output (Variable),                        */
	0x95, 0x05,         /*      Report Count (5),                         */
	0x91, 0x01,         /*      Output (Constant),                        */
	0xC0,               /*  End Collection                                */
पूर्ण;

अटल __u8 *holtek_kbd_report_fixup(काष्ठा hid_device *hdev, __u8 *rdesc,
		अचिन्हित पूर्णांक *rsize)
अणु
	काष्ठा usb_पूर्णांकerface *पूर्णांकf = to_usb_पूर्णांकerface(hdev->dev.parent);

	अगर (पूर्णांकf->cur_altsetting->desc.bInterfaceNumber == 1) अणु
		rdesc = holtek_kbd_rdesc_fixed;
		*rsize = माप(holtek_kbd_rdesc_fixed);
	पूर्ण
	वापस rdesc;
पूर्ण

अटल पूर्णांक holtek_kbd_input_event(काष्ठा input_dev *dev, अचिन्हित पूर्णांक type,
		अचिन्हित पूर्णांक code,
		पूर्णांक value)
अणु
	काष्ठा hid_device *hid = input_get_drvdata(dev);
	काष्ठा usb_device *usb_dev = hid_to_usb_dev(hid);

	/* Locate the boot पूर्णांकerface, to receive the LED change events */
	काष्ठा usb_पूर्णांकerface *boot_पूर्णांकerface = usb_अगरnum_to_अगर(usb_dev, 0);
	काष्ठा hid_device *boot_hid;
	काष्ठा hid_input *boot_hid_input;

	अगर (unlikely(boot_पूर्णांकerface == शून्य))
		वापस -ENODEV;

	boot_hid = usb_get_पूर्णांकfdata(boot_पूर्णांकerface);
	boot_hid_input = list_first_entry(&boot_hid->inमाला_दो,
		काष्ठा hid_input, list);

	वापस boot_hid_input->input->event(boot_hid_input->input, type, code,
			value);
पूर्ण

अटल पूर्णांक holtek_kbd_probe(काष्ठा hid_device *hdev,
		स्थिर काष्ठा hid_device_id *id)
अणु
	काष्ठा usb_पूर्णांकerface *पूर्णांकf = to_usb_पूर्णांकerface(hdev->dev.parent);
	पूर्णांक ret = hid_parse(hdev);

	अगर (!ret)
		ret = hid_hw_start(hdev, HID_CONNECT_DEFAULT);

	अगर (!ret && पूर्णांकf->cur_altsetting->desc.bInterfaceNumber == 1) अणु
		काष्ठा hid_input *hidinput;
		list_क्रम_each_entry(hidinput, &hdev->inमाला_दो, list) अणु
			hidinput->input->event = holtek_kbd_input_event;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा hid_device_id holtek_kbd_devices[] = अणु
	अणु HID_USB_DEVICE(USB_VENDOR_ID_HOLTEK_ALT,
			USB_DEVICE_ID_HOLTEK_ALT_KEYBOARD) पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(hid, holtek_kbd_devices);

अटल काष्ठा hid_driver holtek_kbd_driver = अणु
	.name = "holtek_kbd",
	.id_table = holtek_kbd_devices,
	.report_fixup = holtek_kbd_report_fixup,
	.probe = holtek_kbd_probe
पूर्ण;
module_hid_driver(holtek_kbd_driver);

MODULE_LICENSE("GPL");
