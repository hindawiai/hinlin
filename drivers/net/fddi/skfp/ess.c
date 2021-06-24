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
 * *******************************************************************
 * This SBA code implements the Synchronous Bandwidth Allocation
 * functions described in the "FDDI Synchronous Forum Implementer's
 * Agreement" dated December 1th, 1993.
 * *******************************************************************
 *
 *	PURPOSE: The purpose of this function is to control
 *		 synchronous allocations on a single FDDI segment.
 *		 Allocations are limited to the primary FDDI ring.
 *		 The SBM provides recovery mechanisms to recover
 *		 unused bandwidth also resolves T_Neg and
 *		 reconfiguration changes. Many of the SBM state
 *		 machine inमाला_दो are sourced by the underlying
 *		 FDDI sub-प्रणाली supporting the SBA application.
 *
 * *******************************************************************
 */

#समावेश "h/types.h"
#समावेश "h/fddi.h"
#समावेश "h/smc.h"
#समावेश "h/smt_p.h"


#अगर_अघोषित	SLIM_SMT

#अगर_घोषित ESS

#अगर_अघोषित lपूर्णांक
#घोषणा LINT_USE(x)
#अन्यथा
#घोषणा LINT_USE(x)	(x)=(x)
#पूर्ण_अगर
#घोषणा MS2BCLK(x)	((x)*12500L)

/*
	-------------------------------------------------------------
	LOCAL VARIABLES:
	-------------------------------------------------------------
*/

अटल स्थिर u_लघु plist_raf_alc_res[] = अणु SMT_P0012, SMT_P320B, SMT_P320F,
					SMT_P3210, SMT_P0019, SMT_P001A,
					SMT_P001D, 0 पूर्ण ;

अटल स्थिर u_लघु plist_raf_chg_req[] = अणु SMT_P320B, SMT_P320F, SMT_P3210,
					SMT_P001A, 0 पूर्ण ;

अटल स्थिर काष्ठा fddi_addr smt_sba_da = अणुअणु0x80,0x01,0x43,0x00,0x80,0x0Cपूर्णपूर्ण ;
अटल स्थिर काष्ठा fddi_addr null_addr = अणुअणु0,0,0,0,0,0पूर्णपूर्ण ;

/*
	-------------------------------------------------------------
	GLOBAL VARIABLES:
	-------------------------------------------------------------
*/


/*
	-------------------------------------------------------------
	LOCAL FUNCTIONS:
	-------------------------------------------------------------
*/

अटल व्योम ess_send_response(काष्ठा s_smc *smc, काष्ठा smt_header *sm,
			      पूर्णांक sba_cmd);
अटल व्योम ess_config_fअगरo(काष्ठा s_smc *smc);
अटल व्योम ess_send_alc_req(काष्ठा s_smc *smc);
अटल व्योम ess_send_frame(काष्ठा s_smc *smc, SMbuf *mb);

/*
	-------------------------------------------------------------
	EXTERNAL FUNCTIONS:
	-------------------------------------------------------------
*/

/*
	-------------------------------------------------------------
	PUBLIC FUNCTIONS:
	-------------------------------------------------------------
*/

व्योम ess_समयr_poll(काष्ठा s_smc *smc);
व्योम ess_para_change(काष्ठा s_smc *smc);
पूर्णांक ess_raf_received_pack(काष्ठा s_smc *smc, SMbuf *mb, काष्ठा smt_header *sm,
			  पूर्णांक fs);
अटल पूर्णांक process_bw_alloc(काष्ठा s_smc *smc, दीर्घ पूर्णांक payload, दीर्घ पूर्णांक overhead);


/*
 * --------------------------------------------------------------------------
 *	End Station Support	(ESS)
 * --------------------------------------------------------------------------
 */

/*
 * evaluate the RAF frame
 */
पूर्णांक ess_raf_received_pack(काष्ठा s_smc *smc, SMbuf *mb, काष्ठा smt_header *sm,
			  पूर्णांक fs)
अणु
	व्योम			*p ;		/* universal poपूर्णांकer */
	काष्ठा smt_p_0016	*cmd ;		/* para: command क्रम the ESS */
	SMbuf			*db ;
	u_दीर्घ			msg_res_type ;	/* recource type */
	u_दीर्घ			payload, overhead ;
	पूर्णांक			local ;
	पूर्णांक			i ;

	/*
	 * Message Processing Code
	 */
	 local = ((fs & L_INDICATOR) != 0) ;

	/*
	 * get the resource type
	 */
	अगर (!(p = (व्योम *) sm_to_para(smc,sm,SMT_P0015))) अणु
		DB_ESS("ESS: RAF frame error, parameter type not found");
		वापस fs;
	पूर्ण
	msg_res_type = ((काष्ठा smt_p_0015 *)p)->res_type ;

	/*
	 * get the poपूर्णांकer to the ESS command
	 */
	अगर (!(cmd = (काष्ठा smt_p_0016 *) sm_to_para(smc,sm,SMT_P0016))) अणु
		/*
		 * error in frame: para ESS command was not found
		 */
		 DB_ESS("ESS: RAF frame error, parameter command not found");
		 वापस fs;
	पूर्ण

	DB_ESSN(2, "fc %x	ft %x", sm->smt_class, sm->smt_type);
	DB_ESSN(2, "ver %x	tran %x", sm->smt_version, sm->smt_tid);
	DB_ESSN(2, "stn_id %pM", &sm->smt_source);

	DB_ESSN(2, "infolen %x	res %lx", sm->smt_len, msg_res_type);
	DB_ESSN(2, "sbacmd %x", cmd->sba_cmd);

	/*
	 * evaluate the ESS command
	 */
	चयन (cmd->sba_cmd) अणु

	/*
	 * Process an ESS Allocation Request
	 */
	हाल REQUEST_ALLOCATION :
		/*
		 * check क्रम an RAF Request (Allocation Request)
		 */
		अगर (sm->smt_type == SMT_REQUEST) अणु
			/*
			 * process the Allocation request only अगर the frame is
			 * local and no अटल allocation is used
			 */
			अगर (!local || smc->mib.fddiESSPayload)
				वापस fs;
			
			p = (व्योम *) sm_to_para(smc,sm,SMT_P0019)  ;
			क्रम (i = 0; i < 5; i++) अणु
				अगर (((काष्ठा smt_p_0019 *)p)->alloc_addr.a[i]) अणु
					वापस fs;
				पूर्ण
			पूर्ण

			/*
			 * Note: The Application should send a LAN_LOC_FRAME.
			 *	 The ESS करो not send the Frame to the network!
			 */
			smc->ess.alloc_trans_id = sm->smt_tid ;
			DB_ESS("ESS: save Alloc Req Trans ID %x", sm->smt_tid);
			p = (व्योम *) sm_to_para(smc,sm,SMT_P320F) ;
			((काष्ठा smt_p_320f *)p)->mib_payload =
				smc->mib.a[PATH0].fddiPATHSbaPayload ;
			p = (व्योम *) sm_to_para(smc,sm,SMT_P3210) ;
			((काष्ठा smt_p_3210 *)p)->mib_overhead =
				smc->mib.a[PATH0].fddiPATHSbaOverhead ;
			sm->smt_dest = smt_sba_da ;

			अगर (smc->ess.local_sba_active)
				वापस fs | I_INDICATOR;

			अगर (!(db = smt_get_mbuf(smc)))
				वापस fs;

			db->sm_len = mb->sm_len ;
			db->sm_off = mb->sm_off ;
			स_नकल(((अक्षर *)(db->sm_data+db->sm_off)),(अक्षर *)sm,
				(पूर्णांक)db->sm_len) ;
			dump_smt(smc,
				(काष्ठा smt_header *)(db->sm_data+db->sm_off),
				"RAF") ;
			smt_send_frame(smc,db,FC_SMT_INFO,0) ;
			वापस fs;
		पूर्ण

		/*
		 * The RAF frame is an Allocation Response !
		 * check the parameters
		 */
		अगर (smt_check_para(smc,sm,plist_raf_alc_res)) अणु
			DB_ESS("ESS: RAF with para problem, ignoring");
			वापस fs;
		पूर्ण

		/*
		 * VERIFY THE FRAME IS WELL BUILT:
		 *
		 *	1. path index = primary ring only
		 *	2. resource type = sync bw only
		 *	3. trans action id = alloc_trans_id
		 *	4. reason code = success
		 *
		 * If any are violated, discard the RAF frame
		 */
		अगर ((((काष्ठा smt_p_320b *)sm_to_para(smc,sm,SMT_P320B))->path_index
			!= PRIMARY_RING) ||
			(msg_res_type != SYNC_BW) ||
		(((काष्ठा smt_p_reason *)sm_to_para(smc,sm,SMT_P0012))->rdf_reason
			!= SMT_RDF_SUCCESS) ||
			(sm->smt_tid != smc->ess.alloc_trans_id)) अणु

			DB_ESS("ESS: Allocation Response not accepted");
			वापस fs;
		पूर्ण

		/*
		 * Extract message parameters
		 */
		p = (व्योम *) sm_to_para(smc,sm,SMT_P320F) ;
                अगर (!p) अणु
                        prपूर्णांकk(KERN_ERR "ESS: sm_to_para failed");
                        वापस fs;
                पूर्ण       
		payload = ((काष्ठा smt_p_320f *)p)->mib_payload ;
		p = (व्योम *) sm_to_para(smc,sm,SMT_P3210) ;
                अगर (!p) अणु
                        prपूर्णांकk(KERN_ERR "ESS: sm_to_para failed");
                        वापस fs;
                पूर्ण       
		overhead = ((काष्ठा smt_p_3210 *)p)->mib_overhead ;

		DB_ESSN(2, "payload= %lx	overhead= %lx",
			payload, overhead);

		/*
		 * process the bandwidth allocation
		 */
		(व्योम)process_bw_alloc(smc,(दीर्घ)payload,(दीर्घ)overhead) ;

		वापस fs;
		/* end of Process Allocation Request */

	/*
	 * Process an ESS Change Request
	 */
	हाल CHANGE_ALLOCATION :
		/*
		 * except only replies
		 */
		अगर (sm->smt_type != SMT_REQUEST) अणु
			DB_ESS("ESS: Do not process Change Responses");
			वापस fs;
		पूर्ण

		/*
		 * check the para क्रम the Change Request
		 */
		अगर (smt_check_para(smc,sm,plist_raf_chg_req)) अणु
			DB_ESS("ESS: RAF with para problem, ignoring");
			वापस fs;
		पूर्ण

		/*
		 * Verअगरy the path index and resource
		 * type are correct. If any of
		 * these are false, करोn't process this
		 * change request frame.
		 */
		अगर ((((काष्ठा smt_p_320b *)sm_to_para(smc,sm,SMT_P320B))->path_index
			!= PRIMARY_RING) || (msg_res_type != SYNC_BW)) अणु
			DB_ESS("ESS: RAF frame with para problem, ignoring");
			वापस fs;
		पूर्ण

		/*
		 * Extract message queue parameters
		 */
		p = (व्योम *) sm_to_para(smc,sm,SMT_P320F) ;
		payload = ((काष्ठा smt_p_320f *)p)->mib_payload ;
		p = (व्योम *) sm_to_para(smc,sm,SMT_P3210) ;
		overhead = ((काष्ठा smt_p_3210 *)p)->mib_overhead ;

		DB_ESSN(2, "ESS: Change Request from %pM",
			&sm->smt_source);
		DB_ESSN(2, "payload= %lx	overhead= %lx",
			payload, overhead);

		/*
		 * process the bandwidth allocation
		 */
		अगर(!process_bw_alloc(smc,(दीर्घ)payload,(दीर्घ)overhead))
			वापस fs;

		/*
		 * send an RAF Change Reply
		 */
		ess_send_response(smc,sm,CHANGE_ALLOCATION) ;

		वापस fs;
		/* end of Process Change Request */

	/*
	 * Process Report Response
	 */
	हाल REPORT_ALLOCATION :
		/*
		 * except only requests
		 */
		अगर (sm->smt_type != SMT_REQUEST) अणु
			DB_ESS("ESS: Do not process a Report Reply");
			वापस fs;
		पूर्ण

		DB_ESSN(2, "ESS: Report Request from %pM",
			&sm->smt_source);

		/*
		 * verअगरy that the resource type is sync bw only
		 */
		अगर (msg_res_type != SYNC_BW) अणु
			DB_ESS("ESS: ignoring RAF with para problem");
			वापस fs;
		पूर्ण

		/*
		 * send an RAF Change Reply
		 */
		ess_send_response(smc,sm,REPORT_ALLOCATION) ;

		वापस fs;
		/* end of Process Report Request */

	शेष:
		/*
		 * error in frame
		 */
		DB_ESS("ESS: ignoring RAF with bad sba_cmd");
		अवरोध ;
	पूर्ण

	वापस fs;
पूर्ण

/*
 * determines the synchronous bandwidth, set the TSYNC रेजिस्टर and the
 * mib variables SBAPayload, SBAOverhead and fddiMACT-NEG.
 */
अटल पूर्णांक process_bw_alloc(काष्ठा s_smc *smc, दीर्घ पूर्णांक payload, दीर्घ पूर्णांक overhead)
अणु
	/*
	 * determine the synchronous bandwidth (sync_bw) in bytes per T-NEG,
	 * अगर the payload is greater than zero.
	 * For the SBAPayload and the SBAOverhead we have the following
	 * unite quations
 	 *		      _		  _
	 *		     |	     bytes |
	 *	SBAPayload = | 8000 ------ |
	 *		     |		s  |
	 *		      -		  -
 	 *		       _       _
	 *		      |	 bytes	|
	 *	SBAOverhead = | ------	|
	 *		      |	 T-NEG	|
	 *		       -       -
 	 *
	 * T-NEG is described by the equation:
	 *
	 *		     (-) fddiMACT-NEG
	 *	T-NEG =	    -------------------
	 *			12500000 1/s
	 *
	 * The number of bytes we are able to send is the payload
	 * plus the overhead.
	 *
	 *			  bytes    T-NEG SBAPayload 8000 bytes/s
	 * sync_bw =  SBAOverhead ------ + -----------------------------
	 *	   		  T-NEG		T-NEG
	 *
	 *
	 *	      		     1
	 * sync_bw =  SBAOverhead + ---- (-)fddiMACT-NEG * SBAPayload
	 *	       		    1562
	 *
	 */

	/*
	 * set the mib attributes fddiPATHSbaOverhead, fddiPATHSbaPayload
	 */
/*	अगर (smt_set_obj(smc,SMT_P320F,payload,S_SET)) अणु
		DB_ESS("ESS: SMT does not accept the payload value");
		वापस FALSE;
	पूर्ण
	अगर (smt_set_obj(smc,SMT_P3210,overhead,S_SET)) अणु
		DB_ESS("ESS: SMT does not accept the overhead value");
		वापस FALSE;
	पूर्ण */

	/* premliminary */
	अगर (payload > MAX_PAYLOAD || overhead > 5000) अणु
		DB_ESS("ESS: payload / overhead not accepted");
		वापस FALSE;
	पूर्ण

	/*
	 * start the iterative allocation process अगर the payload or the overhead
	 * are smaller than the parsed values
	 */
	अगर (smc->mib.fddiESSPayload &&
		((u_दीर्घ)payload != smc->mib.fddiESSPayload ||
		(u_दीर्घ)overhead != smc->mib.fddiESSOverhead)) अणु
		smc->ess.raf_act_समयr_poll = TRUE ;
		smc->ess.समयr_count = 0 ;
	पूर्ण

	/*
	 * evulate the Payload
	 */
	अगर (payload) अणु
		DB_ESSN(2, "ESS: turn SMT_ST_SYNC_SERVICE bit on");
		smc->ess.sync_bw_available = TRUE ;

		smc->ess.sync_bw = overhead -
			(दीर्घ)smc->mib.m[MAC0].fddiMACT_Neg *
			payload / 1562 ;
	पूर्ण
	अन्यथा अणु
		DB_ESSN(2, "ESS: turn SMT_ST_SYNC_SERVICE bit off");
		smc->ess.sync_bw_available = FALSE ;
		smc->ess.sync_bw = 0 ;
		overhead = 0 ;
	पूर्ण

	smc->mib.a[PATH0].fddiPATHSbaPayload = payload ;
	smc->mib.a[PATH0].fddiPATHSbaOverhead = overhead ;


	DB_ESSN(2, "tsync = %lx", smc->ess.sync_bw);

	ess_config_fअगरo(smc) ;
	set_क्रमmac_tsync(smc,smc->ess.sync_bw) ;
	वापस TRUE;
पूर्ण

अटल व्योम ess_send_response(काष्ठा s_smc *smc, काष्ठा smt_header *sm,
			      पूर्णांक sba_cmd)
अणु
	काष्ठा smt_sba_chg	*chg ;
	SMbuf			*mb ;
	व्योम			*p ;

	/*
	 * get and initialize the response frame
	 */
	अगर (sba_cmd == CHANGE_ALLOCATION) अणु
		अगर (!(mb=smt_build_frame(smc,SMT_RAF,SMT_REPLY,
				माप(काष्ठा smt_sba_chg))))
				वापस ;
	पूर्ण
	अन्यथा अणु
		अगर (!(mb=smt_build_frame(smc,SMT_RAF,SMT_REPLY,
				माप(काष्ठा smt_sba_rep_res))))
				वापस ;
	पूर्ण

	chg = smtod(mb,काष्ठा smt_sba_chg *) ;
	chg->smt.smt_tid = sm->smt_tid ;
	chg->smt.smt_dest = sm->smt_source ;

	/* set P15 */
	chg->s_type.para.p_type = SMT_P0015 ;
	chg->s_type.para.p_len = माप(काष्ठा smt_p_0015) - PARA_LEN ;
	chg->s_type.res_type = SYNC_BW ;

	/* set P16 */
	chg->cmd.para.p_type = SMT_P0016 ;
	chg->cmd.para.p_len = माप(काष्ठा smt_p_0016) - PARA_LEN ;
	chg->cmd.sba_cmd = sba_cmd ;

	/* set P320B */
	chg->path.para.p_type = SMT_P320B ;
	chg->path.para.p_len = माप(काष्ठा smt_p_320b) - PARA_LEN ;
	chg->path.mib_index = SBAPATHINDEX ;
	chg->path.path_pad = 0;
	chg->path.path_index = PRIMARY_RING ;

	/* set P320F */
	chg->payload.para.p_type = SMT_P320F ;
	chg->payload.para.p_len = माप(काष्ठा smt_p_320f) - PARA_LEN ;
	chg->payload.mib_index = SBAPATHINDEX ;
	chg->payload.mib_payload = smc->mib.a[PATH0].fddiPATHSbaPayload ;

	/* set P3210 */
	chg->overhead.para.p_type = SMT_P3210 ;
	chg->overhead.para.p_len = माप(काष्ठा smt_p_3210) - PARA_LEN ;
	chg->overhead.mib_index = SBAPATHINDEX ;
	chg->overhead.mib_overhead = smc->mib.a[PATH0].fddiPATHSbaOverhead ;

	अगर (sba_cmd == CHANGE_ALLOCATION) अणु
		/* set P1A */
		chg->cat.para.p_type = SMT_P001A ;
		chg->cat.para.p_len = माप(काष्ठा smt_p_001a) - PARA_LEN ;
		p = (व्योम *) sm_to_para(smc,sm,SMT_P001A) ;
		chg->cat.category = ((काष्ठा smt_p_001a *)p)->category ;
	पूर्ण
	dump_smt(smc,(काष्ठा smt_header *)chg,"RAF") ;
	ess_send_frame(smc,mb) ;
पूर्ण

व्योम ess_समयr_poll(काष्ठा s_smc *smc)
अणु
	अगर (!smc->ess.raf_act_समयr_poll)
		वापस ;

	DB_ESSN(2, "ESS: timer_poll");

	smc->ess.समयr_count++ ;
	अगर (smc->ess.समयr_count == 10) अणु
		smc->ess.समयr_count = 0 ;
		ess_send_alc_req(smc) ;
	पूर्ण
पूर्ण

अटल व्योम ess_send_alc_req(काष्ठा s_smc *smc)
अणु
	काष्ठा smt_sba_alc_req *req ;
	SMbuf	*mb ;

	/*
	 * send never allocation request where the requested payload and
	 * overhead is zero or deallocate bandwidth when no bandwidth is
	 * parsed
	 */
	अगर (!smc->mib.fddiESSPayload) अणु
		smc->mib.fddiESSOverhead = 0 ;
	पूर्ण
	अन्यथा अणु
		अगर (!smc->mib.fddiESSOverhead)
			smc->mib.fddiESSOverhead = DEFAULT_OV ;
	पूर्ण

	अगर (smc->mib.fddiESSOverhead ==
		smc->mib.a[PATH0].fddiPATHSbaOverhead &&
		smc->mib.fddiESSPayload ==
		smc->mib.a[PATH0].fddiPATHSbaPayload)अणु
		smc->ess.raf_act_समयr_poll = FALSE ;
		smc->ess.समयr_count = 7 ;	/* next RAF alc req after 3 s */
		वापस ;
	पूर्ण
	
	/*
	 * get and initialize the response frame
	 */
	अगर (!(mb=smt_build_frame(smc,SMT_RAF,SMT_REQUEST,
			माप(काष्ठा smt_sba_alc_req))))
			वापस ;
	req = smtod(mb,काष्ठा smt_sba_alc_req *) ;
	req->smt.smt_tid = smc->ess.alloc_trans_id = smt_get_tid(smc) ;
	req->smt.smt_dest = smt_sba_da ;

	/* set P15 */
	req->s_type.para.p_type = SMT_P0015 ;
	req->s_type.para.p_len = माप(काष्ठा smt_p_0015) - PARA_LEN ;
	req->s_type.res_type = SYNC_BW ;

	/* set P16 */
	req->cmd.para.p_type = SMT_P0016 ;
	req->cmd.para.p_len = माप(काष्ठा smt_p_0016) - PARA_LEN ;
	req->cmd.sba_cmd = REQUEST_ALLOCATION ;

	/*
	 * set the parameter type and parameter length of all used
	 * parameters
	 */

	/* set P320B */
	req->path.para.p_type = SMT_P320B ;
	req->path.para.p_len = माप(काष्ठा smt_p_320b) - PARA_LEN ;
	req->path.mib_index = SBAPATHINDEX ;
	req->path.path_pad = 0;
	req->path.path_index = PRIMARY_RING ;

	/* set P0017 */
	req->pl_req.para.p_type = SMT_P0017 ;
	req->pl_req.para.p_len = माप(काष्ठा smt_p_0017) - PARA_LEN ;
	req->pl_req.sba_pl_req = smc->mib.fddiESSPayload -
		smc->mib.a[PATH0].fddiPATHSbaPayload ;

	/* set P0018 */
	req->ov_req.para.p_type = SMT_P0018 ;
	req->ov_req.para.p_len = माप(काष्ठा smt_p_0018) - PARA_LEN ;
	req->ov_req.sba_ov_req = smc->mib.fddiESSOverhead -
		smc->mib.a[PATH0].fddiPATHSbaOverhead ;

	/* set P320F */
	req->payload.para.p_type = SMT_P320F ;
	req->payload.para.p_len = माप(काष्ठा smt_p_320f) - PARA_LEN ;
	req->payload.mib_index = SBAPATHINDEX ;
	req->payload.mib_payload = smc->mib.a[PATH0].fddiPATHSbaPayload ;

	/* set P3210 */
	req->overhead.para.p_type = SMT_P3210 ;
	req->overhead.para.p_len = माप(काष्ठा smt_p_3210) - PARA_LEN ;
	req->overhead.mib_index = SBAPATHINDEX ;
	req->overhead.mib_overhead = smc->mib.a[PATH0].fddiPATHSbaOverhead ;

	/* set P19 */
	req->a_addr.para.p_type = SMT_P0019 ;
	req->a_addr.para.p_len = माप(काष्ठा smt_p_0019) - PARA_LEN ;
	req->a_addr.sba_pad = 0;
	req->a_addr.alloc_addr = null_addr ;

	/* set P1A */
	req->cat.para.p_type = SMT_P001A ;
	req->cat.para.p_len = माप(काष्ठा smt_p_001a) - PARA_LEN ;
	req->cat.category = smc->mib.fddiESSCategory ;

	/* set P1B */
	req->tneg.para.p_type = SMT_P001B ;
	req->tneg.para.p_len = माप(काष्ठा smt_p_001b) - PARA_LEN ;
	req->tneg.max_t_neg = smc->mib.fddiESSMaxTNeg ;

	/* set P1C */
	req->segm.para.p_type = SMT_P001C ;
	req->segm.para.p_len = माप(काष्ठा smt_p_001c) - PARA_LEN ;
	req->segm.min_seg_siz = smc->mib.fddiESSMinSegmentSize ;

	dump_smt(smc,(काष्ठा smt_header *)req,"RAF") ;
	ess_send_frame(smc,mb) ;
पूर्ण

अटल व्योम ess_send_frame(काष्ठा s_smc *smc, SMbuf *mb)
अणु
	/*
	 * check अगर the frame must be send to the own ESS
	 */
	अगर (smc->ess.local_sba_active) अणु
		/*
		 * Send the Change Reply to the local SBA
		 */
		DB_ESS("ESS:Send to the local SBA");
		अगर (!smc->ess.sba_reply_pend)
			smc->ess.sba_reply_pend = mb ;
		अन्यथा अणु
			DB_ESS("Frame is lost - another frame was pending");
			smt_मुक्त_mbuf(smc,mb) ;
		पूर्ण
	पूर्ण
	अन्यथा अणु
		/*
		 * Send the SBA RAF Change Reply to the network
		 */
		DB_ESS("ESS:Send to the network");
		smt_send_frame(smc,mb,FC_SMT_INFO,0) ;
	पूर्ण
पूर्ण

व्योम ess_para_change(काष्ठा s_smc *smc)
अणु
	(व्योम)process_bw_alloc(smc,(दीर्घ)smc->mib.a[PATH0].fddiPATHSbaPayload,
		(दीर्घ)smc->mib.a[PATH0].fddiPATHSbaOverhead) ;
पूर्ण

अटल व्योम ess_config_fअगरo(काष्ठा s_smc *smc)
अणु
	/*
	 * अगर nothing to करो निकास 
	 */
	अगर (smc->mib.a[PATH0].fddiPATHSbaPayload) अणु
		अगर (smc->hw.fp.fअगरo.fअगरo_config_mode & SYNC_TRAFFIC_ON &&
			(smc->hw.fp.fअगरo.fअगरo_config_mode&SEND_ASYNC_AS_SYNC) ==
			smc->mib.fddiESSSynchTxMode) अणु
			वापस ;
		पूर्ण
	पूर्ण
	अन्यथा अणु
		अगर (!(smc->hw.fp.fअगरo.fअगरo_config_mode & SYNC_TRAFFIC_ON)) अणु
			वापस ;
		पूर्ण
	पूर्ण

	/*
	 * split up the FIFO and reinitialize the queues
	 */
	क्रमmac_reinit_tx(smc) ;
पूर्ण

#पूर्ण_अगर /* ESS */

#पूर्ण_अगर	/* no SLIM_SMT */

