<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  HID driver क्रम Steअन्यथाries SRW-S1
 *
 *  Copyright (c) 2013 Simon Wood
 */

/*
 */

#समावेश <linux/device.h>
#समावेश <linux/hid.h>
#समावेश <linux/module.h>

#समावेश "hid-ids.h"

#अगर IS_BUILTIN(CONFIG_LEDS_CLASS) || \
    (IS_MODULE(CONFIG_LEDS_CLASS) && IS_MODULE(CONFIG_HID_STEELSERIES))
#घोषणा SRWS1_NUMBER_LEDS 15
काष्ठा steअन्यथाries_srws1_data अणु
	__u16 led_state;
	/* the last element is used क्रम setting all leds simultaneously */
	काष्ठा led_classdev *led[SRWS1_NUMBER_LEDS + 1];
पूर्ण;
#पूर्ण_अगर

/* Fixed report descriptor क्रम Steअन्यथाries SRW-S1 wheel controller
 *
 * The original descriptor hides the sensitivity and assists dials
 * a custom venकरोr usage page. This inserts a patch to make them
 * appear in the 'Generic Desktop' usage.
 */

अटल __u8 steअन्यथाries_srws1_rdesc_fixed[] = अणु
0x05, 0x01,         /*  Usage Page (Desktop)                */
0x09, 0x08,         /*  Usage (MultiAxis), Changed          */
0xA1, 0x01,         /*  Collection (Application),           */
0xA1, 0x02,         /*      Collection (Logical),           */
0x95, 0x01,         /*          Report Count (1),           */
0x05, 0x01,         /* Changed  Usage Page (Desktop),       */
0x09, 0x30,         /* Changed  Usage (X),                  */
0x16, 0xF8, 0xF8,   /*          Logical Minimum (-1800),    */
0x26, 0x08, 0x07,   /*          Logical Maximum (1800),     */
0x65, 0x14,         /*          Unit (Degrees),             */
0x55, 0x0F,         /*          Unit Exponent (15),         */
0x75, 0x10,         /*          Report Size (16),           */
0x81, 0x02,         /*          Input (Variable),           */
0x09, 0x31,         /* Changed  Usage (Y),                  */
0x15, 0x00,         /*          Logical Minimum (0),        */
0x26, 0xFF, 0x03,   /*          Logical Maximum (1023),     */
0x75, 0x0C,         /*          Report Size (12),           */
0x81, 0x02,         /*          Input (Variable),           */
0x09, 0x32,         /* Changed  Usage (Z),                  */
0x15, 0x00,         /*          Logical Minimum (0),        */
0x26, 0xFF, 0x03,   /*          Logical Maximum (1023),     */
0x75, 0x0C,         /*          Report Size (12),           */
0x81, 0x02,         /*          Input (Variable),           */
0x05, 0x01,         /*          Usage Page (Desktop),       */
0x09, 0x39,         /*          Usage (Hat Switch),         */
0x25, 0x07,         /*          Logical Maximum (7),        */
0x35, 0x00,         /*          Physical Minimum (0),       */
0x46, 0x3B, 0x01,   /*          Physical Maximum (315),     */
0x65, 0x14,         /*          Unit (Degrees),             */
0x75, 0x04,         /*          Report Size (4),            */
0x95, 0x01,         /*          Report Count (1),           */
0x81, 0x02,         /*          Input (Variable),           */
0x25, 0x01,         /*          Logical Maximum (1),        */
0x45, 0x01,         /*          Physical Maximum (1),       */
0x65, 0x00,         /*          Unit,                       */
0x75, 0x01,         /*          Report Size (1),            */
0x95, 0x03,         /*          Report Count (3),           */
0x81, 0x01,         /*          Input (Constant),           */
0x05, 0x09,         /*          Usage Page (Button),        */
0x19, 0x01,         /*          Usage Minimum (01h),        */
0x29, 0x11,         /*          Usage Maximum (11h),        */
0x95, 0x11,         /*          Report Count (17),          */
0x81, 0x02,         /*          Input (Variable),           */
                    /*   ---- Dial patch starts here ----   */
0x05, 0x01,         /*          Usage Page (Desktop),       */
0x09, 0x33,         /*          Usage (RX),                 */
0x75, 0x04,         /*          Report Size (4),            */
0x95, 0x02,         /*          Report Count (2),           */
0x15, 0x00,         /*          Logical Minimum (0),        */
0x25, 0x0b,         /*          Logical Maximum (b),        */
0x81, 0x02,         /*          Input (Variable),           */
0x09, 0x35,         /*          Usage (RZ),                 */
0x75, 0x04,         /*          Report Size (4),            */
0x95, 0x01,         /*          Report Count (1),           */
0x25, 0x03,         /*          Logical Maximum (3),        */
0x81, 0x02,         /*          Input (Variable),           */
                    /*    ---- Dial patch ends here ----    */
0x06, 0x00, 0xFF,   /*          Usage Page (FF00h),         */
0x09, 0x01,         /*          Usage (01h),                */
0x75, 0x04,         /* Changed  Report Size (4),            */
0x95, 0x0D,         /* Changed  Report Count (13),          */
0x81, 0x02,         /*          Input (Variable),           */
0xC0,               /*      End Collection,                 */
0xA1, 0x02,         /*      Collection (Logical),           */
0x09, 0x02,         /*          Usage (02h),                */
0x75, 0x08,         /*          Report Size (8),            */
0x95, 0x10,         /*          Report Count (16),          */
0x91, 0x02,         /*          Output (Variable),          */
0xC0,               /*      End Collection,                 */
0xC0                /*  End Collection                      */
पूर्ण;

#अगर IS_BUILTIN(CONFIG_LEDS_CLASS) || \
    (IS_MODULE(CONFIG_LEDS_CLASS) && IS_MODULE(CONFIG_HID_STEELSERIES))
अटल व्योम steअन्यथाries_srws1_set_leds(काष्ठा hid_device *hdev, __u16 leds)
अणु
	काष्ठा list_head *report_list = &hdev->report_क्रमागत[HID_OUTPUT_REPORT].report_list;
	काष्ठा hid_report *report = list_entry(report_list->next, काष्ठा hid_report, list);
	__s32 *value = report->field[0]->value;

	value[0] = 0x40;
	value[1] = leds & 0xFF;
	value[2] = leds >> 8;
	value[3] = 0x00;
	value[4] = 0x00;
	value[5] = 0x00;
	value[6] = 0x00;
	value[7] = 0x00;
	value[8] = 0x00;
	value[9] = 0x00;
	value[10] = 0x00;
	value[11] = 0x00;
	value[12] = 0x00;
	value[13] = 0x00;
	value[14] = 0x00;
	value[15] = 0x00;

	hid_hw_request(hdev, report, HID_REQ_SET_REPORT);

	/* Note: LED change करोes not show on device until the device is पढ़ो/polled */
पूर्ण

अटल व्योम steअन्यथाries_srws1_led_all_set_brightness(काष्ठा led_classdev *led_cdev,
			क्रमागत led_brightness value)
अणु
	काष्ठा device *dev = led_cdev->dev->parent;
	काष्ठा hid_device *hid = to_hid_device(dev);
	काष्ठा steअन्यथाries_srws1_data *drv_data = hid_get_drvdata(hid);

	अगर (!drv_data) अणु
		hid_err(hid, "Device data not found.");
		वापस;
	पूर्ण

	अगर (value == LED_OFF)
		drv_data->led_state = 0;
	अन्यथा
		drv_data->led_state = (1 << (SRWS1_NUMBER_LEDS + 1)) - 1;

	steअन्यथाries_srws1_set_leds(hid, drv_data->led_state);
पूर्ण

अटल क्रमागत led_brightness steअन्यथाries_srws1_led_all_get_brightness(काष्ठा led_classdev *led_cdev)
अणु
	काष्ठा device *dev = led_cdev->dev->parent;
	काष्ठा hid_device *hid = to_hid_device(dev);
	काष्ठा steअन्यथाries_srws1_data *drv_data;

	drv_data = hid_get_drvdata(hid);

	अगर (!drv_data) अणु
		hid_err(hid, "Device data not found.");
		वापस LED_OFF;
	पूर्ण

	वापस (drv_data->led_state >> SRWS1_NUMBER_LEDS) ? LED_FULL : LED_OFF;
पूर्ण

अटल व्योम steअन्यथाries_srws1_led_set_brightness(काष्ठा led_classdev *led_cdev,
			क्रमागत led_brightness value)
अणु
	काष्ठा device *dev = led_cdev->dev->parent;
	काष्ठा hid_device *hid = to_hid_device(dev);
	काष्ठा steअन्यथाries_srws1_data *drv_data = hid_get_drvdata(hid);
	पूर्णांक i, state = 0;

	अगर (!drv_data) अणु
		hid_err(hid, "Device data not found.");
		वापस;
	पूर्ण

	क्रम (i = 0; i < SRWS1_NUMBER_LEDS; i++) अणु
		अगर (led_cdev != drv_data->led[i])
			जारी;

		state = (drv_data->led_state >> i) & 1;
		अगर (value == LED_OFF && state) अणु
			drv_data->led_state &= ~(1 << i);
			steअन्यथाries_srws1_set_leds(hid, drv_data->led_state);
		पूर्ण अन्यथा अगर (value != LED_OFF && !state) अणु
			drv_data->led_state |= 1 << i;
			steअन्यथाries_srws1_set_leds(hid, drv_data->led_state);
		पूर्ण
		अवरोध;
	पूर्ण
पूर्ण

अटल क्रमागत led_brightness steअन्यथाries_srws1_led_get_brightness(काष्ठा led_classdev *led_cdev)
अणु
	काष्ठा device *dev = led_cdev->dev->parent;
	काष्ठा hid_device *hid = to_hid_device(dev);
	काष्ठा steअन्यथाries_srws1_data *drv_data;
	पूर्णांक i, value = 0;

	drv_data = hid_get_drvdata(hid);

	अगर (!drv_data) अणु
		hid_err(hid, "Device data not found.");
		वापस LED_OFF;
	पूर्ण

	क्रम (i = 0; i < SRWS1_NUMBER_LEDS; i++)
		अगर (led_cdev == drv_data->led[i]) अणु
			value = (drv_data->led_state >> i) & 1;
			अवरोध;
		पूर्ण

	वापस value ? LED_FULL : LED_OFF;
पूर्ण

अटल पूर्णांक steअन्यथाries_srws1_probe(काष्ठा hid_device *hdev,
		स्थिर काष्ठा hid_device_id *id)
अणु
	पूर्णांक ret, i;
	काष्ठा led_classdev *led;
	माप_प्रकार name_sz;
	अक्षर *name;

	काष्ठा steअन्यथाries_srws1_data *drv_data = kzalloc(माप(*drv_data), GFP_KERNEL);

	अगर (drv_data == शून्य) अणु
		hid_err(hdev, "can't alloc SRW-S1 memory\n");
		वापस -ENOMEM;
	पूर्ण

	hid_set_drvdata(hdev, drv_data);

	ret = hid_parse(hdev);
	अगर (ret) अणु
		hid_err(hdev, "parse failed\n");
		जाओ err_मुक्त;
	पूर्ण

	अगर (!hid_validate_values(hdev, HID_OUTPUT_REPORT, 0, 0, 16)) अणु
		ret = -ENODEV;
		जाओ err_मुक्त;
	पूर्ण

	ret = hid_hw_start(hdev, HID_CONNECT_DEFAULT);
	अगर (ret) अणु
		hid_err(hdev, "hw start failed\n");
		जाओ err_मुक्त;
	पूर्ण

	/* रेजिस्टर led subप्रणाली */
	drv_data->led_state = 0;
	क्रम (i = 0; i < SRWS1_NUMBER_LEDS + 1; i++)
		drv_data->led[i] = शून्य;

	steअन्यथाries_srws1_set_leds(hdev, 0);

	name_sz = म_माप(hdev->uniq) + 16;

	/* 'ALL', क्रम setting all LEDs simultaneously */
	led = kzalloc(माप(काष्ठा led_classdev)+name_sz, GFP_KERNEL);
	अगर (!led) अणु
		hid_err(hdev, "can't allocate memory for LED ALL\n");
		जाओ err_led;
	पूर्ण

	name = (व्योम *)(&led[1]);
	snम_लिखो(name, name_sz, "SRWS1::%s::RPMALL", hdev->uniq);
	led->name = name;
	led->brightness = 0;
	led->max_brightness = 1;
	led->brightness_get = steअन्यथाries_srws1_led_all_get_brightness;
	led->brightness_set = steअन्यथाries_srws1_led_all_set_brightness;

	drv_data->led[SRWS1_NUMBER_LEDS] = led;
	ret = led_classdev_रेजिस्टर(&hdev->dev, led);
	अगर (ret)
		जाओ err_led;

	/* Each inभागidual LED */
	क्रम (i = 0; i < SRWS1_NUMBER_LEDS; i++) अणु
		led = kzalloc(माप(काष्ठा led_classdev)+name_sz, GFP_KERNEL);
		अगर (!led) अणु
			hid_err(hdev, "can't allocate memory for LED %d\n", i);
			जाओ err_led;
		पूर्ण

		name = (व्योम *)(&led[1]);
		snम_लिखो(name, name_sz, "SRWS1::%s::RPM%d", hdev->uniq, i+1);
		led->name = name;
		led->brightness = 0;
		led->max_brightness = 1;
		led->brightness_get = steअन्यथाries_srws1_led_get_brightness;
		led->brightness_set = steअन्यथाries_srws1_led_set_brightness;

		drv_data->led[i] = led;
		ret = led_classdev_रेजिस्टर(&hdev->dev, led);

		अगर (ret) अणु
			hid_err(hdev, "failed to register LED %d. Aborting.\n", i);
err_led:
			/* Deरेजिस्टर all LEDs (अगर any) */
			क्रम (i = 0; i < SRWS1_NUMBER_LEDS + 1; i++) अणु
				led = drv_data->led[i];
				drv_data->led[i] = शून्य;
				अगर (!led)
					जारी;
				led_classdev_unरेजिस्टर(led);
				kमुक्त(led);
			पूर्ण
			जाओ out;	/* but let the driver जारी without LEDs */
		पूर्ण
	पूर्ण
out:
	वापस 0;
err_मुक्त:
	kमुक्त(drv_data);
	वापस ret;
पूर्ण

अटल व्योम steअन्यथाries_srws1_हटाओ(काष्ठा hid_device *hdev)
अणु
	पूर्णांक i;
	काष्ठा led_classdev *led;

	काष्ठा steअन्यथाries_srws1_data *drv_data = hid_get_drvdata(hdev);

	अगर (drv_data) अणु
		/* Deरेजिस्टर LEDs (अगर any) */
		क्रम (i = 0; i < SRWS1_NUMBER_LEDS + 1; i++) अणु
			led = drv_data->led[i];
			drv_data->led[i] = शून्य;
			अगर (!led)
				जारी;
			led_classdev_unरेजिस्टर(led);
			kमुक्त(led);
		पूर्ण

	पूर्ण

	hid_hw_stop(hdev);
	kमुक्त(drv_data);
	वापस;
पूर्ण
#पूर्ण_अगर

अटल __u8 *steअन्यथाries_srws1_report_fixup(काष्ठा hid_device *hdev, __u8 *rdesc,
		अचिन्हित पूर्णांक *rsize)
अणु
	अगर (*rsize >= 115 && rdesc[11] == 0x02 && rdesc[13] == 0xc8
			&& rdesc[29] == 0xbb && rdesc[40] == 0xc5) अणु
		hid_info(hdev, "Fixing up Steelseries SRW-S1 report descriptor\n");
		rdesc = steअन्यथाries_srws1_rdesc_fixed;
		*rsize = माप(steअन्यथाries_srws1_rdesc_fixed);
	पूर्ण
	वापस rdesc;
पूर्ण

अटल स्थिर काष्ठा hid_device_id steअन्यथाries_srws1_devices[] = अणु
	अणु HID_USB_DEVICE(USB_VENDOR_ID_STEELSERIES, USB_DEVICE_ID_STEELSERIES_SRWS1) पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(hid, steअन्यथाries_srws1_devices);

अटल काष्ठा hid_driver steअन्यथाries_srws1_driver = अणु
	.name = "steelseries_srws1",
	.id_table = steअन्यथाries_srws1_devices,
#अगर IS_BUILTIN(CONFIG_LEDS_CLASS) || \
    (IS_MODULE(CONFIG_LEDS_CLASS) && IS_MODULE(CONFIG_HID_STEELSERIES))
	.probe = steअन्यथाries_srws1_probe,
	.हटाओ = steअन्यथाries_srws1_हटाओ,
#पूर्ण_अगर
	.report_fixup = steअन्यथाries_srws1_report_fixup
पूर्ण;

module_hid_driver(steअन्यथाries_srws1_driver);
MODULE_LICENSE("GPL");
