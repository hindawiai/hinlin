<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright 2003 Digi International (www.digi.com)
 *	Scott H Kilau <Scott_Kilau at digi करोt com>
 *
 *	NOTE TO LINUX KERNEL HACKERS:  DO NOT REFORMAT THIS CODE!
 *
 *	This is shared code between Digi's CVS archive and the
 *	Linux Kernel sources.
 *	Changing the source just क्रम reक्रमmatting needlessly अवरोधs
 *	our CVS dअगरf history.
 *
 *	Send any bug fixes/changes to:  Eng.Linux at digi करोt com.
 *	Thank you.
 *
 */

#समावेश <linux/delay.h>	/* For udelay */
#समावेश <linux/पन.स>		/* For पढ़ो[bwl]/ग_लिखो[bwl] */
#समावेश <linux/serial.h>	/* For काष्ठा async_serial */
#समावेश <linux/serial_reg.h>	/* For the various UART offsets */
#समावेश <linux/pci.h>
#समावेश <linux/tty.h>

#समावेश "jsm.h"	/* Driver मुख्य header file */

अटल काष्ठा अणु
	अचिन्हित पूर्णांक rate;
	अचिन्हित पूर्णांक cflag;
पूर्ण baud_rates[] = अणु
	अणु 921600, B921600 पूर्ण,
	अणु 460800, B460800 पूर्ण,
	अणु 230400, B230400 पूर्ण,
	अणु 115200, B115200 पूर्ण,
	अणु  57600, B57600  पूर्ण,
	अणु  38400, B38400  पूर्ण,
	अणु  19200, B19200  पूर्ण,
	अणु   9600, B9600   पूर्ण,
	अणु   4800, B4800   पूर्ण,
	अणु   2400, B2400   पूर्ण,
	अणु   1200, B1200   पूर्ण,
	अणु    600, B600    पूर्ण,
	अणु    300, B300    पूर्ण,
	अणु    200, B200    पूर्ण,
	अणु    150, B150    पूर्ण,
	अणु    134, B134    पूर्ण,
	अणु    110, B110    पूर्ण,
	अणु     75, B75     पूर्ण,
	अणु     50, B50     पूर्ण,
पूर्ण;

अटल व्योम cls_set_cts_flow_control(काष्ठा jsm_channel *ch)
अणु
	u8 lcrb = पढ़ोb(&ch->ch_cls_uart->lcr);
	u8 ier = पढ़ोb(&ch->ch_cls_uart->ier);
	u8 isr_fcr = 0;

	/*
	 * The Enhanced Register Set may only be accessed when
	 * the Line Control Register is set to 0xBFh.
	 */
	ग_लिखोb(UART_EXAR654_ENHANCED_REGISTER_SET, &ch->ch_cls_uart->lcr);

	isr_fcr = पढ़ोb(&ch->ch_cls_uart->isr_fcr);

	/* Turn on CTS flow control, turn off IXON flow control */
	isr_fcr |= (UART_EXAR654_EFR_ECB | UART_EXAR654_EFR_CTSDSR);
	isr_fcr &= ~(UART_EXAR654_EFR_IXON);

	ग_लिखोb(isr_fcr, &ch->ch_cls_uart->isr_fcr);

	/* Write old LCR value back out, which turns enhanced access off */
	ग_लिखोb(lcrb, &ch->ch_cls_uart->lcr);

	/*
	 * Enable पूर्णांकerrupts क्रम CTS flow, turn off पूर्णांकerrupts क्रम
	 * received XOFF अक्षरs
	 */
	ier |= (UART_EXAR654_IER_CTSDSR);
	ier &= ~(UART_EXAR654_IER_XOFF);
	ग_लिखोb(ier, &ch->ch_cls_uart->ier);

	/* Set the usual FIFO values */
	ग_लिखोb((UART_FCR_ENABLE_FIFO), &ch->ch_cls_uart->isr_fcr);

	ग_लिखोb((UART_FCR_ENABLE_FIFO | UART_16654_FCR_RXTRIGGER_56 |
		UART_16654_FCR_TXTRIGGER_16 | UART_FCR_CLEAR_RCVR),
		&ch->ch_cls_uart->isr_fcr);

	ch->ch_t_tlevel = 16;
पूर्ण

अटल व्योम cls_set_ixon_flow_control(काष्ठा jsm_channel *ch)
अणु
	u8 lcrb = पढ़ोb(&ch->ch_cls_uart->lcr);
	u8 ier = पढ़ोb(&ch->ch_cls_uart->ier);
	u8 isr_fcr = 0;

	/*
	 * The Enhanced Register Set may only be accessed when
	 * the Line Control Register is set to 0xBFh.
	 */
	ग_लिखोb(UART_EXAR654_ENHANCED_REGISTER_SET, &ch->ch_cls_uart->lcr);

	isr_fcr = पढ़ोb(&ch->ch_cls_uart->isr_fcr);

	/* Turn on IXON flow control, turn off CTS flow control */
	isr_fcr |= (UART_EXAR654_EFR_ECB | UART_EXAR654_EFR_IXON);
	isr_fcr &= ~(UART_EXAR654_EFR_CTSDSR);

	ग_लिखोb(isr_fcr, &ch->ch_cls_uart->isr_fcr);

	/* Now set our current start/stop अक्षरs जबतक in enhanced mode */
	ग_लिखोb(ch->ch_startc, &ch->ch_cls_uart->mcr);
	ग_लिखोb(0, &ch->ch_cls_uart->lsr);
	ग_लिखोb(ch->ch_stopc, &ch->ch_cls_uart->msr);
	ग_लिखोb(0, &ch->ch_cls_uart->spr);

	/* Write old LCR value back out, which turns enhanced access off */
	ग_लिखोb(lcrb, &ch->ch_cls_uart->lcr);

	/*
	 * Disable पूर्णांकerrupts क्रम CTS flow, turn on पूर्णांकerrupts क्रम
	 * received XOFF अक्षरs
	 */
	ier &= ~(UART_EXAR654_IER_CTSDSR);
	ier |= (UART_EXAR654_IER_XOFF);
	ग_लिखोb(ier, &ch->ch_cls_uart->ier);

	/* Set the usual FIFO values */
	ग_लिखोb((UART_FCR_ENABLE_FIFO), &ch->ch_cls_uart->isr_fcr);

	ग_लिखोb((UART_FCR_ENABLE_FIFO | UART_16654_FCR_RXTRIGGER_16 |
		UART_16654_FCR_TXTRIGGER_16 | UART_FCR_CLEAR_RCVR),
		&ch->ch_cls_uart->isr_fcr);
पूर्ण

अटल व्योम cls_set_no_output_flow_control(काष्ठा jsm_channel *ch)
अणु
	u8 lcrb = पढ़ोb(&ch->ch_cls_uart->lcr);
	u8 ier = पढ़ोb(&ch->ch_cls_uart->ier);
	u8 isr_fcr = 0;

	/*
	 * The Enhanced Register Set may only be accessed when
	 * the Line Control Register is set to 0xBFh.
	 */
	ग_लिखोb(UART_EXAR654_ENHANCED_REGISTER_SET, &ch->ch_cls_uart->lcr);

	isr_fcr = पढ़ोb(&ch->ch_cls_uart->isr_fcr);

	/* Turn off IXON flow control, turn off CTS flow control */
	isr_fcr |= (UART_EXAR654_EFR_ECB);
	isr_fcr &= ~(UART_EXAR654_EFR_CTSDSR | UART_EXAR654_EFR_IXON);

	ग_लिखोb(isr_fcr, &ch->ch_cls_uart->isr_fcr);

	/* Write old LCR value back out, which turns enhanced access off */
	ग_लिखोb(lcrb, &ch->ch_cls_uart->lcr);

	/*
	 * Disable पूर्णांकerrupts क्रम CTS flow, turn off पूर्णांकerrupts क्रम
	 * received XOFF अक्षरs
	 */
	ier &= ~(UART_EXAR654_IER_CTSDSR);
	ier &= ~(UART_EXAR654_IER_XOFF);
	ग_लिखोb(ier, &ch->ch_cls_uart->ier);

	/* Set the usual FIFO values */
	ग_लिखोb((UART_FCR_ENABLE_FIFO), &ch->ch_cls_uart->isr_fcr);

	ग_लिखोb((UART_FCR_ENABLE_FIFO | UART_16654_FCR_RXTRIGGER_16 |
		UART_16654_FCR_TXTRIGGER_16 | UART_FCR_CLEAR_RCVR),
		&ch->ch_cls_uart->isr_fcr);

	ch->ch_r_watermark = 0;
	ch->ch_t_tlevel = 16;
	ch->ch_r_tlevel = 16;
पूर्ण

अटल व्योम cls_set_rts_flow_control(काष्ठा jsm_channel *ch)
अणु
	u8 lcrb = पढ़ोb(&ch->ch_cls_uart->lcr);
	u8 ier = पढ़ोb(&ch->ch_cls_uart->ier);
	u8 isr_fcr = 0;

	/*
	 * The Enhanced Register Set may only be accessed when
	 * the Line Control Register is set to 0xBFh.
	 */
	ग_लिखोb(UART_EXAR654_ENHANCED_REGISTER_SET, &ch->ch_cls_uart->lcr);

	isr_fcr = पढ़ोb(&ch->ch_cls_uart->isr_fcr);

	/* Turn on RTS flow control, turn off IXOFF flow control */
	isr_fcr |= (UART_EXAR654_EFR_ECB | UART_EXAR654_EFR_RTSDTR);
	isr_fcr &= ~(UART_EXAR654_EFR_IXOFF);

	ग_लिखोb(isr_fcr, &ch->ch_cls_uart->isr_fcr);

	/* Write old LCR value back out, which turns enhanced access off */
	ग_लिखोb(lcrb, &ch->ch_cls_uart->lcr);

	/* Enable पूर्णांकerrupts क्रम RTS flow */
	ier |= (UART_EXAR654_IER_RTSDTR);
	ग_लिखोb(ier, &ch->ch_cls_uart->ier);

	/* Set the usual FIFO values */
	ग_लिखोb((UART_FCR_ENABLE_FIFO), &ch->ch_cls_uart->isr_fcr);

	ग_लिखोb((UART_FCR_ENABLE_FIFO | UART_16654_FCR_RXTRIGGER_56 |
		UART_16654_FCR_TXTRIGGER_16 | UART_FCR_CLEAR_RCVR),
		&ch->ch_cls_uart->isr_fcr);

	ch->ch_r_watermark = 4;
	ch->ch_r_tlevel = 8;
पूर्ण

अटल व्योम cls_set_ixoff_flow_control(काष्ठा jsm_channel *ch)
अणु
	u8 lcrb = पढ़ोb(&ch->ch_cls_uart->lcr);
	u8 ier = पढ़ोb(&ch->ch_cls_uart->ier);
	u8 isr_fcr = 0;

	/*
	 * The Enhanced Register Set may only be accessed when
	 * the Line Control Register is set to 0xBFh.
	 */
	ग_लिखोb(UART_EXAR654_ENHANCED_REGISTER_SET, &ch->ch_cls_uart->lcr);

	isr_fcr = पढ़ोb(&ch->ch_cls_uart->isr_fcr);

	/* Turn on IXOFF flow control, turn off RTS flow control */
	isr_fcr |= (UART_EXAR654_EFR_ECB | UART_EXAR654_EFR_IXOFF);
	isr_fcr &= ~(UART_EXAR654_EFR_RTSDTR);

	ग_लिखोb(isr_fcr, &ch->ch_cls_uart->isr_fcr);

	/* Now set our current start/stop अक्षरs जबतक in enhanced mode */
	ग_लिखोb(ch->ch_startc, &ch->ch_cls_uart->mcr);
	ग_लिखोb(0, &ch->ch_cls_uart->lsr);
	ग_लिखोb(ch->ch_stopc, &ch->ch_cls_uart->msr);
	ग_लिखोb(0, &ch->ch_cls_uart->spr);

	/* Write old LCR value back out, which turns enhanced access off */
	ग_लिखोb(lcrb, &ch->ch_cls_uart->lcr);

	/* Disable पूर्णांकerrupts क्रम RTS flow */
	ier &= ~(UART_EXAR654_IER_RTSDTR);
	ग_लिखोb(ier, &ch->ch_cls_uart->ier);

	/* Set the usual FIFO values */
	ग_लिखोb((UART_FCR_ENABLE_FIFO), &ch->ch_cls_uart->isr_fcr);

	ग_लिखोb((UART_FCR_ENABLE_FIFO | UART_16654_FCR_RXTRIGGER_16 |
		UART_16654_FCR_TXTRIGGER_16 | UART_FCR_CLEAR_RCVR),
		&ch->ch_cls_uart->isr_fcr);
पूर्ण

अटल व्योम cls_set_no_input_flow_control(काष्ठा jsm_channel *ch)
अणु
	u8 lcrb = पढ़ोb(&ch->ch_cls_uart->lcr);
	u8 ier = पढ़ोb(&ch->ch_cls_uart->ier);
	u8 isr_fcr = 0;

	/*
	 * The Enhanced Register Set may only be accessed when
	 * the Line Control Register is set to 0xBFh.
	 */
	ग_लिखोb(UART_EXAR654_ENHANCED_REGISTER_SET, &ch->ch_cls_uart->lcr);

	isr_fcr = पढ़ोb(&ch->ch_cls_uart->isr_fcr);

	/* Turn off IXOFF flow control, turn off RTS flow control */
	isr_fcr |= (UART_EXAR654_EFR_ECB);
	isr_fcr &= ~(UART_EXAR654_EFR_RTSDTR | UART_EXAR654_EFR_IXOFF);

	ग_लिखोb(isr_fcr, &ch->ch_cls_uart->isr_fcr);

	/* Write old LCR value back out, which turns enhanced access off */
	ग_लिखोb(lcrb, &ch->ch_cls_uart->lcr);

	/* Disable पूर्णांकerrupts क्रम RTS flow */
	ier &= ~(UART_EXAR654_IER_RTSDTR);
	ग_लिखोb(ier, &ch->ch_cls_uart->ier);

	/* Set the usual FIFO values */
	ग_लिखोb((UART_FCR_ENABLE_FIFO), &ch->ch_cls_uart->isr_fcr);

	ग_लिखोb((UART_FCR_ENABLE_FIFO | UART_16654_FCR_RXTRIGGER_16 |
		UART_16654_FCR_TXTRIGGER_16 | UART_FCR_CLEAR_RCVR),
		&ch->ch_cls_uart->isr_fcr);

	ch->ch_t_tlevel = 16;
	ch->ch_r_tlevel = 16;
पूर्ण

/*
 * cls_clear_अवरोध.
 * Determines whether its समय to shut off अवरोध condition.
 *
 * No locks are assumed to be held when calling this function.
 * channel lock is held and released in this function.
 */
अटल व्योम cls_clear_अवरोध(काष्ठा jsm_channel *ch)
अणु
	अचिन्हित दीर्घ lock_flags;

	spin_lock_irqsave(&ch->ch_lock, lock_flags);

	/* Turn अवरोध off, and unset some variables */
	अगर (ch->ch_flags & CH_BREAK_SENDING) अणु
		u8 temp = पढ़ोb(&ch->ch_cls_uart->lcr);

		ग_लिखोb((temp & ~UART_LCR_SBC), &ch->ch_cls_uart->lcr);

		ch->ch_flags &= ~(CH_BREAK_SENDING);
		jsm_dbg(IOCTL, &ch->ch_bd->pci_dev,
			"clear break Finishing UART_LCR_SBC! finished: %lx\n",
			jअगरfies);
	पूर्ण
	spin_unlock_irqrestore(&ch->ch_lock, lock_flags);
पूर्ण

अटल व्योम cls_disable_receiver(काष्ठा jsm_channel *ch)
अणु
	u8 पंचांगp = पढ़ोb(&ch->ch_cls_uart->ier);

	पंचांगp &= ~(UART_IER_RDI);
	ग_लिखोb(पंचांगp, &ch->ch_cls_uart->ier);
पूर्ण

अटल व्योम cls_enable_receiver(काष्ठा jsm_channel *ch)
अणु
	u8 पंचांगp = पढ़ोb(&ch->ch_cls_uart->ier);

	पंचांगp |= (UART_IER_RDI);
	ग_लिखोb(पंचांगp, &ch->ch_cls_uart->ier);
पूर्ण

/* Make the UART उठाओ any of the output संकेतs we want up */
अटल व्योम cls_निश्चित_modem_संकेतs(काष्ठा jsm_channel *ch)
अणु
	अगर (!ch)
		वापस;

	ग_लिखोb(ch->ch_mostat, &ch->ch_cls_uart->mcr);
पूर्ण

अटल व्योम cls_copy_data_from_uart_to_queue(काष्ठा jsm_channel *ch)
अणु
	पूर्णांक qleft = 0;
	u8 linestatus = 0;
	u8 error_mask = 0;
	u16 head;
	u16 tail;
	अचिन्हित दीर्घ flags;

	अगर (!ch)
		वापस;

	spin_lock_irqsave(&ch->ch_lock, flags);

	/* cache head and tail of queue */
	head = ch->ch_r_head & RQUEUEMASK;
	tail = ch->ch_r_tail & RQUEUEMASK;

	/* Get our cached LSR */
	linestatus = ch->ch_cached_lsr;
	ch->ch_cached_lsr = 0;

	/* Store how much space we have left in the queue */
	qleft = tail - head - 1;
	अगर (qleft < 0)
		qleft += RQUEUEMASK + 1;

	/*
	 * Create a mask to determine whether we should
	 * insert the अक्षरacter (अगर any) पूर्णांकo our queue.
	 */
	अगर (ch->ch_c_अगरlag & IGNBRK)
		error_mask |= UART_LSR_BI;

	जबतक (1) अणु
		/*
		 * Grab the linestatus रेजिस्टर, we need to
		 * check to see अगर there is any data to पढ़ो
		 */
		linestatus = पढ़ोb(&ch->ch_cls_uart->lsr);

		/* Break out अगर there is no data to fetch */
		अगर (!(linestatus & UART_LSR_DR))
			अवरोध;

		/*
		 * Discard अक्षरacter अगर we are ignoring the error mask
		 * which in this हाल is the अवरोध संकेत.
		 */
		अगर (linestatus & error_mask)  अणु
			linestatus = 0;
			पढ़ोb(&ch->ch_cls_uart->txrx);
			जारी;
		पूर्ण

		/*
		 * If our queue is full, we have no choice but to drop some
		 * data. The assumption is that HWFLOW or SWFLOW should have
		 * stopped things way way beक्रमe we got to this poपूर्णांक.
		 *
		 * I decided that I wanted to ditch the oldest data first,
		 * I hope thats okay with everyone? Yes? Good.
		 */
		जबतक (qleft < 1) अणु
			tail = (tail + 1) & RQUEUEMASK;
			ch->ch_r_tail = tail;
			ch->ch_err_overrun++;
			qleft++;
		पूर्ण

		ch->ch_equeue[head] = linestatus & (UART_LSR_BI | UART_LSR_PE
								 | UART_LSR_FE);
		ch->ch_rqueue[head] = पढ़ोb(&ch->ch_cls_uart->txrx);

		qleft--;

		अगर (ch->ch_equeue[head] & UART_LSR_PE)
			ch->ch_err_parity++;
		अगर (ch->ch_equeue[head] & UART_LSR_BI)
			ch->ch_err_अवरोध++;
		अगर (ch->ch_equeue[head] & UART_LSR_FE)
			ch->ch_err_frame++;

		/* Add to, and flip head अगर needed */
		head = (head + 1) & RQUEUEMASK;
		ch->ch_rxcount++;
	पूर्ण

	/*
	 * Write new final heads to channel काष्ठाure.
	 */
	ch->ch_r_head = head & RQUEUEMASK;
	ch->ch_e_head = head & EQUEUEMASK;

	spin_unlock_irqrestore(&ch->ch_lock, flags);
पूर्ण

अटल व्योम cls_copy_data_from_queue_to_uart(काष्ठा jsm_channel *ch)
अणु
	u16 tail;
	पूर्णांक n;
	पूर्णांक qlen;
	u32 len_written = 0;
	काष्ठा circ_buf *circ;

	अगर (!ch)
		वापस;

	circ = &ch->uart_port.state->xmit;

	/* No data to ग_लिखो to the UART */
	अगर (uart_circ_empty(circ))
		वापस;

	/* If port is "stopped", करोn't send any data to the UART */
	अगर ((ch->ch_flags & CH_STOP) || (ch->ch_flags & CH_BREAK_SENDING))
		वापस;

	/* We have to करो it this way, because of the EXAR TXFIFO count bug. */
	अगर (!(ch->ch_flags & (CH_TX_FIFO_EMPTY | CH_TX_FIFO_LWM)))
		वापस;

	n = 32;

	/* cache tail of queue */
	tail = circ->tail & (UART_XMIT_SIZE - 1);
	qlen = uart_circ_अक्षरs_pending(circ);

	/* Find minimum of the FIFO space, versus queue length */
	n = min(n, qlen);

	जबतक (n > 0) अणु
		ग_लिखोb(circ->buf[tail], &ch->ch_cls_uart->txrx);
		tail = (tail + 1) & (UART_XMIT_SIZE - 1);
		n--;
		ch->ch_txcount++;
		len_written++;
	पूर्ण

	/* Update the final tail */
	circ->tail = tail & (UART_XMIT_SIZE - 1);

	अगर (len_written > ch->ch_t_tlevel)
		ch->ch_flags &= ~(CH_TX_FIFO_EMPTY | CH_TX_FIFO_LWM);

	अगर (uart_circ_empty(circ))
		uart_ग_लिखो_wakeup(&ch->uart_port);
पूर्ण

अटल व्योम cls_parse_modem(काष्ठा jsm_channel *ch, u8 संकेतs)
अणु
	u8 mसंकेतs = संकेतs;

	jsm_dbg(MSIGS, &ch->ch_bd->pci_dev,
		"neo_parse_modem: port: %d msignals: %x\n",
		ch->ch_portnum, mसंकेतs);

	/*
	 * Scrub off lower bits.
	 * They signअगरy delta's, which I don't care about
	 * Keep DDCD and DDSR though
	 */
	mसंकेतs &= 0xf8;

	अगर (mसंकेतs & UART_MSR_DDCD)
		uart_handle_dcd_change(&ch->uart_port, mसंकेतs & UART_MSR_DCD);
	अगर (mसंकेतs & UART_MSR_DDSR)
		uart_handle_dcd_change(&ch->uart_port, mसंकेतs & UART_MSR_CTS);

	अगर (mसंकेतs & UART_MSR_DCD)
		ch->ch_mistat |= UART_MSR_DCD;
	अन्यथा
		ch->ch_mistat &= ~UART_MSR_DCD;

	अगर (mसंकेतs & UART_MSR_DSR)
		ch->ch_mistat |= UART_MSR_DSR;
	अन्यथा
		ch->ch_mistat &= ~UART_MSR_DSR;

	अगर (mसंकेतs & UART_MSR_RI)
		ch->ch_mistat |= UART_MSR_RI;
	अन्यथा
		ch->ch_mistat &= ~UART_MSR_RI;

	अगर (mसंकेतs & UART_MSR_CTS)
		ch->ch_mistat |= UART_MSR_CTS;
	अन्यथा
		ch->ch_mistat &= ~UART_MSR_CTS;

	jsm_dbg(MSIGS, &ch->ch_bd->pci_dev,
		"Port: %d DTR: %d RTS: %d CTS: %d DSR: %d " "RI: %d CD: %d\n",
		ch->ch_portnum,
		!!((ch->ch_mistat | ch->ch_mostat) & UART_MCR_DTR),
		!!((ch->ch_mistat | ch->ch_mostat) & UART_MCR_RTS),
		!!((ch->ch_mistat | ch->ch_mostat) & UART_MSR_CTS),
		!!((ch->ch_mistat | ch->ch_mostat) & UART_MSR_DSR),
		!!((ch->ch_mistat | ch->ch_mostat) & UART_MSR_RI),
		!!((ch->ch_mistat | ch->ch_mostat) & UART_MSR_DCD));
पूर्ण

/* Parse the ISR रेजिस्टर क्रम the specअगरic port */
अटल अंतरभूत व्योम cls_parse_isr(काष्ठा jsm_board *brd, uपूर्णांक port)
अणु
	काष्ठा jsm_channel *ch;
	u8 isr = 0;
	अचिन्हित दीर्घ flags;

	/*
	 * No need to verअगरy board poपूर्णांकer, it was alपढ़ोy
	 * verअगरied in the पूर्णांकerrupt routine.
	 */

	अगर (port >= brd->nasync)
		वापस;

	ch = brd->channels[port];
	अगर (!ch)
		वापस;

	/* Here we try to figure out what caused the पूर्णांकerrupt to happen */
	जबतक (1) अणु
		isr = पढ़ोb(&ch->ch_cls_uart->isr_fcr);

		/* Bail अगर no pending पूर्णांकerrupt on port */
		अगर (isr & UART_IIR_NO_INT)
			अवरोध;

		/* Receive Interrupt pending */
		अगर (isr & (UART_IIR_RDI | UART_IIR_RDI_TIMEOUT)) अणु
			/* Read data from uart -> queue */
			cls_copy_data_from_uart_to_queue(ch);
			jsm_check_queue_flow_control(ch);
		पूर्ण

		/* Transmit Hold रेजिस्टर empty pending */
		अगर (isr & UART_IIR_THRI) अणु
			/* Transfer data (अगर any) from Write Queue -> UART. */
			spin_lock_irqsave(&ch->ch_lock, flags);
			ch->ch_flags |= (CH_TX_FIFO_EMPTY | CH_TX_FIFO_LWM);
			spin_unlock_irqrestore(&ch->ch_lock, flags);
			cls_copy_data_from_queue_to_uart(ch);
		पूर्ण

		/*
		 * CTS/RTS change of state:
		 * Don't need to करो anything, the cls_parse_modem
		 * below will grab the updated modem संकेतs.
		 */

		/* Parse any modem संकेत changes */
		cls_parse_modem(ch, पढ़ोb(&ch->ch_cls_uart->msr));
	पूर्ण
पूर्ण

/* Channel lock MUST be held beक्रमe calling this function! */
अटल व्योम cls_flush_uart_ग_लिखो(काष्ठा jsm_channel *ch)
अणु
	u8 पंचांगp = 0;
	u8 i = 0;

	अगर (!ch)
		वापस;

	ग_लिखोb((UART_FCR_ENABLE_FIFO | UART_FCR_CLEAR_XMIT),
						&ch->ch_cls_uart->isr_fcr);

	क्रम (i = 0; i < 10; i++) अणु
		/* Check to see अगर the UART feels it completely flushed FIFO */
		पंचांगp = पढ़ोb(&ch->ch_cls_uart->isr_fcr);
		अगर (पंचांगp & UART_FCR_CLEAR_XMIT) अणु
			jsm_dbg(IOCTL, &ch->ch_bd->pci_dev,
				"Still flushing TX UART... i: %d\n", i);
			udelay(10);
		पूर्ण अन्यथा
			अवरोध;
	पूर्ण

	ch->ch_flags |= (CH_TX_FIFO_EMPTY | CH_TX_FIFO_LWM);
पूर्ण

/* Channel lock MUST be held beक्रमe calling this function! */
अटल व्योम cls_flush_uart_पढ़ो(काष्ठा jsm_channel *ch)
अणु
	अगर (!ch)
		वापस;

	/*
	 * For complete POSIX compatibility, we should be purging the
	 * पढ़ो FIFO in the UART here.
	 *
	 * However, clearing the पढ़ो FIFO (UART_FCR_CLEAR_RCVR) also
	 * incorrectly flushes ग_लिखो data as well as just basically trashing the
	 * FIFO.
	 *
	 * Presumably, this is a bug in this UART.
	 */

	udelay(10);
पूर्ण

अटल व्योम cls_send_start_अक्षरacter(काष्ठा jsm_channel *ch)
अणु
	अगर (!ch)
		वापस;

	अगर (ch->ch_startc != __DISABLED_CHAR) अणु
		ch->ch_xon_sends++;
		ग_लिखोb(ch->ch_startc, &ch->ch_cls_uart->txrx);
	पूर्ण
पूर्ण

अटल व्योम cls_send_stop_अक्षरacter(काष्ठा jsm_channel *ch)
अणु
	अगर (!ch)
		वापस;

	अगर (ch->ch_stopc != __DISABLED_CHAR) अणु
		ch->ch_xoff_sends++;
		ग_लिखोb(ch->ch_stopc, &ch->ch_cls_uart->txrx);
	पूर्ण
पूर्ण

/*
 * cls_param()
 * Send any/all changes to the line to the UART.
 */
अटल व्योम cls_param(काष्ठा jsm_channel *ch)
अणु
	u8 lcr = 0;
	u8 uart_lcr = 0;
	u8 ier = 0;
	u32 baud = 9600;
	पूर्णांक quot = 0;
	काष्ठा jsm_board *bd;
	पूर्णांक i;
	अचिन्हित पूर्णांक cflag;

	bd = ch->ch_bd;
	अगर (!bd)
		वापस;

	/*
	 * If baud rate is zero, flush queues, and set mval to drop DTR.
	 */
	अगर ((ch->ch_c_cflag & (CBAUD)) == 0) अणु
		ch->ch_r_head = 0;
		ch->ch_r_tail = 0;
		ch->ch_e_head = 0;
		ch->ch_e_tail = 0;

		cls_flush_uart_ग_लिखो(ch);
		cls_flush_uart_पढ़ो(ch);

		/* The baudrate is B0 so all modem lines are to be dropped. */
		ch->ch_flags |= (CH_BAUD0);
		ch->ch_mostat &= ~(UART_MCR_RTS | UART_MCR_DTR);
		cls_निश्चित_modem_संकेतs(ch);
		वापस;
	पूर्ण

	cflag = C_BAUD(ch->uart_port.state->port.tty);
	baud = 9600;
	क्रम (i = 0; i < ARRAY_SIZE(baud_rates); i++) अणु
		अगर (baud_rates[i].cflag == cflag) अणु
			baud = baud_rates[i].rate;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (ch->ch_flags & CH_BAUD0)
		ch->ch_flags &= ~(CH_BAUD0);

	अगर (ch->ch_c_cflag & PARENB)
		lcr |= UART_LCR_PARITY;

	अगर (!(ch->ch_c_cflag & PARODD))
		lcr |= UART_LCR_EPAR;

	/*
	 * Not all platक्रमms support mark/space parity,
	 * so this will hide behind an अगरdef.
	 */
#अगर_घोषित CMSPAR
	अगर (ch->ch_c_cflag & CMSPAR)
		lcr |= UART_LCR_SPAR;
#पूर्ण_अगर

	अगर (ch->ch_c_cflag & CSTOPB)
		lcr |= UART_LCR_STOP;

	चयन (ch->ch_c_cflag & CSIZE) अणु
	हाल CS5:
		lcr |= UART_LCR_WLEN5;
		अवरोध;
	हाल CS6:
		lcr |= UART_LCR_WLEN6;
		अवरोध;
	हाल CS7:
		lcr |= UART_LCR_WLEN7;
		अवरोध;
	हाल CS8:
	शेष:
		lcr |= UART_LCR_WLEN8;
		अवरोध;
	पूर्ण

	ier = पढ़ोb(&ch->ch_cls_uart->ier);
	uart_lcr = पढ़ोb(&ch->ch_cls_uart->lcr);

	quot = ch->ch_bd->bd_भागidend / baud;

	अगर (quot != 0) अणु
		ग_लिखोb(UART_LCR_DLAB, &ch->ch_cls_uart->lcr);
		ग_लिखोb((quot & 0xff), &ch->ch_cls_uart->txrx);
		ग_लिखोb((quot >> 8), &ch->ch_cls_uart->ier);
		ग_लिखोb(lcr, &ch->ch_cls_uart->lcr);
	पूर्ण

	अगर (uart_lcr != lcr)
		ग_लिखोb(lcr, &ch->ch_cls_uart->lcr);

	अगर (ch->ch_c_cflag & CREAD)
		ier |= (UART_IER_RDI | UART_IER_RLSI);

	ier |= (UART_IER_THRI | UART_IER_MSI);

	ग_लिखोb(ier, &ch->ch_cls_uart->ier);

	अगर (ch->ch_c_cflag & CRTSCTS)
		cls_set_cts_flow_control(ch);
	अन्यथा अगर (ch->ch_c_अगरlag & IXON) अणु
		/*
		 * If start/stop is set to disable,
		 * then we should disable flow control.
		 */
		अगर ((ch->ch_startc == __DISABLED_CHAR) ||
			(ch->ch_stopc == __DISABLED_CHAR))
			cls_set_no_output_flow_control(ch);
		अन्यथा
			cls_set_ixon_flow_control(ch);
	पूर्ण अन्यथा
		cls_set_no_output_flow_control(ch);

	अगर (ch->ch_c_cflag & CRTSCTS)
		cls_set_rts_flow_control(ch);
	अन्यथा अगर (ch->ch_c_अगरlag & IXOFF) अणु
		/*
		 * If start/stop is set to disable,
		 * then we should disable flow control.
		 */
		अगर ((ch->ch_startc == __DISABLED_CHAR) ||
			(ch->ch_stopc == __DISABLED_CHAR))
			cls_set_no_input_flow_control(ch);
		अन्यथा
			cls_set_ixoff_flow_control(ch);
	पूर्ण अन्यथा
		cls_set_no_input_flow_control(ch);

	cls_निश्चित_modem_संकेतs(ch);

	/* get current status of the modem संकेतs now */
	cls_parse_modem(ch, पढ़ोb(&ch->ch_cls_uart->msr));
पूर्ण

/*
 * cls_पूर्णांकr()
 *
 * Classic specअगरic पूर्णांकerrupt handler.
 */
अटल irqवापस_t cls_पूर्णांकr(पूर्णांक irq, व्योम *व्योमbrd)
अणु
	काष्ठा jsm_board *brd = व्योमbrd;
	अचिन्हित दीर्घ lock_flags;
	अचिन्हित अक्षर uart_poll;
	uपूर्णांक i = 0;

	/* Lock out the slow poller from running on this board. */
	spin_lock_irqsave(&brd->bd_पूर्णांकr_lock, lock_flags);

	/*
	 * Check the board's global पूर्णांकerrupt offset to see अगर we
	 * acctually करो have an पूर्णांकerrupt pending on us.
	 */
	uart_poll = पढ़ोb(brd->re_map_membase + UART_CLASSIC_POLL_ADDR_OFFSET);

	jsm_dbg(INTR, &brd->pci_dev, "%s:%d uart_poll: %x\n",
		__खाता__, __LINE__, uart_poll);

	अगर (!uart_poll) अणु
		jsm_dbg(INTR, &brd->pci_dev,
			"Kernel interrupted to me, but no pending interrupts...\n");
		spin_unlock_irqrestore(&brd->bd_पूर्णांकr_lock, lock_flags);
		वापस IRQ_NONE;
	पूर्ण

	/* At this poपूर्णांक, we have at least SOMETHING to service, dig further. */

	/* Parse each port to find out what caused the पूर्णांकerrupt */
	क्रम (i = 0; i < brd->nasync; i++)
		cls_parse_isr(brd, i);

	spin_unlock_irqrestore(&brd->bd_पूर्णांकr_lock, lock_flags);

	वापस IRQ_HANDLED;
पूर्ण

/* Inits UART */
अटल व्योम cls_uart_init(काष्ठा jsm_channel *ch)
अणु
	अचिन्हित अक्षर lcrb = पढ़ोb(&ch->ch_cls_uart->lcr);
	अचिन्हित अक्षर isr_fcr = 0;

	ग_लिखोb(0, &ch->ch_cls_uart->ier);

	/*
	 * The Enhanced Register Set may only be accessed when
	 * the Line Control Register is set to 0xBFh.
	 */
	ग_लिखोb(UART_EXAR654_ENHANCED_REGISTER_SET, &ch->ch_cls_uart->lcr);

	isr_fcr = पढ़ोb(&ch->ch_cls_uart->isr_fcr);

	/* Turn on Enhanced/Extended controls */
	isr_fcr |= (UART_EXAR654_EFR_ECB);

	ग_लिखोb(isr_fcr, &ch->ch_cls_uart->isr_fcr);

	/* Write old LCR value back out, which turns enhanced access off */
	ग_लिखोb(lcrb, &ch->ch_cls_uart->lcr);

	/* Clear out UART and FIFO */
	पढ़ोb(&ch->ch_cls_uart->txrx);

	ग_लिखोb((UART_FCR_ENABLE_FIFO|UART_FCR_CLEAR_RCVR|UART_FCR_CLEAR_XMIT),
						 &ch->ch_cls_uart->isr_fcr);
	udelay(10);

	ch->ch_flags |= (CH_FIFO_ENABLED | CH_TX_FIFO_EMPTY | CH_TX_FIFO_LWM);

	पढ़ोb(&ch->ch_cls_uart->lsr);
	पढ़ोb(&ch->ch_cls_uart->msr);
पूर्ण

/*
 * Turns off UART.
 */
अटल व्योम cls_uart_off(काष्ठा jsm_channel *ch)
अणु
	/* Stop all पूर्णांकerrupts from accurring. */
	ग_लिखोb(0, &ch->ch_cls_uart->ier);
पूर्ण

/*
 * cls_get_uarts_bytes_left.
 * Returns 0 is nothing left in the FIFO, वापसs 1 otherwise.
 *
 * The channel lock MUST be held by the calling function.
 */
अटल u32 cls_get_uart_bytes_left(काष्ठा jsm_channel *ch)
अणु
	u8 left = 0;
	u8 lsr = पढ़ोb(&ch->ch_cls_uart->lsr);

	/* Determine whether the Transmitter is empty or not */
	अगर (!(lsr & UART_LSR_TEMT))
		left = 1;
	अन्यथा अणु
		ch->ch_flags |= (CH_TX_FIFO_EMPTY | CH_TX_FIFO_LWM);
		left = 0;
	पूर्ण

	वापस left;
पूर्ण

/*
 * cls_send_अवरोध.
 * Starts sending a अवरोध thru the UART.
 *
 * The channel lock MUST be held by the calling function.
 */
अटल व्योम cls_send_अवरोध(काष्ठा jsm_channel *ch)
अणु
	/* Tell the UART to start sending the अवरोध */
	अगर (!(ch->ch_flags & CH_BREAK_SENDING)) अणु
		u8 temp = पढ़ोb(&ch->ch_cls_uart->lcr);

		ग_लिखोb((temp | UART_LCR_SBC), &ch->ch_cls_uart->lcr);
		ch->ch_flags |= (CH_BREAK_SENDING);
	पूर्ण
पूर्ण

/*
 * cls_send_immediate_अक्षर.
 * Sends a specअगरic अक्षरacter as soon as possible to the UART,
 * jumping over any bytes that might be in the ग_लिखो queue.
 *
 * The channel lock MUST be held by the calling function.
 */
अटल व्योम cls_send_immediate_अक्षर(काष्ठा jsm_channel *ch, अचिन्हित अक्षर c)
अणु
	ग_लिखोb(c, &ch->ch_cls_uart->txrx);
पूर्ण

काष्ठा board_ops jsm_cls_ops = अणु
	.पूर्णांकr =				cls_पूर्णांकr,
	.uart_init =			cls_uart_init,
	.uart_off =			cls_uart_off,
	.param =			cls_param,
	.निश्चित_modem_संकेतs =		cls_निश्चित_modem_संकेतs,
	.flush_uart_ग_लिखो =		cls_flush_uart_ग_लिखो,
	.flush_uart_पढ़ो =		cls_flush_uart_पढ़ो,
	.disable_receiver =		cls_disable_receiver,
	.enable_receiver =		cls_enable_receiver,
	.send_अवरोध =			cls_send_अवरोध,
	.clear_अवरोध =			cls_clear_अवरोध,
	.send_start_अक्षरacter =		cls_send_start_अक्षरacter,
	.send_stop_अक्षरacter =		cls_send_stop_अक्षरacter,
	.copy_data_from_queue_to_uart = cls_copy_data_from_queue_to_uart,
	.get_uart_bytes_left =		cls_get_uart_bytes_left,
	.send_immediate_अक्षर =		cls_send_immediate_अक्षर
पूर्ण;

