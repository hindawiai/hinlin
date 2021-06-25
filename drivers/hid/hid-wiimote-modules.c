<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Device Modules क्रम Nपूर्णांकenकरो Wii / Wii U HID Driver
 * Copyright (c) 2011-2013 David Herrmann <dh.herrmann@gmail.com>
 */

/*
 */

/*
 * Wiimote Modules
 * Nपूर्णांकenकरो devices provide dअगरferent peripherals and many new devices lack
 * initial features like the IR camera. Thereक्रमe, each peripheral device is
 * implemented as an independent module and we probe on each device only the
 * modules क्रम the hardware that really is available.
 *
 * Module registration is sequential. Unregistration is करोne in reverse order.
 * After device detection, the needed modules are loaded. Users can trigger
 * re-detection which causes all modules to be unloaded and then reload the
 * modules क्रम the new detected device.
 *
 * wdata->input is a shared input device. It is always initialized prior to
 * module registration. If at least one रेजिस्टरed module is marked as
 * WIIMOD_FLAG_INPUT, then the input device will get रेजिस्टरed after all
 * modules were रेजिस्टरed.
 * Please note that it is unरेजिस्टरed _beक्रमe_ the "remove" callbacks are
 * called. This guarantees that no input पूर्णांकeraction is करोne, anymore. However,
 * the wiimote core keeps a reference to the input device so it is मुक्तd only
 * after all modules were हटाओd. It is safe to send events to unरेजिस्टरed
 * input devices.
 */

#समावेश <linux/device.h>
#समावेश <linux/hid.h>
#समावेश <linux/input.h>
#समावेश <linux/spinlock.h>
#समावेश "hid-wiimote.h"

/*
 * Keys
 * The initial Wii Remote provided a bunch of buttons that are reported as
 * part of the core protocol. Many later devices dropped these and report
 * invalid data in the core button reports. Load this only on devices which
 * correctly send button reports.
 * It uses the shared input device.
 */

अटल स्थिर __u16 wiimod_keys_map[] = अणु
	KEY_LEFT,	/* WIIPROTO_KEY_LEFT */
	KEY_RIGHT,	/* WIIPROTO_KEY_RIGHT */
	KEY_UP,		/* WIIPROTO_KEY_UP */
	KEY_DOWN,	/* WIIPROTO_KEY_DOWN */
	KEY_NEXT,	/* WIIPROTO_KEY_PLUS */
	KEY_PREVIOUS,	/* WIIPROTO_KEY_MINUS */
	BTN_1,		/* WIIPROTO_KEY_ONE */
	BTN_2,		/* WIIPROTO_KEY_TWO */
	BTN_A,		/* WIIPROTO_KEY_A */
	BTN_B,		/* WIIPROTO_KEY_B */
	BTN_MODE,	/* WIIPROTO_KEY_HOME */
पूर्ण;

अटल व्योम wiimod_keys_in_keys(काष्ठा wiimote_data *wdata, स्थिर __u8 *keys)
अणु
	input_report_key(wdata->input, wiimod_keys_map[WIIPROTO_KEY_LEFT],
							!!(keys[0] & 0x01));
	input_report_key(wdata->input, wiimod_keys_map[WIIPROTO_KEY_RIGHT],
							!!(keys[0] & 0x02));
	input_report_key(wdata->input, wiimod_keys_map[WIIPROTO_KEY_DOWN],
							!!(keys[0] & 0x04));
	input_report_key(wdata->input, wiimod_keys_map[WIIPROTO_KEY_UP],
							!!(keys[0] & 0x08));
	input_report_key(wdata->input, wiimod_keys_map[WIIPROTO_KEY_PLUS],
							!!(keys[0] & 0x10));
	input_report_key(wdata->input, wiimod_keys_map[WIIPROTO_KEY_TWO],
							!!(keys[1] & 0x01));
	input_report_key(wdata->input, wiimod_keys_map[WIIPROTO_KEY_ONE],
							!!(keys[1] & 0x02));
	input_report_key(wdata->input, wiimod_keys_map[WIIPROTO_KEY_B],
							!!(keys[1] & 0x04));
	input_report_key(wdata->input, wiimod_keys_map[WIIPROTO_KEY_A],
							!!(keys[1] & 0x08));
	input_report_key(wdata->input, wiimod_keys_map[WIIPROTO_KEY_MINUS],
							!!(keys[1] & 0x10));
	input_report_key(wdata->input, wiimod_keys_map[WIIPROTO_KEY_HOME],
							!!(keys[1] & 0x80));
	input_sync(wdata->input);
पूर्ण

अटल पूर्णांक wiimod_keys_probe(स्थिर काष्ठा wiimod_ops *ops,
			     काष्ठा wiimote_data *wdata)
अणु
	अचिन्हित पूर्णांक i;

	set_bit(EV_KEY, wdata->input->evbit);
	क्रम (i = 0; i < WIIPROTO_KEY_COUNT; ++i)
		set_bit(wiimod_keys_map[i], wdata->input->keybit);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा wiimod_ops wiimod_keys = अणु
	.flags = WIIMOD_FLAG_INPUT,
	.arg = 0,
	.probe = wiimod_keys_probe,
	.हटाओ = शून्य,
	.in_keys = wiimod_keys_in_keys,
पूर्ण;

/*
 * Rumble
 * Nearly all devices provide a rumble feature. A small motor क्रम
 * क्रमce-feedback effects. We provide an FF_RUMBLE memless ff device on the
 * shared input device अगर this module is loaded.
 * The rumble motor is controlled via a flag on almost every output report so
 * the wiimote core handles the rumble flag. But अगर a device करोesn't provide
 * the rumble motor, this flag shouldn't be set.
 */

/* used by wiimod_rumble and wiipro_rumble */
अटल व्योम wiimod_rumble_worker(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा wiimote_data *wdata = container_of(work, काष्ठा wiimote_data,
						  rumble_worker);

	spin_lock_irq(&wdata->state.lock);
	wiiproto_req_rumble(wdata, wdata->state.cache_rumble);
	spin_unlock_irq(&wdata->state.lock);
पूर्ण

अटल पूर्णांक wiimod_rumble_play(काष्ठा input_dev *dev, व्योम *data,
			      काष्ठा ff_effect *eff)
अणु
	काष्ठा wiimote_data *wdata = input_get_drvdata(dev);
	__u8 value;

	/*
	 * The wiimote supports only a single rumble motor so अगर any magnitude
	 * is set to non-zero then we start the rumble motor. If both are set to
	 * zero, we stop the rumble motor.
	 */

	अगर (eff->u.rumble.strong_magnitude || eff->u.rumble.weak_magnitude)
		value = 1;
	अन्यथा
		value = 0;

	/* Locking state.lock here might deadlock with input_event() calls.
	 * schedule_work acts as barrier. Merging multiple changes is fine. */
	wdata->state.cache_rumble = value;
	schedule_work(&wdata->rumble_worker);

	वापस 0;
पूर्ण

अटल पूर्णांक wiimod_rumble_probe(स्थिर काष्ठा wiimod_ops *ops,
			       काष्ठा wiimote_data *wdata)
अणु
	INIT_WORK(&wdata->rumble_worker, wiimod_rumble_worker);

	set_bit(FF_RUMBLE, wdata->input->ffbit);
	अगर (input_ff_create_memless(wdata->input, शून्य, wiimod_rumble_play))
		वापस -ENOMEM;

	वापस 0;
पूर्ण

अटल व्योम wiimod_rumble_हटाओ(स्थिर काष्ठा wiimod_ops *ops,
				 काष्ठा wiimote_data *wdata)
अणु
	अचिन्हित दीर्घ flags;

	cancel_work_sync(&wdata->rumble_worker);

	spin_lock_irqsave(&wdata->state.lock, flags);
	wiiproto_req_rumble(wdata, 0);
	spin_unlock_irqrestore(&wdata->state.lock, flags);
पूर्ण

अटल स्थिर काष्ठा wiimod_ops wiimod_rumble = अणु
	.flags = WIIMOD_FLAG_INPUT,
	.arg = 0,
	.probe = wiimod_rumble_probe,
	.हटाओ = wiimod_rumble_हटाओ,
पूर्ण;

/*
 * Battery
 * 1 byte of battery capacity inक्रमmation is sent aदीर्घ every protocol status
 * report. The wiimote core caches it but we try to update it on every
 * user-space request.
 * This is supported by nearly every device so it's almost always enabled.
 */

अटल क्रमागत घातer_supply_property wiimod_battery_props[] = अणु
	POWER_SUPPLY_PROP_CAPACITY,
	POWER_SUPPLY_PROP_SCOPE,
पूर्ण;

अटल पूर्णांक wiimod_battery_get_property(काष्ठा घातer_supply *psy,
				       क्रमागत घातer_supply_property psp,
				       जोड़ घातer_supply_propval *val)
अणु
	काष्ठा wiimote_data *wdata = घातer_supply_get_drvdata(psy);
	पूर्णांक ret = 0, state;
	अचिन्हित दीर्घ flags;

	अगर (psp == POWER_SUPPLY_PROP_SCOPE) अणु
		val->पूर्णांकval = POWER_SUPPLY_SCOPE_DEVICE;
		वापस 0;
	पूर्ण अन्यथा अगर (psp != POWER_SUPPLY_PROP_CAPACITY) अणु
		वापस -EINVAL;
	पूर्ण

	ret = wiimote_cmd_acquire(wdata);
	अगर (ret)
		वापस ret;

	spin_lock_irqsave(&wdata->state.lock, flags);
	wiimote_cmd_set(wdata, WIIPROTO_REQ_SREQ, 0);
	wiiproto_req_status(wdata);
	spin_unlock_irqrestore(&wdata->state.lock, flags);

	wiimote_cmd_रुको(wdata);
	wiimote_cmd_release(wdata);

	spin_lock_irqsave(&wdata->state.lock, flags);
	state = wdata->state.cmd_battery;
	spin_unlock_irqrestore(&wdata->state.lock, flags);

	val->पूर्णांकval = state * 100 / 255;
	वापस ret;
पूर्ण

अटल पूर्णांक wiimod_battery_probe(स्थिर काष्ठा wiimod_ops *ops,
				काष्ठा wiimote_data *wdata)
अणु
	काष्ठा घातer_supply_config psy_cfg = अणु .drv_data = wdata, पूर्ण;
	पूर्णांक ret;

	wdata->battery_desc.properties = wiimod_battery_props;
	wdata->battery_desc.num_properties = ARRAY_SIZE(wiimod_battery_props);
	wdata->battery_desc.get_property = wiimod_battery_get_property;
	wdata->battery_desc.type = POWER_SUPPLY_TYPE_BATTERY;
	wdata->battery_desc.use_क्रम_apm = 0;
	wdata->battery_desc.name = kaप्र_लिखो(GFP_KERNEL, "wiimote_battery_%s",
					     wdata->hdev->uniq);
	अगर (!wdata->battery_desc.name)
		वापस -ENOMEM;

	wdata->battery = घातer_supply_रेजिस्टर(&wdata->hdev->dev,
					       &wdata->battery_desc,
					       &psy_cfg);
	अगर (IS_ERR(wdata->battery)) अणु
		hid_err(wdata->hdev, "cannot register battery device\n");
		ret = PTR_ERR(wdata->battery);
		जाओ err_मुक्त;
	पूर्ण

	घातer_supply_घातers(wdata->battery, &wdata->hdev->dev);
	वापस 0;

err_मुक्त:
	kमुक्त(wdata->battery_desc.name);
	wdata->battery_desc.name = शून्य;
	वापस ret;
पूर्ण

अटल व्योम wiimod_battery_हटाओ(स्थिर काष्ठा wiimod_ops *ops,
				  काष्ठा wiimote_data *wdata)
अणु
	अगर (!wdata->battery_desc.name)
		वापस;

	घातer_supply_unरेजिस्टर(wdata->battery);
	kमुक्त(wdata->battery_desc.name);
	wdata->battery_desc.name = शून्य;
पूर्ण

अटल स्थिर काष्ठा wiimod_ops wiimod_battery = अणु
	.flags = 0,
	.arg = 0,
	.probe = wiimod_battery_probe,
	.हटाओ = wiimod_battery_हटाओ,
पूर्ण;

/*
 * LED
 * 0 to 4 player LEDs are supported by devices. The "arg" field of the
 * wiimod_ops काष्ठाure specअगरies which LED this module controls. This allows
 * to रेजिस्टर a limited number of LEDs.
 * State is managed by wiimote core.
 */

अटल क्रमागत led_brightness wiimod_led_get(काष्ठा led_classdev *led_dev)
अणु
	काष्ठा device *dev = led_dev->dev->parent;
	काष्ठा wiimote_data *wdata = dev_to_wii(dev);
	पूर्णांक i;
	अचिन्हित दीर्घ flags;
	bool value = false;

	क्रम (i = 0; i < 4; ++i) अणु
		अगर (wdata->leds[i] == led_dev) अणु
			spin_lock_irqsave(&wdata->state.lock, flags);
			value = wdata->state.flags & WIIPROTO_FLAG_LED(i + 1);
			spin_unlock_irqrestore(&wdata->state.lock, flags);
			अवरोध;
		पूर्ण
	पूर्ण

	वापस value ? LED_FULL : LED_OFF;
पूर्ण

अटल व्योम wiimod_led_set(काष्ठा led_classdev *led_dev,
			   क्रमागत led_brightness value)
अणु
	काष्ठा device *dev = led_dev->dev->parent;
	काष्ठा wiimote_data *wdata = dev_to_wii(dev);
	पूर्णांक i;
	अचिन्हित दीर्घ flags;
	__u8 state, flag;

	क्रम (i = 0; i < 4; ++i) अणु
		अगर (wdata->leds[i] == led_dev) अणु
			flag = WIIPROTO_FLAG_LED(i + 1);
			spin_lock_irqsave(&wdata->state.lock, flags);
			state = wdata->state.flags;
			अगर (value == LED_OFF)
				wiiproto_req_leds(wdata, state & ~flag);
			अन्यथा
				wiiproto_req_leds(wdata, state | flag);
			spin_unlock_irqrestore(&wdata->state.lock, flags);
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक wiimod_led_probe(स्थिर काष्ठा wiimod_ops *ops,
			    काष्ठा wiimote_data *wdata)
अणु
	काष्ठा device *dev = &wdata->hdev->dev;
	माप_प्रकार namesz = म_माप(dev_name(dev)) + 9;
	काष्ठा led_classdev *led;
	अचिन्हित दीर्घ flags;
	अक्षर *name;
	पूर्णांक ret;

	led = kzalloc(माप(काष्ठा led_classdev) + namesz, GFP_KERNEL);
	अगर (!led)
		वापस -ENOMEM;

	name = (व्योम*)&led[1];
	snम_लिखो(name, namesz, "%s:blue:p%lu", dev_name(dev), ops->arg);
	led->name = name;
	led->brightness = 0;
	led->max_brightness = 1;
	led->brightness_get = wiimod_led_get;
	led->brightness_set = wiimod_led_set;

	wdata->leds[ops->arg] = led;
	ret = led_classdev_रेजिस्टर(dev, led);
	अगर (ret)
		जाओ err_मुक्त;

	/* enable LED1 to stop initial LED-blinking */
	अगर (ops->arg == 0) अणु
		spin_lock_irqsave(&wdata->state.lock, flags);
		wiiproto_req_leds(wdata, WIIPROTO_FLAG_LED1);
		spin_unlock_irqrestore(&wdata->state.lock, flags);
	पूर्ण

	वापस 0;

err_मुक्त:
	wdata->leds[ops->arg] = शून्य;
	kमुक्त(led);
	वापस ret;
पूर्ण

अटल व्योम wiimod_led_हटाओ(स्थिर काष्ठा wiimod_ops *ops,
			      काष्ठा wiimote_data *wdata)
अणु
	अगर (!wdata->leds[ops->arg])
		वापस;

	led_classdev_unरेजिस्टर(wdata->leds[ops->arg]);
	kमुक्त(wdata->leds[ops->arg]);
	wdata->leds[ops->arg] = शून्य;
पूर्ण

अटल स्थिर काष्ठा wiimod_ops wiimod_leds[4] = अणु
	अणु
		.flags = 0,
		.arg = 0,
		.probe = wiimod_led_probe,
		.हटाओ = wiimod_led_हटाओ,
	पूर्ण,
	अणु
		.flags = 0,
		.arg = 1,
		.probe = wiimod_led_probe,
		.हटाओ = wiimod_led_हटाओ,
	पूर्ण,
	अणु
		.flags = 0,
		.arg = 2,
		.probe = wiimod_led_probe,
		.हटाओ = wiimod_led_हटाओ,
	पूर्ण,
	अणु
		.flags = 0,
		.arg = 3,
		.probe = wiimod_led_probe,
		.हटाओ = wiimod_led_हटाओ,
	पूर्ण,
पूर्ण;

/*
 * Accelerometer
 * 3 axis accelerometer data is part of nearly all DRMs. If not supported by a
 * device, it's mostly cleared to 0. This module parses this data and provides
 * it via a separate input device.
 */

अटल व्योम wiimod_accel_in_accel(काष्ठा wiimote_data *wdata,
				  स्थिर __u8 *accel)
अणु
	__u16 x, y, z;

	अगर (!(wdata->state.flags & WIIPROTO_FLAG_ACCEL))
		वापस;

	/*
	 * payload is: BB BB XX YY ZZ
	 * Accelerometer data is encoded पूर्णांकo 3 10bit values. XX, YY and ZZ
	 * contain the upper 8 bits of each value. The lower 2 bits are
	 * contained in the buttons data BB BB.
	 * Bits 6 and 7 of the first buttons byte BB is the lower 2 bits of the
	 * X accel value. Bit 5 of the second buttons byte is the 2nd bit of Y
	 * accel value and bit 6 is the second bit of the Z value.
	 * The first bit of Y and Z values is not available and always set to 0.
	 * 0x200 is वापसed on no movement.
	 */

	x = accel[2] << 2;
	y = accel[3] << 2;
	z = accel[4] << 2;

	x |= (accel[0] >> 5) & 0x3;
	y |= (accel[1] >> 4) & 0x2;
	z |= (accel[1] >> 5) & 0x2;

	input_report_असल(wdata->accel, ABS_RX, x - 0x200);
	input_report_असल(wdata->accel, ABS_RY, y - 0x200);
	input_report_असल(wdata->accel, ABS_RZ, z - 0x200);
	input_sync(wdata->accel);
पूर्ण

अटल पूर्णांक wiimod_accel_खोलो(काष्ठा input_dev *dev)
अणु
	काष्ठा wiimote_data *wdata = input_get_drvdata(dev);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&wdata->state.lock, flags);
	wiiproto_req_accel(wdata, true);
	spin_unlock_irqrestore(&wdata->state.lock, flags);

	वापस 0;
पूर्ण

अटल व्योम wiimod_accel_बंद(काष्ठा input_dev *dev)
अणु
	काष्ठा wiimote_data *wdata = input_get_drvdata(dev);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&wdata->state.lock, flags);
	wiiproto_req_accel(wdata, false);
	spin_unlock_irqrestore(&wdata->state.lock, flags);
पूर्ण

अटल पूर्णांक wiimod_accel_probe(स्थिर काष्ठा wiimod_ops *ops,
			      काष्ठा wiimote_data *wdata)
अणु
	पूर्णांक ret;

	wdata->accel = input_allocate_device();
	अगर (!wdata->accel)
		वापस -ENOMEM;

	input_set_drvdata(wdata->accel, wdata);
	wdata->accel->खोलो = wiimod_accel_खोलो;
	wdata->accel->बंद = wiimod_accel_बंद;
	wdata->accel->dev.parent = &wdata->hdev->dev;
	wdata->accel->id.bustype = wdata->hdev->bus;
	wdata->accel->id.venकरोr = wdata->hdev->venकरोr;
	wdata->accel->id.product = wdata->hdev->product;
	wdata->accel->id.version = wdata->hdev->version;
	wdata->accel->name = WIIMOTE_NAME " Accelerometer";

	set_bit(EV_ABS, wdata->accel->evbit);
	set_bit(ABS_RX, wdata->accel->असलbit);
	set_bit(ABS_RY, wdata->accel->असलbit);
	set_bit(ABS_RZ, wdata->accel->असलbit);
	input_set_असल_params(wdata->accel, ABS_RX, -500, 500, 2, 4);
	input_set_असल_params(wdata->accel, ABS_RY, -500, 500, 2, 4);
	input_set_असल_params(wdata->accel, ABS_RZ, -500, 500, 2, 4);

	ret = input_रेजिस्टर_device(wdata->accel);
	अगर (ret) अणु
		hid_err(wdata->hdev, "cannot register input device\n");
		जाओ err_मुक्त;
	पूर्ण

	वापस 0;

err_मुक्त:
	input_मुक्त_device(wdata->accel);
	wdata->accel = शून्य;
	वापस ret;
पूर्ण

अटल व्योम wiimod_accel_हटाओ(स्थिर काष्ठा wiimod_ops *ops,
				काष्ठा wiimote_data *wdata)
अणु
	अगर (!wdata->accel)
		वापस;

	input_unरेजिस्टर_device(wdata->accel);
	wdata->accel = शून्य;
पूर्ण

अटल स्थिर काष्ठा wiimod_ops wiimod_accel = अणु
	.flags = 0,
	.arg = 0,
	.probe = wiimod_accel_probe,
	.हटाओ = wiimod_accel_हटाओ,
	.in_accel = wiimod_accel_in_accel,
पूर्ण;

/*
 * IR Cam
 * Up to 4 IR sources can be tracked by a normal Wii Remote. The IR cam needs
 * to be initialized with a fairly complex procedure and consumes a lot of
 * घातer. Thereक्रमe, as दीर्घ as no application uses the IR input device, it is
 * kept offline.
 * Nearly no other device than the normal Wii Remotes supports the IR cam so
 * you can disable this module क्रम these devices.
 */

अटल व्योम wiimod_ir_in_ir(काष्ठा wiimote_data *wdata, स्थिर __u8 *ir,
			    bool packed, अचिन्हित पूर्णांक id)
अणु
	__u16 x, y;
	__u8 xid, yid;
	bool sync = false;

	अगर (!(wdata->state.flags & WIIPROTO_FLAGS_IR))
		वापस;

	चयन (id) अणु
	हाल 0:
		xid = ABS_HAT0X;
		yid = ABS_HAT0Y;
		अवरोध;
	हाल 1:
		xid = ABS_HAT1X;
		yid = ABS_HAT1Y;
		अवरोध;
	हाल 2:
		xid = ABS_HAT2X;
		yid = ABS_HAT2Y;
		अवरोध;
	हाल 3:
		xid = ABS_HAT3X;
		yid = ABS_HAT3Y;
		sync = true;
		अवरोध;
	शेष:
		वापस;
	पूर्ण

	/*
	 * Basic IR data is encoded पूर्णांकo 3 bytes. The first two bytes are the
	 * lower 8 bit of the X/Y data, the 3rd byte contains the upper 2 bits
	 * of both.
	 * If data is packed, then the 3rd byte is put first and slightly
	 * reordered. This allows to पूर्णांकerleave packed and non-packed data to
	 * have two IR sets in 5 bytes instead of 6.
	 * The resulting 10bit X/Y values are passed to the ABS_HAT? input dev.
	 */

	अगर (packed) अणु
		x = ir[1] | ((ir[0] & 0x03) << 8);
		y = ir[2] | ((ir[0] & 0x0c) << 6);
	पूर्ण अन्यथा अणु
		x = ir[0] | ((ir[2] & 0x30) << 4);
		y = ir[1] | ((ir[2] & 0xc0) << 2);
	पूर्ण

	input_report_असल(wdata->ir, xid, x);
	input_report_असल(wdata->ir, yid, y);

	अगर (sync)
		input_sync(wdata->ir);
पूर्ण

अटल पूर्णांक wiimod_ir_change(काष्ठा wiimote_data *wdata, __u16 mode)
अणु
	पूर्णांक ret;
	अचिन्हित दीर्घ flags;
	__u8 क्रमmat = 0;
	अटल स्थिर __u8 data_enable[] = अणु 0x01 पूर्ण;
	अटल स्थिर __u8 data_sens1[] = अणु 0x02, 0x00, 0x00, 0x71, 0x01,
						0x00, 0xaa, 0x00, 0x64 पूर्ण;
	अटल स्थिर __u8 data_sens2[] = अणु 0x63, 0x03 पूर्ण;
	अटल स्थिर __u8 data_fin[] = अणु 0x08 पूर्ण;

	spin_lock_irqsave(&wdata->state.lock, flags);

	अगर (mode == (wdata->state.flags & WIIPROTO_FLAGS_IR)) अणु
		spin_unlock_irqrestore(&wdata->state.lock, flags);
		वापस 0;
	पूर्ण

	अगर (mode == 0) अणु
		wdata->state.flags &= ~WIIPROTO_FLAGS_IR;
		wiiproto_req_ir1(wdata, 0);
		wiiproto_req_ir2(wdata, 0);
		wiiproto_req_drm(wdata, WIIPROTO_REQ_शून्य);
		spin_unlock_irqrestore(&wdata->state.lock, flags);
		वापस 0;
	पूर्ण

	spin_unlock_irqrestore(&wdata->state.lock, flags);

	ret = wiimote_cmd_acquire(wdata);
	अगर (ret)
		वापस ret;

	/* send PIXEL CLOCK ENABLE cmd first */
	spin_lock_irqsave(&wdata->state.lock, flags);
	wiimote_cmd_set(wdata, WIIPROTO_REQ_IR1, 0);
	wiiproto_req_ir1(wdata, 0x06);
	spin_unlock_irqrestore(&wdata->state.lock, flags);

	ret = wiimote_cmd_रुको(wdata);
	अगर (ret)
		जाओ unlock;
	अगर (wdata->state.cmd_err) अणु
		ret = -EIO;
		जाओ unlock;
	पूर्ण

	/* enable IR LOGIC */
	spin_lock_irqsave(&wdata->state.lock, flags);
	wiimote_cmd_set(wdata, WIIPROTO_REQ_IR2, 0);
	wiiproto_req_ir2(wdata, 0x06);
	spin_unlock_irqrestore(&wdata->state.lock, flags);

	ret = wiimote_cmd_रुको(wdata);
	अगर (ret)
		जाओ unlock;
	अगर (wdata->state.cmd_err) अणु
		ret = -EIO;
		जाओ unlock;
	पूर्ण

	/* enable IR cam but करो not make it send data, yet */
	ret = wiimote_cmd_ग_लिखो(wdata, 0xb00030, data_enable,
							माप(data_enable));
	अगर (ret)
		जाओ unlock;

	/* ग_लिखो first sensitivity block */
	ret = wiimote_cmd_ग_लिखो(wdata, 0xb00000, data_sens1,
							माप(data_sens1));
	अगर (ret)
		जाओ unlock;

	/* ग_लिखो second sensitivity block */
	ret = wiimote_cmd_ग_लिखो(wdata, 0xb0001a, data_sens2,
							माप(data_sens2));
	अगर (ret)
		जाओ unlock;

	/* put IR cam पूर्णांकo desired state */
	चयन (mode) अणु
		हाल WIIPROTO_FLAG_IR_FULL:
			क्रमmat = 5;
			अवरोध;
		हाल WIIPROTO_FLAG_IR_EXT:
			क्रमmat = 3;
			अवरोध;
		हाल WIIPROTO_FLAG_IR_BASIC:
			क्रमmat = 1;
			अवरोध;
	पूर्ण
	ret = wiimote_cmd_ग_लिखो(wdata, 0xb00033, &क्रमmat, माप(क्रमmat));
	अगर (ret)
		जाओ unlock;

	/* make IR cam send data */
	ret = wiimote_cmd_ग_लिखो(wdata, 0xb00030, data_fin, माप(data_fin));
	अगर (ret)
		जाओ unlock;

	/* request new DRM mode compatible to IR mode */
	spin_lock_irqsave(&wdata->state.lock, flags);
	wdata->state.flags &= ~WIIPROTO_FLAGS_IR;
	wdata->state.flags |= mode & WIIPROTO_FLAGS_IR;
	wiiproto_req_drm(wdata, WIIPROTO_REQ_शून्य);
	spin_unlock_irqrestore(&wdata->state.lock, flags);

unlock:
	wiimote_cmd_release(wdata);
	वापस ret;
पूर्ण

अटल पूर्णांक wiimod_ir_खोलो(काष्ठा input_dev *dev)
अणु
	काष्ठा wiimote_data *wdata = input_get_drvdata(dev);

	वापस wiimod_ir_change(wdata, WIIPROTO_FLAG_IR_BASIC);
पूर्ण

अटल व्योम wiimod_ir_बंद(काष्ठा input_dev *dev)
अणु
	काष्ठा wiimote_data *wdata = input_get_drvdata(dev);

	wiimod_ir_change(wdata, 0);
पूर्ण

अटल पूर्णांक wiimod_ir_probe(स्थिर काष्ठा wiimod_ops *ops,
			   काष्ठा wiimote_data *wdata)
अणु
	पूर्णांक ret;

	wdata->ir = input_allocate_device();
	अगर (!wdata->ir)
		वापस -ENOMEM;

	input_set_drvdata(wdata->ir, wdata);
	wdata->ir->खोलो = wiimod_ir_खोलो;
	wdata->ir->बंद = wiimod_ir_बंद;
	wdata->ir->dev.parent = &wdata->hdev->dev;
	wdata->ir->id.bustype = wdata->hdev->bus;
	wdata->ir->id.venकरोr = wdata->hdev->venकरोr;
	wdata->ir->id.product = wdata->hdev->product;
	wdata->ir->id.version = wdata->hdev->version;
	wdata->ir->name = WIIMOTE_NAME " IR";

	set_bit(EV_ABS, wdata->ir->evbit);
	set_bit(ABS_HAT0X, wdata->ir->असलbit);
	set_bit(ABS_HAT0Y, wdata->ir->असलbit);
	set_bit(ABS_HAT1X, wdata->ir->असलbit);
	set_bit(ABS_HAT1Y, wdata->ir->असलbit);
	set_bit(ABS_HAT2X, wdata->ir->असलbit);
	set_bit(ABS_HAT2Y, wdata->ir->असलbit);
	set_bit(ABS_HAT3X, wdata->ir->असलbit);
	set_bit(ABS_HAT3Y, wdata->ir->असलbit);
	input_set_असल_params(wdata->ir, ABS_HAT0X, 0, 1023, 2, 4);
	input_set_असल_params(wdata->ir, ABS_HAT0Y, 0, 767, 2, 4);
	input_set_असल_params(wdata->ir, ABS_HAT1X, 0, 1023, 2, 4);
	input_set_असल_params(wdata->ir, ABS_HAT1Y, 0, 767, 2, 4);
	input_set_असल_params(wdata->ir, ABS_HAT2X, 0, 1023, 2, 4);
	input_set_असल_params(wdata->ir, ABS_HAT2Y, 0, 767, 2, 4);
	input_set_असल_params(wdata->ir, ABS_HAT3X, 0, 1023, 2, 4);
	input_set_असल_params(wdata->ir, ABS_HAT3Y, 0, 767, 2, 4);

	ret = input_रेजिस्टर_device(wdata->ir);
	अगर (ret) अणु
		hid_err(wdata->hdev, "cannot register input device\n");
		जाओ err_मुक्त;
	पूर्ण

	वापस 0;

err_मुक्त:
	input_मुक्त_device(wdata->ir);
	wdata->ir = शून्य;
	वापस ret;
पूर्ण

अटल व्योम wiimod_ir_हटाओ(स्थिर काष्ठा wiimod_ops *ops,
			     काष्ठा wiimote_data *wdata)
अणु
	अगर (!wdata->ir)
		वापस;

	input_unरेजिस्टर_device(wdata->ir);
	wdata->ir = शून्य;
पूर्ण

अटल स्थिर काष्ठा wiimod_ops wiimod_ir = अणु
	.flags = 0,
	.arg = 0,
	.probe = wiimod_ir_probe,
	.हटाओ = wiimod_ir_हटाओ,
	.in_ir = wiimod_ir_in_ir,
पूर्ण;

/*
 * Nunchuk Extension
 * The Nपूर्णांकenकरो Wii Nunchuk was the first official extension published by
 * Nपूर्णांकenकरो. It provides two additional keys and a separate accelerometer. It
 * can be hotplugged to standard Wii Remotes.
 */

क्रमागत wiimod_nunchuk_keys अणु
	WIIMOD_NUNCHUK_KEY_C,
	WIIMOD_NUNCHUK_KEY_Z,
	WIIMOD_NUNCHUK_KEY_NUM,
पूर्ण;

अटल स्थिर __u16 wiimod_nunchuk_map[] = अणु
	BTN_C,		/* WIIMOD_NUNCHUK_KEY_C */
	BTN_Z,		/* WIIMOD_NUNCHUK_KEY_Z */
पूर्ण;

अटल व्योम wiimod_nunchuk_in_ext(काष्ठा wiimote_data *wdata, स्थिर __u8 *ext)
अणु
	__s16 x, y, z, bx, by;

	/*   Byte |   8    7 |  6    5 |  4    3 |  2 |  1  |
	 *   -----+----------+---------+---------+----+-----+
	 *    1   |              Button X <7:0>             |
	 *    2   |              Button Y <7:0>             |
	 *   -----+----------+---------+---------+----+-----+
	 *    3   |               Speed X <9:2>             |
	 *    4   |               Speed Y <9:2>             |
	 *    5   |               Speed Z <9:2>             |
	 *   -----+----------+---------+---------+----+-----+
	 *    6   | Z <1:0>  | Y <1:0> | X <1:0> | BC | BZ  |
	 *   -----+----------+---------+---------+----+-----+
	 * Button X/Y is the analog stick. Speed X, Y and Z are the
	 * accelerometer data in the same क्रमmat as the wiimote's accelerometer.
	 * The 6th byte contains the LSBs of the accelerometer data.
	 * BC and BZ are the C and Z buttons: 0 means pressed
	 *
	 * If reported पूर्णांकerleaved with motionp, then the layout changes. The
	 * 5th and 6th byte changes to:
	 *   -----+-----------------------------------+-----+
	 *    5   |            Speed Z <9:3>          | EXT |
	 *   -----+--------+-----+-----+----+----+----+-----+
	 *    6   |Z <2:1> |Y <1>|X <1>| BC | BZ | 0  |  0  |
	 *   -----+--------+-----+-----+----+----+----+-----+
	 * All three accelerometer values lose their LSB. The other data is
	 * still available but slightly moved.
	 *
	 * Center data क्रम button values is 128. Center value क्रम accelerometer
	 * values it 512 / 0x200
	 */

	bx = ext[0];
	by = ext[1];
	bx -= 128;
	by -= 128;

	x = ext[2] << 2;
	y = ext[3] << 2;
	z = ext[4] << 2;

	अगर (wdata->state.flags & WIIPROTO_FLAG_MP_ACTIVE) अणु
		x |= (ext[5] >> 3) & 0x02;
		y |= (ext[5] >> 4) & 0x02;
		z &= ~0x4;
		z |= (ext[5] >> 5) & 0x06;
	पूर्ण अन्यथा अणु
		x |= (ext[5] >> 2) & 0x03;
		y |= (ext[5] >> 4) & 0x03;
		z |= (ext[5] >> 6) & 0x03;
	पूर्ण

	x -= 0x200;
	y -= 0x200;
	z -= 0x200;

	input_report_असल(wdata->extension.input, ABS_HAT0X, bx);
	input_report_असल(wdata->extension.input, ABS_HAT0Y, by);

	input_report_असल(wdata->extension.input, ABS_RX, x);
	input_report_असल(wdata->extension.input, ABS_RY, y);
	input_report_असल(wdata->extension.input, ABS_RZ, z);

	अगर (wdata->state.flags & WIIPROTO_FLAG_MP_ACTIVE) अणु
		input_report_key(wdata->extension.input,
			wiimod_nunchuk_map[WIIMOD_NUNCHUK_KEY_Z],
			!(ext[5] & 0x04));
		input_report_key(wdata->extension.input,
			wiimod_nunchuk_map[WIIMOD_NUNCHUK_KEY_C],
			!(ext[5] & 0x08));
	पूर्ण अन्यथा अणु
		input_report_key(wdata->extension.input,
			wiimod_nunchuk_map[WIIMOD_NUNCHUK_KEY_Z],
			!(ext[5] & 0x01));
		input_report_key(wdata->extension.input,
			wiimod_nunchuk_map[WIIMOD_NUNCHUK_KEY_C],
			!(ext[5] & 0x02));
	पूर्ण

	input_sync(wdata->extension.input);
पूर्ण

अटल पूर्णांक wiimod_nunchuk_खोलो(काष्ठा input_dev *dev)
अणु
	काष्ठा wiimote_data *wdata = input_get_drvdata(dev);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&wdata->state.lock, flags);
	wdata->state.flags |= WIIPROTO_FLAG_EXT_USED;
	wiiproto_req_drm(wdata, WIIPROTO_REQ_शून्य);
	spin_unlock_irqrestore(&wdata->state.lock, flags);

	वापस 0;
पूर्ण

अटल व्योम wiimod_nunchuk_बंद(काष्ठा input_dev *dev)
अणु
	काष्ठा wiimote_data *wdata = input_get_drvdata(dev);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&wdata->state.lock, flags);
	wdata->state.flags &= ~WIIPROTO_FLAG_EXT_USED;
	wiiproto_req_drm(wdata, WIIPROTO_REQ_शून्य);
	spin_unlock_irqrestore(&wdata->state.lock, flags);
पूर्ण

अटल पूर्णांक wiimod_nunchuk_probe(स्थिर काष्ठा wiimod_ops *ops,
				काष्ठा wiimote_data *wdata)
अणु
	पूर्णांक ret, i;

	wdata->extension.input = input_allocate_device();
	अगर (!wdata->extension.input)
		वापस -ENOMEM;

	input_set_drvdata(wdata->extension.input, wdata);
	wdata->extension.input->खोलो = wiimod_nunchuk_खोलो;
	wdata->extension.input->बंद = wiimod_nunchuk_बंद;
	wdata->extension.input->dev.parent = &wdata->hdev->dev;
	wdata->extension.input->id.bustype = wdata->hdev->bus;
	wdata->extension.input->id.venकरोr = wdata->hdev->venकरोr;
	wdata->extension.input->id.product = wdata->hdev->product;
	wdata->extension.input->id.version = wdata->hdev->version;
	wdata->extension.input->name = WIIMOTE_NAME " Nunchuk";

	set_bit(EV_KEY, wdata->extension.input->evbit);
	क्रम (i = 0; i < WIIMOD_NUNCHUK_KEY_NUM; ++i)
		set_bit(wiimod_nunchuk_map[i],
			wdata->extension.input->keybit);

	set_bit(EV_ABS, wdata->extension.input->evbit);
	set_bit(ABS_HAT0X, wdata->extension.input->असलbit);
	set_bit(ABS_HAT0Y, wdata->extension.input->असलbit);
	input_set_असल_params(wdata->extension.input,
			     ABS_HAT0X, -120, 120, 2, 4);
	input_set_असल_params(wdata->extension.input,
			     ABS_HAT0Y, -120, 120, 2, 4);
	set_bit(ABS_RX, wdata->extension.input->असलbit);
	set_bit(ABS_RY, wdata->extension.input->असलbit);
	set_bit(ABS_RZ, wdata->extension.input->असलbit);
	input_set_असल_params(wdata->extension.input,
			     ABS_RX, -500, 500, 2, 4);
	input_set_असल_params(wdata->extension.input,
			     ABS_RY, -500, 500, 2, 4);
	input_set_असल_params(wdata->extension.input,
			     ABS_RZ, -500, 500, 2, 4);

	ret = input_रेजिस्टर_device(wdata->extension.input);
	अगर (ret)
		जाओ err_मुक्त;

	वापस 0;

err_मुक्त:
	input_मुक्त_device(wdata->extension.input);
	wdata->extension.input = शून्य;
	वापस ret;
पूर्ण

अटल व्योम wiimod_nunchuk_हटाओ(स्थिर काष्ठा wiimod_ops *ops,
				  काष्ठा wiimote_data *wdata)
अणु
	अगर (!wdata->extension.input)
		वापस;

	input_unरेजिस्टर_device(wdata->extension.input);
	wdata->extension.input = शून्य;
पूर्ण

अटल स्थिर काष्ठा wiimod_ops wiimod_nunchuk = अणु
	.flags = 0,
	.arg = 0,
	.probe = wiimod_nunchuk_probe,
	.हटाओ = wiimod_nunchuk_हटाओ,
	.in_ext = wiimod_nunchuk_in_ext,
पूर्ण;

/*
 * Classic Controller
 * Another official extension from Nपूर्णांकenकरो. It provides a classic
 * gamecube-like controller that can be hotplugged on the Wii Remote.
 * It has several hardware buttons and चयनes that are all reported via
 * a normal extension device.
 */

क्रमागत wiimod_classic_keys अणु
	WIIMOD_CLASSIC_KEY_A,
	WIIMOD_CLASSIC_KEY_B,
	WIIMOD_CLASSIC_KEY_X,
	WIIMOD_CLASSIC_KEY_Y,
	WIIMOD_CLASSIC_KEY_ZL,
	WIIMOD_CLASSIC_KEY_ZR,
	WIIMOD_CLASSIC_KEY_PLUS,
	WIIMOD_CLASSIC_KEY_MINUS,
	WIIMOD_CLASSIC_KEY_HOME,
	WIIMOD_CLASSIC_KEY_LEFT,
	WIIMOD_CLASSIC_KEY_RIGHT,
	WIIMOD_CLASSIC_KEY_UP,
	WIIMOD_CLASSIC_KEY_DOWN,
	WIIMOD_CLASSIC_KEY_LT,
	WIIMOD_CLASSIC_KEY_RT,
	WIIMOD_CLASSIC_KEY_NUM,
पूर्ण;

अटल स्थिर __u16 wiimod_classic_map[] = अणु
	BTN_A,		/* WIIMOD_CLASSIC_KEY_A */
	BTN_B,		/* WIIMOD_CLASSIC_KEY_B */
	BTN_X,		/* WIIMOD_CLASSIC_KEY_X */
	BTN_Y,		/* WIIMOD_CLASSIC_KEY_Y */
	BTN_TL2,	/* WIIMOD_CLASSIC_KEY_ZL */
	BTN_TR2,	/* WIIMOD_CLASSIC_KEY_ZR */
	KEY_NEXT,	/* WIIMOD_CLASSIC_KEY_PLUS */
	KEY_PREVIOUS,	/* WIIMOD_CLASSIC_KEY_MINUS */
	BTN_MODE,	/* WIIMOD_CLASSIC_KEY_HOME */
	KEY_LEFT,	/* WIIMOD_CLASSIC_KEY_LEFT */
	KEY_RIGHT,	/* WIIMOD_CLASSIC_KEY_RIGHT */
	KEY_UP,		/* WIIMOD_CLASSIC_KEY_UP */
	KEY_DOWN,	/* WIIMOD_CLASSIC_KEY_DOWN */
	BTN_TL,		/* WIIMOD_CLASSIC_KEY_LT */
	BTN_TR,		/* WIIMOD_CLASSIC_KEY_RT */
पूर्ण;

अटल व्योम wiimod_classic_in_ext(काष्ठा wiimote_data *wdata, स्थिर __u8 *ext)
अणु
	__s8 rx, ry, lx, ly, lt, rt;

	/*   Byte |  8  |  7  |  6  |  5  |  4  |  3  |  2  |  1  |
	 *   -----+-----+-----+-----+-----+-----+-----+-----+-----+
	 *    1   | RX <5:4>  |              LX <5:0>             |
	 *    2   | RX <3:2>  |              LY <5:0>             |
	 *   -----+-----+-----+-----+-----------------------------+
	 *    3   |RX<1>| LT <5:4>  |         RY <5:1>            |
	 *   -----+-----+-----------+-----------------------------+
	 *    4   |     LT <3:1>    |         RT <5:1>            |
	 *   -----+-----+-----+-----+-----+-----+-----+-----+-----+
	 *    5   | BDR | BDD | BLT | B-  | BH  | B+  | BRT |  1  |
	 *   -----+-----+-----+-----+-----+-----+-----+-----+-----+
	 *    6   | BZL | BB  | BY  | BA  | BX  | BZR | BDL | BDU |
	 *   -----+-----+-----+-----+-----+-----+-----+-----+-----+
	 * All buttons are 0 अगर pressed
	 * RX and RY are right analog stick
	 * LX and LY are left analog stick
	 * LT is left trigger, RT is right trigger
	 * BLT is 0 अगर left trigger is fully pressed
	 * BRT is 0 अगर right trigger is fully pressed
	 * BDR, BDD, BDL, BDU क्रमm the D-Pad with right, करोwn, left, up buttons
	 * BZL is left Z button and BZR is right Z button
	 * B-, BH, B+ are +, HOME and - buttons
	 * BB, BY, BA, BX are A, B, X, Y buttons
	 * LSB of RX, RY, LT, and RT are not transmitted and always 0.
	 *
	 * With motionp enabled it changes slightly to this:
	 *   Byte |  8  |  7  |  6  |  5  |  4  |  3  |  2  |  1  |
	 *   -----+-----+-----+-----+-----+-----+-----+-----+-----+
	 *    1   | RX <5:4>  |          LX <5:1>           | BDU |
	 *    2   | RX <3:2>  |          LY <5:1>           | BDL |
	 *   -----+-----+-----+-----+-----------------------+-----+
	 *    3   |RX<1>| LT <5:4>  |         RY <5:1>            |
	 *   -----+-----+-----------+-----------------------------+
	 *    4   |     LT <3:1>    |         RT <5:1>            |
	 *   -----+-----+-----+-----+-----+-----+-----+-----+-----+
	 *    5   | BDR | BDD | BLT | B-  | BH  | B+  | BRT | EXT |
	 *   -----+-----+-----+-----+-----+-----+-----+-----+-----+
	 *    6   | BZL | BB  | BY  | BA  | BX  | BZR |  0  |  0  |
	 *   -----+-----+-----+-----+-----+-----+-----+-----+-----+
	 * Only the LSBs of LX and LY are lost. BDU and BDL are moved, the rest
	 * is the same as beक्रमe.
	 */

	अटल स्थिर s8 digital_to_analog[3] = अणु0x20, 0, -0x20पूर्ण;

	अगर (wdata->state.flags & WIIPROTO_FLAG_MP_ACTIVE) अणु
		अगर (wiimote_dpad_as_analog) अणु
			lx = digital_to_analog[1 - !(ext[4] & 0x80)
				+ !(ext[1] & 0x01)];
			ly = digital_to_analog[1 - !(ext[4] & 0x40)
				+ !(ext[0] & 0x01)];
		पूर्ण अन्यथा अणु
			lx = (ext[0] & 0x3e) - 0x20;
			ly = (ext[1] & 0x3e) - 0x20;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (wiimote_dpad_as_analog) अणु
			lx = digital_to_analog[1 - !(ext[4] & 0x80)
				+ !(ext[5] & 0x02)];
			ly = digital_to_analog[1 - !(ext[4] & 0x40)
				+ !(ext[5] & 0x01)];
		पूर्ण अन्यथा अणु
			lx = (ext[0] & 0x3f) - 0x20;
			ly = (ext[1] & 0x3f) - 0x20;
		पूर्ण
	पूर्ण

	rx = (ext[0] >> 3) & 0x18;
	rx |= (ext[1] >> 5) & 0x06;
	rx |= (ext[2] >> 7) & 0x01;
	ry = ext[2] & 0x1f;

	rt = ext[3] & 0x1f;
	lt = (ext[2] >> 2) & 0x18;
	lt |= (ext[3] >> 5) & 0x07;

	rx <<= 1;
	ry <<= 1;
	rt <<= 1;
	lt <<= 1;

	input_report_असल(wdata->extension.input, ABS_HAT1X, lx);
	input_report_असल(wdata->extension.input, ABS_HAT1Y, ly);
	input_report_असल(wdata->extension.input, ABS_HAT2X, rx - 0x20);
	input_report_असल(wdata->extension.input, ABS_HAT2Y, ry - 0x20);
	input_report_असल(wdata->extension.input, ABS_HAT3X, rt);
	input_report_असल(wdata->extension.input, ABS_HAT3Y, lt);

	input_report_key(wdata->extension.input,
			 wiimod_classic_map[WIIMOD_CLASSIC_KEY_LT],
			 !(ext[4] & 0x20));
	input_report_key(wdata->extension.input,
			 wiimod_classic_map[WIIMOD_CLASSIC_KEY_MINUS],
			 !(ext[4] & 0x10));
	input_report_key(wdata->extension.input,
			 wiimod_classic_map[WIIMOD_CLASSIC_KEY_HOME],
			 !(ext[4] & 0x08));
	input_report_key(wdata->extension.input,
			 wiimod_classic_map[WIIMOD_CLASSIC_KEY_PLUS],
			 !(ext[4] & 0x04));
	input_report_key(wdata->extension.input,
			 wiimod_classic_map[WIIMOD_CLASSIC_KEY_RT],
			 !(ext[4] & 0x02));
	input_report_key(wdata->extension.input,
			 wiimod_classic_map[WIIMOD_CLASSIC_KEY_ZL],
			 !(ext[5] & 0x80));
	input_report_key(wdata->extension.input,
			 wiimod_classic_map[WIIMOD_CLASSIC_KEY_B],
			 !(ext[5] & 0x40));
	input_report_key(wdata->extension.input,
			 wiimod_classic_map[WIIMOD_CLASSIC_KEY_Y],
			 !(ext[5] & 0x20));
	input_report_key(wdata->extension.input,
			 wiimod_classic_map[WIIMOD_CLASSIC_KEY_A],
			 !(ext[5] & 0x10));
	input_report_key(wdata->extension.input,
			 wiimod_classic_map[WIIMOD_CLASSIC_KEY_X],
			 !(ext[5] & 0x08));
	input_report_key(wdata->extension.input,
			 wiimod_classic_map[WIIMOD_CLASSIC_KEY_ZR],
			 !(ext[5] & 0x04));

	अगर (!wiimote_dpad_as_analog) अणु
		input_report_key(wdata->extension.input,
				 wiimod_classic_map[WIIMOD_CLASSIC_KEY_RIGHT],
				 !(ext[4] & 0x80));
		input_report_key(wdata->extension.input,
				 wiimod_classic_map[WIIMOD_CLASSIC_KEY_DOWN],
				 !(ext[4] & 0x40));

		अगर (wdata->state.flags & WIIPROTO_FLAG_MP_ACTIVE) अणु
			input_report_key(wdata->extension.input,
				 wiimod_classic_map[WIIMOD_CLASSIC_KEY_LEFT],
				 !(ext[1] & 0x01));
			input_report_key(wdata->extension.input,
				 wiimod_classic_map[WIIMOD_CLASSIC_KEY_UP],
				 !(ext[0] & 0x01));
		पूर्ण अन्यथा अणु
			input_report_key(wdata->extension.input,
				 wiimod_classic_map[WIIMOD_CLASSIC_KEY_LEFT],
				 !(ext[5] & 0x02));
			input_report_key(wdata->extension.input,
				 wiimod_classic_map[WIIMOD_CLASSIC_KEY_UP],
				 !(ext[5] & 0x01));
		पूर्ण
	पूर्ण

	input_sync(wdata->extension.input);
पूर्ण

अटल पूर्णांक wiimod_classic_खोलो(काष्ठा input_dev *dev)
अणु
	काष्ठा wiimote_data *wdata = input_get_drvdata(dev);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&wdata->state.lock, flags);
	wdata->state.flags |= WIIPROTO_FLAG_EXT_USED;
	wiiproto_req_drm(wdata, WIIPROTO_REQ_शून्य);
	spin_unlock_irqrestore(&wdata->state.lock, flags);

	वापस 0;
पूर्ण

अटल व्योम wiimod_classic_बंद(काष्ठा input_dev *dev)
अणु
	काष्ठा wiimote_data *wdata = input_get_drvdata(dev);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&wdata->state.lock, flags);
	wdata->state.flags &= ~WIIPROTO_FLAG_EXT_USED;
	wiiproto_req_drm(wdata, WIIPROTO_REQ_शून्य);
	spin_unlock_irqrestore(&wdata->state.lock, flags);
पूर्ण

अटल पूर्णांक wiimod_classic_probe(स्थिर काष्ठा wiimod_ops *ops,
				काष्ठा wiimote_data *wdata)
अणु
	पूर्णांक ret, i;

	wdata->extension.input = input_allocate_device();
	अगर (!wdata->extension.input)
		वापस -ENOMEM;

	input_set_drvdata(wdata->extension.input, wdata);
	wdata->extension.input->खोलो = wiimod_classic_खोलो;
	wdata->extension.input->बंद = wiimod_classic_बंद;
	wdata->extension.input->dev.parent = &wdata->hdev->dev;
	wdata->extension.input->id.bustype = wdata->hdev->bus;
	wdata->extension.input->id.venकरोr = wdata->hdev->venकरोr;
	wdata->extension.input->id.product = wdata->hdev->product;
	wdata->extension.input->id.version = wdata->hdev->version;
	wdata->extension.input->name = WIIMOTE_NAME " Classic Controller";

	set_bit(EV_KEY, wdata->extension.input->evbit);
	क्रम (i = 0; i < WIIMOD_CLASSIC_KEY_NUM; ++i)
		set_bit(wiimod_classic_map[i],
			wdata->extension.input->keybit);

	set_bit(EV_ABS, wdata->extension.input->evbit);
	set_bit(ABS_HAT1X, wdata->extension.input->असलbit);
	set_bit(ABS_HAT1Y, wdata->extension.input->असलbit);
	set_bit(ABS_HAT2X, wdata->extension.input->असलbit);
	set_bit(ABS_HAT2Y, wdata->extension.input->असलbit);
	set_bit(ABS_HAT3X, wdata->extension.input->असलbit);
	set_bit(ABS_HAT3Y, wdata->extension.input->असलbit);
	input_set_असल_params(wdata->extension.input,
			     ABS_HAT1X, -30, 30, 1, 1);
	input_set_असल_params(wdata->extension.input,
			     ABS_HAT1Y, -30, 30, 1, 1);
	input_set_असल_params(wdata->extension.input,
			     ABS_HAT2X, -30, 30, 1, 1);
	input_set_असल_params(wdata->extension.input,
			     ABS_HAT2Y, -30, 30, 1, 1);
	input_set_असल_params(wdata->extension.input,
			     ABS_HAT3X, -30, 30, 1, 1);
	input_set_असल_params(wdata->extension.input,
			     ABS_HAT3Y, -30, 30, 1, 1);

	ret = input_रेजिस्टर_device(wdata->extension.input);
	अगर (ret)
		जाओ err_मुक्त;

	वापस 0;

err_मुक्त:
	input_मुक्त_device(wdata->extension.input);
	wdata->extension.input = शून्य;
	वापस ret;
पूर्ण

अटल व्योम wiimod_classic_हटाओ(स्थिर काष्ठा wiimod_ops *ops,
				  काष्ठा wiimote_data *wdata)
अणु
	अगर (!wdata->extension.input)
		वापस;

	input_unरेजिस्टर_device(wdata->extension.input);
	wdata->extension.input = शून्य;
पूर्ण

अटल स्थिर काष्ठा wiimod_ops wiimod_classic = अणु
	.flags = 0,
	.arg = 0,
	.probe = wiimod_classic_probe,
	.हटाओ = wiimod_classic_हटाओ,
	.in_ext = wiimod_classic_in_ext,
पूर्ण;

/*
 * Balance Board Extension
 * The Nपूर्णांकenकरो Wii Balance Board provides four hardware weight sensor plus a
 * single push button. No other peripherals are available. However, the
 * balance-board data is sent via a standard Wii Remote extension. All other
 * data क्रम non-present hardware is zeroed out.
 * Some 3rd party devices react allergic अगर we try to access normal Wii Remote
 * hardware, so this extension module should be the only module that is loaded
 * on balance boards.
 * The balance board needs 8 bytes extension data instead of basic 6 bytes so
 * it needs the WIIMOD_FLAG_EXT8 flag.
 */

अटल व्योम wiimod_bboard_in_keys(काष्ठा wiimote_data *wdata, स्थिर __u8 *keys)
अणु
	input_report_key(wdata->extension.input, BTN_A,
			 !!(keys[1] & 0x08));
	input_sync(wdata->extension.input);
पूर्ण

अटल व्योम wiimod_bboard_in_ext(काष्ठा wiimote_data *wdata,
				 स्थिर __u8 *ext)
अणु
	__s32 val[4], पंचांगp, भाग;
	अचिन्हित पूर्णांक i;
	काष्ठा wiimote_state *s = &wdata->state;

	/*
	 * Balance board data layout:
	 *
	 *   Byte |  8  7  6  5  4  3  2  1  |
	 *   -----+--------------------------+
	 *    1   |    Top Right <15:8>      |
	 *    2   |    Top Right  <7:0>      |
	 *   -----+--------------------------+
	 *    3   | Bottom Right <15:8>      |
	 *    4   | Bottom Right  <7:0>      |
	 *   -----+--------------------------+
	 *    5   |     Top Left <15:8>      |
	 *    6   |     Top Left  <7:0>      |
	 *   -----+--------------------------+
	 *    7   |  Bottom Left <15:8>      |
	 *    8   |  Bottom Left  <7:0>      |
	 *   -----+--------------------------+
	 *
	 * These values represent the weight-measurements of the Wii-balance
	 * board with 16bit precision.
	 *
	 * The balance-board is never reported पूर्णांकerleaved with motionp.
	 */

	val[0] = ext[0];
	val[0] <<= 8;
	val[0] |= ext[1];

	val[1] = ext[2];
	val[1] <<= 8;
	val[1] |= ext[3];

	val[2] = ext[4];
	val[2] <<= 8;
	val[2] |= ext[5];

	val[3] = ext[6];
	val[3] <<= 8;
	val[3] |= ext[7];

	/* apply calibration data */
	क्रम (i = 0; i < 4; i++) अणु
		अगर (val[i] <= s->calib_bboard[i][0]) अणु
			पंचांगp = 0;
		पूर्ण अन्यथा अगर (val[i] < s->calib_bboard[i][1]) अणु
			पंचांगp = val[i] - s->calib_bboard[i][0];
			पंचांगp *= 1700;
			भाग = s->calib_bboard[i][1] - s->calib_bboard[i][0];
			पंचांगp /= भाग ? भाग : 1;
		पूर्ण अन्यथा अणु
			पंचांगp = val[i] - s->calib_bboard[i][1];
			पंचांगp *= 1700;
			भाग = s->calib_bboard[i][2] - s->calib_bboard[i][1];
			पंचांगp /= भाग ? भाग : 1;
			पंचांगp += 1700;
		पूर्ण
		val[i] = पंचांगp;
	पूर्ण

	input_report_असल(wdata->extension.input, ABS_HAT0X, val[0]);
	input_report_असल(wdata->extension.input, ABS_HAT0Y, val[1]);
	input_report_असल(wdata->extension.input, ABS_HAT1X, val[2]);
	input_report_असल(wdata->extension.input, ABS_HAT1Y, val[3]);
	input_sync(wdata->extension.input);
पूर्ण

अटल पूर्णांक wiimod_bboard_खोलो(काष्ठा input_dev *dev)
अणु
	काष्ठा wiimote_data *wdata = input_get_drvdata(dev);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&wdata->state.lock, flags);
	wdata->state.flags |= WIIPROTO_FLAG_EXT_USED;
	wiiproto_req_drm(wdata, WIIPROTO_REQ_शून्य);
	spin_unlock_irqrestore(&wdata->state.lock, flags);

	वापस 0;
पूर्ण

अटल व्योम wiimod_bboard_बंद(काष्ठा input_dev *dev)
अणु
	काष्ठा wiimote_data *wdata = input_get_drvdata(dev);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&wdata->state.lock, flags);
	wdata->state.flags &= ~WIIPROTO_FLAG_EXT_USED;
	wiiproto_req_drm(wdata, WIIPROTO_REQ_शून्य);
	spin_unlock_irqrestore(&wdata->state.lock, flags);
पूर्ण

अटल sमाप_प्रकार wiimod_bboard_calib_show(काष्ठा device *dev,
					काष्ठा device_attribute *attr,
					अक्षर *out)
अणु
	काष्ठा wiimote_data *wdata = dev_to_wii(dev);
	पूर्णांक i, j, ret;
	__u16 val;
	__u8 buf[24], offs;

	ret = wiimote_cmd_acquire(wdata);
	अगर (ret)
		वापस ret;

	ret = wiimote_cmd_पढ़ो(wdata, 0xa40024, buf, 12);
	अगर (ret != 12) अणु
		wiimote_cmd_release(wdata);
		वापस ret < 0 ? ret : -EIO;
	पूर्ण
	ret = wiimote_cmd_पढ़ो(wdata, 0xa40024 + 12, buf + 12, 12);
	अगर (ret != 12) अणु
		wiimote_cmd_release(wdata);
		वापस ret < 0 ? ret : -EIO;
	पूर्ण

	wiimote_cmd_release(wdata);

	spin_lock_irq(&wdata->state.lock);
	offs = 0;
	क्रम (i = 0; i < 3; ++i) अणु
		क्रम (j = 0; j < 4; ++j) अणु
			wdata->state.calib_bboard[j][i] = buf[offs];
			wdata->state.calib_bboard[j][i] <<= 8;
			wdata->state.calib_bboard[j][i] |= buf[offs + 1];
			offs += 2;
		पूर्ण
	पूर्ण
	spin_unlock_irq(&wdata->state.lock);

	ret = 0;
	क्रम (i = 0; i < 3; ++i) अणु
		क्रम (j = 0; j < 4; ++j) अणु
			val = wdata->state.calib_bboard[j][i];
			अगर (i == 2 && j == 3)
				ret += प्र_लिखो(&out[ret], "%04x\n", val);
			अन्यथा
				ret += प्र_लिखो(&out[ret], "%04x:", val);
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल DEVICE_ATTR(bboard_calib, S_IRUGO, wiimod_bboard_calib_show, शून्य);

अटल पूर्णांक wiimod_bboard_probe(स्थिर काष्ठा wiimod_ops *ops,
			       काष्ठा wiimote_data *wdata)
अणु
	पूर्णांक ret, i, j;
	__u8 buf[24], offs;

	wiimote_cmd_acquire_noपूर्णांक(wdata);

	ret = wiimote_cmd_पढ़ो(wdata, 0xa40024, buf, 12);
	अगर (ret != 12) अणु
		wiimote_cmd_release(wdata);
		वापस ret < 0 ? ret : -EIO;
	पूर्ण
	ret = wiimote_cmd_पढ़ो(wdata, 0xa40024 + 12, buf + 12, 12);
	अगर (ret != 12) अणु
		wiimote_cmd_release(wdata);
		वापस ret < 0 ? ret : -EIO;
	पूर्ण

	wiimote_cmd_release(wdata);

	offs = 0;
	क्रम (i = 0; i < 3; ++i) अणु
		क्रम (j = 0; j < 4; ++j) अणु
			wdata->state.calib_bboard[j][i] = buf[offs];
			wdata->state.calib_bboard[j][i] <<= 8;
			wdata->state.calib_bboard[j][i] |= buf[offs + 1];
			offs += 2;
		पूर्ण
	पूर्ण

	wdata->extension.input = input_allocate_device();
	अगर (!wdata->extension.input)
		वापस -ENOMEM;

	ret = device_create_file(&wdata->hdev->dev,
				 &dev_attr_bboard_calib);
	अगर (ret) अणु
		hid_err(wdata->hdev, "cannot create sysfs attribute\n");
		जाओ err_मुक्त;
	पूर्ण

	input_set_drvdata(wdata->extension.input, wdata);
	wdata->extension.input->खोलो = wiimod_bboard_खोलो;
	wdata->extension.input->बंद = wiimod_bboard_बंद;
	wdata->extension.input->dev.parent = &wdata->hdev->dev;
	wdata->extension.input->id.bustype = wdata->hdev->bus;
	wdata->extension.input->id.venकरोr = wdata->hdev->venकरोr;
	wdata->extension.input->id.product = wdata->hdev->product;
	wdata->extension.input->id.version = wdata->hdev->version;
	wdata->extension.input->name = WIIMOTE_NAME " Balance Board";

	set_bit(EV_KEY, wdata->extension.input->evbit);
	set_bit(BTN_A, wdata->extension.input->keybit);

	set_bit(EV_ABS, wdata->extension.input->evbit);
	set_bit(ABS_HAT0X, wdata->extension.input->असलbit);
	set_bit(ABS_HAT0Y, wdata->extension.input->असलbit);
	set_bit(ABS_HAT1X, wdata->extension.input->असलbit);
	set_bit(ABS_HAT1Y, wdata->extension.input->असलbit);
	input_set_असल_params(wdata->extension.input,
			     ABS_HAT0X, 0, 65535, 2, 4);
	input_set_असल_params(wdata->extension.input,
			     ABS_HAT0Y, 0, 65535, 2, 4);
	input_set_असल_params(wdata->extension.input,
			     ABS_HAT1X, 0, 65535, 2, 4);
	input_set_असल_params(wdata->extension.input,
			     ABS_HAT1Y, 0, 65535, 2, 4);

	ret = input_रेजिस्टर_device(wdata->extension.input);
	अगर (ret)
		जाओ err_file;

	वापस 0;

err_file:
	device_हटाओ_file(&wdata->hdev->dev,
			   &dev_attr_bboard_calib);
err_मुक्त:
	input_मुक्त_device(wdata->extension.input);
	wdata->extension.input = शून्य;
	वापस ret;
पूर्ण

अटल व्योम wiimod_bboard_हटाओ(स्थिर काष्ठा wiimod_ops *ops,
				 काष्ठा wiimote_data *wdata)
अणु
	अगर (!wdata->extension.input)
		वापस;

	input_unरेजिस्टर_device(wdata->extension.input);
	wdata->extension.input = शून्य;
	device_हटाओ_file(&wdata->hdev->dev,
			   &dev_attr_bboard_calib);
पूर्ण

अटल स्थिर काष्ठा wiimod_ops wiimod_bboard = अणु
	.flags = WIIMOD_FLAG_EXT8,
	.arg = 0,
	.probe = wiimod_bboard_probe,
	.हटाओ = wiimod_bboard_हटाओ,
	.in_keys = wiimod_bboard_in_keys,
	.in_ext = wiimod_bboard_in_ext,
पूर्ण;

/*
 * Pro Controller
 * Released with the Wii U was the Nपूर्णांकenकरो Wii U Pro Controller. It करोes not
 * work together with the classic Wii, but only with the new Wii U. However, it
 * uses the same protocol and provides a builtin "classic controller pro"
 * extension, few standard buttons, a rumble motor, 4 LEDs and a battery.
 * We provide all these via a standard extension device as the device करोesn't
 * feature an extension port.
 */

क्रमागत wiimod_pro_keys अणु
	WIIMOD_PRO_KEY_A,
	WIIMOD_PRO_KEY_B,
	WIIMOD_PRO_KEY_X,
	WIIMOD_PRO_KEY_Y,
	WIIMOD_PRO_KEY_PLUS,
	WIIMOD_PRO_KEY_MINUS,
	WIIMOD_PRO_KEY_HOME,
	WIIMOD_PRO_KEY_LEFT,
	WIIMOD_PRO_KEY_RIGHT,
	WIIMOD_PRO_KEY_UP,
	WIIMOD_PRO_KEY_DOWN,
	WIIMOD_PRO_KEY_TL,
	WIIMOD_PRO_KEY_TR,
	WIIMOD_PRO_KEY_ZL,
	WIIMOD_PRO_KEY_ZR,
	WIIMOD_PRO_KEY_THUMBL,
	WIIMOD_PRO_KEY_THUMBR,
	WIIMOD_PRO_KEY_NUM,
पूर्ण;

अटल स्थिर __u16 wiimod_pro_map[] = अणु
	BTN_EAST,	/* WIIMOD_PRO_KEY_A */
	BTN_SOUTH,	/* WIIMOD_PRO_KEY_B */
	BTN_NORTH,	/* WIIMOD_PRO_KEY_X */
	BTN_WEST,	/* WIIMOD_PRO_KEY_Y */
	BTN_START,	/* WIIMOD_PRO_KEY_PLUS */
	BTN_SELECT,	/* WIIMOD_PRO_KEY_MINUS */
	BTN_MODE,	/* WIIMOD_PRO_KEY_HOME */
	BTN_DPAD_LEFT,	/* WIIMOD_PRO_KEY_LEFT */
	BTN_DPAD_RIGHT,	/* WIIMOD_PRO_KEY_RIGHT */
	BTN_DPAD_UP,	/* WIIMOD_PRO_KEY_UP */
	BTN_DPAD_DOWN,	/* WIIMOD_PRO_KEY_DOWN */
	BTN_TL,		/* WIIMOD_PRO_KEY_TL */
	BTN_TR,		/* WIIMOD_PRO_KEY_TR */
	BTN_TL2,	/* WIIMOD_PRO_KEY_ZL */
	BTN_TR2,	/* WIIMOD_PRO_KEY_ZR */
	BTN_THUMBL,	/* WIIMOD_PRO_KEY_THUMBL */
	BTN_THUMBR,	/* WIIMOD_PRO_KEY_THUMBR */
पूर्ण;

अटल व्योम wiimod_pro_in_ext(काष्ठा wiimote_data *wdata, स्थिर __u8 *ext)
अणु
	__s16 rx, ry, lx, ly;

	/*   Byte |  8  |  7  |  6  |  5  |  4  |  3  |  2  |  1  |
	 *   -----+-----+-----+-----+-----+-----+-----+-----+-----+
	 *    1   |                   LX <7:0>                    |
	 *   -----+-----------------------+-----------------------+
	 *    2   |  0     0     0     0  |       LX <11:8>       |
	 *   -----+-----------------------+-----------------------+
	 *    3   |                   RX <7:0>                    |
	 *   -----+-----------------------+-----------------------+
	 *    4   |  0     0     0     0  |       RX <11:8>       |
	 *   -----+-----------------------+-----------------------+
	 *    5   |                   LY <7:0>                    |
	 *   -----+-----------------------+-----------------------+
	 *    6   |  0     0     0     0  |       LY <11:8>       |
	 *   -----+-----------------------+-----------------------+
	 *    7   |                   RY <7:0>                    |
	 *   -----+-----------------------+-----------------------+
	 *    8   |  0     0     0     0  |       RY <11:8>       |
	 *   -----+-----+-----+-----+-----+-----+-----+-----+-----+
	 *    9   | BDR | BDD | BLT | B-  | BH  | B+  | BRT |  1  |
	 *   -----+-----+-----+-----+-----+-----+-----+-----+-----+
	 *   10   | BZL | BB  | BY  | BA  | BX  | BZR | BDL | BDU |
	 *   -----+-----+-----+-----+-----+-----+-----+-----+-----+
	 *   11   |  1  |     BATTERY     | USB |CHARG|LTHUM|RTHUM|
	 *   -----+-----+-----------------+-----------+-----+-----+
	 * All buttons are low-active (0 अगर pressed)
	 * RX and RY are right analog stick
	 * LX and LY are left analog stick
	 * BLT is left trigger, BRT is right trigger.
	 * BDR, BDD, BDL, BDU क्रमm the D-Pad with right, करोwn, left, up buttons
	 * BZL is left Z button and BZR is right Z button
	 * B-, BH, B+ are +, HOME and - buttons
	 * BB, BY, BA, BX are A, B, X, Y buttons
	 *
	 * Bits marked as 0/1 are unknown and never changed during tests.
	 *
	 * Not entirely verअगरied:
	 *   CHARG: 1 अगर unअक्षरging, 0 अगर अक्षरging
	 *   USB: 1 अगर not connected, 0 अगर connected
	 *   BATTERY: battery capacity from 000 (empty) to 100 (full)
	 */

	lx = (ext[0] & 0xff) | ((ext[1] & 0x0f) << 8);
	rx = (ext[2] & 0xff) | ((ext[3] & 0x0f) << 8);
	ly = (ext[4] & 0xff) | ((ext[5] & 0x0f) << 8);
	ry = (ext[6] & 0xff) | ((ext[7] & 0x0f) << 8);

	/* zero-poपूर्णांक offsets */
	lx -= 0x800;
	ly = 0x800 - ly;
	rx -= 0x800;
	ry = 0x800 - ry;

	/* Trivial स्वतःmatic calibration. We करोn't know any calibration data
	 * in the EEPROM so we must use the first report to calibrate the
	 * null-position of the analog sticks. Users can retrigger calibration
	 * via sysfs, or set it explicitly. If data is off more than असल(500),
	 * we skip calibration as the sticks are likely to be moved alपढ़ोy. */
	अगर (!(wdata->state.flags & WIIPROTO_FLAG_PRO_CALIB_DONE)) अणु
		wdata->state.flags |= WIIPROTO_FLAG_PRO_CALIB_DONE;
		अगर (असल(lx) < 500)
			wdata->state.calib_pro_sticks[0] = -lx;
		अगर (असल(ly) < 500)
			wdata->state.calib_pro_sticks[1] = -ly;
		अगर (असल(rx) < 500)
			wdata->state.calib_pro_sticks[2] = -rx;
		अगर (असल(ry) < 500)
			wdata->state.calib_pro_sticks[3] = -ry;
	पूर्ण

	/* apply calibration data */
	lx += wdata->state.calib_pro_sticks[0];
	ly += wdata->state.calib_pro_sticks[1];
	rx += wdata->state.calib_pro_sticks[2];
	ry += wdata->state.calib_pro_sticks[3];

	input_report_असल(wdata->extension.input, ABS_X, lx);
	input_report_असल(wdata->extension.input, ABS_Y, ly);
	input_report_असल(wdata->extension.input, ABS_RX, rx);
	input_report_असल(wdata->extension.input, ABS_RY, ry);

	input_report_key(wdata->extension.input,
			 wiimod_pro_map[WIIMOD_PRO_KEY_RIGHT],
			 !(ext[8] & 0x80));
	input_report_key(wdata->extension.input,
			 wiimod_pro_map[WIIMOD_PRO_KEY_DOWN],
			 !(ext[8] & 0x40));
	input_report_key(wdata->extension.input,
			 wiimod_pro_map[WIIMOD_PRO_KEY_TL],
			 !(ext[8] & 0x20));
	input_report_key(wdata->extension.input,
			 wiimod_pro_map[WIIMOD_PRO_KEY_MINUS],
			 !(ext[8] & 0x10));
	input_report_key(wdata->extension.input,
			 wiimod_pro_map[WIIMOD_PRO_KEY_HOME],
			 !(ext[8] & 0x08));
	input_report_key(wdata->extension.input,
			 wiimod_pro_map[WIIMOD_PRO_KEY_PLUS],
			 !(ext[8] & 0x04));
	input_report_key(wdata->extension.input,
			 wiimod_pro_map[WIIMOD_PRO_KEY_TR],
			 !(ext[8] & 0x02));

	input_report_key(wdata->extension.input,
			 wiimod_pro_map[WIIMOD_PRO_KEY_ZL],
			 !(ext[9] & 0x80));
	input_report_key(wdata->extension.input,
			 wiimod_pro_map[WIIMOD_PRO_KEY_B],
			 !(ext[9] & 0x40));
	input_report_key(wdata->extension.input,
			 wiimod_pro_map[WIIMOD_PRO_KEY_Y],
			 !(ext[9] & 0x20));
	input_report_key(wdata->extension.input,
			 wiimod_pro_map[WIIMOD_PRO_KEY_A],
			 !(ext[9] & 0x10));
	input_report_key(wdata->extension.input,
			 wiimod_pro_map[WIIMOD_PRO_KEY_X],
			 !(ext[9] & 0x08));
	input_report_key(wdata->extension.input,
			 wiimod_pro_map[WIIMOD_PRO_KEY_ZR],
			 !(ext[9] & 0x04));
	input_report_key(wdata->extension.input,
			 wiimod_pro_map[WIIMOD_PRO_KEY_LEFT],
			 !(ext[9] & 0x02));
	input_report_key(wdata->extension.input,
			 wiimod_pro_map[WIIMOD_PRO_KEY_UP],
			 !(ext[9] & 0x01));

	input_report_key(wdata->extension.input,
			 wiimod_pro_map[WIIMOD_PRO_KEY_THUMBL],
			 !(ext[10] & 0x02));
	input_report_key(wdata->extension.input,
			 wiimod_pro_map[WIIMOD_PRO_KEY_THUMBR],
			 !(ext[10] & 0x01));

	input_sync(wdata->extension.input);
पूर्ण

अटल पूर्णांक wiimod_pro_खोलो(काष्ठा input_dev *dev)
अणु
	काष्ठा wiimote_data *wdata = input_get_drvdata(dev);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&wdata->state.lock, flags);
	wdata->state.flags |= WIIPROTO_FLAG_EXT_USED;
	wiiproto_req_drm(wdata, WIIPROTO_REQ_शून्य);
	spin_unlock_irqrestore(&wdata->state.lock, flags);

	वापस 0;
पूर्ण

अटल व्योम wiimod_pro_बंद(काष्ठा input_dev *dev)
अणु
	काष्ठा wiimote_data *wdata = input_get_drvdata(dev);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&wdata->state.lock, flags);
	wdata->state.flags &= ~WIIPROTO_FLAG_EXT_USED;
	wiiproto_req_drm(wdata, WIIPROTO_REQ_शून्य);
	spin_unlock_irqrestore(&wdata->state.lock, flags);
पूर्ण

अटल पूर्णांक wiimod_pro_play(काष्ठा input_dev *dev, व्योम *data,
			   काष्ठा ff_effect *eff)
अणु
	काष्ठा wiimote_data *wdata = input_get_drvdata(dev);
	__u8 value;

	/*
	 * The wiimote supports only a single rumble motor so अगर any magnitude
	 * is set to non-zero then we start the rumble motor. If both are set to
	 * zero, we stop the rumble motor.
	 */

	अगर (eff->u.rumble.strong_magnitude || eff->u.rumble.weak_magnitude)
		value = 1;
	अन्यथा
		value = 0;

	/* Locking state.lock here might deadlock with input_event() calls.
	 * schedule_work acts as barrier. Merging multiple changes is fine. */
	wdata->state.cache_rumble = value;
	schedule_work(&wdata->rumble_worker);

	वापस 0;
पूर्ण

अटल sमाप_प्रकार wiimod_pro_calib_show(काष्ठा device *dev,
				     काष्ठा device_attribute *attr,
				     अक्षर *out)
अणु
	काष्ठा wiimote_data *wdata = dev_to_wii(dev);
	पूर्णांक r;

	r = 0;
	r += प्र_लिखो(&out[r], "%+06hd:", wdata->state.calib_pro_sticks[0]);
	r += प्र_लिखो(&out[r], "%+06hd ", wdata->state.calib_pro_sticks[1]);
	r += प्र_लिखो(&out[r], "%+06hd:", wdata->state.calib_pro_sticks[2]);
	r += प्र_लिखो(&out[r], "%+06hd\n", wdata->state.calib_pro_sticks[3]);

	वापस r;
पूर्ण

अटल sमाप_प्रकार wiimod_pro_calib_store(काष्ठा device *dev,
				      काष्ठा device_attribute *attr,
				      स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा wiimote_data *wdata = dev_to_wii(dev);
	पूर्णांक r;
	s16 x1, y1, x2, y2;

	अगर (!म_भेदन(buf, "scan\n", 5)) अणु
		spin_lock_irq(&wdata->state.lock);
		wdata->state.flags &= ~WIIPROTO_FLAG_PRO_CALIB_DONE;
		spin_unlock_irq(&wdata->state.lock);
	पूर्ण अन्यथा अणु
		r = माला_पूछो(buf, "%hd:%hd %hd:%hd", &x1, &y1, &x2, &y2);
		अगर (r != 4)
			वापस -EINVAL;

		spin_lock_irq(&wdata->state.lock);
		wdata->state.flags |= WIIPROTO_FLAG_PRO_CALIB_DONE;
		spin_unlock_irq(&wdata->state.lock);

		wdata->state.calib_pro_sticks[0] = x1;
		wdata->state.calib_pro_sticks[1] = y1;
		wdata->state.calib_pro_sticks[2] = x2;
		wdata->state.calib_pro_sticks[3] = y2;
	पूर्ण

	वापस strnlen(buf, PAGE_SIZE);
पूर्ण

अटल DEVICE_ATTR(pro_calib, S_IRUGO|S_IWUSR|S_IWGRP, wiimod_pro_calib_show,
		   wiimod_pro_calib_store);

अटल पूर्णांक wiimod_pro_probe(स्थिर काष्ठा wiimod_ops *ops,
			    काष्ठा wiimote_data *wdata)
अणु
	पूर्णांक ret, i;
	अचिन्हित दीर्घ flags;

	INIT_WORK(&wdata->rumble_worker, wiimod_rumble_worker);
	wdata->state.calib_pro_sticks[0] = 0;
	wdata->state.calib_pro_sticks[1] = 0;
	wdata->state.calib_pro_sticks[2] = 0;
	wdata->state.calib_pro_sticks[3] = 0;

	spin_lock_irqsave(&wdata->state.lock, flags);
	wdata->state.flags &= ~WIIPROTO_FLAG_PRO_CALIB_DONE;
	spin_unlock_irqrestore(&wdata->state.lock, flags);

	wdata->extension.input = input_allocate_device();
	अगर (!wdata->extension.input)
		वापस -ENOMEM;

	set_bit(FF_RUMBLE, wdata->extension.input->ffbit);
	input_set_drvdata(wdata->extension.input, wdata);

	अगर (input_ff_create_memless(wdata->extension.input, शून्य,
				    wiimod_pro_play)) अणु
		ret = -ENOMEM;
		जाओ err_मुक्त;
	पूर्ण

	ret = device_create_file(&wdata->hdev->dev,
				 &dev_attr_pro_calib);
	अगर (ret) अणु
		hid_err(wdata->hdev, "cannot create sysfs attribute\n");
		जाओ err_मुक्त;
	पूर्ण

	wdata->extension.input->खोलो = wiimod_pro_खोलो;
	wdata->extension.input->बंद = wiimod_pro_बंद;
	wdata->extension.input->dev.parent = &wdata->hdev->dev;
	wdata->extension.input->id.bustype = wdata->hdev->bus;
	wdata->extension.input->id.venकरोr = wdata->hdev->venकरोr;
	wdata->extension.input->id.product = wdata->hdev->product;
	wdata->extension.input->id.version = wdata->hdev->version;
	wdata->extension.input->name = WIIMOTE_NAME " Pro Controller";

	set_bit(EV_KEY, wdata->extension.input->evbit);
	क्रम (i = 0; i < WIIMOD_PRO_KEY_NUM; ++i)
		set_bit(wiimod_pro_map[i],
			wdata->extension.input->keybit);

	set_bit(EV_ABS, wdata->extension.input->evbit);
	set_bit(ABS_X, wdata->extension.input->असलbit);
	set_bit(ABS_Y, wdata->extension.input->असलbit);
	set_bit(ABS_RX, wdata->extension.input->असलbit);
	set_bit(ABS_RY, wdata->extension.input->असलbit);
	input_set_असल_params(wdata->extension.input,
			     ABS_X, -0x400, 0x400, 4, 100);
	input_set_असल_params(wdata->extension.input,
			     ABS_Y, -0x400, 0x400, 4, 100);
	input_set_असल_params(wdata->extension.input,
			     ABS_RX, -0x400, 0x400, 4, 100);
	input_set_असल_params(wdata->extension.input,
			     ABS_RY, -0x400, 0x400, 4, 100);

	ret = input_रेजिस्टर_device(wdata->extension.input);
	अगर (ret)
		जाओ err_file;

	वापस 0;

err_file:
	device_हटाओ_file(&wdata->hdev->dev,
			   &dev_attr_pro_calib);
err_मुक्त:
	input_मुक्त_device(wdata->extension.input);
	wdata->extension.input = शून्य;
	वापस ret;
पूर्ण

अटल व्योम wiimod_pro_हटाओ(स्थिर काष्ठा wiimod_ops *ops,
			      काष्ठा wiimote_data *wdata)
अणु
	अचिन्हित दीर्घ flags;

	अगर (!wdata->extension.input)
		वापस;

	input_unरेजिस्टर_device(wdata->extension.input);
	wdata->extension.input = शून्य;
	cancel_work_sync(&wdata->rumble_worker);
	device_हटाओ_file(&wdata->hdev->dev,
			   &dev_attr_pro_calib);

	spin_lock_irqsave(&wdata->state.lock, flags);
	wiiproto_req_rumble(wdata, 0);
	spin_unlock_irqrestore(&wdata->state.lock, flags);
पूर्ण

अटल स्थिर काष्ठा wiimod_ops wiimod_pro = अणु
	.flags = WIIMOD_FLAG_EXT16,
	.arg = 0,
	.probe = wiimod_pro_probe,
	.हटाओ = wiimod_pro_हटाओ,
	.in_ext = wiimod_pro_in_ext,
पूर्ण;

/*
 * Drums
 * Guitar-Hero, Rock-Band and other games came bundled with drums which can
 * be plugged as extension to a Wiimote. Drum-reports are still not entirely
 * figured out, but the most important inक्रमmation is known.
 * We create a separate device क्रम drums and report all inक्रमmation via this
 * input device.
 */

अटल अंतरभूत व्योम wiimod_drums_report_pressure(काष्ठा wiimote_data *wdata,
						__u8 none, __u8 which,
						__u8 pressure, __u8 onoff,
						__u8 *store, __u16 code,
						__u8 which_code)
अणु
	अटल स्थिर __u8 शेष_pressure = 3;

	अगर (!none && which == which_code) अणु
		*store = pressure;
		input_report_असल(wdata->extension.input, code, *store);
	पूर्ण अन्यथा अगर (onoff != !!*store) अणु
		*store = onoff ? शेष_pressure : 0;
		input_report_असल(wdata->extension.input, code, *store);
	पूर्ण
पूर्ण

अटल व्योम wiimod_drums_in_ext(काष्ठा wiimote_data *wdata, स्थिर __u8 *ext)
अणु
	__u8 pressure, which, none, hhp, sx, sy;
	__u8 o, r, y, g, b, bass, bm, bp;

	/*   Byte |  8  |  7  |  6  |  5  |  4  |  3  |  2  |  1  |
	 *   -----+-----+-----+-----+-----+-----+-----+-----+-----+
	 *    1   |  0  |  0  |              SX <5:0>             |
	 *    2   |  0  |  0  |              SY <5:0>             |
	 *   -----+-----+-----+-----------------------------+-----+
	 *    3   | HPP | NON |         WHICH <5:1>         |  ?  |
	 *   -----+-----+-----+-----+-----+-----+-----+-----+-----+
	 *    4   |   SOFT <7:5>    |  0  |  1  |  1  |  0  |  ?  |
	 *   -----+-----+-----+-----+-----+-----+-----+-----+-----+
	 *    5   |  ?  |  1  |  1  | B-  |  1  | B+  |  1  |  ?  |
	 *   -----+-----+-----+-----+-----+-----+-----+-----+-----+
	 *    6   |  O  |  R  |  Y  |  G  |  B  | BSS |  1  |  1  |
	 *   -----+-----+-----+-----+-----+-----+-----+-----+-----+
	 * All buttons are 0 अगर pressed
	 *
	 * With Motion+ enabled, the following bits will get invalid:
	 *   Byte |  8  |  7  |  6  |  5  |  4  |  3  |  2  |  1  |
	 *   -----+-----+-----+-----+-----+-----+-----+-----+-----+
	 *    1   |  0  |  0  |              SX <5:1>       |XXXXX|
	 *    2   |  0  |  0  |              SY <5:1>       |XXXXX|
	 *   -----+-----+-----+-----------------------------+-----+
	 *    3   | HPP | NON |         WHICH <5:1>         |  ?  |
	 *   -----+-----+-----+-----+-----+-----+-----+-----+-----+
	 *    4   |   SOFT <7:5>    |  0  |  1  |  1  |  0  |  ?  |
	 *   -----+-----+-----+-----+-----+-----+-----+-----+-----+
	 *    5   |  ?  |  1  |  1  | B-  |  1  | B+  |  1  |XXXXX|
	 *   -----+-----+-----+-----+-----+-----+-----+-----+-----+
	 *    6   |  O  |  R  |  Y  |  G  |  B  | BSS |XXXXX|XXXXX|
	 *   -----+-----+-----+-----+-----+-----+-----+-----+-----+
	 */

	pressure = 7 - (ext[3] >> 5);
	which = (ext[2] >> 1) & 0x1f;
	none = !!(ext[2] & 0x40);
	hhp = !(ext[2] & 0x80);
	sx = ext[0] & 0x3f;
	sy = ext[1] & 0x3f;
	o = !(ext[5] & 0x80);
	r = !(ext[5] & 0x40);
	y = !(ext[5] & 0x20);
	g = !(ext[5] & 0x10);
	b = !(ext[5] & 0x08);
	bass = !(ext[5] & 0x04);
	bm = !(ext[4] & 0x10);
	bp = !(ext[4] & 0x04);

	अगर (wdata->state.flags & WIIPROTO_FLAG_MP_ACTIVE) अणु
		sx &= 0x3e;
		sy &= 0x3e;
	पूर्ण

	wiimod_drums_report_pressure(wdata, none, which, pressure,
				     o, &wdata->state.pressure_drums[0],
				     ABS_HAT2Y, 0x0e);
	wiimod_drums_report_pressure(wdata, none, which, pressure,
				     r, &wdata->state.pressure_drums[1],
				     ABS_HAT0X, 0x19);
	wiimod_drums_report_pressure(wdata, none, which, pressure,
				     y, &wdata->state.pressure_drums[2],
				     ABS_HAT2X, 0x11);
	wiimod_drums_report_pressure(wdata, none, which, pressure,
				     g, &wdata->state.pressure_drums[3],
				     ABS_HAT1X, 0x12);
	wiimod_drums_report_pressure(wdata, none, which, pressure,
				     b, &wdata->state.pressure_drums[4],
				     ABS_HAT0Y, 0x0f);

	/* Bass shares pressure with hi-hat (set via hhp) */
	wiimod_drums_report_pressure(wdata, none, hhp ? 0xff : which, pressure,
				     bass, &wdata->state.pressure_drums[5],
				     ABS_HAT3X, 0x1b);
	/* Hi-hat has no on/off values, just pressure. Force to off/0. */
	wiimod_drums_report_pressure(wdata, none, hhp ? which : 0xff, pressure,
				     0, &wdata->state.pressure_drums[6],
				     ABS_HAT3Y, 0x0e);

	input_report_असल(wdata->extension.input, ABS_X, sx - 0x20);
	input_report_असल(wdata->extension.input, ABS_Y, sy - 0x20);

	input_report_key(wdata->extension.input, BTN_START, bp);
	input_report_key(wdata->extension.input, BTN_SELECT, bm);

	input_sync(wdata->extension.input);
पूर्ण

अटल पूर्णांक wiimod_drums_खोलो(काष्ठा input_dev *dev)
अणु
	काष्ठा wiimote_data *wdata = input_get_drvdata(dev);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&wdata->state.lock, flags);
	wdata->state.flags |= WIIPROTO_FLAG_EXT_USED;
	wiiproto_req_drm(wdata, WIIPROTO_REQ_शून्य);
	spin_unlock_irqrestore(&wdata->state.lock, flags);

	वापस 0;
पूर्ण

अटल व्योम wiimod_drums_बंद(काष्ठा input_dev *dev)
अणु
	काष्ठा wiimote_data *wdata = input_get_drvdata(dev);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&wdata->state.lock, flags);
	wdata->state.flags &= ~WIIPROTO_FLAG_EXT_USED;
	wiiproto_req_drm(wdata, WIIPROTO_REQ_शून्य);
	spin_unlock_irqrestore(&wdata->state.lock, flags);
पूर्ण

अटल पूर्णांक wiimod_drums_probe(स्थिर काष्ठा wiimod_ops *ops,
			      काष्ठा wiimote_data *wdata)
अणु
	पूर्णांक ret;

	wdata->extension.input = input_allocate_device();
	अगर (!wdata->extension.input)
		वापस -ENOMEM;

	input_set_drvdata(wdata->extension.input, wdata);
	wdata->extension.input->खोलो = wiimod_drums_खोलो;
	wdata->extension.input->बंद = wiimod_drums_बंद;
	wdata->extension.input->dev.parent = &wdata->hdev->dev;
	wdata->extension.input->id.bustype = wdata->hdev->bus;
	wdata->extension.input->id.venकरोr = wdata->hdev->venकरोr;
	wdata->extension.input->id.product = wdata->hdev->product;
	wdata->extension.input->id.version = wdata->hdev->version;
	wdata->extension.input->name = WIIMOTE_NAME " Drums";

	set_bit(EV_KEY, wdata->extension.input->evbit);
	set_bit(BTN_START, wdata->extension.input->keybit);
	set_bit(BTN_SELECT, wdata->extension.input->keybit);

	set_bit(EV_ABS, wdata->extension.input->evbit);
	set_bit(ABS_X, wdata->extension.input->असलbit);
	set_bit(ABS_Y, wdata->extension.input->असलbit);
	set_bit(ABS_HAT0X, wdata->extension.input->असलbit);
	set_bit(ABS_HAT0Y, wdata->extension.input->असलbit);
	set_bit(ABS_HAT1X, wdata->extension.input->असलbit);
	set_bit(ABS_HAT2X, wdata->extension.input->असलbit);
	set_bit(ABS_HAT2Y, wdata->extension.input->असलbit);
	set_bit(ABS_HAT3X, wdata->extension.input->असलbit);
	set_bit(ABS_HAT3Y, wdata->extension.input->असलbit);
	input_set_असल_params(wdata->extension.input,
			     ABS_X, -32, 31, 1, 1);
	input_set_असल_params(wdata->extension.input,
			     ABS_Y, -32, 31, 1, 1);
	input_set_असल_params(wdata->extension.input,
			     ABS_HAT0X, 0, 7, 0, 0);
	input_set_असल_params(wdata->extension.input,
			     ABS_HAT0Y, 0, 7, 0, 0);
	input_set_असल_params(wdata->extension.input,
			     ABS_HAT1X, 0, 7, 0, 0);
	input_set_असल_params(wdata->extension.input,
			     ABS_HAT2X, 0, 7, 0, 0);
	input_set_असल_params(wdata->extension.input,
			     ABS_HAT2Y, 0, 7, 0, 0);
	input_set_असल_params(wdata->extension.input,
			     ABS_HAT3X, 0, 7, 0, 0);
	input_set_असल_params(wdata->extension.input,
			     ABS_HAT3Y, 0, 7, 0, 0);

	ret = input_रेजिस्टर_device(wdata->extension.input);
	अगर (ret)
		जाओ err_मुक्त;

	वापस 0;

err_मुक्त:
	input_मुक्त_device(wdata->extension.input);
	wdata->extension.input = शून्य;
	वापस ret;
पूर्ण

अटल व्योम wiimod_drums_हटाओ(स्थिर काष्ठा wiimod_ops *ops,
				काष्ठा wiimote_data *wdata)
अणु
	अगर (!wdata->extension.input)
		वापस;

	input_unरेजिस्टर_device(wdata->extension.input);
	wdata->extension.input = शून्य;
पूर्ण

अटल स्थिर काष्ठा wiimod_ops wiimod_drums = अणु
	.flags = 0,
	.arg = 0,
	.probe = wiimod_drums_probe,
	.हटाओ = wiimod_drums_हटाओ,
	.in_ext = wiimod_drums_in_ext,
पूर्ण;

/*
 * Guitar
 * Guitar-Hero, Rock-Band and other games came bundled with guitars which can
 * be plugged as extension to a Wiimote.
 * We create a separate device क्रम guitars and report all inक्रमmation via this
 * input device.
 */

क्रमागत wiimod_guitar_keys अणु
	WIIMOD_GUITAR_KEY_G,
	WIIMOD_GUITAR_KEY_R,
	WIIMOD_GUITAR_KEY_Y,
	WIIMOD_GUITAR_KEY_B,
	WIIMOD_GUITAR_KEY_O,
	WIIMOD_GUITAR_KEY_UP,
	WIIMOD_GUITAR_KEY_DOWN,
	WIIMOD_GUITAR_KEY_PLUS,
	WIIMOD_GUITAR_KEY_MINUS,
	WIIMOD_GUITAR_KEY_NUM,
पूर्ण;

अटल स्थिर __u16 wiimod_guitar_map[] = अणु
	BTN_1,			/* WIIMOD_GUITAR_KEY_G */
	BTN_2,			/* WIIMOD_GUITAR_KEY_R */
	BTN_3,			/* WIIMOD_GUITAR_KEY_Y */
	BTN_4,			/* WIIMOD_GUITAR_KEY_B */
	BTN_5,			/* WIIMOD_GUITAR_KEY_O */
	BTN_DPAD_UP,		/* WIIMOD_GUITAR_KEY_UP */
	BTN_DPAD_DOWN,		/* WIIMOD_GUITAR_KEY_DOWN */
	BTN_START,		/* WIIMOD_GUITAR_KEY_PLUS */
	BTN_SELECT,		/* WIIMOD_GUITAR_KEY_MINUS */
पूर्ण;

अटल व्योम wiimod_guitar_in_ext(काष्ठा wiimote_data *wdata, स्थिर __u8 *ext)
अणु
	__u8 sx, sy, tb, wb, bd, bm, bp, bo, br, bb, bg, by, bu;

	/*   Byte |  8  |  7  |  6  |  5  |  4  |  3  |  2  |  1  |
	 *   -----+-----+-----+-----+-----+-----+-----+-----+-----+
	 *    1   |  0  |  0  |              SX <5:0>             |
	 *    2   |  0  |  0  |              SY <5:0>             |
	 *   -----+-----+-----+-----+-----------------------------+
	 *    3   |  0  |  0  |  0  |      TB <4:0>               |
	 *   -----+-----+-----+-----+-----------------------------+
	 *    4   |  0  |  0  |  0  |      WB <4:0>               |
	 *   -----+-----+-----+-----+-----+-----+-----+-----+-----+
	 *    5   |  1  | BD  |  1  | B-  |  1  | B+  |  1  |  1  |
	 *   -----+-----+-----+-----+-----+-----+-----+-----+-----+
	 *    6   | BO  | BR  | BB  | BG  | BY  |  1  |  1  | BU  |
	 *   -----+-----+-----+-----+-----+-----+-----+-----+-----+
	 * All buttons are 0 अगर pressed
	 *
	 * With Motion+ enabled, it will look like this:
	 *   Byte |  8  |  7  |  6  |  5  |  4  |  3  |  2  |  1  |
	 *   -----+-----+-----+-----+-----+-----+-----+-----+-----+
	 *    1   |  0  |  0  |              SX <5:1>       | BU  |
	 *    2   |  0  |  0  |              SY <5:1>       |  1  |
	 *   -----+-----+-----+-----+-----------------------+-----+
	 *    3   |  0  |  0  |  0  |      TB <4:0>               |
	 *   -----+-----+-----+-----+-----------------------------+
	 *    4   |  0  |  0  |  0  |      WB <4:0>               |
	 *   -----+-----+-----+-----+-----+-----+-----+-----+-----+
	 *    5   |  1  | BD  |  1  | B-  |  1  | B+  |  1  |XXXXX|
	 *   -----+-----+-----+-----+-----+-----+-----+-----+-----+
	 *    6   | BO  | BR  | BB  | BG  | BY  |  1  |XXXXX|XXXXX|
	 *   -----+-----+-----+-----+-----+-----+-----+-----+-----+
	 */

	sx = ext[0] & 0x3f;
	sy = ext[1] & 0x3f;
	tb = ext[2] & 0x1f;
	wb = ext[3] & 0x1f;
	bd = !(ext[4] & 0x40);
	bm = !(ext[4] & 0x10);
	bp = !(ext[4] & 0x04);
	bo = !(ext[5] & 0x80);
	br = !(ext[5] & 0x40);
	bb = !(ext[5] & 0x20);
	bg = !(ext[5] & 0x10);
	by = !(ext[5] & 0x08);
	bu = !(ext[5] & 0x01);

	अगर (wdata->state.flags & WIIPROTO_FLAG_MP_ACTIVE) अणु
		bu = !(ext[0] & 0x01);
		sx &= 0x3e;
		sy &= 0x3e;
	पूर्ण

	input_report_असल(wdata->extension.input, ABS_X, sx - 0x20);
	input_report_असल(wdata->extension.input, ABS_Y, sy - 0x20);
	input_report_असल(wdata->extension.input, ABS_HAT0X, tb);
	input_report_असल(wdata->extension.input, ABS_HAT1X, wb - 0x10);

	input_report_key(wdata->extension.input,
			 wiimod_guitar_map[WIIMOD_GUITAR_KEY_G],
			 bg);
	input_report_key(wdata->extension.input,
			 wiimod_guitar_map[WIIMOD_GUITAR_KEY_R],
			 br);
	input_report_key(wdata->extension.input,
			 wiimod_guitar_map[WIIMOD_GUITAR_KEY_Y],
			 by);
	input_report_key(wdata->extension.input,
			 wiimod_guitar_map[WIIMOD_GUITAR_KEY_B],
			 bb);
	input_report_key(wdata->extension.input,
			 wiimod_guitar_map[WIIMOD_GUITAR_KEY_O],
			 bo);
	input_report_key(wdata->extension.input,
			 wiimod_guitar_map[WIIMOD_GUITAR_KEY_UP],
			 bu);
	input_report_key(wdata->extension.input,
			 wiimod_guitar_map[WIIMOD_GUITAR_KEY_DOWN],
			 bd);
	input_report_key(wdata->extension.input,
			 wiimod_guitar_map[WIIMOD_GUITAR_KEY_PLUS],
			 bp);
	input_report_key(wdata->extension.input,
			 wiimod_guitar_map[WIIMOD_GUITAR_KEY_MINUS],
			 bm);

	input_sync(wdata->extension.input);
पूर्ण

अटल पूर्णांक wiimod_guitar_खोलो(काष्ठा input_dev *dev)
अणु
	काष्ठा wiimote_data *wdata = input_get_drvdata(dev);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&wdata->state.lock, flags);
	wdata->state.flags |= WIIPROTO_FLAG_EXT_USED;
	wiiproto_req_drm(wdata, WIIPROTO_REQ_शून्य);
	spin_unlock_irqrestore(&wdata->state.lock, flags);

	वापस 0;
पूर्ण

अटल व्योम wiimod_guitar_बंद(काष्ठा input_dev *dev)
अणु
	काष्ठा wiimote_data *wdata = input_get_drvdata(dev);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&wdata->state.lock, flags);
	wdata->state.flags &= ~WIIPROTO_FLAG_EXT_USED;
	wiiproto_req_drm(wdata, WIIPROTO_REQ_शून्य);
	spin_unlock_irqrestore(&wdata->state.lock, flags);
पूर्ण

अटल पूर्णांक wiimod_guitar_probe(स्थिर काष्ठा wiimod_ops *ops,
			       काष्ठा wiimote_data *wdata)
अणु
	पूर्णांक ret, i;

	wdata->extension.input = input_allocate_device();
	अगर (!wdata->extension.input)
		वापस -ENOMEM;

	input_set_drvdata(wdata->extension.input, wdata);
	wdata->extension.input->खोलो = wiimod_guitar_खोलो;
	wdata->extension.input->बंद = wiimod_guitar_बंद;
	wdata->extension.input->dev.parent = &wdata->hdev->dev;
	wdata->extension.input->id.bustype = wdata->hdev->bus;
	wdata->extension.input->id.venकरोr = wdata->hdev->venकरोr;
	wdata->extension.input->id.product = wdata->hdev->product;
	wdata->extension.input->id.version = wdata->hdev->version;
	wdata->extension.input->name = WIIMOTE_NAME " Guitar";

	set_bit(EV_KEY, wdata->extension.input->evbit);
	क्रम (i = 0; i < WIIMOD_GUITAR_KEY_NUM; ++i)
		set_bit(wiimod_guitar_map[i],
			wdata->extension.input->keybit);

	set_bit(EV_ABS, wdata->extension.input->evbit);
	set_bit(ABS_X, wdata->extension.input->असलbit);
	set_bit(ABS_Y, wdata->extension.input->असलbit);
	set_bit(ABS_HAT0X, wdata->extension.input->असलbit);
	set_bit(ABS_HAT1X, wdata->extension.input->असलbit);
	input_set_असल_params(wdata->extension.input,
			     ABS_X, -32, 31, 1, 1);
	input_set_असल_params(wdata->extension.input,
			     ABS_Y, -32, 31, 1, 1);
	input_set_असल_params(wdata->extension.input,
			     ABS_HAT0X, 0, 0x1f, 1, 1);
	input_set_असल_params(wdata->extension.input,
			     ABS_HAT1X, 0, 0x0f, 1, 1);

	ret = input_रेजिस्टर_device(wdata->extension.input);
	अगर (ret)
		जाओ err_मुक्त;

	वापस 0;

err_मुक्त:
	input_मुक्त_device(wdata->extension.input);
	wdata->extension.input = शून्य;
	वापस ret;
पूर्ण

अटल व्योम wiimod_guitar_हटाओ(स्थिर काष्ठा wiimod_ops *ops,
				 काष्ठा wiimote_data *wdata)
अणु
	अगर (!wdata->extension.input)
		वापस;

	input_unरेजिस्टर_device(wdata->extension.input);
	wdata->extension.input = शून्य;
पूर्ण

अटल स्थिर काष्ठा wiimod_ops wiimod_guitar = अणु
	.flags = 0,
	.arg = 0,
	.probe = wiimod_guitar_probe,
	.हटाओ = wiimod_guitar_हटाओ,
	.in_ext = wiimod_guitar_in_ext,
पूर्ण;

/*
 * Builtin Motion Plus
 * This module simply sets the WIIPROTO_FLAG_BUILTIN_MP protocol flag which
 * disables polling क्रम Motion-Plus. This should be set only क्रम devices which
 * करोn't allow MP hotplugging.
 */

अटल पूर्णांक wiimod_builtin_mp_probe(स्थिर काष्ठा wiimod_ops *ops,
				   काष्ठा wiimote_data *wdata)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&wdata->state.lock, flags);
	wdata->state.flags |= WIIPROTO_FLAG_BUILTIN_MP;
	spin_unlock_irqrestore(&wdata->state.lock, flags);

	वापस 0;
पूर्ण

अटल व्योम wiimod_builtin_mp_हटाओ(स्थिर काष्ठा wiimod_ops *ops,
				     काष्ठा wiimote_data *wdata)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&wdata->state.lock, flags);
	wdata->state.flags |= WIIPROTO_FLAG_BUILTIN_MP;
	spin_unlock_irqrestore(&wdata->state.lock, flags);
पूर्ण

अटल स्थिर काष्ठा wiimod_ops wiimod_builtin_mp = अणु
	.flags = 0,
	.arg = 0,
	.probe = wiimod_builtin_mp_probe,
	.हटाओ = wiimod_builtin_mp_हटाओ,
पूर्ण;

/*
 * No Motion Plus
 * This module simply sets the WIIPROTO_FLAG_NO_MP protocol flag which
 * disables motion-plus. This is needed क्रम devices that advertise this but we
 * करोn't know how to use it (or whether it is actually present).
 */

अटल पूर्णांक wiimod_no_mp_probe(स्थिर काष्ठा wiimod_ops *ops,
			      काष्ठा wiimote_data *wdata)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&wdata->state.lock, flags);
	wdata->state.flags |= WIIPROTO_FLAG_NO_MP;
	spin_unlock_irqrestore(&wdata->state.lock, flags);

	वापस 0;
पूर्ण

अटल व्योम wiimod_no_mp_हटाओ(स्थिर काष्ठा wiimod_ops *ops,
				काष्ठा wiimote_data *wdata)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&wdata->state.lock, flags);
	wdata->state.flags |= WIIPROTO_FLAG_NO_MP;
	spin_unlock_irqrestore(&wdata->state.lock, flags);
पूर्ण

अटल स्थिर काष्ठा wiimod_ops wiimod_no_mp = अणु
	.flags = 0,
	.arg = 0,
	.probe = wiimod_no_mp_probe,
	.हटाओ = wiimod_no_mp_हटाओ,
पूर्ण;

/*
 * Motion Plus
 * The Motion Plus extension provides rotation sensors (gyro) as a small
 * extension device क्रम Wii Remotes. Many devices have them built-in so
 * you cannot see them from the outside.
 * Motion Plus extensions are special because they are on a separate extension
 * port and allow other extensions to be used simultaneously. This is all
 * handled by the Wiimote Core so we करोn't have to deal with it.
 */

अटल व्योम wiimod_mp_in_mp(काष्ठा wiimote_data *wdata, स्थिर __u8 *ext)
अणु
	__s32 x, y, z;

	/*        |   8    7    6    5    4    3 |  2  |  1  |
	 *   -----+------------------------------+-----+-----+
	 *    1   |               Yaw Speed <7:0>            |
	 *    2   |              Roll Speed <7:0>            |
	 *    3   |             Pitch Speed <7:0>            |
	 *   -----+------------------------------+-----+-----+
	 *    4   |       Yaw Speed <13:8>       | Yaw |Pitch|
	 *   -----+------------------------------+-----+-----+
	 *    5   |      Roll Speed <13:8>       |Roll | Ext |
	 *   -----+------------------------------+-----+-----+
	 *    6   |     Pitch Speed <13:8>       |  1  |  0  |
	 *   -----+------------------------------+-----+-----+
	 * The single bits Yaw, Roll, Pitch in the lower right corner specअगरy
	 * whether the wiimote is rotating fast (0) or slow (1). Speed क्रम slow
	 * roation is 8192/440 units / deg/s and क्रम fast rotation 8192/2000
	 * units / deg/s. To get a linear scale क्रम fast rotation we multiply
	 * by 2000/440 = ~4.5454 and scale both fast and slow by 9 to match the
	 * previous scale reported by this driver.
	 * This leaves a linear scale with 8192*9/440 (~167.564) units / deg/s.
	 * If the wiimote is not rotating the sensor reports 2^13 = 8192.
	 * Ext specअगरies whether an extension is connected to the motionp.
	 * which is parsed by wiimote-core.
	 */

	x = ext[0];
	y = ext[1];
	z = ext[2];

	x |= (((__u16)ext[3]) << 6) & 0xff00;
	y |= (((__u16)ext[4]) << 6) & 0xff00;
	z |= (((__u16)ext[5]) << 6) & 0xff00;

	x -= 8192;
	y -= 8192;
	z -= 8192;

	अगर (!(ext[3] & 0x02))
		x = (x * 2000 * 9) / 440;
	अन्यथा
		x *= 9;
	अगर (!(ext[4] & 0x02))
		y = (y * 2000 * 9) / 440;
	अन्यथा
		y *= 9;
	अगर (!(ext[3] & 0x01))
		z = (z * 2000 * 9) / 440;
	अन्यथा
		z *= 9;

	input_report_असल(wdata->mp, ABS_RX, x);
	input_report_असल(wdata->mp, ABS_RY, y);
	input_report_असल(wdata->mp, ABS_RZ, z);
	input_sync(wdata->mp);
पूर्ण

अटल पूर्णांक wiimod_mp_खोलो(काष्ठा input_dev *dev)
अणु
	काष्ठा wiimote_data *wdata = input_get_drvdata(dev);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&wdata->state.lock, flags);
	wdata->state.flags |= WIIPROTO_FLAG_MP_USED;
	wiiproto_req_drm(wdata, WIIPROTO_REQ_शून्य);
	__wiimote_schedule(wdata);
	spin_unlock_irqrestore(&wdata->state.lock, flags);

	वापस 0;
पूर्ण

अटल व्योम wiimod_mp_बंद(काष्ठा input_dev *dev)
अणु
	काष्ठा wiimote_data *wdata = input_get_drvdata(dev);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&wdata->state.lock, flags);
	wdata->state.flags &= ~WIIPROTO_FLAG_MP_USED;
	wiiproto_req_drm(wdata, WIIPROTO_REQ_शून्य);
	__wiimote_schedule(wdata);
	spin_unlock_irqrestore(&wdata->state.lock, flags);
पूर्ण

अटल पूर्णांक wiimod_mp_probe(स्थिर काष्ठा wiimod_ops *ops,
			   काष्ठा wiimote_data *wdata)
अणु
	पूर्णांक ret;

	wdata->mp = input_allocate_device();
	अगर (!wdata->mp)
		वापस -ENOMEM;

	input_set_drvdata(wdata->mp, wdata);
	wdata->mp->खोलो = wiimod_mp_खोलो;
	wdata->mp->बंद = wiimod_mp_बंद;
	wdata->mp->dev.parent = &wdata->hdev->dev;
	wdata->mp->id.bustype = wdata->hdev->bus;
	wdata->mp->id.venकरोr = wdata->hdev->venकरोr;
	wdata->mp->id.product = wdata->hdev->product;
	wdata->mp->id.version = wdata->hdev->version;
	wdata->mp->name = WIIMOTE_NAME " Motion Plus";

	set_bit(EV_ABS, wdata->mp->evbit);
	set_bit(ABS_RX, wdata->mp->असलbit);
	set_bit(ABS_RY, wdata->mp->असलbit);
	set_bit(ABS_RZ, wdata->mp->असलbit);
	input_set_असल_params(wdata->mp,
			     ABS_RX, -16000, 16000, 4, 8);
	input_set_असल_params(wdata->mp,
			     ABS_RY, -16000, 16000, 4, 8);
	input_set_असल_params(wdata->mp,
			     ABS_RZ, -16000, 16000, 4, 8);

	ret = input_रेजिस्टर_device(wdata->mp);
	अगर (ret)
		जाओ err_मुक्त;

	वापस 0;

err_मुक्त:
	input_मुक्त_device(wdata->mp);
	wdata->mp = शून्य;
	वापस ret;
पूर्ण

अटल व्योम wiimod_mp_हटाओ(स्थिर काष्ठा wiimod_ops *ops,
			     काष्ठा wiimote_data *wdata)
अणु
	अगर (!wdata->mp)
		वापस;

	input_unरेजिस्टर_device(wdata->mp);
	wdata->mp = शून्य;
पूर्ण

स्थिर काष्ठा wiimod_ops wiimod_mp = अणु
	.flags = 0,
	.arg = 0,
	.probe = wiimod_mp_probe,
	.हटाओ = wiimod_mp_हटाओ,
	.in_mp = wiimod_mp_in_mp,
पूर्ण;

/* module table */

अटल स्थिर काष्ठा wiimod_ops wiimod_dummy;

स्थिर काष्ठा wiimod_ops *wiimod_table[WIIMOD_NUM] = अणु
	[WIIMOD_KEYS] = &wiimod_keys,
	[WIIMOD_RUMBLE] = &wiimod_rumble,
	[WIIMOD_BATTERY] = &wiimod_battery,
	[WIIMOD_LED1] = &wiimod_leds[0],
	[WIIMOD_LED2] = &wiimod_leds[1],
	[WIIMOD_LED3] = &wiimod_leds[2],
	[WIIMOD_LED4] = &wiimod_leds[3],
	[WIIMOD_ACCEL] = &wiimod_accel,
	[WIIMOD_IR] = &wiimod_ir,
	[WIIMOD_BUILTIN_MP] = &wiimod_builtin_mp,
	[WIIMOD_NO_MP] = &wiimod_no_mp,
पूर्ण;

स्थिर काष्ठा wiimod_ops *wiimod_ext_table[WIIMOTE_EXT_NUM] = अणु
	[WIIMOTE_EXT_NONE] = &wiimod_dummy,
	[WIIMOTE_EXT_UNKNOWN] = &wiimod_dummy,
	[WIIMOTE_EXT_NUNCHUK] = &wiimod_nunchuk,
	[WIIMOTE_EXT_CLASSIC_CONTROLLER] = &wiimod_classic,
	[WIIMOTE_EXT_BALANCE_BOARD] = &wiimod_bboard,
	[WIIMOTE_EXT_PRO_CONTROLLER] = &wiimod_pro,
	[WIIMOTE_EXT_DRUMS] = &wiimod_drums,
	[WIIMOTE_EXT_GUITAR] = &wiimod_guitar,
पूर्ण;
