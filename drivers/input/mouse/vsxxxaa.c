<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Driver क्रम	DEC VSXXX-AA mouse (hockey-puck mouse, ball or two rollers)
 *		DEC VSXXX-GA mouse (rectangular mouse, with ball)
 *		DEC VSXXX-AB tablet (digitizer with hair cross or stylus)
 *
 * Copyright (C) 2003-2004 by Jan-Benedict Glaw <jbglaw@lug-owl.de>
 *
 * The packet क्रमmat was initially taken from a patch to GPM which is (C) 2001
 * by	Karsten Merker <merker@linuxtag.org>
 * and	Maciej W. Rozycki <macro@ds2.pg.gda.pl>
 * Later on, I had access to the device's करोcumentation (referenced below).
 */

/*
 */

/*
 * Building an adaptor to DE9 / DB25 RS232
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 * DISCLAIMER: Use this description AT YOUR OWN RISK! I'll not pay क्रम
 * anything अगर you अवरोध your mouse, your computer or whatever!
 *
 * In theory, this mouse is a simple RS232 device. In practice, it has got
 * a quite uncommon plug and the requirement to additionally get a घातer
 * supply at +5V and -12V.
 *
 * If you look at the socket/jack (_not_ at the plug), we use this pin
 * numbering:
 *    _______
 *   / 7 6 5 \
 *  | 4 --- 3 |
 *   \  2 1  /
 *    -------
 *
 *	DEC socket	DE9	DB25	Note
 *	1 (GND)		5	7	-
 *	2 (RxD)		2	3	-
 *	3 (TxD)		3	2	-
 *	4 (-12V)	-	-	Somewhere from the PSU. At ATX, it's
 *					the thin blue wire at pin 12 of the
 *					ATX घातer connector. Only required क्रम
 *					VSXXX-AA/-GA mice.
 *	5 (+5V)		-	-	PSU (red wires of ATX घातer connector
 *					on pin 4, 6, 19 or 20) or HDD घातer
 *					connector (also red wire).
 *	6 (+12V)	-	-	HDD घातer connector, yellow wire. Only
 *					required क्रम VSXXX-AB digitizer.
 *	7 (dev. avail.)	-	-	The mouse लघुs this one to pin 1.
 *					This way, the host computer can detect
 *					the mouse. To use it with the adaptor,
 *					simply करोn't connect this pin.
 *
 * So to get a working adaptor, you need to connect the mouse with three
 * wires to a RS232 port and two or three additional wires क्रम +5V, +12V and
 * -12V to the PSU.
 *
 * Flow specअगरication क्रम the link is 4800, 8o1.
 *
 * The mice and tablet are described in "VCB02 Video Subप्रणाली - Technical
 * Manual", DEC EK-104AA-TM-001. You'll find it at MANX, a search engine
 * specअगरic क्रम DEC करोcumentation. Try
 * http://www.vt100.net/manx/details?pn=EK-104AA-TM-001;id=21;cp=1
 */

#समावेश <linux/delay.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/input.h>
#समावेश <linux/serपन.स>

#घोषणा DRIVER_DESC "Driver for DEC VSXXX-AA and -GA mice and VSXXX-AB tablet"

MODULE_AUTHOR("Jan-Benedict Glaw <jbglaw@lug-owl.de>");
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_LICENSE("GPL");

#अघोषित VSXXXAA_DEBUG
#अगर_घोषित VSXXXAA_DEBUG
#घोषणा DBG(x...) prपूर्णांकk(x)
#अन्यथा
#घोषणा DBG(x...) करो अणुपूर्ण जबतक (0)
#पूर्ण_अगर

#घोषणा VSXXXAA_INTRO_MASK	0x80
#घोषणा VSXXXAA_INTRO_HEAD	0x80
#घोषणा IS_HDR_BYTE(x)			\
	(((x) & VSXXXAA_INTRO_MASK) == VSXXXAA_INTRO_HEAD)

#घोषणा VSXXXAA_PACKET_MASK	0xe0
#घोषणा VSXXXAA_PACKET_REL	0x80
#घोषणा VSXXXAA_PACKET_ABS	0xc0
#घोषणा VSXXXAA_PACKET_POR	0xa0
#घोषणा MATCH_PACKET_TYPE(data, type)	\
	(((data) & VSXXXAA_PACKET_MASK) == (type))



काष्ठा vsxxxaa अणु
	काष्ठा input_dev *dev;
	काष्ठा serio *serio;
#घोषणा BUFLEN 15 /* At least 5 is needed क्रम a full tablet packet */
	अचिन्हित अक्षर buf[BUFLEN];
	अचिन्हित अक्षर count;
	अचिन्हित अक्षर version;
	अचिन्हित अक्षर country;
	अचिन्हित अक्षर type;
	अक्षर name[64];
	अक्षर phys[32];
पूर्ण;

अटल व्योम vsxxxaa_drop_bytes(काष्ठा vsxxxaa *mouse, पूर्णांक num)
अणु
	अगर (num >= mouse->count) अणु
		mouse->count = 0;
	पूर्ण अन्यथा अणु
		स_हटाओ(mouse->buf, mouse->buf + num, BUFLEN - num);
		mouse->count -= num;
	पूर्ण
पूर्ण

अटल व्योम vsxxxaa_queue_byte(काष्ठा vsxxxaa *mouse, अचिन्हित अक्षर byte)
अणु
	अगर (mouse->count == BUFLEN) अणु
		prपूर्णांकk(KERN_ERR "%s on %s: Dropping a byte of full buffer.\n",
			mouse->name, mouse->phys);
		vsxxxaa_drop_bytes(mouse, 1);
	पूर्ण

	DBG(KERN_INFO "Queueing byte 0x%02x\n", byte);

	mouse->buf[mouse->count++] = byte;
पूर्ण

अटल व्योम vsxxxaa_detection_करोne(काष्ठा vsxxxaa *mouse)
अणु
	चयन (mouse->type) अणु
	हाल 0x02:
		strlcpy(mouse->name, "DEC VSXXX-AA/-GA mouse",
			माप(mouse->name));
		अवरोध;

	हाल 0x04:
		strlcpy(mouse->name, "DEC VSXXX-AB digitizer",
			माप(mouse->name));
		अवरोध;

	शेष:
		snम_लिखो(mouse->name, माप(mouse->name),
			 "unknown DEC pointer device (type = 0x%02x)",
			 mouse->type);
		अवरोध;
	पूर्ण

	prपूर्णांकk(KERN_INFO
		"Found %s version 0x%02x from country 0x%02x on port %s\n",
		mouse->name, mouse->version, mouse->country, mouse->phys);
पूर्ण

/*
 * Returns number of bytes to be dropped, 0 अगर packet is okay.
 */
अटल पूर्णांक vsxxxaa_check_packet(काष्ठा vsxxxaa *mouse, पूर्णांक packet_len)
अणु
	पूर्णांक i;

	/* First byte must be a header byte */
	अगर (!IS_HDR_BYTE(mouse->buf[0])) अणु
		DBG("vsck: len=%d, 1st=0x%02x\n", packet_len, mouse->buf[0]);
		वापस 1;
	पूर्ण

	/* Check all following bytes */
	क्रम (i = 1; i < packet_len; i++) अणु
		अगर (IS_HDR_BYTE(mouse->buf[i])) अणु
			prपूर्णांकk(KERN_ERR
				"Need to drop %d bytes of a broken packet.\n",
				i - 1);
			DBG(KERN_INFO "check: len=%d, b[%d]=0x%02x\n",
			    packet_len, i, mouse->buf[i]);
			वापस i - 1;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक vsxxxaa_smells_like_packet(काष्ठा vsxxxaa *mouse,
					     अचिन्हित अक्षर type, माप_प्रकार len)
अणु
	वापस mouse->count >= len && MATCH_PACKET_TYPE(mouse->buf[0], type);
पूर्ण

अटल व्योम vsxxxaa_handle_REL_packet(काष्ठा vsxxxaa *mouse)
अणु
	काष्ठा input_dev *dev = mouse->dev;
	अचिन्हित अक्षर *buf = mouse->buf;
	पूर्णांक left, middle, right;
	पूर्णांक dx, dy;

	/*
	 * Check क्रम normal stream packets. This is three bytes,
	 * with the first byte's 3 MSB set to 100.
	 *
	 * [0]:	1	0	0	SignX	SignY	Left	Middle	Right
	 * [1]: 0	dx	dx	dx	dx	dx	dx	dx
	 * [2]:	0	dy	dy	dy	dy	dy	dy	dy
	 */

	/*
	 * Low 7 bit of byte 1 are असल(dx), bit 7 is
	 * 0, bit 4 of byte 0 is direction.
	 */
	dx = buf[1] & 0x7f;
	dx *= ((buf[0] >> 4) & 0x01) ? 1 : -1;

	/*
	 * Low 7 bit of byte 2 are असल(dy), bit 7 is
	 * 0, bit 3 of byte 0 is direction.
	 */
	dy = buf[2] & 0x7f;
	dy *= ((buf[0] >> 3) & 0x01) ? -1 : 1;

	/*
	 * Get button state. It's the low three bits
	 * (क्रम three buttons) of byte 0.
	 */
	left	= buf[0] & 0x04;
	middle	= buf[0] & 0x02;
	right	= buf[0] & 0x01;

	vsxxxaa_drop_bytes(mouse, 3);

	DBG(KERN_INFO "%s on %s: dx=%d, dy=%d, buttons=%s%s%s\n",
	    mouse->name, mouse->phys, dx, dy,
	    left ? "L" : "l", middle ? "M" : "m", right ? "R" : "r");

	/*
	 * Report what we've found so far...
	 */
	input_report_key(dev, BTN_LEFT, left);
	input_report_key(dev, BTN_MIDDLE, middle);
	input_report_key(dev, BTN_RIGHT, right);
	input_report_key(dev, BTN_TOUCH, 0);
	input_report_rel(dev, REL_X, dx);
	input_report_rel(dev, REL_Y, dy);
	input_sync(dev);
पूर्ण

अटल व्योम vsxxxaa_handle_ABS_packet(काष्ठा vsxxxaa *mouse)
अणु
	काष्ठा input_dev *dev = mouse->dev;
	अचिन्हित अक्षर *buf = mouse->buf;
	पूर्णांक left, middle, right, touch;
	पूर्णांक x, y;

	/*
	 * Tablet position / button packet
	 *
	 * [0]:	1	1	0	B4	B3	B2	B1	Pr
	 * [1]:	0	0	X5	X4	X3	X2	X1	X0
	 * [2]:	0	0	X11	X10	X9	X8	X7	X6
	 * [3]:	0	0	Y5	Y4	Y3	Y2	Y1	Y0
	 * [4]:	0	0	Y11	Y10	Y9	Y8	Y7	Y6
	 */

	/*
	 * Get X/Y position. Y axis needs to be inverted since VSXXX-AB
	 * counts करोwn->top जबतक monitor counts top->bottom.
	 */
	x = ((buf[2] & 0x3f) << 6) | (buf[1] & 0x3f);
	y = ((buf[4] & 0x3f) << 6) | (buf[3] & 0x3f);
	y = 1023 - y;

	/*
	 * Get button state. It's bits <4..1> of byte 0.
	 */
	left	= buf[0] & 0x02;
	middle	= buf[0] & 0x04;
	right	= buf[0] & 0x08;
	touch	= buf[0] & 0x10;

	vsxxxaa_drop_bytes(mouse, 5);

	DBG(KERN_INFO "%s on %s: x=%d, y=%d, buttons=%s%s%s%s\n",
	    mouse->name, mouse->phys, x, y,
	    left ? "L" : "l", middle ? "M" : "m",
	    right ? "R" : "r", touch ? "T" : "t");

	/*
	 * Report what we've found so far...
	 */
	input_report_key(dev, BTN_LEFT, left);
	input_report_key(dev, BTN_MIDDLE, middle);
	input_report_key(dev, BTN_RIGHT, right);
	input_report_key(dev, BTN_TOUCH, touch);
	input_report_असल(dev, ABS_X, x);
	input_report_असल(dev, ABS_Y, y);
	input_sync(dev);
पूर्ण

अटल व्योम vsxxxaa_handle_POR_packet(काष्ठा vsxxxaa *mouse)
अणु
	काष्ठा input_dev *dev = mouse->dev;
	अचिन्हित अक्षर *buf = mouse->buf;
	पूर्णांक left, middle, right;
	अचिन्हित अक्षर error;

	/*
	 * Check क्रम Power-On-Reset packets. These are sent out
	 * after plugging the mouse in, or when explicitly
	 * requested by sending 'T'.
	 *
	 * [0]:	1	0	1	0	R3	R2	R1	R0
	 * [1]:	0	M2	M1	M0	D3	D2	D1	D0
	 * [2]:	0	E6	E5	E4	E3	E2	E1	E0
	 * [3]:	0	0	0	0	0	Left	Middle	Right
	 *
	 * M: manufacturer location code
	 * R: revision code
	 * E: Error code. If it's in the range of 0x00..0x1f, only some
	 *    minor problem occurred. Errors >= 0x20 are considered bad
	 *    and the device may not work properly...
	 * D: <0010> == mouse, <0100> == tablet
	 */

	mouse->version = buf[0] & 0x0f;
	mouse->country = (buf[1] >> 4) & 0x07;
	mouse->type = buf[1] & 0x0f;
	error = buf[2] & 0x7f;

	/*
	 * Get button state. It's the low three bits
	 * (क्रम three buttons) of byte 0. Maybe even the bit <3>
	 * has some meaning अगर a tablet is attached.
	 */
	left	= buf[0] & 0x04;
	middle	= buf[0] & 0x02;
	right	= buf[0] & 0x01;

	vsxxxaa_drop_bytes(mouse, 4);
	vsxxxaa_detection_करोne(mouse);

	अगर (error <= 0x1f) अणु
		/* No (serious) error. Report buttons */
		input_report_key(dev, BTN_LEFT, left);
		input_report_key(dev, BTN_MIDDLE, middle);
		input_report_key(dev, BTN_RIGHT, right);
		input_report_key(dev, BTN_TOUCH, 0);
		input_sync(dev);

		अगर (error != 0)
			prपूर्णांकk(KERN_INFO "Your %s on %s reports error=0x%02x\n",
				mouse->name, mouse->phys, error);

	पूर्ण

	/*
	 * If the mouse was hot-plugged, we need to क्रमce dअगरferential mode
	 * now... However, give it a second to recover from it's reset.
	 */
	prपूर्णांकk(KERN_NOTICE
		"%s on %s: Forcing standard packet format, "
		"incremental streaming mode and 72 samples/sec\n",
		mouse->name, mouse->phys);
	serio_ग_लिखो(mouse->serio, 'S');	/* Standard क्रमmat */
	mdelay(50);
	serio_ग_लिखो(mouse->serio, 'R');	/* Incremental */
	mdelay(50);
	serio_ग_लिखो(mouse->serio, 'L');	/* 72 samples/sec */
पूर्ण

अटल व्योम vsxxxaa_parse_buffer(काष्ठा vsxxxaa *mouse)
अणु
	अचिन्हित अक्षर *buf = mouse->buf;
	पूर्णांक stray_bytes;

	/*
	 * Parse buffer to death...
	 */
	करो अणु
		/*
		 * Out of sync? Throw away what we करोn't understand. Each
		 * packet starts with a byte whose bit 7 is set. Unhandled
		 * packets (ie. which we करोn't know about or simply b0rk3d
		 * data...) will get shअगरted out of the buffer after some
		 * activity on the mouse.
		 */
		जबतक (mouse->count > 0 && !IS_HDR_BYTE(buf[0])) अणु
			prपूर्णांकk(KERN_ERR "%s on %s: Dropping a byte to regain "
				"sync with mouse data stream...\n",
				mouse->name, mouse->phys);
			vsxxxaa_drop_bytes(mouse, 1);
		पूर्ण

		/*
		 * Check क्रम packets we know about.
		 */

		अगर (vsxxxaa_smells_like_packet(mouse, VSXXXAA_PACKET_REL, 3)) अणु
			/* Check क्रम broken packet */
			stray_bytes = vsxxxaa_check_packet(mouse, 3);
			अगर (!stray_bytes)
				vsxxxaa_handle_REL_packet(mouse);

		पूर्ण अन्यथा अगर (vsxxxaa_smells_like_packet(mouse,
						      VSXXXAA_PACKET_ABS, 5)) अणु
			/* Check क्रम broken packet */
			stray_bytes = vsxxxaa_check_packet(mouse, 5);
			अगर (!stray_bytes)
				vsxxxaa_handle_ABS_packet(mouse);

		पूर्ण अन्यथा अगर (vsxxxaa_smells_like_packet(mouse,
						      VSXXXAA_PACKET_POR, 4)) अणु
			/* Check क्रम broken packet */
			stray_bytes = vsxxxaa_check_packet(mouse, 4);
			अगर (!stray_bytes)
				vsxxxaa_handle_POR_packet(mouse);

		पूर्ण अन्यथा अणु
			अवरोध; /* No REL, ABS or POR packet found */
		पूर्ण

		अगर (stray_bytes > 0) अणु
			prपूर्णांकk(KERN_ERR "Dropping %d bytes now...\n",
				stray_bytes);
			vsxxxaa_drop_bytes(mouse, stray_bytes);
		पूर्ण

	पूर्ण जबतक (1);
पूर्ण

अटल irqवापस_t vsxxxaa_पूर्णांकerrupt(काष्ठा serio *serio,
				     अचिन्हित अक्षर data, अचिन्हित पूर्णांक flags)
अणु
	काष्ठा vsxxxaa *mouse = serio_get_drvdata(serio);

	vsxxxaa_queue_byte(mouse, data);
	vsxxxaa_parse_buffer(mouse);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम vsxxxaa_disconnect(काष्ठा serio *serio)
अणु
	काष्ठा vsxxxaa *mouse = serio_get_drvdata(serio);

	serio_बंद(serio);
	serio_set_drvdata(serio, शून्य);
	input_unरेजिस्टर_device(mouse->dev);
	kमुक्त(mouse);
पूर्ण

अटल पूर्णांक vsxxxaa_connect(काष्ठा serio *serio, काष्ठा serio_driver *drv)
अणु
	काष्ठा vsxxxaa *mouse;
	काष्ठा input_dev *input_dev;
	पूर्णांक err = -ENOMEM;

	mouse = kzalloc(माप(काष्ठा vsxxxaa), GFP_KERNEL);
	input_dev = input_allocate_device();
	अगर (!mouse || !input_dev)
		जाओ fail1;

	mouse->dev = input_dev;
	mouse->serio = serio;
	strlcat(mouse->name, "DEC VSXXX-AA/-GA mouse or VSXXX-AB digitizer",
		 माप(mouse->name));
	snम_लिखो(mouse->phys, माप(mouse->phys), "%s/input0", serio->phys);

	input_dev->name = mouse->name;
	input_dev->phys = mouse->phys;
	input_dev->id.bustype = BUS_RS232;
	input_dev->dev.parent = &serio->dev;

	__set_bit(EV_KEY, input_dev->evbit);		/* We have buttons */
	__set_bit(EV_REL, input_dev->evbit);
	__set_bit(EV_ABS, input_dev->evbit);
	__set_bit(BTN_LEFT, input_dev->keybit);		/* We have 3 buttons */
	__set_bit(BTN_MIDDLE, input_dev->keybit);
	__set_bit(BTN_RIGHT, input_dev->keybit);
	__set_bit(BTN_TOUCH, input_dev->keybit);	/* ...and Tablet */
	__set_bit(REL_X, input_dev->relbit);
	__set_bit(REL_Y, input_dev->relbit);
	input_set_असल_params(input_dev, ABS_X, 0, 1023, 0, 0);
	input_set_असल_params(input_dev, ABS_Y, 0, 1023, 0, 0);

	serio_set_drvdata(serio, mouse);

	err = serio_खोलो(serio, drv);
	अगर (err)
		जाओ fail2;

	/*
	 * Request selftest. Standard packet क्रमmat and dअगरferential
	 * mode will be requested after the device ID'ed successfully.
	 */
	serio_ग_लिखो(serio, 'T'); /* Test */

	err = input_रेजिस्टर_device(input_dev);
	अगर (err)
		जाओ fail3;

	वापस 0;

 fail3:	serio_बंद(serio);
 fail2:	serio_set_drvdata(serio, शून्य);
 fail1:	input_मुक्त_device(input_dev);
	kमुक्त(mouse);
	वापस err;
पूर्ण

अटल काष्ठा serio_device_id vsxxaa_serio_ids[] = अणु
	अणु
		.type	= SERIO_RS232,
		.proto	= SERIO_VSXXXAA,
		.id	= SERIO_ANY,
		.extra	= SERIO_ANY,
	पूर्ण,
	अणु 0 पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(serio, vsxxaa_serio_ids);

अटल काष्ठा serio_driver vsxxxaa_drv = अणु
	.driver		= अणु
		.name	= "vsxxxaa",
	पूर्ण,
	.description	= DRIVER_DESC,
	.id_table	= vsxxaa_serio_ids,
	.connect	= vsxxxaa_connect,
	.पूर्णांकerrupt	= vsxxxaa_पूर्णांकerrupt,
	.disconnect	= vsxxxaa_disconnect,
पूर्ण;

module_serio_driver(vsxxxaa_drv);
