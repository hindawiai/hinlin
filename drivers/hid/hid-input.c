<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Copyright (c) 2000-2001 Vojtech Pavlik
 *  Copyright (c) 2006-2010 Jiri Kosina
 *
 *  HID to Linux Input mapping
 */

/*
 *
 * Should you need to contact me, the author, you can करो so either by
 * e-mail - mail your message to <vojtech@ucw.cz>, or by paper mail:
 * Vojtech Pavlik, Simunkova 1594, Prague 8, 182 00 Czech Reखुला
 */

#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/kernel.h>

#समावेश <linux/hid.h>
#समावेश <linux/hid-debug.h>

#समावेश "hid-ids.h"

#घोषणा unk	KEY_UNKNOWN

अटल स्थिर अचिन्हित अक्षर hid_keyboard[256] = अणु
	  0,  0,  0,  0, 30, 48, 46, 32, 18, 33, 34, 35, 23, 36, 37, 38,
	 50, 49, 24, 25, 16, 19, 31, 20, 22, 47, 17, 45, 21, 44,  2,  3,
	  4,  5,  6,  7,  8,  9, 10, 11, 28,  1, 14, 15, 57, 12, 13, 26,
	 27, 43, 43, 39, 40, 41, 51, 52, 53, 58, 59, 60, 61, 62, 63, 64,
	 65, 66, 67, 68, 87, 88, 99, 70,119,110,102,104,111,107,109,106,
	105,108,103, 69, 98, 55, 74, 78, 96, 79, 80, 81, 75, 76, 77, 71,
	 72, 73, 82, 83, 86,127,116,117,183,184,185,186,187,188,189,190,
	191,192,193,194,134,138,130,132,128,129,131,137,133,135,136,113,
	115,114,unk,unk,unk,121,unk, 89, 93,124, 92, 94, 95,unk,unk,unk,
	122,123, 90, 91, 85,unk,unk,unk,unk,unk,unk,unk,111,unk,unk,unk,
	unk,unk,unk,unk,unk,unk,unk,unk,unk,unk,unk,unk,unk,unk,unk,unk,
	unk,unk,unk,unk,unk,unk,179,180,unk,unk,unk,unk,unk,unk,unk,unk,
	unk,unk,unk,unk,unk,unk,unk,unk,unk,unk,unk,unk,unk,unk,unk,unk,
	unk,unk,unk,unk,unk,unk,unk,unk,111,unk,unk,unk,unk,unk,unk,unk,
	 29, 42, 56,125, 97, 54,100,126,164,166,165,163,161,115,114,113,
	150,158,159,128,136,177,178,176,142,152,173,140,unk,unk,unk,unk
पूर्ण;

अटल स्थिर काष्ठा अणु
	__s32 x;
	__s32 y;
पूर्ण  hid_hat_to_axis[] = अणुअणु 0, 0पूर्ण, अणु 0,-1पूर्ण, अणु 1,-1पूर्ण, अणु 1, 0पूर्ण, अणु 1, 1पूर्ण, अणु 0, 1पूर्ण, अणु-1, 1पूर्ण, अणु-1, 0पूर्ण, अणु-1,-1पूर्णपूर्ण;

#घोषणा map_असल(c)	hid_map_usage(hidinput, usage, &bit, &max, EV_ABS, (c))
#घोषणा map_rel(c)	hid_map_usage(hidinput, usage, &bit, &max, EV_REL, (c))
#घोषणा map_key(c)	hid_map_usage(hidinput, usage, &bit, &max, EV_KEY, (c))
#घोषणा map_led(c)	hid_map_usage(hidinput, usage, &bit, &max, EV_LED, (c))

#घोषणा map_असल_clear(c)	hid_map_usage_clear(hidinput, usage, &bit, \
		&max, EV_ABS, (c))
#घोषणा map_key_clear(c)	hid_map_usage_clear(hidinput, usage, &bit, \
		&max, EV_KEY, (c))

अटल bool match_scancode(काष्ठा hid_usage *usage,
			   अचिन्हित पूर्णांक cur_idx, अचिन्हित पूर्णांक scancode)
अणु
	वापस (usage->hid & (HID_USAGE_PAGE | HID_USAGE)) == scancode;
पूर्ण

अटल bool match_keycode(काष्ठा hid_usage *usage,
			  अचिन्हित पूर्णांक cur_idx, अचिन्हित पूर्णांक keycode)
अणु
	/*
	 * We should exclude unmapped usages when करोing lookup by keycode.
	 */
	वापस (usage->type == EV_KEY && usage->code == keycode);
पूर्ण

अटल bool match_index(काष्ठा hid_usage *usage,
			अचिन्हित पूर्णांक cur_idx, अचिन्हित पूर्णांक idx)
अणु
	वापस cur_idx == idx;
पूर्ण

प्रकार bool (*hid_usage_cmp_t)(काष्ठा hid_usage *usage,
				अचिन्हित पूर्णांक cur_idx, अचिन्हित पूर्णांक val);

अटल काष्ठा hid_usage *hidinput_find_key(काष्ठा hid_device *hid,
					   hid_usage_cmp_t match,
					   अचिन्हित पूर्णांक value,
					   अचिन्हित पूर्णांक *usage_idx)
अणु
	अचिन्हित पूर्णांक i, j, k, cur_idx = 0;
	काष्ठा hid_report *report;
	काष्ठा hid_usage *usage;

	क्रम (k = HID_INPUT_REPORT; k <= HID_OUTPUT_REPORT; k++) अणु
		list_क्रम_each_entry(report, &hid->report_क्रमागत[k].report_list, list) अणु
			क्रम (i = 0; i < report->maxfield; i++) अणु
				क्रम (j = 0; j < report->field[i]->maxusage; j++) अणु
					usage = report->field[i]->usage + j;
					अगर (usage->type == EV_KEY || usage->type == 0) अणु
						अगर (match(usage, cur_idx, value)) अणु
							अगर (usage_idx)
								*usage_idx = cur_idx;
							वापस usage;
						पूर्ण
						cur_idx++;
					पूर्ण
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण
	वापस शून्य;
पूर्ण

अटल काष्ठा hid_usage *hidinput_locate_usage(काष्ठा hid_device *hid,
					स्थिर काष्ठा input_keymap_entry *ke,
					अचिन्हित पूर्णांक *index)
अणु
	काष्ठा hid_usage *usage;
	अचिन्हित पूर्णांक scancode;

	अगर (ke->flags & INPUT_KEYMAP_BY_INDEX)
		usage = hidinput_find_key(hid, match_index, ke->index, index);
	अन्यथा अगर (input_scancode_to_scalar(ke, &scancode) == 0)
		usage = hidinput_find_key(hid, match_scancode, scancode, index);
	अन्यथा
		usage = शून्य;

	वापस usage;
पूर्ण

अटल पूर्णांक hidinput_getkeycode(काष्ठा input_dev *dev,
			       काष्ठा input_keymap_entry *ke)
अणु
	काष्ठा hid_device *hid = input_get_drvdata(dev);
	काष्ठा hid_usage *usage;
	अचिन्हित पूर्णांक scancode, index;

	usage = hidinput_locate_usage(hid, ke, &index);
	अगर (usage) अणु
		ke->keycode = usage->type == EV_KEY ?
				usage->code : KEY_RESERVED;
		ke->index = index;
		scancode = usage->hid & (HID_USAGE_PAGE | HID_USAGE);
		ke->len = माप(scancode);
		स_नकल(ke->scancode, &scancode, माप(scancode));
		वापस 0;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक hidinput_setkeycode(काष्ठा input_dev *dev,
			       स्थिर काष्ठा input_keymap_entry *ke,
			       अचिन्हित पूर्णांक *old_keycode)
अणु
	काष्ठा hid_device *hid = input_get_drvdata(dev);
	काष्ठा hid_usage *usage;

	usage = hidinput_locate_usage(hid, ke, शून्य);
	अगर (usage) अणु
		*old_keycode = usage->type == EV_KEY ?
				usage->code : KEY_RESERVED;
		usage->code = ke->keycode;

		clear_bit(*old_keycode, dev->keybit);
		set_bit(usage->code, dev->keybit);
		dbg_hid("Assigned keycode %d to HID usage code %x\n",
			usage->code, usage->hid);

		/*
		 * Set the keybit क्रम the old keycode अगर the old keycode is used
		 * by another key
		 */
		अगर (hidinput_find_key(hid, match_keycode, *old_keycode, शून्य))
			set_bit(*old_keycode, dev->keybit);

		वापस 0;
	पूर्ण

	वापस -EINVAL;
पूर्ण


/**
 * hidinput_calc_असल_res - calculate an असलolute axis resolution
 * @field: the HID report field to calculate resolution क्रम
 * @code: axis code
 *
 * The क्रमmula is:
 *                         (logical_maximum - logical_minimum)
 * resolution = ----------------------------------------------------------
 *              (physical_maximum - physical_minimum) * 10 ^ unit_exponent
 *
 * as seen in the HID specअगरication v1.11 6.2.2.7 Global Items.
 *
 * Only exponent 1 length units are processed. Cenसमयters and inches are
 * converted to millimeters. Degrees are converted to radians.
 */
__s32 hidinput_calc_असल_res(स्थिर काष्ठा hid_field *field, __u16 code)
अणु
	__s32 unit_exponent = field->unit_exponent;
	__s32 logical_extents = field->logical_maximum -
					field->logical_minimum;
	__s32 physical_extents = field->physical_maximum -
					field->physical_minimum;
	__s32 prev;

	/* Check अगर the extents are sane */
	अगर (logical_extents <= 0 || physical_extents <= 0)
		वापस 0;

	/*
	 * Verअगरy and convert units.
	 * See HID specअगरication v1.11 6.2.2.7 Global Items क्रम unit decoding
	 */
	चयन (code) अणु
	हाल ABS_X:
	हाल ABS_Y:
	हाल ABS_Z:
	हाल ABS_MT_POSITION_X:
	हाल ABS_MT_POSITION_Y:
	हाल ABS_MT_TOOL_X:
	हाल ABS_MT_TOOL_Y:
	हाल ABS_MT_TOUCH_MAJOR:
	हाल ABS_MT_TOUCH_MINOR:
		अगर (field->unit == 0x11) अणु		/* If cenसमयters */
			/* Convert to millimeters */
			unit_exponent += 1;
		पूर्ण अन्यथा अगर (field->unit == 0x13) अणु	/* If inches */
			/* Convert to millimeters */
			prev = physical_extents;
			physical_extents *= 254;
			अगर (physical_extents < prev)
				वापस 0;
			unit_exponent -= 1;
		पूर्ण अन्यथा अणु
			वापस 0;
		पूर्ण
		अवरोध;

	हाल ABS_RX:
	हाल ABS_RY:
	हाल ABS_RZ:
	हाल ABS_WHEEL:
	हाल ABS_TILT_X:
	हाल ABS_TILT_Y:
		अगर (field->unit == 0x14) अणु		/* If degrees */
			/* Convert to radians */
			prev = logical_extents;
			logical_extents *= 573;
			अगर (logical_extents < prev)
				वापस 0;
			unit_exponent += 1;
		पूर्ण अन्यथा अगर (field->unit != 0x12) अणु	/* If not radians */
			वापस 0;
		पूर्ण
		अवरोध;

	शेष:
		वापस 0;
	पूर्ण

	/* Apply negative unit exponent */
	क्रम (; unit_exponent < 0; unit_exponent++) अणु
		prev = logical_extents;
		logical_extents *= 10;
		अगर (logical_extents < prev)
			वापस 0;
	पूर्ण
	/* Apply positive unit exponent */
	क्रम (; unit_exponent > 0; unit_exponent--) अणु
		prev = physical_extents;
		physical_extents *= 10;
		अगर (physical_extents < prev)
			वापस 0;
	पूर्ण

	/* Calculate resolution */
	वापस DIV_ROUND_CLOSEST(logical_extents, physical_extents);
पूर्ण
EXPORT_SYMBOL_GPL(hidinput_calc_असल_res);

#अगर_घोषित CONFIG_HID_BATTERY_STRENGTH
अटल क्रमागत घातer_supply_property hidinput_battery_props[] = अणु
	POWER_SUPPLY_PROP_PRESENT,
	POWER_SUPPLY_PROP_ONLINE,
	POWER_SUPPLY_PROP_CAPACITY,
	POWER_SUPPLY_PROP_MODEL_NAME,
	POWER_SUPPLY_PROP_STATUS,
	POWER_SUPPLY_PROP_SCOPE,
पूर्ण;

#घोषणा HID_BATTERY_QUIRK_PERCENT	(1 << 0) /* always reports percent */
#घोषणा HID_BATTERY_QUIRK_FEATURE	(1 << 1) /* ask क्रम feature report */
#घोषणा HID_BATTERY_QUIRK_IGNORE	(1 << 2) /* completely ignore the battery */

अटल स्थिर काष्ठा hid_device_id hid_battery_quirks[] = अणु
	अणु HID_BLUETOOTH_DEVICE(USB_VENDOR_ID_APPLE,
		USB_DEVICE_ID_APPLE_ALU_WIRELESS_2009_ISO),
	  HID_BATTERY_QUIRK_PERCENT | HID_BATTERY_QUIRK_FEATURE पूर्ण,
	अणु HID_BLUETOOTH_DEVICE(USB_VENDOR_ID_APPLE,
		USB_DEVICE_ID_APPLE_ALU_WIRELESS_2009_ANSI),
	  HID_BATTERY_QUIRK_PERCENT | HID_BATTERY_QUIRK_FEATURE पूर्ण,
	अणु HID_BLUETOOTH_DEVICE(USB_VENDOR_ID_APPLE,
		USB_DEVICE_ID_APPLE_ALU_WIRELESS_2011_ANSI),
	  HID_BATTERY_QUIRK_PERCENT | HID_BATTERY_QUIRK_FEATURE पूर्ण,
	अणु HID_BLUETOOTH_DEVICE(USB_VENDOR_ID_APPLE,
			       USB_DEVICE_ID_APPLE_ALU_WIRELESS_2011_ISO),
	  HID_BATTERY_QUIRK_PERCENT | HID_BATTERY_QUIRK_FEATURE पूर्ण,
	अणु HID_BLUETOOTH_DEVICE(USB_VENDOR_ID_APPLE,
		USB_DEVICE_ID_APPLE_ALU_WIRELESS_ANSI),
	  HID_BATTERY_QUIRK_PERCENT | HID_BATTERY_QUIRK_FEATURE पूर्ण,
	अणु HID_BLUETOOTH_DEVICE(USB_VENDOR_ID_ELECOM,
		USB_DEVICE_ID_ELECOM_BM084),
	  HID_BATTERY_QUIRK_IGNORE पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_SYMBOL,
		USB_DEVICE_ID_SYMBOL_SCANNER_3),
	  HID_BATTERY_QUIRK_IGNORE पूर्ण,
	अणु HID_BLUETOOTH_DEVICE(USB_VENDOR_ID_ASUSTEK,
		USB_DEVICE_ID_ASUSTEK_T100CHI_KEYBOARD),
	  HID_BATTERY_QUIRK_IGNORE पूर्ण,
	अणु HID_BLUETOOTH_DEVICE(USB_VENDOR_ID_LOGITECH,
		USB_DEVICE_ID_LOGITECH_DINOVO_EDGE_KBD),
	  HID_BATTERY_QUIRK_IGNORE पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_ELAN, USB_DEVICE_ID_ASUS_UX550_TOUCHSCREEN),
	  HID_BATTERY_QUIRK_IGNORE पूर्ण,
	अणु HID_I2C_DEVICE(USB_VENDOR_ID_ELAN, I2C_DEVICE_ID_HP_SPECTRE_X360_15),
	  HID_BATTERY_QUIRK_IGNORE पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल अचिन्हित find_battery_quirk(काष्ठा hid_device *hdev)
अणु
	अचिन्हित quirks = 0;
	स्थिर काष्ठा hid_device_id *match;

	match = hid_match_id(hdev, hid_battery_quirks);
	अगर (match != शून्य)
		quirks = match->driver_data;

	वापस quirks;
पूर्ण

अटल पूर्णांक hidinput_scale_battery_capacity(काष्ठा hid_device *dev,
					   पूर्णांक value)
अणु
	अगर (dev->battery_min < dev->battery_max &&
	    value >= dev->battery_min && value <= dev->battery_max)
		value = ((value - dev->battery_min) * 100) /
			(dev->battery_max - dev->battery_min);

	वापस value;
पूर्ण

अटल पूर्णांक hidinput_query_battery_capacity(काष्ठा hid_device *dev)
अणु
	u8 *buf;
	पूर्णांक ret;

	buf = kदो_स्मृति(4, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	ret = hid_hw_raw_request(dev, dev->battery_report_id, buf, 4,
				 dev->battery_report_type, HID_REQ_GET_REPORT);
	अगर (ret < 2) अणु
		kमुक्त(buf);
		वापस -ENODATA;
	पूर्ण

	ret = hidinput_scale_battery_capacity(dev, buf[1]);
	kमुक्त(buf);
	वापस ret;
पूर्ण

अटल पूर्णांक hidinput_get_battery_property(काष्ठा घातer_supply *psy,
					 क्रमागत घातer_supply_property prop,
					 जोड़ घातer_supply_propval *val)
अणु
	काष्ठा hid_device *dev = घातer_supply_get_drvdata(psy);
	पूर्णांक value;
	पूर्णांक ret = 0;

	चयन (prop) अणु
	हाल POWER_SUPPLY_PROP_PRESENT:
	हाल POWER_SUPPLY_PROP_ONLINE:
		val->पूर्णांकval = 1;
		अवरोध;

	हाल POWER_SUPPLY_PROP_CAPACITY:
		अगर (dev->battery_status != HID_BATTERY_REPORTED &&
		    !dev->battery_aव्योम_query) अणु
			value = hidinput_query_battery_capacity(dev);
			अगर (value < 0)
				वापस value;
		पूर्ण अन्यथा  अणु
			value = dev->battery_capacity;
		पूर्ण

		val->पूर्णांकval = value;
		अवरोध;

	हाल POWER_SUPPLY_PROP_MODEL_NAME:
		val->strval = dev->name;
		अवरोध;

	हाल POWER_SUPPLY_PROP_STATUS:
		अगर (dev->battery_status != HID_BATTERY_REPORTED &&
		    !dev->battery_aव्योम_query) अणु
			value = hidinput_query_battery_capacity(dev);
			अगर (value < 0)
				वापस value;

			dev->battery_capacity = value;
			dev->battery_status = HID_BATTERY_QUERIED;
		पूर्ण

		अगर (dev->battery_status == HID_BATTERY_UNKNOWN)
			val->पूर्णांकval = POWER_SUPPLY_STATUS_UNKNOWN;
		अन्यथा अगर (dev->battery_capacity == 100)
			val->पूर्णांकval = POWER_SUPPLY_STATUS_FULL;
		अन्यथा
			val->पूर्णांकval = POWER_SUPPLY_STATUS_DISCHARGING;
		अवरोध;

	हाल POWER_SUPPLY_PROP_SCOPE:
		val->पूर्णांकval = POWER_SUPPLY_SCOPE_DEVICE;
		अवरोध;

	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक hidinput_setup_battery(काष्ठा hid_device *dev, अचिन्हित report_type,
				  काष्ठा hid_field *field, bool is_percentage)
अणु
	काष्ठा घातer_supply_desc *psy_desc;
	काष्ठा घातer_supply_config psy_cfg = अणु .drv_data = dev, पूर्ण;
	अचिन्हित quirks;
	s32 min, max;
	पूर्णांक error;

	अगर (dev->battery)
		वापस 0;	/* alपढ़ोy initialized? */

	quirks = find_battery_quirk(dev);

	hid_dbg(dev, "device %x:%x:%x %d quirks %d\n",
		dev->bus, dev->venकरोr, dev->product, dev->version, quirks);

	अगर (quirks & HID_BATTERY_QUIRK_IGNORE)
		वापस 0;

	psy_desc = kzalloc(माप(*psy_desc), GFP_KERNEL);
	अगर (!psy_desc)
		वापस -ENOMEM;

	psy_desc->name = kaप्र_लिखो(GFP_KERNEL, "hid-%s-battery",
				   म_माप(dev->uniq) ?
					dev->uniq : dev_name(&dev->dev));
	अगर (!psy_desc->name) अणु
		error = -ENOMEM;
		जाओ err_मुक्त_mem;
	पूर्ण

	psy_desc->type = POWER_SUPPLY_TYPE_BATTERY;
	psy_desc->properties = hidinput_battery_props;
	psy_desc->num_properties = ARRAY_SIZE(hidinput_battery_props);
	psy_desc->use_क्रम_apm = 0;
	psy_desc->get_property = hidinput_get_battery_property;

	min = field->logical_minimum;
	max = field->logical_maximum;

	अगर (is_percentage || (quirks & HID_BATTERY_QUIRK_PERCENT)) अणु
		min = 0;
		max = 100;
	पूर्ण

	अगर (quirks & HID_BATTERY_QUIRK_FEATURE)
		report_type = HID_FEATURE_REPORT;

	dev->battery_min = min;
	dev->battery_max = max;
	dev->battery_report_type = report_type;
	dev->battery_report_id = field->report->id;

	/*
	 * Stylus is normally not connected to the device and thus we
	 * can't query the device and get meaningful battery strength.
	 * We have to रुको क्रम the device to report it on its own.
	 */
	dev->battery_aव्योम_query = report_type == HID_INPUT_REPORT &&
				   field->physical == HID_DG_STYLUS;

	dev->battery = घातer_supply_रेजिस्टर(&dev->dev, psy_desc, &psy_cfg);
	अगर (IS_ERR(dev->battery)) अणु
		error = PTR_ERR(dev->battery);
		hid_warn(dev, "can't register power supply: %d\n", error);
		जाओ err_मुक्त_name;
	पूर्ण

	घातer_supply_घातers(dev->battery, &dev->dev);
	वापस 0;

err_मुक्त_name:
	kमुक्त(psy_desc->name);
err_मुक्त_mem:
	kमुक्त(psy_desc);
	dev->battery = शून्य;
	वापस error;
पूर्ण

अटल व्योम hidinput_cleanup_battery(काष्ठा hid_device *dev)
अणु
	स्थिर काष्ठा घातer_supply_desc *psy_desc;

	अगर (!dev->battery)
		वापस;

	psy_desc = dev->battery->desc;
	घातer_supply_unरेजिस्टर(dev->battery);
	kमुक्त(psy_desc->name);
	kमुक्त(psy_desc);
	dev->battery = शून्य;
पूर्ण

अटल व्योम hidinput_update_battery(काष्ठा hid_device *dev, पूर्णांक value)
अणु
	पूर्णांक capacity;

	अगर (!dev->battery)
		वापस;

	अगर (value == 0 || value < dev->battery_min || value > dev->battery_max)
		वापस;

	capacity = hidinput_scale_battery_capacity(dev, value);

	अगर (dev->battery_status != HID_BATTERY_REPORTED ||
	    capacity != dev->battery_capacity ||
	    kसमय_after(kसमय_get_coarse(), dev->battery_ratelimit_समय)) अणु
		dev->battery_capacity = capacity;
		dev->battery_status = HID_BATTERY_REPORTED;
		dev->battery_ratelimit_समय =
			kसमय_add_ms(kसमय_get_coarse(), 30 * 1000);
		घातer_supply_changed(dev->battery);
	पूर्ण
पूर्ण
#अन्यथा  /* !CONFIG_HID_BATTERY_STRENGTH */
अटल पूर्णांक hidinput_setup_battery(काष्ठा hid_device *dev, अचिन्हित report_type,
				  काष्ठा hid_field *field, bool is_percentage)
अणु
	वापस 0;
पूर्ण

अटल व्योम hidinput_cleanup_battery(काष्ठा hid_device *dev)
अणु
पूर्ण

अटल व्योम hidinput_update_battery(काष्ठा hid_device *dev, पूर्णांक value)
अणु
पूर्ण
#पूर्ण_अगर	/* CONFIG_HID_BATTERY_STRENGTH */

अटल व्योम hidinput_configure_usage(काष्ठा hid_input *hidinput, काष्ठा hid_field *field,
				     काष्ठा hid_usage *usage)
अणु
	काष्ठा input_dev *input = hidinput->input;
	काष्ठा hid_device *device = input_get_drvdata(input);
	पूर्णांक max = 0, code;
	अचिन्हित दीर्घ *bit = शून्य;

	field->hidinput = hidinput;

	अगर (field->flags & HID_MAIN_ITEM_CONSTANT)
		जाओ ignore;

	/* Ignore अगर report count is out of bounds. */
	अगर (field->report_count < 1)
		जाओ ignore;

	/* only LED usages are supported in output fields */
	अगर (field->report_type == HID_OUTPUT_REPORT &&
			(usage->hid & HID_USAGE_PAGE) != HID_UP_LED) अणु
		जाओ ignore;
	पूर्ण

	अगर (device->driver->input_mapping) अणु
		पूर्णांक ret = device->driver->input_mapping(device, hidinput, field,
				usage, &bit, &max);
		अगर (ret > 0)
			जाओ mapped;
		अगर (ret < 0)
			जाओ ignore;
	पूर्ण

	चयन (usage->hid & HID_USAGE_PAGE) अणु
	हाल HID_UP_UNDEFINED:
		जाओ ignore;

	हाल HID_UP_KEYBOARD:
		set_bit(EV_REP, input->evbit);

		अगर ((usage->hid & HID_USAGE) < 256) अणु
			अगर (!hid_keyboard[usage->hid & HID_USAGE]) जाओ ignore;
			map_key_clear(hid_keyboard[usage->hid & HID_USAGE]);
		पूर्ण अन्यथा
			map_key(KEY_UNKNOWN);

		अवरोध;

	हाल HID_UP_BUTTON:
		code = ((usage->hid - 1) & HID_USAGE);

		चयन (field->application) अणु
		हाल HID_GD_MOUSE:
		हाल HID_GD_POINTER:  code += BTN_MOUSE; अवरोध;
		हाल HID_GD_JOYSTICK:
				अगर (code <= 0xf)
					code += BTN_JOYSTICK;
				अन्यथा
					code += BTN_TRIGGER_HAPPY - 0x10;
				अवरोध;
		हाल HID_GD_GAMEPAD:
				अगर (code <= 0xf)
					code += BTN_GAMEPAD;
				अन्यथा
					code += BTN_TRIGGER_HAPPY - 0x10;
				अवरोध;
		शेष:
			चयन (field->physical) अणु
			हाल HID_GD_MOUSE:
			हाल HID_GD_POINTER:  code += BTN_MOUSE; अवरोध;
			हाल HID_GD_JOYSTICK: code += BTN_JOYSTICK; अवरोध;
			हाल HID_GD_GAMEPAD:  code += BTN_GAMEPAD; अवरोध;
			शेष:              code += BTN_MISC;
			पूर्ण
		पूर्ण

		map_key(code);
		अवरोध;

	हाल HID_UP_SIMULATION:
		चयन (usage->hid & 0xffff) अणु
		हाल 0xba: map_असल(ABS_RUDDER);   अवरोध;
		हाल 0xbb: map_असल(ABS_THROTTLE); अवरोध;
		हाल 0xc4: map_असल(ABS_GAS);      अवरोध;
		हाल 0xc5: map_असल(ABS_BRAKE);    अवरोध;
		हाल 0xc8: map_असल(ABS_WHEEL);    अवरोध;
		शेष:   जाओ ignore;
		पूर्ण
		अवरोध;

	हाल HID_UP_GENDESK:
		अगर ((usage->hid & 0xf0) == 0x80) अणु	/* SystemControl */
			चयन (usage->hid & 0xf) अणु
			हाल 0x1: map_key_clear(KEY_POWER);  अवरोध;
			हाल 0x2: map_key_clear(KEY_SLEEP);  अवरोध;
			हाल 0x3: map_key_clear(KEY_WAKEUP); अवरोध;
			हाल 0x4: map_key_clear(KEY_CONTEXT_MENU); अवरोध;
			हाल 0x5: map_key_clear(KEY_MENU); अवरोध;
			हाल 0x6: map_key_clear(KEY_PROG1); अवरोध;
			हाल 0x7: map_key_clear(KEY_HELP); अवरोध;
			हाल 0x8: map_key_clear(KEY_EXIT); अवरोध;
			हाल 0x9: map_key_clear(KEY_SELECT); अवरोध;
			हाल 0xa: map_key_clear(KEY_RIGHT); अवरोध;
			हाल 0xb: map_key_clear(KEY_LEFT); अवरोध;
			हाल 0xc: map_key_clear(KEY_UP); अवरोध;
			हाल 0xd: map_key_clear(KEY_DOWN); अवरोध;
			हाल 0xe: map_key_clear(KEY_POWER2); अवरोध;
			हाल 0xf: map_key_clear(KEY_RESTART); अवरोध;
			शेष: जाओ unknown;
			पूर्ण
			अवरोध;
		पूर्ण

		अगर ((usage->hid & 0xf0) == 0xb0) अणु	/* SC - Display */
			चयन (usage->hid & 0xf) अणु
			हाल 0x05: map_key_clear(KEY_SWITCHVIDEOMODE); अवरोध;
			शेष: जाओ ignore;
			पूर्ण
			अवरोध;
		पूर्ण

		/*
		 * Some lazy venकरोrs declare 255 usages क्रम System Control,
		 * leading to the creation of ABS_X|Y axis and too many others.
		 * It wouldn't be a problem if joydev doesn't consider the
		 * device as a joystick then.
		 */
		अगर (field->application == HID_GD_SYSTEM_CONTROL)
			जाओ ignore;

		अगर ((usage->hid & 0xf0) == 0x90) अणु	/* D-pad */
			चयन (usage->hid) अणु
			हाल HID_GD_UP:	   usage->hat_dir = 1; अवरोध;
			हाल HID_GD_DOWN:  usage->hat_dir = 5; अवरोध;
			हाल HID_GD_RIGHT: usage->hat_dir = 3; अवरोध;
			हाल HID_GD_LEFT:  usage->hat_dir = 7; अवरोध;
			शेष: जाओ unknown;
			पूर्ण
			अगर (field->dpad) अणु
				map_असल(field->dpad);
				जाओ ignore;
			पूर्ण
			map_असल(ABS_HAT0X);
			अवरोध;
		पूर्ण

		चयन (usage->hid) अणु
		/* These usage IDs map directly to the usage codes. */
		हाल HID_GD_X: हाल HID_GD_Y: हाल HID_GD_Z:
		हाल HID_GD_RX: हाल HID_GD_RY: हाल HID_GD_RZ:
			अगर (field->flags & HID_MAIN_ITEM_RELATIVE)
				map_rel(usage->hid & 0xf);
			अन्यथा
				map_असल_clear(usage->hid & 0xf);
			अवरोध;

		हाल HID_GD_WHEEL:
			अगर (field->flags & HID_MAIN_ITEM_RELATIVE) अणु
				set_bit(REL_WHEEL, input->relbit);
				map_rel(REL_WHEEL_HI_RES);
			पूर्ण अन्यथा अणु
				map_असल(usage->hid & 0xf);
			पूर्ण
			अवरोध;
		हाल HID_GD_SLIDER: हाल HID_GD_DIAL:
			अगर (field->flags & HID_MAIN_ITEM_RELATIVE)
				map_rel(usage->hid & 0xf);
			अन्यथा
				map_असल(usage->hid & 0xf);
			अवरोध;

		हाल HID_GD_HATSWITCH:
			usage->hat_min = field->logical_minimum;
			usage->hat_max = field->logical_maximum;
			map_असल(ABS_HAT0X);
			अवरोध;

		हाल HID_GD_START:	map_key_clear(BTN_START);	अवरोध;
		हाल HID_GD_SELECT:	map_key_clear(BTN_SELECT);	अवरोध;

		हाल HID_GD_RFKILL_BTN:
			/* MS wireless radio ctl extension, also check CA */
			अगर (field->application == HID_GD_WIRELESS_RADIO_CTLS) अणु
				map_key_clear(KEY_RFKILL);
				/* We need to simulate the btn release */
				field->flags |= HID_MAIN_ITEM_RELATIVE;
				अवरोध;
			पूर्ण
			जाओ unknown;

		शेष: जाओ unknown;
		पूर्ण

		अवरोध;

	हाल HID_UP_LED:
		चयन (usage->hid & 0xffff) अणु		      /* HID-Value:                   */
		हाल 0x01:  map_led (LED_NUML);     अवरोध;    /*   "Num Lock"                 */
		हाल 0x02:  map_led (LED_CAPSL);    अवरोध;    /*   "Caps Lock"                */
		हाल 0x03:  map_led (LED_SCROLLL);  अवरोध;    /*   "Scroll Lock"              */
		हाल 0x04:  map_led (LED_COMPOSE);  अवरोध;    /*   "Compose"                  */
		हाल 0x05:  map_led (LED_KANA);     अवरोध;    /*   "Kana"                     */
		हाल 0x27:  map_led (LED_SLEEP);    अवरोध;    /*   "Stand-By"                 */
		हाल 0x4c:  map_led (LED_SUSPEND);  अवरोध;    /*   "System Suspend"           */
		हाल 0x09:  map_led (LED_MUTE);     अवरोध;    /*   "Mute"                     */
		हाल 0x4b:  map_led (LED_MISC);     अवरोध;    /*   "Generic Indicator"        */
		हाल 0x19:  map_led (LED_MAIL);     अवरोध;    /*   "Message Waiting"          */
		हाल 0x4d:  map_led (LED_CHARGING); अवरोध;    /*   "External Power Connected" */

		शेष: जाओ ignore;
		पूर्ण
		अवरोध;

	हाल HID_UP_DIGITIZER:
		अगर ((field->application & 0xff) == 0x01) /* Digitizer */
			__set_bit(INPUT_PROP_POINTER, input->propbit);
		अन्यथा अगर ((field->application & 0xff) == 0x02) /* Pen */
			__set_bit(INPUT_PROP_सूचीECT, input->propbit);

		चयन (usage->hid & 0xff) अणु
		हाल 0x00: /* Undefined */
			जाओ ignore;

		हाल 0x30: /* TipPressure */
			अगर (!test_bit(BTN_TOUCH, input->keybit)) अणु
				device->quirks |= HID_QUIRK_NOTOUCH;
				set_bit(EV_KEY, input->evbit);
				set_bit(BTN_TOUCH, input->keybit);
			पूर्ण
			map_असल_clear(ABS_PRESSURE);
			अवरोध;

		हाल 0x32: /* InRange */
			चयन (field->physical & 0xff) अणु
			हाल 0x21: map_key(BTN_TOOL_MOUSE); अवरोध;
			हाल 0x22: map_key(BTN_TOOL_FINGER); अवरोध;
			शेष: map_key(BTN_TOOL_PEN); अवरोध;
			पूर्ण
			अवरोध;

		हाल 0x3b: /* Battery Strength */
			hidinput_setup_battery(device, HID_INPUT_REPORT, field, false);
			usage->type = EV_PWR;
			वापस;

		हाल 0x3c: /* Invert */
			map_key_clear(BTN_TOOL_RUBBER);
			अवरोध;

		हाल 0x3d: /* X Tilt */
			map_असल_clear(ABS_TILT_X);
			अवरोध;

		हाल 0x3e: /* Y Tilt */
			map_असल_clear(ABS_TILT_Y);
			अवरोध;

		हाल 0x33: /* Touch */
		हाल 0x42: /* TipSwitch */
		हाल 0x43: /* TipSwitch2 */
			device->quirks &= ~HID_QUIRK_NOTOUCH;
			map_key_clear(BTN_TOUCH);
			अवरोध;

		हाल 0x44: /* BarrelSwitch */
			map_key_clear(BTN_STYLUS);
			अवरोध;

		हाल 0x45: /* ERASER */
			/*
			 * This event is reported when eraser tip touches the surface.
			 * Actual eraser (BTN_TOOL_RUBBER) is set by Invert usage when
			 * tool माला_लो in proximity.
			 */
			map_key_clear(BTN_TOUCH);
			अवरोध;

		हाल 0x46: /* TabletPick */
		हाल 0x5a: /* SecondaryBarrelSwitch */
			map_key_clear(BTN_STYLUS2);
			अवरोध;

		हाल 0x5b: /* TransducerSerialNumber */
			usage->type = EV_MSC;
			usage->code = MSC_SERIAL;
			bit = input->mscbit;
			max = MSC_MAX;
			अवरोध;

		शेष:  जाओ unknown;
		पूर्ण
		अवरोध;

	हाल HID_UP_TELEPHONY:
		चयन (usage->hid & HID_USAGE) अणु
		हाल 0x2f: map_key_clear(KEY_MICMUTE);		अवरोध;
		हाल 0xb0: map_key_clear(KEY_NUMERIC_0);	अवरोध;
		हाल 0xb1: map_key_clear(KEY_NUMERIC_1);	अवरोध;
		हाल 0xb2: map_key_clear(KEY_NUMERIC_2);	अवरोध;
		हाल 0xb3: map_key_clear(KEY_NUMERIC_3);	अवरोध;
		हाल 0xb4: map_key_clear(KEY_NUMERIC_4);	अवरोध;
		हाल 0xb5: map_key_clear(KEY_NUMERIC_5);	अवरोध;
		हाल 0xb6: map_key_clear(KEY_NUMERIC_6);	अवरोध;
		हाल 0xb7: map_key_clear(KEY_NUMERIC_7);	अवरोध;
		हाल 0xb8: map_key_clear(KEY_NUMERIC_8);	अवरोध;
		हाल 0xb9: map_key_clear(KEY_NUMERIC_9);	अवरोध;
		हाल 0xba: map_key_clear(KEY_NUMERIC_STAR);	अवरोध;
		हाल 0xbb: map_key_clear(KEY_NUMERIC_POUND);	अवरोध;
		हाल 0xbc: map_key_clear(KEY_NUMERIC_A);	अवरोध;
		हाल 0xbd: map_key_clear(KEY_NUMERIC_B);	अवरोध;
		हाल 0xbe: map_key_clear(KEY_NUMERIC_C);	अवरोध;
		हाल 0xbf: map_key_clear(KEY_NUMERIC_D);	अवरोध;
		शेष: जाओ ignore;
		पूर्ण
		अवरोध;

	हाल HID_UP_CONSUMER:	/* USB HUT v1.12, pages 75-84 */
		चयन (usage->hid & HID_USAGE) अणु
		हाल 0x000: जाओ ignore;
		हाल 0x030: map_key_clear(KEY_POWER);		अवरोध;
		हाल 0x031: map_key_clear(KEY_RESTART);		अवरोध;
		हाल 0x032: map_key_clear(KEY_SLEEP);		अवरोध;
		हाल 0x034: map_key_clear(KEY_SLEEP);		अवरोध;
		हाल 0x035: map_key_clear(KEY_KBDILLUMTOGGLE);	अवरोध;
		हाल 0x036: map_key_clear(BTN_MISC);		अवरोध;

		हाल 0x040: map_key_clear(KEY_MENU);		अवरोध; /* Menu */
		हाल 0x041: map_key_clear(KEY_SELECT);		अवरोध; /* Menu Pick */
		हाल 0x042: map_key_clear(KEY_UP);		अवरोध; /* Menu Up */
		हाल 0x043: map_key_clear(KEY_DOWN);		अवरोध; /* Menu Down */
		हाल 0x044: map_key_clear(KEY_LEFT);		अवरोध; /* Menu Left */
		हाल 0x045: map_key_clear(KEY_RIGHT);		अवरोध; /* Menu Right */
		हाल 0x046: map_key_clear(KEY_ESC);		अवरोध; /* Menu Escape */
		हाल 0x047: map_key_clear(KEY_KPPLUS);		अवरोध; /* Menu Value Increase */
		हाल 0x048: map_key_clear(KEY_KPMINUS);		अवरोध; /* Menu Value Decrease */

		हाल 0x060: map_key_clear(KEY_INFO);		अवरोध; /* Data On Screen */
		हाल 0x061: map_key_clear(KEY_SUBTITLE);	अवरोध; /* Closed Caption */
		हाल 0x063: map_key_clear(KEY_VCR);		अवरोध; /* VCR/TV */
		हाल 0x065: map_key_clear(KEY_CAMERA);		अवरोध; /* Snapshot */
		हाल 0x069: map_key_clear(KEY_RED);		अवरोध;
		हाल 0x06a: map_key_clear(KEY_GREEN);		अवरोध;
		हाल 0x06b: map_key_clear(KEY_BLUE);		अवरोध;
		हाल 0x06c: map_key_clear(KEY_YELLOW);		अवरोध;
		हाल 0x06d: map_key_clear(KEY_ASPECT_RATIO);	अवरोध;

		हाल 0x06f: map_key_clear(KEY_BRIGHTNESSUP);		अवरोध;
		हाल 0x070: map_key_clear(KEY_BRIGHTNESSDOWN);		अवरोध;
		हाल 0x072: map_key_clear(KEY_BRIGHTNESS_TOGGLE);	अवरोध;
		हाल 0x073: map_key_clear(KEY_BRIGHTNESS_MIN);		अवरोध;
		हाल 0x074: map_key_clear(KEY_BRIGHTNESS_MAX);		अवरोध;
		हाल 0x075: map_key_clear(KEY_BRIGHTNESS_AUTO);		अवरोध;

		हाल 0x079: map_key_clear(KEY_KBDILLUMUP);	अवरोध;
		हाल 0x07a: map_key_clear(KEY_KBDILLUMDOWN);	अवरोध;
		हाल 0x07c: map_key_clear(KEY_KBDILLUMTOGGLE);	अवरोध;

		हाल 0x082: map_key_clear(KEY_VIDEO_NEXT);	अवरोध;
		हाल 0x083: map_key_clear(KEY_LAST);		अवरोध;
		हाल 0x084: map_key_clear(KEY_ENTER);		अवरोध;
		हाल 0x088: map_key_clear(KEY_PC);		अवरोध;
		हाल 0x089: map_key_clear(KEY_TV);		अवरोध;
		हाल 0x08a: map_key_clear(KEY_WWW);		अवरोध;
		हाल 0x08b: map_key_clear(KEY_DVD);		अवरोध;
		हाल 0x08c: map_key_clear(KEY_PHONE);		अवरोध;
		हाल 0x08d: map_key_clear(KEY_PROGRAM);		अवरोध;
		हाल 0x08e: map_key_clear(KEY_VIDEOPHONE);	अवरोध;
		हाल 0x08f: map_key_clear(KEY_GAMES);		अवरोध;
		हाल 0x090: map_key_clear(KEY_MEMO);		अवरोध;
		हाल 0x091: map_key_clear(KEY_CD);		अवरोध;
		हाल 0x092: map_key_clear(KEY_VCR);		अवरोध;
		हाल 0x093: map_key_clear(KEY_TUNER);		अवरोध;
		हाल 0x094: map_key_clear(KEY_EXIT);		अवरोध;
		हाल 0x095: map_key_clear(KEY_HELP);		अवरोध;
		हाल 0x096: map_key_clear(KEY_TAPE);		अवरोध;
		हाल 0x097: map_key_clear(KEY_TV2);		अवरोध;
		हाल 0x098: map_key_clear(KEY_SAT);		अवरोध;
		हाल 0x09a: map_key_clear(KEY_PVR);		अवरोध;

		हाल 0x09c: map_key_clear(KEY_CHANNELUP);	अवरोध;
		हाल 0x09d: map_key_clear(KEY_CHANNELDOWN);	अवरोध;
		हाल 0x0a0: map_key_clear(KEY_VCR2);		अवरोध;

		हाल 0x0b0: map_key_clear(KEY_PLAY);		अवरोध;
		हाल 0x0b1: map_key_clear(KEY_PAUSE);		अवरोध;
		हाल 0x0b2: map_key_clear(KEY_RECORD);		अवरोध;
		हाल 0x0b3: map_key_clear(KEY_FASTFORWARD);	अवरोध;
		हाल 0x0b4: map_key_clear(KEY_REWIND);		अवरोध;
		हाल 0x0b5: map_key_clear(KEY_NEXTSONG);	अवरोध;
		हाल 0x0b6: map_key_clear(KEY_PREVIOUSSONG);	अवरोध;
		हाल 0x0b7: map_key_clear(KEY_STOPCD);		अवरोध;
		हाल 0x0b8: map_key_clear(KEY_EJECTCD);		अवरोध;
		हाल 0x0bc: map_key_clear(KEY_MEDIA_REPEAT);	अवरोध;
		हाल 0x0b9: map_key_clear(KEY_SHUFFLE);		अवरोध;
		हाल 0x0bf: map_key_clear(KEY_SLOW);		अवरोध;

		हाल 0x0cd: map_key_clear(KEY_PLAYPAUSE);	अवरोध;
		हाल 0x0cf: map_key_clear(KEY_VOICECOMMAND);	अवरोध;

		हाल 0x0d9: map_key_clear(KEY_EMOJI_PICKER);	अवरोध;

		हाल 0x0e0: map_असल_clear(ABS_VOLUME);		अवरोध;
		हाल 0x0e2: map_key_clear(KEY_MUTE);		अवरोध;
		हाल 0x0e5: map_key_clear(KEY_BASSBOOST);	अवरोध;
		हाल 0x0e9: map_key_clear(KEY_VOLUMEUP);	अवरोध;
		हाल 0x0ea: map_key_clear(KEY_VOLUMEDOWN);	अवरोध;
		हाल 0x0f5: map_key_clear(KEY_SLOW);		अवरोध;

		हाल 0x181: map_key_clear(KEY_BUTTONCONFIG);	अवरोध;
		हाल 0x182: map_key_clear(KEY_BOOKMARKS);	अवरोध;
		हाल 0x183: map_key_clear(KEY_CONFIG);		अवरोध;
		हाल 0x184: map_key_clear(KEY_WORDPROCESSOR);	अवरोध;
		हाल 0x185: map_key_clear(KEY_EDITOR);		अवरोध;
		हाल 0x186: map_key_clear(KEY_SPREADSHEET);	अवरोध;
		हाल 0x187: map_key_clear(KEY_GRAPHICSEDITOR);	अवरोध;
		हाल 0x188: map_key_clear(KEY_PRESENTATION);	अवरोध;
		हाल 0x189: map_key_clear(KEY_DATABASE);	अवरोध;
		हाल 0x18a: map_key_clear(KEY_MAIL);		अवरोध;
		हाल 0x18b: map_key_clear(KEY_NEWS);		अवरोध;
		हाल 0x18c: map_key_clear(KEY_VOICEMAIL);	अवरोध;
		हाल 0x18d: map_key_clear(KEY_ADDRESSBOOK);	अवरोध;
		हाल 0x18e: map_key_clear(KEY_CALENDAR);	अवरोध;
		हाल 0x18f: map_key_clear(KEY_TASKMANAGER);	अवरोध;
		हाल 0x190: map_key_clear(KEY_JOURNAL);		अवरोध;
		हाल 0x191: map_key_clear(KEY_FIन_अंकCE);		अवरोध;
		हाल 0x192: map_key_clear(KEY_CALC);		अवरोध;
		हाल 0x193: map_key_clear(KEY_PLAYER);		अवरोध;
		हाल 0x194: map_key_clear(KEY_खाता);		अवरोध;
		हाल 0x196: map_key_clear(KEY_WWW);		अवरोध;
		हाल 0x199: map_key_clear(KEY_CHAT);		अवरोध;
		हाल 0x19c: map_key_clear(KEY_LOGOFF);		अवरोध;
		हाल 0x19e: map_key_clear(KEY_COFFEE);		अवरोध;
		हाल 0x19f: map_key_clear(KEY_CONTROLPANEL);		अवरोध;
		हाल 0x1a2: map_key_clear(KEY_APPSELECT);		अवरोध;
		हाल 0x1a3: map_key_clear(KEY_NEXT);		अवरोध;
		हाल 0x1a4: map_key_clear(KEY_PREVIOUS);	अवरोध;
		हाल 0x1a6: map_key_clear(KEY_HELP);		अवरोध;
		हाल 0x1a7: map_key_clear(KEY_DOCUMENTS);	अवरोध;
		हाल 0x1ab: map_key_clear(KEY_SPELLCHECK);	अवरोध;
		हाल 0x1ae: map_key_clear(KEY_KEYBOARD);	अवरोध;
		हाल 0x1b1: map_key_clear(KEY_SCREENSAVER);		अवरोध;
		हाल 0x1b4: map_key_clear(KEY_खाता);		अवरोध;
		हाल 0x1b6: map_key_clear(KEY_IMAGES);		अवरोध;
		हाल 0x1b7: map_key_clear(KEY_AUDIO);		अवरोध;
		हाल 0x1b8: map_key_clear(KEY_VIDEO);		अवरोध;
		हाल 0x1bc: map_key_clear(KEY_MESSENGER);	अवरोध;
		हाल 0x1bd: map_key_clear(KEY_INFO);		अवरोध;
		हाल 0x1cb: map_key_clear(KEY_ASSISTANT);	अवरोध;
		हाल 0x201: map_key_clear(KEY_NEW);		अवरोध;
		हाल 0x202: map_key_clear(KEY_OPEN);		अवरोध;
		हाल 0x203: map_key_clear(KEY_CLOSE);		अवरोध;
		हाल 0x204: map_key_clear(KEY_EXIT);		अवरोध;
		हाल 0x207: map_key_clear(KEY_SAVE);		अवरोध;
		हाल 0x208: map_key_clear(KEY_PRINT);		अवरोध;
		हाल 0x209: map_key_clear(KEY_PROPS);		अवरोध;
		हाल 0x21a: map_key_clear(KEY_UNDO);		अवरोध;
		हाल 0x21b: map_key_clear(KEY_COPY);		अवरोध;
		हाल 0x21c: map_key_clear(KEY_CUT);		अवरोध;
		हाल 0x21d: map_key_clear(KEY_PASTE);		अवरोध;
		हाल 0x21f: map_key_clear(KEY_FIND);		अवरोध;
		हाल 0x221: map_key_clear(KEY_SEARCH);		अवरोध;
		हाल 0x222: map_key_clear(KEY_GOTO);		अवरोध;
		हाल 0x223: map_key_clear(KEY_HOMEPAGE);	अवरोध;
		हाल 0x224: map_key_clear(KEY_BACK);		अवरोध;
		हाल 0x225: map_key_clear(KEY_FORWARD);		अवरोध;
		हाल 0x226: map_key_clear(KEY_STOP);		अवरोध;
		हाल 0x227: map_key_clear(KEY_REFRESH);		अवरोध;
		हाल 0x22a: map_key_clear(KEY_BOOKMARKS);	अवरोध;
		हाल 0x22d: map_key_clear(KEY_ZOOMIN);		अवरोध;
		हाल 0x22e: map_key_clear(KEY_ZOOMOUT);		अवरोध;
		हाल 0x22f: map_key_clear(KEY_ZOOMRESET);	अवरोध;
		हाल 0x232: map_key_clear(KEY_FULL_SCREEN);	अवरोध;
		हाल 0x233: map_key_clear(KEY_SCROLLUP);	अवरोध;
		हाल 0x234: map_key_clear(KEY_SCROLLDOWN);	अवरोध;
		हाल 0x238: /* AC Pan */
			set_bit(REL_HWHEEL, input->relbit);
			map_rel(REL_HWHEEL_HI_RES);
			अवरोध;
		हाल 0x23d: map_key_clear(KEY_EDIT);		अवरोध;
		हाल 0x25f: map_key_clear(KEY_CANCEL);		अवरोध;
		हाल 0x269: map_key_clear(KEY_INSERT);		अवरोध;
		हाल 0x26a: map_key_clear(KEY_DELETE);		अवरोध;
		हाल 0x279: map_key_clear(KEY_REDO);		अवरोध;

		हाल 0x289: map_key_clear(KEY_REPLY);		अवरोध;
		हाल 0x28b: map_key_clear(KEY_FORWARDMAIL);	अवरोध;
		हाल 0x28c: map_key_clear(KEY_SEND);		अवरोध;

		हाल 0x29d: map_key_clear(KEY_KBD_LAYOUT_NEXT);	अवरोध;

		हाल 0x2c7: map_key_clear(KEY_KBDINPUTASSIST_PREV);		अवरोध;
		हाल 0x2c8: map_key_clear(KEY_KBDINPUTASSIST_NEXT);		अवरोध;
		हाल 0x2c9: map_key_clear(KEY_KBDINPUTASSIST_PREVGROUP);		अवरोध;
		हाल 0x2ca: map_key_clear(KEY_KBDINPUTASSIST_NEXTGROUP);		अवरोध;
		हाल 0x2cb: map_key_clear(KEY_KBDINPUTASSIST_ACCEPT);	अवरोध;
		हाल 0x2cc: map_key_clear(KEY_KBDINPUTASSIST_CANCEL);	अवरोध;

		हाल 0x29f: map_key_clear(KEY_SCALE);		अवरोध;

		शेष: map_key_clear(KEY_UNKNOWN);
		पूर्ण
		अवरोध;

	हाल HID_UP_GENDEVCTRLS:
		चयन (usage->hid) अणु
		हाल HID_DC_BATTERYSTRENGTH:
			hidinput_setup_battery(device, HID_INPUT_REPORT, field, false);
			usage->type = EV_PWR;
			वापस;
		पूर्ण
		जाओ unknown;

	हाल HID_UP_BATTERY:
		चयन (usage->hid) अणु
		हाल HID_BAT_ABSOLUTESTATखातापूर्णCHARGE:
			hidinput_setup_battery(device, HID_INPUT_REPORT, field, true);
			usage->type = EV_PWR;
			वापस;
		पूर्ण
		जाओ unknown;

	हाल HID_UP_HPVENDOR:	/* Reported on a Dutch layout HP5308 */
		set_bit(EV_REP, input->evbit);
		चयन (usage->hid & HID_USAGE) अणु
		हाल 0x021: map_key_clear(KEY_PRINT);           अवरोध;
		हाल 0x070: map_key_clear(KEY_HP);		अवरोध;
		हाल 0x071: map_key_clear(KEY_CAMERA);		अवरोध;
		हाल 0x072: map_key_clear(KEY_SOUND);		अवरोध;
		हाल 0x073: map_key_clear(KEY_QUESTION);	अवरोध;
		हाल 0x080: map_key_clear(KEY_EMAIL);		अवरोध;
		हाल 0x081: map_key_clear(KEY_CHAT);		अवरोध;
		हाल 0x082: map_key_clear(KEY_SEARCH);		अवरोध;
		हाल 0x083: map_key_clear(KEY_CONNECT);	        अवरोध;
		हाल 0x084: map_key_clear(KEY_FIन_अंकCE);		अवरोध;
		हाल 0x085: map_key_clear(KEY_SPORT);		अवरोध;
		हाल 0x086: map_key_clear(KEY_SHOP);	        अवरोध;
		शेष:    जाओ ignore;
		पूर्ण
		अवरोध;

	हाल HID_UP_HPVENDOR2:
		set_bit(EV_REP, input->evbit);
		चयन (usage->hid & HID_USAGE) अणु
		हाल 0x001: map_key_clear(KEY_MICMUTE);		अवरोध;
		हाल 0x003: map_key_clear(KEY_BRIGHTNESSDOWN);	अवरोध;
		हाल 0x004: map_key_clear(KEY_BRIGHTNESSUP);	अवरोध;
		शेष:    जाओ ignore;
		पूर्ण
		अवरोध;

	हाल HID_UP_MSVENDOR:
		जाओ ignore;

	हाल HID_UP_CUSTOM: /* Reported on Logitech and Apple USB keyboards */
		set_bit(EV_REP, input->evbit);
		जाओ ignore;

	हाल HID_UP_LOGIVENDOR:
		/* पूर्णांकentional fallback */
	हाल HID_UP_LOGIVENDOR2:
		/* पूर्णांकentional fallback */
	हाल HID_UP_LOGIVENDOR3:
		जाओ ignore;

	हाल HID_UP_PID:
		चयन (usage->hid & HID_USAGE) अणु
		हाल 0xa4: map_key_clear(BTN_DEAD);	अवरोध;
		शेष: जाओ ignore;
		पूर्ण
		अवरोध;

	शेष:
	unknown:
		अगर (field->report_size == 1) अणु
			अगर (field->report->type == HID_OUTPUT_REPORT) अणु
				map_led(LED_MISC);
				अवरोध;
			पूर्ण
			map_key(BTN_MISC);
			अवरोध;
		पूर्ण
		अगर (field->flags & HID_MAIN_ITEM_RELATIVE) अणु
			map_rel(REL_MISC);
			अवरोध;
		पूर्ण
		map_असल(ABS_MISC);
		अवरोध;
	पूर्ण

mapped:
	/* Mapping failed, bail out */
	अगर (!bit)
		वापस;

	अगर (device->driver->input_mapped &&
	    device->driver->input_mapped(device, hidinput, field, usage,
					 &bit, &max) < 0) अणु
		/*
		 * The driver indicated that no further generic handling
		 * of the usage is desired.
		 */
		वापस;
	पूर्ण

	set_bit(usage->type, input->evbit);

	/*
	 * This part is *really* controversial:
	 * - HID aims at being generic so we should करो our best to export
	 *   all incoming events
	 * - HID describes what events are, so there is no reason क्रम ABS_X
	 *   to be mapped to ABS_Y
	 * - HID is using *_MISC+N as a शेष value, but nothing prevents
	 *   *_MISC+N to overग_लिखो a legitimate even, which confuses userspace
	 *   (क्रम instance ABS_MISC + 7 is ABS_MT_SLOT, which has a dअगरferent
	 *   processing)
	 *
	 * If devices still want to use this (at their own risk), they will
	 * have to use the quirk HID_QUIRK_INCREMENT_USAGE_ON_DUPLICATE, but
	 * the शेष should be a reliable mapping.
	 */
	जबतक (usage->code <= max && test_and_set_bit(usage->code, bit)) अणु
		अगर (device->quirks & HID_QUIRK_INCREMENT_USAGE_ON_DUPLICATE) अणु
			usage->code = find_next_zero_bit(bit,
							 max + 1,
							 usage->code);
		पूर्ण अन्यथा अणु
			device->status |= HID_STAT_DUP_DETECTED;
			जाओ ignore;
		पूर्ण
	पूर्ण

	अगर (usage->code > max)
		जाओ ignore;

	अगर (usage->type == EV_ABS) अणु

		पूर्णांक a = field->logical_minimum;
		पूर्णांक b = field->logical_maximum;

		अगर ((device->quirks & HID_QUIRK_BADPAD) && (usage->code == ABS_X || usage->code == ABS_Y)) अणु
			a = field->logical_minimum = 0;
			b = field->logical_maximum = 255;
		पूर्ण

		अगर (field->application == HID_GD_GAMEPAD || field->application == HID_GD_JOYSTICK)
			input_set_असल_params(input, usage->code, a, b, (b - a) >> 8, (b - a) >> 4);
		अन्यथा	input_set_असल_params(input, usage->code, a, b, 0, 0);

		input_असल_set_res(input, usage->code,
				  hidinput_calc_असल_res(field, usage->code));

		/* use a larger शेष input buffer क्रम MT devices */
		अगर (usage->code == ABS_MT_POSITION_X && input->hपूर्णांक_events_per_packet == 0)
			input_set_events_per_packet(input, 60);
	पूर्ण

	अगर (usage->type == EV_ABS &&
	    (usage->hat_min < usage->hat_max || usage->hat_dir)) अणु
		पूर्णांक i;
		क्रम (i = usage->code; i < usage->code + 2 && i <= max; i++) अणु
			input_set_असल_params(input, i, -1, 1, 0, 0);
			set_bit(i, input->असलbit);
		पूर्ण
		अगर (usage->hat_dir && !field->dpad)
			field->dpad = usage->code;
	पूर्ण

	/* क्रम those devices which produce Consumer volume usage as relative,
	 * we emulate pressing volumeup/volumeकरोwn appropriate number of बार
	 * in hidinput_hid_event()
	 */
	अगर ((usage->type == EV_ABS) && (field->flags & HID_MAIN_ITEM_RELATIVE) &&
			(usage->code == ABS_VOLUME)) अणु
		set_bit(KEY_VOLUMEUP, input->keybit);
		set_bit(KEY_VOLUMEDOWN, input->keybit);
	पूर्ण

	अगर (usage->type == EV_KEY) अणु
		set_bit(EV_MSC, input->evbit);
		set_bit(MSC_SCAN, input->mscbit);
	पूर्ण

	वापस;

ignore:
	usage->type = 0;
	usage->code = 0;
पूर्ण

अटल व्योम hidinput_handle_scroll(काष्ठा hid_usage *usage,
				   काष्ठा input_dev *input,
				   __s32 value)
अणु
	पूर्णांक code;
	पूर्णांक hi_res, lo_res;

	अगर (value == 0)
		वापस;

	अगर (usage->code == REL_WHEEL_HI_RES)
		code = REL_WHEEL;
	अन्यथा
		code = REL_HWHEEL;

	/*
	 * Winकरोws reports one wheel click as value 120. Where a high-res
	 * scroll wheel is present, a fraction of 120 is reported instead.
	 * Our REL_WHEEL_HI_RES axis करोes the same because all HW must
	 * adhere to the 120 expectation.
	 */
	hi_res = value * 120/usage->resolution_multiplier;

	usage->wheel_accumulated += hi_res;
	lo_res = usage->wheel_accumulated/120;
	अगर (lo_res)
		usage->wheel_accumulated -= lo_res * 120;

	input_event(input, EV_REL, code, lo_res);
	input_event(input, EV_REL, usage->code, hi_res);
पूर्ण

व्योम hidinput_hid_event(काष्ठा hid_device *hid, काष्ठा hid_field *field, काष्ठा hid_usage *usage, __s32 value)
अणु
	काष्ठा input_dev *input;
	अचिन्हित *quirks = &hid->quirks;

	अगर (!usage->type)
		वापस;

	अगर (usage->type == EV_PWR) अणु
		hidinput_update_battery(hid, value);
		वापस;
	पूर्ण

	अगर (!field->hidinput)
		वापस;

	input = field->hidinput->input;

	अगर (usage->hat_min < usage->hat_max || usage->hat_dir) अणु
		पूर्णांक hat_dir = usage->hat_dir;
		अगर (!hat_dir)
			hat_dir = (value - usage->hat_min) * 8 / (usage->hat_max - usage->hat_min + 1) + 1;
		अगर (hat_dir < 0 || hat_dir > 8) hat_dir = 0;
		input_event(input, usage->type, usage->code    , hid_hat_to_axis[hat_dir].x);
		input_event(input, usage->type, usage->code + 1, hid_hat_to_axis[hat_dir].y);
		वापस;
	पूर्ण

	अगर (usage->hid == (HID_UP_DIGITIZER | 0x003c)) अणु /* Invert */
		*quirks = value ? (*quirks | HID_QUIRK_INVERT) : (*quirks & ~HID_QUIRK_INVERT);
		वापस;
	पूर्ण

	अगर (usage->hid == (HID_UP_DIGITIZER | 0x0032)) अणु /* InRange */
		अगर (value) अणु
			input_event(input, usage->type, (*quirks & HID_QUIRK_INVERT) ? BTN_TOOL_RUBBER : usage->code, 1);
			वापस;
		पूर्ण
		input_event(input, usage->type, usage->code, 0);
		input_event(input, usage->type, BTN_TOOL_RUBBER, 0);
		वापस;
	पूर्ण

	अगर (usage->hid == (HID_UP_DIGITIZER | 0x0030) && (*quirks & HID_QUIRK_NOTOUCH)) अणु /* Pressure */
		पूर्णांक a = field->logical_minimum;
		पूर्णांक b = field->logical_maximum;
		input_event(input, EV_KEY, BTN_TOUCH, value > a + ((b - a) >> 3));
	पूर्ण

	अगर (usage->hid == (HID_UP_PID | 0x83UL)) अणु /* Simultaneous Effects Max */
		dbg_hid("Maximum Effects - %d\n",value);
		वापस;
	पूर्ण

	अगर (usage->hid == (HID_UP_PID | 0x7fUL)) अणु
		dbg_hid("PID Pool Report\n");
		वापस;
	पूर्ण

	अगर ((usage->type == EV_KEY) && (usage->code == 0)) /* Key 0 is "unassigned", not KEY_UNKNOWN */
		वापस;

	अगर ((usage->type == EV_REL) && (usage->code == REL_WHEEL_HI_RES ||
					usage->code == REL_HWHEEL_HI_RES)) अणु
		hidinput_handle_scroll(usage, input, value);
		वापस;
	पूर्ण

	अगर ((usage->type == EV_ABS) && (field->flags & HID_MAIN_ITEM_RELATIVE) &&
			(usage->code == ABS_VOLUME)) अणु
		पूर्णांक count = असल(value);
		पूर्णांक direction = value > 0 ? KEY_VOLUMEUP : KEY_VOLUMEDOWN;
		पूर्णांक i;

		क्रम (i = 0; i < count; i++) अणु
			input_event(input, EV_KEY, direction, 1);
			input_sync(input);
			input_event(input, EV_KEY, direction, 0);
			input_sync(input);
		पूर्ण
		वापस;
	पूर्ण

	/*
	 * Ignore out-of-range values as per HID specअगरication,
	 * section 5.10 and 6.2.25, when शून्य state bit is present.
	 * When it's not, clamp the value to match Microsoft's input
	 * driver as mentioned in "Required HID usages for digitizers":
	 * https://msdn.microsoft.com/en-us/library/winकरोws/hardware/dn672278(v=vs.85).asp
	 *
	 * The logical_minimum < logical_maximum check is करोne so that we
	 * करोn't unपूर्णांकentionally discard values sent by devices which
	 * करोn't specअगरy logical min and max.
	 */
	अगर ((field->flags & HID_MAIN_ITEM_VARIABLE) &&
	    (field->logical_minimum < field->logical_maximum)) अणु
		अगर (field->flags & HID_MAIN_ITEM_शून्य_STATE &&
		    (value < field->logical_minimum ||
		     value > field->logical_maximum)) अणु
			dbg_hid("Ignoring out-of-range value %x\n", value);
			वापस;
		पूर्ण
		value = clamp(value,
			      field->logical_minimum,
			      field->logical_maximum);
	पूर्ण

	/*
	 * Ignore reports क्रम असलolute data अगर the data didn't change. This is
	 * not only an optimization but also fixes 'dead' key reports. Some
	 * RollOver implementations क्रम localized keys (like BACKSLASH/PIPE; HID
	 * 0x31 and 0x32) report multiple keys, even though a localized keyboard
	 * can only have one of them physically available. The 'dead' keys
	 * report स्थिरant 0. As all map to the same keycode, they'd confuse
	 * the input layer. If we filter the 'dead' keys on the HID level, we
	 * skip the keycode translation and only क्रमward real events.
	 */
	अगर (!(field->flags & (HID_MAIN_ITEM_RELATIVE |
	                      HID_MAIN_ITEM_BUFFERED_BYTE)) &&
			      (field->flags & HID_MAIN_ITEM_VARIABLE) &&
	    usage->usage_index < field->maxusage &&
	    value == field->value[usage->usage_index])
		वापस;

	/* report the usage code as scancode अगर the key status has changed */
	अगर (usage->type == EV_KEY &&
	    (!test_bit(usage->code, input->key)) == value)
		input_event(input, EV_MSC, MSC_SCAN, usage->hid);

	input_event(input, usage->type, usage->code, value);

	अगर ((field->flags & HID_MAIN_ITEM_RELATIVE) &&
	    usage->type == EV_KEY && value) अणु
		input_sync(input);
		input_event(input, usage->type, usage->code, 0);
	पूर्ण
पूर्ण

व्योम hidinput_report_event(काष्ठा hid_device *hid, काष्ठा hid_report *report)
अणु
	काष्ठा hid_input *hidinput;

	अगर (hid->quirks & HID_QUIRK_NO_INPUT_SYNC)
		वापस;

	list_क्रम_each_entry(hidinput, &hid->inमाला_दो, list)
		input_sync(hidinput->input);
पूर्ण
EXPORT_SYMBOL_GPL(hidinput_report_event);

पूर्णांक hidinput_find_field(काष्ठा hid_device *hid, अचिन्हित पूर्णांक type, अचिन्हित पूर्णांक code, काष्ठा hid_field **field)
अणु
	काष्ठा hid_report *report;
	पूर्णांक i, j;

	list_क्रम_each_entry(report, &hid->report_क्रमागत[HID_OUTPUT_REPORT].report_list, list) अणु
		क्रम (i = 0; i < report->maxfield; i++) अणु
			*field = report->field[i];
			क्रम (j = 0; j < (*field)->maxusage; j++)
				अगर ((*field)->usage[j].type == type && (*field)->usage[j].code == code)
					वापस j;
		पूर्ण
	पूर्ण
	वापस -1;
पूर्ण
EXPORT_SYMBOL_GPL(hidinput_find_field);

काष्ठा hid_field *hidinput_get_led_field(काष्ठा hid_device *hid)
अणु
	काष्ठा hid_report *report;
	काष्ठा hid_field *field;
	पूर्णांक i, j;

	list_क्रम_each_entry(report,
			    &hid->report_क्रमागत[HID_OUTPUT_REPORT].report_list,
			    list) अणु
		क्रम (i = 0; i < report->maxfield; i++) अणु
			field = report->field[i];
			क्रम (j = 0; j < field->maxusage; j++)
				अगर (field->usage[j].type == EV_LED)
					वापस field;
		पूर्ण
	पूर्ण
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(hidinput_get_led_field);

अचिन्हित पूर्णांक hidinput_count_leds(काष्ठा hid_device *hid)
अणु
	काष्ठा hid_report *report;
	काष्ठा hid_field *field;
	पूर्णांक i, j;
	अचिन्हित पूर्णांक count = 0;

	list_क्रम_each_entry(report,
			    &hid->report_क्रमागत[HID_OUTPUT_REPORT].report_list,
			    list) अणु
		क्रम (i = 0; i < report->maxfield; i++) अणु
			field = report->field[i];
			क्रम (j = 0; j < field->maxusage; j++)
				अगर (field->usage[j].type == EV_LED &&
				    field->value[j])
					count += 1;
		पूर्ण
	पूर्ण
	वापस count;
पूर्ण
EXPORT_SYMBOL_GPL(hidinput_count_leds);

अटल व्योम hidinput_led_worker(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा hid_device *hid = container_of(work, काष्ठा hid_device,
					      led_work);
	काष्ठा hid_field *field;
	काष्ठा hid_report *report;
	पूर्णांक ret;
	u32 len;
	__u8 *buf;

	field = hidinput_get_led_field(hid);
	अगर (!field)
		वापस;

	/*
	 * field->report is accessed unlocked regarding HID core. So there might
	 * be another incoming SET-LED request from user-space, which changes
	 * the LED state जबतक we assemble our outgoing buffer. However, this
	 * करोesn't matter as hid_output_report() correctly converts it पूर्णांकo a
	 * boolean value no matter what inक्रमmation is currently set on the LED
	 * field (even garbage). So the remote device will always get a valid
	 * request.
	 * And in हाल we send a wrong value, a next led worker is spawned
	 * क्रम every SET-LED request so the following worker will send the
	 * correct value, guaranteed!
	 */

	report = field->report;

	/* use custom SET_REPORT request अगर possible (asynchronous) */
	अगर (hid->ll_driver->request)
		वापस hid->ll_driver->request(hid, report, HID_REQ_SET_REPORT);

	/* fall back to generic raw-output-report */
	len = hid_report_len(report);
	buf = hid_alloc_report_buf(report, GFP_KERNEL);
	अगर (!buf)
		वापस;

	hid_output_report(report, buf);
	/* synchronous output report */
	ret = hid_hw_output_report(hid, buf, len);
	अगर (ret == -ENOSYS)
		hid_hw_raw_request(hid, report->id, buf, len, HID_OUTPUT_REPORT,
				HID_REQ_SET_REPORT);
	kमुक्त(buf);
पूर्ण

अटल पूर्णांक hidinput_input_event(काष्ठा input_dev *dev, अचिन्हित पूर्णांक type,
				अचिन्हित पूर्णांक code, पूर्णांक value)
अणु
	काष्ठा hid_device *hid = input_get_drvdata(dev);
	काष्ठा hid_field *field;
	पूर्णांक offset;

	अगर (type == EV_FF)
		वापस input_ff_event(dev, type, code, value);

	अगर (type != EV_LED)
		वापस -1;

	अगर ((offset = hidinput_find_field(hid, type, code, &field)) == -1) अणु
		hid_warn(dev, "event field not found\n");
		वापस -1;
	पूर्ण

	hid_set_field(field, offset, value);

	schedule_work(&hid->led_work);
	वापस 0;
पूर्ण

अटल पूर्णांक hidinput_खोलो(काष्ठा input_dev *dev)
अणु
	काष्ठा hid_device *hid = input_get_drvdata(dev);

	वापस hid_hw_खोलो(hid);
पूर्ण

अटल व्योम hidinput_बंद(काष्ठा input_dev *dev)
अणु
	काष्ठा hid_device *hid = input_get_drvdata(dev);

	hid_hw_बंद(hid);
पूर्ण

अटल bool __hidinput_change_resolution_multipliers(काष्ठा hid_device *hid,
		काष्ठा hid_report *report, bool use_logical_max)
अणु
	काष्ठा hid_usage *usage;
	bool update_needed = false;
	bool get_report_completed = false;
	पूर्णांक i, j;

	अगर (report->maxfield == 0)
		वापस false;

	क्रम (i = 0; i < report->maxfield; i++) अणु
		__s32 value = use_logical_max ?
			      report->field[i]->logical_maximum :
			      report->field[i]->logical_minimum;

		/* There is no good reason क्रम a Resolution
		 * Multiplier to have a count other than 1.
		 * Ignore that हाल.
		 */
		अगर (report->field[i]->report_count != 1)
			जारी;

		क्रम (j = 0; j < report->field[i]->maxusage; j++) अणु
			usage = &report->field[i]->usage[j];

			अगर (usage->hid != HID_GD_RESOLUTION_MULTIPLIER)
				जारी;

			/*
			 * If we have more than one feature within this
			 * report we need to fill in the bits from the
			 * others beक्रमe we can overग_लिखो the ones क्रम the
			 * Resolution Multiplier.
			 *
			 * But अगर we're not allowed to पढ़ो from the device,
			 * we just bail. Such a device should not exist
			 * anyway.
			 */
			अगर (!get_report_completed && report->maxfield > 1) अणु
				अगर (hid->quirks & HID_QUIRK_NO_INIT_REPORTS)
					वापस update_needed;

				hid_hw_request(hid, report, HID_REQ_GET_REPORT);
				hid_hw_रुको(hid);
				get_report_completed = true;
			पूर्ण

			report->field[i]->value[j] = value;
			update_needed = true;
		पूर्ण
	पूर्ण

	वापस update_needed;
पूर्ण

अटल व्योम hidinput_change_resolution_multipliers(काष्ठा hid_device *hid)
अणु
	काष्ठा hid_report_क्रमागत *rep_क्रमागत;
	काष्ठा hid_report *rep;
	पूर्णांक ret;

	rep_क्रमागत = &hid->report_क्रमागत[HID_FEATURE_REPORT];
	list_क्रम_each_entry(rep, &rep_क्रमागत->report_list, list) अणु
		bool update_needed = __hidinput_change_resolution_multipliers(hid,
								     rep, true);

		अगर (update_needed) अणु
			ret = __hid_request(hid, rep, HID_REQ_SET_REPORT);
			अगर (ret) अणु
				__hidinput_change_resolution_multipliers(hid,
								    rep, false);
				वापस;
			पूर्ण
		पूर्ण
	पूर्ण

	/* refresh our काष्ठाs */
	hid_setup_resolution_multiplier(hid);
पूर्ण

अटल व्योम report_features(काष्ठा hid_device *hid)
अणु
	काष्ठा hid_driver *drv = hid->driver;
	काष्ठा hid_report_क्रमागत *rep_क्रमागत;
	काष्ठा hid_report *rep;
	काष्ठा hid_usage *usage;
	पूर्णांक i, j;

	rep_क्रमागत = &hid->report_क्रमागत[HID_FEATURE_REPORT];
	list_क्रम_each_entry(rep, &rep_क्रमागत->report_list, list)
		क्रम (i = 0; i < rep->maxfield; i++) अणु
			/* Ignore अगर report count is out of bounds. */
			अगर (rep->field[i]->report_count < 1)
				जारी;

			क्रम (j = 0; j < rep->field[i]->maxusage; j++) अणु
				usage = &rep->field[i]->usage[j];

				/* Verअगरy अगर Battery Strength feature is available */
				अगर (usage->hid == HID_DC_BATTERYSTRENGTH)
					hidinput_setup_battery(hid, HID_FEATURE_REPORT,
							       rep->field[i], false);

				अगर (drv->feature_mapping)
					drv->feature_mapping(hid, rep->field[i], usage);
			पूर्ण
		पूर्ण
पूर्ण

अटल काष्ठा hid_input *hidinput_allocate(काष्ठा hid_device *hid,
					   अचिन्हित पूर्णांक application)
अणु
	काष्ठा hid_input *hidinput = kzalloc(माप(*hidinput), GFP_KERNEL);
	काष्ठा input_dev *input_dev = input_allocate_device();
	स्थिर अक्षर *suffix = शून्य;
	माप_प्रकार suffix_len, name_len;

	अगर (!hidinput || !input_dev)
		जाओ fail;

	अगर ((hid->quirks & HID_QUIRK_INPUT_PER_APP) &&
	    hid->maxapplication > 1) अणु
		चयन (application) अणु
		हाल HID_GD_KEYBOARD:
			suffix = "Keyboard";
			अवरोध;
		हाल HID_GD_KEYPAD:
			suffix = "Keypad";
			अवरोध;
		हाल HID_GD_MOUSE:
			suffix = "Mouse";
			अवरोध;
		हाल HID_DG_STYLUS:
			suffix = "Pen";
			अवरोध;
		हाल HID_DG_TOUCHSCREEN:
			suffix = "Touchscreen";
			अवरोध;
		हाल HID_DG_TOUCHPAD:
			suffix = "Touchpad";
			अवरोध;
		हाल HID_GD_SYSTEM_CONTROL:
			suffix = "System Control";
			अवरोध;
		हाल HID_CP_CONSUMER_CONTROL:
			suffix = "Consumer Control";
			अवरोध;
		हाल HID_GD_WIRELESS_RADIO_CTLS:
			suffix = "Wireless Radio Control";
			अवरोध;
		हाल HID_GD_SYSTEM_MULTIAXIS:
			suffix = "System Multi Axis";
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (suffix) अणु
		name_len = म_माप(hid->name);
		suffix_len = म_माप(suffix);
		अगर ((name_len < suffix_len) ||
		    म_भेद(hid->name + name_len - suffix_len, suffix)) अणु
			hidinput->name = kaप्र_लिखो(GFP_KERNEL, "%s %s",
						   hid->name, suffix);
			अगर (!hidinput->name)
				जाओ fail;
		पूर्ण
	पूर्ण

	input_set_drvdata(input_dev, hid);
	input_dev->event = hidinput_input_event;
	input_dev->खोलो = hidinput_खोलो;
	input_dev->बंद = hidinput_बंद;
	input_dev->setkeycode = hidinput_setkeycode;
	input_dev->getkeycode = hidinput_getkeycode;

	input_dev->name = hidinput->name ? hidinput->name : hid->name;
	input_dev->phys = hid->phys;
	input_dev->uniq = hid->uniq;
	input_dev->id.bustype = hid->bus;
	input_dev->id.venकरोr  = hid->venकरोr;
	input_dev->id.product = hid->product;
	input_dev->id.version = hid->version;
	input_dev->dev.parent = &hid->dev;

	hidinput->input = input_dev;
	hidinput->application = application;
	list_add_tail(&hidinput->list, &hid->inमाला_दो);

	INIT_LIST_HEAD(&hidinput->reports);

	वापस hidinput;

fail:
	kमुक्त(hidinput);
	input_मुक्त_device(input_dev);
	hid_err(hid, "Out of memory during hid input probe\n");
	वापस शून्य;
पूर्ण

अटल bool hidinput_has_been_populated(काष्ठा hid_input *hidinput)
अणु
	पूर्णांक i;
	अचिन्हित दीर्घ r = 0;

	क्रम (i = 0; i < BITS_TO_LONGS(EV_CNT); i++)
		r |= hidinput->input->evbit[i];

	क्रम (i = 0; i < BITS_TO_LONGS(KEY_CNT); i++)
		r |= hidinput->input->keybit[i];

	क्रम (i = 0; i < BITS_TO_LONGS(REL_CNT); i++)
		r |= hidinput->input->relbit[i];

	क्रम (i = 0; i < BITS_TO_LONGS(ABS_CNT); i++)
		r |= hidinput->input->असलbit[i];

	क्रम (i = 0; i < BITS_TO_LONGS(MSC_CNT); i++)
		r |= hidinput->input->mscbit[i];

	क्रम (i = 0; i < BITS_TO_LONGS(LED_CNT); i++)
		r |= hidinput->input->ledbit[i];

	क्रम (i = 0; i < BITS_TO_LONGS(SND_CNT); i++)
		r |= hidinput->input->sndbit[i];

	क्रम (i = 0; i < BITS_TO_LONGS(FF_CNT); i++)
		r |= hidinput->input->ffbit[i];

	क्रम (i = 0; i < BITS_TO_LONGS(SW_CNT); i++)
		r |= hidinput->input->swbit[i];

	वापस !!r;
पूर्ण

अटल व्योम hidinput_cleanup_hidinput(काष्ठा hid_device *hid,
		काष्ठा hid_input *hidinput)
अणु
	काष्ठा hid_report *report;
	पूर्णांक i, k;

	list_del(&hidinput->list);
	input_मुक्त_device(hidinput->input);
	kमुक्त(hidinput->name);

	क्रम (k = HID_INPUT_REPORT; k <= HID_OUTPUT_REPORT; k++) अणु
		अगर (k == HID_OUTPUT_REPORT &&
			hid->quirks & HID_QUIRK_SKIP_OUTPUT_REPORTS)
			जारी;

		list_क्रम_each_entry(report, &hid->report_क्रमागत[k].report_list,
				    list) अणु

			क्रम (i = 0; i < report->maxfield; i++)
				अगर (report->field[i]->hidinput == hidinput)
					report->field[i]->hidinput = शून्य;
		पूर्ण
	पूर्ण

	kमुक्त(hidinput);
पूर्ण

अटल काष्ठा hid_input *hidinput_match(काष्ठा hid_report *report)
अणु
	काष्ठा hid_device *hid = report->device;
	काष्ठा hid_input *hidinput;

	list_क्रम_each_entry(hidinput, &hid->inमाला_दो, list) अणु
		अगर (hidinput->report &&
		    hidinput->report->id == report->id)
			वापस hidinput;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल काष्ठा hid_input *hidinput_match_application(काष्ठा hid_report *report)
अणु
	काष्ठा hid_device *hid = report->device;
	काष्ठा hid_input *hidinput;

	list_क्रम_each_entry(hidinput, &hid->inमाला_दो, list) अणु
		अगर (hidinput->application == report->application)
			वापस hidinput;

		/*
		 * Keep SystemControl and ConsumerControl applications together
		 * with the मुख्य keyboard, अगर present.
		 */
		अगर ((report->application == HID_GD_SYSTEM_CONTROL ||
		     report->application == HID_CP_CONSUMER_CONTROL) &&
		    hidinput->application == HID_GD_KEYBOARD) अणु
			वापस hidinput;
		पूर्ण
	पूर्ण

	वापस शून्य;
पूर्ण

अटल अंतरभूत व्योम hidinput_configure_usages(काष्ठा hid_input *hidinput,
					     काष्ठा hid_report *report)
अणु
	पूर्णांक i, j;

	क्रम (i = 0; i < report->maxfield; i++)
		क्रम (j = 0; j < report->field[i]->maxusage; j++)
			hidinput_configure_usage(hidinput, report->field[i],
						 report->field[i]->usage + j);
पूर्ण

/*
 * Register the input device; prपूर्णांक a message.
 * Configure the input layer पूर्णांकerface
 * Read all reports and initialize the असलolute field values.
 */

पूर्णांक hidinput_connect(काष्ठा hid_device *hid, अचिन्हित पूर्णांक क्रमce)
अणु
	काष्ठा hid_driver *drv = hid->driver;
	काष्ठा hid_report *report;
	काष्ठा hid_input *next, *hidinput = शून्य;
	अचिन्हित पूर्णांक application;
	पूर्णांक i, k;

	INIT_LIST_HEAD(&hid->inमाला_दो);
	INIT_WORK(&hid->led_work, hidinput_led_worker);

	hid->status &= ~HID_STAT_DUP_DETECTED;

	अगर (!क्रमce) अणु
		क्रम (i = 0; i < hid->maxcollection; i++) अणु
			काष्ठा hid_collection *col = &hid->collection[i];
			अगर (col->type == HID_COLLECTION_APPLICATION ||
					col->type == HID_COLLECTION_PHYSICAL)
				अगर (IS_INPUT_APPLICATION(col->usage))
					अवरोध;
		पूर्ण

		अगर (i == hid->maxcollection)
			वापस -1;
	पूर्ण

	report_features(hid);

	क्रम (k = HID_INPUT_REPORT; k <= HID_OUTPUT_REPORT; k++) अणु
		अगर (k == HID_OUTPUT_REPORT &&
			hid->quirks & HID_QUIRK_SKIP_OUTPUT_REPORTS)
			जारी;

		list_क्रम_each_entry(report, &hid->report_क्रमागत[k].report_list, list) अणु

			अगर (!report->maxfield)
				जारी;

			application = report->application;

			/*
			 * Find the previous hidinput report attached
			 * to this report id.
			 */
			अगर (hid->quirks & HID_QUIRK_MULTI_INPUT)
				hidinput = hidinput_match(report);
			अन्यथा अगर (hid->maxapplication > 1 &&
				 (hid->quirks & HID_QUIRK_INPUT_PER_APP))
				hidinput = hidinput_match_application(report);

			अगर (!hidinput) अणु
				hidinput = hidinput_allocate(hid, application);
				अगर (!hidinput)
					जाओ out_unwind;
			पूर्ण

			hidinput_configure_usages(hidinput, report);

			अगर (hid->quirks & HID_QUIRK_MULTI_INPUT)
				hidinput->report = report;

			list_add_tail(&report->hidinput_list,
				      &hidinput->reports);
		पूर्ण
	पूर्ण

	hidinput_change_resolution_multipliers(hid);

	list_क्रम_each_entry_safe(hidinput, next, &hid->inमाला_दो, list) अणु
		अगर (drv->input_configured &&
		    drv->input_configured(hid, hidinput))
			जाओ out_unwind;

		अगर (!hidinput_has_been_populated(hidinput)) अणु
			/* no need to रेजिस्टर an input device not populated */
			hidinput_cleanup_hidinput(hid, hidinput);
			जारी;
		पूर्ण

		अगर (input_रेजिस्टर_device(hidinput->input))
			जाओ out_unwind;
		hidinput->रेजिस्टरed = true;
	पूर्ण

	अगर (list_empty(&hid->inमाला_दो)) अणु
		hid_err(hid, "No inputs registered, leaving\n");
		जाओ out_unwind;
	पूर्ण

	अगर (hid->status & HID_STAT_DUP_DETECTED)
		hid_dbg(hid,
			"Some usages could not be mapped, please use HID_QUIRK_INCREMENT_USAGE_ON_DUPLICATE if this is legitimate.\n");

	वापस 0;

out_unwind:
	/* unwind the ones we alपढ़ोy रेजिस्टरed */
	hidinput_disconnect(hid);

	वापस -1;
पूर्ण
EXPORT_SYMBOL_GPL(hidinput_connect);

व्योम hidinput_disconnect(काष्ठा hid_device *hid)
अणु
	काष्ठा hid_input *hidinput, *next;

	hidinput_cleanup_battery(hid);

	list_क्रम_each_entry_safe(hidinput, next, &hid->inमाला_दो, list) अणु
		list_del(&hidinput->list);
		अगर (hidinput->रेजिस्टरed)
			input_unरेजिस्टर_device(hidinput->input);
		अन्यथा
			input_मुक्त_device(hidinput->input);
		kमुक्त(hidinput->name);
		kमुक्त(hidinput);
	पूर्ण

	/* led_work is spawned by input_dev callbacks, but करोesn't access the
	 * parent input_dev at all. Once all input devices are हटाओd, we
	 * know that led_work will never get restarted, so we can cancel it
	 * synchronously and are safe. */
	cancel_work_sync(&hid->led_work);
पूर्ण
EXPORT_SYMBOL_GPL(hidinput_disconnect);
