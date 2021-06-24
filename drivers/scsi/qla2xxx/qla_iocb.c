<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * QLogic Fibre Channel HBA Driver
 * Copyright (c)  2003-2014 QLogic Corporation
 */
#समावेश "qla_def.h"
#समावेश "qla_target.h"

#समावेश <linux/blkdev.h>
#समावेश <linux/delay.h>

#समावेश <scsi/scsi_tcq.h>

/**
 * qla2x00_get_cmd_direction() - Determine control_flag data direction.
 * @sp: SCSI command
 *
 * Returns the proper CF_* direction based on CDB.
 */
अटल अंतरभूत uपूर्णांक16_t
qla2x00_get_cmd_direction(srb_t *sp)
अणु
	uपूर्णांक16_t cflags;
	काष्ठा scsi_cmnd *cmd = GET_CMD_SP(sp);
	काष्ठा scsi_qla_host *vha = sp->vha;

	cflags = 0;

	/* Set transfer direction */
	अगर (cmd->sc_data_direction == DMA_TO_DEVICE) अणु
		cflags = CF_WRITE;
		vha->qla_stats.output_bytes += scsi_bufflen(cmd);
		vha->qla_stats.output_requests++;
	पूर्ण अन्यथा अगर (cmd->sc_data_direction == DMA_FROM_DEVICE) अणु
		cflags = CF_READ;
		vha->qla_stats.input_bytes += scsi_bufflen(cmd);
		vha->qla_stats.input_requests++;
	पूर्ण
	वापस (cflags);
पूर्ण

/**
 * qla2x00_calc_iocbs_32() - Determine number of Command Type 2 and
 * Continuation Type 0 IOCBs to allocate.
 *
 * @dsds: number of data segment descriptors needed
 *
 * Returns the number of IOCB entries needed to store @dsds.
 */
uपूर्णांक16_t
qla2x00_calc_iocbs_32(uपूर्णांक16_t dsds)
अणु
	uपूर्णांक16_t iocbs;

	iocbs = 1;
	अगर (dsds > 3) अणु
		iocbs += (dsds - 3) / 7;
		अगर ((dsds - 3) % 7)
			iocbs++;
	पूर्ण
	वापस (iocbs);
पूर्ण

/**
 * qla2x00_calc_iocbs_64() - Determine number of Command Type 3 and
 * Continuation Type 1 IOCBs to allocate.
 *
 * @dsds: number of data segment descriptors needed
 *
 * Returns the number of IOCB entries needed to store @dsds.
 */
uपूर्णांक16_t
qla2x00_calc_iocbs_64(uपूर्णांक16_t dsds)
अणु
	uपूर्णांक16_t iocbs;

	iocbs = 1;
	अगर (dsds > 2) अणु
		iocbs += (dsds - 2) / 5;
		अगर ((dsds - 2) % 5)
			iocbs++;
	पूर्ण
	वापस (iocbs);
पूर्ण

/**
 * qla2x00_prep_cont_type0_iocb() - Initialize a Continuation Type 0 IOCB.
 * @vha: HA context
 *
 * Returns a poपूर्णांकer to the Continuation Type 0 IOCB packet.
 */
अटल अंतरभूत cont_entry_t *
qla2x00_prep_cont_type0_iocb(काष्ठा scsi_qla_host *vha)
अणु
	cont_entry_t *cont_pkt;
	काष्ठा req_que *req = vha->req;
	/* Adjust ring index. */
	req->ring_index++;
	अगर (req->ring_index == req->length) अणु
		req->ring_index = 0;
		req->ring_ptr = req->ring;
	पूर्ण अन्यथा अणु
		req->ring_ptr++;
	पूर्ण

	cont_pkt = (cont_entry_t *)req->ring_ptr;

	/* Load packet शेषs. */
	put_unaligned_le32(CONTINUE_TYPE, &cont_pkt->entry_type);

	वापस (cont_pkt);
पूर्ण

/**
 * qla2x00_prep_cont_type1_iocb() - Initialize a Continuation Type 1 IOCB.
 * @vha: HA context
 * @req: request queue
 *
 * Returns a poपूर्णांकer to the continuation type 1 IOCB packet.
 */
अटल अंतरभूत cont_a64_entry_t *
qla2x00_prep_cont_type1_iocb(scsi_qla_host_t *vha, काष्ठा req_que *req)
अणु
	cont_a64_entry_t *cont_pkt;

	/* Adjust ring index. */
	req->ring_index++;
	अगर (req->ring_index == req->length) अणु
		req->ring_index = 0;
		req->ring_ptr = req->ring;
	पूर्ण अन्यथा अणु
		req->ring_ptr++;
	पूर्ण

	cont_pkt = (cont_a64_entry_t *)req->ring_ptr;

	/* Load packet शेषs. */
	put_unaligned_le32(IS_QLAFX00(vha->hw) ? CONTINUE_A64_TYPE_FX00 :
			   CONTINUE_A64_TYPE, &cont_pkt->entry_type);

	वापस (cont_pkt);
पूर्ण

अंतरभूत पूर्णांक
qla24xx_configure_prot_mode(srb_t *sp, uपूर्णांक16_t *fw_prot_opts)
अणु
	काष्ठा scsi_cmnd *cmd = GET_CMD_SP(sp);
	uपूर्णांक8_t	guard = scsi_host_get_guard(cmd->device->host);

	/* We always use DIFF Bundling क्रम best perक्रमmance */
	*fw_prot_opts = 0;

	/* Translate SCSI opcode to a protection opcode */
	चयन (scsi_get_prot_op(cmd)) अणु
	हाल SCSI_PROT_READ_STRIP:
		*fw_prot_opts |= PO_MODE_DIF_REMOVE;
		अवरोध;
	हाल SCSI_PROT_WRITE_INSERT:
		*fw_prot_opts |= PO_MODE_DIF_INSERT;
		अवरोध;
	हाल SCSI_PROT_READ_INSERT:
		*fw_prot_opts |= PO_MODE_DIF_INSERT;
		अवरोध;
	हाल SCSI_PROT_WRITE_STRIP:
		*fw_prot_opts |= PO_MODE_DIF_REMOVE;
		अवरोध;
	हाल SCSI_PROT_READ_PASS:
	हाल SCSI_PROT_WRITE_PASS:
		अगर (guard & SHOST_DIX_GUARD_IP)
			*fw_prot_opts |= PO_MODE_DIF_TCP_CKSUM;
		अन्यथा
			*fw_prot_opts |= PO_MODE_DIF_PASS;
		अवरोध;
	शेष:	/* Normal Request */
		*fw_prot_opts |= PO_MODE_DIF_PASS;
		अवरोध;
	पूर्ण

	वापस scsi_prot_sg_count(cmd);
पूर्ण

/*
 * qla2x00_build_scsi_iocbs_32() - Build IOCB command utilizing 32bit
 * capable IOCB types.
 *
 * @sp: SRB command to process
 * @cmd_pkt: Command type 2 IOCB
 * @tot_dsds: Total number of segments to transfer
 */
व्योम qla2x00_build_scsi_iocbs_32(srb_t *sp, cmd_entry_t *cmd_pkt,
    uपूर्णांक16_t tot_dsds)
अणु
	uपूर्णांक16_t	avail_dsds;
	काष्ठा dsd32	*cur_dsd;
	scsi_qla_host_t	*vha;
	काष्ठा scsi_cmnd *cmd;
	काष्ठा scatterlist *sg;
	पूर्णांक i;

	cmd = GET_CMD_SP(sp);

	/* Update entry type to indicate Command Type 2 IOCB */
	put_unaligned_le32(COMMAND_TYPE, &cmd_pkt->entry_type);

	/* No data transfer */
	अगर (!scsi_bufflen(cmd) || cmd->sc_data_direction == DMA_NONE) अणु
		cmd_pkt->byte_count = cpu_to_le32(0);
		वापस;
	पूर्ण

	vha = sp->vha;
	cmd_pkt->control_flags |= cpu_to_le16(qla2x00_get_cmd_direction(sp));

	/* Three DSDs are available in the Command Type 2 IOCB */
	avail_dsds = ARRAY_SIZE(cmd_pkt->dsd32);
	cur_dsd = cmd_pkt->dsd32;

	/* Load data segments */
	scsi_क्रम_each_sg(cmd, sg, tot_dsds, i) अणु
		cont_entry_t *cont_pkt;

		/* Allocate additional continuation packets? */
		अगर (avail_dsds == 0) अणु
			/*
			 * Seven DSDs are available in the Continuation
			 * Type 0 IOCB.
			 */
			cont_pkt = qla2x00_prep_cont_type0_iocb(vha);
			cur_dsd = cont_pkt->dsd;
			avail_dsds = ARRAY_SIZE(cont_pkt->dsd);
		पूर्ण

		append_dsd32(&cur_dsd, sg);
		avail_dsds--;
	पूर्ण
पूर्ण

/**
 * qla2x00_build_scsi_iocbs_64() - Build IOCB command utilizing 64bit
 * capable IOCB types.
 *
 * @sp: SRB command to process
 * @cmd_pkt: Command type 3 IOCB
 * @tot_dsds: Total number of segments to transfer
 */
व्योम qla2x00_build_scsi_iocbs_64(srb_t *sp, cmd_entry_t *cmd_pkt,
    uपूर्णांक16_t tot_dsds)
अणु
	uपूर्णांक16_t	avail_dsds;
	काष्ठा dsd64	*cur_dsd;
	scsi_qla_host_t	*vha;
	काष्ठा scsi_cmnd *cmd;
	काष्ठा scatterlist *sg;
	पूर्णांक i;

	cmd = GET_CMD_SP(sp);

	/* Update entry type to indicate Command Type 3 IOCB */
	put_unaligned_le32(COMMAND_A64_TYPE, &cmd_pkt->entry_type);

	/* No data transfer */
	अगर (!scsi_bufflen(cmd) || cmd->sc_data_direction == DMA_NONE) अणु
		cmd_pkt->byte_count = cpu_to_le32(0);
		वापस;
	पूर्ण

	vha = sp->vha;
	cmd_pkt->control_flags |= cpu_to_le16(qla2x00_get_cmd_direction(sp));

	/* Two DSDs are available in the Command Type 3 IOCB */
	avail_dsds = ARRAY_SIZE(cmd_pkt->dsd64);
	cur_dsd = cmd_pkt->dsd64;

	/* Load data segments */
	scsi_क्रम_each_sg(cmd, sg, tot_dsds, i) अणु
		cont_a64_entry_t *cont_pkt;

		/* Allocate additional continuation packets? */
		अगर (avail_dsds == 0) अणु
			/*
			 * Five DSDs are available in the Continuation
			 * Type 1 IOCB.
			 */
			cont_pkt = qla2x00_prep_cont_type1_iocb(vha, vha->req);
			cur_dsd = cont_pkt->dsd;
			avail_dsds = ARRAY_SIZE(cont_pkt->dsd);
		पूर्ण

		append_dsd64(&cur_dsd, sg);
		avail_dsds--;
	पूर्ण
पूर्ण

/*
 * Find the first handle that is not in use, starting from
 * req->current_outstanding_cmd + 1. The caller must hold the lock that is
 * associated with @req.
 */
uपूर्णांक32_t qla2xxx_get_next_handle(काष्ठा req_que *req)
अणु
	uपूर्णांक32_t index, handle = req->current_outstanding_cmd;

	क्रम (index = 1; index < req->num_outstanding_cmds; index++) अणु
		handle++;
		अगर (handle == req->num_outstanding_cmds)
			handle = 1;
		अगर (!req->outstanding_cmds[handle])
			वापस handle;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * qla2x00_start_scsi() - Send a SCSI command to the ISP
 * @sp: command to send to the ISP
 *
 * Returns non-zero अगर a failure occurred, अन्यथा zero.
 */
पूर्णांक
qla2x00_start_scsi(srb_t *sp)
अणु
	पूर्णांक		nseg;
	अचिन्हित दीर्घ   flags;
	scsi_qla_host_t	*vha;
	काष्ठा scsi_cmnd *cmd;
	uपूर्णांक32_t	*clr_ptr;
	uपूर्णांक32_t	handle;
	cmd_entry_t	*cmd_pkt;
	uपूर्णांक16_t	cnt;
	uपूर्णांक16_t	req_cnt;
	uपूर्णांक16_t	tot_dsds;
	काष्ठा device_reg_2xxx __iomem *reg;
	काष्ठा qla_hw_data *ha;
	काष्ठा req_que *req;
	काष्ठा rsp_que *rsp;

	/* Setup device poपूर्णांकers. */
	vha = sp->vha;
	ha = vha->hw;
	reg = &ha->iobase->isp;
	cmd = GET_CMD_SP(sp);
	req = ha->req_q_map[0];
	rsp = ha->rsp_q_map[0];
	/* So we know we haven't pci_map'ed anything yet */
	tot_dsds = 0;

	/* Send marker अगर required */
	अगर (vha->marker_needed != 0) अणु
		अगर (qla2x00_marker(vha, ha->base_qpair, 0, 0, MK_SYNC_ALL) !=
		    QLA_SUCCESS) अणु
			वापस (QLA_FUNCTION_FAILED);
		पूर्ण
		vha->marker_needed = 0;
	पूर्ण

	/* Acquire ring specअगरic lock */
	spin_lock_irqsave(&ha->hardware_lock, flags);

	handle = qla2xxx_get_next_handle(req);
	अगर (handle == 0)
		जाओ queuing_error;

	/* Map the sg table so we have an accurate count of sg entries needed */
	अगर (scsi_sg_count(cmd)) अणु
		nseg = dma_map_sg(&ha->pdev->dev, scsi_sglist(cmd),
		    scsi_sg_count(cmd), cmd->sc_data_direction);
		अगर (unlikely(!nseg))
			जाओ queuing_error;
	पूर्ण अन्यथा
		nseg = 0;

	tot_dsds = nseg;

	/* Calculate the number of request entries needed. */
	req_cnt = ha->isp_ops->calc_req_entries(tot_dsds);
	अगर (req->cnt < (req_cnt + 2)) अणु
		cnt = rd_reg_word_relaxed(ISP_REQ_Q_OUT(ha, reg));
		अगर (req->ring_index < cnt)
			req->cnt = cnt - req->ring_index;
		अन्यथा
			req->cnt = req->length -
			    (req->ring_index - cnt);
		/* If still no head room then bail out */
		अगर (req->cnt < (req_cnt + 2))
			जाओ queuing_error;
	पूर्ण

	/* Build command packet */
	req->current_outstanding_cmd = handle;
	req->outstanding_cmds[handle] = sp;
	sp->handle = handle;
	cmd->host_scribble = (अचिन्हित अक्षर *)(अचिन्हित दीर्घ)handle;
	req->cnt -= req_cnt;

	cmd_pkt = (cmd_entry_t *)req->ring_ptr;
	cmd_pkt->handle = handle;
	/* Zero out reमुख्यing portion of packet. */
	clr_ptr = (uपूर्णांक32_t *)cmd_pkt + 2;
	स_रखो(clr_ptr, 0, REQUEST_ENTRY_SIZE - 8);
	cmd_pkt->dseg_count = cpu_to_le16(tot_dsds);

	/* Set target ID and LUN number*/
	SET_TARGET_ID(ha, cmd_pkt->target, sp->fcport->loop_id);
	cmd_pkt->lun = cpu_to_le16(cmd->device->lun);
	cmd_pkt->control_flags = cpu_to_le16(CF_SIMPLE_TAG);

	/* Load SCSI command packet. */
	स_नकल(cmd_pkt->scsi_cdb, cmd->cmnd, cmd->cmd_len);
	cmd_pkt->byte_count = cpu_to_le32((uपूर्णांक32_t)scsi_bufflen(cmd));

	/* Build IOCB segments */
	ha->isp_ops->build_iocbs(sp, cmd_pkt, tot_dsds);

	/* Set total data segment count. */
	cmd_pkt->entry_count = (uपूर्णांक8_t)req_cnt;
	wmb();

	/* Adjust ring index. */
	req->ring_index++;
	अगर (req->ring_index == req->length) अणु
		req->ring_index = 0;
		req->ring_ptr = req->ring;
	पूर्ण अन्यथा
		req->ring_ptr++;

	sp->flags |= SRB_DMA_VALID;

	/* Set chip new ring index. */
	wrt_reg_word(ISP_REQ_Q_IN(ha, reg), req->ring_index);
	rd_reg_word_relaxed(ISP_REQ_Q_IN(ha, reg));	/* PCI Posting. */

	/* Manage unprocessed RIO/ZIO commands in response queue. */
	अगर (vha->flags.process_response_queue &&
	    rsp->ring_ptr->signature != RESPONSE_PROCESSED)
		qla2x00_process_response_queue(rsp);

	spin_unlock_irqrestore(&ha->hardware_lock, flags);
	वापस (QLA_SUCCESS);

queuing_error:
	अगर (tot_dsds)
		scsi_dma_unmap(cmd);

	spin_unlock_irqrestore(&ha->hardware_lock, flags);

	वापस (QLA_FUNCTION_FAILED);
पूर्ण

/**
 * qla2x00_start_iocbs() - Execute the IOCB command
 * @vha: HA context
 * @req: request queue
 */
व्योम
qla2x00_start_iocbs(काष्ठा scsi_qla_host *vha, काष्ठा req_que *req)
अणु
	काष्ठा qla_hw_data *ha = vha->hw;
	device_reg_t *reg = ISP_QUE_REG(ha, req->id);

	अगर (IS_P3P_TYPE(ha)) अणु
		qla82xx_start_iocbs(vha);
	पूर्ण अन्यथा अणु
		/* Adjust ring index. */
		req->ring_index++;
		अगर (req->ring_index == req->length) अणु
			req->ring_index = 0;
			req->ring_ptr = req->ring;
		पूर्ण अन्यथा
			req->ring_ptr++;

		/* Set chip new ring index. */
		अगर (ha->mqenable || IS_QLA27XX(ha) || IS_QLA28XX(ha)) अणु
			wrt_reg_dword(req->req_q_in, req->ring_index);
		पूर्ण अन्यथा अगर (IS_QLA83XX(ha)) अणु
			wrt_reg_dword(req->req_q_in, req->ring_index);
			rd_reg_dword_relaxed(&ha->iobase->isp24.hccr);
		पूर्ण अन्यथा अगर (IS_QLAFX00(ha)) अणु
			wrt_reg_dword(&reg->ispfx00.req_q_in, req->ring_index);
			rd_reg_dword_relaxed(&reg->ispfx00.req_q_in);
			QLAFX00_SET_HST_INTR(ha, ha->rqstq_पूर्णांकr_code);
		पूर्ण अन्यथा अगर (IS_FWI2_CAPABLE(ha)) अणु
			wrt_reg_dword(&reg->isp24.req_q_in, req->ring_index);
			rd_reg_dword_relaxed(&reg->isp24.req_q_in);
		पूर्ण अन्यथा अणु
			wrt_reg_word(ISP_REQ_Q_IN(ha, &reg->isp),
				req->ring_index);
			rd_reg_word_relaxed(ISP_REQ_Q_IN(ha, &reg->isp));
		पूर्ण
	पूर्ण
पूर्ण

/**
 * __qla2x00_marker() - Send a marker IOCB to the firmware.
 * @vha: HA context
 * @qpair: queue pair poपूर्णांकer
 * @loop_id: loop ID
 * @lun: LUN
 * @type: marker modअगरier
 *
 * Can be called from both normal and पूर्णांकerrupt context.
 *
 * Returns non-zero अगर a failure occurred, अन्यथा zero.
 */
अटल पूर्णांक
__qla2x00_marker(काष्ठा scsi_qla_host *vha, काष्ठा qla_qpair *qpair,
    uपूर्णांक16_t loop_id, uपूर्णांक64_t lun, uपूर्णांक8_t type)
अणु
	mrk_entry_t *mrk;
	काष्ठा mrk_entry_24xx *mrk24 = शून्य;
	काष्ठा req_que *req = qpair->req;
	काष्ठा qla_hw_data *ha = vha->hw;
	scsi_qla_host_t *base_vha = pci_get_drvdata(ha->pdev);

	mrk = (mrk_entry_t *)__qla2x00_alloc_iocbs(qpair, शून्य);
	अगर (mrk == शून्य) अणु
		ql_log(ql_log_warn, base_vha, 0x3026,
		    "Failed to allocate Marker IOCB.\n");

		वापस (QLA_FUNCTION_FAILED);
	पूर्ण

	mrk->entry_type = MARKER_TYPE;
	mrk->modअगरier = type;
	अगर (type != MK_SYNC_ALL) अणु
		अगर (IS_FWI2_CAPABLE(ha)) अणु
			mrk24 = (काष्ठा mrk_entry_24xx *) mrk;
			mrk24->nport_handle = cpu_to_le16(loop_id);
			पूर्णांक_to_scsilun(lun, (काष्ठा scsi_lun *)&mrk24->lun);
			host_to_fcp_swap(mrk24->lun, माप(mrk24->lun));
			mrk24->vp_index = vha->vp_idx;
			mrk24->handle = make_handle(req->id, mrk24->handle);
		पूर्ण अन्यथा अणु
			SET_TARGET_ID(ha, mrk->target, loop_id);
			mrk->lun = cpu_to_le16((uपूर्णांक16_t)lun);
		पूर्ण
	पूर्ण
	wmb();

	qla2x00_start_iocbs(vha, req);

	वापस (QLA_SUCCESS);
पूर्ण

पूर्णांक
qla2x00_marker(काष्ठा scsi_qla_host *vha, काष्ठा qla_qpair *qpair,
    uपूर्णांक16_t loop_id, uपूर्णांक64_t lun, uपूर्णांक8_t type)
अणु
	पूर्णांक ret;
	अचिन्हित दीर्घ flags = 0;

	spin_lock_irqsave(qpair->qp_lock_ptr, flags);
	ret = __qla2x00_marker(vha, qpair, loop_id, lun, type);
	spin_unlock_irqrestore(qpair->qp_lock_ptr, flags);

	वापस (ret);
पूर्ण

/*
 * qla2x00_issue_marker
 *
 * Issue marker
 * Caller CAN have hardware lock held as specअगरied by ha_locked parameter.
 * Might release it, then reaquire.
 */
पूर्णांक qla2x00_issue_marker(scsi_qla_host_t *vha, पूर्णांक ha_locked)
अणु
	अगर (ha_locked) अणु
		अगर (__qla2x00_marker(vha, vha->hw->base_qpair, 0, 0,
					MK_SYNC_ALL) != QLA_SUCCESS)
			वापस QLA_FUNCTION_FAILED;
	पूर्ण अन्यथा अणु
		अगर (qla2x00_marker(vha, vha->hw->base_qpair, 0, 0,
					MK_SYNC_ALL) != QLA_SUCCESS)
			वापस QLA_FUNCTION_FAILED;
	पूर्ण
	vha->marker_needed = 0;

	वापस QLA_SUCCESS;
पूर्ण

अटल अंतरभूत पूर्णांक
qla24xx_build_scsi_type_6_iocbs(srb_t *sp, काष्ठा cmd_type_6 *cmd_pkt,
	uपूर्णांक16_t tot_dsds)
अणु
	काष्ठा dsd64 *cur_dsd = शून्य, *next_dsd;
	scsi_qla_host_t	*vha;
	काष्ठा qla_hw_data *ha;
	काष्ठा scsi_cmnd *cmd;
	काष्ठा	scatterlist *cur_seg;
	uपूर्णांक8_t avail_dsds;
	uपूर्णांक8_t first_iocb = 1;
	uपूर्णांक32_t dsd_list_len;
	काष्ठा dsd_dma *dsd_ptr;
	काष्ठा ct6_dsd *ctx;
	काष्ठा qla_qpair *qpair = sp->qpair;

	cmd = GET_CMD_SP(sp);

	/* Update entry type to indicate Command Type 3 IOCB */
	put_unaligned_le32(COMMAND_TYPE_6, &cmd_pkt->entry_type);

	/* No data transfer */
	अगर (!scsi_bufflen(cmd) || cmd->sc_data_direction == DMA_NONE) अणु
		cmd_pkt->byte_count = cpu_to_le32(0);
		वापस 0;
	पूर्ण

	vha = sp->vha;
	ha = vha->hw;

	/* Set transfer direction */
	अगर (cmd->sc_data_direction == DMA_TO_DEVICE) अणु
		cmd_pkt->control_flags = cpu_to_le16(CF_WRITE_DATA);
		qpair->counters.output_bytes += scsi_bufflen(cmd);
		qpair->counters.output_requests++;
	पूर्ण अन्यथा अगर (cmd->sc_data_direction == DMA_FROM_DEVICE) अणु
		cmd_pkt->control_flags = cpu_to_le16(CF_READ_DATA);
		qpair->counters.input_bytes += scsi_bufflen(cmd);
		qpair->counters.input_requests++;
	पूर्ण

	cur_seg = scsi_sglist(cmd);
	ctx = sp->u.scmd.ct6_ctx;

	जबतक (tot_dsds) अणु
		avail_dsds = (tot_dsds > QLA_DSDS_PER_IOCB) ?
		    QLA_DSDS_PER_IOCB : tot_dsds;
		tot_dsds -= avail_dsds;
		dsd_list_len = (avail_dsds + 1) * QLA_DSD_SIZE;

		dsd_ptr = list_first_entry(&ha->gbl_dsd_list,
		    काष्ठा dsd_dma, list);
		next_dsd = dsd_ptr->dsd_addr;
		list_del(&dsd_ptr->list);
		ha->gbl_dsd_avail--;
		list_add_tail(&dsd_ptr->list, &ctx->dsd_list);
		ctx->dsd_use_cnt++;
		ha->gbl_dsd_inuse++;

		अगर (first_iocb) अणु
			first_iocb = 0;
			put_unaligned_le64(dsd_ptr->dsd_list_dma,
					   &cmd_pkt->fcp_dsd.address);
			cmd_pkt->fcp_dsd.length = cpu_to_le32(dsd_list_len);
		पूर्ण अन्यथा अणु
			put_unaligned_le64(dsd_ptr->dsd_list_dma,
					   &cur_dsd->address);
			cur_dsd->length = cpu_to_le32(dsd_list_len);
			cur_dsd++;
		पूर्ण
		cur_dsd = next_dsd;
		जबतक (avail_dsds) अणु
			append_dsd64(&cur_dsd, cur_seg);
			cur_seg = sg_next(cur_seg);
			avail_dsds--;
		पूर्ण
	पूर्ण

	/* Null termination */
	cur_dsd->address = 0;
	cur_dsd->length = 0;
	cur_dsd++;
	cmd_pkt->control_flags |= cpu_to_le16(CF_DATA_SEG_DESCR_ENABLE);
	वापस 0;
पूर्ण

/*
 * qla24xx_calc_dsd_lists() - Determine number of DSD list required
 * क्रम Command Type 6.
 *
 * @dsds: number of data segment descriptors needed
 *
 * Returns the number of dsd list needed to store @dsds.
 */
अटल अंतरभूत uपूर्णांक16_t
qla24xx_calc_dsd_lists(uपूर्णांक16_t dsds)
अणु
	uपूर्णांक16_t dsd_lists = 0;

	dsd_lists = (dsds/QLA_DSDS_PER_IOCB);
	अगर (dsds % QLA_DSDS_PER_IOCB)
		dsd_lists++;
	वापस dsd_lists;
पूर्ण


/**
 * qla24xx_build_scsi_iocbs() - Build IOCB command utilizing Command Type 7
 * IOCB types.
 *
 * @sp: SRB command to process
 * @cmd_pkt: Command type 3 IOCB
 * @tot_dsds: Total number of segments to transfer
 * @req: poपूर्णांकer to request queue
 */
अंतरभूत व्योम
qla24xx_build_scsi_iocbs(srb_t *sp, काष्ठा cmd_type_7 *cmd_pkt,
	uपूर्णांक16_t tot_dsds, काष्ठा req_que *req)
अणु
	uपूर्णांक16_t	avail_dsds;
	काष्ठा dsd64	*cur_dsd;
	scsi_qla_host_t	*vha;
	काष्ठा scsi_cmnd *cmd;
	काष्ठा scatterlist *sg;
	पूर्णांक i;
	काष्ठा qla_qpair *qpair = sp->qpair;

	cmd = GET_CMD_SP(sp);

	/* Update entry type to indicate Command Type 3 IOCB */
	put_unaligned_le32(COMMAND_TYPE_7, &cmd_pkt->entry_type);

	/* No data transfer */
	अगर (!scsi_bufflen(cmd) || cmd->sc_data_direction == DMA_NONE) अणु
		cmd_pkt->byte_count = cpu_to_le32(0);
		वापस;
	पूर्ण

	vha = sp->vha;

	/* Set transfer direction */
	अगर (cmd->sc_data_direction == DMA_TO_DEVICE) अणु
		cmd_pkt->task_mgmt_flags = cpu_to_le16(TMF_WRITE_DATA);
		qpair->counters.output_bytes += scsi_bufflen(cmd);
		qpair->counters.output_requests++;
	पूर्ण अन्यथा अगर (cmd->sc_data_direction == DMA_FROM_DEVICE) अणु
		cmd_pkt->task_mgmt_flags = cpu_to_le16(TMF_READ_DATA);
		qpair->counters.input_bytes += scsi_bufflen(cmd);
		qpair->counters.input_requests++;
	पूर्ण

	/* One DSD is available in the Command Type 3 IOCB */
	avail_dsds = 1;
	cur_dsd = &cmd_pkt->dsd;

	/* Load data segments */

	scsi_क्रम_each_sg(cmd, sg, tot_dsds, i) अणु
		cont_a64_entry_t *cont_pkt;

		/* Allocate additional continuation packets? */
		अगर (avail_dsds == 0) अणु
			/*
			 * Five DSDs are available in the Continuation
			 * Type 1 IOCB.
			 */
			cont_pkt = qla2x00_prep_cont_type1_iocb(vha, req);
			cur_dsd = cont_pkt->dsd;
			avail_dsds = ARRAY_SIZE(cont_pkt->dsd);
		पूर्ण

		append_dsd64(&cur_dsd, sg);
		avail_dsds--;
	पूर्ण
पूर्ण

काष्ठा fw_dअगर_context अणु
	__le32	ref_tag;
	__le16	app_tag;
	uपूर्णांक8_t ref_tag_mask[4];	/* Validation/Replacement Mask*/
	uपूर्णांक8_t app_tag_mask[2];	/* Validation/Replacement Mask*/
पूर्ण;

/*
 * qla24xx_set_t10dअगर_tags_from_cmd - Extract Ref and App tags from SCSI command
 *
 */
अटल अंतरभूत व्योम
qla24xx_set_t10dअगर_tags(srb_t *sp, काष्ठा fw_dअगर_context *pkt,
    अचिन्हित पूर्णांक protcnt)
अणु
	काष्ठा scsi_cmnd *cmd = GET_CMD_SP(sp);

	चयन (scsi_get_prot_type(cmd)) अणु
	हाल SCSI_PROT_DIF_TYPE0:
		/*
		 * No check क्रम ql2xenablehba_err_chk, as it would be an
		 * I/O error अगर hba tag generation is not करोne.
		 */
		pkt->ref_tag = cpu_to_le32((uपूर्णांक32_t)
		    (0xffffffff & scsi_get_lba(cmd)));

		अगर (!qla2x00_hba_err_chk_enabled(sp))
			अवरोध;

		pkt->ref_tag_mask[0] = 0xff;
		pkt->ref_tag_mask[1] = 0xff;
		pkt->ref_tag_mask[2] = 0xff;
		pkt->ref_tag_mask[3] = 0xff;
		अवरोध;

	/*
	 * For TYPE 2 protection: 16 bit GUARD + 32 bit REF tag has to
	 * match LBA in CDB + N
	 */
	हाल SCSI_PROT_DIF_TYPE2:
		pkt->app_tag = cpu_to_le16(0);
		pkt->app_tag_mask[0] = 0x0;
		pkt->app_tag_mask[1] = 0x0;

		pkt->ref_tag = cpu_to_le32((uपूर्णांक32_t)
		    (0xffffffff & scsi_get_lba(cmd)));

		अगर (!qla2x00_hba_err_chk_enabled(sp))
			अवरोध;

		/* enable ALL bytes of the ref tag */
		pkt->ref_tag_mask[0] = 0xff;
		pkt->ref_tag_mask[1] = 0xff;
		pkt->ref_tag_mask[2] = 0xff;
		pkt->ref_tag_mask[3] = 0xff;
		अवरोध;

	/* For Type 3 protection: 16 bit GUARD only */
	हाल SCSI_PROT_DIF_TYPE3:
		pkt->ref_tag_mask[0] = pkt->ref_tag_mask[1] =
			pkt->ref_tag_mask[2] = pkt->ref_tag_mask[3] =
								0x00;
		अवरोध;

	/*
	 * For TYpe 1 protection: 16 bit GUARD tag, 32 bit REF tag, and
	 * 16 bit app tag.
	 */
	हाल SCSI_PROT_DIF_TYPE1:
		pkt->ref_tag = cpu_to_le32((uपूर्णांक32_t)
		    (0xffffffff & scsi_get_lba(cmd)));
		pkt->app_tag = cpu_to_le16(0);
		pkt->app_tag_mask[0] = 0x0;
		pkt->app_tag_mask[1] = 0x0;

		अगर (!qla2x00_hba_err_chk_enabled(sp))
			अवरोध;

		/* enable ALL bytes of the ref tag */
		pkt->ref_tag_mask[0] = 0xff;
		pkt->ref_tag_mask[1] = 0xff;
		pkt->ref_tag_mask[2] = 0xff;
		pkt->ref_tag_mask[3] = 0xff;
		अवरोध;
	पूर्ण
पूर्ण

पूर्णांक
qla24xx_get_one_block_sg(uपूर्णांक32_t blk_sz, काष्ठा qla2_sgx *sgx,
	uपूर्णांक32_t *partial)
अणु
	काष्ठा scatterlist *sg;
	uपूर्णांक32_t cumulative_partial, sg_len;
	dma_addr_t sg_dma_addr;

	अगर (sgx->num_bytes == sgx->tot_bytes)
		वापस 0;

	sg = sgx->cur_sg;
	cumulative_partial = sgx->tot_partial;

	sg_dma_addr = sg_dma_address(sg);
	sg_len = sg_dma_len(sg);

	sgx->dma_addr = sg_dma_addr + sgx->bytes_consumed;

	अगर ((cumulative_partial + (sg_len - sgx->bytes_consumed)) >= blk_sz) अणु
		sgx->dma_len = (blk_sz - cumulative_partial);
		sgx->tot_partial = 0;
		sgx->num_bytes += blk_sz;
		*partial = 0;
	पूर्ण अन्यथा अणु
		sgx->dma_len = sg_len - sgx->bytes_consumed;
		sgx->tot_partial += sgx->dma_len;
		*partial = 1;
	पूर्ण

	sgx->bytes_consumed += sgx->dma_len;

	अगर (sg_len == sgx->bytes_consumed) अणु
		sg = sg_next(sg);
		sgx->num_sg++;
		sgx->cur_sg = sg;
		sgx->bytes_consumed = 0;
	पूर्ण

	वापस 1;
पूर्ण

पूर्णांक
qla24xx_walk_and_build_sglist_no_dअगरb(काष्ठा qla_hw_data *ha, srb_t *sp,
	काष्ठा dsd64 *dsd, uपूर्णांक16_t tot_dsds, काष्ठा qla_tc_param *tc)
अणु
	व्योम *next_dsd;
	uपूर्णांक8_t avail_dsds = 0;
	uपूर्णांक32_t dsd_list_len;
	काष्ठा dsd_dma *dsd_ptr;
	काष्ठा scatterlist *sg_prot;
	काष्ठा dsd64 *cur_dsd = dsd;
	uपूर्णांक16_t	used_dsds = tot_dsds;
	uपूर्णांक32_t	prot_पूर्णांक; /* protection पूर्णांकerval */
	uपूर्णांक32_t	partial;
	काष्ठा qla2_sgx sgx;
	dma_addr_t	sle_dma;
	uपूर्णांक32_t	sle_dma_len, tot_prot_dma_len = 0;
	काष्ठा scsi_cmnd *cmd;

	स_रखो(&sgx, 0, माप(काष्ठा qla2_sgx));
	अगर (sp) अणु
		cmd = GET_CMD_SP(sp);
		prot_पूर्णांक = cmd->device->sector_size;

		sgx.tot_bytes = scsi_bufflen(cmd);
		sgx.cur_sg = scsi_sglist(cmd);
		sgx.sp = sp;

		sg_prot = scsi_prot_sglist(cmd);
	पूर्ण अन्यथा अगर (tc) अणु
		prot_पूर्णांक      = tc->blk_sz;
		sgx.tot_bytes = tc->bufflen;
		sgx.cur_sg    = tc->sg;
		sg_prot	      = tc->prot_sg;
	पूर्ण अन्यथा अणु
		BUG();
		वापस 1;
	पूर्ण

	जबतक (qla24xx_get_one_block_sg(prot_पूर्णांक, &sgx, &partial)) अणु

		sle_dma = sgx.dma_addr;
		sle_dma_len = sgx.dma_len;
alloc_and_fill:
		/* Allocate additional continuation packets? */
		अगर (avail_dsds == 0) अणु
			avail_dsds = (used_dsds > QLA_DSDS_PER_IOCB) ?
					QLA_DSDS_PER_IOCB : used_dsds;
			dsd_list_len = (avail_dsds + 1) * 12;
			used_dsds -= avail_dsds;

			/* allocate tracking DS */
			dsd_ptr = kzalloc(माप(काष्ठा dsd_dma), GFP_ATOMIC);
			अगर (!dsd_ptr)
				वापस 1;

			/* allocate new list */
			dsd_ptr->dsd_addr = next_dsd =
			    dma_pool_alloc(ha->dl_dma_pool, GFP_ATOMIC,
				&dsd_ptr->dsd_list_dma);

			अगर (!next_dsd) अणु
				/*
				 * Need to cleanup only this dsd_ptr, rest
				 * will be करोne by sp_मुक्त_dma()
				 */
				kमुक्त(dsd_ptr);
				वापस 1;
			पूर्ण

			अगर (sp) अणु
				list_add_tail(&dsd_ptr->list,
					      &sp->u.scmd.crc_ctx->dsd_list);

				sp->flags |= SRB_CRC_CTX_DSD_VALID;
			पूर्ण अन्यथा अणु
				list_add_tail(&dsd_ptr->list,
				    &(tc->ctx->dsd_list));
				*tc->ctx_dsd_alloced = 1;
			पूर्ण


			/* add new list to cmd iocb or last list */
			put_unaligned_le64(dsd_ptr->dsd_list_dma,
					   &cur_dsd->address);
			cur_dsd->length = cpu_to_le32(dsd_list_len);
			cur_dsd = next_dsd;
		पूर्ण
		put_unaligned_le64(sle_dma, &cur_dsd->address);
		cur_dsd->length = cpu_to_le32(sle_dma_len);
		cur_dsd++;
		avail_dsds--;

		अगर (partial == 0) अणु
			/* Got a full protection पूर्णांकerval */
			sle_dma = sg_dma_address(sg_prot) + tot_prot_dma_len;
			sle_dma_len = 8;

			tot_prot_dma_len += sle_dma_len;
			अगर (tot_prot_dma_len == sg_dma_len(sg_prot)) अणु
				tot_prot_dma_len = 0;
				sg_prot = sg_next(sg_prot);
			पूर्ण

			partial = 1; /* So as to not re-enter this block */
			जाओ alloc_and_fill;
		पूर्ण
	पूर्ण
	/* Null termination */
	cur_dsd->address = 0;
	cur_dsd->length = 0;
	cur_dsd++;
	वापस 0;
पूर्ण

पूर्णांक
qla24xx_walk_and_build_sglist(काष्ठा qla_hw_data *ha, srb_t *sp,
	काष्ठा dsd64 *dsd, uपूर्णांक16_t tot_dsds, काष्ठा qla_tc_param *tc)
अणु
	व्योम *next_dsd;
	uपूर्णांक8_t avail_dsds = 0;
	uपूर्णांक32_t dsd_list_len;
	काष्ठा dsd_dma *dsd_ptr;
	काष्ठा scatterlist *sg, *sgl;
	काष्ठा dsd64 *cur_dsd = dsd;
	पूर्णांक	i;
	uपूर्णांक16_t	used_dsds = tot_dsds;
	काष्ठा scsi_cmnd *cmd;

	अगर (sp) अणु
		cmd = GET_CMD_SP(sp);
		sgl = scsi_sglist(cmd);
	पूर्ण अन्यथा अगर (tc) अणु
		sgl = tc->sg;
	पूर्ण अन्यथा अणु
		BUG();
		वापस 1;
	पूर्ण


	क्रम_each_sg(sgl, sg, tot_dsds, i) अणु
		/* Allocate additional continuation packets? */
		अगर (avail_dsds == 0) अणु
			avail_dsds = (used_dsds > QLA_DSDS_PER_IOCB) ?
					QLA_DSDS_PER_IOCB : used_dsds;
			dsd_list_len = (avail_dsds + 1) * 12;
			used_dsds -= avail_dsds;

			/* allocate tracking DS */
			dsd_ptr = kzalloc(माप(काष्ठा dsd_dma), GFP_ATOMIC);
			अगर (!dsd_ptr)
				वापस 1;

			/* allocate new list */
			dsd_ptr->dsd_addr = next_dsd =
			    dma_pool_alloc(ha->dl_dma_pool, GFP_ATOMIC,
				&dsd_ptr->dsd_list_dma);

			अगर (!next_dsd) अणु
				/*
				 * Need to cleanup only this dsd_ptr, rest
				 * will be करोne by sp_मुक्त_dma()
				 */
				kमुक्त(dsd_ptr);
				वापस 1;
			पूर्ण

			अगर (sp) अणु
				list_add_tail(&dsd_ptr->list,
					      &sp->u.scmd.crc_ctx->dsd_list);

				sp->flags |= SRB_CRC_CTX_DSD_VALID;
			पूर्ण अन्यथा अणु
				list_add_tail(&dsd_ptr->list,
				    &(tc->ctx->dsd_list));
				*tc->ctx_dsd_alloced = 1;
			पूर्ण

			/* add new list to cmd iocb or last list */
			put_unaligned_le64(dsd_ptr->dsd_list_dma,
					   &cur_dsd->address);
			cur_dsd->length = cpu_to_le32(dsd_list_len);
			cur_dsd = next_dsd;
		पूर्ण
		append_dsd64(&cur_dsd, sg);
		avail_dsds--;

	पूर्ण
	/* Null termination */
	cur_dsd->address = 0;
	cur_dsd->length = 0;
	cur_dsd++;
	वापस 0;
पूर्ण

पूर्णांक
qla24xx_walk_and_build_prot_sglist(काष्ठा qla_hw_data *ha, srb_t *sp,
	काष्ठा dsd64 *cur_dsd, uपूर्णांक16_t tot_dsds, काष्ठा qla_tgt_cmd *tc)
अणु
	काष्ठा dsd_dma *dsd_ptr = शून्य, *dअगर_dsd, *nxt_dsd;
	काष्ठा scatterlist *sg, *sgl;
	काष्ठा crc_context *dअगरctx = शून्य;
	काष्ठा scsi_qla_host *vha;
	uपूर्णांक dsd_list_len;
	uपूर्णांक avail_dsds = 0;
	uपूर्णांक used_dsds = tot_dsds;
	bool dअगर_local_dma_alloc = false;
	bool direction_to_device = false;
	पूर्णांक i;

	अगर (sp) अणु
		काष्ठा scsi_cmnd *cmd = GET_CMD_SP(sp);

		sgl = scsi_prot_sglist(cmd);
		vha = sp->vha;
		dअगरctx = sp->u.scmd.crc_ctx;
		direction_to_device = cmd->sc_data_direction == DMA_TO_DEVICE;
		ql_dbg(ql_dbg_tgt + ql_dbg_verbose, vha, 0xe021,
		  "%s: scsi_cmnd: %p, crc_ctx: %p, sp: %p\n",
			__func__, cmd, dअगरctx, sp);
	पूर्ण अन्यथा अगर (tc) अणु
		vha = tc->vha;
		sgl = tc->prot_sg;
		dअगरctx = tc->ctx;
		direction_to_device = tc->dma_data_direction == DMA_TO_DEVICE;
	पूर्ण अन्यथा अणु
		BUG();
		वापस 1;
	पूर्ण

	ql_dbg(ql_dbg_tgt + ql_dbg_verbose, vha, 0xe021,
	    "%s: enter (write=%u)\n", __func__, direction_to_device);

	/* अगर initiator करोing ग_लिखो or target करोing पढ़ो */
	अगर (direction_to_device) अणु
		क्रम_each_sg(sgl, sg, tot_dsds, i) अणु
			u64 sle_phys = sg_phys(sg);

			/* If SGE addr + len flips bits in upper 32-bits */
			अगर (MSD(sle_phys + sg->length) ^ MSD(sle_phys)) अणु
				ql_dbg(ql_dbg_tgt + ql_dbg_verbose, vha, 0xe022,
				    "%s: page boundary crossing (phys=%llx len=%x)\n",
				    __func__, sle_phys, sg->length);

				अगर (dअगरctx) अणु
					ha->dअगर_bundle_crossed_pages++;
					dअगर_local_dma_alloc = true;
				पूर्ण अन्यथा अणु
					ql_dbg(ql_dbg_tgt + ql_dbg_verbose,
					    vha, 0xe022,
					    "%s: difctx pointer is NULL\n",
					    __func__);
				पूर्ण
				अवरोध;
			पूर्ण
		पूर्ण
		ha->dअगर_bundle_ग_लिखोs++;
	पूर्ण अन्यथा अणु
		ha->dअगर_bundle_पढ़ोs++;
	पूर्ण

	अगर (ql2xdअगरbundlingपूर्णांकernalbuffers)
		dअगर_local_dma_alloc = direction_to_device;

	अगर (dअगर_local_dma_alloc) अणु
		u32 track_dअगरbundl_buf = 0;
		u32 ldma_sg_len = 0;
		u8 ldma_needed = 1;

		dअगरctx->no_dअगर_bundl = 0;
		dअगरctx->dअगर_bundl_len = 0;

		/* Track DSD buffers */
		INIT_LIST_HEAD(&dअगरctx->ldअगर_dsd_list);
		/* Track local DMA buffers */
		INIT_LIST_HEAD(&dअगरctx->ldअगर_dma_hndl_list);

		क्रम_each_sg(sgl, sg, tot_dsds, i) अणु
			u32 sglen = sg_dma_len(sg);

			ql_dbg(ql_dbg_tgt + ql_dbg_verbose, vha, 0xe023,
			    "%s: sg[%x] (phys=%llx sglen=%x) ldma_sg_len: %x dif_bundl_len: %x ldma_needed: %x\n",
			    __func__, i, (u64)sg_phys(sg), sglen, ldma_sg_len,
			    dअगरctx->dअगर_bundl_len, ldma_needed);

			जबतक (sglen) अणु
				u32 xfrlen = 0;

				अगर (ldma_needed) अणु
					/*
					 * Allocate list item to store
					 * the DMA buffers
					 */
					dsd_ptr = kzalloc(माप(*dsd_ptr),
					    GFP_ATOMIC);
					अगर (!dsd_ptr) अणु
						ql_dbg(ql_dbg_tgt, vha, 0xe024,
						    "%s: failed alloc dsd_ptr\n",
						    __func__);
						वापस 1;
					पूर्ण
					ha->dअगर_bundle_kallocs++;

					/* allocate dma buffer */
					dsd_ptr->dsd_addr = dma_pool_alloc
						(ha->dअगर_bundl_pool, GFP_ATOMIC,
						 &dsd_ptr->dsd_list_dma);
					अगर (!dsd_ptr->dsd_addr) अणु
						ql_dbg(ql_dbg_tgt, vha, 0xe024,
						    "%s: failed alloc ->dsd_ptr\n",
						    __func__);
						/*
						 * need to cleanup only this
						 * dsd_ptr rest will be करोne
						 * by sp_मुक्त_dma()
						 */
						kमुक्त(dsd_ptr);
						ha->dअगर_bundle_kallocs--;
						वापस 1;
					पूर्ण
					ha->dअगर_bundle_dma_allocs++;
					ldma_needed = 0;
					dअगरctx->no_dअगर_bundl++;
					list_add_tail(&dsd_ptr->list,
					    &dअगरctx->ldअगर_dma_hndl_list);
				पूर्ण

				/* xfrlen is min of dma pool size and sglen */
				xfrlen = (sglen >
				   (DIF_BUNDLING_DMA_POOL_SIZE - ldma_sg_len)) ?
				    DIF_BUNDLING_DMA_POOL_SIZE - ldma_sg_len :
				    sglen;

				/* replace with local allocated dma buffer */
				sg_pcopy_to_buffer(sgl, sg_nents(sgl),
				    dsd_ptr->dsd_addr + ldma_sg_len, xfrlen,
				    dअगरctx->dअगर_bundl_len);
				dअगरctx->dअगर_bundl_len += xfrlen;
				sglen -= xfrlen;
				ldma_sg_len += xfrlen;
				अगर (ldma_sg_len == DIF_BUNDLING_DMA_POOL_SIZE ||
				    sg_is_last(sg)) अणु
					ldma_needed = 1;
					ldma_sg_len = 0;
				पूर्ण
			पूर्ण
		पूर्ण

		track_dअगरbundl_buf = used_dsds = dअगरctx->no_dअगर_bundl;
		ql_dbg(ql_dbg_tgt + ql_dbg_verbose, vha, 0xe025,
		    "dif_bundl_len=%x, no_dif_bundl=%x track_difbundl_buf: %x\n",
		    dअगरctx->dअगर_bundl_len, dअगरctx->no_dअगर_bundl,
		    track_dअगरbundl_buf);

		अगर (sp)
			sp->flags |= SRB_DIF_BUNDL_DMA_VALID;
		अन्यथा
			tc->prot_flags = DIF_BUNDL_DMA_VALID;

		list_क्रम_each_entry_safe(dअगर_dsd, nxt_dsd,
		    &dअगरctx->ldअगर_dma_hndl_list, list) अणु
			u32 sglen = (dअगरctx->dअगर_bundl_len >
			    DIF_BUNDLING_DMA_POOL_SIZE) ?
			    DIF_BUNDLING_DMA_POOL_SIZE : dअगरctx->dअगर_bundl_len;

			BUG_ON(track_dअगरbundl_buf == 0);

			/* Allocate additional continuation packets? */
			अगर (avail_dsds == 0) अणु
				ql_dbg(ql_dbg_tgt + ql_dbg_verbose, vha,
				    0xe024,
				    "%s: adding continuation iocb's\n",
				    __func__);
				avail_dsds = (used_dsds > QLA_DSDS_PER_IOCB) ?
				    QLA_DSDS_PER_IOCB : used_dsds;
				dsd_list_len = (avail_dsds + 1) * 12;
				used_dsds -= avail_dsds;

				/* allocate tracking DS */
				dsd_ptr = kzalloc(माप(*dsd_ptr), GFP_ATOMIC);
				अगर (!dsd_ptr) अणु
					ql_dbg(ql_dbg_tgt, vha, 0xe026,
					    "%s: failed alloc dsd_ptr\n",
					    __func__);
					वापस 1;
				पूर्ण
				ha->dअगर_bundle_kallocs++;

				dअगरctx->no_ldअगर_dsd++;
				/* allocate new list */
				dsd_ptr->dsd_addr =
				    dma_pool_alloc(ha->dl_dma_pool, GFP_ATOMIC,
					&dsd_ptr->dsd_list_dma);
				अगर (!dsd_ptr->dsd_addr) अणु
					ql_dbg(ql_dbg_tgt, vha, 0xe026,
					    "%s: failed alloc ->dsd_addr\n",
					    __func__);
					/*
					 * need to cleanup only this dsd_ptr
					 *  rest will be करोne by sp_मुक्त_dma()
					 */
					kमुक्त(dsd_ptr);
					ha->dअगर_bundle_kallocs--;
					वापस 1;
				पूर्ण
				ha->dअगर_bundle_dma_allocs++;

				अगर (sp) अणु
					list_add_tail(&dsd_ptr->list,
					    &dअगरctx->ldअगर_dsd_list);
					sp->flags |= SRB_CRC_CTX_DSD_VALID;
				पूर्ण अन्यथा अणु
					list_add_tail(&dsd_ptr->list,
					    &dअगरctx->ldअगर_dsd_list);
					tc->ctx_dsd_alloced = 1;
				पूर्ण

				/* add new list to cmd iocb or last list */
				put_unaligned_le64(dsd_ptr->dsd_list_dma,
						   &cur_dsd->address);
				cur_dsd->length = cpu_to_le32(dsd_list_len);
				cur_dsd = dsd_ptr->dsd_addr;
			पूर्ण
			put_unaligned_le64(dअगर_dsd->dsd_list_dma,
					   &cur_dsd->address);
			cur_dsd->length = cpu_to_le32(sglen);
			cur_dsd++;
			avail_dsds--;
			dअगरctx->dअगर_bundl_len -= sglen;
			track_dअगरbundl_buf--;
		पूर्ण

		ql_dbg(ql_dbg_tgt + ql_dbg_verbose, vha, 0xe026,
		    "%s: no_ldif_dsd:%x, no_dif_bundl:%x\n", __func__,
			dअगरctx->no_ldअगर_dsd, dअगरctx->no_dअगर_bundl);
	पूर्ण अन्यथा अणु
		क्रम_each_sg(sgl, sg, tot_dsds, i) अणु
			/* Allocate additional continuation packets? */
			अगर (avail_dsds == 0) अणु
				avail_dsds = (used_dsds > QLA_DSDS_PER_IOCB) ?
				    QLA_DSDS_PER_IOCB : used_dsds;
				dsd_list_len = (avail_dsds + 1) * 12;
				used_dsds -= avail_dsds;

				/* allocate tracking DS */
				dsd_ptr = kzalloc(माप(*dsd_ptr), GFP_ATOMIC);
				अगर (!dsd_ptr) अणु
					ql_dbg(ql_dbg_tgt + ql_dbg_verbose,
					    vha, 0xe027,
					    "%s: failed alloc dsd_dma...\n",
					    __func__);
					वापस 1;
				पूर्ण

				/* allocate new list */
				dsd_ptr->dsd_addr =
				    dma_pool_alloc(ha->dl_dma_pool, GFP_ATOMIC,
					&dsd_ptr->dsd_list_dma);
				अगर (!dsd_ptr->dsd_addr) अणु
					/* need to cleanup only this dsd_ptr */
					/* rest will be करोne by sp_मुक्त_dma() */
					kमुक्त(dsd_ptr);
					वापस 1;
				पूर्ण

				अगर (sp) अणु
					list_add_tail(&dsd_ptr->list,
					    &dअगरctx->dsd_list);
					sp->flags |= SRB_CRC_CTX_DSD_VALID;
				पूर्ण अन्यथा अणु
					list_add_tail(&dsd_ptr->list,
					    &dअगरctx->dsd_list);
					tc->ctx_dsd_alloced = 1;
				पूर्ण

				/* add new list to cmd iocb or last list */
				put_unaligned_le64(dsd_ptr->dsd_list_dma,
						   &cur_dsd->address);
				cur_dsd->length = cpu_to_le32(dsd_list_len);
				cur_dsd = dsd_ptr->dsd_addr;
			पूर्ण
			append_dsd64(&cur_dsd, sg);
			avail_dsds--;
		पूर्ण
	पूर्ण
	/* Null termination */
	cur_dsd->address = 0;
	cur_dsd->length = 0;
	cur_dsd++;
	वापस 0;
पूर्ण

/**
 * qla24xx_build_scsi_crc_2_iocbs() - Build IOCB command utilizing Command
 *							Type 6 IOCB types.
 *
 * @sp: SRB command to process
 * @cmd_pkt: Command type 3 IOCB
 * @tot_dsds: Total number of segments to transfer
 * @tot_prot_dsds: Total number of segments with protection inक्रमmation
 * @fw_prot_opts: Protection options to be passed to firmware
 */
अटल अंतरभूत पूर्णांक
qla24xx_build_scsi_crc_2_iocbs(srb_t *sp, काष्ठा cmd_type_crc_2 *cmd_pkt,
    uपूर्णांक16_t tot_dsds, uपूर्णांक16_t tot_prot_dsds, uपूर्णांक16_t fw_prot_opts)
अणु
	काष्ठा dsd64		*cur_dsd;
	__be32			*fcp_dl;
	scsi_qla_host_t		*vha;
	काष्ठा scsi_cmnd	*cmd;
	uपूर्णांक32_t		total_bytes = 0;
	uपूर्णांक32_t		data_bytes;
	uपूर्णांक32_t		dअगर_bytes;
	uपूर्णांक8_t			bundling = 1;
	uपूर्णांक16_t		blk_size;
	काष्ठा crc_context	*crc_ctx_pkt = शून्य;
	काष्ठा qla_hw_data	*ha;
	uपूर्णांक8_t			additional_fcpcdb_len;
	uपूर्णांक16_t		fcp_cmnd_len;
	काष्ठा fcp_cmnd		*fcp_cmnd;
	dma_addr_t		crc_ctx_dma;

	cmd = GET_CMD_SP(sp);

	/* Update entry type to indicate Command Type CRC_2 IOCB */
	put_unaligned_le32(COMMAND_TYPE_CRC_2, &cmd_pkt->entry_type);

	vha = sp->vha;
	ha = vha->hw;

	/* No data transfer */
	data_bytes = scsi_bufflen(cmd);
	अगर (!data_bytes || cmd->sc_data_direction == DMA_NONE) अणु
		cmd_pkt->byte_count = cpu_to_le32(0);
		वापस QLA_SUCCESS;
	पूर्ण

	cmd_pkt->vp_index = sp->vha->vp_idx;

	/* Set transfer direction */
	अगर (cmd->sc_data_direction == DMA_TO_DEVICE) अणु
		cmd_pkt->control_flags =
		    cpu_to_le16(CF_WRITE_DATA);
	पूर्ण अन्यथा अगर (cmd->sc_data_direction == DMA_FROM_DEVICE) अणु
		cmd_pkt->control_flags =
		    cpu_to_le16(CF_READ_DATA);
	पूर्ण

	अगर ((scsi_get_prot_op(cmd) == SCSI_PROT_READ_INSERT) ||
	    (scsi_get_prot_op(cmd) == SCSI_PROT_WRITE_STRIP) ||
	    (scsi_get_prot_op(cmd) == SCSI_PROT_READ_STRIP) ||
	    (scsi_get_prot_op(cmd) == SCSI_PROT_WRITE_INSERT))
		bundling = 0;

	/* Allocate CRC context from global pool */
	crc_ctx_pkt = sp->u.scmd.crc_ctx =
	    dma_pool_zalloc(ha->dl_dma_pool, GFP_ATOMIC, &crc_ctx_dma);

	अगर (!crc_ctx_pkt)
		जाओ crc_queuing_error;

	crc_ctx_pkt->crc_ctx_dma = crc_ctx_dma;

	sp->flags |= SRB_CRC_CTX_DMA_VALID;

	/* Set handle */
	crc_ctx_pkt->handle = cmd_pkt->handle;

	INIT_LIST_HEAD(&crc_ctx_pkt->dsd_list);

	qla24xx_set_t10dअगर_tags(sp, (काष्ठा fw_dअगर_context *)
	    &crc_ctx_pkt->ref_tag, tot_prot_dsds);

	put_unaligned_le64(crc_ctx_dma, &cmd_pkt->crc_context_address);
	cmd_pkt->crc_context_len = cpu_to_le16(CRC_CONTEXT_LEN_FW);

	/* Determine SCSI command length -- align to 4 byte boundary */
	अगर (cmd->cmd_len > 16) अणु
		additional_fcpcdb_len = cmd->cmd_len - 16;
		अगर ((cmd->cmd_len % 4) != 0) अणु
			/* SCSI cmd > 16 bytes must be multiple of 4 */
			जाओ crc_queuing_error;
		पूर्ण
		fcp_cmnd_len = 12 + cmd->cmd_len + 4;
	पूर्ण अन्यथा अणु
		additional_fcpcdb_len = 0;
		fcp_cmnd_len = 12 + 16 + 4;
	पूर्ण

	fcp_cmnd = &crc_ctx_pkt->fcp_cmnd;

	fcp_cmnd->additional_cdb_len = additional_fcpcdb_len;
	अगर (cmd->sc_data_direction == DMA_TO_DEVICE)
		fcp_cmnd->additional_cdb_len |= 1;
	अन्यथा अगर (cmd->sc_data_direction == DMA_FROM_DEVICE)
		fcp_cmnd->additional_cdb_len |= 2;

	पूर्णांक_to_scsilun(cmd->device->lun, &fcp_cmnd->lun);
	स_नकल(fcp_cmnd->cdb, cmd->cmnd, cmd->cmd_len);
	cmd_pkt->fcp_cmnd_dseg_len = cpu_to_le16(fcp_cmnd_len);
	put_unaligned_le64(crc_ctx_dma + CRC_CONTEXT_FCPCMND_OFF,
			   &cmd_pkt->fcp_cmnd_dseg_address);
	fcp_cmnd->task_management = 0;
	fcp_cmnd->task_attribute = TSK_SIMPLE;

	cmd_pkt->fcp_rsp_dseg_len = 0; /* Let response come in status iocb */

	/* Compute dअगर len and adjust data len to incude protection */
	dअगर_bytes = 0;
	blk_size = cmd->device->sector_size;
	dअगर_bytes = (data_bytes / blk_size) * 8;

	चयन (scsi_get_prot_op(GET_CMD_SP(sp))) अणु
	हाल SCSI_PROT_READ_INSERT:
	हाल SCSI_PROT_WRITE_STRIP:
		total_bytes = data_bytes;
		data_bytes += dअगर_bytes;
		अवरोध;

	हाल SCSI_PROT_READ_STRIP:
	हाल SCSI_PROT_WRITE_INSERT:
	हाल SCSI_PROT_READ_PASS:
	हाल SCSI_PROT_WRITE_PASS:
		total_bytes = data_bytes + dअगर_bytes;
		अवरोध;
	शेष:
		BUG();
	पूर्ण

	अगर (!qla2x00_hba_err_chk_enabled(sp))
		fw_prot_opts |= 0x10; /* Disable Guard tag checking */
	/* HBA error checking enabled */
	अन्यथा अगर (IS_PI_UNINIT_CAPABLE(ha)) अणु
		अगर ((scsi_get_prot_type(GET_CMD_SP(sp)) == SCSI_PROT_DIF_TYPE1)
		    || (scsi_get_prot_type(GET_CMD_SP(sp)) ==
			SCSI_PROT_DIF_TYPE2))
			fw_prot_opts |= BIT_10;
		अन्यथा अगर (scsi_get_prot_type(GET_CMD_SP(sp)) ==
		    SCSI_PROT_DIF_TYPE3)
			fw_prot_opts |= BIT_11;
	पूर्ण

	अगर (!bundling) अणु
		cur_dsd = &crc_ctx_pkt->u.nobundling.data_dsd[0];
	पूर्ण अन्यथा अणु
		/*
		 * Configure Bundling अगर we need to fetch पूर्णांकerlaving
		 * protection PCI accesses
		 */
		fw_prot_opts |= PO_ENABLE_DIF_BUNDLING;
		crc_ctx_pkt->u.bundling.dअगर_byte_count = cpu_to_le32(dअगर_bytes);
		crc_ctx_pkt->u.bundling.dseg_count = cpu_to_le16(tot_dsds -
							tot_prot_dsds);
		cur_dsd = &crc_ctx_pkt->u.bundling.data_dsd[0];
	पूर्ण

	/* Finish the common fields of CRC pkt */
	crc_ctx_pkt->blk_size = cpu_to_le16(blk_size);
	crc_ctx_pkt->prot_opts = cpu_to_le16(fw_prot_opts);
	crc_ctx_pkt->byte_count = cpu_to_le32(data_bytes);
	crc_ctx_pkt->guard_seed = cpu_to_le16(0);
	/* Fibre channel byte count */
	cmd_pkt->byte_count = cpu_to_le32(total_bytes);
	fcp_dl = (__be32 *)(crc_ctx_pkt->fcp_cmnd.cdb + 16 +
	    additional_fcpcdb_len);
	*fcp_dl = htonl(total_bytes);

	अगर (!data_bytes || cmd->sc_data_direction == DMA_NONE) अणु
		cmd_pkt->byte_count = cpu_to_le32(0);
		वापस QLA_SUCCESS;
	पूर्ण
	/* Walks data segments */

	cmd_pkt->control_flags |= cpu_to_le16(CF_DATA_SEG_DESCR_ENABLE);

	अगर (!bundling && tot_prot_dsds) अणु
		अगर (qla24xx_walk_and_build_sglist_no_dअगरb(ha, sp,
			cur_dsd, tot_dsds, शून्य))
			जाओ crc_queuing_error;
	पूर्ण अन्यथा अगर (qla24xx_walk_and_build_sglist(ha, sp, cur_dsd,
			(tot_dsds - tot_prot_dsds), शून्य))
		जाओ crc_queuing_error;

	अगर (bundling && tot_prot_dsds) अणु
		/* Walks dअगर segments */
		cmd_pkt->control_flags |= cpu_to_le16(CF_DIF_SEG_DESCR_ENABLE);
		cur_dsd = &crc_ctx_pkt->u.bundling.dअगर_dsd;
		अगर (qla24xx_walk_and_build_prot_sglist(ha, sp, cur_dsd,
				tot_prot_dsds, शून्य))
			जाओ crc_queuing_error;
	पूर्ण
	वापस QLA_SUCCESS;

crc_queuing_error:
	/* Cleanup will be perक्रमmed by the caller */

	वापस QLA_FUNCTION_FAILED;
पूर्ण

/**
 * qla24xx_start_scsi() - Send a SCSI command to the ISP
 * @sp: command to send to the ISP
 *
 * Returns non-zero अगर a failure occurred, अन्यथा zero.
 */
पूर्णांक
qla24xx_start_scsi(srb_t *sp)
अणु
	पूर्णांक		nseg;
	अचिन्हित दीर्घ   flags;
	uपूर्णांक32_t	*clr_ptr;
	uपूर्णांक32_t	handle;
	काष्ठा cmd_type_7 *cmd_pkt;
	uपूर्णांक16_t	cnt;
	uपूर्णांक16_t	req_cnt;
	uपूर्णांक16_t	tot_dsds;
	काष्ठा req_que *req = शून्य;
	काष्ठा rsp_que *rsp;
	काष्ठा scsi_cmnd *cmd = GET_CMD_SP(sp);
	काष्ठा scsi_qla_host *vha = sp->vha;
	काष्ठा qla_hw_data *ha = vha->hw;

	/* Setup device poपूर्णांकers. */
	req = vha->req;
	rsp = req->rsp;

	/* So we know we haven't pci_map'ed anything yet */
	tot_dsds = 0;

	/* Send marker अगर required */
	अगर (vha->marker_needed != 0) अणु
		अगर (qla2x00_marker(vha, ha->base_qpair, 0, 0, MK_SYNC_ALL) !=
		    QLA_SUCCESS)
			वापस QLA_FUNCTION_FAILED;
		vha->marker_needed = 0;
	पूर्ण

	/* Acquire ring specअगरic lock */
	spin_lock_irqsave(&ha->hardware_lock, flags);

	handle = qla2xxx_get_next_handle(req);
	अगर (handle == 0)
		जाओ queuing_error;

	/* Map the sg table so we have an accurate count of sg entries needed */
	अगर (scsi_sg_count(cmd)) अणु
		nseg = dma_map_sg(&ha->pdev->dev, scsi_sglist(cmd),
		    scsi_sg_count(cmd), cmd->sc_data_direction);
		अगर (unlikely(!nseg))
			जाओ queuing_error;
	पूर्ण अन्यथा
		nseg = 0;

	tot_dsds = nseg;
	req_cnt = qla24xx_calc_iocbs(vha, tot_dsds);

	sp->iores.res_type = RESOURCE_INI;
	sp->iores.iocb_cnt = req_cnt;
	अगर (qla_get_iocbs(sp->qpair, &sp->iores))
		जाओ queuing_error;

	अगर (req->cnt < (req_cnt + 2)) अणु
		अगर (IS_SHADOW_REG_CAPABLE(ha)) अणु
			cnt = *req->out_ptr;
		पूर्ण अन्यथा अणु
			cnt = rd_reg_dword_relaxed(req->req_q_out);
			अगर (qla2x00_check_reg16_क्रम_disconnect(vha, cnt))
				जाओ queuing_error;
		पूर्ण

		अगर (req->ring_index < cnt)
			req->cnt = cnt - req->ring_index;
		अन्यथा
			req->cnt = req->length -
				(req->ring_index - cnt);
		अगर (req->cnt < (req_cnt + 2))
			जाओ queuing_error;
	पूर्ण

	/* Build command packet. */
	req->current_outstanding_cmd = handle;
	req->outstanding_cmds[handle] = sp;
	sp->handle = handle;
	cmd->host_scribble = (अचिन्हित अक्षर *)(अचिन्हित दीर्घ)handle;
	req->cnt -= req_cnt;

	cmd_pkt = (काष्ठा cmd_type_7 *)req->ring_ptr;
	cmd_pkt->handle = make_handle(req->id, handle);

	/* Zero out reमुख्यing portion of packet. */
	/*    tagged queuing modअगरier -- शेष is TSK_SIMPLE (0). */
	clr_ptr = (uपूर्णांक32_t *)cmd_pkt + 2;
	स_रखो(clr_ptr, 0, REQUEST_ENTRY_SIZE - 8);
	cmd_pkt->dseg_count = cpu_to_le16(tot_dsds);

	/* Set NPORT-ID and LUN number*/
	cmd_pkt->nport_handle = cpu_to_le16(sp->fcport->loop_id);
	cmd_pkt->port_id[0] = sp->fcport->d_id.b.al_pa;
	cmd_pkt->port_id[1] = sp->fcport->d_id.b.area;
	cmd_pkt->port_id[2] = sp->fcport->d_id.b.करोमुख्य;
	cmd_pkt->vp_index = sp->vha->vp_idx;

	पूर्णांक_to_scsilun(cmd->device->lun, &cmd_pkt->lun);
	host_to_fcp_swap((uपूर्णांक8_t *)&cmd_pkt->lun, माप(cmd_pkt->lun));

	cmd_pkt->task = TSK_SIMPLE;

	/* Load SCSI command packet. */
	स_नकल(cmd_pkt->fcp_cdb, cmd->cmnd, cmd->cmd_len);
	host_to_fcp_swap(cmd_pkt->fcp_cdb, माप(cmd_pkt->fcp_cdb));

	cmd_pkt->byte_count = cpu_to_le32((uपूर्णांक32_t)scsi_bufflen(cmd));

	/* Build IOCB segments */
	qla24xx_build_scsi_iocbs(sp, cmd_pkt, tot_dsds, req);

	/* Set total data segment count. */
	cmd_pkt->entry_count = (uपूर्णांक8_t)req_cnt;
	wmb();
	/* Adjust ring index. */
	req->ring_index++;
	अगर (req->ring_index == req->length) अणु
		req->ring_index = 0;
		req->ring_ptr = req->ring;
	पूर्ण अन्यथा
		req->ring_ptr++;

	sp->flags |= SRB_DMA_VALID;

	/* Set chip new ring index. */
	wrt_reg_dword(req->req_q_in, req->ring_index);

	/* Manage unprocessed RIO/ZIO commands in response queue. */
	अगर (vha->flags.process_response_queue &&
	    rsp->ring_ptr->signature != RESPONSE_PROCESSED)
		qla24xx_process_response_queue(vha, rsp);

	spin_unlock_irqrestore(&ha->hardware_lock, flags);
	वापस QLA_SUCCESS;

queuing_error:
	अगर (tot_dsds)
		scsi_dma_unmap(cmd);

	qla_put_iocbs(sp->qpair, &sp->iores);
	spin_unlock_irqrestore(&ha->hardware_lock, flags);

	वापस QLA_FUNCTION_FAILED;
पूर्ण

/**
 * qla24xx_dअगर_start_scsi() - Send a SCSI command to the ISP
 * @sp: command to send to the ISP
 *
 * Returns non-zero अगर a failure occurred, अन्यथा zero.
 */
पूर्णांक
qla24xx_dअगर_start_scsi(srb_t *sp)
अणु
	पूर्णांक			nseg;
	अचिन्हित दीर्घ		flags;
	uपूर्णांक32_t		*clr_ptr;
	uपूर्णांक32_t		handle;
	uपूर्णांक16_t		cnt;
	uपूर्णांक16_t		req_cnt = 0;
	uपूर्णांक16_t		tot_dsds;
	uपूर्णांक16_t		tot_prot_dsds;
	uपूर्णांक16_t		fw_prot_opts = 0;
	काष्ठा req_que		*req = शून्य;
	काष्ठा rsp_que		*rsp = शून्य;
	काष्ठा scsi_cmnd	*cmd = GET_CMD_SP(sp);
	काष्ठा scsi_qla_host	*vha = sp->vha;
	काष्ठा qla_hw_data	*ha = vha->hw;
	काष्ठा cmd_type_crc_2	*cmd_pkt;
	uपूर्णांक32_t		status = 0;

#घोषणा QDSS_GOT_Q_SPACE	BIT_0

	/* Only process protection or >16 cdb in this routine */
	अगर (scsi_get_prot_op(cmd) == SCSI_PROT_NORMAL) अणु
		अगर (cmd->cmd_len <= 16)
			वापस qla24xx_start_scsi(sp);
	पूर्ण

	/* Setup device poपूर्णांकers. */
	req = vha->req;
	rsp = req->rsp;

	/* So we know we haven't pci_map'ed anything yet */
	tot_dsds = 0;

	/* Send marker अगर required */
	अगर (vha->marker_needed != 0) अणु
		अगर (qla2x00_marker(vha, ha->base_qpair, 0, 0, MK_SYNC_ALL) !=
		    QLA_SUCCESS)
			वापस QLA_FUNCTION_FAILED;
		vha->marker_needed = 0;
	पूर्ण

	/* Acquire ring specअगरic lock */
	spin_lock_irqsave(&ha->hardware_lock, flags);

	handle = qla2xxx_get_next_handle(req);
	अगर (handle == 0)
		जाओ queuing_error;

	/* Compute number of required data segments */
	/* Map the sg table so we have an accurate count of sg entries needed */
	अगर (scsi_sg_count(cmd)) अणु
		nseg = dma_map_sg(&ha->pdev->dev, scsi_sglist(cmd),
		    scsi_sg_count(cmd), cmd->sc_data_direction);
		अगर (unlikely(!nseg))
			जाओ queuing_error;
		अन्यथा
			sp->flags |= SRB_DMA_VALID;

		अगर ((scsi_get_prot_op(cmd) == SCSI_PROT_READ_INSERT) ||
		    (scsi_get_prot_op(cmd) == SCSI_PROT_WRITE_STRIP)) अणु
			काष्ठा qla2_sgx sgx;
			uपूर्णांक32_t	partial;

			स_रखो(&sgx, 0, माप(काष्ठा qla2_sgx));
			sgx.tot_bytes = scsi_bufflen(cmd);
			sgx.cur_sg = scsi_sglist(cmd);
			sgx.sp = sp;

			nseg = 0;
			जबतक (qla24xx_get_one_block_sg(
			    cmd->device->sector_size, &sgx, &partial))
				nseg++;
		पूर्ण
	पूर्ण अन्यथा
		nseg = 0;

	/* number of required data segments */
	tot_dsds = nseg;

	/* Compute number of required protection segments */
	अगर (qla24xx_configure_prot_mode(sp, &fw_prot_opts)) अणु
		nseg = dma_map_sg(&ha->pdev->dev, scsi_prot_sglist(cmd),
		    scsi_prot_sg_count(cmd), cmd->sc_data_direction);
		अगर (unlikely(!nseg))
			जाओ queuing_error;
		अन्यथा
			sp->flags |= SRB_CRC_PROT_DMA_VALID;

		अगर ((scsi_get_prot_op(cmd) == SCSI_PROT_READ_INSERT) ||
		    (scsi_get_prot_op(cmd) == SCSI_PROT_WRITE_STRIP)) अणु
			nseg = scsi_bufflen(cmd) / cmd->device->sector_size;
		पूर्ण
	पूर्ण अन्यथा अणु
		nseg = 0;
	पूर्ण

	req_cnt = 1;
	/* Total Data and protection sg segment(s) */
	tot_prot_dsds = nseg;
	tot_dsds += nseg;

	sp->iores.res_type = RESOURCE_INI;
	sp->iores.iocb_cnt = qla24xx_calc_iocbs(vha, tot_dsds);
	अगर (qla_get_iocbs(sp->qpair, &sp->iores))
		जाओ queuing_error;

	अगर (req->cnt < (req_cnt + 2)) अणु
		अगर (IS_SHADOW_REG_CAPABLE(ha)) अणु
			cnt = *req->out_ptr;
		पूर्ण अन्यथा अणु
			cnt = rd_reg_dword_relaxed(req->req_q_out);
			अगर (qla2x00_check_reg16_क्रम_disconnect(vha, cnt))
				जाओ queuing_error;
		पूर्ण
		अगर (req->ring_index < cnt)
			req->cnt = cnt - req->ring_index;
		अन्यथा
			req->cnt = req->length -
				(req->ring_index - cnt);
		अगर (req->cnt < (req_cnt + 2))
			जाओ queuing_error;
	पूर्ण

	status |= QDSS_GOT_Q_SPACE;

	/* Build header part of command packet (excluding the OPCODE). */
	req->current_outstanding_cmd = handle;
	req->outstanding_cmds[handle] = sp;
	sp->handle = handle;
	cmd->host_scribble = (अचिन्हित अक्षर *)(अचिन्हित दीर्घ)handle;
	req->cnt -= req_cnt;

	/* Fill-in common area */
	cmd_pkt = (काष्ठा cmd_type_crc_2 *)req->ring_ptr;
	cmd_pkt->handle = make_handle(req->id, handle);

	clr_ptr = (uपूर्णांक32_t *)cmd_pkt + 2;
	स_रखो(clr_ptr, 0, REQUEST_ENTRY_SIZE - 8);

	/* Set NPORT-ID and LUN number*/
	cmd_pkt->nport_handle = cpu_to_le16(sp->fcport->loop_id);
	cmd_pkt->port_id[0] = sp->fcport->d_id.b.al_pa;
	cmd_pkt->port_id[1] = sp->fcport->d_id.b.area;
	cmd_pkt->port_id[2] = sp->fcport->d_id.b.करोमुख्य;

	पूर्णांक_to_scsilun(cmd->device->lun, &cmd_pkt->lun);
	host_to_fcp_swap((uपूर्णांक8_t *)&cmd_pkt->lun, माप(cmd_pkt->lun));

	/* Total Data and protection segment(s) */
	cmd_pkt->dseg_count = cpu_to_le16(tot_dsds);

	/* Build IOCB segments and adjust क्रम data protection segments */
	अगर (qla24xx_build_scsi_crc_2_iocbs(sp, (काष्ठा cmd_type_crc_2 *)
	    req->ring_ptr, tot_dsds, tot_prot_dsds, fw_prot_opts) !=
		QLA_SUCCESS)
		जाओ queuing_error;

	cmd_pkt->entry_count = (uपूर्णांक8_t)req_cnt;
	/* Specअगरy response queue number where completion should happen */
	cmd_pkt->entry_status = (uपूर्णांक8_t) rsp->id;
	cmd_pkt->समयout = cpu_to_le16(0);
	wmb();

	/* Adjust ring index. */
	req->ring_index++;
	अगर (req->ring_index == req->length) अणु
		req->ring_index = 0;
		req->ring_ptr = req->ring;
	पूर्ण अन्यथा
		req->ring_ptr++;

	/* Set chip new ring index. */
	wrt_reg_dword(req->req_q_in, req->ring_index);

	/* Manage unprocessed RIO/ZIO commands in response queue. */
	अगर (vha->flags.process_response_queue &&
	    rsp->ring_ptr->signature != RESPONSE_PROCESSED)
		qla24xx_process_response_queue(vha, rsp);

	spin_unlock_irqrestore(&ha->hardware_lock, flags);

	वापस QLA_SUCCESS;

queuing_error:
	अगर (status & QDSS_GOT_Q_SPACE) अणु
		req->outstanding_cmds[handle] = शून्य;
		req->cnt += req_cnt;
	पूर्ण
	/* Cleanup will be perक्रमmed by the caller (queuecommand) */

	qla_put_iocbs(sp->qpair, &sp->iores);
	spin_unlock_irqrestore(&ha->hardware_lock, flags);

	वापस QLA_FUNCTION_FAILED;
पूर्ण

/**
 * qla2xxx_start_scsi_mq() - Send a SCSI command to the ISP
 * @sp: command to send to the ISP
 *
 * Returns non-zero अगर a failure occurred, अन्यथा zero.
 */
अटल पूर्णांक
qla2xxx_start_scsi_mq(srb_t *sp)
अणु
	पूर्णांक		nseg;
	अचिन्हित दीर्घ   flags;
	uपूर्णांक32_t	*clr_ptr;
	uपूर्णांक32_t	handle;
	काष्ठा cmd_type_7 *cmd_pkt;
	uपूर्णांक16_t	cnt;
	uपूर्णांक16_t	req_cnt;
	uपूर्णांक16_t	tot_dsds;
	काष्ठा req_que *req = शून्य;
	काष्ठा rsp_que *rsp;
	काष्ठा scsi_cmnd *cmd = GET_CMD_SP(sp);
	काष्ठा scsi_qla_host *vha = sp->fcport->vha;
	काष्ठा qla_hw_data *ha = vha->hw;
	काष्ठा qla_qpair *qpair = sp->qpair;

	/* Acquire qpair specअगरic lock */
	spin_lock_irqsave(&qpair->qp_lock, flags);

	/* Setup qpair poपूर्णांकers */
	req = qpair->req;
	rsp = qpair->rsp;

	/* So we know we haven't pci_map'ed anything yet */
	tot_dsds = 0;

	/* Send marker अगर required */
	अगर (vha->marker_needed != 0) अणु
		अगर (__qla2x00_marker(vha, qpair, 0, 0, MK_SYNC_ALL) !=
		    QLA_SUCCESS) अणु
			spin_unlock_irqrestore(&qpair->qp_lock, flags);
			वापस QLA_FUNCTION_FAILED;
		पूर्ण
		vha->marker_needed = 0;
	पूर्ण

	handle = qla2xxx_get_next_handle(req);
	अगर (handle == 0)
		जाओ queuing_error;

	/* Map the sg table so we have an accurate count of sg entries needed */
	अगर (scsi_sg_count(cmd)) अणु
		nseg = dma_map_sg(&ha->pdev->dev, scsi_sglist(cmd),
		    scsi_sg_count(cmd), cmd->sc_data_direction);
		अगर (unlikely(!nseg))
			जाओ queuing_error;
	पूर्ण अन्यथा
		nseg = 0;

	tot_dsds = nseg;
	req_cnt = qla24xx_calc_iocbs(vha, tot_dsds);

	sp->iores.res_type = RESOURCE_INI;
	sp->iores.iocb_cnt = req_cnt;
	अगर (qla_get_iocbs(sp->qpair, &sp->iores))
		जाओ queuing_error;

	अगर (req->cnt < (req_cnt + 2)) अणु
		अगर (IS_SHADOW_REG_CAPABLE(ha)) अणु
			cnt = *req->out_ptr;
		पूर्ण अन्यथा अणु
			cnt = rd_reg_dword_relaxed(req->req_q_out);
			अगर (qla2x00_check_reg16_क्रम_disconnect(vha, cnt))
				जाओ queuing_error;
		पूर्ण

		अगर (req->ring_index < cnt)
			req->cnt = cnt - req->ring_index;
		अन्यथा
			req->cnt = req->length -
				(req->ring_index - cnt);
		अगर (req->cnt < (req_cnt + 2))
			जाओ queuing_error;
	पूर्ण

	/* Build command packet. */
	req->current_outstanding_cmd = handle;
	req->outstanding_cmds[handle] = sp;
	sp->handle = handle;
	cmd->host_scribble = (अचिन्हित अक्षर *)(अचिन्हित दीर्घ)handle;
	req->cnt -= req_cnt;

	cmd_pkt = (काष्ठा cmd_type_7 *)req->ring_ptr;
	cmd_pkt->handle = make_handle(req->id, handle);

	/* Zero out reमुख्यing portion of packet. */
	/*    tagged queuing modअगरier -- शेष is TSK_SIMPLE (0). */
	clr_ptr = (uपूर्णांक32_t *)cmd_pkt + 2;
	स_रखो(clr_ptr, 0, REQUEST_ENTRY_SIZE - 8);
	cmd_pkt->dseg_count = cpu_to_le16(tot_dsds);

	/* Set NPORT-ID and LUN number*/
	cmd_pkt->nport_handle = cpu_to_le16(sp->fcport->loop_id);
	cmd_pkt->port_id[0] = sp->fcport->d_id.b.al_pa;
	cmd_pkt->port_id[1] = sp->fcport->d_id.b.area;
	cmd_pkt->port_id[2] = sp->fcport->d_id.b.करोमुख्य;
	cmd_pkt->vp_index = sp->fcport->vha->vp_idx;

	पूर्णांक_to_scsilun(cmd->device->lun, &cmd_pkt->lun);
	host_to_fcp_swap((uपूर्णांक8_t *)&cmd_pkt->lun, माप(cmd_pkt->lun));

	cmd_pkt->task = TSK_SIMPLE;

	/* Load SCSI command packet. */
	स_नकल(cmd_pkt->fcp_cdb, cmd->cmnd, cmd->cmd_len);
	host_to_fcp_swap(cmd_pkt->fcp_cdb, माप(cmd_pkt->fcp_cdb));

	cmd_pkt->byte_count = cpu_to_le32((uपूर्णांक32_t)scsi_bufflen(cmd));

	/* Build IOCB segments */
	qla24xx_build_scsi_iocbs(sp, cmd_pkt, tot_dsds, req);

	/* Set total data segment count. */
	cmd_pkt->entry_count = (uपूर्णांक8_t)req_cnt;
	wmb();
	/* Adjust ring index. */
	req->ring_index++;
	अगर (req->ring_index == req->length) अणु
		req->ring_index = 0;
		req->ring_ptr = req->ring;
	पूर्ण अन्यथा
		req->ring_ptr++;

	sp->flags |= SRB_DMA_VALID;

	/* Set chip new ring index. */
	wrt_reg_dword(req->req_q_in, req->ring_index);

	/* Manage unprocessed RIO/ZIO commands in response queue. */
	अगर (vha->flags.process_response_queue &&
	    rsp->ring_ptr->signature != RESPONSE_PROCESSED)
		qla24xx_process_response_queue(vha, rsp);

	spin_unlock_irqrestore(&qpair->qp_lock, flags);
	वापस QLA_SUCCESS;

queuing_error:
	अगर (tot_dsds)
		scsi_dma_unmap(cmd);

	qla_put_iocbs(sp->qpair, &sp->iores);
	spin_unlock_irqrestore(&qpair->qp_lock, flags);

	वापस QLA_FUNCTION_FAILED;
पूर्ण


/**
 * qla2xxx_dअगर_start_scsi_mq() - Send a SCSI command to the ISP
 * @sp: command to send to the ISP
 *
 * Returns non-zero अगर a failure occurred, अन्यथा zero.
 */
पूर्णांक
qla2xxx_dअगर_start_scsi_mq(srb_t *sp)
अणु
	पूर्णांक			nseg;
	अचिन्हित दीर्घ		flags;
	uपूर्णांक32_t		*clr_ptr;
	uपूर्णांक32_t		handle;
	uपूर्णांक16_t		cnt;
	uपूर्णांक16_t		req_cnt = 0;
	uपूर्णांक16_t		tot_dsds;
	uपूर्णांक16_t		tot_prot_dsds;
	uपूर्णांक16_t		fw_prot_opts = 0;
	काष्ठा req_que		*req = शून्य;
	काष्ठा rsp_que		*rsp = शून्य;
	काष्ठा scsi_cmnd	*cmd = GET_CMD_SP(sp);
	काष्ठा scsi_qla_host	*vha = sp->fcport->vha;
	काष्ठा qla_hw_data	*ha = vha->hw;
	काष्ठा cmd_type_crc_2	*cmd_pkt;
	uपूर्णांक32_t		status = 0;
	काष्ठा qla_qpair	*qpair = sp->qpair;

#घोषणा QDSS_GOT_Q_SPACE	BIT_0

	/* Check क्रम host side state */
	अगर (!qpair->online) अणु
		cmd->result = DID_NO_CONNECT << 16;
		वापस QLA_INTERFACE_ERROR;
	पूर्ण

	अगर (!qpair->dअगरdix_supported &&
		scsi_get_prot_op(cmd) != SCSI_PROT_NORMAL) अणु
		cmd->result = DID_NO_CONNECT << 16;
		वापस QLA_INTERFACE_ERROR;
	पूर्ण

	/* Only process protection or >16 cdb in this routine */
	अगर (scsi_get_prot_op(cmd) == SCSI_PROT_NORMAL) अणु
		अगर (cmd->cmd_len <= 16)
			वापस qla2xxx_start_scsi_mq(sp);
	पूर्ण

	spin_lock_irqsave(&qpair->qp_lock, flags);

	/* Setup qpair poपूर्णांकers */
	rsp = qpair->rsp;
	req = qpair->req;

	/* So we know we haven't pci_map'ed anything yet */
	tot_dsds = 0;

	/* Send marker अगर required */
	अगर (vha->marker_needed != 0) अणु
		अगर (__qla2x00_marker(vha, qpair, 0, 0, MK_SYNC_ALL) !=
		    QLA_SUCCESS) अणु
			spin_unlock_irqrestore(&qpair->qp_lock, flags);
			वापस QLA_FUNCTION_FAILED;
		पूर्ण
		vha->marker_needed = 0;
	पूर्ण

	handle = qla2xxx_get_next_handle(req);
	अगर (handle == 0)
		जाओ queuing_error;

	/* Compute number of required data segments */
	/* Map the sg table so we have an accurate count of sg entries needed */
	अगर (scsi_sg_count(cmd)) अणु
		nseg = dma_map_sg(&ha->pdev->dev, scsi_sglist(cmd),
		    scsi_sg_count(cmd), cmd->sc_data_direction);
		अगर (unlikely(!nseg))
			जाओ queuing_error;
		अन्यथा
			sp->flags |= SRB_DMA_VALID;

		अगर ((scsi_get_prot_op(cmd) == SCSI_PROT_READ_INSERT) ||
		    (scsi_get_prot_op(cmd) == SCSI_PROT_WRITE_STRIP)) अणु
			काष्ठा qla2_sgx sgx;
			uपूर्णांक32_t	partial;

			स_रखो(&sgx, 0, माप(काष्ठा qla2_sgx));
			sgx.tot_bytes = scsi_bufflen(cmd);
			sgx.cur_sg = scsi_sglist(cmd);
			sgx.sp = sp;

			nseg = 0;
			जबतक (qla24xx_get_one_block_sg(
			    cmd->device->sector_size, &sgx, &partial))
				nseg++;
		पूर्ण
	पूर्ण अन्यथा
		nseg = 0;

	/* number of required data segments */
	tot_dsds = nseg;

	/* Compute number of required protection segments */
	अगर (qla24xx_configure_prot_mode(sp, &fw_prot_opts)) अणु
		nseg = dma_map_sg(&ha->pdev->dev, scsi_prot_sglist(cmd),
		    scsi_prot_sg_count(cmd), cmd->sc_data_direction);
		अगर (unlikely(!nseg))
			जाओ queuing_error;
		अन्यथा
			sp->flags |= SRB_CRC_PROT_DMA_VALID;

		अगर ((scsi_get_prot_op(cmd) == SCSI_PROT_READ_INSERT) ||
		    (scsi_get_prot_op(cmd) == SCSI_PROT_WRITE_STRIP)) अणु
			nseg = scsi_bufflen(cmd) / cmd->device->sector_size;
		पूर्ण
	पूर्ण अन्यथा अणु
		nseg = 0;
	पूर्ण

	req_cnt = 1;
	/* Total Data and protection sg segment(s) */
	tot_prot_dsds = nseg;
	tot_dsds += nseg;

	sp->iores.res_type = RESOURCE_INI;
	sp->iores.iocb_cnt = qla24xx_calc_iocbs(vha, tot_dsds);
	अगर (qla_get_iocbs(sp->qpair, &sp->iores))
		जाओ queuing_error;

	अगर (req->cnt < (req_cnt + 2)) अणु
		अगर (IS_SHADOW_REG_CAPABLE(ha)) अणु
			cnt = *req->out_ptr;
		पूर्ण अन्यथा अणु
			cnt = rd_reg_dword_relaxed(req->req_q_out);
			अगर (qla2x00_check_reg16_क्रम_disconnect(vha, cnt))
				जाओ queuing_error;
		पूर्ण

		अगर (req->ring_index < cnt)
			req->cnt = cnt - req->ring_index;
		अन्यथा
			req->cnt = req->length -
				(req->ring_index - cnt);
		अगर (req->cnt < (req_cnt + 2))
			जाओ queuing_error;
	पूर्ण

	status |= QDSS_GOT_Q_SPACE;

	/* Build header part of command packet (excluding the OPCODE). */
	req->current_outstanding_cmd = handle;
	req->outstanding_cmds[handle] = sp;
	sp->handle = handle;
	cmd->host_scribble = (अचिन्हित अक्षर *)(अचिन्हित दीर्घ)handle;
	req->cnt -= req_cnt;

	/* Fill-in common area */
	cmd_pkt = (काष्ठा cmd_type_crc_2 *)req->ring_ptr;
	cmd_pkt->handle = make_handle(req->id, handle);

	clr_ptr = (uपूर्णांक32_t *)cmd_pkt + 2;
	स_रखो(clr_ptr, 0, REQUEST_ENTRY_SIZE - 8);

	/* Set NPORT-ID and LUN number*/
	cmd_pkt->nport_handle = cpu_to_le16(sp->fcport->loop_id);
	cmd_pkt->port_id[0] = sp->fcport->d_id.b.al_pa;
	cmd_pkt->port_id[1] = sp->fcport->d_id.b.area;
	cmd_pkt->port_id[2] = sp->fcport->d_id.b.करोमुख्य;

	पूर्णांक_to_scsilun(cmd->device->lun, &cmd_pkt->lun);
	host_to_fcp_swap((uपूर्णांक8_t *)&cmd_pkt->lun, माप(cmd_pkt->lun));

	/* Total Data and protection segment(s) */
	cmd_pkt->dseg_count = cpu_to_le16(tot_dsds);

	/* Build IOCB segments and adjust क्रम data protection segments */
	अगर (qla24xx_build_scsi_crc_2_iocbs(sp, (काष्ठा cmd_type_crc_2 *)
	    req->ring_ptr, tot_dsds, tot_prot_dsds, fw_prot_opts) !=
		QLA_SUCCESS)
		जाओ queuing_error;

	cmd_pkt->entry_count = (uपूर्णांक8_t)req_cnt;
	cmd_pkt->समयout = cpu_to_le16(0);
	wmb();

	/* Adjust ring index. */
	req->ring_index++;
	अगर (req->ring_index == req->length) अणु
		req->ring_index = 0;
		req->ring_ptr = req->ring;
	पूर्ण अन्यथा
		req->ring_ptr++;

	/* Set chip new ring index. */
	wrt_reg_dword(req->req_q_in, req->ring_index);

	/* Manage unprocessed RIO/ZIO commands in response queue. */
	अगर (vha->flags.process_response_queue &&
	    rsp->ring_ptr->signature != RESPONSE_PROCESSED)
		qla24xx_process_response_queue(vha, rsp);

	spin_unlock_irqrestore(&qpair->qp_lock, flags);

	वापस QLA_SUCCESS;

queuing_error:
	अगर (status & QDSS_GOT_Q_SPACE) अणु
		req->outstanding_cmds[handle] = शून्य;
		req->cnt += req_cnt;
	पूर्ण
	/* Cleanup will be perक्रमmed by the caller (queuecommand) */

	qla_put_iocbs(sp->qpair, &sp->iores);
	spin_unlock_irqrestore(&qpair->qp_lock, flags);

	वापस QLA_FUNCTION_FAILED;
पूर्ण

/* Generic Control-SRB manipulation functions. */

/* hardware_lock assumed to be held. */

व्योम *
__qla2x00_alloc_iocbs(काष्ठा qla_qpair *qpair, srb_t *sp)
अणु
	scsi_qla_host_t *vha = qpair->vha;
	काष्ठा qla_hw_data *ha = vha->hw;
	काष्ठा req_que *req = qpair->req;
	device_reg_t *reg = ISP_QUE_REG(ha, req->id);
	uपूर्णांक32_t handle;
	request_t *pkt;
	uपूर्णांक16_t cnt, req_cnt;

	pkt = शून्य;
	req_cnt = 1;
	handle = 0;

	अगर (sp && (sp->type != SRB_SCSI_CMD)) अणु
		/* Adjust entry-counts as needed. */
		req_cnt = sp->iocbs;
	पूर्ण

	/* Check क्रम room on request queue. */
	अगर (req->cnt < req_cnt + 2) अणु
		अगर (qpair->use_shaकरोw_reg)
			cnt = *req->out_ptr;
		अन्यथा अगर (ha->mqenable || IS_QLA83XX(ha) || IS_QLA27XX(ha) ||
		    IS_QLA28XX(ha))
			cnt = rd_reg_dword(&reg->isp25mq.req_q_out);
		अन्यथा अगर (IS_P3P_TYPE(ha))
			cnt = rd_reg_dword(reg->isp82.req_q_out);
		अन्यथा अगर (IS_FWI2_CAPABLE(ha))
			cnt = rd_reg_dword(&reg->isp24.req_q_out);
		अन्यथा अगर (IS_QLAFX00(ha))
			cnt = rd_reg_dword(&reg->ispfx00.req_q_out);
		अन्यथा
			cnt = qla2x00_debounce_रेजिस्टर(
			    ISP_REQ_Q_OUT(ha, &reg->isp));

		अगर (!qpair->use_shaकरोw_reg && cnt == ISP_REG16_DISCONNECT) अणु
			qla_schedule_eeh_work(vha);
			वापस शून्य;
		पूर्ण

		अगर  (req->ring_index < cnt)
			req->cnt = cnt - req->ring_index;
		अन्यथा
			req->cnt = req->length -
			    (req->ring_index - cnt);
	पूर्ण
	अगर (req->cnt < req_cnt + 2)
		जाओ queuing_error;

	अगर (sp) अणु
		handle = qla2xxx_get_next_handle(req);
		अगर (handle == 0) अणु
			ql_log(ql_log_warn, vha, 0x700b,
			    "No room on outstanding cmd array.\n");
			जाओ queuing_error;
		पूर्ण

		/* Prep command array. */
		req->current_outstanding_cmd = handle;
		req->outstanding_cmds[handle] = sp;
		sp->handle = handle;
	पूर्ण

	/* Prep packet */
	req->cnt -= req_cnt;
	pkt = req->ring_ptr;
	स_रखो(pkt, 0, REQUEST_ENTRY_SIZE);
	अगर (IS_QLAFX00(ha)) अणु
		wrt_reg_byte((u8 __क्रमce __iomem *)&pkt->entry_count, req_cnt);
		wrt_reg_dword((__le32 __क्रमce __iomem *)&pkt->handle, handle);
	पूर्ण अन्यथा अणु
		pkt->entry_count = req_cnt;
		pkt->handle = handle;
	पूर्ण

	वापस pkt;

queuing_error:
	qpair->tgt_counters.num_alloc_iocb_failed++;
	वापस pkt;
पूर्ण

व्योम *
qla2x00_alloc_iocbs_पढ़ोy(काष्ठा qla_qpair *qpair, srb_t *sp)
अणु
	scsi_qla_host_t *vha = qpair->vha;

	अगर (qla2x00_reset_active(vha))
		वापस शून्य;

	वापस __qla2x00_alloc_iocbs(qpair, sp);
पूर्ण

व्योम *
qla2x00_alloc_iocbs(काष्ठा scsi_qla_host *vha, srb_t *sp)
अणु
	वापस __qla2x00_alloc_iocbs(vha->hw->base_qpair, sp);
पूर्ण

अटल व्योम
qla24xx_prli_iocb(srb_t *sp, काष्ठा logio_entry_24xx *logio)
अणु
	काष्ठा srb_iocb *lio = &sp->u.iocb_cmd;

	logio->entry_type = LOGINOUT_PORT_IOCB_TYPE;
	logio->control_flags = cpu_to_le16(LCF_COMMAND_PRLI);
	अगर (lio->u.logio.flags & SRB_LOGIN_NVME_PRLI) अणु
		logio->control_flags |= cpu_to_le16(LCF_NVME_PRLI);
		अगर (sp->vha->flags.nvme_first_burst)
			logio->io_parameter[0] =
				cpu_to_le32(NVME_PRLI_SP_FIRST_BURST);
		अगर (sp->vha->flags.nvme2_enabled) अणु
			/* Set service parameter BIT_7 क्रम NVME CONF support */
			logio->io_parameter[0] |=
				cpu_to_le32(NVME_PRLI_SP_CONF);
			/* Set service parameter BIT_8 क्रम SLER support */
			logio->io_parameter[0] |=
				cpu_to_le32(NVME_PRLI_SP_SLER);
			/* Set service parameter BIT_9 क्रम PI control support */
			logio->io_parameter[0] |=
				cpu_to_le32(NVME_PRLI_SP_PI_CTRL);
		पूर्ण
	पूर्ण

	logio->nport_handle = cpu_to_le16(sp->fcport->loop_id);
	logio->port_id[0] = sp->fcport->d_id.b.al_pa;
	logio->port_id[1] = sp->fcport->d_id.b.area;
	logio->port_id[2] = sp->fcport->d_id.b.करोमुख्य;
	logio->vp_index = sp->vha->vp_idx;
पूर्ण

अटल व्योम
qla24xx_login_iocb(srb_t *sp, काष्ठा logio_entry_24xx *logio)
अणु
	काष्ठा srb_iocb *lio = &sp->u.iocb_cmd;

	logio->entry_type = LOGINOUT_PORT_IOCB_TYPE;
	logio->control_flags = cpu_to_le16(LCF_COMMAND_PLOGI);

	अगर (lio->u.logio.flags & SRB_LOGIN_PRLI_ONLY) अणु
		logio->control_flags = cpu_to_le16(LCF_COMMAND_PRLI);
	पूर्ण अन्यथा अणु
		logio->control_flags = cpu_to_le16(LCF_COMMAND_PLOGI);
		अगर (lio->u.logio.flags & SRB_LOGIN_COND_PLOGI)
			logio->control_flags |= cpu_to_le16(LCF_COND_PLOGI);
		अगर (lio->u.logio.flags & SRB_LOGIN_SKIP_PRLI)
			logio->control_flags |= cpu_to_le16(LCF_SKIP_PRLI);
	पूर्ण
	logio->nport_handle = cpu_to_le16(sp->fcport->loop_id);
	logio->port_id[0] = sp->fcport->d_id.b.al_pa;
	logio->port_id[1] = sp->fcport->d_id.b.area;
	logio->port_id[2] = sp->fcport->d_id.b.करोमुख्य;
	logio->vp_index = sp->vha->vp_idx;
पूर्ण

अटल व्योम
qla2x00_login_iocb(srb_t *sp, काष्ठा mbx_entry *mbx)
अणु
	काष्ठा qla_hw_data *ha = sp->vha->hw;
	काष्ठा srb_iocb *lio = &sp->u.iocb_cmd;
	uपूर्णांक16_t opts;

	mbx->entry_type = MBX_IOCB_TYPE;
	SET_TARGET_ID(ha, mbx->loop_id, sp->fcport->loop_id);
	mbx->mb0 = cpu_to_le16(MBC_LOGIN_FABRIC_PORT);
	opts = lio->u.logio.flags & SRB_LOGIN_COND_PLOGI ? BIT_0 : 0;
	opts |= lio->u.logio.flags & SRB_LOGIN_SKIP_PRLI ? BIT_1 : 0;
	अगर (HAS_EXTENDED_IDS(ha)) अणु
		mbx->mb1 = cpu_to_le16(sp->fcport->loop_id);
		mbx->mb10 = cpu_to_le16(opts);
	पूर्ण अन्यथा अणु
		mbx->mb1 = cpu_to_le16((sp->fcport->loop_id << 8) | opts);
	पूर्ण
	mbx->mb2 = cpu_to_le16(sp->fcport->d_id.b.करोमुख्य);
	mbx->mb3 = cpu_to_le16(sp->fcport->d_id.b.area << 8 |
	    sp->fcport->d_id.b.al_pa);
	mbx->mb9 = cpu_to_le16(sp->vha->vp_idx);
पूर्ण

अटल व्योम
qla24xx_logout_iocb(srb_t *sp, काष्ठा logio_entry_24xx *logio)
अणु
	u16 control_flags = LCF_COMMAND_LOGO;
	logio->entry_type = LOGINOUT_PORT_IOCB_TYPE;

	अगर (sp->fcport->explicit_logout) अणु
		control_flags |= LCF_EXPL_LOGO|LCF_FREE_NPORT;
	पूर्ण अन्यथा अणु
		control_flags |= LCF_IMPL_LOGO;

		अगर (!sp->fcport->keep_nport_handle)
			control_flags |= LCF_FREE_NPORT;
	पूर्ण

	logio->control_flags = cpu_to_le16(control_flags);
	logio->nport_handle = cpu_to_le16(sp->fcport->loop_id);
	logio->port_id[0] = sp->fcport->d_id.b.al_pa;
	logio->port_id[1] = sp->fcport->d_id.b.area;
	logio->port_id[2] = sp->fcport->d_id.b.करोमुख्य;
	logio->vp_index = sp->vha->vp_idx;
पूर्ण

अटल व्योम
qla2x00_logout_iocb(srb_t *sp, काष्ठा mbx_entry *mbx)
अणु
	काष्ठा qla_hw_data *ha = sp->vha->hw;

	mbx->entry_type = MBX_IOCB_TYPE;
	SET_TARGET_ID(ha, mbx->loop_id, sp->fcport->loop_id);
	mbx->mb0 = cpu_to_le16(MBC_LOGOUT_FABRIC_PORT);
	mbx->mb1 = HAS_EXTENDED_IDS(ha) ?
	    cpu_to_le16(sp->fcport->loop_id) :
	    cpu_to_le16(sp->fcport->loop_id << 8);
	mbx->mb2 = cpu_to_le16(sp->fcport->d_id.b.करोमुख्य);
	mbx->mb3 = cpu_to_le16(sp->fcport->d_id.b.area << 8 |
	    sp->fcport->d_id.b.al_pa);
	mbx->mb9 = cpu_to_le16(sp->vha->vp_idx);
	/* Implicit: mbx->mbx10 = 0. */
पूर्ण

अटल व्योम
qla24xx_adisc_iocb(srb_t *sp, काष्ठा logio_entry_24xx *logio)
अणु
	logio->entry_type = LOGINOUT_PORT_IOCB_TYPE;
	logio->control_flags = cpu_to_le16(LCF_COMMAND_ADISC);
	logio->nport_handle = cpu_to_le16(sp->fcport->loop_id);
	logio->vp_index = sp->vha->vp_idx;
पूर्ण

अटल व्योम
qla2x00_adisc_iocb(srb_t *sp, काष्ठा mbx_entry *mbx)
अणु
	काष्ठा qla_hw_data *ha = sp->vha->hw;

	mbx->entry_type = MBX_IOCB_TYPE;
	SET_TARGET_ID(ha, mbx->loop_id, sp->fcport->loop_id);
	mbx->mb0 = cpu_to_le16(MBC_GET_PORT_DATABASE);
	अगर (HAS_EXTENDED_IDS(ha)) अणु
		mbx->mb1 = cpu_to_le16(sp->fcport->loop_id);
		mbx->mb10 = cpu_to_le16(BIT_0);
	पूर्ण अन्यथा अणु
		mbx->mb1 = cpu_to_le16((sp->fcport->loop_id << 8) | BIT_0);
	पूर्ण
	mbx->mb2 = cpu_to_le16(MSW(ha->async_pd_dma));
	mbx->mb3 = cpu_to_le16(LSW(ha->async_pd_dma));
	mbx->mb6 = cpu_to_le16(MSW(MSD(ha->async_pd_dma)));
	mbx->mb7 = cpu_to_le16(LSW(MSD(ha->async_pd_dma)));
	mbx->mb9 = cpu_to_le16(sp->vha->vp_idx);
पूर्ण

अटल व्योम
qla24xx_पंचांग_iocb(srb_t *sp, काष्ठा tsk_mgmt_entry *tsk)
अणु
	uपूर्णांक32_t flags;
	uपूर्णांक64_t lun;
	काष्ठा fc_port *fcport = sp->fcport;
	scsi_qla_host_t *vha = fcport->vha;
	काष्ठा qla_hw_data *ha = vha->hw;
	काष्ठा srb_iocb *iocb = &sp->u.iocb_cmd;
	काष्ठा req_que *req = vha->req;

	flags = iocb->u.पंचांगf.flags;
	lun = iocb->u.पंचांगf.lun;

	tsk->entry_type = TSK_MGMT_IOCB_TYPE;
	tsk->entry_count = 1;
	tsk->handle = make_handle(req->id, tsk->handle);
	tsk->nport_handle = cpu_to_le16(fcport->loop_id);
	tsk->समयout = cpu_to_le16(ha->r_a_tov / 10 * 2);
	tsk->control_flags = cpu_to_le32(flags);
	tsk->port_id[0] = fcport->d_id.b.al_pa;
	tsk->port_id[1] = fcport->d_id.b.area;
	tsk->port_id[2] = fcport->d_id.b.करोमुख्य;
	tsk->vp_index = fcport->vha->vp_idx;

	अगर (flags == TCF_LUN_RESET) अणु
		पूर्णांक_to_scsilun(lun, &tsk->lun);
		host_to_fcp_swap((uपूर्णांक8_t *)&tsk->lun,
			माप(tsk->lun));
	पूर्ण
पूर्ण

व्योम qla2x00_init_समयr(srb_t *sp, अचिन्हित दीर्घ पंचांगo)
अणु
	समयr_setup(&sp->u.iocb_cmd.समयr, qla2x00_sp_समयout, 0);
	sp->u.iocb_cmd.समयr.expires = jअगरfies + पंचांगo * HZ;
	sp->मुक्त = qla2x00_sp_मुक्त;
	अगर (IS_QLAFX00(sp->vha->hw) && sp->type == SRB_FXIOCB_DCMD)
		init_completion(&sp->u.iocb_cmd.u.fxiocb.fxiocb_comp);
	sp->start_समयr = 1;
पूर्ण

अटल व्योम qla2x00_els_dcmd_sp_मुक्त(srb_t *sp)
अणु
	काष्ठा srb_iocb *elsio = &sp->u.iocb_cmd;

	kमुक्त(sp->fcport);

	अगर (elsio->u.els_logo.els_logo_pyld)
		dma_मुक्त_coherent(&sp->vha->hw->pdev->dev, DMA_POOL_SIZE,
		    elsio->u.els_logo.els_logo_pyld,
		    elsio->u.els_logo.els_logo_pyld_dma);

	del_समयr(&elsio->समयr);
	qla2x00_rel_sp(sp);
पूर्ण

अटल व्योम
qla2x00_els_dcmd_iocb_समयout(व्योम *data)
अणु
	srb_t *sp = data;
	fc_port_t *fcport = sp->fcport;
	काष्ठा scsi_qla_host *vha = sp->vha;
	काष्ठा srb_iocb *lio = &sp->u.iocb_cmd;
	अचिन्हित दीर्घ flags = 0;
	पूर्णांक res, h;

	ql_dbg(ql_dbg_io, vha, 0x3069,
	    "%s Timeout, hdl=%x, portid=%02x%02x%02x\n",
	    sp->name, sp->handle, fcport->d_id.b.करोमुख्य, fcport->d_id.b.area,
	    fcport->d_id.b.al_pa);

	/* Abort the exchange */
	res = qla24xx_async_पात_cmd(sp, false);
	अगर (res) अणु
		ql_dbg(ql_dbg_io, vha, 0x3070,
		    "mbx abort_command failed.\n");
		spin_lock_irqsave(sp->qpair->qp_lock_ptr, flags);
		क्रम (h = 1; h < sp->qpair->req->num_outstanding_cmds; h++) अणु
			अगर (sp->qpair->req->outstanding_cmds[h] == sp) अणु
				sp->qpair->req->outstanding_cmds[h] = शून्य;
				अवरोध;
			पूर्ण
		पूर्ण
		spin_unlock_irqrestore(sp->qpair->qp_lock_ptr, flags);
		complete(&lio->u.els_logo.comp);
	पूर्ण अन्यथा अणु
		ql_dbg(ql_dbg_io, vha, 0x3071,
		    "mbx abort_command success.\n");
	पूर्ण
पूर्ण

अटल व्योम qla2x00_els_dcmd_sp_करोne(srb_t *sp, पूर्णांक res)
अणु
	fc_port_t *fcport = sp->fcport;
	काष्ठा srb_iocb *lio = &sp->u.iocb_cmd;
	काष्ठा scsi_qla_host *vha = sp->vha;

	ql_dbg(ql_dbg_io, vha, 0x3072,
	    "%s hdl=%x, portid=%02x%02x%02x done\n",
	    sp->name, sp->handle, fcport->d_id.b.करोमुख्य,
	    fcport->d_id.b.area, fcport->d_id.b.al_pa);

	complete(&lio->u.els_logo.comp);
पूर्ण

पूर्णांक
qla24xx_els_dcmd_iocb(scsi_qla_host_t *vha, पूर्णांक els_opcode,
    port_id_t remote_did)
अणु
	srb_t *sp;
	fc_port_t *fcport = शून्य;
	काष्ठा srb_iocb *elsio = शून्य;
	काष्ठा qla_hw_data *ha = vha->hw;
	काष्ठा els_logo_payload logo_pyld;
	पूर्णांक rval = QLA_SUCCESS;

	fcport = qla2x00_alloc_fcport(vha, GFP_KERNEL);
	अगर (!fcport) अणु
	       ql_log(ql_log_info, vha, 0x70e5, "fcport allocation failed\n");
	       वापस -ENOMEM;
	पूर्ण

	/* Alloc SRB काष्ठाure */
	sp = qla2x00_get_sp(vha, fcport, GFP_KERNEL);
	अगर (!sp) अणु
		kमुक्त(fcport);
		ql_log(ql_log_info, vha, 0x70e6,
		 "SRB allocation failed\n");
		वापस -ENOMEM;
	पूर्ण

	elsio = &sp->u.iocb_cmd;
	fcport->loop_id = 0xFFFF;
	fcport->d_id.b.करोमुख्य = remote_did.b.करोमुख्य;
	fcport->d_id.b.area = remote_did.b.area;
	fcport->d_id.b.al_pa = remote_did.b.al_pa;

	ql_dbg(ql_dbg_io, vha, 0x3073, "portid=%02x%02x%02x done\n",
	    fcport->d_id.b.करोमुख्य, fcport->d_id.b.area, fcport->d_id.b.al_pa);

	sp->type = SRB_ELS_DCMD;
	sp->name = "ELS_DCMD";
	sp->fcport = fcport;
	elsio->समयout = qla2x00_els_dcmd_iocb_समयout;
	qla2x00_init_समयr(sp, ELS_DCMD_TIMEOUT);
	init_completion(&sp->u.iocb_cmd.u.els_logo.comp);
	sp->करोne = qla2x00_els_dcmd_sp_करोne;
	sp->मुक्त = qla2x00_els_dcmd_sp_मुक्त;

	elsio->u.els_logo.els_logo_pyld = dma_alloc_coherent(&ha->pdev->dev,
			    DMA_POOL_SIZE, &elsio->u.els_logo.els_logo_pyld_dma,
			    GFP_KERNEL);

	अगर (!elsio->u.els_logo.els_logo_pyld) अणु
		sp->मुक्त(sp);
		वापस QLA_FUNCTION_FAILED;
	पूर्ण

	स_रखो(&logo_pyld, 0, माप(काष्ठा els_logo_payload));

	elsio->u.els_logo.els_cmd = els_opcode;
	logo_pyld.opcode = els_opcode;
	logo_pyld.s_id[0] = vha->d_id.b.al_pa;
	logo_pyld.s_id[1] = vha->d_id.b.area;
	logo_pyld.s_id[2] = vha->d_id.b.करोमुख्य;
	host_to_fcp_swap(logo_pyld.s_id, माप(uपूर्णांक32_t));
	स_नकल(&logo_pyld.wwpn, vha->port_name, WWN_SIZE);

	स_नकल(elsio->u.els_logo.els_logo_pyld, &logo_pyld,
	    माप(काष्ठा els_logo_payload));
	ql_dbg(ql_dbg_disc + ql_dbg_buffer, vha, 0x3075, "LOGO buffer:");
	ql_dump_buffer(ql_dbg_disc + ql_dbg_buffer, vha, 0x010a,
		       elsio->u.els_logo.els_logo_pyld,
		       माप(*elsio->u.els_logo.els_logo_pyld));

	rval = qla2x00_start_sp(sp);
	अगर (rval != QLA_SUCCESS) अणु
		sp->मुक्त(sp);
		वापस QLA_FUNCTION_FAILED;
	पूर्ण

	ql_dbg(ql_dbg_io, vha, 0x3074,
	    "%s LOGO sent, hdl=%x, loopid=%x, portid=%02x%02x%02x.\n",
	    sp->name, sp->handle, fcport->loop_id, fcport->d_id.b.करोमुख्य,
	    fcport->d_id.b.area, fcport->d_id.b.al_pa);

	रुको_क्रम_completion(&elsio->u.els_logo.comp);

	sp->मुक्त(sp);
	वापस rval;
पूर्ण

अटल व्योम
qla24xx_els_logo_iocb(srb_t *sp, काष्ठा els_entry_24xx *els_iocb)
अणु
	scsi_qla_host_t *vha = sp->vha;
	काष्ठा srb_iocb *elsio = &sp->u.iocb_cmd;

	els_iocb->entry_type = ELS_IOCB_TYPE;
	els_iocb->entry_count = 1;
	els_iocb->sys_define = 0;
	els_iocb->entry_status = 0;
	els_iocb->handle = sp->handle;
	els_iocb->nport_handle = cpu_to_le16(sp->fcport->loop_id);
	els_iocb->tx_dsd_count = cpu_to_le16(1);
	els_iocb->vp_index = vha->vp_idx;
	els_iocb->sof_type = EST_SOFI3;
	els_iocb->rx_dsd_count = 0;
	els_iocb->opcode = elsio->u.els_logo.els_cmd;

	els_iocb->d_id[0] = sp->fcport->d_id.b.al_pa;
	els_iocb->d_id[1] = sp->fcport->d_id.b.area;
	els_iocb->d_id[2] = sp->fcport->d_id.b.करोमुख्य;
	/* For SID the byte order is dअगरferent than DID */
	els_iocb->s_id[1] = vha->d_id.b.al_pa;
	els_iocb->s_id[2] = vha->d_id.b.area;
	els_iocb->s_id[0] = vha->d_id.b.करोमुख्य;

	अगर (elsio->u.els_logo.els_cmd == ELS_DCMD_PLOGI) अणु
		els_iocb->control_flags = 0;
		els_iocb->tx_byte_count = els_iocb->tx_len =
			cpu_to_le32(माप(काष्ठा els_plogi_payload));
		put_unaligned_le64(elsio->u.els_plogi.els_plogi_pyld_dma,
				   &els_iocb->tx_address);
		els_iocb->rx_dsd_count = cpu_to_le16(1);
		els_iocb->rx_byte_count = els_iocb->rx_len =
			cpu_to_le32(माप(काष्ठा els_plogi_payload));
		put_unaligned_le64(elsio->u.els_plogi.els_resp_pyld_dma,
				   &els_iocb->rx_address);

		ql_dbg(ql_dbg_io + ql_dbg_buffer, vha, 0x3073,
		    "PLOGI ELS IOCB:\n");
		ql_dump_buffer(ql_log_info, vha, 0x0109,
		    (uपूर्णांक8_t *)els_iocb,
		    माप(*els_iocb));
	पूर्ण अन्यथा अणु
		els_iocb->control_flags = cpu_to_le16(1 << 13);
		els_iocb->tx_byte_count =
			cpu_to_le32(माप(काष्ठा els_logo_payload));
		put_unaligned_le64(elsio->u.els_logo.els_logo_pyld_dma,
				   &els_iocb->tx_address);
		els_iocb->tx_len = cpu_to_le32(माप(काष्ठा els_logo_payload));

		els_iocb->rx_byte_count = 0;
		els_iocb->rx_address = 0;
		els_iocb->rx_len = 0;
		ql_dbg(ql_dbg_io + ql_dbg_buffer, vha, 0x3076,
		       "LOGO ELS IOCB:");
		ql_dump_buffer(ql_log_info, vha, 0x010b,
			       els_iocb,
			       माप(*els_iocb));
	पूर्ण

	sp->vha->qla_stats.control_requests++;
पूर्ण

अटल व्योम
qla2x00_els_dcmd2_iocb_समयout(व्योम *data)
अणु
	srb_t *sp = data;
	fc_port_t *fcport = sp->fcport;
	काष्ठा scsi_qla_host *vha = sp->vha;
	अचिन्हित दीर्घ flags = 0;
	पूर्णांक res, h;

	ql_dbg(ql_dbg_io + ql_dbg_disc, vha, 0x3069,
	    "%s hdl=%x ELS Timeout, %8phC portid=%06x\n",
	    sp->name, sp->handle, fcport->port_name, fcport->d_id.b24);

	/* Abort the exchange */
	res = qla24xx_async_पात_cmd(sp, false);
	ql_dbg(ql_dbg_io, vha, 0x3070,
	    "mbx abort_command %s\n",
	    (res == QLA_SUCCESS) ? "successful" : "failed");
	अगर (res) अणु
		spin_lock_irqsave(sp->qpair->qp_lock_ptr, flags);
		क्रम (h = 1; h < sp->qpair->req->num_outstanding_cmds; h++) अणु
			अगर (sp->qpair->req->outstanding_cmds[h] == sp) अणु
				sp->qpair->req->outstanding_cmds[h] = शून्य;
				अवरोध;
			पूर्ण
		पूर्ण
		spin_unlock_irqrestore(sp->qpair->qp_lock_ptr, flags);
		sp->करोne(sp, QLA_FUNCTION_TIMEOUT);
	पूर्ण
पूर्ण

व्योम qla2x00_els_dcmd2_मुक्त(scsi_qla_host_t *vha, काष्ठा els_plogi *els_plogi)
अणु
	अगर (els_plogi->els_plogi_pyld)
		dma_मुक्त_coherent(&vha->hw->pdev->dev,
				  els_plogi->tx_size,
				  els_plogi->els_plogi_pyld,
				  els_plogi->els_plogi_pyld_dma);

	अगर (els_plogi->els_resp_pyld)
		dma_मुक्त_coherent(&vha->hw->pdev->dev,
				  els_plogi->rx_size,
				  els_plogi->els_resp_pyld,
				  els_plogi->els_resp_pyld_dma);
पूर्ण

अटल व्योम qla2x00_els_dcmd2_sp_करोne(srb_t *sp, पूर्णांक res)
अणु
	fc_port_t *fcport = sp->fcport;
	काष्ठा srb_iocb *lio = &sp->u.iocb_cmd;
	काष्ठा scsi_qla_host *vha = sp->vha;
	काष्ठा event_arg ea;
	काष्ठा qla_work_evt *e;
	काष्ठा fc_port *conflict_fcport;
	port_id_t cid;	/* conflict Nport id */
	स्थिर __le32 *fw_status = sp->u.iocb_cmd.u.els_plogi.fw_status;
	u16 lid;

	ql_dbg(ql_dbg_disc, vha, 0x3072,
	    "%s ELS done rc %d hdl=%x, portid=%06x %8phC\n",
	    sp->name, res, sp->handle, fcport->d_id.b24, fcport->port_name);

	fcport->flags &= ~(FCF_ASYNC_SENT|FCF_ASYNC_ACTIVE);
	del_समयr(&sp->u.iocb_cmd.समयr);

	अगर (sp->flags & SRB_WAKEUP_ON_COMP)
		complete(&lio->u.els_plogi.comp);
	अन्यथा अणु
		चयन (le32_to_cpu(fw_status[0])) अणु
		हाल CS_DATA_UNDERRUN:
		हाल CS_COMPLETE:
			स_रखो(&ea, 0, माप(ea));
			ea.fcport = fcport;
			ea.rc = res;
			qla_handle_els_plogi_करोne(vha, &ea);
			अवरोध;

		हाल CS_IOCB_ERROR:
			चयन (le32_to_cpu(fw_status[1])) अणु
			हाल LSC_SCODE_PORTID_USED:
				lid = le32_to_cpu(fw_status[2]) & 0xffff;
				qlt_find_sess_invalidate_other(vha,
				    wwn_to_u64(fcport->port_name),
				    fcport->d_id, lid, &conflict_fcport);
				अगर (conflict_fcport) अणु
					/*
					 * Another fcport shares the same
					 * loop_id & nport id; conflict
					 * fcport needs to finish cleanup
					 * beक्रमe this fcport can proceed
					 * to login.
					 */
					conflict_fcport->conflict = fcport;
					fcport->login_छोड़ो = 1;
					ql_dbg(ql_dbg_disc, vha, 0x20ed,
					    "%s %d %8phC pid %06x inuse with lid %#x post gidpn\n",
					    __func__, __LINE__,
					    fcport->port_name,
					    fcport->d_id.b24, lid);
				पूर्ण अन्यथा अणु
					ql_dbg(ql_dbg_disc, vha, 0x20ed,
					    "%s %d %8phC pid %06x inuse with lid %#x sched del\n",
					    __func__, __LINE__,
					    fcport->port_name,
					    fcport->d_id.b24, lid);
					qla2x00_clear_loop_id(fcport);
					set_bit(lid, vha->hw->loop_id_map);
					fcport->loop_id = lid;
					fcport->keep_nport_handle = 0;
					qlt_schedule_sess_क्रम_deletion(fcport);
				पूर्ण
				अवरोध;

			हाल LSC_SCODE_NPORT_USED:
				cid.b.करोमुख्य = (le32_to_cpu(fw_status[2]) >> 16)
					& 0xff;
				cid.b.area   = (le32_to_cpu(fw_status[2]) >>  8)
					& 0xff;
				cid.b.al_pa  = le32_to_cpu(fw_status[2]) & 0xff;
				cid.b.rsvd_1 = 0;

				ql_dbg(ql_dbg_disc, vha, 0x20ec,
				    "%s %d %8phC lid %#x in use with pid %06x post gnl\n",
				    __func__, __LINE__, fcport->port_name,
				    fcport->loop_id, cid.b24);
				set_bit(fcport->loop_id,
				    vha->hw->loop_id_map);
				fcport->loop_id = FC_NO_LOOP_ID;
				qla24xx_post_gnl_work(vha, fcport);
				अवरोध;

			हाल LSC_SCODE_NOXCB:
				vha->hw->exch_starvation++;
				अगर (vha->hw->exch_starvation > 5) अणु
					ql_log(ql_log_warn, vha, 0xd046,
					    "Exchange starvation. Resetting RISC\n");
					vha->hw->exch_starvation = 0;
					set_bit(ISP_ABORT_NEEDED,
					    &vha->dpc_flags);
					qla2xxx_wake_dpc(vha);
				पूर्ण
				fallthrough;
			शेष:
				ql_dbg(ql_dbg_disc, vha, 0x20eb,
				    "%s %8phC cmd error fw_status 0x%x 0x%x 0x%x\n",
				    __func__, sp->fcport->port_name,
				    fw_status[0], fw_status[1], fw_status[2]);

				fcport->flags &= ~FCF_ASYNC_SENT;
				qla2x00_set_fcport_disc_state(fcport,
				    DSC_LOGIN_FAILED);
				set_bit(RELOGIN_NEEDED, &vha->dpc_flags);
				अवरोध;
			पूर्ण
			अवरोध;

		शेष:
			ql_dbg(ql_dbg_disc, vha, 0x20eb,
			    "%s %8phC cmd error 2 fw_status 0x%x 0x%x 0x%x\n",
			    __func__, sp->fcport->port_name,
			    fw_status[0], fw_status[1], fw_status[2]);

			sp->fcport->flags &= ~FCF_ASYNC_SENT;
			qla2x00_set_fcport_disc_state(fcport, DSC_LOGIN_FAILED);
			set_bit(RELOGIN_NEEDED, &vha->dpc_flags);
			अवरोध;
		पूर्ण

		e = qla2x00_alloc_work(vha, QLA_EVT_UNMAP);
		अगर (!e) अणु
			काष्ठा srb_iocb *elsio = &sp->u.iocb_cmd;

			qla2x00_els_dcmd2_मुक्त(vha, &elsio->u.els_plogi);
			sp->मुक्त(sp);
			वापस;
		पूर्ण
		e->u.iosb.sp = sp;
		qla2x00_post_work(vha, e);
	पूर्ण
पूर्ण

पूर्णांक
qla24xx_els_dcmd2_iocb(scsi_qla_host_t *vha, पूर्णांक els_opcode,
    fc_port_t *fcport, bool रुको)
अणु
	srb_t *sp;
	काष्ठा srb_iocb *elsio = शून्य;
	काष्ठा qla_hw_data *ha = vha->hw;
	पूर्णांक rval = QLA_SUCCESS;
	व्योम	*ptr, *resp_ptr;

	/* Alloc SRB काष्ठाure */
	sp = qla2x00_get_sp(vha, fcport, GFP_KERNEL);
	अगर (!sp) अणु
		ql_log(ql_log_info, vha, 0x70e6,
		 "SRB allocation failed\n");
		fcport->flags &= ~FCF_ASYNC_ACTIVE;
		वापस -ENOMEM;
	पूर्ण

	fcport->flags |= FCF_ASYNC_SENT;
	qla2x00_set_fcport_disc_state(fcport, DSC_LOGIN_PEND);
	elsio = &sp->u.iocb_cmd;
	ql_dbg(ql_dbg_io, vha, 0x3073,
	    "Enter: PLOGI portid=%06x\n", fcport->d_id.b24);

	sp->type = SRB_ELS_DCMD;
	sp->name = "ELS_DCMD";
	sp->fcport = fcport;

	elsio->समयout = qla2x00_els_dcmd2_iocb_समयout;
	अगर (रुको)
		sp->flags = SRB_WAKEUP_ON_COMP;

	qla2x00_init_समयr(sp, ELS_DCMD_TIMEOUT + 2);

	sp->करोne = qla2x00_els_dcmd2_sp_करोne;
	elsio->u.els_plogi.tx_size = elsio->u.els_plogi.rx_size = DMA_POOL_SIZE;

	ptr = elsio->u.els_plogi.els_plogi_pyld =
	    dma_alloc_coherent(&ha->pdev->dev, elsio->u.els_plogi.tx_size,
		&elsio->u.els_plogi.els_plogi_pyld_dma, GFP_KERNEL);

	अगर (!elsio->u.els_plogi.els_plogi_pyld) अणु
		rval = QLA_FUNCTION_FAILED;
		जाओ out;
	पूर्ण

	resp_ptr = elsio->u.els_plogi.els_resp_pyld =
	    dma_alloc_coherent(&ha->pdev->dev, elsio->u.els_plogi.rx_size,
		&elsio->u.els_plogi.els_resp_pyld_dma, GFP_KERNEL);

	अगर (!elsio->u.els_plogi.els_resp_pyld) अणु
		rval = QLA_FUNCTION_FAILED;
		जाओ out;
	पूर्ण

	ql_dbg(ql_dbg_io, vha, 0x3073, "PLOGI %p %p\n", ptr, resp_ptr);

	स_रखो(ptr, 0, माप(काष्ठा els_plogi_payload));
	स_रखो(resp_ptr, 0, माप(काष्ठा els_plogi_payload));
	स_नकल(elsio->u.els_plogi.els_plogi_pyld->data,
	    &ha->plogi_els_payld.fl_csp, LOGIN_TEMPLATE_SIZE);

	elsio->u.els_plogi.els_cmd = els_opcode;
	elsio->u.els_plogi.els_plogi_pyld->opcode = els_opcode;

	ql_dbg(ql_dbg_disc + ql_dbg_buffer, vha, 0x3073, "PLOGI buffer:\n");
	ql_dump_buffer(ql_dbg_disc + ql_dbg_buffer, vha, 0x0109,
	    (uपूर्णांक8_t *)elsio->u.els_plogi.els_plogi_pyld,
	    माप(*elsio->u.els_plogi.els_plogi_pyld));

	init_completion(&elsio->u.els_plogi.comp);
	rval = qla2x00_start_sp(sp);
	अगर (rval != QLA_SUCCESS) अणु
		rval = QLA_FUNCTION_FAILED;
	पूर्ण अन्यथा अणु
		ql_dbg(ql_dbg_disc, vha, 0x3074,
		    "%s PLOGI sent, hdl=%x, loopid=%x, to port_id %06x from port_id %06x\n",
		    sp->name, sp->handle, fcport->loop_id,
		    fcport->d_id.b24, vha->d_id.b24);
	पूर्ण

	अगर (रुको) अणु
		रुको_क्रम_completion(&elsio->u.els_plogi.comp);

		अगर (elsio->u.els_plogi.comp_status != CS_COMPLETE)
			rval = QLA_FUNCTION_FAILED;
	पूर्ण अन्यथा अणु
		जाओ करोne;
	पूर्ण

out:
	fcport->flags &= ~(FCF_ASYNC_SENT | FCF_ASYNC_ACTIVE);
	qla2x00_els_dcmd2_मुक्त(vha, &elsio->u.els_plogi);
	sp->मुक्त(sp);
करोne:
	वापस rval;
पूर्ण

अटल व्योम
qla24xx_els_iocb(srb_t *sp, काष्ठा els_entry_24xx *els_iocb)
अणु
	काष्ठा bsg_job *bsg_job = sp->u.bsg_job;
	काष्ठा fc_bsg_request *bsg_request = bsg_job->request;

        els_iocb->entry_type = ELS_IOCB_TYPE;
        els_iocb->entry_count = 1;
        els_iocb->sys_define = 0;
        els_iocb->entry_status = 0;
        els_iocb->handle = sp->handle;
	els_iocb->nport_handle = cpu_to_le16(sp->fcport->loop_id);
	els_iocb->tx_dsd_count = cpu_to_le16(bsg_job->request_payload.sg_cnt);
	els_iocb->vp_index = sp->vha->vp_idx;
        els_iocb->sof_type = EST_SOFI3;
	els_iocb->rx_dsd_count = cpu_to_le16(bsg_job->reply_payload.sg_cnt);

	els_iocb->opcode =
	    sp->type == SRB_ELS_CMD_RPT ?
	    bsg_request->rqst_data.r_els.els_code :
	    bsg_request->rqst_data.h_els.command_code;
	els_iocb->d_id[0] = sp->fcport->d_id.b.al_pa;
	els_iocb->d_id[1] = sp->fcport->d_id.b.area;
	els_iocb->d_id[2] = sp->fcport->d_id.b.करोमुख्य;
        els_iocb->control_flags = 0;
        els_iocb->rx_byte_count =
            cpu_to_le32(bsg_job->reply_payload.payload_len);
        els_iocb->tx_byte_count =
            cpu_to_le32(bsg_job->request_payload.payload_len);

	put_unaligned_le64(sg_dma_address(bsg_job->request_payload.sg_list),
			   &els_iocb->tx_address);
        els_iocb->tx_len = cpu_to_le32(sg_dma_len
            (bsg_job->request_payload.sg_list));

	put_unaligned_le64(sg_dma_address(bsg_job->reply_payload.sg_list),
			   &els_iocb->rx_address);
        els_iocb->rx_len = cpu_to_le32(sg_dma_len
            (bsg_job->reply_payload.sg_list));

	sp->vha->qla_stats.control_requests++;
पूर्ण

अटल व्योम
qla2x00_ct_iocb(srb_t *sp, ms_iocb_entry_t *ct_iocb)
अणु
	uपूर्णांक16_t        avail_dsds;
	काष्ठा dsd64	*cur_dsd;
	काष्ठा scatterlist *sg;
	पूर्णांक index;
	uपूर्णांक16_t tot_dsds;
	scsi_qla_host_t *vha = sp->vha;
	काष्ठा qla_hw_data *ha = vha->hw;
	काष्ठा bsg_job *bsg_job = sp->u.bsg_job;
	पूर्णांक entry_count = 1;

	स_रखो(ct_iocb, 0, माप(ms_iocb_entry_t));
	ct_iocb->entry_type = CT_IOCB_TYPE;
	ct_iocb->entry_status = 0;
	ct_iocb->handle1 = sp->handle;
	SET_TARGET_ID(ha, ct_iocb->loop_id, sp->fcport->loop_id);
	ct_iocb->status = cpu_to_le16(0);
	ct_iocb->control_flags = cpu_to_le16(0);
	ct_iocb->समयout = 0;
	ct_iocb->cmd_dsd_count =
	    cpu_to_le16(bsg_job->request_payload.sg_cnt);
	ct_iocb->total_dsd_count =
	    cpu_to_le16(bsg_job->request_payload.sg_cnt + 1);
	ct_iocb->req_bytecount =
	    cpu_to_le32(bsg_job->request_payload.payload_len);
	ct_iocb->rsp_bytecount =
	    cpu_to_le32(bsg_job->reply_payload.payload_len);

	put_unaligned_le64(sg_dma_address(bsg_job->request_payload.sg_list),
			   &ct_iocb->req_dsd.address);
	ct_iocb->req_dsd.length = ct_iocb->req_bytecount;

	put_unaligned_le64(sg_dma_address(bsg_job->reply_payload.sg_list),
			   &ct_iocb->rsp_dsd.address);
	ct_iocb->rsp_dsd.length = ct_iocb->rsp_bytecount;

	avail_dsds = 1;
	cur_dsd = &ct_iocb->rsp_dsd;
	index = 0;
	tot_dsds = bsg_job->reply_payload.sg_cnt;

	क्रम_each_sg(bsg_job->reply_payload.sg_list, sg, tot_dsds, index) अणु
		cont_a64_entry_t *cont_pkt;

		/* Allocate additional continuation packets? */
		अगर (avail_dsds == 0) अणु
			/*
			* Five DSDs are available in the Cont.
			* Type 1 IOCB.
			       */
			cont_pkt = qla2x00_prep_cont_type1_iocb(vha,
			    vha->hw->req_q_map[0]);
			cur_dsd = cont_pkt->dsd;
			avail_dsds = 5;
			entry_count++;
		पूर्ण

		append_dsd64(&cur_dsd, sg);
		avail_dsds--;
	पूर्ण
	ct_iocb->entry_count = entry_count;

	sp->vha->qla_stats.control_requests++;
पूर्ण

अटल व्योम
qla24xx_ct_iocb(srb_t *sp, काष्ठा ct_entry_24xx *ct_iocb)
अणु
	uपूर्णांक16_t        avail_dsds;
	काष्ठा dsd64	*cur_dsd;
	काष्ठा scatterlist *sg;
	पूर्णांक index;
	uपूर्णांक16_t cmd_dsds, rsp_dsds;
	scsi_qla_host_t *vha = sp->vha;
	काष्ठा qla_hw_data *ha = vha->hw;
	काष्ठा bsg_job *bsg_job = sp->u.bsg_job;
	पूर्णांक entry_count = 1;
	cont_a64_entry_t *cont_pkt = शून्य;

	ct_iocb->entry_type = CT_IOCB_TYPE;
        ct_iocb->entry_status = 0;
        ct_iocb->sys_define = 0;
        ct_iocb->handle = sp->handle;

	ct_iocb->nport_handle = cpu_to_le16(sp->fcport->loop_id);
	ct_iocb->vp_index = sp->vha->vp_idx;
	ct_iocb->comp_status = cpu_to_le16(0);

	cmd_dsds = bsg_job->request_payload.sg_cnt;
	rsp_dsds = bsg_job->reply_payload.sg_cnt;

	ct_iocb->cmd_dsd_count = cpu_to_le16(cmd_dsds);
        ct_iocb->समयout = 0;
	ct_iocb->rsp_dsd_count = cpu_to_le16(rsp_dsds);
        ct_iocb->cmd_byte_count =
            cpu_to_le32(bsg_job->request_payload.payload_len);

	avail_dsds = 2;
	cur_dsd = ct_iocb->dsd;
	index = 0;

	क्रम_each_sg(bsg_job->request_payload.sg_list, sg, cmd_dsds, index) अणु
		/* Allocate additional continuation packets? */
		अगर (avail_dsds == 0) अणु
			/*
			 * Five DSDs are available in the Cont.
			 * Type 1 IOCB.
			 */
			cont_pkt = qla2x00_prep_cont_type1_iocb(
			    vha, ha->req_q_map[0]);
			cur_dsd = cont_pkt->dsd;
			avail_dsds = 5;
			entry_count++;
		पूर्ण

		append_dsd64(&cur_dsd, sg);
		avail_dsds--;
	पूर्ण

	index = 0;

	क्रम_each_sg(bsg_job->reply_payload.sg_list, sg, rsp_dsds, index) अणु
		/* Allocate additional continuation packets? */
		अगर (avail_dsds == 0) अणु
			/*
			* Five DSDs are available in the Cont.
			* Type 1 IOCB.
			       */
			cont_pkt = qla2x00_prep_cont_type1_iocb(vha,
			    ha->req_q_map[0]);
			cur_dsd = cont_pkt->dsd;
			avail_dsds = 5;
			entry_count++;
		पूर्ण

		append_dsd64(&cur_dsd, sg);
		avail_dsds--;
	पूर्ण
        ct_iocb->entry_count = entry_count;
पूर्ण

/*
 * qla82xx_start_scsi() - Send a SCSI command to the ISP
 * @sp: command to send to the ISP
 *
 * Returns non-zero अगर a failure occurred, अन्यथा zero.
 */
पूर्णांक
qla82xx_start_scsi(srb_t *sp)
अणु
	पूर्णांक		nseg;
	अचिन्हित दीर्घ   flags;
	काष्ठा scsi_cmnd *cmd;
	uपूर्णांक32_t	*clr_ptr;
	uपूर्णांक32_t	handle;
	uपूर्णांक16_t	cnt;
	uपूर्णांक16_t	req_cnt;
	uपूर्णांक16_t	tot_dsds;
	काष्ठा device_reg_82xx __iomem *reg;
	uपूर्णांक32_t dbval;
	__be32 *fcp_dl;
	uपूर्णांक8_t additional_cdb_len;
	काष्ठा ct6_dsd *ctx;
	काष्ठा scsi_qla_host *vha = sp->vha;
	काष्ठा qla_hw_data *ha = vha->hw;
	काष्ठा req_que *req = शून्य;
	काष्ठा rsp_que *rsp = शून्य;

	/* Setup device poपूर्णांकers. */
	reg = &ha->iobase->isp82;
	cmd = GET_CMD_SP(sp);
	req = vha->req;
	rsp = ha->rsp_q_map[0];

	/* So we know we haven't pci_map'ed anything yet */
	tot_dsds = 0;

	dbval = 0x04 | (ha->portnum << 5);

	/* Send marker अगर required */
	अगर (vha->marker_needed != 0) अणु
		अगर (qla2x00_marker(vha, ha->base_qpair,
			0, 0, MK_SYNC_ALL) != QLA_SUCCESS) अणु
			ql_log(ql_log_warn, vha, 0x300c,
			    "qla2x00_marker failed for cmd=%p.\n", cmd);
			वापस QLA_FUNCTION_FAILED;
		पूर्ण
		vha->marker_needed = 0;
	पूर्ण

	/* Acquire ring specअगरic lock */
	spin_lock_irqsave(&ha->hardware_lock, flags);

	handle = qla2xxx_get_next_handle(req);
	अगर (handle == 0)
		जाओ queuing_error;

	/* Map the sg table so we have an accurate count of sg entries needed */
	अगर (scsi_sg_count(cmd)) अणु
		nseg = dma_map_sg(&ha->pdev->dev, scsi_sglist(cmd),
		    scsi_sg_count(cmd), cmd->sc_data_direction);
		अगर (unlikely(!nseg))
			जाओ queuing_error;
	पूर्ण अन्यथा
		nseg = 0;

	tot_dsds = nseg;

	अगर (tot_dsds > ql2xshअगरtctondsd) अणु
		काष्ठा cmd_type_6 *cmd_pkt;
		uपूर्णांक16_t more_dsd_lists = 0;
		काष्ठा dsd_dma *dsd_ptr;
		uपूर्णांक16_t i;

		more_dsd_lists = qla24xx_calc_dsd_lists(tot_dsds);
		अगर ((more_dsd_lists + ha->gbl_dsd_inuse) >= NUM_DSD_CHAIN) अणु
			ql_dbg(ql_dbg_io, vha, 0x300d,
			    "Num of DSD list %d is than %d for cmd=%p.\n",
			    more_dsd_lists + ha->gbl_dsd_inuse, NUM_DSD_CHAIN,
			    cmd);
			जाओ queuing_error;
		पूर्ण

		अगर (more_dsd_lists <= ha->gbl_dsd_avail)
			जाओ sufficient_dsds;
		अन्यथा
			more_dsd_lists -= ha->gbl_dsd_avail;

		क्रम (i = 0; i < more_dsd_lists; i++) अणु
			dsd_ptr = kzalloc(माप(काष्ठा dsd_dma), GFP_ATOMIC);
			अगर (!dsd_ptr) अणु
				ql_log(ql_log_fatal, vha, 0x300e,
				    "Failed to allocate memory for dsd_dma "
				    "for cmd=%p.\n", cmd);
				जाओ queuing_error;
			पूर्ण

			dsd_ptr->dsd_addr = dma_pool_alloc(ha->dl_dma_pool,
				GFP_ATOMIC, &dsd_ptr->dsd_list_dma);
			अगर (!dsd_ptr->dsd_addr) अणु
				kमुक्त(dsd_ptr);
				ql_log(ql_log_fatal, vha, 0x300f,
				    "Failed to allocate memory for dsd_addr "
				    "for cmd=%p.\n", cmd);
				जाओ queuing_error;
			पूर्ण
			list_add_tail(&dsd_ptr->list, &ha->gbl_dsd_list);
			ha->gbl_dsd_avail++;
		पूर्ण

sufficient_dsds:
		req_cnt = 1;

		अगर (req->cnt < (req_cnt + 2)) अणु
			cnt = (uपूर्णांक16_t)rd_reg_dword_relaxed(
				&reg->req_q_out[0]);
			अगर (req->ring_index < cnt)
				req->cnt = cnt - req->ring_index;
			अन्यथा
				req->cnt = req->length -
					(req->ring_index - cnt);
			अगर (req->cnt < (req_cnt + 2))
				जाओ queuing_error;
		पूर्ण

		ctx = sp->u.scmd.ct6_ctx =
		    mempool_alloc(ha->ctx_mempool, GFP_ATOMIC);
		अगर (!ctx) अणु
			ql_log(ql_log_fatal, vha, 0x3010,
			    "Failed to allocate ctx for cmd=%p.\n", cmd);
			जाओ queuing_error;
		पूर्ण

		स_रखो(ctx, 0, माप(काष्ठा ct6_dsd));
		ctx->fcp_cmnd = dma_pool_zalloc(ha->fcp_cmnd_dma_pool,
			GFP_ATOMIC, &ctx->fcp_cmnd_dma);
		अगर (!ctx->fcp_cmnd) अणु
			ql_log(ql_log_fatal, vha, 0x3011,
			    "Failed to allocate fcp_cmnd for cmd=%p.\n", cmd);
			जाओ queuing_error;
		पूर्ण

		/* Initialize the DSD list and dma handle */
		INIT_LIST_HEAD(&ctx->dsd_list);
		ctx->dsd_use_cnt = 0;

		अगर (cmd->cmd_len > 16) अणु
			additional_cdb_len = cmd->cmd_len - 16;
			अगर ((cmd->cmd_len % 4) != 0) अणु
				/* SCSI command bigger than 16 bytes must be
				 * multiple of 4
				 */
				ql_log(ql_log_warn, vha, 0x3012,
				    "scsi cmd len %d not multiple of 4 "
				    "for cmd=%p.\n", cmd->cmd_len, cmd);
				जाओ queuing_error_fcp_cmnd;
			पूर्ण
			ctx->fcp_cmnd_len = 12 + cmd->cmd_len + 4;
		पूर्ण अन्यथा अणु
			additional_cdb_len = 0;
			ctx->fcp_cmnd_len = 12 + 16 + 4;
		पूर्ण

		cmd_pkt = (काष्ठा cmd_type_6 *)req->ring_ptr;
		cmd_pkt->handle = make_handle(req->id, handle);

		/* Zero out reमुख्यing portion of packet. */
		/*    tagged queuing modअगरier -- शेष is TSK_SIMPLE (0). */
		clr_ptr = (uपूर्णांक32_t *)cmd_pkt + 2;
		स_रखो(clr_ptr, 0, REQUEST_ENTRY_SIZE - 8);
		cmd_pkt->dseg_count = cpu_to_le16(tot_dsds);

		/* Set NPORT-ID and LUN number*/
		cmd_pkt->nport_handle = cpu_to_le16(sp->fcport->loop_id);
		cmd_pkt->port_id[0] = sp->fcport->d_id.b.al_pa;
		cmd_pkt->port_id[1] = sp->fcport->d_id.b.area;
		cmd_pkt->port_id[2] = sp->fcport->d_id.b.करोमुख्य;
		cmd_pkt->vp_index = sp->vha->vp_idx;

		/* Build IOCB segments */
		अगर (qla24xx_build_scsi_type_6_iocbs(sp, cmd_pkt, tot_dsds))
			जाओ queuing_error_fcp_cmnd;

		पूर्णांक_to_scsilun(cmd->device->lun, &cmd_pkt->lun);
		host_to_fcp_swap((uपूर्णांक8_t *)&cmd_pkt->lun, माप(cmd_pkt->lun));

		/* build FCP_CMND IU */
		पूर्णांक_to_scsilun(cmd->device->lun, &ctx->fcp_cmnd->lun);
		ctx->fcp_cmnd->additional_cdb_len = additional_cdb_len;

		अगर (cmd->sc_data_direction == DMA_TO_DEVICE)
			ctx->fcp_cmnd->additional_cdb_len |= 1;
		अन्यथा अगर (cmd->sc_data_direction == DMA_FROM_DEVICE)
			ctx->fcp_cmnd->additional_cdb_len |= 2;

		/* Populate the FCP_PRIO. */
		अगर (ha->flags.fcp_prio_enabled)
			ctx->fcp_cmnd->task_attribute |=
			    sp->fcport->fcp_prio << 3;

		स_नकल(ctx->fcp_cmnd->cdb, cmd->cmnd, cmd->cmd_len);

		fcp_dl = (__be32 *)(ctx->fcp_cmnd->cdb + 16 +
		    additional_cdb_len);
		*fcp_dl = htonl((uपूर्णांक32_t)scsi_bufflen(cmd));

		cmd_pkt->fcp_cmnd_dseg_len = cpu_to_le16(ctx->fcp_cmnd_len);
		put_unaligned_le64(ctx->fcp_cmnd_dma,
				   &cmd_pkt->fcp_cmnd_dseg_address);

		sp->flags |= SRB_FCP_CMND_DMA_VALID;
		cmd_pkt->byte_count = cpu_to_le32((uपूर्णांक32_t)scsi_bufflen(cmd));
		/* Set total data segment count. */
		cmd_pkt->entry_count = (uपूर्णांक8_t)req_cnt;
		/* Specअगरy response queue number where
		 * completion should happen
		 */
		cmd_pkt->entry_status = (uपूर्णांक8_t) rsp->id;
	पूर्ण अन्यथा अणु
		काष्ठा cmd_type_7 *cmd_pkt;

		req_cnt = qla24xx_calc_iocbs(vha, tot_dsds);
		अगर (req->cnt < (req_cnt + 2)) अणु
			cnt = (uपूर्णांक16_t)rd_reg_dword_relaxed(
			    &reg->req_q_out[0]);
			अगर (req->ring_index < cnt)
				req->cnt = cnt - req->ring_index;
			अन्यथा
				req->cnt = req->length -
					(req->ring_index - cnt);
		पूर्ण
		अगर (req->cnt < (req_cnt + 2))
			जाओ queuing_error;

		cmd_pkt = (काष्ठा cmd_type_7 *)req->ring_ptr;
		cmd_pkt->handle = make_handle(req->id, handle);

		/* Zero out reमुख्यing portion of packet. */
		/* tagged queuing modअगरier -- शेष is TSK_SIMPLE (0).*/
		clr_ptr = (uपूर्णांक32_t *)cmd_pkt + 2;
		स_रखो(clr_ptr, 0, REQUEST_ENTRY_SIZE - 8);
		cmd_pkt->dseg_count = cpu_to_le16(tot_dsds);

		/* Set NPORT-ID and LUN number*/
		cmd_pkt->nport_handle = cpu_to_le16(sp->fcport->loop_id);
		cmd_pkt->port_id[0] = sp->fcport->d_id.b.al_pa;
		cmd_pkt->port_id[1] = sp->fcport->d_id.b.area;
		cmd_pkt->port_id[2] = sp->fcport->d_id.b.करोमुख्य;
		cmd_pkt->vp_index = sp->vha->vp_idx;

		पूर्णांक_to_scsilun(cmd->device->lun, &cmd_pkt->lun);
		host_to_fcp_swap((uपूर्णांक8_t *)&cmd_pkt->lun,
		    माप(cmd_pkt->lun));

		/* Populate the FCP_PRIO. */
		अगर (ha->flags.fcp_prio_enabled)
			cmd_pkt->task |= sp->fcport->fcp_prio << 3;

		/* Load SCSI command packet. */
		स_नकल(cmd_pkt->fcp_cdb, cmd->cmnd, cmd->cmd_len);
		host_to_fcp_swap(cmd_pkt->fcp_cdb, माप(cmd_pkt->fcp_cdb));

		cmd_pkt->byte_count = cpu_to_le32((uपूर्णांक32_t)scsi_bufflen(cmd));

		/* Build IOCB segments */
		qla24xx_build_scsi_iocbs(sp, cmd_pkt, tot_dsds, req);

		/* Set total data segment count. */
		cmd_pkt->entry_count = (uपूर्णांक8_t)req_cnt;
		/* Specअगरy response queue number where
		 * completion should happen.
		 */
		cmd_pkt->entry_status = (uपूर्णांक8_t) rsp->id;

	पूर्ण
	/* Build command packet. */
	req->current_outstanding_cmd = handle;
	req->outstanding_cmds[handle] = sp;
	sp->handle = handle;
	cmd->host_scribble = (अचिन्हित अक्षर *)(अचिन्हित दीर्घ)handle;
	req->cnt -= req_cnt;
	wmb();

	/* Adjust ring index. */
	req->ring_index++;
	अगर (req->ring_index == req->length) अणु
		req->ring_index = 0;
		req->ring_ptr = req->ring;
	पूर्ण अन्यथा
		req->ring_ptr++;

	sp->flags |= SRB_DMA_VALID;

	/* Set chip new ring index. */
	/* ग_लिखो, पढ़ो and verअगरy logic */
	dbval = dbval | (req->id << 8) | (req->ring_index << 16);
	अगर (ql2xdbwr)
		qla82xx_wr_32(ha, (uपूर्णांकptr_t __क्रमce)ha->nxdb_wr_ptr, dbval);
	अन्यथा अणु
		wrt_reg_dword(ha->nxdb_wr_ptr, dbval);
		wmb();
		जबतक (rd_reg_dword(ha->nxdb_rd_ptr) != dbval) अणु
			wrt_reg_dword(ha->nxdb_wr_ptr, dbval);
			wmb();
		पूर्ण
	पूर्ण

	/* Manage unprocessed RIO/ZIO commands in response queue. */
	अगर (vha->flags.process_response_queue &&
	    rsp->ring_ptr->signature != RESPONSE_PROCESSED)
		qla24xx_process_response_queue(vha, rsp);

	spin_unlock_irqrestore(&ha->hardware_lock, flags);
	वापस QLA_SUCCESS;

queuing_error_fcp_cmnd:
	dma_pool_मुक्त(ha->fcp_cmnd_dma_pool, ctx->fcp_cmnd, ctx->fcp_cmnd_dma);
queuing_error:
	अगर (tot_dsds)
		scsi_dma_unmap(cmd);

	अगर (sp->u.scmd.crc_ctx) अणु
		mempool_मुक्त(sp->u.scmd.crc_ctx, ha->ctx_mempool);
		sp->u.scmd.crc_ctx = शून्य;
	पूर्ण
	spin_unlock_irqrestore(&ha->hardware_lock, flags);

	वापस QLA_FUNCTION_FAILED;
पूर्ण

अटल व्योम
qla24xx_पात_iocb(srb_t *sp, काष्ठा पात_entry_24xx *abt_iocb)
अणु
	काष्ठा srb_iocb *aio = &sp->u.iocb_cmd;
	scsi_qla_host_t *vha = sp->vha;
	काष्ठा req_que *req = sp->qpair->req;
	srb_t *orig_sp = sp->cmd_sp;

	स_रखो(abt_iocb, 0, माप(काष्ठा पात_entry_24xx));
	abt_iocb->entry_type = ABORT_IOCB_TYPE;
	abt_iocb->entry_count = 1;
	abt_iocb->handle = make_handle(req->id, sp->handle);
	अगर (sp->fcport) अणु
		abt_iocb->nport_handle = cpu_to_le16(sp->fcport->loop_id);
		abt_iocb->port_id[0] = sp->fcport->d_id.b.al_pa;
		abt_iocb->port_id[1] = sp->fcport->d_id.b.area;
		abt_iocb->port_id[2] = sp->fcport->d_id.b.करोमुख्य;
	पूर्ण
	abt_iocb->handle_to_पात =
		make_handle(le16_to_cpu(aio->u.abt.req_que_no),
			    aio->u.abt.cmd_hndl);
	abt_iocb->vp_index = vha->vp_idx;
	abt_iocb->req_que_no = aio->u.abt.req_que_no;

	/* need to pass original sp */
	अगर (orig_sp)
		qla_nvme_पात_set_option(abt_iocb, orig_sp);

	/* Send the command to the firmware */
	wmb();
पूर्ण

अटल व्योम
qla2x00_mb_iocb(srb_t *sp, काष्ठा mbx_24xx_entry *mbx)
अणु
	पूर्णांक i, sz;

	mbx->entry_type = MBX_IOCB_TYPE;
	mbx->handle = sp->handle;
	sz = min(ARRAY_SIZE(mbx->mb), ARRAY_SIZE(sp->u.iocb_cmd.u.mbx.out_mb));

	क्रम (i = 0; i < sz; i++)
		mbx->mb[i] = sp->u.iocb_cmd.u.mbx.out_mb[i];
पूर्ण

अटल व्योम
qla2x00_ctpthru_cmd_iocb(srb_t *sp, काष्ठा ct_entry_24xx *ct_pkt)
अणु
	sp->u.iocb_cmd.u.ctarg.iocb = ct_pkt;
	qla24xx_prep_ms_iocb(sp->vha, &sp->u.iocb_cmd.u.ctarg);
	ct_pkt->handle = sp->handle;
पूर्ण

अटल व्योम qla2x00_send_notअगरy_ack_iocb(srb_t *sp,
	काष्ठा nack_to_isp *nack)
अणु
	काष्ठा imm_ntfy_from_isp *ntfy = sp->u.iocb_cmd.u.nack.ntfy;

	nack->entry_type = NOTIFY_ACK_TYPE;
	nack->entry_count = 1;
	nack->ox_id = ntfy->ox_id;

	nack->u.isp24.handle = sp->handle;
	nack->u.isp24.nport_handle = ntfy->u.isp24.nport_handle;
	अगर (le16_to_cpu(ntfy->u.isp24.status) == IMM_NTFY_ELS) अणु
		nack->u.isp24.flags = ntfy->u.isp24.flags &
			cpu_to_le16(NOTIFY24XX_FLAGS_PUREX_IOCB);
	पूर्ण
	nack->u.isp24.srr_rx_id = ntfy->u.isp24.srr_rx_id;
	nack->u.isp24.status = ntfy->u.isp24.status;
	nack->u.isp24.status_subcode = ntfy->u.isp24.status_subcode;
	nack->u.isp24.fw_handle = ntfy->u.isp24.fw_handle;
	nack->u.isp24.exchange_address = ntfy->u.isp24.exchange_address;
	nack->u.isp24.srr_rel_offs = ntfy->u.isp24.srr_rel_offs;
	nack->u.isp24.srr_ui = ntfy->u.isp24.srr_ui;
	nack->u.isp24.srr_flags = 0;
	nack->u.isp24.srr_reject_code = 0;
	nack->u.isp24.srr_reject_code_expl = 0;
	nack->u.isp24.vp_index = ntfy->u.isp24.vp_index;
पूर्ण

/*
 * Build NVME LS request
 */
अटल व्योम
qla_nvme_ls(srb_t *sp, काष्ठा pt_ls4_request *cmd_pkt)
अणु
	काष्ठा srb_iocb *nvme;

	nvme = &sp->u.iocb_cmd;
	cmd_pkt->entry_type = PT_LS4_REQUEST;
	cmd_pkt->entry_count = 1;
	cmd_pkt->control_flags = cpu_to_le16(CF_LS4_ORIGINATOR << CF_LS4_SHIFT);

	cmd_pkt->समयout = cpu_to_le16(nvme->u.nvme.समयout_sec);
	cmd_pkt->nport_handle = cpu_to_le16(sp->fcport->loop_id);
	cmd_pkt->vp_index = sp->fcport->vha->vp_idx;

	cmd_pkt->tx_dseg_count = cpu_to_le16(1);
	cmd_pkt->tx_byte_count = cpu_to_le32(nvme->u.nvme.cmd_len);
	cmd_pkt->dsd[0].length = cpu_to_le32(nvme->u.nvme.cmd_len);
	put_unaligned_le64(nvme->u.nvme.cmd_dma, &cmd_pkt->dsd[0].address);

	cmd_pkt->rx_dseg_count = cpu_to_le16(1);
	cmd_pkt->rx_byte_count = cpu_to_le32(nvme->u.nvme.rsp_len);
	cmd_pkt->dsd[1].length = cpu_to_le32(nvme->u.nvme.rsp_len);
	put_unaligned_le64(nvme->u.nvme.rsp_dma, &cmd_pkt->dsd[1].address);
पूर्ण

अटल व्योम
qla25xx_ctrlvp_iocb(srb_t *sp, काष्ठा vp_ctrl_entry_24xx *vce)
अणु
	पूर्णांक map, pos;

	vce->entry_type = VP_CTRL_IOCB_TYPE;
	vce->handle = sp->handle;
	vce->entry_count = 1;
	vce->command = cpu_to_le16(sp->u.iocb_cmd.u.ctrlvp.cmd);
	vce->vp_count = cpu_to_le16(1);

	/*
	 * index map in firmware starts with 1; decrement index
	 * this is ok as we never use index 0
	 */
	map = (sp->u.iocb_cmd.u.ctrlvp.vp_index - 1) / 8;
	pos = (sp->u.iocb_cmd.u.ctrlvp.vp_index - 1) & 7;
	vce->vp_idx_map[map] |= 1 << pos;
पूर्ण

अटल व्योम
qla24xx_prlo_iocb(srb_t *sp, काष्ठा logio_entry_24xx *logio)
अणु
	logio->entry_type = LOGINOUT_PORT_IOCB_TYPE;
	logio->control_flags =
	    cpu_to_le16(LCF_COMMAND_PRLO|LCF_IMPL_PRLO);

	logio->nport_handle = cpu_to_le16(sp->fcport->loop_id);
	logio->port_id[0] = sp->fcport->d_id.b.al_pa;
	logio->port_id[1] = sp->fcport->d_id.b.area;
	logio->port_id[2] = sp->fcport->d_id.b.करोमुख्य;
	logio->vp_index = sp->fcport->vha->vp_idx;
पूर्ण

पूर्णांक
qla2x00_start_sp(srb_t *sp)
अणु
	पूर्णांक rval = QLA_SUCCESS;
	scsi_qla_host_t *vha = sp->vha;
	काष्ठा qla_hw_data *ha = vha->hw;
	काष्ठा qla_qpair *qp = sp->qpair;
	व्योम *pkt;
	अचिन्हित दीर्घ flags;

	अगर (vha->hw->flags.eeh_busy)
		वापस -EIO;

	spin_lock_irqsave(qp->qp_lock_ptr, flags);
	pkt = __qla2x00_alloc_iocbs(sp->qpair, sp);
	अगर (!pkt) अणु
		rval = EAGAIN;
		ql_log(ql_log_warn, vha, 0x700c,
		    "qla2x00_alloc_iocbs failed.\n");
		जाओ करोne;
	पूर्ण

	चयन (sp->type) अणु
	हाल SRB_LOGIN_CMD:
		IS_FWI2_CAPABLE(ha) ?
		    qla24xx_login_iocb(sp, pkt) :
		    qla2x00_login_iocb(sp, pkt);
		अवरोध;
	हाल SRB_PRLI_CMD:
		qla24xx_prli_iocb(sp, pkt);
		अवरोध;
	हाल SRB_LOGOUT_CMD:
		IS_FWI2_CAPABLE(ha) ?
		    qla24xx_logout_iocb(sp, pkt) :
		    qla2x00_logout_iocb(sp, pkt);
		अवरोध;
	हाल SRB_ELS_CMD_RPT:
	हाल SRB_ELS_CMD_HST:
		qla24xx_els_iocb(sp, pkt);
		अवरोध;
	हाल SRB_CT_CMD:
		IS_FWI2_CAPABLE(ha) ?
		    qla24xx_ct_iocb(sp, pkt) :
		    qla2x00_ct_iocb(sp, pkt);
		अवरोध;
	हाल SRB_ADISC_CMD:
		IS_FWI2_CAPABLE(ha) ?
		    qla24xx_adisc_iocb(sp, pkt) :
		    qla2x00_adisc_iocb(sp, pkt);
		अवरोध;
	हाल SRB_TM_CMD:
		IS_QLAFX00(ha) ?
		    qlafx00_पंचांग_iocb(sp, pkt) :
		    qla24xx_पंचांग_iocb(sp, pkt);
		अवरोध;
	हाल SRB_FXIOCB_DCMD:
	हाल SRB_FXIOCB_BCMD:
		qlafx00_fxdisc_iocb(sp, pkt);
		अवरोध;
	हाल SRB_NVME_LS:
		qla_nvme_ls(sp, pkt);
		अवरोध;
	हाल SRB_ABT_CMD:
		IS_QLAFX00(ha) ?
			qlafx00_पात_iocb(sp, pkt) :
			qla24xx_पात_iocb(sp, pkt);
		अवरोध;
	हाल SRB_ELS_DCMD:
		qla24xx_els_logo_iocb(sp, pkt);
		अवरोध;
	हाल SRB_CT_PTHRU_CMD:
		qla2x00_ctpthru_cmd_iocb(sp, pkt);
		अवरोध;
	हाल SRB_MB_IOCB:
		qla2x00_mb_iocb(sp, pkt);
		अवरोध;
	हाल SRB_NACK_PLOGI:
	हाल SRB_NACK_PRLI:
	हाल SRB_NACK_LOGO:
		qla2x00_send_notअगरy_ack_iocb(sp, pkt);
		अवरोध;
	हाल SRB_CTRL_VP:
		qla25xx_ctrlvp_iocb(sp, pkt);
		अवरोध;
	हाल SRB_PRLO_CMD:
		qla24xx_prlo_iocb(sp, pkt);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	अगर (sp->start_समयr)
		add_समयr(&sp->u.iocb_cmd.समयr);

	wmb();
	qla2x00_start_iocbs(vha, qp->req);
करोne:
	spin_unlock_irqrestore(qp->qp_lock_ptr, flags);
	वापस rval;
पूर्ण

अटल व्योम
qla25xx_build_bidir_iocb(srb_t *sp, काष्ठा scsi_qla_host *vha,
				काष्ठा cmd_bidir *cmd_pkt, uपूर्णांक32_t tot_dsds)
अणु
	uपूर्णांक16_t avail_dsds;
	काष्ठा dsd64 *cur_dsd;
	uपूर्णांक32_t req_data_len = 0;
	uपूर्णांक32_t rsp_data_len = 0;
	काष्ठा scatterlist *sg;
	पूर्णांक index;
	पूर्णांक entry_count = 1;
	काष्ठा bsg_job *bsg_job = sp->u.bsg_job;

	/*Update entry type to indicate bidir command */
	put_unaligned_le32(COMMAND_BIसूचीECTIONAL, &cmd_pkt->entry_type);

	/* Set the transfer direction, in this set both flags
	 * Also set the BD_WRAP_BACK flag, firmware will take care
	 * assigning DID=SID क्रम outgoing pkts.
	 */
	cmd_pkt->wr_dseg_count = cpu_to_le16(bsg_job->request_payload.sg_cnt);
	cmd_pkt->rd_dseg_count = cpu_to_le16(bsg_job->reply_payload.sg_cnt);
	cmd_pkt->control_flags = cpu_to_le16(BD_WRITE_DATA | BD_READ_DATA |
							BD_WRAP_BACK);

	req_data_len = rsp_data_len = bsg_job->request_payload.payload_len;
	cmd_pkt->wr_byte_count = cpu_to_le32(req_data_len);
	cmd_pkt->rd_byte_count = cpu_to_le32(rsp_data_len);
	cmd_pkt->समयout = cpu_to_le16(qla2x00_get_async_समयout(vha) + 2);

	vha->bidi_stats.transfer_bytes += req_data_len;
	vha->bidi_stats.io_count++;

	vha->qla_stats.output_bytes += req_data_len;
	vha->qla_stats.output_requests++;

	/* Only one dsd is available क्रम bidirectional IOCB, reमुख्यing dsds
	 * are bundled in continuation iocb
	 */
	avail_dsds = 1;
	cur_dsd = &cmd_pkt->fcp_dsd;

	index = 0;

	क्रम_each_sg(bsg_job->request_payload.sg_list, sg,
				bsg_job->request_payload.sg_cnt, index) अणु
		cont_a64_entry_t *cont_pkt;

		/* Allocate additional continuation packets */
		अगर (avail_dsds == 0) अणु
			/* Continuation type 1 IOCB can accomodate
			 * 5 DSDS
			 */
			cont_pkt = qla2x00_prep_cont_type1_iocb(vha, vha->req);
			cur_dsd = cont_pkt->dsd;
			avail_dsds = 5;
			entry_count++;
		पूर्ण
		append_dsd64(&cur_dsd, sg);
		avail_dsds--;
	पूर्ण
	/* For पढ़ो request DSD will always goes to continuation IOCB
	 * and follow the ग_लिखो DSD. If there is room on the current IOCB
	 * then it is added to that IOCB अन्यथा new continuation IOCB is
	 * allocated.
	 */
	क्रम_each_sg(bsg_job->reply_payload.sg_list, sg,
				bsg_job->reply_payload.sg_cnt, index) अणु
		cont_a64_entry_t *cont_pkt;

		/* Allocate additional continuation packets */
		अगर (avail_dsds == 0) अणु
			/* Continuation type 1 IOCB can accomodate
			 * 5 DSDS
			 */
			cont_pkt = qla2x00_prep_cont_type1_iocb(vha, vha->req);
			cur_dsd = cont_pkt->dsd;
			avail_dsds = 5;
			entry_count++;
		पूर्ण
		append_dsd64(&cur_dsd, sg);
		avail_dsds--;
	पूर्ण
	/* This value should be same as number of IOCB required क्रम this cmd */
	cmd_pkt->entry_count = entry_count;
पूर्ण

पूर्णांक
qla2x00_start_bidir(srb_t *sp, काष्ठा scsi_qla_host *vha, uपूर्णांक32_t tot_dsds)
अणु

	काष्ठा qla_hw_data *ha = vha->hw;
	अचिन्हित दीर्घ flags;
	uपूर्णांक32_t handle;
	uपूर्णांक16_t req_cnt;
	uपूर्णांक16_t cnt;
	uपूर्णांक32_t *clr_ptr;
	काष्ठा cmd_bidir *cmd_pkt = शून्य;
	काष्ठा rsp_que *rsp;
	काष्ठा req_que *req;
	पूर्णांक rval = EXT_STATUS_OK;

	rval = QLA_SUCCESS;

	rsp = ha->rsp_q_map[0];
	req = vha->req;

	/* Send marker अगर required */
	अगर (vha->marker_needed != 0) अणु
		अगर (qla2x00_marker(vha, ha->base_qpair,
			0, 0, MK_SYNC_ALL) != QLA_SUCCESS)
			वापस EXT_STATUS_MAILBOX;
		vha->marker_needed = 0;
	पूर्ण

	/* Acquire ring specअगरic lock */
	spin_lock_irqsave(&ha->hardware_lock, flags);

	handle = qla2xxx_get_next_handle(req);
	अगर (handle == 0) अणु
		rval = EXT_STATUS_BUSY;
		जाओ queuing_error;
	पूर्ण

	/* Calculate number of IOCB required */
	req_cnt = qla24xx_calc_iocbs(vha, tot_dsds);

	/* Check क्रम room on request queue. */
	अगर (req->cnt < req_cnt + 2) अणु
		अगर (IS_SHADOW_REG_CAPABLE(ha)) अणु
			cnt = *req->out_ptr;
		पूर्ण अन्यथा अणु
			cnt = rd_reg_dword_relaxed(req->req_q_out);
			अगर (qla2x00_check_reg16_क्रम_disconnect(vha, cnt))
				जाओ queuing_error;
		पूर्ण

		अगर  (req->ring_index < cnt)
			req->cnt = cnt - req->ring_index;
		अन्यथा
			req->cnt = req->length -
				(req->ring_index - cnt);
	पूर्ण
	अगर (req->cnt < req_cnt + 2) अणु
		rval = EXT_STATUS_BUSY;
		जाओ queuing_error;
	पूर्ण

	cmd_pkt = (काष्ठा cmd_bidir *)req->ring_ptr;
	cmd_pkt->handle = make_handle(req->id, handle);

	/* Zero out reमुख्यing portion of packet. */
	/* tagged queuing modअगरier -- शेष is TSK_SIMPLE (0).*/
	clr_ptr = (uपूर्णांक32_t *)cmd_pkt + 2;
	स_रखो(clr_ptr, 0, REQUEST_ENTRY_SIZE - 8);

	/* Set NPORT-ID  (of vha)*/
	cmd_pkt->nport_handle = cpu_to_le16(vha->self_login_loop_id);
	cmd_pkt->port_id[0] = vha->d_id.b.al_pa;
	cmd_pkt->port_id[1] = vha->d_id.b.area;
	cmd_pkt->port_id[2] = vha->d_id.b.करोमुख्य;

	qla25xx_build_bidir_iocb(sp, vha, cmd_pkt, tot_dsds);
	cmd_pkt->entry_status = (uपूर्णांक8_t) rsp->id;
	/* Build command packet. */
	req->current_outstanding_cmd = handle;
	req->outstanding_cmds[handle] = sp;
	sp->handle = handle;
	req->cnt -= req_cnt;

	/* Send the command to the firmware */
	wmb();
	qla2x00_start_iocbs(vha, req);
queuing_error:
	spin_unlock_irqrestore(&ha->hardware_lock, flags);

	वापस rval;
पूर्ण
