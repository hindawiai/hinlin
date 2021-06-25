<शैली गुरु>
/*
 * I/O Processor (IOP) management
 * Written and (C) 1999 by Joshua M. Thompson (funaho@jurai.org)
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice and this list of conditions.
 * 2. Redistributions in binary क्रमm must reproduce the above copyright
 *    notice and this list of conditions in the करोcumentation and/or other
 *    materials provided with the distribution.
 */

/*
 * The IOP chips are used in the IIfx and some Quadras (900, 950) to manage
 * serial and ADB. They are actually a 6502 processor and some glue logic.
 *
 * 990429 (jmt) - Initial implementation, just enough to knock the SCC IOP
 *		  पूर्णांकo compatible mode so nobody has to fiddle with the
 *		  Serial Switch control panel anymore.
 * 990603 (jmt) - Added code to grab the correct ISM IOP पूर्णांकerrupt क्रम OSS
 *		  and non-OSS machines (at least I hope it's correct on a
 *		  non-OSS machine -- someone with a Q900 or Q950 needs to
 *		  check this.)
 * 990605 (jmt) - Rearranged things a bit wrt IOP detection; iop_present is
 *		  gone, IOP base addresses are now in an array and the
 *		  globally-visible functions take an IOP number instead of an
 *		  an actual base address.
 * 990610 (jmt) - Finished the message passing framework and it seems to work.
 *		  Sending _definitely_ works; my adb-bus.c mods can send
 *		  messages and receive the MSG_COMPLETED status back from the
 *		  IOP. The trick now is figuring out the message क्रमmats.
 * 990611 (jmt) - More cleanups. Fixed problem where unclaimed messages on a
 *		  receive channel were never properly acknowledged. Bracketed
 *		  the reमुख्यing debug prपूर्णांकk's with #ifdef's and disabled
 *		  debugging. I can now type on the console.
 * 990612 (jmt) - Copyright notice added. Reworked the way replies are handled.
 *		  It turns out that replies are placed back in the send buffer
 *		  क्रम that channel; messages on the receive channels are always
 *		  unsolicited messages from the IOP (and our replies to them
 *		  should go back in the receive channel.) Also added tracking
 *		  of device names to the listener functions ala the पूर्णांकerrupt
 *		  handlers.
 * 990729 (jmt) - Added passing of pt_regs काष्ठाure to IOP handlers. This is
 *		  used by the new unअगरied ADB driver.
 *
 * TODO:
 *
 * o The SCC IOP has to be placed in bypass mode beक्रमe the serial console
 *   माला_लो initialized. iop_init() would be one place to करो that. Or the
 *   bootloader could करो that. For now, the Serial Switch control panel
 *   is needed क्रम that -- contrary to the changelog above.
 * o Something should be periodically checking iop_alive() to make sure the
 *   IOP hasn't died.
 * o Some of the IOP manager routines need better error checking and
 *   वापस codes. Nothing major, just prettying up.
 */

/*
 * -----------------------
 * IOP Message Passing 101
 * -----------------------
 *
 * The host talks to the IOPs using a rather simple message-passing scheme via
 * a shared memory area in the IOP RAM. Each IOP has seven "channels"; each
 * channel is connected to a specअगरic software driver on the IOP. For example
 * on the SCC IOP there is one channel क्रम each serial port. Each channel has
 * an incoming and and outgoing message queue with a depth of one.
 *
 * A message is 32 bytes plus a state byte क्रम the channel (MSG_IDLE, MSG_NEW,
 * MSG_RCVD, MSG_COMPLETE). To send a message you copy the message पूर्णांकo the
 * buffer, set the state to MSG_NEW and संकेत the IOP by setting the IRQ flag
 * in the IOP control to 1. The IOP will move the state to MSG_RCVD when it
 * receives the message and then to MSG_COMPLETE when the message processing
 * has completed. It is the host's responsibility at that poपूर्णांक to पढ़ो the
 * reply back out of the send channel buffer and reset the channel state back
 * to MSG_IDLE.
 *
 * To receive message from the IOP the same procedure is used except the roles
 * are reversed. That is, the IOP माला_दो message in the channel with a state of
 * MSG_NEW, and the host receives the message and move its state to MSG_RCVD
 * and then to MSG_COMPLETE when processing is completed and the reply (अगर any)
 * has been placed back in the receive channel. The IOP will then reset the
 * channel state to MSG_IDLE.
 *
 * Two sets of host पूर्णांकerrupts are provided, INT0 and INT1. Both appear on one
 * पूर्णांकerrupt level; they are distinguished by a pair of bits in the IOP status
 * रेजिस्टर. The IOP will उठाओ INT0 when one or more messages in the send
 * channels have gone to the MSG_COMPLETE state and it will उठाओ INT1 when one
 * or more messages on the receive channels have gone to the MSG_NEW state.
 *
 * Since each channel handles only one message we have to implement a small
 * पूर्णांकerrupt-driven queue on our end. Messages to be sent are placed on the
 * queue क्रम sending and contain a poपूर्णांकer to an optional callback function.
 * The handler क्रम a message is called when the message state goes to
 * MSG_COMPLETE.
 *
 * For receiving message we मुख्यtain a list of handler functions to call when
 * a message is received on that IOP/channel combination. The handlers are
 * called much like an पूर्णांकerrupt handler and are passed a copy of the message
 * from the IOP. The message state will be in MSG_RCVD जबतक the handler runs;
 * it is the handler's responsibility to call iop_complete_message() when
 * finished; this function moves the message state to MSG_COMPLETE and संकेतs
 * the IOP. This two-step process is provided to allow the handler to defer
 * message processing to a bottom-half handler अगर the processing will take
 * a signअगरicant amount of समय (handlers are called at पूर्णांकerrupt समय so they
 * should execute quickly.)
 */

#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mm.h>
#समावेश <linux/delay.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>

#समावेश <यंत्र/macपूर्णांकosh.h>
#समावेश <यंत्र/macपूर्णांकs.h>
#समावेश <यंत्र/mac_iop.h>

#अगर_घोषित DEBUG
#घोषणा iop_pr_debug(fmt, ...) \
	prपूर्णांकk(KERN_DEBUG "%s: " fmt, __func__, ##__VA_ARGS__)
#घोषणा iop_pr_cont(fmt, ...) \
	prपूर्णांकk(KERN_CONT fmt, ##__VA_ARGS__)
#अन्यथा
#घोषणा iop_pr_debug(fmt, ...) \
	no_prपूर्णांकk(KERN_DEBUG "%s: " fmt, __func__, ##__VA_ARGS__)
#घोषणा iop_pr_cont(fmt, ...) \
	no_prपूर्णांकk(KERN_CONT fmt, ##__VA_ARGS__)
#पूर्ण_अगर

/* Non-zero अगर the IOPs are present */

पूर्णांक iop_scc_present, iop_ism_present;

/* काष्ठाure क्रम tracking channel listeners */

काष्ठा listener अणु
	स्थिर अक्षर *devname;
	व्योम (*handler)(काष्ठा iop_msg *);
पूर्ण;

/*
 * IOP काष्ठाures क्रम the two IOPs
 *
 * The SCC IOP controls both serial ports (A and B) as its two functions.
 * The ISM IOP controls the SWIM (floppy drive) and ADB.
 */

अटल अस्थिर काष्ठा mac_iop *iop_base[NUM_IOPS];

/*
 * IOP message queues
 */

अटल काष्ठा iop_msg iop_msg_pool[NUM_IOP_MSGS];
अटल काष्ठा iop_msg *iop_send_queue[NUM_IOPS][NUM_IOP_CHAN];
अटल काष्ठा listener iop_listeners[NUM_IOPS][NUM_IOP_CHAN];

irqवापस_t iop_ism_irq(पूर्णांक, व्योम *);

/*
 * Private access functions
 */

अटल __अंतरभूत__ व्योम iop_loadaddr(अस्थिर काष्ठा mac_iop *iop, __u16 addr)
अणु
	iop->ram_addr_lo = addr;
	iop->ram_addr_hi = addr >> 8;
पूर्ण

अटल __अंतरभूत__ __u8 iop_पढ़ोb(अस्थिर काष्ठा mac_iop *iop, __u16 addr)
अणु
	iop->ram_addr_lo = addr;
	iop->ram_addr_hi = addr >> 8;
	वापस iop->ram_data;
पूर्ण

अटल __अंतरभूत__ व्योम iop_ग_लिखोb(अस्थिर काष्ठा mac_iop *iop, __u16 addr, __u8 data)
अणु
	iop->ram_addr_lo = addr;
	iop->ram_addr_hi = addr >> 8;
	iop->ram_data = data;
पूर्ण

अटल __अंतरभूत__ व्योम iop_stop(अस्थिर काष्ठा mac_iop *iop)
अणु
	iop->status_ctrl = IOP_AUTOINC;
पूर्ण

अटल __अंतरभूत__ व्योम iop_start(अस्थिर काष्ठा mac_iop *iop)
अणु
	iop->status_ctrl = IOP_RUN | IOP_AUTOINC;
पूर्ण

अटल __अंतरभूत__ व्योम iop_पूर्णांकerrupt(अस्थिर काष्ठा mac_iop *iop)
अणु
	iop->status_ctrl = IOP_IRQ | IOP_RUN | IOP_AUTOINC;
पूर्ण

अटल पूर्णांक iop_alive(अस्थिर काष्ठा mac_iop *iop)
अणु
	पूर्णांक retval;

	retval = (iop_पढ़ोb(iop, IOP_ADDR_ALIVE) == 0xFF);
	iop_ग_लिखोb(iop, IOP_ADDR_ALIVE, 0);
	वापस retval;
पूर्ण

अटल काष्ठा iop_msg *iop_get_unused_msg(व्योम)
अणु
	पूर्णांक i;
	अचिन्हित दीर्घ flags;

	local_irq_save(flags);

	क्रम (i = 0 ; i < NUM_IOP_MSGS ; i++) अणु
		अगर (iop_msg_pool[i].status == IOP_MSGSTATUS_UNUSED) अणु
			iop_msg_pool[i].status = IOP_MSGSTATUS_WAITING;
			local_irq_restore(flags);
			वापस &iop_msg_pool[i];
		पूर्ण
	पूर्ण

	local_irq_restore(flags);
	वापस शून्य;
पूर्ण

/*
 * Initialize the IOPs, अगर present.
 */

व्योम __init iop_init(व्योम)
अणु
	पूर्णांक i;

	अगर (macपूर्णांकosh_config->scc_type == MAC_SCC_IOP) अणु
		अगर (macपूर्णांकosh_config->ident == MAC_MODEL_IIFX)
			iop_base[IOP_NUM_SCC] = (काष्ठा mac_iop *)SCC_IOP_BASE_IIFX;
		अन्यथा
			iop_base[IOP_NUM_SCC] = (काष्ठा mac_iop *)SCC_IOP_BASE_QUADRA;
		iop_scc_present = 1;
		pr_debug("SCC IOP detected at %p\n", iop_base[IOP_NUM_SCC]);
	पूर्ण
	अगर (macपूर्णांकosh_config->adb_type == MAC_ADB_IOP) अणु
		अगर (macपूर्णांकosh_config->ident == MAC_MODEL_IIFX)
			iop_base[IOP_NUM_ISM] = (काष्ठा mac_iop *)ISM_IOP_BASE_IIFX;
		अन्यथा
			iop_base[IOP_NUM_ISM] = (काष्ठा mac_iop *)ISM_IOP_BASE_QUADRA;
		iop_ism_present = 1;
		pr_debug("ISM IOP detected at %p\n", iop_base[IOP_NUM_ISM]);

		iop_stop(iop_base[IOP_NUM_ISM]);
		iop_start(iop_base[IOP_NUM_ISM]);
		iop_alive(iop_base[IOP_NUM_ISM]); /* clears the alive flag */
	पूर्ण

	/* Make the whole pool available and empty the queues */

	क्रम (i = 0 ; i < NUM_IOP_MSGS ; i++) अणु
		iop_msg_pool[i].status = IOP_MSGSTATUS_UNUSED;
	पूर्ण

	क्रम (i = 0 ; i < NUM_IOP_CHAN ; i++) अणु
		iop_send_queue[IOP_NUM_SCC][i] = शून्य;
		iop_send_queue[IOP_NUM_ISM][i] = शून्य;
		iop_listeners[IOP_NUM_SCC][i].devname = शून्य;
		iop_listeners[IOP_NUM_SCC][i].handler = शून्य;
		iop_listeners[IOP_NUM_ISM][i].devname = शून्य;
		iop_listeners[IOP_NUM_ISM][i].handler = शून्य;
	पूर्ण
पूर्ण

/*
 * Register the पूर्णांकerrupt handler क्रम the IOPs.
 */

व्योम __init iop_रेजिस्टर_पूर्णांकerrupts(व्योम)
अणु
	अगर (iop_ism_present) अणु
		अगर (macपूर्णांकosh_config->ident == MAC_MODEL_IIFX) अणु
			अगर (request_irq(IRQ_MAC_ADB, iop_ism_irq, 0,
					"ISM IOP", (व्योम *)IOP_NUM_ISM))
				pr_err("Couldn't register ISM IOP interrupt\n");
		पूर्ण अन्यथा अणु
			अगर (request_irq(IRQ_VIA2_0, iop_ism_irq, 0, "ISM IOP",
					(व्योम *)IOP_NUM_ISM))
				pr_err("Couldn't register ISM IOP interrupt\n");
		पूर्ण
		अगर (!iop_alive(iop_base[IOP_NUM_ISM])) अणु
			pr_warn("IOP: oh my god, they killed the ISM IOP!\n");
		पूर्ण अन्यथा अणु
			pr_warn("IOP: the ISM IOP seems to be alive.\n");
		पूर्ण
	पूर्ण
पूर्ण

/*
 * Register or unरेजिस्टर a listener क्रम a specअगरic IOP and channel
 *
 * If the handler poपूर्णांकer is शून्य the current listener (अगर any) is
 * unरेजिस्टरed. Otherwise the new listener is रेजिस्टरed provided
 * there is no existing listener रेजिस्टरed.
 */

पूर्णांक iop_listen(uपूर्णांक iop_num, uपूर्णांक chan,
		व्योम (*handler)(काष्ठा iop_msg *),
		स्थिर अक्षर *devname)
अणु
	अगर ((iop_num >= NUM_IOPS) || !iop_base[iop_num]) वापस -EINVAL;
	अगर (chan >= NUM_IOP_CHAN) वापस -EINVAL;
	अगर (iop_listeners[iop_num][chan].handler && handler) वापस -EINVAL;
	iop_listeners[iop_num][chan].devname = devname;
	iop_listeners[iop_num][chan].handler = handler;
	वापस 0;
पूर्ण

/*
 * Complete reception of a message, which just means copying the reply
 * पूर्णांकo the buffer, setting the channel state to MSG_COMPLETE and
 * notअगरying the IOP.
 */

व्योम iop_complete_message(काष्ठा iop_msg *msg)
अणु
	पूर्णांक iop_num = msg->iop_num;
	पूर्णांक chan = msg->channel;
	पूर्णांक i,offset;

	iop_pr_debug("iop_num %d chan %d reply %*ph\n",
		     msg->iop_num, msg->channel, IOP_MSG_LEN, msg->reply);

	offset = IOP_ADDR_RECV_MSG + (msg->channel * IOP_MSG_LEN);

	क्रम (i = 0 ; i < IOP_MSG_LEN ; i++, offset++) अणु
		iop_ग_लिखोb(iop_base[iop_num], offset, msg->reply[i]);
	पूर्ण

	iop_ग_लिखोb(iop_base[iop_num],
		   IOP_ADDR_RECV_STATE + chan, IOP_MSG_COMPLETE);
	iop_पूर्णांकerrupt(iop_base[msg->iop_num]);

	msg->status = IOP_MSGSTATUS_UNUSED;
पूर्ण

/*
 * Actually put a message पूर्णांकo a send channel buffer
 */

अटल व्योम iop_करो_send(काष्ठा iop_msg *msg)
अणु
	अस्थिर काष्ठा mac_iop *iop = iop_base[msg->iop_num];
	पूर्णांक i,offset;

	iop_pr_debug("iop_num %d chan %d message %*ph\n",
		     msg->iop_num, msg->channel, IOP_MSG_LEN, msg->message);

	offset = IOP_ADDR_SEND_MSG + (msg->channel * IOP_MSG_LEN);

	क्रम (i = 0 ; i < IOP_MSG_LEN ; i++, offset++) अणु
		iop_ग_लिखोb(iop, offset, msg->message[i]);
	पूर्ण

	iop_ग_लिखोb(iop, IOP_ADDR_SEND_STATE + msg->channel, IOP_MSG_NEW);

	iop_पूर्णांकerrupt(iop);
पूर्ण

/*
 * Handle sending a message on a channel that
 * has gone पूर्णांकo the IOP_MSG_COMPLETE state.
 */

अटल व्योम iop_handle_send(uपूर्णांक iop_num, uपूर्णांक chan)
अणु
	अस्थिर काष्ठा mac_iop *iop = iop_base[iop_num];
	काष्ठा iop_msg *msg;
	पूर्णांक i,offset;

	iop_ग_लिखोb(iop, IOP_ADDR_SEND_STATE + chan, IOP_MSG_IDLE);

	अगर (!(msg = iop_send_queue[iop_num][chan])) वापस;

	msg->status = IOP_MSGSTATUS_COMPLETE;
	offset = IOP_ADDR_SEND_MSG + (chan * IOP_MSG_LEN);
	क्रम (i = 0 ; i < IOP_MSG_LEN ; i++, offset++) अणु
		msg->reply[i] = iop_पढ़ोb(iop, offset);
	पूर्ण
	iop_pr_debug("iop_num %d chan %d reply %*ph\n",
		     iop_num, chan, IOP_MSG_LEN, msg->reply);

	अगर (msg->handler) (*msg->handler)(msg);
	msg->status = IOP_MSGSTATUS_UNUSED;
	msg = msg->next;
	iop_send_queue[iop_num][chan] = msg;
	अगर (msg && iop_पढ़ोb(iop, IOP_ADDR_SEND_STATE + chan) == IOP_MSG_IDLE)
		iop_करो_send(msg);
पूर्ण

/*
 * Handle reception of a message on a channel that has
 * gone पूर्णांकo the IOP_MSG_NEW state.
 */

अटल व्योम iop_handle_recv(uपूर्णांक iop_num, uपूर्णांक chan)
अणु
	अस्थिर काष्ठा mac_iop *iop = iop_base[iop_num];
	पूर्णांक i,offset;
	काष्ठा iop_msg *msg;

	msg = iop_get_unused_msg();
	msg->iop_num = iop_num;
	msg->channel = chan;
	msg->status = IOP_MSGSTATUS_UNSOL;
	msg->handler = iop_listeners[iop_num][chan].handler;

	offset = IOP_ADDR_RECV_MSG + (chan * IOP_MSG_LEN);

	क्रम (i = 0 ; i < IOP_MSG_LEN ; i++, offset++) अणु
		msg->message[i] = iop_पढ़ोb(iop, offset);
	पूर्ण
	iop_pr_debug("iop_num %d chan %d message %*ph\n",
		     iop_num, chan, IOP_MSG_LEN, msg->message);

	iop_ग_लिखोb(iop, IOP_ADDR_RECV_STATE + chan, IOP_MSG_RCVD);

	/* If there is a listener, call it now. Otherwise complete */
	/* the message ourselves to aव्योम possible stalls.         */

	अगर (msg->handler) अणु
		(*msg->handler)(msg);
	पूर्ण अन्यथा अणु
		स_रखो(msg->reply, 0, IOP_MSG_LEN);
		iop_complete_message(msg);
	पूर्ण
पूर्ण

/*
 * Send a message
 *
 * The message is placed at the end of the send queue. Afterwards अगर the
 * channel is idle we क्रमce an immediate send of the next message in the
 * queue.
 */

पूर्णांक iop_send_message(uपूर्णांक iop_num, uपूर्णांक chan, व्योम *privdata,
		      uपूर्णांक msg_len, __u8 *msg_data,
		      व्योम (*handler)(काष्ठा iop_msg *))
अणु
	काष्ठा iop_msg *msg, *q;

	अगर ((iop_num >= NUM_IOPS) || !iop_base[iop_num]) वापस -EINVAL;
	अगर (chan >= NUM_IOP_CHAN) वापस -EINVAL;
	अगर (msg_len > IOP_MSG_LEN) वापस -EINVAL;

	msg = iop_get_unused_msg();
	अगर (!msg) वापस -ENOMEM;

	msg->next = शून्य;
	msg->status = IOP_MSGSTATUS_WAITING;
	msg->iop_num = iop_num;
	msg->channel = chan;
	msg->caller_priv = privdata;
	स_नकल(msg->message, msg_data, msg_len);
	msg->handler = handler;

	अगर (!(q = iop_send_queue[iop_num][chan])) अणु
		iop_send_queue[iop_num][chan] = msg;
		iop_करो_send(msg);
	पूर्ण अन्यथा अणु
		जबतक (q->next) q = q->next;
		q->next = msg;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Upload code to the shared RAM of an IOP.
 */

व्योम iop_upload_code(uपूर्णांक iop_num, __u8 *code_start,
		     uपूर्णांक code_len, __u16 shared_ram_start)
अणु
	अगर ((iop_num >= NUM_IOPS) || !iop_base[iop_num]) वापस;

	iop_loadaddr(iop_base[iop_num], shared_ram_start);

	जबतक (code_len--) अणु
		iop_base[iop_num]->ram_data = *code_start++;
	पूर्ण
पूर्ण

/*
 * Download code from the shared RAM of an IOP.
 */

व्योम iop_करोwnload_code(uपूर्णांक iop_num, __u8 *code_start,
		       uपूर्णांक code_len, __u16 shared_ram_start)
अणु
	अगर ((iop_num >= NUM_IOPS) || !iop_base[iop_num]) वापस;

	iop_loadaddr(iop_base[iop_num], shared_ram_start);

	जबतक (code_len--) अणु
		*code_start++ = iop_base[iop_num]->ram_data;
	पूर्ण
पूर्ण

/*
 * Compare the code in the shared RAM of an IOP with a copy in प्रणाली memory
 * and वापस 0 on match or the first nonmatching प्रणाली memory address on
 * failure.
 */

__u8 *iop_compare_code(uपूर्णांक iop_num, __u8 *code_start,
		       uपूर्णांक code_len, __u16 shared_ram_start)
अणु
	अगर ((iop_num >= NUM_IOPS) || !iop_base[iop_num]) वापस code_start;

	iop_loadaddr(iop_base[iop_num], shared_ram_start);

	जबतक (code_len--) अणु
		अगर (*code_start != iop_base[iop_num]->ram_data) अणु
			वापस code_start;
		पूर्ण
		code_start++;
	पूर्ण
	वापस (__u8 *) 0;
पूर्ण

/*
 * Handle an ISM IOP पूर्णांकerrupt
 */

irqवापस_t iop_ism_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	uपूर्णांक iop_num = (uपूर्णांक) dev_id;
	अस्थिर काष्ठा mac_iop *iop = iop_base[iop_num];
	पूर्णांक i,state;
	u8 events = iop->status_ctrl & (IOP_INT0 | IOP_INT1);

	करो अणु
		iop_pr_debug("iop_num %d status %02X\n", iop_num,
			     iop->status_ctrl);

		/* INT0 indicates state change on an outgoing message channel */
		अगर (events & IOP_INT0) अणु
			iop->status_ctrl = IOP_INT0 | IOP_RUN | IOP_AUTOINC;
			क्रम (i = 0; i < NUM_IOP_CHAN; i++) अणु
				state = iop_पढ़ोb(iop, IOP_ADDR_SEND_STATE + i);
				अगर (state == IOP_MSG_COMPLETE)
					iop_handle_send(iop_num, i);
				अन्यथा अगर (state != IOP_MSG_IDLE)
					iop_pr_debug("chan %d send state %02X\n",
						     i, state);
			पूर्ण
		पूर्ण

		/* INT1 क्रम incoming messages */
		अगर (events & IOP_INT1) अणु
			iop->status_ctrl = IOP_INT1 | IOP_RUN | IOP_AUTOINC;
			क्रम (i = 0; i < NUM_IOP_CHAN; i++) अणु
				state = iop_पढ़ोb(iop, IOP_ADDR_RECV_STATE + i);
				अगर (state == IOP_MSG_NEW)
					iop_handle_recv(iop_num, i);
				अन्यथा अगर (state != IOP_MSG_IDLE)
					iop_pr_debug("chan %d recv state %02X\n",
						     i, state);
			पूर्ण
		पूर्ण

		events = iop->status_ctrl & (IOP_INT0 | IOP_INT1);
	पूर्ण जबतक (events);

	वापस IRQ_HANDLED;
पूर्ण

व्योम iop_ism_irq_poll(uपूर्णांक iop_num)
अणु
	अचिन्हित दीर्घ flags;

	local_irq_save(flags);
	iop_ism_irq(0, (व्योम *)iop_num);
	local_irq_restore(flags);
पूर्ण
