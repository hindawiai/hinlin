<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Copyright (c) 1998-2001 Vojtech Pavlik
 */

/*
 * Gravis/Kensington GrIP protocol joystick and gamepad driver क्रम Linux
 */

/*
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/gameport.h>
#समावेश <linux/input.h>
#समावेश <linux/jअगरfies.h>

#घोषणा DRIVER_DESC	"Gravis GrIP protocol joystick driver"

MODULE_AUTHOR("Vojtech Pavlik <vojtech@ucw.cz>");
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_LICENSE("GPL");

#घोषणा GRIP_MODE_GPP		1
#घोषणा GRIP_MODE_BD		2
#घोषणा GRIP_MODE_XT		3
#घोषणा GRIP_MODE_DC		4

#घोषणा GRIP_LENGTH_GPP		24
#घोषणा GRIP_STROBE_GPP		200	/* 200 us */
#घोषणा GRIP_LENGTH_XT		4
#घोषणा GRIP_STROBE_XT		64	/* 64 us */
#घोषणा GRIP_MAX_CHUNKS_XT	10
#घोषणा GRIP_MAX_BITS_XT	30

काष्ठा grip अणु
	काष्ठा gameport *gameport;
	काष्ठा input_dev *dev[2];
	अचिन्हित अक्षर mode[2];
	पूर्णांक पढ़ोs;
	पूर्णांक bads;
	अक्षर phys[2][32];
पूर्ण;

अटल पूर्णांक grip_btn_gpp[] = अणु BTN_START, BTN_SELECT, BTN_TR2, BTN_Y, 0, BTN_TL2, BTN_A, BTN_B, BTN_X, 0, BTN_TL, BTN_TR, -1 पूर्ण;
अटल पूर्णांक grip_btn_bd[] = अणु BTN_THUMB, BTN_THUMB2, BTN_TRIGGER, BTN_TOP, BTN_BASE, -1 पूर्ण;
अटल पूर्णांक grip_btn_xt[] = अणु BTN_TRIGGER, BTN_THUMB, BTN_A, BTN_B, BTN_C, BTN_X, BTN_Y, BTN_Z, BTN_SELECT, BTN_START, BTN_MODE, -1 पूर्ण;
अटल पूर्णांक grip_btn_dc[] = अणु BTN_TRIGGER, BTN_THUMB, BTN_TOP, BTN_TOP2, BTN_BASE, BTN_BASE2, BTN_BASE3, BTN_BASE4, BTN_BASE5, -1 पूर्ण;

अटल पूर्णांक grip_असल_gpp[] = अणु ABS_X, ABS_Y, -1 पूर्ण;
अटल पूर्णांक grip_असल_bd[] = अणु ABS_X, ABS_Y, ABS_THROTTLE, ABS_HAT0X, ABS_HAT0Y, -1 पूर्ण;
अटल पूर्णांक grip_असल_xt[] = अणु ABS_X, ABS_Y, ABS_BRAKE, ABS_GAS, ABS_THROTTLE, ABS_HAT0X, ABS_HAT0Y, ABS_HAT1X, ABS_HAT1Y, -1 पूर्ण;
अटल पूर्णांक grip_असल_dc[] = अणु ABS_X, ABS_Y, ABS_RX, ABS_RY, ABS_THROTTLE, ABS_HAT0X, ABS_HAT0Y, -1 पूर्ण;

अटल अक्षर *grip_name[] = अणु शून्य, "Gravis GamePad Pro", "Gravis Blackhawk Digital",
				"Gravis Xterminator Digital", "Gravis Xterminator DualControl" पूर्ण;
अटल पूर्णांक *grip_असल[] = अणु शून्य, grip_असल_gpp, grip_असल_bd, grip_असल_xt, grip_असल_dc पूर्ण;
अटल पूर्णांक *grip_btn[] = अणु शून्य, grip_btn_gpp, grip_btn_bd, grip_btn_xt, grip_btn_dc पूर्ण;
अटल अक्षर grip_anx[] = अणु 0, 0, 3, 5, 5 पूर्ण;
अटल अक्षर grip_cen[] = अणु 0, 0, 2, 2, 4 पूर्ण;

/*
 * grip_gpp_पढ़ो_packet() पढ़ोs a Gravis GamePad Pro packet.
 */

अटल पूर्णांक grip_gpp_पढ़ो_packet(काष्ठा gameport *gameport, पूर्णांक shअगरt, अचिन्हित पूर्णांक *data)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित अक्षर u, v;
	अचिन्हित पूर्णांक t;
	पूर्णांक i;

	पूर्णांक strobe = gameport_समय(gameport, GRIP_STROBE_GPP);

	data[0] = 0;
	t = strobe;
	i = 0;

	local_irq_save(flags);

	v = gameport_पढ़ो(gameport) >> shअगरt;

	करो अणु
		t--;
		u = v; v = (gameport_पढ़ो(gameport) >> shअगरt) & 3;
		अगर (~v & u & 1) अणु
			data[0] |= (v >> 1) << i++;
			t = strobe;
		पूर्ण
	पूर्ण जबतक (i < GRIP_LENGTH_GPP && t > 0);

	local_irq_restore(flags);

	अगर (i < GRIP_LENGTH_GPP) वापस -1;

	क्रम (i = 0; i < GRIP_LENGTH_GPP && (data[0] & 0xfe4210) ^ 0x7c0000; i++)
		data[0] = data[0] >> 1 | (data[0] & 1) << (GRIP_LENGTH_GPP - 1);

	वापस -(i == GRIP_LENGTH_GPP);
पूर्ण

/*
 * grip_xt_पढ़ो_packet() पढ़ोs a Gravis Xterminator packet.
 */

अटल पूर्णांक grip_xt_पढ़ो_packet(काष्ठा gameport *gameport, पूर्णांक shअगरt, अचिन्हित पूर्णांक *data)
अणु
	अचिन्हित पूर्णांक i, j, buf, crc;
	अचिन्हित अक्षर u, v, w;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक t;
	अक्षर status;

	पूर्णांक strobe = gameport_समय(gameport, GRIP_STROBE_XT);

	data[0] = data[1] = data[2] = data[3] = 0;
	status = buf = i = j = 0;
	t = strobe;

	local_irq_save(flags);

	v = w = (gameport_पढ़ो(gameport) >> shअगरt) & 3;

	करो अणु
		t--;
		u = (gameport_पढ़ो(gameport) >> shअगरt) & 3;

		अगर (u ^ v) अणु

			अगर ((u ^ v) & 1) अणु
				buf = (buf << 1) | (u >> 1);
				t = strobe;
				i++;
			पूर्ण अन्यथा

			अगर ((((u ^ v) & (v ^ w)) >> 1) & ~(u | v | w) & 1) अणु
				अगर (i == 20) अणु
					crc = buf ^ (buf >> 7) ^ (buf >> 14);
					अगर (!((crc ^ (0x25cb9e70 >> ((crc >> 2) & 0x1c))) & 0xf)) अणु
						data[buf >> 18] = buf >> 4;
						status |= 1 << (buf >> 18);
					पूर्ण
					j++;
				पूर्ण
				t = strobe;
				buf = 0;
				i = 0;
			पूर्ण
			w = v;
			v = u;
		पूर्ण

	पूर्ण जबतक (status != 0xf && i < GRIP_MAX_BITS_XT && j < GRIP_MAX_CHUNKS_XT && t > 0);

	local_irq_restore(flags);

	वापस -(status != 0xf);
पूर्ण

/*
 * grip_समयr() repeatedly polls the joysticks and generates events.
 */

अटल व्योम grip_poll(काष्ठा gameport *gameport)
अणु
	काष्ठा grip *grip = gameport_get_drvdata(gameport);
	अचिन्हित पूर्णांक data[GRIP_LENGTH_XT];
	काष्ठा input_dev *dev;
	पूर्णांक i, j;

	क्रम (i = 0; i < 2; i++) अणु

		dev = grip->dev[i];
		अगर (!dev)
			जारी;

		grip->पढ़ोs++;

		चयन (grip->mode[i]) अणु

			हाल GRIP_MODE_GPP:

				अगर (grip_gpp_पढ़ो_packet(grip->gameport, (i << 1) + 4, data)) अणु
					grip->bads++;
					अवरोध;
				पूर्ण

				input_report_असल(dev, ABS_X, ((*data >> 15) & 1) - ((*data >> 16) & 1));
				input_report_असल(dev, ABS_Y, ((*data >> 13) & 1) - ((*data >> 12) & 1));

				क्रम (j = 0; j < 12; j++)
					अगर (grip_btn_gpp[j])
						input_report_key(dev, grip_btn_gpp[j], (*data >> j) & 1);

				अवरोध;

			हाल GRIP_MODE_BD:

				अगर (grip_xt_पढ़ो_packet(grip->gameport, (i << 1) + 4, data)) अणु
					grip->bads++;
					अवरोध;
				पूर्ण

				input_report_असल(dev, ABS_X,        (data[0] >> 2) & 0x3f);
				input_report_असल(dev, ABS_Y,  63 - ((data[0] >> 8) & 0x3f));
				input_report_असल(dev, ABS_THROTTLE, (data[2] >> 8) & 0x3f);

				input_report_असल(dev, ABS_HAT0X, ((data[2] >> 1) & 1) - ( data[2]       & 1));
				input_report_असल(dev, ABS_HAT0Y, ((data[2] >> 2) & 1) - ((data[2] >> 3) & 1));

				क्रम (j = 0; j < 5; j++)
					input_report_key(dev, grip_btn_bd[j], (data[3] >> (j + 4)) & 1);

				अवरोध;

			हाल GRIP_MODE_XT:

				अगर (grip_xt_पढ़ो_packet(grip->gameport, (i << 1) + 4, data)) अणु
					grip->bads++;
					अवरोध;
				पूर्ण

				input_report_असल(dev, ABS_X,        (data[0] >> 2) & 0x3f);
				input_report_असल(dev, ABS_Y,  63 - ((data[0] >> 8) & 0x3f));
				input_report_असल(dev, ABS_BRAKE,    (data[1] >> 2) & 0x3f);
				input_report_असल(dev, ABS_GAS,	    (data[1] >> 8) & 0x3f);
				input_report_असल(dev, ABS_THROTTLE, (data[2] >> 8) & 0x3f);

				input_report_असल(dev, ABS_HAT0X, ((data[2] >> 1) & 1) - ( data[2]       & 1));
				input_report_असल(dev, ABS_HAT0Y, ((data[2] >> 2) & 1) - ((data[2] >> 3) & 1));
				input_report_असल(dev, ABS_HAT1X, ((data[2] >> 5) & 1) - ((data[2] >> 4) & 1));
				input_report_असल(dev, ABS_HAT1Y, ((data[2] >> 6) & 1) - ((data[2] >> 7) & 1));

				क्रम (j = 0; j < 11; j++)
					input_report_key(dev, grip_btn_xt[j], (data[3] >> (j + 3)) & 1);
				अवरोध;

			हाल GRIP_MODE_DC:

				अगर (grip_xt_पढ़ो_packet(grip->gameport, (i << 1) + 4, data)) अणु
					grip->bads++;
					अवरोध;
				पूर्ण

				input_report_असल(dev, ABS_X,        (data[0] >> 2) & 0x3f);
				input_report_असल(dev, ABS_Y,        (data[0] >> 8) & 0x3f);
				input_report_असल(dev, ABS_RX,       (data[1] >> 2) & 0x3f);
				input_report_असल(dev, ABS_RY,	    (data[1] >> 8) & 0x3f);
				input_report_असल(dev, ABS_THROTTLE, (data[2] >> 8) & 0x3f);

				input_report_असल(dev, ABS_HAT0X, ((data[2] >> 1) & 1) - ( data[2]       & 1));
				input_report_असल(dev, ABS_HAT0Y, ((data[2] >> 2) & 1) - ((data[2] >> 3) & 1));

				क्रम (j = 0; j < 9; j++)
					input_report_key(dev, grip_btn_dc[j], (data[3] >> (j + 3)) & 1);
				अवरोध;


		पूर्ण

		input_sync(dev);
	पूर्ण
पूर्ण

अटल पूर्णांक grip_खोलो(काष्ठा input_dev *dev)
अणु
	काष्ठा grip *grip = input_get_drvdata(dev);

	gameport_start_polling(grip->gameport);
	वापस 0;
पूर्ण

अटल व्योम grip_बंद(काष्ठा input_dev *dev)
अणु
	काष्ठा grip *grip = input_get_drvdata(dev);

	gameport_stop_polling(grip->gameport);
पूर्ण

अटल पूर्णांक grip_connect(काष्ठा gameport *gameport, काष्ठा gameport_driver *drv)
अणु
	काष्ठा grip *grip;
	काष्ठा input_dev *input_dev;
	अचिन्हित पूर्णांक data[GRIP_LENGTH_XT];
	पूर्णांक i, j, t;
	पूर्णांक err;

	अगर (!(grip = kzalloc(माप(काष्ठा grip), GFP_KERNEL)))
		वापस -ENOMEM;

	grip->gameport = gameport;

	gameport_set_drvdata(gameport, grip);

	err = gameport_खोलो(gameport, drv, GAMEPORT_MODE_RAW);
	अगर (err)
		जाओ fail1;

	क्रम (i = 0; i < 2; i++) अणु
		अगर (!grip_gpp_पढ़ो_packet(gameport, (i << 1) + 4, data)) अणु
			grip->mode[i] = GRIP_MODE_GPP;
			जारी;
		पूर्ण
		अगर (!grip_xt_पढ़ो_packet(gameport, (i << 1) + 4, data)) अणु
			अगर (!(data[3] & 7)) अणु
				grip->mode[i] = GRIP_MODE_BD;
				जारी;
			पूर्ण
			अगर (!(data[2] & 0xf0)) अणु
				grip->mode[i] = GRIP_MODE_XT;
				जारी;
			पूर्ण
			grip->mode[i] = GRIP_MODE_DC;
			जारी;
		पूर्ण
	पूर्ण

	अगर (!grip->mode[0] && !grip->mode[1]) अणु
		err = -ENODEV;
		जाओ fail2;
	पूर्ण

	gameport_set_poll_handler(gameport, grip_poll);
	gameport_set_poll_पूर्णांकerval(gameport, 20);

	क्रम (i = 0; i < 2; i++) अणु
		अगर (!grip->mode[i])
			जारी;

		grip->dev[i] = input_dev = input_allocate_device();
		अगर (!input_dev) अणु
			err = -ENOMEM;
			जाओ fail3;
		पूर्ण

		snम_लिखो(grip->phys[i], माप(grip->phys[i]),
			 "%s/input%d", gameport->phys, i);

		input_dev->name = grip_name[grip->mode[i]];
		input_dev->phys = grip->phys[i];
		input_dev->id.bustype = BUS_GAMEPORT;
		input_dev->id.venकरोr = GAMEPORT_ID_VENDOR_GRAVIS;
		input_dev->id.product = grip->mode[i];
		input_dev->id.version = 0x0100;
		input_dev->dev.parent = &gameport->dev;

		input_set_drvdata(input_dev, grip);

		input_dev->खोलो = grip_खोलो;
		input_dev->बंद = grip_बंद;

		input_dev->evbit[0] = BIT_MASK(EV_KEY) | BIT_MASK(EV_ABS);

		क्रम (j = 0; (t = grip_असल[grip->mode[i]][j]) >= 0; j++) अणु

			अगर (j < grip_cen[grip->mode[i]])
				input_set_असल_params(input_dev, t, 14, 52, 1, 2);
			अन्यथा अगर (j < grip_anx[grip->mode[i]])
				input_set_असल_params(input_dev, t, 3, 57, 1, 0);
			अन्यथा
				input_set_असल_params(input_dev, t, -1, 1, 0, 0);
		पूर्ण

		क्रम (j = 0; (t = grip_btn[grip->mode[i]][j]) >= 0; j++)
			अगर (t > 0)
				set_bit(t, input_dev->keybit);

		err = input_रेजिस्टर_device(grip->dev[i]);
		अगर (err)
			जाओ fail4;
	पूर्ण

	वापस 0;

 fail4:	input_मुक्त_device(grip->dev[i]);
 fail3:	जबतक (--i >= 0)
		अगर (grip->dev[i])
			input_unरेजिस्टर_device(grip->dev[i]);
 fail2:	gameport_बंद(gameport);
 fail1:	gameport_set_drvdata(gameport, शून्य);
	kमुक्त(grip);
	वापस err;
पूर्ण

अटल व्योम grip_disconnect(काष्ठा gameport *gameport)
अणु
	काष्ठा grip *grip = gameport_get_drvdata(gameport);
	पूर्णांक i;

	क्रम (i = 0; i < 2; i++)
		अगर (grip->dev[i])
			input_unरेजिस्टर_device(grip->dev[i]);
	gameport_बंद(gameport);
	gameport_set_drvdata(gameport, शून्य);
	kमुक्त(grip);
पूर्ण

अटल काष्ठा gameport_driver grip_drv = अणु
	.driver		= अणु
		.name	= "grip",
		.owner	= THIS_MODULE,
	पूर्ण,
	.description	= DRIVER_DESC,
	.connect	= grip_connect,
	.disconnect	= grip_disconnect,
पूर्ण;

module_gameport_driver(grip_drv);
