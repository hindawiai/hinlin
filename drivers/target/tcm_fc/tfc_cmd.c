<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2010 Cisco Systems, Inc.
 */

/* XXX TBD some includes may be extraneous */

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/utsname.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/types.h>
#समावेश <linux/माला.स>
#समावेश <linux/configfs.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/hash.h>
#समावेश <यंत्र/unaligned.h>
#समावेश <scsi/scsi_tcq.h>
#समावेश <scsi/libfc.h>

#समावेश <target/target_core_base.h>
#समावेश <target/target_core_fabric.h>

#समावेश "tcm_fc.h"

/*
 * Dump cmd state क्रम debugging.
 */
अटल व्योम _ft_dump_cmd(काष्ठा ft_cmd *cmd, स्थिर अक्षर *caller)
अणु
	काष्ठा fc_exch *ep;
	काष्ठा fc_seq *sp;
	काष्ठा se_cmd *se_cmd;
	काष्ठा scatterlist *sg;
	पूर्णांक count;

	se_cmd = &cmd->se_cmd;
	pr_debug("%s: cmd %p sess %p seq %p se_cmd %p\n",
		caller, cmd, cmd->sess, cmd->seq, se_cmd);

	pr_debug("%s: cmd %p data_nents %u len %u se_cmd_flags <0x%x>\n",
		caller, cmd, se_cmd->t_data_nents,
	       se_cmd->data_length, se_cmd->se_cmd_flags);

	क्रम_each_sg(se_cmd->t_data_sg, sg, se_cmd->t_data_nents, count)
		pr_debug("%s: cmd %p sg %p page %p "
			"len 0x%x off 0x%x\n",
			caller, cmd, sg,
			sg_page(sg), sg->length, sg->offset);

	sp = cmd->seq;
	अगर (sp) अणु
		ep = fc_seq_exch(sp);
		pr_debug("%s: cmd %p sid %x did %x "
			"ox_id %x rx_id %x seq_id %x e_stat %x\n",
			caller, cmd, ep->sid, ep->did, ep->oxid, ep->rxid,
			sp->id, ep->esb_stat);
	पूर्ण
पूर्ण

व्योम ft_dump_cmd(काष्ठा ft_cmd *cmd, स्थिर अक्षर *caller)
अणु
	अगर (unlikely(ft_debug_logging))
		_ft_dump_cmd(cmd, caller);
पूर्ण

अटल व्योम ft_मुक्त_cmd(काष्ठा ft_cmd *cmd)
अणु
	काष्ठा fc_frame *fp;
	काष्ठा ft_sess *sess;

	अगर (!cmd)
		वापस;
	sess = cmd->sess;
	fp = cmd->req_frame;
	अगर (fr_seq(fp))
		fc_seq_release(fr_seq(fp));
	fc_frame_मुक्त(fp);
	target_मुक्त_tag(sess->se_sess, &cmd->se_cmd);
	ft_sess_put(sess);	/* unकरो get from lookup at recv */
पूर्ण

व्योम ft_release_cmd(काष्ठा se_cmd *se_cmd)
अणु
	काष्ठा ft_cmd *cmd = container_of(se_cmd, काष्ठा ft_cmd, se_cmd);

	ft_मुक्त_cmd(cmd);
पूर्ण

पूर्णांक ft_check_stop_मुक्त(काष्ठा se_cmd *se_cmd)
अणु
	वापस transport_generic_मुक्त_cmd(se_cmd, 0);
पूर्ण

/*
 * Send response.
 */
पूर्णांक ft_queue_status(काष्ठा se_cmd *se_cmd)
अणु
	काष्ठा ft_cmd *cmd = container_of(se_cmd, काष्ठा ft_cmd, se_cmd);
	काष्ठा fc_frame *fp;
	काष्ठा fcp_resp_with_ext *fcp;
	काष्ठा fc_lport *lport;
	काष्ठा fc_exch *ep;
	माप_प्रकार len;
	पूर्णांक rc;

	अगर (cmd->पातed)
		वापस 0;
	ft_dump_cmd(cmd, __func__);
	ep = fc_seq_exch(cmd->seq);
	lport = ep->lp;
	len = माप(*fcp) + se_cmd->scsi_sense_length;
	fp = fc_frame_alloc(lport, len);
	अगर (!fp) अणु
		se_cmd->scsi_status = SAM_STAT_TASK_SET_FULL;
		वापस -ENOMEM;
	पूर्ण

	fcp = fc_frame_payload_get(fp, len);
	स_रखो(fcp, 0, len);
	fcp->resp.fr_status = se_cmd->scsi_status;

	len = se_cmd->scsi_sense_length;
	अगर (len) अणु
		fcp->resp.fr_flags |= FCP_SNS_LEN_VAL;
		fcp->ext.fr_sns_len = htonl(len);
		स_नकल((fcp + 1), se_cmd->sense_buffer, len);
	पूर्ण

	/*
	 * Test underflow and overflow with one mask.  Usually both are off.
	 * Bidirectional commands are not handled yet.
	 */
	अगर (se_cmd->se_cmd_flags & (SCF_OVERFLOW_BIT | SCF_UNDERFLOW_BIT)) अणु
		अगर (se_cmd->se_cmd_flags & SCF_OVERFLOW_BIT)
			fcp->resp.fr_flags |= FCP_RESID_OVER;
		अन्यथा
			fcp->resp.fr_flags |= FCP_RESID_UNDER;
		fcp->ext.fr_resid = cpu_to_be32(se_cmd->residual_count);
	पूर्ण

	/*
	 * Send response.
	 */
	cmd->seq = fc_seq_start_next(cmd->seq);
	fc_fill_fc_hdr(fp, FC_RCTL_DD_CMD_STATUS, ep->did, ep->sid, FC_TYPE_FCP,
		       FC_FC_EX_CTX | FC_FC_LAST_SEQ | FC_FC_END_SEQ, 0);

	rc = fc_seq_send(lport, cmd->seq, fp);
	अगर (rc) अणु
		pr_info_ratelimited("%s: Failed to send response frame %p, "
				    "xid <0x%x>\n", __func__, fp, ep->xid);
		/*
		 * Generate a TASK_SET_FULL status to notअगरy the initiator
		 * to reduce it's queue_depth after the se_cmd response has
		 * been re-queued by target-core.
		 */
		se_cmd->scsi_status = SAM_STAT_TASK_SET_FULL;
		वापस -ENOMEM;
	पूर्ण
	fc_exch_करोne(cmd->seq);
	/*
	 * Drop the extra ACK_KREF reference taken by target_submit_cmd()
	 * ahead of ft_check_stop_मुक्त() -> transport_generic_मुक्त_cmd()
	 * final se_cmd->cmd_kref put.
	 */
	target_put_sess_cmd(&cmd->se_cmd);
	वापस 0;
पूर्ण

/*
 * Send TX_RDY (transfer पढ़ोy).
 */
पूर्णांक ft_ग_लिखो_pending(काष्ठा se_cmd *se_cmd)
अणु
	काष्ठा ft_cmd *cmd = container_of(se_cmd, काष्ठा ft_cmd, se_cmd);
	काष्ठा fc_frame *fp;
	काष्ठा fcp_txrdy *txrdy;
	काष्ठा fc_lport *lport;
	काष्ठा fc_exch *ep;
	काष्ठा fc_frame_header *fh;
	u32 f_ctl;

	ft_dump_cmd(cmd, __func__);

	अगर (cmd->पातed)
		वापस 0;
	ep = fc_seq_exch(cmd->seq);
	lport = ep->lp;
	fp = fc_frame_alloc(lport, माप(*txrdy));
	अगर (!fp)
		वापस -ENOMEM; /* Signal QUEUE_FULL */

	txrdy = fc_frame_payload_get(fp, माप(*txrdy));
	स_रखो(txrdy, 0, माप(*txrdy));
	txrdy->ft_burst_len = htonl(se_cmd->data_length);

	cmd->seq = fc_seq_start_next(cmd->seq);
	fc_fill_fc_hdr(fp, FC_RCTL_DD_DATA_DESC, ep->did, ep->sid, FC_TYPE_FCP,
		       FC_FC_EX_CTX | FC_FC_END_SEQ | FC_FC_SEQ_INIT, 0);

	fh = fc_frame_header_get(fp);
	f_ctl = ntoh24(fh->fh_f_ctl);

	/* Only अगर it is 'Exchange Responder' */
	अगर (f_ctl & FC_FC_EX_CTX) अणु
		/* Target is 'exchange responder' and sending XFER_READY
		 * to 'exchange initiator (initiator)'
		 */
		अगर ((ep->xid <= lport->lro_xid) &&
		    (fh->fh_r_ctl == FC_RCTL_DD_DATA_DESC)) अणु
			अगर ((se_cmd->se_cmd_flags & SCF_SCSI_DATA_CDB) &&
			    lport->tt.ddp_target(lport, ep->xid,
						 se_cmd->t_data_sg,
						 se_cmd->t_data_nents))
				cmd->was_ddp_setup = 1;
		पूर्ण
	पूर्ण
	fc_seq_send(lport, cmd->seq, fp);
	वापस 0;
पूर्ण

पूर्णांक ft_get_cmd_state(काष्ठा se_cmd *se_cmd)
अणु
	वापस 0;
पूर्ण

/*
 * FC sequence response handler क्रम follow-on sequences (data) and पातs.
 */
अटल व्योम ft_recv_seq(काष्ठा fc_seq *sp, काष्ठा fc_frame *fp, व्योम *arg)
अणु
	काष्ठा ft_cmd *cmd = arg;
	काष्ठा fc_frame_header *fh;

	अगर (IS_ERR(fp)) अणु
		/* XXX need to find cmd अगर queued */
		cmd->seq = शून्य;
		cmd->पातed = true;
		वापस;
	पूर्ण

	fh = fc_frame_header_get(fp);

	चयन (fh->fh_r_ctl) अणु
	हाल FC_RCTL_DD_SOL_DATA:	/* ग_लिखो data */
		ft_recv_ग_लिखो_data(cmd, fp);
		अवरोध;
	हाल FC_RCTL_DD_UNSOL_CTL:	/* command */
	हाल FC_RCTL_DD_SOL_CTL:	/* transfer पढ़ोy */
	हाल FC_RCTL_DD_DATA_DESC:	/* transfer पढ़ोy */
	शेष:
		pr_debug("%s: unhandled frame r_ctl %x\n",
		       __func__, fh->fh_r_ctl);
		ft_invl_hw_context(cmd);
		fc_frame_मुक्त(fp);
		transport_generic_मुक्त_cmd(&cmd->se_cmd, 0);
		अवरोध;
	पूर्ण
पूर्ण

/*
 * Send a FCP response including SCSI status and optional FCP rsp_code.
 * status is SAM_STAT_GOOD (zero) अगरf code is valid.
 * This is used in error हालs, such as allocation failures.
 */
अटल व्योम ft_send_resp_status(काष्ठा fc_lport *lport,
				स्थिर काष्ठा fc_frame *rx_fp,
				u32 status, क्रमागत fcp_resp_rsp_codes code)
अणु
	काष्ठा fc_frame *fp;
	काष्ठा fc_seq *sp;
	स्थिर काष्ठा fc_frame_header *fh;
	माप_प्रकार len;
	काष्ठा fcp_resp_with_ext *fcp;
	काष्ठा fcp_resp_rsp_info *info;

	fh = fc_frame_header_get(rx_fp);
	pr_debug("FCP error response: did %x oxid %x status %x code %x\n",
		  ntoh24(fh->fh_s_id), ntohs(fh->fh_ox_id), status, code);
	len = माप(*fcp);
	अगर (status == SAM_STAT_GOOD)
		len += माप(*info);
	fp = fc_frame_alloc(lport, len);
	अगर (!fp)
		वापस;
	fcp = fc_frame_payload_get(fp, len);
	स_रखो(fcp, 0, len);
	fcp->resp.fr_status = status;
	अगर (status == SAM_STAT_GOOD) अणु
		fcp->ext.fr_rsp_len = htonl(माप(*info));
		fcp->resp.fr_flags |= FCP_RSP_LEN_VAL;
		info = (काष्ठा fcp_resp_rsp_info *)(fcp + 1);
		info->rsp_code = code;
	पूर्ण

	fc_fill_reply_hdr(fp, rx_fp, FC_RCTL_DD_CMD_STATUS, 0);
	sp = fr_seq(fp);
	अगर (sp) अणु
		fc_seq_send(lport, sp, fp);
		fc_exch_करोne(sp);
	पूर्ण अन्यथा अणु
		lport->tt.frame_send(lport, fp);
	पूर्ण
पूर्ण

/*
 * Send error or task management response.
 */
अटल व्योम ft_send_resp_code(काष्ठा ft_cmd *cmd,
			      क्रमागत fcp_resp_rsp_codes code)
अणु
	ft_send_resp_status(cmd->sess->tport->lport,
			    cmd->req_frame, SAM_STAT_GOOD, code);
पूर्ण


/*
 * Send error or task management response.
 * Always मुक्तs the cmd and associated state.
 */
अटल व्योम ft_send_resp_code_and_मुक्त(काष्ठा ft_cmd *cmd,
				      क्रमागत fcp_resp_rsp_codes code)
अणु
	ft_send_resp_code(cmd, code);
	ft_मुक्त_cmd(cmd);
पूर्ण

/*
 * Handle Task Management Request.
 */
अटल व्योम ft_send_पंचांग(काष्ठा ft_cmd *cmd)
अणु
	काष्ठा fcp_cmnd *fcp;
	पूर्णांक rc;
	u8 पंचांग_func;

	fcp = fc_frame_payload_get(cmd->req_frame, माप(*fcp));

	चयन (fcp->fc_पंचांग_flags) अणु
	हाल FCP_TMF_LUN_RESET:
		पंचांग_func = TMR_LUN_RESET;
		अवरोध;
	हाल FCP_TMF_TGT_RESET:
		पंचांग_func = TMR_TARGET_WARM_RESET;
		अवरोध;
	हाल FCP_TMF_CLR_TASK_SET:
		पंचांग_func = TMR_CLEAR_TASK_SET;
		अवरोध;
	हाल FCP_TMF_ABT_TASK_SET:
		पंचांग_func = TMR_ABORT_TASK_SET;
		अवरोध;
	हाल FCP_TMF_CLR_ACA:
		पंचांग_func = TMR_CLEAR_ACA;
		अवरोध;
	शेष:
		/*
		 * FCP4r01 indicates having a combination of
		 * पंचांग_flags set is invalid.
		 */
		pr_debug("invalid FCP tm_flags %x\n", fcp->fc_पंचांग_flags);
		ft_send_resp_code_and_मुक्त(cmd, FCP_CMND_FIELDS_INVALID);
		वापस;
	पूर्ण

	/* FIXME: Add referenced task tag क्रम ABORT_TASK */
	rc = target_submit_पंचांगr(&cmd->se_cmd, cmd->sess->se_sess,
		&cmd->ft_sense_buffer[0], scsilun_to_पूर्णांक(&fcp->fc_lun),
		cmd, पंचांग_func, GFP_KERNEL, 0, TARGET_SCF_ACK_KREF);
	अगर (rc < 0)
		ft_send_resp_code_and_मुक्त(cmd, FCP_TMF_FAILED);
पूर्ण

/*
 * Send status from completed task management request.
 */
व्योम ft_queue_पंचांग_resp(काष्ठा se_cmd *se_cmd)
अणु
	काष्ठा ft_cmd *cmd = container_of(se_cmd, काष्ठा ft_cmd, se_cmd);
	काष्ठा se_पंचांगr_req *पंचांगr = se_cmd->se_पंचांगr_req;
	क्रमागत fcp_resp_rsp_codes code;

	अगर (cmd->पातed)
		वापस;
	चयन (पंचांगr->response) अणु
	हाल TMR_FUNCTION_COMPLETE:
		code = FCP_TMF_CMPL;
		अवरोध;
	हाल TMR_LUN_DOES_NOT_EXIST:
		code = FCP_TMF_INVALID_LUN;
		अवरोध;
	हाल TMR_FUNCTION_REJECTED:
		code = FCP_TMF_REJECTED;
		अवरोध;
	हाल TMR_TASK_DOES_NOT_EXIST:
	हाल TMR_TASK_MGMT_FUNCTION_NOT_SUPPORTED:
	शेष:
		code = FCP_TMF_FAILED;
		अवरोध;
	पूर्ण
	pr_debug("tmr fn %d resp %d fcp code %d\n",
		  पंचांगr->function, पंचांगr->response, code);
	ft_send_resp_code(cmd, code);
	/*
	 * Drop the extra ACK_KREF reference taken by target_submit_पंचांगr()
	 * ahead of ft_check_stop_मुक्त() -> transport_generic_मुक्त_cmd()
	 * final se_cmd->cmd_kref put.
	 */
	target_put_sess_cmd(&cmd->se_cmd);
पूर्ण

व्योम ft_पातed_task(काष्ठा se_cmd *se_cmd)
अणु
	वापस;
पूर्ण

अटल व्योम ft_send_work(काष्ठा work_काष्ठा *work);

/*
 * Handle incoming FCP command.
 */
अटल व्योम ft_recv_cmd(काष्ठा ft_sess *sess, काष्ठा fc_frame *fp)
अणु
	काष्ठा ft_cmd *cmd;
	काष्ठा fc_lport *lport = sess->tport->lport;
	काष्ठा se_session *se_sess = sess->se_sess;
	पूर्णांक tag, cpu;

	tag = sbiपंचांगap_queue_get(&se_sess->sess_tag_pool, &cpu);
	अगर (tag < 0)
		जाओ busy;

	cmd = &((काष्ठा ft_cmd *)se_sess->sess_cmd_map)[tag];
	स_रखो(cmd, 0, माप(काष्ठा ft_cmd));

	cmd->se_cmd.map_tag = tag;
	cmd->se_cmd.map_cpu = cpu;
	cmd->sess = sess;
	cmd->seq = fc_seq_assign(lport, fp);
	अगर (!cmd->seq) अणु
		target_मुक्त_tag(se_sess, &cmd->se_cmd);
		जाओ busy;
	पूर्ण
	cmd->req_frame = fp;		/* hold frame during cmd */

	INIT_WORK(&cmd->work, ft_send_work);
	queue_work(sess->tport->tpg->workqueue, &cmd->work);
	वापस;

busy:
	pr_debug("cmd or seq allocation failure - sending BUSY\n");
	ft_send_resp_status(lport, fp, SAM_STAT_BUSY, 0);
	fc_frame_मुक्त(fp);
	ft_sess_put(sess);		/* unकरो get from lookup */
पूर्ण


/*
 * Handle incoming FCP frame.
 * Caller has verअगरied that the frame is type FCP.
 */
व्योम ft_recv_req(काष्ठा ft_sess *sess, काष्ठा fc_frame *fp)
अणु
	काष्ठा fc_frame_header *fh = fc_frame_header_get(fp);

	चयन (fh->fh_r_ctl) अणु
	हाल FC_RCTL_DD_UNSOL_CMD:	/* command */
		ft_recv_cmd(sess, fp);
		अवरोध;
	हाल FC_RCTL_DD_SOL_DATA:	/* ग_लिखो data */
	हाल FC_RCTL_DD_UNSOL_CTL:
	हाल FC_RCTL_DD_SOL_CTL:
	हाल FC_RCTL_DD_DATA_DESC:	/* transfer पढ़ोy */
	हाल FC_RCTL_ELS4_REQ:		/* SRR, perhaps */
	शेष:
		pr_debug("%s: unhandled frame r_ctl %x\n",
		       __func__, fh->fh_r_ctl);
		fc_frame_मुक्त(fp);
		ft_sess_put(sess);	/* unकरो get from lookup */
		अवरोध;
	पूर्ण
पूर्ण

/*
 * Send new command to target.
 */
अटल व्योम ft_send_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ft_cmd *cmd = container_of(work, काष्ठा ft_cmd, work);
	काष्ठा fc_frame_header *fh = fc_frame_header_get(cmd->req_frame);
	काष्ठा fcp_cmnd *fcp;
	पूर्णांक data_dir = 0;
	पूर्णांक task_attr;

	fcp = fc_frame_payload_get(cmd->req_frame, माप(*fcp));
	अगर (!fcp)
		जाओ err;

	अगर (fcp->fc_flags & FCP_CFL_LEN_MASK)
		जाओ err;		/* not handling दीर्घer CDBs yet */

	/*
	 * Check क्रम FCP task management flags
	 */
	अगर (fcp->fc_पंचांग_flags) अणु
		ft_send_पंचांग(cmd);
		वापस;
	पूर्ण

	चयन (fcp->fc_flags & (FCP_CFL_RDDATA | FCP_CFL_WRDATA)) अणु
	हाल 0:
		data_dir = DMA_NONE;
		अवरोध;
	हाल FCP_CFL_RDDATA:
		data_dir = DMA_FROM_DEVICE;
		अवरोध;
	हाल FCP_CFL_WRDATA:
		data_dir = DMA_TO_DEVICE;
		अवरोध;
	हाल FCP_CFL_WRDATA | FCP_CFL_RDDATA:
		जाओ err;	/* TBD not supported by tcm_fc yet */
	पूर्ण
	/*
	 * Locate the SAM Task Attr from fc_pri_ta
	 */
	चयन (fcp->fc_pri_ta & FCP_PTA_MASK) अणु
	हाल FCP_PTA_HEADQ:
		task_attr = TCM_HEAD_TAG;
		अवरोध;
	हाल FCP_PTA_ORDERED:
		task_attr = TCM_ORDERED_TAG;
		अवरोध;
	हाल FCP_PTA_ACA:
		task_attr = TCM_ACA_TAG;
		अवरोध;
	हाल FCP_PTA_SIMPLE:
	शेष:
		task_attr = TCM_SIMPLE_TAG;
	पूर्ण

	fc_seq_set_resp(cmd->seq, ft_recv_seq, cmd);
	cmd->se_cmd.tag = fc_seq_exch(cmd->seq)->rxid;

	/*
	 * Use a single se_cmd->cmd_kref as we expect to release se_cmd
	 * directly from ft_check_stop_मुक्त callback in response path.
	 */
	अगर (target_init_cmd(&cmd->se_cmd, cmd->sess->se_sess,
			    &cmd->ft_sense_buffer[0],
			    scsilun_to_पूर्णांक(&fcp->fc_lun), ntohl(fcp->fc_dl),
			    task_attr, data_dir, TARGET_SCF_ACK_KREF))
		जाओ err;

	अगर (target_submit_prep(&cmd->se_cmd, fcp->fc_cdb, शून्य, 0, शून्य, 0,
			       शून्य, 0, GFP_KERNEL))
		वापस;

	target_submit(&cmd->se_cmd);
	pr_debug("r_ctl %x target_submit_cmd %p\n", fh->fh_r_ctl, cmd);
	वापस;

err:
	ft_send_resp_code_and_मुक्त(cmd, FCP_CMND_FIELDS_INVALID);
पूर्ण
