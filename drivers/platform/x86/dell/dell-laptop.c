<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  Driver क्रम Dell laptop extras
 *
 *  Copyright (c) Red Hat <mjg@redhat.com>
 *  Copyright (c) 2014 Gabriele Mazzotta <gabriele.mzt@gmail.com>
 *  Copyright (c) 2014 Pali Rohथँr <pali@kernel.org>
 *
 *  Based on करोcumentation in the libsmbios package:
 *  Copyright (C) 2005-2014 Dell Inc.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/backlight.h>
#समावेश <linux/err.h>
#समावेश <linux/dmi.h>
#समावेश <linux/पन.स>
#समावेश <linux/rfसमाप्त.h>
#समावेश <linux/घातer_supply.h>
#समावेश <linux/acpi.h>
#समावेश <linux/mm.h>
#समावेश <linux/i8042.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/seq_file.h>
#समावेश <acpi/video.h>
#समावेश "dell-rbtn.h"
#समावेश "dell-smbios.h"

काष्ठा quirk_entry अणु
	bool touchpad_led;
	bool kbd_led_not_present;
	bool kbd_led_levels_off_1;
	bool kbd_missing_ac_tag;

	bool needs_kbd_समयouts;
	/*
	 * Ordered list of समयouts expressed in seconds.
	 * The list must end with -1
	 */
	पूर्णांक kbd_समयouts[];
पूर्ण;

अटल काष्ठा quirk_entry *quirks;

अटल काष्ठा quirk_entry quirk_dell_vostro_v130 = अणु
	.touchpad_led = true,
पूर्ण;

अटल पूर्णांक __init dmi_matched(स्थिर काष्ठा dmi_प्रणाली_id *dmi)
अणु
	quirks = dmi->driver_data;
	वापस 1;
पूर्ण

/*
 * These values come from Winकरोws utility provided by Dell. If any other value
 * is used then BIOS silently set समयout to 0 without any error message.
 */
अटल काष्ठा quirk_entry quirk_dell_xps13_9333 = अणु
	.needs_kbd_समयouts = true,
	.kbd_समयouts = अणु 0, 5, 15, 60, 5 * 60, 15 * 60, -1 पूर्ण,
पूर्ण;

अटल काष्ठा quirk_entry quirk_dell_xps13_9370 = अणु
	.kbd_missing_ac_tag = true,
पूर्ण;

अटल काष्ठा quirk_entry quirk_dell_latitude_e6410 = अणु
	.kbd_led_levels_off_1 = true,
पूर्ण;

अटल काष्ठा quirk_entry quirk_dell_inspiron_1012 = अणु
	.kbd_led_not_present = true,
पूर्ण;

अटल काष्ठा platक्रमm_driver platक्रमm_driver = अणु
	.driver = अणु
		.name = "dell-laptop",
	पूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_device *platक्रमm_device;
अटल काष्ठा backlight_device *dell_backlight_device;
अटल काष्ठा rfसमाप्त *wअगरi_rfसमाप्त;
अटल काष्ठा rfसमाप्त *bluetooth_rfसमाप्त;
अटल काष्ठा rfसमाप्त *wwan_rfसमाप्त;
अटल bool क्रमce_rfसमाप्त;

module_param(क्रमce_rfसमाप्त, bool, 0444);
MODULE_PARM_DESC(क्रमce_rfसमाप्त, "enable rfkill on non whitelisted models");

अटल स्थिर काष्ठा dmi_प्रणाली_id dell_device_table[] __initस्थिर = अणु
	अणु
		.ident = "Dell laptop",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Dell Inc."),
			DMI_MATCH(DMI_CHASSIS_TYPE, "8"),
		पूर्ण,
	पूर्ण,
	अणु
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Dell Inc."),
			DMI_MATCH(DMI_CHASSIS_TYPE, "9"), /*Laptop*/
		पूर्ण,
	पूर्ण,
	अणु
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Dell Inc."),
			DMI_MATCH(DMI_CHASSIS_TYPE, "10"), /*Notebook*/
		पूर्ण,
	पूर्ण,
	अणु
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Dell Inc."),
			DMI_MATCH(DMI_CHASSIS_TYPE, "30"), /*Tablet*/
		पूर्ण,
	पूर्ण,
	अणु
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Dell Inc."),
			DMI_MATCH(DMI_CHASSIS_TYPE, "31"), /*Convertible*/
		पूर्ण,
	पूर्ण,
	अणु
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Dell Inc."),
			DMI_MATCH(DMI_CHASSIS_TYPE, "32"), /*Detachable*/
		पूर्ण,
	पूर्ण,
	अणु
		.ident = "Dell Computer Corporation",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Dell Computer Corporation"),
			DMI_MATCH(DMI_CHASSIS_TYPE, "8"),
		पूर्ण,
	पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(dmi, dell_device_table);

अटल स्थिर काष्ठा dmi_प्रणाली_id dell_quirks[] __initस्थिर = अणु
	अणु
		.callback = dmi_matched,
		.ident = "Dell Vostro V130",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Dell Inc."),
			DMI_MATCH(DMI_PRODUCT_NAME, "Vostro V130"),
		पूर्ण,
		.driver_data = &quirk_dell_vostro_v130,
	पूर्ण,
	अणु
		.callback = dmi_matched,
		.ident = "Dell Vostro V131",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Dell Inc."),
			DMI_MATCH(DMI_PRODUCT_NAME, "Vostro V131"),
		पूर्ण,
		.driver_data = &quirk_dell_vostro_v130,
	पूर्ण,
	अणु
		.callback = dmi_matched,
		.ident = "Dell Vostro 3350",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Dell Inc."),
			DMI_MATCH(DMI_PRODUCT_NAME, "Vostro 3350"),
		पूर्ण,
		.driver_data = &quirk_dell_vostro_v130,
	पूर्ण,
	अणु
		.callback = dmi_matched,
		.ident = "Dell Vostro 3555",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Dell Inc."),
			DMI_MATCH(DMI_PRODUCT_NAME, "Vostro 3555"),
		पूर्ण,
		.driver_data = &quirk_dell_vostro_v130,
	पूर्ण,
	अणु
		.callback = dmi_matched,
		.ident = "Dell Inspiron N311z",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Dell Inc."),
			DMI_MATCH(DMI_PRODUCT_NAME, "Inspiron N311z"),
		पूर्ण,
		.driver_data = &quirk_dell_vostro_v130,
	पूर्ण,
	अणु
		.callback = dmi_matched,
		.ident = "Dell Inspiron M5110",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Dell Inc."),
			DMI_MATCH(DMI_PRODUCT_NAME, "Inspiron M5110"),
		पूर्ण,
		.driver_data = &quirk_dell_vostro_v130,
	पूर्ण,
	अणु
		.callback = dmi_matched,
		.ident = "Dell Vostro 3360",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Dell Inc."),
			DMI_MATCH(DMI_PRODUCT_NAME, "Vostro 3360"),
		पूर्ण,
		.driver_data = &quirk_dell_vostro_v130,
	पूर्ण,
	अणु
		.callback = dmi_matched,
		.ident = "Dell Vostro 3460",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Dell Inc."),
			DMI_MATCH(DMI_PRODUCT_NAME, "Vostro 3460"),
		पूर्ण,
		.driver_data = &quirk_dell_vostro_v130,
	पूर्ण,
	अणु
		.callback = dmi_matched,
		.ident = "Dell Vostro 3560",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Dell Inc."),
			DMI_MATCH(DMI_PRODUCT_NAME, "Vostro 3560"),
		पूर्ण,
		.driver_data = &quirk_dell_vostro_v130,
	पूर्ण,
	अणु
		.callback = dmi_matched,
		.ident = "Dell Vostro 3450",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Dell Inc."),
			DMI_MATCH(DMI_PRODUCT_NAME, "Dell System Vostro 3450"),
		पूर्ण,
		.driver_data = &quirk_dell_vostro_v130,
	पूर्ण,
	अणु
		.callback = dmi_matched,
		.ident = "Dell Inspiron 5420",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Dell Inc."),
			DMI_MATCH(DMI_PRODUCT_NAME, "Inspiron 5420"),
		पूर्ण,
		.driver_data = &quirk_dell_vostro_v130,
	पूर्ण,
	अणु
		.callback = dmi_matched,
		.ident = "Dell Inspiron 5520",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Dell Inc."),
			DMI_MATCH(DMI_PRODUCT_NAME, "Inspiron 5520"),
		पूर्ण,
		.driver_data = &quirk_dell_vostro_v130,
	पूर्ण,
	अणु
		.callback = dmi_matched,
		.ident = "Dell Inspiron 5720",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Dell Inc."),
			DMI_MATCH(DMI_PRODUCT_NAME, "Inspiron 5720"),
		पूर्ण,
		.driver_data = &quirk_dell_vostro_v130,
	पूर्ण,
	अणु
		.callback = dmi_matched,
		.ident = "Dell Inspiron 7420",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Dell Inc."),
			DMI_MATCH(DMI_PRODUCT_NAME, "Inspiron 7420"),
		पूर्ण,
		.driver_data = &quirk_dell_vostro_v130,
	पूर्ण,
	अणु
		.callback = dmi_matched,
		.ident = "Dell Inspiron 7520",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Dell Inc."),
			DMI_MATCH(DMI_PRODUCT_NAME, "Inspiron 7520"),
		पूर्ण,
		.driver_data = &quirk_dell_vostro_v130,
	पूर्ण,
	अणु
		.callback = dmi_matched,
		.ident = "Dell Inspiron 7720",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Dell Inc."),
			DMI_MATCH(DMI_PRODUCT_NAME, "Inspiron 7720"),
		पूर्ण,
		.driver_data = &quirk_dell_vostro_v130,
	पूर्ण,
	अणु
		.callback = dmi_matched,
		.ident = "Dell XPS13 9333",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Dell Inc."),
			DMI_MATCH(DMI_PRODUCT_NAME, "XPS13 9333"),
		पूर्ण,
		.driver_data = &quirk_dell_xps13_9333,
	पूर्ण,
	अणु
		.callback = dmi_matched,
		.ident = "Dell XPS 13 9370",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Dell Inc."),
			DMI_MATCH(DMI_PRODUCT_NAME, "XPS 13 9370"),
		पूर्ण,
		.driver_data = &quirk_dell_xps13_9370,
	पूर्ण,
	अणु
		.callback = dmi_matched,
		.ident = "Dell Latitude E6410",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Dell Inc."),
			DMI_MATCH(DMI_PRODUCT_NAME, "Latitude E6410"),
		पूर्ण,
		.driver_data = &quirk_dell_latitude_e6410,
	पूर्ण,
	अणु
		.callback = dmi_matched,
		.ident = "Dell Inspiron 1012",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Dell Inc."),
			DMI_MATCH(DMI_PRODUCT_NAME, "Inspiron 1012"),
		पूर्ण,
		.driver_data = &quirk_dell_inspiron_1012,
	पूर्ण,
	अणु
		.callback = dmi_matched,
		.ident = "Dell Inspiron 1018",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Dell Inc."),
			DMI_MATCH(DMI_PRODUCT_NAME, "Inspiron 1018"),
		पूर्ण,
		.driver_data = &quirk_dell_inspiron_1012,
	पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल व्योम dell_fill_request(काष्ठा calling_पूर्णांकerface_buffer *buffer,
			       u32 arg0, u32 arg1, u32 arg2, u32 arg3)
अणु
	स_रखो(buffer, 0, माप(काष्ठा calling_पूर्णांकerface_buffer));
	buffer->input[0] = arg0;
	buffer->input[1] = arg1;
	buffer->input[2] = arg2;
	buffer->input[3] = arg3;
पूर्ण

अटल पूर्णांक dell_send_request(काष्ठा calling_पूर्णांकerface_buffer *buffer,
			     u16 class, u16 select)
अणु
	पूर्णांक ret;

	buffer->cmd_class = class;
	buffer->cmd_select = select;
	ret = dell_smbios_call(buffer);
	अगर (ret != 0)
		वापस ret;
	वापस dell_smbios_error(buffer->output[0]);
पूर्ण

/*
 * Derived from inक्रमmation in smbios-wireless-ctl:
 *
 * cbSelect 17, Value 11
 *
 * Return Wireless Info
 * cbArg1, byte0 = 0x00
 *
 *     cbRes1 Standard वापस codes (0, -1, -2)
 *     cbRes2 Info bit flags:
 *
 *     0 Hardware चयन supported (1)
 *     1 WiFi locator supported (1)
 *     2 WLAN supported (1)
 *     3 Bluetooth (BT) supported (1)
 *     4 WWAN supported (1)
 *     5 Wireless KBD supported (1)
 *     6 Uw b supported (1)
 *     7 WiGig supported (1)
 *     8 WLAN installed (1)
 *     9 BT installed (1)
 *     10 WWAN installed (1)
 *     11 Uw b installed (1)
 *     12 WiGig installed (1)
 *     13-15 Reserved (0)
 *     16 Hardware (HW) चयन is On (1)
 *     17 WLAN disabled (1)
 *     18 BT disabled (1)
 *     19 WWAN disabled (1)
 *     20 Uw b disabled (1)
 *     21 WiGig disabled (1)
 *     20-31 Reserved (0)
 *
 *     cbRes3 NVRAM size in bytes
 *     cbRes4, byte 0 NVRAM क्रमmat version number
 *
 *
 * Set QuickSet Radio Disable Flag
 *     cbArg1, byte0 = 0x01
 *     cbArg1, byte1
 *     Radio ID     value:
 *     0        Radio Status
 *     1        WLAN ID
 *     2        BT ID
 *     3        WWAN ID
 *     4        UWB ID
 *     5        WIGIG ID
 *     cbArg1, byte2    Flag bits:
 *             0 QuickSet disables radio (1)
 *             1-7 Reserved (0)
 *
 *     cbRes1    Standard वापस codes (0, -1, -2)
 *     cbRes2    QuickSet (QS) radio disable bit map:
 *     0 QS disables WLAN
 *     1 QS disables BT
 *     2 QS disables WWAN
 *     3 QS disables UWB
 *     4 QS disables WIGIG
 *     5-31 Reserved (0)
 *
 * Wireless Switch Configuration
 *     cbArg1, byte0 = 0x02
 *
 *     cbArg1, byte1
 *     Subcommand:
 *     0 Get config
 *     1 Set config
 *     2 Set WiFi locator enable/disable
 *     cbArg1,byte2
 *     Switch settings (अगर byte 1==1):
 *     0 WLAN sw itch control (1)
 *     1 BT sw itch control (1)
 *     2 WWAN sw itch control (1)
 *     3 UWB sw itch control (1)
 *     4 WiGig sw itch control (1)
 *     5-7 Reserved (0)
 *    cbArg1, byte2 Enable bits (अगर byte 1==2):
 *     0 Enable WiFi locator (1)
 *
 *    cbRes1     Standard वापस codes (0, -1, -2)
 *    cbRes2 QuickSet radio disable bit map:
 *     0 WLAN controlled by sw itch (1)
 *     1 BT controlled by sw itch (1)
 *     2 WWAN controlled by sw itch (1)
 *     3 UWB controlled by sw itch (1)
 *     4 WiGig controlled by sw itch (1)
 *     5-6 Reserved (0)
 *     7 Wireless sw itch config locked (1)
 *     8 WiFi locator enabled (1)
 *     9-14 Reserved (0)
 *     15 WiFi locator setting locked (1)
 *     16-31 Reserved (0)
 *
 * Read Local Config Data (LCD)
 *     cbArg1, byte0 = 0x10
 *     cbArg1, byte1 NVRAM index low byte
 *     cbArg1, byte2 NVRAM index high byte
 *     cbRes1 Standard वापस codes (0, -1, -2)
 *     cbRes2 4 bytes पढ़ो from LCD[index]
 *     cbRes3 4 bytes पढ़ो from LCD[index+4]
 *     cbRes4 4 bytes पढ़ो from LCD[index+8]
 *
 * Write Local Config Data (LCD)
 *     cbArg1, byte0 = 0x11
 *     cbArg1, byte1 NVRAM index low byte
 *     cbArg1, byte2 NVRAM index high byte
 *     cbArg2 4 bytes to w rite at LCD[index]
 *     cbArg3 4 bytes to w rite at LCD[index+4]
 *     cbArg4 4 bytes to w rite at LCD[index+8]
 *     cbRes1 Standard वापस codes (0, -1, -2)
 *
 * Populate Local Config Data from NVRAM
 *     cbArg1, byte0 = 0x12
 *     cbRes1 Standard वापस codes (0, -1, -2)
 *
 * Commit Local Config Data to NVRAM
 *     cbArg1, byte0 = 0x13
 *     cbRes1 Standard वापस codes (0, -1, -2)
 */

अटल पूर्णांक dell_rfसमाप्त_set(व्योम *data, bool blocked)
अणु
	पूर्णांक disable = blocked ? 1 : 0;
	अचिन्हित दीर्घ radio = (अचिन्हित दीर्घ)data;
	पूर्णांक hwचयन_bit = (अचिन्हित दीर्घ)data - 1;
	काष्ठा calling_पूर्णांकerface_buffer buffer;
	पूर्णांक hwचयन;
	पूर्णांक status;
	पूर्णांक ret;

	dell_fill_request(&buffer, 0, 0, 0, 0);
	ret = dell_send_request(&buffer, CLASS_INFO, SELECT_RFKILL);
	अगर (ret)
		वापस ret;
	status = buffer.output[1];

	dell_fill_request(&buffer, 0x2, 0, 0, 0);
	ret = dell_send_request(&buffer, CLASS_INFO, SELECT_RFKILL);
	अगर (ret)
		वापस ret;
	hwचयन = buffer.output[1];

	/* If the hardware चयन controls this radio, and the hardware
	   चयन is disabled, always disable the radio */
	अगर (ret == 0 && (hwचयन & BIT(hwचयन_bit)) &&
	    (status & BIT(0)) && !(status & BIT(16)))
		disable = 1;

	dell_fill_request(&buffer, 1 | (radio<<8) | (disable << 16), 0, 0, 0);
	ret = dell_send_request(&buffer, CLASS_INFO, SELECT_RFKILL);
	वापस ret;
पूर्ण

अटल व्योम dell_rfसमाप्त_update_sw_state(काष्ठा rfसमाप्त *rfसमाप्त, पूर्णांक radio,
					पूर्णांक status)
अणु
	अगर (status & BIT(0)) अणु
		/* Has hw-चयन, sync sw_state to BIOS */
		काष्ठा calling_पूर्णांकerface_buffer buffer;
		पूर्णांक block = rfसमाप्त_blocked(rfसमाप्त);
		dell_fill_request(&buffer,
				   1 | (radio << 8) | (block << 16), 0, 0, 0);
		dell_send_request(&buffer, CLASS_INFO, SELECT_RFKILL);
	पूर्ण अन्यथा अणु
		/* No hw-चयन, sync BIOS state to sw_state */
		rfसमाप्त_set_sw_state(rfसमाप्त, !!(status & BIT(radio + 16)));
	पूर्ण
पूर्ण

अटल व्योम dell_rfसमाप्त_update_hw_state(काष्ठा rfसमाप्त *rfसमाप्त, पूर्णांक radio,
					पूर्णांक status, पूर्णांक hwचयन)
अणु
	अगर (hwचयन & (BIT(radio - 1)))
		rfसमाप्त_set_hw_state(rfसमाप्त, !(status & BIT(16)));
पूर्ण

अटल व्योम dell_rfसमाप्त_query(काष्ठा rfसमाप्त *rfसमाप्त, व्योम *data)
अणु
	पूर्णांक radio = ((अचिन्हित दीर्घ)data & 0xF);
	काष्ठा calling_पूर्णांकerface_buffer buffer;
	पूर्णांक hwचयन;
	पूर्णांक status;
	पूर्णांक ret;

	dell_fill_request(&buffer, 0, 0, 0, 0);
	ret = dell_send_request(&buffer, CLASS_INFO, SELECT_RFKILL);
	status = buffer.output[1];

	अगर (ret != 0 || !(status & BIT(0))) अणु
		वापस;
	पूर्ण

	dell_fill_request(&buffer, 0x2, 0, 0, 0);
	ret = dell_send_request(&buffer, CLASS_INFO, SELECT_RFKILL);
	hwचयन = buffer.output[1];

	अगर (ret != 0)
		वापस;

	dell_rfसमाप्त_update_hw_state(rfसमाप्त, radio, status, hwचयन);
पूर्ण

अटल स्थिर काष्ठा rfसमाप्त_ops dell_rfसमाप्त_ops = अणु
	.set_block = dell_rfसमाप्त_set,
	.query = dell_rfसमाप्त_query,
पूर्ण;

अटल काष्ठा dentry *dell_laptop_dir;

अटल पूर्णांक dell_debugfs_show(काष्ठा seq_file *s, व्योम *data)
अणु
	काष्ठा calling_पूर्णांकerface_buffer buffer;
	पूर्णांक hwचयन_state;
	पूर्णांक hwचयन_ret;
	पूर्णांक status;
	पूर्णांक ret;

	dell_fill_request(&buffer, 0, 0, 0, 0);
	ret = dell_send_request(&buffer, CLASS_INFO, SELECT_RFKILL);
	अगर (ret)
		वापस ret;
	status = buffer.output[1];

	dell_fill_request(&buffer, 0x2, 0, 0, 0);
	hwचयन_ret = dell_send_request(&buffer, CLASS_INFO, SELECT_RFKILL);
	अगर (hwचयन_ret)
		वापस hwचयन_ret;
	hwचयन_state = buffer.output[1];

	seq_म_लिखो(s, "return:\t%d\n", ret);
	seq_म_लिखो(s, "status:\t0x%X\n", status);
	seq_म_लिखो(s, "Bit 0 : Hardware switch supported:   %lu\n",
		   status & BIT(0));
	seq_म_लिखो(s, "Bit 1 : Wifi locator supported:      %lu\n",
		  (status & BIT(1)) >> 1);
	seq_म_लिखो(s, "Bit 2 : Wifi is supported:           %lu\n",
		  (status & BIT(2)) >> 2);
	seq_म_लिखो(s, "Bit 3 : Bluetooth is supported:      %lu\n",
		  (status & BIT(3)) >> 3);
	seq_म_लिखो(s, "Bit 4 : WWAN is supported:           %lu\n",
		  (status & BIT(4)) >> 4);
	seq_म_लिखो(s, "Bit 5 : Wireless keyboard supported: %lu\n",
		  (status & BIT(5)) >> 5);
	seq_म_लिखो(s, "Bit 6 : UWB supported:               %lu\n",
		  (status & BIT(6)) >> 6);
	seq_म_लिखो(s, "Bit 7 : WiGig supported:             %lu\n",
		  (status & BIT(7)) >> 7);
	seq_म_लिखो(s, "Bit 8 : Wifi is installed:           %lu\n",
		  (status & BIT(8)) >> 8);
	seq_म_लिखो(s, "Bit 9 : Bluetooth is installed:      %lu\n",
		  (status & BIT(9)) >> 9);
	seq_म_लिखो(s, "Bit 10: WWAN is installed:           %lu\n",
		  (status & BIT(10)) >> 10);
	seq_म_लिखो(s, "Bit 11: UWB installed:               %lu\n",
		  (status & BIT(11)) >> 11);
	seq_म_लिखो(s, "Bit 12: WiGig installed:             %lu\n",
		  (status & BIT(12)) >> 12);

	seq_म_लिखो(s, "Bit 16: Hardware switch is on:       %lu\n",
		  (status & BIT(16)) >> 16);
	seq_म_लिखो(s, "Bit 17: Wifi is blocked:             %lu\n",
		  (status & BIT(17)) >> 17);
	seq_म_लिखो(s, "Bit 18: Bluetooth is blocked:        %lu\n",
		  (status & BIT(18)) >> 18);
	seq_म_लिखो(s, "Bit 19: WWAN is blocked:             %lu\n",
		  (status & BIT(19)) >> 19);
	seq_म_लिखो(s, "Bit 20: UWB is blocked:              %lu\n",
		  (status & BIT(20)) >> 20);
	seq_म_लिखो(s, "Bit 21: WiGig is blocked:            %lu\n",
		  (status & BIT(21)) >> 21);

	seq_म_लिखो(s, "\nhwswitch_return:\t%d\n", hwचयन_ret);
	seq_म_लिखो(s, "hwswitch_state:\t0x%X\n", hwचयन_state);
	seq_म_लिखो(s, "Bit 0 : Wifi controlled by switch:      %lu\n",
		   hwचयन_state & BIT(0));
	seq_म_लिखो(s, "Bit 1 : Bluetooth controlled by switch: %lu\n",
		   (hwचयन_state & BIT(1)) >> 1);
	seq_म_लिखो(s, "Bit 2 : WWAN controlled by switch:      %lu\n",
		   (hwचयन_state & BIT(2)) >> 2);
	seq_म_लिखो(s, "Bit 3 : UWB controlled by switch:       %lu\n",
		   (hwचयन_state & BIT(3)) >> 3);
	seq_म_लिखो(s, "Bit 4 : WiGig controlled by switch:     %lu\n",
		   (hwचयन_state & BIT(4)) >> 4);
	seq_म_लिखो(s, "Bit 7 : Wireless switch config locked:  %lu\n",
		   (hwचयन_state & BIT(7)) >> 7);
	seq_म_लिखो(s, "Bit 8 : Wifi locator enabled:           %lu\n",
		   (hwचयन_state & BIT(8)) >> 8);
	seq_म_लिखो(s, "Bit 15: Wifi locator setting locked:    %lu\n",
		   (hwचयन_state & BIT(15)) >> 15);

	वापस 0;
पूर्ण
DEFINE_SHOW_ATTRIBUTE(dell_debugfs);

अटल व्योम dell_update_rfसमाप्त(काष्ठा work_काष्ठा *ignored)
अणु
	काष्ठा calling_पूर्णांकerface_buffer buffer;
	पूर्णांक hwचयन = 0;
	पूर्णांक status;
	पूर्णांक ret;

	dell_fill_request(&buffer, 0, 0, 0, 0);
	ret = dell_send_request(&buffer, CLASS_INFO, SELECT_RFKILL);
	status = buffer.output[1];

	अगर (ret != 0)
		वापस;

	dell_fill_request(&buffer, 0x2, 0, 0, 0);
	ret = dell_send_request(&buffer, CLASS_INFO, SELECT_RFKILL);

	अगर (ret == 0 && (status & BIT(0)))
		hwचयन = buffer.output[1];

	अगर (wअगरi_rfसमाप्त) अणु
		dell_rfसमाप्त_update_hw_state(wअगरi_rfसमाप्त, 1, status, hwचयन);
		dell_rfसमाप्त_update_sw_state(wअगरi_rfसमाप्त, 1, status);
	पूर्ण
	अगर (bluetooth_rfसमाप्त) अणु
		dell_rfसमाप्त_update_hw_state(bluetooth_rfसमाप्त, 2, status,
					    hwचयन);
		dell_rfसमाप्त_update_sw_state(bluetooth_rfसमाप्त, 2, status);
	पूर्ण
	अगर (wwan_rfसमाप्त) अणु
		dell_rfसमाप्त_update_hw_state(wwan_rfसमाप्त, 3, status, hwचयन);
		dell_rfसमाप्त_update_sw_state(wwan_rfसमाप्त, 3, status);
	पूर्ण
पूर्ण
अटल DECLARE_DELAYED_WORK(dell_rfसमाप्त_work, dell_update_rfसमाप्त);

अटल bool dell_laptop_i8042_filter(अचिन्हित अक्षर data, अचिन्हित अक्षर str,
			      काष्ठा serio *port)
अणु
	अटल bool extended;

	अगर (str & I8042_STR_AUXDATA)
		वापस false;

	अगर (unlikely(data == 0xe0)) अणु
		extended = true;
		वापस false;
	पूर्ण अन्यथा अगर (unlikely(extended)) अणु
		चयन (data) अणु
		हाल 0x8:
			schedule_delayed_work(&dell_rfसमाप्त_work,
					      round_jअगरfies_relative(HZ / 4));
			अवरोध;
		पूर्ण
		extended = false;
	पूर्ण

	वापस false;
पूर्ण

अटल पूर्णांक (*dell_rbtn_notअगरier_रेजिस्टर_func)(काष्ठा notअगरier_block *);
अटल पूर्णांक (*dell_rbtn_notअगरier_unरेजिस्टर_func)(काष्ठा notअगरier_block *);

अटल पूर्णांक dell_laptop_rbtn_notअगरier_call(काष्ठा notअगरier_block *nb,
					  अचिन्हित दीर्घ action, व्योम *data)
अणु
	schedule_delayed_work(&dell_rfसमाप्त_work, 0);
	वापस NOTIFY_OK;
पूर्ण

अटल काष्ठा notअगरier_block dell_laptop_rbtn_notअगरier = अणु
	.notअगरier_call = dell_laptop_rbtn_notअगरier_call,
पूर्ण;

अटल पूर्णांक __init dell_setup_rfसमाप्त(व्योम)
अणु
	काष्ठा calling_पूर्णांकerface_buffer buffer;
	पूर्णांक status, ret, whitelisted;
	स्थिर अक्षर *product;

	/*
	 * rfसमाप्त support causes trouble on various models, mostly Inspirons.
	 * So we whitelist certain series, and करोn't support rfसमाप्त on others.
	 */
	whitelisted = 0;
	product = dmi_get_प्रणाली_info(DMI_PRODUCT_NAME);
	अगर (product &&  (म_भेदन(product, "Latitude", 8) == 0 ||
			 म_भेदन(product, "Precision", 9) == 0))
		whitelisted = 1;
	अगर (!क्रमce_rfसमाप्त && !whitelisted)
		वापस 0;

	dell_fill_request(&buffer, 0, 0, 0, 0);
	ret = dell_send_request(&buffer, CLASS_INFO, SELECT_RFKILL);
	status = buffer.output[1];

	/* dell wireless info smbios call is not supported */
	अगर (ret != 0)
		वापस 0;

	/* rfसमाप्त is only tested on laptops with a hwचयन */
	अगर (!(status & BIT(0)) && !क्रमce_rfसमाप्त)
		वापस 0;

	अगर ((status & (1<<2|1<<8)) == (1<<2|1<<8)) अणु
		wअगरi_rfसमाप्त = rfसमाप्त_alloc("dell-wifi", &platक्रमm_device->dev,
					   RFKILL_TYPE_WLAN,
					   &dell_rfसमाप्त_ops, (व्योम *) 1);
		अगर (!wअगरi_rfसमाप्त) अणु
			ret = -ENOMEM;
			जाओ err_wअगरi;
		पूर्ण
		ret = rfसमाप्त_रेजिस्टर(wअगरi_rfसमाप्त);
		अगर (ret)
			जाओ err_wअगरi;
	पूर्ण

	अगर ((status & (1<<3|1<<9)) == (1<<3|1<<9)) अणु
		bluetooth_rfसमाप्त = rfसमाप्त_alloc("dell-bluetooth",
						&platक्रमm_device->dev,
						RFKILL_TYPE_BLUETOOTH,
						&dell_rfसमाप्त_ops, (व्योम *) 2);
		अगर (!bluetooth_rfसमाप्त) अणु
			ret = -ENOMEM;
			जाओ err_bluetooth;
		पूर्ण
		ret = rfसमाप्त_रेजिस्टर(bluetooth_rfसमाप्त);
		अगर (ret)
			जाओ err_bluetooth;
	पूर्ण

	अगर ((status & (1<<4|1<<10)) == (1<<4|1<<10)) अणु
		wwan_rfसमाप्त = rfसमाप्त_alloc("dell-wwan",
					   &platक्रमm_device->dev,
					   RFKILL_TYPE_WWAN,
					   &dell_rfसमाप्त_ops, (व्योम *) 3);
		अगर (!wwan_rfसमाप्त) अणु
			ret = -ENOMEM;
			जाओ err_wwan;
		पूर्ण
		ret = rfसमाप्त_रेजिस्टर(wwan_rfसमाप्त);
		अगर (ret)
			जाओ err_wwan;
	पूर्ण

	/*
	 * Dell Airplane Mode Switch driver (dell-rbtn) supports ACPI devices
	 * which can receive events from HW slider चयन.
	 *
	 * Dell SMBIOS on whitelisted models supports controlling radio devices
	 * but करोes not support receiving HW button चयन events. We can use
	 * i8042 filter hook function to receive keyboard data and handle
	 * keycode क्रम HW button.
	 *
	 * So अगर it is possible we will use Dell Airplane Mode Switch ACPI
	 * driver क्रम receiving HW events and Dell SMBIOS क्रम setting rfसमाप्त
	 * states. If ACPI driver or device is not available we will fallback to
	 * i8042 filter hook function.
	 *
	 * To prevent duplicate rfसमाप्त devices which control and करो same thing,
	 * dell-rbtn driver will स्वतःmatically हटाओ its own rfसमाप्त devices
	 * once function dell_rbtn_notअगरier_रेजिस्टर() is called.
	 */

	dell_rbtn_notअगरier_रेजिस्टर_func =
		symbol_request(dell_rbtn_notअगरier_रेजिस्टर);
	अगर (dell_rbtn_notअगरier_रेजिस्टर_func) अणु
		dell_rbtn_notअगरier_unरेजिस्टर_func =
			symbol_request(dell_rbtn_notअगरier_unरेजिस्टर);
		अगर (!dell_rbtn_notअगरier_unरेजिस्टर_func) अणु
			symbol_put(dell_rbtn_notअगरier_रेजिस्टर);
			dell_rbtn_notअगरier_रेजिस्टर_func = शून्य;
		पूर्ण
	पूर्ण

	अगर (dell_rbtn_notअगरier_रेजिस्टर_func) अणु
		ret = dell_rbtn_notअगरier_रेजिस्टर_func(
			&dell_laptop_rbtn_notअगरier);
		symbol_put(dell_rbtn_notअगरier_रेजिस्टर);
		dell_rbtn_notअगरier_रेजिस्टर_func = शून्य;
		अगर (ret != 0) अणु
			symbol_put(dell_rbtn_notअगरier_unरेजिस्टर);
			dell_rbtn_notअगरier_unरेजिस्टर_func = शून्य;
		पूर्ण
	पूर्ण अन्यथा अणु
		pr_info("Symbols from dell-rbtn acpi driver are not available\n");
		ret = -ENODEV;
	पूर्ण

	अगर (ret == 0) अणु
		pr_info("Using dell-rbtn acpi driver for receiving events\n");
	पूर्ण अन्यथा अगर (ret != -ENODEV) अणु
		pr_warn("Unable to register dell rbtn notifier\n");
		जाओ err_filter;
	पूर्ण अन्यथा अणु
		ret = i8042_install_filter(dell_laptop_i8042_filter);
		अगर (ret) अणु
			pr_warn("Unable to install key filter\n");
			जाओ err_filter;
		पूर्ण
		pr_info("Using i8042 filter function for receiving events\n");
	पूर्ण

	वापस 0;
err_filter:
	अगर (wwan_rfसमाप्त)
		rfसमाप्त_unरेजिस्टर(wwan_rfसमाप्त);
err_wwan:
	rfसमाप्त_destroy(wwan_rfसमाप्त);
	अगर (bluetooth_rfसमाप्त)
		rfसमाप्त_unरेजिस्टर(bluetooth_rfसमाप्त);
err_bluetooth:
	rfसमाप्त_destroy(bluetooth_rfसमाप्त);
	अगर (wअगरi_rfसमाप्त)
		rfसमाप्त_unरेजिस्टर(wअगरi_rfसमाप्त);
err_wअगरi:
	rfसमाप्त_destroy(wअगरi_rfसमाप्त);

	वापस ret;
पूर्ण

अटल व्योम dell_cleanup_rfसमाप्त(व्योम)
अणु
	अगर (dell_rbtn_notअगरier_unरेजिस्टर_func) अणु
		dell_rbtn_notअगरier_unरेजिस्टर_func(&dell_laptop_rbtn_notअगरier);
		symbol_put(dell_rbtn_notअगरier_unरेजिस्टर);
		dell_rbtn_notअगरier_unरेजिस्टर_func = शून्य;
	पूर्ण अन्यथा अणु
		i8042_हटाओ_filter(dell_laptop_i8042_filter);
	पूर्ण
	cancel_delayed_work_sync(&dell_rfसमाप्त_work);
	अगर (wअगरi_rfसमाप्त) अणु
		rfसमाप्त_unरेजिस्टर(wअगरi_rfसमाप्त);
		rfसमाप्त_destroy(wअगरi_rfसमाप्त);
	पूर्ण
	अगर (bluetooth_rfसमाप्त) अणु
		rfसमाप्त_unरेजिस्टर(bluetooth_rfसमाप्त);
		rfसमाप्त_destroy(bluetooth_rfसमाप्त);
	पूर्ण
	अगर (wwan_rfसमाप्त) अणु
		rfसमाप्त_unरेजिस्टर(wwan_rfसमाप्त);
		rfसमाप्त_destroy(wwan_rfसमाप्त);
	पूर्ण
पूर्ण

अटल पूर्णांक dell_send_पूर्णांकensity(काष्ठा backlight_device *bd)
अणु
	काष्ठा calling_पूर्णांकerface_buffer buffer;
	काष्ठा calling_पूर्णांकerface_token *token;
	पूर्णांक ret;

	token = dell_smbios_find_token(BRIGHTNESS_TOKEN);
	अगर (!token)
		वापस -ENODEV;

	dell_fill_request(&buffer,
			   token->location, bd->props.brightness, 0, 0);
	अगर (घातer_supply_is_प्रणाली_supplied() > 0)
		ret = dell_send_request(&buffer,
					CLASS_TOKEN_WRITE, SELECT_TOKEN_AC);
	अन्यथा
		ret = dell_send_request(&buffer,
					CLASS_TOKEN_WRITE, SELECT_TOKEN_BAT);

	वापस ret;
पूर्ण

अटल पूर्णांक dell_get_पूर्णांकensity(काष्ठा backlight_device *bd)
अणु
	काष्ठा calling_पूर्णांकerface_buffer buffer;
	काष्ठा calling_पूर्णांकerface_token *token;
	पूर्णांक ret;

	token = dell_smbios_find_token(BRIGHTNESS_TOKEN);
	अगर (!token)
		वापस -ENODEV;

	dell_fill_request(&buffer, token->location, 0, 0, 0);
	अगर (घातer_supply_is_प्रणाली_supplied() > 0)
		ret = dell_send_request(&buffer,
					CLASS_TOKEN_READ, SELECT_TOKEN_AC);
	अन्यथा
		ret = dell_send_request(&buffer,
					CLASS_TOKEN_READ, SELECT_TOKEN_BAT);

	अगर (ret == 0)
		ret = buffer.output[1];

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा backlight_ops dell_ops = अणु
	.get_brightness = dell_get_पूर्णांकensity,
	.update_status  = dell_send_पूर्णांकensity,
पूर्ण;

अटल व्योम touchpad_led_on(व्योम)
अणु
	पूर्णांक command = 0x97;
	अक्षर data = 1;
	i8042_command(&data, command | 1 << 12);
पूर्ण

अटल व्योम touchpad_led_off(व्योम)
अणु
	पूर्णांक command = 0x97;
	अक्षर data = 2;
	i8042_command(&data, command | 1 << 12);
पूर्ण

अटल व्योम touchpad_led_set(काष्ठा led_classdev *led_cdev,
	क्रमागत led_brightness value)
अणु
	अगर (value > 0)
		touchpad_led_on();
	अन्यथा
		touchpad_led_off();
पूर्ण

अटल काष्ठा led_classdev touchpad_led = अणु
	.name = "dell-laptop::touchpad",
	.brightness_set = touchpad_led_set,
	.flags = LED_CORE_SUSPENDRESUME,
पूर्ण;

अटल पूर्णांक __init touchpad_led_init(काष्ठा device *dev)
अणु
	वापस led_classdev_रेजिस्टर(dev, &touchpad_led);
पूर्ण

अटल व्योम touchpad_led_निकास(व्योम)
अणु
	led_classdev_unरेजिस्टर(&touchpad_led);
पूर्ण

/*
 * Derived from inक्रमmation in smbios-keyboard-ctl:
 *
 * cbClass 4
 * cbSelect 11
 * Keyboard illumination
 * cbArg1 determines the function to be perक्रमmed
 *
 * cbArg1 0x0 = Get Feature Inक्रमmation
 *  cbRES1         Standard वापस codes (0, -1, -2)
 *  cbRES2, word0  Biपंचांगap of user-selectable modes
 *     bit 0     Always off (All प्रणालीs)
 *     bit 1     Always on (Travis ATG, Siberia)
 *     bit 2     Auto: ALS-based On; ALS-based Off (Travis ATG)
 *     bit 3     Auto: ALS- and input-activity-based On; input-activity based Off
 *     bit 4     Auto: Input-activity-based On; input-activity based Off
 *     bit 5     Auto: Input-activity-based On (illumination level 25%); input-activity based Off
 *     bit 6     Auto: Input-activity-based On (illumination level 50%); input-activity based Off
 *     bit 7     Auto: Input-activity-based On (illumination level 75%); input-activity based Off
 *     bit 8     Auto: Input-activity-based On (illumination level 100%); input-activity based Off
 *     bits 9-15 Reserved क्रम future use
 *  cbRES2, byte2  Reserved क्रम future use
 *  cbRES2, byte3  Keyboard illumination type
 *     0         Reserved
 *     1         Tasklight
 *     2         Backlight
 *     3-255     Reserved क्रम future use
 *  cbRES3, byte0  Supported स्वतः keyboard illumination trigger biपंचांगap.
 *     bit 0     Any keystroke
 *     bit 1     Touchpad activity
 *     bit 2     Poपूर्णांकing stick
 *     bit 3     Any mouse
 *     bits 4-7  Reserved क्रम future use
 *  cbRES3, byte1  Supported समयout unit biपंचांगap
 *     bit 0     Seconds
 *     bit 1     Minutes
 *     bit 2     Hours
 *     bit 3     Days
 *     bits 4-7  Reserved क्रम future use
 *  cbRES3, byte2  Number of keyboard light brightness levels
 *  cbRES4, byte0  Maximum acceptable seconds value (0 अगर seconds not supported).
 *  cbRES4, byte1  Maximum acceptable minutes value (0 अगर minutes not supported).
 *  cbRES4, byte2  Maximum acceptable hours value (0 अगर hours not supported).
 *  cbRES4, byte3  Maximum acceptable days value (0 अगर days not supported)
 *
 * cbArg1 0x1 = Get Current State
 *  cbRES1         Standard वापस codes (0, -1, -2)
 *  cbRES2, word0  Biपंचांगap of current mode state
 *     bit 0     Always off (All प्रणालीs)
 *     bit 1     Always on (Travis ATG, Siberia)
 *     bit 2     Auto: ALS-based On; ALS-based Off (Travis ATG)
 *     bit 3     Auto: ALS- and input-activity-based On; input-activity based Off
 *     bit 4     Auto: Input-activity-based On; input-activity based Off
 *     bit 5     Auto: Input-activity-based On (illumination level 25%); input-activity based Off
 *     bit 6     Auto: Input-activity-based On (illumination level 50%); input-activity based Off
 *     bit 7     Auto: Input-activity-based On (illumination level 75%); input-activity based Off
 *     bit 8     Auto: Input-activity-based On (illumination level 100%); input-activity based Off
 *     bits 9-15 Reserved क्रम future use
 *     Note: Only One bit can be set
 *  cbRES2, byte2  Currently active स्वतः keyboard illumination triggers.
 *     bit 0     Any keystroke
 *     bit 1     Touchpad activity
 *     bit 2     Poपूर्णांकing stick
 *     bit 3     Any mouse
 *     bits 4-7  Reserved क्रम future use
 *  cbRES2, byte3  Current Timeout on battery
 *     bits 7:6  Timeout units indicator:
 *     00b       Seconds
 *     01b       Minutes
 *     10b       Hours
 *     11b       Days
 *     bits 5:0  Timeout value (0-63) in sec/min/hr/day
 *     NOTE: A value of 0 means always on (no समयout) अगर any bits of RES3 byte
 *     are set upon वापस from the [Get feature inक्रमmation] call.
 *  cbRES3, byte0  Current setting of ALS value that turns the light on or off.
 *  cbRES3, byte1  Current ALS पढ़ोing
 *  cbRES3, byte2  Current keyboard light level.
 *  cbRES3, byte3  Current समयout on AC Power
 *     bits 7:6  Timeout units indicator:
 *     00b       Seconds
 *     01b       Minutes
 *     10b       Hours
 *     11b       Days
 *     Bits 5:0  Timeout value (0-63) in sec/min/hr/day
 *     NOTE: A value of 0 means always on (no समयout) अगर any bits of RES3 byte2
 *     are set upon वापस from the upon वापस from the [Get Feature inक्रमmation] call.
 *
 * cbArg1 0x2 = Set New State
 *  cbRES1         Standard वापस codes (0, -1, -2)
 *  cbArg2, word0  Biपंचांगap of current mode state
 *     bit 0     Always off (All प्रणालीs)
 *     bit 1     Always on (Travis ATG, Siberia)
 *     bit 2     Auto: ALS-based On; ALS-based Off (Travis ATG)
 *     bit 3     Auto: ALS- and input-activity-based On; input-activity based Off
 *     bit 4     Auto: Input-activity-based On; input-activity based Off
 *     bit 5     Auto: Input-activity-based On (illumination level 25%); input-activity based Off
 *     bit 6     Auto: Input-activity-based On (illumination level 50%); input-activity based Off
 *     bit 7     Auto: Input-activity-based On (illumination level 75%); input-activity based Off
 *     bit 8     Auto: Input-activity-based On (illumination level 100%); input-activity based Off
 *     bits 9-15 Reserved क्रम future use
 *     Note: Only One bit can be set
 *  cbArg2, byte2  Desired स्वतः keyboard illumination triggers. Must reमुख्य inactive to allow
 *                 keyboard to turn off स्वतःmatically.
 *     bit 0     Any keystroke
 *     bit 1     Touchpad activity
 *     bit 2     Poपूर्णांकing stick
 *     bit 3     Any mouse
 *     bits 4-7  Reserved क्रम future use
 *  cbArg2, byte3  Desired Timeout on battery
 *     bits 7:6  Timeout units indicator:
 *     00b       Seconds
 *     01b       Minutes
 *     10b       Hours
 *     11b       Days
 *     bits 5:0  Timeout value (0-63) in sec/min/hr/day
 *  cbArg3, byte0  Desired setting of ALS value that turns the light on or off.
 *  cbArg3, byte2  Desired keyboard light level.
 *  cbArg3, byte3  Desired Timeout on AC घातer
 *     bits 7:6  Timeout units indicator:
 *     00b       Seconds
 *     01b       Minutes
 *     10b       Hours
 *     11b       Days
 *     bits 5:0  Timeout value (0-63) in sec/min/hr/day
 */


क्रमागत kbd_समयout_unit अणु
	KBD_TIMEOUT_SECONDS = 0,
	KBD_TIMEOUT_MINUTES,
	KBD_TIMEOUT_HOURS,
	KBD_TIMEOUT_DAYS,
पूर्ण;

क्रमागत kbd_mode_bit अणु
	KBD_MODE_BIT_OFF = 0,
	KBD_MODE_BIT_ON,
	KBD_MODE_BIT_ALS,
	KBD_MODE_BIT_TRIGGER_ALS,
	KBD_MODE_BIT_TRIGGER,
	KBD_MODE_BIT_TRIGGER_25,
	KBD_MODE_BIT_TRIGGER_50,
	KBD_MODE_BIT_TRIGGER_75,
	KBD_MODE_BIT_TRIGGER_100,
पूर्ण;

#घोषणा kbd_is_als_mode_bit(bit) \
	((bit) == KBD_MODE_BIT_ALS || (bit) == KBD_MODE_BIT_TRIGGER_ALS)
#घोषणा kbd_is_trigger_mode_bit(bit) \
	((bit) >= KBD_MODE_BIT_TRIGGER_ALS && (bit) <= KBD_MODE_BIT_TRIGGER_100)
#घोषणा kbd_is_level_mode_bit(bit) \
	((bit) >= KBD_MODE_BIT_TRIGGER_25 && (bit) <= KBD_MODE_BIT_TRIGGER_100)

काष्ठा kbd_info अणु
	u16 modes;
	u8 type;
	u8 triggers;
	u8 levels;
	u8 seconds;
	u8 minutes;
	u8 hours;
	u8 days;
पूर्ण;

काष्ठा kbd_state अणु
	u8 mode_bit;
	u8 triggers;
	u8 समयout_value;
	u8 समयout_unit;
	u8 समयout_value_ac;
	u8 समयout_unit_ac;
	u8 als_setting;
	u8 als_value;
	u8 level;
पूर्ण;

अटल स्थिर पूर्णांक kbd_tokens[] = अणु
	KBD_LED_OFF_TOKEN,
	KBD_LED_AUTO_25_TOKEN,
	KBD_LED_AUTO_50_TOKEN,
	KBD_LED_AUTO_75_TOKEN,
	KBD_LED_AUTO_100_TOKEN,
	KBD_LED_ON_TOKEN,
पूर्ण;

अटल u16 kbd_token_bits;

अटल काष्ठा kbd_info kbd_info;
अटल bool kbd_als_supported;
अटल bool kbd_triggers_supported;
अटल bool kbd_समयout_ac_supported;

अटल u8 kbd_mode_levels[16];
अटल पूर्णांक kbd_mode_levels_count;

अटल u8 kbd_previous_level;
अटल u8 kbd_previous_mode_bit;

अटल bool kbd_led_present;
अटल DEFINE_MUTEX(kbd_led_mutex);
अटल क्रमागत led_brightness kbd_led_level;

/*
 * NOTE: there are three ways to set the keyboard backlight level.
 * First, via kbd_state.mode_bit (assigning KBD_MODE_BIT_TRIGGER_* value).
 * Second, via kbd_state.level (assigning numerical value <= kbd_info.levels).
 * Third, via SMBIOS tokens (KBD_LED_* in kbd_tokens)
 *
 * There are laptops which support only one of these methods. If we want to
 * support as many machines as possible we need to implement all three methods.
 * The first two methods use the kbd_state काष्ठाure. The third uses SMBIOS
 * tokens. If kbd_info.levels == 0, the machine करोes not support setting the
 * keyboard backlight level via kbd_state.level.
 */

अटल पूर्णांक kbd_get_info(काष्ठा kbd_info *info)
अणु
	काष्ठा calling_पूर्णांकerface_buffer buffer;
	u8 units;
	पूर्णांक ret;

	dell_fill_request(&buffer, 0, 0, 0, 0);
	ret = dell_send_request(&buffer,
				CLASS_KBD_BACKLIGHT, SELECT_KBD_BACKLIGHT);
	अगर (ret)
		वापस ret;

	info->modes = buffer.output[1] & 0xFFFF;
	info->type = (buffer.output[1] >> 24) & 0xFF;
	info->triggers = buffer.output[2] & 0xFF;
	units = (buffer.output[2] >> 8) & 0xFF;
	info->levels = (buffer.output[2] >> 16) & 0xFF;

	अगर (quirks && quirks->kbd_led_levels_off_1 && info->levels)
		info->levels--;

	अगर (units & BIT(0))
		info->seconds = (buffer.output[3] >> 0) & 0xFF;
	अगर (units & BIT(1))
		info->minutes = (buffer.output[3] >> 8) & 0xFF;
	अगर (units & BIT(2))
		info->hours = (buffer.output[3] >> 16) & 0xFF;
	अगर (units & BIT(3))
		info->days = (buffer.output[3] >> 24) & 0xFF;

	वापस ret;
पूर्ण

अटल अचिन्हित पूर्णांक kbd_get_max_level(व्योम)
अणु
	अगर (kbd_info.levels != 0)
		वापस kbd_info.levels;
	अगर (kbd_mode_levels_count > 0)
		वापस kbd_mode_levels_count - 1;
	वापस 0;
पूर्ण

अटल पूर्णांक kbd_get_level(काष्ठा kbd_state *state)
अणु
	पूर्णांक i;

	अगर (kbd_info.levels != 0)
		वापस state->level;

	अगर (kbd_mode_levels_count > 0) अणु
		क्रम (i = 0; i < kbd_mode_levels_count; ++i)
			अगर (kbd_mode_levels[i] == state->mode_bit)
				वापस i;
		वापस 0;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक kbd_set_level(काष्ठा kbd_state *state, u8 level)
अणु
	अगर (kbd_info.levels != 0) अणु
		अगर (level != 0)
			kbd_previous_level = level;
		अगर (state->level == level)
			वापस 0;
		state->level = level;
		अगर (level != 0 && state->mode_bit == KBD_MODE_BIT_OFF)
			state->mode_bit = kbd_previous_mode_bit;
		अन्यथा अगर (level == 0 && state->mode_bit != KBD_MODE_BIT_OFF) अणु
			kbd_previous_mode_bit = state->mode_bit;
			state->mode_bit = KBD_MODE_BIT_OFF;
		पूर्ण
		वापस 0;
	पूर्ण

	अगर (kbd_mode_levels_count > 0 && level < kbd_mode_levels_count) अणु
		अगर (level != 0)
			kbd_previous_level = level;
		state->mode_bit = kbd_mode_levels[level];
		वापस 0;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक kbd_get_state(काष्ठा kbd_state *state)
अणु
	काष्ठा calling_पूर्णांकerface_buffer buffer;
	पूर्णांक ret;

	dell_fill_request(&buffer, 0x1, 0, 0, 0);
	ret = dell_send_request(&buffer,
				CLASS_KBD_BACKLIGHT, SELECT_KBD_BACKLIGHT);
	अगर (ret)
		वापस ret;

	state->mode_bit = ffs(buffer.output[1] & 0xFFFF);
	अगर (state->mode_bit != 0)
		state->mode_bit--;

	state->triggers = (buffer.output[1] >> 16) & 0xFF;
	state->समयout_value = (buffer.output[1] >> 24) & 0x3F;
	state->समयout_unit = (buffer.output[1] >> 30) & 0x3;
	state->als_setting = buffer.output[2] & 0xFF;
	state->als_value = (buffer.output[2] >> 8) & 0xFF;
	state->level = (buffer.output[2] >> 16) & 0xFF;
	state->समयout_value_ac = (buffer.output[2] >> 24) & 0x3F;
	state->समयout_unit_ac = (buffer.output[2] >> 30) & 0x3;

	वापस ret;
पूर्ण

अटल पूर्णांक kbd_set_state(काष्ठा kbd_state *state)
अणु
	काष्ठा calling_पूर्णांकerface_buffer buffer;
	पूर्णांक ret;
	u32 input1;
	u32 input2;

	input1 = BIT(state->mode_bit) & 0xFFFF;
	input1 |= (state->triggers & 0xFF) << 16;
	input1 |= (state->समयout_value & 0x3F) << 24;
	input1 |= (state->समयout_unit & 0x3) << 30;
	input2 = state->als_setting & 0xFF;
	input2 |= (state->level & 0xFF) << 16;
	input2 |= (state->समयout_value_ac & 0x3F) << 24;
	input2 |= (state->समयout_unit_ac & 0x3) << 30;
	dell_fill_request(&buffer, 0x2, input1, input2, 0);
	ret = dell_send_request(&buffer,
				CLASS_KBD_BACKLIGHT, SELECT_KBD_BACKLIGHT);

	वापस ret;
पूर्ण

अटल पूर्णांक kbd_set_state_safe(काष्ठा kbd_state *state, काष्ठा kbd_state *old)
अणु
	पूर्णांक ret;

	ret = kbd_set_state(state);
	अगर (ret == 0)
		वापस 0;

	/*
	 * When setting the new state fails,try to restore the previous one.
	 * This is needed on some machines where BIOS sets a शेष state when
	 * setting a new state fails. This शेष state could be all off.
	 */

	अगर (kbd_set_state(old))
		pr_err("Setting old previous keyboard state failed\n");

	वापस ret;
पूर्ण

अटल पूर्णांक kbd_set_token_bit(u8 bit)
अणु
	काष्ठा calling_पूर्णांकerface_buffer buffer;
	काष्ठा calling_पूर्णांकerface_token *token;
	पूर्णांक ret;

	अगर (bit >= ARRAY_SIZE(kbd_tokens))
		वापस -EINVAL;

	token = dell_smbios_find_token(kbd_tokens[bit]);
	अगर (!token)
		वापस -EINVAL;

	dell_fill_request(&buffer, token->location, token->value, 0, 0);
	ret = dell_send_request(&buffer, CLASS_TOKEN_WRITE, SELECT_TOKEN_STD);

	वापस ret;
पूर्ण

अटल पूर्णांक kbd_get_token_bit(u8 bit)
अणु
	काष्ठा calling_पूर्णांकerface_buffer buffer;
	काष्ठा calling_पूर्णांकerface_token *token;
	पूर्णांक ret;
	पूर्णांक val;

	अगर (bit >= ARRAY_SIZE(kbd_tokens))
		वापस -EINVAL;

	token = dell_smbios_find_token(kbd_tokens[bit]);
	अगर (!token)
		वापस -EINVAL;

	dell_fill_request(&buffer, token->location, 0, 0, 0);
	ret = dell_send_request(&buffer, CLASS_TOKEN_READ, SELECT_TOKEN_STD);
	val = buffer.output[1];

	अगर (ret)
		वापस ret;

	वापस (val == token->value);
पूर्ण

अटल पूर्णांक kbd_get_first_active_token_bit(व्योम)
अणु
	पूर्णांक i;
	पूर्णांक ret;

	क्रम (i = 0; i < ARRAY_SIZE(kbd_tokens); ++i) अणु
		ret = kbd_get_token_bit(i);
		अगर (ret == 1)
			वापस i;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक kbd_get_valid_token_counts(व्योम)
अणु
	वापस hweight16(kbd_token_bits);
पूर्ण

अटल अंतरभूत पूर्णांक kbd_init_info(व्योम)
अणु
	काष्ठा kbd_state state;
	पूर्णांक ret;
	पूर्णांक i;

	ret = kbd_get_info(&kbd_info);
	अगर (ret)
		वापस ret;

	/* NOTE: Old models without KBD_LED_AC_TOKEN token supports only one
	 *       समयout value which is shared क्रम both battery and AC घातer
	 *       settings. So करो not try to set AC values on old models.
	 */
	अगर ((quirks && quirks->kbd_missing_ac_tag) ||
	    dell_smbios_find_token(KBD_LED_AC_TOKEN))
		kbd_समयout_ac_supported = true;

	kbd_get_state(&state);

	/* NOTE: समयout value is stored in 6 bits so max value is 63 */
	अगर (kbd_info.seconds > 63)
		kbd_info.seconds = 63;
	अगर (kbd_info.minutes > 63)
		kbd_info.minutes = 63;
	अगर (kbd_info.hours > 63)
		kbd_info.hours = 63;
	अगर (kbd_info.days > 63)
		kbd_info.days = 63;

	/* NOTE: On tested machines ON mode did not work and caused
	 *       problems (turned backlight off) so करो not use it
	 */
	kbd_info.modes &= ~BIT(KBD_MODE_BIT_ON);

	kbd_previous_level = kbd_get_level(&state);
	kbd_previous_mode_bit = state.mode_bit;

	अगर (kbd_previous_level == 0 && kbd_get_max_level() != 0)
		kbd_previous_level = 1;

	अगर (kbd_previous_mode_bit == KBD_MODE_BIT_OFF) अणु
		kbd_previous_mode_bit =
			ffs(kbd_info.modes & ~BIT(KBD_MODE_BIT_OFF));
		अगर (kbd_previous_mode_bit != 0)
			kbd_previous_mode_bit--;
	पूर्ण

	अगर (kbd_info.modes & (BIT(KBD_MODE_BIT_ALS) |
			      BIT(KBD_MODE_BIT_TRIGGER_ALS)))
		kbd_als_supported = true;

	अगर (kbd_info.modes & (
	    BIT(KBD_MODE_BIT_TRIGGER_ALS) | BIT(KBD_MODE_BIT_TRIGGER) |
	    BIT(KBD_MODE_BIT_TRIGGER_25) | BIT(KBD_MODE_BIT_TRIGGER_50) |
	    BIT(KBD_MODE_BIT_TRIGGER_75) | BIT(KBD_MODE_BIT_TRIGGER_100)
	   ))
		kbd_triggers_supported = true;

	/* kbd_mode_levels[0] is reserved, see below */
	क्रम (i = 0; i < 16; ++i)
		अगर (kbd_is_level_mode_bit(i) && (BIT(i) & kbd_info.modes))
			kbd_mode_levels[1 + kbd_mode_levels_count++] = i;

	/*
	 * Find the first supported mode and assign to kbd_mode_levels[0].
	 * This should be 0 (off), but we cannot depend on the BIOS to
	 * support 0.
	 */
	अगर (kbd_mode_levels_count > 0) अणु
		क्रम (i = 0; i < 16; ++i) अणु
			अगर (BIT(i) & kbd_info.modes) अणु
				kbd_mode_levels[0] = i;
				अवरोध;
			पूर्ण
		पूर्ण
		kbd_mode_levels_count++;
	पूर्ण

	वापस 0;

पूर्ण

अटल अंतरभूत व्योम kbd_init_tokens(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(kbd_tokens); ++i)
		अगर (dell_smbios_find_token(kbd_tokens[i]))
			kbd_token_bits |= BIT(i);
पूर्ण

अटल व्योम kbd_init(व्योम)
अणु
	पूर्णांक ret;

	अगर (quirks && quirks->kbd_led_not_present)
		वापस;

	ret = kbd_init_info();
	kbd_init_tokens();

	/*
	 * Only supports keyboard backlight when it has at least two modes.
	 */
	अगर ((ret == 0 && (kbd_info.levels != 0 || kbd_mode_levels_count >= 2))
	    || kbd_get_valid_token_counts() >= 2)
		kbd_led_present = true;
पूर्ण

अटल sमाप_प्रकार kbd_led_समयout_store(काष्ठा device *dev,
				     काष्ठा device_attribute *attr,
				     स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा kbd_state new_state;
	काष्ठा kbd_state state;
	bool convert;
	पूर्णांक value;
	पूर्णांक ret;
	अक्षर ch;
	u8 unit;
	पूर्णांक i;

	ret = माला_पूछो(buf, "%d %c", &value, &ch);
	अगर (ret < 1)
		वापस -EINVAL;
	अन्यथा अगर (ret == 1)
		ch = 's';

	अगर (value < 0)
		वापस -EINVAL;

	convert = false;

	चयन (ch) अणु
	हाल 's':
		अगर (value > kbd_info.seconds)
			convert = true;
		unit = KBD_TIMEOUT_SECONDS;
		अवरोध;
	हाल 'm':
		अगर (value > kbd_info.minutes)
			convert = true;
		unit = KBD_TIMEOUT_MINUTES;
		अवरोध;
	हाल 'h':
		अगर (value > kbd_info.hours)
			convert = true;
		unit = KBD_TIMEOUT_HOURS;
		अवरोध;
	हाल 'd':
		अगर (value > kbd_info.days)
			convert = true;
		unit = KBD_TIMEOUT_DAYS;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (quirks && quirks->needs_kbd_समयouts)
		convert = true;

	अगर (convert) अणु
		/* Convert value from current units to seconds */
		चयन (unit) अणु
		हाल KBD_TIMEOUT_DAYS:
			value *= 24;
			fallthrough;
		हाल KBD_TIMEOUT_HOURS:
			value *= 60;
			fallthrough;
		हाल KBD_TIMEOUT_MINUTES:
			value *= 60;
			unit = KBD_TIMEOUT_SECONDS;
		पूर्ण

		अगर (quirks && quirks->needs_kbd_समयouts) अणु
			क्रम (i = 0; quirks->kbd_समयouts[i] != -1; i++) अणु
				अगर (value <= quirks->kbd_समयouts[i]) अणु
					value = quirks->kbd_समयouts[i];
					अवरोध;
				पूर्ण
			पूर्ण
		पूर्ण

		अगर (value <= kbd_info.seconds && kbd_info.seconds) अणु
			unit = KBD_TIMEOUT_SECONDS;
		पूर्ण अन्यथा अगर (value / 60 <= kbd_info.minutes && kbd_info.minutes) अणु
			value /= 60;
			unit = KBD_TIMEOUT_MINUTES;
		पूर्ण अन्यथा अगर (value / (60 * 60) <= kbd_info.hours && kbd_info.hours) अणु
			value /= (60 * 60);
			unit = KBD_TIMEOUT_HOURS;
		पूर्ण अन्यथा अगर (value / (60 * 60 * 24) <= kbd_info.days && kbd_info.days) अणु
			value /= (60 * 60 * 24);
			unit = KBD_TIMEOUT_DAYS;
		पूर्ण अन्यथा अणु
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	mutex_lock(&kbd_led_mutex);

	ret = kbd_get_state(&state);
	अगर (ret)
		जाओ out;

	new_state = state;

	अगर (kbd_समयout_ac_supported && घातer_supply_is_प्रणाली_supplied() > 0) अणु
		new_state.समयout_value_ac = value;
		new_state.समयout_unit_ac = unit;
	पूर्ण अन्यथा अणु
		new_state.समयout_value = value;
		new_state.समयout_unit = unit;
	पूर्ण

	ret = kbd_set_state_safe(&new_state, &state);
	अगर (ret)
		जाओ out;

	ret = count;
out:
	mutex_unlock(&kbd_led_mutex);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार kbd_led_समयout_show(काष्ठा device *dev,
				    काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा kbd_state state;
	पूर्णांक value;
	पूर्णांक ret;
	पूर्णांक len;
	u8 unit;

	ret = kbd_get_state(&state);
	अगर (ret)
		वापस ret;

	अगर (kbd_समयout_ac_supported && घातer_supply_is_प्रणाली_supplied() > 0) अणु
		value = state.समयout_value_ac;
		unit = state.समयout_unit_ac;
	पूर्ण अन्यथा अणु
		value = state.समयout_value;
		unit = state.समयout_unit;
	पूर्ण

	len = प्र_लिखो(buf, "%d", value);

	चयन (unit) अणु
	हाल KBD_TIMEOUT_SECONDS:
		वापस len + प्र_लिखो(buf+len, "s\n");
	हाल KBD_TIMEOUT_MINUTES:
		वापस len + प्र_लिखो(buf+len, "m\n");
	हाल KBD_TIMEOUT_HOURS:
		वापस len + प्र_लिखो(buf+len, "h\n");
	हाल KBD_TIMEOUT_DAYS:
		वापस len + प्र_लिखो(buf+len, "d\n");
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस len;
पूर्ण

अटल DEVICE_ATTR(stop_समयout, S_IRUGO | S_IWUSR,
		   kbd_led_समयout_show, kbd_led_समयout_store);

अटल स्थिर अक्षर * स्थिर kbd_led_triggers[] = अणु
	"keyboard",
	"touchpad",
	/*"trackstick"*/ शून्य, /* NOTE: trackstick is just alias क्रम touchpad */
	"mouse",
पूर्ण;

अटल sमाप_प्रकार kbd_led_triggers_store(काष्ठा device *dev,
				      काष्ठा device_attribute *attr,
				      स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा kbd_state new_state;
	काष्ठा kbd_state state;
	bool triggers_enabled = false;
	पूर्णांक trigger_bit = -1;
	अक्षर trigger[21];
	पूर्णांक i, ret;

	ret = माला_पूछो(buf, "%20s", trigger);
	अगर (ret != 1)
		वापस -EINVAL;

	अगर (trigger[0] != '+' && trigger[0] != '-')
		वापस -EINVAL;

	mutex_lock(&kbd_led_mutex);

	ret = kbd_get_state(&state);
	अगर (ret)
		जाओ out;

	अगर (kbd_triggers_supported)
		triggers_enabled = kbd_is_trigger_mode_bit(state.mode_bit);

	अगर (kbd_triggers_supported) अणु
		क्रम (i = 0; i < ARRAY_SIZE(kbd_led_triggers); ++i) अणु
			अगर (!(kbd_info.triggers & BIT(i)))
				जारी;
			अगर (!kbd_led_triggers[i])
				जारी;
			अगर (म_भेद(trigger+1, kbd_led_triggers[i]) != 0)
				जारी;
			अगर (trigger[0] == '+' &&
			    triggers_enabled && (state.triggers & BIT(i))) अणु
				ret = count;
				जाओ out;
			पूर्ण
			अगर (trigger[0] == '-' &&
			    (!triggers_enabled || !(state.triggers & BIT(i)))) अणु
				ret = count;
				जाओ out;
			पूर्ण
			trigger_bit = i;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (trigger_bit == -1) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	new_state = state;
	अगर (trigger[0] == '+')
		new_state.triggers |= BIT(trigger_bit);
	अन्यथा अणु
		new_state.triggers &= ~BIT(trigger_bit);
		/*
		 * NOTE: trackstick bit (2) must be disabled when
		 *       disabling touchpad bit (1), otherwise touchpad
		 *       bit (1) will not be disabled
		 */
		अगर (trigger_bit == 1)
			new_state.triggers &= ~BIT(2);
	पूर्ण
	अगर ((kbd_info.triggers & new_state.triggers) !=
	    new_state.triggers) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण
	अगर (new_state.triggers && !triggers_enabled) अणु
		new_state.mode_bit = KBD_MODE_BIT_TRIGGER;
		kbd_set_level(&new_state, kbd_previous_level);
	पूर्ण अन्यथा अगर (new_state.triggers == 0) अणु
		kbd_set_level(&new_state, 0);
	पूर्ण
	अगर (!(kbd_info.modes & BIT(new_state.mode_bit))) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण
	ret = kbd_set_state_safe(&new_state, &state);
	अगर (ret)
		जाओ out;
	अगर (new_state.mode_bit != KBD_MODE_BIT_OFF)
		kbd_previous_mode_bit = new_state.mode_bit;
	ret = count;
out:
	mutex_unlock(&kbd_led_mutex);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार kbd_led_triggers_show(काष्ठा device *dev,
				     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा kbd_state state;
	bool triggers_enabled;
	पूर्णांक level, i, ret;
	पूर्णांक len = 0;

	ret = kbd_get_state(&state);
	अगर (ret)
		वापस ret;

	len = 0;

	अगर (kbd_triggers_supported) अणु
		triggers_enabled = kbd_is_trigger_mode_bit(state.mode_bit);
		level = kbd_get_level(&state);
		क्रम (i = 0; i < ARRAY_SIZE(kbd_led_triggers); ++i) अणु
			अगर (!(kbd_info.triggers & BIT(i)))
				जारी;
			अगर (!kbd_led_triggers[i])
				जारी;
			अगर ((triggers_enabled || level <= 0) &&
			    (state.triggers & BIT(i)))
				buf[len++] = '+';
			अन्यथा
				buf[len++] = '-';
			len += प्र_लिखो(buf+len, "%s ", kbd_led_triggers[i]);
		पूर्ण
	पूर्ण

	अगर (len)
		buf[len - 1] = '\n';

	वापस len;
पूर्ण

अटल DEVICE_ATTR(start_triggers, S_IRUGO | S_IWUSR,
		   kbd_led_triggers_show, kbd_led_triggers_store);

अटल sमाप_प्रकार kbd_led_als_enabled_store(काष्ठा device *dev,
					 काष्ठा device_attribute *attr,
					 स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा kbd_state new_state;
	काष्ठा kbd_state state;
	bool triggers_enabled = false;
	पूर्णांक enable;
	पूर्णांक ret;

	ret = kstrtoपूर्णांक(buf, 0, &enable);
	अगर (ret)
		वापस ret;

	mutex_lock(&kbd_led_mutex);

	ret = kbd_get_state(&state);
	अगर (ret)
		जाओ out;

	अगर (enable == kbd_is_als_mode_bit(state.mode_bit)) अणु
		ret = count;
		जाओ out;
	पूर्ण

	new_state = state;

	अगर (kbd_triggers_supported)
		triggers_enabled = kbd_is_trigger_mode_bit(state.mode_bit);

	अगर (enable) अणु
		अगर (triggers_enabled)
			new_state.mode_bit = KBD_MODE_BIT_TRIGGER_ALS;
		अन्यथा
			new_state.mode_bit = KBD_MODE_BIT_ALS;
	पूर्ण अन्यथा अणु
		अगर (triggers_enabled) अणु
			new_state.mode_bit = KBD_MODE_BIT_TRIGGER;
			kbd_set_level(&new_state, kbd_previous_level);
		पूर्ण अन्यथा अणु
			new_state.mode_bit = KBD_MODE_BIT_ON;
		पूर्ण
	पूर्ण
	अगर (!(kbd_info.modes & BIT(new_state.mode_bit)))  अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	ret = kbd_set_state_safe(&new_state, &state);
	अगर (ret)
		जाओ out;
	kbd_previous_mode_bit = new_state.mode_bit;

	ret = count;
out:
	mutex_unlock(&kbd_led_mutex);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार kbd_led_als_enabled_show(काष्ठा device *dev,
					काष्ठा device_attribute *attr,
					अक्षर *buf)
अणु
	काष्ठा kbd_state state;
	bool enabled = false;
	पूर्णांक ret;

	ret = kbd_get_state(&state);
	अगर (ret)
		वापस ret;
	enabled = kbd_is_als_mode_bit(state.mode_bit);

	वापस प्र_लिखो(buf, "%d\n", enabled ? 1 : 0);
पूर्ण

अटल DEVICE_ATTR(als_enabled, S_IRUGO | S_IWUSR,
		   kbd_led_als_enabled_show, kbd_led_als_enabled_store);

अटल sमाप_प्रकार kbd_led_als_setting_store(काष्ठा device *dev,
					 काष्ठा device_attribute *attr,
					 स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा kbd_state state;
	काष्ठा kbd_state new_state;
	u8 setting;
	पूर्णांक ret;

	ret = kstrtou8(buf, 10, &setting);
	अगर (ret)
		वापस ret;

	mutex_lock(&kbd_led_mutex);

	ret = kbd_get_state(&state);
	अगर (ret)
		जाओ out;

	new_state = state;
	new_state.als_setting = setting;

	ret = kbd_set_state_safe(&new_state, &state);
	अगर (ret)
		जाओ out;

	ret = count;
out:
	mutex_unlock(&kbd_led_mutex);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार kbd_led_als_setting_show(काष्ठा device *dev,
					काष्ठा device_attribute *attr,
					अक्षर *buf)
अणु
	काष्ठा kbd_state state;
	पूर्णांक ret;

	ret = kbd_get_state(&state);
	अगर (ret)
		वापस ret;

	वापस प्र_लिखो(buf, "%d\n", state.als_setting);
पूर्ण

अटल DEVICE_ATTR(als_setting, S_IRUGO | S_IWUSR,
		   kbd_led_als_setting_show, kbd_led_als_setting_store);

अटल काष्ठा attribute *kbd_led_attrs[] = अणु
	&dev_attr_stop_समयout.attr,
	&dev_attr_start_triggers.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group kbd_led_group = अणु
	.attrs = kbd_led_attrs,
पूर्ण;

अटल काष्ठा attribute *kbd_led_als_attrs[] = अणु
	&dev_attr_als_enabled.attr,
	&dev_attr_als_setting.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group kbd_led_als_group = अणु
	.attrs = kbd_led_als_attrs,
पूर्ण;

अटल स्थिर काष्ठा attribute_group *kbd_led_groups[] = अणु
	&kbd_led_group,
	&kbd_led_als_group,
	शून्य,
पूर्ण;

अटल क्रमागत led_brightness kbd_led_level_get(काष्ठा led_classdev *led_cdev)
अणु
	पूर्णांक ret;
	u16 num;
	काष्ठा kbd_state state;

	अगर (kbd_get_max_level()) अणु
		ret = kbd_get_state(&state);
		अगर (ret)
			वापस 0;
		ret = kbd_get_level(&state);
		अगर (ret < 0)
			वापस 0;
		वापस ret;
	पूर्ण

	अगर (kbd_get_valid_token_counts()) अणु
		ret = kbd_get_first_active_token_bit();
		अगर (ret < 0)
			वापस 0;
		क्रम (num = kbd_token_bits; num != 0 && ret > 0; --ret)
			num &= num - 1; /* clear the first bit set */
		अगर (num == 0)
			वापस 0;
		वापस ffs(num) - 1;
	पूर्ण

	pr_warn("Keyboard brightness level control not supported\n");
	वापस 0;
पूर्ण

अटल पूर्णांक kbd_led_level_set(काष्ठा led_classdev *led_cdev,
			     क्रमागत led_brightness value)
अणु
	क्रमागत led_brightness new_value = value;
	काष्ठा kbd_state state;
	काष्ठा kbd_state new_state;
	u16 num;
	पूर्णांक ret;

	mutex_lock(&kbd_led_mutex);

	अगर (kbd_get_max_level()) अणु
		ret = kbd_get_state(&state);
		अगर (ret)
			जाओ out;
		new_state = state;
		ret = kbd_set_level(&new_state, value);
		अगर (ret)
			जाओ out;
		ret = kbd_set_state_safe(&new_state, &state);
	पूर्ण अन्यथा अगर (kbd_get_valid_token_counts()) अणु
		क्रम (num = kbd_token_bits; num != 0 && value > 0; --value)
			num &= num - 1; /* clear the first bit set */
		अगर (num == 0)
			ret = 0;
		अन्यथा
			ret = kbd_set_token_bit(ffs(num) - 1);
	पूर्ण अन्यथा अणु
		pr_warn("Keyboard brightness level control not supported\n");
		ret = -ENXIO;
	पूर्ण

out:
	अगर (ret == 0)
		kbd_led_level = new_value;

	mutex_unlock(&kbd_led_mutex);
	वापस ret;
पूर्ण

अटल काष्ठा led_classdev kbd_led = अणु
	.name           = "dell::kbd_backlight",
	.flags		= LED_BRIGHT_HW_CHANGED,
	.brightness_set_blocking = kbd_led_level_set,
	.brightness_get = kbd_led_level_get,
	.groups         = kbd_led_groups,
पूर्ण;

अटल पूर्णांक __init kbd_led_init(काष्ठा device *dev)
अणु
	पूर्णांक ret;

	kbd_init();
	अगर (!kbd_led_present)
		वापस -ENODEV;
	अगर (!kbd_als_supported)
		kbd_led_groups[1] = शून्य;
	kbd_led.max_brightness = kbd_get_max_level();
	अगर (!kbd_led.max_brightness) अणु
		kbd_led.max_brightness = kbd_get_valid_token_counts();
		अगर (kbd_led.max_brightness)
			kbd_led.max_brightness--;
	पूर्ण

	kbd_led_level = kbd_led_level_get(शून्य);

	ret = led_classdev_रेजिस्टर(dev, &kbd_led);
	अगर (ret)
		kbd_led_present = false;

	वापस ret;
पूर्ण

अटल व्योम brightness_set_निकास(काष्ठा led_classdev *led_cdev,
				क्रमागत led_brightness value)
अणु
	/* Don't change backlight level on निकास */
पूर्ण;

अटल व्योम kbd_led_निकास(व्योम)
अणु
	अगर (!kbd_led_present)
		वापस;
	kbd_led.brightness_set = brightness_set_निकास;
	led_classdev_unरेजिस्टर(&kbd_led);
पूर्ण

अटल पूर्णांक dell_laptop_notअगरier_call(काष्ठा notअगरier_block *nb,
				     अचिन्हित दीर्घ action, व्योम *data)
अणु
	bool changed = false;
	क्रमागत led_brightness new_kbd_led_level;

	चयन (action) अणु
	हाल DELL_LAPTOP_KBD_BACKLIGHT_BRIGHTNESS_CHANGED:
		अगर (!kbd_led_present)
			अवरोध;

		mutex_lock(&kbd_led_mutex);
		new_kbd_led_level = kbd_led_level_get(&kbd_led);
		अगर (kbd_led_level != new_kbd_led_level) अणु
			kbd_led_level = new_kbd_led_level;
			changed = true;
		पूर्ण
		mutex_unlock(&kbd_led_mutex);

		अगर (changed)
			led_classdev_notअगरy_brightness_hw_changed(&kbd_led,
								kbd_led_level);
		अवरोध;
	पूर्ण

	वापस NOTIFY_OK;
पूर्ण

अटल काष्ठा notअगरier_block dell_laptop_notअगरier = अणु
	.notअगरier_call = dell_laptop_notअगरier_call,
पूर्ण;

अटल पूर्णांक micmute_led_set(काष्ठा led_classdev *led_cdev,
			   क्रमागत led_brightness brightness)
अणु
	काष्ठा calling_पूर्णांकerface_buffer buffer;
	काष्ठा calling_पूर्णांकerface_token *token;
	पूर्णांक state = brightness != LED_OFF;

	अगर (state == 0)
		token = dell_smbios_find_token(GLOBAL_MIC_MUTE_DISABLE);
	अन्यथा
		token = dell_smbios_find_token(GLOBAL_MIC_MUTE_ENABLE);

	अगर (!token)
		वापस -ENODEV;

	dell_fill_request(&buffer, token->location, token->value, 0, 0);
	dell_send_request(&buffer, CLASS_TOKEN_WRITE, SELECT_TOKEN_STD);

	वापस 0;
पूर्ण

अटल काष्ठा led_classdev micmute_led_cdev = अणु
	.name = "platform::micmute",
	.max_brightness = 1,
	.brightness_set_blocking = micmute_led_set,
	.शेष_trigger = "audio-micmute",
पूर्ण;

अटल पूर्णांक __init dell_init(व्योम)
अणु
	काष्ठा calling_पूर्णांकerface_token *token;
	पूर्णांक max_पूर्णांकensity = 0;
	पूर्णांक ret;

	अगर (!dmi_check_प्रणाली(dell_device_table))
		वापस -ENODEV;

	quirks = शून्य;
	/* find अगर this machine support other functions */
	dmi_check_प्रणाली(dell_quirks);

	ret = platक्रमm_driver_रेजिस्टर(&platक्रमm_driver);
	अगर (ret)
		जाओ fail_platक्रमm_driver;
	platक्रमm_device = platक्रमm_device_alloc("dell-laptop", -1);
	अगर (!platक्रमm_device) अणु
		ret = -ENOMEM;
		जाओ fail_platक्रमm_device1;
	पूर्ण
	ret = platक्रमm_device_add(platक्रमm_device);
	अगर (ret)
		जाओ fail_platक्रमm_device2;

	ret = dell_setup_rfसमाप्त();

	अगर (ret) अणु
		pr_warn("Unable to setup rfkill\n");
		जाओ fail_rfसमाप्त;
	पूर्ण

	अगर (quirks && quirks->touchpad_led)
		touchpad_led_init(&platक्रमm_device->dev);

	kbd_led_init(&platक्रमm_device->dev);

	dell_laptop_dir = debugfs_create_dir("dell_laptop", शून्य);
	debugfs_create_file("rfkill", 0444, dell_laptop_dir, शून्य,
			    &dell_debugfs_fops);

	dell_laptop_रेजिस्टर_notअगरier(&dell_laptop_notअगरier);

	अगर (dell_smbios_find_token(GLOBAL_MIC_MUTE_DISABLE) &&
	    dell_smbios_find_token(GLOBAL_MIC_MUTE_ENABLE)) अणु
		micmute_led_cdev.brightness = ledtrig_audio_get(LED_AUDIO_MICMUTE);
		ret = led_classdev_रेजिस्टर(&platक्रमm_device->dev, &micmute_led_cdev);
		अगर (ret < 0)
			जाओ fail_led;
	पूर्ण

	अगर (acpi_video_get_backlight_type() != acpi_backlight_venकरोr)
		वापस 0;

	token = dell_smbios_find_token(BRIGHTNESS_TOKEN);
	अगर (token) अणु
		काष्ठा calling_पूर्णांकerface_buffer buffer;

		dell_fill_request(&buffer, token->location, 0, 0, 0);
		ret = dell_send_request(&buffer,
					CLASS_TOKEN_READ, SELECT_TOKEN_AC);
		अगर (ret == 0)
			max_पूर्णांकensity = buffer.output[3];
	पूर्ण

	अगर (max_पूर्णांकensity) अणु
		काष्ठा backlight_properties props;
		स_रखो(&props, 0, माप(काष्ठा backlight_properties));
		props.type = BACKLIGHT_PLATFORM;
		props.max_brightness = max_पूर्णांकensity;
		dell_backlight_device = backlight_device_रेजिस्टर("dell_backlight",
								  &platक्रमm_device->dev,
								  शून्य,
								  &dell_ops,
								  &props);

		अगर (IS_ERR(dell_backlight_device)) अणु
			ret = PTR_ERR(dell_backlight_device);
			dell_backlight_device = शून्य;
			जाओ fail_backlight;
		पूर्ण

		dell_backlight_device->props.brightness =
			dell_get_पूर्णांकensity(dell_backlight_device);
		अगर (dell_backlight_device->props.brightness < 0) अणु
			ret = dell_backlight_device->props.brightness;
			जाओ fail_get_brightness;
		पूर्ण
		backlight_update_status(dell_backlight_device);
	पूर्ण

	वापस 0;

fail_get_brightness:
	backlight_device_unरेजिस्टर(dell_backlight_device);
fail_backlight:
	led_classdev_unरेजिस्टर(&micmute_led_cdev);
fail_led:
	dell_cleanup_rfसमाप्त();
fail_rfसमाप्त:
	platक्रमm_device_del(platक्रमm_device);
fail_platक्रमm_device2:
	platक्रमm_device_put(platक्रमm_device);
fail_platक्रमm_device1:
	platक्रमm_driver_unरेजिस्टर(&platक्रमm_driver);
fail_platक्रमm_driver:
	वापस ret;
पूर्ण

अटल व्योम __निकास dell_निकास(व्योम)
अणु
	dell_laptop_unरेजिस्टर_notअगरier(&dell_laptop_notअगरier);
	debugfs_हटाओ_recursive(dell_laptop_dir);
	अगर (quirks && quirks->touchpad_led)
		touchpad_led_निकास();
	kbd_led_निकास();
	backlight_device_unरेजिस्टर(dell_backlight_device);
	led_classdev_unरेजिस्टर(&micmute_led_cdev);
	dell_cleanup_rfसमाप्त();
	अगर (platक्रमm_device) अणु
		platक्रमm_device_unरेजिस्टर(platक्रमm_device);
		platक्रमm_driver_unरेजिस्टर(&platक्रमm_driver);
	पूर्ण
पूर्ण

/* dell-rbtn.c driver export functions which will not work correctly (and could
 * cause kernel crash) अगर they are called beक्रमe dell-rbtn.c init code. This is
 * not problem when dell-rbtn.c is compiled as बाह्यal module. When both files
 * (dell-rbtn.c and dell-laptop.c) are compiled अटलally पूर्णांकo kernel, then we
 * need to ensure that dell_init() will be called after initializing dell-rbtn.
 * This can be achieved by late_initcall() instead module_init().
 */
late_initcall(dell_init);
module_निकास(dell_निकास);

MODULE_AUTHOR("Matthew Garrett <mjg@redhat.com>");
MODULE_AUTHOR("Gabriele Mazzotta <gabriele.mzt@gmail.com>");
MODULE_AUTHOR("Pali Rohथँr <pali@kernel.org>");
MODULE_DESCRIPTION("Dell laptop driver");
MODULE_LICENSE("GPL");
