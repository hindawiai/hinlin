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
	PCM
	Physical Connection Management
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
 * 		sm_pm_control()
 *		sm_ph_linestate()
 *
 * 	The following HW dependent events are required :
 *		PC_QLS
 *		PC_ILS
 *		PC_HLS
 *		PC_MLS
 *		PC_NSE
 *		PC_LEM
 *
 */


#समावेश "h/types.h"
#समावेश "h/fddi.h"
#समावेश "h/smc.h"
#समावेश "h/supern_2.h"
#घोषणा KERNEL
#समावेश "h/smtstate.h"

#अगर_घोषित	FDDI_MIB
बाह्य पूर्णांक snmp_fddi_trap(
#अगर_घोषित	ANSIC
काष्ठा s_smc	* smc, पूर्णांक  type, पूर्णांक  index
#पूर्ण_अगर
);
#पूर्ण_अगर
#अगर_घोषित	CONCENTRATOR
बाह्य पूर्णांक plc_is_installed(
#अगर_घोषित	ANSIC
काष्ठा s_smc *smc ,
पूर्णांक p
#पूर्ण_अगर
) ;
#पूर्ण_अगर
/*
 * FSM Macros
 */
#घोषणा AFLAG		(0x20)
#घोषणा GO_STATE(x)	(mib->fddiPORTPCMState = (x)|AFLAG)
#घोषणा ACTIONS_DONE()	(mib->fddiPORTPCMState &= ~AFLAG)
#घोषणा ACTIONS(x)	(x|AFLAG)

/*
 * PCM states
 */
#घोषणा PC0_OFF			0
#घोषणा PC1_BREAK		1
#घोषणा PC2_TRACE		2
#घोषणा PC3_CONNECT		3
#घोषणा PC4_NEXT		4
#घोषणा PC5_SIGNAL		5
#घोषणा PC6_JOIN		6
#घोषणा PC7_VERIFY		7
#घोषणा PC8_ACTIVE		8
#घोषणा PC9_MAINT		9

/*
 * symbolic state names
 */
अटल स्थिर अक्षर * स्थिर pcm_states[] =  अणु
	"PC0_OFF","PC1_BREAK","PC2_TRACE","PC3_CONNECT","PC4_NEXT",
	"PC5_SIGNAL","PC6_JOIN","PC7_VERIFY","PC8_ACTIVE","PC9_MAINT"
पूर्ण ;

/*
 * symbolic event names
 */
अटल स्थिर अक्षर * स्थिर pcm_events[] = अणु
	"NONE","PC_START","PC_STOP","PC_LOOP","PC_JOIN","PC_SIGNAL",
	"PC_REJECT","PC_MAINT","PC_TRACE","PC_PDR",
	"PC_ENABLE","PC_DISABLE",
	"PC_QLS","PC_ILS","PC_MLS","PC_HLS","PC_LS_PDR","PC_LS_NONE",
	"PC_TIMEOUT_TB_MAX","PC_TIMEOUT_TB_MIN",
	"PC_TIMEOUT_C_MIN","PC_TIMEOUT_T_OUT",
	"PC_TIMEOUT_TL_MIN","PC_TIMEOUT_T_NEXT","PC_TIMEOUT_LCT",
	"PC_NSE","PC_LEM"
पूर्ण ;

#अगर_घोषित	MOT_ELM
/*
 * PCL-S control रेजिस्टर
 * this रेजिस्टर in the PLC-S controls the scrambling parameters
 */
#घोषणा PLCS_CONTROL_C_U	0
#घोषणा PLCS_CONTROL_C_S	(PL_C_SDOFF_ENABLE | PL_C_SDON_ENABLE | \
				 PL_C_CIPHER_ENABLE)
#घोषणा	PLCS_FASSERT_U		0
#घोषणा	PLCS_FASSERT_S		0xFd76	/* 52.0 us */
#घोषणा	PLCS_FDEASSERT_U	0
#घोषणा	PLCS_FDEASSERT_S	0
#अन्यथा	/* nMOT_ELM */
/*
 * PCL-S control रेजिस्टर
 * this रेजिस्टर in the PLC-S controls the scrambling parameters
 * can be patched क्रम ANSI compliance अगर standard changes
 */
अटल स्थिर u_अक्षर plcs_control_c_u[17] = "PLC_CNTRL_C_U=\0\0" ;
अटल स्थिर u_अक्षर plcs_control_c_s[17] = "PLC_CNTRL_C_S=\01\02" ;

#घोषणा PLCS_CONTROL_C_U (plcs_control_c_u[14] | (plcs_control_c_u[15]<<8))
#घोषणा PLCS_CONTROL_C_S (plcs_control_c_s[14] | (plcs_control_c_s[15]<<8))
#पूर्ण_अगर	/* nMOT_ELM */

/*
 * बाह्यal vars
 */
/* काष्ठा definition see 'cmtdef.h' (also used by CFM) */

#घोषणा PS_OFF		0
#घोषणा PS_BIT3		1
#घोषणा PS_BIT4		2
#घोषणा PS_BIT7		3
#घोषणा PS_LCT		4
#घोषणा PS_BIT8		5
#घोषणा PS_JOIN		6
#घोषणा PS_ACTIVE	7

#घोषणा LCT_LEM_MAX	255

/*
 * PLC timing parameter
 */

#घोषणा PLC_MS(m)	((पूर्णांक)((0x10000L-(m*100000L/2048))))
#घोषणा SLOW_TL_MIN	PLC_MS(6)
#घोषणा SLOW_C_MIN	PLC_MS(10)

अटल	स्थिर काष्ठा plt अणु
	पूर्णांक	समयr ;			/* relative plc समयr address */
	पूर्णांक	para ;			/* शेष timing parameters */
पूर्ण plपंचांग[] = अणु
	अणु PL_C_MIN, SLOW_C_MIN पूर्ण,	/* min t. to reमुख्य Connect State */
	अणु PL_TL_MIN, SLOW_TL_MIN पूर्ण,	/* min t. to transmit a Line State */
	अणु PL_TB_MIN, TP_TB_MIN पूर्ण,	/* min अवरोध समय */
	अणु PL_T_OUT, TP_T_OUT पूर्ण,		/* Signaling समयout */
	अणु PL_LC_LENGTH, TP_LC_LENGTH पूर्ण,	/* Link Confidence Test Time */
	अणु PL_T_SCRUB, TP_T_SCRUB पूर्ण,	/* Scrub Time == MAC TVX समय ! */
	अणु PL_NS_MAX, TP_NS_MAX पूर्ण,	/* max t. that noise is tolerated */
	अणु 0,0 पूर्ण
पूर्ण ;

/*
 * पूर्णांकerrupt mask
 */
#अगर_घोषित	SUPERNET_3
/*
 * Do we need the EBUF error during संकेतing, too, to detect SUPERNET_3
 * PLL bug?
 */
अटल स्थिर पूर्णांक plc_imsk_na = PL_PCM_CODE | PL_TRACE_PROP | PL_PCM_BREAK |
			PL_PCM_ENABLED | PL_SELF_TEST | PL_EBUF_ERR;
#अन्यथा	/* SUPERNET_3 */
/*
 * We करो NOT need the elasticity buffer error during संकेतing.
 */
अटल पूर्णांक plc_imsk_na = PL_PCM_CODE | PL_TRACE_PROP | PL_PCM_BREAK |
			PL_PCM_ENABLED | PL_SELF_TEST ;
#पूर्ण_अगर	/* SUPERNET_3 */
अटल स्थिर पूर्णांक plc_imsk_act = PL_PCM_CODE | PL_TRACE_PROP | PL_PCM_BREAK |
			PL_PCM_ENABLED | PL_SELF_TEST | PL_EBUF_ERR;

/* पूर्णांकernal functions */
अटल व्योम pcm_fsm(काष्ठा s_smc *smc, काष्ठा s_phy *phy, पूर्णांक cmd);
अटल व्योम pc_rcode_actions(काष्ठा s_smc *smc, पूर्णांक bit, काष्ठा s_phy *phy);
अटल व्योम pc_tcode_actions(काष्ठा s_smc *smc, स्थिर पूर्णांक bit, काष्ठा s_phy *phy);
अटल व्योम reset_lem_काष्ठा(काष्ठा s_phy *phy);
अटल व्योम plc_init(काष्ठा s_smc *smc, पूर्णांक p);
अटल व्योम sm_ph_lem_start(काष्ठा s_smc *smc, पूर्णांक np, पूर्णांक threshold);
अटल व्योम sm_ph_lem_stop(काष्ठा s_smc *smc, पूर्णांक np);
अटल व्योम sm_ph_linestate(काष्ठा s_smc *smc, पूर्णांक phy, पूर्णांक ls);
अटल व्योम real_init_plc(काष्ठा s_smc *smc);

/*
 * SMT समयr पूर्णांकerface
 *      start PCM समयr 0
 */
अटल व्योम start_pcm_समयr0(काष्ठा s_smc *smc, u_दीर्घ value, पूर्णांक event,
			     काष्ठा s_phy *phy)
अणु
	phy->समयr0_exp = FALSE ;       /* clear समयr event flag */
	smt_समयr_start(smc,&phy->pcm_समयr0,value,
		EV_TOKEN(EVENT_PCM+phy->np,event)) ;
पूर्ण
/*
 * SMT समयr पूर्णांकerface
 *      stop PCM समयr 0
 */
अटल व्योम stop_pcm_समयr0(काष्ठा s_smc *smc, काष्ठा s_phy *phy)
अणु
	अगर (phy->pcm_समयr0.पंचांग_active)
		smt_समयr_stop(smc,&phy->pcm_समयr0) ;
पूर्ण

/*
	init PCM state machine (called by driver)
	clear all PCM vars and flags
*/
व्योम pcm_init(काष्ठा s_smc *smc)
अणु
	पूर्णांक		i ;
	पूर्णांक		np ;
	काष्ठा s_phy	*phy ;
	काष्ठा fddi_mib_p	*mib ;

	क्रम (np = 0,phy = smc->y ; np < NUMPHYS ; np++,phy++) अणु
		/* Indicates the type of PHY being used */
		mib = phy->mib ;
		mib->fddiPORTPCMState = ACTIONS(PC0_OFF) ;
		phy->np = np ;
		चयन (smc->s.sas) अणु
#अगर_घोषित	CONCENTRATOR
		हाल SMT_SAS :
			mib->fddiPORTMy_Type = (np == PS) ? TS : TM ;
			अवरोध ;
		हाल SMT_DAS :
			mib->fddiPORTMy_Type = (np == PA) ? TA :
					(np == PB) ? TB : TM ;
			अवरोध ;
		हाल SMT_NAC :
			mib->fddiPORTMy_Type = TM ;
			अवरोध;
#अन्यथा
		हाल SMT_SAS :
			mib->fddiPORTMy_Type = (np == PS) ? TS : TNONE ;
			mib->fddiPORTHardwarePresent = (np == PS) ? TRUE :
					FALSE ;
#अगर_अघोषित	SUPERNET_3
			smc->y[PA].mib->fddiPORTPCMState = PC0_OFF ;
#अन्यथा
			smc->y[PB].mib->fddiPORTPCMState = PC0_OFF ;
#पूर्ण_अगर
			अवरोध ;
		हाल SMT_DAS :
			mib->fddiPORTMy_Type = (np == PB) ? TB : TA ;
			अवरोध ;
#पूर्ण_अगर
		पूर्ण
		/*
		 * set PMD-type
		 */
		phy->pmd_scramble = 0 ;
		चयन (phy->pmd_type[PMD_SK_PMD]) अणु
		हाल 'P' :
			mib->fddiPORTPMDClass = MIB_PMDCLASS_MULTI ;
			अवरोध ;
		हाल 'L' :
			mib->fddiPORTPMDClass = MIB_PMDCLASS_LCF ;
			अवरोध ;
		हाल 'D' :
			mib->fddiPORTPMDClass = MIB_PMDCLASS_TP ;
			अवरोध ;
		हाल 'S' :
			mib->fddiPORTPMDClass = MIB_PMDCLASS_TP ;
			phy->pmd_scramble = TRUE ;
			अवरोध ;
		हाल 'U' :
			mib->fddiPORTPMDClass = MIB_PMDCLASS_TP ;
			phy->pmd_scramble = TRUE ;
			अवरोध ;
		हाल '1' :
			mib->fddiPORTPMDClass = MIB_PMDCLASS_SINGLE1 ;
			अवरोध ;
		हाल '2' :
			mib->fddiPORTPMDClass = MIB_PMDCLASS_SINGLE2 ;
			अवरोध ;
		हाल '3' :
			mib->fddiPORTPMDClass = MIB_PMDCLASS_SINGLE2 ;
			अवरोध ;
		हाल '4' :
			mib->fddiPORTPMDClass = MIB_PMDCLASS_SINGLE1 ;
			अवरोध ;
		हाल 'H' :
			mib->fddiPORTPMDClass = MIB_PMDCLASS_UNKNOWN ;
			अवरोध ;
		हाल 'I' :
			mib->fddiPORTPMDClass = MIB_PMDCLASS_TP ;
			अवरोध ;
		हाल 'G' :
			mib->fddiPORTPMDClass = MIB_PMDCLASS_TP ;
			अवरोध ;
		शेष:
			mib->fddiPORTPMDClass = MIB_PMDCLASS_UNKNOWN ;
			अवरोध ;
		पूर्ण
		/*
		 * A and B port can be on primary and secondary path
		 */
		चयन (mib->fddiPORTMy_Type) अणु
		हाल TA :
			mib->fddiPORTAvailablePaths |= MIB_PATH_S ;
			mib->fddiPORTRequestedPaths[1] = MIB_P_PATH_LOCAL ;
			mib->fddiPORTRequestedPaths[2] =
				MIB_P_PATH_LOCAL |
				MIB_P_PATH_CON_ALTER |
				MIB_P_PATH_SEC_PREFER ;
			mib->fddiPORTRequestedPaths[3] =
				MIB_P_PATH_LOCAL |
				MIB_P_PATH_CON_ALTER |
				MIB_P_PATH_SEC_PREFER |
				MIB_P_PATH_THRU ;
			अवरोध ;
		हाल TB :
			mib->fddiPORTAvailablePaths |= MIB_PATH_S ;
			mib->fddiPORTRequestedPaths[1] = MIB_P_PATH_LOCAL ;
			mib->fddiPORTRequestedPaths[2] =
				MIB_P_PATH_LOCAL |
				MIB_P_PATH_PRIM_PREFER ;
			mib->fddiPORTRequestedPaths[3] =
				MIB_P_PATH_LOCAL |
				MIB_P_PATH_PRIM_PREFER |
				MIB_P_PATH_CON_PREFER |
				MIB_P_PATH_THRU ;
			अवरोध ;
		हाल TS :
			mib->fddiPORTAvailablePaths |= MIB_PATH_S ;
			mib->fddiPORTRequestedPaths[1] = MIB_P_PATH_LOCAL ;
			mib->fddiPORTRequestedPaths[2] =
				MIB_P_PATH_LOCAL |
				MIB_P_PATH_CON_ALTER |
				MIB_P_PATH_PRIM_PREFER ;
			mib->fddiPORTRequestedPaths[3] =
				MIB_P_PATH_LOCAL |
				MIB_P_PATH_CON_ALTER |
				MIB_P_PATH_PRIM_PREFER ;
			अवरोध ;
		हाल TM :
			mib->fddiPORTRequestedPaths[1] = MIB_P_PATH_LOCAL ;
			mib->fddiPORTRequestedPaths[2] =
				MIB_P_PATH_LOCAL |
				MIB_P_PATH_SEC_ALTER |
				MIB_P_PATH_PRIM_ALTER ;
			mib->fddiPORTRequestedPaths[3] = 0 ;
			अवरोध ;
		पूर्ण

		phy->pc_lem_fail = FALSE ;
		mib->fddiPORTPCMStateX = mib->fddiPORTPCMState ;
		mib->fddiPORTLCTFail_Ct = 0 ;
		mib->fddiPORTBS_Flag = 0 ;
		mib->fddiPORTCurrentPath = MIB_PATH_ISOLATED ;
		mib->fddiPORTNeighborType = TNONE ;
		phy->ls_flag = 0 ;
		phy->rc_flag = 0 ;
		phy->tc_flag = 0 ;
		phy->td_flag = 0 ;
		अगर (np >= PM)
			phy->phy_name = '0' + np - PM ;
		अन्यथा
			phy->phy_name = 'A' + np ;
		phy->wc_flag = FALSE ;		/* set by SMT */
		स_रखो((अक्षर *)&phy->lem,0,माप(काष्ठा lem_counter)) ;
		reset_lem_काष्ठा(phy) ;
		स_रखो((अक्षर *)&phy->plc,0,माप(काष्ठा s_plc)) ;
		phy->plc.p_state = PS_OFF ;
		क्रम (i = 0 ; i < NUMBITS ; i++) अणु
			phy->t_next[i] = 0 ;
		पूर्ण
	पूर्ण
	real_init_plc(smc) ;
पूर्ण

व्योम init_plc(काष्ठा s_smc *smc)
अणु
	SK_UNUSED(smc) ;

	/*
	 * dummy
	 * this is an obsolete खुला entry poपूर्णांक that has to reमुख्य
	 * क्रम compat. It is used by various drivers.
	 * the work is now करोne in real_init_plc()
	 * which is called from pcm_init() ;
	 */
पूर्ण

अटल व्योम real_init_plc(काष्ठा s_smc *smc)
अणु
	पूर्णांक	p ;

	क्रम (p = 0 ; p < NUMPHYS ; p++)
		plc_init(smc,p) ;
पूर्ण

अटल व्योम plc_init(काष्ठा s_smc *smc, पूर्णांक p)
अणु
	पूर्णांक	i ;
#अगर_अघोषित	MOT_ELM
	पूर्णांक	rev ;	/* Revision of PLC-x */
#पूर्ण_अगर	/* MOT_ELM */

	/* transit PCM state machine to MAINT state */
	outpw(PLC(p,PL_CNTRL_B),0) ;
	outpw(PLC(p,PL_CNTRL_B),PL_PCM_STOP) ;
	outpw(PLC(p,PL_CNTRL_A),0) ;

	/*
	 * अगर PLC-S then set control रेजिस्टर C
	 */
#अगर_अघोषित	MOT_ELM
	rev = inpw(PLC(p,PL_STATUS_A)) & PLC_REV_MASK ;
	अगर (rev != PLC_REVISION_A)
#पूर्ण_अगर	/* MOT_ELM */
	अणु
		अगर (smc->y[p].pmd_scramble) अणु
			outpw(PLC(p,PL_CNTRL_C),PLCS_CONTROL_C_S) ;
#अगर_घोषित	MOT_ELM
			outpw(PLC(p,PL_T_FOT_ASS),PLCS_FASSERT_S) ;
			outpw(PLC(p,PL_T_FOT_DEASS),PLCS_FDEASSERT_S) ;
#पूर्ण_अगर	/* MOT_ELM */
		पूर्ण
		अन्यथा अणु
			outpw(PLC(p,PL_CNTRL_C),PLCS_CONTROL_C_U) ;
#अगर_घोषित	MOT_ELM
			outpw(PLC(p,PL_T_FOT_ASS),PLCS_FASSERT_U) ;
			outpw(PLC(p,PL_T_FOT_DEASS),PLCS_FDEASSERT_U) ;
#पूर्ण_अगर	/* MOT_ELM */
		पूर्ण
	पूर्ण

	/*
	 * set समयr रेजिस्टर
	 */
	क्रम ( i = 0 ; plपंचांग[i].समयr; i++)	/* set समयr parameter reg */
		outpw(PLC(p,plपंचांग[i].समयr),plपंचांग[i].para) ;

	(व्योम)inpw(PLC(p,PL_INTR_EVENT)) ;	/* clear पूर्णांकerrupt event reg */
	plc_clear_irq(smc,p) ;
	outpw(PLC(p,PL_INTR_MASK),plc_imsk_na); /* enable non active irq's */

	/*
	 * अगर PCM is configured क्रम class s, it will NOT go to the
	 * REMOVE state अगर offline (page 3-36;)
	 * in the concentrator, all inactive PHYS always must be in
	 * the हटाओ state
	 * there's no real need to use this feature at all ..
	 */
#अगर_अघोषित	CONCENTRATOR
	अगर ((smc->s.sas == SMT_SAS) && (p == PS)) अणु
		outpw(PLC(p,PL_CNTRL_B),PL_CLASS_S) ;
	पूर्ण
#पूर्ण_अगर
पूर्ण

/*
 * control PCM state machine
 */
अटल व्योम plc_go_state(काष्ठा s_smc *smc, पूर्णांक p, पूर्णांक state)
अणु
	HW_PTR port ;
	पूर्णांक val ;

	SK_UNUSED(smc) ;

	port = (HW_PTR) (PLC(p,PL_CNTRL_B)) ;
	val = inpw(port) & ~(PL_PCM_CNTRL | PL_MAINT) ;
	outpw(port,val) ;
	outpw(port,val | state) ;
पूर्ण

/*
 * पढ़ो current line state (called by ECM & PCM)
 */
पूर्णांक sm_pm_get_ls(काष्ठा s_smc *smc, पूर्णांक phy)
अणु
	पूर्णांक	state ;

#अगर_घोषित	CONCENTRATOR
	अगर (!plc_is_installed(smc,phy))
		वापस PC_QLS;
#पूर्ण_अगर

	state = inpw(PLC(phy,PL_STATUS_A)) & PL_LINE_ST ;
	चयन(state) अणु
	हाल PL_L_QLS:
		state = PC_QLS ;
		अवरोध ;
	हाल PL_L_MLS:
		state = PC_MLS ;
		अवरोध ;
	हाल PL_L_HLS:
		state = PC_HLS ;
		अवरोध ;
	हाल PL_L_ILS4:
	हाल PL_L_ILS16:
		state = PC_ILS ;
		अवरोध ;
	हाल PL_L_ALS:
		state = PC_LS_PDR ;
		अवरोध ;
	शेष :
		state = PC_LS_NONE ;
	पूर्ण
	वापस state;
पूर्ण

अटल पूर्णांक plc_send_bits(काष्ठा s_smc *smc, काष्ठा s_phy *phy, पूर्णांक len)
अणु
	पूर्णांक np = phy->np ;		/* PHY index */
	पूर्णांक	n ;
	पूर्णांक	i ;

	SK_UNUSED(smc) ;

	/* create bit vector */
	क्रम (i = len-1,n = 0 ; i >= 0 ; i--) अणु
		n = (n<<1) | phy->t_val[phy->bitn+i] ;
	पूर्ण
	अगर (inpw(PLC(np,PL_STATUS_B)) & PL_PCM_SIGNAL) अणु
#अगर	0
		म_लिखो("PL_PCM_SIGNAL is set\n") ;
#पूर्ण_अगर
		वापस 1;
	पूर्ण
	/* ग_लिखो bit[n] & length = 1 to regs */
	outpw(PLC(np,PL_VECTOR_LEN),len-1) ;	/* len=nr-1 */
	outpw(PLC(np,PL_XMIT_VECTOR),n) ;
#अगर_घोषित	DEBUG
#अगर 1
#अगर_घोषित	DEBUG_BRD
	अगर (smc->debug.d_plc & 0x80)
#अन्यथा
	अगर (debug.d_plc & 0x80)
#पूर्ण_अगर
		म_लिखो("SIGNALING bit %d .. %d\n",phy->bitn,phy->bitn+len-1) ;
#पूर्ण_अगर
#पूर्ण_अगर
	वापस 0;
पूर्ण

/*
 * config plc muxes
 */
व्योम plc_config_mux(काष्ठा s_smc *smc, पूर्णांक mux)
अणु
	अगर (smc->s.sas != SMT_DAS)
		वापस ;
	अगर (mux == MUX_WRAPB) अणु
		SETMASK(PLC(PA,PL_CNTRL_B),PL_CONFIG_CNTRL,PL_CONFIG_CNTRL) ;
		SETMASK(PLC(PA,PL_CNTRL_A),PL_SC_REM_LOOP,PL_SC_REM_LOOP) ;
	पूर्ण
	अन्यथा अणु
		CLEAR(PLC(PA,PL_CNTRL_B),PL_CONFIG_CNTRL) ;
		CLEAR(PLC(PA,PL_CNTRL_A),PL_SC_REM_LOOP) ;
	पूर्ण
	CLEAR(PLC(PB,PL_CNTRL_B),PL_CONFIG_CNTRL) ;
	CLEAR(PLC(PB,PL_CNTRL_A),PL_SC_REM_LOOP) ;
पूर्ण

/*
	PCM state machine
	called by dispatcher  & fddi_init() (driver)
	करो
		display state change
		process event
	until SM is stable
*/
व्योम pcm(काष्ठा s_smc *smc, स्थिर पूर्णांक np, पूर्णांक event)
अणु
	पूर्णांक	state ;
	पूर्णांक	oldstate ;
	काष्ठा s_phy	*phy ;
	काष्ठा fddi_mib_p	*mib ;

#अगर_अघोषित	CONCENTRATOR
	/*
	 * ignore 2nd PHY अगर SAS
	 */
	अगर ((np != PS) && (smc->s.sas == SMT_SAS))
		वापस ;
#पूर्ण_अगर
	phy = &smc->y[np] ;
	mib = phy->mib ;
	oldstate = mib->fddiPORTPCMState ;
	करो अणु
		DB_PCM("PCM %c: state %s%s, event %s",
		       phy->phy_name,
		       mib->fddiPORTPCMState & AFLAG ? "ACTIONS " : "",
		       pcm_states[mib->fddiPORTPCMState & ~AFLAG],
		       pcm_events[event]);
		state = mib->fddiPORTPCMState ;
		pcm_fsm(smc,phy,event) ;
		event = 0 ;
	पूर्ण जबतक (state != mib->fddiPORTPCMState) ;
	/*
	 * because the PLC करोes the bit संकेतing क्रम us,
	 * we're always in SIGNAL state
	 * the MIB want's to see CONNECT
	 * we thereक्रमe fake an entry in the MIB
	 */
	अगर (state == PC5_SIGNAL)
		mib->fddiPORTPCMStateX = PC3_CONNECT ;
	अन्यथा
		mib->fddiPORTPCMStateX = state ;

#अगर_अघोषित	SLIM_SMT
	/*
	 * path change
	 */
	अगर (	mib->fddiPORTPCMState != oldstate &&
		((oldstate == PC8_ACTIVE) || (mib->fddiPORTPCMState == PC8_ACTIVE))) अणु
		smt_srf_event(smc,SMT_EVENT_PORT_PATH_CHANGE,
			(पूर्णांक) (INDEX_PORT+ phy->np),0) ;
	पूर्ण
#पूर्ण_अगर

#अगर_घोषित FDDI_MIB
	/* check whether a snmp-trap has to be sent */

	अगर ( mib->fddiPORTPCMState != oldstate ) अणु
		/* a real state change took place */
		DB_SNMP ("PCM from %d to %d\n", oldstate, mib->fddiPORTPCMState);
		अगर ( mib->fddiPORTPCMState == PC0_OFF ) अणु
			/* send first trap */
			snmp_fddi_trap (smc, 1, (पूर्णांक) mib->fddiPORTIndex );
		पूर्ण अन्यथा अगर ( oldstate == PC0_OFF ) अणु
			/* send second trap */
			snmp_fddi_trap (smc, 2, (पूर्णांक) mib->fddiPORTIndex );
		पूर्ण अन्यथा अगर ( mib->fddiPORTPCMState != PC2_TRACE &&
			oldstate == PC8_ACTIVE ) अणु
			/* send third trap */
			snmp_fddi_trap (smc, 3, (पूर्णांक) mib->fddiPORTIndex );
		पूर्ण अन्यथा अगर ( mib->fddiPORTPCMState == PC8_ACTIVE ) अणु
			/* send fourth trap */
			snmp_fddi_trap (smc, 4, (पूर्णांक) mib->fddiPORTIndex );
		पूर्ण
	पूर्ण
#पूर्ण_अगर

	pcm_state_change(smc,np,state) ;
पूर्ण

/*
 * PCM state machine
 */
अटल व्योम pcm_fsm(काष्ठा s_smc *smc, काष्ठा s_phy *phy, पूर्णांक cmd)
अणु
	पूर्णांक	i ;
	पूर्णांक	np = phy->np ;		/* PHY index */
	काष्ठा s_plc	*plc ;
	काष्ठा fddi_mib_p	*mib ;
#अगर_अघोषित	MOT_ELM
	u_लघु	plc_rev ;		/* Revision of the plc */
#पूर्ण_अगर	/* nMOT_ELM */

	plc = &phy->plc ;
	mib = phy->mib ;

	/*
	 * general transitions independent of state
	 */
	चयन (cmd) अणु
	हाल PC_STOP :
		/*PC00-PC80*/
		अगर (mib->fddiPORTPCMState != PC9_MAINT) अणु
			GO_STATE(PC0_OFF) ;
			AIX_EVENT(smc, (u_दीर्घ) FDDI_RING_STATUS, (u_दीर्घ)
				FDDI_PORT_EVENT, (u_दीर्घ) FDDI_PORT_STOP,
				smt_get_port_event_word(smc));
		पूर्ण
		वापस ;
	हाल PC_START :
		/*PC01-PC81*/
		अगर (mib->fddiPORTPCMState != PC9_MAINT)
			GO_STATE(PC1_BREAK) ;
		वापस ;
	हाल PC_DISABLE :
		/* PC09-PC99 */
		GO_STATE(PC9_MAINT) ;
		AIX_EVENT(smc, (u_दीर्घ) FDDI_RING_STATUS, (u_दीर्घ)
			FDDI_PORT_EVENT, (u_दीर्घ) FDDI_PORT_DISABLED,
			smt_get_port_event_word(smc));
		वापस ;
	हाल PC_TIMEOUT_LCT :
		/* अगर दीर्घ or extended LCT */
		stop_pcm_समयr0(smc,phy) ;
		CLEAR(PLC(np,PL_CNTRL_B),PL_LONG) ;
		/* end of LCT is indicate by PCM_CODE (initiate PCM event) */
		वापस ;
	पूर्ण

	चयन(mib->fddiPORTPCMState) अणु
	हाल ACTIONS(PC0_OFF) :
		stop_pcm_समयr0(smc,phy) ;
		outpw(PLC(np,PL_CNTRL_A),0) ;
		CLEAR(PLC(np,PL_CNTRL_B),PL_PC_JOIN) ;
		CLEAR(PLC(np,PL_CNTRL_B),PL_LONG) ;
		sm_ph_lem_stop(smc,np) ;		/* disable LEM */
		phy->cf_loop = FALSE ;
		phy->cf_join = FALSE ;
		queue_event(smc,EVENT_CFM,CF_JOIN+np) ;
		plc_go_state(smc,np,PL_PCM_STOP) ;
		mib->fddiPORTConnectState = PCM_DISABLED ;
		ACTIONS_DONE() ;
		अवरोध ;
	हाल PC0_OFF:
		/*PC09*/
		अगर (cmd == PC_MAINT) अणु
			GO_STATE(PC9_MAINT) ;
			अवरोध ;
		पूर्ण
		अवरोध ;
	हाल ACTIONS(PC1_BREAK) :
		/* Stop the LCT समयr अगर we came from Signal state */
		stop_pcm_समयr0(smc,phy) ;
		ACTIONS_DONE() ;
		plc_go_state(smc,np,0) ;
		CLEAR(PLC(np,PL_CNTRL_B),PL_PC_JOIN) ;
		CLEAR(PLC(np,PL_CNTRL_B),PL_LONG) ;
		sm_ph_lem_stop(smc,np) ;		/* disable LEM */
		/*
		 * अगर vector is alपढ़ोy loaded, go to OFF to clear PCM_SIGNAL
		 */
#अगर	0
		अगर (inpw(PLC(np,PL_STATUS_B)) & PL_PCM_SIGNAL) अणु
			plc_go_state(smc,np,PL_PCM_STOP) ;
			/* TB_MIN ? */
		पूर्ण
#पूर्ण_अगर
		/*
		 * Go to OFF state in any हाल.
		 */
		plc_go_state(smc,np,PL_PCM_STOP) ;

		अगर (mib->fddiPORTPC_Withhold == PC_WH_NONE)
			mib->fddiPORTConnectState = PCM_CONNECTING ;
		phy->cf_loop = FALSE ;
		phy->cf_join = FALSE ;
		queue_event(smc,EVENT_CFM,CF_JOIN+np) ;
		phy->ls_flag = FALSE ;
		phy->pc_mode = PM_NONE ;	/* needed by CFM */
		phy->bitn = 0 ;			/* bit संकेतing start bit */
		क्रम (i = 0 ; i < 3 ; i++)
			pc_tcode_actions(smc,i,phy) ;

		/* Set the non-active पूर्णांकerrupt mask रेजिस्टर */
		outpw(PLC(np,PL_INTR_MASK),plc_imsk_na) ;

		/*
		 * If the LCT was stopped. There might be a
		 * PCM_CODE पूर्णांकerrupt event present.
		 * This must be cleared.
		 */
		(व्योम)inpw(PLC(np,PL_INTR_EVENT)) ;
#अगर_अघोषित	MOT_ELM
		/* Get the plc revision क्रम revision dependent code */
		plc_rev = inpw(PLC(np,PL_STATUS_A)) & PLC_REV_MASK ;

		अगर (plc_rev != PLC_REV_SN3)
#पूर्ण_अगर	/* MOT_ELM */
		अणु
			/*
			 * No supernet III PLC, so set Xmit verctor and
			 * length BEFORE starting the state machine.
			 */
			अगर (plc_send_bits(smc,phy,3)) अणु
				वापस ;
			पूर्ण
		पूर्ण

		/*
		 * Now give the Start command.
		 * - The start command shall be करोne beक्रमe setting the bits
		 *   to be संकेतed. (In PLC-S description and PLCS in SN3.
		 * - The start command shall be issued AFTER setting the
		 *   XMIT vector and the XMIT length रेजिस्टर.
		 *
		 * We करो it exactly according this specs क्रम the old PLC and
		 * the new PLCS inside the SN3.
		 * For the usual PLCS we try it the way it is करोne क्रम the
		 * old PLC and set the XMIT रेजिस्टरs again, अगर the PLC is
		 * not in SIGNAL state. This is करोne according to an PLCS
		 * errata workaround.
		 */

		plc_go_state(smc,np,PL_PCM_START) ;

		/*
		 * workaround क्रम PLC-S eng. sample errata
		 */
#अगर_घोषित	MOT_ELM
		अगर (!(inpw(PLC(np,PL_STATUS_B)) & PL_PCM_SIGNAL))
#अन्यथा	/* nMOT_ELM */
		अगर (((inpw(PLC(np,PL_STATUS_A)) & PLC_REV_MASK) !=
			PLC_REVISION_A) &&
			!(inpw(PLC(np,PL_STATUS_B)) & PL_PCM_SIGNAL))
#पूर्ण_अगर	/* nMOT_ELM */
		अणु
			/*
			 * Set रेजिस्टर again (PLCS errata) or the first समय
			 * (new SN3 PLCS).
			 */
			(व्योम) plc_send_bits(smc,phy,3) ;
		पूर्ण
		/*
		 * end of workaround
		 */

		GO_STATE(PC5_SIGNAL) ;
		plc->p_state = PS_BIT3 ;
		plc->p_bits = 3 ;
		plc->p_start = 0 ;

		अवरोध ;
	हाल PC1_BREAK :
		अवरोध ;
	हाल ACTIONS(PC2_TRACE) :
		plc_go_state(smc,np,PL_PCM_TRACE) ;
		ACTIONS_DONE() ;
		अवरोध ;
	हाल PC2_TRACE :
		अवरोध ;

	हाल PC3_CONNECT :	/* these states are करोne by hardware */
	हाल PC4_NEXT :
		अवरोध ;

	हाल ACTIONS(PC5_SIGNAL) :
		ACTIONS_DONE() ;
		fallthrough;
	हाल PC5_SIGNAL :
		अगर ((cmd != PC_SIGNAL) && (cmd != PC_TIMEOUT_LCT))
			अवरोध ;
		चयन (plc->p_state) अणु
		हाल PS_BIT3 :
			क्रम (i = 0 ; i <= 2 ; i++)
				pc_rcode_actions(smc,i,phy) ;
			pc_tcode_actions(smc,3,phy) ;
			plc->p_state = PS_BIT4 ;
			plc->p_bits = 1 ;
			plc->p_start = 3 ;
			phy->bitn = 3 ;
			अगर (plc_send_bits(smc,phy,1)) अणु
				वापस ;
			पूर्ण
			अवरोध ;
		हाल PS_BIT4 :
			pc_rcode_actions(smc,3,phy) ;
			क्रम (i = 4 ; i <= 6 ; i++)
				pc_tcode_actions(smc,i,phy) ;
			plc->p_state = PS_BIT7 ;
			plc->p_bits = 3 ;
			plc->p_start = 4 ;
			phy->bitn = 4 ;
			अगर (plc_send_bits(smc,phy,3)) अणु
				वापस ;
			पूर्ण
			अवरोध ;
		हाल PS_BIT7 :
			क्रम (i = 3 ; i <= 6 ; i++)
				pc_rcode_actions(smc,i,phy) ;
			plc->p_state = PS_LCT ;
			plc->p_bits = 0 ;
			plc->p_start = 7 ;
			phy->bitn = 7 ;
		sm_ph_lem_start(smc,np,(पूर्णांक)smc->s.lct_लघु) ; /* enable LEM */
			/* start LCT */
			i = inpw(PLC(np,PL_CNTRL_B)) & ~PL_PC_LOOP ;
			outpw(PLC(np,PL_CNTRL_B),i) ;	/* must be cleared */
			outpw(PLC(np,PL_CNTRL_B),i | PL_RLBP) ;
			अवरोध ;
		हाल PS_LCT :
			/* check क्रम local LCT failure */
			pc_tcode_actions(smc,7,phy) ;
			/*
			 * set tval[7]
			 */
			plc->p_state = PS_BIT8 ;
			plc->p_bits = 1 ;
			plc->p_start = 7 ;
			phy->bitn = 7 ;
			अगर (plc_send_bits(smc,phy,1)) अणु
				वापस ;
			पूर्ण
			अवरोध ;
		हाल PS_BIT8 :
			/* check क्रम remote LCT failure */
			pc_rcode_actions(smc,7,phy) ;
			अगर (phy->t_val[7] || phy->r_val[7]) अणु
				plc_go_state(smc,np,PL_PCM_STOP) ;
				GO_STATE(PC1_BREAK) ;
				अवरोध ;
			पूर्ण
			क्रम (i = 8 ; i <= 9 ; i++)
				pc_tcode_actions(smc,i,phy) ;
			plc->p_state = PS_JOIN ;
			plc->p_bits = 2 ;
			plc->p_start = 8 ;
			phy->bitn = 8 ;
			अगर (plc_send_bits(smc,phy,2)) अणु
				वापस ;
			पूर्ण
			अवरोध ;
		हाल PS_JOIN :
			क्रम (i = 8 ; i <= 9 ; i++)
				pc_rcode_actions(smc,i,phy) ;
			plc->p_state = PS_ACTIVE ;
			GO_STATE(PC6_JOIN) ;
			अवरोध ;
		पूर्ण
		अवरोध ;

	हाल ACTIONS(PC6_JOIN) :
		/*
		 * prevent mux error when going from WRAP_A to WRAP_B
		 */
		अगर (smc->s.sas == SMT_DAS && np == PB &&
			(smc->y[PA].pc_mode == PM_TREE ||
			 smc->y[PB].pc_mode == PM_TREE)) अणु
			SETMASK(PLC(np,PL_CNTRL_A),
				PL_SC_REM_LOOP,PL_SC_REM_LOOP) ;
			SETMASK(PLC(np,PL_CNTRL_B),
				PL_CONFIG_CNTRL,PL_CONFIG_CNTRL) ;
		पूर्ण
		SETMASK(PLC(np,PL_CNTRL_B),PL_PC_JOIN,PL_PC_JOIN) ;
		SETMASK(PLC(np,PL_CNTRL_B),PL_PC_JOIN,PL_PC_JOIN) ;
		ACTIONS_DONE() ;
		cmd = 0 ;
		fallthrough;
	हाल PC6_JOIN :
		चयन (plc->p_state) अणु
		हाल PS_ACTIVE:
			/*PC88b*/
			अगर (!phy->cf_join) अणु
				phy->cf_join = TRUE ;
				queue_event(smc,EVENT_CFM,CF_JOIN+np) ;
			पूर्ण
			अगर (cmd == PC_JOIN)
				GO_STATE(PC8_ACTIVE) ;
			/*PC82*/
			अगर (cmd == PC_TRACE) अणु
				GO_STATE(PC2_TRACE) ;
				अवरोध ;
			पूर्ण
			अवरोध ;
		पूर्ण
		अवरोध ;

	हाल PC7_VERIFY :
		अवरोध ;

	हाल ACTIONS(PC8_ACTIVE) :
		/*
		 * start LEM क्रम SMT
		 */
		sm_ph_lem_start(smc,(पूर्णांक)phy->np,LCT_LEM_MAX) ;

		phy->tr_flag = FALSE ;
		mib->fddiPORTConnectState = PCM_ACTIVE ;

		/* Set the active पूर्णांकerrupt mask रेजिस्टर */
		outpw(PLC(np,PL_INTR_MASK),plc_imsk_act) ;

		ACTIONS_DONE() ;
		अवरोध ;
	हाल PC8_ACTIVE :
		/*PC81 is करोne by PL_TNE_EXPIRED irq */
		/*PC82*/
		अगर (cmd == PC_TRACE) अणु
			GO_STATE(PC2_TRACE) ;
			अवरोध ;
		पूर्ण
		/*PC88c: is करोne by TRACE_PROP irq */

		अवरोध ;
	हाल ACTIONS(PC9_MAINT) :
		stop_pcm_समयr0(smc,phy) ;
		CLEAR(PLC(np,PL_CNTRL_B),PL_PC_JOIN) ;
		CLEAR(PLC(np,PL_CNTRL_B),PL_LONG) ;
		CLEAR(PLC(np,PL_INTR_MASK),PL_LE_CTR) ;	/* disable LEM पूर्णांक. */
		sm_ph_lem_stop(smc,np) ;		/* disable LEM */
		phy->cf_loop = FALSE ;
		phy->cf_join = FALSE ;
		queue_event(smc,EVENT_CFM,CF_JOIN+np) ;
		plc_go_state(smc,np,PL_PCM_STOP) ;
		mib->fddiPORTConnectState = PCM_DISABLED ;
		SETMASK(PLC(np,PL_CNTRL_B),PL_MAINT,PL_MAINT) ;
		sm_ph_linestate(smc,np,(पूर्णांक) MIB2LS(mib->fddiPORTMaपूर्णांक_LS)) ;
		outpw(PLC(np,PL_CNTRL_A),PL_SC_BYPASS) ;
		ACTIONS_DONE() ;
		अवरोध ;
	हाल PC9_MAINT :
		DB_PCMN(1, "PCM %c : MAINT", phy->phy_name);
		/*PC90*/
		अगर (cmd == PC_ENABLE) अणु
			GO_STATE(PC0_OFF) ;
			अवरोध ;
		पूर्ण
		अवरोध ;

	शेष:
		SMT_PANIC(smc,SMT_E0118, SMT_E0118_MSG) ;
		अवरोध ;
	पूर्ण
पूर्ण

/*
 * क्रमce line state on a PHY output	(only in MAINT state)
 */
अटल व्योम sm_ph_linestate(काष्ठा s_smc *smc, पूर्णांक phy, पूर्णांक ls)
अणु
	पूर्णांक	cntrl ;

	SK_UNUSED(smc) ;

	cntrl = (inpw(PLC(phy,PL_CNTRL_B)) & ~PL_MAINT_LS) |
						PL_PCM_STOP | PL_MAINT ;
	चयन(ls) अणु
	हाल PC_QLS: 		/* Force Quiet */
		cntrl |= PL_M_QUI0 ;
		अवरोध ;
	हाल PC_MLS: 		/* Force Master */
		cntrl |= PL_M_MASTR ;
		अवरोध ;
	हाल PC_HLS: 		/* Force Halt */
		cntrl |= PL_M_HALT ;
		अवरोध ;
	शेष :
	हाल PC_ILS: 		/* Force Idle */
		cntrl |= PL_M_IDLE ;
		अवरोध ;
	हाल PC_LS_PDR: 	/* Enable repeat filter */
		cntrl |= PL_M_TPDR ;
		अवरोध ;
	पूर्ण
	outpw(PLC(phy,PL_CNTRL_B),cntrl) ;
पूर्ण

अटल व्योम reset_lem_काष्ठा(काष्ठा s_phy *phy)
अणु
	काष्ठा lem_counter *lem = &phy->lem ;

	phy->mib->fddiPORTLer_Estimate = 15 ;
	lem->lem_भग्न_ber = 15 * 100 ;
पूर्ण

/*
 * link error monitor
 */
अटल व्योम lem_evaluate(काष्ठा s_smc *smc, काष्ठा s_phy *phy)
अणु
	पूर्णांक ber ;
	u_दीर्घ errors ;
	काष्ठा lem_counter *lem = &phy->lem ;
	काष्ठा fddi_mib_p	*mib ;
	पूर्णांक			cond ;

	mib = phy->mib ;

	अगर (!lem->lem_on)
		वापस ;

	errors = inpw(PLC(((पूर्णांक) phy->np),PL_LINK_ERR_CTR)) ;
	lem->lem_errors += errors ;
	mib->fddiPORTLem_Ct += errors ;

	errors = lem->lem_errors ;
	/*
	 * calculation is called on a पूर्णांकervall of 8 seconds
	 *	-> this means, that one error in 8 sec. is one of 8*125*10E6
	 *	the same as BER = 10E-9
	 * Please note:
	 *	-> 9 errors in 8 seconds mean:
	 *	   BER = 9 * 10E-9  and this is
	 *	    < 10E-8, so the limit of 10E-8 is not reached!
	 */

		अगर (!errors)		ber = 15 ;
	अन्यथा	अगर (errors <= 9)	ber = 9 ;
	अन्यथा	अगर (errors <= 99)	ber = 8 ;
	अन्यथा	अगर (errors <= 999)	ber = 7 ;
	अन्यथा	अगर (errors <= 9999)	ber = 6 ;
	अन्यथा	अगर (errors <= 99999)	ber = 5 ;
	अन्यथा	अगर (errors <= 999999)	ber = 4 ;
	अन्यथा	अगर (errors <= 9999999)	ber = 3 ;
	अन्यथा	अगर (errors <= 99999999)	ber = 2 ;
	अन्यथा	अगर (errors <= 999999999) ber = 1 ;
	अन्यथा				ber = 0 ;

	/*
	 * weighted average
	 */
	ber *= 100 ;
	lem->lem_भग्न_ber = lem->lem_भग्न_ber * 7 + ber * 3 ;
	lem->lem_भग्न_ber /= 10 ;
	mib->fddiPORTLer_Estimate = lem->lem_भग्न_ber / 100 ;
	अगर (mib->fddiPORTLer_Estimate < 4) अणु
		mib->fddiPORTLer_Estimate = 4 ;
	पूर्ण

	अगर (lem->lem_errors) अणु
		DB_PCMN(1, "LEM %c :", phy->np == PB ? 'B' : 'A');
		DB_PCMN(1, "errors      : %ld", lem->lem_errors);
		DB_PCMN(1, "sum_errors  : %ld", mib->fddiPORTLem_Ct);
		DB_PCMN(1, "current BER : 10E-%d", ber / 100);
		DB_PCMN(1, "float BER   : 10E-(%d/100)", lem->lem_भग्न_ber);
		DB_PCMN(1, "avg. BER    : 10E-%d", mib->fddiPORTLer_Estimate);
	पूर्ण

	lem->lem_errors = 0L ;

#अगर_अघोषित	SLIM_SMT
	cond = (mib->fddiPORTLer_Estimate <= mib->fddiPORTLer_Alarm) ?
		TRUE : FALSE ;
#अगर_घोषित	SMT_EXT_CUTOFF
	smt_ler_alarm_check(smc,phy,cond) ;
#पूर्ण_अगर	/* nSMT_EXT_CUTOFF */
	अगर (cond != mib->fddiPORTLerFlag) अणु
		smt_srf_event(smc,SMT_COND_PORT_LER,
			(पूर्णांक) (INDEX_PORT+ phy->np) ,cond) ;
	पूर्ण
#पूर्ण_अगर

	अगर (	mib->fddiPORTLer_Estimate <= mib->fddiPORTLer_Cutoff) अणु
		phy->pc_lem_fail = TRUE ;		/* flag */
		mib->fddiPORTLem_Reject_Ct++ ;
		/*
		 * "forgive 10e-2" अगर we cutoff so we can come
		 * up again ..
		 */
		lem->lem_भग्न_ber += 2*100 ;

		/*PC81b*/
#अगर_घोषित	CONCENTRATOR
		DB_PCMN(1, "PCM: LER cutoff on port %d cutoff %d",
			phy->np, mib->fddiPORTLer_Cutoff);
#पूर्ण_अगर
#अगर_घोषित	SMT_EXT_CUTOFF
		smt_port_off_event(smc,phy->np);
#अन्यथा	/* nSMT_EXT_CUTOFF */
		queue_event(smc,(पूर्णांक)(EVENT_PCM+phy->np),PC_START) ;
#पूर्ण_अगर	/* nSMT_EXT_CUTOFF */
	पूर्ण
पूर्ण

/*
 * called by SMT to calculate LEM bit error rate
 */
व्योम sm_lem_evaluate(काष्ठा s_smc *smc)
अणु
	पूर्णांक np ;

	क्रम (np = 0 ; np < NUMPHYS ; np++)
		lem_evaluate(smc,&smc->y[np]) ;
पूर्ण

अटल व्योम lem_check_lct(काष्ठा s_smc *smc, काष्ठा s_phy *phy)
अणु
	काष्ठा lem_counter	*lem = &phy->lem ;
	काष्ठा fddi_mib_p	*mib ;
	पूर्णांक errors ;

	mib = phy->mib ;

	phy->pc_lem_fail = FALSE ;		/* flag */
	errors = inpw(PLC(((पूर्णांक)phy->np),PL_LINK_ERR_CTR)) ;
	lem->lem_errors += errors ;
	mib->fddiPORTLem_Ct += errors ;
	अगर (lem->lem_errors) अणु
		चयन(phy->lc_test) अणु
		हाल LC_SHORT:
			अगर (lem->lem_errors >= smc->s.lct_लघु)
				phy->pc_lem_fail = TRUE ;
			अवरोध ;
		हाल LC_MEDIUM:
			अगर (lem->lem_errors >= smc->s.lct_medium)
				phy->pc_lem_fail = TRUE ;
			अवरोध ;
		हाल LC_LONG:
			अगर (lem->lem_errors >= smc->s.lct_दीर्घ)
				phy->pc_lem_fail = TRUE ;
			अवरोध ;
		हाल LC_EXTENDED:
			अगर (lem->lem_errors >= smc->s.lct_extended)
				phy->pc_lem_fail = TRUE ;
			अवरोध ;
		पूर्ण
		DB_PCMN(1, " >>errors : %lu", lem->lem_errors);
	पूर्ण
	अगर (phy->pc_lem_fail) अणु
		mib->fddiPORTLCTFail_Ct++ ;
		mib->fddiPORTLem_Reject_Ct++ ;
	पूर्ण
	अन्यथा
		mib->fddiPORTLCTFail_Ct = 0 ;
पूर्ण

/*
 * LEM functions
 */
अटल व्योम sm_ph_lem_start(काष्ठा s_smc *smc, पूर्णांक np, पूर्णांक threshold)
अणु
	काष्ठा lem_counter *lem = &smc->y[np].lem ;

	lem->lem_on = 1 ;
	lem->lem_errors = 0L ;

	/* Do NOT reset mib->fddiPORTLer_Estimate here. It is called too
	 * often.
	 */

	outpw(PLC(np,PL_LE_THRESHOLD),threshold) ;
	(व्योम)inpw(PLC(np,PL_LINK_ERR_CTR)) ;	/* clear error counter */

	/* enable LE INT */
	SETMASK(PLC(np,PL_INTR_MASK),PL_LE_CTR,PL_LE_CTR) ;
पूर्ण

अटल व्योम sm_ph_lem_stop(काष्ठा s_smc *smc, पूर्णांक np)
अणु
	काष्ठा lem_counter *lem = &smc->y[np].lem ;

	lem->lem_on = 0 ;
	CLEAR(PLC(np,PL_INTR_MASK),PL_LE_CTR) ;
पूर्ण

/*
 * PCM pseuकरो code
 * receive actions are called AFTER the bit n is received,
 * i.e. अगर pc_rcode_actions(5) is called, bit 6 is the next bit to be received
 */

/*
 * PCM pseuकरो code 5.1 .. 6.1
 */
अटल व्योम pc_rcode_actions(काष्ठा s_smc *smc, पूर्णांक bit, काष्ठा s_phy *phy)
अणु
	काष्ठा fddi_mib_p	*mib ;

	mib = phy->mib ;

	DB_PCMN(1, "SIG rec %x %x:", bit, phy->r_val[bit]);
	bit++ ;

	चयन(bit) अणु
	हाल 0:
	हाल 1:
	हाल 2:
		अवरोध ;
	हाल 3 :
		अगर (phy->r_val[1] == 0 && phy->r_val[2] == 0)
			mib->fddiPORTNeighborType = TA ;
		अन्यथा अगर (phy->r_val[1] == 0 && phy->r_val[2] == 1)
			mib->fddiPORTNeighborType = TB ;
		अन्यथा अगर (phy->r_val[1] == 1 && phy->r_val[2] == 0)
			mib->fddiPORTNeighborType = TS ;
		अन्यथा अगर (phy->r_val[1] == 1 && phy->r_val[2] == 1)
			mib->fddiPORTNeighborType = TM ;
		अवरोध ;
	हाल 4:
		अगर (mib->fddiPORTMy_Type == TM &&
			mib->fddiPORTNeighborType == TM) अणु
			DB_PCMN(1, "PCM %c : E100 withhold M-M",
				phy->phy_name);
			mib->fddiPORTPC_Withhold = PC_WH_M_M ;
			RS_SET(smc,RS_EVENT) ;
		पूर्ण
		अन्यथा अगर (phy->t_val[3] || phy->r_val[3]) अणु
			mib->fddiPORTPC_Withhold = PC_WH_NONE ;
			अगर (mib->fddiPORTMy_Type == TM ||
			    mib->fddiPORTNeighborType == TM)
				phy->pc_mode = PM_TREE ;
			अन्यथा
				phy->pc_mode = PM_PEER ;

			/* reevaluate the selection criteria (wc_flag) */
			all_selection_criteria (smc);

			अगर (phy->wc_flag) अणु
				mib->fddiPORTPC_Withhold = PC_WH_PATH ;
			पूर्ण
		पूर्ण
		अन्यथा अणु
			mib->fddiPORTPC_Withhold = PC_WH_OTHER ;
			RS_SET(smc,RS_EVENT) ;
			DB_PCMN(1, "PCM %c : E101 withhold other",
				phy->phy_name);
		पूर्ण
		phy->twisted = ((mib->fddiPORTMy_Type != TS) &&
				(mib->fddiPORTMy_Type != TM) &&
				(mib->fddiPORTNeighborType ==
				mib->fddiPORTMy_Type)) ;
		अगर (phy->twisted) अणु
			DB_PCMN(1, "PCM %c : E102 !!! TWISTED !!!",
				phy->phy_name);
		पूर्ण
		अवरोध ;
	हाल 5 :
		अवरोध ;
	हाल 6:
		अगर (phy->t_val[4] || phy->r_val[4]) अणु
			अगर ((phy->t_val[4] && phy->t_val[5]) ||
			    (phy->r_val[4] && phy->r_val[5]) )
				phy->lc_test = LC_EXTENDED ;
			अन्यथा
				phy->lc_test = LC_LONG ;
		पूर्ण
		अन्यथा अगर (phy->t_val[5] || phy->r_val[5])
			phy->lc_test = LC_MEDIUM ;
		अन्यथा
			phy->lc_test = LC_SHORT ;
		चयन (phy->lc_test) अणु
		हाल LC_SHORT :				/* 50ms */
			outpw(PLC((पूर्णांक)phy->np,PL_LC_LENGTH), TP_LC_LENGTH ) ;
			phy->t_next[7] = smc->s.pcm_lc_लघु ;
			अवरोध ;
		हाल LC_MEDIUM :			/* 500ms */
			outpw(PLC((पूर्णांक)phy->np,PL_LC_LENGTH), TP_LC_LONGLN ) ;
			phy->t_next[7] = smc->s.pcm_lc_medium ;
			अवरोध ;
		हाल LC_LONG :
			SETMASK(PLC((पूर्णांक)phy->np,PL_CNTRL_B),PL_LONG,PL_LONG) ;
			phy->t_next[7] = smc->s.pcm_lc_दीर्घ ;
			अवरोध ;
		हाल LC_EXTENDED :
			SETMASK(PLC((पूर्णांक)phy->np,PL_CNTRL_B),PL_LONG,PL_LONG) ;
			phy->t_next[7] = smc->s.pcm_lc_extended ;
			अवरोध ;
		पूर्ण
		अगर (phy->t_next[7] > smc->s.pcm_lc_medium) अणु
			start_pcm_समयr0(smc,phy->t_next[7],PC_TIMEOUT_LCT,phy);
		पूर्ण
		DB_PCMN(1, "LCT timer = %ld us", phy->t_next[7]);
		phy->t_next[9] = smc->s.pcm_t_next_9 ;
		अवरोध ;
	हाल 7:
		अगर (phy->t_val[6]) अणु
			phy->cf_loop = TRUE ;
		पूर्ण
		phy->td_flag = TRUE ;
		अवरोध ;
	हाल 8:
		अगर (phy->t_val[7] || phy->r_val[7]) अणु
			DB_PCMN(1, "PCM %c : E103 LCT fail %s",
				phy->phy_name,
				phy->t_val[7] ? "local" : "remote");
			queue_event(smc,(पूर्णांक)(EVENT_PCM+phy->np),PC_START) ;
		पूर्ण
		अवरोध ;
	हाल 9:
		अगर (phy->t_val[8] || phy->r_val[8]) अणु
			अगर (phy->t_val[8])
				phy->cf_loop = TRUE ;
			phy->td_flag = TRUE ;
		पूर्ण
		अवरोध ;
	हाल 10:
		अगर (phy->r_val[9]) अणु
			/* neighbor पूर्णांकends to have MAC on output */ ;
			mib->fddiPORTMacIndicated.R_val = TRUE ;
		पूर्ण
		अन्यथा अणु
			/* neighbor करोes not पूर्णांकend to have MAC on output */ ;
			mib->fddiPORTMacIndicated.R_val = FALSE ;
		पूर्ण
		अवरोध ;
	पूर्ण
पूर्ण

/*
 * PCM pseuकरो code 5.1 .. 6.1
 */
अटल व्योम pc_tcode_actions(काष्ठा s_smc *smc, स्थिर पूर्णांक bit, काष्ठा s_phy *phy)
अणु
	पूर्णांक	np = phy->np ;
	काष्ठा fddi_mib_p	*mib ;

	mib = phy->mib ;

	चयन(bit) अणु
	हाल 0:
		phy->t_val[0] = 0 ;		/* no escape used */
		अवरोध ;
	हाल 1:
		अगर (mib->fddiPORTMy_Type == TS || mib->fddiPORTMy_Type == TM)
			phy->t_val[1] = 1 ;
		अन्यथा
			phy->t_val[1] = 0 ;
		अवरोध ;
	हाल 2 :
		अगर (mib->fddiPORTMy_Type == TB || mib->fddiPORTMy_Type == TM)
			phy->t_val[2] = 1 ;
		अन्यथा
			phy->t_val[2] = 0 ;
		अवरोध ;
	हाल 3:
		अणु
		पूर्णांक	type,ne ;
		पूर्णांक	policy ;

		type = mib->fddiPORTMy_Type ;
		ne = mib->fddiPORTNeighborType ;
		policy = smc->mib.fddiSMTConnectionPolicy ;

		phy->t_val[3] = 1 ;	/* Accept connection */
		चयन (type) अणु
		हाल TA :
			अगर (
				((policy & POLICY_AA) && ne == TA) ||
				((policy & POLICY_AB) && ne == TB) ||
				((policy & POLICY_AS) && ne == TS) ||
				((policy & POLICY_AM) && ne == TM) )
				phy->t_val[3] = 0 ;	/* Reject */
			अवरोध ;
		हाल TB :
			अगर (
				((policy & POLICY_BA) && ne == TA) ||
				((policy & POLICY_BB) && ne == TB) ||
				((policy & POLICY_BS) && ne == TS) ||
				((policy & POLICY_BM) && ne == TM) )
				phy->t_val[3] = 0 ;	/* Reject */
			अवरोध ;
		हाल TS :
			अगर (
				((policy & POLICY_SA) && ne == TA) ||
				((policy & POLICY_SB) && ne == TB) ||
				((policy & POLICY_SS) && ne == TS) ||
				((policy & POLICY_SM) && ne == TM) )
				phy->t_val[3] = 0 ;	/* Reject */
			अवरोध ;
		हाल TM :
			अगर (	ne == TM ||
				((policy & POLICY_MA) && ne == TA) ||
				((policy & POLICY_MB) && ne == TB) ||
				((policy & POLICY_MS) && ne == TS) ||
				((policy & POLICY_MM) && ne == TM) )
				phy->t_val[3] = 0 ;	/* Reject */
			अवरोध ;
		पूर्ण
#अगर_अघोषित	SLIM_SMT
		/*
		 * detect undesirable connection attempt event
		 */
		अगर (	(type == TA && ne == TA ) ||
			(type == TA && ne == TS ) ||
			(type == TB && ne == TB ) ||
			(type == TB && ne == TS ) ||
			(type == TS && ne == TA ) ||
			(type == TS && ne == TB ) ) अणु
			smt_srf_event(smc,SMT_EVENT_PORT_CONNECTION,
				(पूर्णांक) (INDEX_PORT+ phy->np) ,0) ;
		पूर्ण
#पूर्ण_अगर
		पूर्ण
		अवरोध ;
	हाल 4:
		अगर (mib->fddiPORTPC_Withhold == PC_WH_NONE) अणु
			अगर (phy->pc_lem_fail) अणु
				phy->t_val[4] = 1 ;	/* दीर्घ */
				phy->t_val[5] = 0 ;
			पूर्ण
			अन्यथा अणु
				phy->t_val[4] = 0 ;
				अगर (mib->fddiPORTLCTFail_Ct > 0)
					phy->t_val[5] = 1 ;	/* medium */
				अन्यथा
					phy->t_val[5] = 0 ;	/* लघु */

				/*
				 * Implementers choice: use medium
				 * instead of लघु when undesired
				 * connection attempt is made.
				 */
				अगर (phy->wc_flag)
					phy->t_val[5] = 1 ;	/* medium */
			पूर्ण
			mib->fddiPORTConnectState = PCM_CONNECTING ;
		पूर्ण
		अन्यथा अणु
			mib->fddiPORTConnectState = PCM_STANDBY ;
			phy->t_val[4] = 1 ;	/* extended */
			phy->t_val[5] = 1 ;
		पूर्ण
		अवरोध ;
	हाल 5:
		अवरोध ;
	हाल 6:
		/* we करो NOT have a MAC क्रम LCT */
		phy->t_val[6] = 0 ;
		अवरोध ;
	हाल 7:
		phy->cf_loop = FALSE ;
		lem_check_lct(smc,phy) ;
		अगर (phy->pc_lem_fail) अणु
			DB_PCMN(1, "PCM %c : E104 LCT failed", phy->phy_name);
			phy->t_val[7] = 1 ;
		पूर्ण
		अन्यथा
			phy->t_val[7] = 0 ;
		अवरोध ;
	हाल 8:
		phy->t_val[8] = 0 ;	/* Don't request MAC loopback */
		अवरोध ;
	हाल 9:
		phy->cf_loop = 0 ;
		अगर ((mib->fddiPORTPC_Withhold != PC_WH_NONE) ||
		     ((smc->s.sas == SMT_DAS) && (phy->wc_flag))) अणु
			queue_event(smc,EVENT_PCM+np,PC_START) ;
			अवरोध ;
		पूर्ण
		phy->t_val[9] = FALSE ;
		चयन (smc->s.sas) अणु
		हाल SMT_DAS :
			/*
			 * MAC पूर्णांकended on output
			 */
			अगर (phy->pc_mode == PM_TREE) अणु
				अगर ((np == PB) || ((np == PA) &&
				(smc->y[PB].mib->fddiPORTConnectState !=
					PCM_ACTIVE)))
					phy->t_val[9] = TRUE ;
			पूर्ण
			अन्यथा अणु
				अगर (np == PB)
					phy->t_val[9] = TRUE ;
			पूर्ण
			अवरोध ;
		हाल SMT_SAS :
			अगर (np == PS)
				phy->t_val[9] = TRUE ;
			अवरोध ;
#अगर_घोषित	CONCENTRATOR
		हाल SMT_NAC :
			/*
			 * MAC पूर्णांकended on output
			 */
			अगर (np == PB)
				phy->t_val[9] = TRUE ;
			अवरोध ;
#पूर्ण_अगर
		पूर्ण
		mib->fddiPORTMacIndicated.T_val = phy->t_val[9] ;
		अवरोध ;
	पूर्ण
	DB_PCMN(1, "SIG snd %x %x:", bit, phy->t_val[bit]);
पूर्ण

/*
 * वापस status twisted (called by SMT)
 */
पूर्णांक pcm_status_twisted(काष्ठा s_smc *smc)
अणु
	पूर्णांक	twist = 0 ;
	अगर (smc->s.sas != SMT_DAS)
		वापस 0;
	अगर (smc->y[PA].twisted && (smc->y[PA].mib->fddiPORTPCMState == PC8_ACTIVE))
		twist |= 1 ;
	अगर (smc->y[PB].twisted && (smc->y[PB].mib->fddiPORTPCMState == PC8_ACTIVE))
		twist |= 2 ;
	वापस twist;
पूर्ण

/*
 * वापस status	(called by SMT)
 *	type
 *	state
 *	remote phy type
 *	remote mac yes/no
 */
व्योम pcm_status_state(काष्ठा s_smc *smc, पूर्णांक np, पूर्णांक *type, पूर्णांक *state,
		      पूर्णांक *remote, पूर्णांक *mac)
अणु
	काष्ठा s_phy	*phy = &smc->y[np] ;
	काष्ठा fddi_mib_p	*mib ;

	mib = phy->mib ;

	/* remote PHY type and MAC - set only अगर active */
	*mac = 0 ;
	*type = mib->fddiPORTMy_Type ;		/* our PHY type */
	*state = mib->fddiPORTConnectState ;
	*remote = mib->fddiPORTNeighborType ;

	चयन(mib->fddiPORTPCMState) अणु
	हाल PC8_ACTIVE :
		*mac = mib->fddiPORTMacIndicated.R_val ;
		अवरोध ;
	पूर्ण
पूर्ण

/*
 * वापस rooted station status (called by SMT)
 */
पूर्णांक pcm_rooted_station(काष्ठा s_smc *smc)
अणु
	पूर्णांक	n ;

	क्रम (n = 0 ; n < NUMPHYS ; n++) अणु
		अगर (smc->y[n].mib->fddiPORTPCMState == PC8_ACTIVE &&
		    smc->y[n].mib->fddiPORTNeighborType == TM)
			वापस 0;
	पूर्ण
	वापस 1;
पूर्ण

/*
 * Interrupt actions क्रम PLC & PCM events
 */
व्योम plc_irq(काष्ठा s_smc *smc, पूर्णांक np, अचिन्हित पूर्णांक cmd)
/* पूर्णांक np;	PHY index */
अणु
	काष्ठा s_phy *phy = &smc->y[np] ;
	काष्ठा s_plc *plc = &phy->plc ;
	पूर्णांक		n ;
#अगर_घोषित	SUPERNET_3
	पूर्णांक		corr_mask ;
#पूर्ण_अगर	/* SUPERNET_3 */
	पूर्णांक		i ;

	अगर (np >= smc->s.numphys) अणु
		plc->soft_err++ ;
		वापस ;
	पूर्ण
	अगर (cmd & PL_EBUF_ERR) अणु	/* elastic buff. det. over-|underflow*/
		/*
		 * Check whether the SRF Condition occurred.
		 */
		अगर (!plc->ebuf_cont && phy->mib->fddiPORTPCMState == PC8_ACTIVE)अणु
			/*
			 * This is the real Elasticity Error.
			 * More than one in a row are treated as a
			 * single one.
			 * Only count this in the active state.
			 */
			phy->mib->fddiPORTEBError_Ct ++ ;

		पूर्ण

		plc->ebuf_err++ ;
		अगर (plc->ebuf_cont <= 1000) अणु
			/*
			 * Prevent counter from being wrapped after
			 * hanging years in that पूर्णांकerrupt.
			 */
			plc->ebuf_cont++ ;	/* Ebuf continuous error */
		पूर्ण

#अगर_घोषित	SUPERNET_3
		अगर (plc->ebuf_cont == 1000 &&
			((inpw(PLC(np,PL_STATUS_A)) & PLC_REV_MASK) ==
			PLC_REV_SN3)) अणु
			/*
			 * This पूर्णांकerrupt remeained high क्रम at least
			 * 1000 consecutive पूर्णांकerrupt calls.
			 *
			 * This is caused by a hardware error of the
			 * ORION part of the Supernet III chipset.
			 *
			 * Disable this bit from the mask.
			 */
			corr_mask = (plc_imsk_na & ~PL_EBUF_ERR) ;
			outpw(PLC(np,PL_INTR_MASK),corr_mask);

			/*
			 * Disconnect from the ring.
			 * Call the driver with the reset indication.
			 */
			queue_event(smc,EVENT_ECM,EC_DISCONNECT) ;

			/*
			 * Make an error log entry.
			 */
			SMT_ERR_LOG(smc,SMT_E0136, SMT_E0136_MSG) ;

			/*
			 * Indicate the Reset.
			 */
			drv_reset_indication(smc) ;
		पूर्ण
#पूर्ण_अगर	/* SUPERNET_3 */
	पूर्ण अन्यथा अणु
		/* Reset the continuous error variable */
		plc->ebuf_cont = 0 ;	/* reset Ebuf continuous error */
	पूर्ण
	अगर (cmd & PL_PHYINV) अणु		/* physical layer invalid संकेत */
		plc->phyinv++ ;
	पूर्ण
	अगर (cmd & PL_VSYM_CTR) अणु	/* violation symbol counter has incr.*/
		plc->vsym_ctr++ ;
	पूर्ण
	अगर (cmd & PL_MINI_CTR) अणु	/* dep. on PLC_CNTRL_A's MINI_CTR_INT*/
		plc->mini_ctr++ ;
	पूर्ण
	अगर (cmd & PL_LE_CTR) अणु		/* link error event counter */
		पूर्णांक	j ;

		/*
		 * note: PL_LINK_ERR_CTR MUST be पढ़ो to clear it
		 */
		j = inpw(PLC(np,PL_LE_THRESHOLD)) ;
		i = inpw(PLC(np,PL_LINK_ERR_CTR)) ;

		अगर (i < j) अणु
			/* wrapped around */
			i += 256 ;
		पूर्ण

		अगर (phy->lem.lem_on) अणु
			/* Note: Lem errors shall only be counted when
			 * link is ACTIVE or LCT is active.
			 */
			phy->lem.lem_errors += i ;
			phy->mib->fddiPORTLem_Ct += i ;
		पूर्ण
	पूर्ण
	अगर (cmd & PL_TPC_EXPIRED) अणु	/* TPC समयr reached zero */
		अगर (plc->p_state == PS_LCT) अणु
			/*
			 * end of LCT
			 */
			;
		पूर्ण
		plc->tpc_exp++ ;
	पूर्ण
	अगर (cmd & PL_LS_MATCH) अणु	/* LS == LS in PLC_CNTRL_B's MATCH_LS*/
		चयन (inpw(PLC(np,PL_CNTRL_B)) & PL_MATCH_LS) अणु
		हाल PL_I_IDLE :	phy->curr_ls = PC_ILS ;		अवरोध ;
		हाल PL_I_HALT :	phy->curr_ls = PC_HLS ;		अवरोध ;
		हाल PL_I_MASTR :	phy->curr_ls = PC_MLS ;		अवरोध ;
		हाल PL_I_QUIET :	phy->curr_ls = PC_QLS ;		अवरोध ;
		पूर्ण
	पूर्ण
	अगर (cmd & PL_PCM_BREAK) अणु	/* PCM has entered the BREAK state */
		पूर्णांक	reason;

		reason = inpw(PLC(np,PL_STATUS_B)) & PL_BREAK_REASON ;

		चयन (reason) अणु
		हाल PL_B_PCS :		plc->b_pcs++ ;	अवरोध ;
		हाल PL_B_TPC :		plc->b_tpc++ ;	अवरोध ;
		हाल PL_B_TNE :		plc->b_tne++ ;	अवरोध ;
		हाल PL_B_QLS :		plc->b_qls++ ;	अवरोध ;
		हाल PL_B_ILS :		plc->b_ils++ ;	अवरोध ;
		हाल PL_B_HLS :		plc->b_hls++ ;	अवरोध ;
		पूर्ण

		/*jd 05-Aug-1999 changed: Bug #10419 */
		DB_PCMN(1, "PLC %d: MDcF = %x", np, smc->e.DisconnectFlag);
		अगर (smc->e.DisconnectFlag == FALSE) अणु
			DB_PCMN(1, "PLC %d: restart (reason %x)", np, reason);
			queue_event(smc,EVENT_PCM+np,PC_START) ;
		पूर्ण
		अन्यथा अणु
			DB_PCMN(1, "PLC %d: NO!! restart (reason %x)",
				np, reason);
		पूर्ण
		वापस ;
	पूर्ण
	/*
	 * If both CODE & ENABLE are set ignore enable
	 */
	अगर (cmd & PL_PCM_CODE) अणु /* receive last sign.-bit | LCT complete */
		queue_event(smc,EVENT_PCM+np,PC_SIGNAL) ;
		n = inpw(PLC(np,PL_RCV_VECTOR)) ;
		क्रम (i = 0 ; i < plc->p_bits ; i++) अणु
			phy->r_val[plc->p_start+i] = n & 1 ;
			n >>= 1 ;
		पूर्ण
	पूर्ण
	अन्यथा अगर (cmd & PL_PCM_ENABLED) अणु /* निश्चितed SC_JOIN, scrub.completed*/
		queue_event(smc,EVENT_PCM+np,PC_JOIN) ;
	पूर्ण
	अगर (cmd & PL_TRACE_PROP) अणु	/* MLS जबतक PC8_ACTIV || PC2_TRACE */
		/*PC22b*/
		अगर (!phy->tr_flag) अणु
			DB_PCMN(1, "PCM : irq TRACE_PROP %d %d",
				np, smc->mib.fddiSMTECMState);
			phy->tr_flag = TRUE ;
			smc->e.trace_prop |= ENTITY_BIT(ENTITY_PHY(np)) ;
			queue_event(smc,EVENT_ECM,EC_TRACE_PROP) ;
		पूर्ण
	पूर्ण
	/*
	 * filter PLC glitch ???
	 * QLS || HLS only जबतक in PC2_TRACE state
	 */
	अगर ((cmd & PL_SELF_TEST) && (phy->mib->fddiPORTPCMState == PC2_TRACE)) अणु
		/*PC22a*/
		अगर (smc->e.path_test == PT_PASSED) अणु
			DB_PCMN(1, "PCM : state = %s %d",
				get_pcmstate(smc, np),
				phy->mib->fddiPORTPCMState);

			smc->e.path_test = PT_PENDING ;
			queue_event(smc,EVENT_ECM,EC_PATH_TEST) ;
		पूर्ण
	पूर्ण
	अगर (cmd & PL_TNE_EXPIRED) अणु	/* TNE: length of noise events */
		/* अवरोध_required (TNE > NS_Max) */
		अगर (phy->mib->fddiPORTPCMState == PC8_ACTIVE) अणु
			अगर (!phy->tr_flag) अणु
				DB_PCMN(1, "PCM %c : PC81 %s",
					phy->phy_name, "NSE");
				queue_event(smc, EVENT_PCM + np, PC_START);
				वापस;
			पूर्ण
		पूर्ण
	पूर्ण
#अगर	0
	अगर (cmd & PL_NP_ERR) अणु		/* NP has requested to r/w an inv reg*/
		/*
		 * It's a bug by AMD
		 */
		plc->np_err++ ;
	पूर्ण
	/* pin inactiv (GND) */
	अगर (cmd & PL_PARITY_ERR) अणु	/* p. error dedected on TX9-0 inp */
		plc->parity_err++ ;
	पूर्ण
	अगर (cmd & PL_LSDO) अणु		/* carrier detected */
		;
	पूर्ण
#पूर्ण_अगर
पूर्ण

#अगर_घोषित	DEBUG
/*
 * fill state काष्ठा
 */
व्योम pcm_get_state(काष्ठा s_smc *smc, काष्ठा smt_state *state)
अणु
	काष्ठा s_phy	*phy ;
	काष्ठा pcm_state *pcs ;
	पूर्णांक	i ;
	पूर्णांक	ii ;
	लघु	rbits ;
	लघु	tbits ;
	काष्ठा fddi_mib_p	*mib ;

	क्रम (i = 0, phy = smc->y, pcs = state->pcm_state ; i < NUMPHYS ;
		i++ , phy++, pcs++ ) अणु
		mib = phy->mib ;
		pcs->pcm_type = (u_अक्षर) mib->fddiPORTMy_Type ;
		pcs->pcm_state = (u_अक्षर) mib->fddiPORTPCMState ;
		pcs->pcm_mode = phy->pc_mode ;
		pcs->pcm_neighbor = (u_अक्षर) mib->fddiPORTNeighborType ;
		pcs->pcm_bsf = mib->fddiPORTBS_Flag ;
		pcs->pcm_lsf = phy->ls_flag ;
		pcs->pcm_lct_fail = (u_अक्षर) mib->fddiPORTLCTFail_Ct ;
		pcs->pcm_ls_rx = LS2MIB(sm_pm_get_ls(smc,i)) ;
		क्रम (ii = 0, rbits = tbits = 0 ; ii < NUMBITS ; ii++) अणु
			rbits <<= 1 ;
			tbits <<= 1 ;
			अगर (phy->r_val[NUMBITS-1-ii])
				rbits |= 1 ;
			अगर (phy->t_val[NUMBITS-1-ii])
				tbits |= 1 ;
		पूर्ण
		pcs->pcm_r_val = rbits ;
		pcs->pcm_t_val = tbits ;
	पूर्ण
पूर्ण

पूर्णांक get_pcm_state(काष्ठा s_smc *smc, पूर्णांक np)
अणु
	पूर्णांक pcs ;

	SK_UNUSED(smc) ;

	चयन (inpw(PLC(np,PL_STATUS_B)) & PL_PCM_STATE) अणु
		हाल PL_PC0 :	pcs = PC_STOP ;		अवरोध ;
		हाल PL_PC1 :	pcs = PC_START ;	अवरोध ;
		हाल PL_PC2 :	pcs = PC_TRACE ;	अवरोध ;
		हाल PL_PC3 :	pcs = PC_SIGNAL ;	अवरोध ;
		हाल PL_PC4 :	pcs = PC_SIGNAL ;	अवरोध ;
		हाल PL_PC5 :	pcs = PC_SIGNAL ;	अवरोध ;
		हाल PL_PC6 :	pcs = PC_JOIN ;		अवरोध ;
		हाल PL_PC7 :	pcs = PC_JOIN ;		अवरोध ;
		हाल PL_PC8 :	pcs = PC_ENABLE ;	अवरोध ;
		हाल PL_PC9 :	pcs = PC_MAINT ;	अवरोध ;
		शेष :	pcs = PC_DISABLE ; 	अवरोध ;
	पूर्ण
	वापस pcs;
पूर्ण

अक्षर *get_linestate(काष्ठा s_smc *smc, पूर्णांक np)
अणु
	अक्षर *ls = "" ;

	SK_UNUSED(smc) ;

	चयन (inpw(PLC(np,PL_STATUS_A)) & PL_LINE_ST) अणु
		हाल PL_L_NLS :	ls = "NOISE" ;	अवरोध ;
		हाल PL_L_ALS :	ls = "ACTIV" ;	अवरोध ;
		हाल PL_L_UND :	ls = "UNDEF" ;	अवरोध ;
		हाल PL_L_ILS4:	ls = "ILS 4" ;	अवरोध ;
		हाल PL_L_QLS :	ls = "QLS" ;	अवरोध ;
		हाल PL_L_MLS :	ls = "MLS" ;	अवरोध ;
		हाल PL_L_HLS :	ls = "HLS" ;	अवरोध ;
		हाल PL_L_ILS16:ls = "ILS16" ;	अवरोध ;
#अगर_घोषित	lपूर्णांक
		शेष:	ls = "unknown" ; अवरोध ;
#पूर्ण_अगर
	पूर्ण
	वापस ls;
पूर्ण

अक्षर *get_pcmstate(काष्ठा s_smc *smc, पूर्णांक np)
अणु
	अक्षर *pcs ;
	
	SK_UNUSED(smc) ;

	चयन (inpw(PLC(np,PL_STATUS_B)) & PL_PCM_STATE) अणु
		हाल PL_PC0 :	pcs = "OFF" ;		अवरोध ;
		हाल PL_PC1 :	pcs = "BREAK" ;		अवरोध ;
		हाल PL_PC2 :	pcs = "TRACE" ;		अवरोध ;
		हाल PL_PC3 :	pcs = "CONNECT";	अवरोध ;
		हाल PL_PC4 :	pcs = "NEXT" ;		अवरोध ;
		हाल PL_PC5 :	pcs = "SIGNAL" ;	अवरोध ;
		हाल PL_PC6 :	pcs = "JOIN" ;		अवरोध ;
		हाल PL_PC7 :	pcs = "VERIFY" ;	अवरोध ;
		हाल PL_PC8 :	pcs = "ACTIV" ;		अवरोध ;
		हाल PL_PC9 :	pcs = "MAINT" ;		अवरोध ;
		शेष :	pcs = "UNKNOWN" ; 	अवरोध ;
	पूर्ण
	वापस pcs;
पूर्ण

व्योम list_phy(काष्ठा s_smc *smc)
अणु
	काष्ठा s_plc *plc ;
	पूर्णांक np ;

	क्रम (np = 0 ; np < NUMPHYS ; np++) अणु
		plc  = &smc->y[np].plc ;
		म_लिखो("PHY %d:\tERRORS\t\t\tBREAK_REASONS\t\tSTATES:\n",np) ;
		म_लिखो("\tsoft_error: %ld \t\tPC_Start : %ld\n",
						plc->soft_err,plc->b_pcs);
		म_लिखो("\tparity_err: %ld \t\tTPC exp. : %ld\t\tLine: %s\n",
			plc->parity_err,plc->b_tpc,get_linestate(smc,np)) ;
		म_लिखो("\tebuf_error: %ld \t\tTNE exp. : %ld\n",
						plc->ebuf_err,plc->b_tne) ;
		म_लिखो("\tphyinvalid: %ld \t\tQLS det. : %ld\t\tPCM : %s\n",
			plc->phyinv,plc->b_qls,get_pcmstate(smc,np)) ;
		म_लिखो("\tviosym_ctr: %ld \t\tILS det. : %ld\n",
						plc->vsym_ctr,plc->b_ils)  ;
		म_लिखो("\tmingap_ctr: %ld \t\tHLS det. : %ld\n",
						plc->mini_ctr,plc->b_hls) ;
		म_लिखो("\tnodepr_err: %ld\n",plc->np_err) ;
		म_लिखो("\tTPC_exp : %ld\n",plc->tpc_exp) ;
		म_लिखो("\tLEM_err : %ld\n",smc->y[np].lem.lem_errors) ;
	पूर्ण
पूर्ण


#अगर_घोषित	CONCENTRATOR
व्योम pcm_lem_dump(काष्ठा s_smc *smc)
अणु
	पूर्णांक		i ;
	काष्ठा s_phy	*phy ;
	काष्ठा fddi_mib_p	*mib ;

	अक्षर		*entostring() ;

	म_लिखो("PHY	errors	BER\n") ;
	म_लिखो("----------------------\n") ;
	क्रम (i = 0,phy = smc->y ; i < NUMPHYS ; i++,phy++) अणु
		अगर (!plc_is_installed(smc,i))
			जारी ;
		mib = phy->mib ;
		म_लिखो("%s\t%ld\t10E-%d\n",
			entostring(smc,ENTITY_PHY(i)),
			mib->fddiPORTLem_Ct,
			mib->fddiPORTLer_Estimate) ;
	पूर्ण
पूर्ण
#पूर्ण_अगर
#पूर्ण_अगर
