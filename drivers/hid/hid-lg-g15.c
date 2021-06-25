<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 *  HID driver क्रम gaming keys on Logitech gaming keyboards (such as the G15)
 *
 *  Copyright (c) 2019 Hans de Goede <hdegoede@redhat.com>
 */

#समावेश <linux/device.h>
#समावेश <linux/hid.h>
#समावेश <linux/module.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/sched.h>
#समावेश <linux/usb.h>
#समावेश <linux/रुको.h>

#समावेश "hid-ids.h"

#घोषणा LG_G15_TRANSFER_BUF_SIZE	20

#घोषणा LG_G15_FEATURE_REPORT		0x02

#घोषणा LG_G510_FEATURE_M_KEYS_LEDS	0x04
#घोषणा LG_G510_FEATURE_BACKLIGHT_RGB	0x05
#घोषणा LG_G510_FEATURE_POWER_ON_RGB	0x06

क्रमागत lg_g15_model अणु
	LG_G15,
	LG_G15_V2,
	LG_G510,
	LG_G510_USB_AUDIO,
पूर्ण;

क्रमागत lg_g15_led_type अणु
	LG_G15_KBD_BRIGHTNESS,
	LG_G15_LCD_BRIGHTNESS,
	LG_G15_BRIGHTNESS_MAX,
	LG_G15_MACRO_PRESET1 = 2,
	LG_G15_MACRO_PRESET2,
	LG_G15_MACRO_PRESET3,
	LG_G15_MACRO_RECORD,
	LG_G15_LED_MAX
पूर्ण;

काष्ठा lg_g15_led अणु
	काष्ठा led_classdev cdev;
	क्रमागत led_brightness brightness;
	क्रमागत lg_g15_led_type led;
	u8 red, green, blue;
पूर्ण;

काष्ठा lg_g15_data अणु
	/* Must be first क्रम proper dma alignment */
	u8 transfer_buf[LG_G15_TRANSFER_BUF_SIZE];
	/* Protects the transfer_buf and led brightness */
	काष्ठा mutex mutex;
	काष्ठा work_काष्ठा work;
	काष्ठा input_dev *input;
	काष्ठा hid_device *hdev;
	क्रमागत lg_g15_model model;
	काष्ठा lg_g15_led leds[LG_G15_LED_MAX];
	bool game_mode_enabled;
पूर्ण;

/******** G15 and G15 v2 LED functions ********/

अटल पूर्णांक lg_g15_update_led_brightness(काष्ठा lg_g15_data *g15)
अणु
	पूर्णांक ret;

	ret = hid_hw_raw_request(g15->hdev, LG_G15_FEATURE_REPORT,
				 g15->transfer_buf, 4,
				 HID_FEATURE_REPORT, HID_REQ_GET_REPORT);
	अगर (ret != 4) अणु
		hid_err(g15->hdev, "Error getting LED brightness: %d\n", ret);
		वापस (ret < 0) ? ret : -EIO;
	पूर्ण

	g15->leds[LG_G15_KBD_BRIGHTNESS].brightness = g15->transfer_buf[1];
	g15->leds[LG_G15_LCD_BRIGHTNESS].brightness = g15->transfer_buf[2];

	g15->leds[LG_G15_MACRO_PRESET1].brightness =
		!(g15->transfer_buf[3] & 0x01);
	g15->leds[LG_G15_MACRO_PRESET2].brightness =
		!(g15->transfer_buf[3] & 0x02);
	g15->leds[LG_G15_MACRO_PRESET3].brightness =
		!(g15->transfer_buf[3] & 0x04);
	g15->leds[LG_G15_MACRO_RECORD].brightness =
		!(g15->transfer_buf[3] & 0x08);

	वापस 0;
पूर्ण

अटल क्रमागत led_brightness lg_g15_led_get(काष्ठा led_classdev *led_cdev)
अणु
	काष्ठा lg_g15_led *g15_led =
		container_of(led_cdev, काष्ठा lg_g15_led, cdev);
	काष्ठा lg_g15_data *g15 = dev_get_drvdata(led_cdev->dev->parent);
	क्रमागत led_brightness brightness;

	mutex_lock(&g15->mutex);
	lg_g15_update_led_brightness(g15);
	brightness = g15->leds[g15_led->led].brightness;
	mutex_unlock(&g15->mutex);

	वापस brightness;
पूर्ण

अटल पूर्णांक lg_g15_led_set(काष्ठा led_classdev *led_cdev,
			  क्रमागत led_brightness brightness)
अणु
	काष्ठा lg_g15_led *g15_led =
		container_of(led_cdev, काष्ठा lg_g15_led, cdev);
	काष्ठा lg_g15_data *g15 = dev_get_drvdata(led_cdev->dev->parent);
	u8 val, mask = 0;
	पूर्णांक i, ret;

	/* Ignore LED off on unरेजिस्टर / keyboard unplug */
	अगर (led_cdev->flags & LED_UNREGISTERING)
		वापस 0;

	mutex_lock(&g15->mutex);

	g15->transfer_buf[0] = LG_G15_FEATURE_REPORT;
	g15->transfer_buf[3] = 0;

	अगर (g15_led->led < LG_G15_BRIGHTNESS_MAX) अणु
		g15->transfer_buf[1] = g15_led->led + 1;
		g15->transfer_buf[2] = brightness << (g15_led->led * 4);
	पूर्ण अन्यथा अणु
		क्रम (i = LG_G15_MACRO_PRESET1; i < LG_G15_LED_MAX; i++) अणु
			अगर (i == g15_led->led)
				val = brightness;
			अन्यथा
				val = g15->leds[i].brightness;

			अगर (val)
				mask |= 1 << (i - LG_G15_MACRO_PRESET1);
		पूर्ण

		g15->transfer_buf[1] = 0x04;
		g15->transfer_buf[2] = ~mask;
	पूर्ण

	ret = hid_hw_raw_request(g15->hdev, LG_G15_FEATURE_REPORT,
				 g15->transfer_buf, 4,
				 HID_FEATURE_REPORT, HID_REQ_SET_REPORT);
	अगर (ret == 4) अणु
		/* Success */
		g15_led->brightness = brightness;
		ret = 0;
	पूर्ण अन्यथा अणु
		hid_err(g15->hdev, "Error setting LED brightness: %d\n", ret);
		ret = (ret < 0) ? ret : -EIO;
	पूर्ण

	mutex_unlock(&g15->mutex);

	वापस ret;
पूर्ण

अटल व्योम lg_g15_leds_changed_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा lg_g15_data *g15 = container_of(work, काष्ठा lg_g15_data, work);
	क्रमागत led_brightness old_brightness[LG_G15_BRIGHTNESS_MAX];
	क्रमागत led_brightness brightness[LG_G15_BRIGHTNESS_MAX];
	पूर्णांक i, ret;

	mutex_lock(&g15->mutex);
	क्रम (i = 0; i < LG_G15_BRIGHTNESS_MAX; i++)
		old_brightness[i] = g15->leds[i].brightness;

	ret = lg_g15_update_led_brightness(g15);

	क्रम (i = 0; i < LG_G15_BRIGHTNESS_MAX; i++)
		brightness[i] = g15->leds[i].brightness;
	mutex_unlock(&g15->mutex);

	अगर (ret)
		वापस;

	क्रम (i = 0; i < LG_G15_BRIGHTNESS_MAX; i++) अणु
		अगर (brightness[i] == old_brightness[i])
			जारी;

		led_classdev_notअगरy_brightness_hw_changed(&g15->leds[i].cdev,
							  brightness[i]);
	पूर्ण
पूर्ण

/******** G510 LED functions ********/

अटल पूर्णांक lg_g510_get_initial_led_brightness(काष्ठा lg_g15_data *g15, पूर्णांक i)
अणु
	पूर्णांक ret, high;

	ret = hid_hw_raw_request(g15->hdev, LG_G510_FEATURE_BACKLIGHT_RGB + i,
				 g15->transfer_buf, 4,
				 HID_FEATURE_REPORT, HID_REQ_GET_REPORT);
	अगर (ret != 4) अणु
		hid_err(g15->hdev, "Error getting LED brightness: %d\n", ret);
		वापस (ret < 0) ? ret : -EIO;
	पूर्ण

	high = max3(g15->transfer_buf[1], g15->transfer_buf[2],
		    g15->transfer_buf[3]);

	अगर (high) अणु
		g15->leds[i].red =
			DIV_ROUND_CLOSEST(g15->transfer_buf[1] * 255, high);
		g15->leds[i].green =
			DIV_ROUND_CLOSEST(g15->transfer_buf[2] * 255, high);
		g15->leds[i].blue =
			DIV_ROUND_CLOSEST(g15->transfer_buf[3] * 255, high);
		g15->leds[i].brightness = high;
	पूर्ण अन्यथा अणु
		g15->leds[i].red   = 255;
		g15->leds[i].green = 255;
		g15->leds[i].blue  = 255;
		g15->leds[i].brightness = 0;
	पूर्ण

	वापस 0;
पूर्ण

/* Must be called with g15->mutex locked */
अटल पूर्णांक lg_g510_kbd_led_ग_लिखो(काष्ठा lg_g15_data *g15,
				 काष्ठा lg_g15_led *g15_led,
				 क्रमागत led_brightness brightness)
अणु
	पूर्णांक ret;

	g15->transfer_buf[0] = 5 + g15_led->led;
	g15->transfer_buf[1] =
		DIV_ROUND_CLOSEST(g15_led->red * brightness, 255);
	g15->transfer_buf[2] =
		DIV_ROUND_CLOSEST(g15_led->green * brightness, 255);
	g15->transfer_buf[3] =
		DIV_ROUND_CLOSEST(g15_led->blue * brightness, 255);

	ret = hid_hw_raw_request(g15->hdev,
				 LG_G510_FEATURE_BACKLIGHT_RGB + g15_led->led,
				 g15->transfer_buf, 4,
				 HID_FEATURE_REPORT, HID_REQ_SET_REPORT);
	अगर (ret == 4) अणु
		/* Success */
		g15_led->brightness = brightness;
		ret = 0;
	पूर्ण अन्यथा अणु
		hid_err(g15->hdev, "Error setting LED brightness: %d\n", ret);
		ret = (ret < 0) ? ret : -EIO;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक lg_g510_kbd_led_set(काष्ठा led_classdev *led_cdev,
			       क्रमागत led_brightness brightness)
अणु
	काष्ठा lg_g15_led *g15_led =
		container_of(led_cdev, काष्ठा lg_g15_led, cdev);
	काष्ठा lg_g15_data *g15 = dev_get_drvdata(led_cdev->dev->parent);
	पूर्णांक ret;

	/* Ignore LED off on unरेजिस्टर / keyboard unplug */
	अगर (led_cdev->flags & LED_UNREGISTERING)
		वापस 0;

	mutex_lock(&g15->mutex);
	ret = lg_g510_kbd_led_ग_लिखो(g15, g15_led, brightness);
	mutex_unlock(&g15->mutex);

	वापस ret;
पूर्ण

अटल क्रमागत led_brightness lg_g510_kbd_led_get(काष्ठा led_classdev *led_cdev)
अणु
	काष्ठा lg_g15_led *g15_led =
		container_of(led_cdev, काष्ठा lg_g15_led, cdev);

	वापस g15_led->brightness;
पूर्ण

अटल sमाप_प्रकार color_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
			   स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा led_classdev *led_cdev = dev_get_drvdata(dev);
	काष्ठा lg_g15_led *g15_led =
		container_of(led_cdev, काष्ठा lg_g15_led, cdev);
	काष्ठा lg_g15_data *g15 = dev_get_drvdata(led_cdev->dev->parent);
	अचिन्हित दीर्घ value;
	पूर्णांक ret;

	अगर (count < 7 || (count == 8 && buf[7] != '\n') || count > 8)
		वापस -EINVAL;

	अगर (buf[0] != '#')
		वापस -EINVAL;

	ret = kम_से_अदीर्घ(buf + 1, 16, &value);
	अगर (ret)
		वापस ret;

	mutex_lock(&g15->mutex);
	g15_led->red   = (value & 0xff0000) >> 16;
	g15_led->green = (value & 0x00ff00) >> 8;
	g15_led->blue  = (value & 0x0000ff);
	ret = lg_g510_kbd_led_ग_लिखो(g15, g15_led, g15_led->brightness);
	mutex_unlock(&g15->mutex);

	वापस (ret < 0) ? ret : count;
पूर्ण

अटल sमाप_प्रकार color_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			  अक्षर *buf)
अणु
	काष्ठा led_classdev *led_cdev = dev_get_drvdata(dev);
	काष्ठा lg_g15_led *g15_led =
		container_of(led_cdev, काष्ठा lg_g15_led, cdev);
	काष्ठा lg_g15_data *g15 = dev_get_drvdata(led_cdev->dev->parent);
	sमाप_प्रकार ret;

	mutex_lock(&g15->mutex);
	ret = प्र_लिखो(buf, "#%02x%02x%02x\n",
		      g15_led->red, g15_led->green, g15_led->blue);
	mutex_unlock(&g15->mutex);

	वापस ret;
पूर्ण

अटल DEVICE_ATTR_RW(color);

अटल काष्ठा attribute *lg_g510_kbd_led_attrs[] = अणु
	&dev_attr_color.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group lg_g510_kbd_led_group = अणु
	.attrs = lg_g510_kbd_led_attrs,
पूर्ण;

अटल स्थिर काष्ठा attribute_group *lg_g510_kbd_led_groups[] = अणु
	&lg_g510_kbd_led_group,
	शून्य,
पूर्ण;

अटल व्योम lg_g510_leds_sync_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा lg_g15_data *g15 = container_of(work, काष्ठा lg_g15_data, work);

	mutex_lock(&g15->mutex);
	lg_g510_kbd_led_ग_लिखो(g15, &g15->leds[LG_G15_KBD_BRIGHTNESS],
			      g15->leds[LG_G15_KBD_BRIGHTNESS].brightness);
	mutex_unlock(&g15->mutex);
पूर्ण

अटल पूर्णांक lg_g510_update_mkey_led_brightness(काष्ठा lg_g15_data *g15)
अणु
	पूर्णांक ret;

	ret = hid_hw_raw_request(g15->hdev, LG_G510_FEATURE_M_KEYS_LEDS,
				 g15->transfer_buf, 2,
				 HID_FEATURE_REPORT, HID_REQ_GET_REPORT);
	अगर (ret != 2) अणु
		hid_err(g15->hdev, "Error getting LED brightness: %d\n", ret);
		ret = (ret < 0) ? ret : -EIO;
	पूर्ण

	g15->leds[LG_G15_MACRO_PRESET1].brightness =
		!!(g15->transfer_buf[1] & 0x80);
	g15->leds[LG_G15_MACRO_PRESET2].brightness =
		!!(g15->transfer_buf[1] & 0x40);
	g15->leds[LG_G15_MACRO_PRESET3].brightness =
		!!(g15->transfer_buf[1] & 0x20);
	g15->leds[LG_G15_MACRO_RECORD].brightness =
		!!(g15->transfer_buf[1] & 0x10);

	वापस 0;
पूर्ण

अटल क्रमागत led_brightness lg_g510_mkey_led_get(काष्ठा led_classdev *led_cdev)
अणु
	काष्ठा lg_g15_led *g15_led =
		container_of(led_cdev, काष्ठा lg_g15_led, cdev);
	काष्ठा lg_g15_data *g15 = dev_get_drvdata(led_cdev->dev->parent);
	क्रमागत led_brightness brightness;

	mutex_lock(&g15->mutex);
	lg_g510_update_mkey_led_brightness(g15);
	brightness = g15->leds[g15_led->led].brightness;
	mutex_unlock(&g15->mutex);

	वापस brightness;
पूर्ण

अटल पूर्णांक lg_g510_mkey_led_set(काष्ठा led_classdev *led_cdev,
				क्रमागत led_brightness brightness)
अणु
	काष्ठा lg_g15_led *g15_led =
		container_of(led_cdev, काष्ठा lg_g15_led, cdev);
	काष्ठा lg_g15_data *g15 = dev_get_drvdata(led_cdev->dev->parent);
	u8 val, mask = 0;
	पूर्णांक i, ret;

	/* Ignore LED off on unरेजिस्टर / keyboard unplug */
	अगर (led_cdev->flags & LED_UNREGISTERING)
		वापस 0;

	mutex_lock(&g15->mutex);

	क्रम (i = LG_G15_MACRO_PRESET1; i < LG_G15_LED_MAX; i++) अणु
		अगर (i == g15_led->led)
			val = brightness;
		अन्यथा
			val = g15->leds[i].brightness;

		अगर (val)
			mask |= 0x80 >> (i - LG_G15_MACRO_PRESET1);
	पूर्ण

	g15->transfer_buf[0] = LG_G510_FEATURE_M_KEYS_LEDS;
	g15->transfer_buf[1] = mask;

	ret = hid_hw_raw_request(g15->hdev, LG_G510_FEATURE_M_KEYS_LEDS,
				 g15->transfer_buf, 2,
				 HID_FEATURE_REPORT, HID_REQ_SET_REPORT);
	अगर (ret == 2) अणु
		/* Success */
		g15_led->brightness = brightness;
		ret = 0;
	पूर्ण अन्यथा अणु
		hid_err(g15->hdev, "Error setting LED brightness: %d\n", ret);
		ret = (ret < 0) ? ret : -EIO;
	पूर्ण

	mutex_unlock(&g15->mutex);

	वापस ret;
पूर्ण

/******** Generic LED functions ********/
अटल पूर्णांक lg_g15_get_initial_led_brightness(काष्ठा lg_g15_data *g15)
अणु
	पूर्णांक ret;

	चयन (g15->model) अणु
	हाल LG_G15:
	हाल LG_G15_V2:
		वापस lg_g15_update_led_brightness(g15);
	हाल LG_G510:
	हाल LG_G510_USB_AUDIO:
		ret = lg_g510_get_initial_led_brightness(g15, 0);
		अगर (ret)
			वापस ret;

		ret = lg_g510_get_initial_led_brightness(g15, 1);
		अगर (ret)
			वापस ret;

		वापस lg_g510_update_mkey_led_brightness(g15);
	पूर्ण
	वापस -EINVAL; /* Never reached */
पूर्ण

/******** Input functions ********/

/* On the G15 Mark I Logitech has been quite creative with which bit is what */
अटल पूर्णांक lg_g15_event(काष्ठा lg_g15_data *g15, u8 *data, पूर्णांक size)
अणु
	पूर्णांक i, val;

	/* G1 - G6 */
	क्रम (i = 0; i < 6; i++) अणु
		val = data[i + 1] & (1 << i);
		input_report_key(g15->input, KEY_MACRO1 + i, val);
	पूर्ण
	/* G7 - G12 */
	क्रम (i = 0; i < 6; i++) अणु
		val = data[i + 2] & (1 << i);
		input_report_key(g15->input, KEY_MACRO7 + i, val);
	पूर्ण
	/* G13 - G17 */
	क्रम (i = 0; i < 5; i++) अणु
		val = data[i + 1] & (4 << i);
		input_report_key(g15->input, KEY_MACRO13 + i, val);
	पूर्ण
	/* G18 */
	input_report_key(g15->input, KEY_MACRO18, data[8] & 0x40);

	/* M1 - M3 */
	क्रम (i = 0; i < 3; i++) अणु
		val = data[i + 6] & (1 << i);
		input_report_key(g15->input, KEY_MACRO_PRESET1 + i, val);
	पूर्ण
	/* MR */
	input_report_key(g15->input, KEY_MACRO_RECORD_START, data[7] & 0x40);

	/* Most left (round) button below the LCD */
	input_report_key(g15->input, KEY_KBD_LCD_MENU1, data[8] & 0x80);
	/* 4 other buttons below the LCD */
	क्रम (i = 0; i < 4; i++) अणु
		val = data[i + 2] & 0x80;
		input_report_key(g15->input, KEY_KBD_LCD_MENU2 + i, val);
	पूर्ण

	/* Backlight cycle button pressed? */
	अगर (data[1] & 0x80)
		schedule_work(&g15->work);

	input_sync(g15->input);
	वापस 0;
पूर्ण

अटल पूर्णांक lg_g15_v2_event(काष्ठा lg_g15_data *g15, u8 *data, पूर्णांक size)
अणु
	पूर्णांक i, val;

	/* G1 - G6 */
	क्रम (i = 0; i < 6; i++) अणु
		val = data[1] & (1 << i);
		input_report_key(g15->input, KEY_MACRO1 + i, val);
	पूर्ण

	/* M1 - M3 + MR */
	input_report_key(g15->input, KEY_MACRO_PRESET1, data[1] & 0x40);
	input_report_key(g15->input, KEY_MACRO_PRESET2, data[1] & 0x80);
	input_report_key(g15->input, KEY_MACRO_PRESET3, data[2] & 0x20);
	input_report_key(g15->input, KEY_MACRO_RECORD_START, data[2] & 0x40);

	/* Round button to the left of the LCD */
	input_report_key(g15->input, KEY_KBD_LCD_MENU1, data[2] & 0x80);
	/* 4 buttons below the LCD */
	क्रम (i = 0; i < 4; i++) अणु
		val = data[2] & (2 << i);
		input_report_key(g15->input, KEY_KBD_LCD_MENU2 + i, val);
	पूर्ण

	/* Backlight cycle button pressed? */
	अगर (data[2] & 0x01)
		schedule_work(&g15->work);

	input_sync(g15->input);
	वापस 0;
पूर्ण

अटल पूर्णांक lg_g510_event(काष्ठा lg_g15_data *g15, u8 *data, पूर्णांक size)
अणु
	bool game_mode_enabled;
	पूर्णांक i, val;

	/* G1 - G18 */
	क्रम (i = 0; i < 18; i++) अणु
		val = data[i / 8 + 1] & (1 << (i % 8));
		input_report_key(g15->input, KEY_MACRO1 + i, val);
	पूर्ण

	/* Game mode on/off slider */
	game_mode_enabled = data[3] & 0x04;
	अगर (game_mode_enabled != g15->game_mode_enabled) अणु
		अगर (game_mode_enabled)
			hid_info(g15->hdev, "Game Mode enabled, Windows (super) key is disabled\n");
		अन्यथा
			hid_info(g15->hdev, "Game Mode disabled\n");
		g15->game_mode_enabled = game_mode_enabled;
	पूर्ण

	/* M1 - M3 */
	क्रम (i = 0; i < 3; i++) अणु
		val = data[3] & (0x10 << i);
		input_report_key(g15->input, KEY_MACRO_PRESET1 + i, val);
	पूर्ण
	/* MR */
	input_report_key(g15->input, KEY_MACRO_RECORD_START, data[3] & 0x80);

	/* LCD menu keys */
	क्रम (i = 0; i < 5; i++) अणु
		val = data[4] & (1 << i);
		input_report_key(g15->input, KEY_KBD_LCD_MENU1 + i, val);
	पूर्ण

	/* Headphone Mute */
	input_report_key(g15->input, KEY_MUTE, data[4] & 0x20);
	/* Microphone Mute */
	input_report_key(g15->input, KEY_F20, data[4] & 0x40);

	input_sync(g15->input);
	वापस 0;
पूर्ण

अटल पूर्णांक lg_g510_leds_event(काष्ठा lg_g15_data *g15, u8 *data, पूर्णांक size)
अणु
	bool backlight_disabled;

	/*
	 * The G510 ignores backlight updates when the backlight is turned off
	 * through the light toggle button on the keyboard, to work around this
	 * we queue a workitem to sync values when the backlight is turned on.
	 */
	backlight_disabled = data[1] & 0x04;
	अगर (!backlight_disabled)
		schedule_work(&g15->work);

	वापस 0;
पूर्ण

अटल पूर्णांक lg_g15_raw_event(काष्ठा hid_device *hdev, काष्ठा hid_report *report,
			    u8 *data, पूर्णांक size)
अणु
	काष्ठा lg_g15_data *g15 = hid_get_drvdata(hdev);

	अगर (!g15)
		वापस 0;

	चयन (g15->model) अणु
	हाल LG_G15:
		अगर (data[0] == 0x02 && size == 9)
			वापस lg_g15_event(g15, data, size);
		अवरोध;
	हाल LG_G15_V2:
		अगर (data[0] == 0x02 && size == 5)
			वापस lg_g15_v2_event(g15, data, size);
		अवरोध;
	हाल LG_G510:
	हाल LG_G510_USB_AUDIO:
		अगर (data[0] == 0x03 && size == 5)
			वापस lg_g510_event(g15, data, size);
		अगर (data[0] == 0x04 && size == 2)
			वापस lg_g510_leds_event(g15, data, size);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक lg_g15_input_खोलो(काष्ठा input_dev *dev)
अणु
	काष्ठा hid_device *hdev = input_get_drvdata(dev);

	वापस hid_hw_खोलो(hdev);
पूर्ण

अटल व्योम lg_g15_input_बंद(काष्ठा input_dev *dev)
अणु
	काष्ठा hid_device *hdev = input_get_drvdata(dev);

	hid_hw_बंद(hdev);
पूर्ण

अटल पूर्णांक lg_g15_रेजिस्टर_led(काष्ठा lg_g15_data *g15, पूर्णांक i)
अणु
	अटल स्थिर अक्षर * स्थिर led_names[] = अणु
		"g15::kbd_backlight",
		"g15::lcd_backlight",
		"g15::macro_preset1",
		"g15::macro_preset2",
		"g15::macro_preset3",
		"g15::macro_record",
	पूर्ण;

	g15->leds[i].led = i;
	g15->leds[i].cdev.name = led_names[i];

	चयन (g15->model) अणु
	हाल LG_G15:
	हाल LG_G15_V2:
		g15->leds[i].cdev.brightness_set_blocking = lg_g15_led_set;
		g15->leds[i].cdev.brightness_get = lg_g15_led_get;
		अगर (i < LG_G15_BRIGHTNESS_MAX) अणु
			g15->leds[i].cdev.flags = LED_BRIGHT_HW_CHANGED;
			g15->leds[i].cdev.max_brightness = 2;
		पूर्ण अन्यथा अणु
			g15->leds[i].cdev.max_brightness = 1;
		पूर्ण
		अवरोध;
	हाल LG_G510:
	हाल LG_G510_USB_AUDIO:
		चयन (i) अणु
		हाल LG_G15_LCD_BRIGHTNESS:
			/*
			 * The G510 करोes not have a separate LCD brightness,
			 * but it करोes have a separate घातer-on (reset) value.
			 */
			g15->leds[i].cdev.name = "g15::power_on_backlight_val";
			fallthrough;
		हाल LG_G15_KBD_BRIGHTNESS:
			g15->leds[i].cdev.brightness_set_blocking =
				lg_g510_kbd_led_set;
			g15->leds[i].cdev.brightness_get =
				lg_g510_kbd_led_get;
			g15->leds[i].cdev.max_brightness = 255;
			g15->leds[i].cdev.groups = lg_g510_kbd_led_groups;
			अवरोध;
		शेष:
			g15->leds[i].cdev.brightness_set_blocking =
				lg_g510_mkey_led_set;
			g15->leds[i].cdev.brightness_get =
				lg_g510_mkey_led_get;
			g15->leds[i].cdev.max_brightness = 1;
		पूर्ण
		अवरोध;
	पूर्ण

	वापस devm_led_classdev_रेजिस्टर(&g15->hdev->dev, &g15->leds[i].cdev);
पूर्ण

अटल पूर्णांक lg_g15_probe(काष्ठा hid_device *hdev, स्थिर काष्ठा hid_device_id *id)
अणु
	u8 gkeys_settings_output_report = 0;
	u8 gkeys_settings_feature_report = 0;
	काष्ठा hid_report_क्रमागत *rep_क्रमागत;
	अचिन्हित पूर्णांक connect_mask = 0;
	bool has_ff000000 = false;
	काष्ठा lg_g15_data *g15;
	काष्ठा input_dev *input;
	काष्ठा hid_report *rep;
	पूर्णांक ret, i, gkeys = 0;

	hdev->quirks |= HID_QUIRK_INPUT_PER_APP;

	ret = hid_parse(hdev);
	अगर (ret)
		वापस ret;

	/*
	 * Some models have multiple पूर्णांकerfaces, we want the पूर्णांकerface with
	 * with the f000.0000 application input report.
	 */
	rep_क्रमागत = &hdev->report_क्रमागत[HID_INPUT_REPORT];
	list_क्रम_each_entry(rep, &rep_क्रमागत->report_list, list) अणु
		अगर (rep->application == 0xff000000)
			has_ff000000 = true;
	पूर्ण
	अगर (!has_ff000000)
		वापस hid_hw_start(hdev, HID_CONNECT_DEFAULT);

	g15 = devm_kzalloc(&hdev->dev, माप(*g15), GFP_KERNEL);
	अगर (!g15)
		वापस -ENOMEM;

	mutex_init(&g15->mutex);

	input = devm_input_allocate_device(&hdev->dev);
	अगर (!input)
		वापस -ENOMEM;

	g15->hdev = hdev;
	g15->model = id->driver_data;
	hid_set_drvdata(hdev, (व्योम *)g15);

	चयन (g15->model) अणु
	हाल LG_G15:
		INIT_WORK(&g15->work, lg_g15_leds_changed_work);
		/*
		 * The G15 and G15 v2 use a separate usb-device (on a builtin
		 * hub) which emulates a keyboard क्रम the F1 - F12 emulation
		 * on the G-keys, which we disable, rendering the emulated kbd
		 * non-functional, so we करो not let hid-input connect.
		 */
		connect_mask = HID_CONNECT_HIDRAW;
		gkeys_settings_output_report = 0x02;
		gkeys = 18;
		अवरोध;
	हाल LG_G15_V2:
		INIT_WORK(&g15->work, lg_g15_leds_changed_work);
		connect_mask = HID_CONNECT_HIDRAW;
		gkeys_settings_output_report = 0x02;
		gkeys = 6;
		अवरोध;
	हाल LG_G510:
	हाल LG_G510_USB_AUDIO:
		INIT_WORK(&g15->work, lg_g510_leds_sync_work);
		connect_mask = HID_CONNECT_HIDINPUT | HID_CONNECT_HIDRAW;
		gkeys_settings_feature_report = 0x01;
		gkeys = 18;
		अवरोध;
	पूर्ण

	ret = hid_hw_start(hdev, connect_mask);
	अगर (ret)
		वापस ret;

	/* Tell the keyboard to stop sending F1-F12 + 1-6 क्रम G1 - G18 */
	अगर (gkeys_settings_output_report) अणु
		g15->transfer_buf[0] = gkeys_settings_output_report;
		स_रखो(g15->transfer_buf + 1, 0, gkeys);
		/*
		 * The kbd ignores our output report अगर we करो not queue
		 * an URB on the USB input endpoपूर्णांक first...
		 */
		ret = hid_hw_खोलो(hdev);
		अगर (ret)
			जाओ error_hw_stop;
		ret = hid_hw_output_report(hdev, g15->transfer_buf, gkeys + 1);
		hid_hw_बंद(hdev);
	पूर्ण

	अगर (gkeys_settings_feature_report) अणु
		g15->transfer_buf[0] = gkeys_settings_feature_report;
		स_रखो(g15->transfer_buf + 1, 0, gkeys);
		ret = hid_hw_raw_request(g15->hdev,
				gkeys_settings_feature_report,
				g15->transfer_buf, gkeys + 1,
				HID_FEATURE_REPORT, HID_REQ_SET_REPORT);
	पूर्ण

	अगर (ret < 0) अणु
		hid_err(hdev, "Error %d disabling keyboard emulation for the G-keys, falling back to generic hid-input driver\n",
			ret);
		hid_set_drvdata(hdev, शून्य);
		वापस 0;
	पूर्ण

	/* Get initial brightness levels */
	ret = lg_g15_get_initial_led_brightness(g15);
	अगर (ret)
		जाओ error_hw_stop;

	/* Setup and रेजिस्टर input device */
	input->name = "Logitech Gaming Keyboard Gaming Keys";
	input->phys = hdev->phys;
	input->uniq = hdev->uniq;
	input->id.bustype = hdev->bus;
	input->id.venकरोr  = hdev->venकरोr;
	input->id.product = hdev->product;
	input->id.version = hdev->version;
	input->dev.parent = &hdev->dev;
	input->खोलो = lg_g15_input_खोलो;
	input->बंद = lg_g15_input_बंद;

	/* G-keys */
	क्रम (i = 0; i < gkeys; i++)
		input_set_capability(input, EV_KEY, KEY_MACRO1 + i);

	/* M1 - M3 and MR keys */
	क्रम (i = 0; i < 3; i++)
		input_set_capability(input, EV_KEY, KEY_MACRO_PRESET1 + i);
	input_set_capability(input, EV_KEY, KEY_MACRO_RECORD_START);

	/* Keys below the LCD, पूर्णांकended क्रम controlling a menu on the LCD */
	क्रम (i = 0; i < 5; i++)
		input_set_capability(input, EV_KEY, KEY_KBD_LCD_MENU1 + i);

	/*
	 * On the G510 only report headphone and mic mute keys when *not* using
	 * the builtin USB audio device. When the builtin audio is used these
	 * keys directly toggle mute (and the LEDs) on/off.
	 */
	अगर (g15->model == LG_G510) अणु
		input_set_capability(input, EV_KEY, KEY_MUTE);
		/* Userspace expects F20 क्रम micmute */
		input_set_capability(input, EV_KEY, KEY_F20);
	पूर्ण

	g15->input = input;
	input_set_drvdata(input, hdev);

	ret = input_रेजिस्टर_device(input);
	अगर (ret)
		जाओ error_hw_stop;

	/* Register LED devices */
	क्रम (i = 0; i < LG_G15_LED_MAX; i++) अणु
		ret = lg_g15_रेजिस्टर_led(g15, i);
		अगर (ret)
			जाओ error_hw_stop;
	पूर्ण

	वापस 0;

error_hw_stop:
	hid_hw_stop(hdev);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा hid_device_id lg_g15_devices[] = अणु
	/* The G11 is a G15 without the LCD, treat it as a G15 */
	अणु HID_USB_DEVICE(USB_VENDOR_ID_LOGITECH,
		USB_DEVICE_ID_LOGITECH_G11),
		.driver_data = LG_G15 पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_LOGITECH,
			 USB_DEVICE_ID_LOGITECH_G15_LCD),
		.driver_data = LG_G15 पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_LOGITECH,
			 USB_DEVICE_ID_LOGITECH_G15_V2_LCD),
		.driver_data = LG_G15_V2 पूर्ण,
	/* G510 without a headset plugged in */
	अणु HID_USB_DEVICE(USB_VENDOR_ID_LOGITECH,
			 USB_DEVICE_ID_LOGITECH_G510),
		.driver_data = LG_G510 पूर्ण,
	/* G510 with headset plugged in / with extra USB audio पूर्णांकerface */
	अणु HID_USB_DEVICE(USB_VENDOR_ID_LOGITECH,
			 USB_DEVICE_ID_LOGITECH_G510_USB_AUDIO),
		.driver_data = LG_G510_USB_AUDIO पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(hid, lg_g15_devices);

अटल काष्ठा hid_driver lg_g15_driver = अणु
	.name			= "lg-g15",
	.id_table		= lg_g15_devices,
	.raw_event		= lg_g15_raw_event,
	.probe			= lg_g15_probe,
पूर्ण;
module_hid_driver(lg_g15_driver);

MODULE_LICENSE("GPL");
