<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  HID driver क्रम Sony DualSense(TM) controller.
 *
 *  Copyright (c) 2020 Sony Interactive Entertainment
 */

#समावेश <linux/bits.h>
#समावेश <linux/crc32.h>
#समावेश <linux/device.h>
#समावेश <linux/hid.h>
#समावेश <linux/idr.h>
#समावेश <linux/input/mt.h>
#समावेश <linux/module.h>

#समावेश <यंत्र/unaligned.h>

#समावेश "hid-ids.h"

/* List of connected playstation devices. */
अटल DEFINE_MUTEX(ps_devices_lock);
अटल LIST_HEAD(ps_devices_list);

अटल DEFINE_IDA(ps_player_id_allocator);

#घोषणा HID_PLAYSTATION_VERSION_PATCH 0x8000

/* Base class क्रम playstation devices. */
काष्ठा ps_device अणु
	काष्ठा list_head list;
	काष्ठा hid_device *hdev;
	spinlock_t lock;

	uपूर्णांक32_t player_id;

	काष्ठा घातer_supply_desc battery_desc;
	काष्ठा घातer_supply *battery;
	uपूर्णांक8_t battery_capacity;
	पूर्णांक battery_status;

	uपूर्णांक8_t mac_address[6]; /* Note: stored in little endian order. */
	uपूर्णांक32_t hw_version;
	uपूर्णांक32_t fw_version;

	पूर्णांक (*parse_report)(काष्ठा ps_device *dev, काष्ठा hid_report *report, u8 *data, पूर्णांक size);
पूर्ण;

/* Calibration data क्रम playstation motion sensors. */
काष्ठा ps_calibration_data अणु
	पूर्णांक असल_code;
	लघु bias;
	पूर्णांक sens_numer;
	पूर्णांक sens_denom;
पूर्ण;

/* Seed values क्रम DualShock4 / DualSense CRC32 क्रम dअगरferent report types. */
#घोषणा PS_INPUT_CRC32_SEED	0xA1
#घोषणा PS_OUTPUT_CRC32_SEED	0xA2
#घोषणा PS_FEATURE_CRC32_SEED	0xA3

#घोषणा DS_INPUT_REPORT_USB			0x01
#घोषणा DS_INPUT_REPORT_USB_SIZE		64
#घोषणा DS_INPUT_REPORT_BT			0x31
#घोषणा DS_INPUT_REPORT_BT_SIZE			78
#घोषणा DS_OUTPUT_REPORT_USB			0x02
#घोषणा DS_OUTPUT_REPORT_USB_SIZE		63
#घोषणा DS_OUTPUT_REPORT_BT			0x31
#घोषणा DS_OUTPUT_REPORT_BT_SIZE		78

#घोषणा DS_FEATURE_REPORT_CALIBRATION		0x05
#घोषणा DS_FEATURE_REPORT_CALIBRATION_SIZE	41
#घोषणा DS_FEATURE_REPORT_PAIRING_INFO		0x09
#घोषणा DS_FEATURE_REPORT_PAIRING_INFO_SIZE	20
#घोषणा DS_FEATURE_REPORT_FIRMWARE_INFO		0x20
#घोषणा DS_FEATURE_REPORT_FIRMWARE_INFO_SIZE	64

/* Button masks क्रम DualSense input report. */
#घोषणा DS_BUTTONS0_HAT_SWITCH	GENMASK(3, 0)
#घोषणा DS_BUTTONS0_SQUARE	BIT(4)
#घोषणा DS_BUTTONS0_CROSS	BIT(5)
#घोषणा DS_BUTTONS0_CIRCLE	BIT(6)
#घोषणा DS_BUTTONS0_TRIANGLE	BIT(7)
#घोषणा DS_BUTTONS1_L1		BIT(0)
#घोषणा DS_BUTTONS1_R1		BIT(1)
#घोषणा DS_BUTTONS1_L2		BIT(2)
#घोषणा DS_BUTTONS1_R2		BIT(3)
#घोषणा DS_BUTTONS1_CREATE	BIT(4)
#घोषणा DS_BUTTONS1_OPTIONS	BIT(5)
#घोषणा DS_BUTTONS1_L3		BIT(6)
#घोषणा DS_BUTTONS1_R3		BIT(7)
#घोषणा DS_BUTTONS2_PS_HOME	BIT(0)
#घोषणा DS_BUTTONS2_TOUCHPAD	BIT(1)
#घोषणा DS_BUTTONS2_MIC_MUTE	BIT(2)

/* Status field of DualSense input report. */
#घोषणा DS_STATUS_BATTERY_CAPACITY	GENMASK(3, 0)
#घोषणा DS_STATUS_CHARGING		GENMASK(7, 4)
#घोषणा DS_STATUS_CHARGING_SHIFT	4

/*
 * Status of a DualSense touch poपूर्णांक contact.
 * Contact IDs, with highest bit set are 'inactive'
 * and any associated data is then invalid.
 */
#घोषणा DS_TOUCH_POINT_INACTIVE BIT(7)

 /* Magic value required in tag field of Bluetooth output report. */
#घोषणा DS_OUTPUT_TAG 0x10
/* Flags क्रम DualSense output report. */
#घोषणा DS_OUTPUT_VALID_FLAG0_COMPATIBLE_VIBRATION BIT(0)
#घोषणा DS_OUTPUT_VALID_FLAG0_HAPTICS_SELECT BIT(1)
#घोषणा DS_OUTPUT_VALID_FLAG1_MIC_MUTE_LED_CONTROL_ENABLE BIT(0)
#घोषणा DS_OUTPUT_VALID_FLAG1_POWER_SAVE_CONTROL_ENABLE BIT(1)
#घोषणा DS_OUTPUT_VALID_FLAG1_LIGHTBAR_CONTROL_ENABLE BIT(2)
#घोषणा DS_OUTPUT_VALID_FLAG1_RELEASE_LEDS BIT(3)
#घोषणा DS_OUTPUT_VALID_FLAG1_PLAYER_INDICATOR_CONTROL_ENABLE BIT(4)
#घोषणा DS_OUTPUT_VALID_FLAG2_LIGHTBAR_SETUP_CONTROL_ENABLE BIT(1)
#घोषणा DS_OUTPUT_POWER_SAVE_CONTROL_MIC_MUTE BIT(4)
#घोषणा DS_OUTPUT_LIGHTBAR_SETUP_LIGHT_OUT BIT(1)

/* DualSense hardware limits */
#घोषणा DS_ACC_RES_PER_G	8192
#घोषणा DS_ACC_RANGE		(4*DS_ACC_RES_PER_G)
#घोषणा DS_GYRO_RES_PER_DEG_S	1024
#घोषणा DS_GYRO_RANGE		(2048*DS_GYRO_RES_PER_DEG_S)
#घोषणा DS_TOUCHPAD_WIDTH	1920
#घोषणा DS_TOUCHPAD_HEIGHT	1080

काष्ठा dualsense अणु
	काष्ठा ps_device base;
	काष्ठा input_dev *gamepad;
	काष्ठा input_dev *sensors;
	काष्ठा input_dev *touchpad;

	/* Calibration data क्रम accelerometer and gyroscope. */
	काष्ठा ps_calibration_data accel_calib_data[3];
	काष्ठा ps_calibration_data gyro_calib_data[3];

	/* Timestamp क्रम sensor data */
	bool sensor_बारtamp_initialized;
	uपूर्णांक32_t prev_sensor_बारtamp;
	uपूर्णांक32_t sensor_बारtamp_us;

	/* Compatible rumble state */
	bool update_rumble;
	uपूर्णांक8_t motor_left;
	uपूर्णांक8_t motor_right;

	/* RGB lightbar */
	bool update_lightbar;
	uपूर्णांक8_t lightbar_red;
	uपूर्णांक8_t lightbar_green;
	uपूर्णांक8_t lightbar_blue;

	/* Microphone */
	bool update_mic_mute;
	bool mic_muted;
	bool last_btn_mic_state;

	/* Player leds */
	bool update_player_leds;
	uपूर्णांक8_t player_leds_state;
	काष्ठा led_classdev player_leds[5];

	काष्ठा work_काष्ठा output_worker;
	व्योम *output_report_dmabuf;
	uपूर्णांक8_t output_seq; /* Sequence number क्रम output report. */
पूर्ण;

काष्ठा dualsense_touch_poपूर्णांक अणु
	uपूर्णांक8_t contact;
	uपूर्णांक8_t x_lo;
	uपूर्णांक8_t x_hi:4, y_lo:4;
	uपूर्णांक8_t y_hi;
पूर्ण __packed;
अटल_निश्चित(माप(काष्ठा dualsense_touch_poपूर्णांक) == 4);

/* Main DualSense input report excluding any BT/USB specअगरic headers. */
काष्ठा dualsense_input_report अणु
	uपूर्णांक8_t x, y;
	uपूर्णांक8_t rx, ry;
	uपूर्णांक8_t z, rz;
	uपूर्णांक8_t seq_number;
	uपूर्णांक8_t buttons[4];
	uपूर्णांक8_t reserved[4];

	/* Motion sensors */
	__le16 gyro[3]; /* x, y, z */
	__le16 accel[3]; /* x, y, z */
	__le32 sensor_बारtamp;
	uपूर्णांक8_t reserved2;

	/* Touchpad */
	काष्ठा dualsense_touch_poपूर्णांक poपूर्णांकs[2];

	uपूर्णांक8_t reserved3[12];
	uपूर्णांक8_t status;
	uपूर्णांक8_t reserved4[10];
पूर्ण __packed;
/* Common input report size shared equals the size of the USB report minus 1 byte क्रम ReportID. */
अटल_निश्चित(माप(काष्ठा dualsense_input_report) == DS_INPUT_REPORT_USB_SIZE - 1);

/* Common data between DualSense BT/USB मुख्य output report. */
काष्ठा dualsense_output_report_common अणु
	uपूर्णांक8_t valid_flag0;
	uपूर्णांक8_t valid_flag1;

	/* For DualShock 4 compatibility mode. */
	uपूर्णांक8_t motor_right;
	uपूर्णांक8_t motor_left;

	/* Audio controls */
	uपूर्णांक8_t reserved[4];
	uपूर्णांक8_t mute_button_led;

	uपूर्णांक8_t घातer_save_control;
	uपूर्णांक8_t reserved2[28];

	/* LEDs and lightbar */
	uपूर्णांक8_t valid_flag2;
	uपूर्णांक8_t reserved3[2];
	uपूर्णांक8_t lightbar_setup;
	uपूर्णांक8_t led_brightness;
	uपूर्णांक8_t player_leds;
	uपूर्णांक8_t lightbar_red;
	uपूर्णांक8_t lightbar_green;
	uपूर्णांक8_t lightbar_blue;
पूर्ण __packed;
अटल_निश्चित(माप(काष्ठा dualsense_output_report_common) == 47);

काष्ठा dualsense_output_report_bt अणु
	uपूर्णांक8_t report_id; /* 0x31 */
	uपूर्णांक8_t seq_tag;
	uपूर्णांक8_t tag;
	काष्ठा dualsense_output_report_common common;
	uपूर्णांक8_t reserved[24];
	__le32 crc32;
पूर्ण __packed;
अटल_निश्चित(माप(काष्ठा dualsense_output_report_bt) == DS_OUTPUT_REPORT_BT_SIZE);

काष्ठा dualsense_output_report_usb अणु
	uपूर्णांक8_t report_id; /* 0x02 */
	काष्ठा dualsense_output_report_common common;
	uपूर्णांक8_t reserved[15];
पूर्ण __packed;
अटल_निश्चित(माप(काष्ठा dualsense_output_report_usb) == DS_OUTPUT_REPORT_USB_SIZE);

/*
 * The DualSense has a मुख्य output report used to control most features. It is
 * largely the same between Bluetooth and USB except क्रम dअगरferent headers and CRC.
 * This काष्ठाure hide the dअगरferences between the two to simplअगरy sending output reports.
 */
काष्ठा dualsense_output_report अणु
	uपूर्णांक8_t *data; /* Start of data */
	uपूर्णांक8_t len; /* Size of output report */

	/* Poपूर्णांकs to Bluetooth data payload in हाल क्रम a Bluetooth report अन्यथा शून्य. */
	काष्ठा dualsense_output_report_bt *bt;
	/* Poपूर्णांकs to USB data payload in हाल क्रम a USB report अन्यथा शून्य. */
	काष्ठा dualsense_output_report_usb *usb;
	/* Poपूर्णांकs to common section of report, so past any headers. */
	काष्ठा dualsense_output_report_common *common;
पूर्ण;

/*
 * Common gamepad buttons across DualShock 3 / 4 and DualSense.
 * Note: क्रम device with a touchpad, touchpad button is not included
 *        as it will be part of the touchpad device.
 */
अटल स्थिर पूर्णांक ps_gamepad_buttons[] = अणु
	BTN_WEST, /* Square */
	BTN_NORTH, /* Triangle */
	BTN_EAST, /* Circle */
	BTN_SOUTH, /* Cross */
	BTN_TL, /* L1 */
	BTN_TR, /* R1 */
	BTN_TL2, /* L2 */
	BTN_TR2, /* R2 */
	BTN_SELECT, /* Create (PS5) / Share (PS4) */
	BTN_START, /* Option */
	BTN_THUMBL, /* L3 */
	BTN_THUMBR, /* R3 */
	BTN_MODE, /* PS Home */
पूर्ण;

अटल स्थिर काष्ठा अणुपूर्णांक x; पूर्णांक y; पूर्ण ps_gamepad_hat_mapping[] = अणु
	अणु0, -1पूर्ण, अणु1, -1पूर्ण, अणु1, 0पूर्ण, अणु1, 1पूर्ण, अणु0, 1पूर्ण, अणु-1, 1पूर्ण, अणु-1, 0पूर्ण, अणु-1, -1पूर्ण,
	अणु0, 0पूर्ण,
पूर्ण;

/*
 * Add a new ps_device to ps_devices अगर it करोesn't exist.
 * Return error on duplicate device, which can happen अगर the same
 * device is connected using both Bluetooth and USB.
 */
अटल पूर्णांक ps_devices_list_add(काष्ठा ps_device *dev)
अणु
	काष्ठा ps_device *entry;

	mutex_lock(&ps_devices_lock);
	list_क्रम_each_entry(entry, &ps_devices_list, list) अणु
		अगर (!स_भेद(entry->mac_address, dev->mac_address, माप(dev->mac_address))) अणु
			hid_err(dev->hdev, "Duplicate device found for MAC address %pMR.\n",
					dev->mac_address);
			mutex_unlock(&ps_devices_lock);
			वापस -EEXIST;
		पूर्ण
	पूर्ण

	list_add_tail(&dev->list, &ps_devices_list);
	mutex_unlock(&ps_devices_lock);
	वापस 0;
पूर्ण

अटल पूर्णांक ps_devices_list_हटाओ(काष्ठा ps_device *dev)
अणु
	mutex_lock(&ps_devices_lock);
	list_del(&dev->list);
	mutex_unlock(&ps_devices_lock);
	वापस 0;
पूर्ण

अटल पूर्णांक ps_device_set_player_id(काष्ठा ps_device *dev)
अणु
	पूर्णांक ret = ida_alloc(&ps_player_id_allocator, GFP_KERNEL);

	अगर (ret < 0)
		वापस ret;

	dev->player_id = ret;
	वापस 0;
पूर्ण

अटल व्योम ps_device_release_player_id(काष्ठा ps_device *dev)
अणु
	ida_मुक्त(&ps_player_id_allocator, dev->player_id);

	dev->player_id = U32_MAX;
पूर्ण

अटल काष्ठा input_dev *ps_allocate_input_dev(काष्ठा hid_device *hdev, स्थिर अक्षर *name_suffix)
अणु
	काष्ठा input_dev *input_dev;

	input_dev = devm_input_allocate_device(&hdev->dev);
	अगर (!input_dev)
		वापस ERR_PTR(-ENOMEM);

	input_dev->id.bustype = hdev->bus;
	input_dev->id.venकरोr = hdev->venकरोr;
	input_dev->id.product = hdev->product;
	input_dev->id.version = hdev->version;
	input_dev->uniq = hdev->uniq;

	अगर (name_suffix) अणु
		input_dev->name = devm_kaप्र_लिखो(&hdev->dev, GFP_KERNEL, "%s %s", hdev->name,
				name_suffix);
		अगर (!input_dev->name)
			वापस ERR_PTR(-ENOMEM);
	पूर्ण अन्यथा अणु
		input_dev->name = hdev->name;
	पूर्ण

	input_set_drvdata(input_dev, hdev);

	वापस input_dev;
पूर्ण

अटल क्रमागत घातer_supply_property ps_घातer_supply_props[] = अणु
	POWER_SUPPLY_PROP_STATUS,
	POWER_SUPPLY_PROP_PRESENT,
	POWER_SUPPLY_PROP_CAPACITY,
	POWER_SUPPLY_PROP_SCOPE,
पूर्ण;

अटल पूर्णांक ps_battery_get_property(काष्ठा घातer_supply *psy,
		क्रमागत घातer_supply_property psp,
		जोड़ घातer_supply_propval *val)
अणु
	काष्ठा ps_device *dev = घातer_supply_get_drvdata(psy);
	uपूर्णांक8_t battery_capacity;
	पूर्णांक battery_status;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = 0;

	spin_lock_irqsave(&dev->lock, flags);
	battery_capacity = dev->battery_capacity;
	battery_status = dev->battery_status;
	spin_unlock_irqrestore(&dev->lock, flags);

	चयन (psp) अणु
	हाल POWER_SUPPLY_PROP_STATUS:
		val->पूर्णांकval = battery_status;
		अवरोध;
	हाल POWER_SUPPLY_PROP_PRESENT:
		val->पूर्णांकval = 1;
		अवरोध;
	हाल POWER_SUPPLY_PROP_CAPACITY:
		val->पूर्णांकval = battery_capacity;
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

अटल पूर्णांक ps_device_रेजिस्टर_battery(काष्ठा ps_device *dev)
अणु
	काष्ठा घातer_supply *battery;
	काष्ठा घातer_supply_config battery_cfg = अणु .drv_data = dev पूर्ण;
	पूर्णांक ret;

	dev->battery_desc.type = POWER_SUPPLY_TYPE_BATTERY;
	dev->battery_desc.properties = ps_घातer_supply_props;
	dev->battery_desc.num_properties = ARRAY_SIZE(ps_घातer_supply_props);
	dev->battery_desc.get_property = ps_battery_get_property;
	dev->battery_desc.name = devm_kaप्र_लिखो(&dev->hdev->dev, GFP_KERNEL,
			"ps-controller-battery-%pMR", dev->mac_address);
	अगर (!dev->battery_desc.name)
		वापस -ENOMEM;

	battery = devm_घातer_supply_रेजिस्टर(&dev->hdev->dev, &dev->battery_desc, &battery_cfg);
	अगर (IS_ERR(battery)) अणु
		ret = PTR_ERR(battery);
		hid_err(dev->hdev, "Unable to register battery device: %d\n", ret);
		वापस ret;
	पूर्ण
	dev->battery = battery;

	ret = घातer_supply_घातers(dev->battery, &dev->hdev->dev);
	अगर (ret) अणु
		hid_err(dev->hdev, "Unable to activate battery device: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

/* Compute crc32 of HID data and compare against expected CRC. */
अटल bool ps_check_crc32(uपूर्णांक8_t seed, uपूर्णांक8_t *data, माप_प्रकार len, uपूर्णांक32_t report_crc)
अणु
	uपूर्णांक32_t crc;

	crc = crc32_le(0xFFFFFFFF, &seed, 1);
	crc = ~crc32_le(crc, data, len);

	वापस crc == report_crc;
पूर्ण

अटल काष्ठा input_dev *ps_gamepad_create(काष्ठा hid_device *hdev,
		पूर्णांक (*play_effect)(काष्ठा input_dev *, व्योम *, काष्ठा ff_effect *))
अणु
	काष्ठा input_dev *gamepad;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	gamepad = ps_allocate_input_dev(hdev, शून्य);
	अगर (IS_ERR(gamepad))
		वापस ERR_CAST(gamepad);

	input_set_असल_params(gamepad, ABS_X, 0, 255, 0, 0);
	input_set_असल_params(gamepad, ABS_Y, 0, 255, 0, 0);
	input_set_असल_params(gamepad, ABS_Z, 0, 255, 0, 0);
	input_set_असल_params(gamepad, ABS_RX, 0, 255, 0, 0);
	input_set_असल_params(gamepad, ABS_RY, 0, 255, 0, 0);
	input_set_असल_params(gamepad, ABS_RZ, 0, 255, 0, 0);

	input_set_असल_params(gamepad, ABS_HAT0X, -1, 1, 0, 0);
	input_set_असल_params(gamepad, ABS_HAT0Y, -1, 1, 0, 0);

	क्रम (i = 0; i < ARRAY_SIZE(ps_gamepad_buttons); i++)
		input_set_capability(gamepad, EV_KEY, ps_gamepad_buttons[i]);

#अगर IS_ENABLED(CONFIG_PLAYSTATION_FF)
	अगर (play_effect) अणु
		input_set_capability(gamepad, EV_FF, FF_RUMBLE);
		input_ff_create_memless(gamepad, शून्य, play_effect);
	पूर्ण
#पूर्ण_अगर

	ret = input_रेजिस्टर_device(gamepad);
	अगर (ret)
		वापस ERR_PTR(ret);

	वापस gamepad;
पूर्ण

अटल पूर्णांक ps_get_report(काष्ठा hid_device *hdev, uपूर्णांक8_t report_id, uपूर्णांक8_t *buf, माप_प्रकार size)
अणु
	पूर्णांक ret;

	ret = hid_hw_raw_request(hdev, report_id, buf, size, HID_FEATURE_REPORT,
				 HID_REQ_GET_REPORT);
	अगर (ret < 0) अणु
		hid_err(hdev, "Failed to retrieve feature with reportID %d: %d\n", report_id, ret);
		वापस ret;
	पूर्ण

	अगर (ret != size) अणु
		hid_err(hdev, "Invalid byte count transferred, expected %zu got %d\n", size, ret);
		वापस -EINVAL;
	पूर्ण

	अगर (buf[0] != report_id) अणु
		hid_err(hdev, "Invalid reportID received, expected %d got %d\n", report_id, buf[0]);
		वापस -EINVAL;
	पूर्ण

	अगर (hdev->bus == BUS_BLUETOOTH) अणु
		/* Last 4 bytes contains crc32. */
		uपूर्णांक8_t crc_offset = size - 4;
		uपूर्णांक32_t report_crc = get_unaligned_le32(&buf[crc_offset]);

		अगर (!ps_check_crc32(PS_FEATURE_CRC32_SEED, buf, crc_offset, report_crc)) अणु
			hid_err(hdev, "CRC check failed for reportID=%d\n", report_id);
			वापस -EILSEQ;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा input_dev *ps_sensors_create(काष्ठा hid_device *hdev, पूर्णांक accel_range, पूर्णांक accel_res,
		पूर्णांक gyro_range, पूर्णांक gyro_res)
अणु
	काष्ठा input_dev *sensors;
	पूर्णांक ret;

	sensors = ps_allocate_input_dev(hdev, "Motion Sensors");
	अगर (IS_ERR(sensors))
		वापस ERR_CAST(sensors);

	__set_bit(INPUT_PROP_ACCELEROMETER, sensors->propbit);
	__set_bit(EV_MSC, sensors->evbit);
	__set_bit(MSC_TIMESTAMP, sensors->mscbit);

	/* Accelerometer */
	input_set_असल_params(sensors, ABS_X, -accel_range, accel_range, 16, 0);
	input_set_असल_params(sensors, ABS_Y, -accel_range, accel_range, 16, 0);
	input_set_असल_params(sensors, ABS_Z, -accel_range, accel_range, 16, 0);
	input_असल_set_res(sensors, ABS_X, accel_res);
	input_असल_set_res(sensors, ABS_Y, accel_res);
	input_असल_set_res(sensors, ABS_Z, accel_res);

	/* Gyroscope */
	input_set_असल_params(sensors, ABS_RX, -gyro_range, gyro_range, 16, 0);
	input_set_असल_params(sensors, ABS_RY, -gyro_range, gyro_range, 16, 0);
	input_set_असल_params(sensors, ABS_RZ, -gyro_range, gyro_range, 16, 0);
	input_असल_set_res(sensors, ABS_RX, gyro_res);
	input_असल_set_res(sensors, ABS_RY, gyro_res);
	input_असल_set_res(sensors, ABS_RZ, gyro_res);

	ret = input_रेजिस्टर_device(sensors);
	अगर (ret)
		वापस ERR_PTR(ret);

	वापस sensors;
पूर्ण

अटल काष्ठा input_dev *ps_touchpad_create(काष्ठा hid_device *hdev, पूर्णांक width, पूर्णांक height,
		अचिन्हित पूर्णांक num_contacts)
अणु
	काष्ठा input_dev *touchpad;
	पूर्णांक ret;

	touchpad = ps_allocate_input_dev(hdev, "Touchpad");
	अगर (IS_ERR(touchpad))
		वापस ERR_CAST(touchpad);

	/* Map button underneath touchpad to BTN_LEFT. */
	input_set_capability(touchpad, EV_KEY, BTN_LEFT);
	__set_bit(INPUT_PROP_BUTTONPAD, touchpad->propbit);

	input_set_असल_params(touchpad, ABS_MT_POSITION_X, 0, width - 1, 0, 0);
	input_set_असल_params(touchpad, ABS_MT_POSITION_Y, 0, height - 1, 0, 0);

	ret = input_mt_init_slots(touchpad, num_contacts, INPUT_MT_POINTER);
	अगर (ret)
		वापस ERR_PTR(ret);

	ret = input_रेजिस्टर_device(touchpad);
	अगर (ret)
		वापस ERR_PTR(ret);

	वापस touchpad;
पूर्ण

अटल sमाप_प्रकार firmware_version_show(काष्ठा device *dev,
				काष्ठा device_attribute
				*attr, अक्षर *buf)
अणु
	काष्ठा hid_device *hdev = to_hid_device(dev);
	काष्ठा ps_device *ps_dev = hid_get_drvdata(hdev);

	वापस sysfs_emit(buf, "0x%08x\n", ps_dev->fw_version);
पूर्ण

अटल DEVICE_ATTR_RO(firmware_version);

अटल sमाप_प्रकार hardware_version_show(काष्ठा device *dev,
				काष्ठा device_attribute
				*attr, अक्षर *buf)
अणु
	काष्ठा hid_device *hdev = to_hid_device(dev);
	काष्ठा ps_device *ps_dev = hid_get_drvdata(hdev);

	वापस sysfs_emit(buf, "0x%08x\n", ps_dev->hw_version);
पूर्ण

अटल DEVICE_ATTR_RO(hardware_version);

अटल काष्ठा attribute *ps_device_attributes[] = अणु
	&dev_attr_firmware_version.attr,
	&dev_attr_hardware_version.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group ps_device_attribute_group = अणु
	.attrs = ps_device_attributes,
पूर्ण;

अटल पूर्णांक dualsense_get_calibration_data(काष्ठा dualsense *ds)
अणु
	लघु gyro_pitch_bias, gyro_pitch_plus, gyro_pitch_minus;
	लघु gyro_yaw_bias, gyro_yaw_plus, gyro_yaw_minus;
	लघु gyro_roll_bias, gyro_roll_plus, gyro_roll_minus;
	लघु gyro_speed_plus, gyro_speed_minus;
	लघु acc_x_plus, acc_x_minus;
	लघु acc_y_plus, acc_y_minus;
	लघु acc_z_plus, acc_z_minus;
	पूर्णांक speed_2x;
	पूर्णांक range_2g;
	पूर्णांक ret = 0;
	uपूर्णांक8_t *buf;

	buf = kzalloc(DS_FEATURE_REPORT_CALIBRATION_SIZE, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	ret = ps_get_report(ds->base.hdev, DS_FEATURE_REPORT_CALIBRATION, buf,
			DS_FEATURE_REPORT_CALIBRATION_SIZE);
	अगर (ret) अणु
		hid_err(ds->base.hdev, "Failed to retrieve DualSense calibration info: %d\n", ret);
		जाओ err_मुक्त;
	पूर्ण

	gyro_pitch_bias  = get_unaligned_le16(&buf[1]);
	gyro_yaw_bias    = get_unaligned_le16(&buf[3]);
	gyro_roll_bias   = get_unaligned_le16(&buf[5]);
	gyro_pitch_plus  = get_unaligned_le16(&buf[7]);
	gyro_pitch_minus = get_unaligned_le16(&buf[9]);
	gyro_yaw_plus    = get_unaligned_le16(&buf[11]);
	gyro_yaw_minus   = get_unaligned_le16(&buf[13]);
	gyro_roll_plus   = get_unaligned_le16(&buf[15]);
	gyro_roll_minus  = get_unaligned_le16(&buf[17]);
	gyro_speed_plus  = get_unaligned_le16(&buf[19]);
	gyro_speed_minus = get_unaligned_le16(&buf[21]);
	acc_x_plus       = get_unaligned_le16(&buf[23]);
	acc_x_minus      = get_unaligned_le16(&buf[25]);
	acc_y_plus       = get_unaligned_le16(&buf[27]);
	acc_y_minus      = get_unaligned_le16(&buf[29]);
	acc_z_plus       = get_unaligned_le16(&buf[31]);
	acc_z_minus      = get_unaligned_le16(&buf[33]);

	/*
	 * Set gyroscope calibration and normalization parameters.
	 * Data values will be normalized to 1/DS_GYRO_RES_PER_DEG_S degree/s.
	 */
	speed_2x = (gyro_speed_plus + gyro_speed_minus);
	ds->gyro_calib_data[0].असल_code = ABS_RX;
	ds->gyro_calib_data[0].bias = gyro_pitch_bias;
	ds->gyro_calib_data[0].sens_numer = speed_2x*DS_GYRO_RES_PER_DEG_S;
	ds->gyro_calib_data[0].sens_denom = gyro_pitch_plus - gyro_pitch_minus;

	ds->gyro_calib_data[1].असल_code = ABS_RY;
	ds->gyro_calib_data[1].bias = gyro_yaw_bias;
	ds->gyro_calib_data[1].sens_numer = speed_2x*DS_GYRO_RES_PER_DEG_S;
	ds->gyro_calib_data[1].sens_denom = gyro_yaw_plus - gyro_yaw_minus;

	ds->gyro_calib_data[2].असल_code = ABS_RZ;
	ds->gyro_calib_data[2].bias = gyro_roll_bias;
	ds->gyro_calib_data[2].sens_numer = speed_2x*DS_GYRO_RES_PER_DEG_S;
	ds->gyro_calib_data[2].sens_denom = gyro_roll_plus - gyro_roll_minus;

	/*
	 * Set accelerometer calibration and normalization parameters.
	 * Data values will be normalized to 1/DS_ACC_RES_PER_G g.
	 */
	range_2g = acc_x_plus - acc_x_minus;
	ds->accel_calib_data[0].असल_code = ABS_X;
	ds->accel_calib_data[0].bias = acc_x_plus - range_2g / 2;
	ds->accel_calib_data[0].sens_numer = 2*DS_ACC_RES_PER_G;
	ds->accel_calib_data[0].sens_denom = range_2g;

	range_2g = acc_y_plus - acc_y_minus;
	ds->accel_calib_data[1].असल_code = ABS_Y;
	ds->accel_calib_data[1].bias = acc_y_plus - range_2g / 2;
	ds->accel_calib_data[1].sens_numer = 2*DS_ACC_RES_PER_G;
	ds->accel_calib_data[1].sens_denom = range_2g;

	range_2g = acc_z_plus - acc_z_minus;
	ds->accel_calib_data[2].असल_code = ABS_Z;
	ds->accel_calib_data[2].bias = acc_z_plus - range_2g / 2;
	ds->accel_calib_data[2].sens_numer = 2*DS_ACC_RES_PER_G;
	ds->accel_calib_data[2].sens_denom = range_2g;

err_मुक्त:
	kमुक्त(buf);
	वापस ret;
पूर्ण

अटल पूर्णांक dualsense_get_firmware_info(काष्ठा dualsense *ds)
अणु
	uपूर्णांक8_t *buf;
	पूर्णांक ret;

	buf = kzalloc(DS_FEATURE_REPORT_FIRMWARE_INFO_SIZE, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	ret = ps_get_report(ds->base.hdev, DS_FEATURE_REPORT_FIRMWARE_INFO, buf,
			DS_FEATURE_REPORT_FIRMWARE_INFO_SIZE);
	अगर (ret) अणु
		hid_err(ds->base.hdev, "Failed to retrieve DualSense firmware info: %d\n", ret);
		जाओ err_मुक्त;
	पूर्ण

	ds->base.hw_version = get_unaligned_le32(&buf[24]);
	ds->base.fw_version = get_unaligned_le32(&buf[28]);

err_मुक्त:
	kमुक्त(buf);
	वापस ret;
पूर्ण

अटल पूर्णांक dualsense_get_mac_address(काष्ठा dualsense *ds)
अणु
	uपूर्णांक8_t *buf;
	पूर्णांक ret = 0;

	buf = kzalloc(DS_FEATURE_REPORT_PAIRING_INFO_SIZE, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	ret = ps_get_report(ds->base.hdev, DS_FEATURE_REPORT_PAIRING_INFO, buf,
			DS_FEATURE_REPORT_PAIRING_INFO_SIZE);
	अगर (ret) अणु
		hid_err(ds->base.hdev, "Failed to retrieve DualSense pairing info: %d\n", ret);
		जाओ err_मुक्त;
	पूर्ण

	स_नकल(ds->base.mac_address, &buf[1], माप(ds->base.mac_address));

err_मुक्त:
	kमुक्त(buf);
	वापस ret;
पूर्ण

अटल व्योम dualsense_init_output_report(काष्ठा dualsense *ds, काष्ठा dualsense_output_report *rp,
		व्योम *buf)
अणु
	काष्ठा hid_device *hdev = ds->base.hdev;

	अगर (hdev->bus == BUS_BLUETOOTH) अणु
		काष्ठा dualsense_output_report_bt *bt = buf;

		स_रखो(bt, 0, माप(*bt));
		bt->report_id = DS_OUTPUT_REPORT_BT;
		bt->tag = DS_OUTPUT_TAG; /* Tag must be set. Exact meaning is unclear. */

		/*
		 * Highest 4-bit is a sequence number, which needs to be increased
		 * every report. Lowest 4-bit is tag and can be zero क्रम now.
		 */
		bt->seq_tag = (ds->output_seq << 4) | 0x0;
		अगर (++ds->output_seq == 16)
			ds->output_seq = 0;

		rp->data = buf;
		rp->len = माप(*bt);
		rp->bt = bt;
		rp->usb = शून्य;
		rp->common = &bt->common;
	पूर्ण अन्यथा अणु /* USB */
		काष्ठा dualsense_output_report_usb *usb = buf;

		स_रखो(usb, 0, माप(*usb));
		usb->report_id = DS_OUTPUT_REPORT_USB;

		rp->data = buf;
		rp->len = माप(*usb);
		rp->bt = शून्य;
		rp->usb = usb;
		rp->common = &usb->common;
	पूर्ण
पूर्ण

/*
 * Helper function to send DualSense output reports. Applies a CRC at the end of a report
 * क्रम Bluetooth reports.
 */
अटल व्योम dualsense_send_output_report(काष्ठा dualsense *ds,
		काष्ठा dualsense_output_report *report)
अणु
	काष्ठा hid_device *hdev = ds->base.hdev;

	/* Bluetooth packets need to be चिन्हित with a CRC in the last 4 bytes. */
	अगर (report->bt) अणु
		uपूर्णांक32_t crc;
		uपूर्णांक8_t seed = PS_OUTPUT_CRC32_SEED;

		crc = crc32_le(0xFFFFFFFF, &seed, 1);
		crc = ~crc32_le(crc, report->data, report->len - 4);

		report->bt->crc32 = cpu_to_le32(crc);
	पूर्ण

	hid_hw_output_report(hdev, report->data, report->len);
पूर्ण

अटल व्योम dualsense_output_worker(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा dualsense *ds = container_of(work, काष्ठा dualsense, output_worker);
	काष्ठा dualsense_output_report report;
	काष्ठा dualsense_output_report_common *common;
	अचिन्हित दीर्घ flags;

	dualsense_init_output_report(ds, &report, ds->output_report_dmabuf);
	common = report.common;

	spin_lock_irqsave(&ds->base.lock, flags);

	अगर (ds->update_rumble) अणु
		/* Select classic rumble style haptics and enable it. */
		common->valid_flag0 |= DS_OUTPUT_VALID_FLAG0_HAPTICS_SELECT;
		common->valid_flag0 |= DS_OUTPUT_VALID_FLAG0_COMPATIBLE_VIBRATION;
		common->motor_left = ds->motor_left;
		common->motor_right = ds->motor_right;
		ds->update_rumble = false;
	पूर्ण

	अगर (ds->update_lightbar) अणु
		common->valid_flag1 |= DS_OUTPUT_VALID_FLAG1_LIGHTBAR_CONTROL_ENABLE;
		common->lightbar_red = ds->lightbar_red;
		common->lightbar_green = ds->lightbar_green;
		common->lightbar_blue = ds->lightbar_blue;

		ds->update_lightbar = false;
	पूर्ण

	अगर (ds->update_player_leds) अणु
		common->valid_flag1 |= DS_OUTPUT_VALID_FLAG1_PLAYER_INDICATOR_CONTROL_ENABLE;
		common->player_leds = ds->player_leds_state;

		ds->update_player_leds = false;
	पूर्ण

	अगर (ds->update_mic_mute) अणु
		common->valid_flag1 |= DS_OUTPUT_VALID_FLAG1_MIC_MUTE_LED_CONTROL_ENABLE;
		common->mute_button_led = ds->mic_muted;

		अगर (ds->mic_muted) अणु
			/* Disable microphone */
			common->valid_flag1 |= DS_OUTPUT_VALID_FLAG1_POWER_SAVE_CONTROL_ENABLE;
			common->घातer_save_control |= DS_OUTPUT_POWER_SAVE_CONTROL_MIC_MUTE;
		पूर्ण अन्यथा अणु
			/* Enable microphone */
			common->valid_flag1 |= DS_OUTPUT_VALID_FLAG1_POWER_SAVE_CONTROL_ENABLE;
			common->घातer_save_control &= ~DS_OUTPUT_POWER_SAVE_CONTROL_MIC_MUTE;
		पूर्ण

		ds->update_mic_mute = false;
	पूर्ण

	spin_unlock_irqrestore(&ds->base.lock, flags);

	dualsense_send_output_report(ds, &report);
पूर्ण

अटल पूर्णांक dualsense_parse_report(काष्ठा ps_device *ps_dev, काष्ठा hid_report *report,
		u8 *data, पूर्णांक size)
अणु
	काष्ठा hid_device *hdev = ps_dev->hdev;
	काष्ठा dualsense *ds = container_of(ps_dev, काष्ठा dualsense, base);
	काष्ठा dualsense_input_report *ds_report;
	uपूर्णांक8_t battery_data, battery_capacity, अक्षरging_status, value;
	पूर्णांक battery_status;
	uपूर्णांक32_t sensor_बारtamp;
	bool btn_mic_state;
	अचिन्हित दीर्घ flags;
	पूर्णांक i;

	/*
	 * DualSense in USB uses the full HID report क्रम reportID 1, but
	 * Bluetooth uses a minimal HID report क्रम reportID 1 and reports
	 * the full report using reportID 49.
	 */
	अगर (hdev->bus == BUS_USB && report->id == DS_INPUT_REPORT_USB &&
			size == DS_INPUT_REPORT_USB_SIZE) अणु
		ds_report = (काष्ठा dualsense_input_report *)&data[1];
	पूर्ण अन्यथा अगर (hdev->bus == BUS_BLUETOOTH && report->id == DS_INPUT_REPORT_BT &&
			size == DS_INPUT_REPORT_BT_SIZE) अणु
		/* Last 4 bytes of input report contain crc32 */
		uपूर्णांक32_t report_crc = get_unaligned_le32(&data[size - 4]);

		अगर (!ps_check_crc32(PS_INPUT_CRC32_SEED, data, size - 4, report_crc)) अणु
			hid_err(hdev, "DualSense input CRC's check failed\n");
			वापस -EILSEQ;
		पूर्ण

		ds_report = (काष्ठा dualsense_input_report *)&data[2];
	पूर्ण अन्यथा अणु
		hid_err(hdev, "Unhandled reportID=%d\n", report->id);
		वापस -1;
	पूर्ण

	input_report_असल(ds->gamepad, ABS_X,  ds_report->x);
	input_report_असल(ds->gamepad, ABS_Y,  ds_report->y);
	input_report_असल(ds->gamepad, ABS_RX, ds_report->rx);
	input_report_असल(ds->gamepad, ABS_RY, ds_report->ry);
	input_report_असल(ds->gamepad, ABS_Z,  ds_report->z);
	input_report_असल(ds->gamepad, ABS_RZ, ds_report->rz);

	value = ds_report->buttons[0] & DS_BUTTONS0_HAT_SWITCH;
	अगर (value >= ARRAY_SIZE(ps_gamepad_hat_mapping))
		value = 8; /* center */
	input_report_असल(ds->gamepad, ABS_HAT0X, ps_gamepad_hat_mapping[value].x);
	input_report_असल(ds->gamepad, ABS_HAT0Y, ps_gamepad_hat_mapping[value].y);

	input_report_key(ds->gamepad, BTN_WEST,   ds_report->buttons[0] & DS_BUTTONS0_SQUARE);
	input_report_key(ds->gamepad, BTN_SOUTH,  ds_report->buttons[0] & DS_BUTTONS0_CROSS);
	input_report_key(ds->gamepad, BTN_EAST,   ds_report->buttons[0] & DS_BUTTONS0_CIRCLE);
	input_report_key(ds->gamepad, BTN_NORTH,  ds_report->buttons[0] & DS_BUTTONS0_TRIANGLE);
	input_report_key(ds->gamepad, BTN_TL,     ds_report->buttons[1] & DS_BUTTONS1_L1);
	input_report_key(ds->gamepad, BTN_TR,     ds_report->buttons[1] & DS_BUTTONS1_R1);
	input_report_key(ds->gamepad, BTN_TL2,    ds_report->buttons[1] & DS_BUTTONS1_L2);
	input_report_key(ds->gamepad, BTN_TR2,    ds_report->buttons[1] & DS_BUTTONS1_R2);
	input_report_key(ds->gamepad, BTN_SELECT, ds_report->buttons[1] & DS_BUTTONS1_CREATE);
	input_report_key(ds->gamepad, BTN_START,  ds_report->buttons[1] & DS_BUTTONS1_OPTIONS);
	input_report_key(ds->gamepad, BTN_THUMBL, ds_report->buttons[1] & DS_BUTTONS1_L3);
	input_report_key(ds->gamepad, BTN_THUMBR, ds_report->buttons[1] & DS_BUTTONS1_R3);
	input_report_key(ds->gamepad, BTN_MODE,   ds_report->buttons[2] & DS_BUTTONS2_PS_HOME);
	input_sync(ds->gamepad);

	/*
	 * The DualSense has an पूर्णांकernal microphone, which can be muted through a mute button
	 * on the device. The driver is expected to पढ़ो the button state and program the device
	 * to mute/unmute audio at the hardware level.
	 */
	btn_mic_state = !!(ds_report->buttons[2] & DS_BUTTONS2_MIC_MUTE);
	अगर (btn_mic_state && !ds->last_btn_mic_state) अणु
		spin_lock_irqsave(&ps_dev->lock, flags);
		ds->update_mic_mute = true;
		ds->mic_muted = !ds->mic_muted; /* toggle */
		spin_unlock_irqrestore(&ps_dev->lock, flags);

		/* Schedule updating of microphone state at hardware level. */
		schedule_work(&ds->output_worker);
	पूर्ण
	ds->last_btn_mic_state = btn_mic_state;

	/* Parse and calibrate gyroscope data. */
	क्रम (i = 0; i < ARRAY_SIZE(ds_report->gyro); i++) अणु
		पूर्णांक raw_data = (लघु)le16_to_cpu(ds_report->gyro[i]);
		पूर्णांक calib_data = mult_frac(ds->gyro_calib_data[i].sens_numer,
					   raw_data - ds->gyro_calib_data[i].bias,
					   ds->gyro_calib_data[i].sens_denom);

		input_report_असल(ds->sensors, ds->gyro_calib_data[i].असल_code, calib_data);
	पूर्ण

	/* Parse and calibrate accelerometer data. */
	क्रम (i = 0; i < ARRAY_SIZE(ds_report->accel); i++) अणु
		पूर्णांक raw_data = (लघु)le16_to_cpu(ds_report->accel[i]);
		पूर्णांक calib_data = mult_frac(ds->accel_calib_data[i].sens_numer,
					   raw_data - ds->accel_calib_data[i].bias,
					   ds->accel_calib_data[i].sens_denom);

		input_report_असल(ds->sensors, ds->accel_calib_data[i].असल_code, calib_data);
	पूर्ण

	/* Convert बारtamp (in 0.33us unit) to बारtamp_us */
	sensor_बारtamp = le32_to_cpu(ds_report->sensor_बारtamp);
	अगर (!ds->sensor_बारtamp_initialized) अणु
		ds->sensor_बारtamp_us = DIV_ROUND_CLOSEST(sensor_बारtamp, 3);
		ds->sensor_बारtamp_initialized = true;
	पूर्ण अन्यथा अणु
		uपूर्णांक32_t delta;

		अगर (ds->prev_sensor_बारtamp > sensor_बारtamp)
			delta = (U32_MAX - ds->prev_sensor_बारtamp + sensor_बारtamp + 1);
		अन्यथा
			delta = sensor_बारtamp - ds->prev_sensor_बारtamp;
		ds->sensor_बारtamp_us += DIV_ROUND_CLOSEST(delta, 3);
	पूर्ण
	ds->prev_sensor_बारtamp = sensor_बारtamp;
	input_event(ds->sensors, EV_MSC, MSC_TIMESTAMP, ds->sensor_बारtamp_us);
	input_sync(ds->sensors);

	क्रम (i = 0; i < ARRAY_SIZE(ds_report->poपूर्णांकs); i++) अणु
		काष्ठा dualsense_touch_poपूर्णांक *poपूर्णांक = &ds_report->poपूर्णांकs[i];
		bool active = (poपूर्णांक->contact & DS_TOUCH_POINT_INACTIVE) ? false : true;

		input_mt_slot(ds->touchpad, i);
		input_mt_report_slot_state(ds->touchpad, MT_TOOL_FINGER, active);

		अगर (active) अणु
			पूर्णांक x = (poपूर्णांक->x_hi << 8) | poपूर्णांक->x_lo;
			पूर्णांक y = (poपूर्णांक->y_hi << 4) | poपूर्णांक->y_lo;

			input_report_असल(ds->touchpad, ABS_MT_POSITION_X, x);
			input_report_असल(ds->touchpad, ABS_MT_POSITION_Y, y);
		पूर्ण
	पूर्ण
	input_mt_sync_frame(ds->touchpad);
	input_report_key(ds->touchpad, BTN_LEFT, ds_report->buttons[2] & DS_BUTTONS2_TOUCHPAD);
	input_sync(ds->touchpad);

	battery_data = ds_report->status & DS_STATUS_BATTERY_CAPACITY;
	अक्षरging_status = (ds_report->status & DS_STATUS_CHARGING) >> DS_STATUS_CHARGING_SHIFT;

	चयन (अक्षरging_status) अणु
	हाल 0x0:
		/*
		 * Each unit of battery data corresponds to 10%
		 * 0 = 0-9%, 1 = 10-19%, .. and 10 = 100%
		 */
		battery_capacity = min(battery_data * 10 + 5, 100);
		battery_status = POWER_SUPPLY_STATUS_DISCHARGING;
		अवरोध;
	हाल 0x1:
		battery_capacity = min(battery_data * 10 + 5, 100);
		battery_status = POWER_SUPPLY_STATUS_CHARGING;
		अवरोध;
	हाल 0x2:
		battery_capacity = 100;
		battery_status = POWER_SUPPLY_STATUS_FULL;
		अवरोध;
	हाल 0xa: /* voltage or temperature out of range */
	हाल 0xb: /* temperature error */
		battery_capacity = 0;
		battery_status = POWER_SUPPLY_STATUS_NOT_CHARGING;
		अवरोध;
	हाल 0xf: /* अक्षरging error */
	शेष:
		battery_capacity = 0;
		battery_status = POWER_SUPPLY_STATUS_UNKNOWN;
	पूर्ण

	spin_lock_irqsave(&ps_dev->lock, flags);
	ps_dev->battery_capacity = battery_capacity;
	ps_dev->battery_status = battery_status;
	spin_unlock_irqrestore(&ps_dev->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक dualsense_play_effect(काष्ठा input_dev *dev, व्योम *data, काष्ठा ff_effect *effect)
अणु
	काष्ठा hid_device *hdev = input_get_drvdata(dev);
	काष्ठा dualsense *ds = hid_get_drvdata(hdev);
	अचिन्हित दीर्घ flags;

	अगर (effect->type != FF_RUMBLE)
		वापस 0;

	spin_lock_irqsave(&ds->base.lock, flags);
	ds->update_rumble = true;
	ds->motor_left = effect->u.rumble.strong_magnitude / 256;
	ds->motor_right = effect->u.rumble.weak_magnitude / 256;
	spin_unlock_irqrestore(&ds->base.lock, flags);

	schedule_work(&ds->output_worker);
	वापस 0;
पूर्ण

अटल पूर्णांक dualsense_reset_leds(काष्ठा dualsense *ds)
अणु
	काष्ठा dualsense_output_report report;
	uपूर्णांक8_t *buf;

	buf = kzalloc(माप(काष्ठा dualsense_output_report_bt), GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	dualsense_init_output_report(ds, &report, buf);
	/*
	 * On Bluetooth the DualSense outमाला_दो an animation on the lightbar
	 * during startup and मुख्यtains a color afterwards. We need to explicitly
	 * reconfigure the lightbar beक्रमe we can करो any programming later on.
	 * In USB the lightbar is not on by शेष, but reकरोing the setup there
	 * करोesn't hurt.
	 */
	report.common->valid_flag2 = DS_OUTPUT_VALID_FLAG2_LIGHTBAR_SETUP_CONTROL_ENABLE;
	report.common->lightbar_setup = DS_OUTPUT_LIGHTBAR_SETUP_LIGHT_OUT; /* Fade light out. */
	dualsense_send_output_report(ds, &report);

	kमुक्त(buf);
	वापस 0;
पूर्ण

अटल व्योम dualsense_set_lightbar(काष्ठा dualsense *ds, uपूर्णांक8_t red, uपूर्णांक8_t green, uपूर्णांक8_t blue)
अणु
	ds->update_lightbar = true;
	ds->lightbar_red = red;
	ds->lightbar_green = green;
	ds->lightbar_blue = blue;

	schedule_work(&ds->output_worker);
पूर्ण

अटल व्योम dualsense_set_player_leds(काष्ठा dualsense *ds)
अणु
	/*
	 * The DualSense controller has a row of 5 LEDs used क्रम player ids.
	 * Behavior on the PlayStation 5 console is to center the player id
	 * across the LEDs, so e.g. player 1 would be "--x--" with x being 'on'.
	 * Follow a similar mapping here.
	 */
	अटल स्थिर पूर्णांक player_ids[5] = अणु
		BIT(2),
		BIT(3) | BIT(1),
		BIT(4) | BIT(2) | BIT(0),
		BIT(4) | BIT(3) | BIT(1) | BIT(0),
		BIT(4) | BIT(3) | BIT(2) | BIT(1) | BIT(0)
	पूर्ण;

	uपूर्णांक8_t player_id = ds->base.player_id % ARRAY_SIZE(player_ids);

	ds->update_player_leds = true;
	ds->player_leds_state = player_ids[player_id];
	schedule_work(&ds->output_worker);
पूर्ण

अटल काष्ठा ps_device *dualsense_create(काष्ठा hid_device *hdev)
अणु
	काष्ठा dualsense *ds;
	काष्ठा ps_device *ps_dev;
	uपूर्णांक8_t max_output_report_size;
	पूर्णांक ret;

	ds = devm_kzalloc(&hdev->dev, माप(*ds), GFP_KERNEL);
	अगर (!ds)
		वापस ERR_PTR(-ENOMEM);

	/*
	 * Patch version to allow userspace to distinguish between
	 * hid-generic vs hid-playstation axis and button mapping.
	 */
	hdev->version |= HID_PLAYSTATION_VERSION_PATCH;

	ps_dev = &ds->base;
	ps_dev->hdev = hdev;
	spin_lock_init(&ps_dev->lock);
	ps_dev->battery_capacity = 100; /* initial value until parse_report. */
	ps_dev->battery_status = POWER_SUPPLY_STATUS_UNKNOWN;
	ps_dev->parse_report = dualsense_parse_report;
	INIT_WORK(&ds->output_worker, dualsense_output_worker);
	hid_set_drvdata(hdev, ds);

	max_output_report_size = माप(काष्ठा dualsense_output_report_bt);
	ds->output_report_dmabuf = devm_kzalloc(&hdev->dev, max_output_report_size, GFP_KERNEL);
	अगर (!ds->output_report_dmabuf)
		वापस ERR_PTR(-ENOMEM);

	ret = dualsense_get_mac_address(ds);
	अगर (ret) अणु
		hid_err(hdev, "Failed to get MAC address from DualSense\n");
		वापस ERR_PTR(ret);
	पूर्ण
	snम_लिखो(hdev->uniq, माप(hdev->uniq), "%pMR", ds->base.mac_address);

	ret = dualsense_get_firmware_info(ds);
	अगर (ret) अणु
		hid_err(hdev, "Failed to get firmware info from DualSense\n");
		वापस ERR_PTR(ret);
	पूर्ण

	ret = ps_devices_list_add(ps_dev);
	अगर (ret)
		वापस ERR_PTR(ret);

	ret = dualsense_get_calibration_data(ds);
	अगर (ret) अणु
		hid_err(hdev, "Failed to get calibration data from DualSense\n");
		जाओ err;
	पूर्ण

	ds->gamepad = ps_gamepad_create(hdev, dualsense_play_effect);
	अगर (IS_ERR(ds->gamepad)) अणु
		ret = PTR_ERR(ds->gamepad);
		जाओ err;
	पूर्ण

	ds->sensors = ps_sensors_create(hdev, DS_ACC_RANGE, DS_ACC_RES_PER_G,
			DS_GYRO_RANGE, DS_GYRO_RES_PER_DEG_S);
	अगर (IS_ERR(ds->sensors)) अणु
		ret = PTR_ERR(ds->sensors);
		जाओ err;
	पूर्ण

	ds->touchpad = ps_touchpad_create(hdev, DS_TOUCHPAD_WIDTH, DS_TOUCHPAD_HEIGHT, 2);
	अगर (IS_ERR(ds->touchpad)) अणु
		ret = PTR_ERR(ds->touchpad);
		जाओ err;
	पूर्ण

	ret = ps_device_रेजिस्टर_battery(ps_dev);
	अगर (ret)
		जाओ err;

	/*
	 * The hardware may have control over the LEDs (e.g. in Bluetooth on startup).
	 * Reset the LEDs (lightbar, mute, player leds), so we can control them
	 * from software.
	 */
	ret = dualsense_reset_leds(ds);
	अगर (ret)
		जाओ err;

	dualsense_set_lightbar(ds, 0, 0, 128); /* blue */

	ret = ps_device_set_player_id(ps_dev);
	अगर (ret) अणु
		hid_err(hdev, "Failed to assign player id for DualSense: %d\n", ret);
		जाओ err;
	पूर्ण

	/* Set player LEDs to our player id. */
	dualsense_set_player_leds(ds);

	/*
	 * Reporting hardware and firmware is important as there are frequent updates, which
	 * can change behavior.
	 */
	hid_info(hdev, "Registered DualSense controller hw_version=0x%08x fw_version=0x%08x\n",
			ds->base.hw_version, ds->base.fw_version);

	वापस &ds->base;

err:
	ps_devices_list_हटाओ(ps_dev);
	वापस ERR_PTR(ret);
पूर्ण

अटल पूर्णांक ps_raw_event(काष्ठा hid_device *hdev, काष्ठा hid_report *report,
		u8 *data, पूर्णांक size)
अणु
	काष्ठा ps_device *dev = hid_get_drvdata(hdev);

	अगर (dev && dev->parse_report)
		वापस dev->parse_report(dev, report, data, size);

	वापस 0;
पूर्ण

अटल पूर्णांक ps_probe(काष्ठा hid_device *hdev, स्थिर काष्ठा hid_device_id *id)
अणु
	काष्ठा ps_device *dev;
	पूर्णांक ret;

	ret = hid_parse(hdev);
	अगर (ret) अणु
		hid_err(hdev, "Parse failed\n");
		वापस ret;
	पूर्ण

	ret = hid_hw_start(hdev, HID_CONNECT_HIDRAW);
	अगर (ret) अणु
		hid_err(hdev, "Failed to start HID device\n");
		वापस ret;
	पूर्ण

	ret = hid_hw_खोलो(hdev);
	अगर (ret) अणु
		hid_err(hdev, "Failed to open HID device\n");
		जाओ err_stop;
	पूर्ण

	अगर (hdev->product == USB_DEVICE_ID_SONY_PS5_CONTROLLER) अणु
		dev = dualsense_create(hdev);
		अगर (IS_ERR(dev)) अणु
			hid_err(hdev, "Failed to create dualsense.\n");
			ret = PTR_ERR(dev);
			जाओ err_बंद;
		पूर्ण
	पूर्ण

	ret = devm_device_add_group(&hdev->dev, &ps_device_attribute_group);
	अगर (ret) अणु
		hid_err(hdev, "Failed to register sysfs nodes.\n");
		जाओ err_बंद;
	पूर्ण

	वापस ret;

err_बंद:
	hid_hw_बंद(hdev);
err_stop:
	hid_hw_stop(hdev);
	वापस ret;
पूर्ण

अटल व्योम ps_हटाओ(काष्ठा hid_device *hdev)
अणु
	काष्ठा ps_device *dev = hid_get_drvdata(hdev);

	ps_devices_list_हटाओ(dev);
	ps_device_release_player_id(dev);

	hid_hw_बंद(hdev);
	hid_hw_stop(hdev);
पूर्ण

अटल स्थिर काष्ठा hid_device_id ps_devices[] = अणु
	अणु HID_BLUETOOTH_DEVICE(USB_VENDOR_ID_SONY, USB_DEVICE_ID_SONY_PS5_CONTROLLER) पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_SONY, USB_DEVICE_ID_SONY_PS5_CONTROLLER) पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(hid, ps_devices);

अटल काष्ठा hid_driver ps_driver = अणु
	.name		= "playstation",
	.id_table	= ps_devices,
	.probe		= ps_probe,
	.हटाओ		= ps_हटाओ,
	.raw_event	= ps_raw_event,
पूर्ण;

अटल पूर्णांक __init ps_init(व्योम)
अणु
	वापस hid_रेजिस्टर_driver(&ps_driver);
पूर्ण

अटल व्योम __निकास ps_निकास(व्योम)
अणु
	hid_unरेजिस्टर_driver(&ps_driver);
	ida_destroy(&ps_player_id_allocator);
पूर्ण

module_init(ps_init);
module_निकास(ps_निकास);

MODULE_AUTHOR("Sony Interactive Entertainment");
MODULE_DESCRIPTION("HID Driver for PlayStation peripherals.");
MODULE_LICENSE("GPL");
