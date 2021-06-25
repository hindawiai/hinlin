<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * HID driver क्रम Google Fiber TV Box remote controls
 *
 * Copyright (c) 2014-2015 Google Inc.
 *
 * Author: Petri Gynther <pgynther@google.com>
 */
#समावेश <linux/device.h>
#समावेश <linux/hid.h>
#समावेश <linux/input.h>
#समावेश <linux/module.h>

#समावेश "hid-ids.h"

#घोषणा GFRM100  1  /* Google Fiber GFRM100 (Bluetooth classic) */
#घोषणा GFRM200  2  /* Google Fiber GFRM200 (Bluetooth LE) */

#घोषणा GFRM100_SEARCH_KEY_REPORT_ID   0xF7
#घोषणा GFRM100_SEARCH_KEY_DOWN        0x0
#घोषणा GFRM100_SEARCH_KEY_AUDIO_DATA  0x1
#घोषणा GFRM100_SEARCH_KEY_UP          0x2

अटल u8 search_key_dn[3] = अणु0x40, 0x21, 0x02पूर्ण;
अटल u8 search_key_up[3] = अणु0x40, 0x00, 0x00पूर्ण;

अटल पूर्णांक gfrm_input_mapping(काष्ठा hid_device *hdev, काष्ठा hid_input *hi,
		काष्ठा hid_field *field, काष्ठा hid_usage *usage,
		अचिन्हित दीर्घ **bit, पूर्णांक *max)
अणु
	अचिन्हित दीर्घ hdev_type = (अचिन्हित दीर्घ) hid_get_drvdata(hdev);

	अगर (hdev_type == GFRM100) अणु
		अगर (usage->hid == (HID_UP_CONSUMER | 0x4)) अणु
			/* Consumer.0004 -> KEY_INFO */
			hid_map_usage_clear(hi, usage, bit, max, EV_KEY, KEY_INFO);
			वापस 1;
		पूर्ण

		अगर (usage->hid == (HID_UP_CONSUMER | 0x41)) अणु
			/* Consumer.0041 -> KEY_OK */
			hid_map_usage_clear(hi, usage, bit, max, EV_KEY, KEY_OK);
			वापस 1;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक gfrm_raw_event(काष्ठा hid_device *hdev, काष्ठा hid_report *report,
		u8 *data, पूर्णांक size)
अणु
	अचिन्हित दीर्घ hdev_type = (अचिन्हित दीर्घ) hid_get_drvdata(hdev);
	पूर्णांक ret = 0;

	अगर (hdev_type != GFRM100)
		वापस 0;

	अगर (size < 2 || data[0] != GFRM100_SEARCH_KEY_REPORT_ID)
		वापस 0;

	/*
	 * Convert GFRM100 Search key reports पूर्णांकo Consumer.0221 (Key.Search)
	 * reports. Ignore audio data.
	 */
	चयन (data[1]) अणु
	हाल GFRM100_SEARCH_KEY_DOWN:
		ret = hid_report_raw_event(hdev, HID_INPUT_REPORT, search_key_dn,
					   माप(search_key_dn), 1);
		अवरोध;

	हाल GFRM100_SEARCH_KEY_AUDIO_DATA:
		अवरोध;

	हाल GFRM100_SEARCH_KEY_UP:
		ret = hid_report_raw_event(hdev, HID_INPUT_REPORT, search_key_up,
					   माप(search_key_up), 1);
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

	वापस (ret < 0) ? ret : -1;
पूर्ण

अटल पूर्णांक gfrm_input_configured(काष्ठा hid_device *hid, काष्ठा hid_input *hidinput)
अणु
	/*
	 * Enable software स्वतःrepeat with:
	 * - repeat delay: 400 msec
	 * - repeat period: 100 msec
	 */
	input_enable_softrepeat(hidinput->input, 400, 100);
	वापस 0;
पूर्ण

अटल पूर्णांक gfrm_probe(काष्ठा hid_device *hdev, स्थिर काष्ठा hid_device_id *id)
अणु
	पूर्णांक ret;

	hid_set_drvdata(hdev, (व्योम *) id->driver_data);

	ret = hid_parse(hdev);
	अगर (ret)
		जाओ करोne;

	अगर (id->driver_data == GFRM100) अणु
		/*
		 * GFRM100 HID Report Descriptor करोes not describe the Search
		 * key reports. Thus, we need to add it manually here, so that
		 * those reports reach gfrm_raw_event() from hid_input_report().
		 */
		अगर (!hid_रेजिस्टर_report(hdev, HID_INPUT_REPORT,
					 GFRM100_SEARCH_KEY_REPORT_ID, 0)) अणु
			ret = -ENOMEM;
			जाओ करोne;
		पूर्ण
	पूर्ण

	ret = hid_hw_start(hdev, HID_CONNECT_DEFAULT);
करोne:
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा hid_device_id gfrm_devices[] = अणु
	अणु HID_BLUETOOTH_DEVICE(0x58, 0x2000),
		.driver_data = GFRM100 पूर्ण,
	अणु HID_BLUETOOTH_DEVICE(0x471, 0x2210),
		.driver_data = GFRM200 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(hid, gfrm_devices);

अटल काष्ठा hid_driver gfrm_driver = अणु
	.name = "gfrm",
	.id_table = gfrm_devices,
	.probe = gfrm_probe,
	.input_mapping = gfrm_input_mapping,
	.raw_event = gfrm_raw_event,
	.input_configured = gfrm_input_configured,
पूर्ण;

module_hid_driver(gfrm_driver);

MODULE_AUTHOR("Petri Gynther <pgynther@google.com>");
MODULE_DESCRIPTION("Google Fiber TV Box remote control driver");
MODULE_LICENSE("GPL");
