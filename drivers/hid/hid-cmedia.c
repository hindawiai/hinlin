<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * HID driver क्रम CMedia CM6533 audio jack controls
 *
 * Copyright (C) 2015 Ben Chen <ben_chen@bizlinktech.com>
 */

#समावेश <linux/device.h>
#समावेश <linux/hid.h>
#समावेश <linux/module.h>
#समावेश "hid-ids.h"

MODULE_AUTHOR("Ben Chen");
MODULE_DESCRIPTION("CM6533 HID jack controls");
MODULE_LICENSE("GPL");

#घोषणा CM6533_JD_TYPE_COUNT      1
#घोषणा CM6533_JD_RAWEV_LEN	 16
#घोषणा CM6533_JD_SFX_OFFSET	  8

/*
*
*CM6533 audio jack HID raw events:
*
*Plug in:
*01000600 002083xx 080008c0 10000000
*about 3 seconds later...
*01000a00 002083xx 08000380 10000000
*01000600 002083xx 08000380 10000000
*
*Plug out:
*01000400 002083xx 080008c0 x0000000
*/

अटल स्थिर u8 ji_sfx[] = अणु 0x08, 0x00, 0x08, 0xc0 पूर्ण;
अटल स्थिर u8 ji_in[]  = अणु 0x01, 0x00, 0x06, 0x00 पूर्ण;
अटल स्थिर u8 ji_out[] = अणु 0x01, 0x00, 0x04, 0x00 पूर्ण;

अटल पूर्णांक jack_चयन_types[CM6533_JD_TYPE_COUNT] = अणु
	SW_HEADPHONE_INSERT,
पूर्ण;

काष्ठा cmhid अणु
	काष्ठा input_dev *input_dev;
	काष्ठा hid_device *hid;
	अचिन्हित लघु चयन_map[CM6533_JD_TYPE_COUNT];
पूर्ण;

अटल व्योम hp_ev(काष्ठा hid_device *hid, काष्ठा cmhid *cm, पूर्णांक value)
अणु
	input_report_चयन(cm->input_dev, SW_HEADPHONE_INSERT, value);
	input_sync(cm->input_dev);
पूर्ण

अटल पूर्णांक cmhid_raw_event(काष्ठा hid_device *hid, काष्ठा hid_report *report,
	 u8 *data, पूर्णांक len)
अणु
	काष्ठा cmhid *cm = hid_get_drvdata(hid);

	अगर (len != CM6533_JD_RAWEV_LEN)
		जाओ out;
	अगर (स_भेद(data+CM6533_JD_SFX_OFFSET, ji_sfx, माप(ji_sfx)))
		जाओ out;

	अगर (!स_भेद(data, ji_out, माप(ji_out))) अणु
		hp_ev(hid, cm, 0);
		जाओ out;
	पूर्ण
	अगर (!स_भेद(data, ji_in, माप(ji_in))) अणु
		hp_ev(hid, cm, 1);
		जाओ out;
	पूर्ण

out:
	वापस 0;
पूर्ण

अटल पूर्णांक cmhid_input_configured(काष्ठा hid_device *hid,
		काष्ठा hid_input *hidinput)
अणु
	काष्ठा input_dev *input_dev = hidinput->input;
	काष्ठा cmhid *cm = hid_get_drvdata(hid);
	पूर्णांक i;

	cm->input_dev = input_dev;
	स_नकल(cm->चयन_map, jack_चयन_types, माप(cm->चयन_map));
	input_dev->evbit[0] = BIT(EV_SW);
	क्रम (i = 0; i < CM6533_JD_TYPE_COUNT; i++)
		input_set_capability(cm->input_dev,
				EV_SW, jack_चयन_types[i]);
	वापस 0;
पूर्ण

अटल पूर्णांक cmhid_input_mapping(काष्ठा hid_device *hid,
		काष्ठा hid_input *hi, काष्ठा hid_field *field,
		काष्ठा hid_usage *usage, अचिन्हित दीर्घ **bit, पूर्णांक *max)
अणु
	वापस -1;
पूर्ण

अटल पूर्णांक cmhid_probe(काष्ठा hid_device *hid, स्थिर काष्ठा hid_device_id *id)
अणु
	पूर्णांक ret;
	काष्ठा cmhid *cm;

	cm = kzalloc(माप(काष्ठा cmhid), GFP_KERNEL);
	अगर (!cm) अणु
		ret = -ENOMEM;
		जाओ allocfail;
	पूर्ण

	cm->hid = hid;

	hid->quirks |= HID_QUIRK_HIDINPUT_FORCE;
	hid_set_drvdata(hid, cm);

	ret = hid_parse(hid);
	अगर (ret) अणु
		hid_err(hid, "parse failed\n");
		जाओ fail;
	पूर्ण

	ret = hid_hw_start(hid, HID_CONNECT_DEFAULT | HID_CONNECT_HIDDEV_FORCE);
	अगर (ret) अणु
		hid_err(hid, "hw start failed\n");
		जाओ fail;
	पूर्ण

	वापस 0;
fail:
	kमुक्त(cm);
allocfail:
	वापस ret;
पूर्ण

अटल व्योम cmhid_हटाओ(काष्ठा hid_device *hid)
अणु
	काष्ठा cmhid *cm = hid_get_drvdata(hid);

	hid_hw_stop(hid);
	kमुक्त(cm);
पूर्ण

अटल स्थिर काष्ठा hid_device_id cmhid_devices[] = अणु
	अणु HID_USB_DEVICE(USB_VENDOR_ID_CMEDIA, USB_DEVICE_ID_CM6533) पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(hid, cmhid_devices);

अटल काष्ठा hid_driver cmhid_driver = अणु
	.name = "cm6533_jd",
	.id_table = cmhid_devices,
	.raw_event = cmhid_raw_event,
	.input_configured = cmhid_input_configured,
	.probe = cmhid_probe,
	.हटाओ = cmhid_हटाओ,
	.input_mapping = cmhid_input_mapping,
पूर्ण;
module_hid_driver(cmhid_driver);

