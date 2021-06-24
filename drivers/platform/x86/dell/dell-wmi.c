<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Dell WMI hotkeys
 *
 * Copyright (C) 2008 Red Hat <mjg@redhat.com>
 * Copyright (C) 2014-2015 Pali Rohथँr <pali@kernel.org>
 *
 * Portions based on wistron_btns.c:
 * Copyright (C) 2005 Miloslav Trmac <mitr@volny.cz>
 * Copyright (C) 2005 Bernhard Rosenkraenzer <bero@arklinux.org>
 * Copyright (C) 2005 Dmitry Torokhov <dtor@mail.ru>
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/types.h>
#समावेश <linux/input.h>
#समावेश <linux/input/sparse-keymap.h>
#समावेश <linux/acpi.h>
#समावेश <linux/माला.स>
#समावेश <linux/dmi.h>
#समावेश <linux/wmi.h>
#समावेश <acpi/video.h>
#समावेश "dell-smbios.h"
#समावेश "dell-wmi-descriptor.h"

MODULE_AUTHOR("Matthew Garrett <mjg@redhat.com>");
MODULE_AUTHOR("Pali Rohथँr <pali@kernel.org>");
MODULE_DESCRIPTION("Dell laptop WMI hotkeys driver");
MODULE_LICENSE("GPL");

#घोषणा DELL_EVENT_GUID "9DBB5994-A997-11DA-B012-B622A1EF5492"

अटल bool wmi_requires_smbios_request;

काष्ठा dell_wmi_priv अणु
	काष्ठा input_dev *input_dev;
	u32 पूर्णांकerface_version;
पूर्ण;

अटल पूर्णांक __init dmi_matched(स्थिर काष्ठा dmi_प्रणाली_id *dmi)
अणु
	wmi_requires_smbios_request = 1;
	वापस 1;
पूर्ण

अटल स्थिर काष्ठा dmi_प्रणाली_id dell_wmi_smbios_list[] __initस्थिर = अणु
	अणु
		.callback = dmi_matched,
		.ident = "Dell Inspiron M5110",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Dell Inc."),
			DMI_MATCH(DMI_PRODUCT_NAME, "Inspiron M5110"),
		पूर्ण,
	पूर्ण,
	अणु
		.callback = dmi_matched,
		.ident = "Dell Vostro V131",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Dell Inc."),
			DMI_MATCH(DMI_PRODUCT_NAME, "Vostro V131"),
		पूर्ण,
	पूर्ण,
	अणु पूर्ण
पूर्ण;

/*
 * Keymap क्रम WMI events of type 0x0000
 *
 * Certain keys are flagged as KE_IGNORE. All of these are either
 * notअगरications (rather than requests क्रम change) or are also sent
 * via the keyboard controller so should not be sent again.
 */
अटल स्थिर काष्ठा key_entry dell_wmi_keymap_type_0000[] = अणु
	अणु KE_IGNORE, 0x003a, अणु KEY_CAPSLOCK पूर्ण पूर्ण,

	/* Key code is followed by brightness level */
	अणु KE_KEY,    0xe005, अणु KEY_BRIGHTNESSDOWN पूर्ण पूर्ण,
	अणु KE_KEY,    0xe006, अणु KEY_BRIGHTNESSUP पूर्ण पूर्ण,

	/* Battery health status button */
	अणु KE_KEY,    0xe007, अणु KEY_BATTERY पूर्ण पूर्ण,

	/* Radio devices state change, key code is followed by other values */
	अणु KE_IGNORE, 0xe008, अणु KEY_RFKILL पूर्ण पूर्ण,

	अणु KE_KEY,    0xe009, अणु KEY_EJECTCD पूर्ण पूर्ण,

	/* Key code is followed by: next, active and attached devices */
	अणु KE_KEY,    0xe00b, अणु KEY_SWITCHVIDEOMODE पूर्ण पूर्ण,

	/* Key code is followed by keyboard illumination level */
	अणु KE_IGNORE, 0xe00c, अणु KEY_KBDILLUMTOGGLE पूर्ण पूर्ण,

	/* BIOS error detected */
	अणु KE_IGNORE, 0xe00d, अणु KEY_RESERVED पूर्ण पूर्ण,

	/* Battery was हटाओd or inserted */
	अणु KE_IGNORE, 0xe00e, अणु KEY_RESERVED पूर्ण पूर्ण,

	/* Wअगरi Catcher */
	अणु KE_KEY,    0xe011, अणु KEY_WLAN पूर्ण पूर्ण,

	/* Ambient light sensor toggle */
	अणु KE_IGNORE, 0xe013, अणु KEY_RESERVED पूर्ण पूर्ण,

	अणु KE_IGNORE, 0xe020, अणु KEY_MUTE पूर्ण पूर्ण,

	/* Unknown, defined in ACPI DSDT */
	/* अणु KE_IGNORE, 0xe023, अणु KEY_RESERVED पूर्ण पूर्ण, */

	/* Untested, Dell Instant Launch key on Inspiron 7520 */
	/* अणु KE_IGNORE, 0xe024, अणु KEY_RESERVED पूर्ण पूर्ण, */

	/* Dell Instant Launch key */
	अणु KE_KEY,    0xe025, अणु KEY_PROG4 पूर्ण पूर्ण,

	/* Audio panel key */
	अणु KE_IGNORE, 0xe026, अणु KEY_RESERVED पूर्ण पूर्ण,

	/* LCD Display On/Off Control key */
	अणु KE_KEY,    0xe027, अणु KEY_DISPLAYTOGGLE पूर्ण पूर्ण,

	/* Untested, Mulसमयdia key on Dell Vostro 3560 */
	/* अणु KE_IGNORE, 0xe028, अणु KEY_RESERVED पूर्ण पूर्ण, */

	/* Dell Instant Launch key */
	अणु KE_KEY,    0xe029, अणु KEY_PROG4 पूर्ण पूर्ण,

	/* Untested, Winकरोws Mobility Center button on Inspiron 7520 */
	/* अणु KE_IGNORE, 0xe02a, अणु KEY_RESERVED पूर्ण पूर्ण, */

	/* Unknown, defined in ACPI DSDT */
	/* अणु KE_IGNORE, 0xe02b, अणु KEY_RESERVED पूर्ण पूर्ण, */

	/* Untested, Dell Audio With Preset Switch button on Inspiron 7520 */
	/* अणु KE_IGNORE, 0xe02c, अणु KEY_RESERVED पूर्ण पूर्ण, */

	अणु KE_IGNORE, 0xe02e, अणु KEY_VOLUMEDOWN पूर्ण पूर्ण,
	अणु KE_IGNORE, 0xe030, अणु KEY_VOLUMEUP पूर्ण पूर्ण,
	अणु KE_IGNORE, 0xe033, अणु KEY_KBDILLUMUP पूर्ण पूर्ण,
	अणु KE_IGNORE, 0xe034, अणु KEY_KBDILLUMDOWN पूर्ण पूर्ण,
	अणु KE_IGNORE, 0xe03a, अणु KEY_CAPSLOCK पूर्ण पूर्ण,

	/* NIC Link is Up */
	अणु KE_IGNORE, 0xe043, अणु KEY_RESERVED पूर्ण पूर्ण,

	/* NIC Link is Down */
	अणु KE_IGNORE, 0xe044, अणु KEY_RESERVED पूर्ण पूर्ण,

	/*
	 * This entry is very suspicious!
	 * Originally Matthew Garrett created this dell-wmi driver specially क्रम
	 * "button with a picture of a battery" which has event code 0xe045.
	 * Later Mario Limonciello from Dell told us that event code 0xe045 is
	 * reported by Num Lock and should be ignored because key is send also
	 * by keyboard controller.
	 * So क्रम now we will ignore this event to prevent potential द्विगुन
	 * Num Lock key press.
	 */
	अणु KE_IGNORE, 0xe045, अणु KEY_NUMLOCK पूर्ण पूर्ण,

	/* Scroll lock and also going to tablet mode on portable devices */
	अणु KE_IGNORE, 0xe046, अणु KEY_SCROLLLOCK पूर्ण पूर्ण,

	/* Untested, going from tablet mode on portable devices */
	/* अणु KE_IGNORE, 0xe047, अणु KEY_RESERVED पूर्ण पूर्ण, */

	/* Dell Support Center key */
	अणु KE_IGNORE, 0xe06e, अणु KEY_RESERVED पूर्ण पूर्ण,

	अणु KE_IGNORE, 0xe0f7, अणु KEY_MUTE पूर्ण पूर्ण,
	अणु KE_IGNORE, 0xe0f8, अणु KEY_VOLUMEDOWN पूर्ण पूर्ण,
	अणु KE_IGNORE, 0xe0f9, अणु KEY_VOLUMEUP पूर्ण पूर्ण,
पूर्ण;

काष्ठा dell_bios_keymap_entry अणु
	u16 scancode;
	u16 keycode;
पूर्ण;

काष्ठा dell_bios_hotkey_table अणु
	काष्ठा dmi_header header;
	काष्ठा dell_bios_keymap_entry keymap[];

पूर्ण;

काष्ठा dell_dmi_results अणु
	पूर्णांक err;
	पूर्णांक keymap_size;
	काष्ठा key_entry *keymap;
पूर्ण;

/* Uninitialized entries here are KEY_RESERVED == 0. */
अटल स्थिर u16 bios_to_linux_keycode[256] = अणु
	[0]	= KEY_MEDIA,
	[1]	= KEY_NEXTSONG,
	[2]	= KEY_PLAYPAUSE,
	[3]	= KEY_PREVIOUSSONG,
	[4]	= KEY_STOPCD,
	[5]	= KEY_UNKNOWN,
	[6]	= KEY_UNKNOWN,
	[7]	= KEY_UNKNOWN,
	[8]	= KEY_WWW,
	[9]	= KEY_UNKNOWN,
	[10]	= KEY_VOLUMEDOWN,
	[11]	= KEY_MUTE,
	[12]	= KEY_VOLUMEUP,
	[13]	= KEY_UNKNOWN,
	[14]	= KEY_BATTERY,
	[15]	= KEY_EJECTCD,
	[16]	= KEY_UNKNOWN,
	[17]	= KEY_SLEEP,
	[18]	= KEY_PROG1,
	[19]	= KEY_BRIGHTNESSDOWN,
	[20]	= KEY_BRIGHTNESSUP,
	[21]	= KEY_BRIGHTNESS_AUTO,
	[22]	= KEY_KBDILLUMTOGGLE,
	[23]	= KEY_UNKNOWN,
	[24]	= KEY_SWITCHVIDEOMODE,
	[25]	= KEY_UNKNOWN,
	[26]	= KEY_UNKNOWN,
	[27]	= KEY_SWITCHVIDEOMODE,
	[28]	= KEY_UNKNOWN,
	[29]	= KEY_UNKNOWN,
	[30]	= KEY_PROG2,
	[31]	= KEY_UNKNOWN,
	[32]	= KEY_UNKNOWN,
	[33]	= KEY_UNKNOWN,
	[34]	= KEY_UNKNOWN,
	[35]	= KEY_UNKNOWN,
	[36]	= KEY_UNKNOWN,
	[37]	= KEY_UNKNOWN,
	[38]	= KEY_MICMUTE,
	[255]	= KEY_PROG3,
पूर्ण;

/*
 * Keymap क्रम WMI events of type 0x0010
 *
 * These are applied अगर the 0xB2 DMI hotkey table is present and करोesn't
 * override them.
 */
अटल स्थिर काष्ठा key_entry dell_wmi_keymap_type_0010[] = अणु
	/* Fn-lock चयनed to function keys */
	अणु KE_IGNORE, 0x0, अणु KEY_RESERVED पूर्ण पूर्ण,

	/* Fn-lock चयनed to mulसमयdia keys */
	अणु KE_IGNORE, 0x1, अणु KEY_RESERVED पूर्ण पूर्ण,

	/* Keyboard backlight change notअगरication */
	अणु KE_IGNORE, 0x3f, अणु KEY_RESERVED पूर्ण पूर्ण,

	/* Backlight brightness level */
	अणु KE_KEY,    0x57, अणु KEY_BRIGHTNESSDOWN पूर्ण पूर्ण,
	अणु KE_KEY,    0x58, अणु KEY_BRIGHTNESSUP पूर्ण पूर्ण,

	/* Mic mute */
	अणु KE_KEY, 0x150, अणु KEY_MICMUTE पूर्ण पूर्ण,

	/* Fn-lock */
	अणु KE_IGNORE, 0x151, अणु KEY_RESERVED पूर्ण पूर्ण,

	/* Change keyboard illumination */
	अणु KE_IGNORE, 0x152, अणु KEY_KBDILLUMTOGGLE पूर्ण पूर्ण,

	/*
	 * Radio disable (notअगरy only -- there is no model क्रम which the
	 * WMI event is supposed to trigger an action).
	 */
	अणु KE_IGNORE, 0x153, अणु KEY_RFKILL पूर्ण पूर्ण,

	/* RGB keyboard backlight control */
	अणु KE_IGNORE, 0x154, अणु KEY_RESERVED पूर्ण पूर्ण,

	/*
	 * Stealth mode toggle. This will "disable all lights and sounds".
	 * The action is perक्रमmed by the BIOS and EC; the WMI event is just
	 * a notअगरication. On the XPS 13 9350, this is Fn+F7, and there's
	 * a BIOS setting to enable and disable the hotkey.
	 */
	अणु KE_IGNORE, 0x155, अणु KEY_RESERVED पूर्ण पूर्ण,

	/* Rugged magnetic करोck attach/detach events */
	अणु KE_IGNORE, 0x156, अणु KEY_RESERVED पूर्ण पूर्ण,
	अणु KE_IGNORE, 0x157, अणु KEY_RESERVED पूर्ण पूर्ण,

	/* Rugged programmable (P1/P2/P3 keys) */
	अणु KE_KEY,    0x850, अणु KEY_PROG1 पूर्ण पूर्ण,
	अणु KE_KEY,    0x851, अणु KEY_PROG2 पूर्ण पूर्ण,
	अणु KE_KEY,    0x852, अणु KEY_PROG3 पूर्ण पूर्ण,

	/*
	 * Radio disable (notअगरy only -- there is no model क्रम which the
	 * WMI event is supposed to trigger an action).
	 */
	अणु KE_IGNORE, 0xe008, अणु KEY_RFKILL पूर्ण पूर्ण,

	/* Fn-lock */
	अणु KE_IGNORE, 0xe035, अणु KEY_RESERVED पूर्ण पूर्ण,
पूर्ण;

/*
 * Keymap क्रम WMI events of type 0x0011
 */
अटल स्थिर काष्ठा key_entry dell_wmi_keymap_type_0011[] = अणु
	/* Battery unplugged */
	अणु KE_IGNORE, 0xfff0, अणु KEY_RESERVED पूर्ण पूर्ण,

	/* Battery inserted */
	अणु KE_IGNORE, 0xfff1, अणु KEY_RESERVED पूर्ण पूर्ण,

	/*
	 * Detachable keyboard detached / unकरोcked
	 * Note SW_TABLET_MODE is alपढ़ोy reported through the पूर्णांकel_vbtn
	 * driver क्रम this, so we ignore it.
	 */
	अणु KE_IGNORE, 0xfff2, अणु KEY_RESERVED पूर्ण पूर्ण,

	/* Detachable keyboard attached / करोcked */
	अणु KE_IGNORE, 0xfff3, अणु KEY_RESERVED पूर्ण पूर्ण,

	/* Keyboard backlight level changed */
	अणु KE_IGNORE, KBD_LED_OFF_TOKEN,      अणु KEY_RESERVED पूर्ण पूर्ण,
	अणु KE_IGNORE, KBD_LED_ON_TOKEN,       अणु KEY_RESERVED पूर्ण पूर्ण,
	अणु KE_IGNORE, KBD_LED_AUTO_TOKEN,     अणु KEY_RESERVED पूर्ण पूर्ण,
	अणु KE_IGNORE, KBD_LED_AUTO_25_TOKEN,  अणु KEY_RESERVED पूर्ण पूर्ण,
	अणु KE_IGNORE, KBD_LED_AUTO_50_TOKEN,  अणु KEY_RESERVED पूर्ण पूर्ण,
	अणु KE_IGNORE, KBD_LED_AUTO_75_TOKEN,  अणु KEY_RESERVED पूर्ण पूर्ण,
	अणु KE_IGNORE, KBD_LED_AUTO_100_TOKEN, अणु KEY_RESERVED पूर्ण पूर्ण,
पूर्ण;

/*
 * Keymap क्रम WMI events of type 0x0012
 * They are events with extended data
 */
अटल स्थिर काष्ठा key_entry dell_wmi_keymap_type_0012[] = अणु
	/* Fn-lock button pressed */
	अणु KE_IGNORE, 0xe035, अणु KEY_RESERVED पूर्ण पूर्ण,
पूर्ण;

अटल व्योम dell_wmi_process_key(काष्ठा wmi_device *wdev, पूर्णांक type, पूर्णांक code)
अणु
	काष्ठा dell_wmi_priv *priv = dev_get_drvdata(&wdev->dev);
	स्थिर काष्ठा key_entry *key;

	key = sparse_keymap_entry_from_scancode(priv->input_dev,
						(type << 16) | code);
	अगर (!key) अणु
		pr_info("Unknown key with type 0x%04x and code 0x%04x pressed\n",
			type, code);
		वापस;
	पूर्ण

	pr_debug("Key with type 0x%04x and code 0x%04x pressed\n", type, code);

	/* Don't report brightness notअगरications that will also come via ACPI */
	अगर ((key->keycode == KEY_BRIGHTNESSUP ||
	     key->keycode == KEY_BRIGHTNESSDOWN) &&
	    acpi_video_handles_brightness_key_presses())
		वापस;

	अगर (type == 0x0000 && code == 0xe025 && !wmi_requires_smbios_request)
		वापस;

	अगर (key->keycode == KEY_KBDILLUMTOGGLE)
		dell_laptop_call_notअगरier(
			DELL_LAPTOP_KBD_BACKLIGHT_BRIGHTNESS_CHANGED, शून्य);

	sparse_keymap_report_entry(priv->input_dev, key, 1, true);
पूर्ण

अटल व्योम dell_wmi_notअगरy(काष्ठा wmi_device *wdev,
			    जोड़ acpi_object *obj)
अणु
	काष्ठा dell_wmi_priv *priv = dev_get_drvdata(&wdev->dev);
	u16 *buffer_entry, *buffer_end;
	acpi_size buffer_size;
	पूर्णांक len, i;

	अगर (obj->type != ACPI_TYPE_BUFFER) अणु
		pr_warn("bad response type %x\n", obj->type);
		वापस;
	पूर्ण

	pr_debug("Received WMI event (%*ph)\n",
		obj->buffer.length, obj->buffer.poपूर्णांकer);

	buffer_entry = (u16 *)obj->buffer.poपूर्णांकer;
	buffer_size = obj->buffer.length/2;
	buffer_end = buffer_entry + buffer_size;

	/*
	 * BIOS/ACPI on devices with WMI पूर्णांकerface version 0 करोes not clear
	 * buffer beक्रमe filling it. So next समय when BIOS/ACPI send WMI event
	 * which is smaller as previous then it contains garbage in buffer from
	 * previous event.
	 *
	 * BIOS/ACPI on devices with WMI पूर्णांकerface version 1 clears buffer and
	 * someबार send more events in buffer at one call.
	 *
	 * So to prevent पढ़ोing garbage from buffer we will process only first
	 * one event on devices with WMI पूर्णांकerface version 0.
	 */
	अगर (priv->पूर्णांकerface_version == 0 && buffer_entry < buffer_end)
		अगर (buffer_end > buffer_entry + buffer_entry[0] + 1)
			buffer_end = buffer_entry + buffer_entry[0] + 1;

	जबतक (buffer_entry < buffer_end) अणु

		len = buffer_entry[0];
		अगर (len == 0)
			अवरोध;

		len++;

		अगर (buffer_entry + len > buffer_end) अणु
			pr_warn("Invalid length of WMI event\n");
			अवरोध;
		पूर्ण

		pr_debug("Process buffer (%*ph)\n", len*2, buffer_entry);

		चयन (buffer_entry[1]) अणु
		हाल 0x0000: /* One key pressed or event occurred */
		हाल 0x0012: /* Event with extended data occurred */
			अगर (len > 2)
				dell_wmi_process_key(wdev, buffer_entry[1],
						     buffer_entry[2]);
			/* Extended data is currently ignored */
			अवरोध;
		हाल 0x0010: /* Sequence of keys pressed */
		हाल 0x0011: /* Sequence of events occurred */
			क्रम (i = 2; i < len; ++i)
				dell_wmi_process_key(wdev, buffer_entry[1],
						     buffer_entry[i]);
			अवरोध;
		शेष: /* Unknown event */
			pr_info("Unknown WMI event type 0x%x\n",
				(पूर्णांक)buffer_entry[1]);
			अवरोध;
		पूर्ण

		buffer_entry += len;

	पूर्ण

पूर्ण

अटल bool have_scancode(u32 scancode, स्थिर काष्ठा key_entry *keymap, पूर्णांक len)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < len; i++)
		अगर (keymap[i].code == scancode)
			वापस true;

	वापस false;
पूर्ण

अटल व्योम handle_dmi_entry(स्थिर काष्ठा dmi_header *dm, व्योम *opaque)
अणु
	काष्ठा dell_dmi_results *results = opaque;
	काष्ठा dell_bios_hotkey_table *table;
	पूर्णांक hotkey_num, i, pos = 0;
	काष्ठा key_entry *keymap;

	अगर (results->err || results->keymap)
		वापस;		/* We alपढ़ोy found the hotkey table. */

	/* The Dell hotkey table is type 0xB2.  Scan until we find it. */
	अगर (dm->type != 0xb2)
		वापस;

	table = container_of(dm, काष्ठा dell_bios_hotkey_table, header);

	hotkey_num = (table->header.length -
		      माप(काष्ठा dell_bios_hotkey_table)) /
				माप(काष्ठा dell_bios_keymap_entry);
	अगर (hotkey_num < 1) अणु
		/*
		 * Historically, dell-wmi would ignore a DMI entry of
		 * fewer than 7 bytes.  Sizes between 4 and 8 bytes are
		 * nonsensical (both the header and all entries are 4
		 * bytes), so we approximate the old behavior by
		 * ignoring tables with fewer than one entry.
		 */
		वापस;
	पूर्ण

	keymap = kसुस्मृति(hotkey_num, माप(काष्ठा key_entry), GFP_KERNEL);
	अगर (!keymap) अणु
		results->err = -ENOMEM;
		वापस;
	पूर्ण

	क्रम (i = 0; i < hotkey_num; i++) अणु
		स्थिर काष्ठा dell_bios_keymap_entry *bios_entry =
					&table->keymap[i];

		/* Uninitialized entries are 0 aka KEY_RESERVED. */
		u16 keycode = (bios_entry->keycode <
			       ARRAY_SIZE(bios_to_linux_keycode)) ?
			bios_to_linux_keycode[bios_entry->keycode] :
			(bios_entry->keycode == 0xffff ? KEY_UNKNOWN : KEY_RESERVED);

		/*
		 * Log अगर we find an entry in the DMI table that we करोn't
		 * understand.  If this happens, we should figure out what
		 * the entry means and add it to bios_to_linux_keycode.
		 */
		अगर (keycode == KEY_RESERVED) अणु
			pr_info("firmware scancode 0x%x maps to unrecognized keycode 0x%x\n",
				bios_entry->scancode, bios_entry->keycode);
			जारी;
		पूर्ण

		अगर (keycode == KEY_KBDILLUMTOGGLE)
			keymap[pos].type = KE_IGNORE;
		अन्यथा
			keymap[pos].type = KE_KEY;
		keymap[pos].code = bios_entry->scancode;
		keymap[pos].keycode = keycode;

		pos++;
	पूर्ण

	results->keymap = keymap;
	results->keymap_size = pos;
पूर्ण

अटल पूर्णांक dell_wmi_input_setup(काष्ठा wmi_device *wdev)
अणु
	काष्ठा dell_wmi_priv *priv = dev_get_drvdata(&wdev->dev);
	काष्ठा dell_dmi_results dmi_results = अणुपूर्ण;
	काष्ठा key_entry *keymap;
	पूर्णांक err, i, pos = 0;

	priv->input_dev = input_allocate_device();
	अगर (!priv->input_dev)
		वापस -ENOMEM;

	priv->input_dev->name = "Dell WMI hotkeys";
	priv->input_dev->id.bustype = BUS_HOST;
	priv->input_dev->dev.parent = &wdev->dev;

	अगर (dmi_walk(handle_dmi_entry, &dmi_results)) अणु
		/*
		 * Historically, dell-wmi ignored dmi_walk errors.  A failure
		 * is certainly surprising, but it probably just indicates
		 * a very old laptop.
		 */
		pr_warn("no DMI; using the old-style hotkey interface\n");
	पूर्ण

	अगर (dmi_results.err) अणु
		err = dmi_results.err;
		जाओ err_मुक्त_dev;
	पूर्ण

	keymap = kसुस्मृति(dmi_results.keymap_size +
			 ARRAY_SIZE(dell_wmi_keymap_type_0000) +
			 ARRAY_SIZE(dell_wmi_keymap_type_0010) +
			 ARRAY_SIZE(dell_wmi_keymap_type_0011) +
			 ARRAY_SIZE(dell_wmi_keymap_type_0012) +
			 1,
			 माप(काष्ठा key_entry), GFP_KERNEL);
	अगर (!keymap) अणु
		kमुक्त(dmi_results.keymap);
		err = -ENOMEM;
		जाओ err_मुक्त_dev;
	पूर्ण

	/* Append table with events of type 0x0010 which comes from DMI */
	क्रम (i = 0; i < dmi_results.keymap_size; i++) अणु
		keymap[pos] = dmi_results.keymap[i];
		keymap[pos].code |= (0x0010 << 16);
		pos++;
	पूर्ण

	kमुक्त(dmi_results.keymap);

	/* Append table with extra events of type 0x0010 which are not in DMI */
	क्रम (i = 0; i < ARRAY_SIZE(dell_wmi_keymap_type_0010); i++) अणु
		स्थिर काष्ठा key_entry *entry = &dell_wmi_keymap_type_0010[i];

		/*
		 * Check अगर we've alपढ़ोy found this scancode.  This takes
		 * quadratic समय, but it करोesn't matter unless the list
		 * of extra keys माला_लो very दीर्घ.
		 */
		अगर (dmi_results.keymap_size &&
		    have_scancode(entry->code | (0x0010 << 16),
				  keymap, dmi_results.keymap_size)
		   )
			जारी;

		keymap[pos] = *entry;
		keymap[pos].code |= (0x0010 << 16);
		pos++;
	पूर्ण

	/* Append table with events of type 0x0011 */
	क्रम (i = 0; i < ARRAY_SIZE(dell_wmi_keymap_type_0011); i++) अणु
		keymap[pos] = dell_wmi_keymap_type_0011[i];
		keymap[pos].code |= (0x0011 << 16);
		pos++;
	पूर्ण

	/* Append table with events of type 0x0012 */
	क्रम (i = 0; i < ARRAY_SIZE(dell_wmi_keymap_type_0012); i++) अणु
		keymap[pos] = dell_wmi_keymap_type_0012[i];
		keymap[pos].code |= (0x0012 << 16);
		pos++;
	पूर्ण

	/*
	 * Now append also table with "legacy" events of type 0x0000. Some of
	 * them are reported also on laptops which have scancodes in DMI.
	 */
	क्रम (i = 0; i < ARRAY_SIZE(dell_wmi_keymap_type_0000); i++) अणु
		keymap[pos] = dell_wmi_keymap_type_0000[i];
		pos++;
	पूर्ण

	keymap[pos].type = KE_END;

	err = sparse_keymap_setup(priv->input_dev, keymap, शून्य);
	/*
	 * Sparse keymap library makes a copy of keymap so we करोn't need the
	 * original one that was allocated.
	 */
	kमुक्त(keymap);
	अगर (err)
		जाओ err_मुक्त_dev;

	err = input_रेजिस्टर_device(priv->input_dev);
	अगर (err)
		जाओ err_मुक्त_dev;

	वापस 0;

 err_मुक्त_dev:
	input_मुक्त_device(priv->input_dev);
	वापस err;
पूर्ण

अटल व्योम dell_wmi_input_destroy(काष्ठा wmi_device *wdev)
अणु
	काष्ठा dell_wmi_priv *priv = dev_get_drvdata(&wdev->dev);

	input_unरेजिस्टर_device(priv->input_dev);
पूर्ण

/*
 * According to Dell SMBIOS करोcumentation:
 *
 * 17  3  Application Program Registration
 *
 *     cbArg1 Application ID 1 = 0x00010000
 *     cbArg2 Application ID 2
 *            QUICKSET/DCP = 0x51534554 "QSET"
 *            ALS Driver   = 0x416c7353 "AlsS"
 *            Latitude ON  = 0x4c6f6e52 "LonR"
 *     cbArg3 Application version or revision number
 *     cbArg4 0 = Unरेजिस्टर application
 *            1 = Register application
 *     cbRes1 Standard वापस codes (0, -1, -2)
 */

अटल पूर्णांक dell_wmi_events_set_enabled(bool enable)
अणु
	काष्ठा calling_पूर्णांकerface_buffer *buffer;
	पूर्णांक ret;

	buffer = kzalloc(माप(काष्ठा calling_पूर्णांकerface_buffer), GFP_KERNEL);
	अगर (!buffer)
		वापस -ENOMEM;
	buffer->cmd_class = CLASS_INFO;
	buffer->cmd_select = SELECT_APP_REGISTRATION;
	buffer->input[0] = 0x10000;
	buffer->input[1] = 0x51534554;
	buffer->input[3] = enable;
	ret = dell_smbios_call(buffer);
	अगर (ret == 0)
		ret = buffer->output[0];
	kमुक्त(buffer);

	वापस dell_smbios_error(ret);
पूर्ण

अटल पूर्णांक dell_wmi_probe(काष्ठा wmi_device *wdev, स्थिर व्योम *context)
अणु
	काष्ठा dell_wmi_priv *priv;
	पूर्णांक ret;

	ret = dell_wmi_get_descriptor_valid();
	अगर (ret)
		वापस ret;

	priv = devm_kzalloc(
		&wdev->dev, माप(काष्ठा dell_wmi_priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;
	dev_set_drvdata(&wdev->dev, priv);

	अगर (!dell_wmi_get_पूर्णांकerface_version(&priv->पूर्णांकerface_version))
		वापस -EPROBE_DEFER;

	वापस dell_wmi_input_setup(wdev);
पूर्ण

अटल व्योम dell_wmi_हटाओ(काष्ठा wmi_device *wdev)
अणु
	dell_wmi_input_destroy(wdev);
पूर्ण
अटल स्थिर काष्ठा wmi_device_id dell_wmi_id_table[] = अणु
	अणु .guid_string = DELL_EVENT_GUID पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल काष्ठा wmi_driver dell_wmi_driver = अणु
	.driver = अणु
		.name = "dell-wmi",
	पूर्ण,
	.id_table = dell_wmi_id_table,
	.probe = dell_wmi_probe,
	.हटाओ = dell_wmi_हटाओ,
	.notअगरy = dell_wmi_notअगरy,
पूर्ण;

अटल पूर्णांक __init dell_wmi_init(व्योम)
अणु
	पूर्णांक err;

	dmi_check_प्रणाली(dell_wmi_smbios_list);

	अगर (wmi_requires_smbios_request) अणु
		err = dell_wmi_events_set_enabled(true);
		अगर (err) अणु
			pr_err("Failed to enable WMI events\n");
			वापस err;
		पूर्ण
	पूर्ण

	वापस wmi_driver_रेजिस्टर(&dell_wmi_driver);
पूर्ण
late_initcall(dell_wmi_init);

अटल व्योम __निकास dell_wmi_निकास(व्योम)
अणु
	अगर (wmi_requires_smbios_request)
		dell_wmi_events_set_enabled(false);

	wmi_driver_unरेजिस्टर(&dell_wmi_driver);
पूर्ण
module_निकास(dell_wmi_निकास);

MODULE_DEVICE_TABLE(wmi, dell_wmi_id_table);
