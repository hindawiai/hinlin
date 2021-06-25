<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Copyright (c) 1998-2001 Vojtech Pavlik
 */

/*
 * FP-Gaming Assassin 3D joystick driver क्रम Linux
 */

/*
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/gameport.h>
#समावेश <linux/input.h>
#समावेश <linux/jअगरfies.h>

#घोषणा DRIVER_DESC	"FP-Gaming Assassin 3D joystick driver"

MODULE_AUTHOR("Vojtech Pavlik <vojtech@ucw.cz>");
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_LICENSE("GPL");

#घोषणा A3D_MAX_START		600	/* 600 us */
#घोषणा A3D_MAX_STROBE		80	/* 80 us */
#घोषणा A3D_MAX_LENGTH		40	/* 40*3 bits */

#घोषणा A3D_MODE_A3D		1	/* Assassin 3D */
#घोषणा A3D_MODE_PAN		2	/* Panther */
#घोषणा A3D_MODE_OEM		3	/* Panther OEM version */
#घोषणा A3D_MODE_PXL		4	/* Panther XL */

अटल अक्षर *a3d_names[] = अणु शून्य, "FP-Gaming Assassin 3D", "MadCatz Panther", "OEM Panther",
			"MadCatz Panther XL", "MadCatz Panther XL w/ rudder" पूर्ण;

काष्ठा a3d अणु
	काष्ठा gameport *gameport;
	काष्ठा gameport *adc;
	काष्ठा input_dev *dev;
	पूर्णांक axes[4];
	पूर्णांक buttons;
	पूर्णांक mode;
	पूर्णांक length;
	पूर्णांक पढ़ोs;
	पूर्णांक bads;
	अक्षर phys[32];
पूर्ण;

/*
 * a3d_पढ़ो_packet() पढ़ोs an Assassin 3D packet.
 */

अटल पूर्णांक a3d_पढ़ो_packet(काष्ठा gameport *gameport, पूर्णांक length, अक्षर *data)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित अक्षर u, v;
	अचिन्हित पूर्णांक t, s;
	पूर्णांक i;

	i = 0;
	t = gameport_समय(gameport, A3D_MAX_START);
	s = gameport_समय(gameport, A3D_MAX_STROBE);

	local_irq_save(flags);
	gameport_trigger(gameport);
	v = gameport_पढ़ो(gameport);

	जबतक (t > 0 && i < length) अणु
		t--;
		u = v; v = gameport_पढ़ो(gameport);
		अगर (~v & u & 0x10) अणु
			data[i++] = v >> 5;
			t = s;
		पूर्ण
	पूर्ण

	local_irq_restore(flags);

	वापस i;
पूर्ण

/*
 * a3d_csum() computes checksum of triplet packet
 */

अटल पूर्णांक a3d_csum(अक्षर *data, पूर्णांक count)
अणु
	पूर्णांक i, csum = 0;

	क्रम (i = 0; i < count - 2; i++)
		csum += data[i];
	वापस (csum & 0x3f) != ((data[count - 2] << 3) | data[count - 1]);
पूर्ण

अटल व्योम a3d_पढ़ो(काष्ठा a3d *a3d, अचिन्हित अक्षर *data)
अणु
	काष्ठा input_dev *dev = a3d->dev;

	चयन (a3d->mode) अणु

		हाल A3D_MODE_A3D:
		हाल A3D_MODE_OEM:
		हाल A3D_MODE_PAN:

			input_report_rel(dev, REL_X, ((data[5] << 6) | (data[6] << 3) | data[ 7]) - ((data[5] & 4) << 7));
			input_report_rel(dev, REL_Y, ((data[8] << 6) | (data[9] << 3) | data[10]) - ((data[8] & 4) << 7));

			input_report_key(dev, BTN_RIGHT,  data[2] & 1);
			input_report_key(dev, BTN_LEFT,   data[3] & 2);
			input_report_key(dev, BTN_MIDDLE, data[3] & 4);

			input_sync(dev);

			a3d->axes[0] = ((चिन्हित अक्षर)((data[11] << 6) | (data[12] << 3) | (data[13]))) + 128;
			a3d->axes[1] = ((चिन्हित अक्षर)((data[14] << 6) | (data[15] << 3) | (data[16]))) + 128;
			a3d->axes[2] = ((चिन्हित अक्षर)((data[17] << 6) | (data[18] << 3) | (data[19]))) + 128;
			a3d->axes[3] = ((चिन्हित अक्षर)((data[20] << 6) | (data[21] << 3) | (data[22]))) + 128;

			a3d->buttons = ((data[3] << 3) | data[4]) & 0xf;

			अवरोध;

		हाल A3D_MODE_PXL:

			input_report_rel(dev, REL_X, ((data[ 9] << 6) | (data[10] << 3) | data[11]) - ((data[ 9] & 4) << 7));
			input_report_rel(dev, REL_Y, ((data[12] << 6) | (data[13] << 3) | data[14]) - ((data[12] & 4) << 7));

			input_report_key(dev, BTN_RIGHT,  data[2] & 1);
			input_report_key(dev, BTN_LEFT,   data[3] & 2);
			input_report_key(dev, BTN_MIDDLE, data[3] & 4);
			input_report_key(dev, BTN_SIDE,   data[7] & 2);
			input_report_key(dev, BTN_EXTRA,  data[7] & 4);

			input_report_असल(dev, ABS_X,        ((चिन्हित अक्षर)((data[15] << 6) | (data[16] << 3) | (data[17]))) + 128);
			input_report_असल(dev, ABS_Y,        ((चिन्हित अक्षर)((data[18] << 6) | (data[19] << 3) | (data[20]))) + 128);
			input_report_असल(dev, ABS_RUDDER,   ((चिन्हित अक्षर)((data[21] << 6) | (data[22] << 3) | (data[23]))) + 128);
			input_report_असल(dev, ABS_THROTTLE, ((चिन्हित अक्षर)((data[24] << 6) | (data[25] << 3) | (data[26]))) + 128);

			input_report_असल(dev, ABS_HAT0X, ( data[5]       & 1) - ((data[5] >> 2) & 1));
			input_report_असल(dev, ABS_HAT0Y, ((data[5] >> 1) & 1) - ((data[6] >> 2) & 1));
			input_report_असल(dev, ABS_HAT1X, ((data[4] >> 1) & 1) - ( data[3]       & 1));
			input_report_असल(dev, ABS_HAT1Y, ((data[4] >> 2) & 1) - ( data[4]       & 1));

			input_report_key(dev, BTN_TRIGGER, data[8] & 1);
			input_report_key(dev, BTN_THUMB,   data[8] & 2);
			input_report_key(dev, BTN_TOP,     data[8] & 4);
			input_report_key(dev, BTN_PINKIE,  data[7] & 1);

			input_sync(dev);

			अवरोध;
	पूर्ण
पूर्ण


/*
 * a3d_poll() पढ़ोs and analyzes A3D joystick data.
 */

अटल व्योम a3d_poll(काष्ठा gameport *gameport)
अणु
	काष्ठा a3d *a3d = gameport_get_drvdata(gameport);
	अचिन्हित अक्षर data[A3D_MAX_LENGTH];

	a3d->पढ़ोs++;
	अगर (a3d_पढ़ो_packet(a3d->gameport, a3d->length, data) != a3d->length ||
	    data[0] != a3d->mode || a3d_csum(data, a3d->length))
		a3d->bads++;
	अन्यथा
		a3d_पढ़ो(a3d, data);
पूर्ण

/*
 * a3d_adc_cooked_पढ़ो() copies the acis and button data to the
 * callers arrays. It could करो the पढ़ो itself, but the caller could
 * call this more than 50 बार a second, which would use too much CPU.
 */

अटल पूर्णांक a3d_adc_cooked_पढ़ो(काष्ठा gameport *gameport, पूर्णांक *axes, पूर्णांक *buttons)
अणु
	काष्ठा a3d *a3d = gameport->port_data;
	पूर्णांक i;

	क्रम (i = 0; i < 4; i++)
		axes[i] = (a3d->axes[i] < 254) ? a3d->axes[i] : -1;
	*buttons = a3d->buttons;
	वापस 0;
पूर्ण

/*
 * a3d_adc_खोलो() is the gameport खोलो routine. It refuses to serve
 * any but cooked data.
 */

अटल पूर्णांक a3d_adc_खोलो(काष्ठा gameport *gameport, पूर्णांक mode)
अणु
	काष्ठा a3d *a3d = gameport->port_data;

	अगर (mode != GAMEPORT_MODE_COOKED)
		वापस -1;

	gameport_start_polling(a3d->gameport);
	वापस 0;
पूर्ण

/*
 * a3d_adc_बंद() is a callback from the input बंद routine.
 */

अटल व्योम a3d_adc_बंद(काष्ठा gameport *gameport)
अणु
	काष्ठा a3d *a3d = gameport->port_data;

	gameport_stop_polling(a3d->gameport);
पूर्ण

/*
 * a3d_खोलो() is a callback from the input खोलो routine.
 */

अटल पूर्णांक a3d_खोलो(काष्ठा input_dev *dev)
अणु
	काष्ठा a3d *a3d = input_get_drvdata(dev);

	gameport_start_polling(a3d->gameport);
	वापस 0;
पूर्ण

/*
 * a3d_बंद() is a callback from the input बंद routine.
 */

अटल व्योम a3d_बंद(काष्ठा input_dev *dev)
अणु
	काष्ठा a3d *a3d = input_get_drvdata(dev);

	gameport_stop_polling(a3d->gameport);
पूर्ण

/*
 * a3d_connect() probes क्रम A3D joysticks.
 */

अटल पूर्णांक a3d_connect(काष्ठा gameport *gameport, काष्ठा gameport_driver *drv)
अणु
	काष्ठा a3d *a3d;
	काष्ठा input_dev *input_dev;
	काष्ठा gameport *adc;
	अचिन्हित अक्षर data[A3D_MAX_LENGTH];
	पूर्णांक i;
	पूर्णांक err;

	a3d = kzalloc(माप(काष्ठा a3d), GFP_KERNEL);
	input_dev = input_allocate_device();
	अगर (!a3d || !input_dev) अणु
		err = -ENOMEM;
		जाओ fail1;
	पूर्ण

	a3d->dev = input_dev;
	a3d->gameport = gameport;

	gameport_set_drvdata(gameport, a3d);

	err = gameport_खोलो(gameport, drv, GAMEPORT_MODE_RAW);
	अगर (err)
		जाओ fail1;

	i = a3d_पढ़ो_packet(gameport, A3D_MAX_LENGTH, data);

	अगर (!i || a3d_csum(data, i)) अणु
		err = -ENODEV;
		जाओ fail2;
	पूर्ण

	a3d->mode = data[0];

	अगर (!a3d->mode || a3d->mode > 5) अणु
		prपूर्णांकk(KERN_WARNING "a3d.c: Unknown A3D device detected "
			"(%s, id=%d), contact <vojtech@ucw.cz>\n", gameport->phys, a3d->mode);
		err = -ENODEV;
		जाओ fail2;
	पूर्ण

	gameport_set_poll_handler(gameport, a3d_poll);
	gameport_set_poll_पूर्णांकerval(gameport, 20);

	snम_लिखो(a3d->phys, माप(a3d->phys), "%s/input0", gameport->phys);

	input_dev->name = a3d_names[a3d->mode];
	input_dev->phys = a3d->phys;
	input_dev->id.bustype = BUS_GAMEPORT;
	input_dev->id.venकरोr = GAMEPORT_ID_VENDOR_MADCATZ;
	input_dev->id.product = a3d->mode;
	input_dev->id.version = 0x0100;
	input_dev->dev.parent = &gameport->dev;
	input_dev->खोलो = a3d_खोलो;
	input_dev->बंद = a3d_बंद;

	input_set_drvdata(input_dev, a3d);

	अगर (a3d->mode == A3D_MODE_PXL) अणु

		पूर्णांक axes[] = अणु ABS_X, ABS_Y, ABS_THROTTLE, ABS_RUDDER पूर्ण;

		a3d->length = 33;

		input_dev->evbit[0] |= BIT_MASK(EV_ABS) | BIT_MASK(EV_KEY) |
			BIT_MASK(EV_REL);
		input_dev->relbit[0] |= BIT_MASK(REL_X) | BIT_MASK(REL_Y);
		input_dev->असलbit[0] |= BIT_MASK(ABS_X) | BIT_MASK(ABS_Y) |
			BIT_MASK(ABS_THROTTLE) | BIT_MASK(ABS_RUDDER) |
			BIT_MASK(ABS_HAT0X) | BIT_MASK(ABS_HAT0Y) |
			BIT_MASK(ABS_HAT1X) | BIT_MASK(ABS_HAT1Y);
		input_dev->keybit[BIT_WORD(BTN_MOUSE)] |= BIT_MASK(BTN_RIGHT) |
			BIT_MASK(BTN_LEFT) | BIT_MASK(BTN_MIDDLE) |
			BIT_MASK(BTN_SIDE) | BIT_MASK(BTN_EXTRA);
		input_dev->keybit[BIT_WORD(BTN_JOYSTICK)] |=
			BIT_MASK(BTN_TRIGGER) | BIT_MASK(BTN_THUMB) |
			BIT_MASK(BTN_TOP) | BIT_MASK(BTN_PINKIE);

		a3d_पढ़ो(a3d, data);

		क्रम (i = 0; i < 4; i++) अणु
			अगर (i < 2)
				input_set_असल_params(input_dev, axes[i],
					48, input_असल_get_val(input_dev, axes[i]) * 2 - 48, 0, 8);
			अन्यथा
				input_set_असल_params(input_dev, axes[i], 2, 253, 0, 0);
			input_set_असल_params(input_dev, ABS_HAT0X + i, -1, 1, 0, 0);
		पूर्ण

	पूर्ण अन्यथा अणु
		a3d->length = 29;

		input_dev->evbit[0] |= BIT_MASK(EV_KEY) | BIT_MASK(EV_REL);
		input_dev->relbit[0] |= BIT_MASK(REL_X) | BIT_MASK(REL_Y);
		input_dev->keybit[BIT_WORD(BTN_MOUSE)] |= BIT_MASK(BTN_RIGHT) |
			BIT_MASK(BTN_LEFT) | BIT_MASK(BTN_MIDDLE);

		a3d_पढ़ो(a3d, data);

		अगर (!(a3d->adc = adc = gameport_allocate_port()))
			prपूर्णांकk(KERN_ERR "a3d: Not enough memory for ADC port\n");
		अन्यथा अणु
			adc->port_data = a3d;
			adc->खोलो = a3d_adc_खोलो;
			adc->बंद = a3d_adc_बंद;
			adc->cooked_पढ़ो = a3d_adc_cooked_पढ़ो;
			adc->fuzz = 1;

			gameport_set_name(adc, a3d_names[a3d->mode]);
			gameport_set_phys(adc, "%s/gameport0", gameport->phys);
			adc->dev.parent = &gameport->dev;

			gameport_रेजिस्टर_port(adc);
		पूर्ण
	पूर्ण

	err = input_रेजिस्टर_device(a3d->dev);
	अगर (err)
		जाओ fail3;

	वापस 0;

 fail3:	अगर (a3d->adc)
		gameport_unरेजिस्टर_port(a3d->adc);
 fail2:	gameport_बंद(gameport);
 fail1:	gameport_set_drvdata(gameport, शून्य);
	input_मुक्त_device(input_dev);
	kमुक्त(a3d);
	वापस err;
पूर्ण

अटल व्योम a3d_disconnect(काष्ठा gameport *gameport)
अणु
	काष्ठा a3d *a3d = gameport_get_drvdata(gameport);

	input_unरेजिस्टर_device(a3d->dev);
	अगर (a3d->adc)
		gameport_unरेजिस्टर_port(a3d->adc);
	gameport_बंद(gameport);
	gameport_set_drvdata(gameport, शून्य);
	kमुक्त(a3d);
पूर्ण

अटल काष्ठा gameport_driver a3d_drv = अणु
	.driver		= अणु
		.name	= "adc",
		.owner	= THIS_MODULE,
	पूर्ण,
	.description	= DRIVER_DESC,
	.connect	= a3d_connect,
	.disconnect	= a3d_disconnect,
पूर्ण;

module_gameport_driver(a3d_drv);
