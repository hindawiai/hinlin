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

/*
 * FDDI MIB
 */

/*
 * प्रकारs
 */

प्रकार	u_दीर्घ	Counter ;
प्रकार u_अक्षर	TimeStamp[8] ;
प्रकार काष्ठा fddi_addr LongAddr ;
प्रकार	u_दीर्घ	Timer_2 ;
प्रकार	u_दीर्घ	Timer ;
प्रकार	u_लघु	ResId ;
प्रकार u_लघु	SMTEnum ;
प्रकार	u_अक्षर	SMTFlag ;

प्रकार काष्ठा अणु
	Counter		count ;
	TimeStamp	बारtamp ;
पूर्ण SetCountType ;

/*
 * bits क्रम bit string "available_path"
 */
#घोषणा MIB_PATH_P	(1<<0)
#घोषणा MIB_PATH_S	(1<<1)
#घोषणा MIB_PATH_L	(1<<2)

/*
 * bits क्रम bit string PermittedPaths & RequestedPaths (SIZE(8))
 */
#घोषणा MIB_P_PATH_LOCAL	(1<<0)
#घोषणा MIB_P_PATH_SEC_ALTER	(1<<1)
#घोषणा MIB_P_PATH_PRIM_ALTER	(1<<2)
#घोषणा MIB_P_PATH_CON_ALTER	(1<<3)
#घोषणा MIB_P_PATH_SEC_PREFER	(1<<4)
#घोषणा MIB_P_PATH_PRIM_PREFER	(1<<5)
#घोषणा MIB_P_PATH_CON_PREFER	(1<<6)
#घोषणा MIB_P_PATH_THRU		(1<<7)

/*
 * क्रमागत current path
 */
#घोषणा MIB_PATH_ISOLATED	0
#घोषणा MIB_PATH_LOCAL		1
#घोषणा MIB_PATH_SECONDARY	2
#घोषणा MIB_PATH_PRIMARY	3
#घोषणा MIB_PATH_CONCATENATED	4
#घोषणा MIB_PATH_THRU		5

/*
 * क्रमागत PMDClass
 */
#घोषणा MIB_PMDCLASS_MULTI	0
#घोषणा MIB_PMDCLASS_SINGLE1	1
#घोषणा MIB_PMDCLASS_SINGLE2	2
#घोषणा MIB_PMDCLASS_SONET	3
#घोषणा MIB_PMDCLASS_LCF	4
#घोषणा MIB_PMDCLASS_TP		5
#घोषणा MIB_PMDCLASS_UNKNOWN	6
#घोषणा MIB_PMDCLASS_UNSPEC	7

/*
 * क्रमागत SMTStationStatus
 */
#घोषणा MIB_SMT_STASTA_CON	0
#घोषणा MIB_SMT_STASTA_SEPA	1
#घोषणा MIB_SMT_STASTA_THRU	2


काष्ठा fddi_mib अणु
	/*
	 * निजी
	 */
	u_अक्षर			fddiPRPMFPasswd[8] ;
	काष्ठा smt_sid		fddiPRPMFStation ;

#अगर_घोषित	ESS
	/*
	 * निजी variables क्रम अटल allocation of the
	 * End Station Support
	 */
	u_दीर्घ	fddiESSPayload ;	/* payload क्रम अटल alloc */
	u_दीर्घ	fddiESSOverhead ;	/* frame ov क्रम अटल alloc */
	u_दीर्घ	fddiESSMaxTNeg ;	/* maximum of T-NEG */
	u_दीर्घ	fddiESSMinSegmentSize ;	/* min size of the sync frames */
	u_दीर्घ	fddiESSCategory ;	/* category क्रम the Alloc req */
	लघु	fddiESSSynchTxMode ;	/* send all LLC frames as sync */
#पूर्ण_अगर	/* ESS */
#अगर_घोषित	SBA
	/*
	 * निजी variables क्रम the Synchronous Bandwidth Allocator
	 */
	अक्षर	fddiSBACommand ;	/* holds the parsed SBA cmd */
	u_अक्षर	fddiSBAAvailable ;	/* SBA allocatable value */
#पूर्ण_अगर	/* SBA */

	/*
	 * SMT standard mib
	 */
	काष्ठा smt_sid		fddiSMTStationId ;
	u_लघु			fddiSMTOpVersionId ;
	u_लघु			fddiSMTHiVersionId ;
	u_लघु			fddiSMTLoVersionId ;
	u_अक्षर			fddiSMTManufacturerData[32] ;
	u_अक्षर			fddiSMTUserData[32] ;
	u_लघु			fddiSMTMIBVersionId ;

	/*
	 * ConfigGrp
	 */
	u_अक्षर			fddiSMTMac_Ct ;
	u_अक्षर			fddiSMTNonMaster_Ct ;
	u_अक्षर			fddiSMTMaster_Ct ;
	u_अक्षर			fddiSMTAvailablePaths ;
	u_लघु			fddiSMTConfigCapabilities ;
	u_लघु			fddiSMTConfigPolicy ;
	u_लघु			fddiSMTConnectionPolicy ;
	u_लघु			fddiSMTTT_Notअगरy ;
	u_अक्षर			fddiSMTStatRptPolicy ;
	u_दीर्घ			fddiSMTTrace_MaxExpiration ;
	u_लघु			fddiSMTPORTIndexes[NUMPHYS] ;
	u_लघु			fddiSMTMACIndexes ;
	u_अक्षर			fddiSMTBypassPresent ;

	/*
	 * StatusGrp
	 */
	SMTEnum			fddiSMTECMState ;
	SMTEnum			fddiSMTCF_State ;
	SMTEnum			fddiSMTStationStatus ;
	u_अक्षर			fddiSMTRemoteDisconnectFlag ;
	u_अक्षर			fddiSMTPeerWrapFlag ;

	/*
	 * MIBOperationGrp
	 */
	TimeStamp		fddiSMTTimeStamp ;
	TimeStamp		fddiSMTTransitionTimeStamp ;
	SetCountType		fddiSMTSetCount ;
	काष्ठा smt_sid		fddiSMTLastSetStationId ;

	काष्ठा fddi_mib_m अणु
		u_लघु		fddiMACFrameStatusFunctions ;
		Timer_2		fddiMACT_MaxCapabilitiy ;
		Timer_2		fddiMACTVXCapabilitiy ;

		/* ConfigGrp */
		u_अक्षर		fddiMACMultiple_N ;	/* निजी */
		u_अक्षर		fddiMACMultiple_P ;	/* निजी */
		u_अक्षर		fddiMACDuplicateAddressCond ;/* निजी */
		u_अक्षर		fddiMACAvailablePaths ;
		u_लघु		fddiMACCurrentPath ;
		LongAddr	fddiMACUpstreamNbr ;
		LongAddr	fddiMACDownstreamNbr ;
		LongAddr	fddiMACOldUpstreamNbr ;
		LongAddr	fddiMACOldDownstreamNbr ;
		SMTEnum		fddiMACDupAddressTest ;
		u_लघु		fddiMACRequestedPaths ;
		SMTEnum		fddiMACDownstreamPORTType ;
		ResId		fddiMACIndex ;

		/* AddressGrp */
		LongAddr	fddiMACSMTAddress ;

		/* OperationGrp */
		Timer_2		fddiMACT_Min ;	/* निजी */
		Timer_2		fddiMACT_ReqMIB ;
		Timer_2		fddiMACT_Req ;	/* निजी */
		Timer_2		fddiMACT_Neg ;
		Timer_2		fddiMACT_MaxMIB ;
		Timer_2		fddiMACT_Max ;	/* निजी */
		Timer_2		fddiMACTvxValueMIB ;
		Timer_2		fddiMACTvxValue ; /* निजी */
		Timer_2		fddiMACT_Pri0 ;
		Timer_2		fddiMACT_Pri1 ;
		Timer_2		fddiMACT_Pri2 ;
		Timer_2		fddiMACT_Pri3 ;
		Timer_2		fddiMACT_Pri4 ;
		Timer_2		fddiMACT_Pri5 ;
		Timer_2		fddiMACT_Pri6 ;

		/* CountersGrp */
		Counter		fddiMACFrame_Ct ;
		Counter		fddiMACCopied_Ct ;
		Counter		fddiMACTransmit_Ct ;
		Counter		fddiMACToken_Ct ;
		Counter		fddiMACError_Ct ;
		Counter		fddiMACLost_Ct ;
		Counter		fddiMACTvxExpired_Ct ;
		Counter		fddiMACNotCopied_Ct ;
		Counter		fddiMACRingOp_Ct ;

		Counter		fddiMACSMTCopied_Ct ;		/* निजी */
		Counter		fddiMACSMTTransmit_Ct ;		/* निजी */

		/* निजी क्रम delta ratio */
		Counter		fddiMACOld_Frame_Ct ;
		Counter		fddiMACOld_Copied_Ct ;
		Counter		fddiMACOld_Error_Ct ;
		Counter		fddiMACOld_Lost_Ct ;
		Counter		fddiMACOld_NotCopied_Ct ;

		/* FrameErrorConditionGrp */
		u_लघु		fddiMACFrameErrorThreshold ;
		u_लघु		fddiMACFrameErrorRatio ;

		/* NotCopiedConditionGrp */
		u_लघु		fddiMACNotCopiedThreshold ;
		u_लघु		fddiMACNotCopiedRatio ;

		/* StatusGrp */
		SMTEnum		fddiMACRMTState ;
		SMTFlag		fddiMACDA_Flag ;
		SMTFlag		fddiMACUNDA_Flag ;
		SMTFlag		fddiMACFrameErrorFlag ;
		SMTFlag		fddiMACNotCopiedFlag ;
		SMTFlag		fddiMACMA_UnitdataAvailable ;
		SMTFlag		fddiMACHardwarePresent ;
		SMTFlag		fddiMACMA_UnitdataEnable ;

	पूर्ण m[NUMMACS] ;
#घोषणा MAC0	0

	काष्ठा fddi_mib_a अणु
		ResId		fddiPATHIndex ;
		u_दीर्घ		fddiPATHSbaPayload ;
		u_दीर्घ		fddiPATHSbaOverhead ;
		/* fddiPATHConfiguration is built on demand */
		/* u_दीर्घ		fddiPATHConfiguration ; */
		Timer		fddiPATHT_Rmode ;
		u_दीर्घ		fddiPATHSbaAvailable ;
		Timer_2		fddiPATHTVXLowerBound ;
		Timer_2		fddiPATHT_MaxLowerBound ;
		Timer_2		fddiPATHMaxT_Req ;
	पूर्ण a[NUMPATHS] ;
#घोषणा PATH0	0

	काष्ठा fddi_mib_p अणु
		/* ConfigGrp */
		SMTEnum		fddiPORTMy_Type ;
		SMTEnum		fddiPORTNeighborType ;
		u_अक्षर		fddiPORTConnectionPolicies ;
		काष्ठा अणु
			u_अक्षर	T_val ;
			u_अक्षर	R_val ;
		पूर्ण fddiPORTMacIndicated ;
		SMTEnum		fddiPORTCurrentPath ;
		/* must be 4: is 32 bit in SMT क्रमmat
		 * indices :
		 *	1	none
		 *	2	tree
		 *	3	peer
		 */
		u_अक्षर		fddiPORTRequestedPaths[4] ;
		u_लघु		fddiPORTMACPlacement ;
		u_अक्षर		fddiPORTAvailablePaths ;
		u_अक्षर		fddiPORTConnectionCapabilities ;
		SMTEnum		fddiPORTPMDClass ;
		ResId		fddiPORTIndex ;

		/* OperationGrp */
		SMTEnum		fddiPORTMaपूर्णांक_LS ;
		SMTEnum		fddiPORTPC_LS ;
		u_अक्षर		fddiPORTBS_Flag ;

		/* ErrorCtrsGrp */
		Counter		fddiPORTLCTFail_Ct ;
		Counter		fddiPORTEBError_Ct ;
		Counter		fddiPORTOldEBError_Ct ;

		/* LerGrp */
		Counter		fddiPORTLem_Reject_Ct ;
		Counter		fddiPORTLem_Ct ;
		u_अक्षर		fddiPORTLer_Estimate ;
		u_अक्षर		fddiPORTLer_Cutoff ;
		u_अक्षर		fddiPORTLer_Alarm ;

		/* StatusGrp */
		SMTEnum		fddiPORTConnectState ;
		SMTEnum		fddiPORTPCMState ;	/* real value */
		SMTEnum		fddiPORTPCMStateX ;	/* value क्रम MIB */
		SMTEnum		fddiPORTPC_Withhold ;
		SMTFlag		fddiPORTHardwarePresent ;
		u_अक्षर		fddiPORTLerFlag ;

		u_अक्षर		fddiPORTMultiple_U ;	/* निजी */
		u_अक्षर		fddiPORTMultiple_P ;	/* निजी */
		u_अक्षर		fddiPORTEB_Condition ;	/* निजी */
	पूर्ण p[NUMPHYS] ;
	काष्ठा अणु
		Counter		fddiPRIVECF_Req_Rx ;	/* ECF req received */
		Counter		fddiPRIVECF_Reply_Rx ;	/* ECF repl received */
		Counter		fddiPRIVECF_Req_Tx ;	/* ECF req transm */
		Counter		fddiPRIVECF_Reply_Tx ;	/* ECF repl transm */
		Counter		fddiPRIVPMF_Get_Rx ;	/* PMF Get rec */
		Counter		fddiPRIVPMF_Set_Rx ;	/* PMF Set rec */
		Counter		fddiPRIVRDF_Rx ;	/* RDF received */
		Counter		fddiPRIVRDF_Tx ;	/* RDF transmitted */
	पूर्ण priv ;
पूर्ण ;

/*
 * OIDs क्रम statistics
 */
#घोषणा	SMT_OID_CF_STATE	1	/* fddiSMTCF_State */
#घोषणा	SMT_OID_PCM_STATE_A	2	/* fddiPORTPCMState port A */
#घोषणा	SMT_OID_PCM_STATE_B	17	/* fddiPORTPCMState port B */
#घोषणा	SMT_OID_RMT_STATE	3	/* fddiMACRMTState */
#घोषणा	SMT_OID_UNA		4	/* fddiMACUpstreamNbr */
#घोषणा	SMT_OID_DNA		5	/* fddiMACOldDownstreamNbr */
#घोषणा	SMT_OID_ERROR_CT	6	/* fddiMACError_Ct */
#घोषणा	SMT_OID_LOST_CT		7	/* fddiMACLost_Ct */
#घोषणा	SMT_OID_LEM_CT		8	/* fddiPORTLem_Ct */
#घोषणा	SMT_OID_LEM_CT_A	11	/* fddiPORTLem_Ct port A */
#घोषणा	SMT_OID_LEM_CT_B	12	/* fddiPORTLem_Ct port B */
#घोषणा	SMT_OID_LCT_FAIL_CT	9	/* fddiPORTLCTFail_Ct */
#घोषणा	SMT_OID_LCT_FAIL_CT_A	13	/* fddiPORTLCTFail_Ct port A */
#घोषणा	SMT_OID_LCT_FAIL_CT_B	14	/* fddiPORTLCTFail_Ct port B */
#घोषणा	SMT_OID_LEM_REJECT_CT	10	/* fddiPORTLem_Reject_Ct */
#घोषणा	SMT_OID_LEM_REJECT_CT_A	15	/* fddiPORTLem_Reject_Ct port A */
#घोषणा	SMT_OID_LEM_REJECT_CT_B	16	/* fddiPORTLem_Reject_Ct port B */

/*
 * SK MIB
 */
#घोषणा SMT_OID_ECF_REQ_RX	20	/* ECF requests received */
#घोषणा SMT_OID_ECF_REPLY_RX	21	/* ECF replies received */
#घोषणा SMT_OID_ECF_REQ_TX	22	/* ECF requests transmitted */
#घोषणा SMT_OID_ECF_REPLY_TX	23	/* ECF replies transmitted */
#घोषणा SMT_OID_PMF_GET_RX	24	/* PMF get requests received */
#घोषणा SMT_OID_PMF_SET_RX	25	/* PMF set requests received */
#घोषणा SMT_OID_RDF_RX		26	/* RDF received */
#घोषणा SMT_OID_RDF_TX		27	/* RDF transmitted */
