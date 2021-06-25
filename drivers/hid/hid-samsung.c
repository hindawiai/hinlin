<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  HID driver क्रम some samsung "special" devices
 *
 *  Copyright (c) 1999 Andreas Gal
 *  Copyright (c) 2000-2005 Vojtech Pavlik <vojtech@suse.cz>
 *  Copyright (c) 2005 Michael Haboustak <mike-@cinci.rr.com> क्रम Concept2, Inc
 *  Copyright (c) 2006-2007 Jiri Kosina
 *  Copyright (c) 2008 Jiri Slaby
 *  Copyright (c) 2010 Don Prince <dhprince.devel@yahoo.co.uk>
 *
 *  This driver supports several HID devices:
 *
 *  [0419:0001] Samsung IrDA remote controller (reports as Cypress USB Mouse).
 *	various hid report fixups क्रम dअगरferent variants.
 *
 *  [0419:0600] Creative Desktop Wireless 6000 keyboard/mouse combo
 *	several key mappings used from the consumer usage page
 *	deviate from the USB HUT 1.12 standard.
 */

/*
 */

#समावेश <linux/device.h>
#समावेश <linux/usb.h>
#समावेश <linux/hid.h>
#समावेश <linux/module.h>

#समावेश "hid-ids.h"

/*
 * There are several variants क्रम 0419:0001:
 *
 * 1. 184 byte report descriptor
 * Venकरोr specअगरic report #4 has a size of 48 bit,
 * and thereक्रमe is not accepted when inspecting the descriptors.
 * As a workaround we reपूर्णांकerpret the report as:
 *   Variable type, count 6, size 8 bit, log. maximum 255
 * The burden to reस्थिरruct the data is moved पूर्णांकo user space.
 *
 * 2. 203 byte report descriptor
 * Report #4 has an array field with logical range 0..18 instead of 1..15.
 *
 * 3. 135 byte report descriptor
 * Report #4 has an array field with logical range 0..17 instead of 1..14.
 *
 * 4. 171 byte report descriptor
 * Report #3 has an array field with logical range 0..1 instead of 1..3.
 */
अटल अंतरभूत व्योम samsung_irda_dev_trace(काष्ठा hid_device *hdev,
		अचिन्हित पूर्णांक rsize)
अणु
	hid_info(hdev, "fixing up Samsung IrDA %d byte report descriptor\n",
		 rsize);
पूर्ण

अटल __u8 *samsung_irda_report_fixup(काष्ठा hid_device *hdev, __u8 *rdesc,
		अचिन्हित पूर्णांक *rsize)
अणु
	अगर (*rsize == 184 && rdesc[175] == 0x25 && rdesc[176] == 0x40 &&
			rdesc[177] == 0x75 && rdesc[178] == 0x30 &&
			rdesc[179] == 0x95 && rdesc[180] == 0x01 &&
			rdesc[182] == 0x40) अणु
		samsung_irda_dev_trace(hdev, 184);
		rdesc[176] = 0xff;
		rdesc[178] = 0x08;
		rdesc[180] = 0x06;
		rdesc[182] = 0x42;
	पूर्ण अन्यथा
	अगर (*rsize == 203 && rdesc[192] == 0x15 && rdesc[193] == 0x0 &&
			rdesc[194] == 0x25 && rdesc[195] == 0x12) अणु
		samsung_irda_dev_trace(hdev, 203);
		rdesc[193] = 0x1;
		rdesc[195] = 0xf;
	पूर्ण अन्यथा
	अगर (*rsize == 135 && rdesc[124] == 0x15 && rdesc[125] == 0x0 &&
			rdesc[126] == 0x25 && rdesc[127] == 0x11) अणु
		samsung_irda_dev_trace(hdev, 135);
		rdesc[125] = 0x1;
		rdesc[127] = 0xe;
	पूर्ण अन्यथा
	अगर (*rsize == 171 && rdesc[160] == 0x15 && rdesc[161] == 0x0 &&
			rdesc[162] == 0x25 && rdesc[163] == 0x01) अणु
		samsung_irda_dev_trace(hdev, 171);
		rdesc[161] = 0x1;
		rdesc[163] = 0x3;
	पूर्ण
	वापस rdesc;
पूर्ण

#घोषणा samsung_kbd_mouse_map_key_clear(c) \
	hid_map_usage_clear(hi, usage, bit, max, EV_KEY, (c))

अटल पूर्णांक samsung_kbd_mouse_input_mapping(काष्ठा hid_device *hdev,
	काष्ठा hid_input *hi, काष्ठा hid_field *field, काष्ठा hid_usage *usage,
	अचिन्हित दीर्घ **bit, पूर्णांक *max)
अणु
	काष्ठा usb_पूर्णांकerface *पूर्णांकf = to_usb_पूर्णांकerface(hdev->dev.parent);
	अचिन्हित लघु अगरnum = पूर्णांकf->cur_altsetting->desc.bInterfaceNumber;

	अगर (1 != अगरnum || HID_UP_CONSUMER != (usage->hid & HID_USAGE_PAGE))
		वापस 0;

	dbg_hid("samsung wireless keyboard/mouse input mapping event [0x%x]\n",
		usage->hid & HID_USAGE);

	चयन (usage->hid & HID_USAGE) अणु
	/* report 2 */
	हाल 0x183: samsung_kbd_mouse_map_key_clear(KEY_MEDIA); अवरोध;
	हाल 0x195: samsung_kbd_mouse_map_key_clear(KEY_EMAIL);	अवरोध;
	हाल 0x196: samsung_kbd_mouse_map_key_clear(KEY_CALC); अवरोध;
	हाल 0x197: samsung_kbd_mouse_map_key_clear(KEY_COMPUTER); अवरोध;
	हाल 0x22b: samsung_kbd_mouse_map_key_clear(KEY_SEARCH); अवरोध;
	हाल 0x22c: samsung_kbd_mouse_map_key_clear(KEY_WWW); अवरोध;
	हाल 0x22d: samsung_kbd_mouse_map_key_clear(KEY_BACK); अवरोध;
	हाल 0x22e: samsung_kbd_mouse_map_key_clear(KEY_FORWARD); अवरोध;
	हाल 0x22f: samsung_kbd_mouse_map_key_clear(KEY_FAVORITES); अवरोध;
	हाल 0x230: samsung_kbd_mouse_map_key_clear(KEY_REFRESH); अवरोध;
	हाल 0x231: samsung_kbd_mouse_map_key_clear(KEY_STOP); अवरोध;
	शेष:
		वापस 0;
	पूर्ण

	वापस 1;
पूर्ण

अटल __u8 *samsung_report_fixup(काष्ठा hid_device *hdev, __u8 *rdesc,
	अचिन्हित पूर्णांक *rsize)
अणु
	अगर (USB_DEVICE_ID_SAMSUNG_IR_REMOTE == hdev->product)
		rdesc = samsung_irda_report_fixup(hdev, rdesc, rsize);
	वापस rdesc;
पूर्ण

अटल पूर्णांक samsung_input_mapping(काष्ठा hid_device *hdev, काष्ठा hid_input *hi,
	काष्ठा hid_field *field, काष्ठा hid_usage *usage,
	अचिन्हित दीर्घ **bit, पूर्णांक *max)
अणु
	पूर्णांक ret = 0;

	अगर (USB_DEVICE_ID_SAMSUNG_WIRELESS_KBD_MOUSE == hdev->product)
		ret = samsung_kbd_mouse_input_mapping(hdev,
			hi, field, usage, bit, max);

	वापस ret;
पूर्ण

अटल पूर्णांक samsung_probe(काष्ठा hid_device *hdev,
		स्थिर काष्ठा hid_device_id *id)
अणु
	पूर्णांक ret;
	अचिन्हित पूर्णांक cmask = HID_CONNECT_DEFAULT;

	ret = hid_parse(hdev);
	अगर (ret) अणु
		hid_err(hdev, "parse failed\n");
		जाओ err_मुक्त;
	पूर्ण

	अगर (USB_DEVICE_ID_SAMSUNG_IR_REMOTE == hdev->product) अणु
		अगर (hdev->rsize == 184) अणु
			/* disable hidinput, क्रमce hiddev */
			cmask = (cmask & ~HID_CONNECT_HIDINPUT) |
				HID_CONNECT_HIDDEV_FORCE;
		पूर्ण
	पूर्ण

	ret = hid_hw_start(hdev, cmask);
	अगर (ret) अणु
		hid_err(hdev, "hw start failed\n");
		जाओ err_मुक्त;
	पूर्ण

	वापस 0;
err_मुक्त:
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा hid_device_id samsung_devices[] = अणु
	अणु HID_USB_DEVICE(USB_VENDOR_ID_SAMSUNG, USB_DEVICE_ID_SAMSUNG_IR_REMOTE) पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_SAMSUNG, USB_DEVICE_ID_SAMSUNG_WIRELESS_KBD_MOUSE) पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(hid, samsung_devices);

अटल काष्ठा hid_driver samsung_driver = अणु
	.name = "samsung",
	.id_table = samsung_devices,
	.report_fixup = samsung_report_fixup,
	.input_mapping = samsung_input_mapping,
	.probe = samsung_probe,
पूर्ण;
module_hid_driver(samsung_driver);

MODULE_LICENSE("GPL");
