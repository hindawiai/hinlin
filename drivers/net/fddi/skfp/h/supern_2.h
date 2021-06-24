<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/******************************************************************************
 *
 *	(C)Copyright 1998,1999 SysKonnect,
 *	a business unit of Schneider & Koch & Co. Datenप्रणालीe GmbH.
 *
 *	The inक्रमmation in this file is provided "AS IS" without warranty.
 *
 ******************************************************************************/

/*
	defines क्रम AMD Supernet II chip set
	the chips are referred to as
		FPLUS	Formac Plus
		PLC	Physical Layer

	added defines क्रम AMD Supernet III chip set
	added comments on dअगरferences between Supernet II and Supernet III
	added defines क्रम the Motorola ELM (MOT_ELM)
*/

#अगर_अघोषित	_SUPERNET_
#घोषणा _SUPERNET_

/*
 * Define Supernet 3 when used
 */
#अगर_घोषित	PCI
#अगर_अघोषित	SUPERNET_3
#घोषणा	SUPERNET_3
#पूर्ण_अगर
#घोषणा TAG
#पूर्ण_अगर

#घोषणा	MB	0xff
#घोषणा	MW	0xffff
#घोषणा	MD	0xffffffff

/*
 * FORMAC frame status (rx_msext)
 */
#घोषणा	FS_EI		(1<<2)
#घोषणा	FS_AI		(1<<1)
#घोषणा	FS_CI		(1<<0)

#घोषणा FS_MSVALID	(1<<15)		/* end of queue */
#घोषणा FS_MSRABT	(1<<14)		/* frame was पातed during reception*/
#घोषणा FS_SSRCRTG	(1<<12)		/* अगर SA has set MSB (source-routing)*/
#घोषणा FS_SEAC2	(FS_EI<<9)	/* error indicator */
#घोषणा FS_SEAC1	(FS_AI<<9)	/* address indicator */
#घोषणा FS_SEAC0	(FS_CI<<9)	/* copy indicator */
#घोषणा FS_SFRMERR	(1<<8)		/* error detected (CRC or length) */
#घोषणा FS_SADRRG	(1<<7)		/* address recognized */
#घोषणा FS_SFRMTY2	(1<<6)		/* frame-class bit */
#घोषणा FS_SFRMTY1	(1<<5)		/* frame-type bit (impementor) */
#घोषणा FS_SFRMTY0	(1<<4)		/* frame-type bit (LLC) */
#घोषणा FS_ERFBB1	(1<<1)		/* byte offset (depends on LSB bit) */
#घोषणा FS_ERFBB0	(1<<0)		/*  - " - */

/*
 * status frame type
 */
#घोषणा	FRM_SMT		(0)	/* asynchr. frames */
#घोषणा	FRM_LLCA	(1)
#घोषणा	FRM_IMPA	(2)	
#घोषणा	FRM_MAC		(4)	/* synchr. frames */
#घोषणा	FRM_LLCS	(5)
#घोषणा	FRM_IMPS	(6)

/*
 * bits in rx_descr.i	(receive frame status word)
 */
#घोषणा RX_MSVALID	((दीर्घ)1<<31)	/* memory status valid */
#घोषणा RX_MSRABT	((दीर्घ)1<<30)	/* memory status receive पात */
#घोषणा RX_FS_E		((दीर्घ)FS_SEAC2<<16)	/* error indicator */
#घोषणा RX_FS_A		((दीर्घ)FS_SEAC1<<16)	/* address indicator */
#घोषणा RX_FS_C		((दीर्घ)FS_SEAC0<<16)	/* copy indicator */
#घोषणा RX_FS_CRC	((दीर्घ)FS_SFRMERR<<16)/* error detected */
#घोषणा RX_FS_ADDRESS	((दीर्घ)FS_SADRRG<<16)	/* address recognized */
#घोषणा RX_FS_MAC	((दीर्घ)FS_SFRMTY2<<16)/* MAC frame */
#घोषणा RX_FS_SMT	((दीर्घ)0<<16)		/* SMT frame */
#घोषणा RX_FS_IMPL	((दीर्घ)FS_SFRMTY1<<16)/* implementer frame */
#घोषणा RX_FS_LLC	((दीर्घ)FS_SFRMTY0<<16)/* LLC frame */

/*
 * receive frame descriptor
 */
जोड़ rx_descr अणु
	काष्ठा अणु
#अगर_घोषित	LITTLE_ENDIAN
	अचिन्हित पूर्णांक	rx_length :16 ;	/* frame length lower/upper byte */
	अचिन्हित पूर्णांक	rx_erfbb  :2 ;	/* received frame byte boundary */
	अचिन्हित पूर्णांक	rx_reserv2:2 ;	/* reserved */
	अचिन्हित पूर्णांक	rx_sfrmty :3 ;	/* frame type bits */
	अचिन्हित पूर्णांक	rx_sadrrg :1 ;	/* DA == MA or broad-/multicast */
	अचिन्हित पूर्णांक	rx_sfrmerr:1 ;	/* received frame not valid */
	अचिन्हित पूर्णांक	rx_seac0  :1 ;	/* frame-copied  C-indicator */
	अचिन्हित पूर्णांक	rx_seac1  :1 ;	/* address-match A-indicator */
	अचिन्हित पूर्णांक	rx_seac2  :1 ;	/* frame-error   E-indicator */
	अचिन्हित पूर्णांक	rx_ssrcrtg:1 ;	/* == 1 SA has MSB set */
	अचिन्हित पूर्णांक	rx_reserv1:1 ;	/* reserved */
	अचिन्हित पूर्णांक	rx_msrabt :1 ;	/* memory status receive पात */
	अचिन्हित पूर्णांक	rx_msvalid:1 ;	/* memory status valid */
#अन्यथा
	अचिन्हित पूर्णांक	rx_msvalid:1 ;	/* memory status valid */
	अचिन्हित पूर्णांक	rx_msrabt :1 ;	/* memory status receive पात */
	अचिन्हित पूर्णांक	rx_reserv1:1 ;	/* reserved */
	अचिन्हित पूर्णांक	rx_ssrcrtg:1 ;	/* == 1 SA has MSB set */
	अचिन्हित पूर्णांक	rx_seac2  :1 ;	/* frame-error   E-indicator */
	अचिन्हित पूर्णांक	rx_seac1  :1 ;	/* address-match A-indicator */
	अचिन्हित पूर्णांक	rx_seac0  :1 ;	/* frame-copied  C-indicator */
	अचिन्हित पूर्णांक	rx_sfrmerr:1 ;	/* received frame not valid */
	अचिन्हित पूर्णांक	rx_sadrrg :1 ;	/* DA == MA or broad-/multicast */
	अचिन्हित पूर्णांक	rx_sfrmty :3 ;	/* frame type bits */
	अचिन्हित पूर्णांक	rx_erfbb  :2 ;	/* received frame byte boundary */
	अचिन्हित पूर्णांक	rx_reserv2:2 ;	/* reserved */
	अचिन्हित पूर्णांक	rx_length :16 ;	/* frame length lower/upper byte */
#पूर्ण_अगर
	पूर्ण r ;
	दीर्घ	i ;
पूर्ण ;

/* defines क्रम Receive Frame Descriptor access */
#घोषणा RD_S_ERFBB	0x00030000L	/* received frame byte boundary */
#घोषणा RD_S_RES2	0x000c0000L	/* reserved */
#घोषणा RD_S_SFRMTY	0x00700000L	/* frame type bits */
#घोषणा RD_S_SADRRG	0x00800000L	/* DA == MA or broad-/multicast */
#घोषणा RD_S_SFRMERR	0x01000000L	/* received frame not valid */
#घोषणा	RD_S_SEAC	0x0e000000L	/* frame status indicators */
#घोषणा RD_S_SEAC0	0x02000000L	/* frame-copied  हाल-indicator */
#घोषणा RD_S_SEAC1	0x04000000L	/* address-match A-indicator */
#घोषणा RD_S_SEAC2	0x08000000L	/* frame-error   E-indicator */
#घोषणा RD_S_SSRCRTG	0x10000000L	/* == 1 SA has MSB set */
#घोषणा RD_S_RES1	0x20000000L	/* reserved */
#घोषणा RD_S_MSRABT	0x40000000L	/* memory status receive पात */
#घोषणा RD_S_MSVALID	0x80000000L	/* memory status valid */

#घोषणा	RD_STATUS	0xffff0000L
#घोषणा	RD_LENGTH	0x0000ffffL

/* defines क्रम Receive Frames Status Word values */
/*RD_S_SFRMTY*/
#घोषणा RD_FRM_SMT	(अचिन्हित दीर्घ)(0<<20)     /* asynchr. frames */
#घोषणा RD_FRM_LLCA	(अचिन्हित दीर्घ)(1<<20)
#घोषणा RD_FRM_IMPA	(अचिन्हित दीर्घ)(2<<20)
#घोषणा RD_FRM_MAC	(अचिन्हित दीर्घ)(4<<20)     /* synchr. frames */
#घोषणा RD_FRM_LLCS	(अचिन्हित दीर्घ)(5<<20)
#घोषणा RD_FRM_IMPS	(अचिन्हित दीर्घ)(6<<20)

#घोषणा TX_DESCRIPTOR	0x40000000L
#घोषणा TX_OFFSET_3	0x18000000L

#घोषणा TXP1	2

/*
 * transmit frame descriptor
 */
जोड़ tx_descr अणु
	काष्ठा अणु
#अगर_घोषित	LITTLE_ENDIAN
	अचिन्हित पूर्णांक	tx_length:16 ;	/* frame length lower/upper byte */
	अचिन्हित पूर्णांक	tx_res	 :8 ;	/* reserved 	 (bit 16..23) */
	अचिन्हित पूर्णांक	tx_xmtabt:1 ;	/* transmit पात */
	अचिन्हित पूर्णांक	tx_nfcs  :1 ;	/* no frame check sequence */
	अचिन्हित पूर्णांक	tx_xकरोne :1 ;	/* give up token */
	अचिन्हित पूर्णांक	tx_rpxm  :2 ;	/* byte offset */
	अचिन्हित पूर्णांक	tx_pat1  :2 ;	/* must be TXP1 */
	अचिन्हित पूर्णांक	tx_more	 :1 ;	/* more frame in chain */
#अन्यथा
	अचिन्हित पूर्णांक	tx_more	 :1 ;	/* more frame in chain */
	अचिन्हित पूर्णांक	tx_pat1  :2 ;	/* must be TXP1 */
	अचिन्हित पूर्णांक	tx_rpxm  :2 ;	/* byte offset */
	अचिन्हित पूर्णांक	tx_xकरोne :1 ;	/* give up token */
	अचिन्हित पूर्णांक	tx_nfcs  :1 ;	/* no frame check sequence */
	अचिन्हित पूर्णांक	tx_xmtabt:1 ;	/* transmit पात */
	अचिन्हित पूर्णांक	tx_res	 :8 ;	/* reserved 	 (bit 16..23) */
	अचिन्हित पूर्णांक	tx_length:16 ;	/* frame length lower/upper byte */
#पूर्ण_अगर
	पूर्ण t ;
	दीर्घ	i ;
पूर्ण ;

/* defines क्रम Transmit Descriptor access */
#घोषणा	TD_C_MORE	0x80000000L	/* more frame in chain */
#घोषणा	TD_C_DESCR	0x60000000L	/* must be TXP1 */
#घोषणा	TD_C_TXFBB	0x18000000L	/* byte offset */
#घोषणा	TD_C_XDONE	0x04000000L	/* give up token */
#घोषणा TD_C_NFCS	0x02000000L	/* no frame check sequence */
#घोषणा TD_C_XMTABT	0x01000000L	/* transmit पात */

#घोषणा	TD_C_LNCNU	0x0000ff00L	
#घोषणा TD_C_LNCNL	0x000000ffL
#घोषणा TD_C_LNCN	0x0000ffffL	/* frame length lower/upper byte */
 
/*
 * transmit poपूर्णांकer
 */
जोड़ tx_poपूर्णांकer अणु
	काष्ठा t अणु
#अगर_घोषित	LITTLE_ENDIAN
	अचिन्हित पूर्णांक	tp_poपूर्णांकer:16 ;	/* poपूर्णांकer to tx_descr (low/high) */
	अचिन्हित पूर्णांक	tp_res	  :8 ;	/* reserved 	 (bit 16..23) */
	अचिन्हित पूर्णांक	tp_pattern:8 ;	/* fixed pattern (bit 24..31) */
#अन्यथा
	अचिन्हित पूर्णांक	tp_pattern:8 ;	/* fixed pattern (bit 24..31) */
	अचिन्हित पूर्णांक	tp_res	  :8 ;	/* reserved 	 (bit 16..23) */
	अचिन्हित पूर्णांक	tp_poपूर्णांकer:16 ;	/* poपूर्णांकer to tx_descr (low/high) */
#पूर्ण_अगर
	पूर्ण t ;
	दीर्घ	i ;
पूर्ण ;

/* defines क्रम Nontag Mode Poपूर्णांकer access */
#घोषणा	TD_P_CNTRL	0xff000000L
#घोषणा TD_P_RPXU	0x0000ff00L
#घोषणा TD_P_RPXL	0x000000ffL
#घोषणा TD_P_RPX	0x0000ffffL


#घोषणा TX_PATTERN	0xa0
#घोषणा TX_POINTER_END	0xa0000000L
#घोषणा TX_INT_PATTERN	0xa0000000L

काष्ठा tx_queue अणु
	काष्ठा tx_queue *tq_next ;
	u_लघु tq_pack_offset ;	/* offset buffer memory */
	u_अक्षर  tq_pad[2] ;
पूर्ण ;

/*
	defines क्रम FORMAC Plus (Am79C830)
*/

/*
 *  FORMAC+ पढ़ो/ग_लिखो (r/w) रेजिस्टरs
 */
#घोषणा FM_CMDREG1	0x00		/* ग_लिखो command reg 1 inकाष्ठाion */
#घोषणा FM_CMDREG2	0x01		/* ग_लिखो command reg 2 inकाष्ठाion */
#घोषणा FM_ST1U		0x00		/* पढ़ो upper 16-bit of status reg 1 */
#घोषणा FM_ST1L		0x01		/* पढ़ो lower 16-bit of status reg 1 */
#घोषणा FM_ST2U		0x02		/* पढ़ो upper 16-bit of status reg 2 */
#घोषणा FM_ST2L		0x03		/* पढ़ो lower 16-bit of status reg 2 */
#घोषणा FM_IMSK1U	0x04		/* r/w upper 16-bit of IMSK 1 */
#घोषणा FM_IMSK1L	0x05		/* r/w lower 16-bit of IMSK 1 */
#घोषणा FM_IMSK2U	0x06		/* r/w upper 16-bit of IMSK 2 */
#घोषणा FM_IMSK2L	0x07		/* r/w lower 16-bit of IMSK 2 */
#घोषणा FM_SAID		0x08		/* r/w लघु addr.-inभागidual */
#घोषणा FM_LAIM		0x09		/* r/w दीर्घ addr.-ind. (MSW of LAID) */
#घोषणा FM_LAIC		0x0a		/* r/w दीर्घ addr.-ind. (middle)*/
#घोषणा FM_LAIL		0x0b		/* r/w दीर्घ addr.-ind. (LSW) */
#घोषणा FM_SAGP		0x0c		/* r/w लघु address-group */
#घोषणा FM_LAGM		0x0d		/* r/w दीर्घ addr.-gr. (MSW of LAGP) */
#घोषणा FM_LAGC		0x0e		/* r/w दीर्घ addr.-gr. (middle) */
#घोषणा FM_LAGL		0x0f		/* r/w दीर्घ addr.-gr. (LSW) */
#घोषणा FM_MDREG1	0x10		/* r/w 16-bit mode reg 1 */
#घोषणा FM_STMCHN	0x11		/* पढ़ो state-machine reg */
#घोषणा FM_MIR1		0x12		/* पढ़ो upper 16-bit of MAC Info Reg */
#घोषणा FM_MIR0		0x13		/* पढ़ो lower 16-bit of MAC Info Reg */
#घोषणा FM_TMAX		0x14		/* r/w 16-bit TMAX reg */
#घोषणा FM_TVX		0x15		/* ग_लिखो 8-bit TVX reg with NP7-0
					   पढ़ो TVX on NP7-0, समयr on NP15-8*/
#घोषणा FM_TRT		0x16		/* r/w upper 16-bit of TRT समयr */
#घोषणा FM_THT		0x17		/* r/w upper 16-bit of THT समयr */
#घोषणा FM_TNEG		0x18		/* पढ़ो upper 16-bit of TNEG (TTRT) */
#घोषणा FM_TMRS		0x19		/* पढ़ो lower 5-bit of TNEG,TRT,THT */
			/* F E D C  B A 9 8  7 6 5 4  3 2 1 0
			   x |-TNEG4-0| |-TRT4-0-| |-THT4-0-| (x-late count) */
#घोषणा FM_TREQ0	0x1a		/* r/w 16-bit TREQ0 reg (LSW of TRT) */
#घोषणा FM_TREQ1	0x1b		/* r/w 16-bit TREQ1 reg (MSW of TRT) */
#घोषणा FM_PRI0		0x1c		/* r/w priority r. क्रम asyn.-queue 0 */
#घोषणा FM_PRI1		0x1d		/* r/w priority r. क्रम asyn.-queue 1 */
#घोषणा FM_PRI2		0x1e		/* r/w priority r. क्रम asyn.-queue 2 */
#घोषणा FM_TSYNC	0x1f		/* r/w 16-bit of the TSYNC रेजिस्टर */
#घोषणा FM_MDREG2	0x20		/* r/w 16-bit mode reg 2 */
#घोषणा FM_FRMTHR	0x21		/* r/w the frame threshold रेजिस्टर */
#घोषणा FM_EACB		0x22		/* r/w end addr of claim/beacon area */
#घोषणा FM_EARV		0x23		/* r/w end addr of receive queue */
/* Supernet 3 */
#घोषणा	FM_EARV1	FM_EARV

#घोषणा FM_EAS		0x24		/* r/w end addr of synchr. queue */
#घोषणा FM_EAA0		0x25		/* r/w end addr of asyn. queue 0 */
#घोषणा FM_EAA1		0x26		/* r/w end addr of asyn. queue 1 */
#घोषणा FM_EAA2		0x27		/* r/w end addr of asyn. queue 2 */
#घोषणा FM_SACL		0x28		/* r/w start addr of claim frame */
#घोषणा FM_SABC		0x29		/* r/w start addr of beacon frame */
#घोषणा FM_WPXSF	0x2a		/* r/w the ग_लिखो ptr. क्रम special fr.*/
#घोषणा FM_RPXSF	0x2b		/* r/w the पढ़ो ptr. क्रम special fr. */
#घोषणा FM_RPR		0x2d		/* r/w the पढ़ो ptr. क्रम receive qu. */
#घोषणा FM_WPR		0x2e		/* r/w the ग_लिखो ptr. क्रम receive qu.*/
#घोषणा FM_SWPR		0x2f		/* r/w the shaकरोw wr.-ptr. क्रम rec.q.*/
/* Supernet 3 */ 
#घोषणा FM_RPR1         FM_RPR   
#घोषणा FM_WPR1         FM_WPR 
#घोषणा FM_SWPR1        FM_SWPR

#घोषणा FM_WPXS		0x30		/* r/w the ग_लिखो ptr. क्रम synchr. qu.*/
#घोषणा FM_WPXA0	0x31		/* r/w the ग_लिखो ptr. क्रम asyn. qu.0 */
#घोषणा FM_WPXA1	0x32		/* r/w the ग_लिखो ptr. क्रम asyn. qu.1 */
#घोषणा FM_WPXA2	0x33		/* r/w the ग_लिखो ptr. क्रम asyn. qu.2 */
#घोषणा FM_SWPXS	0x34		/* r/w the shaकरोw wr.-ptr. क्रम syn.q.*/
#घोषणा FM_SWPXA0	0x35		/* r/w the shad. wr.-ptr. क्रम asyn.q0*/
#घोषणा FM_SWPXA1	0x36		/* r/w the shad. wr.-ptr. क्रम asyn.q1*/
#घोषणा FM_SWPXA2	0x37		/* r/w the shad. wr.-ptr. क्रम asyn.q2*/
#घोषणा FM_RPXS		0x38		/* r/w the पढ़ो ptr. क्रम synchr. qu. */
#घोषणा FM_RPXA0	0x39		/* r/w the पढ़ो ptr. क्रम asyn. qu. 0 */
#घोषणा FM_RPXA1	0x3a		/* r/w the पढ़ो ptr. क्रम asyn. qu. 1 */
#घोषणा FM_RPXA2	0x3b		/* r/w the पढ़ो ptr. क्रम asyn. qu. 2 */
#घोषणा FM_MARR		0x3c		/* r/w the memory पढ़ो addr रेजिस्टर */
#घोषणा FM_MARW		0x3d		/* r/w the memory ग_लिखो addr रेजिस्टर*/
#घोषणा FM_MDRU		0x3e		/* r/w upper 16-bit of mem. data reg */
#घोषणा FM_MDRL		0x3f		/* r/w lower 16-bit of mem. data reg */

/* following inकाष्ठाions relate to MAC counters and समयr */
#घोषणा FM_TMSYNC	0x40		/* r/w upper 16 bits of TMSYNC समयr */
#घोषणा FM_FCNTR	0x41		/* r/w the 16-bit frame counter */
#घोषणा FM_LCNTR	0x42		/* r/w the 16-bit lost counter */
#घोषणा FM_ECNTR	0x43		/* r/w the 16-bit error counter */

/* Supernet 3:	extensions to old रेजिस्टर block */
#घोषणा	FM_FSCNTR	0x44		/* r/? Frame Strip Counter */
#घोषणा	FM_FRSELREG	0x45		/* r/w Frame Selection Register */

/* Supernet 3:	extensions क्रम 2. receive queue etc. */
#घोषणा	FM_MDREG3	0x60		/* r/w Mode Register 3 */
#घोषणा	FM_ST3U		0x61		/* पढ़ो upper 16-bit of status reg 3 */
#घोषणा	FM_ST3L		0x62		/* पढ़ो lower 16-bit of status reg 3 */
#घोषणा	FM_IMSK3U	0x63		/* r/w upper 16-bit of IMSK reg 3 */
#घोषणा	FM_IMSK3L	0x64		/* r/w lower 16-bit of IMSK reg 3 */
#घोषणा	FM_IVR		0x65		/* पढ़ो Interrupt Vector रेजिस्टर */
#घोषणा	FM_IMR		0x66		/* r/w Interrupt mask रेजिस्टर */
/* 0x67	Hidden */
#घोषणा	FM_RPR2		0x68		/* r/w the पढ़ो ptr. क्रम rec. qu. 2 */
#घोषणा	FM_WPR2		0x69		/* r/w the ग_लिखो ptr. क्रम rec. qu. 2 */
#घोषणा	FM_SWPR2	0x6a		/* r/w the shaकरोw wptr. क्रम rec. q. 2 */
#घोषणा	FM_EARV2	0x6b		/* r/w end addr of rec. qu. 2 */
#घोषणा	FM_UNLCKDLY	0x6c		/* r/w Auto Unlock Delay रेजिस्टर */
					/* Bit 15-8: RECV2 unlock threshold */
					/* Bit  7-0: RECV1 unlock threshold */
/* 0x6f-0x73	Hidden */
#घोषणा	FM_LTDPA1	0x79		/* r/w Last Trans desc ptr क्रम A1 qu. */
/* 0x80-0x9a	PLCS रेजिस्टरs of built-in PLCS  (Supernet 3 only) */

/* Supernet 3: Adderss Filter Registers */
#घोषणा	FM_AFCMD	0xb0		/* r/w Address Filter Command Reg */
#घोषणा	FM_AFSTAT	0xb2		/* r/w Address Filter Status Reg */
#घोषणा	FM_AFBIST	0xb4		/* r/w Address Filter BIST signature */
#घोषणा	FM_AFCOMP2	0xb6		/* r/w Address Filter Compaअक्रम 2 */
#घोषणा	FM_AFCOMP1	0xb8		/* r/w Address Filter Compaअक्रम 1 */
#घोषणा	FM_AFCOMP0	0xba		/* r/w Address Filter Compaअक्रम 0 */
#घोषणा	FM_AFMASK2	0xbc		/* r/w Address Filter Mask 2 */
#घोषणा	FM_AFMASK1	0xbe		/* r/w Address Filter Mask 1 */
#घोषणा	FM_AFMASK0	0xc0		/* r/w Address Filter Mask 0 */
#घोषणा	FM_AFPERS	0xc2		/* r/w Address Filter Personality Reg */

/* Supernet 3: Orion (PDX?) Registers */
#घोषणा	FM_ORBIST	0xd0		/* r/w Orion BIST signature */
#घोषणा	FM_ORSTAT	0xd2		/* r/w Orion Status Register */


/*
 * Mode Register 1 (MDREG1)
 */
#घोषणा FM_RES0		0x0001		/* reserved */
					/* SN3: other definition */
#घोषणा	FM_XMTINH_HOLD	0x0002		/* transmit-inhibit/hold bit */
					/* SN3: other definition */
#घोषणा	FM_HOFLXI	0x0003		/* SN3: Hold / Flush / Inhibit */
#घोषणा	FM_FULL_HALF	0x0004		/* full-duplex/half-duplex bit */
#घोषणा	FM_LOCKTX	0x0008		/* lock-transmit-asynchr.-queues bit */
#घोषणा FM_EXGPA0	0x0010		/* extended-group-addressing bit 0 */
#घोषणा FM_EXGPA1	0x0020		/* extended-group-addressing bit 1 */
#घोषणा FM_DISCRY	0x0040		/* disable-carry bit */
					/* SN3: reserved */
#घोषणा FM_SELRA	0x0080		/* select input from PHY (1=RA,0=RB) */

#घोषणा FM_ADDET	0x0700		/* address detection */
#घोषणा FM_MDAMA	(0<<8)		/* address detection : DA = MA */
#घोषणा FM_MDASAMA	(1<<8)		/* address detection : DA=MA||SA=MA */
#घोषणा	FM_MRNNSAFNMA	(2<<8)		/* rec. non-NSA frames DA=MA&&SA!=MA */
#घोषणा	FM_MRNNSAF	(3<<8)		/* rec. non-NSA frames DA = MA */
#घोषणा	FM_MDISRCV	(4<<8)		/* disable receive function */
#घोषणा	FM_MRES0	(5<<8)		/* reserve */
#घोषणा	FM_MLIMPROM	(6<<8)		/* limited-promiscuous mode */
#घोषणा FM_MPROMISCOUS	(7<<8)		/* address detection : promiscuous */

#घोषणा FM_SELSA	0x0800		/* select-लघु-address bit */

#घोषणा FM_MMODE	0x7000		/* mode select */
#घोषणा FM_MINIT	(0<<12)		/* initialize */
#घोषणा FM_MMEMACT	(1<<12)		/* memory activate */
#घोषणा FM_MONLINESP	(2<<12)		/* on-line special */
#घोषणा FM_MONLINE	(3<<12)		/* on-line (FDDI operational mode) */
#घोषणा FM_MILOOP	(4<<12)		/* पूर्णांकernal loopback */
#घोषणा FM_MRES1	(5<<12)		/* reserved */
#घोषणा FM_MRES2	(6<<12)		/* reserved */
#घोषणा FM_MELOOP	(7<<12)		/* बाह्यal loopback */

#घोषणा	FM_SNGLFRM	0x8000		/* single-frame-receive mode */
					/* SN3: reserved */

#घोषणा	MDR1INIT	(FM_MINIT | FM_MDAMA)

/*
 * Mode Register 2 (MDREG2)
 */
#घोषणा	FM_AFULL	0x000f		/* 4-bit value (empty loc.in txqueue)*/
#घोषणा	FM_RCVERR	0x0010		/* rec.-errored-frames bit */
#घोषणा	FM_SYMCTL	0x0020		/* sysmbol-control bit */
					/* SN3: reserved */
#घोषणा	FM_SYNPRQ	0x0040		/* synchron.-NP-DMA-request bit */
#घोषणा	FM_ENNPRQ	0x0080		/* enable-NP-DMA-request bit */
#घोषणा	FM_ENHSRQ	0x0100		/* enable-host-request bit */
#घोषणा	FM_RXFBB01	0x0600		/* rec. frame byte boundary bit0 & 1 */
#घोषणा	FM_LSB		0x0800		/* determ. ordering of bytes in buffer*/
#घोषणा	FM_PARITY	0x1000		/* 1 = even, 0 = odd */
#घोषणा	FM_CHKPAR	0x2000		/* 1 = parity of 32-bit buffer BD-bus*/
#घोषणा	FM_STRPFCS	0x4000		/* 1 = strips FCS field of rec.frame */
#घोषणा	FM_BMMODE	0x8000		/* Buffer-Memory-Mode (1 = tag mode) */
					/* SN3: 1 = tag, 0 = modअगरied tag */

/*
 * Status Register 1, Upper 16 Bits (ST1U)
 */
#घोषणा FM_STEFRMS	0x0001		/* transmit end of frame: synchr. qu.*/
#घोषणा FM_STEFRMA0	0x0002		/* transmit end of frame: asyn. qu.0 */
#घोषणा FM_STEFRMA1	0x0004		/* transmit end of frame: asyn. qu.1 */
#घोषणा FM_STEFRMA2	0x0008		/* transmit end of frame: asyn. qu.2 */
					/* SN3: reserved */
#घोषणा FM_STECFRMS	0x0010		/* transmit end of chain of syn. qu. */
					/* SN3: reserved */
#घोषणा FM_STECFRMA0	0x0020		/* transmit end of chain of asyn. q0 */
					/* SN3: reserved */
#घोषणा FM_STECFRMA1	0x0040		/* transmit end of chain of asyn. q1 */
					/* SN3: STECMDA1 */
#घोषणा FM_STECMDA1	0x0040		/* SN3: 'no description' */
#घोषणा FM_STECFRMA2	0x0080		/* transmit end of chain of asyn. q2 */
					/* SN3: reserved */
#घोषणा	FM_STEXDONS	0x0100		/* transmit until XDONE in syn. qu. */
#घोषणा	FM_STBFLA	0x0200		/* asynchr.-queue trans. buffer full */
#घोषणा	FM_STBFLS	0x0400		/* synchr.-queue transm. buffer full */
#घोषणा	FM_STXABRS	0x0800		/* synchr. queue transmit-पात */
#घोषणा	FM_STXABRA0	0x1000		/* asynchr. queue 0 transmit-पात */
#घोषणा	FM_STXABRA1	0x2000		/* asynchr. queue 1 transmit-पात */
#घोषणा	FM_STXABRA2	0x4000		/* asynchr. queue 2 transmit-पात */
					/* SN3: reserved */
#घोषणा	FM_SXMTABT	0x8000		/* transmit पात */

/*
 * Status Register 1, Lower 16 Bits (ST1L)
 */
#घोषणा FM_SQLCKS	0x0001		/* queue lock क्रम synchr. queue */
#घोषणा FM_SQLCKA0	0x0002		/* queue lock क्रम asynchr. queue 0 */
#घोषणा FM_SQLCKA1	0x0004		/* queue lock क्रम asynchr. queue 1 */
#घोषणा FM_SQLCKA2	0x0008		/* queue lock क्रम asynchr. queue 2 */
					/* SN3: reserved */
#घोषणा FM_STXINFLS	0x0010		/* transmit inकाष्ठाion full: syn. */
					/* SN3: reserved */
#घोषणा FM_STXINFLA0	0x0020		/* transmit inकाष्ठाion full: asyn.0 */
					/* SN3: reserved */
#घोषणा FM_STXINFLA1	0x0040		/* transmit inकाष्ठाion full: asyn.1 */
					/* SN3: reserved */
#घोषणा FM_STXINFLA2	0x0080		/* transmit inकाष्ठाion full: asyn.2 */
					/* SN3: reserved */
#घोषणा FM_SPCEPDS	0x0100		/* parity/coding error: syn. queue */
#घोषणा FM_SPCEPDA0	0x0200		/* parity/coding error: asyn. queue0 */
#घोषणा FM_SPCEPDA1	0x0400		/* parity/coding error: asyn. queue1 */
#घोषणा FM_SPCEPDA2	0x0800		/* parity/coding error: asyn. queue2 */
					/* SN3: reserved */
#घोषणा FM_STBURS	0x1000		/* transmit buffer underrun: syn. q. */
#घोषणा FM_STBURA0	0x2000		/* transmit buffer underrun: asyn.0 */
#घोषणा FM_STBURA1	0x4000		/* transmit buffer underrun: asyn.1 */
#घोषणा FM_STBURA2	0x8000		/* transmit buffer underrun: asyn.2 */
					/* SN3: reserved */

/*
 * Status Register 2, Upper 16 Bits (ST2U)
 */
#घोषणा FM_SOTRBEC	0x0001		/* other beacon received */
#घोषणा FM_SMYBEC	0x0002		/* my beacon received */
#घोषणा FM_SBEC		0x0004		/* beacon state entered */
#घोषणा FM_SLOCLM	0x0008		/* low claim received */
#घोषणा FM_SHICLM	0x0010		/* high claim received */
#घोषणा FM_SMYCLM	0x0020		/* my claim received */
#घोषणा FM_SCLM		0x0040		/* claim state entered */
#घोषणा FM_SERRSF	0x0080		/* error in special frame */
#घोषणा FM_SNFSLD	0x0100		/* NP and FORMAC+ simultaneous load */
#घोषणा FM_SRFRCTOV	0x0200		/* receive frame counter overflow */
					/* SN3: reserved */
#घोषणा FM_SRCVFRM	0x0400		/* receive frame */
					/* SN3: reserved */
#घोषणा FM_SRCVOVR	0x0800		/* receive FIFO overflow */
#घोषणा FM_SRBFL	0x1000		/* receive buffer full */
#घोषणा FM_SRABT	0x2000		/* receive पात */
#घोषणा FM_SRBMT	0x4000		/* receive buffer empty */
#घोषणा FM_SRCOMP	0x8000		/* receive complete. Nontag mode */

/*
 * Status Register 2, Lower 16 Bits (ST2L)
 * Attention: SN3 करोcu shows these bits the other way around
 */
#घोषणा FM_SRES0	0x0001		/* reserved */
#घोषणा FM_SESTRIPTK	0x0001		/* SN3: 'no description' */
#घोषणा FM_STRTEXR	0x0002		/* TRT expired in claim | beacon st. */
#घोषणा FM_SDUPCLM	0x0004		/* duplicate claim received */
#घोषणा FM_SSIFG	0x0008		/* लघु पूर्णांकerframe gap */
#घोषणा FM_SFRMCTR	0x0010		/* frame counter overflow */
#घोषणा FM_SERRCTR	0x0020		/* error counter overflow */
#घोषणा FM_SLSTCTR	0x0040		/* lost counter overflow */
#घोषणा FM_SPHINV	0x0080		/* PHY invalid */
#घोषणा FM_SADET	0x0100		/* address detect */
#घोषणा FM_SMISFRM	0x0200		/* missed frame */
#घोषणा FM_STRTEXP	0x0400		/* TRT expired and late count > 0 */
#घोषणा FM_STVXEXP	0x0800		/* TVX expired */
#घोषणा FM_STKISS	0x1000		/* token issued */
#घोषणा FM_STKERR	0x2000		/* token error */
#घोषणा FM_SMULTDA	0x4000		/* multiple destination address */
#घोषणा FM_SRNGOP	0x8000		/* ring operational */

/*
 * Supernet 3:
 * Status Register 3, Upper 16 Bits (ST3U)
 */
#घोषणा	FM_SRQUNLCK1	0x0001		/* receive queue unlocked queue 1 */
#घोषणा	FM_SRQUNLCK2	0x0002		/* receive queue unlocked queue 2 */
#घोषणा	FM_SRPERRQ1	0x0004		/* receive parity error rx queue 1 */
#घोषणा	FM_SRPERRQ2	0x0008		/* receive parity error rx queue 2 */
					/* Bit 4-10: reserved */
#घोषणा	FM_SRCVOVR2	0x0800		/* receive FIFO overfull rx queue 2 */
#घोषणा	FM_SRBFL2	0x1000		/* receive buffer full rx queue 2 */
#घोषणा	FM_SRABT2	0x2000		/* receive पात rx queue 2 */
#घोषणा	FM_SRBMT2	0x4000		/* receive buf empty rx queue 2 */
#घोषणा	FM_SRCOMP2	0x8000		/* receive comp rx queue 2 */

/*
 * Supernet 3:
 * Status Register 3, Lower 16 Bits (ST3L)
 */
#घोषणा	FM_AF_BIST_DONE		0x0001	/* Address Filter BIST is करोne */
#घोषणा	FM_PLC_BIST_DONE	0x0002	/* पूर्णांकernal PLC Bist is करोne */
#घोषणा	FM_PDX_BIST_DONE	0x0004	/* PDX BIST is करोne */
					/* Bit  3: reserved */
#घोषणा	FM_SICAMDAMAT		0x0010	/* Status पूर्णांकernal CAM DA match */
#घोषणा	FM_SICAMDAXACT		0x0020	/* Status पूर्णांकernal CAM DA exact match */
#घोषणा	FM_SICAMSAMAT		0x0040	/* Status पूर्णांकernal CAM SA match */
#घोषणा	FM_SICAMSAXACT		0x0080	/* Status पूर्णांकernal CAM SA exact match */

/*
 * MAC State-Machine Register FM_STMCHN
 */
#घोषणा	FM_MDRTAG	0x0004		/* tag bit of दीर्घ word पढ़ो */
#घोषणा	FM_SNPPND	0x0008		/* r/w from buffer mem. is pending */
#घोषणा	FM_TXSTAT	0x0070		/* transmitter state machine state */
#घोषणा	FM_RCSTAT	0x0380		/* receiver state machine state */
#घोषणा	FM_TM01		0x0c00		/* indicate token mode */
#घोषणा	FM_SIM		0x1000		/* indicate send immediate-mode */
#घोषणा	FM_REV		0xe000		/* FORMAC Plus revision number */

/*
 * Supernet 3
 * Mode Register 3
 */
#घोषणा	FM_MENRS	0x0001		/* Ena enhanced rec status encoding */
#घोषणा	FM_MENXS	0x0002		/* Ena enhanced xmit status encoding */
#घोषणा	FM_MENXCT	0x0004		/* Ena EXACT/INEXACT matching */
#घोषणा	FM_MENAFULL	0x0008		/* Ena enh QCTRL encoding क्रम AFULL */
#घोषणा	FM_MEIND	0x0030		/* Ena enh A,C indicator settings */
#घोषणा	FM_MENQCTRL	0x0040		/* Ena enh QCTRL encoding */
#घोषणा	FM_MENRQAUNLCK	0x0080		/* Ena rec q स्वतः unlock */
#घोषणा	FM_MENDAS	0x0100		/* Ena DAS connections by cntr MUX */
#घोषणा	FM_MENPLCCST	0x0200		/* Ena Counter Segm test in PLC blck */
#घोषणा	FM_MENSGLINT	0x0400		/* Ena Vectored Interrupt पढ़ोing */
#घोषणा	FM_MENDRCV	0x0800		/* Ena dual receive queue operation */
#घोषणा	FM_MENFCLOC	0x3000		/* Ena FC location within frm data */
#घोषणा	FM_MENTRCMD	0x4000		/* Ena ASYNC1 xmit only after command */
#घोषणा	FM_MENTDLPBK	0x8000		/* Ena TDAT to RDAT lkoopback */

/*
 * Supernet 3
 * Frame Selection Register
 */
#घोषणा	FM_RECV1	0x000f		/* options क्रम receive queue 1 */
#घोषणा	FM_RCV1_ALL	(0<<0)		/* receive all frames */
#घोषणा	FM_RCV1_LLC	(1<<0)		/* rec all LLC frames */
#घोषणा	FM_RCV1_SMT	(2<<0)		/* rec all SMT frames */
#घोषणा	FM_RCV1_NSMT	(3<<0)		/* rec non-SMT frames */
#घोषणा	FM_RCV1_IMP	(4<<0)		/* rec Implementor frames */
#घोषणा	FM_RCV1_MAC	(5<<0)		/* rec all MAC frames */
#घोषणा	FM_RCV1_SLLC	(6<<0)		/* rec all sync LLC frames */
#घोषणा	FM_RCV1_ALLC	(7<<0)		/* rec all async LLC frames */
#घोषणा	FM_RCV1_VOID	(8<<0)		/* rec all व्योम frames */
#घोषणा	FM_RCV1_ALSMT	(9<<0)		/* rec all async LLC & SMT frames */
#घोषणा	FM_RECV2	0x00f0		/* options क्रम receive queue 2 */
#घोषणा	FM_RCV2_ALL	(0<<4)		/* receive all other frames */
#घोषणा	FM_RCV2_LLC	(1<<4)		/* rec all LLC frames */
#घोषणा	FM_RCV2_SMT	(2<<4)		/* rec all SMT frames */
#घोषणा	FM_RCV2_NSMT	(3<<4)		/* rec non-SMT frames */
#घोषणा	FM_RCV2_IMP	(4<<4)		/* rec Implementor frames */
#घोषणा	FM_RCV2_MAC	(5<<4)		/* rec all MAC frames */
#घोषणा	FM_RCV2_SLLC	(6<<4)		/* rec all sync LLC frames */
#घोषणा	FM_RCV2_ALLC	(7<<4)		/* rec all async LLC frames */
#घोषणा	FM_RCV2_VOID	(8<<4)		/* rec all व्योम frames */
#घोषणा	FM_RCV2_ALSMT	(9<<4)		/* rec all async LLC & SMT frames */
#घोषणा	FM_ENXMTADSWAP	0x4000		/* enh rec addr swap (phys -> can) */
#घोषणा	FM_ENRCVADSWAP	0x8000		/* enh tx addr swap (can -> phys) */

/*
 * Supernet 3:
 * Address Filter Command Register (AFCMD)
 */
#घोषणा	FM_INST		0x0007		/* Address Filter Operation */
#घोषणा FM_IINV_CAM	(0<<0)		/* Invalidate CAM */
#घोषणा FM_IWRITE_CAM	(1<<0)		/* Write CAM */
#घोषणा FM_IREAD_CAM	(2<<0)		/* Read CAM */
#घोषणा FM_IRUN_BIST	(3<<0)		/* Run BIST */
#घोषणा FM_IFIND	(4<<0)		/* Find */
#घोषणा FM_IINV		(5<<0)		/* Invalidate */
#घोषणा FM_ISKIP	(6<<0)		/* Skip */
#घोषणा FM_ICL_SKIP	(7<<0)		/* Clear all SKIP bits */

/*
 * Supernet 3:
 * Address Filter Status Register (AFSTAT)
 */
					/* Bit  0-4: reserved */
#घोषणा	FM_REV_NO	0x00e0		/* Revision Number of Address Filter */
#घोषणा	FM_BIST_DONE	0x0100		/* BIST complete */
#घोषणा	FM_EMPTY	0x0200		/* CAM empty */
#घोषणा	FM_ERROR	0x0400		/* Error (improper operation) */
#घोषणा	FM_MULT		0x0800		/* Multiple Match */
#घोषणा	FM_EXACT	0x1000		/* Exact Match */
#घोषणा	FM_FOUND	0x2000		/* Compaअक्रम found in CAM */
#घोषणा	FM_FULL		0x4000		/* CAM full */
#घोषणा	FM_DONE		0x8000		/* DONE indicator */

/*
 * Supernet 3:
 * BIST Signature Register (AFBIST)
 */
#घोषणा	AF_BIST_SIGNAT	0x0553		/* Address Filter BIST Signature */

/*
 * Supernet 3:
 * Personality Register (AFPERS)
 */
#घोषणा	FM_VALID	0x0001		/* CAM Entry Valid */
#घोषणा	FM_DA		0x0002		/* Destination Address */
#घोषणा	FM_DAX		0x0004		/* Destination Address Exact */
#घोषणा	FM_SA		0x0008		/* Source Address */
#घोषणा	FM_SAX		0x0010		/* Source Address Exact */
#घोषणा	FM_SKIP		0x0020		/* Skip this entry */

/*
 * inकाष्ठाion set क्रम command रेजिस्टर 1 (NPADDR6-0 = 0x00)
 */
#घोषणा FM_IRESET	0x01		/* software reset */
#घोषणा FM_IRMEMWI	0x02		/* load Memory Data Reg., inc MARR */
#घोषणा FM_IRMEMWO	0x03		/* load MDR from buffer memory, n.i. */
#घोषणा FM_IIL		0x04		/* idle/listen */
#घोषणा FM_ICL		0x05		/* claim/listen */
#घोषणा FM_IBL		0x06		/* beacon/listen */
#घोषणा FM_ILTVX	0x07		/* load TVX समयr from TVX reg */
#घोषणा FM_INRTM	0x08		/* nonrestricted token mode */
#घोषणा FM_IENTM	0x09		/* enter nonrestricted token mode */
#घोषणा FM_IERTM	0x0a		/* enter restricted token mode */
#घोषणा FM_IRTM		0x0b		/* restricted token mode */
#घोषणा FM_ISURT	0x0c		/* send unrestricted token */
#घोषणा FM_ISRT		0x0d		/* send restricted token */
#घोषणा FM_ISIM		0x0e		/* enter send-immediate mode */
#घोषणा FM_IESIM	0x0f		/* निकास send-immediate mode */
#घोषणा FM_ICLLS	0x11		/* clear synchronous queue lock */
#घोषणा FM_ICLLA0	0x12		/* clear asynchronous queue 0 lock */
#घोषणा FM_ICLLA1	0x14		/* clear asynchronous queue 1 lock */
#घोषणा FM_ICLLA2	0x18		/* clear asynchronous queue 2 lock */
					/* SN3: reserved */
#घोषणा FM_ICLLR	0x20		/* clear receive queue (SN3:1) lock */
#घोषणा FM_ICLLR2	0x21		/* SN3: clear receive queue 2 lock */
#घोषणा FM_ITRXBUS	0x22		/* SN3: Tristate X-Bus (SAS only) */
#घोषणा FM_IDRXBUS	0x23		/* SN3: drive X-Bus */
#घोषणा FM_ICLLAL	0x3f		/* clear all queue locks */

/*
 * inकाष्ठाion set क्रम command रेजिस्टर 2 (NPADDR6-0 = 0x01)
 */
#घोषणा FM_ITRS		0x01		/* transmit synchronous queue */
					/* SN3: reserved */
#घोषणा FM_ITRA0	0x02		/* transmit asynchronous queue 0 */
					/* SN3: reserved */
#घोषणा FM_ITRA1	0x04		/* transmit asynchronous queue 1 */
					/* SN3: reserved */
#घोषणा FM_ITRA2	0x08		/* transmit asynchronous queue 2 */
					/* SN3: reserved */
#घोषणा FM_IACTR	0x10		/* पात current transmit activity */
#घोषणा FM_IRSTQ	0x20		/* reset transmit queues */
#घोषणा FM_ISTTB	0x30		/* set tag bit */
#घोषणा FM_IERSF	0x40		/* enable receive single frame */
					/* SN3: reserved */
#घोषणा	FM_ITR		0x50		/* SN3: Transmit Command */


/*
 *	defines क्रम PLC (Am79C864)
 */

/*
 *  PLC पढ़ो/ग_लिखो (r/w) रेजिस्टरs
 */
#घोषणा PL_CNTRL_A	0x00		/* control रेजिस्टर A (r/w) */
#घोषणा PL_CNTRL_B	0x01		/* control रेजिस्टर B (r/w) */
#घोषणा PL_INTR_MASK	0x02		/* पूर्णांकerrupt mask (r/w) */
#घोषणा PL_XMIT_VECTOR	0x03		/* transmit vector रेजिस्टर (r/w) */
#घोषणा PL_VECTOR_LEN	0x04		/* transmit vector length (r/w) */
#घोषणा PL_LE_THRESHOLD	0x05		/* link error event threshold (r/w) */
#घोषणा PL_C_MIN	0x06		/* minimum connect state समय (r/w) */
#घोषणा PL_TL_MIN	0x07		/* min. line state transmit t. (r/w) */
#घोषणा PL_TB_MIN	0x08		/* minimum अवरोध समय (r/w) */
#घोषणा PL_T_OUT	0x09		/* संकेत समयout (r/w) */
#घोषणा PL_CNTRL_C	0x0a		/* control रेजिस्टर C (r/w) */
#घोषणा PL_LC_LENGTH	0x0b		/* link confidence test समय (r/w) */
#घोषणा PL_T_SCRUB	0x0c		/* scrub समय = MAC TVX (r/w) */
#घोषणा PL_NS_MAX	0x0d		/* max. noise समय beक्रमe अवरोध (r/w)*/
#घोषणा PL_TPC_LOAD_V	0x0e		/* TPC समयr load value (ग_लिखो only) */
#घोषणा PL_TNE_LOAD_V	0x0f		/* TNE समयr load value (ग_लिखो only) */
#घोषणा PL_STATUS_A	0x10		/* status रेजिस्टर A (पढ़ो only) */
#घोषणा PL_STATUS_B	0x11		/* status रेजिस्टर B (पढ़ो only) */
#घोषणा PL_TPC		0x12		/* समयr क्रम PCM (ro) [20.48 us] */
#घोषणा PL_TNE		0x13		/* समय of noise event [0.32 us] */
#घोषणा PL_CLK_DIV	0x14		/* TNE घड़ी भागider (पढ़ो only) */
#घोषणा PL_BIST_SIGNAT	0x15		/* built in self test signature (ro)*/
#घोषणा PL_RCV_VECTOR	0x16		/* receive vector reg. (पढ़ो only) */
#घोषणा PL_INTR_EVENT	0x17		/* पूर्णांकerrupt event reg. (पढ़ो only) */
#घोषणा PL_VIOL_SYM_CTR	0x18		/* violation symbol count. (पढ़ो o) */
#घोषणा PL_MIN_IDLE_CTR	0x19		/* minimum idle counter (पढ़ो only) */
#घोषणा PL_LINK_ERR_CTR	0x1a		/* link error event ctr.(पढ़ो only) */
#अगर_घोषित	MOT_ELM
#घोषणा	PL_T_FOT_ASS	0x1e		/* FOTOFF Assert Timer */
#घोषणा	PL_T_FOT_DEASS	0x1f		/* FOTOFF Deनिश्चित Timer */
#पूर्ण_अगर	/* MOT_ELM */

#अगर_घोषित	MOT_ELM
/*
 * Special Quad-Elm Registers.
 * A Quad-ELM consists of क्रम ELMs and these additional रेजिस्टरs.
 */
#घोषणा	QELM_XBAR_W	0x80		/* Crossbar Control ELM W */
#घोषणा	QELM_XBAR_X	0x81		/* Crossbar Control ELM X */
#घोषणा	QELM_XBAR_Y	0x82		/* Crossbar Control ELM Y */
#घोषणा	QELM_XBAR_Z	0x83		/* Crossbar Control ELM Z */
#घोषणा	QELM_XBAR_P	0x84		/* Crossbar Control Bus P */
#घोषणा	QELM_XBAR_S	0x85		/* Crossbar Control Bus S */
#घोषणा	QELM_XBAR_R	0x86		/* Crossbar Control Bus R */
#घोषणा	QELM_WR_XBAR	0x87		/* Write the Crossbar now (ग_लिखो) */
#घोषणा	QELM_CTR_W	0x88		/* Counter W */
#घोषणा	QELM_CTR_X	0x89		/* Counter X */
#घोषणा	QELM_CTR_Y	0x8a		/* Counter Y */
#घोषणा	QELM_CTR_Z	0x8b		/* Counter Z */
#घोषणा	QELM_INT_MASK	0x8c		/* Interrupt mask रेजिस्टर */
#घोषणा	QELM_INT_DATA	0x8d		/* Interrupt data (event) रेजिस्टर */
#घोषणा	QELM_ELMB	0x00		/* Elm base */
#घोषणा	QELM_ELM_SIZE	0x20		/* ELM size */
#पूर्ण_अगर	/* MOT_ELM */
/*
 * PLC control रेजिस्टर A (PL_CNTRL_A: log. addr. 0x00)
 * It is used क्रम समयr configuration, specअगरication of PCM MAINT state option,
 * counter पूर्णांकerrupt frequency, PLC data path config. and Built In Self Test.
 */
#घोषणा	PL_RUN_BIST	0x0001		/* begin running its Built In Self T.*/
#घोषणा	PL_RF_DISABLE	0x0002		/* disable the Repeat Filter state m.*/
#घोषणा	PL_SC_REM_LOOP	0x0004		/* remote loopback path */
#घोषणा	PL_SC_BYPASS	0x0008		/* by providing a physical bypass */
#घोषणा	PL_LM_LOC_LOOP	0x0010		/* loop path just after elastic buff.*/
#घोषणा	PL_EB_LOC_LOOP	0x0020		/* loop path just prior to PDT/PDR IF*/
#घोषणा	PL_FOT_OFF	0x0040		/* निश्चितion of /FOTOFF pin of PLC */
#घोषणा	PL_LOOPBACK	0x0080		/* it cause the /LPBCK pin ass. low */
#घोषणा	PL_MINI_CTR_INT 0x0100		/* partially contr. when bit is ass. */
#घोषणा	PL_VSYM_CTR_INT	0x0200		/* controls when पूर्णांक bit is निश्चितed */
#घोषणा	PL_ENA_PAR_CHK	0x0400		/* enable parity check */
#घोषणा	PL_REQ_SCRUB	0x0800		/* limited access to scrub capability*/
#घोषणा	PL_TPC_16BIT	0x1000		/* causes the TPC as a 16 bit समयr */
#घोषणा	PL_TNE_16BIT	0x2000		/* causes the TNE as a 16 bit समयr */
#घोषणा	PL_NOISE_TIMER	0x4000		/* allows the noise timing function */

/*
 * PLC control रेजिस्टर B (PL_CNTRL_B: log. addr. 0x01)
 * It contains संकेतs and requeste to direct the process of PCM and it is also
 * used to control the Line State Match पूर्णांकerrupt.
 */
#घोषणा	PL_PCM_CNTRL	0x0003		/* control PCM state machine */
#घोषणा	PL_PCM_NAF	(0)		/* state is not affected */
#घोषणा	PL_PCM_START	(1)		/* goes to the BREAK state */
#घोषणा	PL_PCM_TRACE	(2)		/* goes to the TRACE state */
#घोषणा	PL_PCM_STOP	(3)		/* goes to the OFF state */

#घोषणा	PL_MAINT	0x0004		/* अगर OFF state --> MAINT state */
#घोषणा	PL_LONG		0x0008		/* perf. a दीर्घ Link Confid.Test(LCT)*/
#घोषणा	PL_PC_JOIN	0x0010		/* अगर NEXT state --> JOIN state */

#घोषणा	PL_PC_LOOP	0x0060		/* loopback used in the LCT */
#घोषणा	PL_NOLCT	(0<<5)		/* no LCT is perक्रमmed */
#घोषणा	PL_TPDR		(1<<5)		/* PCM निश्चितs transmit PDR */
#घोषणा	PL_TIDLE	(2<<5)		/* PCM निश्चितs transmit idle */
#घोषणा	PL_RLBP		(3<<5)		/* trans. PDR & remote loopb. path */

#घोषणा	PL_CLASS_S	0x0080		/* signअगर. that single att. station */

#घोषणा	PL_MAINT_LS	0x0700		/* line state जबतक in the MAINT st. */
#घोषणा	PL_M_QUI0	(0<<8)		/* transmit QUIET line state */
#घोषणा	PL_M_IDLE	(1<<8)		/* transmit IDLE line state */
#घोषणा	PL_M_HALT	(2<<8)		/* transmit HALT line state */
#घोषणा	PL_M_MASTR	(3<<8)		/* transmit MASTER line state */
#घोषणा	PL_M_QUI1	(4<<8)		/* transmit QUIET line state */
#घोषणा	PL_M_QUI2	(5<<8)		/* transmit QUIET line state */
#घोषणा	PL_M_TPDR	(6<<8)		/* tr. PHY_DATA requ.-symbol is tr.ed*/
#घोषणा	PL_M_QUI3	(7<<8)		/* transmit QUIET line state */

#घोषणा	PL_MATCH_LS	0x7800		/* line state to be comp. with curr.*/
#घोषणा	PL_I_ANY	(0<<11)		/* Int. on any change in *_LINE_ST */
#घोषणा	PL_I_IDLE	(1<<11)		/* Interrupt on IDLE line state */
#घोषणा	PL_I_HALT	(2<<11)		/* Interrupt on HALT line state */
#घोषणा	PL_I_MASTR	(4<<11)		/* Interrupt on MASTER line state */
#घोषणा	PL_I_QUIET	(8<<11)		/* Interrupt on QUIET line state */

#घोषणा	PL_CONFIG_CNTRL	0x8000		/* control over scrub, byp. & loopb.*/

/*
 * PLC control रेजिस्टर C (PL_CNTRL_C: log. addr. 0x0a)
 * It contains the scrambling control रेजिस्टरs (PLC-S only)
 */
#घोषणा PL_C_CIPHER_ENABLE	(1<<0)	/* enable scrambler */
#घोषणा PL_C_CIPHER_LPBCK	(1<<1)	/* loopback scrambler */
#घोषणा PL_C_SDOFF_ENABLE	(1<<6)	/* enable SDOFF समयr */
#घोषणा PL_C_SDON_ENABLE	(1<<7)	/* enable SDON समयr */
#अगर_घोषित	MOT_ELM
#घोषणा PL_C_FOTOFF_CTRL	(3<<2)	/* FOTOFF समयr control */
#घोषणा PL_C_FOTOFF_TIM		(0<<2)	/* FOTOFF use समयr क्रम (de)-निश्चित */
#घोषणा PL_C_FOTOFF_INA		(2<<2)	/* FOTOFF क्रमced inactive */
#घोषणा PL_C_FOTOFF_ACT		(3<<2)	/* FOTOFF क्रमced active */
#घोषणा PL_C_FOTOFF_SRCE	(1<<4)	/* FOTOFF source is PCM state != OFF */
#घोषणा	PL_C_RXDATA_EN		(1<<5)	/* Rec scr data क्रमced to 0 */
#घोषणा	PL_C_SDNRZEN		(1<<8)	/* Monitor rec descr. data क्रम act */
#अन्यथा	/* nMOT_ELM */
#घोषणा PL_C_FOTOFF_CTRL	(3<<8)	/* FOTOFF समयr control */
#घोषणा PL_C_FOTOFF_0		(0<<8)	/* समयr off */
#घोषणा PL_C_FOTOFF_30		(1<<8)	/* 30uS */
#घोषणा PL_C_FOTOFF_50		(2<<8)	/* 50uS */
#घोषणा PL_C_FOTOFF_NEVER	(3<<8)	/* never */
#घोषणा PL_C_SDON_TIMER		(3<<10)	/* SDON समयr control */
#घोषणा PL_C_SDON_084		(0<<10)	/* 0.84 uS */
#घोषणा PL_C_SDON_132		(1<<10)	/* 1.32 uS */
#घोषणा PL_C_SDON_252		(2<<10)	/* 2.52 uS */
#घोषणा PL_C_SDON_512		(3<<10)	/* 5.12 uS */
#घोषणा PL_C_SOFF_TIMER		(3<<12)	/* SDOFF समयr control */
#घोषणा PL_C_SOFF_076		(0<<12)	/* 0.76 uS */
#घोषणा PL_C_SOFF_132		(1<<12)	/* 1.32 uS */
#घोषणा PL_C_SOFF_252		(2<<12)	/* 2.52 uS */
#घोषणा PL_C_SOFF_512		(3<<12)	/* 5.12 uS */
#घोषणा PL_C_TSEL		(3<<14)	/* scrambler path select */
#पूर्ण_अगर	/* nMOT_ELM */

/*
 * PLC status रेजिस्टर A (PL_STATUS_A: log. addr. 0x10)
 * It is used to report status inक्रमmation to the Node Processor about the 
 * Line State Machine (LSM).
 */
#अगर_घोषित	MOT_ELM
#घोषणा PLC_INT_MASK	0xc000		/* ELM पूर्णांकegration bits in status A */
#घोषणा PLC_INT_C	0x0000		/* ELM Revision Band C */
#घोषणा PLC_INT_CAMEL	0x4000		/* ELM पूर्णांकegrated पूर्णांकo CAMEL */
#घोषणा PLC_INT_QE	0x8000		/* ELM पूर्णांकegrated पूर्णांकo Quad ELM */
#घोषणा PLC_REV_MASK	0x3800		/* revision bits in status A */
#घोषणा PLC_REVISION_B	0x0000		/* rev bits क्रम ELM Rev B */
#घोषणा PLC_REVISION_QA	0x0800		/* rev bits क्रम ELM core in QELM-A */
#अन्यथा	/* nMOT_ELM */
#घोषणा PLC_REV_MASK	0xf800		/* revision bits in status A */
#घोषणा PLC_REVISION_A	0x0000		/* revision bits क्रम PLC */
#घोषणा PLC_REVISION_S	0xf800		/* revision bits क्रम PLC-S */
#घोषणा PLC_REV_SN3	0x7800		/* revision bits क्रम PLC-S in IFCP */
#पूर्ण_अगर	/* nMOT_ELM */
#घोषणा	PL_SYM_PR_CTR	0x0007		/* contains the LSM symbol pair Ctr. */
#घोषणा	PL_UNKN_LINE_ST	0x0008		/* unknown line state bit from LSM */
#घोषणा	PL_LSM_STATE	0x0010		/* state bit of LSM */

#घोषणा	PL_LINE_ST	0x00e0		/* contains recogn. line state of LSM*/
#घोषणा	PL_L_NLS	(0<<5)		/* noise line state */
#घोषणा	PL_L_ALS	(1<<5)		/* activ line state */
#घोषणा	PL_L_UND	(2<<5)		/* undefined */
#घोषणा	PL_L_ILS4	(3<<5)		/* idle l. s. (after 4 idle symbols) */
#घोषणा	PL_L_QLS	(4<<5)		/* quiet line state */
#घोषणा	PL_L_MLS	(5<<5)		/* master line state */
#घोषणा	PL_L_HLS	(6<<5)		/* halt line state */
#घोषणा	PL_L_ILS16	(7<<5)		/* idle line state (after 16 idle s.)*/

#घोषणा	PL_PREV_LINE_ST	0x0300		/* value of previous line state */
#घोषणा	PL_P_QLS	(0<<8)		/* quiet line state */
#घोषणा	PL_P_MLS	(1<<8)		/* master line state */
#घोषणा	PL_P_HLS	(2<<8)		/* halt line state */
#घोषणा	PL_P_ILS16	(3<<8)		/* idle line state (after 16 idle s.)*/

#घोषणा	PL_SIGNAL_DET	0x0400		/* 1=that संकेत detect is deनिश्चितed*/


/*
 * PLC status रेजिस्टर B (PL_STATUS_B: log. addr. 0x11)
 * It contains संकेतs and status from the repeat filter and PCM state machine.
 */
#घोषणा	PL_BREAK_REASON	0x0007		/* reason क्रम PCM state mach.s to br.*/
#घोषणा	PL_B_NOT	(0)		/* PCM SM has not gone to BREAK state*/
#घोषणा	PL_B_PCS	(1)		/* PC_Start issued */
#घोषणा	PL_B_TPC	(2)		/* TPC समयr expired after T_OUT */
#घोषणा	PL_B_TNE	(3)		/* TNE समयr expired after NS_MAX */
#घोषणा	PL_B_QLS	(4)		/* quit line state detected */
#घोषणा	PL_B_ILS	(5)		/* idle line state detected */
#घोषणा	PL_B_HLS	(6)		/* halt line state detected */

#घोषणा	PL_TCF		0x0008		/* transmit code flag (start exec.) */
#घोषणा	PL_RCF		0x0010		/* receive code flag (start exec.) */
#घोषणा	PL_LSF		0x0020		/* line state flag (l.s. has been r.)*/
#घोषणा	PL_PCM_SIGNAL	0x0040		/* indic. that XMIT_VECTOR hb.written*/

#घोषणा	PL_PCM_STATE	0x0780		/* state bits of PCM state machine */
#घोषणा	PL_PC0		(0<<7)		/* OFF	   - when /RST or PCM_CNTRL */
#घोषणा	PL_PC1		(1<<7)		/* BREAK   - entry poपूर्णांक in start PCM*/
#घोषणा	PL_PC2		(2<<7)		/* TRACE   - to localize stuck Beacon*/
#घोषणा	PL_PC3		(3<<7)		/* CONNECT - synchronize ends of conn*/
#घोषणा	PL_PC4		(4<<7)		/* NEXT	   - to separate the संकेतng*/
#घोषणा	PL_PC5		(5<<7)		/* SIGNAL  - PCM trans/rec. bit infos*/
#घोषणा	PL_PC6		(6<<7)		/* JOIN	   - 1. state to activ conn. */
#घोषणा	PL_PC7		(7<<7)		/* VERIFY  - 2. - " - (3. ACTIVE) */
#घोषणा	PL_PC8		(8<<7)		/* ACTIVE  - PHY has been incorporated*/
#घोषणा	PL_PC9		(9<<7)		/* MAINT   - क्रम test purposes or so 
					   that PCM op. completely in softw. */

#घोषणा	PL_PCI_SCRUB	0x0800		/* scrubbing function is being exec. */

#घोषणा	PL_PCI_STATE	0x3000		/* Physical Connect. Insertion SM */
#घोषणा	PL_CI_REMV	(0<<12)		/* REMOVED */
#घोषणा	PL_CI_ISCR	(1<<12)		/* INSERT_SCRUB */
#घोषणा	PL_CI_RSCR	(2<<12)		/* REMOVE_SCRUB */
#घोषणा	PL_CI_INS	(3<<12)		/* INSERTED */

#घोषणा	PL_RF_STATE	0xc000		/* state bit of repeate filter SM */
#घोषणा	PL_RF_REPT	(0<<14)		/* REPEAT */
#घोषणा	PL_RF_IDLE	(1<<14)		/* IDLE */
#घोषणा	PL_RF_HALT1	(2<<14)		/* HALT1 */
#घोषणा	PL_RF_HALT2	(3<<14)		/* HALT2 */


/*
 * PLC पूर्णांकerrupt event रेजिस्टर (PL_INTR_EVENT: log. addr. 0x17)
 * It is पढ़ो only and is clearde whenever it is पढ़ो!
 * It is used by the PLC to report events to the node processor.
 */
#घोषणा	PL_PARITY_ERR	0x0001		/* p. error h.b.detected on TX9-0 inp*/
#घोषणा	PL_LS_MATCH	0x0002		/* l.s.== l.s. PLC_CNTRL_B's MATCH_LS*/
#घोषणा	PL_PCM_CODE	0x0004		/* transmit&receive | LCT complete */
#घोषणा	PL_TRACE_PROP	0x0008		/* master l.s. जबतक PCM ACTIV|TRACE */
#घोषणा	PL_SELF_TEST	0x0010		/* QUIET|HALT जबतक PCM in TRACE st. */
#घोषणा	PL_PCM_BREAK	0x0020		/* PCM has entered the BREAK state */
#घोषणा	PL_PCM_ENABLED	0x0040		/* निश्चितed SC_JOIN, scrub. & ACTIV */
#घोषणा	PL_TPC_EXPIRED	0x0080		/* TPC समयr reached zero */
#घोषणा	PL_TNE_EXPIRED	0x0100		/* TNE समयr reached zero */
#घोषणा	PL_EBUF_ERR	0x0200		/* elastic buff. det. over-|underflow*/
#घोषणा	PL_PHYINV	0x0400		/* physical layer invalid संकेत */
#घोषणा	PL_VSYM_CTR	0x0800		/* violation symbol counter has incr.*/
#घोषणा	PL_MINI_CTR	0x1000		/* dep. on PLC_CNTRL_A's MINI_CTR_INT*/
#घोषणा	PL_LE_CTR	0x2000		/* link error event counter */
#घोषणा	PL_LSDO		0x4000		/* SDO input pin changed to a 1 */
#घोषणा	PL_NP_ERR	0x8000		/* NP has requested to r/w an inv. r.*/

/*
 * The PLC पूर्णांकerrupt mask रेजिस्टर (PL_INTR_MASK: log. addr. 0x02) स्थिरr. is
 * equal PL_INTR_EVENT रेजिस्टर.
 * For each set bit, the setting of corresponding bit generate an पूर्णांक to NP. 
 */

#अगर_घोषित	MOT_ELM
/*
 * Quad ELM Crosbar Control रेजिस्टर values (QELM_XBAR_?)
 */
#घोषणा	QELM_XOUT_IDLE	0x0000		/* Idles/Passthrough */
#घोषणा	QELM_XOUT_P	0x0001		/* Output to: Bus P */
#घोषणा	QELM_XOUT_S	0x0002		/* Output to: Bus S */
#घोषणा	QELM_XOUT_R	0x0003		/* Output to: Bus R */
#घोषणा	QELM_XOUT_W	0x0004		/* Output to: ELM W */
#घोषणा	QELM_XOUT_X	0x0005		/* Output to: ELM X */
#घोषणा	QELM_XOUT_Y	0x0006		/* Output to: ELM Y */
#घोषणा	QELM_XOUT_Z	0x0007		/* Output to: ELM Z */

/*
 * Quad ELM Interrupt data and event रेजिस्टरs.
 */
#घोषणा	QELM_NP_ERR	(1<<15)		/* Node Processor Error */
#घोषणा	QELM_COUNT_Z	(1<<7)		/* Counter Z Interrupt */
#घोषणा	QELM_COUNT_Y	(1<<6)		/* Counter Y Interrupt */
#घोषणा	QELM_COUNT_X	(1<<5)		/* Counter X Interrupt */
#घोषणा	QELM_COUNT_W	(1<<4)		/* Counter W Interrupt */
#घोषणा	QELM_ELM_Z	(1<<3)		/* ELM Z Interrupt */
#घोषणा	QELM_ELM_Y	(1<<2)		/* ELM Y Interrupt */
#घोषणा	QELM_ELM_X	(1<<1)		/* ELM X Interrupt */
#घोषणा	QELM_ELM_W	(1<<0)		/* ELM W Interrupt */
#पूर्ण_अगर	/* MOT_ELM */
/*
 * PLC Timing Parameters
 */
#घोषणा	TP_C_MIN	0xff9c	/*   2    ms */
#घोषणा	TP_TL_MIN	0xfff0	/*   0.3  ms */
#घोषणा	TP_TB_MIN	0xff10	/*   5    ms */
#घोषणा	TP_T_OUT	0xd9db	/* 200    ms */
#घोषणा	TP_LC_LENGTH	0xf676	/*  50    ms */
#घोषणा	TP_LC_LONGLN	0xa0a2	/* 500    ms */
#घोषणा	TP_T_SCRUB	0xff6d	/*   3.5  ms */
#घोषणा	TP_NS_MAX	0xf021	/*   1.3   ms */

/*
 * BIST values
 */
#घोषणा PLC_BIST	0x6ecd		/* BIST signature क्रम PLC */
#घोषणा PLCS_BIST	0x5b6b 		/* BIST signature क्रम PLC-S */
#घोषणा	PLC_ELM_B_BIST	0x6ecd		/* BIST signature of ELM Rev. B */
#घोषणा	PLC_ELM_D_BIST	0x5b6b		/* BIST signature of ELM Rev. D */
#घोषणा	PLC_CAM_A_BIST	0x9e75		/* BIST signature of CAMEL Rev. A */
#घोषणा	PLC_CAM_B_BIST	0x5b6b		/* BIST signature of CAMEL Rev. B */
#घोषणा	PLC_IFD_A_BIST	0x9e75		/* BIST signature of IFDDI Rev. A */
#घोषणा	PLC_IFD_B_BIST	0x5b6b		/* BIST signature of IFDDI Rev. B */
#घोषणा	PLC_QELM_A_BIST	0x5b6b		/* BIST signature of QELM Rev. A */

/*
 	FDDI board recources	
 */

/*
 * request रेजिस्टर array (log. addr: RQA_A + a<<1 अणुa=0..7पूर्ण) ग_लिखो only.
 * It specअगरies to FORMAC+ the type of buffer memory access the host requires.
 */
#घोषणा	RQ_NOT		0		/* not request */
#घोषणा	RQ_RES		1		/* reserved */
#घोषणा	RQ_SFW		2		/* special frame ग_लिखो */
#घोषणा	RQ_RRQ		3		/* पढ़ो request: receive queue */
#घोषणा	RQ_WSQ		4		/* ग_लिखो request: synchronous queue */
#घोषणा	RQ_WA0		5		/* ग_लिखो requ.: asynchronous queue 0 */
#घोषणा	RQ_WA1		6		/* ग_लिखो requ.: asynchronous queue 1 */
#घोषणा	RQ_WA2		7		/* ग_लिखो requ.: asynchronous queue 2 */

#घोषणा	SZ_LONG		(माप(दीर्घ))

/*
 * FDDI शेषs
 * NOTE : In the ANSI करोcs, बार are specअगरied in units of "symbol time".
 * 	  AMD chips use BCLK as unit. 1 BCKL == 2 symbols
 */
#घोषणा	COMPLREF	((u_दीर्घ)32*256*256)	/* two's complement 21 bit */
#घोषणा MSTOBCLK(x)	((u_दीर्घ)(x)*12500L)
#घोषणा MSTOTVX(x)	(((u_दीर्घ)(x)*1000L)/80/255)

#पूर्ण_अगर	/* _SUPERNET_ */
