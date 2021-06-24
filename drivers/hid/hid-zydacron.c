<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
*  HID driver क्रम zydacron remote control
*
*  Copyright (c) 2010 Don Prince <dhprince.devel@yahoo.co.uk>
*/

/*
*/

#समावेश <linux/device.h>
#समावेश <linux/hid.h>
#समावेश <linux/module.h>

#समावेश "hid-ids.h"

काष्ठा zc_device अणु
	काष्ठा input_dev	*input_ep81;
	अचिन्हित लघु		last_key[4];
पूर्ण;


/*
* Zydacron remote control has an invalid HID report descriptor,
* that needs fixing beक्रमe we can parse it.
*/
अटल __u8 *zc_report_fixup(काष्ठा hid_device *hdev, __u8 *rdesc,
	अचिन्हित पूर्णांक *rsize)
अणु
	अगर (*rsize >= 253 &&
		rdesc[0x96] == 0xbc && rdesc[0x97] == 0xff &&
		rdesc[0xca] == 0xbc && rdesc[0xcb] == 0xff &&
		rdesc[0xe1] == 0xbc && rdesc[0xe2] == 0xff) अणु
			hid_info(hdev,
				"fixing up zydacron remote control report descriptor\n");
			rdesc[0x96] = rdesc[0xca] = rdesc[0xe1] = 0x0c;
			rdesc[0x97] = rdesc[0xcb] = rdesc[0xe2] = 0x00;
		पूर्ण
	वापस rdesc;
पूर्ण

#घोषणा zc_map_key_clear(c) \
	hid_map_usage_clear(hi, usage, bit, max, EV_KEY, (c))

अटल पूर्णांक zc_input_mapping(काष्ठा hid_device *hdev, काष्ठा hid_input *hi,
	काष्ठा hid_field *field, काष्ठा hid_usage *usage,
	अचिन्हित दीर्घ **bit, पूर्णांक *max)
अणु
	पूर्णांक i;
	काष्ठा zc_device *zc = hid_get_drvdata(hdev);
	zc->input_ep81 = hi->input;

	अगर ((usage->hid & HID_USAGE_PAGE) != HID_UP_CONSUMER)
		वापस 0;

	dbg_hid("zynacron input mapping event [0x%x]\n",
		usage->hid & HID_USAGE);

	चयन (usage->hid & HID_USAGE) अणु
	/* report 2 */
	हाल 0x10:
		zc_map_key_clear(KEY_MODE);
		अवरोध;
	हाल 0x30:
		zc_map_key_clear(KEY_SCREEN);
		अवरोध;
	हाल 0x70:
		zc_map_key_clear(KEY_INFO);
		अवरोध;
	/* report 3 */
	हाल 0x04:
		zc_map_key_clear(KEY_RADIO);
		अवरोध;
	/* report 4 */
	हाल 0x0d:
		zc_map_key_clear(KEY_PVR);
		अवरोध;
	हाल 0x25:
		zc_map_key_clear(KEY_TV);
		अवरोध;
	हाल 0x47:
		zc_map_key_clear(KEY_AUDIO);
		अवरोध;
	हाल 0x49:
		zc_map_key_clear(KEY_AUX);
		अवरोध;
	हाल 0x4a:
		zc_map_key_clear(KEY_VIDEO);
		अवरोध;
	हाल 0x48:
		zc_map_key_clear(KEY_DVD);
		अवरोध;
	हाल 0x24:
		zc_map_key_clear(KEY_MENU);
		अवरोध;
	हाल 0x32:
		zc_map_key_clear(KEY_TEXT);
		अवरोध;
	शेष:
		वापस 0;
	पूर्ण

	क्रम (i = 0; i < 4; i++)
		zc->last_key[i] = 0;

	वापस 1;
पूर्ण

अटल पूर्णांक zc_raw_event(काष्ठा hid_device *hdev, काष्ठा hid_report *report,
	 u8 *data, पूर्णांक size)
अणु
	काष्ठा zc_device *zc = hid_get_drvdata(hdev);
	पूर्णांक ret = 0;
	अचिन्हित key;
	अचिन्हित लघु index;

	अगर (report->id == data[0]) अणु

		/* अवरोध keys */
		क्रम (index = 0; index < 4; index++) अणु
			key = zc->last_key[index];
			अगर (key) अणु
				input_event(zc->input_ep81, EV_KEY, key, 0);
				zc->last_key[index] = 0;
			पूर्ण
		पूर्ण

		key = 0;
		चयन (report->id) अणु
		हाल 0x02:
		हाल 0x03:
			चयन (data[1]) अणु
			हाल 0x10:
				key = KEY_MODE;
				index = 0;
				अवरोध;
			हाल 0x30:
				key = KEY_SCREEN;
				index = 1;
				अवरोध;
			हाल 0x70:
				key = KEY_INFO;
				index = 2;
				अवरोध;
			हाल 0x04:
				key = KEY_RADIO;
				index = 3;
				अवरोध;
			पूर्ण

			अगर (key) अणु
				input_event(zc->input_ep81, EV_KEY, key, 1);
				zc->last_key[index] = key;
			पूर्ण

			ret = 1;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक zc_probe(काष्ठा hid_device *hdev, स्थिर काष्ठा hid_device_id *id)
अणु
	पूर्णांक ret;
	काष्ठा zc_device *zc;

	zc = devm_kzalloc(&hdev->dev, माप(*zc), GFP_KERNEL);
	अगर (zc == शून्य) अणु
		hid_err(hdev, "can't alloc descriptor\n");
		वापस -ENOMEM;
	पूर्ण

	hid_set_drvdata(hdev, zc);

	ret = hid_parse(hdev);
	अगर (ret) अणु
		hid_err(hdev, "parse failed\n");
		वापस ret;
	पूर्ण

	ret = hid_hw_start(hdev, HID_CONNECT_DEFAULT);
	अगर (ret) अणु
		hid_err(hdev, "hw start failed\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा hid_device_id zc_devices[] = अणु
	अणु HID_USB_DEVICE(USB_VENDOR_ID_ZYDACRON, USB_DEVICE_ID_ZYDACRON_REMOTE_CONTROL) पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(hid, zc_devices);

अटल काष्ठा hid_driver zc_driver = अणु
	.name = "zydacron",
	.id_table = zc_devices,
	.report_fixup = zc_report_fixup,
	.input_mapping = zc_input_mapping,
	.raw_event = zc_raw_event,
	.probe = zc_probe,
पूर्ण;
module_hid_driver(zc_driver);

MODULE_LICENSE("GPL");
