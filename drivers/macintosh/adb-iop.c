<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * I/O Processor (IOP) ADB Driver
 * Written and (C) 1999 by Joshua M. Thompson (funaho@jurai.org)
 * Based on via-cuda.c by Paul Mackerras.
 *
 * 1999-07-01 (jmt) - First implementation क्रम new driver architecture.
 *
 * 1999-07-31 (jmt) - First working version.
 */

#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mm.h>
#समावेश <linux/delay.h>
#समावेश <linux/init.h>

#समावेश <यंत्र/macपूर्णांकosh.h>
#समावेश <यंत्र/macपूर्णांकs.h>
#समावेश <यंत्र/mac_iop.h>
#समावेश <यंत्र/adb_iop.h>
#समावेश <यंत्र/unaligned.h>

#समावेश <linux/adb.h>

अटल काष्ठा adb_request *current_req;
अटल काष्ठा adb_request *last_req;
अटल अचिन्हित पूर्णांक स्वतःpoll_devs;
अटल u8 स्वतःpoll_addr;

अटल क्रमागत adb_iop_state अणु
	idle,
	sending,
	aरुकोing_reply
पूर्ण adb_iop_state;

अटल व्योम adb_iop_start(व्योम);
अटल पूर्णांक adb_iop_probe(व्योम);
अटल पूर्णांक adb_iop_init(व्योम);
अटल पूर्णांक adb_iop_send_request(काष्ठा adb_request *, पूर्णांक);
अटल पूर्णांक adb_iop_ग_लिखो(काष्ठा adb_request *);
अटल पूर्णांक adb_iop_स्वतःpoll(पूर्णांक);
अटल व्योम adb_iop_poll(व्योम);
अटल पूर्णांक adb_iop_reset_bus(व्योम);

/* ADB command byte काष्ठाure */
#घोषणा ADDR_MASK       0xF0
#घोषणा OP_MASK         0x0C
#घोषणा TALK            0x0C

काष्ठा adb_driver adb_iop_driver = अणु
	.name         = "ISM IOP",
	.probe        = adb_iop_probe,
	.init         = adb_iop_init,
	.send_request = adb_iop_send_request,
	.स्वतःpoll     = adb_iop_स्वतःpoll,
	.poll         = adb_iop_poll,
	.reset_bus    = adb_iop_reset_bus
पूर्ण;

अटल व्योम adb_iop_करोne(व्योम)
अणु
	काष्ठा adb_request *req = current_req;

	adb_iop_state = idle;

	req->complete = 1;
	current_req = req->next;
	अगर (req->करोne)
		(*req->करोne)(req);

	अगर (adb_iop_state == idle)
		adb_iop_start();
पूर्ण

/*
 * Completion routine क्रम ADB commands sent to the IOP.
 *
 * This will be called when a packet has been successfully sent.
 */

अटल व्योम adb_iop_complete(काष्ठा iop_msg *msg)
अणु
	अचिन्हित दीर्घ flags;

	local_irq_save(flags);

	adb_iop_state = aरुकोing_reply;

	local_irq_restore(flags);
पूर्ण

/*
 * Listen क्रम ADB messages from the IOP.
 *
 * This will be called when unsolicited IOP messages are received.
 * These IOP messages can carry ADB स्वतःpoll responses and also occur
 * after explicit ADB commands.
 */

अटल व्योम adb_iop_listen(काष्ठा iop_msg *msg)
अणु
	काष्ठा adb_iopmsg *amsg = (काष्ठा adb_iopmsg *)msg->message;
	u8 addr = (amsg->cmd & ADDR_MASK) >> 4;
	u8 op = amsg->cmd & OP_MASK;
	अचिन्हित दीर्घ flags;
	bool req_करोne = false;

	local_irq_save(flags);

	/* Responses to Talk commands may be unsolicited as they are
	 * produced when the IOP polls devices. They are mostly समयouts.
	 */
	अगर (op == TALK && ((1 << addr) & स्वतःpoll_devs))
		स्वतःpoll_addr = addr;

	चयन (amsg->flags & (ADB_IOP_EXPLICIT |
			       ADB_IOP_AUTOPOLL |
			       ADB_IOP_TIMEOUT)) अणु
	हाल ADB_IOP_EXPLICIT:
	हाल ADB_IOP_EXPLICIT | ADB_IOP_TIMEOUT:
		अगर (adb_iop_state == aरुकोing_reply) अणु
			काष्ठा adb_request *req = current_req;

			अगर (req->reply_expected) अणु
				req->reply_len = amsg->count + 1;
				स_नकल(req->reply, &amsg->cmd, req->reply_len);
			पूर्ण

			req_करोne = true;
		पूर्ण
		अवरोध;
	हाल ADB_IOP_AUTOPOLL:
		अगर (((1 << addr) & स्वतःpoll_devs) &&
		    amsg->cmd == ADB_READREG(addr, 0))
			adb_input(&amsg->cmd, amsg->count + 1, 1);
		अवरोध;
	पूर्ण
	msg->reply[0] = स्वतःpoll_addr ? ADB_IOP_AUTOPOLL : 0;
	msg->reply[1] = 0;
	msg->reply[2] = स्वतःpoll_addr ? ADB_READREG(स्वतःpoll_addr, 0) : 0;
	iop_complete_message(msg);

	अगर (req_करोne)
		adb_iop_करोne();

	local_irq_restore(flags);
पूर्ण

/*
 * Start sending an ADB packet, IOP style
 *
 * There isn't much to करो other than hand the packet over to the IOP
 * after encapsulating it in an adb_iopmsg.
 */

अटल व्योम adb_iop_start(व्योम)
अणु
	काष्ठा adb_request *req;
	काष्ठा adb_iopmsg amsg;

	/* get the packet to send */
	req = current_req;
	अगर (!req)
		वापस;

	/* The IOP takes MacII-style packets, so strip the initial
	 * ADB_PACKET byte.
	 */
	amsg.flags = ADB_IOP_EXPLICIT;
	amsg.count = req->nbytes - 2;

	/* amsg.data immediately follows amsg.cmd, effectively making
	 * &amsg.cmd a poपूर्णांकer to the beginning of a full ADB packet.
	 */
	स_नकल(&amsg.cmd, req->data + 1, req->nbytes - 1);

	req->sent = 1;
	adb_iop_state = sending;

	/* Now send it. The IOP manager will call adb_iop_complete
	 * when the message has been sent.
	 */
	iop_send_message(ADB_IOP, ADB_CHAN, req, माप(amsg), (__u8 *)&amsg,
			 adb_iop_complete);
पूर्ण

अटल पूर्णांक adb_iop_probe(व्योम)
अणु
	अगर (!iop_ism_present)
		वापस -ENODEV;
	वापस 0;
पूर्ण

अटल पूर्णांक adb_iop_init(व्योम)
अणु
	pr_info("adb: IOP ISM driver v0.4 for Unified ADB\n");
	iop_listen(ADB_IOP, ADB_CHAN, adb_iop_listen, "ADB");
	वापस 0;
पूर्ण

अटल पूर्णांक adb_iop_send_request(काष्ठा adb_request *req, पूर्णांक sync)
अणु
	पूर्णांक err;

	err = adb_iop_ग_लिखो(req);
	अगर (err)
		वापस err;

	अगर (sync) अणु
		जबतक (!req->complete)
			adb_iop_poll();
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक adb_iop_ग_लिखो(काष्ठा adb_request *req)
अणु
	अचिन्हित दीर्घ flags;

	अगर ((req->nbytes < 2) || (req->data[0] != ADB_PACKET)) अणु
		req->complete = 1;
		वापस -EINVAL;
	पूर्ण

	req->next = शून्य;
	req->sent = 0;
	req->complete = 0;
	req->reply_len = 0;

	local_irq_save(flags);

	अगर (current_req) अणु
		last_req->next = req;
		last_req = req;
	पूर्ण अन्यथा अणु
		current_req = req;
		last_req = req;
	पूर्ण

	अगर (adb_iop_state == idle)
		adb_iop_start();

	local_irq_restore(flags);

	वापस 0;
पूर्ण

अटल व्योम adb_iop_set_ap_complete(काष्ठा iop_msg *msg)
अणु
	काष्ठा adb_iopmsg *amsg = (काष्ठा adb_iopmsg *)msg->message;

	स्वतःpoll_devs = get_unaligned_be16(amsg->data);
	अगर (स्वतःpoll_devs & (1 << स्वतःpoll_addr))
		वापस;
	स्वतःpoll_addr = स्वतःpoll_devs ? (ffs(स्वतःpoll_devs) - 1) : 0;
पूर्ण

अटल पूर्णांक adb_iop_स्वतःpoll(पूर्णांक devs)
अणु
	काष्ठा adb_iopmsg amsg;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक mask = (अचिन्हित पूर्णांक)devs & 0xFFFE;

	local_irq_save(flags);

	amsg.flags = ADB_IOP_SET_AUTOPOLL | (mask ? ADB_IOP_AUTOPOLL : 0);
	amsg.count = 2;
	amsg.cmd = 0;
	put_unaligned_be16(mask, amsg.data);

	iop_send_message(ADB_IOP, ADB_CHAN, शून्य, माप(amsg), (__u8 *)&amsg,
			 adb_iop_set_ap_complete);

	local_irq_restore(flags);

	वापस 0;
पूर्ण

अटल व्योम adb_iop_poll(व्योम)
अणु
	iop_ism_irq_poll(ADB_IOP);
पूर्ण

अटल पूर्णांक adb_iop_reset_bus(व्योम)
अणु
	काष्ठा adb_request req;

	/* Command = 0, Address = ignored */
	adb_request(&req, शून्य, ADBREQ_NOSEND, 1, ADB_BUSRESET);
	adb_iop_send_request(&req, 1);

	/* Don't want any more requests during the Global Reset low समय. */
	mdelay(3);

	वापस 0;
पूर्ण
