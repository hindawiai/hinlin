<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/******************************************************************************
 *
 *	(C)Copyright 1998,1999 SysKonnect,
 *	a business unit of Schneider & Koch & Co. Datenप्रणालीe GmbH.
 *
 *	See the file "skfddi.c" क्रम further inक्रमmation.
 *
 *	The inक्रमmation in this file is provided "AS IS" without warranty.
 *
 ******************************************************************************/

/*
	SMT Event Queue Management
*/

#समावेश "h/types.h"
#समावेश "h/fddi.h"
#समावेश "h/smc.h"

#घोषणा PRINTF(a,b,c)

/*
 * init event queue management
 */
व्योम ev_init(काष्ठा s_smc *smc)
अणु
	smc->q.ev_put = smc->q.ev_get = smc->q.ev_queue ;
पूर्ण

/*
 * add event to queue
 */
व्योम queue_event(काष्ठा s_smc *smc, पूर्णांक class, पूर्णांक event)
अणु
	PRINTF("queue class %d event %d\n",class,event) ;
	smc->q.ev_put->class = class ;
	smc->q.ev_put->event = event ;
	अगर (++smc->q.ev_put == &smc->q.ev_queue[MAX_EVENT])
		smc->q.ev_put = smc->q.ev_queue ;

	अगर (smc->q.ev_put == smc->q.ev_get) अणु
		SMT_ERR_LOG(smc,SMT_E0137, SMT_E0137_MSG) ;
	पूर्ण
पूर्ण

/*
 * समयr_event is called from HW समयr package.
 */
व्योम समयr_event(काष्ठा s_smc *smc, u_दीर्घ token)
अणु
	PRINTF("timer event class %d token %d\n",
		EV_T_CLASS(token),
		EV_T_EVENT(token)) ;
	queue_event(smc,EV_T_CLASS(token),EV_T_EVENT(token));
पूर्ण

/*
 * event dispatcher
 *	जबतक event queue is not empty
 *		get event from queue
 *		send command to state machine
 *	end
 */
व्योम ev_dispatcher(काष्ठा s_smc *smc)
अणु
	काष्ठा event_queue *ev ;	/* poपूर्णांकer पूर्णांकo queue */
	पूर्णांक		class ;

	ev = smc->q.ev_get ;
	PRINTF("dispatch get %x put %x\n",ev,smc->q.ev_put) ;
	जबतक (ev != smc->q.ev_put) अणु
		PRINTF("dispatch class %d event %d\n",ev->class,ev->event) ;
		चयन(class = ev->class) अणु
		हाल EVENT_ECM :		/* Entity Corordination  Man. */
			ecm(smc,(पूर्णांक)ev->event) ;
			अवरोध ;
		हाल EVENT_CFM :		/* Configuration Man. */
			cfm(smc,(पूर्णांक)ev->event) ;
			अवरोध ;
		हाल EVENT_RMT :		/* Ring Man. */
			rmt(smc,(पूर्णांक)ev->event) ;
			अवरोध ;
		हाल EVENT_SMT :
			smt_event(smc,(पूर्णांक)ev->event) ;
			अवरोध ;
#अगर_घोषित	CONCENTRATOR
		हाल 99 :
			समयr_test_event(smc,(पूर्णांक)ev->event) ;
			अवरोध ;
#पूर्ण_अगर
		हाल EVENT_PCMA :		/* PHY A */
		हाल EVENT_PCMB :		/* PHY B */
		शेष :
			अगर (class >= EVENT_PCMA &&
			    class < EVENT_PCMA + NUMPHYS) अणु
				pcm(smc,class - EVENT_PCMA,(पूर्णांक)ev->event) ;
				अवरोध ;
			पूर्ण
			SMT_PANIC(smc,SMT_E0121, SMT_E0121_MSG) ;
			वापस ;
		पूर्ण

		अगर (++ev == &smc->q.ev_queue[MAX_EVENT])
			ev = smc->q.ev_queue ;

		/* Renew get: it is used in queue_events to detect overruns */
		smc->q.ev_get = ev;
	पूर्ण
पूर्ण

/*
 * smt_online connects to or disconnects from the ring
 * MUST be called to initiate connection establishment
 *
 *	on	0	disconnect
 *	on	1	connect
 */
u_लघु smt_online(काष्ठा s_smc *smc, पूर्णांक on)
अणु
	queue_event(smc,EVENT_ECM,on ? EC_CONNECT : EC_DISCONNECT) ;
	ev_dispatcher(smc) ;
	वापस smc->mib.fddiSMTCF_State;
पूर्ण

/*
 * set SMT flag to value
 *	flag		flag name
 *	value		flag value
 * dump current flag setting
 */
#अगर_घोषित	CONCENTRATOR
व्योम करो_smt_flag(काष्ठा s_smc *smc, अक्षर *flag, पूर्णांक value)
अणु
#अगर_घोषित	DEBUG
	काष्ठा smt_debug	*deb;

	SK_UNUSED(smc) ;

#अगर_घोषित	DEBUG_BRD
	deb = &smc->debug;
#अन्यथा
	deb = &debug;
#पूर्ण_अगर
	अगर (!म_भेद(flag,"smt"))
		deb->d_smt = value ;
	अन्यथा अगर (!म_भेद(flag,"smtf"))
		deb->d_smtf = value ;
	अन्यथा अगर (!म_भेद(flag,"pcm"))
		deb->d_pcm = value ;
	अन्यथा अगर (!म_भेद(flag,"rmt"))
		deb->d_rmt = value ;
	अन्यथा अगर (!म_भेद(flag,"cfm"))
		deb->d_cfm = value ;
	अन्यथा अगर (!म_भेद(flag,"ecm"))
		deb->d_ecm = value ;
	म_लिखो("smt	%d\n",deb->d_smt) ;
	म_लिखो("smtf	%d\n",deb->d_smtf) ;
	म_लिखो("pcm	%d\n",deb->d_pcm) ;
	म_लिखो("rmt	%d\n",deb->d_rmt) ;
	म_लिखो("cfm	%d\n",deb->d_cfm) ;
	म_लिखो("ecm	%d\n",deb->d_ecm) ;
#पूर्ण_अगर	/* DEBUG */
पूर्ण
#पूर्ण_अगर
