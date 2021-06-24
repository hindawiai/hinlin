<शैली गुरु>
/*
 * Linux V4L2 radio driver क्रम the Grअगरfin radioSHARK2 USB radio receiver
 *
 * Note the radioSHARK2 offers the audio through a regular USB audio device,
 * this driver only handles the tuning.
 *
 * The info necessary to drive the shark2 was taken from the small userspace
 * shark2.c program by Hisaaki Shibata, which he kindly placed in the Public
 * Doमुख्य.
 *
 * Copyright (c) 2012 Hans de Goede <hdegoede@redhat.com>
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 */

#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/leds.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/usb.h>
#समावेश <linux/workqueue.h>
#समावेश <media/v4l2-device.h>
#समावेश "radio-tea5777.h"

#अगर defined(CONFIG_LEDS_CLASS) || \
    (defined(CONFIG_LEDS_CLASS_MODULE) && defined(CONFIG_RADIO_SHARK2_MODULE))
#घोषणा SHARK_USE_LEDS 1
#पूर्ण_अगर

MODULE_AUTHOR("Hans de Goede <hdegoede@redhat.com>");
MODULE_DESCRIPTION("Griffin radioSHARK2, USB radio receiver driver");
MODULE_LICENSE("GPL");

अटल पूर्णांक debug;
module_param(debug, पूर्णांक, 0);
MODULE_PARM_DESC(debug, "Debug level (0-1)");

#घोषणा SHARK_IN_EP		0x83
#घोषणा SHARK_OUT_EP		0x05

#घोषणा TB_LEN 7
#घोषणा DRV_NAME "radioshark2"

#घोषणा v4l2_dev_to_shark(d) container_of(d, काष्ठा shark_device, v4l2_dev)

क्रमागत अणु BLUE_LED, RED_LED, NO_LEDS पूर्ण;

काष्ठा shark_device अणु
	काष्ठा usb_device *usbdev;
	काष्ठा v4l2_device v4l2_dev;
	काष्ठा radio_tea5777 tea;

#अगर_घोषित SHARK_USE_LEDS
	काष्ठा work_काष्ठा led_work;
	काष्ठा led_classdev leds[NO_LEDS];
	अक्षर led_names[NO_LEDS][32];
	atomic_t brightness[NO_LEDS];
	अचिन्हित दीर्घ brightness_new;
#पूर्ण_अगर

	u8 *transfer_buffer;
पूर्ण;

अटल atomic_t shark_instance = ATOMIC_INIT(0);

अटल पूर्णांक shark_ग_लिखो_reg(काष्ठा radio_tea5777 *tea, u64 reg)
अणु
	काष्ठा shark_device *shark = tea->निजी_data;
	पूर्णांक i, res, actual_len;

	स_रखो(shark->transfer_buffer, 0, TB_LEN);
	shark->transfer_buffer[0] = 0x81; /* Write रेजिस्टर command */
	क्रम (i = 0; i < 6; i++)
		shark->transfer_buffer[i + 1] = (reg >> (40 - i * 8)) & 0xff;

	v4l2_dbg(1, debug, tea->v4l2_dev, "shark2-write: %*ph\n",
		 7, shark->transfer_buffer);

	res = usb_पूर्णांकerrupt_msg(shark->usbdev,
				usb_sndपूर्णांकpipe(shark->usbdev, SHARK_OUT_EP),
				shark->transfer_buffer, TB_LEN,
				&actual_len, 1000);
	अगर (res < 0) अणु
		v4l2_err(tea->v4l2_dev, "write error: %d\n", res);
		वापस res;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक shark_पढ़ो_reg(काष्ठा radio_tea5777 *tea, u32 *reg_ret)
अणु
	काष्ठा shark_device *shark = tea->निजी_data;
	पूर्णांक i, res, actual_len;
	u32 reg = 0;

	स_रखो(shark->transfer_buffer, 0, TB_LEN);
	shark->transfer_buffer[0] = 0x82;
	res = usb_पूर्णांकerrupt_msg(shark->usbdev,
				usb_sndपूर्णांकpipe(shark->usbdev, SHARK_OUT_EP),
				shark->transfer_buffer, TB_LEN,
				&actual_len, 1000);
	अगर (res < 0) अणु
		v4l2_err(tea->v4l2_dev, "request-read error: %d\n", res);
		वापस res;
	पूर्ण

	res = usb_पूर्णांकerrupt_msg(shark->usbdev,
				usb_rcvपूर्णांकpipe(shark->usbdev, SHARK_IN_EP),
				shark->transfer_buffer, TB_LEN,
				&actual_len, 1000);
	अगर (res < 0) अणु
		v4l2_err(tea->v4l2_dev, "read error: %d\n", res);
		वापस res;
	पूर्ण

	क्रम (i = 0; i < 3; i++)
		reg |= shark->transfer_buffer[i] << (16 - i * 8);

	v4l2_dbg(1, debug, tea->v4l2_dev, "shark2-read: %*ph\n",
		 3, shark->transfer_buffer);

	*reg_ret = reg;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा radio_tea5777_ops shark_tea_ops = अणु
	.ग_लिखो_reg = shark_ग_लिखो_reg,
	.पढ़ो_reg  = shark_पढ़ो_reg,
पूर्ण;

#अगर_घोषित SHARK_USE_LEDS
अटल व्योम shark_led_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा shark_device *shark =
		container_of(work, काष्ठा shark_device, led_work);
	पूर्णांक i, res, brightness, actual_len;

	क्रम (i = 0; i < 2; i++) अणु
		अगर (!test_and_clear_bit(i, &shark->brightness_new))
			जारी;

		brightness = atomic_पढ़ो(&shark->brightness[i]);
		स_रखो(shark->transfer_buffer, 0, TB_LEN);
		shark->transfer_buffer[0] = 0x83 + i;
		shark->transfer_buffer[1] = brightness;
		res = usb_पूर्णांकerrupt_msg(shark->usbdev,
					usb_sndपूर्णांकpipe(shark->usbdev,
						       SHARK_OUT_EP),
					shark->transfer_buffer, TB_LEN,
					&actual_len, 1000);
		अगर (res < 0)
			v4l2_err(&shark->v4l2_dev, "set LED %s error: %d\n",
				 shark->led_names[i], res);
	पूर्ण
पूर्ण

अटल व्योम shark_led_set_blue(काष्ठा led_classdev *led_cdev,
			       क्रमागत led_brightness value)
अणु
	काष्ठा shark_device *shark =
		container_of(led_cdev, काष्ठा shark_device, leds[BLUE_LED]);

	atomic_set(&shark->brightness[BLUE_LED], value);
	set_bit(BLUE_LED, &shark->brightness_new);
	schedule_work(&shark->led_work);
पूर्ण

अटल व्योम shark_led_set_red(काष्ठा led_classdev *led_cdev,
			      क्रमागत led_brightness value)
अणु
	काष्ठा shark_device *shark =
		container_of(led_cdev, काष्ठा shark_device, leds[RED_LED]);

	atomic_set(&shark->brightness[RED_LED], value);
	set_bit(RED_LED, &shark->brightness_new);
	schedule_work(&shark->led_work);
पूर्ण

अटल स्थिर काष्ठा led_classdev shark_led_ढाँचाs[NO_LEDS] = अणु
	[BLUE_LED] = अणु
		.name		= "%s:blue:",
		.brightness	= LED_OFF,
		.max_brightness = 127,
		.brightness_set = shark_led_set_blue,
	पूर्ण,
	[RED_LED] = अणु
		.name		= "%s:red:",
		.brightness	= LED_OFF,
		.max_brightness = 1,
		.brightness_set = shark_led_set_red,
	पूर्ण,
पूर्ण;

अटल पूर्णांक shark_रेजिस्टर_leds(काष्ठा shark_device *shark, काष्ठा device *dev)
अणु
	पूर्णांक i, retval;

	atomic_set(&shark->brightness[BLUE_LED], 127);
	INIT_WORK(&shark->led_work, shark_led_work);
	क्रम (i = 0; i < NO_LEDS; i++) अणु
		shark->leds[i] = shark_led_ढाँचाs[i];
		snम_लिखो(shark->led_names[i], माप(shark->led_names[0]),
			 shark->leds[i].name, shark->v4l2_dev.name);
		shark->leds[i].name = shark->led_names[i];
		retval = led_classdev_रेजिस्टर(dev, &shark->leds[i]);
		अगर (retval) अणु
			v4l2_err(&shark->v4l2_dev,
				 "couldn't register led: %s\n",
				 shark->led_names[i]);
			वापस retval;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम shark_unरेजिस्टर_leds(काष्ठा shark_device *shark)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < NO_LEDS; i++)
		led_classdev_unरेजिस्टर(&shark->leds[i]);

	cancel_work_sync(&shark->led_work);
पूर्ण

अटल अंतरभूत व्योम shark_resume_leds(काष्ठा shark_device *shark)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < NO_LEDS; i++)
		set_bit(i, &shark->brightness_new);

	schedule_work(&shark->led_work);
पूर्ण
#अन्यथा
अटल पूर्णांक shark_रेजिस्टर_leds(काष्ठा shark_device *shark, काष्ठा device *dev)
अणु
	v4l2_warn(&shark->v4l2_dev,
		  "CONFIG_LEDS_CLASS not enabled, LED support disabled\n");
	वापस 0;
पूर्ण
अटल अंतरभूत व्योम shark_unरेजिस्टर_leds(काष्ठा shark_device *shark) अणु पूर्ण
अटल अंतरभूत व्योम shark_resume_leds(काष्ठा shark_device *shark) अणु पूर्ण
#पूर्ण_अगर

अटल व्योम usb_shark_disconnect(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा v4l2_device *v4l2_dev = usb_get_पूर्णांकfdata(पूर्णांकf);
	काष्ठा shark_device *shark = v4l2_dev_to_shark(v4l2_dev);

	mutex_lock(&shark->tea.mutex);
	v4l2_device_disconnect(&shark->v4l2_dev);
	radio_tea5777_निकास(&shark->tea);
	mutex_unlock(&shark->tea.mutex);

	shark_unरेजिस्टर_leds(shark);

	v4l2_device_put(&shark->v4l2_dev);
पूर्ण

अटल व्योम usb_shark_release(काष्ठा v4l2_device *v4l2_dev)
अणु
	काष्ठा shark_device *shark = v4l2_dev_to_shark(v4l2_dev);

	v4l2_device_unरेजिस्टर(&shark->v4l2_dev);
	kमुक्त(shark->transfer_buffer);
	kमुक्त(shark);
पूर्ण

अटल पूर्णांक usb_shark_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकf,
			   स्थिर काष्ठा usb_device_id *id)
अणु
	काष्ठा shark_device *shark;
	पूर्णांक retval = -ENOMEM;

	shark = kzalloc(माप(काष्ठा shark_device), GFP_KERNEL);
	अगर (!shark)
		वापस retval;

	shark->transfer_buffer = kदो_स्मृति(TB_LEN, GFP_KERNEL);
	अगर (!shark->transfer_buffer)
		जाओ err_alloc_buffer;

	v4l2_device_set_name(&shark->v4l2_dev, DRV_NAME, &shark_instance);

	retval = shark_रेजिस्टर_leds(shark, &पूर्णांकf->dev);
	अगर (retval)
		जाओ err_reg_leds;

	shark->v4l2_dev.release = usb_shark_release;
	retval = v4l2_device_रेजिस्टर(&पूर्णांकf->dev, &shark->v4l2_dev);
	अगर (retval) अणु
		v4l2_err(&shark->v4l2_dev, "couldn't register v4l2_device\n");
		जाओ err_reg_dev;
	पूर्ण

	shark->usbdev = पूर्णांकerface_to_usbdev(पूर्णांकf);
	shark->tea.v4l2_dev = &shark->v4l2_dev;
	shark->tea.निजी_data = shark;
	shark->tea.ops = &shark_tea_ops;
	shark->tea.has_am = true;
	shark->tea.ग_लिखो_beक्रमe_पढ़ो = true;
	strscpy(shark->tea.card, "Griffin radioSHARK2",
		माप(shark->tea.card));
	usb_make_path(shark->usbdev, shark->tea.bus_info,
		माप(shark->tea.bus_info));

	retval = radio_tea5777_init(&shark->tea, THIS_MODULE);
	अगर (retval) अणु
		v4l2_err(&shark->v4l2_dev, "couldn't init tea5777\n");
		जाओ err_init_tea;
	पूर्ण

	वापस 0;

err_init_tea:
	v4l2_device_unरेजिस्टर(&shark->v4l2_dev);
err_reg_dev:
	shark_unरेजिस्टर_leds(shark);
err_reg_leds:
	kमुक्त(shark->transfer_buffer);
err_alloc_buffer:
	kमुक्त(shark);

	वापस retval;
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक usb_shark_suspend(काष्ठा usb_पूर्णांकerface *पूर्णांकf, pm_message_t message)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक usb_shark_resume(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा v4l2_device *v4l2_dev = usb_get_पूर्णांकfdata(पूर्णांकf);
	काष्ठा shark_device *shark = v4l2_dev_to_shark(v4l2_dev);
	पूर्णांक ret;

	mutex_lock(&shark->tea.mutex);
	ret = radio_tea5777_set_freq(&shark->tea);
	mutex_unlock(&shark->tea.mutex);

	shark_resume_leds(shark);

	वापस ret;
पूर्ण
#पूर्ण_अगर

/* Specअगरy the bcdDevice value, as the radioSHARK and radioSHARK2 share ids */
अटल स्थिर काष्ठा usb_device_id usb_shark_device_table[] = अणु
	अणु .match_flags = USB_DEVICE_ID_MATCH_DEVICE_AND_VERSION |
			 USB_DEVICE_ID_MATCH_INT_CLASS,
	  .idVenकरोr     = 0x077d,
	  .idProduct    = 0x627a,
	  .bcdDevice_lo = 0x0010,
	  .bcdDevice_hi = 0x0010,
	  .bInterfaceClass = 3,
	पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(usb, usb_shark_device_table);

अटल काष्ठा usb_driver usb_shark_driver = अणु
	.name			= DRV_NAME,
	.probe			= usb_shark_probe,
	.disconnect		= usb_shark_disconnect,
	.id_table		= usb_shark_device_table,
#अगर_घोषित CONFIG_PM
	.suspend		= usb_shark_suspend,
	.resume			= usb_shark_resume,
	.reset_resume		= usb_shark_resume,
#पूर्ण_अगर
पूर्ण;
module_usb_driver(usb_shark_driver);
