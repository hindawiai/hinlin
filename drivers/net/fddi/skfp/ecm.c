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
	SMT ECM
	Entity Coordination Management
	Hardware independent state machine
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
 * 		sm_pm_bypass_req()
 * 		sm_pm_get_ls()
 * 
 * 	The following HW dependent events are required :
 *		NONE
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
#घोषणा GO_STATE(x)	(smc->mib.fddiSMTECMState = (x)|AFLAG)
#घोषणा ACTIONS_DONE()	(smc->mib.fddiSMTECMState &= ~AFLAG)
#घोषणा ACTIONS(x)	(x|AFLAG)

#घोषणा EC0_OUT		0			/* not inserted */
#घोषणा EC1_IN		1			/* inserted */
#घोषणा EC2_TRACE	2			/* tracing */
#घोषणा EC3_LEAVE	3			/* leaving the ring */
#घोषणा EC4_PATH_TEST	4			/* perक्रमming path test */
#घोषणा EC5_INSERT	5			/* bypass being turned on */
#घोषणा EC6_CHECK	6			/* checking bypass */
#घोषणा EC7_DEINSERT	7			/* bypass being turnde off */

/*
 * symbolic state names
 */
अटल स्थिर अक्षर * स्थिर ecm_states[] = अणु
	"EC0_OUT","EC1_IN","EC2_TRACE","EC3_LEAVE","EC4_PATH_TEST",
	"EC5_INSERT","EC6_CHECK","EC7_DEINSERT"
पूर्ण ;

/*
 * symbolic event names
 */
अटल स्थिर अक्षर * स्थिर ecm_events[] = अणु
	"NONE","EC_CONNECT","EC_DISCONNECT","EC_TRACE_PROP","EC_PATH_TEST",
	"EC_TIMEOUT_TD","EC_TIMEOUT_TMAX",
	"EC_TIMEOUT_IMAX","EC_TIMEOUT_INMAX","EC_TEST_DONE"
पूर्ण ;

/*
 * all Globals  are defined in smc.h
 * काष्ठा s_ecm
 */

/*
 * function declarations
 */

अटल व्योम ecm_fsm(काष्ठा s_smc *smc, पूर्णांक cmd);
अटल व्योम start_ecm_समयr(काष्ठा s_smc *smc, u_दीर्घ value, पूर्णांक event);
अटल व्योम stop_ecm_समयr(काष्ठा s_smc *smc);
अटल व्योम prop_actions(काष्ठा s_smc *smc);

/*
	init ECM state machine
	clear all ECM vars and flags
*/
व्योम ecm_init(काष्ठा s_smc *smc)
अणु
	smc->e.path_test = PT_PASSED ;
	smc->e.trace_prop = 0 ;
	smc->e.sb_flag = 0 ;
	smc->mib.fddiSMTECMState = ACTIONS(EC0_OUT) ;
	smc->e.ecm_line_state = FALSE ;
पूर्ण

/*
	ECM state machine
	called by dispatcher

	करो
		display state change
		process event
	until SM is stable
*/
व्योम ecm(काष्ठा s_smc *smc, पूर्णांक event)
अणु
	पूर्णांक	state ;

	करो अणु
		DB_ECM("ECM : state %s%s event %s",
		       smc->mib.fddiSMTECMState & AFLAG ? "ACTIONS " : "",
		       ecm_states[smc->mib.fddiSMTECMState & ~AFLAG],
		       ecm_events[event]);
		state = smc->mib.fddiSMTECMState ;
		ecm_fsm(smc,event) ;
		event = 0 ;
	पूर्ण जबतक (state != smc->mib.fddiSMTECMState) ;
	ecm_state_change(smc,(पूर्णांक)smc->mib.fddiSMTECMState) ;
पूर्ण

/*
	process ECM event
*/
अटल व्योम ecm_fsm(काष्ठा s_smc *smc, पूर्णांक cmd)
अणु
	पूर्णांक ls_a ;			/* current line state PHY A */
	पूर्णांक ls_b ;			/* current line state PHY B */
	पूर्णांक	p ;			/* ports */


	smc->mib.fddiSMTBypassPresent = sm_pm_bypass_present(smc) ;
	अगर (cmd == EC_CONNECT)
		smc->mib.fddiSMTRemoteDisconnectFlag = FALSE ;

	/* For AIX event notअगरication: */
	/* Is a disconnect  command remotely issued ? */
	अगर (cmd == EC_DISCONNECT &&
	    smc->mib.fddiSMTRemoteDisconnectFlag == TRUE) अणु
		AIX_EVENT (smc, (u_दीर्घ) CIO_HARD_FAIL, (u_दीर्घ)
			FDDI_REMOTE_DISCONNECT, smt_get_event_word(smc),
			smt_get_error_word(smc) );
	पूर्ण

	/*jd 05-Aug-1999 Bug #10419 "Port Disconnect fails at Dup MAc Cond."*/
	अगर (cmd == EC_CONNECT) अणु
		smc->e.DisconnectFlag = FALSE ;
	पूर्ण
	अन्यथा अगर (cmd == EC_DISCONNECT) अणु
		smc->e.DisconnectFlag = TRUE ;
	पूर्ण
	
	चयन(smc->mib.fddiSMTECMState) अणु
	हाल ACTIONS(EC0_OUT) :
		/*
		 * We करो not perक्रमm a path test
		 */
		smc->e.path_test = PT_PASSED ;
		smc->e.ecm_line_state = FALSE ;
		stop_ecm_समयr(smc) ;
		ACTIONS_DONE() ;
		अवरोध ;
	हाल EC0_OUT:
		/*EC01*/
		अगर (cmd == EC_CONNECT && !smc->mib.fddiSMTBypassPresent
			&& smc->e.path_test==PT_PASSED) अणु
			GO_STATE(EC1_IN) ;
			अवरोध ;
		पूर्ण
		/*EC05*/
		अन्यथा अगर (cmd == EC_CONNECT && (smc->e.path_test==PT_PASSED) &&
			smc->mib.fddiSMTBypassPresent &&
			(smc->s.sas == SMT_DAS)) अणु
			GO_STATE(EC5_INSERT) ;
			अवरोध ;
		पूर्ण
		अवरोध;
	हाल ACTIONS(EC1_IN) :
		stop_ecm_समयr(smc) ;
		smc->e.trace_prop = 0 ;
		sm_ma_control(smc,MA_TREQ) ;
		क्रम (p = 0 ; p < NUMPHYS ; p++)
			अगर (smc->mib.p[p].fddiPORTHardwarePresent)
				queue_event(smc,EVENT_PCMA+p,PC_START) ;
		ACTIONS_DONE() ;
		अवरोध ;
	हाल EC1_IN:
		/*EC12*/
		अगर (cmd == EC_TRACE_PROP) अणु
			prop_actions(smc) ;
			GO_STATE(EC2_TRACE) ;
			अवरोध ;
		पूर्ण
		/*EC13*/
		अन्यथा अगर (cmd == EC_DISCONNECT) अणु
			GO_STATE(EC3_LEAVE) ;
			अवरोध ;
		पूर्ण
		अवरोध;
	हाल ACTIONS(EC2_TRACE) :
		start_ecm_समयr(smc,MIB2US(smc->mib.fddiSMTTrace_MaxExpiration),
			EC_TIMEOUT_TMAX) ;
		ACTIONS_DONE() ;
		अवरोध ;
	हाल EC2_TRACE :
		/*EC22*/
		अगर (cmd == EC_TRACE_PROP) अणु
			prop_actions(smc) ;
			GO_STATE(EC2_TRACE) ;
			अवरोध ;
		पूर्ण
		/*EC23a*/
		अन्यथा अगर (cmd == EC_DISCONNECT) अणु
			smc->e.path_test = PT_EXITING ;
			GO_STATE(EC3_LEAVE) ;
			अवरोध ;
		पूर्ण
		/*EC23b*/
		अन्यथा अगर (smc->e.path_test == PT_PENDING) अणु
			GO_STATE(EC3_LEAVE) ;
			अवरोध ;
		पूर्ण
		/*EC23c*/
		अन्यथा अगर (cmd == EC_TIMEOUT_TMAX) अणु
			/* Trace_Max is expired */
			/* -> send AIX_EVENT */
			AIX_EVENT(smc, (u_दीर्घ) FDDI_RING_STATUS,
				(u_दीर्घ) FDDI_SMT_ERROR, (u_दीर्घ)
				FDDI_TRACE_MAX, smt_get_error_word(smc));
			smc->e.path_test = PT_PENDING ;
			GO_STATE(EC3_LEAVE) ;
			अवरोध ;
		पूर्ण
		अवरोध ;
	हाल ACTIONS(EC3_LEAVE) :
		start_ecm_समयr(smc,smc->s.ecm_td_min,EC_TIMEOUT_TD) ;
		क्रम (p = 0 ; p < NUMPHYS ; p++)
			queue_event(smc,EVENT_PCMA+p,PC_STOP) ;
		ACTIONS_DONE() ;
		अवरोध ;
	हाल EC3_LEAVE:
		/*EC30*/
		अगर (cmd == EC_TIMEOUT_TD && !smc->mib.fddiSMTBypassPresent &&
			(smc->e.path_test != PT_PENDING)) अणु
			GO_STATE(EC0_OUT) ;
			अवरोध ;
		पूर्ण
		/*EC34*/
		अन्यथा अगर (cmd == EC_TIMEOUT_TD &&
			(smc->e.path_test == PT_PENDING)) अणु
			GO_STATE(EC4_PATH_TEST) ;
			अवरोध ;
		पूर्ण
		/*EC31*/
		अन्यथा अगर (cmd == EC_CONNECT && smc->e.path_test == PT_PASSED) अणु
			GO_STATE(EC1_IN) ;
			अवरोध ;
		पूर्ण
		/*EC33*/
		अन्यथा अगर (cmd == EC_DISCONNECT &&
			smc->e.path_test == PT_PENDING) अणु
			smc->e.path_test = PT_EXITING ;
			/*
			 * stay in state - state will be left via समयout
			 */
		पूर्ण
		/*EC37*/
		अन्यथा अगर (cmd == EC_TIMEOUT_TD &&
			smc->mib.fddiSMTBypassPresent &&
			smc->e.path_test != PT_PENDING) अणु
			GO_STATE(EC7_DEINSERT) ;
			अवरोध ;
		पूर्ण
		अवरोध ;
	हाल ACTIONS(EC4_PATH_TEST) :
		stop_ecm_समयr(smc) ;
		smc->e.path_test = PT_TESTING ;
		start_ecm_समयr(smc,smc->s.ecm_test_करोne,EC_TEST_DONE) ;
		/* now perक्रमm path test ... just a simulation */
		ACTIONS_DONE() ;
		अवरोध ;
	हाल EC4_PATH_TEST :
		/* path test करोne delay */
		अगर (cmd == EC_TEST_DONE)
			smc->e.path_test = PT_PASSED ;

		अगर (smc->e.path_test == PT_FAILED)
			RS_SET(smc,RS_PATHTEST) ;

		/*EC40a*/
		अगर (smc->e.path_test == PT_FAILED &&
			!smc->mib.fddiSMTBypassPresent) अणु
			GO_STATE(EC0_OUT) ;
			अवरोध ;
		पूर्ण
		/*EC40b*/
		अन्यथा अगर (cmd == EC_DISCONNECT &&
			!smc->mib.fddiSMTBypassPresent) अणु
			GO_STATE(EC0_OUT) ;
			अवरोध ;
		पूर्ण
		/*EC41*/
		अन्यथा अगर (smc->e.path_test == PT_PASSED) अणु
			GO_STATE(EC1_IN) ;
			अवरोध ;
		पूर्ण
		/*EC47a*/
		अन्यथा अगर (smc->e.path_test == PT_FAILED &&
			smc->mib.fddiSMTBypassPresent) अणु
			GO_STATE(EC7_DEINSERT) ;
			अवरोध ;
		पूर्ण
		/*EC47b*/
		अन्यथा अगर (cmd == EC_DISCONNECT &&
			smc->mib.fddiSMTBypassPresent) अणु
			GO_STATE(EC7_DEINSERT) ;
			अवरोध ;
		पूर्ण
		अवरोध ;
	हाल ACTIONS(EC5_INSERT) :
		sm_pm_bypass_req(smc,BP_INSERT);
		start_ecm_समयr(smc,smc->s.ecm_in_max,EC_TIMEOUT_INMAX) ;
		ACTIONS_DONE() ;
		अवरोध ;
	हाल EC5_INSERT :
		/*EC56*/
		अगर (cmd == EC_TIMEOUT_INMAX) अणु
			GO_STATE(EC6_CHECK) ;
			अवरोध ;
		पूर्ण
		/*EC57*/
		अन्यथा अगर (cmd == EC_DISCONNECT) अणु
			GO_STATE(EC7_DEINSERT) ;
			अवरोध ;
		पूर्ण
		अवरोध ;
	हाल ACTIONS(EC6_CHECK) :
		/*
		 * in EC6_CHECK, we *POLL* the line state !
		 * check whether both bypass चयनes have चयनed.
		 */
		start_ecm_समयr(smc,smc->s.ecm_check_poll,0) ;
		smc->e.ecm_line_state = TRUE ;	/* flag to pcm: report Q/HLS */
		ACTIONS_DONE() ;
		अवरोध ;
	हाल EC6_CHECK :
		ls_a = sm_pm_get_ls(smc,PA) ;
		ls_b = sm_pm_get_ls(smc,PB) ;

		/*EC61*/
		अगर (((ls_a == PC_QLS) || (ls_a == PC_HLS)) &&
		    ((ls_b == PC_QLS) || (ls_b == PC_HLS)) ) अणु
			smc->e.sb_flag = FALSE ;
			smc->e.ecm_line_state = FALSE ;
			GO_STATE(EC1_IN) ;
			अवरोध ;
		पूर्ण
		/*EC66*/
		अन्यथा अगर (!smc->e.sb_flag &&
			 (((ls_a == PC_ILS) && (ls_b == PC_QLS)) ||
			  ((ls_a == PC_QLS) && (ls_b == PC_ILS))))अणु
			smc->e.sb_flag = TRUE ;
			DB_ECMN(1, "ECM : EC6_CHECK - stuck bypass");
			AIX_EVENT(smc, (u_दीर्घ) FDDI_RING_STATUS, (u_दीर्घ)
				FDDI_SMT_ERROR, (u_दीर्घ) FDDI_BYPASS_STUCK,
				smt_get_error_word(smc));
		पूर्ण
		/*EC67*/
		अन्यथा अगर (cmd == EC_DISCONNECT) अणु
			smc->e.ecm_line_state = FALSE ;
			GO_STATE(EC7_DEINSERT) ;
			अवरोध ;
		पूर्ण
		अन्यथा अणु
			/*
			 * restart poll
			 */
			start_ecm_समयr(smc,smc->s.ecm_check_poll,0) ;
		पूर्ण
		अवरोध ;
	हाल ACTIONS(EC7_DEINSERT) :
		sm_pm_bypass_req(smc,BP_DEINSERT);
		start_ecm_समयr(smc,smc->s.ecm_i_max,EC_TIMEOUT_IMAX) ;
		ACTIONS_DONE() ;
		अवरोध ;
	हाल EC7_DEINSERT:
		/*EC70*/
		अगर (cmd == EC_TIMEOUT_IMAX) अणु
			GO_STATE(EC0_OUT) ;
			अवरोध ;
		पूर्ण
		/*EC75*/
		अन्यथा अगर (cmd == EC_CONNECT && smc->e.path_test == PT_PASSED) अणु
			GO_STATE(EC5_INSERT) ;
			अवरोध ;
		पूर्ण
		अवरोध;
	शेष:
		SMT_PANIC(smc,SMT_E0107, SMT_E0107_MSG) ;
		अवरोध;
	पूर्ण
पूर्ण

#अगर_अघोषित	CONCENTRATOR
/*
 * trace propagation actions क्रम SAS & DAS
 */
अटल व्योम prop_actions(काष्ठा s_smc *smc)
अणु
	पूर्णांक	port_in = 0 ;
	पूर्णांक	port_out = 0 ;

	RS_SET(smc,RS_EVENT) ;
	चयन (smc->s.sas) अणु
	हाल SMT_SAS :
		port_in = port_out = pcm_get_s_port(smc) ;
		अवरोध ;
	हाल SMT_DAS :
		port_in = cfm_get_mac_input(smc) ;	/* PA or PB */
		port_out = cfm_get_mac_output(smc) ;	/* PA or PB */
		अवरोध ;
	हाल SMT_NAC :
		SMT_PANIC(smc,SMT_E0108, SMT_E0108_MSG) ;
		वापस ;
	पूर्ण

	DB_ECM("ECM : prop_actions - trace_prop %lu", smc->e.trace_prop);
	DB_ECM("ECM : prop_actions - in %d out %d", port_in, port_out);

	अगर (smc->e.trace_prop & ENTITY_BIT(ENTITY_MAC)) अणु
		/* trace initiatior */
		DB_ECM("ECM : initiate TRACE on PHY %c", 'A' + port_in - PA);
		queue_event(smc,EVENT_PCM+port_in,PC_TRACE) ;
	पूर्ण
	अन्यथा अगर ((smc->e.trace_prop & ENTITY_BIT(ENTITY_PHY(PA))) &&
		port_out != PA) अणु
		/* trace propagate upstream */
		DB_ECM("ECM : propagate TRACE on PHY B");
		queue_event(smc,EVENT_PCMB,PC_TRACE) ;
	पूर्ण
	अन्यथा अगर ((smc->e.trace_prop & ENTITY_BIT(ENTITY_PHY(PB))) &&
		port_out != PB) अणु
		/* trace propagate upstream */
		DB_ECM("ECM : propagate TRACE on PHY A");
		queue_event(smc,EVENT_PCMA,PC_TRACE) ;
	पूर्ण
	अन्यथा अणु
		/* संकेत trace termination */
		DB_ECM("ECM : TRACE terminated");
		smc->e.path_test = PT_PENDING ;
	पूर्ण
	smc->e.trace_prop = 0 ;
पूर्ण
#अन्यथा
/*
 * trace propagation actions क्रम Concentrator
 */
अटल व्योम prop_actions(काष्ठा s_smc *smc)
अणु
	पूर्णांक	initiator ;
	पूर्णांक	upstream ;
	पूर्णांक	p ;

	RS_SET(smc,RS_EVENT) ;
	जबतक (smc->e.trace_prop) अणु
		DB_ECM("ECM : prop_actions - trace_prop %d",
		       smc->e.trace_prop);

		अगर (smc->e.trace_prop & ENTITY_BIT(ENTITY_MAC)) अणु
			initiator = ENTITY_MAC ;
			smc->e.trace_prop &= ~ENTITY_BIT(ENTITY_MAC) ;
			DB_ECM("ECM: MAC initiates trace");
		पूर्ण
		अन्यथा अणु
			क्रम (p = NUMPHYS-1 ; p >= 0 ; p--) अणु
				अगर (smc->e.trace_prop &
					ENTITY_BIT(ENTITY_PHY(p)))
					अवरोध ;
			पूर्ण
			initiator = ENTITY_PHY(p) ;
			smc->e.trace_prop &= ~ENTITY_BIT(ENTITY_PHY(p)) ;
		पूर्ण
		upstream = cem_get_upstream(smc,initiator) ;

		अगर (upstream == ENTITY_MAC) अणु
			/* संकेत trace termination */
			DB_ECM("ECM : TRACE terminated");
			smc->e.path_test = PT_PENDING ;
		पूर्ण
		अन्यथा अणु
			/* trace propagate upstream */
			DB_ECM("ECM : propagate TRACE on PHY %d", upstream);
			queue_event(smc,EVENT_PCM+upstream,PC_TRACE) ;
		पूर्ण
	पूर्ण
पूर्ण
#पूर्ण_अगर


/*
 * SMT समयr पूर्णांकerface
 *	start ECM समयr
 */
अटल व्योम start_ecm_समयr(काष्ठा s_smc *smc, u_दीर्घ value, पूर्णांक event)
अणु
	smt_समयr_start(smc,&smc->e.ecm_समयr,value,EV_TOKEN(EVENT_ECM,event));
पूर्ण

/*
 * SMT समयr पूर्णांकerface
 *	stop ECM समयr
 */
अटल व्योम stop_ecm_समयr(काष्ठा s_smc *smc)
अणु
	अगर (smc->e.ecm_समयr.पंचांग_active)
		smt_समयr_stop(smc,&smc->e.ecm_समयr) ;
पूर्ण
