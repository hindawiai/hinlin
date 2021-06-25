<शैली गुरु>
/*
 * include/linux/serial.h
 *
 * Copyright (C) 1992 by Theoकरोre Ts'o.
 * 
 * Redistribution of this file is permitted under the terms of the GNU 
 * Public License (GPL)
 */
#अगर_अघोषित _LINUX_SERIAL_H
#घोषणा _LINUX_SERIAL_H

#समावेश <यंत्र/page.h>
#समावेश <uapi/linux/serial.h>


/*
 * Counters of the input lines (CTS, DSR, RI, CD) पूर्णांकerrupts
 */

काष्ठा async_icount अणु
	__u32	cts, dsr, rng, dcd, tx, rx;
	__u32	frame, parity, overrun, brk;
	__u32	buf_overrun;
पूर्ण;

/*
 * The size of the serial xmit buffer is 1 page, or 4096 bytes
 */
#घोषणा SERIAL_XMIT_SIZE PAGE_SIZE

#समावेश <linux/compiler.h>

#पूर्ण_अगर /* _LINUX_SERIAL_H */
