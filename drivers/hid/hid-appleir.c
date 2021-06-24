<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * HID driver क्रम the apple ir device
 *
 * Original driver written by James McKenzie
 * Ported to recent 2.6 kernel versions by Greg Kroah-Harपंचांगan <gregkh@suse.de>
 * Updated to support newer remotes by Bastien Nocera <hadess@hadess.net>
 * Ported to HID subप्रणाली by Benjamin Tissoires <benjamin.tissoires@gmail.com>
 *
 * Copyright (C) 2006 James McKenzie
 * Copyright (C) 2008 Greg Kroah-Harपंचांगan <greg@kroah.com>
 * Copyright (C) 2008 Novell Inc.
 * Copyright (C) 2010, 2012 Bastien Nocera <hadess@hadess.net>
 * Copyright (C) 2013 Benjamin Tissoires <benjamin.tissoires@gmail.com>
 * Copyright (C) 2013 Red Hat Inc. All Rights Reserved
 */

#समावेश <linux/device.h>
#समावेश <linux/hid.h>
#समावेश <linux/module.h>
#समावेश "hid-ids.h"

MODULE_AUTHOR("James McKenzie");
MODULE_AUTHOR("Benjamin Tissoires <benjamin.tissoires@redhat.com>");
MODULE_DESCRIPTION("HID Apple IR remote controls");
MODULE_LICENSE("GPL");

#घोषणा KEY_MASK		0x0F
#घोषणा TWO_PACKETS_MASK	0x40

/*
 * James McKenzie has two devices both of which report the following
 * 25 87 ee 83 0a	+
 * 25 87 ee 83 0c	-
 * 25 87 ee 83 09	<<
 * 25 87 ee 83 06	>>
 * 25 87 ee 83 05	>"
 * 25 87 ee 83 03	menu
 * 26 00 00 00 00	क्रम key repeat
 */

/*
 * Thomas Glanzmann reports the following responses
 * 25 87 ee ca 0b	+
 * 25 87 ee ca 0d	-
 * 25 87 ee ca 08	<<
 * 25 87 ee ca 07	>>
 * 25 87 ee ca 04	>"
 * 25 87 ee ca 02	menu
 * 26 00 00 00 00       क्रम key repeat
 *
 * He also observes the following event someबार
 * sent after a key is release, which I पूर्णांकerpret
 * as a flat battery message
 * 25 87 e0 ca 06	flat battery
 */

/*
 * Alexandre Karpenko reports the following responses क्रम Device ID 0x8242
 * 25 87 ee 47 0b	+
 * 25 87 ee 47 0d	-
 * 25 87 ee 47 08	<<
 * 25 87 ee 47 07	>>
 * 25 87 ee 47 04	>"
 * 25 87 ee 47 02	menu
 * 26 87 ee 47 **	क्रम key repeat (** is the code of the key being held)
 */

/*
 * Bastien Nocera's remote
 * 25 87 ee 91 5f	followed by
 * 25 87 ee 91 05	gives you >"
 *
 * 25 87 ee 91 5c	followed by
 * 25 87 ee 91 05	gives you the middle button
 */

/*
 * Fabien Andre's remote
 * 25 87 ee a3 5e	followed by
 * 25 87 ee a3 04	gives you >"
 *
 * 25 87 ee a3 5d	followed by
 * 25 87 ee a3 04	gives you the middle button
 */

अटल स्थिर अचिन्हित लघु appleir_key_table[] = अणु
	KEY_RESERVED,
	KEY_MENU,
	KEY_PLAYPAUSE,
	KEY_FORWARD,
	KEY_BACK,
	KEY_VOLUMEUP,
	KEY_VOLUMEDOWN,
	KEY_RESERVED,
	KEY_RESERVED,
	KEY_RESERVED,
	KEY_RESERVED,
	KEY_RESERVED,
	KEY_RESERVED,
	KEY_RESERVED,
	KEY_ENTER,
	KEY_PLAYPAUSE,
	KEY_RESERVED,
पूर्ण;

काष्ठा appleir अणु
	काष्ठा input_dev *input_dev;
	काष्ठा hid_device *hid;
	अचिन्हित लघु keymap[ARRAY_SIZE(appleir_key_table)];
	काष्ठा समयr_list key_up_समयr;	/* समयr क्रम key up */
	spinlock_t lock;		/* protects .current_key */
	पूर्णांक current_key;		/* the currently pressed key */
	पूर्णांक prev_key_idx;		/* key index in a 2 packets message */
पूर्ण;

अटल पूर्णांक get_key(पूर्णांक data)
अणु
	/*
	 * The key is coded accross bits 2..9:
	 *
	 * 0x00 or 0x01 (        )	key:  0		-> KEY_RESERVED
	 * 0x02 or 0x03 (  menu  )	key:  1		-> KEY_MENU
	 * 0x04 or 0x05 (   >"   )	key:  2		-> KEY_PLAYPAUSE
	 * 0x06 or 0x07 (   >>   )	key:  3		-> KEY_FORWARD
	 * 0x08 or 0x09 (   <<   )	key:  4		-> KEY_BACK
	 * 0x0a or 0x0b (    +   )	key:  5		-> KEY_VOLUMEUP
	 * 0x0c or 0x0d (    -   )	key:  6		-> KEY_VOLUMEDOWN
	 * 0x0e or 0x0f (        )	key:  7		-> KEY_RESERVED
	 * 0x50 or 0x51 (        )	key:  8		-> KEY_RESERVED
	 * 0x52 or 0x53 (        )	key:  9		-> KEY_RESERVED
	 * 0x54 or 0x55 (        )	key: 10		-> KEY_RESERVED
	 * 0x56 or 0x57 (        )	key: 11		-> KEY_RESERVED
	 * 0x58 or 0x59 (        )	key: 12		-> KEY_RESERVED
	 * 0x5a or 0x5b (        )	key: 13		-> KEY_RESERVED
	 * 0x5c or 0x5d ( middle )	key: 14		-> KEY_ENTER
	 * 0x5e or 0x5f (   >"   )	key: 15		-> KEY_PLAYPAUSE
	 *
	 * Packets starting with 0x5 are part of a two-packets message,
	 * we notअगरy the caller by sending a negative value.
	 */
	पूर्णांक key = (data >> 1) & KEY_MASK;

	अगर ((data & TWO_PACKETS_MASK))
		/* Part of a 2 packets-command */
		key = -key;

	वापस key;
पूर्ण

अटल व्योम key_up(काष्ठा hid_device *hid, काष्ठा appleir *appleir, पूर्णांक key)
अणु
	input_report_key(appleir->input_dev, key, 0);
	input_sync(appleir->input_dev);
पूर्ण

अटल व्योम key_करोwn(काष्ठा hid_device *hid, काष्ठा appleir *appleir, पूर्णांक key)
अणु
	input_report_key(appleir->input_dev, key, 1);
	input_sync(appleir->input_dev);
पूर्ण

अटल व्योम battery_flat(काष्ठा appleir *appleir)
अणु
	dev_err(&appleir->input_dev->dev, "possible flat battery?\n");
पूर्ण

अटल व्योम key_up_tick(काष्ठा समयr_list *t)
अणु
	काष्ठा appleir *appleir = from_समयr(appleir, t, key_up_समयr);
	काष्ठा hid_device *hid = appleir->hid;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&appleir->lock, flags);
	अगर (appleir->current_key) अणु
		key_up(hid, appleir, appleir->current_key);
		appleir->current_key = 0;
	पूर्ण
	spin_unlock_irqrestore(&appleir->lock, flags);
पूर्ण

अटल पूर्णांक appleir_raw_event(काष्ठा hid_device *hid, काष्ठा hid_report *report,
	 u8 *data, पूर्णांक len)
अणु
	काष्ठा appleir *appleir = hid_get_drvdata(hid);
	अटल स्थिर u8 keyकरोwn[] = अणु 0x25, 0x87, 0xee पूर्ण;
	अटल स्थिर u8 keyrepeat[] = अणु 0x26, पूर्ण;
	अटल स्थिर u8 flatbattery[] = अणु 0x25, 0x87, 0xe0 पूर्ण;
	अचिन्हित दीर्घ flags;

	अगर (len != 5)
		जाओ out;

	अगर (!स_भेद(data, keyकरोwn, माप(keyकरोwn))) अणु
		पूर्णांक index;

		spin_lock_irqsave(&appleir->lock, flags);
		/*
		 * If we alपढ़ोy have a key करोwn, take it up beक्रमe marking
		 * this one करोwn
		 */
		अगर (appleir->current_key)
			key_up(hid, appleir, appleir->current_key);

		/* Handle dual packet commands */
		अगर (appleir->prev_key_idx > 0)
			index = appleir->prev_key_idx;
		अन्यथा
			index = get_key(data[4]);

		अगर (index >= 0) अणु
			appleir->current_key = appleir->keymap[index];

			key_करोwn(hid, appleir, appleir->current_key);
			/*
			 * Remote करोesn't करो key up, either pull them up, in
			 * the test above, or here set a समयr which pulls
			 * them up after 1/8 s
			 */
			mod_समयr(&appleir->key_up_समयr, jअगरfies + HZ / 8);
			appleir->prev_key_idx = 0;
		पूर्ण अन्यथा
			/* Remember key क्रम next packet */
			appleir->prev_key_idx = -index;
		spin_unlock_irqrestore(&appleir->lock, flags);
		जाओ out;
	पूर्ण

	appleir->prev_key_idx = 0;

	अगर (!स_भेद(data, keyrepeat, माप(keyrepeat))) अणु
		key_करोwn(hid, appleir, appleir->current_key);
		/*
		 * Remote करोesn't करो key up, either pull them up, in the test
		 * above, or here set a समयr which pulls them up after 1/8 s
		 */
		mod_समयr(&appleir->key_up_समयr, jअगरfies + HZ / 8);
		जाओ out;
	पूर्ण

	अगर (!स_भेद(data, flatbattery, माप(flatbattery))) अणु
		battery_flat(appleir);
		/* Fall through */
	पूर्ण

out:
	/* let hidraw and hiddev handle the report */
	वापस 0;
पूर्ण

अटल पूर्णांक appleir_input_configured(काष्ठा hid_device *hid,
		काष्ठा hid_input *hidinput)
अणु
	काष्ठा input_dev *input_dev = hidinput->input;
	काष्ठा appleir *appleir = hid_get_drvdata(hid);
	पूर्णांक i;

	appleir->input_dev = input_dev;

	input_dev->keycode = appleir->keymap;
	input_dev->keycodesize = माप(अचिन्हित लघु);
	input_dev->keycodemax = ARRAY_SIZE(appleir->keymap);

	input_dev->evbit[0] = BIT(EV_KEY) | BIT(EV_REP);

	स_नकल(appleir->keymap, appleir_key_table, माप(appleir->keymap));
	क्रम (i = 0; i < ARRAY_SIZE(appleir_key_table); i++)
		set_bit(appleir->keymap[i], input_dev->keybit);
	clear_bit(KEY_RESERVED, input_dev->keybit);

	वापस 0;
पूर्ण

अटल पूर्णांक appleir_input_mapping(काष्ठा hid_device *hid,
		काष्ठा hid_input *hi, काष्ठा hid_field *field,
		काष्ठा hid_usage *usage, अचिन्हित दीर्घ **bit, पूर्णांक *max)
अणु
	वापस -1;
पूर्ण

अटल पूर्णांक appleir_probe(काष्ठा hid_device *hid, स्थिर काष्ठा hid_device_id *id)
अणु
	पूर्णांक ret;
	काष्ठा appleir *appleir;

	appleir = devm_kzalloc(&hid->dev, माप(काष्ठा appleir), GFP_KERNEL);
	अगर (!appleir)
		वापस -ENOMEM;

	appleir->hid = hid;

	/* क्रमce input as some remotes bypass the input registration */
	hid->quirks |= HID_QUIRK_HIDINPUT_FORCE;

	spin_lock_init(&appleir->lock);
	समयr_setup(&appleir->key_up_समयr, key_up_tick, 0);

	hid_set_drvdata(hid, appleir);

	ret = hid_parse(hid);
	अगर (ret) अणु
		hid_err(hid, "parse failed\n");
		जाओ fail;
	पूर्ण

	ret = hid_hw_start(hid, HID_CONNECT_DEFAULT | HID_CONNECT_HIDDEV_FORCE);
	अगर (ret) अणु
		hid_err(hid, "hw start failed\n");
		जाओ fail;
	पूर्ण

	वापस 0;
fail:
	devm_kमुक्त(&hid->dev, appleir);
	वापस ret;
पूर्ण

अटल व्योम appleir_हटाओ(काष्ठा hid_device *hid)
अणु
	काष्ठा appleir *appleir = hid_get_drvdata(hid);
	hid_hw_stop(hid);
	del_समयr_sync(&appleir->key_up_समयr);
पूर्ण

अटल स्थिर काष्ठा hid_device_id appleir_devices[] = अणु
	अणु HID_USB_DEVICE(USB_VENDOR_ID_APPLE, USB_DEVICE_ID_APPLE_IRCONTROL) पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_APPLE, USB_DEVICE_ID_APPLE_IRCONTROL2) पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_APPLE, USB_DEVICE_ID_APPLE_IRCONTROL3) पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_APPLE, USB_DEVICE_ID_APPLE_IRCONTROL4) पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_APPLE, USB_DEVICE_ID_APPLE_IRCONTROL5) पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(hid, appleir_devices);

अटल काष्ठा hid_driver appleir_driver = अणु
	.name = "appleir",
	.id_table = appleir_devices,
	.raw_event = appleir_raw_event,
	.input_configured = appleir_input_configured,
	.probe = appleir_probe,
	.हटाओ = appleir_हटाओ,
	.input_mapping = appleir_input_mapping,
पूर्ण;
module_hid_driver(appleir_driver);
