<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Copyright (c) 1998-2005 Vojtech Pavlik
 */

/*
 * Microsoft SideWinder joystick family driver क्रम Linux
 */

/*
 */

#समावेश <linux/delay.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/input.h>
#समावेश <linux/gameport.h>
#समावेश <linux/jअगरfies.h>

#घोषणा DRIVER_DESC	"Microsoft SideWinder joystick family driver"

MODULE_AUTHOR("Vojtech Pavlik <vojtech@ucw.cz>");
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_LICENSE("GPL");

/*
 * These are really magic values. Changing them can make a problem go away,
 * as well as अवरोध everything.
 */

#अघोषित SW_DEBUG
#अघोषित SW_DEBUG_DATA

#घोषणा SW_START	600	/* The समय we रुको क्रम the first bit [600 us] */
#घोषणा SW_STROBE	60	/* Max समय per bit [60 us] */
#घोषणा SW_TIMEOUT	6	/* Wait क्रम everything to settle [6 ms] */
#घोषणा SW_KICK		45	/* Wait after A0 fall till kick [45 us] */
#घोषणा SW_END		8	/* Number of bits beक्रमe end of packet to kick */
#घोषणा SW_FAIL		16	/* Number of packet पढ़ो errors to fail and reinitialize */
#घोषणा SW_BAD		2	/* Number of packet पढ़ो errors to चयन off 3d Pro optimization */
#घोषणा SW_OK		64	/* Number of packet पढ़ो successes to चयन optimization back on */
#घोषणा SW_LENGTH	512	/* Max number of bits in a packet */

#अगर_घोषित SW_DEBUG
#घोषणा dbg(क्रमmat, arg...) prपूर्णांकk(KERN_DEBUG __खाता__ ": " क्रमmat "\n" , ## arg)
#अन्यथा
#घोषणा dbg(क्रमmat, arg...) करो अणुपूर्ण जबतक (0)
#पूर्ण_अगर

/*
 * SideWinder joystick types ...
 */

#घोषणा SW_ID_3DP	0
#घोषणा SW_ID_GP	1
#घोषणा SW_ID_PP	2
#घोषणा SW_ID_FFP	3
#घोषणा SW_ID_FSP	4
#घोषणा SW_ID_FFW	5

/*
 * Names, buttons, axes ...
 */

अटल अक्षर *sw_name[] = अणु	"3D Pro", "GamePad", "Precision Pro", "Force Feedback Pro", "FreeStyle Pro",
				"Force Feedback Wheel" पूर्ण;

अटल अक्षर sw_असल[][7] = अणु
	अणु ABS_X, ABS_Y, ABS_RZ, ABS_THROTTLE, ABS_HAT0X, ABS_HAT0Y पूर्ण,
	अणु ABS_X, ABS_Y पूर्ण,
	अणु ABS_X, ABS_Y, ABS_RZ, ABS_THROTTLE, ABS_HAT0X, ABS_HAT0Y पूर्ण,
	अणु ABS_X, ABS_Y, ABS_RZ, ABS_THROTTLE, ABS_HAT0X, ABS_HAT0Y पूर्ण,
	अणु ABS_X, ABS_Y,         ABS_THROTTLE, ABS_HAT0X, ABS_HAT0Y पूर्ण,
	अणु ABS_RX, ABS_RUDDER,   ABS_THROTTLE पूर्णपूर्ण;

अटल अक्षर sw_bit[][7] = अणु
	अणु 10, 10,  9, 10,  1,  1 पूर्ण,
	अणु  1,  1                 पूर्ण,
	अणु 10, 10,  6,  7,  1,  1 पूर्ण,
	अणु 10, 10,  6,  7,  1,  1 पूर्ण,
	अणु 10, 10,  6,  1,  1     पूर्ण,
	अणु 10,  7,  7,  1,  1     पूर्णपूर्ण;

अटल लघु sw_btn[][12] = अणु
	अणु BTN_TRIGGER, BTN_TOP, BTN_THUMB, BTN_THUMB2, BTN_BASE, BTN_BASE2, BTN_BASE3, BTN_BASE4, BTN_MODE पूर्ण,
	अणु BTN_A, BTN_B, BTN_C, BTN_X, BTN_Y, BTN_Z, BTN_TL, BTN_TR, BTN_START, BTN_MODE पूर्ण,
	अणु BTN_TRIGGER, BTN_THUMB, BTN_TOP, BTN_TOP2, BTN_BASE, BTN_BASE2, BTN_BASE3, BTN_BASE4, BTN_SELECT पूर्ण,
	अणु BTN_TRIGGER, BTN_THUMB, BTN_TOP, BTN_TOP2, BTN_BASE, BTN_BASE2, BTN_BASE3, BTN_BASE4, BTN_SELECT पूर्ण,
	अणु BTN_A, BTN_B, BTN_C, BTN_X, BTN_Y, BTN_Z, BTN_TL, BTN_TR, BTN_START, BTN_MODE, BTN_SELECT पूर्ण,
	अणु BTN_TRIGGER, BTN_TOP, BTN_THUMB, BTN_THUMB2, BTN_BASE, BTN_BASE2, BTN_BASE3, BTN_BASE4 पूर्णपूर्ण;

अटल काष्ठा अणु
	पूर्णांक x;
	पूर्णांक y;
पूर्ण sw_hat_to_axis[] = अणुअणु 0, 0पूर्ण, अणु 0,-1पूर्ण, अणु 1,-1पूर्ण, अणु 1, 0पूर्ण, अणु 1, 1पूर्ण, अणु 0, 1पूर्ण, अणु-1, 1पूर्ण, अणु-1, 0पूर्ण, अणु-1,-1पूर्णपूर्ण;

काष्ठा sw अणु
	काष्ठा gameport *gameport;
	काष्ठा input_dev *dev[4];
	अक्षर name[64];
	अक्षर phys[4][32];
	पूर्णांक length;
	पूर्णांक type;
	पूर्णांक bits;
	पूर्णांक number;
	पूर्णांक fail;
	पूर्णांक ok;
	पूर्णांक पढ़ोs;
	पूर्णांक bads;
पूर्ण;

/*
 * sw_पढ़ो_packet() is a function which पढ़ोs either a data packet, or an
 * identअगरication packet from a SideWinder joystick. The protocol is very,
 * very, very braindamaged. Microsoft patented it in US patent #5628686.
 */

अटल पूर्णांक sw_पढ़ो_packet(काष्ठा gameport *gameport, अचिन्हित अक्षर *buf, पूर्णांक length, पूर्णांक id)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक समयout, bitout, sched, i, kick, start, strobe;
	अचिन्हित अक्षर pending, u, v;

	i = -id;						/* Don't care about data, only want ID */
	समयout = id ? gameport_समय(gameport, SW_TIMEOUT * 1000) : 0; /* Set up global समयout क्रम ID packet */
	kick = id ? gameport_समय(gameport, SW_KICK) : 0;	/* Set up kick समयout क्रम ID packet */
	start = gameport_समय(gameport, SW_START);
	strobe = gameport_समय(gameport, SW_STROBE);
	bitout = start;
	pending = 0;
	sched = 0;

        local_irq_save(flags);					/* Quiet, please */

	gameport_trigger(gameport);				/* Trigger */
	v = gameport_पढ़ो(gameport);

	करो अणु
		bitout--;
		u = v;
		v = gameport_पढ़ो(gameport);
	पूर्ण जबतक (!(~v & u & 0x10) && (bitout > 0));		/* Wait क्रम first falling edge on घड़ी */

	अगर (bitout > 0)
		bitout = strobe;				/* Extend समय अगर not समयd out */

	जबतक ((समयout > 0 || bitout > 0) && (i < length)) अणु

		समयout--;
		bitout--;					/* Decrement समयrs */
		sched--;

		u = v;
		v = gameport_पढ़ो(gameport);

		अगर ((~u & v & 0x10) && (bitout > 0)) अणु		/* Rising edge on घड़ी - data bit */
			अगर (i >= 0)				/* Want this data */
				buf[i] = v >> 5;		/* Store it */
			i++;					/* Advance index */
			bitout = strobe;			/* Extend समयout क्रम next bit */
		पूर्ण

		अगर (kick && (~v & u & 0x01)) अणु			/* Falling edge on axis 0 */
			sched = kick;				/* Schedule second trigger */
			kick = 0;				/* Don't schedule next समय on falling edge */
			pending = 1;				/* Mark schedule */
		पूर्ण

		अगर (pending && sched < 0 && (i > -SW_END)) अणु	/* Second trigger समय */
			gameport_trigger(gameport);		/* Trigger */
			bitout = start;				/* Long bit समयout */
			pending = 0;				/* Unmark schedule */
			समयout = 0;				/* Switch from global to bit समयouts */
		पूर्ण
	पूर्ण

	local_irq_restore(flags);					/* Done - relax */

#अगर_घोषित SW_DEBUG_DATA
	अणु
		पूर्णांक j;
		prपूर्णांकk(KERN_DEBUG "sidewinder.c: Read %d triplets. [", i);
		क्रम (j = 0; j < i; j++) prपूर्णांकk("%d", buf[j]);
		prपूर्णांकk("]\n");
	पूर्ण
#पूर्ण_अगर

	वापस i;
पूर्ण

/*
 * sw_get_bits() and GB() compose bits from the triplet buffer पूर्णांकo a __u64.
 * Parameter 'pos' is bit number inside packet where to start at, 'num' is number
 * of bits to be पढ़ो, 'shift' is offset in the resulting __u64 to start at, bits
 * is number of bits per triplet.
 */

#घोषणा GB(pos,num) sw_get_bits(buf, pos, num, sw->bits)

अटल __u64 sw_get_bits(अचिन्हित अक्षर *buf, पूर्णांक pos, पूर्णांक num, अक्षर bits)
अणु
	__u64 data = 0;
	पूर्णांक tri = pos % bits;						/* Start position */
	पूर्णांक i   = pos / bits;
	पूर्णांक bit = 0;

	जबतक (num--) अणु
		data |= (__u64)((buf[i] >> tri++) & 1) << bit++;	/* Transfer bit */
		अगर (tri == bits) अणु
			i++;						/* Next triplet */
			tri = 0;
		पूर्ण
	पूर्ण

	वापस data;
पूर्ण

/*
 * sw_init_digital() initializes a SideWinder 3D Pro joystick
 * पूर्णांकo digital mode.
 */

अटल व्योम sw_init_digital(काष्ठा gameport *gameport)
अणु
	अटल स्थिर पूर्णांक seq[] = अणु 140, 140+725, 140+300, 0 पूर्ण;
	अचिन्हित दीर्घ flags;
	पूर्णांक i, t;

        local_irq_save(flags);

	i = 0;
        करो अणु
                gameport_trigger(gameport);			/* Trigger */
		t = gameport_समय(gameport, SW_TIMEOUT * 1000);
		जबतक ((gameport_पढ़ो(gameport) & 1) && t) t--;	/* Wait क्रम axis to fall back to 0 */
                udelay(seq[i]);					/* Delay magic समय */
        पूर्ण जबतक (seq[++i]);

	gameport_trigger(gameport);				/* Last trigger */

	local_irq_restore(flags);
पूर्ण

/*
 * sw_parity() computes parity of __u64
 */

अटल पूर्णांक sw_parity(__u64 t)
अणु
	पूर्णांक x = t ^ (t >> 32);

	x ^= x >> 16;
	x ^= x >> 8;
	x ^= x >> 4;
	x ^= x >> 2;
	x ^= x >> 1;
	वापस x & 1;
पूर्ण

/*
 * sw_ccheck() checks synchronization bits and computes checksum of nibbles.
 */

अटल पूर्णांक sw_check(__u64 t)
अणु
	अचिन्हित अक्षर sum = 0;

	अगर ((t & 0x8080808080808080ULL) ^ 0x80)			/* Sync */
		वापस -1;

	जबतक (t) अणु						/* Sum */
		sum += t & 0xf;
		t >>= 4;
	पूर्ण

	वापस sum & 0xf;
पूर्ण

/*
 * sw_parse() analyzes SideWinder joystick data, and ग_लिखोs the results पूर्णांकo
 * the axes and buttons arrays.
 */

अटल पूर्णांक sw_parse(अचिन्हित अक्षर *buf, काष्ठा sw *sw)
अणु
	पूर्णांक hat, i, j;
	काष्ठा input_dev *dev;

	चयन (sw->type) अणु

		हाल SW_ID_3DP:

			अगर (sw_check(GB(0,64)) || (hat = (GB(6,1) << 3) | GB(60,3)) > 8)
				वापस -1;

			dev = sw->dev[0];

			input_report_असल(dev, ABS_X,        (GB( 3,3) << 7) | GB(16,7));
			input_report_असल(dev, ABS_Y,        (GB( 0,3) << 7) | GB(24,7));
			input_report_असल(dev, ABS_RZ,       (GB(35,2) << 7) | GB(40,7));
			input_report_असल(dev, ABS_THROTTLE, (GB(32,3) << 7) | GB(48,7));

			input_report_असल(dev, ABS_HAT0X, sw_hat_to_axis[hat].x);
			input_report_असल(dev, ABS_HAT0Y, sw_hat_to_axis[hat].y);

			क्रम (j = 0; j < 7; j++)
				input_report_key(dev, sw_btn[SW_ID_3DP][j], !GB(j+8,1));

			input_report_key(dev, BTN_BASE4, !GB(38,1));
			input_report_key(dev, BTN_BASE5, !GB(37,1));

			input_sync(dev);

			वापस 0;

		हाल SW_ID_GP:

			क्रम (i = 0; i < sw->number; i ++) अणु

				अगर (sw_parity(GB(i*15,15)))
					वापस -1;

				input_report_असल(sw->dev[i], ABS_X, GB(i*15+3,1) - GB(i*15+2,1));
				input_report_असल(sw->dev[i], ABS_Y, GB(i*15+0,1) - GB(i*15+1,1));

				क्रम (j = 0; j < 10; j++)
					input_report_key(sw->dev[i], sw_btn[SW_ID_GP][j], !GB(i*15+j+4,1));

				input_sync(sw->dev[i]);
			पूर्ण

			वापस 0;

		हाल SW_ID_PP:
		हाल SW_ID_FFP:

			अगर (!sw_parity(GB(0,48)) || (hat = GB(42,4)) > 8)
				वापस -1;

			dev = sw->dev[0];
			input_report_असल(dev, ABS_X,        GB( 9,10));
			input_report_असल(dev, ABS_Y,        GB(19,10));
			input_report_असल(dev, ABS_RZ,       GB(36, 6));
			input_report_असल(dev, ABS_THROTTLE, GB(29, 7));

			input_report_असल(dev, ABS_HAT0X, sw_hat_to_axis[hat].x);
			input_report_असल(dev, ABS_HAT0Y, sw_hat_to_axis[hat].y);

			क्रम (j = 0; j < 9; j++)
				input_report_key(dev, sw_btn[SW_ID_PP][j], !GB(j,1));

			input_sync(dev);

			वापस 0;

		हाल SW_ID_FSP:

			अगर (!sw_parity(GB(0,43)) || (hat = GB(28,4)) > 8)
				वापस -1;

			dev = sw->dev[0];
			input_report_असल(dev, ABS_X,        GB( 0,10));
			input_report_असल(dev, ABS_Y,        GB(16,10));
			input_report_असल(dev, ABS_THROTTLE, GB(32, 6));

			input_report_असल(dev, ABS_HAT0X, sw_hat_to_axis[hat].x);
			input_report_असल(dev, ABS_HAT0Y, sw_hat_to_axis[hat].y);

			क्रम (j = 0; j < 6; j++)
				input_report_key(dev, sw_btn[SW_ID_FSP][j], !GB(j+10,1));

			input_report_key(dev, BTN_TR,     !GB(26,1));
			input_report_key(dev, BTN_START,  !GB(27,1));
			input_report_key(dev, BTN_MODE,   !GB(38,1));
			input_report_key(dev, BTN_SELECT, !GB(39,1));

			input_sync(dev);

			वापस 0;

		हाल SW_ID_FFW:

			अगर (!sw_parity(GB(0,33)))
				वापस -1;

			dev = sw->dev[0];
			input_report_असल(dev, ABS_RX,       GB( 0,10));
			input_report_असल(dev, ABS_RUDDER,   GB(10, 6));
			input_report_असल(dev, ABS_THROTTLE, GB(16, 6));

			क्रम (j = 0; j < 8; j++)
				input_report_key(dev, sw_btn[SW_ID_FFW][j], !GB(j+22,1));

			input_sync(dev);

			वापस 0;
	पूर्ण

	वापस -1;
पूर्ण

/*
 * sw_पढ़ो() पढ़ोs SideWinder joystick data, and reinitializes
 * the joystick in हाल of persistent problems. This is the function that is
 * called from the generic code to poll the joystick.
 */

अटल पूर्णांक sw_पढ़ो(काष्ठा sw *sw)
अणु
	अचिन्हित अक्षर buf[SW_LENGTH];
	पूर्णांक i;

	i = sw_पढ़ो_packet(sw->gameport, buf, sw->length, 0);

	अगर (sw->type == SW_ID_3DP && sw->length == 66 && i != 66) अणु		/* Broken packet, try to fix */

		अगर (i == 64 && !sw_check(sw_get_bits(buf,0,64,1))) अणु		/* Last init failed, 1 bit mode */
			prपूर्णांकk(KERN_WARNING "sidewinder.c: Joystick in wrong mode on %s"
				" - going to reinitialize.\n", sw->gameport->phys);
			sw->fail = SW_FAIL;					/* Reinitialize */
			i = 128;						/* Bogus value */
		पूर्ण

		अगर (i < 66 && GB(0,64) == GB(i*3-66,64))			/* 1 == 3 */
			i = 66;							/* Everything is fine */

		अगर (i < 66 && GB(0,64) == GB(66,64))				/* 1 == 2 */
			i = 66;							/* Everything is fine */

		अगर (i < 66 && GB(i*3-132,64) == GB(i*3-66,64)) अणु		/* 2 == 3 */
			स_हटाओ(buf, buf + i - 22, 22);				/* Move data */
			i = 66;							/* Carry on */
		पूर्ण
	पूर्ण

	अगर (i == sw->length && !sw_parse(buf, sw)) अणु				/* Parse data */

		sw->fail = 0;
		sw->ok++;

		अगर (sw->type == SW_ID_3DP && sw->length == 66			/* Many packets OK */
			&& sw->ok > SW_OK) अणु

			prपूर्णांकk(KERN_INFO "sidewinder.c: No more trouble on %s"
				" - enabling optimization again.\n", sw->gameport->phys);
			sw->length = 22;
		पूर्ण

		वापस 0;
	पूर्ण

	sw->ok = 0;
	sw->fail++;

	अगर (sw->type == SW_ID_3DP && sw->length == 22 && sw->fail > SW_BAD) अणु	/* Consecutive bad packets */

		prपूर्णांकk(KERN_INFO "sidewinder.c: Many bit errors on %s"
			" - disabling optimization.\n", sw->gameport->phys);
		sw->length = 66;
	पूर्ण

	अगर (sw->fail < SW_FAIL)
		वापस -1;							/* Not enough, करोn't reinitialize yet */

	prपूर्णांकk(KERN_WARNING "sidewinder.c: Too many bit errors on %s"
		" - reinitializing joystick.\n", sw->gameport->phys);

	अगर (!i && sw->type == SW_ID_3DP) अणु					/* 3D Pro can be in analog mode */
		mdelay(3 * SW_TIMEOUT);
		sw_init_digital(sw->gameport);
	पूर्ण

	mdelay(SW_TIMEOUT);
	i = sw_पढ़ो_packet(sw->gameport, buf, SW_LENGTH, 0);			/* Read normal data packet */
	mdelay(SW_TIMEOUT);
	sw_पढ़ो_packet(sw->gameport, buf, SW_LENGTH, i);			/* Read ID packet, this initializes the stick */

	sw->fail = SW_FAIL;

	वापस -1;
पूर्ण

अटल व्योम sw_poll(काष्ठा gameport *gameport)
अणु
	काष्ठा sw *sw = gameport_get_drvdata(gameport);

	sw->पढ़ोs++;
	अगर (sw_पढ़ो(sw))
		sw->bads++;
पूर्ण

अटल पूर्णांक sw_खोलो(काष्ठा input_dev *dev)
अणु
	काष्ठा sw *sw = input_get_drvdata(dev);

	gameport_start_polling(sw->gameport);
	वापस 0;
पूर्ण

अटल व्योम sw_बंद(काष्ठा input_dev *dev)
अणु
	काष्ठा sw *sw = input_get_drvdata(dev);

	gameport_stop_polling(sw->gameport);
पूर्ण

/*
 * sw_prपूर्णांक_packet() prपूर्णांकs the contents of a SideWinder packet.
 */

अटल व्योम sw_prपूर्णांक_packet(अक्षर *name, पूर्णांक length, अचिन्हित अक्षर *buf, अक्षर bits)
अणु
	पूर्णांक i;

	prपूर्णांकk(KERN_INFO "sidewinder.c: %s packet, %d bits. [", name, length);
	क्रम (i = (((length + 3) >> 2) - 1); i >= 0; i--)
		prपूर्णांकk("%x", (पूर्णांक)sw_get_bits(buf, i << 2, 4, bits));
	prपूर्णांकk("]\n");
पूर्ण

/*
 * sw_3dp_id() translates the 3DP id पूर्णांकo a human legible string.
 * Unक्रमtunately I करोn't know how to करो this क्रम the other SW types.
 */

अटल व्योम sw_3dp_id(अचिन्हित अक्षर *buf, अक्षर *comment, माप_प्रकार size)
अणु
	पूर्णांक i;
	अक्षर pnp[8], rev[9];

	क्रम (i = 0; i < 7; i++)						/* ASCII PnP ID */
		pnp[i] = sw_get_bits(buf, 24+8*i, 8, 1);

	क्रम (i = 0; i < 8; i++)						/* ASCII firmware revision */
		rev[i] = sw_get_bits(buf, 88+8*i, 8, 1);

	pnp[7] = rev[8] = 0;

	snम_लिखो(comment, size, " [PnP %d.%02d id %s rev %s]",
		(पूर्णांक) ((sw_get_bits(buf, 8, 6, 1) << 6) |		/* Two 6-bit values */
			sw_get_bits(buf, 16, 6, 1)) / 100,
		(पूर्णांक) ((sw_get_bits(buf, 8, 6, 1) << 6) |
			sw_get_bits(buf, 16, 6, 1)) % 100,
		 pnp, rev);
पूर्ण

/*
 * sw_guess_mode() checks the upper two button bits क्रम toggling -
 * indication of that the joystick is in 3-bit mode. This is करोcumented
 * behavior क्रम 3DP ID packet, and क्रम example the FSP करोes this in
 * normal packets instead. Fun ...
 */

अटल पूर्णांक sw_guess_mode(अचिन्हित अक्षर *buf, पूर्णांक len)
अणु
	पूर्णांक i;
	अचिन्हित अक्षर xor = 0;

	क्रम (i = 1; i < len; i++)
		xor |= (buf[i - 1] ^ buf[i]) & 6;

	वापस !!xor * 2 + 1;
पूर्ण

/*
 * sw_connect() probes क्रम SideWinder type joysticks.
 */

अटल पूर्णांक sw_connect(काष्ठा gameport *gameport, काष्ठा gameport_driver *drv)
अणु
	काष्ठा sw *sw;
	काष्ठा input_dev *input_dev;
	पूर्णांक i, j, k, l;
	पूर्णांक err = 0;
	अचिन्हित अक्षर *buf = शून्य;	/* [SW_LENGTH] */
	अचिन्हित अक्षर *idbuf = शून्य;	/* [SW_LENGTH] */
	अचिन्हित अक्षर m = 1;
	अक्षर comment[40];

	comment[0] = 0;

	sw = kzalloc(माप(काष्ठा sw), GFP_KERNEL);
	buf = kदो_स्मृति(SW_LENGTH, GFP_KERNEL);
	idbuf = kदो_स्मृति(SW_LENGTH, GFP_KERNEL);
	अगर (!sw || !buf || !idbuf) अणु
		err = -ENOMEM;
		जाओ fail1;
	पूर्ण

	sw->gameport = gameport;

	gameport_set_drvdata(gameport, sw);

	err = gameport_खोलो(gameport, drv, GAMEPORT_MODE_RAW);
	अगर (err)
		जाओ fail1;

	dbg("Init 0: Opened %s, io %#x, speed %d",
		gameport->phys, gameport->io, gameport->speed);

	i = sw_पढ़ो_packet(gameport, buf, SW_LENGTH, 0);		/* Read normal packet */
	msleep(SW_TIMEOUT);
	dbg("Init 1: Mode %d. Length %d.", m , i);

	अगर (!i) अणु							/* No data. 3d Pro analog mode? */
		sw_init_digital(gameport);				/* Switch to digital */
		msleep(SW_TIMEOUT);
		i = sw_पढ़ो_packet(gameport, buf, SW_LENGTH, 0);	/* Retry पढ़ोing packet */
		msleep(SW_TIMEOUT);
		dbg("Init 1b: Length %d.", i);
		अगर (!i) अणु						/* No data -> FAIL */
			err = -ENODEV;
			जाओ fail2;
		पूर्ण
	पूर्ण

	j = sw_पढ़ो_packet(gameport, idbuf, SW_LENGTH, i);		/* Read ID. This initializes the stick */
	m |= sw_guess_mode(idbuf, j);					/* ID packet should carry mode info [3DP] */
	dbg("Init 2: Mode %d. ID Length %d.", m, j);

	अगर (j <= 0) अणु							/* Read ID failed. Happens in 1-bit mode on PP */
		msleep(SW_TIMEOUT);
		i = sw_पढ़ो_packet(gameport, buf, SW_LENGTH, 0);	/* Retry पढ़ोing packet */
		m |= sw_guess_mode(buf, i);
		dbg("Init 2b: Mode %d. Length %d.", m, i);
		अगर (!i) अणु
			err = -ENODEV;
			जाओ fail2;
		पूर्ण
		msleep(SW_TIMEOUT);
		j = sw_पढ़ो_packet(gameport, idbuf, SW_LENGTH, i);	/* Retry पढ़ोing ID */
		dbg("Init 2c: ID Length %d.", j);
	पूर्ण

	sw->type = -1;
	k = SW_FAIL;							/* Try SW_FAIL बार */
	l = 0;

	करो अणु
		k--;
		msleep(SW_TIMEOUT);
		i = sw_पढ़ो_packet(gameport, buf, SW_LENGTH, 0);	/* Read data packet */
		dbg("Init 3: Mode %d. Length %d. Last %d. Tries %d.", m, i, l, k);

		अगर (i > l) अणु						/* Longer? As we can only lose bits, it makes */
									/* no sense to try detection क्रम a packet लघुer */
			l = i;						/* than the previous one */

			sw->number = 1;
			sw->gameport = gameport;
			sw->length = i;
			sw->bits = m;

			dbg("Init 3a: Case %d.\n", i * m);

			चयन (i * m) अणु
				हाल 60:
					sw->number++;
					fallthrough;
				हाल 45:				/* Ambiguous packet length */
					अगर (j <= 40) अणु			/* ID length less or eq 40 -> FSP */
				हाल 43:
						sw->type = SW_ID_FSP;
						अवरोध;
					पूर्ण
					sw->number++;
					fallthrough;
				हाल 30:
					sw->number++;
					fallthrough;
				हाल 15:
					sw->type = SW_ID_GP;
					अवरोध;
				हाल 33:
				हाल 31:
					sw->type = SW_ID_FFW;
					अवरोध;
				हाल 48:				/* Ambiguous */
					अगर (j == 14) अणु			/* ID length 14*3 -> FFP */
						sw->type = SW_ID_FFP;
						प्र_लिखो(comment, " [AC %s]", sw_get_bits(idbuf,38,1,3) ? "off" : "on");
					पूर्ण अन्यथा
						sw->type = SW_ID_PP;
					अवरोध;
				हाल 66:
					sw->bits = 3;
					fallthrough;
				हाल 198:
					sw->length = 22;
					fallthrough;
				हाल 64:
					sw->type = SW_ID_3DP;
					अगर (j == 160)
						sw_3dp_id(idbuf, comment, माप(comment));
					अवरोध;
			पूर्ण
		पूर्ण

	पूर्ण जबतक (k && sw->type == -1);

	अगर (sw->type == -1) अणु
		prपूर्णांकk(KERN_WARNING "sidewinder.c: unknown joystick device detected "
			"on %s, contact <vojtech@ucw.cz>\n", gameport->phys);
		sw_prपूर्णांक_packet("ID", j * 3, idbuf, 3);
		sw_prपूर्णांक_packet("Data", i * m, buf, m);
		err = -ENODEV;
		जाओ fail2;
	पूर्ण

#अगर_घोषित SW_DEBUG
	sw_prपूर्णांक_packet("ID", j * 3, idbuf, 3);
	sw_prपूर्णांक_packet("Data", i * m, buf, m);
#पूर्ण_अगर

	gameport_set_poll_handler(gameport, sw_poll);
	gameport_set_poll_पूर्णांकerval(gameport, 20);

	k = i;
	l = j;

	क्रम (i = 0; i < sw->number; i++) अणु
		पूर्णांक bits, code;

		snम_लिखो(sw->name, माप(sw->name),
			 "Microsoft SideWinder %s", sw_name[sw->type]);
		snम_लिखो(sw->phys[i], माप(sw->phys[i]),
			 "%s/input%d", gameport->phys, i);

		sw->dev[i] = input_dev = input_allocate_device();
		अगर (!input_dev) अणु
			err = -ENOMEM;
			जाओ fail3;
		पूर्ण

		input_dev->name = sw->name;
		input_dev->phys = sw->phys[i];
		input_dev->id.bustype = BUS_GAMEPORT;
		input_dev->id.venकरोr = GAMEPORT_ID_VENDOR_MICROSOFT;
		input_dev->id.product = sw->type;
		input_dev->id.version = 0x0100;
		input_dev->dev.parent = &gameport->dev;

		input_set_drvdata(input_dev, sw);

		input_dev->खोलो = sw_खोलो;
		input_dev->बंद = sw_बंद;

		input_dev->evbit[0] = BIT_MASK(EV_KEY) | BIT_MASK(EV_ABS);

		क्रम (j = 0; (bits = sw_bit[sw->type][j]); j++) अणु
			पूर्णांक min, max, fuzz, flat;

			code = sw_असल[sw->type][j];
			min = bits == 1 ? -1 : 0;
			max = (1 << bits) - 1;
			fuzz = (bits >> 1) >= 2 ? 1 << ((bits >> 1) - 2) : 0;
			flat = code == ABS_THROTTLE || bits < 5 ?
				0 : 1 << (bits - 5);

			input_set_असल_params(input_dev, code,
					     min, max, fuzz, flat);
		पूर्ण

		क्रम (j = 0; (code = sw_btn[sw->type][j]); j++)
			__set_bit(code, input_dev->keybit);

		dbg("%s%s [%d-bit id %d data %d]\n", sw->name, comment, m, l, k);

		err = input_रेजिस्टर_device(sw->dev[i]);
		अगर (err)
			जाओ fail4;
	पूर्ण

 out:	kमुक्त(buf);
	kमुक्त(idbuf);

	वापस err;

 fail4:	input_मुक्त_device(sw->dev[i]);
 fail3:	जबतक (--i >= 0)
		input_unरेजिस्टर_device(sw->dev[i]);
 fail2:	gameport_बंद(gameport);
 fail1:	gameport_set_drvdata(gameport, शून्य);
	kमुक्त(sw);
	जाओ out;
पूर्ण

अटल व्योम sw_disconnect(काष्ठा gameport *gameport)
अणु
	काष्ठा sw *sw = gameport_get_drvdata(gameport);
	पूर्णांक i;

	क्रम (i = 0; i < sw->number; i++)
		input_unरेजिस्टर_device(sw->dev[i]);
	gameport_बंद(gameport);
	gameport_set_drvdata(gameport, शून्य);
	kमुक्त(sw);
पूर्ण

अटल काष्ठा gameport_driver sw_drv = अणु
	.driver		= अणु
		.name	= "sidewinder",
		.owner	= THIS_MODULE,
	पूर्ण,
	.description	= DRIVER_DESC,
	.connect	= sw_connect,
	.disconnect	= sw_disconnect,
पूर्ण;

module_gameport_driver(sw_drv);
