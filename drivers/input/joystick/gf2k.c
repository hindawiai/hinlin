<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Copyright (c) 1998-2001 Vojtech Pavlik
 */

/*
 * Genius Flight 2000 joystick driver क्रम Linux
 */

/*
 */

#समावेश <linux/delay.h>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/input.h>
#समावेश <linux/gameport.h>
#समावेश <linux/jअगरfies.h>

#घोषणा DRIVER_DESC	"Genius Flight 2000 joystick driver"

MODULE_AUTHOR("Vojtech Pavlik <vojtech@ucw.cz>");
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_LICENSE("GPL");

#घोषणा GF2K_START		400	/* The समय we रुको क्रम the first bit [400 us] */
#घोषणा GF2K_STROBE		40	/* The समय we रुको क्रम the first bit [40 us] */
#घोषणा GF2K_TIMEOUT		4	/* Wait क्रम everything to settle [4 ms] */
#घोषणा GF2K_LENGTH		80	/* Max number of triplets in a packet */

/*
 * Genius joystick ids ...
 */

#घोषणा GF2K_ID_G09		1
#घोषणा GF2K_ID_F30D		2
#घोषणा GF2K_ID_F30		3
#घोषणा GF2K_ID_F31D		4
#घोषणा GF2K_ID_F305		5
#घोषणा GF2K_ID_F23P		6
#घोषणा GF2K_ID_F31		7
#घोषणा GF2K_ID_MAX		7

अटल अक्षर gf2k_length[] = अणु 40, 40, 40, 40, 40, 40, 40, 40 पूर्ण;
अटल अक्षर gf2k_hat_to_axis[][2] = अणुअणु 0, 0पूर्ण, अणु 0,-1पूर्ण, अणु 1,-1पूर्ण, अणु 1, 0पूर्ण, अणु 1, 1पूर्ण, अणु 0, 1पूर्ण, अणु-1, 1पूर्ण, अणु-1, 0पूर्ण, अणु-1,-1पूर्णपूर्ण;

अटल अक्षर *gf2k_names[] = अणु"", "Genius G-09D", "Genius F-30D", "Genius F-30", "Genius MaxFighter F-31D",
				"Genius F-30-5", "Genius Flight2000 F-23", "Genius F-31"पूर्ण;
अटल अचिन्हित अक्षर gf2k_hats[] = अणु 0, 2, 0, 0, 2, 0, 2, 0 पूर्ण;
अटल अचिन्हित अक्षर gf2k_axes[] = अणु 0, 2, 0, 0, 4, 0, 4, 0 पूर्ण;
अटल अचिन्हित अक्षर gf2k_joys[] = अणु 0, 0, 0, 0,10, 0, 8, 0 पूर्ण;
अटल अचिन्हित अक्षर gf2k_pads[] = अणु 0, 6, 0, 0, 0, 0, 0, 0 पूर्ण;
अटल अचिन्हित अक्षर gf2k_lens[] = अणु 0,18, 0, 0,18, 0,18, 0 पूर्ण;

अटल अचिन्हित अक्षर gf2k_असल[] = अणु ABS_X, ABS_Y, ABS_THROTTLE, ABS_RUDDER, ABS_GAS, ABS_BRAKE पूर्ण;
अटल लघु gf2k_btn_joy[] = अणु BTN_TRIGGER, BTN_THUMB, BTN_TOP, BTN_TOP2, BTN_BASE, BTN_BASE2, BTN_BASE3, BTN_BASE4 पूर्ण;
अटल लघु gf2k_btn_pad[] = अणु BTN_A, BTN_B, BTN_C, BTN_X, BTN_Y, BTN_Z, BTN_TL, BTN_TR, BTN_TL2, BTN_TR2, BTN_START, BTN_SELECT पूर्ण;


अटल लघु gf2k_seq_reset[] = अणु 240, 340, 0 पूर्ण;
अटल लघु gf2k_seq_digital[] = अणु 590, 320, 860, 0 पूर्ण;

काष्ठा gf2k अणु
	काष्ठा gameport *gameport;
	काष्ठा input_dev *dev;
	पूर्णांक पढ़ोs;
	पूर्णांक bads;
	अचिन्हित अक्षर id;
	अचिन्हित अक्षर length;
	अक्षर phys[32];
पूर्ण;

/*
 * gf2k_पढ़ो_packet() पढ़ोs a Genius Flight2000 packet.
 */

अटल पूर्णांक gf2k_पढ़ो_packet(काष्ठा gameport *gameport, पूर्णांक length, अक्षर *data)
अणु
	अचिन्हित अक्षर u, v;
	पूर्णांक i;
	अचिन्हित पूर्णांक t, p;
	अचिन्हित दीर्घ flags;

	t = gameport_समय(gameport, GF2K_START);
	p = gameport_समय(gameport, GF2K_STROBE);

	i = 0;

	local_irq_save(flags);

	gameport_trigger(gameport);
	v = gameport_पढ़ो(gameport);

	जबतक (t > 0 && i < length) अणु
		t--; u = v;
		v = gameport_पढ़ो(gameport);
		अगर (v & ~u & 0x10) अणु
			data[i++] = v >> 5;
			t = p;
		पूर्ण
	पूर्ण

	local_irq_restore(flags);

	वापस i;
पूर्ण

/*
 * gf2k_trigger_seq() initializes a Genius Flight2000 joystick
 * पूर्णांकo digital mode.
 */

अटल व्योम gf2k_trigger_seq(काष्ठा gameport *gameport, लघु *seq)
अणु

	अचिन्हित दीर्घ flags;
	पूर्णांक i, t;

        local_irq_save(flags);

	i = 0;
        करो अणु
		gameport_trigger(gameport);
		t = gameport_समय(gameport, GF2K_TIMEOUT * 1000);
		जबतक ((gameport_पढ़ो(gameport) & 1) && t) t--;
                udelay(seq[i]);
        पूर्ण जबतक (seq[++i]);

	gameport_trigger(gameport);

	local_irq_restore(flags);
पूर्ण

/*
 * js_sw_get_bits() composes bits from the triplet buffer पूर्णांकo a __u64.
 * Parameter 'pos' is bit number inside packet where to start at, 'num' is number
 * of bits to be पढ़ो, 'shift' is offset in the resulting __u64 to start at, bits
 * is number of bits per triplet.
 */

#घोषणा GB(p,n,s)	gf2k_get_bits(data, p, n, s)

अटल पूर्णांक gf2k_get_bits(अचिन्हित अक्षर *buf, पूर्णांक pos, पूर्णांक num, पूर्णांक shअगरt)
अणु
	__u64 data = 0;
	पूर्णांक i;

	क्रम (i = 0; i < num / 3 + 2; i++)
		data |= buf[pos / 3 + i] << (i * 3);
	data >>= pos % 3;
	data &= (1 << num) - 1;
	data <<= shअगरt;

	वापस data;
पूर्ण

अटल व्योम gf2k_पढ़ो(काष्ठा gf2k *gf2k, अचिन्हित अक्षर *data)
अणु
	काष्ठा input_dev *dev = gf2k->dev;
	पूर्णांक i, t;

	क्रम (i = 0; i < 4 && i < gf2k_axes[gf2k->id]; i++)
		input_report_असल(dev, gf2k_असल[i], GB(i<<3,8,0) | GB(i+46,1,8) | GB(i+50,1,9));

	क्रम (i = 0; i < 2 && i < gf2k_axes[gf2k->id] - 4; i++)
		input_report_असल(dev, gf2k_असल[i], GB(i*9+60,8,0) | GB(i+54,1,9));

	t = GB(40,4,0);

	क्रम (i = 0; i < gf2k_hats[gf2k->id]; i++)
		input_report_असल(dev, ABS_HAT0X + i, gf2k_hat_to_axis[t][i]);

	t = GB(44,2,0) | GB(32,8,2) | GB(78,2,10);

	क्रम (i = 0; i < gf2k_joys[gf2k->id]; i++)
		input_report_key(dev, gf2k_btn_joy[i], (t >> i) & 1);

	क्रम (i = 0; i < gf2k_pads[gf2k->id]; i++)
		input_report_key(dev, gf2k_btn_pad[i], (t >> i) & 1);

	input_sync(dev);
पूर्ण

/*
 * gf2k_poll() पढ़ोs and analyzes Genius joystick data.
 */

अटल व्योम gf2k_poll(काष्ठा gameport *gameport)
अणु
	काष्ठा gf2k *gf2k = gameport_get_drvdata(gameport);
	अचिन्हित अक्षर data[GF2K_LENGTH];

	gf2k->पढ़ोs++;

	अगर (gf2k_पढ़ो_packet(gf2k->gameport, gf2k_length[gf2k->id], data) < gf2k_length[gf2k->id])
		gf2k->bads++;
	अन्यथा
		gf2k_पढ़ो(gf2k, data);
पूर्ण

अटल पूर्णांक gf2k_खोलो(काष्ठा input_dev *dev)
अणु
	काष्ठा gf2k *gf2k = input_get_drvdata(dev);

	gameport_start_polling(gf2k->gameport);
	वापस 0;
पूर्ण

अटल व्योम gf2k_बंद(काष्ठा input_dev *dev)
अणु
	काष्ठा gf2k *gf2k = input_get_drvdata(dev);

	gameport_stop_polling(gf2k->gameport);
पूर्ण

/*
 * gf2k_connect() probes क्रम Genius id joysticks.
 */

अटल पूर्णांक gf2k_connect(काष्ठा gameport *gameport, काष्ठा gameport_driver *drv)
अणु
	काष्ठा gf2k *gf2k;
	काष्ठा input_dev *input_dev;
	अचिन्हित अक्षर data[GF2K_LENGTH];
	पूर्णांक i, err;

	gf2k = kzalloc(माप(काष्ठा gf2k), GFP_KERNEL);
	input_dev = input_allocate_device();
	अगर (!gf2k || !input_dev) अणु
		err = -ENOMEM;
		जाओ fail1;
	पूर्ण

	gf2k->gameport = gameport;
	gf2k->dev = input_dev;

	gameport_set_drvdata(gameport, gf2k);

	err = gameport_खोलो(gameport, drv, GAMEPORT_MODE_RAW);
	अगर (err)
		जाओ fail1;

	gf2k_trigger_seq(gameport, gf2k_seq_reset);

	msleep(GF2K_TIMEOUT);

	gf2k_trigger_seq(gameport, gf2k_seq_digital);

	msleep(GF2K_TIMEOUT);

	अगर (gf2k_पढ़ो_packet(gameport, GF2K_LENGTH, data) < 12) अणु
		err = -ENODEV;
		जाओ fail2;
	पूर्ण

	अगर (!(gf2k->id = GB(7,2,0) | GB(3,3,2) | GB(0,3,5))) अणु
		err = -ENODEV;
		जाओ fail2;
	पूर्ण

#अगर_घोषित RESET_WORKS
	अगर ((gf2k->id != (GB(19,2,0) | GB(15,3,2) | GB(12,3,5))) &&
	    (gf2k->id != (GB(31,2,0) | GB(27,3,2) | GB(24,3,5)))) अणु
		err = -ENODEV;
		जाओ fail2;
	पूर्ण
#अन्यथा
	gf2k->id = 6;
#पूर्ण_अगर

	अगर (gf2k->id > GF2K_ID_MAX || !gf2k_axes[gf2k->id]) अणु
		prपूर्णांकk(KERN_WARNING "gf2k.c: Not yet supported joystick on %s. [id: %d type:%s]\n",
			gameport->phys, gf2k->id, gf2k->id > GF2K_ID_MAX ? "Unknown" : gf2k_names[gf2k->id]);
		err = -ENODEV;
		जाओ fail2;
	पूर्ण

	gameport_set_poll_handler(gameport, gf2k_poll);
	gameport_set_poll_पूर्णांकerval(gameport, 20);

	snम_लिखो(gf2k->phys, माप(gf2k->phys), "%s/input0", gameport->phys);

	gf2k->length = gf2k_lens[gf2k->id];

	input_dev->name = gf2k_names[gf2k->id];
	input_dev->phys = gf2k->phys;
	input_dev->id.bustype = BUS_GAMEPORT;
	input_dev->id.venकरोr = GAMEPORT_ID_VENDOR_GENIUS;
	input_dev->id.product = gf2k->id;
	input_dev->id.version = 0x0100;
	input_dev->dev.parent = &gameport->dev;

	input_set_drvdata(input_dev, gf2k);

	input_dev->खोलो = gf2k_खोलो;
	input_dev->बंद = gf2k_बंद;

	input_dev->evbit[0] = BIT_MASK(EV_KEY) | BIT_MASK(EV_ABS);

	क्रम (i = 0; i < gf2k_axes[gf2k->id]; i++)
		set_bit(gf2k_असल[i], input_dev->असलbit);

	क्रम (i = 0; i < gf2k_hats[gf2k->id]; i++)
		input_set_असल_params(input_dev, ABS_HAT0X + i, -1, 1, 0, 0);

	क्रम (i = 0; i < gf2k_joys[gf2k->id]; i++)
		set_bit(gf2k_btn_joy[i], input_dev->keybit);

	क्रम (i = 0; i < gf2k_pads[gf2k->id]; i++)
		set_bit(gf2k_btn_pad[i], input_dev->keybit);

	gf2k_पढ़ो_packet(gameport, gf2k->length, data);
	gf2k_पढ़ो(gf2k, data);

	क्रम (i = 0; i < gf2k_axes[gf2k->id]; i++) अणु
		पूर्णांक max = i < 2 ?
			input_असल_get_val(input_dev, gf2k_असल[i]) * 2 :
			input_असल_get_val(input_dev, gf2k_असल[0]) +
				input_असल_get_val(input_dev, gf2k_असल[1]);
		पूर्णांक flat = i < 2 ? 24 : 0;

		input_set_असल_params(input_dev, gf2k_असल[i],
				     32, max - 32, 8, flat);
	पूर्ण

	err = input_रेजिस्टर_device(gf2k->dev);
	अगर (err)
		जाओ fail2;

	वापस 0;

 fail2:	gameport_बंद(gameport);
 fail1:	gameport_set_drvdata(gameport, शून्य);
	input_मुक्त_device(input_dev);
	kमुक्त(gf2k);
	वापस err;
पूर्ण

अटल व्योम gf2k_disconnect(काष्ठा gameport *gameport)
अणु
	काष्ठा gf2k *gf2k = gameport_get_drvdata(gameport);

	input_unरेजिस्टर_device(gf2k->dev);
	gameport_बंद(gameport);
	gameport_set_drvdata(gameport, शून्य);
	kमुक्त(gf2k);
पूर्ण

अटल काष्ठा gameport_driver gf2k_drv = अणु
	.driver		= अणु
		.name	= "gf2k",
	पूर्ण,
	.description	= DRIVER_DESC,
	.connect	= gf2k_connect,
	.disconnect	= gf2k_disconnect,
पूर्ण;

module_gameport_driver(gf2k_drv);
