<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Device driver क्रम the via ADB on (many) Mac II-class machines
 *
 * Based on the original ADB keyboard handler Copyright (c) 1997 Alan Cox
 * Also derived from code Copyright (C) 1996 Paul Mackerras.
 *
 * With various updates provided over the years by Michael Schmitz,
 * Guideo Koerber and others.
 *
 * Reग_लिखो क्रम Unअगरied ADB by Joshua M. Thompson (funaho@jurai.org)
 *
 * 1999-08-02 (jmt) - Initial reग_लिखो क्रम Unअगरied ADB.
 * 2000-03-29 Tony Mantler <tonym@mac.linux-m68k.org>
 *            - Big overhaul, should actually work now.
 * 2006-12-31 Finn Thain - Another overhaul.
 *
 * Suggested पढ़ोing:
 *   Inside Macपूर्णांकosh, ch. 5 ADB Manager
 *   Guide to the Macinstosh Family Hardware, ch. 8 Apple Desktop Bus
 *   Rockwell R6522 VIA datasheet
 *
 * Apple's "ADB Analyzer" bus snअगरfer is invaluable:
 *   ftp://ftp.apple.com/developer/Tool_Chest/Devices_-_Hardware/Apple_Desktop_Bus/
 */

#समावेश <मानकतर्क.स>
#समावेश <linux/types.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kernel.h>
#समावेश <linux/delay.h>
#समावेश <linux/adb.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/init.h>
#समावेश <यंत्र/macपूर्णांकosh.h>
#समावेश <यंत्र/macपूर्णांकs.h>
#समावेश <यंत्र/mac_via.h>

अटल अस्थिर अचिन्हित अक्षर *via;

/* VIA रेजिस्टरs - spaced 0x200 bytes apart */
#घोषणा RS		0x200		/* skip between रेजिस्टरs */
#घोषणा B		0		/* B-side data */
#घोषणा A		RS		/* A-side data */
#घोषणा सूचीB		(2*RS)		/* B-side direction (1=output) */
#घोषणा सूचीA		(3*RS)		/* A-side direction (1=output) */
#घोषणा T1CL		(4*RS)		/* Timer 1 ctr/latch (low 8 bits) */
#घोषणा T1CH		(5*RS)		/* Timer 1 counter (high 8 bits) */
#घोषणा T1LL		(6*RS)		/* Timer 1 latch (low 8 bits) */
#घोषणा T1LH		(7*RS)		/* Timer 1 latch (high 8 bits) */
#घोषणा T2CL		(8*RS)		/* Timer 2 ctr/latch (low 8 bits) */
#घोषणा T2CH		(9*RS)		/* Timer 2 counter (high 8 bits) */
#घोषणा SR		(10*RS)		/* Shअगरt रेजिस्टर */
#घोषणा ACR		(11*RS)		/* Auxiliary control रेजिस्टर */
#घोषणा PCR		(12*RS)		/* Peripheral control रेजिस्टर */
#घोषणा IFR		(13*RS)		/* Interrupt flag रेजिस्टर */
#घोषणा IER		(14*RS)		/* Interrupt enable रेजिस्टर */
#घोषणा ANH		(15*RS)		/* A-side data, no handshake */

/* Bits in B data रेजिस्टर: all active low */
#घोषणा CTLR_IRQ	0x08		/* Controller rcv status (input) */
#घोषणा ST_MASK		0x30		/* mask क्रम selecting ADB state bits */

/* Bits in ACR */
#घोषणा SR_CTRL		0x1c		/* Shअगरt रेजिस्टर control bits */
#घोषणा SR_EXT		0x0c		/* Shअगरt on बाह्यal घड़ी */
#घोषणा SR_OUT		0x10		/* Shअगरt out अगर 1 */

/* Bits in IFR and IER */
#घोषणा IER_SET		0x80		/* set bits in IER */
#घोषणा IER_CLR		0		/* clear bits in IER */
#घोषणा SR_INT		0x04		/* Shअगरt रेजिस्टर full/empty */

/* ADB transaction states according to GMHW */
#घोषणा ST_CMD		0x00		/* ADB state: command byte */
#घोषणा ST_EVEN		0x10		/* ADB state: even data byte */
#घोषणा ST_ODD		0x20		/* ADB state: odd data byte */
#घोषणा ST_IDLE		0x30		/* ADB state: idle, nothing to send */

/* ADB command byte काष्ठाure */
#घोषणा ADDR_MASK	0xF0
#घोषणा CMD_MASK	0x0F
#घोषणा OP_MASK		0x0C
#घोषणा TALK		0x0C

अटल पूर्णांक macii_init_via(व्योम);
अटल व्योम macii_start(व्योम);
अटल irqवापस_t macii_पूर्णांकerrupt(पूर्णांक irq, व्योम *arg);
अटल व्योम macii_queue_poll(व्योम);

अटल पूर्णांक macii_probe(व्योम);
अटल पूर्णांक macii_init(व्योम);
अटल पूर्णांक macii_send_request(काष्ठा adb_request *req, पूर्णांक sync);
अटल पूर्णांक macii_ग_लिखो(काष्ठा adb_request *req);
अटल पूर्णांक macii_स्वतःpoll(पूर्णांक devs);
अटल व्योम macii_poll(व्योम);
अटल पूर्णांक macii_reset_bus(व्योम);

काष्ठा adb_driver via_macii_driver = अणु
	.name         = "Mac II",
	.probe        = macii_probe,
	.init         = macii_init,
	.send_request = macii_send_request,
	.स्वतःpoll     = macii_स्वतःpoll,
	.poll         = macii_poll,
	.reset_bus    = macii_reset_bus,
पूर्ण;

अटल क्रमागत macii_state अणु
	idle,
	sending,
	पढ़ोing,
पूर्ण macii_state;

अटल काष्ठा adb_request *current_req; /* first request काष्ठा in the queue */
अटल काष्ठा adb_request *last_req;     /* last request काष्ठा in the queue */
अटल अचिन्हित अक्षर reply_buf[16];        /* storage क्रम स्वतःpolled replies */
अटल अचिन्हित अक्षर *reply_ptr;     /* next byte in reply_buf or req->reply */
अटल bool पढ़ोing_reply;       /* store reply in reply_buf अन्यथा req->reply */
अटल पूर्णांक data_index;      /* index of the next byte to send from req->data */
अटल पूर्णांक reply_len; /* number of bytes received in reply_buf or req->reply */
अटल पूर्णांक status;          /* VIA's ADB status bits captured upon पूर्णांकerrupt */
अटल bool bus_समयout;                   /* no data was sent by the device */
अटल bool srq_निश्चितed;    /* have to poll क्रम the device that निश्चितed it */
अटल u8 last_cmd;              /* the most recent command byte transmitted */
अटल u8 last_talk_cmd;    /* the most recent Talk command byte transmitted */
अटल u8 last_poll_cmd; /* the most recent Talk R0 command byte transmitted */
अटल अचिन्हित पूर्णांक स्वतःpoll_devs;  /* bits set are device addresses to poll */

/* Check क्रम MacII style ADB */
अटल पूर्णांक macii_probe(व्योम)
अणु
	अगर (macपूर्णांकosh_config->adb_type != MAC_ADB_II)
		वापस -ENODEV;

	via = via1;

	pr_info("adb: Mac II ADB Driver v1.0 for Unified ADB\n");
	वापस 0;
पूर्ण

/* Initialize the driver */
अटल पूर्णांक macii_init(व्योम)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक err;

	local_irq_save(flags);

	err = macii_init_via();
	अगर (err)
		जाओ out;

	err = request_irq(IRQ_MAC_ADB, macii_पूर्णांकerrupt, 0, "ADB",
			  macii_पूर्णांकerrupt);
	अगर (err)
		जाओ out;

	macii_state = idle;
out:
	local_irq_restore(flags);
	वापस err;
पूर्ण

/* initialize the hardware */
अटल पूर्णांक macii_init_via(व्योम)
अणु
	अचिन्हित अक्षर x;

	/* We want CTLR_IRQ as input and ST_EVEN | ST_ODD as output lines. */
	via[सूचीB] = (via[सूचीB] | ST_EVEN | ST_ODD) & ~CTLR_IRQ;

	/* Set up state: idle */
	via[B] |= ST_IDLE;

	/* Shअगरt रेजिस्टर on input */
	via[ACR] = (via[ACR] & ~SR_CTRL) | SR_EXT;

	/* Wipe any pending data and पूर्णांक */
	x = via[SR];

	वापस 0;
पूर्ण

/* Send an ADB poll (Talk Register 0 command prepended to the request queue) */
अटल व्योम macii_queue_poll(व्योम)
अणु
	अटल काष्ठा adb_request req;
	अचिन्हित अक्षर poll_command;
	अचिन्हित पूर्णांक poll_addr;

	/* This only polls devices in the स्वतःpoll list, which assumes that
	 * unprobed devices never निश्चित SRQ. That could happen अगर a device was
	 * plugged in after the adb bus scan. Unplugging it again will resolve
	 * the problem. This behaviour is similar to MacOS.
	 */
	अगर (!स्वतःpoll_devs)
		वापस;

	/* The device most recently polled may not be the best device to poll
	 * right now. Some other device(s) may have संकेतled SRQ (the active
	 * device won't करो that). Or the स्वतःpoll list may have been changed.
	 * Try polling the next higher address.
	 */
	poll_addr = (last_poll_cmd & ADDR_MASK) >> 4;
	अगर ((srq_निश्चितed && last_cmd == last_poll_cmd) ||
	    !(स्वतःpoll_devs & (1 << poll_addr))) अणु
		अचिन्हित पूर्णांक higher_devs;

		higher_devs = स्वतःpoll_devs & -(1 << (poll_addr + 1));
		poll_addr = ffs(higher_devs ? higher_devs : स्वतःpoll_devs) - 1;
	पूर्ण

	/* Send a Talk Register 0 command */
	poll_command = ADB_READREG(poll_addr, 0);

	/* No need to repeat this Talk command. The transceiver will करो that
	 * as दीर्घ as it is idle.
	 */
	अगर (poll_command == last_cmd)
		वापस;

	adb_request(&req, शून्य, ADBREQ_NOSEND, 1, poll_command);

	req.sent = 0;
	req.complete = 0;
	req.reply_len = 0;
	req.next = current_req;

	अगर (WARN_ON(current_req)) अणु
		current_req = &req;
	पूर्ण अन्यथा अणु
		current_req = &req;
		last_req = &req;
	पूर्ण
पूर्ण

/* Send an ADB request; अगर sync, poll out the reply 'till it's करोne */
अटल पूर्णांक macii_send_request(काष्ठा adb_request *req, पूर्णांक sync)
अणु
	पूर्णांक err;

	err = macii_ग_लिखो(req);
	अगर (err)
		वापस err;

	अगर (sync)
		जबतक (!req->complete)
			macii_poll();

	वापस 0;
पूर्ण

/* Send an ADB request (append to request queue) */
अटल पूर्णांक macii_ग_लिखो(काष्ठा adb_request *req)
अणु
	अचिन्हित दीर्घ flags;

	अगर (req->nbytes < 2 || req->data[0] != ADB_PACKET || req->nbytes > 15) अणु
		req->complete = 1;
		वापस -EINVAL;
	पूर्ण

	req->next = शून्य;
	req->sent = 0;
	req->complete = 0;
	req->reply_len = 0;

	local_irq_save(flags);

	अगर (current_req != शून्य) अणु
		last_req->next = req;
		last_req = req;
	पूर्ण अन्यथा अणु
		current_req = req;
		last_req = req;
		अगर (macii_state == idle)
			macii_start();
	पूर्ण

	local_irq_restore(flags);

	वापस 0;
पूर्ण

/* Start स्वतः-polling */
अटल पूर्णांक macii_स्वतःpoll(पूर्णांक devs)
अणु
	अचिन्हित दीर्घ flags;

	local_irq_save(flags);

	/* bit 1 == device 1, and so on. */
	स्वतःpoll_devs = (अचिन्हित पूर्णांक)devs & 0xFFFE;

	अगर (!current_req) अणु
		macii_queue_poll();
		अगर (current_req && macii_state == idle)
			macii_start();
	पूर्ण

	local_irq_restore(flags);

	वापस 0;
पूर्ण

/* Prod the chip without पूर्णांकerrupts */
अटल व्योम macii_poll(व्योम)
अणु
	macii_पूर्णांकerrupt(0, शून्य);
पूर्ण

/* Reset the bus */
अटल पूर्णांक macii_reset_bus(व्योम)
अणु
	काष्ठा adb_request req;

	/* Command = 0, Address = ignored */
	adb_request(&req, शून्य, ADBREQ_NOSEND, 1, ADB_BUSRESET);
	macii_send_request(&req, 1);

	/* Don't want any more requests during the Global Reset low समय. */
	udelay(3000);

	वापस 0;
पूर्ण

/* Start sending ADB packet */
अटल व्योम macii_start(व्योम)
अणु
	काष्ठा adb_request *req;

	req = current_req;

	/* Now send it. Be careful though, that first byte of the request
	 * is actually ADB_PACKET; the real data begins at index 1!
	 * And req->nbytes is the number of bytes of real data plus one.
	 */

	/* Output mode */
	via[ACR] |= SR_OUT;
	/* Load data */
	via[SR] = req->data[1];
	/* set ADB state to 'command' */
	via[B] = (via[B] & ~ST_MASK) | ST_CMD;

	macii_state = sending;
	data_index = 2;

	bus_समयout = false;
	srq_निश्चितed = false;
पूर्ण

/*
 * The notorious ADB पूर्णांकerrupt handler - करोes all of the protocol handling.
 * Relies on the ADB controller sending and receiving data, thereby
 * generating shअगरt रेजिस्टर पूर्णांकerrupts (SR_INT) क्रम us. This means there has
 * to be activity on the ADB bus. The chip will poll to achieve this.
 *
 * The VIA Port B output संकेतling works as follows. After the ADB transceiver
 * sees a transition on the PB4 and PB5 lines it will crank over the VIA shअगरt
 * रेजिस्टर which eventually उठाओs the SR_INT पूर्णांकerrupt. The PB4/PB5 outमाला_दो
 * are toggled with each byte as the ADB transaction progresses.
 *
 * Request with no reply expected (and empty transceiver buffer):
 *     CMD -> IDLE
 * Request with expected reply packet (or with buffered स्वतःpoll packet):
 *     CMD -> EVEN -> ODD -> EVEN -> ... -> IDLE
 * Unsolicited packet:
 *     IDLE -> EVEN -> ODD -> EVEN -> ... -> IDLE
 */
अटल irqवापस_t macii_पूर्णांकerrupt(पूर्णांक irq, व्योम *arg)
अणु
	पूर्णांक x;
	काष्ठा adb_request *req;
	अचिन्हित दीर्घ flags;

	local_irq_save(flags);

	अगर (!arg) अणु
		/* Clear the SR IRQ flag when polling. */
		अगर (via[IFR] & SR_INT)
			via[IFR] = SR_INT;
		अन्यथा अणु
			local_irq_restore(flags);
			वापस IRQ_NONE;
		पूर्ण
	पूर्ण

	status = via[B] & (ST_MASK | CTLR_IRQ);

	चयन (macii_state) अणु
	हाल idle:
		WARN_ON((status & ST_MASK) != ST_IDLE);

		reply_ptr = reply_buf;
		पढ़ोing_reply = false;

		bus_समयout = false;
		srq_निश्चितed = false;

		x = via[SR];

		अगर (!(status & CTLR_IRQ)) अणु
			/* /CTLR_IRQ निश्चितed in idle state means we must
			 * पढ़ो an स्वतःpoll reply from the transceiver buffer.
			 */
			macii_state = पढ़ोing;
			*reply_ptr = x;
			reply_len = 1;
		पूर्ण अन्यथा अणु
			/* bus समयout */
			reply_len = 0;
			अवरोध;
		पूर्ण

		/* set ADB state = even क्रम first data byte */
		via[B] = (via[B] & ~ST_MASK) | ST_EVEN;
		अवरोध;

	हाल sending:
		req = current_req;

		अगर (status == (ST_CMD | CTLR_IRQ)) अणु
			/* /CTLR_IRQ de-निश्चितed after the command byte means
			 * the host can जारी with the transaction.
			 */

			/* Store command byte */
			last_cmd = req->data[1];
			अगर ((last_cmd & OP_MASK) == TALK) अणु
				last_talk_cmd = last_cmd;
				अगर ((last_cmd & CMD_MASK) == ADB_READREG(0, 0))
					last_poll_cmd = last_cmd;
			पूर्ण
		पूर्ण

		अगर (status == ST_CMD) अणु
			/* /CTLR_IRQ निश्चितed after the command byte means we
			 * must पढ़ो an स्वतःpoll reply. The first byte was
			 * lost because the shअगरt रेजिस्टर was an output.
			 */
			macii_state = पढ़ोing;

			पढ़ोing_reply = false;
			reply_ptr = reply_buf;
			*reply_ptr = last_talk_cmd;
			reply_len = 1;

			/* reset to shअगरt in */
			via[ACR] &= ~SR_OUT;
			x = via[SR];
		पूर्ण अन्यथा अगर (data_index >= req->nbytes) अणु
			req->sent = 1;

			अगर (req->reply_expected) अणु
				macii_state = पढ़ोing;

				पढ़ोing_reply = true;
				reply_ptr = req->reply;
				*reply_ptr = req->data[1];
				reply_len = 1;

				via[ACR] &= ~SR_OUT;
				x = via[SR];
			पूर्ण अन्यथा अगर ((req->data[1] & OP_MASK) == TALK) अणु
				macii_state = पढ़ोing;

				पढ़ोing_reply = false;
				reply_ptr = reply_buf;
				*reply_ptr = req->data[1];
				reply_len = 1;

				via[ACR] &= ~SR_OUT;
				x = via[SR];

				req->complete = 1;
				current_req = req->next;
				अगर (req->करोne)
					(*req->करोne)(req);
			पूर्ण अन्यथा अणु
				macii_state = idle;

				req->complete = 1;
				current_req = req->next;
				अगर (req->करोne)
					(*req->करोne)(req);
				अवरोध;
			पूर्ण
		पूर्ण अन्यथा अणु
			via[SR] = req->data[data_index++];
		पूर्ण

		अगर ((via[B] & ST_MASK) == ST_CMD) अणु
			/* just sent the command byte, set to EVEN */
			via[B] = (via[B] & ~ST_MASK) | ST_EVEN;
		पूर्ण अन्यथा अणु
			/* invert state bits, toggle ODD/EVEN */
			via[B] ^= ST_MASK;
		पूर्ण
		अवरोध;

	हाल पढ़ोing:
		x = via[SR];
		WARN_ON((status & ST_MASK) == ST_CMD ||
			(status & ST_MASK) == ST_IDLE);

		अगर (!(status & CTLR_IRQ)) अणु
			अगर (status == ST_EVEN && reply_len == 1) अणु
				bus_समयout = true;
			पूर्ण अन्यथा अगर (status == ST_ODD && reply_len == 2) अणु
				srq_निश्चितed = true;
			पूर्ण अन्यथा अणु
				macii_state = idle;

				अगर (bus_समयout)
					reply_len = 0;

				अगर (पढ़ोing_reply) अणु
					काष्ठा adb_request *req = current_req;

					req->reply_len = reply_len;

					req->complete = 1;
					current_req = req->next;
					अगर (req->करोne)
						(*req->करोne)(req);
				पूर्ण अन्यथा अगर (reply_len && स्वतःpoll_devs &&
					   reply_buf[0] == last_poll_cmd) अणु
					adb_input(reply_buf, reply_len, 1);
				पूर्ण
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (reply_len < ARRAY_SIZE(reply_buf)) अणु
			reply_ptr++;
			*reply_ptr = x;
			reply_len++;
		पूर्ण

		/* invert state bits, toggle ODD/EVEN */
		via[B] ^= ST_MASK;
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

	अगर (macii_state == idle) अणु
		अगर (!current_req)
			macii_queue_poll();

		अगर (current_req)
			macii_start();

		अगर (macii_state == idle) अणु
			via[ACR] &= ~SR_OUT;
			x = via[SR];
			via[B] = (via[B] & ~ST_MASK) | ST_IDLE;
		पूर्ण
	पूर्ण

	local_irq_restore(flags);
	वापस IRQ_HANDLED;
पूर्ण
