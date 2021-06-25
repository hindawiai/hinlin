<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Copyright (c) 2001 Vojtech Pavlik
 *
 *  Based on the work of:
 *	Toby Deshane
 */

/*
 * InterAct digital gamepad/joystick driver क्रम Linux
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

#घोषणा DRIVER_DESC	"InterAct digital joystick driver"

MODULE_AUTHOR("Vojtech Pavlik <vojtech@ucw.cz>");
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_LICENSE("GPL");

#घोषणा INTERACT_MAX_START	600	/* 400 us */
#घोषणा INTERACT_MAX_STROBE	60	/* 40 us */
#घोषणा INTERACT_MAX_LENGTH	32	/* 32 bits */

#घोषणा INTERACT_TYPE_HHFX	0	/* HammerHead/FX */
#घोषणा INTERACT_TYPE_PP8D	1	/* ProPad 8 */

काष्ठा पूर्णांकeract अणु
	काष्ठा gameport *gameport;
	काष्ठा input_dev *dev;
	पूर्णांक bads;
	पूर्णांक पढ़ोs;
	अचिन्हित अक्षर type;
	अचिन्हित अक्षर length;
	अक्षर phys[32];
पूर्ण;

अटल लघु पूर्णांकeract_असल_hhfx[] =
	अणु ABS_RX, ABS_RY, ABS_X, ABS_Y, ABS_HAT0X, ABS_HAT0Y, -1 पूर्ण;
अटल लघु पूर्णांकeract_असल_pp8d[] =
	अणु ABS_X, ABS_Y, -1 पूर्ण;

अटल लघु पूर्णांकeract_btn_hhfx[] =
	अणु BTN_TR, BTN_X, BTN_Y, BTN_Z, BTN_A, BTN_B, BTN_C, BTN_TL, BTN_TL2, BTN_TR2, BTN_MODE, BTN_SELECT, -1 पूर्ण;
अटल लघु पूर्णांकeract_btn_pp8d[] =
	अणु BTN_C, BTN_TL, BTN_TR, BTN_A, BTN_B, BTN_Y, BTN_Z, BTN_X, -1 पूर्ण;

काष्ठा पूर्णांकeract_type अणु
	पूर्णांक id;
	लघु *असल;
	लघु *btn;
	अक्षर *name;
	अचिन्हित अक्षर length;
	अचिन्हित अक्षर b8;
पूर्ण;

अटल काष्ठा पूर्णांकeract_type पूर्णांकeract_type[] = अणु
	अणु 0x6202, पूर्णांकeract_असल_hhfx, पूर्णांकeract_btn_hhfx, "InterAct HammerHead/FX",    32, 4 पूर्ण,
	अणु 0x53f8, पूर्णांकeract_असल_pp8d, पूर्णांकeract_btn_pp8d, "InterAct ProPad 8 Digital", 16, 0 पूर्ण,
	अणु 0 पूर्णपूर्ण;

/*
 * पूर्णांकeract_पढ़ो_packet() पढ़ोs and InterAct joystick data.
 */

अटल पूर्णांक पूर्णांकeract_पढ़ो_packet(काष्ठा gameport *gameport, पूर्णांक length, u32 *data)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित अक्षर u, v;
	अचिन्हित पूर्णांक t, s;
	पूर्णांक i;

	i = 0;
	data[0] = data[1] = data[2] = 0;
	t = gameport_समय(gameport, INTERACT_MAX_START);
	s = gameport_समय(gameport, INTERACT_MAX_STROBE);

	local_irq_save(flags);
	gameport_trigger(gameport);
	v = gameport_पढ़ो(gameport);

	जबतक (t > 0 && i < length) अणु
		t--;
		u = v; v = gameport_पढ़ो(gameport);
		अगर (v & ~u & 0x40) अणु
			data[0] = (data[0] << 1) | ((v >> 4) & 1);
			data[1] = (data[1] << 1) | ((v >> 5) & 1);
			data[2] = (data[2] << 1) | ((v >> 7) & 1);
			i++;
			t = s;
		पूर्ण
	पूर्ण

	local_irq_restore(flags);

	वापस i;
पूर्ण

/*
 * पूर्णांकeract_poll() पढ़ोs and analyzes InterAct joystick data.
 */

अटल व्योम पूर्णांकeract_poll(काष्ठा gameport *gameport)
अणु
	काष्ठा पूर्णांकeract *पूर्णांकeract = gameport_get_drvdata(gameport);
	काष्ठा input_dev *dev = पूर्णांकeract->dev;
	u32 data[3];
	पूर्णांक i;

	पूर्णांकeract->पढ़ोs++;

	अगर (पूर्णांकeract_पढ़ो_packet(पूर्णांकeract->gameport, पूर्णांकeract->length, data) < पूर्णांकeract->length) अणु
		पूर्णांकeract->bads++;
	पूर्ण अन्यथा अणु

		क्रम (i = 0; i < 3; i++)
			data[i] <<= INTERACT_MAX_LENGTH - पूर्णांकeract->length;

		चयन (पूर्णांकeract->type) अणु

			हाल INTERACT_TYPE_HHFX:

				क्रम (i = 0; i < 4; i++)
					input_report_असल(dev, पूर्णांकeract_असल_hhfx[i], (data[i & 1] >> ((i >> 1) << 3)) & 0xff);

				क्रम (i = 0; i < 2; i++)
					input_report_असल(dev, ABS_HAT0Y - i,
						((data[1] >> ((i << 1) + 17)) & 1)  - ((data[1] >> ((i << 1) + 16)) & 1));

				क्रम (i = 0; i < 8; i++)
					input_report_key(dev, पूर्णांकeract_btn_hhfx[i], (data[0] >> (i + 16)) & 1);

				क्रम (i = 0; i < 4; i++)
					input_report_key(dev, पूर्णांकeract_btn_hhfx[i + 8], (data[1] >> (i + 20)) & 1);

				अवरोध;

			हाल INTERACT_TYPE_PP8D:

				क्रम (i = 0; i < 2; i++)
					input_report_असल(dev, पूर्णांकeract_असल_pp8d[i],
						((data[0] >> ((i << 1) + 20)) & 1)  - ((data[0] >> ((i << 1) + 21)) & 1));

				क्रम (i = 0; i < 8; i++)
					input_report_key(dev, पूर्णांकeract_btn_pp8d[i], (data[1] >> (i + 16)) & 1);

				अवरोध;
		पूर्ण
	पूर्ण

	input_sync(dev);
पूर्ण

/*
 * पूर्णांकeract_खोलो() is a callback from the input खोलो routine.
 */

अटल पूर्णांक पूर्णांकeract_खोलो(काष्ठा input_dev *dev)
अणु
	काष्ठा पूर्णांकeract *पूर्णांकeract = input_get_drvdata(dev);

	gameport_start_polling(पूर्णांकeract->gameport);
	वापस 0;
पूर्ण

/*
 * पूर्णांकeract_बंद() is a callback from the input बंद routine.
 */

अटल व्योम पूर्णांकeract_बंद(काष्ठा input_dev *dev)
अणु
	काष्ठा पूर्णांकeract *पूर्णांकeract = input_get_drvdata(dev);

	gameport_stop_polling(पूर्णांकeract->gameport);
पूर्ण

/*
 * पूर्णांकeract_connect() probes क्रम InterAct joysticks.
 */

अटल पूर्णांक पूर्णांकeract_connect(काष्ठा gameport *gameport, काष्ठा gameport_driver *drv)
अणु
	काष्ठा पूर्णांकeract *पूर्णांकeract;
	काष्ठा input_dev *input_dev;
	__u32 data[3];
	पूर्णांक i, t;
	पूर्णांक err;

	पूर्णांकeract = kzalloc(माप(काष्ठा पूर्णांकeract), GFP_KERNEL);
	input_dev = input_allocate_device();
	अगर (!पूर्णांकeract || !input_dev) अणु
		err = -ENOMEM;
		जाओ fail1;
	पूर्ण

	पूर्णांकeract->gameport = gameport;
	पूर्णांकeract->dev = input_dev;

	gameport_set_drvdata(gameport, पूर्णांकeract);

	err = gameport_खोलो(gameport, drv, GAMEPORT_MODE_RAW);
	अगर (err)
		जाओ fail1;

	i = पूर्णांकeract_पढ़ो_packet(gameport, INTERACT_MAX_LENGTH * 2, data);

	अगर (i != 32 || (data[0] >> 24) != 0x0c || (data[1] >> 24) != 0x02) अणु
		err = -ENODEV;
		जाओ fail2;
	पूर्ण

	क्रम (i = 0; पूर्णांकeract_type[i].length; i++)
		अगर (पूर्णांकeract_type[i].id == (data[2] >> 16))
			अवरोध;

	अगर (!पूर्णांकeract_type[i].length) अणु
		prपूर्णांकk(KERN_WARNING "interact.c: Unknown joystick on %s. [len %d d0 %08x d1 %08x i2 %08x]\n",
			gameport->phys, i, data[0], data[1], data[2]);
		err = -ENODEV;
		जाओ fail2;
	पूर्ण

	gameport_set_poll_handler(gameport, पूर्णांकeract_poll);
	gameport_set_poll_पूर्णांकerval(gameport, 20);

	snम_लिखो(पूर्णांकeract->phys, माप(पूर्णांकeract->phys), "%s/input0", gameport->phys);

	पूर्णांकeract->type = i;
	पूर्णांकeract->length = पूर्णांकeract_type[i].length;

	input_dev->name = पूर्णांकeract_type[i].name;
	input_dev->phys = पूर्णांकeract->phys;
	input_dev->id.bustype = BUS_GAMEPORT;
	input_dev->id.venकरोr = GAMEPORT_ID_VENDOR_INTERACT;
	input_dev->id.product = पूर्णांकeract_type[i].id;
	input_dev->id.version = 0x0100;
	input_dev->dev.parent = &gameport->dev;

	input_set_drvdata(input_dev, पूर्णांकeract);

	input_dev->खोलो = पूर्णांकeract_खोलो;
	input_dev->बंद = पूर्णांकeract_बंद;

	input_dev->evbit[0] = BIT_MASK(EV_KEY) | BIT_MASK(EV_ABS);

	क्रम (i = 0; (t = पूर्णांकeract_type[पूर्णांकeract->type].असल[i]) >= 0; i++) अणु
		अगर (i < पूर्णांकeract_type[पूर्णांकeract->type].b8)
			input_set_असल_params(input_dev, t, 0, 255, 0, 0);
		अन्यथा
			input_set_असल_params(input_dev, t, -1, 1, 0, 0);
	पूर्ण

	क्रम (i = 0; (t = पूर्णांकeract_type[पूर्णांकeract->type].btn[i]) >= 0; i++)
		__set_bit(t, input_dev->keybit);

	err = input_रेजिस्टर_device(पूर्णांकeract->dev);
	अगर (err)
		जाओ fail2;

	वापस 0;

fail2:	gameport_बंद(gameport);
fail1:  gameport_set_drvdata(gameport, शून्य);
	input_मुक्त_device(input_dev);
	kमुक्त(पूर्णांकeract);
	वापस err;
पूर्ण

अटल व्योम पूर्णांकeract_disconnect(काष्ठा gameport *gameport)
अणु
	काष्ठा पूर्णांकeract *पूर्णांकeract = gameport_get_drvdata(gameport);

	input_unरेजिस्टर_device(पूर्णांकeract->dev);
	gameport_बंद(gameport);
	gameport_set_drvdata(gameport, शून्य);
	kमुक्त(पूर्णांकeract);
पूर्ण

अटल काष्ठा gameport_driver पूर्णांकeract_drv = अणु
	.driver		= अणु
		.name	= "interact",
	पूर्ण,
	.description	= DRIVER_DESC,
	.connect	= पूर्णांकeract_connect,
	.disconnect	= पूर्णांकeract_disconnect,
पूर्ण;

module_gameport_driver(पूर्णांकeract_drv);
