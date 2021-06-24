<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Line 6 Linux USB driver
 *
 * Copyright (C) 2004-2010 Markus Grabner (grabner@icg.tugraz.at)
 */

#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/usb.h>
#समावेश <linux/रुको.h>
#समावेश <linux/module.h>
#समावेश <sound/core.h>

#समावेश "driver.h"

#घोषणा VARIAX_STARTUP_DELAY1 1000
#घोषणा VARIAX_STARTUP_DELAY3 100
#घोषणा VARIAX_STARTUP_DELAY4 100

/*
	Stages of Variax startup procedure
*/
क्रमागत अणु
	VARIAX_STARTUP_VERSIONREQ,
	VARIAX_STARTUP_ACTIVATE,
	VARIAX_STARTUP_SETUP,
पूर्ण;

क्रमागत अणु
	LINE6_PODXTLIVE_VARIAX,
	LINE6_VARIAX
पूर्ण;

काष्ठा usb_line6_variax अणु
	/* Generic Line 6 USB data */
	काष्ठा usb_line6 line6;

	/* Buffer क्रम activation code */
	अचिन्हित अक्षर *buffer_activate;

	/* Current progress in startup procedure */
	पूर्णांक startup_progress;
पूर्ण;

#घोषणा line6_to_variax(x)	container_of(x, काष्ठा usb_line6_variax, line6)

#घोषणा VARIAX_OFFSET_ACTIVATE 7

/*
	This message is sent by the device during initialization and identअगरies
	the connected guitar version.
*/
अटल स्थिर अक्षर variax_init_version[] = अणु
	0xf0, 0x7e, 0x7f, 0x06, 0x02, 0x00, 0x01, 0x0c,
	0x07, 0x00, 0x00, 0x00
पूर्ण;

/*
	This message is the last one sent by the device during initialization.
*/
अटल स्थिर अक्षर variax_init_करोne[] = अणु
	0xf0, 0x00, 0x01, 0x0c, 0x07, 0x00, 0x6b
पूर्ण;

अटल स्थिर अक्षर variax_activate[] = अणु
	0xf0, 0x00, 0x01, 0x0c, 0x07, 0x00, 0x2a, 0x01,
	0xf7
पूर्ण;

अटल व्योम variax_activate_async(काष्ठा usb_line6_variax *variax, पूर्णांक a)
अणु
	variax->buffer_activate[VARIAX_OFFSET_ACTIVATE] = a;
	line6_send_raw_message_async(&variax->line6, variax->buffer_activate,
				     माप(variax_activate));
पूर्ण

/*
	Variax startup procedure.
	This is a sequence of functions with special requirements (e.g., must
	not run immediately after initialization, must not run in पूर्णांकerrupt
	context). After the last one has finished, the device is पढ़ोy to use.
*/

अटल व्योम variax_startup(काष्ठा usb_line6 *line6)
अणु
	काष्ठा usb_line6_variax *variax = line6_to_variax(line6);

	चयन (variax->startup_progress) अणु
	हाल VARIAX_STARTUP_VERSIONREQ:
		/* repeat request until getting the response */
		schedule_delayed_work(&line6->startup_work,
				      msecs_to_jअगरfies(VARIAX_STARTUP_DELAY1));
		/* request firmware version: */
		line6_version_request_async(line6);
		अवरोध;
	हाल VARIAX_STARTUP_ACTIVATE:
		/* activate device: */
		variax_activate_async(variax, 1);
		variax->startup_progress = VARIAX_STARTUP_SETUP;
		schedule_delayed_work(&line6->startup_work,
				      msecs_to_jअगरfies(VARIAX_STARTUP_DELAY4));
		अवरोध;
	हाल VARIAX_STARTUP_SETUP:
		/* ALSA audio पूर्णांकerface: */
		snd_card_रेजिस्टर(variax->line6.card);
		अवरोध;
	पूर्ण
पूर्ण

/*
	Process a completely received message.
*/
अटल व्योम line6_variax_process_message(काष्ठा usb_line6 *line6)
अणु
	काष्ठा usb_line6_variax *variax = line6_to_variax(line6);
	स्थिर अचिन्हित अक्षर *buf = variax->line6.buffer_message;

	चयन (buf[0]) अणु
	हाल LINE6_RESET:
		dev_info(variax->line6.अगरcdev, "VARIAX reset\n");
		अवरोध;

	हाल LINE6_SYSEX_BEGIN:
		अगर (स_भेद(buf + 1, variax_init_version + 1,
			   माप(variax_init_version) - 1) == 0) अणु
			अगर (variax->startup_progress >= VARIAX_STARTUP_ACTIVATE)
				अवरोध;
			variax->startup_progress = VARIAX_STARTUP_ACTIVATE;
			cancel_delayed_work(&line6->startup_work);
			schedule_delayed_work(&line6->startup_work,
					      msecs_to_jअगरfies(VARIAX_STARTUP_DELAY3));
		पूर्ण अन्यथा अगर (स_भेद(buf + 1, variax_init_करोne + 1,
				  माप(variax_init_करोne) - 1) == 0) अणु
			/* notअगरy of complete initialization: */
			अगर (variax->startup_progress >= VARIAX_STARTUP_SETUP)
				अवरोध;
			cancel_delayed_work(&line6->startup_work);
			schedule_delayed_work(&line6->startup_work, 0);
		पूर्ण
		अवरोध;
	पूर्ण
पूर्ण

/*
	Variax deकाष्ठाor.
*/
अटल व्योम line6_variax_disconnect(काष्ठा usb_line6 *line6)
अणु
	काष्ठा usb_line6_variax *variax = line6_to_variax(line6);

	kमुक्त(variax->buffer_activate);
पूर्ण

/*
	 Try to init workbench device.
*/
अटल पूर्णांक variax_init(काष्ठा usb_line6 *line6,
		       स्थिर काष्ठा usb_device_id *id)
अणु
	काष्ठा usb_line6_variax *variax = line6_to_variax(line6);

	line6->process_message = line6_variax_process_message;
	line6->disconnect = line6_variax_disconnect;
	line6->startup = variax_startup;

	/* initialize USB buffers: */
	variax->buffer_activate = kmemdup(variax_activate,
					  माप(variax_activate), GFP_KERNEL);

	अगर (variax->buffer_activate == शून्य)
		वापस -ENOMEM;

	/* initiate startup procedure: */
	schedule_delayed_work(&line6->startup_work,
			      msecs_to_jअगरfies(VARIAX_STARTUP_DELAY1));
	वापस 0;
पूर्ण

#घोषणा LINE6_DEVICE(prod) USB_DEVICE(0x0e41, prod)
#घोषणा LINE6_IF_NUM(prod, n) USB_DEVICE_INTERFACE_NUMBER(0x0e41, prod, n)

/* table of devices that work with this driver */
अटल स्थिर काष्ठा usb_device_id variax_id_table[] = अणु
	अणु LINE6_IF_NUM(0x4650, 1), .driver_info = LINE6_PODXTLIVE_VARIAX पूर्ण,
	अणु LINE6_DEVICE(0x534d),    .driver_info = LINE6_VARIAX पूर्ण,
	अणुपूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(usb, variax_id_table);

अटल स्थिर काष्ठा line6_properties variax_properties_table[] = अणु
	[LINE6_PODXTLIVE_VARIAX] = अणु
		.id = "PODxtLive",
		.name = "PODxt Live",
		.capabilities	= LINE6_CAP_CONTROL
				| LINE6_CAP_CONTROL_MIDI,
		.altsetting = 1,
		.ep_ctrl_r = 0x86,
		.ep_ctrl_w = 0x05,
		.ep_audio_r = 0x82,
		.ep_audio_w = 0x01,
	पूर्ण,
	[LINE6_VARIAX] = अणु
		.id = "Variax",
		.name = "Variax Workbench",
		.capabilities	= LINE6_CAP_CONTROL
				| LINE6_CAP_CONTROL_MIDI,
		.altsetting = 1,
		.ep_ctrl_r = 0x82,
		.ep_ctrl_w = 0x01,
		/* no audio channel */
	पूर्ण
पूर्ण;

/*
	Probe USB device.
*/
अटल पूर्णांक variax_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकerface,
			स्थिर काष्ठा usb_device_id *id)
अणु
	वापस line6_probe(पूर्णांकerface, id, "Line6-Variax",
			   &variax_properties_table[id->driver_info],
			   variax_init, माप(काष्ठा usb_line6_variax));
पूर्ण

अटल काष्ठा usb_driver variax_driver = अणु
	.name = KBUILD_MODNAME,
	.probe = variax_probe,
	.disconnect = line6_disconnect,
#अगर_घोषित CONFIG_PM
	.suspend = line6_suspend,
	.resume = line6_resume,
	.reset_resume = line6_resume,
#पूर्ण_अगर
	.id_table = variax_id_table,
पूर्ण;

module_usb_driver(variax_driver);

MODULE_DESCRIPTION("Variax Workbench USB driver");
MODULE_LICENSE("GPL");
