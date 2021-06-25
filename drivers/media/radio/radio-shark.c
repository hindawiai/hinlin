<शैली गुरु>
/*
 * Linux V4L2 radio driver क्रम the Grअगरfin radioSHARK USB radio receiver
 *
 * Note the radioSHARK offers the audio through a regular USB audio device,
 * this driver only handles the tuning.
 *
 * The info necessary to drive the shark was taken from the small userspace
 * shark.c program by Michael Rolig, which he kindly placed in the Public
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
#समावेश <media/drv-पूर्णांकf/tea575x.h>

#अगर defined(CONFIG_LEDS_CLASS) || \
    (defined(CONFIG_LEDS_CLASS_MODULE) && defined(CONFIG_RADIO_SHARK_MODULE))
#घोषणा SHARK_USE_LEDS 1
#पूर्ण_अगर

/*
 * Version Inक्रमmation
 */
MODULE_AUTHOR("Hans de Goede <hdegoede@redhat.com>");
MODULE_DESCRIPTION("Griffin radioSHARK, USB radio receiver driver");
MODULE_LICENSE("GPL");

#घोषणा SHARK_IN_EP		0x83
#घोषणा SHARK_OUT_EP		0x05

#घोषणा TEA575X_BIT_MONO	(1<<22)		/* 0 = stereo, 1 = mono */
#घोषणा TEA575X_BIT_BAND_MASK	(3<<20)
#घोषणा TEA575X_BIT_BAND_FM	(0<<20)

#घोषणा TB_LEN 6
#घोषणा DRV_NAME "radioshark"

#घोषणा v4l2_dev_to_shark(d) container_of(d, काष्ठा shark_device, v4l2_dev)

/* Note BLUE_IS_PULSE comes after NO_LEDS as it is a status bit, not a LED */
क्रमागत अणु BLUE_LED, BLUE_PULSE_LED, RED_LED, NO_LEDS, BLUE_IS_PULSE पूर्ण;

काष्ठा shark_device अणु
	काष्ठा usb_device *usbdev;
	काष्ठा v4l2_device v4l2_dev;
	काष्ठा snd_tea575x tea;

#अगर_घोषित SHARK_USE_LEDS
	काष्ठा work_काष्ठा led_work;
	काष्ठा led_classdev leds[NO_LEDS];
	अक्षर led_names[NO_LEDS][32];
	atomic_t brightness[NO_LEDS];
	अचिन्हित दीर्घ brightness_new;
#पूर्ण_अगर

	u8 *transfer_buffer;
	u32 last_val;
पूर्ण;

अटल atomic_t shark_instance = ATOMIC_INIT(0);

अटल व्योम shark_ग_लिखो_val(काष्ठा snd_tea575x *tea, u32 val)
अणु
	काष्ठा shark_device *shark = tea->निजी_data;
	पूर्णांक i, res, actual_len;

	/* Aव्योम unnecessary (slow) USB transfers */
	अगर (shark->last_val == val)
		वापस;

	स_रखो(shark->transfer_buffer, 0, TB_LEN);
	shark->transfer_buffer[0] = 0xc0; /* Write shअगरt रेजिस्टर command */
	क्रम (i = 0; i < 4; i++)
		shark->transfer_buffer[i] |= (val >> (24 - i * 8)) & 0xff;

	res = usb_पूर्णांकerrupt_msg(shark->usbdev,
				usb_sndपूर्णांकpipe(shark->usbdev, SHARK_OUT_EP),
				shark->transfer_buffer, TB_LEN,
				&actual_len, 1000);
	अगर (res >= 0)
		shark->last_val = val;
	अन्यथा
		v4l2_err(&shark->v4l2_dev, "set-freq error: %d\n", res);
पूर्ण

अटल u32 shark_पढ़ो_val(काष्ठा snd_tea575x *tea)
अणु
	काष्ठा shark_device *shark = tea->निजी_data;
	पूर्णांक i, res, actual_len;
	u32 val = 0;

	स_रखो(shark->transfer_buffer, 0, TB_LEN);
	shark->transfer_buffer[0] = 0x80;
	res = usb_पूर्णांकerrupt_msg(shark->usbdev,
				usb_sndपूर्णांकpipe(shark->usbdev, SHARK_OUT_EP),
				shark->transfer_buffer, TB_LEN,
				&actual_len, 1000);
	अगर (res < 0) अणु
		v4l2_err(&shark->v4l2_dev, "request-status error: %d\n", res);
		वापस shark->last_val;
	पूर्ण

	res = usb_पूर्णांकerrupt_msg(shark->usbdev,
				usb_rcvपूर्णांकpipe(shark->usbdev, SHARK_IN_EP),
				shark->transfer_buffer, TB_LEN,
				&actual_len, 1000);
	अगर (res < 0) अणु
		v4l2_err(&shark->v4l2_dev, "get-status error: %d\n", res);
		वापस shark->last_val;
	पूर्ण

	क्रम (i = 0; i < 4; i++)
		val |= shark->transfer_buffer[i] << (24 - i * 8);

	shark->last_val = val;

	/*
	 * The shark करोes not allow actually पढ़ोing the stereo / mono pin :(
	 * So assume that when we're tuned to an FM station and mono has not
	 * been requested, that we're receiving stereo.
	 */
	अगर (((val & TEA575X_BIT_BAND_MASK) == TEA575X_BIT_BAND_FM) &&
	    !(val & TEA575X_BIT_MONO))
		shark->tea.stereo = true;
	अन्यथा
		shark->tea.stereo = false;

	वापस val;
पूर्ण

अटल स्थिर काष्ठा snd_tea575x_ops shark_tea_ops = अणु
	.ग_लिखो_val = shark_ग_लिखो_val,
	.पढ़ो_val  = shark_पढ़ो_val,
पूर्ण;

#अगर_घोषित SHARK_USE_LEDS
अटल व्योम shark_led_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा shark_device *shark =
		container_of(work, काष्ठा shark_device, led_work);
	पूर्णांक i, res, brightness, actual_len;

	क्रम (i = 0; i < 3; i++) अणु
		अगर (!test_and_clear_bit(i, &shark->brightness_new))
			जारी;

		brightness = atomic_पढ़ो(&shark->brightness[i]);
		स_रखो(shark->transfer_buffer, 0, TB_LEN);
		अगर (i != RED_LED) अणु
			shark->transfer_buffer[0] = 0xA0 + i;
			shark->transfer_buffer[1] = brightness;
		पूर्ण अन्यथा
			shark->transfer_buffer[0] = brightness ? 0xA9 : 0xA8;
		res = usb_पूर्णांकerrupt_msg(shark->usbdev,
					usb_sndपूर्णांकpipe(shark->usbdev, 0x05),
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
	clear_bit(BLUE_IS_PULSE, &shark->brightness_new);
	schedule_work(&shark->led_work);
पूर्ण

अटल व्योम shark_led_set_blue_pulse(काष्ठा led_classdev *led_cdev,
				     क्रमागत led_brightness value)
अणु
	काष्ठा shark_device *shark = container_of(led_cdev,
				काष्ठा shark_device, leds[BLUE_PULSE_LED]);

	atomic_set(&shark->brightness[BLUE_PULSE_LED], 256 - value);
	set_bit(BLUE_PULSE_LED, &shark->brightness_new);
	set_bit(BLUE_IS_PULSE, &shark->brightness_new);
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
	[BLUE_PULSE_LED] = अणु
		.name		= "%s:blue-pulse:",
		.brightness	= LED_OFF,
		.max_brightness = 255,
		.brightness_set = shark_led_set_blue_pulse,
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
	अगर (test_bit(BLUE_IS_PULSE, &shark->brightness_new))
		set_bit(BLUE_PULSE_LED, &shark->brightness_new);
	अन्यथा
		set_bit(BLUE_LED, &shark->brightness_new);
	set_bit(RED_LED, &shark->brightness_new);
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
	snd_tea575x_निकास(&shark->tea);
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
	shark->tea.radio_nr = -1;
	shark->tea.ops = &shark_tea_ops;
	shark->tea.cannot_mute = true;
	shark->tea.has_am = true;
	strscpy(shark->tea.card, "Griffin radioSHARK",
		माप(shark->tea.card));
	usb_make_path(shark->usbdev, shark->tea.bus_info,
		माप(shark->tea.bus_info));

	retval = snd_tea575x_init(&shark->tea, THIS_MODULE);
	अगर (retval) अणु
		v4l2_err(&shark->v4l2_dev, "couldn't init tea5757\n");
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

	mutex_lock(&shark->tea.mutex);
	snd_tea575x_set_freq(&shark->tea);
	mutex_unlock(&shark->tea.mutex);

	shark_resume_leds(shark);

	वापस 0;
पूर्ण
#पूर्ण_अगर

/* Specअगरy the bcdDevice value, as the radioSHARK and radioSHARK2 share ids */
अटल स्थिर काष्ठा usb_device_id usb_shark_device_table[] = अणु
	अणु .match_flags = USB_DEVICE_ID_MATCH_DEVICE_AND_VERSION |
			 USB_DEVICE_ID_MATCH_INT_CLASS,
	  .idVenकरोr     = 0x077d,
	  .idProduct    = 0x627a,
	  .bcdDevice_lo = 0x0001,
	  .bcdDevice_hi = 0x0001,
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
