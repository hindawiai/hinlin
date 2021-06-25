<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*-*-linux-c-*-*/

/*
  Copyright (C) 2007,2008 Jonathan Woithe <jwoithe@just42.net>
  Copyright (C) 2008 Peter Gruber <nokos@gmx.net>
  Copyright (C) 2008 Tony Vroon <tony@linx.net>
  Based on earlier work:
    Copyright (C) 2003 Shane Spencer <shane@bogomip.com>
    Adrian Yee <brewt-fujitsu@brewt.org>

  Templated from msi-laptop.c and thinkpad_acpi.c which is copyright
  by its respective authors.

 */

/*
 * fujitsu-laptop.c - Fujitsu laptop support, providing access to additional
 * features made available on a range of Fujitsu laptops including the
 * P2xxx/P5xxx/S6xxx/S7xxx series.
 *
 * This driver implements a venकरोr-specअगरic backlight control पूर्णांकerface क्रम
 * Fujitsu laptops and provides support क्रम hotkeys present on certain Fujitsu
 * laptops.
 *
 * This driver has been tested on a Fujitsu Lअगरebook S6410, S7020 and
 * P8010.  It should work on most P-series and S-series Lअगरebooks, but
 * YMMV.
 *
 * The module parameter use_alt_lcd_levels चयनes between dअगरferent ACPI
 * brightness controls which are used by dअगरferent Fujitsu laptops.  In most
 * हालs the correct method is स्वतःmatically detected. "use_alt_lcd_levels=1"
 * is applicable क्रम a Fujitsu Lअगरebook S6410 अगर स्वतःdetection fails.
 *
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/acpi.h>
#समावेश <linux/bitops.h>
#समावेश <linux/dmi.h>
#समावेश <linux/backlight.h>
#समावेश <linux/fb.h>
#समावेश <linux/input.h>
#समावेश <linux/input/sparse-keymap.h>
#समावेश <linux/kfअगरo.h>
#समावेश <linux/leds.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <acpi/video.h>

#घोषणा FUJITSU_DRIVER_VERSION		"0.6.0"

#घोषणा FUJITSU_LCD_N_LEVELS		8

#घोषणा ACPI_FUJITSU_CLASS		"fujitsu"
#घोषणा ACPI_FUJITSU_BL_HID		"FUJ02B1"
#घोषणा ACPI_FUJITSU_BL_DRIVER_NAME	"Fujitsu laptop FUJ02B1 ACPI brightness driver"
#घोषणा ACPI_FUJITSU_BL_DEVICE_NAME	"Fujitsu FUJ02B1"
#घोषणा ACPI_FUJITSU_LAPTOP_HID		"FUJ02E3"
#घोषणा ACPI_FUJITSU_LAPTOP_DRIVER_NAME	"Fujitsu laptop FUJ02E3 ACPI hotkeys driver"
#घोषणा ACPI_FUJITSU_LAPTOP_DEVICE_NAME	"Fujitsu FUJ02E3"

#घोषणा ACPI_FUJITSU_NOTIFY_CODE	0x80

/* FUNC पूर्णांकerface - command values */
#घोषणा FUNC_FLAGS			BIT(12)
#घोषणा FUNC_LEDS			(BIT(12) | BIT(0))
#घोषणा FUNC_BUTTONS			(BIT(12) | BIT(1))
#घोषणा FUNC_BACKLIGHT			(BIT(12) | BIT(2))

/* FUNC पूर्णांकerface - responses */
#घोषणा UNSUPPORTED_CMD			0x80000000

/* FUNC पूर्णांकerface - status flags */
#घोषणा FLAG_RFKILL			BIT(5)
#घोषणा FLAG_LID			BIT(8)
#घोषणा FLAG_DOCK			BIT(9)
#घोषणा FLAG_TOUCHPAD_TOGGLE		BIT(26)
#घोषणा FLAG_MICMUTE			BIT(29)
#घोषणा FLAG_SOFTKEYS			(FLAG_RFKILL | FLAG_TOUCHPAD_TOGGLE | FLAG_MICMUTE)

/* FUNC पूर्णांकerface - LED control */
#घोषणा FUNC_LED_OFF			BIT(0)
#घोषणा FUNC_LED_ON			(BIT(0) | BIT(16) | BIT(17))
#घोषणा LOGOLAMP_POWERON		BIT(13)
#घोषणा LOGOLAMP_ALWAYS			BIT(14)
#घोषणा KEYBOARD_LAMPS			BIT(8)
#घोषणा RADIO_LED_ON			BIT(5)
#घोषणा ECO_LED				BIT(16)
#घोषणा ECO_LED_ON			BIT(19)

/* FUNC पूर्णांकerface - backlight घातer control */
#घोषणा BACKLIGHT_PARAM_POWER		BIT(2)
#घोषणा BACKLIGHT_OFF			(BIT(0) | BIT(1))
#घोषणा BACKLIGHT_ON			0

/* Scancodes पढ़ो from the GIRB रेजिस्टर */
#घोषणा KEY1_CODE			0x410
#घोषणा KEY2_CODE			0x411
#घोषणा KEY3_CODE			0x412
#घोषणा KEY4_CODE			0x413
#घोषणा KEY5_CODE			0x420

/* Hotkey ringbuffer limits */
#घोषणा MAX_HOTKEY_RINGBUFFER_SIZE	100
#घोषणा RINGBUFFERSIZE			40

/* Module parameters */
अटल पूर्णांक use_alt_lcd_levels = -1;
अटल bool disable_brightness_adjust;

/* Device controlling the backlight and associated keys */
काष्ठा fujitsu_bl अणु
	काष्ठा input_dev *input;
	अक्षर phys[32];
	काष्ठा backlight_device *bl_device;
	अचिन्हित पूर्णांक max_brightness;
	अचिन्हित पूर्णांक brightness_level;
पूर्ण;

अटल काष्ठा fujitsu_bl *fujitsu_bl;

/* Device used to access hotkeys and other features on the laptop */
काष्ठा fujitsu_laptop अणु
	काष्ठा input_dev *input;
	अक्षर phys[32];
	काष्ठा platक्रमm_device *pf_device;
	काष्ठा kfअगरo fअगरo;
	spinlock_t fअगरo_lock;
	पूर्णांक flags_supported;
	पूर्णांक flags_state;
पूर्ण;

अटल काष्ठा acpi_device *fext;

/* Fujitsu ACPI पूर्णांकerface function */

अटल पूर्णांक call_fext_func(काष्ठा acpi_device *device,
			  पूर्णांक func, पूर्णांक op, पूर्णांक feature, पूर्णांक state)
अणु
	जोड़ acpi_object params[4] = अणु
		अणु .पूर्णांकeger.type = ACPI_TYPE_INTEGER, .पूर्णांकeger.value = func पूर्ण,
		अणु .पूर्णांकeger.type = ACPI_TYPE_INTEGER, .पूर्णांकeger.value = op पूर्ण,
		अणु .पूर्णांकeger.type = ACPI_TYPE_INTEGER, .पूर्णांकeger.value = feature पूर्ण,
		अणु .पूर्णांकeger.type = ACPI_TYPE_INTEGER, .पूर्णांकeger.value = state पूर्ण
	पूर्ण;
	काष्ठा acpi_object_list arg_list = अणु 4, params पूर्ण;
	अचिन्हित दीर्घ दीर्घ value;
	acpi_status status;

	status = acpi_evaluate_पूर्णांकeger(device->handle, "FUNC", &arg_list,
				       &value);
	अगर (ACPI_FAILURE(status)) अणु
		acpi_handle_err(device->handle, "Failed to evaluate FUNC\n");
		वापस -ENODEV;
	पूर्ण

	acpi_handle_debug(device->handle,
			  "FUNC 0x%x (args 0x%x, 0x%x, 0x%x) returned 0x%x\n",
			  func, op, feature, state, (पूर्णांक)value);
	वापस value;
पूर्ण

/* Hardware access क्रम LCD brightness control */

अटल पूर्णांक set_lcd_level(काष्ठा acpi_device *device, पूर्णांक level)
अणु
	काष्ठा fujitsu_bl *priv = acpi_driver_data(device);
	acpi_status status;
	अक्षर *method;

	चयन (use_alt_lcd_levels) अणु
	हाल -1:
		अगर (acpi_has_method(device->handle, "SBL2"))
			method = "SBL2";
		अन्यथा
			method = "SBLL";
		अवरोध;
	हाल 1:
		method = "SBL2";
		अवरोध;
	शेष:
		method = "SBLL";
		अवरोध;
	पूर्ण

	acpi_handle_debug(device->handle, "set lcd level via %s [%d]\n", method,
			  level);

	अगर (level < 0 || level >= priv->max_brightness)
		वापस -EINVAL;

	status = acpi_execute_simple_method(device->handle, method, level);
	अगर (ACPI_FAILURE(status)) अणु
		acpi_handle_err(device->handle, "Failed to evaluate %s\n",
				method);
		वापस -ENODEV;
	पूर्ण

	priv->brightness_level = level;

	वापस 0;
पूर्ण

अटल पूर्णांक get_lcd_level(काष्ठा acpi_device *device)
अणु
	काष्ठा fujitsu_bl *priv = acpi_driver_data(device);
	अचिन्हित दीर्घ दीर्घ state = 0;
	acpi_status status = AE_OK;

	acpi_handle_debug(device->handle, "get lcd level via GBLL\n");

	status = acpi_evaluate_पूर्णांकeger(device->handle, "GBLL", शून्य, &state);
	अगर (ACPI_FAILURE(status))
		वापस 0;

	priv->brightness_level = state & 0x0fffffff;

	वापस priv->brightness_level;
पूर्ण

अटल पूर्णांक get_max_brightness(काष्ठा acpi_device *device)
अणु
	काष्ठा fujitsu_bl *priv = acpi_driver_data(device);
	अचिन्हित दीर्घ दीर्घ state = 0;
	acpi_status status = AE_OK;

	acpi_handle_debug(device->handle, "get max lcd level via RBLL\n");

	status = acpi_evaluate_पूर्णांकeger(device->handle, "RBLL", शून्य, &state);
	अगर (ACPI_FAILURE(status))
		वापस -1;

	priv->max_brightness = state;

	वापस priv->max_brightness;
पूर्ण

/* Backlight device stuff */

अटल पूर्णांक bl_get_brightness(काष्ठा backlight_device *b)
अणु
	काष्ठा acpi_device *device = bl_get_data(b);

	वापस b->props.घातer == FB_BLANK_POWERDOWN ? 0 : get_lcd_level(device);
पूर्ण

अटल पूर्णांक bl_update_status(काष्ठा backlight_device *b)
अणु
	काष्ठा acpi_device *device = bl_get_data(b);

	अगर (fext) अणु
		अगर (b->props.घातer == FB_BLANK_POWERDOWN)
			call_fext_func(fext, FUNC_BACKLIGHT, 0x1,
				       BACKLIGHT_PARAM_POWER, BACKLIGHT_OFF);
		अन्यथा
			call_fext_func(fext, FUNC_BACKLIGHT, 0x1,
				       BACKLIGHT_PARAM_POWER, BACKLIGHT_ON);
	पूर्ण

	वापस set_lcd_level(device, b->props.brightness);
पूर्ण

अटल स्थिर काष्ठा backlight_ops fujitsu_bl_ops = अणु
	.get_brightness = bl_get_brightness,
	.update_status = bl_update_status,
पूर्ण;

अटल sमाप_प्रकार lid_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			अक्षर *buf)
अणु
	काष्ठा fujitsu_laptop *priv = dev_get_drvdata(dev);

	अगर (!(priv->flags_supported & FLAG_LID))
		वापस प्र_लिखो(buf, "unknown\n");
	अगर (priv->flags_state & FLAG_LID)
		वापस प्र_लिखो(buf, "open\n");
	अन्यथा
		वापस प्र_लिखो(buf, "closed\n");
पूर्ण

अटल sमाप_प्रकार करोck_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			 अक्षर *buf)
अणु
	काष्ठा fujitsu_laptop *priv = dev_get_drvdata(dev);

	अगर (!(priv->flags_supported & FLAG_DOCK))
		वापस प्र_लिखो(buf, "unknown\n");
	अगर (priv->flags_state & FLAG_DOCK)
		वापस प्र_लिखो(buf, "docked\n");
	अन्यथा
		वापस प्र_लिखो(buf, "undocked\n");
पूर्ण

अटल sमाप_प्रकार radios_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			   अक्षर *buf)
अणु
	काष्ठा fujitsu_laptop *priv = dev_get_drvdata(dev);

	अगर (!(priv->flags_supported & FLAG_RFKILL))
		वापस प्र_लिखो(buf, "unknown\n");
	अगर (priv->flags_state & FLAG_RFKILL)
		वापस प्र_लिखो(buf, "on\n");
	अन्यथा
		वापस प्र_लिखो(buf, "killed\n");
पूर्ण

अटल DEVICE_ATTR_RO(lid);
अटल DEVICE_ATTR_RO(करोck);
अटल DEVICE_ATTR_RO(radios);

अटल काष्ठा attribute *fujitsu_pf_attributes[] = अणु
	&dev_attr_lid.attr,
	&dev_attr_करोck.attr,
	&dev_attr_radios.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group fujitsu_pf_attribute_group = अणु
	.attrs = fujitsu_pf_attributes
पूर्ण;

अटल काष्ठा platक्रमm_driver fujitsu_pf_driver = अणु
	.driver = अणु
		   .name = "fujitsu-laptop",
		   पूर्ण
पूर्ण;

/* ACPI device क्रम LCD brightness control */

अटल स्थिर काष्ठा key_entry keymap_backlight[] = अणु
	अणु KE_KEY, true, अणु KEY_BRIGHTNESSUP पूर्ण पूर्ण,
	अणु KE_KEY, false, अणु KEY_BRIGHTNESSDOWN पूर्ण पूर्ण,
	अणु KE_END, 0 पूर्ण
पूर्ण;

अटल पूर्णांक acpi_fujitsu_bl_input_setup(काष्ठा acpi_device *device)
अणु
	काष्ठा fujitsu_bl *priv = acpi_driver_data(device);
	पूर्णांक ret;

	priv->input = devm_input_allocate_device(&device->dev);
	अगर (!priv->input)
		वापस -ENOMEM;

	snम_लिखो(priv->phys, माप(priv->phys), "%s/video/input0",
		 acpi_device_hid(device));

	priv->input->name = acpi_device_name(device);
	priv->input->phys = priv->phys;
	priv->input->id.bustype = BUS_HOST;
	priv->input->id.product = 0x06;

	ret = sparse_keymap_setup(priv->input, keymap_backlight, शून्य);
	अगर (ret)
		वापस ret;

	वापस input_रेजिस्टर_device(priv->input);
पूर्ण

अटल पूर्णांक fujitsu_backlight_रेजिस्टर(काष्ठा acpi_device *device)
अणु
	काष्ठा fujitsu_bl *priv = acpi_driver_data(device);
	स्थिर काष्ठा backlight_properties props = अणु
		.brightness = priv->brightness_level,
		.max_brightness = priv->max_brightness - 1,
		.type = BACKLIGHT_PLATFORM
	पूर्ण;
	काष्ठा backlight_device *bd;

	bd = devm_backlight_device_रेजिस्टर(&device->dev, "fujitsu-laptop",
					    &device->dev, device,
					    &fujitsu_bl_ops, &props);
	अगर (IS_ERR(bd))
		वापस PTR_ERR(bd);

	priv->bl_device = bd;

	वापस 0;
पूर्ण

अटल पूर्णांक acpi_fujitsu_bl_add(काष्ठा acpi_device *device)
अणु
	काष्ठा fujitsu_bl *priv;
	पूर्णांक ret;

	अगर (acpi_video_get_backlight_type() != acpi_backlight_venकरोr)
		वापस -ENODEV;

	priv = devm_kzalloc(&device->dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	fujitsu_bl = priv;
	म_नकल(acpi_device_name(device), ACPI_FUJITSU_BL_DEVICE_NAME);
	म_नकल(acpi_device_class(device), ACPI_FUJITSU_CLASS);
	device->driver_data = priv;

	pr_info("ACPI: %s [%s]\n",
		acpi_device_name(device), acpi_device_bid(device));

	अगर (get_max_brightness(device) <= 0)
		priv->max_brightness = FUJITSU_LCD_N_LEVELS;
	get_lcd_level(device);

	ret = acpi_fujitsu_bl_input_setup(device);
	अगर (ret)
		वापस ret;

	वापस fujitsu_backlight_रेजिस्टर(device);
पूर्ण

/* Brightness notअगरy */

अटल व्योम acpi_fujitsu_bl_notअगरy(काष्ठा acpi_device *device, u32 event)
अणु
	काष्ठा fujitsu_bl *priv = acpi_driver_data(device);
	पूर्णांक oldb, newb;

	अगर (event != ACPI_FUJITSU_NOTIFY_CODE) अणु
		acpi_handle_info(device->handle, "unsupported event [0x%x]\n",
				 event);
		sparse_keymap_report_event(priv->input, -1, 1, true);
		वापस;
	पूर्ण

	oldb = priv->brightness_level;
	get_lcd_level(device);
	newb = priv->brightness_level;

	acpi_handle_debug(device->handle,
			  "brightness button event [%i -> %i]\n", oldb, newb);

	अगर (oldb == newb)
		वापस;

	अगर (!disable_brightness_adjust)
		set_lcd_level(device, newb);

	sparse_keymap_report_event(priv->input, oldb < newb, 1, true);
पूर्ण

/* ACPI device क्रम hotkey handling */

अटल स्थिर काष्ठा key_entry keymap_शेष[] = अणु
	अणु KE_KEY, KEY1_CODE,            अणु KEY_PROG1 पूर्ण पूर्ण,
	अणु KE_KEY, KEY2_CODE,            अणु KEY_PROG2 पूर्ण पूर्ण,
	अणु KE_KEY, KEY3_CODE,            अणु KEY_PROG3 पूर्ण पूर्ण,
	अणु KE_KEY, KEY4_CODE,            अणु KEY_PROG4 पूर्ण पूर्ण,
	अणु KE_KEY, KEY5_CODE,            अणु KEY_RFKILL पूर्ण पूर्ण,
	/* Soft keys पढ़ो from status flags */
	अणु KE_KEY, FLAG_RFKILL,          अणु KEY_RFKILL पूर्ण पूर्ण,
	अणु KE_KEY, FLAG_TOUCHPAD_TOGGLE, अणु KEY_TOUCHPAD_TOGGLE पूर्ण पूर्ण,
	अणु KE_KEY, FLAG_MICMUTE,         अणु KEY_MICMUTE पूर्ण पूर्ण,
	अणु KE_END, 0 पूर्ण
पूर्ण;

अटल स्थिर काष्ठा key_entry keymap_s64x0[] = अणु
	अणु KE_KEY, KEY1_CODE, अणु KEY_SCREENLOCK पूर्ण पूर्ण,	/* "Lock" */
	अणु KE_KEY, KEY2_CODE, अणु KEY_HELP पूर्ण पूर्ण,		/* "Mobility Center */
	अणु KE_KEY, KEY3_CODE, अणु KEY_PROG3 पूर्ण पूर्ण,
	अणु KE_KEY, KEY4_CODE, अणु KEY_PROG4 पूर्ण पूर्ण,
	अणु KE_END, 0 पूर्ण
पूर्ण;

अटल स्थिर काष्ठा key_entry keymap_p8010[] = अणु
	अणु KE_KEY, KEY1_CODE, अणु KEY_HELP पूर्ण पूर्ण,		/* "Support" */
	अणु KE_KEY, KEY2_CODE, अणु KEY_PROG2 पूर्ण पूर्ण,
	अणु KE_KEY, KEY3_CODE, अणु KEY_SWITCHVIDEOMODE पूर्ण पूर्ण,	/* "Presentation" */
	अणु KE_KEY, KEY4_CODE, अणु KEY_WWW पूर्ण पूर्ण,		/* "WWW" */
	अणु KE_END, 0 पूर्ण
पूर्ण;

अटल स्थिर काष्ठा key_entry *keymap = keymap_शेष;

अटल पूर्णांक fujitsu_laptop_dmi_keymap_override(स्थिर काष्ठा dmi_प्रणाली_id *id)
अणु
	pr_info("Identified laptop model '%s'\n", id->ident);
	keymap = id->driver_data;
	वापस 1;
पूर्ण

अटल स्थिर काष्ठा dmi_प्रणाली_id fujitsu_laptop_dmi_table[] = अणु
	अणु
		.callback = fujitsu_laptop_dmi_keymap_override,
		.ident = "Fujitsu Siemens S6410",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "FUJITSU SIEMENS"),
			DMI_MATCH(DMI_PRODUCT_NAME, "LIFEBOOK S6410"),
		पूर्ण,
		.driver_data = (व्योम *)keymap_s64x0
	पूर्ण,
	अणु
		.callback = fujitsu_laptop_dmi_keymap_override,
		.ident = "Fujitsu Siemens S6420",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "FUJITSU SIEMENS"),
			DMI_MATCH(DMI_PRODUCT_NAME, "LIFEBOOK S6420"),
		पूर्ण,
		.driver_data = (व्योम *)keymap_s64x0
	पूर्ण,
	अणु
		.callback = fujitsu_laptop_dmi_keymap_override,
		.ident = "Fujitsu LifeBook P8010",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "FUJITSU"),
			DMI_MATCH(DMI_PRODUCT_NAME, "LifeBook P8010"),
		पूर्ण,
		.driver_data = (व्योम *)keymap_p8010
	पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल पूर्णांक acpi_fujitsu_laptop_input_setup(काष्ठा acpi_device *device)
अणु
	काष्ठा fujitsu_laptop *priv = acpi_driver_data(device);
	पूर्णांक ret;

	priv->input = devm_input_allocate_device(&device->dev);
	अगर (!priv->input)
		वापस -ENOMEM;

	snम_लिखो(priv->phys, माप(priv->phys), "%s/input0",
		 acpi_device_hid(device));

	priv->input->name = acpi_device_name(device);
	priv->input->phys = priv->phys;
	priv->input->id.bustype = BUS_HOST;

	dmi_check_प्रणाली(fujitsu_laptop_dmi_table);
	ret = sparse_keymap_setup(priv->input, keymap, शून्य);
	अगर (ret)
		वापस ret;

	वापस input_रेजिस्टर_device(priv->input);
पूर्ण

अटल पूर्णांक fujitsu_laptop_platक्रमm_add(काष्ठा acpi_device *device)
अणु
	काष्ठा fujitsu_laptop *priv = acpi_driver_data(device);
	पूर्णांक ret;

	priv->pf_device = platक्रमm_device_alloc("fujitsu-laptop", -1);
	अगर (!priv->pf_device)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(priv->pf_device, priv);

	ret = platक्रमm_device_add(priv->pf_device);
	अगर (ret)
		जाओ err_put_platक्रमm_device;

	ret = sysfs_create_group(&priv->pf_device->dev.kobj,
				 &fujitsu_pf_attribute_group);
	अगर (ret)
		जाओ err_del_platक्रमm_device;

	वापस 0;

err_del_platक्रमm_device:
	platक्रमm_device_del(priv->pf_device);
err_put_platक्रमm_device:
	platक्रमm_device_put(priv->pf_device);

	वापस ret;
पूर्ण

अटल व्योम fujitsu_laptop_platक्रमm_हटाओ(काष्ठा acpi_device *device)
अणु
	काष्ठा fujitsu_laptop *priv = acpi_driver_data(device);

	sysfs_हटाओ_group(&priv->pf_device->dev.kobj,
			   &fujitsu_pf_attribute_group);
	platक्रमm_device_unरेजिस्टर(priv->pf_device);
पूर्ण

अटल पूर्णांक logolamp_set(काष्ठा led_classdev *cdev,
			क्रमागत led_brightness brightness)
अणु
	काष्ठा acpi_device *device = to_acpi_device(cdev->dev->parent);
	पूर्णांक घातeron = FUNC_LED_ON, always = FUNC_LED_ON;
	पूर्णांक ret;

	अगर (brightness < LED_HALF)
		घातeron = FUNC_LED_OFF;

	अगर (brightness < LED_FULL)
		always = FUNC_LED_OFF;

	ret = call_fext_func(device, FUNC_LEDS, 0x1, LOGOLAMP_POWERON, घातeron);
	अगर (ret < 0)
		वापस ret;

	वापस call_fext_func(device, FUNC_LEDS, 0x1, LOGOLAMP_ALWAYS, always);
पूर्ण

अटल क्रमागत led_brightness logolamp_get(काष्ठा led_classdev *cdev)
अणु
	काष्ठा acpi_device *device = to_acpi_device(cdev->dev->parent);
	पूर्णांक ret;

	ret = call_fext_func(device, FUNC_LEDS, 0x2, LOGOLAMP_ALWAYS, 0x0);
	अगर (ret == FUNC_LED_ON)
		वापस LED_FULL;

	ret = call_fext_func(device, FUNC_LEDS, 0x2, LOGOLAMP_POWERON, 0x0);
	अगर (ret == FUNC_LED_ON)
		वापस LED_HALF;

	वापस LED_OFF;
पूर्ण

अटल पूर्णांक kblamps_set(काष्ठा led_classdev *cdev,
		       क्रमागत led_brightness brightness)
अणु
	काष्ठा acpi_device *device = to_acpi_device(cdev->dev->parent);

	अगर (brightness >= LED_FULL)
		वापस call_fext_func(device, FUNC_LEDS, 0x1, KEYBOARD_LAMPS,
				      FUNC_LED_ON);
	अन्यथा
		वापस call_fext_func(device, FUNC_LEDS, 0x1, KEYBOARD_LAMPS,
				      FUNC_LED_OFF);
पूर्ण

अटल क्रमागत led_brightness kblamps_get(काष्ठा led_classdev *cdev)
अणु
	काष्ठा acpi_device *device = to_acpi_device(cdev->dev->parent);
	क्रमागत led_brightness brightness = LED_OFF;

	अगर (call_fext_func(device,
			   FUNC_LEDS, 0x2, KEYBOARD_LAMPS, 0x0) == FUNC_LED_ON)
		brightness = LED_FULL;

	वापस brightness;
पूर्ण

अटल पूर्णांक radio_led_set(काष्ठा led_classdev *cdev,
			 क्रमागत led_brightness brightness)
अणु
	काष्ठा acpi_device *device = to_acpi_device(cdev->dev->parent);

	अगर (brightness >= LED_FULL)
		वापस call_fext_func(device, FUNC_FLAGS, 0x5, RADIO_LED_ON,
				      RADIO_LED_ON);
	अन्यथा
		वापस call_fext_func(device, FUNC_FLAGS, 0x5, RADIO_LED_ON,
				      0x0);
पूर्ण

अटल क्रमागत led_brightness radio_led_get(काष्ठा led_classdev *cdev)
अणु
	काष्ठा acpi_device *device = to_acpi_device(cdev->dev->parent);
	क्रमागत led_brightness brightness = LED_OFF;

	अगर (call_fext_func(device, FUNC_FLAGS, 0x4, 0x0, 0x0) & RADIO_LED_ON)
		brightness = LED_FULL;

	वापस brightness;
पूर्ण

अटल पूर्णांक eco_led_set(काष्ठा led_classdev *cdev,
		       क्रमागत led_brightness brightness)
अणु
	काष्ठा acpi_device *device = to_acpi_device(cdev->dev->parent);
	पूर्णांक curr;

	curr = call_fext_func(device, FUNC_LEDS, 0x2, ECO_LED, 0x0);
	अगर (brightness >= LED_FULL)
		वापस call_fext_func(device, FUNC_LEDS, 0x1, ECO_LED,
				      curr | ECO_LED_ON);
	अन्यथा
		वापस call_fext_func(device, FUNC_LEDS, 0x1, ECO_LED,
				      curr & ~ECO_LED_ON);
पूर्ण

अटल क्रमागत led_brightness eco_led_get(काष्ठा led_classdev *cdev)
अणु
	काष्ठा acpi_device *device = to_acpi_device(cdev->dev->parent);
	क्रमागत led_brightness brightness = LED_OFF;

	अगर (call_fext_func(device, FUNC_LEDS, 0x2, ECO_LED, 0x0) & ECO_LED_ON)
		brightness = LED_FULL;

	वापस brightness;
पूर्ण

अटल पूर्णांक acpi_fujitsu_laptop_leds_रेजिस्टर(काष्ठा acpi_device *device)
अणु
	काष्ठा fujitsu_laptop *priv = acpi_driver_data(device);
	काष्ठा led_classdev *led;
	पूर्णांक ret;

	अगर (call_fext_func(device,
			   FUNC_LEDS, 0x0, 0x0, 0x0) & LOGOLAMP_POWERON) अणु
		led = devm_kzalloc(&device->dev, माप(*led), GFP_KERNEL);
		अगर (!led)
			वापस -ENOMEM;

		led->name = "fujitsu::logolamp";
		led->brightness_set_blocking = logolamp_set;
		led->brightness_get = logolamp_get;
		ret = devm_led_classdev_रेजिस्टर(&device->dev, led);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर ((call_fext_func(device,
			    FUNC_LEDS, 0x0, 0x0, 0x0) & KEYBOARD_LAMPS) &&
	    (call_fext_func(device, FUNC_BUTTONS, 0x0, 0x0, 0x0) == 0x0)) अणु
		led = devm_kzalloc(&device->dev, माप(*led), GFP_KERNEL);
		अगर (!led)
			वापस -ENOMEM;

		led->name = "fujitsu::kblamps";
		led->brightness_set_blocking = kblamps_set;
		led->brightness_get = kblamps_get;
		ret = devm_led_classdev_रेजिस्टर(&device->dev, led);
		अगर (ret)
			वापस ret;
	पूर्ण

	/*
	 * Some Fujitsu laptops have a radio toggle button in place of a slide
	 * चयन and all such machines appear to also have an RF LED.  Based on
	 * comparing DSDT tables of four Fujitsu Lअगरebook models (E744, E751,
	 * S7110, S8420; the first one has a radio toggle button, the other
	 * three have slide चयनes), bit 17 of flags_supported (the value
	 * वापसed by method S000 of ACPI device FUJ02E3) seems to indicate
	 * whether given model has a radio toggle button.
	 */
	अगर (priv->flags_supported & BIT(17)) अणु
		led = devm_kzalloc(&device->dev, माप(*led), GFP_KERNEL);
		अगर (!led)
			वापस -ENOMEM;

		led->name = "fujitsu::radio_led";
		led->brightness_set_blocking = radio_led_set;
		led->brightness_get = radio_led_get;
		led->शेष_trigger = "rfkill-any";
		ret = devm_led_classdev_रेजिस्टर(&device->dev, led);
		अगर (ret)
			वापस ret;
	पूर्ण

	/* Support क्रम eco led is not always संकेतed in bit corresponding
	 * to the bit used to control the led. According to the DSDT table,
	 * bit 14 seems to indicate presence of said led as well.
	 * Confirm by testing the status.
	 */
	अगर ((call_fext_func(device, FUNC_LEDS, 0x0, 0x0, 0x0) & BIT(14)) &&
	    (call_fext_func(device,
			    FUNC_LEDS, 0x2, ECO_LED, 0x0) != UNSUPPORTED_CMD)) अणु
		led = devm_kzalloc(&device->dev, माप(*led), GFP_KERNEL);
		अगर (!led)
			वापस -ENOMEM;

		led->name = "fujitsu::eco_led";
		led->brightness_set_blocking = eco_led_set;
		led->brightness_get = eco_led_get;
		ret = devm_led_classdev_रेजिस्टर(&device->dev, led);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक acpi_fujitsu_laptop_add(काष्ठा acpi_device *device)
अणु
	काष्ठा fujitsu_laptop *priv;
	पूर्णांक ret, i = 0;

	priv = devm_kzalloc(&device->dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	WARN_ONCE(fext, "More than one FUJ02E3 ACPI device was found.  Driver may not work as intended.");
	fext = device;

	म_नकल(acpi_device_name(device), ACPI_FUJITSU_LAPTOP_DEVICE_NAME);
	म_नकल(acpi_device_class(device), ACPI_FUJITSU_CLASS);
	device->driver_data = priv;

	/* kfअगरo */
	spin_lock_init(&priv->fअगरo_lock);
	ret = kfअगरo_alloc(&priv->fअगरo, RINGBUFFERSIZE * माप(पूर्णांक),
			  GFP_KERNEL);
	अगर (ret)
		वापस ret;

	pr_info("ACPI: %s [%s]\n",
		acpi_device_name(device), acpi_device_bid(device));

	जबतक (call_fext_func(device, FUNC_BUTTONS, 0x1, 0x0, 0x0) != 0 &&
	       i++ < MAX_HOTKEY_RINGBUFFER_SIZE)
		; /* No action, result is discarded */
	acpi_handle_debug(device->handle, "Discarded %i ringbuffer entries\n",
			  i);

	priv->flags_supported = call_fext_func(device, FUNC_FLAGS, 0x0, 0x0,
					       0x0);

	/* Make sure our biपंचांगask of supported functions is cleared अगर the
	   RFKILL function block is not implemented, like on the S7020. */
	अगर (priv->flags_supported == UNSUPPORTED_CMD)
		priv->flags_supported = 0;

	अगर (priv->flags_supported)
		priv->flags_state = call_fext_func(device, FUNC_FLAGS, 0x4, 0x0,
						   0x0);

	/* Suspect this is a keymap of the application panel, prपूर्णांक it */
	acpi_handle_info(device->handle, "BTNI: [0x%x]\n",
			 call_fext_func(device, FUNC_BUTTONS, 0x0, 0x0, 0x0));

	/* Sync backlight घातer status */
	अगर (fujitsu_bl && fujitsu_bl->bl_device &&
	    acpi_video_get_backlight_type() == acpi_backlight_venकरोr) अणु
		अगर (call_fext_func(fext, FUNC_BACKLIGHT, 0x2,
				   BACKLIGHT_PARAM_POWER, 0x0) == BACKLIGHT_OFF)
			fujitsu_bl->bl_device->props.घातer = FB_BLANK_POWERDOWN;
		अन्यथा
			fujitsu_bl->bl_device->props.घातer = FB_BLANK_UNBLANK;
	पूर्ण

	ret = acpi_fujitsu_laptop_input_setup(device);
	अगर (ret)
		जाओ err_मुक्त_fअगरo;

	ret = acpi_fujitsu_laptop_leds_रेजिस्टर(device);
	अगर (ret)
		जाओ err_मुक्त_fअगरo;

	ret = fujitsu_laptop_platक्रमm_add(device);
	अगर (ret)
		जाओ err_मुक्त_fअगरo;

	वापस 0;

err_मुक्त_fअगरo:
	kfअगरo_मुक्त(&priv->fअगरo);

	वापस ret;
पूर्ण

अटल पूर्णांक acpi_fujitsu_laptop_हटाओ(काष्ठा acpi_device *device)
अणु
	काष्ठा fujitsu_laptop *priv = acpi_driver_data(device);

	fujitsu_laptop_platक्रमm_हटाओ(device);

	kfअगरo_मुक्त(&priv->fअगरo);

	वापस 0;
पूर्ण

अटल व्योम acpi_fujitsu_laptop_press(काष्ठा acpi_device *device, पूर्णांक scancode)
अणु
	काष्ठा fujitsu_laptop *priv = acpi_driver_data(device);
	पूर्णांक ret;

	ret = kfअगरo_in_locked(&priv->fअगरo, (अचिन्हित अक्षर *)&scancode,
			      माप(scancode), &priv->fअगरo_lock);
	अगर (ret != माप(scancode)) अणु
		dev_info(&priv->input->dev, "Could not push scancode [0x%x]\n",
			 scancode);
		वापस;
	पूर्ण
	sparse_keymap_report_event(priv->input, scancode, 1, false);
	dev_dbg(&priv->input->dev, "Push scancode into ringbuffer [0x%x]\n",
		scancode);
पूर्ण

अटल व्योम acpi_fujitsu_laptop_release(काष्ठा acpi_device *device)
अणु
	काष्ठा fujitsu_laptop *priv = acpi_driver_data(device);
	पूर्णांक scancode, ret;

	जबतक (true) अणु
		ret = kfअगरo_out_locked(&priv->fअगरo, (अचिन्हित अक्षर *)&scancode,
				       माप(scancode), &priv->fअगरo_lock);
		अगर (ret != माप(scancode))
			वापस;
		sparse_keymap_report_event(priv->input, scancode, 0, false);
		dev_dbg(&priv->input->dev,
			"Pop scancode from ringbuffer [0x%x]\n", scancode);
	पूर्ण
पूर्ण

अटल व्योम acpi_fujitsu_laptop_notअगरy(काष्ठा acpi_device *device, u32 event)
अणु
	काष्ठा fujitsu_laptop *priv = acpi_driver_data(device);
	अचिन्हित दीर्घ flags;
	पूर्णांक scancode, i = 0;
	अचिन्हित पूर्णांक irb;

	अगर (event != ACPI_FUJITSU_NOTIFY_CODE) अणु
		acpi_handle_info(device->handle, "Unsupported event [0x%x]\n",
				 event);
		sparse_keymap_report_event(priv->input, -1, 1, true);
		वापस;
	पूर्ण

	अगर (priv->flags_supported)
		priv->flags_state = call_fext_func(device, FUNC_FLAGS, 0x4, 0x0,
						   0x0);

	जबतक ((irb = call_fext_func(device,
				     FUNC_BUTTONS, 0x1, 0x0, 0x0)) != 0 &&
	       i++ < MAX_HOTKEY_RINGBUFFER_SIZE) अणु
		scancode = irb & 0x4ff;
		अगर (sparse_keymap_entry_from_scancode(priv->input, scancode))
			acpi_fujitsu_laptop_press(device, scancode);
		अन्यथा अगर (scancode == 0)
			acpi_fujitsu_laptop_release(device);
		अन्यथा
			acpi_handle_info(device->handle,
					 "Unknown GIRB result [%x]\n", irb);
	पूर्ण

	/*
	 * First seen on the Skylake-based Lअगरebook E736/E746/E756), the
	 * touchpad toggle hotkey (Fn+F4) is handled in software. Other models
	 * have since added additional "soft keys". These are reported in the
	 * status flags queried using FUNC_FLAGS.
	 */
	अगर (priv->flags_supported & (FLAG_SOFTKEYS)) अणु
		flags = call_fext_func(device, FUNC_FLAGS, 0x1, 0x0, 0x0);
		flags &= (FLAG_SOFTKEYS);
		क्रम_each_set_bit(i, &flags, BITS_PER_LONG)
			sparse_keymap_report_event(priv->input, BIT(i), 1, true);
	पूर्ण
पूर्ण

/* Initialization */

अटल स्थिर काष्ठा acpi_device_id fujitsu_bl_device_ids[] = अणु
	अणुACPI_FUJITSU_BL_HID, 0पूर्ण,
	अणु"", 0पूर्ण,
पूर्ण;

अटल काष्ठा acpi_driver acpi_fujitsu_bl_driver = अणु
	.name = ACPI_FUJITSU_BL_DRIVER_NAME,
	.class = ACPI_FUJITSU_CLASS,
	.ids = fujitsu_bl_device_ids,
	.ops = अणु
		.add = acpi_fujitsu_bl_add,
		.notअगरy = acpi_fujitsu_bl_notअगरy,
		पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा acpi_device_id fujitsu_laptop_device_ids[] = अणु
	अणुACPI_FUJITSU_LAPTOP_HID, 0पूर्ण,
	अणु"", 0पूर्ण,
पूर्ण;

अटल काष्ठा acpi_driver acpi_fujitsu_laptop_driver = अणु
	.name = ACPI_FUJITSU_LAPTOP_DRIVER_NAME,
	.class = ACPI_FUJITSU_CLASS,
	.ids = fujitsu_laptop_device_ids,
	.ops = अणु
		.add = acpi_fujitsu_laptop_add,
		.हटाओ = acpi_fujitsu_laptop_हटाओ,
		.notअगरy = acpi_fujitsu_laptop_notअगरy,
		पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा acpi_device_id fujitsu_ids[] __used = अणु
	अणुACPI_FUJITSU_BL_HID, 0पूर्ण,
	अणुACPI_FUJITSU_LAPTOP_HID, 0पूर्ण,
	अणु"", 0पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(acpi, fujitsu_ids);

अटल पूर्णांक __init fujitsu_init(व्योम)
अणु
	पूर्णांक ret;

	ret = acpi_bus_रेजिस्टर_driver(&acpi_fujitsu_bl_driver);
	अगर (ret)
		वापस ret;

	/* Register platक्रमm stuff */

	ret = platक्रमm_driver_रेजिस्टर(&fujitsu_pf_driver);
	अगर (ret)
		जाओ err_unरेजिस्टर_acpi;

	/* Register laptop driver */

	ret = acpi_bus_रेजिस्टर_driver(&acpi_fujitsu_laptop_driver);
	अगर (ret)
		जाओ err_unरेजिस्टर_platक्रमm_driver;

	pr_info("driver " FUJITSU_DRIVER_VERSION " successfully loaded\n");

	वापस 0;

err_unरेजिस्टर_platक्रमm_driver:
	platक्रमm_driver_unरेजिस्टर(&fujitsu_pf_driver);
err_unरेजिस्टर_acpi:
	acpi_bus_unरेजिस्टर_driver(&acpi_fujitsu_bl_driver);

	वापस ret;
पूर्ण

अटल व्योम __निकास fujitsu_cleanup(व्योम)
अणु
	acpi_bus_unरेजिस्टर_driver(&acpi_fujitsu_laptop_driver);

	platक्रमm_driver_unरेजिस्टर(&fujitsu_pf_driver);

	acpi_bus_unरेजिस्टर_driver(&acpi_fujitsu_bl_driver);

	pr_info("driver unloaded\n");
पूर्ण

module_init(fujitsu_init);
module_निकास(fujitsu_cleanup);

module_param(use_alt_lcd_levels, पूर्णांक, 0644);
MODULE_PARM_DESC(use_alt_lcd_levels, "Interface used for setting LCD brightness level (-1 = auto, 0 = force SBLL, 1 = force SBL2)");
module_param(disable_brightness_adjust, bool, 0644);
MODULE_PARM_DESC(disable_brightness_adjust, "Disable LCD brightness adjustment");

MODULE_AUTHOR("Jonathan Woithe, Peter Gruber, Tony Vroon");
MODULE_DESCRIPTION("Fujitsu laptop extras support");
MODULE_VERSION(FUJITSU_DRIVER_VERSION);
MODULE_LICENSE("GPL");
