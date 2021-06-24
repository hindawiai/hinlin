<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  USB HID driver क्रम Glorious PC Gaming Race
 *  Glorious Model O, O- and D mice.
 *
 *  Copyright (c) 2020 Samuel दavoj <sammko@sammserver.com>
 */

/*
 */

#समावेश <linux/hid.h>
#समावेश <linux/module.h>

#समावेश "hid-ids.h"

MODULE_AUTHOR("Samuel दavoj <sammko@sammserver.com>");
MODULE_DESCRIPTION("HID driver for Glorious PC Gaming Race mice");

/*
 * Glorious Model O and O- specअगरy the स्थिर flag in the consumer input
 * report descriptor, which leads to inमाला_दो being ignored. Fix this
 * by patching the descriptor.
 */
अटल __u8 *glorious_report_fixup(काष्ठा hid_device *hdev, __u8 *rdesc,
		अचिन्हित पूर्णांक *rsize)
अणु
	अगर (*rsize == 213 &&
		rdesc[84] == 129 && rdesc[112] == 129 && rdesc[140] == 129 &&
		rdesc[85] == 3   && rdesc[113] == 3   && rdesc[141] == 3) अणु
		hid_info(hdev, "patching Glorious Model O consumer control report descriptor\n");
		rdesc[85] = rdesc[113] = rdesc[141] = \
			HID_MAIN_ITEM_VARIABLE | HID_MAIN_ITEM_RELATIVE;
	पूर्ण
	वापस rdesc;
पूर्ण

अटल व्योम glorious_update_name(काष्ठा hid_device *hdev)
अणु
	स्थिर अक्षर *model = "Device";

	चयन (hdev->product) अणु
	हाल USB_DEVICE_ID_GLORIOUS_MODEL_O:
		model = "Model O"; अवरोध;
	हाल USB_DEVICE_ID_GLORIOUS_MODEL_D:
		model = "Model D"; अवरोध;
	पूर्ण

	snम_लिखो(hdev->name, माप(hdev->name), "%s %s", "Glorious", model);
पूर्ण

अटल पूर्णांक glorious_probe(काष्ठा hid_device *hdev,
		स्थिर काष्ठा hid_device_id *id)
अणु
	पूर्णांक ret;

	hdev->quirks |= HID_QUIRK_INPUT_PER_APP;

	ret = hid_parse(hdev);
	अगर (ret)
		वापस ret;

	glorious_update_name(hdev);

	वापस hid_hw_start(hdev, HID_CONNECT_DEFAULT);
पूर्ण

अटल स्थिर काष्ठा hid_device_id glorious_devices[] = अणु
	अणु HID_USB_DEVICE(USB_VENDOR_ID_GLORIOUS,
		USB_DEVICE_ID_GLORIOUS_MODEL_O) पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_GLORIOUS,
		USB_DEVICE_ID_GLORIOUS_MODEL_D) पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(hid, glorious_devices);

अटल काष्ठा hid_driver glorious_driver = अणु
	.name = "glorious",
	.id_table = glorious_devices,
	.probe = glorious_probe,
	.report_fixup = glorious_report_fixup
पूर्ण;

module_hid_driver(glorious_driver);

MODULE_LICENSE("GPL");
