<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * NES, SNES, N64, MultiSystem, PSX gamepad driver क्रम Linux
 *
 *  Copyright (c) 1999-2004	Vojtech Pavlik <vojtech@suse.cz>
 *  Copyright (c) 2004		Peter Nelson <rufus-kernel@hackish.org>
 *
 *  Based on the work of:
 *	Andree Borrmann		John Dahlstrom
 *	David Kuder		Nathan Hand
 *	Raphael Assenat
 */

/*
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/delay.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/parport.h>
#समावेश <linux/input.h>
#समावेश <linux/mutex.h>
#समावेश <linux/slab.h>

MODULE_AUTHOR("Vojtech Pavlik <vojtech@ucw.cz>");
MODULE_DESCRIPTION("NES, SNES, N64, MultiSystem, PSX gamepad driver");
MODULE_LICENSE("GPL");

#घोषणा GC_MAX_PORTS		3
#घोषणा GC_MAX_DEVICES		5

काष्ठा gc_config अणु
	पूर्णांक args[GC_MAX_DEVICES + 1];
	अचिन्हित पूर्णांक nargs;
पूर्ण;

अटल काष्ठा gc_config gc_cfg[GC_MAX_PORTS];

module_param_array_named(map, gc_cfg[0].args, पूर्णांक, &gc_cfg[0].nargs, 0);
MODULE_PARM_DESC(map, "Describes first set of devices (<parport#>,<pad1>,<pad2>,..<pad5>)");
module_param_array_named(map2, gc_cfg[1].args, पूर्णांक, &gc_cfg[1].nargs, 0);
MODULE_PARM_DESC(map2, "Describes second set of devices");
module_param_array_named(map3, gc_cfg[2].args, पूर्णांक, &gc_cfg[2].nargs, 0);
MODULE_PARM_DESC(map3, "Describes third set of devices");

/* see also gs_psx_delay parameter in PSX support section */

क्रमागत gc_type अणु
	GC_NONE = 0,
	GC_SNES,
	GC_NES,
	GC_NES4,
	GC_MULTI,
	GC_MULTI2,
	GC_N64,
	GC_PSX,
	GC_DDR,
	GC_SNESMOUSE,
	GC_MAX
पूर्ण;

#घोषणा GC_REFRESH_TIME	HZ/100

काष्ठा gc_pad अणु
	काष्ठा input_dev *dev;
	क्रमागत gc_type type;
	अक्षर phys[32];
पूर्ण;

काष्ठा gc अणु
	काष्ठा pardevice *pd;
	काष्ठा gc_pad pads[GC_MAX_DEVICES];
	काष्ठा समयr_list समयr;
	पूर्णांक pad_count[GC_MAX];
	पूर्णांक used;
	पूर्णांक parportno;
	काष्ठा mutex mutex;
पूर्ण;

काष्ठा gc_subdev अणु
	अचिन्हित पूर्णांक idx;
पूर्ण;

अटल काष्ठा gc *gc_base[3];

अटल स्थिर पूर्णांक gc_status_bit[] = अणु 0x40, 0x80, 0x20, 0x10, 0x08 पूर्ण;

अटल स्थिर अक्षर *gc_names[] = अणु
	शून्य, "SNES pad", "NES pad", "NES FourPort", "Multisystem joystick",
	"Multisystem 2-button joystick", "N64 controller", "PSX controller",
	"PSX DDR controller", "SNES mouse"
पूर्ण;

/*
 * N64 support.
 */

अटल स्थिर अचिन्हित अक्षर gc_n64_bytes[] = अणु 0, 1, 13, 15, 14, 12, 10, 11, 2, 3 पूर्ण;
अटल स्थिर लघु gc_n64_btn[] = अणु
	BTN_A, BTN_B, BTN_C, BTN_X, BTN_Y, BTN_Z,
	BTN_TL, BTN_TR, BTN_TRIGGER, BTN_START
पूर्ण;

#घोषणा GC_N64_LENGTH		32		/* N64 bit length, not including stop bit */
#घोषणा GC_N64_STOP_LENGTH	5		/* Length of encoded stop bit */
#घोषणा GC_N64_CMD_00		0x11111111UL
#घोषणा GC_N64_CMD_01		0xd1111111UL
#घोषणा GC_N64_CMD_03		0xdd111111UL
#घोषणा GC_N64_CMD_1b		0xdd1dd111UL
#घोषणा GC_N64_CMD_c0		0x111111ddUL
#घोषणा GC_N64_CMD_80		0x1111111dUL
#घोषणा GC_N64_STOP_BIT		0x1d		/* Encoded stop bit */
#घोषणा GC_N64_REQUEST_DATA	GC_N64_CMD_01	/* the request data command */
#घोषणा GC_N64_DELAY		133		/* delay between transmit request, and response पढ़ोy (us) */
#घोषणा GC_N64_DWS		3		/* delay between ग_लिखो segments (required क्रम sound playback because of ISA DMA) */
						/* GC_N64_DWS > 24 is known to fail */
#घोषणा GC_N64_POWER_W		0xe2		/* घातer during ग_लिखो (transmit request) */
#घोषणा GC_N64_POWER_R		0xfd		/* घातer during पढ़ो */
#घोषणा GC_N64_OUT		0x1d		/* output bits to the 4 pads */
						/* Reading the मुख्य axes of any N64 pad is known to fail अगर the corresponding bit */
						/* in GC_N64_OUT is pulled low on the output port (by any routine) क्रम more */
						/* than 123 us */
#घोषणा GC_N64_CLOCK		0x02		/* घड़ी bits क्रम पढ़ो */

/*
 * Used क्रम rumble code.
 */

/* Send encoded command */
अटल व्योम gc_n64_send_command(काष्ठा gc *gc, अचिन्हित दीर्घ cmd,
				अचिन्हित अक्षर target)
अणु
	काष्ठा parport *port = gc->pd->port;
	पूर्णांक i;

	क्रम (i = 0; i < GC_N64_LENGTH; i++) अणु
		अचिन्हित अक्षर data = (cmd >> i) & 1 ? target : 0;
		parport_ग_लिखो_data(port, GC_N64_POWER_W | data);
		udelay(GC_N64_DWS);
	पूर्ण
पूर्ण

/* Send stop bit */
अटल व्योम gc_n64_send_stop_bit(काष्ठा gc *gc, अचिन्हित अक्षर target)
अणु
	काष्ठा parport *port = gc->pd->port;
	पूर्णांक i;

	क्रम (i = 0; i < GC_N64_STOP_LENGTH; i++) अणु
		अचिन्हित अक्षर data = (GC_N64_STOP_BIT >> i) & 1 ? target : 0;
		parport_ग_लिखो_data(port, GC_N64_POWER_W | data);
		udelay(GC_N64_DWS);
	पूर्ण
पूर्ण

/*
 * gc_n64_पढ़ो_packet() पढ़ोs an N64 packet.
 * Each pad uses one bit per byte. So all pads connected to this port
 * are पढ़ो in parallel.
 */

अटल व्योम gc_n64_पढ़ो_packet(काष्ठा gc *gc, अचिन्हित अक्षर *data)
अणु
	पूर्णांक i;
	अचिन्हित दीर्घ flags;

/*
 * Request the pad to transmit data
 */

	local_irq_save(flags);
	gc_n64_send_command(gc, GC_N64_REQUEST_DATA, GC_N64_OUT);
	gc_n64_send_stop_bit(gc, GC_N64_OUT);
	local_irq_restore(flags);

/*
 * Wait क्रम the pad response to be loaded पूर्णांकo the 33-bit रेजिस्टर
 * of the adapter.
 */

	udelay(GC_N64_DELAY);

/*
 * Grab data (ignoring the last bit, which is a stop bit)
 */

	क्रम (i = 0; i < GC_N64_LENGTH; i++) अणु
		parport_ग_लिखो_data(gc->pd->port, GC_N64_POWER_R);
		udelay(2);
		data[i] = parport_पढ़ो_status(gc->pd->port);
		parport_ग_लिखो_data(gc->pd->port, GC_N64_POWER_R | GC_N64_CLOCK);
	 पूर्ण

/*
 * We must रुको 200 ms here क्रम the controller to reinitialize beक्रमe
 * the next पढ़ो request. No worries as दीर्घ as gc_पढ़ो is polled less
 * frequently than this.
 */

पूर्ण

अटल व्योम gc_n64_process_packet(काष्ठा gc *gc)
अणु
	अचिन्हित अक्षर data[GC_N64_LENGTH];
	काष्ठा input_dev *dev;
	पूर्णांक i, j, s;
	चिन्हित अक्षर x, y;

	gc_n64_पढ़ो_packet(gc, data);

	क्रम (i = 0; i < GC_MAX_DEVICES; i++) अणु

		अगर (gc->pads[i].type != GC_N64)
			जारी;

		dev = gc->pads[i].dev;
		s = gc_status_bit[i];

		अगर (s & ~(data[8] | data[9])) अणु

			x = y = 0;

			क्रम (j = 0; j < 8; j++) अणु
				अगर (data[23 - j] & s)
					x |= 1 << j;
				अगर (data[31 - j] & s)
					y |= 1 << j;
			पूर्ण

			input_report_असल(dev, ABS_X,  x);
			input_report_असल(dev, ABS_Y, -y);

			input_report_असल(dev, ABS_HAT0X,
					 !(s & data[6]) - !(s & data[7]));
			input_report_असल(dev, ABS_HAT0Y,
					 !(s & data[4]) - !(s & data[5]));

			क्रम (j = 0; j < 10; j++)
				input_report_key(dev, gc_n64_btn[j],
						 s & data[gc_n64_bytes[j]]);

			input_sync(dev);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक gc_n64_play_effect(काष्ठा input_dev *dev, व्योम *data,
			      काष्ठा ff_effect *effect)
अणु
	पूर्णांक i;
	अचिन्हित दीर्घ flags;
	काष्ठा gc *gc = input_get_drvdata(dev);
	काष्ठा gc_subdev *sdev = data;
	अचिन्हित अक्षर target = 1 << sdev->idx; /* select desired pin */

	अगर (effect->type == FF_RUMBLE) अणु
		काष्ठा ff_rumble_effect *rumble = &effect->u.rumble;
		अचिन्हित पूर्णांक cmd =
			rumble->strong_magnitude || rumble->weak_magnitude ?
			GC_N64_CMD_01 : GC_N64_CMD_00;

		local_irq_save(flags);

		/* Init Rumble - 0x03, 0x80, 0x01, (34)0x80 */
		gc_n64_send_command(gc, GC_N64_CMD_03, target);
		gc_n64_send_command(gc, GC_N64_CMD_80, target);
		gc_n64_send_command(gc, GC_N64_CMD_01, target);
		क्रम (i = 0; i < 32; i++)
			gc_n64_send_command(gc, GC_N64_CMD_80, target);
		gc_n64_send_stop_bit(gc, target);

		udelay(GC_N64_DELAY);

		/* Now start or stop it - 0x03, 0xc0, 0zx1b, (32)0x01/0x00 */
		gc_n64_send_command(gc, GC_N64_CMD_03, target);
		gc_n64_send_command(gc, GC_N64_CMD_c0, target);
		gc_n64_send_command(gc, GC_N64_CMD_1b, target);
		क्रम (i = 0; i < 32; i++)
			gc_n64_send_command(gc, cmd, target);
		gc_n64_send_stop_bit(gc, target);

		local_irq_restore(flags);

	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक gc_n64_init_ff(काष्ठा input_dev *dev, पूर्णांक i)
अणु
	काष्ठा gc_subdev *sdev;
	पूर्णांक err;

	sdev = kदो_स्मृति(माप(*sdev), GFP_KERNEL);
	अगर (!sdev)
		वापस -ENOMEM;

	sdev->idx = i;

	input_set_capability(dev, EV_FF, FF_RUMBLE);

	err = input_ff_create_memless(dev, sdev, gc_n64_play_effect);
	अगर (err) अणु
		kमुक्त(sdev);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * NES/SNES support.
 */

#घोषणा GC_NES_DELAY		6	/* Delay between bits - 6us */
#घोषणा GC_NES_LENGTH		8	/* The NES pads use 8 bits of data */
#घोषणा GC_SNES_LENGTH		12	/* The SNES true length is 16, but the
					   last 4 bits are unused */
#घोषणा GC_SNESMOUSE_LENGTH	32	/* The SNES mouse uses 32 bits, the first
					   16 bits are equivalent to a gamepad */

#घोषणा GC_NES_POWER	0xfc
#घोषणा GC_NES_CLOCK	0x01
#घोषणा GC_NES_LATCH	0x02

अटल स्थिर अचिन्हित अक्षर gc_nes_bytes[] = अणु 0, 1, 2, 3 पूर्ण;
अटल स्थिर अचिन्हित अक्षर gc_snes_bytes[] = अणु 8, 0, 2, 3, 9, 1, 10, 11 पूर्ण;
अटल स्थिर लघु gc_snes_btn[] = अणु
	BTN_A, BTN_B, BTN_SELECT, BTN_START, BTN_X, BTN_Y, BTN_TL, BTN_TR
पूर्ण;

/*
 * gc_nes_पढ़ो_packet() पढ़ोs a NES/SNES packet.
 * Each pad uses one bit per byte. So all pads connected to
 * this port are पढ़ो in parallel.
 */

अटल व्योम gc_nes_पढ़ो_packet(काष्ठा gc *gc, पूर्णांक length, अचिन्हित अक्षर *data)
अणु
	पूर्णांक i;

	parport_ग_लिखो_data(gc->pd->port, GC_NES_POWER | GC_NES_CLOCK | GC_NES_LATCH);
	udelay(GC_NES_DELAY * 2);
	parport_ग_लिखो_data(gc->pd->port, GC_NES_POWER | GC_NES_CLOCK);

	क्रम (i = 0; i < length; i++) अणु
		udelay(GC_NES_DELAY);
		parport_ग_लिखो_data(gc->pd->port, GC_NES_POWER);
		data[i] = parport_पढ़ो_status(gc->pd->port) ^ 0x7f;
		udelay(GC_NES_DELAY);
		parport_ग_लिखो_data(gc->pd->port, GC_NES_POWER | GC_NES_CLOCK);
	पूर्ण
पूर्ण

अटल व्योम gc_nes_process_packet(काष्ठा gc *gc)
अणु
	अचिन्हित अक्षर data[GC_SNESMOUSE_LENGTH];
	काष्ठा gc_pad *pad;
	काष्ठा input_dev *dev;
	पूर्णांक i, j, s, len;
	अक्षर x_rel, y_rel;

	len = gc->pad_count[GC_SNESMOUSE] ? GC_SNESMOUSE_LENGTH :
			(gc->pad_count[GC_SNES] ? GC_SNES_LENGTH : GC_NES_LENGTH);

	gc_nes_पढ़ो_packet(gc, len, data);

	क्रम (i = 0; i < GC_MAX_DEVICES; i++) अणु

		pad = &gc->pads[i];
		dev = pad->dev;
		s = gc_status_bit[i];

		चयन (pad->type) अणु

		हाल GC_NES:

			input_report_असल(dev, ABS_X, !(s & data[6]) - !(s & data[7]));
			input_report_असल(dev, ABS_Y, !(s & data[4]) - !(s & data[5]));

			क्रम (j = 0; j < 4; j++)
				input_report_key(dev, gc_snes_btn[j],
						 s & data[gc_nes_bytes[j]]);
			input_sync(dev);
			अवरोध;

		हाल GC_SNES:

			input_report_असल(dev, ABS_X, !(s & data[6]) - !(s & data[7]));
			input_report_असल(dev, ABS_Y, !(s & data[4]) - !(s & data[5]));

			क्रम (j = 0; j < 8; j++)
				input_report_key(dev, gc_snes_btn[j],
						 s & data[gc_snes_bytes[j]]);
			input_sync(dev);
			अवरोध;

		हाल GC_SNESMOUSE:
			/*
			 * The 4 unused bits from SNES controllers appear
			 * to be ID bits so use them to make sure we are
			 * dealing with a mouse.
			 * gamepad is connected. This is important since
			 * my SNES gamepad sends 1's क्रम bits 16-31, which
			 * cause the mouse poपूर्णांकer to quickly move to the
			 * upper left corner of the screen.
			 */
			अगर (!(s & data[12]) && !(s & data[13]) &&
			    !(s & data[14]) && (s & data[15])) अणु
				input_report_key(dev, BTN_LEFT, s & data[9]);
				input_report_key(dev, BTN_RIGHT, s & data[8]);

				x_rel = y_rel = 0;
				क्रम (j = 0; j < 7; j++) अणु
					x_rel <<= 1;
					अगर (data[25 + j] & s)
						x_rel |= 1;

					y_rel <<= 1;
					अगर (data[17 + j] & s)
						y_rel |= 1;
				पूर्ण

				अगर (x_rel) अणु
					अगर (data[24] & s)
						x_rel = -x_rel;
					input_report_rel(dev, REL_X, x_rel);
				पूर्ण

				अगर (y_rel) अणु
					अगर (data[16] & s)
						y_rel = -y_rel;
					input_report_rel(dev, REL_Y, y_rel);
				पूर्ण

				input_sync(dev);
			पूर्ण
			अवरोध;

		शेष:
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

/*
 * Multiप्रणाली joystick support
 */

#घोषणा GC_MULTI_LENGTH		5	/* Multi प्रणाली joystick packet length is 5 */
#घोषणा GC_MULTI2_LENGTH	6	/* One more bit क्रम one more button */

/*
 * gc_multi_पढ़ो_packet() पढ़ोs a Multiप्रणाली joystick packet.
 */

अटल व्योम gc_multi_पढ़ो_packet(काष्ठा gc *gc, पूर्णांक length, अचिन्हित अक्षर *data)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < length; i++) अणु
		parport_ग_लिखो_data(gc->pd->port, ~(1 << i));
		data[i] = parport_पढ़ो_status(gc->pd->port) ^ 0x7f;
	पूर्ण
पूर्ण

अटल व्योम gc_multi_process_packet(काष्ठा gc *gc)
अणु
	अचिन्हित अक्षर data[GC_MULTI2_LENGTH];
	पूर्णांक data_len = gc->pad_count[GC_MULTI2] ? GC_MULTI2_LENGTH : GC_MULTI_LENGTH;
	काष्ठा gc_pad *pad;
	काष्ठा input_dev *dev;
	पूर्णांक i, s;

	gc_multi_पढ़ो_packet(gc, data_len, data);

	क्रम (i = 0; i < GC_MAX_DEVICES; i++) अणु
		pad = &gc->pads[i];
		dev = pad->dev;
		s = gc_status_bit[i];

		चयन (pad->type) अणु
		हाल GC_MULTI2:
			input_report_key(dev, BTN_THUMB, s & data[5]);
			fallthrough;

		हाल GC_MULTI:
			input_report_असल(dev, ABS_X,
					 !(s & data[2]) - !(s & data[3]));
			input_report_असल(dev, ABS_Y,
					 !(s & data[0]) - !(s & data[1]));
			input_report_key(dev, BTN_TRIGGER, s & data[4]);
			input_sync(dev);
			अवरोध;

		शेष:
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

/*
 * PSX support
 *
 * See करोcumentation at:
 *	http://www.geocities.co.jp/Playtown/2004/psx/ps_eng.txt	
 *	http://www.gamesx.com/controldata/psxcont/psxcont.hपंचांग
 *
 */

#घोषणा GC_PSX_DELAY	25		/* 25 usec */
#घोषणा GC_PSX_LENGTH	8		/* talk to the controller in bits */
#घोषणा GC_PSX_BYTES	6		/* the maximum number of bytes to पढ़ो off the controller */

#घोषणा GC_PSX_MOUSE	1		/* Mouse */
#घोषणा GC_PSX_NEGCON	2		/* NegCon */
#घोषणा GC_PSX_NORMAL	4		/* Digital / Analog or Rumble in Digital mode  */
#घोषणा GC_PSX_ANALOG	5		/* Analog in Analog mode / Rumble in Green mode */
#घोषणा GC_PSX_RUMBLE	7		/* Rumble in Red mode */

#घोषणा GC_PSX_CLOCK	0x04		/* Pin 4 */
#घोषणा GC_PSX_COMMAND	0x01		/* Pin 2 */
#घोषणा GC_PSX_POWER	0xf8		/* Pins 5-9 */
#घोषणा GC_PSX_SELECT	0x02		/* Pin 3 */

#घोषणा GC_PSX_ID(x)	((x) >> 4)	/* High nibble is device type */
#घोषणा GC_PSX_LEN(x)	(((x) & 0xf) << 1)	/* Low nibble is length in bytes/2 */

अटल पूर्णांक gc_psx_delay = GC_PSX_DELAY;
module_param_named(psx_delay, gc_psx_delay, uपूर्णांक, 0);
MODULE_PARM_DESC(psx_delay, "Delay when accessing Sony PSX controller (usecs)");

अटल स्थिर लघु gc_psx_असल[] = अणु
	ABS_X, ABS_Y, ABS_RX, ABS_RY, ABS_HAT0X, ABS_HAT0Y
पूर्ण;
अटल स्थिर लघु gc_psx_btn[] = अणु
	BTN_TL, BTN_TR, BTN_TL2, BTN_TR2, BTN_A, BTN_B, BTN_X, BTN_Y,
	BTN_START, BTN_SELECT, BTN_THUMBL, BTN_THUMBR
पूर्ण;
अटल स्थिर लघु gc_psx_ddr_btn[] = अणु BTN_0, BTN_1, BTN_2, BTN_3 पूर्ण;

/*
 * gc_psx_command() ग_लिखोs 8bit command and पढ़ोs 8bit data from
 * the psx pad.
 */

अटल व्योम gc_psx_command(काष्ठा gc *gc, पूर्णांक b, अचिन्हित अक्षर *data)
अणु
	काष्ठा parport *port = gc->pd->port;
	पूर्णांक i, j, cmd, पढ़ो;

	स_रखो(data, 0, GC_MAX_DEVICES);

	क्रम (i = 0; i < GC_PSX_LENGTH; i++, b >>= 1) अणु
		cmd = (b & 1) ? GC_PSX_COMMAND : 0;
		parport_ग_लिखो_data(port, cmd | GC_PSX_POWER);
		udelay(gc_psx_delay);

		पढ़ो = parport_पढ़ो_status(port) ^ 0x80;

		क्रम (j = 0; j < GC_MAX_DEVICES; j++) अणु
			काष्ठा gc_pad *pad = &gc->pads[j];

			अगर (pad->type == GC_PSX || pad->type == GC_DDR)
				data[j] |= (पढ़ो & gc_status_bit[j]) ? (1 << i) : 0;
		पूर्ण

		parport_ग_लिखो_data(gc->pd->port, cmd | GC_PSX_CLOCK | GC_PSX_POWER);
		udelay(gc_psx_delay);
	पूर्ण
पूर्ण

/*
 * gc_psx_पढ़ो_packet() पढ़ोs a whole psx packet and वापसs
 * device identअगरier code.
 */

अटल व्योम gc_psx_पढ़ो_packet(काष्ठा gc *gc,
			       अचिन्हित अक्षर data[GC_MAX_DEVICES][GC_PSX_BYTES],
			       अचिन्हित अक्षर id[GC_MAX_DEVICES])
अणु
	पूर्णांक i, j, max_len = 0;
	अचिन्हित दीर्घ flags;
	अचिन्हित अक्षर data2[GC_MAX_DEVICES];

	/* Select pad */
	parport_ग_लिखो_data(gc->pd->port, GC_PSX_CLOCK | GC_PSX_SELECT | GC_PSX_POWER);
	udelay(gc_psx_delay);
	/* Deselect, begin command */
	parport_ग_लिखो_data(gc->pd->port, GC_PSX_CLOCK | GC_PSX_POWER);
	udelay(gc_psx_delay);

	local_irq_save(flags);

	gc_psx_command(gc, 0x01, data2);	/* Access pad */
	gc_psx_command(gc, 0x42, id);		/* Get device ids */
	gc_psx_command(gc, 0, data2);		/* Dump status */

	/* Find the दीर्घest pad */
	क्रम (i = 0; i < GC_MAX_DEVICES; i++) अणु
		काष्ठा gc_pad *pad = &gc->pads[i];

		अगर ((pad->type == GC_PSX || pad->type == GC_DDR) &&
		    GC_PSX_LEN(id[i]) > max_len &&
		    GC_PSX_LEN(id[i]) <= GC_PSX_BYTES) अणु
			max_len = GC_PSX_LEN(id[i]);
		पूर्ण
	पूर्ण

	/* Read in all the data */
	क्रम (i = 0; i < max_len; i++) अणु
		gc_psx_command(gc, 0, data2);
		क्रम (j = 0; j < GC_MAX_DEVICES; j++)
			data[j][i] = data2[j];
	पूर्ण

	local_irq_restore(flags);

	parport_ग_लिखो_data(gc->pd->port, GC_PSX_CLOCK | GC_PSX_SELECT | GC_PSX_POWER);

	/* Set id's to the real value */
	क्रम (i = 0; i < GC_MAX_DEVICES; i++)
		id[i] = GC_PSX_ID(id[i]);
पूर्ण

अटल व्योम gc_psx_report_one(काष्ठा gc_pad *pad, अचिन्हित अक्षर psx_type,
			      अचिन्हित अक्षर *data)
अणु
	काष्ठा input_dev *dev = pad->dev;
	पूर्णांक i;

	चयन (psx_type) अणु

	हाल GC_PSX_RUMBLE:

		input_report_key(dev, BTN_THUMBL, ~data[0] & 0x04);
		input_report_key(dev, BTN_THUMBR, ~data[0] & 0x02);
		fallthrough;

	हाल GC_PSX_NEGCON:
	हाल GC_PSX_ANALOG:

		अगर (pad->type == GC_DDR) अणु
			क्रम (i = 0; i < 4; i++)
				input_report_key(dev, gc_psx_ddr_btn[i],
						 ~data[0] & (0x10 << i));
		पूर्ण अन्यथा अणु
			क्रम (i = 0; i < 4; i++)
				input_report_असल(dev, gc_psx_असल[i + 2],
						 data[i + 2]);

			input_report_असल(dev, ABS_X,
				!!(data[0] & 0x80) * 128 + !(data[0] & 0x20) * 127);
			input_report_असल(dev, ABS_Y,
				!!(data[0] & 0x10) * 128 + !(data[0] & 0x40) * 127);
		पूर्ण

		क्रम (i = 0; i < 8; i++)
			input_report_key(dev, gc_psx_btn[i], ~data[1] & (1 << i));

		input_report_key(dev, BTN_START,  ~data[0] & 0x08);
		input_report_key(dev, BTN_SELECT, ~data[0] & 0x01);

		input_sync(dev);

		अवरोध;

	हाल GC_PSX_NORMAL:

		अगर (pad->type == GC_DDR) अणु
			क्रम (i = 0; i < 4; i++)
				input_report_key(dev, gc_psx_ddr_btn[i],
						 ~data[0] & (0x10 << i));
		पूर्ण अन्यथा अणु
			input_report_असल(dev, ABS_X,
				!!(data[0] & 0x80) * 128 + !(data[0] & 0x20) * 127);
			input_report_असल(dev, ABS_Y,
				!!(data[0] & 0x10) * 128 + !(data[0] & 0x40) * 127);

			/*
			 * For some reason अगर the extra axes are left unset
			 * they drअगरt.
			 * क्रम (i = 0; i < 4; i++)
				input_report_असल(dev, gc_psx_असल[i + 2], 128);
			 * This needs to be debugged properly,
			 * maybe fuzz processing needs to be करोne
			 * in input_sync()
			 *				 --vojtech
			 */
		पूर्ण

		क्रम (i = 0; i < 8; i++)
			input_report_key(dev, gc_psx_btn[i], ~data[1] & (1 << i));

		input_report_key(dev, BTN_START,  ~data[0] & 0x08);
		input_report_key(dev, BTN_SELECT, ~data[0] & 0x01);

		input_sync(dev);

		अवरोध;

	शेष: /* not a pad, ignore */
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम gc_psx_process_packet(काष्ठा gc *gc)
अणु
	अचिन्हित अक्षर data[GC_MAX_DEVICES][GC_PSX_BYTES];
	अचिन्हित अक्षर id[GC_MAX_DEVICES];
	काष्ठा gc_pad *pad;
	पूर्णांक i;

	gc_psx_पढ़ो_packet(gc, data, id);

	क्रम (i = 0; i < GC_MAX_DEVICES; i++) अणु
		pad = &gc->pads[i];
		अगर (pad->type == GC_PSX || pad->type == GC_DDR)
			gc_psx_report_one(pad, id[i], data[i]);
	पूर्ण
पूर्ण

/*
 * gc_समयr() initiates पढ़ोs of console pads data.
 */

अटल व्योम gc_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा gc *gc = from_समयr(gc, t, समयr);

/*
 * N64 pads - must be पढ़ो first, any पढ़ो confuses them क्रम 200 us
 */

	अगर (gc->pad_count[GC_N64])
		gc_n64_process_packet(gc);

/*
 * NES and SNES pads or mouse
 */

	अगर (gc->pad_count[GC_NES] ||
	    gc->pad_count[GC_SNES] ||
	    gc->pad_count[GC_SNESMOUSE]) अणु
		gc_nes_process_packet(gc);
	पूर्ण

/*
 * Multi and Multi2 joysticks
 */

	अगर (gc->pad_count[GC_MULTI] || gc->pad_count[GC_MULTI2])
		gc_multi_process_packet(gc);

/*
 * PSX controllers
 */

	अगर (gc->pad_count[GC_PSX] || gc->pad_count[GC_DDR])
		gc_psx_process_packet(gc);

	mod_समयr(&gc->समयr, jअगरfies + GC_REFRESH_TIME);
पूर्ण

अटल पूर्णांक gc_खोलो(काष्ठा input_dev *dev)
अणु
	काष्ठा gc *gc = input_get_drvdata(dev);
	पूर्णांक err;

	err = mutex_lock_पूर्णांकerruptible(&gc->mutex);
	अगर (err)
		वापस err;

	अगर (!gc->used++) अणु
		parport_claim(gc->pd);
		parport_ग_लिखो_control(gc->pd->port, 0x04);
		mod_समयr(&gc->समयr, jअगरfies + GC_REFRESH_TIME);
	पूर्ण

	mutex_unlock(&gc->mutex);
	वापस 0;
पूर्ण

अटल व्योम gc_बंद(काष्ठा input_dev *dev)
अणु
	काष्ठा gc *gc = input_get_drvdata(dev);

	mutex_lock(&gc->mutex);
	अगर (!--gc->used) अणु
		del_समयr_sync(&gc->समयr);
		parport_ग_लिखो_control(gc->pd->port, 0x00);
		parport_release(gc->pd);
	पूर्ण
	mutex_unlock(&gc->mutex);
पूर्ण

अटल पूर्णांक gc_setup_pad(काष्ठा gc *gc, पूर्णांक idx, पूर्णांक pad_type)
अणु
	काष्ठा gc_pad *pad = &gc->pads[idx];
	काष्ठा input_dev *input_dev;
	पूर्णांक i;
	पूर्णांक err;

	अगर (pad_type < 1 || pad_type >= GC_MAX) अणु
		pr_err("Pad type %d unknown\n", pad_type);
		वापस -EINVAL;
	पूर्ण

	pad->dev = input_dev = input_allocate_device();
	अगर (!input_dev) अणु
		pr_err("Not enough memory for input device\n");
		वापस -ENOMEM;
	पूर्ण

	pad->type = pad_type;

	snम_लिखो(pad->phys, माप(pad->phys),
		 "%s/input%d", gc->pd->port->name, idx);

	input_dev->name = gc_names[pad_type];
	input_dev->phys = pad->phys;
	input_dev->id.bustype = BUS_PARPORT;
	input_dev->id.venकरोr = 0x0001;
	input_dev->id.product = pad_type;
	input_dev->id.version = 0x0100;

	input_set_drvdata(input_dev, gc);

	input_dev->खोलो = gc_खोलो;
	input_dev->बंद = gc_बंद;

	अगर (pad_type != GC_SNESMOUSE) अणु
		input_dev->evbit[0] = BIT_MASK(EV_KEY) | BIT_MASK(EV_ABS);

		क्रम (i = 0; i < 2; i++)
			input_set_असल_params(input_dev, ABS_X + i, -1, 1, 0, 0);
	पूर्ण अन्यथा
		input_dev->evbit[0] = BIT_MASK(EV_KEY) | BIT_MASK(EV_REL);

	gc->pad_count[pad_type]++;

	चयन (pad_type) अणु

	हाल GC_N64:
		क्रम (i = 0; i < 10; i++)
			input_set_capability(input_dev, EV_KEY, gc_n64_btn[i]);

		क्रम (i = 0; i < 2; i++) अणु
			input_set_असल_params(input_dev, ABS_X + i, -127, 126, 0, 2);
			input_set_असल_params(input_dev, ABS_HAT0X + i, -1, 1, 0, 0);
		पूर्ण

		err = gc_n64_init_ff(input_dev, idx);
		अगर (err) अणु
			pr_warn("Failed to initiate rumble for N64 device %d\n",
				idx);
			जाओ err_मुक्त_dev;
		पूर्ण

		अवरोध;

	हाल GC_SNESMOUSE:
		input_set_capability(input_dev, EV_KEY, BTN_LEFT);
		input_set_capability(input_dev, EV_KEY, BTN_RIGHT);
		input_set_capability(input_dev, EV_REL, REL_X);
		input_set_capability(input_dev, EV_REL, REL_Y);
		अवरोध;

	हाल GC_SNES:
		क्रम (i = 4; i < 8; i++)
			input_set_capability(input_dev, EV_KEY, gc_snes_btn[i]);
		fallthrough;

	हाल GC_NES:
		क्रम (i = 0; i < 4; i++)
			input_set_capability(input_dev, EV_KEY, gc_snes_btn[i]);
		अवरोध;

	हाल GC_MULTI2:
		input_set_capability(input_dev, EV_KEY, BTN_THUMB);
		fallthrough;

	हाल GC_MULTI:
		input_set_capability(input_dev, EV_KEY, BTN_TRIGGER);
		अवरोध;

	हाल GC_PSX:
		क्रम (i = 0; i < 6; i++)
			input_set_असल_params(input_dev,
					     gc_psx_असल[i], 4, 252, 0, 2);
		क्रम (i = 0; i < 12; i++)
			input_set_capability(input_dev, EV_KEY, gc_psx_btn[i]);
		अवरोध;

		अवरोध;

	हाल GC_DDR:
		क्रम (i = 0; i < 4; i++)
			input_set_capability(input_dev, EV_KEY,
					     gc_psx_ddr_btn[i]);
		क्रम (i = 0; i < 12; i++)
			input_set_capability(input_dev, EV_KEY, gc_psx_btn[i]);

		अवरोध;
	पूर्ण

	err = input_रेजिस्टर_device(pad->dev);
	अगर (err)
		जाओ err_मुक्त_dev;

	वापस 0;

err_मुक्त_dev:
	input_मुक्त_device(pad->dev);
	pad->dev = शून्य;
	वापस err;
पूर्ण

अटल व्योम gc_attach(काष्ठा parport *pp)
अणु
	काष्ठा gc *gc;
	काष्ठा pardevice *pd;
	पूर्णांक i, port_idx;
	पूर्णांक count = 0;
	पूर्णांक *pads, n_pads;
	काष्ठा pardev_cb gc_parport_cb;

	क्रम (port_idx = 0; port_idx < GC_MAX_PORTS; port_idx++) अणु
		अगर (gc_cfg[port_idx].nargs == 0 || gc_cfg[port_idx].args[0] < 0)
			जारी;

		अगर (gc_cfg[port_idx].args[0] == pp->number)
			अवरोध;
	पूर्ण

	अगर (port_idx == GC_MAX_PORTS) अणु
		pr_debug("Not using parport%d.\n", pp->number);
		वापस;
	पूर्ण
	pads = gc_cfg[port_idx].args + 1;
	n_pads = gc_cfg[port_idx].nargs - 1;

	स_रखो(&gc_parport_cb, 0, माप(gc_parport_cb));
	gc_parport_cb.flags = PARPORT_FLAG_EXCL;

	pd = parport_रेजिस्टर_dev_model(pp, "gamecon", &gc_parport_cb,
					port_idx);
	अगर (!pd) अणु
		pr_err("parport busy already - lp.o loaded?\n");
		वापस;
	पूर्ण

	gc = kzalloc(माप(काष्ठा gc), GFP_KERNEL);
	अगर (!gc) अणु
		pr_err("Not enough memory\n");
		जाओ err_unreg_pardev;
	पूर्ण

	mutex_init(&gc->mutex);
	gc->pd = pd;
	gc->parportno = pp->number;
	समयr_setup(&gc->समयr, gc_समयr, 0);

	क्रम (i = 0; i < n_pads && i < GC_MAX_DEVICES; i++) अणु
		अगर (!pads[i])
			जारी;

		अगर (gc_setup_pad(gc, i, pads[i]))
			जाओ err_unreg_devs;

		count++;
	पूर्ण

	अगर (count == 0) अणु
		pr_err("No valid devices specified\n");
		जाओ err_मुक्त_gc;
	पूर्ण

	gc_base[port_idx] = gc;
	वापस;

 err_unreg_devs:
	जबतक (--i >= 0)
		अगर (gc->pads[i].dev)
			input_unरेजिस्टर_device(gc->pads[i].dev);
 err_मुक्त_gc:
	kमुक्त(gc);
 err_unreg_pardev:
	parport_unरेजिस्टर_device(pd);
पूर्ण

अटल व्योम gc_detach(काष्ठा parport *port)
अणु
	पूर्णांक i;
	काष्ठा gc *gc;

	क्रम (i = 0; i < GC_MAX_PORTS; i++) अणु
		अगर (gc_base[i] && gc_base[i]->parportno == port->number)
			अवरोध;
	पूर्ण

	अगर (i == GC_MAX_PORTS)
		वापस;

	gc = gc_base[i];
	gc_base[i] = शून्य;

	क्रम (i = 0; i < GC_MAX_DEVICES; i++)
		अगर (gc->pads[i].dev)
			input_unरेजिस्टर_device(gc->pads[i].dev);
	parport_unरेजिस्टर_device(gc->pd);
	kमुक्त(gc);
पूर्ण

अटल काष्ठा parport_driver gc_parport_driver = अणु
	.name = "gamecon",
	.match_port = gc_attach,
	.detach = gc_detach,
	.devmodel = true,
पूर्ण;

अटल पूर्णांक __init gc_init(व्योम)
अणु
	पूर्णांक i;
	पूर्णांक have_dev = 0;

	क्रम (i = 0; i < GC_MAX_PORTS; i++) अणु
		अगर (gc_cfg[i].nargs == 0 || gc_cfg[i].args[0] < 0)
			जारी;

		अगर (gc_cfg[i].nargs < 2) अणु
			pr_err("at least one device must be specified\n");
			वापस -EINVAL;
		पूर्ण

		have_dev = 1;
	पूर्ण

	अगर (!have_dev)
		वापस -ENODEV;

	वापस parport_रेजिस्टर_driver(&gc_parport_driver);
पूर्ण

अटल व्योम __निकास gc_निकास(व्योम)
अणु
	parport_unरेजिस्टर_driver(&gc_parport_driver);
पूर्ण

module_init(gc_init);
module_निकास(gc_निकास);
