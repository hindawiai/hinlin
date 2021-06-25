<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright(c) 2007 Intel Corporation. All rights reserved.
 *
 * Maपूर्णांकained at www.Open-FCoE.org
 */

/*
 * PORT LOCKING NOTES
 *
 * These comments only apply to the 'port code' which consists of the lport,
 * disc and rport blocks.
 *
 * MOTIVATION
 *
 * The lport, disc and rport blocks all have mutexes that are used to protect
 * those objects. The मुख्य motivation क्रम these locks is to prevent from
 * having an lport reset just beक्रमe we send a frame. In that scenario the
 * lport's FID would get set to zero and then we'd send a frame with an
 * invalid SID. We also need to ensure that states करोn't change unexpectedly
 * जबतक processing another state.
 *
 * HIERARCHY
 *
 * The following hierarchy defines the locking rules. A greater lock
 * may be held beक्रमe acquiring a lesser lock, but a lesser lock should never
 * be held जबतक attempting to acquire a greater lock. Here is the hierarchy-
 *
 * lport > disc, lport > rport, disc > rport
 *
 * CALLBACKS
 *
 * The callbacks cause complications with this scheme. There is a callback
 * from the rport (to either lport or disc) and a callback from disc
 * (to the lport).
 *
 * As rports निकास the rport state machine a callback is made to the owner of
 * the rport to notअगरy success or failure. Since the callback is likely to
 * cause the lport or disc to grab its lock we cannot hold the rport lock
 * जबतक making the callback. To ensure that the rport is not मुक्त'd जबतक
 * processing the callback the rport callbacks are serialized through a
 * single-thपढ़ोed workqueue. An rport would never be मुक्त'd जबतक in a
 * callback handler because no other rport work in this queue can be executed
 * at the same समय.
 *
 * When discovery succeeds or fails a callback is made to the lport as
 * notअगरication. Currently, successful discovery causes the lport to take no
 * action. A failure will cause the lport to reset. There is likely a circular
 * locking problem with this implementation.
 */

/*
 * LPORT LOCKING
 *
 * The critical sections रक्षित by the lport's mutex are quite broad and
 * may be improved upon in the future. The lport code and its locking करोesn't
 * influence the I/O path, so excessive locking करोesn't penalize I/O
 * perक्रमmance.
 *
 * The strategy is to lock whenever processing a request or response. Note
 * that every _enter_* function corresponds to a state change. They generally
 * change the lports state and then send a request out on the wire. We lock
 * beक्रमe calling any of these functions to protect that state change. This
 * means that the entry poपूर्णांकs पूर्णांकo the lport block manage the locks जबतक
 * the state machine can transition between states (i.e. _enter_* functions)
 * जबतक always staying रक्षित.
 *
 * When handling responses we also hold the lport mutex broadly. When the
 * lport receives the response frame it locks the mutex and then calls the
 * appropriate handler क्रम the particuar response. Generally a response will
 * trigger a state change and so the lock must alपढ़ोy be held.
 *
 * Retries also have to consider the locking. The retries occur from a work
 * context and the work function will lock the lport and then retry the state
 * (i.e. _enter_* function).
 */

#समावेश <linux/समयr.h>
#समावेश <linux/delay.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <यंत्र/unaligned.h>

#समावेश <scsi/fc/fc_gs.h>

#समावेश <scsi/libfc.h>
#समावेश <linux/scatterlist.h>

#समावेश "fc_encode.h"
#समावेश "fc_libfc.h"

/* Fabric IDs to use क्रम poपूर्णांक-to-poपूर्णांक mode, chosen on whims. */
#घोषणा FC_LOCAL_PTP_FID_LO   0x010101
#घोषणा FC_LOCAL_PTP_FID_HI   0x010102

#घोषणा	DNS_DELAY	      3 /* Discovery delay after RSCN (in seconds)*/

अटल व्योम fc_lport_error(काष्ठा fc_lport *, काष्ठा fc_frame *);

अटल व्योम fc_lport_enter_reset(काष्ठा fc_lport *);
अटल व्योम fc_lport_enter_flogi(काष्ठा fc_lport *);
अटल व्योम fc_lport_enter_dns(काष्ठा fc_lport *);
अटल व्योम fc_lport_enter_ns(काष्ठा fc_lport *, क्रमागत fc_lport_state);
अटल व्योम fc_lport_enter_scr(काष्ठा fc_lport *);
अटल व्योम fc_lport_enter_पढ़ोy(काष्ठा fc_lport *);
अटल व्योम fc_lport_enter_logo(काष्ठा fc_lport *);
अटल व्योम fc_lport_enter_fdmi(काष्ठा fc_lport *lport);
अटल व्योम fc_lport_enter_ms(काष्ठा fc_lport *, क्रमागत fc_lport_state);

अटल स्थिर अक्षर *fc_lport_state_names[] = अणु
	[LPORT_ST_DISABLED] = "disabled",
	[LPORT_ST_FLOGI] =    "FLOGI",
	[LPORT_ST_DNS] =      "dNS",
	[LPORT_ST_RNN_ID] =   "RNN_ID",
	[LPORT_ST_RSNN_NN] =  "RSNN_NN",
	[LPORT_ST_RSPN_ID] =  "RSPN_ID",
	[LPORT_ST_RFT_ID] =   "RFT_ID",
	[LPORT_ST_RFF_ID] =   "RFF_ID",
	[LPORT_ST_FDMI] =     "FDMI",
	[LPORT_ST_RHBA] =     "RHBA",
	[LPORT_ST_RPA] =      "RPA",
	[LPORT_ST_DHBA] =     "DHBA",
	[LPORT_ST_DPRT] =     "DPRT",
	[LPORT_ST_SCR] =      "SCR",
	[LPORT_ST_READY] =    "Ready",
	[LPORT_ST_LOGO] =     "LOGO",
	[LPORT_ST_RESET] =    "reset",
पूर्ण;

/**
 * काष्ठा fc_bsg_info - FC Passthrough managemet काष्ठाure
 * @job:      The passthrough job
 * @lport:    The local port to pass through a command
 * @rsp_code: The expected response code
 * @sg:	      job->reply_payload.sg_list
 * @nents:    job->reply_payload.sg_cnt
 * @offset:   The offset पूर्णांकo the response data
 */
काष्ठा fc_bsg_info अणु
	काष्ठा bsg_job *job;
	काष्ठा fc_lport *lport;
	u16 rsp_code;
	काष्ठा scatterlist *sg;
	u32 nents;
	माप_प्रकार offset;
पूर्ण;

/**
 * fc_frame_drop() - Dummy frame handler
 * @lport: The local port the frame was received on
 * @fp:	   The received frame
 */
अटल पूर्णांक fc_frame_drop(काष्ठा fc_lport *lport, काष्ठा fc_frame *fp)
अणु
	fc_frame_मुक्त(fp);
	वापस 0;
पूर्ण

/**
 * fc_lport_rport_callback() - Event handler क्रम rport events
 * @lport: The lport which is receiving the event
 * @rdata: निजी remote port data
 * @event: The event that occurred
 *
 * Locking Note: The rport lock should not be held when calling
 *		 this function.
 */
अटल व्योम fc_lport_rport_callback(काष्ठा fc_lport *lport,
				    काष्ठा fc_rport_priv *rdata,
				    क्रमागत fc_rport_event event)
अणु
	FC_LPORT_DBG(lport, "Received a %d event for port (%6.6x)\n", event,
		     rdata->ids.port_id);

	mutex_lock(&lport->lp_mutex);
	चयन (event) अणु
	हाल RPORT_EV_READY:
		अगर (lport->state == LPORT_ST_DNS) अणु
			lport->dns_rdata = rdata;
			fc_lport_enter_ns(lport, LPORT_ST_RNN_ID);
		पूर्ण अन्यथा अगर (lport->state == LPORT_ST_FDMI) अणु
			lport->ms_rdata = rdata;
			fc_lport_enter_ms(lport, LPORT_ST_DHBA);
		पूर्ण अन्यथा अणु
			FC_LPORT_DBG(lport, "Received an READY event "
				     "on port (%6.6x) for the directory "
				     "server, but the lport is not "
				     "in the DNS or FDMI state, it's in the "
				     "%d state", rdata->ids.port_id,
				     lport->state);
			fc_rport_logoff(rdata);
		पूर्ण
		अवरोध;
	हाल RPORT_EV_LOGO:
	हाल RPORT_EV_FAILED:
	हाल RPORT_EV_STOP:
		अगर (rdata->ids.port_id == FC_FID_सूची_SERV)
			lport->dns_rdata = शून्य;
		अन्यथा अगर (rdata->ids.port_id == FC_FID_MGMT_SERV)
			lport->ms_rdata = शून्य;
		अवरोध;
	हाल RPORT_EV_NONE:
		अवरोध;
	पूर्ण
	mutex_unlock(&lport->lp_mutex);
पूर्ण

/**
 * fc_lport_state() - Return a string which represents the lport's state
 * @lport: The lport whose state is to converted to a string
 */
अटल स्थिर अक्षर *fc_lport_state(काष्ठा fc_lport *lport)
अणु
	स्थिर अक्षर *cp;

	cp = fc_lport_state_names[lport->state];
	अगर (!cp)
		cp = "unknown";
	वापस cp;
पूर्ण

/**
 * fc_lport_ptp_setup() - Create an rport क्रम poपूर्णांक-to-poपूर्णांक mode
 * @lport:	 The lport to attach the ptp rport to
 * @remote_fid:	 The FID of the ptp rport
 * @remote_wwpn: The WWPN of the ptp rport
 * @remote_wwnn: The WWNN of the ptp rport
 */
अटल व्योम fc_lport_ptp_setup(काष्ठा fc_lport *lport,
			       u32 remote_fid, u64 remote_wwpn,
			       u64 remote_wwnn)
अणु
	lockdep_निश्चित_held(&lport->lp_mutex);

	अगर (lport->ptp_rdata) अणु
		fc_rport_logoff(lport->ptp_rdata);
		kref_put(&lport->ptp_rdata->kref, fc_rport_destroy);
	पूर्ण
	mutex_lock(&lport->disc.disc_mutex);
	lport->ptp_rdata = fc_rport_create(lport, remote_fid);
	kref_get(&lport->ptp_rdata->kref);
	lport->ptp_rdata->ids.port_name = remote_wwpn;
	lport->ptp_rdata->ids.node_name = remote_wwnn;
	mutex_unlock(&lport->disc.disc_mutex);

	fc_rport_login(lport->ptp_rdata);

	fc_lport_enter_पढ़ोy(lport);
पूर्ण

/**
 * fc_get_host_port_state() - Return the port state of the given Scsi_Host
 * @shost:  The SCSI host whose port state is to be determined
 */
व्योम fc_get_host_port_state(काष्ठा Scsi_Host *shost)
अणु
	काष्ठा fc_lport *lport = shost_priv(shost);

	mutex_lock(&lport->lp_mutex);
	अगर (!lport->link_up)
		fc_host_port_state(shost) = FC_PORTSTATE_LINKDOWN;
	अन्यथा
		चयन (lport->state) अणु
		हाल LPORT_ST_READY:
			fc_host_port_state(shost) = FC_PORTSTATE_ONLINE;
			अवरोध;
		शेष:
			fc_host_port_state(shost) = FC_PORTSTATE_OFFLINE;
		पूर्ण
	mutex_unlock(&lport->lp_mutex);
पूर्ण
EXPORT_SYMBOL(fc_get_host_port_state);

/**
 * fc_get_host_speed() - Return the speed of the given Scsi_Host
 * @shost: The SCSI host whose port speed is to be determined
 */
व्योम fc_get_host_speed(काष्ठा Scsi_Host *shost)
अणु
	काष्ठा fc_lport *lport = shost_priv(shost);

	fc_host_speed(shost) = lport->link_speed;
पूर्ण
EXPORT_SYMBOL(fc_get_host_speed);

/**
 * fc_get_host_stats() - Return the Scsi_Host's statistics
 * @shost: The SCSI host whose statistics are to be वापसed
 */
काष्ठा fc_host_statistics *fc_get_host_stats(काष्ठा Scsi_Host *shost)
अणु
	काष्ठा fc_host_statistics *fc_stats;
	काष्ठा fc_lport *lport = shost_priv(shost);
	अचिन्हित पूर्णांक cpu;
	u64 fcp_in_bytes = 0;
	u64 fcp_out_bytes = 0;

	fc_stats = &lport->host_stats;
	स_रखो(fc_stats, 0, माप(काष्ठा fc_host_statistics));

	fc_stats->seconds_since_last_reset = (jअगरfies - lport->boot_समय) / HZ;

	क्रम_each_possible_cpu(cpu) अणु
		काष्ठा fc_stats *stats;

		stats = per_cpu_ptr(lport->stats, cpu);

		fc_stats->tx_frames += stats->TxFrames;
		fc_stats->tx_words += stats->TxWords;
		fc_stats->rx_frames += stats->RxFrames;
		fc_stats->rx_words += stats->RxWords;
		fc_stats->error_frames += stats->ErrorFrames;
		fc_stats->invalid_crc_count += stats->InvalidCRCCount;
		fc_stats->fcp_input_requests += stats->InputRequests;
		fc_stats->fcp_output_requests += stats->OutputRequests;
		fc_stats->fcp_control_requests += stats->ControlRequests;
		fcp_in_bytes += stats->InputBytes;
		fcp_out_bytes += stats->OutputBytes;
		fc_stats->fcp_packet_alloc_failures += stats->FcpPktAllocFails;
		fc_stats->fcp_packet_पातs += stats->FcpPktAborts;
		fc_stats->fcp_frame_alloc_failures += stats->FcpFrameAllocFails;
		fc_stats->link_failure_count += stats->LinkFailureCount;
	पूर्ण
	fc_stats->fcp_input_megabytes = भाग_u64(fcp_in_bytes, 1000000);
	fc_stats->fcp_output_megabytes = भाग_u64(fcp_out_bytes, 1000000);
	fc_stats->lip_count = -1;
	fc_stats->nos_count = -1;
	fc_stats->loss_of_sync_count = -1;
	fc_stats->loss_of_संकेत_count = -1;
	fc_stats->prim_seq_protocol_err_count = -1;
	fc_stats->dumped_frames = -1;

	/* update exches stats */
	fc_exch_update_stats(lport);

	वापस fc_stats;
पूर्ण
EXPORT_SYMBOL(fc_get_host_stats);

/**
 * fc_lport_flogi_fill() - Fill in FLOGI command क्रम request
 * @lport: The local port the FLOGI is क्रम
 * @flogi: The FLOGI command
 * @op:	   The opcode
 */
अटल व्योम fc_lport_flogi_fill(काष्ठा fc_lport *lport,
				काष्ठा fc_els_flogi *flogi,
				अचिन्हित पूर्णांक op)
अणु
	काष्ठा fc_els_csp *sp;
	काष्ठा fc_els_cssp *cp;

	स_रखो(flogi, 0, माप(*flogi));
	flogi->fl_cmd = (u8) op;
	put_unaligned_be64(lport->wwpn, &flogi->fl_wwpn);
	put_unaligned_be64(lport->wwnn, &flogi->fl_wwnn);
	sp = &flogi->fl_csp;
	sp->sp_hi_ver = 0x20;
	sp->sp_lo_ver = 0x20;
	sp->sp_bb_cred = htons(10);	/* this माला_लो set by gateway */
	sp->sp_bb_data = htons((u16) lport->mfs);
	cp = &flogi->fl_cssp[3 - 1];	/* class 3 parameters */
	cp->cp_class = htons(FC_CPC_VALID | FC_CPC_SEQ);
	अगर (op != ELS_FLOGI) अणु
		sp->sp_features = htons(FC_SP_FT_CIRO);
		sp->sp_tot_seq = htons(255);	/* seq. we accept */
		sp->sp_rel_off = htons(0x1f);
		sp->sp_e_d_tov = htonl(lport->e_d_tov);

		cp->cp_rdfs = htons((u16) lport->mfs);
		cp->cp_con_seq = htons(255);
		cp->cp_खोलो_seq = 1;
	पूर्ण
पूर्ण

/**
 * fc_lport_add_fc4_type() - Add a supported FC-4 type to a local port
 * @lport: The local port to add a new FC-4 type to
 * @type:  The new FC-4 type
 */
अटल व्योम fc_lport_add_fc4_type(काष्ठा fc_lport *lport, क्रमागत fc_fh_type type)
अणु
	__be32 *mp;

	mp = &lport->fcts.ff_type_map[type / FC_NS_BPW];
	*mp = htonl(ntohl(*mp) | 1UL << (type % FC_NS_BPW));
पूर्ण

/**
 * fc_lport_recv_rlir_req() - Handle received Registered Link Incident Report.
 * @lport: Fibre Channel local port receiving the RLIR
 * @fp:	   The RLIR request frame
 */
अटल व्योम fc_lport_recv_rlir_req(काष्ठा fc_lport *lport, काष्ठा fc_frame *fp)
अणु
	lockdep_निश्चित_held(&lport->lp_mutex);

	FC_LPORT_DBG(lport, "Received RLIR request while in state %s\n",
		     fc_lport_state(lport));

	fc_seq_els_rsp_send(fp, ELS_LS_ACC, शून्य);
	fc_frame_मुक्त(fp);
पूर्ण

/**
 * fc_lport_recv_echo_req() - Handle received ECHO request
 * @lport: The local port receiving the ECHO
 * @in_fp: ECHO request frame
 */
अटल व्योम fc_lport_recv_echo_req(काष्ठा fc_lport *lport,
				   काष्ठा fc_frame *in_fp)
अणु
	काष्ठा fc_frame *fp;
	अचिन्हित पूर्णांक len;
	व्योम *pp;
	व्योम *dp;

	lockdep_निश्चित_held(&lport->lp_mutex);

	FC_LPORT_DBG(lport, "Received ECHO request while in state %s\n",
		     fc_lport_state(lport));

	len = fr_len(in_fp) - माप(काष्ठा fc_frame_header);
	pp = fc_frame_payload_get(in_fp, len);

	अगर (len < माप(__be32))
		len = माप(__be32);

	fp = fc_frame_alloc(lport, len);
	अगर (fp) अणु
		dp = fc_frame_payload_get(fp, len);
		स_नकल(dp, pp, len);
		*((__be32 *)dp) = htonl(ELS_LS_ACC << 24);
		fc_fill_reply_hdr(fp, in_fp, FC_RCTL_ELS_REP, 0);
		lport->tt.frame_send(lport, fp);
	पूर्ण
	fc_frame_मुक्त(in_fp);
पूर्ण

/**
 * fc_lport_recv_rnid_req() - Handle received Request Node ID data request
 * @lport: The local port receiving the RNID
 * @in_fp: The RNID request frame
 */
अटल व्योम fc_lport_recv_rnid_req(काष्ठा fc_lport *lport,
				   काष्ठा fc_frame *in_fp)
अणु
	काष्ठा fc_frame *fp;
	काष्ठा fc_els_rnid *req;
	काष्ठा अणु
		काष्ठा fc_els_rnid_resp rnid;
		काष्ठा fc_els_rnid_cid cid;
		काष्ठा fc_els_rnid_gen gen;
	पूर्ण *rp;
	काष्ठा fc_seq_els_data rjt_data;
	u8 fmt;
	माप_प्रकार len;

	lockdep_निश्चित_held(&lport->lp_mutex);

	FC_LPORT_DBG(lport, "Received RNID request while in state %s\n",
		     fc_lport_state(lport));

	req = fc_frame_payload_get(in_fp, माप(*req));
	अगर (!req) अणु
		rjt_data.reason = ELS_RJT_LOGIC;
		rjt_data.explan = ELS_EXPL_NONE;
		fc_seq_els_rsp_send(in_fp, ELS_LS_RJT, &rjt_data);
	पूर्ण अन्यथा अणु
		fmt = req->rnid_fmt;
		len = माप(*rp);
		अगर (fmt != ELS_RNIDF_GEN ||
		    ntohl(lport->rnid_gen.rnid_atype) == 0) अणु
			fmt = ELS_RNIDF_NONE;	/* nothing to provide */
			len -= माप(rp->gen);
		पूर्ण
		fp = fc_frame_alloc(lport, len);
		अगर (fp) अणु
			rp = fc_frame_payload_get(fp, len);
			स_रखो(rp, 0, len);
			rp->rnid.rnid_cmd = ELS_LS_ACC;
			rp->rnid.rnid_fmt = fmt;
			rp->rnid.rnid_cid_len = माप(rp->cid);
			rp->cid.rnid_wwpn = htonll(lport->wwpn);
			rp->cid.rnid_wwnn = htonll(lport->wwnn);
			अगर (fmt == ELS_RNIDF_GEN) अणु
				rp->rnid.rnid_sid_len = माप(rp->gen);
				स_नकल(&rp->gen, &lport->rnid_gen,
				       माप(rp->gen));
			पूर्ण
			fc_fill_reply_hdr(fp, in_fp, FC_RCTL_ELS_REP, 0);
			lport->tt.frame_send(lport, fp);
		पूर्ण
	पूर्ण
	fc_frame_मुक्त(in_fp);
पूर्ण

/**
 * fc_lport_recv_logo_req() - Handle received fabric LOGO request
 * @lport: The local port receiving the LOGO
 * @fp:	   The LOGO request frame
 */
अटल व्योम fc_lport_recv_logo_req(काष्ठा fc_lport *lport, काष्ठा fc_frame *fp)
अणु
	lockdep_निश्चित_held(&lport->lp_mutex);

	fc_seq_els_rsp_send(fp, ELS_LS_ACC, शून्य);
	fc_lport_enter_reset(lport);
	fc_frame_मुक्त(fp);
पूर्ण

/**
 * fc_fabric_login() - Start the lport state machine
 * @lport: The local port that should log पूर्णांकo the fabric
 *
 * Locking Note: This function should not be called
 *		 with the lport lock held.
 */
पूर्णांक fc_fabric_login(काष्ठा fc_lport *lport)
अणु
	पूर्णांक rc = -1;

	mutex_lock(&lport->lp_mutex);
	अगर (lport->state == LPORT_ST_DISABLED ||
	    lport->state == LPORT_ST_LOGO) अणु
		fc_lport_state_enter(lport, LPORT_ST_RESET);
		fc_lport_enter_reset(lport);
		rc = 0;
	पूर्ण
	mutex_unlock(&lport->lp_mutex);

	वापस rc;
पूर्ण
EXPORT_SYMBOL(fc_fabric_login);

/**
 * __fc_linkup() - Handler क्रम transport linkup events
 * @lport: The lport whose link is up
 */
व्योम __fc_linkup(काष्ठा fc_lport *lport)
अणु
	lockdep_निश्चित_held(&lport->lp_mutex);

	अगर (!lport->link_up) अणु
		lport->link_up = 1;

		अगर (lport->state == LPORT_ST_RESET)
			fc_lport_enter_flogi(lport);
	पूर्ण
पूर्ण

/**
 * fc_linkup() - Handler क्रम transport linkup events
 * @lport: The local port whose link is up
 */
व्योम fc_linkup(काष्ठा fc_lport *lport)
अणु
	prपूर्णांकk(KERN_INFO "host%d: libfc: Link up on port (%6.6x)\n",
	       lport->host->host_no, lport->port_id);

	mutex_lock(&lport->lp_mutex);
	__fc_linkup(lport);
	mutex_unlock(&lport->lp_mutex);
पूर्ण
EXPORT_SYMBOL(fc_linkup);

/**
 * __fc_linkकरोwn() - Handler क्रम transport linkकरोwn events
 * @lport: The lport whose link is करोwn
 */
व्योम __fc_linkकरोwn(काष्ठा fc_lport *lport)
अणु
	lockdep_निश्चित_held(&lport->lp_mutex);

	अगर (lport->link_up) अणु
		lport->link_up = 0;
		fc_lport_enter_reset(lport);
		lport->tt.fcp_cleanup(lport);
	पूर्ण
पूर्ण

/**
 * fc_linkकरोwn() - Handler क्रम transport linkकरोwn events
 * @lport: The local port whose link is करोwn
 */
व्योम fc_linkकरोwn(काष्ठा fc_lport *lport)
अणु
	prपूर्णांकk(KERN_INFO "host%d: libfc: Link down on port (%6.6x)\n",
	       lport->host->host_no, lport->port_id);

	mutex_lock(&lport->lp_mutex);
	__fc_linkकरोwn(lport);
	mutex_unlock(&lport->lp_mutex);
पूर्ण
EXPORT_SYMBOL(fc_linkकरोwn);

/**
 * fc_fabric_logoff() - Logout of the fabric
 * @lport: The local port to logoff the fabric
 *
 * Return value:
 *	0 क्रम success, -1 क्रम failure
 */
पूर्णांक fc_fabric_logoff(काष्ठा fc_lport *lport)
अणु
	lport->tt.disc_stop_final(lport);
	mutex_lock(&lport->lp_mutex);
	अगर (lport->dns_rdata)
		fc_rport_logoff(lport->dns_rdata);
	mutex_unlock(&lport->lp_mutex);
	fc_rport_flush_queue();
	mutex_lock(&lport->lp_mutex);
	fc_lport_enter_logo(lport);
	mutex_unlock(&lport->lp_mutex);
	cancel_delayed_work_sync(&lport->retry_work);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(fc_fabric_logoff);

/**
 * fc_lport_destroy() - Unरेजिस्टर a fc_lport
 * @lport: The local port to unरेजिस्टर
 *
 * Note:
 * निकास routine क्रम fc_lport instance
 * clean-up all the allocated memory
 * and मुक्त up other प्रणाली resources.
 *
 */
पूर्णांक fc_lport_destroy(काष्ठा fc_lport *lport)
अणु
	mutex_lock(&lport->lp_mutex);
	lport->state = LPORT_ST_DISABLED;
	lport->link_up = 0;
	lport->tt.frame_send = fc_frame_drop;
	mutex_unlock(&lport->lp_mutex);

	lport->tt.fcp_पात_io(lport);
	lport->tt.disc_stop_final(lport);
	lport->tt.exch_mgr_reset(lport, 0, 0);
	cancel_delayed_work_sync(&lport->retry_work);
	fc_fc4_del_lport(lport);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(fc_lport_destroy);

/**
 * fc_set_mfs() - Set the maximum frame size क्रम a local port
 * @lport: The local port to set the MFS क्रम
 * @mfs:   The new MFS
 */
पूर्णांक fc_set_mfs(काष्ठा fc_lport *lport, u32 mfs)
अणु
	अचिन्हित पूर्णांक old_mfs;
	पूर्णांक rc = -EINVAL;

	mutex_lock(&lport->lp_mutex);

	old_mfs = lport->mfs;

	अगर (mfs >= FC_MIN_MAX_FRAME) अणु
		mfs &= ~3;
		अगर (mfs > FC_MAX_FRAME)
			mfs = FC_MAX_FRAME;
		mfs -= माप(काष्ठा fc_frame_header);
		lport->mfs = mfs;
		rc = 0;
	पूर्ण

	अगर (!rc && mfs < old_mfs)
		fc_lport_enter_reset(lport);

	mutex_unlock(&lport->lp_mutex);

	वापस rc;
पूर्ण
EXPORT_SYMBOL(fc_set_mfs);

/**
 * fc_lport_disc_callback() - Callback क्रम discovery events
 * @lport: The local port receiving the event
 * @event: The discovery event
 */
अटल व्योम fc_lport_disc_callback(काष्ठा fc_lport *lport,
				   क्रमागत fc_disc_event event)
अणु
	चयन (event) अणु
	हाल DISC_EV_SUCCESS:
		FC_LPORT_DBG(lport, "Discovery succeeded\n");
		अवरोध;
	हाल DISC_EV_FAILED:
		prपूर्णांकk(KERN_ERR "host%d: libfc: "
		       "Discovery failed for port (%6.6x)\n",
		       lport->host->host_no, lport->port_id);
		mutex_lock(&lport->lp_mutex);
		fc_lport_enter_reset(lport);
		mutex_unlock(&lport->lp_mutex);
		अवरोध;
	हाल DISC_EV_NONE:
		WARN_ON(1);
		अवरोध;
	पूर्ण
पूर्ण

/**
 * fc_lport_enter_पढ़ोy() - Enter the पढ़ोy state and start discovery
 * @lport: The local port that is पढ़ोy
 */
अटल व्योम fc_lport_enter_पढ़ोy(काष्ठा fc_lport *lport)
अणु
	lockdep_निश्चित_held(&lport->lp_mutex);

	FC_LPORT_DBG(lport, "Entered READY from state %s\n",
		     fc_lport_state(lport));

	fc_lport_state_enter(lport, LPORT_ST_READY);
	अगर (lport->vport)
		fc_vport_set_state(lport->vport, FC_VPORT_ACTIVE);
	fc_vports_linkchange(lport);

	अगर (!lport->ptp_rdata)
		lport->tt.disc_start(fc_lport_disc_callback, lport);
पूर्ण

/**
 * fc_lport_set_port_id() - set the local port Port ID
 * @lport: The local port which will have its Port ID set.
 * @port_id: The new port ID.
 * @fp: The frame containing the incoming request, or शून्य.
 */
अटल व्योम fc_lport_set_port_id(काष्ठा fc_lport *lport, u32 port_id,
				 काष्ठा fc_frame *fp)
अणु
	lockdep_निश्चित_held(&lport->lp_mutex);

	अगर (port_id)
		prपूर्णांकk(KERN_INFO "host%d: Assigned Port ID %6.6x\n",
		       lport->host->host_no, port_id);

	lport->port_id = port_id;

	/* Update the fc_host */
	fc_host_port_id(lport->host) = port_id;

	अगर (lport->tt.lport_set_port_id)
		lport->tt.lport_set_port_id(lport, port_id, fp);
पूर्ण

/**
 * fc_lport_set_local_id() - set the local port Port ID क्रम poपूर्णांक-to-multipoपूर्णांक
 * @lport: The local port which will have its Port ID set.
 * @port_id: The new port ID.
 *
 * Called by the lower-level driver when transport sets the local port_id.
 * This is used in VN_port to VN_port mode क्रम FCoE, and causes FLOGI and
 * discovery to be skipped.
 */
व्योम fc_lport_set_local_id(काष्ठा fc_lport *lport, u32 port_id)
अणु
	mutex_lock(&lport->lp_mutex);

	fc_lport_set_port_id(lport, port_id, शून्य);

	चयन (lport->state) अणु
	हाल LPORT_ST_RESET:
	हाल LPORT_ST_FLOGI:
		अगर (port_id)
			fc_lport_enter_पढ़ोy(lport);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	mutex_unlock(&lport->lp_mutex);
पूर्ण
EXPORT_SYMBOL(fc_lport_set_local_id);

/**
 * fc_lport_recv_flogi_req() - Receive a FLOGI request
 * @lport: The local port that received the request
 * @rx_fp: The FLOGI frame
 *
 * A received FLOGI request indicates a poपूर्णांक-to-poपूर्णांक connection.
 * Accept it with the common service parameters indicating our N port.
 * Set up to करो a PLOGI अगर we have the higher-number WWPN.
 */
अटल व्योम fc_lport_recv_flogi_req(काष्ठा fc_lport *lport,
				    काष्ठा fc_frame *rx_fp)
अणु
	काष्ठा fc_frame *fp;
	काष्ठा fc_frame_header *fh;
	काष्ठा fc_els_flogi *flp;
	काष्ठा fc_els_flogi *new_flp;
	u64 remote_wwpn;
	u32 remote_fid;
	u32 local_fid;

	lockdep_निश्चित_held(&lport->lp_mutex);

	FC_LPORT_DBG(lport, "Received FLOGI request while in state %s\n",
		     fc_lport_state(lport));

	remote_fid = fc_frame_sid(rx_fp);
	flp = fc_frame_payload_get(rx_fp, माप(*flp));
	अगर (!flp)
		जाओ out;
	remote_wwpn = get_unaligned_be64(&flp->fl_wwpn);
	अगर (remote_wwpn == lport->wwpn) अणु
		prपूर्णांकk(KERN_WARNING "host%d: libfc: Received FLOGI from port "
		       "with same WWPN %16.16llx\n",
		       lport->host->host_no, remote_wwpn);
		जाओ out;
	पूर्ण
	FC_LPORT_DBG(lport, "FLOGI from port WWPN %16.16llx\n", remote_wwpn);

	/*
	 * XXX what is the right thing to करो क्रम FIDs?
	 * The originator might expect our S_ID to be 0xfffffe.
	 * But अगर so, both of us could end up with the same FID.
	 */
	local_fid = FC_LOCAL_PTP_FID_LO;
	अगर (remote_wwpn < lport->wwpn) अणु
		local_fid = FC_LOCAL_PTP_FID_HI;
		अगर (!remote_fid || remote_fid == local_fid)
			remote_fid = FC_LOCAL_PTP_FID_LO;
	पूर्ण अन्यथा अगर (!remote_fid) अणु
		remote_fid = FC_LOCAL_PTP_FID_HI;
	पूर्ण

	fc_lport_set_port_id(lport, local_fid, rx_fp);

	fp = fc_frame_alloc(lport, माप(*flp));
	अगर (fp) अणु
		new_flp = fc_frame_payload_get(fp, माप(*flp));
		fc_lport_flogi_fill(lport, new_flp, ELS_FLOGI);
		new_flp->fl_cmd = (u8) ELS_LS_ACC;

		/*
		 * Send the response.  If this fails, the originator should
		 * repeat the sequence.
		 */
		fc_fill_reply_hdr(fp, rx_fp, FC_RCTL_ELS_REP, 0);
		fh = fc_frame_header_get(fp);
		hton24(fh->fh_s_id, local_fid);
		hton24(fh->fh_d_id, remote_fid);
		lport->tt.frame_send(lport, fp);

	पूर्ण अन्यथा अणु
		fc_lport_error(lport, fp);
	पूर्ण
	fc_lport_ptp_setup(lport, remote_fid, remote_wwpn,
			   get_unaligned_be64(&flp->fl_wwnn));
out:
	fc_frame_मुक्त(rx_fp);
पूर्ण

/**
 * fc_lport_recv_els_req() - The generic lport ELS request handler
 * @lport: The local port that received the request
 * @fp:	   The request frame
 *
 * This function will see अगर the lport handles the request or
 * अगर an rport should handle the request.
 *
 * Locking Note: This function should not be called with the lport
 *		 lock held because it will grab the lock.
 */
अटल व्योम fc_lport_recv_els_req(काष्ठा fc_lport *lport,
				  काष्ठा fc_frame *fp)
अणु
	mutex_lock(&lport->lp_mutex);

	/*
	 * Handle special ELS हालs like FLOGI, LOGO, and
	 * RSCN here.  These करोn't require a session.
	 * Even अगर we had a session, it might not be पढ़ोy.
	 */
	अगर (!lport->link_up)
		fc_frame_मुक्त(fp);
	अन्यथा अणु
		/*
		 * Check opcode.
		 */
		चयन (fc_frame_payload_op(fp)) अणु
		हाल ELS_FLOGI:
			अगर (!lport->poपूर्णांक_to_multipoपूर्णांक)
				fc_lport_recv_flogi_req(lport, fp);
			अन्यथा
				fc_rport_recv_req(lport, fp);
			अवरोध;
		हाल ELS_LOGO:
			अगर (fc_frame_sid(fp) == FC_FID_FLOGI)
				fc_lport_recv_logo_req(lport, fp);
			अन्यथा
				fc_rport_recv_req(lport, fp);
			अवरोध;
		हाल ELS_RSCN:
			lport->tt.disc_recv_req(lport, fp);
			अवरोध;
		हाल ELS_ECHO:
			fc_lport_recv_echo_req(lport, fp);
			अवरोध;
		हाल ELS_RLIR:
			fc_lport_recv_rlir_req(lport, fp);
			अवरोध;
		हाल ELS_RNID:
			fc_lport_recv_rnid_req(lport, fp);
			अवरोध;
		शेष:
			fc_rport_recv_req(lport, fp);
			अवरोध;
		पूर्ण
	पूर्ण
	mutex_unlock(&lport->lp_mutex);
पूर्ण

अटल पूर्णांक fc_lport_els_prli(काष्ठा fc_rport_priv *rdata, u32 spp_len,
			     स्थिर काष्ठा fc_els_spp *spp_in,
			     काष्ठा fc_els_spp *spp_out)
अणु
	वापस FC_SPP_RESP_INVL;
पूर्ण

काष्ठा fc4_prov fc_lport_els_prov = अणु
	.prli = fc_lport_els_prli,
	.recv = fc_lport_recv_els_req,
पूर्ण;

/**
 * fc_lport_recv() - The generic lport request handler
 * @lport: The lport that received the request
 * @fp: The frame the request is in
 *
 * Locking Note: This function should not be called with the lport
 *		 lock held because it may grab the lock.
 */
व्योम fc_lport_recv(काष्ठा fc_lport *lport, काष्ठा fc_frame *fp)
अणु
	काष्ठा fc_frame_header *fh = fc_frame_header_get(fp);
	काष्ठा fc_seq *sp = fr_seq(fp);
	काष्ठा fc4_prov *prov;

	/*
	 * Use RCU पढ़ो lock and module_lock to be sure module करोesn't
	 * deरेजिस्टर and get unloaded जबतक we're calling it.
	 * try_module_get() is अंतरभूतd and accepts a शून्य parameter.
	 * Only ELSes and FCP target ops should come through here.
	 * The locking is unक्रमtunate, and a better scheme is being sought.
	 */

	rcu_पढ़ो_lock();
	अगर (fh->fh_type >= FC_FC4_PROV_SIZE)
		जाओ drop;
	prov = rcu_dereference(fc_passive_prov[fh->fh_type]);
	अगर (!prov || !try_module_get(prov->module))
		जाओ drop;
	rcu_पढ़ो_unlock();
	prov->recv(lport, fp);
	module_put(prov->module);
	वापस;
drop:
	rcu_पढ़ो_unlock();
	FC_LPORT_DBG(lport, "dropping unexpected frame type %x\n", fh->fh_type);
	fc_frame_मुक्त(fp);
	अगर (sp)
		fc_exch_करोne(sp);
पूर्ण
EXPORT_SYMBOL(fc_lport_recv);

/**
 * fc_lport_reset() - Reset a local port
 * @lport: The local port which should be reset
 *
 * Locking Note: This functions should not be called with the
 *		 lport lock held.
 */
पूर्णांक fc_lport_reset(काष्ठा fc_lport *lport)
अणु
	cancel_delayed_work_sync(&lport->retry_work);
	mutex_lock(&lport->lp_mutex);
	fc_lport_enter_reset(lport);
	mutex_unlock(&lport->lp_mutex);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(fc_lport_reset);

/**
 * fc_lport_reset_locked() - Reset the local port w/ the lport lock held
 * @lport: The local port to be reset
 */
अटल व्योम fc_lport_reset_locked(काष्ठा fc_lport *lport)
अणु
	lockdep_निश्चित_held(&lport->lp_mutex);

	अगर (lport->dns_rdata) अणु
		fc_rport_logoff(lport->dns_rdata);
		lport->dns_rdata = शून्य;
	पूर्ण

	अगर (lport->ptp_rdata) अणु
		fc_rport_logoff(lport->ptp_rdata);
		kref_put(&lport->ptp_rdata->kref, fc_rport_destroy);
		lport->ptp_rdata = शून्य;
	पूर्ण

	lport->tt.disc_stop(lport);

	lport->tt.exch_mgr_reset(lport, 0, 0);
	fc_host_fabric_name(lport->host) = 0;

	अगर (lport->port_id && (!lport->poपूर्णांक_to_multipoपूर्णांक || !lport->link_up))
		fc_lport_set_port_id(lport, 0, शून्य);
पूर्ण

/**
 * fc_lport_enter_reset() - Reset the local port
 * @lport: The local port to be reset
 */
अटल व्योम fc_lport_enter_reset(काष्ठा fc_lport *lport)
अणु
	lockdep_निश्चित_held(&lport->lp_mutex);

	FC_LPORT_DBG(lport, "Entered RESET state from %s state\n",
		     fc_lport_state(lport));

	अगर (lport->state == LPORT_ST_DISABLED || lport->state == LPORT_ST_LOGO)
		वापस;

	अगर (lport->vport) अणु
		अगर (lport->link_up)
			fc_vport_set_state(lport->vport, FC_VPORT_INITIALIZING);
		अन्यथा
			fc_vport_set_state(lport->vport, FC_VPORT_LINKDOWN);
	पूर्ण
	fc_lport_state_enter(lport, LPORT_ST_RESET);
	fc_host_post_event(lport->host, fc_get_event_number(),
			   FCH_EVT_LIPRESET, 0);
	fc_vports_linkchange(lport);
	fc_lport_reset_locked(lport);
	अगर (lport->link_up)
		fc_lport_enter_flogi(lport);
पूर्ण

/**
 * fc_lport_enter_disabled() - Disable the local port
 * @lport: The local port to be reset
 */
अटल व्योम fc_lport_enter_disabled(काष्ठा fc_lport *lport)
अणु
	lockdep_निश्चित_held(&lport->lp_mutex);

	FC_LPORT_DBG(lport, "Entered disabled state from %s state\n",
		     fc_lport_state(lport));

	fc_lport_state_enter(lport, LPORT_ST_DISABLED);
	fc_vports_linkchange(lport);
	fc_lport_reset_locked(lport);
पूर्ण

/**
 * fc_lport_error() - Handler क्रम any errors
 * @lport: The local port that the error was on
 * @fp:	   The error code encoded in a frame poपूर्णांकer
 *
 * If the error was caused by a resource allocation failure
 * then रुको क्रम half a second and retry, otherwise retry
 * after the e_d_tov समय.
 */
अटल व्योम fc_lport_error(काष्ठा fc_lport *lport, काष्ठा fc_frame *fp)
अणु
	अचिन्हित दीर्घ delay = 0;
	FC_LPORT_DBG(lport, "Error %ld in state %s, retries %d\n",
		     IS_ERR(fp) ? -PTR_ERR(fp) : 0, fc_lport_state(lport),
		     lport->retry_count);

	अगर (PTR_ERR(fp) == -FC_EX_CLOSED)
		वापस;

	/*
	 * Memory allocation failure, or the exchange समयd out
	 * or we received LS_RJT.
	 * Retry after delay
	 */
	अगर (lport->retry_count < lport->max_retry_count) अणु
		lport->retry_count++;
		अगर (!fp)
			delay = msecs_to_jअगरfies(500);
		अन्यथा
			delay =	msecs_to_jअगरfies(lport->e_d_tov);

		schedule_delayed_work(&lport->retry_work, delay);
	पूर्ण अन्यथा
		fc_lport_enter_reset(lport);
पूर्ण

/**
 * fc_lport_ns_resp() - Handle response to a name server
 *			registration exchange
 * @sp:	    current sequence in exchange
 * @fp:	    response frame
 * @lp_arg: Fibre Channel host port instance
 *
 * Locking Note: This function will be called without the lport lock
 * held, but it will lock, call an _enter_* function or fc_lport_error()
 * and then unlock the lport.
 */
अटल व्योम fc_lport_ns_resp(काष्ठा fc_seq *sp, काष्ठा fc_frame *fp,
			     व्योम *lp_arg)
अणु
	काष्ठा fc_lport *lport = lp_arg;
	काष्ठा fc_frame_header *fh;
	काष्ठा fc_ct_hdr *ct;

	FC_LPORT_DBG(lport, "Received a ns %s\n", fc_els_resp_type(fp));

	अगर (fp == ERR_PTR(-FC_EX_CLOSED))
		वापस;

	mutex_lock(&lport->lp_mutex);

	अगर (lport->state < LPORT_ST_RNN_ID || lport->state > LPORT_ST_RFF_ID) अणु
		FC_LPORT_DBG(lport, "Received a name server response, "
			     "but in state %s\n", fc_lport_state(lport));
		अगर (IS_ERR(fp))
			जाओ err;
		जाओ out;
	पूर्ण

	अगर (IS_ERR(fp)) अणु
		fc_lport_error(lport, fp);
		जाओ err;
	पूर्ण

	fh = fc_frame_header_get(fp);
	ct = fc_frame_payload_get(fp, माप(*ct));

	अगर (fh && ct && fh->fh_type == FC_TYPE_CT &&
	    ct->ct_fs_type == FC_FST_सूची &&
	    ct->ct_fs_subtype == FC_NS_SUBTYPE &&
	    ntohs(ct->ct_cmd) == FC_FS_ACC)
		चयन (lport->state) अणु
		हाल LPORT_ST_RNN_ID:
			fc_lport_enter_ns(lport, LPORT_ST_RSNN_NN);
			अवरोध;
		हाल LPORT_ST_RSNN_NN:
			fc_lport_enter_ns(lport, LPORT_ST_RSPN_ID);
			अवरोध;
		हाल LPORT_ST_RSPN_ID:
			fc_lport_enter_ns(lport, LPORT_ST_RFT_ID);
			अवरोध;
		हाल LPORT_ST_RFT_ID:
			fc_lport_enter_ns(lport, LPORT_ST_RFF_ID);
			अवरोध;
		हाल LPORT_ST_RFF_ID:
			अगर (lport->fdmi_enabled)
				fc_lport_enter_fdmi(lport);
			अन्यथा
				fc_lport_enter_scr(lport);
			अवरोध;
		शेष:
			/* should have alपढ़ोy been caught by state checks */
			अवरोध;
		पूर्ण
	अन्यथा
		fc_lport_error(lport, fp);
out:
	fc_frame_मुक्त(fp);
err:
	mutex_unlock(&lport->lp_mutex);
पूर्ण

/**
 * fc_lport_ms_resp() - Handle response to a management server
 *			exchange
 * @sp:	    current sequence in exchange
 * @fp:	    response frame
 * @lp_arg: Fibre Channel host port instance
 *
 * Locking Note: This function will be called without the lport lock
 * held, but it will lock, call an _enter_* function or fc_lport_error()
 * and then unlock the lport.
 */
अटल व्योम fc_lport_ms_resp(काष्ठा fc_seq *sp, काष्ठा fc_frame *fp,
			     व्योम *lp_arg)
अणु
	काष्ठा fc_lport *lport = lp_arg;
	काष्ठा fc_frame_header *fh;
	काष्ठा fc_ct_hdr *ct;

	FC_LPORT_DBG(lport, "Received a ms %s\n", fc_els_resp_type(fp));

	अगर (fp == ERR_PTR(-FC_EX_CLOSED))
		वापस;

	mutex_lock(&lport->lp_mutex);

	अगर (lport->state < LPORT_ST_RHBA || lport->state > LPORT_ST_DPRT) अणु
		FC_LPORT_DBG(lport, "Received a management server response, "
			     "but in state %s\n", fc_lport_state(lport));
		अगर (IS_ERR(fp))
			जाओ err;
		जाओ out;
	पूर्ण

	अगर (IS_ERR(fp)) अणु
		fc_lport_error(lport, fp);
		जाओ err;
	पूर्ण

	fh = fc_frame_header_get(fp);
	ct = fc_frame_payload_get(fp, माप(*ct));

	अगर (fh && ct && fh->fh_type == FC_TYPE_CT &&
	    ct->ct_fs_type == FC_FST_MGMT &&
	    ct->ct_fs_subtype == FC_FDMI_SUBTYPE) अणु
		FC_LPORT_DBG(lport, "Received a management server response, "
				    "reason=%d explain=%d\n",
				    ct->ct_reason,
				    ct->ct_explan);

		चयन (lport->state) अणु
		हाल LPORT_ST_RHBA:
			अगर (ntohs(ct->ct_cmd) == FC_FS_ACC)
				fc_lport_enter_ms(lport, LPORT_ST_RPA);
			अन्यथा /* Error Skip RPA */
				fc_lport_enter_scr(lport);
			अवरोध;
		हाल LPORT_ST_RPA:
			fc_lport_enter_scr(lport);
			अवरोध;
		हाल LPORT_ST_DPRT:
			fc_lport_enter_ms(lport, LPORT_ST_RHBA);
			अवरोध;
		हाल LPORT_ST_DHBA:
			fc_lport_enter_ms(lport, LPORT_ST_DPRT);
			अवरोध;
		शेष:
			/* should have alपढ़ोy been caught by state checks */
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Invalid Frame? */
		fc_lport_error(lport, fp);
	पूर्ण
out:
	fc_frame_मुक्त(fp);
err:
	mutex_unlock(&lport->lp_mutex);
पूर्ण

/**
 * fc_lport_scr_resp() - Handle response to State Change Register (SCR) request
 * @sp:	    current sequence in SCR exchange
 * @fp:	    response frame
 * @lp_arg: Fibre Channel lport port instance that sent the registration request
 *
 * Locking Note: This function will be called without the lport lock
 * held, but it will lock, call an _enter_* function or fc_lport_error
 * and then unlock the lport.
 */
अटल व्योम fc_lport_scr_resp(काष्ठा fc_seq *sp, काष्ठा fc_frame *fp,
			      व्योम *lp_arg)
अणु
	काष्ठा fc_lport *lport = lp_arg;
	u8 op;

	FC_LPORT_DBG(lport, "Received a SCR %s\n", fc_els_resp_type(fp));

	अगर (fp == ERR_PTR(-FC_EX_CLOSED))
		वापस;

	mutex_lock(&lport->lp_mutex);

	अगर (lport->state != LPORT_ST_SCR) अणु
		FC_LPORT_DBG(lport, "Received a SCR response, but in state "
			     "%s\n", fc_lport_state(lport));
		अगर (IS_ERR(fp))
			जाओ err;
		जाओ out;
	पूर्ण

	अगर (IS_ERR(fp)) अणु
		fc_lport_error(lport, fp);
		जाओ err;
	पूर्ण

	op = fc_frame_payload_op(fp);
	अगर (op == ELS_LS_ACC)
		fc_lport_enter_पढ़ोy(lport);
	अन्यथा
		fc_lport_error(lport, fp);

out:
	fc_frame_मुक्त(fp);
err:
	mutex_unlock(&lport->lp_mutex);
पूर्ण

/**
 * fc_lport_enter_scr() - Send a SCR (State Change Register) request
 * @lport: The local port to रेजिस्टर क्रम state changes
 */
अटल व्योम fc_lport_enter_scr(काष्ठा fc_lport *lport)
अणु
	काष्ठा fc_frame *fp;

	lockdep_निश्चित_held(&lport->lp_mutex);

	FC_LPORT_DBG(lport, "Entered SCR state from %s state\n",
		     fc_lport_state(lport));

	fc_lport_state_enter(lport, LPORT_ST_SCR);

	fp = fc_frame_alloc(lport, माप(काष्ठा fc_els_scr));
	अगर (!fp) अणु
		fc_lport_error(lport, fp);
		वापस;
	पूर्ण

	अगर (!lport->tt.elsct_send(lport, FC_FID_FCTRL, fp, ELS_SCR,
				  fc_lport_scr_resp, lport,
				  2 * lport->r_a_tov))
		fc_lport_error(lport, शून्य);
पूर्ण

/**
 * fc_lport_enter_ns() - रेजिस्टर some object with the name server
 * @lport: Fibre Channel local port to रेजिस्टर
 * @state: Local port state
 */
अटल व्योम fc_lport_enter_ns(काष्ठा fc_lport *lport, क्रमागत fc_lport_state state)
अणु
	काष्ठा fc_frame *fp;
	क्रमागत fc_ns_req cmd;
	पूर्णांक size = माप(काष्ठा fc_ct_hdr);
	माप_प्रकार len;

	lockdep_निश्चित_held(&lport->lp_mutex);

	FC_LPORT_DBG(lport, "Entered %s state from %s state\n",
		     fc_lport_state_names[state],
		     fc_lport_state(lport));

	fc_lport_state_enter(lport, state);

	चयन (state) अणु
	हाल LPORT_ST_RNN_ID:
		cmd = FC_NS_RNN_ID;
		size += माप(काष्ठा fc_ns_rn_id);
		अवरोध;
	हाल LPORT_ST_RSNN_NN:
		len = strnlen(fc_host_symbolic_name(lport->host), 255);
		/* अगर there is no symbolic name, skip to RFT_ID */
		अगर (!len)
			वापस fc_lport_enter_ns(lport, LPORT_ST_RFT_ID);
		cmd = FC_NS_RSNN_NN;
		size += माप(काष्ठा fc_ns_rsnn) + len;
		अवरोध;
	हाल LPORT_ST_RSPN_ID:
		len = strnlen(fc_host_symbolic_name(lport->host), 255);
		/* अगर there is no symbolic name, skip to RFT_ID */
		अगर (!len)
			वापस fc_lport_enter_ns(lport, LPORT_ST_RFT_ID);
		cmd = FC_NS_RSPN_ID;
		size += माप(काष्ठा fc_ns_rspn) + len;
		अवरोध;
	हाल LPORT_ST_RFT_ID:
		cmd = FC_NS_RFT_ID;
		size += माप(काष्ठा fc_ns_rft);
		अवरोध;
	हाल LPORT_ST_RFF_ID:
		cmd = FC_NS_RFF_ID;
		size += माप(काष्ठा fc_ns_rff_id);
		अवरोध;
	शेष:
		fc_lport_error(lport, शून्य);
		वापस;
	पूर्ण

	fp = fc_frame_alloc(lport, size);
	अगर (!fp) अणु
		fc_lport_error(lport, fp);
		वापस;
	पूर्ण

	अगर (!lport->tt.elsct_send(lport, FC_FID_सूची_SERV, fp, cmd,
				  fc_lport_ns_resp,
				  lport, 3 * lport->r_a_tov))
		fc_lport_error(lport, fp);
पूर्ण

अटल काष्ठा fc_rport_operations fc_lport_rport_ops = अणु
	.event_callback = fc_lport_rport_callback,
पूर्ण;

/**
 * fc_lport_enter_dns() - Create a fc_rport क्रम the name server
 * @lport: The local port requesting a remote port क्रम the name server
 */
अटल व्योम fc_lport_enter_dns(काष्ठा fc_lport *lport)
अणु
	काष्ठा fc_rport_priv *rdata;

	lockdep_निश्चित_held(&lport->lp_mutex);

	FC_LPORT_DBG(lport, "Entered DNS state from %s state\n",
		     fc_lport_state(lport));

	fc_lport_state_enter(lport, LPORT_ST_DNS);

	mutex_lock(&lport->disc.disc_mutex);
	rdata = fc_rport_create(lport, FC_FID_सूची_SERV);
	mutex_unlock(&lport->disc.disc_mutex);
	अगर (!rdata)
		जाओ err;

	rdata->ops = &fc_lport_rport_ops;
	fc_rport_login(rdata);
	वापस;

err:
	fc_lport_error(lport, शून्य);
पूर्ण

/**
 * fc_lport_enter_ms() - management server commands
 * @lport: Fibre Channel local port to रेजिस्टर
 * @state: Local port state
 */
अटल व्योम fc_lport_enter_ms(काष्ठा fc_lport *lport, क्रमागत fc_lport_state state)
अणु
	काष्ठा fc_frame *fp;
	क्रमागत fc_fdmi_req cmd;
	पूर्णांक size = माप(काष्ठा fc_ct_hdr);
	माप_प्रकार len;
	पूर्णांक numattrs;

	lockdep_निश्चित_held(&lport->lp_mutex);

	FC_LPORT_DBG(lport, "Entered %s state from %s state\n",
		     fc_lport_state_names[state],
		     fc_lport_state(lport));

	fc_lport_state_enter(lport, state);

	चयन (state) अणु
	हाल LPORT_ST_RHBA:
		cmd = FC_FDMI_RHBA;
		/* Number of HBA Attributes */
		numattrs = 10;
		len = माप(काष्ठा fc_fdmi_rhba);
		len -= माप(काष्ठा fc_fdmi_attr_entry);
		len += (numattrs * FC_FDMI_ATTR_ENTRY_HEADER_LEN);
		len += FC_FDMI_HBA_ATTR_NODENAME_LEN;
		len += FC_FDMI_HBA_ATTR_MANUFACTURER_LEN;
		len += FC_FDMI_HBA_ATTR_SERIALNUMBER_LEN;
		len += FC_FDMI_HBA_ATTR_MODEL_LEN;
		len += FC_FDMI_HBA_ATTR_MODELDESCR_LEN;
		len += FC_FDMI_HBA_ATTR_HARDWAREVERSION_LEN;
		len += FC_FDMI_HBA_ATTR_DRIVERVERSION_LEN;
		len += FC_FDMI_HBA_ATTR_OPTIONROMVERSION_LEN;
		len += FC_FDMI_HBA_ATTR_FIRMWAREVERSION_LEN;
		len += FC_FDMI_HBA_ATTR_OSNAMEVERSION_LEN;

		size += len;
		अवरोध;
	हाल LPORT_ST_RPA:
		cmd = FC_FDMI_RPA;
		/* Number of Port Attributes */
		numattrs = 6;
		len = माप(काष्ठा fc_fdmi_rpa);
		len -= माप(काष्ठा fc_fdmi_attr_entry);
		len += (numattrs * FC_FDMI_ATTR_ENTRY_HEADER_LEN);
		len += FC_FDMI_PORT_ATTR_FC4TYPES_LEN;
		len += FC_FDMI_PORT_ATTR_SUPPORTEDSPEED_LEN;
		len += FC_FDMI_PORT_ATTR_CURRENTPORTSPEED_LEN;
		len += FC_FDMI_PORT_ATTR_MAXFRAMESIZE_LEN;
		len += FC_FDMI_PORT_ATTR_OSDEVICENAME_LEN;
		len += FC_FDMI_PORT_ATTR_HOSTNAME_LEN;

		size += len;
		अवरोध;
	हाल LPORT_ST_DPRT:
		cmd = FC_FDMI_DPRT;
		len = माप(काष्ठा fc_fdmi_dprt);
		size += len;
		अवरोध;
	हाल LPORT_ST_DHBA:
		cmd = FC_FDMI_DHBA;
		len = माप(काष्ठा fc_fdmi_dhba);
		size += len;
		अवरोध;
	शेष:
		fc_lport_error(lport, शून्य);
		वापस;
	पूर्ण

	FC_LPORT_DBG(lport, "Cmd=0x%x Len %d size %d\n",
			     cmd, (पूर्णांक)len, size);
	fp = fc_frame_alloc(lport, size);
	अगर (!fp) अणु
		fc_lport_error(lport, fp);
		वापस;
	पूर्ण

	अगर (!lport->tt.elsct_send(lport, FC_FID_MGMT_SERV, fp, cmd,
				  fc_lport_ms_resp,
				  lport, 3 * lport->r_a_tov))
		fc_lport_error(lport, fp);
पूर्ण

/**
 * fc_lport_enter_fdmi() - Create a fc_rport क्रम the management server
 * @lport: The local port requesting a remote port क्रम the management server
 */
अटल व्योम fc_lport_enter_fdmi(काष्ठा fc_lport *lport)
अणु
	काष्ठा fc_rport_priv *rdata;

	lockdep_निश्चित_held(&lport->lp_mutex);

	FC_LPORT_DBG(lport, "Entered FDMI state from %s state\n",
		     fc_lport_state(lport));

	fc_lport_state_enter(lport, LPORT_ST_FDMI);

	mutex_lock(&lport->disc.disc_mutex);
	rdata = fc_rport_create(lport, FC_FID_MGMT_SERV);
	mutex_unlock(&lport->disc.disc_mutex);
	अगर (!rdata)
		जाओ err;

	rdata->ops = &fc_lport_rport_ops;
	fc_rport_login(rdata);
	वापस;

err:
	fc_lport_error(lport, शून्य);
पूर्ण

/**
 * fc_lport_समयout() - Handler क्रम the retry_work समयr
 * @work: The work काष्ठा of the local port
 */
अटल व्योम fc_lport_समयout(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा fc_lport *lport =
		container_of(work, काष्ठा fc_lport,
			     retry_work.work);

	mutex_lock(&lport->lp_mutex);

	चयन (lport->state) अणु
	हाल LPORT_ST_DISABLED:
		अवरोध;
	हाल LPORT_ST_READY:
		अवरोध;
	हाल LPORT_ST_RESET:
		अवरोध;
	हाल LPORT_ST_FLOGI:
		fc_lport_enter_flogi(lport);
		अवरोध;
	हाल LPORT_ST_DNS:
		fc_lport_enter_dns(lport);
		अवरोध;
	हाल LPORT_ST_RNN_ID:
	हाल LPORT_ST_RSNN_NN:
	हाल LPORT_ST_RSPN_ID:
	हाल LPORT_ST_RFT_ID:
	हाल LPORT_ST_RFF_ID:
		fc_lport_enter_ns(lport, lport->state);
		अवरोध;
	हाल LPORT_ST_FDMI:
		fc_lport_enter_fdmi(lport);
		अवरोध;
	हाल LPORT_ST_RHBA:
	हाल LPORT_ST_RPA:
	हाल LPORT_ST_DHBA:
	हाल LPORT_ST_DPRT:
		FC_LPORT_DBG(lport, "Skipping lport state %s to SCR\n",
			     fc_lport_state(lport));
		fallthrough;
	हाल LPORT_ST_SCR:
		fc_lport_enter_scr(lport);
		अवरोध;
	हाल LPORT_ST_LOGO:
		fc_lport_enter_logo(lport);
		अवरोध;
	पूर्ण

	mutex_unlock(&lport->lp_mutex);
पूर्ण

/**
 * fc_lport_logo_resp() - Handle response to LOGO request
 * @sp:	    The sequence that the LOGO was on
 * @fp:	    The LOGO frame
 * @lp_arg: The lport port that received the LOGO request
 *
 * Locking Note: This function will be called without the lport lock
 * held, but it will lock, call an _enter_* function or fc_lport_error()
 * and then unlock the lport.
 */
व्योम fc_lport_logo_resp(काष्ठा fc_seq *sp, काष्ठा fc_frame *fp,
			व्योम *lp_arg)
अणु
	काष्ठा fc_lport *lport = lp_arg;
	u8 op;

	FC_LPORT_DBG(lport, "Received a LOGO %s\n", fc_els_resp_type(fp));

	अगर (fp == ERR_PTR(-FC_EX_CLOSED))
		वापस;

	mutex_lock(&lport->lp_mutex);

	अगर (lport->state != LPORT_ST_LOGO) अणु
		FC_LPORT_DBG(lport, "Received a LOGO response, but in state "
			     "%s\n", fc_lport_state(lport));
		अगर (IS_ERR(fp))
			जाओ err;
		जाओ out;
	पूर्ण

	अगर (IS_ERR(fp)) अणु
		fc_lport_error(lport, fp);
		जाओ err;
	पूर्ण

	op = fc_frame_payload_op(fp);
	अगर (op == ELS_LS_ACC)
		fc_lport_enter_disabled(lport);
	अन्यथा
		fc_lport_error(lport, fp);

out:
	fc_frame_मुक्त(fp);
err:
	mutex_unlock(&lport->lp_mutex);
पूर्ण
EXPORT_SYMBOL(fc_lport_logo_resp);

/**
 * fc_lport_enter_logo() - Logout of the fabric
 * @lport: The local port to be logged out
 */
अटल व्योम fc_lport_enter_logo(काष्ठा fc_lport *lport)
अणु
	काष्ठा fc_frame *fp;
	काष्ठा fc_els_logo *logo;

	lockdep_निश्चित_held(&lport->lp_mutex);

	FC_LPORT_DBG(lport, "Entered LOGO state from %s state\n",
		     fc_lport_state(lport));

	fc_lport_state_enter(lport, LPORT_ST_LOGO);
	fc_vports_linkchange(lport);

	fp = fc_frame_alloc(lport, माप(*logo));
	अगर (!fp) अणु
		fc_lport_error(lport, fp);
		वापस;
	पूर्ण

	अगर (!lport->tt.elsct_send(lport, FC_FID_FLOGI, fp, ELS_LOGO,
				  fc_lport_logo_resp, lport,
				  2 * lport->r_a_tov))
		fc_lport_error(lport, शून्य);
पूर्ण

/**
 * fc_lport_flogi_resp() - Handle response to FLOGI request
 * @sp:	    The sequence that the FLOGI was on
 * @fp:	    The FLOGI response frame
 * @lp_arg: The lport port that received the FLOGI response
 *
 * Locking Note: This function will be called without the lport lock
 * held, but it will lock, call an _enter_* function or fc_lport_error()
 * and then unlock the lport.
 */
व्योम fc_lport_flogi_resp(काष्ठा fc_seq *sp, काष्ठा fc_frame *fp,
			 व्योम *lp_arg)
अणु
	काष्ठा fc_lport *lport = lp_arg;
	काष्ठा fc_frame_header *fh;
	काष्ठा fc_els_flogi *flp;
	u32 did;
	u16 csp_flags;
	अचिन्हित पूर्णांक r_a_tov;
	अचिन्हित पूर्णांक e_d_tov;
	u16 mfs;

	FC_LPORT_DBG(lport, "Received a FLOGI %s\n", fc_els_resp_type(fp));

	अगर (fp == ERR_PTR(-FC_EX_CLOSED))
		वापस;

	mutex_lock(&lport->lp_mutex);

	अगर (lport->state != LPORT_ST_FLOGI) अणु
		FC_LPORT_DBG(lport, "Received a FLOGI response, but in state "
			     "%s\n", fc_lport_state(lport));
		अगर (IS_ERR(fp))
			जाओ err;
		जाओ out;
	पूर्ण

	अगर (IS_ERR(fp)) अणु
		fc_lport_error(lport, fp);
		जाओ err;
	पूर्ण

	fh = fc_frame_header_get(fp);
	did = fc_frame_did(fp);
	अगर (fh->fh_r_ctl != FC_RCTL_ELS_REP || did == 0 ||
	    fc_frame_payload_op(fp) != ELS_LS_ACC) अणु
		FC_LPORT_DBG(lport, "FLOGI not accepted or bad response\n");
		fc_lport_error(lport, fp);
		जाओ out;
	पूर्ण

	flp = fc_frame_payload_get(fp, माप(*flp));
	अगर (!flp) अणु
		FC_LPORT_DBG(lport, "FLOGI bad response\n");
		fc_lport_error(lport, fp);
		जाओ out;
	पूर्ण

	mfs = ntohs(flp->fl_csp.sp_bb_data) &
		FC_SP_BB_DATA_MASK;

	अगर (mfs < FC_SP_MIN_MAX_PAYLOAD || mfs > FC_SP_MAX_MAX_PAYLOAD) अणु
		FC_LPORT_DBG(lport, "FLOGI bad mfs:%hu response, "
			     "lport->mfs:%u\n", mfs, lport->mfs);
		fc_lport_error(lport, fp);
		जाओ out;
	पूर्ण

	अगर (mfs <= lport->mfs) अणु
		lport->mfs = mfs;
		fc_host_maxframe_size(lport->host) = mfs;
	पूर्ण

	csp_flags = ntohs(flp->fl_csp.sp_features);
	r_a_tov = ntohl(flp->fl_csp.sp_r_a_tov);
	e_d_tov = ntohl(flp->fl_csp.sp_e_d_tov);
	अगर (csp_flags & FC_SP_FT_EDTR)
		e_d_tov /= 1000000;

	lport->npiv_enabled = !!(csp_flags & FC_SP_FT_NPIV_ACC);

	अगर ((csp_flags & FC_SP_FT_FPORT) == 0) अणु
		अगर (e_d_tov > lport->e_d_tov)
			lport->e_d_tov = e_d_tov;
		lport->r_a_tov = 2 * lport->e_d_tov;
		fc_lport_set_port_id(lport, did, fp);
		prपूर्णांकk(KERN_INFO "host%d: libfc: "
		       "Port (%6.6x) entered "
		       "point-to-point mode\n",
		       lport->host->host_no, did);
		fc_lport_ptp_setup(lport, fc_frame_sid(fp),
				   get_unaligned_be64(
					   &flp->fl_wwpn),
				   get_unaligned_be64(
					   &flp->fl_wwnn));
	पूर्ण अन्यथा अणु
		अगर (e_d_tov > lport->e_d_tov)
			lport->e_d_tov = e_d_tov;
		अगर (r_a_tov > lport->r_a_tov)
			lport->r_a_tov = r_a_tov;
		fc_host_fabric_name(lport->host) =
			get_unaligned_be64(&flp->fl_wwnn);
		fc_lport_set_port_id(lport, did, fp);
		fc_lport_enter_dns(lport);
	पूर्ण

out:
	fc_frame_मुक्त(fp);
err:
	mutex_unlock(&lport->lp_mutex);
पूर्ण
EXPORT_SYMBOL(fc_lport_flogi_resp);

/**
 * fc_lport_enter_flogi() - Send a FLOGI request to the fabric manager
 * @lport: Fibre Channel local port to be logged in to the fabric
 */
अटल व्योम fc_lport_enter_flogi(काष्ठा fc_lport *lport)
अणु
	काष्ठा fc_frame *fp;

	lockdep_निश्चित_held(&lport->lp_mutex);

	FC_LPORT_DBG(lport, "Entered FLOGI state from %s state\n",
		     fc_lport_state(lport));

	fc_lport_state_enter(lport, LPORT_ST_FLOGI);

	अगर (lport->poपूर्णांक_to_multipoपूर्णांक) अणु
		अगर (lport->port_id)
			fc_lport_enter_पढ़ोy(lport);
		वापस;
	पूर्ण

	fp = fc_frame_alloc(lport, माप(काष्ठा fc_els_flogi));
	अगर (!fp)
		वापस fc_lport_error(lport, fp);

	अगर (!lport->tt.elsct_send(lport, FC_FID_FLOGI, fp,
				  lport->vport ? ELS_FDISC : ELS_FLOGI,
				  fc_lport_flogi_resp, lport,
				  lport->vport ? 2 * lport->r_a_tov :
				  lport->e_d_tov))
		fc_lport_error(lport, शून्य);
पूर्ण

/**
 * fc_lport_config() - Configure a fc_lport
 * @lport: The local port to be configured
 */
पूर्णांक fc_lport_config(काष्ठा fc_lport *lport)
अणु
	INIT_DELAYED_WORK(&lport->retry_work, fc_lport_समयout);
	mutex_init(&lport->lp_mutex);

	fc_lport_state_enter(lport, LPORT_ST_DISABLED);

	fc_lport_add_fc4_type(lport, FC_TYPE_FCP);
	fc_lport_add_fc4_type(lport, FC_TYPE_CT);
	fc_fc4_conf_lport_params(lport, FC_TYPE_FCP);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(fc_lport_config);

/**
 * fc_lport_init() - Initialize the lport layer क्रम a local port
 * @lport: The local port to initialize the exchange layer क्रम
 */
पूर्णांक fc_lport_init(काष्ठा fc_lport *lport)
अणु
	fc_host_port_type(lport->host) = FC_PORTTYPE_NPORT;
	fc_host_node_name(lport->host) = lport->wwnn;
	fc_host_port_name(lport->host) = lport->wwpn;
	fc_host_supported_classes(lport->host) = FC_COS_CLASS3;
	स_रखो(fc_host_supported_fc4s(lport->host), 0,
	       माप(fc_host_supported_fc4s(lport->host)));
	fc_host_supported_fc4s(lport->host)[2] = 1;
	fc_host_supported_fc4s(lport->host)[7] = 1;

	/* This value is also unchanging */
	स_रखो(fc_host_active_fc4s(lport->host), 0,
	       माप(fc_host_active_fc4s(lport->host)));
	fc_host_active_fc4s(lport->host)[2] = 1;
	fc_host_active_fc4s(lport->host)[7] = 1;
	fc_host_maxframe_size(lport->host) = lport->mfs;
	fc_host_supported_speeds(lport->host) = 0;
	अगर (lport->link_supported_speeds & FC_PORTSPEED_1GBIT)
		fc_host_supported_speeds(lport->host) |= FC_PORTSPEED_1GBIT;
	अगर (lport->link_supported_speeds & FC_PORTSPEED_10GBIT)
		fc_host_supported_speeds(lport->host) |= FC_PORTSPEED_10GBIT;
	fc_fc4_add_lport(lport);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(fc_lport_init);

/**
 * fc_lport_bsg_resp() - The common response handler क्रम FC Passthrough requests
 * @sp:	      The sequence क्रम the FC Passthrough response
 * @fp:	      The response frame
 * @info_arg: The BSG info that the response is क्रम
 */
अटल व्योम fc_lport_bsg_resp(काष्ठा fc_seq *sp, काष्ठा fc_frame *fp,
			      व्योम *info_arg)
अणु
	काष्ठा fc_bsg_info *info = info_arg;
	काष्ठा bsg_job *job = info->job;
	काष्ठा fc_bsg_reply *bsg_reply = job->reply;
	काष्ठा fc_lport *lport = info->lport;
	काष्ठा fc_frame_header *fh;
	माप_प्रकार len;
	व्योम *buf;

	अगर (IS_ERR(fp)) अणु
		bsg_reply->result = (PTR_ERR(fp) == -FC_EX_CLOSED) ?
			-ECONNABORTED : -ETIMEDOUT;
		job->reply_len = माप(uपूर्णांक32_t);
		bsg_job_करोne(job, bsg_reply->result,
			       bsg_reply->reply_payload_rcv_len);
		kमुक्त(info);
		वापस;
	पूर्ण

	mutex_lock(&lport->lp_mutex);
	fh = fc_frame_header_get(fp);
	len = fr_len(fp) - माप(*fh);
	buf = fc_frame_payload_get(fp, 0);

	अगर (fr_sof(fp) == FC_SOF_I3 && !ntohs(fh->fh_seq_cnt)) अणु
		/* Get the response code from the first frame payload */
		अचिन्हित लघु cmd = (info->rsp_code == FC_FS_ACC) ?
			ntohs(((काष्ठा fc_ct_hdr *)buf)->ct_cmd) :
			(अचिन्हित लघु)fc_frame_payload_op(fp);

		/* Save the reply status of the job */
		bsg_reply->reply_data.ctels_reply.status =
			(cmd == info->rsp_code) ?
			FC_CTELS_STATUS_OK : FC_CTELS_STATUS_REJECT;
	पूर्ण

	bsg_reply->reply_payload_rcv_len +=
		fc_copy_buffer_to_sglist(buf, len, info->sg, &info->nents,
					 &info->offset, शून्य);

	अगर (fr_eof(fp) == FC_खातापूर्ण_T &&
	    (ntoh24(fh->fh_f_ctl) & (FC_FC_LAST_SEQ | FC_FC_END_SEQ)) ==
	    (FC_FC_LAST_SEQ | FC_FC_END_SEQ)) अणु
		अगर (bsg_reply->reply_payload_rcv_len >
		    job->reply_payload.payload_len)
			bsg_reply->reply_payload_rcv_len =
				job->reply_payload.payload_len;
		bsg_reply->result = 0;
		bsg_job_करोne(job, bsg_reply->result,
			       bsg_reply->reply_payload_rcv_len);
		kमुक्त(info);
	पूर्ण
	fc_frame_मुक्त(fp);
	mutex_unlock(&lport->lp_mutex);
पूर्ण

/**
 * fc_lport_els_request() - Send ELS passthrough request
 * @job:   The BSG Passthrough job
 * @lport: The local port sending the request
 * @did:   The destination port id
 * @tov:   The समयout period (in ms)
 */
अटल पूर्णांक fc_lport_els_request(काष्ठा bsg_job *job,
				काष्ठा fc_lport *lport,
				u32 did, u32 tov)
अणु
	काष्ठा fc_bsg_info *info;
	काष्ठा fc_frame *fp;
	काष्ठा fc_frame_header *fh;
	अक्षर *pp;
	पूर्णांक len;

	lockdep_निश्चित_held(&lport->lp_mutex);

	fp = fc_frame_alloc(lport, job->request_payload.payload_len);
	अगर (!fp)
		वापस -ENOMEM;

	len = job->request_payload.payload_len;
	pp = fc_frame_payload_get(fp, len);

	sg_copy_to_buffer(job->request_payload.sg_list,
			  job->request_payload.sg_cnt,
			  pp, len);

	fh = fc_frame_header_get(fp);
	fh->fh_r_ctl = FC_RCTL_ELS_REQ;
	hton24(fh->fh_d_id, did);
	hton24(fh->fh_s_id, lport->port_id);
	fh->fh_type = FC_TYPE_ELS;
	hton24(fh->fh_f_ctl, FC_FCTL_REQ);
	fh->fh_cs_ctl = 0;
	fh->fh_df_ctl = 0;
	fh->fh_parm_offset = 0;

	info = kzalloc(माप(काष्ठा fc_bsg_info), GFP_KERNEL);
	अगर (!info) अणु
		fc_frame_मुक्त(fp);
		वापस -ENOMEM;
	पूर्ण

	info->job = job;
	info->lport = lport;
	info->rsp_code = ELS_LS_ACC;
	info->nents = job->reply_payload.sg_cnt;
	info->sg = job->reply_payload.sg_list;

	अगर (!fc_exch_seq_send(lport, fp, fc_lport_bsg_resp,
			      शून्य, info, tov)) अणु
		kमुक्त(info);
		वापस -ECOMM;
	पूर्ण
	वापस 0;
पूर्ण

/**
 * fc_lport_ct_request() - Send CT Passthrough request
 * @job:   The BSG Passthrough job
 * @lport: The local port sending the request
 * @did:   The destination FC-ID
 * @tov:   The समयout period to रुको क्रम the response
 */
अटल पूर्णांक fc_lport_ct_request(काष्ठा bsg_job *job,
			       काष्ठा fc_lport *lport, u32 did, u32 tov)
अणु
	काष्ठा fc_bsg_info *info;
	काष्ठा fc_frame *fp;
	काष्ठा fc_frame_header *fh;
	काष्ठा fc_ct_req *ct;
	माप_प्रकार len;

	lockdep_निश्चित_held(&lport->lp_mutex);

	fp = fc_frame_alloc(lport, माप(काष्ठा fc_ct_hdr) +
			    job->request_payload.payload_len);
	अगर (!fp)
		वापस -ENOMEM;

	len = job->request_payload.payload_len;
	ct = fc_frame_payload_get(fp, len);

	sg_copy_to_buffer(job->request_payload.sg_list,
			  job->request_payload.sg_cnt,
			  ct, len);

	fh = fc_frame_header_get(fp);
	fh->fh_r_ctl = FC_RCTL_DD_UNSOL_CTL;
	hton24(fh->fh_d_id, did);
	hton24(fh->fh_s_id, lport->port_id);
	fh->fh_type = FC_TYPE_CT;
	hton24(fh->fh_f_ctl, FC_FCTL_REQ);
	fh->fh_cs_ctl = 0;
	fh->fh_df_ctl = 0;
	fh->fh_parm_offset = 0;

	info = kzalloc(माप(काष्ठा fc_bsg_info), GFP_KERNEL);
	अगर (!info) अणु
		fc_frame_मुक्त(fp);
		वापस -ENOMEM;
	पूर्ण

	info->job = job;
	info->lport = lport;
	info->rsp_code = FC_FS_ACC;
	info->nents = job->reply_payload.sg_cnt;
	info->sg = job->reply_payload.sg_list;

	अगर (!fc_exch_seq_send(lport, fp, fc_lport_bsg_resp,
			      शून्य, info, tov)) अणु
		kमुक्त(info);
		वापस -ECOMM;
	पूर्ण
	वापस 0;
पूर्ण

/**
 * fc_lport_bsg_request() - The common entry poपूर्णांक क्रम sending
 *			    FC Passthrough requests
 * @job: The BSG passthrough job
 */
पूर्णांक fc_lport_bsg_request(काष्ठा bsg_job *job)
अणु
	काष्ठा fc_bsg_request *bsg_request = job->request;
	काष्ठा fc_bsg_reply *bsg_reply = job->reply;
	काष्ठा Scsi_Host *shost = fc_bsg_to_shost(job);
	काष्ठा fc_lport *lport = shost_priv(shost);
	काष्ठा fc_rport *rport;
	काष्ठा fc_rport_priv *rdata;
	पूर्णांक rc = -EINVAL;
	u32 did, tov;

	bsg_reply->reply_payload_rcv_len = 0;

	mutex_lock(&lport->lp_mutex);

	चयन (bsg_request->msgcode) अणु
	हाल FC_BSG_RPT_ELS:
		rport = fc_bsg_to_rport(job);
		अगर (!rport)
			अवरोध;

		rdata = rport->dd_data;
		rc = fc_lport_els_request(job, lport, rport->port_id,
					  rdata->e_d_tov);
		अवरोध;

	हाल FC_BSG_RPT_CT:
		rport = fc_bsg_to_rport(job);
		अगर (!rport)
			अवरोध;

		rdata = rport->dd_data;
		rc = fc_lport_ct_request(job, lport, rport->port_id,
					 rdata->e_d_tov);
		अवरोध;

	हाल FC_BSG_HST_CT:
		did = ntoh24(bsg_request->rqst_data.h_ct.port_id);
		अगर (did == FC_FID_सूची_SERV) अणु
			rdata = lport->dns_rdata;
			अगर (!rdata)
				अवरोध;
			tov = rdata->e_d_tov;
		पूर्ण अन्यथा अणु
			rdata = fc_rport_lookup(lport, did);
			अगर (!rdata)
				अवरोध;
			tov = rdata->e_d_tov;
			kref_put(&rdata->kref, fc_rport_destroy);
		पूर्ण

		rc = fc_lport_ct_request(job, lport, did, tov);
		अवरोध;

	हाल FC_BSG_HST_ELS_NOLOGIN:
		did = ntoh24(bsg_request->rqst_data.h_els.port_id);
		rc = fc_lport_els_request(job, lport, did, lport->e_d_tov);
		अवरोध;
	पूर्ण

	mutex_unlock(&lport->lp_mutex);
	वापस rc;
पूर्ण
EXPORT_SYMBOL(fc_lport_bsg_request);
