<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  QLogic FCoE Offload Driver
 *  Copyright (c) 2016-2018 Cavium Inc.
 */
#समावेश "qedf.h"

/* It's assumed that the lock is held when calling this function. */
अटल पूर्णांक qedf_initiate_els(काष्ठा qedf_rport *fcport, अचिन्हित पूर्णांक op,
	व्योम *data, uपूर्णांक32_t data_len,
	व्योम (*cb_func)(काष्ठा qedf_els_cb_arg *cb_arg),
	काष्ठा qedf_els_cb_arg *cb_arg, uपूर्णांक32_t समयr_msec)
अणु
	काष्ठा qedf_ctx *qedf;
	काष्ठा fc_lport *lport;
	काष्ठा qedf_ioreq *els_req;
	काष्ठा qedf_mp_req *mp_req;
	काष्ठा fc_frame_header *fc_hdr;
	काष्ठा e4_fcoe_task_context *task;
	पूर्णांक rc = 0;
	uपूर्णांक32_t did, sid;
	uपूर्णांक16_t xid;
	काष्ठा fcoe_wqe *sqe;
	अचिन्हित दीर्घ flags;
	u16 sqe_idx;

	अगर (!fcport) अणु
		QEDF_ERR(शून्य, "fcport is NULL");
		rc = -EINVAL;
		जाओ els_err;
	पूर्ण

	qedf = fcport->qedf;
	lport = qedf->lport;

	QEDF_INFO(&(qedf->dbg_ctx), QEDF_LOG_ELS, "Sending ELS\n");

	rc = fc_remote_port_chkपढ़ोy(fcport->rport);
	अगर (rc) अणु
		QEDF_ERR(&(qedf->dbg_ctx), "els 0x%x: rport not ready\n", op);
		rc = -EAGAIN;
		जाओ els_err;
	पूर्ण
	अगर (lport->state != LPORT_ST_READY || !(lport->link_up)) अणु
		QEDF_ERR(&(qedf->dbg_ctx), "els 0x%x: link is not ready\n",
			  op);
		rc = -EAGAIN;
		जाओ els_err;
	पूर्ण

	अगर (!test_bit(QEDF_RPORT_SESSION_READY, &fcport->flags)) अणु
		QEDF_ERR(&(qedf->dbg_ctx), "els 0x%x: fcport not ready\n", op);
		rc = -EINVAL;
		जाओ els_err;
	पूर्ण

	els_req = qedf_alloc_cmd(fcport, QEDF_ELS);
	अगर (!els_req) अणु
		QEDF_INFO(&qedf->dbg_ctx, QEDF_LOG_ELS,
			  "Failed to alloc ELS request 0x%x\n", op);
		rc = -ENOMEM;
		जाओ els_err;
	पूर्ण

	QEDF_INFO(&(qedf->dbg_ctx), QEDF_LOG_ELS, "initiate_els els_req = "
		   "0x%p cb_arg = %p xid = %x\n", els_req, cb_arg,
		   els_req->xid);
	els_req->sc_cmd = शून्य;
	els_req->cmd_type = QEDF_ELS;
	els_req->fcport = fcport;
	els_req->cb_func = cb_func;
	cb_arg->io_req = els_req;
	cb_arg->op = op;
	els_req->cb_arg = cb_arg;
	els_req->data_xfer_len = data_len;

	/* Record which cpu this request is associated with */
	els_req->cpu = smp_processor_id();

	mp_req = (काष्ठा qedf_mp_req *)&(els_req->mp_req);
	rc = qedf_init_mp_req(els_req);
	अगर (rc) अणु
		QEDF_ERR(&(qedf->dbg_ctx), "ELS MP request init failed\n");
		kref_put(&els_req->refcount, qedf_release_cmd);
		जाओ els_err;
	पूर्ण अन्यथा अणु
		rc = 0;
	पूर्ण

	/* Fill ELS Payload */
	अगर ((op >= ELS_LS_RJT) && (op <= ELS_AUTH_ELS)) अणु
		स_नकल(mp_req->req_buf, data, data_len);
	पूर्ण अन्यथा अणु
		QEDF_ERR(&(qedf->dbg_ctx), "Invalid ELS op 0x%x\n", op);
		els_req->cb_func = शून्य;
		els_req->cb_arg = शून्य;
		kref_put(&els_req->refcount, qedf_release_cmd);
		rc = -EINVAL;
	पूर्ण

	अगर (rc)
		जाओ els_err;

	/* Fill FC header */
	fc_hdr = &(mp_req->req_fc_hdr);

	did = fcport->rdata->ids.port_id;
	sid = fcport->sid;

	__fc_fill_fc_hdr(fc_hdr, FC_RCTL_ELS_REQ, did, sid,
			   FC_TYPE_ELS, FC_FC_FIRST_SEQ | FC_FC_END_SEQ |
			   FC_FC_SEQ_INIT, 0);

	/* Obtain exchange id */
	xid = els_req->xid;

	spin_lock_irqsave(&fcport->rport_lock, flags);

	sqe_idx = qedf_get_sqe_idx(fcport);
	sqe = &fcport->sq[sqe_idx];
	स_रखो(sqe, 0, माप(काष्ठा fcoe_wqe));

	/* Initialize task context क्रम this IO request */
	task = qedf_get_task_mem(&qedf->tasks, xid);
	qedf_init_mp_task(els_req, task, sqe);

	/* Put समयr on els request */
	अगर (समयr_msec)
		qedf_cmd_समयr_set(qedf, els_req, समयr_msec);

	/* Ring करोorbell */
	QEDF_INFO(&(qedf->dbg_ctx), QEDF_LOG_ELS, "Ringing doorbell for ELS "
		   "req\n");
	qedf_ring_करोorbell(fcport);
	set_bit(QEDF_CMD_OUTSTANDING, &els_req->flags);

	spin_unlock_irqrestore(&fcport->rport_lock, flags);
els_err:
	वापस rc;
पूर्ण

व्योम qedf_process_els_compl(काष्ठा qedf_ctx *qedf, काष्ठा fcoe_cqe *cqe,
	काष्ठा qedf_ioreq *els_req)
अणु
	काष्ठा fcoe_cqe_midpath_info *mp_info;
	काष्ठा qedf_rport *fcport;

	QEDF_INFO(&(qedf->dbg_ctx), QEDF_LOG_ELS, "Entered with xid = 0x%x"
		   " cmd_type = %d.\n", els_req->xid, els_req->cmd_type);

	अगर ((els_req->event == QEDF_IOREQ_EV_ELS_FLUSH)
		|| (els_req->event == QEDF_IOREQ_EV_CLEANUP_SUCCESS)
		|| (els_req->event == QEDF_IOREQ_EV_CLEANUP_FAILED)) अणु
		QEDF_INFO(&qedf->dbg_ctx, QEDF_LOG_IO,
			"ELS completion xid=0x%x after flush event=0x%x",
			els_req->xid, els_req->event);
		वापस;
	पूर्ण

	fcport = els_req->fcport;

	/* When flush is active,
	 * let the cmds be completed from the cleanup context
	 */
	अगर (test_bit(QEDF_RPORT_IN_TARGET_RESET, &fcport->flags) ||
		test_bit(QEDF_RPORT_IN_LUN_RESET, &fcport->flags)) अणु
		QEDF_INFO(&qedf->dbg_ctx, QEDF_LOG_IO,
			"Dropping ELS completion xid=0x%x as fcport is flushing",
			els_req->xid);
		वापस;
	पूर्ण

	clear_bit(QEDF_CMD_OUTSTANDING, &els_req->flags);

	/* Kill the ELS समयr */
	cancel_delayed_work(&els_req->समयout_work);

	/* Get ELS response length from CQE */
	mp_info = &cqe->cqe_info.midpath_info;
	els_req->mp_req.resp_len = mp_info->data_placement_size;

	/* Parse ELS response */
	अगर ((els_req->cb_func) && (els_req->cb_arg)) अणु
		els_req->cb_func(els_req->cb_arg);
		els_req->cb_arg = शून्य;
	पूर्ण

	kref_put(&els_req->refcount, qedf_release_cmd);
पूर्ण

अटल व्योम qedf_rrq_compl(काष्ठा qedf_els_cb_arg *cb_arg)
अणु
	काष्ठा qedf_ioreq *orig_io_req;
	काष्ठा qedf_ioreq *rrq_req;
	काष्ठा qedf_ctx *qedf;
	पूर्णांक refcount;

	rrq_req = cb_arg->io_req;
	qedf = rrq_req->fcport->qedf;

	QEDF_INFO(&(qedf->dbg_ctx), QEDF_LOG_ELS, "Entered.\n");

	orig_io_req = cb_arg->पातed_io_req;

	अगर (!orig_io_req) अणु
		QEDF_ERR(&qedf->dbg_ctx,
			 "Original io_req is NULL, rrq_req = %p.\n", rrq_req);
		जाओ out_मुक्त;
	पूर्ण

	refcount = kref_पढ़ो(&orig_io_req->refcount);
	QEDF_INFO(&(qedf->dbg_ctx), QEDF_LOG_ELS, "rrq_compl: orig io = %p,"
		   " orig xid = 0x%x, rrq_xid = 0x%x, refcount=%d\n",
		   orig_io_req, orig_io_req->xid, rrq_req->xid, refcount);

	/*
	 * This should वापस the पातed io_req to the command pool. Note that
	 * we need to check the refcound in हाल the original request was
	 * flushed but we get a completion on this xid.
	 */
	अगर (orig_io_req && refcount > 0)
		kref_put(&orig_io_req->refcount, qedf_release_cmd);

out_मुक्त:
	/*
	 * Release a reference to the rrq request अगर we समयd out as the
	 * rrq completion handler is called directly from the समयout handler
	 * and not from els_compl where the reference would have normally been
	 * released.
	 */
	अगर (rrq_req->event == QEDF_IOREQ_EV_ELS_TMO)
		kref_put(&rrq_req->refcount, qedf_release_cmd);
	kमुक्त(cb_arg);
पूर्ण

/* Assumes kref is alपढ़ोy held by caller */
पूर्णांक qedf_send_rrq(काष्ठा qedf_ioreq *पातed_io_req)
अणु

	काष्ठा fc_els_rrq rrq;
	काष्ठा qedf_rport *fcport;
	काष्ठा fc_lport *lport;
	काष्ठा qedf_els_cb_arg *cb_arg = शून्य;
	काष्ठा qedf_ctx *qedf;
	uपूर्णांक32_t sid;
	uपूर्णांक32_t r_a_tov;
	पूर्णांक rc;
	पूर्णांक refcount;

	अगर (!पातed_io_req) अणु
		QEDF_ERR(शून्य, "abort_io_req is NULL.\n");
		वापस -EINVAL;
	पूर्ण

	fcport = पातed_io_req->fcport;

	अगर (!fcport) अणु
		refcount = kref_पढ़ो(&पातed_io_req->refcount);
		QEDF_ERR(शून्य,
			 "RRQ work was queued prior to a flush xid=0x%x, refcount=%d.\n",
			 पातed_io_req->xid, refcount);
		kref_put(&पातed_io_req->refcount, qedf_release_cmd);
		वापस -EINVAL;
	पूर्ण

	/* Check that fcport is still offloaded */
	अगर (!test_bit(QEDF_RPORT_SESSION_READY, &fcport->flags)) अणु
		QEDF_ERR(शून्य, "fcport is no longer offloaded.\n");
		वापस -EINVAL;
	पूर्ण

	अगर (!fcport->qedf) अणु
		QEDF_ERR(शून्य, "fcport->qedf is NULL.\n");
		वापस -EINVAL;
	पूर्ण

	qedf = fcport->qedf;

	/*
	 * Sanity check that we can send a RRQ to make sure that refcount isn't
	 * 0
	 */
	refcount = kref_पढ़ो(&पातed_io_req->refcount);
	अगर (refcount != 1) अणु
		QEDF_INFO(&qedf->dbg_ctx, QEDF_LOG_ELS,
			  "refcount for xid=%x io_req=%p refcount=%d is not 1.\n",
			  पातed_io_req->xid, पातed_io_req, refcount);
		वापस -EINVAL;
	पूर्ण

	lport = qedf->lport;
	sid = fcport->sid;
	r_a_tov = lport->r_a_tov;

	QEDF_INFO(&(qedf->dbg_ctx), QEDF_LOG_ELS, "Sending RRQ orig "
		   "io = %p, orig_xid = 0x%x\n", पातed_io_req,
		   पातed_io_req->xid);
	स_रखो(&rrq, 0, माप(rrq));

	cb_arg = kzalloc(माप(काष्ठा qedf_els_cb_arg), GFP_NOIO);
	अगर (!cb_arg) अणु
		QEDF_ERR(&(qedf->dbg_ctx), "Unable to allocate cb_arg for "
			  "RRQ\n");
		rc = -ENOMEM;
		जाओ rrq_err;
	पूर्ण

	cb_arg->पातed_io_req = पातed_io_req;

	rrq.rrq_cmd = ELS_RRQ;
	hton24(rrq.rrq_s_id, sid);
	rrq.rrq_ox_id = htons(पातed_io_req->xid);
	rrq.rrq_rx_id =
	    htons(पातed_io_req->task->tstorm_st_context.पढ़ो_ग_लिखो.rx_id);

	rc = qedf_initiate_els(fcport, ELS_RRQ, &rrq, माप(rrq),
	    qedf_rrq_compl, cb_arg, r_a_tov);

rrq_err:
	अगर (rc) अणु
		QEDF_ERR(&(qedf->dbg_ctx), "RRQ failed - release orig io "
			  "req 0x%x\n", पातed_io_req->xid);
		kमुक्त(cb_arg);
		kref_put(&पातed_io_req->refcount, qedf_release_cmd);
	पूर्ण
	वापस rc;
पूर्ण

अटल व्योम qedf_process_l2_frame_compl(काष्ठा qedf_rport *fcport,
					काष्ठा fc_frame *fp,
					u16 l2_oxid)
अणु
	काष्ठा fc_lport *lport = fcport->qedf->lport;
	काष्ठा fc_frame_header *fh;
	u32 crc;

	fh = (काष्ठा fc_frame_header *)fc_frame_header_get(fp);

	/* Set the OXID we वापस to what libfc used */
	अगर (l2_oxid != FC_XID_UNKNOWN)
		fh->fh_ox_id = htons(l2_oxid);

	/* Setup header fields */
	fh->fh_r_ctl = FC_RCTL_ELS_REP;
	fh->fh_type = FC_TYPE_ELS;
	/* Last sequence, end sequence */
	fh->fh_f_ctl[0] = 0x98;
	hton24(fh->fh_d_id, lport->port_id);
	hton24(fh->fh_s_id, fcport->rdata->ids.port_id);
	fh->fh_rx_id = 0xffff;

	/* Set frame attributes */
	crc = fcoe_fc_crc(fp);
	fc_frame_init(fp);
	fr_dev(fp) = lport;
	fr_sof(fp) = FC_SOF_I3;
	fr_eof(fp) = FC_खातापूर्ण_T;
	fr_crc(fp) = cpu_to_le32(~crc);

	/* Send completed request to libfc */
	fc_exch_recv(lport, fp);
पूर्ण

/*
 * In instances where an ELS command बार out we may need to restart the
 * rport by logging out and then logging back in.
 */
व्योम qedf_restart_rport(काष्ठा qedf_rport *fcport)
अणु
	काष्ठा fc_lport *lport;
	काष्ठा fc_rport_priv *rdata;
	u32 port_id;
	अचिन्हित दीर्घ flags;

	अगर (!fcport) अणु
		QEDF_ERR(शून्य, "fcport is NULL.\n");
		वापस;
	पूर्ण

	spin_lock_irqsave(&fcport->rport_lock, flags);
	अगर (test_bit(QEDF_RPORT_IN_RESET, &fcport->flags) ||
	    !test_bit(QEDF_RPORT_SESSION_READY, &fcport->flags) ||
	    test_bit(QEDF_RPORT_UPLOADING_CONNECTION, &fcport->flags)) अणु
		QEDF_ERR(&(fcport->qedf->dbg_ctx), "fcport %p already in reset or not offloaded.\n",
		    fcport);
		spin_unlock_irqrestore(&fcport->rport_lock, flags);
		वापस;
	पूर्ण

	/* Set that we are now in reset */
	set_bit(QEDF_RPORT_IN_RESET, &fcport->flags);
	spin_unlock_irqrestore(&fcport->rport_lock, flags);

	rdata = fcport->rdata;
	अगर (rdata && !kref_get_unless_zero(&rdata->kref)) अणु
		fcport->rdata = शून्य;
		rdata = शून्य;
	पूर्ण

	अगर (rdata && rdata->rp_state == RPORT_ST_READY) अणु
		lport = fcport->qedf->lport;
		port_id = rdata->ids.port_id;
		QEDF_ERR(&(fcport->qedf->dbg_ctx),
		    "LOGO port_id=%x.\n", port_id);
		fc_rport_logoff(rdata);
		kref_put(&rdata->kref, fc_rport_destroy);
		mutex_lock(&lport->disc.disc_mutex);
		/* Recreate the rport and log back in */
		rdata = fc_rport_create(lport, port_id);
		mutex_unlock(&lport->disc.disc_mutex);
		अगर (rdata)
			fc_rport_login(rdata);
		fcport->rdata = rdata;
	पूर्ण
	clear_bit(QEDF_RPORT_IN_RESET, &fcport->flags);
पूर्ण

अटल व्योम qedf_l2_els_compl(काष्ठा qedf_els_cb_arg *cb_arg)
अणु
	काष्ठा qedf_ioreq *els_req;
	काष्ठा qedf_rport *fcport;
	काष्ठा qedf_mp_req *mp_req;
	काष्ठा fc_frame *fp;
	काष्ठा fc_frame_header *fh, *mp_fc_hdr;
	व्योम *resp_buf, *fc_payload;
	u32 resp_len;
	u16 l2_oxid;

	l2_oxid = cb_arg->l2_oxid;
	els_req = cb_arg->io_req;

	अगर (!els_req) अणु
		QEDF_ERR(शून्य, "els_req is NULL.\n");
		जाओ मुक्त_arg;
	पूर्ण

	/*
	 * If we are flushing the command just मुक्त the cb_arg as none of the
	 * response data will be valid.
	 */
	अगर (els_req->event == QEDF_IOREQ_EV_ELS_FLUSH) अणु
		QEDF_ERR(शून्य, "els_req xid=0x%x event is flush.\n",
			 els_req->xid);
		जाओ मुक्त_arg;
	पूर्ण

	fcport = els_req->fcport;
	mp_req = &(els_req->mp_req);
	mp_fc_hdr = &(mp_req->resp_fc_hdr);
	resp_len = mp_req->resp_len;
	resp_buf = mp_req->resp_buf;

	/*
	 * If a middle path ELS command बार out, करोn't try to वापस
	 * the command but rather करो any पूर्णांकernal cleanup and then libfc
	 * समयout the command and clean up its पूर्णांकernal resources.
	 */
	अगर (els_req->event == QEDF_IOREQ_EV_ELS_TMO) अणु
		/*
		 * If ADISC बार out, libfc will समयout the exchange and then
		 * try to send a PLOGI which will समयout since the session is
		 * still offloaded.  Force libfc to logout the session which
		 * will offload the connection and allow the PLOGI response to
		 * flow over the LL2 path.
		 */
		अगर (cb_arg->op == ELS_ADISC)
			qedf_restart_rport(fcport);
		वापस;
	पूर्ण

	अगर (माप(काष्ठा fc_frame_header) + resp_len > QEDF_PAGE_SIZE) अणु
		QEDF_ERR(&(fcport->qedf->dbg_ctx), "resp_len is "
		   "beyond page size.\n");
		जाओ मुक्त_arg;
	पूर्ण

	fp = fc_frame_alloc(fcport->qedf->lport, resp_len);
	अगर (!fp) अणु
		QEDF_ERR(&(fcport->qedf->dbg_ctx),
		    "fc_frame_alloc failure.\n");
		वापस;
	पूर्ण

	/* Copy frame header from firmware पूर्णांकo fp */
	fh = (काष्ठा fc_frame_header *)fc_frame_header_get(fp);
	स_नकल(fh, mp_fc_hdr, माप(काष्ठा fc_frame_header));

	/* Copy payload from firmware पूर्णांकo fp */
	fc_payload = fc_frame_payload_get(fp, resp_len);
	स_नकल(fc_payload, resp_buf, resp_len);

	QEDF_INFO(&(fcport->qedf->dbg_ctx), QEDF_LOG_ELS,
	    "Completing OX_ID 0x%x back to libfc.\n", l2_oxid);
	qedf_process_l2_frame_compl(fcport, fp, l2_oxid);

मुक्त_arg:
	kमुक्त(cb_arg);
पूर्ण

पूर्णांक qedf_send_adisc(काष्ठा qedf_rport *fcport, काष्ठा fc_frame *fp)
अणु
	काष्ठा fc_els_adisc *adisc;
	काष्ठा fc_frame_header *fh;
	काष्ठा fc_lport *lport = fcport->qedf->lport;
	काष्ठा qedf_els_cb_arg *cb_arg = शून्य;
	काष्ठा qedf_ctx *qedf;
	uपूर्णांक32_t r_a_tov = lport->r_a_tov;
	पूर्णांक rc;

	qedf = fcport->qedf;
	fh = fc_frame_header_get(fp);

	cb_arg = kzalloc(माप(काष्ठा qedf_els_cb_arg), GFP_NOIO);
	अगर (!cb_arg) अणु
		QEDF_ERR(&(qedf->dbg_ctx), "Unable to allocate cb_arg for "
			  "ADISC\n");
		rc = -ENOMEM;
		जाओ adisc_err;
	पूर्ण
	cb_arg->l2_oxid = ntohs(fh->fh_ox_id);

	QEDF_INFO(&(qedf->dbg_ctx), QEDF_LOG_ELS,
	    "Sending ADISC ox_id=0x%x.\n", cb_arg->l2_oxid);

	adisc = fc_frame_payload_get(fp, माप(*adisc));

	rc = qedf_initiate_els(fcport, ELS_ADISC, adisc, माप(*adisc),
	    qedf_l2_els_compl, cb_arg, r_a_tov);

adisc_err:
	अगर (rc) अणु
		QEDF_ERR(&(qedf->dbg_ctx), "ADISC failed.\n");
		kमुक्त(cb_arg);
	पूर्ण
	वापस rc;
पूर्ण

अटल व्योम qedf_srr_compl(काष्ठा qedf_els_cb_arg *cb_arg)
अणु
	काष्ठा qedf_ioreq *orig_io_req;
	काष्ठा qedf_ioreq *srr_req;
	काष्ठा qedf_mp_req *mp_req;
	काष्ठा fc_frame_header *mp_fc_hdr, *fh;
	काष्ठा fc_frame *fp;
	व्योम *resp_buf, *fc_payload;
	u32 resp_len;
	काष्ठा fc_lport *lport;
	काष्ठा qedf_ctx *qedf;
	पूर्णांक refcount;
	u8 opcode;

	srr_req = cb_arg->io_req;
	qedf = srr_req->fcport->qedf;
	lport = qedf->lport;

	orig_io_req = cb_arg->पातed_io_req;

	अगर (!orig_io_req) अणु
		QEDF_ERR(शून्य, "orig_io_req is NULL.\n");
		जाओ out_मुक्त;
	पूर्ण

	clear_bit(QEDF_CMD_SRR_SENT, &orig_io_req->flags);

	अगर (srr_req->event != QEDF_IOREQ_EV_ELS_TMO &&
	    srr_req->event != QEDF_IOREQ_EV_ELS_ERR_DETECT)
		cancel_delayed_work_sync(&orig_io_req->समयout_work);

	refcount = kref_पढ़ो(&orig_io_req->refcount);
	QEDF_INFO(&(qedf->dbg_ctx), QEDF_LOG_ELS, "Entered: orig_io=%p,"
		   " orig_io_xid=0x%x, rec_xid=0x%x, refcount=%d\n",
		   orig_io_req, orig_io_req->xid, srr_req->xid, refcount);

	/* If a SRR बार out, simply मुक्त resources */
	अगर (srr_req->event == QEDF_IOREQ_EV_ELS_TMO) अणु
		QEDF_ERR(&qedf->dbg_ctx,
			 "ELS timeout rec_xid=0x%x.\n", srr_req->xid);
		जाओ out_put;
	पूर्ण

	/* Normalize response data पूर्णांकo काष्ठा fc_frame */
	mp_req = &(srr_req->mp_req);
	mp_fc_hdr = &(mp_req->resp_fc_hdr);
	resp_len = mp_req->resp_len;
	resp_buf = mp_req->resp_buf;

	fp = fc_frame_alloc(lport, resp_len);
	अगर (!fp) अणु
		QEDF_ERR(&(qedf->dbg_ctx),
		    "fc_frame_alloc failure.\n");
		जाओ out_put;
	पूर्ण

	/* Copy frame header from firmware पूर्णांकo fp */
	fh = (काष्ठा fc_frame_header *)fc_frame_header_get(fp);
	स_नकल(fh, mp_fc_hdr, माप(काष्ठा fc_frame_header));

	/* Copy payload from firmware पूर्णांकo fp */
	fc_payload = fc_frame_payload_get(fp, resp_len);
	स_नकल(fc_payload, resp_buf, resp_len);

	opcode = fc_frame_payload_op(fp);
	चयन (opcode) अणु
	हाल ELS_LS_ACC:
		QEDF_INFO(&(qedf->dbg_ctx), QEDF_LOG_ELS,
		    "SRR success.\n");
		अवरोध;
	हाल ELS_LS_RJT:
		QEDF_INFO(&qedf->dbg_ctx, QEDF_LOG_ELS,
		    "SRR rejected.\n");
		qedf_initiate_abts(orig_io_req, true);
		अवरोध;
	पूर्ण

	fc_frame_मुक्त(fp);
out_put:
	/* Put reference क्रम original command since SRR completed */
	kref_put(&orig_io_req->refcount, qedf_release_cmd);
out_मुक्त:
	kमुक्त(cb_arg);
पूर्ण

अटल पूर्णांक qedf_send_srr(काष्ठा qedf_ioreq *orig_io_req, u32 offset, u8 r_ctl)
अणु
	काष्ठा fcp_srr srr;
	काष्ठा qedf_ctx *qedf;
	काष्ठा qedf_rport *fcport;
	काष्ठा fc_lport *lport;
	काष्ठा qedf_els_cb_arg *cb_arg = शून्य;
	u32 r_a_tov;
	पूर्णांक rc;

	अगर (!orig_io_req) अणु
		QEDF_ERR(शून्य, "orig_io_req is NULL.\n");
		वापस -EINVAL;
	पूर्ण

	fcport = orig_io_req->fcport;

	/* Check that fcport is still offloaded */
	अगर (!test_bit(QEDF_RPORT_SESSION_READY, &fcport->flags)) अणु
		QEDF_ERR(शून्य, "fcport is no longer offloaded.\n");
		वापस -EINVAL;
	पूर्ण

	अगर (!fcport->qedf) अणु
		QEDF_ERR(शून्य, "fcport->qedf is NULL.\n");
		वापस -EINVAL;
	पूर्ण

	/* Take reference until SRR command completion */
	kref_get(&orig_io_req->refcount);

	qedf = fcport->qedf;
	lport = qedf->lport;
	r_a_tov = lport->r_a_tov;

	QEDF_INFO(&(qedf->dbg_ctx), QEDF_LOG_ELS, "Sending SRR orig_io=%p, "
		   "orig_xid=0x%x\n", orig_io_req, orig_io_req->xid);
	स_रखो(&srr, 0, माप(srr));

	cb_arg = kzalloc(माप(काष्ठा qedf_els_cb_arg), GFP_NOIO);
	अगर (!cb_arg) अणु
		QEDF_ERR(&(qedf->dbg_ctx), "Unable to allocate cb_arg for "
			  "SRR\n");
		rc = -ENOMEM;
		जाओ srr_err;
	पूर्ण

	cb_arg->पातed_io_req = orig_io_req;

	srr.srr_op = ELS_SRR;
	srr.srr_ox_id = htons(orig_io_req->xid);
	srr.srr_rx_id = htons(orig_io_req->rx_id);
	srr.srr_rel_off = htonl(offset);
	srr.srr_r_ctl = r_ctl;

	rc = qedf_initiate_els(fcport, ELS_SRR, &srr, माप(srr),
	    qedf_srr_compl, cb_arg, r_a_tov);

srr_err:
	अगर (rc) अणु
		QEDF_ERR(&(qedf->dbg_ctx), "SRR failed - release orig_io_req"
			  "=0x%x\n", orig_io_req->xid);
		kमुक्त(cb_arg);
		/* If we fail to queue SRR, send ABTS to orig_io */
		qedf_initiate_abts(orig_io_req, true);
		kref_put(&orig_io_req->refcount, qedf_release_cmd);
	पूर्ण अन्यथा
		/* Tell other thपढ़ोs that SRR is in progress */
		set_bit(QEDF_CMD_SRR_SENT, &orig_io_req->flags);

	वापस rc;
पूर्ण

अटल व्योम qedf_initiate_seq_cleanup(काष्ठा qedf_ioreq *orig_io_req,
	u32 offset, u8 r_ctl)
अणु
	काष्ठा qedf_rport *fcport;
	अचिन्हित दीर्घ flags;
	काष्ठा qedf_els_cb_arg *cb_arg;
	काष्ठा fcoe_wqe *sqe;
	u16 sqe_idx;

	fcport = orig_io_req->fcport;

	QEDF_INFO(&(fcport->qedf->dbg_ctx), QEDF_LOG_ELS,
	    "Doing sequence cleanup for xid=0x%x offset=%u.\n",
	    orig_io_req->xid, offset);

	cb_arg = kzalloc(माप(काष्ठा qedf_els_cb_arg), GFP_NOIO);
	अगर (!cb_arg) अणु
		QEDF_ERR(&(fcport->qedf->dbg_ctx), "Unable to allocate cb_arg "
			  "for sequence cleanup\n");
		वापस;
	पूर्ण

	/* Get reference क्रम cleanup request */
	kref_get(&orig_io_req->refcount);

	orig_io_req->cmd_type = QEDF_SEQ_CLEANUP;
	cb_arg->offset = offset;
	cb_arg->r_ctl = r_ctl;
	orig_io_req->cb_arg = cb_arg;

	qedf_cmd_समयr_set(fcport->qedf, orig_io_req,
	    QEDF_CLEANUP_TIMEOUT * HZ);

	spin_lock_irqsave(&fcport->rport_lock, flags);

	sqe_idx = qedf_get_sqe_idx(fcport);
	sqe = &fcport->sq[sqe_idx];
	स_रखो(sqe, 0, माप(काष्ठा fcoe_wqe));
	orig_io_req->task_params->sqe = sqe;

	init_initiator_sequence_recovery_fcoe_task(orig_io_req->task_params,
						   offset);
	qedf_ring_करोorbell(fcport);

	spin_unlock_irqrestore(&fcport->rport_lock, flags);
पूर्ण

व्योम qedf_process_seq_cleanup_compl(काष्ठा qedf_ctx *qedf,
	काष्ठा fcoe_cqe *cqe, काष्ठा qedf_ioreq *io_req)
अणु
	पूर्णांक rc;
	काष्ठा qedf_els_cb_arg *cb_arg;

	cb_arg = io_req->cb_arg;

	/* If we समयd out just मुक्त resources */
	अगर (io_req->event == QEDF_IOREQ_EV_ELS_TMO || !cqe) अणु
		QEDF_ERR(&qedf->dbg_ctx,
			 "cqe is NULL or timeout event (0x%x)", io_req->event);
		जाओ मुक्त;
	पूर्ण

	/* Kill the समयr we put on the request */
	cancel_delayed_work_sync(&io_req->समयout_work);

	rc = qedf_send_srr(io_req, cb_arg->offset, cb_arg->r_ctl);
	अगर (rc)
		QEDF_ERR(&(qedf->dbg_ctx), "Unable to send SRR, I/O will "
		    "abort, xid=0x%x.\n", io_req->xid);
मुक्त:
	kमुक्त(cb_arg);
	kref_put(&io_req->refcount, qedf_release_cmd);
पूर्ण

अटल bool qedf_requeue_io_req(काष्ठा qedf_ioreq *orig_io_req)
अणु
	काष्ठा qedf_rport *fcport;
	काष्ठा qedf_ioreq *new_io_req;
	अचिन्हित दीर्घ flags;
	bool rc = false;

	fcport = orig_io_req->fcport;
	अगर (!fcport) अणु
		QEDF_ERR(शून्य, "fcport is NULL.\n");
		जाओ out;
	पूर्ण

	अगर (!orig_io_req->sc_cmd) अणु
		QEDF_ERR(&(fcport->qedf->dbg_ctx), "sc_cmd is NULL for "
		    "xid=0x%x.\n", orig_io_req->xid);
		जाओ out;
	पूर्ण

	new_io_req = qedf_alloc_cmd(fcport, QEDF_SCSI_CMD);
	अगर (!new_io_req) अणु
		QEDF_ERR(&(fcport->qedf->dbg_ctx), "Could not allocate new "
		    "io_req.\n");
		जाओ out;
	पूर्ण

	new_io_req->sc_cmd = orig_io_req->sc_cmd;

	/*
	 * This keeps the sc_cmd काष्ठा from being वापसed to the tape
	 * driver and being requeued twice. We करो need to put a reference
	 * क्रम the original I/O request since we will not करो a SCSI completion
	 * क्रम it.
	 */
	orig_io_req->sc_cmd = शून्य;
	kref_put(&orig_io_req->refcount, qedf_release_cmd);

	spin_lock_irqsave(&fcport->rport_lock, flags);

	/* kref क्रम new command released in qedf_post_io_req on error */
	अगर (qedf_post_io_req(fcport, new_io_req)) अणु
		QEDF_ERR(&(fcport->qedf->dbg_ctx), "Unable to post io_req\n");
		/* Return SQE to pool */
		atomic_inc(&fcport->मुक्त_sqes);
	पूर्ण अन्यथा अणु
		QEDF_INFO(&(fcport->qedf->dbg_ctx), QEDF_LOG_ELS,
		    "Reissued SCSI command from  orig_xid=0x%x on "
		    "new_xid=0x%x.\n", orig_io_req->xid, new_io_req->xid);
		/*
		 * Abort the original I/O but करो not वापस SCSI command as
		 * it has been reissued on another OX_ID.
		 */
		spin_unlock_irqrestore(&fcport->rport_lock, flags);
		qedf_initiate_abts(orig_io_req, false);
		जाओ out;
	पूर्ण

	spin_unlock_irqrestore(&fcport->rport_lock, flags);
out:
	वापस rc;
पूर्ण


अटल व्योम qedf_rec_compl(काष्ठा qedf_els_cb_arg *cb_arg)
अणु
	काष्ठा qedf_ioreq *orig_io_req;
	काष्ठा qedf_ioreq *rec_req;
	काष्ठा qedf_mp_req *mp_req;
	काष्ठा fc_frame_header *mp_fc_hdr, *fh;
	काष्ठा fc_frame *fp;
	व्योम *resp_buf, *fc_payload;
	u32 resp_len;
	काष्ठा fc_lport *lport;
	काष्ठा qedf_ctx *qedf;
	पूर्णांक refcount;
	क्रमागत fc_rctl r_ctl;
	काष्ठा fc_els_ls_rjt *rjt;
	काष्ठा fc_els_rec_acc *acc;
	u8 opcode;
	u32 offset, e_stat;
	काष्ठा scsi_cmnd *sc_cmd;
	bool srr_needed = false;

	rec_req = cb_arg->io_req;
	qedf = rec_req->fcport->qedf;
	lport = qedf->lport;

	orig_io_req = cb_arg->पातed_io_req;

	अगर (!orig_io_req) अणु
		QEDF_ERR(शून्य, "orig_io_req is NULL.\n");
		जाओ out_मुक्त;
	पूर्ण

	अगर (rec_req->event != QEDF_IOREQ_EV_ELS_TMO &&
	    rec_req->event != QEDF_IOREQ_EV_ELS_ERR_DETECT)
		cancel_delayed_work_sync(&orig_io_req->समयout_work);

	refcount = kref_पढ़ो(&orig_io_req->refcount);
	QEDF_INFO(&(qedf->dbg_ctx), QEDF_LOG_ELS, "Entered: orig_io=%p,"
		   " orig_io_xid=0x%x, rec_xid=0x%x, refcount=%d\n",
		   orig_io_req, orig_io_req->xid, rec_req->xid, refcount);

	/* If a REC बार out, मुक्त resources */
	अगर (rec_req->event == QEDF_IOREQ_EV_ELS_TMO) अणु
		QEDF_ERR(&qedf->dbg_ctx,
			 "Got TMO event, orig_io_req %p orig_io_xid=0x%x.\n",
			 orig_io_req, orig_io_req->xid);
		जाओ out_put;
	पूर्ण

	/* Normalize response data पूर्णांकo काष्ठा fc_frame */
	mp_req = &(rec_req->mp_req);
	mp_fc_hdr = &(mp_req->resp_fc_hdr);
	resp_len = mp_req->resp_len;
	acc = resp_buf = mp_req->resp_buf;

	fp = fc_frame_alloc(lport, resp_len);
	अगर (!fp) अणु
		QEDF_ERR(&(qedf->dbg_ctx),
		    "fc_frame_alloc failure.\n");
		जाओ out_put;
	पूर्ण

	/* Copy frame header from firmware पूर्णांकo fp */
	fh = (काष्ठा fc_frame_header *)fc_frame_header_get(fp);
	स_नकल(fh, mp_fc_hdr, माप(काष्ठा fc_frame_header));

	/* Copy payload from firmware पूर्णांकo fp */
	fc_payload = fc_frame_payload_get(fp, resp_len);
	स_नकल(fc_payload, resp_buf, resp_len);

	opcode = fc_frame_payload_op(fp);
	अगर (opcode == ELS_LS_RJT) अणु
		rjt = fc_frame_payload_get(fp, माप(*rjt));
		अगर (!rjt) अणु
			QEDF_ERR(&qedf->dbg_ctx, "payload get failed");
			जाओ out_मुक्त_frame;
		पूर्ण

		QEDF_INFO(&(qedf->dbg_ctx), QEDF_LOG_ELS,
		    "Received LS_RJT for REC: er_reason=0x%x, "
		    "er_explan=0x%x.\n", rjt->er_reason, rjt->er_explan);
		/*
		 * The following response(s) mean that we need to reissue the
		 * request on another exchange.  We need to करो this without
		 * inक्रमming the upper layers lest it cause an application
		 * error.
		 */
		अगर ((rjt->er_reason == ELS_RJT_LOGIC ||
		    rjt->er_reason == ELS_RJT_UNAB) &&
		    rjt->er_explan == ELS_EXPL_OXID_RXID) अणु
			QEDF_INFO(&(qedf->dbg_ctx), QEDF_LOG_ELS,
			    "Handle CMD LOST case.\n");
			qedf_requeue_io_req(orig_io_req);
		पूर्ण
	पूर्ण अन्यथा अगर (opcode == ELS_LS_ACC) अणु
		offset = ntohl(acc->reca_fc4value);
		e_stat = ntohl(acc->reca_e_stat);
		QEDF_INFO(&(qedf->dbg_ctx), QEDF_LOG_ELS,
		    "Received LS_ACC for REC: offset=0x%x, e_stat=0x%x.\n",
		    offset, e_stat);
		अगर (e_stat & ESB_ST_SEQ_INIT)  अणु
			QEDF_INFO(&(qedf->dbg_ctx), QEDF_LOG_ELS,
			    "Target has the seq init\n");
			जाओ out_मुक्त_frame;
		पूर्ण
		sc_cmd = orig_io_req->sc_cmd;
		अगर (!sc_cmd) अणु
			QEDF_INFO(&(qedf->dbg_ctx), QEDF_LOG_ELS,
			    "sc_cmd is NULL for xid=0x%x.\n",
			    orig_io_req->xid);
			जाओ out_मुक्त_frame;
		पूर्ण
		/* SCSI ग_लिखो हाल */
		अगर (sc_cmd->sc_data_direction == DMA_TO_DEVICE) अणु
			अगर (offset == orig_io_req->data_xfer_len) अणु
				QEDF_INFO(&(qedf->dbg_ctx), QEDF_LOG_ELS,
				    "WRITE - response lost.\n");
				r_ctl = FC_RCTL_DD_CMD_STATUS;
				srr_needed = true;
				offset = 0;
			पूर्ण अन्यथा अणु
				QEDF_INFO(&(qedf->dbg_ctx), QEDF_LOG_ELS,
				    "WRITE - XFER_RDY/DATA lost.\n");
				r_ctl = FC_RCTL_DD_DATA_DESC;
				/* Use data from warning CQE instead of REC */
				offset = orig_io_req->tx_buf_off;
			पूर्ण
		/* SCSI पढ़ो हाल */
		पूर्ण अन्यथा अणु
			अगर (orig_io_req->rx_buf_off ==
			    orig_io_req->data_xfer_len) अणु
				QEDF_INFO(&(qedf->dbg_ctx), QEDF_LOG_ELS,
				    "READ - response lost.\n");
				srr_needed = true;
				r_ctl = FC_RCTL_DD_CMD_STATUS;
				offset = 0;
			पूर्ण अन्यथा अणु
				QEDF_INFO(&(qedf->dbg_ctx), QEDF_LOG_ELS,
				    "READ - DATA lost.\n");
				/*
				 * For पढ़ो हाल we always set the offset to 0
				 * क्रम sequence recovery task.
				 */
				offset = 0;
				r_ctl = FC_RCTL_DD_SOL_DATA;
			पूर्ण
		पूर्ण

		अगर (srr_needed)
			qedf_send_srr(orig_io_req, offset, r_ctl);
		अन्यथा
			qedf_initiate_seq_cleanup(orig_io_req, offset, r_ctl);
	पूर्ण

out_मुक्त_frame:
	fc_frame_मुक्त(fp);
out_put:
	/* Put reference क्रम original command since REC completed */
	kref_put(&orig_io_req->refcount, qedf_release_cmd);
out_मुक्त:
	kमुक्त(cb_arg);
पूर्ण

/* Assumes kref is alपढ़ोy held by caller */
पूर्णांक qedf_send_rec(काष्ठा qedf_ioreq *orig_io_req)
अणु

	काष्ठा fc_els_rec rec;
	काष्ठा qedf_rport *fcport;
	काष्ठा fc_lport *lport;
	काष्ठा qedf_els_cb_arg *cb_arg = शून्य;
	काष्ठा qedf_ctx *qedf;
	uपूर्णांक32_t sid;
	uपूर्णांक32_t r_a_tov;
	पूर्णांक rc;

	अगर (!orig_io_req) अणु
		QEDF_ERR(शून्य, "orig_io_req is NULL.\n");
		वापस -EINVAL;
	पूर्ण

	fcport = orig_io_req->fcport;

	/* Check that fcport is still offloaded */
	अगर (!test_bit(QEDF_RPORT_SESSION_READY, &fcport->flags)) अणु
		QEDF_ERR(शून्य, "fcport is no longer offloaded.\n");
		वापस -EINVAL;
	पूर्ण

	अगर (!fcport->qedf) अणु
		QEDF_ERR(शून्य, "fcport->qedf is NULL.\n");
		वापस -EINVAL;
	पूर्ण

	/* Take reference until REC command completion */
	kref_get(&orig_io_req->refcount);

	qedf = fcport->qedf;
	lport = qedf->lport;
	sid = fcport->sid;
	r_a_tov = lport->r_a_tov;

	स_रखो(&rec, 0, माप(rec));

	cb_arg = kzalloc(माप(काष्ठा qedf_els_cb_arg), GFP_NOIO);
	अगर (!cb_arg) अणु
		QEDF_ERR(&(qedf->dbg_ctx), "Unable to allocate cb_arg for "
			  "REC\n");
		rc = -ENOMEM;
		जाओ rec_err;
	पूर्ण

	cb_arg->पातed_io_req = orig_io_req;

	rec.rec_cmd = ELS_REC;
	hton24(rec.rec_s_id, sid);
	rec.rec_ox_id = htons(orig_io_req->xid);
	rec.rec_rx_id =
	    htons(orig_io_req->task->tstorm_st_context.पढ़ो_ग_लिखो.rx_id);

	QEDF_INFO(&(qedf->dbg_ctx), QEDF_LOG_ELS, "Sending REC orig_io=%p, "
	   "orig_xid=0x%x rx_id=0x%x\n", orig_io_req,
	   orig_io_req->xid, rec.rec_rx_id);
	rc = qedf_initiate_els(fcport, ELS_REC, &rec, माप(rec),
	    qedf_rec_compl, cb_arg, r_a_tov);

rec_err:
	अगर (rc) अणु
		QEDF_ERR(&(qedf->dbg_ctx), "REC failed - release orig_io_req"
			  "=0x%x\n", orig_io_req->xid);
		kमुक्त(cb_arg);
		kref_put(&orig_io_req->refcount, qedf_release_cmd);
	पूर्ण
	वापस rc;
पूर्ण
