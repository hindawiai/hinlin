<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* $Id: scc.h,v 1.29 1997/04/02 14:56:45 jreuter Exp jreuter $ */
#अगर_अघोषित	_SCC_H
#घोषणा	_SCC_H

#समावेश <uapi/linux/scc.h>


क्रमागत अणुTX_OFF, TX_ONपूर्ण;	/* command क्रम scc_key_trx() */

/* Vector masks in RR2B */

#घोषणा VECTOR_MASK	0x06
#घोषणा TXINT		0x00
#घोषणा EXINT		0x02
#घोषणा RXINT		0x04
#घोषणा SPINT		0x06

#अगर_घोषित CONFIG_SCC_DELAY
#घोषणा Inb(port)	inb_p(port)
#घोषणा Outb(port, val)	outb_p(val, port)
#अन्यथा
#घोषणा Inb(port)	inb(port)
#घोषणा Outb(port, val)	outb(val, port)
#पूर्ण_अगर

/* SCC channel control काष्ठाure क्रम KISS */

काष्ठा scc_kiss अणु
	अचिन्हित अक्षर txdelay;		/* Transmit Delay 10 ms/cnt */
	अचिन्हित अक्षर persist;		/* Persistence (0-255) as a % */
	अचिन्हित अक्षर slotसमय;		/* Delay to रुको on persistence hit */
	अचिन्हित अक्षर tailसमय;		/* Delay after last byte written */
	अचिन्हित अक्षर fulldup;		/* Full Duplex mode 0=CSMA 1=DUP 2=ALWAYS KEYED */
	अचिन्हित अक्षर रुकोसमय;		/* Waitसमय beक्रमe any transmit attempt */
	अचिन्हित पूर्णांक  maxkeyup;		/* Maximum समय to transmit (seconds) */
	अचिन्हित पूर्णांक  mपूर्णांकime;		/* Minimal offसमय after MAXKEYUP समयout (seconds) */
	अचिन्हित पूर्णांक  idleसमय;		/* Maximum idle समय in ALWAYS KEYED mode (seconds) */
	अचिन्हित पूर्णांक  maxdefer;		/* Timer क्रम CSMA channel busy limit */
	अचिन्हित अक्षर tx_inhibit;	/* Transmit is not allowed when set */	
	अचिन्हित अक्षर group;		/* Group ID क्रम AX.25 TX पूर्णांकerlocking */
	अचिन्हित अक्षर mode;		/* 'normal' or 'hwctrl' mode (unused) */
	अचिन्हित अक्षर softdcd;		/* Use DPLL instead of DCD pin क्रम carrier detect */
पूर्ण;


/* SCC channel काष्ठाure */

काष्ठा scc_channel अणु
	पूर्णांक init;			/* channel exists? */

	काष्ठा net_device *dev;		/* link to device control काष्ठाure */
	काष्ठा net_device_stats dev_stat;/* device statistics */

	अक्षर bअक्रम;			/* manufacturer of the board */
	दीर्घ घड़ी;			/* used घड़ी */

	io_port ctrl;			/* I/O address of CONTROL रेजिस्टर */
	io_port	data;			/* I/O address of DATA रेजिस्टर */
	io_port special;		/* I/O address of special function port */
	पूर्णांक irq;			/* Number of Interrupt */

	अक्षर option;
	अक्षर enhanced;			/* Enhanced SCC support */

	अचिन्हित अक्षर wreg[16]; 	/* Copy of last written value in WRx */
	अचिन्हित अक्षर status;		/* Copy of R0 at last बाह्यal पूर्णांकerrupt */
	अचिन्हित अक्षर dcd;		/* DCD status */

        काष्ठा scc_kiss kiss;		/* control काष्ठाure क्रम KISS params */
        काष्ठा scc_stat stat;		/* statistical inक्रमmation */
        काष्ठा scc_modem modem; 	/* modem inक्रमmation */

        काष्ठा sk_buff_head tx_queue;	/* next tx buffer */
        काष्ठा sk_buff *rx_buff;	/* poपूर्णांकer to frame currently received */
        काष्ठा sk_buff *tx_buff;	/* poपूर्णांकer to frame currently transmitted */

	/* Timer */
	काष्ठा समयr_list tx_t;		/* tx समयr क्रम this channel */
	काष्ठा समयr_list tx_wकरोg;	/* tx watchकरोgs */
	
	/* Channel lock */
	spinlock_t	lock;		/* Channel guard lock */
पूर्ण;

#पूर्ण_अगर /* defined(_SCC_H) */
