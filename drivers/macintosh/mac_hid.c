<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * drivers/macपूर्णांकosh/mac_hid.c
 *
 * HID support stuff क्रम Macपूर्णांकosh computers.
 *
 * Copyright (C) 2000 Franz Sirl.
 *
 * This file will soon be हटाओd in favor of an uinput userspace tool.
 */

#समावेश <linux/init.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/sysctl.h>
#समावेश <linux/input.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>

MODULE_LICENSE("GPL");

अटल पूर्णांक mouse_emulate_buttons;
अटल पूर्णांक mouse_button2_keycode = KEY_RIGHTCTRL;	/* right control key */
अटल पूर्णांक mouse_button3_keycode = KEY_RIGHTALT;	/* right option key */

अटल काष्ठा input_dev *mac_hid_emumouse_dev;

अटल DEFINE_MUTEX(mac_hid_emumouse_mutex);

अटल पूर्णांक mac_hid_create_emumouse(व्योम)
अणु
	अटल काष्ठा lock_class_key mac_hid_emumouse_dev_event_class;
	अटल काष्ठा lock_class_key mac_hid_emumouse_dev_mutex_class;
	पूर्णांक err;

	mac_hid_emumouse_dev = input_allocate_device();
	अगर (!mac_hid_emumouse_dev)
		वापस -ENOMEM;

	lockdep_set_class(&mac_hid_emumouse_dev->event_lock,
			  &mac_hid_emumouse_dev_event_class);
	lockdep_set_class(&mac_hid_emumouse_dev->mutex,
			  &mac_hid_emumouse_dev_mutex_class);

	mac_hid_emumouse_dev->name = "Macintosh mouse button emulation";
	mac_hid_emumouse_dev->id.bustype = BUS_ADB;
	mac_hid_emumouse_dev->id.venकरोr = 0x0001;
	mac_hid_emumouse_dev->id.product = 0x0001;
	mac_hid_emumouse_dev->id.version = 0x0100;

	mac_hid_emumouse_dev->evbit[0] = BIT_MASK(EV_KEY) | BIT_MASK(EV_REL);
	mac_hid_emumouse_dev->keybit[BIT_WORD(BTN_MOUSE)] =
		BIT_MASK(BTN_LEFT) | BIT_MASK(BTN_MIDDLE) | BIT_MASK(BTN_RIGHT);
	mac_hid_emumouse_dev->relbit[0] = BIT_MASK(REL_X) | BIT_MASK(REL_Y);

	err = input_रेजिस्टर_device(mac_hid_emumouse_dev);
	अगर (err) अणु
		input_मुक्त_device(mac_hid_emumouse_dev);
		mac_hid_emumouse_dev = शून्य;
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम mac_hid_destroy_emumouse(व्योम)
अणु
	input_unरेजिस्टर_device(mac_hid_emumouse_dev);
	mac_hid_emumouse_dev = शून्य;
पूर्ण

अटल bool mac_hid_emumouse_filter(काष्ठा input_handle *handle,
				    अचिन्हित पूर्णांक type, अचिन्हित पूर्णांक code,
				    पूर्णांक value)
अणु
	अचिन्हित पूर्णांक btn;

	अगर (type != EV_KEY)
		वापस false;

	अगर (code == mouse_button2_keycode)
		btn = BTN_MIDDLE;
	अन्यथा अगर (code == mouse_button3_keycode)
		btn = BTN_RIGHT;
	अन्यथा
		वापस false;

	input_report_key(mac_hid_emumouse_dev, btn, value);
	input_sync(mac_hid_emumouse_dev);

	वापस true;
पूर्ण

अटल पूर्णांक mac_hid_emumouse_connect(काष्ठा input_handler *handler,
				    काष्ठा input_dev *dev,
				    स्थिर काष्ठा input_device_id *id)
अणु
	काष्ठा input_handle *handle;
	पूर्णांक error;

	/* Don't bind to ourselves */
	अगर (dev == mac_hid_emumouse_dev)
		वापस -ENODEV;

	handle = kzalloc(माप(काष्ठा input_handle), GFP_KERNEL);
	अगर (!handle)
		वापस -ENOMEM;

	handle->dev = dev;
	handle->handler = handler;
	handle->name = "mac-button-emul";

	error = input_रेजिस्टर_handle(handle);
	अगर (error) अणु
		prपूर्णांकk(KERN_ERR
			"mac_hid: Failed to register button emulation handle, "
			"error %d\n", error);
		जाओ err_मुक्त;
	पूर्ण

	error = input_खोलो_device(handle);
	अगर (error) अणु
		prपूर्णांकk(KERN_ERR
			"mac_hid: Failed to open input device, error %d\n",
			error);
		जाओ err_unरेजिस्टर;
	पूर्ण

	वापस 0;

 err_unरेजिस्टर:
	input_unरेजिस्टर_handle(handle);
 err_मुक्त:
	kमुक्त(handle);
	वापस error;
पूर्ण

अटल व्योम mac_hid_emumouse_disconnect(काष्ठा input_handle *handle)
अणु
	input_बंद_device(handle);
	input_unरेजिस्टर_handle(handle);
	kमुक्त(handle);
पूर्ण

अटल स्थिर काष्ठा input_device_id mac_hid_emumouse_ids[] = अणु
	अणु
		.flags = INPUT_DEVICE_ID_MATCH_EVBIT,
		.evbit = अणु BIT_MASK(EV_KEY) पूर्ण,
	पूर्ण,
	अणु पूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(input, mac_hid_emumouse_ids);

अटल काष्ठा input_handler mac_hid_emumouse_handler = अणु
	.filter		= mac_hid_emumouse_filter,
	.connect	= mac_hid_emumouse_connect,
	.disconnect	= mac_hid_emumouse_disconnect,
	.name		= "mac-button-emul",
	.id_table	= mac_hid_emumouse_ids,
पूर्ण;

अटल पूर्णांक mac_hid_start_emulation(व्योम)
अणु
	पूर्णांक err;

	err = mac_hid_create_emumouse();
	अगर (err)
		वापस err;

	err = input_रेजिस्टर_handler(&mac_hid_emumouse_handler);
	अगर (err) अणु
		mac_hid_destroy_emumouse();
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम mac_hid_stop_emulation(व्योम)
अणु
	input_unरेजिस्टर_handler(&mac_hid_emumouse_handler);
	mac_hid_destroy_emumouse();
पूर्ण

अटल पूर्णांक mac_hid_toggle_emumouse(काष्ठा ctl_table *table, पूर्णांक ग_लिखो,
				   व्योम *buffer, माप_प्रकार *lenp, loff_t *ppos)
अणु
	पूर्णांक *valp = table->data;
	पूर्णांक old_val = *valp;
	पूर्णांक rc;

	rc = mutex_lock_समाप्तable(&mac_hid_emumouse_mutex);
	अगर (rc)
		वापस rc;

	rc = proc_करोपूर्णांकvec(table, ग_लिखो, buffer, lenp, ppos);

	अगर (rc == 0 && ग_लिखो && *valp != old_val) अणु
		अगर (*valp == 1)
			rc = mac_hid_start_emulation();
		अन्यथा अगर (*valp == 0)
			mac_hid_stop_emulation();
		अन्यथा
			rc = -EINVAL;
	पूर्ण

	/* Restore the old value in हाल of error */
	अगर (rc)
		*valp = old_val;

	mutex_unlock(&mac_hid_emumouse_mutex);

	वापस rc;
पूर्ण

/* file(s) in /proc/sys/dev/mac_hid */
अटल काष्ठा ctl_table mac_hid_files[] = अणु
	अणु
		.procname	= "mouse_button_emulation",
		.data		= &mouse_emulate_buttons,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= mac_hid_toggle_emumouse,
	पूर्ण,
	अणु
		.procname	= "mouse_button2_keycode",
		.data		= &mouse_button2_keycode,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec,
	पूर्ण,
	अणु
		.procname	= "mouse_button3_keycode",
		.data		= &mouse_button3_keycode,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec,
	पूर्ण,
	अणु पूर्ण
पूर्ण;

/* dir in /proc/sys/dev */
अटल काष्ठा ctl_table mac_hid_dir[] = अणु
	अणु
		.procname	= "mac_hid",
		.maxlen		= 0,
		.mode		= 0555,
		.child		= mac_hid_files,
	पूर्ण,
	अणु पूर्ण
पूर्ण;

/* /proc/sys/dev itself, in हाल that is not there yet */
अटल काष्ठा ctl_table mac_hid_root_dir[] = अणु
	अणु
		.procname	= "dev",
		.maxlen		= 0,
		.mode		= 0555,
		.child		= mac_hid_dir,
	पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल काष्ठा ctl_table_header *mac_hid_sysctl_header;

अटल पूर्णांक __init mac_hid_init(व्योम)
अणु
	mac_hid_sysctl_header = रेजिस्टर_sysctl_table(mac_hid_root_dir);
	अगर (!mac_hid_sysctl_header)
		वापस -ENOMEM;

	वापस 0;
पूर्ण
module_init(mac_hid_init);

अटल व्योम __निकास mac_hid_निकास(व्योम)
अणु
	unरेजिस्टर_sysctl_table(mac_hid_sysctl_header);

	अगर (mouse_emulate_buttons)
		mac_hid_stop_emulation();
पूर्ण
module_निकास(mac_hid_निकास);
