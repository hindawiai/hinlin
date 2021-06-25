<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *
 * Author	Karsten Keil <kkeil@novell.com>
 *
 * Copyright 2008  by Karsten Keil <kkeil@novell.com>
 */
#समावेश "layer2.h"
#समावेश <linux/अक्रमom.h>
#समावेश <linux/slab.h>
#समावेश "core.h"

#घोषणा ID_REQUEST	1
#घोषणा ID_ASSIGNED	2
#घोषणा ID_DENIED	3
#घोषणा ID_CHK_REQ	4
#घोषणा ID_CHK_RES	5
#घोषणा ID_REMOVE	6
#घोषणा ID_VERIFY	7

#घोषणा TEI_ENTITY_ID	0xf

#घोषणा MGR_PH_ACTIVE	16
#घोषणा MGR_PH_NOTREADY	17

#घोषणा DATIMER_VAL	10000

अटल	u_पूर्णांक	*debug;

अटल काष्ठा Fsm deactfsm = अणुशून्य, 0, 0, शून्य, शून्यपूर्ण;
अटल काष्ठा Fsm teअगरsmu = अणुशून्य, 0, 0, शून्य, शून्यपूर्ण;
अटल काष्ठा Fsm teअगरsmn = अणुशून्य, 0, 0, शून्य, शून्यपूर्ण;

क्रमागत अणु
	ST_L1_DEACT,
	ST_L1_DEACT_PENDING,
	ST_L1_ACTIV,
पूर्ण;
#घोषणा DEACT_STATE_COUNT (ST_L1_ACTIV + 1)

अटल अक्षर *strDeactState[] =
अणु
	"ST_L1_DEACT",
	"ST_L1_DEACT_PENDING",
	"ST_L1_ACTIV",
पूर्ण;

क्रमागत अणु
	EV_ACTIVATE,
	EV_ACTIVATE_IND,
	EV_DEACTIVATE,
	EV_DEACTIVATE_IND,
	EV_UI,
	EV_DATIMER,
पूर्ण;

#घोषणा DEACT_EVENT_COUNT (EV_DATIMER + 1)

अटल अक्षर *strDeactEvent[] =
अणु
	"EV_ACTIVATE",
	"EV_ACTIVATE_IND",
	"EV_DEACTIVATE",
	"EV_DEACTIVATE_IND",
	"EV_UI",
	"EV_DATIMER",
पूर्ण;

अटल व्योम
da_debug(काष्ठा FsmInst *fi, अक्षर *fmt, ...)
अणु
	काष्ठा manager	*mgr = fi->userdata;
	काष्ठा va_क्रमmat vaf;
	बहु_सूची va;

	अगर (!(*debug & DEBUG_L2_TEIFSM))
		वापस;

	बहु_शुरू(va, fmt);

	vaf.fmt = fmt;
	vaf.va = &va;

	prपूर्णांकk(KERN_DEBUG "mgr(%d): %pV\n", mgr->ch.st->dev->id, &vaf);

	बहु_पूर्ण(va);
पूर्ण

अटल व्योम
da_activate(काष्ठा FsmInst *fi, पूर्णांक event, व्योम *arg)
अणु
	काष्ठा manager	*mgr = fi->userdata;

	अगर (fi->state == ST_L1_DEACT_PENDING)
		mISDN_FsmDelTimer(&mgr->daसमयr, 1);
	mISDN_FsmChangeState(fi, ST_L1_ACTIV);
पूर्ण

अटल व्योम
da_deactivate_ind(काष्ठा FsmInst *fi, पूर्णांक event, व्योम *arg)
अणु
	mISDN_FsmChangeState(fi, ST_L1_DEACT);
पूर्ण

अटल व्योम
da_deactivate(काष्ठा FsmInst *fi, पूर्णांक event, व्योम *arg)
अणु
	काष्ठा manager	*mgr = fi->userdata;
	काष्ठा layer2	*l2;
	u_दीर्घ		flags;

	पढ़ो_lock_irqsave(&mgr->lock, flags);
	list_क्रम_each_entry(l2, &mgr->layer2, list) अणु
		अगर (l2->l2m.state > ST_L2_4) अणु
			/* have still activ TEI */
			पढ़ो_unlock_irqrestore(&mgr->lock, flags);
			वापस;
		पूर्ण
	पूर्ण
	पढ़ो_unlock_irqrestore(&mgr->lock, flags);
	/* All TEI are inactiv */
	अगर (!test_bit(OPTION_L1_HOLD, &mgr->options)) अणु
		mISDN_FsmAddTimer(&mgr->daसमयr, DATIMER_VAL, EV_DATIMER,
				  शून्य, 1);
		mISDN_FsmChangeState(fi, ST_L1_DEACT_PENDING);
	पूर्ण
पूर्ण

अटल व्योम
da_ui(काष्ठा FsmInst *fi, पूर्णांक event, व्योम *arg)
अणु
	काष्ठा manager	*mgr = fi->userdata;

	/* restart da समयr */
	अगर (!test_bit(OPTION_L1_HOLD, &mgr->options)) अणु
		mISDN_FsmDelTimer(&mgr->daसमयr, 2);
		mISDN_FsmAddTimer(&mgr->daसमयr, DATIMER_VAL, EV_DATIMER,
				  शून्य, 2);
	पूर्ण
पूर्ण

अटल व्योम
da_समयr(काष्ठा FsmInst *fi, पूर्णांक event, व्योम *arg)
अणु
	काष्ठा manager	*mgr = fi->userdata;
	काष्ठा layer2	*l2;
	u_दीर्घ		flags;

	/* check again */
	पढ़ो_lock_irqsave(&mgr->lock, flags);
	list_क्रम_each_entry(l2, &mgr->layer2, list) अणु
		अगर (l2->l2m.state > ST_L2_4) अणु
			/* have still activ TEI */
			पढ़ो_unlock_irqrestore(&mgr->lock, flags);
			mISDN_FsmChangeState(fi, ST_L1_ACTIV);
			वापस;
		पूर्ण
	पूर्ण
	पढ़ो_unlock_irqrestore(&mgr->lock, flags);
	/* All TEI are inactiv */
	mISDN_FsmChangeState(fi, ST_L1_DEACT);
	_queue_data(&mgr->ch, PH_DEACTIVATE_REQ, MISDN_ID_ANY, 0, शून्य,
		    GFP_ATOMIC);
पूर्ण

अटल काष्ठा FsmNode DeactFnList[] =
अणु
	अणुST_L1_DEACT, EV_ACTIVATE_IND, da_activateपूर्ण,
	अणुST_L1_ACTIV, EV_DEACTIVATE_IND, da_deactivate_indपूर्ण,
	अणुST_L1_ACTIV, EV_DEACTIVATE, da_deactivateपूर्ण,
	अणुST_L1_DEACT_PENDING, EV_ACTIVATE, da_activateपूर्ण,
	अणुST_L1_DEACT_PENDING, EV_UI, da_uiपूर्ण,
	अणुST_L1_DEACT_PENDING, EV_DATIMER, da_समयrपूर्ण,
पूर्ण;

क्रमागत अणु
	ST_TEI_NOP,
	ST_TEI_IDREQ,
	ST_TEI_IDVERIFY,
पूर्ण;

#घोषणा TEI_STATE_COUNT (ST_TEI_IDVERIFY + 1)

अटल अक्षर *strTeiState[] =
अणु
	"ST_TEI_NOP",
	"ST_TEI_IDREQ",
	"ST_TEI_IDVERIFY",
पूर्ण;

क्रमागत अणु
	EV_IDREQ,
	EV_ASSIGN,
	EV_ASSIGN_REQ,
	EV_DENIED,
	EV_CHKREQ,
	EV_CHKRESP,
	EV_REMOVE,
	EV_VERIFY,
	EV_TIMER,
पूर्ण;

#घोषणा TEI_EVENT_COUNT (EV_TIMER + 1)

अटल अक्षर *strTeiEvent[] =
अणु
	"EV_IDREQ",
	"EV_ASSIGN",
	"EV_ASSIGN_REQ",
	"EV_DENIED",
	"EV_CHKREQ",
	"EV_CHKRESP",
	"EV_REMOVE",
	"EV_VERIFY",
	"EV_TIMER",
पूर्ण;

अटल व्योम
tei_debug(काष्ठा FsmInst *fi, अक्षर *fmt, ...)
अणु
	काष्ठा teimgr	*पंचांग = fi->userdata;
	काष्ठा va_क्रमmat vaf;
	बहु_सूची va;

	अगर (!(*debug & DEBUG_L2_TEIFSM))
		वापस;

	बहु_शुरू(va, fmt);

	vaf.fmt = fmt;
	vaf.va = &va;

	prपूर्णांकk(KERN_DEBUG "sapi(%d) tei(%d): %pV\n",
	       पंचांग->l2->sapi, पंचांग->l2->tei, &vaf);

	बहु_पूर्ण(va);
पूर्ण



अटल पूर्णांक
get_मुक्त_id(काष्ठा manager *mgr)
अणु
	DECLARE_BITMAP(ids, 64) = अणु [0 ... BITS_TO_LONGS(64) - 1] = 0 पूर्ण;
	पूर्णांक		i;
	काष्ठा layer2	*l2;

	list_क्रम_each_entry(l2, &mgr->layer2, list) अणु
		अगर (l2->ch.nr > 63) अणु
			prपूर्णांकk(KERN_WARNING
			       "%s: more as 63 layer2 for one device\n",
			       __func__);
			वापस -EBUSY;
		पूर्ण
		__set_bit(l2->ch.nr, ids);
	पूर्ण
	i = find_next_zero_bit(ids, 64, 1);
	अगर (i < 64)
		वापस i;
	prपूर्णांकk(KERN_WARNING "%s: more as 63 layer2 for one device\n",
	       __func__);
	वापस -EBUSY;
पूर्ण

अटल पूर्णांक
get_मुक्त_tei(काष्ठा manager *mgr)
अणु
	DECLARE_BITMAP(ids, 64) = अणु [0 ... BITS_TO_LONGS(64) - 1] = 0 पूर्ण;
	पूर्णांक		i;
	काष्ठा layer2	*l2;

	list_क्रम_each_entry(l2, &mgr->layer2, list) अणु
		अगर (l2->ch.nr == 0)
			जारी;
		अगर ((l2->ch.addr & 0xff) != 0)
			जारी;
		i = l2->ch.addr >> 8;
		अगर (i < 64)
			जारी;
		i -= 64;

		__set_bit(i, ids);
	पूर्ण
	i = find_first_zero_bit(ids, 64);
	अगर (i < 64)
		वापस i + 64;
	prपूर्णांकk(KERN_WARNING "%s: more as 63 dynamic tei for one device\n",
	       __func__);
	वापस -1;
पूर्ण

अटल व्योम
teiup_create(काष्ठा manager *mgr, u_पूर्णांक prim, पूर्णांक len, व्योम *arg)
अणु
	काष्ठा sk_buff	*skb;
	काष्ठा mISDNhead *hh;
	पूर्णांक		err;

	skb = mI_alloc_skb(len, GFP_ATOMIC);
	अगर (!skb)
		वापस;
	hh = mISDN_HEAD_P(skb);
	hh->prim = prim;
	hh->id = (mgr->ch.nr << 16) | mgr->ch.addr;
	अगर (len)
		skb_put_data(skb, arg, len);
	err = mgr->up->send(mgr->up, skb);
	अगर (err) अणु
		prपूर्णांकk(KERN_WARNING "%s: err=%d\n", __func__, err);
		dev_kमुक्त_skb(skb);
	पूर्ण
पूर्ण

अटल u_पूर्णांक
new_id(काष्ठा manager *mgr)
अणु
	u_पूर्णांक	id;

	id = mgr->nextid++;
	अगर (id == 0x7fff)
		mgr->nextid = 1;
	id <<= 16;
	id |= GROUP_TEI << 8;
	id |= TEI_SAPI;
	वापस id;
पूर्ण

अटल व्योम
करो_send(काष्ठा manager *mgr)
अणु
	अगर (!test_bit(MGR_PH_ACTIVE, &mgr->options))
		वापस;

	अगर (!test_and_set_bit(MGR_PH_NOTREADY, &mgr->options)) अणु
		काष्ठा sk_buff	*skb = skb_dequeue(&mgr->sendq);

		अगर (!skb) अणु
			test_and_clear_bit(MGR_PH_NOTREADY, &mgr->options);
			वापस;
		पूर्ण
		mgr->lastid = mISDN_HEAD_ID(skb);
		mISDN_FsmEvent(&mgr->deact, EV_UI, शून्य);
		अगर (mgr->ch.recv(mgr->ch.peer, skb)) अणु
			dev_kमुक्त_skb(skb);
			test_and_clear_bit(MGR_PH_NOTREADY, &mgr->options);
			mgr->lastid = MISDN_ID_NONE;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम
करो_ack(काष्ठा manager *mgr, u_पूर्णांक id)
अणु
	अगर (test_bit(MGR_PH_NOTREADY, &mgr->options)) अणु
		अगर (id == mgr->lastid) अणु
			अगर (test_bit(MGR_PH_ACTIVE, &mgr->options)) अणु
				काष्ठा sk_buff	*skb;

				skb = skb_dequeue(&mgr->sendq);
				अगर (skb) अणु
					mgr->lastid = mISDN_HEAD_ID(skb);
					अगर (!mgr->ch.recv(mgr->ch.peer, skb))
						वापस;
					dev_kमुक्त_skb(skb);
				पूर्ण
			पूर्ण
			mgr->lastid = MISDN_ID_NONE;
			test_and_clear_bit(MGR_PH_NOTREADY, &mgr->options);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम
mgr_send_करोwn(काष्ठा manager *mgr, काष्ठा sk_buff *skb)
अणु
	skb_queue_tail(&mgr->sendq, skb);
	अगर (!test_bit(MGR_PH_ACTIVE, &mgr->options)) अणु
		_queue_data(&mgr->ch, PH_ACTIVATE_REQ, MISDN_ID_ANY, 0,
			    शून्य, GFP_KERNEL);
	पूर्ण अन्यथा अणु
		करो_send(mgr);
	पूर्ण
पूर्ण

अटल पूर्णांक
dl_unit_data(काष्ठा manager *mgr, काष्ठा sk_buff *skb)
अणु
	अगर (!test_bit(MGR_OPT_NETWORK, &mgr->options)) /* only net send UI */
		वापस -EINVAL;
	अगर (!test_bit(MGR_PH_ACTIVE, &mgr->options))
		_queue_data(&mgr->ch, PH_ACTIVATE_REQ, MISDN_ID_ANY, 0,
			    शून्य, GFP_KERNEL);
	skb_push(skb, 3);
	skb->data[0] = 0x02; /* SAPI 0 C/R = 1 */
	skb->data[1] = 0xff; /* TEI 127 */
	skb->data[2] = UI;   /* UI frame */
	mISDN_HEAD_PRIM(skb) = PH_DATA_REQ;
	mISDN_HEAD_ID(skb) = new_id(mgr);
	skb_queue_tail(&mgr->sendq, skb);
	करो_send(mgr);
	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक
अक्रमom_ri(व्योम)
अणु
	u16 x;

	get_अक्रमom_bytes(&x, माप(x));
	वापस x;
पूर्ण

अटल काष्ठा layer2 *
findtei(काष्ठा manager *mgr, पूर्णांक tei)
अणु
	काष्ठा layer2	*l2;
	u_दीर्घ		flags;

	पढ़ो_lock_irqsave(&mgr->lock, flags);
	list_क्रम_each_entry(l2, &mgr->layer2, list) अणु
		अगर ((l2->sapi == 0) && (l2->tei > 0) &&
		    (l2->tei != GROUP_TEI) && (l2->tei == tei))
			जाओ करोne;
	पूर्ण
	l2 = शून्य;
करोne:
	पढ़ो_unlock_irqrestore(&mgr->lock, flags);
	वापस l2;
पूर्ण

अटल व्योम
put_tei_msg(काष्ठा manager *mgr, u_अक्षर m_id, अचिन्हित पूर्णांक ri, पूर्णांक tei)
अणु
	काष्ठा sk_buff *skb;
	u_अक्षर bp[8];

	bp[0] = (TEI_SAPI << 2);
	अगर (test_bit(MGR_OPT_NETWORK, &mgr->options))
		bp[0] |= 2; /* CR:=1 क्रम net command */
	bp[1] = (GROUP_TEI << 1) | 0x1;
	bp[2] = UI;
	bp[3] = TEI_ENTITY_ID;
	bp[4] = ri >> 8;
	bp[5] = ri & 0xff;
	bp[6] = m_id;
	bp[7] = ((tei << 1) & 0xff) | 1;
	skb = _alloc_mISDN_skb(PH_DATA_REQ, new_id(mgr), 8, bp, GFP_ATOMIC);
	अगर (!skb) अणु
		prपूर्णांकk(KERN_WARNING "%s: no skb for tei msg\n", __func__);
		वापस;
	पूर्ण
	mgr_send_करोwn(mgr, skb);
पूर्ण

अटल व्योम
tei_id_request(काष्ठा FsmInst *fi, पूर्णांक event, व्योम *arg)
अणु
	काष्ठा teimgr *पंचांग = fi->userdata;

	अगर (पंचांग->l2->tei != GROUP_TEI) अणु
		पंचांग->tei_m.prपूर्णांकdebug(&पंचांग->tei_m,
				     "assign request for already assigned tei %d",
				     पंचांग->l2->tei);
		वापस;
	पूर्ण
	पंचांग->ri = अक्रमom_ri();
	अगर (*debug & DEBUG_L2_TEI)
		पंचांग->tei_m.prपूर्णांकdebug(&पंचांग->tei_m,
				     "assign request ri %d", पंचांग->ri);
	put_tei_msg(पंचांग->mgr, ID_REQUEST, पंचांग->ri, GROUP_TEI);
	mISDN_FsmChangeState(fi, ST_TEI_IDREQ);
	mISDN_FsmAddTimer(&पंचांग->समयr, पंचांग->tval, EV_TIMER, शून्य, 1);
	पंचांग->nval = 3;
पूर्ण

अटल व्योम
tei_id_assign(काष्ठा FsmInst *fi, पूर्णांक event, व्योम *arg)
अणु
	काष्ठा teimgr	*पंचांग = fi->userdata;
	काष्ठा layer2	*l2;
	u_अक्षर *dp = arg;
	पूर्णांक ri, tei;

	ri = ((अचिन्हित पूर्णांक) *dp++ << 8);
	ri += *dp++;
	dp++;
	tei = *dp >> 1;
	अगर (*debug & DEBUG_L2_TEI)
		पंचांग->tei_m.prपूर्णांकdebug(fi, "identity assign ri %d tei %d",
				     ri, tei);
	l2 = findtei(पंचांग->mgr, tei);
	अगर (l2) अणु	/* same tei is in use */
		अगर (ri != l2->पंचांग->ri) अणु
			पंचांग->tei_m.prपूर्णांकdebug(fi,
					     "possible duplicate assignment tei %d", tei);
			tei_l2(l2, MDL_ERROR_RSP, 0);
		पूर्ण
	पूर्ण अन्यथा अगर (ri == पंचांग->ri) अणु
		mISDN_FsmDelTimer(&पंचांग->समयr, 1);
		mISDN_FsmChangeState(fi, ST_TEI_NOP);
		tei_l2(पंचांग->l2, MDL_ASSIGN_REQ, tei);
	पूर्ण
पूर्ण

अटल व्योम
tei_id_test_dup(काष्ठा FsmInst *fi, पूर्णांक event, व्योम *arg)
अणु
	काष्ठा teimgr	*पंचांग = fi->userdata;
	काष्ठा layer2	*l2;
	u_अक्षर *dp = arg;
	पूर्णांक tei, ri;

	ri = ((अचिन्हित पूर्णांक) *dp++ << 8);
	ri += *dp++;
	dp++;
	tei = *dp >> 1;
	अगर (*debug & DEBUG_L2_TEI)
		पंचांग->tei_m.prपूर्णांकdebug(fi, "foreign identity assign ri %d tei %d",
				     ri, tei);
	l2 = findtei(पंचांग->mgr, tei);
	अगर (l2) अणु	/* same tei is in use */
		अगर (ri != l2->पंचांग->ri) अणु	/* and it wasn't our request */
			पंचांग->tei_m.prपूर्णांकdebug(fi,
					     "possible duplicate assignment tei %d", tei);
			mISDN_FsmEvent(&l2->पंचांग->tei_m, EV_VERIFY, शून्य);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम
tei_id_denied(काष्ठा FsmInst *fi, पूर्णांक event, व्योम *arg)
अणु
	काष्ठा teimgr *पंचांग = fi->userdata;
	u_अक्षर *dp = arg;
	पूर्णांक ri, tei;

	ri = ((अचिन्हित पूर्णांक) *dp++ << 8);
	ri += *dp++;
	dp++;
	tei = *dp >> 1;
	अगर (*debug & DEBUG_L2_TEI)
		पंचांग->tei_m.prपूर्णांकdebug(fi, "identity denied ri %d tei %d",
				     ri, tei);
पूर्ण

अटल व्योम
tei_id_chk_req(काष्ठा FsmInst *fi, पूर्णांक event, व्योम *arg)
अणु
	काष्ठा teimgr *पंचांग = fi->userdata;
	u_अक्षर *dp = arg;
	पूर्णांक tei;

	tei = *(dp + 3) >> 1;
	अगर (*debug & DEBUG_L2_TEI)
		पंचांग->tei_m.prपूर्णांकdebug(fi, "identity check req tei %d", tei);
	अगर ((पंचांग->l2->tei != GROUP_TEI) && ((tei == GROUP_TEI) ||
					   (tei == पंचांग->l2->tei))) अणु
		mISDN_FsmDelTimer(&पंचांग->समयr, 4);
		mISDN_FsmChangeState(&पंचांग->tei_m, ST_TEI_NOP);
		put_tei_msg(पंचांग->mgr, ID_CHK_RES, अक्रमom_ri(), पंचांग->l2->tei);
	पूर्ण
पूर्ण

अटल व्योम
tei_id_हटाओ(काष्ठा FsmInst *fi, पूर्णांक event, व्योम *arg)
अणु
	काष्ठा teimgr *पंचांग = fi->userdata;
	u_अक्षर *dp = arg;
	पूर्णांक tei;

	tei = *(dp + 3) >> 1;
	अगर (*debug & DEBUG_L2_TEI)
		पंचांग->tei_m.prपूर्णांकdebug(fi, "identity remove tei %d", tei);
	अगर ((पंचांग->l2->tei != GROUP_TEI) &&
	    ((tei == GROUP_TEI) || (tei == पंचांग->l2->tei))) अणु
		mISDN_FsmDelTimer(&पंचांग->समयr, 5);
		mISDN_FsmChangeState(&पंचांग->tei_m, ST_TEI_NOP);
		tei_l2(पंचांग->l2, MDL_REMOVE_REQ, 0);
	पूर्ण
पूर्ण

अटल व्योम
tei_id_verअगरy(काष्ठा FsmInst *fi, पूर्णांक event, व्योम *arg)
अणु
	काष्ठा teimgr *पंचांग = fi->userdata;

	अगर (*debug & DEBUG_L2_TEI)
		पंचांग->tei_m.prपूर्णांकdebug(fi, "id verify request for tei %d",
				     पंचांग->l2->tei);
	put_tei_msg(पंचांग->mgr, ID_VERIFY, 0, पंचांग->l2->tei);
	mISDN_FsmChangeState(&पंचांग->tei_m, ST_TEI_IDVERIFY);
	mISDN_FsmAddTimer(&पंचांग->समयr, पंचांग->tval, EV_TIMER, शून्य, 2);
	पंचांग->nval = 2;
पूर्ण

अटल व्योम
tei_id_req_tout(काष्ठा FsmInst *fi, पूर्णांक event, व्योम *arg)
अणु
	काष्ठा teimgr *पंचांग = fi->userdata;

	अगर (--पंचांग->nval) अणु
		पंचांग->ri = अक्रमom_ri();
		अगर (*debug & DEBUG_L2_TEI)
			पंचांग->tei_m.prपूर्णांकdebug(fi, "assign req(%d) ri %d",
					     4 - पंचांग->nval, पंचांग->ri);
		put_tei_msg(पंचांग->mgr, ID_REQUEST, पंचांग->ri, GROUP_TEI);
		mISDN_FsmAddTimer(&पंचांग->समयr, पंचांग->tval, EV_TIMER, शून्य, 3);
	पूर्ण अन्यथा अणु
		पंचांग->tei_m.prपूर्णांकdebug(fi, "assign req failed");
		tei_l2(पंचांग->l2, MDL_ERROR_RSP, 0);
		mISDN_FsmChangeState(fi, ST_TEI_NOP);
	पूर्ण
पूर्ण

अटल व्योम
tei_id_ver_tout(काष्ठा FsmInst *fi, पूर्णांक event, व्योम *arg)
अणु
	काष्ठा teimgr *पंचांग = fi->userdata;

	अगर (--पंचांग->nval) अणु
		अगर (*debug & DEBUG_L2_TEI)
			पंचांग->tei_m.prपूर्णांकdebug(fi,
					     "id verify req(%d) for tei %d",
					     3 - पंचांग->nval, पंचांग->l2->tei);
		put_tei_msg(पंचांग->mgr, ID_VERIFY, 0, पंचांग->l2->tei);
		mISDN_FsmAddTimer(&पंचांग->समयr, पंचांग->tval, EV_TIMER, शून्य, 4);
	पूर्ण अन्यथा अणु
		पंचांग->tei_m.prपूर्णांकdebug(fi, "verify req for tei %d failed",
				     पंचांग->l2->tei);
		tei_l2(पंचांग->l2, MDL_REMOVE_REQ, 0);
		mISDN_FsmChangeState(fi, ST_TEI_NOP);
	पूर्ण
पूर्ण

अटल काष्ठा FsmNode TeiFnListUser[] =
अणु
	अणुST_TEI_NOP, EV_IDREQ, tei_id_requestपूर्ण,
	अणुST_TEI_NOP, EV_ASSIGN, tei_id_test_dupपूर्ण,
	अणुST_TEI_NOP, EV_VERIFY, tei_id_verअगरyपूर्ण,
	अणुST_TEI_NOP, EV_REMOVE, tei_id_हटाओपूर्ण,
	अणुST_TEI_NOP, EV_CHKREQ, tei_id_chk_reqपूर्ण,
	अणुST_TEI_IDREQ, EV_TIMER, tei_id_req_toutपूर्ण,
	अणुST_TEI_IDREQ, EV_ASSIGN, tei_id_assignपूर्ण,
	अणुST_TEI_IDREQ, EV_DENIED, tei_id_deniedपूर्ण,
	अणुST_TEI_IDVERIFY, EV_TIMER, tei_id_ver_toutपूर्ण,
	अणुST_TEI_IDVERIFY, EV_REMOVE, tei_id_हटाओपूर्ण,
	अणुST_TEI_IDVERIFY, EV_CHKREQ, tei_id_chk_reqपूर्ण,
पूर्ण;

अटल व्योम
tei_l2हटाओ(काष्ठा layer2 *l2)
अणु
	put_tei_msg(l2->पंचांग->mgr, ID_REMOVE, 0, l2->tei);
	tei_l2(l2, MDL_REMOVE_REQ, 0);
	list_del(&l2->ch.list);
	l2->ch.ctrl(&l2->ch, CLOSE_CHANNEL, शून्य);
पूर्ण

अटल व्योम
tei_assign_req(काष्ठा FsmInst *fi, पूर्णांक event, व्योम *arg)
अणु
	काष्ठा teimgr *पंचांग = fi->userdata;
	u_अक्षर *dp = arg;

	अगर (पंचांग->l2->tei == GROUP_TEI) अणु
		पंचांग->tei_m.prपूर्णांकdebug(&पंचांग->tei_m,
				     "net tei assign request without tei");
		वापस;
	पूर्ण
	पंचांग->ri = ((अचिन्हित पूर्णांक) *dp++ << 8);
	पंचांग->ri += *dp++;
	अगर (*debug & DEBUG_L2_TEI)
		पंचांग->tei_m.prपूर्णांकdebug(&पंचांग->tei_m,
				     "net assign request ri %d teim %d", पंचांग->ri, *dp);
	put_tei_msg(पंचांग->mgr, ID_ASSIGNED, पंचांग->ri, पंचांग->l2->tei);
	mISDN_FsmChangeState(fi, ST_TEI_NOP);
पूर्ण

अटल व्योम
tei_id_chk_req_net(काष्ठा FsmInst *fi, पूर्णांक event, व्योम *arg)
अणु
	काष्ठा teimgr	*पंचांग = fi->userdata;

	अगर (*debug & DEBUG_L2_TEI)
		पंचांग->tei_m.prपूर्णांकdebug(fi, "id check request for tei %d",
				     पंचांग->l2->tei);
	पंचांग->rcnt = 0;
	put_tei_msg(पंचांग->mgr, ID_CHK_REQ, 0, पंचांग->l2->tei);
	mISDN_FsmChangeState(&पंचांग->tei_m, ST_TEI_IDVERIFY);
	mISDN_FsmAddTimer(&पंचांग->समयr, पंचांग->tval, EV_TIMER, शून्य, 2);
	पंचांग->nval = 2;
पूर्ण

अटल व्योम
tei_id_chk_resp(काष्ठा FsmInst *fi, पूर्णांक event, व्योम *arg)
अणु
	काष्ठा teimgr *पंचांग = fi->userdata;
	u_अक्षर *dp = arg;
	पूर्णांक tei;

	tei = dp[3] >> 1;
	अगर (*debug & DEBUG_L2_TEI)
		पंचांग->tei_m.prपूर्णांकdebug(fi, "identity check resp tei %d", tei);
	अगर (tei == पंचांग->l2->tei)
		पंचांग->rcnt++;
पूर्ण

अटल व्योम
tei_id_verअगरy_net(काष्ठा FsmInst *fi, पूर्णांक event, व्योम *arg)
अणु
	काष्ठा teimgr *पंचांग = fi->userdata;
	u_अक्षर *dp = arg;
	पूर्णांक tei;

	tei = dp[3] >> 1;
	अगर (*debug & DEBUG_L2_TEI)
		पंचांग->tei_m.prपूर्णांकdebug(fi, "identity verify req tei %d/%d",
				     tei, पंचांग->l2->tei);
	अगर (tei == पंचांग->l2->tei)
		tei_id_chk_req_net(fi, event, arg);
पूर्ण

अटल व्योम
tei_id_ver_tout_net(काष्ठा FsmInst *fi, पूर्णांक event, व्योम *arg)
अणु
	काष्ठा teimgr *पंचांग = fi->userdata;

	अगर (पंचांग->rcnt == 1) अणु
		अगर (*debug & DEBUG_L2_TEI)
			पंचांग->tei_m.prपूर्णांकdebug(fi,
					     "check req for tei %d successful\n", पंचांग->l2->tei);
		mISDN_FsmChangeState(fi, ST_TEI_NOP);
	पूर्ण अन्यथा अगर (पंचांग->rcnt > 1) अणु
		/* duplicate assignment; हटाओ */
		tei_l2हटाओ(पंचांग->l2);
	पूर्ण अन्यथा अगर (--पंचांग->nval) अणु
		अगर (*debug & DEBUG_L2_TEI)
			पंचांग->tei_m.prपूर्णांकdebug(fi,
					     "id check req(%d) for tei %d",
					     3 - पंचांग->nval, पंचांग->l2->tei);
		put_tei_msg(पंचांग->mgr, ID_CHK_REQ, 0, पंचांग->l2->tei);
		mISDN_FsmAddTimer(&पंचांग->समयr, पंचांग->tval, EV_TIMER, शून्य, 4);
	पूर्ण अन्यथा अणु
		पंचांग->tei_m.prपूर्णांकdebug(fi, "check req for tei %d failed",
				     पंचांग->l2->tei);
		mISDN_FsmChangeState(fi, ST_TEI_NOP);
		tei_l2हटाओ(पंचांग->l2);
	पूर्ण
पूर्ण

अटल काष्ठा FsmNode TeiFnListNet[] =
अणु
	अणुST_TEI_NOP, EV_ASSIGN_REQ, tei_assign_reqपूर्ण,
	अणुST_TEI_NOP, EV_VERIFY, tei_id_verअगरy_netपूर्ण,
	अणुST_TEI_NOP, EV_CHKREQ, tei_id_chk_req_netपूर्ण,
	अणुST_TEI_IDVERIFY, EV_TIMER, tei_id_ver_tout_netपूर्ण,
	अणुST_TEI_IDVERIFY, EV_CHKRESP, tei_id_chk_respपूर्ण,
पूर्ण;

अटल व्योम
tei_ph_data_ind(काष्ठा teimgr *पंचांग, u_पूर्णांक mt, u_अक्षर *dp, पूर्णांक len)
अणु
	अगर (test_bit(FLG_FIXED_TEI, &पंचांग->l2->flag))
		वापस;
	अगर (*debug & DEBUG_L2_TEI)
		पंचांग->tei_m.prपूर्णांकdebug(&पंचांग->tei_m, "tei handler mt %x", mt);
	अगर (mt == ID_ASSIGNED)
		mISDN_FsmEvent(&पंचांग->tei_m, EV_ASSIGN, dp);
	अन्यथा अगर (mt == ID_DENIED)
		mISDN_FsmEvent(&पंचांग->tei_m, EV_DENIED, dp);
	अन्यथा अगर (mt == ID_CHK_REQ)
		mISDN_FsmEvent(&पंचांग->tei_m, EV_CHKREQ, dp);
	अन्यथा अगर (mt == ID_REMOVE)
		mISDN_FsmEvent(&पंचांग->tei_m, EV_REMOVE, dp);
	अन्यथा अगर (mt == ID_VERIFY)
		mISDN_FsmEvent(&पंचांग->tei_m, EV_VERIFY, dp);
	अन्यथा अगर (mt == ID_CHK_RES)
		mISDN_FsmEvent(&पंचांग->tei_m, EV_CHKRESP, dp);
पूर्ण

अटल काष्ठा layer2 *
create_new_tei(काष्ठा manager *mgr, पूर्णांक tei, पूर्णांक sapi)
अणु
	अचिन्हित दीर्घ		opt = 0;
	अचिन्हित दीर्घ		flags;
	पूर्णांक			id;
	काष्ठा layer2		*l2;
	काष्ठा channel_req	rq;

	अगर (!mgr->up)
		वापस शून्य;
	अगर ((tei >= 0) && (tei < 64))
		test_and_set_bit(OPTION_L2_FIXEDTEI, &opt);
	अगर (mgr->ch.st->dev->Dprotocols & ((1 << ISDN_P_TE_E1) |
	    (1 << ISDN_P_NT_E1))) अणु
		test_and_set_bit(OPTION_L2_PMX, &opt);
		rq.protocol = ISDN_P_NT_E1;
	पूर्ण अन्यथा अणु
		rq.protocol = ISDN_P_NT_S0;
	पूर्ण
	l2 = create_l2(mgr->up, ISDN_P_LAPD_NT, opt, tei, sapi);
	अगर (!l2) अणु
		prपूर्णांकk(KERN_WARNING "%s:no memory for layer2\n", __func__);
		वापस शून्य;
	पूर्ण
	l2->पंचांग = kzalloc(माप(काष्ठा teimgr), GFP_KERNEL);
	अगर (!l2->पंचांग) अणु
		kमुक्त(l2);
		prपूर्णांकk(KERN_WARNING "%s:no memory for teimgr\n", __func__);
		वापस शून्य;
	पूर्ण
	l2->पंचांग->mgr = mgr;
	l2->पंचांग->l2 = l2;
	l2->पंचांग->tei_m.debug = *debug & DEBUG_L2_TEIFSM;
	l2->पंचांग->tei_m.userdata = l2->पंचांग;
	l2->पंचांग->tei_m.prपूर्णांकdebug = tei_debug;
	l2->पंचांग->tei_m.fsm = &teअगरsmn;
	l2->पंचांग->tei_m.state = ST_TEI_NOP;
	l2->पंचांग->tval = 2000; /* T202  2 sec */
	mISDN_FsmInitTimer(&l2->पंचांग->tei_m, &l2->पंचांग->समयr);
	ग_लिखो_lock_irqsave(&mgr->lock, flags);
	id = get_मुक्त_id(mgr);
	list_add_tail(&l2->list, &mgr->layer2);
	ग_लिखो_unlock_irqrestore(&mgr->lock, flags);
	अगर (id < 0) अणु
		l2->ch.ctrl(&l2->ch, CLOSE_CHANNEL, शून्य);
		prपूर्णांकk(KERN_WARNING "%s:no free id\n", __func__);
		वापस शून्य;
	पूर्ण अन्यथा अणु
		l2->ch.nr = id;
		__add_layer2(&l2->ch, mgr->ch.st);
		l2->ch.recv = mgr->ch.recv;
		l2->ch.peer = mgr->ch.peer;
		l2->ch.ctrl(&l2->ch, OPEN_CHANNEL, शून्य);
		/* We need खोलो here L1 क्रम the manager as well (refcounting) */
		rq.adr.dev = mgr->ch.st->dev->id;
		id = mgr->ch.st->own.ctrl(&mgr->ch.st->own, OPEN_CHANNEL, &rq);
		अगर (id < 0) अणु
			prपूर्णांकk(KERN_WARNING "%s: cannot open L1\n", __func__);
			l2->ch.ctrl(&l2->ch, CLOSE_CHANNEL, शून्य);
			l2 = शून्य;
		पूर्ण
	पूर्ण
	वापस l2;
पूर्ण

अटल व्योम
new_tei_req(काष्ठा manager *mgr, u_अक्षर *dp)
अणु
	पूर्णांक		tei, ri;
	काष्ठा layer2	*l2;

	ri = dp[0] << 8;
	ri += dp[1];
	अगर (!mgr->up)
		जाओ denied;
	अगर (!(dp[3] & 1)) /* Extension bit != 1 */
		जाओ denied;
	अगर (dp[3] != 0xff)
		tei = dp[3] >> 1; /* 3GPP TS 08.56 6.1.11.2 */
	अन्यथा
		tei = get_मुक्त_tei(mgr);
	अगर (tei < 0) अणु
		prपूर्णांकk(KERN_WARNING "%s:No free tei\n", __func__);
		जाओ denied;
	पूर्ण
	l2 = create_new_tei(mgr, tei, CTRL_SAPI);
	अगर (!l2)
		जाओ denied;
	अन्यथा
		mISDN_FsmEvent(&l2->पंचांग->tei_m, EV_ASSIGN_REQ, dp);
	वापस;
denied:
	put_tei_msg(mgr, ID_DENIED, ri, GROUP_TEI);
पूर्ण

अटल पूर्णांक
ph_data_ind(काष्ठा manager *mgr, काष्ठा sk_buff *skb)
अणु
	पूर्णांक		ret = -EINVAL;
	काष्ठा layer2	*l2, *nl2;
	u_अक्षर		mt;

	अगर (skb->len < 8) अणु
		अगर (*debug  & DEBUG_L2_TEI)
			prपूर्णांकk(KERN_DEBUG "%s: short mgr frame %d/8\n",
			       __func__, skb->len);
		जाओ करोne;
	पूर्ण

	अगर ((skb->data[0] >> 2) != TEI_SAPI) /* not क्रम us */
		जाओ करोne;
	अगर (skb->data[0] & 1) /* EA0 क्रमmal error */
		जाओ करोne;
	अगर (!(skb->data[1] & 1)) /* EA1 क्रमmal error */
		जाओ करोne;
	अगर ((skb->data[1] >> 1) != GROUP_TEI) /* not क्रम us */
		जाओ करोne;
	अगर ((skb->data[2] & 0xef) != UI) /* not UI */
		जाओ करोne;
	अगर (skb->data[3] != TEI_ENTITY_ID) /* not tei entity */
		जाओ करोne;
	mt = skb->data[6];
	चयन (mt) अणु
	हाल ID_REQUEST:
	हाल ID_CHK_RES:
	हाल ID_VERIFY:
		अगर (!test_bit(MGR_OPT_NETWORK, &mgr->options))
			जाओ करोne;
		अवरोध;
	हाल ID_ASSIGNED:
	हाल ID_DENIED:
	हाल ID_CHK_REQ:
	हाल ID_REMOVE:
		अगर (test_bit(MGR_OPT_NETWORK, &mgr->options))
			जाओ करोne;
		अवरोध;
	शेष:
		जाओ करोne;
	पूर्ण
	ret = 0;
	अगर (mt == ID_REQUEST) अणु
		new_tei_req(mgr, &skb->data[4]);
		जाओ करोne;
	पूर्ण
	list_क्रम_each_entry_safe(l2, nl2, &mgr->layer2, list) अणु
		tei_ph_data_ind(l2->पंचांग, mt, &skb->data[4], skb->len - 4);
	पूर्ण
करोne:
	वापस ret;
पूर्ण

पूर्णांक
l2_tei(काष्ठा layer2 *l2, u_पूर्णांक cmd, u_दीर्घ arg)
अणु
	काष्ठा teimgr	*पंचांग = l2->पंचांग;

	अगर (test_bit(FLG_FIXED_TEI, &l2->flag))
		वापस 0;
	अगर (*debug & DEBUG_L2_TEI)
		prपूर्णांकk(KERN_DEBUG "%s: cmd(%x)\n", __func__, cmd);
	चयन (cmd) अणु
	हाल MDL_ASSIGN_IND:
		mISDN_FsmEvent(&पंचांग->tei_m, EV_IDREQ, शून्य);
		अवरोध;
	हाल MDL_ERROR_IND:
		अगर (test_bit(MGR_OPT_NETWORK, &पंचांग->mgr->options))
			mISDN_FsmEvent(&पंचांग->tei_m, EV_CHKREQ, &l2->tei);
		अगर (test_bit(MGR_OPT_USER, &पंचांग->mgr->options))
			mISDN_FsmEvent(&पंचांग->tei_m, EV_VERIFY, शून्य);
		अवरोध;
	हाल MDL_STATUS_UP_IND:
		अगर (test_bit(MGR_OPT_NETWORK, &पंचांग->mgr->options))
			mISDN_FsmEvent(&पंचांग->mgr->deact, EV_ACTIVATE, शून्य);
		अवरोध;
	हाल MDL_STATUS_DOWN_IND:
		अगर (test_bit(MGR_OPT_NETWORK, &पंचांग->mgr->options))
			mISDN_FsmEvent(&पंचांग->mgr->deact, EV_DEACTIVATE, शून्य);
		अवरोध;
	हाल MDL_STATUS_UI_IND:
		अगर (test_bit(MGR_OPT_NETWORK, &पंचांग->mgr->options))
			mISDN_FsmEvent(&पंचांग->mgr->deact, EV_UI, शून्य);
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

व्योम
TEIrelease(काष्ठा layer2 *l2)
अणु
	काष्ठा teimgr	*पंचांग = l2->पंचांग;
	u_दीर्घ		flags;

	mISDN_FsmDelTimer(&पंचांग->समयr, 1);
	ग_लिखो_lock_irqsave(&पंचांग->mgr->lock, flags);
	list_del(&l2->list);
	ग_लिखो_unlock_irqrestore(&पंचांग->mgr->lock, flags);
	l2->पंचांग = शून्य;
	kमुक्त(पंचांग);
पूर्ण

अटल पूर्णांक
create_teimgr(काष्ठा manager *mgr, काष्ठा channel_req *crq)
अणु
	काष्ठा layer2		*l2;
	अचिन्हित दीर्घ		opt = 0;
	अचिन्हित दीर्घ		flags;
	पूर्णांक			id;
	काष्ठा channel_req	l1rq;

	अगर (*debug & DEBUG_L2_TEI)
		prपूर्णांकk(KERN_DEBUG "%s: %s proto(%x) adr(%d %d %d %d)\n",
		       __func__, dev_name(&mgr->ch.st->dev->dev),
		       crq->protocol, crq->adr.dev, crq->adr.channel,
		       crq->adr.sapi, crq->adr.tei);
	अगर (crq->adr.tei > GROUP_TEI)
		वापस -EINVAL;
	अगर (crq->adr.tei < 64)
		test_and_set_bit(OPTION_L2_FIXEDTEI, &opt);
	अगर (crq->adr.tei == 0)
		test_and_set_bit(OPTION_L2_PTP, &opt);
	अगर (test_bit(MGR_OPT_NETWORK, &mgr->options)) अणु
		अगर (crq->protocol == ISDN_P_LAPD_TE)
			वापस -EPROTONOSUPPORT;
		अगर ((crq->adr.tei != 0) && (crq->adr.tei != 127))
			वापस -EINVAL;
		अगर (mgr->up) अणु
			prपूर्णांकk(KERN_WARNING
			       "%s: only one network manager is allowed\n",
			       __func__);
			वापस -EBUSY;
		पूर्ण
	पूर्ण अन्यथा अगर (test_bit(MGR_OPT_USER, &mgr->options)) अणु
		अगर (crq->protocol == ISDN_P_LAPD_NT)
			वापस -EPROTONOSUPPORT;
		अगर ((crq->adr.tei >= 64) && (crq->adr.tei < GROUP_TEI))
			वापस -EINVAL; /* dyn tei */
	पूर्ण अन्यथा अणु
		अगर (crq->protocol == ISDN_P_LAPD_NT)
			test_and_set_bit(MGR_OPT_NETWORK, &mgr->options);
		अगर (crq->protocol == ISDN_P_LAPD_TE)
			test_and_set_bit(MGR_OPT_USER, &mgr->options);
	पूर्ण
	l1rq.adr = crq->adr;
	अगर (mgr->ch.st->dev->Dprotocols
	    & ((1 << ISDN_P_TE_E1) | (1 << ISDN_P_NT_E1)))
		test_and_set_bit(OPTION_L2_PMX, &opt);
	अगर ((crq->protocol == ISDN_P_LAPD_NT) && (crq->adr.tei == 127)) अणु
		mgr->up = crq->ch;
		id = DL_INFO_L2_CONNECT;
		teiup_create(mgr, DL_INFORMATION_IND, माप(id), &id);
		अगर (test_bit(MGR_PH_ACTIVE, &mgr->options))
			teiup_create(mgr, PH_ACTIVATE_IND, 0, शून्य);
		crq->ch = शून्य;
		अगर (!list_empty(&mgr->layer2)) अणु
			पढ़ो_lock_irqsave(&mgr->lock, flags);
			list_क्रम_each_entry(l2, &mgr->layer2, list) अणु
				l2->up = mgr->up;
				l2->ch.ctrl(&l2->ch, OPEN_CHANNEL, शून्य);
			पूर्ण
			पढ़ो_unlock_irqrestore(&mgr->lock, flags);
		पूर्ण
		वापस 0;
	पूर्ण
	l2 = create_l2(crq->ch, crq->protocol, opt,
		       crq->adr.tei, crq->adr.sapi);
	अगर (!l2)
		वापस -ENOMEM;
	l2->पंचांग = kzalloc(माप(काष्ठा teimgr), GFP_KERNEL);
	अगर (!l2->पंचांग) अणु
		kमुक्त(l2);
		prपूर्णांकk(KERN_ERR "kmalloc teimgr failed\n");
		वापस -ENOMEM;
	पूर्ण
	l2->पंचांग->mgr = mgr;
	l2->पंचांग->l2 = l2;
	l2->पंचांग->tei_m.debug = *debug & DEBUG_L2_TEIFSM;
	l2->पंचांग->tei_m.userdata = l2->पंचांग;
	l2->पंचांग->tei_m.prपूर्णांकdebug = tei_debug;
	अगर (crq->protocol == ISDN_P_LAPD_TE) अणु
		l2->पंचांग->tei_m.fsm = &teअगरsmu;
		l2->पंचांग->tei_m.state = ST_TEI_NOP;
		l2->पंचांग->tval = 1000; /* T201  1 sec */
		अगर (test_bit(OPTION_L2_PMX, &opt))
			l1rq.protocol = ISDN_P_TE_E1;
		अन्यथा
			l1rq.protocol = ISDN_P_TE_S0;
	पूर्ण अन्यथा अणु
		l2->पंचांग->tei_m.fsm = &teअगरsmn;
		l2->पंचांग->tei_m.state = ST_TEI_NOP;
		l2->पंचांग->tval = 2000; /* T202  2 sec */
		अगर (test_bit(OPTION_L2_PMX, &opt))
			l1rq.protocol = ISDN_P_NT_E1;
		अन्यथा
			l1rq.protocol = ISDN_P_NT_S0;
	पूर्ण
	mISDN_FsmInitTimer(&l2->पंचांग->tei_m, &l2->पंचांग->समयr);
	ग_लिखो_lock_irqsave(&mgr->lock, flags);
	id = get_मुक्त_id(mgr);
	list_add_tail(&l2->list, &mgr->layer2);
	ग_लिखो_unlock_irqrestore(&mgr->lock, flags);
	अगर (id >= 0) अणु
		l2->ch.nr = id;
		l2->up->nr = id;
		crq->ch = &l2->ch;
		/* We need खोलो here L1 क्रम the manager as well (refcounting) */
		id = mgr->ch.st->own.ctrl(&mgr->ch.st->own, OPEN_CHANNEL,
					  &l1rq);
	पूर्ण
	अगर (id < 0)
		l2->ch.ctrl(&l2->ch, CLOSE_CHANNEL, शून्य);
	वापस id;
पूर्ण

अटल पूर्णांक
mgr_send(काष्ठा mISDNchannel *ch, काष्ठा sk_buff *skb)
अणु
	काष्ठा manager	*mgr;
	काष्ठा mISDNhead	*hh =  mISDN_HEAD_P(skb);
	पूर्णांक			ret = -EINVAL;

	mgr = container_of(ch, काष्ठा manager, ch);
	अगर (*debug & DEBUG_L2_RECV)
		prपूर्णांकk(KERN_DEBUG "%s: prim(%x) id(%x)\n",
		       __func__, hh->prim, hh->id);
	चयन (hh->prim) अणु
	हाल PH_DATA_IND:
		mISDN_FsmEvent(&mgr->deact, EV_UI, शून्य);
		ret = ph_data_ind(mgr, skb);
		अवरोध;
	हाल PH_DATA_CNF:
		करो_ack(mgr, hh->id);
		ret = 0;
		अवरोध;
	हाल PH_ACTIVATE_IND:
		test_and_set_bit(MGR_PH_ACTIVE, &mgr->options);
		अगर (mgr->up)
			teiup_create(mgr, PH_ACTIVATE_IND, 0, शून्य);
		mISDN_FsmEvent(&mgr->deact, EV_ACTIVATE_IND, शून्य);
		करो_send(mgr);
		ret = 0;
		अवरोध;
	हाल PH_DEACTIVATE_IND:
		test_and_clear_bit(MGR_PH_ACTIVE, &mgr->options);
		अगर (mgr->up)
			teiup_create(mgr, PH_DEACTIVATE_IND, 0, शून्य);
		mISDN_FsmEvent(&mgr->deact, EV_DEACTIVATE_IND, शून्य);
		ret = 0;
		अवरोध;
	हाल DL_UNITDATA_REQ:
		वापस dl_unit_data(mgr, skb);
	पूर्ण
	अगर (!ret)
		dev_kमुक्त_skb(skb);
	वापस ret;
पूर्ण

अटल पूर्णांक
मुक्त_teimanager(काष्ठा manager *mgr)
अणु
	काष्ठा layer2	*l2, *nl2;

	test_and_clear_bit(OPTION_L1_HOLD, &mgr->options);
	अगर (test_bit(MGR_OPT_NETWORK, &mgr->options)) अणु
		/* not locked lock is taken in release tei */
		mgr->up = शून्य;
		अगर (test_bit(OPTION_L2_CLEANUP, &mgr->options)) अणु
			list_क्रम_each_entry_safe(l2, nl2, &mgr->layer2, list) अणु
				put_tei_msg(mgr, ID_REMOVE, 0, l2->tei);
				mutex_lock(&mgr->ch.st->lmutex);
				list_del(&l2->ch.list);
				mutex_unlock(&mgr->ch.st->lmutex);
				l2->ch.ctrl(&l2->ch, CLOSE_CHANNEL, शून्य);
			पूर्ण
			test_and_clear_bit(MGR_OPT_NETWORK, &mgr->options);
		पूर्ण अन्यथा अणु
			list_क्रम_each_entry_safe(l2, nl2, &mgr->layer2, list) अणु
				l2->up = शून्य;
			पूर्ण
		पूर्ण
	पूर्ण
	अगर (test_bit(MGR_OPT_USER, &mgr->options)) अणु
		अगर (list_empty(&mgr->layer2))
			test_and_clear_bit(MGR_OPT_USER, &mgr->options);
	पूर्ण
	mgr->ch.st->dev->D.ctrl(&mgr->ch.st->dev->D, CLOSE_CHANNEL, शून्य);
	वापस 0;
पूर्ण

अटल पूर्णांक
ctrl_teimanager(काष्ठा manager *mgr, व्योम *arg)
अणु
	/* currently we only have one option */
	अचिन्हित पूर्णांक *val = (अचिन्हित पूर्णांक *)arg;

	चयन (val[0]) अणु
	हाल IMCLEAR_L2:
		अगर (val[1])
			test_and_set_bit(OPTION_L2_CLEANUP, &mgr->options);
		अन्यथा
			test_and_clear_bit(OPTION_L2_CLEANUP, &mgr->options);
		अवरोध;
	हाल IMHOLD_L1:
		अगर (val[1])
			test_and_set_bit(OPTION_L1_HOLD, &mgr->options);
		अन्यथा
			test_and_clear_bit(OPTION_L1_HOLD, &mgr->options);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

/* This function करोes create a L2 क्रम fixed TEI in NT Mode */
अटल पूर्णांक
check_data(काष्ठा manager *mgr, काष्ठा sk_buff *skb)
अणु
	काष्ठा mISDNhead	*hh =  mISDN_HEAD_P(skb);
	पूर्णांक			ret, tei, sapi;
	काष्ठा layer2		*l2;

	अगर (*debug & DEBUG_L2_CTRL)
		prपूर्णांकk(KERN_DEBUG "%s: prim(%x) id(%x)\n",
		       __func__, hh->prim, hh->id);
	अगर (test_bit(MGR_OPT_USER, &mgr->options))
		वापस -ENOTCONN;
	अगर (hh->prim != PH_DATA_IND)
		वापस -ENOTCONN;
	अगर (skb->len != 3)
		वापस -ENOTCONN;
	अगर (skb->data[0] & 3) /* EA0 and CR must be  0 */
		वापस -EINVAL;
	sapi = skb->data[0] >> 2;
	अगर (!(skb->data[1] & 1)) /* invalid EA1 */
		वापस -EINVAL;
	tei = skb->data[1] >> 1;
	अगर (tei > 63) /* not a fixed tei */
		वापस -ENOTCONN;
	अगर ((skb->data[2] & ~0x10) != SABME)
		वापस -ENOTCONN;
	/* We got a SABME क्रम a fixed TEI */
	अगर (*debug & DEBUG_L2_CTRL)
		prपूर्णांकk(KERN_DEBUG "%s: SABME sapi(%d) tei(%d)\n",
		       __func__, sapi, tei);
	l2 = create_new_tei(mgr, tei, sapi);
	अगर (!l2) अणु
		अगर (*debug & DEBUG_L2_CTRL)
			prपूर्णांकk(KERN_DEBUG "%s: failed to create new tei\n",
			       __func__);
		वापस -ENOMEM;
	पूर्ण
	ret = l2->ch.send(&l2->ch, skb);
	वापस ret;
पूर्ण

व्योम
delete_teimanager(काष्ठा mISDNchannel *ch)
अणु
	काष्ठा manager	*mgr;
	काष्ठा layer2	*l2, *nl2;

	mgr = container_of(ch, काष्ठा manager, ch);
	/* not locked lock is taken in release tei */
	list_क्रम_each_entry_safe(l2, nl2, &mgr->layer2, list) अणु
		mutex_lock(&mgr->ch.st->lmutex);
		list_del(&l2->ch.list);
		mutex_unlock(&mgr->ch.st->lmutex);
		l2->ch.ctrl(&l2->ch, CLOSE_CHANNEL, शून्य);
	पूर्ण
	list_del(&mgr->ch.list);
	list_del(&mgr->bcast.list);
	skb_queue_purge(&mgr->sendq);
	kमुक्त(mgr);
पूर्ण

अटल पूर्णांक
mgr_ctrl(काष्ठा mISDNchannel *ch, u_पूर्णांक cmd, व्योम *arg)
अणु
	काष्ठा manager	*mgr;
	पूर्णांक		ret = -EINVAL;

	mgr = container_of(ch, काष्ठा manager, ch);
	अगर (*debug & DEBUG_L2_CTRL)
		prपूर्णांकk(KERN_DEBUG "%s(%x, %p)\n", __func__, cmd, arg);
	चयन (cmd) अणु
	हाल OPEN_CHANNEL:
		ret = create_teimgr(mgr, arg);
		अवरोध;
	हाल CLOSE_CHANNEL:
		ret = मुक्त_teimanager(mgr);
		अवरोध;
	हाल CONTROL_CHANNEL:
		ret = ctrl_teimanager(mgr, arg);
		अवरोध;
	हाल CHECK_DATA:
		ret = check_data(mgr, arg);
		अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक
mgr_bcast(काष्ठा mISDNchannel *ch, काष्ठा sk_buff *skb)
अणु
	काष्ठा manager		*mgr = container_of(ch, काष्ठा manager, bcast);
	काष्ठा mISDNhead	*hhc, *hh = mISDN_HEAD_P(skb);
	काष्ठा sk_buff		*cskb = शून्य;
	काष्ठा layer2		*l2;
	u_दीर्घ			flags;
	पूर्णांक			ret;

	पढ़ो_lock_irqsave(&mgr->lock, flags);
	list_क्रम_each_entry(l2, &mgr->layer2, list) अणु
		अगर ((hh->id & MISDN_ID_SAPI_MASK) ==
		    (l2->ch.addr & MISDN_ID_SAPI_MASK)) अणु
			अगर (list_is_last(&l2->list, &mgr->layer2)) अणु
				cskb = skb;
				skb = शून्य;
			पूर्ण अन्यथा अणु
				अगर (!cskb)
					cskb = skb_copy(skb, GFP_ATOMIC);
			पूर्ण
			अगर (cskb) अणु
				hhc = mISDN_HEAD_P(cskb);
				/* save original header behind normal header */
				hhc++;
				*hhc = *hh;
				hhc--;
				hhc->prim = DL_INTERN_MSG;
				hhc->id = l2->ch.nr;
				ret = ch->st->own.recv(&ch->st->own, cskb);
				अगर (ret) अणु
					अगर (*debug & DEBUG_SEND_ERR)
						prपूर्णांकk(KERN_DEBUG
						       "%s ch%d prim(%x) addr(%x)"
						       " err %d\n",
						       __func__, l2->ch.nr,
						       hh->prim, l2->ch.addr, ret);
				पूर्ण अन्यथा
					cskb = शून्य;
			पूर्ण अन्यथा अणु
				prपूर्णांकk(KERN_WARNING "%s ch%d addr %x no mem\n",
				       __func__, ch->nr, ch->addr);
				जाओ out;
			पूर्ण
		पूर्ण
	पूर्ण
out:
	पढ़ो_unlock_irqrestore(&mgr->lock, flags);
	dev_kमुक्त_skb(cskb);
	dev_kमुक्त_skb(skb);
	वापस 0;
पूर्ण

अटल पूर्णांक
mgr_bcast_ctrl(काष्ठा mISDNchannel *ch, u_पूर्णांक cmd, व्योम *arg)
अणु

	वापस -EINVAL;
पूर्ण

पूर्णांक
create_teimanager(काष्ठा mISDNdevice *dev)
अणु
	काष्ठा manager *mgr;

	mgr = kzalloc(माप(काष्ठा manager), GFP_KERNEL);
	अगर (!mgr)
		वापस -ENOMEM;
	INIT_LIST_HEAD(&mgr->layer2);
	rwlock_init(&mgr->lock);
	skb_queue_head_init(&mgr->sendq);
	mgr->nextid = 1;
	mgr->lastid = MISDN_ID_NONE;
	mgr->ch.send = mgr_send;
	mgr->ch.ctrl = mgr_ctrl;
	mgr->ch.st = dev->D.st;
	set_channel_address(&mgr->ch, TEI_SAPI, GROUP_TEI);
	add_layer2(&mgr->ch, dev->D.st);
	mgr->bcast.send = mgr_bcast;
	mgr->bcast.ctrl = mgr_bcast_ctrl;
	mgr->bcast.st = dev->D.st;
	set_channel_address(&mgr->bcast, 0, GROUP_TEI);
	add_layer2(&mgr->bcast, dev->D.st);
	mgr->deact.debug = *debug & DEBUG_MANAGER;
	mgr->deact.userdata = mgr;
	mgr->deact.prपूर्णांकdebug = da_debug;
	mgr->deact.fsm = &deactfsm;
	mgr->deact.state = ST_L1_DEACT;
	mISDN_FsmInitTimer(&mgr->deact, &mgr->daसमयr);
	dev->teimgr = &mgr->ch;
	वापस 0;
पूर्ण

पूर्णांक TEIInit(u_पूर्णांक *deb)
अणु
	पूर्णांक res;
	debug = deb;
	teअगरsmu.state_count = TEI_STATE_COUNT;
	teअगरsmu.event_count = TEI_EVENT_COUNT;
	teअगरsmu.strEvent = strTeiEvent;
	teअगरsmu.strState = strTeiState;
	res = mISDN_FsmNew(&teअगरsmu, TeiFnListUser, ARRAY_SIZE(TeiFnListUser));
	अगर (res)
		जाओ error;
	teअगरsmn.state_count = TEI_STATE_COUNT;
	teअगरsmn.event_count = TEI_EVENT_COUNT;
	teअगरsmn.strEvent = strTeiEvent;
	teअगरsmn.strState = strTeiState;
	res = mISDN_FsmNew(&teअगरsmn, TeiFnListNet, ARRAY_SIZE(TeiFnListNet));
	अगर (res)
		जाओ error_smn;
	deactfsm.state_count =  DEACT_STATE_COUNT;
	deactfsm.event_count = DEACT_EVENT_COUNT;
	deactfsm.strEvent = strDeactEvent;
	deactfsm.strState = strDeactState;
	res = mISDN_FsmNew(&deactfsm, DeactFnList, ARRAY_SIZE(DeactFnList));
	अगर (res)
		जाओ error_deact;
	वापस 0;

error_deact:
	mISDN_FsmFree(&teअगरsmn);
error_smn:
	mISDN_FsmFree(&teअगरsmu);
error:
	वापस res;
पूर्ण

व्योम TEIFree(व्योम)
अणु
	mISDN_FsmFree(&teअगरsmu);
	mISDN_FsmFree(&teअगरsmn);
	mISDN_FsmFree(&deactfsm);
पूर्ण
