<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * QLogic Fibre Channel HBA Driver
 * Copyright (c)  2003-2014 QLogic Corporation
 */
#समावेश "qla_def.h"
#समावेश "qla_target.h"
#समावेश <linux/utsname.h>

अटल पूर्णांक qla2x00_sns_ga_nxt(scsi_qla_host_t *, fc_port_t *);
अटल पूर्णांक qla2x00_sns_gid_pt(scsi_qla_host_t *, sw_info_t *);
अटल पूर्णांक qla2x00_sns_gpn_id(scsi_qla_host_t *, sw_info_t *);
अटल पूर्णांक qla2x00_sns_gnn_id(scsi_qla_host_t *, sw_info_t *);
अटल पूर्णांक qla2x00_sns_rft_id(scsi_qla_host_t *);
अटल पूर्णांक qla2x00_sns_rnn_id(scsi_qla_host_t *);
अटल पूर्णांक qla_async_rftid(scsi_qla_host_t *, port_id_t *);
अटल पूर्णांक qla_async_rffid(scsi_qla_host_t *, port_id_t *, u8, u8);
अटल पूर्णांक qla_async_rnnid(scsi_qla_host_t *, port_id_t *, u8*);
अटल पूर्णांक qla_async_rsnn_nn(scsi_qla_host_t *);



/**
 * qla2x00_prep_ms_iocb() - Prepare common MS/CT IOCB fields क्रम SNS CT query.
 * @vha: HA context
 * @arg: CT arguments
 *
 * Returns a poपूर्णांकer to the @vha's ms_iocb.
 */
व्योम *
qla2x00_prep_ms_iocb(scsi_qla_host_t *vha, काष्ठा ct_arg *arg)
अणु
	काष्ठा qla_hw_data *ha = vha->hw;
	ms_iocb_entry_t *ms_pkt;

	ms_pkt = (ms_iocb_entry_t *)arg->iocb;
	स_रखो(ms_pkt, 0, माप(ms_iocb_entry_t));

	ms_pkt->entry_type = MS_IOCB_TYPE;
	ms_pkt->entry_count = 1;
	SET_TARGET_ID(ha, ms_pkt->loop_id, SIMPLE_NAME_SERVER);
	ms_pkt->control_flags = cpu_to_le16(CF_READ | CF_HEAD_TAG);
	ms_pkt->समयout = cpu_to_le16(ha->r_a_tov / 10 * 2);
	ms_pkt->cmd_dsd_count = cpu_to_le16(1);
	ms_pkt->total_dsd_count = cpu_to_le16(2);
	ms_pkt->rsp_bytecount = cpu_to_le32(arg->rsp_size);
	ms_pkt->req_bytecount = cpu_to_le32(arg->req_size);

	put_unaligned_le64(arg->req_dma, &ms_pkt->req_dsd.address);
	ms_pkt->req_dsd.length = ms_pkt->req_bytecount;

	put_unaligned_le64(arg->rsp_dma, &ms_pkt->rsp_dsd.address);
	ms_pkt->rsp_dsd.length = ms_pkt->rsp_bytecount;

	vha->qla_stats.control_requests++;

	वापस (ms_pkt);
पूर्ण

/**
 * qla24xx_prep_ms_iocb() - Prepare common CT IOCB fields क्रम SNS CT query.
 * @vha: HA context
 * @arg: CT arguments
 *
 * Returns a poपूर्णांकer to the @ha's ms_iocb.
 */
व्योम *
qla24xx_prep_ms_iocb(scsi_qla_host_t *vha, काष्ठा ct_arg *arg)
अणु
	काष्ठा qla_hw_data *ha = vha->hw;
	काष्ठा ct_entry_24xx *ct_pkt;

	ct_pkt = (काष्ठा ct_entry_24xx *)arg->iocb;
	स_रखो(ct_pkt, 0, माप(काष्ठा ct_entry_24xx));

	ct_pkt->entry_type = CT_IOCB_TYPE;
	ct_pkt->entry_count = 1;
	ct_pkt->nport_handle = cpu_to_le16(arg->nport_handle);
	ct_pkt->समयout = cpu_to_le16(ha->r_a_tov / 10 * 2);
	ct_pkt->cmd_dsd_count = cpu_to_le16(1);
	ct_pkt->rsp_dsd_count = cpu_to_le16(1);
	ct_pkt->rsp_byte_count = cpu_to_le32(arg->rsp_size);
	ct_pkt->cmd_byte_count = cpu_to_le32(arg->req_size);

	put_unaligned_le64(arg->req_dma, &ct_pkt->dsd[0].address);
	ct_pkt->dsd[0].length = ct_pkt->cmd_byte_count;

	put_unaligned_le64(arg->rsp_dma, &ct_pkt->dsd[1].address);
	ct_pkt->dsd[1].length = ct_pkt->rsp_byte_count;
	ct_pkt->vp_index = vha->vp_idx;

	vha->qla_stats.control_requests++;

	वापस (ct_pkt);
पूर्ण

/**
 * qla2x00_prep_ct_req() - Prepare common CT request fields क्रम SNS query.
 * @p: CT request buffer
 * @cmd: GS command
 * @rsp_size: response size in bytes
 *
 * Returns a poपूर्णांकer to the पूर्णांकitialized @ct_req.
 */
अटल अंतरभूत काष्ठा ct_sns_req *
qla2x00_prep_ct_req(काष्ठा ct_sns_pkt *p, uपूर्णांक16_t cmd, uपूर्णांक16_t rsp_size)
अणु
	स_रखो(p, 0, माप(काष्ठा ct_sns_pkt));

	p->p.req.header.revision = 0x01;
	p->p.req.header.gs_type = 0xFC;
	p->p.req.header.gs_subtype = 0x02;
	p->p.req.command = cpu_to_be16(cmd);
	p->p.req.max_rsp_size = cpu_to_be16((rsp_size - 16) / 4);

	वापस &p->p.req;
पूर्ण

पूर्णांक
qla2x00_chk_ms_status(scsi_qla_host_t *vha, ms_iocb_entry_t *ms_pkt,
    काष्ठा ct_sns_rsp *ct_rsp, स्थिर अक्षर *routine)
अणु
	पूर्णांक rval;
	uपूर्णांक16_t comp_status;
	काष्ठा qla_hw_data *ha = vha->hw;
	bool lid_is_sns = false;

	rval = QLA_FUNCTION_FAILED;
	अगर (ms_pkt->entry_status != 0) अणु
		ql_dbg(ql_dbg_disc, vha, 0x2031,
		    "%s failed, error status (%x) on port_id: %02x%02x%02x.\n",
		    routine, ms_pkt->entry_status, vha->d_id.b.करोमुख्य,
		    vha->d_id.b.area, vha->d_id.b.al_pa);
	पूर्ण अन्यथा अणु
		अगर (IS_FWI2_CAPABLE(ha))
			comp_status = le16_to_cpu(
			    ((काष्ठा ct_entry_24xx *)ms_pkt)->comp_status);
		अन्यथा
			comp_status = le16_to_cpu(ms_pkt->status);
		चयन (comp_status) अणु
		हाल CS_COMPLETE:
		हाल CS_DATA_UNDERRUN:
		हाल CS_DATA_OVERRUN:		/* Overrun? */
			अगर (ct_rsp->header.response !=
			    cpu_to_be16(CT_ACCEPT_RESPONSE)) अणु
				ql_dbg(ql_dbg_disc + ql_dbg_buffer, vha, 0x2077,
				    "%s failed rejected request on port_id: %02x%02x%02x Completion status 0x%x, response 0x%x\n",
				    routine, vha->d_id.b.करोमुख्य,
				    vha->d_id.b.area, vha->d_id.b.al_pa,
				    comp_status, ct_rsp->header.response);
				ql_dump_buffer(ql_dbg_disc + ql_dbg_buffer, vha,
				    0x2078, ct_rsp,
				    दुरत्व(typeof(*ct_rsp), rsp));
				rval = QLA_INVALID_COMMAND;
			पूर्ण अन्यथा
				rval = QLA_SUCCESS;
			अवरोध;
		हाल CS_PORT_LOGGED_OUT:
			अगर (IS_FWI2_CAPABLE(ha)) अणु
				अगर (le16_to_cpu(ms_pkt->loop_id.extended) ==
				    NPH_SNS)
					lid_is_sns = true;
			पूर्ण अन्यथा अणु
				अगर (le16_to_cpu(ms_pkt->loop_id.extended) ==
				    SIMPLE_NAME_SERVER)
					lid_is_sns = true;
			पूर्ण
			अगर (lid_is_sns) अणु
				ql_dbg(ql_dbg_async, vha, 0x502b,
					"%s failed, Name server has logged out",
					routine);
				rval = QLA_NOT_LOGGED_IN;
				set_bit(LOOP_RESYNC_NEEDED, &vha->dpc_flags);
				set_bit(LOCAL_LOOP_UPDATE, &vha->dpc_flags);
			पूर्ण
			अवरोध;
		हाल CS_TIMEOUT:
			rval = QLA_FUNCTION_TIMEOUT;
			fallthrough;
		शेष:
			ql_dbg(ql_dbg_disc, vha, 0x2033,
			    "%s failed, completion status (%x) on port_id: "
			    "%02x%02x%02x.\n", routine, comp_status,
			    vha->d_id.b.करोमुख्य, vha->d_id.b.area,
			    vha->d_id.b.al_pa);
			अवरोध;
		पूर्ण
	पूर्ण
	वापस rval;
पूर्ण

/**
 * qla2x00_ga_nxt() - SNS scan क्रम fabric devices via GA_NXT command.
 * @vha: HA context
 * @fcport: fcport entry to updated
 *
 * Returns 0 on success.
 */
पूर्णांक
qla2x00_ga_nxt(scsi_qla_host_t *vha, fc_port_t *fcport)
अणु
	पूर्णांक		rval;

	ms_iocb_entry_t	*ms_pkt;
	काष्ठा ct_sns_req	*ct_req;
	काष्ठा ct_sns_rsp	*ct_rsp;
	काष्ठा qla_hw_data *ha = vha->hw;
	काष्ठा ct_arg arg;

	अगर (IS_QLA2100(ha) || IS_QLA2200(ha))
		वापस qla2x00_sns_ga_nxt(vha, fcport);

	arg.iocb = ha->ms_iocb;
	arg.req_dma = ha->ct_sns_dma;
	arg.rsp_dma = ha->ct_sns_dma;
	arg.req_size = GA_NXT_REQ_SIZE;
	arg.rsp_size = GA_NXT_RSP_SIZE;
	arg.nport_handle = NPH_SNS;

	/* Issue GA_NXT */
	/* Prepare common MS IOCB */
	ms_pkt = ha->isp_ops->prep_ms_iocb(vha, &arg);

	/* Prepare CT request */
	ct_req = qla2x00_prep_ct_req(ha->ct_sns, GA_NXT_CMD,
	    GA_NXT_RSP_SIZE);
	ct_rsp = &ha->ct_sns->p.rsp;

	/* Prepare CT arguments -- port_id */
	ct_req->req.port_id.port_id = port_id_to_be_id(fcport->d_id);

	/* Execute MS IOCB */
	rval = qla2x00_issue_iocb(vha, ha->ms_iocb, ha->ms_iocb_dma,
	    माप(ms_iocb_entry_t));
	अगर (rval != QLA_SUCCESS) अणु
		/*EMPTY*/
		ql_dbg(ql_dbg_disc, vha, 0x2062,
		    "GA_NXT issue IOCB failed (%d).\n", rval);
	पूर्ण अन्यथा अगर (qla2x00_chk_ms_status(vha, ms_pkt, ct_rsp, "GA_NXT") !=
	    QLA_SUCCESS) अणु
		rval = QLA_FUNCTION_FAILED;
	पूर्ण अन्यथा अणु
		/* Populate fc_port_t entry. */
		fcport->d_id = be_to_port_id(ct_rsp->rsp.ga_nxt.port_id);

		स_नकल(fcport->node_name, ct_rsp->rsp.ga_nxt.node_name,
		    WWN_SIZE);
		स_नकल(fcport->port_name, ct_rsp->rsp.ga_nxt.port_name,
		    WWN_SIZE);

		fcport->fc4_type = (ct_rsp->rsp.ga_nxt.fc4_types[2] & BIT_0) ?
		    FS_FC4TYPE_FCP : FC4_TYPE_OTHER;

		अगर (ct_rsp->rsp.ga_nxt.port_type != NS_N_PORT_TYPE &&
		    ct_rsp->rsp.ga_nxt.port_type != NS_NL_PORT_TYPE)
			fcport->d_id.b.करोमुख्य = 0xf0;

		ql_dbg(ql_dbg_disc, vha, 0x2063,
		    "GA_NXT entry - nn %8phN pn %8phN "
		    "port_id=%02x%02x%02x.\n",
		    fcport->node_name, fcport->port_name,
		    fcport->d_id.b.करोमुख्य, fcport->d_id.b.area,
		    fcport->d_id.b.al_pa);
	पूर्ण

	वापस (rval);
पूर्ण

अटल अंतरभूत पूर्णांक
qla2x00_gid_pt_rsp_size(scsi_qla_host_t *vha)
अणु
	वापस vha->hw->max_fibre_devices * 4 + 16;
पूर्ण

/**
 * qla2x00_gid_pt() - SNS scan क्रम fabric devices via GID_PT command.
 * @vha: HA context
 * @list: चयन info entries to populate
 *
 * NOTE: Non-Nx_Ports are not requested.
 *
 * Returns 0 on success.
 */
पूर्णांक
qla2x00_gid_pt(scsi_qla_host_t *vha, sw_info_t *list)
अणु
	पूर्णांक		rval;
	uपूर्णांक16_t	i;

	ms_iocb_entry_t	*ms_pkt;
	काष्ठा ct_sns_req	*ct_req;
	काष्ठा ct_sns_rsp	*ct_rsp;

	काष्ठा ct_sns_gid_pt_data *gid_data;
	काष्ठा qla_hw_data *ha = vha->hw;
	uपूर्णांक16_t gid_pt_rsp_size;
	काष्ठा ct_arg arg;

	अगर (IS_QLA2100(ha) || IS_QLA2200(ha))
		वापस qla2x00_sns_gid_pt(vha, list);

	gid_data = शून्य;
	gid_pt_rsp_size = qla2x00_gid_pt_rsp_size(vha);

	arg.iocb = ha->ms_iocb;
	arg.req_dma = ha->ct_sns_dma;
	arg.rsp_dma = ha->ct_sns_dma;
	arg.req_size = GID_PT_REQ_SIZE;
	arg.rsp_size = gid_pt_rsp_size;
	arg.nport_handle = NPH_SNS;

	/* Issue GID_PT */
	/* Prepare common MS IOCB */
	ms_pkt = ha->isp_ops->prep_ms_iocb(vha, &arg);

	/* Prepare CT request */
	ct_req = qla2x00_prep_ct_req(ha->ct_sns, GID_PT_CMD, gid_pt_rsp_size);
	ct_rsp = &ha->ct_sns->p.rsp;

	/* Prepare CT arguments -- port_type */
	ct_req->req.gid_pt.port_type = NS_NX_PORT_TYPE;

	/* Execute MS IOCB */
	rval = qla2x00_issue_iocb(vha, ha->ms_iocb, ha->ms_iocb_dma,
	    माप(ms_iocb_entry_t));
	अगर (rval != QLA_SUCCESS) अणु
		/*EMPTY*/
		ql_dbg(ql_dbg_disc, vha, 0x2055,
		    "GID_PT issue IOCB failed (%d).\n", rval);
	पूर्ण अन्यथा अगर (qla2x00_chk_ms_status(vha, ms_pkt, ct_rsp, "GID_PT") !=
	    QLA_SUCCESS) अणु
		rval = QLA_FUNCTION_FAILED;
	पूर्ण अन्यथा अणु
		/* Set port IDs in चयन info list. */
		क्रम (i = 0; i < ha->max_fibre_devices; i++) अणु
			gid_data = &ct_rsp->rsp.gid_pt.entries[i];
			list[i].d_id = be_to_port_id(gid_data->port_id);
			स_रखो(list[i].fabric_port_name, 0, WWN_SIZE);
			list[i].fp_speed = PORT_SPEED_UNKNOWN;

			/* Last one निकास. */
			अगर (gid_data->control_byte & BIT_7) अणु
				list[i].d_id.b.rsvd_1 = gid_data->control_byte;
				अवरोध;
			पूर्ण
		पूर्ण

		/*
		 * If we've used all available slots, then the चयन is
		 * reporting back more devices than we can handle with this
		 * single call.  Return a failed status, and let GA_NXT handle
		 * the overload.
		 */
		अगर (i == ha->max_fibre_devices)
			rval = QLA_FUNCTION_FAILED;
	पूर्ण

	वापस (rval);
पूर्ण

/**
 * qla2x00_gpn_id() - SNS Get Port Name (GPN_ID) query.
 * @vha: HA context
 * @list: चयन info entries to populate
 *
 * Returns 0 on success.
 */
पूर्णांक
qla2x00_gpn_id(scsi_qla_host_t *vha, sw_info_t *list)
अणु
	पूर्णांक		rval = QLA_SUCCESS;
	uपूर्णांक16_t	i;

	ms_iocb_entry_t	*ms_pkt;
	काष्ठा ct_sns_req	*ct_req;
	काष्ठा ct_sns_rsp	*ct_rsp;
	काष्ठा qla_hw_data *ha = vha->hw;
	काष्ठा ct_arg arg;

	अगर (IS_QLA2100(ha) || IS_QLA2200(ha))
		वापस qla2x00_sns_gpn_id(vha, list);

	arg.iocb = ha->ms_iocb;
	arg.req_dma = ha->ct_sns_dma;
	arg.rsp_dma = ha->ct_sns_dma;
	arg.req_size = GPN_ID_REQ_SIZE;
	arg.rsp_size = GPN_ID_RSP_SIZE;
	arg.nport_handle = NPH_SNS;

	क्रम (i = 0; i < ha->max_fibre_devices; i++) अणु
		/* Issue GPN_ID */
		/* Prepare common MS IOCB */
		ms_pkt = ha->isp_ops->prep_ms_iocb(vha, &arg);

		/* Prepare CT request */
		ct_req = qla2x00_prep_ct_req(ha->ct_sns, GPN_ID_CMD,
		    GPN_ID_RSP_SIZE);
		ct_rsp = &ha->ct_sns->p.rsp;

		/* Prepare CT arguments -- port_id */
		ct_req->req.port_id.port_id = port_id_to_be_id(list[i].d_id);

		/* Execute MS IOCB */
		rval = qla2x00_issue_iocb(vha, ha->ms_iocb, ha->ms_iocb_dma,
		    माप(ms_iocb_entry_t));
		अगर (rval != QLA_SUCCESS) अणु
			/*EMPTY*/
			ql_dbg(ql_dbg_disc, vha, 0x2056,
			    "GPN_ID issue IOCB failed (%d).\n", rval);
			अवरोध;
		पूर्ण अन्यथा अगर (qla2x00_chk_ms_status(vha, ms_pkt, ct_rsp,
		    "GPN_ID") != QLA_SUCCESS) अणु
			rval = QLA_FUNCTION_FAILED;
			अवरोध;
		पूर्ण अन्यथा अणु
			/* Save portname */
			स_नकल(list[i].port_name,
			    ct_rsp->rsp.gpn_id.port_name, WWN_SIZE);
		पूर्ण

		/* Last device निकास. */
		अगर (list[i].d_id.b.rsvd_1 != 0)
			अवरोध;
	पूर्ण

	वापस (rval);
पूर्ण

/**
 * qla2x00_gnn_id() - SNS Get Node Name (GNN_ID) query.
 * @vha: HA context
 * @list: चयन info entries to populate
 *
 * Returns 0 on success.
 */
पूर्णांक
qla2x00_gnn_id(scsi_qla_host_t *vha, sw_info_t *list)
अणु
	पूर्णांक		rval = QLA_SUCCESS;
	uपूर्णांक16_t	i;
	काष्ठा qla_hw_data *ha = vha->hw;
	ms_iocb_entry_t	*ms_pkt;
	काष्ठा ct_sns_req	*ct_req;
	काष्ठा ct_sns_rsp	*ct_rsp;
	काष्ठा ct_arg arg;

	अगर (IS_QLA2100(ha) || IS_QLA2200(ha))
		वापस qla2x00_sns_gnn_id(vha, list);

	arg.iocb = ha->ms_iocb;
	arg.req_dma = ha->ct_sns_dma;
	arg.rsp_dma = ha->ct_sns_dma;
	arg.req_size = GNN_ID_REQ_SIZE;
	arg.rsp_size = GNN_ID_RSP_SIZE;
	arg.nport_handle = NPH_SNS;

	क्रम (i = 0; i < ha->max_fibre_devices; i++) अणु
		/* Issue GNN_ID */
		/* Prepare common MS IOCB */
		ms_pkt = ha->isp_ops->prep_ms_iocb(vha, &arg);

		/* Prepare CT request */
		ct_req = qla2x00_prep_ct_req(ha->ct_sns, GNN_ID_CMD,
		    GNN_ID_RSP_SIZE);
		ct_rsp = &ha->ct_sns->p.rsp;

		/* Prepare CT arguments -- port_id */
		ct_req->req.port_id.port_id = port_id_to_be_id(list[i].d_id);

		/* Execute MS IOCB */
		rval = qla2x00_issue_iocb(vha, ha->ms_iocb, ha->ms_iocb_dma,
		    माप(ms_iocb_entry_t));
		अगर (rval != QLA_SUCCESS) अणु
			/*EMPTY*/
			ql_dbg(ql_dbg_disc, vha, 0x2057,
			    "GNN_ID issue IOCB failed (%d).\n", rval);
			अवरोध;
		पूर्ण अन्यथा अगर (qla2x00_chk_ms_status(vha, ms_pkt, ct_rsp,
		    "GNN_ID") != QLA_SUCCESS) अणु
			rval = QLA_FUNCTION_FAILED;
			अवरोध;
		पूर्ण अन्यथा अणु
			/* Save nodename */
			स_नकल(list[i].node_name,
			    ct_rsp->rsp.gnn_id.node_name, WWN_SIZE);

			ql_dbg(ql_dbg_disc, vha, 0x2058,
			    "GID_PT entry - nn %8phN pn %8phN "
			    "portid=%02x%02x%02x.\n",
			    list[i].node_name, list[i].port_name,
			    list[i].d_id.b.करोमुख्य, list[i].d_id.b.area,
			    list[i].d_id.b.al_pa);
		पूर्ण

		/* Last device निकास. */
		अगर (list[i].d_id.b.rsvd_1 != 0)
			अवरोध;
	पूर्ण

	वापस (rval);
पूर्ण

अटल व्योम qla2x00_async_sns_sp_करोne(srb_t *sp, पूर्णांक rc)
अणु
	काष्ठा scsi_qla_host *vha = sp->vha;
	काष्ठा ct_sns_pkt *ct_sns;
	काष्ठा qla_work_evt *e;

	sp->rc = rc;
	अगर (rc == QLA_SUCCESS) अणु
		ql_dbg(ql_dbg_disc, vha, 0x204f,
		    "Async done-%s exiting normally.\n",
		    sp->name);
	पूर्ण अन्यथा अगर (rc == QLA_FUNCTION_TIMEOUT) अणु
		ql_dbg(ql_dbg_disc, vha, 0x204f,
		    "Async done-%s timeout\n", sp->name);
	पूर्ण अन्यथा अणु
		ct_sns = (काष्ठा ct_sns_pkt *)sp->u.iocb_cmd.u.ctarg.rsp;
		स_रखो(ct_sns, 0, माप(*ct_sns));
		sp->retry_count++;
		अगर (sp->retry_count > 3)
			जाओ err;

		ql_dbg(ql_dbg_disc, vha, 0x204f,
		    "Async done-%s fail rc %x.  Retry count %d\n",
		    sp->name, rc, sp->retry_count);

		e = qla2x00_alloc_work(vha, QLA_EVT_SP_RETRY);
		अगर (!e)
			जाओ err2;

		del_समयr(&sp->u.iocb_cmd.समयr);
		e->u.iosb.sp = sp;
		qla2x00_post_work(vha, e);
		वापस;
	पूर्ण

err:
	e = qla2x00_alloc_work(vha, QLA_EVT_UNMAP);
err2:
	अगर (!e) अणु
		/* please ignore kernel warning. otherwise, we have mem leak. */
		अगर (sp->u.iocb_cmd.u.ctarg.req) अणु
			dma_मुक्त_coherent(&vha->hw->pdev->dev,
			    sp->u.iocb_cmd.u.ctarg.req_allocated_size,
			    sp->u.iocb_cmd.u.ctarg.req,
			    sp->u.iocb_cmd.u.ctarg.req_dma);
			sp->u.iocb_cmd.u.ctarg.req = शून्य;
		पूर्ण

		अगर (sp->u.iocb_cmd.u.ctarg.rsp) अणु
			dma_मुक्त_coherent(&vha->hw->pdev->dev,
			    sp->u.iocb_cmd.u.ctarg.rsp_allocated_size,
			    sp->u.iocb_cmd.u.ctarg.rsp,
			    sp->u.iocb_cmd.u.ctarg.rsp_dma);
			sp->u.iocb_cmd.u.ctarg.rsp = शून्य;
		पूर्ण

		sp->मुक्त(sp);

		वापस;
	पूर्ण

	e->u.iosb.sp = sp;
	qla2x00_post_work(vha, e);
पूर्ण

/**
 * qla2x00_rft_id() - SNS Register FC-4 TYPEs (RFT_ID) supported by the HBA.
 * @vha: HA context
 *
 * Returns 0 on success.
 */
पूर्णांक
qla2x00_rft_id(scsi_qla_host_t *vha)
अणु
	काष्ठा qla_hw_data *ha = vha->hw;

	अगर (IS_QLA2100(ha) || IS_QLA2200(ha))
		वापस qla2x00_sns_rft_id(vha);

	वापस qla_async_rftid(vha, &vha->d_id);
पूर्ण

अटल पूर्णांक qla_async_rftid(scsi_qla_host_t *vha, port_id_t *d_id)
अणु
	पूर्णांक rval = QLA_MEMORY_ALLOC_FAILED;
	काष्ठा ct_sns_req *ct_req;
	srb_t *sp;
	काष्ठा ct_sns_pkt *ct_sns;

	अगर (!vha->flags.online)
		जाओ करोne;

	sp = qla2x00_get_sp(vha, शून्य, GFP_KERNEL);
	अगर (!sp)
		जाओ करोne;

	sp->type = SRB_CT_PTHRU_CMD;
	sp->name = "rft_id";
	qla2x00_init_समयr(sp, qla2x00_get_async_समयout(vha) + 2);

	sp->u.iocb_cmd.u.ctarg.req = dma_alloc_coherent(&vha->hw->pdev->dev,
	    माप(काष्ठा ct_sns_pkt), &sp->u.iocb_cmd.u.ctarg.req_dma,
	    GFP_KERNEL);
	sp->u.iocb_cmd.u.ctarg.req_allocated_size = माप(काष्ठा ct_sns_pkt);
	अगर (!sp->u.iocb_cmd.u.ctarg.req) अणु
		ql_log(ql_log_warn, vha, 0xd041,
		    "%s: Failed to allocate ct_sns request.\n",
		    __func__);
		जाओ करोne_मुक्त_sp;
	पूर्ण

	sp->u.iocb_cmd.u.ctarg.rsp = dma_alloc_coherent(&vha->hw->pdev->dev,
	    माप(काष्ठा ct_sns_pkt), &sp->u.iocb_cmd.u.ctarg.rsp_dma,
	    GFP_KERNEL);
	sp->u.iocb_cmd.u.ctarg.rsp_allocated_size = माप(काष्ठा ct_sns_pkt);
	अगर (!sp->u.iocb_cmd.u.ctarg.rsp) अणु
		ql_log(ql_log_warn, vha, 0xd042,
		    "%s: Failed to allocate ct_sns request.\n",
		    __func__);
		जाओ करोne_मुक्त_sp;
	पूर्ण
	ct_sns = (काष्ठा ct_sns_pkt *)sp->u.iocb_cmd.u.ctarg.rsp;
	स_रखो(ct_sns, 0, माप(*ct_sns));
	ct_sns = (काष्ठा ct_sns_pkt *)sp->u.iocb_cmd.u.ctarg.req;

	/* Prepare CT request */
	ct_req = qla2x00_prep_ct_req(ct_sns, RFT_ID_CMD, RFT_ID_RSP_SIZE);

	/* Prepare CT arguments -- port_id, FC-4 types */
	ct_req->req.rft_id.port_id = port_id_to_be_id(vha->d_id);
	ct_req->req.rft_id.fc4_types[2] = 0x01;		/* FCP-3 */

	अगर (vha->flags.nvme_enabled)
		ct_req->req.rft_id.fc4_types[6] = 1;    /* NVMe type 28h */

	sp->u.iocb_cmd.u.ctarg.req_size = RFT_ID_REQ_SIZE;
	sp->u.iocb_cmd.u.ctarg.rsp_size = RFT_ID_RSP_SIZE;
	sp->u.iocb_cmd.u.ctarg.nport_handle = NPH_SNS;
	sp->u.iocb_cmd.समयout = qla2x00_async_iocb_समयout;
	sp->करोne = qla2x00_async_sns_sp_करोne;

	ql_dbg(ql_dbg_disc, vha, 0xffff,
	    "Async-%s - hdl=%x portid %06x.\n",
	    sp->name, sp->handle, d_id->b24);

	rval = qla2x00_start_sp(sp);
	अगर (rval != QLA_SUCCESS) अणु
		ql_dbg(ql_dbg_disc, vha, 0x2043,
		    "RFT_ID issue IOCB failed (%d).\n", rval);
		जाओ करोne_मुक्त_sp;
	पूर्ण
	वापस rval;
करोne_मुक्त_sp:
	sp->मुक्त(sp);
करोne:
	वापस rval;
पूर्ण

/**
 * qla2x00_rff_id() - SNS Register FC-4 Features (RFF_ID) supported by the HBA.
 * @vha: HA context
 * @type: not used
 *
 * Returns 0 on success.
 */
पूर्णांक
qla2x00_rff_id(scsi_qla_host_t *vha, u8 type)
अणु
	काष्ठा qla_hw_data *ha = vha->hw;

	अगर (IS_QLA2100(ha) || IS_QLA2200(ha)) अणु
		ql_dbg(ql_dbg_disc, vha, 0x2046,
		    "RFF_ID call not supported on ISP2100/ISP2200.\n");
		वापस (QLA_SUCCESS);
	पूर्ण

	वापस qla_async_rffid(vha, &vha->d_id, qlt_rff_id(vha),
	    FC4_TYPE_FCP_SCSI);
पूर्ण

अटल पूर्णांक qla_async_rffid(scsi_qla_host_t *vha, port_id_t *d_id,
    u8 fc4feature, u8 fc4type)
अणु
	पूर्णांक rval = QLA_MEMORY_ALLOC_FAILED;
	काष्ठा ct_sns_req *ct_req;
	srb_t *sp;
	काष्ठा ct_sns_pkt *ct_sns;

	sp = qla2x00_get_sp(vha, शून्य, GFP_KERNEL);
	अगर (!sp)
		जाओ करोne;

	sp->type = SRB_CT_PTHRU_CMD;
	sp->name = "rff_id";
	qla2x00_init_समयr(sp, qla2x00_get_async_समयout(vha) + 2);

	sp->u.iocb_cmd.u.ctarg.req = dma_alloc_coherent(&vha->hw->pdev->dev,
	    माप(काष्ठा ct_sns_pkt), &sp->u.iocb_cmd.u.ctarg.req_dma,
	    GFP_KERNEL);
	sp->u.iocb_cmd.u.ctarg.req_allocated_size = माप(काष्ठा ct_sns_pkt);
	अगर (!sp->u.iocb_cmd.u.ctarg.req) अणु
		ql_log(ql_log_warn, vha, 0xd041,
		    "%s: Failed to allocate ct_sns request.\n",
		    __func__);
		जाओ करोne_मुक्त_sp;
	पूर्ण

	sp->u.iocb_cmd.u.ctarg.rsp = dma_alloc_coherent(&vha->hw->pdev->dev,
	    माप(काष्ठा ct_sns_pkt), &sp->u.iocb_cmd.u.ctarg.rsp_dma,
	    GFP_KERNEL);
	sp->u.iocb_cmd.u.ctarg.rsp_allocated_size = माप(काष्ठा ct_sns_pkt);
	अगर (!sp->u.iocb_cmd.u.ctarg.rsp) अणु
		ql_log(ql_log_warn, vha, 0xd042,
		    "%s: Failed to allocate ct_sns request.\n",
		    __func__);
		जाओ करोne_मुक्त_sp;
	पूर्ण
	ct_sns = (काष्ठा ct_sns_pkt *)sp->u.iocb_cmd.u.ctarg.rsp;
	स_रखो(ct_sns, 0, माप(*ct_sns));
	ct_sns = (काष्ठा ct_sns_pkt *)sp->u.iocb_cmd.u.ctarg.req;

	/* Prepare CT request */
	ct_req = qla2x00_prep_ct_req(ct_sns, RFF_ID_CMD, RFF_ID_RSP_SIZE);

	/* Prepare CT arguments -- port_id, FC-4 feature, FC-4 type */
	ct_req->req.rff_id.port_id = port_id_to_be_id(*d_id);
	ct_req->req.rff_id.fc4_feature = fc4feature;
	ct_req->req.rff_id.fc4_type = fc4type;		/* SCSI - FCP */

	sp->u.iocb_cmd.u.ctarg.req_size = RFF_ID_REQ_SIZE;
	sp->u.iocb_cmd.u.ctarg.rsp_size = RFF_ID_RSP_SIZE;
	sp->u.iocb_cmd.u.ctarg.nport_handle = NPH_SNS;
	sp->u.iocb_cmd.समयout = qla2x00_async_iocb_समयout;
	sp->करोne = qla2x00_async_sns_sp_करोne;

	ql_dbg(ql_dbg_disc, vha, 0xffff,
	    "Async-%s - hdl=%x portid %06x feature %x type %x.\n",
	    sp->name, sp->handle, d_id->b24, fc4feature, fc4type);

	rval = qla2x00_start_sp(sp);
	अगर (rval != QLA_SUCCESS) अणु
		ql_dbg(ql_dbg_disc, vha, 0x2047,
		    "RFF_ID issue IOCB failed (%d).\n", rval);
		जाओ करोne_मुक्त_sp;
	पूर्ण

	वापस rval;

करोne_मुक्त_sp:
	sp->मुक्त(sp);
करोne:
	वापस rval;
पूर्ण

/**
 * qla2x00_rnn_id() - SNS Register Node Name (RNN_ID) of the HBA.
 * @vha: HA context
 *
 * Returns 0 on success.
 */
पूर्णांक
qla2x00_rnn_id(scsi_qla_host_t *vha)
अणु
	काष्ठा qla_hw_data *ha = vha->hw;

	अगर (IS_QLA2100(ha) || IS_QLA2200(ha))
		वापस qla2x00_sns_rnn_id(vha);

	वापस  qla_async_rnnid(vha, &vha->d_id, vha->node_name);
पूर्ण

अटल पूर्णांक qla_async_rnnid(scsi_qla_host_t *vha, port_id_t *d_id,
	u8 *node_name)
अणु
	पूर्णांक rval = QLA_MEMORY_ALLOC_FAILED;
	काष्ठा ct_sns_req *ct_req;
	srb_t *sp;
	काष्ठा ct_sns_pkt *ct_sns;

	sp = qla2x00_get_sp(vha, शून्य, GFP_KERNEL);
	अगर (!sp)
		जाओ करोne;

	sp->type = SRB_CT_PTHRU_CMD;
	sp->name = "rnid";
	qla2x00_init_समयr(sp, qla2x00_get_async_समयout(vha) + 2);

	sp->u.iocb_cmd.u.ctarg.req = dma_alloc_coherent(&vha->hw->pdev->dev,
	    माप(काष्ठा ct_sns_pkt), &sp->u.iocb_cmd.u.ctarg.req_dma,
	    GFP_KERNEL);
	sp->u.iocb_cmd.u.ctarg.req_allocated_size = माप(काष्ठा ct_sns_pkt);
	अगर (!sp->u.iocb_cmd.u.ctarg.req) अणु
		ql_log(ql_log_warn, vha, 0xd041,
		    "%s: Failed to allocate ct_sns request.\n",
		    __func__);
		जाओ करोne_मुक्त_sp;
	पूर्ण

	sp->u.iocb_cmd.u.ctarg.rsp = dma_alloc_coherent(&vha->hw->pdev->dev,
	    माप(काष्ठा ct_sns_pkt), &sp->u.iocb_cmd.u.ctarg.rsp_dma,
	    GFP_KERNEL);
	sp->u.iocb_cmd.u.ctarg.rsp_allocated_size = माप(काष्ठा ct_sns_pkt);
	अगर (!sp->u.iocb_cmd.u.ctarg.rsp) अणु
		ql_log(ql_log_warn, vha, 0xd042,
		    "%s: Failed to allocate ct_sns request.\n",
		    __func__);
		जाओ करोne_मुक्त_sp;
	पूर्ण
	ct_sns = (काष्ठा ct_sns_pkt *)sp->u.iocb_cmd.u.ctarg.rsp;
	स_रखो(ct_sns, 0, माप(*ct_sns));
	ct_sns = (काष्ठा ct_sns_pkt *)sp->u.iocb_cmd.u.ctarg.req;

	/* Prepare CT request */
	ct_req = qla2x00_prep_ct_req(ct_sns, RNN_ID_CMD, RNN_ID_RSP_SIZE);

	/* Prepare CT arguments -- port_id, node_name */
	ct_req->req.rnn_id.port_id = port_id_to_be_id(vha->d_id);
	स_नकल(ct_req->req.rnn_id.node_name, vha->node_name, WWN_SIZE);

	sp->u.iocb_cmd.u.ctarg.req_size = RNN_ID_REQ_SIZE;
	sp->u.iocb_cmd.u.ctarg.rsp_size = RNN_ID_RSP_SIZE;
	sp->u.iocb_cmd.u.ctarg.nport_handle = NPH_SNS;

	sp->u.iocb_cmd.समयout = qla2x00_async_iocb_समयout;
	sp->करोne = qla2x00_async_sns_sp_करोne;

	ql_dbg(ql_dbg_disc, vha, 0xffff,
	    "Async-%s - hdl=%x portid %06x\n",
	    sp->name, sp->handle, d_id->b24);

	rval = qla2x00_start_sp(sp);
	अगर (rval != QLA_SUCCESS) अणु
		ql_dbg(ql_dbg_disc, vha, 0x204d,
		    "RNN_ID issue IOCB failed (%d).\n", rval);
		जाओ करोne_मुक्त_sp;
	पूर्ण

	वापस rval;

करोne_मुक्त_sp:
	sp->मुक्त(sp);
करोne:
	वापस rval;
पूर्ण

माप_प्रकार
qla2x00_get_sym_node_name(scsi_qla_host_t *vha, uपूर्णांक8_t *snn, माप_प्रकार size)
अणु
	काष्ठा qla_hw_data *ha = vha->hw;

	अगर (IS_QLAFX00(ha))
		वापस scnम_लिखो(snn, size, "%s FW:v%s DVR:v%s",
		    ha->model_number, ha->mr.fw_version, qla2x00_version_str);

	वापस scnम_लिखो(snn, size, "%s FW:v%d.%02d.%02d DVR:v%s",
	    ha->model_number, ha->fw_major_version, ha->fw_minor_version,
	    ha->fw_subminor_version, qla2x00_version_str);
पूर्ण

/**
 * qla2x00_rsnn_nn() - SNS Register Symbolic Node Name (RSNN_NN) of the HBA.
 * @vha: HA context
 *
 * Returns 0 on success.
 */
पूर्णांक
qla2x00_rsnn_nn(scsi_qla_host_t *vha)
अणु
	काष्ठा qla_hw_data *ha = vha->hw;

	अगर (IS_QLA2100(ha) || IS_QLA2200(ha)) अणु
		ql_dbg(ql_dbg_disc, vha, 0x2050,
		    "RSNN_ID call unsupported on ISP2100/ISP2200.\n");
		वापस (QLA_SUCCESS);
	पूर्ण

	वापस qla_async_rsnn_nn(vha);
पूर्ण

अटल पूर्णांक qla_async_rsnn_nn(scsi_qla_host_t *vha)
अणु
	पूर्णांक rval = QLA_MEMORY_ALLOC_FAILED;
	काष्ठा ct_sns_req *ct_req;
	srb_t *sp;
	काष्ठा ct_sns_pkt *ct_sns;

	sp = qla2x00_get_sp(vha, शून्य, GFP_KERNEL);
	अगर (!sp)
		जाओ करोne;

	sp->type = SRB_CT_PTHRU_CMD;
	sp->name = "rsnn_nn";
	qla2x00_init_समयr(sp, qla2x00_get_async_समयout(vha) + 2);

	sp->u.iocb_cmd.u.ctarg.req = dma_alloc_coherent(&vha->hw->pdev->dev,
	    माप(काष्ठा ct_sns_pkt), &sp->u.iocb_cmd.u.ctarg.req_dma,
	    GFP_KERNEL);
	sp->u.iocb_cmd.u.ctarg.req_allocated_size = माप(काष्ठा ct_sns_pkt);
	अगर (!sp->u.iocb_cmd.u.ctarg.req) अणु
		ql_log(ql_log_warn, vha, 0xd041,
		    "%s: Failed to allocate ct_sns request.\n",
		    __func__);
		जाओ करोne_मुक्त_sp;
	पूर्ण

	sp->u.iocb_cmd.u.ctarg.rsp = dma_alloc_coherent(&vha->hw->pdev->dev,
	    माप(काष्ठा ct_sns_pkt), &sp->u.iocb_cmd.u.ctarg.rsp_dma,
	    GFP_KERNEL);
	sp->u.iocb_cmd.u.ctarg.rsp_allocated_size = माप(काष्ठा ct_sns_pkt);
	अगर (!sp->u.iocb_cmd.u.ctarg.rsp) अणु
		ql_log(ql_log_warn, vha, 0xd042,
		    "%s: Failed to allocate ct_sns request.\n",
		    __func__);
		जाओ करोne_मुक्त_sp;
	पूर्ण
	ct_sns = (काष्ठा ct_sns_pkt *)sp->u.iocb_cmd.u.ctarg.rsp;
	स_रखो(ct_sns, 0, माप(*ct_sns));
	ct_sns = (काष्ठा ct_sns_pkt *)sp->u.iocb_cmd.u.ctarg.req;

	/* Prepare CT request */
	ct_req = qla2x00_prep_ct_req(ct_sns, RSNN_NN_CMD, RSNN_NN_RSP_SIZE);

	/* Prepare CT arguments -- node_name, symbolic node_name, size */
	स_नकल(ct_req->req.rsnn_nn.node_name, vha->node_name, WWN_SIZE);

	/* Prepare the Symbolic Node Name */
	qla2x00_get_sym_node_name(vha, ct_req->req.rsnn_nn.sym_node_name,
	    माप(ct_req->req.rsnn_nn.sym_node_name));
	ct_req->req.rsnn_nn.name_len =
	    (uपूर्णांक8_t)म_माप(ct_req->req.rsnn_nn.sym_node_name);


	sp->u.iocb_cmd.u.ctarg.req_size = 24 + 1 + ct_req->req.rsnn_nn.name_len;
	sp->u.iocb_cmd.u.ctarg.rsp_size = RSNN_NN_RSP_SIZE;
	sp->u.iocb_cmd.u.ctarg.nport_handle = NPH_SNS;

	sp->u.iocb_cmd.समयout = qla2x00_async_iocb_समयout;
	sp->करोne = qla2x00_async_sns_sp_करोne;

	ql_dbg(ql_dbg_disc, vha, 0xffff,
	    "Async-%s - hdl=%x.\n",
	    sp->name, sp->handle);

	rval = qla2x00_start_sp(sp);
	अगर (rval != QLA_SUCCESS) अणु
		ql_dbg(ql_dbg_disc, vha, 0x2043,
		    "RFT_ID issue IOCB failed (%d).\n", rval);
		जाओ करोne_मुक्त_sp;
	पूर्ण

	वापस rval;

करोne_मुक्त_sp:
	sp->मुक्त(sp);
करोne:
	वापस rval;
पूर्ण

/**
 * qla2x00_prep_sns_cmd() - Prepare common SNS command request fields क्रम query.
 * @vha: HA context
 * @cmd: GS command
 * @scmd_len: Subcommand length
 * @data_size: response size in bytes
 *
 * Returns a poपूर्णांकer to the @ha's sns_cmd.
 */
अटल अंतरभूत काष्ठा sns_cmd_pkt *
qla2x00_prep_sns_cmd(scsi_qla_host_t *vha, uपूर्णांक16_t cmd, uपूर्णांक16_t scmd_len,
    uपूर्णांक16_t data_size)
अणु
	uपूर्णांक16_t		wc;
	काष्ठा sns_cmd_pkt	*sns_cmd;
	काष्ठा qla_hw_data *ha = vha->hw;

	sns_cmd = ha->sns_cmd;
	स_रखो(sns_cmd, 0, माप(काष्ठा sns_cmd_pkt));
	wc = data_size / 2;			/* Size in 16bit words. */
	sns_cmd->p.cmd.buffer_length = cpu_to_le16(wc);
	put_unaligned_le64(ha->sns_cmd_dma, &sns_cmd->p.cmd.buffer_address);
	sns_cmd->p.cmd.subcommand_length = cpu_to_le16(scmd_len);
	sns_cmd->p.cmd.subcommand = cpu_to_le16(cmd);
	wc = (data_size - 16) / 4;		/* Size in 32bit words. */
	sns_cmd->p.cmd.size = cpu_to_le16(wc);

	vha->qla_stats.control_requests++;

	वापस (sns_cmd);
पूर्ण

/**
 * qla2x00_sns_ga_nxt() - SNS scan क्रम fabric devices via GA_NXT command.
 * @vha: HA context
 * @fcport: fcport entry to updated
 *
 * This command uses the old Exectute SNS Command mailbox routine.
 *
 * Returns 0 on success.
 */
अटल पूर्णांक
qla2x00_sns_ga_nxt(scsi_qla_host_t *vha, fc_port_t *fcport)
अणु
	पूर्णांक		rval = QLA_SUCCESS;
	काष्ठा qla_hw_data *ha = vha->hw;
	काष्ठा sns_cmd_pkt	*sns_cmd;

	/* Issue GA_NXT. */
	/* Prepare SNS command request. */
	sns_cmd = qla2x00_prep_sns_cmd(vha, GA_NXT_CMD, GA_NXT_SNS_SCMD_LEN,
	    GA_NXT_SNS_DATA_SIZE);

	/* Prepare SNS command arguments -- port_id. */
	sns_cmd->p.cmd.param[0] = fcport->d_id.b.al_pa;
	sns_cmd->p.cmd.param[1] = fcport->d_id.b.area;
	sns_cmd->p.cmd.param[2] = fcport->d_id.b.करोमुख्य;

	/* Execute SNS command. */
	rval = qla2x00_send_sns(vha, ha->sns_cmd_dma, GA_NXT_SNS_CMD_SIZE / 2,
	    माप(काष्ठा sns_cmd_pkt));
	अगर (rval != QLA_SUCCESS) अणु
		/*EMPTY*/
		ql_dbg(ql_dbg_disc, vha, 0x205f,
		    "GA_NXT Send SNS failed (%d).\n", rval);
	पूर्ण अन्यथा अगर (sns_cmd->p.gan_data[8] != 0x80 ||
	    sns_cmd->p.gan_data[9] != 0x02) अणु
		ql_dbg(ql_dbg_disc + ql_dbg_buffer, vha, 0x2084,
		    "GA_NXT failed, rejected request ga_nxt_rsp:\n");
		ql_dump_buffer(ql_dbg_disc + ql_dbg_buffer, vha, 0x2074,
		    sns_cmd->p.gan_data, 16);
		rval = QLA_FUNCTION_FAILED;
	पूर्ण अन्यथा अणु
		/* Populate fc_port_t entry. */
		fcport->d_id.b.करोमुख्य = sns_cmd->p.gan_data[17];
		fcport->d_id.b.area = sns_cmd->p.gan_data[18];
		fcport->d_id.b.al_pa = sns_cmd->p.gan_data[19];

		स_नकल(fcport->node_name, &sns_cmd->p.gan_data[284], WWN_SIZE);
		स_नकल(fcport->port_name, &sns_cmd->p.gan_data[20], WWN_SIZE);

		अगर (sns_cmd->p.gan_data[16] != NS_N_PORT_TYPE &&
		    sns_cmd->p.gan_data[16] != NS_NL_PORT_TYPE)
			fcport->d_id.b.करोमुख्य = 0xf0;

		ql_dbg(ql_dbg_disc, vha, 0x2061,
		    "GA_NXT entry - nn %8phN pn %8phN "
		    "port_id=%02x%02x%02x.\n",
		    fcport->node_name, fcport->port_name,
		    fcport->d_id.b.करोमुख्य, fcport->d_id.b.area,
		    fcport->d_id.b.al_pa);
	पूर्ण

	वापस (rval);
पूर्ण

/**
 * qla2x00_sns_gid_pt() - SNS scan क्रम fabric devices via GID_PT command.
 * @vha: HA context
 * @list: चयन info entries to populate
 *
 * This command uses the old Exectute SNS Command mailbox routine.
 *
 * NOTE: Non-Nx_Ports are not requested.
 *
 * Returns 0 on success.
 */
अटल पूर्णांक
qla2x00_sns_gid_pt(scsi_qla_host_t *vha, sw_info_t *list)
अणु
	पूर्णांक		rval;
	काष्ठा qla_hw_data *ha = vha->hw;
	uपूर्णांक16_t	i;
	uपूर्णांक8_t		*entry;
	काष्ठा sns_cmd_pkt	*sns_cmd;
	uपूर्णांक16_t gid_pt_sns_data_size;

	gid_pt_sns_data_size = qla2x00_gid_pt_rsp_size(vha);

	/* Issue GID_PT. */
	/* Prepare SNS command request. */
	sns_cmd = qla2x00_prep_sns_cmd(vha, GID_PT_CMD, GID_PT_SNS_SCMD_LEN,
	    gid_pt_sns_data_size);

	/* Prepare SNS command arguments -- port_type. */
	sns_cmd->p.cmd.param[0] = NS_NX_PORT_TYPE;

	/* Execute SNS command. */
	rval = qla2x00_send_sns(vha, ha->sns_cmd_dma, GID_PT_SNS_CMD_SIZE / 2,
	    माप(काष्ठा sns_cmd_pkt));
	अगर (rval != QLA_SUCCESS) अणु
		/*EMPTY*/
		ql_dbg(ql_dbg_disc, vha, 0x206d,
		    "GID_PT Send SNS failed (%d).\n", rval);
	पूर्ण अन्यथा अगर (sns_cmd->p.gid_data[8] != 0x80 ||
	    sns_cmd->p.gid_data[9] != 0x02) अणु
		ql_dbg(ql_dbg_disc, vha, 0x202f,
		    "GID_PT failed, rejected request, gid_rsp:\n");
		ql_dump_buffer(ql_dbg_disc + ql_dbg_buffer, vha, 0x2081,
		    sns_cmd->p.gid_data, 16);
		rval = QLA_FUNCTION_FAILED;
	पूर्ण अन्यथा अणु
		/* Set port IDs in चयन info list. */
		क्रम (i = 0; i < ha->max_fibre_devices; i++) अणु
			entry = &sns_cmd->p.gid_data[(i * 4) + 16];
			list[i].d_id.b.करोमुख्य = entry[1];
			list[i].d_id.b.area = entry[2];
			list[i].d_id.b.al_pa = entry[3];

			/* Last one निकास. */
			अगर (entry[0] & BIT_7) अणु
				list[i].d_id.b.rsvd_1 = entry[0];
				अवरोध;
			पूर्ण
		पूर्ण

		/*
		 * If we've used all available slots, then the चयन is
		 * reporting back more devices that we can handle with this
		 * single call.  Return a failed status, and let GA_NXT handle
		 * the overload.
		 */
		अगर (i == ha->max_fibre_devices)
			rval = QLA_FUNCTION_FAILED;
	पूर्ण

	वापस (rval);
पूर्ण

/**
 * qla2x00_sns_gpn_id() - SNS Get Port Name (GPN_ID) query.
 * @vha: HA context
 * @list: चयन info entries to populate
 *
 * This command uses the old Exectute SNS Command mailbox routine.
 *
 * Returns 0 on success.
 */
अटल पूर्णांक
qla2x00_sns_gpn_id(scsi_qla_host_t *vha, sw_info_t *list)
अणु
	पूर्णांक		rval = QLA_SUCCESS;
	काष्ठा qla_hw_data *ha = vha->hw;
	uपूर्णांक16_t	i;
	काष्ठा sns_cmd_pkt	*sns_cmd;

	क्रम (i = 0; i < ha->max_fibre_devices; i++) अणु
		/* Issue GPN_ID */
		/* Prepare SNS command request. */
		sns_cmd = qla2x00_prep_sns_cmd(vha, GPN_ID_CMD,
		    GPN_ID_SNS_SCMD_LEN, GPN_ID_SNS_DATA_SIZE);

		/* Prepare SNS command arguments -- port_id. */
		sns_cmd->p.cmd.param[0] = list[i].d_id.b.al_pa;
		sns_cmd->p.cmd.param[1] = list[i].d_id.b.area;
		sns_cmd->p.cmd.param[2] = list[i].d_id.b.करोमुख्य;

		/* Execute SNS command. */
		rval = qla2x00_send_sns(vha, ha->sns_cmd_dma,
		    GPN_ID_SNS_CMD_SIZE / 2, माप(काष्ठा sns_cmd_pkt));
		अगर (rval != QLA_SUCCESS) अणु
			/*EMPTY*/
			ql_dbg(ql_dbg_disc, vha, 0x2032,
			    "GPN_ID Send SNS failed (%d).\n", rval);
		पूर्ण अन्यथा अगर (sns_cmd->p.gpn_data[8] != 0x80 ||
		    sns_cmd->p.gpn_data[9] != 0x02) अणु
			ql_dbg(ql_dbg_disc + ql_dbg_buffer, vha, 0x207e,
			    "GPN_ID failed, rejected request, gpn_rsp:\n");
			ql_dump_buffer(ql_dbg_disc + ql_dbg_buffer, vha, 0x207f,
			    sns_cmd->p.gpn_data, 16);
			rval = QLA_FUNCTION_FAILED;
		पूर्ण अन्यथा अणु
			/* Save portname */
			स_नकल(list[i].port_name, &sns_cmd->p.gpn_data[16],
			    WWN_SIZE);
		पूर्ण

		/* Last device निकास. */
		अगर (list[i].d_id.b.rsvd_1 != 0)
			अवरोध;
	पूर्ण

	वापस (rval);
पूर्ण

/**
 * qla2x00_sns_gnn_id() - SNS Get Node Name (GNN_ID) query.
 * @vha: HA context
 * @list: चयन info entries to populate
 *
 * This command uses the old Exectute SNS Command mailbox routine.
 *
 * Returns 0 on success.
 */
अटल पूर्णांक
qla2x00_sns_gnn_id(scsi_qla_host_t *vha, sw_info_t *list)
अणु
	पूर्णांक		rval = QLA_SUCCESS;
	काष्ठा qla_hw_data *ha = vha->hw;
	uपूर्णांक16_t	i;
	काष्ठा sns_cmd_pkt	*sns_cmd;

	क्रम (i = 0; i < ha->max_fibre_devices; i++) अणु
		/* Issue GNN_ID */
		/* Prepare SNS command request. */
		sns_cmd = qla2x00_prep_sns_cmd(vha, GNN_ID_CMD,
		    GNN_ID_SNS_SCMD_LEN, GNN_ID_SNS_DATA_SIZE);

		/* Prepare SNS command arguments -- port_id. */
		sns_cmd->p.cmd.param[0] = list[i].d_id.b.al_pa;
		sns_cmd->p.cmd.param[1] = list[i].d_id.b.area;
		sns_cmd->p.cmd.param[2] = list[i].d_id.b.करोमुख्य;

		/* Execute SNS command. */
		rval = qla2x00_send_sns(vha, ha->sns_cmd_dma,
		    GNN_ID_SNS_CMD_SIZE / 2, माप(काष्ठा sns_cmd_pkt));
		अगर (rval != QLA_SUCCESS) अणु
			/*EMPTY*/
			ql_dbg(ql_dbg_disc, vha, 0x203f,
			    "GNN_ID Send SNS failed (%d).\n", rval);
		पूर्ण अन्यथा अगर (sns_cmd->p.gnn_data[8] != 0x80 ||
		    sns_cmd->p.gnn_data[9] != 0x02) अणु
			ql_dbg(ql_dbg_disc + ql_dbg_buffer, vha, 0x2082,
			    "GNN_ID failed, rejected request, gnn_rsp:\n");
			ql_dump_buffer(ql_dbg_disc + ql_dbg_buffer, vha, 0x207a,
			    sns_cmd->p.gnn_data, 16);
			rval = QLA_FUNCTION_FAILED;
		पूर्ण अन्यथा अणु
			/* Save nodename */
			स_नकल(list[i].node_name, &sns_cmd->p.gnn_data[16],
			    WWN_SIZE);

			ql_dbg(ql_dbg_disc, vha, 0x206e,
			    "GID_PT entry - nn %8phN pn %8phN "
			    "port_id=%02x%02x%02x.\n",
			    list[i].node_name, list[i].port_name,
			    list[i].d_id.b.करोमुख्य, list[i].d_id.b.area,
			    list[i].d_id.b.al_pa);
		पूर्ण

		/* Last device निकास. */
		अगर (list[i].d_id.b.rsvd_1 != 0)
			अवरोध;
	पूर्ण

	वापस (rval);
पूर्ण

/**
 * qla2x00_sns_rft_id() - SNS Register FC-4 TYPEs (RFT_ID) supported by the HBA.
 * @vha: HA context
 *
 * This command uses the old Exectute SNS Command mailbox routine.
 *
 * Returns 0 on success.
 */
अटल पूर्णांक
qla2x00_sns_rft_id(scsi_qla_host_t *vha)
अणु
	पूर्णांक		rval;
	काष्ठा qla_hw_data *ha = vha->hw;
	काष्ठा sns_cmd_pkt	*sns_cmd;

	/* Issue RFT_ID. */
	/* Prepare SNS command request. */
	sns_cmd = qla2x00_prep_sns_cmd(vha, RFT_ID_CMD, RFT_ID_SNS_SCMD_LEN,
	    RFT_ID_SNS_DATA_SIZE);

	/* Prepare SNS command arguments -- port_id, FC-4 types */
	sns_cmd->p.cmd.param[0] = vha->d_id.b.al_pa;
	sns_cmd->p.cmd.param[1] = vha->d_id.b.area;
	sns_cmd->p.cmd.param[2] = vha->d_id.b.करोमुख्य;

	sns_cmd->p.cmd.param[5] = 0x01;			/* FCP-3 */

	/* Execute SNS command. */
	rval = qla2x00_send_sns(vha, ha->sns_cmd_dma, RFT_ID_SNS_CMD_SIZE / 2,
	    माप(काष्ठा sns_cmd_pkt));
	अगर (rval != QLA_SUCCESS) अणु
		/*EMPTY*/
		ql_dbg(ql_dbg_disc, vha, 0x2060,
		    "RFT_ID Send SNS failed (%d).\n", rval);
	पूर्ण अन्यथा अगर (sns_cmd->p.rft_data[8] != 0x80 ||
	    sns_cmd->p.rft_data[9] != 0x02) अणु
		ql_dbg(ql_dbg_disc + ql_dbg_buffer, vha, 0x2083,
		    "RFT_ID failed, rejected request rft_rsp:\n");
		ql_dump_buffer(ql_dbg_disc + ql_dbg_buffer, vha, 0x2080,
		    sns_cmd->p.rft_data, 16);
		rval = QLA_FUNCTION_FAILED;
	पूर्ण अन्यथा अणु
		ql_dbg(ql_dbg_disc, vha, 0x2073,
		    "RFT_ID exiting normally.\n");
	पूर्ण

	वापस (rval);
पूर्ण

/**
 * qla2x00_sns_rnn_id() - SNS Register Node Name (RNN_ID) of the HBA.
 * @vha: HA context
 *
 * This command uses the old Exectute SNS Command mailbox routine.
 *
 * Returns 0 on success.
 */
अटल पूर्णांक
qla2x00_sns_rnn_id(scsi_qla_host_t *vha)
अणु
	पूर्णांक		rval;
	काष्ठा qla_hw_data *ha = vha->hw;
	काष्ठा sns_cmd_pkt	*sns_cmd;

	/* Issue RNN_ID. */
	/* Prepare SNS command request. */
	sns_cmd = qla2x00_prep_sns_cmd(vha, RNN_ID_CMD, RNN_ID_SNS_SCMD_LEN,
	    RNN_ID_SNS_DATA_SIZE);

	/* Prepare SNS command arguments -- port_id, nodename. */
	sns_cmd->p.cmd.param[0] = vha->d_id.b.al_pa;
	sns_cmd->p.cmd.param[1] = vha->d_id.b.area;
	sns_cmd->p.cmd.param[2] = vha->d_id.b.करोमुख्य;

	sns_cmd->p.cmd.param[4] = vha->node_name[7];
	sns_cmd->p.cmd.param[5] = vha->node_name[6];
	sns_cmd->p.cmd.param[6] = vha->node_name[5];
	sns_cmd->p.cmd.param[7] = vha->node_name[4];
	sns_cmd->p.cmd.param[8] = vha->node_name[3];
	sns_cmd->p.cmd.param[9] = vha->node_name[2];
	sns_cmd->p.cmd.param[10] = vha->node_name[1];
	sns_cmd->p.cmd.param[11] = vha->node_name[0];

	/* Execute SNS command. */
	rval = qla2x00_send_sns(vha, ha->sns_cmd_dma, RNN_ID_SNS_CMD_SIZE / 2,
	    माप(काष्ठा sns_cmd_pkt));
	अगर (rval != QLA_SUCCESS) अणु
		/*EMPTY*/
		ql_dbg(ql_dbg_disc, vha, 0x204a,
		    "RNN_ID Send SNS failed (%d).\n", rval);
	पूर्ण अन्यथा अगर (sns_cmd->p.rnn_data[8] != 0x80 ||
	    sns_cmd->p.rnn_data[9] != 0x02) अणु
		ql_dbg(ql_dbg_disc + ql_dbg_buffer, vha, 0x207b,
		    "RNN_ID failed, rejected request, rnn_rsp:\n");
		ql_dump_buffer(ql_dbg_disc + ql_dbg_buffer, vha, 0x207c,
		    sns_cmd->p.rnn_data, 16);
		rval = QLA_FUNCTION_FAILED;
	पूर्ण अन्यथा अणु
		ql_dbg(ql_dbg_disc, vha, 0x204c,
		    "RNN_ID exiting normally.\n");
	पूर्ण

	वापस (rval);
पूर्ण

/**
 * qla2x00_mgmt_svr_login() - Login to fabric Management Service.
 * @vha: HA context
 *
 * Returns 0 on success.
 */
पूर्णांक
qla2x00_mgmt_svr_login(scsi_qla_host_t *vha)
अणु
	पूर्णांक ret, rval;
	uपूर्णांक16_t mb[MAILBOX_REGISTER_COUNT];
	काष्ठा qla_hw_data *ha = vha->hw;

	ret = QLA_SUCCESS;
	अगर (vha->flags.management_server_logged_in)
		वापस ret;

	rval = ha->isp_ops->fabric_login(vha, vha->mgmt_svr_loop_id, 0xff, 0xff,
	    0xfa, mb, BIT_1);
	अगर (rval != QLA_SUCCESS || mb[0] != MBS_COMMAND_COMPLETE) अणु
		अगर (rval == QLA_MEMORY_ALLOC_FAILED)
			ql_dbg(ql_dbg_disc, vha, 0x2085,
			    "Failed management_server login: loopid=%x "
			    "rval=%d\n", vha->mgmt_svr_loop_id, rval);
		अन्यथा
			ql_dbg(ql_dbg_disc, vha, 0x2024,
			    "Failed management_server login: loopid=%x "
			    "mb[0]=%x mb[1]=%x mb[2]=%x mb[6]=%x mb[7]=%x.\n",
			    vha->mgmt_svr_loop_id, mb[0], mb[1], mb[2], mb[6],
			    mb[7]);
		ret = QLA_FUNCTION_FAILED;
	पूर्ण अन्यथा
		vha->flags.management_server_logged_in = 1;

	वापस ret;
पूर्ण

/**
 * qla2x00_prep_ms_fdmi_iocb() - Prepare common MS IOCB fields क्रम FDMI query.
 * @vha: HA context
 * @req_size: request size in bytes
 * @rsp_size: response size in bytes
 *
 * Returns a poपूर्णांकer to the @ha's ms_iocb.
 */
व्योम *
qla2x00_prep_ms_fdmi_iocb(scsi_qla_host_t *vha, uपूर्णांक32_t req_size,
    uपूर्णांक32_t rsp_size)
अणु
	ms_iocb_entry_t *ms_pkt;
	काष्ठा qla_hw_data *ha = vha->hw;

	ms_pkt = ha->ms_iocb;
	स_रखो(ms_pkt, 0, माप(ms_iocb_entry_t));

	ms_pkt->entry_type = MS_IOCB_TYPE;
	ms_pkt->entry_count = 1;
	SET_TARGET_ID(ha, ms_pkt->loop_id, vha->mgmt_svr_loop_id);
	ms_pkt->control_flags = cpu_to_le16(CF_READ | CF_HEAD_TAG);
	ms_pkt->समयout = cpu_to_le16(ha->r_a_tov / 10 * 2);
	ms_pkt->cmd_dsd_count = cpu_to_le16(1);
	ms_pkt->total_dsd_count = cpu_to_le16(2);
	ms_pkt->rsp_bytecount = cpu_to_le32(rsp_size);
	ms_pkt->req_bytecount = cpu_to_le32(req_size);

	put_unaligned_le64(ha->ct_sns_dma, &ms_pkt->req_dsd.address);
	ms_pkt->req_dsd.length = ms_pkt->req_bytecount;

	put_unaligned_le64(ha->ct_sns_dma, &ms_pkt->rsp_dsd.address);
	ms_pkt->rsp_dsd.length = ms_pkt->rsp_bytecount;

	वापस ms_pkt;
पूर्ण

/**
 * qla24xx_prep_ms_fdmi_iocb() - Prepare common MS IOCB fields क्रम FDMI query.
 * @vha: HA context
 * @req_size: request size in bytes
 * @rsp_size: response size in bytes
 *
 * Returns a poपूर्णांकer to the @ha's ms_iocb.
 */
व्योम *
qla24xx_prep_ms_fdmi_iocb(scsi_qla_host_t *vha, uपूर्णांक32_t req_size,
    uपूर्णांक32_t rsp_size)
अणु
	काष्ठा ct_entry_24xx *ct_pkt;
	काष्ठा qla_hw_data *ha = vha->hw;

	ct_pkt = (काष्ठा ct_entry_24xx *)ha->ms_iocb;
	स_रखो(ct_pkt, 0, माप(काष्ठा ct_entry_24xx));

	ct_pkt->entry_type = CT_IOCB_TYPE;
	ct_pkt->entry_count = 1;
	ct_pkt->nport_handle = cpu_to_le16(vha->mgmt_svr_loop_id);
	ct_pkt->समयout = cpu_to_le16(ha->r_a_tov / 10 * 2);
	ct_pkt->cmd_dsd_count = cpu_to_le16(1);
	ct_pkt->rsp_dsd_count = cpu_to_le16(1);
	ct_pkt->rsp_byte_count = cpu_to_le32(rsp_size);
	ct_pkt->cmd_byte_count = cpu_to_le32(req_size);

	put_unaligned_le64(ha->ct_sns_dma, &ct_pkt->dsd[0].address);
	ct_pkt->dsd[0].length = ct_pkt->cmd_byte_count;

	put_unaligned_le64(ha->ct_sns_dma, &ct_pkt->dsd[1].address);
	ct_pkt->dsd[1].length = ct_pkt->rsp_byte_count;
	ct_pkt->vp_index = vha->vp_idx;

	वापस ct_pkt;
पूर्ण

अटल व्योम
qla2x00_update_ms_fdmi_iocb(scsi_qla_host_t *vha, uपूर्णांक32_t req_size)
अणु
	काष्ठा qla_hw_data *ha = vha->hw;
	ms_iocb_entry_t *ms_pkt = ha->ms_iocb;
	काष्ठा ct_entry_24xx *ct_pkt = (काष्ठा ct_entry_24xx *)ha->ms_iocb;

	अगर (IS_FWI2_CAPABLE(ha)) अणु
		ct_pkt->cmd_byte_count = cpu_to_le32(req_size);
		ct_pkt->dsd[0].length = ct_pkt->cmd_byte_count;
	पूर्ण अन्यथा अणु
		ms_pkt->req_bytecount = cpu_to_le32(req_size);
		ms_pkt->req_dsd.length = ms_pkt->req_bytecount;
	पूर्ण
पूर्ण

/**
 * qla2x00_prep_ct_fdmi_req() - Prepare common CT request fields क्रम SNS query.
 * @p: CT request buffer
 * @cmd: GS command
 * @rsp_size: response size in bytes
 *
 * Returns a poपूर्णांकer to the पूर्णांकitialized @ct_req.
 */
अटल अंतरभूत काष्ठा ct_sns_req *
qla2x00_prep_ct_fdmi_req(काष्ठा ct_sns_pkt *p, uपूर्णांक16_t cmd,
    uपूर्णांक16_t rsp_size)
अणु
	स_रखो(p, 0, माप(काष्ठा ct_sns_pkt));

	p->p.req.header.revision = 0x01;
	p->p.req.header.gs_type = 0xFA;
	p->p.req.header.gs_subtype = 0x10;
	p->p.req.command = cpu_to_be16(cmd);
	p->p.req.max_rsp_size = cpu_to_be16((rsp_size - 16) / 4);

	वापस &p->p.req;
पूर्ण

uपूर्णांक
qla25xx_fdmi_port_speed_capability(काष्ठा qla_hw_data *ha)
अणु
	uपूर्णांक speeds = 0;

	अगर (IS_CNA_CAPABLE(ha))
		वापस FDMI_PORT_SPEED_10GB;
	अगर (IS_QLA28XX(ha) || IS_QLA27XX(ha)) अणु
		अगर (ha->max_supported_speed == 2) अणु
			अगर (ha->min_supported_speed <= 6)
				speeds |= FDMI_PORT_SPEED_64GB;
		पूर्ण
		अगर (ha->max_supported_speed == 2 ||
		    ha->max_supported_speed == 1) अणु
			अगर (ha->min_supported_speed <= 5)
				speeds |= FDMI_PORT_SPEED_32GB;
		पूर्ण
		अगर (ha->max_supported_speed == 2 ||
		    ha->max_supported_speed == 1 ||
		    ha->max_supported_speed == 0) अणु
			अगर (ha->min_supported_speed <= 4)
				speeds |= FDMI_PORT_SPEED_16GB;
		पूर्ण
		अगर (ha->max_supported_speed == 1 ||
		    ha->max_supported_speed == 0) अणु
			अगर (ha->min_supported_speed <= 3)
				speeds |= FDMI_PORT_SPEED_8GB;
		पूर्ण
		अगर (ha->max_supported_speed == 0) अणु
			अगर (ha->min_supported_speed <= 2)
				speeds |= FDMI_PORT_SPEED_4GB;
		पूर्ण
		वापस speeds;
	पूर्ण
	अगर (IS_QLA2031(ha)) अणु
		अगर ((ha->pdev->subप्रणाली_venकरोr == 0x103C) &&
		    (ha->pdev->subप्रणाली_device == 0x8002)) अणु
			speeds = FDMI_PORT_SPEED_16GB;
		पूर्ण अन्यथा अणु
			speeds = FDMI_PORT_SPEED_16GB|FDMI_PORT_SPEED_8GB|
				FDMI_PORT_SPEED_4GB;
		पूर्ण
		वापस speeds;
	पूर्ण
	अगर (IS_QLA25XX(ha) || IS_QLAFX00(ha))
		वापस FDMI_PORT_SPEED_8GB|FDMI_PORT_SPEED_4GB|
			FDMI_PORT_SPEED_2GB|FDMI_PORT_SPEED_1GB;
	अगर (IS_QLA24XX_TYPE(ha))
		वापस FDMI_PORT_SPEED_4GB|FDMI_PORT_SPEED_2GB|
			FDMI_PORT_SPEED_1GB;
	अगर (IS_QLA23XX(ha))
		वापस FDMI_PORT_SPEED_2GB|FDMI_PORT_SPEED_1GB;
	वापस FDMI_PORT_SPEED_1GB;
पूर्ण

uपूर्णांक
qla25xx_fdmi_port_speed_currently(काष्ठा qla_hw_data *ha)
अणु
	चयन (ha->link_data_rate) अणु
	हाल PORT_SPEED_1GB:
		वापस FDMI_PORT_SPEED_1GB;
	हाल PORT_SPEED_2GB:
		वापस FDMI_PORT_SPEED_2GB;
	हाल PORT_SPEED_4GB:
		वापस FDMI_PORT_SPEED_4GB;
	हाल PORT_SPEED_8GB:
		वापस FDMI_PORT_SPEED_8GB;
	हाल PORT_SPEED_10GB:
		वापस FDMI_PORT_SPEED_10GB;
	हाल PORT_SPEED_16GB:
		वापस FDMI_PORT_SPEED_16GB;
	हाल PORT_SPEED_32GB:
		वापस FDMI_PORT_SPEED_32GB;
	हाल PORT_SPEED_64GB:
		वापस FDMI_PORT_SPEED_64GB;
	शेष:
		वापस FDMI_PORT_SPEED_UNKNOWN;
	पूर्ण
पूर्ण

/**
 * qla2x00_hba_attributes() - perक्रमm HBA attributes registration
 * @vha: HA context
 * @entries: number of entries to use
 * @callopt: Option to issue extended or standard FDMI
 *           command parameter
 *
 * Returns 0 on success.
 */
अटल अचिन्हित दीर्घ
qla2x00_hba_attributes(scsi_qla_host_t *vha, व्योम *entries,
	अचिन्हित पूर्णांक callopt)
अणु
	काष्ठा qla_hw_data *ha = vha->hw;
	काष्ठा init_cb_24xx *icb24 = (व्योम *)ha->init_cb;
	काष्ठा new_utsname *p_sysid = utsname();
	काष्ठा ct_fdmi_hba_attr *eiter;
	uपूर्णांक16_t alen;
	अचिन्हित दीर्घ size = 0;

	/* Nodename. */
	eiter = entries + size;
	eiter->type = cpu_to_be16(FDMI_HBA_NODE_NAME);
	स_नकल(eiter->a.node_name, vha->node_name, माप(eiter->a.node_name));
	alen = माप(eiter->a.node_name);
	alen += FDMI_ATTR_TYPELEN(eiter);
	eiter->len = cpu_to_be16(alen);
	size += alen;
	ql_dbg(ql_dbg_disc, vha, 0x20a0,
	    "NODENAME = %016llx.\n", wwn_to_u64(eiter->a.node_name));
	/* Manufacturer. */
	eiter = entries + size;
	eiter->type = cpu_to_be16(FDMI_HBA_MANUFACTURER);
	alen = scnम_लिखो(
		eiter->a.manufacturer, माप(eiter->a.manufacturer),
		"%s", "QLogic Corporation");
	alen += FDMI_ATTR_ALIGNMENT(alen);
	alen += FDMI_ATTR_TYPELEN(eiter);
	eiter->len = cpu_to_be16(alen);
	size += alen;
	ql_dbg(ql_dbg_disc, vha, 0x20a1,
	    "MANUFACTURER = %s.\n", eiter->a.manufacturer);
	/* Serial number. */
	eiter = entries + size;
	eiter->type = cpu_to_be16(FDMI_HBA_SERIAL_NUMBER);
	alen = 0;
	अगर (IS_FWI2_CAPABLE(ha)) अणु
		alen = qla2xxx_get_vpd_field(vha, "SN",
		    eiter->a.serial_num, माप(eiter->a.serial_num));
	पूर्ण
	अगर (!alen) अणु
		uपूर्णांक32_t sn = ((ha->serial0 & 0x1f) << 16) |
			(ha->serial2 << 8) | ha->serial1;
		alen = scnम_लिखो(
			eiter->a.serial_num, माप(eiter->a.serial_num),
			"%c%05d", 'A' + sn / 100000, sn % 100000);
	पूर्ण
	alen += FDMI_ATTR_ALIGNMENT(alen);
	alen += FDMI_ATTR_TYPELEN(eiter);
	eiter->len = cpu_to_be16(alen);
	size += alen;
	ql_dbg(ql_dbg_disc, vha, 0x20a2,
	    "SERIAL NUMBER = %s.\n", eiter->a.serial_num);
	/* Model name. */
	eiter = entries + size;
	eiter->type = cpu_to_be16(FDMI_HBA_MODEL);
	alen = scnम_लिखो(
		eiter->a.model, माप(eiter->a.model),
		"%s", ha->model_number);
	alen += FDMI_ATTR_ALIGNMENT(alen);
	alen += FDMI_ATTR_TYPELEN(eiter);
	eiter->len = cpu_to_be16(alen);
	size += alen;
	ql_dbg(ql_dbg_disc, vha, 0x20a3,
	    "MODEL NAME = %s.\n", eiter->a.model);
	/* Model description. */
	eiter = entries + size;
	eiter->type = cpu_to_be16(FDMI_HBA_MODEL_DESCRIPTION);
	alen = scnम_लिखो(
		eiter->a.model_desc, माप(eiter->a.model_desc),
		"%s", ha->model_desc);
	alen += FDMI_ATTR_ALIGNMENT(alen);
	alen += FDMI_ATTR_TYPELEN(eiter);
	eiter->len = cpu_to_be16(alen);
	size += alen;
	ql_dbg(ql_dbg_disc, vha, 0x20a4,
	    "MODEL DESCRIPTION = %s.\n", eiter->a.model_desc);
	/* Hardware version. */
	eiter = entries + size;
	eiter->type = cpu_to_be16(FDMI_HBA_HARDWARE_VERSION);
	alen = 0;
	अगर (IS_FWI2_CAPABLE(ha)) अणु
		अगर (!alen) अणु
			alen = qla2xxx_get_vpd_field(vha, "MN",
			    eiter->a.hw_version, माप(eiter->a.hw_version));
		पूर्ण
		अगर (!alen) अणु
			alen = qla2xxx_get_vpd_field(vha, "EC",
			    eiter->a.hw_version, माप(eiter->a.hw_version));
		पूर्ण
	पूर्ण
	अगर (!alen) अणु
		alen = scnम_लिखो(
			eiter->a.hw_version, माप(eiter->a.hw_version),
			"HW:%s", ha->adapter_id);
	पूर्ण
	alen += FDMI_ATTR_ALIGNMENT(alen);
	alen += FDMI_ATTR_TYPELEN(eiter);
	eiter->len = cpu_to_be16(alen);
	size += alen;
	ql_dbg(ql_dbg_disc, vha, 0x20a5,
	    "HARDWARE VERSION = %s.\n", eiter->a.hw_version);
	/* Driver version. */
	eiter = entries + size;
	eiter->type = cpu_to_be16(FDMI_HBA_DRIVER_VERSION);
	alen = scnम_लिखो(
		eiter->a.driver_version, माप(eiter->a.driver_version),
		"%s", qla2x00_version_str);
	alen += FDMI_ATTR_ALIGNMENT(alen);
	alen += FDMI_ATTR_TYPELEN(eiter);
	eiter->len = cpu_to_be16(alen);
	size += alen;
	ql_dbg(ql_dbg_disc, vha, 0x20a6,
	    "DRIVER VERSION = %s.\n", eiter->a.driver_version);
	/* Option ROM version. */
	eiter = entries + size;
	eiter->type = cpu_to_be16(FDMI_HBA_OPTION_ROM_VERSION);
	alen = scnम_लिखो(
		eiter->a.orom_version, माप(eiter->a.orom_version),
		"%d.%02d", ha->bios_revision[1], ha->bios_revision[0]);
	alen += FDMI_ATTR_ALIGNMENT(alen);
	alen += FDMI_ATTR_TYPELEN(eiter);
	eiter->len = cpu_to_be16(alen);
	size += alen;

	ql_dbg(ql_dbg_disc, vha, 0x20a7,
	    "OPTROM VERSION = %d.%02d.\n",
	    eiter->a.orom_version[1], eiter->a.orom_version[0]);
	/* Firmware version */
	eiter = entries + size;
	eiter->type = cpu_to_be16(FDMI_HBA_FIRMWARE_VERSION);
	ha->isp_ops->fw_version_str(vha, eiter->a.fw_version,
	    माप(eiter->a.fw_version));
	alen += FDMI_ATTR_ALIGNMENT(alen);
	alen += FDMI_ATTR_TYPELEN(eiter);
	eiter->len = cpu_to_be16(alen);
	size += alen;
	ql_dbg(ql_dbg_disc, vha, 0x20a8,
	    "FIRMWARE VERSION = %s.\n", eiter->a.fw_version);
	अगर (callopt == CALLOPT_FDMI1)
		जाओ करोne;
	/* OS Name and Version */
	eiter = entries + size;
	eiter->type = cpu_to_be16(FDMI_HBA_OS_NAME_AND_VERSION);
	alen = 0;
	अगर (p_sysid) अणु
		alen = scnम_लिखो(
			eiter->a.os_version, माप(eiter->a.os_version),
			"%s %s %s",
			p_sysid->sysname, p_sysid->release, p_sysid->machine);
	पूर्ण
	अगर (!alen) अणु
		alen = scnम_लिखो(
			eiter->a.os_version, माप(eiter->a.os_version),
			"%s %s",
			"Linux", fc_host_प्रणाली_hostname(vha->host));
	पूर्ण
	alen += FDMI_ATTR_ALIGNMENT(alen);
	alen += FDMI_ATTR_TYPELEN(eiter);
	eiter->len = cpu_to_be16(alen);
	size += alen;
	ql_dbg(ql_dbg_disc, vha, 0x20a9,
	    "OS VERSION = %s.\n", eiter->a.os_version);
	/* MAX CT Payload Length */
	eiter = entries + size;
	eiter->type = cpu_to_be16(FDMI_HBA_MAXIMUM_CT_PAYLOAD_LENGTH);
	eiter->a.max_ct_len = cpu_to_be32(le16_to_cpu(IS_FWI2_CAPABLE(ha) ?
		icb24->frame_payload_size : ha->init_cb->frame_payload_size));
	alen = माप(eiter->a.max_ct_len);
	alen += FDMI_ATTR_TYPELEN(eiter);
	eiter->len = cpu_to_be16(alen);
	size += alen;
	ql_dbg(ql_dbg_disc, vha, 0x20aa,
	    "CT PAYLOAD LENGTH = 0x%x.\n", be32_to_cpu(eiter->a.max_ct_len));
	/* Node Sybolic Name */
	eiter = entries + size;
	eiter->type = cpu_to_be16(FDMI_HBA_NODE_SYMBOLIC_NAME);
	alen = qla2x00_get_sym_node_name(vha, eiter->a.sym_name,
	    माप(eiter->a.sym_name));
	alen += FDMI_ATTR_ALIGNMENT(alen);
	alen += FDMI_ATTR_TYPELEN(eiter);
	eiter->len = cpu_to_be16(alen);
	size += alen;
	ql_dbg(ql_dbg_disc, vha, 0x20ab,
	    "SYMBOLIC NAME = %s.\n", eiter->a.sym_name);
	/* Venकरोr Specअगरic inक्रमmation */
	eiter = entries + size;
	eiter->type = cpu_to_be16(FDMI_HBA_VENDOR_SPECIFIC_INFO);
	eiter->a.venकरोr_specअगरic_info = cpu_to_be32(PCI_VENDOR_ID_QLOGIC);
	alen = माप(eiter->a.venकरोr_specअगरic_info);
	alen += FDMI_ATTR_TYPELEN(eiter);
	eiter->len = cpu_to_be16(alen);
	size += alen;
	ql_dbg(ql_dbg_disc, vha, 0x20ac,
	    "VENDOR SPECIFIC INFO = 0x%x.\n",
	    be32_to_cpu(eiter->a.venकरोr_specअगरic_info));
	/* Num Ports */
	eiter = entries + size;
	eiter->type = cpu_to_be16(FDMI_HBA_NUM_PORTS);
	eiter->a.num_ports = cpu_to_be32(1);
	alen = माप(eiter->a.num_ports);
	alen += FDMI_ATTR_TYPELEN(eiter);
	eiter->len = cpu_to_be16(alen);
	size += alen;
	ql_dbg(ql_dbg_disc, vha, 0x20ad,
	    "PORT COUNT = %x.\n", be32_to_cpu(eiter->a.num_ports));
	/* Fabric Name */
	eiter = entries + size;
	eiter->type = cpu_to_be16(FDMI_HBA_FABRIC_NAME);
	स_नकल(eiter->a.fabric_name, vha->fabric_node_name,
	    माप(eiter->a.fabric_name));
	alen = माप(eiter->a.fabric_name);
	alen += FDMI_ATTR_TYPELEN(eiter);
	eiter->len = cpu_to_be16(alen);
	size += alen;
	ql_dbg(ql_dbg_disc, vha, 0x20ae,
	    "FABRIC NAME = %016llx.\n", wwn_to_u64(eiter->a.fabric_name));
	/* BIOS Version */
	eiter = entries + size;
	eiter->type = cpu_to_be16(FDMI_HBA_BOOT_BIOS_NAME);
	alen = scnम_लिखो(
		eiter->a.bios_name, माप(eiter->a.bios_name),
		"BIOS %d.%02d", ha->bios_revision[1], ha->bios_revision[0]);
	alen += FDMI_ATTR_ALIGNMENT(alen);
	alen += FDMI_ATTR_TYPELEN(eiter);
	eiter->len = cpu_to_be16(alen);
	size += alen;
	ql_dbg(ql_dbg_disc, vha, 0x20af,
	    "BIOS NAME = %s\n", eiter->a.bios_name);
	/* Venकरोr Identअगरier */
	eiter = entries + size;
	eiter->type = cpu_to_be16(FDMI_HBA_VENDOR_IDENTIFIER);
	alen = scnम_लिखो(
		eiter->a.venकरोr_identअगरier, माप(eiter->a.venकरोr_identअगरier),
		"%s", "QLGC");
	alen += FDMI_ATTR_ALIGNMENT(alen);
	alen += FDMI_ATTR_TYPELEN(eiter);
	eiter->len = cpu_to_be16(alen);
	size += alen;
	ql_dbg(ql_dbg_disc, vha, 0x20b0,
	    "VENDOR IDENTIFIER = %s.\n", eiter->a.venकरोr_identअगरier);
करोne:
	वापस size;
पूर्ण

/**
 * qla2x00_port_attributes() - perक्रमm Port attributes registration
 * @vha: HA context
 * @entries: number of entries to use
 * @callopt: Option to issue extended or standard FDMI
 *           command parameter
 *
 * Returns 0 on success.
 */
अटल अचिन्हित दीर्घ
qla2x00_port_attributes(scsi_qla_host_t *vha, व्योम *entries,
	अचिन्हित पूर्णांक callopt)
अणु
	काष्ठा qla_hw_data *ha = vha->hw;
	काष्ठा init_cb_24xx *icb24 = (व्योम *)ha->init_cb;
	काष्ठा new_utsname *p_sysid = utsname();
	अक्षर *hostname = p_sysid ?
		p_sysid->nodename : fc_host_प्रणाली_hostname(vha->host);
	काष्ठा ct_fdmi_port_attr *eiter;
	uपूर्णांक16_t alen;
	अचिन्हित दीर्घ size = 0;

	/* FC4 types. */
	eiter = entries + size;
	eiter->type = cpu_to_be16(FDMI_PORT_FC4_TYPES);
	eiter->a.fc4_types[0] = 0x00;
	eiter->a.fc4_types[1] = 0x00;
	eiter->a.fc4_types[2] = 0x01;
	eiter->a.fc4_types[3] = 0x00;
	alen = माप(eiter->a.fc4_types);
	alen += FDMI_ATTR_TYPELEN(eiter);
	eiter->len = cpu_to_be16(alen);
	size += alen;
	ql_dbg(ql_dbg_disc, vha, 0x20c0,
	    "FC4 TYPES = %016llx.\n", *(uपूर्णांक64_t *)eiter->a.fc4_types);
	अगर (vha->flags.nvme_enabled) अणु
		eiter->a.fc4_types[6] = 1;      /* NVMe type 28h */
		ql_dbg(ql_dbg_disc, vha, 0x211f,
		    "NVME FC4 Type = %02x 0x0 0x0 0x0 0x0 0x0.\n",
		    eiter->a.fc4_types[6]);
	पूर्ण
	/* Supported speed. */
	eiter = entries + size;
	eiter->type = cpu_to_be16(FDMI_PORT_SUPPORT_SPEED);
	eiter->a.sup_speed = cpu_to_be32(
		qla25xx_fdmi_port_speed_capability(ha));
	alen = माप(eiter->a.sup_speed);
	alen += FDMI_ATTR_TYPELEN(eiter);
	eiter->len = cpu_to_be16(alen);
	size += alen;
	ql_dbg(ql_dbg_disc, vha, 0x20c1,
	    "SUPPORTED SPEED = %x.\n", be32_to_cpu(eiter->a.sup_speed));
	/* Current speed. */
	eiter = entries + size;
	eiter->type = cpu_to_be16(FDMI_PORT_CURRENT_SPEED);
	eiter->a.cur_speed = cpu_to_be32(
		qla25xx_fdmi_port_speed_currently(ha));
	alen = माप(eiter->a.cur_speed);
	alen += FDMI_ATTR_TYPELEN(eiter);
	eiter->len = cpu_to_be16(alen);
	size += alen;
	ql_dbg(ql_dbg_disc, vha, 0x20c2,
	    "CURRENT SPEED = %x.\n", be32_to_cpu(eiter->a.cur_speed));
	/* Max frame size. */
	eiter = entries + size;
	eiter->type = cpu_to_be16(FDMI_PORT_MAX_FRAME_SIZE);
	eiter->a.max_frame_size = cpu_to_be32(le16_to_cpu(IS_FWI2_CAPABLE(ha) ?
		icb24->frame_payload_size : ha->init_cb->frame_payload_size));
	alen = माप(eiter->a.max_frame_size);
	alen += FDMI_ATTR_TYPELEN(eiter);
	eiter->len = cpu_to_be16(alen);
	size += alen;
	ql_dbg(ql_dbg_disc, vha, 0x20c3,
	    "MAX FRAME SIZE = %x.\n", be32_to_cpu(eiter->a.max_frame_size));
	/* OS device name. */
	eiter = entries + size;
	eiter->type = cpu_to_be16(FDMI_PORT_OS_DEVICE_NAME);
	alen = scnम_लिखो(
		eiter->a.os_dev_name, माप(eiter->a.os_dev_name),
		"%s:host%lu", QLA2XXX_DRIVER_NAME, vha->host_no);
	alen += FDMI_ATTR_ALIGNMENT(alen);
	alen += FDMI_ATTR_TYPELEN(eiter);
	eiter->len = cpu_to_be16(alen);
	size += alen;
	ql_dbg(ql_dbg_disc, vha, 0x20c4,
	    "OS DEVICE NAME = %s.\n", eiter->a.os_dev_name);
	/* Hostname. */
	eiter = entries + size;
	eiter->type = cpu_to_be16(FDMI_PORT_HOST_NAME);
	अगर (!*hostname || !म_भेदन(hostname, "(none)", 6))
		hostname = "Linux-default";
	alen = scnम_लिखो(
		eiter->a.host_name, माप(eiter->a.host_name),
		"%s", hostname);
	alen += FDMI_ATTR_ALIGNMENT(alen);
	alen += FDMI_ATTR_TYPELEN(eiter);
	eiter->len = cpu_to_be16(alen);
	size += alen;
	ql_dbg(ql_dbg_disc, vha, 0x20c5,
	    "HOSTNAME = %s.\n", eiter->a.host_name);

	अगर (callopt == CALLOPT_FDMI1)
		जाओ करोne;

	/* Node Name */
	eiter = entries + size;
	eiter->type = cpu_to_be16(FDMI_PORT_NODE_NAME);
	स_नकल(eiter->a.node_name, vha->node_name, माप(eiter->a.node_name));
	alen = माप(eiter->a.node_name);
	alen += FDMI_ATTR_TYPELEN(eiter);
	eiter->len = cpu_to_be16(alen);
	size += alen;
	ql_dbg(ql_dbg_disc, vha, 0x20c6,
	    "NODENAME = %016llx.\n", wwn_to_u64(eiter->a.node_name));

	/* Port Name */
	eiter = entries + size;
	eiter->type = cpu_to_be16(FDMI_PORT_NAME);
	स_नकल(eiter->a.port_name, vha->port_name, माप(eiter->a.port_name));
	alen = माप(eiter->a.port_name);
	alen += FDMI_ATTR_TYPELEN(eiter);
	eiter->len = cpu_to_be16(alen);
	size += alen;
	ql_dbg(ql_dbg_disc, vha, 0x20c7,
	    "PORTNAME = %016llx.\n", wwn_to_u64(eiter->a.port_name));

	/* Port Symbolic Name */
	eiter = entries + size;
	eiter->type = cpu_to_be16(FDMI_PORT_SYM_NAME);
	alen = qla2x00_get_sym_node_name(vha, eiter->a.port_sym_name,
	    माप(eiter->a.port_sym_name));
	alen += FDMI_ATTR_ALIGNMENT(alen);
	alen += FDMI_ATTR_TYPELEN(eiter);
	eiter->len = cpu_to_be16(alen);
	size += alen;
	ql_dbg(ql_dbg_disc, vha, 0x20c8,
	    "PORT SYMBOLIC NAME = %s\n", eiter->a.port_sym_name);

	/* Port Type */
	eiter = entries + size;
	eiter->type = cpu_to_be16(FDMI_PORT_TYPE);
	eiter->a.port_type = cpu_to_be32(NS_NX_PORT_TYPE);
	alen = माप(eiter->a.port_type);
	alen += FDMI_ATTR_TYPELEN(eiter);
	eiter->len = cpu_to_be16(alen);
	size += alen;
	ql_dbg(ql_dbg_disc, vha, 0x20c9,
	    "PORT TYPE = %x.\n", be32_to_cpu(eiter->a.port_type));

	/* Supported Class of Service */
	eiter = entries + size;
	eiter->type = cpu_to_be16(FDMI_PORT_SUPP_COS);
	eiter->a.port_supported_cos = cpu_to_be32(FC_CLASS_3);
	alen = माप(eiter->a.port_supported_cos);
	alen += FDMI_ATTR_TYPELEN(eiter);
	eiter->len = cpu_to_be16(alen);
	size += alen;
	ql_dbg(ql_dbg_disc, vha, 0x20ca,
	    "SUPPORTED COS = %08x\n", be32_to_cpu(eiter->a.port_supported_cos));

	/* Port Fabric Name */
	eiter = entries + size;
	eiter->type = cpu_to_be16(FDMI_PORT_FABRIC_NAME);
	स_नकल(eiter->a.fabric_name, vha->fabric_node_name,
	    माप(eiter->a.fabric_name));
	alen = माप(eiter->a.fabric_name);
	alen += FDMI_ATTR_TYPELEN(eiter);
	eiter->len = cpu_to_be16(alen);
	size += alen;
	ql_dbg(ql_dbg_disc, vha, 0x20cb,
	    "FABRIC NAME = %016llx.\n", wwn_to_u64(eiter->a.fabric_name));

	/* FC4_type */
	eiter = entries + size;
	eiter->type = cpu_to_be16(FDMI_PORT_FC4_TYPE);
	eiter->a.port_fc4_type[0] = 0x00;
	eiter->a.port_fc4_type[1] = 0x00;
	eiter->a.port_fc4_type[2] = 0x01;
	eiter->a.port_fc4_type[3] = 0x00;
	alen = माप(eiter->a.port_fc4_type);
	alen += FDMI_ATTR_TYPELEN(eiter);
	eiter->len = cpu_to_be16(alen);
	size += alen;
	ql_dbg(ql_dbg_disc, vha, 0x20cc,
	    "PORT ACTIVE FC4 TYPE = %016llx.\n",
	    *(uपूर्णांक64_t *)eiter->a.port_fc4_type);

	/* Port State */
	eiter = entries + size;
	eiter->type = cpu_to_be16(FDMI_PORT_STATE);
	eiter->a.port_state = cpu_to_be32(2);
	alen = माप(eiter->a.port_state);
	alen += FDMI_ATTR_TYPELEN(eiter);
	eiter->len = cpu_to_be16(alen);
	size += alen;
	ql_dbg(ql_dbg_disc, vha, 0x20cd,
	    "PORT_STATE = %x.\n", be32_to_cpu(eiter->a.port_state));

	/* Number of Ports */
	eiter = entries + size;
	eiter->type = cpu_to_be16(FDMI_PORT_COUNT);
	eiter->a.num_ports = cpu_to_be32(1);
	alen = माप(eiter->a.num_ports);
	alen += FDMI_ATTR_TYPELEN(eiter);
	eiter->len = cpu_to_be16(alen);
	size += alen;
	ql_dbg(ql_dbg_disc, vha, 0x20ce,
	    "PORT COUNT = %x.\n", be32_to_cpu(eiter->a.num_ports));

	/* Port Identअगरier */
	eiter = entries + size;
	eiter->type = cpu_to_be16(FDMI_PORT_IDENTIFIER);
	eiter->a.port_id = cpu_to_be32(vha->d_id.b24);
	alen = माप(eiter->a.port_id);
	alen += FDMI_ATTR_TYPELEN(eiter);
	eiter->len = cpu_to_be16(alen);
	size += alen;
	ql_dbg(ql_dbg_disc, vha, 0x20cf,
	    "PORT ID = %x.\n", be32_to_cpu(eiter->a.port_id));

	अगर (callopt == CALLOPT_FDMI2 || !ql2xsmartsan)
		जाओ करोne;

	/* Smart SAN Service Category (Populate Smart SAN Initiator)*/
	eiter = entries + size;
	eiter->type = cpu_to_be16(FDMI_SMARTSAN_SERVICE);
	alen = scnम_लिखो(
		eiter->a.smartsan_service, माप(eiter->a.smartsan_service),
		"%s", "Smart SAN Initiator");
	alen += FDMI_ATTR_ALIGNMENT(alen);
	alen += FDMI_ATTR_TYPELEN(eiter);
	eiter->len = cpu_to_be16(alen);
	size += alen;
	ql_dbg(ql_dbg_disc, vha, 0x20d0,
	    "SMARTSAN SERVICE CATEGORY = %s.\n", eiter->a.smartsan_service);

	/* Smart SAN GUID (NWWN+PWWN) */
	eiter = entries + size;
	eiter->type = cpu_to_be16(FDMI_SMARTSAN_GUID);
	स_नकल(eiter->a.smartsan_guid, vha->node_name, WWN_SIZE);
	स_नकल(eiter->a.smartsan_guid + WWN_SIZE, vha->port_name, WWN_SIZE);
	alen = माप(eiter->a.smartsan_guid);
	alen += FDMI_ATTR_TYPELEN(eiter);
	eiter->len = cpu_to_be16(alen);
	size += alen;
	ql_dbg(ql_dbg_disc, vha, 0x20d1,
	    "Smart SAN GUID = %016llx-%016llx\n",
	    wwn_to_u64(eiter->a.smartsan_guid),
	    wwn_to_u64(eiter->a.smartsan_guid + WWN_SIZE));

	/* Smart SAN Version (populate "Smart SAN Version 1.0") */
	eiter = entries + size;
	eiter->type = cpu_to_be16(FDMI_SMARTSAN_VERSION);
	alen = scnम_लिखो(
		eiter->a.smartsan_version, माप(eiter->a.smartsan_version),
		"%s", "Smart SAN Version 2.0");
	alen += FDMI_ATTR_ALIGNMENT(alen);
	alen += FDMI_ATTR_TYPELEN(eiter);
	eiter->len = cpu_to_be16(alen);
	size += alen;
	ql_dbg(ql_dbg_disc, vha, 0x20d2,
	    "SMARTSAN VERSION = %s\n", eiter->a.smartsan_version);

	/* Smart SAN Product Name (Specअगरy Adapter Model No) */
	eiter = entries + size;
	eiter->type = cpu_to_be16(FDMI_SMARTSAN_PROD_NAME);
	alen = scnम_लिखो(eiter->a.smartsan_prod_name,
		माप(eiter->a.smartsan_prod_name),
		"ISP%04x", ha->pdev->device);
	alen += FDMI_ATTR_ALIGNMENT(alen);
	alen += FDMI_ATTR_TYPELEN(eiter);
	eiter->len = cpu_to_be16(alen);
	size += alen;
	ql_dbg(ql_dbg_disc, vha, 0x20d3,
	    "SMARTSAN PRODUCT NAME = %s\n", eiter->a.smartsan_prod_name);

	/* Smart SAN Port Info (specअगरy: 1=Physical, 2=NPIV, 3=SRIOV) */
	eiter = entries + size;
	eiter->type = cpu_to_be16(FDMI_SMARTSAN_PORT_INFO);
	eiter->a.smartsan_port_info = cpu_to_be32(vha->vp_idx ? 2 : 1);
	alen = माप(eiter->a.smartsan_port_info);
	alen += FDMI_ATTR_TYPELEN(eiter);
	eiter->len = cpu_to_be16(alen);
	size += alen;
	ql_dbg(ql_dbg_disc, vha, 0x20d4,
	    "SMARTSAN PORT INFO = %x\n", eiter->a.smartsan_port_info);

	/* Smart SAN Security Support */
	eiter = entries + size;
	eiter->type = cpu_to_be16(FDMI_SMARTSAN_SECURITY_SUPPORT);
	eiter->a.smartsan_security_support = cpu_to_be32(1);
	alen = माप(eiter->a.smartsan_security_support);
	alen += FDMI_ATTR_TYPELEN(eiter);
	eiter->len = cpu_to_be16(alen);
	size += alen;
	ql_dbg(ql_dbg_disc, vha, 0x20d6,
	    "SMARTSAN SECURITY SUPPORT = %d\n",
	    be32_to_cpu(eiter->a.smartsan_security_support));

करोne:
	वापस size;
पूर्ण

/**
 * qla2x00_fdmi_rhba() - perक्रमm RHBA FDMI registration
 * @vha: HA context
 * @callopt: Option to issue FDMI registration
 *
 * Returns 0 on success.
 */
अटल पूर्णांक
qla2x00_fdmi_rhba(scsi_qla_host_t *vha, अचिन्हित पूर्णांक callopt)
अणु
	काष्ठा qla_hw_data *ha = vha->hw;
	अचिन्हित दीर्घ size = 0;
	अचिन्हित पूर्णांक rval, count;
	ms_iocb_entry_t *ms_pkt;
	काष्ठा ct_sns_req *ct_req;
	काष्ठा ct_sns_rsp *ct_rsp;
	व्योम *entries;

	count = callopt != CALLOPT_FDMI1 ?
	    FDMI2_HBA_ATTR_COUNT : FDMI1_HBA_ATTR_COUNT;

	size = RHBA_RSP_SIZE;

	ql_dbg(ql_dbg_disc, vha, 0x20e0,
	    "RHBA (callopt=%x count=%u size=%lu).\n", callopt, count, size);

	/*   Request size adjusted after CT preparation */
	ms_pkt = ha->isp_ops->prep_ms_fdmi_iocb(vha, 0, size);

	/* Prepare CT request */
	ct_req = qla2x00_prep_ct_fdmi_req(ha->ct_sns, RHBA_CMD, size);
	ct_rsp = &ha->ct_sns->p.rsp;

	/* Prepare FDMI command entries */
	स_नकल(ct_req->req.rhba.hba_identअगरier, vha->port_name,
	    माप(ct_req->req.rhba.hba_identअगरier));
	size += माप(ct_req->req.rhba.hba_identअगरier);

	ct_req->req.rhba.entry_count = cpu_to_be32(1);
	size += माप(ct_req->req.rhba.entry_count);

	स_नकल(ct_req->req.rhba.port_name, vha->port_name,
	    माप(ct_req->req.rhba.port_name));
	size += माप(ct_req->req.rhba.port_name);

	/* Attribute count */
	ct_req->req.rhba.attrs.count = cpu_to_be32(count);
	size += माप(ct_req->req.rhba.attrs.count);

	/* Attribute block */
	entries = &ct_req->req.rhba.attrs.entry;

	size += qla2x00_hba_attributes(vha, entries, callopt);

	/* Update MS request size. */
	qla2x00_update_ms_fdmi_iocb(vha, size + 16);

	ql_dbg(ql_dbg_disc, vha, 0x20e1,
	    "RHBA %016llx %016llx.\n",
	    wwn_to_u64(ct_req->req.rhba.hba_identअगरier),
	    wwn_to_u64(ct_req->req.rhba.port_name));

	ql_dump_buffer(ql_dbg_disc + ql_dbg_buffer, vha, 0x20e2,
	    entries, size);

	/* Execute MS IOCB */
	rval = qla2x00_issue_iocb(vha, ha->ms_iocb, ha->ms_iocb_dma,
	    माप(*ha->ms_iocb));
	अगर (rval) अणु
		ql_dbg(ql_dbg_disc, vha, 0x20e3,
		    "RHBA iocb failed (%d).\n", rval);
		वापस rval;
	पूर्ण

	rval = qla2x00_chk_ms_status(vha, ms_pkt, ct_rsp, "RHBA");
	अगर (rval) अणु
		अगर (ct_rsp->header.reason_code == CT_REASON_CANNOT_PERFORM &&
		    ct_rsp->header.explanation_code ==
		    CT_EXPL_ALREADY_REGISTERED) अणु
			ql_dbg(ql_dbg_disc, vha, 0x20e4,
			    "RHBA already registered.\n");
			वापस QLA_ALREADY_REGISTERED;
		पूर्ण

		ql_dbg(ql_dbg_disc, vha, 0x20e5,
		    "RHBA failed, CT Reason %#x, CT Explanation %#x\n",
		    ct_rsp->header.reason_code,
		    ct_rsp->header.explanation_code);
		वापस rval;
	पूर्ण

	ql_dbg(ql_dbg_disc, vha, 0x20e6, "RHBA exiting normally.\n");
	वापस rval;
पूर्ण


अटल पूर्णांक
qla2x00_fdmi_dhba(scsi_qla_host_t *vha)
अणु
	पूर्णांक rval;
	काष्ठा qla_hw_data *ha = vha->hw;
	ms_iocb_entry_t *ms_pkt;
	काष्ठा ct_sns_req *ct_req;
	काष्ठा ct_sns_rsp *ct_rsp;
	/* Issue RPA */
	/* Prepare common MS IOCB */
	ms_pkt = ha->isp_ops->prep_ms_fdmi_iocb(vha, DHBA_REQ_SIZE,
	    DHBA_RSP_SIZE);
	/* Prepare CT request */
	ct_req = qla2x00_prep_ct_fdmi_req(ha->ct_sns, DHBA_CMD, DHBA_RSP_SIZE);
	ct_rsp = &ha->ct_sns->p.rsp;
	/* Prepare FDMI command arguments -- portname. */
	स_नकल(ct_req->req.dhba.port_name, vha->port_name, WWN_SIZE);
	ql_dbg(ql_dbg_disc, vha, 0x2036,
	    "DHBA portname = %8phN.\n", ct_req->req.dhba.port_name);
	/* Execute MS IOCB */
	rval = qla2x00_issue_iocb(vha, ha->ms_iocb, ha->ms_iocb_dma,
	    माप(ms_iocb_entry_t));
	अगर (rval != QLA_SUCCESS) अणु
		/*EMPTY*/
		ql_dbg(ql_dbg_disc, vha, 0x2037,
		    "DHBA issue IOCB failed (%d).\n", rval);
	पूर्ण अन्यथा अगर (qla2x00_chk_ms_status(vha, ms_pkt, ct_rsp, "DHBA") !=
	    QLA_SUCCESS) अणु
		rval = QLA_FUNCTION_FAILED;
	पूर्ण अन्यथा अणु
		ql_dbg(ql_dbg_disc, vha, 0x2038,
		    "DHBA exiting normally.\n");
	पूर्ण
	वापस rval;
पूर्ण

/**
 * qla2x00_fdmi_rprt() - perक्रमm RPRT registration
 * @vha: HA context
 * @callopt: Option to issue extended or standard FDMI
 *           command parameter
 *
 * Returns 0 on success.
 */
अटल पूर्णांक
qla2x00_fdmi_rprt(scsi_qla_host_t *vha, पूर्णांक callopt)
अणु
	काष्ठा scsi_qla_host *base_vha = pci_get_drvdata(vha->hw->pdev);
	काष्ठा qla_hw_data *ha = vha->hw;
	uदीर्घ size = 0;
	uपूर्णांक rval, count;
	ms_iocb_entry_t *ms_pkt;
	काष्ठा ct_sns_req *ct_req;
	काष्ठा ct_sns_rsp *ct_rsp;
	व्योम *entries;
	count = callopt == CALLOPT_FDMI2_SMARTSAN && ql2xsmartsan ?
		FDMI2_SMARTSAN_PORT_ATTR_COUNT :
		callopt != CALLOPT_FDMI1 ?
		FDMI2_PORT_ATTR_COUNT : FDMI1_PORT_ATTR_COUNT;

	size = RPRT_RSP_SIZE;
	ql_dbg(ql_dbg_disc, vha, 0x20e8,
	    "RPRT (callopt=%x count=%u size=%lu).\n", callopt, count, size);
	/* Request size adjusted after CT preparation */
	ms_pkt = ha->isp_ops->prep_ms_fdmi_iocb(vha, 0, size);
	/* Prepare CT request */
	ct_req = qla2x00_prep_ct_fdmi_req(ha->ct_sns, RPRT_CMD, size);
	ct_rsp = &ha->ct_sns->p.rsp;
	/* Prepare FDMI command entries */
	स_नकल(ct_req->req.rprt.hba_identअगरier, base_vha->port_name,
	    माप(ct_req->req.rprt.hba_identअगरier));
	size += माप(ct_req->req.rprt.hba_identअगरier);
	स_नकल(ct_req->req.rprt.port_name, vha->port_name,
	    माप(ct_req->req.rprt.port_name));
	size += माप(ct_req->req.rprt.port_name);
	/* Attribute count */
	ct_req->req.rprt.attrs.count = cpu_to_be32(count);
	size += माप(ct_req->req.rprt.attrs.count);
	/* Attribute block */
	entries = ct_req->req.rprt.attrs.entry;
	size += qla2x00_port_attributes(vha, entries, callopt);
	/* Update MS request size. */
	qla2x00_update_ms_fdmi_iocb(vha, size + 16);
	ql_dbg(ql_dbg_disc, vha, 0x20e9,
	    "RPRT %016llx  %016llx.\n",
	    wwn_to_u64(ct_req->req.rprt.port_name),
	    wwn_to_u64(ct_req->req.rprt.port_name));
	ql_dump_buffer(ql_dbg_disc + ql_dbg_buffer, vha, 0x20ea,
	    entries, size);
	/* Execute MS IOCB */
	rval = qla2x00_issue_iocb(vha, ha->ms_iocb, ha->ms_iocb_dma,
	    माप(*ha->ms_iocb));
	अगर (rval) अणु
		ql_dbg(ql_dbg_disc, vha, 0x20eb,
		    "RPRT iocb failed (%d).\n", rval);
		वापस rval;
	पूर्ण
	rval = qla2x00_chk_ms_status(vha, ms_pkt, ct_rsp, "RPRT");
	अगर (rval) अणु
		अगर (ct_rsp->header.reason_code == CT_REASON_CANNOT_PERFORM &&
		    ct_rsp->header.explanation_code ==
		    CT_EXPL_ALREADY_REGISTERED) अणु
			ql_dbg(ql_dbg_disc, vha, 0x20ec,
			    "RPRT already registered.\n");
			वापस QLA_ALREADY_REGISTERED;
		पूर्ण

		ql_dbg(ql_dbg_disc, vha, 0x20ed,
		    "RPRT failed, CT Reason code: %#x, CT Explanation %#x\n",
		    ct_rsp->header.reason_code,
		    ct_rsp->header.explanation_code);
		वापस rval;
	पूर्ण
	ql_dbg(ql_dbg_disc, vha, 0x20ee, "RPRT exiting normally.\n");
	वापस rval;
पूर्ण

/**
 * qla2x00_fdmi_rpa() - perक्रमm RPA registration
 * @vha: HA context
 * @callopt: Option to issue FDMI registration
 *
 * Returns 0 on success.
 */
अटल पूर्णांक
qla2x00_fdmi_rpa(scsi_qla_host_t *vha, uपूर्णांक callopt)
अणु
	काष्ठा qla_hw_data *ha = vha->hw;
	uदीर्घ size = 0;
	uपूर्णांक rval, count;
	ms_iocb_entry_t *ms_pkt;
	काष्ठा ct_sns_req *ct_req;
	काष्ठा ct_sns_rsp *ct_rsp;
	व्योम *entries;

	count =
	    callopt == CALLOPT_FDMI2_SMARTSAN && ql2xsmartsan ?
		FDMI2_SMARTSAN_PORT_ATTR_COUNT :
	    callopt != CALLOPT_FDMI1 ?
		FDMI2_PORT_ATTR_COUNT : FDMI1_PORT_ATTR_COUNT;

	size =
	    callopt != CALLOPT_FDMI1 ?
		SMARTSAN_RPA_RSP_SIZE : RPA_RSP_SIZE;

	ql_dbg(ql_dbg_disc, vha, 0x20f0,
	    "RPA (callopt=%x count=%u size=%lu).\n", callopt, count, size);

	/* Request size adjusted after CT preparation */
	ms_pkt = ha->isp_ops->prep_ms_fdmi_iocb(vha, 0, size);

	/* Prepare CT request */
	ct_req = qla2x00_prep_ct_fdmi_req(ha->ct_sns, RPA_CMD, size);
	ct_rsp = &ha->ct_sns->p.rsp;

	/* Prepare FDMI command entries. */
	स_नकल(ct_req->req.rpa.port_name, vha->port_name,
	    माप(ct_req->req.rpa.port_name));
	size += माप(ct_req->req.rpa.port_name);

	/* Attribute count */
	ct_req->req.rpa.attrs.count = cpu_to_be32(count);
	size += माप(ct_req->req.rpa.attrs.count);

	/* Attribute block */
	entries = ct_req->req.rpa.attrs.entry;

	size += qla2x00_port_attributes(vha, entries, callopt);

	/* Update MS request size. */
	qla2x00_update_ms_fdmi_iocb(vha, size + 16);

	ql_dbg(ql_dbg_disc, vha, 0x20f1,
	    "RPA %016llx.\n", wwn_to_u64(ct_req->req.rpa.port_name));

	ql_dump_buffer(ql_dbg_disc + ql_dbg_buffer, vha, 0x20f2,
	    entries, size);

	/* Execute MS IOCB */
	rval = qla2x00_issue_iocb(vha, ha->ms_iocb, ha->ms_iocb_dma,
	    माप(*ha->ms_iocb));
	अगर (rval) अणु
		ql_dbg(ql_dbg_disc, vha, 0x20f3,
		    "RPA iocb failed (%d).\n", rval);
		वापस rval;
	पूर्ण

	rval = qla2x00_chk_ms_status(vha, ms_pkt, ct_rsp, "RPA");
	अगर (rval) अणु
		अगर (ct_rsp->header.reason_code == CT_REASON_CANNOT_PERFORM &&
		    ct_rsp->header.explanation_code ==
		    CT_EXPL_ALREADY_REGISTERED) अणु
			ql_dbg(ql_dbg_disc, vha, 0x20f4,
			    "RPA already registered.\n");
			वापस QLA_ALREADY_REGISTERED;
		पूर्ण

		ql_dbg(ql_dbg_disc, vha, 0x20f5,
		    "RPA failed, CT Reason code: %#x, CT Explanation %#x\n",
		    ct_rsp->header.reason_code,
		    ct_rsp->header.explanation_code);
		वापस rval;
	पूर्ण

	ql_dbg(ql_dbg_disc, vha, 0x20f6, "RPA exiting normally.\n");
	वापस rval;
पूर्ण

/**
 * qla2x00_fdmi_रेजिस्टर() -
 * @vha: HA context
 *
 * Returns 0 on success.
 */
पूर्णांक
qla2x00_fdmi_रेजिस्टर(scsi_qla_host_t *vha)
अणु
	पूर्णांक rval = QLA_SUCCESS;
	काष्ठा qla_hw_data *ha = vha->hw;

	अगर (IS_QLA2100(ha) || IS_QLA2200(ha) ||
	    IS_QLAFX00(ha))
		वापस rval;

	rval = qla2x00_mgmt_svr_login(vha);
	अगर (rval)
		वापस rval;

	/* For npiv/vport send rprt only */
	अगर (vha->vp_idx) अणु
		अगर (ql2xsmartsan)
			rval = qla2x00_fdmi_rprt(vha, CALLOPT_FDMI2_SMARTSAN);
		अगर (rval || !ql2xsmartsan)
			rval = qla2x00_fdmi_rprt(vha, CALLOPT_FDMI2);
		अगर (rval)
			rval = qla2x00_fdmi_rprt(vha, CALLOPT_FDMI1);

		वापस rval;
	पूर्ण

	/* Try fdmi2 first, अगर fails then try fdmi1 */
	rval = qla2x00_fdmi_rhba(vha, CALLOPT_FDMI2);
	अगर (rval) अणु
		अगर (rval != QLA_ALREADY_REGISTERED)
			जाओ try_fdmi;

		rval = qla2x00_fdmi_dhba(vha);
		अगर (rval)
			जाओ try_fdmi;

		rval = qla2x00_fdmi_rhba(vha, CALLOPT_FDMI2);
		अगर (rval)
			जाओ try_fdmi;
	पूर्ण

	अगर (ql2xsmartsan)
		rval = qla2x00_fdmi_rpa(vha, CALLOPT_FDMI2_SMARTSAN);
	अगर (rval || !ql2xsmartsan)
		rval = qla2x00_fdmi_rpa(vha, CALLOPT_FDMI2);
	अगर (rval)
		जाओ try_fdmi;

	वापस rval;

try_fdmi:
	rval = qla2x00_fdmi_rhba(vha, CALLOPT_FDMI1);
	अगर (rval) अणु
		अगर (rval != QLA_ALREADY_REGISTERED)
			वापस rval;

		rval = qla2x00_fdmi_dhba(vha);
		अगर (rval)
			वापस rval;

		rval = qla2x00_fdmi_rhba(vha, CALLOPT_FDMI1);
		अगर (rval)
			वापस rval;
	पूर्ण

	rval = qla2x00_fdmi_rpa(vha, CALLOPT_FDMI1);

	वापस rval;
पूर्ण

/**
 * qla2x00_gfpn_id() - SNS Get Fabric Port Name (GFPN_ID) query.
 * @vha: HA context
 * @list: चयन info entries to populate
 *
 * Returns 0 on success.
 */
पूर्णांक
qla2x00_gfpn_id(scsi_qla_host_t *vha, sw_info_t *list)
अणु
	पूर्णांक		rval = QLA_SUCCESS;
	uपूर्णांक16_t	i;
	काष्ठा qla_hw_data *ha = vha->hw;
	ms_iocb_entry_t	*ms_pkt;
	काष्ठा ct_sns_req	*ct_req;
	काष्ठा ct_sns_rsp	*ct_rsp;
	काष्ठा ct_arg arg;

	अगर (!IS_IIDMA_CAPABLE(ha))
		वापस QLA_FUNCTION_FAILED;

	arg.iocb = ha->ms_iocb;
	arg.req_dma = ha->ct_sns_dma;
	arg.rsp_dma = ha->ct_sns_dma;
	arg.req_size = GFPN_ID_REQ_SIZE;
	arg.rsp_size = GFPN_ID_RSP_SIZE;
	arg.nport_handle = NPH_SNS;

	क्रम (i = 0; i < ha->max_fibre_devices; i++) अणु
		/* Issue GFPN_ID */
		/* Prepare common MS IOCB */
		ms_pkt = ha->isp_ops->prep_ms_iocb(vha, &arg);

		/* Prepare CT request */
		ct_req = qla2x00_prep_ct_req(ha->ct_sns, GFPN_ID_CMD,
		    GFPN_ID_RSP_SIZE);
		ct_rsp = &ha->ct_sns->p.rsp;

		/* Prepare CT arguments -- port_id */
		ct_req->req.port_id.port_id = port_id_to_be_id(list[i].d_id);

		/* Execute MS IOCB */
		rval = qla2x00_issue_iocb(vha, ha->ms_iocb, ha->ms_iocb_dma,
		    माप(ms_iocb_entry_t));
		अगर (rval != QLA_SUCCESS) अणु
			/*EMPTY*/
			ql_dbg(ql_dbg_disc, vha, 0x2023,
			    "GFPN_ID issue IOCB failed (%d).\n", rval);
			अवरोध;
		पूर्ण अन्यथा अगर (qla2x00_chk_ms_status(vha, ms_pkt, ct_rsp,
		    "GFPN_ID") != QLA_SUCCESS) अणु
			rval = QLA_FUNCTION_FAILED;
			अवरोध;
		पूर्ण अन्यथा अणु
			/* Save fabric portname */
			स_नकल(list[i].fabric_port_name,
			    ct_rsp->rsp.gfpn_id.port_name, WWN_SIZE);
		पूर्ण

		/* Last device निकास. */
		अगर (list[i].d_id.b.rsvd_1 != 0)
			अवरोध;
	पूर्ण

	वापस (rval);
पूर्ण


अटल अंतरभूत काष्ठा ct_sns_req *
qla24xx_prep_ct_fm_req(काष्ठा ct_sns_pkt *p, uपूर्णांक16_t cmd,
    uपूर्णांक16_t rsp_size)
अणु
	स_रखो(p, 0, माप(काष्ठा ct_sns_pkt));

	p->p.req.header.revision = 0x01;
	p->p.req.header.gs_type = 0xFA;
	p->p.req.header.gs_subtype = 0x01;
	p->p.req.command = cpu_to_be16(cmd);
	p->p.req.max_rsp_size = cpu_to_be16((rsp_size - 16) / 4);

	वापस &p->p.req;
पूर्ण

अटल uपूर्णांक16_t
qla2x00_port_speed_capability(uपूर्णांक16_t speed)
अणु
	चयन (speed) अणु
	हाल BIT_15:
		वापस PORT_SPEED_1GB;
	हाल BIT_14:
		वापस PORT_SPEED_2GB;
	हाल BIT_13:
		वापस PORT_SPEED_4GB;
	हाल BIT_12:
		वापस PORT_SPEED_10GB;
	हाल BIT_11:
		वापस PORT_SPEED_8GB;
	हाल BIT_10:
		वापस PORT_SPEED_16GB;
	हाल BIT_8:
		वापस PORT_SPEED_32GB;
	हाल BIT_7:
		वापस PORT_SPEED_64GB;
	शेष:
		वापस PORT_SPEED_UNKNOWN;
	पूर्ण
पूर्ण

/**
 * qla2x00_gpsc() - FCS Get Port Speed Capabilities (GPSC) query.
 * @vha: HA context
 * @list: चयन info entries to populate
 *
 * Returns 0 on success.
 */
पूर्णांक
qla2x00_gpsc(scsi_qla_host_t *vha, sw_info_t *list)
अणु
	पूर्णांक		rval;
	uपूर्णांक16_t	i;
	काष्ठा qla_hw_data *ha = vha->hw;
	ms_iocb_entry_t *ms_pkt;
	काष्ठा ct_sns_req	*ct_req;
	काष्ठा ct_sns_rsp	*ct_rsp;
	काष्ठा ct_arg arg;

	अगर (!IS_IIDMA_CAPABLE(ha))
		वापस QLA_FUNCTION_FAILED;
	अगर (!ha->flags.gpsc_supported)
		वापस QLA_FUNCTION_FAILED;

	rval = qla2x00_mgmt_svr_login(vha);
	अगर (rval)
		वापस rval;

	arg.iocb = ha->ms_iocb;
	arg.req_dma = ha->ct_sns_dma;
	arg.rsp_dma = ha->ct_sns_dma;
	arg.req_size = GPSC_REQ_SIZE;
	arg.rsp_size = GPSC_RSP_SIZE;
	arg.nport_handle = vha->mgmt_svr_loop_id;

	क्रम (i = 0; i < ha->max_fibre_devices; i++) अणु
		/* Issue GFPN_ID */
		/* Prepare common MS IOCB */
		ms_pkt = qla24xx_prep_ms_iocb(vha, &arg);

		/* Prepare CT request */
		ct_req = qla24xx_prep_ct_fm_req(ha->ct_sns, GPSC_CMD,
		    GPSC_RSP_SIZE);
		ct_rsp = &ha->ct_sns->p.rsp;

		/* Prepare CT arguments -- port_name */
		स_नकल(ct_req->req.gpsc.port_name, list[i].fabric_port_name,
		    WWN_SIZE);

		/* Execute MS IOCB */
		rval = qla2x00_issue_iocb(vha, ha->ms_iocb, ha->ms_iocb_dma,
		    माप(ms_iocb_entry_t));
		अगर (rval != QLA_SUCCESS) अणु
			/*EMPTY*/
			ql_dbg(ql_dbg_disc, vha, 0x2059,
			    "GPSC issue IOCB failed (%d).\n", rval);
		पूर्ण अन्यथा अगर ((rval = qla2x00_chk_ms_status(vha, ms_pkt, ct_rsp,
		    "GPSC")) != QLA_SUCCESS) अणु
			/* FM command unsupported? */
			अगर (rval == QLA_INVALID_COMMAND &&
			    (ct_rsp->header.reason_code ==
				CT_REASON_INVALID_COMMAND_CODE ||
			     ct_rsp->header.reason_code ==
				CT_REASON_COMMAND_UNSUPPORTED)) अणु
				ql_dbg(ql_dbg_disc, vha, 0x205a,
				    "GPSC command unsupported, disabling "
				    "query.\n");
				ha->flags.gpsc_supported = 0;
				rval = QLA_FUNCTION_FAILED;
				अवरोध;
			पूर्ण
			rval = QLA_FUNCTION_FAILED;
		पूर्ण अन्यथा अणु
			list->fp_speed = qla2x00_port_speed_capability(
			    be16_to_cpu(ct_rsp->rsp.gpsc.speed));
			ql_dbg(ql_dbg_disc, vha, 0x205b,
			    "GPSC ext entry - fpn "
			    "%8phN speeds=%04x speed=%04x.\n",
			    list[i].fabric_port_name,
			    be16_to_cpu(ct_rsp->rsp.gpsc.speeds),
			    be16_to_cpu(ct_rsp->rsp.gpsc.speed));
		पूर्ण

		/* Last device निकास. */
		अगर (list[i].d_id.b.rsvd_1 != 0)
			अवरोध;
	पूर्ण

	वापस (rval);
पूर्ण

/**
 * qla2x00_gff_id() - SNS Get FC-4 Features (GFF_ID) query.
 *
 * @vha: HA context
 * @list: चयन info entries to populate
 *
 */
व्योम
qla2x00_gff_id(scsi_qla_host_t *vha, sw_info_t *list)
अणु
	पूर्णांक		rval;
	uपूर्णांक16_t	i;

	ms_iocb_entry_t	*ms_pkt;
	काष्ठा ct_sns_req	*ct_req;
	काष्ठा ct_sns_rsp	*ct_rsp;
	काष्ठा qla_hw_data *ha = vha->hw;
	uपूर्णांक8_t fcp_scsi_features = 0, nvme_features = 0;
	काष्ठा ct_arg arg;

	क्रम (i = 0; i < ha->max_fibre_devices; i++) अणु
		/* Set शेष FC4 Type as UNKNOWN so the शेष is to
		 * Process this port */
		list[i].fc4_type = 0;

		/* Do not attempt GFF_ID अगर we are not FWI_2 capable */
		अगर (!IS_FWI2_CAPABLE(ha))
			जारी;

		arg.iocb = ha->ms_iocb;
		arg.req_dma = ha->ct_sns_dma;
		arg.rsp_dma = ha->ct_sns_dma;
		arg.req_size = GFF_ID_REQ_SIZE;
		arg.rsp_size = GFF_ID_RSP_SIZE;
		arg.nport_handle = NPH_SNS;

		/* Prepare common MS IOCB */
		ms_pkt = ha->isp_ops->prep_ms_iocb(vha, &arg);

		/* Prepare CT request */
		ct_req = qla2x00_prep_ct_req(ha->ct_sns, GFF_ID_CMD,
		    GFF_ID_RSP_SIZE);
		ct_rsp = &ha->ct_sns->p.rsp;

		/* Prepare CT arguments -- port_id */
		ct_req->req.port_id.port_id = port_id_to_be_id(list[i].d_id);

		/* Execute MS IOCB */
		rval = qla2x00_issue_iocb(vha, ha->ms_iocb, ha->ms_iocb_dma,
		   माप(ms_iocb_entry_t));

		अगर (rval != QLA_SUCCESS) अणु
			ql_dbg(ql_dbg_disc, vha, 0x205c,
			    "GFF_ID issue IOCB failed (%d).\n", rval);
		पूर्ण अन्यथा अगर (qla2x00_chk_ms_status(vha, ms_pkt, ct_rsp,
			       "GFF_ID") != QLA_SUCCESS) अणु
			ql_dbg(ql_dbg_disc, vha, 0x205d,
			    "GFF_ID IOCB status had a failure status code.\n");
		पूर्ण अन्यथा अणु
			fcp_scsi_features =
			   ct_rsp->rsp.gff_id.fc4_features[GFF_FCP_SCSI_OFFSET];
			fcp_scsi_features &= 0x0f;

			अगर (fcp_scsi_features) अणु
				list[i].fc4_type = FS_FC4TYPE_FCP;
				list[i].fc4_features = fcp_scsi_features;
			पूर्ण

			nvme_features =
			    ct_rsp->rsp.gff_id.fc4_features[GFF_NVME_OFFSET];
			nvme_features &= 0xf;

			अगर (nvme_features) अणु
				list[i].fc4_type |= FS_FC4TYPE_NVME;
				list[i].fc4_features = nvme_features;
			पूर्ण
		पूर्ण

		/* Last device निकास. */
		अगर (list[i].d_id.b.rsvd_1 != 0)
			अवरोध;
	पूर्ण
पूर्ण

पूर्णांक qla24xx_post_gpsc_work(काष्ठा scsi_qla_host *vha, fc_port_t *fcport)
अणु
	काष्ठा qla_work_evt *e;

	e = qla2x00_alloc_work(vha, QLA_EVT_GPSC);
	अगर (!e)
		वापस QLA_FUNCTION_FAILED;

	e->u.fcport.fcport = fcport;
	वापस qla2x00_post_work(vha, e);
पूर्ण

व्योम qla24xx_handle_gpsc_event(scsi_qla_host_t *vha, काष्ठा event_arg *ea)
अणु
	काष्ठा fc_port *fcport = ea->fcport;

	ql_dbg(ql_dbg_disc, vha, 0x20d8,
	    "%s %8phC DS %d LS %d rc %d login %d|%d rscn %d|%d lid %d\n",
	    __func__, fcport->port_name, fcport->disc_state,
	    fcport->fw_login_state, ea->rc, ea->sp->gen2, fcport->login_gen,
	    ea->sp->gen2, fcport->rscn_gen|ea->sp->gen1, fcport->loop_id);

	अगर (fcport->disc_state == DSC_DELETE_PEND)
		वापस;

	अगर (ea->sp->gen2 != fcport->login_gen) अणु
		/* target side must have changed it. */
		ql_dbg(ql_dbg_disc, vha, 0x20d3,
		    "%s %8phC generation changed\n",
		    __func__, fcport->port_name);
		वापस;
	पूर्ण अन्यथा अगर (ea->sp->gen1 != fcport->rscn_gen) अणु
		वापस;
	पूर्ण

	qla_post_iidma_work(vha, fcport);
पूर्ण

अटल व्योम qla24xx_async_gpsc_sp_करोne(srb_t *sp, पूर्णांक res)
अणु
	काष्ठा scsi_qla_host *vha = sp->vha;
	काष्ठा qla_hw_data *ha = vha->hw;
	fc_port_t *fcport = sp->fcport;
	काष्ठा ct_sns_rsp       *ct_rsp;
	काष्ठा event_arg ea;

	ct_rsp = &fcport->ct_desc.ct_sns->p.rsp;

	ql_dbg(ql_dbg_disc, vha, 0x2053,
	    "Async done-%s res %x, WWPN %8phC \n",
	    sp->name, res, fcport->port_name);

	fcport->flags &= ~(FCF_ASYNC_SENT | FCF_ASYNC_ACTIVE);

	अगर (res == QLA_FUNCTION_TIMEOUT)
		जाओ करोne;

	अगर (res == (DID_ERROR << 16)) अणु
		/* entry status error */
		जाओ करोne;
	पूर्ण अन्यथा अगर (res) अणु
		अगर ((ct_rsp->header.reason_code ==
			 CT_REASON_INVALID_COMMAND_CODE) ||
			(ct_rsp->header.reason_code ==
			CT_REASON_COMMAND_UNSUPPORTED)) अणु
			ql_dbg(ql_dbg_disc, vha, 0x2019,
			    "GPSC command unsupported, disabling query.\n");
			ha->flags.gpsc_supported = 0;
			जाओ करोne;
		पूर्ण
	पूर्ण अन्यथा अणु
		fcport->fp_speed = qla2x00_port_speed_capability(
		    be16_to_cpu(ct_rsp->rsp.gpsc.speed));

		ql_dbg(ql_dbg_disc, vha, 0x2054,
		    "Async-%s OUT WWPN %8phC speeds=%04x speed=%04x.\n",
		    sp->name, fcport->fabric_port_name,
		    be16_to_cpu(ct_rsp->rsp.gpsc.speeds),
		    be16_to_cpu(ct_rsp->rsp.gpsc.speed));
	पूर्ण
	स_रखो(&ea, 0, माप(ea));
	ea.rc = res;
	ea.fcport = fcport;
	ea.sp = sp;
	qla24xx_handle_gpsc_event(vha, &ea);

करोne:
	sp->मुक्त(sp);
पूर्ण

पूर्णांक qla24xx_async_gpsc(scsi_qla_host_t *vha, fc_port_t *fcport)
अणु
	पूर्णांक rval = QLA_FUNCTION_FAILED;
	काष्ठा ct_sns_req       *ct_req;
	srb_t *sp;

	अगर (!vha->flags.online || (fcport->flags & FCF_ASYNC_SENT))
		वापस rval;

	sp = qla2x00_get_sp(vha, fcport, GFP_KERNEL);
	अगर (!sp)
		जाओ करोne;

	sp->type = SRB_CT_PTHRU_CMD;
	sp->name = "gpsc";
	sp->gen1 = fcport->rscn_gen;
	sp->gen2 = fcport->login_gen;

	qla2x00_init_समयr(sp, qla2x00_get_async_समयout(vha) + 2);

	/* CT_IU preamble  */
	ct_req = qla24xx_prep_ct_fm_req(fcport->ct_desc.ct_sns, GPSC_CMD,
		GPSC_RSP_SIZE);

	/* GPSC req */
	स_नकल(ct_req->req.gpsc.port_name, fcport->fabric_port_name,
		WWN_SIZE);

	sp->u.iocb_cmd.u.ctarg.req = fcport->ct_desc.ct_sns;
	sp->u.iocb_cmd.u.ctarg.req_dma = fcport->ct_desc.ct_sns_dma;
	sp->u.iocb_cmd.u.ctarg.rsp = fcport->ct_desc.ct_sns;
	sp->u.iocb_cmd.u.ctarg.rsp_dma = fcport->ct_desc.ct_sns_dma;
	sp->u.iocb_cmd.u.ctarg.req_size = GPSC_REQ_SIZE;
	sp->u.iocb_cmd.u.ctarg.rsp_size = GPSC_RSP_SIZE;
	sp->u.iocb_cmd.u.ctarg.nport_handle = vha->mgmt_svr_loop_id;

	sp->u.iocb_cmd.समयout = qla2x00_async_iocb_समयout;
	sp->करोne = qla24xx_async_gpsc_sp_करोne;

	ql_dbg(ql_dbg_disc, vha, 0x205e,
	    "Async-%s %8phC hdl=%x loopid=%x portid=%02x%02x%02x.\n",
	    sp->name, fcport->port_name, sp->handle,
	    fcport->loop_id, fcport->d_id.b.करोमुख्य,
	    fcport->d_id.b.area, fcport->d_id.b.al_pa);

	rval = qla2x00_start_sp(sp);
	अगर (rval != QLA_SUCCESS)
		जाओ करोne_मुक्त_sp;
	वापस rval;

करोne_मुक्त_sp:
	sp->मुक्त(sp);
करोne:
	वापस rval;
पूर्ण

पूर्णांक qla24xx_post_gpnid_work(काष्ठा scsi_qla_host *vha, port_id_t *id)
अणु
	काष्ठा qla_work_evt *e;

	अगर (test_bit(UNLOADING, &vha->dpc_flags) ||
	    (vha->vp_idx && test_bit(VPORT_DELETE, &vha->dpc_flags)))
		वापस 0;

	e = qla2x00_alloc_work(vha, QLA_EVT_GPNID);
	अगर (!e)
		वापस QLA_FUNCTION_FAILED;

	e->u.gpnid.id = *id;
	वापस qla2x00_post_work(vha, e);
पूर्ण

व्योम qla24xx_sp_unmap(scsi_qla_host_t *vha, srb_t *sp)
अणु
	काष्ठा srb_iocb *c = &sp->u.iocb_cmd;

	चयन (sp->type) अणु
	हाल SRB_ELS_DCMD:
		qla2x00_els_dcmd2_मुक्त(vha, &c->u.els_plogi);
		अवरोध;
	हाल SRB_CT_PTHRU_CMD:
	शेष:
		अगर (sp->u.iocb_cmd.u.ctarg.req) अणु
			dma_मुक्त_coherent(&vha->hw->pdev->dev,
			    sp->u.iocb_cmd.u.ctarg.req_allocated_size,
			    sp->u.iocb_cmd.u.ctarg.req,
			    sp->u.iocb_cmd.u.ctarg.req_dma);
			sp->u.iocb_cmd.u.ctarg.req = शून्य;
		पूर्ण

		अगर (sp->u.iocb_cmd.u.ctarg.rsp) अणु
			dma_मुक्त_coherent(&vha->hw->pdev->dev,
			    sp->u.iocb_cmd.u.ctarg.rsp_allocated_size,
			    sp->u.iocb_cmd.u.ctarg.rsp,
			    sp->u.iocb_cmd.u.ctarg.rsp_dma);
			sp->u.iocb_cmd.u.ctarg.rsp = शून्य;
		पूर्ण
		अवरोध;
	पूर्ण

	sp->मुक्त(sp);
पूर्ण

व्योम qla24xx_handle_gpnid_event(scsi_qla_host_t *vha, काष्ठा event_arg *ea)
अणु
	fc_port_t *fcport, *conflict, *t;
	u16 data[2];

	ql_dbg(ql_dbg_disc, vha, 0xffff,
	    "%s %d port_id: %06x\n",
	    __func__, __LINE__, ea->id.b24);

	अगर (ea->rc) अणु
		/* cable is disconnected */
		list_क्रम_each_entry_safe(fcport, t, &vha->vp_fcports, list) अणु
			अगर (fcport->d_id.b24 == ea->id.b24)
				fcport->scan_state = QLA_FCPORT_SCAN;

			qlt_schedule_sess_क्रम_deletion(fcport);
		पूर्ण
	पूर्ण अन्यथा अणु
		/* cable is connected */
		fcport = qla2x00_find_fcport_by_wwpn(vha, ea->port_name, 1);
		अगर (fcport) अणु
			list_क्रम_each_entry_safe(conflict, t, &vha->vp_fcports,
			    list) अणु
				अगर ((conflict->d_id.b24 == ea->id.b24) &&
				    (fcport != conflict))
					/*
					 * 2 fcports with conflict Nport ID or
					 * an existing fcport is having nport ID
					 * conflict with new fcport.
					 */

					conflict->scan_state = QLA_FCPORT_SCAN;

				qlt_schedule_sess_क्रम_deletion(conflict);
			पूर्ण

			fcport->scan_needed = 0;
			fcport->rscn_gen++;
			fcport->scan_state = QLA_FCPORT_FOUND;
			fcport->flags |= FCF_FABRIC_DEVICE;
			अगर (fcport->login_retry == 0) अणु
				fcport->login_retry =
					vha->hw->login_retry_count;
				ql_dbg(ql_dbg_disc, vha, 0xffff,
				    "Port login retry %8phN, lid 0x%04x cnt=%d.\n",
				    fcport->port_name, fcport->loop_id,
				    fcport->login_retry);
			पूर्ण
			चयन (fcport->disc_state) अणु
			हाल DSC_LOGIN_COMPLETE:
				/* recheck session is still पूर्णांकact. */
				ql_dbg(ql_dbg_disc, vha, 0x210d,
				    "%s %d %8phC revalidate session with ADISC\n",
				    __func__, __LINE__, fcport->port_name);
				data[0] = data[1] = 0;
				qla2x00_post_async_adisc_work(vha, fcport,
				    data);
				अवरोध;
			हाल DSC_DELETED:
				ql_dbg(ql_dbg_disc, vha, 0x210d,
				    "%s %d %8phC login\n", __func__, __LINE__,
				    fcport->port_name);
				fcport->d_id = ea->id;
				qla24xx_fcport_handle_login(vha, fcport);
				अवरोध;
			हाल DSC_DELETE_PEND:
				fcport->d_id = ea->id;
				अवरोध;
			शेष:
				fcport->d_id = ea->id;
				अवरोध;
			पूर्ण
		पूर्ण अन्यथा अणु
			list_क्रम_each_entry_safe(conflict, t, &vha->vp_fcports,
			    list) अणु
				अगर (conflict->d_id.b24 == ea->id.b24) अणु
					/* 2 fcports with conflict Nport ID or
					 * an existing fcport is having nport ID
					 * conflict with new fcport.
					 */
					ql_dbg(ql_dbg_disc, vha, 0xffff,
					    "%s %d %8phC DS %d\n",
					    __func__, __LINE__,
					    conflict->port_name,
					    conflict->disc_state);

					conflict->scan_state = QLA_FCPORT_SCAN;
					qlt_schedule_sess_क्रम_deletion(conflict);
				पूर्ण
			पूर्ण

			/* create new fcport */
			ql_dbg(ql_dbg_disc, vha, 0x2065,
			    "%s %d %8phC post new sess\n",
			    __func__, __LINE__, ea->port_name);
			qla24xx_post_newsess_work(vha, &ea->id,
			    ea->port_name, शून्य, शून्य, 0);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम qla2x00_async_gpnid_sp_करोne(srb_t *sp, पूर्णांक res)
अणु
	काष्ठा scsi_qla_host *vha = sp->vha;
	काष्ठा ct_sns_req *ct_req =
	    (काष्ठा ct_sns_req *)sp->u.iocb_cmd.u.ctarg.req;
	काष्ठा ct_sns_rsp *ct_rsp =
	    (काष्ठा ct_sns_rsp *)sp->u.iocb_cmd.u.ctarg.rsp;
	काष्ठा event_arg ea;
	काष्ठा qla_work_evt *e;
	अचिन्हित दीर्घ flags;

	अगर (res)
		ql_dbg(ql_dbg_disc, vha, 0x2066,
		    "Async done-%s fail res %x rscn gen %d ID %3phC. %8phC\n",
		    sp->name, res, sp->gen1, &ct_req->req.port_id.port_id,
		    ct_rsp->rsp.gpn_id.port_name);
	अन्यथा
		ql_dbg(ql_dbg_disc, vha, 0x2066,
		    "Async done-%s good rscn gen %d ID %3phC. %8phC\n",
		    sp->name, sp->gen1, &ct_req->req.port_id.port_id,
		    ct_rsp->rsp.gpn_id.port_name);

	स_रखो(&ea, 0, माप(ea));
	स_नकल(ea.port_name, ct_rsp->rsp.gpn_id.port_name, WWN_SIZE);
	ea.sp = sp;
	ea.id = be_to_port_id(ct_req->req.port_id.port_id);
	ea.rc = res;

	spin_lock_irqsave(&vha->hw->tgt.sess_lock, flags);
	list_del(&sp->elem);
	spin_unlock_irqrestore(&vha->hw->tgt.sess_lock, flags);

	अगर (res) अणु
		अगर (res == QLA_FUNCTION_TIMEOUT) अणु
			qla24xx_post_gpnid_work(sp->vha, &ea.id);
			sp->मुक्त(sp);
			वापस;
		पूर्ण
	पूर्ण अन्यथा अगर (sp->gen1) अणु
		/* There was another RSCN क्रम this Nport ID */
		qla24xx_post_gpnid_work(sp->vha, &ea.id);
		sp->मुक्त(sp);
		वापस;
	पूर्ण

	qla24xx_handle_gpnid_event(vha, &ea);

	e = qla2x00_alloc_work(vha, QLA_EVT_UNMAP);
	अगर (!e) अणु
		/* please ignore kernel warning. otherwise, we have mem leak. */
		dma_मुक्त_coherent(&vha->hw->pdev->dev,
				  sp->u.iocb_cmd.u.ctarg.req_allocated_size,
				  sp->u.iocb_cmd.u.ctarg.req,
				  sp->u.iocb_cmd.u.ctarg.req_dma);
		sp->u.iocb_cmd.u.ctarg.req = शून्य;

		dma_मुक्त_coherent(&vha->hw->pdev->dev,
				  sp->u.iocb_cmd.u.ctarg.rsp_allocated_size,
				  sp->u.iocb_cmd.u.ctarg.rsp,
				  sp->u.iocb_cmd.u.ctarg.rsp_dma);
		sp->u.iocb_cmd.u.ctarg.rsp = शून्य;

		sp->मुक्त(sp);
		वापस;
	पूर्ण

	e->u.iosb.sp = sp;
	qla2x00_post_work(vha, e);
पूर्ण

/* Get WWPN with Nport ID. */
पूर्णांक qla24xx_async_gpnid(scsi_qla_host_t *vha, port_id_t *id)
अणु
	पूर्णांक rval = QLA_FUNCTION_FAILED;
	काष्ठा ct_sns_req       *ct_req;
	srb_t *sp, *tsp;
	काष्ठा ct_sns_pkt *ct_sns;
	अचिन्हित दीर्घ flags;

	अगर (!vha->flags.online)
		जाओ करोne;

	sp = qla2x00_get_sp(vha, शून्य, GFP_KERNEL);
	अगर (!sp)
		जाओ करोne;

	sp->type = SRB_CT_PTHRU_CMD;
	sp->name = "gpnid";
	sp->u.iocb_cmd.u.ctarg.id = *id;
	sp->gen1 = 0;
	qla2x00_init_समयr(sp, qla2x00_get_async_समयout(vha) + 2);

	spin_lock_irqsave(&vha->hw->tgt.sess_lock, flags);
	list_क्रम_each_entry(tsp, &vha->gpnid_list, elem) अणु
		अगर (tsp->u.iocb_cmd.u.ctarg.id.b24 == id->b24) अणु
			tsp->gen1++;
			spin_unlock_irqrestore(&vha->hw->tgt.sess_lock, flags);
			sp->मुक्त(sp);
			जाओ करोne;
		पूर्ण
	पूर्ण
	list_add_tail(&sp->elem, &vha->gpnid_list);
	spin_unlock_irqrestore(&vha->hw->tgt.sess_lock, flags);

	sp->u.iocb_cmd.u.ctarg.req = dma_alloc_coherent(&vha->hw->pdev->dev,
		माप(काष्ठा ct_sns_pkt), &sp->u.iocb_cmd.u.ctarg.req_dma,
		GFP_KERNEL);
	sp->u.iocb_cmd.u.ctarg.req_allocated_size = माप(काष्ठा ct_sns_pkt);
	अगर (!sp->u.iocb_cmd.u.ctarg.req) अणु
		ql_log(ql_log_warn, vha, 0xd041,
		    "Failed to allocate ct_sns request.\n");
		जाओ करोne_मुक्त_sp;
	पूर्ण

	sp->u.iocb_cmd.u.ctarg.rsp = dma_alloc_coherent(&vha->hw->pdev->dev,
		माप(काष्ठा ct_sns_pkt), &sp->u.iocb_cmd.u.ctarg.rsp_dma,
		GFP_KERNEL);
	sp->u.iocb_cmd.u.ctarg.rsp_allocated_size = माप(काष्ठा ct_sns_pkt);
	अगर (!sp->u.iocb_cmd.u.ctarg.rsp) अणु
		ql_log(ql_log_warn, vha, 0xd042,
		    "Failed to allocate ct_sns request.\n");
		जाओ करोne_मुक्त_sp;
	पूर्ण

	ct_sns = (काष्ठा ct_sns_pkt *)sp->u.iocb_cmd.u.ctarg.rsp;
	स_रखो(ct_sns, 0, माप(*ct_sns));

	ct_sns = (काष्ठा ct_sns_pkt *)sp->u.iocb_cmd.u.ctarg.req;
	/* CT_IU preamble  */
	ct_req = qla2x00_prep_ct_req(ct_sns, GPN_ID_CMD, GPN_ID_RSP_SIZE);

	/* GPN_ID req */
	ct_req->req.port_id.port_id = port_id_to_be_id(*id);

	sp->u.iocb_cmd.u.ctarg.req_size = GPN_ID_REQ_SIZE;
	sp->u.iocb_cmd.u.ctarg.rsp_size = GPN_ID_RSP_SIZE;
	sp->u.iocb_cmd.u.ctarg.nport_handle = NPH_SNS;

	sp->u.iocb_cmd.समयout = qla2x00_async_iocb_समयout;
	sp->करोne = qla2x00_async_gpnid_sp_करोne;

	ql_dbg(ql_dbg_disc, vha, 0x2067,
	    "Async-%s hdl=%x ID %3phC.\n", sp->name,
	    sp->handle, &ct_req->req.port_id.port_id);

	rval = qla2x00_start_sp(sp);
	अगर (rval != QLA_SUCCESS)
		जाओ करोne_मुक्त_sp;

	वापस rval;

करोne_मुक्त_sp:
	spin_lock_irqsave(&vha->hw->vport_slock, flags);
	list_del(&sp->elem);
	spin_unlock_irqrestore(&vha->hw->vport_slock, flags);

	अगर (sp->u.iocb_cmd.u.ctarg.req) अणु
		dma_मुक्त_coherent(&vha->hw->pdev->dev,
			माप(काष्ठा ct_sns_pkt),
			sp->u.iocb_cmd.u.ctarg.req,
			sp->u.iocb_cmd.u.ctarg.req_dma);
		sp->u.iocb_cmd.u.ctarg.req = शून्य;
	पूर्ण
	अगर (sp->u.iocb_cmd.u.ctarg.rsp) अणु
		dma_मुक्त_coherent(&vha->hw->pdev->dev,
			माप(काष्ठा ct_sns_pkt),
			sp->u.iocb_cmd.u.ctarg.rsp,
			sp->u.iocb_cmd.u.ctarg.rsp_dma);
		sp->u.iocb_cmd.u.ctarg.rsp = शून्य;
	पूर्ण

	sp->मुक्त(sp);
करोne:
	वापस rval;
पूर्ण

व्योम qla24xx_handle_gffid_event(scsi_qla_host_t *vha, काष्ठा event_arg *ea)
अणु
	fc_port_t *fcport = ea->fcport;

	qla24xx_post_gnl_work(vha, fcport);
पूर्ण

व्योम qla24xx_async_gffid_sp_करोne(srb_t *sp, पूर्णांक res)
अणु
	काष्ठा scsi_qla_host *vha = sp->vha;
	fc_port_t *fcport = sp->fcport;
	काष्ठा ct_sns_rsp *ct_rsp;
	काष्ठा event_arg ea;
	uपूर्णांक8_t fc4_scsi_feat;
	uपूर्णांक8_t fc4_nvme_feat;

	ql_dbg(ql_dbg_disc, vha, 0x2133,
	       "Async done-%s res %x ID %x. %8phC\n",
	       sp->name, res, fcport->d_id.b24, fcport->port_name);

	fcport->flags &= ~FCF_ASYNC_SENT;
	ct_rsp = &fcport->ct_desc.ct_sns->p.rsp;
	fc4_scsi_feat = ct_rsp->rsp.gff_id.fc4_features[GFF_FCP_SCSI_OFFSET];
	fc4_nvme_feat = ct_rsp->rsp.gff_id.fc4_features[GFF_NVME_OFFSET];

	/*
	 * FC-GS-7, 5.2.3.12 FC-4 Features - क्रमmat
	 * The क्रमmat of the FC-4 Features object, as defined by the FC-4,
	 * Shall be an array of 4-bit values, one क्रम each type code value
	 */
	अगर (!res) अणु
		अगर (fc4_scsi_feat & 0xf) अणु
			/* w1 b00:03 */
			fcport->fc4_type = FS_FC4TYPE_FCP;
			fcport->fc4_features = fc4_scsi_feat & 0xf;
		पूर्ण

		अगर (fc4_nvme_feat & 0xf) अणु
			/* w5 [00:03]/28h */
			fcport->fc4_type |= FS_FC4TYPE_NVME;
			fcport->fc4_features = fc4_nvme_feat & 0xf;
		पूर्ण
	पूर्ण

	स_रखो(&ea, 0, माप(ea));
	ea.sp = sp;
	ea.fcport = sp->fcport;
	ea.rc = res;

	qla24xx_handle_gffid_event(vha, &ea);
	sp->मुक्त(sp);
पूर्ण

/* Get FC4 Feature with Nport ID. */
पूर्णांक qla24xx_async_gffid(scsi_qla_host_t *vha, fc_port_t *fcport)
अणु
	पूर्णांक rval = QLA_FUNCTION_FAILED;
	काष्ठा ct_sns_req       *ct_req;
	srb_t *sp;

	अगर (!vha->flags.online || (fcport->flags & FCF_ASYNC_SENT))
		वापस rval;

	sp = qla2x00_get_sp(vha, fcport, GFP_KERNEL);
	अगर (!sp)
		वापस rval;

	fcport->flags |= FCF_ASYNC_SENT;
	sp->type = SRB_CT_PTHRU_CMD;
	sp->name = "gffid";
	sp->gen1 = fcport->rscn_gen;
	sp->gen2 = fcport->login_gen;

	sp->u.iocb_cmd.समयout = qla2x00_async_iocb_समयout;
	qla2x00_init_समयr(sp, qla2x00_get_async_समयout(vha) + 2);

	/* CT_IU preamble  */
	ct_req = qla2x00_prep_ct_req(fcport->ct_desc.ct_sns, GFF_ID_CMD,
	    GFF_ID_RSP_SIZE);

	ct_req->req.gff_id.port_id[0] = fcport->d_id.b.करोमुख्य;
	ct_req->req.gff_id.port_id[1] = fcport->d_id.b.area;
	ct_req->req.gff_id.port_id[2] = fcport->d_id.b.al_pa;

	sp->u.iocb_cmd.u.ctarg.req = fcport->ct_desc.ct_sns;
	sp->u.iocb_cmd.u.ctarg.req_dma = fcport->ct_desc.ct_sns_dma;
	sp->u.iocb_cmd.u.ctarg.rsp = fcport->ct_desc.ct_sns;
	sp->u.iocb_cmd.u.ctarg.rsp_dma = fcport->ct_desc.ct_sns_dma;
	sp->u.iocb_cmd.u.ctarg.req_size = GFF_ID_REQ_SIZE;
	sp->u.iocb_cmd.u.ctarg.rsp_size = GFF_ID_RSP_SIZE;
	sp->u.iocb_cmd.u.ctarg.nport_handle = NPH_SNS;

	sp->करोne = qla24xx_async_gffid_sp_करोne;

	ql_dbg(ql_dbg_disc, vha, 0x2132,
	    "Async-%s hdl=%x  %8phC.\n", sp->name,
	    sp->handle, fcport->port_name);

	rval = qla2x00_start_sp(sp);
	अगर (rval != QLA_SUCCESS)
		जाओ करोne_मुक्त_sp;

	वापस rval;
करोne_मुक्त_sp:
	sp->मुक्त(sp);
	fcport->flags &= ~FCF_ASYNC_SENT;
	वापस rval;
पूर्ण

/* GPN_FT + GNN_FT*/
अटल पूर्णांक qla2x00_is_a_vp(scsi_qla_host_t *vha, u64 wwn)
अणु
	काष्ठा qla_hw_data *ha = vha->hw;
	scsi_qla_host_t *vp;
	अचिन्हित दीर्घ flags;
	u64 twwn;
	पूर्णांक rc = 0;

	अगर (!ha->num_vhosts)
		वापस 0;

	spin_lock_irqsave(&ha->vport_slock, flags);
	list_क्रम_each_entry(vp, &ha->vp_list, list) अणु
		twwn = wwn_to_u64(vp->port_name);
		अगर (wwn == twwn) अणु
			rc = 1;
			अवरोध;
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&ha->vport_slock, flags);

	वापस rc;
पूर्ण

व्योम qla24xx_async_gnnft_करोne(scsi_qla_host_t *vha, srb_t *sp)
अणु
	fc_port_t *fcport;
	u32 i, rc;
	bool found;
	काष्ठा fab_scan_rp *rp, *trp;
	अचिन्हित दीर्घ flags;
	u8 recheck = 0;
	u16 dup = 0, dup_cnt = 0;

	ql_dbg(ql_dbg_disc + ql_dbg_verbose, vha, 0xffff,
	    "%s enter\n", __func__);

	अगर (sp->gen1 != vha->hw->base_qpair->chip_reset) अणु
		ql_dbg(ql_dbg_disc, vha, 0xffff,
		    "%s scan stop due to chip reset %x/%x\n",
		    sp->name, sp->gen1, vha->hw->base_qpair->chip_reset);
		जाओ out;
	पूर्ण

	rc = sp->rc;
	अगर (rc) अणु
		vha->scan.scan_retry++;
		अगर (vha->scan.scan_retry < MAX_SCAN_RETRIES) अणु
			set_bit(LOCAL_LOOP_UPDATE, &vha->dpc_flags);
			set_bit(LOOP_RESYNC_NEEDED, &vha->dpc_flags);
			जाओ out;
		पूर्ण अन्यथा अणु
			ql_dbg(ql_dbg_disc, vha, 0xffff,
			    "%s: Fabric scan failed for %d retries.\n",
			    __func__, vha->scan.scan_retry);
			/*
			 * Unable to scan any rports. logout loop below
			 * will unरेजिस्टर all sessions.
			 */
			list_क्रम_each_entry(fcport, &vha->vp_fcports, list) अणु
				अगर ((fcport->flags & FCF_FABRIC_DEVICE) != 0) अणु
					fcport->scan_state = QLA_FCPORT_SCAN;
					अगर (fcport->loop_id == FC_NO_LOOP_ID)
						fcport->logout_on_delete = 0;
					अन्यथा
						fcport->logout_on_delete = 1;
				पूर्ण
			पूर्ण
			जाओ login_logout;
		पूर्ण
	पूर्ण
	vha->scan.scan_retry = 0;

	list_क्रम_each_entry(fcport, &vha->vp_fcports, list)
		fcport->scan_state = QLA_FCPORT_SCAN;

	क्रम (i = 0; i < vha->hw->max_fibre_devices; i++) अणु
		u64 wwn;
		पूर्णांक k;

		rp = &vha->scan.l[i];
		found = false;

		wwn = wwn_to_u64(rp->port_name);
		अगर (wwn == 0)
			जारी;

		/* Remove duplicate NPORT ID entries from चयन data base */
		क्रम (k = i + 1; k < vha->hw->max_fibre_devices; k++) अणु
			trp = &vha->scan.l[k];
			अगर (rp->id.b24 == trp->id.b24) अणु
				dup = 1;
				dup_cnt++;
				ql_dbg(ql_dbg_disc + ql_dbg_verbose,
				    vha, 0xffff,
				    "Detected duplicate NPORT ID from switch data base: ID %06x WWN %8phN WWN %8phN\n",
				    rp->id.b24, rp->port_name, trp->port_name);
				स_रखो(trp, 0, माप(*trp));
			पूर्ण
		पूर्ण

		अगर (!स_भेद(rp->port_name, vha->port_name, WWN_SIZE))
			जारी;

		/* Bypass reserved करोमुख्य fields. */
		अगर ((rp->id.b.करोमुख्य & 0xf0) == 0xf0)
			जारी;

		/* Bypass भव ports of the same host. */
		अगर (qla2x00_is_a_vp(vha, wwn))
			जारी;

		list_क्रम_each_entry(fcport, &vha->vp_fcports, list) अणु
			अगर (स_भेद(rp->port_name, fcport->port_name, WWN_SIZE))
				जारी;
			fcport->scan_state = QLA_FCPORT_FOUND;
			fcport->last_rscn_gen = fcport->rscn_gen;
			found = true;
			/*
			 * If device was not a fabric device beक्रमe.
			 */
			अगर ((fcport->flags & FCF_FABRIC_DEVICE) == 0) अणु
				qla2x00_clear_loop_id(fcport);
				fcport->flags |= FCF_FABRIC_DEVICE;
			पूर्ण अन्यथा अगर (fcport->d_id.b24 != rp->id.b24 ||
				   (fcport->scan_needed &&
				    fcport->port_type != FCT_INITIATOR &&
				    fcport->port_type != FCT_NVME_INITIATOR)) अणु
				qlt_schedule_sess_क्रम_deletion(fcport);
			पूर्ण
			fcport->d_id.b24 = rp->id.b24;
			fcport->scan_needed = 0;
			अवरोध;
		पूर्ण

		अगर (!found) अणु
			ql_dbg(ql_dbg_disc, vha, 0xffff,
			    "%s %d %8phC post new sess\n",
			    __func__, __LINE__, rp->port_name);
			qla24xx_post_newsess_work(vha, &rp->id, rp->port_name,
			    rp->node_name, शून्य, rp->fc4type);
		पूर्ण
	पूर्ण

	अगर (dup) अणु
		ql_log(ql_log_warn, vha, 0xffff,
		    "Detected %d duplicate NPORT ID(s) from switch data base\n",
		    dup_cnt);
	पूर्ण

login_logout:
	/*
	 * Logout all previous fabric dev marked lost, except FCP2 devices.
	 */
	list_क्रम_each_entry(fcport, &vha->vp_fcports, list) अणु
		अगर ((fcport->flags & FCF_FABRIC_DEVICE) == 0) अणु
			fcport->scan_needed = 0;
			जारी;
		पूर्ण

		अगर (fcport->scan_state != QLA_FCPORT_FOUND) अणु
			bool करो_delete = false;

			अगर (fcport->scan_needed &&
			    fcport->disc_state == DSC_LOGIN_PEND) अणु
				/* Cable got disconnected after we sent
				 * a login. Do delete to prevent समयout.
				 */
				fcport->logout_on_delete = 1;
				करो_delete = true;
			पूर्ण

			fcport->scan_needed = 0;
			अगर (((qla_dual_mode_enabled(vha) ||
			      qla_ini_mode_enabled(vha)) &&
			    atomic_पढ़ो(&fcport->state) == FCS_ONLINE) ||
				करो_delete) अणु
				अगर (fcport->loop_id != FC_NO_LOOP_ID) अणु
					अगर (fcport->flags & FCF_FCP2_DEVICE)
						fcport->logout_on_delete = 0;

					ql_log(ql_log_warn, vha, 0x20f0,
					       "%s %d %8phC post del sess\n",
					       __func__, __LINE__,
					       fcport->port_name);

					fcport->tgt_link_करोwn_समय = 0;
					qlt_schedule_sess_क्रम_deletion(fcport);
					जारी;
				पूर्ण
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (fcport->scan_needed ||
			    fcport->disc_state != DSC_LOGIN_COMPLETE) अणु
				अगर (fcport->login_retry == 0) अणु
					fcport->login_retry =
						vha->hw->login_retry_count;
					ql_dbg(ql_dbg_disc, vha, 0x20a3,
					    "Port login retry %8phN, lid 0x%04x retry cnt=%d.\n",
					    fcport->port_name, fcport->loop_id,
					    fcport->login_retry);
				पूर्ण
				fcport->scan_needed = 0;
				qla24xx_fcport_handle_login(vha, fcport);
			पूर्ण
		पूर्ण
	पूर्ण

	recheck = 1;
out:
	qla24xx_sp_unmap(vha, sp);
	spin_lock_irqsave(&vha->work_lock, flags);
	vha->scan.scan_flags &= ~SF_SCANNING;
	spin_unlock_irqrestore(&vha->work_lock, flags);

	अगर (recheck) अणु
		list_क्रम_each_entry(fcport, &vha->vp_fcports, list) अणु
			अगर (fcport->scan_needed) अणु
				set_bit(LOCAL_LOOP_UPDATE, &vha->dpc_flags);
				set_bit(LOOP_RESYNC_NEEDED, &vha->dpc_flags);
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक qla2x00_post_gnnft_gpnft_करोne_work(काष्ठा scsi_qla_host *vha,
    srb_t *sp, पूर्णांक cmd)
अणु
	काष्ठा qla_work_evt *e;

	अगर (cmd != QLA_EVT_GPNFT_DONE && cmd != QLA_EVT_GNNFT_DONE)
		वापस QLA_PARAMETER_ERROR;

	e = qla2x00_alloc_work(vha, cmd);
	अगर (!e)
		वापस QLA_FUNCTION_FAILED;

	e->u.iosb.sp = sp;

	वापस qla2x00_post_work(vha, e);
पूर्ण

अटल पूर्णांक qla2x00_post_nvme_gpnft_work(काष्ठा scsi_qla_host *vha,
    srb_t *sp, पूर्णांक cmd)
अणु
	काष्ठा qla_work_evt *e;

	अगर (cmd != QLA_EVT_GPNFT)
		वापस QLA_PARAMETER_ERROR;

	e = qla2x00_alloc_work(vha, cmd);
	अगर (!e)
		वापस QLA_FUNCTION_FAILED;

	e->u.gpnft.fc4_type = FC4_TYPE_NVME;
	e->u.gpnft.sp = sp;

	वापस qla2x00_post_work(vha, e);
पूर्ण

अटल व्योम qla2x00_find_मुक्त_fcp_nvme_slot(काष्ठा scsi_qla_host *vha,
	काष्ठा srb *sp)
अणु
	काष्ठा qla_hw_data *ha = vha->hw;
	पूर्णांक num_fibre_dev = ha->max_fibre_devices;
	काष्ठा ct_sns_req *ct_req =
		(काष्ठा ct_sns_req *)sp->u.iocb_cmd.u.ctarg.req;
	काष्ठा ct_sns_gpnft_rsp *ct_rsp =
		(काष्ठा ct_sns_gpnft_rsp *)sp->u.iocb_cmd.u.ctarg.rsp;
	काष्ठा ct_sns_gpn_ft_data *d;
	काष्ठा fab_scan_rp *rp;
	u16 cmd = be16_to_cpu(ct_req->command);
	u8 fc4_type = sp->gen2;
	पूर्णांक i, j, k;
	port_id_t id;
	u8 found;
	u64 wwn;

	j = 0;
	क्रम (i = 0; i < num_fibre_dev; i++) अणु
		d  = &ct_rsp->entries[i];

		id.b.rsvd_1 = 0;
		id.b.करोमुख्य = d->port_id[0];
		id.b.area   = d->port_id[1];
		id.b.al_pa  = d->port_id[2];
		wwn = wwn_to_u64(d->port_name);

		अगर (id.b24 == 0 || wwn == 0)
			जारी;

		अगर (fc4_type == FC4_TYPE_FCP_SCSI) अणु
			अगर (cmd == GPN_FT_CMD) अणु
				rp = &vha->scan.l[j];
				rp->id = id;
				स_नकल(rp->port_name, d->port_name, 8);
				j++;
				rp->fc4type = FS_FC4TYPE_FCP;
			पूर्ण अन्यथा अणु
				क्रम (k = 0; k < num_fibre_dev; k++) अणु
					rp = &vha->scan.l[k];
					अगर (id.b24 == rp->id.b24) अणु
						स_नकल(rp->node_name,
						    d->port_name, 8);
						अवरोध;
					पूर्ण
				पूर्ण
			पूर्ण
		पूर्ण अन्यथा अणु
			/* Search अगर the fibre device supports FC4_TYPE_NVME */
			अगर (cmd == GPN_FT_CMD) अणु
				found = 0;

				क्रम (k = 0; k < num_fibre_dev; k++) अणु
					rp = &vha->scan.l[k];
					अगर (!स_भेद(rp->port_name,
					    d->port_name, 8)) अणु
						/*
						 * Supports FC-NVMe & FCP
						 */
						rp->fc4type |= FS_FC4TYPE_NVME;
						found = 1;
						अवरोध;
					पूर्ण
				पूर्ण

				/* We found new FC-NVMe only port */
				अगर (!found) अणु
					क्रम (k = 0; k < num_fibre_dev; k++) अणु
						rp = &vha->scan.l[k];
						अगर (wwn_to_u64(rp->port_name)) अणु
							जारी;
						पूर्ण अन्यथा अणु
							rp->id = id;
							स_नकल(rp->port_name,
							    d->port_name, 8);
							rp->fc4type =
							    FS_FC4TYPE_NVME;
							अवरोध;
						पूर्ण
					पूर्ण
				पूर्ण
			पूर्ण अन्यथा अणु
				क्रम (k = 0; k < num_fibre_dev; k++) अणु
					rp = &vha->scan.l[k];
					अगर (id.b24 == rp->id.b24) अणु
						स_नकल(rp->node_name,
						    d->port_name, 8);
						अवरोध;
					पूर्ण
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम qla2x00_async_gpnft_gnnft_sp_करोne(srb_t *sp, पूर्णांक res)
अणु
	काष्ठा scsi_qla_host *vha = sp->vha;
	काष्ठा ct_sns_req *ct_req =
		(काष्ठा ct_sns_req *)sp->u.iocb_cmd.u.ctarg.req;
	u16 cmd = be16_to_cpu(ct_req->command);
	u8 fc4_type = sp->gen2;
	अचिन्हित दीर्घ flags;
	पूर्णांक rc;

	/* gen2 field is holding the fc4type */
	ql_dbg(ql_dbg_disc, vha, 0xffff,
	    "Async done-%s res %x FC4Type %x\n",
	    sp->name, res, sp->gen2);

	del_समयr(&sp->u.iocb_cmd.समयr);
	sp->rc = res;
	अगर (res) अणु
		अचिन्हित दीर्घ flags;
		स्थिर अक्षर *name = sp->name;

		अगर (res == QLA_OS_TIMER_EXPIRED) अणु
			/* चयन is ignoring all commands.
			 * This might be a zone disable behavior.
			 * This means we hit 64s समयout.
			 * 22s GPNFT + 44s Abort = 64s
			 */
			ql_dbg(ql_dbg_disc, vha, 0xffff,
			       "%s: Switch Zone check please .\n",
			       name);
			qla2x00_mark_all_devices_lost(vha);
		पूर्ण

		/*
		 * We are in an Interrupt context, queue up this
		 * sp क्रम GNNFT_DONE work. This will allow all
		 * the resource to get मुक्तd up.
		 */
		rc = qla2x00_post_gnnft_gpnft_करोne_work(vha, sp,
		    QLA_EVT_GNNFT_DONE);
		अगर (rc) अणु
			/* Cleanup here to prevent memory leak */
			qla24xx_sp_unmap(vha, sp);

			spin_lock_irqsave(&vha->work_lock, flags);
			vha->scan.scan_flags &= ~SF_SCANNING;
			vha->scan.scan_retry++;
			spin_unlock_irqrestore(&vha->work_lock, flags);

			अगर (vha->scan.scan_retry < MAX_SCAN_RETRIES) अणु
				set_bit(LOCAL_LOOP_UPDATE, &vha->dpc_flags);
				set_bit(LOOP_RESYNC_NEEDED, &vha->dpc_flags);
				qla2xxx_wake_dpc(vha);
			पूर्ण अन्यथा अणु
				ql_dbg(ql_dbg_disc, vha, 0xffff,
				    "Async done-%s rescan failed on all retries.\n",
				    name);
			पूर्ण
		पूर्ण
		वापस;
	पूर्ण

	qla2x00_find_मुक्त_fcp_nvme_slot(vha, sp);

	अगर ((fc4_type == FC4_TYPE_FCP_SCSI) && vha->flags.nvme_enabled &&
	    cmd == GNN_FT_CMD) अणु
		spin_lock_irqsave(&vha->work_lock, flags);
		vha->scan.scan_flags &= ~SF_SCANNING;
		spin_unlock_irqrestore(&vha->work_lock, flags);

		sp->rc = res;
		rc = qla2x00_post_nvme_gpnft_work(vha, sp, QLA_EVT_GPNFT);
		अगर (rc) अणु
			qla24xx_sp_unmap(vha, sp);
			set_bit(LOCAL_LOOP_UPDATE, &vha->dpc_flags);
			set_bit(LOOP_RESYNC_NEEDED, &vha->dpc_flags);
		पूर्ण
		वापस;
	पूर्ण

	अगर (cmd == GPN_FT_CMD) अणु
		rc = qla2x00_post_gnnft_gpnft_करोne_work(vha, sp,
		    QLA_EVT_GPNFT_DONE);
	पूर्ण अन्यथा अणु
		rc = qla2x00_post_gnnft_gpnft_करोne_work(vha, sp,
		    QLA_EVT_GNNFT_DONE);
	पूर्ण

	अगर (rc) अणु
		qla24xx_sp_unmap(vha, sp);
		set_bit(LOCAL_LOOP_UPDATE, &vha->dpc_flags);
		set_bit(LOOP_RESYNC_NEEDED, &vha->dpc_flags);
		वापस;
	पूर्ण
पूर्ण

/*
 * Get WWNN list क्रम fc4_type
 *
 * It is assumed the same SRB is re-used from GPNFT to aव्योम
 * mem मुक्त & re-alloc
 */
अटल पूर्णांक qla24xx_async_gnnft(scsi_qla_host_t *vha, काष्ठा srb *sp,
    u8 fc4_type)
अणु
	पूर्णांक rval = QLA_FUNCTION_FAILED;
	काष्ठा ct_sns_req *ct_req;
	काष्ठा ct_sns_pkt *ct_sns;
	अचिन्हित दीर्घ flags;

	अगर (!vha->flags.online) अणु
		spin_lock_irqsave(&vha->work_lock, flags);
		vha->scan.scan_flags &= ~SF_SCANNING;
		spin_unlock_irqrestore(&vha->work_lock, flags);
		जाओ करोne_मुक्त_sp;
	पूर्ण

	अगर (!sp->u.iocb_cmd.u.ctarg.req || !sp->u.iocb_cmd.u.ctarg.rsp) अणु
		ql_log(ql_log_warn, vha, 0xffff,
		    "%s: req %p rsp %p are not setup\n",
		    __func__, sp->u.iocb_cmd.u.ctarg.req,
		    sp->u.iocb_cmd.u.ctarg.rsp);
		spin_lock_irqsave(&vha->work_lock, flags);
		vha->scan.scan_flags &= ~SF_SCANNING;
		spin_unlock_irqrestore(&vha->work_lock, flags);
		WARN_ON(1);
		set_bit(LOCAL_LOOP_UPDATE, &vha->dpc_flags);
		set_bit(LOOP_RESYNC_NEEDED, &vha->dpc_flags);
		जाओ करोne_मुक्त_sp;
	पूर्ण

	ql_dbg(ql_dbg_disc, vha, 0xfffff,
	    "%s: FC4Type %x, CT-PASSTHRU %s command ctarg rsp size %d, ctarg req size %d\n",
	    __func__, fc4_type, sp->name, sp->u.iocb_cmd.u.ctarg.rsp_size,
	     sp->u.iocb_cmd.u.ctarg.req_size);

	sp->type = SRB_CT_PTHRU_CMD;
	sp->name = "gnnft";
	sp->gen1 = vha->hw->base_qpair->chip_reset;
	sp->gen2 = fc4_type;

	sp->u.iocb_cmd.समयout = qla2x00_async_iocb_समयout;
	qla2x00_init_समयr(sp, qla2x00_get_async_समयout(vha) + 2);

	स_रखो(sp->u.iocb_cmd.u.ctarg.rsp, 0, sp->u.iocb_cmd.u.ctarg.rsp_size);
	स_रखो(sp->u.iocb_cmd.u.ctarg.req, 0, sp->u.iocb_cmd.u.ctarg.req_size);

	ct_sns = (काष्ठा ct_sns_pkt *)sp->u.iocb_cmd.u.ctarg.req;
	/* CT_IU preamble  */
	ct_req = qla2x00_prep_ct_req(ct_sns, GNN_FT_CMD,
	    sp->u.iocb_cmd.u.ctarg.rsp_size);

	/* GPN_FT req */
	ct_req->req.gpn_ft.port_type = fc4_type;

	sp->u.iocb_cmd.u.ctarg.req_size = GNN_FT_REQ_SIZE;
	sp->u.iocb_cmd.u.ctarg.nport_handle = NPH_SNS;

	sp->करोne = qla2x00_async_gpnft_gnnft_sp_करोne;

	ql_dbg(ql_dbg_disc, vha, 0xffff,
	    "Async-%s hdl=%x FC4Type %x.\n", sp->name,
	    sp->handle, ct_req->req.gpn_ft.port_type);

	rval = qla2x00_start_sp(sp);
	अगर (rval != QLA_SUCCESS) अणु
		जाओ करोne_मुक्त_sp;
	पूर्ण

	वापस rval;

करोne_मुक्त_sp:
	अगर (sp->u.iocb_cmd.u.ctarg.req) अणु
		dma_मुक्त_coherent(&vha->hw->pdev->dev,
		    sp->u.iocb_cmd.u.ctarg.req_allocated_size,
		    sp->u.iocb_cmd.u.ctarg.req,
		    sp->u.iocb_cmd.u.ctarg.req_dma);
		sp->u.iocb_cmd.u.ctarg.req = शून्य;
	पूर्ण
	अगर (sp->u.iocb_cmd.u.ctarg.rsp) अणु
		dma_मुक्त_coherent(&vha->hw->pdev->dev,
		    sp->u.iocb_cmd.u.ctarg.rsp_allocated_size,
		    sp->u.iocb_cmd.u.ctarg.rsp,
		    sp->u.iocb_cmd.u.ctarg.rsp_dma);
		sp->u.iocb_cmd.u.ctarg.rsp = शून्य;
	पूर्ण

	sp->मुक्त(sp);

	spin_lock_irqsave(&vha->work_lock, flags);
	vha->scan.scan_flags &= ~SF_SCANNING;
	अगर (vha->scan.scan_flags == 0) अणु
		ql_dbg(ql_dbg_disc, vha, 0xffff,
		    "%s: schedule\n", __func__);
		vha->scan.scan_flags |= SF_QUEUED;
		schedule_delayed_work(&vha->scan.scan_work, 5);
	पूर्ण
	spin_unlock_irqrestore(&vha->work_lock, flags);


	वापस rval;
पूर्ण /* GNNFT */

व्योम qla24xx_async_gpnft_करोne(scsi_qla_host_t *vha, srb_t *sp)
अणु
	ql_dbg(ql_dbg_disc + ql_dbg_verbose, vha, 0xffff,
	    "%s enter\n", __func__);
	qla24xx_async_gnnft(vha, sp, sp->gen2);
पूर्ण

/* Get WWPN list क्रम certain fc4_type */
पूर्णांक qla24xx_async_gpnft(scsi_qla_host_t *vha, u8 fc4_type, srb_t *sp)
अणु
	पूर्णांक rval = QLA_FUNCTION_FAILED;
	काष्ठा ct_sns_req       *ct_req;
	काष्ठा ct_sns_pkt *ct_sns;
	u32 rspsz;
	अचिन्हित दीर्घ flags;

	ql_dbg(ql_dbg_disc + ql_dbg_verbose, vha, 0xffff,
	    "%s enter\n", __func__);

	अगर (!vha->flags.online)
		वापस rval;

	spin_lock_irqsave(&vha->work_lock, flags);
	अगर (vha->scan.scan_flags & SF_SCANNING) अणु
		spin_unlock_irqrestore(&vha->work_lock, flags);
		ql_dbg(ql_dbg_disc + ql_dbg_verbose, vha, 0xffff,
		    "%s: scan active\n", __func__);
		वापस rval;
	पूर्ण
	vha->scan.scan_flags |= SF_SCANNING;
	spin_unlock_irqrestore(&vha->work_lock, flags);

	अगर (fc4_type == FC4_TYPE_FCP_SCSI) अणु
		ql_dbg(ql_dbg_disc + ql_dbg_verbose, vha, 0xffff,
		    "%s: Performing FCP Scan\n", __func__);

		अगर (sp)
			sp->मुक्त(sp); /* should not happen */

		sp = qla2x00_get_sp(vha, शून्य, GFP_KERNEL);
		अगर (!sp) अणु
			spin_lock_irqsave(&vha->work_lock, flags);
			vha->scan.scan_flags &= ~SF_SCANNING;
			spin_unlock_irqrestore(&vha->work_lock, flags);
			वापस rval;
		पूर्ण

		sp->u.iocb_cmd.u.ctarg.req = dma_alloc_coherent(&vha->hw->pdev->dev,
								माप(काष्ठा ct_sns_pkt),
								&sp->u.iocb_cmd.u.ctarg.req_dma,
								GFP_KERNEL);
		sp->u.iocb_cmd.u.ctarg.req_allocated_size = माप(काष्ठा ct_sns_pkt);
		अगर (!sp->u.iocb_cmd.u.ctarg.req) अणु
			ql_log(ql_log_warn, vha, 0xffff,
			    "Failed to allocate ct_sns request.\n");
			spin_lock_irqsave(&vha->work_lock, flags);
			vha->scan.scan_flags &= ~SF_SCANNING;
			spin_unlock_irqrestore(&vha->work_lock, flags);
			qla2x00_rel_sp(sp);
			वापस rval;
		पूर्ण
		sp->u.iocb_cmd.u.ctarg.req_size = GPN_FT_REQ_SIZE;

		rspsz = माप(काष्ठा ct_sns_gpnft_rsp) +
			((vha->hw->max_fibre_devices - 1) *
			    माप(काष्ठा ct_sns_gpn_ft_data));

		sp->u.iocb_cmd.u.ctarg.rsp = dma_alloc_coherent(&vha->hw->pdev->dev,
								rspsz,
								&sp->u.iocb_cmd.u.ctarg.rsp_dma,
								GFP_KERNEL);
		sp->u.iocb_cmd.u.ctarg.rsp_allocated_size = rspsz;
		अगर (!sp->u.iocb_cmd.u.ctarg.rsp) अणु
			ql_log(ql_log_warn, vha, 0xffff,
			    "Failed to allocate ct_sns request.\n");
			spin_lock_irqsave(&vha->work_lock, flags);
			vha->scan.scan_flags &= ~SF_SCANNING;
			spin_unlock_irqrestore(&vha->work_lock, flags);
			dma_मुक्त_coherent(&vha->hw->pdev->dev,
			    sp->u.iocb_cmd.u.ctarg.req_allocated_size,
			    sp->u.iocb_cmd.u.ctarg.req,
			    sp->u.iocb_cmd.u.ctarg.req_dma);
			sp->u.iocb_cmd.u.ctarg.req = शून्य;
			qla2x00_rel_sp(sp);
			वापस rval;
		पूर्ण
		sp->u.iocb_cmd.u.ctarg.rsp_size = rspsz;

		ql_dbg(ql_dbg_disc + ql_dbg_verbose, vha, 0xffff,
		    "%s scan list size %d\n", __func__, vha->scan.size);

		स_रखो(vha->scan.l, 0, vha->scan.size);
	पूर्ण अन्यथा अगर (!sp) अणु
		ql_dbg(ql_dbg_disc, vha, 0xffff,
		    "NVME scan did not provide SP\n");
		वापस rval;
	पूर्ण

	sp->type = SRB_CT_PTHRU_CMD;
	sp->name = "gpnft";
	sp->gen1 = vha->hw->base_qpair->chip_reset;
	sp->gen2 = fc4_type;

	sp->u.iocb_cmd.समयout = qla2x00_async_iocb_समयout;
	qla2x00_init_समयr(sp, qla2x00_get_async_समयout(vha) + 2);

	rspsz = sp->u.iocb_cmd.u.ctarg.rsp_size;
	स_रखो(sp->u.iocb_cmd.u.ctarg.rsp, 0, sp->u.iocb_cmd.u.ctarg.rsp_size);
	स_रखो(sp->u.iocb_cmd.u.ctarg.req, 0, sp->u.iocb_cmd.u.ctarg.req_size);

	ct_sns = (काष्ठा ct_sns_pkt *)sp->u.iocb_cmd.u.ctarg.req;
	/* CT_IU preamble  */
	ct_req = qla2x00_prep_ct_req(ct_sns, GPN_FT_CMD, rspsz);

	/* GPN_FT req */
	ct_req->req.gpn_ft.port_type = fc4_type;

	sp->u.iocb_cmd.u.ctarg.nport_handle = NPH_SNS;

	sp->करोne = qla2x00_async_gpnft_gnnft_sp_करोne;

	ql_dbg(ql_dbg_disc, vha, 0xffff,
	    "Async-%s hdl=%x FC4Type %x.\n", sp->name,
	    sp->handle, ct_req->req.gpn_ft.port_type);

	rval = qla2x00_start_sp(sp);
	अगर (rval != QLA_SUCCESS) अणु
		जाओ करोne_मुक्त_sp;
	पूर्ण

	वापस rval;

करोne_मुक्त_sp:
	अगर (sp->u.iocb_cmd.u.ctarg.req) अणु
		dma_मुक्त_coherent(&vha->hw->pdev->dev,
		    sp->u.iocb_cmd.u.ctarg.req_allocated_size,
		    sp->u.iocb_cmd.u.ctarg.req,
		    sp->u.iocb_cmd.u.ctarg.req_dma);
		sp->u.iocb_cmd.u.ctarg.req = शून्य;
	पूर्ण
	अगर (sp->u.iocb_cmd.u.ctarg.rsp) अणु
		dma_मुक्त_coherent(&vha->hw->pdev->dev,
		    sp->u.iocb_cmd.u.ctarg.rsp_allocated_size,
		    sp->u.iocb_cmd.u.ctarg.rsp,
		    sp->u.iocb_cmd.u.ctarg.rsp_dma);
		sp->u.iocb_cmd.u.ctarg.rsp = शून्य;
	पूर्ण

	sp->मुक्त(sp);

	spin_lock_irqsave(&vha->work_lock, flags);
	vha->scan.scan_flags &= ~SF_SCANNING;
	अगर (vha->scan.scan_flags == 0) अणु
		ql_dbg(ql_dbg_disc + ql_dbg_verbose, vha, 0xffff,
		    "%s: Scan scheduled.\n", __func__);
		vha->scan.scan_flags |= SF_QUEUED;
		schedule_delayed_work(&vha->scan.scan_work, 5);
	पूर्ण
	spin_unlock_irqrestore(&vha->work_lock, flags);


	वापस rval;
पूर्ण

व्योम qla_scan_work_fn(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा fab_scan *s = container_of(to_delayed_work(work),
	    काष्ठा fab_scan, scan_work);
	काष्ठा scsi_qla_host *vha = container_of(s, काष्ठा scsi_qla_host,
	    scan);
	अचिन्हित दीर्घ flags;

	ql_dbg(ql_dbg_disc, vha, 0xffff,
	    "%s: schedule loop resync\n", __func__);
	set_bit(LOCAL_LOOP_UPDATE, &vha->dpc_flags);
	set_bit(LOOP_RESYNC_NEEDED, &vha->dpc_flags);
	qla2xxx_wake_dpc(vha);
	spin_lock_irqsave(&vha->work_lock, flags);
	vha->scan.scan_flags &= ~SF_QUEUED;
	spin_unlock_irqrestore(&vha->work_lock, flags);
पूर्ण

/* GNN_ID */
व्योम qla24xx_handle_gnnid_event(scsi_qla_host_t *vha, काष्ठा event_arg *ea)
अणु
	qla24xx_post_gnl_work(vha, ea->fcport);
पूर्ण

अटल व्योम qla2x00_async_gnnid_sp_करोne(srb_t *sp, पूर्णांक res)
अणु
	काष्ठा scsi_qla_host *vha = sp->vha;
	fc_port_t *fcport = sp->fcport;
	u8 *node_name = fcport->ct_desc.ct_sns->p.rsp.rsp.gnn_id.node_name;
	काष्ठा event_arg ea;
	u64 wwnn;

	fcport->flags &= ~FCF_ASYNC_SENT;
	wwnn = wwn_to_u64(node_name);
	अगर (wwnn)
		स_नकल(fcport->node_name, node_name, WWN_SIZE);

	स_रखो(&ea, 0, माप(ea));
	ea.fcport = fcport;
	ea.sp = sp;
	ea.rc = res;

	ql_dbg(ql_dbg_disc, vha, 0x204f,
	    "Async done-%s res %x, WWPN %8phC %8phC\n",
	    sp->name, res, fcport->port_name, fcport->node_name);

	qla24xx_handle_gnnid_event(vha, &ea);

	sp->मुक्त(sp);
पूर्ण

पूर्णांक qla24xx_async_gnnid(scsi_qla_host_t *vha, fc_port_t *fcport)
अणु
	पूर्णांक rval = QLA_FUNCTION_FAILED;
	काष्ठा ct_sns_req       *ct_req;
	srb_t *sp;

	अगर (!vha->flags.online || (fcport->flags & FCF_ASYNC_SENT))
		वापस rval;

	qla2x00_set_fcport_disc_state(fcport, DSC_GNN_ID);
	sp = qla2x00_get_sp(vha, fcport, GFP_ATOMIC);
	अगर (!sp)
		जाओ करोne;

	fcport->flags |= FCF_ASYNC_SENT;
	sp->type = SRB_CT_PTHRU_CMD;
	sp->name = "gnnid";
	sp->gen1 = fcport->rscn_gen;
	sp->gen2 = fcport->login_gen;

	sp->u.iocb_cmd.समयout = qla2x00_async_iocb_समयout;
	qla2x00_init_समयr(sp, qla2x00_get_async_समयout(vha) + 2);

	/* CT_IU preamble  */
	ct_req = qla2x00_prep_ct_req(fcport->ct_desc.ct_sns, GNN_ID_CMD,
	    GNN_ID_RSP_SIZE);

	/* GNN_ID req */
	ct_req->req.port_id.port_id = port_id_to_be_id(fcport->d_id);


	/* req & rsp use the same buffer */
	sp->u.iocb_cmd.u.ctarg.req = fcport->ct_desc.ct_sns;
	sp->u.iocb_cmd.u.ctarg.req_dma = fcport->ct_desc.ct_sns_dma;
	sp->u.iocb_cmd.u.ctarg.rsp = fcport->ct_desc.ct_sns;
	sp->u.iocb_cmd.u.ctarg.rsp_dma = fcport->ct_desc.ct_sns_dma;
	sp->u.iocb_cmd.u.ctarg.req_size = GNN_ID_REQ_SIZE;
	sp->u.iocb_cmd.u.ctarg.rsp_size = GNN_ID_RSP_SIZE;
	sp->u.iocb_cmd.u.ctarg.nport_handle = NPH_SNS;

	sp->करोne = qla2x00_async_gnnid_sp_करोne;

	ql_dbg(ql_dbg_disc, vha, 0xffff,
	    "Async-%s - %8phC hdl=%x loopid=%x portid %06x.\n",
	    sp->name, fcport->port_name,
	    sp->handle, fcport->loop_id, fcport->d_id.b24);

	rval = qla2x00_start_sp(sp);
	अगर (rval != QLA_SUCCESS)
		जाओ करोne_मुक्त_sp;
	वापस rval;

करोne_मुक्त_sp:
	sp->मुक्त(sp);
	fcport->flags &= ~FCF_ASYNC_SENT;
करोne:
	वापस rval;
पूर्ण

पूर्णांक qla24xx_post_gnnid_work(काष्ठा scsi_qla_host *vha, fc_port_t *fcport)
अणु
	काष्ठा qla_work_evt *e;
	पूर्णांक ls;

	ls = atomic_पढ़ो(&vha->loop_state);
	अगर (((ls != LOOP_READY) && (ls != LOOP_UP)) ||
		test_bit(UNLOADING, &vha->dpc_flags))
		वापस 0;

	e = qla2x00_alloc_work(vha, QLA_EVT_GNNID);
	अगर (!e)
		वापस QLA_FUNCTION_FAILED;

	e->u.fcport.fcport = fcport;
	वापस qla2x00_post_work(vha, e);
पूर्ण

/* GPFN_ID */
व्योम qla24xx_handle_gfpnid_event(scsi_qla_host_t *vha, काष्ठा event_arg *ea)
अणु
	fc_port_t *fcport = ea->fcport;

	ql_dbg(ql_dbg_disc, vha, 0xffff,
	    "%s %8phC DS %d LS %d rc %d login %d|%d rscn %d|%d fcpcnt %d\n",
	    __func__, fcport->port_name, fcport->disc_state,
	    fcport->fw_login_state, ea->rc, fcport->login_gen, ea->sp->gen2,
	    fcport->rscn_gen, ea->sp->gen1, vha->fcport_count);

	अगर (fcport->disc_state == DSC_DELETE_PEND)
		वापस;

	अगर (ea->sp->gen2 != fcport->login_gen) अणु
		/* target side must have changed it. */
		ql_dbg(ql_dbg_disc, vha, 0x20d3,
		    "%s %8phC generation changed\n",
		    __func__, fcport->port_name);
		वापस;
	पूर्ण अन्यथा अगर (ea->sp->gen1 != fcport->rscn_gen) अणु
		वापस;
	पूर्ण

	qla24xx_post_gpsc_work(vha, fcport);
पूर्ण

अटल व्योम qla2x00_async_gfpnid_sp_करोne(srb_t *sp, पूर्णांक res)
अणु
	काष्ठा scsi_qla_host *vha = sp->vha;
	fc_port_t *fcport = sp->fcport;
	u8 *fpn = fcport->ct_desc.ct_sns->p.rsp.rsp.gfpn_id.port_name;
	काष्ठा event_arg ea;
	u64 wwn;

	wwn = wwn_to_u64(fpn);
	अगर (wwn)
		स_नकल(fcport->fabric_port_name, fpn, WWN_SIZE);

	स_रखो(&ea, 0, माप(ea));
	ea.fcport = fcport;
	ea.sp = sp;
	ea.rc = res;

	ql_dbg(ql_dbg_disc, vha, 0x204f,
	    "Async done-%s res %x, WWPN %8phC %8phC\n",
	    sp->name, res, fcport->port_name, fcport->fabric_port_name);

	qla24xx_handle_gfpnid_event(vha, &ea);

	sp->मुक्त(sp);
पूर्ण

पूर्णांक qla24xx_async_gfpnid(scsi_qla_host_t *vha, fc_port_t *fcport)
अणु
	पूर्णांक rval = QLA_FUNCTION_FAILED;
	काष्ठा ct_sns_req       *ct_req;
	srb_t *sp;

	अगर (!vha->flags.online || (fcport->flags & FCF_ASYNC_SENT))
		वापस rval;

	sp = qla2x00_get_sp(vha, fcport, GFP_ATOMIC);
	अगर (!sp)
		जाओ करोne;

	sp->type = SRB_CT_PTHRU_CMD;
	sp->name = "gfpnid";
	sp->gen1 = fcport->rscn_gen;
	sp->gen2 = fcport->login_gen;

	sp->u.iocb_cmd.समयout = qla2x00_async_iocb_समयout;
	qla2x00_init_समयr(sp, qla2x00_get_async_समयout(vha) + 2);

	/* CT_IU preamble  */
	ct_req = qla2x00_prep_ct_req(fcport->ct_desc.ct_sns, GFPN_ID_CMD,
	    GFPN_ID_RSP_SIZE);

	/* GFPN_ID req */
	ct_req->req.port_id.port_id = port_id_to_be_id(fcport->d_id);


	/* req & rsp use the same buffer */
	sp->u.iocb_cmd.u.ctarg.req = fcport->ct_desc.ct_sns;
	sp->u.iocb_cmd.u.ctarg.req_dma = fcport->ct_desc.ct_sns_dma;
	sp->u.iocb_cmd.u.ctarg.rsp = fcport->ct_desc.ct_sns;
	sp->u.iocb_cmd.u.ctarg.rsp_dma = fcport->ct_desc.ct_sns_dma;
	sp->u.iocb_cmd.u.ctarg.req_size = GFPN_ID_REQ_SIZE;
	sp->u.iocb_cmd.u.ctarg.rsp_size = GFPN_ID_RSP_SIZE;
	sp->u.iocb_cmd.u.ctarg.nport_handle = NPH_SNS;

	sp->करोne = qla2x00_async_gfpnid_sp_करोne;

	ql_dbg(ql_dbg_disc, vha, 0xffff,
	    "Async-%s - %8phC hdl=%x loopid=%x portid %06x.\n",
	    sp->name, fcport->port_name,
	    sp->handle, fcport->loop_id, fcport->d_id.b24);

	rval = qla2x00_start_sp(sp);
	अगर (rval != QLA_SUCCESS)
		जाओ करोne_मुक्त_sp;

	वापस rval;

करोne_मुक्त_sp:
	sp->मुक्त(sp);
करोne:
	वापस rval;
पूर्ण

पूर्णांक qla24xx_post_gfpnid_work(काष्ठा scsi_qla_host *vha, fc_port_t *fcport)
अणु
	काष्ठा qla_work_evt *e;
	पूर्णांक ls;

	ls = atomic_पढ़ो(&vha->loop_state);
	अगर (((ls != LOOP_READY) && (ls != LOOP_UP)) ||
		test_bit(UNLOADING, &vha->dpc_flags))
		वापस 0;

	e = qla2x00_alloc_work(vha, QLA_EVT_GFPNID);
	अगर (!e)
		वापस QLA_FUNCTION_FAILED;

	e->u.fcport.fcport = fcport;
	वापस qla2x00_post_work(vha, e);
पूर्ण
