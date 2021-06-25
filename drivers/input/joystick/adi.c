<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Copyright (c) 1998-2005 Vojtech Pavlik
 */

/*
 * Logitech ADI joystick family driver क्रम Linux
 */

/*
 */

#समावेश <linux/delay.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/माला.स>
#समावेश <linux/slab.h>
#समावेश <linux/input.h>
#समावेश <linux/gameport.h>
#समावेश <linux/jअगरfies.h>

#घोषणा DRIVER_DESC	"Logitech ADI joystick family driver"

MODULE_AUTHOR("Vojtech Pavlik <vojtech@ucw.cz>");
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_LICENSE("GPL");

/*
 * Times, array sizes, flags, ids.
 */

#घोषणा ADI_MAX_START		200	/* Trigger to packet समयout [200us] */
#घोषणा ADI_MAX_STROBE		40	/* Single bit समयout [40us] */
#घोषणा ADI_INIT_DELAY		10	/* Delay after init packet [10ms] */
#घोषणा ADI_DATA_DELAY		4	/* Delay after data packet [4ms] */

#घोषणा ADI_MAX_LENGTH		256
#घोषणा ADI_MIN_LENGTH		8
#घोषणा ADI_MIN_LEN_LENGTH	10
#घोषणा ADI_MIN_ID_LENGTH	66
#घोषणा ADI_MAX_NAME_LENGTH	64
#घोषणा ADI_MAX_CNAME_LENGTH	16
#घोषणा ADI_MAX_PHYS_LENGTH	64

#घोषणा ADI_FLAG_HAT		0x04
#घोषणा ADI_FLAG_10BIT		0x08

#घोषणा ADI_ID_TPD		0x01
#घोषणा ADI_ID_WGP		0x06
#घोषणा ADI_ID_WGPE		0x08
#घोषणा ADI_ID_MAX		0x0a

/*
 * Names, buttons, axes ...
 */

अटल अक्षर *adi_names[] = अणु	"WingMan Extreme Digital", "ThunderPad Digital", "SideCar", "CyberMan 2",
				"WingMan Interceptor", "WingMan Formula", "WingMan GamePad",
				"WingMan Extreme Digital 3D", "WingMan GamePad Extreme",
				"WingMan GamePad USB", "Unknown Device %#x" पूर्ण;

अटल अक्षर adi_wmgpe_असल[] =	अणु ABS_X, ABS_Y, ABS_HAT0X, ABS_HAT0Y पूर्ण;
अटल अक्षर adi_wmi_असल[] =	अणु ABS_X, ABS_Y, ABS_THROTTLE, ABS_HAT0X, ABS_HAT0Y, ABS_HAT1X, ABS_HAT1Y, ABS_HAT2X, ABS_HAT2Y पूर्ण;
अटल अक्षर adi_wmed3d_असल[] =	अणु ABS_X, ABS_Y, ABS_THROTTLE, ABS_RZ, ABS_HAT0X, ABS_HAT0Y पूर्ण;
अटल अक्षर adi_cm2_असल[] =	अणु ABS_X, ABS_Y, ABS_Z, ABS_RX, ABS_RY, ABS_RZ पूर्ण;
अटल अक्षर adi_wmf_असल[] =	अणु ABS_WHEEL, ABS_GAS, ABS_BRAKE, ABS_HAT0X, ABS_HAT0Y, ABS_HAT1X, ABS_HAT1Y, ABS_HAT2X, ABS_HAT2Y पूर्ण;

अटल लघु adi_wmgpe_key[] =	अणु BTN_A, BTN_B, BTN_C, BTN_X, BTN_Y, BTN_Z,  BTN_TL, BTN_TR, BTN_START, BTN_MODE, BTN_SELECT पूर्ण;
अटल लघु adi_wmi_key[] =	अणु BTN_TRIGGER,  BTN_TOP, BTN_THUMB, BTN_TOP2, BTN_BASE, BTN_BASE2, BTN_BASE3, BTN_BASE4, BTN_EXTRA पूर्ण;
अटल लघु adi_wmed3d_key[] =	अणु BTN_TRIGGER, BTN_THUMB, BTN_THUMB2, BTN_TOP, BTN_TOP2, BTN_BASE, BTN_BASE2 पूर्ण;
अटल लघु adi_cm2_key[] =	अणु BTN_1, BTN_2, BTN_3, BTN_4, BTN_5, BTN_6, BTN_7, BTN_8 पूर्ण;

अटल अक्षर* adi_असल[] = अणु adi_wmi_असल, adi_wmgpe_असल, adi_wmf_असल, adi_cm2_असल, adi_wmi_असल, adi_wmf_असल,
			   adi_wmgpe_असल, adi_wmed3d_असल, adi_wmgpe_असल, adi_wmgpe_असल, adi_wmi_असल पूर्ण;

अटल लघु* adi_key[] = अणु adi_wmi_key, adi_wmgpe_key, adi_cm2_key, adi_cm2_key, adi_wmi_key, adi_cm2_key,
			    adi_wmgpe_key, adi_wmed3d_key, adi_wmgpe_key, adi_wmgpe_key, adi_wmi_key पूर्ण;

/*
 * Hat to axis conversion arrays.
 */

अटल काष्ठा अणु
	पूर्णांक x;
	पूर्णांक y;
पूर्ण adi_hat_to_axis[] = अणुअणु 0, 0पूर्ण, अणु 0,-1पूर्ण, अणु 1,-1पूर्ण, अणु 1, 0पूर्ण, अणु 1, 1पूर्ण, अणु 0, 1पूर्ण, अणु-1, 1पूर्ण, अणु-1, 0पूर्ण, अणु-1,-1पूर्णपूर्ण;

/*
 * Per-port inक्रमmation.
 */

काष्ठा adi अणु
	काष्ठा input_dev *dev;
	पूर्णांक length;
	पूर्णांक ret;
	पूर्णांक idx;
	अचिन्हित अक्षर id;
	अक्षर buttons;
	अक्षर axes10;
	अक्षर axes8;
	चिन्हित अक्षर pad;
	अक्षर hats;
	अक्षर *असल;
	लघु *key;
	अक्षर name[ADI_MAX_NAME_LENGTH];
	अक्षर cname[ADI_MAX_CNAME_LENGTH];
	अक्षर phys[ADI_MAX_PHYS_LENGTH];
	अचिन्हित अक्षर data[ADI_MAX_LENGTH];
पूर्ण;

काष्ठा adi_port अणु
	काष्ठा gameport *gameport;
	काष्ठा adi adi[2];
	पूर्णांक bad;
	पूर्णांक पढ़ोs;
पूर्ण;

/*
 * adi_पढ़ो_packet() पढ़ोs a Logitech ADI packet.
 */

अटल व्योम adi_पढ़ो_packet(काष्ठा adi_port *port)
अणु
	काष्ठा adi *adi = port->adi;
	काष्ठा gameport *gameport = port->gameport;
	अचिन्हित अक्षर u, v, w, x, z;
	पूर्णांक t[2], s[2], i;
	अचिन्हित दीर्घ flags;

	क्रम (i = 0; i < 2; i++) अणु
		adi[i].ret = -1;
		t[i] = gameport_समय(gameport, ADI_MAX_START);
		s[i] = 0;
	पूर्ण

	local_irq_save(flags);

	gameport_trigger(gameport);
	v = z = gameport_पढ़ो(gameport);

	करो अणु
		u = v;
		w = u ^ (v = x = gameport_पढ़ो(gameport));
		क्रम (i = 0; i < 2; i++, w >>= 2, x >>= 2) अणु
			t[i]--;
			अगर ((w & 0x30) && s[i]) अणु
				अगर ((w & 0x30) < 0x30 && adi[i].ret < ADI_MAX_LENGTH && t[i] > 0) अणु
					adi[i].data[++adi[i].ret] = w;
					t[i] = gameport_समय(gameport, ADI_MAX_STROBE);
				पूर्ण अन्यथा t[i] = 0;
			पूर्ण अन्यथा अगर (!(x & 0x30)) s[i] = 1;
		पूर्ण
	पूर्ण जबतक (t[0] > 0 || t[1] > 0);

	local_irq_restore(flags);

	वापस;
पूर्ण

/*
 * adi_move_bits() detects a possible 2-stream mode, and moves
 * the bits accordingly.
 */

अटल व्योम adi_move_bits(काष्ठा adi_port *port, पूर्णांक length)
अणु
	पूर्णांक i;
	काष्ठा adi *adi = port->adi;

	adi[0].idx = adi[1].idx = 0;

	अगर (adi[0].ret <= 0 || adi[1].ret <= 0) वापस;
	अगर (adi[0].data[0] & 0x20 || ~adi[1].data[0] & 0x20) वापस;

	क्रम (i = 1; i <= adi[1].ret; i++)
		adi[0].data[((length - 1) >> 1) + i + 1] = adi[1].data[i];

	adi[0].ret += adi[1].ret;
	adi[1].ret = -1;
पूर्ण

/*
 * adi_get_bits() gathers bits from the data packet.
 */

अटल अंतरभूत पूर्णांक adi_get_bits(काष्ठा adi *adi, पूर्णांक count)
अणु
	पूर्णांक bits = 0;
	पूर्णांक i;
	अगर ((adi->idx += count) > adi->ret) वापस 0;
	क्रम (i = 0; i < count; i++)
		bits |= ((adi->data[adi->idx - i] >> 5) & 1) << i;
	वापस bits;
पूर्ण

/*
 * adi_decode() decodes Logitech joystick data पूर्णांकo input events.
 */

अटल पूर्णांक adi_decode(काष्ठा adi *adi)
अणु
	काष्ठा input_dev *dev = adi->dev;
	अक्षर *असल = adi->असल;
	लघु *key = adi->key;
	पूर्णांक i, t;

	अगर (adi->ret < adi->length || adi->id != (adi_get_bits(adi, 4) | (adi_get_bits(adi, 4) << 4)))
		वापस -1;

	क्रम (i = 0; i < adi->axes10; i++)
		input_report_असल(dev, *असल++, adi_get_bits(adi, 10));

	क्रम (i = 0; i < adi->axes8; i++)
		input_report_असल(dev, *असल++, adi_get_bits(adi, 8));

	क्रम (i = 0; i < adi->buttons && i < 63; i++) अणु
		अगर (i == adi->pad) अणु
			t = adi_get_bits(adi, 4);
			input_report_असल(dev, *असल++, ((t >> 2) & 1) - ( t       & 1));
			input_report_असल(dev, *असल++, ((t >> 1) & 1) - ((t >> 3) & 1));
		पूर्ण
		input_report_key(dev, *key++, adi_get_bits(adi, 1));
	पूर्ण

	क्रम (i = 0; i < adi->hats; i++) अणु
		अगर ((t = adi_get_bits(adi, 4)) > 8) t = 0;
		input_report_असल(dev, *असल++, adi_hat_to_axis[t].x);
		input_report_असल(dev, *असल++, adi_hat_to_axis[t].y);
	पूर्ण

	क्रम (i = 63; i < adi->buttons; i++)
		input_report_key(dev, *key++, adi_get_bits(adi, 1));

	input_sync(dev);

	वापस 0;
पूर्ण

/*
 * adi_पढ़ो() पढ़ोs the data packet and decodes it.
 */

अटल पूर्णांक adi_पढ़ो(काष्ठा adi_port *port)
अणु
	पूर्णांक i;
	पूर्णांक result = 0;

	adi_पढ़ो_packet(port);
	adi_move_bits(port, port->adi[0].length);

	क्रम (i = 0; i < 2; i++)
		अगर (port->adi[i].length)
			 result |= adi_decode(port->adi + i);

	वापस result;
पूर्ण

/*
 * adi_poll() repeatedly polls the Logitech joysticks.
 */

अटल व्योम adi_poll(काष्ठा gameport *gameport)
अणु
	काष्ठा adi_port *port = gameport_get_drvdata(gameport);

	port->bad -= adi_पढ़ो(port);
	port->पढ़ोs++;
पूर्ण

/*
 * adi_खोलो() is a callback from the input खोलो routine.
 */

अटल पूर्णांक adi_खोलो(काष्ठा input_dev *dev)
अणु
	काष्ठा adi_port *port = input_get_drvdata(dev);

	gameport_start_polling(port->gameport);
	वापस 0;
पूर्ण

/*
 * adi_बंद() is a callback from the input बंद routine.
 */

अटल व्योम adi_बंद(काष्ठा input_dev *dev)
अणु
	काष्ठा adi_port *port = input_get_drvdata(dev);

	gameport_stop_polling(port->gameport);
पूर्ण

/*
 * adi_init_digital() sends a trigger & delay sequence
 * to reset and initialize a Logitech joystick पूर्णांकo digital mode.
 */

अटल व्योम adi_init_digital(काष्ठा gameport *gameport)
अणु
	अटल स्थिर पूर्णांक seq[] = अणु 4, -2, -3, 10, -6, -11, -7, -9, 11, 0 पूर्ण;
	पूर्णांक i;

	क्रम (i = 0; seq[i]; i++) अणु
		gameport_trigger(gameport);
		अगर (seq[i] > 0)
			msleep(seq[i]);
		अगर (seq[i] < 0) अणु
			mdelay(-seq[i]);
			udelay(-seq[i]*14);	/* It looks like mdelay() is off by approx 1.4% */
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम adi_id_decode(काष्ठा adi *adi, काष्ठा adi_port *port)
अणु
	पूर्णांक i, t;

	अगर (adi->ret < ADI_MIN_ID_LENGTH) /* Minimum ID packet length */
		वापस;

	अगर (adi->ret < (t = adi_get_bits(adi, 10))) अणु
		prपूर्णांकk(KERN_WARNING "adi: Short ID packet: reported: %d != read: %d\n", t, adi->ret);
		वापस;
	पूर्ण

	adi->id = adi_get_bits(adi, 4) | (adi_get_bits(adi, 4) << 4);

	अगर ((t = adi_get_bits(adi, 4)) & ADI_FLAG_HAT) adi->hats++;

	adi->length = adi_get_bits(adi, 10);

	अगर (adi->length >= ADI_MAX_LENGTH || adi->length < ADI_MIN_LENGTH) अणु
		prपूर्णांकk(KERN_WARNING "adi: Bad data packet length (%d).\n", adi->length);
		adi->length = 0;
		वापस;
	पूर्ण

	adi->axes8 = adi_get_bits(adi, 4);
	adi->buttons = adi_get_bits(adi, 6);

	अगर (adi_get_bits(adi, 6) != 8 && adi->hats) अणु
		prपूर्णांकk(KERN_WARNING "adi: Other than 8-dir POVs not supported yet.\n");
		adi->length = 0;
		वापस;
	पूर्ण

	adi->buttons += adi_get_bits(adi, 6);
	adi->hats += adi_get_bits(adi, 4);

	i = adi_get_bits(adi, 4);

	अगर (t & ADI_FLAG_10BIT) अणु
		adi->axes10 = adi->axes8 - i;
		adi->axes8 = i;
	पूर्ण

	t = adi_get_bits(adi, 4);

	क्रम (i = 0; i < t; i++)
		adi->cname[i] = adi_get_bits(adi, 8);
	adi->cname[i] = 0;

	t = 8 + adi->buttons + adi->axes10 * 10 + adi->axes8 * 8 + adi->hats * 4;
	अगर (adi->length != t && adi->length != t + (t & 1)) अणु
		prपूर्णांकk(KERN_WARNING "adi: Expected length %d != data length %d\n", t, adi->length);
		adi->length = 0;
		वापस;
	पूर्ण

	चयन (adi->id) अणु
		हाल ADI_ID_TPD:
			adi->pad = 4;
			adi->buttons -= 4;
			अवरोध;
		हाल ADI_ID_WGP:
			adi->pad = 0;
			adi->buttons -= 4;
			अवरोध;
		शेष:
			adi->pad = -1;
			अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक adi_init_input(काष्ठा adi *adi, काष्ठा adi_port *port, पूर्णांक half)
अणु
	काष्ठा input_dev *input_dev;
	अक्षर buf[ADI_MAX_NAME_LENGTH];
	पूर्णांक i, t;

	adi->dev = input_dev = input_allocate_device();
	अगर (!input_dev)
		वापस -ENOMEM;

	t = adi->id < ADI_ID_MAX ? adi->id : ADI_ID_MAX;

	snम_लिखो(buf, ADI_MAX_PHYS_LENGTH, adi_names[t], adi->id);
	snम_लिखो(adi->name, ADI_MAX_NAME_LENGTH, "Logitech %s [%s]", buf, adi->cname);
	snम_लिखो(adi->phys, ADI_MAX_PHYS_LENGTH, "%s/input%d", port->gameport->phys, half);

	adi->असल = adi_असल[t];
	adi->key = adi_key[t];

	input_dev->name = adi->name;
	input_dev->phys = adi->phys;
	input_dev->id.bustype = BUS_GAMEPORT;
	input_dev->id.venकरोr = GAMEPORT_ID_VENDOR_LOGITECH;
	input_dev->id.product = adi->id;
	input_dev->id.version = 0x0100;
	input_dev->dev.parent = &port->gameport->dev;

	input_set_drvdata(input_dev, port);

	input_dev->खोलो = adi_खोलो;
	input_dev->बंद = adi_बंद;

	input_dev->evbit[0] = BIT_MASK(EV_KEY) | BIT_MASK(EV_ABS);

	क्रम (i = 0; i < adi->axes10 + adi->axes8 + (adi->hats + (adi->pad != -1)) * 2; i++)
		set_bit(adi->असल[i], input_dev->असलbit);

	क्रम (i = 0; i < adi->buttons; i++)
		set_bit(adi->key[i], input_dev->keybit);

	वापस 0;
पूर्ण

अटल व्योम adi_init_center(काष्ठा adi *adi)
अणु
	पूर्णांक i, t, x;

	अगर (!adi->length)
		वापस;

	क्रम (i = 0; i < adi->axes10 + adi->axes8 + (adi->hats + (adi->pad != -1)) * 2; i++) अणु

		t = adi->असल[i];
		x = input_असल_get_val(adi->dev, t);

		अगर (t == ABS_THROTTLE || t == ABS_RUDDER || adi->id == ADI_ID_WGPE)
			x = i < adi->axes10 ? 512 : 128;

		अगर (i < adi->axes10)
			input_set_असल_params(adi->dev, t, 64, x * 2 - 64, 2, 16);
		अन्यथा अगर (i < adi->axes10 + adi->axes8)
			input_set_असल_params(adi->dev, t, 48, x * 2 - 48, 1, 16);
		अन्यथा
			input_set_असल_params(adi->dev, t, -1, 1, 0, 0);
	पूर्ण
पूर्ण

/*
 * adi_connect() probes क्रम Logitech ADI joysticks.
 */

अटल पूर्णांक adi_connect(काष्ठा gameport *gameport, काष्ठा gameport_driver *drv)
अणु
	काष्ठा adi_port *port;
	पूर्णांक i;
	पूर्णांक err;

	port = kzalloc(माप(काष्ठा adi_port), GFP_KERNEL);
	अगर (!port)
		वापस -ENOMEM;

	port->gameport = gameport;

	gameport_set_drvdata(gameport, port);

	err = gameport_खोलो(gameport, drv, GAMEPORT_MODE_RAW);
	अगर (err)
		जाओ fail1;

	adi_init_digital(gameport);
	adi_पढ़ो_packet(port);

	अगर (port->adi[0].ret >= ADI_MIN_LEN_LENGTH)
		adi_move_bits(port, adi_get_bits(port->adi, 10));

	क्रम (i = 0; i < 2; i++) अणु
		adi_id_decode(port->adi + i, port);

		अगर (!port->adi[i].length)
			जारी;

		err = adi_init_input(port->adi + i, port, i);
		अगर (err)
			जाओ fail2;
	पूर्ण

	अगर (!port->adi[0].length && !port->adi[1].length) अणु
		err = -ENODEV;
		जाओ fail2;
	पूर्ण

	gameport_set_poll_handler(gameport, adi_poll);
	gameport_set_poll_पूर्णांकerval(gameport, 20);

	msleep(ADI_INIT_DELAY);
	अगर (adi_पढ़ो(port)) अणु
		msleep(ADI_DATA_DELAY);
		adi_पढ़ो(port);
	पूर्ण

	क्रम (i = 0; i < 2; i++)
		अगर (port->adi[i].length > 0) अणु
			adi_init_center(port->adi + i);
			err = input_रेजिस्टर_device(port->adi[i].dev);
			अगर (err)
				जाओ fail3;
		पूर्ण

	वापस 0;

 fail3: जबतक (--i >= 0) अणु
		अगर (port->adi[i].length > 0) अणु
			input_unरेजिस्टर_device(port->adi[i].dev);
			port->adi[i].dev = शून्य;
		पूर्ण
	पूर्ण
 fail2:	क्रम (i = 0; i < 2; i++)
		input_मुक्त_device(port->adi[i].dev);
	gameport_बंद(gameport);
 fail1:	gameport_set_drvdata(gameport, शून्य);
	kमुक्त(port);
	वापस err;
पूर्ण

अटल व्योम adi_disconnect(काष्ठा gameport *gameport)
अणु
	पूर्णांक i;
	काष्ठा adi_port *port = gameport_get_drvdata(gameport);

	क्रम (i = 0; i < 2; i++)
		अगर (port->adi[i].length > 0)
			input_unरेजिस्टर_device(port->adi[i].dev);
	gameport_बंद(gameport);
	gameport_set_drvdata(gameport, शून्य);
	kमुक्त(port);
पूर्ण

अटल काष्ठा gameport_driver adi_drv = अणु
	.driver		= अणु
		.name	= "adi",
	पूर्ण,
	.description	= DRIVER_DESC,
	.connect	= adi_connect,
	.disconnect	= adi_disconnect,
पूर्ण;

module_gameport_driver(adi_drv);
