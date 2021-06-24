<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * QLogic Fibre Channel HBA Driver
 * Copyright (c)  2003-2017 QLogic Corporation
 */
#समावेश "qla_nvme.h"
#समावेश <linux/scatterlist.h>
#समावेश <linux/delay.h>
#समावेश <linux/nvme.h>
#समावेश <linux/nvme-fc.h>

अटल काष्ठा nvme_fc_port_ढाँचा qla_nvme_fc_transport;

पूर्णांक qla_nvme_रेजिस्टर_remote(काष्ठा scsi_qla_host *vha, काष्ठा fc_port *fcport)
अणु
	काष्ठा qla_nvme_rport *rport;
	काष्ठा nvme_fc_port_info req;
	पूर्णांक ret;

	अगर (!IS_ENABLED(CONFIG_NVME_FC))
		वापस 0;

	अगर (!vha->flags.nvme_enabled) अणु
		ql_log(ql_log_info, vha, 0x2100,
		    "%s: Not registering target since Host NVME is not enabled\n",
		    __func__);
		वापस 0;
	पूर्ण

	अगर (!vha->nvme_local_port && qla_nvme_रेजिस्टर_hba(vha))
		वापस 0;

	अगर (!(fcport->nvme_prli_service_param &
	    (NVME_PRLI_SP_TARGET | NVME_PRLI_SP_DISCOVERY)) ||
		(fcport->nvme_flag & NVME_FLAG_REGISTERED))
		वापस 0;

	fcport->nvme_flag &= ~NVME_FLAG_RESETTING;

	स_रखो(&req, 0, माप(काष्ठा nvme_fc_port_info));
	req.port_name = wwn_to_u64(fcport->port_name);
	req.node_name = wwn_to_u64(fcport->node_name);
	req.port_role = 0;
	req.dev_loss_पंचांगo = 0;

	अगर (fcport->nvme_prli_service_param & NVME_PRLI_SP_INITIATOR)
		req.port_role = FC_PORT_ROLE_NVME_INITIATOR;

	अगर (fcport->nvme_prli_service_param & NVME_PRLI_SP_TARGET)
		req.port_role |= FC_PORT_ROLE_NVME_TARGET;

	अगर (fcport->nvme_prli_service_param & NVME_PRLI_SP_DISCOVERY)
		req.port_role |= FC_PORT_ROLE_NVME_DISCOVERY;

	req.port_id = fcport->d_id.b24;

	ql_log(ql_log_info, vha, 0x2102,
	    "%s: traddr=nn-0x%016llx:pn-0x%016llx PortID:%06x\n",
	    __func__, req.node_name, req.port_name,
	    req.port_id);

	ret = nvme_fc_रेजिस्टर_remoteport(vha->nvme_local_port, &req,
	    &fcport->nvme_remote_port);
	अगर (ret) अणु
		ql_log(ql_log_warn, vha, 0x212e,
		    "Failed to register remote port. Transport returned %d\n",
		    ret);
		वापस ret;
	पूर्ण

	अगर (fcport->nvme_prli_service_param & NVME_PRLI_SP_SLER)
		ql_log(ql_log_info, vha, 0x212a,
		       "PortID:%06x Supports SLER\n", req.port_id);

	अगर (fcport->nvme_prli_service_param & NVME_PRLI_SP_PI_CTRL)
		ql_log(ql_log_info, vha, 0x212b,
		       "PortID:%06x Supports PI control\n", req.port_id);

	rport = fcport->nvme_remote_port->निजी;
	rport->fcport = fcport;

	fcport->nvme_flag |= NVME_FLAG_REGISTERED;
	वापस 0;
पूर्ण

/* Allocate a queue क्रम NVMe traffic */
अटल पूर्णांक qla_nvme_alloc_queue(काष्ठा nvme_fc_local_port *lport,
    अचिन्हित पूर्णांक qidx, u16 qsize, व्योम **handle)
अणु
	काष्ठा scsi_qla_host *vha;
	काष्ठा qla_hw_data *ha;
	काष्ठा qla_qpair *qpair;

	अगर (!qidx)
		qidx++;

	vha = (काष्ठा scsi_qla_host *)lport->निजी;
	ha = vha->hw;

	ql_log(ql_log_info, vha, 0x2104,
	    "%s: handle %p, idx =%d, qsize %d\n",
	    __func__, handle, qidx, qsize);

	अगर (qidx > qla_nvme_fc_transport.max_hw_queues) अणु
		ql_log(ql_log_warn, vha, 0x212f,
		    "%s: Illegal qidx=%d. Max=%d\n",
		    __func__, qidx, qla_nvme_fc_transport.max_hw_queues);
		वापस -EINVAL;
	पूर्ण

	अगर (ha->queue_pair_map[qidx]) अणु
		*handle = ha->queue_pair_map[qidx];
		ql_log(ql_log_info, vha, 0x2121,
		    "Returning existing qpair of %p for idx=%x\n",
		    *handle, qidx);
		वापस 0;
	पूर्ण

	qpair = qla2xxx_create_qpair(vha, 5, vha->vp_idx, true);
	अगर (qpair == शून्य) अणु
		ql_log(ql_log_warn, vha, 0x2122,
		    "Failed to allocate qpair\n");
		वापस -EINVAL;
	पूर्ण
	*handle = qpair;

	वापस 0;
पूर्ण

अटल व्योम qla_nvme_release_fcp_cmd_kref(काष्ठा kref *kref)
अणु
	काष्ठा srb *sp = container_of(kref, काष्ठा srb, cmd_kref);
	काष्ठा nvme_निजी *priv = (काष्ठा nvme_निजी *)sp->priv;
	काष्ठा nvmefc_fcp_req *fd;
	काष्ठा srb_iocb *nvme;
	अचिन्हित दीर्घ flags;

	अगर (!priv)
		जाओ out;

	nvme = &sp->u.iocb_cmd;
	fd = nvme->u.nvme.desc;

	spin_lock_irqsave(&priv->cmd_lock, flags);
	priv->sp = शून्य;
	sp->priv = शून्य;
	अगर (priv->comp_status == QLA_SUCCESS) अणु
		fd->rcv_rsplen = le16_to_cpu(nvme->u.nvme.rsp_pyld_len);
		fd->status = NVME_SC_SUCCESS;
	पूर्ण अन्यथा अणु
		fd->rcv_rsplen = 0;
		fd->transferred_length = 0;
		fd->status = NVME_SC_INTERNAL;
	पूर्ण
	spin_unlock_irqrestore(&priv->cmd_lock, flags);

	fd->करोne(fd);
out:
	qla2xxx_rel_qpair_sp(sp->qpair, sp);
पूर्ण

अटल व्योम qla_nvme_release_ls_cmd_kref(काष्ठा kref *kref)
अणु
	काष्ठा srb *sp = container_of(kref, काष्ठा srb, cmd_kref);
	काष्ठा nvme_निजी *priv = (काष्ठा nvme_निजी *)sp->priv;
	काष्ठा nvmefc_ls_req *fd;
	अचिन्हित दीर्घ flags;

	अगर (!priv)
		जाओ out;

	spin_lock_irqsave(&priv->cmd_lock, flags);
	priv->sp = शून्य;
	sp->priv = शून्य;
	spin_unlock_irqrestore(&priv->cmd_lock, flags);

	fd = priv->fd;
	fd->करोne(fd, priv->comp_status);
out:
	qla2x00_rel_sp(sp);
पूर्ण

अटल व्योम qla_nvme_ls_complete(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा nvme_निजी *priv =
		container_of(work, काष्ठा nvme_निजी, ls_work);

	kref_put(&priv->sp->cmd_kref, qla_nvme_release_ls_cmd_kref);
पूर्ण

अटल व्योम qla_nvme_sp_ls_करोne(srb_t *sp, पूर्णांक res)
अणु
	काष्ठा nvme_निजी *priv = sp->priv;

	अगर (WARN_ON_ONCE(kref_पढ़ो(&sp->cmd_kref) == 0))
		वापस;

	अगर (res)
		res = -EINVAL;

	priv->comp_status = res;
	INIT_WORK(&priv->ls_work, qla_nvme_ls_complete);
	schedule_work(&priv->ls_work);
पूर्ण

/* it assumed that QPair lock is held. */
अटल व्योम qla_nvme_sp_करोne(srb_t *sp, पूर्णांक res)
अणु
	काष्ठा nvme_निजी *priv = sp->priv;

	priv->comp_status = res;
	kref_put(&sp->cmd_kref, qla_nvme_release_fcp_cmd_kref);

	वापस;
पूर्ण

अटल व्योम qla_nvme_पात_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा nvme_निजी *priv =
		container_of(work, काष्ठा nvme_निजी, पात_work);
	srb_t *sp = priv->sp;
	fc_port_t *fcport = sp->fcport;
	काष्ठा qla_hw_data *ha = fcport->vha->hw;
	पूर्णांक rval;

	ql_dbg(ql_dbg_io, fcport->vha, 0xffff,
	       "%s called for sp=%p, hndl=%x on fcport=%p deleted=%d\n",
	       __func__, sp, sp->handle, fcport, fcport->deleted);

	अगर (!ha->flags.fw_started || fcport->deleted)
		जाओ out;

	अगर (ha->flags.host_shutting_करोwn) अणु
		ql_log(ql_log_info, sp->fcport->vha, 0xffff,
		    "%s Calling done on sp: %p, type: 0x%x\n",
		    __func__, sp, sp->type);
		sp->करोne(sp, 0);
		जाओ out;
	पूर्ण

	rval = ha->isp_ops->पात_command(sp);

	ql_dbg(ql_dbg_io, fcport->vha, 0x212b,
	    "%s: %s command for sp=%p, handle=%x on fcport=%p rval=%x\n",
	    __func__, (rval != QLA_SUCCESS) ? "Failed to abort" : "Aborted",
	    sp, sp->handle, fcport, rval);

	/*
	 * Returned beक्रमe decreasing kref so that I/O requests
	 * are रुकोed until ABTS complete. This kref is decreased
	 * at qla24xx_पात_sp_करोne function.
	 */
	अगर (ql2xabts_रुको_nvme && QLA_ABTS_WAIT_ENABLED(sp))
		वापस;
out:
	/* kref_get was करोne beक्रमe work was schedule. */
	kref_put(&sp->cmd_kref, sp->put_fn);
पूर्ण

अटल व्योम qla_nvme_ls_पात(काष्ठा nvme_fc_local_port *lport,
    काष्ठा nvme_fc_remote_port *rport, काष्ठा nvmefc_ls_req *fd)
अणु
	काष्ठा nvme_निजी *priv = fd->निजी;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&priv->cmd_lock, flags);
	अगर (!priv->sp) अणु
		spin_unlock_irqrestore(&priv->cmd_lock, flags);
		वापस;
	पूर्ण

	अगर (!kref_get_unless_zero(&priv->sp->cmd_kref)) अणु
		spin_unlock_irqrestore(&priv->cmd_lock, flags);
		वापस;
	पूर्ण
	spin_unlock_irqrestore(&priv->cmd_lock, flags);

	INIT_WORK(&priv->पात_work, qla_nvme_पात_work);
	schedule_work(&priv->पात_work);
पूर्ण

अटल पूर्णांक qla_nvme_ls_req(काष्ठा nvme_fc_local_port *lport,
    काष्ठा nvme_fc_remote_port *rport, काष्ठा nvmefc_ls_req *fd)
अणु
	काष्ठा qla_nvme_rport *qla_rport = rport->निजी;
	fc_port_t *fcport = qla_rport->fcport;
	काष्ठा srb_iocb   *nvme;
	काष्ठा nvme_निजी *priv = fd->निजी;
	काष्ठा scsi_qla_host *vha;
	पूर्णांक     rval = QLA_FUNCTION_FAILED;
	काष्ठा qla_hw_data *ha;
	srb_t           *sp;

	अगर (!fcport || fcport->deleted)
		वापस rval;

	vha = fcport->vha;
	ha = vha->hw;

	अगर (!ha->flags.fw_started)
		वापस rval;

	/* Alloc SRB काष्ठाure */
	sp = qla2x00_get_sp(vha, fcport, GFP_ATOMIC);
	अगर (!sp)
		वापस rval;

	sp->type = SRB_NVME_LS;
	sp->name = "nvme_ls";
	sp->करोne = qla_nvme_sp_ls_करोne;
	sp->put_fn = qla_nvme_release_ls_cmd_kref;
	sp->priv = priv;
	priv->sp = sp;
	kref_init(&sp->cmd_kref);
	spin_lock_init(&priv->cmd_lock);
	nvme = &sp->u.iocb_cmd;
	priv->fd = fd;
	nvme->u.nvme.desc = fd;
	nvme->u.nvme.dir = 0;
	nvme->u.nvme.dl = 0;
	nvme->u.nvme.cmd_len = fd->rqstlen;
	nvme->u.nvme.rsp_len = fd->rsplen;
	nvme->u.nvme.rsp_dma = fd->rspdma;
	nvme->u.nvme.समयout_sec = fd->समयout;
	nvme->u.nvme.cmd_dma = dma_map_single(&ha->pdev->dev, fd->rqstaddr,
	    fd->rqstlen, DMA_TO_DEVICE);
	dma_sync_single_क्रम_device(&ha->pdev->dev, nvme->u.nvme.cmd_dma,
	    fd->rqstlen, DMA_TO_DEVICE);

	rval = qla2x00_start_sp(sp);
	अगर (rval != QLA_SUCCESS) अणु
		ql_log(ql_log_warn, vha, 0x700e,
		    "qla2x00_start_sp failed = %d\n", rval);
		wake_up(&sp->nvme_ls_रुकोq);
		sp->priv = शून्य;
		priv->sp = शून्य;
		qla2x00_rel_sp(sp);
		वापस rval;
	पूर्ण

	वापस rval;
पूर्ण

अटल व्योम qla_nvme_fcp_पात(काष्ठा nvme_fc_local_port *lport,
    काष्ठा nvme_fc_remote_port *rport, व्योम *hw_queue_handle,
    काष्ठा nvmefc_fcp_req *fd)
अणु
	काष्ठा nvme_निजी *priv = fd->निजी;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&priv->cmd_lock, flags);
	अगर (!priv->sp) अणु
		spin_unlock_irqrestore(&priv->cmd_lock, flags);
		वापस;
	पूर्ण
	अगर (!kref_get_unless_zero(&priv->sp->cmd_kref)) अणु
		spin_unlock_irqrestore(&priv->cmd_lock, flags);
		वापस;
	पूर्ण
	spin_unlock_irqrestore(&priv->cmd_lock, flags);

	INIT_WORK(&priv->पात_work, qla_nvme_पात_work);
	schedule_work(&priv->पात_work);
पूर्ण

अटल अंतरभूत पूर्णांक qla2x00_start_nvme_mq(srb_t *sp)
अणु
	अचिन्हित दीर्घ   flags;
	uपूर्णांक32_t        *clr_ptr;
	uपूर्णांक32_t        handle;
	काष्ठा cmd_nvme *cmd_pkt;
	uपूर्णांक16_t        cnt, i;
	uपूर्णांक16_t        req_cnt;
	uपूर्णांक16_t        tot_dsds;
	uपूर्णांक16_t	avail_dsds;
	काष्ठा dsd64	*cur_dsd;
	काष्ठा req_que *req = शून्य;
	काष्ठा scsi_qla_host *vha = sp->fcport->vha;
	काष्ठा qla_hw_data *ha = vha->hw;
	काष्ठा qla_qpair *qpair = sp->qpair;
	काष्ठा srb_iocb *nvme = &sp->u.iocb_cmd;
	काष्ठा scatterlist *sgl, *sg;
	काष्ठा nvmefc_fcp_req *fd = nvme->u.nvme.desc;
	काष्ठा nvme_fc_cmd_iu *cmd = fd->cmdaddr;
	uपूर्णांक32_t        rval = QLA_SUCCESS;

	/* Setup qpair poपूर्णांकers */
	req = qpair->req;
	tot_dsds = fd->sg_cnt;

	/* Acquire qpair specअगरic lock */
	spin_lock_irqsave(&qpair->qp_lock, flags);

	handle = qla2xxx_get_next_handle(req);
	अगर (handle == 0) अणु
		rval = -EBUSY;
		जाओ queuing_error;
	पूर्ण
	req_cnt = qla24xx_calc_iocbs(vha, tot_dsds);
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
			req->cnt = req->length - (req->ring_index - cnt);

		अगर (req->cnt < (req_cnt + 2))अणु
			rval = -EBUSY;
			जाओ queuing_error;
		पूर्ण
	पूर्ण

	अगर (unlikely(!fd->sqid)) अणु
		अगर (cmd->sqe.common.opcode == nvme_admin_async_event) अणु
			nvme->u.nvme.aen_op = 1;
			atomic_inc(&ha->nvme_active_aen_cnt);
		पूर्ण
	पूर्ण

	/* Build command packet. */
	req->current_outstanding_cmd = handle;
	req->outstanding_cmds[handle] = sp;
	sp->handle = handle;
	req->cnt -= req_cnt;

	cmd_pkt = (काष्ठा cmd_nvme *)req->ring_ptr;
	cmd_pkt->handle = make_handle(req->id, handle);

	/* Zero out reमुख्यing portion of packet. */
	clr_ptr = (uपूर्णांक32_t *)cmd_pkt + 2;
	स_रखो(clr_ptr, 0, REQUEST_ENTRY_SIZE - 8);

	cmd_pkt->entry_status = 0;

	/* Update entry type to indicate Command NVME IOCB */
	cmd_pkt->entry_type = COMMAND_NVME;

	/* No data transfer how करो we check buffer len == 0?? */
	अगर (fd->io_dir == NVMEFC_FCP_READ) अणु
		cmd_pkt->control_flags = cpu_to_le16(CF_READ_DATA);
		qpair->counters.input_bytes += fd->payload_length;
		qpair->counters.input_requests++;
	पूर्ण अन्यथा अगर (fd->io_dir == NVMEFC_FCP_WRITE) अणु
		cmd_pkt->control_flags = cpu_to_le16(CF_WRITE_DATA);
		अगर ((vha->flags.nvme_first_burst) &&
		    (sp->fcport->nvme_prli_service_param &
			NVME_PRLI_SP_FIRST_BURST)) अणु
			अगर ((fd->payload_length <=
			    sp->fcport->nvme_first_burst_size) ||
				(sp->fcport->nvme_first_burst_size == 0))
				cmd_pkt->control_flags |=
					cpu_to_le16(CF_NVME_FIRST_BURST_ENABLE);
		पूर्ण
		qpair->counters.output_bytes += fd->payload_length;
		qpair->counters.output_requests++;
	पूर्ण अन्यथा अगर (fd->io_dir == 0) अणु
		cmd_pkt->control_flags = 0;
	पूर्ण
	/* Set BIT_13 of control flags क्रम Async event */
	अगर (vha->flags.nvme2_enabled &&
	    cmd->sqe.common.opcode == nvme_admin_async_event) अणु
		cmd_pkt->control_flags |= cpu_to_le16(CF_ADMIN_ASYNC_EVENT);
	पूर्ण

	/* Set NPORT-ID */
	cmd_pkt->nport_handle = cpu_to_le16(sp->fcport->loop_id);
	cmd_pkt->port_id[0] = sp->fcport->d_id.b.al_pa;
	cmd_pkt->port_id[1] = sp->fcport->d_id.b.area;
	cmd_pkt->port_id[2] = sp->fcport->d_id.b.करोमुख्य;
	cmd_pkt->vp_index = sp->fcport->vha->vp_idx;

	/* NVME RSP IU */
	cmd_pkt->nvme_rsp_dsd_len = cpu_to_le16(fd->rsplen);
	put_unaligned_le64(fd->rspdma, &cmd_pkt->nvme_rsp_dseg_address);

	/* NVME CNMD IU */
	cmd_pkt->nvme_cmnd_dseg_len = cpu_to_le16(fd->cmdlen);
	cmd_pkt->nvme_cmnd_dseg_address = cpu_to_le64(fd->cmddma);

	cmd_pkt->dseg_count = cpu_to_le16(tot_dsds);
	cmd_pkt->byte_count = cpu_to_le32(fd->payload_length);

	/* One DSD is available in the Command Type NVME IOCB */
	avail_dsds = 1;
	cur_dsd = &cmd_pkt->nvme_dsd;
	sgl = fd->first_sgl;

	/* Load data segments */
	क्रम_each_sg(sgl, sg, tot_dsds, i) अणु
		cont_a64_entry_t *cont_pkt;

		/* Allocate additional continuation packets? */
		अगर (avail_dsds == 0) अणु
			/*
			 * Five DSDs are available in the Continuation
			 * Type 1 IOCB.
			 */

			/* Adjust ring index */
			req->ring_index++;
			अगर (req->ring_index == req->length) अणु
				req->ring_index = 0;
				req->ring_ptr = req->ring;
			पूर्ण अन्यथा अणु
				req->ring_ptr++;
			पूर्ण
			cont_pkt = (cont_a64_entry_t *)req->ring_ptr;
			put_unaligned_le32(CONTINUE_A64_TYPE,
					   &cont_pkt->entry_type);

			cur_dsd = cont_pkt->dsd;
			avail_dsds = ARRAY_SIZE(cont_pkt->dsd);
		पूर्ण

		append_dsd64(&cur_dsd, sg);
		avail_dsds--;
	पूर्ण

	/* Set total entry count. */
	cmd_pkt->entry_count = (uपूर्णांक8_t)req_cnt;
	wmb();

	/* Adjust ring index. */
	req->ring_index++;
	अगर (req->ring_index == req->length) अणु
		req->ring_index = 0;
		req->ring_ptr = req->ring;
	पूर्ण अन्यथा अणु
		req->ring_ptr++;
	पूर्ण

	/* Set chip new ring index. */
	wrt_reg_dword(req->req_q_in, req->ring_index);

queuing_error:
	spin_unlock_irqrestore(&qpair->qp_lock, flags);

	वापस rval;
पूर्ण

/* Post a command */
अटल पूर्णांक qla_nvme_post_cmd(काष्ठा nvme_fc_local_port *lport,
    काष्ठा nvme_fc_remote_port *rport, व्योम *hw_queue_handle,
    काष्ठा nvmefc_fcp_req *fd)
अणु
	fc_port_t *fcport;
	काष्ठा srb_iocb *nvme;
	काष्ठा scsi_qla_host *vha;
	पूर्णांक rval;
	srb_t *sp;
	काष्ठा qla_qpair *qpair = hw_queue_handle;
	काष्ठा nvme_निजी *priv = fd->निजी;
	काष्ठा qla_nvme_rport *qla_rport = rport->निजी;

	अगर (!priv) अणु
		/* nvme association has been torn करोwn */
		वापस -ENODEV;
	पूर्ण

	fcport = qla_rport->fcport;

	अगर (unlikely(!qpair || !fcport || fcport->deleted))
		वापस -EBUSY;

	अगर (!(fcport->nvme_flag & NVME_FLAG_REGISTERED))
		वापस -ENODEV;

	vha = fcport->vha;

	अगर (test_bit(ABORT_ISP_ACTIVE, &vha->dpc_flags))
		वापस -EBUSY;

	/*
	 * If we know the dev is going away जबतक the transport is still sending
	 * IO's वापस busy back to stall the IO Q.  This happens when the
	 * link goes away and fw hasn't notified us yet, but IO's are being
	 * वापसed. If the dev comes back quickly we won't exhaust the IO
	 * retry count at the core.
	 */
	अगर (fcport->nvme_flag & NVME_FLAG_RESETTING)
		वापस -EBUSY;

	/* Alloc SRB काष्ठाure */
	sp = qla2xxx_get_qpair_sp(vha, qpair, fcport, GFP_ATOMIC);
	अगर (!sp)
		वापस -EBUSY;

	init_रुकोqueue_head(&sp->nvme_ls_रुकोq);
	kref_init(&sp->cmd_kref);
	spin_lock_init(&priv->cmd_lock);
	sp->priv = priv;
	priv->sp = sp;
	sp->type = SRB_NVME_CMD;
	sp->name = "nvme_cmd";
	sp->करोne = qla_nvme_sp_करोne;
	sp->put_fn = qla_nvme_release_fcp_cmd_kref;
	sp->qpair = qpair;
	sp->vha = vha;
	sp->cmd_sp = sp;
	nvme = &sp->u.iocb_cmd;
	nvme->u.nvme.desc = fd;

	rval = qla2x00_start_nvme_mq(sp);
	अगर (rval != QLA_SUCCESS) अणु
		ql_log(ql_log_warn, vha, 0x212d,
		    "qla2x00_start_nvme_mq failed = %d\n", rval);
		wake_up(&sp->nvme_ls_रुकोq);
		sp->priv = शून्य;
		priv->sp = शून्य;
		qla2xxx_rel_qpair_sp(sp->qpair, sp);
	पूर्ण

	वापस rval;
पूर्ण

अटल व्योम qla_nvme_localport_delete(काष्ठा nvme_fc_local_port *lport)
अणु
	काष्ठा scsi_qla_host *vha = lport->निजी;

	ql_log(ql_log_info, vha, 0x210f,
	    "localport delete of %p completed.\n", vha->nvme_local_port);
	vha->nvme_local_port = शून्य;
	complete(&vha->nvme_del_करोne);
पूर्ण

अटल व्योम qla_nvme_remoteport_delete(काष्ठा nvme_fc_remote_port *rport)
अणु
	fc_port_t *fcport;
	काष्ठा qla_nvme_rport *qla_rport = rport->निजी;

	fcport = qla_rport->fcport;
	fcport->nvme_remote_port = शून्य;
	fcport->nvme_flag &= ~NVME_FLAG_REGISTERED;
	fcport->nvme_flag &= ~NVME_FLAG_DELETING;
	ql_log(ql_log_info, fcport->vha, 0x2110,
	    "remoteport_delete of %p %8phN completed.\n",
	    fcport, fcport->port_name);
	complete(&fcport->nvme_del_करोne);
पूर्ण

अटल काष्ठा nvme_fc_port_ढाँचा qla_nvme_fc_transport = अणु
	.localport_delete = qla_nvme_localport_delete,
	.remoteport_delete = qla_nvme_remoteport_delete,
	.create_queue   = qla_nvme_alloc_queue,
	.delete_queue 	= शून्य,
	.ls_req		= qla_nvme_ls_req,
	.ls_पात	= qla_nvme_ls_पात,
	.fcp_io		= qla_nvme_post_cmd,
	.fcp_पात	= qla_nvme_fcp_पात,
	.max_hw_queues  = 8,
	.max_sgl_segments = 1024,
	.max_dअगर_sgl_segments = 64,
	.dma_boundary = 0xFFFFFFFF,
	.local_priv_sz  = 8,
	.remote_priv_sz = माप(काष्ठा qla_nvme_rport),
	.lsrqst_priv_sz = माप(काष्ठा nvme_निजी),
	.fcprqst_priv_sz = माप(काष्ठा nvme_निजी),
पूर्ण;

व्योम qla_nvme_unरेजिस्टर_remote_port(काष्ठा fc_port *fcport)
अणु
	पूर्णांक ret;

	अगर (!IS_ENABLED(CONFIG_NVME_FC))
		वापस;

	ql_log(ql_log_warn, शून्य, 0x2112,
	    "%s: unregister remoteport on %p %8phN\n",
	    __func__, fcport, fcport->port_name);

	अगर (test_bit(PFLG_DRIVER_REMOVING, &fcport->vha->pci_flags))
		nvme_fc_set_remoteport_devloss(fcport->nvme_remote_port, 0);

	init_completion(&fcport->nvme_del_करोne);
	ret = nvme_fc_unरेजिस्टर_remoteport(fcport->nvme_remote_port);
	अगर (ret)
		ql_log(ql_log_info, fcport->vha, 0x2114,
			"%s: Failed to unregister nvme_remote_port (%d)\n",
			    __func__, ret);
	रुको_क्रम_completion(&fcport->nvme_del_करोne);
पूर्ण

व्योम qla_nvme_delete(काष्ठा scsi_qla_host *vha)
अणु
	पूर्णांक nv_ret;

	अगर (!IS_ENABLED(CONFIG_NVME_FC))
		वापस;

	अगर (vha->nvme_local_port) अणु
		init_completion(&vha->nvme_del_करोne);
		ql_log(ql_log_info, vha, 0x2116,
			"unregister localport=%p\n",
			vha->nvme_local_port);
		nv_ret = nvme_fc_unरेजिस्टर_localport(vha->nvme_local_port);
		अगर (nv_ret)
			ql_log(ql_log_info, vha, 0x2115,
			    "Unregister of localport failed\n");
		अन्यथा
			रुको_क्रम_completion(&vha->nvme_del_करोne);
	पूर्ण
पूर्ण

पूर्णांक qla_nvme_रेजिस्टर_hba(काष्ठा scsi_qla_host *vha)
अणु
	काष्ठा nvme_fc_port_ढाँचा *पंचांगpl;
	काष्ठा qla_hw_data *ha;
	काष्ठा nvme_fc_port_info pinfo;
	पूर्णांक ret = -EINVAL;

	अगर (!IS_ENABLED(CONFIG_NVME_FC))
		वापस ret;

	ha = vha->hw;
	पंचांगpl = &qla_nvme_fc_transport;

	WARN_ON(vha->nvme_local_port);

	अगर (ha->max_req_queues < 3) अणु
		अगर (!ha->flags.max_req_queue_warned)
			ql_log(ql_log_info, vha, 0x2120,
			       "%s: Disabling FC-NVME due to lack of free queue pairs (%d).\n",
			       __func__, ha->max_req_queues);
		ha->flags.max_req_queue_warned = 1;
		वापस ret;
	पूर्ण

	qla_nvme_fc_transport.max_hw_queues =
	    min((uपूर्णांक8_t)(qla_nvme_fc_transport.max_hw_queues),
		(uपूर्णांक8_t)(ha->max_req_queues - 2));

	pinfo.node_name = wwn_to_u64(vha->node_name);
	pinfo.port_name = wwn_to_u64(vha->port_name);
	pinfo.port_role = FC_PORT_ROLE_NVME_INITIATOR;
	pinfo.port_id = vha->d_id.b24;

	ql_log(ql_log_info, vha, 0xffff,
	    "register_localport: host-traddr=nn-0x%llx:pn-0x%llx on portID:%x\n",
	    pinfo.node_name, pinfo.port_name, pinfo.port_id);
	qla_nvme_fc_transport.dma_boundary = vha->host->dma_boundary;

	ret = nvme_fc_रेजिस्टर_localport(&pinfo, पंचांगpl,
	    get_device(&ha->pdev->dev), &vha->nvme_local_port);
	अगर (ret) अणु
		ql_log(ql_log_warn, vha, 0xffff,
		    "register_localport failed: ret=%x\n", ret);
	पूर्ण अन्यथा अणु
		vha->nvme_local_port->निजी = vha;
	पूर्ण

	वापस ret;
पूर्ण

व्योम qla_nvme_पात_set_option(काष्ठा पात_entry_24xx *abt, srb_t *orig_sp)
अणु
	काष्ठा qla_hw_data *ha;

	अगर (!(ql2xabts_रुको_nvme && QLA_ABTS_WAIT_ENABLED(orig_sp)))
		वापस;

	ha = orig_sp->fcport->vha->hw;

	WARN_ON_ONCE(abt->options & cpu_to_le16(BIT_0));
	/* Use Driver Specअगरied Retry Count */
	abt->options |= cpu_to_le16(AOF_ABTS_RTY_CNT);
	abt->drv.abts_rty_cnt = cpu_to_le16(2);
	/* Use specअगरied response समयout */
	abt->options |= cpu_to_le16(AOF_RSP_TIMEOUT);
	/* set it to 2 * r_a_tov in secs */
	abt->drv.rsp_समयout = cpu_to_le16(2 * (ha->r_a_tov / 10));
पूर्ण

व्योम qla_nvme_पात_process_comp_status(काष्ठा पात_entry_24xx *abt, srb_t *orig_sp)
अणु
	u16	comp_status;
	काष्ठा scsi_qla_host *vha;

	अगर (!(ql2xabts_रुको_nvme && QLA_ABTS_WAIT_ENABLED(orig_sp)))
		वापस;

	vha = orig_sp->fcport->vha;

	comp_status = le16_to_cpu(abt->comp_status);
	चयन (comp_status) अणु
	हाल CS_RESET:		/* reset event पातed */
	हाल CS_ABORTED:	/* IOCB was cleaned */
	/* N_Port handle is not currently logged in */
	हाल CS_TIMEOUT:
	/* N_Port handle was logged out जबतक रुकोing क्रम ABTS to complete */
	हाल CS_PORT_UNAVAILABLE:
	/* Firmware found that the port name changed */
	हाल CS_PORT_LOGGED_OUT:
	/* BA_RJT was received क्रम the ABTS */
	हाल CS_PORT_CONFIG_CHG:
		ql_dbg(ql_dbg_async + ql_dbg_mbx, vha, 0xf09d,
		       "Abort I/O IOCB completed with error, comp_status=%x\n",
		comp_status);
		अवरोध;

	/* BA_RJT was received क्रम the ABTS */
	हाल CS_REJECT_RECEIVED:
		ql_dbg(ql_dbg_async + ql_dbg_mbx, vha, 0xf09e,
		       "BA_RJT was received for the ABTS rjt_vendorUnique = %u",
			abt->fw.ba_rjt_venकरोrUnique);
		ql_dbg(ql_dbg_async + ql_dbg_mbx, vha, 0xf09e,
		       "ba_rjt_reasonCodeExpl = %u, ba_rjt_reasonCode = %u\n",
		       abt->fw.ba_rjt_reasonCodeExpl, abt->fw.ba_rjt_reasonCode);
		अवरोध;

	हाल CS_COMPLETE:
		ql_dbg(ql_dbg_async + ql_dbg_mbx, vha, 0xf09f,
		       "IOCB request is completed successfully comp_status=%x\n",
		comp_status);
		अवरोध;

	हाल CS_IOCB_ERROR:
		ql_dbg(ql_dbg_async + ql_dbg_mbx, vha, 0xf0a0,
		       "IOCB request is failed, comp_status=%x\n", comp_status);
		अवरोध;

	शेष:
		ql_dbg(ql_dbg_async + ql_dbg_mbx, vha, 0xf0a1,
		       "Invalid Abort IO IOCB Completion Status %x\n",
		comp_status);
		अवरोध;
	पूर्ण
पूर्ण

अंतरभूत व्योम qla_रुको_nvme_release_cmd_kref(srb_t *orig_sp)
अणु
	अगर (!(ql2xabts_रुको_nvme && QLA_ABTS_WAIT_ENABLED(orig_sp)))
		वापस;
	kref_put(&orig_sp->cmd_kref, orig_sp->put_fn);
पूर्ण
