<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Asus Notebooks WMI hotkey driver
 *
 * Copyright(C) 2010 Corentin Chary <corentin.अक्षरy@gmail.com>
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/input.h>
#समावेश <linux/input/sparse-keymap.h>
#समावेश <linux/fb.h>
#समावेश <linux/dmi.h>
#समावेश <linux/i8042.h>

#समावेश "asus-wmi.h"

#घोषणा	ASUS_NB_WMI_खाता	"asus-nb-wmi"

MODULE_AUTHOR("Corentin Chary <corentin.chary@gmail.com>");
MODULE_DESCRIPTION("Asus Notebooks WMI Hotkey Driver");
MODULE_LICENSE("GPL");

#घोषणा ASUS_NB_WMI_EVENT_GUID	"0B3CBB35-E3C2-45ED-91C2-4C5A6D195D1C"

MODULE_ALIAS("wmi:"ASUS_NB_WMI_EVENT_GUID);

/*
 * WAPF defines the behavior of the Fn+Fx wlan key
 * The signअगरicance of values is yet to be found, but
 * most of the समय:
 * Bit | Bluetooth | WLAN
 *  0  | Hardware  | Hardware
 *  1  | Hardware  | Software
 *  4  | Software  | Software
 */
अटल पूर्णांक wapf = -1;
module_param(wapf, uपूर्णांक, 0444);
MODULE_PARM_DESC(wapf, "WAPF value");

अटल काष्ठा quirk_entry *quirks;

अटल bool asus_q500a_i8042_filter(अचिन्हित अक्षर data, अचिन्हित अक्षर str,
			      काष्ठा serio *port)
अणु
	अटल bool extended;
	bool ret = false;

	अगर (str & I8042_STR_AUXDATA)
		वापस false;

	अगर (unlikely(data == 0xe1)) अणु
		extended = true;
		ret = true;
	पूर्ण अन्यथा अगर (unlikely(extended)) अणु
		extended = false;
		ret = true;
	पूर्ण

	वापस ret;
पूर्ण

अटल काष्ठा quirk_entry quirk_asus_unknown = अणु
	.wapf = 0,
	.wmi_backlight_set_devstate = true,
पूर्ण;

अटल काष्ठा quirk_entry quirk_asus_q500a = अणु
	.i8042_filter = asus_q500a_i8042_filter,
	.wmi_backlight_set_devstate = true,
पूर्ण;

/*
 * For those machines that need software to control bt/wअगरi status
 * and can't adjust brightness through ACPI पूर्णांकerface
 * and have duplicate events(ACPI and WMI) क्रम display toggle
 */
अटल काष्ठा quirk_entry quirk_asus_x55u = अणु
	.wapf = 4,
	.wmi_backlight_घातer = true,
	.wmi_backlight_set_devstate = true,
	.no_display_toggle = true,
पूर्ण;

अटल काष्ठा quirk_entry quirk_asus_wapf4 = अणु
	.wapf = 4,
	.wmi_backlight_set_devstate = true,
पूर्ण;

अटल काष्ठा quirk_entry quirk_asus_x200ca = अणु
	.wapf = 2,
	.wmi_backlight_set_devstate = true,
पूर्ण;

अटल काष्ठा quirk_entry quirk_asus_ux303ub = अणु
	.wmi_backlight_native = true,
	.wmi_backlight_set_devstate = true,
पूर्ण;

अटल काष्ठा quirk_entry quirk_asus_x550lb = अणु
	.wmi_backlight_set_devstate = true,
	.xusb2pr = 0x01D9,
पूर्ण;

अटल काष्ठा quirk_entry quirk_asus_क्रमceals = अणु
	.wmi_backlight_set_devstate = true,
	.wmi_क्रमce_als_set = true,
पूर्ण;

अटल काष्ठा quirk_entry quirk_asus_venकरोr_backlight = अणु
	.wmi_backlight_घातer = true,
	.wmi_backlight_set_devstate = true,
पूर्ण;

अटल काष्ठा quirk_entry quirk_asus_use_kbd_करोck_devid = अणु
	.use_kbd_करोck_devid = true,
पूर्ण;

अटल काष्ठा quirk_entry quirk_asus_use_lid_flip_devid = अणु
	.wmi_backlight_set_devstate = true,
	.use_lid_flip_devid = true,
पूर्ण;

अटल पूर्णांक dmi_matched(स्थिर काष्ठा dmi_प्रणाली_id *dmi)
अणु
	pr_info("Identified laptop model '%s'\n", dmi->ident);
	quirks = dmi->driver_data;
	वापस 1;
पूर्ण

अटल स्थिर काष्ठा dmi_प्रणाली_id asus_quirks[] = अणु
	अणु
		.callback = dmi_matched,
		.ident = "ASUSTeK COMPUTER INC. Q500A",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "ASUSTeK COMPUTER INC."),
			DMI_MATCH(DMI_PRODUCT_NAME, "Q500A"),
		पूर्ण,
		.driver_data = &quirk_asus_q500a,
	पूर्ण,
	अणु
		.callback = dmi_matched,
		.ident = "ASUSTeK COMPUTER INC. U32U",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "ASUSTeK Computer Inc."),
			DMI_MATCH(DMI_PRODUCT_NAME, "U32U"),
		पूर्ण,
		/*
		 * Note this machine has a Brazos APU, and most Brazos Asus
		 * machines need quirk_asus_x55u / wmi_backlight_घातer but
		 * here acpi-video seems to work fine क्रम backlight control.
		 */
		.driver_data = &quirk_asus_wapf4,
	पूर्ण,
	अणु
		.callback = dmi_matched,
		.ident = "ASUSTeK COMPUTER INC. X302UA",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "ASUSTeK COMPUTER INC."),
			DMI_MATCH(DMI_PRODUCT_NAME, "X302UA"),
		पूर्ण,
		.driver_data = &quirk_asus_wapf4,
	पूर्ण,
	अणु
		.callback = dmi_matched,
		.ident = "ASUSTeK COMPUTER INC. X401U",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "ASUSTeK COMPUTER INC."),
			DMI_MATCH(DMI_PRODUCT_NAME, "X401U"),
		पूर्ण,
		.driver_data = &quirk_asus_x55u,
	पूर्ण,
	अणु
		.callback = dmi_matched,
		.ident = "ASUSTeK COMPUTER INC. X401A",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "ASUSTeK COMPUTER INC."),
			DMI_MATCH(DMI_PRODUCT_NAME, "X401A"),
		पूर्ण,
		.driver_data = &quirk_asus_wapf4,
	पूर्ण,
	अणु
		.callback = dmi_matched,
		.ident = "ASUSTeK COMPUTER INC. X401A1",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "ASUSTeK COMPUTER INC."),
			DMI_MATCH(DMI_PRODUCT_NAME, "X401A1"),
		पूर्ण,
		.driver_data = &quirk_asus_wapf4,
	पूर्ण,
	अणु
		.callback = dmi_matched,
		.ident = "ASUSTeK COMPUTER INC. X45U",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "ASUSTeK COMPUTER INC."),
			DMI_MATCH(DMI_PRODUCT_NAME, "X45U"),
		पूर्ण,
		.driver_data = &quirk_asus_wapf4,
	पूर्ण,
	अणु
		.callback = dmi_matched,
		.ident = "ASUSTeK COMPUTER INC. X456UA",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "ASUSTeK COMPUTER INC."),
			DMI_MATCH(DMI_PRODUCT_NAME, "X456UA"),
		पूर्ण,
		.driver_data = &quirk_asus_wapf4,
	पूर्ण,
	अणु
		.callback = dmi_matched,
		.ident = "ASUSTeK COMPUTER INC. X456UF",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "ASUSTeK COMPUTER INC."),
			DMI_MATCH(DMI_PRODUCT_NAME, "X456UF"),
		पूर्ण,
		.driver_data = &quirk_asus_wapf4,
	पूर्ण,
	अणु
		.callback = dmi_matched,
		.ident = "ASUSTeK COMPUTER INC. X501U",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "ASUSTeK COMPUTER INC."),
			DMI_MATCH(DMI_PRODUCT_NAME, "X501U"),
		पूर्ण,
		.driver_data = &quirk_asus_x55u,
	पूर्ण,
	अणु
		.callback = dmi_matched,
		.ident = "ASUSTeK COMPUTER INC. X501A",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "ASUSTeK COMPUTER INC."),
			DMI_MATCH(DMI_PRODUCT_NAME, "X501A"),
		पूर्ण,
		.driver_data = &quirk_asus_wapf4,
	पूर्ण,
	अणु
		.callback = dmi_matched,
		.ident = "ASUSTeK COMPUTER INC. X501A1",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "ASUSTeK COMPUTER INC."),
			DMI_MATCH(DMI_PRODUCT_NAME, "X501A1"),
		पूर्ण,
		.driver_data = &quirk_asus_wapf4,
	पूर्ण,
	अणु
		.callback = dmi_matched,
		.ident = "ASUSTeK COMPUTER INC. X550CA",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "ASUSTeK COMPUTER INC."),
			DMI_MATCH(DMI_PRODUCT_NAME, "X550CA"),
		पूर्ण,
		.driver_data = &quirk_asus_wapf4,
	पूर्ण,
	अणु
		.callback = dmi_matched,
		.ident = "ASUSTeK COMPUTER INC. X550CC",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "ASUSTeK COMPUTER INC."),
			DMI_MATCH(DMI_PRODUCT_NAME, "X550CC"),
		पूर्ण,
		.driver_data = &quirk_asus_wapf4,
	पूर्ण,
	अणु
		.callback = dmi_matched,
		.ident = "ASUSTeK COMPUTER INC. X550CL",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "ASUSTeK COMPUTER INC."),
			DMI_MATCH(DMI_PRODUCT_NAME, "X550CL"),
		पूर्ण,
		.driver_data = &quirk_asus_wapf4,
	पूर्ण,
	अणु
		.callback = dmi_matched,
		.ident = "ASUSTeK COMPUTER INC. X550VB",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "ASUSTeK COMPUTER INC."),
			DMI_MATCH(DMI_PRODUCT_NAME, "X550VB"),
		पूर्ण,
		.driver_data = &quirk_asus_wapf4,
	पूर्ण,
	अणु
		.callback = dmi_matched,
		.ident = "ASUSTeK COMPUTER INC. X551CA",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "ASUSTeK COMPUTER INC."),
			DMI_MATCH(DMI_PRODUCT_NAME, "X551CA"),
		पूर्ण,
		.driver_data = &quirk_asus_wapf4,
	पूर्ण,
	अणु
		.callback = dmi_matched,
		.ident = "ASUSTeK COMPUTER INC. X55A",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "ASUSTeK COMPUTER INC."),
			DMI_MATCH(DMI_PRODUCT_NAME, "X55A"),
		पूर्ण,
		.driver_data = &quirk_asus_wapf4,
	पूर्ण,
	अणु
		.callback = dmi_matched,
		.ident = "ASUSTeK COMPUTER INC. X55C",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "ASUSTeK COMPUTER INC."),
			DMI_MATCH(DMI_PRODUCT_NAME, "X55C"),
		पूर्ण,
		.driver_data = &quirk_asus_wapf4,
	पूर्ण,
	अणु
		.callback = dmi_matched,
		.ident = "ASUSTeK COMPUTER INC. X55U",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "ASUSTeK COMPUTER INC."),
			DMI_MATCH(DMI_PRODUCT_NAME, "X55U"),
		पूर्ण,
		.driver_data = &quirk_asus_x55u,
	पूर्ण,
	अणु
		.callback = dmi_matched,
		.ident = "ASUSTeK COMPUTER INC. X55VD",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "ASUSTeK COMPUTER INC."),
			DMI_MATCH(DMI_PRODUCT_NAME, "X55VD"),
		पूर्ण,
		.driver_data = &quirk_asus_wapf4,
	पूर्ण,
	अणु
		.callback = dmi_matched,
		.ident = "ASUSTeK COMPUTER INC. X75A",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "ASUSTeK COMPUTER INC."),
			DMI_MATCH(DMI_PRODUCT_NAME, "X75A"),
		पूर्ण,
		.driver_data = &quirk_asus_wapf4,
	पूर्ण,
	अणु
		.callback = dmi_matched,
		.ident = "ASUSTeK COMPUTER INC. X75VBP",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "ASUSTeK COMPUTER INC."),
			DMI_MATCH(DMI_PRODUCT_NAME, "X75VBP"),
		पूर्ण,
		.driver_data = &quirk_asus_wapf4,
	पूर्ण,
	अणु
		.callback = dmi_matched,
		.ident = "ASUSTeK COMPUTER INC. X75VD",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "ASUSTeK COMPUTER INC."),
			DMI_MATCH(DMI_PRODUCT_NAME, "X75VD"),
		पूर्ण,
		.driver_data = &quirk_asus_wapf4,
	पूर्ण,
	अणु
		.callback = dmi_matched,
		.ident = "ASUSTeK COMPUTER INC. 1015E",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "ASUSTeK COMPUTER INC."),
			DMI_MATCH(DMI_PRODUCT_NAME, "1015E"),
		पूर्ण,
		.driver_data = &quirk_asus_wapf4,
	पूर्ण,
	अणु
		.callback = dmi_matched,
		.ident = "ASUSTeK COMPUTER INC. 1015U",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "ASUSTeK COMPUTER INC."),
			DMI_MATCH(DMI_PRODUCT_NAME, "1015U"),
		पूर्ण,
		.driver_data = &quirk_asus_wapf4,
	पूर्ण,
	अणु
		.callback = dmi_matched,
		.ident = "ASUSTeK COMPUTER INC. X200CA",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "ASUSTeK COMPUTER INC."),
			DMI_MATCH(DMI_PRODUCT_NAME, "X200CA"),
		पूर्ण,
		.driver_data = &quirk_asus_x200ca,
	पूर्ण,
	अणु
		.callback = dmi_matched,
		.ident = "ASUSTeK COMPUTER INC. UX303UB",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "ASUSTeK COMPUTER INC."),
			DMI_MATCH(DMI_PRODUCT_NAME, "UX303UB"),
		पूर्ण,
		.driver_data = &quirk_asus_ux303ub,
	पूर्ण,
	अणु
		.callback = dmi_matched,
		.ident = "ASUSTeK COMPUTER INC. UX330UAK",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "ASUSTeK COMPUTER INC."),
			DMI_MATCH(DMI_PRODUCT_NAME, "UX330UAK"),
		पूर्ण,
		.driver_data = &quirk_asus_क्रमceals,
	पूर्ण,
	अणु
		.callback = dmi_matched,
		.ident = "ASUSTeK COMPUTER INC. X550LB",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "ASUSTeK COMPUTER INC."),
			DMI_MATCH(DMI_PRODUCT_NAME, "X550LB"),
		पूर्ण,
		.driver_data = &quirk_asus_x550lb,
	पूर्ण,
	अणु
		.callback = dmi_matched,
		.ident = "ASUSTeK COMPUTER INC. UX430UQ",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "ASUSTeK COMPUTER INC."),
			DMI_MATCH(DMI_PRODUCT_NAME, "UX430UQ"),
		पूर्ण,
		.driver_data = &quirk_asus_क्रमceals,
	पूर्ण,
	अणु
		.callback = dmi_matched,
		.ident = "ASUSTeK COMPUTER INC. UX430UNR",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "ASUSTeK COMPUTER INC."),
			DMI_MATCH(DMI_PRODUCT_NAME, "UX430UNR"),
		पूर्ण,
		.driver_data = &quirk_asus_क्रमceals,
	पूर्ण,
	अणु
		.callback = dmi_matched,
		.ident = "ASUSTeK COMPUTER INC. GA401IH",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "ASUSTeK COMPUTER INC."),
			DMI_MATCH(DMI_PRODUCT_NAME, "GA401IH"),
		पूर्ण,
		.driver_data = &quirk_asus_venकरोr_backlight,
	पूर्ण,
	अणु
		.callback = dmi_matched,
		.ident = "ASUSTeK COMPUTER INC. GA401II",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "ASUSTeK COMPUTER INC."),
			DMI_MATCH(DMI_PRODUCT_NAME, "GA401II"),
		पूर्ण,
		.driver_data = &quirk_asus_venकरोr_backlight,
	पूर्ण,
	अणु
		.callback = dmi_matched,
		.ident = "ASUSTeK COMPUTER INC. GA401IU",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "ASUSTeK COMPUTER INC."),
			DMI_MATCH(DMI_PRODUCT_NAME, "GA401IU"),
		पूर्ण,
		.driver_data = &quirk_asus_venकरोr_backlight,
	पूर्ण,
	अणु
		.callback = dmi_matched,
		.ident = "ASUSTeK COMPUTER INC. GA401IV",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "ASUSTeK COMPUTER INC."),
			DMI_MATCH(DMI_PRODUCT_NAME, "GA401IV"),
		पूर्ण,
		.driver_data = &quirk_asus_venकरोr_backlight,
	पूर्ण,
	अणु
		.callback = dmi_matched,
		.ident = "ASUSTeK COMPUTER INC. GA401IVC",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "ASUSTeK COMPUTER INC."),
			DMI_MATCH(DMI_PRODUCT_NAME, "GA401IVC"),
		पूर्ण,
		.driver_data = &quirk_asus_venकरोr_backlight,
	पूर्ण,
		अणु
		.callback = dmi_matched,
		.ident = "ASUSTeK COMPUTER INC. GA502II",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "ASUSTeK COMPUTER INC."),
			DMI_MATCH(DMI_PRODUCT_NAME, "GA502II"),
		पूर्ण,
		.driver_data = &quirk_asus_venकरोr_backlight,
	पूर्ण,
	अणु
		.callback = dmi_matched,
		.ident = "ASUSTeK COMPUTER INC. GA502IU",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "ASUSTeK COMPUTER INC."),
			DMI_MATCH(DMI_PRODUCT_NAME, "GA502IU"),
		पूर्ण,
		.driver_data = &quirk_asus_venकरोr_backlight,
	पूर्ण,
	अणु
		.callback = dmi_matched,
		.ident = "ASUSTeK COMPUTER INC. GA502IV",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "ASUSTeK COMPUTER INC."),
			DMI_MATCH(DMI_PRODUCT_NAME, "GA502IV"),
		पूर्ण,
		.driver_data = &quirk_asus_venकरोr_backlight,
	पूर्ण,
	अणु
		.callback = dmi_matched,
		.ident = "Asus Transformer T100TA / T100HA / T100CHI",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "ASUSTeK COMPUTER INC."),
			/* Match *T100* */
			DMI_MATCH(DMI_PRODUCT_NAME, "T100"),
		पूर्ण,
		.driver_data = &quirk_asus_use_kbd_करोck_devid,
	पूर्ण,
	अणु
		.callback = dmi_matched,
		.ident = "Asus Transformer T101HA",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "ASUSTeK COMPUTER INC."),
			DMI_MATCH(DMI_PRODUCT_NAME, "T101HA"),
		पूर्ण,
		.driver_data = &quirk_asus_use_kbd_करोck_devid,
	पूर्ण,
	अणु
		.callback = dmi_matched,
		.ident = "Asus Transformer T200TA",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "ASUSTeK COMPUTER INC."),
			DMI_MATCH(DMI_PRODUCT_NAME, "T200TA"),
		पूर्ण,
		.driver_data = &quirk_asus_use_kbd_करोck_devid,
	पूर्ण,
	अणु
		.callback = dmi_matched,
		.ident = "ASUS ZenBook Flip UX360",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "ASUSTeK COMPUTER INC."),
			/* Match UX360* */
			DMI_MATCH(DMI_PRODUCT_NAME, "UX360"),
		पूर्ण,
		.driver_data = &quirk_asus_use_lid_flip_devid,
	पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल व्योम asus_nb_wmi_quirks(काष्ठा asus_wmi_driver *driver)
अणु
	पूर्णांक ret;

	quirks = &quirk_asus_unknown;
	dmi_check_प्रणाली(asus_quirks);

	driver->quirks = quirks;
	driver->panel_घातer = FB_BLANK_UNBLANK;

	/* overग_लिखो the wapf setting अगर the wapf paramater is specअगरied */
	अगर (wapf != -1)
		quirks->wapf = wapf;
	अन्यथा
		wapf = quirks->wapf;

	अगर (quirks->i8042_filter) अणु
		ret = i8042_install_filter(quirks->i8042_filter);
		अगर (ret) अणु
			pr_warn("Unable to install key filter\n");
			वापस;
		पूर्ण
		pr_info("Using i8042 filter function for receiving events\n");
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा key_entry asus_nb_wmi_keymap[] = अणु
	अणु KE_KEY, ASUS_WMI_BRN_DOWN, अणु KEY_BRIGHTNESSDOWN पूर्ण पूर्ण,
	अणु KE_KEY, ASUS_WMI_BRN_UP, अणु KEY_BRIGHTNESSUP पूर्ण पूर्ण,
	अणु KE_KEY, 0x30, अणु KEY_VOLUMEUP पूर्ण पूर्ण,
	अणु KE_KEY, 0x31, अणु KEY_VOLUMEDOWN पूर्ण पूर्ण,
	अणु KE_KEY, 0x32, अणु KEY_MUTE पूर्ण पूर्ण,
	अणु KE_KEY, 0x35, अणु KEY_SCREENLOCK पूर्ण पूर्ण,
	अणु KE_KEY, 0x40, अणु KEY_PREVIOUSSONG पूर्ण पूर्ण,
	अणु KE_KEY, 0x41, अणु KEY_NEXTSONG पूर्ण पूर्ण,
	अणु KE_KEY, 0x43, अणु KEY_STOPCD पूर्ण पूर्ण, /* Stop/Eject */
	अणु KE_KEY, 0x45, अणु KEY_PLAYPAUSE पूर्ण पूर्ण,
	अणु KE_KEY, 0x4c, अणु KEY_MEDIA पूर्ण पूर्ण, /* WMP Key */
	अणु KE_KEY, 0x50, अणु KEY_EMAIL पूर्ण पूर्ण,
	अणु KE_KEY, 0x51, अणु KEY_WWW पूर्ण पूर्ण,
	अणु KE_KEY, 0x55, अणु KEY_CALC पूर्ण पूर्ण,
	अणु KE_IGNORE, 0x57, पूर्ण,  /* Battery mode */
	अणु KE_IGNORE, 0x58, पूर्ण,  /* AC mode */
	अणु KE_KEY, 0x5C, अणु KEY_F15 पूर्ण पूर्ण,  /* Power Gear key */
	अणु KE_KEY, 0x5D, अणु KEY_WLAN पूर्ण पूर्ण, /* Wireless console Toggle */
	अणु KE_KEY, 0x5E, अणु KEY_WLAN पूर्ण पूर्ण, /* Wireless console Enable */
	अणु KE_KEY, 0x5F, अणु KEY_WLAN पूर्ण पूर्ण, /* Wireless console Disable */
	अणु KE_KEY, 0x60, अणु KEY_TOUCHPAD_ON पूर्ण पूर्ण,
	अणु KE_KEY, 0x61, अणु KEY_SWITCHVIDEOMODE पूर्ण पूर्ण, /* SDSP LCD only */
	अणु KE_KEY, 0x62, अणु KEY_SWITCHVIDEOMODE पूर्ण पूर्ण, /* SDSP CRT only */
	अणु KE_KEY, 0x63, अणु KEY_SWITCHVIDEOMODE पूर्ण पूर्ण, /* SDSP LCD + CRT */
	अणु KE_KEY, 0x64, अणु KEY_SWITCHVIDEOMODE पूर्ण पूर्ण, /* SDSP TV */
	अणु KE_KEY, 0x65, अणु KEY_SWITCHVIDEOMODE पूर्ण पूर्ण, /* SDSP LCD + TV */
	अणु KE_KEY, 0x66, अणु KEY_SWITCHVIDEOMODE पूर्ण पूर्ण, /* SDSP CRT + TV */
	अणु KE_KEY, 0x67, अणु KEY_SWITCHVIDEOMODE पूर्ण पूर्ण, /* SDSP LCD + CRT + TV */
	अणु KE_KEY, 0x6B, अणु KEY_TOUCHPAD_TOGGLE पूर्ण पूर्ण,
	अणु KE_IGNORE, 0x6E, पूर्ण,  /* Low Battery notअगरication */
	अणु KE_KEY, 0x71, अणु KEY_F13 पूर्ण पूर्ण, /* General-purpose button */
	अणु KE_IGNORE, 0x79, पूर्ण,  /* Charger type dectection notअगरication */
	अणु KE_KEY, 0x7a, अणु KEY_ALS_TOGGLE पूर्ण पूर्ण, /* Ambient Light Sensor Toggle */
	अणु KE_KEY, 0x7c, अणु KEY_MICMUTE पूर्ण पूर्ण,
	अणु KE_KEY, 0x7D, अणु KEY_BLUETOOTH पूर्ण पूर्ण, /* Bluetooth Enable */
	अणु KE_KEY, 0x7E, अणु KEY_BLUETOOTH पूर्ण पूर्ण, /* Bluetooth Disable */
	अणु KE_KEY, 0x82, अणु KEY_CAMERA पूर्ण पूर्ण,
	अणु KE_KEY, 0x88, अणु KEY_RFKILL  पूर्ण पूर्ण, /* Radio Toggle Key */
	अणु KE_KEY, 0x8A, अणु KEY_PROG1 पूर्ण पूर्ण, /* Color enhancement mode */
	अणु KE_KEY, 0x8C, अणु KEY_SWITCHVIDEOMODE पूर्ण पूर्ण, /* SDSP DVI only */
	अणु KE_KEY, 0x8D, अणु KEY_SWITCHVIDEOMODE पूर्ण पूर्ण, /* SDSP LCD + DVI */
	अणु KE_KEY, 0x8E, अणु KEY_SWITCHVIDEOMODE पूर्ण पूर्ण, /* SDSP CRT + DVI */
	अणु KE_KEY, 0x8F, अणु KEY_SWITCHVIDEOMODE पूर्ण पूर्ण, /* SDSP TV + DVI */
	अणु KE_KEY, 0x90, अणु KEY_SWITCHVIDEOMODE पूर्ण पूर्ण, /* SDSP LCD + CRT + DVI */
	अणु KE_KEY, 0x91, अणु KEY_SWITCHVIDEOMODE पूर्ण पूर्ण, /* SDSP LCD + TV + DVI */
	अणु KE_KEY, 0x92, अणु KEY_SWITCHVIDEOMODE पूर्ण पूर्ण, /* SDSP CRT + TV + DVI */
	अणु KE_KEY, 0x93, अणु KEY_SWITCHVIDEOMODE पूर्ण पूर्ण, /* SDSP LCD + CRT + TV + DVI */
	अणु KE_KEY, 0x95, अणु KEY_MEDIA पूर्ण पूर्ण,
	अणु KE_KEY, 0x99, अणु KEY_PHONE पूर्ण पूर्ण, /* Conflicts with fan mode चयन */
	अणु KE_KEY, 0xA0, अणु KEY_SWITCHVIDEOMODE पूर्ण पूर्ण, /* SDSP HDMI only */
	अणु KE_KEY, 0xA1, अणु KEY_SWITCHVIDEOMODE पूर्ण पूर्ण, /* SDSP LCD + HDMI */
	अणु KE_KEY, 0xA2, अणु KEY_SWITCHVIDEOMODE पूर्ण पूर्ण, /* SDSP CRT + HDMI */
	अणु KE_KEY, 0xA3, अणु KEY_SWITCHVIDEOMODE पूर्ण पूर्ण, /* SDSP TV + HDMI */
	अणु KE_KEY, 0xA4, अणु KEY_SWITCHVIDEOMODE पूर्ण पूर्ण, /* SDSP LCD + CRT + HDMI */
	अणु KE_KEY, 0xA5, अणु KEY_SWITCHVIDEOMODE पूर्ण पूर्ण, /* SDSP LCD + TV + HDMI */
	अणु KE_KEY, 0xA6, अणु KEY_SWITCHVIDEOMODE पूर्ण पूर्ण, /* SDSP CRT + TV + HDMI */
	अणु KE_KEY, 0xA7, अणु KEY_SWITCHVIDEOMODE पूर्ण पूर्ण, /* SDSP LCD + CRT + TV + HDMI */
	अणु KE_KEY, 0xB5, अणु KEY_CALC पूर्ण पूर्ण,
	अणु KE_KEY, 0xC4, अणु KEY_KBDILLUMUP पूर्ण पूर्ण,
	अणु KE_KEY, 0xC5, अणु KEY_KBDILLUMDOWN पूर्ण पूर्ण,
	अणु KE_IGNORE, 0xC6, पूर्ण,  /* Ambient Light Sensor notअगरication */
	अणु KE_KEY, 0xFA, अणु KEY_PROG2 पूर्ण पूर्ण,           /* Lid flip action */
	अणु KE_END, 0पूर्ण,
पूर्ण;

अटल काष्ठा asus_wmi_driver asus_nb_wmi_driver = अणु
	.name = ASUS_NB_WMI_खाता,
	.owner = THIS_MODULE,
	.event_guid = ASUS_NB_WMI_EVENT_GUID,
	.keymap = asus_nb_wmi_keymap,
	.input_name = "Asus WMI hotkeys",
	.input_phys = ASUS_NB_WMI_खाता "/input0",
	.detect_quirks = asus_nb_wmi_quirks,
पूर्ण;


अटल पूर्णांक __init asus_nb_wmi_init(व्योम)
अणु
	वापस asus_wmi_रेजिस्टर_driver(&asus_nb_wmi_driver);
पूर्ण

अटल व्योम __निकास asus_nb_wmi_निकास(व्योम)
अणु
	asus_wmi_unरेजिस्टर_driver(&asus_nb_wmi_driver);
पूर्ण

module_init(asus_nb_wmi_init);
module_निकास(asus_nb_wmi_निकास);
