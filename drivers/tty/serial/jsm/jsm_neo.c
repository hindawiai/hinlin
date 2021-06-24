<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/************************************************************************
 * Copyright 2003 Digi International (www.digi.com)
 *
 * Copyright (C) 2004 IBM Corporation. All rights reserved.
 *
 * Contact Inक्रमmation:
 * Scott H Kilau <Scott_Kilau@digi.com>
 * Wendy Xiong   <wendyx@us.ibm.com>
 *
 ***********************************************************************/
#समावेश <linux/delay.h>	/* For udelay */
#समावेश <linux/serial_reg.h>	/* For the various UART offsets */
#समावेश <linux/tty.h>
#समावेश <linux/pci.h>
#समावेश <यंत्र/पन.स>

#समावेश "jsm.h"		/* Driver मुख्य header file */

अटल u32 jsm_offset_table[8] = अणु 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80 पूर्ण;

/*
 * This function allows calls to ensure that all outstanding
 * PCI ग_लिखोs have been completed, by करोing a PCI पढ़ो against
 * a non-deकाष्ठाive, पढ़ो-only location on the Neo card.
 *
 * In this हाल, we are पढ़ोing the DVID (Read-only Device Identअगरication)
 * value of the Neo card.
 */
अटल अंतरभूत व्योम neo_pci_posting_flush(काष्ठा jsm_board *bd)
अणु
      पढ़ोb(bd->re_map_membase + 0x8D);
पूर्ण

अटल व्योम neo_set_cts_flow_control(काष्ठा jsm_channel *ch)
अणु
	u8 ier, efr;
	ier = पढ़ोb(&ch->ch_neo_uart->ier);
	efr = पढ़ोb(&ch->ch_neo_uart->efr);

	jsm_dbg(PARAM, &ch->ch_bd->pci_dev, "Setting CTSFLOW\n");

	/* Turn on स्वतः CTS flow control */
	ier |= (UART_17158_IER_CTSDSR);
	efr |= (UART_17158_EFR_ECB | UART_17158_EFR_CTSDSR);

	/* Turn off स्वतः Xon flow control */
	efr &= ~(UART_17158_EFR_IXON);

	/* Why? Becuz Exar's spec says we have to zero it out beक्रमe setting it */
	ग_लिखोb(0, &ch->ch_neo_uart->efr);

	/* Turn on UART enhanced bits */
	ग_लिखोb(efr, &ch->ch_neo_uart->efr);

	/* Turn on table D, with 8 अक्षर hi/low watermarks */
	ग_लिखोb((UART_17158_FCTR_TRGD | UART_17158_FCTR_RTS_4DELAY), &ch->ch_neo_uart->fctr);

	/* Feed the UART our trigger levels */
	ग_लिखोb(8, &ch->ch_neo_uart->tfअगरo);
	ch->ch_t_tlevel = 8;

	ग_लिखोb(ier, &ch->ch_neo_uart->ier);
पूर्ण

अटल व्योम neo_set_rts_flow_control(काष्ठा jsm_channel *ch)
अणु
	u8 ier, efr;
	ier = पढ़ोb(&ch->ch_neo_uart->ier);
	efr = पढ़ोb(&ch->ch_neo_uart->efr);

	jsm_dbg(PARAM, &ch->ch_bd->pci_dev, "Setting RTSFLOW\n");

	/* Turn on स्वतः RTS flow control */
	ier |= (UART_17158_IER_RTSDTR);
	efr |= (UART_17158_EFR_ECB | UART_17158_EFR_RTSDTR);

	/* Turn off स्वतः Xoff flow control */
	ier &= ~(UART_17158_IER_XOFF);
	efr &= ~(UART_17158_EFR_IXOFF);

	/* Why? Becuz Exar's spec says we have to zero it out beक्रमe setting it */
	ग_लिखोb(0, &ch->ch_neo_uart->efr);

	/* Turn on UART enhanced bits */
	ग_लिखोb(efr, &ch->ch_neo_uart->efr);

	ग_लिखोb((UART_17158_FCTR_TRGD | UART_17158_FCTR_RTS_4DELAY), &ch->ch_neo_uart->fctr);
	ch->ch_r_watermark = 4;

	ग_लिखोb(56, &ch->ch_neo_uart->rfअगरo);
	ch->ch_r_tlevel = 56;

	ग_लिखोb(ier, &ch->ch_neo_uart->ier);

	/*
	 * From the Neo UART spec sheet:
	 * The स्वतः RTS/DTR function must be started by निश्चितing
	 * RTS/DTR# output pin (MCR bit-0 or 1 to logic 1 after
	 * it is enabled.
	 */
	ch->ch_mostat |= (UART_MCR_RTS);
पूर्ण


अटल व्योम neo_set_ixon_flow_control(काष्ठा jsm_channel *ch)
अणु
	u8 ier, efr;
	ier = पढ़ोb(&ch->ch_neo_uart->ier);
	efr = पढ़ोb(&ch->ch_neo_uart->efr);

	jsm_dbg(PARAM, &ch->ch_bd->pci_dev, "Setting IXON FLOW\n");

	/* Turn off स्वतः CTS flow control */
	ier &= ~(UART_17158_IER_CTSDSR);
	efr &= ~(UART_17158_EFR_CTSDSR);

	/* Turn on स्वतः Xon flow control */
	efr |= (UART_17158_EFR_ECB | UART_17158_EFR_IXON);

	/* Why? Becuz Exar's spec says we have to zero it out beक्रमe setting it */
	ग_लिखोb(0, &ch->ch_neo_uart->efr);

	/* Turn on UART enhanced bits */
	ग_लिखोb(efr, &ch->ch_neo_uart->efr);

	ग_लिखोb((UART_17158_FCTR_TRGD | UART_17158_FCTR_RTS_8DELAY), &ch->ch_neo_uart->fctr);
	ch->ch_r_watermark = 4;

	ग_लिखोb(32, &ch->ch_neo_uart->rfअगरo);
	ch->ch_r_tlevel = 32;

	/* Tell UART what start/stop अक्षरs it should be looking क्रम */
	ग_लिखोb(ch->ch_startc, &ch->ch_neo_uart->xonअक्षर1);
	ग_लिखोb(0, &ch->ch_neo_uart->xonअक्षर2);

	ग_लिखोb(ch->ch_stopc, &ch->ch_neo_uart->xoffअक्षर1);
	ग_लिखोb(0, &ch->ch_neo_uart->xoffअक्षर2);

	ग_लिखोb(ier, &ch->ch_neo_uart->ier);
पूर्ण

अटल व्योम neo_set_ixoff_flow_control(काष्ठा jsm_channel *ch)
अणु
	u8 ier, efr;
	ier = पढ़ोb(&ch->ch_neo_uart->ier);
	efr = पढ़ोb(&ch->ch_neo_uart->efr);

	jsm_dbg(PARAM, &ch->ch_bd->pci_dev, "Setting IXOFF FLOW\n");

	/* Turn off स्वतः RTS flow control */
	ier &= ~(UART_17158_IER_RTSDTR);
	efr &= ~(UART_17158_EFR_RTSDTR);

	/* Turn on स्वतः Xoff flow control */
	ier |= (UART_17158_IER_XOFF);
	efr |= (UART_17158_EFR_ECB | UART_17158_EFR_IXOFF);

	/* Why? Becuz Exar's spec says we have to zero it out beक्रमe setting it */
	ग_लिखोb(0, &ch->ch_neo_uart->efr);

	/* Turn on UART enhanced bits */
	ग_लिखोb(efr, &ch->ch_neo_uart->efr);

	/* Turn on table D, with 8 अक्षर hi/low watermarks */
	ग_लिखोb((UART_17158_FCTR_TRGD | UART_17158_FCTR_RTS_8DELAY), &ch->ch_neo_uart->fctr);

	ग_लिखोb(8, &ch->ch_neo_uart->tfअगरo);
	ch->ch_t_tlevel = 8;

	/* Tell UART what start/stop अक्षरs it should be looking क्रम */
	ग_लिखोb(ch->ch_startc, &ch->ch_neo_uart->xonअक्षर1);
	ग_लिखोb(0, &ch->ch_neo_uart->xonअक्षर2);

	ग_लिखोb(ch->ch_stopc, &ch->ch_neo_uart->xoffअक्षर1);
	ग_लिखोb(0, &ch->ch_neo_uart->xoffअक्षर2);

	ग_लिखोb(ier, &ch->ch_neo_uart->ier);
पूर्ण

अटल व्योम neo_set_no_input_flow_control(काष्ठा jsm_channel *ch)
अणु
	u8 ier, efr;
	ier = पढ़ोb(&ch->ch_neo_uart->ier);
	efr = पढ़ोb(&ch->ch_neo_uart->efr);

	jsm_dbg(PARAM, &ch->ch_bd->pci_dev, "Unsetting Input FLOW\n");

	/* Turn off स्वतः RTS flow control */
	ier &= ~(UART_17158_IER_RTSDTR);
	efr &= ~(UART_17158_EFR_RTSDTR);

	/* Turn off स्वतः Xoff flow control */
	ier &= ~(UART_17158_IER_XOFF);
	अगर (ch->ch_c_अगरlag & IXON)
		efr &= ~(UART_17158_EFR_IXOFF);
	अन्यथा
		efr &= ~(UART_17158_EFR_ECB | UART_17158_EFR_IXOFF);

	/* Why? Becuz Exar's spec says we have to zero it out beक्रमe setting it */
	ग_लिखोb(0, &ch->ch_neo_uart->efr);

	/* Turn on UART enhanced bits */
	ग_लिखोb(efr, &ch->ch_neo_uart->efr);

	/* Turn on table D, with 8 अक्षर hi/low watermarks */
	ग_लिखोb((UART_17158_FCTR_TRGD | UART_17158_FCTR_RTS_8DELAY), &ch->ch_neo_uart->fctr);

	ch->ch_r_watermark = 0;

	ग_लिखोb(16, &ch->ch_neo_uart->tfअगरo);
	ch->ch_t_tlevel = 16;

	ग_लिखोb(16, &ch->ch_neo_uart->rfअगरo);
	ch->ch_r_tlevel = 16;

	ग_लिखोb(ier, &ch->ch_neo_uart->ier);
पूर्ण

अटल व्योम neo_set_no_output_flow_control(काष्ठा jsm_channel *ch)
अणु
	u8 ier, efr;
	ier = पढ़ोb(&ch->ch_neo_uart->ier);
	efr = पढ़ोb(&ch->ch_neo_uart->efr);

	jsm_dbg(PARAM, &ch->ch_bd->pci_dev, "Unsetting Output FLOW\n");

	/* Turn off स्वतः CTS flow control */
	ier &= ~(UART_17158_IER_CTSDSR);
	efr &= ~(UART_17158_EFR_CTSDSR);

	/* Turn off स्वतः Xon flow control */
	अगर (ch->ch_c_अगरlag & IXOFF)
		efr &= ~(UART_17158_EFR_IXON);
	अन्यथा
		efr &= ~(UART_17158_EFR_ECB | UART_17158_EFR_IXON);

	/* Why? Becuz Exar's spec says we have to zero it out beक्रमe setting it */
	ग_लिखोb(0, &ch->ch_neo_uart->efr);

	/* Turn on UART enhanced bits */
	ग_लिखोb(efr, &ch->ch_neo_uart->efr);

	/* Turn on table D, with 8 अक्षर hi/low watermarks */
	ग_लिखोb((UART_17158_FCTR_TRGD | UART_17158_FCTR_RTS_8DELAY), &ch->ch_neo_uart->fctr);

	ch->ch_r_watermark = 0;

	ग_लिखोb(16, &ch->ch_neo_uart->tfअगरo);
	ch->ch_t_tlevel = 16;

	ग_लिखोb(16, &ch->ch_neo_uart->rfअगरo);
	ch->ch_r_tlevel = 16;

	ग_लिखोb(ier, &ch->ch_neo_uart->ier);
पूर्ण

अटल अंतरभूत व्योम neo_set_new_start_stop_अक्षरs(काष्ठा jsm_channel *ch)
अणु

	/* अगर hardware flow control is set, then skip this whole thing */
	अगर (ch->ch_c_cflag & CRTSCTS)
		वापस;

	jsm_dbg(PARAM, &ch->ch_bd->pci_dev, "start\n");

	/* Tell UART what start/stop अक्षरs it should be looking क्रम */
	ग_लिखोb(ch->ch_startc, &ch->ch_neo_uart->xonअक्षर1);
	ग_लिखोb(0, &ch->ch_neo_uart->xonअक्षर2);

	ग_लिखोb(ch->ch_stopc, &ch->ch_neo_uart->xoffअक्षर1);
	ग_लिखोb(0, &ch->ch_neo_uart->xoffअक्षर2);
पूर्ण

अटल व्योम neo_copy_data_from_uart_to_queue(काष्ठा jsm_channel *ch)
अणु
	पूर्णांक qleft = 0;
	u8 linestatus = 0;
	u8 error_mask = 0;
	पूर्णांक n = 0;
	पूर्णांक total = 0;
	u16 head;
	u16 tail;

	/* cache head and tail of queue */
	head = ch->ch_r_head & RQUEUEMASK;
	tail = ch->ch_r_tail & RQUEUEMASK;

	/* Get our cached LSR */
	linestatus = ch->ch_cached_lsr;
	ch->ch_cached_lsr = 0;

	/* Store how much space we have left in the queue */
	अगर ((qleft = tail - head - 1) < 0)
		qleft += RQUEUEMASK + 1;

	/*
	 * If the UART is not in FIFO mode, क्रमce the FIFO copy to
	 * NOT be run, by setting total to 0.
	 *
	 * On the other hand, अगर the UART IS in FIFO mode, then ask
	 * the UART to give us an approximation of data it has RX'ed.
	 */
	अगर (!(ch->ch_flags & CH_FIFO_ENABLED))
		total = 0;
	अन्यथा अणु
		total = पढ़ोb(&ch->ch_neo_uart->rfअगरo);

		/*
		 * EXAR chip bug - RX FIFO COUNT - Fudge factor.
		 *
		 * This resolves a problem/bug with the Exar chip that someबार
		 * वापसs a bogus value in the rfअगरo रेजिस्टर.
		 * The count can be any where from 0-3 bytes "off".
		 * Bizarre, but true.
		 */
		total -= 3;
	पूर्ण

	/*
	 * Finally, bound the copy to make sure we करोn't overflow
	 * our own queue...
	 * The byte by byte copy loop below this loop this will
	 * deal with the queue overflow possibility.
	 */
	total = min(total, qleft);

	जबतक (total > 0) अणु
		/*
		 * Grab the linestatus रेजिस्टर, we need to check
		 * to see अगर there are any errors in the FIFO.
		 */
		linestatus = पढ़ोb(&ch->ch_neo_uart->lsr);

		/*
		 * Break out अगर there is a FIFO error somewhere.
		 * This will allow us to go byte by byte करोwn below,
		 * finding the exact location of the error.
		 */
		अगर (linestatus & UART_17158_RX_FIFO_DATA_ERROR)
			अवरोध;

		/* Make sure we करोn't go over the end of our queue */
		n = min(((u32) total), (RQUEUESIZE - (u32) head));

		/*
		 * Cut करोwn n even further अगर needed, this is to fix
		 * a problem with स_नकल_fromio() with the Neo on the
		 * IBM pSeries platक्रमm.
		 * 15 bytes max appears to be the magic number.
		 */
		n = min((u32) n, (u32) 12);

		/*
		 * Since we are grabbing the linestatus रेजिस्टर, which
		 * will reset some bits after our पढ़ो, we need to ensure
		 * we करोn't miss our TX FIFO emptys.
		 */
		अगर (linestatus & (UART_LSR_THRE | UART_17158_TX_AND_FIFO_CLR))
			ch->ch_flags |= (CH_TX_FIFO_EMPTY | CH_TX_FIFO_LWM);

		linestatus = 0;

		/* Copy data from uart to the queue */
		स_नकल_fromio(ch->ch_rqueue + head, &ch->ch_neo_uart->txrxburst, n);
		/*
		 * Since RX_FIFO_DATA_ERROR was 0, we are guaranteed
		 * that all the data currently in the FIFO is मुक्त of
		 * अवरोधs and parity/frame/orun errors.
		 */
		स_रखो(ch->ch_equeue + head, 0, n);

		/* Add to and flip head अगर needed */
		head = (head + n) & RQUEUEMASK;
		total -= n;
		qleft -= n;
		ch->ch_rxcount += n;
	पूर्ण

	/*
	 * Create a mask to determine whether we should
	 * insert the अक्षरacter (अगर any) पूर्णांकo our queue.
	 */
	अगर (ch->ch_c_अगरlag & IGNBRK)
		error_mask |= UART_LSR_BI;

	/*
	 * Now cleanup any leftover bytes still in the UART.
	 * Also deal with any possible queue overflow here as well.
	 */
	जबतक (1) अणु

		/*
		 * Its possible we have a linestatus from the loop above
		 * this, so we "OR" on any extra bits.
		 */
		linestatus |= पढ़ोb(&ch->ch_neo_uart->lsr);

		/*
		 * If the chip tells us there is no more data pending to
		 * be पढ़ो, we can then leave.
		 * But beक्रमe we करो, cache the linestatus, just in हाल.
		 */
		अगर (!(linestatus & UART_LSR_DR)) अणु
			ch->ch_cached_lsr = linestatus;
			अवरोध;
		पूर्ण

		/* No need to store this bit */
		linestatus &= ~UART_LSR_DR;

		/*
		 * Since we are grabbing the linestatus रेजिस्टर, which
		 * will reset some bits after our पढ़ो, we need to ensure
		 * we करोn't miss our TX FIFO emptys.
		 */
		अगर (linestatus & (UART_LSR_THRE | UART_17158_TX_AND_FIFO_CLR)) अणु
			linestatus &= ~(UART_LSR_THRE | UART_17158_TX_AND_FIFO_CLR);
			ch->ch_flags |= (CH_TX_FIFO_EMPTY | CH_TX_FIFO_LWM);
		पूर्ण

		/*
		 * Discard अक्षरacter अगर we are ignoring the error mask.
		 */
		अगर (linestatus & error_mask) अणु
			u8 discard;
			linestatus = 0;
			स_नकल_fromio(&discard, &ch->ch_neo_uart->txrxburst, 1);
			जारी;
		पूर्ण

		/*
		 * If our queue is full, we have no choice but to drop some data.
		 * The assumption is that HWFLOW or SWFLOW should have stopped
		 * things way way beक्रमe we got to this poपूर्णांक.
		 *
		 * I decided that I wanted to ditch the oldest data first,
		 * I hope thats okay with everyone? Yes? Good.
		 */
		जबतक (qleft < 1) अणु
			jsm_dbg(READ, &ch->ch_bd->pci_dev,
				"Queue full, dropping DATA:%x LSR:%x\n",
				ch->ch_rqueue[tail], ch->ch_equeue[tail]);

			ch->ch_r_tail = tail = (tail + 1) & RQUEUEMASK;
			ch->ch_err_overrun++;
			qleft++;
		पूर्ण

		स_नकल_fromio(ch->ch_rqueue + head, &ch->ch_neo_uart->txrxburst, 1);
		ch->ch_equeue[head] = (u8) linestatus;

		jsm_dbg(READ, &ch->ch_bd->pci_dev, "DATA/LSR pair: %x %x\n",
			ch->ch_rqueue[head], ch->ch_equeue[head]);

		/* Ditch any reमुख्यing linestatus value. */
		linestatus = 0;

		/* Add to and flip head अगर needed */
		head = (head + 1) & RQUEUEMASK;

		qleft--;
		ch->ch_rxcount++;
	पूर्ण

	/*
	 * Write new final heads to channel काष्ठाure.
	 */
	ch->ch_r_head = head & RQUEUEMASK;
	ch->ch_e_head = head & EQUEUEMASK;
	jsm_input(ch);
पूर्ण

अटल व्योम neo_copy_data_from_queue_to_uart(काष्ठा jsm_channel *ch)
अणु
	u16 head;
	u16 tail;
	पूर्णांक n;
	पूर्णांक s;
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
	/*
	 * If FIFOs are disabled. Send data directly to txrx रेजिस्टर
	 */
	अगर (!(ch->ch_flags & CH_FIFO_ENABLED)) अणु
		u8 lsrbits = पढ़ोb(&ch->ch_neo_uart->lsr);

		ch->ch_cached_lsr |= lsrbits;
		अगर (ch->ch_cached_lsr & UART_LSR_THRE) अणु
			ch->ch_cached_lsr &= ~(UART_LSR_THRE);

			ग_लिखोb(circ->buf[circ->tail], &ch->ch_neo_uart->txrx);
			jsm_dbg(WRITE, &ch->ch_bd->pci_dev,
				"Tx data: %x\n", circ->buf[circ->tail]);
			circ->tail = (circ->tail + 1) & (UART_XMIT_SIZE - 1);
			ch->ch_txcount++;
		पूर्ण
		वापस;
	पूर्ण

	/*
	 * We have to करो it this way, because of the EXAR TXFIFO count bug.
	 */
	अगर (!(ch->ch_flags & (CH_TX_FIFO_EMPTY | CH_TX_FIFO_LWM)))
		वापस;

	n = UART_17158_TX_FIFOSIZE - ch->ch_t_tlevel;

	/* cache head and tail of queue */
	head = circ->head & (UART_XMIT_SIZE - 1);
	tail = circ->tail & (UART_XMIT_SIZE - 1);
	qlen = uart_circ_अक्षरs_pending(circ);

	/* Find minimum of the FIFO space, versus queue length */
	n = min(n, qlen);

	जबतक (n > 0) अणु

		s = ((head >= tail) ? head : UART_XMIT_SIZE) - tail;
		s = min(s, n);

		अगर (s <= 0)
			अवरोध;

		स_नकल_toio(&ch->ch_neo_uart->txrxburst, circ->buf + tail, s);
		/* Add and flip queue अगर needed */
		tail = (tail + s) & (UART_XMIT_SIZE - 1);
		n -= s;
		ch->ch_txcount += s;
		len_written += s;
	पूर्ण

	/* Update the final tail */
	circ->tail = tail & (UART_XMIT_SIZE - 1);

	अगर (len_written >= ch->ch_t_tlevel)
		ch->ch_flags &= ~(CH_TX_FIFO_EMPTY | CH_TX_FIFO_LWM);

	अगर (uart_circ_empty(circ))
		uart_ग_लिखो_wakeup(&ch->uart_port);
पूर्ण

अटल व्योम neo_parse_modem(काष्ठा jsm_channel *ch, u8 संकेतs)
अणु
	u8 mसंकेतs = संकेतs;

	jsm_dbg(MSIGS, &ch->ch_bd->pci_dev,
		"neo_parse_modem: port: %d msignals: %x\n",
		ch->ch_portnum, mसंकेतs);

	/* Scrub off lower bits. They signअगरy delta's, which I don't care about */
	/* Keep DDCD and DDSR though */
	mसंकेतs &= 0xf8;

	अगर (mसंकेतs & UART_MSR_DDCD)
		uart_handle_dcd_change(&ch->uart_port, mसंकेतs & UART_MSR_DCD);
	अगर (mसंकेतs & UART_MSR_DDSR)
		uart_handle_cts_change(&ch->uart_port, mसंकेतs & UART_MSR_CTS);
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

/* Make the UART उठाओ any of the output संकेतs we want up */
अटल व्योम neo_निश्चित_modem_संकेतs(काष्ठा jsm_channel *ch)
अणु
	अगर (!ch)
		वापस;

	ग_लिखोb(ch->ch_mostat, &ch->ch_neo_uart->mcr);

	/* flush ग_लिखो operation */
	neo_pci_posting_flush(ch->ch_bd);
पूर्ण

/*
 * Flush the WRITE FIFO on the Neo.
 *
 * NOTE: Channel lock MUST be held beक्रमe calling this function!
 */
अटल व्योम neo_flush_uart_ग_लिखो(काष्ठा jsm_channel *ch)
अणु
	u8 पंचांगp = 0;
	पूर्णांक i = 0;

	अगर (!ch)
		वापस;

	ग_लिखोb((UART_FCR_ENABLE_FIFO | UART_FCR_CLEAR_XMIT), &ch->ch_neo_uart->isr_fcr);

	क्रम (i = 0; i < 10; i++) अणु

		/* Check to see अगर the UART feels it completely flushed the FIFO. */
		पंचांगp = पढ़ोb(&ch->ch_neo_uart->isr_fcr);
		अगर (पंचांगp & UART_FCR_CLEAR_XMIT) अणु
			jsm_dbg(IOCTL, &ch->ch_bd->pci_dev,
				"Still flushing TX UART... i: %d\n", i);
			udelay(10);
		पूर्ण
		अन्यथा
			अवरोध;
	पूर्ण

	ch->ch_flags |= (CH_TX_FIFO_EMPTY | CH_TX_FIFO_LWM);
पूर्ण


/*
 * Flush the READ FIFO on the Neo.
 *
 * NOTE: Channel lock MUST be held beक्रमe calling this function!
 */
अटल व्योम neo_flush_uart_पढ़ो(काष्ठा jsm_channel *ch)
अणु
	u8 पंचांगp = 0;
	पूर्णांक i = 0;

	अगर (!ch)
		वापस;

	ग_लिखोb((UART_FCR_ENABLE_FIFO | UART_FCR_CLEAR_RCVR), &ch->ch_neo_uart->isr_fcr);

	क्रम (i = 0; i < 10; i++) अणु

		/* Check to see अगर the UART feels it completely flushed the FIFO. */
		पंचांगp = पढ़ोb(&ch->ch_neo_uart->isr_fcr);
		अगर (पंचांगp & 2) अणु
			jsm_dbg(IOCTL, &ch->ch_bd->pci_dev,
				"Still flushing RX UART... i: %d\n", i);
			udelay(10);
		पूर्ण
		अन्यथा
			अवरोध;
	पूर्ण
पूर्ण

/*
 * No locks are assumed to be held when calling this function.
 */
अटल व्योम neo_clear_अवरोध(काष्ठा jsm_channel *ch)
अणु
	अचिन्हित दीर्घ lock_flags;

	spin_lock_irqsave(&ch->ch_lock, lock_flags);

	/* Turn अवरोध off, and unset some variables */
	अगर (ch->ch_flags & CH_BREAK_SENDING) अणु
		u8 temp = पढ़ोb(&ch->ch_neo_uart->lcr);
		ग_लिखोb((temp & ~UART_LCR_SBC), &ch->ch_neo_uart->lcr);

		ch->ch_flags &= ~(CH_BREAK_SENDING);
		jsm_dbg(IOCTL, &ch->ch_bd->pci_dev,
			"clear break Finishing UART_LCR_SBC! finished: %lx\n",
			jअगरfies);

		/* flush ग_लिखो operation */
		neo_pci_posting_flush(ch->ch_bd);
	पूर्ण
	spin_unlock_irqrestore(&ch->ch_lock, lock_flags);
पूर्ण

/*
 * Parse the ISR रेजिस्टर.
 */
अटल व्योम neo_parse_isr(काष्ठा jsm_board *brd, u32 port)
अणु
	काष्ठा jsm_channel *ch;
	u8 isr;
	u8 cause;
	अचिन्हित दीर्घ lock_flags;

	अगर (!brd)
		वापस;

	अगर (port >= brd->maxports)
		वापस;

	ch = brd->channels[port];
	अगर (!ch)
		वापस;

	/* Here we try to figure out what caused the पूर्णांकerrupt to happen */
	जबतक (1) अणु

		isr = पढ़ोb(&ch->ch_neo_uart->isr_fcr);

		/* Bail अगर no pending पूर्णांकerrupt */
		अगर (isr & UART_IIR_NO_INT)
			अवरोध;

		/*
		 * Yank off the upper 2 bits, which just show that the FIFO's are enabled.
		 */
		isr &= ~(UART_17158_IIR_FIFO_ENABLED);

		jsm_dbg(INTR, &ch->ch_bd->pci_dev, "%s:%d isr: %x\n",
			__खाता__, __LINE__, isr);

		अगर (isr & (UART_17158_IIR_RDI_TIMEOUT | UART_IIR_RDI)) अणु
			/* Read data from uart -> queue */
			neo_copy_data_from_uart_to_queue(ch);

			/* Call our tty layer to enक्रमce queue flow control अगर needed. */
			spin_lock_irqsave(&ch->ch_lock, lock_flags);
			jsm_check_queue_flow_control(ch);
			spin_unlock_irqrestore(&ch->ch_lock, lock_flags);
		पूर्ण

		अगर (isr & UART_IIR_THRI) अणु
			/* Transfer data (अगर any) from Write Queue -> UART. */
			spin_lock_irqsave(&ch->ch_lock, lock_flags);
			ch->ch_flags |= (CH_TX_FIFO_EMPTY | CH_TX_FIFO_LWM);
			spin_unlock_irqrestore(&ch->ch_lock, lock_flags);
			neo_copy_data_from_queue_to_uart(ch);
		पूर्ण

		अगर (isr & UART_17158_IIR_XONXOFF) अणु
			cause = पढ़ोb(&ch->ch_neo_uart->xoffअक्षर1);

			jsm_dbg(INTR, &ch->ch_bd->pci_dev,
				"Port %d. Got ISR_XONXOFF: cause:%x\n",
				port, cause);

			/*
			 * Since the UART detected either an XON or
			 * XOFF match, we need to figure out which
			 * one it was, so we can suspend or resume data flow.
			 */
			spin_lock_irqsave(&ch->ch_lock, lock_flags);
			अगर (cause == UART_17158_XON_DETECT) अणु
				/* Is output stopped right now, अगर so, resume it */
				अगर (brd->channels[port]->ch_flags & CH_STOP) अणु
					ch->ch_flags &= ~(CH_STOP);
				पूर्ण
				jsm_dbg(INTR, &ch->ch_bd->pci_dev,
					"Port %d. XON detected in incoming data\n",
					port);
			पूर्ण
			अन्यथा अगर (cause == UART_17158_XOFF_DETECT) अणु
				अगर (!(brd->channels[port]->ch_flags & CH_STOP)) अणु
					ch->ch_flags |= CH_STOP;
					jsm_dbg(INTR, &ch->ch_bd->pci_dev,
						"Setting CH_STOP\n");
				पूर्ण
				jsm_dbg(INTR, &ch->ch_bd->pci_dev,
					"Port: %d. XOFF detected in incoming data\n",
					port);
			पूर्ण
			spin_unlock_irqrestore(&ch->ch_lock, lock_flags);
		पूर्ण

		अगर (isr & UART_17158_IIR_HWFLOW_STATE_CHANGE) अणु
			/*
			 * If we get here, this means the hardware is करोing स्वतः flow control.
			 * Check to see whether RTS/DTR or CTS/DSR caused this पूर्णांकerrupt.
			 */
			cause = पढ़ोb(&ch->ch_neo_uart->mcr);

			/* Which pin is करोing स्वतः flow? RTS or DTR? */
			spin_lock_irqsave(&ch->ch_lock, lock_flags);
			अगर ((cause & 0x4) == 0) अणु
				अगर (cause & UART_MCR_RTS)
					ch->ch_mostat |= UART_MCR_RTS;
				अन्यथा
					ch->ch_mostat &= ~(UART_MCR_RTS);
			पूर्ण अन्यथा अणु
				अगर (cause & UART_MCR_DTR)
					ch->ch_mostat |= UART_MCR_DTR;
				अन्यथा
					ch->ch_mostat &= ~(UART_MCR_DTR);
			पूर्ण
			spin_unlock_irqrestore(&ch->ch_lock, lock_flags);
		पूर्ण

		/* Parse any modem संकेत changes */
		jsm_dbg(INTR, &ch->ch_bd->pci_dev,
			"MOD_STAT: sending to parse_modem_sigs\n");
		neo_parse_modem(ch, पढ़ोb(&ch->ch_neo_uart->msr));
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम neo_parse_lsr(काष्ठा jsm_board *brd, u32 port)
अणु
	काष्ठा jsm_channel *ch;
	पूर्णांक linestatus;
	अचिन्हित दीर्घ lock_flags;

	अगर (!brd)
		वापस;

	अगर (port >= brd->maxports)
		वापस;

	ch = brd->channels[port];
	अगर (!ch)
		वापस;

	linestatus = पढ़ोb(&ch->ch_neo_uart->lsr);

	jsm_dbg(INTR, &ch->ch_bd->pci_dev, "%s:%d port: %d linestatus: %x\n",
		__खाता__, __LINE__, port, linestatus);

	ch->ch_cached_lsr |= linestatus;

	अगर (ch->ch_cached_lsr & UART_LSR_DR) अणु
		/* Read data from uart -> queue */
		neo_copy_data_from_uart_to_queue(ch);
		spin_lock_irqsave(&ch->ch_lock, lock_flags);
		jsm_check_queue_flow_control(ch);
		spin_unlock_irqrestore(&ch->ch_lock, lock_flags);
	पूर्ण

	/*
	 * This is a special flag. It indicates that at least 1
	 * RX error (parity, framing, or अवरोध) has happened.
	 * Mark this in our काष्ठा, which will tell me that I have
	 *to करो the special RX+LSR पढ़ो क्रम this FIFO load.
	 */
	अगर (linestatus & UART_17158_RX_FIFO_DATA_ERROR)
		jsm_dbg(INTR, &ch->ch_bd->pci_dev,
			"%s:%d Port: %d Got an RX error, need to parse LSR\n",
			__खाता__, __LINE__, port);

	/*
	 * The next 3 tests should *NOT* happen, as the above test
	 * should encapsulate all 3... At least, thats what Exar says.
	 */

	अगर (linestatus & UART_LSR_PE) अणु
		ch->ch_err_parity++;
		jsm_dbg(INTR, &ch->ch_bd->pci_dev, "%s:%d Port: %d. PAR ERR!\n",
			__खाता__, __LINE__, port);
	पूर्ण

	अगर (linestatus & UART_LSR_FE) अणु
		ch->ch_err_frame++;
		jsm_dbg(INTR, &ch->ch_bd->pci_dev, "%s:%d Port: %d. FRM ERR!\n",
			__खाता__, __LINE__, port);
	पूर्ण

	अगर (linestatus & UART_LSR_BI) अणु
		ch->ch_err_अवरोध++;
		jsm_dbg(INTR, &ch->ch_bd->pci_dev,
			"%s:%d Port: %d. BRK INTR!\n",
			__खाता__, __LINE__, port);
	पूर्ण

	अगर (linestatus & UART_LSR_OE) अणु
		/*
		 * Rx Oruns. Exar says that an orun will NOT corrupt
		 * the FIFO. It will just replace the holding रेजिस्टर
		 * with this new data byte. So basically just ignore this.
		 * Probably we should eventually have an orun stat in our driver...
		 */
		ch->ch_err_overrun++;
		jsm_dbg(INTR, &ch->ch_bd->pci_dev,
			"%s:%d Port: %d. Rx Overrun!\n",
			__खाता__, __LINE__, port);
	पूर्ण

	अगर (linestatus & UART_LSR_THRE) अणु
		spin_lock_irqsave(&ch->ch_lock, lock_flags);
		ch->ch_flags |= (CH_TX_FIFO_EMPTY | CH_TX_FIFO_LWM);
		spin_unlock_irqrestore(&ch->ch_lock, lock_flags);

		/* Transfer data (अगर any) from Write Queue -> UART. */
		neo_copy_data_from_queue_to_uart(ch);
	पूर्ण
	अन्यथा अगर (linestatus & UART_17158_TX_AND_FIFO_CLR) अणु
		spin_lock_irqsave(&ch->ch_lock, lock_flags);
		ch->ch_flags |= (CH_TX_FIFO_EMPTY | CH_TX_FIFO_LWM);
		spin_unlock_irqrestore(&ch->ch_lock, lock_flags);

		/* Transfer data (अगर any) from Write Queue -> UART. */
		neo_copy_data_from_queue_to_uart(ch);
	पूर्ण
पूर्ण

/*
 * neo_param()
 * Send any/all changes to the line to the UART.
 */
अटल व्योम neo_param(काष्ठा jsm_channel *ch)
अणु
	u8 lcr = 0;
	u8 uart_lcr, ier;
	u32 baud;
	पूर्णांक quot;
	काष्ठा jsm_board *bd;

	bd = ch->ch_bd;
	अगर (!bd)
		वापस;

	/*
	 * If baud rate is zero, flush queues, and set mval to drop DTR.
	 */
	अगर ((ch->ch_c_cflag & (CBAUD)) == 0) अणु
		ch->ch_r_head = ch->ch_r_tail = 0;
		ch->ch_e_head = ch->ch_e_tail = 0;

		neo_flush_uart_ग_लिखो(ch);
		neo_flush_uart_पढ़ो(ch);

		ch->ch_flags |= (CH_BAUD0);
		ch->ch_mostat &= ~(UART_MCR_RTS | UART_MCR_DTR);
		neo_निश्चित_modem_संकेतs(ch);
		वापस;

	पूर्ण अन्यथा अणु
		पूर्णांक i;
		अचिन्हित पूर्णांक cflag;
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
	पूर्ण

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

	ier = पढ़ोb(&ch->ch_neo_uart->ier);
	uart_lcr = पढ़ोb(&ch->ch_neo_uart->lcr);

	quot = ch->ch_bd->bd_भागidend / baud;

	अगर (quot != 0) अणु
		ग_लिखोb(UART_LCR_DLAB, &ch->ch_neo_uart->lcr);
		ग_लिखोb((quot & 0xff), &ch->ch_neo_uart->txrx);
		ग_लिखोb((quot >> 8), &ch->ch_neo_uart->ier);
		ग_लिखोb(lcr, &ch->ch_neo_uart->lcr);
	पूर्ण

	अगर (uart_lcr != lcr)
		ग_लिखोb(lcr, &ch->ch_neo_uart->lcr);

	अगर (ch->ch_c_cflag & CREAD)
		ier |= (UART_IER_RDI | UART_IER_RLSI);

	ier |= (UART_IER_THRI | UART_IER_MSI);

	ग_लिखोb(ier, &ch->ch_neo_uart->ier);

	/* Set new start/stop अक्षरs */
	neo_set_new_start_stop_अक्षरs(ch);

	अगर (ch->ch_c_cflag & CRTSCTS)
		neo_set_cts_flow_control(ch);
	अन्यथा अगर (ch->ch_c_अगरlag & IXON) अणु
		/* If start/stop is set to disable, then we should disable flow control */
		अगर ((ch->ch_startc == __DISABLED_CHAR) || (ch->ch_stopc == __DISABLED_CHAR))
			neo_set_no_output_flow_control(ch);
		अन्यथा
			neo_set_ixon_flow_control(ch);
	पूर्ण
	अन्यथा
		neo_set_no_output_flow_control(ch);

	अगर (ch->ch_c_cflag & CRTSCTS)
		neo_set_rts_flow_control(ch);
	अन्यथा अगर (ch->ch_c_अगरlag & IXOFF) अणु
		/* If start/stop is set to disable, then we should disable flow control */
		अगर ((ch->ch_startc == __DISABLED_CHAR) || (ch->ch_stopc == __DISABLED_CHAR))
			neo_set_no_input_flow_control(ch);
		अन्यथा
			neo_set_ixoff_flow_control(ch);
	पूर्ण
	अन्यथा
		neo_set_no_input_flow_control(ch);
	/*
	 * Adjust the RX FIFO Trigger level अगर baud is less than 9600.
	 * Not exactly elegant, but this is needed because of the Exar chip's
	 * delay on firing off the RX FIFO पूर्णांकerrupt on slower baud rates.
	 */
	अगर (baud < 9600) अणु
		ग_लिखोb(1, &ch->ch_neo_uart->rfअगरo);
		ch->ch_r_tlevel = 1;
	पूर्ण

	neo_निश्चित_modem_संकेतs(ch);

	/* Get current status of the modem संकेतs now */
	neo_parse_modem(ch, पढ़ोb(&ch->ch_neo_uart->msr));
	वापस;
पूर्ण

/*
 * jsm_neo_पूर्णांकr()
 *
 * Neo specअगरic पूर्णांकerrupt handler.
 */
अटल irqवापस_t neo_पूर्णांकr(पूर्णांक irq, व्योम *व्योमbrd)
अणु
	काष्ठा jsm_board *brd = व्योमbrd;
	काष्ठा jsm_channel *ch;
	पूर्णांक port = 0;
	पूर्णांक type = 0;
	पूर्णांक current_port;
	u32 पंचांगp;
	u32 uart_poll;
	अचिन्हित दीर्घ lock_flags;
	अचिन्हित दीर्घ lock_flags2;
	पूर्णांक outofloop_count = 0;

	/* Lock out the slow poller from running on this board. */
	spin_lock_irqsave(&brd->bd_पूर्णांकr_lock, lock_flags);

	/*
	 * Read in "extended" IRQ inक्रमmation from the 32bit Neo रेजिस्टर.
	 * Bits 0-7: What port triggered the पूर्णांकerrupt.
	 * Bits 8-31: Each 3bits indicate what type of पूर्णांकerrupt occurred.
	 */
	uart_poll = पढ़ोl(brd->re_map_membase + UART_17158_POLL_ADDR_OFFSET);

	jsm_dbg(INTR, &brd->pci_dev, "%s:%d uart_poll: %x\n",
		__खाता__, __LINE__, uart_poll);

	अगर (!uart_poll) अणु
		jsm_dbg(INTR, &brd->pci_dev,
			"Kernel interrupted to me, but no pending interrupts...\n");
		spin_unlock_irqrestore(&brd->bd_पूर्णांकr_lock, lock_flags);
		वापस IRQ_NONE;
	पूर्ण

	/* At this poपूर्णांक, we have at least SOMETHING to service, dig further... */

	current_port = 0;

	/* Loop on each port */
	जबतक (((uart_poll & 0xff) != 0) && (outofloop_count < 0xff))अणु

		पंचांगp = uart_poll;
		outofloop_count++;

		/* Check current port to see अगर it has पूर्णांकerrupt pending */
		अगर ((पंचांगp & jsm_offset_table[current_port]) != 0) अणु
			port = current_port;
			type = पंचांगp >> (8 + (port * 3));
			type &= 0x7;
		पूर्ण अन्यथा अणु
			current_port++;
			जारी;
		पूर्ण

		jsm_dbg(INTR, &brd->pci_dev, "%s:%d port: %x type: %x\n",
			__खाता__, __LINE__, port, type);

		/* Remove this port + type from uart_poll */
		uart_poll &= ~(jsm_offset_table[port]);

		अगर (!type) अणु
			/* If no type, just ignore it, and move onto next port */
			jsm_dbg(INTR, &brd->pci_dev,
				"Interrupt with no type! port: %d\n", port);
			जारी;
		पूर्ण

		/* Switch on type of पूर्णांकerrupt we have */
		चयन (type) अणु

		हाल UART_17158_RXRDY_TIMEOUT:
			/*
			 * RXRDY Time-out is cleared by पढ़ोing data in the
			* RX FIFO until it falls below the trigger level.
			 */

			/* Verअगरy the port is in range. */
			अगर (port >= brd->nasync)
				जारी;

			ch = brd->channels[port];
			अगर (!ch)
				जारी;

			neo_copy_data_from_uart_to_queue(ch);

			/* Call our tty layer to enक्रमce queue flow control अगर needed. */
			spin_lock_irqsave(&ch->ch_lock, lock_flags2);
			jsm_check_queue_flow_control(ch);
			spin_unlock_irqrestore(&ch->ch_lock, lock_flags2);

			जारी;

		हाल UART_17158_RX_LINE_STATUS:
			/*
			 * RXRDY and RX LINE Status (logic OR of LSR[4:1])
			 */
			neo_parse_lsr(brd, port);
			जारी;

		हाल UART_17158_TXRDY:
			/*
			 * TXRDY पूर्णांकerrupt clears after पढ़ोing ISR रेजिस्टर क्रम the UART channel.
			 */

			/*
			 * Yes, this is odd...
			 * Why would I check EVERY possibility of type of
			 * पूर्णांकerrupt, when we know its TXRDY???
			 * Becuz क्रम some reason, even tho we got triggered क्रम TXRDY,
			 * it seems to be occasionally wrong. Instead of TX, which
			 * it should be, I was getting things like RXDY too. Weird.
			 */
			neo_parse_isr(brd, port);
			जारी;

		हाल UART_17158_MSR:
			/*
			 * MSR or flow control was seen.
			 */
			neo_parse_isr(brd, port);
			जारी;

		शेष:
			/*
			 * The UART triggered us with a bogus पूर्णांकerrupt type.
			 * It appears the Exar chip, when REALLY bogged करोwn, will throw
			 * these once and aजबतक.
			 * Its harmless, just ignore it and move on.
			 */
			jsm_dbg(INTR, &brd->pci_dev,
				"%s:%d Unknown Interrupt type: %x\n",
				__खाता__, __LINE__, type);
			जारी;
		पूर्ण
	पूर्ण

	spin_unlock_irqrestore(&brd->bd_पूर्णांकr_lock, lock_flags);

	jsm_dbg(INTR, &brd->pci_dev, "finish\n");
	वापस IRQ_HANDLED;
पूर्ण

/*
 * Neo specअगरic way of turning off the receiver.
 * Used as a way to enक्रमce queue flow control when in
 * hardware flow control mode.
 */
अटल व्योम neo_disable_receiver(काष्ठा jsm_channel *ch)
अणु
	u8 पंचांगp = पढ़ोb(&ch->ch_neo_uart->ier);
	पंचांगp &= ~(UART_IER_RDI);
	ग_लिखोb(पंचांगp, &ch->ch_neo_uart->ier);

	/* flush ग_लिखो operation */
	neo_pci_posting_flush(ch->ch_bd);
पूर्ण


/*
 * Neo specअगरic way of turning on the receiver.
 * Used as a way to un-enक्रमce queue flow control when in
 * hardware flow control mode.
 */
अटल व्योम neo_enable_receiver(काष्ठा jsm_channel *ch)
अणु
	u8 पंचांगp = पढ़ोb(&ch->ch_neo_uart->ier);
	पंचांगp |= (UART_IER_RDI);
	ग_लिखोb(पंचांगp, &ch->ch_neo_uart->ier);

	/* flush ग_लिखो operation */
	neo_pci_posting_flush(ch->ch_bd);
पूर्ण

अटल व्योम neo_send_start_अक्षरacter(काष्ठा jsm_channel *ch)
अणु
	अगर (!ch)
		वापस;

	अगर (ch->ch_startc != __DISABLED_CHAR) अणु
		ch->ch_xon_sends++;
		ग_लिखोb(ch->ch_startc, &ch->ch_neo_uart->txrx);

		/* flush ग_लिखो operation */
		neo_pci_posting_flush(ch->ch_bd);
	पूर्ण
पूर्ण

अटल व्योम neo_send_stop_अक्षरacter(काष्ठा jsm_channel *ch)
अणु
	अगर (!ch)
		वापस;

	अगर (ch->ch_stopc != __DISABLED_CHAR) अणु
		ch->ch_xoff_sends++;
		ग_लिखोb(ch->ch_stopc, &ch->ch_neo_uart->txrx);

		/* flush ग_लिखो operation */
		neo_pci_posting_flush(ch->ch_bd);
	पूर्ण
पूर्ण

/*
 * neo_uart_init
 */
अटल व्योम neo_uart_init(काष्ठा jsm_channel *ch)
अणु
	ग_लिखोb(0, &ch->ch_neo_uart->ier);
	ग_लिखोb(0, &ch->ch_neo_uart->efr);
	ग_लिखोb(UART_EFR_ECB, &ch->ch_neo_uart->efr);

	/* Clear out UART and FIFO */
	पढ़ोb(&ch->ch_neo_uart->txrx);
	ग_लिखोb((UART_FCR_ENABLE_FIFO|UART_FCR_CLEAR_RCVR|UART_FCR_CLEAR_XMIT), &ch->ch_neo_uart->isr_fcr);
	पढ़ोb(&ch->ch_neo_uart->lsr);
	पढ़ोb(&ch->ch_neo_uart->msr);

	ch->ch_flags |= CH_FIFO_ENABLED;

	/* Assert any संकेतs we want up */
	ग_लिखोb(ch->ch_mostat, &ch->ch_neo_uart->mcr);
पूर्ण

/*
 * Make the UART completely turn off.
 */
अटल व्योम neo_uart_off(काष्ठा jsm_channel *ch)
अणु
	/* Turn off UART enhanced bits */
	ग_लिखोb(0, &ch->ch_neo_uart->efr);

	/* Stop all पूर्णांकerrupts from occurring. */
	ग_लिखोb(0, &ch->ch_neo_uart->ier);
पूर्ण

अटल u32 neo_get_uart_bytes_left(काष्ठा jsm_channel *ch)
अणु
	u8 left = 0;
	u8 lsr = पढ़ोb(&ch->ch_neo_uart->lsr);

	/* We must cache the LSR as some of the bits get reset once पढ़ो... */
	ch->ch_cached_lsr |= lsr;

	/* Determine whether the Transmitter is empty or not */
	अगर (!(lsr & UART_LSR_TEMT))
		left = 1;
	अन्यथा अणु
		ch->ch_flags |= (CH_TX_FIFO_EMPTY | CH_TX_FIFO_LWM);
		left = 0;
	पूर्ण

	वापस left;
पूर्ण

/* Channel lock MUST be held by the calling function! */
अटल व्योम neo_send_अवरोध(काष्ठा jsm_channel *ch)
अणु
	/*
	 * Set the समय we should stop sending the अवरोध.
	 * If we are alपढ़ोy sending a अवरोध, toss away the existing
	 * समय to stop, and use this new value instead.
	 */

	/* Tell the UART to start sending the अवरोध */
	अगर (!(ch->ch_flags & CH_BREAK_SENDING)) अणु
		u8 temp = पढ़ोb(&ch->ch_neo_uart->lcr);
		ग_लिखोb((temp | UART_LCR_SBC), &ch->ch_neo_uart->lcr);
		ch->ch_flags |= (CH_BREAK_SENDING);

		/* flush ग_लिखो operation */
		neo_pci_posting_flush(ch->ch_bd);
	पूर्ण
पूर्ण

/*
 * neo_send_immediate_अक्षर.
 *
 * Sends a specअगरic अक्षरacter as soon as possible to the UART,
 * jumping over any bytes that might be in the ग_लिखो queue.
 *
 * The channel lock MUST be held by the calling function.
 */
अटल व्योम neo_send_immediate_अक्षर(काष्ठा jsm_channel *ch, अचिन्हित अक्षर c)
अणु
	अगर (!ch)
		वापस;

	ग_लिखोb(c, &ch->ch_neo_uart->txrx);

	/* flush ग_लिखो operation */
	neo_pci_posting_flush(ch->ch_bd);
पूर्ण

काष्ठा board_ops jsm_neo_ops = अणु
	.पूर्णांकr				= neo_पूर्णांकr,
	.uart_init			= neo_uart_init,
	.uart_off			= neo_uart_off,
	.param				= neo_param,
	.निश्चित_modem_संकेतs		= neo_निश्चित_modem_संकेतs,
	.flush_uart_ग_लिखो		= neo_flush_uart_ग_लिखो,
	.flush_uart_पढ़ो		= neo_flush_uart_पढ़ो,
	.disable_receiver		= neo_disable_receiver,
	.enable_receiver		= neo_enable_receiver,
	.send_अवरोध			= neo_send_अवरोध,
	.clear_अवरोध			= neo_clear_अवरोध,
	.send_start_अक्षरacter		= neo_send_start_अक्षरacter,
	.send_stop_अक्षरacter		= neo_send_stop_अक्षरacter,
	.copy_data_from_queue_to_uart	= neo_copy_data_from_queue_to_uart,
	.get_uart_bytes_left		= neo_get_uart_bytes_left,
	.send_immediate_अक्षर		= neo_send_immediate_अक्षर
पूर्ण;
