<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/* $Id: scc.h,v 1.29 1997/04/02 14:56:45 jreuter Exp jreuter $ */

#अगर_अघोषित _UAPI_SCC_H
#घोषणा _UAPI_SCC_H

#समावेश <linux/sockios.h>

/* selection of hardware types */

#घोषणा PA0HZP		0x00	/* hardware type क्रम PA0HZP SCC card and compatible */
#घोषणा EAGLE		0x01    /* hardware type क्रम EAGLE card */
#घोषणा PC100		0x02	/* hardware type क्रम PC100 card */
#घोषणा PRIMUS		0x04	/* hardware type क्रम PRIMUS-PC (DG9BL) card */
#घोषणा DRSI		0x08	/* hardware type क्रम DRSI PC*Packet card */
#घोषणा BAYCOM		0x10	/* hardware type क्रम BayCom (U)SCC */

/* DEV ioctl() commands */

क्रमागत SCC_ioctl_cmds अणु
	SIOCSCCRESERVED = SIOCDEVPRIVATE,
	SIOCSCCCFG,
	SIOCSCCINI,
	SIOCSCCCHANINI,
	SIOCSCCSMEM,
	SIOCSCCGKISS,
	SIOCSCCSKISS,
	SIOCSCCGSTAT,
	SIOCSCCCAL
पूर्ण;

/* Device parameter control (from WAMPES) */

क्रमागत L1_params अणु
	PARAM_DATA,
	PARAM_TXDELAY,
	PARAM_PERSIST,
	PARAM_SLOTTIME,
	PARAM_TXTAIL,
	PARAM_FULLDUP,
	PARAM_SOFTDCD,		/* was: PARAM_HW */
	PARAM_MUTE,		/* ??? */
	PARAM_DTR,
	PARAM_RTS,
	PARAM_SPEED,
	PARAM_ENDDELAY,		/* ??? */
	PARAM_GROUP,
	PARAM_IDLE,
	PARAM_MIN,
	PARAM_MAXKEY,
	PARAM_WAIT,
	PARAM_MAXDEFER,
	PARAM_TX,
	PARAM_HWEVENT = 31,
	PARAM_RETURN = 255	/* reset kiss mode */
पूर्ण;

/* fulldup parameter */

क्रमागत FULLDUP_modes अणु
	KISS_DUPLEX_HALF,	/* normal CSMA operation */
	KISS_DUPLEX_FULL,	/* fullduplex, key करोwn trx after transmission */
	KISS_DUPLEX_LINK,	/* fullduplex, key करोwn trx after 'idletime' sec */
	KISS_DUPLEX_OPTIMA	/* fullduplex, let the protocol layer control the hw */
पूर्ण;

/* misc. parameters */

#घोषणा TIMER_OFF	65535U	/* to चयन off समयrs */
#घोषणा NO_SUCH_PARAM	65534U	/* param not implemented */

/* HWEVENT parameter */

क्रमागत HWEVENT_opts अणु
	HWEV_DCD_ON,
	HWEV_DCD_OFF,
	HWEV_ALL_SENT
पूर्ण;

/* channel grouping */

#घोषणा RXGROUP		0100	/* अगर set, only tx when all channels clear */
#घोषणा TXGROUP		0200	/* अगर set, करोn't transmit simultaneously */

/* Tx/Rx घड़ी sources */

क्रमागत CLOCK_sources अणु
	CLK_DPLL,	/* normal halfduplex operation */
	CLK_EXTERNAL,	/* बाह्यal घड़ीing (G3RUH/DF9IC modems) */
	CLK_DIVIDER,	/* Rx = DPLL, Tx = भागider (fullduplex with */
			/* modems without घड़ी regeneration */
	CLK_BRG		/* experimental fullduplex mode with DPLL/BRG क्रम */
			/* MODEMs without घड़ी recovery */
पूर्ण;

/* Tx state */

क्रमागत TX_state अणु
	TXS_IDLE,	/* Transmitter off, no data pending */
	TXS_BUSY,	/* रुकोing क्रम permission to send / tailसमय */
	TXS_ACTIVE,	/* Transmitter on, sending data */
	TXS_NEWFRAME,	/* reset CRC and send (next) frame */
	TXS_IDLE2,	/* Transmitter on, no data pending */
	TXS_WAIT,	/* Waiting क्रम Mपूर्णांकime to expire */
	TXS_TIMEOUT	/* We had a transmission समयout */
पूर्ण;

प्रकार अचिन्हित दीर्घ io_port;	/* type definition क्रम an 'io port address' */

/* SCC statistical inक्रमmation */

काष्ठा scc_stat अणु
        दीर्घ rxपूर्णांकs;            /* Receiver पूर्णांकerrupts */
        दीर्घ txपूर्णांकs;            /* Transmitter पूर्णांकerrupts */
        दीर्घ exपूर्णांकs;            /* External/status पूर्णांकerrupts */
        दीर्घ spपूर्णांकs;            /* Special receiver पूर्णांकerrupts */

        दीर्घ txframes;          /* Packets sent */
        दीर्घ rxframes;          /* Number of Frames Actually Received */
        दीर्घ rxerrs;            /* CRC Errors */
        दीर्घ txerrs;		/* KISS errors */
        
	अचिन्हित पूर्णांक nospace;	/* "Out of buffers" */
	अचिन्हित पूर्णांक rx_over;	/* Receiver Overruns */
	अचिन्हित पूर्णांक tx_under;	/* Transmitter Underruns */

	अचिन्हित पूर्णांक tx_state;	/* Transmitter state */
	पूर्णांक tx_queued;		/* tx frames enqueued */

	अचिन्हित पूर्णांक maxqueue;	/* allocated tx_buffers */
	अचिन्हित पूर्णांक bufsize;	/* used buffersize */
पूर्ण;

काष्ठा scc_modem अणु
	दीर्घ speed;		/* Line speed, bps */
	अक्षर घड़ीsrc;		/* 0 = DPLL, 1 = बाह्यal, 2 = भागider */
	अक्षर nrz;		/* NRZ instead of NRZI */	
पूर्ण;

काष्ठा scc_kiss_cmd अणु
	पूर्णांक  	 command;	/* one of the KISS-Commands defined above */
	अचिन्हित param;		/* KISS-Param */
पूर्ण;

काष्ठा scc_hw_config अणु
	io_port data_a;		/* data port channel A */
	io_port ctrl_a;		/* control port channel A */
	io_port data_b;		/* data port channel B */
	io_port ctrl_b;		/* control port channel B */
	io_port vector_latch;	/* INTACK-Latch (#) */
	io_port	special;	/* special function port */

	पूर्णांक	irq;		/* irq */
	दीर्घ	घड़ी;		/* घड़ी */
	अक्षर	option;		/* command क्रम function port */

	अक्षर bअक्रम;		/* hardware type */
	अक्षर escc;		/* use ext. features of a 8580/85180/85280 */
पूर्ण;

/* (#) only one INTACK latch allowed. */


काष्ठा scc_mem_config अणु
	अचिन्हित पूर्णांक dummy;
	अचिन्हित पूर्णांक bufsize;
पूर्ण;

काष्ठा scc_calibrate अणु
	अचिन्हित पूर्णांक समय;
	अचिन्हित अक्षर pattern;
पूर्ण;

#पूर्ण_अगर /* _UAPI_SCC_H */
