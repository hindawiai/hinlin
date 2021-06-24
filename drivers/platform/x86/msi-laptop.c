<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*-*-linux-c-*-*/

/*
  Copyright (C) 2006 Lennart Poettering <mzxreary (at) 0poपूर्णांकer (करोt) de>

 */

/*
 * msi-laptop.c - MSI S270 laptop support. This laptop is sold under
 * various bअक्रमs, including "Cytron/TCM/Medion/Tchibo MD96100".
 *
 * Driver also supports S271, S420 models.
 *
 * This driver exports a few files in /sys/devices/platक्रमm/msi-laptop-pf/:
 *
 *   lcd_level - Screen brightness: contains a single पूर्णांकeger in the
 *   range 0..8. (rw)
 *
 *   स्वतः_brightness - Enable स्वतःmatic brightness control: contains
 *   either 0 or 1. If set to 1 the hardware adjusts the screen
 *   brightness स्वतःmatically when the घातer cord is
 *   plugged/unplugged. (rw)
 *
 *   wlan - WLAN subप्रणाली enabled: contains either 0 or 1. (ro)
 *
 *   bluetooth - Bluetooth subप्रणाली enabled: contains either 0 or 1
 *   Please note that this file is स्थिरantly 0 अगर no Bluetooth
 *   hardware is available. (ro)
 *
 * In addition to these platक्रमm device attributes the driver
 * रेजिस्टरs itself in the Linux backlight control subप्रणाली and is
 * available to userspace under /sys/class/backlight/msi-laptop-bl/.
 *
 * This driver might work on other laptops produced by MSI. If you
 * want to try it you can pass क्रमce=1 as argument to the module which
 * will क्रमce it to load even when the DMI data करोesn't identअगरy the
 * laptop as MSI S270. YMMV.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/acpi.h>
#समावेश <linux/dmi.h>
#समावेश <linux/backlight.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/rfसमाप्त.h>
#समावेश <linux/i8042.h>
#समावेश <linux/input.h>
#समावेश <linux/input/sparse-keymap.h>
#समावेश <acpi/video.h>

#घोषणा MSI_DRIVER_VERSION "0.5"

#घोषणा MSI_LCD_LEVEL_MAX 9

#घोषणा MSI_EC_COMMAND_WIRELESS 0x10
#घोषणा MSI_EC_COMMAND_LCD_LEVEL 0x11

#घोषणा MSI_STANDARD_EC_COMMAND_ADDRESS	0x2e
#घोषणा MSI_STANDARD_EC_BLUETOOTH_MASK	(1 << 0)
#घोषणा MSI_STANDARD_EC_WEBCAM_MASK	(1 << 1)
#घोषणा MSI_STANDARD_EC_WLAN_MASK	(1 << 3)
#घोषणा MSI_STANDARD_EC_3G_MASK		(1 << 4)

/* For set SCM load flag to disable BIOS fn key */
#घोषणा MSI_STANDARD_EC_SCM_LOAD_ADDRESS	0x2d
#घोषणा MSI_STANDARD_EC_SCM_LOAD_MASK		(1 << 0)

#घोषणा MSI_STANDARD_EC_FUNCTIONS_ADDRESS	0xe4
/* Power LED is orange - Turbo mode */
#घोषणा MSI_STANDARD_EC_TURBO_MASK		(1 << 1)
/* Power LED is green - ECO mode */
#घोषणा MSI_STANDARD_EC_ECO_MASK		(1 << 3)
/* Touchpad is turned on */
#घोषणा MSI_STANDARD_EC_TOUCHPAD_MASK		(1 << 4)
/* If this bit != bit 1, turbo mode can't be toggled */
#घोषणा MSI_STANDARD_EC_TURBO_COOLDOWN_MASK	(1 << 7)

#घोषणा MSI_STANDARD_EC_FAN_ADDRESS		0x33
/* If zero, fan rotates at maximal speed */
#घोषणा MSI_STANDARD_EC_AUTOFAN_MASK		(1 << 0)

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक msi_laptop_resume(काष्ठा device *device);
#पूर्ण_अगर
अटल SIMPLE_DEV_PM_OPS(msi_laptop_pm, शून्य, msi_laptop_resume);

#घोषणा MSI_STANDARD_EC_DEVICES_EXISTS_ADDRESS	0x2f

अटल bool क्रमce;
module_param(क्रमce, bool, 0);
MODULE_PARM_DESC(क्रमce, "Force driver load, ignore DMI data");

अटल पूर्णांक स्वतः_brightness;
module_param(स्वतः_brightness, पूर्णांक, 0);
MODULE_PARM_DESC(स्वतः_brightness, "Enable automatic brightness control (0: disabled; 1: enabled; 2: don't touch)");

अटल स्थिर काष्ठा key_entry msi_laptop_keymap[] = अणु
	अणुKE_KEY, KEY_TOUCHPAD_ON, अणुKEY_TOUCHPAD_ONपूर्ण पूर्ण,	/* Touch Pad On */
	अणुKE_KEY, KEY_TOUCHPAD_OFF, अणुKEY_TOUCHPAD_OFFपूर्ण पूर्ण,/* Touch Pad On */
	अणुKE_END, 0पूर्ण
पूर्ण;

अटल काष्ठा input_dev *msi_laptop_input_dev;

अटल पूर्णांक wlan_s, bluetooth_s, threeg_s;
अटल पूर्णांक threeg_exists;
अटल काष्ठा rfसमाप्त *rfk_wlan, *rfk_bluetooth, *rfk_threeg;

/* MSI laptop quirks */
काष्ठा quirk_entry अणु
	bool old_ec_model;

	/* Some MSI 3G netbook only have one fn key to control
	 * Wlan/Bluetooth/3G, those netbook will load the SCM (winकरोws app) to
	 * disable the original Wlan/Bluetooth control by BIOS when user press
	 * fn key, then control Wlan/Bluetooth/3G by SCM (software control by
	 * OS). Without SCM, user cann't on/off 3G module on those 3G netbook.
	 * On Linux, msi-laptop driver will करो the same thing to disable the
	 * original BIOS control, then might need use HAL or other userland
	 * application to करो the software control that simulate with SCM.
	 * e.g. MSI N034 netbook
	 */
	bool load_scm_model;

	/* Some MSI laptops need delay beक्रमe पढ़ोing from EC */
	bool ec_delay;

	/* Some MSI Wind netbooks (e.g. MSI Wind U100) need loading SCM to get
	 * some features working (e.g. ECO mode), but we cannot change
	 * Wlan/Bluetooth state in software and we can only पढ़ो its state.
	 */
	bool ec_पढ़ो_only;
पूर्ण;

अटल काष्ठा quirk_entry *quirks;

/* Hardware access */

अटल पूर्णांक set_lcd_level(पूर्णांक level)
अणु
	u8 buf[2];

	अगर (level < 0 || level >= MSI_LCD_LEVEL_MAX)
		वापस -EINVAL;

	buf[0] = 0x80;
	buf[1] = (u8) (level*31);

	वापस ec_transaction(MSI_EC_COMMAND_LCD_LEVEL, buf, माप(buf),
			      शून्य, 0);
पूर्ण

अटल पूर्णांक get_lcd_level(व्योम)
अणु
	u8 wdata = 0, rdata;
	पूर्णांक result;

	result = ec_transaction(MSI_EC_COMMAND_LCD_LEVEL, &wdata, 1,
				&rdata, 1);
	अगर (result < 0)
		वापस result;

	वापस (पूर्णांक) rdata / 31;
पूर्ण

अटल पूर्णांक get_स्वतः_brightness(व्योम)
अणु
	u8 wdata = 4, rdata;
	पूर्णांक result;

	result = ec_transaction(MSI_EC_COMMAND_LCD_LEVEL, &wdata, 1,
				&rdata, 1);
	अगर (result < 0)
		वापस result;

	वापस !!(rdata & 8);
पूर्ण

अटल पूर्णांक set_स्वतः_brightness(पूर्णांक enable)
अणु
	u8 wdata[2], rdata;
	पूर्णांक result;

	wdata[0] = 4;

	result = ec_transaction(MSI_EC_COMMAND_LCD_LEVEL, wdata, 1,
				&rdata, 1);
	अगर (result < 0)
		वापस result;

	wdata[0] = 0x84;
	wdata[1] = (rdata & 0xF7) | (enable ? 8 : 0);

	वापस ec_transaction(MSI_EC_COMMAND_LCD_LEVEL, wdata, 2,
			      शून्य, 0);
पूर्ण

अटल sमाप_प्रकार set_device_state(स्थिर अक्षर *buf, माप_प्रकार count, u8 mask)
अणु
	पूर्णांक status;
	u8 wdata = 0, rdata;
	पूर्णांक result;

	अगर (माला_पूछो(buf, "%i", &status) != 1 || (status < 0 || status > 1))
		वापस -EINVAL;

	अगर (quirks->ec_पढ़ो_only)
		वापस -EOPNOTSUPP;

	/* पढ़ो current device state */
	result = ec_पढ़ो(MSI_STANDARD_EC_COMMAND_ADDRESS, &rdata);
	अगर (result < 0)
		वापस result;

	अगर (!!(rdata & mask) != status) अणु
		/* reverse device bit */
		अगर (rdata & mask)
			wdata = rdata & ~mask;
		अन्यथा
			wdata = rdata | mask;

		result = ec_ग_लिखो(MSI_STANDARD_EC_COMMAND_ADDRESS, wdata);
		अगर (result < 0)
			वापस result;
	पूर्ण

	वापस count;
पूर्ण

अटल पूर्णांक get_wireless_state(पूर्णांक *wlan, पूर्णांक *bluetooth)
अणु
	u8 wdata = 0, rdata;
	पूर्णांक result;

	result = ec_transaction(MSI_EC_COMMAND_WIRELESS, &wdata, 1, &rdata, 1);
	अगर (result < 0)
		वापस result;

	अगर (wlan)
		*wlan = !!(rdata & 8);

	अगर (bluetooth)
		*bluetooth = !!(rdata & 128);

	वापस 0;
पूर्ण

अटल पूर्णांक get_wireless_state_ec_standard(व्योम)
अणु
	u8 rdata;
	पूर्णांक result;

	result = ec_पढ़ो(MSI_STANDARD_EC_COMMAND_ADDRESS, &rdata);
	अगर (result < 0)
		वापस result;

	wlan_s = !!(rdata & MSI_STANDARD_EC_WLAN_MASK);

	bluetooth_s = !!(rdata & MSI_STANDARD_EC_BLUETOOTH_MASK);

	threeg_s = !!(rdata & MSI_STANDARD_EC_3G_MASK);

	वापस 0;
पूर्ण

अटल पूर्णांक get_threeg_exists(व्योम)
अणु
	u8 rdata;
	पूर्णांक result;

	result = ec_पढ़ो(MSI_STANDARD_EC_DEVICES_EXISTS_ADDRESS, &rdata);
	अगर (result < 0)
		वापस result;

	threeg_exists = !!(rdata & MSI_STANDARD_EC_3G_MASK);

	वापस 0;
पूर्ण

/* Backlight device stuff */

अटल पूर्णांक bl_get_brightness(काष्ठा backlight_device *b)
अणु
	वापस get_lcd_level();
पूर्ण


अटल पूर्णांक bl_update_status(काष्ठा backlight_device *b)
अणु
	वापस set_lcd_level(b->props.brightness);
पूर्ण

अटल स्थिर काष्ठा backlight_ops msibl_ops = अणु
	.get_brightness = bl_get_brightness,
	.update_status  = bl_update_status,
पूर्ण;

अटल काष्ठा backlight_device *msibl_device;

/* Platक्रमm device */

अटल sमाप_प्रकार show_wlan(काष्ठा device *dev,
	काष्ठा device_attribute *attr, अक्षर *buf)
अणु

	पूर्णांक ret, enabled = 0;

	अगर (quirks->old_ec_model) अणु
		ret = get_wireless_state(&enabled, शून्य);
	पूर्ण अन्यथा अणु
		ret = get_wireless_state_ec_standard();
		enabled = wlan_s;
	पूर्ण
	अगर (ret < 0)
		वापस ret;

	वापस प्र_लिखो(buf, "%i\n", enabled);
पूर्ण

अटल sमाप_प्रकार store_wlan(काष्ठा device *dev,
	काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	वापस set_device_state(buf, count, MSI_STANDARD_EC_WLAN_MASK);
पूर्ण

अटल sमाप_प्रकार show_bluetooth(काष्ठा device *dev,
	काष्ठा device_attribute *attr, अक्षर *buf)
अणु

	पूर्णांक ret, enabled = 0;

	अगर (quirks->old_ec_model) अणु
		ret = get_wireless_state(शून्य, &enabled);
	पूर्ण अन्यथा अणु
		ret = get_wireless_state_ec_standard();
		enabled = bluetooth_s;
	पूर्ण
	अगर (ret < 0)
		वापस ret;

	वापस प्र_लिखो(buf, "%i\n", enabled);
पूर्ण

अटल sमाप_प्रकार store_bluetooth(काष्ठा device *dev,
	काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	वापस set_device_state(buf, count, MSI_STANDARD_EC_BLUETOOTH_MASK);
पूर्ण

अटल sमाप_प्रकार show_threeg(काष्ठा device *dev,
	काष्ठा device_attribute *attr, अक्षर *buf)
अणु

	पूर्णांक ret;

	/* old msi ec not support 3G */
	अगर (quirks->old_ec_model)
		वापस -ENODEV;

	ret = get_wireless_state_ec_standard();
	अगर (ret < 0)
		वापस ret;

	वापस प्र_लिखो(buf, "%i\n", threeg_s);
पूर्ण

अटल sमाप_प्रकार store_threeg(काष्ठा device *dev,
	काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	वापस set_device_state(buf, count, MSI_STANDARD_EC_3G_MASK);
पूर्ण

अटल sमाप_प्रकार show_lcd_level(काष्ठा device *dev,
	काष्ठा device_attribute *attr, अक्षर *buf)
अणु

	पूर्णांक ret;

	ret = get_lcd_level();
	अगर (ret < 0)
		वापस ret;

	वापस प्र_लिखो(buf, "%i\n", ret);
पूर्ण

अटल sमाप_प्रकार store_lcd_level(काष्ठा device *dev,
	काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु

	पूर्णांक level, ret;

	अगर (माला_पूछो(buf, "%i", &level) != 1 ||
	    (level < 0 || level >= MSI_LCD_LEVEL_MAX))
		वापस -EINVAL;

	ret = set_lcd_level(level);
	अगर (ret < 0)
		वापस ret;

	वापस count;
पूर्ण

अटल sमाप_प्रकार show_स्वतः_brightness(काष्ठा device *dev,
	काष्ठा device_attribute *attr, अक्षर *buf)
अणु

	पूर्णांक ret;

	ret = get_स्वतः_brightness();
	अगर (ret < 0)
		वापस ret;

	वापस प्र_लिखो(buf, "%i\n", ret);
पूर्ण

अटल sमाप_प्रकार store_स्वतः_brightness(काष्ठा device *dev,
	काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु

	पूर्णांक enable, ret;

	अगर (माला_पूछो(buf, "%i", &enable) != 1 || (enable != (enable & 1)))
		वापस -EINVAL;

	ret = set_स्वतः_brightness(enable);
	अगर (ret < 0)
		वापस ret;

	वापस count;
पूर्ण

अटल sमाप_प्रकार show_touchpad(काष्ठा device *dev,
	काष्ठा device_attribute *attr, अक्षर *buf)
अणु

	u8 rdata;
	पूर्णांक result;

	result = ec_पढ़ो(MSI_STANDARD_EC_FUNCTIONS_ADDRESS, &rdata);
	अगर (result < 0)
		वापस result;

	वापस प्र_लिखो(buf, "%i\n", !!(rdata & MSI_STANDARD_EC_TOUCHPAD_MASK));
पूर्ण

अटल sमाप_प्रकार show_turbo(काष्ठा device *dev,
	काष्ठा device_attribute *attr, अक्षर *buf)
अणु

	u8 rdata;
	पूर्णांक result;

	result = ec_पढ़ो(MSI_STANDARD_EC_FUNCTIONS_ADDRESS, &rdata);
	अगर (result < 0)
		वापस result;

	वापस प्र_लिखो(buf, "%i\n", !!(rdata & MSI_STANDARD_EC_TURBO_MASK));
पूर्ण

अटल sमाप_प्रकार show_eco(काष्ठा device *dev,
	काष्ठा device_attribute *attr, अक्षर *buf)
अणु

	u8 rdata;
	पूर्णांक result;

	result = ec_पढ़ो(MSI_STANDARD_EC_FUNCTIONS_ADDRESS, &rdata);
	अगर (result < 0)
		वापस result;

	वापस प्र_लिखो(buf, "%i\n", !!(rdata & MSI_STANDARD_EC_ECO_MASK));
पूर्ण

अटल sमाप_प्रकार show_turbo_coolकरोwn(काष्ठा device *dev,
	काष्ठा device_attribute *attr, अक्षर *buf)
अणु

	u8 rdata;
	पूर्णांक result;

	result = ec_पढ़ो(MSI_STANDARD_EC_FUNCTIONS_ADDRESS, &rdata);
	अगर (result < 0)
		वापस result;

	वापस प्र_लिखो(buf, "%i\n", (!!(rdata & MSI_STANDARD_EC_TURBO_MASK)) |
		(!!(rdata & MSI_STANDARD_EC_TURBO_COOLDOWN_MASK) << 1));
पूर्ण

अटल sमाप_प्रकार show_स्वतः_fan(काष्ठा device *dev,
	काष्ठा device_attribute *attr, अक्षर *buf)
अणु

	u8 rdata;
	पूर्णांक result;

	result = ec_पढ़ो(MSI_STANDARD_EC_FAN_ADDRESS, &rdata);
	अगर (result < 0)
		वापस result;

	वापस प्र_लिखो(buf, "%i\n", !!(rdata & MSI_STANDARD_EC_AUTOFAN_MASK));
पूर्ण

अटल sमाप_प्रकार store_स्वतः_fan(काष्ठा device *dev,
	काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु

	पूर्णांक enable, result;

	अगर (माला_पूछो(buf, "%i", &enable) != 1 || (enable != (enable & 1)))
		वापस -EINVAL;

	result = ec_ग_लिखो(MSI_STANDARD_EC_FAN_ADDRESS, enable);
	अगर (result < 0)
		वापस result;

	वापस count;
पूर्ण

अटल DEVICE_ATTR(lcd_level, 0644, show_lcd_level, store_lcd_level);
अटल DEVICE_ATTR(स्वतः_brightness, 0644, show_स्वतः_brightness,
		   store_स्वतः_brightness);
अटल DEVICE_ATTR(bluetooth, 0444, show_bluetooth, शून्य);
अटल DEVICE_ATTR(wlan, 0444, show_wlan, शून्य);
अटल DEVICE_ATTR(threeg, 0444, show_threeg, शून्य);
अटल DEVICE_ATTR(touchpad, 0444, show_touchpad, शून्य);
अटल DEVICE_ATTR(turbo_mode, 0444, show_turbo, शून्य);
अटल DEVICE_ATTR(eco_mode, 0444, show_eco, शून्य);
अटल DEVICE_ATTR(turbo_coolकरोwn, 0444, show_turbo_coolकरोwn, शून्य);
अटल DEVICE_ATTR(स्वतः_fan, 0644, show_स्वतः_fan, store_स्वतः_fan);

अटल काष्ठा attribute *msipf_attributes[] = अणु
	&dev_attr_bluetooth.attr,
	&dev_attr_wlan.attr,
	&dev_attr_touchpad.attr,
	&dev_attr_turbo_mode.attr,
	&dev_attr_eco_mode.attr,
	&dev_attr_turbo_coolकरोwn.attr,
	&dev_attr_स्वतः_fan.attr,
	शून्य
पूर्ण;

अटल काष्ठा attribute *msipf_old_attributes[] = अणु
	&dev_attr_lcd_level.attr,
	&dev_attr_स्वतः_brightness.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group msipf_attribute_group = अणु
	.attrs = msipf_attributes
पूर्ण;

अटल स्थिर काष्ठा attribute_group msipf_old_attribute_group = अणु
	.attrs = msipf_old_attributes
पूर्ण;

अटल काष्ठा platक्रमm_driver msipf_driver = अणु
	.driver = अणु
		.name = "msi-laptop-pf",
		.pm = &msi_laptop_pm,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device *msipf_device;

/* Initialization */

अटल काष्ठा quirk_entry quirk_old_ec_model = अणु
	.old_ec_model = true,
पूर्ण;

अटल काष्ठा quirk_entry quirk_load_scm_model = अणु
	.load_scm_model = true,
	.ec_delay = true,
पूर्ण;

अटल काष्ठा quirk_entry quirk_load_scm_ro_model = अणु
	.load_scm_model = true,
	.ec_पढ़ो_only = true,
पूर्ण;

अटल पूर्णांक dmi_check_cb(स्थिर काष्ठा dmi_प्रणाली_id *dmi)
अणु
	pr_info("Identified laptop model '%s'\n", dmi->ident);

	quirks = dmi->driver_data;

	वापस 1;
पूर्ण

अटल स्थिर काष्ठा dmi_प्रणाली_id msi_dmi_table[] __initस्थिर = अणु
	अणु
		.ident = "MSI S270",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "MICRO-STAR INT'L CO.,LTD"),
			DMI_MATCH(DMI_PRODUCT_NAME, "MS-1013"),
			DMI_MATCH(DMI_PRODUCT_VERSION, "0131"),
			DMI_MATCH(DMI_CHASSIS_VENDOR,
				  "MICRO-STAR INT'L CO.,LTD")
		पूर्ण,
		.driver_data = &quirk_old_ec_model,
		.callback = dmi_check_cb
	पूर्ण,
	अणु
		.ident = "MSI S271",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Micro-Star International"),
			DMI_MATCH(DMI_PRODUCT_NAME, "MS-1058"),
			DMI_MATCH(DMI_PRODUCT_VERSION, "0581"),
			DMI_MATCH(DMI_BOARD_NAME, "MS-1058")
		पूर्ण,
		.driver_data = &quirk_old_ec_model,
		.callback = dmi_check_cb
	पूर्ण,
	अणु
		.ident = "MSI S420",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Micro-Star International"),
			DMI_MATCH(DMI_PRODUCT_NAME, "MS-1412"),
			DMI_MATCH(DMI_BOARD_VENDOR, "MSI"),
			DMI_MATCH(DMI_BOARD_NAME, "MS-1412")
		पूर्ण,
		.driver_data = &quirk_old_ec_model,
		.callback = dmi_check_cb
	पूर्ण,
	अणु
		.ident = "Medion MD96100",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "NOTEBOOK"),
			DMI_MATCH(DMI_PRODUCT_NAME, "SAM2000"),
			DMI_MATCH(DMI_PRODUCT_VERSION, "0131"),
			DMI_MATCH(DMI_CHASSIS_VENDOR,
				  "MICRO-STAR INT'L CO.,LTD")
		पूर्ण,
		.driver_data = &quirk_old_ec_model,
		.callback = dmi_check_cb
	पूर्ण,
	अणु
		.ident = "MSI N034",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR,
				"MICRO-STAR INTERNATIONAL CO., LTD"),
			DMI_MATCH(DMI_PRODUCT_NAME, "MS-N034"),
			DMI_MATCH(DMI_CHASSIS_VENDOR,
			"MICRO-STAR INTERNATIONAL CO., LTD")
		पूर्ण,
		.driver_data = &quirk_load_scm_model,
		.callback = dmi_check_cb
	पूर्ण,
	अणु
		.ident = "MSI N051",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR,
				"MICRO-STAR INTERNATIONAL CO., LTD"),
			DMI_MATCH(DMI_PRODUCT_NAME, "MS-N051"),
			DMI_MATCH(DMI_CHASSIS_VENDOR,
			"MICRO-STAR INTERNATIONAL CO., LTD")
		पूर्ण,
		.driver_data = &quirk_load_scm_model,
		.callback = dmi_check_cb
	पूर्ण,
	अणु
		.ident = "MSI N014",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR,
				"MICRO-STAR INTERNATIONAL CO., LTD"),
			DMI_MATCH(DMI_PRODUCT_NAME, "MS-N014"),
		पूर्ण,
		.driver_data = &quirk_load_scm_model,
		.callback = dmi_check_cb
	पूर्ण,
	अणु
		.ident = "MSI CR620",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR,
				"Micro-Star International"),
			DMI_MATCH(DMI_PRODUCT_NAME, "CR620"),
		पूर्ण,
		.driver_data = &quirk_load_scm_model,
		.callback = dmi_check_cb
	पूर्ण,
	अणु
		.ident = "MSI U270",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR,
				"Micro-Star International Co., Ltd."),
			DMI_MATCH(DMI_PRODUCT_NAME, "U270 series"),
		पूर्ण,
		.driver_data = &quirk_load_scm_model,
		.callback = dmi_check_cb
	पूर्ण,
	अणु
		.ident = "MSI U90/U100",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR,
				"MICRO-STAR INTERNATIONAL CO., LTD"),
			DMI_MATCH(DMI_PRODUCT_NAME, "U90/U100"),
		पूर्ण,
		.driver_data = &quirk_load_scm_ro_model,
		.callback = dmi_check_cb
	पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल पूर्णांक rfसमाप्त_bluetooth_set(व्योम *data, bool blocked)
अणु
	/* Do something with blocked...*/
	/*
	 * blocked == false is on
	 * blocked == true is off
	 */
	पूर्णांक result = set_device_state(blocked ? "0" : "1", 0,
			MSI_STANDARD_EC_BLUETOOTH_MASK);

	वापस min(result, 0);
पूर्ण

अटल पूर्णांक rfसमाप्त_wlan_set(व्योम *data, bool blocked)
अणु
	पूर्णांक result = set_device_state(blocked ? "0" : "1", 0,
			MSI_STANDARD_EC_WLAN_MASK);

	वापस min(result, 0);
पूर्ण

अटल पूर्णांक rfसमाप्त_threeg_set(व्योम *data, bool blocked)
अणु
	पूर्णांक result = set_device_state(blocked ? "0" : "1", 0,
			MSI_STANDARD_EC_3G_MASK);

	वापस min(result, 0);
पूर्ण

अटल स्थिर काष्ठा rfसमाप्त_ops rfसमाप्त_bluetooth_ops = अणु
	.set_block = rfसमाप्त_bluetooth_set
पूर्ण;

अटल स्थिर काष्ठा rfसमाप्त_ops rfसमाप्त_wlan_ops = अणु
	.set_block = rfसमाप्त_wlan_set
पूर्ण;

अटल स्थिर काष्ठा rfसमाप्त_ops rfसमाप्त_threeg_ops = अणु
	.set_block = rfसमाप्त_threeg_set
पूर्ण;

अटल व्योम rfसमाप्त_cleanup(व्योम)
अणु
	अगर (rfk_bluetooth) अणु
		rfसमाप्त_unरेजिस्टर(rfk_bluetooth);
		rfसमाप्त_destroy(rfk_bluetooth);
	पूर्ण

	अगर (rfk_threeg) अणु
		rfसमाप्त_unरेजिस्टर(rfk_threeg);
		rfसमाप्त_destroy(rfk_threeg);
	पूर्ण

	अगर (rfk_wlan) अणु
		rfसमाप्त_unरेजिस्टर(rfk_wlan);
		rfसमाप्त_destroy(rfk_wlan);
	पूर्ण
पूर्ण

अटल bool msi_rfसमाप्त_set_state(काष्ठा rfसमाप्त *rfसमाप्त, bool blocked)
अणु
	अगर (quirks->ec_पढ़ो_only)
		वापस rfसमाप्त_set_hw_state(rfसमाप्त, blocked);
	अन्यथा
		वापस rfसमाप्त_set_sw_state(rfसमाप्त, blocked);
पूर्ण

अटल व्योम msi_update_rfसमाप्त(काष्ठा work_काष्ठा *ignored)
अणु
	get_wireless_state_ec_standard();

	अगर (rfk_wlan)
		msi_rfसमाप्त_set_state(rfk_wlan, !wlan_s);
	अगर (rfk_bluetooth)
		msi_rfसमाप्त_set_state(rfk_bluetooth, !bluetooth_s);
	अगर (rfk_threeg)
		msi_rfसमाप्त_set_state(rfk_threeg, !threeg_s);
पूर्ण
अटल DECLARE_DELAYED_WORK(msi_rfसमाप्त_dwork, msi_update_rfसमाप्त);
अटल DECLARE_WORK(msi_rfसमाप्त_work, msi_update_rfसमाप्त);

अटल व्योम msi_send_touchpad_key(काष्ठा work_काष्ठा *ignored)
अणु
	u8 rdata;
	पूर्णांक result;

	result = ec_पढ़ो(MSI_STANDARD_EC_FUNCTIONS_ADDRESS, &rdata);
	अगर (result < 0)
		वापस;

	sparse_keymap_report_event(msi_laptop_input_dev,
		(rdata & MSI_STANDARD_EC_TOUCHPAD_MASK) ?
		KEY_TOUCHPAD_ON : KEY_TOUCHPAD_OFF, 1, true);
पूर्ण
अटल DECLARE_DELAYED_WORK(msi_touchpad_dwork, msi_send_touchpad_key);
अटल DECLARE_WORK(msi_touchpad_work, msi_send_touchpad_key);

अटल bool msi_laptop_i8042_filter(अचिन्हित अक्षर data, अचिन्हित अक्षर str,
				काष्ठा serio *port)
अणु
	अटल bool extended;

	अगर (str & I8042_STR_AUXDATA)
		वापस false;

	/* 0x54 wwan, 0x62 bluetooth, 0x76 wlan, 0xE4 touchpad toggle*/
	अगर (unlikely(data == 0xe0)) अणु
		extended = true;
		वापस false;
	पूर्ण अन्यथा अगर (unlikely(extended)) अणु
		extended = false;
		चयन (data) अणु
		हाल 0xE4:
			अगर (quirks->ec_delay) अणु
				schedule_delayed_work(&msi_touchpad_dwork,
					round_jअगरfies_relative(0.5 * HZ));
			पूर्ण अन्यथा
				schedule_work(&msi_touchpad_work);
			अवरोध;
		हाल 0x54:
		हाल 0x62:
		हाल 0x76:
			अगर (quirks->ec_delay) अणु
				schedule_delayed_work(&msi_rfसमाप्त_dwork,
					round_jअगरfies_relative(0.5 * HZ));
			पूर्ण अन्यथा
				schedule_work(&msi_rfसमाप्त_work);
			अवरोध;
		पूर्ण
	पूर्ण

	वापस false;
पूर्ण

अटल व्योम msi_init_rfसमाप्त(काष्ठा work_काष्ठा *ignored)
अणु
	अगर (rfk_wlan) अणु
		rfसमाप्त_set_sw_state(rfk_wlan, !wlan_s);
		rfसमाप्त_wlan_set(शून्य, !wlan_s);
	पूर्ण
	अगर (rfk_bluetooth) अणु
		rfसमाप्त_set_sw_state(rfk_bluetooth, !bluetooth_s);
		rfसमाप्त_bluetooth_set(शून्य, !bluetooth_s);
	पूर्ण
	अगर (rfk_threeg) अणु
		rfसमाप्त_set_sw_state(rfk_threeg, !threeg_s);
		rfसमाप्त_threeg_set(शून्य, !threeg_s);
	पूर्ण
पूर्ण
अटल DECLARE_DELAYED_WORK(msi_rfसमाप्त_init, msi_init_rfसमाप्त);

अटल पूर्णांक rfसमाप्त_init(काष्ठा platक्रमm_device *sdev)
अणु
	/* add rfसमाप्त */
	पूर्णांक retval;

	/* keep the hardware wireless state */
	get_wireless_state_ec_standard();

	rfk_bluetooth = rfसमाप्त_alloc("msi-bluetooth", &sdev->dev,
				RFKILL_TYPE_BLUETOOTH,
				&rfसमाप्त_bluetooth_ops, शून्य);
	अगर (!rfk_bluetooth) अणु
		retval = -ENOMEM;
		जाओ err_bluetooth;
	पूर्ण
	retval = rfसमाप्त_रेजिस्टर(rfk_bluetooth);
	अगर (retval)
		जाओ err_bluetooth;

	rfk_wlan = rfसमाप्त_alloc("msi-wlan", &sdev->dev, RFKILL_TYPE_WLAN,
				&rfसमाप्त_wlan_ops, शून्य);
	अगर (!rfk_wlan) अणु
		retval = -ENOMEM;
		जाओ err_wlan;
	पूर्ण
	retval = rfसमाप्त_रेजिस्टर(rfk_wlan);
	अगर (retval)
		जाओ err_wlan;

	अगर (threeg_exists) अणु
		rfk_threeg = rfसमाप्त_alloc("msi-threeg", &sdev->dev,
				RFKILL_TYPE_WWAN, &rfसमाप्त_threeg_ops, शून्य);
		अगर (!rfk_threeg) अणु
			retval = -ENOMEM;
			जाओ err_threeg;
		पूर्ण
		retval = rfसमाप्त_रेजिस्टर(rfk_threeg);
		अगर (retval)
			जाओ err_threeg;
	पूर्ण

	/* schedule to run rfसमाप्त state initial */
	अगर (quirks->ec_delay) अणु
		schedule_delayed_work(&msi_rfसमाप्त_init,
			round_jअगरfies_relative(1 * HZ));
	पूर्ण अन्यथा
		schedule_work(&msi_rfसमाप्त_work);

	वापस 0;

err_threeg:
	rfसमाप्त_destroy(rfk_threeg);
	अगर (rfk_wlan)
		rfसमाप्त_unरेजिस्टर(rfk_wlan);
err_wlan:
	rfसमाप्त_destroy(rfk_wlan);
	अगर (rfk_bluetooth)
		rfसमाप्त_unरेजिस्टर(rfk_bluetooth);
err_bluetooth:
	rfसमाप्त_destroy(rfk_bluetooth);

	वापस retval;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक msi_laptop_resume(काष्ठा device *device)
अणु
	u8 data;
	पूर्णांक result;

	अगर (!quirks->load_scm_model)
		वापस 0;

	/* set load SCM to disable hardware control by fn key */
	result = ec_पढ़ो(MSI_STANDARD_EC_SCM_LOAD_ADDRESS, &data);
	अगर (result < 0)
		वापस result;

	result = ec_ग_लिखो(MSI_STANDARD_EC_SCM_LOAD_ADDRESS,
		data | MSI_STANDARD_EC_SCM_LOAD_MASK);
	अगर (result < 0)
		वापस result;

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक __init msi_laptop_input_setup(व्योम)
अणु
	पूर्णांक err;

	msi_laptop_input_dev = input_allocate_device();
	अगर (!msi_laptop_input_dev)
		वापस -ENOMEM;

	msi_laptop_input_dev->name = "MSI Laptop hotkeys";
	msi_laptop_input_dev->phys = "msi-laptop/input0";
	msi_laptop_input_dev->id.bustype = BUS_HOST;

	err = sparse_keymap_setup(msi_laptop_input_dev,
		msi_laptop_keymap, शून्य);
	अगर (err)
		जाओ err_मुक्त_dev;

	err = input_रेजिस्टर_device(msi_laptop_input_dev);
	अगर (err)
		जाओ err_मुक्त_dev;

	वापस 0;

err_मुक्त_dev:
	input_मुक्त_device(msi_laptop_input_dev);
	वापस err;
पूर्ण

अटल पूर्णांक __init load_scm_model_init(काष्ठा platक्रमm_device *sdev)
अणु
	u8 data;
	पूर्णांक result;

	अगर (!quirks->ec_पढ़ो_only) अणु
		/* allow userland ग_लिखो sysfs file  */
		dev_attr_bluetooth.store = store_bluetooth;
		dev_attr_wlan.store = store_wlan;
		dev_attr_threeg.store = store_threeg;
		dev_attr_bluetooth.attr.mode |= S_IWUSR;
		dev_attr_wlan.attr.mode |= S_IWUSR;
		dev_attr_threeg.attr.mode |= S_IWUSR;
	पूर्ण

	/* disable hardware control by fn key */
	result = ec_पढ़ो(MSI_STANDARD_EC_SCM_LOAD_ADDRESS, &data);
	अगर (result < 0)
		वापस result;

	result = ec_ग_लिखो(MSI_STANDARD_EC_SCM_LOAD_ADDRESS,
		data | MSI_STANDARD_EC_SCM_LOAD_MASK);
	अगर (result < 0)
		वापस result;

	/* initial rfसमाप्त */
	result = rfसमाप्त_init(sdev);
	अगर (result < 0)
		जाओ fail_rfसमाप्त;

	/* setup input device */
	result = msi_laptop_input_setup();
	अगर (result)
		जाओ fail_input;

	result = i8042_install_filter(msi_laptop_i8042_filter);
	अगर (result) अणु
		pr_err("Unable to install key filter\n");
		जाओ fail_filter;
	पूर्ण

	वापस 0;

fail_filter:
	input_unरेजिस्टर_device(msi_laptop_input_dev);

fail_input:
	rfसमाप्त_cleanup();

fail_rfसमाप्त:

	वापस result;

पूर्ण

अटल पूर्णांक __init msi_init(व्योम)
अणु
	पूर्णांक ret;

	अगर (acpi_disabled)
		वापस -ENODEV;

	dmi_check_प्रणाली(msi_dmi_table);
	अगर (!quirks)
		/* quirks may be शून्य अगर no match in DMI table */
		quirks = &quirk_load_scm_model;
	अगर (क्रमce)
		quirks = &quirk_old_ec_model;

	अगर (!quirks->old_ec_model)
		get_threeg_exists();

	अगर (स्वतः_brightness < 0 || स्वतः_brightness > 2)
		वापस -EINVAL;

	/* Register backlight stuff */

	अगर (quirks->old_ec_model ||
	    acpi_video_get_backlight_type() == acpi_backlight_venकरोr) अणु
		काष्ठा backlight_properties props;
		स_रखो(&props, 0, माप(काष्ठा backlight_properties));
		props.type = BACKLIGHT_PLATFORM;
		props.max_brightness = MSI_LCD_LEVEL_MAX - 1;
		msibl_device = backlight_device_रेजिस्टर("msi-laptop-bl", शून्य,
							 शून्य, &msibl_ops,
							 &props);
		अगर (IS_ERR(msibl_device))
			वापस PTR_ERR(msibl_device);
	पूर्ण

	ret = platक्रमm_driver_रेजिस्टर(&msipf_driver);
	अगर (ret)
		जाओ fail_backlight;

	/* Register platक्रमm stuff */

	msipf_device = platक्रमm_device_alloc("msi-laptop-pf", -1);
	अगर (!msipf_device) अणु
		ret = -ENOMEM;
		जाओ fail_platक्रमm_driver;
	पूर्ण

	ret = platक्रमm_device_add(msipf_device);
	अगर (ret)
		जाओ fail_device_add;

	अगर (quirks->load_scm_model && (load_scm_model_init(msipf_device) < 0)) अणु
		ret = -EINVAL;
		जाओ fail_scm_model_init;
	पूर्ण

	ret = sysfs_create_group(&msipf_device->dev.kobj,
				 &msipf_attribute_group);
	अगर (ret)
		जाओ fail_create_group;

	अगर (!quirks->old_ec_model) अणु
		अगर (threeg_exists)
			ret = device_create_file(&msipf_device->dev,
						&dev_attr_threeg);
		अगर (ret)
			जाओ fail_create_attr;
	पूर्ण अन्यथा अणु
		ret = sysfs_create_group(&msipf_device->dev.kobj,
					 &msipf_old_attribute_group);
		अगर (ret)
			जाओ fail_create_attr;

		/* Disable स्वतःmatic brightness control by शेष because
		 * this module was probably loaded to करो brightness control in
		 * software. */

		अगर (स्वतः_brightness != 2)
			set_स्वतः_brightness(स्वतः_brightness);
	पूर्ण

	pr_info("driver " MSI_DRIVER_VERSION " successfully loaded\n");

	वापस 0;

fail_create_attr:
	sysfs_हटाओ_group(&msipf_device->dev.kobj, &msipf_attribute_group);
fail_create_group:
	अगर (quirks->load_scm_model) अणु
		i8042_हटाओ_filter(msi_laptop_i8042_filter);
		cancel_delayed_work_sync(&msi_rfसमाप्त_dwork);
		cancel_work_sync(&msi_rfसमाप्त_work);
		rfसमाप्त_cleanup();
	पूर्ण
fail_scm_model_init:
	platक्रमm_device_del(msipf_device);
fail_device_add:
	platक्रमm_device_put(msipf_device);
fail_platक्रमm_driver:
	platक्रमm_driver_unरेजिस्टर(&msipf_driver);
fail_backlight:
	backlight_device_unरेजिस्टर(msibl_device);

	वापस ret;
पूर्ण

अटल व्योम __निकास msi_cleanup(व्योम)
अणु
	अगर (quirks->load_scm_model) अणु
		i8042_हटाओ_filter(msi_laptop_i8042_filter);
		input_unरेजिस्टर_device(msi_laptop_input_dev);
		cancel_delayed_work_sync(&msi_rfसमाप्त_dwork);
		cancel_work_sync(&msi_rfसमाप्त_work);
		rfसमाप्त_cleanup();
	पूर्ण

	sysfs_हटाओ_group(&msipf_device->dev.kobj, &msipf_attribute_group);
	अगर (!quirks->old_ec_model && threeg_exists)
		device_हटाओ_file(&msipf_device->dev, &dev_attr_threeg);
	platक्रमm_device_unरेजिस्टर(msipf_device);
	platक्रमm_driver_unरेजिस्टर(&msipf_driver);
	backlight_device_unरेजिस्टर(msibl_device);

	अगर (quirks->old_ec_model) अणु
		/* Enable स्वतःmatic brightness control again */
		अगर (स्वतः_brightness != 2)
			set_स्वतः_brightness(1);
	पूर्ण

	pr_info("driver unloaded\n");
पूर्ण

module_init(msi_init);
module_निकास(msi_cleanup);

MODULE_AUTHOR("Lennart Poettering");
MODULE_DESCRIPTION("MSI Laptop Support");
MODULE_VERSION(MSI_DRIVER_VERSION);
MODULE_LICENSE("GPL");

MODULE_ALIAS("dmi:*:svnMICRO-STARINT'LCO.,LTD:pnMS-1013:pvr0131*:cvnMICRO-STARINT'LCO.,LTD:ct10:*");
MODULE_ALIAS("dmi:*:svnMicro-StarInternational:pnMS-1058:pvr0581:rvnMSI:rnMS-1058:*:ct10:*");
MODULE_ALIAS("dmi:*:svnMicro-StarInternational:pnMS-1412:*:rvnMSI:rnMS-1412:*:cvnMICRO-STARINT'LCO.,LTD:ct10:*");
MODULE_ALIAS("dmi:*:svnNOTEBOOK:pnSAM2000:pvr0131*:cvnMICRO-STARINT'LCO.,LTD:ct10:*");
MODULE_ALIAS("dmi:*:svnMICRO-STARINTERNATIONAL*:pnMS-N034:*");
MODULE_ALIAS("dmi:*:svnMICRO-STARINTERNATIONAL*:pnMS-N051:*");
MODULE_ALIAS("dmi:*:svnMICRO-STARINTERNATIONAL*:pnMS-N014:*");
MODULE_ALIAS("dmi:*:svnMicro-StarInternational*:pnCR620:*");
MODULE_ALIAS("dmi:*:svnMicro-StarInternational*:pnU270series:*");
MODULE_ALIAS("dmi:*:svnMICRO-STARINTERNATIONAL*:pnU90/U100:*");
