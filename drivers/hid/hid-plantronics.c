<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Plantronics USB HID Driver
 *
 *  Copyright (c) 2014 JD Cole <jd.cole@plantronics.com>
 *  Copyright (c) 2015-2018 Terry Junge <terry.junge@plantronics.com>
 */

/*
 */

#समावेश "hid-ids.h"

#समावेश <linux/hid.h>
#समावेश <linux/module.h>
#समावेश <linux/jअगरfies.h>

#घोषणा PLT_HID_1_0_PAGE	0xffa00000
#घोषणा PLT_HID_2_0_PAGE	0xffa20000

#घोषणा PLT_BASIC_TELEPHONY	0x0003
#घोषणा PLT_BASIC_EXCEPTION	0x0005

#घोषणा PLT_VOL_UP		0x00b1
#घोषणा PLT_VOL_DOWN		0x00b2

#घोषणा PLT1_VOL_UP		(PLT_HID_1_0_PAGE | PLT_VOL_UP)
#घोषणा PLT1_VOL_DOWN		(PLT_HID_1_0_PAGE | PLT_VOL_DOWN)
#घोषणा PLT2_VOL_UP		(PLT_HID_2_0_PAGE | PLT_VOL_UP)
#घोषणा PLT2_VOL_DOWN		(PLT_HID_2_0_PAGE | PLT_VOL_DOWN)

#घोषणा PLT_DA60		0xda60
#घोषणा PLT_BT300_MIN		0x0413
#घोषणा PLT_BT300_MAX		0x0418


#घोषणा PLT_ALLOW_CONSUMER (field->application == HID_CP_CONSUMERCONTROL && \
			    (usage->hid & HID_USAGE_PAGE) == HID_UP_CONSUMER)

#घोषणा PLT_QUIRK_DOUBLE_VOLUME_KEYS BIT(0)

#घोषणा PLT_DOUBLE_KEY_TIMEOUT 5 /* ms */

काष्ठा plt_drv_data अणु
	अचिन्हित दीर्घ device_type;
	अचिन्हित दीर्घ last_volume_key_ts;
	u32 quirks;
पूर्ण;

अटल पूर्णांक plantronics_input_mapping(काष्ठा hid_device *hdev,
				     काष्ठा hid_input *hi,
				     काष्ठा hid_field *field,
				     काष्ठा hid_usage *usage,
				     अचिन्हित दीर्घ **bit, पूर्णांक *max)
अणु
	अचिन्हित लघु mapped_key;
	काष्ठा plt_drv_data *drv_data = hid_get_drvdata(hdev);
	अचिन्हित दीर्घ plt_type = drv_data->device_type;

	/* special हाल क्रम PTT products */
	अगर (field->application == HID_GD_JOYSTICK)
		जाओ शेषed;

	/* handle volume up/करोwn mapping */
	/* non-standard types or multi-HID पूर्णांकerfaces - plt_type is PID */
	अगर (!(plt_type & HID_USAGE_PAGE)) अणु
		चयन (plt_type) अणु
		हाल PLT_DA60:
			अगर (PLT_ALLOW_CONSUMER)
				जाओ शेषed;
			जाओ ignored;
		शेष:
			अगर (PLT_ALLOW_CONSUMER)
				जाओ शेषed;
		पूर्ण
	पूर्ण
	/* handle standard types - plt_type is 0xffa0uuuu or 0xffa2uuuu */
	/* 'basic telephony compliant' - allow शेष consumer page map */
	अन्यथा अगर ((plt_type & HID_USAGE) >= PLT_BASIC_TELEPHONY &&
		 (plt_type & HID_USAGE) != PLT_BASIC_EXCEPTION) अणु
		अगर (PLT_ALLOW_CONSUMER)
			जाओ शेषed;
	पूर्ण
	/* not 'basic telephony' - apply legacy mapping */
	/* only map अगर the field is in the device's primary venकरोr page */
	अन्यथा अगर (!((field->application ^ plt_type) & HID_USAGE_PAGE)) अणु
		चयन (usage->hid) अणु
		हाल PLT1_VOL_UP:
		हाल PLT2_VOL_UP:
			mapped_key = KEY_VOLUMEUP;
			जाओ mapped;
		हाल PLT1_VOL_DOWN:
		हाल PLT2_VOL_DOWN:
			mapped_key = KEY_VOLUMEDOWN;
			जाओ mapped;
		पूर्ण
	पूर्ण

/*
 * Future mapping of call control or other usages,
 * अगर and when keys are defined would go here
 * otherwise, ignore everything अन्यथा that was not mapped
 */

ignored:
	वापस -1;

शेषed:
	hid_dbg(hdev, "usage: %08x (appl: %08x) - defaulted\n",
		usage->hid, field->application);
	वापस 0;

mapped:
	hid_map_usage_clear(hi, usage, bit, max, EV_KEY, mapped_key);
	hid_dbg(hdev, "usage: %08x (appl: %08x) - mapped to key %d\n",
		usage->hid, field->application, mapped_key);
	वापस 1;
पूर्ण

अटल पूर्णांक plantronics_event(काष्ठा hid_device *hdev, काष्ठा hid_field *field,
			     काष्ठा hid_usage *usage, __s32 value)
अणु
	काष्ठा plt_drv_data *drv_data = hid_get_drvdata(hdev);

	अगर (drv_data->quirks & PLT_QUIRK_DOUBLE_VOLUME_KEYS) अणु
		अचिन्हित दीर्घ prev_ts, cur_ts;

		/* Usages are filtered in plantronics_usages. */

		अगर (!value) /* Handle key presses only. */
			वापस 0;

		prev_ts = drv_data->last_volume_key_ts;
		cur_ts = jअगरfies;
		अगर (jअगरfies_to_msecs(cur_ts - prev_ts) <= PLT_DOUBLE_KEY_TIMEOUT)
			वापस 1; /* Ignore the repeated key. */

		drv_data->last_volume_key_ts = cur_ts;
	पूर्ण

	वापस 0;
पूर्ण

अटल अचिन्हित दीर्घ plantronics_device_type(काष्ठा hid_device *hdev)
अणु
	अचिन्हित i, col_page;
	अचिन्हित दीर्घ plt_type = hdev->product;

	/* multi-HID पूर्णांकerfaces? - plt_type is PID */
	अगर (plt_type >= PLT_BT300_MIN && plt_type <= PLT_BT300_MAX)
		जाओ निकास;

	/* determine primary venकरोr page */
	क्रम (i = 0; i < hdev->maxcollection; i++) अणु
		col_page = hdev->collection[i].usage & HID_USAGE_PAGE;
		अगर (col_page == PLT_HID_2_0_PAGE) अणु
			plt_type = hdev->collection[i].usage;
			अवरोध;
		पूर्ण
		अगर (col_page == PLT_HID_1_0_PAGE)
			plt_type = hdev->collection[i].usage;
	पूर्ण

निकास:
	hid_dbg(hdev, "plt_type decoded as: %08lx\n", plt_type);
	वापस plt_type;
पूर्ण

अटल पूर्णांक plantronics_probe(काष्ठा hid_device *hdev,
			     स्थिर काष्ठा hid_device_id *id)
अणु
	काष्ठा plt_drv_data *drv_data;
	पूर्णांक ret;

	drv_data = devm_kzalloc(&hdev->dev, माप(*drv_data), GFP_KERNEL);
	अगर (!drv_data)
		वापस -ENOMEM;

	ret = hid_parse(hdev);
	अगर (ret) अणु
		hid_err(hdev, "parse failed\n");
		जाओ err;
	पूर्ण

	drv_data->device_type = plantronics_device_type(hdev);
	drv_data->quirks = id->driver_data;
	drv_data->last_volume_key_ts = jअगरfies - msecs_to_jअगरfies(PLT_DOUBLE_KEY_TIMEOUT);

	hid_set_drvdata(hdev, drv_data);

	ret = hid_hw_start(hdev, HID_CONNECT_DEFAULT |
		HID_CONNECT_HIDINPUT_FORCE | HID_CONNECT_HIDDEV_FORCE);
	अगर (ret)
		hid_err(hdev, "hw start failed\n");

err:
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा hid_device_id plantronics_devices[] = अणु
	अणु HID_USB_DEVICE(USB_VENDOR_ID_PLANTRONICS,
					 USB_DEVICE_ID_PLANTRONICS_BLACKWIRE_3220_SERIES),
		.driver_data = PLT_QUIRK_DOUBLE_VOLUME_KEYS पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_PLANTRONICS, HID_ANY_ID) पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(hid, plantronics_devices);

अटल स्थिर काष्ठा hid_usage_id plantronics_usages[] = अणु
	अणु HID_CP_VOLUMEUP, EV_KEY, HID_ANY_ID पूर्ण,
	अणु HID_CP_VOLUMEDOWN, EV_KEY, HID_ANY_ID पूर्ण,
	अणु HID_TERMINATOR, HID_TERMINATOR, HID_TERMINATOR पूर्ण
पूर्ण;

अटल काष्ठा hid_driver plantronics_driver = अणु
	.name = "plantronics",
	.id_table = plantronics_devices,
	.usage_table = plantronics_usages,
	.input_mapping = plantronics_input_mapping,
	.event = plantronics_event,
	.probe = plantronics_probe,
पूर्ण;
module_hid_driver(plantronics_driver);

MODULE_AUTHOR("JD Cole <jd.cole@plantronics.com>");
MODULE_AUTHOR("Terry Junge <terry.junge@plantronics.com>");
MODULE_DESCRIPTION("Plantronics USB HID Driver");
MODULE_LICENSE("GPL");
