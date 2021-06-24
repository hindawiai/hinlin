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
	Parameter Management Frame processing क्रम SMT 7.2
*/

#समावेश "h/types.h"
#समावेश "h/fddi.h"
#समावेश "h/smc.h"
#समावेश "h/smt_p.h"

#घोषणा KERNEL
#समावेश "h/smtstate.h"

#अगर_अघोषित	SLIM_SMT

अटल पूर्णांक smt_authorize(काष्ठा s_smc *smc, काष्ठा smt_header *sm);
अटल पूर्णांक smt_check_set_count(काष्ठा s_smc *smc, काष्ठा smt_header *sm);
अटल स्थिर काष्ठा s_p_tab* smt_get_ptab(u_लघु para);
अटल पूर्णांक smt_mib_phys(काष्ठा s_smc *smc);
अटल पूर्णांक smt_set_para(काष्ठा s_smc *smc, काष्ठा smt_para *pa, पूर्णांक index,
			पूर्णांक local, पूर्णांक set);
व्योम smt_add_para(काष्ठा s_smc *smc, काष्ठा s_pcon *pcon, u_लघु para,
		  पूर्णांक index, पूर्णांक local);
अटल SMbuf *smt_build_pmf_response(काष्ठा s_smc *smc, काष्ठा smt_header *req,
				     पूर्णांक set, पूर्णांक local);
अटल पूर्णांक port_to_mib(काष्ठा s_smc *smc, पूर्णांक p);

#घोषणा MOFFSS(e)	दुरत्व(काष्ठा fddi_mib, e)
#घोषणा MOFFMS(e)	दुरत्व(काष्ठा fddi_mib_m, e)
#घोषणा MOFFAS(e)	दुरत्व(काष्ठा fddi_mib_a, e)
#घोषणा MOFFPS(e)	दुरत्व(काष्ठा fddi_mib_p, e)


#घोषणा AC_G	0x01		/* Get */
#घोषणा AC_GR	0x02		/* Get/Set */
#घोषणा AC_S	0x04		/* Set */
#घोषणा AC_NA	0x08
#घोषणा AC_GROUP	0x10		/* Group */
#घोषणा MS2BCLK(x)	((x)*12500L)
/*
	F	LFag (byte)
	B	byte
	S	u_लघु	16 bit
	C	Counter 32 bit
	L	Long 32 bit
	T	Timer_2	32 bit
	P	TimeStamp ;
	A	LongAddress (6 byte)
	E	Enum 16 bit
	R	ResId 16 Bit
*/
अटल स्थिर काष्ठा s_p_tab अणु
	u_लघु	p_num ;		/* parameter code */
	u_अक्षर	p_access ;	/* access rights */
	u_लघु	p_offset ;	/* offset in mib */
	अक्षर	p_swap[3] ;	/* क्रमmat string */
पूर्ण p_tab[] = अणु
	/* StationIdGrp */
	अणु SMT_P100A,AC_GROUP	पूर्ण ,
	अणु SMT_P100B,AC_G,	MOFFSS(fddiSMTStationId),	"8"	पूर्ण ,
	अणु SMT_P100D,AC_G,	MOFFSS(fddiSMTOpVersionId),	"S"	पूर्ण ,
	अणु SMT_P100E,AC_G,	MOFFSS(fddiSMTHiVersionId),	"S"	पूर्ण ,
	अणु SMT_P100F,AC_G,	MOFFSS(fddiSMTLoVersionId),	"S"	पूर्ण ,
	अणु SMT_P1010,AC_G,	MOFFSS(fddiSMTManufacturerData), "D" पूर्ण ,
	अणु SMT_P1011,AC_GR,	MOFFSS(fddiSMTUserData),	"D"	पूर्ण ,
	अणु SMT_P1012,AC_G,	MOFFSS(fddiSMTMIBVersionId),	"S"	पूर्ण ,

	/* StationConfigGrp */
	अणु SMT_P1014,AC_GROUP	पूर्ण ,
	अणु SMT_P1015,AC_G,	MOFFSS(fddiSMTMac_Ct),		"B"	पूर्ण ,
	अणु SMT_P1016,AC_G,	MOFFSS(fddiSMTNonMaster_Ct),	"B"	पूर्ण ,
	अणु SMT_P1017,AC_G,	MOFFSS(fddiSMTMaster_Ct),	"B"	पूर्ण ,
	अणु SMT_P1018,AC_G,	MOFFSS(fddiSMTAvailablePaths),	"B"	पूर्ण ,
	अणु SMT_P1019,AC_G,	MOFFSS(fddiSMTConfigCapabilities),"S"	पूर्ण ,
	अणु SMT_P101A,AC_GR,	MOFFSS(fddiSMTConfigPolicy),	"wS"	पूर्ण ,
	अणु SMT_P101B,AC_GR,	MOFFSS(fddiSMTConnectionPolicy),"wS"	पूर्ण ,
	अणु SMT_P101D,AC_GR,	MOFFSS(fddiSMTTT_Notअगरy),	"wS"	पूर्ण ,
	अणु SMT_P101E,AC_GR,	MOFFSS(fddiSMTStatRptPolicy),	"bB"	पूर्ण ,
	अणु SMT_P101F,AC_GR,	MOFFSS(fddiSMTTrace_MaxExpiration),"lL"	पूर्ण ,
	अणु SMT_P1020,AC_G,	MOFFSS(fddiSMTPORTIndexes),	"II"	पूर्ण ,
	अणु SMT_P1021,AC_G,	MOFFSS(fddiSMTMACIndexes),	"I"	पूर्ण ,
	अणु SMT_P1022,AC_G,	MOFFSS(fddiSMTBypassPresent),	"F"	पूर्ण ,

	/* StatusGrp */
	अणु SMT_P1028,AC_GROUP	पूर्ण ,
	अणु SMT_P1029,AC_G,	MOFFSS(fddiSMTECMState),	"E"	पूर्ण ,
	अणु SMT_P102A,AC_G,	MOFFSS(fddiSMTCF_State),	"E"	पूर्ण ,
	अणु SMT_P102C,AC_G,	MOFFSS(fddiSMTRemoteDisconnectFlag),"F"	पूर्ण ,
	अणु SMT_P102D,AC_G,	MOFFSS(fddiSMTStationStatus),	"E"	पूर्ण ,
	अणु SMT_P102E,AC_G,	MOFFSS(fddiSMTPeerWrapFlag),	"F"	पूर्ण ,

	/* MIBOperationGrp */
	अणु SMT_P1032,AC_GROUP	पूर्ण ,
	अणु SMT_P1033,AC_G,	MOFFSS(fddiSMTTimeStamp),"P"		पूर्ण ,
	अणु SMT_P1034,AC_G,	MOFFSS(fddiSMTTransitionTimeStamp),"P"	पूर्ण ,
	/* NOTE : SMT_P1035 is alपढ़ोy swapped ! SMT_P_SETCOUNT */
	अणु SMT_P1035,AC_G,	MOFFSS(fddiSMTSetCount),"4P"		पूर्ण ,
	अणु SMT_P1036,AC_G,	MOFFSS(fddiSMTLastSetStationId),"8"	पूर्ण ,

	अणु SMT_P103C,AC_S,	0,				"wS"	पूर्ण ,

	/*
	 * PRIVATE EXTENSIONS
	 * only accessible locally to get/set passwd
	 */
	अणु SMT_P10F0,AC_GR,	MOFFSS(fddiPRPMFPasswd),	"8"	पूर्ण ,
	अणु SMT_P10F1,AC_GR,	MOFFSS(fddiPRPMFStation),	"8"	पूर्ण ,
#अगर_घोषित	ESS
	अणु SMT_P10F2,AC_GR,	MOFFSS(fddiESSPayload),		"lL"	पूर्ण ,
	अणु SMT_P10F3,AC_GR,	MOFFSS(fddiESSOverhead),	"lL"	पूर्ण ,
	अणु SMT_P10F4,AC_GR,	MOFFSS(fddiESSMaxTNeg),		"lL"	पूर्ण ,
	अणु SMT_P10F5,AC_GR,	MOFFSS(fddiESSMinSegmentSize),	"lL"	पूर्ण ,
	अणु SMT_P10F6,AC_GR,	MOFFSS(fddiESSCategory),	"lL"	पूर्ण ,
	अणु SMT_P10F7,AC_GR,	MOFFSS(fddiESSSynchTxMode),	"wS"	पूर्ण ,
#पूर्ण_अगर
#अगर_घोषित	SBA
	अणु SMT_P10F8,AC_GR,	MOFFSS(fddiSBACommand),		"bF"	पूर्ण ,
	अणु SMT_P10F9,AC_GR,	MOFFSS(fddiSBAAvailable),	"bF"	पूर्ण ,
#पूर्ण_अगर
	/* MAC Attributes */
	अणु SMT_P200A,AC_GROUP	पूर्ण ,
	अणु SMT_P200B,AC_G,	MOFFMS(fddiMACFrameStatusFunctions),"S"	पूर्ण ,
	अणु SMT_P200D,AC_G,	MOFFMS(fddiMACT_MaxCapabilitiy),"T"	पूर्ण ,
	अणु SMT_P200E,AC_G,	MOFFMS(fddiMACTVXCapabilitiy),"T"	पूर्ण ,

	/* ConfigGrp */
	अणु SMT_P2014,AC_GROUP	पूर्ण ,
	अणु SMT_P2016,AC_G,	MOFFMS(fddiMACAvailablePaths),	"B"	पूर्ण ,
	अणु SMT_P2017,AC_G,	MOFFMS(fddiMACCurrentPath),	"S"	पूर्ण ,
	अणु SMT_P2018,AC_G,	MOFFMS(fddiMACUpstreamNbr),	"A"	पूर्ण ,
	अणु SMT_P2019,AC_G,	MOFFMS(fddiMACDownstreamNbr),	"A"	पूर्ण ,
	अणु SMT_P201A,AC_G,	MOFFMS(fddiMACOldUpstreamNbr),	"A"	पूर्ण ,
	अणु SMT_P201B,AC_G,	MOFFMS(fddiMACOldDownstreamNbr),"A"	पूर्ण ,
	अणु SMT_P201D,AC_G,	MOFFMS(fddiMACDupAddressTest),	"E"	पूर्ण ,
	अणु SMT_P2020,AC_GR,	MOFFMS(fddiMACRequestedPaths),	"wS"	पूर्ण ,
	अणु SMT_P2021,AC_G,	MOFFMS(fddiMACDownstreamPORTType),"E"	पूर्ण ,
	अणु SMT_P2022,AC_G,	MOFFMS(fddiMACIndex),		"S"	पूर्ण ,

	/* AddressGrp */
	अणु SMT_P2028,AC_GROUP	पूर्ण ,
	अणु SMT_P2029,AC_G,	MOFFMS(fddiMACSMTAddress),	"A"	पूर्ण ,

	/* OperationGrp */
	अणु SMT_P2032,AC_GROUP	पूर्ण ,
	अणु SMT_P2033,AC_G,	MOFFMS(fddiMACT_Req),		"T"	पूर्ण ,
	अणु SMT_P2034,AC_G,	MOFFMS(fddiMACT_Neg),		"T"	पूर्ण ,
	अणु SMT_P2035,AC_G,	MOFFMS(fddiMACT_Max),		"T"	पूर्ण ,
	अणु SMT_P2036,AC_G,	MOFFMS(fddiMACTvxValue),	"T"	पूर्ण ,
	अणु SMT_P2038,AC_G,	MOFFMS(fddiMACT_Pri0),		"T"	पूर्ण ,
	अणु SMT_P2039,AC_G,	MOFFMS(fddiMACT_Pri1),		"T"	पूर्ण ,
	अणु SMT_P203A,AC_G,	MOFFMS(fddiMACT_Pri2),		"T"	पूर्ण ,
	अणु SMT_P203B,AC_G,	MOFFMS(fddiMACT_Pri3),		"T"	पूर्ण ,
	अणु SMT_P203C,AC_G,	MOFFMS(fddiMACT_Pri4),		"T"	पूर्ण ,
	अणु SMT_P203D,AC_G,	MOFFMS(fddiMACT_Pri5),		"T"	पूर्ण ,
	अणु SMT_P203E,AC_G,	MOFFMS(fddiMACT_Pri6),		"T"	पूर्ण ,


	/* CountersGrp */
	अणु SMT_P2046,AC_GROUP	पूर्ण ,
	अणु SMT_P2047,AC_G,	MOFFMS(fddiMACFrame_Ct),	"C"	पूर्ण ,
	अणु SMT_P2048,AC_G,	MOFFMS(fddiMACCopied_Ct),	"C"	पूर्ण ,
	अणु SMT_P2049,AC_G,	MOFFMS(fddiMACTransmit_Ct),	"C"	पूर्ण ,
	अणु SMT_P204A,AC_G,	MOFFMS(fddiMACToken_Ct),	"C"	पूर्ण ,
	अणु SMT_P2051,AC_G,	MOFFMS(fddiMACError_Ct),	"C"	पूर्ण ,
	अणु SMT_P2052,AC_G,	MOFFMS(fddiMACLost_Ct),		"C"	पूर्ण ,
	अणु SMT_P2053,AC_G,	MOFFMS(fddiMACTvxExpired_Ct),	"C"	पूर्ण ,
	अणु SMT_P2054,AC_G,	MOFFMS(fddiMACNotCopied_Ct),	"C"	पूर्ण ,
	अणु SMT_P2056,AC_G,	MOFFMS(fddiMACRingOp_Ct),	"C"	पूर्ण ,

	/* FrameErrorConditionGrp */
	अणु SMT_P205A,AC_GROUP	पूर्ण ,
	अणु SMT_P205F,AC_GR,	MOFFMS(fddiMACFrameErrorThreshold),"wS"	पूर्ण ,
	अणु SMT_P2060,AC_G,	MOFFMS(fddiMACFrameErrorRatio),	"S"	पूर्ण ,

	/* NotCopiedConditionGrp */
	अणु SMT_P2064,AC_GROUP	पूर्ण ,
	अणु SMT_P2067,AC_GR,	MOFFMS(fddiMACNotCopiedThreshold),"wS"	पूर्ण ,
	अणु SMT_P2069,AC_G,	MOFFMS(fddiMACNotCopiedRatio),	"S"	पूर्ण ,

	/* StatusGrp */
	अणु SMT_P206E,AC_GROUP	पूर्ण ,
	अणु SMT_P206F,AC_G,	MOFFMS(fddiMACRMTState),	"S"	पूर्ण ,
	अणु SMT_P2070,AC_G,	MOFFMS(fddiMACDA_Flag),	"F"	पूर्ण ,
	अणु SMT_P2071,AC_G,	MOFFMS(fddiMACUNDA_Flag),	"F"	पूर्ण ,
	अणु SMT_P2072,AC_G,	MOFFMS(fddiMACFrameErrorFlag),	"F"	पूर्ण ,
	अणु SMT_P2073,AC_G,	MOFFMS(fddiMACNotCopiedFlag),	"F"	पूर्ण ,
	अणु SMT_P2074,AC_G,	MOFFMS(fddiMACMA_UnitdataAvailable),"F"	पूर्ण ,
	अणु SMT_P2075,AC_G,	MOFFMS(fddiMACHardwarePresent),	"F"	पूर्ण ,
	अणु SMT_P2076,AC_GR,	MOFFMS(fddiMACMA_UnitdataEnable),"bF"	पूर्ण ,

	/*
	 * PRIVATE EXTENSIONS
	 * only accessible locally to get/set TMIN
	 */
	अणु SMT_P20F0,AC_NA						पूर्ण ,
	अणु SMT_P20F1,AC_GR,	MOFFMS(fddiMACT_Min),		"lT"	पूर्ण ,

	/* Path Attributes */
	/*
	 * DON't swap 320B,320F,3210: they are alपढ़ोy swapped in swap_para()
	 */
	अणु SMT_P320A,AC_GROUP	पूर्ण ,
	अणु SMT_P320B,AC_G,	MOFFAS(fddiPATHIndex),		"r"	पूर्ण ,
	अणु SMT_P320F,AC_GR,	MOFFAS(fddiPATHSbaPayload),	"l4"	पूर्ण ,
	अणु SMT_P3210,AC_GR,	MOFFAS(fddiPATHSbaOverhead),	"l4"	पूर्ण ,
	/* fddiPATHConfiguration */
	अणु SMT_P3212,AC_G,	0,				""	पूर्ण ,
	अणु SMT_P3213,AC_GR,	MOFFAS(fddiPATHT_Rmode),	"lT"	पूर्ण ,
	अणु SMT_P3214,AC_GR,	MOFFAS(fddiPATHSbaAvailable),	"lL"	पूर्ण ,
	अणु SMT_P3215,AC_GR,	MOFFAS(fddiPATHTVXLowerBound),	"lT"	पूर्ण ,
	अणु SMT_P3216,AC_GR,	MOFFAS(fddiPATHT_MaxLowerBound),"lT"	पूर्ण ,
	अणु SMT_P3217,AC_GR,	MOFFAS(fddiPATHMaxT_Req),	"lT"	पूर्ण ,

	/* Port Attributes */
	/* ConfigGrp */
	अणु SMT_P400A,AC_GROUP	पूर्ण ,
	अणु SMT_P400C,AC_G,	MOFFPS(fddiPORTMy_Type),	"E"	पूर्ण ,
	अणु SMT_P400D,AC_G,	MOFFPS(fddiPORTNeighborType),	"E"	पूर्ण ,
	अणु SMT_P400E,AC_GR,	MOFFPS(fddiPORTConnectionPolicies),"bB"	पूर्ण ,
	अणु SMT_P400F,AC_G,	MOFFPS(fddiPORTMacIndicated),	"2"	पूर्ण ,
	अणु SMT_P4010,AC_G,	MOFFPS(fddiPORTCurrentPath),	"E"	पूर्ण ,
	अणु SMT_P4011,AC_GR,	MOFFPS(fddiPORTRequestedPaths),	"l4"	पूर्ण ,
	अणु SMT_P4012,AC_G,	MOFFPS(fddiPORTMACPlacement),	"S"	पूर्ण ,
	अणु SMT_P4013,AC_G,	MOFFPS(fddiPORTAvailablePaths),	"B"	पूर्ण ,
	अणु SMT_P4016,AC_G,	MOFFPS(fddiPORTPMDClass),	"E"	पूर्ण ,
	अणु SMT_P4017,AC_G,	MOFFPS(fddiPORTConnectionCapabilities),	"B"पूर्ण ,
	अणु SMT_P401D,AC_G,	MOFFPS(fddiPORTIndex),		"R"	पूर्ण ,

	/* OperationGrp */
	अणु SMT_P401E,AC_GROUP	पूर्ण ,
	अणु SMT_P401F,AC_GR,	MOFFPS(fddiPORTMaपूर्णांक_LS),	"wE"	पूर्ण ,
	अणु SMT_P4021,AC_G,	MOFFPS(fddiPORTBS_Flag),	"F"	पूर्ण ,
	अणु SMT_P4022,AC_G,	MOFFPS(fddiPORTPC_LS),		"E"	पूर्ण ,

	/* ErrorCtrsGrp */
	अणु SMT_P4028,AC_GROUP	पूर्ण ,
	अणु SMT_P4029,AC_G,	MOFFPS(fddiPORTEBError_Ct),	"C"	पूर्ण ,
	अणु SMT_P402A,AC_G,	MOFFPS(fddiPORTLCTFail_Ct),	"C"	पूर्ण ,

	/* LerGrp */
	अणु SMT_P4032,AC_GROUP	पूर्ण ,
	अणु SMT_P4033,AC_G,	MOFFPS(fddiPORTLer_Estimate),	"F"	पूर्ण ,
	अणु SMT_P4034,AC_G,	MOFFPS(fddiPORTLem_Reject_Ct),	"C"	पूर्ण ,
	अणु SMT_P4035,AC_G,	MOFFPS(fddiPORTLem_Ct),		"C"	पूर्ण ,
	अणु SMT_P403A,AC_GR,	MOFFPS(fddiPORTLer_Cutoff),	"bB"	पूर्ण ,
	अणु SMT_P403B,AC_GR,	MOFFPS(fddiPORTLer_Alarm),	"bB"	पूर्ण ,

	/* StatusGrp */
	अणु SMT_P403C,AC_GROUP	पूर्ण ,
	अणु SMT_P403D,AC_G,	MOFFPS(fddiPORTConnectState),	"E"	पूर्ण ,
	अणु SMT_P403E,AC_G,	MOFFPS(fddiPORTPCMStateX),	"E"	पूर्ण ,
	अणु SMT_P403F,AC_G,	MOFFPS(fddiPORTPC_Withhold),	"E"	पूर्ण ,
	अणु SMT_P4040,AC_G,	MOFFPS(fddiPORTLerFlag),	"F"	पूर्ण ,
	अणु SMT_P4041,AC_G,	MOFFPS(fddiPORTHardwarePresent),"F"	पूर्ण ,

	अणु SMT_P4046,AC_S,	0,				"wS"	पूर्ण ,

	अणु 0,	AC_GROUP	पूर्ण ,
	अणु 0 पूर्ण
पूर्ण ;

व्योम smt_pmf_received_pack(काष्ठा s_smc *smc, SMbuf *mb, पूर्णांक local)
अणु
	काष्ठा smt_header	*sm ;
	SMbuf		*reply ;

	sm = smtod(mb,काष्ठा smt_header *) ;
	DB_SMT("SMT: processing PMF frame at %p len %d", sm, mb->sm_len);
#अगर_घोषित	DEBUG
	dump_smt(smc,sm,"PMF Received") ;
#पूर्ण_अगर
	/*
	 * Start the watchकरोg: It may be a दीर्घ, दीर्घ packet and
	 * maybe the watchकरोg occurs ...
	 */
	smt_start_watchकरोg(smc) ;

	अगर (sm->smt_class == SMT_PMF_GET ||
	    sm->smt_class == SMT_PMF_SET) अणु
		reply = smt_build_pmf_response(smc,sm,
			sm->smt_class == SMT_PMF_SET,local) ;
		अगर (reply) अणु
			sm = smtod(reply,काष्ठा smt_header *) ;
#अगर_घोषित	DEBUG
			dump_smt(smc,sm,"PMF Reply") ;
#पूर्ण_अगर
			smt_send_frame(smc,reply,FC_SMT_INFO,local) ;
		पूर्ण
	पूर्ण
पूर्ण

अटल SMbuf *smt_build_pmf_response(काष्ठा s_smc *smc, काष्ठा smt_header *req,
				     पूर्णांक set, पूर्णांक local)
अणु
	SMbuf			*mb ;
	काष्ठा smt_header	*smt ;
	काष्ठा smt_para		*pa ;
	काष्ठा smt_p_reason	*res ;
	स्थिर काष्ठा s_p_tab	*pt ;
	पूर्णांक			len ;
	पूर्णांक			index ;
	पूर्णांक			idx_end ;
	पूर्णांक			error ;
	पूर्णांक			range ;
	SK_LOC_DECL(काष्ठा s_pcon,pcon) ;
	SK_LOC_DECL(काष्ठा s_pcon,set_pcon) ;

	/*
	 * build SMT header
	 */
	अगर (!(mb = smt_get_mbuf(smc)))
		वापस mb;

	smt = smtod(mb, काष्ठा smt_header *) ;
	smt->smt_dest = req->smt_source ;	/* DA == source of request */
	smt->smt_class = req->smt_class ;	/* same class (GET/SET) */
	smt->smt_type = SMT_REPLY ;
	smt->smt_version = SMT_VID_2 ;
	smt->smt_tid = req->smt_tid ;		/* same TID */
	smt->smt_pad = 0 ;
	smt->smt_len = 0 ;

	/*
	 * setup parameter status
	 */
	pcon.pc_len = SMT_MAX_INFO_LEN ;	/* max para length */
	pcon.pc_err = 0 ;			/* no error */
	pcon.pc_badset = 0 ;			/* no bad set count */
	pcon.pc_p = (व्योम *) (smt + 1) ;	/* paras start here */

	/*
	 * check authoriziation and set count
	 */
	error = 0 ;
	अगर (set) अणु
		अगर (!local && smt_authorize(smc,req))
			error = SMT_RDF_AUTHOR ;
		अन्यथा अगर (smt_check_set_count(smc,req))
			pcon.pc_badset = SMT_RDF_BADSET ;
	पूर्ण
	/*
	 * add reason code and all mandatory parameters
	 */
	res = (काष्ठा smt_p_reason *) pcon.pc_p ;
	smt_add_para(smc,&pcon,(u_लघु) SMT_P_REASON,0,0) ;
	smt_add_para(smc,&pcon,(u_लघु) SMT_P1033,0,0) ;
	/* update 1035 and 1036 later अगर set */
	set_pcon = pcon ;
	smt_add_para(smc,&pcon,(u_लघु) SMT_P1035,0,0) ;
	smt_add_para(smc,&pcon,(u_लघु) SMT_P1036,0,0) ;

	pcon.pc_err = error ;
	len = req->smt_len ;
	pa = (काष्ठा smt_para *) (req + 1) ;
	/*
	 * process list of paras
	 */
	जबतक (!pcon.pc_err && len > 0 ) अणु
		अगर (((u_लघु)len < pa->p_len + PARA_LEN) || (pa->p_len & 3)) अणु
			pcon.pc_err = SMT_RDF_LENGTH ;
			अवरोध ;
		पूर्ण

		अगर (((range = (pa->p_type & 0xf000)) == 0x2000) ||
			range == 0x3000 || range == 0x4000) अणु
			/*
			 * get index क्रम PART,MAC ad PATH group
			 */
			index = *((u_अक्षर *)pa + PARA_LEN + 3) ;/* index */
			idx_end = index ;
			अगर (!set && (pa->p_len != 4)) अणु
				pcon.pc_err = SMT_RDF_LENGTH ;
				अवरोध ;
			पूर्ण
			अगर (!index && !set) अणु
				चयन (range) अणु
				हाल 0x2000 :
					index = INDEX_MAC ;
					idx_end = index - 1 + NUMMACS ;
					अवरोध ;
				हाल 0x3000 :
					index = INDEX_PATH ;
					idx_end = index - 1 + NUMPATHS ;
					अवरोध ;
				हाल 0x4000 :
					index = INDEX_PORT ;
					idx_end = index - 1 + NUMPHYS ;
#अगर_अघोषित	CONCENTRATOR
					अगर (smc->s.sas == SMT_SAS)
						idx_end = INDEX_PORT ;
#पूर्ण_अगर
					अवरोध ;
				पूर्ण
			पूर्ण
		पूर्ण
		अन्यथा अणु
			/*
			 * smt group has no index
			 */
			अगर (!set && (pa->p_len != 0)) अणु
				pcon.pc_err = SMT_RDF_LENGTH ;
				अवरोध ;
			पूर्ण
			index = 0 ;
			idx_end = 0 ;
		पूर्ण
		जबतक (index <= idx_end) अणु
			/*
			 * अगर group
			 *	add all paras of group
			 */
			pt = smt_get_ptab(pa->p_type) ;
			अगर (pt && pt->p_access == AC_GROUP && !set) अणु
				pt++ ;
				जबतक (pt->p_access == AC_G ||
					pt->p_access == AC_GR) अणु
					smt_add_para(smc,&pcon,pt->p_num,
						index,local);
					pt++ ;
				पूर्ण
			पूर्ण
			/*
			 * ignore
			 *	AUTHORIZATION in get/set
			 *	SET COUNT in set
			 */
			अन्यथा अगर (pa->p_type != SMT_P_AUTHOR &&
				 (!set || (pa->p_type != SMT_P1035))) अणु
				पूर्णांक	st ;
				अगर (pcon.pc_badset) अणु
					smt_add_para(smc,&pcon,pa->p_type,
						index,local) ;
				पूर्ण
				अन्यथा अगर (set) अणु
					st = smt_set_para(smc,pa,index,local,1);
					/*
					 * वापस para even अगर error
					 */
					smt_add_para(smc,&pcon,pa->p_type,
						index,local) ;
					pcon.pc_err = st ;
				पूर्ण
				अन्यथा अणु
					अगर (pt && pt->p_access == AC_S) अणु
						pcon.pc_err =
							SMT_RDF_ILLEGAL ;
					पूर्ण
					smt_add_para(smc,&pcon,pa->p_type,
						index,local) ;
				पूर्ण
			पूर्ण
			अगर (pcon.pc_err)
				अवरोध ;
			index++ ;
		पूर्ण
		len -= pa->p_len + PARA_LEN ;
		pa = (काष्ठा smt_para *) ((अक्षर *)pa + pa->p_len + PARA_LEN) ;
	पूर्ण
	smt->smt_len = SMT_MAX_INFO_LEN - pcon.pc_len ;
	mb->sm_len = smt->smt_len + माप(काष्ठा smt_header) ;

	/* update reason code */
	res->rdf_reason = pcon.pc_badset ? pcon.pc_badset :
			pcon.pc_err ? pcon.pc_err : SMT_RDF_SUCCESS ;
	अगर (set && (res->rdf_reason == SMT_RDF_SUCCESS)) अणु
		/*
		 * increment set count
		 * set समय stamp
		 * store station id of last set
		 */
		smc->mib.fddiSMTSetCount.count++ ;
		smt_set_बारtamp(smc,smc->mib.fddiSMTSetCount.बारtamp) ;
		smc->mib.fddiSMTLastSetStationId = req->smt_sid ;
		smt_add_para(smc,&set_pcon,(u_लघु) SMT_P1035,0,0) ;
		smt_add_para(smc,&set_pcon,(u_लघु) SMT_P1036,0,0) ;
	पूर्ण
	वापस mb;
पूर्ण

अटल पूर्णांक smt_authorize(काष्ठा s_smc *smc, काष्ठा smt_header *sm)
अणु
	काष्ठा smt_para	*pa ;
	पूर्णांक		i ;
	अक्षर		*p ;

	/*
	 * check source station id अगर not zero
	 */
	p = (अक्षर *) &smc->mib.fddiPRPMFStation ;
	क्रम (i = 0 ; i < 8 && !p[i] ; i++)
		;
	अगर (i != 8) अणु
		अगर (स_भेद((अक्षर *) &sm->smt_sid,
			(अक्षर *) &smc->mib.fddiPRPMFStation,8))
			वापस 1;
	पूर्ण
	/*
	 * check authoriziation parameter अगर passwd not zero
	 */
	p = (अक्षर *) smc->mib.fddiPRPMFPasswd ;
	क्रम (i = 0 ; i < 8 && !p[i] ; i++)
		;
	अगर (i != 8) अणु
		pa = (काष्ठा smt_para *) sm_to_para(smc,sm,SMT_P_AUTHOR) ;
		अगर (!pa)
			वापस 1;
		अगर (pa->p_len != 8)
			वापस 1;
		अगर (स_भेद((अक्षर *)(pa+1),(अक्षर *)smc->mib.fddiPRPMFPasswd,8))
			वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक smt_check_set_count(काष्ठा s_smc *smc, काष्ठा smt_header *sm)
अणु
	काष्ठा smt_para	*pa ;
	काष्ठा smt_p_setcount	*sc ;

	pa = (काष्ठा smt_para *) sm_to_para(smc,sm,SMT_P1035) ;
	अगर (pa) अणु
		sc = (काष्ठा smt_p_setcount *) pa ;
		अगर ((smc->mib.fddiSMTSetCount.count != sc->count) ||
			स_भेद((अक्षर *) smc->mib.fddiSMTSetCount.बारtamp,
			(अक्षर *)sc->बारtamp,8))
			वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

व्योम smt_add_para(काष्ठा s_smc *smc, काष्ठा s_pcon *pcon, u_लघु para,
		  पूर्णांक index, पूर्णांक local)
अणु
	काष्ठा smt_para	*pa ;
	स्थिर काष्ठा s_p_tab	*pt ;
	काष्ठा fddi_mib_m *mib_m = शून्य;
	काष्ठा fddi_mib_p *mib_p = शून्य;
	पूर्णांक		len ;
	पूर्णांक		plen ;
	अक्षर		*from ;
	अक्षर		*to ;
	स्थिर अक्षर	*swap ;
	अक्षर		c ;
	पूर्णांक		range ;
	अक्षर		*mib_addr ;
	पूर्णांक		mac ;
	पूर्णांक		path ;
	पूर्णांक		port ;
	पूर्णांक		sp_len ;

	/*
	 * skip अगर error
	 */
	अगर (pcon->pc_err)
		वापस ;

	/*
	 * actions करोn't have a value
	 */
	pt = smt_get_ptab(para) ;
	अगर (pt && pt->p_access == AC_S)
		वापस ;

	to = (अक्षर *) (pcon->pc_p) ;	/* destination poपूर्णांकer */
	len = pcon->pc_len ;		/* मुक्त space */
	plen = len ;			/* remember start length */
	pa = (काष्ठा smt_para *) to ;	/* type/length poपूर्णांकer */
	to += PARA_LEN ;		/* skip smt_para */
	len -= PARA_LEN ;
	/*
	 * set index अगर required
	 */
	अगर (((range = (para & 0xf000)) == 0x2000) ||
		range == 0x3000 || range == 0x4000) अणु
		अगर (len < 4)
			जाओ wrong_error ;
		to[0] = 0 ;
		to[1] = 0 ;
		to[2] = 0 ;
		to[3] = index ;
		len -= 4 ;
		to += 4 ;
	पूर्ण
	mac = index - INDEX_MAC ;
	path = index - INDEX_PATH ;
	port = index - INDEX_PORT ;
	/*
	 * get poपूर्णांकer to mib
	 */
	चयन (range) अणु
	हाल 0x1000 :
	शेष :
		mib_addr = (अक्षर *) (&smc->mib) ;
		अवरोध ;
	हाल 0x2000 :
		अगर (mac < 0 || mac >= NUMMACS) अणु
			pcon->pc_err = SMT_RDF_NOPARAM ;
			वापस ;
		पूर्ण
		mib_addr = (अक्षर *) (&smc->mib.m[mac]) ;
		mib_m = (काष्ठा fddi_mib_m *) mib_addr ;
		अवरोध ;
	हाल 0x3000 :
		अगर (path < 0 || path >= NUMPATHS) अणु
			pcon->pc_err = SMT_RDF_NOPARAM ;
			वापस ;
		पूर्ण
		mib_addr = (अक्षर *) (&smc->mib.a[path]) ;
		अवरोध ;
	हाल 0x4000 :
		अगर (port < 0 || port >= smt_mib_phys(smc)) अणु
			pcon->pc_err = SMT_RDF_NOPARAM ;
			वापस ;
		पूर्ण
		mib_addr = (अक्षर *) (&smc->mib.p[port_to_mib(smc,port)]) ;
		mib_p = (काष्ठा fddi_mib_p *) mib_addr ;
		अवरोध ;
	पूर्ण
	/*
	 * check special paras
	 */
	swap = शून्य;
	चयन (para) अणु
	हाल SMT_P10F0 :
	हाल SMT_P10F1 :
#अगर_घोषित	ESS
	हाल SMT_P10F2 :
	हाल SMT_P10F3 :
	हाल SMT_P10F4 :
	हाल SMT_P10F5 :
	हाल SMT_P10F6 :
	हाल SMT_P10F7 :
#पूर्ण_अगर
#अगर_घोषित	SBA
	हाल SMT_P10F8 :
	हाल SMT_P10F9 :
#पूर्ण_अगर
	हाल SMT_P20F1 :
		अगर (!local) अणु
			pcon->pc_err = SMT_RDF_NOPARAM ;
			वापस ;
		पूर्ण
		अवरोध ;
	हाल SMT_P2034 :
	हाल SMT_P2046 :
	हाल SMT_P2047 :
	हाल SMT_P204A :
	हाल SMT_P2051 :
	हाल SMT_P2052 :
		mac_update_counter(smc) ;
		अवरोध ;
	हाल SMT_P4022:
		mib_p->fddiPORTPC_LS = LS2MIB(
			sm_pm_get_ls(smc,port_to_mib(smc,port))) ;
		अवरोध ;
	हाल SMT_P_REASON :
		*(u32 *)to = 0 ;
		sp_len = 4 ;
		जाओ sp_करोne ;
	हाल SMT_P1033 :			/* समय stamp */
		smt_set_बारtamp(smc,smc->mib.fddiSMTTimeStamp) ;
		अवरोध ;

	हाल SMT_P1020:				/* port indexes */
#अगर	NUMPHYS == 12
		swap = "IIIIIIIIIIII" ;
#अन्यथा
#अगर	NUMPHYS == 2
		अगर (smc->s.sas == SMT_SAS)
			swap = "I" ;
		अन्यथा
			swap = "II" ;
#अन्यथा
#अगर	NUMPHYS == 24
		swap = "IIIIIIIIIIIIIIIIIIIIIIII" ;
#अन्यथा
	????
#पूर्ण_अगर
#पूर्ण_अगर
#पूर्ण_अगर
		अवरोध ;
	हाल SMT_P3212 :
		अणु
			sp_len = cem_build_path(smc,to,path) ;
			जाओ sp_करोne ;
		पूर्ण
	हाल SMT_P1048 :		/* peer wrap condition */
		अणु
			काष्ठा smt_p_1048	*sp ;
			sp = (काष्ठा smt_p_1048 *) to ;
			sp->p1048_flag = smc->mib.fddiSMTPeerWrapFlag ;
			sp->p1048_cf_state = smc->mib.fddiSMTCF_State ;
			sp_len = माप(काष्ठा smt_p_1048) ;
			जाओ sp_करोne ;
		पूर्ण
	हाल SMT_P208C :
		अणु
			काष्ठा smt_p_208c	*sp ;
			sp = (काष्ठा smt_p_208c *) to ;
			sp->p208c_flag =
				smc->mib.m[MAC0].fddiMACDuplicateAddressCond ;
			sp->p208c_dupcondition =
				(mib_m->fddiMACDA_Flag ? SMT_ST_MY_DUPA : 0) |
				(mib_m->fddiMACUNDA_Flag ? SMT_ST_UNA_DUPA : 0);
			sp->p208c_fddiदीर्घ =
				mib_m->fddiMACSMTAddress ;
			sp->p208c_fddiunaदीर्घ =
				mib_m->fddiMACUpstreamNbr ;
			sp->p208c_pad = 0 ;
			sp_len = माप(काष्ठा smt_p_208c) ;
			जाओ sp_करोne ;
		पूर्ण
	हाल SMT_P208D :		/* frame error condition */
		अणु
			काष्ठा smt_p_208d	*sp ;
			sp = (काष्ठा smt_p_208d *) to ;
			sp->p208d_flag =
				mib_m->fddiMACFrameErrorFlag ;
			sp->p208d_frame_ct =
				mib_m->fddiMACFrame_Ct ;
			sp->p208d_error_ct =
				mib_m->fddiMACError_Ct ;
			sp->p208d_lost_ct =
				mib_m->fddiMACLost_Ct ;
			sp->p208d_ratio =
				mib_m->fddiMACFrameErrorRatio ;
			sp_len = माप(काष्ठा smt_p_208d) ;
			जाओ sp_करोne ;
		पूर्ण
	हाल SMT_P208E :		/* not copied condition */
		अणु
			काष्ठा smt_p_208e	*sp ;
			sp = (काष्ठा smt_p_208e *) to ;
			sp->p208e_flag =
				mib_m->fddiMACNotCopiedFlag ;
			sp->p208e_not_copied =
				mib_m->fddiMACNotCopied_Ct ;
			sp->p208e_copied =
				mib_m->fddiMACCopied_Ct ;
			sp->p208e_not_copied_ratio =
				mib_m->fddiMACNotCopiedRatio ;
			sp_len = माप(काष्ठा smt_p_208e) ;
			जाओ sp_करोne ;
		पूर्ण
	हाल SMT_P208F :	/* neighbor change event */
		अणु
			काष्ठा smt_p_208f	*sp ;
			sp = (काष्ठा smt_p_208f *) to ;
			sp->p208f_multiple =
				mib_m->fddiMACMultiple_N ;
			sp->p208f_nacondition =
				mib_m->fddiMACDuplicateAddressCond ;
			sp->p208f_old_una =
				mib_m->fddiMACOldUpstreamNbr ;
			sp->p208f_new_una =
				mib_m->fddiMACUpstreamNbr ;
			sp->p208f_old_dna =
				mib_m->fddiMACOldDownstreamNbr ;
			sp->p208f_new_dna =
				mib_m->fddiMACDownstreamNbr ;
			sp->p208f_curren_path =
				mib_m->fddiMACCurrentPath ;
			sp->p208f_smt_address =
				mib_m->fddiMACSMTAddress ;
			sp_len = माप(काष्ठा smt_p_208f) ;
			जाओ sp_करोne ;
		पूर्ण
	हाल SMT_P2090 :
		अणु
			काष्ठा smt_p_2090	*sp ;
			sp = (काष्ठा smt_p_2090 *) to ;
			sp->p2090_multiple =
				mib_m->fddiMACMultiple_P ;
			sp->p2090_availablepaths =
				mib_m->fddiMACAvailablePaths ;
			sp->p2090_currentpath =
				mib_m->fddiMACCurrentPath ;
			sp->p2090_requestedpaths =
				mib_m->fddiMACRequestedPaths ;
			sp_len = माप(काष्ठा smt_p_2090) ;
			जाओ sp_करोne ;
		पूर्ण
	हाल SMT_P4050 :
		अणु
			काष्ठा smt_p_4050	*sp ;
			sp = (काष्ठा smt_p_4050 *) to ;
			sp->p4050_flag =
				mib_p->fddiPORTLerFlag ;
			sp->p4050_pad = 0 ;
			sp->p4050_cutoff =
				mib_p->fddiPORTLer_Cutoff ;
			sp->p4050_alarm =
				mib_p->fddiPORTLer_Alarm ;
			sp->p4050_estimate =
				mib_p->fddiPORTLer_Estimate ;
			sp->p4050_reject_ct =
				mib_p->fddiPORTLem_Reject_Ct ;
			sp->p4050_ct =
				mib_p->fddiPORTLem_Ct ;
			sp_len = माप(काष्ठा smt_p_4050) ;
			जाओ sp_करोne ;
		पूर्ण

	हाल SMT_P4051 :
		अणु
			काष्ठा smt_p_4051	*sp ;
			sp = (काष्ठा smt_p_4051 *) to ;
			sp->p4051_multiple =
				mib_p->fddiPORTMultiple_U ;
			sp->p4051_porttype =
				mib_p->fddiPORTMy_Type ;
			sp->p4051_connectstate =
				mib_p->fddiPORTConnectState ;
			sp->p4051_pc_neighbor =
				mib_p->fddiPORTNeighborType ;
			sp->p4051_pc_withhold =
				mib_p->fddiPORTPC_Withhold ;
			sp_len = माप(काष्ठा smt_p_4051) ;
			जाओ sp_करोne ;
		पूर्ण
	हाल SMT_P4052 :
		अणु
			काष्ठा smt_p_4052	*sp ;
			sp = (काष्ठा smt_p_4052 *) to ;
			sp->p4052_flag =
				mib_p->fddiPORTEB_Condition ;
			sp->p4052_eberrorcount =
				mib_p->fddiPORTEBError_Ct ;
			sp_len = माप(काष्ठा smt_p_4052) ;
			जाओ sp_करोne ;
		पूर्ण
	हाल SMT_P4053 :
		अणु
			काष्ठा smt_p_4053	*sp ;
			sp = (काष्ठा smt_p_4053 *) to ;
			sp->p4053_multiple =
				mib_p->fddiPORTMultiple_P ;
			sp->p4053_availablepaths =
				mib_p->fddiPORTAvailablePaths ;
			sp->p4053_currentpath =
				mib_p->fddiPORTCurrentPath ;
			स_नकल(	(अक्षर *) &sp->p4053_requestedpaths,
				(अक्षर *) mib_p->fddiPORTRequestedPaths,4) ;
			sp->p4053_mytype =
				mib_p->fddiPORTMy_Type ;
			sp->p4053_neighbortype =
				mib_p->fddiPORTNeighborType ;
			sp_len = माप(काष्ठा smt_p_4053) ;
			जाओ sp_करोne ;
		पूर्ण
	शेष :
		अवरोध ;
	पूर्ण
	/*
	 * in table ?
	 */
	अगर (!pt) अणु
		pcon->pc_err = (para & 0xff00) ? SMT_RDF_NOPARAM :
						SMT_RDF_ILLEGAL ;
		वापस ;
	पूर्ण
	/*
	 * check access rights
	 */
	चयन (pt->p_access) अणु
	हाल AC_G :
	हाल AC_GR :
		अवरोध ;
	शेष :
		pcon->pc_err = SMT_RDF_ILLEGAL ;
		वापस ;
	पूर्ण
	from = mib_addr + pt->p_offset ;
	अगर (!swap)
		swap = pt->p_swap ;		/* poपूर्णांकer to swap string */

	/*
	 * copy values
	 */
	जबतक ((c = *swap++)) अणु
		चयन(c) अणु
		हाल 'b' :
		हाल 'w' :
		हाल 'l' :
			अवरोध ;
		हाल 'S' :
		हाल 'E' :
		हाल 'R' :
		हाल 'r' :
			अगर (len < 4)
				जाओ len_error ;
			to[0] = 0 ;
			to[1] = 0 ;
#अगर_घोषित	LITTLE_ENDIAN
			अगर (c == 'r') अणु
				to[2] = *from++ ;
				to[3] = *from++ ;
			पूर्ण
			अन्यथा अणु
				to[3] = *from++ ;
				to[2] = *from++ ;
			पूर्ण
#अन्यथा
			to[2] = *from++ ;
			to[3] = *from++ ;
#पूर्ण_अगर
			to += 4 ;
			len -= 4 ;
			अवरोध ;
		हाल 'I' :		/* क्रम SET of port indexes */
			अगर (len < 2)
				जाओ len_error ;
#अगर_घोषित	LITTLE_ENDIAN
			to[1] = *from++ ;
			to[0] = *from++ ;
#अन्यथा
			to[0] = *from++ ;
			to[1] = *from++ ;
#पूर्ण_अगर
			to += 2 ;
			len -= 2 ;
			अवरोध ;
		हाल 'F' :
		हाल 'B' :
			अगर (len < 4)
				जाओ len_error ;
			len -= 4 ;
			to[0] = 0 ;
			to[1] = 0 ;
			to[2] = 0 ;
			to[3] = *from++ ;
			to += 4 ;
			अवरोध ;
		हाल 'C' :
		हाल 'T' :
		हाल 'L' :
			अगर (len < 4)
				जाओ len_error ;
#अगर_घोषित	LITTLE_ENDIAN
			to[3] = *from++ ;
			to[2] = *from++ ;
			to[1] = *from++ ;
			to[0] = *from++ ;
#अन्यथा
			to[0] = *from++ ;
			to[1] = *from++ ;
			to[2] = *from++ ;
			to[3] = *from++ ;
#पूर्ण_अगर
			len -= 4 ;
			to += 4 ;
			अवरोध ;
		हाल '2' :		/* PortMacIndicated */
			अगर (len < 4)
				जाओ len_error ;
			to[0] = 0 ;
			to[1] = 0 ;
			to[2] = *from++ ;
			to[3] = *from++ ;
			len -= 4 ;
			to += 4 ;
			अवरोध ;
		हाल '4' :
			अगर (len < 4)
				जाओ len_error ;
			to[0] = *from++ ;
			to[1] = *from++ ;
			to[2] = *from++ ;
			to[3] = *from++ ;
			len -= 4 ;
			to += 4 ;
			अवरोध ;
		हाल 'A' :
			अगर (len < 8)
				जाओ len_error ;
			to[0] = 0 ;
			to[1] = 0 ;
			स_नकल((अक्षर *) to+2,(अक्षर *) from,6) ;
			to += 8 ;
			from += 8 ;
			len -= 8 ;
			अवरोध ;
		हाल '8' :
			अगर (len < 8)
				जाओ len_error ;
			स_नकल((अक्षर *) to,(अक्षर *) from,8) ;
			to += 8 ;
			from += 8 ;
			len -= 8 ;
			अवरोध ;
		हाल 'D' :
			अगर (len < 32)
				जाओ len_error ;
			स_नकल((अक्षर *) to,(अक्षर *) from,32) ;
			to += 32 ;
			from += 32 ;
			len -= 32 ;
			अवरोध ;
		हाल 'P' :		/* बारtamp is NOT swapped */
			अगर (len < 8)
				जाओ len_error ;
			to[0] = *from++ ;
			to[1] = *from++ ;
			to[2] = *from++ ;
			to[3] = *from++ ;
			to[4] = *from++ ;
			to[5] = *from++ ;
			to[6] = *from++ ;
			to[7] = *from++ ;
			to += 8 ;
			len -= 8 ;
			अवरोध ;
		शेष :
			SMT_PANIC(smc,SMT_E0119, SMT_E0119_MSG) ;
			अवरोध ;
		पूर्ण
	पूर्ण

करोne:
	/*
	 * make it even (in हाल of 'I' encoding)
	 * note: len is DECREMENTED
	 */
	अगर (len & 3) अणु
		to[0] = 0 ;
		to[1] = 0 ;
		to += 4 - (len & 3 ) ;
		len = len & ~ 3 ;
	पूर्ण

	/* set type and length */
	pa->p_type = para ;
	pa->p_len = plen - len - PARA_LEN ;
	/* वापस values */
	pcon->pc_p = (व्योम *) to ;
	pcon->pc_len = len ;
	वापस ;

sp_करोne:
	len -= sp_len ;
	to += sp_len ;
	जाओ करोne ;

len_error:
	/* parameter करोes not fit in frame */
	pcon->pc_err = SMT_RDF_TOOLONG ;
	वापस ;

wrong_error:
	pcon->pc_err = SMT_RDF_LENGTH ;
पूर्ण

/*
 * set parameter
 */
अटल पूर्णांक smt_set_para(काष्ठा s_smc *smc, काष्ठा smt_para *pa, पूर्णांक index,
			पूर्णांक local, पूर्णांक set)
अणु
#घोषणा IFSET(x)	अगर (set) (x)

	स्थिर काष्ठा s_p_tab	*pt ;
	पूर्णांक		len ;
	अक्षर		*from ;
	अक्षर		*to ;
	स्थिर अक्षर	*swap ;
	अक्षर		c ;
	अक्षर		*mib_addr ;
	काष्ठा fddi_mib	*mib ;
	काष्ठा fddi_mib_m	*mib_m = शून्य;
	काष्ठा fddi_mib_a	*mib_a = शून्य;
	काष्ठा fddi_mib_p	*mib_p = शून्य;
	पूर्णांक		mac ;
	पूर्णांक		path ;
	पूर्णांक		port ;
	SK_LOC_DECL(u_अक्षर,byte_val) ;
	SK_LOC_DECL(u_लघु,word_val) ;
	SK_LOC_DECL(u_दीर्घ,दीर्घ_val) ;

	mac = index - INDEX_MAC ;
	path = index - INDEX_PATH ;
	port = index - INDEX_PORT ;
	len = pa->p_len ;
	from = (अक्षर *) (pa + 1 ) ;

	mib = &smc->mib ;
	चयन (pa->p_type & 0xf000) अणु
	हाल 0x1000 :
	शेष :
		mib_addr = (अक्षर *) mib ;
		अवरोध ;
	हाल 0x2000 :
		अगर (mac < 0 || mac >= NUMMACS) अणु
			वापस SMT_RDF_NOPARAM;
		पूर्ण
		mib_m = &smc->mib.m[mac] ;
		mib_addr = (अक्षर *) mib_m ;
		from += 4 ;		/* skip index */
		len -= 4 ;
		अवरोध ;
	हाल 0x3000 :
		अगर (path < 0 || path >= NUMPATHS) अणु
			वापस SMT_RDF_NOPARAM;
		पूर्ण
		mib_a = &smc->mib.a[path] ;
		mib_addr = (अक्षर *) mib_a ;
		from += 4 ;		/* skip index */
		len -= 4 ;
		अवरोध ;
	हाल 0x4000 :
		अगर (port < 0 || port >= smt_mib_phys(smc)) अणु
			वापस SMT_RDF_NOPARAM;
		पूर्ण
		mib_p = &smc->mib.p[port_to_mib(smc,port)] ;
		mib_addr = (अक्षर *) mib_p ;
		from += 4 ;		/* skip index */
		len -= 4 ;
		अवरोध ;
	पूर्ण
	चयन (pa->p_type) अणु
	हाल SMT_P10F0 :
	हाल SMT_P10F1 :
#अगर_घोषित	ESS
	हाल SMT_P10F2 :
	हाल SMT_P10F3 :
	हाल SMT_P10F4 :
	हाल SMT_P10F5 :
	हाल SMT_P10F6 :
	हाल SMT_P10F7 :
#पूर्ण_अगर
#अगर_घोषित	SBA
	हाल SMT_P10F8 :
	हाल SMT_P10F9 :
#पूर्ण_अगर
	हाल SMT_P20F1 :
		अगर (!local)
			वापस SMT_RDF_NOPARAM;
		अवरोध ;
	पूर्ण
	pt = smt_get_ptab(pa->p_type) ;
	अगर (!pt)
		वापस (pa->p_type & 0xff00) ? SMT_RDF_NOPARAM :
					       SMT_RDF_ILLEGAL;
	चयन (pt->p_access) अणु
	हाल AC_GR :
	हाल AC_S :
		अवरोध ;
	शेष :
		वापस SMT_RDF_ILLEGAL;
	पूर्ण
	to = mib_addr + pt->p_offset ;
	swap = pt->p_swap ;		/* poपूर्णांकer to swap string */

	जबतक (swap && (c = *swap++)) अणु
		चयन(c) अणु
		हाल 'b' :
			to = (अक्षर *) &byte_val ;
			अवरोध ;
		हाल 'w' :
			to = (अक्षर *) &word_val ;
			अवरोध ;
		हाल 'l' :
			to = (अक्षर *) &दीर्घ_val ;
			अवरोध ;
		हाल 'S' :
		हाल 'E' :
		हाल 'R' :
		हाल 'r' :
			अगर (len < 4) अणु
				जाओ len_error ;
			पूर्ण
			अगर (from[0] | from[1])
				जाओ val_error ;
#अगर_घोषित	LITTLE_ENDIAN
			अगर (c == 'r') अणु
				to[0] = from[2] ;
				to[1] = from[3] ;
			पूर्ण
			अन्यथा अणु
				to[1] = from[2] ;
				to[0] = from[3] ;
			पूर्ण
#अन्यथा
			to[0] = from[2] ;
			to[1] = from[3] ;
#पूर्ण_अगर
			from += 4 ;
			to += 2 ;
			len -= 4 ;
			अवरोध ;
		हाल 'F' :
		हाल 'B' :
			अगर (len < 4) अणु
				जाओ len_error ;
			पूर्ण
			अगर (from[0] | from[1] | from[2])
				जाओ val_error ;
			to[0] = from[3] ;
			len -= 4 ;
			from += 4 ;
			to += 4 ;
			अवरोध ;
		हाल 'C' :
		हाल 'T' :
		हाल 'L' :
			अगर (len < 4) अणु
				जाओ len_error ;
			पूर्ण
#अगर_घोषित	LITTLE_ENDIAN
			to[3] = *from++ ;
			to[2] = *from++ ;
			to[1] = *from++ ;
			to[0] = *from++ ;
#अन्यथा
			to[0] = *from++ ;
			to[1] = *from++ ;
			to[2] = *from++ ;
			to[3] = *from++ ;
#पूर्ण_अगर
			len -= 4 ;
			to += 4 ;
			अवरोध ;
		हाल 'A' :
			अगर (len < 8)
				जाओ len_error ;
			अगर (set)
				स_नकल(to,from+2,6) ;
			to += 8 ;
			from += 8 ;
			len -= 8 ;
			अवरोध ;
		हाल '4' :
			अगर (len < 4)
				जाओ len_error ;
			अगर (set)
				स_नकल(to,from,4) ;
			to += 4 ;
			from += 4 ;
			len -= 4 ;
			अवरोध ;
		हाल '8' :
			अगर (len < 8)
				जाओ len_error ;
			अगर (set)
				स_नकल(to,from,8) ;
			to += 8 ;
			from += 8 ;
			len -= 8 ;
			अवरोध ;
		हाल 'D' :
			अगर (len < 32)
				जाओ len_error ;
			अगर (set)
				स_नकल(to,from,32) ;
			to += 32 ;
			from += 32 ;
			len -= 32 ;
			अवरोध ;
		हाल 'P' :		/* बारtamp is NOT swapped */
			अगर (set) अणु
				to[0] = *from++ ;
				to[1] = *from++ ;
				to[2] = *from++ ;
				to[3] = *from++ ;
				to[4] = *from++ ;
				to[5] = *from++ ;
				to[6] = *from++ ;
				to[7] = *from++ ;
			पूर्ण
			to += 8 ;
			len -= 8 ;
			अवरोध ;
		शेष :
			SMT_PANIC(smc,SMT_E0120, SMT_E0120_MSG) ;
			वापस SMT_RDF_ILLEGAL;
		पूर्ण
	पूर्ण
	/*
	 * actions and पूर्णांकernal updates
	 */
	चयन (pa->p_type) अणु
	हाल SMT_P101A:			/* fddiSMTConfigPolicy */
		अगर (word_val & ~1)
			जाओ val_error ;
		IFSET(mib->fddiSMTConfigPolicy = word_val) ;
		अवरोध ;
	हाल SMT_P101B :		/* fddiSMTConnectionPolicy */
		अगर (!(word_val & POLICY_MM))
			जाओ val_error ;
		IFSET(mib->fddiSMTConnectionPolicy = word_val) ;
		अवरोध ;
	हाल SMT_P101D : 		/* fddiSMTTT_Notअगरy */
		अगर (word_val < 2 || word_val > 30)
			जाओ val_error ;
		IFSET(mib->fddiSMTTT_Notअगरy = word_val) ;
		अवरोध ;
	हाल SMT_P101E :		/* fddiSMTStatRptPolicy */
		अगर (byte_val & ~1)
			जाओ val_error ;
		IFSET(mib->fddiSMTStatRptPolicy = byte_val) ;
		अवरोध ;
	हाल SMT_P101F :		/* fddiSMTTrace_MaxExpiration */
		/*
		 * note: lower limit trace_max = 6.001773... s
		 * NO upper limit
		 */
		अगर (दीर्घ_val < (दीर्घ)0x478bf51L)
			जाओ val_error ;
		IFSET(mib->fddiSMTTrace_MaxExpiration = दीर्घ_val) ;
		अवरोध ;
#अगर_घोषित	ESS
	हाल SMT_P10F2 :		/* fddiESSPayload */
		अगर (दीर्घ_val > 1562)
			जाओ val_error ;
		अगर (set && smc->mib.fddiESSPayload != दीर्घ_val) अणु
			smc->ess.raf_act_समयr_poll = TRUE ;
			smc->mib.fddiESSPayload = दीर्घ_val ;
		पूर्ण
		अवरोध ;
	हाल SMT_P10F3 :		/* fddiESSOverhead */
		अगर (दीर्घ_val < 50 || दीर्घ_val > 5000)
			जाओ val_error ;
		अगर (set && smc->mib.fddiESSPayload &&
			smc->mib.fddiESSOverhead != दीर्घ_val) अणु
			smc->ess.raf_act_समयr_poll = TRUE ;
			smc->mib.fddiESSOverhead = दीर्घ_val ;
		पूर्ण
		अवरोध ;
	हाल SMT_P10F4 :		/* fddiESSMaxTNeg */
		अगर (दीर्घ_val > -MS2BCLK(5) || दीर्घ_val < -MS2BCLK(165))
			जाओ val_error ;
		IFSET(mib->fddiESSMaxTNeg = दीर्घ_val) ;
		अवरोध ;
	हाल SMT_P10F5 :		/* fddiESSMinSegmentSize */
		अगर (दीर्घ_val < 1 || दीर्घ_val > 4478)
			जाओ val_error ;
		IFSET(mib->fddiESSMinSegmentSize = दीर्घ_val) ;
		अवरोध ;
	हाल SMT_P10F6 :		/* fddiESSCategory */
		अगर ((दीर्घ_val & 0xffff) != 1)
			जाओ val_error ;
		IFSET(mib->fddiESSCategory = दीर्घ_val) ;
		अवरोध ;
	हाल SMT_P10F7 :		/* fddiESSSyncTxMode */
		अगर (word_val > 1)
			जाओ val_error ;
		IFSET(mib->fddiESSSynchTxMode = word_val) ;
		अवरोध ;
#पूर्ण_अगर
#अगर_घोषित	SBA
	हाल SMT_P10F8 :		/* fddiSBACommand */
		अगर (byte_val != SB_STOP && byte_val != SB_START)
			जाओ val_error ;
		IFSET(mib->fddiSBACommand = byte_val) ;
		अवरोध ;
	हाल SMT_P10F9 :		/* fddiSBAAvailable */
		अगर (byte_val > 100)
			जाओ val_error ;
		IFSET(mib->fddiSBAAvailable = byte_val) ;
		अवरोध ;
#पूर्ण_अगर
	हाल SMT_P2020 :		/* fddiMACRequestedPaths */
		अगर ((word_val & (MIB_P_PATH_PRIM_PREFER |
			MIB_P_PATH_PRIM_ALTER)) == 0 )
			जाओ val_error ;
		IFSET(mib_m->fddiMACRequestedPaths = word_val) ;
		अवरोध ;
	हाल SMT_P205F :		/* fddiMACFrameErrorThreshold */
		/* 0 .. ffff acceptable */
		IFSET(mib_m->fddiMACFrameErrorThreshold = word_val) ;
		अवरोध ;
	हाल SMT_P2067 :		/* fddiMACNotCopiedThreshold */
		/* 0 .. ffff acceptable */
		IFSET(mib_m->fddiMACNotCopiedThreshold = word_val) ;
		अवरोध ;
	हाल SMT_P2076:			/* fddiMACMA_UnitdataEnable */
		अगर (byte_val & ~1)
			जाओ val_error ;
		अगर (set) अणु
			mib_m->fddiMACMA_UnitdataEnable = byte_val ;
			queue_event(smc,EVENT_RMT,RM_ENABLE_FLAG) ;
		पूर्ण
		अवरोध ;
	हाल SMT_P20F1 :		/* fddiMACT_Min */
		IFSET(mib_m->fddiMACT_Min = दीर्घ_val) ;
		अवरोध ;
	हाल SMT_P320F :
		अगर (दीर्घ_val > 1562)
			जाओ val_error ;
		IFSET(mib_a->fddiPATHSbaPayload = दीर्घ_val) ;
#अगर_घोषित	ESS
		अगर (set)
			ess_para_change(smc) ;
#पूर्ण_अगर
		अवरोध ;
	हाल SMT_P3210 :
		अगर (दीर्घ_val > 5000)
			जाओ val_error ;
		
		अगर (दीर्घ_val != 0 && mib_a->fddiPATHSbaPayload == 0)
			जाओ val_error ;

		IFSET(mib_a->fddiPATHSbaOverhead = दीर्घ_val) ;
#अगर_घोषित	ESS
		अगर (set)
			ess_para_change(smc) ;
#पूर्ण_अगर
		अवरोध ;
	हाल SMT_P3213:			/* fddiPATHT_Rmode */
		/* no limit :
		 * 0 .. 343.597 => 0 .. 2e32 * 80nS
		 */
		अगर (set) अणु
			mib_a->fddiPATHT_Rmode = दीर्घ_val ;
			rपंचांग_set_समयr(smc) ;
		पूर्ण
		अवरोध ;
	हाल SMT_P3214 :		/* fddiPATHSbaAvailable */
		अगर (दीर्घ_val > 0x00BEBC20L)
			जाओ val_error ;
#अगर_घोषित SBA 
		अगर (set && mib->fddiSBACommand == SB_STOP)
			जाओ val_error ;
#पूर्ण_अगर
		IFSET(mib_a->fddiPATHSbaAvailable = दीर्घ_val) ;
		अवरोध ;
	हाल SMT_P3215 :		/* fddiPATHTVXLowerBound */
		IFSET(mib_a->fddiPATHTVXLowerBound = दीर्घ_val) ;
		जाओ change_mac_para ;
	हाल SMT_P3216 :		/* fddiPATHT_MaxLowerBound */
		IFSET(mib_a->fddiPATHT_MaxLowerBound = दीर्घ_val) ;
		जाओ change_mac_para ;
	हाल SMT_P3217 :		/* fddiPATHMaxT_Req */
		IFSET(mib_a->fddiPATHMaxT_Req = दीर्घ_val) ;

change_mac_para:
		अगर (set && smt_set_mac_opvalues(smc)) अणु
			RS_SET(smc,RS_EVENT) ;
			smc->sm.please_reconnect = 1 ;
			queue_event(smc,EVENT_ECM,EC_DISCONNECT) ;
		पूर्ण
		अवरोध ;
	हाल SMT_P400E :		/* fddiPORTConnectionPolicies */
		अगर (byte_val > 1)
			जाओ val_error ;
		IFSET(mib_p->fddiPORTConnectionPolicies = byte_val) ;
		अवरोध ;
	हाल SMT_P4011 :		/* fddiPORTRequestedPaths */
		/* all 3*8 bits allowed */
		IFSET(स_नकल((अक्षर *)mib_p->fddiPORTRequestedPaths,
			(अक्षर *)&दीर्घ_val,4)) ;
		अवरोध ;
	हाल SMT_P401F:			/* fddiPORTMaपूर्णांक_LS */
		अगर (word_val > 4)
			जाओ val_error ;
		IFSET(mib_p->fddiPORTMaपूर्णांक_LS = word_val) ;
		अवरोध ;
	हाल SMT_P403A :		/* fddiPORTLer_Cutoff */
		अगर (byte_val < 4 || byte_val > 15)
			जाओ val_error ;
		IFSET(mib_p->fddiPORTLer_Cutoff = byte_val) ;
		अवरोध ;
	हाल SMT_P403B :		/* fddiPORTLer_Alarm */
		अगर (byte_val < 4 || byte_val > 15)
			जाओ val_error ;
		IFSET(mib_p->fddiPORTLer_Alarm = byte_val) ;
		अवरोध ;

	/*
	 * Actions
	 */
	हाल SMT_P103C :		/* fddiSMTStationAction */
		अगर (smt_action(smc,SMT_STATION_ACTION, (पूर्णांक) word_val, 0))
			जाओ val_error ;
		अवरोध ;
	हाल SMT_P4046:			/* fddiPORTAction */
		अगर (smt_action(smc,SMT_PORT_ACTION, (पूर्णांक) word_val,
			port_to_mib(smc,port)))
			जाओ val_error ;
		अवरोध ;
	शेष :
		अवरोध ;
	पूर्ण
	वापस 0;

val_error:
	/* parameter value in frame is out of range */
	वापस SMT_RDF_RANGE;

len_error:
	/* parameter value in frame is too लघु */
	वापस SMT_RDF_LENGTH;

#अगर	0
no_author_error:
	/* parameter not setable, because the SBA is not active
	 * Please note: we give the वापस code 'not authorizeed
	 *  because SBA denied is not a valid वापस code in the
	 * PMF protocol.
	 */
	वापस SMT_RDF_AUTHOR;
#पूर्ण_अगर
पूर्ण

अटल स्थिर काष्ठा s_p_tab *smt_get_ptab(u_लघु para)
अणु
	स्थिर काष्ठा s_p_tab	*pt ;
	क्रम (pt = p_tab ; pt->p_num && pt->p_num != para ; pt++)
		;
	वापस pt->p_num ? pt : शून्य;
पूर्ण

अटल पूर्णांक smt_mib_phys(काष्ठा s_smc *smc)
अणु
#अगर_घोषित	CONCENTRATOR
	SK_UNUSED(smc) ;

	वापस NUMPHYS;
#अन्यथा
	अगर (smc->s.sas == SMT_SAS)
		वापस 1;
	वापस NUMPHYS;
#पूर्ण_अगर
पूर्ण

अटल पूर्णांक port_to_mib(काष्ठा s_smc *smc, पूर्णांक p)
अणु
#अगर_घोषित	CONCENTRATOR
	SK_UNUSED(smc) ;

	वापस p;
#अन्यथा
	अगर (smc->s.sas == SMT_SAS)
		वापस PS;
	वापस p;
#पूर्ण_अगर
पूर्ण


#अगर_घोषित	DEBUG
#अगर_अघोषित	BOOT
व्योम dump_smt(काष्ठा s_smc *smc, काष्ठा smt_header *sm, अक्षर *text)
अणु
	पूर्णांक	len ;
	काष्ठा smt_para	*pa ;
	अक्षर	*c ;
	पूर्णांक	n ;
	पूर्णांक	nn ;
#अगर_घोषित	LITTLE_ENDIAN
	पूर्णांक	smtlen ;
#पूर्ण_अगर

	SK_UNUSED(smc) ;

#अगर_घोषित	DEBUG_BRD
	अगर (smc->debug.d_smtf < 2)
#अन्यथा
	अगर (debug.d_smtf < 2)
#पूर्ण_अगर
		वापस ;
#अगर_घोषित	LITTLE_ENDIAN
	smtlen = sm->smt_len + माप(काष्ठा smt_header) ;
#पूर्ण_अगर
	म_लिखो("SMT Frame [%s]:\nDA  ",text) ;
	dump_hex((अक्षर *) &sm->smt_dest,6) ;
	म_लिखो("\tSA ") ;
	dump_hex((अक्षर *) &sm->smt_source,6) ;
	म_लिखो(" Class %x Type %x Version %x\n",
		sm->smt_class,sm->smt_type,sm->smt_version)  ;
	म_लिखो("TID %x\t\tSID ", sm->smt_tid);
	dump_hex((अक्षर *) &sm->smt_sid,8) ;
	म_लिखो(" LEN %x\n",sm->smt_len) ;

	len = sm->smt_len ;
	pa = (काष्ठा smt_para *) (sm + 1) ;
	जबतक (len > 0 ) अणु
		पूर्णांक	plen ;
#अगर_घोषित UNIX
		म_लिखो("TYPE %x LEN %x VALUE\t",pa->p_type,pa->p_len) ;
#अन्यथा
		म_लिखो("TYPE %04x LEN %2x VALUE\t",pa->p_type,pa->p_len) ;
#पूर्ण_अगर
		n = pa->p_len ;
		अगर ( (n < 0 ) || (n > (पूर्णांक)(len - PARA_LEN))) अणु
			n = len - PARA_LEN ;
			म_लिखो(" BAD LENGTH\n") ;
			अवरोध ;
		पूर्ण
#अगर_घोषित	LITTLE_ENDIAN
		smt_swap_para(sm,smtlen,0) ;
#पूर्ण_अगर
		अगर (n < 24) अणु
			dump_hex((अक्षर *)(pa+1),(पूर्णांक) n) ;
			म_लिखो("\n") ;
		पूर्ण
		अन्यथा अणु
			पूर्णांक	first = 0 ;
			c = (अक्षर *)(pa+1) ;
			dump_hex(c,16) ;
			म_लिखो("\n") ;
			n -= 16 ;
			c += 16 ;
			जबतक (n > 0) अणु
				nn = (n > 16) ? 16 : n ;
				अगर (n > 64) अणु
					अगर (first == 0)
						म_लिखो("\t\t\t...\n") ;
					first = 1 ;
				पूर्ण
				अन्यथा अणु
					म_लिखो("\t\t\t") ;
					dump_hex(c,nn) ;
					म_लिखो("\n") ;
				पूर्ण
				n -= nn ;
				c += 16 ;
			पूर्ण
		पूर्ण
#अगर_घोषित	LITTLE_ENDIAN
		smt_swap_para(sm,smtlen,1) ;
#पूर्ण_अगर
		plen = (pa->p_len + PARA_LEN + 3) & ~3 ;
		len -= plen ;
		pa = (काष्ठा smt_para *)((अक्षर *)pa + plen) ;
	पूर्ण
	म_लिखो("-------------------------------------------------\n\n") ;
पूर्ण

व्योम dump_hex(अक्षर *p, पूर्णांक len)
अणु
	पूर्णांक	n = 0 ;
	जबतक (len--) अणु
		n++ ;
#अगर_घोषित UNIX
		म_लिखो("%x%s",*p++ & 0xff,len ? ( (n & 7) ? " " : "-") : "") ;
#अन्यथा
		म_लिखो("%02x%s",*p++ & 0xff,len ? ( (n & 7) ? " " : "-") : "") ;
#पूर्ण_अगर
	पूर्ण
पूर्ण
#पूर्ण_अगर	/* no BOOT */
#पूर्ण_अगर	/* DEBUG */


#पूर्ण_अगर	/* no SLIM_SMT */
