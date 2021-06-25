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

#समावेश <scsi/scsi_tcq.h>

अटल पूर्णांक
qla4xxx_space_in_req_ring(काष्ठा scsi_qla_host *ha, uपूर्णांक16_t req_cnt)
अणु
	uपूर्णांक16_t cnt;

	/* Calculate number of मुक्त request entries. */
	अगर ((req_cnt + 2) >= ha->req_q_count) अणु
		cnt = (uपूर्णांक16_t) ha->isp_ops->rd_shdw_req_q_out(ha);
		अगर (ha->request_in < cnt)
			ha->req_q_count = cnt - ha->request_in;
		अन्यथा
			ha->req_q_count = REQUEST_QUEUE_DEPTH -
						(ha->request_in - cnt);
	पूर्ण

	/* Check अगर room क्रम request in request ring. */
	अगर ((req_cnt + 2) < ha->req_q_count)
		वापस 1;
	अन्यथा
		वापस 0;
पूर्ण

अटल व्योम qla4xxx_advance_req_ring_ptr(काष्ठा scsi_qla_host *ha)
अणु
	/* Advance request queue poपूर्णांकer */
	अगर (ha->request_in == (REQUEST_QUEUE_DEPTH - 1)) अणु
		ha->request_in = 0;
		ha->request_ptr = ha->request_ring;
	पूर्ण अन्यथा अणु
		ha->request_in++;
		ha->request_ptr++;
	पूर्ण
पूर्ण

/**
 * qla4xxx_get_req_pkt - वापसs a valid entry in request queue.
 * @ha: Poपूर्णांकer to host adapter काष्ठाure.
 * @queue_entry: Poपूर्णांकer to poपूर्णांकer to queue entry काष्ठाure
 *
 * This routine perक्रमms the following tasks:
 *	- वापसs the current request_in poपूर्णांकer (अगर queue not full)
 *	- advances the request_in poपूर्णांकer
 *	- checks क्रम queue full
 **/
अटल पूर्णांक qla4xxx_get_req_pkt(काष्ठा scsi_qla_host *ha,
			       काष्ठा queue_entry **queue_entry)
अणु
	uपूर्णांक16_t req_cnt = 1;

	अगर (qla4xxx_space_in_req_ring(ha, req_cnt)) अणु
		*queue_entry = ha->request_ptr;
		स_रखो(*queue_entry, 0, माप(**queue_entry));

		qla4xxx_advance_req_ring_ptr(ha);
		ha->req_q_count -= req_cnt;
		वापस QLA_SUCCESS;
	पूर्ण

	वापस QLA_ERROR;
पूर्ण

/**
 * qla4xxx_send_marker_iocb - issues marker iocb to HBA
 * @ha: Poपूर्णांकer to host adapter काष्ठाure.
 * @ddb_entry: Poपूर्णांकer to device database entry
 * @lun: SCSI LUN
 * @mrkr_mod: marker identअगरier
 *
 * This routine issues a marker IOCB.
 **/
पूर्णांक qla4xxx_send_marker_iocb(काष्ठा scsi_qla_host *ha,
	काष्ठा ddb_entry *ddb_entry, uपूर्णांक64_t lun, uपूर्णांक16_t mrkr_mod)
अणु
	काष्ठा qla4_marker_entry *marker_entry;
	अचिन्हित दीर्घ flags = 0;
	uपूर्णांक8_t status = QLA_SUCCESS;

	/* Acquire hardware specअगरic lock */
	spin_lock_irqsave(&ha->hardware_lock, flags);

	/* Get poपूर्णांकer to the queue entry क्रम the marker */
	अगर (qla4xxx_get_req_pkt(ha, (काष्ठा queue_entry **) &marker_entry) !=
	    QLA_SUCCESS) अणु
		status = QLA_ERROR;
		जाओ निकास_send_marker;
	पूर्ण

	/* Put the marker in the request queue */
	marker_entry->hdr.entryType = ET_MARKER;
	marker_entry->hdr.entryCount = 1;
	marker_entry->target = cpu_to_le16(ddb_entry->fw_ddb_index);
	marker_entry->modअगरier = cpu_to_le16(mrkr_mod);
	पूर्णांक_to_scsilun(lun, &marker_entry->lun);
	wmb();

	/* Tell ISP it's got a new I/O request */
	ha->isp_ops->queue_iocb(ha);

निकास_send_marker:
	spin_unlock_irqrestore(&ha->hardware_lock, flags);
	वापस status;
पूर्ण

अटल काष्ठा continuation_t1_entry *
qla4xxx_alloc_cont_entry(काष्ठा scsi_qla_host *ha)
अणु
	काष्ठा continuation_t1_entry *cont_entry;

	cont_entry = (काष्ठा continuation_t1_entry *)ha->request_ptr;

	qla4xxx_advance_req_ring_ptr(ha);

	/* Load packet शेषs */
	cont_entry->hdr.entryType = ET_CONTINUE;
	cont_entry->hdr.entryCount = 1;
	cont_entry->hdr.प्रणालीDefined = (uपूर्णांक8_t) cpu_to_le16(ha->request_in);

	वापस cont_entry;
पूर्ण

अटल uपूर्णांक16_t qla4xxx_calc_request_entries(uपूर्णांक16_t dsds)
अणु
	uपूर्णांक16_t iocbs;

	iocbs = 1;
	अगर (dsds > COMMAND_SEG) अणु
		iocbs += (dsds - COMMAND_SEG) / CONTINUE_SEG;
		अगर ((dsds - COMMAND_SEG) % CONTINUE_SEG)
			iocbs++;
	पूर्ण
	वापस iocbs;
पूर्ण

अटल व्योम qla4xxx_build_scsi_iocbs(काष्ठा srb *srb,
				     काष्ठा command_t3_entry *cmd_entry,
				     uपूर्णांक16_t tot_dsds)
अणु
	काष्ठा scsi_qla_host *ha;
	uपूर्णांक16_t avail_dsds;
	काष्ठा data_seg_a64 *cur_dsd;
	काष्ठा scsi_cmnd *cmd;
	काष्ठा scatterlist *sg;
	पूर्णांक i;

	cmd = srb->cmd;
	ha = srb->ha;

	अगर (!scsi_bufflen(cmd) || cmd->sc_data_direction == DMA_NONE) अणु
		/* No data being transferred */
		cmd_entry->ttlByteCnt = __स्थिरant_cpu_to_le32(0);
		वापस;
	पूर्ण

	avail_dsds = COMMAND_SEG;
	cur_dsd = (काष्ठा data_seg_a64 *) & (cmd_entry->dataseg[0]);

	scsi_क्रम_each_sg(cmd, sg, tot_dsds, i) अणु
		dma_addr_t sle_dma;

		/* Allocate additional continuation packets? */
		अगर (avail_dsds == 0) अणु
			काष्ठा continuation_t1_entry *cont_entry;

			cont_entry = qla4xxx_alloc_cont_entry(ha);
			cur_dsd =
				(काष्ठा data_seg_a64 *)
				&cont_entry->dataseg[0];
			avail_dsds = CONTINUE_SEG;
		पूर्ण

		sle_dma = sg_dma_address(sg);
		cur_dsd->base.addrLow = cpu_to_le32(LSDW(sle_dma));
		cur_dsd->base.addrHigh = cpu_to_le32(MSDW(sle_dma));
		cur_dsd->count = cpu_to_le32(sg_dma_len(sg));
		avail_dsds--;

		cur_dsd++;
	पूर्ण
पूर्ण

व्योम qla4_83xx_queue_iocb(काष्ठा scsi_qla_host *ha)
अणु
	ग_लिखोl(ha->request_in, &ha->qla4_83xx_reg->req_q_in);
	पढ़ोl(&ha->qla4_83xx_reg->req_q_in);
पूर्ण

व्योम qla4_83xx_complete_iocb(काष्ठा scsi_qla_host *ha)
अणु
	ग_लिखोl(ha->response_out, &ha->qla4_83xx_reg->rsp_q_out);
	पढ़ोl(&ha->qla4_83xx_reg->rsp_q_out);
पूर्ण

/**
 * qla4_82xx_queue_iocb - Tell ISP it's got new request(s)
 * @ha: poपूर्णांकer to host adapter काष्ठाure.
 *
 * This routine notअगरies the ISP that one or more new request
 * queue entries have been placed on the request queue.
 **/
व्योम qla4_82xx_queue_iocb(काष्ठा scsi_qla_host *ha)
अणु
	uपूर्णांक32_t dbval = 0;

	dbval = 0x14 | (ha->func_num << 5);
	dbval = dbval | (0 << 8) | (ha->request_in << 16);

	qla4_82xx_wr_32(ha, ha->nx_db_wr_ptr, ha->request_in);
पूर्ण

/**
 * qla4_82xx_complete_iocb - Tell ISP we're करोne with response(s)
 * @ha: poपूर्णांकer to host adapter काष्ठाure.
 *
 * This routine notअगरies the ISP that one or more response/completion
 * queue entries have been processed by the driver.
 * This also clears the पूर्णांकerrupt.
 **/
व्योम qla4_82xx_complete_iocb(काष्ठा scsi_qla_host *ha)
अणु
	ग_लिखोl(ha->response_out, &ha->qla4_82xx_reg->rsp_q_out);
	पढ़ोl(&ha->qla4_82xx_reg->rsp_q_out);
पूर्ण

/**
 * qla4xxx_queue_iocb - Tell ISP it's got new request(s)
 * @ha: poपूर्णांकer to host adapter काष्ठाure.
 *
 * This routine is notअगरies the ISP that one or more new request
 * queue entries have been placed on the request queue.
 **/
व्योम qla4xxx_queue_iocb(काष्ठा scsi_qla_host *ha)
अणु
	ग_लिखोl(ha->request_in, &ha->reg->req_q_in);
	पढ़ोl(&ha->reg->req_q_in);
पूर्ण

/**
 * qla4xxx_complete_iocb - Tell ISP we're करोne with response(s)
 * @ha: poपूर्णांकer to host adapter काष्ठाure.
 *
 * This routine is notअगरies the ISP that one or more response/completion
 * queue entries have been processed by the driver.
 * This also clears the पूर्णांकerrupt.
 **/
व्योम qla4xxx_complete_iocb(काष्ठा scsi_qla_host *ha)
अणु
	ग_लिखोl(ha->response_out, &ha->reg->rsp_q_out);
	पढ़ोl(&ha->reg->rsp_q_out);
पूर्ण

/**
 * qla4xxx_send_command_to_isp - issues command to HBA
 * @ha: poपूर्णांकer to host adapter काष्ठाure.
 * @srb: poपूर्णांकer to SCSI Request Block to be sent to ISP
 *
 * This routine is called by qla4xxx_queuecommand to build an ISP
 * command and pass it to the ISP क्रम execution.
 **/
पूर्णांक qla4xxx_send_command_to_isp(काष्ठा scsi_qla_host *ha, काष्ठा srb * srb)
अणु
	काष्ठा scsi_cmnd *cmd = srb->cmd;
	काष्ठा ddb_entry *ddb_entry;
	काष्ठा command_t3_entry *cmd_entry;
	पूर्णांक nseg;
	uपूर्णांक16_t tot_dsds;
	uपूर्णांक16_t req_cnt;
	अचिन्हित दीर्घ flags;
	uपूर्णांक32_t index;

	/* Get real lun and adapter */
	ddb_entry = srb->ddb;

	tot_dsds = 0;

	/* Acquire hardware specअगरic lock */
	spin_lock_irqsave(&ha->hardware_lock, flags);

	index = (uपूर्णांक32_t)cmd->request->tag;

	/*
	 * Check to see अगर adapter is online beक्रमe placing request on
	 * request queue.  If a reset occurs and a request is in the queue,
	 * the firmware will still attempt to process the request, retrieving
	 * garbage क्रम poपूर्णांकers.
	 */
	अगर (!test_bit(AF_ONLINE, &ha->flags)) अणु
		DEBUG2(prपूर्णांकk("scsi%ld: %s: Adapter OFFLINE! "
			      "Do not issue command.\n",
			      ha->host_no, __func__));
		जाओ queuing_error;
	पूर्ण

	/* Calculate the number of request entries needed. */
	nseg = scsi_dma_map(cmd);
	अगर (nseg < 0)
		जाओ queuing_error;
	tot_dsds = nseg;

	req_cnt = qla4xxx_calc_request_entries(tot_dsds);
	अगर (!qla4xxx_space_in_req_ring(ha, req_cnt))
		जाओ queuing_error;

	/* total iocbs active */
	अगर ((ha->iocb_cnt + req_cnt) >= ha->iocb_hiwat)
		जाओ queuing_error;

	/* Build command packet */
	cmd_entry = (काष्ठा command_t3_entry *) ha->request_ptr;
	स_रखो(cmd_entry, 0, माप(काष्ठा command_t3_entry));
	cmd_entry->hdr.entryType = ET_COMMAND;
	cmd_entry->handle = cpu_to_le32(index);
	cmd_entry->target = cpu_to_le16(ddb_entry->fw_ddb_index);

	पूर्णांक_to_scsilun(cmd->device->lun, &cmd_entry->lun);
	cmd_entry->ttlByteCnt = cpu_to_le32(scsi_bufflen(cmd));
	स_नकल(cmd_entry->cdb, cmd->cmnd, cmd->cmd_len);
	cmd_entry->dataSegCnt = cpu_to_le16(tot_dsds);
	cmd_entry->hdr.entryCount = req_cnt;

	/* Set data transfer direction control flags
	 * NOTE: Look at data_direction bits अगरf there is data to be
	 *	 transferred, as the data direction bit is someसमयd filled
	 *	 in when there is no data to be transferred */
	cmd_entry->control_flags = CF_NO_DATA;
	अगर (scsi_bufflen(cmd)) अणु
		अगर (cmd->sc_data_direction == DMA_TO_DEVICE)
			cmd_entry->control_flags = CF_WRITE;
		अन्यथा अगर (cmd->sc_data_direction == DMA_FROM_DEVICE)
			cmd_entry->control_flags = CF_READ;

		ha->bytes_xfered += scsi_bufflen(cmd);
		अगर (ha->bytes_xfered & ~0xFFFFF)अणु
			ha->total_mbytes_xferred += ha->bytes_xfered >> 20;
			ha->bytes_xfered &= 0xFFFFF;
		पूर्ण
	पूर्ण

	/* Set tagged queueing control flags */
	cmd_entry->control_flags |= CF_SIMPLE_TAG;

	qla4xxx_advance_req_ring_ptr(ha);
	qla4xxx_build_scsi_iocbs(srb, cmd_entry, tot_dsds);
	wmb();

	srb->cmd->host_scribble = (अचिन्हित अक्षर *)(अचिन्हित दीर्घ)index;

	/* update counters */
	srb->state = SRB_ACTIVE_STATE;
	srb->flags |= SRB_DMA_VALID;

	/* Track IOCB used */
	ha->iocb_cnt += req_cnt;
	srb->iocb_cnt = req_cnt;
	ha->req_q_count -= req_cnt;

	ha->isp_ops->queue_iocb(ha);
	spin_unlock_irqrestore(&ha->hardware_lock, flags);

	वापस QLA_SUCCESS;

queuing_error:
	अगर (tot_dsds)
		scsi_dma_unmap(cmd);

	spin_unlock_irqrestore(&ha->hardware_lock, flags);

	वापस QLA_ERROR;
पूर्ण

पूर्णांक qla4xxx_send_passthru0(काष्ठा iscsi_task *task)
अणु
	काष्ठा passthru0 *passthru_iocb;
	काष्ठा iscsi_session *sess = task->conn->session;
	काष्ठा ddb_entry *ddb_entry = sess->dd_data;
	काष्ठा scsi_qla_host *ha = ddb_entry->ha;
	काष्ठा ql4_task_data *task_data = task->dd_data;
	uपूर्णांक16_t ctrl_flags = 0;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = QLA_ERROR;

	spin_lock_irqsave(&ha->hardware_lock, flags);
	task_data->iocb_req_cnt = 1;
	/* Put the IOCB on the request queue */
	अगर (!qla4xxx_space_in_req_ring(ha, task_data->iocb_req_cnt))
		जाओ queuing_error;

	passthru_iocb = (काष्ठा passthru0 *) ha->request_ptr;

	स_रखो(passthru_iocb, 0, माप(काष्ठा passthru0));
	passthru_iocb->hdr.entryType = ET_PASSTHRU0;
	passthru_iocb->hdr.प्रणालीDefined = SD_ISCSI_PDU;
	passthru_iocb->hdr.entryCount = task_data->iocb_req_cnt;
	passthru_iocb->handle = task->itt;
	passthru_iocb->target = cpu_to_le16(ddb_entry->fw_ddb_index);
	passthru_iocb->समयout = cpu_to_le16(PT_DEFAULT_TIMEOUT);

	/* Setup the out & in DSDs */
	अगर (task_data->req_len) अणु
		स_नकल((uपूर्णांक8_t *)task_data->req_buffer +
		       माप(काष्ठा iscsi_hdr), task->data, task->data_count);
		ctrl_flags |= PT_FLAG_SEND_BUFFER;
		passthru_iocb->out_dsd.base.addrLow =
					cpu_to_le32(LSDW(task_data->req_dma));
		passthru_iocb->out_dsd.base.addrHigh =
					cpu_to_le32(MSDW(task_data->req_dma));
		passthru_iocb->out_dsd.count =
					cpu_to_le32(task->data_count +
						    माप(काष्ठा iscsi_hdr));
	पूर्ण
	अगर (task_data->resp_len) अणु
		passthru_iocb->in_dsd.base.addrLow =
					cpu_to_le32(LSDW(task_data->resp_dma));
		passthru_iocb->in_dsd.base.addrHigh =
					cpu_to_le32(MSDW(task_data->resp_dma));
		passthru_iocb->in_dsd.count =
			cpu_to_le32(task_data->resp_len);
	पूर्ण

	ctrl_flags |= (PT_FLAG_ISCSI_PDU | PT_FLAG_WAIT_4_RESPONSE);
	passthru_iocb->control_flags = cpu_to_le16(ctrl_flags);

	/* Update the request poपूर्णांकer */
	qla4xxx_advance_req_ring_ptr(ha);
	wmb();

	/* Track IOCB used */
	ha->iocb_cnt += task_data->iocb_req_cnt;
	ha->req_q_count -= task_data->iocb_req_cnt;
	ha->isp_ops->queue_iocb(ha);
	ret = QLA_SUCCESS;

queuing_error:
	spin_unlock_irqrestore(&ha->hardware_lock, flags);
	वापस ret;
पूर्ण

अटल काष्ठा mrb *qla4xxx_get_new_mrb(काष्ठा scsi_qla_host *ha)
अणु
	काष्ठा mrb *mrb;

	mrb = kzalloc(माप(*mrb), GFP_KERNEL);
	अगर (!mrb)
		वापस mrb;

	mrb->ha = ha;
	वापस mrb;
पूर्ण

अटल पूर्णांक qla4xxx_send_mbox_iocb(काष्ठा scsi_qla_host *ha, काष्ठा mrb *mrb,
				  uपूर्णांक32_t *in_mbox)
अणु
	पूर्णांक rval = QLA_SUCCESS;
	uपूर्णांक32_t i;
	अचिन्हित दीर्घ flags;
	uपूर्णांक32_t index = 0;

	/* Acquire hardware specअगरic lock */
	spin_lock_irqsave(&ha->hardware_lock, flags);

	/* Get poपूर्णांकer to the queue entry क्रम the marker */
	rval = qla4xxx_get_req_pkt(ha, (काष्ठा queue_entry **) &(mrb->mbox));
	अगर (rval != QLA_SUCCESS)
		जाओ निकास_mbox_iocb;

	index = ha->mrb_index;
	/* get valid mrb index*/
	क्रम (i = 0; i < MAX_MRB; i++) अणु
		index++;
		अगर (index == MAX_MRB)
			index = 1;
		अगर (ha->active_mrb_array[index] == शून्य) अणु
			ha->mrb_index = index;
			अवरोध;
		पूर्ण
	पूर्ण

	mrb->iocb_cnt = 1;
	ha->active_mrb_array[index] = mrb;
	mrb->mbox->handle = index;
	mrb->mbox->hdr.entryType = ET_MBOX_CMD;
	mrb->mbox->hdr.entryCount = mrb->iocb_cnt;
	स_नकल(mrb->mbox->in_mbox, in_mbox, 32);
	mrb->mbox_cmd = in_mbox[0];
	wmb();

	ha->iocb_cnt += mrb->iocb_cnt;
	ha->isp_ops->queue_iocb(ha);
निकास_mbox_iocb:
	spin_unlock_irqrestore(&ha->hardware_lock, flags);
	वापस rval;
पूर्ण

पूर्णांक qla4xxx_ping_iocb(काष्ठा scsi_qla_host *ha, uपूर्णांक32_t options,
		      uपूर्णांक32_t payload_size, uपूर्णांक32_t pid, uपूर्णांक8_t *ipaddr)
अणु
	uपूर्णांक32_t in_mbox[8];
	काष्ठा mrb *mrb = शून्य;
	पूर्णांक rval = QLA_SUCCESS;

	स_रखो(in_mbox, 0, माप(in_mbox));

	mrb = qla4xxx_get_new_mrb(ha);
	अगर (!mrb) अणु
		DEBUG2(ql4_prपूर्णांकk(KERN_WARNING, ha, "%s: fail to get new mrb\n",
				  __func__));
		rval = QLA_ERROR;
		जाओ निकास_ping;
	पूर्ण

	in_mbox[0] = MBOX_CMD_PING;
	in_mbox[1] = options;
	स_नकल(&in_mbox[2], &ipaddr[0], 4);
	स_नकल(&in_mbox[3], &ipaddr[4], 4);
	स_नकल(&in_mbox[4], &ipaddr[8], 4);
	स_नकल(&in_mbox[5], &ipaddr[12], 4);
	in_mbox[6] = payload_size;

	mrb->pid = pid;
	rval = qla4xxx_send_mbox_iocb(ha, mrb, in_mbox);

	अगर (rval != QLA_SUCCESS)
		जाओ निकास_ping;

	वापस rval;
निकास_ping:
	kमुक्त(mrb);
	वापस rval;
पूर्ण
