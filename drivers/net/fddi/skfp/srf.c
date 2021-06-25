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
	SMT 7.2 Status Response Frame Implementation
	SRF state machine and frame generation
*/

#समावेश "h/types.h"
#समावेश "h/fddi.h"
#समावेश "h/smc.h"
#समावेश "h/smt_p.h"

#घोषणा KERNEL
#समावेश "h/smtstate.h"

#अगर_अघोषित	SLIM_SMT
#अगर_अघोषित	BOOT

/*
 * function declarations
 */
अटल व्योम clear_all_rep(काष्ठा s_smc *smc);
अटल व्योम clear_reported(काष्ठा s_smc *smc);
अटल व्योम smt_send_srf(काष्ठा s_smc *smc);
अटल काष्ठा s_srf_evc *smt_get_evc(काष्ठा s_smc *smc, पूर्णांक code, पूर्णांक index);

#घोषणा MAX_EVCS	ARRAY_SIZE(smc->evcs)

काष्ठा evc_init अणु
	u_अक्षर code ;
	u_अक्षर index ;
	u_अक्षर n ;
	u_लघु	para ;
पूर्ण  ;

अटल स्थिर काष्ठा evc_init evc_inits[] = अणु
	अणु SMT_COND_SMT_PEER_WRAP,		0,1,SMT_P1048	पूर्ण ,

	अणु SMT_COND_MAC_DUP_ADDR,		INDEX_MAC, NUMMACS,SMT_P208C पूर्ण ,
	अणु SMT_COND_MAC_FRAME_ERROR,		INDEX_MAC, NUMMACS,SMT_P208D पूर्ण ,
	अणु SMT_COND_MAC_NOT_COPIED,		INDEX_MAC, NUMMACS,SMT_P208E पूर्ण ,
	अणु SMT_EVENT_MAC_NEIGHBOR_CHANGE,	INDEX_MAC, NUMMACS,SMT_P208F पूर्ण ,
	अणु SMT_EVENT_MAC_PATH_CHANGE,		INDEX_MAC, NUMMACS,SMT_P2090 पूर्ण ,

	अणु SMT_COND_PORT_LER,			INDEX_PORT,NUMPHYS,SMT_P4050 पूर्ण ,
	अणु SMT_COND_PORT_EB_ERROR,		INDEX_PORT,NUMPHYS,SMT_P4052 पूर्ण ,
	अणु SMT_EVENT_PORT_CONNECTION,		INDEX_PORT,NUMPHYS,SMT_P4051 पूर्ण ,
	अणु SMT_EVENT_PORT_PATH_CHANGE,		INDEX_PORT,NUMPHYS,SMT_P4053 पूर्ण ,
पूर्ण ;

#घोषणा MAX_INIT_EVC	ARRAY_SIZE(evc_inits)

व्योम smt_init_evc(काष्ठा s_smc *smc)
अणु
	काष्ठा s_srf_evc	*evc ;
	स्थिर काष्ठा evc_init 	*init ;
	अचिन्हित पूर्णांक		i ;
	पूर्णांक			index ;
	पूर्णांक			offset ;

	अटल u_अक्षर		fail_safe = FALSE ;

	स_रखो((अक्षर *)smc->evcs,0,माप(smc->evcs)) ;

	evc = smc->evcs ;
	init = evc_inits ;

	क्रम (i = 0 ; i < MAX_INIT_EVC ; i++) अणु
		क्रम (index = 0 ; index < init->n ; index++) अणु
			evc->evc_code = init->code ;
			evc->evc_para = init->para ;
			evc->evc_index = init->index + index ;
#अगर_अघोषित	DEBUG
			evc->evc_multiple = &fail_safe ;
			evc->evc_cond_state = &fail_safe ;
#पूर्ण_अगर
			evc++ ;
		पूर्ण
		init++ ;
	पूर्ण

	अगर ((अचिन्हित पूर्णांक) (evc - smc->evcs) > MAX_EVCS) अणु
		SMT_PANIC(smc,SMT_E0127, SMT_E0127_MSG) ;
	पूर्ण

	/*
	 * conditions
	 */
	smc->evcs[0].evc_cond_state = &smc->mib.fddiSMTPeerWrapFlag ;
	smc->evcs[1].evc_cond_state =
		&smc->mib.m[MAC0].fddiMACDuplicateAddressCond ;
	smc->evcs[2].evc_cond_state =
		&smc->mib.m[MAC0].fddiMACFrameErrorFlag ;
	smc->evcs[3].evc_cond_state =
		&smc->mib.m[MAC0].fddiMACNotCopiedFlag ;

	/*
	 * events
	 */
	smc->evcs[4].evc_multiple = &smc->mib.m[MAC0].fddiMACMultiple_N ;
	smc->evcs[5].evc_multiple = &smc->mib.m[MAC0].fddiMACMultiple_P ;

	offset = 6 ;
	क्रम (i = 0 ; i < NUMPHYS ; i++) अणु
		/*
		 * conditions
		 */
		smc->evcs[offset + 0*NUMPHYS].evc_cond_state =
			&smc->mib.p[i].fddiPORTLerFlag ;
		smc->evcs[offset + 1*NUMPHYS].evc_cond_state =
			&smc->mib.p[i].fddiPORTEB_Condition ;

		/*
		 * events
		 */
		smc->evcs[offset + 2*NUMPHYS].evc_multiple =
			&smc->mib.p[i].fddiPORTMultiple_U ;
		smc->evcs[offset + 3*NUMPHYS].evc_multiple =
			&smc->mib.p[i].fddiPORTMultiple_P ;
		offset++ ;
	पूर्ण
#अगर_घोषित	DEBUG
	क्रम (i = 0, evc = smc->evcs ; i < MAX_EVCS ; i++, evc++) अणु
		अगर (SMT_IS_CONDITION(evc->evc_code)) अणु
			अगर (!evc->evc_cond_state) अणु
				SMT_PANIC(smc,SMT_E0128, SMT_E0128_MSG) ;
			पूर्ण
			evc->evc_multiple = &fail_safe ;
		पूर्ण
		अन्यथा अणु
			अगर (!evc->evc_multiple) अणु
				SMT_PANIC(smc,SMT_E0129, SMT_E0129_MSG) ;
			पूर्ण
			evc->evc_cond_state = &fail_safe ;
		पूर्ण
	पूर्ण
#पूर्ण_अगर
	smc->srf.TSR = smt_get_समय() ;
	smc->srf.sr_state = SR0_WAIT ;
पूर्ण

अटल काष्ठा s_srf_evc *smt_get_evc(काष्ठा s_smc *smc, पूर्णांक code, पूर्णांक index)
अणु
	अचिन्हित पूर्णांक		i ;
	काष्ठा s_srf_evc	*evc ;

	क्रम (i = 0, evc = smc->evcs ; i < MAX_EVCS ; i++, evc++) अणु
		अगर (evc->evc_code == code && evc->evc_index == index)
			वापस evc;
	पूर्ण
	वापस शून्य;
पूर्ण

#घोषणा THRESHOLD_2	(2*TICKS_PER_SECOND)
#घोषणा THRESHOLD_32	(32*TICKS_PER_SECOND)

अटल स्थिर अक्षर * स्थिर srf_names[] = अणु
	"None","MACPathChangeEvent",	"MACNeighborChangeEvent",
	"PORTPathChangeEvent",		"PORTUndesiredConnectionAttemptEvent",
	"SMTPeerWrapCondition",		"SMTHoldCondition",
	"MACFrameErrorCondition",	"MACDuplicateAddressCondition",
	"MACNotCopiedCondition",	"PORTEBErrorCondition",
	"PORTLerCondition"
पूर्ण ;

व्योम smt_srf_event(काष्ठा s_smc *smc, पूर्णांक code, पूर्णांक index, पूर्णांक cond)
अणु
	काष्ठा s_srf_evc	*evc ;
	पूर्णांक			cond_निश्चितed = 0 ;
	पूर्णांक			cond_deनिश्चितed = 0 ;
	पूर्णांक			event_occurred = 0 ;
	पूर्णांक			tsr ;
	पूर्णांक			T_Limit = 2*TICKS_PER_SECOND ;

	अगर (code == SMT_COND_MAC_DUP_ADDR && cond) अणु
		RS_SET(smc,RS_DUPADDR) ;
	पूर्ण

	अगर (code) अणु
		DB_SMT("SRF: %s index %d", srf_names[code], index);

		अगर (!(evc = smt_get_evc(smc,code,index))) अणु
			DB_SMT("SRF : smt_get_evc() failed");
			वापस ;
		पूर्ण
		/*
		 * ignore condition अगर no change
		 */
		अगर (SMT_IS_CONDITION(code)) अणु
			अगर (*evc->evc_cond_state == cond)
				वापस ;
		पूर्ण

		/*
		 * set transition समय stamp
		 */
		smt_set_बारtamp(smc,smc->mib.fddiSMTTransitionTimeStamp) ;
		अगर (SMT_IS_CONDITION(code)) अणु
			DB_SMT("SRF: condition is %s", cond ? "ON" : "OFF");
			अगर (cond) अणु
				*evc->evc_cond_state = TRUE ;
				evc->evc_rep_required = TRUE ;
				smc->srf.any_report = TRUE ;
				cond_निश्चितed = TRUE ;
			पूर्ण
			अन्यथा अणु
				*evc->evc_cond_state = FALSE ;
				cond_deनिश्चितed = TRUE ;
			पूर्ण
		पूर्ण
		अन्यथा अणु
			अगर (evc->evc_rep_required) अणु
				*evc->evc_multiple  = TRUE ;
			पूर्ण
			अन्यथा अणु
				evc->evc_rep_required = TRUE ;
				*evc->evc_multiple  = FALSE ;
			पूर्ण
			smc->srf.any_report = TRUE ;
			event_occurred = TRUE ;
		पूर्ण
#अगर_घोषित	FDDI_MIB
		snmp_srf_event(smc,evc) ;
#पूर्ण_अगर	/* FDDI_MIB */
	पूर्ण
	tsr = smt_get_समय() - smc->srf.TSR ;

	चयन (smc->srf.sr_state) अणु
	हाल SR0_WAIT :
		/* SR01a */
		अगर (cond_निश्चितed && tsr < T_Limit) अणु
			smc->srf.SRThreshold = THRESHOLD_2 ;
			smc->srf.sr_state = SR1_HOLDOFF ;
			अवरोध ;
		पूर्ण
		/* SR01b */
		अगर (cond_deनिश्चितed && tsr < T_Limit) अणु
			smc->srf.sr_state = SR1_HOLDOFF ;
			अवरोध ;
		पूर्ण
		/* SR01c */
		अगर (event_occurred && tsr < T_Limit) अणु
			smc->srf.sr_state = SR1_HOLDOFF ;
			अवरोध ;
		पूर्ण
		/* SR00b */
		अगर (cond_निश्चितed && tsr >= T_Limit) अणु
			smc->srf.SRThreshold = THRESHOLD_2 ;
			smc->srf.TSR = smt_get_समय() ;
			smt_send_srf(smc) ;
			अवरोध ;
		पूर्ण
		/* SR00c */
		अगर (cond_deनिश्चितed && tsr >= T_Limit) अणु
			smc->srf.TSR = smt_get_समय() ;
			smt_send_srf(smc) ;
			अवरोध ;
		पूर्ण
		/* SR00d */
		अगर (event_occurred && tsr >= T_Limit) अणु
			smc->srf.TSR = smt_get_समय() ;
			smt_send_srf(smc) ;
			अवरोध ;
		पूर्ण
		/* SR00e */
		अगर (smc->srf.any_report && (u_दीर्घ) tsr >=
			smc->srf.SRThreshold) अणु
			smc->srf.SRThreshold *= 2 ;
			अगर (smc->srf.SRThreshold > THRESHOLD_32)
				smc->srf.SRThreshold = THRESHOLD_32 ;
			smc->srf.TSR = smt_get_समय() ;
			smt_send_srf(smc) ;
			अवरोध ;
		पूर्ण
		/* SR02 */
		अगर (!smc->mib.fddiSMTStatRptPolicy) अणु
			smc->srf.sr_state = SR2_DISABLED ;
			अवरोध ;
		पूर्ण
		अवरोध ;
	हाल SR1_HOLDOFF :
		/* SR10b */
		अगर (tsr >= T_Limit) अणु
			smc->srf.sr_state = SR0_WAIT ;
			smc->srf.TSR = smt_get_समय() ;
			smt_send_srf(smc) ;
			अवरोध ;
		पूर्ण
		/* SR11a */
		अगर (cond_निश्चितed) अणु
			smc->srf.SRThreshold = THRESHOLD_2 ;
		पूर्ण
		/* SR11b */
		/* SR11c */
		/* handled above */
		/* SR12 */
		अगर (!smc->mib.fddiSMTStatRptPolicy) अणु
			smc->srf.sr_state = SR2_DISABLED ;
			अवरोध ;
		पूर्ण
		अवरोध ;
	हाल SR2_DISABLED :
		अगर (smc->mib.fddiSMTStatRptPolicy) अणु
			smc->srf.sr_state = SR0_WAIT ;
			smc->srf.TSR = smt_get_समय() ;
			smc->srf.SRThreshold = THRESHOLD_2 ;
			clear_all_rep(smc) ;
			अवरोध ;
		पूर्ण
		अवरोध ;
	पूर्ण
पूर्ण

अटल व्योम clear_all_rep(काष्ठा s_smc *smc)
अणु
	काष्ठा s_srf_evc	*evc ;
	अचिन्हित पूर्णांक		i ;

	क्रम (i = 0, evc = smc->evcs ; i < MAX_EVCS ; i++, evc++) अणु
		evc->evc_rep_required = FALSE ;
		अगर (SMT_IS_CONDITION(evc->evc_code))
			*evc->evc_cond_state = FALSE ;
	पूर्ण
	smc->srf.any_report = FALSE ;
पूर्ण

अटल व्योम clear_reported(काष्ठा s_smc *smc)
अणु
	काष्ठा s_srf_evc	*evc ;
	अचिन्हित पूर्णांक		i ;

	smc->srf.any_report = FALSE ;
	क्रम (i = 0, evc = smc->evcs ; i < MAX_EVCS ; i++, evc++) अणु
		अगर (SMT_IS_CONDITION(evc->evc_code)) अणु
			अगर (*evc->evc_cond_state == FALSE)
				evc->evc_rep_required = FALSE ;
			अन्यथा
				smc->srf.any_report = TRUE ;
		पूर्ण
		अन्यथा अणु
			evc->evc_rep_required = FALSE ;
			*evc->evc_multiple = FALSE ;
		पूर्ण
	पूर्ण
पूर्ण

/*
 * build and send SMT SRF frame
 */
अटल व्योम smt_send_srf(काष्ठा s_smc *smc)
अणु

	काष्ठा smt_header	*smt ;
	काष्ठा s_srf_evc	*evc ;
	SK_LOC_DECL(काष्ठा s_pcon,pcon) ;
	SMbuf			*mb ;
	अचिन्हित पूर्णांक		i ;

	अटल स्थिर काष्ठा fddi_addr SMT_SRF_DA = अणु
		अणु 0x80, 0x01, 0x43, 0x00, 0x80, 0x08 पूर्ण
	पूर्ण ;

	/*
	 * build SMT header
	 */
	अगर (!smc->r.sm_ma_avail)
		वापस ;
	अगर (!(mb = smt_build_frame(smc,SMT_SRF,SMT_ANNOUNCE,0)))
		वापस ;

	RS_SET(smc,RS_SOFTERROR) ;

	smt = smtod(mb, काष्ठा smt_header *) ;
	smt->smt_dest = SMT_SRF_DA ;		/* DA == SRF multicast */

	/*
	 * setup parameter status
	 */
	pcon.pc_len = SMT_MAX_INFO_LEN ;	/* max para length */
	pcon.pc_err = 0 ;			/* no error */
	pcon.pc_badset = 0 ;			/* no bad set count */
	pcon.pc_p = (व्योम *) (smt + 1) ;	/* paras start here */

	smt_add_para(smc,&pcon,(u_लघु) SMT_P1033,0,0) ;
	smt_add_para(smc,&pcon,(u_लघु) SMT_P1034,0,0) ;

	क्रम (i = 0, evc = smc->evcs ; i < MAX_EVCS ; i++, evc++) अणु
		अगर (evc->evc_rep_required) अणु
			smt_add_para(smc,&pcon,evc->evc_para,
				(पूर्णांक)evc->evc_index,0) ;
		पूर्ण
	पूर्ण
	smt->smt_len = SMT_MAX_INFO_LEN - pcon.pc_len ;
	mb->sm_len = smt->smt_len + माप(काष्ठा smt_header) ;

	DB_SMT("SRF: sending SRF at %p, len %d", smt, mb->sm_len);
	DB_SMT("SRF: state SR%d Threshold %lu",
	       smc->srf.sr_state, smc->srf.SRThreshold / TICKS_PER_SECOND);
#अगर_घोषित	DEBUG
	dump_smt(smc,smt,"SRF Send") ;
#पूर्ण_अगर
	smt_send_frame(smc,mb,FC_SMT_INFO,0) ;
	clear_reported(smc) ;
पूर्ण

#पूर्ण_अगर	/* no BOOT */
#पूर्ण_अगर	/* no SLIM_SMT */

