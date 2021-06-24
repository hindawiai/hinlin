<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Jabra USB HID Driver
 *
 *  Copyright (c) 2017 Niels Skou Olsen <nolsen@jabra.com>
 */

/*
 */

#समावेश <linux/hid.h>
#समावेश <linux/module.h>

#समावेश "hid-ids.h"

#घोषणा HID_UP_VENDOR_DEFINED_MIN	0xff000000
#घोषणा HID_UP_VENDOR_DEFINED_MAX	0xffff0000

अटल पूर्णांक jabra_input_mapping(काष्ठा hid_device *hdev,
			       काष्ठा hid_input *hi,
			       काष्ठा hid_field *field,
			       काष्ठा hid_usage *usage,
			       अचिन्हित दीर्घ **bit, पूर्णांक *max)
अणु
	पूर्णांक is_venकरोr_defined =
		((usage->hid & HID_USAGE_PAGE) >= HID_UP_VENDOR_DEFINED_MIN &&
		 (usage->hid & HID_USAGE_PAGE) <= HID_UP_VENDOR_DEFINED_MAX);

	dbg_hid("hid=0x%08x appl=0x%08x coll_idx=0x%02x usage_idx=0x%02x: %s\n",
		usage->hid,
		field->application,
		usage->collection_index,
		usage->usage_index,
		is_venकरोr_defined ? "ignored" : "defaulted");

	/* Ignore venकरोr defined usages, शेष map standard usages */
	वापस is_venकरोr_defined ? -1 : 0;
पूर्ण

अटल स्थिर काष्ठा hid_device_id jabra_devices[] = अणु
	अणु HID_USB_DEVICE(USB_VENDOR_ID_JABRA, HID_ANY_ID) पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(hid, jabra_devices);

अटल काष्ठा hid_driver jabra_driver = अणु
	.name = "jabra",
	.id_table = jabra_devices,
	.input_mapping = jabra_input_mapping,
पूर्ण;
module_hid_driver(jabra_driver);

MODULE_AUTHOR("Niels Skou Olsen <nolsen@jabra.com>");
MODULE_DESCRIPTION("Jabra USB HID Driver");
MODULE_LICENSE("GPL");
