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
	SMT/CMT शेषs
*/

#समावेश "h/types.h"
#समावेश "h/fddi.h"
#समावेश "h/smc.h"

#अगर_अघोषित OEM_USER_DATA
#घोषणा OEM_USER_DATA	"SK-NET FDDI V2.0 Userdata"
#पूर्ण_अगर

/*
 * शेषs
 */
#घोषणा TTMS(x)	((u_दीर्घ)(x)*1000L)
#घोषणा TTS(x)	((u_दीर्घ)(x)*1000000L)
#घोषणा TTUS(x)	((u_दीर्घ)(x))

#घोषणा DEFAULT_TB_MIN		TTMS(5)
#घोषणा DEFAULT_TB_MAX		TTMS(50)
#घोषणा DEFAULT_C_MIN		TTUS(1600)
#घोषणा DEFAULT_T_OUT		TTMS(100+5)
#घोषणा DEFAULT_TL_MIN		TTUS(30)
#घोषणा DEFAULT_LC_SHORT	TTMS(50+5)
#घोषणा DEFAULT_LC_MEDIUM	TTMS(500+20)
#घोषणा DEFAULT_LC_LONG		TTS(5)+TTMS(50)
#घोषणा DEFAULT_LC_EXTENDED	TTS(50)+TTMS(50)
#घोषणा DEFAULT_T_NEXT_9	TTMS(200+10)
#घोषणा DEFAULT_NS_MAX		TTUS(1310)
#घोषणा DEFAULT_I_MAX		TTMS(25)
#घोषणा DEFAULT_IN_MAX		TTMS(40)
#घोषणा DEFAULT_TD_MIN		TTMS(5)
#घोषणा DEFAULT_T_NON_OP	TTS(1)
#घोषणा DEFAULT_T_STUCK		TTS(8)
#घोषणा DEFAULT_T_सूचीECT	TTMS(370)
#घोषणा DEFAULT_T_JAM		TTMS(370)
#घोषणा DEFAULT_T_ANNOUNCE	TTMS(2500)
#घोषणा DEFAULT_D_MAX		TTUS(1617)
#घोषणा DEFAULT_LEM_ALARM	(8)
#घोषणा DEFAULT_LEM_CUTOFF	(7)
#घोषणा DEFAULT_TEST_DONE	TTS(1)
#घोषणा DEFAULT_CHECK_POLL	TTS(1)
#घोषणा DEFAULT_POLL		TTMS(50)

/*
 * LCT errors threshold
 */
#घोषणा DEFAULT_LCT_SHORT	1
#घोषणा DEFAULT_LCT_MEDIUM	3
#घोषणा DEFAULT_LCT_LONG	5
#घोषणा DEFAULT_LCT_EXTEND	50

/* Forward declarations */
व्योम smt_reset_शेषs(काष्ठा s_smc *smc, पूर्णांक level);
अटल व्योम smt_init_mib(काष्ठा s_smc *smc, पूर्णांक level);
अटल पूर्णांक set_min_max(पूर्णांक maxflag, u_दीर्घ mib, u_दीर्घ limit, u_दीर्घ *oper);

#घोषणा MS2BCLK(x)	((x)*12500L)
#घोषणा US2BCLK(x)	((x)*1250L)

व्योम smt_reset_शेषs(काष्ठा s_smc *smc, पूर्णांक level)
अणु
	काष्ठा smt_config	*smt ;
	पूर्णांक			i ;
	u_दीर्घ			smt_boot_समय;


	smt_init_mib(smc,level) ;

	smc->os.smc_version = SMC_VERSION ;
	smt_boot_समय = smt_get_समय();
	क्रम( i = 0; i < NUMMACS; i++ )
		smc->sm.last_tok_समय[i] = smt_boot_समय ;
	smt = &smc->s ;
	smt->attach_s = 0 ;
	smt->build_ring_map = 1 ;
	smt->sas = SMT_DAS ;
	smt->numphys = NUMPHYS ;
	smt->pcm_tb_min = DEFAULT_TB_MIN ;
	smt->pcm_tb_max = DEFAULT_TB_MAX ;
	smt->pcm_c_min = DEFAULT_C_MIN ;
	smt->pcm_t_out = DEFAULT_T_OUT ;
	smt->pcm_tl_min = DEFAULT_TL_MIN ;
	smt->pcm_lc_लघु = DEFAULT_LC_SHORT ;
	smt->pcm_lc_medium = DEFAULT_LC_MEDIUM ;
	smt->pcm_lc_दीर्घ = DEFAULT_LC_LONG ;
	smt->pcm_lc_extended = DEFAULT_LC_EXTENDED ;
	smt->pcm_t_next_9 = DEFAULT_T_NEXT_9 ;
	smt->pcm_ns_max = DEFAULT_NS_MAX ;
	smt->ecm_i_max = DEFAULT_I_MAX ;
	smt->ecm_in_max = DEFAULT_IN_MAX ;
	smt->ecm_td_min = DEFAULT_TD_MIN ;
	smt->ecm_test_करोne = DEFAULT_TEST_DONE ;
	smt->ecm_check_poll = DEFAULT_CHECK_POLL ;
	smt->rmt_t_non_op = DEFAULT_T_NON_OP ;
	smt->rmt_t_stuck = DEFAULT_T_STUCK ;
	smt->rmt_t_direct = DEFAULT_T_सूचीECT ;
	smt->rmt_t_jam = DEFAULT_T_JAM ;
	smt->rmt_t_announce = DEFAULT_T_ANNOUNCE ;
	smt->rmt_t_poll = DEFAULT_POLL ;
        smt->rmt_dup_mac_behavior = FALSE ;  /* See Struct smt_config */
	smt->mac_d_max = DEFAULT_D_MAX ;

	smt->lct_लघु = DEFAULT_LCT_SHORT ;
	smt->lct_medium = DEFAULT_LCT_MEDIUM ;
	smt->lct_दीर्घ = DEFAULT_LCT_LONG ;
	smt->lct_extended = DEFAULT_LCT_EXTEND ;

#अगर_अघोषित	SLIM_SMT
#अगर_घोषित	ESS
	अगर (level == 0) अणु
		smc->ess.sync_bw_available = FALSE ;
		smc->mib.fddiESSPayload = 0 ;
		smc->mib.fddiESSOverhead = 0 ;
		smc->mib.fddiESSMaxTNeg = (u_दीर्घ)(- MS2BCLK(25)) ;
		smc->mib.fddiESSMinSegmentSize = 1 ;
		smc->mib.fddiESSCategory = SB_STATIC ;
		smc->mib.fddiESSSynchTxMode = FALSE ;
		smc->ess.raf_act_समयr_poll = FALSE ;
		smc->ess.समयr_count = 7 ; 	/* first RAF alc req after 3s */
	पूर्ण
	smc->ess.local_sba_active = FALSE ;
	smc->ess.sba_reply_pend = शून्य ;
#पूर्ण_अगर
#अगर_घोषित	SBA
	smt_init_sba(smc,level) ;
#पूर्ण_अगर
#पूर्ण_अगर	/* no SLIM_SMT */
#अगर_घोषित	TAG_MODE
	अगर (level == 0) अणु
		smc->hw.pci_fix_value = 0 ;
	पूर्ण
#पूर्ण_अगर
पूर्ण

/*
 * manufacturer data
 */
अटल स्थिर अक्षर man_data[32] =
/*	 01234567890123456789012345678901	*/
	"xxxSK-NET FDDI SMT 7.3 - V2.8.8" ;

अटल व्योम smt_init_mib(काष्ठा s_smc *smc, पूर्णांक level)
अणु
	काष्ठा fddi_mib		*mib ;
	काष्ठा fddi_mib_p	*pm ;
	पूर्णांक			port ;
	पूर्णांक			path ;

	mib = &smc->mib ;
	अगर (level == 0) अणु
		/*
		 * set EVERYTHING to ZERO
		 * EXCEPT hw and os
		 */
		स_रखो(((अक्षर *)smc)+
			माप(काष्ठा s_smt_os)+माप(काष्ठा s_smt_hw), 0,
			माप(काष्ठा s_smc) -
			माप(काष्ठा s_smt_os) - माप(काष्ठा s_smt_hw)) ;
	पूर्ण
	अन्यथा अणु
		mib->fddiSMTRemoteDisconnectFlag = 0 ;
		mib->fddiSMTPeerWrapFlag = 0 ;
	पूर्ण

	mib->fddiSMTOpVersionId = 2 ;
	mib->fddiSMTHiVersionId = 2 ;
	mib->fddiSMTLoVersionId = 2 ;
	स_नकल((अक्षर *) mib->fddiSMTManufacturerData,man_data,32) ;
	अगर (level == 0) अणु
		म_नकल(mib->fddiSMTUserData,OEM_USER_DATA) ;
	पूर्ण
	mib->fddiSMTMIBVersionId = 1 ;
	mib->fddiSMTMac_Ct = NUMMACS ;
	mib->fddiSMTConnectionPolicy = POLICY_MM | POLICY_AA | POLICY_BB ;

	/*
	 * fddiSMTNonMaster_Ct and fddiSMTMaster_Ct are set in smt_fixup_mib
	 * s.sas is not set yet (is set in init driver)
	 */
	mib->fddiSMTAvailablePaths = MIB_PATH_P | MIB_PATH_S ;

	mib->fddiSMTConfigCapabilities = 0 ;	/* no hold,no wrap_ab*/
	mib->fddiSMTTT_Notअगरy = 10 ;
	mib->fddiSMTStatRptPolicy = TRUE ;
	mib->fddiSMTTrace_MaxExpiration = SEC2MIB(7) ;
	mib->fddiSMTMACIndexes = INDEX_MAC ;
	mib->fddiSMTStationStatus = MIB_SMT_STASTA_SEPA ;	/* separated */

	mib->m[MAC0].fddiMACIndex = INDEX_MAC ;
	mib->m[MAC0].fddiMACFrameStatusFunctions = FSC_TYPE0 ;
	mib->m[MAC0].fddiMACRequestedPaths =
		MIB_P_PATH_LOCAL |
		MIB_P_PATH_SEC_ALTER |
		MIB_P_PATH_PRIM_ALTER ;
	mib->m[MAC0].fddiMACAvailablePaths = MIB_PATH_P ;
	mib->m[MAC0].fddiMACCurrentPath = MIB_PATH_PRIMARY ;
	mib->m[MAC0].fddiMACT_MaxCapabilitiy = (u_दीर्घ)(- MS2BCLK(165)) ;
	mib->m[MAC0].fddiMACTVXCapabilitiy = (u_दीर्घ)(- US2BCLK(52)) ;
	अगर (level == 0) अणु
		mib->m[MAC0].fddiMACTvxValue = (u_दीर्घ)(- US2BCLK(27)) ;
		mib->m[MAC0].fddiMACTvxValueMIB = (u_दीर्घ)(- US2BCLK(27)) ;
		mib->m[MAC0].fddiMACT_Req = (u_दीर्घ)(- MS2BCLK(165)) ;
		mib->m[MAC0].fddiMACT_ReqMIB = (u_दीर्घ)(- MS2BCLK(165)) ;
		mib->m[MAC0].fddiMACT_Max = (u_दीर्घ)(- MS2BCLK(165)) ;
		mib->m[MAC0].fddiMACT_MaxMIB = (u_दीर्घ)(- MS2BCLK(165)) ;
		mib->m[MAC0].fddiMACT_Min = (u_दीर्घ)(- MS2BCLK(4)) ;
	पूर्ण
	mib->m[MAC0].fddiMACHardwarePresent = TRUE ;
	mib->m[MAC0].fddiMACMA_UnitdataEnable = TRUE ;
	mib->m[MAC0].fddiMACFrameErrorThreshold = 1 ;
	mib->m[MAC0].fddiMACNotCopiedThreshold = 1 ;
	/*
	 * Path attributes
	 */
	क्रम (path = 0 ; path < NUMPATHS ; path++) अणु
		mib->a[path].fddiPATHIndex = INDEX_PATH + path ;
		अगर (level == 0) अणु
			mib->a[path].fddiPATHTVXLowerBound =
				(u_दीर्घ)(- US2BCLK(27)) ;
			mib->a[path].fddiPATHT_MaxLowerBound =
				(u_दीर्घ)(- MS2BCLK(165)) ;
			mib->a[path].fddiPATHMaxT_Req =
				(u_दीर्घ)(- MS2BCLK(165)) ;
		पूर्ण
	पूर्ण


	/*
	 * Port attributes
	 */
	pm = mib->p ;
	क्रम (port = 0 ; port <  NUMPHYS ; port++) अणु
		/*
		 * set MIB poपूर्णांकer in phy
		 */
		/* Attention: करोn't initialize mib poपूर्णांकer here! */
		/*  It must be initialized during phase 2 */
		smc->y[port].mib = शून्य;
		mib->fddiSMTPORTIndexes[port] = port+INDEX_PORT ;

		pm->fddiPORTIndex = port+INDEX_PORT ;
		pm->fddiPORTHardwarePresent = TRUE ;
		अगर (level == 0) अणु
			pm->fddiPORTLer_Alarm = DEFAULT_LEM_ALARM ;
			pm->fddiPORTLer_Cutoff = DEFAULT_LEM_CUTOFF ;
		पूर्ण
		/*
		 * fddiPORTRequestedPaths are set in pcmplc.c
		 * we करोn't know the port type yet !
		 */
		pm->fddiPORTRequestedPaths[1] = 0 ;
		pm->fddiPORTRequestedPaths[2] = 0 ;
		pm->fddiPORTRequestedPaths[3] = 0 ;
		pm->fddiPORTAvailablePaths = MIB_PATH_P ;
		pm->fddiPORTPMDClass = MIB_PMDCLASS_MULTI ;
		pm++ ;
	पूर्ण

	(व्योम) smt_set_mac_opvalues(smc) ;
पूर्ण

पूर्णांक smt_set_mac_opvalues(काष्ठा s_smc *smc)
अणु
	पूर्णांक	st ;
	पूर्णांक	st2 ;

	st = set_min_max(1,smc->mib.m[MAC0].fddiMACTvxValueMIB,
		smc->mib.a[PATH0].fddiPATHTVXLowerBound,
		&smc->mib.m[MAC0].fddiMACTvxValue) ;
	st |= set_min_max(0,smc->mib.m[MAC0].fddiMACT_MaxMIB,
		smc->mib.a[PATH0].fddiPATHT_MaxLowerBound,
		&smc->mib.m[MAC0].fddiMACT_Max) ;
	st |= (st2 = set_min_max(0,smc->mib.m[MAC0].fddiMACT_ReqMIB,
		smc->mib.a[PATH0].fddiPATHMaxT_Req,
		&smc->mib.m[MAC0].fddiMACT_Req)) ;
	अगर (st2) अणु
		/* Treq attribute changed remotely. So send an AIX_EVENT to the
		 * user
		 */
		AIX_EVENT(smc, (u_दीर्घ) FDDI_RING_STATUS, (u_दीर्घ)
			FDDI_SMT_EVENT, (u_दीर्घ) FDDI_REMOTE_T_REQ,
			smt_get_event_word(smc));
	पूर्ण
	वापस st;
पूर्ण

व्योम smt_fixup_mib(काष्ठा s_smc *smc)
अणु
#अगर_घोषित	CONCENTRATOR
	चयन (smc->s.sas) अणु
	हाल SMT_SAS :
		smc->mib.fddiSMTNonMaster_Ct = 1 ;
		अवरोध ;
	हाल SMT_DAS :
		smc->mib.fddiSMTNonMaster_Ct = 2 ;
		अवरोध ;
	हाल SMT_NAC :
		smc->mib.fddiSMTNonMaster_Ct = 0 ;
		अवरोध ;
	पूर्ण
	smc->mib.fddiSMTMaster_Ct = NUMPHYS - smc->mib.fddiSMTNonMaster_Ct ;
#अन्यथा
	चयन (smc->s.sas) अणु
	हाल SMT_SAS :
		smc->mib.fddiSMTNonMaster_Ct = 1 ;
		अवरोध ;
	हाल SMT_DAS :
		smc->mib.fddiSMTNonMaster_Ct = 2 ;
		अवरोध ;
	पूर्ण
	smc->mib.fddiSMTMaster_Ct = 0 ;
#पूर्ण_अगर
पूर्ण

/*
 * determine new setting क्रम operational value
 * अगर limit is lower than mib
 *	use limit
 * अन्यथा
 *	use mib
 * NOTE : numbers are negative, negate comparison !
 */
अटल पूर्णांक set_min_max(पूर्णांक maxflag, u_दीर्घ mib, u_दीर्घ limit, u_दीर्घ *oper)
अणु
	u_दीर्घ	old ;
	old = *oper ;
	अगर ((limit > mib) ^ maxflag)
		*oper = limit ;
	अन्यथा
		*oper = mib ;
	वापस old != *oper;
पूर्ण

