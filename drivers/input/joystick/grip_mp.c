<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  Driver क्रम the Gravis Grip Multiport, a gamepad "hub" that
 *  connects up to four 9-pin digital gamepads/joysticks.
 *  Driver tested on SMP and UP kernel versions 2.4.18-4 and 2.4.18-5.
 *
 *  Thanks to Chris Gassib क्रम helpful advice.
 *
 *  Copyright (c)      2002 Brian Bonnlander, Bill Soudan
 *  Copyright (c) 1998-2000 Vojtech Pavlik
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/gameport.h>
#समावेश <linux/input.h>
#समावेश <linux/delay.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/jअगरfies.h>

#घोषणा DRIVER_DESC	"Gravis Grip Multiport driver"

MODULE_AUTHOR("Brian Bonnlander");
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_LICENSE("GPL");

#अगर_घोषित GRIP_DEBUG
#घोषणा dbg(क्रमmat, arg...) prपूर्णांकk(KERN_ERR __खाता__ ": " क्रमmat "\n" , ## arg)
#अन्यथा
#घोषणा dbg(क्रमmat, arg...) करो अणुपूर्ण जबतक (0)
#पूर्ण_अगर

#घोषणा GRIP_MAX_PORTS	4
/*
 * Grip multiport state
 */

काष्ठा grip_port अणु
	काष्ठा input_dev *dev;
	पूर्णांक mode;
	पूर्णांक रेजिस्टरed;

	/* inभागidual gamepad states */
	पूर्णांक buttons;
	पूर्णांक xaxes;
	पूर्णांक yaxes;
	पूर्णांक dirty;     /* has the state been updated? */
पूर्ण;

काष्ठा grip_mp अणु
	काष्ठा gameport *gameport;
	काष्ठा grip_port *port[GRIP_MAX_PORTS];
	पूर्णांक पढ़ोs;
	पूर्णांक bads;
पूर्ण;

/*
 * Multiport packet पूर्णांकerpretation
 */

#घोषणा PACKET_FULL          0x80000000       /* packet is full                        */
#घोषणा PACKET_IO_FAST       0x40000000       /* 3 bits per gameport पढ़ो              */
#घोषणा PACKET_IO_SLOW       0x20000000       /* 1 bit per gameport पढ़ो               */
#घोषणा PACKET_MP_MORE       0x04000000       /* multiport wants to send more          */
#घोषणा PACKET_MP_DONE       0x02000000       /* multiport करोne sending                */

/*
 * Packet status code पूर्णांकerpretation
 */

#घोषणा IO_GOT_PACKET        0x0100           /* Got a packet                           */
#घोषणा IO_MODE_FAST         0x0200           /* Used 3 data bits per gameport पढ़ो     */
#घोषणा IO_SLOT_CHANGE       0x0800           /* Multiport physical slot status changed */
#घोषणा IO_DONE              0x1000           /* Multiport is करोne sending packets      */
#घोषणा IO_RETRY             0x4000           /* Try again later to get packet          */
#घोषणा IO_RESET             0x8000           /* Force multiport to resend all packets  */

/*
 * Gamepad configuration data.  Other 9-pin digital joystick devices
 * may work with the multiport, so this may not be an exhaustive list!
 * Commoकरोre 64 joystick reमुख्यs untested.
 */

#घोषणा GRIP_INIT_DELAY         2000          /*  2 ms */

#घोषणा GRIP_MODE_NONE		0
#घोषणा GRIP_MODE_RESET         1
#घोषणा GRIP_MODE_GP		2
#घोषणा GRIP_MODE_C64		3

अटल स्थिर पूर्णांक grip_btn_gp[]  = अणु BTN_TR, BTN_TL, BTN_A, BTN_B, BTN_C, BTN_X, BTN_Y, BTN_Z, -1 पूर्ण;
अटल स्थिर पूर्णांक grip_btn_c64[] = अणु BTN_JOYSTICK, -1 पूर्ण;

अटल स्थिर पूर्णांक grip_असल_gp[]  = अणु ABS_X, ABS_Y, -1 पूर्ण;
अटल स्थिर पूर्णांक grip_असल_c64[] = अणु ABS_X, ABS_Y, -1 पूर्ण;

अटल स्थिर पूर्णांक *grip_असल[] = अणु शून्य, शून्य, grip_असल_gp, grip_असल_c64 पूर्ण;
अटल स्थिर पूर्णांक *grip_btn[] = अणु शून्य, शून्य, grip_btn_gp, grip_btn_c64 पूर्ण;

अटल स्थिर अक्षर *grip_name[] = अणु शून्य, शून्य, "Gravis Grip Pad", "Commodore 64 Joystick" पूर्ण;

अटल स्थिर पूर्णांक init_seq[] = अणु
	1, 0, 1, 1, 0, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1,
	1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 0, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1,
	1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1,
	0, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1 पूर्ण;

/* Maps multiport directional values to X,Y axis values (each axis encoded in 3 bits) */

अटल स्थिर पूर्णांक axis_map[] = अणु 5, 9, 1, 5, 6, 10, 2, 6, 4, 8, 0, 4, 5, 9, 1, 5 पूर्ण;

अटल पूर्णांक रेजिस्टर_slot(पूर्णांक i, काष्ठा grip_mp *grip);

/*
 * Returns whether an odd or even number of bits are on in pkt.
 */

अटल पूर्णांक bit_parity(u32 pkt)
अणु
	पूर्णांक x = pkt ^ (pkt >> 16);
	x ^= x >> 8;
	x ^= x >> 4;
	x ^= x >> 2;
	x ^= x >> 1;
	वापस x & 1;
पूर्ण

/*
 * Poll gameport; वापस true अगर all bits set in 'onbits' are on and
 * all bits set in 'offbits' are off.
 */

अटल अंतरभूत पूर्णांक poll_until(u8 onbits, u8 offbits, पूर्णांक u_sec, काष्ठा gameport* gp, u8 *data)
अणु
	पूर्णांक i, nloops;

	nloops = gameport_समय(gp, u_sec);
	क्रम (i = 0; i < nloops; i++) अणु
		*data = gameport_पढ़ो(gp);
		अगर ((*data & onbits) == onbits &&
		    (~(*data) & offbits) == offbits)
			वापस 1;
	पूर्ण
	dbg("gameport timed out after %d microseconds.\n", u_sec);
	वापस 0;
पूर्ण

/*
 * Gets a 28-bit packet from the multiport.
 *
 * After getting a packet successfully, commands encoded by sendcode may
 * be sent to the multiport.
 *
 * The multiport घड़ी value is reflected in gameport bit B4.
 *
 * Returns a packet status code indicating whether packet is valid, the transfer
 * mode, and any error conditions.
 *
 * sendflags:      current I/O status
 * sendcode:   data to send to the multiport अगर sendflags is nonzero
 */

अटल पूर्णांक mp_io(काष्ठा gameport* gameport, पूर्णांक sendflags, पूर्णांक sendcode, u32 *packet)
अणु
	u8  raw_data;            /* raw data from gameport */
	u8  data_mask;           /* packet data bits from raw_data */
	u32 pkt;                 /* packet temporary storage */
	पूर्णांक bits_per_पढ़ो;       /* num packet bits per gameport पढ़ो */
	पूर्णांक portvals = 0;        /* used क्रम port value sanity check */
	पूर्णांक i;

	/* Gameport bits B0, B4, B5 should first be off, then B4 should come on. */

	*packet = 0;
	raw_data = gameport_पढ़ो(gameport);
	अगर (raw_data & 1)
		वापस IO_RETRY;

	क्रम (i = 0; i < 64; i++) अणु
		raw_data = gameport_पढ़ो(gameport);
		portvals |= 1 << ((raw_data >> 4) & 3); /* Demux B4, B5 */
	पूर्ण

	अगर (portvals == 1) अणु                            /* B4, B5 off */
		raw_data = gameport_पढ़ो(gameport);
		portvals = raw_data & 0xf0;

		अगर (raw_data & 0x31)
			वापस IO_RESET;
		gameport_trigger(gameport);

		अगर (!poll_until(0x10, 0, 308, gameport, &raw_data))
			वापस IO_RESET;
	पूर्ण अन्यथा
		वापस IO_RETRY;

	/* Determine packet transfer mode and prepare क्रम packet स्थिरruction. */

	अगर (raw_data & 0x20) अणु                 /* 3 data bits/पढ़ो */
		portvals |= raw_data >> 4;     /* Compare B4-B7 beक्रमe & after trigger */

		अगर (portvals != 0xb)
			वापस 0;
		data_mask = 7;
		bits_per_पढ़ो = 3;
		pkt = (PACKET_FULL | PACKET_IO_FAST) >> 28;
	पूर्ण अन्यथा अणु                                 /* 1 data bit/पढ़ो */
		data_mask = 1;
		bits_per_पढ़ो = 1;
		pkt = (PACKET_FULL | PACKET_IO_SLOW) >> 28;
	पूर्ण

	/* Conकाष्ठा a packet.  Final data bits must be zero. */

	जबतक (1) अणु
		अगर (!poll_until(0, 0x10, 77, gameport, &raw_data))
			वापस IO_RESET;
		raw_data = (raw_data >> 5) & data_mask;

		अगर (pkt & PACKET_FULL)
			अवरोध;
		pkt = (pkt << bits_per_पढ़ो) | raw_data;

		अगर (!poll_until(0x10, 0, 77, gameport, &raw_data))
			वापस IO_RESET;
	पूर्ण

	अगर (raw_data)
		वापस IO_RESET;

	/* If 3 bits/पढ़ो used, drop from 30 bits to 28. */

	अगर (bits_per_पढ़ो == 3) अणु
		pkt = (pkt & 0xffff0000) | ((pkt << 1) & 0xffff);
		pkt = (pkt >> 2) | 0xf0000000;
	पूर्ण

	अगर (bit_parity(pkt) == 1)
		वापस IO_RESET;

	/* Acknowledge packet receipt */

	अगर (!poll_until(0x30, 0, 77, gameport, &raw_data))
		वापस IO_RESET;

	raw_data = gameport_पढ़ो(gameport);

	अगर (raw_data & 1)
		वापस IO_RESET;

	gameport_trigger(gameport);

	अगर (!poll_until(0, 0x20, 77, gameport, &raw_data))
		वापस IO_RESET;

        /* Return अगर we just wanted the packet or multiport wants to send more */

	*packet = pkt;
	अगर ((sendflags == 0) || ((sendflags & IO_RETRY) && !(pkt & PACKET_MP_DONE)))
		वापस IO_GOT_PACKET;

	अगर (pkt & PACKET_MP_MORE)
		वापस IO_GOT_PACKET | IO_RETRY;

	/* Multiport is करोne sending packets and is पढ़ोy to receive data */

	अगर (!poll_until(0x20, 0, 77, gameport, &raw_data))
		वापस IO_GOT_PACKET | IO_RESET;

	raw_data = gameport_पढ़ो(gameport);
	अगर (raw_data & 1)
		वापस IO_GOT_PACKET | IO_RESET;

	/* Trigger gameport based on bits in sendcode */

	gameport_trigger(gameport);
	करो अणु
		अगर (!poll_until(0x20, 0x10, 116, gameport, &raw_data))
			वापस IO_GOT_PACKET | IO_RESET;

		अगर (!poll_until(0x30, 0, 193, gameport, &raw_data))
			वापस IO_GOT_PACKET | IO_RESET;

		अगर (raw_data & 1)
			वापस IO_GOT_PACKET | IO_RESET;

		अगर (sendcode & 1)
			gameport_trigger(gameport);

		sendcode >>= 1;
	पूर्ण जबतक (sendcode);

	वापस IO_GOT_PACKET | IO_MODE_FAST;
पूर्ण

/*
 * Disables and restores पूर्णांकerrupts क्रम mp_io(), which करोes the actual I/O.
 */

अटल पूर्णांक multiport_io(काष्ठा gameport* gameport, पूर्णांक sendflags, पूर्णांक sendcode, u32 *packet)
अणु
	पूर्णांक status;
	अचिन्हित दीर्घ flags;

	local_irq_save(flags);
	status = mp_io(gameport, sendflags, sendcode, packet);
	local_irq_restore(flags);

	वापस status;
पूर्ण

/*
 * Puts multiport पूर्णांकo digital mode.  Multiport LED turns green.
 *
 * Returns true अगर a valid digital packet was received, false otherwise.
 */

अटल पूर्णांक dig_mode_start(काष्ठा gameport *gameport, u32 *packet)
अणु
	पूर्णांक i;
	पूर्णांक flags, tries = 0, bads = 0;

	क्रम (i = 0; i < ARRAY_SIZE(init_seq); i++) अणु     /* Send magic sequence */
		अगर (init_seq[i])
			gameport_trigger(gameport);
		udelay(GRIP_INIT_DELAY);
	पूर्ण

	क्रम (i = 0; i < 16; i++)            /* Wait क्रम multiport to settle */
		udelay(GRIP_INIT_DELAY);

	जबतक (tries < 64 && bads < 8) अणु    /* Reset multiport and try getting a packet */

		flags = multiport_io(gameport, IO_RESET, 0x27, packet);

		अगर (flags & IO_MODE_FAST)
			वापस 1;

		अगर (flags & IO_RETRY)
			tries++;
		अन्यथा
			bads++;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Packet काष्ठाure: B0-B15   => gamepad state
 *                   B16-B20  => gamepad device type
 *                   B21-B24  => multiport slot index (1-4)
 *
 * Known device types: 0x1f (grip pad), 0x0 (no device).  Others may exist.
 *
 * Returns the packet status.
 */

अटल पूर्णांक get_and_decode_packet(काष्ठा grip_mp *grip, पूर्णांक flags)
अणु
	काष्ठा grip_port *port;
	u32 packet;
	पूर्णांक joytype = 0;
	पूर्णांक slot;

	/* Get a packet and check क्रम validity */

	flags &= IO_RESET | IO_RETRY;
	flags = multiport_io(grip->gameport, flags, 0, &packet);
	grip->पढ़ोs++;

	अगर (packet & PACKET_MP_DONE)
		flags |= IO_DONE;

	अगर (flags && !(flags & IO_GOT_PACKET)) अणु
		grip->bads++;
		वापस flags;
	पूर्ण

	/* Ignore non-gamepad packets, e.g. multiport hardware version */

	slot = ((packet >> 21) & 0xf) - 1;
	अगर ((slot < 0) || (slot > 3))
		वापस flags;

	port = grip->port[slot];

	/*
	 * Handle "reset" packets, which occur at startup, and when gamepads
	 * are हटाओd or plugged in.  May contain configuration of a new gamepad.
	 */

	joytype = (packet >> 16) & 0x1f;
	अगर (!joytype) अणु

		अगर (port->रेजिस्टरed) अणु
			prपूर्णांकk(KERN_INFO "grip_mp: removing %s, slot %d\n",
			       grip_name[port->mode], slot);
			input_unरेजिस्टर_device(port->dev);
			port->रेजिस्टरed = 0;
		पूर्ण
		dbg("Reset: grip multiport slot %d\n", slot);
		port->mode = GRIP_MODE_RESET;
		flags |= IO_SLOT_CHANGE;
		वापस flags;
	पूर्ण

	/* Interpret a grip pad packet */

	अगर (joytype == 0x1f) अणु

		पूर्णांक dir = (packet >> 8) & 0xf;          /* eight way directional value */
		port->buttons = (~packet) & 0xff;
		port->yaxes = ((axis_map[dir] >> 2) & 3) - 1;
		port->xaxes = (axis_map[dir] & 3) - 1;
		port->dirty = 1;

		अगर (port->mode == GRIP_MODE_RESET)
			flags |= IO_SLOT_CHANGE;

		port->mode = GRIP_MODE_GP;

		अगर (!port->रेजिस्टरed) अणु
			dbg("New Grip pad in multiport slot %d.\n", slot);
			अगर (रेजिस्टर_slot(slot, grip)) अणु
				port->mode = GRIP_MODE_RESET;
				port->dirty = 0;
			पूर्ण
		पूर्ण
		वापस flags;
	पूर्ण

	/* Handle non-grip device codes.  For now, just prपूर्णांक diagnostics. */

	अणु
		अटल पूर्णांक strange_code = 0;
		अगर (strange_code != joytype) अणु
			prपूर्णांकk(KERN_INFO "Possible non-grip pad/joystick detected.\n");
			prपूर्णांकk(KERN_INFO "Got joy type 0x%x and packet 0x%x.\n", joytype, packet);
			strange_code = joytype;
		पूर्ण
	पूर्ण
	वापस flags;
पूर्ण

/*
 * Returns true अगर all multiport slot states appear valid.
 */

अटल पूर्णांक slots_valid(काष्ठा grip_mp *grip)
अणु
	पूर्णांक flags, slot, invalid = 0, active = 0;

	flags = get_and_decode_packet(grip, 0);
	अगर (!(flags & IO_GOT_PACKET))
		वापस 0;

	क्रम (slot = 0; slot < 4; slot++) अणु
		अगर (grip->port[slot]->mode == GRIP_MODE_RESET)
			invalid = 1;
		अगर (grip->port[slot]->mode != GRIP_MODE_NONE)
			active = 1;
	पूर्ण

	/* Return true अगर no active slot but multiport sent all its data */
	अगर (!active)
		वापस (flags & IO_DONE) ? 1 : 0;

	/* Return false अगर invalid device code received */
	वापस invalid ? 0 : 1;
पूर्ण

/*
 * Returns whether the multiport was placed पूर्णांकo digital mode and
 * able to communicate its state successfully.
 */

अटल पूर्णांक multiport_init(काष्ठा grip_mp *grip)
अणु
	पूर्णांक dig_mode, initialized = 0, tries = 0;
	u32 packet;

	dig_mode = dig_mode_start(grip->gameport, &packet);
	जबतक (!dig_mode && tries < 4) अणु
		dig_mode = dig_mode_start(grip->gameport, &packet);
		tries++;
	पूर्ण

	अगर (dig_mode)
		dbg("multiport_init(): digital mode activated.\n");
	अन्यथा अणु
		dbg("multiport_init(): unable to activate digital mode.\n");
		वापस 0;
	पूर्ण

	/* Get packets, store multiport state, and check state's validity */
	क्रम (tries = 0; tries < 4096; tries++) अणु
		अगर (slots_valid(grip)) अणु
			initialized = 1;
			अवरोध;
		पूर्ण
	पूर्ण
	dbg("multiport_init(): initialized == %d\n", initialized);
	वापस initialized;
पूर्ण

/*
 * Reports joystick state to the linux input layer.
 */

अटल व्योम report_slot(काष्ठा grip_mp *grip, पूर्णांक slot)
अणु
	काष्ठा grip_port *port = grip->port[slot];
	पूर्णांक i;

	/* Store button states with linux input driver */

	क्रम (i = 0; i < 8; i++)
		input_report_key(port->dev, grip_btn_gp[i], (port->buttons >> i) & 1);

	/* Store axis states with linux driver */

	input_report_असल(port->dev, ABS_X, port->xaxes);
	input_report_असल(port->dev, ABS_Y, port->yaxes);

	/* Tell the receiver of the events to process them */

	input_sync(port->dev);

	port->dirty = 0;
पूर्ण

/*
 * Get the multiport state.
 */

अटल व्योम grip_poll(काष्ठा gameport *gameport)
अणु
	काष्ठा grip_mp *grip = gameport_get_drvdata(gameport);
	पूर्णांक i, npkts, flags;

	क्रम (npkts = 0; npkts < 4; npkts++) अणु
		flags = IO_RETRY;
		क्रम (i = 0; i < 32; i++) अणु
			flags = get_and_decode_packet(grip, flags);
			अगर ((flags & IO_GOT_PACKET) || !(flags & IO_RETRY))
				अवरोध;
		पूर्ण
		अगर (flags & IO_DONE)
			अवरोध;
	पूर्ण

	क्रम (i = 0; i < 4; i++)
		अगर (grip->port[i]->dirty)
			report_slot(grip, i);
पूर्ण

/*
 * Called when a joystick device file is खोलोed
 */

अटल पूर्णांक grip_खोलो(काष्ठा input_dev *dev)
अणु
	काष्ठा grip_mp *grip = input_get_drvdata(dev);

	gameport_start_polling(grip->gameport);
	वापस 0;
पूर्ण

/*
 * Called when a joystick device file is बंदd
 */

अटल व्योम grip_बंद(काष्ठा input_dev *dev)
अणु
	काष्ठा grip_mp *grip = input_get_drvdata(dev);

	gameport_stop_polling(grip->gameport);
पूर्ण

/*
 * Tell the linux input layer about a newly plugged-in gamepad.
 */

अटल पूर्णांक रेजिस्टर_slot(पूर्णांक slot, काष्ठा grip_mp *grip)
अणु
	काष्ठा grip_port *port = grip->port[slot];
	काष्ठा input_dev *input_dev;
	पूर्णांक j, t;
	पूर्णांक err;

	port->dev = input_dev = input_allocate_device();
	अगर (!input_dev)
		वापस -ENOMEM;

	input_dev->name = grip_name[port->mode];
	input_dev->id.bustype = BUS_GAMEPORT;
	input_dev->id.venकरोr = GAMEPORT_ID_VENDOR_GRAVIS;
	input_dev->id.product = 0x0100 + port->mode;
	input_dev->id.version = 0x0100;
	input_dev->dev.parent = &grip->gameport->dev;

	input_set_drvdata(input_dev, grip);

	input_dev->खोलो = grip_खोलो;
	input_dev->बंद = grip_बंद;

	input_dev->evbit[0] = BIT_MASK(EV_KEY) | BIT_MASK(EV_ABS);

	क्रम (j = 0; (t = grip_असल[port->mode][j]) >= 0; j++)
		input_set_असल_params(input_dev, t, -1, 1, 0, 0);

	क्रम (j = 0; (t = grip_btn[port->mode][j]) >= 0; j++)
		अगर (t > 0)
			set_bit(t, input_dev->keybit);

	err = input_रेजिस्टर_device(port->dev);
	अगर (err) अणु
		input_मुक्त_device(port->dev);
		वापस err;
	पूर्ण

	port->रेजिस्टरed = 1;

	अगर (port->dirty)	            /* report initial state, अगर any */
		report_slot(grip, slot);

	वापस 0;
पूर्ण

अटल पूर्णांक grip_connect(काष्ठा gameport *gameport, काष्ठा gameport_driver *drv)
अणु
	काष्ठा grip_mp *grip;
	पूर्णांक err;

	अगर (!(grip = kzalloc(माप(काष्ठा grip_mp), GFP_KERNEL)))
		वापस -ENOMEM;

	grip->gameport = gameport;

	gameport_set_drvdata(gameport, grip);

	err = gameport_खोलो(gameport, drv, GAMEPORT_MODE_RAW);
	अगर (err)
		जाओ fail1;

	gameport_set_poll_handler(gameport, grip_poll);
	gameport_set_poll_पूर्णांकerval(gameport, 20);

	अगर (!multiport_init(grip)) अणु
		err = -ENODEV;
		जाओ fail2;
	पूर्ण

	अगर (!grip->port[0]->mode && !grip->port[1]->mode && !grip->port[2]->mode && !grip->port[3]->mode) अणु
		/* nothing plugged in */
		err = -ENODEV;
		जाओ fail2;
	पूर्ण

	वापस 0;

fail2:	gameport_बंद(gameport);
fail1:	gameport_set_drvdata(gameport, शून्य);
	kमुक्त(grip);
	वापस err;
पूर्ण

अटल व्योम grip_disconnect(काष्ठा gameport *gameport)
अणु
	काष्ठा grip_mp *grip = gameport_get_drvdata(gameport);
	पूर्णांक i;

	क्रम (i = 0; i < 4; i++)
		अगर (grip->port[i]->रेजिस्टरed)
			input_unरेजिस्टर_device(grip->port[i]->dev);
	gameport_बंद(gameport);
	gameport_set_drvdata(gameport, शून्य);
	kमुक्त(grip);
पूर्ण

अटल काष्ठा gameport_driver grip_drv = अणु
	.driver		= अणु
		.name	= "grip_mp",
	पूर्ण,
	.description	= DRIVER_DESC,
	.connect	= grip_connect,
	.disconnect	= grip_disconnect,
पूर्ण;

module_gameport_driver(grip_drv);
