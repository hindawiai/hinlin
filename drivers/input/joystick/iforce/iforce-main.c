<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Copyright (c) 2000-2002 Vojtech Pavlik <vojtech@ucw.cz>
 *  Copyright (c) 2001-2002, 2007 Johann Deneux <johann.deneux@gmail.com>
 *
 *  USB/RS232 I-Force joysticks and wheels.
 */

#समावेश <यंत्र/unaligned.h>
#समावेश "iforce.h"

MODULE_AUTHOR("Vojtech Pavlik <vojtech@ucw.cz>, Johann Deneux <johann.deneux@gmail.com>");
MODULE_DESCRIPTION("Core I-Force joysticks and wheels driver");
MODULE_LICENSE("GPL");

अटल चिन्हित लघु btn_joystick[] =
अणु BTN_TRIGGER, BTN_TOP, BTN_THUMB, BTN_TOP2, BTN_BASE,
  BTN_BASE2, BTN_BASE3, BTN_BASE4, BTN_BASE5, BTN_A,
  BTN_B, BTN_C, BTN_DEAD, -1 पूर्ण;

अटल चिन्हित लघु btn_joystick_avb[] =
अणु BTN_TRIGGER, BTN_THUMB, BTN_TOP, BTN_TOP2, BTN_BASE,
  BTN_BASE2, BTN_BASE3, BTN_BASE4, BTN_DEAD, -1 पूर्ण;

अटल चिन्हित लघु btn_wheel[] =
अणु BTN_GEAR_DOWN, BTN_GEAR_UP, BTN_BASE, BTN_BASE2, BTN_BASE3,
  BTN_BASE4, BTN_BASE5, BTN_BASE6, -1 पूर्ण;

अटल चिन्हित लघु असल_joystick[] =
अणु ABS_X, ABS_Y, ABS_THROTTLE, ABS_HAT0X, ABS_HAT0Y, -1 पूर्ण;

अटल चिन्हित लघु असल_joystick_rudder[] =
अणु ABS_X, ABS_Y, ABS_THROTTLE, ABS_RUDDER, ABS_HAT0X, ABS_HAT0Y, -1 पूर्ण;

अटल चिन्हित लघु असल_avb_pegasus[] =
अणु ABS_X, ABS_Y, ABS_THROTTLE, ABS_RUDDER, ABS_HAT0X, ABS_HAT0Y,
  ABS_HAT1X, ABS_HAT1Y, -1 पूर्ण;

अटल चिन्हित लघु असल_wheel[] =
अणु ABS_WHEEL, ABS_GAS, ABS_BRAKE, ABS_HAT0X, ABS_HAT0Y, -1 पूर्ण;

अटल चिन्हित लघु ff_अगरorce[] =
अणु FF_PERIODIC, FF_CONSTANT, FF_SPRING, FF_DAMPER,
  FF_SQUARE, FF_TRIANGLE, FF_SINE, FF_SAW_UP, FF_SAW_DOWN, FF_GAIN,
  FF_AUTOCENTER, -1 पूर्ण;

अटल काष्ठा अगरorce_device अगरorce_device[] = अणु
	अणु 0x044f, 0xa01c, "Thrustmaster Motor Sport GT",		btn_wheel, असल_wheel, ff_अगरorce पूर्ण,
	अणु 0x046d, 0xc281, "Logitech WingMan Force",			btn_joystick, असल_joystick, ff_अगरorce पूर्ण,
	अणु 0x046d, 0xc291, "Logitech WingMan Formula Force",		btn_wheel, असल_wheel, ff_अगरorce पूर्ण,
	अणु 0x05ef, 0x020a, "AVB Top Shot Pegasus",			btn_joystick_avb, असल_avb_pegasus, ff_अगरorce पूर्ण,
	अणु 0x05ef, 0x8884, "AVB Mag Turbo Force",			btn_wheel, असल_wheel, ff_अगरorce पूर्ण,
	अणु 0x05ef, 0x8888, "AVB Top Shot Force Feedback Racing Wheel",	btn_wheel, असल_wheel, ff_अगरorce पूर्ण, //?
	अणु 0x061c, 0xc0a4, "ACT LABS Force RS",                          btn_wheel, असल_wheel, ff_अगरorce पूर्ण, //?
	अणु 0x061c, 0xc084, "ACT LABS Force RS",				btn_wheel, असल_wheel, ff_अगरorce पूर्ण,
	अणु 0x06a3, 0xff04, "Saitek R440 Force Wheel",			btn_wheel, असल_wheel, ff_अगरorce पूर्ण, //?
	अणु 0x06f8, 0x0001, "Guillemot Race Leader Force Feedback",	btn_wheel, असल_wheel, ff_अगरorce पूर्ण, //?
	अणु 0x06f8, 0x0001, "Guillemot Jet Leader Force Feedback",	btn_joystick, असल_joystick_rudder, ff_अगरorce पूर्ण,
	अणु 0x06f8, 0x0004, "Guillemot Force Feedback Racing Wheel",	btn_wheel, असल_wheel, ff_अगरorce पूर्ण, //?
	अणु 0x06f8, 0xa302, "Guillemot Jet Leader 3D",			btn_joystick, असल_joystick, ff_अगरorce पूर्ण, //?
	अणु 0x06d6, 0x29bc, "Trust Force Feedback Race Master",		btn_wheel, असल_wheel, ff_अगरorce पूर्ण,
	अणु 0x0000, 0x0000, "Unknown I-Force Device [%04x:%04x]",		btn_joystick, असल_joystick, ff_अगरorce पूर्ण
पूर्ण;

अटल पूर्णांक अगरorce_playback(काष्ठा input_dev *dev, पूर्णांक effect_id, पूर्णांक value)
अणु
	काष्ठा अगरorce *अगरorce = input_get_drvdata(dev);
	काष्ठा अगरorce_core_effect *core_effect = &अगरorce->core_effects[effect_id];

	अगर (value > 0)
		set_bit(FF_CORE_SHOULD_PLAY, core_effect->flags);
	अन्यथा
		clear_bit(FF_CORE_SHOULD_PLAY, core_effect->flags);

	अगरorce_control_playback(अगरorce, effect_id, value);
	वापस 0;
पूर्ण

अटल व्योम अगरorce_set_gain(काष्ठा input_dev *dev, u16 gain)
अणु
	काष्ठा अगरorce *अगरorce = input_get_drvdata(dev);
	अचिन्हित अक्षर data[3];

	data[0] = gain >> 9;
	अगरorce_send_packet(अगरorce, FF_CMD_GAIN, data);
पूर्ण

अटल व्योम अगरorce_set_स्वतःcenter(काष्ठा input_dev *dev, u16 magnitude)
अणु
	काष्ठा अगरorce *अगरorce = input_get_drvdata(dev);
	अचिन्हित अक्षर data[3];

	data[0] = 0x03;
	data[1] = magnitude >> 9;
	अगरorce_send_packet(अगरorce, FF_CMD_AUTOCENTER, data);

	data[0] = 0x04;
	data[1] = 0x01;
	अगरorce_send_packet(अगरorce, FF_CMD_AUTOCENTER, data);
पूर्ण

/*
 * Function called when an ioctl is perक्रमmed on the event dev entry.
 * It uploads an effect to the device
 */
अटल पूर्णांक अगरorce_upload_effect(काष्ठा input_dev *dev, काष्ठा ff_effect *effect, काष्ठा ff_effect *old)
अणु
	काष्ठा अगरorce *अगरorce = input_get_drvdata(dev);
	काष्ठा अगरorce_core_effect *core_effect = &अगरorce->core_effects[effect->id];
	पूर्णांक ret;

	अगर (__test_and_set_bit(FF_CORE_IS_USED, core_effect->flags)) अणु
		/* Check the effect is not alपढ़ोy being updated */
		अगर (test_bit(FF_CORE_UPDATE, core_effect->flags))
			वापस -EAGAIN;
	पूर्ण

/*
 * Upload the effect
 */
	चयन (effect->type) अणु
	हाल FF_PERIODIC:
		ret = अगरorce_upload_periodic(अगरorce, effect, old);
		अवरोध;

	हाल FF_CONSTANT:
		ret = अगरorce_upload_स्थिरant(अगरorce, effect, old);
		अवरोध;

	हाल FF_SPRING:
	हाल FF_DAMPER:
		ret = अगरorce_upload_condition(अगरorce, effect, old);
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (ret == 0) अणु
		/* A packet was sent, क्रमbid new updates until we are notअगरied
		 * that the packet was updated
		 */
		set_bit(FF_CORE_UPDATE, core_effect->flags);
	पूर्ण
	वापस ret;
पूर्ण

/*
 * Erases an effect: it मुक्तs the effect id and mark as unused the memory
 * allocated क्रम the parameters
 */
अटल पूर्णांक अगरorce_erase_effect(काष्ठा input_dev *dev, पूर्णांक effect_id)
अणु
	काष्ठा अगरorce *अगरorce = input_get_drvdata(dev);
	काष्ठा अगरorce_core_effect *core_effect = &अगरorce->core_effects[effect_id];
	पूर्णांक err = 0;

	अगर (test_bit(FF_MOD1_IS_USED, core_effect->flags))
		err = release_resource(&core_effect->mod1_chunk);

	अगर (!err && test_bit(FF_MOD2_IS_USED, core_effect->flags))
		err = release_resource(&core_effect->mod2_chunk);

	/* TODO: remember to change that अगर more FF_MOD* bits are added */
	core_effect->flags[0] = 0;

	वापस err;
पूर्ण

अटल पूर्णांक अगरorce_खोलो(काष्ठा input_dev *dev)
अणु
	काष्ठा अगरorce *अगरorce = input_get_drvdata(dev);

	अगरorce->xport_ops->start_io(अगरorce);

	अगर (test_bit(EV_FF, dev->evbit)) अणु
		/* Enable क्रमce feedback */
		अगरorce_send_packet(अगरorce, FF_CMD_ENABLE, "\004");
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम अगरorce_बंद(काष्ठा input_dev *dev)
अणु
	काष्ठा अगरorce *अगरorce = input_get_drvdata(dev);
	पूर्णांक i;

	अगर (test_bit(EV_FF, dev->evbit)) अणु
		/* Check: no effects should be present in memory */
		क्रम (i = 0; i < dev->ff->max_effects; i++) अणु
			अगर (test_bit(FF_CORE_IS_USED, अगरorce->core_effects[i].flags)) अणु
				dev_warn(&dev->dev,
					"%s: Device still owns effects\n",
					__func__);
				अवरोध;
			पूर्ण
		पूर्ण

		/* Disable क्रमce feedback playback */
		अगरorce_send_packet(अगरorce, FF_CMD_ENABLE, "\001");
		/* Wait क्रम the command to complete */
		रुको_event_पूर्णांकerruptible(अगरorce->रुको,
			!test_bit(IFORCE_XMIT_RUNNING, अगरorce->xmit_flags));
	पूर्ण

	अगरorce->xport_ops->stop_io(अगरorce);
पूर्ण

पूर्णांक अगरorce_init_device(काष्ठा device *parent, u16 bustype,
		       काष्ठा अगरorce *अगरorce)
अणु
	काष्ठा input_dev *input_dev;
	काष्ठा ff_device *ff;
	u8 c[] = "CEOV";
	u8 buf[IFORCE_MAX_LENGTH];
	माप_प्रकार len;
	पूर्णांक i, error;
	पूर्णांक ff_effects = 0;

	input_dev = input_allocate_device();
	अगर (!input_dev)
		वापस -ENOMEM;

	init_रुकोqueue_head(&अगरorce->रुको);
	spin_lock_init(&अगरorce->xmit_lock);
	mutex_init(&अगरorce->mem_mutex);
	अगरorce->xmit.buf = अगरorce->xmit_data;
	अगरorce->dev = input_dev;

/*
 * Input device fields.
 */

	input_dev->id.bustype = bustype;
	input_dev->dev.parent = parent;

	input_set_drvdata(input_dev, अगरorce);

	input_dev->name = "Unknown I-Force device";
	input_dev->खोलो = अगरorce_खोलो;
	input_dev->बंद = अगरorce_बंद;

/*
 * On-device memory allocation.
 */

	अगरorce->device_memory.name = "I-Force device effect memory";
	अगरorce->device_memory.start = 0;
	अगरorce->device_memory.end = 200;
	अगरorce->device_memory.flags = IORESOURCE_MEM;
	अगरorce->device_memory.parent = शून्य;
	अगरorce->device_memory.child = शून्य;
	अगरorce->device_memory.sibling = शून्य;

/*
 * Wait until device पढ़ोy - until it sends its first response.
 */

	क्रम (i = 0; i < 20; i++)
		अगर (!अगरorce_get_id_packet(अगरorce, 'O', buf, &len))
			अवरोध;

	अगर (i == 20) अणु /* 5 seconds */
		dev_err(&input_dev->dev,
			"Timeout waiting for response from device.\n");
		error = -ENODEV;
		जाओ fail;
	पूर्ण

/*
 * Get device info.
 */

	अगर (!अगरorce_get_id_packet(अगरorce, 'M', buf, &len) || len < 3)
		input_dev->id.venकरोr = get_unaligned_le16(buf + 1);
	अन्यथा
		dev_warn(&अगरorce->dev->dev, "Device does not respond to id packet M\n");

	अगर (!अगरorce_get_id_packet(अगरorce, 'P', buf, &len) || len < 3)
		input_dev->id.product = get_unaligned_le16(buf + 1);
	अन्यथा
		dev_warn(&अगरorce->dev->dev, "Device does not respond to id packet P\n");

	अगर (!अगरorce_get_id_packet(अगरorce, 'B', buf, &len) || len < 3)
		अगरorce->device_memory.end = get_unaligned_le16(buf + 1);
	अन्यथा
		dev_warn(&अगरorce->dev->dev, "Device does not respond to id packet B\n");

	अगर (!अगरorce_get_id_packet(अगरorce, 'N', buf, &len) || len < 2)
		ff_effects = buf[1];
	अन्यथा
		dev_warn(&अगरorce->dev->dev, "Device does not respond to id packet N\n");

	/* Check अगर the device can store more effects than the driver can really handle */
	अगर (ff_effects > IFORCE_EFFECTS_MAX) अणु
		dev_warn(&अगरorce->dev->dev, "Limiting number of effects to %d (device reports %d)\n",
		       IFORCE_EFFECTS_MAX, ff_effects);
		ff_effects = IFORCE_EFFECTS_MAX;
	पूर्ण

/*
 * Display additional info.
 */

	क्रम (i = 0; c[i]; i++)
		अगर (!अगरorce_get_id_packet(अगरorce, c[i], buf, &len))
			अगरorce_dump_packet(अगरorce, "info",
					   (FF_CMD_QUERY & 0xff00) | len, buf);

/*
 * Disable spring, enable क्रमce feedback.
 */
	अगरorce_set_स्वतःcenter(input_dev, 0);

/*
 * Find appropriate device entry
 */

	क्रम (i = 0; अगरorce_device[i].idvenकरोr; i++)
		अगर (अगरorce_device[i].idvenकरोr == input_dev->id.venकरोr &&
		    अगरorce_device[i].idproduct == input_dev->id.product)
			अवरोध;

	अगरorce->type = अगरorce_device + i;
	input_dev->name = अगरorce->type->name;

/*
 * Set input device bitfields and ranges.
 */

	input_dev->evbit[0] = BIT_MASK(EV_KEY) | BIT_MASK(EV_ABS) |
		BIT_MASK(EV_FF_STATUS);

	क्रम (i = 0; अगरorce->type->btn[i] >= 0; i++)
		set_bit(अगरorce->type->btn[i], input_dev->keybit);

	क्रम (i = 0; अगरorce->type->असल[i] >= 0; i++) अणु

		चिन्हित लघु t = अगरorce->type->असल[i];

		चयन (t) अणु
		हाल ABS_X:
		हाल ABS_Y:
		हाल ABS_WHEEL:
			input_set_असल_params(input_dev, t, -1920, 1920, 16, 128);
			set_bit(t, input_dev->ffbit);
			अवरोध;

		हाल ABS_THROTTLE:
		हाल ABS_GAS:
		हाल ABS_BRAKE:
			input_set_असल_params(input_dev, t, 0, 255, 0, 0);
			अवरोध;

		हाल ABS_RUDDER:
			input_set_असल_params(input_dev, t, -128, 127, 0, 0);
			अवरोध;

		हाल ABS_HAT0X:
		हाल ABS_HAT0Y:
		हाल ABS_HAT1X:
		हाल ABS_HAT1Y:
			input_set_असल_params(input_dev, t, -1, 1, 0, 0);
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (ff_effects) अणु

		क्रम (i = 0; अगरorce->type->ff[i] >= 0; i++)
			set_bit(अगरorce->type->ff[i], input_dev->ffbit);

		error = input_ff_create(input_dev, ff_effects);
		अगर (error)
			जाओ fail;

		ff = input_dev->ff;
		ff->upload = अगरorce_upload_effect;
		ff->erase = अगरorce_erase_effect;
		ff->set_gain = अगरorce_set_gain;
		ff->set_स्वतःcenter = अगरorce_set_स्वतःcenter;
		ff->playback = अगरorce_playback;
	पूर्ण
/*
 * Register input device.
 */

	error = input_रेजिस्टर_device(अगरorce->dev);
	अगर (error)
		जाओ fail;

	वापस 0;

 fail:	input_मुक्त_device(input_dev);
	वापस error;
पूर्ण
EXPORT_SYMBOL(अगरorce_init_device);
