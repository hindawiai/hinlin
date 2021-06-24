<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Layer 2 defines
 *
 * Copyright 2008  by Karsten Keil <kkeil@novell.com>
 */

#समावेश <linux/mISDNअगर.h>
#समावेश <linux/skbuff.h>
#समावेश "fsm.h"

#घोषणा MAX_WINDOW	8

काष्ठा manager अणु
	काष्ठा mISDNchannel	ch;
	काष्ठा mISDNchannel	bcast;
	u_दीर्घ			options;
	काष्ठा list_head	layer2;
	rwlock_t		lock;
	काष्ठा FsmInst		deact;
	काष्ठा FsmTimer		daसमयr;
	काष्ठा sk_buff_head	sendq;
	काष्ठा mISDNchannel	*up;
	u_पूर्णांक			nextid;
	u_पूर्णांक			lastid;
पूर्ण;

काष्ठा teimgr अणु
	पूर्णांक			ri;
	पूर्णांक			rcnt;
	काष्ठा FsmInst		tei_m;
	काष्ठा FsmTimer		समयr;
	पूर्णांक			tval, nval;
	काष्ठा layer2		*l2;
	काष्ठा manager		*mgr;
पूर्ण;

काष्ठा laddr अणु
	u_अक्षर	A;
	u_अक्षर	B;
पूर्ण;

काष्ठा layer2 अणु
	काष्ठा list_head	list;
	काष्ठा mISDNchannel	ch;
	u_दीर्घ			flag;
	पूर्णांक			id;
	काष्ठा mISDNchannel	*up;
	चिन्हित अक्षर		sapi;
	चिन्हित अक्षर		tei;
	काष्ठा laddr		addr;
	u_पूर्णांक			maxlen;
	काष्ठा teimgr		*पंचांग;
	u_पूर्णांक			vs, va, vr;
	पूर्णांक			rc;
	u_पूर्णांक			winकरोw;
	u_पूर्णांक			sow;
	काष्ठा FsmInst		l2m;
	काष्ठा FsmTimer		t200, t203;
	पूर्णांक			T200, N200, T203;
	u_पूर्णांक			next_id;
	u_पूर्णांक			करोwn_id;
	काष्ठा sk_buff		*winकरोwar[MAX_WINDOW];
	काष्ठा sk_buff_head	i_queue;
	काष्ठा sk_buff_head	ui_queue;
	काष्ठा sk_buff_head	करोwn_queue;
	काष्ठा sk_buff_head	पंचांगp_queue;
पूर्ण;

क्रमागत अणु
	ST_L2_1,
	ST_L2_2,
	ST_L2_3,
	ST_L2_4,
	ST_L2_5,
	ST_L2_6,
	ST_L2_7,
	ST_L2_8,
पूर्ण;

#घोषणा L2_STATE_COUNT (ST_L2_8 + 1)

बाह्य काष्ठा layer2	*create_l2(काष्ठा mISDNchannel *, u_पूर्णांक,
				   u_दीर्घ, पूर्णांक, पूर्णांक);
बाह्य पूर्णांक		tei_l2(काष्ठा layer2 *, u_पूर्णांक, u_दीर्घ arg);


/* from tei.c */
बाह्य पूर्णांक		l2_tei(काष्ठा layer2 *, u_पूर्णांक, u_दीर्घ arg);
बाह्य व्योम		TEIrelease(काष्ठा layer2 *);
बाह्य पूर्णांक		TEIInit(u_पूर्णांक *);
बाह्य व्योम		TEIFree(व्योम);

#घोषणा MAX_L2HEADER_LEN 4

#घोषणा RR	0x01
#घोषणा RNR	0x05
#घोषणा REJ	0x09
#घोषणा SABME	0x6f
#घोषणा SABM	0x2f
#घोषणा DM	0x0f
#घोषणा UI	0x03
#घोषणा DISC	0x43
#घोषणा UA	0x63
#घोषणा FRMR	0x87
#घोषणा XID	0xaf

#घोषणा CMD	0
#घोषणा RSP	1

#घोषणा LC_FLUSH_WAIT 1

#घोषणा FLG_LAPB	0
#घोषणा FLG_LAPD	1
#घोषणा FLG_ORIG	2
#घोषणा FLG_MOD128	3
#घोषणा FLG_PEND_REL	4
#घोषणा FLG_L3_INIT	5
#घोषणा FLG_T200_RUN	6
#घोषणा FLG_ACK_PEND	7
#घोषणा FLG_REJEXC	8
#घोषणा FLG_OWN_BUSY	9
#घोषणा FLG_PEER_BUSY	10
#घोषणा FLG_DCHAN_BUSY	11
#घोषणा FLG_L1_ACTIV	12
#घोषणा FLG_ESTAB_PEND	13
#घोषणा FLG_PTP		14
#घोषणा FLG_FIXED_TEI	15
#घोषणा FLG_L2BLOCK	16
#घोषणा FLG_L1_NOTREADY	17
#घोषणा FLG_LAPD_NET	18
