<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * QLogic Fibre Channel HBA Driver
 * Copyright (c)  2003-2014 QLogic Corporation
 */
#समावेश "qla_def.h"
#समावेश "qla_gbl.h"

#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/delay.h>
#समावेश <linux/bsg-lib.h>

अटल व्योम qla2xxx_मुक्त_fcport_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा fc_port *fcport = container_of(work, typeof(*fcport),
	    मुक्त_work);

	qla2x00_मुक्त_fcport(fcport);
पूर्ण

/* BSG support क्रम ELS/CT pass through */
व्योम qla2x00_bsg_job_करोne(srb_t *sp, पूर्णांक res)
अणु
	काष्ठा bsg_job *bsg_job = sp->u.bsg_job;
	काष्ठा fc_bsg_reply *bsg_reply = bsg_job->reply;

	sp->मुक्त(sp);

	bsg_reply->result = res;
	bsg_job_करोne(bsg_job, bsg_reply->result,
		       bsg_reply->reply_payload_rcv_len);
पूर्ण

व्योम qla2x00_bsg_sp_मुक्त(srb_t *sp)
अणु
	काष्ठा qla_hw_data *ha = sp->vha->hw;
	काष्ठा bsg_job *bsg_job = sp->u.bsg_job;
	काष्ठा fc_bsg_request *bsg_request = bsg_job->request;
	काष्ठा qla_mt_iocb_rqst_fx00 *piocb_rqst;

	अगर (sp->type == SRB_FXIOCB_BCMD) अणु
		piocb_rqst = (काष्ठा qla_mt_iocb_rqst_fx00 *)
		    &bsg_request->rqst_data.h_venकरोr.venकरोr_cmd[1];

		अगर (piocb_rqst->flags & SRB_FXDISC_REQ_DMA_VALID)
			dma_unmap_sg(&ha->pdev->dev,
			    bsg_job->request_payload.sg_list,
			    bsg_job->request_payload.sg_cnt, DMA_TO_DEVICE);

		अगर (piocb_rqst->flags & SRB_FXDISC_RESP_DMA_VALID)
			dma_unmap_sg(&ha->pdev->dev,
			    bsg_job->reply_payload.sg_list,
			    bsg_job->reply_payload.sg_cnt, DMA_FROM_DEVICE);
	पूर्ण अन्यथा अणु
		dma_unmap_sg(&ha->pdev->dev, bsg_job->request_payload.sg_list,
		    bsg_job->request_payload.sg_cnt, DMA_TO_DEVICE);

		dma_unmap_sg(&ha->pdev->dev, bsg_job->reply_payload.sg_list,
		    bsg_job->reply_payload.sg_cnt, DMA_FROM_DEVICE);
	पूर्ण

	अगर (sp->type == SRB_CT_CMD ||
	    sp->type == SRB_FXIOCB_BCMD ||
	    sp->type == SRB_ELS_CMD_HST) अणु
		INIT_WORK(&sp->fcport->मुक्त_work, qla2xxx_मुक्त_fcport_work);
		queue_work(ha->wq, &sp->fcport->मुक्त_work);
	पूर्ण

	qla2x00_rel_sp(sp);
पूर्ण

पूर्णांक
qla24xx_fcp_prio_cfg_valid(scsi_qla_host_t *vha,
	काष्ठा qla_fcp_prio_cfg *pri_cfg, uपूर्णांक8_t flag)
अणु
	पूर्णांक i, ret, num_valid;
	uपूर्णांक8_t *bcode;
	काष्ठा qla_fcp_prio_entry *pri_entry;
	uपूर्णांक32_t *bcode_val_ptr, bcode_val;

	ret = 1;
	num_valid = 0;
	bcode = (uपूर्णांक8_t *)pri_cfg;
	bcode_val_ptr = (uपूर्णांक32_t *)pri_cfg;
	bcode_val = (uपूर्णांक32_t)(*bcode_val_ptr);

	अगर (bcode_val == 0xFFFFFFFF) अणु
		/* No FCP Priority config data in flash */
		ql_dbg(ql_dbg_user, vha, 0x7051,
		    "No FCP Priority config data.\n");
		वापस 0;
	पूर्ण

	अगर (स_भेद(bcode, "HQOS", 4)) अणु
		/* Invalid FCP priority data header*/
		ql_dbg(ql_dbg_user, vha, 0x7052,
		    "Invalid FCP Priority data header. bcode=0x%x.\n",
		    bcode_val);
		वापस 0;
	पूर्ण
	अगर (flag != 1)
		वापस ret;

	pri_entry = &pri_cfg->entry[0];
	क्रम (i = 0; i < pri_cfg->num_entries; i++) अणु
		अगर (pri_entry->flags & FCP_PRIO_ENTRY_TAG_VALID)
			num_valid++;
		pri_entry++;
	पूर्ण

	अगर (num_valid == 0) अणु
		/* No valid FCP priority data entries */
		ql_dbg(ql_dbg_user, vha, 0x7053,
		    "No valid FCP Priority data entries.\n");
		ret = 0;
	पूर्ण अन्यथा अणु
		/* FCP priority data is valid */
		ql_dbg(ql_dbg_user, vha, 0x7054,
		    "Valid FCP priority data. num entries = %d.\n",
		    num_valid);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक
qla24xx_proc_fcp_prio_cfg_cmd(काष्ठा bsg_job *bsg_job)
अणु
	काष्ठा Scsi_Host *host = fc_bsg_to_shost(bsg_job);
	काष्ठा fc_bsg_request *bsg_request = bsg_job->request;
	काष्ठा fc_bsg_reply *bsg_reply = bsg_job->reply;
	scsi_qla_host_t *vha = shost_priv(host);
	काष्ठा qla_hw_data *ha = vha->hw;
	पूर्णांक ret = 0;
	uपूर्णांक32_t len;
	uपूर्णांक32_t oper;

	अगर (!(IS_QLA24XX_TYPE(ha) || IS_QLA25XX(ha) || IS_P3P_TYPE(ha))) अणु
		ret = -EINVAL;
		जाओ निकास_fcp_prio_cfg;
	पूर्ण

	/* Get the sub command */
	oper = bsg_request->rqst_data.h_venकरोr.venकरोr_cmd[1];

	/* Only set config is allowed अगर config memory is not allocated */
	अगर (!ha->fcp_prio_cfg && (oper != QLFC_FCP_PRIO_SET_CONFIG)) अणु
		ret = -EINVAL;
		जाओ निकास_fcp_prio_cfg;
	पूर्ण
	चयन (oper) अणु
	हाल QLFC_FCP_PRIO_DISABLE:
		अगर (ha->flags.fcp_prio_enabled) अणु
			ha->flags.fcp_prio_enabled = 0;
			ha->fcp_prio_cfg->attributes &=
				~FCP_PRIO_ATTR_ENABLE;
			qla24xx_update_all_fcp_prio(vha);
			bsg_reply->result = DID_OK;
		पूर्ण अन्यथा अणु
			ret = -EINVAL;
			bsg_reply->result = (DID_ERROR << 16);
			जाओ निकास_fcp_prio_cfg;
		पूर्ण
		अवरोध;

	हाल QLFC_FCP_PRIO_ENABLE:
		अगर (!ha->flags.fcp_prio_enabled) अणु
			अगर (ha->fcp_prio_cfg) अणु
				ha->flags.fcp_prio_enabled = 1;
				ha->fcp_prio_cfg->attributes |=
				    FCP_PRIO_ATTR_ENABLE;
				qla24xx_update_all_fcp_prio(vha);
				bsg_reply->result = DID_OK;
			पूर्ण अन्यथा अणु
				ret = -EINVAL;
				bsg_reply->result = (DID_ERROR << 16);
				जाओ निकास_fcp_prio_cfg;
			पूर्ण
		पूर्ण
		अवरोध;

	हाल QLFC_FCP_PRIO_GET_CONFIG:
		len = bsg_job->reply_payload.payload_len;
		अगर (!len || len > FCP_PRIO_CFG_SIZE) अणु
			ret = -EINVAL;
			bsg_reply->result = (DID_ERROR << 16);
			जाओ निकास_fcp_prio_cfg;
		पूर्ण

		bsg_reply->result = DID_OK;
		bsg_reply->reply_payload_rcv_len =
			sg_copy_from_buffer(
			bsg_job->reply_payload.sg_list,
			bsg_job->reply_payload.sg_cnt, ha->fcp_prio_cfg,
			len);

		अवरोध;

	हाल QLFC_FCP_PRIO_SET_CONFIG:
		len = bsg_job->request_payload.payload_len;
		अगर (!len || len > FCP_PRIO_CFG_SIZE) अणु
			bsg_reply->result = (DID_ERROR << 16);
			ret = -EINVAL;
			जाओ निकास_fcp_prio_cfg;
		पूर्ण

		अगर (!ha->fcp_prio_cfg) अणु
			ha->fcp_prio_cfg = vदो_स्मृति(FCP_PRIO_CFG_SIZE);
			अगर (!ha->fcp_prio_cfg) अणु
				ql_log(ql_log_warn, vha, 0x7050,
				    "Unable to allocate memory for fcp prio "
				    "config data (%x).\n", FCP_PRIO_CFG_SIZE);
				bsg_reply->result = (DID_ERROR << 16);
				ret = -ENOMEM;
				जाओ निकास_fcp_prio_cfg;
			पूर्ण
		पूर्ण

		स_रखो(ha->fcp_prio_cfg, 0, FCP_PRIO_CFG_SIZE);
		sg_copy_to_buffer(bsg_job->request_payload.sg_list,
		bsg_job->request_payload.sg_cnt, ha->fcp_prio_cfg,
			FCP_PRIO_CFG_SIZE);

		/* validate fcp priority data */

		अगर (!qla24xx_fcp_prio_cfg_valid(vha, ha->fcp_prio_cfg, 1)) अणु
			bsg_reply->result = (DID_ERROR << 16);
			ret = -EINVAL;
			/* If buffer was invalidatic पूर्णांक
			 * fcp_prio_cfg is of no use
			 */
			vमुक्त(ha->fcp_prio_cfg);
			ha->fcp_prio_cfg = शून्य;
			जाओ निकास_fcp_prio_cfg;
		पूर्ण

		ha->flags.fcp_prio_enabled = 0;
		अगर (ha->fcp_prio_cfg->attributes & FCP_PRIO_ATTR_ENABLE)
			ha->flags.fcp_prio_enabled = 1;
		qla24xx_update_all_fcp_prio(vha);
		bsg_reply->result = DID_OK;
		अवरोध;
	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण
निकास_fcp_prio_cfg:
	अगर (!ret)
		bsg_job_करोne(bsg_job, bsg_reply->result,
			       bsg_reply->reply_payload_rcv_len);
	वापस ret;
पूर्ण

अटल पूर्णांक
qla2x00_process_els(काष्ठा bsg_job *bsg_job)
अणु
	काष्ठा fc_bsg_request *bsg_request = bsg_job->request;
	काष्ठा fc_rport *rport;
	fc_port_t *fcport = शून्य;
	काष्ठा Scsi_Host *host;
	scsi_qla_host_t *vha;
	काष्ठा qla_hw_data *ha;
	srb_t *sp;
	स्थिर अक्षर *type;
	पूर्णांक req_sg_cnt, rsp_sg_cnt;
	पूर्णांक rval =  (DID_ERROR << 16);
	uपूर्णांक16_t nextlid = 0;

	अगर (bsg_request->msgcode == FC_BSG_RPT_ELS) अणु
		rport = fc_bsg_to_rport(bsg_job);
		fcport = *(fc_port_t **) rport->dd_data;
		host = rport_to_shost(rport);
		vha = shost_priv(host);
		ha = vha->hw;
		type = "FC_BSG_RPT_ELS";
	पूर्ण अन्यथा अणु
		host = fc_bsg_to_shost(bsg_job);
		vha = shost_priv(host);
		ha = vha->hw;
		type = "FC_BSG_HST_ELS_NOLOGIN";
	पूर्ण

	अगर (!vha->flags.online) अणु
		ql_log(ql_log_warn, vha, 0x7005, "Host not online.\n");
		rval = -EIO;
		जाओ करोne;
	पूर्ण

	/* pass through is supported only क्रम ISP 4Gb or higher */
	अगर (!IS_FWI2_CAPABLE(ha)) अणु
		ql_dbg(ql_dbg_user, vha, 0x7001,
		    "ELS passthru not supported for ISP23xx based adapters.\n");
		rval = -EPERM;
		जाओ करोne;
	पूर्ण

	/*  Multiple SG's are not supported क्रम ELS requests */
	अगर (bsg_job->request_payload.sg_cnt > 1 ||
		bsg_job->reply_payload.sg_cnt > 1) अणु
		ql_dbg(ql_dbg_user, vha, 0x7002,
		    "Multiple SG's are not supported for ELS requests, "
		    "request_sg_cnt=%x reply_sg_cnt=%x.\n",
		    bsg_job->request_payload.sg_cnt,
		    bsg_job->reply_payload.sg_cnt);
		rval = -EPERM;
		जाओ करोne;
	पूर्ण

	/* ELS request क्रम rport */
	अगर (bsg_request->msgcode == FC_BSG_RPT_ELS) अणु
		/* make sure the rport is logged in,
		 * अगर not perक्रमm fabric login
		 */
		अगर (qla2x00_fabric_login(vha, fcport, &nextlid)) अणु
			ql_dbg(ql_dbg_user, vha, 0x7003,
			    "Failed to login port %06X for ELS passthru.\n",
			    fcport->d_id.b24);
			rval = -EIO;
			जाओ करोne;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Allocate a dummy fcport काष्ठाure, since functions
		 * preparing the IOCB and mailbox command retrieves port
		 * specअगरic inक्रमmation from fcport काष्ठाure. For Host based
		 * ELS commands there will be no fcport काष्ठाure allocated
		 */
		fcport = qla2x00_alloc_fcport(vha, GFP_KERNEL);
		अगर (!fcport) अणु
			rval = -ENOMEM;
			जाओ करोne;
		पूर्ण

		/* Initialize all required  fields of fcport */
		fcport->vha = vha;
		fcport->d_id.b.al_pa =
			bsg_request->rqst_data.h_els.port_id[0];
		fcport->d_id.b.area =
			bsg_request->rqst_data.h_els.port_id[1];
		fcport->d_id.b.करोमुख्य =
			bsg_request->rqst_data.h_els.port_id[2];
		fcport->loop_id =
			(fcport->d_id.b.al_pa == 0xFD) ?
			NPH_FABRIC_CONTROLLER : NPH_F_PORT;
	पूर्ण

	req_sg_cnt =
		dma_map_sg(&ha->pdev->dev, bsg_job->request_payload.sg_list,
		bsg_job->request_payload.sg_cnt, DMA_TO_DEVICE);
	अगर (!req_sg_cnt) अणु
		dma_unmap_sg(&ha->pdev->dev, bsg_job->request_payload.sg_list,
		    bsg_job->request_payload.sg_cnt, DMA_TO_DEVICE);
		rval = -ENOMEM;
		जाओ करोne_मुक्त_fcport;
	पूर्ण

	rsp_sg_cnt = dma_map_sg(&ha->pdev->dev, bsg_job->reply_payload.sg_list,
		bsg_job->reply_payload.sg_cnt, DMA_FROM_DEVICE);
        अगर (!rsp_sg_cnt) अणु
		dma_unmap_sg(&ha->pdev->dev, bsg_job->reply_payload.sg_list,
		    bsg_job->reply_payload.sg_cnt, DMA_FROM_DEVICE);
		rval = -ENOMEM;
		जाओ करोne_मुक्त_fcport;
	पूर्ण

	अगर ((req_sg_cnt !=  bsg_job->request_payload.sg_cnt) ||
		(rsp_sg_cnt != bsg_job->reply_payload.sg_cnt)) अणु
		ql_log(ql_log_warn, vha, 0x7008,
		    "dma mapping resulted in different sg counts, "
		    "request_sg_cnt: %x dma_request_sg_cnt:%x reply_sg_cnt:%x "
		    "dma_reply_sg_cnt:%x.\n", bsg_job->request_payload.sg_cnt,
		    req_sg_cnt, bsg_job->reply_payload.sg_cnt, rsp_sg_cnt);
		rval = -EAGAIN;
		जाओ करोne_unmap_sg;
	पूर्ण

	/* Alloc SRB काष्ठाure */
	sp = qla2x00_get_sp(vha, fcport, GFP_KERNEL);
	अगर (!sp) अणु
		rval = -ENOMEM;
		जाओ करोne_unmap_sg;
	पूर्ण

	sp->type =
		(bsg_request->msgcode == FC_BSG_RPT_ELS ?
		 SRB_ELS_CMD_RPT : SRB_ELS_CMD_HST);
	sp->name =
		(bsg_request->msgcode == FC_BSG_RPT_ELS ?
		 "bsg_els_rpt" : "bsg_els_hst");
	sp->u.bsg_job = bsg_job;
	sp->मुक्त = qla2x00_bsg_sp_मुक्त;
	sp->करोne = qla2x00_bsg_job_करोne;

	ql_dbg(ql_dbg_user, vha, 0x700a,
	    "bsg rqst type: %s els type: %x - loop-id=%x "
	    "portid=%-2x%02x%02x.\n", type,
	    bsg_request->rqst_data.h_els.command_code, fcport->loop_id,
	    fcport->d_id.b.करोमुख्य, fcport->d_id.b.area, fcport->d_id.b.al_pa);

	rval = qla2x00_start_sp(sp);
	अगर (rval != QLA_SUCCESS) अणु
		ql_log(ql_log_warn, vha, 0x700e,
		    "qla2x00_start_sp failed = %d\n", rval);
		qla2x00_rel_sp(sp);
		rval = -EIO;
		जाओ करोne_unmap_sg;
	पूर्ण
	वापस rval;

करोne_unmap_sg:
	dma_unmap_sg(&ha->pdev->dev, bsg_job->request_payload.sg_list,
		bsg_job->request_payload.sg_cnt, DMA_TO_DEVICE);
	dma_unmap_sg(&ha->pdev->dev, bsg_job->reply_payload.sg_list,
		bsg_job->reply_payload.sg_cnt, DMA_FROM_DEVICE);
	जाओ करोne_मुक्त_fcport;

करोne_मुक्त_fcport:
	अगर (bsg_request->msgcode == FC_BSG_RPT_ELS)
		qla2x00_मुक्त_fcport(fcport);
करोne:
	वापस rval;
पूर्ण

अटल अंतरभूत uपूर्णांक16_t
qla24xx_calc_ct_iocbs(uपूर्णांक16_t dsds)
अणु
	uपूर्णांक16_t iocbs;

	iocbs = 1;
	अगर (dsds > 2) अणु
		iocbs += (dsds - 2) / 5;
		अगर ((dsds - 2) % 5)
			iocbs++;
	पूर्ण
	वापस iocbs;
पूर्ण

अटल पूर्णांक
qla2x00_process_ct(काष्ठा bsg_job *bsg_job)
अणु
	srb_t *sp;
	काष्ठा fc_bsg_request *bsg_request = bsg_job->request;
	काष्ठा Scsi_Host *host = fc_bsg_to_shost(bsg_job);
	scsi_qla_host_t *vha = shost_priv(host);
	काष्ठा qla_hw_data *ha = vha->hw;
	पूर्णांक rval = (DID_ERROR << 16);
	पूर्णांक req_sg_cnt, rsp_sg_cnt;
	uपूर्णांक16_t loop_id;
	काष्ठा fc_port *fcport;
	अक्षर  *type = "FC_BSG_HST_CT";

	req_sg_cnt =
		dma_map_sg(&ha->pdev->dev, bsg_job->request_payload.sg_list,
			bsg_job->request_payload.sg_cnt, DMA_TO_DEVICE);
	अगर (!req_sg_cnt) अणु
		ql_log(ql_log_warn, vha, 0x700f,
		    "dma_map_sg return %d for request\n", req_sg_cnt);
		rval = -ENOMEM;
		जाओ करोne;
	पूर्ण

	rsp_sg_cnt = dma_map_sg(&ha->pdev->dev, bsg_job->reply_payload.sg_list,
		bsg_job->reply_payload.sg_cnt, DMA_FROM_DEVICE);
	अगर (!rsp_sg_cnt) अणु
		ql_log(ql_log_warn, vha, 0x7010,
		    "dma_map_sg return %d for reply\n", rsp_sg_cnt);
		rval = -ENOMEM;
		जाओ करोne;
	पूर्ण

	अगर ((req_sg_cnt !=  bsg_job->request_payload.sg_cnt) ||
	    (rsp_sg_cnt != bsg_job->reply_payload.sg_cnt)) अणु
		ql_log(ql_log_warn, vha, 0x7011,
		    "request_sg_cnt: %x dma_request_sg_cnt: %x reply_sg_cnt:%x "
		    "dma_reply_sg_cnt: %x\n", bsg_job->request_payload.sg_cnt,
		    req_sg_cnt, bsg_job->reply_payload.sg_cnt, rsp_sg_cnt);
		rval = -EAGAIN;
		जाओ करोne_unmap_sg;
	पूर्ण

	अगर (!vha->flags.online) अणु
		ql_log(ql_log_warn, vha, 0x7012,
		    "Host is not online.\n");
		rval = -EIO;
		जाओ करोne_unmap_sg;
	पूर्ण

	loop_id =
		(bsg_request->rqst_data.h_ct.preamble_word1 & 0xFF000000)
			>> 24;
	चयन (loop_id) अणु
	हाल 0xFC:
		loop_id = NPH_SNS;
		अवरोध;
	हाल 0xFA:
		loop_id = vha->mgmt_svr_loop_id;
		अवरोध;
	शेष:
		ql_dbg(ql_dbg_user, vha, 0x7013,
		    "Unknown loop id: %x.\n", loop_id);
		rval = -EINVAL;
		जाओ करोne_unmap_sg;
	पूर्ण

	/* Allocate a dummy fcport काष्ठाure, since functions preparing the
	 * IOCB and mailbox command retrieves port specअगरic inक्रमmation
	 * from fcport काष्ठाure. For Host based ELS commands there will be
	 * no fcport काष्ठाure allocated
	 */
	fcport = qla2x00_alloc_fcport(vha, GFP_KERNEL);
	अगर (!fcport) अणु
		ql_log(ql_log_warn, vha, 0x7014,
		    "Failed to allocate fcport.\n");
		rval = -ENOMEM;
		जाओ करोne_unmap_sg;
	पूर्ण

	/* Initialize all required  fields of fcport */
	fcport->vha = vha;
	fcport->d_id.b.al_pa = bsg_request->rqst_data.h_ct.port_id[0];
	fcport->d_id.b.area = bsg_request->rqst_data.h_ct.port_id[1];
	fcport->d_id.b.करोमुख्य = bsg_request->rqst_data.h_ct.port_id[2];
	fcport->loop_id = loop_id;

	/* Alloc SRB काष्ठाure */
	sp = qla2x00_get_sp(vha, fcport, GFP_KERNEL);
	अगर (!sp) अणु
		ql_log(ql_log_warn, vha, 0x7015,
		    "qla2x00_get_sp failed.\n");
		rval = -ENOMEM;
		जाओ करोne_मुक्त_fcport;
	पूर्ण

	sp->type = SRB_CT_CMD;
	sp->name = "bsg_ct";
	sp->iocbs = qla24xx_calc_ct_iocbs(req_sg_cnt + rsp_sg_cnt);
	sp->u.bsg_job = bsg_job;
	sp->मुक्त = qla2x00_bsg_sp_मुक्त;
	sp->करोne = qla2x00_bsg_job_करोne;

	ql_dbg(ql_dbg_user, vha, 0x7016,
	    "bsg rqst type: %s else type: %x - "
	    "loop-id=%x portid=%02x%02x%02x.\n", type,
	    (bsg_request->rqst_data.h_ct.preamble_word2 >> 16),
	    fcport->loop_id, fcport->d_id.b.करोमुख्य, fcport->d_id.b.area,
	    fcport->d_id.b.al_pa);

	rval = qla2x00_start_sp(sp);
	अगर (rval != QLA_SUCCESS) अणु
		ql_log(ql_log_warn, vha, 0x7017,
		    "qla2x00_start_sp failed=%d.\n", rval);
		qla2x00_rel_sp(sp);
		rval = -EIO;
		जाओ करोne_मुक्त_fcport;
	पूर्ण
	वापस rval;

करोne_मुक्त_fcport:
	qla2x00_मुक्त_fcport(fcport);
करोne_unmap_sg:
	dma_unmap_sg(&ha->pdev->dev, bsg_job->request_payload.sg_list,
		bsg_job->request_payload.sg_cnt, DMA_TO_DEVICE);
	dma_unmap_sg(&ha->pdev->dev, bsg_job->reply_payload.sg_list,
		bsg_job->reply_payload.sg_cnt, DMA_FROM_DEVICE);
करोne:
	वापस rval;
पूर्ण

/* Disable loopback mode */
अटल अंतरभूत पूर्णांक
qla81xx_reset_loopback_mode(scsi_qla_host_t *vha, uपूर्णांक16_t *config,
			    पूर्णांक रुको, पूर्णांक रुको2)
अणु
	पूर्णांक ret = 0;
	पूर्णांक rval = 0;
	uपूर्णांक16_t new_config[4];
	काष्ठा qla_hw_data *ha = vha->hw;

	अगर (!IS_QLA81XX(ha) && !IS_QLA8031(ha) && !IS_QLA8044(ha))
		जाओ करोne_reset_पूर्णांकernal;

	स_रखो(new_config, 0 , माप(new_config));
	अगर ((config[0] & INTERNAL_LOOPBACK_MASK) >> 1 ==
	    ENABLE_INTERNAL_LOOPBACK ||
	    (config[0] & INTERNAL_LOOPBACK_MASK) >> 1 ==
	    ENABLE_EXTERNAL_LOOPBACK) अणु
		new_config[0] = config[0] & ~INTERNAL_LOOPBACK_MASK;
		ql_dbg(ql_dbg_user, vha, 0x70bf, "new_config[0]=%02x\n",
		    (new_config[0] & INTERNAL_LOOPBACK_MASK));
		स_नकल(&new_config[1], &config[1], माप(uपूर्णांक16_t) * 3) ;

		ha->notअगरy_dcbx_comp = रुको;
		ha->notअगरy_lb_portup_comp = रुको2;

		ret = qla81xx_set_port_config(vha, new_config);
		अगर (ret != QLA_SUCCESS) अणु
			ql_log(ql_log_warn, vha, 0x7025,
			    "Set port config failed.\n");
			ha->notअगरy_dcbx_comp = 0;
			ha->notअगरy_lb_portup_comp = 0;
			rval = -EINVAL;
			जाओ करोne_reset_पूर्णांकernal;
		पूर्ण

		/* Wait क्रम DCBX complete event */
		अगर (रुको && !रुको_क्रम_completion_समयout(&ha->dcbx_comp,
			(DCBX_COMP_TIMEOUT * HZ))) अणु
			ql_dbg(ql_dbg_user, vha, 0x7026,
			    "DCBX completion not received.\n");
			ha->notअगरy_dcbx_comp = 0;
			ha->notअगरy_lb_portup_comp = 0;
			rval = -EINVAL;
			जाओ करोne_reset_पूर्णांकernal;
		पूर्ण अन्यथा
			ql_dbg(ql_dbg_user, vha, 0x7027,
			    "DCBX completion received.\n");

		अगर (रुको2 &&
		    !रुको_क्रम_completion_समयout(&ha->lb_portup_comp,
		    (LB_PORTUP_COMP_TIMEOUT * HZ))) अणु
			ql_dbg(ql_dbg_user, vha, 0x70c5,
			    "Port up completion not received.\n");
			ha->notअगरy_lb_portup_comp = 0;
			rval = -EINVAL;
			जाओ करोne_reset_पूर्णांकernal;
		पूर्ण अन्यथा
			ql_dbg(ql_dbg_user, vha, 0x70c6,
			    "Port up completion received.\n");

		ha->notअगरy_dcbx_comp = 0;
		ha->notअगरy_lb_portup_comp = 0;
	पूर्ण
करोne_reset_पूर्णांकernal:
	वापस rval;
पूर्ण

/*
 * Set the port configuration to enable the पूर्णांकernal or बाह्यal loopback
 * depending on the loopback mode.
 */
अटल अंतरभूत पूर्णांक
qla81xx_set_loopback_mode(scsi_qla_host_t *vha, uपूर्णांक16_t *config,
	uपूर्णांक16_t *new_config, uपूर्णांक16_t mode)
अणु
	पूर्णांक ret = 0;
	पूर्णांक rval = 0;
	अचिन्हित दीर्घ rem_पंचांगo = 0, current_पंचांगo = 0;
	काष्ठा qla_hw_data *ha = vha->hw;

	अगर (!IS_QLA81XX(ha) && !IS_QLA8031(ha) && !IS_QLA8044(ha))
		जाओ करोne_set_पूर्णांकernal;

	अगर (mode == INTERNAL_LOOPBACK)
		new_config[0] = config[0] | (ENABLE_INTERNAL_LOOPBACK << 1);
	अन्यथा अगर (mode == EXTERNAL_LOOPBACK)
		new_config[0] = config[0] | (ENABLE_EXTERNAL_LOOPBACK << 1);
	ql_dbg(ql_dbg_user, vha, 0x70be,
	     "new_config[0]=%02x\n", (new_config[0] & INTERNAL_LOOPBACK_MASK));

	स_नकल(&new_config[1], &config[1], माप(uपूर्णांक16_t) * 3);

	ha->notअगरy_dcbx_comp = 1;
	ret = qla81xx_set_port_config(vha, new_config);
	अगर (ret != QLA_SUCCESS) अणु
		ql_log(ql_log_warn, vha, 0x7021,
		    "set port config failed.\n");
		ha->notअगरy_dcbx_comp = 0;
		rval = -EINVAL;
		जाओ करोne_set_पूर्णांकernal;
	पूर्ण

	/* Wait क्रम DCBX complete event */
	current_पंचांगo = DCBX_COMP_TIMEOUT * HZ;
	जबतक (1) अणु
		rem_पंचांगo = रुको_क्रम_completion_समयout(&ha->dcbx_comp,
		    current_पंचांगo);
		अगर (!ha->idc_extend_पंचांगo || rem_पंचांगo) अणु
			ha->idc_extend_पंचांगo = 0;
			अवरोध;
		पूर्ण
		current_पंचांगo = ha->idc_extend_पंचांगo * HZ;
		ha->idc_extend_पंचांगo = 0;
	पूर्ण

	अगर (!rem_पंचांगo) अणु
		ql_dbg(ql_dbg_user, vha, 0x7022,
		    "DCBX completion not received.\n");
		ret = qla81xx_reset_loopback_mode(vha, new_config, 0, 0);
		/*
		 * If the reset of the loopback mode करोesn't work take a FCoE
		 * dump and reset the chip.
		 */
		अगर (ret) अणु
			qla2xxx_dump_fw(vha);
			set_bit(ISP_ABORT_NEEDED, &vha->dpc_flags);
		पूर्ण
		rval = -EINVAL;
	पूर्ण अन्यथा अणु
		अगर (ha->flags.idc_compl_status) अणु
			ql_dbg(ql_dbg_user, vha, 0x70c3,
			    "Bad status in IDC Completion AEN\n");
			rval = -EINVAL;
			ha->flags.idc_compl_status = 0;
		पूर्ण अन्यथा
			ql_dbg(ql_dbg_user, vha, 0x7023,
			    "DCBX completion received.\n");
	पूर्ण

	ha->notअगरy_dcbx_comp = 0;
	ha->idc_extend_पंचांगo = 0;

करोne_set_पूर्णांकernal:
	वापस rval;
पूर्ण

अटल पूर्णांक
qla2x00_process_loopback(काष्ठा bsg_job *bsg_job)
अणु
	काष्ठा fc_bsg_request *bsg_request = bsg_job->request;
	काष्ठा fc_bsg_reply *bsg_reply = bsg_job->reply;
	काष्ठा Scsi_Host *host = fc_bsg_to_shost(bsg_job);
	scsi_qla_host_t *vha = shost_priv(host);
	काष्ठा qla_hw_data *ha = vha->hw;
	पूर्णांक rval;
	uपूर्णांक8_t command_sent;
	अक्षर *type;
	काष्ठा msg_echo_lb elreq;
	uपूर्णांक16_t response[MAILBOX_REGISTER_COUNT];
	uपूर्णांक16_t config[4], new_config[4];
	uपूर्णांक8_t *fw_sts_ptr;
	व्योम *req_data = शून्य;
	dma_addr_t req_data_dma;
	uपूर्णांक32_t req_data_len;
	uपूर्णांक8_t *rsp_data = शून्य;
	dma_addr_t rsp_data_dma;
	uपूर्णांक32_t rsp_data_len;

	अगर (!vha->flags.online) अणु
		ql_log(ql_log_warn, vha, 0x7019, "Host is not online.\n");
		वापस -EIO;
	पूर्ण

	स_रखो(&elreq, 0, माप(elreq));

	elreq.req_sg_cnt = dma_map_sg(&ha->pdev->dev,
		bsg_job->request_payload.sg_list, bsg_job->request_payload.sg_cnt,
		DMA_TO_DEVICE);

	अगर (!elreq.req_sg_cnt) अणु
		ql_log(ql_log_warn, vha, 0x701a,
		    "dma_map_sg returned %d for request.\n", elreq.req_sg_cnt);
		वापस -ENOMEM;
	पूर्ण

	elreq.rsp_sg_cnt = dma_map_sg(&ha->pdev->dev,
		bsg_job->reply_payload.sg_list, bsg_job->reply_payload.sg_cnt,
		DMA_FROM_DEVICE);

	अगर (!elreq.rsp_sg_cnt) अणु
		ql_log(ql_log_warn, vha, 0x701b,
		    "dma_map_sg returned %d for reply.\n", elreq.rsp_sg_cnt);
		rval = -ENOMEM;
		जाओ करोne_unmap_req_sg;
	पूर्ण

	अगर ((elreq.req_sg_cnt !=  bsg_job->request_payload.sg_cnt) ||
		(elreq.rsp_sg_cnt != bsg_job->reply_payload.sg_cnt)) अणु
		ql_log(ql_log_warn, vha, 0x701c,
		    "dma mapping resulted in different sg counts, "
		    "request_sg_cnt: %x dma_request_sg_cnt: %x "
		    "reply_sg_cnt: %x dma_reply_sg_cnt: %x.\n",
		    bsg_job->request_payload.sg_cnt, elreq.req_sg_cnt,
		    bsg_job->reply_payload.sg_cnt, elreq.rsp_sg_cnt);
		rval = -EAGAIN;
		जाओ करोne_unmap_sg;
	पूर्ण
	req_data_len = rsp_data_len = bsg_job->request_payload.payload_len;
	req_data = dma_alloc_coherent(&ha->pdev->dev, req_data_len,
		&req_data_dma, GFP_KERNEL);
	अगर (!req_data) अणु
		ql_log(ql_log_warn, vha, 0x701d,
		    "dma alloc failed for req_data.\n");
		rval = -ENOMEM;
		जाओ करोne_unmap_sg;
	पूर्ण

	rsp_data = dma_alloc_coherent(&ha->pdev->dev, rsp_data_len,
		&rsp_data_dma, GFP_KERNEL);
	अगर (!rsp_data) अणु
		ql_log(ql_log_warn, vha, 0x7004,
		    "dma alloc failed for rsp_data.\n");
		rval = -ENOMEM;
		जाओ करोne_मुक्त_dma_req;
	पूर्ण

	/* Copy the request buffer in req_data now */
	sg_copy_to_buffer(bsg_job->request_payload.sg_list,
		bsg_job->request_payload.sg_cnt, req_data, req_data_len);

	elreq.send_dma = req_data_dma;
	elreq.rcv_dma = rsp_data_dma;
	elreq.transfer_size = req_data_len;

	elreq.options = bsg_request->rqst_data.h_venकरोr.venकरोr_cmd[1];
	elreq.iteration_count =
	    bsg_request->rqst_data.h_venकरोr.venकरोr_cmd[2];

	अगर (atomic_पढ़ो(&vha->loop_state) == LOOP_READY &&
	    ((ha->current_topology == ISP_CFG_F && (elreq.options & 7) >= 2) ||
	    ((IS_QLA81XX(ha) || IS_QLA8031(ha) || IS_QLA8044(ha)) &&
	    get_unaligned_le32(req_data) == ELS_OPCODE_BYTE &&
	    req_data_len == MAX_ELS_FRAME_PAYLOAD &&
	    elreq.options == EXTERNAL_LOOPBACK))) अणु
		type = "FC_BSG_HST_VENDOR_ECHO_DIAG";
		ql_dbg(ql_dbg_user, vha, 0x701e,
		    "BSG request type: %s.\n", type);
		command_sent = INT_DEF_LB_ECHO_CMD;
		rval = qla2x00_echo_test(vha, &elreq, response);
	पूर्ण अन्यथा अणु
		अगर (IS_QLA81XX(ha) || IS_QLA8031(ha) || IS_QLA8044(ha)) अणु
			स_रखो(config, 0, माप(config));
			स_रखो(new_config, 0, माप(new_config));

			अगर (qla81xx_get_port_config(vha, config)) अणु
				ql_log(ql_log_warn, vha, 0x701f,
				    "Get port config failed.\n");
				rval = -EPERM;
				जाओ करोne_मुक्त_dma_rsp;
			पूर्ण

			अगर ((config[0] & INTERNAL_LOOPBACK_MASK) != 0) अणु
				ql_dbg(ql_dbg_user, vha, 0x70c4,
				    "Loopback operation already in "
				    "progress.\n");
				rval = -EAGAIN;
				जाओ करोne_मुक्त_dma_rsp;
			पूर्ण

			ql_dbg(ql_dbg_user, vha, 0x70c0,
			    "elreq.options=%04x\n", elreq.options);

			अगर (elreq.options == EXTERNAL_LOOPBACK)
				अगर (IS_QLA8031(ha) || IS_QLA8044(ha))
					rval = qla81xx_set_loopback_mode(vha,
					    config, new_config, elreq.options);
				अन्यथा
					rval = qla81xx_reset_loopback_mode(vha,
					    config, 1, 0);
			अन्यथा
				rval = qla81xx_set_loopback_mode(vha, config,
				    new_config, elreq.options);

			अगर (rval) अणु
				rval = -EPERM;
				जाओ करोne_मुक्त_dma_rsp;
			पूर्ण

			type = "FC_BSG_HST_VENDOR_LOOPBACK";
			ql_dbg(ql_dbg_user, vha, 0x7028,
			    "BSG request type: %s.\n", type);

			command_sent = INT_DEF_LB_LOOPBACK_CMD;
			rval = qla2x00_loopback_test(vha, &elreq, response);

			अगर (response[0] == MBS_COMMAND_ERROR &&
					response[1] == MBS_LB_RESET) अणु
				ql_log(ql_log_warn, vha, 0x7029,
				    "MBX command error, Aborting ISP.\n");
				set_bit(ISP_ABORT_NEEDED, &vha->dpc_flags);
				qla2xxx_wake_dpc(vha);
				qla2x00_रुको_क्रम_chip_reset(vha);
				/* Also reset the MPI */
				अगर (IS_QLA81XX(ha)) अणु
					अगर (qla81xx_restart_mpi_firmware(vha) !=
					    QLA_SUCCESS) अणु
						ql_log(ql_log_warn, vha, 0x702a,
						    "MPI reset failed.\n");
					पूर्ण
				पूर्ण

				rval = -EIO;
				जाओ करोne_मुक्त_dma_rsp;
			पूर्ण

			अगर (new_config[0]) अणु
				पूर्णांक ret;

				/* Revert back to original port config
				 * Also clear पूर्णांकernal loopback
				 */
				ret = qla81xx_reset_loopback_mode(vha,
				    new_config, 0, 1);
				अगर (ret) अणु
					/*
					 * If the reset of the loopback mode
					 * करोesn't work take FCoE dump and then
					 * reset the chip.
					 */
					qla2xxx_dump_fw(vha);
					set_bit(ISP_ABORT_NEEDED,
					    &vha->dpc_flags);
				पूर्ण

			पूर्ण

		पूर्ण अन्यथा अणु
			type = "FC_BSG_HST_VENDOR_LOOPBACK";
			ql_dbg(ql_dbg_user, vha, 0x702b,
			    "BSG request type: %s.\n", type);
			command_sent = INT_DEF_LB_LOOPBACK_CMD;
			rval = qla2x00_loopback_test(vha, &elreq, response);
		पूर्ण
	पूर्ण

	अगर (rval) अणु
		ql_log(ql_log_warn, vha, 0x702c,
		    "Vendor request %s failed.\n", type);

		rval = 0;
		bsg_reply->result = (DID_ERROR << 16);
		bsg_reply->reply_payload_rcv_len = 0;
	पूर्ण अन्यथा अणु
		ql_dbg(ql_dbg_user, vha, 0x702d,
		    "Vendor request %s completed.\n", type);
		bsg_reply->result = (DID_OK << 16);
		sg_copy_from_buffer(bsg_job->reply_payload.sg_list,
			bsg_job->reply_payload.sg_cnt, rsp_data,
			rsp_data_len);
	पूर्ण

	bsg_job->reply_len = माप(काष्ठा fc_bsg_reply) +
	    माप(response) + माप(uपूर्णांक8_t);
	fw_sts_ptr = bsg_job->reply + माप(काष्ठा fc_bsg_reply);
	स_नकल(bsg_job->reply + माप(काष्ठा fc_bsg_reply), response,
			माप(response));
	fw_sts_ptr += माप(response);
	*fw_sts_ptr = command_sent;

करोne_मुक्त_dma_rsp:
	dma_मुक्त_coherent(&ha->pdev->dev, rsp_data_len,
		rsp_data, rsp_data_dma);
करोne_मुक्त_dma_req:
	dma_मुक्त_coherent(&ha->pdev->dev, req_data_len,
		req_data, req_data_dma);
करोne_unmap_sg:
	dma_unmap_sg(&ha->pdev->dev,
	    bsg_job->reply_payload.sg_list,
	    bsg_job->reply_payload.sg_cnt, DMA_FROM_DEVICE);
करोne_unmap_req_sg:
	dma_unmap_sg(&ha->pdev->dev,
	    bsg_job->request_payload.sg_list,
	    bsg_job->request_payload.sg_cnt, DMA_TO_DEVICE);
	अगर (!rval)
		bsg_job_करोne(bsg_job, bsg_reply->result,
			       bsg_reply->reply_payload_rcv_len);
	वापस rval;
पूर्ण

अटल पूर्णांक
qla84xx_reset(काष्ठा bsg_job *bsg_job)
अणु
	काष्ठा fc_bsg_request *bsg_request = bsg_job->request;
	काष्ठा Scsi_Host *host = fc_bsg_to_shost(bsg_job);
	काष्ठा fc_bsg_reply *bsg_reply = bsg_job->reply;
	scsi_qla_host_t *vha = shost_priv(host);
	काष्ठा qla_hw_data *ha = vha->hw;
	पूर्णांक rval = 0;
	uपूर्णांक32_t flag;

	अगर (!IS_QLA84XX(ha)) अणु
		ql_dbg(ql_dbg_user, vha, 0x702f, "Not 84xx, exiting.\n");
		वापस -EINVAL;
	पूर्ण

	flag = bsg_request->rqst_data.h_venकरोr.venकरोr_cmd[1];

	rval = qla84xx_reset_chip(vha, flag == A84_ISSUE_RESET_DIAG_FW);

	अगर (rval) अणु
		ql_log(ql_log_warn, vha, 0x7030,
		    "Vendor request 84xx reset failed.\n");
		rval = (DID_ERROR << 16);

	पूर्ण अन्यथा अणु
		ql_dbg(ql_dbg_user, vha, 0x7031,
		    "Vendor request 84xx reset completed.\n");
		bsg_reply->result = DID_OK;
		bsg_job_करोne(bsg_job, bsg_reply->result,
			       bsg_reply->reply_payload_rcv_len);
	पूर्ण

	वापस rval;
पूर्ण

अटल पूर्णांक
qla84xx_updatefw(काष्ठा bsg_job *bsg_job)
अणु
	काष्ठा fc_bsg_request *bsg_request = bsg_job->request;
	काष्ठा fc_bsg_reply *bsg_reply = bsg_job->reply;
	काष्ठा Scsi_Host *host = fc_bsg_to_shost(bsg_job);
	scsi_qla_host_t *vha = shost_priv(host);
	काष्ठा qla_hw_data *ha = vha->hw;
	काष्ठा verअगरy_chip_entry_84xx *mn = शून्य;
	dma_addr_t mn_dma, fw_dma;
	व्योम *fw_buf = शून्य;
	पूर्णांक rval = 0;
	uपूर्णांक32_t sg_cnt;
	uपूर्णांक32_t data_len;
	uपूर्णांक16_t options;
	uपूर्णांक32_t flag;
	uपूर्णांक32_t fw_ver;

	अगर (!IS_QLA84XX(ha)) अणु
		ql_dbg(ql_dbg_user, vha, 0x7032,
		    "Not 84xx, exiting.\n");
		वापस -EINVAL;
	पूर्ण

	sg_cnt = dma_map_sg(&ha->pdev->dev, bsg_job->request_payload.sg_list,
		bsg_job->request_payload.sg_cnt, DMA_TO_DEVICE);
	अगर (!sg_cnt) अणु
		ql_log(ql_log_warn, vha, 0x7033,
		    "dma_map_sg returned %d for request.\n", sg_cnt);
		वापस -ENOMEM;
	पूर्ण

	अगर (sg_cnt != bsg_job->request_payload.sg_cnt) अणु
		ql_log(ql_log_warn, vha, 0x7034,
		    "DMA mapping resulted in different sg counts, "
		    "request_sg_cnt: %x dma_request_sg_cnt: %x.\n",
		    bsg_job->request_payload.sg_cnt, sg_cnt);
		rval = -EAGAIN;
		जाओ करोne_unmap_sg;
	पूर्ण

	data_len = bsg_job->request_payload.payload_len;
	fw_buf = dma_alloc_coherent(&ha->pdev->dev, data_len,
		&fw_dma, GFP_KERNEL);
	अगर (!fw_buf) अणु
		ql_log(ql_log_warn, vha, 0x7035,
		    "DMA alloc failed for fw_buf.\n");
		rval = -ENOMEM;
		जाओ करोne_unmap_sg;
	पूर्ण

	sg_copy_to_buffer(bsg_job->request_payload.sg_list,
		bsg_job->request_payload.sg_cnt, fw_buf, data_len);

	mn = dma_pool_zalloc(ha->s_dma_pool, GFP_KERNEL, &mn_dma);
	अगर (!mn) अणु
		ql_log(ql_log_warn, vha, 0x7036,
		    "DMA alloc failed for fw buffer.\n");
		rval = -ENOMEM;
		जाओ करोne_मुक्त_fw_buf;
	पूर्ण

	flag = bsg_request->rqst_data.h_venकरोr.venकरोr_cmd[1];
	fw_ver = get_unaligned_le32((uपूर्णांक32_t *)fw_buf + 2);

	mn->entry_type = VERIFY_CHIP_IOCB_TYPE;
	mn->entry_count = 1;

	options = VCO_FORCE_UPDATE | VCO_END_OF_DATA;
	अगर (flag == A84_ISSUE_UPDATE_DIAGFW_CMD)
		options |= VCO_DIAG_FW;

	mn->options = cpu_to_le16(options);
	mn->fw_ver =  cpu_to_le32(fw_ver);
	mn->fw_size =  cpu_to_le32(data_len);
	mn->fw_seq_size =  cpu_to_le32(data_len);
	put_unaligned_le64(fw_dma, &mn->dsd.address);
	mn->dsd.length = cpu_to_le32(data_len);
	mn->data_seg_cnt = cpu_to_le16(1);

	rval = qla2x00_issue_iocb_समयout(vha, mn, mn_dma, 0, 120);

	अगर (rval) अणु
		ql_log(ql_log_warn, vha, 0x7037,
		    "Vendor request 84xx updatefw failed.\n");

		rval = (DID_ERROR << 16);
	पूर्ण अन्यथा अणु
		ql_dbg(ql_dbg_user, vha, 0x7038,
		    "Vendor request 84xx updatefw completed.\n");

		bsg_job->reply_len = माप(काष्ठा fc_bsg_reply);
		bsg_reply->result = DID_OK;
	पूर्ण

	dma_pool_मुक्त(ha->s_dma_pool, mn, mn_dma);

करोne_मुक्त_fw_buf:
	dma_मुक्त_coherent(&ha->pdev->dev, data_len, fw_buf, fw_dma);

करोne_unmap_sg:
	dma_unmap_sg(&ha->pdev->dev, bsg_job->request_payload.sg_list,
		bsg_job->request_payload.sg_cnt, DMA_TO_DEVICE);

	अगर (!rval)
		bsg_job_करोne(bsg_job, bsg_reply->result,
			       bsg_reply->reply_payload_rcv_len);
	वापस rval;
पूर्ण

अटल पूर्णांक
qla84xx_mgmt_cmd(काष्ठा bsg_job *bsg_job)
अणु
	काष्ठा fc_bsg_request *bsg_request = bsg_job->request;
	काष्ठा fc_bsg_reply *bsg_reply = bsg_job->reply;
	काष्ठा Scsi_Host *host = fc_bsg_to_shost(bsg_job);
	scsi_qla_host_t *vha = shost_priv(host);
	काष्ठा qla_hw_data *ha = vha->hw;
	काष्ठा access_chip_84xx *mn = शून्य;
	dma_addr_t mn_dma, mgmt_dma;
	व्योम *mgmt_b = शून्य;
	पूर्णांक rval = 0;
	काष्ठा qla_bsg_a84_mgmt *ql84_mgmt;
	uपूर्णांक32_t sg_cnt;
	uपूर्णांक32_t data_len = 0;
	uपूर्णांक32_t dma_direction = DMA_NONE;

	अगर (!IS_QLA84XX(ha)) अणु
		ql_log(ql_log_warn, vha, 0x703a,
		    "Not 84xx, exiting.\n");
		वापस -EINVAL;
	पूर्ण

	mn = dma_pool_zalloc(ha->s_dma_pool, GFP_KERNEL, &mn_dma);
	अगर (!mn) अणु
		ql_log(ql_log_warn, vha, 0x703c,
		    "DMA alloc failed for fw buffer.\n");
		वापस -ENOMEM;
	पूर्ण

	mn->entry_type = ACCESS_CHIP_IOCB_TYPE;
	mn->entry_count = 1;
	ql84_mgmt = (व्योम *)bsg_request + माप(काष्ठा fc_bsg_request);
	चयन (ql84_mgmt->mgmt.cmd) अणु
	हाल QLA84_MGMT_READ_MEM:
	हाल QLA84_MGMT_GET_INFO:
		sg_cnt = dma_map_sg(&ha->pdev->dev,
			bsg_job->reply_payload.sg_list,
			bsg_job->reply_payload.sg_cnt, DMA_FROM_DEVICE);
		अगर (!sg_cnt) अणु
			ql_log(ql_log_warn, vha, 0x703d,
			    "dma_map_sg returned %d for reply.\n", sg_cnt);
			rval = -ENOMEM;
			जाओ निकास_mgmt;
		पूर्ण

		dma_direction = DMA_FROM_DEVICE;

		अगर (sg_cnt != bsg_job->reply_payload.sg_cnt) अणु
			ql_log(ql_log_warn, vha, 0x703e,
			    "DMA mapping resulted in different sg counts, "
			    "reply_sg_cnt: %x dma_reply_sg_cnt: %x.\n",
			    bsg_job->reply_payload.sg_cnt, sg_cnt);
			rval = -EAGAIN;
			जाओ करोne_unmap_sg;
		पूर्ण

		data_len = bsg_job->reply_payload.payload_len;

		mgmt_b = dma_alloc_coherent(&ha->pdev->dev, data_len,
		    &mgmt_dma, GFP_KERNEL);
		अगर (!mgmt_b) अणु
			ql_log(ql_log_warn, vha, 0x703f,
			    "DMA alloc failed for mgmt_b.\n");
			rval = -ENOMEM;
			जाओ करोne_unmap_sg;
		पूर्ण

		अगर (ql84_mgmt->mgmt.cmd == QLA84_MGMT_READ_MEM) अणु
			mn->options = cpu_to_le16(ACO_DUMP_MEMORY);
			mn->parameter1 =
				cpu_to_le32(
				ql84_mgmt->mgmt.mgmtp.u.mem.start_addr);

		पूर्ण अन्यथा अगर (ql84_mgmt->mgmt.cmd == QLA84_MGMT_GET_INFO) अणु
			mn->options = cpu_to_le16(ACO_REQUEST_INFO);
			mn->parameter1 =
				cpu_to_le32(ql84_mgmt->mgmt.mgmtp.u.info.type);

			mn->parameter2 =
				cpu_to_le32(
				ql84_mgmt->mgmt.mgmtp.u.info.context);
		पूर्ण
		अवरोध;

	हाल QLA84_MGMT_WRITE_MEM:
		sg_cnt = dma_map_sg(&ha->pdev->dev,
			bsg_job->request_payload.sg_list,
			bsg_job->request_payload.sg_cnt, DMA_TO_DEVICE);

		अगर (!sg_cnt) अणु
			ql_log(ql_log_warn, vha, 0x7040,
			    "dma_map_sg returned %d.\n", sg_cnt);
			rval = -ENOMEM;
			जाओ निकास_mgmt;
		पूर्ण

		dma_direction = DMA_TO_DEVICE;

		अगर (sg_cnt != bsg_job->request_payload.sg_cnt) अणु
			ql_log(ql_log_warn, vha, 0x7041,
			    "DMA mapping resulted in different sg counts, "
			    "request_sg_cnt: %x dma_request_sg_cnt: %x.\n",
			    bsg_job->request_payload.sg_cnt, sg_cnt);
			rval = -EAGAIN;
			जाओ करोne_unmap_sg;
		पूर्ण

		data_len = bsg_job->request_payload.payload_len;
		mgmt_b = dma_alloc_coherent(&ha->pdev->dev, data_len,
			&mgmt_dma, GFP_KERNEL);
		अगर (!mgmt_b) अणु
			ql_log(ql_log_warn, vha, 0x7042,
			    "DMA alloc failed for mgmt_b.\n");
			rval = -ENOMEM;
			जाओ करोne_unmap_sg;
		पूर्ण

		sg_copy_to_buffer(bsg_job->request_payload.sg_list,
			bsg_job->request_payload.sg_cnt, mgmt_b, data_len);

		mn->options = cpu_to_le16(ACO_LOAD_MEMORY);
		mn->parameter1 =
			cpu_to_le32(ql84_mgmt->mgmt.mgmtp.u.mem.start_addr);
		अवरोध;

	हाल QLA84_MGMT_CHNG_CONFIG:
		mn->options = cpu_to_le16(ACO_CHANGE_CONFIG_PARAM);
		mn->parameter1 =
			cpu_to_le32(ql84_mgmt->mgmt.mgmtp.u.config.id);

		mn->parameter2 =
			cpu_to_le32(ql84_mgmt->mgmt.mgmtp.u.config.param0);

		mn->parameter3 =
			cpu_to_le32(ql84_mgmt->mgmt.mgmtp.u.config.param1);
		अवरोध;

	शेष:
		rval = -EIO;
		जाओ निकास_mgmt;
	पूर्ण

	अगर (ql84_mgmt->mgmt.cmd != QLA84_MGMT_CHNG_CONFIG) अणु
		mn->total_byte_cnt = cpu_to_le32(ql84_mgmt->mgmt.len);
		mn->dseg_count = cpu_to_le16(1);
		put_unaligned_le64(mgmt_dma, &mn->dsd.address);
		mn->dsd.length = cpu_to_le32(ql84_mgmt->mgmt.len);
	पूर्ण

	rval = qla2x00_issue_iocb(vha, mn, mn_dma, 0);

	अगर (rval) अणु
		ql_log(ql_log_warn, vha, 0x7043,
		    "Vendor request 84xx mgmt failed.\n");

		rval = (DID_ERROR << 16);

	पूर्ण अन्यथा अणु
		ql_dbg(ql_dbg_user, vha, 0x7044,
		    "Vendor request 84xx mgmt completed.\n");

		bsg_job->reply_len = माप(काष्ठा fc_bsg_reply);
		bsg_reply->result = DID_OK;

		अगर ((ql84_mgmt->mgmt.cmd == QLA84_MGMT_READ_MEM) ||
			(ql84_mgmt->mgmt.cmd == QLA84_MGMT_GET_INFO)) अणु
			bsg_reply->reply_payload_rcv_len =
				bsg_job->reply_payload.payload_len;

			sg_copy_from_buffer(bsg_job->reply_payload.sg_list,
				bsg_job->reply_payload.sg_cnt, mgmt_b,
				data_len);
		पूर्ण
	पूर्ण

करोne_unmap_sg:
	अगर (mgmt_b)
		dma_मुक्त_coherent(&ha->pdev->dev, data_len, mgmt_b, mgmt_dma);

	अगर (dma_direction == DMA_TO_DEVICE)
		dma_unmap_sg(&ha->pdev->dev, bsg_job->request_payload.sg_list,
			bsg_job->request_payload.sg_cnt, DMA_TO_DEVICE);
	अन्यथा अगर (dma_direction == DMA_FROM_DEVICE)
		dma_unmap_sg(&ha->pdev->dev, bsg_job->reply_payload.sg_list,
			bsg_job->reply_payload.sg_cnt, DMA_FROM_DEVICE);

निकास_mgmt:
	dma_pool_मुक्त(ha->s_dma_pool, mn, mn_dma);

	अगर (!rval)
		bsg_job_करोne(bsg_job, bsg_reply->result,
			       bsg_reply->reply_payload_rcv_len);
	वापस rval;
पूर्ण

अटल पूर्णांक
qla24xx_iidma(काष्ठा bsg_job *bsg_job)
अणु
	काष्ठा fc_bsg_request *bsg_request = bsg_job->request;
	काष्ठा fc_bsg_reply *bsg_reply = bsg_job->reply;
	काष्ठा Scsi_Host *host = fc_bsg_to_shost(bsg_job);
	scsi_qla_host_t *vha = shost_priv(host);
	पूर्णांक rval = 0;
	काष्ठा qla_port_param *port_param = शून्य;
	fc_port_t *fcport = शून्य;
	पूर्णांक found = 0;
	uपूर्णांक16_t mb[MAILBOX_REGISTER_COUNT];
	uपूर्णांक8_t *rsp_ptr = शून्य;

	अगर (!IS_IIDMA_CAPABLE(vha->hw)) अणु
		ql_log(ql_log_info, vha, 0x7046, "iiDMA not supported.\n");
		वापस -EINVAL;
	पूर्ण

	port_param = (व्योम *)bsg_request + माप(काष्ठा fc_bsg_request);
	अगर (port_param->fc_scsi_addr.dest_type != EXT_DEF_TYPE_WWPN) अणु
		ql_log(ql_log_warn, vha, 0x7048,
		    "Invalid destination type.\n");
		वापस -EINVAL;
	पूर्ण

	list_क्रम_each_entry(fcport, &vha->vp_fcports, list) अणु
		अगर (fcport->port_type != FCT_TARGET)
			जारी;

		अगर (स_भेद(port_param->fc_scsi_addr.dest_addr.wwpn,
			fcport->port_name, माप(fcport->port_name)))
			जारी;

		found = 1;
		अवरोध;
	पूर्ण

	अगर (!found) अणु
		ql_log(ql_log_warn, vha, 0x7049,
		    "Failed to find port.\n");
		वापस -EINVAL;
	पूर्ण

	अगर (atomic_पढ़ो(&fcport->state) != FCS_ONLINE) अणु
		ql_log(ql_log_warn, vha, 0x704a,
		    "Port is not online.\n");
		वापस -EINVAL;
	पूर्ण

	अगर (fcport->flags & FCF_LOGIN_NEEDED) अणु
		ql_log(ql_log_warn, vha, 0x704b,
		    "Remote port not logged in flags = 0x%x.\n", fcport->flags);
		वापस -EINVAL;
	पूर्ण

	अगर (port_param->mode)
		rval = qla2x00_set_idma_speed(vha, fcport->loop_id,
			port_param->speed, mb);
	अन्यथा
		rval = qla2x00_get_idma_speed(vha, fcport->loop_id,
			&port_param->speed, mb);

	अगर (rval) अणु
		ql_log(ql_log_warn, vha, 0x704c,
		    "iiDMA cmd failed for %8phN -- "
		    "%04x %x %04x %04x.\n", fcport->port_name,
		    rval, fcport->fp_speed, mb[0], mb[1]);
		rval = (DID_ERROR << 16);
	पूर्ण अन्यथा अणु
		अगर (!port_param->mode) अणु
			bsg_job->reply_len = माप(काष्ठा fc_bsg_reply) +
				माप(काष्ठा qla_port_param);

			rsp_ptr = ((uपूर्णांक8_t *)bsg_reply) +
				माप(काष्ठा fc_bsg_reply);

			स_नकल(rsp_ptr, port_param,
				माप(काष्ठा qla_port_param));
		पूर्ण

		bsg_reply->result = DID_OK;
		bsg_job_करोne(bsg_job, bsg_reply->result,
			       bsg_reply->reply_payload_rcv_len);
	पूर्ण

	वापस rval;
पूर्ण

अटल पूर्णांक
qla2x00_optrom_setup(काष्ठा bsg_job *bsg_job, scsi_qla_host_t *vha,
	uपूर्णांक8_t is_update)
अणु
	काष्ठा fc_bsg_request *bsg_request = bsg_job->request;
	uपूर्णांक32_t start = 0;
	पूर्णांक valid = 0;
	काष्ठा qla_hw_data *ha = vha->hw;

	अगर (unlikely(pci_channel_offline(ha->pdev)))
		वापस -EINVAL;

	start = bsg_request->rqst_data.h_venकरोr.venकरोr_cmd[1];
	अगर (start > ha->optrom_size) अणु
		ql_log(ql_log_warn, vha, 0x7055,
		    "start %d > optrom_size %d.\n", start, ha->optrom_size);
		वापस -EINVAL;
	पूर्ण

	अगर (ha->optrom_state != QLA_SWAITING) अणु
		ql_log(ql_log_info, vha, 0x7056,
		    "optrom_state %d.\n", ha->optrom_state);
		वापस -EBUSY;
	पूर्ण

	ha->optrom_region_start = start;
	ql_dbg(ql_dbg_user, vha, 0x7057, "is_update=%d.\n", is_update);
	अगर (is_update) अणु
		अगर (ha->optrom_size == OPTROM_SIZE_2300 && start == 0)
			valid = 1;
		अन्यथा अगर (start == (ha->flt_region_boot * 4) ||
		    start == (ha->flt_region_fw * 4))
			valid = 1;
		अन्यथा अगर (IS_QLA24XX_TYPE(ha) || IS_QLA25XX(ha) ||
		    IS_CNA_CAPABLE(ha) || IS_QLA2031(ha) || IS_QLA27XX(ha) ||
		    IS_QLA28XX(ha))
			valid = 1;
		अगर (!valid) अणु
			ql_log(ql_log_warn, vha, 0x7058,
			    "Invalid start region 0x%x/0x%x.\n", start,
			    bsg_job->request_payload.payload_len);
			वापस -EINVAL;
		पूर्ण

		ha->optrom_region_size = start +
		    bsg_job->request_payload.payload_len > ha->optrom_size ?
		    ha->optrom_size - start :
		    bsg_job->request_payload.payload_len;
		ha->optrom_state = QLA_SWRITING;
	पूर्ण अन्यथा अणु
		ha->optrom_region_size = start +
		    bsg_job->reply_payload.payload_len > ha->optrom_size ?
		    ha->optrom_size - start :
		    bsg_job->reply_payload.payload_len;
		ha->optrom_state = QLA_SREADING;
	पूर्ण

	ha->optrom_buffer = vzalloc(ha->optrom_region_size);
	अगर (!ha->optrom_buffer) अणु
		ql_log(ql_log_warn, vha, 0x7059,
		    "Read: Unable to allocate memory for optrom retrieval "
		    "(%x)\n", ha->optrom_region_size);

		ha->optrom_state = QLA_SWAITING;
		वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
qla2x00_पढ़ो_optrom(काष्ठा bsg_job *bsg_job)
अणु
	काष्ठा fc_bsg_reply *bsg_reply = bsg_job->reply;
	काष्ठा Scsi_Host *host = fc_bsg_to_shost(bsg_job);
	scsi_qla_host_t *vha = shost_priv(host);
	काष्ठा qla_hw_data *ha = vha->hw;
	पूर्णांक rval = 0;

	अगर (ha->flags.nic_core_reset_hdlr_active)
		वापस -EBUSY;

	mutex_lock(&ha->optrom_mutex);
	rval = qla2x00_optrom_setup(bsg_job, vha, 0);
	अगर (rval) अणु
		mutex_unlock(&ha->optrom_mutex);
		वापस rval;
	पूर्ण

	ha->isp_ops->पढ़ो_optrom(vha, ha->optrom_buffer,
	    ha->optrom_region_start, ha->optrom_region_size);

	sg_copy_from_buffer(bsg_job->reply_payload.sg_list,
	    bsg_job->reply_payload.sg_cnt, ha->optrom_buffer,
	    ha->optrom_region_size);

	bsg_reply->reply_payload_rcv_len = ha->optrom_region_size;
	bsg_reply->result = DID_OK;
	vमुक्त(ha->optrom_buffer);
	ha->optrom_buffer = शून्य;
	ha->optrom_state = QLA_SWAITING;
	mutex_unlock(&ha->optrom_mutex);
	bsg_job_करोne(bsg_job, bsg_reply->result,
		       bsg_reply->reply_payload_rcv_len);
	वापस rval;
पूर्ण

अटल पूर्णांक
qla2x00_update_optrom(काष्ठा bsg_job *bsg_job)
अणु
	काष्ठा fc_bsg_reply *bsg_reply = bsg_job->reply;
	काष्ठा Scsi_Host *host = fc_bsg_to_shost(bsg_job);
	scsi_qla_host_t *vha = shost_priv(host);
	काष्ठा qla_hw_data *ha = vha->hw;
	पूर्णांक rval = 0;

	mutex_lock(&ha->optrom_mutex);
	rval = qla2x00_optrom_setup(bsg_job, vha, 1);
	अगर (rval) अणु
		mutex_unlock(&ha->optrom_mutex);
		वापस rval;
	पूर्ण

	/* Set the isp82xx_no_md_cap not to capture minidump */
	ha->flags.isp82xx_no_md_cap = 1;

	sg_copy_to_buffer(bsg_job->request_payload.sg_list,
	    bsg_job->request_payload.sg_cnt, ha->optrom_buffer,
	    ha->optrom_region_size);

	rval = ha->isp_ops->ग_लिखो_optrom(vha, ha->optrom_buffer,
	    ha->optrom_region_start, ha->optrom_region_size);

	अगर (rval) अणु
		bsg_reply->result = -EINVAL;
		rval = -EINVAL;
	पूर्ण अन्यथा अणु
		bsg_reply->result = DID_OK;
	पूर्ण
	vमुक्त(ha->optrom_buffer);
	ha->optrom_buffer = शून्य;
	ha->optrom_state = QLA_SWAITING;
	mutex_unlock(&ha->optrom_mutex);
	bsg_job_करोne(bsg_job, bsg_reply->result,
		       bsg_reply->reply_payload_rcv_len);
	वापस rval;
पूर्ण

अटल पूर्णांक
qla2x00_update_fru_versions(काष्ठा bsg_job *bsg_job)
अणु
	काष्ठा fc_bsg_reply *bsg_reply = bsg_job->reply;
	काष्ठा Scsi_Host *host = fc_bsg_to_shost(bsg_job);
	scsi_qla_host_t *vha = shost_priv(host);
	काष्ठा qla_hw_data *ha = vha->hw;
	पूर्णांक rval = 0;
	uपूर्णांक8_t bsg[DMA_POOL_SIZE];
	काष्ठा qla_image_version_list *list = (व्योम *)bsg;
	काष्ठा qla_image_version *image;
	uपूर्णांक32_t count;
	dma_addr_t sfp_dma;
	व्योम *sfp = dma_pool_alloc(ha->s_dma_pool, GFP_KERNEL, &sfp_dma);

	अगर (!sfp) अणु
		bsg_reply->reply_data.venकरोr_reply.venकरोr_rsp[0] =
		    EXT_STATUS_NO_MEMORY;
		जाओ करोne;
	पूर्ण

	sg_copy_to_buffer(bsg_job->request_payload.sg_list,
	    bsg_job->request_payload.sg_cnt, list, माप(bsg));

	image = list->version;
	count = list->count;
	जबतक (count--) अणु
		स_नकल(sfp, &image->field_info, माप(image->field_info));
		rval = qla2x00_ग_लिखो_sfp(vha, sfp_dma, sfp,
		    image->field_address.device, image->field_address.offset,
		    माप(image->field_info), image->field_address.option);
		अगर (rval) अणु
			bsg_reply->reply_data.venकरोr_reply.venकरोr_rsp[0] =
			    EXT_STATUS_MAILBOX;
			जाओ dealloc;
		पूर्ण
		image++;
	पूर्ण

	bsg_reply->reply_data.venकरोr_reply.venकरोr_rsp[0] = 0;

dealloc:
	dma_pool_मुक्त(ha->s_dma_pool, sfp, sfp_dma);

करोne:
	bsg_job->reply_len = माप(काष्ठा fc_bsg_reply);
	bsg_reply->result = DID_OK << 16;
	bsg_job_करोne(bsg_job, bsg_reply->result,
		       bsg_reply->reply_payload_rcv_len);

	वापस 0;
पूर्ण

अटल पूर्णांक
qla2x00_पढ़ो_fru_status(काष्ठा bsg_job *bsg_job)
अणु
	काष्ठा fc_bsg_reply *bsg_reply = bsg_job->reply;
	काष्ठा Scsi_Host *host = fc_bsg_to_shost(bsg_job);
	scsi_qla_host_t *vha = shost_priv(host);
	काष्ठा qla_hw_data *ha = vha->hw;
	पूर्णांक rval = 0;
	uपूर्णांक8_t bsg[DMA_POOL_SIZE];
	काष्ठा qla_status_reg *sr = (व्योम *)bsg;
	dma_addr_t sfp_dma;
	uपूर्णांक8_t *sfp = dma_pool_alloc(ha->s_dma_pool, GFP_KERNEL, &sfp_dma);

	अगर (!sfp) अणु
		bsg_reply->reply_data.venकरोr_reply.venकरोr_rsp[0] =
		    EXT_STATUS_NO_MEMORY;
		जाओ करोne;
	पूर्ण

	sg_copy_to_buffer(bsg_job->request_payload.sg_list,
	    bsg_job->request_payload.sg_cnt, sr, माप(*sr));

	rval = qla2x00_पढ़ो_sfp(vha, sfp_dma, sfp,
	    sr->field_address.device, sr->field_address.offset,
	    माप(sr->status_reg), sr->field_address.option);
	sr->status_reg = *sfp;

	अगर (rval) अणु
		bsg_reply->reply_data.venकरोr_reply.venकरोr_rsp[0] =
		    EXT_STATUS_MAILBOX;
		जाओ dealloc;
	पूर्ण

	sg_copy_from_buffer(bsg_job->reply_payload.sg_list,
	    bsg_job->reply_payload.sg_cnt, sr, माप(*sr));

	bsg_reply->reply_data.venकरोr_reply.venकरोr_rsp[0] = 0;

dealloc:
	dma_pool_मुक्त(ha->s_dma_pool, sfp, sfp_dma);

करोne:
	bsg_job->reply_len = माप(काष्ठा fc_bsg_reply);
	bsg_reply->reply_payload_rcv_len = माप(*sr);
	bsg_reply->result = DID_OK << 16;
	bsg_job_करोne(bsg_job, bsg_reply->result,
		       bsg_reply->reply_payload_rcv_len);

	वापस 0;
पूर्ण

अटल पूर्णांक
qla2x00_ग_लिखो_fru_status(काष्ठा bsg_job *bsg_job)
अणु
	काष्ठा fc_bsg_reply *bsg_reply = bsg_job->reply;
	काष्ठा Scsi_Host *host = fc_bsg_to_shost(bsg_job);
	scsi_qla_host_t *vha = shost_priv(host);
	काष्ठा qla_hw_data *ha = vha->hw;
	पूर्णांक rval = 0;
	uपूर्णांक8_t bsg[DMA_POOL_SIZE];
	काष्ठा qla_status_reg *sr = (व्योम *)bsg;
	dma_addr_t sfp_dma;
	uपूर्णांक8_t *sfp = dma_pool_alloc(ha->s_dma_pool, GFP_KERNEL, &sfp_dma);

	अगर (!sfp) अणु
		bsg_reply->reply_data.venकरोr_reply.venकरोr_rsp[0] =
		    EXT_STATUS_NO_MEMORY;
		जाओ करोne;
	पूर्ण

	sg_copy_to_buffer(bsg_job->request_payload.sg_list,
	    bsg_job->request_payload.sg_cnt, sr, माप(*sr));

	*sfp = sr->status_reg;
	rval = qla2x00_ग_लिखो_sfp(vha, sfp_dma, sfp,
	    sr->field_address.device, sr->field_address.offset,
	    माप(sr->status_reg), sr->field_address.option);

	अगर (rval) अणु
		bsg_reply->reply_data.venकरोr_reply.venकरोr_rsp[0] =
		    EXT_STATUS_MAILBOX;
		जाओ dealloc;
	पूर्ण

	bsg_reply->reply_data.venकरोr_reply.venकरोr_rsp[0] = 0;

dealloc:
	dma_pool_मुक्त(ha->s_dma_pool, sfp, sfp_dma);

करोne:
	bsg_job->reply_len = माप(काष्ठा fc_bsg_reply);
	bsg_reply->result = DID_OK << 16;
	bsg_job_करोne(bsg_job, bsg_reply->result,
		       bsg_reply->reply_payload_rcv_len);

	वापस 0;
पूर्ण

अटल पूर्णांक
qla2x00_ग_लिखो_i2c(काष्ठा bsg_job *bsg_job)
अणु
	काष्ठा fc_bsg_reply *bsg_reply = bsg_job->reply;
	काष्ठा Scsi_Host *host = fc_bsg_to_shost(bsg_job);
	scsi_qla_host_t *vha = shost_priv(host);
	काष्ठा qla_hw_data *ha = vha->hw;
	पूर्णांक rval = 0;
	uपूर्णांक8_t bsg[DMA_POOL_SIZE];
	काष्ठा qla_i2c_access *i2c = (व्योम *)bsg;
	dma_addr_t sfp_dma;
	uपूर्णांक8_t *sfp = dma_pool_alloc(ha->s_dma_pool, GFP_KERNEL, &sfp_dma);

	अगर (!sfp) अणु
		bsg_reply->reply_data.venकरोr_reply.venकरोr_rsp[0] =
		    EXT_STATUS_NO_MEMORY;
		जाओ करोne;
	पूर्ण

	sg_copy_to_buffer(bsg_job->request_payload.sg_list,
	    bsg_job->request_payload.sg_cnt, i2c, माप(*i2c));

	स_नकल(sfp, i2c->buffer, i2c->length);
	rval = qla2x00_ग_लिखो_sfp(vha, sfp_dma, sfp,
	    i2c->device, i2c->offset, i2c->length, i2c->option);

	अगर (rval) अणु
		bsg_reply->reply_data.venकरोr_reply.venकरोr_rsp[0] =
		    EXT_STATUS_MAILBOX;
		जाओ dealloc;
	पूर्ण

	bsg_reply->reply_data.venकरोr_reply.venकरोr_rsp[0] = 0;

dealloc:
	dma_pool_मुक्त(ha->s_dma_pool, sfp, sfp_dma);

करोne:
	bsg_job->reply_len = माप(काष्ठा fc_bsg_reply);
	bsg_reply->result = DID_OK << 16;
	bsg_job_करोne(bsg_job, bsg_reply->result,
		       bsg_reply->reply_payload_rcv_len);

	वापस 0;
पूर्ण

अटल पूर्णांक
qla2x00_पढ़ो_i2c(काष्ठा bsg_job *bsg_job)
अणु
	काष्ठा fc_bsg_reply *bsg_reply = bsg_job->reply;
	काष्ठा Scsi_Host *host = fc_bsg_to_shost(bsg_job);
	scsi_qla_host_t *vha = shost_priv(host);
	काष्ठा qla_hw_data *ha = vha->hw;
	पूर्णांक rval = 0;
	uपूर्णांक8_t bsg[DMA_POOL_SIZE];
	काष्ठा qla_i2c_access *i2c = (व्योम *)bsg;
	dma_addr_t sfp_dma;
	uपूर्णांक8_t *sfp = dma_pool_alloc(ha->s_dma_pool, GFP_KERNEL, &sfp_dma);

	अगर (!sfp) अणु
		bsg_reply->reply_data.venकरोr_reply.venकरोr_rsp[0] =
		    EXT_STATUS_NO_MEMORY;
		जाओ करोne;
	पूर्ण

	sg_copy_to_buffer(bsg_job->request_payload.sg_list,
	    bsg_job->request_payload.sg_cnt, i2c, माप(*i2c));

	rval = qla2x00_पढ़ो_sfp(vha, sfp_dma, sfp,
		i2c->device, i2c->offset, i2c->length, i2c->option);

	अगर (rval) अणु
		bsg_reply->reply_data.venकरोr_reply.venकरोr_rsp[0] =
		    EXT_STATUS_MAILBOX;
		जाओ dealloc;
	पूर्ण

	स_नकल(i2c->buffer, sfp, i2c->length);
	sg_copy_from_buffer(bsg_job->reply_payload.sg_list,
	    bsg_job->reply_payload.sg_cnt, i2c, माप(*i2c));

	bsg_reply->reply_data.venकरोr_reply.venकरोr_rsp[0] = 0;

dealloc:
	dma_pool_मुक्त(ha->s_dma_pool, sfp, sfp_dma);

करोne:
	bsg_job->reply_len = माप(काष्ठा fc_bsg_reply);
	bsg_reply->reply_payload_rcv_len = माप(*i2c);
	bsg_reply->result = DID_OK << 16;
	bsg_job_करोne(bsg_job, bsg_reply->result,
		       bsg_reply->reply_payload_rcv_len);

	वापस 0;
पूर्ण

अटल पूर्णांक
qla24xx_process_bidir_cmd(काष्ठा bsg_job *bsg_job)
अणु
	काष्ठा fc_bsg_reply *bsg_reply = bsg_job->reply;
	काष्ठा Scsi_Host *host = fc_bsg_to_shost(bsg_job);
	scsi_qla_host_t *vha = shost_priv(host);
	काष्ठा qla_hw_data *ha = vha->hw;
	uपूर्णांक32_t rval = EXT_STATUS_OK;
	uपूर्णांक16_t req_sg_cnt = 0;
	uपूर्णांक16_t rsp_sg_cnt = 0;
	uपूर्णांक16_t nextlid = 0;
	uपूर्णांक32_t tot_dsds;
	srb_t *sp = शून्य;
	uपूर्णांक32_t req_data_len;
	uपूर्णांक32_t rsp_data_len;

	/* Check the type of the adapter */
	अगर (!IS_BIDI_CAPABLE(ha)) अणु
		ql_log(ql_log_warn, vha, 0x70a0,
			"This adapter is not supported\n");
		rval = EXT_STATUS_NOT_SUPPORTED;
		जाओ करोne;
	पूर्ण

	अगर (test_bit(ISP_ABORT_NEEDED, &vha->dpc_flags) ||
		test_bit(ABORT_ISP_ACTIVE, &vha->dpc_flags) ||
		test_bit(ISP_ABORT_RETRY, &vha->dpc_flags)) अणु
		rval =  EXT_STATUS_BUSY;
		जाओ करोne;
	पूर्ण

	/* Check अगर host is online */
	अगर (!vha->flags.online) अणु
		ql_log(ql_log_warn, vha, 0x70a1,
			"Host is not online\n");
		rval = EXT_STATUS_DEVICE_OFFLINE;
		जाओ करोne;
	पूर्ण

	/* Check अगर cable is plugged in or not */
	अगर (vha->device_flags & DFLG_NO_CABLE) अणु
		ql_log(ql_log_warn, vha, 0x70a2,
			"Cable is unplugged...\n");
		rval = EXT_STATUS_INVALID_CFG;
		जाओ करोne;
	पूर्ण

	/* Check अगर the चयन is connected or not */
	अगर (ha->current_topology != ISP_CFG_F) अणु
		ql_log(ql_log_warn, vha, 0x70a3,
			"Host is not connected to the switch\n");
		rval = EXT_STATUS_INVALID_CFG;
		जाओ करोne;
	पूर्ण

	/* Check अगर operating mode is P2P */
	अगर (ha->operating_mode != P2P) अणु
		ql_log(ql_log_warn, vha, 0x70a4,
		    "Host operating mode is not P2p\n");
		rval = EXT_STATUS_INVALID_CFG;
		जाओ करोne;
	पूर्ण

	mutex_lock(&ha->selflogin_lock);
	अगर (vha->self_login_loop_id == 0) अणु
		/* Initialize all required  fields of fcport */
		vha->bidir_fcport.vha = vha;
		vha->bidir_fcport.d_id.b.al_pa = vha->d_id.b.al_pa;
		vha->bidir_fcport.d_id.b.area = vha->d_id.b.area;
		vha->bidir_fcport.d_id.b.करोमुख्य = vha->d_id.b.करोमुख्य;
		vha->bidir_fcport.loop_id = vha->loop_id;

		अगर (qla2x00_fabric_login(vha, &(vha->bidir_fcport), &nextlid)) अणु
			ql_log(ql_log_warn, vha, 0x70a7,
			    "Failed to login port %06X for bidirectional IOCB\n",
			    vha->bidir_fcport.d_id.b24);
			mutex_unlock(&ha->selflogin_lock);
			rval = EXT_STATUS_MAILBOX;
			जाओ करोne;
		पूर्ण
		vha->self_login_loop_id = nextlid - 1;

	पूर्ण
	/* Assign the self login loop id to fcport */
	mutex_unlock(&ha->selflogin_lock);

	vha->bidir_fcport.loop_id = vha->self_login_loop_id;

	req_sg_cnt = dma_map_sg(&ha->pdev->dev,
		bsg_job->request_payload.sg_list,
		bsg_job->request_payload.sg_cnt,
		DMA_TO_DEVICE);

	अगर (!req_sg_cnt) अणु
		rval = EXT_STATUS_NO_MEMORY;
		जाओ करोne;
	पूर्ण

	rsp_sg_cnt = dma_map_sg(&ha->pdev->dev,
		bsg_job->reply_payload.sg_list, bsg_job->reply_payload.sg_cnt,
		DMA_FROM_DEVICE);

	अगर (!rsp_sg_cnt) अणु
		rval = EXT_STATUS_NO_MEMORY;
		जाओ करोne_unmap_req_sg;
	पूर्ण

	अगर ((req_sg_cnt !=  bsg_job->request_payload.sg_cnt) ||
		(rsp_sg_cnt != bsg_job->reply_payload.sg_cnt)) अणु
		ql_dbg(ql_dbg_user, vha, 0x70a9,
		    "Dma mapping resulted in different sg counts "
		    "[request_sg_cnt: %x dma_request_sg_cnt: %x reply_sg_cnt: "
		    "%x dma_reply_sg_cnt: %x]\n",
		    bsg_job->request_payload.sg_cnt, req_sg_cnt,
		    bsg_job->reply_payload.sg_cnt, rsp_sg_cnt);
		rval = EXT_STATUS_NO_MEMORY;
		जाओ करोne_unmap_sg;
	पूर्ण

	req_data_len = bsg_job->request_payload.payload_len;
	rsp_data_len = bsg_job->reply_payload.payload_len;

	अगर (req_data_len != rsp_data_len) अणु
		rval = EXT_STATUS_BUSY;
		ql_log(ql_log_warn, vha, 0x70aa,
		    "req_data_len != rsp_data_len\n");
		जाओ करोne_unmap_sg;
	पूर्ण

	/* Alloc SRB काष्ठाure */
	sp = qla2x00_get_sp(vha, &(vha->bidir_fcport), GFP_KERNEL);
	अगर (!sp) अणु
		ql_dbg(ql_dbg_user, vha, 0x70ac,
		    "Alloc SRB structure failed\n");
		rval = EXT_STATUS_NO_MEMORY;
		जाओ करोne_unmap_sg;
	पूर्ण

	/*Populate srb->ctx with bidir ctx*/
	sp->u.bsg_job = bsg_job;
	sp->मुक्त = qla2x00_bsg_sp_मुक्त;
	sp->type = SRB_BIDI_CMD;
	sp->करोne = qla2x00_bsg_job_करोne;

	/* Add the पढ़ो and ग_लिखो sg count */
	tot_dsds = rsp_sg_cnt + req_sg_cnt;

	rval = qla2x00_start_bidir(sp, vha, tot_dsds);
	अगर (rval != EXT_STATUS_OK)
		जाओ करोne_मुक्त_srb;
	/* the bsg request  will be completed in the पूर्णांकerrupt handler */
	वापस rval;

करोne_मुक्त_srb:
	mempool_मुक्त(sp, ha->srb_mempool);
करोne_unmap_sg:
	dma_unmap_sg(&ha->pdev->dev,
	    bsg_job->reply_payload.sg_list,
	    bsg_job->reply_payload.sg_cnt, DMA_FROM_DEVICE);
करोne_unmap_req_sg:
	dma_unmap_sg(&ha->pdev->dev,
	    bsg_job->request_payload.sg_list,
	    bsg_job->request_payload.sg_cnt, DMA_TO_DEVICE);
करोne:

	/* Return an error venकरोr specअगरic response
	 * and complete the bsg request
	 */
	bsg_reply->reply_data.venकरोr_reply.venकरोr_rsp[0] = rval;
	bsg_job->reply_len = माप(काष्ठा fc_bsg_reply);
	bsg_reply->reply_payload_rcv_len = 0;
	bsg_reply->result = (DID_OK) << 16;
	bsg_job_करोne(bsg_job, bsg_reply->result,
		       bsg_reply->reply_payload_rcv_len);
	/* Always वापस success, venकरोr rsp carries correct status */
	वापस 0;
पूर्ण

अटल पूर्णांक
qlafx00_mgmt_cmd(काष्ठा bsg_job *bsg_job)
अणु
	काष्ठा fc_bsg_request *bsg_request = bsg_job->request;
	काष्ठा Scsi_Host *host = fc_bsg_to_shost(bsg_job);
	scsi_qla_host_t *vha = shost_priv(host);
	काष्ठा qla_hw_data *ha = vha->hw;
	पूर्णांक rval = (DID_ERROR << 16);
	काष्ठा qla_mt_iocb_rqst_fx00 *piocb_rqst;
	srb_t *sp;
	पूर्णांक req_sg_cnt = 0, rsp_sg_cnt = 0;
	काष्ठा fc_port *fcport;
	अक्षर  *type = "FC_BSG_HST_FX_MGMT";

	/* Copy the IOCB specअगरic inक्रमmation */
	piocb_rqst = (काष्ठा qla_mt_iocb_rqst_fx00 *)
	    &bsg_request->rqst_data.h_venकरोr.venकरोr_cmd[1];

	/* Dump the venकरोr inक्रमmation */
	ql_dump_buffer(ql_dbg_user + ql_dbg_verbose , vha, 0x70cf,
	    piocb_rqst, माप(*piocb_rqst));

	अगर (!vha->flags.online) अणु
		ql_log(ql_log_warn, vha, 0x70d0,
		    "Host is not online.\n");
		rval = -EIO;
		जाओ करोne;
	पूर्ण

	अगर (piocb_rqst->flags & SRB_FXDISC_REQ_DMA_VALID) अणु
		req_sg_cnt = dma_map_sg(&ha->pdev->dev,
		    bsg_job->request_payload.sg_list,
		    bsg_job->request_payload.sg_cnt, DMA_TO_DEVICE);
		अगर (!req_sg_cnt) अणु
			ql_log(ql_log_warn, vha, 0x70c7,
			    "dma_map_sg return %d for request\n", req_sg_cnt);
			rval = -ENOMEM;
			जाओ करोne;
		पूर्ण
	पूर्ण

	अगर (piocb_rqst->flags & SRB_FXDISC_RESP_DMA_VALID) अणु
		rsp_sg_cnt = dma_map_sg(&ha->pdev->dev,
		    bsg_job->reply_payload.sg_list,
		    bsg_job->reply_payload.sg_cnt, DMA_FROM_DEVICE);
		अगर (!rsp_sg_cnt) अणु
			ql_log(ql_log_warn, vha, 0x70c8,
			    "dma_map_sg return %d for reply\n", rsp_sg_cnt);
			rval = -ENOMEM;
			जाओ करोne_unmap_req_sg;
		पूर्ण
	पूर्ण

	ql_dbg(ql_dbg_user, vha, 0x70c9,
	    "request_sg_cnt: %x dma_request_sg_cnt: %x reply_sg_cnt:%x "
	    "dma_reply_sg_cnt: %x\n", bsg_job->request_payload.sg_cnt,
	    req_sg_cnt, bsg_job->reply_payload.sg_cnt, rsp_sg_cnt);

	/* Allocate a dummy fcport काष्ठाure, since functions preparing the
	 * IOCB and mailbox command retrieves port specअगरic inक्रमmation
	 * from fcport काष्ठाure. For Host based ELS commands there will be
	 * no fcport काष्ठाure allocated
	 */
	fcport = qla2x00_alloc_fcport(vha, GFP_KERNEL);
	अगर (!fcport) अणु
		ql_log(ql_log_warn, vha, 0x70ca,
		    "Failed to allocate fcport.\n");
		rval = -ENOMEM;
		जाओ करोne_unmap_rsp_sg;
	पूर्ण

	/* Alloc SRB काष्ठाure */
	sp = qla2x00_get_sp(vha, fcport, GFP_KERNEL);
	अगर (!sp) अणु
		ql_log(ql_log_warn, vha, 0x70cb,
		    "qla2x00_get_sp failed.\n");
		rval = -ENOMEM;
		जाओ करोne_मुक्त_fcport;
	पूर्ण

	/* Initialize all required  fields of fcport */
	fcport->vha = vha;
	fcport->loop_id = le32_to_cpu(piocb_rqst->dataword);

	sp->type = SRB_FXIOCB_BCMD;
	sp->name = "bsg_fx_mgmt";
	sp->iocbs = qla24xx_calc_ct_iocbs(req_sg_cnt + rsp_sg_cnt);
	sp->u.bsg_job = bsg_job;
	sp->मुक्त = qla2x00_bsg_sp_मुक्त;
	sp->करोne = qla2x00_bsg_job_करोne;

	ql_dbg(ql_dbg_user, vha, 0x70cc,
	    "bsg rqst type: %s fx_mgmt_type: %x id=%x\n",
	    type, piocb_rqst->func_type, fcport->loop_id);

	rval = qla2x00_start_sp(sp);
	अगर (rval != QLA_SUCCESS) अणु
		ql_log(ql_log_warn, vha, 0x70cd,
		    "qla2x00_start_sp failed=%d.\n", rval);
		mempool_मुक्त(sp, ha->srb_mempool);
		rval = -EIO;
		जाओ करोne_मुक्त_fcport;
	पूर्ण
	वापस rval;

करोne_मुक्त_fcport:
	qla2x00_मुक्त_fcport(fcport);

करोne_unmap_rsp_sg:
	अगर (piocb_rqst->flags & SRB_FXDISC_RESP_DMA_VALID)
		dma_unmap_sg(&ha->pdev->dev,
		    bsg_job->reply_payload.sg_list,
		    bsg_job->reply_payload.sg_cnt, DMA_FROM_DEVICE);
करोne_unmap_req_sg:
	अगर (piocb_rqst->flags & SRB_FXDISC_REQ_DMA_VALID)
		dma_unmap_sg(&ha->pdev->dev,
		    bsg_job->request_payload.sg_list,
		    bsg_job->request_payload.sg_cnt, DMA_TO_DEVICE);

करोne:
	वापस rval;
पूर्ण

अटल पूर्णांक
qla26xx_serdes_op(काष्ठा bsg_job *bsg_job)
अणु
	काष्ठा fc_bsg_reply *bsg_reply = bsg_job->reply;
	काष्ठा Scsi_Host *host = fc_bsg_to_shost(bsg_job);
	scsi_qla_host_t *vha = shost_priv(host);
	पूर्णांक rval = 0;
	काष्ठा qla_serdes_reg sr;

	स_रखो(&sr, 0, माप(sr));

	sg_copy_to_buffer(bsg_job->request_payload.sg_list,
	    bsg_job->request_payload.sg_cnt, &sr, माप(sr));

	चयन (sr.cmd) अणु
	हाल INT_SC_SERDES_WRITE_REG:
		rval = qla2x00_ग_लिखो_serdes_word(vha, sr.addr, sr.val);
		bsg_reply->reply_payload_rcv_len = 0;
		अवरोध;
	हाल INT_SC_SERDES_READ_REG:
		rval = qla2x00_पढ़ो_serdes_word(vha, sr.addr, &sr.val);
		sg_copy_from_buffer(bsg_job->reply_payload.sg_list,
		    bsg_job->reply_payload.sg_cnt, &sr, माप(sr));
		bsg_reply->reply_payload_rcv_len = माप(sr);
		अवरोध;
	शेष:
		ql_dbg(ql_dbg_user, vha, 0x708c,
		    "Unknown serdes cmd %x.\n", sr.cmd);
		rval = -EINVAL;
		अवरोध;
	पूर्ण

	bsg_reply->reply_data.venकरोr_reply.venकरोr_rsp[0] =
	    rval ? EXT_STATUS_MAILBOX : 0;

	bsg_job->reply_len = माप(काष्ठा fc_bsg_reply);
	bsg_reply->result = DID_OK << 16;
	bsg_job_करोne(bsg_job, bsg_reply->result,
		       bsg_reply->reply_payload_rcv_len);
	वापस 0;
पूर्ण

अटल पूर्णांक
qla8044_serdes_op(काष्ठा bsg_job *bsg_job)
अणु
	काष्ठा fc_bsg_reply *bsg_reply = bsg_job->reply;
	काष्ठा Scsi_Host *host = fc_bsg_to_shost(bsg_job);
	scsi_qla_host_t *vha = shost_priv(host);
	पूर्णांक rval = 0;
	काष्ठा qla_serdes_reg_ex sr;

	स_रखो(&sr, 0, माप(sr));

	sg_copy_to_buffer(bsg_job->request_payload.sg_list,
	    bsg_job->request_payload.sg_cnt, &sr, माप(sr));

	चयन (sr.cmd) अणु
	हाल INT_SC_SERDES_WRITE_REG:
		rval = qla8044_ग_लिखो_serdes_word(vha, sr.addr, sr.val);
		bsg_reply->reply_payload_rcv_len = 0;
		अवरोध;
	हाल INT_SC_SERDES_READ_REG:
		rval = qla8044_पढ़ो_serdes_word(vha, sr.addr, &sr.val);
		sg_copy_from_buffer(bsg_job->reply_payload.sg_list,
		    bsg_job->reply_payload.sg_cnt, &sr, माप(sr));
		bsg_reply->reply_payload_rcv_len = माप(sr);
		अवरोध;
	शेष:
		ql_dbg(ql_dbg_user, vha, 0x7020,
		    "Unknown serdes cmd %x.\n", sr.cmd);
		rval = -EINVAL;
		अवरोध;
	पूर्ण

	bsg_reply->reply_data.venकरोr_reply.venकरोr_rsp[0] =
	    rval ? EXT_STATUS_MAILBOX : 0;

	bsg_job->reply_len = माप(काष्ठा fc_bsg_reply);
	bsg_reply->result = DID_OK << 16;
	bsg_job_करोne(bsg_job, bsg_reply->result,
		       bsg_reply->reply_payload_rcv_len);
	वापस 0;
पूर्ण

अटल पूर्णांक
qla27xx_get_flash_upd_cap(काष्ठा bsg_job *bsg_job)
अणु
	काष्ठा fc_bsg_reply *bsg_reply = bsg_job->reply;
	काष्ठा Scsi_Host *host = fc_bsg_to_shost(bsg_job);
	scsi_qla_host_t *vha = shost_priv(host);
	काष्ठा qla_hw_data *ha = vha->hw;
	काष्ठा qla_flash_update_caps cap;

	अगर (!(IS_QLA27XX(ha)) && !IS_QLA28XX(ha))
		वापस -EPERM;

	स_रखो(&cap, 0, माप(cap));
	cap.capabilities = (uपूर्णांक64_t)ha->fw_attributes_ext[1] << 48 |
			   (uपूर्णांक64_t)ha->fw_attributes_ext[0] << 32 |
			   (uपूर्णांक64_t)ha->fw_attributes_h << 16 |
			   (uपूर्णांक64_t)ha->fw_attributes;

	sg_copy_from_buffer(bsg_job->reply_payload.sg_list,
	    bsg_job->reply_payload.sg_cnt, &cap, माप(cap));
	bsg_reply->reply_payload_rcv_len = माप(cap);

	bsg_reply->reply_data.venकरोr_reply.venकरोr_rsp[0] =
	    EXT_STATUS_OK;

	bsg_job->reply_len = माप(काष्ठा fc_bsg_reply);
	bsg_reply->result = DID_OK << 16;
	bsg_job_करोne(bsg_job, bsg_reply->result,
		       bsg_reply->reply_payload_rcv_len);
	वापस 0;
पूर्ण

अटल पूर्णांक
qla27xx_set_flash_upd_cap(काष्ठा bsg_job *bsg_job)
अणु
	काष्ठा fc_bsg_reply *bsg_reply = bsg_job->reply;
	काष्ठा Scsi_Host *host = fc_bsg_to_shost(bsg_job);
	scsi_qla_host_t *vha = shost_priv(host);
	काष्ठा qla_hw_data *ha = vha->hw;
	uपूर्णांक64_t online_fw_attr = 0;
	काष्ठा qla_flash_update_caps cap;

	अगर (!IS_QLA27XX(ha) && !IS_QLA28XX(ha))
		वापस -EPERM;

	स_रखो(&cap, 0, माप(cap));
	sg_copy_to_buffer(bsg_job->request_payload.sg_list,
	    bsg_job->request_payload.sg_cnt, &cap, माप(cap));

	online_fw_attr = (uपूर्णांक64_t)ha->fw_attributes_ext[1] << 48 |
			 (uपूर्णांक64_t)ha->fw_attributes_ext[0] << 32 |
			 (uपूर्णांक64_t)ha->fw_attributes_h << 16 |
			 (uपूर्णांक64_t)ha->fw_attributes;

	अगर (online_fw_attr != cap.capabilities) अणु
		bsg_reply->reply_data.venकरोr_reply.venकरोr_rsp[0] =
		    EXT_STATUS_INVALID_PARAM;
		वापस -EINVAL;
	पूर्ण

	अगर (cap.outage_duration < MAX_LOOP_TIMEOUT)  अणु
		bsg_reply->reply_data.venकरोr_reply.venकरोr_rsp[0] =
		    EXT_STATUS_INVALID_PARAM;
		वापस -EINVAL;
	पूर्ण

	bsg_reply->reply_payload_rcv_len = 0;

	bsg_reply->reply_data.venकरोr_reply.venकरोr_rsp[0] =
	    EXT_STATUS_OK;

	bsg_job->reply_len = माप(काष्ठा fc_bsg_reply);
	bsg_reply->result = DID_OK << 16;
	bsg_job_करोne(bsg_job, bsg_reply->result,
		       bsg_reply->reply_payload_rcv_len);
	वापस 0;
पूर्ण

अटल पूर्णांक
qla27xx_get_bbcr_data(काष्ठा bsg_job *bsg_job)
अणु
	काष्ठा fc_bsg_reply *bsg_reply = bsg_job->reply;
	काष्ठा Scsi_Host *host = fc_bsg_to_shost(bsg_job);
	scsi_qla_host_t *vha = shost_priv(host);
	काष्ठा qla_hw_data *ha = vha->hw;
	काष्ठा qla_bbcr_data bbcr;
	uपूर्णांक16_t loop_id, topo, sw_cap;
	uपूर्णांक8_t करोमुख्य, area, al_pa, state;
	पूर्णांक rval;

	अगर (!IS_QLA27XX(ha) && !IS_QLA28XX(ha))
		वापस -EPERM;

	स_रखो(&bbcr, 0, माप(bbcr));

	अगर (vha->flags.bbcr_enable)
		bbcr.status = QLA_BBCR_STATUS_ENABLED;
	अन्यथा
		bbcr.status = QLA_BBCR_STATUS_DISABLED;

	अगर (bbcr.status == QLA_BBCR_STATUS_ENABLED) अणु
		rval = qla2x00_get_adapter_id(vha, &loop_id, &al_pa,
			&area, &करोमुख्य, &topo, &sw_cap);
		अगर (rval != QLA_SUCCESS) अणु
			bbcr.status = QLA_BBCR_STATUS_UNKNOWN;
			bbcr.state = QLA_BBCR_STATE_OFFLINE;
			bbcr.mbx1 = loop_id;
			जाओ करोne;
		पूर्ण

		state = (vha->bbcr >> 12) & 0x1;

		अगर (state) अणु
			bbcr.state = QLA_BBCR_STATE_OFFLINE;
			bbcr.offline_reason_code = QLA_BBCR_REASON_LOGIN_REJECT;
		पूर्ण अन्यथा अणु
			bbcr.state = QLA_BBCR_STATE_ONLINE;
			bbcr.negotiated_bbscn = (vha->bbcr >> 8) & 0xf;
		पूर्ण

		bbcr.configured_bbscn = vha->bbcr & 0xf;
	पूर्ण

करोne:
	sg_copy_from_buffer(bsg_job->reply_payload.sg_list,
		bsg_job->reply_payload.sg_cnt, &bbcr, माप(bbcr));
	bsg_reply->reply_payload_rcv_len = माप(bbcr);

	bsg_reply->reply_data.venकरोr_reply.venकरोr_rsp[0] = EXT_STATUS_OK;

	bsg_job->reply_len = माप(काष्ठा fc_bsg_reply);
	bsg_reply->result = DID_OK << 16;
	bsg_job_करोne(bsg_job, bsg_reply->result,
		       bsg_reply->reply_payload_rcv_len);
	वापस 0;
पूर्ण

अटल पूर्णांक
qla2x00_get_priv_stats(काष्ठा bsg_job *bsg_job)
अणु
	काष्ठा fc_bsg_request *bsg_request = bsg_job->request;
	काष्ठा fc_bsg_reply *bsg_reply = bsg_job->reply;
	काष्ठा Scsi_Host *host = fc_bsg_to_shost(bsg_job);
	scsi_qla_host_t *vha = shost_priv(host);
	काष्ठा qla_hw_data *ha = vha->hw;
	काष्ठा scsi_qla_host *base_vha = pci_get_drvdata(ha->pdev);
	काष्ठा link_statistics *stats = शून्य;
	dma_addr_t stats_dma;
	पूर्णांक rval;
	uपूर्णांक32_t *cmd = bsg_request->rqst_data.h_venकरोr.venकरोr_cmd;
	uपूर्णांक options = cmd[0] == QL_VND_GET_PRIV_STATS_EX ? cmd[1] : 0;

	अगर (test_bit(UNLOADING, &vha->dpc_flags))
		वापस -ENODEV;

	अगर (unlikely(pci_channel_offline(ha->pdev)))
		वापस -ENODEV;

	अगर (qla2x00_reset_active(vha))
		वापस -EBUSY;

	अगर (!IS_FWI2_CAPABLE(ha))
		वापस -EPERM;

	stats = dma_alloc_coherent(&ha->pdev->dev, माप(*stats), &stats_dma,
				   GFP_KERNEL);
	अगर (!stats) अणु
		ql_log(ql_log_warn, vha, 0x70e2,
		    "Failed to allocate memory for stats.\n");
		वापस -ENOMEM;
	पूर्ण

	rval = qla24xx_get_isp_stats(base_vha, stats, stats_dma, options);

	अगर (rval == QLA_SUCCESS) अणु
		ql_dump_buffer(ql_dbg_user + ql_dbg_verbose, vha, 0x70e5,
			stats, माप(*stats));
		sg_copy_from_buffer(bsg_job->reply_payload.sg_list,
			bsg_job->reply_payload.sg_cnt, stats, माप(*stats));
	पूर्ण

	bsg_reply->reply_payload_rcv_len = माप(*stats);
	bsg_reply->reply_data.venकरोr_reply.venकरोr_rsp[0] =
	    rval ? EXT_STATUS_MAILBOX : EXT_STATUS_OK;

	bsg_job->reply_len = माप(*bsg_reply);
	bsg_reply->result = DID_OK << 16;
	bsg_job_करोne(bsg_job, bsg_reply->result,
		       bsg_reply->reply_payload_rcv_len);

	dma_मुक्त_coherent(&ha->pdev->dev, माप(*stats),
		stats, stats_dma);

	वापस 0;
पूर्ण

अटल पूर्णांक
qla2x00_करो_dport_diagnostics(काष्ठा bsg_job *bsg_job)
अणु
	काष्ठा fc_bsg_reply *bsg_reply = bsg_job->reply;
	काष्ठा Scsi_Host *host = fc_bsg_to_shost(bsg_job);
	scsi_qla_host_t *vha = shost_priv(host);
	पूर्णांक rval;
	काष्ठा qla_dport_diag *dd;

	अगर (!IS_QLA83XX(vha->hw) && !IS_QLA27XX(vha->hw) &&
	    !IS_QLA28XX(vha->hw))
		वापस -EPERM;

	dd = kदो_स्मृति(माप(*dd), GFP_KERNEL);
	अगर (!dd) अणु
		ql_log(ql_log_warn, vha, 0x70db,
		    "Failed to allocate memory for dport.\n");
		वापस -ENOMEM;
	पूर्ण

	sg_copy_to_buffer(bsg_job->request_payload.sg_list,
	    bsg_job->request_payload.sg_cnt, dd, माप(*dd));

	rval = qla26xx_dport_diagnostics(
	    vha, dd->buf, माप(dd->buf), dd->options);
	अगर (rval == QLA_SUCCESS) अणु
		sg_copy_from_buffer(bsg_job->reply_payload.sg_list,
		    bsg_job->reply_payload.sg_cnt, dd, माप(*dd));
	पूर्ण

	bsg_reply->reply_payload_rcv_len = माप(*dd);
	bsg_reply->reply_data.venकरोr_reply.venकरोr_rsp[0] =
	    rval ? EXT_STATUS_MAILBOX : EXT_STATUS_OK;

	bsg_job->reply_len = माप(*bsg_reply);
	bsg_reply->result = DID_OK << 16;
	bsg_job_करोne(bsg_job, bsg_reply->result,
		       bsg_reply->reply_payload_rcv_len);

	kमुक्त(dd);

	वापस 0;
पूर्ण

अटल पूर्णांक
qla2x00_get_flash_image_status(काष्ठा bsg_job *bsg_job)
अणु
	scsi_qla_host_t *vha = shost_priv(fc_bsg_to_shost(bsg_job));
	काष्ठा fc_bsg_reply *bsg_reply = bsg_job->reply;
	काष्ठा qla_hw_data *ha = vha->hw;
	काष्ठा qla_active_regions regions = अणु पूर्ण;
	काष्ठा active_regions active_regions = अणु पूर्ण;

	qla27xx_get_active_image(vha, &active_regions);
	regions.global_image = active_regions.global;

	अगर (IS_QLA28XX(ha)) अणु
		qla28xx_get_aux_images(vha, &active_regions);
		regions.board_config = active_regions.aux.board_config;
		regions.vpd_nvram = active_regions.aux.vpd_nvram;
		regions.npiv_config_0_1 = active_regions.aux.npiv_config_0_1;
		regions.npiv_config_2_3 = active_regions.aux.npiv_config_2_3;
	पूर्ण

	ql_dbg(ql_dbg_user, vha, 0x70e1,
	    "%s(%lu): FW=%u BCFG=%u VPDNVR=%u NPIV01=%u NPIV02=%u\n",
	    __func__, vha->host_no, regions.global_image,
	    regions.board_config, regions.vpd_nvram,
	    regions.npiv_config_0_1, regions.npiv_config_2_3);

	sg_copy_from_buffer(bsg_job->reply_payload.sg_list,
	    bsg_job->reply_payload.sg_cnt, &regions, माप(regions));

	bsg_reply->reply_data.venकरोr_reply.venकरोr_rsp[0] = EXT_STATUS_OK;
	bsg_reply->reply_payload_rcv_len = माप(regions);
	bsg_reply->result = DID_OK << 16;
	bsg_job->reply_len = माप(काष्ठा fc_bsg_reply);
	bsg_job_करोne(bsg_job, bsg_reply->result,
	    bsg_reply->reply_payload_rcv_len);

	वापस 0;
पूर्ण

अटल पूर्णांक
qla2x00_manage_host_stats(काष्ठा bsg_job *bsg_job)
अणु
	scsi_qla_host_t *vha = shost_priv(fc_bsg_to_shost(bsg_job));
	काष्ठा fc_bsg_reply *bsg_reply = bsg_job->reply;
	काष्ठा ql_vnd_mng_host_stats_param *req_data;
	काष्ठा ql_vnd_mng_host_stats_resp rsp_data;
	u32 req_data_len;
	पूर्णांक ret = 0;

	अगर (!vha->flags.online) अणु
		ql_log(ql_log_warn, vha, 0x0000, "Host is not online.\n");
		वापस -EIO;
	पूर्ण

	req_data_len = bsg_job->request_payload.payload_len;

	अगर (req_data_len != माप(काष्ठा ql_vnd_mng_host_stats_param)) अणु
		ql_log(ql_log_warn, vha, 0x0000, "req_data_len invalid.\n");
		वापस -EIO;
	पूर्ण

	req_data = kzalloc(माप(*req_data), GFP_KERNEL);
	अगर (!req_data) अणु
		ql_log(ql_log_warn, vha, 0x0000, "req_data memory allocation failure.\n");
		वापस -ENOMEM;
	पूर्ण

	/* Copy the request buffer in req_data */
	sg_copy_to_buffer(bsg_job->request_payload.sg_list,
			  bsg_job->request_payload.sg_cnt, req_data,
			  req_data_len);

	चयन (req_data->action) अणु
	हाल QLA_STOP:
		ret = qla2xxx_stop_stats(vha->host, req_data->stat_type);
		अवरोध;
	हाल QLA_START:
		ret = qla2xxx_start_stats(vha->host, req_data->stat_type);
		अवरोध;
	हाल QLA_CLEAR:
		ret = qla2xxx_reset_stats(vha->host, req_data->stat_type);
		अवरोध;
	शेष:
		ql_log(ql_log_warn, vha, 0x0000, "Invalid action.\n");
		ret = -EIO;
		अवरोध;
	पूर्ण

	kमुक्त(req_data);

	/* Prepare response */
	rsp_data.status = ret;
	bsg_job->reply_payload.payload_len = माप(काष्ठा ql_vnd_mng_host_stats_resp);

	bsg_reply->reply_data.venकरोr_reply.venकरोr_rsp[0] = EXT_STATUS_OK;
	bsg_reply->reply_payload_rcv_len =
		sg_copy_from_buffer(bsg_job->reply_payload.sg_list,
				    bsg_job->reply_payload.sg_cnt,
				    &rsp_data,
				    माप(काष्ठा ql_vnd_mng_host_stats_resp));

	bsg_reply->result = DID_OK;
	bsg_job_करोne(bsg_job, bsg_reply->result,
		     bsg_reply->reply_payload_rcv_len);

	वापस ret;
पूर्ण

अटल पूर्णांक
qla2x00_get_host_stats(काष्ठा bsg_job *bsg_job)
अणु
	scsi_qla_host_t *vha = shost_priv(fc_bsg_to_shost(bsg_job));
	काष्ठा fc_bsg_reply *bsg_reply = bsg_job->reply;
	काष्ठा ql_vnd_stats_param *req_data;
	काष्ठा ql_vnd_host_stats_resp rsp_data;
	u32 req_data_len;
	पूर्णांक ret = 0;
	u64 ini_entry_count = 0;
	u64 entry_count = 0;
	u64 tgt_num = 0;
	u64 पंचांगp_stat_type = 0;
	u64 response_len = 0;
	व्योम *data;

	req_data_len = bsg_job->request_payload.payload_len;

	अगर (req_data_len != माप(काष्ठा ql_vnd_stats_param)) अणु
		ql_log(ql_log_warn, vha, 0x0000, "req_data_len invalid.\n");
		वापस -EIO;
	पूर्ण

	req_data = kzalloc(माप(*req_data), GFP_KERNEL);
	अगर (!req_data) अणु
		ql_log(ql_log_warn, vha, 0x0000, "req_data memory allocation failure.\n");
		वापस -ENOMEM;
	पूर्ण

	/* Copy the request buffer in req_data */
	sg_copy_to_buffer(bsg_job->request_payload.sg_list,
			  bsg_job->request_payload.sg_cnt, req_data, req_data_len);

	/* Copy stat type to work on it */
	पंचांगp_stat_type = req_data->stat_type;

	अगर (पंचांगp_stat_type & QLA2XX_TGT_SHT_LNK_DOWN) अणु
		/* Num of tgts connected to this host */
		tgt_num = qla2x00_get_num_tgts(vha);
		/* unset BIT_17 */
		पंचांगp_stat_type &= ~(1 << 17);
	पूर्ण

	/* Total ini stats */
	ini_entry_count = qla2x00_count_set_bits(पंचांगp_stat_type);

	/* Total number of entries */
	entry_count = ini_entry_count + tgt_num;

	response_len = माप(काष्ठा ql_vnd_host_stats_resp) +
		(माप(काष्ठा ql_vnd_stat_entry) * entry_count);

	अगर (response_len > bsg_job->reply_payload.payload_len) अणु
		rsp_data.status = EXT_STATUS_BUFFER_TOO_SMALL;
		bsg_reply->reply_data.venकरोr_reply.venकरोr_rsp[0] = EXT_STATUS_BUFFER_TOO_SMALL;
		bsg_job->reply_payload.payload_len = माप(काष्ठा ql_vnd_mng_host_stats_resp);

		bsg_reply->reply_payload_rcv_len =
			sg_copy_from_buffer(bsg_job->reply_payload.sg_list,
					    bsg_job->reply_payload.sg_cnt, &rsp_data,
					    माप(काष्ठा ql_vnd_mng_host_stats_resp));

		bsg_reply->result = DID_OK;
		bsg_job_करोne(bsg_job, bsg_reply->result,
			     bsg_reply->reply_payload_rcv_len);
		जाओ host_stat_out;
	पूर्ण

	data = kzalloc(response_len, GFP_KERNEL);
	अगर (!data) अणु
		ret = -ENOMEM;
		जाओ host_stat_out;
	पूर्ण

	ret = qla2xxx_get_ini_stats(fc_bsg_to_shost(bsg_job), req_data->stat_type,
				    data, response_len);

	rsp_data.status = EXT_STATUS_OK;
	bsg_reply->reply_data.venकरोr_reply.venकरोr_rsp[0] = EXT_STATUS_OK;

	bsg_reply->reply_payload_rcv_len = sg_copy_from_buffer(bsg_job->reply_payload.sg_list,
							       bsg_job->reply_payload.sg_cnt,
							       data, response_len);
	bsg_reply->result = DID_OK;
	bsg_job_करोne(bsg_job, bsg_reply->result,
		     bsg_reply->reply_payload_rcv_len);

	kमुक्त(data);
host_stat_out:
	kमुक्त(req_data);
	वापस ret;
पूर्ण

अटल काष्ठा fc_rport *
qla2xxx_find_rport(scsi_qla_host_t *vha, uपूर्णांक32_t tgt_num)
अणु
	fc_port_t *fcport = शून्य;

	list_क्रम_each_entry(fcport, &vha->vp_fcports, list) अणु
		अगर (fcport->rport->number == tgt_num)
			वापस fcport->rport;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल पूर्णांक
qla2x00_get_tgt_stats(काष्ठा bsg_job *bsg_job)
अणु
	scsi_qla_host_t *vha = shost_priv(fc_bsg_to_shost(bsg_job));
	काष्ठा fc_bsg_reply *bsg_reply = bsg_job->reply;
	काष्ठा ql_vnd_tgt_stats_param *req_data;
	u32 req_data_len;
	पूर्णांक ret = 0;
	u64 response_len = 0;
	काष्ठा ql_vnd_tgt_stats_resp *data = शून्य;
	काष्ठा fc_rport *rport = शून्य;

	अगर (!vha->flags.online) अणु
		ql_log(ql_log_warn, vha, 0x0000, "Host is not online.\n");
		वापस -EIO;
	पूर्ण

	req_data_len = bsg_job->request_payload.payload_len;

	अगर (req_data_len != माप(काष्ठा ql_vnd_stat_entry)) अणु
		ql_log(ql_log_warn, vha, 0x0000, "req_data_len invalid.\n");
		वापस -EIO;
	पूर्ण

	req_data = kzalloc(माप(*req_data), GFP_KERNEL);
	अगर (!req_data) अणु
		ql_log(ql_log_warn, vha, 0x0000, "req_data memory allocation failure.\n");
		वापस -ENOMEM;
	पूर्ण

	/* Copy the request buffer in req_data */
	sg_copy_to_buffer(bsg_job->request_payload.sg_list,
			  bsg_job->request_payload.sg_cnt,
			  req_data, req_data_len);

	response_len = माप(काष्ठा ql_vnd_tgt_stats_resp) +
		माप(काष्ठा ql_vnd_stat_entry);

	/* काष्ठाure + size क्रम one entry */
	data = kzalloc(response_len, GFP_KERNEL);
	अगर (!data) अणु
		kमुक्त(req_data);
		वापस -ENOMEM;
	पूर्ण

	अगर (response_len > bsg_job->reply_payload.payload_len) अणु
		data->status = EXT_STATUS_BUFFER_TOO_SMALL;
		bsg_reply->reply_data.venकरोr_reply.venकरोr_rsp[0] = EXT_STATUS_BUFFER_TOO_SMALL;
		bsg_job->reply_payload.payload_len = माप(काष्ठा ql_vnd_mng_host_stats_resp);

		bsg_reply->reply_payload_rcv_len =
			sg_copy_from_buffer(bsg_job->reply_payload.sg_list,
					    bsg_job->reply_payload.sg_cnt, data,
					    माप(काष्ठा ql_vnd_tgt_stats_resp));

		bsg_reply->result = DID_OK;
		bsg_job_करोne(bsg_job, bsg_reply->result,
			     bsg_reply->reply_payload_rcv_len);
		जाओ tgt_stat_out;
	पूर्ण

	rport = qla2xxx_find_rport(vha, req_data->tgt_id);
	अगर (!rport) अणु
		ql_log(ql_log_warn, vha, 0x0000, "target %d not found.\n", req_data->tgt_id);
		ret = EXT_STATUS_INVALID_PARAM;
		data->status = EXT_STATUS_INVALID_PARAM;
		जाओ reply;
	पूर्ण

	ret = qla2xxx_get_tgt_stats(fc_bsg_to_shost(bsg_job), req_data->stat_type,
				    rport, (व्योम *)data, response_len);

	bsg_reply->reply_data.venकरोr_reply.venकरोr_rsp[0] = EXT_STATUS_OK;
reply:
	bsg_reply->reply_payload_rcv_len =
		sg_copy_from_buffer(bsg_job->reply_payload.sg_list,
				    bsg_job->reply_payload.sg_cnt, data,
				    response_len);
	bsg_reply->result = DID_OK;
	bsg_job_करोne(bsg_job, bsg_reply->result,
		     bsg_reply->reply_payload_rcv_len);

tgt_stat_out:
	kमुक्त(data);
	kमुक्त(req_data);

	वापस ret;
पूर्ण

अटल पूर्णांक
qla2x00_manage_host_port(काष्ठा bsg_job *bsg_job)
अणु
	scsi_qla_host_t *vha = shost_priv(fc_bsg_to_shost(bsg_job));
	काष्ठा fc_bsg_reply *bsg_reply = bsg_job->reply;
	काष्ठा ql_vnd_mng_host_port_param *req_data;
	काष्ठा ql_vnd_mng_host_port_resp rsp_data;
	u32 req_data_len;
	पूर्णांक ret = 0;

	req_data_len = bsg_job->request_payload.payload_len;

	अगर (req_data_len != माप(काष्ठा ql_vnd_mng_host_port_param)) अणु
		ql_log(ql_log_warn, vha, 0x0000, "req_data_len invalid.\n");
		वापस -EIO;
	पूर्ण

	req_data = kzalloc(माप(*req_data), GFP_KERNEL);
	अगर (!req_data) अणु
		ql_log(ql_log_warn, vha, 0x0000, "req_data memory allocation failure.\n");
		वापस -ENOMEM;
	पूर्ण

	/* Copy the request buffer in req_data */
	sg_copy_to_buffer(bsg_job->request_payload.sg_list,
			  bsg_job->request_payload.sg_cnt, req_data, req_data_len);

	चयन (req_data->action) अणु
	हाल QLA_ENABLE:
		ret = qla2xxx_enable_port(vha->host);
		अवरोध;
	हाल QLA_DISABLE:
		ret = qla2xxx_disable_port(vha->host);
		अवरोध;
	शेष:
		ql_log(ql_log_warn, vha, 0x0000, "Invalid action.\n");
		ret = -EIO;
		अवरोध;
	पूर्ण

	kमुक्त(req_data);

	/* Prepare response */
	rsp_data.status = ret;
	bsg_reply->reply_data.venकरोr_reply.venकरोr_rsp[0] = EXT_STATUS_OK;
	bsg_job->reply_payload.payload_len = माप(काष्ठा ql_vnd_mng_host_port_resp);

	bsg_reply->reply_payload_rcv_len =
		sg_copy_from_buffer(bsg_job->reply_payload.sg_list,
				    bsg_job->reply_payload.sg_cnt, &rsp_data,
				    माप(काष्ठा ql_vnd_mng_host_port_resp));
	bsg_reply->result = DID_OK;
	bsg_job_करोne(bsg_job, bsg_reply->result,
		     bsg_reply->reply_payload_rcv_len);

	वापस ret;
पूर्ण

अटल पूर्णांक
qla2x00_process_venकरोr_specअगरic(काष्ठा bsg_job *bsg_job)
अणु
	काष्ठा fc_bsg_request *bsg_request = bsg_job->request;

	चयन (bsg_request->rqst_data.h_venकरोr.venकरोr_cmd[0]) अणु
	हाल QL_VND_LOOPBACK:
		वापस qla2x00_process_loopback(bsg_job);

	हाल QL_VND_A84_RESET:
		वापस qla84xx_reset(bsg_job);

	हाल QL_VND_A84_UPDATE_FW:
		वापस qla84xx_updatefw(bsg_job);

	हाल QL_VND_A84_MGMT_CMD:
		वापस qla84xx_mgmt_cmd(bsg_job);

	हाल QL_VND_IIDMA:
		वापस qla24xx_iidma(bsg_job);

	हाल QL_VND_FCP_PRIO_CFG_CMD:
		वापस qla24xx_proc_fcp_prio_cfg_cmd(bsg_job);

	हाल QL_VND_READ_FLASH:
		वापस qla2x00_पढ़ो_optrom(bsg_job);

	हाल QL_VND_UPDATE_FLASH:
		वापस qla2x00_update_optrom(bsg_job);

	हाल QL_VND_SET_FRU_VERSION:
		वापस qla2x00_update_fru_versions(bsg_job);

	हाल QL_VND_READ_FRU_STATUS:
		वापस qla2x00_पढ़ो_fru_status(bsg_job);

	हाल QL_VND_WRITE_FRU_STATUS:
		वापस qla2x00_ग_लिखो_fru_status(bsg_job);

	हाल QL_VND_WRITE_I2C:
		वापस qla2x00_ग_लिखो_i2c(bsg_job);

	हाल QL_VND_READ_I2C:
		वापस qla2x00_पढ़ो_i2c(bsg_job);

	हाल QL_VND_DIAG_IO_CMD:
		वापस qla24xx_process_bidir_cmd(bsg_job);

	हाल QL_VND_FX00_MGMT_CMD:
		वापस qlafx00_mgmt_cmd(bsg_job);

	हाल QL_VND_SERDES_OP:
		वापस qla26xx_serdes_op(bsg_job);

	हाल QL_VND_SERDES_OP_EX:
		वापस qla8044_serdes_op(bsg_job);

	हाल QL_VND_GET_FLASH_UPDATE_CAPS:
		वापस qla27xx_get_flash_upd_cap(bsg_job);

	हाल QL_VND_SET_FLASH_UPDATE_CAPS:
		वापस qla27xx_set_flash_upd_cap(bsg_job);

	हाल QL_VND_GET_BBCR_DATA:
		वापस qla27xx_get_bbcr_data(bsg_job);

	हाल QL_VND_GET_PRIV_STATS:
	हाल QL_VND_GET_PRIV_STATS_EX:
		वापस qla2x00_get_priv_stats(bsg_job);

	हाल QL_VND_DPORT_DIAGNOSTICS:
		वापस qla2x00_करो_dport_diagnostics(bsg_job);

	हाल QL_VND_SS_GET_FLASH_IMAGE_STATUS:
		वापस qla2x00_get_flash_image_status(bsg_job);

	हाल QL_VND_MANAGE_HOST_STATS:
		वापस qla2x00_manage_host_stats(bsg_job);

	हाल QL_VND_GET_HOST_STATS:
		वापस qla2x00_get_host_stats(bsg_job);

	हाल QL_VND_GET_TGT_STATS:
		वापस qla2x00_get_tgt_stats(bsg_job);

	हाल QL_VND_MANAGE_HOST_PORT:
		वापस qla2x00_manage_host_port(bsg_job);

	शेष:
		वापस -ENOSYS;
	पूर्ण
पूर्ण

पूर्णांक
qla24xx_bsg_request(काष्ठा bsg_job *bsg_job)
अणु
	काष्ठा fc_bsg_request *bsg_request = bsg_job->request;
	काष्ठा fc_bsg_reply *bsg_reply = bsg_job->reply;
	पूर्णांक ret = -EINVAL;
	काष्ठा fc_rport *rport;
	काष्ठा Scsi_Host *host;
	scsi_qla_host_t *vha;

	/* In हाल no data transferred. */
	bsg_reply->reply_payload_rcv_len = 0;

	अगर (bsg_request->msgcode == FC_BSG_RPT_ELS) अणु
		rport = fc_bsg_to_rport(bsg_job);
		host = rport_to_shost(rport);
		vha = shost_priv(host);
	पूर्ण अन्यथा अणु
		host = fc_bsg_to_shost(bsg_job);
		vha = shost_priv(host);
	पूर्ण

	/* Disable port will bring करोwn the chip, allow enable command */
	अगर (bsg_request->rqst_data.h_venकरोr.venकरोr_cmd[0] == QL_VND_MANAGE_HOST_PORT ||
	    bsg_request->rqst_data.h_venकरोr.venकरोr_cmd[0] == QL_VND_GET_HOST_STATS)
		जाओ skip_chip_chk;

	अगर (vha->hw->flags.port_isolated) अणु
		bsg_reply->result = DID_ERROR;
		/* operation not permitted */
		वापस -EPERM;
	पूर्ण

	अगर (qla2x00_chip_is_करोwn(vha)) अणु
		ql_dbg(ql_dbg_user, vha, 0x709f,
		    "BSG: ISP abort active/needed -- cmd=%d.\n",
		    bsg_request->msgcode);
		वापस -EBUSY;
	पूर्ण

skip_chip_chk:
	ql_dbg(ql_dbg_user, vha, 0x7000,
	    "Entered %s msgcode=0x%x.\n", __func__, bsg_request->msgcode);

	चयन (bsg_request->msgcode) अणु
	हाल FC_BSG_RPT_ELS:
	हाल FC_BSG_HST_ELS_NOLOGIN:
		ret = qla2x00_process_els(bsg_job);
		अवरोध;
	हाल FC_BSG_HST_CT:
		ret = qla2x00_process_ct(bsg_job);
		अवरोध;
	हाल FC_BSG_HST_VENDOR:
		ret = qla2x00_process_venकरोr_specअगरic(bsg_job);
		अवरोध;
	हाल FC_BSG_HST_ADD_RPORT:
	हाल FC_BSG_HST_DEL_RPORT:
	हाल FC_BSG_RPT_CT:
	शेष:
		ql_log(ql_log_warn, vha, 0x705a, "Unsupported BSG request.\n");
		अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

पूर्णांक
qla24xx_bsg_समयout(काष्ठा bsg_job *bsg_job)
अणु
	काष्ठा fc_bsg_reply *bsg_reply = bsg_job->reply;
	scsi_qla_host_t *vha = shost_priv(fc_bsg_to_shost(bsg_job));
	काष्ठा qla_hw_data *ha = vha->hw;
	srb_t *sp;
	पूर्णांक cnt, que;
	अचिन्हित दीर्घ flags;
	काष्ठा req_que *req;

	/* find the bsg job from the active list of commands */
	spin_lock_irqsave(&ha->hardware_lock, flags);
	क्रम (que = 0; que < ha->max_req_queues; que++) अणु
		req = ha->req_q_map[que];
		अगर (!req)
			जारी;

		क्रम (cnt = 1; cnt < req->num_outstanding_cmds; cnt++) अणु
			sp = req->outstanding_cmds[cnt];
			अगर (sp) अणु
				अगर (((sp->type == SRB_CT_CMD) ||
					(sp->type == SRB_ELS_CMD_HST) ||
					(sp->type == SRB_FXIOCB_BCMD))
					&& (sp->u.bsg_job == bsg_job)) अणु
					req->outstanding_cmds[cnt] = शून्य;
					spin_unlock_irqrestore(&ha->hardware_lock, flags);
					अगर (ha->isp_ops->पात_command(sp)) अणु
						ql_log(ql_log_warn, vha, 0x7089,
						    "mbx abort_command "
						    "failed.\n");
						bsg_reply->result = -EIO;
					पूर्ण अन्यथा अणु
						ql_dbg(ql_dbg_user, vha, 0x708a,
						    "mbx abort_command "
						    "success.\n");
						bsg_reply->result = 0;
					पूर्ण
					spin_lock_irqsave(&ha->hardware_lock, flags);
					जाओ करोne;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&ha->hardware_lock, flags);
	ql_log(ql_log_info, vha, 0x708b, "SRB not found to abort.\n");
	bsg_reply->result = -ENXIO;
	वापस 0;

करोne:
	spin_unlock_irqrestore(&ha->hardware_lock, flags);
	sp->मुक्त(sp);
	वापस 0;
पूर्ण
