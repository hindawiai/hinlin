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

#अगर_अघोषित	_SCMECM_
#घोषणा _SCMECM_

#अगर	defined(PCI) && !defined(OSDEF)
/*
 * In the हाल of the PCI bus the file osdef1st.h must be present
 */
#घोषणा	OSDEF
#पूर्ण_अगर

#अगर_घोषित	PCI
#अगर_अघोषित	SUPERNET_3
#घोषणा	SUPERNET_3
#पूर्ण_अगर
#अगर_अघोषित	TAG_MODE
#घोषणा	TAG_MODE
#पूर्ण_अगर
#पूर्ण_अगर

/*
 * include all other files in required order
 * the following files must have been included beक्रमe:
 *	types.h
 *	fddi.h
 */
#अगर_घोषित	OSDEF
#समावेश "osdef1st.h"
#पूर्ण_अगर	/* OSDEF */
#अगर_घोषित	OEM_CONCEPT
#समावेश "oemdef.h"
#पूर्ण_अगर	/* OEM_CONCEPT */
#समावेश "smt.h"
#समावेश "cmtdef.h"
#समावेश "fddimib.h"
#समावेश "targethw.h"		/* all target hw dependencies */
#समावेश "targetos.h"		/* all target os dependencies */
#अगर_घोषित	ESS
#समावेश "sba.h"
#पूर्ण_अगर

/*
 * Event Queue
 *	queue.c
 * events are class/value pairs
 *	class	is addressee, e.g. RMT, PCM etc.
 *	value	is command, e.g. line state change, ring op change etc.
 */
काष्ठा event_queue अणु
	u_लघु	class ;			/* event class */
	u_लघु	event ;			/* event value */
पूर्ण ;

/*
 * define event queue as circular buffer
 */
#अगर_घोषित	CONCENTRATOR
#घोषणा MAX_EVENT	128
#अन्यथा	/* nCONCENTRATOR */
#घोषणा MAX_EVENT	64
#पूर्ण_अगर	/* nCONCENTRATOR */

काष्ठा s_queue अणु

	काष्ठा event_queue ev_queue[MAX_EVENT];
	काष्ठा event_queue *ev_put ;
	काष्ठा event_queue *ev_get ;
पूर्ण ;

/*
 * ECM - Entity Coordination Management
 * ecm.c
 */
काष्ठा s_ecm अणु
	u_अक्षर path_test ;		/* ECM path test variable */
	u_अक्षर sb_flag ;		/* ECM stuck bypass */
	u_अक्षर DisconnectFlag ;		/* jd 05-Aug-1999 Bug #10419 
					 * ECM disconnected */
	u_अक्षर ecm_line_state ;		/* flag to dispatcher : line states */
	u_दीर्घ trace_prop ;		/* ECM Trace_Prop flag >= 16 bits !! */
	/* NUMPHYS note:
	 * this variable must have enough bits to hold all entiies in
	 * the station. So NUMPHYS may not be greater than 31.
	 */
	अक्षर	ec_pad[2] ;
	काष्ठा smt_समयr ecm_समयr ;	/* समयr */
पूर्ण ;


/*
 * RMT - Ring Management
 * rmt.c
 */
काष्ठा s_rmt अणु
	u_अक्षर dup_addr_test ;		/* state of dupl. addr. test */
	u_अक्षर da_flag ;		/* flag : duplicate address det. */
	u_अक्षर loop_avail ;		/* flag : MAC available क्रम loopback */
	u_अक्षर sm_ma_avail ;		/* flag : MAC available क्रम SMT */
	u_अक्षर no_flag ;		/* flag : ring not operational */
	u_अक्षर bn_flag ;		/* flag : MAC reached beacon state */
	u_अक्षर jm_flag ;		/* flag : jamming in NON_OP_DUP */
	u_अक्षर rm_join ;		/* CFM flag RM_Join */
	u_अक्षर rm_loop ;		/* CFM flag RM_Loop */

	दीर्घ fast_rm_join ;		/* bit mask of active ports */
	/*
	 * समयr and flags
	 */
	काष्ठा smt_समयr rmt_समयr0 ;	/* समयr 0 */
	काष्ठा smt_समयr rmt_समयr1 ;	/* समयr 1 */
	काष्ठा smt_समयr rmt_समयr2 ;	/* समयr 2 */
	u_अक्षर समयr0_exp ;		/* flag : समयr 0 expired */
	u_अक्षर समयr1_exp ;		/* flag : समयr 1 expired */
	u_अक्षर समयr2_exp ;		/* flag : समयr 2 expired */

	u_अक्षर rm_pad1;
पूर्ण ;

/*
 * CFM - Configuration Management
 * cfm.c
 * used क्रम SAS and DAS
 */
काष्ठा s_cfm अणु
	u_अक्षर cf_state;		/* CFM state machine current state */
	u_अक्षर cf_pad[3] ;
पूर्ण ;

/*
 * CEM - Configuration Element Management
 * cem.c
 * used क्रम Concentrator
 */
#अगर_घोषित	CONCENTRATOR
काष्ठा s_cem अणु
	पूर्णांक	ce_state ;	/* CEM state */
	पूर्णांक	ce_port ;	/* PA PB PM PM+1 .. */
	पूर्णांक	ce_type ;	/* TA TB TS TM */
पूर्ण ;

/*
 * linked list of CCEs in current token path
 */
काष्ठा s_c_ring अणु
	काष्ठा s_c_ring	*c_next ;
	अक्षर		c_entity ;
पूर्ण ;

काष्ठा mib_path_config अणु
	u_दीर्घ	fddimibPATHConfigSMTIndex;
	u_दीर्घ	fddimibPATHConfigPATHIndex;
	u_दीर्घ	fddimibPATHConfigTokenOrder;
	u_दीर्घ	fddimibPATHConfigResourceType;
#घोषणा SNMP_RES_TYPE_MAC	2	/* Resource is a MAC */
#घोषणा SNMP_RES_TYPE_PORT	4	/* Resource is a PORT */
	u_दीर्घ	fddimibPATHConfigResourceIndex;
	u_दीर्घ	fddimibPATHConfigCurrentPath;
#घोषणा SNMP_PATH_ISOLATED	1	/* Current path is isolated */
#घोषणा SNMP_PATH_LOCAL		2	/* Current path is local */
#घोषणा SNMP_PATH_SECONDARY	3	/* Current path is secondary */
#घोषणा SNMP_PATH_PRIMARY	4	/* Current path is primary */
#घोषणा SNMP_PATH_CONCATENATED	5	/* Current path is concatenated */
#घोषणा SNMP_PATH_THRU		6	/* Current path is thru */
पूर्ण;


#पूर्ण_अगर

/*
 * PCM connect states
 */
#घोषणा PCM_DISABLED	0
#घोषणा PCM_CONNECTING	1
#घोषणा PCM_STANDBY	2
#घोषणा PCM_ACTIVE	3

काष्ठा s_pcm अणु
	u_अक्षर	pcm_pad[3] ;
पूर्ण ;

/*
 * PHY काष्ठा
 * one per physical port
 */
काष्ठा s_phy अणु
	/* Inter Module Globals */
	काष्ठा fddi_mib_p	*mib ;

	u_अक्षर np ;		/* index 0 .. NUMPHYS */
	u_अक्षर cf_join ;
	u_अक्षर cf_loop ;
	u_अक्षर wc_flag ;	/* withhold connection flag */
	u_अक्षर pc_mode ;	/* Holds the negotiated mode of the PCM */
	u_अक्षर pc_lem_fail ;	/* flag : LCT failed */
	u_अक्षर lc_test ;
	u_अक्षर scrub ;		/* CFM flag Scrub -> PCM */
	अक्षर phy_name ;
	u_अक्षर pmd_type[2] ;	/* SK connector/transceiver type codes */
#घोषणा PMD_SK_CONN	0	/* pmd_type[PMD_SK_CONN] = Connector */
#घोषणा PMD_SK_PMD	1	/* pmd_type[PMD_SK_PMD] = Xver */
	u_अक्षर pmd_scramble ;	/* scrambler on/off */

	/* inner Module Globals */
	u_अक्षर curr_ls ;	/* current line state */
	u_अक्षर ls_flag ;
	u_अक्षर rc_flag ;
	u_अक्षर tc_flag ;
	u_अक्षर td_flag ;
	u_अक्षर bitn ;
	u_अक्षर tr_flag ;	/* trace recvd जबतक in active */
	u_अक्षर twisted ;	/* flag to indicate an A-A or B-B connection */
	u_अक्षर t_val[NUMBITS] ;	/* transmit bits क्रम संकेतing */
	u_अक्षर r_val[NUMBITS] ;	/* receive bits क्रम संकेतing */
	u_दीर्घ t_next[NUMBITS] ;
	काष्ठा smt_समयr pcm_समयr0 ;
	काष्ठा smt_समयr pcm_समयr1 ;
	काष्ठा smt_समयr pcm_समयr2 ;
	u_अक्षर समयr0_exp ;
	u_अक्षर समयr1_exp ;
	u_अक्षर समयr2_exp ;
	u_अक्षर pcm_pad1[1] ;
	पूर्णांक	cem_pst ;	/* CEM निजी state; used क्रम dual homing */
	काष्ठा lem_counter lem ;
#अगर_घोषित	AMDPLC
	काष्ठा s_plc	plc ;
#पूर्ण_अगर
पूर्ण ;

/*
 * समयr package
 * smtसमयr.c
 */
काष्ठा s_समयr अणु
	काष्ठा smt_समयr	*st_queue ;
	काष्ठा smt_समयr	st_fast ;
पूर्ण ;

/*
 * SRF types and data
 */
#घोषणा SMT_EVENT_BASE			1
#घोषणा SMT_EVENT_MAC_PATH_CHANGE	(SMT_EVENT_BASE+0)
#घोषणा SMT_EVENT_MAC_NEIGHBOR_CHANGE	(SMT_EVENT_BASE+1)
#घोषणा SMT_EVENT_PORT_PATH_CHANGE	(SMT_EVENT_BASE+2)
#घोषणा SMT_EVENT_PORT_CONNECTION	(SMT_EVENT_BASE+3)

#घोषणा SMT_IS_CONDITION(x)			((x)>=SMT_COND_BASE)

#घोषणा SMT_COND_BASE		(SMT_EVENT_PORT_CONNECTION+1)
#घोषणा SMT_COND_SMT_PEER_WRAP		(SMT_COND_BASE+0)
#घोषणा SMT_COND_SMT_HOLD		(SMT_COND_BASE+1)
#घोषणा SMT_COND_MAC_FRAME_ERROR	(SMT_COND_BASE+2)
#घोषणा SMT_COND_MAC_DUP_ADDR		(SMT_COND_BASE+3)
#घोषणा SMT_COND_MAC_NOT_COPIED		(SMT_COND_BASE+4)
#घोषणा SMT_COND_PORT_EB_ERROR		(SMT_COND_BASE+5)
#घोषणा SMT_COND_PORT_LER		(SMT_COND_BASE+6)

#घोषणा SR0_WAIT	0
#घोषणा SR1_HOLDOFF	1
#घोषणा SR2_DISABLED	2

काष्ठा s_srf अणु
	u_दीर्घ	SRThreshold ;			/* threshold value */
	u_अक्षर	RT_Flag ;			/* report transmitted flag */
	u_अक्षर	sr_state ;			/* state-machine */
	u_अक्षर	any_report ;			/* any report required */
	u_दीर्घ	TSR ;				/* समयr */
	u_लघु	ring_status ;			/* IBM ring status */
पूर्ण ;

/*
 * IBM token ring status
 */
#घोषणा RS_RES15	(1<<15)			/* reserved */
#घोषणा RS_HARDERROR	(1<<14)			/* ring करोwn */
#घोषणा RS_SOFTERROR	(1<<13)			/* sent SRF */
#घोषणा RS_BEACON	(1<<12)			/* transmitted beacon */
#घोषणा RS_PATHTEST	(1<<11)			/* path test failed */
#घोषणा RS_SELFTEST	(1<<10)			/* selftest required */
#घोषणा RS_RES9		(1<< 9)			/* reserved */
#घोषणा RS_DISCONNECT	(1<< 8)			/* remote disconnect */
#घोषणा RS_RES7		(1<< 7)			/* reserved */
#घोषणा RS_DUPADDR	(1<< 6)			/* duplicate address */
#घोषणा RS_NORINGOP	(1<< 5)			/* no ring op */
#घोषणा RS_VERSION	(1<< 4)			/* SMT version mismatch */
#घोषणा RS_STUCKBYPASSS	(1<< 3)			/* stuck bypass */
#घोषणा RS_EVENT	(1<< 2)			/* FDDI event occurred */
#घोषणा RS_RINGOPCHANGE	(1<< 1)			/* ring op changed */
#घोषणा RS_RES0		(1<< 0)			/* reserved */

#घोषणा RS_SET(smc,bit) \
	ring_status_indication(smc,smc->srf.ring_status |= bit)
#घोषणा RS_CLEAR(smc,bit)	\
	ring_status_indication(smc,smc->srf.ring_status &= ~bit)

#घोषणा RS_CLEAR_EVENT	(0xffff & ~(RS_NORINGOP))

/* Define the AIX-event-Notअगरication as null function अगर it isn't defined */
/* in the targetos.h file */
#अगर_अघोषित AIX_EVENT
#घोषणा AIX_EVENT(smc,opt0,opt1,opt2,opt3)	/* nothing */
#पूर्ण_अगर

काष्ठा s_srf_evc अणु
	u_अक्षर	evc_code ;			/* event code type */
	u_अक्षर	evc_index ;			/* index क्रम mult. instances */
	u_अक्षर	evc_rep_required ;		/* report required */
	u_लघु	evc_para ;			/* SMT Para Number */
	u_अक्षर	*evc_cond_state ;		/* condition state */
	u_अक्षर	*evc_multiple ;			/* multiple occurrence */
पूर्ण ;

/*
 * Values used by frame based services
 * smt.c
 */
#घोषणा SMT_MAX_TEST		5
#घोषणा SMT_TID_NIF		0		/* pending NIF request */
#घोषणा SMT_TID_NIF_TEST	1		/* pending NIF test */
#घोषणा SMT_TID_ECF_UNA		2		/* pending ECF UNA test */
#घोषणा SMT_TID_ECF_DNA		3		/* pending ECF DNA test */
#घोषणा SMT_TID_ECF		4		/* pending ECF test */

काष्ठा smt_values अणु
	u_दीर्घ		smt_tvu ;		/* समयr valid una */
	u_दीर्घ		smt_tvd ;		/* समयr valid dna */
	u_दीर्घ		smt_tid ;		/* transaction id */
	u_दीर्घ		pend[SMT_MAX_TEST] ;	/* TID of requests */
	u_दीर्घ		uniq_समय ;		/* unique समय stamp */
	u_लघु		uniq_ticks  ;		/* unique समय stamp */
	u_लघु		please_reconnect ;	/* flag : reconnect */
	u_दीर्घ		smt_last_lem ;
	u_दीर्घ		smt_last_notअगरy ;
	काष्ठा smt_समयr	smt_समयr ;	/* SMT NIF समयr */
	u_दीर्घ		last_tok_समय[NUMMACS];	/* token cnt emulation */
पूर्ण ;

/*
 * SMT/CMT configurable parameters
 */
#घोषणा SMT_DAS	0			/* dual attach */
#घोषणा SMT_SAS	1			/* single attach */
#घोषणा SMT_NAC	2			/* null attach concentrator */

काष्ठा smt_config अणु
	u_अक्षर	attach_s ;		/* CFM attach to secondary path */
	u_अक्षर	sas ;			/* SMT_DAS/SAS/NAC */
	u_अक्षर	build_ring_map ;	/* build ringmap अगर TRUE */
	u_अक्षर	numphys ;		/* number of active phys */
	u_अक्षर	sc_pad[1] ;

	u_दीर्घ	pcm_tb_min ;		/* PCM : TB_Min समयr value */
	u_दीर्घ	pcm_tb_max ;		/* PCM : TB_Max समयr value */
	u_दीर्घ	pcm_c_min ;		/* PCM : C_Min समयr value */
	u_दीर्घ	pcm_t_out ;		/* PCM : T_Out समयr value */
	u_दीर्घ	pcm_tl_min ;		/* PCM : TL_min समयr value */
	u_दीर्घ	pcm_lc_लघु ;		/* PCM : LC_Short समयr value */
	u_दीर्घ	pcm_lc_medium ;		/* PCM : LC_Medium समयr value */
	u_दीर्घ	pcm_lc_दीर्घ ;		/* PCM : LC_Long समयr value */
	u_दीर्घ	pcm_lc_extended ;	/* PCM : LC_Extended समयr value */
	u_दीर्घ	pcm_t_next_9 ;		/* PCM : T_Next[9] समयr value */
	u_दीर्घ	pcm_ns_max ;		/* PCM : NS_Max समयr value */

	u_दीर्घ	ecm_i_max ;		/* ECM : I_Max समयr value */
	u_दीर्घ	ecm_in_max ;		/* ECM : IN_Max समयr value */
	u_दीर्घ	ecm_td_min ;		/* ECM : TD_Min समयr */
	u_दीर्घ	ecm_test_करोne ;		/* ECM : path test करोne समयr */
	u_दीर्घ	ecm_check_poll ;	/* ECM : check bypass poller */

	u_दीर्घ	rmt_t_non_op ;		/* RMT : T_Non_OP समयr value */
	u_दीर्घ	rmt_t_stuck ;		/* RMT : T_Stuck समयr value */
	u_दीर्घ	rmt_t_direct ;		/* RMT : T_Direct समयr value */
	u_दीर्घ	rmt_t_jam ;		/* RMT : T_Jam समयr value */
	u_दीर्घ	rmt_t_announce ;	/* RMT : T_Announce समयr value */
	u_दीर्घ	rmt_t_poll ;		/* RMT : claim/beacon poller */
	u_दीर्घ  rmt_dup_mac_behavior ;  /* Flag क्रम the beavior of SMT अगर
					 * a Duplicate MAC Address was detected.
					 * FALSE: SMT will leave finally the ring
					 * TRUE:  SMT will reinstert पूर्णांकo the ring
					 */
	u_दीर्घ	mac_d_max ;		/* MAC : D_Max समयr value */

	u_दीर्घ lct_लघु ;		/* LCT : error threshold */
	u_दीर्घ lct_medium ;		/* LCT : error threshold */
	u_दीर्घ lct_दीर्घ ;		/* LCT : error threshold */
	u_दीर्घ lct_extended ;		/* LCT : error threshold */
पूर्ण ;

#अगर_घोषित	DEBUG
/*
 * Debugging काष्ठा someबार used in smc
 */
काष्ठा	smt_debug अणु
	पूर्णांक	d_smtf ;
	पूर्णांक	d_smt ;
	पूर्णांक	d_ecm ;
	पूर्णांक	d_rmt ;
	पूर्णांक	d_cfm ;
	पूर्णांक	d_pcm ;
	पूर्णांक	d_plc ;
#अगर_घोषित	ESS
	पूर्णांक	d_ess ;
#पूर्ण_अगर
#अगर_घोषित	SBA
	पूर्णांक	d_sba ;
#पूर्ण_अगर
	काष्ठा	os_debug	d_os;	/* Include specअगरic OS DEBUG काष्ठा */
पूर्ण ;

#अगर_अघोषित	DEBUG_BRD
/* all boards shall be debugged with one debug काष्ठा */
बाह्य	काष्ठा	smt_debug	debug;	/* Declaration of debug काष्ठा */
#पूर्ण_अगर	/* DEBUG_BRD */

#पूर्ण_अगर	/* DEBUG */

/*
 * the SMT Context Struct SMC
 * this काष्ठा contains ALL global variables of SMT
 */
काष्ठा s_smc अणु
	काष्ठा s_smt_os	os ;		/* os specअगरic */
	काष्ठा s_smt_hw	hw ;		/* hardware */

/*
 * NOTE: os and hw MUST BE the first two काष्ठाs
 * anything beyond hw WILL BE SET TO ZERO in smt_set_शेषs()
 */
	काष्ठा smt_config s ;		/* smt स्थिरants */
	काष्ठा smt_values sm ;		/* smt variables */
	काष्ठा s_ecm	e ;		/* ecm */
	काष्ठा s_rmt	r ;		/* rmt */
	काष्ठा s_cfm	cf ;		/* cfm/cem */
#अगर_घोषित	CONCENTRATOR
	काष्ठा s_cem	ce[NUMPHYS] ;	/* cem */
	काष्ठा s_c_ring	cr[NUMPHYS+NUMMACS] ;
#पूर्ण_अगर
	काष्ठा s_pcm	p ;		/* pcm */
	काष्ठा s_phy	y[NUMPHYS] ;	/* phy */
	काष्ठा s_queue	q ;		/* queue */
	काष्ठा s_समयr	t ;		/* समयr */
	काष्ठा s_srf srf ;		/* SRF */
	काष्ठा s_srf_evc evcs[6+NUMPHYS*4] ;
	काष्ठा fddi_mib	mib ;		/* __THE_MIB__ */
#अगर_घोषित	SBA
	काष्ठा s_sba	sba ;		/* SBA variables */
#पूर्ण_अगर
#अगर_घोषित	ESS
	काष्ठा s_ess	ess ;		/* Ess variables */
#पूर्ण_अगर
#अगर	defined(DEBUG) && defined(DEBUG_BRD)
	/* If you want all single board to be debugged separately */
	काष्ठा smt_debug	debug;	/* Declaration of debug काष्ठा */
#पूर्ण_अगर	/* DEBUG_BRD && DEBUG */
पूर्ण ;

बाह्य स्थिर काष्ठा fddi_addr fddi_broadcast;

व्योम all_selection_criteria(काष्ठा s_smc *smc);
व्योम card_stop(काष्ठा s_smc *smc);
व्योम init_board(काष्ठा s_smc *smc, u_अक्षर *mac_addr);
पूर्णांक init_fplus(काष्ठा s_smc *smc);
व्योम init_plc(काष्ठा s_smc *smc);
पूर्णांक init_smt(काष्ठा s_smc *smc, u_अक्षर *mac_addr);
व्योम mac1_irq(काष्ठा s_smc *smc, u_लघु stu, u_लघु stl);
व्योम mac2_irq(काष्ठा s_smc *smc, u_लघु code_s2u, u_लघु code_s2l);
व्योम mac3_irq(काष्ठा s_smc *smc, u_लघु code_s3u, u_लघु code_s3l);
पूर्णांक pcm_status_twisted(काष्ठा s_smc *smc);
व्योम plc1_irq(काष्ठा s_smc *smc);
व्योम plc2_irq(काष्ठा s_smc *smc);
व्योम पढ़ो_address(काष्ठा s_smc *smc, u_अक्षर *mac_addr);
व्योम समयr_irq(काष्ठा s_smc *smc);

#पूर्ण_अगर	/* _SCMECM_ */

