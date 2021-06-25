<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Copyright (c) 1998-2001 Vojtech Pavlik
 *
 *   Based on the work of:
 *	Trystan Larey-Williams
 */

/*
 * ThrustMaster DirectConnect (BSP) joystick family driver क्रम Linux
 */

/*
 */

#समावेश <linux/delay.h>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/gameport.h>
#समावेश <linux/input.h>
#समावेश <linux/jअगरfies.h>

#घोषणा DRIVER_DESC	"ThrustMaster DirectConnect joystick driver"

MODULE_AUTHOR("Vojtech Pavlik <vojtech@ucw.cz>");
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_LICENSE("GPL");

#घोषणा TMDC_MAX_START		600	/* 600 us */
#घोषणा TMDC_MAX_STROBE		60	/* 60 us */
#घोषणा TMDC_MAX_LENGTH		13

#घोषणा TMDC_MODE_M3DI		1
#घोषणा TMDC_MODE_3DRP		3
#घोषणा TMDC_MODE_AT		4
#घोषणा TMDC_MODE_FM		8
#घोषणा TMDC_MODE_FGP		163

#घोषणा TMDC_BYTE_ID		10
#घोषणा TMDC_BYTE_REV		11
#घोषणा TMDC_BYTE_DEF		12

#घोषणा TMDC_ABS		7
#घोषणा TMDC_ABS_HAT		4
#घोषणा TMDC_BTN		16

अटल स्थिर अचिन्हित अक्षर पंचांगdc_byte_a[16] = अणु 0, 1, 3, 4, 6, 7 पूर्ण;
अटल स्थिर अचिन्हित अक्षर पंचांगdc_byte_d[16] = अणु 2, 5, 8, 9 पूर्ण;

अटल स्थिर चिन्हित अक्षर पंचांगdc_असल[TMDC_ABS] =
	अणु ABS_X, ABS_Y, ABS_RUDDER, ABS_THROTTLE, ABS_RX, ABS_RY, ABS_RZ पूर्ण;
अटल स्थिर चिन्हित अक्षर पंचांगdc_असल_hat[TMDC_ABS_HAT] =
	अणु ABS_HAT0X, ABS_HAT0Y, ABS_HAT1X, ABS_HAT1Y पूर्ण;
अटल स्थिर चिन्हित अक्षर पंचांगdc_असल_at[TMDC_ABS] =
	अणु ABS_X, ABS_Y, ABS_RUDDER, -1, ABS_THROTTLE पूर्ण;
अटल स्थिर चिन्हित अक्षर पंचांगdc_असल_fm[TMDC_ABS] =
	अणु ABS_RX, ABS_RY, ABS_X, ABS_Y पूर्ण;

अटल स्थिर लघु पंचांगdc_btn_pad[TMDC_BTN] =
	अणु BTN_A, BTN_B, BTN_C, BTN_X, BTN_Y, BTN_Z, BTN_START, BTN_SELECT, BTN_TL, BTN_TR पूर्ण;
अटल स्थिर लघु पंचांगdc_btn_joy[TMDC_BTN] =
	अणु BTN_TRIGGER, BTN_THUMB, BTN_TOP, BTN_TOP2, BTN_BASE, BTN_BASE2, BTN_THUMB2, BTN_PINKIE,
	  BTN_BASE3, BTN_BASE4, BTN_A, BTN_B, BTN_C, BTN_X, BTN_Y, BTN_Z पूर्ण;
अटल स्थिर लघु पंचांगdc_btn_fm[TMDC_BTN] =
        अणु BTN_TRIGGER, BTN_C, BTN_B, BTN_A, BTN_THUMB, BTN_X, BTN_Y, BTN_Z, BTN_TOP, BTN_TOP2 पूर्ण;
अटल स्थिर लघु पंचांगdc_btn_at[TMDC_BTN] =
        अणु BTN_TRIGGER, BTN_THUMB2, BTN_PINKIE, BTN_THUMB, BTN_BASE6, BTN_BASE5, BTN_BASE4,
          BTN_BASE3, BTN_BASE2, BTN_BASE पूर्ण;

अटल स्थिर काष्ठा अणु
        पूर्णांक x;
        पूर्णांक y;
पूर्ण पंचांगdc_hat_to_axis[] = अणुअणु 0, 0पूर्ण, अणु 1, 0पूर्ण, अणु 0,-1पूर्ण, अणु-1, 0पूर्ण, अणु 0, 1पूर्णपूर्ण;

अटल स्थिर काष्ठा पंचांगdc_model अणु
	अचिन्हित अक्षर id;
	स्थिर अक्षर *name;
	अक्षर असल;
	अक्षर hats;
	अक्षर btnc[4];
	अक्षर btno[4];
	स्थिर चिन्हित अक्षर *axes;
	स्थिर लघु *buttons;
पूर्ण पंचांगdc_models[] = अणु
	अणु   1, "ThrustMaster Millenium 3D Inceptor",	  6, 2, अणु 4, 2 पूर्ण, अणु 4, 6 पूर्ण, पंचांगdc_असल, पंचांगdc_btn_joy पूर्ण,
	अणु   3, "ThrustMaster Rage 3D Gamepad",		  2, 0, अणु 8, 2 पूर्ण, अणु 0, 0 पूर्ण, पंचांगdc_असल, पंचांगdc_btn_pad पूर्ण,
	अणु   4, "ThrustMaster Attack Throttle",		  5, 2, अणु 4, 6 पूर्ण, अणु 4, 2 पूर्ण, पंचांगdc_असल_at, पंचांगdc_btn_at पूर्ण,
	अणु   8, "ThrustMaster FragMaster",		  4, 0, अणु 8, 2 पूर्ण, अणु 0, 0 पूर्ण, पंचांगdc_असल_fm, पंचांगdc_btn_fm पूर्ण,
	अणु 163, "Thrustmaster Fusion GamePad",		  2, 0, अणु 8, 2 पूर्ण, अणु 0, 0 पूर्ण, पंचांगdc_असल, पंचांगdc_btn_pad पूर्ण,
	अणु   0, "Unknown %d-axis, %d-button TM device %d", 0, 0, अणु 0, 0 पूर्ण, अणु 0, 0 पूर्ण, पंचांगdc_असल, पंचांगdc_btn_joy पूर्ण
पूर्ण;


काष्ठा पंचांगdc_port अणु
	काष्ठा input_dev *dev;
	अक्षर name[64];
	अक्षर phys[32];
	पूर्णांक mode;
	स्थिर चिन्हित अक्षर *असल;
	स्थिर लघु *btn;
	अचिन्हित अक्षर असलc;
	अचिन्हित अक्षर btnc[4];
	अचिन्हित अक्षर btno[4];
पूर्ण;

काष्ठा पंचांगdc अणु
	काष्ठा gameport *gameport;
	काष्ठा पंचांगdc_port *port[2];
#अगर 0
	काष्ठा input_dev *dev[2];
	अक्षर name[2][64];
	अक्षर phys[2][32];
	पूर्णांक mode[2];
	चिन्हित अक्षर *असल[2];
	लघु *btn[2];
	अचिन्हित अक्षर असलc[2];
	अचिन्हित अक्षर btnc[2][4];
	अचिन्हित अक्षर btno[2][4];
#पूर्ण_अगर
	पूर्णांक पढ़ोs;
	पूर्णांक bads;
	अचिन्हित अक्षर exists;
पूर्ण;

/*
 * पंचांगdc_पढ़ो_packet() पढ़ोs a ThrustMaster packet.
 */

अटल पूर्णांक पंचांगdc_पढ़ो_packet(काष्ठा gameport *gameport, अचिन्हित अक्षर data[2][TMDC_MAX_LENGTH])
अणु
	अचिन्हित अक्षर u, v, w, x;
	अचिन्हित दीर्घ flags;
	पूर्णांक i[2], j[2], t[2], p, k;

	p = gameport_समय(gameport, TMDC_MAX_STROBE);

	क्रम (k = 0; k < 2; k++) अणु
		t[k] = gameport_समय(gameport, TMDC_MAX_START);
		i[k] = j[k] = 0;
	पूर्ण

	local_irq_save(flags);
	gameport_trigger(gameport);

	w = gameport_पढ़ो(gameport) >> 4;

	करो अणु
		x = w;
		w = gameport_पढ़ो(gameport) >> 4;

		क्रम (k = 0, v = w, u = x; k < 2; k++, v >>= 2, u >>= 2) अणु
			अगर (~v & u & 2) अणु
				अगर (t[k] <= 0 || i[k] >= TMDC_MAX_LENGTH) जारी;
				t[k] = p;
				अगर (j[k] == 0) अणु				 /* Start bit */
					अगर (~v & 1) t[k] = 0;
					data[k][i[k]] = 0; j[k]++; जारी;
				पूर्ण
				अगर (j[k] == 9) अणु				/* Stop bit */
					अगर (v & 1) t[k] = 0;
					j[k] = 0; i[k]++; जारी;
				पूर्ण
				data[k][i[k]] |= (~v & 1) << (j[k]++ - 1);	/* Data bit */
			पूर्ण
			t[k]--;
		पूर्ण
	पूर्ण जबतक (t[0] > 0 || t[1] > 0);

	local_irq_restore(flags);

	वापस (i[0] == TMDC_MAX_LENGTH) | ((i[1] == TMDC_MAX_LENGTH) << 1);
पूर्ण

अटल पूर्णांक पंचांगdc_parse_packet(काष्ठा पंचांगdc_port *port, अचिन्हित अक्षर *data)
अणु
	पूर्णांक i, k, l;

	अगर (data[TMDC_BYTE_ID] != port->mode)
		वापस -1;

	क्रम (i = 0; i < port->असलc; i++) अणु
		अगर (port->असल[i] < 0)
			वापस 0;

		input_report_असल(port->dev, port->असल[i], data[पंचांगdc_byte_a[i]]);
	पूर्ण

	चयन (port->mode) अणु

		हाल TMDC_MODE_M3DI:

			i = पंचांगdc_byte_d[0];
			input_report_असल(port->dev, ABS_HAT0X, ((data[i] >> 3) & 1) - ((data[i] >> 1) & 1));
			input_report_असल(port->dev, ABS_HAT0Y, ((data[i] >> 2) & 1) - ( data[i]       & 1));
			अवरोध;

		हाल TMDC_MODE_AT:

			i = पंचांगdc_byte_a[3];
			input_report_असल(port->dev, ABS_HAT0X, पंचांगdc_hat_to_axis[(data[i] - 141) / 25].x);
			input_report_असल(port->dev, ABS_HAT0Y, पंचांगdc_hat_to_axis[(data[i] - 141) / 25].y);
			अवरोध;

	पूर्ण

	क्रम (k = l = 0; k < 4; k++) अणु
		क्रम (i = 0; i < port->btnc[k]; i++)
			input_report_key(port->dev, port->btn[i + l],
				((data[पंचांगdc_byte_d[k]] >> (i + port->btno[k])) & 1));
		l += port->btnc[k];
	पूर्ण

	input_sync(port->dev);

	वापस 0;
पूर्ण

/*
 * पंचांगdc_poll() पढ़ोs and analyzes ThrustMaster joystick data.
 */

अटल व्योम पंचांगdc_poll(काष्ठा gameport *gameport)
अणु
	अचिन्हित अक्षर data[2][TMDC_MAX_LENGTH];
	काष्ठा पंचांगdc *पंचांगdc = gameport_get_drvdata(gameport);
	अचिन्हित अक्षर r, bad = 0;
	पूर्णांक i;

	पंचांगdc->पढ़ोs++;

	अगर ((r = पंचांगdc_पढ़ो_packet(पंचांगdc->gameport, data)) != पंचांगdc->exists)
		bad = 1;
	अन्यथा अणु
		क्रम (i = 0; i < 2; i++) अणु
			अगर (r & (1 << i) & पंचांगdc->exists) अणु

				अगर (पंचांगdc_parse_packet(पंचांगdc->port[i], data[i]))
					bad = 1;
			पूर्ण
		पूर्ण
	पूर्ण

	पंचांगdc->bads += bad;
पूर्ण

अटल पूर्णांक पंचांगdc_खोलो(काष्ठा input_dev *dev)
अणु
	काष्ठा पंचांगdc *पंचांगdc = input_get_drvdata(dev);

	gameport_start_polling(पंचांगdc->gameport);
	वापस 0;
पूर्ण

अटल व्योम पंचांगdc_बंद(काष्ठा input_dev *dev)
अणु
	काष्ठा पंचांगdc *पंचांगdc = input_get_drvdata(dev);

	gameport_stop_polling(पंचांगdc->gameport);
पूर्ण

अटल पूर्णांक पंचांगdc_setup_port(काष्ठा पंचांगdc *पंचांगdc, पूर्णांक idx, अचिन्हित अक्षर *data)
अणु
	स्थिर काष्ठा पंचांगdc_model *model;
	काष्ठा पंचांगdc_port *port;
	काष्ठा input_dev *input_dev;
	पूर्णांक i, j, b = 0;
	पूर्णांक err;

	पंचांगdc->port[idx] = port = kzalloc(माप (काष्ठा पंचांगdc_port), GFP_KERNEL);
	input_dev = input_allocate_device();
	अगर (!port || !input_dev) अणु
		err = -ENOMEM;
		जाओ fail;
	पूर्ण

	port->mode = data[TMDC_BYTE_ID];

	क्रम (model = पंचांगdc_models; model->id && model->id != port->mode; model++)
		/* empty */;

	port->असल = model->axes;
	port->btn = model->buttons;

	अगर (!model->id) अणु
		port->असलc = data[TMDC_BYTE_DEF] >> 4;
		क्रम (i = 0; i < 4; i++)
			port->btnc[i] = i < (data[TMDC_BYTE_DEF] & 0xf) ? 8 : 0;
	पूर्ण अन्यथा अणु
		port->असलc = model->असल;
		क्रम (i = 0; i < 4; i++)
			port->btnc[i] = model->btnc[i];
	पूर्ण

	क्रम (i = 0; i < 4; i++)
		port->btno[i] = model->btno[i];

	snम_लिखो(port->name, माप(port->name), model->name,
		 port->असलc, (data[TMDC_BYTE_DEF] & 0xf) << 3, port->mode);
	snम_लिखो(port->phys, माप(port->phys), "%s/input%d", पंचांगdc->gameport->phys, i);

	port->dev = input_dev;

	input_dev->name = port->name;
	input_dev->phys = port->phys;
	input_dev->id.bustype = BUS_GAMEPORT;
	input_dev->id.venकरोr = GAMEPORT_ID_VENDOR_THRUSTMASTER;
	input_dev->id.product = model->id;
	input_dev->id.version = 0x0100;
	input_dev->dev.parent = &पंचांगdc->gameport->dev;

	input_set_drvdata(input_dev, पंचांगdc);

	input_dev->खोलो = पंचांगdc_खोलो;
	input_dev->बंद = पंचांगdc_बंद;

	input_dev->evbit[0] = BIT_MASK(EV_KEY) | BIT_MASK(EV_ABS);

	क्रम (i = 0; i < port->असलc && i < TMDC_ABS; i++)
		अगर (port->असल[i] >= 0)
			input_set_असल_params(input_dev, port->असल[i], 8, 248, 2, 4);

	क्रम (i = 0; i < model->hats && i < TMDC_ABS_HAT; i++)
		input_set_असल_params(input_dev, पंचांगdc_असल_hat[i], -1, 1, 0, 0);

	क्रम (i = 0; i < 4; i++) अणु
		क्रम (j = 0; j < port->btnc[i] && j < TMDC_BTN; j++)
			set_bit(port->btn[j + b], input_dev->keybit);
		b += port->btnc[i];
	पूर्ण

	err = input_रेजिस्टर_device(port->dev);
	अगर (err)
		जाओ fail;

	वापस 0;

 fail:	input_मुक्त_device(input_dev);
	kमुक्त(port);
	वापस err;
पूर्ण

/*
 * पंचांगdc_probe() probes क्रम ThrustMaster type joysticks.
 */

अटल पूर्णांक पंचांगdc_connect(काष्ठा gameport *gameport, काष्ठा gameport_driver *drv)
अणु
	अचिन्हित अक्षर data[2][TMDC_MAX_LENGTH];
	काष्ठा पंचांगdc *पंचांगdc;
	पूर्णांक i;
	पूर्णांक err;

	अगर (!(पंचांगdc = kzalloc(माप(काष्ठा पंचांगdc), GFP_KERNEL)))
		वापस -ENOMEM;

	पंचांगdc->gameport = gameport;

	gameport_set_drvdata(gameport, पंचांगdc);

	err = gameport_खोलो(gameport, drv, GAMEPORT_MODE_RAW);
	अगर (err)
		जाओ fail1;

	अगर (!(पंचांगdc->exists = पंचांगdc_पढ़ो_packet(gameport, data))) अणु
		err = -ENODEV;
		जाओ fail2;
	पूर्ण

	gameport_set_poll_handler(gameport, पंचांगdc_poll);
	gameport_set_poll_पूर्णांकerval(gameport, 20);

	क्रम (i = 0; i < 2; i++) अणु
		अगर (पंचांगdc->exists & (1 << i)) अणु

			err = पंचांगdc_setup_port(पंचांगdc, i, data[i]);
			अगर (err)
				जाओ fail3;
		पूर्ण
	पूर्ण

	वापस 0;

 fail3: जबतक (--i >= 0) अणु
		अगर (पंचांगdc->port[i]) अणु
			input_unरेजिस्टर_device(पंचांगdc->port[i]->dev);
			kमुक्त(पंचांगdc->port[i]);
		पूर्ण
	पूर्ण
 fail2:	gameport_बंद(gameport);
 fail1:	gameport_set_drvdata(gameport, शून्य);
	kमुक्त(पंचांगdc);
	वापस err;
पूर्ण

अटल व्योम पंचांगdc_disconnect(काष्ठा gameport *gameport)
अणु
	काष्ठा पंचांगdc *पंचांगdc = gameport_get_drvdata(gameport);
	पूर्णांक i;

	क्रम (i = 0; i < 2; i++) अणु
		अगर (पंचांगdc->port[i]) अणु
			input_unरेजिस्टर_device(पंचांगdc->port[i]->dev);
			kमुक्त(पंचांगdc->port[i]);
		पूर्ण
	पूर्ण
	gameport_बंद(gameport);
	gameport_set_drvdata(gameport, शून्य);
	kमुक्त(पंचांगdc);
पूर्ण

अटल काष्ठा gameport_driver पंचांगdc_drv = अणु
	.driver		= अणु
		.name	= "tmdc",
		.owner	= THIS_MODULE,
	पूर्ण,
	.description	= DRIVER_DESC,
	.connect	= पंचांगdc_connect,
	.disconnect	= पंचांगdc_disconnect,
पूर्ण;

module_gameport_driver(पंचांगdc_drv);
