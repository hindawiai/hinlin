<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *
 * Author	Karsten Keil <kkeil@novell.com>
 *
 *   Basic declarations क्रम the mISDN HW channels
 *
 * Copyright 2008  by Karsten Keil <kkeil@novell.com>
 */

#अगर_अघोषित MISDNHW_H
#घोषणा MISDNHW_H
#समावेश <linux/mISDNअगर.h>
#समावेश <linux/समयr.h>

/*
 * HW DEBUG 0xHHHHGGGG
 * H - hardware driver specअगरic bits
 * G - क्रम all drivers
 */

#घोषणा DEBUG_HW		0x00000001
#घोषणा DEBUG_HW_OPEN		0x00000002
#घोषणा DEBUG_HW_DCHANNEL	0x00000100
#घोषणा DEBUG_HW_DFIFO		0x00000200
#घोषणा DEBUG_HW_BCHANNEL	0x00001000
#घोषणा DEBUG_HW_BFIFO		0x00002000

#घोषणा MAX_DFRAME_LEN_L1	300
#घोषणा MAX_MON_FRAME		32
#घोषणा MAX_LOG_SPACE		2048
#घोषणा MISDN_COPY_SIZE		32

/* channel->Flags bit field */
#घोषणा FLG_TX_BUSY		0	/* tx_buf in use */
#घोषणा FLG_TX_NEXT		1	/* next_skb in use */
#घोषणा FLG_L1_BUSY		2	/* L1 is permanent busy */
#घोषणा FLG_L2_ACTIVATED	3	/* activated from L2 */
#घोषणा FLG_OPEN		5	/* channel is in use */
#घोषणा FLG_ACTIVE		6	/* channel is activated */
#घोषणा FLG_BUSY_TIMER		7
/* channel type */
#घोषणा FLG_DCHANNEL		8	/* channel is D-channel */
#घोषणा FLG_BCHANNEL		9	/* channel is B-channel */
#घोषणा FLG_ECHANNEL		10	/* channel is E-channel */
#घोषणा FLG_TRANSPARENT		12	/* channel use transparent data */
#घोषणा FLG_HDLC		13	/* channel use hdlc data */
#घोषणा FLG_L2DATA		14	/* channel use L2 DATA primitivs */
#घोषणा FLG_ORIGIN		15	/* channel is on origin site */
/* channel specअगरic stuff */
#घोषणा FLG_FILLEMPTY		16	/* fill fअगरo on first frame (empty) */
/* arcofi specअगरic */
#घोषणा FLG_ARCOFI_TIMER	17
#घोषणा FLG_ARCOFI_ERROR	18
/* isar specअगरic */
#घोषणा FLG_INITIALIZED		17
#घोषणा FLG_DLEETX		18
#घोषणा FLG_LASTDLE		19
#घोषणा FLG_FIRST		20
#घोषणा FLG_LASTDATA		21
#घोषणा FLG_NMD_DATA		22
#घोषणा FLG_FTI_RUN		23
#घोषणा FLG_LL_OK		24
#घोषणा FLG_LL_CONN		25
#घोषणा FLG_DTMFSEND		26
#घोषणा FLG_TX_EMPTY		27
/* stop sending received data upstream */
#घोषणा FLG_RX_OFF		28
/* workq events */
#घोषणा FLG_RECVQUEUE		30
#घोषणा	FLG_PHCHANGE		31

#घोषणा schedule_event(s, ev)	करो अणु \
					test_and_set_bit(ev, &((s)->Flags)); \
					schedule_work(&((s)->workq)); \
				पूर्ण जबतक (0)

काष्ठा dchannel अणु
	काष्ठा mISDNdevice	dev;
	u_दीर्घ			Flags;
	काष्ठा work_काष्ठा	workq;
	व्योम			(*phfunc) (काष्ठा dchannel *);
	u_पूर्णांक			state;
	व्योम			*l1;
	व्योम			*hw;
	पूर्णांक			slot;	/* multiport card channel slot */
	काष्ठा समयr_list	समयr;
	/* receive data */
	काष्ठा sk_buff		*rx_skb;
	पूर्णांक			maxlen;
	/* send data */
	काष्ठा sk_buff_head	squeue;
	काष्ठा sk_buff_head	rqueue;
	काष्ठा sk_buff		*tx_skb;
	पूर्णांक			tx_idx;
	पूर्णांक			debug;
	/* statistics */
	पूर्णांक			err_crc;
	पूर्णांक			err_tx;
	पूर्णांक			err_rx;
पूर्ण;

प्रकार पूर्णांक	(dchannel_l1callback)(काष्ठा dchannel *, u_पूर्णांक);
बाह्य पूर्णांक	create_l1(काष्ठा dchannel *, dchannel_l1callback *);

/* निजी L1 commands */
#घोषणा INFO0		0x8002
#घोषणा INFO1		0x8102
#घोषणा INFO2		0x8202
#घोषणा INFO3_P8	0x8302
#घोषणा INFO3_P10	0x8402
#घोषणा INFO4_P8	0x8502
#घोषणा INFO4_P10	0x8602
#घोषणा LOSTFRAMING	0x8702
#घोषणा ANYSIGNAL	0x8802
#घोषणा HW_POWERDOWN	0x8902
#घोषणा HW_RESET_REQ	0x8a02
#घोषणा HW_POWERUP_REQ	0x8b02
#घोषणा HW_DEACT_REQ	0x8c02
#घोषणा HW_ACTIVATE_REQ	0x8e02
#घोषणा HW_D_NOBLOCKED  0x8f02
#घोषणा HW_RESET_IND	0x9002
#घोषणा HW_POWERUP_IND	0x9102
#घोषणा HW_DEACT_IND	0x9202
#घोषणा HW_ACTIVATE_IND	0x9302
#घोषणा HW_DEACT_CNF	0x9402
#घोषणा HW_TESTLOOP	0x9502
#घोषणा HW_TESTRX_RAW	0x9602
#घोषणा HW_TESTRX_HDLC	0x9702
#घोषणा HW_TESTRX_OFF	0x9802
#घोषणा HW_TIMER3_IND	0x9902
#घोषणा HW_TIMER3_VALUE	0x9a00
#घोषणा HW_TIMER3_VMASK	0x00FF

काष्ठा layer1;
बाह्य पूर्णांक	l1_event(काष्ठा layer1 *, u_पूर्णांक);

#घोषणा MISDN_BCH_FILL_SIZE	4

काष्ठा bchannel अणु
	काष्ठा mISDNchannel	ch;
	पूर्णांक			nr;
	u_दीर्घ			Flags;
	काष्ठा work_काष्ठा	workq;
	u_पूर्णांक			state;
	व्योम			*hw;
	पूर्णांक			slot;	/* multiport card channel slot */
	काष्ठा समयr_list	समयr;
	/* receive data */
	u8			fill[MISDN_BCH_FILL_SIZE];
	काष्ठा sk_buff		*rx_skb;
	अचिन्हित लघु		maxlen;
	अचिन्हित लघु		init_maxlen; /* initial value */
	अचिन्हित लघु		next_maxlen; /* pending value */
	अचिन्हित लघु		minlen; /* क्रम transparent data */
	अचिन्हित लघु		init_minlen; /* initial value */
	अचिन्हित लघु		next_minlen; /* pending value */
	/* send data */
	काष्ठा sk_buff		*next_skb;
	काष्ठा sk_buff		*tx_skb;
	काष्ठा sk_buff_head	rqueue;
	पूर्णांक			rcount;
	पूर्णांक			tx_idx;
	पूर्णांक			debug;
	/* statistics */
	पूर्णांक			err_crc;
	पूर्णांक			err_tx;
	पूर्णांक			err_rx;
	पूर्णांक			dropcnt;
पूर्ण;

बाह्य पूर्णांक	mISDN_initdchannel(काष्ठा dchannel *, पूर्णांक, व्योम *);
बाह्य पूर्णांक	mISDN_initbchannel(काष्ठा bchannel *, अचिन्हित लघु,
				   अचिन्हित लघु);
बाह्य पूर्णांक	mISDN_मुक्तdchannel(काष्ठा dchannel *);
बाह्य व्योम	mISDN_clear_bchannel(काष्ठा bchannel *);
बाह्य व्योम	mISDN_मुक्तbchannel(काष्ठा bchannel *);
बाह्य पूर्णांक	mISDN_ctrl_bchannel(काष्ठा bchannel *, काष्ठा mISDN_ctrl_req *);
बाह्य व्योम	queue_ch_frame(काष्ठा mISDNchannel *, u_पूर्णांक,
			पूर्णांक, काष्ठा sk_buff *);
बाह्य पूर्णांक	dchannel_senddata(काष्ठा dchannel *, काष्ठा sk_buff *);
बाह्य पूर्णांक	bchannel_senddata(काष्ठा bchannel *, काष्ठा sk_buff *);
बाह्य पूर्णांक      bchannel_get_rxbuf(काष्ठा bchannel *, पूर्णांक);
बाह्य व्योम	recv_Dchannel(काष्ठा dchannel *);
बाह्य व्योम	recv_Echannel(काष्ठा dchannel *, काष्ठा dchannel *);
बाह्य व्योम	recv_Bchannel(काष्ठा bchannel *, अचिन्हित पूर्णांक, bool);
बाह्य व्योम	recv_Dchannel_skb(काष्ठा dchannel *, काष्ठा sk_buff *);
बाह्य व्योम	recv_Bchannel_skb(काष्ठा bchannel *, काष्ठा sk_buff *);
बाह्य पूर्णांक	get_next_bframe(काष्ठा bchannel *);
बाह्य पूर्णांक	get_next_dframe(काष्ठा dchannel *);

#पूर्ण_अगर
