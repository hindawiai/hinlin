<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-1.0+ WITH Linux-syscall-note */
/*
 * include/linux/serial.h
 *
 * Copyright (C) 1992 by Theoकरोre Ts'o.
 * 
 * Redistribution of this file is permitted under the terms of the GNU 
 * Public License (GPL)
 */

#अगर_अघोषित _UAPI_LINUX_SERIAL_H
#घोषणा _UAPI_LINUX_SERIAL_H

#समावेश <linux/types.h>

#समावेश <linux/tty_flags.h>


काष्ठा serial_काष्ठा अणु
	पूर्णांक	type;
	पूर्णांक	line;
	अचिन्हित पूर्णांक	port;
	पूर्णांक	irq;
	पूर्णांक	flags;
	पूर्णांक	xmit_fअगरo_size;
	पूर्णांक	custom_भागisor;
	पूर्णांक	baud_base;
	अचिन्हित लघु	बंद_delay;
	अक्षर	io_type;
	अक्षर	reserved_अक्षर[1];
	पूर्णांक	hub6;
	अचिन्हित लघु	closing_रुको; /* समय to रुको beक्रमe closing */
	अचिन्हित लघु	closing_रुको2; /* no दीर्घer used... */
	अचिन्हित अक्षर	*iomem_base;
	अचिन्हित लघु	iomem_reg_shअगरt;
	अचिन्हित पूर्णांक	port_high;
	अचिन्हित दीर्घ	iomap_base;	/* cookie passed पूर्णांकo ioremap */
पूर्ण;

/*
 * For the बंद रुको बार, 0 means रुको क्रमever क्रम serial port to
 * flush its output.  65535 means करोn't रुको at all.
 */
#घोषणा ASYNC_CLOSING_WAIT_INF	0
#घोषणा ASYNC_CLOSING_WAIT_NONE	65535

/*
 * These are the supported serial types.
 */
#घोषणा PORT_UNKNOWN	0
#घोषणा PORT_8250	1
#घोषणा PORT_16450	2
#घोषणा PORT_16550	3
#घोषणा PORT_16550A	4
#घोषणा PORT_CIRRUS     5
#घोषणा PORT_16650	6
#घोषणा PORT_16650V2	7
#घोषणा PORT_16750	8
#घोषणा PORT_STARTECH	9
#घोषणा PORT_16C950	10	/* Oxक्रमd Semiconductor */
#घोषणा PORT_16654	11
#घोषणा PORT_16850	12
#घोषणा PORT_RSA	13	/* RSA-DV II/S card */
#घोषणा PORT_MAX	13

#घोषणा SERIAL_IO_PORT	0
#घोषणा SERIAL_IO_HUB6	1
#घोषणा SERIAL_IO_MEM	2
#घोषणा SERIAL_IO_MEM32	  3
#घोषणा SERIAL_IO_AU	  4
#घोषणा SERIAL_IO_TSI	  5
#घोषणा SERIAL_IO_MEM32BE 6
#घोषणा SERIAL_IO_MEM16	7

#घोषणा UART_CLEAR_FIFO		0x01
#घोषणा UART_USE_FIFO		0x02
#घोषणा UART_STARTECH		0x04
#घोषणा UART_NATSEMI		0x08


/*
 * Multiport serial configuration काष्ठाure --- बाह्यal काष्ठाure
 */
काष्ठा serial_multiport_काष्ठा अणु
	पूर्णांक		irq;
	पूर्णांक		port1;
	अचिन्हित अक्षर	mask1, match1;
	पूर्णांक		port2;
	अचिन्हित अक्षर	mask2, match2;
	पूर्णांक		port3;
	अचिन्हित अक्षर	mask3, match3;
	पूर्णांक		port4;
	अचिन्हित अक्षर	mask4, match4;
	पूर्णांक		port_monitor;
	पूर्णांक	reserved[32];
पूर्ण;

/*
 * Serial input पूर्णांकerrupt line counters -- बाह्यal काष्ठाure
 * Four lines can पूर्णांकerrupt: CTS, DSR, RI, DCD
 */
काष्ठा serial_icounter_काष्ठा अणु
	पूर्णांक cts, dsr, rng, dcd;
	पूर्णांक rx, tx;
	पूर्णांक frame, overrun, parity, brk;
	पूर्णांक buf_overrun;
	पूर्णांक reserved[9];
पूर्ण;

/*
 * Serial पूर्णांकerface क्रम controlling RS485 settings on chips with suitable
 * support. Set with TIOCSRS485 and get with TIOCGRS485 अगर supported by your
 * platक्रमm. The set function वापसs the new state, with any unsupported bits
 * reverted appropriately.
 */

काष्ठा serial_rs485 अणु
	__u32	flags;			/* RS485 feature flags */
#घोषणा SER_RS485_ENABLED		(1 << 0)	/* If enabled */
#घोषणा SER_RS485_RTS_ON_SEND		(1 << 1)	/* Logical level क्रम
							   RTS pin when
							   sending */
#घोषणा SER_RS485_RTS_AFTER_SEND	(1 << 2)	/* Logical level क्रम
							   RTS pin after sent*/
#घोषणा SER_RS485_RX_DURING_TX		(1 << 4)
#घोषणा SER_RS485_TERMINATE_BUS		(1 << 5)	/* Enable bus
							   termination
							   (अगर supported) */
	__u32	delay_rts_beक्रमe_send;	/* Delay beक्रमe send (milliseconds) */
	__u32	delay_rts_after_send;	/* Delay after send (milliseconds) */
	__u32	padding[5];		/* Memory is cheap, new काष्ठाs
					   are a royal PITA .. */
पूर्ण;

/*
 * Serial पूर्णांकerface क्रम controlling ISO7816 settings on chips with suitable
 * support. Set with TIOCSISO7816 and get with TIOCGISO7816 अगर supported by
 * your platक्रमm.
 */
काष्ठा serial_iso7816 अणु
	__u32	flags;			/* ISO7816 feature flags */
#घोषणा SER_ISO7816_ENABLED		(1 << 0)
#घोषणा SER_ISO7816_T_PARAM		(0x0f << 4)
#घोषणा SER_ISO7816_T(t)		(((t) & 0x0f) << 4)
	__u32	tg;
	__u32	sc_fi;
	__u32	sc_di;
	__u32	clk;
	__u32	reserved[5];
पूर्ण;

#पूर्ण_अगर /* _UAPI_LINUX_SERIAL_H */
