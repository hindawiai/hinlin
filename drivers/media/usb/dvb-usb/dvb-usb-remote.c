<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* dvb-usb-remote.c is part of the DVB USB library.
 *
 * Copyright (C) 2004-6 Patrick Boettcher (patrick.boettcher@posteo.de)
 * see dvb-usb-init.c क्रम copyright inक्रमmation.
 *
 * This file contains functions क्रम initializing the input-device and क्रम handling remote-control-queries.
 */
#समावेश "dvb-usb-common.h"
#समावेश <linux/usb/input.h>

अटल अचिन्हित पूर्णांक
legacy_dvb_usb_get_keymap_index(स्थिर काष्ठा input_keymap_entry *ke,
				काष्ठा rc_map_table *keymap,
				अचिन्हित पूर्णांक keymap_size)
अणु
	अचिन्हित पूर्णांक index;
	अचिन्हित पूर्णांक scancode;

	अगर (ke->flags & INPUT_KEYMAP_BY_INDEX) अणु
		index = ke->index;
	पूर्ण अन्यथा अणु
		अगर (input_scancode_to_scalar(ke, &scancode))
			वापस keymap_size;

		/* See अगर we can match the raw key code. */
		क्रम (index = 0; index < keymap_size; index++)
			अगर (keymap[index].scancode == scancode)
				अवरोध;

		/* See अगर there is an unused hole in the map */
		अगर (index >= keymap_size) अणु
			क्रम (index = 0; index < keymap_size; index++) अणु
				अगर (keymap[index].keycode == KEY_RESERVED ||
				    keymap[index].keycode == KEY_UNKNOWN) अणु
					अवरोध;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	वापस index;
पूर्ण

अटल पूर्णांक legacy_dvb_usb_getkeycode(काष्ठा input_dev *dev,
				     काष्ठा input_keymap_entry *ke)
अणु
	काष्ठा dvb_usb_device *d = input_get_drvdata(dev);
	काष्ठा rc_map_table *keymap = d->props.rc.legacy.rc_map_table;
	अचिन्हित पूर्णांक keymap_size = d->props.rc.legacy.rc_map_size;
	अचिन्हित पूर्णांक index;

	index = legacy_dvb_usb_get_keymap_index(ke, keymap, keymap_size);
	अगर (index >= keymap_size)
		वापस -EINVAL;

	ke->keycode = keymap[index].keycode;
	अगर (ke->keycode == KEY_UNKNOWN)
		ke->keycode = KEY_RESERVED;
	ke->len = माप(keymap[index].scancode);
	स_नकल(&ke->scancode, &keymap[index].scancode, ke->len);
	ke->index = index;

	वापस 0;
पूर्ण

अटल पूर्णांक legacy_dvb_usb_setkeycode(काष्ठा input_dev *dev,
				     स्थिर काष्ठा input_keymap_entry *ke,
				     अचिन्हित पूर्णांक *old_keycode)
अणु
	काष्ठा dvb_usb_device *d = input_get_drvdata(dev);
	काष्ठा rc_map_table *keymap = d->props.rc.legacy.rc_map_table;
	अचिन्हित पूर्णांक keymap_size = d->props.rc.legacy.rc_map_size;
	अचिन्हित पूर्णांक index;

	index = legacy_dvb_usb_get_keymap_index(ke, keymap, keymap_size);
	/*
	 * FIXME: Currently, it is not possible to increase the size of
	 * scancode table. For it to happen, one possibility
	 * would be to allocate a table with key_map_size + 1,
	 * copying data, appending the new key on it, and मुक्तing
	 * the old one - or maybe just allocating some spare space
	 */
	अगर (index >= keymap_size)
		वापस -EINVAL;

	*old_keycode = keymap[index].keycode;
	keymap->keycode = ke->keycode;
	__set_bit(ke->keycode, dev->keybit);

	अगर (*old_keycode != KEY_RESERVED) अणु
		__clear_bit(*old_keycode, dev->keybit);
		क्रम (index = 0; index < keymap_size; index++) अणु
			अगर (keymap[index].keycode == *old_keycode) अणु
				__set_bit(*old_keycode, dev->keybit);
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/* Remote-control poll function - called every dib->rc_query_पूर्णांकerval ms to see
 * whether the remote control has received anything.
 *
 * TODO: Fix the repeat rate of the input device.
 */
अटल व्योम legacy_dvb_usb_पढ़ो_remote_control(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा dvb_usb_device *d =
		container_of(work, काष्ठा dvb_usb_device, rc_query_work.work);
	u32 event;
	पूर्णांक state;

	/* TODO: need a lock here.  We can simply skip checking क्रम the remote control
	   अगर we're busy. */

	/* when the parameter has been set to 1 via sysfs जबतक the driver was running */
	अगर (dvb_usb_disable_rc_polling)
		वापस;

	अगर (d->props.rc.legacy.rc_query(d,&event,&state)) अणु
		err("error while querying for an remote control event.");
		जाओ schedule;
	पूर्ण


	चयन (state) अणु
		हाल REMOTE_NO_KEY_PRESSED:
			अवरोध;
		हाल REMOTE_KEY_PRESSED:
			deb_rc("key pressed\n");
			d->last_event = event;
			input_event(d->input_dev, EV_KEY, event, 1);
			input_sync(d->input_dev);
			input_event(d->input_dev, EV_KEY, d->last_event, 0);
			input_sync(d->input_dev);
			अवरोध;
		हाल REMOTE_KEY_REPEAT:
			deb_rc("key repeated\n");
			input_event(d->input_dev, EV_KEY, event, 1);
			input_sync(d->input_dev);
			input_event(d->input_dev, EV_KEY, d->last_event, 0);
			input_sync(d->input_dev);
			अवरोध;
		शेष:
			अवरोध;
	पूर्ण

/* improved repeat handling ???
	चयन (state) अणु
		हाल REMOTE_NO_KEY_PRESSED:
			deb_rc("NO KEY PRESSED\n");
			अगर (d->last_state != REMOTE_NO_KEY_PRESSED) अणु
				deb_rc("releasing event %d\n",d->last_event);
				input_event(d->rc_input_dev, EV_KEY, d->last_event, 0);
				input_sync(d->rc_input_dev);
			पूर्ण
			d->last_state = REMOTE_NO_KEY_PRESSED;
			d->last_event = 0;
			अवरोध;
		हाल REMOTE_KEY_PRESSED:
			deb_rc("KEY PRESSED\n");
			deb_rc("pressing event %d\n",event);

			input_event(d->rc_input_dev, EV_KEY, event, 1);
			input_sync(d->rc_input_dev);

			d->last_event = event;
			d->last_state = REMOTE_KEY_PRESSED;
			अवरोध;
		हाल REMOTE_KEY_REPEAT:
			deb_rc("KEY_REPEAT\n");
			अगर (d->last_state != REMOTE_NO_KEY_PRESSED) अणु
				deb_rc("repeating event %d\n",d->last_event);
				input_event(d->rc_input_dev, EV_KEY, d->last_event, 2);
				input_sync(d->rc_input_dev);
				d->last_state = REMOTE_KEY_REPEAT;
			पूर्ण
		शेष:
			अवरोध;
	पूर्ण
*/

schedule:
	schedule_delayed_work(&d->rc_query_work,msecs_to_jअगरfies(d->props.rc.legacy.rc_पूर्णांकerval));
पूर्ण

अटल पूर्णांक legacy_dvb_usb_remote_init(काष्ठा dvb_usb_device *d)
अणु
	पूर्णांक i, err, rc_पूर्णांकerval;
	काष्ठा input_dev *input_dev;

	input_dev = input_allocate_device();
	अगर (!input_dev)
		वापस -ENOMEM;

	input_dev->evbit[0] = BIT_MASK(EV_KEY);
	input_dev->name = "IR-receiver inside an USB DVB receiver";
	input_dev->phys = d->rc_phys;
	usb_to_input_id(d->udev, &input_dev->id);
	input_dev->dev.parent = &d->udev->dev;
	d->input_dev = input_dev;
	d->rc_dev = शून्य;

	input_dev->getkeycode = legacy_dvb_usb_getkeycode;
	input_dev->setkeycode = legacy_dvb_usb_setkeycode;

	/* set the bits क्रम the keys */
	deb_rc("key map size: %d\n", d->props.rc.legacy.rc_map_size);
	क्रम (i = 0; i < d->props.rc.legacy.rc_map_size; i++) अणु
		deb_rc("setting bit for event %d item %d\n",
			d->props.rc.legacy.rc_map_table[i].keycode, i);
		set_bit(d->props.rc.legacy.rc_map_table[i].keycode, input_dev->keybit);
	पूर्ण

	/* setting these two values to non-zero, we have to manage key repeats */
	input_dev->rep[REP_PERIOD] = d->props.rc.legacy.rc_पूर्णांकerval;
	input_dev->rep[REP_DELAY]  = d->props.rc.legacy.rc_पूर्णांकerval + 150;

	input_set_drvdata(input_dev, d);

	err = input_रेजिस्टर_device(input_dev);
	अगर (err)
		input_मुक्त_device(input_dev);

	rc_पूर्णांकerval = d->props.rc.legacy.rc_पूर्णांकerval;

	INIT_DELAYED_WORK(&d->rc_query_work, legacy_dvb_usb_पढ़ो_remote_control);

	info("schedule remote query interval to %d msecs.", rc_पूर्णांकerval);
	schedule_delayed_work(&d->rc_query_work,
			      msecs_to_jअगरfies(rc_पूर्णांकerval));

	d->state |= DVB_USB_STATE_REMOTE;

	वापस err;
पूर्ण

/* Remote-control poll function - called every dib->rc_query_पूर्णांकerval ms to see
 * whether the remote control has received anything.
 *
 * TODO: Fix the repeat rate of the input device.
 */
अटल व्योम dvb_usb_पढ़ो_remote_control(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा dvb_usb_device *d =
		container_of(work, काष्ठा dvb_usb_device, rc_query_work.work);
	पूर्णांक err;

	/* TODO: need a lock here.  We can simply skip checking क्रम the remote control
	   अगर we're busy. */

	/* when the parameter has been set to 1 via sysfs जबतक the
	 * driver was running, or when bulk mode is enabled after IR init
	 */
	अगर (dvb_usb_disable_rc_polling || d->props.rc.core.bulk_mode)
		वापस;

	err = d->props.rc.core.rc_query(d);
	अगर (err)
		err("error %d while querying for an remote control event.", err);

	schedule_delayed_work(&d->rc_query_work,
			      msecs_to_jअगरfies(d->props.rc.core.rc_पूर्णांकerval));
पूर्ण

अटल पूर्णांक rc_core_dvb_usb_remote_init(काष्ठा dvb_usb_device *d)
अणु
	पूर्णांक err, rc_पूर्णांकerval;
	काष्ठा rc_dev *dev;

	dev = rc_allocate_device(d->props.rc.core.driver_type);
	अगर (!dev)
		वापस -ENOMEM;

	dev->driver_name = d->props.rc.core.module_name;
	dev->map_name = d->props.rc.core.rc_codes;
	dev->change_protocol = d->props.rc.core.change_protocol;
	dev->allowed_protocols = d->props.rc.core.allowed_protos;
	usb_to_input_id(d->udev, &dev->input_id);
	dev->device_name = d->desc->name;
	dev->input_phys = d->rc_phys;
	dev->dev.parent = &d->udev->dev;
	dev->priv = d;
	dev->scancode_mask = d->props.rc.core.scancode_mask;

	err = rc_रेजिस्टर_device(dev);
	अगर (err < 0) अणु
		rc_मुक्त_device(dev);
		वापस err;
	पूर्ण

	d->input_dev = शून्य;
	d->rc_dev = dev;

	अगर (!d->props.rc.core.rc_query || d->props.rc.core.bulk_mode)
		वापस 0;

	/* Polling mode - initialize a work queue क्रम handling it */
	INIT_DELAYED_WORK(&d->rc_query_work, dvb_usb_पढ़ो_remote_control);

	rc_पूर्णांकerval = d->props.rc.core.rc_पूर्णांकerval;

	info("schedule remote query interval to %d msecs.", rc_पूर्णांकerval);
	schedule_delayed_work(&d->rc_query_work,
			      msecs_to_jअगरfies(rc_पूर्णांकerval));

	वापस 0;
पूर्ण

पूर्णांक dvb_usb_remote_init(काष्ठा dvb_usb_device *d)
अणु
	पूर्णांक err;

	अगर (dvb_usb_disable_rc_polling)
		वापस 0;

	अगर (d->props.rc.legacy.rc_map_table && d->props.rc.legacy.rc_query)
		d->props.rc.mode = DVB_RC_LEGACY;
	अन्यथा अगर (d->props.rc.core.rc_codes)
		d->props.rc.mode = DVB_RC_CORE;
	अन्यथा
		वापस 0;

	usb_make_path(d->udev, d->rc_phys, माप(d->rc_phys));
	strlcat(d->rc_phys, "/ir0", माप(d->rc_phys));

	/* Start the remote-control polling. */
	अगर (d->props.rc.legacy.rc_पूर्णांकerval < 40)
		d->props.rc.legacy.rc_पूर्णांकerval = 100; /* शेष */

	अगर (d->props.rc.mode == DVB_RC_LEGACY)
		err = legacy_dvb_usb_remote_init(d);
	अन्यथा
		err = rc_core_dvb_usb_remote_init(d);
	अगर (err)
		वापस err;

	d->state |= DVB_USB_STATE_REMOTE;

	वापस 0;
पूर्ण

पूर्णांक dvb_usb_remote_निकास(काष्ठा dvb_usb_device *d)
अणु
	अगर (d->state & DVB_USB_STATE_REMOTE) अणु
		cancel_delayed_work_sync(&d->rc_query_work);
		अगर (d->props.rc.mode == DVB_RC_LEGACY)
			input_unरेजिस्टर_device(d->input_dev);
		अन्यथा
			rc_unरेजिस्टर_device(d->rc_dev);
	पूर्ण
	d->state &= ~DVB_USB_STATE_REMOTE;
	वापस 0;
पूर्ण

#घोषणा DVB_USB_RC_NEC_EMPTY           0x00
#घोषणा DVB_USB_RC_NEC_KEY_PRESSED     0x01
#घोषणा DVB_USB_RC_NEC_KEY_REPEATED    0x02
पूर्णांक dvb_usb_nec_rc_key_to_event(काष्ठा dvb_usb_device *d,
		u8 keybuf[5], u32 *event, पूर्णांक *state)
अणु
	पूर्णांक i;
	काष्ठा rc_map_table *keymap = d->props.rc.legacy.rc_map_table;
	*event = 0;
	*state = REMOTE_NO_KEY_PRESSED;
	चयन (keybuf[0]) अणु
		हाल DVB_USB_RC_NEC_EMPTY:
			अवरोध;
		हाल DVB_USB_RC_NEC_KEY_PRESSED:
			अगर ((u8) ~keybuf[1] != keybuf[2] ||
				(u8) ~keybuf[3] != keybuf[4]) अणु
				deb_err("remote control checksum failed.\n");
				अवरोध;
			पूर्ण
			/* See अगर we can match the raw key code. */
			क्रम (i = 0; i < d->props.rc.legacy.rc_map_size; i++)
				अगर (rc5_custom(&keymap[i]) == keybuf[1] &&
					rc5_data(&keymap[i]) == keybuf[3]) अणु
					*event = keymap[i].keycode;
					*state = REMOTE_KEY_PRESSED;
					वापस 0;
				पूर्ण
			deb_err("key mapping failed - no appropriate key found in keymapping\n");
			अवरोध;
		हाल DVB_USB_RC_NEC_KEY_REPEATED:
			*state = REMOTE_KEY_REPEAT;
			अवरोध;
		शेष:
			deb_err("unknown type of remote status: %d\n",keybuf[0]);
			अवरोध;
	पूर्ण
	वापस 0;
पूर्ण
EXPORT_SYMBOL(dvb_usb_nec_rc_key_to_event);
