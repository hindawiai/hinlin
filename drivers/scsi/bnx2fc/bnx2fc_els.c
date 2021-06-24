<शैली गुरु>
/*
 * bnx2fc_els.c: QLogic Linux FCoE offload driver.
 * This file contains helper routines that handle ELS requests
 * and responses.
 *
 * Copyright (c) 2008-2013 Broadcom Corporation
 * Copyright (c) 2014-2016 QLogic Corporation
 * Copyright (c) 2016-2017 Cavium Inc.
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation.
 *
 * Written by: Bhanu Prakash Gollapudi (bprakash@broadcom.com)
 */

#समावेश "bnx2fc.h"

अटल व्योम bnx2fc_logo_resp(काष्ठा fc_seq *seq, काष्ठा fc_frame *fp,
			     व्योम *arg);
अटल व्योम bnx2fc_flogi_resp(काष्ठा fc_seq *seq, काष्ठा fc_frame *fp,
			      व्योम *arg);
अटल पूर्णांक bnx2fc_initiate_els(काष्ठा bnx2fc_rport *tgt, अचिन्हित पूर्णांक op,
			व्योम *data, u32 data_len,
			व्योम (*cb_func)(काष्ठा bnx2fc_els_cb_arg *cb_arg),
			काष्ठा bnx2fc_els_cb_arg *cb_arg, u32 समयr_msec);

अटल व्योम bnx2fc_rrq_compl(काष्ठा bnx2fc_els_cb_arg *cb_arg)
अणु
	काष्ठा bnx2fc_cmd *orig_io_req;
	काष्ठा bnx2fc_cmd *rrq_req;
	पूर्णांक rc = 0;

	BUG_ON(!cb_arg);
	rrq_req = cb_arg->io_req;
	orig_io_req = cb_arg->पातed_io_req;
	BUG_ON(!orig_io_req);
	BNX2FC_ELS_DBG("rrq_compl: orig xid = 0x%x, rrq_xid = 0x%x\n",
		   orig_io_req->xid, rrq_req->xid);

	kref_put(&orig_io_req->refcount, bnx2fc_cmd_release);

	अगर (test_and_clear_bit(BNX2FC_FLAG_ELS_TIMEOUT, &rrq_req->req_flags)) अणु
		/*
		 * els req is समयd out. cleanup the IO with FW and
		 * drop the completion. Remove from active_cmd_queue.
		 */
		BNX2FC_ELS_DBG("rrq xid - 0x%x timed out, clean it up\n",
			   rrq_req->xid);

		अगर (rrq_req->on_active_queue) अणु
			list_del_init(&rrq_req->link);
			rrq_req->on_active_queue = 0;
			rc = bnx2fc_initiate_cleanup(rrq_req);
			BUG_ON(rc);
		पूर्ण
	पूर्ण
	kमुक्त(cb_arg);
पूर्ण
पूर्णांक bnx2fc_send_rrq(काष्ठा bnx2fc_cmd *पातed_io_req)
अणु

	काष्ठा fc_els_rrq rrq;
	काष्ठा bnx2fc_rport *tgt = पातed_io_req->tgt;
	काष्ठा fc_lport *lport = शून्य;
	काष्ठा bnx2fc_els_cb_arg *cb_arg = शून्य;
	u32 sid = 0;
	u32 r_a_tov = 0;
	अचिन्हित दीर्घ start = jअगरfies;
	पूर्णांक rc;

	अगर (!test_bit(BNX2FC_FLAG_SESSION_READY, &tgt->flags))
		वापस -EINVAL;

	lport = tgt->rdata->local_port;
	sid = tgt->sid;
	r_a_tov = lport->r_a_tov;

	BNX2FC_ELS_DBG("Sending RRQ orig_xid = 0x%x\n",
		   पातed_io_req->xid);
	स_रखो(&rrq, 0, माप(rrq));

	cb_arg = kzalloc(माप(काष्ठा bnx2fc_els_cb_arg), GFP_NOIO);
	अगर (!cb_arg) अणु
		prपूर्णांकk(KERN_ERR PFX "Unable to allocate cb_arg for RRQ\n");
		rc = -ENOMEM;
		जाओ rrq_err;
	पूर्ण

	cb_arg->पातed_io_req = पातed_io_req;

	rrq.rrq_cmd = ELS_RRQ;
	hton24(rrq.rrq_s_id, sid);
	rrq.rrq_ox_id = htons(पातed_io_req->xid);
	rrq.rrq_rx_id = htons(पातed_io_req->task->rxwr_txrd.var_ctx.rx_id);

retry_rrq:
	rc = bnx2fc_initiate_els(tgt, ELS_RRQ, &rrq, माप(rrq),
				 bnx2fc_rrq_compl, cb_arg,
				 r_a_tov);
	अगर (rc == -ENOMEM) अणु
		अगर (समय_after(jअगरfies, start + (10 * HZ))) अणु
			BNX2FC_ELS_DBG("rrq Failed\n");
			rc = FAILED;
			जाओ rrq_err;
		पूर्ण
		msleep(20);
		जाओ retry_rrq;
	पूर्ण
rrq_err:
	अगर (rc) अणु
		BNX2FC_ELS_DBG("RRQ failed - release orig io req 0x%x\n",
			पातed_io_req->xid);
		kमुक्त(cb_arg);
		spin_lock_bh(&tgt->tgt_lock);
		kref_put(&पातed_io_req->refcount, bnx2fc_cmd_release);
		spin_unlock_bh(&tgt->tgt_lock);
	पूर्ण
	वापस rc;
पूर्ण

अटल व्योम bnx2fc_l2_els_compl(काष्ठा bnx2fc_els_cb_arg *cb_arg)
अणु
	काष्ठा bnx2fc_cmd *els_req;
	काष्ठा bnx2fc_rport *tgt;
	काष्ठा bnx2fc_mp_req *mp_req;
	काष्ठा fc_frame_header *fc_hdr;
	अचिन्हित अक्षर *buf;
	व्योम *resp_buf;
	u32 resp_len, hdr_len;
	u16 l2_oxid;
	पूर्णांक frame_len;
	पूर्णांक rc = 0;

	l2_oxid = cb_arg->l2_oxid;
	BNX2FC_ELS_DBG("ELS COMPL - l2_oxid = 0x%x\n", l2_oxid);

	els_req = cb_arg->io_req;
	अगर (test_and_clear_bit(BNX2FC_FLAG_ELS_TIMEOUT, &els_req->req_flags)) अणु
		/*
		 * els req is समयd out. cleanup the IO with FW and
		 * drop the completion. libfc will handle the els समयout
		 */
		अगर (els_req->on_active_queue) अणु
			list_del_init(&els_req->link);
			els_req->on_active_queue = 0;
			rc = bnx2fc_initiate_cleanup(els_req);
			BUG_ON(rc);
		पूर्ण
		जाओ मुक्त_arg;
	पूर्ण

	tgt = els_req->tgt;
	mp_req = &(els_req->mp_req);
	fc_hdr = &(mp_req->resp_fc_hdr);
	resp_len = mp_req->resp_len;
	resp_buf = mp_req->resp_buf;

	buf = kzalloc(PAGE_SIZE, GFP_ATOMIC);
	अगर (!buf) अणु
		prपूर्णांकk(KERN_ERR PFX "Unable to alloc mp buf\n");
		जाओ मुक्त_arg;
	पूर्ण
	hdr_len = माप(*fc_hdr);
	अगर (hdr_len + resp_len > PAGE_SIZE) अणु
		prपूर्णांकk(KERN_ERR PFX "l2_els_compl: resp len is "
				    "beyond page size\n");
		जाओ मुक्त_buf;
	पूर्ण
	स_नकल(buf, fc_hdr, hdr_len);
	स_नकल(buf + hdr_len, resp_buf, resp_len);
	frame_len = hdr_len + resp_len;

	bnx2fc_process_l2_frame_compl(tgt, buf, frame_len, l2_oxid);

मुक्त_buf:
	kमुक्त(buf);
मुक्त_arg:
	kमुक्त(cb_arg);
पूर्ण

पूर्णांक bnx2fc_send_adisc(काष्ठा bnx2fc_rport *tgt, काष्ठा fc_frame *fp)
अणु
	काष्ठा fc_els_adisc *adisc;
	काष्ठा fc_frame_header *fh;
	काष्ठा bnx2fc_els_cb_arg *cb_arg;
	काष्ठा fc_lport *lport = tgt->rdata->local_port;
	u32 r_a_tov = lport->r_a_tov;
	पूर्णांक rc;

	fh = fc_frame_header_get(fp);
	cb_arg = kzalloc(माप(काष्ठा bnx2fc_els_cb_arg), GFP_ATOMIC);
	अगर (!cb_arg) अणु
		prपूर्णांकk(KERN_ERR PFX "Unable to allocate cb_arg for ADISC\n");
		वापस -ENOMEM;
	पूर्ण

	cb_arg->l2_oxid = ntohs(fh->fh_ox_id);

	BNX2FC_ELS_DBG("send ADISC: l2_oxid = 0x%x\n", cb_arg->l2_oxid);
	adisc = fc_frame_payload_get(fp, माप(*adisc));
	/* adisc is initialized by libfc */
	rc = bnx2fc_initiate_els(tgt, ELS_ADISC, adisc, माप(*adisc),
				 bnx2fc_l2_els_compl, cb_arg, 2 * r_a_tov);
	अगर (rc)
		kमुक्त(cb_arg);
	वापस rc;
पूर्ण

पूर्णांक bnx2fc_send_logo(काष्ठा bnx2fc_rport *tgt, काष्ठा fc_frame *fp)
अणु
	काष्ठा fc_els_logo *logo;
	काष्ठा fc_frame_header *fh;
	काष्ठा bnx2fc_els_cb_arg *cb_arg;
	काष्ठा fc_lport *lport = tgt->rdata->local_port;
	u32 r_a_tov = lport->r_a_tov;
	पूर्णांक rc;

	fh = fc_frame_header_get(fp);
	cb_arg = kzalloc(माप(काष्ठा bnx2fc_els_cb_arg), GFP_ATOMIC);
	अगर (!cb_arg) अणु
		prपूर्णांकk(KERN_ERR PFX "Unable to allocate cb_arg for LOGO\n");
		वापस -ENOMEM;
	पूर्ण

	cb_arg->l2_oxid = ntohs(fh->fh_ox_id);

	BNX2FC_ELS_DBG("Send LOGO: l2_oxid = 0x%x\n", cb_arg->l2_oxid);
	logo = fc_frame_payload_get(fp, माप(*logo));
	/* logo is initialized by libfc */
	rc = bnx2fc_initiate_els(tgt, ELS_LOGO, logo, माप(*logo),
				 bnx2fc_l2_els_compl, cb_arg, 2 * r_a_tov);
	अगर (rc)
		kमुक्त(cb_arg);
	वापस rc;
पूर्ण

पूर्णांक bnx2fc_send_rls(काष्ठा bnx2fc_rport *tgt, काष्ठा fc_frame *fp)
अणु
	काष्ठा fc_els_rls *rls;
	काष्ठा fc_frame_header *fh;
	काष्ठा bnx2fc_els_cb_arg *cb_arg;
	काष्ठा fc_lport *lport = tgt->rdata->local_port;
	u32 r_a_tov = lport->r_a_tov;
	पूर्णांक rc;

	fh = fc_frame_header_get(fp);
	cb_arg = kzalloc(माप(काष्ठा bnx2fc_els_cb_arg), GFP_ATOMIC);
	अगर (!cb_arg) अणु
		prपूर्णांकk(KERN_ERR PFX "Unable to allocate cb_arg for LOGO\n");
		वापस -ENOMEM;
	पूर्ण

	cb_arg->l2_oxid = ntohs(fh->fh_ox_id);

	rls = fc_frame_payload_get(fp, माप(*rls));
	/* rls is initialized by libfc */
	rc = bnx2fc_initiate_els(tgt, ELS_RLS, rls, माप(*rls),
				  bnx2fc_l2_els_compl, cb_arg, 2 * r_a_tov);
	अगर (rc)
		kमुक्त(cb_arg);
	वापस rc;
पूर्ण

अटल व्योम bnx2fc_srr_compl(काष्ठा bnx2fc_els_cb_arg *cb_arg)
अणु
	काष्ठा bnx2fc_mp_req *mp_req;
	काष्ठा fc_frame_header *fc_hdr, *fh;
	काष्ठा bnx2fc_cmd *srr_req;
	काष्ठा bnx2fc_cmd *orig_io_req;
	काष्ठा fc_frame *fp;
	अचिन्हित अक्षर *buf;
	व्योम *resp_buf;
	u32 resp_len, hdr_len;
	u8 opcode;
	पूर्णांक rc = 0;

	orig_io_req = cb_arg->पातed_io_req;
	srr_req = cb_arg->io_req;
	अगर (test_and_clear_bit(BNX2FC_FLAG_ELS_TIMEOUT, &srr_req->req_flags)) अणु
		/* SRR समयकरोut */
		BNX2FC_IO_DBG(srr_req, "srr timed out, abort "
		       "orig_io - 0x%x\n",
			orig_io_req->xid);
		rc = bnx2fc_initiate_abts(srr_req);
		अगर (rc != SUCCESS) अणु
			BNX2FC_IO_DBG(srr_req, "srr_compl: initiate_abts "
				"failed. issue cleanup\n");
			bnx2fc_initiate_cleanup(srr_req);
		पूर्ण
		अगर (test_bit(BNX2FC_FLAG_IO_COMPL, &orig_io_req->req_flags) ||
		    test_bit(BNX2FC_FLAG_ISSUE_ABTS, &orig_io_req->req_flags)) अणु
			BNX2FC_IO_DBG(srr_req, "srr_compl:xid 0x%x flags = %lx",
				      orig_io_req->xid, orig_io_req->req_flags);
			जाओ srr_compl_करोne;
		पूर्ण
		orig_io_req->srr_retry++;
		अगर (orig_io_req->srr_retry <= SRR_RETRY_COUNT) अणु
			काष्ठा bnx2fc_rport *tgt = orig_io_req->tgt;
			spin_unlock_bh(&tgt->tgt_lock);
			rc = bnx2fc_send_srr(orig_io_req,
					     orig_io_req->srr_offset,
					     orig_io_req->srr_rctl);
			spin_lock_bh(&tgt->tgt_lock);
			अगर (!rc)
				जाओ srr_compl_करोne;
		पूर्ण

		rc = bnx2fc_initiate_abts(orig_io_req);
		अगर (rc != SUCCESS) अणु
			BNX2FC_IO_DBG(srr_req, "srr_compl: initiate_abts "
				"failed xid = 0x%x. issue cleanup\n",
				orig_io_req->xid);
			bnx2fc_initiate_cleanup(orig_io_req);
		पूर्ण
		जाओ srr_compl_करोne;
	पूर्ण
	अगर (test_bit(BNX2FC_FLAG_IO_COMPL, &orig_io_req->req_flags) ||
	    test_bit(BNX2FC_FLAG_ISSUE_ABTS, &orig_io_req->req_flags)) अणु
		BNX2FC_IO_DBG(srr_req, "srr_compl:xid - 0x%x flags = %lx",
			      orig_io_req->xid, orig_io_req->req_flags);
		जाओ srr_compl_करोne;
	पूर्ण
	mp_req = &(srr_req->mp_req);
	fc_hdr = &(mp_req->resp_fc_hdr);
	resp_len = mp_req->resp_len;
	resp_buf = mp_req->resp_buf;

	hdr_len = माप(*fc_hdr);
	buf = kzalloc(PAGE_SIZE, GFP_ATOMIC);
	अगर (!buf) अणु
		prपूर्णांकk(KERN_ERR PFX "srr buf: mem alloc failure\n");
		जाओ srr_compl_करोne;
	पूर्ण
	स_नकल(buf, fc_hdr, hdr_len);
	स_नकल(buf + hdr_len, resp_buf, resp_len);

	fp = fc_frame_alloc(शून्य, resp_len);
	अगर (!fp) अणु
		prपूर्णांकk(KERN_ERR PFX "fc_frame_alloc failure\n");
		जाओ मुक्त_buf;
	पूर्ण

	fh = (काष्ठा fc_frame_header *) fc_frame_header_get(fp);
	/* Copy FC Frame header and payload पूर्णांकo the frame */
	स_नकल(fh, buf, hdr_len + resp_len);

	opcode = fc_frame_payload_op(fp);
	चयन (opcode) अणु
	हाल ELS_LS_ACC:
		BNX2FC_IO_DBG(srr_req, "SRR success\n");
		अवरोध;
	हाल ELS_LS_RJT:
		BNX2FC_IO_DBG(srr_req, "SRR rejected\n");
		rc = bnx2fc_initiate_abts(orig_io_req);
		अगर (rc != SUCCESS) अणु
			BNX2FC_IO_DBG(srr_req, "srr_compl: initiate_abts "
				"failed xid = 0x%x. issue cleanup\n",
				orig_io_req->xid);
			bnx2fc_initiate_cleanup(orig_io_req);
		पूर्ण
		अवरोध;
	शेष:
		BNX2FC_IO_DBG(srr_req, "srr compl - invalid opcode = %d\n",
			opcode);
		अवरोध;
	पूर्ण
	fc_frame_मुक्त(fp);
मुक्त_buf:
	kमुक्त(buf);
srr_compl_करोne:
	kref_put(&orig_io_req->refcount, bnx2fc_cmd_release);
पूर्ण

अटल व्योम bnx2fc_rec_compl(काष्ठा bnx2fc_els_cb_arg *cb_arg)
अणु
	काष्ठा bnx2fc_cmd *orig_io_req, *new_io_req;
	काष्ठा bnx2fc_cmd *rec_req;
	काष्ठा bnx2fc_mp_req *mp_req;
	काष्ठा fc_frame_header *fc_hdr, *fh;
	काष्ठा fc_els_ls_rjt *rjt;
	काष्ठा fc_els_rec_acc *acc;
	काष्ठा bnx2fc_rport *tgt;
	काष्ठा fcoe_err_report_entry *err_entry;
	काष्ठा scsi_cmnd *sc_cmd;
	क्रमागत fc_rctl r_ctl;
	अचिन्हित अक्षर *buf;
	व्योम *resp_buf;
	काष्ठा fc_frame *fp;
	u8 opcode;
	u32 offset;
	u32 e_stat;
	u32 resp_len, hdr_len;
	पूर्णांक rc = 0;
	bool send_seq_clnp = false;
	bool पात_io = false;

	BNX2FC_MISC_DBG("Entered rec_compl callback\n");
	rec_req = cb_arg->io_req;
	orig_io_req = cb_arg->पातed_io_req;
	BNX2FC_IO_DBG(rec_req, "rec_compl: orig xid = 0x%x", orig_io_req->xid);
	tgt = orig_io_req->tgt;

	/* Handle REC समयout हाल */
	अगर (test_and_clear_bit(BNX2FC_FLAG_ELS_TIMEOUT, &rec_req->req_flags)) अणु
		BNX2FC_IO_DBG(rec_req, "timed out, abort "
		       "orig_io - 0x%x\n",
			orig_io_req->xid);
		/* els req is समयd out. send abts क्रम els */
		rc = bnx2fc_initiate_abts(rec_req);
		अगर (rc != SUCCESS) अणु
			BNX2FC_IO_DBG(rec_req, "rec_compl: initiate_abts "
				"failed. issue cleanup\n");
			bnx2fc_initiate_cleanup(rec_req);
		पूर्ण
		orig_io_req->rec_retry++;
		/* REC समयकरोut. send ABTS to the orig IO req */
		अगर (orig_io_req->rec_retry <= REC_RETRY_COUNT) अणु
			spin_unlock_bh(&tgt->tgt_lock);
			rc = bnx2fc_send_rec(orig_io_req);
			spin_lock_bh(&tgt->tgt_lock);
			अगर (!rc)
				जाओ rec_compl_करोne;
		पूर्ण
		rc = bnx2fc_initiate_abts(orig_io_req);
		अगर (rc != SUCCESS) अणु
			BNX2FC_IO_DBG(rec_req, "rec_compl: initiate_abts "
				"failed xid = 0x%x. issue cleanup\n",
				orig_io_req->xid);
			bnx2fc_initiate_cleanup(orig_io_req);
		पूर्ण
		जाओ rec_compl_करोne;
	पूर्ण

	अगर (test_bit(BNX2FC_FLAG_IO_COMPL, &orig_io_req->req_flags)) अणु
		BNX2FC_IO_DBG(rec_req, "completed"
		       "orig_io - 0x%x\n",
			orig_io_req->xid);
		जाओ rec_compl_करोne;
	पूर्ण
	अगर (test_bit(BNX2FC_FLAG_ISSUE_ABTS, &orig_io_req->req_flags)) अणु
		BNX2FC_IO_DBG(rec_req, "abts in prog "
		       "orig_io - 0x%x\n",
			orig_io_req->xid);
		जाओ rec_compl_करोne;
	पूर्ण

	mp_req = &(rec_req->mp_req);
	fc_hdr = &(mp_req->resp_fc_hdr);
	resp_len = mp_req->resp_len;
	acc = resp_buf = mp_req->resp_buf;

	hdr_len = माप(*fc_hdr);

	buf = kzalloc(PAGE_SIZE, GFP_ATOMIC);
	अगर (!buf) अणु
		prपूर्णांकk(KERN_ERR PFX "rec buf: mem alloc failure\n");
		जाओ rec_compl_करोne;
	पूर्ण
	स_नकल(buf, fc_hdr, hdr_len);
	स_नकल(buf + hdr_len, resp_buf, resp_len);

	fp = fc_frame_alloc(शून्य, resp_len);
	अगर (!fp) अणु
		prपूर्णांकk(KERN_ERR PFX "fc_frame_alloc failure\n");
		जाओ मुक्त_buf;
	पूर्ण

	fh = (काष्ठा fc_frame_header *) fc_frame_header_get(fp);
	/* Copy FC Frame header and payload पूर्णांकo the frame */
	स_नकल(fh, buf, hdr_len + resp_len);

	opcode = fc_frame_payload_op(fp);
	अगर (opcode == ELS_LS_RJT) अणु
		BNX2FC_IO_DBG(rec_req, "opcode is RJT\n");
		rjt = fc_frame_payload_get(fp, माप(*rjt));
		अगर ((rjt->er_reason == ELS_RJT_LOGIC ||
		    rjt->er_reason == ELS_RJT_UNAB) &&
		    rjt->er_explan == ELS_EXPL_OXID_RXID) अणु
			BNX2FC_IO_DBG(rec_req, "handle CMD LOST case\n");
			new_io_req = bnx2fc_cmd_alloc(tgt);
			अगर (!new_io_req)
				जाओ पात_io;
			new_io_req->sc_cmd = orig_io_req->sc_cmd;
			/* cleanup orig_io_req that is with the FW */
			set_bit(BNX2FC_FLAG_CMD_LOST,
				&orig_io_req->req_flags);
			bnx2fc_initiate_cleanup(orig_io_req);
			/* Post a new IO req with the same sc_cmd */
			BNX2FC_IO_DBG(rec_req, "Post IO request again\n");
			rc = bnx2fc_post_io_req(tgt, new_io_req);
			अगर (!rc)
				जाओ मुक्त_frame;
			BNX2FC_IO_DBG(rec_req, "REC: io post err\n");
		पूर्ण
पात_io:
		rc = bnx2fc_initiate_abts(orig_io_req);
		अगर (rc != SUCCESS) अणु
			BNX2FC_IO_DBG(rec_req, "rec_compl: initiate_abts "
				"failed. issue cleanup\n");
			bnx2fc_initiate_cleanup(orig_io_req);
		पूर्ण
	पूर्ण अन्यथा अगर (opcode == ELS_LS_ACC) अणु
		/* REVISIT: Check अगर the exchange is alपढ़ोy पातed */
		offset = ntohl(acc->reca_fc4value);
		e_stat = ntohl(acc->reca_e_stat);
		अगर (e_stat & ESB_ST_SEQ_INIT)  अणु
			BNX2FC_IO_DBG(rec_req, "target has the seq init\n");
			जाओ मुक्त_frame;
		पूर्ण
		BNX2FC_IO_DBG(rec_req, "e_stat = 0x%x, offset = 0x%x\n",
			e_stat, offset);
		/* Seq initiative is with us */
		err_entry = (काष्ठा fcoe_err_report_entry *)
			     &orig_io_req->err_entry;
		sc_cmd = orig_io_req->sc_cmd;
		अगर (sc_cmd->sc_data_direction == DMA_TO_DEVICE) अणु
			/* SCSI WRITE command */
			अगर (offset == orig_io_req->data_xfer_len) अणु
				BNX2FC_IO_DBG(rec_req, "WRITE - resp lost\n");
				/* FCP_RSP lost */
				r_ctl = FC_RCTL_DD_CMD_STATUS;
				offset = 0;
			पूर्ण अन्यथा  अणु
				/* start transmitting from offset */
				BNX2FC_IO_DBG(rec_req, "XFER_RDY/DATA lost\n");
				send_seq_clnp = true;
				r_ctl = FC_RCTL_DD_DATA_DESC;
				अगर (bnx2fc_initiate_seq_cleanup(orig_io_req,
								offset, r_ctl))
					पात_io = true;
				/* XFER_RDY */
			पूर्ण
		पूर्ण अन्यथा अणु
			/* SCSI READ command */
			अगर (err_entry->data.rx_buf_off ==
					orig_io_req->data_xfer_len) अणु
				/* FCP_RSP lost */
				BNX2FC_IO_DBG(rec_req, "READ - resp lost\n");
				r_ctl = FC_RCTL_DD_CMD_STATUS;
				offset = 0;
			पूर्ण अन्यथा  अणु
				/* request retransmission from this offset */
				send_seq_clnp = true;
				offset = err_entry->data.rx_buf_off;
				BNX2FC_IO_DBG(rec_req, "RD DATA lost\n");
				/* FCP_DATA lost */
				r_ctl = FC_RCTL_DD_SOL_DATA;
				अगर (bnx2fc_initiate_seq_cleanup(orig_io_req,
								offset, r_ctl))
					पात_io = true;
			पूर्ण
		पूर्ण
		अगर (पात_io) अणु
			rc = bnx2fc_initiate_abts(orig_io_req);
			अगर (rc != SUCCESS) अणु
				BNX2FC_IO_DBG(rec_req, "rec_compl:initiate_abts"
					      " failed. issue cleanup\n");
				bnx2fc_initiate_cleanup(orig_io_req);
			पूर्ण
		पूर्ण अन्यथा अगर (!send_seq_clnp) अणु
			BNX2FC_IO_DBG(rec_req, "Send SRR - FCP_RSP\n");
			spin_unlock_bh(&tgt->tgt_lock);
			rc = bnx2fc_send_srr(orig_io_req, offset, r_ctl);
			spin_lock_bh(&tgt->tgt_lock);

			अगर (rc) अणु
				BNX2FC_IO_DBG(rec_req, "Unable to send SRR"
					" IO will abort\n");
			पूर्ण
		पूर्ण
	पूर्ण
मुक्त_frame:
	fc_frame_मुक्त(fp);
मुक्त_buf:
	kमुक्त(buf);
rec_compl_करोne:
	kref_put(&orig_io_req->refcount, bnx2fc_cmd_release);
	kमुक्त(cb_arg);
पूर्ण

पूर्णांक bnx2fc_send_rec(काष्ठा bnx2fc_cmd *orig_io_req)
अणु
	काष्ठा fc_els_rec rec;
	काष्ठा bnx2fc_rport *tgt = orig_io_req->tgt;
	काष्ठा fc_lport *lport = tgt->rdata->local_port;
	काष्ठा bnx2fc_els_cb_arg *cb_arg = शून्य;
	u32 sid = tgt->sid;
	u32 r_a_tov = lport->r_a_tov;
	पूर्णांक rc;

	BNX2FC_IO_DBG(orig_io_req, "Sending REC\n");
	स_रखो(&rec, 0, माप(rec));

	cb_arg = kzalloc(माप(काष्ठा bnx2fc_els_cb_arg), GFP_ATOMIC);
	अगर (!cb_arg) अणु
		prपूर्णांकk(KERN_ERR PFX "Unable to allocate cb_arg for REC\n");
		rc = -ENOMEM;
		जाओ rec_err;
	पूर्ण
	kref_get(&orig_io_req->refcount);

	cb_arg->पातed_io_req = orig_io_req;

	rec.rec_cmd = ELS_REC;
	hton24(rec.rec_s_id, sid);
	rec.rec_ox_id = htons(orig_io_req->xid);
	rec.rec_rx_id = htons(orig_io_req->task->rxwr_txrd.var_ctx.rx_id);

	rc = bnx2fc_initiate_els(tgt, ELS_REC, &rec, माप(rec),
				 bnx2fc_rec_compl, cb_arg,
				 r_a_tov);
	अगर (rc) अणु
		BNX2FC_IO_DBG(orig_io_req, "REC failed - release\n");
		spin_lock_bh(&tgt->tgt_lock);
		kref_put(&orig_io_req->refcount, bnx2fc_cmd_release);
		spin_unlock_bh(&tgt->tgt_lock);
		kमुक्त(cb_arg);
	पूर्ण
rec_err:
	वापस rc;
पूर्ण

पूर्णांक bnx2fc_send_srr(काष्ठा bnx2fc_cmd *orig_io_req, u32 offset, u8 r_ctl)
अणु
	काष्ठा fcp_srr srr;
	काष्ठा bnx2fc_rport *tgt = orig_io_req->tgt;
	काष्ठा fc_lport *lport = tgt->rdata->local_port;
	काष्ठा bnx2fc_els_cb_arg *cb_arg = शून्य;
	u32 r_a_tov = lport->r_a_tov;
	पूर्णांक rc;

	BNX2FC_IO_DBG(orig_io_req, "Sending SRR\n");
	स_रखो(&srr, 0, माप(srr));

	cb_arg = kzalloc(माप(काष्ठा bnx2fc_els_cb_arg), GFP_ATOMIC);
	अगर (!cb_arg) अणु
		prपूर्णांकk(KERN_ERR PFX "Unable to allocate cb_arg for SRR\n");
		rc = -ENOMEM;
		जाओ srr_err;
	पूर्ण
	kref_get(&orig_io_req->refcount);

	cb_arg->पातed_io_req = orig_io_req;

	srr.srr_op = ELS_SRR;
	srr.srr_ox_id = htons(orig_io_req->xid);
	srr.srr_rx_id = htons(orig_io_req->task->rxwr_txrd.var_ctx.rx_id);
	srr.srr_rel_off = htonl(offset);
	srr.srr_r_ctl = r_ctl;
	orig_io_req->srr_offset = offset;
	orig_io_req->srr_rctl = r_ctl;

	rc = bnx2fc_initiate_els(tgt, ELS_SRR, &srr, माप(srr),
				 bnx2fc_srr_compl, cb_arg,
				 r_a_tov);
	अगर (rc) अणु
		BNX2FC_IO_DBG(orig_io_req, "SRR failed - release\n");
		spin_lock_bh(&tgt->tgt_lock);
		kref_put(&orig_io_req->refcount, bnx2fc_cmd_release);
		spin_unlock_bh(&tgt->tgt_lock);
		kमुक्त(cb_arg);
	पूर्ण अन्यथा
		set_bit(BNX2FC_FLAG_SRR_SENT, &orig_io_req->req_flags);

srr_err:
	वापस rc;
पूर्ण

अटल पूर्णांक bnx2fc_initiate_els(काष्ठा bnx2fc_rport *tgt, अचिन्हित पूर्णांक op,
			व्योम *data, u32 data_len,
			व्योम (*cb_func)(काष्ठा bnx2fc_els_cb_arg *cb_arg),
			काष्ठा bnx2fc_els_cb_arg *cb_arg, u32 समयr_msec)
अणु
	काष्ठा fcoe_port *port = tgt->port;
	काष्ठा bnx2fc_पूर्णांकerface *पूर्णांकerface = port->priv;
	काष्ठा fc_rport *rport = tgt->rport;
	काष्ठा fc_lport *lport = port->lport;
	काष्ठा bnx2fc_cmd *els_req;
	काष्ठा bnx2fc_mp_req *mp_req;
	काष्ठा fc_frame_header *fc_hdr;
	काष्ठा fcoe_task_ctx_entry *task;
	काष्ठा fcoe_task_ctx_entry *task_page;
	पूर्णांक rc = 0;
	पूर्णांक task_idx, index;
	u32 did, sid;
	u16 xid;

	rc = fc_remote_port_chkपढ़ोy(rport);
	अगर (rc) अणु
		prपूर्णांकk(KERN_ERR PFX "els 0x%x: rport not ready\n", op);
		rc = -EINVAL;
		जाओ els_err;
	पूर्ण
	अगर (lport->state != LPORT_ST_READY || !(lport->link_up)) अणु
		prपूर्णांकk(KERN_ERR PFX "els 0x%x: link is not ready\n", op);
		rc = -EINVAL;
		जाओ els_err;
	पूर्ण
	अगर (!(test_bit(BNX2FC_FLAG_SESSION_READY, &tgt->flags))) अणु
		prपूर्णांकk(KERN_ERR PFX "els 0x%x: tgt not ready\n", op);
		rc = -EINVAL;
		जाओ els_err;
	पूर्ण
	els_req = bnx2fc_elsपंचांग_alloc(tgt, BNX2FC_ELS);
	अगर (!els_req) अणु
		rc = -ENOMEM;
		जाओ els_err;
	पूर्ण

	els_req->sc_cmd = शून्य;
	els_req->port = port;
	els_req->tgt = tgt;
	els_req->cb_func = cb_func;
	cb_arg->io_req = els_req;
	els_req->cb_arg = cb_arg;
	els_req->data_xfer_len = data_len;

	mp_req = (काष्ठा bnx2fc_mp_req *)&(els_req->mp_req);
	rc = bnx2fc_init_mp_req(els_req);
	अगर (rc == FAILED) अणु
		prपूर्णांकk(KERN_ERR PFX "ELS MP request init failed\n");
		spin_lock_bh(&tgt->tgt_lock);
		kref_put(&els_req->refcount, bnx2fc_cmd_release);
		spin_unlock_bh(&tgt->tgt_lock);
		rc = -ENOMEM;
		जाओ els_err;
	पूर्ण अन्यथा अणु
		/* rc SUCCESS */
		rc = 0;
	पूर्ण

	/* Set the data_xfer_len to the size of ELS payload */
	mp_req->req_len = data_len;
	els_req->data_xfer_len = mp_req->req_len;

	/* Fill ELS Payload */
	अगर ((op >= ELS_LS_RJT) && (op <= ELS_AUTH_ELS)) अणु
		स_नकल(mp_req->req_buf, data, data_len);
	पूर्ण अन्यथा अणु
		prपूर्णांकk(KERN_ERR PFX "Invalid ELS op 0x%x\n", op);
		els_req->cb_func = शून्य;
		els_req->cb_arg = शून्य;
		spin_lock_bh(&tgt->tgt_lock);
		kref_put(&els_req->refcount, bnx2fc_cmd_release);
		spin_unlock_bh(&tgt->tgt_lock);
		rc = -EINVAL;
	पूर्ण

	अगर (rc)
		जाओ els_err;

	/* Fill FC header */
	fc_hdr = &(mp_req->req_fc_hdr);

	did = tgt->rport->port_id;
	sid = tgt->sid;

	अगर (op == ELS_SRR)
		__fc_fill_fc_hdr(fc_hdr, FC_RCTL_ELS4_REQ, did, sid,
				   FC_TYPE_FCP, FC_FC_FIRST_SEQ |
				   FC_FC_END_SEQ | FC_FC_SEQ_INIT, 0);
	अन्यथा
		__fc_fill_fc_hdr(fc_hdr, FC_RCTL_ELS_REQ, did, sid,
				   FC_TYPE_ELS, FC_FC_FIRST_SEQ |
				   FC_FC_END_SEQ | FC_FC_SEQ_INIT, 0);

	/* Obtain exchange id */
	xid = els_req->xid;
	task_idx = xid/BNX2FC_TASKS_PER_PAGE;
	index = xid % BNX2FC_TASKS_PER_PAGE;

	/* Initialize task context क्रम this IO request */
	task_page = (काष्ठा fcoe_task_ctx_entry *)
			पूर्णांकerface->hba->task_ctx[task_idx];
	task = &(task_page[index]);
	bnx2fc_init_mp_task(els_req, task);

	spin_lock_bh(&tgt->tgt_lock);

	अगर (!test_bit(BNX2FC_FLAG_SESSION_READY, &tgt->flags)) अणु
		prपूर्णांकk(KERN_ERR PFX "initiate_els.. session not ready\n");
		els_req->cb_func = शून्य;
		els_req->cb_arg = शून्य;
		kref_put(&els_req->refcount, bnx2fc_cmd_release);
		spin_unlock_bh(&tgt->tgt_lock);
		वापस -EINVAL;
	पूर्ण

	अगर (समयr_msec)
		bnx2fc_cmd_समयr_set(els_req, समयr_msec);
	bnx2fc_add_2_sq(tgt, xid);

	els_req->on_active_queue = 1;
	list_add_tail(&els_req->link, &tgt->els_queue);

	/* Ring करोorbell */
	bnx2fc_ring_करोorbell(tgt);
	spin_unlock_bh(&tgt->tgt_lock);

els_err:
	वापस rc;
पूर्ण

व्योम bnx2fc_process_els_compl(काष्ठा bnx2fc_cmd *els_req,
			      काष्ठा fcoe_task_ctx_entry *task, u8 num_rq)
अणु
	काष्ठा bnx2fc_mp_req *mp_req;
	काष्ठा fc_frame_header *fc_hdr;
	u64 *hdr;
	u64 *temp_hdr;

	BNX2FC_ELS_DBG("Entered process_els_compl xid = 0x%x"
			"cmd_type = %d\n", els_req->xid, els_req->cmd_type);

	अगर (test_and_set_bit(BNX2FC_FLAG_ELS_DONE,
			     &els_req->req_flags)) अणु
		BNX2FC_ELS_DBG("Timer context finished processing this "
			   "els - 0x%x\n", els_req->xid);
		/* This IO करोesn't receive cleanup completion */
		kref_put(&els_req->refcount, bnx2fc_cmd_release);
		वापस;
	पूर्ण

	/* Cancel the समयout_work, as we received the response */
	अगर (cancel_delayed_work(&els_req->समयout_work))
		kref_put(&els_req->refcount,
			 bnx2fc_cmd_release); /* drop समयr hold */

	अगर (els_req->on_active_queue) अणु
		list_del_init(&els_req->link);
		els_req->on_active_queue = 0;
	पूर्ण

	mp_req = &(els_req->mp_req);
	fc_hdr = &(mp_req->resp_fc_hdr);

	hdr = (u64 *)fc_hdr;
	temp_hdr = (u64 *)
		&task->rxwr_only.जोड़_ctx.comp_info.mp_rsp.fc_hdr;
	hdr[0] = cpu_to_be64(temp_hdr[0]);
	hdr[1] = cpu_to_be64(temp_hdr[1]);
	hdr[2] = cpu_to_be64(temp_hdr[2]);

	mp_req->resp_len =
		task->rxwr_only.जोड़_ctx.comp_info.mp_rsp.mp_payload_len;

	/* Parse ELS response */
	अगर ((els_req->cb_func) && (els_req->cb_arg)) अणु
		els_req->cb_func(els_req->cb_arg);
		els_req->cb_arg = शून्य;
	पूर्ण

	kref_put(&els_req->refcount, bnx2fc_cmd_release);
पूर्ण

#घोषणा		BNX2FC_FCOE_MAC_METHOD_GRANGED_MAC	1
#घोषणा		BNX2FC_FCOE_MAC_METHOD_FCF_MAP		2
#घोषणा		BNX2FC_FCOE_MAC_METHOD_FCOE_SET_MAC	3
अटल व्योम bnx2fc_flogi_resp(काष्ठा fc_seq *seq, काष्ठा fc_frame *fp,
			      व्योम *arg)
अणु
	काष्ठा fcoe_ctlr *fip = arg;
	काष्ठा fc_exch *exch = fc_seq_exch(seq);
	काष्ठा fc_lport *lport = exch->lp;

	काष्ठा fc_frame_header *fh;
	u8 *granted_mac;
	u8 fcoe_mac[6];
	u8 fc_map[3];
	पूर्णांक method;

	अगर (IS_ERR(fp))
		जाओ करोne;

	fh = fc_frame_header_get(fp);
	granted_mac = fr_cb(fp)->granted_mac;

	/*
	 * We set the source MAC क्रम FCoE traffic based on the Granted MAC
	 * address from the चयन.
	 *
	 * If granted_mac is non-zero, we use that.
	 * If the granted_mac is zeroed out, create the FCoE MAC based on
	 * the sel_fcf->fc_map and the d_id fo the FLOGI frame.
	 * If sel_fcf->fc_map is 0, then we use the शेष FCF-MAC plus the
	 * d_id of the FLOGI frame.
	 */
	अगर (!is_zero_ether_addr(granted_mac)) अणु
		ether_addr_copy(fcoe_mac, granted_mac);
		method = BNX2FC_FCOE_MAC_METHOD_GRANGED_MAC;
	पूर्ण अन्यथा अगर (fip->sel_fcf && fip->sel_fcf->fc_map != 0) अणु
		hton24(fc_map, fip->sel_fcf->fc_map);
		fcoe_mac[0] = fc_map[0];
		fcoe_mac[1] = fc_map[1];
		fcoe_mac[2] = fc_map[2];
		fcoe_mac[3] = fh->fh_d_id[0];
		fcoe_mac[4] = fh->fh_d_id[1];
		fcoe_mac[5] = fh->fh_d_id[2];
		method = BNX2FC_FCOE_MAC_METHOD_FCF_MAP;
	पूर्ण अन्यथा अणु
		fc_fcoe_set_mac(fcoe_mac, fh->fh_d_id);
		method = BNX2FC_FCOE_MAC_METHOD_FCOE_SET_MAC;
	पूर्ण

	BNX2FC_HBA_DBG(lport, "fcoe_mac=%pM method=%d\n", fcoe_mac, method);
	fip->update_mac(lport, fcoe_mac);
करोne:
	fc_lport_flogi_resp(seq, fp, lport);
पूर्ण

अटल व्योम bnx2fc_logo_resp(काष्ठा fc_seq *seq, काष्ठा fc_frame *fp,
			     व्योम *arg)
अणु
	काष्ठा fcoe_ctlr *fip = arg;
	काष्ठा fc_exch *exch = fc_seq_exch(seq);
	काष्ठा fc_lport *lport = exch->lp;
	अटल u8 zero_mac[ETH_ALEN] = अणु 0 पूर्ण;

	अगर (!IS_ERR(fp))
		fip->update_mac(lport, zero_mac);
	fc_lport_logo_resp(seq, fp, lport);
पूर्ण

काष्ठा fc_seq *bnx2fc_elsct_send(काष्ठा fc_lport *lport, u32 did,
				      काष्ठा fc_frame *fp, अचिन्हित पूर्णांक op,
				      व्योम (*resp)(काष्ठा fc_seq *,
						   काष्ठा fc_frame *,
						   व्योम *),
				      व्योम *arg, u32 समयout)
अणु
	काष्ठा fcoe_port *port = lport_priv(lport);
	काष्ठा bnx2fc_पूर्णांकerface *पूर्णांकerface = port->priv;
	काष्ठा fcoe_ctlr *fip = bnx2fc_to_ctlr(पूर्णांकerface);
	काष्ठा fc_frame_header *fh = fc_frame_header_get(fp);

	चयन (op) अणु
	हाल ELS_FLOGI:
	हाल ELS_FDISC:
		वापस fc_elsct_send(lport, did, fp, op, bnx2fc_flogi_resp,
				     fip, समयout);
	हाल ELS_LOGO:
		/* only hook onto fabric logouts, not port logouts */
		अगर (ntoh24(fh->fh_d_id) != FC_FID_FLOGI)
			अवरोध;
		वापस fc_elsct_send(lport, did, fp, op, bnx2fc_logo_resp,
				     fip, समयout);
	पूर्ण
	वापस fc_elsct_send(lport, did, fp, op, resp, arg, समयout);
पूर्ण
