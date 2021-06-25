<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * QLogic iSCSI HBA Driver
 * Copyright (c)  2003-2013 QLogic Corporation
 */

#समावेश "ql4_def.h"
#समावेश "ql4_glbl.h"
#समावेश "ql4_dbg.h"
#समावेश "ql4_inline.h"

/**
 * qla4xxx_copy_sense - copy sense data	पूर्णांकo cmd sense buffer
 * @ha: Poपूर्णांकer to host adapter काष्ठाure.
 * @sts_entry: Poपूर्णांकer to status entry काष्ठाure.
 * @srb: Poपूर्णांकer to srb काष्ठाure.
 **/
अटल व्योम qla4xxx_copy_sense(काष्ठा scsi_qla_host *ha,
                               काष्ठा status_entry *sts_entry,
                               काष्ठा srb *srb)
अणु
	काष्ठा scsi_cmnd *cmd = srb->cmd;
	uपूर्णांक16_t sense_len;

	स_रखो(cmd->sense_buffer, 0, SCSI_SENSE_BUFFERSIZE);
	sense_len = le16_to_cpu(sts_entry->senseDataByteCnt);
	अगर (sense_len == 0) अणु
		DEBUG2(ql4_prपूर्णांकk(KERN_INFO, ha, "scsi%ld:%d:%d:%llu: %s:"
				  " sense len 0\n", ha->host_no,
				  cmd->device->channel, cmd->device->id,
				  cmd->device->lun, __func__));
		ha->status_srb = शून्य;
		वापस;
	पूर्ण
	/* Save total available sense length,
	 * not to exceed cmd's sense buffer size */
	sense_len = min_t(uपूर्णांक16_t, sense_len, SCSI_SENSE_BUFFERSIZE);
	srb->req_sense_ptr = cmd->sense_buffer;
	srb->req_sense_len = sense_len;

	/* Copy sense from sts_entry pkt */
	sense_len = min_t(uपूर्णांक16_t, sense_len, IOCB_MAX_SENSEDATA_LEN);
	स_नकल(cmd->sense_buffer, sts_entry->senseData, sense_len);

	DEBUG2(prपूर्णांकk(KERN_INFO "scsi%ld:%d:%d:%llu: %s: sense key = %x, "
		"ASL= %02x, ASC/ASCQ = %02x/%02x\n", ha->host_no,
		cmd->device->channel, cmd->device->id,
		cmd->device->lun, __func__,
		sts_entry->senseData[2] & 0x0f,
		sts_entry->senseData[7],
		sts_entry->senseData[12],
		sts_entry->senseData[13]));

	DEBUG5(qla4xxx_dump_buffer(cmd->sense_buffer, sense_len));
	srb->flags |= SRB_GOT_SENSE;

	/* Update srb, in हाल a sts_cont pkt follows */
	srb->req_sense_ptr += sense_len;
	srb->req_sense_len -= sense_len;
	अगर (srb->req_sense_len != 0)
		ha->status_srb = srb;
	अन्यथा
		ha->status_srb = शून्य;
पूर्ण

/**
 * qla4xxx_status_cont_entry - Process a Status Continuations entry.
 * @ha: SCSI driver HA context
 * @sts_cont: Entry poपूर्णांकer
 *
 * Extended sense data.
 */
अटल व्योम
qla4xxx_status_cont_entry(काष्ठा scsi_qla_host *ha,
			  काष्ठा status_cont_entry *sts_cont)
अणु
	काष्ठा srb *srb = ha->status_srb;
	काष्ठा scsi_cmnd *cmd;
	uपूर्णांक16_t sense_len;

	अगर (srb == शून्य)
		वापस;

	cmd = srb->cmd;
	अगर (cmd == शून्य) अणु
		DEBUG2(prपूर्णांकk(KERN_INFO "scsi%ld: %s: Cmd already returned "
			"back to OS srb=%p srb->state:%d\n", ha->host_no,
			__func__, srb, srb->state));
		ha->status_srb = शून्य;
		वापस;
	पूर्ण

	/* Copy sense data. */
	sense_len = min_t(uपूर्णांक16_t, srb->req_sense_len,
			  IOCB_MAX_EXT_SENSEDATA_LEN);
	स_नकल(srb->req_sense_ptr, sts_cont->ext_sense_data, sense_len);
	DEBUG5(qla4xxx_dump_buffer(srb->req_sense_ptr, sense_len));

	srb->req_sense_ptr += sense_len;
	srb->req_sense_len -= sense_len;

	/* Place command on करोne queue. */
	अगर (srb->req_sense_len == 0) अणु
		kref_put(&srb->srb_ref, qla4xxx_srb_compl);
		ha->status_srb = शून्य;
	पूर्ण
पूर्ण

/**
 * qla4xxx_status_entry - processes status IOCBs
 * @ha: Poपूर्णांकer to host adapter काष्ठाure.
 * @sts_entry: Poपूर्णांकer to status entry काष्ठाure.
 **/
अटल व्योम qla4xxx_status_entry(काष्ठा scsi_qla_host *ha,
				 काष्ठा status_entry *sts_entry)
अणु
	uपूर्णांक8_t scsi_status;
	काष्ठा scsi_cmnd *cmd;
	काष्ठा srb *srb;
	काष्ठा ddb_entry *ddb_entry;
	uपूर्णांक32_t residual;

	srb = qla4xxx_del_from_active_array(ha, le32_to_cpu(sts_entry->handle));
	अगर (!srb) अणु
		ql4_prपूर्णांकk(KERN_WARNING, ha, "%s invalid status entry: "
			   "handle=0x%0x, srb=%p\n", __func__,
			   sts_entry->handle, srb);
		अगर (is_qla80XX(ha))
			set_bit(DPC_RESET_HA_FW_CONTEXT, &ha->dpc_flags);
		अन्यथा
			set_bit(DPC_RESET_HA, &ha->dpc_flags);
		वापस;
	पूर्ण

	cmd = srb->cmd;
	अगर (cmd == शून्य) अणु
		DEBUG2(prपूर्णांकk("scsi%ld: %s: Command already returned back to "
			      "OS pkt->handle=%d srb=%p srb->state:%d\n",
			      ha->host_no, __func__, sts_entry->handle,
			      srb, srb->state));
		ql4_prपूर्णांकk(KERN_WARNING, ha, "Command is NULL:"
		    " already returned to OS (srb=%p)\n", srb);
		वापस;
	पूर्ण

	ddb_entry = srb->ddb;
	अगर (ddb_entry == शून्य) अणु
		cmd->result = DID_NO_CONNECT << 16;
		जाओ status_entry_निकास;
	पूर्ण

	residual = le32_to_cpu(sts_entry->residualByteCnt);

	/* Translate ISP error to a Linux SCSI error. */
	scsi_status = sts_entry->scsiStatus;
	चयन (sts_entry->completionStatus) अणु
	हाल SCS_COMPLETE:

		अगर (sts_entry->iscsiFlags & ISCSI_FLAG_RESIDUAL_OVER) अणु
			cmd->result = DID_ERROR << 16;
			अवरोध;
		पूर्ण

		अगर (sts_entry->iscsiFlags &ISCSI_FLAG_RESIDUAL_UNDER) अणु
			scsi_set_resid(cmd, residual);
			अगर (!scsi_status && ((scsi_bufflen(cmd) - residual) <
				cmd->underflow)) अणु

				cmd->result = DID_ERROR << 16;

				DEBUG2(prपूर्णांकk("scsi%ld:%d:%d:%llu: %s: "
					"Mid-layer Data underrun0, "
					"xferlen = 0x%x, "
					"residual = 0x%x\n", ha->host_no,
					cmd->device->channel,
					cmd->device->id,
					cmd->device->lun, __func__,
					scsi_bufflen(cmd), residual));
				अवरोध;
			पूर्ण
		पूर्ण

		cmd->result = DID_OK << 16 | scsi_status;

		अगर (scsi_status != SAM_STAT_CHECK_CONDITION)
			अवरोध;

		/* Copy Sense Data पूर्णांकo sense buffer. */
		qla4xxx_copy_sense(ha, sts_entry, srb);
		अवरोध;

	हाल SCS_INCOMPLETE:
		/* Always set the status to DID_ERROR, since
		 * all conditions result in that status anyway */
		cmd->result = DID_ERROR << 16;
		अवरोध;

	हाल SCS_RESET_OCCURRED:
		DEBUG2(prपूर्णांकk("scsi%ld:%d:%d:%llu: %s: Device RESET occurred\n",
			      ha->host_no, cmd->device->channel,
			      cmd->device->id, cmd->device->lun, __func__));

		cmd->result = DID_RESET << 16;
		अवरोध;

	हाल SCS_ABORTED:
		DEBUG2(prपूर्णांकk("scsi%ld:%d:%d:%llu: %s: Abort occurred\n",
			      ha->host_no, cmd->device->channel,
			      cmd->device->id, cmd->device->lun, __func__));

		cmd->result = DID_RESET << 16;
		अवरोध;

	हाल SCS_TIMEOUT:
		DEBUG2(prपूर्णांकk(KERN_INFO "scsi%ld:%d:%d:%llu: Timeout\n",
			      ha->host_no, cmd->device->channel,
			      cmd->device->id, cmd->device->lun));

		cmd->result = DID_TRANSPORT_DISRUPTED << 16;

		/*
		 * Mark device missing so that we won't जारी to send
		 * I/O to this device.	We should get a ddb state change
		 * AEN soon.
		 */
		अगर (iscsi_is_session_online(ddb_entry->sess))
			qla4xxx_mark_device_missing(ddb_entry->sess);
		अवरोध;

	हाल SCS_DATA_UNDERRUN:
	हाल SCS_DATA_OVERRUN:
		अगर ((sts_entry->iscsiFlags & ISCSI_FLAG_RESIDUAL_OVER) ||
		     (sts_entry->completionStatus == SCS_DATA_OVERRUN)) अणु
			DEBUG2(prपूर्णांकk("scsi%ld:%d:%d:%llu: %s: " "Data overrun\n",
				      ha->host_no,
				      cmd->device->channel, cmd->device->id,
				      cmd->device->lun, __func__));

			cmd->result = DID_ERROR << 16;
			अवरोध;
		पूर्ण

		scsi_set_resid(cmd, residual);

		अगर (sts_entry->iscsiFlags & ISCSI_FLAG_RESIDUAL_UNDER) अणु

			/* Both the firmware and target reported UNDERRUN:
			 *
			 * MID-LAYER UNDERFLOW हाल:
			 * Some kernels करो not properly detect midlayer
			 * underflow, so we manually check it and वापस
			 * ERROR अगर the minimum required data was not
			 * received.
			 *
			 * ALL OTHER हालs:
			 * Fall thru to check scsi_status
			 */
			अगर (!scsi_status && (scsi_bufflen(cmd) - residual) <
			    cmd->underflow) अणु
				DEBUG2(ql4_prपूर्णांकk(KERN_INFO, ha,
						  "scsi%ld:%d:%d:%llu: %s: Mid-layer Data underrun, xferlen = 0x%x,residual = 0x%x\n",
						   ha->host_no,
						   cmd->device->channel,
						   cmd->device->id,
						   cmd->device->lun, __func__,
						   scsi_bufflen(cmd),
						   residual));

				cmd->result = DID_ERROR << 16;
				अवरोध;
			पूर्ण

		पूर्ण अन्यथा अगर (scsi_status != SAM_STAT_TASK_SET_FULL &&
			   scsi_status != SAM_STAT_BUSY) अणु

			/*
			 * The firmware reports UNDERRUN, but the target करोes
			 * not report it:
			 *
			 *   scsi_status     |    host_byte       device_byte
			 *                   |     (19:16)          (7:0)
			 *   =============   |    =========       ===========
			 *   TASK_SET_FULL   |    DID_OK          scsi_status
			 *   BUSY            |    DID_OK          scsi_status
			 *   ALL OTHERS      |    DID_ERROR       scsi_status
			 *
			 *   Note: If scsi_status is task set full or busy,
			 *   then this अन्यथा अगर would fall thru to check the
			 *   scsi_status and वापस DID_OK.
			 */

			DEBUG2(ql4_prपूर्णांकk(KERN_INFO, ha,
					  "scsi%ld:%d:%d:%llu: %s: Dropped frame(s) detected (0x%x of 0x%x bytes).\n",
					  ha->host_no,
					  cmd->device->channel,
					  cmd->device->id,
					  cmd->device->lun, __func__,
					  residual,
					  scsi_bufflen(cmd)));

			cmd->result = DID_ERROR << 16 | scsi_status;
			जाओ check_scsi_status;
		पूर्ण

		cmd->result = DID_OK << 16 | scsi_status;

check_scsi_status:
		अगर (scsi_status == SAM_STAT_CHECK_CONDITION)
			qla4xxx_copy_sense(ha, sts_entry, srb);

		अवरोध;

	हाल SCS_DEVICE_LOGGED_OUT:
	हाल SCS_DEVICE_UNAVAILABLE:
		DEBUG2(prपूर्णांकk(KERN_INFO "scsi%ld:%d:%d:%llu: SCS_DEVICE "
		    "state: 0x%x\n", ha->host_no,
		    cmd->device->channel, cmd->device->id,
		    cmd->device->lun, sts_entry->completionStatus));
		/*
		 * Mark device missing so that we won't जारी to
		 * send I/O to this device.  We should get a ddb
		 * state change AEN soon.
		 */
		अगर (iscsi_is_session_online(ddb_entry->sess))
			qla4xxx_mark_device_missing(ddb_entry->sess);

		cmd->result = DID_TRANSPORT_DISRUPTED << 16;
		अवरोध;

	हाल SCS_QUEUE_FULL:
		/*
		 * SCSI Mid-Layer handles device queue full
		 */
		cmd->result = DID_OK << 16 | sts_entry->scsiStatus;
		DEBUG2(prपूर्णांकk("scsi%ld:%d:%llu: %s: QUEUE FULL detected "
			      "compl=%02x, scsi=%02x, state=%02x, iFlags=%02x,"
			      " iResp=%02x\n", ha->host_no, cmd->device->id,
			      cmd->device->lun, __func__,
			      sts_entry->completionStatus,
			      sts_entry->scsiStatus, sts_entry->state_flags,
			      sts_entry->iscsiFlags,
			      sts_entry->iscsiResponse));
		अवरोध;

	शेष:
		cmd->result = DID_ERROR << 16;
		अवरोध;
	पूर्ण

status_entry_निकास:

	/* complete the request, अगर not रुकोing क्रम status_continuation pkt */
	srb->cc_stat = sts_entry->completionStatus;
	अगर (ha->status_srb == शून्य)
		kref_put(&srb->srb_ref, qla4xxx_srb_compl);
पूर्ण

/**
 * qla4xxx_passthru_status_entry - processes passthru status IOCBs (0x3C)
 * @ha: Poपूर्णांकer to host adapter काष्ठाure.
 * @sts_entry: Poपूर्णांकer to status entry काष्ठाure.
 **/
अटल व्योम qla4xxx_passthru_status_entry(काष्ठा scsi_qla_host *ha,
					  काष्ठा passthru_status *sts_entry)
अणु
	काष्ठा iscsi_task *task;
	काष्ठा ddb_entry *ddb_entry;
	काष्ठा ql4_task_data *task_data;
	काष्ठा iscsi_cls_conn *cls_conn;
	काष्ठा iscsi_conn *conn;
	itt_t itt;
	uपूर्णांक32_t fw_ddb_index;

	itt = sts_entry->handle;
	fw_ddb_index = le32_to_cpu(sts_entry->target);

	ddb_entry = qla4xxx_lookup_ddb_by_fw_index(ha, fw_ddb_index);

	अगर (ddb_entry == शून्य) अणु
		ql4_prपूर्णांकk(KERN_ERR, ha, "%s: Invalid target index = 0x%x\n",
			   __func__, sts_entry->target);
		वापस;
	पूर्ण

	cls_conn = ddb_entry->conn;
	conn = cls_conn->dd_data;
	spin_lock(&conn->session->back_lock);
	task = iscsi_itt_to_task(conn, itt);
	spin_unlock(&conn->session->back_lock);

	अगर (task == शून्य) अणु
		ql4_prपूर्णांकk(KERN_ERR, ha, "%s: Task is NULL\n", __func__);
		वापस;
	पूर्ण

	task_data = task->dd_data;
	स_नकल(&task_data->sts, sts_entry, माप(काष्ठा passthru_status));
	ha->iocb_cnt -= task_data->iocb_req_cnt;
	queue_work(ha->task_wq, &task_data->task_work);
पूर्ण

अटल काष्ठा mrb *qla4xxx_del_mrb_from_active_array(काष्ठा scsi_qla_host *ha,
						     uपूर्णांक32_t index)
अणु
	काष्ठा mrb *mrb = शून्य;

	/* validate handle and हटाओ from active array */
	अगर (index >= MAX_MRB)
		वापस mrb;

	mrb = ha->active_mrb_array[index];
	ha->active_mrb_array[index] = शून्य;
	अगर (!mrb)
		वापस mrb;

	/* update counters */
	ha->iocb_cnt -= mrb->iocb_cnt;

	वापस mrb;
पूर्ण

अटल व्योम qla4xxx_mbox_status_entry(काष्ठा scsi_qla_host *ha,
				      काष्ठा mbox_status_iocb *mbox_sts_entry)
अणु
	काष्ठा mrb *mrb;
	uपूर्णांक32_t status;
	uपूर्णांक32_t data_size;

	mrb = qla4xxx_del_mrb_from_active_array(ha,
					le32_to_cpu(mbox_sts_entry->handle));

	अगर (mrb == शून्य) अणु
		ql4_prपूर्णांकk(KERN_WARNING, ha, "%s: mrb[%d] is null\n", __func__,
			   mbox_sts_entry->handle);
		वापस;
	पूर्ण

	चयन (mrb->mbox_cmd) अणु
	हाल MBOX_CMD_PING:
		DEBUG2(ql4_prपूर्णांकk(KERN_INFO, ha, "%s: mbox_cmd = 0x%x, "
				  "mbox_sts[0] = 0x%x, mbox_sts[6] = 0x%x\n",
				  __func__, mrb->mbox_cmd,
				  mbox_sts_entry->out_mbox[0],
				  mbox_sts_entry->out_mbox[6]));

		अगर (mbox_sts_entry->out_mbox[0] == MBOX_STS_COMMAND_COMPLETE)
			status = ISCSI_PING_SUCCESS;
		अन्यथा
			status = mbox_sts_entry->out_mbox[6];

		data_size = माप(mbox_sts_entry->out_mbox);

		qla4xxx_post_ping_evt_work(ha, status, mrb->pid, data_size,
					(uपूर्णांक8_t *) mbox_sts_entry->out_mbox);
		अवरोध;

	शेष:
		DEBUG2(ql4_prपूर्णांकk(KERN_WARNING, ha, "%s: invalid mbox_cmd = "
				  "0x%x\n", __func__, mrb->mbox_cmd));
	पूर्ण

	kमुक्त(mrb);
	वापस;
पूर्ण

/**
 * qla4xxx_process_response_queue - process response queue completions
 * @ha: Poपूर्णांकer to host adapter काष्ठाure.
 *
 * This routine process response queue completions in पूर्णांकerrupt context.
 * Hardware_lock locked upon entry
 **/
व्योम qla4xxx_process_response_queue(काष्ठा scsi_qla_host *ha)
अणु
	uपूर्णांक32_t count = 0;
	काष्ठा srb *srb = शून्य;
	काष्ठा status_entry *sts_entry;

	/* Process all responses from response queue */
	जबतक ((ha->response_ptr->signature != RESPONSE_PROCESSED)) अणु
		sts_entry = (काष्ठा status_entry *) ha->response_ptr;
		count++;

		/* Advance poपूर्णांकers क्रम next entry */
		अगर (ha->response_out == (RESPONSE_QUEUE_DEPTH - 1)) अणु
			ha->response_out = 0;
			ha->response_ptr = ha->response_ring;
		पूर्ण अन्यथा अणु
			ha->response_out++;
			ha->response_ptr++;
		पूर्ण

		/* process entry */
		चयन (sts_entry->hdr.entryType) अणु
		हाल ET_STATUS:
			/* Common status */
			qla4xxx_status_entry(ha, sts_entry);
			अवरोध;

		हाल ET_PASSTHRU_STATUS:
			अगर (sts_entry->hdr.प्रणालीDefined == SD_ISCSI_PDU)
				qla4xxx_passthru_status_entry(ha,
					(काष्ठा passthru_status *)sts_entry);
			अन्यथा
				ql4_prपूर्णांकk(KERN_ERR, ha,
					   "%s: Invalid status received\n",
					   __func__);

			अवरोध;

		हाल ET_STATUS_CONTINUATION:
			qla4xxx_status_cont_entry(ha,
				(काष्ठा status_cont_entry *) sts_entry);
			अवरोध;

		हाल ET_COMMAND:
			/* ISP device queue is full. Command not
			 * accepted by ISP.  Queue command क्रम
			 * later */

			srb = qla4xxx_del_from_active_array(ha,
						    le32_to_cpu(sts_entry->
								handle));
			अगर (srb == शून्य)
				जाओ निकास_prq_invalid_handle;

			DEBUG2(prपूर्णांकk("scsi%ld: %s: FW device queue full, "
				      "srb %p\n", ha->host_no, __func__, srb));

			/* ETRY normally by sending it back with
			 * DID_BUS_BUSY */
			srb->cmd->result = DID_BUS_BUSY << 16;
			kref_put(&srb->srb_ref, qla4xxx_srb_compl);
			अवरोध;

		हाल ET_CONTINUE:
			/* Just throw away the continuation entries */
			DEBUG2(prपूर्णांकk("scsi%ld: %s: Continuation entry - "
				      "ignoring\n", ha->host_no, __func__));
			अवरोध;

		हाल ET_MBOX_STATUS:
			DEBUG2(ql4_prपूर्णांकk(KERN_INFO, ha,
					  "%s: mbox status IOCB\n", __func__));
			qla4xxx_mbox_status_entry(ha,
					(काष्ठा mbox_status_iocb *)sts_entry);
			अवरोध;

		शेष:
			/*
			 * Invalid entry in response queue, reset RISC
			 * firmware.
			 */
			DEBUG2(prपूर्णांकk("scsi%ld: %s: Invalid entry %x in "
				      "response queue \n", ha->host_no,
				      __func__,
				      sts_entry->hdr.entryType));
			जाओ निकास_prq_error;
		पूर्ण
		((काष्ठा response *)sts_entry)->signature = RESPONSE_PROCESSED;
		wmb();
	पूर्ण

	/*
	 * Tell ISP we're करोne with response(s). This also clears the पूर्णांकerrupt.
	 */
	ha->isp_ops->complete_iocb(ha);

	वापस;

निकास_prq_invalid_handle:
	DEBUG2(prपूर्णांकk("scsi%ld: %s: Invalid handle(srb)=%p type=%x IOCS=%x\n",
		      ha->host_no, __func__, srb, sts_entry->hdr.entryType,
		      sts_entry->completionStatus));

निकास_prq_error:
	ha->isp_ops->complete_iocb(ha);
	set_bit(DPC_RESET_HA, &ha->dpc_flags);
पूर्ण

/**
 * qla4_83xx_loopback_in_progress: Is loopback in progress?
 * @ha: Poपूर्णांकer to host adapter काष्ठाure.
 * वापसs: 1 = loopback in progress, 0 = loopback not in progress
 **/
अटल पूर्णांक qla4_83xx_loopback_in_progress(काष्ठा scsi_qla_host *ha)
अणु
	पूर्णांक rval = 1;

	अगर (is_qla8032(ha) || is_qla8042(ha)) अणु
		अगर ((ha->idc_info.info2 & ENABLE_INTERNAL_LOOPBACK) ||
		    (ha->idc_info.info2 & ENABLE_EXTERNAL_LOOPBACK)) अणु
			DEBUG2(ql4_prपूर्णांकk(KERN_INFO, ha,
					  "%s: Loopback diagnostics in progress\n",
					  __func__));
			rval = 1;
		पूर्ण अन्यथा अणु
			DEBUG2(ql4_prपूर्णांकk(KERN_INFO, ha,
					  "%s: Loopback diagnostics not in progress\n",
					  __func__));
			rval = 0;
		पूर्ण
	पूर्ण

	वापस rval;
पूर्ण

अटल व्योम qla4xxx_update_ipaddr_state(काष्ठा scsi_qla_host *ha,
					uपूर्णांक32_t ipaddr_idx,
					uपूर्णांक32_t ipaddr_fw_state)
अणु
	uपूर्णांक8_t ipaddr_state;
	uपूर्णांक8_t ip_idx;

	ip_idx = ipaddr_idx & 0xF;
	ipaddr_state = qla4xxx_set_ipaddr_state((uपूर्णांक8_t)ipaddr_fw_state);

	चयन (ip_idx) अणु
	हाल 0:
		ha->ip_config.ipv4_addr_state = ipaddr_state;
		अवरोध;
	हाल 1:
		ha->ip_config.ipv6_link_local_state = ipaddr_state;
		अवरोध;
	हाल 2:
		ha->ip_config.ipv6_addr0_state = ipaddr_state;
		अवरोध;
	हाल 3:
		ha->ip_config.ipv6_addr1_state = ipaddr_state;
		अवरोध;
	शेष:
		ql4_prपूर्णांकk(KERN_INFO, ha, "%s: Invalid IPADDR index %d\n",
			   __func__, ip_idx);
	पूर्ण
पूर्ण

अटल व्योम qla4xxx_शेष_router_changed(काष्ठा scsi_qla_host *ha,
					   uपूर्णांक32_t *mbox_sts)
अणु
	स_नकल(&ha->ip_config.ipv6_शेष_router_addr.s6_addr32[0],
	       &mbox_sts[2], माप(uपूर्णांक32_t));
	स_नकल(&ha->ip_config.ipv6_शेष_router_addr.s6_addr32[1],
	       &mbox_sts[3], माप(uपूर्णांक32_t));
	स_नकल(&ha->ip_config.ipv6_शेष_router_addr.s6_addr32[2],
	       &mbox_sts[4], माप(uपूर्णांक32_t));
	स_नकल(&ha->ip_config.ipv6_शेष_router_addr.s6_addr32[3],
	       &mbox_sts[5], माप(uपूर्णांक32_t));
पूर्ण

/**
 * qla4xxx_isr_decode_mailbox - decodes mailbox status
 * @ha: Poपूर्णांकer to host adapter काष्ठाure.
 * @mbox_status: Mailbox status.
 *
 * This routine decodes the mailbox status during the ISR.
 * Hardware_lock locked upon entry. runs in पूर्णांकerrupt context.
 **/
अटल व्योम qla4xxx_isr_decode_mailbox(काष्ठा scsi_qla_host * ha,
				       uपूर्णांक32_t mbox_status)
अणु
	पूर्णांक i;
	uपूर्णांक32_t mbox_sts[MBOX_AEN_REG_COUNT];
	__le32 __iomem *mailbox_out;
	uपूर्णांक32_t opcode = 0;

	अगर (is_qla8032(ha) || is_qla8042(ha))
		mailbox_out = &ha->qla4_83xx_reg->mailbox_out[0];
	अन्यथा अगर (is_qla8022(ha))
		mailbox_out = &ha->qla4_82xx_reg->mailbox_out[0];
	अन्यथा
		mailbox_out = &ha->reg->mailbox[0];

	अगर ((mbox_status == MBOX_STS_BUSY) ||
	    (mbox_status == MBOX_STS_INTERMEDIATE_COMPLETION) ||
	    (mbox_status >> 12 == MBOX_COMPLETION_STATUS)) अणु
		ha->mbox_status[0] = mbox_status;

		अगर (test_bit(AF_MBOX_COMMAND, &ha->flags)) अणु
			/*
			 * Copy all mailbox रेजिस्टरs to a temporary
			 * location and set mailbox command करोne flag
			 */
			क्रम (i = 0; i < ha->mbox_status_count; i++)
				ha->mbox_status[i] = पढ़ोl(&mailbox_out[i]);

			set_bit(AF_MBOX_COMMAND_DONE, &ha->flags);

			अगर (test_bit(AF_MBOX_COMMAND_NOPOLL, &ha->flags))
				complete(&ha->mbx_पूर्णांकr_comp);
		पूर्ण
	पूर्ण अन्यथा अगर (mbox_status >> 12 == MBOX_ASYNC_EVENT_STATUS) अणु
		क्रम (i = 0; i < MBOX_AEN_REG_COUNT; i++)
			mbox_sts[i] = पढ़ोl(&mailbox_out[i]);

		/* Immediately process the AENs that करोn't require much work.
		 * Only queue the database_changed AENs */
		अगर (ha->aen_log.count < MAX_AEN_ENTRIES) अणु
			क्रम (i = 0; i < MBOX_AEN_REG_COUNT; i++)
				ha->aen_log.entry[ha->aen_log.count].mbox_sts[i] =
				    mbox_sts[i];
			ha->aen_log.count++;
		पूर्ण
		चयन (mbox_status) अणु
		हाल MBOX_ASTS_SYSTEM_ERROR:
			/* Log Mailbox रेजिस्टरs */
			ql4_prपूर्णांकk(KERN_INFO, ha, "%s: System Err\n", __func__);
			qla4xxx_dump_रेजिस्टरs(ha);

			अगर ((is_qla8022(ha) && ql4xकरोntresethba) ||
			    ((is_qla8032(ha) || is_qla8042(ha)) &&
			     qla4_83xx_idc_करोntreset(ha))) अणु
				DEBUG2(prपूर्णांकk("scsi%ld: %s:Don't Reset HBA\n",
				    ha->host_no, __func__));
			पूर्ण अन्यथा अणु
				set_bit(AF_GET_CRASH_RECORD, &ha->flags);
				set_bit(DPC_RESET_HA, &ha->dpc_flags);
			पूर्ण
			अवरोध;

		हाल MBOX_ASTS_REQUEST_TRANSFER_ERROR:
		हाल MBOX_ASTS_RESPONSE_TRANSFER_ERROR:
		हाल MBOX_ASTS_NVRAM_INVALID:
		हाल MBOX_ASTS_IP_ADDRESS_CHANGED:
		हाल MBOX_ASTS_DHCP_LEASE_EXPIRED:
			DEBUG2(prपूर्णांकk("scsi%ld: AEN %04x, ERROR Status, "
				      "Reset HA\n", ha->host_no, mbox_status));
			अगर (is_qla80XX(ha))
				set_bit(DPC_RESET_HA_FW_CONTEXT,
					&ha->dpc_flags);
			अन्यथा
				set_bit(DPC_RESET_HA, &ha->dpc_flags);
			अवरोध;

		हाल MBOX_ASTS_LINK_UP:
			set_bit(AF_LINK_UP, &ha->flags);
			अगर (test_bit(AF_INIT_DONE, &ha->flags))
				set_bit(DPC_LINK_CHANGED, &ha->dpc_flags);

			ql4_prपूर्णांकk(KERN_INFO, ha, "%s: LINK UP\n", __func__);
			qla4xxx_post_aen_work(ha, ISCSI_EVENT_LINKUP,
					      माप(mbox_sts),
					      (uपूर्णांक8_t *) mbox_sts);

			अगर ((is_qla8032(ha) || is_qla8042(ha)) &&
			    ha->notअगरy_link_up_comp)
				complete(&ha->link_up_comp);

			अवरोध;

		हाल MBOX_ASTS_LINK_DOWN:
			clear_bit(AF_LINK_UP, &ha->flags);
			अगर (test_bit(AF_INIT_DONE, &ha->flags)) अणु
				set_bit(DPC_LINK_CHANGED, &ha->dpc_flags);
				qla4xxx_wake_dpc(ha);
			पूर्ण

			ql4_prपूर्णांकk(KERN_INFO, ha, "%s: LINK DOWN\n", __func__);
			qla4xxx_post_aen_work(ha, ISCSI_EVENT_LINKDOWN,
					      माप(mbox_sts),
					      (uपूर्णांक8_t *) mbox_sts);
			अवरोध;

		हाल MBOX_ASTS_HEARTBEAT:
			ha->seconds_since_last_heartbeat = 0;
			अवरोध;

		हाल MBOX_ASTS_DHCP_LEASE_ACQUIRED:
			DEBUG2(prपूर्णांकk("scsi%ld: AEN %04x DHCP LEASE "
				      "ACQUIRED\n", ha->host_no, mbox_status));
			set_bit(DPC_GET_DHCP_IP_ADDR, &ha->dpc_flags);
			अवरोध;

		हाल MBOX_ASTS_PROTOCOL_STATISTIC_ALARM:
		हाल MBOX_ASTS_SCSI_COMMAND_PDU_REJECTED: /* Target
							   * mode
							   * only */
		हाल MBOX_ASTS_UNSOLICITED_PDU_RECEIVED:  /* Connection mode */
		हाल MBOX_ASTS_IPSEC_SYSTEM_FATAL_ERROR:
		हाल MBOX_ASTS_SUBNET_STATE_CHANGE:
		हाल MBOX_ASTS_DUPLICATE_IP:
			/* No action */
			DEBUG2(prपूर्णांकk("scsi%ld: AEN %04x\n", ha->host_no,
				      mbox_status));
			अवरोध;

		हाल MBOX_ASTS_IP_ADDR_STATE_CHANGED:
			prपूर्णांकk("scsi%ld: AEN %04x, mbox_sts[2]=%04x, "
			    "mbox_sts[3]=%04x\n", ha->host_no, mbox_sts[0],
			    mbox_sts[2], mbox_sts[3]);

			qla4xxx_update_ipaddr_state(ha, mbox_sts[5],
						    mbox_sts[3]);
			/* mbox_sts[2] = Old ACB state
			 * mbox_sts[3] = new ACB state */
			अगर ((mbox_sts[3] == IP_ADDRSTATE_PREFERRED) &&
			    ((mbox_sts[2] == IP_ADDRSTATE_TENTATIVE) ||
			     (mbox_sts[2] == IP_ADDRSTATE_ACQUIRING))) अणु
				set_bit(DPC_GET_DHCP_IP_ADDR, &ha->dpc_flags);
			पूर्ण अन्यथा अगर ((mbox_sts[3] == IP_ADDRSTATE_ACQUIRING) &&
				   (mbox_sts[2] == IP_ADDRSTATE_PREFERRED)) अणु
				अगर (is_qla80XX(ha))
					set_bit(DPC_RESET_HA_FW_CONTEXT,
						&ha->dpc_flags);
				अन्यथा
					set_bit(DPC_RESET_HA, &ha->dpc_flags);
			पूर्ण अन्यथा अगर (mbox_sts[3] == IP_ADDRSTATE_DISABLING) अणु
				ql4_prपूर्णांकk(KERN_INFO, ha, "scsi%ld: %s: ACB in disabling state\n",
					   ha->host_no, __func__);
			पूर्ण अन्यथा अगर (mbox_sts[3] == IP_ADDRSTATE_UNCONFIGURED) अणु
				complete(&ha->disable_acb_comp);
				ql4_prपूर्णांकk(KERN_INFO, ha, "scsi%ld: %s: ACB state unconfigured\n",
					   ha->host_no, __func__);
			पूर्ण
			अवरोध;

		हाल MBOX_ASTS_IPV6_LINK_MTU_CHANGE:
		हाल MBOX_ASTS_IPV6_AUTO_PREFIX_IGNORED:
		हाल MBOX_ASTS_IPV6_ND_LOCAL_PREFIX_IGNORED:
			/* No action */
			DEBUG2(ql4_prपूर्णांकk(KERN_INFO, ha, "scsi%ld: AEN %04x\n",
					  ha->host_no, mbox_status));
			अवरोध;

		हाल MBOX_ASTS_ICMPV6_ERROR_MSG_RCVD:
			DEBUG2(ql4_prपूर्णांकk(KERN_INFO, ha,
					  "scsi%ld: AEN %04x, IPv6 ERROR, "
					  "mbox_sts[1]=%08x, mbox_sts[2]=%08x, mbox_sts[3}=%08x, mbox_sts[4]=%08x mbox_sts[5]=%08x\n",
					  ha->host_no, mbox_sts[0], mbox_sts[1],
					  mbox_sts[2], mbox_sts[3], mbox_sts[4],
					  mbox_sts[5]));
			अवरोध;

		हाल MBOX_ASTS_MAC_ADDRESS_CHANGED:
		हाल MBOX_ASTS_DNS:
			/* No action */
			DEBUG2(prपूर्णांकk(KERN_INFO "scsi%ld: AEN %04x, "
				      "mbox_sts[1]=%04x, mbox_sts[2]=%04x\n",
				      ha->host_no, mbox_sts[0],
				      mbox_sts[1], mbox_sts[2]));
			अवरोध;

		हाल MBOX_ASTS_SELF_TEST_FAILED:
		हाल MBOX_ASTS_LOGIN_FAILED:
			/* No action */
			DEBUG2(prपूर्णांकk("scsi%ld: AEN %04x, mbox_sts[1]=%04x, "
				      "mbox_sts[2]=%04x, mbox_sts[3]=%04x\n",
				      ha->host_no, mbox_sts[0], mbox_sts[1],
				      mbox_sts[2], mbox_sts[3]));
			अवरोध;

		हाल MBOX_ASTS_DATABASE_CHANGED:
			/* Queue AEN inक्रमmation and process it in the DPC
			 * routine */
			अगर (ha->aen_q_count > 0) अणु

				/* decrement available counter */
				ha->aen_q_count--;

				क्रम (i = 0; i < MBOX_AEN_REG_COUNT; i++)
					ha->aen_q[ha->aen_in].mbox_sts[i] =
					    mbox_sts[i];

				/* prपूर्णांक debug message */
				DEBUG2(prपूर्णांकk("scsi%ld: AEN[%d] %04x queued "
					      "mb1:0x%x mb2:0x%x mb3:0x%x "
					      "mb4:0x%x mb5:0x%x\n",
					      ha->host_no, ha->aen_in,
					      mbox_sts[0], mbox_sts[1],
					      mbox_sts[2], mbox_sts[3],
					      mbox_sts[4], mbox_sts[5]));

				/* advance poपूर्णांकer */
				ha->aen_in++;
				अगर (ha->aen_in == MAX_AEN_ENTRIES)
					ha->aen_in = 0;

				/* The DPC routine will process the aen */
				set_bit(DPC_AEN, &ha->dpc_flags);
			पूर्ण अन्यथा अणु
				DEBUG2(prपूर्णांकk("scsi%ld: %s: aen %04x, queue "
					      "overflowed!  AEN LOST!!\n",
					      ha->host_no, __func__,
					      mbox_sts[0]));

				DEBUG2(prपूर्णांकk("scsi%ld: DUMP AEN QUEUE\n",
					      ha->host_no));

				क्रम (i = 0; i < MAX_AEN_ENTRIES; i++) अणु
					DEBUG2(prपूर्णांकk("AEN[%d] %04x %04x %04x "
						      "%04x\n", i, mbox_sts[0],
						      mbox_sts[1], mbox_sts[2],
						      mbox_sts[3]));
				पूर्ण
			पूर्ण
			अवरोध;

		हाल MBOX_ASTS_TXSCVR_INSERTED:
			DEBUG2(prपूर्णांकk(KERN_WARNING
			    "scsi%ld: AEN %04x Transceiver"
			    " inserted\n",  ha->host_no, mbox_sts[0]));
			अवरोध;

		हाल MBOX_ASTS_TXSCVR_REMOVED:
			DEBUG2(prपूर्णांकk(KERN_WARNING
			    "scsi%ld: AEN %04x Transceiver"
			    " removed\n",  ha->host_no, mbox_sts[0]));
			अवरोध;

		हाल MBOX_ASTS_IDC_REQUEST_NOTIFICATION:
			अगर (is_qla8032(ha) || is_qla8042(ha)) अणु
				DEBUG2(ql4_prपूर्णांकk(KERN_INFO, ha,
						  "scsi%ld: AEN %04x, mbox_sts[1]=%08x, mbox_sts[2]=%08x, mbox_sts[3]=%08x, mbox_sts[4]=%08x\n",
						  ha->host_no, mbox_sts[0],
						  mbox_sts[1], mbox_sts[2],
						  mbox_sts[3], mbox_sts[4]));
				opcode = mbox_sts[1] >> 16;
				अगर ((opcode == MBOX_CMD_SET_PORT_CONFIG) ||
				    (opcode == MBOX_CMD_PORT_RESET)) अणु
					set_bit(DPC_POST_IDC_ACK,
						&ha->dpc_flags);
					ha->idc_info.request_desc = mbox_sts[1];
					ha->idc_info.info1 = mbox_sts[2];
					ha->idc_info.info2 = mbox_sts[3];
					ha->idc_info.info3 = mbox_sts[4];
					qla4xxx_wake_dpc(ha);
				पूर्ण
			पूर्ण
			अवरोध;

		हाल MBOX_ASTS_IDC_COMPLETE:
			अगर (is_qla8032(ha) || is_qla8042(ha)) अणु
				DEBUG2(ql4_prपूर्णांकk(KERN_INFO, ha,
						  "scsi%ld: AEN %04x, mbox_sts[1]=%08x, mbox_sts[2]=%08x, mbox_sts[3]=%08x, mbox_sts[4]=%08x\n",
						  ha->host_no, mbox_sts[0],
						  mbox_sts[1], mbox_sts[2],
						  mbox_sts[3], mbox_sts[4]));
				DEBUG2(ql4_prपूर्णांकk(KERN_INFO, ha,
						  "scsi:%ld: AEN %04x IDC Complete notification\n",
						  ha->host_no, mbox_sts[0]));

				opcode = mbox_sts[1] >> 16;
				अगर (ha->notअगरy_idc_comp)
					complete(&ha->idc_comp);

				अगर ((opcode == MBOX_CMD_SET_PORT_CONFIG) ||
				    (opcode == MBOX_CMD_PORT_RESET))
					ha->idc_info.info2 = mbox_sts[3];

				अगर (qla4_83xx_loopback_in_progress(ha)) अणु
					set_bit(AF_LOOPBACK, &ha->flags);
				पूर्ण अन्यथा अणु
					clear_bit(AF_LOOPBACK, &ha->flags);
					अगर (ha->saved_acb)
						set_bit(DPC_RESTORE_ACB,
							&ha->dpc_flags);
				पूर्ण
				qla4xxx_wake_dpc(ha);
			पूर्ण
			अवरोध;

		हाल MBOX_ASTS_IPV6_DEFAULT_ROUTER_CHANGED:
			DEBUG2(ql4_prपूर्णांकk(KERN_INFO, ha,
					  "scsi%ld: AEN %04x, mbox_sts[1]=%08x, mbox_sts[2]=%08x, mbox_sts[3]=%08x, mbox_sts[4]=%08x mbox_sts[5]=%08x\n",
					  ha->host_no, mbox_sts[0], mbox_sts[1],
					  mbox_sts[2], mbox_sts[3], mbox_sts[4],
					  mbox_sts[5]));
			DEBUG2(ql4_prपूर्णांकk(KERN_INFO, ha,
					  "scsi%ld: AEN %04x Received IPv6 default router changed notification\n",
					  ha->host_no, mbox_sts[0]));
			qla4xxx_शेष_router_changed(ha, mbox_sts);
			अवरोध;

		हाल MBOX_ASTS_IDC_TIME_EXTEND_NOTIFICATION:
			DEBUG2(ql4_prपूर्णांकk(KERN_INFO, ha,
					  "scsi%ld: AEN %04x, mbox_sts[1]=%08x, mbox_sts[2]=%08x, mbox_sts[3]=%08x, mbox_sts[4]=%08x mbox_sts[5]=%08x\n",
					  ha->host_no, mbox_sts[0], mbox_sts[1],
					  mbox_sts[2], mbox_sts[3], mbox_sts[4],
					  mbox_sts[5]));
			DEBUG2(ql4_prपूर्णांकk(KERN_INFO, ha,
					  "scsi%ld: AEN %04x Received IDC Extend Timeout notification\n",
					  ha->host_no, mbox_sts[0]));
			/* new IDC समयout */
			ha->idc_extend_पंचांगo = mbox_sts[1];
			अवरोध;

		हाल MBOX_ASTS_INITIALIZATION_FAILED:
			DEBUG2(ql4_prपूर्णांकk(KERN_INFO, ha,
					  "scsi%ld: AEN %04x, mbox_sts[3]=%08x\n",
					  ha->host_no, mbox_sts[0],
					  mbox_sts[3]));
			अवरोध;

		हाल MBOX_ASTS_SYSTEM_WARNING_EVENT:
			DEBUG2(ql4_prपूर्णांकk(KERN_WARNING, ha,
					  "scsi%ld: AEN %04x, mbox_sts[1]=%08x, mbox_sts[2]=%08x, mbox_sts[3]=%08x, mbox_sts[4]=%08x mbox_sts[5]=%08x\n",
					  ha->host_no, mbox_sts[0], mbox_sts[1],
					  mbox_sts[2], mbox_sts[3], mbox_sts[4],
					  mbox_sts[5]));
			अवरोध;

		हाल MBOX_ASTS_DCBX_CONF_CHANGE:
			DEBUG2(ql4_prपूर्णांकk(KERN_INFO, ha,
					  "scsi%ld: AEN %04x, mbox_sts[1]=%08x, mbox_sts[2]=%08x, mbox_sts[3]=%08x, mbox_sts[4]=%08x mbox_sts[5]=%08x\n",
					  ha->host_no, mbox_sts[0], mbox_sts[1],
					  mbox_sts[2], mbox_sts[3], mbox_sts[4],
					  mbox_sts[5]));
			DEBUG2(ql4_prपूर्णांकk(KERN_INFO, ha,
					  "scsi%ld: AEN %04x Received DCBX configuration changed notification\n",
					  ha->host_no, mbox_sts[0]));
			अवरोध;

		शेष:
			DEBUG2(prपूर्णांकk(KERN_WARNING
				      "scsi%ld: AEN %04x UNKNOWN\n",
				      ha->host_no, mbox_sts[0]));
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		DEBUG2(prपूर्णांकk("scsi%ld: Unknown mailbox status %08X\n",
			      ha->host_no, mbox_status));

		ha->mbox_status[0] = mbox_status;
	पूर्ण
पूर्ण

व्योम qla4_83xx_पूर्णांकerrupt_service_routine(काष्ठा scsi_qla_host *ha,
					 uपूर्णांक32_t पूर्णांकr_status)
अणु
	/* Process mailbox/asynch event पूर्णांकerrupt.*/
	अगर (पूर्णांकr_status) अणु
		qla4xxx_isr_decode_mailbox(ha,
				पढ़ोl(&ha->qla4_83xx_reg->mailbox_out[0]));
		/* clear the पूर्णांकerrupt */
		ग_लिखोl(0, &ha->qla4_83xx_reg->risc_पूर्णांकr);
	पूर्ण अन्यथा अणु
		qla4xxx_process_response_queue(ha);
	पूर्ण

	/* clear the पूर्णांकerrupt */
	ग_लिखोl(0, &ha->qla4_83xx_reg->mb_पूर्णांक_mask);
पूर्ण

/**
 * qla4_82xx_पूर्णांकerrupt_service_routine - isr
 * @ha: poपूर्णांकer to host adapter काष्ठाure.
 * @पूर्णांकr_status: Local पूर्णांकerrupt status/type.
 *
 * This is the मुख्य पूर्णांकerrupt service routine.
 * hardware_lock locked upon entry. runs in पूर्णांकerrupt context.
 **/
व्योम qla4_82xx_पूर्णांकerrupt_service_routine(काष्ठा scsi_qla_host *ha,
    uपूर्णांक32_t पूर्णांकr_status)
अणु
	/* Process response queue पूर्णांकerrupt. */
	अगर ((पूर्णांकr_status & HSRX_RISC_IOCB_INT) &&
	    test_bit(AF_INIT_DONE, &ha->flags))
		qla4xxx_process_response_queue(ha);

	/* Process mailbox/asynch event पूर्णांकerrupt.*/
	अगर (पूर्णांकr_status & HSRX_RISC_MB_INT)
		qla4xxx_isr_decode_mailbox(ha,
		    पढ़ोl(&ha->qla4_82xx_reg->mailbox_out[0]));

	/* clear the पूर्णांकerrupt */
	ग_लिखोl(0, &ha->qla4_82xx_reg->host_पूर्णांक);
	पढ़ोl(&ha->qla4_82xx_reg->host_पूर्णांक);
पूर्ण

/**
 * qla4xxx_पूर्णांकerrupt_service_routine - isr
 * @ha: poपूर्णांकer to host adapter काष्ठाure.
 * @पूर्णांकr_status: Local पूर्णांकerrupt status/type.
 *
 * This is the मुख्य पूर्णांकerrupt service routine.
 * hardware_lock locked upon entry. runs in पूर्णांकerrupt context.
 **/
व्योम qla4xxx_पूर्णांकerrupt_service_routine(काष्ठा scsi_qla_host * ha,
				       uपूर्णांक32_t पूर्णांकr_status)
अणु
	/* Process response queue पूर्णांकerrupt. */
	अगर (पूर्णांकr_status & CSR_SCSI_COMPLETION_INTR)
		qla4xxx_process_response_queue(ha);

	/* Process mailbox/asynch event	 पूर्णांकerrupt.*/
	अगर (पूर्णांकr_status & CSR_SCSI_PROCESSOR_INTR) अणु
		qla4xxx_isr_decode_mailbox(ha,
					   पढ़ोl(&ha->reg->mailbox[0]));

		/* Clear Mailbox Interrupt */
		ग_लिखोl(set_rmask(CSR_SCSI_PROCESSOR_INTR),
		       &ha->reg->ctrl_status);
		पढ़ोl(&ha->reg->ctrl_status);
	पूर्ण
पूर्ण

/**
 * qla4_82xx_spurious_पूर्णांकerrupt - processes spurious पूर्णांकerrupt
 * @ha: poपूर्णांकer to host adapter काष्ठाure.
 * @reqs_count: .
 *
 **/
अटल व्योम qla4_82xx_spurious_पूर्णांकerrupt(काष्ठा scsi_qla_host *ha,
    uपूर्णांक8_t reqs_count)
अणु
	अगर (reqs_count)
		वापस;

	DEBUG2(ql4_prपूर्णांकk(KERN_INFO, ha, "Spurious Interrupt\n"));
	अगर (is_qla8022(ha)) अणु
		ग_लिखोl(0, &ha->qla4_82xx_reg->host_पूर्णांक);
		अगर (!ha->pdev->msi_enabled && !ha->pdev->msix_enabled)
			qla4_82xx_wr_32(ha, ha->nx_legacy_पूर्णांकr.tgt_mask_reg,
			    0xfbff);
	पूर्ण
	ha->spurious_पूर्णांक_count++;
पूर्ण

/**
 * qla4xxx_पूर्णांकr_handler - hardware पूर्णांकerrupt handler.
 * @irq: Unused
 * @dev_id: Poपूर्णांकer to host adapter काष्ठाure
 **/
irqवापस_t qla4xxx_पूर्णांकr_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा scsi_qla_host *ha;
	uपूर्णांक32_t पूर्णांकr_status;
	अचिन्हित दीर्घ flags = 0;
	uपूर्णांक8_t reqs_count = 0;

	ha = (काष्ठा scsi_qla_host *) dev_id;
	अगर (!ha) अणु
		DEBUG2(prपूर्णांकk(KERN_INFO
			      "qla4xxx: Interrupt with NULL host ptr\n"));
		वापस IRQ_NONE;
	पूर्ण

	spin_lock_irqsave(&ha->hardware_lock, flags);

	ha->isr_count++;
	/*
	 * Repeatedly service पूर्णांकerrupts up to a maximum of
	 * MAX_REQS_SERVICED_PER_INTR
	 */
	जबतक (1) अणु
		/*
		 * Read पूर्णांकerrupt status
		 */
		अगर (ha->isp_ops->rd_shdw_rsp_q_in(ha) !=
		    ha->response_out)
			पूर्णांकr_status = CSR_SCSI_COMPLETION_INTR;
		अन्यथा
			पूर्णांकr_status = पढ़ोl(&ha->reg->ctrl_status);

		अगर ((पूर्णांकr_status &
		    (CSR_SCSI_RESET_INTR|CSR_FATAL_ERROR|INTR_PENDING)) == 0) अणु
			अगर (reqs_count == 0)
				ha->spurious_पूर्णांक_count++;
			अवरोध;
		पूर्ण

		अगर (पूर्णांकr_status & CSR_FATAL_ERROR) अणु
			DEBUG2(prपूर्णांकk(KERN_INFO "scsi%ld: Fatal Error, "
				      "Status 0x%04x\n", ha->host_no,
				      पढ़ोl(isp_port_error_status (ha))));

			/* Issue Soft Reset to clear this error condition.
			 * This will prevent the RISC from repeatedly
			 * पूर्णांकerrupting the driver; thus, allowing the DPC to
			 * get scheduled to जारी error recovery.
			 * NOTE: Disabling RISC पूर्णांकerrupts करोes not work in
			 * this हाल, as CSR_FATAL_ERROR overrides
			 * CSR_SCSI_INTR_ENABLE */
			अगर ((पढ़ोl(&ha->reg->ctrl_status) &
			     CSR_SCSI_RESET_INTR) == 0) अणु
				ग_लिखोl(set_rmask(CSR_SOFT_RESET),
				       &ha->reg->ctrl_status);
				पढ़ोl(&ha->reg->ctrl_status);
			पूर्ण

			ग_लिखोl(set_rmask(CSR_FATAL_ERROR),
			       &ha->reg->ctrl_status);
			पढ़ोl(&ha->reg->ctrl_status);

			__qla4xxx_disable_पूर्णांकrs(ha);

			set_bit(DPC_RESET_HA, &ha->dpc_flags);

			अवरोध;
		पूर्ण अन्यथा अगर (पूर्णांकr_status & CSR_SCSI_RESET_INTR) अणु
			clear_bit(AF_ONLINE, &ha->flags);
			__qla4xxx_disable_पूर्णांकrs(ha);

			ग_लिखोl(set_rmask(CSR_SCSI_RESET_INTR),
			       &ha->reg->ctrl_status);
			पढ़ोl(&ha->reg->ctrl_status);

			अगर (!test_bit(AF_HA_REMOVAL, &ha->flags))
				set_bit(DPC_RESET_HA_INTR, &ha->dpc_flags);

			अवरोध;
		पूर्ण अन्यथा अगर (पूर्णांकr_status & INTR_PENDING) अणु
			ha->isp_ops->पूर्णांकerrupt_service_routine(ha, पूर्णांकr_status);
			ha->total_io_count++;
			अगर (++reqs_count == MAX_REQS_SERVICED_PER_INTR)
				अवरोध;
		पूर्ण
	पूर्ण

	spin_unlock_irqrestore(&ha->hardware_lock, flags);

	वापस IRQ_HANDLED;
पूर्ण

/**
 * qla4_82xx_पूर्णांकr_handler - hardware पूर्णांकerrupt handler.
 * @irq: Unused
 * @dev_id: Poपूर्णांकer to host adapter काष्ठाure
 **/
irqवापस_t qla4_82xx_पूर्णांकr_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा scsi_qla_host *ha = dev_id;
	uपूर्णांक32_t पूर्णांकr_status;
	uपूर्णांक32_t status;
	अचिन्हित दीर्घ flags = 0;
	uपूर्णांक8_t reqs_count = 0;

	अगर (unlikely(pci_channel_offline(ha->pdev)))
		वापस IRQ_HANDLED;

	ha->isr_count++;
	status = qla4_82xx_rd_32(ha, ISR_INT_VECTOR);
	अगर (!(status & ha->nx_legacy_पूर्णांकr.पूर्णांक_vec_bit))
		वापस IRQ_NONE;

	status = qla4_82xx_rd_32(ha, ISR_INT_STATE_REG);
	अगर (!ISR_IS_LEGACY_INTR_TRIGGERED(status)) अणु
		DEBUG7(ql4_prपूर्णांकk(KERN_INFO, ha,
				  "%s legacy Int not triggered\n", __func__));
		वापस IRQ_NONE;
	पूर्ण

	/* clear the पूर्णांकerrupt */
	qla4_82xx_wr_32(ha, ha->nx_legacy_पूर्णांकr.tgt_status_reg, 0xffffffff);

	/* पढ़ो twice to ensure ग_लिखो is flushed */
	qla4_82xx_rd_32(ha, ISR_INT_VECTOR);
	qla4_82xx_rd_32(ha, ISR_INT_VECTOR);

	spin_lock_irqsave(&ha->hardware_lock, flags);
	जबतक (1) अणु
		अगर (!(पढ़ोl(&ha->qla4_82xx_reg->host_पूर्णांक) &
		    ISRX_82XX_RISC_INT)) अणु
			qla4_82xx_spurious_पूर्णांकerrupt(ha, reqs_count);
			अवरोध;
		पूर्ण
		पूर्णांकr_status =  पढ़ोl(&ha->qla4_82xx_reg->host_status);
		अगर ((पूर्णांकr_status &
		    (HSRX_RISC_MB_INT | HSRX_RISC_IOCB_INT)) == 0)  अणु
			qla4_82xx_spurious_पूर्णांकerrupt(ha, reqs_count);
			अवरोध;
		पूर्ण

		ha->isp_ops->पूर्णांकerrupt_service_routine(ha, पूर्णांकr_status);

		/* Enable Interrupt */
		qla4_82xx_wr_32(ha, ha->nx_legacy_पूर्णांकr.tgt_mask_reg, 0xfbff);

		अगर (++reqs_count == MAX_REQS_SERVICED_PER_INTR)
			अवरोध;
	पूर्ण

	spin_unlock_irqrestore(&ha->hardware_lock, flags);
	वापस IRQ_HANDLED;
पूर्ण

#घोषणा LEG_INT_PTR_B31		(1 << 31)
#घोषणा LEG_INT_PTR_B30		(1 << 30)
#घोषणा PF_BITS_MASK		(0xF << 16)

/**
 * qla4_83xx_पूर्णांकr_handler - hardware पूर्णांकerrupt handler.
 * @irq: Unused
 * @dev_id: Poपूर्णांकer to host adapter काष्ठाure
 **/
irqवापस_t qla4_83xx_पूर्णांकr_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा scsi_qla_host *ha = dev_id;
	uपूर्णांक32_t leg_पूर्णांक_ptr = 0;
	अचिन्हित दीर्घ flags = 0;

	ha->isr_count++;
	leg_पूर्णांक_ptr = पढ़ोl(&ha->qla4_83xx_reg->leg_पूर्णांक_ptr);

	/* Legacy पूर्णांकerrupt is valid अगर bit31 of leg_पूर्णांक_ptr is set */
	अगर (!(leg_पूर्णांक_ptr & LEG_INT_PTR_B31)) अणु
		DEBUG7(ql4_prपूर्णांकk(KERN_ERR, ha,
				  "%s: Legacy Interrupt Bit 31 not set, spurious interrupt!\n",
				  __func__));
		वापस IRQ_NONE;
	पूर्ण

	/* Validate the PCIE function ID set in leg_पूर्णांक_ptr bits [19..16] */
	अगर ((leg_पूर्णांक_ptr & PF_BITS_MASK) != ha->pf_bit) अणु
		DEBUG7(ql4_prपूर्णांकk(KERN_ERR, ha,
				  "%s: Incorrect function ID 0x%x in legacy interrupt register, ha->pf_bit = 0x%x\n",
				  __func__, (leg_पूर्णांक_ptr & PF_BITS_MASK),
				  ha->pf_bit));
		वापस IRQ_NONE;
	पूर्ण

	/* To de-निश्चित legacy पूर्णांकerrupt, ग_लिखो 0 to Legacy Interrupt Trigger
	 * Control रेजिस्टर and poll till Legacy Interrupt Poपूर्णांकer रेजिस्टर
	 * bit30 is 0.
	 */
	ग_लिखोl(0, &ha->qla4_83xx_reg->leg_पूर्णांक_trig);
	करो अणु
		leg_पूर्णांक_ptr = पढ़ोl(&ha->qla4_83xx_reg->leg_पूर्णांक_ptr);
		अगर ((leg_पूर्णांक_ptr & PF_BITS_MASK) != ha->pf_bit)
			अवरोध;
	पूर्ण जबतक (leg_पूर्णांक_ptr & LEG_INT_PTR_B30);

	spin_lock_irqsave(&ha->hardware_lock, flags);
	leg_पूर्णांक_ptr = पढ़ोl(&ha->qla4_83xx_reg->risc_पूर्णांकr);
	ha->isp_ops->पूर्णांकerrupt_service_routine(ha, leg_पूर्णांक_ptr);
	spin_unlock_irqrestore(&ha->hardware_lock, flags);

	वापस IRQ_HANDLED;
पूर्ण

irqवापस_t
qla4_8xxx_msi_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा scsi_qla_host *ha;

	ha = (काष्ठा scsi_qla_host *) dev_id;
	अगर (!ha) अणु
		DEBUG2(prपूर्णांकk(KERN_INFO
		    "qla4xxx: MSIX: Interrupt with NULL host ptr\n"));
		वापस IRQ_NONE;
	पूर्ण

	ha->isr_count++;
	/* clear the पूर्णांकerrupt */
	qla4_82xx_wr_32(ha, ha->nx_legacy_पूर्णांकr.tgt_status_reg, 0xffffffff);

	/* पढ़ो twice to ensure ग_लिखो is flushed */
	qla4_82xx_rd_32(ha, ISR_INT_VECTOR);
	qla4_82xx_rd_32(ha, ISR_INT_VECTOR);

	वापस qla4_8xxx_शेष_पूर्णांकr_handler(irq, dev_id);
पूर्ण

अटल irqवापस_t qla4_83xx_mailbox_पूर्णांकr_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा scsi_qla_host *ha = dev_id;
	अचिन्हित दीर्घ flags;
	uपूर्णांक32_t ival = 0;

	spin_lock_irqsave(&ha->hardware_lock, flags);

	ival = पढ़ोl(&ha->qla4_83xx_reg->risc_पूर्णांकr);
	अगर (ival == 0) अणु
		ql4_prपूर्णांकk(KERN_INFO, ha,
			   "%s: It is a spurious mailbox interrupt!\n",
			   __func__);
		ival = पढ़ोl(&ha->qla4_83xx_reg->mb_पूर्णांक_mask);
		ival &= ~INT_MASK_FW_MB;
		ग_लिखोl(ival, &ha->qla4_83xx_reg->mb_पूर्णांक_mask);
		जाओ निकास;
	पूर्ण

	qla4xxx_isr_decode_mailbox(ha,
				   पढ़ोl(&ha->qla4_83xx_reg->mailbox_out[0]));
	ग_लिखोl(0, &ha->qla4_83xx_reg->risc_पूर्णांकr);
	ival = पढ़ोl(&ha->qla4_83xx_reg->mb_पूर्णांक_mask);
	ival &= ~INT_MASK_FW_MB;
	ग_लिखोl(ival, &ha->qla4_83xx_reg->mb_पूर्णांक_mask);
	ha->isr_count++;
निकास:
	spin_unlock_irqrestore(&ha->hardware_lock, flags);
	वापस IRQ_HANDLED;
पूर्ण

/**
 * qla4_8xxx_शेष_पूर्णांकr_handler - hardware पूर्णांकerrupt handler.
 * @irq: Unused
 * @dev_id: Poपूर्णांकer to host adapter काष्ठाure
 *
 * This पूर्णांकerrupt handler is called directly क्रम MSI-X, and
 * called indirectly क्रम MSI.
 **/
irqवापस_t
qla4_8xxx_शेष_पूर्णांकr_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा scsi_qla_host *ha = dev_id;
	अचिन्हित दीर्घ   flags;
	uपूर्णांक32_t पूर्णांकr_status;
	uपूर्णांक8_t reqs_count = 0;

	अगर (is_qla8032(ha) || is_qla8042(ha)) अणु
		qla4_83xx_mailbox_पूर्णांकr_handler(irq, dev_id);
	पूर्ण अन्यथा अणु
		spin_lock_irqsave(&ha->hardware_lock, flags);
		जबतक (1) अणु
			अगर (!(पढ़ोl(&ha->qla4_82xx_reg->host_पूर्णांक) &
			    ISRX_82XX_RISC_INT)) अणु
				qla4_82xx_spurious_पूर्णांकerrupt(ha, reqs_count);
				अवरोध;
			पूर्ण

			पूर्णांकr_status =  पढ़ोl(&ha->qla4_82xx_reg->host_status);
			अगर ((पूर्णांकr_status &
			    (HSRX_RISC_MB_INT | HSRX_RISC_IOCB_INT)) == 0) अणु
				qla4_82xx_spurious_पूर्णांकerrupt(ha, reqs_count);
				अवरोध;
			पूर्ण

			ha->isp_ops->पूर्णांकerrupt_service_routine(ha, पूर्णांकr_status);

			अगर (++reqs_count == MAX_REQS_SERVICED_PER_INTR)
				अवरोध;
		पूर्ण
		ha->isr_count++;
		spin_unlock_irqrestore(&ha->hardware_lock, flags);
	पूर्ण
	वापस IRQ_HANDLED;
पूर्ण

irqवापस_t
qla4_8xxx_msix_rsp_q(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा scsi_qla_host *ha = dev_id;
	अचिन्हित दीर्घ flags;
	पूर्णांक पूर्णांकr_status;
	uपूर्णांक32_t ival = 0;

	spin_lock_irqsave(&ha->hardware_lock, flags);
	अगर (is_qla8032(ha) || is_qla8042(ha)) अणु
		ival = पढ़ोl(&ha->qla4_83xx_reg->iocb_पूर्णांक_mask);
		अगर (ival == 0) अणु
			ql4_prपूर्णांकk(KERN_INFO, ha, "%s: It is a spurious iocb interrupt!\n",
				   __func__);
			जाओ निकास_msix_rsp_q;
		पूर्ण
		qla4xxx_process_response_queue(ha);
		ग_लिखोl(0, &ha->qla4_83xx_reg->iocb_पूर्णांक_mask);
	पूर्ण अन्यथा अणु
		पूर्णांकr_status = पढ़ोl(&ha->qla4_82xx_reg->host_status);
		अगर (पूर्णांकr_status & HSRX_RISC_IOCB_INT) अणु
			qla4xxx_process_response_queue(ha);
			ग_लिखोl(0, &ha->qla4_82xx_reg->host_पूर्णांक);
		पूर्ण अन्यथा अणु
			ql4_prपूर्णांकk(KERN_INFO, ha, "%s: spurious iocb interrupt...\n",
				   __func__);
			जाओ निकास_msix_rsp_q;
		पूर्ण
	पूर्ण
	ha->isr_count++;
निकास_msix_rsp_q:
	spin_unlock_irqrestore(&ha->hardware_lock, flags);
	वापस IRQ_HANDLED;
पूर्ण

/**
 * qla4xxx_process_aen - processes AENs generated by firmware
 * @ha: poपूर्णांकer to host adapter काष्ठाure.
 * @process_aen: type of AENs to process
 *
 * Processes specअगरic types of Asynchronous Events generated by firmware.
 * The type of AENs to process is specअगरied by process_aen and can be
 *	PROCESS_ALL_AENS	 0
 *	FLUSH_DDB_CHANGED_AENS	 1
 *	RELOGIN_DDB_CHANGED_AENS 2
 **/
व्योम qla4xxx_process_aen(काष्ठा scsi_qla_host * ha, uपूर्णांक8_t process_aen)
अणु
	uपूर्णांक32_t mbox_sts[MBOX_AEN_REG_COUNT];
	काष्ठा aen *aen;
	पूर्णांक i;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ha->hardware_lock, flags);
	जबतक (ha->aen_out != ha->aen_in) अणु
		aen = &ha->aen_q[ha->aen_out];
		/* copy aen inक्रमmation to local काष्ठाure */
		क्रम (i = 0; i < MBOX_AEN_REG_COUNT; i++)
			mbox_sts[i] = aen->mbox_sts[i];

		ha->aen_q_count++;
		ha->aen_out++;

		अगर (ha->aen_out == MAX_AEN_ENTRIES)
			ha->aen_out = 0;

		spin_unlock_irqrestore(&ha->hardware_lock, flags);

		DEBUG2(prपूर्णांकk("qla4xxx(%ld): AEN[%d]=0x%08x, mbx1=0x%08x mbx2=0x%08x"
			" mbx3=0x%08x mbx4=0x%08x\n", ha->host_no,
			(ha->aen_out ? (ha->aen_out-1): (MAX_AEN_ENTRIES-1)),
			mbox_sts[0], mbox_sts[1], mbox_sts[2],
			mbox_sts[3], mbox_sts[4]));

		चयन (mbox_sts[0]) अणु
		हाल MBOX_ASTS_DATABASE_CHANGED:
			चयन (process_aen) अणु
			हाल FLUSH_DDB_CHANGED_AENS:
				DEBUG2(prपूर्णांकk("scsi%ld: AEN[%d] %04x, index "
					      "[%d] state=%04x FLUSHED!\n",
					      ha->host_no, ha->aen_out,
					      mbox_sts[0], mbox_sts[2],
					      mbox_sts[3]));
				अवरोध;
			हाल PROCESS_ALL_AENS:
			शेष:
				/* Specअगरic device. */
				अगर (mbox_sts[1] == 1)
					qla4xxx_process_ddb_changed(ha,
						mbox_sts[2], mbox_sts[3],
						mbox_sts[4]);
				अवरोध;
			पूर्ण
		पूर्ण
		spin_lock_irqsave(&ha->hardware_lock, flags);
	पूर्ण
	spin_unlock_irqrestore(&ha->hardware_lock, flags);
पूर्ण

पूर्णांक qla4xxx_request_irqs(काष्ठा scsi_qla_host *ha)
अणु
	पूर्णांक ret = 0;
	पूर्णांक rval = QLA_ERROR;

	अगर (is_qla40XX(ha))
		जाओ try_पूर्णांकx;

	अगर (ql4xenablemsix == 2) अणु
		/* Note: MSI Interrupts not supported क्रम ISP8324 and ISP8042 */
		अगर (is_qla8032(ha) || is_qla8042(ha)) अणु
			ql4_prपूर्णांकk(KERN_INFO, ha, "%s: MSI Interrupts not supported for ISP%04x, Falling back-to INTx mode\n",
				   __func__, ha->pdev->device);
			जाओ try_पूर्णांकx;
		पूर्ण
		जाओ try_msi;
	पूर्ण

	अगर (ql4xenablemsix == 0 || ql4xenablemsix != 1)
		जाओ try_पूर्णांकx;

	/* Trying MSI-X */
	ret = qla4_8xxx_enable_msix(ha);
	अगर (!ret) अणु
		DEBUG2(ql4_prपूर्णांकk(KERN_INFO, ha,
		    "MSI-X: Enabled (0x%X).\n", ha->revision_id));
		जाओ irq_attached;
	पूर्ण अन्यथा अणु
		अगर (is_qla8032(ha) || is_qla8042(ha)) अणु
			ql4_prपूर्णांकk(KERN_INFO, ha, "%s: ISP%04x: MSI-X: Falling back-to INTx mode. ret = %d\n",
				   __func__, ha->pdev->device, ret);
			जाओ try_पूर्णांकx;
		पूर्ण
	पूर्ण

	ql4_prपूर्णांकk(KERN_WARNING, ha,
	    "MSI-X: Falling back-to MSI mode -- %d.\n", ret);

try_msi:
	/* Trying MSI */
	ret = pci_alloc_irq_vectors(ha->pdev, 1, 1, PCI_IRQ_MSI);
	अगर (ret > 0) अणु
		ret = request_irq(ha->pdev->irq, qla4_8xxx_msi_handler,
			0, DRIVER_NAME, ha);
		अगर (!ret) अणु
			DEBUG2(ql4_prपूर्णांकk(KERN_INFO, ha, "MSI: Enabled.\n"));
			जाओ irq_attached;
		पूर्ण अन्यथा अणु
			ql4_prपूर्णांकk(KERN_WARNING, ha,
			    "MSI: Failed to reserve interrupt %d "
			    "already in use.\n", ha->pdev->irq);
			pci_मुक्त_irq_vectors(ha->pdev);
		पूर्ण
	पूर्ण

try_पूर्णांकx:
	अगर (is_qla8022(ha)) अणु
		ql4_prपूर्णांकk(KERN_WARNING, ha, "%s: ISP82xx Legacy interrupt not supported\n",
			   __func__);
		जाओ irq_not_attached;
	पूर्ण

	/* Trying INTx */
	ret = request_irq(ha->pdev->irq, ha->isp_ops->पूर्णांकr_handler,
	    IRQF_SHARED, DRIVER_NAME, ha);
	अगर (!ret) अणु
		DEBUG2(ql4_prपूर्णांकk(KERN_INFO, ha, "INTx: Enabled.\n"));
		जाओ irq_attached;

	पूर्ण अन्यथा अणु
		ql4_prपूर्णांकk(KERN_WARNING, ha,
		    "INTx: Failed to reserve interrupt %d already in"
		    " use.\n", ha->pdev->irq);
		जाओ irq_not_attached;
	पूर्ण

irq_attached:
	set_bit(AF_IRQ_ATTACHED, &ha->flags);
	ha->host->irq = ha->pdev->irq;
	ql4_prपूर्णांकk(KERN_INFO, ha, "%s: irq %d attached\n",
		   __func__, ha->pdev->irq);
	rval = QLA_SUCCESS;
irq_not_attached:
	वापस rval;
पूर्ण

व्योम qla4xxx_मुक्त_irqs(काष्ठा scsi_qla_host *ha)
अणु
	अगर (!test_and_clear_bit(AF_IRQ_ATTACHED, &ha->flags))
		वापस;

	अगर (ha->pdev->msix_enabled)
		मुक्त_irq(pci_irq_vector(ha->pdev, 1), ha);
	मुक्त_irq(pci_irq_vector(ha->pdev, 0), ha);
	pci_मुक्त_irq_vectors(ha->pdev);
पूर्ण
