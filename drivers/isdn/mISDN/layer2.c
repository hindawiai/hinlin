<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *
 * Author	Karsten Keil <kkeil@novell.com>
 *
 * Copyright 2008  by Karsten Keil <kkeil@novell.com>
 */

#समावेश <linux/mISDNअगर.h>
#समावेश <linux/slab.h>
#समावेश "core.h"
#समावेश "fsm.h"
#समावेश "layer2.h"

अटल u_पूर्णांक *debug;

अटल
काष्ठा Fsm l2fsm = अणुशून्य, 0, 0, शून्य, शून्यपूर्ण;

अटल अक्षर *strL2State[] =
अणु
	"ST_L2_1",
	"ST_L2_2",
	"ST_L2_3",
	"ST_L2_4",
	"ST_L2_5",
	"ST_L2_6",
	"ST_L2_7",
	"ST_L2_8",
पूर्ण;

क्रमागत अणु
	EV_L2_UI,
	EV_L2_SABME,
	EV_L2_DISC,
	EV_L2_DM,
	EV_L2_UA,
	EV_L2_FRMR,
	EV_L2_SUPER,
	EV_L2_I,
	EV_L2_DL_DATA,
	EV_L2_ACK_PULL,
	EV_L2_DL_UNITDATA,
	EV_L2_DL_ESTABLISH_REQ,
	EV_L2_DL_RELEASE_REQ,
	EV_L2_MDL_ASSIGN,
	EV_L2_MDL_REMOVE,
	EV_L2_MDL_ERROR,
	EV_L1_DEACTIVATE,
	EV_L2_T200,
	EV_L2_T203,
	EV_L2_T200I,
	EV_L2_T203I,
	EV_L2_SET_OWN_BUSY,
	EV_L2_CLEAR_OWN_BUSY,
	EV_L2_FRAME_ERROR,
पूर्ण;

#घोषणा L2_EVENT_COUNT (EV_L2_FRAME_ERROR + 1)

अटल अक्षर *strL2Event[] =
अणु
	"EV_L2_UI",
	"EV_L2_SABME",
	"EV_L2_DISC",
	"EV_L2_DM",
	"EV_L2_UA",
	"EV_L2_FRMR",
	"EV_L2_SUPER",
	"EV_L2_I",
	"EV_L2_DL_DATA",
	"EV_L2_ACK_PULL",
	"EV_L2_DL_UNITDATA",
	"EV_L2_DL_ESTABLISH_REQ",
	"EV_L2_DL_RELEASE_REQ",
	"EV_L2_MDL_ASSIGN",
	"EV_L2_MDL_REMOVE",
	"EV_L2_MDL_ERROR",
	"EV_L1_DEACTIVATE",
	"EV_L2_T200",
	"EV_L2_T203",
	"EV_L2_T200I",
	"EV_L2_T203I",
	"EV_L2_SET_OWN_BUSY",
	"EV_L2_CLEAR_OWN_BUSY",
	"EV_L2_FRAME_ERROR",
पूर्ण;

अटल व्योम
l2m_debug(काष्ठा FsmInst *fi, अक्षर *fmt, ...)
अणु
	काष्ठा layer2 *l2 = fi->userdata;
	काष्ठा va_क्रमmat vaf;
	बहु_सूची va;

	अगर (!(*debug & DEBUG_L2_FSM))
		वापस;

	बहु_शुरू(va, fmt);

	vaf.fmt = fmt;
	vaf.va = &va;

	prपूर्णांकk(KERN_DEBUG "%s l2 (sapi %d tei %d): %pV\n",
	       mISDNDevName4ch(&l2->ch), l2->sapi, l2->tei, &vaf);

	बहु_पूर्ण(va);
पूर्ण

अंतरभूत u_पूर्णांक
l2headersize(काष्ठा layer2 *l2, पूर्णांक ui)
अणु
	वापस ((test_bit(FLG_MOD128, &l2->flag) && (!ui)) ? 2 : 1) +
		(test_bit(FLG_LAPD, &l2->flag) ? 2 : 1);
पूर्ण

अंतरभूत u_पूर्णांक
l2addrsize(काष्ठा layer2 *l2)
अणु
	वापस test_bit(FLG_LAPD, &l2->flag) ? 2 : 1;
पूर्ण

अटल u_पूर्णांक
l2_newid(काष्ठा layer2 *l2)
अणु
	u_पूर्णांक	id;

	id = l2->next_id++;
	अगर (id == 0x7fff)
		l2->next_id = 1;
	id <<= 16;
	id |= l2->tei << 8;
	id |= l2->sapi;
	वापस id;
पूर्ण

अटल व्योम
l2up(काष्ठा layer2 *l2, u_पूर्णांक prim, काष्ठा sk_buff *skb)
अणु
	पूर्णांक	err;

	अगर (!l2->up)
		वापस;
	mISDN_HEAD_PRIM(skb) = prim;
	mISDN_HEAD_ID(skb) = (l2->ch.nr << 16) | l2->ch.addr;
	err = l2->up->send(l2->up, skb);
	अगर (err) अणु
		prपूर्णांकk(KERN_WARNING "%s: dev %s err=%d\n", __func__,
		       mISDNDevName4ch(&l2->ch), err);
		dev_kमुक्त_skb(skb);
	पूर्ण
पूर्ण

अटल व्योम
l2up_create(काष्ठा layer2 *l2, u_पूर्णांक prim, पूर्णांक len, व्योम *arg)
अणु
	काष्ठा sk_buff	*skb;
	काष्ठा mISDNhead *hh;
	पूर्णांक		err;

	अगर (!l2->up)
		वापस;
	skb = mI_alloc_skb(len, GFP_ATOMIC);
	अगर (!skb)
		वापस;
	hh = mISDN_HEAD_P(skb);
	hh->prim = prim;
	hh->id = (l2->ch.nr << 16) | l2->ch.addr;
	अगर (len)
		skb_put_data(skb, arg, len);
	err = l2->up->send(l2->up, skb);
	अगर (err) अणु
		prपूर्णांकk(KERN_WARNING "%s: dev %s err=%d\n", __func__,
		       mISDNDevName4ch(&l2->ch), err);
		dev_kमुक्त_skb(skb);
	पूर्ण
पूर्ण

अटल पूर्णांक
l2करोwn_skb(काष्ठा layer2 *l2, काष्ठा sk_buff *skb) अणु
	पूर्णांक ret;

	ret = l2->ch.recv(l2->ch.peer, skb);
	अगर (ret && (*debug & DEBUG_L2_RECV))
		prपूर्णांकk(KERN_DEBUG "l2down_skb: dev %s ret(%d)\n",
		       mISDNDevName4ch(&l2->ch), ret);
	वापस ret;
पूर्ण

अटल पूर्णांक
l2करोwn_raw(काष्ठा layer2 *l2, काष्ठा sk_buff *skb)
अणु
	काष्ठा mISDNhead *hh = mISDN_HEAD_P(skb);

	अगर (hh->prim == PH_DATA_REQ) अणु
		अगर (test_and_set_bit(FLG_L1_NOTREADY, &l2->flag)) अणु
			skb_queue_tail(&l2->करोwn_queue, skb);
			वापस 0;
		पूर्ण
		l2->करोwn_id = mISDN_HEAD_ID(skb);
	पूर्ण
	वापस l2करोwn_skb(l2, skb);
पूर्ण

अटल पूर्णांक
l2करोwn(काष्ठा layer2 *l2, u_पूर्णांक prim, u_पूर्णांक id, काष्ठा sk_buff *skb)
अणु
	काष्ठा mISDNhead *hh = mISDN_HEAD_P(skb);

	hh->prim = prim;
	hh->id = id;
	वापस l2करोwn_raw(l2, skb);
पूर्ण

अटल पूर्णांक
l2करोwn_create(काष्ठा layer2 *l2, u_पूर्णांक prim, u_पूर्णांक id, पूर्णांक len, व्योम *arg)
अणु
	काष्ठा sk_buff	*skb;
	पूर्णांक		err;
	काष्ठा mISDNhead *hh;

	skb = mI_alloc_skb(len, GFP_ATOMIC);
	अगर (!skb)
		वापस -ENOMEM;
	hh = mISDN_HEAD_P(skb);
	hh->prim = prim;
	hh->id = id;
	अगर (len)
		skb_put_data(skb, arg, len);
	err = l2करोwn_raw(l2, skb);
	अगर (err)
		dev_kमुक्त_skb(skb);
	वापस err;
पूर्ण

अटल पूर्णांक
ph_data_confirm(काष्ठा layer2 *l2, काष्ठा mISDNhead *hh, काष्ठा sk_buff *skb) अणु
	काष्ठा sk_buff *nskb = skb;
	पूर्णांक ret = -EAGAIN;

	अगर (test_bit(FLG_L1_NOTREADY, &l2->flag)) अणु
		अगर (hh->id == l2->करोwn_id) अणु
			nskb = skb_dequeue(&l2->करोwn_queue);
			अगर (nskb) अणु
				l2->करोwn_id = mISDN_HEAD_ID(nskb);
				अगर (l2करोwn_skb(l2, nskb)) अणु
					dev_kमुक्त_skb(nskb);
					l2->करोwn_id = MISDN_ID_NONE;
				पूर्ण
			पूर्ण अन्यथा
				l2->करोwn_id = MISDN_ID_NONE;
			अगर (ret) अणु
				dev_kमुक्त_skb(skb);
				ret = 0;
			पूर्ण
			अगर (l2->करोwn_id == MISDN_ID_NONE) अणु
				test_and_clear_bit(FLG_L1_NOTREADY, &l2->flag);
				mISDN_FsmEvent(&l2->l2m, EV_L2_ACK_PULL, शून्य);
			पूर्ण
		पूर्ण
	पूर्ण
	अगर (!test_and_set_bit(FLG_L1_NOTREADY, &l2->flag)) अणु
		nskb = skb_dequeue(&l2->करोwn_queue);
		अगर (nskb) अणु
			l2->करोwn_id = mISDN_HEAD_ID(nskb);
			अगर (l2करोwn_skb(l2, nskb)) अणु
				dev_kमुक्त_skb(nskb);
				l2->करोwn_id = MISDN_ID_NONE;
				test_and_clear_bit(FLG_L1_NOTREADY, &l2->flag);
			पूर्ण
		पूर्ण अन्यथा
			test_and_clear_bit(FLG_L1_NOTREADY, &l2->flag);
	पूर्ण
	वापस ret;
पूर्ण

अटल व्योम
l2_समयout(काष्ठा FsmInst *fi, पूर्णांक event, व्योम *arg)
अणु
	काष्ठा layer2 *l2 = fi->userdata;
	काष्ठा sk_buff *skb;
	काष्ठा mISDNhead *hh;

	skb = mI_alloc_skb(0, GFP_ATOMIC);
	अगर (!skb) अणु
		prपूर्णांकk(KERN_WARNING "%s: L2(%d,%d) nr:%x timer %s no skb\n",
		       mISDNDevName4ch(&l2->ch), l2->sapi, l2->tei,
		       l2->ch.nr, event == EV_L2_T200 ? "T200" : "T203");
		वापस;
	पूर्ण
	hh = mISDN_HEAD_P(skb);
	hh->prim = event == EV_L2_T200 ? DL_TIMER200_IND : DL_TIMER203_IND;
	hh->id = l2->ch.nr;
	अगर (*debug & DEBUG_TIMER)
		prपूर्णांकk(KERN_DEBUG "%s: L2(%d,%d) nr:%x timer %s expired\n",
		       mISDNDevName4ch(&l2->ch), l2->sapi, l2->tei,
		       l2->ch.nr, event == EV_L2_T200 ? "T200" : "T203");
	अगर (l2->ch.st)
		l2->ch.st->own.recv(&l2->ch.st->own, skb);
पूर्ण

अटल पूर्णांक
l2mgr(काष्ठा layer2 *l2, u_पूर्णांक prim, व्योम *arg) अणु
	दीर्घ c = (दीर्घ)arg;

	prपूर्णांकk(KERN_WARNING "l2mgr: dev %s addr:%x prim %x %c\n",
	       mISDNDevName4ch(&l2->ch), l2->id, prim, (अक्षर)c);
	अगर (test_bit(FLG_LAPD, &l2->flag) &&
	    !test_bit(FLG_FIXED_TEI, &l2->flag)) अणु
		चयन (c) अणु
		हाल 'C':
		हाल 'D':
		हाल 'G':
		हाल 'H':
			l2_tei(l2, prim, (u_दीर्घ)arg);
			अवरोध;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम
set_peer_busy(काष्ठा layer2 *l2) अणु
	test_and_set_bit(FLG_PEER_BUSY, &l2->flag);
	अगर (skb_queue_len(&l2->i_queue) || skb_queue_len(&l2->ui_queue))
		test_and_set_bit(FLG_L2BLOCK, &l2->flag);
पूर्ण

अटल व्योम
clear_peer_busy(काष्ठा layer2 *l2) अणु
	अगर (test_and_clear_bit(FLG_PEER_BUSY, &l2->flag))
		test_and_clear_bit(FLG_L2BLOCK, &l2->flag);
पूर्ण

अटल व्योम
InitWin(काष्ठा layer2 *l2)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < MAX_WINDOW; i++)
		l2->winकरोwar[i] = शून्य;
पूर्ण

अटल पूर्णांक
मुक्तwin(काष्ठा layer2 *l2)
अणु
	पूर्णांक i, cnt = 0;

	क्रम (i = 0; i < MAX_WINDOW; i++) अणु
		अगर (l2->winकरोwar[i]) अणु
			cnt++;
			dev_kमुक्त_skb(l2->winकरोwar[i]);
			l2->winकरोwar[i] = शून्य;
		पूर्ण
	पूर्ण
	वापस cnt;
पूर्ण

अटल व्योम
ReleaseWin(काष्ठा layer2 *l2)
अणु
	पूर्णांक cnt = मुक्तwin(l2);

	अगर (cnt)
		prपूर्णांकk(KERN_WARNING
		       "isdnl2 freed %d skbuffs in release\n", cnt);
पूर्ण

अंतरभूत अचिन्हित पूर्णांक
cansend(काष्ठा layer2 *l2)
अणु
	अचिन्हित पूर्णांक p1;

	अगर (test_bit(FLG_MOD128, &l2->flag))
		p1 = (l2->vs - l2->va) % 128;
	अन्यथा
		p1 = (l2->vs - l2->va) % 8;
	वापस (p1 < l2->winकरोw) && !test_bit(FLG_PEER_BUSY, &l2->flag);
पूर्ण

अंतरभूत व्योम
clear_exception(काष्ठा layer2 *l2)
अणु
	test_and_clear_bit(FLG_ACK_PEND, &l2->flag);
	test_and_clear_bit(FLG_REJEXC, &l2->flag);
	test_and_clear_bit(FLG_OWN_BUSY, &l2->flag);
	clear_peer_busy(l2);
पूर्ण

अटल पूर्णांक
sethdraddr(काष्ठा layer2 *l2, u_अक्षर *header, पूर्णांक rsp)
अणु
	u_अक्षर *ptr = header;
	पूर्णांक crbit = rsp;

	अगर (test_bit(FLG_LAPD, &l2->flag)) अणु
		अगर (test_bit(FLG_LAPD_NET, &l2->flag))
			crbit = !crbit;
		*ptr++ = (l2->sapi << 2) | (crbit ? 2 : 0);
		*ptr++ = (l2->tei << 1) | 1;
		वापस 2;
	पूर्ण अन्यथा अणु
		अगर (test_bit(FLG_ORIG, &l2->flag))
			crbit = !crbit;
		अगर (crbit)
			*ptr++ = l2->addr.B;
		अन्यथा
			*ptr++ = l2->addr.A;
		वापस 1;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम
enqueue_super(काष्ठा layer2 *l2, काष्ठा sk_buff *skb)
अणु
	अगर (l2करोwn(l2, PH_DATA_REQ, l2_newid(l2), skb))
		dev_kमुक्त_skb(skb);
पूर्ण

अटल अंतरभूत व्योम
enqueue_ui(काष्ठा layer2 *l2, काष्ठा sk_buff *skb)
अणु
	अगर (l2->पंचांग)
		l2_tei(l2, MDL_STATUS_UI_IND, 0);
	अगर (l2करोwn(l2, PH_DATA_REQ, l2_newid(l2), skb))
		dev_kमुक्त_skb(skb);
पूर्ण

अंतरभूत पूर्णांक
IsUI(u_अक्षर *data)
अणु
	वापस (data[0] & 0xef) == UI;
पूर्ण

अंतरभूत पूर्णांक
IsUA(u_अक्षर *data)
अणु
	वापस (data[0] & 0xef) == UA;
पूर्ण

अंतरभूत पूर्णांक
IsDM(u_अक्षर *data)
अणु
	वापस (data[0] & 0xef) == DM;
पूर्ण

अंतरभूत पूर्णांक
IsDISC(u_अक्षर *data)
अणु
	वापस (data[0] & 0xef) == DISC;
पूर्ण

अंतरभूत पूर्णांक
IsRR(u_अक्षर *data, काष्ठा layer2 *l2)
अणु
	अगर (test_bit(FLG_MOD128, &l2->flag))
		वापस data[0] == RR;
	अन्यथा
		वापस (data[0] & 0xf) == 1;
पूर्ण

अंतरभूत पूर्णांक
IsSFrame(u_अक्षर *data, काष्ठा layer2 *l2)
अणु
	रेजिस्टर u_अक्षर d = *data;

	अगर (!test_bit(FLG_MOD128, &l2->flag))
		d &= 0xf;
	वापस ((d & 0xf3) == 1) && ((d & 0x0c) != 0x0c);
पूर्ण

अंतरभूत पूर्णांक
IsSABME(u_अक्षर *data, काष्ठा layer2 *l2)
अणु
	u_अक्षर d = data[0] & ~0x10;

	वापस test_bit(FLG_MOD128, &l2->flag) ? d == SABME : d == SABM;
पूर्ण

अंतरभूत पूर्णांक
IsREJ(u_अक्षर *data, काष्ठा layer2 *l2)
अणु
	वापस test_bit(FLG_MOD128, &l2->flag) ?
		data[0] == REJ : (data[0] & 0xf) == REJ;
पूर्ण

अंतरभूत पूर्णांक
IsFRMR(u_अक्षर *data)
अणु
	वापस (data[0] & 0xef) == FRMR;
पूर्ण

अंतरभूत पूर्णांक
IsRNR(u_अक्षर *data, काष्ठा layer2 *l2)
अणु
	वापस test_bit(FLG_MOD128, &l2->flag) ?
		data[0] == RNR : (data[0] & 0xf) == RNR;
पूर्ण

अटल पूर्णांक
अगरrame_error(काष्ठा layer2 *l2, काष्ठा sk_buff *skb)
अणु
	u_पूर्णांक	i;
	पूर्णांक	rsp = *skb->data & 0x2;

	i = l2addrsize(l2) + (test_bit(FLG_MOD128, &l2->flag) ? 2 : 1);
	अगर (test_bit(FLG_ORIG, &l2->flag))
		rsp = !rsp;
	अगर (rsp)
		वापस 'L';
	अगर (skb->len < i)
		वापस 'N';
	अगर ((skb->len - i) > l2->maxlen)
		वापस 'O';
	वापस 0;
पूर्ण

अटल पूर्णांक
super_error(काष्ठा layer2 *l2, काष्ठा sk_buff *skb)
अणु
	अगर (skb->len != l2addrsize(l2) +
	    (test_bit(FLG_MOD128, &l2->flag) ? 2 : 1))
		वापस 'N';
	वापस 0;
पूर्ण

अटल पूर्णांक
unnum_error(काष्ठा layer2 *l2, काष्ठा sk_buff *skb, पूर्णांक wantrsp)
अणु
	पूर्णांक rsp = (*skb->data & 0x2) >> 1;
	अगर (test_bit(FLG_ORIG, &l2->flag))
		rsp = !rsp;
	अगर (rsp != wantrsp)
		वापस 'L';
	अगर (skb->len != l2addrsize(l2) + 1)
		वापस 'N';
	वापस 0;
पूर्ण

अटल पूर्णांक
UI_error(काष्ठा layer2 *l2, काष्ठा sk_buff *skb)
अणु
	पूर्णांक rsp = *skb->data & 0x2;
	अगर (test_bit(FLG_ORIG, &l2->flag))
		rsp = !rsp;
	अगर (rsp)
		वापस 'L';
	अगर (skb->len > l2->maxlen + l2addrsize(l2) + 1)
		वापस 'O';
	वापस 0;
पूर्ण

अटल पूर्णांक
FRMR_error(काष्ठा layer2 *l2, काष्ठा sk_buff *skb)
अणु
	u_पूर्णांक	headers = l2addrsize(l2) + 1;
	u_अक्षर	*datap = skb->data + headers;
	पूर्णांक	rsp = *skb->data & 0x2;

	अगर (test_bit(FLG_ORIG, &l2->flag))
		rsp = !rsp;
	अगर (!rsp)
		वापस 'L';
	अगर (test_bit(FLG_MOD128, &l2->flag)) अणु
		अगर (skb->len < headers + 5)
			वापस 'N';
		अन्यथा अगर (*debug & DEBUG_L2)
			l2m_debug(&l2->l2m,
				  "FRMR information %2x %2x %2x %2x %2x",
				  datap[0], datap[1], datap[2], datap[3], datap[4]);
	पूर्ण अन्यथा अणु
		अगर (skb->len < headers + 3)
			वापस 'N';
		अन्यथा अगर (*debug & DEBUG_L2)
			l2m_debug(&l2->l2m,
				  "FRMR information %2x %2x %2x",
				  datap[0], datap[1], datap[2]);
	पूर्ण
	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक
legalnr(काष्ठा layer2 *l2, अचिन्हित पूर्णांक nr)
अणु
	अगर (test_bit(FLG_MOD128, &l2->flag))
		वापस ((nr - l2->va) % 128) <= ((l2->vs - l2->va) % 128);
	अन्यथा
		वापस ((nr - l2->va) % 8) <= ((l2->vs - l2->va) % 8);
पूर्ण

अटल व्योम
setva(काष्ठा layer2 *l2, अचिन्हित पूर्णांक nr)
अणु
	काष्ठा sk_buff	*skb;

	जबतक (l2->va != nr) अणु
		l2->va++;
		अगर (test_bit(FLG_MOD128, &l2->flag))
			l2->va %= 128;
		अन्यथा
			l2->va %= 8;
		अगर (l2->winकरोwar[l2->sow]) अणु
			skb_trim(l2->winकरोwar[l2->sow], 0);
			skb_queue_tail(&l2->पंचांगp_queue, l2->winकरोwar[l2->sow]);
			l2->winकरोwar[l2->sow] = शून्य;
		पूर्ण
		l2->sow = (l2->sow + 1) % l2->winकरोw;
	पूर्ण
	skb = skb_dequeue(&l2->पंचांगp_queue);
	जबतक (skb) अणु
		dev_kमुक्त_skb(skb);
		skb = skb_dequeue(&l2->पंचांगp_queue);
	पूर्ण
पूर्ण

अटल व्योम
send_uframe(काष्ठा layer2 *l2, काष्ठा sk_buff *skb, u_अक्षर cmd, u_अक्षर cr)
अणु
	u_अक्षर पंचांगp[MAX_L2HEADER_LEN];
	पूर्णांक i;

	i = sethdraddr(l2, पंचांगp, cr);
	पंचांगp[i++] = cmd;
	अगर (skb)
		skb_trim(skb, 0);
	अन्यथा अणु
		skb = mI_alloc_skb(i, GFP_ATOMIC);
		अगर (!skb) अणु
			prपूर्णांकk(KERN_WARNING "%s: can't alloc skbuff in %s\n",
			       mISDNDevName4ch(&l2->ch), __func__);
			वापस;
		पूर्ण
	पूर्ण
	skb_put_data(skb, पंचांगp, i);
	enqueue_super(l2, skb);
पूर्ण


अंतरभूत u_अक्षर
get_PollFlag(काष्ठा layer2 *l2, काष्ठा sk_buff *skb)
अणु
	वापस skb->data[l2addrsize(l2)] & 0x10;
पूर्ण

अंतरभूत u_अक्षर
get_PollFlagFree(काष्ठा layer2 *l2, काष्ठा sk_buff *skb)
अणु
	u_अक्षर PF;

	PF = get_PollFlag(l2, skb);
	dev_kमुक्त_skb(skb);
	वापस PF;
पूर्ण

अंतरभूत व्योम
start_t200(काष्ठा layer2 *l2, पूर्णांक i)
अणु
	mISDN_FsmAddTimer(&l2->t200, l2->T200, EV_L2_T200, शून्य, i);
	test_and_set_bit(FLG_T200_RUN, &l2->flag);
पूर्ण

अंतरभूत व्योम
restart_t200(काष्ठा layer2 *l2, पूर्णांक i)
अणु
	mISDN_FsmRestartTimer(&l2->t200, l2->T200, EV_L2_T200, शून्य, i);
	test_and_set_bit(FLG_T200_RUN, &l2->flag);
पूर्ण

अंतरभूत व्योम
stop_t200(काष्ठा layer2 *l2, पूर्णांक i)
अणु
	अगर (test_and_clear_bit(FLG_T200_RUN, &l2->flag))
		mISDN_FsmDelTimer(&l2->t200, i);
पूर्ण

अंतरभूत व्योम
st5_dl_release_l2l3(काष्ठा layer2 *l2)
अणु
	पूर्णांक pr;

	अगर (test_and_clear_bit(FLG_PEND_REL, &l2->flag))
		pr = DL_RELEASE_CNF;
	अन्यथा
		pr = DL_RELEASE_IND;
	l2up_create(l2, pr, 0, शून्य);
पूर्ण

अंतरभूत व्योम
lapb_dl_release_l2l3(काष्ठा layer2 *l2, पूर्णांक f)
अणु
	अगर (test_bit(FLG_LAPB, &l2->flag))
		l2करोwn_create(l2, PH_DEACTIVATE_REQ, l2_newid(l2), 0, शून्य);
	l2up_create(l2, f, 0, शून्य);
पूर्ण

अटल व्योम
establishlink(काष्ठा FsmInst *fi)
अणु
	काष्ठा layer2 *l2 = fi->userdata;
	u_अक्षर cmd;

	clear_exception(l2);
	l2->rc = 0;
	cmd = (test_bit(FLG_MOD128, &l2->flag) ? SABME : SABM) | 0x10;
	send_uframe(l2, शून्य, cmd, CMD);
	mISDN_FsmDelTimer(&l2->t203, 1);
	restart_t200(l2, 1);
	test_and_clear_bit(FLG_PEND_REL, &l2->flag);
	मुक्तwin(l2);
	mISDN_FsmChangeState(fi, ST_L2_5);
पूर्ण

अटल व्योम
l2_mdl_error_ua(काष्ठा FsmInst *fi, पूर्णांक event, व्योम *arg)
अणु
	काष्ठा sk_buff *skb = arg;
	काष्ठा layer2 *l2 = fi->userdata;

	अगर (get_PollFlagFree(l2, skb))
		l2mgr(l2, MDL_ERROR_IND, (व्योम *) 'C');
	अन्यथा
		l2mgr(l2, MDL_ERROR_IND, (व्योम *) 'D');

पूर्ण

अटल व्योम
l2_mdl_error_dm(काष्ठा FsmInst *fi, पूर्णांक event, व्योम *arg)
अणु
	काष्ठा sk_buff *skb = arg;
	काष्ठा layer2 *l2 = fi->userdata;

	अगर (get_PollFlagFree(l2, skb))
		l2mgr(l2, MDL_ERROR_IND, (व्योम *) 'B');
	अन्यथा अणु
		l2mgr(l2, MDL_ERROR_IND, (व्योम *) 'E');
		establishlink(fi);
		test_and_clear_bit(FLG_L3_INIT, &l2->flag);
	पूर्ण
पूर्ण

अटल व्योम
l2_st8_mdl_error_dm(काष्ठा FsmInst *fi, पूर्णांक event, व्योम *arg)
अणु
	काष्ठा sk_buff *skb = arg;
	काष्ठा layer2 *l2 = fi->userdata;

	अगर (get_PollFlagFree(l2, skb))
		l2mgr(l2, MDL_ERROR_IND, (व्योम *) 'B');
	अन्यथा
		l2mgr(l2, MDL_ERROR_IND, (व्योम *) 'E');
	establishlink(fi);
	test_and_clear_bit(FLG_L3_INIT, &l2->flag);
पूर्ण

अटल व्योम
l2_go_st3(काष्ठा FsmInst *fi, पूर्णांक event, व्योम *arg)
अणु
	dev_kमुक्त_skb((काष्ठा sk_buff *)arg);
	mISDN_FsmChangeState(fi, ST_L2_3);
पूर्ण

अटल व्योम
l2_mdl_assign(काष्ठा FsmInst *fi, पूर्णांक event, व्योम *arg)
अणु
	काष्ठा layer2	*l2 = fi->userdata;

	mISDN_FsmChangeState(fi, ST_L2_3);
	dev_kमुक्त_skb((काष्ठा sk_buff *)arg);
	l2_tei(l2, MDL_ASSIGN_IND, 0);
पूर्ण

अटल व्योम
l2_queue_ui_assign(काष्ठा FsmInst *fi, पूर्णांक event, व्योम *arg)
अणु
	काष्ठा layer2 *l2 = fi->userdata;
	काष्ठा sk_buff *skb = arg;

	skb_queue_tail(&l2->ui_queue, skb);
	mISDN_FsmChangeState(fi, ST_L2_2);
	l2_tei(l2, MDL_ASSIGN_IND, 0);
पूर्ण

अटल व्योम
l2_queue_ui(काष्ठा FsmInst *fi, पूर्णांक event, व्योम *arg)
अणु
	काष्ठा layer2 *l2 = fi->userdata;
	काष्ठा sk_buff *skb = arg;

	skb_queue_tail(&l2->ui_queue, skb);
पूर्ण

अटल व्योम
tx_ui(काष्ठा layer2 *l2)
अणु
	काष्ठा sk_buff *skb;
	u_अक्षर header[MAX_L2HEADER_LEN];
	पूर्णांक i;

	i = sethdraddr(l2, header, CMD);
	अगर (test_bit(FLG_LAPD_NET, &l2->flag))
		header[1] = 0xff; /* tei 127 */
	header[i++] = UI;
	जबतक ((skb = skb_dequeue(&l2->ui_queue))) अणु
		स_नकल(skb_push(skb, i), header, i);
		enqueue_ui(l2, skb);
	पूर्ण
पूर्ण

अटल व्योम
l2_send_ui(काष्ठा FsmInst *fi, पूर्णांक event, व्योम *arg)
अणु
	काष्ठा layer2 *l2 = fi->userdata;
	काष्ठा sk_buff *skb = arg;

	skb_queue_tail(&l2->ui_queue, skb);
	tx_ui(l2);
पूर्ण

अटल व्योम
l2_got_ui(काष्ठा FsmInst *fi, पूर्णांक event, व्योम *arg)
अणु
	काष्ठा layer2 *l2 = fi->userdata;
	काष्ठा sk_buff *skb = arg;

	skb_pull(skb, l2headersize(l2, 1));
/*
 *		in states 1-3 क्रम broadcast
 */

	अगर (l2->पंचांग)
		l2_tei(l2, MDL_STATUS_UI_IND, 0);
	l2up(l2, DL_UNITDATA_IND, skb);
पूर्ण

अटल व्योम
l2_establish(काष्ठा FsmInst *fi, पूर्णांक event, व्योम *arg)
अणु
	काष्ठा sk_buff *skb = arg;
	काष्ठा layer2 *l2 = fi->userdata;

	establishlink(fi);
	test_and_set_bit(FLG_L3_INIT, &l2->flag);
	dev_kमुक्त_skb(skb);
पूर्ण

अटल व्योम
l2_discard_i_setl3(काष्ठा FsmInst *fi, पूर्णांक event, व्योम *arg)
अणु
	काष्ठा sk_buff *skb = arg;
	काष्ठा layer2 *l2 = fi->userdata;

	skb_queue_purge(&l2->i_queue);
	test_and_set_bit(FLG_L3_INIT, &l2->flag);
	test_and_clear_bit(FLG_PEND_REL, &l2->flag);
	dev_kमुक्त_skb(skb);
पूर्ण

अटल व्योम
l2_l3_reestablish(काष्ठा FsmInst *fi, पूर्णांक event, व्योम *arg)
अणु
	काष्ठा sk_buff *skb = arg;
	काष्ठा layer2 *l2 = fi->userdata;

	skb_queue_purge(&l2->i_queue);
	establishlink(fi);
	test_and_set_bit(FLG_L3_INIT, &l2->flag);
	dev_kमुक्त_skb(skb);
पूर्ण

अटल व्योम
l2_release(काष्ठा FsmInst *fi, पूर्णांक event, व्योम *arg)
अणु
	काष्ठा layer2 *l2 = fi->userdata;
	काष्ठा sk_buff *skb = arg;

	skb_trim(skb, 0);
	l2up(l2, DL_RELEASE_CNF, skb);
पूर्ण

अटल व्योम
l2_pend_rel(काष्ठा FsmInst *fi, पूर्णांक event, व्योम *arg)
अणु
	काष्ठा sk_buff *skb = arg;
	काष्ठा layer2 *l2 = fi->userdata;

	test_and_set_bit(FLG_PEND_REL, &l2->flag);
	dev_kमुक्त_skb(skb);
पूर्ण

अटल व्योम
l2_disconnect(काष्ठा FsmInst *fi, पूर्णांक event, व्योम *arg)
अणु
	काष्ठा layer2 *l2 = fi->userdata;
	काष्ठा sk_buff *skb = arg;

	skb_queue_purge(&l2->i_queue);
	मुक्तwin(l2);
	mISDN_FsmChangeState(fi, ST_L2_6);
	l2->rc = 0;
	send_uframe(l2, शून्य, DISC | 0x10, CMD);
	mISDN_FsmDelTimer(&l2->t203, 1);
	restart_t200(l2, 2);
	dev_kमुक्त_skb(skb);
पूर्ण

अटल व्योम
l2_start_multi(काष्ठा FsmInst *fi, पूर्णांक event, व्योम *arg)
अणु
	काष्ठा layer2	*l2 = fi->userdata;
	काष्ठा sk_buff	*skb = arg;

	l2->vs = 0;
	l2->va = 0;
	l2->vr = 0;
	l2->sow = 0;
	clear_exception(l2);
	send_uframe(l2, शून्य, UA | get_PollFlag(l2, skb), RSP);
	mISDN_FsmChangeState(fi, ST_L2_7);
	mISDN_FsmAddTimer(&l2->t203, l2->T203, EV_L2_T203, शून्य, 3);
	skb_trim(skb, 0);
	l2up(l2, DL_ESTABLISH_IND, skb);
	अगर (l2->पंचांग)
		l2_tei(l2, MDL_STATUS_UP_IND, 0);
पूर्ण

अटल व्योम
l2_send_UA(काष्ठा FsmInst *fi, पूर्णांक event, व्योम *arg)
अणु
	काष्ठा layer2 *l2 = fi->userdata;
	काष्ठा sk_buff *skb = arg;

	send_uframe(l2, skb, UA | get_PollFlag(l2, skb), RSP);
पूर्ण

अटल व्योम
l2_send_DM(काष्ठा FsmInst *fi, पूर्णांक event, व्योम *arg)
अणु
	काष्ठा layer2 *l2 = fi->userdata;
	काष्ठा sk_buff *skb = arg;

	send_uframe(l2, skb, DM | get_PollFlag(l2, skb), RSP);
पूर्ण

अटल व्योम
l2_restart_multi(काष्ठा FsmInst *fi, पूर्णांक event, व्योम *arg)
अणु
	काष्ठा layer2	*l2 = fi->userdata;
	काष्ठा sk_buff	*skb = arg;
	पूर्णांक		est = 0;

	send_uframe(l2, skb, UA | get_PollFlag(l2, skb), RSP);

	l2mgr(l2, MDL_ERROR_IND, (व्योम *) 'F');

	अगर (l2->vs != l2->va) अणु
		skb_queue_purge(&l2->i_queue);
		est = 1;
	पूर्ण

	clear_exception(l2);
	l2->vs = 0;
	l2->va = 0;
	l2->vr = 0;
	l2->sow = 0;
	mISDN_FsmChangeState(fi, ST_L2_7);
	stop_t200(l2, 3);
	mISDN_FsmRestartTimer(&l2->t203, l2->T203, EV_L2_T203, शून्य, 3);

	अगर (est)
		l2up_create(l2, DL_ESTABLISH_IND, 0, शून्य);
/*		mISDN_queue_data(&l2->inst, l2->inst.id | MSG_BROADCAST,
 *		    MGR_SHORTSTATUS | INDICATION, SSTATUS_L2_ESTABLISHED,
 *		    0, शून्य, 0);
 */
	अगर (skb_queue_len(&l2->i_queue) && cansend(l2))
		mISDN_FsmEvent(fi, EV_L2_ACK_PULL, शून्य);
पूर्ण

अटल व्योम
l2_stop_multi(काष्ठा FsmInst *fi, पूर्णांक event, व्योम *arg)
अणु
	काष्ठा layer2	*l2 = fi->userdata;
	काष्ठा sk_buff	*skb = arg;

	mISDN_FsmChangeState(fi, ST_L2_4);
	mISDN_FsmDelTimer(&l2->t203, 3);
	stop_t200(l2, 4);

	send_uframe(l2, skb, UA | get_PollFlag(l2, skb), RSP);
	skb_queue_purge(&l2->i_queue);
	मुक्तwin(l2);
	lapb_dl_release_l2l3(l2, DL_RELEASE_IND);
	अगर (l2->पंचांग)
		l2_tei(l2, MDL_STATUS_DOWN_IND, 0);
पूर्ण

अटल व्योम
l2_connected(काष्ठा FsmInst *fi, पूर्णांक event, व्योम *arg)
अणु
	काष्ठा layer2	*l2 = fi->userdata;
	काष्ठा sk_buff	*skb = arg;
	पूर्णांक pr = -1;

	अगर (!get_PollFlag(l2, skb)) अणु
		l2_mdl_error_ua(fi, event, arg);
		वापस;
	पूर्ण
	dev_kमुक्त_skb(skb);
	अगर (test_and_clear_bit(FLG_PEND_REL, &l2->flag))
		l2_disconnect(fi, event, शून्य);
	अगर (test_and_clear_bit(FLG_L3_INIT, &l2->flag)) अणु
		pr = DL_ESTABLISH_CNF;
	पूर्ण अन्यथा अगर (l2->vs != l2->va) अणु
		skb_queue_purge(&l2->i_queue);
		pr = DL_ESTABLISH_IND;
	पूर्ण
	stop_t200(l2, 5);
	l2->vr = 0;
	l2->vs = 0;
	l2->va = 0;
	l2->sow = 0;
	mISDN_FsmChangeState(fi, ST_L2_7);
	mISDN_FsmAddTimer(&l2->t203, l2->T203, EV_L2_T203, शून्य, 4);
	अगर (pr != -1)
		l2up_create(l2, pr, 0, शून्य);

	अगर (skb_queue_len(&l2->i_queue) && cansend(l2))
		mISDN_FsmEvent(fi, EV_L2_ACK_PULL, शून्य);

	अगर (l2->पंचांग)
		l2_tei(l2, MDL_STATUS_UP_IND, 0);
पूर्ण

अटल व्योम
l2_released(काष्ठा FsmInst *fi, पूर्णांक event, व्योम *arg)
अणु
	काष्ठा layer2 *l2 = fi->userdata;
	काष्ठा sk_buff *skb = arg;

	अगर (!get_PollFlag(l2, skb)) अणु
		l2_mdl_error_ua(fi, event, arg);
		वापस;
	पूर्ण
	dev_kमुक्त_skb(skb);
	stop_t200(l2, 6);
	lapb_dl_release_l2l3(l2, DL_RELEASE_CNF);
	mISDN_FsmChangeState(fi, ST_L2_4);
	अगर (l2->पंचांग)
		l2_tei(l2, MDL_STATUS_DOWN_IND, 0);
पूर्ण

अटल व्योम
l2_reestablish(काष्ठा FsmInst *fi, पूर्णांक event, व्योम *arg)
अणु
	काष्ठा layer2 *l2 = fi->userdata;
	काष्ठा sk_buff *skb = arg;

	अगर (!get_PollFlagFree(l2, skb)) अणु
		establishlink(fi);
		test_and_set_bit(FLG_L3_INIT, &l2->flag);
	पूर्ण
पूर्ण

अटल व्योम
l2_st5_dm_release(काष्ठा FsmInst *fi, पूर्णांक event, व्योम *arg)
अणु
	काष्ठा layer2 *l2 = fi->userdata;
	काष्ठा sk_buff *skb = arg;

	अगर (get_PollFlagFree(l2, skb)) अणु
		stop_t200(l2, 7);
		अगर (!test_bit(FLG_L3_INIT, &l2->flag))
			skb_queue_purge(&l2->i_queue);
		अगर (test_bit(FLG_LAPB, &l2->flag))
			l2करोwn_create(l2, PH_DEACTIVATE_REQ,
				      l2_newid(l2), 0, शून्य);
		st5_dl_release_l2l3(l2);
		mISDN_FsmChangeState(fi, ST_L2_4);
		अगर (l2->पंचांग)
			l2_tei(l2, MDL_STATUS_DOWN_IND, 0);
	पूर्ण
पूर्ण

अटल व्योम
l2_st6_dm_release(काष्ठा FsmInst *fi, पूर्णांक event, व्योम *arg)
अणु
	काष्ठा layer2 *l2 = fi->userdata;
	काष्ठा sk_buff *skb = arg;

	अगर (get_PollFlagFree(l2, skb)) अणु
		stop_t200(l2, 8);
		lapb_dl_release_l2l3(l2, DL_RELEASE_CNF);
		mISDN_FsmChangeState(fi, ST_L2_4);
		अगर (l2->पंचांग)
			l2_tei(l2, MDL_STATUS_DOWN_IND, 0);
	पूर्ण
पूर्ण

अटल व्योम
enquiry_cr(काष्ठा layer2 *l2, u_अक्षर typ, u_अक्षर cr, u_अक्षर pf)
अणु
	काष्ठा sk_buff *skb;
	u_अक्षर पंचांगp[MAX_L2HEADER_LEN];
	पूर्णांक i;

	i = sethdraddr(l2, पंचांगp, cr);
	अगर (test_bit(FLG_MOD128, &l2->flag)) अणु
		पंचांगp[i++] = typ;
		पंचांगp[i++] = (l2->vr << 1) | (pf ? 1 : 0);
	पूर्ण अन्यथा
		पंचांगp[i++] = (l2->vr << 5) | typ | (pf ? 0x10 : 0);
	skb = mI_alloc_skb(i, GFP_ATOMIC);
	अगर (!skb) अणु
		prपूर्णांकk(KERN_WARNING "%s: isdnl2 can't alloc sbbuff in %s\n",
		       mISDNDevName4ch(&l2->ch), __func__);
		वापस;
	पूर्ण
	skb_put_data(skb, पंचांगp, i);
	enqueue_super(l2, skb);
पूर्ण

अंतरभूत व्योम
enquiry_response(काष्ठा layer2 *l2)
अणु
	अगर (test_bit(FLG_OWN_BUSY, &l2->flag))
		enquiry_cr(l2, RNR, RSP, 1);
	अन्यथा
		enquiry_cr(l2, RR, RSP, 1);
	test_and_clear_bit(FLG_ACK_PEND, &l2->flag);
पूर्ण

अंतरभूत व्योम
transmit_enquiry(काष्ठा layer2 *l2)
अणु
	अगर (test_bit(FLG_OWN_BUSY, &l2->flag))
		enquiry_cr(l2, RNR, CMD, 1);
	अन्यथा
		enquiry_cr(l2, RR, CMD, 1);
	test_and_clear_bit(FLG_ACK_PEND, &l2->flag);
	start_t200(l2, 9);
पूर्ण


अटल व्योम
nrerrorrecovery(काष्ठा FsmInst *fi)
अणु
	काष्ठा layer2 *l2 = fi->userdata;

	l2mgr(l2, MDL_ERROR_IND, (व्योम *) 'J');
	establishlink(fi);
	test_and_clear_bit(FLG_L3_INIT, &l2->flag);
पूर्ण

अटल व्योम
invoke_retransmission(काष्ठा layer2 *l2, अचिन्हित पूर्णांक nr)
अणु
	u_पूर्णांक	p1;

	अगर (l2->vs != nr) अणु
		जबतक (l2->vs != nr) अणु
			(l2->vs)--;
			अगर (test_bit(FLG_MOD128, &l2->flag)) अणु
				l2->vs %= 128;
				p1 = (l2->vs - l2->va) % 128;
			पूर्ण अन्यथा अणु
				l2->vs %= 8;
				p1 = (l2->vs - l2->va) % 8;
			पूर्ण
			p1 = (p1 + l2->sow) % l2->winकरोw;
			अगर (l2->winकरोwar[p1])
				skb_queue_head(&l2->i_queue, l2->winकरोwar[p1]);
			अन्यथा
				prपूर्णांकk(KERN_WARNING
				       "%s: windowar[%d] is NULL\n",
				       mISDNDevName4ch(&l2->ch), p1);
			l2->winकरोwar[p1] = शून्य;
		पूर्ण
		mISDN_FsmEvent(&l2->l2m, EV_L2_ACK_PULL, शून्य);
	पूर्ण
पूर्ण

अटल व्योम
l2_st7_got_super(काष्ठा FsmInst *fi, पूर्णांक event, व्योम *arg)
अणु
	काष्ठा layer2 *l2 = fi->userdata;
	काष्ठा sk_buff *skb = arg;
	पूर्णांक PollFlag, rsp, typ = RR;
	अचिन्हित पूर्णांक nr;

	rsp = *skb->data & 0x2;
	अगर (test_bit(FLG_ORIG, &l2->flag))
		rsp = !rsp;

	skb_pull(skb, l2addrsize(l2));
	अगर (IsRNR(skb->data, l2)) अणु
		set_peer_busy(l2);
		typ = RNR;
	पूर्ण अन्यथा
		clear_peer_busy(l2);
	अगर (IsREJ(skb->data, l2))
		typ = REJ;

	अगर (test_bit(FLG_MOD128, &l2->flag)) अणु
		PollFlag = (skb->data[1] & 0x1) == 0x1;
		nr = skb->data[1] >> 1;
	पूर्ण अन्यथा अणु
		PollFlag = (skb->data[0] & 0x10);
		nr = (skb->data[0] >> 5) & 0x7;
	पूर्ण
	dev_kमुक्त_skb(skb);

	अगर (PollFlag) अणु
		अगर (rsp)
			l2mgr(l2, MDL_ERROR_IND, (व्योम *) 'A');
		अन्यथा
			enquiry_response(l2);
	पूर्ण
	अगर (legalnr(l2, nr)) अणु
		अगर (typ == REJ) अणु
			setva(l2, nr);
			invoke_retransmission(l2, nr);
			stop_t200(l2, 10);
			अगर (mISDN_FsmAddTimer(&l2->t203, l2->T203,
					      EV_L2_T203, शून्य, 6))
				l2m_debug(&l2->l2m, "Restart T203 ST7 REJ");
		पूर्ण अन्यथा अगर ((nr == l2->vs) && (typ == RR)) अणु
			setva(l2, nr);
			stop_t200(l2, 11);
			mISDN_FsmRestartTimer(&l2->t203, l2->T203,
					      EV_L2_T203, शून्य, 7);
		पूर्ण अन्यथा अगर ((l2->va != nr) || (typ == RNR)) अणु
			setva(l2, nr);
			अगर (typ != RR)
				mISDN_FsmDelTimer(&l2->t203, 9);
			restart_t200(l2, 12);
		पूर्ण
		अगर (skb_queue_len(&l2->i_queue) && (typ == RR))
			mISDN_FsmEvent(fi, EV_L2_ACK_PULL, शून्य);
	पूर्ण अन्यथा
		nrerrorrecovery(fi);
पूर्ण

अटल व्योम
l2_feed_i_अगर_reest(काष्ठा FsmInst *fi, पूर्णांक event, व्योम *arg)
अणु
	काष्ठा layer2 *l2 = fi->userdata;
	काष्ठा sk_buff *skb = arg;

	अगर (!test_bit(FLG_L3_INIT, &l2->flag))
		skb_queue_tail(&l2->i_queue, skb);
	अन्यथा
		dev_kमुक्त_skb(skb);
पूर्ण

अटल व्योम
l2_feed_i_pull(काष्ठा FsmInst *fi, पूर्णांक event, व्योम *arg)
अणु
	काष्ठा layer2 *l2 = fi->userdata;
	काष्ठा sk_buff *skb = arg;

	skb_queue_tail(&l2->i_queue, skb);
	mISDN_FsmEvent(fi, EV_L2_ACK_PULL, शून्य);
पूर्ण

अटल व्योम
l2_feed_iqueue(काष्ठा FsmInst *fi, पूर्णांक event, व्योम *arg)
अणु
	काष्ठा layer2 *l2 = fi->userdata;
	काष्ठा sk_buff *skb = arg;

	skb_queue_tail(&l2->i_queue, skb);
पूर्ण

अटल व्योम
l2_got_अगरrame(काष्ठा FsmInst *fi, पूर्णांक event, व्योम *arg)
अणु
	काष्ठा layer2	*l2 = fi->userdata;
	काष्ठा sk_buff	*skb = arg;
	पूर्णांक		PollFlag, i;
	u_पूर्णांक		ns, nr;

	i = l2addrsize(l2);
	अगर (test_bit(FLG_MOD128, &l2->flag)) अणु
		PollFlag = ((skb->data[i + 1] & 0x1) == 0x1);
		ns = skb->data[i] >> 1;
		nr = (skb->data[i + 1] >> 1) & 0x7f;
	पूर्ण अन्यथा अणु
		PollFlag = (skb->data[i] & 0x10);
		ns = (skb->data[i] >> 1) & 0x7;
		nr = (skb->data[i] >> 5) & 0x7;
	पूर्ण
	अगर (test_bit(FLG_OWN_BUSY, &l2->flag)) अणु
		dev_kमुक्त_skb(skb);
		अगर (PollFlag)
			enquiry_response(l2);
	पूर्ण अन्यथा अणु
		अगर (l2->vr == ns) अणु
			l2->vr++;
			अगर (test_bit(FLG_MOD128, &l2->flag))
				l2->vr %= 128;
			अन्यथा
				l2->vr %= 8;
			test_and_clear_bit(FLG_REJEXC, &l2->flag);
			अगर (PollFlag)
				enquiry_response(l2);
			अन्यथा
				test_and_set_bit(FLG_ACK_PEND, &l2->flag);
			skb_pull(skb, l2headersize(l2, 0));
			l2up(l2, DL_DATA_IND, skb);
		पूर्ण अन्यथा अणु
			/* n(s)!=v(r) */
			dev_kमुक्त_skb(skb);
			अगर (test_and_set_bit(FLG_REJEXC, &l2->flag)) अणु
				अगर (PollFlag)
					enquiry_response(l2);
			पूर्ण अन्यथा अणु
				enquiry_cr(l2, REJ, RSP, PollFlag);
				test_and_clear_bit(FLG_ACK_PEND, &l2->flag);
			पूर्ण
		पूर्ण
	पूर्ण
	अगर (legalnr(l2, nr)) अणु
		अगर (!test_bit(FLG_PEER_BUSY, &l2->flag) &&
		    (fi->state == ST_L2_7)) अणु
			अगर (nr == l2->vs) अणु
				stop_t200(l2, 13);
				mISDN_FsmRestartTimer(&l2->t203, l2->T203,
						      EV_L2_T203, शून्य, 7);
			पूर्ण अन्यथा अगर (nr != l2->va)
				restart_t200(l2, 14);
		पूर्ण
		setva(l2, nr);
	पूर्ण अन्यथा अणु
		nrerrorrecovery(fi);
		वापस;
	पूर्ण
	अगर (skb_queue_len(&l2->i_queue) && (fi->state == ST_L2_7))
		mISDN_FsmEvent(fi, EV_L2_ACK_PULL, शून्य);
	अगर (test_and_clear_bit(FLG_ACK_PEND, &l2->flag))
		enquiry_cr(l2, RR, RSP, 0);
पूर्ण

अटल व्योम
l2_got_tei(काष्ठा FsmInst *fi, पूर्णांक event, व्योम *arg)
अणु
	काष्ठा layer2	*l2 = fi->userdata;
	u_पूर्णांक		info;

	l2->tei = (चिन्हित अक्षर)(दीर्घ)arg;
	set_channel_address(&l2->ch, l2->sapi, l2->tei);
	info = DL_INFO_L2_CONNECT;
	l2up_create(l2, DL_INFORMATION_IND, माप(info), &info);
	अगर (fi->state == ST_L2_3) अणु
		establishlink(fi);
		test_and_set_bit(FLG_L3_INIT, &l2->flag);
	पूर्ण अन्यथा
		mISDN_FsmChangeState(fi, ST_L2_4);
	अगर (skb_queue_len(&l2->ui_queue))
		tx_ui(l2);
पूर्ण

अटल व्योम
l2_st5_tout_200(काष्ठा FsmInst *fi, पूर्णांक event, व्योम *arg)
अणु
	काष्ठा layer2 *l2 = fi->userdata;

	अगर (test_bit(FLG_LAPD, &l2->flag) &&
	    test_bit(FLG_DCHAN_BUSY, &l2->flag)) अणु
		mISDN_FsmAddTimer(&l2->t200, l2->T200, EV_L2_T200, शून्य, 9);
	पूर्ण अन्यथा अगर (l2->rc == l2->N200) अणु
		mISDN_FsmChangeState(fi, ST_L2_4);
		test_and_clear_bit(FLG_T200_RUN, &l2->flag);
		skb_queue_purge(&l2->i_queue);
		l2mgr(l2, MDL_ERROR_IND, (व्योम *) 'G');
		अगर (test_bit(FLG_LAPB, &l2->flag))
			l2करोwn_create(l2, PH_DEACTIVATE_REQ,
				      l2_newid(l2), 0, शून्य);
		st5_dl_release_l2l3(l2);
		अगर (l2->पंचांग)
			l2_tei(l2, MDL_STATUS_DOWN_IND, 0);
	पूर्ण अन्यथा अणु
		l2->rc++;
		mISDN_FsmAddTimer(&l2->t200, l2->T200, EV_L2_T200, शून्य, 9);
		send_uframe(l2, शून्य, (test_bit(FLG_MOD128, &l2->flag) ?
				       SABME : SABM) | 0x10, CMD);
	पूर्ण
पूर्ण

अटल व्योम
l2_st6_tout_200(काष्ठा FsmInst *fi, पूर्णांक event, व्योम *arg)
अणु
	काष्ठा layer2 *l2 = fi->userdata;

	अगर (test_bit(FLG_LAPD, &l2->flag) &&
	    test_bit(FLG_DCHAN_BUSY, &l2->flag)) अणु
		mISDN_FsmAddTimer(&l2->t200, l2->T200, EV_L2_T200, शून्य, 9);
	पूर्ण अन्यथा अगर (l2->rc == l2->N200) अणु
		mISDN_FsmChangeState(fi, ST_L2_4);
		test_and_clear_bit(FLG_T200_RUN, &l2->flag);
		l2mgr(l2, MDL_ERROR_IND, (व्योम *) 'H');
		lapb_dl_release_l2l3(l2, DL_RELEASE_CNF);
		अगर (l2->पंचांग)
			l2_tei(l2, MDL_STATUS_DOWN_IND, 0);
	पूर्ण अन्यथा अणु
		l2->rc++;
		mISDN_FsmAddTimer(&l2->t200, l2->T200, EV_L2_T200,
				  शून्य, 9);
		send_uframe(l2, शून्य, DISC | 0x10, CMD);
	पूर्ण
पूर्ण

अटल व्योम
l2_st7_tout_200(काष्ठा FsmInst *fi, पूर्णांक event, व्योम *arg)
अणु
	काष्ठा layer2 *l2 = fi->userdata;

	अगर (test_bit(FLG_LAPD, &l2->flag) &&
	    test_bit(FLG_DCHAN_BUSY, &l2->flag)) अणु
		mISDN_FsmAddTimer(&l2->t200, l2->T200, EV_L2_T200, शून्य, 9);
		वापस;
	पूर्ण
	test_and_clear_bit(FLG_T200_RUN, &l2->flag);
	l2->rc = 0;
	mISDN_FsmChangeState(fi, ST_L2_8);
	transmit_enquiry(l2);
	l2->rc++;
पूर्ण

अटल व्योम
l2_st8_tout_200(काष्ठा FsmInst *fi, पूर्णांक event, व्योम *arg)
अणु
	काष्ठा layer2 *l2 = fi->userdata;

	अगर (test_bit(FLG_LAPD, &l2->flag) &&
	    test_bit(FLG_DCHAN_BUSY, &l2->flag)) अणु
		mISDN_FsmAddTimer(&l2->t200, l2->T200, EV_L2_T200, शून्य, 9);
		वापस;
	पूर्ण
	test_and_clear_bit(FLG_T200_RUN, &l2->flag);
	अगर (l2->rc == l2->N200) अणु
		l2mgr(l2, MDL_ERROR_IND, (व्योम *) 'I');
		establishlink(fi);
		test_and_clear_bit(FLG_L3_INIT, &l2->flag);
	पूर्ण अन्यथा अणु
		transmit_enquiry(l2);
		l2->rc++;
	पूर्ण
पूर्ण

अटल व्योम
l2_st7_tout_203(काष्ठा FsmInst *fi, पूर्णांक event, व्योम *arg)
अणु
	काष्ठा layer2 *l2 = fi->userdata;

	अगर (test_bit(FLG_LAPD, &l2->flag) &&
	    test_bit(FLG_DCHAN_BUSY, &l2->flag)) अणु
		mISDN_FsmAddTimer(&l2->t203, l2->T203, EV_L2_T203, शून्य, 9);
		वापस;
	पूर्ण
	mISDN_FsmChangeState(fi, ST_L2_8);
	transmit_enquiry(l2);
	l2->rc = 0;
पूर्ण

अटल व्योम
l2_pull_iqueue(काष्ठा FsmInst *fi, पूर्णांक event, व्योम *arg)
अणु
	काष्ठा layer2	*l2 = fi->userdata;
	काष्ठा sk_buff	*skb, *nskb;
	u_अक्षर		header[MAX_L2HEADER_LEN];
	u_पूर्णांक		i, p1;

	अगर (!cansend(l2))
		वापस;

	skb = skb_dequeue(&l2->i_queue);
	अगर (!skb)
		वापस;
	i = sethdraddr(l2, header, CMD);
	अगर (test_bit(FLG_MOD128, &l2->flag)) अणु
		header[i++] = l2->vs << 1;
		header[i++] = l2->vr << 1;
	पूर्ण अन्यथा
		header[i++] = (l2->vr << 5) | (l2->vs << 1);
	nskb = skb_पुनः_स्मृति_headroom(skb, i);
	अगर (!nskb) अणु
		prपूर्णांकk(KERN_WARNING "%s: no headroom(%d) copy for IFrame\n",
		       mISDNDevName4ch(&l2->ch), i);
		skb_queue_head(&l2->i_queue, skb);
		वापस;
	पूर्ण
	अगर (test_bit(FLG_MOD128, &l2->flag)) अणु
		p1 = (l2->vs - l2->va) % 128;
		l2->vs = (l2->vs + 1) % 128;
	पूर्ण अन्यथा अणु
		p1 = (l2->vs - l2->va) % 8;
		l2->vs = (l2->vs + 1) % 8;
	पूर्ण
	p1 = (p1 + l2->sow) % l2->winकरोw;
	अगर (l2->winकरोwar[p1]) अणु
		prपूर्णांकk(KERN_WARNING "%s: l2 try overwrite ack queue entry %d\n",
		       mISDNDevName4ch(&l2->ch), p1);
		dev_kमुक्त_skb(l2->winकरोwar[p1]);
	पूर्ण
	l2->winकरोwar[p1] = skb;
	स_नकल(skb_push(nskb, i), header, i);
	l2करोwn(l2, PH_DATA_REQ, l2_newid(l2), nskb);
	test_and_clear_bit(FLG_ACK_PEND, &l2->flag);
	अगर (!test_and_set_bit(FLG_T200_RUN, &l2->flag)) अणु
		mISDN_FsmDelTimer(&l2->t203, 13);
		mISDN_FsmAddTimer(&l2->t200, l2->T200, EV_L2_T200, शून्य, 11);
	पूर्ण
पूर्ण

अटल व्योम
l2_st8_got_super(काष्ठा FsmInst *fi, पूर्णांक event, व्योम *arg)
अणु
	काष्ठा layer2 *l2 = fi->userdata;
	काष्ठा sk_buff *skb = arg;
	पूर्णांक PollFlag, rsp, rnr = 0;
	अचिन्हित पूर्णांक nr;

	rsp = *skb->data & 0x2;
	अगर (test_bit(FLG_ORIG, &l2->flag))
		rsp = !rsp;

	skb_pull(skb, l2addrsize(l2));

	अगर (IsRNR(skb->data, l2)) अणु
		set_peer_busy(l2);
		rnr = 1;
	पूर्ण अन्यथा
		clear_peer_busy(l2);

	अगर (test_bit(FLG_MOD128, &l2->flag)) अणु
		PollFlag = (skb->data[1] & 0x1) == 0x1;
		nr = skb->data[1] >> 1;
	पूर्ण अन्यथा अणु
		PollFlag = (skb->data[0] & 0x10);
		nr = (skb->data[0] >> 5) & 0x7;
	पूर्ण
	dev_kमुक्त_skb(skb);
	अगर (rsp && PollFlag) अणु
		अगर (legalnr(l2, nr)) अणु
			अगर (rnr) अणु
				restart_t200(l2, 15);
			पूर्ण अन्यथा अणु
				stop_t200(l2, 16);
				mISDN_FsmAddTimer(&l2->t203, l2->T203,
						  EV_L2_T203, शून्य, 5);
				setva(l2, nr);
			पूर्ण
			invoke_retransmission(l2, nr);
			mISDN_FsmChangeState(fi, ST_L2_7);
			अगर (skb_queue_len(&l2->i_queue) && cansend(l2))
				mISDN_FsmEvent(fi, EV_L2_ACK_PULL, शून्य);
		पूर्ण अन्यथा
			nrerrorrecovery(fi);
	पूर्ण अन्यथा अणु
		अगर (!rsp && PollFlag)
			enquiry_response(l2);
		अगर (legalnr(l2, nr))
			setva(l2, nr);
		अन्यथा
			nrerrorrecovery(fi);
	पूर्ण
पूर्ण

अटल व्योम
l2_got_FRMR(काष्ठा FsmInst *fi, पूर्णांक event, व्योम *arg)
अणु
	काष्ठा layer2 *l2 = fi->userdata;
	काष्ठा sk_buff *skb = arg;

	skb_pull(skb, l2addrsize(l2) + 1);

	अगर (!(skb->data[0] & 1) || ((skb->data[0] & 3) == 1) || /* I or S */
	    (IsUA(skb->data) && (fi->state == ST_L2_7))) अणु
		l2mgr(l2, MDL_ERROR_IND, (व्योम *) 'K');
		establishlink(fi);
		test_and_clear_bit(FLG_L3_INIT, &l2->flag);
	पूर्ण
	dev_kमुक्त_skb(skb);
पूर्ण

अटल व्योम
l2_st24_tei_हटाओ(काष्ठा FsmInst *fi, पूर्णांक event, व्योम *arg)
अणु
	काष्ठा layer2 *l2 = fi->userdata;

	skb_queue_purge(&l2->ui_queue);
	l2->tei = GROUP_TEI;
	mISDN_FsmChangeState(fi, ST_L2_1);
पूर्ण

अटल व्योम
l2_st3_tei_हटाओ(काष्ठा FsmInst *fi, पूर्णांक event, व्योम *arg)
अणु
	काष्ठा layer2 *l2 = fi->userdata;

	skb_queue_purge(&l2->ui_queue);
	l2->tei = GROUP_TEI;
	l2up_create(l2, DL_RELEASE_IND, 0, शून्य);
	mISDN_FsmChangeState(fi, ST_L2_1);
पूर्ण

अटल व्योम
l2_st5_tei_हटाओ(काष्ठा FsmInst *fi, पूर्णांक event, व्योम *arg)
अणु
	काष्ठा layer2 *l2 = fi->userdata;

	skb_queue_purge(&l2->i_queue);
	skb_queue_purge(&l2->ui_queue);
	मुक्तwin(l2);
	l2->tei = GROUP_TEI;
	stop_t200(l2, 17);
	st5_dl_release_l2l3(l2);
	mISDN_FsmChangeState(fi, ST_L2_1);
पूर्ण

अटल व्योम
l2_st6_tei_हटाओ(काष्ठा FsmInst *fi, पूर्णांक event, व्योम *arg)
अणु
	काष्ठा layer2 *l2 = fi->userdata;

	skb_queue_purge(&l2->ui_queue);
	l2->tei = GROUP_TEI;
	stop_t200(l2, 18);
	l2up_create(l2, DL_RELEASE_IND, 0, शून्य);
	mISDN_FsmChangeState(fi, ST_L2_1);
पूर्ण

अटल व्योम
l2_tei_हटाओ(काष्ठा FsmInst *fi, पूर्णांक event, व्योम *arg)
अणु
	काष्ठा layer2 *l2 = fi->userdata;

	skb_queue_purge(&l2->i_queue);
	skb_queue_purge(&l2->ui_queue);
	मुक्तwin(l2);
	l2->tei = GROUP_TEI;
	stop_t200(l2, 17);
	mISDN_FsmDelTimer(&l2->t203, 19);
	l2up_create(l2, DL_RELEASE_IND, 0, शून्य);
/*	mISDN_queue_data(&l2->inst, l2->inst.id | MSG_BROADCAST,
 *		MGR_SHORTSTATUS_IND, SSTATUS_L2_RELEASED,
 *		0, शून्य, 0);
 */
	mISDN_FsmChangeState(fi, ST_L2_1);
पूर्ण

अटल व्योम
l2_st14_persistent_da(काष्ठा FsmInst *fi, पूर्णांक event, व्योम *arg)
अणु
	काष्ठा layer2 *l2 = fi->userdata;
	काष्ठा sk_buff *skb = arg;

	skb_queue_purge(&l2->i_queue);
	skb_queue_purge(&l2->ui_queue);
	अगर (test_and_clear_bit(FLG_ESTAB_PEND, &l2->flag))
		l2up(l2, DL_RELEASE_IND, skb);
	अन्यथा
		dev_kमुक्त_skb(skb);
पूर्ण

अटल व्योम
l2_st5_persistent_da(काष्ठा FsmInst *fi, पूर्णांक event, व्योम *arg)
अणु
	काष्ठा layer2 *l2 = fi->userdata;
	काष्ठा sk_buff *skb = arg;

	skb_queue_purge(&l2->i_queue);
	skb_queue_purge(&l2->ui_queue);
	मुक्तwin(l2);
	stop_t200(l2, 19);
	st5_dl_release_l2l3(l2);
	mISDN_FsmChangeState(fi, ST_L2_4);
	अगर (l2->पंचांग)
		l2_tei(l2, MDL_STATUS_DOWN_IND, 0);
	dev_kमुक्त_skb(skb);
पूर्ण

अटल व्योम
l2_st6_persistent_da(काष्ठा FsmInst *fi, पूर्णांक event, व्योम *arg)
अणु
	काष्ठा layer2 *l2 = fi->userdata;
	काष्ठा sk_buff *skb = arg;

	skb_queue_purge(&l2->ui_queue);
	stop_t200(l2, 20);
	l2up(l2, DL_RELEASE_CNF, skb);
	mISDN_FsmChangeState(fi, ST_L2_4);
	अगर (l2->पंचांग)
		l2_tei(l2, MDL_STATUS_DOWN_IND, 0);
पूर्ण

अटल व्योम
l2_persistent_da(काष्ठा FsmInst *fi, पूर्णांक event, व्योम *arg)
अणु
	काष्ठा layer2 *l2 = fi->userdata;
	काष्ठा sk_buff *skb = arg;

	skb_queue_purge(&l2->i_queue);
	skb_queue_purge(&l2->ui_queue);
	मुक्तwin(l2);
	stop_t200(l2, 19);
	mISDN_FsmDelTimer(&l2->t203, 19);
	l2up(l2, DL_RELEASE_IND, skb);
	mISDN_FsmChangeState(fi, ST_L2_4);
	अगर (l2->पंचांग)
		l2_tei(l2, MDL_STATUS_DOWN_IND, 0);
पूर्ण

अटल व्योम
l2_set_own_busy(काष्ठा FsmInst *fi, पूर्णांक event, व्योम *arg)
अणु
	काष्ठा layer2 *l2 = fi->userdata;
	काष्ठा sk_buff *skb = arg;

	अगर (!test_and_set_bit(FLG_OWN_BUSY, &l2->flag)) अणु
		enquiry_cr(l2, RNR, RSP, 0);
		test_and_clear_bit(FLG_ACK_PEND, &l2->flag);
	पूर्ण
	dev_kमुक्त_skb(skb);
पूर्ण

अटल व्योम
l2_clear_own_busy(काष्ठा FsmInst *fi, पूर्णांक event, व्योम *arg)
अणु
	काष्ठा layer2 *l2 = fi->userdata;
	काष्ठा sk_buff *skb = arg;

	अगर (!test_and_clear_bit(FLG_OWN_BUSY, &l2->flag)) अणु
		enquiry_cr(l2, RR, RSP, 0);
		test_and_clear_bit(FLG_ACK_PEND, &l2->flag);
	पूर्ण
	dev_kमुक्त_skb(skb);
पूर्ण

अटल व्योम
l2_frame_error(काष्ठा FsmInst *fi, पूर्णांक event, व्योम *arg)
अणु
	काष्ठा layer2 *l2 = fi->userdata;

	l2mgr(l2, MDL_ERROR_IND, arg);
पूर्ण

अटल व्योम
l2_frame_error_reest(काष्ठा FsmInst *fi, पूर्णांक event, व्योम *arg)
अणु
	काष्ठा layer2 *l2 = fi->userdata;

	l2mgr(l2, MDL_ERROR_IND, arg);
	establishlink(fi);
	test_and_clear_bit(FLG_L3_INIT, &l2->flag);
पूर्ण

अटल काष्ठा FsmNode L2FnList[] =
अणु
	अणुST_L2_1, EV_L2_DL_ESTABLISH_REQ, l2_mdl_assignपूर्ण,
	अणुST_L2_2, EV_L2_DL_ESTABLISH_REQ, l2_go_st3पूर्ण,
	अणुST_L2_4, EV_L2_DL_ESTABLISH_REQ, l2_establishपूर्ण,
	अणुST_L2_5, EV_L2_DL_ESTABLISH_REQ, l2_discard_i_setl3पूर्ण,
	अणुST_L2_7, EV_L2_DL_ESTABLISH_REQ, l2_l3_reestablishपूर्ण,
	अणुST_L2_8, EV_L2_DL_ESTABLISH_REQ, l2_l3_reestablishपूर्ण,
	अणुST_L2_4, EV_L2_DL_RELEASE_REQ, l2_releaseपूर्ण,
	अणुST_L2_5, EV_L2_DL_RELEASE_REQ, l2_pend_relपूर्ण,
	अणुST_L2_7, EV_L2_DL_RELEASE_REQ, l2_disconnectपूर्ण,
	अणुST_L2_8, EV_L2_DL_RELEASE_REQ, l2_disconnectपूर्ण,
	अणुST_L2_5, EV_L2_DL_DATA, l2_feed_i_अगर_reestपूर्ण,
	अणुST_L2_7, EV_L2_DL_DATA, l2_feed_i_pullपूर्ण,
	अणुST_L2_8, EV_L2_DL_DATA, l2_feed_iqueueपूर्ण,
	अणुST_L2_1, EV_L2_DL_UNITDATA, l2_queue_ui_assignपूर्ण,
	अणुST_L2_2, EV_L2_DL_UNITDATA, l2_queue_uiपूर्ण,
	अणुST_L2_3, EV_L2_DL_UNITDATA, l2_queue_uiपूर्ण,
	अणुST_L2_4, EV_L2_DL_UNITDATA, l2_send_uiपूर्ण,
	अणुST_L2_5, EV_L2_DL_UNITDATA, l2_send_uiपूर्ण,
	अणुST_L2_6, EV_L2_DL_UNITDATA, l2_send_uiपूर्ण,
	अणुST_L2_7, EV_L2_DL_UNITDATA, l2_send_uiपूर्ण,
	अणुST_L2_8, EV_L2_DL_UNITDATA, l2_send_uiपूर्ण,
	अणुST_L2_1, EV_L2_MDL_ASSIGN, l2_got_teiपूर्ण,
	अणुST_L2_2, EV_L2_MDL_ASSIGN, l2_got_teiपूर्ण,
	अणुST_L2_3, EV_L2_MDL_ASSIGN, l2_got_teiपूर्ण,
	अणुST_L2_2, EV_L2_MDL_ERROR, l2_st24_tei_हटाओपूर्ण,
	अणुST_L2_3, EV_L2_MDL_ERROR, l2_st3_tei_हटाओपूर्ण,
	अणुST_L2_4, EV_L2_MDL_REMOVE, l2_st24_tei_हटाओपूर्ण,
	अणुST_L2_5, EV_L2_MDL_REMOVE, l2_st5_tei_हटाओपूर्ण,
	अणुST_L2_6, EV_L2_MDL_REMOVE, l2_st6_tei_हटाओपूर्ण,
	अणुST_L2_7, EV_L2_MDL_REMOVE, l2_tei_हटाओपूर्ण,
	अणुST_L2_8, EV_L2_MDL_REMOVE, l2_tei_हटाओपूर्ण,
	अणुST_L2_4, EV_L2_SABME, l2_start_multiपूर्ण,
	अणुST_L2_5, EV_L2_SABME, l2_send_UAपूर्ण,
	अणुST_L2_6, EV_L2_SABME, l2_send_DMपूर्ण,
	अणुST_L2_7, EV_L2_SABME, l2_restart_multiपूर्ण,
	अणुST_L2_8, EV_L2_SABME, l2_restart_multiपूर्ण,
	अणुST_L2_4, EV_L2_DISC, l2_send_DMपूर्ण,
	अणुST_L2_5, EV_L2_DISC, l2_send_DMपूर्ण,
	अणुST_L2_6, EV_L2_DISC, l2_send_UAपूर्ण,
	अणुST_L2_7, EV_L2_DISC, l2_stop_multiपूर्ण,
	अणुST_L2_8, EV_L2_DISC, l2_stop_multiपूर्ण,
	अणुST_L2_4, EV_L2_UA, l2_mdl_error_uaपूर्ण,
	अणुST_L2_5, EV_L2_UA, l2_connectedपूर्ण,
	अणुST_L2_6, EV_L2_UA, l2_releasedपूर्ण,
	अणुST_L2_7, EV_L2_UA, l2_mdl_error_uaपूर्ण,
	अणुST_L2_8, EV_L2_UA, l2_mdl_error_uaपूर्ण,
	अणुST_L2_4, EV_L2_DM, l2_reestablishपूर्ण,
	अणुST_L2_5, EV_L2_DM, l2_st5_dm_releaseपूर्ण,
	अणुST_L2_6, EV_L2_DM, l2_st6_dm_releaseपूर्ण,
	अणुST_L2_7, EV_L2_DM, l2_mdl_error_dmपूर्ण,
	अणुST_L2_8, EV_L2_DM, l2_st8_mdl_error_dmपूर्ण,
	अणुST_L2_1, EV_L2_UI, l2_got_uiपूर्ण,
	अणुST_L2_2, EV_L2_UI, l2_got_uiपूर्ण,
	अणुST_L2_3, EV_L2_UI, l2_got_uiपूर्ण,
	अणुST_L2_4, EV_L2_UI, l2_got_uiपूर्ण,
	अणुST_L2_5, EV_L2_UI, l2_got_uiपूर्ण,
	अणुST_L2_6, EV_L2_UI, l2_got_uiपूर्ण,
	अणुST_L2_7, EV_L2_UI, l2_got_uiपूर्ण,
	अणुST_L2_8, EV_L2_UI, l2_got_uiपूर्ण,
	अणुST_L2_7, EV_L2_FRMR, l2_got_FRMRपूर्ण,
	अणुST_L2_8, EV_L2_FRMR, l2_got_FRMRपूर्ण,
	अणुST_L2_7, EV_L2_SUPER, l2_st7_got_superपूर्ण,
	अणुST_L2_8, EV_L2_SUPER, l2_st8_got_superपूर्ण,
	अणुST_L2_7, EV_L2_I, l2_got_अगरrameपूर्ण,
	अणुST_L2_8, EV_L2_I, l2_got_अगरrameपूर्ण,
	अणुST_L2_5, EV_L2_T200, l2_समयoutपूर्ण,
	अणुST_L2_6, EV_L2_T200, l2_समयoutपूर्ण,
	अणुST_L2_7, EV_L2_T200, l2_समयoutपूर्ण,
	अणुST_L2_8, EV_L2_T200, l2_समयoutपूर्ण,
	अणुST_L2_7, EV_L2_T203, l2_समयoutपूर्ण,
	अणुST_L2_5, EV_L2_T200I, l2_st5_tout_200पूर्ण,
	अणुST_L2_6, EV_L2_T200I, l2_st6_tout_200पूर्ण,
	अणुST_L2_7, EV_L2_T200I, l2_st7_tout_200पूर्ण,
	अणुST_L2_8, EV_L2_T200I, l2_st8_tout_200पूर्ण,
	अणुST_L2_7, EV_L2_T203I, l2_st7_tout_203पूर्ण,
	अणुST_L2_7, EV_L2_ACK_PULL, l2_pull_iqueueपूर्ण,
	अणुST_L2_7, EV_L2_SET_OWN_BUSY, l2_set_own_busyपूर्ण,
	अणुST_L2_8, EV_L2_SET_OWN_BUSY, l2_set_own_busyपूर्ण,
	अणुST_L2_7, EV_L2_CLEAR_OWN_BUSY, l2_clear_own_busyपूर्ण,
	अणुST_L2_8, EV_L2_CLEAR_OWN_BUSY, l2_clear_own_busyपूर्ण,
	अणुST_L2_4, EV_L2_FRAME_ERROR, l2_frame_errorपूर्ण,
	अणुST_L2_5, EV_L2_FRAME_ERROR, l2_frame_errorपूर्ण,
	अणुST_L2_6, EV_L2_FRAME_ERROR, l2_frame_errorपूर्ण,
	अणुST_L2_7, EV_L2_FRAME_ERROR, l2_frame_error_reestपूर्ण,
	अणुST_L2_8, EV_L2_FRAME_ERROR, l2_frame_error_reestपूर्ण,
	अणुST_L2_1, EV_L1_DEACTIVATE, l2_st14_persistent_daपूर्ण,
	अणुST_L2_2, EV_L1_DEACTIVATE, l2_st24_tei_हटाओपूर्ण,
	अणुST_L2_3, EV_L1_DEACTIVATE, l2_st3_tei_हटाओपूर्ण,
	अणुST_L2_4, EV_L1_DEACTIVATE, l2_st14_persistent_daपूर्ण,
	अणुST_L2_5, EV_L1_DEACTIVATE, l2_st5_persistent_daपूर्ण,
	अणुST_L2_6, EV_L1_DEACTIVATE, l2_st6_persistent_daपूर्ण,
	अणुST_L2_7, EV_L1_DEACTIVATE, l2_persistent_daपूर्ण,
	अणुST_L2_8, EV_L1_DEACTIVATE, l2_persistent_daपूर्ण,
पूर्ण;

अटल पूर्णांक
ph_data_indication(काष्ठा layer2 *l2, काष्ठा mISDNhead *hh, काष्ठा sk_buff *skb)
अणु
	u_अक्षर	*datap = skb->data;
	पूर्णांक	ret = -EINVAL;
	पूर्णांक	psapi, ptei;
	u_पूर्णांक	l;
	पूर्णांक	c = 0;

	l = l2addrsize(l2);
	अगर (skb->len <= l) अणु
		mISDN_FsmEvent(&l2->l2m, EV_L2_FRAME_ERROR, (व्योम *) 'N');
		वापस ret;
	पूर्ण
	अगर (test_bit(FLG_LAPD, &l2->flag)) अणु /* Maybe not needed */
		psapi = *datap++;
		ptei = *datap++;
		अगर ((psapi & 1) || !(ptei & 1)) अणु
			prपूर्णांकk(KERN_WARNING
			       "%s l2 D-channel frame wrong EA0/EA1\n",
			       mISDNDevName4ch(&l2->ch));
			वापस ret;
		पूर्ण
		psapi >>= 2;
		ptei >>= 1;
		अगर (psapi != l2->sapi) अणु
			/* not our business */
			अगर (*debug & DEBUG_L2)
				prपूर्णांकk(KERN_DEBUG "%s: sapi %d/%d mismatch\n",
				       mISDNDevName4ch(&l2->ch), psapi,
				       l2->sapi);
			dev_kमुक्त_skb(skb);
			वापस 0;
		पूर्ण
		अगर ((ptei != l2->tei) && (ptei != GROUP_TEI)) अणु
			/* not our business */
			अगर (*debug & DEBUG_L2)
				prपूर्णांकk(KERN_DEBUG "%s: tei %d/%d mismatch\n",
				       mISDNDevName4ch(&l2->ch), ptei, l2->tei);
			dev_kमुक्त_skb(skb);
			वापस 0;
		पूर्ण
	पूर्ण अन्यथा
		datap += l;
	अगर (!(*datap & 1)) अणु	/* I-Frame */
		c = अगरrame_error(l2, skb);
		अगर (!c)
			ret = mISDN_FsmEvent(&l2->l2m, EV_L2_I, skb);
	पूर्ण अन्यथा अगर (IsSFrame(datap, l2)) अणु	/* S-Frame */
		c = super_error(l2, skb);
		अगर (!c)
			ret = mISDN_FsmEvent(&l2->l2m, EV_L2_SUPER, skb);
	पूर्ण अन्यथा अगर (IsUI(datap)) अणु
		c = UI_error(l2, skb);
		अगर (!c)
			ret = mISDN_FsmEvent(&l2->l2m, EV_L2_UI, skb);
	पूर्ण अन्यथा अगर (IsSABME(datap, l2)) अणु
		c = unnum_error(l2, skb, CMD);
		अगर (!c)
			ret = mISDN_FsmEvent(&l2->l2m, EV_L2_SABME, skb);
	पूर्ण अन्यथा अगर (IsUA(datap)) अणु
		c = unnum_error(l2, skb, RSP);
		अगर (!c)
			ret = mISDN_FsmEvent(&l2->l2m, EV_L2_UA, skb);
	पूर्ण अन्यथा अगर (IsDISC(datap)) अणु
		c = unnum_error(l2, skb, CMD);
		अगर (!c)
			ret = mISDN_FsmEvent(&l2->l2m, EV_L2_DISC, skb);
	पूर्ण अन्यथा अगर (IsDM(datap)) अणु
		c = unnum_error(l2, skb, RSP);
		अगर (!c)
			ret = mISDN_FsmEvent(&l2->l2m, EV_L2_DM, skb);
	पूर्ण अन्यथा अगर (IsFRMR(datap)) अणु
		c = FRMR_error(l2, skb);
		अगर (!c)
			ret = mISDN_FsmEvent(&l2->l2m, EV_L2_FRMR, skb);
	पूर्ण अन्यथा
		c = 'L';
	अगर (c) अणु
		prपूर्णांकk(KERN_WARNING "%s:l2 D-channel frame error %c\n",
		       mISDNDevName4ch(&l2->ch), c);
		mISDN_FsmEvent(&l2->l2m, EV_L2_FRAME_ERROR, (व्योम *)(दीर्घ)c);
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक
l2_send(काष्ठा mISDNchannel *ch, काष्ठा sk_buff *skb)
अणु
	काष्ठा layer2		*l2 = container_of(ch, काष्ठा layer2, ch);
	काष्ठा mISDNhead	*hh =  mISDN_HEAD_P(skb);
	पूर्णांक			ret = -EINVAL;

	अगर (*debug & DEBUG_L2_RECV)
		prपूर्णांकk(KERN_DEBUG "%s: %s prim(%x) id(%x) sapi(%d) tei(%d)\n",
		       __func__, mISDNDevName4ch(&l2->ch), hh->prim, hh->id,
		       l2->sapi, l2->tei);
	अगर (hh->prim == DL_INTERN_MSG) अणु
		काष्ठा mISDNhead *chh = hh + 1; /* saved copy */

		*hh = *chh;
		अगर (*debug & DEBUG_L2_RECV)
			prपूर्णांकk(KERN_DEBUG "%s: prim(%x) id(%x) internal msg\n",
				mISDNDevName4ch(&l2->ch), hh->prim, hh->id);
	पूर्ण
	चयन (hh->prim) अणु
	हाल PH_DATA_IND:
		ret = ph_data_indication(l2, hh, skb);
		अवरोध;
	हाल PH_DATA_CNF:
		ret = ph_data_confirm(l2, hh, skb);
		अवरोध;
	हाल PH_ACTIVATE_IND:
		test_and_set_bit(FLG_L1_ACTIV, &l2->flag);
		l2up_create(l2, MPH_ACTIVATE_IND, 0, शून्य);
		अगर (test_and_clear_bit(FLG_ESTAB_PEND, &l2->flag))
			ret = mISDN_FsmEvent(&l2->l2m,
					     EV_L2_DL_ESTABLISH_REQ, skb);
		अवरोध;
	हाल PH_DEACTIVATE_IND:
		test_and_clear_bit(FLG_L1_ACTIV, &l2->flag);
		l2up_create(l2, MPH_DEACTIVATE_IND, 0, शून्य);
		ret = mISDN_FsmEvent(&l2->l2m, EV_L1_DEACTIVATE, skb);
		अवरोध;
	हाल MPH_INFORMATION_IND:
		अगर (!l2->up)
			अवरोध;
		ret = l2->up->send(l2->up, skb);
		अवरोध;
	हाल DL_DATA_REQ:
		ret = mISDN_FsmEvent(&l2->l2m, EV_L2_DL_DATA, skb);
		अवरोध;
	हाल DL_UNITDATA_REQ:
		ret = mISDN_FsmEvent(&l2->l2m, EV_L2_DL_UNITDATA, skb);
		अवरोध;
	हाल DL_ESTABLISH_REQ:
		अगर (test_bit(FLG_LAPB, &l2->flag))
			test_and_set_bit(FLG_ORIG, &l2->flag);
		अगर (test_bit(FLG_L1_ACTIV, &l2->flag)) अणु
			अगर (test_bit(FLG_LAPD, &l2->flag) ||
			    test_bit(FLG_ORIG, &l2->flag))
				ret = mISDN_FsmEvent(&l2->l2m,
						     EV_L2_DL_ESTABLISH_REQ, skb);
		पूर्ण अन्यथा अणु
			अगर (test_bit(FLG_LAPD, &l2->flag) ||
			    test_bit(FLG_ORIG, &l2->flag)) अणु
				test_and_set_bit(FLG_ESTAB_PEND,
						 &l2->flag);
			पूर्ण
			ret = l2करोwn(l2, PH_ACTIVATE_REQ, l2_newid(l2),
				     skb);
		पूर्ण
		अवरोध;
	हाल DL_RELEASE_REQ:
		अगर (test_bit(FLG_LAPB, &l2->flag))
			l2करोwn_create(l2, PH_DEACTIVATE_REQ,
				      l2_newid(l2), 0, शून्य);
		ret = mISDN_FsmEvent(&l2->l2m, EV_L2_DL_RELEASE_REQ,
				     skb);
		अवरोध;
	हाल DL_TIMER200_IND:
		mISDN_FsmEvent(&l2->l2m, EV_L2_T200I, शून्य);
		अवरोध;
	हाल DL_TIMER203_IND:
		mISDN_FsmEvent(&l2->l2m, EV_L2_T203I, शून्य);
		अवरोध;
	शेष:
		अगर (*debug & DEBUG_L2)
			l2m_debug(&l2->l2m, "l2 unknown pr %04x",
				  hh->prim);
	पूर्ण
	अगर (ret) अणु
		dev_kमुक्त_skb(skb);
		ret = 0;
	पूर्ण
	वापस ret;
पूर्ण

पूर्णांक
tei_l2(काष्ठा layer2 *l2, u_पूर्णांक cmd, u_दीर्घ arg)
अणु
	पूर्णांक		ret = -EINVAL;

	अगर (*debug & DEBUG_L2_TEI)
		prपूर्णांकk(KERN_DEBUG "%s: cmd(%x) in %s\n",
		       mISDNDevName4ch(&l2->ch), cmd, __func__);
	चयन (cmd) अणु
	हाल (MDL_ASSIGN_REQ):
		ret = mISDN_FsmEvent(&l2->l2m, EV_L2_MDL_ASSIGN, (व्योम *)arg);
		अवरोध;
	हाल (MDL_REMOVE_REQ):
		ret = mISDN_FsmEvent(&l2->l2m, EV_L2_MDL_REMOVE, शून्य);
		अवरोध;
	हाल (MDL_ERROR_IND):
		ret = mISDN_FsmEvent(&l2->l2m, EV_L2_MDL_ERROR, शून्य);
		अवरोध;
	हाल (MDL_ERROR_RSP):
		/* ETS 300-125 5.3.2.1 Test: TC13010 */
		prपूर्णांकk(KERN_NOTICE "%s: MDL_ERROR|REQ (tei_l2)\n",
		       mISDNDevName4ch(&l2->ch));
		ret = mISDN_FsmEvent(&l2->l2m, EV_L2_MDL_ERROR, शून्य);
		अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

अटल व्योम
release_l2(काष्ठा layer2 *l2)
अणु
	mISDN_FsmDelTimer(&l2->t200, 21);
	mISDN_FsmDelTimer(&l2->t203, 16);
	skb_queue_purge(&l2->i_queue);
	skb_queue_purge(&l2->ui_queue);
	skb_queue_purge(&l2->करोwn_queue);
	ReleaseWin(l2);
	अगर (test_bit(FLG_LAPD, &l2->flag)) अणु
		TEIrelease(l2);
		अगर (l2->ch.st)
			l2->ch.st->dev->D.ctrl(&l2->ch.st->dev->D,
					       CLOSE_CHANNEL, शून्य);
	पूर्ण
	kमुक्त(l2);
पूर्ण

अटल पूर्णांक
l2_ctrl(काष्ठा mISDNchannel *ch, u_पूर्णांक cmd, व्योम *arg)
अणु
	काष्ठा layer2		*l2 = container_of(ch, काष्ठा layer2, ch);
	u_पूर्णांक			info;

	अगर (*debug & DEBUG_L2_CTRL)
		prपूर्णांकk(KERN_DEBUG "%s: %s cmd(%x)\n",
		       mISDNDevName4ch(ch), __func__, cmd);

	चयन (cmd) अणु
	हाल OPEN_CHANNEL:
		अगर (test_bit(FLG_LAPD, &l2->flag)) अणु
			set_channel_address(&l2->ch, l2->sapi, l2->tei);
			info = DL_INFO_L2_CONNECT;
			l2up_create(l2, DL_INFORMATION_IND,
				    माप(info), &info);
		पूर्ण
		अवरोध;
	हाल CLOSE_CHANNEL:
		अगर (l2->ch.peer)
			l2->ch.peer->ctrl(l2->ch.peer, CLOSE_CHANNEL, शून्य);
		release_l2(l2);
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

काष्ठा layer2 *
create_l2(काष्ठा mISDNchannel *ch, u_पूर्णांक protocol, u_दीर्घ options, पूर्णांक tei,
	  पूर्णांक sapi)
अणु
	काष्ठा layer2		*l2;
	काष्ठा channel_req	rq;

	l2 = kzalloc(माप(काष्ठा layer2), GFP_KERNEL);
	अगर (!l2) अणु
		prपूर्णांकk(KERN_ERR "kzalloc layer2 failed\n");
		वापस शून्य;
	पूर्ण
	l2->next_id = 1;
	l2->करोwn_id = MISDN_ID_NONE;
	l2->up = ch;
	l2->ch.st = ch->st;
	l2->ch.send = l2_send;
	l2->ch.ctrl = l2_ctrl;
	चयन (protocol) अणु
	हाल ISDN_P_LAPD_NT:
		test_and_set_bit(FLG_LAPD, &l2->flag);
		test_and_set_bit(FLG_LAPD_NET, &l2->flag);
		test_and_set_bit(FLG_MOD128, &l2->flag);
		l2->sapi = sapi;
		l2->maxlen = MAX_DFRAME_LEN;
		अगर (test_bit(OPTION_L2_PMX, &options))
			l2->winकरोw = 7;
		अन्यथा
			l2->winकरोw = 1;
		अगर (test_bit(OPTION_L2_PTP, &options))
			test_and_set_bit(FLG_PTP, &l2->flag);
		अगर (test_bit(OPTION_L2_FIXEDTEI, &options))
			test_and_set_bit(FLG_FIXED_TEI, &l2->flag);
		l2->tei = tei;
		l2->T200 = 1000;
		l2->N200 = 3;
		l2->T203 = 10000;
		अगर (test_bit(OPTION_L2_PMX, &options))
			rq.protocol = ISDN_P_NT_E1;
		अन्यथा
			rq.protocol = ISDN_P_NT_S0;
		rq.adr.channel = 0;
		l2->ch.st->dev->D.ctrl(&l2->ch.st->dev->D, OPEN_CHANNEL, &rq);
		अवरोध;
	हाल ISDN_P_LAPD_TE:
		test_and_set_bit(FLG_LAPD, &l2->flag);
		test_and_set_bit(FLG_MOD128, &l2->flag);
		test_and_set_bit(FLG_ORIG, &l2->flag);
		l2->sapi = sapi;
		l2->maxlen = MAX_DFRAME_LEN;
		अगर (test_bit(OPTION_L2_PMX, &options))
			l2->winकरोw = 7;
		अन्यथा
			l2->winकरोw = 1;
		अगर (test_bit(OPTION_L2_PTP, &options))
			test_and_set_bit(FLG_PTP, &l2->flag);
		अगर (test_bit(OPTION_L2_FIXEDTEI, &options))
			test_and_set_bit(FLG_FIXED_TEI, &l2->flag);
		l2->tei = tei;
		l2->T200 = 1000;
		l2->N200 = 3;
		l2->T203 = 10000;
		अगर (test_bit(OPTION_L2_PMX, &options))
			rq.protocol = ISDN_P_TE_E1;
		अन्यथा
			rq.protocol = ISDN_P_TE_S0;
		rq.adr.channel = 0;
		l2->ch.st->dev->D.ctrl(&l2->ch.st->dev->D, OPEN_CHANNEL, &rq);
		अवरोध;
	हाल ISDN_P_B_X75SLP:
		test_and_set_bit(FLG_LAPB, &l2->flag);
		l2->winकरोw = 7;
		l2->maxlen = MAX_DATA_SIZE;
		l2->T200 = 1000;
		l2->N200 = 4;
		l2->T203 = 5000;
		l2->addr.A = 3;
		l2->addr.B = 1;
		अवरोध;
	शेष:
		prपूर्णांकk(KERN_ERR "layer2 create failed prt %x\n",
		       protocol);
		kमुक्त(l2);
		वापस शून्य;
	पूर्ण
	skb_queue_head_init(&l2->i_queue);
	skb_queue_head_init(&l2->ui_queue);
	skb_queue_head_init(&l2->करोwn_queue);
	skb_queue_head_init(&l2->पंचांगp_queue);
	InitWin(l2);
	l2->l2m.fsm = &l2fsm;
	अगर (test_bit(FLG_LAPB, &l2->flag) ||
	    test_bit(FLG_FIXED_TEI, &l2->flag) ||
	    test_bit(FLG_LAPD_NET, &l2->flag))
		l2->l2m.state = ST_L2_4;
	अन्यथा
		l2->l2m.state = ST_L2_1;
	l2->l2m.debug = *debug;
	l2->l2m.userdata = l2;
	l2->l2m.userपूर्णांक = 0;
	l2->l2m.prपूर्णांकdebug = l2m_debug;

	mISDN_FsmInitTimer(&l2->l2m, &l2->t200);
	mISDN_FsmInitTimer(&l2->l2m, &l2->t203);
	वापस l2;
पूर्ण

अटल पूर्णांक
x75create(काष्ठा channel_req *crq)
अणु
	काष्ठा layer2	*l2;

	अगर (crq->protocol != ISDN_P_B_X75SLP)
		वापस -EPROTONOSUPPORT;
	l2 = create_l2(crq->ch, crq->protocol, 0, 0, 0);
	अगर (!l2)
		वापस -ENOMEM;
	crq->ch = &l2->ch;
	crq->protocol = ISDN_P_B_HDLC;
	वापस 0;
पूर्ण

अटल काष्ठा Bprotocol X75SLP = अणु
	.Bprotocols = (1 << (ISDN_P_B_X75SLP & ISDN_P_B_MASK)),
	.name = "X75SLP",
	.create = x75create
पूर्ण;

पूर्णांक
Isdnl2_Init(u_पूर्णांक *deb)
अणु
	पूर्णांक res;
	debug = deb;
	mISDN_रेजिस्टर_Bprotocol(&X75SLP);
	l2fsm.state_count = L2_STATE_COUNT;
	l2fsm.event_count = L2_EVENT_COUNT;
	l2fsm.strEvent = strL2Event;
	l2fsm.strState = strL2State;
	res = mISDN_FsmNew(&l2fsm, L2FnList, ARRAY_SIZE(L2FnList));
	अगर (res)
		जाओ error;
	res = TEIInit(deb);
	अगर (res)
		जाओ error_fsm;
	वापस 0;

error_fsm:
	mISDN_FsmFree(&l2fsm);
error:
	mISDN_unरेजिस्टर_Bprotocol(&X75SLP);
	वापस res;
पूर्ण

व्योम
Isdnl2_cleanup(व्योम)
अणु
	mISDN_unरेजिस्टर_Bprotocol(&X75SLP);
	TEIFree();
	mISDN_FsmFree(&l2fsm);
पूर्ण
