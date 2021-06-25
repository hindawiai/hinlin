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

#समावेश "h/types.h"
#समावेश "h/fddi.h"
#समावेश "h/smc.h"
#समावेश "h/smt_p.h"
#समावेश <linux/bitrev.h>
#समावेश <linux/kernel.h>

#घोषणा KERNEL
#समावेश "h/smtstate.h"

/*
 * FC in SMbuf
 */
#घोषणा m_fc(mb)	((mb)->sm_data[0])

#घोषणा SMT_TID_MAGIC	0x1f0a7b3c

अटल स्थिर अक्षर *स्थिर smt_type_name[] = अणु
	"SMT_00??", "SMT_INFO", "SMT_02??", "SMT_03??",
	"SMT_04??", "SMT_05??", "SMT_06??", "SMT_07??",
	"SMT_08??", "SMT_09??", "SMT_0A??", "SMT_0B??",
	"SMT_0C??", "SMT_0D??", "SMT_0E??", "SMT_NSA"
पूर्ण ;

अटल स्थिर अक्षर *स्थिर smt_class_name[] = अणु
	"UNKNOWN","NIF","SIF_CONFIG","SIF_OPER","ECF","RAF","RDF",
	"SRF","PMF_GET","PMF_SET","ESF"
पूर्ण ;

#घोषणा LAST_CLASS	(SMT_PMF_SET)

अटल स्थिर काष्ठा fddi_addr SMT_Unknown = अणु
	अणु 0,0,0x1f,0,0,0 पूर्ण
पूर्ण ;

/*
 * function prototypes
 */
#अगर_घोषित	LITTLE_ENDIAN
अटल पूर्णांक smt_swap_लघु(u_लघु s);
#पूर्ण_अगर
अटल पूर्णांक mac_index(काष्ठा s_smc *smc, पूर्णांक mac);
अटल पूर्णांक phy_index(काष्ठा s_smc *smc, पूर्णांक phy);
अटल पूर्णांक mac_con_resource_index(काष्ठा s_smc *smc, पूर्णांक mac);
अटल पूर्णांक phy_con_resource_index(काष्ठा s_smc *smc, पूर्णांक phy);
अटल व्योम smt_send_rdf(काष्ठा s_smc *smc, SMbuf *rej, पूर्णांक fc, पूर्णांक reason,
			 पूर्णांक local);
अटल व्योम smt_send_nअगर(काष्ठा s_smc *smc, स्थिर काष्ठा fddi_addr *dest, 
			 पूर्णांक fc, u_दीर्घ tid, पूर्णांक type, पूर्णांक local);
अटल व्योम smt_send_ecf(काष्ठा s_smc *smc, काष्ठा fddi_addr *dest, पूर्णांक fc,
                         u_दीर्घ tid, पूर्णांक type, पूर्णांक len);
अटल व्योम smt_echo_test(काष्ठा s_smc *smc, पूर्णांक dna);
अटल व्योम smt_send_sअगर_config(काष्ठा s_smc *smc, काष्ठा fddi_addr *dest,
				u_दीर्घ tid, पूर्णांक local);
अटल व्योम smt_send_sअगर_operation(काष्ठा s_smc *smc, काष्ठा fddi_addr *dest,
				   u_दीर्घ tid, पूर्णांक local);
#अगर_घोषित LITTLE_ENDIAN
अटल व्योम smt_string_swap(अक्षर *data, स्थिर अक्षर *क्रमmat, पूर्णांक len);
#पूर्ण_अगर
अटल व्योम smt_add_frame_len(SMbuf *mb, पूर्णांक len);
अटल व्योम smt_fill_una(काष्ठा s_smc *smc, काष्ठा smt_p_una *una);
अटल व्योम smt_fill_sde(काष्ठा s_smc *smc, काष्ठा smt_p_sde *sde);
अटल व्योम smt_fill_state(काष्ठा s_smc *smc, काष्ठा smt_p_state *state);
अटल व्योम smt_fill_बारtamp(काष्ठा s_smc *smc, काष्ठा smt_p_बारtamp *ts);
अटल व्योम smt_fill_policy(काष्ठा s_smc *smc, काष्ठा smt_p_policy *policy);
अटल व्योम smt_fill_latency(काष्ठा s_smc *smc, काष्ठा smt_p_latency *latency);
अटल व्योम smt_fill_neighbor(काष्ठा s_smc *smc, काष्ठा smt_p_neighbor *neighbor);
अटल पूर्णांक smt_fill_path(काष्ठा s_smc *smc, काष्ठा smt_p_path *path);
अटल व्योम smt_fill_mac_status(काष्ठा s_smc *smc, काष्ठा smt_p_mac_status *st);
अटल व्योम smt_fill_lem(काष्ठा s_smc *smc, काष्ठा smt_p_lem *lem, पूर्णांक phy);
अटल व्योम smt_fill_version(काष्ठा s_smc *smc, काष्ठा smt_p_version *vers);
अटल व्योम smt_fill_fsc(काष्ठा s_smc *smc, काष्ठा smt_p_fsc *fsc);
अटल व्योम smt_fill_mac_counter(काष्ठा s_smc *smc, काष्ठा smt_p_mac_counter *mc);
अटल व्योम smt_fill_mac_fnc(काष्ठा s_smc *smc, काष्ठा smt_p_mac_fnc *fnc);
अटल व्योम smt_fill_manufacturer(काष्ठा s_smc *smc, 
				  काष्ठा smp_p_manufacturer *man);
अटल व्योम smt_fill_user(काष्ठा s_smc *smc, काष्ठा smp_p_user *user);
अटल व्योम smt_fill_setcount(काष्ठा s_smc *smc, काष्ठा smt_p_setcount *setcount);
अटल व्योम smt_fill_echo(काष्ठा s_smc *smc, काष्ठा smt_p_echo *echo, u_दीर्घ seed,
			  पूर्णांक len);

अटल व्योम smt_clear_una_dna(काष्ठा s_smc *smc);
अटल व्योम smt_clear_old_una_dna(काष्ठा s_smc *smc);
#अगर_घोषित	CONCENTRATOR
अटल पूर्णांक entity_to_index(व्योम);
#पूर्ण_अगर
अटल व्योम update_dac(काष्ठा s_smc *smc, पूर्णांक report);
अटल पूर्णांक भाग_ratio(u_दीर्घ upper, u_दीर्घ lower);
#अगर_घोषित  USE_CAN_ADDR
अटल व्योम	hwm_conv_can(काष्ठा s_smc *smc, अक्षर *data, पूर्णांक len);
#अन्यथा
#घोषणा		hwm_conv_can(smc,data,len)
#पूर्ण_अगर


अटल अंतरभूत पूर्णांक is_my_addr(स्थिर काष्ठा s_smc *smc, 
			     स्थिर काष्ठा fddi_addr *addr)
अणु
	वापस(*(लघु *)(&addr->a[0]) ==
		*(लघु *)(&smc->mib.m[MAC0].fddiMACSMTAddress.a[0])
	  && *(लघु *)(&addr->a[2]) ==
		*(लघु *)(&smc->mib.m[MAC0].fddiMACSMTAddress.a[2])
	  && *(लघु *)(&addr->a[4]) ==
		*(लघु *)(&smc->mib.m[MAC0].fddiMACSMTAddress.a[4])) ;
पूर्ण

अटल अंतरभूत पूर्णांक is_broadcast(स्थिर काष्ठा fddi_addr *addr)
अणु
	वापस *(u_लघु *)(&addr->a[0]) == 0xffff &&
	       *(u_लघु *)(&addr->a[2]) == 0xffff &&
	       *(u_लघु *)(&addr->a[4]) == 0xffff;
पूर्ण

अटल अंतरभूत पूर्णांक is_inभागidual(स्थिर काष्ठा fddi_addr *addr)
अणु
	वापस !(addr->a[0] & GROUP_ADDR);
पूर्ण

अटल अंतरभूत पूर्णांक is_equal(स्थिर काष्ठा fddi_addr *addr1, 
			   स्थिर काष्ठा fddi_addr *addr2)
अणु
	वापस *(u_लघु *)(&addr1->a[0]) == *(u_लघु *)(&addr2->a[0]) &&
	       *(u_लघु *)(&addr1->a[2]) == *(u_लघु *)(&addr2->a[2]) &&
	       *(u_लघु *)(&addr1->a[4]) == *(u_लघु *)(&addr2->a[4]);
पूर्ण

/*
 * list of mandatory paras in frames
 */
अटल स्थिर u_लघु plist_nअगर[] = अणु SMT_P_UNA,SMT_P_SDE,SMT_P_STATE,0 पूर्ण ;

/*
 * init SMT agent
 */
व्योम smt_agent_init(काष्ठा s_smc *smc)
अणु
	पूर्णांक		i ;

	/*
	 * get MAC address
	 */
	smc->mib.m[MAC0].fddiMACSMTAddress = smc->hw.fddi_home_addr ;

	/*
	 * get OUI address from driver (bia == built-in-address)
	 */
	smc->mib.fddiSMTStationId.sid_oem[0] = 0 ;
	smc->mib.fddiSMTStationId.sid_oem[1] = 0 ;
	driver_get_bia(smc,&smc->mib.fddiSMTStationId.sid_node) ;
	क्रम (i = 0 ; i < 6 ; i ++) अणु
		smc->mib.fddiSMTStationId.sid_node.a[i] =
			bitrev8(smc->mib.fddiSMTStationId.sid_node.a[i]);
	पूर्ण
	smc->mib.fddiSMTManufacturerData[0] =
		smc->mib.fddiSMTStationId.sid_node.a[0] ;
	smc->mib.fddiSMTManufacturerData[1] =
		smc->mib.fddiSMTStationId.sid_node.a[1] ;
	smc->mib.fddiSMTManufacturerData[2] =
		smc->mib.fddiSMTStationId.sid_node.a[2] ;
	smc->sm.smt_tid = 0 ;
	smc->mib.m[MAC0].fddiMACDupAddressTest = DA_NONE ;
	smc->mib.m[MAC0].fddiMACUNDA_Flag = FALSE ;
#अगर_अघोषित	SLIM_SMT
	smt_clear_una_dna(smc) ;
	smt_clear_old_una_dna(smc) ;
#पूर्ण_अगर
	क्रम (i = 0 ; i < SMT_MAX_TEST ; i++)
		smc->sm.pend[i] = 0 ;
	smc->sm.please_reconnect = 0 ;
	smc->sm.uniq_ticks = 0 ;
पूर्ण

/*
 * SMT task
 * क्रमever
 *	delay 30 seconds
 *	send NIF
 *	check tvu & tvd
 * end
 */
व्योम smt_agent_task(काष्ठा s_smc *smc)
अणु
	smt_समयr_start(smc,&smc->sm.smt_समयr, (u_दीर्घ)1000000L,
		EV_TOKEN(EVENT_SMT,SM_TIMER)) ;
	DB_SMT("SMT agent task");
पूर्ण

#अगर_अघोषित SMT_REAL_TOKEN_CT
व्योम smt_emulate_token_ct(काष्ठा s_smc *smc, पूर्णांक mac_index)
अणु
	u_दीर्घ	count;
	u_दीर्घ	समय;


	समय = smt_get_समय();
	count =	((समय - smc->sm.last_tok_समय[mac_index]) *
					100)/TICKS_PER_SECOND;

	/*
	 * Only when ring is up we will have a token count. The
	 * flag is unक्रमtunately a single instance value. This
	 * करोesn't matter now, because we currently have only
	 * one MAC instance.
	 */
	अगर (smc->hw.mac_ring_is_up)अणु
		smc->mib.m[mac_index].fddiMACToken_Ct += count;
	पूर्ण

	/* Remember current समय */
	smc->sm.last_tok_समय[mac_index] = समय;

पूर्ण
#पूर्ण_अगर

/*ARGSUSED1*/
व्योम smt_event(काष्ठा s_smc *smc, पूर्णांक event)
अणु
	u_दीर्घ		समय ;
#अगर_अघोषित SMT_REAL_TOKEN_CT
	पूर्णांक		i ;
#पूर्ण_अगर


	अगर (smc->sm.please_reconnect) अणु
		smc->sm.please_reconnect -- ;
		अगर (smc->sm.please_reconnect == 0) अणु
			/* Counted करोwn */
			queue_event(smc,EVENT_ECM,EC_CONNECT) ;
		पूर्ण
	पूर्ण

	अगर (event == SM_FAST)
		वापस ;

	/*
	 * समयr क्रम periodic cleanup in driver
	 * reset and start the watchकरोg (FM2)
	 * ESS समयr
	 * SBA समयr
	 */
	smt_समयr_poll(smc) ;
	smt_start_watchकरोg(smc) ;
#अगर_अघोषित	SLIM_SMT
#अगर_अघोषित BOOT
#अगर_घोषित	ESS
	ess_समयr_poll(smc) ;
#पूर्ण_अगर
#पूर्ण_अगर
#अगर_घोषित	SBA
	sba_समयr_poll(smc) ;
#पूर्ण_अगर

	smt_srf_event(smc,0,0,0) ;

#पूर्ण_अगर	/* no SLIM_SMT */

	समय = smt_get_समय() ;

	अगर (समय - smc->sm.smt_last_lem >= TICKS_PER_SECOND*8) अणु
		/*
		 * Use 8 sec. क्रम the समय पूर्णांकervall, it simplअगरies the
		 * LER estimation.
		 */
		काष्ठा fddi_mib_m	*mib ;
		u_दीर्घ			upper ;
		u_दीर्घ			lower ;
		पूर्णांक			cond ;
		पूर्णांक			port;
		काष्ठा s_phy		*phy ;
		/*
		 * calculate LEM bit error rate
		 */
		sm_lem_evaluate(smc) ;
		smc->sm.smt_last_lem = समय ;

		/*
		 * check conditions
		 */
#अगर_अघोषित	SLIM_SMT
		mac_update_counter(smc) ;
		mib = smc->mib.m ;
		upper =
		(mib->fddiMACLost_Ct - mib->fddiMACOld_Lost_Ct) +
		(mib->fddiMACError_Ct - mib->fddiMACOld_Error_Ct) ;
		lower =
		(mib->fddiMACFrame_Ct - mib->fddiMACOld_Frame_Ct) +
		(mib->fddiMACLost_Ct - mib->fddiMACOld_Lost_Ct) ;
		mib->fddiMACFrameErrorRatio = भाग_ratio(upper,lower) ;

		cond =
			((!mib->fddiMACFrameErrorThreshold &&
			mib->fddiMACError_Ct != mib->fddiMACOld_Error_Ct) ||
			(mib->fddiMACFrameErrorRatio >
			mib->fddiMACFrameErrorThreshold)) ;

		अगर (cond != mib->fddiMACFrameErrorFlag)
			smt_srf_event(smc,SMT_COND_MAC_FRAME_ERROR,
				INDEX_MAC,cond) ;

		upper =
		(mib->fddiMACNotCopied_Ct - mib->fddiMACOld_NotCopied_Ct) ;
		lower =
		upper +
		(mib->fddiMACCopied_Ct - mib->fddiMACOld_Copied_Ct) ;
		mib->fddiMACNotCopiedRatio = भाग_ratio(upper,lower) ;

		cond =
			((!mib->fddiMACNotCopiedThreshold &&
			mib->fddiMACNotCopied_Ct !=
				mib->fddiMACOld_NotCopied_Ct)||
			(mib->fddiMACNotCopiedRatio >
			mib->fddiMACNotCopiedThreshold)) ;

		अगर (cond != mib->fddiMACNotCopiedFlag)
			smt_srf_event(smc,SMT_COND_MAC_NOT_COPIED,
				INDEX_MAC,cond) ;

		/*
		 * set old values
		 */
		mib->fddiMACOld_Frame_Ct = mib->fddiMACFrame_Ct ;
		mib->fddiMACOld_Copied_Ct = mib->fddiMACCopied_Ct ;
		mib->fddiMACOld_Error_Ct = mib->fddiMACError_Ct ;
		mib->fddiMACOld_Lost_Ct = mib->fddiMACLost_Ct ;
		mib->fddiMACOld_NotCopied_Ct = mib->fddiMACNotCopied_Ct ;

		/*
		 * Check port EBError Condition
		 */
		क्रम (port = 0; port < NUMPHYS; port ++) अणु
			phy = &smc->y[port] ;

			अगर (!phy->mib->fddiPORTHardwarePresent) अणु
				जारी;
			पूर्ण

			cond = (phy->mib->fddiPORTEBError_Ct -
				phy->mib->fddiPORTOldEBError_Ct > 5) ;

			/* If ratio is more than 5 in 8 seconds
			 * Set the condition.
			 */
			smt_srf_event(smc,SMT_COND_PORT_EB_ERROR,
				(पूर्णांक) (INDEX_PORT+ phy->np) ,cond) ;

			/*
			 * set old values
			 */
			phy->mib->fddiPORTOldEBError_Ct =
				phy->mib->fddiPORTEBError_Ct ;
		पूर्ण

#पूर्ण_अगर	/* no SLIM_SMT */
	पूर्ण

#अगर_अघोषित	SLIM_SMT

	अगर (समय - smc->sm.smt_last_notअगरy >= (u_दीर्घ)
		(smc->mib.fddiSMTTT_Notअगरy * TICKS_PER_SECOND) ) अणु
		/*
		 * we can either send an announcement or a request
		 * a request will trigger a reply so that we can update
		 * our dna
		 * note: same tid must be used until reply is received
		 */
		अगर (!smc->sm.pend[SMT_TID_NIF])
			smc->sm.pend[SMT_TID_NIF] = smt_get_tid(smc) ;
		smt_send_nअगर(smc,&fddi_broadcast, FC_SMT_NSA,
			smc->sm.pend[SMT_TID_NIF], SMT_REQUEST,0) ;
		smc->sm.smt_last_notअगरy = समय ;
	पूर्ण

	/*
	 * check समयr
	 */
	अगर (smc->sm.smt_tvu &&
	    समय - smc->sm.smt_tvu > 228*TICKS_PER_SECOND) अणु
		DB_SMT("SMT : UNA expired");
		smc->sm.smt_tvu = 0 ;

		अगर (!is_equal(&smc->mib.m[MAC0].fddiMACUpstreamNbr,
			&SMT_Unknown))अणु
			/* Do not update unknown address */
			smc->mib.m[MAC0].fddiMACOldUpstreamNbr=
				smc->mib.m[MAC0].fddiMACUpstreamNbr ;
		पूर्ण
		smc->mib.m[MAC0].fddiMACUpstreamNbr = SMT_Unknown ;
		smc->mib.m[MAC0].fddiMACUNDA_Flag = FALSE ;
		/*
		 * Make sure the fddiMACUNDA_Flag = FALSE is
		 * included in the SRF so we करोn't generate
		 * a separate SRF क्रम the deनिश्चितion of this
		 * condition
		 */
		update_dac(smc,0) ;
		smt_srf_event(smc, SMT_EVENT_MAC_NEIGHBOR_CHANGE,
			INDEX_MAC,0) ;
	पूर्ण
	अगर (smc->sm.smt_tvd &&
	    समय - smc->sm.smt_tvd > 228*TICKS_PER_SECOND) अणु
		DB_SMT("SMT : DNA expired");
		smc->sm.smt_tvd = 0 ;
		अगर (!is_equal(&smc->mib.m[MAC0].fddiMACDownstreamNbr,
			&SMT_Unknown))अणु
			/* Do not update unknown address */
			smc->mib.m[MAC0].fddiMACOldDownstreamNbr=
				smc->mib.m[MAC0].fddiMACDownstreamNbr ;
		पूर्ण
		smc->mib.m[MAC0].fddiMACDownstreamNbr = SMT_Unknown ;
		smt_srf_event(smc, SMT_EVENT_MAC_NEIGHBOR_CHANGE,
			INDEX_MAC,0) ;
	पूर्ण

#पूर्ण_अगर	/* no SLIM_SMT */

#अगर_अघोषित SMT_REAL_TOKEN_CT
	/*
	 * Token counter emulation section. If hardware supports the token
	 * count, the token counter will be updated in mac_update_counter.
	 */
	क्रम (i = MAC0; i < NUMMACS; i++ )अणु
		अगर (समय - smc->sm.last_tok_समय[i] > 2*TICKS_PER_SECOND )अणु
			smt_emulate_token_ct( smc, i );
		पूर्ण
	पूर्ण
#पूर्ण_अगर

	smt_समयr_start(smc,&smc->sm.smt_समयr, (u_दीर्घ)1000000L,
		EV_TOKEN(EVENT_SMT,SM_TIMER)) ;
पूर्ण

अटल पूर्णांक भाग_ratio(u_दीर्घ upper, u_दीर्घ lower)
अणु
	अगर ((upper<<16L) < upper)
		upper = 0xffff0000L ;
	अन्यथा
		upper <<= 16L ;
	अगर (!lower)
		वापस 0;
	वापस (पूर्णांक)(upper/lower) ;
पूर्ण

#अगर_अघोषित	SLIM_SMT

/*
 * receive packet handler
 */
व्योम smt_received_pack(काष्ठा s_smc *smc, SMbuf *mb, पूर्णांक fs)
/* पूर्णांक fs;  frame status */
अणु
	काष्ठा smt_header	*sm ;
	पूर्णांक			local ;

	पूर्णांक			illegal = 0 ;

	चयन (m_fc(mb)) अणु
	हाल FC_SMT_INFO :
	हाल FC_SMT_LAN_LOC :
	हाल FC_SMT_LOC :
	हाल FC_SMT_NSA :
		अवरोध ;
	शेष :
		smt_मुक्त_mbuf(smc,mb) ;
		वापस ;
	पूर्ण

	smc->mib.m[MAC0].fddiMACSMTCopied_Ct++ ;
	sm = smtod(mb,काष्ठा smt_header *) ;
	local = ((fs & L_INDICATOR) != 0) ;
	hwm_conv_can(smc,(अक्षर *)sm,12) ;

	/* check destination address */
	अगर (is_inभागidual(&sm->smt_dest) && !is_my_addr(smc,&sm->smt_dest)) अणु
		smt_मुक्त_mbuf(smc,mb) ;
		वापस ;
	पूर्ण
#अगर	0		/* क्रम DUP recognition, करो NOT filter them */
	/* ignore loop back packets */
	अगर (is_my_addr(smc,&sm->smt_source) && !local) अणु
		smt_मुक्त_mbuf(smc,mb) ;
		वापस ;
	पूर्ण
#पूर्ण_अगर

	smt_swap_para(sm,(पूर्णांक) mb->sm_len,1) ;
	DB_SMT("SMT : received packet [%s] at 0x%p",
	       smt_type_name[m_fc(mb) & 0xf], sm);
	DB_SMT("SMT : version %d, class %s",
	       sm->smt_version,
	       smt_class_name[sm->smt_class > LAST_CLASS ? 0 : sm->smt_class]);

#अगर_घोषित	SBA
	/*
	 * check अगर NSA frame
	 */
	अगर (m_fc(mb) == FC_SMT_NSA && sm->smt_class == SMT_NIF &&
		(sm->smt_type == SMT_ANNOUNCE || sm->smt_type == SMT_REQUEST)) अणु
			smc->sba.sm = sm ;
			sba(smc,NIF) ;
	पूर्ण
#पूर्ण_अगर

	/*
	 * ignore any packet with NSA and A-indicator set
	 */
	अगर ( (fs & A_INDICATOR) && m_fc(mb) == FC_SMT_NSA) अणु
		DB_SMT("SMT : ignoring NSA with A-indicator set from %pM",
		       &sm->smt_source);
		smt_मुक्त_mbuf(smc,mb) ;
		वापस ;
	पूर्ण

	/*
	 * ignore frames with illegal length
	 */
	अगर (((sm->smt_class == SMT_ECF) && (sm->smt_len > SMT_MAX_ECHO_LEN)) ||
	    ((sm->smt_class != SMT_ECF) && (sm->smt_len > SMT_MAX_INFO_LEN))) अणु
		smt_मुक्त_mbuf(smc,mb) ;
		वापस ;
	पूर्ण

	/*
	 * check SMT version
	 */
	चयन (sm->smt_class) अणु
	हाल SMT_NIF :
	हाल SMT_SIF_CONFIG :
	हाल SMT_SIF_OPER :
	हाल SMT_ECF :
		अगर (sm->smt_version != SMT_VID)
			illegal = 1;
		अवरोध ;
	शेष :
		अगर (sm->smt_version != SMT_VID_2)
			illegal = 1;
		अवरोध ;
	पूर्ण
	अगर (illegal) अणु
		DB_SMT("SMT : version = %d, dest = %pM",
		       sm->smt_version, &sm->smt_source);
		smt_send_rdf(smc,mb,m_fc(mb),SMT_RDF_VERSION,local) ;
		smt_मुक्त_mbuf(smc,mb) ;
		वापस ;
	पूर्ण
	अगर ((sm->smt_len > mb->sm_len - माप(काष्ठा smt_header)) ||
	    ((sm->smt_len & 3) && (sm->smt_class != SMT_ECF))) अणु
		DB_SMT("SMT: info length error, len = %d", sm->smt_len);
		smt_send_rdf(smc,mb,m_fc(mb),SMT_RDF_LENGTH,local) ;
		smt_मुक्त_mbuf(smc,mb) ;
		वापस ;
	पूर्ण
	चयन (sm->smt_class) अणु
	हाल SMT_NIF :
		अगर (smt_check_para(smc,sm,plist_nअगर)) अणु
			DB_SMT("SMT: NIF with para problem, ignoring");
			अवरोध ;
		पूर्ण
		चयन (sm->smt_type) अणु
		हाल SMT_ANNOUNCE :
		हाल SMT_REQUEST :
			अगर (!(fs & C_INDICATOR) && m_fc(mb) == FC_SMT_NSA
				&& is_broadcast(&sm->smt_dest)) अणु
				काष्ठा smt_p_state	*st ;

				/* set my UNA */
				अगर (!is_equal(
					&smc->mib.m[MAC0].fddiMACUpstreamNbr,
					&sm->smt_source)) अणु
					DB_SMT("SMT : updated my UNA = %pM",
					       &sm->smt_source);
					अगर (!is_equal(&smc->mib.m[MAC0].
					    fddiMACUpstreamNbr,&SMT_Unknown))अणु
					 /* Do not update unknown address */
					 smc->mib.m[MAC0].fddiMACOldUpstreamNbr=
					 smc->mib.m[MAC0].fddiMACUpstreamNbr ;
					पूर्ण

					smc->mib.m[MAC0].fddiMACUpstreamNbr =
						sm->smt_source ;
					smt_srf_event(smc,
						SMT_EVENT_MAC_NEIGHBOR_CHANGE,
						INDEX_MAC,0) ;
					smt_echo_test(smc,0) ;
				पूर्ण
				smc->sm.smt_tvu = smt_get_समय() ;
				st = (काष्ठा smt_p_state *)
					sm_to_para(smc,sm,SMT_P_STATE) ;
				अगर (st) अणु
					smc->mib.m[MAC0].fddiMACUNDA_Flag =
					(st->st_dupl_addr & SMT_ST_MY_DUPA) ?
					TRUE : FALSE ;
					update_dac(smc,1) ;
				पूर्ण
			पूर्ण
			अगर ((sm->smt_type == SMT_REQUEST) &&
			    is_inभागidual(&sm->smt_source) &&
			    ((!(fs & A_INDICATOR) && m_fc(mb) == FC_SMT_NSA) ||
			     (m_fc(mb) != FC_SMT_NSA))) अणु
				DB_SMT("SMT : replying to NIF request %pM",
				       &sm->smt_source);
				smt_send_nअगर(smc,&sm->smt_source,
					FC_SMT_INFO,
					sm->smt_tid,
					SMT_REPLY,local) ;
			पूर्ण
			अवरोध ;
		हाल SMT_REPLY :
			DB_SMT("SMT : received NIF response from %pM",
			       &sm->smt_source);
			अगर (fs & A_INDICATOR) अणु
				smc->sm.pend[SMT_TID_NIF] = 0 ;
				DB_SMT("SMT : duplicate address");
				smc->mib.m[MAC0].fddiMACDupAddressTest =
					DA_FAILED ;
				smc->r.dup_addr_test = DA_FAILED ;
				queue_event(smc,EVENT_RMT,RM_DUP_ADDR) ;
				smc->mib.m[MAC0].fddiMACDA_Flag = TRUE ;
				update_dac(smc,1) ;
				अवरोध ;
			पूर्ण
			अगर (sm->smt_tid == smc->sm.pend[SMT_TID_NIF]) अणु
				smc->sm.pend[SMT_TID_NIF] = 0 ;
				/* set my DNA */
				अगर (!is_equal(
					&smc->mib.m[MAC0].fddiMACDownstreamNbr,
					&sm->smt_source)) अणु
					DB_SMT("SMT : updated my DNA");
					अगर (!is_equal(&smc->mib.m[MAC0].
					 fddiMACDownstreamNbr, &SMT_Unknown))अणु
					 /* Do not update unknown address */
				smc->mib.m[MAC0].fddiMACOldDownstreamNbr =
					 smc->mib.m[MAC0].fddiMACDownstreamNbr ;
					पूर्ण

					smc->mib.m[MAC0].fddiMACDownstreamNbr =
						sm->smt_source ;
					smt_srf_event(smc,
						SMT_EVENT_MAC_NEIGHBOR_CHANGE,
						INDEX_MAC,0) ;
					smt_echo_test(smc,1) ;
				पूर्ण
				smc->mib.m[MAC0].fddiMACDA_Flag = FALSE ;
				update_dac(smc,1) ;
				smc->sm.smt_tvd = smt_get_समय() ;
				smc->mib.m[MAC0].fddiMACDupAddressTest =
					DA_PASSED ;
				अगर (smc->r.dup_addr_test != DA_PASSED) अणु
					smc->r.dup_addr_test = DA_PASSED ;
					queue_event(smc,EVENT_RMT,RM_DUP_ADDR) ;
				पूर्ण
			पूर्ण
			अन्यथा अगर (sm->smt_tid ==
				smc->sm.pend[SMT_TID_NIF_TEST]) अणु
				DB_SMT("SMT : NIF test TID ok");
			पूर्ण
			अन्यथा अणु
				DB_SMT("SMT : expected TID %lx, got %x",
				       smc->sm.pend[SMT_TID_NIF], sm->smt_tid);
			पूर्ण
			अवरोध ;
		शेष :
			illegal = 2 ;
			अवरोध ;
		पूर्ण
		अवरोध ;
	हाल SMT_SIF_CONFIG :	/* station inक्रमmation */
		अगर (sm->smt_type != SMT_REQUEST)
			अवरोध ;
		DB_SMT("SMT : replying to SIF Config request from %pM",
		       &sm->smt_source);
		smt_send_sअगर_config(smc,&sm->smt_source,sm->smt_tid,local) ;
		अवरोध ;
	हाल SMT_SIF_OPER :	/* station inक्रमmation */
		अगर (sm->smt_type != SMT_REQUEST)
			अवरोध ;
		DB_SMT("SMT : replying to SIF Operation request from %pM",
		       &sm->smt_source);
		smt_send_sअगर_operation(smc,&sm->smt_source,sm->smt_tid,local) ;
		अवरोध ;
	हाल SMT_ECF :		/* echo frame */
		चयन (sm->smt_type) अणु
		हाल SMT_REPLY :
			smc->mib.priv.fddiPRIVECF_Reply_Rx++ ;
			DB_SMT("SMT: received ECF reply from %pM",
			       &sm->smt_source);
			अगर (sm_to_para(smc,sm,SMT_P_ECHODATA) == शून्य) अणु
				DB_SMT("SMT: ECHODATA missing");
				अवरोध ;
			पूर्ण
			अगर (sm->smt_tid == smc->sm.pend[SMT_TID_ECF]) अणु
				DB_SMT("SMT : ECF test TID ok");
			पूर्ण
			अन्यथा अगर (sm->smt_tid == smc->sm.pend[SMT_TID_ECF_UNA]) अणु
				DB_SMT("SMT : ECF test UNA ok");
			पूर्ण
			अन्यथा अगर (sm->smt_tid == smc->sm.pend[SMT_TID_ECF_DNA]) अणु
				DB_SMT("SMT : ECF test DNA ok");
			पूर्ण
			अन्यथा अणु
				DB_SMT("SMT : expected TID %lx, got %x",
				       smc->sm.pend[SMT_TID_ECF],
				       sm->smt_tid);
			पूर्ण
			अवरोध ;
		हाल SMT_REQUEST :
			smc->mib.priv.fddiPRIVECF_Req_Rx++ ;
			अणु
			अगर (sm->smt_len && !sm_to_para(smc,sm,SMT_P_ECHODATA)) अणु
				DB_SMT("SMT: ECF with para problem,sending RDF");
				smt_send_rdf(smc,mb,m_fc(mb),SMT_RDF_LENGTH,
					local) ;
				अवरोध ;
			पूर्ण
			DB_SMT("SMT - sending ECF reply to %pM",
			       &sm->smt_source);

			/* set destination addr.  & reply */
			sm->smt_dest = sm->smt_source ;
			sm->smt_type = SMT_REPLY ;
			dump_smt(smc,sm,"ECF REPLY") ;
			smc->mib.priv.fddiPRIVECF_Reply_Tx++ ;
			smt_send_frame(smc,mb,FC_SMT_INFO,local) ;
			वापस ;		/* DON'T मुक्त mbuf */
			पूर्ण
		शेष :
			illegal = 1 ;
			अवरोध ;
		पूर्ण
		अवरोध ;
#अगर_अघोषित	BOOT
	हाल SMT_RAF :		/* resource allocation */
#अगर_घोषित	ESS
		DB_ESSN(2, "ESS: RAF frame received");
		fs = ess_raf_received_pack(smc,mb,sm,fs) ;
#पूर्ण_अगर

#अगर_घोषित	SBA
		DB_SBAN(2,"SBA: RAF frame received\n",0,0) ;
		sba_raf_received_pack(smc,sm,fs) ;
#पूर्ण_अगर
		अवरोध ;
	हाल SMT_RDF :		/* request denied */
		smc->mib.priv.fddiPRIVRDF_Rx++ ;
		अवरोध ;
	हाल SMT_ESF :		/* extended service - not supported */
		अगर (sm->smt_type == SMT_REQUEST) अणु
			DB_SMT("SMT - received ESF, sending RDF");
			smt_send_rdf(smc,mb,m_fc(mb),SMT_RDF_CLASS,local) ;
		पूर्ण
		अवरोध ;
	हाल SMT_PMF_GET :
	हाल SMT_PMF_SET :
		अगर (sm->smt_type != SMT_REQUEST)
			अवरोध ;
		/* update statistics */
		अगर (sm->smt_class == SMT_PMF_GET)
			smc->mib.priv.fddiPRIVPMF_Get_Rx++ ;
		अन्यथा
			smc->mib.priv.fddiPRIVPMF_Set_Rx++ ;
		/*
		 * ignore PMF SET with I/G set
		 */
		अगर ((sm->smt_class == SMT_PMF_SET) &&
			!is_inभागidual(&sm->smt_dest)) अणु
			DB_SMT("SMT: ignoring PMF-SET with I/G set");
			अवरोध ;
		पूर्ण
		smt_pmf_received_pack(smc,mb, local) ;
		अवरोध ;
	हाल SMT_SRF :
		dump_smt(smc,sm,"SRF received") ;
		अवरोध ;
	शेष :
		अगर (sm->smt_type != SMT_REQUEST)
			अवरोध ;
		/*
		 * For frames with unknown class:
		 * we need to send a RDF frame according to 8.1.3.1.1,
		 * only अगर it is a REQUEST.
		 */
		DB_SMT("SMT : class = %d, send RDF to %pM",
		       sm->smt_class, &sm->smt_source);

		smt_send_rdf(smc,mb,m_fc(mb),SMT_RDF_CLASS,local) ;
		अवरोध ;
#पूर्ण_अगर
	पूर्ण
	अगर (illegal) अणु
		DB_SMT("SMT: discarding invalid frame, reason = %d", illegal);
	पूर्ण
	smt_मुक्त_mbuf(smc,mb) ;
पूर्ण

अटल व्योम update_dac(काष्ठा s_smc *smc, पूर्णांक report)
अणु
	पूर्णांक	cond ;

	cond = ( smc->mib.m[MAC0].fddiMACUNDA_Flag |
		smc->mib.m[MAC0].fddiMACDA_Flag) != 0 ;
	अगर (report && (cond != smc->mib.m[MAC0].fddiMACDuplicateAddressCond))
		smt_srf_event(smc, SMT_COND_MAC_DUP_ADDR,INDEX_MAC,cond) ;
	अन्यथा
		smc->mib.m[MAC0].fddiMACDuplicateAddressCond = cond ;
पूर्ण

/*
 * send SMT frame
 *	set source address
 *	set station ID
 *	send frame
 */
व्योम smt_send_frame(काष्ठा s_smc *smc, SMbuf *mb, पूर्णांक fc, पूर्णांक local)
/* SMbuf *mb;	buffer to send */
/* पूर्णांक fc;	FC value */
अणु
	काष्ठा smt_header	*sm ;

	अगर (!smc->r.sm_ma_avail && !local) अणु
		smt_मुक्त_mbuf(smc,mb) ;
		वापस ;
	पूर्ण
	sm = smtod(mb,काष्ठा smt_header *) ;
	sm->smt_source = smc->mib.m[MAC0].fddiMACSMTAddress ;
	sm->smt_sid = smc->mib.fddiSMTStationId ;

	smt_swap_para(sm,(पूर्णांक) mb->sm_len,0) ;		/* swap para & header */
	hwm_conv_can(smc,(अक्षर *)sm,12) ;		/* convert SA and DA */
	smc->mib.m[MAC0].fddiMACSMTTransmit_Ct++ ;
	smt_send_mbuf(smc,mb,local ? FC_SMT_LOC : fc) ;
पूर्ण

/*
 * generate and send RDF
 */
अटल व्योम smt_send_rdf(काष्ठा s_smc *smc, SMbuf *rej, पूर्णांक fc, पूर्णांक reason,
			 पूर्णांक local)
/* SMbuf *rej;	mbuf of offending frame */
/* पूर्णांक fc;	FC of denied frame */
/* पूर्णांक reason;	reason code */
अणु
	SMbuf	*mb ;
	काष्ठा smt_header	*sm ;	/* header of offending frame */
	काष्ठा smt_rdf	*rdf ;
	पूर्णांक		len ;
	पूर्णांक		frame_len ;

	sm = smtod(rej,काष्ठा smt_header *) ;
	अगर (sm->smt_type != SMT_REQUEST)
		वापस ;

	DB_SMT("SMT: sending RDF to %pM,reason = 0x%x",
	       &sm->smt_source, reason);


	/*
	 * note: get framelength from MAC length, NOT from SMT header
	 * smt header length is included in sm_len
	 */
	frame_len = rej->sm_len ;

	अगर (!(mb=smt_build_frame(smc,SMT_RDF,SMT_REPLY,माप(काष्ठा smt_rdf))))
		वापस ;
	rdf = smtod(mb,काष्ठा smt_rdf *) ;
	rdf->smt.smt_tid = sm->smt_tid ;		/* use TID from sm */
	rdf->smt.smt_dest = sm->smt_source ;		/* set dest = source */

	/* set P12 */
	rdf->reason.para.p_type = SMT_P_REASON ;
	rdf->reason.para.p_len = माप(काष्ठा smt_p_reason) - PARA_LEN ;
	rdf->reason.rdf_reason = reason ;

	/* set P14 */
	rdf->version.para.p_type = SMT_P_VERSION ;
	rdf->version.para.p_len = माप(काष्ठा smt_p_version) - PARA_LEN ;
	rdf->version.v_pad = 0 ;
	rdf->version.v_n = 1 ;
	rdf->version.v_index = 1 ;
	rdf->version.v_version[0] = SMT_VID_2 ;
	rdf->version.v_pad2 = 0 ;

	/* set P13 */
	अगर ((अचिन्हित पूर्णांक) frame_len <= SMT_MAX_INFO_LEN - माप(*rdf) +
		2*माप(काष्ठा smt_header))
		len = frame_len ;
	अन्यथा
		len = SMT_MAX_INFO_LEN - माप(*rdf) +
			2*माप(काष्ठा smt_header) ;
	/* make length multiple of 4 */
	len &= ~3 ;
	rdf->refused.para.p_type = SMT_P_REFUSED ;
	/* length of para is smt_frame + ref_fc */
	rdf->refused.para.p_len = len + 4 ;
	rdf->refused.ref_fc = fc ;

	/* swap it back */
	smt_swap_para(sm,frame_len,0) ;

	स_नकल((अक्षर *) &rdf->refused.ref_header,(अक्षर *) sm,len) ;

	len -= माप(काष्ठा smt_header) ;
	mb->sm_len += len ;
	rdf->smt.smt_len += len ;

	dump_smt(smc,(काष्ठा smt_header *)rdf,"RDF") ;
	smc->mib.priv.fddiPRIVRDF_Tx++ ;
	smt_send_frame(smc,mb,FC_SMT_INFO,local) ;
पूर्ण

/*
 * generate and send NIF
 */
अटल व्योम smt_send_nअगर(काष्ठा s_smc *smc, स्थिर काष्ठा fddi_addr *dest, 
			 पूर्णांक fc, u_दीर्घ tid, पूर्णांक type, पूर्णांक local)
/* काष्ठा fddi_addr *dest;	dest address */
/* पूर्णांक fc;			frame control */
/* u_दीर्घ tid;			transaction id */
/* पूर्णांक type;			frame type */
अणु
	काष्ठा smt_nअगर	*nअगर ;
	SMbuf		*mb ;

	अगर (!(mb = smt_build_frame(smc,SMT_NIF,type,माप(काष्ठा smt_nअगर))))
		वापस ;
	nअगर = smtod(mb, काष्ठा smt_nअगर *) ;
	smt_fill_una(smc,&nअगर->una) ;	/* set UNA */
	smt_fill_sde(smc,&nअगर->sde) ;	/* set station descriptor */
	smt_fill_state(smc,&nअगर->state) ;	/* set state inक्रमmation */
#अगर_घोषित	SMT6_10
	smt_fill_fsc(smc,&nअगर->fsc) ;	/* set frame status cap. */
#पूर्ण_अगर
	nअगर->smt.smt_dest = *dest ;	/* destination address */
	nअगर->smt.smt_tid = tid ;	/* transaction ID */
	dump_smt(smc,(काष्ठा smt_header *)nअगर,"NIF") ;
	smt_send_frame(smc,mb,fc,local) ;
पूर्ण

#अगर_घोषित	DEBUG
/*
 * send NIF request (test purpose)
 */
अटल व्योम smt_send_nअगर_request(काष्ठा s_smc *smc, काष्ठा fddi_addr *dest)
अणु
	smc->sm.pend[SMT_TID_NIF_TEST] = smt_get_tid(smc) ;
	smt_send_nअगर(smc,dest, FC_SMT_INFO, smc->sm.pend[SMT_TID_NIF_TEST],
		SMT_REQUEST,0) ;
पूर्ण

/*
 * send ECF request (test purpose)
 */
अटल व्योम smt_send_ecf_request(काष्ठा s_smc *smc, काष्ठा fddi_addr *dest,
				 पूर्णांक len)
अणु
	smc->sm.pend[SMT_TID_ECF] = smt_get_tid(smc) ;
	smt_send_ecf(smc,dest, FC_SMT_INFO, smc->sm.pend[SMT_TID_ECF],
		SMT_REQUEST,len) ;
पूर्ण
#पूर्ण_अगर

/*
 * echo test
 */
अटल व्योम smt_echo_test(काष्ठा s_smc *smc, पूर्णांक dna)
अणु
	u_दीर्घ	tid ;

	smc->sm.pend[dna ? SMT_TID_ECF_DNA : SMT_TID_ECF_UNA] =
		tid = smt_get_tid(smc) ;
	smt_send_ecf(smc, dna ?
		&smc->mib.m[MAC0].fddiMACDownstreamNbr :
		&smc->mib.m[MAC0].fddiMACUpstreamNbr,
		FC_SMT_INFO,tid, SMT_REQUEST, (SMT_TEST_ECHO_LEN & ~3)-8) ;
पूर्ण

/*
 * generate and send ECF
 */
अटल व्योम smt_send_ecf(काष्ठा s_smc *smc, काष्ठा fddi_addr *dest, पूर्णांक fc,
			 u_दीर्घ tid, पूर्णांक type, पूर्णांक len)
/* काष्ठा fddi_addr *dest;	dest address */
/* पूर्णांक fc;			frame control */
/* u_दीर्घ tid;			transaction id */
/* पूर्णांक type;			frame type */
/* पूर्णांक len;			frame length */
अणु
	काष्ठा smt_ecf	*ecf ;
	SMbuf		*mb ;

	अगर (!(mb = smt_build_frame(smc,SMT_ECF,type,SMT_ECF_LEN + len)))
		वापस ;
	ecf = smtod(mb, काष्ठा smt_ecf *) ;

	smt_fill_echo(smc,&ecf->ec_echo,tid,len) ;	/* set ECHO */
	ecf->smt.smt_dest = *dest ;	/* destination address */
	ecf->smt.smt_tid = tid ;	/* transaction ID */
	smc->mib.priv.fddiPRIVECF_Req_Tx++ ;
	smt_send_frame(smc,mb,fc,0) ;
पूर्ण

/*
 * generate and send SIF config response
 */

अटल व्योम smt_send_sअगर_config(काष्ठा s_smc *smc, काष्ठा fddi_addr *dest,
				u_दीर्घ tid, पूर्णांक local)
/* काष्ठा fddi_addr *dest;	dest address */
/* u_दीर्घ tid;			transaction id */
अणु
	काष्ठा smt_sअगर_config	*sअगर ;
	SMbuf			*mb ;
	पूर्णांक			len ;
	अगर (!(mb = smt_build_frame(smc,SMT_SIF_CONFIG,SMT_REPLY,
		SIZखातापूर्ण_SMT_SIF_CONFIG)))
		वापस ;

	sअगर = smtod(mb, काष्ठा smt_sअगर_config *) ;
	smt_fill_बारtamp(smc,&sअगर->ts) ;	/* set समय stamp */
	smt_fill_sde(smc,&sअगर->sde) ;		/* set station descriptor */
	smt_fill_version(smc,&sअगर->version) ;	/* set version inक्रमmation */
	smt_fill_state(smc,&sअगर->state) ;	/* set state inक्रमmation */
	smt_fill_policy(smc,&sअगर->policy) ;	/* set station policy */
	smt_fill_latency(smc,&sअगर->latency);	/* set station latency */
	smt_fill_neighbor(smc,&sअगर->neighbor);	/* set station neighbor */
	smt_fill_setcount(smc,&sअगर->setcount) ;	/* set count */
	len = smt_fill_path(smc,&sअगर->path);	/* set station path descriptor*/
	sअगर->smt.smt_dest = *dest ;		/* destination address */
	sअगर->smt.smt_tid = tid ;		/* transaction ID */
	smt_add_frame_len(mb,len) ;		/* adjust length fields */
	dump_smt(smc,(काष्ठा smt_header *)sअगर,"SIF Configuration Reply") ;
	smt_send_frame(smc,mb,FC_SMT_INFO,local) ;
पूर्ण

/*
 * generate and send SIF operation response
 */

अटल व्योम smt_send_sअगर_operation(काष्ठा s_smc *smc, काष्ठा fddi_addr *dest,
				   u_दीर्घ tid, पूर्णांक local)
/* काष्ठा fddi_addr *dest;	dest address */
/* u_दीर्घ tid;			transaction id */
अणु
	काष्ठा smt_sअगर_operation *sअगर ;
	SMbuf			*mb ;
	पूर्णांक			ports ;
	पूर्णांक			i ;

	ports = NUMPHYS ;
#अगर_अघोषित	CONCENTRATOR
	अगर (smc->s.sas == SMT_SAS)
		ports = 1 ;
#पूर्ण_अगर

	अगर (!(mb = smt_build_frame(smc,SMT_SIF_OPER,SMT_REPLY,
				   काष्ठा_size(sअगर, lem, ports))))
		वापस ;
	sअगर = smtod(mb, typeof(sअगर));
	smt_fill_बारtamp(smc,&sअगर->ts) ;	/* set समय stamp */
	smt_fill_mac_status(smc,&sअगर->status) ; /* set mac status */
	smt_fill_mac_counter(smc,&sअगर->mc) ; /* set mac counter field */
	smt_fill_mac_fnc(smc,&sअगर->fnc) ; /* set frame not copied counter */
	smt_fill_manufacturer(smc,&sअगर->man) ; /* set manufacturer field */
	smt_fill_user(smc,&sअगर->user) ;		/* set user field */
	smt_fill_setcount(smc,&sअगर->setcount) ;	/* set count */
	/*
	 * set link error mon inक्रमmation
	 */
	अगर (ports == 1) अणु
		smt_fill_lem(smc,sअगर->lem,PS) ;
	पूर्ण
	अन्यथा अणु
		क्रम (i = 0 ; i < ports ; i++) अणु
			smt_fill_lem(smc,&sअगर->lem[i],i) ;
		पूर्ण
	पूर्ण

	sअगर->smt.smt_dest = *dest ;	/* destination address */
	sअगर->smt.smt_tid = tid ;	/* transaction ID */
	dump_smt(smc,(काष्ठा smt_header *)sअगर,"SIF Operation Reply") ;
	smt_send_frame(smc,mb,FC_SMT_INFO,local) ;
पूर्ण

/*
 * get and initialize SMT frame
 */
SMbuf *smt_build_frame(काष्ठा s_smc *smc, पूर्णांक class, पूर्णांक type,
				  पूर्णांक length)
अणु
	SMbuf			*mb ;
	काष्ठा smt_header	*smt ;

#अगर	0
	अगर (!smc->r.sm_ma_avail) अणु
		वापस 0;
	पूर्ण
#पूर्ण_अगर
	अगर (!(mb = smt_get_mbuf(smc)))
		वापस mb;

	mb->sm_len = length ;
	smt = smtod(mb, काष्ठा smt_header *) ;
	smt->smt_dest = fddi_broadcast ; /* set dest = broadcast */
	smt->smt_class = class ;
	smt->smt_type = type ;
	चयन (class) अणु
	हाल SMT_NIF :
	हाल SMT_SIF_CONFIG :
	हाल SMT_SIF_OPER :
	हाल SMT_ECF :
		smt->smt_version = SMT_VID ;
		अवरोध ;
	शेष :
		smt->smt_version = SMT_VID_2 ;
		अवरोध ;
	पूर्ण
	smt->smt_tid = smt_get_tid(smc) ;	/* set transaction ID */
	smt->smt_pad = 0 ;
	smt->smt_len = length - माप(काष्ठा smt_header) ;
	वापस mb;
पूर्ण

अटल व्योम smt_add_frame_len(SMbuf *mb, पूर्णांक len)
अणु
	काष्ठा smt_header	*smt ;

	smt = smtod(mb, काष्ठा smt_header *) ;
	smt->smt_len += len ;
	mb->sm_len += len ;
पूर्ण



/*
 * fill values in UNA parameter
 */
अटल व्योम smt_fill_una(काष्ठा s_smc *smc, काष्ठा smt_p_una *una)
अणु
	SMTSETPARA(una,SMT_P_UNA) ;
	una->una_pad = 0 ;
	una->una_node = smc->mib.m[MAC0].fddiMACUpstreamNbr ;
पूर्ण

/*
 * fill values in SDE parameter
 */
अटल व्योम smt_fill_sde(काष्ठा s_smc *smc, काष्ठा smt_p_sde *sde)
अणु
	SMTSETPARA(sde,SMT_P_SDE) ;
	sde->sde_non_master = smc->mib.fddiSMTNonMaster_Ct ;
	sde->sde_master = smc->mib.fddiSMTMaster_Ct ;
	sde->sde_mac_count = NUMMACS ;		/* only 1 MAC */
#अगर_घोषित	CONCENTRATOR
	sde->sde_type = SMT_SDE_CONCENTRATOR ;
#अन्यथा
	sde->sde_type = SMT_SDE_STATION ;
#पूर्ण_अगर
पूर्ण

/*
 * fill in values in station state parameter
 */
अटल व्योम smt_fill_state(काष्ठा s_smc *smc, काष्ठा smt_p_state *state)
अणु
	पूर्णांक	top ;
	पूर्णांक	twist ;

	SMTSETPARA(state,SMT_P_STATE) ;
	state->st_pad = 0 ;

	/* determine topology */
	top = 0 ;
	अगर (smc->mib.fddiSMTPeerWrapFlag) अणु
		top |= SMT_ST_WRAPPED ;		/* state wrapped */
	पूर्ण
#अगर_घोषित	CONCENTRATOR
	अगर (cfm_status_unattached(smc)) अणु
		top |= SMT_ST_UNATTACHED ;	/* unattached concentrator */
	पूर्ण
#पूर्ण_अगर
	अगर ((twist = pcm_status_twisted(smc)) & 1) अणु
		top |= SMT_ST_TWISTED_A ;	/* twisted cable */
	पूर्ण
	अगर (twist & 2) अणु
		top |= SMT_ST_TWISTED_B ;	/* twisted cable */
	पूर्ण
#अगर_घोषित	OPT_SRF
	top |= SMT_ST_SRF ;
#पूर्ण_अगर
	अगर (pcm_rooted_station(smc))
		top |= SMT_ST_ROOTED_S ;
	अगर (smc->mib.a[0].fddiPATHSbaPayload != 0)
		top |= SMT_ST_SYNC_SERVICE ;
	state->st_topology = top ;
	state->st_dupl_addr =
		((smc->mib.m[MAC0].fddiMACDA_Flag ? SMT_ST_MY_DUPA : 0 ) |
		 (smc->mib.m[MAC0].fddiMACUNDA_Flag ? SMT_ST_UNA_DUPA : 0)) ;
पूर्ण

/*
 * fill values in बारtamp parameter
 */
अटल व्योम smt_fill_बारtamp(काष्ठा s_smc *smc, काष्ठा smt_p_बारtamp *ts)
अणु

	SMTSETPARA(ts,SMT_P_TIMESTAMP) ;
	smt_set_बारtamp(smc,ts->ts_समय) ;
पूर्ण

व्योम smt_set_बारtamp(काष्ठा s_smc *smc, u_अक्षर *p)
अणु
	u_दीर्घ	समय ;
	u_दीर्घ	uसमय ;

	/*
	 * बारtamp is 64 bits दीर्घ ; resolution is 80 nS
	 * our घड़ी resolution is 10mS
	 * 10mS/80ns = 125000 ~ 2^17 = 131072
	 */
	uसमय = smt_get_समय() ;
	समय = uसमय * 100 ;
	समय /= TICKS_PER_SECOND ;
	p[0] = 0 ;
	p[1] = (u_अक्षर)((समय>>(8+8+8+8-1)) & 1) ;
	p[2] = (u_अक्षर)(समय>>(8+8+8-1)) ;
	p[3] = (u_अक्षर)(समय>>(8+8-1)) ;
	p[4] = (u_अक्षर)(समय>>(8-1)) ;
	p[5] = (u_अक्षर)(समय<<1) ;
	p[6] = (u_अक्षर)(smc->sm.uniq_ticks>>8) ;
	p[7] = (u_अक्षर)smc->sm.uniq_ticks ;
	/*
	 * make sure we करोn't wrap: restart whenever the upper digits change
	 */
	अगर (uसमय != smc->sm.uniq_समय) अणु
		smc->sm.uniq_ticks = 0 ;
	पूर्ण
	smc->sm.uniq_ticks++ ;
	smc->sm.uniq_समय = uसमय ;
पूर्ण

/*
 * fill values in station policy parameter
 */
अटल व्योम smt_fill_policy(काष्ठा s_smc *smc, काष्ठा smt_p_policy *policy)
अणु
	पूर्णांक	i ;
	स्थिर u_अक्षर *map ;
	u_लघु	in ;
	u_लघु	out ;

	/*
	 * MIB para 101b (fddiSMTConnectionPolicy) coding
	 * is dअगरferent from 0005 coding
	 */
	अटल स्थिर u_अक्षर ansi_weirdness[16] = अणु
		0,7,5,3,8,1,6,4,9,10,2,11,12,13,14,15
	पूर्ण ;
	SMTSETPARA(policy,SMT_P_POLICY) ;

	out = 0 ;
	in = smc->mib.fddiSMTConnectionPolicy ;
	क्रम (i = 0, map = ansi_weirdness ; i < 16 ; i++) अणु
		अगर (in & 1)
			out |= (1<<*map) ;
		in >>= 1 ;
		map++ ;
	पूर्ण
	policy->pl_config = smc->mib.fddiSMTConfigPolicy ;
	policy->pl_connect = out ;
पूर्ण

/*
 * fill values in latency equivalent parameter
 */
अटल व्योम smt_fill_latency(काष्ठा s_smc *smc, काष्ठा smt_p_latency *latency)
अणु
	SMTSETPARA(latency,SMT_P_LATENCY) ;

	latency->lt_phyout_idx1 = phy_index(smc,0) ;
	latency->lt_latency1 = 10 ;	/* in octets (byte घड़ी) */
	/*
	 * note: latency has two phy entries by definition
	 * क्रम a SAS, the 2nd one is null
	 */
	अगर (smc->s.sas == SMT_DAS) अणु
		latency->lt_phyout_idx2 = phy_index(smc,1) ;
		latency->lt_latency2 = 10 ;	/* in octets (byte घड़ी) */
	पूर्ण
	अन्यथा अणु
		latency->lt_phyout_idx2 = 0 ;
		latency->lt_latency2 = 0 ;
	पूर्ण
पूर्ण

/*
 * fill values in MAC neighbors parameter
 */
अटल व्योम smt_fill_neighbor(काष्ठा s_smc *smc, काष्ठा smt_p_neighbor *neighbor)
अणु
	SMTSETPARA(neighbor,SMT_P_NEIGHBORS) ;

	neighbor->nb_mib_index = INDEX_MAC ;
	neighbor->nb_mac_index = mac_index(smc,1) ;
	neighbor->nb_una = smc->mib.m[MAC0].fddiMACUpstreamNbr ;
	neighbor->nb_dna = smc->mib.m[MAC0].fddiMACDownstreamNbr ;
पूर्ण

/*
 * fill values in path descriptor
 */
#अगर_घोषित	CONCENTRATOR
#घोषणा ALLPHYS	NUMPHYS
#अन्यथा
#घोषणा ALLPHYS	((smc->s.sas == SMT_SAS) ? 1 : 2)
#पूर्ण_अगर

अटल पूर्णांक smt_fill_path(काष्ठा s_smc *smc, काष्ठा smt_p_path *path)
अणु
	SK_LOC_DECL(पूर्णांक,type) ;
	SK_LOC_DECL(पूर्णांक,state) ;
	SK_LOC_DECL(पूर्णांक,remote) ;
	SK_LOC_DECL(पूर्णांक,mac) ;
	पूर्णांक	len ;
	पूर्णांक	p ;
	पूर्णांक	physp ;
	काष्ठा smt_phy_rec	*phy ;
	काष्ठा smt_mac_rec	*pd_mac ;

	len =	PARA_LEN +
		माप(काष्ठा smt_mac_rec) * NUMMACS +
		माप(काष्ठा smt_phy_rec) * ALLPHYS ;
	path->para.p_type = SMT_P_PATH ;
	path->para.p_len = len - PARA_LEN ;

	/* PHYs */
	क्रम (p = 0,phy = path->pd_phy ; p < ALLPHYS ; p++, phy++) अणु
		physp = p ;
#अगर_अघोषित	CONCENTRATOR
		अगर (smc->s.sas == SMT_SAS)
			physp = PS ;
#पूर्ण_अगर
		pcm_status_state(smc,physp,&type,&state,&remote,&mac) ;
#अगर_घोषित	LITTLE_ENDIAN
		phy->phy_mib_index = smt_swap_लघु((u_लघु)p+INDEX_PORT) ;
#अन्यथा
		phy->phy_mib_index = p+INDEX_PORT ;
#पूर्ण_अगर
		phy->phy_type = type ;
		phy->phy_connect_state = state ;
		phy->phy_remote_type = remote ;
		phy->phy_remote_mac = mac ;
		phy->phy_resource_idx = phy_con_resource_index(smc,p) ;
	पूर्ण

	/* MAC */
	pd_mac = (काष्ठा smt_mac_rec *) phy ;
	pd_mac->mac_addr = smc->mib.m[MAC0].fddiMACSMTAddress ;
	pd_mac->mac_resource_idx = mac_con_resource_index(smc,1) ;
	वापस len;
पूर्ण

/*
 * fill values in mac status
 */
अटल व्योम smt_fill_mac_status(काष्ठा s_smc *smc, काष्ठा smt_p_mac_status *st)
अणु
	SMTSETPARA(st,SMT_P_MAC_STATUS) ;

	st->st_mib_index = INDEX_MAC ;
	st->st_mac_index = mac_index(smc,1) ;

	mac_update_counter(smc) ;
	/*
	 * समयr values are represented in SMT as 2's complement numbers
	 * units :	पूर्णांकernal :  2's complement BCLK
	 */
	st->st_t_req = smc->mib.m[MAC0].fddiMACT_Req ;
	st->st_t_neg = smc->mib.m[MAC0].fddiMACT_Neg ;
	st->st_t_max = smc->mib.m[MAC0].fddiMACT_Max ;
	st->st_tvx_value = smc->mib.m[MAC0].fddiMACTvxValue ;
	st->st_t_min = smc->mib.m[MAC0].fddiMACT_Min ;

	st->st_sba = smc->mib.a[PATH0].fddiPATHSbaPayload ;
	st->st_frame_ct = smc->mib.m[MAC0].fddiMACFrame_Ct ;
	st->st_error_ct = smc->mib.m[MAC0].fddiMACError_Ct ;
	st->st_lost_ct = smc->mib.m[MAC0].fddiMACLost_Ct ;
पूर्ण

/*
 * fill values in LEM status
 */
अटल व्योम smt_fill_lem(काष्ठा s_smc *smc, काष्ठा smt_p_lem *lem, पूर्णांक phy)
अणु
	काष्ठा fddi_mib_p	*mib ;

	mib = smc->y[phy].mib ;

	SMTSETPARA(lem,SMT_P_LEM) ;
	lem->lem_mib_index = phy+INDEX_PORT ;
	lem->lem_phy_index = phy_index(smc,phy) ;
	lem->lem_pad2 = 0 ;
	lem->lem_cutoff = mib->fddiPORTLer_Cutoff ;
	lem->lem_alarm = mib->fddiPORTLer_Alarm ;
	/* दीर्घ term bit error rate */
	lem->lem_estimate = mib->fddiPORTLer_Estimate ;
	/* # of rejected connections */
	lem->lem_reject_ct = mib->fddiPORTLem_Reject_Ct ;
	lem->lem_ct = mib->fddiPORTLem_Ct ;	/* total number of errors */
पूर्ण

/*
 * fill version parameter
 */
अटल व्योम smt_fill_version(काष्ठा s_smc *smc, काष्ठा smt_p_version *vers)
अणु
	SK_UNUSED(smc) ;
	SMTSETPARA(vers,SMT_P_VERSION) ;
	vers->v_pad = 0 ;
	vers->v_n = 1 ;				/* one version is enough .. */
	vers->v_index = 1 ;
	vers->v_version[0] = SMT_VID_2 ;
	vers->v_pad2 = 0 ;
पूर्ण

#अगर_घोषित	SMT6_10
/*
 * fill frame status capabilities
 */
/*
 * note: this para 200B is NOT in swap table, because it's also set in
 * PMF add_para
 */
अटल व्योम smt_fill_fsc(काष्ठा s_smc *smc, काष्ठा smt_p_fsc *fsc)
अणु
	SK_UNUSED(smc) ;
	SMTSETPARA(fsc,SMT_P_FSC) ;
	fsc->fsc_pad0 = 0 ;
	fsc->fsc_mac_index = INDEX_MAC ;	/* this is MIB ; MIB is NOT
						 * mac_index ()i !
						 */
	fsc->fsc_pad1 = 0 ;
	fsc->fsc_value = FSC_TYPE0 ;		/* "normal" node */
#अगर_घोषित	LITTLE_ENDIAN
	fsc->fsc_mac_index = smt_swap_लघु(INDEX_MAC) ;
	fsc->fsc_value = smt_swap_लघु(FSC_TYPE0) ;
#पूर्ण_अगर
पूर्ण
#पूर्ण_अगर

/*
 * fill mac counter field
 */
अटल व्योम smt_fill_mac_counter(काष्ठा s_smc *smc, काष्ठा smt_p_mac_counter *mc)
अणु
	SMTSETPARA(mc,SMT_P_MAC_COUNTER) ;
	mc->mc_mib_index = INDEX_MAC ;
	mc->mc_index = mac_index(smc,1) ;
	mc->mc_receive_ct = smc->mib.m[MAC0].fddiMACCopied_Ct ;
	mc->mc_transmit_ct =  smc->mib.m[MAC0].fddiMACTransmit_Ct ;
पूर्ण

/*
 * fill mac frame not copied counter
 */
अटल व्योम smt_fill_mac_fnc(काष्ठा s_smc *smc, काष्ठा smt_p_mac_fnc *fnc)
अणु
	SMTSETPARA(fnc,SMT_P_MAC_FNC) ;
	fnc->nc_mib_index = INDEX_MAC ;
	fnc->nc_index = mac_index(smc,1) ;
	fnc->nc_counter = smc->mib.m[MAC0].fddiMACNotCopied_Ct ;
पूर्ण


/*
 * fill manufacturer field
 */
अटल व्योम smt_fill_manufacturer(काष्ठा s_smc *smc, 
				  काष्ठा smp_p_manufacturer *man)
अणु
	SMTSETPARA(man,SMT_P_MANUFACTURER) ;
	स_नकल((अक्षर *) man->mf_data,
		(अक्षर *) smc->mib.fddiSMTManufacturerData,
		माप(man->mf_data)) ;
पूर्ण

/*
 * fill user field
 */
अटल व्योम smt_fill_user(काष्ठा s_smc *smc, काष्ठा smp_p_user *user)
अणु
	SMTSETPARA(user,SMT_P_USER) ;
	स_नकल((अक्षर *) user->us_data,
		(अक्षर *) smc->mib.fddiSMTUserData,
		माप(user->us_data)) ;
पूर्ण

/*
 * fill set count
 */
अटल व्योम smt_fill_setcount(काष्ठा s_smc *smc, काष्ठा smt_p_setcount *setcount)
अणु
	SK_UNUSED(smc) ;
	SMTSETPARA(setcount,SMT_P_SETCOUNT) ;
	setcount->count = smc->mib.fddiSMTSetCount.count ;
	स_नकल((अक्षर *)setcount->बारtamp,
		(अक्षर *)smc->mib.fddiSMTSetCount.बारtamp,8) ;
पूर्ण

/*
 * fill echo data
 */
अटल व्योम smt_fill_echo(काष्ठा s_smc *smc, काष्ठा smt_p_echo *echo, u_दीर्घ seed,
			  पूर्णांक len)
अणु
	u_अक्षर	*p ;

	SK_UNUSED(smc) ;
	SMTSETPARA(echo,SMT_P_ECHODATA) ;
	echo->para.p_len = len ;
	क्रम (p = echo->ec_data ; len ; len--) अणु
		*p++ = (u_अक्षर) seed ;
		seed += 13 ;
	पूर्ण
पूर्ण

/*
 * clear DNA and UNA
 * called from CFM अगर configuration changes
 */
अटल व्योम smt_clear_una_dna(काष्ठा s_smc *smc)
अणु
	smc->mib.m[MAC0].fddiMACUpstreamNbr = SMT_Unknown ;
	smc->mib.m[MAC0].fddiMACDownstreamNbr = SMT_Unknown ;
पूर्ण

अटल व्योम smt_clear_old_una_dna(काष्ठा s_smc *smc)
अणु
	smc->mib.m[MAC0].fddiMACOldUpstreamNbr = SMT_Unknown ;
	smc->mib.m[MAC0].fddiMACOldDownstreamNbr = SMT_Unknown ;
पूर्ण

u_दीर्घ smt_get_tid(काष्ठा s_smc *smc)
अणु
	u_दीर्घ	tid ;
	जबतक ((tid = ++(smc->sm.smt_tid) ^ SMT_TID_MAGIC) == 0)
		;
	वापस tid & 0x3fffffffL;
पूर्ण

#अगर_घोषित	LITTLE_ENDIAN
/*
 * table of parameter lengths
 */
अटल स्थिर काष्ठा smt_pdef अणु
	पूर्णांक	ptype ;
	पूर्णांक	plen ;
	स्थिर अक्षर	*pswap ;
पूर्ण smt_pdef[] = अणु
	अणु SMT_P_UNA,	माप(काष्ठा smt_p_una) ,
		SWAP_SMT_P_UNA					पूर्ण ,
	अणु SMT_P_SDE,	माप(काष्ठा smt_p_sde) ,
		SWAP_SMT_P_SDE					पूर्ण ,
	अणु SMT_P_STATE,	माप(काष्ठा smt_p_state) ,
		SWAP_SMT_P_STATE				पूर्ण ,
	अणु SMT_P_TIMESTAMP,माप(काष्ठा smt_p_बारtamp) ,
		SWAP_SMT_P_TIMESTAMP				पूर्ण ,
	अणु SMT_P_POLICY,	माप(काष्ठा smt_p_policy) ,
		SWAP_SMT_P_POLICY				पूर्ण ,
	अणु SMT_P_LATENCY,	माप(काष्ठा smt_p_latency) ,
		SWAP_SMT_P_LATENCY				पूर्ण ,
	अणु SMT_P_NEIGHBORS,माप(काष्ठा smt_p_neighbor) ,
		SWAP_SMT_P_NEIGHBORS				पूर्ण ,
	अणु SMT_P_PATH,	माप(काष्ठा smt_p_path) ,
		SWAP_SMT_P_PATH					पूर्ण ,
	अणु SMT_P_MAC_STATUS,माप(काष्ठा smt_p_mac_status) ,
		SWAP_SMT_P_MAC_STATUS				पूर्ण ,
	अणु SMT_P_LEM,	माप(काष्ठा smt_p_lem) ,
		SWAP_SMT_P_LEM					पूर्ण ,
	अणु SMT_P_MAC_COUNTER,माप(काष्ठा smt_p_mac_counter) ,
		SWAP_SMT_P_MAC_COUNTER				पूर्ण ,
	अणु SMT_P_MAC_FNC,माप(काष्ठा smt_p_mac_fnc) ,
		SWAP_SMT_P_MAC_FNC				पूर्ण ,
	अणु SMT_P_PRIORITY,माप(काष्ठा smt_p_priority) ,
		SWAP_SMT_P_PRIORITY				पूर्ण ,
	अणु SMT_P_EB,माप(काष्ठा smt_p_eb) ,
		SWAP_SMT_P_EB					पूर्ण ,
	अणु SMT_P_MANUFACTURER,माप(काष्ठा smp_p_manufacturer) ,
		SWAP_SMT_P_MANUFACTURER				पूर्ण ,
	अणु SMT_P_REASON,	माप(काष्ठा smt_p_reason) ,
		SWAP_SMT_P_REASON				पूर्ण ,
	अणु SMT_P_REFUSED, माप(काष्ठा smt_p_refused) ,
		SWAP_SMT_P_REFUSED				पूर्ण ,
	अणु SMT_P_VERSION, माप(काष्ठा smt_p_version) ,
		SWAP_SMT_P_VERSION				पूर्ण ,
#अगर_घोषित ESS
	अणु SMT_P0015, माप(काष्ठा smt_p_0015) , SWAP_SMT_P0015 पूर्ण ,
	अणु SMT_P0016, माप(काष्ठा smt_p_0016) , SWAP_SMT_P0016 पूर्ण ,
	अणु SMT_P0017, माप(काष्ठा smt_p_0017) , SWAP_SMT_P0017 पूर्ण ,
	अणु SMT_P0018, माप(काष्ठा smt_p_0018) , SWAP_SMT_P0018 पूर्ण ,
	अणु SMT_P0019, माप(काष्ठा smt_p_0019) , SWAP_SMT_P0019 पूर्ण ,
	अणु SMT_P001A, माप(काष्ठा smt_p_001a) , SWAP_SMT_P001A पूर्ण ,
	अणु SMT_P001B, माप(काष्ठा smt_p_001b) , SWAP_SMT_P001B पूर्ण ,
	अणु SMT_P001C, माप(काष्ठा smt_p_001c) , SWAP_SMT_P001C पूर्ण ,
	अणु SMT_P001D, माप(काष्ठा smt_p_001d) , SWAP_SMT_P001D पूर्ण ,
#पूर्ण_अगर
#अगर	0
	अणु SMT_P_FSC,	माप(काष्ठा smt_p_fsc) ,
		SWAP_SMT_P_FSC					पूर्ण ,
#पूर्ण_अगर

	अणु SMT_P_SETCOUNT,0,	SWAP_SMT_P_SETCOUNT		पूर्ण ,
	अणु SMT_P1048,	0,	SWAP_SMT_P1048			पूर्ण ,
	अणु SMT_P208C,	0,	SWAP_SMT_P208C			पूर्ण ,
	अणु SMT_P208D,	0,	SWAP_SMT_P208D			पूर्ण ,
	अणु SMT_P208E,	0,	SWAP_SMT_P208E			पूर्ण ,
	अणु SMT_P208F,	0,	SWAP_SMT_P208F			पूर्ण ,
	अणु SMT_P2090,	0,	SWAP_SMT_P2090			पूर्ण ,
#अगर_घोषित	ESS
	अणु SMT_P320B, माप(काष्ठा smt_p_320b) , SWAP_SMT_P320B पूर्ण ,
	अणु SMT_P320F, माप(काष्ठा smt_p_320f) , SWAP_SMT_P320F पूर्ण ,
	अणु SMT_P3210, माप(काष्ठा smt_p_3210) , SWAP_SMT_P3210 पूर्ण ,
#पूर्ण_अगर
	अणु SMT_P4050,	0,	SWAP_SMT_P4050			पूर्ण ,
	अणु SMT_P4051,	0,	SWAP_SMT_P4051			पूर्ण ,
	अणु SMT_P4052,	0,	SWAP_SMT_P4052			पूर्ण ,
	अणु SMT_P4053,	0,	SWAP_SMT_P4053			पूर्ण ,
पूर्ण ;

#घोषणा N_SMT_PLEN	ARRAY_SIZE(smt_pdef)
#पूर्ण_अगर

पूर्णांक smt_check_para(काष्ठा s_smc *smc, काष्ठा smt_header	*sm,
		   स्थिर u_लघु list[])
अणु
	स्थिर u_लघु		*p = list ;
	जबतक (*p) अणु
		अगर (!sm_to_para(smc,sm,(पूर्णांक) *p)) अणु
			DB_SMT("SMT: smt_check_para - missing para %hx", *p);
			वापस -1;
		पूर्ण
		p++ ;
	पूर्ण
	वापस 0;
पूर्ण

व्योम *sm_to_para(काष्ठा s_smc *smc, काष्ठा smt_header *sm, पूर्णांक para)
अणु
	अक्षर	*p ;
	पूर्णांक	len ;
	पूर्णांक	plen ;
	व्योम	*found = शून्य;

	SK_UNUSED(smc) ;

	len = sm->smt_len ;
	p = (अक्षर *)(sm+1) ;		/* poपूर्णांकer to info */
	जबतक (len > 0 ) अणु
		अगर (((काष्ठा smt_para *)p)->p_type == para)
			found = (व्योम *) p ;
		plen = ((काष्ठा smt_para *)p)->p_len + PARA_LEN ;
		p += plen ;
		len -= plen ;
		अगर (len < 0) अणु
			DB_SMT("SMT : sm_to_para - length error %d", plen);
			वापस शून्य;
		पूर्ण
		अगर ((plen & 3) && (para != SMT_P_ECHODATA)) अणु
			DB_SMT("SMT : sm_to_para - odd length %d", plen);
			वापस शून्य;
		पूर्ण
		अगर (found)
			वापस found;
	पूर्ण
	वापस शून्य;
पूर्ण

#अगर	0
/*
 * send ANTC data test frame
 */
व्योम fddi_send_antc(काष्ठा s_smc *smc, काष्ठा fddi_addr *dest)
अणु
	SK_UNUSED(smc) ;
	SK_UNUSED(dest) ;
#अगर	0
	SMbuf			*mb ;
	काष्ठा smt_header	*smt ;
	पूर्णांक			i ;
	अक्षर			*p ;

	mb = smt_get_mbuf() ;
	mb->sm_len = 3000+12 ;
	p = smtod(mb, अक्षर *) + 12 ;
	क्रम (i = 0 ; i < 3000 ; i++)
		*p++ = 1 << (i&7) ;

	smt = smtod(mb, काष्ठा smt_header *) ;
	smt->smt_dest = *dest ;
	smt->smt_source = smc->mib.m[MAC0].fddiMACSMTAddress ;
	smt_send_mbuf(smc,mb,FC_ASYNC_LLC) ;
#पूर्ण_अगर
पूर्ण
#पूर्ण_अगर

/*
 * वापस अटल mac index
 */
अटल पूर्णांक mac_index(काष्ठा s_smc *smc, पूर्णांक mac)
अणु
	SK_UNUSED(mac) ;
#अगर_घोषित	CONCENTRATOR
	SK_UNUSED(smc) ;
	वापस NUMPHYS + 1;
#अन्यथा
	वापस (smc->s.sas == SMT_SAS) ? 2 : 3;
#पूर्ण_अगर
पूर्ण

/*
 * वापस अटल phy index
 */
अटल पूर्णांक phy_index(काष्ठा s_smc *smc, पूर्णांक phy)
अणु
	SK_UNUSED(smc) ;
	वापस phy + 1;
पूर्ण

/*
 * वापस dynamic mac connection resource index
 */
अटल पूर्णांक mac_con_resource_index(काष्ठा s_smc *smc, पूर्णांक mac)
अणु
#अगर_घोषित	CONCENTRATOR
	SK_UNUSED(smc) ;
	SK_UNUSED(mac) ;
	वापस entity_to_index(smc, cem_get_करोwnstream(smc, ENTITY_MAC));
#अन्यथा
	SK_UNUSED(mac) ;
	चयन (smc->mib.fddiSMTCF_State) अणु
	हाल SC9_C_WRAP_A :
	हाल SC5_THRU_B :
	हाल SC11_C_WRAP_S :
		वापस 1;
	हाल SC10_C_WRAP_B :
	हाल SC4_THRU_A :
		वापस 2;
	पूर्ण
	वापस smc->s.sas == SMT_SAS ? 2 : 3;
#पूर्ण_अगर
पूर्ण

/*
 * वापस dynamic phy connection resource index
 */
अटल पूर्णांक phy_con_resource_index(काष्ठा s_smc *smc, पूर्णांक phy)
अणु
#अगर_घोषित	CONCENTRATOR
	वापस entity_to_index(smc, cem_get_करोwnstream(smc, ENTITY_PHY(phy))) ;
#अन्यथा
	चयन (smc->mib.fddiSMTCF_State) अणु
	हाल SC9_C_WRAP_A :
		वापस phy == PA ? 3 : 2;
	हाल SC10_C_WRAP_B :
		वापस phy == PA ? 1 : 3;
	हाल SC4_THRU_A :
		वापस phy == PA ? 3 : 1;
	हाल SC5_THRU_B :
		वापस phy == PA ? 2 : 3;
	हाल SC11_C_WRAP_S :
		वापस 2;
	पूर्ण
	वापस phy;
#पूर्ण_अगर
पूर्ण

#अगर_घोषित	CONCENTRATOR
अटल पूर्णांक entity_to_index(काष्ठा s_smc *smc, पूर्णांक e)
अणु
	अगर (e == ENTITY_MAC)
		वापस mac_index(smc, 1);
	अन्यथा
		वापस phy_index(smc, e - ENTITY_PHY(0));
पूर्ण
#पूर्ण_अगर

#अगर_घोषित	LITTLE_ENDIAN
अटल पूर्णांक smt_swap_लघु(u_लघु s)
अणु
	वापस ((s>>8)&0xff) | ((s&0xff)<<8);
पूर्ण

व्योम smt_swap_para(काष्ठा smt_header *sm, पूर्णांक len, पूर्णांक direction)
/* पूर्णांक direction;	0 encode 1 decode */
अणु
	काष्ठा smt_para	*pa ;
	स्थिर  काष्ठा smt_pdef	*pd ;
	अक्षर	*p ;
	पूर्णांक	plen ;
	पूर्णांक	type ;
	पूर्णांक	i ;

/*	म_लिखो("smt_swap_para sm %x len %d dir %d\n",
		sm,len,direction) ;
 */
	smt_string_swap((अक्षर *)sm,SWAP_SMTHEADER,len) ;

	/* swap args */
	len -= माप(काष्ठा smt_header) ;

	p = (अक्षर *) (sm + 1) ;
	जबतक (len > 0) अणु
		pa = (काष्ठा smt_para *) p ;
		plen = pa->p_len ;
		type = pa->p_type ;
		pa->p_type = smt_swap_लघु(pa->p_type) ;
		pa->p_len = smt_swap_लघु(pa->p_len) ;
		अगर (direction) अणु
			plen = pa->p_len ;
			type = pa->p_type ;
		पूर्ण
		/*
		 * note: paras can have 0 length !
		 */
		अगर (plen < 0)
			अवरोध ;
		plen += PARA_LEN ;
		क्रम (i = N_SMT_PLEN, pd = smt_pdef; i ; i--,pd++) अणु
			अगर (pd->ptype == type)
				अवरोध ;
		पूर्ण
		अगर (i && pd->pswap) अणु
			smt_string_swap(p+PARA_LEN,pd->pswap,len) ;
		पूर्ण
		len -= plen ;
		p += plen ;
	पूर्ण
पूर्ण

अटल व्योम smt_string_swap(अक्षर *data, स्थिर अक्षर *क्रमmat, पूर्णांक len)
अणु
	स्थिर अक्षर	*खोलो_paren = शून्य ;
	पूर्णांक	x ;

	जबतक (len > 0  && *क्रमmat) अणु
		चयन (*क्रमmat) अणु
		हाल '[' :
			खोलो_paren = क्रमmat ;
			अवरोध ;
		हाल ']' :
			क्रमmat = खोलो_paren ;
			अवरोध ;
		हाल '1' :
		हाल '2' :
		हाल '3' :
		हाल '4' :
		हाल '5' :
		हाल '6' :
		हाल '7' :
		हाल '8' :
		हाल '9' :
			data  += *क्रमmat - '0' ;
			len   -= *क्रमmat - '0' ;
			अवरोध ;
		हाल 'c':
			data++ ;
			len-- ;
			अवरोध ;
		हाल 's' :
			x = data[0] ;
			data[0] = data[1] ;
			data[1] = x ;
			data += 2 ;
			len -= 2 ;
			अवरोध ;
		हाल 'l' :
			x = data[0] ;
			data[0] = data[3] ;
			data[3] = x ;
			x = data[1] ;
			data[1] = data[2] ;
			data[2] = x ;
			data += 4 ;
			len -= 4 ;
			अवरोध ;
		पूर्ण
		क्रमmat++ ;
	पूर्ण
पूर्ण
#अन्यथा
व्योम smt_swap_para(काष्ठा smt_header *sm, पूर्णांक len, पूर्णांक direction)
/* पूर्णांक direction;	0 encode 1 decode */
अणु
	SK_UNUSED(sm) ;
	SK_UNUSED(len) ;
	SK_UNUSED(direction) ;
पूर्ण
#पूर्ण_अगर

/*
 * PMF actions
 */
पूर्णांक smt_action(काष्ठा s_smc *smc, पूर्णांक class, पूर्णांक code, पूर्णांक index)
अणु
	पूर्णांक	event ;
	पूर्णांक	port ;
	DB_SMT("SMT: action %d code %d", class, code);
	चयन(class) अणु
	हाल SMT_STATION_ACTION :
		चयन(code) अणु
		हाल SMT_STATION_ACTION_CONNECT :
			smc->mib.fddiSMTRemoteDisconnectFlag = FALSE ;
			queue_event(smc,EVENT_ECM,EC_CONNECT) ;
			अवरोध ;
		हाल SMT_STATION_ACTION_DISCONNECT :
			queue_event(smc,EVENT_ECM,EC_DISCONNECT) ;
			smc->mib.fddiSMTRemoteDisconnectFlag = TRUE ;
			RS_SET(smc,RS_DISCONNECT) ;
			AIX_EVENT(smc, (u_दीर्घ) FDDI_RING_STATUS, (u_दीर्घ)
				FDDI_SMT_EVENT, (u_दीर्घ) FDDI_REMOTE_DISCONNECT,
				smt_get_event_word(smc));
			अवरोध ;
		हाल SMT_STATION_ACTION_PATHTEST :
			AIX_EVENT(smc, (u_दीर्घ) FDDI_RING_STATUS, (u_दीर्घ)
				FDDI_SMT_EVENT, (u_दीर्घ) FDDI_PATH_TEST,
				smt_get_event_word(smc));
			अवरोध ;
		हाल SMT_STATION_ACTION_SELFTEST :
			AIX_EVENT(smc, (u_दीर्घ) FDDI_RING_STATUS, (u_दीर्घ)
				FDDI_SMT_EVENT, (u_दीर्घ) FDDI_REMOTE_SELF_TEST,
				smt_get_event_word(smc));
			अवरोध ;
		हाल SMT_STATION_ACTION_DISABLE_A :
			अगर (smc->y[PA].pc_mode == PM_PEER) अणु
				RS_SET(smc,RS_EVENT) ;
				queue_event(smc,EVENT_PCM+PA,PC_DISABLE) ;
			पूर्ण
			अवरोध ;
		हाल SMT_STATION_ACTION_DISABLE_B :
			अगर (smc->y[PB].pc_mode == PM_PEER) अणु
				RS_SET(smc,RS_EVENT) ;
				queue_event(smc,EVENT_PCM+PB,PC_DISABLE) ;
			पूर्ण
			अवरोध ;
		हाल SMT_STATION_ACTION_DISABLE_M :
			क्रम (port = 0 ; port <  NUMPHYS ; port++) अणु
				अगर (smc->mib.p[port].fddiPORTMy_Type != TM)
					जारी ;
				RS_SET(smc,RS_EVENT) ;
				queue_event(smc,EVENT_PCM+port,PC_DISABLE) ;
			पूर्ण
			अवरोध ;
		शेष :
			वापस 1;
		पूर्ण
		अवरोध ;
	हाल SMT_PORT_ACTION :
		चयन(code) अणु
		हाल SMT_PORT_ACTION_ENABLE :
			event = PC_ENABLE ;
			अवरोध ;
		हाल SMT_PORT_ACTION_DISABLE :
			event = PC_DISABLE ;
			अवरोध ;
		हाल SMT_PORT_ACTION_MAINT :
			event = PC_MAINT ;
			अवरोध ;
		हाल SMT_PORT_ACTION_START :
			event = PC_START ;
			अवरोध ;
		हाल SMT_PORT_ACTION_STOP :
			event = PC_STOP ;
			अवरोध ;
		शेष :
			वापस 1;
		पूर्ण
		queue_event(smc,EVENT_PCM+index,event) ;
		अवरोध ;
	शेष :
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * canonical conversion of <len> bytes beginning क्रमm *data
 */
#अगर_घोषित  USE_CAN_ADDR
अटल व्योम hwm_conv_can(काष्ठा s_smc *smc, अक्षर *data, पूर्णांक len)
अणु
	पूर्णांक i ;

	SK_UNUSED(smc) ;

	क्रम (i = len; i ; i--, data++)
		*data = bitrev8(*data);
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर	/* no SLIM_SMT */

