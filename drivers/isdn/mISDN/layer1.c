<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *
 * Author	Karsten Keil <kkeil@novell.com>
 *
 * Copyright 2008  by Karsten Keil <kkeil@novell.com>
 */


#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/mISDNhw.h>
#समावेश "core.h"
#समावेश "layer1.h"
#समावेश "fsm.h"

अटल u_पूर्णांक *debug;

काष्ठा layer1 अणु
	u_दीर्घ Flags;
	काष्ठा FsmInst l1m;
	काष्ठा FsmTimer समयr3;
	काष्ठा FsmTimer समयrX;
	पूर्णांक delay;
	पूर्णांक t3_value;
	काष्ठा dchannel *dch;
	dchannel_l1callback *dcb;
पूर्ण;

#घोषणा TIMER3_DEFAULT_VALUE	7000

अटल
काष्ठा Fsm l1fsm_s = अणुशून्य, 0, 0, शून्य, शून्यपूर्ण;

क्रमागत अणु
	ST_L1_F2,
	ST_L1_F3,
	ST_L1_F4,
	ST_L1_F5,
	ST_L1_F6,
	ST_L1_F7,
	ST_L1_F8,
पूर्ण;

#घोषणा L1S_STATE_COUNT (ST_L1_F8 + 1)

अटल अक्षर *strL1SState[] =
अणु
	"ST_L1_F2",
	"ST_L1_F3",
	"ST_L1_F4",
	"ST_L1_F5",
	"ST_L1_F6",
	"ST_L1_F7",
	"ST_L1_F8",
पूर्ण;

क्रमागत अणु
	EV_PH_ACTIVATE,
	EV_PH_DEACTIVATE,
	EV_RESET_IND,
	EV_DEACT_CNF,
	EV_DEACT_IND,
	EV_POWER_UP,
	EV_ANYSIG_IND,
	EV_INFO2_IND,
	EV_INFO4_IND,
	EV_TIMER_DEACT,
	EV_TIMER_ACT,
	EV_TIMER3,
पूर्ण;

#घोषणा L1_EVENT_COUNT (EV_TIMER3 + 1)

अटल अक्षर *strL1Event[] =
अणु
	"EV_PH_ACTIVATE",
	"EV_PH_DEACTIVATE",
	"EV_RESET_IND",
	"EV_DEACT_CNF",
	"EV_DEACT_IND",
	"EV_POWER_UP",
	"EV_ANYSIG_IND",
	"EV_INFO2_IND",
	"EV_INFO4_IND",
	"EV_TIMER_DEACT",
	"EV_TIMER_ACT",
	"EV_TIMER3",
पूर्ण;

अटल व्योम
l1m_debug(काष्ठा FsmInst *fi, अक्षर *fmt, ...)
अणु
	काष्ठा layer1 *l1 = fi->userdata;
	काष्ठा va_क्रमmat vaf;
	बहु_सूची va;

	बहु_शुरू(va, fmt);

	vaf.fmt = fmt;
	vaf.va = &va;

	prपूर्णांकk(KERN_DEBUG "%s: %pV\n", dev_name(&l1->dch->dev.dev), &vaf);

	बहु_पूर्ण(va);
पूर्ण

अटल व्योम
l1_reset(काष्ठा FsmInst *fi, पूर्णांक event, व्योम *arg)
अणु
	mISDN_FsmChangeState(fi, ST_L1_F3);
पूर्ण

अटल व्योम
l1_deact_cnf(काष्ठा FsmInst *fi, पूर्णांक event, व्योम *arg)
अणु
	काष्ठा layer1 *l1 = fi->userdata;

	mISDN_FsmChangeState(fi, ST_L1_F3);
	अगर (test_bit(FLG_L1_ACTIVATING, &l1->Flags))
		l1->dcb(l1->dch, HW_POWERUP_REQ);
पूर्ण

अटल व्योम
l1_deact_req_s(काष्ठा FsmInst *fi, पूर्णांक event, व्योम *arg)
अणु
	काष्ठा layer1 *l1 = fi->userdata;

	mISDN_FsmChangeState(fi, ST_L1_F3);
	mISDN_FsmRestartTimer(&l1->समयrX, 550, EV_TIMER_DEACT, शून्य, 2);
	test_and_set_bit(FLG_L1_DEACTTIMER, &l1->Flags);
पूर्ण

अटल व्योम
l1_घातer_up_s(काष्ठा FsmInst *fi, पूर्णांक event, व्योम *arg)
अणु
	काष्ठा layer1 *l1 = fi->userdata;

	अगर (test_bit(FLG_L1_ACTIVATING, &l1->Flags)) अणु
		mISDN_FsmChangeState(fi, ST_L1_F4);
		l1->dcb(l1->dch, INFO3_P8);
	पूर्ण अन्यथा
		mISDN_FsmChangeState(fi, ST_L1_F3);
पूर्ण

अटल व्योम
l1_go_F5(काष्ठा FsmInst *fi, पूर्णांक event, व्योम *arg)
अणु
	mISDN_FsmChangeState(fi, ST_L1_F5);
पूर्ण

अटल व्योम
l1_go_F8(काष्ठा FsmInst *fi, पूर्णांक event, व्योम *arg)
अणु
	mISDN_FsmChangeState(fi, ST_L1_F8);
पूर्ण

अटल व्योम
l1_info2_ind(काष्ठा FsmInst *fi, पूर्णांक event, व्योम *arg)
अणु
	काष्ठा layer1 *l1 = fi->userdata;

	mISDN_FsmChangeState(fi, ST_L1_F6);
	l1->dcb(l1->dch, INFO3_P8);
पूर्ण

अटल व्योम
l1_info4_ind(काष्ठा FsmInst *fi, पूर्णांक event, व्योम *arg)
अणु
	काष्ठा layer1 *l1 = fi->userdata;

	mISDN_FsmChangeState(fi, ST_L1_F7);
	l1->dcb(l1->dch, INFO3_P8);
	अगर (test_and_clear_bit(FLG_L1_DEACTTIMER, &l1->Flags))
		mISDN_FsmDelTimer(&l1->समयrX, 4);
	अगर (!test_bit(FLG_L1_ACTIVATED, &l1->Flags)) अणु
		अगर (test_and_clear_bit(FLG_L1_T3RUN, &l1->Flags))
			mISDN_FsmDelTimer(&l1->समयr3, 3);
		mISDN_FsmRestartTimer(&l1->समयrX, 110, EV_TIMER_ACT, शून्य, 2);
		test_and_set_bit(FLG_L1_ACTTIMER, &l1->Flags);
	पूर्ण
पूर्ण

अटल व्योम
l1_समयr3(काष्ठा FsmInst *fi, पूर्णांक event, व्योम *arg)
अणु
	काष्ठा layer1 *l1 = fi->userdata;

	test_and_clear_bit(FLG_L1_T3RUN, &l1->Flags);
	अगर (test_and_clear_bit(FLG_L1_ACTIVATING, &l1->Flags)) अणु
		अगर (test_and_clear_bit(FLG_L1_DBLOCKED, &l1->Flags))
			l1->dcb(l1->dch, HW_D_NOBLOCKED);
		l1->dcb(l1->dch, PH_DEACTIVATE_IND);
	पूर्ण
	अगर (l1->l1m.state != ST_L1_F6) अणु
		mISDN_FsmChangeState(fi, ST_L1_F3);
		/* करो not क्रमce anything here, we need send INFO 0 */
	पूर्ण
पूर्ण

अटल व्योम
l1_समयr_act(काष्ठा FsmInst *fi, पूर्णांक event, व्योम *arg)
अणु
	काष्ठा layer1 *l1 = fi->userdata;

	test_and_clear_bit(FLG_L1_ACTTIMER, &l1->Flags);
	test_and_set_bit(FLG_L1_ACTIVATED, &l1->Flags);
	l1->dcb(l1->dch, PH_ACTIVATE_IND);
पूर्ण

अटल व्योम
l1_समयr_deact(काष्ठा FsmInst *fi, पूर्णांक event, व्योम *arg)
अणु
	काष्ठा layer1 *l1 = fi->userdata;

	test_and_clear_bit(FLG_L1_DEACTTIMER, &l1->Flags);
	test_and_clear_bit(FLG_L1_ACTIVATED, &l1->Flags);
	अगर (test_and_clear_bit(FLG_L1_DBLOCKED, &l1->Flags))
		l1->dcb(l1->dch, HW_D_NOBLOCKED);
	l1->dcb(l1->dch, PH_DEACTIVATE_IND);
	l1->dcb(l1->dch, HW_DEACT_REQ);
पूर्ण

अटल व्योम
l1_activate_s(काष्ठा FsmInst *fi, पूर्णांक event, व्योम *arg)
अणु
	काष्ठा layer1 *l1 = fi->userdata;

	mISDN_FsmRestartTimer(&l1->समयr3, l1->t3_value, EV_TIMER3, शून्य, 2);
	test_and_set_bit(FLG_L1_T3RUN, &l1->Flags);
	/* Tell HW to send INFO 1 */
	l1->dcb(l1->dch, HW_RESET_REQ);
पूर्ण

अटल व्योम
l1_activate_no(काष्ठा FsmInst *fi, पूर्णांक event, व्योम *arg)
अणु
	काष्ठा layer1 *l1 = fi->userdata;

	अगर ((!test_bit(FLG_L1_DEACTTIMER, &l1->Flags)) &&
	    (!test_bit(FLG_L1_T3RUN, &l1->Flags))) अणु
		test_and_clear_bit(FLG_L1_ACTIVATING, &l1->Flags);
		अगर (test_and_clear_bit(FLG_L1_DBLOCKED, &l1->Flags))
			l1->dcb(l1->dch, HW_D_NOBLOCKED);
		l1->dcb(l1->dch, PH_DEACTIVATE_IND);
	पूर्ण
पूर्ण

अटल काष्ठा FsmNode L1SFnList[] =
अणु
	अणुST_L1_F3, EV_PH_ACTIVATE, l1_activate_sपूर्ण,
	अणुST_L1_F6, EV_PH_ACTIVATE, l1_activate_noपूर्ण,
	अणुST_L1_F8, EV_PH_ACTIVATE, l1_activate_noपूर्ण,
	अणुST_L1_F3, EV_RESET_IND, l1_resetपूर्ण,
	अणुST_L1_F4, EV_RESET_IND, l1_resetपूर्ण,
	अणुST_L1_F5, EV_RESET_IND, l1_resetपूर्ण,
	अणुST_L1_F6, EV_RESET_IND, l1_resetपूर्ण,
	अणुST_L1_F7, EV_RESET_IND, l1_resetपूर्ण,
	अणुST_L1_F8, EV_RESET_IND, l1_resetपूर्ण,
	अणुST_L1_F3, EV_DEACT_CNF, l1_deact_cnfपूर्ण,
	अणुST_L1_F4, EV_DEACT_CNF, l1_deact_cnfपूर्ण,
	अणुST_L1_F5, EV_DEACT_CNF, l1_deact_cnfपूर्ण,
	अणुST_L1_F6, EV_DEACT_CNF, l1_deact_cnfपूर्ण,
	अणुST_L1_F7, EV_DEACT_CNF, l1_deact_cnfपूर्ण,
	अणुST_L1_F8, EV_DEACT_CNF, l1_deact_cnfपूर्ण,
	अणुST_L1_F6, EV_DEACT_IND, l1_deact_req_sपूर्ण,
	अणुST_L1_F7, EV_DEACT_IND, l1_deact_req_sपूर्ण,
	अणुST_L1_F8, EV_DEACT_IND, l1_deact_req_sपूर्ण,
	अणुST_L1_F3, EV_POWER_UP,  l1_घातer_up_sपूर्ण,
	अणुST_L1_F4, EV_ANYSIG_IND, l1_go_F5पूर्ण,
	अणुST_L1_F6, EV_ANYSIG_IND, l1_go_F8पूर्ण,
	अणुST_L1_F7, EV_ANYSIG_IND, l1_go_F8पूर्ण,
	अणुST_L1_F3, EV_INFO2_IND, l1_info2_indपूर्ण,
	अणुST_L1_F4, EV_INFO2_IND, l1_info2_indपूर्ण,
	अणुST_L1_F5, EV_INFO2_IND, l1_info2_indपूर्ण,
	अणुST_L1_F7, EV_INFO2_IND, l1_info2_indपूर्ण,
	अणुST_L1_F8, EV_INFO2_IND, l1_info2_indपूर्ण,
	अणुST_L1_F3, EV_INFO4_IND, l1_info4_indपूर्ण,
	अणुST_L1_F4, EV_INFO4_IND, l1_info4_indपूर्ण,
	अणुST_L1_F5, EV_INFO4_IND, l1_info4_indपूर्ण,
	अणुST_L1_F6, EV_INFO4_IND, l1_info4_indपूर्ण,
	अणुST_L1_F8, EV_INFO4_IND, l1_info4_indपूर्ण,
	अणुST_L1_F3, EV_TIMER3, l1_समयr3पूर्ण,
	अणुST_L1_F4, EV_TIMER3, l1_समयr3पूर्ण,
	अणुST_L1_F5, EV_TIMER3, l1_समयr3पूर्ण,
	अणुST_L1_F6, EV_TIMER3, l1_समयr3पूर्ण,
	अणुST_L1_F8, EV_TIMER3, l1_समयr3पूर्ण,
	अणुST_L1_F7, EV_TIMER_ACT, l1_समयr_actपूर्ण,
	अणुST_L1_F3, EV_TIMER_DEACT, l1_समयr_deactपूर्ण,
	अणुST_L1_F4, EV_TIMER_DEACT, l1_समयr_deactपूर्ण,
	अणुST_L1_F5, EV_TIMER_DEACT, l1_समयr_deactपूर्ण,
	अणुST_L1_F6, EV_TIMER_DEACT, l1_समयr_deactपूर्ण,
	अणुST_L1_F7, EV_TIMER_DEACT, l1_समयr_deactपूर्ण,
	अणुST_L1_F8, EV_TIMER_DEACT, l1_समयr_deactपूर्ण,
पूर्ण;

अटल व्योम
release_l1(काष्ठा layer1 *l1) अणु
	mISDN_FsmDelTimer(&l1->समयrX, 0);
	mISDN_FsmDelTimer(&l1->समयr3, 0);
	अगर (l1->dch)
		l1->dch->l1 = शून्य;
	module_put(THIS_MODULE);
	kमुक्त(l1);
पूर्ण

पूर्णांक
l1_event(काष्ठा layer1 *l1, u_पूर्णांक event)
अणु
	पूर्णांक		err = 0;

	अगर (!l1)
		वापस -EINVAL;
	चयन (event) अणु
	हाल HW_RESET_IND:
		mISDN_FsmEvent(&l1->l1m, EV_RESET_IND, शून्य);
		अवरोध;
	हाल HW_DEACT_IND:
		mISDN_FsmEvent(&l1->l1m, EV_DEACT_IND, शून्य);
		अवरोध;
	हाल HW_POWERUP_IND:
		mISDN_FsmEvent(&l1->l1m, EV_POWER_UP, शून्य);
		अवरोध;
	हाल HW_DEACT_CNF:
		mISDN_FsmEvent(&l1->l1m, EV_DEACT_CNF, शून्य);
		अवरोध;
	हाल ANYSIGNAL:
		mISDN_FsmEvent(&l1->l1m, EV_ANYSIG_IND, शून्य);
		अवरोध;
	हाल LOSTFRAMING:
		mISDN_FsmEvent(&l1->l1m, EV_ANYSIG_IND, शून्य);
		अवरोध;
	हाल INFO2:
		mISDN_FsmEvent(&l1->l1m, EV_INFO2_IND, शून्य);
		अवरोध;
	हाल INFO4_P8:
		mISDN_FsmEvent(&l1->l1m, EV_INFO4_IND, शून्य);
		अवरोध;
	हाल INFO4_P10:
		mISDN_FsmEvent(&l1->l1m, EV_INFO4_IND, शून्य);
		अवरोध;
	हाल PH_ACTIVATE_REQ:
		अगर (test_bit(FLG_L1_ACTIVATED, &l1->Flags))
			l1->dcb(l1->dch, PH_ACTIVATE_IND);
		अन्यथा अणु
			test_and_set_bit(FLG_L1_ACTIVATING, &l1->Flags);
			mISDN_FsmEvent(&l1->l1m, EV_PH_ACTIVATE, शून्य);
		पूर्ण
		अवरोध;
	हाल CLOSE_CHANNEL:
		release_l1(l1);
		अवरोध;
	शेष:
		अगर ((event & ~HW_TIMER3_VMASK) == HW_TIMER3_VALUE) अणु
			पूर्णांक val = event & HW_TIMER3_VMASK;

			अगर (val < 5)
				val = 5;
			अगर (val > 30)
				val = 30;
			l1->t3_value = val;
			अवरोध;
		पूर्ण
		अगर (*debug & DEBUG_L1)
			prपूर्णांकk(KERN_DEBUG "%s %x unhandled\n",
			       __func__, event);
		err = -EINVAL;
	पूर्ण
	वापस err;
पूर्ण
EXPORT_SYMBOL(l1_event);

पूर्णांक
create_l1(काष्ठा dchannel *dch, dchannel_l1callback *dcb) अणु
	काष्ठा layer1	*nl1;

	nl1 = kzalloc(माप(काष्ठा layer1), GFP_ATOMIC);
	अगर (!nl1) अणु
		prपूर्णांकk(KERN_ERR "kmalloc struct layer1 failed\n");
		वापस -ENOMEM;
	पूर्ण
	nl1->l1m.fsm = &l1fsm_s;
	nl1->l1m.state = ST_L1_F3;
	nl1->Flags = 0;
	nl1->t3_value = TIMER3_DEFAULT_VALUE;
	nl1->l1m.debug = *debug & DEBUG_L1_FSM;
	nl1->l1m.userdata = nl1;
	nl1->l1m.userपूर्णांक = 0;
	nl1->l1m.prपूर्णांकdebug = l1m_debug;
	nl1->dch = dch;
	nl1->dcb = dcb;
	mISDN_FsmInitTimer(&nl1->l1m, &nl1->समयr3);
	mISDN_FsmInitTimer(&nl1->l1m, &nl1->समयrX);
	__module_get(THIS_MODULE);
	dch->l1 = nl1;
	वापस 0;
पूर्ण
EXPORT_SYMBOL(create_l1);

पूर्णांक
l1_init(u_पूर्णांक *deb)
अणु
	debug = deb;
	l1fsm_s.state_count = L1S_STATE_COUNT;
	l1fsm_s.event_count = L1_EVENT_COUNT;
	l1fsm_s.strEvent = strL1Event;
	l1fsm_s.strState = strL1SState;
	वापस mISDN_FsmNew(&l1fsm_s, L1SFnList, ARRAY_SIZE(L1SFnList));
पूर्ण

व्योम
l1_cleanup(व्योम)
अणु
	mISDN_FsmFree(&l1fsm_s);
पूर्ण
