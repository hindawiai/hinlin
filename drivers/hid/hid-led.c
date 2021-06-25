<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Simple USB RGB LED driver
 *
 * Copyright 2016 Heiner Kallweit <hkallweit1@gmail.com>
 * Based on drivers/hid/hid-thingm.c and
 * drivers/usb/misc/usbled.c
 */

#समावेश <linux/hid.h>
#समावेश <linux/hidraw.h>
#समावेश <linux/leds.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>

#समावेश "hid-ids.h"

क्रमागत hidled_report_type अणु
	RAW_REQUEST,
	OUTPUT_REPORT
पूर्ण;

क्रमागत hidled_type अणु
	RISO_KAGAKU,
	DREAM_CHEEKY,
	THINGM,
	DELCOM,
	LUXAFOR,
पूर्ण;

अटल अचिन्हित स्थिर अक्षर riso_kagaku_tbl[] = अणु
/* R+2G+4B -> riso kagaku color index */
	[0] = 0, /* black   */
	[1] = 2, /* red     */
	[2] = 1, /* green   */
	[3] = 5, /* yellow  */
	[4] = 3, /* blue    */
	[5] = 6, /* magenta */
	[6] = 4, /* cyan    */
	[7] = 7  /* white   */
पूर्ण;

#घोषणा RISO_KAGAKU_IX(r, g, b) riso_kagaku_tbl[((r)?1:0)+((g)?2:0)+((b)?4:0)]

जोड़ delcom_packet अणु
	__u8 data[8];
	काष्ठा अणु
		__u8 major_cmd;
		__u8 minor_cmd;
		__u8 data_lsb;
		__u8 data_msb;
	पूर्ण tx;
	काष्ठा अणु
		__u8 cmd;
	पूर्ण rx;
	काष्ठा अणु
		__le16 family_code;
		__le16 security_code;
		__u8 fw_version;
	पूर्ण fw;
पूर्ण;

#घोषणा DELCOM_GREEN_LED	0
#घोषणा DELCOM_RED_LED		1
#घोषणा DELCOM_BLUE_LED		2

काष्ठा hidled_device;
काष्ठा hidled_rgb;

काष्ठा hidled_config अणु
	क्रमागत hidled_type	type;
	स्थिर अक्षर		*name;
	स्थिर अक्षर		*लघु_name;
	क्रमागत led_brightness	max_brightness;
	पूर्णांक			num_leds;
	माप_प्रकार			report_size;
	क्रमागत hidled_report_type	report_type;
	पूर्णांक (*init)(काष्ठा hidled_device *ldev);
	पूर्णांक (*ग_लिखो)(काष्ठा led_classdev *cdev, क्रमागत led_brightness br);
पूर्ण;

काष्ठा hidled_led अणु
	काष्ठा led_classdev	cdev;
	काष्ठा hidled_rgb	*rgb;
	अक्षर			name[32];
पूर्ण;

काष्ठा hidled_rgb अणु
	काष्ठा hidled_device	*ldev;
	काष्ठा hidled_led	red;
	काष्ठा hidled_led	green;
	काष्ठा hidled_led	blue;
	u8			num;
पूर्ण;

काष्ठा hidled_device अणु
	स्थिर काष्ठा hidled_config *config;
	काष्ठा hid_device       *hdev;
	काष्ठा hidled_rgb	*rgb;
	u8			*buf;
	काष्ठा mutex		lock;
पूर्ण;

#घोषणा MAX_REPORT_SIZE		16

#घोषणा to_hidled_led(arg) container_of(arg, काष्ठा hidled_led, cdev)

अटल bool riso_kagaku_चयन_green_blue;
module_param(riso_kagaku_चयन_green_blue, bool, S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(riso_kagaku_चयन_green_blue,
	"switch green and blue RGB component for Riso Kagaku devices");

अटल पूर्णांक hidled_send(काष्ठा hidled_device *ldev, __u8 *buf)
अणु
	पूर्णांक ret;

	mutex_lock(&ldev->lock);

	/*
	 * buffer provided to hid_hw_raw_request must not be on the stack
	 * and must not be part of a data काष्ठाure
	 */
	स_नकल(ldev->buf, buf, ldev->config->report_size);

	अगर (ldev->config->report_type == RAW_REQUEST)
		ret = hid_hw_raw_request(ldev->hdev, buf[0], ldev->buf,
					 ldev->config->report_size,
					 HID_FEATURE_REPORT,
					 HID_REQ_SET_REPORT);
	अन्यथा अगर (ldev->config->report_type == OUTPUT_REPORT)
		ret = hid_hw_output_report(ldev->hdev, ldev->buf,
					   ldev->config->report_size);
	अन्यथा
		ret = -EINVAL;

	mutex_unlock(&ldev->lock);

	अगर (ret < 0)
		वापस ret;

	वापस ret == ldev->config->report_size ? 0 : -EMSGSIZE;
पूर्ण

/* पढ़ोing data is supported क्रम report type RAW_REQUEST only */
अटल पूर्णांक hidled_recv(काष्ठा hidled_device *ldev, __u8 *buf)
अणु
	पूर्णांक ret;

	अगर (ldev->config->report_type != RAW_REQUEST)
		वापस -EINVAL;

	mutex_lock(&ldev->lock);

	स_नकल(ldev->buf, buf, ldev->config->report_size);

	ret = hid_hw_raw_request(ldev->hdev, buf[0], ldev->buf,
				 ldev->config->report_size,
				 HID_FEATURE_REPORT,
				 HID_REQ_SET_REPORT);
	अगर (ret < 0)
		जाओ err;

	ret = hid_hw_raw_request(ldev->hdev, buf[0], ldev->buf,
				 ldev->config->report_size,
				 HID_FEATURE_REPORT,
				 HID_REQ_GET_REPORT);

	स_नकल(buf, ldev->buf, ldev->config->report_size);
err:
	mutex_unlock(&ldev->lock);

	वापस ret < 0 ? ret : 0;
पूर्ण

अटल u8 riso_kagaku_index(काष्ठा hidled_rgb *rgb)
अणु
	क्रमागत led_brightness r, g, b;

	r = rgb->red.cdev.brightness;
	g = rgb->green.cdev.brightness;
	b = rgb->blue.cdev.brightness;

	अगर (riso_kagaku_चयन_green_blue)
		वापस RISO_KAGAKU_IX(r, b, g);
	अन्यथा
		वापस RISO_KAGAKU_IX(r, g, b);
पूर्ण

अटल पूर्णांक riso_kagaku_ग_लिखो(काष्ठा led_classdev *cdev, क्रमागत led_brightness br)
अणु
	काष्ठा hidled_led *led = to_hidled_led(cdev);
	काष्ठा hidled_rgb *rgb = led->rgb;
	__u8 buf[MAX_REPORT_SIZE] = अणुपूर्ण;

	buf[1] = riso_kagaku_index(rgb);

	वापस hidled_send(rgb->ldev, buf);
पूर्ण

अटल पूर्णांक dream_cheeky_ग_लिखो(काष्ठा led_classdev *cdev, क्रमागत led_brightness br)
अणु
	काष्ठा hidled_led *led = to_hidled_led(cdev);
	काष्ठा hidled_rgb *rgb = led->rgb;
	__u8 buf[MAX_REPORT_SIZE] = अणुपूर्ण;

	buf[1] = rgb->red.cdev.brightness;
	buf[2] = rgb->green.cdev.brightness;
	buf[3] = rgb->blue.cdev.brightness;
	buf[7] = 0x1a;
	buf[8] = 0x05;

	वापस hidled_send(rgb->ldev, buf);
पूर्ण

अटल पूर्णांक dream_cheeky_init(काष्ठा hidled_device *ldev)
अणु
	__u8 buf[MAX_REPORT_SIZE] = अणुपूर्ण;

	/* Dream Cheeky magic */
	buf[1] = 0x1f;
	buf[2] = 0x02;
	buf[4] = 0x5f;
	buf[7] = 0x1a;
	buf[8] = 0x03;

	वापस hidled_send(ldev, buf);
पूर्ण

अटल पूर्णांक _thingm_ग_लिखो(काष्ठा led_classdev *cdev, क्रमागत led_brightness br,
			 u8 offset)
अणु
	काष्ठा hidled_led *led = to_hidled_led(cdev);
	__u8 buf[MAX_REPORT_SIZE] = अणु 1, 'c' पूर्ण;

	buf[2] = led->rgb->red.cdev.brightness;
	buf[3] = led->rgb->green.cdev.brightness;
	buf[4] = led->rgb->blue.cdev.brightness;
	buf[7] = led->rgb->num + offset;

	वापस hidled_send(led->rgb->ldev, buf);
पूर्ण

अटल पूर्णांक thingm_ग_लिखो_v1(काष्ठा led_classdev *cdev, क्रमागत led_brightness br)
अणु
	वापस _thingm_ग_लिखो(cdev, br, 0);
पूर्ण

अटल पूर्णांक thingm_ग_लिखो(काष्ठा led_classdev *cdev, क्रमागत led_brightness br)
अणु
	वापस _thingm_ग_लिखो(cdev, br, 1);
पूर्ण

अटल स्थिर काष्ठा hidled_config hidled_config_thingm_v1 = अणु
	.name = "ThingM blink(1) v1",
	.लघु_name = "thingm",
	.max_brightness = 255,
	.num_leds = 1,
	.report_size = 9,
	.report_type = RAW_REQUEST,
	.ग_लिखो = thingm_ग_लिखो_v1,
पूर्ण;

अटल पूर्णांक thingm_init(काष्ठा hidled_device *ldev)
अणु
	__u8 buf[MAX_REPORT_SIZE] = अणु 1, 'v' पूर्ण;
	पूर्णांक ret;

	ret = hidled_recv(ldev, buf);
	अगर (ret)
		वापस ret;

	/* Check क्रम firmware major version 1 */
	अगर (buf[3] == '1')
		ldev->config = &hidled_config_thingm_v1;

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक delcom_get_lednum(स्थिर काष्ठा hidled_led *led)
अणु
	अगर (led == &led->rgb->red)
		वापस DELCOM_RED_LED;
	अन्यथा अगर (led == &led->rgb->green)
		वापस DELCOM_GREEN_LED;
	अन्यथा
		वापस DELCOM_BLUE_LED;
पूर्ण

अटल पूर्णांक delcom_enable_led(काष्ठा hidled_led *led)
अणु
	जोड़ delcom_packet dp = अणु .tx.major_cmd = 101, .tx.minor_cmd = 12 पूर्ण;

	dp.tx.data_lsb = 1 << delcom_get_lednum(led);
	dp.tx.data_msb = 0;

	वापस hidled_send(led->rgb->ldev, dp.data);
पूर्ण

अटल पूर्णांक delcom_set_pwm(काष्ठा hidled_led *led)
अणु
	जोड़ delcom_packet dp = अणु .tx.major_cmd = 101, .tx.minor_cmd = 34 पूर्ण;

	dp.tx.data_lsb = delcom_get_lednum(led);
	dp.tx.data_msb = led->cdev.brightness;

	वापस hidled_send(led->rgb->ldev, dp.data);
पूर्ण

अटल पूर्णांक delcom_ग_लिखो(काष्ठा led_classdev *cdev, क्रमागत led_brightness br)
अणु
	काष्ठा hidled_led *led = to_hidled_led(cdev);
	पूर्णांक ret;

	/*
	 * enable LED
	 * We can't करो this in the init function alपढ़ोy because the device
	 * is पूर्णांकernally reset later.
	 */
	ret = delcom_enable_led(led);
	अगर (ret)
		वापस ret;

	वापस delcom_set_pwm(led);
पूर्ण

अटल पूर्णांक delcom_init(काष्ठा hidled_device *ldev)
अणु
	जोड़ delcom_packet dp = अणु .rx.cmd = 104 पूर्ण;
	पूर्णांक ret;

	ret = hidled_recv(ldev, dp.data);
	अगर (ret)
		वापस ret;
	/*
	 * Several Delcom devices share the same USB VID/PID
	 * Check क्रम family id 2 क्रम Visual Signal Indicator
	 */
	वापस le16_to_cpu(dp.fw.family_code) == 2 ? 0 : -ENODEV;
पूर्ण

अटल पूर्णांक luxaक्रम_ग_लिखो(काष्ठा led_classdev *cdev, क्रमागत led_brightness br)
अणु
	काष्ठा hidled_led *led = to_hidled_led(cdev);
	__u8 buf[MAX_REPORT_SIZE] = अणु [1] = 1 पूर्ण;

	buf[2] = led->rgb->num + 1;
	buf[3] = led->rgb->red.cdev.brightness;
	buf[4] = led->rgb->green.cdev.brightness;
	buf[5] = led->rgb->blue.cdev.brightness;

	वापस hidled_send(led->rgb->ldev, buf);
पूर्ण

अटल स्थिर काष्ठा hidled_config hidled_configs[] = अणु
	अणु
		.type = RISO_KAGAKU,
		.name = "Riso Kagaku Webmail Notifier",
		.लघु_name = "riso_kagaku",
		.max_brightness = 1,
		.num_leds = 1,
		.report_size = 6,
		.report_type = OUTPUT_REPORT,
		.ग_लिखो = riso_kagaku_ग_लिखो,
	पूर्ण,
	अणु
		.type = DREAM_CHEEKY,
		.name = "Dream Cheeky Webmail Notifier",
		.लघु_name = "dream_cheeky",
		.max_brightness = 31,
		.num_leds = 1,
		.report_size = 9,
		.report_type = RAW_REQUEST,
		.init = dream_cheeky_init,
		.ग_लिखो = dream_cheeky_ग_लिखो,
	पूर्ण,
	अणु
		.type = THINGM,
		.name = "ThingM blink(1)",
		.लघु_name = "thingm",
		.max_brightness = 255,
		.num_leds = 2,
		.report_size = 9,
		.report_type = RAW_REQUEST,
		.init = thingm_init,
		.ग_लिखो = thingm_ग_लिखो,
	पूर्ण,
	अणु
		.type = DELCOM,
		.name = "Delcom Visual Signal Indicator G2",
		.लघु_name = "delcom",
		.max_brightness = 100,
		.num_leds = 1,
		.report_size = 8,
		.report_type = RAW_REQUEST,
		.init = delcom_init,
		.ग_लिखो = delcom_ग_लिखो,
	पूर्ण,
	अणु
		.type = LUXAFOR,
		.name = "Greynut Luxafor",
		.लघु_name = "luxafor",
		.max_brightness = 255,
		.num_leds = 6,
		.report_size = 9,
		.report_type = OUTPUT_REPORT,
		.ग_लिखो = luxaक्रम_ग_लिखो,
	पूर्ण,
पूर्ण;

अटल पूर्णांक hidled_init_led(काष्ठा hidled_led *led, स्थिर अक्षर *color_name,
			   काष्ठा hidled_rgb *rgb, अचिन्हित पूर्णांक minor)
अणु
	स्थिर काष्ठा hidled_config *config = rgb->ldev->config;

	अगर (config->num_leds > 1)
		snम_लिखो(led->name, माप(led->name), "%s%u:%s:led%u",
			 config->लघु_name, minor, color_name, rgb->num);
	अन्यथा
		snम_लिखो(led->name, माप(led->name), "%s%u:%s",
			 config->लघु_name, minor, color_name);
	led->cdev.name = led->name;
	led->cdev.max_brightness = config->max_brightness;
	led->cdev.brightness_set_blocking = config->ग_लिखो;
	led->cdev.flags = LED_HW_PLUGGABLE;
	led->rgb = rgb;

	वापस devm_led_classdev_रेजिस्टर(&rgb->ldev->hdev->dev, &led->cdev);
पूर्ण

अटल पूर्णांक hidled_init_rgb(काष्ठा hidled_rgb *rgb, अचिन्हित पूर्णांक minor)
अणु
	पूर्णांक ret;

	/* Register the red diode */
	ret = hidled_init_led(&rgb->red, "red", rgb, minor);
	अगर (ret)
		वापस ret;

	/* Register the green diode */
	ret = hidled_init_led(&rgb->green, "green", rgb, minor);
	अगर (ret)
		वापस ret;

	/* Register the blue diode */
	वापस hidled_init_led(&rgb->blue, "blue", rgb, minor);
पूर्ण

अटल पूर्णांक hidled_probe(काष्ठा hid_device *hdev, स्थिर काष्ठा hid_device_id *id)
अणु
	काष्ठा hidled_device *ldev;
	अचिन्हित पूर्णांक minor;
	पूर्णांक ret, i;

	ldev = devm_kzalloc(&hdev->dev, माप(*ldev), GFP_KERNEL);
	अगर (!ldev)
		वापस -ENOMEM;

	ldev->buf = devm_kदो_स्मृति(&hdev->dev, MAX_REPORT_SIZE, GFP_KERNEL);
	अगर (!ldev->buf)
		वापस -ENOMEM;

	ret = hid_parse(hdev);
	अगर (ret)
		वापस ret;

	ldev->hdev = hdev;
	mutex_init(&ldev->lock);

	क्रम (i = 0; !ldev->config && i < ARRAY_SIZE(hidled_configs); i++)
		अगर (hidled_configs[i].type == id->driver_data)
			ldev->config = &hidled_configs[i];

	अगर (!ldev->config)
		वापस -EINVAL;

	अगर (ldev->config->init) अणु
		ret = ldev->config->init(ldev);
		अगर (ret)
			वापस ret;
	पूर्ण

	ldev->rgb = devm_kसुस्मृति(&hdev->dev, ldev->config->num_leds,
				 माप(काष्ठा hidled_rgb), GFP_KERNEL);
	अगर (!ldev->rgb)
		वापस -ENOMEM;

	ret = hid_hw_start(hdev, HID_CONNECT_HIDRAW);
	अगर (ret)
		वापस ret;

	minor = ((काष्ठा hidraw *) hdev->hidraw)->minor;

	क्रम (i = 0; i < ldev->config->num_leds; i++) अणु
		ldev->rgb[i].ldev = ldev;
		ldev->rgb[i].num = i;
		ret = hidled_init_rgb(&ldev->rgb[i], minor);
		अगर (ret) अणु
			hid_hw_stop(hdev);
			वापस ret;
		पूर्ण
	पूर्ण

	hid_info(hdev, "%s initialized\n", ldev->config->name);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा hid_device_id hidled_table[] = अणु
	अणु HID_USB_DEVICE(USB_VENDOR_ID_RISO_KAGAKU,
	  USB_DEVICE_ID_RI_KA_WEBMAIL), .driver_data = RISO_KAGAKU पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_DREAM_CHEEKY,
	  USB_DEVICE_ID_DREAM_CHEEKY_WN), .driver_data = DREAM_CHEEKY पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_DREAM_CHEEKY,
	  USB_DEVICE_ID_DREAM_CHEEKY_FA), .driver_data = DREAM_CHEEKY पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_THINGM,
	  USB_DEVICE_ID_BLINK1), .driver_data = THINGM पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_DELCOM,
	  USB_DEVICE_ID_DELCOM_VISUAL_IND), .driver_data = DELCOM पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_MICROCHIP,
	  USB_DEVICE_ID_LUXAFOR), .driver_data = LUXAFOR पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(hid, hidled_table);

अटल काष्ठा hid_driver hidled_driver = अणु
	.name = "hid-led",
	.probe = hidled_probe,
	.id_table = hidled_table,
पूर्ण;

module_hid_driver(hidled_driver);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Heiner Kallweit <hkallweit1@gmail.com>");
MODULE_DESCRIPTION("Simple USB RGB LED driver");
