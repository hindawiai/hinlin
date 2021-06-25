<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * I/O Processor (IOP) defines and काष्ठाures, mostly snagged from A/UX
 * header files.
 *
 * The original header from which this was taken is copyrighted. I've करोne some
 * rewriting (in fact my changes make this a bit more पढ़ोable, IMHO) but some
 * more should be करोne.
 */

/*
 * This is the base address of the IOPs. Use this as the address of
 * a "struct iop" (see below) to see where the actual रेजिस्टरs fall.
 */

#घोषणा SCC_IOP_BASE_IIFX	(0x50F04000)
#घोषणा ISM_IOP_BASE_IIFX	(0x50F12000)

#घोषणा SCC_IOP_BASE_QUADRA	(0x50F0C000)
#घोषणा ISM_IOP_BASE_QUADRA	(0x50F1E000)

/* IOP status/control रेजिस्टर bits: */

#घोषणा	IOP_BYPASS	0x01	/* bypass-mode hardware access */
#घोषणा	IOP_AUTOINC	0x02	/* allow स्वतःincrement of ramhi/lo */
#घोषणा	IOP_RUN		0x04	/* set to 0 to reset IOP chip */
#घोषणा	IOP_IRQ		0x08	/* generate IRQ to IOP अगर 1 */
#घोषणा	IOP_INT0	0x10	/* पूर्णांकr priority from IOP to host */
#घोषणा	IOP_INT1	0x20	/* पूर्णांकr priority from IOP to host */
#घोषणा	IOP_HWINT	0x40	/* IRQ from hardware; bypass mode only */
#घोषणा	IOP_DMAINACTIVE	0x80	/* no DMA request active; bypass mode only */

#घोषणा NUM_IOPS	2
#घोषणा NUM_IOP_CHAN	7
#घोषणा NUM_IOP_MSGS	NUM_IOP_CHAN*8
#घोषणा IOP_MSG_LEN	32

/* IOP reference numbers, used by the globally-visible iop_xxx functions */

#घोषणा IOP_NUM_SCC	0
#घोषणा IOP_NUM_ISM	1

/* IOP channel states */

#घोषणा IOP_MSG_IDLE		0       /* idle                         */
#घोषणा IOP_MSG_NEW		1       /* new message sent             */
#घोषणा IOP_MSG_RCVD		2       /* message received; processing */
#घोषणा IOP_MSG_COMPLETE	3       /* message processing complete  */

/* IOP message status codes */

#घोषणा IOP_MSGSTATUS_UNUSED	0	/* Unused message काष्ठाure        */
#घोषणा IOP_MSGSTATUS_WAITING	1	/* रुकोing क्रम channel             */
#घोषणा IOP_MSGSTATUS_SENT	2	/* message sent, aरुकोing reply    */
#घोषणा IOP_MSGSTATUS_COMPLETE	3	/* message complete and reply rcvd */
#घोषणा IOP_MSGSTATUS_UNSOL	6	/* message is unsolicited          */

/* IOP memory addresses of the members of the mac_iop_kernel काष्ठाure. */

#घोषणा IOP_ADDR_MAX_SEND_CHAN	0x0200
#घोषणा IOP_ADDR_SEND_STATE	0x0201
#घोषणा IOP_ADDR_PATCH_CTRL	0x021F
#घोषणा IOP_ADDR_SEND_MSG	0x0220
#घोषणा IOP_ADDR_MAX_RECV_CHAN	0x0300
#घोषणा IOP_ADDR_RECV_STATE	0x0301
#घोषणा IOP_ADDR_ALIVE		0x031F
#घोषणा IOP_ADDR_RECV_MSG	0x0320

#अगर_अघोषित __ASSEMBLY__

/*
 * IOP Control रेजिस्टरs, staggered because in usual Apple style they were
 * too lazy to decode the A0 bit. This काष्ठाure is assumed to begin at
 * one of the xxx_IOP_BASE addresses given above.
 */

काष्ठा mac_iop अणु
    __u8	ram_addr_hi;	/* shared RAM address hi byte */
    __u8	pad0;
    __u8	ram_addr_lo;	/* shared RAM address lo byte */
    __u8	pad1;
    __u8	status_ctrl;	/* status/control रेजिस्टर */
    __u8	pad2[3];
    __u8	ram_data;	/* RAM data byte at ramhi/lo */

    __u8	pad3[23];

    /* Bypass-mode hardware access रेजिस्टरs */

    जोड़ अणु
	काष्ठा अणु		/* SCC रेजिस्टरs */
	    __u8 sccb_cmd;	/* SCC B command reg */
	    __u8 pad4;
	    __u8 scca_cmd;	/* SCC A command reg */
	    __u8 pad5;
	    __u8 sccb_data;	/* SCC B data */
	    __u8 pad6;
	    __u8 scca_data;	/* SCC A data */
	पूर्ण scc_regs;

	काष्ठा अणु		/* ISM रेजिस्टरs */
	    __u8 wdata;		/* ग_लिखो a data byte */
	    __u8 pad7;
	    __u8 wmark;		/* ग_लिखो a mark byte */
	    __u8 pad8;
	    __u8 wcrc;		/* ग_लिखो 2-byte crc to disk */
	    __u8 pad9;
	    __u8 wparams;	/* ग_लिखो the param regs */
	    __u8 pad10;
	    __u8 wphase;	/* ग_लिखो the phase states & dirs */
	    __u8 pad11;
	    __u8 wsetup;	/* ग_लिखो the setup रेजिस्टर */
	    __u8 pad12;
	    __u8 wzeroes;	/* mode reg: 1's clr bits, 0's are x */
	    __u8 pad13;
	    __u8 wones;		/* mode reg: 1's set bits, 0's are x */
	    __u8 pad14;
	    __u8 rdata;		/* पढ़ो a data byte */
	    __u8 pad15;
	    __u8 rmark;		/* पढ़ो a mark byte */
	    __u8 pad16;
	    __u8 rerror;	/* पढ़ो the error रेजिस्टर */
	    __u8 pad17;
	    __u8 rparams;	/* पढ़ो the param regs */
	    __u8 pad18;
	    __u8 rphase;	/* पढ़ो the phase states & dirs */
	    __u8 pad19;
	    __u8 rsetup;	/* पढ़ो the setup रेजिस्टर */
	    __u8 pad20;
	    __u8 rmode;		/* पढ़ो the mode रेजिस्टर */
	    __u8 pad21;
	    __u8 rhandshake;	/* पढ़ो the handshake रेजिस्टर */
	पूर्ण ism_regs;
    पूर्ण b;
पूर्ण;

/* This काष्ठाure is used to track IOP messages in the Linux kernel */

काष्ठा iop_msg अणु
	काष्ठा iop_msg	*next;		/* next message in queue or शून्य     */
	uपूर्णांक	iop_num;		/* IOP number                        */
	uपूर्णांक	channel;		/* channel number                    */
	व्योम	*caller_priv;		/* caller निजी data               */
	पूर्णांक	status;			/* status of this message            */
	__u8	message[IOP_MSG_LEN];	/* the message being sent/received   */
	__u8	reply[IOP_MSG_LEN];	/* the reply to the message          */
	व्योम	(*handler)(काष्ठा iop_msg *);
					/* function to call when reply recvd */
पूर्ण;

बाह्य पूर्णांक iop_scc_present,iop_ism_present;

बाह्य पूर्णांक iop_listen(uपूर्णांक, uपूर्णांक,
			व्योम (*handler)(काष्ठा iop_msg *),
			स्थिर अक्षर *);
बाह्य पूर्णांक iop_send_message(uपूर्णांक, uपूर्णांक, व्योम *, uपूर्णांक, __u8 *,
			    व्योम (*)(काष्ठा iop_msg *));
बाह्य व्योम iop_complete_message(काष्ठा iop_msg *);
बाह्य व्योम iop_upload_code(uपूर्णांक, __u8 *, uपूर्णांक, __u16);
बाह्य व्योम iop_करोwnload_code(uपूर्णांक, __u8 *, uपूर्णांक, __u16);
बाह्य __u8 *iop_compare_code(uपूर्णांक, __u8 *, uपूर्णांक, __u16);
बाह्य व्योम iop_ism_irq_poll(uपूर्णांक);

बाह्य व्योम iop_रेजिस्टर_पूर्णांकerrupts(व्योम);

#पूर्ण_अगर /* __ASSEMBLY__ */
