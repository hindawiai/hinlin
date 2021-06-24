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
	SMT CFM
	Configuration Management
	DAS with single MAC
*/

/*
 *	Hardware independent state machine implemantation
 *	The following बाह्यal SMT functions are referenced :
 *
 *		queue_event()
 *
 *	The following बाह्यal HW dependent functions are referenced :
 *		config_mux()
 *
 *	The following HW dependent events are required :
 *		NONE 
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
#घोषणा GO_STATE(x)	(smc->mib.fddiSMTCF_State = (x)|AFLAG)
#घोषणा ACTIONS_DONE()	(smc->mib.fddiSMTCF_State &= ~AFLAG)
#घोषणा ACTIONS(x)	(x|AFLAG)

/*
 * symbolic state names
 */
अटल स्थिर अक्षर * स्थिर cfm_states[] = अणु
	"SC0_ISOLATED","CF1","CF2","CF3","CF4",
	"SC1_WRAP_A","SC2_WRAP_B","SC5_TRHU_B","SC7_WRAP_S",
	"SC9_C_WRAP_A","SC10_C_WRAP_B","SC11_C_WRAP_S","SC4_THRU_A"
पूर्ण ;

/*
 * symbolic event names
 */
अटल स्थिर अक्षर * स्थिर cfm_events[] = अणु
	"NONE","CF_LOOP_A","CF_LOOP_B","CF_JOIN_A","CF_JOIN_B"
पूर्ण ;

/*
 * map from state to करोwnstream port type
 */
अटल स्थिर अचिन्हित अक्षर cf_to_ptype[] = अणु
	TNONE,TNONE,TNONE,TNONE,TNONE,
	TNONE,TB,TB,TS,
	TA,TB,TS,TB
पूर्ण ;

/*
 * CEM port states
 */
#घोषणा	CEM_PST_DOWN	0
#घोषणा	CEM_PST_UP	1
#घोषणा	CEM_PST_HOLD	2
/* define portstate array only क्रम A and B port */
/* Do this within the smc काष्ठाure (use in multiple cards) */

/*
 * all Globals  are defined in smc.h
 * काष्ठा s_cfm
 */

/*
 * function declarations
 */
अटल व्योम cfm_fsm(काष्ठा s_smc *smc, पूर्णांक cmd);

/*
	init CFM state machine
	clear all CFM vars and flags
*/
व्योम cfm_init(काष्ठा s_smc *smc)
अणु
	smc->mib.fddiSMTCF_State = ACTIONS(SC0_ISOLATED) ;
	smc->r.rm_join = 0 ;
	smc->r.rm_loop = 0 ;
	smc->y[PA].scrub = 0 ;
	smc->y[PB].scrub = 0 ;
	smc->y[PA].cem_pst = CEM_PST_DOWN ;
	smc->y[PB].cem_pst = CEM_PST_DOWN ;
पूर्ण

/* Some terms conditions used by the selection criteria */
#घोषणा THRU_ENABLED(smc)	(smc->y[PA].pc_mode != PM_TREE && \
				 smc->y[PB].pc_mode != PM_TREE)
/* Selection criteria क्रम the ports */
अटल व्योम selection_criteria (काष्ठा s_smc *smc, काष्ठा s_phy *phy)
अणु

	चयन (phy->mib->fddiPORTMy_Type) अणु
	हाल TA:
		अगर ( !THRU_ENABLED(smc) && smc->y[PB].cf_join ) अणु
			phy->wc_flag = TRUE ;
		पूर्ण अन्यथा अणु
			phy->wc_flag = FALSE ;
		पूर्ण

		अवरोध;
	हाल TB:
		/* take precedence over PA */
		phy->wc_flag = FALSE ;
		अवरोध;
	हाल TS:
		phy->wc_flag = FALSE ;
		अवरोध;
	हाल TM:
		phy->wc_flag = FALSE ;
		अवरोध;
	पूर्ण

पूर्ण

व्योम all_selection_criteria(काष्ठा s_smc *smc)
अणु
	काष्ठा s_phy	*phy ;
	पूर्णांक		p ;

	क्रम ( p = 0,phy = smc->y ; p < NUMPHYS; p++, phy++ ) अणु
		/* Do the selection criteria */
		selection_criteria (smc,phy);
	पूर्ण
पूर्ण

अटल व्योम cem_priv_state(काष्ठा s_smc *smc, पूर्णांक event)
/* State machine क्रम निजी PORT states: used to optimize dual homing */
अणु
	पूर्णांक	np;	/* Number of the port */
	पूर्णांक	i;

	/* Do this only in a DAS */
	अगर (smc->s.sas != SMT_DAS )
		वापस ;

	np = event - CF_JOIN;

	अगर (np != PA && np != PB) अणु
		वापस ;
	पूर्ण
	/* Change the port state according to the event (portnumber) */
	अगर (smc->y[np].cf_join) अणु
		smc->y[np].cem_pst = CEM_PST_UP ;
	पूर्ण अन्यथा अगर (!smc->y[np].wc_flag) अणु
		/* set the port to करोne only अगर it is not withheld */
		smc->y[np].cem_pst = CEM_PST_DOWN ;
	पूर्ण

	/* Don't set an hold port to करोwn */

	/* Check all ports of restart conditions */
	क्रम (i = 0 ; i < 2 ; i ++ ) अणु
		/* Check all port क्रम PORT is on hold and no withhold is करोne */
		अगर ( smc->y[i].cem_pst == CEM_PST_HOLD && !smc->y[i].wc_flag ) अणु
			smc->y[i].cem_pst = CEM_PST_DOWN;
			queue_event(smc,(पूर्णांक)(EVENT_PCM+i),PC_START) ;
		पूर्ण
		अगर ( smc->y[i].cem_pst == CEM_PST_UP && smc->y[i].wc_flag ) अणु
			smc->y[i].cem_pst = CEM_PST_HOLD;
			queue_event(smc,(पूर्णांक)(EVENT_PCM+i),PC_START) ;
		पूर्ण
		अगर ( smc->y[i].cem_pst == CEM_PST_DOWN && smc->y[i].wc_flag ) अणु
			/*
			 * The port must be restarted when the wc_flag
			 * will be reset. So set the port on hold.
			 */
			smc->y[i].cem_pst = CEM_PST_HOLD;
		पूर्ण
	पूर्ण
	वापस ;
पूर्ण

/*
	CFM state machine
	called by dispatcher

	करो
		display state change
		process event
	until SM is stable
*/
व्योम cfm(काष्ठा s_smc *smc, पूर्णांक event)
अणु
	पूर्णांक	state ;		/* remember last state */
	पूर्णांक	cond ;

	/* We will करो the following: */
	/*  - compute the variable WC_Flag क्रम every port (This is where */
	/*    we can extend the requested path checking !!) */
	/*  - करो the old (SMT 6.2 like) state machine */
	/*  - करो the resulting station states */

	all_selection_criteria (smc);

	/* We will check now whether a state transition is allowed or not */
	/*  - change the portstates */
	cem_priv_state (smc, event);

	करो अणु
		DB_CFM("CFM : state %s%s event %s",
		       smc->mib.fddiSMTCF_State & AFLAG ? "ACTIONS " : "",
		       cfm_states[smc->mib.fddiSMTCF_State & ~AFLAG],
		       cfm_events[event]);
		state = smc->mib.fddiSMTCF_State ;
		cfm_fsm(smc,event) ;
		event = 0 ;
	पूर्ण जबतक (state != smc->mib.fddiSMTCF_State) ;

#अगर_अघोषित	SLIM_SMT
	/*
	 * check peer wrap condition
	 */
	cond = FALSE ;
	अगर (	(smc->mib.fddiSMTCF_State == SC9_C_WRAP_A &&
		smc->y[PA].pc_mode == PM_PEER) 	||
		(smc->mib.fddiSMTCF_State == SC10_C_WRAP_B &&
		smc->y[PB].pc_mode == PM_PEER) 	||
		(smc->mib.fddiSMTCF_State == SC11_C_WRAP_S &&
		smc->y[PS].pc_mode == PM_PEER &&
		smc->y[PS].mib->fddiPORTNeighborType != TS ) ) अणु
			cond = TRUE ;
	पूर्ण
	अगर (cond != smc->mib.fddiSMTPeerWrapFlag)
		smt_srf_event(smc,SMT_COND_SMT_PEER_WRAP,0,cond) ;

	/*
	 * Don't ever send MAC_PATH_CHANGE events. Our MAC is hard-wired
	 * to the primary path.
	 */

#पूर्ण_अगर	/* no SLIM_SMT */

	/*
	 * set MAC port type
	 */
	smc->mib.m[MAC0].fddiMACDownstreamPORTType =
		cf_to_ptype[smc->mib.fddiSMTCF_State] ;
	cfm_state_change(smc,(पूर्णांक)smc->mib.fddiSMTCF_State) ;
पूर्ण

/*
	process CFM event
*/
/*ARGSUSED1*/
अटल व्योम cfm_fsm(काष्ठा s_smc *smc, पूर्णांक cmd)
अणु
	चयन(smc->mib.fddiSMTCF_State) अणु
	हाल ACTIONS(SC0_ISOLATED) :
		smc->mib.p[PA].fddiPORTCurrentPath = MIB_PATH_ISOLATED ;
		smc->mib.p[PB].fddiPORTCurrentPath = MIB_PATH_ISOLATED ;
		smc->mib.p[PA].fddiPORTMACPlacement = 0 ;
		smc->mib.p[PB].fddiPORTMACPlacement = 0 ;
		smc->mib.fddiSMTStationStatus = MIB_SMT_STASTA_SEPA ;
		config_mux(smc,MUX_ISOLATE) ;	/* configure PHY Mux */
		smc->r.rm_loop = FALSE ;
		smc->r.rm_join = FALSE ;
		queue_event(smc,EVENT_RMT,RM_JOIN) ;/* संकेत RMT */
		/* Don't करो the WC-Flag changing here */
		ACTIONS_DONE() ;
		DB_CFMN(1, "CFM : %s", cfm_states[smc->mib.fddiSMTCF_State]);
		अवरोध;
	हाल SC0_ISOLATED :
		/*SC07*/
		/*SAS port can be PA or PB ! */
		अगर (smc->s.sas && (smc->y[PA].cf_join || smc->y[PA].cf_loop ||
				smc->y[PB].cf_join || smc->y[PB].cf_loop)) अणु
			GO_STATE(SC11_C_WRAP_S) ;
			अवरोध ;
		पूर्ण
		/*SC01*/
		अगर ((smc->y[PA].cem_pst == CEM_PST_UP && smc->y[PA].cf_join &&
		     !smc->y[PA].wc_flag) || smc->y[PA].cf_loop) अणु
			GO_STATE(SC9_C_WRAP_A) ;
			अवरोध ;
		पूर्ण
		/*SC02*/
		अगर ((smc->y[PB].cem_pst == CEM_PST_UP && smc->y[PB].cf_join &&
		     !smc->y[PB].wc_flag) || smc->y[PB].cf_loop) अणु
			GO_STATE(SC10_C_WRAP_B) ;
			अवरोध ;
		पूर्ण
		अवरोध ;
	हाल ACTIONS(SC9_C_WRAP_A) :
		smc->mib.p[PA].fddiPORTCurrentPath = MIB_PATH_CONCATENATED ;
		smc->mib.p[PB].fddiPORTCurrentPath = MIB_PATH_ISOLATED ;
		smc->mib.p[PA].fddiPORTMACPlacement = INDEX_MAC ;
		smc->mib.p[PB].fddiPORTMACPlacement = 0 ;
		smc->mib.fddiSMTStationStatus = MIB_SMT_STASTA_CON ;
		config_mux(smc,MUX_WRAPA) ;		/* configure PHY mux */
		अगर (smc->y[PA].cf_loop) अणु
			smc->r.rm_join = FALSE ;
			smc->r.rm_loop = TRUE ;
			queue_event(smc,EVENT_RMT,RM_LOOP) ;/* संकेत RMT */
		पूर्ण
		अगर (smc->y[PA].cf_join) अणु
			smc->r.rm_loop = FALSE ;
			smc->r.rm_join = TRUE ;
			queue_event(smc,EVENT_RMT,RM_JOIN) ;/* संकेत RMT */
		पूर्ण
		ACTIONS_DONE() ;
		DB_CFMN(1, "CFM : %s", cfm_states[smc->mib.fddiSMTCF_State]);
		अवरोध ;
	हाल SC9_C_WRAP_A :
		/*SC10*/
		अगर ( (smc->y[PA].wc_flag || !smc->y[PA].cf_join) &&
		      !smc->y[PA].cf_loop ) अणु
			GO_STATE(SC0_ISOLATED) ;
			अवरोध ;
		पूर्ण
		/*SC12*/
		अन्यथा अगर ( (smc->y[PB].cf_loop && smc->y[PA].cf_join &&
			   smc->y[PA].cem_pst == CEM_PST_UP) ||
			  ((smc->y[PB].cf_loop ||
			   (smc->y[PB].cf_join &&
			    smc->y[PB].cem_pst == CEM_PST_UP)) &&
			    (smc->y[PA].pc_mode == PM_TREE ||
			     smc->y[PB].pc_mode == PM_TREE))) अणु
			smc->y[PA].scrub = TRUE ;
			GO_STATE(SC10_C_WRAP_B) ;
			अवरोध ;
		पूर्ण
		/*SC14*/
		अन्यथा अगर (!smc->s.attach_s &&
			  smc->y[PA].cf_join &&
			  smc->y[PA].cem_pst == CEM_PST_UP &&
			  smc->y[PA].pc_mode == PM_PEER && smc->y[PB].cf_join &&
			  smc->y[PB].cem_pst == CEM_PST_UP &&
			  smc->y[PB].pc_mode == PM_PEER) अणु
			smc->y[PA].scrub = TRUE ;
			smc->y[PB].scrub = TRUE ;
			GO_STATE(SC4_THRU_A) ;
			अवरोध ;
		पूर्ण
		/*SC15*/
		अन्यथा अगर ( smc->s.attach_s &&
			  smc->y[PA].cf_join &&
			  smc->y[PA].cem_pst == CEM_PST_UP &&
			  smc->y[PA].pc_mode == PM_PEER &&
			  smc->y[PB].cf_join &&
			  smc->y[PB].cem_pst == CEM_PST_UP &&
			  smc->y[PB].pc_mode == PM_PEER) अणु
			smc->y[PA].scrub = TRUE ;
			smc->y[PB].scrub = TRUE ;
			GO_STATE(SC5_THRU_B) ;
			अवरोध ;
		पूर्ण
		अवरोध ;
	हाल ACTIONS(SC10_C_WRAP_B) :
		smc->mib.p[PA].fddiPORTCurrentPath = MIB_PATH_ISOLATED ;
		smc->mib.p[PB].fddiPORTCurrentPath = MIB_PATH_CONCATENATED ;
		smc->mib.p[PA].fddiPORTMACPlacement = 0 ;
		smc->mib.p[PB].fddiPORTMACPlacement = INDEX_MAC ;
		smc->mib.fddiSMTStationStatus = MIB_SMT_STASTA_CON ;
		config_mux(smc,MUX_WRAPB) ;		/* configure PHY mux */
		अगर (smc->y[PB].cf_loop) अणु
			smc->r.rm_join = FALSE ;
			smc->r.rm_loop = TRUE ;
			queue_event(smc,EVENT_RMT,RM_LOOP) ;/* संकेत RMT */
		पूर्ण
		अगर (smc->y[PB].cf_join) अणु
			smc->r.rm_loop = FALSE ;
			smc->r.rm_join = TRUE ;
			queue_event(smc,EVENT_RMT,RM_JOIN) ;/* संकेत RMT */
		पूर्ण
		ACTIONS_DONE() ;
		DB_CFMN(1, "CFM : %s", cfm_states[smc->mib.fddiSMTCF_State]);
		अवरोध ;
	हाल SC10_C_WRAP_B :
		/*SC20*/
		अगर ( !smc->y[PB].cf_join && !smc->y[PB].cf_loop ) अणु
			GO_STATE(SC0_ISOLATED) ;
			अवरोध ;
		पूर्ण
		/*SC21*/
		अन्यथा अगर ( smc->y[PA].cf_loop && smc->y[PA].pc_mode == PM_PEER &&
			  smc->y[PB].cf_join && smc->y[PB].pc_mode == PM_PEER) अणु
			smc->y[PB].scrub = TRUE ;
			GO_STATE(SC9_C_WRAP_A) ;
			अवरोध ;
		पूर्ण
		/*SC24*/
		अन्यथा अगर (!smc->s.attach_s &&
			 smc->y[PA].cf_join && smc->y[PA].pc_mode == PM_PEER &&
			 smc->y[PB].cf_join && smc->y[PB].pc_mode == PM_PEER) अणु
			smc->y[PA].scrub = TRUE ;
			smc->y[PB].scrub = TRUE ;
			GO_STATE(SC4_THRU_A) ;
			अवरोध ;
		पूर्ण
		/*SC25*/
		अन्यथा अगर ( smc->s.attach_s &&
			 smc->y[PA].cf_join && smc->y[PA].pc_mode == PM_PEER &&
			 smc->y[PB].cf_join && smc->y[PB].pc_mode == PM_PEER) अणु
			smc->y[PA].scrub = TRUE ;
			smc->y[PB].scrub = TRUE ;
			GO_STATE(SC5_THRU_B) ;
			अवरोध ;
		पूर्ण
		अवरोध ;
	हाल ACTIONS(SC4_THRU_A) :
		smc->mib.p[PA].fddiPORTCurrentPath = MIB_PATH_THRU ;
		smc->mib.p[PB].fddiPORTCurrentPath = MIB_PATH_THRU ;
		smc->mib.p[PA].fddiPORTMACPlacement = 0 ;
		smc->mib.p[PB].fddiPORTMACPlacement = INDEX_MAC ;
		smc->mib.fddiSMTStationStatus = MIB_SMT_STASTA_THRU ;
		config_mux(smc,MUX_THRUA) ;		/* configure PHY mux */
		smc->r.rm_loop = FALSE ;
		smc->r.rm_join = TRUE ;
		queue_event(smc,EVENT_RMT,RM_JOIN) ;/* संकेत RMT */
		ACTIONS_DONE() ;
		DB_CFMN(1, "CFM : %s", cfm_states[smc->mib.fddiSMTCF_State]);
		अवरोध ;
	हाल SC4_THRU_A :
		/*SC41*/
		अगर (smc->y[PB].wc_flag || !smc->y[PB].cf_join) अणु
			smc->y[PA].scrub = TRUE ;
			GO_STATE(SC9_C_WRAP_A) ;
			अवरोध ;
		पूर्ण
		/*SC42*/
		अन्यथा अगर (!smc->y[PA].cf_join || smc->y[PA].wc_flag) अणु
			smc->y[PB].scrub = TRUE ;
			GO_STATE(SC10_C_WRAP_B) ;
			अवरोध ;
		पूर्ण
		/*SC45*/
		अन्यथा अगर (smc->s.attach_s) अणु
			smc->y[PB].scrub = TRUE ;
			GO_STATE(SC5_THRU_B) ;
			अवरोध ;
		पूर्ण
		अवरोध ;
	हाल ACTIONS(SC5_THRU_B) :
		smc->mib.p[PA].fddiPORTCurrentPath = MIB_PATH_THRU ;
		smc->mib.p[PB].fddiPORTCurrentPath = MIB_PATH_THRU ;
		smc->mib.p[PA].fddiPORTMACPlacement = INDEX_MAC ;
		smc->mib.p[PB].fddiPORTMACPlacement = 0 ;
		smc->mib.fddiSMTStationStatus = MIB_SMT_STASTA_THRU ;
		config_mux(smc,MUX_THRUB) ;		/* configure PHY mux */
		smc->r.rm_loop = FALSE ;
		smc->r.rm_join = TRUE ;
		queue_event(smc,EVENT_RMT,RM_JOIN) ;/* संकेत RMT */
		ACTIONS_DONE() ;
		DB_CFMN(1, "CFM : %s", cfm_states[smc->mib.fddiSMTCF_State]);
		अवरोध ;
	हाल SC5_THRU_B :
		/*SC51*/
		अगर (!smc->y[PB].cf_join || smc->y[PB].wc_flag) अणु
			smc->y[PA].scrub = TRUE ;
			GO_STATE(SC9_C_WRAP_A) ;
			अवरोध ;
		पूर्ण
		/*SC52*/
		अन्यथा अगर (!smc->y[PA].cf_join || smc->y[PA].wc_flag) अणु
			smc->y[PB].scrub = TRUE ;
			GO_STATE(SC10_C_WRAP_B) ;
			अवरोध ;
		पूर्ण
		/*SC54*/
		अन्यथा अगर (!smc->s.attach_s) अणु
			smc->y[PA].scrub = TRUE ;
			GO_STATE(SC4_THRU_A) ;
			अवरोध ;
		पूर्ण
		अवरोध ;
	हाल ACTIONS(SC11_C_WRAP_S) :
		smc->mib.p[PS].fddiPORTCurrentPath = MIB_PATH_CONCATENATED ;
		smc->mib.p[PS].fddiPORTMACPlacement = INDEX_MAC ;
		smc->mib.fddiSMTStationStatus = MIB_SMT_STASTA_CON ;
		config_mux(smc,MUX_WRAPS) ;		/* configure PHY mux */
		अगर (smc->y[PA].cf_loop || smc->y[PB].cf_loop) अणु
			smc->r.rm_join = FALSE ;
			smc->r.rm_loop = TRUE ;
			queue_event(smc,EVENT_RMT,RM_LOOP) ;/* संकेत RMT */
		पूर्ण
		अगर (smc->y[PA].cf_join || smc->y[PB].cf_join) अणु
			smc->r.rm_loop = FALSE ;
			smc->r.rm_join = TRUE ;
			queue_event(smc,EVENT_RMT,RM_JOIN) ;/* संकेत RMT */
		पूर्ण
		ACTIONS_DONE() ;
		DB_CFMN(1, "CFM : %s", cfm_states[smc->mib.fddiSMTCF_State]);
		अवरोध ;
	हाल SC11_C_WRAP_S :
		/*SC70*/
		अगर ( !smc->y[PA].cf_join && !smc->y[PA].cf_loop &&
		     !smc->y[PB].cf_join && !smc->y[PB].cf_loop) अणु
			GO_STATE(SC0_ISOLATED) ;
			अवरोध ;
		पूर्ण
		अवरोध ;
	शेष:
		SMT_PANIC(smc,SMT_E0106, SMT_E0106_MSG) ;
		अवरोध;
	पूर्ण
पूर्ण

/*
 * get MAC's input Port
 *	वापस :
 *		PA or PB
 */
पूर्णांक cfm_get_mac_input(काष्ठा s_smc *smc)
अणु
	वापस (smc->mib.fddiSMTCF_State == SC10_C_WRAP_B ||
		smc->mib.fddiSMTCF_State == SC5_THRU_B) ? PB : PA;
पूर्ण

/*
 * get MAC's output Port
 *	वापस :
 *		PA or PB
 */
पूर्णांक cfm_get_mac_output(काष्ठा s_smc *smc)
अणु
	वापस (smc->mib.fddiSMTCF_State == SC10_C_WRAP_B ||
		smc->mib.fddiSMTCF_State == SC4_THRU_A) ? PB : PA;
पूर्ण

अटल अक्षर path_iso[] = अणु
	0,0,	0,RES_PORT,	0,PA + INDEX_PORT,	0,PATH_ISO,
	0,0,	0,RES_MAC,	0,INDEX_MAC,		0,PATH_ISO,
	0,0,	0,RES_PORT,	0,PB + INDEX_PORT,	0,PATH_ISO
पूर्ण ;

अटल अक्षर path_wrap_a[] = अणु
	0,0,	0,RES_PORT,	0,PA + INDEX_PORT,	0,PATH_PRIM,
	0,0,	0,RES_MAC,	0,INDEX_MAC,		0,PATH_PRIM,
	0,0,	0,RES_PORT,	0,PB + INDEX_PORT,	0,PATH_ISO
पूर्ण ;

अटल अक्षर path_wrap_b[] = अणु
	0,0,	0,RES_PORT,	0,PB + INDEX_PORT,	0,PATH_PRIM,
	0,0,	0,RES_MAC,	0,INDEX_MAC,		0,PATH_PRIM,
	0,0,	0,RES_PORT,	0,PA + INDEX_PORT,	0,PATH_ISO
पूर्ण ;

अटल अक्षर path_thru[] = अणु
	0,0,	0,RES_PORT,	0,PA + INDEX_PORT,	0,PATH_PRIM,
	0,0,	0,RES_MAC,	0,INDEX_MAC,		0,PATH_PRIM,
	0,0,	0,RES_PORT,	0,PB + INDEX_PORT,	0,PATH_PRIM
पूर्ण ;

अटल अक्षर path_wrap_s[] = अणु
	0,0,	0,RES_PORT,	0,PS + INDEX_PORT,	0,PATH_PRIM,
	0,0,	0,RES_MAC,	0,INDEX_MAC,		0,PATH_PRIM,
पूर्ण ;

अटल अक्षर path_iso_s[] = अणु
	0,0,	0,RES_PORT,	0,PS + INDEX_PORT,	0,PATH_ISO,
	0,0,	0,RES_MAC,	0,INDEX_MAC,		0,PATH_ISO,
पूर्ण ;

पूर्णांक cem_build_path(काष्ठा s_smc *smc, अक्षर *to, पूर्णांक path_index)
अणु
	अक्षर	*path ;
	पूर्णांक	len ;

	चयन (smc->mib.fddiSMTCF_State) अणु
	शेष :
	हाल SC0_ISOLATED :
		path = smc->s.sas ? path_iso_s : path_iso ;
		len = smc->s.sas ? माप(path_iso_s) :  माप(path_iso) ;
		अवरोध ;
	हाल SC9_C_WRAP_A :
		path = path_wrap_a ;
		len = माप(path_wrap_a) ;
		अवरोध ;
	हाल SC10_C_WRAP_B :
		path = path_wrap_b ;
		len = माप(path_wrap_b) ;
		अवरोध ;
	हाल SC4_THRU_A :
		path = path_thru ;
		len = माप(path_thru) ;
		अवरोध ;
	हाल SC11_C_WRAP_S :
		path = path_wrap_s ;
		len = माप(path_wrap_s) ;
		अवरोध ;
	पूर्ण
	स_नकल(to,path,len) ;

	LINT_USE(path_index);

	वापस len;
पूर्ण
