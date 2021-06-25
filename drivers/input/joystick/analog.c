<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Copyright (c) 1996-2001 Vojtech Pavlik
 */

/*
 * Analog joystick and gamepad driver क्रम Linux
 */

/*
 */

#समावेश <linux/delay.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/bitops.h>
#समावेश <linux/init.h>
#समावेश <linux/input.h>
#समावेश <linux/gameport.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/समयx.h>
#समावेश <linux/समयkeeping.h>

#घोषणा DRIVER_DESC	"Analog joystick and gamepad driver"

MODULE_AUTHOR("Vojtech Pavlik <vojtech@ucw.cz>");
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_LICENSE("GPL");

अटल bool use_kसमय = true;
module_param(use_kसमय, bool, 0400);
MODULE_PARM_DESC(use_kसमय, "Use ktime for measuring I/O speed");

/*
 * Option parsing.
 */

#घोषणा ANALOG_PORTS		16

अटल अक्षर *js[ANALOG_PORTS];
अटल अचिन्हित पूर्णांक js_nargs;
अटल पूर्णांक analog_options[ANALOG_PORTS];
module_param_array_named(map, js, अक्षरp, &js_nargs, 0);
MODULE_PARM_DESC(map, "Describes analog joysticks type/capabilities");

/*
 * Times, feature definitions.
 */

#घोषणा ANALOG_RUDDER		0x00004
#घोषणा ANALOG_THROTTLE		0x00008
#घोषणा ANALOG_AXES_STD		0x0000f
#घोषणा ANALOG_BTNS_STD		0x000f0

#घोषणा ANALOG_BTNS_CHF		0x00100
#घोषणा ANALOG_HAT1_CHF		0x00200
#घोषणा ANALOG_HAT2_CHF		0x00400
#घोषणा ANALOG_HAT_FCS		0x00800
#घोषणा ANALOG_HATS_ALL		0x00e00
#घोषणा ANALOG_BTN_TL		0x01000
#घोषणा ANALOG_BTN_TR		0x02000
#घोषणा ANALOG_BTN_TL2		0x04000
#घोषणा ANALOG_BTN_TR2		0x08000
#घोषणा ANALOG_BTNS_TLR		0x03000
#घोषणा ANALOG_BTNS_TLR2	0x0c000
#घोषणा ANALOG_BTNS_GAMEPAD	0x0f000

#घोषणा ANALOG_HBTN_CHF		0x10000
#घोषणा ANALOG_ANY_CHF		0x10700
#घोषणा ANALOG_SAITEK		0x20000
#घोषणा ANALOG_EXTENSIONS	0x7ff00
#घोषणा ANALOG_GAMEPAD		0x80000

#घोषणा ANALOG_MAX_TIME		3	/* 3 ms */
#घोषणा ANALOG_LOOP_TIME	2000	/* 2 * loop */
#घोषणा ANALOG_SAITEK_DELAY	200	/* 200 us */
#घोषणा ANALOG_SAITEK_TIME	2000	/* 2000 us */
#घोषणा ANALOG_AXIS_TIME	2	/* 2 * refresh */
#घोषणा ANALOG_INIT_RETRIES	8	/* 8 बार */
#घोषणा ANALOG_FUZZ_BITS	2	/* 2 bit more */
#घोषणा ANALOG_FUZZ_MAGIC	36	/* 36 u*ms/loop */

#घोषणा ANALOG_MAX_NAME_LENGTH  128
#घोषणा ANALOG_MAX_PHYS_LENGTH	32

अटल लघु analog_axes[] = अणु ABS_X, ABS_Y, ABS_RUDDER, ABS_THROTTLE पूर्ण;
अटल लघु analog_hats[] = अणु ABS_HAT0X, ABS_HAT0Y, ABS_HAT1X, ABS_HAT1Y, ABS_HAT2X, ABS_HAT2Y पूर्ण;
अटल लघु analog_pads[] = अणु BTN_Y, BTN_Z, BTN_TL, BTN_TR पूर्ण;
अटल लघु analog_exts[] = अणु ANALOG_HAT1_CHF, ANALOG_HAT2_CHF, ANALOG_HAT_FCS पूर्ण;
अटल लघु analog_pad_btn[] = अणु BTN_A, BTN_B, BTN_C, BTN_X, BTN_TL2, BTN_TR2, BTN_SELECT, BTN_START, BTN_MODE, BTN_BASE पूर्ण;
अटल लघु analog_joy_btn[] = अणु BTN_TRIGGER, BTN_THUMB, BTN_TOP, BTN_TOP2, BTN_BASE, BTN_BASE2,
				  BTN_BASE3, BTN_BASE4, BTN_BASE5, BTN_BASE6 पूर्ण;

अटल अचिन्हित अक्षर analog_chf[] = अणु 0xf, 0x0, 0x1, 0x9, 0x2, 0x4, 0xc, 0x8, 0x3, 0x5, 0xb, 0x7, 0xd, 0xe, 0xa, 0x6 पूर्ण;

काष्ठा analog अणु
	काष्ठा input_dev *dev;
	पूर्णांक mask;
	लघु *buttons;
	अक्षर name[ANALOG_MAX_NAME_LENGTH];
	अक्षर phys[ANALOG_MAX_PHYS_LENGTH];
पूर्ण;

काष्ठा analog_port अणु
	काष्ठा gameport *gameport;
	काष्ठा analog analog[2];
	अचिन्हित अक्षर mask;
	अक्षर saitek;
	अक्षर cooked;
	पूर्णांक bads;
	पूर्णांक पढ़ोs;
	पूर्णांक speed;
	पूर्णांक loop;
	पूर्णांक fuzz;
	पूर्णांक axes[4];
	पूर्णांक buttons;
	पूर्णांक initial[4];
	पूर्णांक axसमय;
पूर्ण;

/*
 * Time macros.
 */

#अगर_घोषित __i386__

#समावेश <linux/i8253.h>

#घोषणा GET_TIME(x)	करो अणु अगर (boot_cpu_has(X86_FEATURE_TSC)) x = (अचिन्हित पूर्णांक)rdtsc(); अन्यथा x = get_समय_pit(); पूर्ण जबतक (0)
#घोषणा DELTA(x,y)	(boot_cpu_has(X86_FEATURE_TSC) ? ((y) - (x)) : ((x) - (y) + ((x) < (y) ? PIT_TICK_RATE / HZ : 0)))
#घोषणा TIME_NAME	(boot_cpu_has(X86_FEATURE_TSC)?"TSC":"PIT")
अटल अचिन्हित पूर्णांक get_समय_pit(व्योम)
अणु
        अचिन्हित दीर्घ flags;
        अचिन्हित पूर्णांक count;

        raw_spin_lock_irqsave(&i8253_lock, flags);
        outb_p(0x00, 0x43);
        count = inb_p(0x40);
        count |= inb_p(0x40) << 8;
        raw_spin_unlock_irqrestore(&i8253_lock, flags);

        वापस count;
पूर्ण
#या_अगर defined(__x86_64__)
#घोषणा GET_TIME(x)	करो अणु x = (अचिन्हित पूर्णांक)rdtsc(); पूर्ण जबतक (0)
#घोषणा DELTA(x,y)	((y)-(x))
#घोषणा TIME_NAME	"TSC"
#या_अगर defined(__alpha__) || defined(CONFIG_ARM) || defined(CONFIG_ARM64) || defined(CONFIG_PPC) || defined(CONFIG_RISCV)
#घोषणा GET_TIME(x)	करो अणु x = get_cycles(); पूर्ण जबतक (0)
#घोषणा DELTA(x,y)	((y)-(x))
#घोषणा TIME_NAME	"get_cycles"
#अन्यथा
#घोषणा FAKE_TIME
अटल अचिन्हित दीर्घ analog_fakeसमय = 0;
#घोषणा GET_TIME(x)     करो अणु x = analog_fakeसमय++; पूर्ण जबतक(0)
#घोषणा DELTA(x,y)	((y)-(x))
#घोषणा TIME_NAME	"Unreliable"
#warning Precise समयr not defined क्रम this architecture.
#पूर्ण_अगर

अटल अंतरभूत u64 get_समय(व्योम)
अणु
	अगर (use_kसमय) अणु
		वापस kसमय_get_ns();
	पूर्ण अन्यथा अणु
		अचिन्हित पूर्णांक x;
		GET_TIME(x);
		वापस x;
	पूर्ण
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक delta(u64 x, u64 y)
अणु
	अगर (use_kसमय)
		वापस y - x;
	अन्यथा
		वापस DELTA((अचिन्हित पूर्णांक)x, (अचिन्हित पूर्णांक)y);
पूर्ण

/*
 * analog_decode() decodes analog joystick data and reports input events.
 */

अटल व्योम analog_decode(काष्ठा analog *analog, पूर्णांक *axes, पूर्णांक *initial, पूर्णांक buttons)
अणु
	काष्ठा input_dev *dev = analog->dev;
	पूर्णांक i, j;

	अगर (analog->mask & ANALOG_HAT_FCS)
		क्रम (i = 0; i < 4; i++)
			अगर (axes[3] < ((initial[3] * ((i << 1) + 1)) >> 3)) अणु
				buttons |= 1 << (i + 14);
				अवरोध;
			पूर्ण

	क्रम (i = j = 0; i < 6; i++)
		अगर (analog->mask & (0x10 << i))
			input_report_key(dev, analog->buttons[j++], (buttons >> i) & 1);

	अगर (analog->mask & ANALOG_HBTN_CHF)
		क्रम (i = 0; i < 4; i++)
			input_report_key(dev, analog->buttons[j++], (buttons >> (i + 10)) & 1);

	अगर (analog->mask & ANALOG_BTN_TL)
		input_report_key(dev, analog_pads[0], axes[2] < (initial[2] >> 1));
	अगर (analog->mask & ANALOG_BTN_TR)
		input_report_key(dev, analog_pads[1], axes[3] < (initial[3] >> 1));
	अगर (analog->mask & ANALOG_BTN_TL2)
		input_report_key(dev, analog_pads[2], axes[2] > (initial[2] + (initial[2] >> 1)));
	अगर (analog->mask & ANALOG_BTN_TR2)
		input_report_key(dev, analog_pads[3], axes[3] > (initial[3] + (initial[3] >> 1)));

	क्रम (i = j = 0; i < 4; i++)
		अगर (analog->mask & (1 << i))
			input_report_असल(dev, analog_axes[j++], axes[i]);

	क्रम (i = j = 0; i < 3; i++)
		अगर (analog->mask & analog_exts[i]) अणु
			input_report_असल(dev, analog_hats[j++],
				((buttons >> ((i << 2) + 7)) & 1) - ((buttons >> ((i << 2) + 9)) & 1));
			input_report_असल(dev, analog_hats[j++],
				((buttons >> ((i << 2) + 8)) & 1) - ((buttons >> ((i << 2) + 6)) & 1));
		पूर्ण

	input_sync(dev);
पूर्ण

/*
 * analog_cooked_पढ़ो() पढ़ोs analog joystick data.
 */

अटल पूर्णांक analog_cooked_पढ़ो(काष्ठा analog_port *port)
अणु
	काष्ठा gameport *gameport = port->gameport;
	u64 समय[4], start, loop, now;
	अचिन्हित पूर्णांक loopout, समयout;
	अचिन्हित अक्षर data[4], this, last;
	अचिन्हित दीर्घ flags;
	पूर्णांक i, j;

	loopout = (ANALOG_LOOP_TIME * port->loop) / 1000;
	समयout = ANALOG_MAX_TIME * port->speed;

	local_irq_save(flags);
	gameport_trigger(gameport);
	now = get_समय();
	local_irq_restore(flags);

	start = now;
	this = port->mask;
	i = 0;

	करो अणु
		loop = now;
		last = this;

		local_irq_disable();
		this = gameport_पढ़ो(gameport) & port->mask;
		now = get_समय();
		local_irq_restore(flags);

		अगर ((last ^ this) && (delta(loop, now) < loopout)) अणु
			data[i] = last ^ this;
			समय[i] = now;
			i++;
		पूर्ण

	पूर्ण जबतक (this && (i < 4) && (delta(start, now) < समयout));

	this <<= 4;

	क्रम (--i; i >= 0; i--) अणु
		this |= data[i];
		क्रम (j = 0; j < 4; j++)
			अगर (data[i] & (1 << j))
				port->axes[j] = (delta(start, समय[i]) << ANALOG_FUZZ_BITS) / port->loop;
	पूर्ण

	वापस -(this != port->mask);
पूर्ण

अटल पूर्णांक analog_button_पढ़ो(काष्ठा analog_port *port, अक्षर saitek, अक्षर chf)
अणु
	अचिन्हित अक्षर u;
	पूर्णांक t = 1, i = 0;
	पूर्णांक strobe = gameport_समय(port->gameport, ANALOG_SAITEK_TIME);

	u = gameport_पढ़ो(port->gameport);

	अगर (!chf) अणु
		port->buttons = (~u >> 4) & 0xf;
		वापस 0;
	पूर्ण

	port->buttons = 0;

	जबतक ((~u & 0xf0) && (i < 16) && t) अणु
		port->buttons |= 1 << analog_chf[(~u >> 4) & 0xf];
		अगर (!saitek) वापस 0;
		udelay(ANALOG_SAITEK_DELAY);
		t = strobe;
		gameport_trigger(port->gameport);
		जबतक (((u = gameport_पढ़ो(port->gameport)) & port->mask) && t) t--;
		i++;
	पूर्ण

	वापस -(!t || (i == 16));
पूर्ण

/*
 * analog_poll() repeatedly polls the Analog joysticks.
 */

अटल व्योम analog_poll(काष्ठा gameport *gameport)
अणु
	काष्ठा analog_port *port = gameport_get_drvdata(gameport);
	पूर्णांक i;

	अक्षर saitek = !!(port->analog[0].mask & ANALOG_SAITEK);
	अक्षर chf = !!(port->analog[0].mask & ANALOG_ANY_CHF);

	अगर (port->cooked) अणु
		port->bads -= gameport_cooked_पढ़ो(port->gameport, port->axes, &port->buttons);
		अगर (chf)
			port->buttons = port->buttons ? (1 << analog_chf[port->buttons]) : 0;
		port->पढ़ोs++;
	पूर्ण अन्यथा अणु
		अगर (!port->axसमय--) अणु
			port->bads -= analog_cooked_पढ़ो(port);
			port->bads -= analog_button_पढ़ो(port, saitek, chf);
			port->पढ़ोs++;
			port->axसमय = ANALOG_AXIS_TIME - 1;
		पूर्ण अन्यथा अणु
			अगर (!saitek)
				analog_button_पढ़ो(port, saitek, chf);
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < 2; i++)
		अगर (port->analog[i].mask)
			analog_decode(port->analog + i, port->axes, port->initial, port->buttons);
पूर्ण

/*
 * analog_खोलो() is a callback from the input खोलो routine.
 */

अटल पूर्णांक analog_खोलो(काष्ठा input_dev *dev)
अणु
	काष्ठा analog_port *port = input_get_drvdata(dev);

	gameport_start_polling(port->gameport);
	वापस 0;
पूर्ण

/*
 * analog_बंद() is a callback from the input बंद routine.
 */

अटल व्योम analog_बंद(काष्ठा input_dev *dev)
अणु
	काष्ठा analog_port *port = input_get_drvdata(dev);

	gameport_stop_polling(port->gameport);
पूर्ण

/*
 * analog_calibrate_समयr() calibrates the समयr and computes loop
 * and समयout values क्रम a joystick port.
 */

अटल व्योम analog_calibrate_समयr(काष्ठा analog_port *port)
अणु
	काष्ठा gameport *gameport = port->gameport;
	अचिन्हित पूर्णांक i, t, tx;
	u64 t1, t2, t3;
	अचिन्हित दीर्घ flags;

	अगर (use_kसमय) अणु
		port->speed = 1000000;
	पूर्ण अन्यथा अणु
		local_irq_save(flags);
		t1 = get_समय();
#अगर_घोषित FAKE_TIME
		analog_fakeसमय += 830;
#पूर्ण_अगर
		mdelay(1);
		t2 = get_समय();
		t3 = get_समय();
		local_irq_restore(flags);

		port->speed = delta(t1, t2) - delta(t2, t3);
	पूर्ण

	tx = ~0;

	क्रम (i = 0; i < 50; i++) अणु
		local_irq_save(flags);
		t1 = get_समय();
		क्रम (t = 0; t < 50; t++) अणु
			gameport_पढ़ो(gameport);
			t2 = get_समय();
		पूर्ण
		t3 = get_समय();
		local_irq_restore(flags);
		udelay(i);
		t = delta(t1, t2) - delta(t2, t3);
		अगर (t < tx) tx = t;
	पूर्ण

        port->loop = tx / 50;
पूर्ण

/*
 * analog_name() स्थिरructs a name क्रम an analog joystick.
 */

अटल व्योम analog_name(काष्ठा analog *analog)
अणु
	snम_लिखो(analog->name, माप(analog->name), "Analog %d-axis %d-button",
		 hweight8(analog->mask & ANALOG_AXES_STD),
		 hweight8(analog->mask & ANALOG_BTNS_STD) + !!(analog->mask & ANALOG_BTNS_CHF) * 2 +
		 hweight16(analog->mask & ANALOG_BTNS_GAMEPAD) + !!(analog->mask & ANALOG_HBTN_CHF) * 4);

	अगर (analog->mask & ANALOG_HATS_ALL)
		snम_लिखो(analog->name, माप(analog->name), "%s %d-hat",
			 analog->name, hweight16(analog->mask & ANALOG_HATS_ALL));

	अगर (analog->mask & ANALOG_HAT_FCS)
		strlcat(analog->name, " FCS", माप(analog->name));
	अगर (analog->mask & ANALOG_ANY_CHF)
		strlcat(analog->name, (analog->mask & ANALOG_SAITEK) ? " Saitek" : " CHF",
			माप(analog->name));

	strlcat(analog->name, (analog->mask & ANALOG_GAMEPAD) ? " gamepad": " joystick",
		माप(analog->name));
पूर्ण

/*
 * analog_init_device()
 */

अटल पूर्णांक analog_init_device(काष्ठा analog_port *port, काष्ठा analog *analog, पूर्णांक index)
अणु
	काष्ठा input_dev *input_dev;
	पूर्णांक i, j, t, v, w, x, y, z;
	पूर्णांक error;

	analog_name(analog);
	snम_लिखो(analog->phys, माप(analog->phys),
		 "%s/input%d", port->gameport->phys, index);
	analog->buttons = (analog->mask & ANALOG_GAMEPAD) ? analog_pad_btn : analog_joy_btn;

	analog->dev = input_dev = input_allocate_device();
	अगर (!input_dev)
		वापस -ENOMEM;

	input_dev->name = analog->name;
	input_dev->phys = analog->phys;
	input_dev->id.bustype = BUS_GAMEPORT;
	input_dev->id.venकरोr = GAMEPORT_ID_VENDOR_ANALOG;
	input_dev->id.product = analog->mask >> 4;
	input_dev->id.version = 0x0100;
	input_dev->dev.parent = &port->gameport->dev;

	input_set_drvdata(input_dev, port);

	input_dev->खोलो = analog_खोलो;
	input_dev->बंद = analog_बंद;

	input_dev->evbit[0] = BIT_MASK(EV_KEY) | BIT_MASK(EV_ABS);

	क्रम (i = j = 0; i < 4; i++)
		अगर (analog->mask & (1 << i)) अणु

			t = analog_axes[j];
			x = port->axes[i];
			y = (port->axes[0] + port->axes[1]) >> 1;
			z = y - port->axes[i];
			z = z > 0 ? z : -z;
			v = (x >> 3);
			w = (x >> 3);

			अगर ((i == 2 || i == 3) && (j == 2 || j == 3) && (z > (y >> 3)))
				x = y;

			अगर (analog->mask & ANALOG_SAITEK) अणु
				अगर (i == 2) x = port->axes[i];
				v = x - (x >> 2);
				w = (x >> 4);
			पूर्ण

			input_set_असल_params(input_dev, t, v, (x << 1) - v, port->fuzz, w);
			j++;
		पूर्ण

	क्रम (i = j = 0; i < 3; i++)
		अगर (analog->mask & analog_exts[i])
			क्रम (x = 0; x < 2; x++) अणु
				t = analog_hats[j++];
				input_set_असल_params(input_dev, t, -1, 1, 0, 0);
			पूर्ण

	क्रम (i = j = 0; i < 4; i++)
		अगर (analog->mask & (0x10 << i))
			set_bit(analog->buttons[j++], input_dev->keybit);

	अगर (analog->mask & ANALOG_BTNS_CHF)
		क्रम (i = 0; i < 2; i++)
			set_bit(analog->buttons[j++], input_dev->keybit);

	अगर (analog->mask & ANALOG_HBTN_CHF)
		क्रम (i = 0; i < 4; i++)
			set_bit(analog->buttons[j++], input_dev->keybit);

	क्रम (i = 0; i < 4; i++)
		अगर (analog->mask & (ANALOG_BTN_TL << i))
			set_bit(analog_pads[i], input_dev->keybit);

	analog_decode(analog, port->axes, port->initial, port->buttons);

	error = input_रेजिस्टर_device(analog->dev);
	अगर (error) अणु
		input_मुक्त_device(analog->dev);
		वापस error;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * analog_init_devices() sets up device-specअगरic values and रेजिस्टरs the input devices.
 */

अटल पूर्णांक analog_init_masks(काष्ठा analog_port *port)
अणु
	पूर्णांक i;
	काष्ठा analog *analog = port->analog;
	पूर्णांक max[4];

	अगर (!port->mask)
		वापस -1;

	अगर ((port->mask & 3) != 3 && port->mask != 0xc) अणु
		prपूर्णांकk(KERN_WARNING "analog.c: Unknown joystick device found  "
			"(data=%#x, %s), probably not analog joystick.\n",
			port->mask, port->gameport->phys);
		वापस -1;
	पूर्ण


	i = analog_options[0]; /* FIXME !!! - need to specअगरy options क्रम dअगरferent ports */

	analog[0].mask = i & 0xfffff;

	analog[0].mask &= ~(ANALOG_AXES_STD | ANALOG_HAT_FCS | ANALOG_BTNS_GAMEPAD)
			| port->mask | ((port->mask << 8) & ANALOG_HAT_FCS)
			| ((port->mask << 10) & ANALOG_BTNS_TLR) | ((port->mask << 12) & ANALOG_BTNS_TLR2);

	analog[0].mask &= ~(ANALOG_HAT2_CHF)
			| ((analog[0].mask & ANALOG_HBTN_CHF) ? 0 : ANALOG_HAT2_CHF);

	analog[0].mask &= ~(ANALOG_THROTTLE | ANALOG_BTN_TR | ANALOG_BTN_TR2)
			| ((~analog[0].mask & ANALOG_HAT_FCS) >> 8)
			| ((~analog[0].mask & ANALOG_HAT_FCS) << 2)
			| ((~analog[0].mask & ANALOG_HAT_FCS) << 4);

	analog[0].mask &= ~(ANALOG_THROTTLE | ANALOG_RUDDER)
			| (((~analog[0].mask & ANALOG_BTNS_TLR ) >> 10)
			&  ((~analog[0].mask & ANALOG_BTNS_TLR2) >> 12));

	analog[1].mask = ((i >> 20) & 0xff) | ((i >> 12) & 0xf0000);

	analog[1].mask &= (analog[0].mask & ANALOG_EXTENSIONS) ? ANALOG_GAMEPAD
			: (((ANALOG_BTNS_STD | port->mask) & ~analog[0].mask) | ANALOG_GAMEPAD);

	अगर (port->cooked) अणु

		क्रम (i = 0; i < 4; i++) max[i] = port->axes[i] << 1;

		अगर ((analog[0].mask & 0x7) == 0x7) max[2] = (max[0] + max[1]) >> 1;
		अगर ((analog[0].mask & 0xb) == 0xb) max[3] = (max[0] + max[1]) >> 1;
		अगर ((analog[0].mask & ANALOG_BTN_TL) && !(analog[0].mask & ANALOG_BTN_TL2)) max[2] >>= 1;
		अगर ((analog[0].mask & ANALOG_BTN_TR) && !(analog[0].mask & ANALOG_BTN_TR2)) max[3] >>= 1;
		अगर ((analog[0].mask & ANALOG_HAT_FCS)) max[3] >>= 1;

		gameport_calibrate(port->gameport, port->axes, max);
	पूर्ण

	क्रम (i = 0; i < 4; i++)
		port->initial[i] = port->axes[i];

	वापस -!(analog[0].mask || analog[1].mask);
पूर्ण

अटल पूर्णांक analog_init_port(काष्ठा gameport *gameport, काष्ठा gameport_driver *drv, काष्ठा analog_port *port)
अणु
	पूर्णांक i, t, u, v;

	port->gameport = gameport;

	gameport_set_drvdata(gameport, port);

	अगर (!gameport_खोलो(gameport, drv, GAMEPORT_MODE_RAW)) अणु

		analog_calibrate_समयr(port);

		gameport_trigger(gameport);
		t = gameport_पढ़ो(gameport);
		msleep(ANALOG_MAX_TIME);
		port->mask = (gameport_पढ़ो(gameport) ^ t) & t & 0xf;
		port->fuzz = (port->speed * ANALOG_FUZZ_MAGIC) / port->loop / 1000 + ANALOG_FUZZ_BITS;

		क्रम (i = 0; i < ANALOG_INIT_RETRIES; i++) अणु
			अगर (!analog_cooked_पढ़ो(port))
				अवरोध;
			msleep(ANALOG_MAX_TIME);
		पूर्ण

		u = v = 0;

		msleep(ANALOG_MAX_TIME);
		t = gameport_समय(gameport, ANALOG_MAX_TIME * 1000);
		gameport_trigger(gameport);
		जबतक ((gameport_पढ़ो(port->gameport) & port->mask) && (u < t))
			u++;
		udelay(ANALOG_SAITEK_DELAY);
		t = gameport_समय(gameport, ANALOG_SAITEK_TIME);
		gameport_trigger(gameport);
		जबतक ((gameport_पढ़ो(port->gameport) & port->mask) && (v < t))
			v++;

		अगर (v < (u >> 1)) अणु /* FIXME - more than one port */
			analog_options[0] |= /* FIXME - more than one port */
				ANALOG_SAITEK | ANALOG_BTNS_CHF | ANALOG_HBTN_CHF | ANALOG_HAT1_CHF;
			वापस 0;
		पूर्ण

		gameport_बंद(gameport);
	पूर्ण

	अगर (!gameport_खोलो(gameport, drv, GAMEPORT_MODE_COOKED)) अणु

		क्रम (i = 0; i < ANALOG_INIT_RETRIES; i++)
			अगर (!gameport_cooked_पढ़ो(gameport, port->axes, &port->buttons))
				अवरोध;
		क्रम (i = 0; i < 4; i++)
			अगर (port->axes[i] != -1)
				port->mask |= 1 << i;

		port->fuzz = gameport->fuzz;
		port->cooked = 1;
		वापस 0;
	पूर्ण

	वापस gameport_खोलो(gameport, drv, GAMEPORT_MODE_RAW);
पूर्ण

अटल पूर्णांक analog_connect(काष्ठा gameport *gameport, काष्ठा gameport_driver *drv)
अणु
	काष्ठा analog_port *port;
	पूर्णांक i;
	पूर्णांक err;

	अगर (!(port = kzalloc(माप(काष्ठा analog_port), GFP_KERNEL)))
		वापस -ENOMEM;

	err = analog_init_port(gameport, drv, port);
	अगर (err)
		जाओ fail1;

	err = analog_init_masks(port);
	अगर (err)
		जाओ fail2;

	gameport_set_poll_handler(gameport, analog_poll);
	gameport_set_poll_पूर्णांकerval(gameport, 10);

	क्रम (i = 0; i < 2; i++)
		अगर (port->analog[i].mask) अणु
			err = analog_init_device(port, port->analog + i, i);
			अगर (err)
				जाओ fail3;
		पूर्ण

	वापस 0;

 fail3: जबतक (--i >= 0)
		अगर (port->analog[i].mask)
			input_unरेजिस्टर_device(port->analog[i].dev);
 fail2:	gameport_बंद(gameport);
 fail1:	gameport_set_drvdata(gameport, शून्य);
	kमुक्त(port);
	वापस err;
पूर्ण

अटल व्योम analog_disconnect(काष्ठा gameport *gameport)
अणु
	काष्ठा analog_port *port = gameport_get_drvdata(gameport);
	पूर्णांक i;

	क्रम (i = 0; i < 2; i++)
		अगर (port->analog[i].mask)
			input_unरेजिस्टर_device(port->analog[i].dev);
	gameport_बंद(gameport);
	gameport_set_drvdata(gameport, शून्य);
	prपूर्णांकk(KERN_INFO "analog.c: %d out of %d reads (%d%%) on %s failed\n",
		port->bads, port->पढ़ोs, port->पढ़ोs ? (port->bads * 100 / port->पढ़ोs) : 0,
		port->gameport->phys);
	kमुक्त(port);
पूर्ण

काष्ठा analog_types अणु
	अक्षर *name;
	पूर्णांक value;
पूर्ण;

अटल काष्ठा analog_types analog_types[] = अणु
	अणु "none",	0x00000000 पूर्ण,
	अणु "auto",	0x000000ff पूर्ण,
	अणु "2btn",	0x0000003f पूर्ण,
	अणु "y-joy",	0x0cc00033 पूर्ण,
	अणु "y-pad",	0x8cc80033 पूर्ण,
	अणु "fcs",	0x000008f7 पूर्ण,
	अणु "chf",	0x000002ff पूर्ण,
	अणु "fullchf",	0x000007ff पूर्ण,
	अणु "gamepad",	0x000830f3 पूर्ण,
	अणु "gamepad8",	0x0008f0f3 पूर्ण,
	अणु शून्य, 0 पूर्ण
पूर्ण;

अटल व्योम analog_parse_options(व्योम)
अणु
	पूर्णांक i, j;
	अक्षर *end;

	क्रम (i = 0; i < js_nargs; i++) अणु

		क्रम (j = 0; analog_types[j].name; j++)
			अगर (!म_भेद(analog_types[j].name, js[i])) अणु
				analog_options[i] = analog_types[j].value;
				अवरोध;
			पूर्ण
		अगर (analog_types[j].name) जारी;

		analog_options[i] = simple_म_से_अदीर्घ(js[i], &end, 0);
		अगर (end != js[i]) जारी;

		analog_options[i] = 0xff;
		अगर (!म_माप(js[i])) जारी;

		prपूर्णांकk(KERN_WARNING "analog.c: Bad config for port %d - \"%s\"\n", i, js[i]);
	पूर्ण

	क्रम (; i < ANALOG_PORTS; i++)
		analog_options[i] = 0xff;
पूर्ण

/*
 * The gameport device काष्ठाure.
 */

अटल काष्ठा gameport_driver analog_drv = अणु
	.driver		= अणु
		.name	= "analog",
	पूर्ण,
	.description	= DRIVER_DESC,
	.connect	= analog_connect,
	.disconnect	= analog_disconnect,
पूर्ण;

अटल पूर्णांक __init analog_init(व्योम)
अणु
	analog_parse_options();
	वापस gameport_रेजिस्टर_driver(&analog_drv);
पूर्ण

अटल व्योम __निकास analog_निकास(व्योम)
अणु
	gameport_unरेजिस्टर_driver(&analog_drv);
पूर्ण

module_init(analog_init);
module_निकास(analog_निकास);
