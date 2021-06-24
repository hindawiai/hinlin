<शैली गुरु>
/*
 * Copyright (C) 2010 Dell Inc.
 * Louis Davis <louis_davis@dell.com>
 * Jim Dailey <jim_dailey@dell.com>
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License as
 * published by the Free Software Foundation.
 *
 */

#समावेश <linux/acpi.h>
#समावेश <linux/leds.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>

MODULE_AUTHOR("Louis Davis/Jim Dailey");
MODULE_DESCRIPTION("Dell LED Control Driver");
MODULE_LICENSE("GPL");

#घोषणा DELL_LED_BIOS_GUID "F6E4FE6E-909D-47cb-8BAB-C9F6F2F8D396"
MODULE_ALIAS("wmi:" DELL_LED_BIOS_GUID);

/* Error Result Codes: */
#घोषणा INVALID_DEVICE_ID	250
#घोषणा INVALID_PARAMETER	251
#घोषणा INVALID_BUFFER		252
#घोषणा INTERFACE_ERROR		253
#घोषणा UNSUPPORTED_COMMAND	254
#घोषणा UNSPECIFIED_ERROR	255

/* Device ID */
#घोषणा DEVICE_ID_PANEL_BACK	1

/* LED Commands */
#घोषणा CMD_LED_ON	16
#घोषणा CMD_LED_OFF	17
#घोषणा CMD_LED_BLINK	18

काष्ठा bios_args अणु
	अचिन्हित अक्षर length;
	अचिन्हित अक्षर result_code;
	अचिन्हित अक्षर device_id;
	अचिन्हित अक्षर command;
	अचिन्हित अक्षर on_समय;
	अचिन्हित अक्षर off_समय;
पूर्ण;

अटल पूर्णांक dell_led_perक्रमm_fn(u8 length, u8 result_code, u8 device_id,
			       u8 command, u8 on_समय, u8 off_समय)
अणु
	काष्ठा acpi_buffer output = अणु ACPI_ALLOCATE_BUFFER, शून्य पूर्ण;
	काष्ठा bios_args *bios_वापस;
	काष्ठा acpi_buffer input;
	जोड़ acpi_object *obj;
	acpi_status status;
	u8 वापस_code;

	काष्ठा bios_args args = अणु
		.length = length,
		.result_code = result_code,
		.device_id = device_id,
		.command = command,
		.on_समय = on_समय,
		.off_समय = off_समय
	पूर्ण;

	input.length = माप(काष्ठा bios_args);
	input.poपूर्णांकer = &args;

	status = wmi_evaluate_method(DELL_LED_BIOS_GUID, 0, 1, &input, &output);
	अगर (ACPI_FAILURE(status))
		वापस status;

	obj = output.poपूर्णांकer;

	अगर (!obj)
		वापस -EINVAL;
	अगर (obj->type != ACPI_TYPE_BUFFER) अणु
		kमुक्त(obj);
		वापस -EINVAL;
	पूर्ण

	bios_वापस = ((काष्ठा bios_args *)obj->buffer.poपूर्णांकer);
	वापस_code = bios_वापस->result_code;

	kमुक्त(obj);

	वापस वापस_code;
पूर्ण

अटल पूर्णांक led_on(व्योम)
अणु
	वापस dell_led_perक्रमm_fn(3,	/* Length of command */
		INTERFACE_ERROR,	/* Init to  INTERFACE_ERROR */
		DEVICE_ID_PANEL_BACK,	/* Device ID */
		CMD_LED_ON,		/* Command */
		0,			/* not used */
		0);			/* not used */
पूर्ण

अटल पूर्णांक led_off(व्योम)
अणु
	वापस dell_led_perक्रमm_fn(3,	/* Length of command */
		INTERFACE_ERROR,	/* Init to  INTERFACE_ERROR */
		DEVICE_ID_PANEL_BACK,	/* Device ID */
		CMD_LED_OFF,		/* Command */
		0,			/* not used */
		0);			/* not used */
पूर्ण

अटल पूर्णांक led_blink(अचिन्हित अक्षर on_eighths, अचिन्हित अक्षर off_eighths)
अणु
	वापस dell_led_perक्रमm_fn(5,	/* Length of command */
		INTERFACE_ERROR,	/* Init to  INTERFACE_ERROR */
		DEVICE_ID_PANEL_BACK,	/* Device ID */
		CMD_LED_BLINK,		/* Command */
		on_eighths,		/* blink on in eigths of a second */
		off_eighths);		/* blink off in eights of a second */
पूर्ण

अटल व्योम dell_led_set(काष्ठा led_classdev *led_cdev,
			 क्रमागत led_brightness value)
अणु
	अगर (value == LED_OFF)
		led_off();
	अन्यथा
		led_on();
पूर्ण

अटल पूर्णांक dell_led_blink(काष्ठा led_classdev *led_cdev,
			  अचिन्हित दीर्घ *delay_on, अचिन्हित दीर्घ *delay_off)
अणु
	अचिन्हित दीर्घ on_eighths;
	अचिन्हित दीर्घ off_eighths;

	/*
	 * The Dell LED delay is based on 125ms पूर्णांकervals.
	 * Need to round up to next पूर्णांकerval.
	 */

	on_eighths = DIV_ROUND_UP(*delay_on, 125);
	on_eighths = clamp_t(अचिन्हित दीर्घ, on_eighths, 1, 255);
	*delay_on = on_eighths * 125;

	off_eighths = DIV_ROUND_UP(*delay_off, 125);
	off_eighths = clamp_t(अचिन्हित दीर्घ, off_eighths, 1, 255);
	*delay_off = off_eighths * 125;

	led_blink(on_eighths, off_eighths);

	वापस 0;
पूर्ण

अटल काष्ठा led_classdev dell_led = अणु
	.name		= "dell::lid",
	.brightness	= LED_OFF,
	.max_brightness = 1,
	.brightness_set = dell_led_set,
	.blink_set	= dell_led_blink,
	.flags		= LED_CORE_SUSPENDRESUME,
पूर्ण;

अटल पूर्णांक __init dell_led_init(व्योम)
अणु
	पूर्णांक error = 0;

	अगर (!wmi_has_guid(DELL_LED_BIOS_GUID))
		वापस -ENODEV;

	error = led_off();
	अगर (error != 0)
		वापस -ENODEV;

	वापस led_classdev_रेजिस्टर(शून्य, &dell_led);
पूर्ण

अटल व्योम __निकास dell_led_निकास(व्योम)
अणु
	led_classdev_unरेजिस्टर(&dell_led);

	led_off();
पूर्ण

module_init(dell_led_init);
module_निकास(dell_led_निकास);
