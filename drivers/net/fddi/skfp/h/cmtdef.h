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

#अगर_अघोषित	_CMTDEF_
#घोषणा _CMTDEF_

/* **************************************************************** */

/*
 * implementation specअगरic स्थिरants
 * MODIIFY THE FOLLOWING THREE DEFINES
 */
#घोषणा AMDPLC			/* अगर Amd PLC chip used */
#अगर_घोषित	CONC
#घोषणा NUMPHYS		12	/* 2 क्रम SAS or DAS, more क्रम Concentrator */
#अन्यथा
#अगर_घोषित	CONC_II
#घोषणा NUMPHYS		24	/* 2 क्रम SAS or DAS, more क्रम Concentrator */
#अन्यथा
#घोषणा NUMPHYS		2	/* 2 क्रम SAS or DAS, more क्रम Concentrator */
#पूर्ण_अगर
#पूर्ण_अगर
#घोषणा NUMMACS		1	/* only 1 supported at the moment */
#घोषणा NUMPATHS	2	/* primary and secondary path supported */

/*
 * DO NOT MODIFY BEYOND THIS POINT
 */

/* **************************************************************** */

#अगर	NUMPHYS > 2
#घोषणा CONCENTRATOR
#पूर्ण_अगर

/*
 * Definitions क्रम comक्रमtable LINT usage
 */
#अगर_घोषित	lपूर्णांक
#घोषणा LINT_USE(x)	(x)=(x)
#अन्यथा
#घोषणा LINT_USE(x)
#पूर्ण_अगर

#अगर_घोषित	DEBUG
#घोषणा	DB_PR(flag, fmt, ...)						\
	करो अणु अगर (flag) म_लिखो(fmt "\n", ##__VA_ARGS__); पूर्ण जबतक (0)
#अन्यथा
#घोषणा	DB_PR(flag, fmt, ...)	no_prपूर्णांकk(fmt "\n", ##__VA_ARGS__)

#पूर्ण_अगर

#अगर_घोषित DEBUG_BRD
#घोषणा DB_TEST (smc->debug)
#अन्यथा
#घोषणा DB_TEST (debug)
#पूर्ण_अगर

#घोषणा DB_ECM(fmt, ...)						\
	DB_PR((DB_TEST).d_smt & 1, fmt, ##__VA_ARGS__)
#घोषणा DB_ECMN(n, fmt, ...)						\
	DB_PR((DB_TEST).d_ecm >= (n), fmt, ##__VA_ARGS__)
#घोषणा DB_RMT(fmt, ...)						\
	DB_PR((DB_TEST).d_smt & 2, fmt, ##__VA_ARGS__)
#घोषणा DB_RMTN(n, fmt, ...)						\
	DB_PR((DB_TEST).d_rmt >= (n), fmt, ##__VA_ARGS__)
#घोषणा DB_CFM(fmt, ...)						\
	DB_PR((DB_TEST).d_smt & 4, fmt, ##__VA_ARGS__)
#घोषणा DB_CFMN(n, fmt, ...)						\
	DB_PR((DB_TEST).d_cfm >= (n), fmt, ##__VA_ARGS__)
#घोषणा DB_PCM(fmt, ...)						\
	DB_PR((DB_TEST).d_smt & 8, fmt, ##__VA_ARGS__)
#घोषणा DB_PCMN(n, fmt, ...)						\
	DB_PR((DB_TEST).d_pcm >= (n), fmt, ##__VA_ARGS__)
#घोषणा DB_SMT(fmt, ...)						\
	DB_PR((DB_TEST).d_smtf, fmt, ##__VA_ARGS__)
#घोषणा DB_SMTN(n, fmt, ...)						\
	DB_PR((DB_TEST).d_smtf >= (n), fmt, ##__VA_ARGS__)
#घोषणा DB_SBA(fmt, ...)						\
	DB_PR((DB_TEST).d_sba, fmt, ##__VA_ARGS__)
#घोषणा DB_SBAN(n, fmt, ...)						\
	DB_PR((DB_TEST).d_sba >= (n), fmt, ##__VA_ARGS__)
#घोषणा DB_ESS(fmt, ...)						\
	DB_PR((DB_TEST).d_ess, fmt, ##__VA_ARGS__)
#घोषणा DB_ESSN(n, fmt, ...)						\
	DB_PR((DB_TEST).d_ess >= (n), fmt, ##__VA_ARGS__)

#अगर_अघोषित	SS_NOT_DS
#घोषणा	SK_LOC_DECL(type,var)	type var
#अन्यथा
#घोषणा	SK_LOC_DECL(type,var)	अटल type var
#पूर्ण_अगर
/*
 * PHYs and PORTS
 * Note: Don't touch the definition of PA and PB. Those might be used
 *	by some "for" loops.
 */
#घोषणा PA		0
#घोषणा PB		1
#अगर	defined(SUPERNET_3) || defined(CONC_II)
/*
 * The port indices have to be dअगरferent,
 * because the MAC output goes through the 2. PLC
 * Conc II: It has to be the first port in the row.
 */
#घोषणा PS		0	/* Internal PLC which is the same as PA */
#अन्यथा
#घोषणा PS		1
#पूर्ण_अगर
#घोषणा PM		2		/* PM .. PA+NUM_PHYS-1 */

/*
 * PHY types - as in path descriptor 'fddiPHYType'
 */
#घोषणा TA			0	/* A port */
#घोषणा TB			1	/* B port */
#घोषणा TS			2	/* S port */
#घोषणा TM			3	/* M port */
#घोषणा TNONE			4


/*
 * indexes in MIB
 */
#घोषणा INDEX_MAC	1
#घोषणा INDEX_PATH	1
#घोषणा INDEX_PORT	1


/*
 * policies
 */
#घोषणा POLICY_AA	(1<<0)		/* reject AA */
#घोषणा POLICY_AB	(1<<1)		/* reject AB */
#घोषणा POLICY_AS	(1<<2)		/* reject AS */
#घोषणा POLICY_AM	(1<<3)		/* reject AM */
#घोषणा POLICY_BA	(1<<4)		/* reject BA */
#घोषणा POLICY_BB	(1<<5)		/* reject BB */
#घोषणा POLICY_BS	(1<<6)		/* reject BS */
#घोषणा POLICY_BM	(1<<7)		/* reject BM */
#घोषणा POLICY_SA	(1<<8)		/* reject SA */
#घोषणा POLICY_SB	(1<<9)		/* reject SB */
#घोषणा POLICY_SS	(1<<10)		/* reject SS */
#घोषणा POLICY_SM	(1<<11)		/* reject SM */
#घोषणा POLICY_MA	(1<<12)		/* reject MA */
#घोषणा POLICY_MB	(1<<13)		/* reject MB */
#घोषणा POLICY_MS	(1<<14)		/* reject MS */
#घोषणा POLICY_MM	(1<<15)		/* reject MM */

/*
 * commands
 */

/*
 * EVENTS
 * event classes
 */
#घोषणा EVENT_ECM	1		/* event class ECM */
#घोषणा EVENT_CFM	2		/* event class CFM */
#घोषणा EVENT_RMT	3		/* event class RMT */
#घोषणा EVENT_SMT	4		/* event class SMT */
#घोषणा EVENT_PCM	5		/* event class PCM */
#घोषणा EVENT_PCMA	5		/* event class PCMA */
#घोषणा EVENT_PCMB	6		/* event class PCMB */

/* WARNING :
 * EVENT_PCM* must be last in the above list
 * अगर more than two ports are used, EVENT_PCM .. EVENT_PCMA+NUM_PHYS-1
 * are used !
 */

#घोषणा EV_TOKEN(class,event)	(((u_दीर्घ)(class)<<16L)|((u_दीर्घ)(event)))
#घोषणा EV_T_CLASS(token)	((पूर्णांक)((token)>>16)&0xffff)
#घोषणा EV_T_EVENT(token)	((पूर्णांक)(token)&0xffff)

/*
 * ECM events
 */
#घोषणा EC_CONNECT	1		/* connect request */
#घोषणा EC_DISCONNECT	2		/* disconnect request */
#घोषणा EC_TRACE_PROP	3		/* trace propagation */
#घोषणा EC_PATH_TEST	4		/* path test */
#घोषणा EC_TIMEOUT_TD	5		/* समयr TD_min */
#घोषणा EC_TIMEOUT_TMAX	6		/* समयr trace_max */
#घोषणा EC_TIMEOUT_IMAX	7		/* समयr I_max */
#घोषणा EC_TIMEOUT_INMAX 8		/* समयr IN_max */
#घोषणा EC_TEST_DONE	9		/* path test करोne */

/*
 * CFM events
 */
#घोषणा CF_LOOP		1		/* cf_loop flag from PCM */
#घोषणा CF_LOOP_A	1		/* cf_loop flag from PCM */
#घोषणा CF_LOOP_B	2		/* cf_loop flag from PCM */
#घोषणा CF_JOIN		3		/* cf_join flag from PCM */
#घोषणा CF_JOIN_A	3		/* cf_join flag from PCM */
#घोषणा CF_JOIN_B	4		/* cf_join flag from PCM */

/*
 * PCM events
 */
#घोषणा PC_START		1
#घोषणा PC_STOP			2
#घोषणा PC_LOOP			3
#घोषणा PC_JOIN			4
#घोषणा PC_SIGNAL		5
#घोषणा PC_REJECT		6
#घोषणा PC_MAINT    		7
#घोषणा PC_TRACE		8
#घोषणा PC_PDR			9
#घोषणा PC_ENABLE		10
#घोषणा PC_DISABLE		11

/*
 * must be ordered as in LineStateType
 */
#घोषणा PC_QLS			12
#घोषणा PC_ILS			13
#घोषणा PC_MLS			14
#घोषणा PC_HLS			15
#घोषणा PC_LS_PDR		16
#घोषणा PC_LS_NONE		17
#घोषणा LS2MIB(x)	((x)-PC_QLS)
#घोषणा MIB2LS(x)	((x)+PC_QLS)

#घोषणा PC_TIMEOUT_TB_MAX	18	/* समयr TB_max */
#घोषणा PC_TIMEOUT_TB_MIN	19	/* समयr TB_min */
#घोषणा PC_TIMEOUT_C_MIN	20	/* समयr C_Min */
#घोषणा PC_TIMEOUT_T_OUT	21	/* समयr T_Out */
#घोषणा PC_TIMEOUT_TL_MIN	22	/* समयr TL_Min */
#घोषणा PC_TIMEOUT_T_NEXT	23	/* समयr t_next[] */
#घोषणा PC_TIMEOUT_LCT		24
#घोषणा PC_NSE			25	/* NOISE hardware समयr */
#घोषणा PC_LEM			26	/* LEM करोne */

/*
 * RMT events				  meaning		from
 */
#घोषणा RM_RING_OP	1		/* ring operational	MAC	*/
#घोषणा RM_RING_NON_OP	2		/* ring not operational	MAC	*/
#घोषणा RM_MY_BEACON	3		/* recvd my beacon	MAC	*/
#घोषणा RM_OTHER_BEACON	4		/* recvd other beacon	MAC	*/
#घोषणा RM_MY_CLAIM	5		/* recvd my claim	MAC	*/
#घोषणा RM_TRT_EXP	6		/* TRT exp		MAC	*/
#घोषणा RM_VALID_CLAIM	7		/* claim from dup addr	MAC	*/
#घोषणा RM_JOIN		8		/* संकेत rm_join	CFM	*/
#घोषणा RM_LOOP		9		/* संकेत rm_loop	CFM	*/
#घोषणा RM_DUP_ADDR	10		/* dup_addr_test hange	SMT-NIF	*/
#घोषणा RM_ENABLE_FLAG	11		/* enable flag */

#घोषणा RM_TIMEOUT_NON_OP	12	/* समयout T_Non_OP	*/
#घोषणा RM_TIMEOUT_T_STUCK	13	/* समयout T_Stuck	*/
#घोषणा RM_TIMEOUT_ANNOUNCE	14	/* समयout T_Announce	*/
#घोषणा RM_TIMEOUT_T_सूचीECT	15	/* समयout T_Direct	*/
#घोषणा RM_TIMEOUT_D_MAX	16	/* समयout D_Max	*/
#घोषणा RM_TIMEOUT_POLL		17	/* claim/beacon poller	*/
#घोषणा RM_TX_STATE_CHANGE	18	/* To restart समयr क्रम D_Max */

/*
 * SMT events
 */
#घोषणा SM_TIMER	1		/* समयr */
#घोषणा SM_FAST		2		/* smt_क्रमce_irq */

/* PC modes */
#घोषणा PM_NONE		0
#घोषणा PM_PEER		1
#घोषणा PM_TREE		2

/*
 * PCM withhold codes
 * MIB PC-WithholdType ENUM
 */
#घोषणा PC_WH_NONE	0		/* ok */
#घोषणा PC_WH_M_M	1		/* M to M */
#घोषणा PC_WH_OTHER	2		/* other incompatible phys */
#घोषणा PC_WH_PATH	3		/* path not available */
/*
 * LCT duration
 */
#घोषणा LC_SHORT	1		/* लघु LCT */
#घोषणा LC_MEDIUM	2		/* medium LCT */
#घोषणा LC_LONG		3		/* दीर्घ LCT */
#घोषणा LC_EXTENDED	4		/* extended LCT */

/*
 * path_test values
 */
#घोषणा PT_NONE		0
#घोषणा PT_TESTING	1		/* test is running */
#घोषणा PT_PASSED	2		/* test passed */
#घोषणा PT_FAILED	3		/* test failed */
#घोषणा PT_PENDING	4		/* path test follows */
#घोषणा PT_EXITING	5		/* disconnected जबतक in trace/leave */

/*
 * duplicate address test
 * MIB DupAddressTest ENUM
 */
#घोषणा DA_NONE		0		/* 		*/
#घोषणा DA_PASSED	1		/* test passed */
#घोषणा DA_FAILED	2		/* test failed */


/*
 * optical bypass
 */
#घोषणा BP_DEINSERT	0		/* disable bypass */
#घोषणा BP_INSERT	1		/* enable bypass */

/*
 * ODL enable/disable
 */
#घोषणा PM_TRANSMIT_DISABLE	0	/* disable xmit */
#घोषणा PM_TRANSMIT_ENABLE	1	/* enable xmit */

/*
 * parameter क्रम config_mux
 * note : number is index in config_endec table !
 */
#घोषणा MUX_THRUA	0		/* through A */
#घोषणा MUX_THRUB	1		/* through B */
#घोषणा MUX_WRAPA	2		/* wrap A */
#घोषणा MUX_WRAPB	3		/* wrap B */
#घोषणा MUX_ISOLATE	4		/* isolated */
#घोषणा MUX_WRAPS	5		/* SAS */

/*
 * MAC control
 */
#घोषणा MA_RESET	0
#घोषणा MA_BEACON	1
#घोषणा MA_CLAIM	2
#घोषणा MA_सूचीECTED	3		/* directed beacon */
#घोषणा MA_TREQ		4		/* change T_Req */
#घोषणा MA_OFFLINE	5		/* चयन MAC to offline */


/*
 * trace prop
 * bit map क्रम trace propagation
 */
#घोषणा ENTITY_MAC	(NUMPHYS)
#घोषणा ENTITY_PHY(p)	(p)
#घोषणा ENTITY_BIT(m)	(1<<(m))

/*
 * Resource Tag Types
 */
#घोषणा PATH_ISO	0	/* isolated */
#घोषणा PATH_PRIM	3	/* primary path */
#घोषणा PATH_THRU	5	/* through path */

#घोषणा RES_MAC		2	/* resource type MAC */
#घोषणा RES_PORT	4	/* resource type PORT */


/*
 * CFM state
 * oops: MUST MATCH CF-StateType in SMT7.2 !
 */
#घोषणा SC0_ISOLATED	0		/* isolated */
#घोषणा SC1_WRAP_A	5		/* wrap A (not used) */
#घोषणा SC2_WRAP_B	6		/* wrap B (not used) */
#घोषणा SC4_THRU_A	12		/* through A */
#घोषणा SC5_THRU_B	7		/* through B (used in SMT 6.2) */
#घोषणा SC7_WRAP_S	8		/* SAS (not used) */
#घोषणा SC9_C_WRAP_A	9		/* c wrap A */
#घोषणा SC10_C_WRAP_B	10		/* c wrap B */
#घोषणा SC11_C_WRAP_S	11		/* c wrap S */

/*
 * convert MIB समय in units of 80nS to uS
 */
#घोषणा MIB2US(t)		((t)/12)
#घोषणा SEC2MIB(s)	((s)*12500000L)
/*
 * SMT समयr
 */
काष्ठा smt_समयr अणु
	काष्ठा smt_समयr	*पंचांग_next ;	/* linked list */
	काष्ठा s_smc		*पंचांग_smc ;	/* poपूर्णांकer to context */
	u_दीर्घ			पंचांग_delta ;	/* delta समय */
	u_दीर्घ			पंचांग_token ;	/* token value */
	u_लघु			पंचांग_active ;	/* flag : active/inactive */
	u_लघु			पंचांग_pad ;	/* pad field */
पूर्ण ;

/*
 * communication काष्ठाures
 */
काष्ठा mac_parameter अणु
	u_दीर्घ	t_neg ;		/* T_Neg parameter */
	u_दीर्घ	t_pri ;		/* T_Pri रेजिस्टर in MAC */
पूर्ण ;

/*
 * MAC counters
 */
काष्ठा mac_counter अणु
	u_दीर्घ	mac_nobuf_counter ;	/* MAC SW counter: no buffer */
	u_दीर्घ	mac_r_restart_counter ;	/* MAC SW counter: rx restarted */
पूर्ण ;

/*
 * para काष्ठा context क्रम SMT parameters
 */
काष्ठा s_pcon अणु
	पूर्णांक	pc_len ;
	पूर्णांक	pc_err ;
	पूर्णांक	pc_badset ;
	व्योम	*pc_p ;
पूर्ण ;

/*
 * link error monitor
 */
#घोषणा LEM_AVG	5
काष्ठा lem_counter अणु
#अगर_घोषित	AM29K
	पूर्णांक	lem_on	;
	u_दीर्घ	lem_errors ;
	u_दीर्घ	lem_symbols ;
	u_दीर्घ	lem_tsymbols ;
	पूर्णांक	lem_s_count ;
	पूर्णांक	lem_n_s ;
	पूर्णांक	lem_values ;
	पूर्णांक	lem_index ;
	पूर्णांक	lem_avg_ber[LEM_AVG] ;
	पूर्णांक	lem_sum ;
#अन्यथा
	u_लघु	lem_भग्न_ber ;		/* 10E-nn bit error rate */
	u_दीर्घ	lem_errors ;		/* accumulated error count */
	u_लघु	lem_on	;
#पूर्ण_अगर
पूर्ण ;

#घोषणा NUMBITS	10

#अगर_घोषित	AMDPLC

/*
 * PLC state table
 */
काष्ठा s_plc अणु
	u_लघु	p_state ;		/* current state */
	u_लघु	p_bits ;		/* number of bits to send */
	u_लघु	p_start ;		/* first bit pos */
	u_लघु	p_pad ;			/* padding क्रम alignment */
	u_दीर्घ soft_err ;		/* error counter */
	u_दीर्घ parity_err ;		/* error counter */
	u_दीर्घ ebuf_err ;		/* error counter */
	u_दीर्घ ebuf_cont ;		/* continuous error counter */
	u_दीर्घ phyinv ;			/* error counter */
	u_दीर्घ vsym_ctr ;		/* error counter */
	u_दीर्घ mini_ctr ;		/* error counter */
	u_दीर्घ tpc_exp ;		/* error counter */
	u_दीर्घ np_err ;			/* error counter */
	u_दीर्घ b_pcs ;			/* error counter */
	u_दीर्घ b_tpc ;			/* error counter */
	u_दीर्घ b_tne ;			/* error counter */
	u_दीर्घ b_qls ;			/* error counter */
	u_दीर्घ b_ils ;			/* error counter */
	u_दीर्घ b_hls ;			/* error counter */
पूर्ण ;
#पूर्ण_अगर

#अगर_घोषित	PROTOTYP_INC
#समावेश "fddi/driver.pro"
#अन्यथा	/* PROTOTYP_INC */
/*
 * function prototypes
 */
#समावेश "mbuf.h"	/* Type definitions क्रम MBUFs */
#समावेश "smtstate.h"	/* काष्ठा smt_state */

व्योम hwt_restart(काष्ठा s_smc *smc);	/* hwt.c */
SMbuf *smt_build_frame(काष्ठा s_smc *smc, पूर्णांक class, पूर्णांक type,
		       पूर्णांक length);	/* smt.c */
SMbuf *smt_get_mbuf(काष्ठा s_smc *smc);	/* drvsr.c */
व्योम *sm_to_para(काष्ठा s_smc *smc, काष्ठा smt_header *sm,
		 पूर्णांक para);		/* smt.c */

#अगर_अघोषित SK_UNUSED
#घोषणा SK_UNUSED(var)		(व्योम)(var)
#पूर्ण_अगर

व्योम queue_event(काष्ठा s_smc *smc, पूर्णांक class, पूर्णांक event);
व्योम ecm(काष्ठा s_smc *smc, पूर्णांक event);
व्योम ecm_init(काष्ठा s_smc *smc);
व्योम rmt(काष्ठा s_smc *smc, पूर्णांक event);
व्योम rmt_init(काष्ठा s_smc *smc);
व्योम pcm(काष्ठा s_smc *smc, स्थिर पूर्णांक np, पूर्णांक event);
व्योम pcm_init(काष्ठा s_smc *smc);
व्योम cfm(काष्ठा s_smc *smc, पूर्णांक event);
व्योम cfm_init(काष्ठा s_smc *smc);
व्योम smt_समयr_start(काष्ठा s_smc *smc, काष्ठा smt_समयr *समयr, u_दीर्घ समय,
		     u_दीर्घ token);
व्योम smt_समयr_stop(काष्ठा s_smc *smc, काष्ठा smt_समयr *समयr);
व्योम pcm_status_state(काष्ठा s_smc *smc, पूर्णांक np, पूर्णांक *type, पूर्णांक *state,
		      पूर्णांक *remote, पूर्णांक *mac);
व्योम plc_config_mux(काष्ठा s_smc *smc, पूर्णांक mux);
व्योम sm_lem_evaluate(काष्ठा s_smc *smc);
व्योम mac_update_counter(काष्ठा s_smc *smc);
व्योम sm_ma_control(काष्ठा s_smc *smc, पूर्णांक mode);
व्योम sm_mac_check_beacon_claim(काष्ठा s_smc *smc);
व्योम config_mux(काष्ठा s_smc *smc, पूर्णांक mux);
व्योम smt_agent_init(काष्ठा s_smc *smc);
व्योम smt_समयr_init(काष्ठा s_smc *smc);
व्योम smt_received_pack(काष्ठा s_smc *smc, SMbuf *mb, पूर्णांक fs);
व्योम smt_add_para(काष्ठा s_smc *smc, काष्ठा s_pcon *pcon, u_लघु para,
		  पूर्णांक index, पूर्णांक local);
व्योम smt_swap_para(काष्ठा smt_header *sm, पूर्णांक len, पूर्णांक direction);
व्योम ev_init(काष्ठा s_smc *smc);
व्योम hwt_init(काष्ठा s_smc *smc);
u_दीर्घ hwt_पढ़ो(काष्ठा s_smc *smc);
व्योम hwt_stop(काष्ठा s_smc *smc);
व्योम hwt_start(काष्ठा s_smc *smc, u_दीर्घ समय);
व्योम smt_send_mbuf(काष्ठा s_smc *smc, SMbuf *mb, पूर्णांक fc);
व्योम smt_मुक्त_mbuf(काष्ठा s_smc *smc, SMbuf *mb);
व्योम sm_pm_bypass_req(काष्ठा s_smc *smc, पूर्णांक mode);
व्योम rmt_indication(काष्ठा s_smc *smc, पूर्णांक i);
व्योम cfm_state_change(काष्ठा s_smc *smc, पूर्णांक c_state);

#अगर defined(DEBUG) || !defined(NO_SMT_PANIC)
व्योम smt_panic(काष्ठा s_smc *smc, अक्षर *text);
#अन्यथा
#घोषणा	smt_panic(smc,text)
#पूर्ण_अगर /* DEBUG || !NO_SMT_PANIC */

व्योम smt_stat_counter(काष्ठा s_smc *smc, पूर्णांक stat);
व्योम smt_समयr_poll(काष्ठा s_smc *smc);
u_दीर्घ smt_get_समय(व्योम);
u_दीर्घ smt_get_tid(काष्ठा s_smc *smc);
व्योम smt_समयr_करोne(काष्ठा s_smc *smc);
व्योम smt_fixup_mib(काष्ठा s_smc *smc);
व्योम smt_reset_शेषs(काष्ठा s_smc *smc, पूर्णांक level);
व्योम smt_agent_task(काष्ठा s_smc *smc);
पूर्णांक smt_check_para(काष्ठा s_smc *smc, काष्ठा smt_header *sm,
		   स्थिर u_लघु list[]);
व्योम driver_get_bia(काष्ठा s_smc *smc, काष्ठा fddi_addr *bia_addr);

#अगर_घोषित SUPERNET_3
व्योम drv_reset_indication(काष्ठा s_smc *smc);
#पूर्ण_अगर	/* SUPERNET_3 */

व्योम smt_start_watchकरोg(काष्ठा s_smc *smc);
व्योम smt_event(काष्ठा s_smc *smc, पूर्णांक event);
व्योम समयr_event(काष्ठा s_smc *smc, u_दीर्घ token);
व्योम ev_dispatcher(काष्ठा s_smc *smc);
व्योम pcm_get_state(काष्ठा s_smc *smc, काष्ठा smt_state *state);
व्योम ecm_state_change(काष्ठा s_smc *smc, पूर्णांक e_state);
पूर्णांक sm_pm_bypass_present(काष्ठा s_smc *smc);
व्योम pcm_state_change(काष्ठा s_smc *smc, पूर्णांक plc, पूर्णांक p_state);
व्योम rmt_state_change(काष्ठा s_smc *smc, पूर्णांक r_state);
पूर्णांक sm_pm_get_ls(काष्ठा s_smc *smc, पूर्णांक phy);
पूर्णांक pcm_get_s_port(काष्ठा s_smc *smc);
पूर्णांक pcm_rooted_station(काष्ठा s_smc *smc);
पूर्णांक cfm_get_mac_input(काष्ठा s_smc *smc);
पूर्णांक cfm_get_mac_output(काष्ठा s_smc *smc);
पूर्णांक cem_build_path(काष्ठा s_smc *smc, अक्षर *to, पूर्णांक path_index);
पूर्णांक sm_mac_get_tx_state(काष्ठा s_smc *smc);
अक्षर *get_pcmstate(काष्ठा s_smc *smc, पूर्णांक np);
पूर्णांक smt_action(काष्ठा s_smc *smc, पूर्णांक class, पूर्णांक code, पूर्णांक index);
u_लघु smt_online(काष्ठा s_smc *smc, पूर्णांक on);
व्योम smt_क्रमce_irq(काष्ठा s_smc *smc);
व्योम smt_pmf_received_pack(काष्ठा s_smc *smc, SMbuf *mb, पूर्णांक local);
व्योम smt_send_frame(काष्ठा s_smc *smc, SMbuf *mb, पूर्णांक fc, पूर्णांक local);
व्योम smt_set_बारtamp(काष्ठा s_smc *smc, u_अक्षर *p);
व्योम mac_set_rx_mode(काष्ठा s_smc *smc,	पूर्णांक mode);
पूर्णांक mac_add_multicast(काष्ठा s_smc *smc, काष्ठा fddi_addr *addr, पूर्णांक can);
व्योम mac_update_multicast(काष्ठा s_smc *smc);
व्योम mac_clear_multicast(काष्ठा s_smc *smc);
व्योम set_क्रमmac_tsync(काष्ठा s_smc *smc, दीर्घ sync_bw);
व्योम क्रमmac_reinit_tx(काष्ठा s_smc *smc);
व्योम क्रमmac_tx_restart(काष्ठा s_smc *smc);
व्योम process_receive(काष्ठा s_smc *smc);
व्योम init_driver_fplus(काष्ठा s_smc *smc);
व्योम rपंचांग_irq(काष्ठा s_smc *smc);
व्योम rपंचांग_set_समयr(काष्ठा s_smc *smc);
व्योम ring_status_indication(काष्ठा s_smc *smc, u_दीर्घ status);
व्योम llc_recover_tx(काष्ठा s_smc *smc);
व्योम llc_restart_tx(काष्ठा s_smc *smc);
व्योम plc_clear_irq(काष्ठा s_smc *smc, पूर्णांक p);
व्योम plc_irq(काष्ठा s_smc *smc,	पूर्णांक np,	अचिन्हित पूर्णांक cmd);
पूर्णांक smt_set_mac_opvalues(काष्ठा s_smc *smc);

#अगर_घोषित TAG_MODE
व्योम mac_करो_pci_fix(काष्ठा s_smc *smc);
व्योम mac_drv_clear_tx_queue(काष्ठा s_smc *smc);
व्योम mac_drv_repair_descr(काष्ठा s_smc *smc);
u_दीर्घ hwt_quick_पढ़ो(काष्ठा s_smc *smc);
व्योम hwt_रुको_समय(काष्ठा s_smc *smc, u_दीर्घ start, दीर्घ duration);
#पूर्ण_अगर

#अगर_घोषित SMT_PNMI
पूर्णांक pnmi_init(काष्ठा s_smc* smc);
पूर्णांक pnmi_process_ndis_id(काष्ठा s_smc *smc, u_दीर्घ ndis_oid, व्योम *buf, पूर्णांक len,
			 पूर्णांक *BytesAccessed, पूर्णांक *BytesNeeded, u_अक्षर action);
#पूर्ण_अगर

#अगर_घोषित	SBA
#अगर_अघोषित _H2INC
व्योम sba();
#पूर्ण_अगर
व्योम sba_raf_received_pack();
व्योम sba_समयr_poll();
व्योम smt_init_sba();
#पूर्ण_अगर

#अगर_घोषित	ESS
पूर्णांक ess_raf_received_pack(काष्ठा s_smc *smc, SMbuf *mb, काष्ठा smt_header *sm,
			  पूर्णांक fs);
व्योम ess_समयr_poll(काष्ठा s_smc *smc);
व्योम ess_para_change(काष्ठा s_smc *smc);
#पूर्ण_अगर

#अगर_अघोषित	BOOT
व्योम smt_init_evc(काष्ठा s_smc *smc);
व्योम smt_srf_event(काष्ठा s_smc *smc, पूर्णांक code, पूर्णांक index, पूर्णांक cond);
#अन्यथा
#घोषणा smt_init_evc(smc)
#घोषणा smt_srf_event(smc,code,index,cond)
#पूर्ण_अगर

#अगर_अघोषित SMT_REAL_TOKEN_CT
व्योम smt_emulate_token_ct(काष्ठा s_smc *smc, पूर्णांक mac_index);
#पूर्ण_अगर

#अगर defined(DEBUG) && !defined(BOOT)
व्योम dump_smt(काष्ठा s_smc *smc, काष्ठा smt_header *sm, अक्षर *text);
#अन्यथा
#घोषणा	dump_smt(smc,sm,text)
#पूर्ण_अगर

#अगर_घोषित	DEBUG
व्योम dump_hex(अक्षर *p, पूर्णांक len);
#पूर्ण_अगर

#पूर्ण_अगर	/* PROTOTYP_INC */

/* PNMI शेष defines */
#अगर_अघोषित PNMI_INIT
#घोषणा	PNMI_INIT(smc)	/* Nothing */
#पूर्ण_अगर

/*
 * SMT_PANIC defines
 */
#अगर_अघोषित	SMT_PANIC
#घोषणा	SMT_PANIC(smc,nr,msg)	smt_panic (smc, msg)
#पूर्ण_अगर

#अगर_अघोषित	SMT_ERR_LOG
#घोषणा	SMT_ERR_LOG(smc,nr,msg)	SMT_PANIC (smc, nr, msg)
#पूर्ण_अगर

#अगर_अघोषित	SMT_EBASE
#घोषणा	SMT_EBASE	100
#पूर्ण_अगर

#घोषणा	SMT_E0100	SMT_EBASE + 0
#घोषणा	SMT_E0100_MSG	"cfm FSM: invalid ce_type"
#घोषणा	SMT_E0101	SMT_EBASE + 1
#घोषणा	SMT_E0101_MSG	"CEM: case ???"
#घोषणा	SMT_E0102	SMT_EBASE + 2
#घोषणा	SMT_E0102_MSG	"CEM A: invalid state"
#घोषणा	SMT_E0103	SMT_EBASE + 3
#घोषणा	SMT_E0103_MSG	"CEM B: invalid state"
#घोषणा	SMT_E0104	SMT_EBASE + 4
#घोषणा	SMT_E0104_MSG	"CEM M: invalid state"
#घोषणा	SMT_E0105	SMT_EBASE + 5
#घोषणा	SMT_E0105_MSG	"CEM S: invalid state"
#घोषणा	SMT_E0106	SMT_EBASE + 6
#घोषणा	SMT_E0106_MSG	"CFM : invalid state"
#घोषणा	SMT_E0107	SMT_EBASE + 7
#घोषणा	SMT_E0107_MSG	"ECM : invalid state"
#घोषणा	SMT_E0108	SMT_EBASE + 8
#घोषणा	SMT_E0108_MSG	"prop_actions : NAC in DAS CFM"
#घोषणा	SMT_E0109	SMT_EBASE + 9
#घोषणा	SMT_E0109_MSG	"ST2U.FM_SERRSF error in special frame"
#घोषणा	SMT_E0110	SMT_EBASE + 10
#घोषणा	SMT_E0110_MSG	"ST2U.FM_SRFRCTOV recv. count. overflow"
#घोषणा	SMT_E0111	SMT_EBASE + 11
#घोषणा	SMT_E0111_MSG	"ST2U.FM_SNFSLD NP & FORMAC simult. load"
#घोषणा	SMT_E0112	SMT_EBASE + 12
#घोषणा	SMT_E0112_MSG	"ST2U.FM_SRCVFRM single-frame recv.-mode"
#घोषणा	SMT_E0113	SMT_EBASE + 13
#घोषणा	SMT_E0113_MSG	"FPLUS: Buffer Memory Error"
#घोषणा	SMT_E0114	SMT_EBASE + 14
#घोषणा	SMT_E0114_MSG	"ST2U.FM_SERRSF error in special frame"
#घोषणा	SMT_E0115	SMT_EBASE + 15
#घोषणा	SMT_E0115_MSG	"ST3L: parity error in receive queue 2"
#घोषणा	SMT_E0116	SMT_EBASE + 16
#घोषणा	SMT_E0116_MSG	"ST3L: parity error in receive queue 1"
#घोषणा	SMT_E0117	SMT_EBASE + 17
#घोषणा	SMT_E0117_MSG	"E_SMT_001: RxD count for receive queue 1 = 0"
#घोषणा	SMT_E0118	SMT_EBASE + 18
#घोषणा	SMT_E0118_MSG	"PCM : invalid state"
#घोषणा	SMT_E0119	SMT_EBASE + 19
#घोषणा	SMT_E0119_MSG	"smt_add_para"
#घोषणा	SMT_E0120	SMT_EBASE + 20
#घोषणा	SMT_E0120_MSG	"smt_set_para"
#घोषणा	SMT_E0121	SMT_EBASE + 21
#घोषणा	SMT_E0121_MSG	"invalid event in dispatcher"
#घोषणा	SMT_E0122	SMT_EBASE + 22
#घोषणा	SMT_E0122_MSG	"RMT : invalid state"
#घोषणा	SMT_E0123	SMT_EBASE + 23
#घोषणा	SMT_E0123_MSG	"SBA: state machine has invalid state"
#घोषणा	SMT_E0124	SMT_EBASE + 24
#घोषणा	SMT_E0124_MSG	"sba_free_session() called with NULL pointer"
#घोषणा	SMT_E0125	SMT_EBASE + 25
#घोषणा	SMT_E0125_MSG	"SBA : invalid session pointer"
#घोषणा	SMT_E0126	SMT_EBASE + 26
#घोषणा	SMT_E0126_MSG	"smt_free_mbuf() called with NULL pointer\n"
#घोषणा	SMT_E0127	SMT_EBASE + 27
#घोषणा	SMT_E0127_MSG	"sizeof evcs"
#घोषणा	SMT_E0128	SMT_EBASE + 28
#घोषणा	SMT_E0128_MSG	"evc->evc_cond_state = 0"
#घोषणा	SMT_E0129	SMT_EBASE + 29
#घोषणा	SMT_E0129_MSG	"evc->evc_multiple = 0"
#घोषणा	SMT_E0130	SMT_EBASE + 30
#घोषणा	SMT_E0130_MSG	ग_लिखो_mdr_warning
#घोषणा	SMT_E0131	SMT_EBASE + 31
#घोषणा	SMT_E0131_MSG	cam_warning
#घोषणा SMT_E0132	SMT_EBASE + 32
#घोषणा SMT_E0132_MSG	"ST1L.FM_SPCEPDx parity/coding error"
#घोषणा SMT_E0133	SMT_EBASE + 33
#घोषणा SMT_E0133_MSG	"ST1L.FM_STBURx tx buffer underrun"
#घोषणा SMT_E0134	SMT_EBASE + 34
#घोषणा SMT_E0134_MSG	"ST1L.FM_SPCEPDx parity error"
#घोषणा SMT_E0135	SMT_EBASE + 35
#घोषणा SMT_E0135_MSG	"RMT: duplicate MAC address detected. Ring left!"
#घोषणा SMT_E0136	SMT_EBASE + 36
#घोषणा SMT_E0136_MSG	"Elasticity Buffer hang-up"
#घोषणा SMT_E0137	SMT_EBASE + 37
#घोषणा SMT_E0137_MSG	"SMT: queue overrun"
#घोषणा SMT_E0138	SMT_EBASE + 38
#घोषणा SMT_E0138_MSG	"RMT: duplicate MAC address detected. Ring NOT left!"
#पूर्ण_अगर	/* _CMTDEF_ */
