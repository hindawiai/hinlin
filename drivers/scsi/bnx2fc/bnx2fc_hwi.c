<शैली गुरु>
/* bnx2fc_hwi.c: QLogic Linux FCoE offload driver.
 * This file contains the code that low level functions that पूर्णांकeract
 * with 57712 FCoE firmware.
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

DECLARE_PER_CPU(काष्ठा bnx2fc_percpu_s, bnx2fc_percpu);

अटल व्योम bnx2fc_fastpath_notअगरication(काष्ठा bnx2fc_hba *hba,
					काष्ठा fcoe_kcqe *new_cqe_kcqe);
अटल व्योम bnx2fc_process_ofld_cmpl(काष्ठा bnx2fc_hba *hba,
					काष्ठा fcoe_kcqe *ofld_kcqe);
अटल व्योम bnx2fc_process_enable_conn_cmpl(काष्ठा bnx2fc_hba *hba,
						काष्ठा fcoe_kcqe *ofld_kcqe);
अटल व्योम bnx2fc_init_failure(काष्ठा bnx2fc_hba *hba, u32 err_code);
अटल व्योम bnx2fc_process_conn_destroy_cmpl(काष्ठा bnx2fc_hba *hba,
					काष्ठा fcoe_kcqe *destroy_kcqe);

पूर्णांक bnx2fc_send_stat_req(काष्ठा bnx2fc_hba *hba)
अणु
	काष्ठा fcoe_kwqe_stat stat_req;
	काष्ठा kwqe *kwqe_arr[2];
	पूर्णांक num_kwqes = 1;
	पूर्णांक rc = 0;

	स_रखो(&stat_req, 0x00, माप(काष्ठा fcoe_kwqe_stat));
	stat_req.hdr.op_code = FCOE_KWQE_OPCODE_STAT;
	stat_req.hdr.flags =
		(FCOE_KWQE_LAYER_CODE << FCOE_KWQE_HEADER_LAYER_CODE_SHIFT);

	stat_req.stat_params_addr_lo = (u32) hba->stats_buf_dma;
	stat_req.stat_params_addr_hi = (u32) ((u64)hba->stats_buf_dma >> 32);

	kwqe_arr[0] = (काष्ठा kwqe *) &stat_req;

	अगर (hba->cnic && hba->cnic->submit_kwqes)
		rc = hba->cnic->submit_kwqes(hba->cnic, kwqe_arr, num_kwqes);

	वापस rc;
पूर्ण

/**
 * bnx2fc_send_fw_fcoe_init_msg - initiates initial handshake with FCoE f/w
 *
 * @hba:	adapter काष्ठाure poपूर्णांकer
 *
 * Send करोwn FCoE firmware init KWQEs which initiates the initial handshake
 *	with the f/w.
 *
 */
पूर्णांक bnx2fc_send_fw_fcoe_init_msg(काष्ठा bnx2fc_hba *hba)
अणु
	काष्ठा fcoe_kwqe_init1 fcoe_init1;
	काष्ठा fcoe_kwqe_init2 fcoe_init2;
	काष्ठा fcoe_kwqe_init3 fcoe_init3;
	काष्ठा kwqe *kwqe_arr[3];
	पूर्णांक num_kwqes = 3;
	पूर्णांक rc = 0;

	अगर (!hba->cnic) अणु
		prपूर्णांकk(KERN_ERR PFX "hba->cnic NULL during fcoe fw init\n");
		वापस -ENODEV;
	पूर्ण

	/* fill init1 KWQE */
	स_रखो(&fcoe_init1, 0x00, माप(काष्ठा fcoe_kwqe_init1));
	fcoe_init1.hdr.op_code = FCOE_KWQE_OPCODE_INIT1;
	fcoe_init1.hdr.flags = (FCOE_KWQE_LAYER_CODE <<
					FCOE_KWQE_HEADER_LAYER_CODE_SHIFT);

	fcoe_init1.num_tasks = hba->max_tasks;
	fcoe_init1.sq_num_wqes = BNX2FC_SQ_WQES_MAX;
	fcoe_init1.rq_num_wqes = BNX2FC_RQ_WQES_MAX;
	fcoe_init1.rq_buffer_log_size = BNX2FC_RQ_BUF_LOG_SZ;
	fcoe_init1.cq_num_wqes = BNX2FC_CQ_WQES_MAX;
	fcoe_init1.dummy_buffer_addr_lo = (u32) hba->dummy_buf_dma;
	fcoe_init1.dummy_buffer_addr_hi = (u32) ((u64)hba->dummy_buf_dma >> 32);
	fcoe_init1.task_list_pbl_addr_lo = (u32) hba->task_ctx_bd_dma;
	fcoe_init1.task_list_pbl_addr_hi =
				(u32) ((u64) hba->task_ctx_bd_dma >> 32);
	fcoe_init1.mtu = BNX2FC_MINI_JUMBO_MTU;

	fcoe_init1.flags = (PAGE_SHIFT <<
				FCOE_KWQE_INIT1_LOG_PAGE_SIZE_SHIFT);

	fcoe_init1.num_sessions_log = BNX2FC_NUM_MAX_SESS_LOG;

	/* fill init2 KWQE */
	स_रखो(&fcoe_init2, 0x00, माप(काष्ठा fcoe_kwqe_init2));
	fcoe_init2.hdr.op_code = FCOE_KWQE_OPCODE_INIT2;
	fcoe_init2.hdr.flags = (FCOE_KWQE_LAYER_CODE <<
					FCOE_KWQE_HEADER_LAYER_CODE_SHIFT);

	fcoe_init2.hsi_major_version = FCOE_HSI_MAJOR_VERSION;
	fcoe_init2.hsi_minor_version = FCOE_HSI_MINOR_VERSION;


	fcoe_init2.hash_tbl_pbl_addr_lo = (u32) hba->hash_tbl_pbl_dma;
	fcoe_init2.hash_tbl_pbl_addr_hi = (u32)
					   ((u64) hba->hash_tbl_pbl_dma >> 32);

	fcoe_init2.t2_hash_tbl_addr_lo = (u32) hba->t2_hash_tbl_dma;
	fcoe_init2.t2_hash_tbl_addr_hi = (u32)
					  ((u64) hba->t2_hash_tbl_dma >> 32);

	fcoe_init2.t2_ptr_hash_tbl_addr_lo = (u32) hba->t2_hash_tbl_ptr_dma;
	fcoe_init2.t2_ptr_hash_tbl_addr_hi = (u32)
					((u64) hba->t2_hash_tbl_ptr_dma >> 32);

	fcoe_init2.मुक्त_list_count = BNX2FC_NUM_MAX_SESS;

	/* fill init3 KWQE */
	स_रखो(&fcoe_init3, 0x00, माप(काष्ठा fcoe_kwqe_init3));
	fcoe_init3.hdr.op_code = FCOE_KWQE_OPCODE_INIT3;
	fcoe_init3.hdr.flags = (FCOE_KWQE_LAYER_CODE <<
					FCOE_KWQE_HEADER_LAYER_CODE_SHIFT);
	fcoe_init3.error_bit_map_lo = 0xffffffff;
	fcoe_init3.error_bit_map_hi = 0xffffffff;

	/*
	 * enable both cached connection and cached tasks
	 * 0 = none, 1 = cached connection, 2 = cached tasks, 3 = both
	 */
	fcoe_init3.perf_config = 3;

	kwqe_arr[0] = (काष्ठा kwqe *) &fcoe_init1;
	kwqe_arr[1] = (काष्ठा kwqe *) &fcoe_init2;
	kwqe_arr[2] = (काष्ठा kwqe *) &fcoe_init3;

	अगर (hba->cnic && hba->cnic->submit_kwqes)
		rc = hba->cnic->submit_kwqes(hba->cnic, kwqe_arr, num_kwqes);

	वापस rc;
पूर्ण
पूर्णांक bnx2fc_send_fw_fcoe_destroy_msg(काष्ठा bnx2fc_hba *hba)
अणु
	काष्ठा fcoe_kwqe_destroy fcoe_destroy;
	काष्ठा kwqe *kwqe_arr[2];
	पूर्णांक num_kwqes = 1;
	पूर्णांक rc = -1;

	/* fill destroy KWQE */
	स_रखो(&fcoe_destroy, 0x00, माप(काष्ठा fcoe_kwqe_destroy));
	fcoe_destroy.hdr.op_code = FCOE_KWQE_OPCODE_DESTROY;
	fcoe_destroy.hdr.flags = (FCOE_KWQE_LAYER_CODE <<
					FCOE_KWQE_HEADER_LAYER_CODE_SHIFT);
	kwqe_arr[0] = (काष्ठा kwqe *) &fcoe_destroy;

	अगर (hba->cnic && hba->cnic->submit_kwqes)
		rc = hba->cnic->submit_kwqes(hba->cnic, kwqe_arr, num_kwqes);
	वापस rc;
पूर्ण

/**
 * bnx2fc_send_session_ofld_req - initiates FCoE Session offload process
 *
 * @port:		port काष्ठाure poपूर्णांकer
 * @tgt:		bnx2fc_rport काष्ठाure poपूर्णांकer
 */
पूर्णांक bnx2fc_send_session_ofld_req(काष्ठा fcoe_port *port,
					काष्ठा bnx2fc_rport *tgt)
अणु
	काष्ठा fc_lport *lport = port->lport;
	काष्ठा bnx2fc_पूर्णांकerface *पूर्णांकerface = port->priv;
	काष्ठा fcoe_ctlr *ctlr = bnx2fc_to_ctlr(पूर्णांकerface);
	काष्ठा bnx2fc_hba *hba = पूर्णांकerface->hba;
	काष्ठा kwqe *kwqe_arr[4];
	काष्ठा fcoe_kwqe_conn_offload1 ofld_req1;
	काष्ठा fcoe_kwqe_conn_offload2 ofld_req2;
	काष्ठा fcoe_kwqe_conn_offload3 ofld_req3;
	काष्ठा fcoe_kwqe_conn_offload4 ofld_req4;
	काष्ठा fc_rport_priv *rdata = tgt->rdata;
	काष्ठा fc_rport *rport = tgt->rport;
	पूर्णांक num_kwqes = 4;
	u32 port_id;
	पूर्णांक rc = 0;
	u16 conn_id;

	/* Initialize offload request 1 काष्ठाure */
	स_रखो(&ofld_req1, 0x00, माप(काष्ठा fcoe_kwqe_conn_offload1));

	ofld_req1.hdr.op_code = FCOE_KWQE_OPCODE_OFFLOAD_CONN1;
	ofld_req1.hdr.flags =
		(FCOE_KWQE_LAYER_CODE << FCOE_KWQE_HEADER_LAYER_CODE_SHIFT);


	conn_id = (u16)tgt->fcoe_conn_id;
	ofld_req1.fcoe_conn_id = conn_id;


	ofld_req1.sq_addr_lo = (u32) tgt->sq_dma;
	ofld_req1.sq_addr_hi = (u32)((u64) tgt->sq_dma >> 32);

	ofld_req1.rq_pbl_addr_lo = (u32) tgt->rq_pbl_dma;
	ofld_req1.rq_pbl_addr_hi = (u32)((u64) tgt->rq_pbl_dma >> 32);

	ofld_req1.rq_first_pbe_addr_lo = (u32) tgt->rq_dma;
	ofld_req1.rq_first_pbe_addr_hi =
				(u32)((u64) tgt->rq_dma >> 32);

	ofld_req1.rq_prod = 0x8000;

	/* Initialize offload request 2 काष्ठाure */
	स_रखो(&ofld_req2, 0x00, माप(काष्ठा fcoe_kwqe_conn_offload2));

	ofld_req2.hdr.op_code = FCOE_KWQE_OPCODE_OFFLOAD_CONN2;
	ofld_req2.hdr.flags =
		(FCOE_KWQE_LAYER_CODE << FCOE_KWQE_HEADER_LAYER_CODE_SHIFT);

	ofld_req2.tx_max_fc_pay_len = rdata->maxframe_size;

	ofld_req2.cq_addr_lo = (u32) tgt->cq_dma;
	ofld_req2.cq_addr_hi = (u32)((u64)tgt->cq_dma >> 32);

	ofld_req2.xferq_addr_lo = (u32) tgt->xferq_dma;
	ofld_req2.xferq_addr_hi = (u32)((u64)tgt->xferq_dma >> 32);

	ofld_req2.conn_db_addr_lo = (u32)tgt->conn_db_dma;
	ofld_req2.conn_db_addr_hi = (u32)((u64)tgt->conn_db_dma >> 32);

	/* Initialize offload request 3 काष्ठाure */
	स_रखो(&ofld_req3, 0x00, माप(काष्ठा fcoe_kwqe_conn_offload3));

	ofld_req3.hdr.op_code = FCOE_KWQE_OPCODE_OFFLOAD_CONN3;
	ofld_req3.hdr.flags =
		(FCOE_KWQE_LAYER_CODE << FCOE_KWQE_HEADER_LAYER_CODE_SHIFT);

	ofld_req3.vlan_tag = पूर्णांकerface->vlan_id <<
				FCOE_KWQE_CONN_OFFLOAD3_VLAN_ID_SHIFT;
	ofld_req3.vlan_tag |= 3 << FCOE_KWQE_CONN_OFFLOAD3_PRIORITY_SHIFT;

	port_id = fc_host_port_id(lport->host);
	अगर (port_id == 0) अणु
		BNX2FC_HBA_DBG(lport, "ofld_req: port_id = 0, link down?\n");
		वापस -EINVAL;
	पूर्ण

	/*
	 * Store s_id of the initiator क्रम further reference. This will
	 * be used during disable/destroy during linkकरोwn processing as
	 * when the lport is reset, the port_id also is reset to 0
	 */
	tgt->sid = port_id;
	ofld_req3.s_id[0] = (port_id & 0x000000FF);
	ofld_req3.s_id[1] = (port_id & 0x0000FF00) >> 8;
	ofld_req3.s_id[2] = (port_id & 0x00FF0000) >> 16;

	port_id = rport->port_id;
	ofld_req3.d_id[0] = (port_id & 0x000000FF);
	ofld_req3.d_id[1] = (port_id & 0x0000FF00) >> 8;
	ofld_req3.d_id[2] = (port_id & 0x00FF0000) >> 16;

	ofld_req3.tx_total_conc_seqs = rdata->max_seq;

	ofld_req3.tx_max_conc_seqs_c3 = rdata->max_seq;
	ofld_req3.rx_max_fc_pay_len  = lport->mfs;

	ofld_req3.rx_total_conc_seqs = BNX2FC_MAX_SEQS;
	ofld_req3.rx_max_conc_seqs_c3 = BNX2FC_MAX_SEQS;
	ofld_req3.rx_खोलो_seqs_exch_c3 = 1;

	ofld_req3.confq_first_pbe_addr_lo = tgt->confq_dma;
	ofld_req3.confq_first_pbe_addr_hi = (u32)((u64) tgt->confq_dma >> 32);

	/* set mul_n_port_ids supported flag to 0, until it is supported */
	ofld_req3.flags = 0;
	/*
	ofld_req3.flags |= (((lport->send_sp_features & FC_SP_FT_MNA) ? 1:0) <<
			    FCOE_KWQE_CONN_OFFLOAD3_B_MUL_N_PORT_IDS_SHIFT);
	*/
	/* Info from PLOGI response */
	ofld_req3.flags |= (((rdata->sp_features & FC_SP_FT_EDTR) ? 1 : 0) <<
			     FCOE_KWQE_CONN_OFFLOAD3_B_E_D_TOV_RES_SHIFT);

	ofld_req3.flags |= (((rdata->sp_features & FC_SP_FT_SEQC) ? 1 : 0) <<
			     FCOE_KWQE_CONN_OFFLOAD3_B_CONT_INCR_SEQ_CNT_SHIFT);

	/*
	 * Info from PRLI response, this info is used क्रम sequence level error
	 * recovery support
	 */
	अगर (tgt->dev_type == TYPE_TAPE) अणु
		ofld_req3.flags |= 1 <<
				    FCOE_KWQE_CONN_OFFLOAD3_B_CONF_REQ_SHIFT;
		ofld_req3.flags |= (((rdata->flags & FC_RP_FLAGS_REC_SUPPORTED)
				    ? 1 : 0) <<
				    FCOE_KWQE_CONN_OFFLOAD3_B_REC_VALID_SHIFT);
	पूर्ण

	/* vlan flag */
	ofld_req3.flags |= (पूर्णांकerface->vlan_enabled <<
			    FCOE_KWQE_CONN_OFFLOAD3_B_VLAN_FLAG_SHIFT);

	/* C2_VALID and ACK flags are not set as they are not supported */


	/* Initialize offload request 4 काष्ठाure */
	स_रखो(&ofld_req4, 0x00, माप(काष्ठा fcoe_kwqe_conn_offload4));
	ofld_req4.hdr.op_code = FCOE_KWQE_OPCODE_OFFLOAD_CONN4;
	ofld_req4.hdr.flags =
		(FCOE_KWQE_LAYER_CODE << FCOE_KWQE_HEADER_LAYER_CODE_SHIFT);

	ofld_req4.e_d_tov_समयr_val = lport->e_d_tov / 20;


	ofld_req4.src_mac_addr_lo[0] =  port->data_src_addr[5];
							/* local mac */
	ofld_req4.src_mac_addr_lo[1] =  port->data_src_addr[4];
	ofld_req4.src_mac_addr_mid[0] =  port->data_src_addr[3];
	ofld_req4.src_mac_addr_mid[1] =  port->data_src_addr[2];
	ofld_req4.src_mac_addr_hi[0] =  port->data_src_addr[1];
	ofld_req4.src_mac_addr_hi[1] =  port->data_src_addr[0];
	ofld_req4.dst_mac_addr_lo[0] =  ctlr->dest_addr[5];
							/* fcf mac */
	ofld_req4.dst_mac_addr_lo[1] = ctlr->dest_addr[4];
	ofld_req4.dst_mac_addr_mid[0] = ctlr->dest_addr[3];
	ofld_req4.dst_mac_addr_mid[1] = ctlr->dest_addr[2];
	ofld_req4.dst_mac_addr_hi[0] = ctlr->dest_addr[1];
	ofld_req4.dst_mac_addr_hi[1] = ctlr->dest_addr[0];

	ofld_req4.lcq_addr_lo = (u32) tgt->lcq_dma;
	ofld_req4.lcq_addr_hi = (u32)((u64) tgt->lcq_dma >> 32);

	ofld_req4.confq_pbl_base_addr_lo = (u32) tgt->confq_pbl_dma;
	ofld_req4.confq_pbl_base_addr_hi =
					(u32)((u64) tgt->confq_pbl_dma >> 32);

	kwqe_arr[0] = (काष्ठा kwqe *) &ofld_req1;
	kwqe_arr[1] = (काष्ठा kwqe *) &ofld_req2;
	kwqe_arr[2] = (काष्ठा kwqe *) &ofld_req3;
	kwqe_arr[3] = (काष्ठा kwqe *) &ofld_req4;

	अगर (hba->cnic && hba->cnic->submit_kwqes)
		rc = hba->cnic->submit_kwqes(hba->cnic, kwqe_arr, num_kwqes);

	वापस rc;
पूर्ण

/**
 * bnx2fc_send_session_enable_req - initiates FCoE Session enablement
 *
 * @port:		port काष्ठाure poपूर्णांकer
 * @tgt:		bnx2fc_rport काष्ठाure poपूर्णांकer
 */
पूर्णांक bnx2fc_send_session_enable_req(काष्ठा fcoe_port *port,
					काष्ठा bnx2fc_rport *tgt)
अणु
	काष्ठा kwqe *kwqe_arr[2];
	काष्ठा bnx2fc_पूर्णांकerface *पूर्णांकerface = port->priv;
	काष्ठा fcoe_ctlr *ctlr = bnx2fc_to_ctlr(पूर्णांकerface);
	काष्ठा bnx2fc_hba *hba = पूर्णांकerface->hba;
	काष्ठा fcoe_kwqe_conn_enable_disable enbl_req;
	काष्ठा fc_lport *lport = port->lport;
	काष्ठा fc_rport *rport = tgt->rport;
	पूर्णांक num_kwqes = 1;
	पूर्णांक rc = 0;
	u32 port_id;

	स_रखो(&enbl_req, 0x00,
	       माप(काष्ठा fcoe_kwqe_conn_enable_disable));
	enbl_req.hdr.op_code = FCOE_KWQE_OPCODE_ENABLE_CONN;
	enbl_req.hdr.flags =
		(FCOE_KWQE_LAYER_CODE << FCOE_KWQE_HEADER_LAYER_CODE_SHIFT);

	enbl_req.src_mac_addr_lo[0] =  port->data_src_addr[5];
							/* local mac */
	enbl_req.src_mac_addr_lo[1] =  port->data_src_addr[4];
	enbl_req.src_mac_addr_mid[0] =  port->data_src_addr[3];
	enbl_req.src_mac_addr_mid[1] =  port->data_src_addr[2];
	enbl_req.src_mac_addr_hi[0] =  port->data_src_addr[1];
	enbl_req.src_mac_addr_hi[1] =  port->data_src_addr[0];
	स_नकल(tgt->src_addr, port->data_src_addr, ETH_ALEN);

	enbl_req.dst_mac_addr_lo[0] =  ctlr->dest_addr[5];
	enbl_req.dst_mac_addr_lo[1] =  ctlr->dest_addr[4];
	enbl_req.dst_mac_addr_mid[0] = ctlr->dest_addr[3];
	enbl_req.dst_mac_addr_mid[1] = ctlr->dest_addr[2];
	enbl_req.dst_mac_addr_hi[0] = ctlr->dest_addr[1];
	enbl_req.dst_mac_addr_hi[1] = ctlr->dest_addr[0];

	port_id = fc_host_port_id(lport->host);
	अगर (port_id != tgt->sid) अणु
		prपूर्णांकk(KERN_ERR PFX "WARN: enable_req port_id = 0x%x,"
				"sid = 0x%x\n", port_id, tgt->sid);
		port_id = tgt->sid;
	पूर्ण
	enbl_req.s_id[0] = (port_id & 0x000000FF);
	enbl_req.s_id[1] = (port_id & 0x0000FF00) >> 8;
	enbl_req.s_id[2] = (port_id & 0x00FF0000) >> 16;

	port_id = rport->port_id;
	enbl_req.d_id[0] = (port_id & 0x000000FF);
	enbl_req.d_id[1] = (port_id & 0x0000FF00) >> 8;
	enbl_req.d_id[2] = (port_id & 0x00FF0000) >> 16;
	enbl_req.vlan_tag = पूर्णांकerface->vlan_id <<
				FCOE_KWQE_CONN_ENABLE_DISABLE_VLAN_ID_SHIFT;
	enbl_req.vlan_tag |= 3 << FCOE_KWQE_CONN_ENABLE_DISABLE_PRIORITY_SHIFT;
	enbl_req.vlan_flag = पूर्णांकerface->vlan_enabled;
	enbl_req.context_id = tgt->context_id;
	enbl_req.conn_id = tgt->fcoe_conn_id;

	kwqe_arr[0] = (काष्ठा kwqe *) &enbl_req;

	अगर (hba->cnic && hba->cnic->submit_kwqes)
		rc = hba->cnic->submit_kwqes(hba->cnic, kwqe_arr, num_kwqes);
	वापस rc;
पूर्ण

/**
 * bnx2fc_send_session_disable_req - initiates FCoE Session disable
 *
 * @port:		port काष्ठाure poपूर्णांकer
 * @tgt:		bnx2fc_rport काष्ठाure poपूर्णांकer
 */
पूर्णांक bnx2fc_send_session_disable_req(काष्ठा fcoe_port *port,
				    काष्ठा bnx2fc_rport *tgt)
अणु
	काष्ठा bnx2fc_पूर्णांकerface *पूर्णांकerface = port->priv;
	काष्ठा fcoe_ctlr *ctlr = bnx2fc_to_ctlr(पूर्णांकerface);
	काष्ठा bnx2fc_hba *hba = पूर्णांकerface->hba;
	काष्ठा fcoe_kwqe_conn_enable_disable disable_req;
	काष्ठा kwqe *kwqe_arr[2];
	काष्ठा fc_rport *rport = tgt->rport;
	पूर्णांक num_kwqes = 1;
	पूर्णांक rc = 0;
	u32 port_id;

	स_रखो(&disable_req, 0x00,
	       माप(काष्ठा fcoe_kwqe_conn_enable_disable));
	disable_req.hdr.op_code = FCOE_KWQE_OPCODE_DISABLE_CONN;
	disable_req.hdr.flags =
		(FCOE_KWQE_LAYER_CODE << FCOE_KWQE_HEADER_LAYER_CODE_SHIFT);

	disable_req.src_mac_addr_lo[0] =  tgt->src_addr[5];
	disable_req.src_mac_addr_lo[1] =  tgt->src_addr[4];
	disable_req.src_mac_addr_mid[0] =  tgt->src_addr[3];
	disable_req.src_mac_addr_mid[1] =  tgt->src_addr[2];
	disable_req.src_mac_addr_hi[0] =  tgt->src_addr[1];
	disable_req.src_mac_addr_hi[1] =  tgt->src_addr[0];

	disable_req.dst_mac_addr_lo[0] =  ctlr->dest_addr[5];
	disable_req.dst_mac_addr_lo[1] =  ctlr->dest_addr[4];
	disable_req.dst_mac_addr_mid[0] = ctlr->dest_addr[3];
	disable_req.dst_mac_addr_mid[1] = ctlr->dest_addr[2];
	disable_req.dst_mac_addr_hi[0] = ctlr->dest_addr[1];
	disable_req.dst_mac_addr_hi[1] = ctlr->dest_addr[0];

	port_id = tgt->sid;
	disable_req.s_id[0] = (port_id & 0x000000FF);
	disable_req.s_id[1] = (port_id & 0x0000FF00) >> 8;
	disable_req.s_id[2] = (port_id & 0x00FF0000) >> 16;


	port_id = rport->port_id;
	disable_req.d_id[0] = (port_id & 0x000000FF);
	disable_req.d_id[1] = (port_id & 0x0000FF00) >> 8;
	disable_req.d_id[2] = (port_id & 0x00FF0000) >> 16;
	disable_req.context_id = tgt->context_id;
	disable_req.conn_id = tgt->fcoe_conn_id;
	disable_req.vlan_tag = पूर्णांकerface->vlan_id <<
				FCOE_KWQE_CONN_ENABLE_DISABLE_VLAN_ID_SHIFT;
	disable_req.vlan_tag |=
			3 << FCOE_KWQE_CONN_ENABLE_DISABLE_PRIORITY_SHIFT;
	disable_req.vlan_flag = पूर्णांकerface->vlan_enabled;

	kwqe_arr[0] = (काष्ठा kwqe *) &disable_req;

	अगर (hba->cnic && hba->cnic->submit_kwqes)
		rc = hba->cnic->submit_kwqes(hba->cnic, kwqe_arr, num_kwqes);

	वापस rc;
पूर्ण

/**
 * bnx2fc_send_session_destroy_req - initiates FCoE Session destroy
 *
 * @hba:		adapter काष्ठाure poपूर्णांकer
 * @tgt:		bnx2fc_rport काष्ठाure poपूर्णांकer
 */
पूर्णांक bnx2fc_send_session_destroy_req(काष्ठा bnx2fc_hba *hba,
					काष्ठा bnx2fc_rport *tgt)
अणु
	काष्ठा fcoe_kwqe_conn_destroy destroy_req;
	काष्ठा kwqe *kwqe_arr[2];
	पूर्णांक num_kwqes = 1;
	पूर्णांक rc = 0;

	स_रखो(&destroy_req, 0x00, माप(काष्ठा fcoe_kwqe_conn_destroy));
	destroy_req.hdr.op_code = FCOE_KWQE_OPCODE_DESTROY_CONN;
	destroy_req.hdr.flags =
		(FCOE_KWQE_LAYER_CODE << FCOE_KWQE_HEADER_LAYER_CODE_SHIFT);

	destroy_req.context_id = tgt->context_id;
	destroy_req.conn_id = tgt->fcoe_conn_id;

	kwqe_arr[0] = (काष्ठा kwqe *) &destroy_req;

	अगर (hba->cnic && hba->cnic->submit_kwqes)
		rc = hba->cnic->submit_kwqes(hba->cnic, kwqe_arr, num_kwqes);

	वापस rc;
पूर्ण

अटल bool is_valid_lport(काष्ठा bnx2fc_hba *hba, काष्ठा fc_lport *lport)
अणु
	काष्ठा bnx2fc_lport *blport;

	spin_lock_bh(&hba->hba_lock);
	list_क्रम_each_entry(blport, &hba->vports, list) अणु
		अगर (blport->lport == lport) अणु
			spin_unlock_bh(&hba->hba_lock);
			वापस true;
		पूर्ण
	पूर्ण
	spin_unlock_bh(&hba->hba_lock);
	वापस false;

पूर्ण


अटल व्योम bnx2fc_unsol_els_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा bnx2fc_unsol_els *unsol_els;
	काष्ठा fc_lport *lport;
	काष्ठा bnx2fc_hba *hba;
	काष्ठा fc_frame *fp;

	unsol_els = container_of(work, काष्ठा bnx2fc_unsol_els, unsol_els_work);
	lport = unsol_els->lport;
	fp = unsol_els->fp;
	hba = unsol_els->hba;
	अगर (is_valid_lport(hba, lport))
		fc_exch_recv(lport, fp);
	kमुक्त(unsol_els);
पूर्ण

व्योम bnx2fc_process_l2_frame_compl(काष्ठा bnx2fc_rport *tgt,
				   अचिन्हित अक्षर *buf,
				   u32 frame_len, u16 l2_oxid)
अणु
	काष्ठा fcoe_port *port = tgt->port;
	काष्ठा fc_lport *lport = port->lport;
	काष्ठा bnx2fc_पूर्णांकerface *पूर्णांकerface = port->priv;
	काष्ठा bnx2fc_unsol_els *unsol_els;
	काष्ठा fc_frame_header *fh;
	काष्ठा fc_frame *fp;
	काष्ठा sk_buff *skb;
	u32 payload_len;
	u32 crc;
	u8 op;


	unsol_els = kzalloc(माप(*unsol_els), GFP_ATOMIC);
	अगर (!unsol_els) अणु
		BNX2FC_TGT_DBG(tgt, "Unable to allocate unsol_work\n");
		वापस;
	पूर्ण

	BNX2FC_TGT_DBG(tgt, "l2_frame_compl l2_oxid = 0x%x, frame_len = %d\n",
		l2_oxid, frame_len);

	payload_len = frame_len - माप(काष्ठा fc_frame_header);

	fp = fc_frame_alloc(lport, payload_len);
	अगर (!fp) अणु
		prपूर्णांकk(KERN_ERR PFX "fc_frame_alloc failure\n");
		kमुक्त(unsol_els);
		वापस;
	पूर्ण

	fh = (काष्ठा fc_frame_header *) fc_frame_header_get(fp);
	/* Copy FC Frame header and payload पूर्णांकo the frame */
	स_नकल(fh, buf, frame_len);

	अगर (l2_oxid != FC_XID_UNKNOWN)
		fh->fh_ox_id = htons(l2_oxid);

	skb = fp_skb(fp);

	अगर ((fh->fh_r_ctl == FC_RCTL_ELS_REQ) ||
	    (fh->fh_r_ctl == FC_RCTL_ELS_REP)) अणु

		अगर (fh->fh_type == FC_TYPE_ELS) अणु
			op = fc_frame_payload_op(fp);
			अगर ((op == ELS_TEST) ||	(op == ELS_ESTC) ||
			    (op == ELS_FAN) || (op == ELS_CSU)) अणु
				/*
				 * No need to reply क्रम these
				 * ELS requests
				 */
				prपूर्णांकk(KERN_ERR PFX "dropping ELS 0x%x\n", op);
				kमुक्त_skb(skb);
				kमुक्त(unsol_els);
				वापस;
			पूर्ण
		पूर्ण
		crc = fcoe_fc_crc(fp);
		fc_frame_init(fp);
		fr_dev(fp) = lport;
		fr_sof(fp) = FC_SOF_I3;
		fr_eof(fp) = FC_खातापूर्ण_T;
		fr_crc(fp) = cpu_to_le32(~crc);
		unsol_els->lport = lport;
		unsol_els->hba = पूर्णांकerface->hba;
		unsol_els->fp = fp;
		INIT_WORK(&unsol_els->unsol_els_work, bnx2fc_unsol_els_work);
		queue_work(bnx2fc_wq, &unsol_els->unsol_els_work);
	पूर्ण अन्यथा अणु
		BNX2FC_HBA_DBG(lport, "fh_r_ctl = 0x%x\n", fh->fh_r_ctl);
		kमुक्त_skb(skb);
		kमुक्त(unsol_els);
	पूर्ण
पूर्ण

अटल व्योम bnx2fc_process_unsol_compl(काष्ठा bnx2fc_rport *tgt, u16 wqe)
अणु
	u8 num_rq;
	काष्ठा fcoe_err_report_entry *err_entry;
	अचिन्हित अक्षर *rq_data;
	अचिन्हित अक्षर *buf = शून्य, *buf1;
	पूर्णांक i;
	u16 xid;
	u32 frame_len, len;
	काष्ठा bnx2fc_cmd *io_req = शून्य;
	काष्ठा bnx2fc_पूर्णांकerface *पूर्णांकerface = tgt->port->priv;
	काष्ठा bnx2fc_hba *hba = पूर्णांकerface->hba;
	पूर्णांक rc = 0;
	u64 err_warn_bit_map;
	u8 err_warn = 0xff;


	BNX2FC_TGT_DBG(tgt, "Entered UNSOL COMPLETION wqe = 0x%x\n", wqe);
	चयन (wqe & FCOE_UNSOLICITED_CQE_SUBTYPE) अणु
	हाल FCOE_UNSOLICITED_FRAME_CQE_TYPE:
		frame_len = (wqe & FCOE_UNSOLICITED_CQE_PKT_LEN) >>
			     FCOE_UNSOLICITED_CQE_PKT_LEN_SHIFT;

		num_rq = (frame_len + BNX2FC_RQ_BUF_SZ - 1) / BNX2FC_RQ_BUF_SZ;

		spin_lock_bh(&tgt->tgt_lock);
		rq_data = (अचिन्हित अक्षर *)bnx2fc_get_next_rqe(tgt, num_rq);
		spin_unlock_bh(&tgt->tgt_lock);

		अगर (rq_data) अणु
			buf = rq_data;
		पूर्ण अन्यथा अणु
			buf1 = buf = kदो_स्मृति((num_rq * BNX2FC_RQ_BUF_SZ),
					      GFP_ATOMIC);

			अगर (!buf1) अणु
				BNX2FC_TGT_DBG(tgt, "Memory alloc failure\n");
				अवरोध;
			पूर्ण

			क्रम (i = 0; i < num_rq; i++) अणु
				spin_lock_bh(&tgt->tgt_lock);
				rq_data = (अचिन्हित अक्षर *)
					   bnx2fc_get_next_rqe(tgt, 1);
				spin_unlock_bh(&tgt->tgt_lock);
				len = BNX2FC_RQ_BUF_SZ;
				स_नकल(buf1, rq_data, len);
				buf1 += len;
			पूर्ण
		पूर्ण
		bnx2fc_process_l2_frame_compl(tgt, buf, frame_len,
					      FC_XID_UNKNOWN);

		अगर (buf != rq_data)
			kमुक्त(buf);
		spin_lock_bh(&tgt->tgt_lock);
		bnx2fc_वापस_rqe(tgt, num_rq);
		spin_unlock_bh(&tgt->tgt_lock);
		अवरोध;

	हाल FCOE_ERROR_DETECTION_CQE_TYPE:
		/*
		 * In हाल of error reporting CQE a single RQ entry
		 * is consumed.
		 */
		spin_lock_bh(&tgt->tgt_lock);
		num_rq = 1;
		err_entry = (काष्ठा fcoe_err_report_entry *)
			     bnx2fc_get_next_rqe(tgt, 1);
		xid = err_entry->fc_hdr.ox_id;
		BNX2FC_TGT_DBG(tgt, "Unsol Error Frame OX_ID = 0x%x\n", xid);
		BNX2FC_TGT_DBG(tgt, "err_warn_bitmap = %08x:%08x\n",
			err_entry->data.err_warn_biपंचांगap_hi,
			err_entry->data.err_warn_biपंचांगap_lo);
		BNX2FC_TGT_DBG(tgt, "buf_offsets - tx = 0x%x, rx = 0x%x\n",
			err_entry->data.tx_buf_off, err_entry->data.rx_buf_off);

		अगर (xid > hba->max_xid) अणु
			BNX2FC_TGT_DBG(tgt, "xid(0x%x) out of FW range\n",
				   xid);
			जाओ ret_err_rqe;
		पूर्ण


		io_req = (काष्ठा bnx2fc_cmd *)hba->cmd_mgr->cmds[xid];
		अगर (!io_req)
			जाओ ret_err_rqe;

		अगर (io_req->cmd_type != BNX2FC_SCSI_CMD) अणु
			prपूर्णांकk(KERN_ERR PFX "err_warn: Not a SCSI cmd\n");
			जाओ ret_err_rqe;
		पूर्ण

		अगर (test_and_clear_bit(BNX2FC_FLAG_IO_CLEANUP,
				       &io_req->req_flags)) अणु
			BNX2FC_IO_DBG(io_req, "unsol_err: cleanup in "
					    "progress.. ignore unsol err\n");
			जाओ ret_err_rqe;
		पूर्ण

		err_warn_bit_map = (u64)
			((u64)err_entry->data.err_warn_biपंचांगap_hi << 32) |
			(u64)err_entry->data.err_warn_biपंचांगap_lo;
		क्रम (i = 0; i < BNX2FC_NUM_ERR_BITS; i++) अणु
			अगर (err_warn_bit_map & (u64)((u64)1 << i)) अणु
				err_warn = i;
				अवरोध;
			पूर्ण
		पूर्ण

		/*
		 * If ABTS is alपढ़ोy in progress, and FW error is
		 * received after that, करो not cancel the समयout_work
		 * and let the error recovery जारी by explicitly
		 * logging out the target, when the ABTS eventually
		 * बार out.
		 */
		अगर (test_bit(BNX2FC_FLAG_ISSUE_ABTS, &io_req->req_flags)) अणु
			prपूर्णांकk(KERN_ERR PFX "err_warn: io_req (0x%x) already "
					    "in ABTS processing\n", xid);
			जाओ ret_err_rqe;
		पूर्ण
		BNX2FC_TGT_DBG(tgt, "err = 0x%x\n", err_warn);
		अगर (tgt->dev_type != TYPE_TAPE)
			जाओ skip_rec;
		चयन (err_warn) अणु
		हाल FCOE_ERROR_CODE_REC_TOV_TIMER_EXPIRATION:
		हाल FCOE_ERROR_CODE_DATA_OOO_RO:
		हाल FCOE_ERROR_CODE_COMMON_INCORRECT_SEQ_CNT:
		हाल FCOE_ERROR_CODE_DATA_SOFI3_SEQ_ACTIVE_SET:
		हाल FCOE_ERROR_CODE_FCP_RSP_OPENED_SEQ:
		हाल FCOE_ERROR_CODE_DATA_SOFN_SEQ_ACTIVE_RESET:
			BNX2FC_TGT_DBG(tgt, "REC TOV popped for xid - 0x%x\n",
				   xid);
			स_नकल(&io_req->err_entry, err_entry,
			       माप(काष्ठा fcoe_err_report_entry));
			अगर (!test_bit(BNX2FC_FLAG_SRR_SENT,
				      &io_req->req_flags)) अणु
				spin_unlock_bh(&tgt->tgt_lock);
				rc = bnx2fc_send_rec(io_req);
				spin_lock_bh(&tgt->tgt_lock);

				अगर (rc)
					जाओ skip_rec;
			पूर्ण अन्यथा
				prपूर्णांकk(KERN_ERR PFX "SRR in progress\n");
			जाओ ret_err_rqe;
		शेष:
			अवरोध;
		पूर्ण

skip_rec:
		set_bit(BNX2FC_FLAG_ISSUE_ABTS, &io_req->req_flags);
		/*
		 * Cancel the समयout_work, as we received IO
		 * completion with FW error.
		 */
		अगर (cancel_delayed_work(&io_req->समयout_work))
			kref_put(&io_req->refcount, bnx2fc_cmd_release);

		rc = bnx2fc_initiate_abts(io_req);
		अगर (rc != SUCCESS) अणु
			prपूर्णांकk(KERN_ERR PFX "err_warn: initiate_abts "
				"failed xid = 0x%x. issue cleanup\n",
				io_req->xid);
			bnx2fc_initiate_cleanup(io_req);
		पूर्ण
ret_err_rqe:
		bnx2fc_वापस_rqe(tgt, 1);
		spin_unlock_bh(&tgt->tgt_lock);
		अवरोध;

	हाल FCOE_WARNING_DETECTION_CQE_TYPE:
		/*
		 *In हाल of warning reporting CQE a single RQ entry
		 * is consumes.
		 */
		spin_lock_bh(&tgt->tgt_lock);
		num_rq = 1;
		err_entry = (काष्ठा fcoe_err_report_entry *)
			     bnx2fc_get_next_rqe(tgt, 1);
		xid = cpu_to_be16(err_entry->fc_hdr.ox_id);
		BNX2FC_TGT_DBG(tgt, "Unsol Warning Frame OX_ID = 0x%x\n", xid);
		BNX2FC_TGT_DBG(tgt, "err_warn_bitmap = %08x:%08x",
			err_entry->data.err_warn_biपंचांगap_hi,
			err_entry->data.err_warn_biपंचांगap_lo);
		BNX2FC_TGT_DBG(tgt, "buf_offsets - tx = 0x%x, rx = 0x%x",
			err_entry->data.tx_buf_off, err_entry->data.rx_buf_off);

		अगर (xid > hba->max_xid) अणु
			BNX2FC_TGT_DBG(tgt, "xid(0x%x) out of FW range\n", xid);
			जाओ ret_warn_rqe;
		पूर्ण

		err_warn_bit_map = (u64)
			((u64)err_entry->data.err_warn_biपंचांगap_hi << 32) |
			(u64)err_entry->data.err_warn_biपंचांगap_lo;
		क्रम (i = 0; i < BNX2FC_NUM_ERR_BITS; i++) अणु
			अगर (err_warn_bit_map & ((u64)1 << i)) अणु
				err_warn = i;
				अवरोध;
			पूर्ण
		पूर्ण
		BNX2FC_TGT_DBG(tgt, "warn = 0x%x\n", err_warn);

		io_req = (काष्ठा bnx2fc_cmd *)hba->cmd_mgr->cmds[xid];
		अगर (!io_req)
			जाओ ret_warn_rqe;

		अगर (io_req->cmd_type != BNX2FC_SCSI_CMD) अणु
			prपूर्णांकk(KERN_ERR PFX "err_warn: Not a SCSI cmd\n");
			जाओ ret_warn_rqe;
		पूर्ण

		स_नकल(&io_req->err_entry, err_entry,
		       माप(काष्ठा fcoe_err_report_entry));

		अगर (err_warn == FCOE_ERROR_CODE_REC_TOV_TIMER_EXPIRATION)
			/* REC_TOV is not a warning code */
			BUG_ON(1);
		अन्यथा
			BNX2FC_TGT_DBG(tgt, "Unsolicited warning\n");
ret_warn_rqe:
		bnx2fc_वापस_rqe(tgt, 1);
		spin_unlock_bh(&tgt->tgt_lock);
		अवरोध;

	शेष:
		prपूर्णांकk(KERN_ERR PFX "Unsol Compl: Invalid CQE Subtype\n");
		अवरोध;
	पूर्ण
पूर्ण

व्योम bnx2fc_process_cq_compl(काष्ठा bnx2fc_rport *tgt, u16 wqe,
			     अचिन्हित अक्षर *rq_data, u8 num_rq,
			     काष्ठा fcoe_task_ctx_entry *task)
अणु
	काष्ठा fcoe_port *port = tgt->port;
	काष्ठा bnx2fc_पूर्णांकerface *पूर्णांकerface = port->priv;
	काष्ठा bnx2fc_hba *hba = पूर्णांकerface->hba;
	काष्ठा bnx2fc_cmd *io_req;

	u16 xid;
	u8  cmd_type;
	u8 rx_state = 0;

	spin_lock_bh(&tgt->tgt_lock);

	xid = wqe & FCOE_PEND_WQ_CQE_TASK_ID;
	io_req = (काष्ठा bnx2fc_cmd *)hba->cmd_mgr->cmds[xid];

	अगर (io_req == शून्य) अणु
		prपूर्णांकk(KERN_ERR PFX "ERROR? cq_compl - io_req is NULL\n");
		spin_unlock_bh(&tgt->tgt_lock);
		वापस;
	पूर्ण

	/* Timestamp IO completion समय */
	cmd_type = io_req->cmd_type;

	rx_state = ((task->rxwr_txrd.var_ctx.rx_flags &
		    FCOE_TCE_RX_WR_TX_RD_VAR_RX_STATE) >>
		    FCOE_TCE_RX_WR_TX_RD_VAR_RX_STATE_SHIFT);

	/* Process other IO completion types */
	चयन (cmd_type) अणु
	हाल BNX2FC_SCSI_CMD:
		अगर (rx_state == FCOE_TASK_RX_STATE_COMPLETED) अणु
			bnx2fc_process_scsi_cmd_compl(io_req, task, num_rq,
						      rq_data);
			spin_unlock_bh(&tgt->tgt_lock);
			वापस;
		पूर्ण

		अगर (rx_state == FCOE_TASK_RX_STATE_ABTS_COMPLETED)
			bnx2fc_process_abts_compl(io_req, task, num_rq);
		अन्यथा अगर (rx_state ==
			 FCOE_TASK_RX_STATE_EXCHANGE_CLEANUP_COMPLETED)
			bnx2fc_process_cleanup_compl(io_req, task, num_rq);
		अन्यथा
			prपूर्णांकk(KERN_ERR PFX "Invalid rx state - %d\n",
				rx_state);
		अवरोध;

	हाल BNX2FC_TASK_MGMT_CMD:
		BNX2FC_IO_DBG(io_req, "Processing TM complete\n");
		bnx2fc_process_पंचांग_compl(io_req, task, num_rq, rq_data);
		अवरोध;

	हाल BNX2FC_ABTS:
		/*
		 * ABTS request received by firmware. ABTS response
		 * will be delivered to the task beदीर्घing to the IO
		 * that was पातed
		 */
		BNX2FC_IO_DBG(io_req, "cq_compl- ABTS sent out by fw\n");
		kref_put(&io_req->refcount, bnx2fc_cmd_release);
		अवरोध;

	हाल BNX2FC_ELS:
		अगर (rx_state == FCOE_TASK_RX_STATE_COMPLETED)
			bnx2fc_process_els_compl(io_req, task, num_rq);
		अन्यथा अगर (rx_state == FCOE_TASK_RX_STATE_ABTS_COMPLETED)
			bnx2fc_process_abts_compl(io_req, task, num_rq);
		अन्यथा अगर (rx_state ==
			 FCOE_TASK_RX_STATE_EXCHANGE_CLEANUP_COMPLETED)
			bnx2fc_process_cleanup_compl(io_req, task, num_rq);
		अन्यथा
			prपूर्णांकk(KERN_ERR PFX "Invalid rx state =  %d\n",
				rx_state);
		अवरोध;

	हाल BNX2FC_CLEANUP:
		BNX2FC_IO_DBG(io_req, "cq_compl- cleanup resp rcvd\n");
		kref_put(&io_req->refcount, bnx2fc_cmd_release);
		अवरोध;

	हाल BNX2FC_SEQ_CLEANUP:
		BNX2FC_IO_DBG(io_req, "cq_compl(0x%x) - seq cleanup resp\n",
			      io_req->xid);
		bnx2fc_process_seq_cleanup_compl(io_req, task, rx_state);
		kref_put(&io_req->refcount, bnx2fc_cmd_release);
		अवरोध;

	शेष:
		prपूर्णांकk(KERN_ERR PFX "Invalid cmd_type %d\n", cmd_type);
		अवरोध;
	पूर्ण
	spin_unlock_bh(&tgt->tgt_lock);
पूर्ण

व्योम bnx2fc_arm_cq(काष्ठा bnx2fc_rport *tgt)
अणु
	काष्ठा b577xx_fcoe_rx_करोorbell *rx_db = &tgt->rx_db;
	u32 msg;

	wmb();
	rx_db->करोorbell_cq_cons = tgt->cq_cons_idx | (tgt->cq_curr_toggle_bit <<
			FCOE_CQE_TOGGLE_BIT_SHIFT);
	msg = *((u32 *)rx_db);
	ग_लिखोl(cpu_to_le32(msg), tgt->ctx_base);

पूर्ण

अटल काष्ठा bnx2fc_work *bnx2fc_alloc_work(काष्ठा bnx2fc_rport *tgt, u16 wqe,
					     अचिन्हित अक्षर *rq_data, u8 num_rq,
					     काष्ठा fcoe_task_ctx_entry *task)
अणु
	काष्ठा bnx2fc_work *work;
	work = kzalloc(माप(काष्ठा bnx2fc_work), GFP_ATOMIC);
	अगर (!work)
		वापस शून्य;

	INIT_LIST_HEAD(&work->list);
	work->tgt = tgt;
	work->wqe = wqe;
	work->num_rq = num_rq;
	work->task = task;
	अगर (rq_data)
		स_नकल(work->rq_data, rq_data, BNX2FC_RQ_BUF_SZ);

	वापस work;
पूर्ण

/* Pending work request completion */
अटल bool bnx2fc_pending_work(काष्ठा bnx2fc_rport *tgt, अचिन्हित पूर्णांक wqe)
अणु
	अचिन्हित पूर्णांक cpu = wqe % num_possible_cpus();
	काष्ठा bnx2fc_percpu_s *fps;
	काष्ठा bnx2fc_work *work;
	काष्ठा fcoe_task_ctx_entry *task;
	काष्ठा fcoe_task_ctx_entry *task_page;
	काष्ठा fcoe_port *port = tgt->port;
	काष्ठा bnx2fc_पूर्णांकerface *पूर्णांकerface = port->priv;
	काष्ठा bnx2fc_hba *hba = पूर्णांकerface->hba;
	अचिन्हित अक्षर *rq_data = शून्य;
	अचिन्हित अक्षर rq_data_buff[BNX2FC_RQ_BUF_SZ];
	पूर्णांक task_idx, index;
	u16 xid;
	u8 num_rq;
	पूर्णांक i;

	xid = wqe & FCOE_PEND_WQ_CQE_TASK_ID;
	अगर (xid >= hba->max_tasks) अणु
		pr_err(PFX "ERROR:xid out of range\n");
		वापस false;
	पूर्ण

	task_idx = xid / BNX2FC_TASKS_PER_PAGE;
	index = xid % BNX2FC_TASKS_PER_PAGE;
	task_page = (काष्ठा fcoe_task_ctx_entry *)hba->task_ctx[task_idx];
	task = &task_page[index];

	num_rq = ((task->rxwr_txrd.var_ctx.rx_flags &
		   FCOE_TCE_RX_WR_TX_RD_VAR_NUM_RQ_WQE) >>
		  FCOE_TCE_RX_WR_TX_RD_VAR_NUM_RQ_WQE_SHIFT);

	स_रखो(rq_data_buff, 0, BNX2FC_RQ_BUF_SZ);

	अगर (!num_rq)
		जाओ num_rq_zero;

	rq_data = bnx2fc_get_next_rqe(tgt, 1);

	अगर (num_rq > 1) अणु
		/* We करो not need extra sense data */
		क्रम (i = 1; i < num_rq; i++)
			bnx2fc_get_next_rqe(tgt, 1);
	पूर्ण

	अगर (rq_data)
		स_नकल(rq_data_buff, rq_data, BNX2FC_RQ_BUF_SZ);

	/* वापस RQ entries */
	क्रम (i = 0; i < num_rq; i++)
		bnx2fc_वापस_rqe(tgt, 1);

num_rq_zero:

	fps = &per_cpu(bnx2fc_percpu, cpu);
	spin_lock_bh(&fps->fp_work_lock);
	अगर (fps->iothपढ़ो) अणु
		work = bnx2fc_alloc_work(tgt, wqe, rq_data_buff,
					 num_rq, task);
		अगर (work) अणु
			list_add_tail(&work->list, &fps->work_list);
			wake_up_process(fps->iothपढ़ो);
			spin_unlock_bh(&fps->fp_work_lock);
			वापस true;
		पूर्ण
	पूर्ण
	spin_unlock_bh(&fps->fp_work_lock);
	bnx2fc_process_cq_compl(tgt, wqe,
				rq_data_buff, num_rq, task);

	वापस true;
पूर्ण

पूर्णांक bnx2fc_process_new_cqes(काष्ठा bnx2fc_rport *tgt)
अणु
	काष्ठा fcoe_cqe *cq;
	u32 cq_cons;
	काष्ठा fcoe_cqe *cqe;
	u32 num_मुक्त_sqes = 0;
	u32 num_cqes = 0;
	u16 wqe;

	/*
	 * cq_lock is a low contention lock used to protect
	 * the CQ data काष्ठाure from being मुक्तd up during
	 * the upload operation
	 */
	spin_lock_bh(&tgt->cq_lock);

	अगर (!tgt->cq) अणु
		prपूर्णांकk(KERN_ERR PFX "process_new_cqes: cq is NULL\n");
		spin_unlock_bh(&tgt->cq_lock);
		वापस 0;
	पूर्ण
	cq = tgt->cq;
	cq_cons = tgt->cq_cons_idx;
	cqe = &cq[cq_cons];

	जबतक (((wqe = cqe->wqe) & FCOE_CQE_TOGGLE_BIT) ==
	       (tgt->cq_curr_toggle_bit <<
	       FCOE_CQE_TOGGLE_BIT_SHIFT)) अणु

		/* new entry on the cq */
		अगर (wqe & FCOE_CQE_CQE_TYPE) अणु
			/* Unsolicited event notअगरication */
			bnx2fc_process_unsol_compl(tgt, wqe);
		पूर्ण अन्यथा अणु
			अगर (bnx2fc_pending_work(tgt, wqe))
				num_मुक्त_sqes++;
		पूर्ण
		cqe++;
		tgt->cq_cons_idx++;
		num_cqes++;

		अगर (tgt->cq_cons_idx == BNX2FC_CQ_WQES_MAX) अणु
			tgt->cq_cons_idx = 0;
			cqe = cq;
			tgt->cq_curr_toggle_bit =
				1 - tgt->cq_curr_toggle_bit;
		पूर्ण
	पूर्ण
	अगर (num_cqes) अणु
		/* Arm CQ only अगर करोorbell is mapped */
		अगर (tgt->ctx_base)
			bnx2fc_arm_cq(tgt);
		atomic_add(num_मुक्त_sqes, &tgt->मुक्त_sqes);
	पूर्ण
	spin_unlock_bh(&tgt->cq_lock);
	वापस 0;
पूर्ण

/**
 * bnx2fc_fastpath_notअगरication - process global event queue (KCQ)
 *
 * @hba:		adapter काष्ठाure poपूर्णांकer
 * @new_cqe_kcqe:	poपूर्णांकer to newly DMA'd KCQ entry
 *
 * Fast path event notअगरication handler
 */
अटल व्योम bnx2fc_fastpath_notअगरication(काष्ठा bnx2fc_hba *hba,
					काष्ठा fcoe_kcqe *new_cqe_kcqe)
अणु
	u32 conn_id = new_cqe_kcqe->fcoe_conn_id;
	काष्ठा bnx2fc_rport *tgt = hba->tgt_ofld_list[conn_id];

	अगर (!tgt) अणु
		prपूर्णांकk(KERN_ERR PFX "conn_id 0x%x not valid\n", conn_id);
		वापस;
	पूर्ण

	bnx2fc_process_new_cqes(tgt);
पूर्ण

/**
 * bnx2fc_process_ofld_cmpl - process FCoE session offload completion
 *
 * @hba:	adapter काष्ठाure poपूर्णांकer
 * @ofld_kcqe:	connection offload kcqe poपूर्णांकer
 *
 * handle session offload completion, enable the session अगर offload is
 * successful.
 */
अटल व्योम bnx2fc_process_ofld_cmpl(काष्ठा bnx2fc_hba *hba,
					काष्ठा fcoe_kcqe *ofld_kcqe)
अणु
	काष्ठा bnx2fc_rport		*tgt;
	काष्ठा bnx2fc_पूर्णांकerface		*पूर्णांकerface;
	u32				conn_id;
	u32				context_id;

	conn_id = ofld_kcqe->fcoe_conn_id;
	context_id = ofld_kcqe->fcoe_conn_context_id;
	tgt = hba->tgt_ofld_list[conn_id];
	अगर (!tgt) अणु
		prपूर्णांकk(KERN_ALERT PFX "ERROR:ofld_cmpl: No pending ofld req\n");
		वापस;
	पूर्ण
	BNX2FC_TGT_DBG(tgt, "Entered ofld compl - context_id = 0x%x\n",
		ofld_kcqe->fcoe_conn_context_id);
	पूर्णांकerface = tgt->port->priv;
	अगर (hba != पूर्णांकerface->hba) अणु
		prपूर्णांकk(KERN_ERR PFX "ERROR:ofld_cmpl: HBA mis-match\n");
		जाओ ofld_cmpl_err;
	पूर्ण
	/*
	 * cnic has allocated a context_id क्रम this session; use this
	 * जबतक enabling the session.
	 */
	tgt->context_id = context_id;
	अगर (ofld_kcqe->completion_status) अणु
		अगर (ofld_kcqe->completion_status ==
				FCOE_KCQE_COMPLETION_STATUS_CTX_ALLOC_FAILURE) अणु
			prपूर्णांकk(KERN_ERR PFX "unable to allocate FCoE context "
				"resources\n");
			set_bit(BNX2FC_FLAG_CTX_ALLOC_FAILURE, &tgt->flags);
		पूर्ण
	पूर्ण अन्यथा अणु
		/* FW offload request successfully completed */
		set_bit(BNX2FC_FLAG_OFFLOADED, &tgt->flags);
	पूर्ण
ofld_cmpl_err:
	set_bit(BNX2FC_FLAG_OFLD_REQ_CMPL, &tgt->flags);
	wake_up_पूर्णांकerruptible(&tgt->ofld_रुको);
पूर्ण

/**
 * bnx2fc_process_enable_conn_cmpl - process FCoE session enable completion
 *
 * @hba:	adapter काष्ठाure poपूर्णांकer
 * @ofld_kcqe:	connection offload kcqe poपूर्णांकer
 *
 * handle session enable completion, mark the rport as पढ़ोy
 */

अटल व्योम bnx2fc_process_enable_conn_cmpl(काष्ठा bnx2fc_hba *hba,
						काष्ठा fcoe_kcqe *ofld_kcqe)
अणु
	काष्ठा bnx2fc_rport		*tgt;
	काष्ठा bnx2fc_पूर्णांकerface		*पूर्णांकerface;
	u32				conn_id;
	u32				context_id;

	context_id = ofld_kcqe->fcoe_conn_context_id;
	conn_id = ofld_kcqe->fcoe_conn_id;
	tgt = hba->tgt_ofld_list[conn_id];
	अगर (!tgt) अणु
		prपूर्णांकk(KERN_ERR PFX "ERROR:enbl_cmpl: No pending ofld req\n");
		वापस;
	पूर्ण

	BNX2FC_TGT_DBG(tgt, "Enable compl - context_id = 0x%x\n",
		ofld_kcqe->fcoe_conn_context_id);

	/*
	 * context_id should be the same क्रम this target during offload
	 * and enable
	 */
	अगर (tgt->context_id != context_id) अणु
		prपूर्णांकk(KERN_ERR PFX "context id mis-match\n");
		वापस;
	पूर्ण
	पूर्णांकerface = tgt->port->priv;
	अगर (hba != पूर्णांकerface->hba) अणु
		prपूर्णांकk(KERN_ERR PFX "bnx2fc-enbl_cmpl: HBA mis-match\n");
		जाओ enbl_cmpl_err;
	पूर्ण
	अगर (!ofld_kcqe->completion_status)
		/* enable successful - rport पढ़ोy क्रम issuing IOs */
		set_bit(BNX2FC_FLAG_ENABLED, &tgt->flags);

enbl_cmpl_err:
	set_bit(BNX2FC_FLAG_OFLD_REQ_CMPL, &tgt->flags);
	wake_up_पूर्णांकerruptible(&tgt->ofld_रुको);
पूर्ण

अटल व्योम bnx2fc_process_conn_disable_cmpl(काष्ठा bnx2fc_hba *hba,
					काष्ठा fcoe_kcqe *disable_kcqe)
अणु

	काष्ठा bnx2fc_rport		*tgt;
	u32				conn_id;

	conn_id = disable_kcqe->fcoe_conn_id;
	tgt = hba->tgt_ofld_list[conn_id];
	अगर (!tgt) अणु
		prपूर्णांकk(KERN_ERR PFX "ERROR: disable_cmpl: No disable req\n");
		वापस;
	पूर्ण

	BNX2FC_TGT_DBG(tgt, PFX "disable_cmpl: conn_id %d\n", conn_id);

	अगर (disable_kcqe->completion_status) अणु
		prपूर्णांकk(KERN_ERR PFX "Disable failed with cmpl status %d\n",
			disable_kcqe->completion_status);
		set_bit(BNX2FC_FLAG_DISABLE_FAILED, &tgt->flags);
		set_bit(BNX2FC_FLAG_UPLD_REQ_COMPL, &tgt->flags);
		wake_up_पूर्णांकerruptible(&tgt->upld_रुको);
	पूर्ण अन्यथा अणु
		/* disable successful */
		BNX2FC_TGT_DBG(tgt, "disable successful\n");
		clear_bit(BNX2FC_FLAG_OFFLOADED, &tgt->flags);
		clear_bit(BNX2FC_FLAG_ENABLED, &tgt->flags);
		set_bit(BNX2FC_FLAG_DISABLED, &tgt->flags);
		set_bit(BNX2FC_FLAG_UPLD_REQ_COMPL, &tgt->flags);
		wake_up_पूर्णांकerruptible(&tgt->upld_रुको);
	पूर्ण
पूर्ण

अटल व्योम bnx2fc_process_conn_destroy_cmpl(काष्ठा bnx2fc_hba *hba,
					काष्ठा fcoe_kcqe *destroy_kcqe)
अणु
	काष्ठा bnx2fc_rport		*tgt;
	u32				conn_id;

	conn_id = destroy_kcqe->fcoe_conn_id;
	tgt = hba->tgt_ofld_list[conn_id];
	अगर (!tgt) अणु
		prपूर्णांकk(KERN_ERR PFX "destroy_cmpl: No destroy req\n");
		वापस;
	पूर्ण

	BNX2FC_TGT_DBG(tgt, "destroy_cmpl: conn_id %d\n", conn_id);

	अगर (destroy_kcqe->completion_status) अणु
		prपूर्णांकk(KERN_ERR PFX "Destroy conn failed, cmpl status %d\n",
			destroy_kcqe->completion_status);
		वापस;
	पूर्ण अन्यथा अणु
		/* destroy successful */
		BNX2FC_TGT_DBG(tgt, "upload successful\n");
		clear_bit(BNX2FC_FLAG_DISABLED, &tgt->flags);
		set_bit(BNX2FC_FLAG_DESTROYED, &tgt->flags);
		set_bit(BNX2FC_FLAG_UPLD_REQ_COMPL, &tgt->flags);
		wake_up_पूर्णांकerruptible(&tgt->upld_रुको);
	पूर्ण
पूर्ण

अटल व्योम bnx2fc_init_failure(काष्ठा bnx2fc_hba *hba, u32 err_code)
अणु
	चयन (err_code) अणु
	हाल FCOE_KCQE_COMPLETION_STATUS_INVALID_OPCODE:
		prपूर्णांकk(KERN_ERR PFX "init_failure due to invalid opcode\n");
		अवरोध;

	हाल FCOE_KCQE_COMPLETION_STATUS_CTX_ALLOC_FAILURE:
		prपूर्णांकk(KERN_ERR PFX "init failed due to ctx alloc failure\n");
		अवरोध;

	हाल FCOE_KCQE_COMPLETION_STATUS_NIC_ERROR:
		prपूर्णांकk(KERN_ERR PFX "init_failure due to NIC error\n");
		अवरोध;
	हाल FCOE_KCQE_COMPLETION_STATUS_ERROR:
		prपूर्णांकk(KERN_ERR PFX "init failure due to compl status err\n");
		अवरोध;
	हाल FCOE_KCQE_COMPLETION_STATUS_WRONG_HSI_VERSION:
		prपूर्णांकk(KERN_ERR PFX "init failure due to HSI mismatch\n");
		अवरोध;
	शेष:
		prपूर्णांकk(KERN_ERR PFX "Unknown Error code %d\n", err_code);
	पूर्ण
पूर्ण

/**
 * bnx2fc_indicate_kcqe() - process KCQE
 *
 * @context:	adapter काष्ठाure poपूर्णांकer
 * @kcq:	kcqe poपूर्णांकer
 * @num_cqe:	Number of completion queue elements
 *
 * Generic KCQ event handler
 */
व्योम bnx2fc_indicate_kcqe(व्योम *context, काष्ठा kcqe *kcq[],
					u32 num_cqe)
अणु
	काष्ठा bnx2fc_hba *hba = (काष्ठा bnx2fc_hba *)context;
	पूर्णांक i = 0;
	काष्ठा fcoe_kcqe *kcqe = शून्य;

	जबतक (i < num_cqe) अणु
		kcqe = (काष्ठा fcoe_kcqe *) kcq[i++];

		चयन (kcqe->op_code) अणु
		हाल FCOE_KCQE_OPCODE_CQ_EVENT_NOTIFICATION:
			bnx2fc_fastpath_notअगरication(hba, kcqe);
			अवरोध;

		हाल FCOE_KCQE_OPCODE_OFFLOAD_CONN:
			bnx2fc_process_ofld_cmpl(hba, kcqe);
			अवरोध;

		हाल FCOE_KCQE_OPCODE_ENABLE_CONN:
			bnx2fc_process_enable_conn_cmpl(hba, kcqe);
			अवरोध;

		हाल FCOE_KCQE_OPCODE_INIT_FUNC:
			अगर (kcqe->completion_status !=
					FCOE_KCQE_COMPLETION_STATUS_SUCCESS) अणु
				bnx2fc_init_failure(hba,
						kcqe->completion_status);
			पूर्ण अन्यथा अणु
				set_bit(ADAPTER_STATE_UP, &hba->adapter_state);
				bnx2fc_get_link_state(hba);
				prपूर्णांकk(KERN_INFO PFX "[%.2x]: FCOE_INIT passed\n",
					(u8)hba->pcidev->bus->number);
			पूर्ण
			अवरोध;

		हाल FCOE_KCQE_OPCODE_DESTROY_FUNC:
			अगर (kcqe->completion_status !=
					FCOE_KCQE_COMPLETION_STATUS_SUCCESS) अणु

				prपूर्णांकk(KERN_ERR PFX "DESTROY failed\n");
			पूर्ण अन्यथा अणु
				prपूर्णांकk(KERN_ERR PFX "DESTROY success\n");
			पूर्ण
			set_bit(BNX2FC_FLAG_DESTROY_CMPL, &hba->flags);
			wake_up_पूर्णांकerruptible(&hba->destroy_रुको);
			अवरोध;

		हाल FCOE_KCQE_OPCODE_DISABLE_CONN:
			bnx2fc_process_conn_disable_cmpl(hba, kcqe);
			अवरोध;

		हाल FCOE_KCQE_OPCODE_DESTROY_CONN:
			bnx2fc_process_conn_destroy_cmpl(hba, kcqe);
			अवरोध;

		हाल FCOE_KCQE_OPCODE_STAT_FUNC:
			अगर (kcqe->completion_status !=
			    FCOE_KCQE_COMPLETION_STATUS_SUCCESS)
				prपूर्णांकk(KERN_ERR PFX "STAT failed\n");
			complete(&hba->stat_req_करोne);
			अवरोध;

		हाल FCOE_KCQE_OPCODE_FCOE_ERROR:
		शेष:
			prपूर्णांकk(KERN_ERR PFX "unknown opcode 0x%x\n",
								kcqe->op_code);
		पूर्ण
	पूर्ण
पूर्ण

व्योम bnx2fc_add_2_sq(काष्ठा bnx2fc_rport *tgt, u16 xid)
अणु
	काष्ठा fcoe_sqe *sqe;

	sqe = &tgt->sq[tgt->sq_prod_idx];

	/* Fill SQ WQE */
	sqe->wqe = xid << FCOE_SQE_TASK_ID_SHIFT;
	sqe->wqe |= tgt->sq_curr_toggle_bit << FCOE_SQE_TOGGLE_BIT_SHIFT;

	/* Advance SQ Prod Idx */
	अगर (++tgt->sq_prod_idx == BNX2FC_SQ_WQES_MAX) अणु
		tgt->sq_prod_idx = 0;
		tgt->sq_curr_toggle_bit = 1 - tgt->sq_curr_toggle_bit;
	पूर्ण
पूर्ण

व्योम bnx2fc_ring_करोorbell(काष्ठा bnx2fc_rport *tgt)
अणु
	काष्ठा b577xx_करोorbell_set_prod *sq_db = &tgt->sq_db;
	u32 msg;

	wmb();
	sq_db->prod = tgt->sq_prod_idx |
				(tgt->sq_curr_toggle_bit << 15);
	msg = *((u32 *)sq_db);
	ग_लिखोl(cpu_to_le32(msg), tgt->ctx_base);

पूर्ण

पूर्णांक bnx2fc_map_करोorbell(काष्ठा bnx2fc_rport *tgt)
अणु
	u32 context_id = tgt->context_id;
	काष्ठा fcoe_port *port = tgt->port;
	u32 reg_off;
	resource_माप_प्रकार reg_base;
	काष्ठा bnx2fc_पूर्णांकerface *पूर्णांकerface = port->priv;
	काष्ठा bnx2fc_hba *hba = पूर्णांकerface->hba;

	reg_base = pci_resource_start(hba->pcidev,
					BNX2X_DOORBELL_PCI_BAR);
	reg_off = (1 << BNX2X_DB_SHIFT) * (context_id & 0x1FFFF);
	tgt->ctx_base = ioremap(reg_base + reg_off, 4);
	अगर (!tgt->ctx_base)
		वापस -ENOMEM;
	वापस 0;
पूर्ण

अक्षर *bnx2fc_get_next_rqe(काष्ठा bnx2fc_rport *tgt, u8 num_items)
अणु
	अक्षर *buf = (अक्षर *)tgt->rq + (tgt->rq_cons_idx * BNX2FC_RQ_BUF_SZ);

	अगर (tgt->rq_cons_idx + num_items > BNX2FC_RQ_WQES_MAX)
		वापस शून्य;

	tgt->rq_cons_idx += num_items;

	अगर (tgt->rq_cons_idx >= BNX2FC_RQ_WQES_MAX)
		tgt->rq_cons_idx -= BNX2FC_RQ_WQES_MAX;

	वापस buf;
पूर्ण

व्योम bnx2fc_वापस_rqe(काष्ठा bnx2fc_rport *tgt, u8 num_items)
अणु
	/* वापस the rq buffer */
	u32 next_prod_idx = tgt->rq_prod_idx + num_items;
	अगर ((next_prod_idx & 0x7fff) == BNX2FC_RQ_WQES_MAX) अणु
		/* Wrap around RQ */
		next_prod_idx += 0x8000 - BNX2FC_RQ_WQES_MAX;
	पूर्ण
	tgt->rq_prod_idx = next_prod_idx;
	tgt->conn_db->rq_prod = tgt->rq_prod_idx;
पूर्ण

व्योम bnx2fc_init_seq_cleanup_task(काष्ठा bnx2fc_cmd *seq_clnp_req,
				  काष्ठा fcoe_task_ctx_entry *task,
				  काष्ठा bnx2fc_cmd *orig_io_req,
				  u32 offset)
अणु
	काष्ठा scsi_cmnd *sc_cmd = orig_io_req->sc_cmd;
	काष्ठा bnx2fc_rport *tgt = seq_clnp_req->tgt;
	काष्ठा fcoe_bd_ctx *bd = orig_io_req->bd_tbl->bd_tbl;
	काष्ठा fcoe_ext_mul_sges_ctx *sgl;
	u8 task_type = FCOE_TASK_TYPE_SEQUENCE_CLEANUP;
	u8 orig_task_type;
	u16 orig_xid = orig_io_req->xid;
	u32 context_id = tgt->context_id;
	u64 phys_addr = (u64)orig_io_req->bd_tbl->bd_tbl_dma;
	u32 orig_offset = offset;
	पूर्णांक bd_count;
	पूर्णांक i;

	स_रखो(task, 0, माप(काष्ठा fcoe_task_ctx_entry));

	अगर (sc_cmd->sc_data_direction == DMA_TO_DEVICE)
		orig_task_type = FCOE_TASK_TYPE_WRITE;
	अन्यथा
		orig_task_type = FCOE_TASK_TYPE_READ;

	/* Tx flags */
	task->txwr_rxrd.स्थिर_ctx.tx_flags =
				FCOE_TASK_TX_STATE_SEQUENCE_CLEANUP <<
				FCOE_TCE_TX_WR_RX_RD_CONST_TX_STATE_SHIFT;
	/* init flags */
	task->txwr_rxrd.स्थिर_ctx.init_flags = task_type <<
				FCOE_TCE_TX_WR_RX_RD_CONST_TASK_TYPE_SHIFT;
	task->txwr_rxrd.स्थिर_ctx.init_flags |= FCOE_TASK_CLASS_TYPE_3 <<
				FCOE_TCE_TX_WR_RX_RD_CONST_CLASS_TYPE_SHIFT;
	task->rxwr_txrd.स्थिर_ctx.init_flags = context_id <<
				FCOE_TCE_RX_WR_TX_RD_CONST_CID_SHIFT;
	task->rxwr_txrd.स्थिर_ctx.init_flags = context_id <<
				FCOE_TCE_RX_WR_TX_RD_CONST_CID_SHIFT;

	task->txwr_rxrd.जोड़_ctx.cleanup.ctx.cleaned_task_id = orig_xid;

	task->txwr_rxrd.जोड़_ctx.cleanup.ctx.rolled_tx_seq_cnt = 0;
	task->txwr_rxrd.जोड़_ctx.cleanup.ctx.rolled_tx_data_offset = offset;

	bd_count = orig_io_req->bd_tbl->bd_valid;

	/* obtain the appropriate bd entry from relative offset */
	क्रम (i = 0; i < bd_count; i++) अणु
		अगर (offset < bd[i].buf_len)
			अवरोध;
		offset -= bd[i].buf_len;
	पूर्ण
	phys_addr += (i * माप(काष्ठा fcoe_bd_ctx));

	अगर (orig_task_type == FCOE_TASK_TYPE_WRITE) अणु
		task->txwr_only.sgl_ctx.sgl.mul_sgl.cur_sge_addr.lo =
				(u32)phys_addr;
		task->txwr_only.sgl_ctx.sgl.mul_sgl.cur_sge_addr.hi =
				(u32)((u64)phys_addr >> 32);
		task->txwr_only.sgl_ctx.sgl.mul_sgl.sgl_size =
				bd_count;
		task->txwr_only.sgl_ctx.sgl.mul_sgl.cur_sge_off =
				offset; /* adjusted offset */
		task->txwr_only.sgl_ctx.sgl.mul_sgl.cur_sge_idx = i;
	पूर्ण अन्यथा अणु

		/* Multiple SGEs were used क्रम this IO */
		sgl = &task->rxwr_only.जोड़_ctx.पढ़ो_info.sgl_ctx.sgl;
		sgl->mul_sgl.cur_sge_addr.lo = (u32)phys_addr;
		sgl->mul_sgl.cur_sge_addr.hi = (u32)((u64)phys_addr >> 32);
		sgl->mul_sgl.sgl_size = bd_count;
		sgl->mul_sgl.cur_sge_off = offset; /*adjusted offset */
		sgl->mul_sgl.cur_sge_idx = i;

		स_रखो(&task->rxwr_only.rx_seq_ctx, 0,
		       माप(काष्ठा fcoe_rx_seq_ctx));
		task->rxwr_only.rx_seq_ctx.low_exp_ro = orig_offset;
		task->rxwr_only.rx_seq_ctx.high_exp_ro = orig_offset;
	पूर्ण
पूर्ण
व्योम bnx2fc_init_cleanup_task(काष्ठा bnx2fc_cmd *io_req,
			      काष्ठा fcoe_task_ctx_entry *task,
			      u16 orig_xid)
अणु
	u8 task_type = FCOE_TASK_TYPE_EXCHANGE_CLEANUP;
	काष्ठा bnx2fc_rport *tgt = io_req->tgt;
	u32 context_id = tgt->context_id;

	स_रखो(task, 0, माप(काष्ठा fcoe_task_ctx_entry));

	/* Tx Write Rx Read */
	/* init flags */
	task->txwr_rxrd.स्थिर_ctx.init_flags = task_type <<
				FCOE_TCE_TX_WR_RX_RD_CONST_TASK_TYPE_SHIFT;
	task->txwr_rxrd.स्थिर_ctx.init_flags |= FCOE_TASK_CLASS_TYPE_3 <<
				FCOE_TCE_TX_WR_RX_RD_CONST_CLASS_TYPE_SHIFT;
	अगर (tgt->dev_type == TYPE_TAPE)
		task->txwr_rxrd.स्थिर_ctx.init_flags |=
				FCOE_TASK_DEV_TYPE_TAPE <<
				FCOE_TCE_TX_WR_RX_RD_CONST_DEV_TYPE_SHIFT;
	अन्यथा
		task->txwr_rxrd.स्थिर_ctx.init_flags |=
				FCOE_TASK_DEV_TYPE_DISK <<
				FCOE_TCE_TX_WR_RX_RD_CONST_DEV_TYPE_SHIFT;
	task->txwr_rxrd.जोड़_ctx.cleanup.ctx.cleaned_task_id = orig_xid;

	/* Tx flags */
	task->txwr_rxrd.स्थिर_ctx.tx_flags =
				FCOE_TASK_TX_STATE_EXCHANGE_CLEANUP <<
				FCOE_TCE_TX_WR_RX_RD_CONST_TX_STATE_SHIFT;

	/* Rx Read Tx Write */
	task->rxwr_txrd.स्थिर_ctx.init_flags = context_id <<
				FCOE_TCE_RX_WR_TX_RD_CONST_CID_SHIFT;
	task->rxwr_txrd.var_ctx.rx_flags |= 1 <<
				FCOE_TCE_RX_WR_TX_RD_VAR_EXP_FIRST_FRAME_SHIFT;
पूर्ण

व्योम bnx2fc_init_mp_task(काष्ठा bnx2fc_cmd *io_req,
				काष्ठा fcoe_task_ctx_entry *task)
अणु
	काष्ठा bnx2fc_mp_req *mp_req = &(io_req->mp_req);
	काष्ठा bnx2fc_rport *tgt = io_req->tgt;
	काष्ठा fc_frame_header *fc_hdr;
	काष्ठा fcoe_ext_mul_sges_ctx *sgl;
	u8 task_type = 0;
	u64 *hdr;
	u64 temp_hdr[3];
	u32 context_id;


	/* Obtain task_type */
	अगर ((io_req->cmd_type == BNX2FC_TASK_MGMT_CMD) ||
	    (io_req->cmd_type == BNX2FC_ELS)) अणु
		task_type = FCOE_TASK_TYPE_MIDPATH;
	पूर्ण अन्यथा अगर (io_req->cmd_type == BNX2FC_ABTS) अणु
		task_type = FCOE_TASK_TYPE_ABTS;
	पूर्ण

	स_रखो(task, 0, माप(काष्ठा fcoe_task_ctx_entry));

	/* Setup the task from io_req क्रम easy reference */
	io_req->task = task;

	BNX2FC_IO_DBG(io_req, "Init MP task for cmd_type = %d task_type = %d\n",
		io_req->cmd_type, task_type);

	/* Tx only */
	अगर ((task_type == FCOE_TASK_TYPE_MIDPATH) ||
	    (task_type == FCOE_TASK_TYPE_UNSOLICITED)) अणु
		task->txwr_only.sgl_ctx.sgl.mul_sgl.cur_sge_addr.lo =
				(u32)mp_req->mp_req_bd_dma;
		task->txwr_only.sgl_ctx.sgl.mul_sgl.cur_sge_addr.hi =
				(u32)((u64)mp_req->mp_req_bd_dma >> 32);
		task->txwr_only.sgl_ctx.sgl.mul_sgl.sgl_size = 1;
	पूर्ण

	/* Tx Write Rx Read */
	/* init flags */
	task->txwr_rxrd.स्थिर_ctx.init_flags = task_type <<
				FCOE_TCE_TX_WR_RX_RD_CONST_TASK_TYPE_SHIFT;
	अगर (tgt->dev_type == TYPE_TAPE)
		task->txwr_rxrd.स्थिर_ctx.init_flags |=
				FCOE_TASK_DEV_TYPE_TAPE <<
				FCOE_TCE_TX_WR_RX_RD_CONST_DEV_TYPE_SHIFT;
	अन्यथा
		task->txwr_rxrd.स्थिर_ctx.init_flags |=
				FCOE_TASK_DEV_TYPE_DISK <<
				FCOE_TCE_TX_WR_RX_RD_CONST_DEV_TYPE_SHIFT;
	task->txwr_rxrd.स्थिर_ctx.init_flags |= FCOE_TASK_CLASS_TYPE_3 <<
				FCOE_TCE_TX_WR_RX_RD_CONST_CLASS_TYPE_SHIFT;

	/* tx flags */
	task->txwr_rxrd.स्थिर_ctx.tx_flags = FCOE_TASK_TX_STATE_INIT <<
				FCOE_TCE_TX_WR_RX_RD_CONST_TX_STATE_SHIFT;

	/* Rx Write Tx Read */
	task->rxwr_txrd.स्थिर_ctx.data_2_trns = io_req->data_xfer_len;

	/* rx flags */
	task->rxwr_txrd.var_ctx.rx_flags |= 1 <<
				FCOE_TCE_RX_WR_TX_RD_VAR_EXP_FIRST_FRAME_SHIFT;

	context_id = tgt->context_id;
	task->rxwr_txrd.स्थिर_ctx.init_flags = context_id <<
				FCOE_TCE_RX_WR_TX_RD_CONST_CID_SHIFT;

	fc_hdr = &(mp_req->req_fc_hdr);
	अगर (task_type == FCOE_TASK_TYPE_MIDPATH) अणु
		fc_hdr->fh_ox_id = cpu_to_be16(io_req->xid);
		fc_hdr->fh_rx_id = htons(0xffff);
		task->rxwr_txrd.var_ctx.rx_id = 0xffff;
	पूर्ण अन्यथा अगर (task_type == FCOE_TASK_TYPE_UNSOLICITED) अणु
		fc_hdr->fh_rx_id = cpu_to_be16(io_req->xid);
	पूर्ण

	/* Fill FC Header पूर्णांकo middle path buffer */
	hdr = (u64 *) &task->txwr_rxrd.जोड़_ctx.tx_frame.fc_hdr;
	स_नकल(temp_hdr, fc_hdr, माप(temp_hdr));
	hdr[0] = cpu_to_be64(temp_hdr[0]);
	hdr[1] = cpu_to_be64(temp_hdr[1]);
	hdr[2] = cpu_to_be64(temp_hdr[2]);

	/* Rx Only */
	अगर (task_type == FCOE_TASK_TYPE_MIDPATH) अणु
		sgl = &task->rxwr_only.जोड़_ctx.पढ़ो_info.sgl_ctx.sgl;

		sgl->mul_sgl.cur_sge_addr.lo = (u32)mp_req->mp_resp_bd_dma;
		sgl->mul_sgl.cur_sge_addr.hi =
				(u32)((u64)mp_req->mp_resp_bd_dma >> 32);
		sgl->mul_sgl.sgl_size = 1;
	पूर्ण
पूर्ण

व्योम bnx2fc_init_task(काष्ठा bnx2fc_cmd *io_req,
			     काष्ठा fcoe_task_ctx_entry *task)
अणु
	u8 task_type;
	काष्ठा scsi_cmnd *sc_cmd = io_req->sc_cmd;
	काष्ठा io_bdt *bd_tbl = io_req->bd_tbl;
	काष्ठा bnx2fc_rport *tgt = io_req->tgt;
	काष्ठा fcoe_cached_sge_ctx *cached_sge;
	काष्ठा fcoe_ext_mul_sges_ctx *sgl;
	पूर्णांक dev_type = tgt->dev_type;
	u64 *fcp_cmnd;
	u64 पंचांगp_fcp_cmnd[4];
	u32 context_id;
	पूर्णांक cnt, i;
	पूर्णांक bd_count;

	स_रखो(task, 0, माप(काष्ठा fcoe_task_ctx_entry));

	/* Setup the task from io_req क्रम easy reference */
	io_req->task = task;

	अगर (sc_cmd->sc_data_direction == DMA_TO_DEVICE)
		task_type = FCOE_TASK_TYPE_WRITE;
	अन्यथा
		task_type = FCOE_TASK_TYPE_READ;

	/* Tx only */
	bd_count = bd_tbl->bd_valid;
	cached_sge = &task->rxwr_only.जोड़_ctx.पढ़ो_info.sgl_ctx.cached_sge;
	अगर (task_type == FCOE_TASK_TYPE_WRITE) अणु
		अगर ((dev_type == TYPE_DISK) && (bd_count == 1)) अणु
			काष्ठा fcoe_bd_ctx *fcoe_bd_tbl = bd_tbl->bd_tbl;

			task->txwr_only.sgl_ctx.cached_sge.cur_buf_addr.lo =
			cached_sge->cur_buf_addr.lo =
					fcoe_bd_tbl->buf_addr_lo;
			task->txwr_only.sgl_ctx.cached_sge.cur_buf_addr.hi =
			cached_sge->cur_buf_addr.hi =
					fcoe_bd_tbl->buf_addr_hi;
			task->txwr_only.sgl_ctx.cached_sge.cur_buf_rem =
			cached_sge->cur_buf_rem =
					fcoe_bd_tbl->buf_len;

			task->txwr_rxrd.स्थिर_ctx.init_flags |= 1 <<
				FCOE_TCE_TX_WR_RX_RD_CONST_CACHED_SGE_SHIFT;
		पूर्ण अन्यथा अणु
			task->txwr_only.sgl_ctx.sgl.mul_sgl.cur_sge_addr.lo =
					(u32)bd_tbl->bd_tbl_dma;
			task->txwr_only.sgl_ctx.sgl.mul_sgl.cur_sge_addr.hi =
					(u32)((u64)bd_tbl->bd_tbl_dma >> 32);
			task->txwr_only.sgl_ctx.sgl.mul_sgl.sgl_size =
					bd_tbl->bd_valid;
		पूर्ण
	पूर्ण

	/*Tx Write Rx Read */
	/* Init state to NORMAL */
	task->txwr_rxrd.स्थिर_ctx.init_flags |= task_type <<
				FCOE_TCE_TX_WR_RX_RD_CONST_TASK_TYPE_SHIFT;
	अगर (dev_type == TYPE_TAPE) अणु
		task->txwr_rxrd.स्थिर_ctx.init_flags |=
				FCOE_TASK_DEV_TYPE_TAPE <<
				FCOE_TCE_TX_WR_RX_RD_CONST_DEV_TYPE_SHIFT;
		io_req->rec_retry = 0;
		io_req->rec_retry = 0;
	पूर्ण अन्यथा
		task->txwr_rxrd.स्थिर_ctx.init_flags |=
				FCOE_TASK_DEV_TYPE_DISK <<
				FCOE_TCE_TX_WR_RX_RD_CONST_DEV_TYPE_SHIFT;
	task->txwr_rxrd.स्थिर_ctx.init_flags |= FCOE_TASK_CLASS_TYPE_3 <<
				FCOE_TCE_TX_WR_RX_RD_CONST_CLASS_TYPE_SHIFT;
	/* tx flags */
	task->txwr_rxrd.स्थिर_ctx.tx_flags = FCOE_TASK_TX_STATE_NORMAL <<
				FCOE_TCE_TX_WR_RX_RD_CONST_TX_STATE_SHIFT;

	/* Set initial seq counter */
	task->txwr_rxrd.जोड़_ctx.tx_seq.ctx.seq_cnt = 1;

	/* Fill FCP_CMND IU */
	fcp_cmnd = (u64 *)
		    task->txwr_rxrd.जोड़_ctx.fcp_cmd.opaque;
	bnx2fc_build_fcp_cmnd(io_req, (काष्ठा fcp_cmnd *)&पंचांगp_fcp_cmnd);

	/* swap fcp_cmnd */
	cnt = माप(काष्ठा fcp_cmnd) / माप(u64);

	क्रम (i = 0; i < cnt; i++) अणु
		*fcp_cmnd = cpu_to_be64(पंचांगp_fcp_cmnd[i]);
		fcp_cmnd++;
	पूर्ण

	/* Rx Write Tx Read */
	task->rxwr_txrd.स्थिर_ctx.data_2_trns = io_req->data_xfer_len;

	context_id = tgt->context_id;
	task->rxwr_txrd.स्थिर_ctx.init_flags = context_id <<
				FCOE_TCE_RX_WR_TX_RD_CONST_CID_SHIFT;

	/* rx flags */
	/* Set state to "waiting for the first packet" */
	task->rxwr_txrd.var_ctx.rx_flags |= 1 <<
				FCOE_TCE_RX_WR_TX_RD_VAR_EXP_FIRST_FRAME_SHIFT;

	task->rxwr_txrd.var_ctx.rx_id = 0xffff;

	/* Rx Only */
	अगर (task_type != FCOE_TASK_TYPE_READ)
		वापस;

	sgl = &task->rxwr_only.जोड़_ctx.पढ़ो_info.sgl_ctx.sgl;
	bd_count = bd_tbl->bd_valid;

	अगर (dev_type == TYPE_DISK) अणु
		अगर (bd_count == 1) अणु

			काष्ठा fcoe_bd_ctx *fcoe_bd_tbl = bd_tbl->bd_tbl;

			cached_sge->cur_buf_addr.lo = fcoe_bd_tbl->buf_addr_lo;
			cached_sge->cur_buf_addr.hi = fcoe_bd_tbl->buf_addr_hi;
			cached_sge->cur_buf_rem = fcoe_bd_tbl->buf_len;
			task->txwr_rxrd.स्थिर_ctx.init_flags |= 1 <<
				FCOE_TCE_TX_WR_RX_RD_CONST_CACHED_SGE_SHIFT;
		पूर्ण अन्यथा अगर (bd_count == 2) अणु
			काष्ठा fcoe_bd_ctx *fcoe_bd_tbl = bd_tbl->bd_tbl;

			cached_sge->cur_buf_addr.lo = fcoe_bd_tbl->buf_addr_lo;
			cached_sge->cur_buf_addr.hi = fcoe_bd_tbl->buf_addr_hi;
			cached_sge->cur_buf_rem = fcoe_bd_tbl->buf_len;

			fcoe_bd_tbl++;
			cached_sge->second_buf_addr.lo =
						 fcoe_bd_tbl->buf_addr_lo;
			cached_sge->second_buf_addr.hi =
						fcoe_bd_tbl->buf_addr_hi;
			cached_sge->second_buf_rem = fcoe_bd_tbl->buf_len;
			task->txwr_rxrd.स्थिर_ctx.init_flags |= 1 <<
				FCOE_TCE_TX_WR_RX_RD_CONST_CACHED_SGE_SHIFT;
		पूर्ण अन्यथा अणु

			sgl->mul_sgl.cur_sge_addr.lo = (u32)bd_tbl->bd_tbl_dma;
			sgl->mul_sgl.cur_sge_addr.hi =
					(u32)((u64)bd_tbl->bd_tbl_dma >> 32);
			sgl->mul_sgl.sgl_size = bd_count;
		पूर्ण
	पूर्ण अन्यथा अणु
		sgl->mul_sgl.cur_sge_addr.lo = (u32)bd_tbl->bd_tbl_dma;
		sgl->mul_sgl.cur_sge_addr.hi =
				(u32)((u64)bd_tbl->bd_tbl_dma >> 32);
		sgl->mul_sgl.sgl_size = bd_count;
	पूर्ण
पूर्ण

/**
 * bnx2fc_setup_task_ctx - allocate and map task context
 *
 * @hba:	poपूर्णांकer to adapter काष्ठाure
 *
 * allocate memory क्रम task context, and associated BD table to be used
 * by firmware
 *
 */
पूर्णांक bnx2fc_setup_task_ctx(काष्ठा bnx2fc_hba *hba)
अणु
	पूर्णांक rc = 0;
	काष्ठा regpair *task_ctx_bdt;
	dma_addr_t addr;
	पूर्णांक task_ctx_arr_sz;
	पूर्णांक i;

	/*
	 * Allocate task context bd table. A page size of bd table
	 * can map 256 buffers. Each buffer contains 32 task context
	 * entries. Hence the limit with one page is 8192 task context
	 * entries.
	 */
	hba->task_ctx_bd_tbl = dma_alloc_coherent(&hba->pcidev->dev,
						  PAGE_SIZE,
						  &hba->task_ctx_bd_dma,
						  GFP_KERNEL);
	अगर (!hba->task_ctx_bd_tbl) अणु
		prपूर्णांकk(KERN_ERR PFX "unable to allocate task context BDT\n");
		rc = -1;
		जाओ out;
	पूर्ण

	/*
	 * Allocate task_ctx which is an array of poपूर्णांकers poपूर्णांकing to
	 * a page containing 32 task contexts
	 */
	task_ctx_arr_sz = (hba->max_tasks / BNX2FC_TASKS_PER_PAGE);
	hba->task_ctx = kzalloc((task_ctx_arr_sz * माप(व्योम *)),
				 GFP_KERNEL);
	अगर (!hba->task_ctx) अणु
		prपूर्णांकk(KERN_ERR PFX "unable to allocate task context array\n");
		rc = -1;
		जाओ out1;
	पूर्ण

	/*
	 * Allocate task_ctx_dma which is an array of dma addresses
	 */
	hba->task_ctx_dma = kदो_स्मृति((task_ctx_arr_sz *
					माप(dma_addr_t)), GFP_KERNEL);
	अगर (!hba->task_ctx_dma) अणु
		prपूर्णांकk(KERN_ERR PFX "unable to alloc context mapping array\n");
		rc = -1;
		जाओ out2;
	पूर्ण

	task_ctx_bdt = (काष्ठा regpair *)hba->task_ctx_bd_tbl;
	क्रम (i = 0; i < task_ctx_arr_sz; i++) अणु

		hba->task_ctx[i] = dma_alloc_coherent(&hba->pcidev->dev,
						      PAGE_SIZE,
						      &hba->task_ctx_dma[i],
						      GFP_KERNEL);
		अगर (!hba->task_ctx[i]) अणु
			prपूर्णांकk(KERN_ERR PFX "unable to alloc task context\n");
			rc = -1;
			जाओ out3;
		पूर्ण
		addr = (u64)hba->task_ctx_dma[i];
		task_ctx_bdt->hi = cpu_to_le32((u64)addr >> 32);
		task_ctx_bdt->lo = cpu_to_le32((u32)addr);
		task_ctx_bdt++;
	पूर्ण
	वापस 0;

out3:
	क्रम (i = 0; i < task_ctx_arr_sz; i++) अणु
		अगर (hba->task_ctx[i]) अणु

			dma_मुक्त_coherent(&hba->pcidev->dev, PAGE_SIZE,
				hba->task_ctx[i], hba->task_ctx_dma[i]);
			hba->task_ctx[i] = शून्य;
		पूर्ण
	पूर्ण

	kमुक्त(hba->task_ctx_dma);
	hba->task_ctx_dma = शून्य;
out2:
	kमुक्त(hba->task_ctx);
	hba->task_ctx = शून्य;
out1:
	dma_मुक्त_coherent(&hba->pcidev->dev, PAGE_SIZE,
			hba->task_ctx_bd_tbl, hba->task_ctx_bd_dma);
	hba->task_ctx_bd_tbl = शून्य;
out:
	वापस rc;
पूर्ण

व्योम bnx2fc_मुक्त_task_ctx(काष्ठा bnx2fc_hba *hba)
अणु
	पूर्णांक task_ctx_arr_sz;
	पूर्णांक i;

	अगर (hba->task_ctx_bd_tbl) अणु
		dma_मुक्त_coherent(&hba->pcidev->dev, PAGE_SIZE,
				    hba->task_ctx_bd_tbl,
				    hba->task_ctx_bd_dma);
		hba->task_ctx_bd_tbl = शून्य;
	पूर्ण

	task_ctx_arr_sz = (hba->max_tasks / BNX2FC_TASKS_PER_PAGE);
	अगर (hba->task_ctx) अणु
		क्रम (i = 0; i < task_ctx_arr_sz; i++) अणु
			अगर (hba->task_ctx[i]) अणु
				dma_मुक्त_coherent(&hba->pcidev->dev, PAGE_SIZE,
						    hba->task_ctx[i],
						    hba->task_ctx_dma[i]);
				hba->task_ctx[i] = शून्य;
			पूर्ण
		पूर्ण
		kमुक्त(hba->task_ctx);
		hba->task_ctx = शून्य;
	पूर्ण

	kमुक्त(hba->task_ctx_dma);
	hba->task_ctx_dma = शून्य;
पूर्ण

अटल व्योम bnx2fc_मुक्त_hash_table(काष्ठा bnx2fc_hba *hba)
अणु
	पूर्णांक i;
	पूर्णांक segment_count;
	u32 *pbl;

	अगर (hba->hash_tbl_segments) अणु

		pbl = hba->hash_tbl_pbl;
		अगर (pbl) अणु
			segment_count = hba->hash_tbl_segment_count;
			क्रम (i = 0; i < segment_count; ++i) अणु
				dma_addr_t dma_address;

				dma_address = le32_to_cpu(*pbl);
				++pbl;
				dma_address += ((u64)le32_to_cpu(*pbl)) << 32;
				++pbl;
				dma_मुक्त_coherent(&hba->pcidev->dev,
						  BNX2FC_HASH_TBL_CHUNK_SIZE,
						  hba->hash_tbl_segments[i],
						  dma_address);
			पूर्ण
		पूर्ण

		kमुक्त(hba->hash_tbl_segments);
		hba->hash_tbl_segments = शून्य;
	पूर्ण

	अगर (hba->hash_tbl_pbl) अणु
		dma_मुक्त_coherent(&hba->pcidev->dev, PAGE_SIZE,
				    hba->hash_tbl_pbl,
				    hba->hash_tbl_pbl_dma);
		hba->hash_tbl_pbl = शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक bnx2fc_allocate_hash_table(काष्ठा bnx2fc_hba *hba)
अणु
	पूर्णांक i;
	पूर्णांक hash_table_size;
	पूर्णांक segment_count;
	पूर्णांक segment_array_size;
	पूर्णांक dma_segment_array_size;
	dma_addr_t *dma_segment_array;
	u32 *pbl;

	hash_table_size = BNX2FC_NUM_MAX_SESS * BNX2FC_MAX_ROWS_IN_HASH_TBL *
		माप(काष्ठा fcoe_hash_table_entry);

	segment_count = hash_table_size + BNX2FC_HASH_TBL_CHUNK_SIZE - 1;
	segment_count /= BNX2FC_HASH_TBL_CHUNK_SIZE;
	hba->hash_tbl_segment_count = segment_count;

	segment_array_size = segment_count * माप(*hba->hash_tbl_segments);
	hba->hash_tbl_segments = kzalloc(segment_array_size, GFP_KERNEL);
	अगर (!hba->hash_tbl_segments) अणु
		prपूर्णांकk(KERN_ERR PFX "hash table pointers alloc failed\n");
		वापस -ENOMEM;
	पूर्ण
	dma_segment_array_size = segment_count * माप(*dma_segment_array);
	dma_segment_array = kzalloc(dma_segment_array_size, GFP_KERNEL);
	अगर (!dma_segment_array) अणु
		prपूर्णांकk(KERN_ERR PFX "hash table pointers (dma) alloc failed\n");
		जाओ cleanup_ht;
	पूर्ण

	क्रम (i = 0; i < segment_count; ++i) अणु
		hba->hash_tbl_segments[i] = dma_alloc_coherent(&hba->pcidev->dev,
							       BNX2FC_HASH_TBL_CHUNK_SIZE,
							       &dma_segment_array[i],
							       GFP_KERNEL);
		अगर (!hba->hash_tbl_segments[i]) अणु
			prपूर्णांकk(KERN_ERR PFX "hash segment alloc failed\n");
			जाओ cleanup_dma;
		पूर्ण
	पूर्ण

	hba->hash_tbl_pbl = dma_alloc_coherent(&hba->pcidev->dev, PAGE_SIZE,
					       &hba->hash_tbl_pbl_dma,
					       GFP_KERNEL);
	अगर (!hba->hash_tbl_pbl) अणु
		prपूर्णांकk(KERN_ERR PFX "hash table pbl alloc failed\n");
		जाओ cleanup_dma;
	पूर्ण

	pbl = hba->hash_tbl_pbl;
	क्रम (i = 0; i < segment_count; ++i) अणु
		u64 paddr = dma_segment_array[i];
		*pbl = cpu_to_le32((u32) paddr);
		++pbl;
		*pbl = cpu_to_le32((u32) (paddr >> 32));
		++pbl;
	पूर्ण
	pbl = hba->hash_tbl_pbl;
	i = 0;
	जबतक (*pbl && *(pbl + 1)) अणु
		++pbl;
		++pbl;
		++i;
	पूर्ण
	kमुक्त(dma_segment_array);
	वापस 0;

cleanup_dma:
	क्रम (i = 0; i < segment_count; ++i) अणु
		अगर (hba->hash_tbl_segments[i])
			dma_मुक्त_coherent(&hba->pcidev->dev,
					    BNX2FC_HASH_TBL_CHUNK_SIZE,
					    hba->hash_tbl_segments[i],
					    dma_segment_array[i]);
	पूर्ण

	kमुक्त(dma_segment_array);

cleanup_ht:
	kमुक्त(hba->hash_tbl_segments);
	hba->hash_tbl_segments = शून्य;
	वापस -ENOMEM;
पूर्ण

/**
 * bnx2fc_setup_fw_resc - Allocate and map hash table and dummy buffer
 *
 * @hba:	Poपूर्णांकer to adapter काष्ठाure
 *
 */
पूर्णांक bnx2fc_setup_fw_resc(काष्ठा bnx2fc_hba *hba)
अणु
	u64 addr;
	u32 mem_size;
	पूर्णांक i;

	अगर (bnx2fc_allocate_hash_table(hba))
		वापस -ENOMEM;

	mem_size = BNX2FC_NUM_MAX_SESS * माप(काष्ठा regpair);
	hba->t2_hash_tbl_ptr = dma_alloc_coherent(&hba->pcidev->dev, mem_size,
						  &hba->t2_hash_tbl_ptr_dma,
						  GFP_KERNEL);
	अगर (!hba->t2_hash_tbl_ptr) अणु
		prपूर्णांकk(KERN_ERR PFX "unable to allocate t2 hash table ptr\n");
		bnx2fc_मुक्त_fw_resc(hba);
		वापस -ENOMEM;
	पूर्ण

	mem_size = BNX2FC_NUM_MAX_SESS *
				माप(काष्ठा fcoe_t2_hash_table_entry);
	hba->t2_hash_tbl = dma_alloc_coherent(&hba->pcidev->dev, mem_size,
					      &hba->t2_hash_tbl_dma,
					      GFP_KERNEL);
	अगर (!hba->t2_hash_tbl) अणु
		prपूर्णांकk(KERN_ERR PFX "unable to allocate t2 hash table\n");
		bnx2fc_मुक्त_fw_resc(hba);
		वापस -ENOMEM;
	पूर्ण
	क्रम (i = 0; i < BNX2FC_NUM_MAX_SESS; i++) अणु
		addr = (अचिन्हित दीर्घ) hba->t2_hash_tbl_dma +
			 ((i+1) * माप(काष्ठा fcoe_t2_hash_table_entry));
		hba->t2_hash_tbl[i].next.lo = addr & 0xffffffff;
		hba->t2_hash_tbl[i].next.hi = addr >> 32;
	पूर्ण

	hba->dummy_buffer = dma_alloc_coherent(&hba->pcidev->dev,
					       PAGE_SIZE, &hba->dummy_buf_dma,
					       GFP_KERNEL);
	अगर (!hba->dummy_buffer) अणु
		prपूर्णांकk(KERN_ERR PFX "unable to alloc MP Dummy Buffer\n");
		bnx2fc_मुक्त_fw_resc(hba);
		वापस -ENOMEM;
	पूर्ण

	hba->stats_buffer = dma_alloc_coherent(&hba->pcidev->dev, PAGE_SIZE,
					       &hba->stats_buf_dma,
					       GFP_KERNEL);
	अगर (!hba->stats_buffer) अणु
		prपूर्णांकk(KERN_ERR PFX "unable to alloc Stats Buffer\n");
		bnx2fc_मुक्त_fw_resc(hba);
		वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

व्योम bnx2fc_मुक्त_fw_resc(काष्ठा bnx2fc_hba *hba)
अणु
	u32 mem_size;

	अगर (hba->stats_buffer) अणु
		dma_मुक्त_coherent(&hba->pcidev->dev, PAGE_SIZE,
				  hba->stats_buffer, hba->stats_buf_dma);
		hba->stats_buffer = शून्य;
	पूर्ण

	अगर (hba->dummy_buffer) अणु
		dma_मुक्त_coherent(&hba->pcidev->dev, PAGE_SIZE,
				  hba->dummy_buffer, hba->dummy_buf_dma);
		hba->dummy_buffer = शून्य;
	पूर्ण

	अगर (hba->t2_hash_tbl_ptr) अणु
		mem_size = BNX2FC_NUM_MAX_SESS * माप(काष्ठा regpair);
		dma_मुक्त_coherent(&hba->pcidev->dev, mem_size,
				    hba->t2_hash_tbl_ptr,
				    hba->t2_hash_tbl_ptr_dma);
		hba->t2_hash_tbl_ptr = शून्य;
	पूर्ण

	अगर (hba->t2_hash_tbl) अणु
		mem_size = BNX2FC_NUM_MAX_SESS *
			    माप(काष्ठा fcoe_t2_hash_table_entry);
		dma_मुक्त_coherent(&hba->pcidev->dev, mem_size,
				    hba->t2_hash_tbl, hba->t2_hash_tbl_dma);
		hba->t2_hash_tbl = शून्य;
	पूर्ण
	bnx2fc_मुक्त_hash_table(hba);
पूर्ण
