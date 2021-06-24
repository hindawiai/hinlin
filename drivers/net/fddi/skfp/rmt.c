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
	SMT RMT
	Ring Management
*/

/*
 * Hardware independent state machine implemantation
 * The following बाह्यal SMT functions are referenced :
 *
 * 		queue_event()
 * 		smt_समयr_start()
 * 		smt_समयr_stop()
 *
 * 	The following बाह्यal HW dependent functions are referenced :
 *		sm_ma_control()
 *		sm_mac_check_beacon_claim()
 *
 * 	The following HW dependent events are required :
 *		RM_RING_OP
 *		RM_RING_NON_OP
 *		RM_MY_BEACON
 *		RM_OTHER_BEACON
 *		RM_MY_CLAIM
 *		RM_TRT_EXP
 *		RM_VALID_CLAIM
 *
 */

#समावेश "h/types.h"
#समावेश "h/fddi.h"
#समावेश "h/smc.h"

#घोषणा KERNEL
#समावेश "h/smtstate.h"

/*
 * FSM Macros
 */
#घोषणा AFLAG	0x10
#घोषणा GO_STATE(x)	(smc->mib.m[MAC0].fddiMACRMTState = (x)|AFLAG)
#घोषणा ACTIONS_DONE()	(smc->mib.m[MAC0].fddiMACRMTState &= ~AFLAG)
#घोषणा ACTIONS(x)	(x|AFLAG)

#घोषणा RM0_ISOLATED	0
#घोषणा RM1_NON_OP	1		/* not operational */
#घोषणा RM2_RING_OP	2		/* ring operational */
#घोषणा RM3_DETECT	3		/* detect dupl addresses */
#घोषणा RM4_NON_OP_DUP	4		/* dupl. addr detected */
#घोषणा RM5_RING_OP_DUP	5		/* ring oper. with dupl. addr */
#घोषणा RM6_सूचीECTED	6		/* sending directed beacons */
#घोषणा RM7_TRACE	7		/* trace initiated */

/*
 * symbolic state names
 */
अटल स्थिर अक्षर * स्थिर rmt_states[] = अणु
	"RM0_ISOLATED","RM1_NON_OP","RM2_RING_OP","RM3_DETECT",
	"RM4_NON_OP_DUP","RM5_RING_OP_DUP","RM6_DIRECTED",
	"RM7_TRACE"
पूर्ण ;

/*
 * symbolic event names
 */
अटल स्थिर अक्षर * स्थिर rmt_events[] = अणु
	"NONE","RM_RING_OP","RM_RING_NON_OP","RM_MY_BEACON",
	"RM_OTHER_BEACON","RM_MY_CLAIM","RM_TRT_EXP","RM_VALID_CLAIM",
	"RM_JOIN","RM_LOOP","RM_DUP_ADDR","RM_ENABLE_FLAG",
	"RM_TIMEOUT_NON_OP","RM_TIMEOUT_T_STUCK",
	"RM_TIMEOUT_ANNOUNCE","RM_TIMEOUT_T_DIRECT",
	"RM_TIMEOUT_D_MAX","RM_TIMEOUT_POLL","RM_TX_STATE_CHANGE"
पूर्ण ;

/*
 * Globals
 * in काष्ठा s_rmt
 */


/*
 * function declarations
 */
अटल व्योम rmt_fsm(काष्ठा s_smc *smc, पूर्णांक cmd);
अटल व्योम start_rmt_समयr0(काष्ठा s_smc *smc, u_दीर्घ value, पूर्णांक event);
अटल व्योम start_rmt_समयr1(काष्ठा s_smc *smc, u_दीर्घ value, पूर्णांक event);
अटल व्योम start_rmt_समयr2(काष्ठा s_smc *smc, u_दीर्घ value, पूर्णांक event);
अटल व्योम stop_rmt_समयr0(काष्ठा s_smc *smc);
अटल व्योम stop_rmt_समयr1(काष्ठा s_smc *smc);
अटल व्योम stop_rmt_समयr2(काष्ठा s_smc *smc);
अटल व्योम rmt_dup_actions(काष्ठा s_smc *smc);
अटल व्योम rmt_reinsert_actions(काष्ठा s_smc *smc);
अटल व्योम rmt_leave_actions(काष्ठा s_smc *smc);
अटल व्योम rmt_new_dup_actions(काष्ठा s_smc *smc);

#अगर_अघोषित SUPERNET_3
बाह्य व्योम restart_trt_क्रम_dbcn() ;
#पूर्ण_अगर /*SUPERNET_3*/

/*
	init RMT state machine
	clear all RMT vars and flags
*/
व्योम rmt_init(काष्ठा s_smc *smc)
अणु
	smc->mib.m[MAC0].fddiMACRMTState = ACTIONS(RM0_ISOLATED) ;
	smc->r.dup_addr_test = DA_NONE ;
	smc->r.da_flag = 0 ;
	smc->mib.m[MAC0].fddiMACMA_UnitdataAvailable = FALSE ;
	smc->r.sm_ma_avail = FALSE ;
	smc->r.loop_avail = 0 ;
	smc->r.bn_flag = 0 ;
	smc->r.jm_flag = 0 ;
	smc->r.no_flag = TRUE ;
पूर्ण

/*
	RMT state machine
	called by dispatcher

	करो
		display state change
		process event
	until SM is stable
*/
व्योम rmt(काष्ठा s_smc *smc, पूर्णांक event)
अणु
	पूर्णांक	state ;

	करो अणु
		DB_RMT("RMT : state %s%s event %s",
		       smc->mib.m[MAC0].fddiMACRMTState & AFLAG ? "ACTIONS " : "",
		       rmt_states[smc->mib.m[MAC0].fddiMACRMTState & ~AFLAG],
		       rmt_events[event]);
		state = smc->mib.m[MAC0].fddiMACRMTState ;
		rmt_fsm(smc,event) ;
		event = 0 ;
	पूर्ण जबतक (state != smc->mib.m[MAC0].fddiMACRMTState) ;
	rmt_state_change(smc,(पूर्णांक)smc->mib.m[MAC0].fddiMACRMTState) ;
पूर्ण

/*
	process RMT event
*/
अटल व्योम rmt_fsm(काष्ठा s_smc *smc, पूर्णांक cmd)
अणु
	/*
	 * RM00-RM70 : from all states
	 */
	अगर (!smc->r.rm_join && !smc->r.rm_loop &&
		smc->mib.m[MAC0].fddiMACRMTState != ACTIONS(RM0_ISOLATED) &&
		smc->mib.m[MAC0].fddiMACRMTState != RM0_ISOLATED) अणु
		RS_SET(smc,RS_NORINGOP) ;
		rmt_indication(smc,0) ;
		GO_STATE(RM0_ISOLATED) ;
		वापस ;
	पूर्ण

	चयन(smc->mib.m[MAC0].fddiMACRMTState) अणु
	हाल ACTIONS(RM0_ISOLATED) :
		stop_rmt_समयr0(smc) ;
		stop_rmt_समयr1(smc) ;
		stop_rmt_समयr2(smc) ;

		/*
		 * Disable MAC.
		 */
		sm_ma_control(smc,MA_OFFLINE) ;
		smc->mib.m[MAC0].fddiMACMA_UnitdataAvailable = FALSE ;
		smc->r.loop_avail = FALSE ;
		smc->r.sm_ma_avail = FALSE ;
		smc->r.no_flag = TRUE ;
		DB_RMTN(1, "RMT : ISOLATED");
		ACTIONS_DONE() ;
		अवरोध ;
	हाल RM0_ISOLATED :
		/*RM01*/
		अगर (smc->r.rm_join || smc->r.rm_loop) अणु
			/*
			 * According to the standard the MAC must be reset
			 * here. The FORMAC will be initialized and Claim
			 * and Beacon Frames will be uploaded to the MAC.
			 * So any change of Treq will take effect NOW.
			 */
			sm_ma_control(smc,MA_RESET) ;
			GO_STATE(RM1_NON_OP) ;
			अवरोध ;
		पूर्ण
		अवरोध ;
	हाल ACTIONS(RM1_NON_OP) :
		start_rmt_समयr0(smc,smc->s.rmt_t_non_op,RM_TIMEOUT_NON_OP) ;
		stop_rmt_समयr1(smc) ;
		stop_rmt_समयr2(smc) ;
		sm_ma_control(smc,MA_BEACON) ;
		DB_RMTN(1, "RMT : RING DOWN");
		RS_SET(smc,RS_NORINGOP) ;
		smc->r.sm_ma_avail = FALSE ;
		rmt_indication(smc,0) ;
		ACTIONS_DONE() ;
		अवरोध ;
	हाल RM1_NON_OP :
		/*RM12*/
		अगर (cmd == RM_RING_OP) अणु
			RS_SET(smc,RS_RINGOPCHANGE) ;
			GO_STATE(RM2_RING_OP) ;
			अवरोध ;
		पूर्ण
		/*RM13*/
		अन्यथा अगर (cmd == RM_TIMEOUT_NON_OP) अणु
			smc->r.bn_flag = FALSE ;
			smc->r.no_flag = TRUE ;
			GO_STATE(RM3_DETECT) ;
			अवरोध ;
		पूर्ण
		अवरोध ;
	हाल ACTIONS(RM2_RING_OP) :
		stop_rmt_समयr0(smc) ;
		stop_rmt_समयr1(smc) ;
		stop_rmt_समयr2(smc) ;
		smc->r.no_flag = FALSE ;
		अगर (smc->r.rm_loop)
			smc->r.loop_avail = TRUE ;
		अगर (smc->r.rm_join) अणु
			smc->r.sm_ma_avail = TRUE ;
			अगर (smc->mib.m[MAC0].fddiMACMA_UnitdataEnable)
			smc->mib.m[MAC0].fddiMACMA_UnitdataAvailable = TRUE ;
				अन्यथा
			smc->mib.m[MAC0].fddiMACMA_UnitdataAvailable = FALSE ;
		पूर्ण
		DB_RMTN(1, "RMT : RING UP");
		RS_CLEAR(smc,RS_NORINGOP) ;
		RS_SET(smc,RS_RINGOPCHANGE) ;
		rmt_indication(smc,1) ;
		smt_stat_counter(smc,0) ;
		ACTIONS_DONE() ;
		अवरोध ;
	हाल RM2_RING_OP :
		/*RM21*/
		अगर (cmd == RM_RING_NON_OP) अणु
			smc->mib.m[MAC0].fddiMACMA_UnitdataAvailable = FALSE ;
			smc->r.loop_avail = FALSE ;
			RS_SET(smc,RS_RINGOPCHANGE) ;
			GO_STATE(RM1_NON_OP) ;
			अवरोध ;
		पूर्ण
		/*RM22a*/
		अन्यथा अगर (cmd == RM_ENABLE_FLAG) अणु
			अगर (smc->mib.m[MAC0].fddiMACMA_UnitdataEnable)
			smc->mib.m[MAC0].fddiMACMA_UnitdataAvailable = TRUE ;
				अन्यथा
			smc->mib.m[MAC0].fddiMACMA_UnitdataAvailable = FALSE ;
		पूर्ण
		/*RM25*/
		अन्यथा अगर (smc->r.dup_addr_test == DA_FAILED) अणु
			smc->mib.m[MAC0].fddiMACMA_UnitdataAvailable = FALSE ;
			smc->r.loop_avail = FALSE ;
			smc->r.da_flag = TRUE ;
			GO_STATE(RM5_RING_OP_DUP) ;
			अवरोध ;
		पूर्ण
		अवरोध ;
	हाल ACTIONS(RM3_DETECT) :
		start_rmt_समयr0(smc,smc->s.mac_d_max*2,RM_TIMEOUT_D_MAX) ;
		start_rmt_समयr1(smc,smc->s.rmt_t_stuck,RM_TIMEOUT_T_STUCK) ;
		start_rmt_समयr2(smc,smc->s.rmt_t_poll,RM_TIMEOUT_POLL) ;
		sm_mac_check_beacon_claim(smc) ;
		DB_RMTN(1, "RMT : RM3_DETECT");
		ACTIONS_DONE() ;
		अवरोध ;
	हाल RM3_DETECT :
		अगर (cmd == RM_TIMEOUT_POLL) अणु
			start_rmt_समयr2(smc,smc->s.rmt_t_poll,RM_TIMEOUT_POLL);
			sm_mac_check_beacon_claim(smc) ;
			अवरोध ;
		पूर्ण
		अगर (cmd == RM_TIMEOUT_D_MAX) अणु
			smc->r.समयr0_exp = TRUE ;
		पूर्ण
		/*
		 *jd(22-Feb-1999)
		 * We need a समय ">= 2*mac_d_max" since we had finished
		 * Claim or Beacon state. So we will restart समयr0 at
		 * every state change.
		 */
		अगर (cmd == RM_TX_STATE_CHANGE) अणु
			start_rmt_समयr0(smc,
					 smc->s.mac_d_max*2,
					 RM_TIMEOUT_D_MAX) ;
		पूर्ण
		/*RM32*/
		अगर (cmd == RM_RING_OP) अणु
			GO_STATE(RM2_RING_OP) ;
			अवरोध ;
		पूर्ण
		/*RM33a*/
		अन्यथा अगर ((cmd == RM_MY_BEACON || cmd == RM_OTHER_BEACON)
			&& smc->r.bn_flag) अणु
			smc->r.bn_flag = FALSE ;
		पूर्ण
		/*RM33b*/
		अन्यथा अगर (cmd == RM_TRT_EXP && !smc->r.bn_flag) अणु
			पूर्णांक	tx ;
			/*
			 * set bn_flag only अगर in state T4 or T5:
			 * only अगर we're the beaconer should we start the
			 * trace !
			 */
			अगर ((tx =  sm_mac_get_tx_state(smc)) == 4 || tx == 5) अणु
			DB_RMTN(2, "RMT : DETECT && TRT_EXPIRED && T4/T5");
				smc->r.bn_flag = TRUE ;
				/*
				 * If one of the upstream stations beaconed
				 * and the link to the upstream neighbor is
				 * lost we need to restart the stuck समयr to
				 * check the "stuck beacon" condition.
				 */
				start_rmt_समयr1(smc,smc->s.rmt_t_stuck,
					RM_TIMEOUT_T_STUCK) ;
			पूर्ण
			/*
			 * We करो NOT need to clear smc->r.bn_flag in हाल of
			 * not being in state T4 or T5, because the flag
			 * must be cleared in order to get in this condition.
			 */

			DB_RMTN(2, "RMT : sm_mac_get_tx_state() = %d (bn_flag = %d)",
				tx, smc->r.bn_flag);
		पूर्ण
		/*RM34a*/
		अन्यथा अगर (cmd == RM_MY_CLAIM && smc->r.समयr0_exp) अणु
			rmt_new_dup_actions(smc) ;
			GO_STATE(RM4_NON_OP_DUP) ;
			अवरोध ;
		पूर्ण
		/*RM34b*/
		अन्यथा अगर (cmd == RM_MY_BEACON && smc->r.समयr0_exp) अणु
			rmt_new_dup_actions(smc) ;
			GO_STATE(RM4_NON_OP_DUP) ;
			अवरोध ;
		पूर्ण
		/*RM34c*/
		अन्यथा अगर (cmd == RM_VALID_CLAIM) अणु
			rmt_new_dup_actions(smc) ;
			GO_STATE(RM4_NON_OP_DUP) ;
			अवरोध ;
		पूर्ण
		/*RM36*/
		अन्यथा अगर (cmd == RM_TIMEOUT_T_STUCK &&
			smc->r.rm_join && smc->r.bn_flag) अणु
			GO_STATE(RM6_सूचीECTED) ;
			अवरोध ;
		पूर्ण
		अवरोध ;
	हाल ACTIONS(RM4_NON_OP_DUP) :
		start_rmt_समयr0(smc,smc->s.rmt_t_announce,RM_TIMEOUT_ANNOUNCE);
		start_rmt_समयr1(smc,smc->s.rmt_t_stuck,RM_TIMEOUT_T_STUCK) ;
		start_rmt_समयr2(smc,smc->s.rmt_t_poll,RM_TIMEOUT_POLL) ;
		sm_mac_check_beacon_claim(smc) ;
		DB_RMTN(1, "RMT : RM4_NON_OP_DUP");
		ACTIONS_DONE() ;
		अवरोध ;
	हाल RM4_NON_OP_DUP :
		अगर (cmd == RM_TIMEOUT_POLL) अणु
			start_rmt_समयr2(smc,smc->s.rmt_t_poll,RM_TIMEOUT_POLL);
			sm_mac_check_beacon_claim(smc) ;
			अवरोध ;
		पूर्ण
		/*RM41*/
		अगर (!smc->r.da_flag) अणु
			GO_STATE(RM1_NON_OP) ;
			अवरोध ;
		पूर्ण
		/*RM44a*/
		अन्यथा अगर ((cmd == RM_MY_BEACON || cmd == RM_OTHER_BEACON) &&
			smc->r.bn_flag) अणु
			smc->r.bn_flag = FALSE ;
		पूर्ण
		/*RM44b*/
		अन्यथा अगर (cmd == RM_TRT_EXP && !smc->r.bn_flag) अणु
			पूर्णांक	tx ;
			/*
			 * set bn_flag only अगर in state T4 or T5:
			 * only अगर we're the beaconer should we start the
			 * trace !
			 */
			अगर ((tx =  sm_mac_get_tx_state(smc)) == 4 || tx == 5) अणु
			DB_RMTN(2, "RMT : NOPDUP && TRT_EXPIRED && T4/T5");
				smc->r.bn_flag = TRUE ;
				/*
				 * If one of the upstream stations beaconed
				 * and the link to the upstream neighbor is
				 * lost we need to restart the stuck समयr to
				 * check the "stuck beacon" condition.
				 */
				start_rmt_समयr1(smc,smc->s.rmt_t_stuck,
					RM_TIMEOUT_T_STUCK) ;
			पूर्ण
			/*
			 * We करो NOT need to clear smc->r.bn_flag in हाल of
			 * not being in state T4 or T5, because the flag
			 * must be cleared in order to get in this condition.
			 */

			DB_RMTN(2, "RMT : sm_mac_get_tx_state() = %d (bn_flag = %d)",
				tx, smc->r.bn_flag);
		पूर्ण
		/*RM44c*/
		अन्यथा अगर (cmd == RM_TIMEOUT_ANNOUNCE && !smc->r.bn_flag) अणु
			rmt_dup_actions(smc) ;
		पूर्ण
		/*RM45*/
		अन्यथा अगर (cmd == RM_RING_OP) अणु
			smc->r.no_flag = FALSE ;
			GO_STATE(RM5_RING_OP_DUP) ;
			अवरोध ;
		पूर्ण
		/*RM46*/
		अन्यथा अगर (cmd == RM_TIMEOUT_T_STUCK &&
			smc->r.rm_join && smc->r.bn_flag) अणु
			GO_STATE(RM6_सूचीECTED) ;
			अवरोध ;
		पूर्ण
		अवरोध ;
	हाल ACTIONS(RM5_RING_OP_DUP) :
		stop_rmt_समयr0(smc) ;
		stop_rmt_समयr1(smc) ;
		stop_rmt_समयr2(smc) ;
		DB_RMTN(1, "RMT : RM5_RING_OP_DUP");
		ACTIONS_DONE() ;
		अवरोध;
	हाल RM5_RING_OP_DUP :
		/*RM52*/
		अगर (smc->r.dup_addr_test == DA_PASSED) अणु
			smc->r.da_flag = FALSE ;
			GO_STATE(RM2_RING_OP) ;
			अवरोध ;
		पूर्ण
		/*RM54*/
		अन्यथा अगर (cmd == RM_RING_NON_OP) अणु
			smc->r.jm_flag = FALSE ;
			smc->r.bn_flag = FALSE ;
			GO_STATE(RM4_NON_OP_DUP) ;
			अवरोध ;
		पूर्ण
		अवरोध ;
	हाल ACTIONS(RM6_सूचीECTED) :
		start_rmt_समयr0(smc,smc->s.rmt_t_direct,RM_TIMEOUT_T_सूचीECT) ;
		stop_rmt_समयr1(smc) ;
		start_rmt_समयr2(smc,smc->s.rmt_t_poll,RM_TIMEOUT_POLL) ;
		sm_ma_control(smc,MA_सूचीECTED) ;
		RS_SET(smc,RS_BEACON) ;
		DB_RMTN(1, "RMT : RM6_DIRECTED");
		ACTIONS_DONE() ;
		अवरोध ;
	हाल RM6_सूचीECTED :
		/*RM63*/
		अगर (cmd == RM_TIMEOUT_POLL) अणु
			start_rmt_समयr2(smc,smc->s.rmt_t_poll,RM_TIMEOUT_POLL);
			sm_mac_check_beacon_claim(smc) ;
#अगर_अघोषित SUPERNET_3
			/* Because of problems with the Supernet II chip set
			 * sending of Directed Beacon will stop after 165ms
			 * thereक्रमe restart_trt_क्रम_dbcn(smc) will be called
			 * to prevent this.
			 */
			restart_trt_क्रम_dbcn(smc) ;
#पूर्ण_अगर /*SUPERNET_3*/
			अवरोध ;
		पूर्ण
		अगर ((cmd == RM_MY_BEACON || cmd == RM_OTHER_BEACON) &&
			!smc->r.da_flag) अणु
			smc->r.bn_flag = FALSE ;
			GO_STATE(RM3_DETECT) ;
			अवरोध ;
		पूर्ण
		/*RM64*/
		अन्यथा अगर ((cmd == RM_MY_BEACON || cmd == RM_OTHER_BEACON) &&
			smc->r.da_flag) अणु
			smc->r.bn_flag = FALSE ;
			GO_STATE(RM4_NON_OP_DUP) ;
			अवरोध ;
		पूर्ण
		/*RM67*/
		अन्यथा अगर (cmd == RM_TIMEOUT_T_सूचीECT) अणु
			GO_STATE(RM7_TRACE) ;
			अवरोध ;
		पूर्ण
		अवरोध ;
	हाल ACTIONS(RM7_TRACE) :
		stop_rmt_समयr0(smc) ;
		stop_rmt_समयr1(smc) ;
		stop_rmt_समयr2(smc) ;
		smc->e.trace_prop |= ENTITY_BIT(ENTITY_MAC) ;
		queue_event(smc,EVENT_ECM,EC_TRACE_PROP) ;
		DB_RMTN(1, "RMT : RM7_TRACE");
		ACTIONS_DONE() ;
		अवरोध ;
	हाल RM7_TRACE :
		अवरोध ;
	शेष:
		SMT_PANIC(smc,SMT_E0122, SMT_E0122_MSG) ;
		अवरोध;
	पूर्ण
पूर्ण

/*
 * (jd) RMT duplicate address actions
 * leave the ring or reinsert just as configured
 */
अटल व्योम rmt_dup_actions(काष्ठा s_smc *smc)
अणु
	अगर (smc->r.jm_flag) अणु
	पूर्ण
	अन्यथा अणु
		अगर (smc->s.rmt_dup_mac_behavior) अणु
			SMT_ERR_LOG(smc,SMT_E0138, SMT_E0138_MSG) ;
                        rmt_reinsert_actions(smc) ;
		पूर्ण
		अन्यथा अणु
			SMT_ERR_LOG(smc,SMT_E0135, SMT_E0135_MSG) ;
			rmt_leave_actions(smc) ;
		पूर्ण
	पूर्ण
पूर्ण

/*
 * Reconnect to the Ring
 */
अटल व्योम rmt_reinsert_actions(काष्ठा s_smc *smc)
अणु
	queue_event(smc,EVENT_ECM,EC_DISCONNECT) ;
	queue_event(smc,EVENT_ECM,EC_CONNECT) ;
पूर्ण

/*
 * duplicate address detected
 */
अटल व्योम rmt_new_dup_actions(काष्ठा s_smc *smc)
अणु
	smc->r.da_flag = TRUE ;
	smc->r.bn_flag = FALSE ;
	smc->r.jm_flag = FALSE ;
	/*
	 * we have three options : change address, jam or leave
	 * we leave the ring as शेष 
	 * Optionally it's possible to reinsert after leaving the Ring
	 * but this will not conक्रमm with SMT Spec.
	 */
	अगर (smc->s.rmt_dup_mac_behavior) अणु
		SMT_ERR_LOG(smc,SMT_E0138, SMT_E0138_MSG) ;
		rmt_reinsert_actions(smc) ;
	पूर्ण
	अन्यथा अणु
		SMT_ERR_LOG(smc,SMT_E0135, SMT_E0135_MSG) ;
		rmt_leave_actions(smc) ;
	पूर्ण
पूर्ण


/*
 * leave the ring
 */
अटल व्योम rmt_leave_actions(काष्ठा s_smc *smc)
अणु
	queue_event(smc,EVENT_ECM,EC_DISCONNECT) ;
	/*
	 * Note: Do NOT try again later. (with please reconnect)
	 * The station must be left from the ring!
	 */
पूर्ण

/*
 * SMT समयr पूर्णांकerface
 *	start RMT समयr 0
 */
अटल व्योम start_rmt_समयr0(काष्ठा s_smc *smc, u_दीर्घ value, पूर्णांक event)
अणु
	smc->r.समयr0_exp = FALSE ;		/* clear समयr event flag */
	smt_समयr_start(smc,&smc->r.rmt_समयr0,value,EV_TOKEN(EVENT_RMT,event));
पूर्ण

/*
 * SMT समयr पूर्णांकerface
 *	start RMT समयr 1
 */
अटल व्योम start_rmt_समयr1(काष्ठा s_smc *smc, u_दीर्घ value, पूर्णांक event)
अणु
	smc->r.समयr1_exp = FALSE ;	/* clear समयr event flag */
	smt_समयr_start(smc,&smc->r.rmt_समयr1,value,EV_TOKEN(EVENT_RMT,event));
पूर्ण

/*
 * SMT समयr पूर्णांकerface
 *	start RMT समयr 2
 */
अटल व्योम start_rmt_समयr2(काष्ठा s_smc *smc, u_दीर्घ value, पूर्णांक event)
अणु
	smc->r.समयr2_exp = FALSE ;		/* clear समयr event flag */
	smt_समयr_start(smc,&smc->r.rmt_समयr2,value,EV_TOKEN(EVENT_RMT,event));
पूर्ण

/*
 * SMT समयr पूर्णांकerface
 *	stop RMT समयr 0
 */
अटल व्योम stop_rmt_समयr0(काष्ठा s_smc *smc)
अणु
	अगर (smc->r.rmt_समयr0.पंचांग_active)
		smt_समयr_stop(smc,&smc->r.rmt_समयr0) ;
पूर्ण

/*
 * SMT समयr पूर्णांकerface
 *	stop RMT समयr 1
 */
अटल व्योम stop_rmt_समयr1(काष्ठा s_smc *smc)
अणु
	अगर (smc->r.rmt_समयr1.पंचांग_active)
		smt_समयr_stop(smc,&smc->r.rmt_समयr1) ;
पूर्ण

/*
 * SMT समयr पूर्णांकerface
 *	stop RMT समयr 2
 */
अटल व्योम stop_rmt_समयr2(काष्ठा s_smc *smc)
अणु
	अगर (smc->r.rmt_समयr2.पंचांग_active)
		smt_समयr_stop(smc,&smc->r.rmt_समयr2) ;
पूर्ण

