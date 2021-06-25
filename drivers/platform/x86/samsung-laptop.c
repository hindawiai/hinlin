<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Samsung Laptop driver
 *
 * Copyright (C) 2009,2011 Greg Kroah-Harपंचांगan (gregkh@suse.de)
 * Copyright (C) 2009,2011 Novell Inc.
 */
#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/delay.h>
#समावेश <linux/pci.h>
#समावेश <linux/backlight.h>
#समावेश <linux/leds.h>
#समावेश <linux/fb.h>
#समावेश <linux/dmi.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/rfसमाप्त.h>
#समावेश <linux/acpi.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/efi.h>
#समावेश <linux/suspend.h>
#समावेश <acpi/video.h>

/*
 * This driver is needed because a number of Samsung laptops करो not hook
 * their control settings through ACPI.  So we have to poke around in the
 * BIOS to करो things like brightness values, and "special" key controls.
 */

/*
 * We have 0 - 8 as valid brightness levels.  The specs say that level 0 should
 * be reserved by the BIOS (which really करोesn't make much sense), we tell
 * userspace that the value is 0 - 7 and then just tell the hardware 1 - 8
 */
#घोषणा MAX_BRIGHT	0x07


#घोषणा SABI_IFACE_MAIN			0x00
#घोषणा SABI_IFACE_SUB			0x02
#घोषणा SABI_IFACE_COMPLETE		0x04
#घोषणा SABI_IFACE_DATA			0x05

#घोषणा WL_STATUS_WLAN			0x0
#घोषणा WL_STATUS_BT			0x2

/* Structure get/set data using sabi */
काष्ठा sabi_data अणु
	जोड़ अणु
		काष्ठा अणु
			u32 d0;
			u32 d1;
			u16 d2;
			u8  d3;
		पूर्ण;
		u8 data[11];
	पूर्ण;
पूर्ण;

काष्ठा sabi_header_offsets अणु
	u8 port;
	u8 re_mem;
	u8 अगरace_func;
	u8 en_mem;
	u8 data_offset;
	u8 data_segment;
पूर्ण;

काष्ठा sabi_commands अणु
	/*
	 * Brightness is 0 - 8, as described above.
	 * Value 0 is क्रम the BIOS to use
	 */
	u16 get_brightness;
	u16 set_brightness;

	/*
	 * first byte:
	 * 0x00 - wireless is off
	 * 0x01 - wireless is on
	 * second byte:
	 * 0x02 - 3G is off
	 * 0x03 - 3G is on
	 * TODO, verअगरy 3G is correct, that करोesn't seem right...
	 */
	u16 get_wireless_button;
	u16 set_wireless_button;

	/* 0 is off, 1 is on */
	u16 get_backlight;
	u16 set_backlight;

	/*
	 * 0x80 or 0x00 - no action
	 * 0x81 - recovery key pressed
	 */
	u16 get_recovery_mode;
	u16 set_recovery_mode;

	/*
	 * on seclinux: 0 is low, 1 is high,
	 * on swsmi: 0 is normal, 1 is silent, 2 is turbo
	 */
	u16 get_perक्रमmance_level;
	u16 set_perक्रमmance_level;

	/* 0x80 is off, 0x81 is on */
	u16 get_battery_lअगरe_extender;
	u16 set_battery_lअगरe_extender;

	/* 0x80 is off, 0x81 is on */
	u16 get_usb_अक्षरge;
	u16 set_usb_अक्षरge;

	/* the first byte is क्रम bluetooth and the third one is क्रम wlan */
	u16 get_wireless_status;
	u16 set_wireless_status;

	/* 0x80 is off, 0x81 is on */
	u16 get_lid_handling;
	u16 set_lid_handling;

	/* 0x81 to पढ़ो, (0x82 | level << 8) to set, 0xaabb to enable */
	u16 kbd_backlight;

	/*
	 * Tell the BIOS that Linux is running on this machine.
	 * 81 is on, 80 is off
	 */
	u16 set_linux;
पूर्ण;

काष्ठा sabi_perक्रमmance_level अणु
	स्थिर अक्षर *name;
	u16 value;
पूर्ण;

काष्ठा sabi_config अणु
	पूर्णांक sabi_version;
	स्थिर अक्षर *test_string;
	u16 मुख्य_function;
	स्थिर काष्ठा sabi_header_offsets header_offsets;
	स्थिर काष्ठा sabi_commands commands;
	स्थिर काष्ठा sabi_perक्रमmance_level perक्रमmance_levels[4];
	u8 min_brightness;
	u8 max_brightness;
पूर्ण;

अटल स्थिर काष्ठा sabi_config sabi_configs[] = अणु
	अणु
		/* I करोn't know अगर it is really 2, but it it is
		 * less than 3 anyway */
		.sabi_version = 2,

		.test_string = "SECLINUX",

		.मुख्य_function = 0x4c49,

		.header_offsets = अणु
			.port = 0x00,
			.re_mem = 0x02,
			.अगरace_func = 0x03,
			.en_mem = 0x04,
			.data_offset = 0x05,
			.data_segment = 0x07,
		पूर्ण,

		.commands = अणु
			.get_brightness = 0x00,
			.set_brightness = 0x01,

			.get_wireless_button = 0x02,
			.set_wireless_button = 0x03,

			.get_backlight = 0x04,
			.set_backlight = 0x05,

			.get_recovery_mode = 0x06,
			.set_recovery_mode = 0x07,

			.get_perक्रमmance_level = 0x08,
			.set_perक्रमmance_level = 0x09,

			.get_battery_lअगरe_extender = 0xFFFF,
			.set_battery_lअगरe_extender = 0xFFFF,

			.get_usb_अक्षरge = 0xFFFF,
			.set_usb_अक्षरge = 0xFFFF,

			.get_wireless_status = 0xFFFF,
			.set_wireless_status = 0xFFFF,

			.get_lid_handling = 0xFFFF,
			.set_lid_handling = 0xFFFF,

			.kbd_backlight = 0xFFFF,

			.set_linux = 0x0a,
		पूर्ण,

		.perक्रमmance_levels = अणु
			अणु
				.name = "silent",
				.value = 0,
			पूर्ण,
			अणु
				.name = "normal",
				.value = 1,
			पूर्ण,
			अणु पूर्ण,
		पूर्ण,
		.min_brightness = 1,
		.max_brightness = 8,
	पूर्ण,
	अणु
		.sabi_version = 3,

		.test_string = "SwSmi@",

		.मुख्य_function = 0x5843,

		.header_offsets = अणु
			.port = 0x00,
			.re_mem = 0x04,
			.अगरace_func = 0x02,
			.en_mem = 0x03,
			.data_offset = 0x05,
			.data_segment = 0x07,
		पूर्ण,

		.commands = अणु
			.get_brightness = 0x10,
			.set_brightness = 0x11,

			.get_wireless_button = 0x12,
			.set_wireless_button = 0x13,

			.get_backlight = 0x2d,
			.set_backlight = 0x2e,

			.get_recovery_mode = 0xff,
			.set_recovery_mode = 0xff,

			.get_perक्रमmance_level = 0x31,
			.set_perक्रमmance_level = 0x32,

			.get_battery_lअगरe_extender = 0x65,
			.set_battery_lअगरe_extender = 0x66,

			.get_usb_अक्षरge = 0x67,
			.set_usb_अक्षरge = 0x68,

			.get_wireless_status = 0x69,
			.set_wireless_status = 0x6a,

			.get_lid_handling = 0x6d,
			.set_lid_handling = 0x6e,

			.kbd_backlight = 0x78,

			.set_linux = 0xff,
		पूर्ण,

		.perक्रमmance_levels = अणु
			अणु
				.name = "normal",
				.value = 0,
			पूर्ण,
			अणु
				.name = "silent",
				.value = 1,
			पूर्ण,
			अणु
				.name = "overclock",
				.value = 2,
			पूर्ण,
			अणु पूर्ण,
		पूर्ण,
		.min_brightness = 0,
		.max_brightness = 8,
	पूर्ण,
	अणु पूर्ण,
पूर्ण;

/*
 * samsung-laptop/    - debugfs root directory
 *   f0000_segment    - dump f0000 segment
 *   command          - current command
 *   data             - current data
 *   d0, d1, d2, d3   - data fields
 *   call             - call SABI using command and data
 *
 * This allow to call arbitrary sabi commands wihout
 * modअगरying the driver at all.
 * For example, setting the keyboard backlight brightness to 5
 *
 *  echo 0x78 > command
 *  echo 0x0582 > d0
 *  echo 0 > d1
 *  echo 0 > d2
 *  echo 0 > d3
 *  cat call
 */

काष्ठा samsung_laptop_debug अणु
	काष्ठा dentry *root;
	काष्ठा sabi_data data;
	u16 command;

	काष्ठा debugfs_blob_wrapper f0000_wrapper;
	काष्ठा debugfs_blob_wrapper data_wrapper;
	काष्ठा debugfs_blob_wrapper sdiag_wrapper;
पूर्ण;

काष्ठा samsung_laptop;

काष्ठा samsung_rfसमाप्त अणु
	काष्ठा samsung_laptop *samsung;
	काष्ठा rfसमाप्त *rfसमाप्त;
	क्रमागत rfसमाप्त_type type;
पूर्ण;

काष्ठा samsung_laptop अणु
	स्थिर काष्ठा sabi_config *config;

	व्योम __iomem *sabi;
	व्योम __iomem *sabi_अगरace;
	व्योम __iomem *f0000_segment;

	काष्ठा mutex sabi_mutex;

	काष्ठा platक्रमm_device *platक्रमm_device;
	काष्ठा backlight_device *backlight_device;

	काष्ठा samsung_rfसमाप्त wlan;
	काष्ठा samsung_rfसमाप्त bluetooth;

	काष्ठा led_classdev kbd_led;
	पूर्णांक kbd_led_wk;
	काष्ठा workqueue_काष्ठा *led_workqueue;
	काष्ठा work_काष्ठा kbd_led_work;

	काष्ठा samsung_laptop_debug debug;
	काष्ठा samsung_quirks *quirks;

	काष्ठा notअगरier_block pm_nb;

	bool handle_backlight;
	bool has_stepping_quirk;

	अक्षर sdiag[64];
पूर्ण;

काष्ठा samsung_quirks अणु
	bool broken_acpi_video;
	bool four_kbd_backlight_levels;
	bool enable_kbd_backlight;
	bool use_native_backlight;
	bool lid_handling;
पूर्ण;

अटल काष्ठा samsung_quirks samsung_unknown = अणुपूर्ण;

अटल काष्ठा samsung_quirks samsung_broken_acpi_video = अणु
	.broken_acpi_video = true,
पूर्ण;

अटल काष्ठा samsung_quirks samsung_use_native_backlight = अणु
	.use_native_backlight = true,
पूर्ण;

अटल काष्ठा samsung_quirks samsung_np740u3e = अणु
	.four_kbd_backlight_levels = true,
	.enable_kbd_backlight = true,
पूर्ण;

अटल काष्ठा samsung_quirks samsung_lid_handling = अणु
	.lid_handling = true,
पूर्ण;

अटल bool क्रमce;
module_param(क्रमce, bool, 0);
MODULE_PARM_DESC(क्रमce,
		"Disable the DMI check and forces the driver to be loaded");

अटल bool debug;
module_param(debug, bool, S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(debug, "Debug enabled or not");

अटल पूर्णांक sabi_command(काष्ठा samsung_laptop *samsung, u16 command,
			काष्ठा sabi_data *in,
			काष्ठा sabi_data *out)
अणु
	स्थिर काष्ठा sabi_config *config = samsung->config;
	पूर्णांक ret = 0;
	u16 port = पढ़ोw(samsung->sabi + config->header_offsets.port);
	u8 complete, अगरace_data;

	mutex_lock(&samsung->sabi_mutex);

	अगर (debug) अणु
		अगर (in)
			pr_info("SABI command:0x%04x "
				"data:{0x%08x, 0x%08x, 0x%04x, 0x%02x}",
				command, in->d0, in->d1, in->d2, in->d3);
		अन्यथा
			pr_info("SABI command:0x%04x", command);
	पूर्ण

	/* enable memory to be able to ग_लिखो to it */
	outb(पढ़ोb(samsung->sabi + config->header_offsets.en_mem), port);

	/* ग_लिखो out the command */
	ग_लिखोw(config->मुख्य_function, samsung->sabi_अगरace + SABI_IFACE_MAIN);
	ग_लिखोw(command, samsung->sabi_अगरace + SABI_IFACE_SUB);
	ग_लिखोb(0, samsung->sabi_अगरace + SABI_IFACE_COMPLETE);
	अगर (in) अणु
		ग_लिखोl(in->d0, samsung->sabi_अगरace + SABI_IFACE_DATA);
		ग_लिखोl(in->d1, samsung->sabi_अगरace + SABI_IFACE_DATA + 4);
		ग_लिखोw(in->d2, samsung->sabi_अगरace + SABI_IFACE_DATA + 8);
		ग_लिखोb(in->d3, samsung->sabi_अगरace + SABI_IFACE_DATA + 10);
	पूर्ण
	outb(पढ़ोb(samsung->sabi + config->header_offsets.अगरace_func), port);

	/* ग_लिखो protect memory to make it safe */
	outb(पढ़ोb(samsung->sabi + config->header_offsets.re_mem), port);

	/* see अगर the command actually succeeded */
	complete = पढ़ोb(samsung->sabi_अगरace + SABI_IFACE_COMPLETE);
	अगरace_data = पढ़ोb(samsung->sabi_अगरace + SABI_IFACE_DATA);

	/* अगरace_data = 0xFF happens when a command is not known
	 * so we only add a warning in debug mode since we will
	 * probably issue some unknown command at startup to find
	 * out which features are supported */
	अगर (complete != 0xaa || (अगरace_data == 0xff && debug))
		pr_warn("SABI command 0x%04x failed with"
			" completion flag 0x%02x and interface data 0x%02x",
			command, complete, अगरace_data);

	अगर (complete != 0xaa || अगरace_data == 0xff) अणु
		ret = -EINVAL;
		जाओ निकास;
	पूर्ण

	अगर (out) अणु
		out->d0 = पढ़ोl(samsung->sabi_अगरace + SABI_IFACE_DATA);
		out->d1 = पढ़ोl(samsung->sabi_अगरace + SABI_IFACE_DATA + 4);
		out->d2 = पढ़ोw(samsung->sabi_अगरace + SABI_IFACE_DATA + 2);
		out->d3 = पढ़ोb(samsung->sabi_अगरace + SABI_IFACE_DATA + 1);
	पूर्ण

	अगर (debug && out) अणु
		pr_info("SABI return data:{0x%08x, 0x%08x, 0x%04x, 0x%02x}",
			out->d0, out->d1, out->d2, out->d3);
	पूर्ण

निकास:
	mutex_unlock(&samsung->sabi_mutex);
	वापस ret;
पूर्ण

/* simple wrappers usable with most commands */
अटल पूर्णांक sabi_set_commandb(काष्ठा samsung_laptop *samsung,
			     u16 command, u8 data)
अणु
	काष्ठा sabi_data in = अणु अणु अणु .d0 = 0, .d1 = 0, .d2 = 0, .d3 = 0 पूर्ण पूर्ण पूर्ण;

	in.data[0] = data;
	वापस sabi_command(samsung, command, &in, शून्य);
पूर्ण

अटल पूर्णांक पढ़ो_brightness(काष्ठा samsung_laptop *samsung)
अणु
	स्थिर काष्ठा sabi_config *config = samsung->config;
	स्थिर काष्ठा sabi_commands *commands = &samsung->config->commands;
	काष्ठा sabi_data sretval;
	पूर्णांक user_brightness = 0;
	पूर्णांक retval;

	retval = sabi_command(samsung, commands->get_brightness,
			      शून्य, &sretval);
	अगर (retval)
		वापस retval;

	user_brightness = sretval.data[0];
	अगर (user_brightness > config->min_brightness)
		user_brightness -= config->min_brightness;
	अन्यथा
		user_brightness = 0;

	वापस user_brightness;
पूर्ण

अटल व्योम set_brightness(काष्ठा samsung_laptop *samsung, u8 user_brightness)
अणु
	स्थिर काष्ठा sabi_config *config = samsung->config;
	स्थिर काष्ठा sabi_commands *commands = &samsung->config->commands;
	u8 user_level = user_brightness + config->min_brightness;

	अगर (samsung->has_stepping_quirk && user_level != 0) अणु
		/*
		 * लघु circuit अगर the specअगरied level is what's alपढ़ोy set
		 * to prevent the screen from flickering needlessly
		 */
		अगर (user_brightness == पढ़ो_brightness(samsung))
			वापस;

		sabi_set_commandb(samsung, commands->set_brightness, 0);
	पूर्ण

	sabi_set_commandb(samsung, commands->set_brightness, user_level);
पूर्ण

अटल पूर्णांक get_brightness(काष्ठा backlight_device *bd)
अणु
	काष्ठा samsung_laptop *samsung = bl_get_data(bd);

	वापस पढ़ो_brightness(samsung);
पूर्ण

अटल व्योम check_क्रम_stepping_quirk(काष्ठा samsung_laptop *samsung)
अणु
	पूर्णांक initial_level;
	पूर्णांक check_level;
	पूर्णांक orig_level = पढ़ो_brightness(samsung);

	/*
	 * Some laptops exhibit the strange behaviour of stepping toward
	 * (rather than setting) the brightness except when changing to/from
	 * brightness level 0. This behaviour is checked क्रम here and worked
	 * around in set_brightness.
	 */

	अगर (orig_level == 0)
		set_brightness(samsung, 1);

	initial_level = पढ़ो_brightness(samsung);

	अगर (initial_level <= 2)
		check_level = initial_level + 2;
	अन्यथा
		check_level = initial_level - 2;

	samsung->has_stepping_quirk = false;
	set_brightness(samsung, check_level);

	अगर (पढ़ो_brightness(samsung) != check_level) अणु
		samsung->has_stepping_quirk = true;
		pr_info("enabled workaround for brightness stepping quirk\n");
	पूर्ण

	set_brightness(samsung, orig_level);
पूर्ण

अटल पूर्णांक update_status(काष्ठा backlight_device *bd)
अणु
	काष्ठा samsung_laptop *samsung = bl_get_data(bd);
	स्थिर काष्ठा sabi_commands *commands = &samsung->config->commands;

	set_brightness(samsung, bd->props.brightness);

	अगर (bd->props.घातer == FB_BLANK_UNBLANK)
		sabi_set_commandb(samsung, commands->set_backlight, 1);
	अन्यथा
		sabi_set_commandb(samsung, commands->set_backlight, 0);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा backlight_ops backlight_ops = अणु
	.get_brightness	= get_brightness,
	.update_status	= update_status,
पूर्ण;

अटल पूर्णांक seclinux_rfसमाप्त_set(व्योम *data, bool blocked)
अणु
	काष्ठा samsung_rfसमाप्त *srfसमाप्त = data;
	काष्ठा samsung_laptop *samsung = srfसमाप्त->samsung;
	स्थिर काष्ठा sabi_commands *commands = &samsung->config->commands;

	वापस sabi_set_commandb(samsung, commands->set_wireless_button,
				 !blocked);
पूर्ण

अटल स्थिर काष्ठा rfसमाप्त_ops seclinux_rfसमाप्त_ops = अणु
	.set_block = seclinux_rfसमाप्त_set,
पूर्ण;

अटल पूर्णांक swsmi_wireless_status(काष्ठा samsung_laptop *samsung,
				 काष्ठा sabi_data *data)
अणु
	स्थिर काष्ठा sabi_commands *commands = &samsung->config->commands;

	वापस sabi_command(samsung, commands->get_wireless_status,
			    शून्य, data);
पूर्ण

अटल पूर्णांक swsmi_rfसमाप्त_set(व्योम *priv, bool blocked)
अणु
	काष्ठा samsung_rfसमाप्त *srfसमाप्त = priv;
	काष्ठा samsung_laptop *samsung = srfसमाप्त->samsung;
	स्थिर काष्ठा sabi_commands *commands = &samsung->config->commands;
	काष्ठा sabi_data data;
	पूर्णांक ret, i;

	ret = swsmi_wireless_status(samsung, &data);
	अगर (ret)
		वापस ret;

	/* Don't set the state क्रम non-present devices */
	क्रम (i = 0; i < 4; i++)
		अगर (data.data[i] == 0x02)
			data.data[1] = 0;

	अगर (srfसमाप्त->type == RFKILL_TYPE_WLAN)
		data.data[WL_STATUS_WLAN] = !blocked;
	अन्यथा अगर (srfसमाप्त->type == RFKILL_TYPE_BLUETOOTH)
		data.data[WL_STATUS_BT] = !blocked;

	वापस sabi_command(samsung, commands->set_wireless_status,
			    &data, &data);
पूर्ण

अटल व्योम swsmi_rfसमाप्त_query(काष्ठा rfसमाप्त *rfसमाप्त, व्योम *priv)
अणु
	काष्ठा samsung_rfसमाप्त *srfसमाप्त = priv;
	काष्ठा samsung_laptop *samsung = srfसमाप्त->samsung;
	काष्ठा sabi_data data;
	पूर्णांक ret;

	ret = swsmi_wireless_status(samsung, &data);
	अगर (ret)
		वापस ;

	अगर (srfसमाप्त->type == RFKILL_TYPE_WLAN)
		ret = data.data[WL_STATUS_WLAN];
	अन्यथा अगर (srfसमाप्त->type == RFKILL_TYPE_BLUETOOTH)
		ret = data.data[WL_STATUS_BT];
	अन्यथा
		वापस ;

	rfसमाप्त_set_sw_state(rfसमाप्त, !ret);
पूर्ण

अटल स्थिर काष्ठा rfसमाप्त_ops swsmi_rfसमाप्त_ops = अणु
	.set_block = swsmi_rfसमाप्त_set,
	.query = swsmi_rfसमाप्त_query,
पूर्ण;

अटल sमाप_प्रकार get_perक्रमmance_level(काष्ठा device *dev,
				     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा samsung_laptop *samsung = dev_get_drvdata(dev);
	स्थिर काष्ठा sabi_config *config = samsung->config;
	स्थिर काष्ठा sabi_commands *commands = &config->commands;
	काष्ठा sabi_data sretval;
	पूर्णांक retval;
	पूर्णांक i;

	/* Read the state */
	retval = sabi_command(samsung, commands->get_perक्रमmance_level,
			      शून्य, &sretval);
	अगर (retval)
		वापस retval;

	/* The logic is backwards, yeah, lots of fun... */
	क्रम (i = 0; config->perक्रमmance_levels[i].name; ++i) अणु
		अगर (sretval.data[0] == config->perक्रमmance_levels[i].value)
			वापस प्र_लिखो(buf, "%s\n", config->perक्रमmance_levels[i].name);
	पूर्ण
	वापस प्र_लिखो(buf, "%s\n", "unknown");
पूर्ण

अटल sमाप_प्रकार set_perक्रमmance_level(काष्ठा device *dev,
				काष्ठा device_attribute *attr, स्थिर अक्षर *buf,
				माप_प्रकार count)
अणु
	काष्ठा samsung_laptop *samsung = dev_get_drvdata(dev);
	स्थिर काष्ठा sabi_config *config = samsung->config;
	स्थिर काष्ठा sabi_commands *commands = &config->commands;
	पूर्णांक i;

	अगर (count < 1)
		वापस count;

	क्रम (i = 0; config->perक्रमmance_levels[i].name; ++i) अणु
		स्थिर काष्ठा sabi_perक्रमmance_level *level =
			&config->perक्रमmance_levels[i];
		अगर (!strnहालcmp(level->name, buf, म_माप(level->name))) अणु
			sabi_set_commandb(samsung,
					  commands->set_perक्रमmance_level,
					  level->value);
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!config->perक्रमmance_levels[i].name)
		वापस -EINVAL;

	वापस count;
पूर्ण

अटल DEVICE_ATTR(perक्रमmance_level, S_IWUSR | S_IRUGO,
		   get_perक्रमmance_level, set_perक्रमmance_level);

अटल पूर्णांक पढ़ो_battery_lअगरe_extender(काष्ठा samsung_laptop *samsung)
अणु
	स्थिर काष्ठा sabi_commands *commands = &samsung->config->commands;
	काष्ठा sabi_data data;
	पूर्णांक retval;

	अगर (commands->get_battery_lअगरe_extender == 0xFFFF)
		वापस -ENODEV;

	स_रखो(&data, 0, माप(data));
	data.data[0] = 0x80;
	retval = sabi_command(samsung, commands->get_battery_lअगरe_extender,
			      &data, &data);

	अगर (retval)
		वापस retval;

	अगर (data.data[0] != 0 && data.data[0] != 1)
		वापस -ENODEV;

	वापस data.data[0];
पूर्ण

अटल पूर्णांक ग_लिखो_battery_lअगरe_extender(काष्ठा samsung_laptop *samsung,
				       पूर्णांक enabled)
अणु
	स्थिर काष्ठा sabi_commands *commands = &samsung->config->commands;
	काष्ठा sabi_data data;

	स_रखो(&data, 0, माप(data));
	data.data[0] = 0x80 | enabled;
	वापस sabi_command(samsung, commands->set_battery_lअगरe_extender,
			    &data, शून्य);
पूर्ण

अटल sमाप_प्रकार get_battery_lअगरe_extender(काष्ठा device *dev,
					 काष्ठा device_attribute *attr,
					 अक्षर *buf)
अणु
	काष्ठा samsung_laptop *samsung = dev_get_drvdata(dev);
	पूर्णांक ret;

	ret = पढ़ो_battery_lअगरe_extender(samsung);
	अगर (ret < 0)
		वापस ret;

	वापस प्र_लिखो(buf, "%d\n", ret);
पूर्ण

अटल sमाप_प्रकार set_battery_lअगरe_extender(काष्ठा device *dev,
					काष्ठा device_attribute *attr,
					स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा samsung_laptop *samsung = dev_get_drvdata(dev);
	पूर्णांक ret, value;

	अगर (!count || kstrtoपूर्णांक(buf, 0, &value) != 0)
		वापस -EINVAL;

	ret = ग_लिखो_battery_lअगरe_extender(samsung, !!value);
	अगर (ret < 0)
		वापस ret;

	वापस count;
पूर्ण

अटल DEVICE_ATTR(battery_lअगरe_extender, S_IWUSR | S_IRUGO,
		   get_battery_lअगरe_extender, set_battery_lअगरe_extender);

अटल पूर्णांक पढ़ो_usb_अक्षरge(काष्ठा samsung_laptop *samsung)
अणु
	स्थिर काष्ठा sabi_commands *commands = &samsung->config->commands;
	काष्ठा sabi_data data;
	पूर्णांक retval;

	अगर (commands->get_usb_अक्षरge == 0xFFFF)
		वापस -ENODEV;

	स_रखो(&data, 0, माप(data));
	data.data[0] = 0x80;
	retval = sabi_command(samsung, commands->get_usb_अक्षरge,
			      &data, &data);

	अगर (retval)
		वापस retval;

	अगर (data.data[0] != 0 && data.data[0] != 1)
		वापस -ENODEV;

	वापस data.data[0];
पूर्ण

अटल पूर्णांक ग_लिखो_usb_अक्षरge(काष्ठा samsung_laptop *samsung,
			    पूर्णांक enabled)
अणु
	स्थिर काष्ठा sabi_commands *commands = &samsung->config->commands;
	काष्ठा sabi_data data;

	स_रखो(&data, 0, माप(data));
	data.data[0] = 0x80 | enabled;
	वापस sabi_command(samsung, commands->set_usb_अक्षरge,
			    &data, शून्य);
पूर्ण

अटल sमाप_प्रकार get_usb_अक्षरge(काष्ठा device *dev,
			      काष्ठा device_attribute *attr,
			      अक्षर *buf)
अणु
	काष्ठा samsung_laptop *samsung = dev_get_drvdata(dev);
	पूर्णांक ret;

	ret = पढ़ो_usb_अक्षरge(samsung);
	अगर (ret < 0)
		वापस ret;

	वापस प्र_लिखो(buf, "%d\n", ret);
पूर्ण

अटल sमाप_प्रकार set_usb_अक्षरge(काष्ठा device *dev,
			      काष्ठा device_attribute *attr,
			      स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा samsung_laptop *samsung = dev_get_drvdata(dev);
	पूर्णांक ret, value;

	अगर (!count || kstrtoपूर्णांक(buf, 0, &value) != 0)
		वापस -EINVAL;

	ret = ग_लिखो_usb_अक्षरge(samsung, !!value);
	अगर (ret < 0)
		वापस ret;

	वापस count;
पूर्ण

अटल DEVICE_ATTR(usb_अक्षरge, S_IWUSR | S_IRUGO,
		   get_usb_अक्षरge, set_usb_अक्षरge);

अटल पूर्णांक पढ़ो_lid_handling(काष्ठा samsung_laptop *samsung)
अणु
	स्थिर काष्ठा sabi_commands *commands = &samsung->config->commands;
	काष्ठा sabi_data data;
	पूर्णांक retval;

	अगर (commands->get_lid_handling == 0xFFFF)
		वापस -ENODEV;

	स_रखो(&data, 0, माप(data));
	retval = sabi_command(samsung, commands->get_lid_handling,
			      &data, &data);

	अगर (retval)
		वापस retval;

	वापस data.data[0] & 0x1;
पूर्ण

अटल पूर्णांक ग_लिखो_lid_handling(काष्ठा samsung_laptop *samsung,
			      पूर्णांक enabled)
अणु
	स्थिर काष्ठा sabi_commands *commands = &samsung->config->commands;
	काष्ठा sabi_data data;

	स_रखो(&data, 0, माप(data));
	data.data[0] = 0x80 | enabled;
	वापस sabi_command(samsung, commands->set_lid_handling,
			    &data, शून्य);
पूर्ण

अटल sमाप_प्रकार get_lid_handling(काष्ठा device *dev,
				काष्ठा device_attribute *attr,
				अक्षर *buf)
अणु
	काष्ठा samsung_laptop *samsung = dev_get_drvdata(dev);
	पूर्णांक ret;

	ret = पढ़ो_lid_handling(samsung);
	अगर (ret < 0)
		वापस ret;

	वापस प्र_लिखो(buf, "%d\n", ret);
पूर्ण

अटल sमाप_प्रकार set_lid_handling(काष्ठा device *dev,
				काष्ठा device_attribute *attr,
				स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा samsung_laptop *samsung = dev_get_drvdata(dev);
	पूर्णांक ret, value;

	अगर (!count || kstrtoपूर्णांक(buf, 0, &value) != 0)
		वापस -EINVAL;

	ret = ग_लिखो_lid_handling(samsung, !!value);
	अगर (ret < 0)
		वापस ret;

	वापस count;
पूर्ण

अटल DEVICE_ATTR(lid_handling, S_IWUSR | S_IRUGO,
		   get_lid_handling, set_lid_handling);

अटल काष्ठा attribute *platक्रमm_attributes[] = अणु
	&dev_attr_perक्रमmance_level.attr,
	&dev_attr_battery_lअगरe_extender.attr,
	&dev_attr_usb_अक्षरge.attr,
	&dev_attr_lid_handling.attr,
	शून्य
पूर्ण;

अटल पूर्णांक find_signature(व्योम __iomem *memcheck, स्थिर अक्षर *testStr)
अणु
	पूर्णांक i = 0;
	पूर्णांक loca;

	क्रम (loca = 0; loca < 0xffff; loca++) अणु
		अक्षर temp = पढ़ोb(memcheck + loca);

		अगर (temp == testStr[i]) अणु
			अगर (i == म_माप(testStr)-1)
				अवरोध;
			++i;
		पूर्ण अन्यथा अणु
			i = 0;
		पूर्ण
	पूर्ण
	वापस loca;
पूर्ण

अटल व्योम samsung_rfसमाप्त_निकास(काष्ठा samsung_laptop *samsung)
अणु
	अगर (samsung->wlan.rfसमाप्त) अणु
		rfसमाप्त_unरेजिस्टर(samsung->wlan.rfसमाप्त);
		rfसमाप्त_destroy(samsung->wlan.rfसमाप्त);
		samsung->wlan.rfसमाप्त = शून्य;
	पूर्ण
	अगर (samsung->bluetooth.rfसमाप्त) अणु
		rfसमाप्त_unरेजिस्टर(samsung->bluetooth.rfसमाप्त);
		rfसमाप्त_destroy(samsung->bluetooth.rfसमाप्त);
		samsung->bluetooth.rfसमाप्त = शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक samsung_new_rfसमाप्त(काष्ठा samsung_laptop *samsung,
			      काष्ठा samsung_rfसमाप्त *arfसमाप्त,
			      स्थिर अक्षर *name, क्रमागत rfसमाप्त_type type,
			      स्थिर काष्ठा rfसमाप्त_ops *ops,
			      पूर्णांक blocked)
अणु
	काष्ठा rfसमाप्त **rfसमाप्त = &arfसमाप्त->rfसमाप्त;
	पूर्णांक ret;

	arfसमाप्त->type = type;
	arfसमाप्त->samsung = samsung;

	*rfसमाप्त = rfसमाप्त_alloc(name, &samsung->platक्रमm_device->dev,
			       type, ops, arfसमाप्त);

	अगर (!*rfसमाप्त)
		वापस -EINVAL;

	अगर (blocked != -1)
		rfसमाप्त_init_sw_state(*rfसमाप्त, blocked);

	ret = rfसमाप्त_रेजिस्टर(*rfसमाप्त);
	अगर (ret) अणु
		rfसमाप्त_destroy(*rfसमाप्त);
		*rfसमाप्त = शून्य;
		वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक __init samsung_rfसमाप्त_init_seclinux(काष्ठा samsung_laptop *samsung)
अणु
	वापस samsung_new_rfसमाप्त(samsung, &samsung->wlan, "samsung-wlan",
				  RFKILL_TYPE_WLAN, &seclinux_rfसमाप्त_ops, -1);
पूर्ण

अटल पूर्णांक __init samsung_rfसमाप्त_init_swsmi(काष्ठा samsung_laptop *samsung)
अणु
	काष्ठा sabi_data data;
	पूर्णांक ret;

	ret = swsmi_wireless_status(samsung, &data);
	अगर (ret) अणु
		/* Some swsmi laptops use the old seclinux way to control
		 * wireless devices */
		अगर (ret == -EINVAL)
			ret = samsung_rfसमाप्त_init_seclinux(samsung);
		वापस ret;
	पूर्ण

	/* 0x02 seems to mean that the device is no present/available */

	अगर (data.data[WL_STATUS_WLAN] != 0x02)
		ret = samsung_new_rfसमाप्त(samsung, &samsung->wlan,
					 "samsung-wlan",
					 RFKILL_TYPE_WLAN,
					 &swsmi_rfसमाप्त_ops,
					 !data.data[WL_STATUS_WLAN]);
	अगर (ret)
		जाओ निकास;

	अगर (data.data[WL_STATUS_BT] != 0x02)
		ret = samsung_new_rfसमाप्त(samsung, &samsung->bluetooth,
					 "samsung-bluetooth",
					 RFKILL_TYPE_BLUETOOTH,
					 &swsmi_rfसमाप्त_ops,
					 !data.data[WL_STATUS_BT]);
	अगर (ret)
		जाओ निकास;

निकास:
	अगर (ret)
		samsung_rfसमाप्त_निकास(samsung);

	वापस ret;
पूर्ण

अटल पूर्णांक __init samsung_rfसमाप्त_init(काष्ठा samsung_laptop *samsung)
अणु
	अगर (samsung->config->sabi_version == 2)
		वापस samsung_rfसमाप्त_init_seclinux(samsung);
	अगर (samsung->config->sabi_version == 3)
		वापस samsung_rfसमाप्त_init_swsmi(samsung);
	वापस 0;
पूर्ण

अटल व्योम samsung_lid_handling_निकास(काष्ठा samsung_laptop *samsung)
अणु
	अगर (samsung->quirks->lid_handling)
		ग_लिखो_lid_handling(samsung, 0);
पूर्ण

अटल पूर्णांक __init samsung_lid_handling_init(काष्ठा samsung_laptop *samsung)
अणु
	पूर्णांक retval = 0;

	अगर (samsung->quirks->lid_handling)
		retval = ग_लिखो_lid_handling(samsung, 1);

	वापस retval;
पूर्ण

अटल पूर्णांक kbd_backlight_enable(काष्ठा samsung_laptop *samsung)
अणु
	स्थिर काष्ठा sabi_commands *commands = &samsung->config->commands;
	काष्ठा sabi_data data;
	पूर्णांक retval;

	अगर (commands->kbd_backlight == 0xFFFF)
		वापस -ENODEV;

	स_रखो(&data, 0, माप(data));
	data.d0 = 0xaabb;
	retval = sabi_command(samsung, commands->kbd_backlight,
			      &data, &data);

	अगर (retval)
		वापस retval;

	अगर (data.d0 != 0xccdd)
		वापस -ENODEV;
	वापस 0;
पूर्ण

अटल पूर्णांक kbd_backlight_पढ़ो(काष्ठा samsung_laptop *samsung)
अणु
	स्थिर काष्ठा sabi_commands *commands = &samsung->config->commands;
	काष्ठा sabi_data data;
	पूर्णांक retval;

	स_रखो(&data, 0, माप(data));
	data.data[0] = 0x81;
	retval = sabi_command(samsung, commands->kbd_backlight,
			      &data, &data);

	अगर (retval)
		वापस retval;

	वापस data.data[0];
पूर्ण

अटल पूर्णांक kbd_backlight_ग_लिखो(काष्ठा samsung_laptop *samsung, पूर्णांक brightness)
अणु
	स्थिर काष्ठा sabi_commands *commands = &samsung->config->commands;
	काष्ठा sabi_data data;

	स_रखो(&data, 0, माप(data));
	data.d0 = 0x82 | ((brightness & 0xFF) << 8);
	वापस sabi_command(samsung, commands->kbd_backlight,
			    &data, शून्य);
पूर्ण

अटल व्योम kbd_led_update(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा samsung_laptop *samsung;

	samsung = container_of(work, काष्ठा samsung_laptop, kbd_led_work);
	kbd_backlight_ग_लिखो(samsung, samsung->kbd_led_wk);
पूर्ण

अटल व्योम kbd_led_set(काष्ठा led_classdev *led_cdev,
			क्रमागत led_brightness value)
अणु
	काष्ठा samsung_laptop *samsung;

	samsung = container_of(led_cdev, काष्ठा samsung_laptop, kbd_led);

	अगर (value > samsung->kbd_led.max_brightness)
		value = samsung->kbd_led.max_brightness;
	अन्यथा अगर (value < 0)
		value = 0;

	samsung->kbd_led_wk = value;
	queue_work(samsung->led_workqueue, &samsung->kbd_led_work);
पूर्ण

अटल क्रमागत led_brightness kbd_led_get(काष्ठा led_classdev *led_cdev)
अणु
	काष्ठा samsung_laptop *samsung;

	samsung = container_of(led_cdev, काष्ठा samsung_laptop, kbd_led);
	वापस kbd_backlight_पढ़ो(samsung);
पूर्ण

अटल व्योम samsung_leds_निकास(काष्ठा samsung_laptop *samsung)
अणु
	led_classdev_unरेजिस्टर(&samsung->kbd_led);
	अगर (samsung->led_workqueue)
		destroy_workqueue(samsung->led_workqueue);
पूर्ण

अटल पूर्णांक __init samsung_leds_init(काष्ठा samsung_laptop *samsung)
अणु
	पूर्णांक ret = 0;

	samsung->led_workqueue = create_singlethपढ़ो_workqueue("led_workqueue");
	अगर (!samsung->led_workqueue)
		वापस -ENOMEM;

	अगर (kbd_backlight_enable(samsung) >= 0) अणु
		INIT_WORK(&samsung->kbd_led_work, kbd_led_update);

		samsung->kbd_led.name = "samsung::kbd_backlight";
		samsung->kbd_led.brightness_set = kbd_led_set;
		samsung->kbd_led.brightness_get = kbd_led_get;
		samsung->kbd_led.max_brightness = 8;
		अगर (samsung->quirks->four_kbd_backlight_levels)
			samsung->kbd_led.max_brightness = 4;

		ret = led_classdev_रेजिस्टर(&samsung->platक्रमm_device->dev,
					   &samsung->kbd_led);
	पूर्ण

	अगर (ret)
		samsung_leds_निकास(samsung);

	वापस ret;
पूर्ण

अटल व्योम samsung_backlight_निकास(काष्ठा samsung_laptop *samsung)
अणु
	अगर (samsung->backlight_device) अणु
		backlight_device_unरेजिस्टर(samsung->backlight_device);
		samsung->backlight_device = शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक __init samsung_backlight_init(काष्ठा samsung_laptop *samsung)
अणु
	काष्ठा backlight_device *bd;
	काष्ठा backlight_properties props;

	अगर (!samsung->handle_backlight)
		वापस 0;

	स_रखो(&props, 0, माप(काष्ठा backlight_properties));
	props.type = BACKLIGHT_PLATFORM;
	props.max_brightness = samsung->config->max_brightness -
		samsung->config->min_brightness;

	bd = backlight_device_रेजिस्टर("samsung",
				       &samsung->platक्रमm_device->dev,
				       samsung, &backlight_ops,
				       &props);
	अगर (IS_ERR(bd))
		वापस PTR_ERR(bd);

	samsung->backlight_device = bd;
	samsung->backlight_device->props.brightness = पढ़ो_brightness(samsung);
	samsung->backlight_device->props.घातer = FB_BLANK_UNBLANK;
	backlight_update_status(samsung->backlight_device);

	वापस 0;
पूर्ण

अटल umode_t samsung_sysfs_is_visible(काष्ठा kobject *kobj,
					काष्ठा attribute *attr, पूर्णांक idx)
अणु
	काष्ठा device *dev = container_of(kobj, काष्ठा device, kobj);
	काष्ठा samsung_laptop *samsung = dev_get_drvdata(dev);
	bool ok = true;

	अगर (attr == &dev_attr_perक्रमmance_level.attr)
		ok = !!samsung->config->perक्रमmance_levels[0].name;
	अगर (attr == &dev_attr_battery_lअगरe_extender.attr)
		ok = !!(पढ़ो_battery_lअगरe_extender(samsung) >= 0);
	अगर (attr == &dev_attr_usb_अक्षरge.attr)
		ok = !!(पढ़ो_usb_अक्षरge(samsung) >= 0);
	अगर (attr == &dev_attr_lid_handling.attr)
		ok = !!(पढ़ो_lid_handling(samsung) >= 0);

	वापस ok ? attr->mode : 0;
पूर्ण

अटल स्थिर काष्ठा attribute_group platक्रमm_attribute_group = अणु
	.is_visible = samsung_sysfs_is_visible,
	.attrs = platक्रमm_attributes
पूर्ण;

अटल व्योम samsung_sysfs_निकास(काष्ठा samsung_laptop *samsung)
अणु
	काष्ठा platक्रमm_device *device = samsung->platक्रमm_device;

	sysfs_हटाओ_group(&device->dev.kobj, &platक्रमm_attribute_group);
पूर्ण

अटल पूर्णांक __init samsung_sysfs_init(काष्ठा samsung_laptop *samsung)
अणु
	काष्ठा platक्रमm_device *device = samsung->platक्रमm_device;

	वापस sysfs_create_group(&device->dev.kobj, &platक्रमm_attribute_group);

पूर्ण

अटल पूर्णांक samsung_laptop_call_show(काष्ठा seq_file *m, व्योम *data)
अणु
	काष्ठा samsung_laptop *samsung = m->निजी;
	काष्ठा sabi_data *sdata = &samsung->debug.data;
	पूर्णांक ret;

	seq_म_लिखो(m, "SABI 0x%04x {0x%08x, 0x%08x, 0x%04x, 0x%02x}\n",
		   samsung->debug.command,
		   sdata->d0, sdata->d1, sdata->d2, sdata->d3);

	ret = sabi_command(samsung, samsung->debug.command, sdata, sdata);

	अगर (ret) अणु
		seq_म_लिखो(m, "SABI command 0x%04x failed\n",
			   samsung->debug.command);
		वापस ret;
	पूर्ण

	seq_म_लिखो(m, "SABI {0x%08x, 0x%08x, 0x%04x, 0x%02x}\n",
		   sdata->d0, sdata->d1, sdata->d2, sdata->d3);
	वापस 0;
पूर्ण
DEFINE_SHOW_ATTRIBUTE(samsung_laptop_call);

अटल व्योम samsung_debugfs_निकास(काष्ठा samsung_laptop *samsung)
अणु
	debugfs_हटाओ_recursive(samsung->debug.root);
पूर्ण

अटल व्योम samsung_debugfs_init(काष्ठा samsung_laptop *samsung)
अणु
	काष्ठा dentry *root;

	root = debugfs_create_dir("samsung-laptop", शून्य);
	samsung->debug.root = root;

	samsung->debug.f0000_wrapper.data = samsung->f0000_segment;
	samsung->debug.f0000_wrapper.size = 0xffff;

	samsung->debug.data_wrapper.data = &samsung->debug.data;
	samsung->debug.data_wrapper.size = माप(samsung->debug.data);

	samsung->debug.sdiag_wrapper.data = samsung->sdiag;
	samsung->debug.sdiag_wrapper.size = म_माप(samsung->sdiag);

	debugfs_create_u16("command", S_IRUGO | S_IWUSR, root,
			   &samsung->debug.command);
	debugfs_create_u32("d0", S_IRUGO | S_IWUSR, root,
			   &samsung->debug.data.d0);
	debugfs_create_u32("d1", S_IRUGO | S_IWUSR, root,
			   &samsung->debug.data.d1);
	debugfs_create_u16("d2", S_IRUGO | S_IWUSR, root,
			   &samsung->debug.data.d2);
	debugfs_create_u8("d3", S_IRUGO | S_IWUSR, root,
			  &samsung->debug.data.d3);
	debugfs_create_blob("data", S_IRUGO | S_IWUSR, root,
			    &samsung->debug.data_wrapper);
	debugfs_create_blob("f0000_segment", S_IRUSR | S_IWUSR, root,
			    &samsung->debug.f0000_wrapper);
	debugfs_create_file("call", S_IFREG | S_IRUGO, root, samsung,
			    &samsung_laptop_call_fops);
	debugfs_create_blob("sdiag", S_IRUGO | S_IWUSR, root,
			    &samsung->debug.sdiag_wrapper);
पूर्ण

अटल व्योम samsung_sabi_निकास(काष्ठा samsung_laptop *samsung)
अणु
	स्थिर काष्ठा sabi_config *config = samsung->config;

	/* Turn off "Linux" mode in the BIOS */
	अगर (config && config->commands.set_linux != 0xff)
		sabi_set_commandb(samsung, config->commands.set_linux, 0x80);

	अगर (samsung->sabi_अगरace) अणु
		iounmap(samsung->sabi_अगरace);
		samsung->sabi_अगरace = शून्य;
	पूर्ण
	अगर (samsung->f0000_segment) अणु
		iounmap(samsung->f0000_segment);
		samsung->f0000_segment = शून्य;
	पूर्ण

	samsung->config = शून्य;
पूर्ण

अटल __init व्योम samsung_sabi_infos(काष्ठा samsung_laptop *samsung, पूर्णांक loca,
				      अचिन्हित पूर्णांक अगरaceP)
अणु
	स्थिर काष्ठा sabi_config *config = samsung->config;

	prपूर्णांकk(KERN_DEBUG "This computer supports SABI==%x\n",
	       loca + 0xf0000 - 6);

	prपूर्णांकk(KERN_DEBUG "SABI header:\n");
	prपूर्णांकk(KERN_DEBUG " SMI Port Number = 0x%04x\n",
	       पढ़ोw(samsung->sabi + config->header_offsets.port));
	prपूर्णांकk(KERN_DEBUG " SMI Interface Function = 0x%02x\n",
	       पढ़ोb(samsung->sabi + config->header_offsets.अगरace_func));
	prपूर्णांकk(KERN_DEBUG " SMI enable memory buffer = 0x%02x\n",
	       पढ़ोb(samsung->sabi + config->header_offsets.en_mem));
	prपूर्णांकk(KERN_DEBUG " SMI restore memory buffer = 0x%02x\n",
	       पढ़ोb(samsung->sabi + config->header_offsets.re_mem));
	prपूर्णांकk(KERN_DEBUG " SABI data offset = 0x%04x\n",
	       पढ़ोw(samsung->sabi + config->header_offsets.data_offset));
	prपूर्णांकk(KERN_DEBUG " SABI data segment = 0x%04x\n",
	       पढ़ोw(samsung->sabi + config->header_offsets.data_segment));

	prपूर्णांकk(KERN_DEBUG " SABI pointer = 0x%08x\n", अगरaceP);
पूर्ण

अटल व्योम __init samsung_sabi_diag(काष्ठा samsung_laptop *samsung)
अणु
	पूर्णांक loca = find_signature(samsung->f0000_segment, "SDiaG@");
	पूर्णांक i;

	अगर (loca == 0xffff)
		वापस ;

	/* Example:
	 * Ident: @SDiaG@686XX-N90X3A/966-SEC-07HL-S90X3A
	 *
	 * Product name: 90X3A
	 * BIOS Version: 07HL
	 */
	loca += 1;
	क्रम (i = 0; loca < 0xffff && i < माप(samsung->sdiag) - 1; loca++) अणु
		अक्षर temp = पढ़ोb(samsung->f0000_segment + loca);

		अगर (है_अक्षर_अंक(temp) || temp == '/' || temp == '-')
			samsung->sdiag[i++] = temp;
		अन्यथा
			अवरोध ;
	पूर्ण

	अगर (debug && samsung->sdiag[0])
		pr_info("sdiag: %s", samsung->sdiag);
पूर्ण

अटल पूर्णांक __init samsung_sabi_init(काष्ठा samsung_laptop *samsung)
अणु
	स्थिर काष्ठा sabi_config *config = शून्य;
	स्थिर काष्ठा sabi_commands *commands;
	अचिन्हित पूर्णांक अगरaceP;
	पूर्णांक loca = 0xffff;
	पूर्णांक ret = 0;
	पूर्णांक i;

	samsung->f0000_segment = ioremap(0xf0000, 0xffff);
	अगर (!samsung->f0000_segment) अणु
		अगर (debug || क्रमce)
			pr_err("Can't map the segment at 0xf0000\n");
		ret = -EINVAL;
		जाओ निकास;
	पूर्ण

	samsung_sabi_diag(samsung);

	/* Try to find one of the signatures in memory to find the header */
	क्रम (i = 0; sabi_configs[i].test_string != शून्य; ++i) अणु
		samsung->config = &sabi_configs[i];
		loca = find_signature(samsung->f0000_segment,
				      samsung->config->test_string);
		अगर (loca != 0xffff)
			अवरोध;
	पूर्ण

	अगर (loca == 0xffff) अणु
		अगर (debug || क्रमce)
			pr_err("This computer does not support SABI\n");
		ret = -ENODEV;
		जाओ निकास;
	पूर्ण

	config = samsung->config;
	commands = &config->commands;

	/* poपूर्णांक to the SMI port Number */
	loca += 1;
	samsung->sabi = (samsung->f0000_segment + loca);

	/* Get a poपूर्णांकer to the SABI Interface */
	अगरaceP = (पढ़ोw(samsung->sabi + config->header_offsets.data_segment) & 0x0ffff) << 4;
	अगरaceP += पढ़ोw(samsung->sabi + config->header_offsets.data_offset) & 0x0ffff;

	अगर (debug)
		samsung_sabi_infos(samsung, loca, अगरaceP);

	samsung->sabi_अगरace = ioremap(अगरaceP, 16);
	अगर (!samsung->sabi_अगरace) अणु
		pr_err("Can't remap %x\n", अगरaceP);
		ret = -EINVAL;
		जाओ निकास;
	पूर्ण

	/* Turn on "Linux" mode in the BIOS */
	अगर (commands->set_linux != 0xff) अणु
		पूर्णांक retval = sabi_set_commandb(samsung,
					       commands->set_linux, 0x81);
		अगर (retval) अणु
			pr_warn("Linux mode was not set!\n");
			ret = -ENODEV;
			जाओ निकास;
		पूर्ण
	पूर्ण

	/* Check क्रम stepping quirk */
	अगर (samsung->handle_backlight)
		check_क्रम_stepping_quirk(samsung);

	pr_info("detected SABI interface: %s\n",
		samsung->config->test_string);

निकास:
	अगर (ret)
		samsung_sabi_निकास(samsung);

	वापस ret;
पूर्ण

अटल व्योम samsung_platक्रमm_निकास(काष्ठा samsung_laptop *samsung)
अणु
	अगर (samsung->platक्रमm_device) अणु
		platक्रमm_device_unरेजिस्टर(samsung->platक्रमm_device);
		samsung->platक्रमm_device = शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक samsung_pm_notअगरication(काष्ठा notअगरier_block *nb,
				   अचिन्हित दीर्घ val, व्योम *ptr)
अणु
	काष्ठा samsung_laptop *samsung;

	samsung = container_of(nb, काष्ठा samsung_laptop, pm_nb);
	अगर (val == PM_POST_HIBERNATION &&
	    samsung->quirks->enable_kbd_backlight)
		kbd_backlight_enable(samsung);

	अगर (val == PM_POST_HIBERNATION && samsung->quirks->lid_handling)
		ग_लिखो_lid_handling(samsung, 1);

	वापस 0;
पूर्ण

अटल पूर्णांक __init samsung_platक्रमm_init(काष्ठा samsung_laptop *samsung)
अणु
	काष्ठा platक्रमm_device *pdev;

	pdev = platक्रमm_device_रेजिस्टर_simple("samsung", -1, शून्य, 0);
	अगर (IS_ERR(pdev))
		वापस PTR_ERR(pdev);

	samsung->platक्रमm_device = pdev;
	platक्रमm_set_drvdata(samsung->platक्रमm_device, samsung);
	वापस 0;
पूर्ण

अटल काष्ठा samsung_quirks *quirks;

अटल पूर्णांक __init samsung_dmi_matched(स्थिर काष्ठा dmi_प्रणाली_id *d)
अणु
	quirks = d->driver_data;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dmi_प्रणाली_id samsung_dmi_table[] __initस्थिर = अणु
	अणु
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR,
					"SAMSUNG ELECTRONICS CO., LTD."),
			DMI_MATCH(DMI_CHASSIS_TYPE, "8"), /* Portable */
		पूर्ण,
	पूर्ण,
	अणु
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR,
					"SAMSUNG ELECTRONICS CO., LTD."),
			DMI_MATCH(DMI_CHASSIS_TYPE, "9"), /* Laptop */
		पूर्ण,
	पूर्ण,
	अणु
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR,
					"SAMSUNG ELECTRONICS CO., LTD."),
			DMI_MATCH(DMI_CHASSIS_TYPE, "10"), /* Notebook */
		पूर्ण,
	पूर्ण,
	अणु
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR,
					"SAMSUNG ELECTRONICS CO., LTD."),
			DMI_MATCH(DMI_CHASSIS_TYPE, "14"), /* Sub-Notebook */
		पूर्ण,
	पूर्ण,
	/* DMI ids क्रम laptops with bad Chassis Type */
	अणु
	  .ident = "R40/R41",
	  .matches = अणु
		DMI_MATCH(DMI_SYS_VENDOR, "SAMSUNG ELECTRONICS CO., LTD."),
		DMI_MATCH(DMI_PRODUCT_NAME, "R40/R41"),
		DMI_MATCH(DMI_BOARD_NAME, "R40/R41"),
		पूर्ण,
	पूर्ण,
	/* Specअगरic DMI ids क्रम laptop with quirks */
	अणु
	 .callback = samsung_dmi_matched,
	 .ident = "N150P",
	 .matches = अणु
		DMI_MATCH(DMI_SYS_VENDOR, "SAMSUNG ELECTRONICS CO., LTD."),
		DMI_MATCH(DMI_PRODUCT_NAME, "N150P"),
		DMI_MATCH(DMI_BOARD_NAME, "N150P"),
		पूर्ण,
	 .driver_data = &samsung_use_native_backlight,
	पूर्ण,
	अणु
	 .callback = samsung_dmi_matched,
	 .ident = "N145P/N250P/N260P",
	 .matches = अणु
		DMI_MATCH(DMI_SYS_VENDOR, "SAMSUNG ELECTRONICS CO., LTD."),
		DMI_MATCH(DMI_PRODUCT_NAME, "N145P/N250P/N260P"),
		DMI_MATCH(DMI_BOARD_NAME, "N145P/N250P/N260P"),
		पूर्ण,
	 .driver_data = &samsung_use_native_backlight,
	पूर्ण,
	अणु
	 .callback = samsung_dmi_matched,
	 .ident = "N150/N210/N220",
	 .matches = अणु
		DMI_MATCH(DMI_SYS_VENDOR, "SAMSUNG ELECTRONICS CO., LTD."),
		DMI_MATCH(DMI_PRODUCT_NAME, "N150/N210/N220"),
		DMI_MATCH(DMI_BOARD_NAME, "N150/N210/N220"),
		पूर्ण,
	 .driver_data = &samsung_broken_acpi_video,
	पूर्ण,
	अणु
	 .callback = samsung_dmi_matched,
	 .ident = "NF110/NF210/NF310",
	 .matches = अणु
		DMI_MATCH(DMI_SYS_VENDOR, "SAMSUNG ELECTRONICS CO., LTD."),
		DMI_MATCH(DMI_PRODUCT_NAME, "NF110/NF210/NF310"),
		DMI_MATCH(DMI_BOARD_NAME, "NF110/NF210/NF310"),
		पूर्ण,
	 .driver_data = &samsung_broken_acpi_video,
	पूर्ण,
	अणु
	 .callback = samsung_dmi_matched,
	 .ident = "X360",
	 .matches = अणु
		DMI_MATCH(DMI_SYS_VENDOR, "SAMSUNG ELECTRONICS CO., LTD."),
		DMI_MATCH(DMI_PRODUCT_NAME, "X360"),
		DMI_MATCH(DMI_BOARD_NAME, "X360"),
		पूर्ण,
	 .driver_data = &samsung_broken_acpi_video,
	पूर्ण,
	अणु
	 .callback = samsung_dmi_matched,
	 .ident = "N250P",
	 .matches = अणु
		DMI_MATCH(DMI_SYS_VENDOR, "SAMSUNG ELECTRONICS CO., LTD."),
		DMI_MATCH(DMI_PRODUCT_NAME, "N250P"),
		DMI_MATCH(DMI_BOARD_NAME, "N250P"),
		पूर्ण,
	 .driver_data = &samsung_use_native_backlight,
	पूर्ण,
	अणु
	 .callback = samsung_dmi_matched,
	 .ident = "NC210",
	 .matches = अणु
		DMI_MATCH(DMI_SYS_VENDOR, "SAMSUNG ELECTRONICS CO., LTD."),
		DMI_MATCH(DMI_PRODUCT_NAME, "NC210/NC110"),
		DMI_MATCH(DMI_BOARD_NAME, "NC210/NC110"),
		पूर्ण,
	 .driver_data = &samsung_broken_acpi_video,
	पूर्ण,
	अणु
	 .callback = samsung_dmi_matched,
	 .ident = "730U3E/740U3E",
	 .matches = अणु
		DMI_MATCH(DMI_SYS_VENDOR, "SAMSUNG ELECTRONICS CO., LTD."),
		DMI_MATCH(DMI_PRODUCT_NAME, "730U3E/740U3E"),
		पूर्ण,
	 .driver_data = &samsung_np740u3e,
	पूर्ण,
	अणु
	 .callback = samsung_dmi_matched,
	 .ident = "300V3Z/300V4Z/300V5Z",
	 .matches = अणु
		DMI_MATCH(DMI_SYS_VENDOR, "SAMSUNG ELECTRONICS CO., LTD."),
		DMI_MATCH(DMI_PRODUCT_NAME, "300V3Z/300V4Z/300V5Z"),
		पूर्ण,
	 .driver_data = &samsung_lid_handling,
	पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(dmi, samsung_dmi_table);

अटल काष्ठा platक्रमm_device *samsung_platक्रमm_device;

अटल पूर्णांक __init samsung_init(व्योम)
अणु
	काष्ठा samsung_laptop *samsung;
	पूर्णांक ret;

	अगर (efi_enabled(EFI_BOOT))
		वापस -ENODEV;

	quirks = &samsung_unknown;
	अगर (!क्रमce && !dmi_check_प्रणाली(samsung_dmi_table))
		वापस -ENODEV;

	samsung = kzalloc(माप(*samsung), GFP_KERNEL);
	अगर (!samsung)
		वापस -ENOMEM;

	mutex_init(&samsung->sabi_mutex);
	samsung->handle_backlight = true;
	samsung->quirks = quirks;

#अगर_घोषित CONFIG_ACPI
	अगर (samsung->quirks->broken_acpi_video)
		acpi_video_set_dmi_backlight_type(acpi_backlight_venकरोr);
	अगर (samsung->quirks->use_native_backlight)
		acpi_video_set_dmi_backlight_type(acpi_backlight_native);

	अगर (acpi_video_get_backlight_type() != acpi_backlight_venकरोr)
		samsung->handle_backlight = false;
#पूर्ण_अगर

	ret = samsung_platक्रमm_init(samsung);
	अगर (ret)
		जाओ error_platक्रमm;

	ret = samsung_sabi_init(samsung);
	अगर (ret)
		जाओ error_sabi;

	ret = samsung_sysfs_init(samsung);
	अगर (ret)
		जाओ error_sysfs;

	ret = samsung_backlight_init(samsung);
	अगर (ret)
		जाओ error_backlight;

	ret = samsung_rfसमाप्त_init(samsung);
	अगर (ret)
		जाओ error_rfसमाप्त;

	ret = samsung_leds_init(samsung);
	अगर (ret)
		जाओ error_leds;

	ret = samsung_lid_handling_init(samsung);
	अगर (ret)
		जाओ error_lid_handling;

	samsung_debugfs_init(samsung);

	samsung->pm_nb.notअगरier_call = samsung_pm_notअगरication;
	रेजिस्टर_pm_notअगरier(&samsung->pm_nb);

	samsung_platक्रमm_device = samsung->platक्रमm_device;
	वापस ret;

error_lid_handling:
	samsung_leds_निकास(samsung);
error_leds:
	samsung_rfसमाप्त_निकास(samsung);
error_rfसमाप्त:
	samsung_backlight_निकास(samsung);
error_backlight:
	samsung_sysfs_निकास(samsung);
error_sysfs:
	samsung_sabi_निकास(samsung);
error_sabi:
	samsung_platक्रमm_निकास(samsung);
error_platक्रमm:
	kमुक्त(samsung);
	वापस ret;
पूर्ण

अटल व्योम __निकास samsung_निकास(व्योम)
अणु
	काष्ठा samsung_laptop *samsung;

	samsung = platक्रमm_get_drvdata(samsung_platक्रमm_device);
	unरेजिस्टर_pm_notअगरier(&samsung->pm_nb);

	samsung_debugfs_निकास(samsung);
	samsung_lid_handling_निकास(samsung);
	samsung_leds_निकास(samsung);
	samsung_rfसमाप्त_निकास(samsung);
	samsung_backlight_निकास(samsung);
	samsung_sysfs_निकास(samsung);
	samsung_sabi_निकास(samsung);
	samsung_platक्रमm_निकास(samsung);

	kमुक्त(samsung);
	samsung_platक्रमm_device = शून्य;
पूर्ण

module_init(samsung_init);
module_निकास(samsung_निकास);

MODULE_AUTHOR("Greg Kroah-Hartman <gregkh@suse.de>");
MODULE_DESCRIPTION("Samsung Backlight driver");
MODULE_LICENSE("GPL");
