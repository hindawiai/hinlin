<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Copyright (c) 2001 Vojtech Pavlik
 */

/*
 * Guillemot Digital Interface Protocol driver क्रम Linux
 */

/*
 */

#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/delay.h>
#समावेश <linux/gameport.h>
#समावेश <linux/input.h>
#समावेश <linux/jअगरfies.h>

#घोषणा DRIVER_DESC	"Guillemot Digital joystick driver"

MODULE_AUTHOR("Vojtech Pavlik <vojtech@ucw.cz>");
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_LICENSE("GPL");

#घोषणा GUILLEMOT_MAX_START	600	/* 600 us */
#घोषणा GUILLEMOT_MAX_STROBE	60	/* 60 us */
#घोषणा GUILLEMOT_MAX_LENGTH	17	/* 17 bytes */

अटल लघु guillemot_असल_pad[] =
	अणु ABS_X, ABS_Y, ABS_THROTTLE, ABS_RUDDER, -1 पूर्ण;

अटल लघु guillemot_btn_pad[] =
	अणु BTN_A, BTN_B, BTN_C, BTN_X, BTN_Y, BTN_Z, BTN_TL, BTN_TR, BTN_MODE, BTN_SELECT, -1 पूर्ण;

अटल काष्ठा अणु
        पूर्णांक x;
        पूर्णांक y;
पूर्ण guillemot_hat_to_axis[16] = अणुअणु 0,-1पूर्ण, अणु 1,-1पूर्ण, अणु 1, 0पूर्ण, अणु 1, 1पूर्ण, अणु 0, 1पूर्ण, अणु-1, 1पूर्ण, अणु-1, 0पूर्ण, अणु-1,-1पूर्णपूर्ण;

काष्ठा guillemot_type अणु
	अचिन्हित अक्षर id;
	लघु *असल;
	लघु *btn;
	पूर्णांक hat;
	अक्षर *name;
पूर्ण;

काष्ठा guillemot अणु
	काष्ठा gameport *gameport;
	काष्ठा input_dev *dev;
	पूर्णांक bads;
	पूर्णांक पढ़ोs;
	काष्ठा guillemot_type *type;
	अचिन्हित अक्षर length;
	अक्षर phys[32];
पूर्ण;

अटल काष्ठा guillemot_type guillemot_type[] = अणु
	अणु 0x00, guillemot_असल_pad, guillemot_btn_pad, 1, "Guillemot Pad" पूर्ण,
	अणु 0 पूर्णपूर्ण;

/*
 * guillemot_पढ़ो_packet() पढ़ोs Guillemot joystick data.
 */

अटल पूर्णांक guillemot_पढ़ो_packet(काष्ठा gameport *gameport, u8 *data)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित अक्षर u, v;
	अचिन्हित पूर्णांक t, s;
	पूर्णांक i;

	क्रम (i = 0; i < GUILLEMOT_MAX_LENGTH; i++)
		data[i] = 0;

	i = 0;
	t = gameport_समय(gameport, GUILLEMOT_MAX_START);
	s = gameport_समय(gameport, GUILLEMOT_MAX_STROBE);

	local_irq_save(flags);
	gameport_trigger(gameport);
	v = gameport_पढ़ो(gameport);

	जबतक (t > 0 && i < GUILLEMOT_MAX_LENGTH * 8) अणु
		t--;
		u = v; v = gameport_पढ़ो(gameport);
		अगर (v & ~u & 0x10) अणु
			data[i >> 3] |= ((v >> 5) & 1) << (i & 7);
			i++;
			t = s;
		पूर्ण
	पूर्ण

	local_irq_restore(flags);

	वापस i;
पूर्ण

/*
 * guillemot_poll() पढ़ोs and analyzes Guillemot joystick data.
 */

अटल व्योम guillemot_poll(काष्ठा gameport *gameport)
अणु
	काष्ठा guillemot *guillemot = gameport_get_drvdata(gameport);
	काष्ठा input_dev *dev = guillemot->dev;
	u8 data[GUILLEMOT_MAX_LENGTH];
	पूर्णांक i;

	guillemot->पढ़ोs++;

	अगर (guillemot_पढ़ो_packet(guillemot->gameport, data) != GUILLEMOT_MAX_LENGTH * 8 ||
		data[0] != 0x55 || data[16] != 0xaa) अणु
		guillemot->bads++;
	पूर्ण अन्यथा अणु

		क्रम (i = 0; i < 6 && guillemot->type->असल[i] >= 0; i++)
			input_report_असल(dev, guillemot->type->असल[i], data[i + 5]);

		अगर (guillemot->type->hat) अणु
			input_report_असल(dev, ABS_HAT0X, guillemot_hat_to_axis[data[4] >> 4].x);
			input_report_असल(dev, ABS_HAT0Y, guillemot_hat_to_axis[data[4] >> 4].y);
		पूर्ण

		क्रम (i = 0; i < 16 && guillemot->type->btn[i] >= 0; i++)
			input_report_key(dev, guillemot->type->btn[i], (data[2 + (i >> 3)] >> (i & 7)) & 1);
	पूर्ण

	input_sync(dev);
पूर्ण

/*
 * guillemot_खोलो() is a callback from the input खोलो routine.
 */

अटल पूर्णांक guillemot_खोलो(काष्ठा input_dev *dev)
अणु
	काष्ठा guillemot *guillemot = input_get_drvdata(dev);

	gameport_start_polling(guillemot->gameport);
	वापस 0;
पूर्ण

/*
 * guillemot_बंद() is a callback from the input बंद routine.
 */

अटल व्योम guillemot_बंद(काष्ठा input_dev *dev)
अणु
	काष्ठा guillemot *guillemot = input_get_drvdata(dev);

	gameport_stop_polling(guillemot->gameport);
पूर्ण

/*
 * guillemot_connect() probes क्रम Guillemot joysticks.
 */

अटल पूर्णांक guillemot_connect(काष्ठा gameport *gameport, काष्ठा gameport_driver *drv)
अणु
	काष्ठा guillemot *guillemot;
	काष्ठा input_dev *input_dev;
	u8 data[GUILLEMOT_MAX_LENGTH];
	पूर्णांक i, t;
	पूर्णांक err;

	guillemot = kzalloc(माप(काष्ठा guillemot), GFP_KERNEL);
	input_dev = input_allocate_device();
	अगर (!guillemot || !input_dev) अणु
		err = -ENOMEM;
		जाओ fail1;
	पूर्ण

	guillemot->gameport = gameport;
	guillemot->dev = input_dev;

	gameport_set_drvdata(gameport, guillemot);

	err = gameport_खोलो(gameport, drv, GAMEPORT_MODE_RAW);
	अगर (err)
		जाओ fail1;

	i = guillemot_पढ़ो_packet(gameport, data);

	अगर (i != GUILLEMOT_MAX_LENGTH * 8 || data[0] != 0x55 || data[16] != 0xaa) अणु
		err = -ENODEV;
		जाओ fail2;
	पूर्ण

	क्रम (i = 0; guillemot_type[i].name; i++)
		अगर (guillemot_type[i].id == data[11])
			अवरोध;

	अगर (!guillemot_type[i].name) अणु
		prपूर्णांकk(KERN_WARNING "guillemot.c: Unknown joystick on %s. [ %02x%02x:%04x, ver %d.%02d ]\n",
			gameport->phys, data[12], data[13], data[11], data[14], data[15]);
		err = -ENODEV;
		जाओ fail2;
	पूर्ण

	gameport_set_poll_handler(gameport, guillemot_poll);
	gameport_set_poll_पूर्णांकerval(gameport, 20);

	snम_लिखो(guillemot->phys, माप(guillemot->phys), "%s/input0", gameport->phys);
	guillemot->type = guillemot_type + i;

	input_dev->name = guillemot_type[i].name;
	input_dev->phys = guillemot->phys;
	input_dev->id.bustype = BUS_GAMEPORT;
	input_dev->id.venकरोr = GAMEPORT_ID_VENDOR_GUILLEMOT;
	input_dev->id.product = guillemot_type[i].id;
	input_dev->id.version = (पूर्णांक)data[14] << 8 | data[15];
	input_dev->dev.parent = &gameport->dev;

	input_set_drvdata(input_dev, guillemot);

	input_dev->खोलो = guillemot_खोलो;
	input_dev->बंद = guillemot_बंद;

	input_dev->evbit[0] = BIT_MASK(EV_KEY) | BIT_MASK(EV_ABS);

	क्रम (i = 0; (t = guillemot->type->असल[i]) >= 0; i++)
		input_set_असल_params(input_dev, t, 0, 255, 0, 0);

	अगर (guillemot->type->hat) अणु
		input_set_असल_params(input_dev, ABS_HAT0X, -1, 1, 0, 0);
		input_set_असल_params(input_dev, ABS_HAT0Y, -1, 1, 0, 0);
	पूर्ण

	क्रम (i = 0; (t = guillemot->type->btn[i]) >= 0; i++)
		set_bit(t, input_dev->keybit);

	err = input_रेजिस्टर_device(guillemot->dev);
	अगर (err)
		जाओ fail2;

	वापस 0;

fail2:	gameport_बंद(gameport);
fail1:  gameport_set_drvdata(gameport, शून्य);
	input_मुक्त_device(input_dev);
	kमुक्त(guillemot);
	वापस err;
पूर्ण

अटल व्योम guillemot_disconnect(काष्ठा gameport *gameport)
अणु
	काष्ठा guillemot *guillemot = gameport_get_drvdata(gameport);

	prपूर्णांकk(KERN_INFO "guillemot.c: Failed %d reads out of %d on %s\n", guillemot->पढ़ोs, guillemot->bads, guillemot->phys);
	input_unरेजिस्टर_device(guillemot->dev);
	gameport_बंद(gameport);
	kमुक्त(guillemot);
पूर्ण

अटल काष्ठा gameport_driver guillemot_drv = अणु
	.driver		= अणु
		.name	= "guillemot",
	पूर्ण,
	.description	= DRIVER_DESC,
	.connect	= guillemot_connect,
	.disconnect	= guillemot_disconnect,
पूर्ण;

module_gameport_driver(guillemot_drv);
