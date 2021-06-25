<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  Input Power Event -> APM Bridge
 *
 *  Copyright (c) 2007 Riअक्षरd Purdie
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/input.h>
#समावेश <linux/slab.h>
#समावेश <linux/init.h>
#समावेश <linux/tty.h>
#समावेश <linux/delay.h>
#समावेश <linux/pm.h>
#समावेश <linux/apm-emulation.h>

अटल व्योम प्रणाली_घातer_event(अचिन्हित पूर्णांक keycode)
अणु
	चयन (keycode) अणु
	हाल KEY_SUSPEND:
		apm_queue_event(APM_USER_SUSPEND);
		pr_info("Requesting system suspend...\n");
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम apmघातer_event(काष्ठा input_handle *handle, अचिन्हित पूर्णांक type,
			   अचिन्हित पूर्णांक code, पूर्णांक value)
अणु
	/* only react on key करोwn events */
	अगर (value != 1)
		वापस;

	चयन (type) अणु
	हाल EV_PWR:
		प्रणाली_घातer_event(code);
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक apmघातer_connect(काष्ठा input_handler *handler,
					  काष्ठा input_dev *dev,
					  स्थिर काष्ठा input_device_id *id)
अणु
	काष्ठा input_handle *handle;
	पूर्णांक error;

	handle = kzalloc(माप(काष्ठा input_handle), GFP_KERNEL);
	अगर (!handle)
		वापस -ENOMEM;

	handle->dev = dev;
	handle->handler = handler;
	handle->name = "apm-power";

	error = input_रेजिस्टर_handle(handle);
	अगर (error) अणु
		pr_err("Failed to register input power handler, error %d\n",
		       error);
		kमुक्त(handle);
		वापस error;
	पूर्ण

	error = input_खोलो_device(handle);
	अगर (error) अणु
		pr_err("Failed to open input power device, error %d\n", error);
		input_unरेजिस्टर_handle(handle);
		kमुक्त(handle);
		वापस error;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम apmघातer_disconnect(काष्ठा input_handle *handle)
अणु
	input_बंद_device(handle);
	input_unरेजिस्टर_handle(handle);
	kमुक्त(handle);
पूर्ण

अटल स्थिर काष्ठा input_device_id apmघातer_ids[] = अणु
	अणु
		.flags = INPUT_DEVICE_ID_MATCH_EVBIT,
		.evbit = अणु BIT_MASK(EV_PWR) पूर्ण,
	पूर्ण,
	अणु पूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(input, apmघातer_ids);

अटल काष्ठा input_handler apmघातer_handler = अणु
	.event =	apmघातer_event,
	.connect =	apmघातer_connect,
	.disconnect =	apmघातer_disconnect,
	.name =		"apm-power",
	.id_table =	apmघातer_ids,
पूर्ण;

अटल पूर्णांक __init apmघातer_init(व्योम)
अणु
	वापस input_रेजिस्टर_handler(&apmघातer_handler);
पूर्ण

अटल व्योम __निकास apmघातer_निकास(व्योम)
अणु
	input_unरेजिस्टर_handler(&apmघातer_handler);
पूर्ण

module_init(apmघातer_init);
module_निकास(apmघातer_निकास);

MODULE_AUTHOR("Richard Purdie <rpurdie@rpsys.net>");
MODULE_DESCRIPTION("Input Power Event -> APM Bridge");
MODULE_LICENSE("GPL");
