<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  HID driver क्रम some petalynx "special" devices
 *
 *  Copyright (c) 1999 Andreas Gal
 *  Copyright (c) 2000-2005 Vojtech Pavlik <vojtech@suse.cz>
 *  Copyright (c) 2005 Michael Haboustak <mike-@cinci.rr.com> क्रम Concept2, Inc
 *  Copyright (c) 2006-2007 Jiri Kosina
 *  Copyright (c) 2008 Jiri Slaby
 */

/*
 */

#समावेश <linux/device.h>
#समावेश <linux/hid.h>
#समावेश <linux/module.h>

#समावेश "hid-ids.h"

/* Petalynx Maxter Remote has maximum क्रम consumer page set too low */
अटल __u8 *pl_report_fixup(काष्ठा hid_device *hdev, __u8 *rdesc,
		अचिन्हित पूर्णांक *rsize)
अणु
	अगर (*rsize >= 62 && rdesc[39] == 0x2a && rdesc[40] == 0xf5 &&
			rdesc[41] == 0x00 && rdesc[59] == 0x26 &&
			rdesc[60] == 0xf9 && rdesc[61] == 0x00) अणु
		hid_info(hdev, "fixing up Petalynx Maxter Remote report descriptor\n");
		rdesc[60] = 0xfa;
		rdesc[40] = 0xfa;
	पूर्ण
	वापस rdesc;
पूर्ण

#घोषणा pl_map_key_clear(c)	hid_map_usage_clear(hi, usage, bit, max, \
					EV_KEY, (c))
अटल पूर्णांक pl_input_mapping(काष्ठा hid_device *hdev, काष्ठा hid_input *hi,
		काष्ठा hid_field *field, काष्ठा hid_usage *usage,
		अचिन्हित दीर्घ **bit, पूर्णांक *max)
अणु
	अगर ((usage->hid & HID_USAGE_PAGE) == HID_UP_LOGIVENDOR) अणु
		चयन (usage->hid & HID_USAGE) अणु
		हाल 0x05a: pl_map_key_clear(KEY_TEXT);		अवरोध;
		हाल 0x05b: pl_map_key_clear(KEY_RED);		अवरोध;
		हाल 0x05c: pl_map_key_clear(KEY_GREEN);	अवरोध;
		हाल 0x05d: pl_map_key_clear(KEY_YELLOW);	अवरोध;
		हाल 0x05e: pl_map_key_clear(KEY_BLUE);		अवरोध;
		शेष:
			वापस 0;
		पूर्ण
		वापस 1;
	पूर्ण

	अगर ((usage->hid & HID_USAGE_PAGE) == HID_UP_CONSUMER) अणु
		चयन (usage->hid & HID_USAGE) अणु
		हाल 0x0f6: pl_map_key_clear(KEY_NEXT);		अवरोध;
		हाल 0x0fa: pl_map_key_clear(KEY_BACK);		अवरोध;
		शेष:
			वापस 0;
		पूर्ण
		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक pl_probe(काष्ठा hid_device *hdev, स्थिर काष्ठा hid_device_id *id)
अणु
	पूर्णांक ret;

	hdev->quirks |= HID_QUIRK_NOGET;

	ret = hid_parse(hdev);
	अगर (ret) अणु
		hid_err(hdev, "parse failed\n");
		जाओ err_मुक्त;
	पूर्ण

	ret = hid_hw_start(hdev, HID_CONNECT_DEFAULT);
	अगर (ret) अणु
		hid_err(hdev, "hw start failed\n");
		जाओ err_मुक्त;
	पूर्ण

	वापस 0;
err_मुक्त:
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा hid_device_id pl_devices[] = अणु
	अणु HID_USB_DEVICE(USB_VENDOR_ID_PETALYNX, USB_DEVICE_ID_PETALYNX_MAXTER_REMOTE) पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(hid, pl_devices);

अटल काष्ठा hid_driver pl_driver = अणु
	.name = "petalynx",
	.id_table = pl_devices,
	.report_fixup = pl_report_fixup,
	.input_mapping = pl_input_mapping,
	.probe = pl_probe,
पूर्ण;
module_hid_driver(pl_driver);

MODULE_LICENSE("GPL");
