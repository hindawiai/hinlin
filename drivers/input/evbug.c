<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Copyright (c) 1999-2001 Vojtech Pavlik
 */

/*
 *  Input driver event debug module - dumps all events पूर्णांकo syslog
 */

/*
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/input.h>
#समावेश <linux/init.h>
#समावेश <linux/device.h>

MODULE_AUTHOR("Vojtech Pavlik <vojtech@ucw.cz>");
MODULE_DESCRIPTION("Input driver event debug module");
MODULE_LICENSE("GPL");

अटल व्योम evbug_event(काष्ठा input_handle *handle, अचिन्हित पूर्णांक type, अचिन्हित पूर्णांक code, पूर्णांक value)
अणु
	prपूर्णांकk(KERN_DEBUG pr_fmt("Event. Dev: %s, Type: %d, Code: %d, Value: %d\n"),
	       dev_name(&handle->dev->dev), type, code, value);
पूर्ण

अटल पूर्णांक evbug_connect(काष्ठा input_handler *handler, काष्ठा input_dev *dev,
			 स्थिर काष्ठा input_device_id *id)
अणु
	काष्ठा input_handle *handle;
	पूर्णांक error;

	handle = kzalloc(माप(काष्ठा input_handle), GFP_KERNEL);
	अगर (!handle)
		वापस -ENOMEM;

	handle->dev = dev;
	handle->handler = handler;
	handle->name = "evbug";

	error = input_रेजिस्टर_handle(handle);
	अगर (error)
		जाओ err_मुक्त_handle;

	error = input_खोलो_device(handle);
	अगर (error)
		जाओ err_unरेजिस्टर_handle;

	prपूर्णांकk(KERN_DEBUG pr_fmt("Connected device: %s (%s at %s)\n"),
	       dev_name(&dev->dev),
	       dev->name ?: "unknown",
	       dev->phys ?: "unknown");

	वापस 0;

 err_unरेजिस्टर_handle:
	input_unरेजिस्टर_handle(handle);
 err_मुक्त_handle:
	kमुक्त(handle);
	वापस error;
पूर्ण

अटल व्योम evbug_disconnect(काष्ठा input_handle *handle)
अणु
	prपूर्णांकk(KERN_DEBUG pr_fmt("Disconnected device: %s\n"),
	       dev_name(&handle->dev->dev));

	input_बंद_device(handle);
	input_unरेजिस्टर_handle(handle);
	kमुक्त(handle);
पूर्ण

अटल स्थिर काष्ठा input_device_id evbug_ids[] = अणु
	अणु .driver_info = 1 पूर्ण,	/* Matches all devices */
	अणु पूर्ण,			/* Terminating zero entry */
पूर्ण;

MODULE_DEVICE_TABLE(input, evbug_ids);

अटल काष्ठा input_handler evbug_handler = अणु
	.event =	evbug_event,
	.connect =	evbug_connect,
	.disconnect =	evbug_disconnect,
	.name =		"evbug",
	.id_table =	evbug_ids,
पूर्ण;

अटल पूर्णांक __init evbug_init(व्योम)
अणु
	वापस input_रेजिस्टर_handler(&evbug_handler);
पूर्ण

अटल व्योम __निकास evbug_निकास(व्योम)
अणु
	input_unरेजिस्टर_handler(&evbug_handler);
पूर्ण

module_init(evbug_init);
module_निकास(evbug_निकास);
