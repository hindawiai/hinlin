<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * QLogic iSCSI Offload Driver
 * Copyright (c) 2016 Cavium Inc.
 */

#समावेश <linux/blkdev.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/अगर_ether.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <scsi/scsi_tcq.h>

#समावेश "qedi.h"
#समावेश "qedi_iscsi.h"
#समावेश "qedi_gbl.h"

पूर्णांक qedi_recover_all_conns(काष्ठा qedi_ctx *qedi)
अणु
	काष्ठा qedi_conn *qedi_conn;
	पूर्णांक i;

	क्रम (i = 0; i < qedi->max_active_conns; i++) अणु
		qedi_conn = qedi_get_conn_from_id(qedi, i);
		अगर (!qedi_conn)
			जारी;

		qedi_start_conn_recovery(qedi, qedi_conn);
	पूर्ण

	वापस SUCCESS;
पूर्ण

अटल पूर्णांक qedi_eh_host_reset(काष्ठा scsi_cmnd *cmd)
अणु
	काष्ठा Scsi_Host *shost = cmd->device->host;
	काष्ठा qedi_ctx *qedi;

	qedi = iscsi_host_priv(shost);

	वापस qedi_recover_all_conns(qedi);
पूर्ण

काष्ठा scsi_host_ढाँचा qedi_host_ढाँचा = अणु
	.module = THIS_MODULE,
	.name = "QLogic QEDI 25/40/100Gb iSCSI Initiator Driver",
	.proc_name = QEDI_MODULE_NAME,
	.queuecommand = iscsi_queuecommand,
	.eh_समयd_out = iscsi_eh_cmd_समयd_out,
	.eh_पात_handler = iscsi_eh_पात,
	.eh_device_reset_handler = iscsi_eh_device_reset,
	.eh_target_reset_handler = iscsi_eh_recover_target,
	.eh_host_reset_handler = qedi_eh_host_reset,
	.target_alloc = iscsi_target_alloc,
	.change_queue_depth = scsi_change_queue_depth,
	.can_queue = QEDI_MAX_ISCSI_TASK,
	.this_id = -1,
	.sg_tablesize = QEDI_ISCSI_MAX_BDS_PER_CMD,
	.max_sectors = 0xffff,
	.dma_boundary = QEDI_HW_DMA_BOUNDARY,
	.cmd_per_lun = 128,
	.shost_attrs = qedi_shost_attrs,
पूर्ण;

अटल व्योम qedi_conn_मुक्त_login_resources(काष्ठा qedi_ctx *qedi,
					   काष्ठा qedi_conn *qedi_conn)
अणु
	अगर (qedi_conn->gen_pdu.resp_bd_tbl) अणु
		dma_मुक्त_coherent(&qedi->pdev->dev, QEDI_PAGE_SIZE,
				  qedi_conn->gen_pdu.resp_bd_tbl,
				  qedi_conn->gen_pdu.resp_bd_dma);
		qedi_conn->gen_pdu.resp_bd_tbl = शून्य;
	पूर्ण

	अगर (qedi_conn->gen_pdu.req_bd_tbl) अणु
		dma_मुक्त_coherent(&qedi->pdev->dev, QEDI_PAGE_SIZE,
				  qedi_conn->gen_pdu.req_bd_tbl,
				  qedi_conn->gen_pdu.req_bd_dma);
		qedi_conn->gen_pdu.req_bd_tbl = शून्य;
	पूर्ण

	अगर (qedi_conn->gen_pdu.resp_buf) अणु
		dma_मुक्त_coherent(&qedi->pdev->dev,
				  ISCSI_DEF_MAX_RECV_SEG_LEN,
				  qedi_conn->gen_pdu.resp_buf,
				  qedi_conn->gen_pdu.resp_dma_addr);
		qedi_conn->gen_pdu.resp_buf = शून्य;
	पूर्ण

	अगर (qedi_conn->gen_pdu.req_buf) अणु
		dma_मुक्त_coherent(&qedi->pdev->dev,
				  ISCSI_DEF_MAX_RECV_SEG_LEN,
				  qedi_conn->gen_pdu.req_buf,
				  qedi_conn->gen_pdu.req_dma_addr);
		qedi_conn->gen_pdu.req_buf = शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक qedi_conn_alloc_login_resources(काष्ठा qedi_ctx *qedi,
					   काष्ठा qedi_conn *qedi_conn)
अणु
	qedi_conn->gen_pdu.req_buf =
		dma_alloc_coherent(&qedi->pdev->dev,
				   ISCSI_DEF_MAX_RECV_SEG_LEN,
				   &qedi_conn->gen_pdu.req_dma_addr,
				   GFP_KERNEL);
	अगर (!qedi_conn->gen_pdu.req_buf)
		जाओ login_req_buf_failure;

	qedi_conn->gen_pdu.req_buf_size = 0;
	qedi_conn->gen_pdu.req_wr_ptr = qedi_conn->gen_pdu.req_buf;

	qedi_conn->gen_pdu.resp_buf =
		dma_alloc_coherent(&qedi->pdev->dev,
				   ISCSI_DEF_MAX_RECV_SEG_LEN,
				   &qedi_conn->gen_pdu.resp_dma_addr,
				   GFP_KERNEL);
	अगर (!qedi_conn->gen_pdu.resp_buf)
		जाओ login_resp_buf_failure;

	qedi_conn->gen_pdu.resp_buf_size = ISCSI_DEF_MAX_RECV_SEG_LEN;
	qedi_conn->gen_pdu.resp_wr_ptr = qedi_conn->gen_pdu.resp_buf;

	qedi_conn->gen_pdu.req_bd_tbl =
		dma_alloc_coherent(&qedi->pdev->dev, QEDI_PAGE_SIZE,
				   &qedi_conn->gen_pdu.req_bd_dma, GFP_KERNEL);
	अगर (!qedi_conn->gen_pdu.req_bd_tbl)
		जाओ login_req_bd_tbl_failure;

	qedi_conn->gen_pdu.resp_bd_tbl =
		dma_alloc_coherent(&qedi->pdev->dev, QEDI_PAGE_SIZE,
				   &qedi_conn->gen_pdu.resp_bd_dma,
				   GFP_KERNEL);
	अगर (!qedi_conn->gen_pdu.resp_bd_tbl)
		जाओ login_resp_bd_tbl_failure;

	QEDI_INFO(&qedi->dbg_ctx, QEDI_LOG_SESS,
		  "Allocation successful, cid=0x%x\n",
		  qedi_conn->iscsi_conn_id);
	वापस 0;

login_resp_bd_tbl_failure:
	dma_मुक्त_coherent(&qedi->pdev->dev, QEDI_PAGE_SIZE,
			  qedi_conn->gen_pdu.req_bd_tbl,
			  qedi_conn->gen_pdu.req_bd_dma);
	qedi_conn->gen_pdu.req_bd_tbl = शून्य;

login_req_bd_tbl_failure:
	dma_मुक्त_coherent(&qedi->pdev->dev, ISCSI_DEF_MAX_RECV_SEG_LEN,
			  qedi_conn->gen_pdu.resp_buf,
			  qedi_conn->gen_pdu.resp_dma_addr);
	qedi_conn->gen_pdu.resp_buf = शून्य;
login_resp_buf_failure:
	dma_मुक्त_coherent(&qedi->pdev->dev, ISCSI_DEF_MAX_RECV_SEG_LEN,
			  qedi_conn->gen_pdu.req_buf,
			  qedi_conn->gen_pdu.req_dma_addr);
	qedi_conn->gen_pdu.req_buf = शून्य;
login_req_buf_failure:
	iscsi_conn_prपूर्णांकk(KERN_ERR, qedi_conn->cls_conn->dd_data,
			  "login resource alloc failed!!\n");
	वापस -ENOMEM;
पूर्ण

अटल व्योम qedi_destroy_cmd_pool(काष्ठा qedi_ctx *qedi,
				  काष्ठा iscsi_session *session)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < session->cmds_max; i++) अणु
		काष्ठा iscsi_task *task = session->cmds[i];
		काष्ठा qedi_cmd *cmd = task->dd_data;

		अगर (cmd->io_tbl.sge_tbl)
			dma_मुक्त_coherent(&qedi->pdev->dev,
					  QEDI_ISCSI_MAX_BDS_PER_CMD *
					  माप(काष्ठा scsi_sge),
					  cmd->io_tbl.sge_tbl,
					  cmd->io_tbl.sge_tbl_dma);

		अगर (cmd->sense_buffer)
			dma_मुक्त_coherent(&qedi->pdev->dev,
					  SCSI_SENSE_BUFFERSIZE,
					  cmd->sense_buffer,
					  cmd->sense_buffer_dma);
	पूर्ण
पूर्ण

अटल पूर्णांक qedi_alloc_sget(काष्ठा qedi_ctx *qedi, काष्ठा iscsi_session *session,
			   काष्ठा qedi_cmd *cmd)
अणु
	काष्ठा qedi_io_bdt *io = &cmd->io_tbl;
	काष्ठा scsi_sge *sge;

	io->sge_tbl = dma_alloc_coherent(&qedi->pdev->dev,
					 QEDI_ISCSI_MAX_BDS_PER_CMD *
					 माप(*sge),
					 &io->sge_tbl_dma, GFP_KERNEL);
	अगर (!io->sge_tbl) अणु
		iscsi_session_prपूर्णांकk(KERN_ERR, session,
				     "Could not allocate BD table.\n");
		वापस -ENOMEM;
	पूर्ण

	io->sge_valid = 0;
	वापस 0;
पूर्ण

अटल पूर्णांक qedi_setup_cmd_pool(काष्ठा qedi_ctx *qedi,
			       काष्ठा iscsi_session *session)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < session->cmds_max; i++) अणु
		काष्ठा iscsi_task *task = session->cmds[i];
		काष्ठा qedi_cmd *cmd = task->dd_data;

		task->hdr = &cmd->hdr;
		task->hdr_max = माप(काष्ठा iscsi_hdr);

		अगर (qedi_alloc_sget(qedi, session, cmd))
			जाओ मुक्त_sमाला_लो;

		cmd->sense_buffer = dma_alloc_coherent(&qedi->pdev->dev,
						       SCSI_SENSE_BUFFERSIZE,
						       &cmd->sense_buffer_dma,
						       GFP_KERNEL);
		अगर (!cmd->sense_buffer)
			जाओ मुक्त_sमाला_लो;
	पूर्ण

	वापस 0;

मुक्त_sमाला_लो:
	qedi_destroy_cmd_pool(qedi, session);
	वापस -ENOMEM;
पूर्ण

अटल काष्ठा iscsi_cls_session *
qedi_session_create(काष्ठा iscsi_endpoपूर्णांक *ep, u16 cmds_max,
		    u16 qdepth, uपूर्णांक32_t initial_cmdsn)
अणु
	काष्ठा Scsi_Host *shost;
	काष्ठा iscsi_cls_session *cls_session;
	काष्ठा qedi_ctx *qedi;
	काष्ठा qedi_endpoपूर्णांक *qedi_ep;

	अगर (!ep)
		वापस शून्य;

	qedi_ep = ep->dd_data;
	shost = qedi_ep->qedi->shost;
	qedi = iscsi_host_priv(shost);

	अगर (cmds_max > qedi->max_sqes)
		cmds_max = qedi->max_sqes;
	अन्यथा अगर (cmds_max < QEDI_SQ_WQES_MIN)
		cmds_max = QEDI_SQ_WQES_MIN;

	cls_session = iscsi_session_setup(&qedi_iscsi_transport, shost,
					  cmds_max, 0, माप(काष्ठा qedi_cmd),
					  initial_cmdsn, ISCSI_MAX_TARGET);
	अगर (!cls_session) अणु
		QEDI_ERR(&qedi->dbg_ctx,
			 "Failed to setup session for ep=%p\n", qedi_ep);
		वापस शून्य;
	पूर्ण

	अगर (qedi_setup_cmd_pool(qedi, cls_session->dd_data)) अणु
		QEDI_ERR(&qedi->dbg_ctx,
			 "Failed to setup cmd pool for ep=%p\n", qedi_ep);
		जाओ session_tearकरोwn;
	पूर्ण

	वापस cls_session;

session_tearकरोwn:
	iscsi_session_tearकरोwn(cls_session);
	वापस शून्य;
पूर्ण

अटल व्योम qedi_session_destroy(काष्ठा iscsi_cls_session *cls_session)
अणु
	काष्ठा iscsi_session *session = cls_session->dd_data;
	काष्ठा Scsi_Host *shost = iscsi_session_to_shost(cls_session);
	काष्ठा qedi_ctx *qedi = iscsi_host_priv(shost);

	qedi_destroy_cmd_pool(qedi, session);
	iscsi_session_tearकरोwn(cls_session);
पूर्ण

अटल काष्ठा iscsi_cls_conn *
qedi_conn_create(काष्ठा iscsi_cls_session *cls_session, uपूर्णांक32_t cid)
अणु
	काष्ठा Scsi_Host *shost = iscsi_session_to_shost(cls_session);
	काष्ठा qedi_ctx *qedi = iscsi_host_priv(shost);
	काष्ठा iscsi_cls_conn *cls_conn;
	काष्ठा qedi_conn *qedi_conn;
	काष्ठा iscsi_conn *conn;

	cls_conn = iscsi_conn_setup(cls_session, माप(*qedi_conn),
				    cid);
	अगर (!cls_conn) अणु
		QEDI_ERR(&qedi->dbg_ctx,
			 "conn_new: iscsi conn setup failed, cid=0x%x, cls_sess=%p!\n",
			 cid, cls_session);
		वापस शून्य;
	पूर्ण

	conn = cls_conn->dd_data;
	qedi_conn = conn->dd_data;
	qedi_conn->cls_conn = cls_conn;
	qedi_conn->qedi = qedi;
	qedi_conn->ep = शून्य;
	qedi_conn->active_cmd_count = 0;
	INIT_LIST_HEAD(&qedi_conn->active_cmd_list);
	spin_lock_init(&qedi_conn->list_lock);

	अगर (qedi_conn_alloc_login_resources(qedi, qedi_conn)) अणु
		iscsi_conn_prपूर्णांकk(KERN_ALERT, conn,
				  "conn_new: login resc alloc failed, cid=0x%x, cls_sess=%p!!\n",
				   cid, cls_session);
		जाओ मुक्त_conn;
	पूर्ण

	वापस cls_conn;

मुक्त_conn:
	iscsi_conn_tearकरोwn(cls_conn);
	वापस शून्य;
पूर्ण

व्योम qedi_mark_device_missing(काष्ठा iscsi_cls_session *cls_session)
अणु
	iscsi_block_session(cls_session);
पूर्ण

व्योम qedi_mark_device_available(काष्ठा iscsi_cls_session *cls_session)
अणु
	iscsi_unblock_session(cls_session);
पूर्ण

अटल पूर्णांक qedi_bind_conn_to_iscsi_cid(काष्ठा qedi_ctx *qedi,
				       काष्ठा qedi_conn *qedi_conn)
अणु
	u32 iscsi_cid = qedi_conn->iscsi_conn_id;

	अगर (qedi->cid_que.conn_cid_tbl[iscsi_cid]) अणु
		iscsi_conn_prपूर्णांकk(KERN_ALERT, qedi_conn->cls_conn->dd_data,
				  "conn bind - entry #%d not free\n",
				  iscsi_cid);
		वापस -EBUSY;
	पूर्ण

	qedi->cid_que.conn_cid_tbl[iscsi_cid] = qedi_conn;
	वापस 0;
पूर्ण

काष्ठा qedi_conn *qedi_get_conn_from_id(काष्ठा qedi_ctx *qedi, u32 iscsi_cid)
अणु
	अगर (!qedi->cid_que.conn_cid_tbl) अणु
		QEDI_ERR(&qedi->dbg_ctx, "missing conn<->cid table\n");
		वापस शून्य;

	पूर्ण अन्यथा अगर (iscsi_cid >= qedi->max_active_conns) अणु
		QEDI_ERR(&qedi->dbg_ctx, "wrong cid #%d\n", iscsi_cid);
		वापस शून्य;
	पूर्ण
	वापस qedi->cid_que.conn_cid_tbl[iscsi_cid];
पूर्ण

अटल पूर्णांक qedi_conn_bind(काष्ठा iscsi_cls_session *cls_session,
			  काष्ठा iscsi_cls_conn *cls_conn,
			  u64 transport_fd, पूर्णांक is_leading)
अणु
	काष्ठा iscsi_conn *conn = cls_conn->dd_data;
	काष्ठा qedi_conn *qedi_conn = conn->dd_data;
	काष्ठा Scsi_Host *shost = iscsi_session_to_shost(cls_session);
	काष्ठा qedi_ctx *qedi = iscsi_host_priv(shost);
	काष्ठा qedi_endpoपूर्णांक *qedi_ep;
	काष्ठा iscsi_endpoपूर्णांक *ep;

	ep = iscsi_lookup_endpoपूर्णांक(transport_fd);
	अगर (!ep)
		वापस -EINVAL;

	qedi_ep = ep->dd_data;
	अगर ((qedi_ep->state == EP_STATE_TCP_FIN_RCVD) ||
	    (qedi_ep->state == EP_STATE_TCP_RST_RCVD))
		वापस -EINVAL;

	अगर (iscsi_conn_bind(cls_session, cls_conn, is_leading))
		वापस -EINVAL;

	qedi_ep->conn = qedi_conn;
	qedi_conn->ep = qedi_ep;
	qedi_conn->iscsi_ep = ep;
	qedi_conn->iscsi_conn_id = qedi_ep->iscsi_cid;
	qedi_conn->fw_cid = qedi_ep->fw_cid;
	qedi_conn->cmd_cleanup_req = 0;
	qedi_conn->cmd_cleanup_cmpl = 0;

	अगर (qedi_bind_conn_to_iscsi_cid(qedi, qedi_conn))
		वापस -EINVAL;

	spin_lock_init(&qedi_conn->पंचांगf_work_lock);
	INIT_LIST_HEAD(&qedi_conn->पंचांगf_work_list);
	init_रुकोqueue_head(&qedi_conn->रुको_queue);
	वापस 0;
पूर्ण

अटल पूर्णांक qedi_iscsi_update_conn(काष्ठा qedi_ctx *qedi,
				  काष्ठा qedi_conn *qedi_conn)
अणु
	काष्ठा qed_iscsi_params_update *conn_info;
	काष्ठा iscsi_cls_conn *cls_conn = qedi_conn->cls_conn;
	काष्ठा iscsi_conn *conn = cls_conn->dd_data;
	काष्ठा qedi_endpoपूर्णांक *qedi_ep;
	पूर्णांक rval;

	qedi_ep = qedi_conn->ep;

	conn_info = kzalloc(माप(*conn_info), GFP_KERNEL);
	अगर (!conn_info) अणु
		QEDI_ERR(&qedi->dbg_ctx, "memory alloc failed\n");
		वापस -ENOMEM;
	पूर्ण

	conn_info->update_flag = 0;

	अगर (conn->hdrdgst_en)
		SET_FIELD(conn_info->update_flag,
			  ISCSI_CONN_UPDATE_RAMROD_PARAMS_HD_EN, true);
	अगर (conn->datadgst_en)
		SET_FIELD(conn_info->update_flag,
			  ISCSI_CONN_UPDATE_RAMROD_PARAMS_DD_EN, true);
	अगर (conn->session->initial_r2t_en)
		SET_FIELD(conn_info->update_flag,
			  ISCSI_CONN_UPDATE_RAMROD_PARAMS_INITIAL_R2T,
			  true);
	अगर (conn->session->imm_data_en)
		SET_FIELD(conn_info->update_flag,
			  ISCSI_CONN_UPDATE_RAMROD_PARAMS_IMMEDIATE_DATA,
			  true);

	conn_info->max_seq_size = conn->session->max_burst;
	conn_info->max_recv_pdu_length = conn->max_recv_dlength;
	conn_info->max_send_pdu_length = conn->max_xmit_dlength;
	conn_info->first_seq_length = conn->session->first_burst;
	conn_info->exp_stat_sn = conn->exp_statsn;

	rval = qedi_ops->update_conn(qedi->cdev, qedi_ep->handle,
				     conn_info);
	अगर (rval) अणु
		rval = -ENXIO;
		QEDI_ERR(&qedi->dbg_ctx, "Could not update connection\n");
	पूर्ण

	kमुक्त(conn_info);
	वापस rval;
पूर्ण

अटल u16 qedi_calc_mss(u16 pmtu, u8 is_ipv6, u8 tcp_ts_en, u8 vlan_en)
अणु
	u16 mss = 0;
	u16 hdrs = TCP_HDR_LEN;

	अगर (is_ipv6)
		hdrs += IPV6_HDR_LEN;
	अन्यथा
		hdrs += IPV4_HDR_LEN;

	mss = pmtu - hdrs;

	अगर (!mss)
		mss = DEF_MSS;

	वापस mss;
पूर्ण

अटल पूर्णांक qedi_iscsi_offload_conn(काष्ठा qedi_endpoपूर्णांक *qedi_ep)
अणु
	काष्ठा qedi_ctx *qedi = qedi_ep->qedi;
	काष्ठा qed_iscsi_params_offload *conn_info;
	पूर्णांक rval;
	पूर्णांक i;

	conn_info = kzalloc(माप(*conn_info), GFP_KERNEL);
	अगर (!conn_info) अणु
		QEDI_ERR(&qedi->dbg_ctx,
			 "Failed to allocate memory ep=%p\n", qedi_ep);
		वापस -ENOMEM;
	पूर्ण

	ether_addr_copy(conn_info->src.mac, qedi_ep->src_mac);
	ether_addr_copy(conn_info->dst.mac, qedi_ep->dst_mac);

	conn_info->src.ip[0] = ntohl(qedi_ep->src_addr[0]);
	conn_info->dst.ip[0] = ntohl(qedi_ep->dst_addr[0]);

	अगर (qedi_ep->ip_type == TCP_IPV4) अणु
		conn_info->ip_version = 0;
		QEDI_INFO(&qedi->dbg_ctx, QEDI_LOG_CONN,
			  "After ntohl: src_addr=%pI4, dst_addr=%pI4\n",
			  qedi_ep->src_addr, qedi_ep->dst_addr);
	पूर्ण अन्यथा अणु
		क्रम (i = 1; i < 4; i++) अणु
			conn_info->src.ip[i] = ntohl(qedi_ep->src_addr[i]);
			conn_info->dst.ip[i] = ntohl(qedi_ep->dst_addr[i]);
		पूर्ण

		conn_info->ip_version = 1;
		QEDI_INFO(&qedi->dbg_ctx, QEDI_LOG_CONN,
			  "After ntohl: src_addr=%pI6, dst_addr=%pI6\n",
			  qedi_ep->src_addr, qedi_ep->dst_addr);
	पूर्ण

	conn_info->src.port = qedi_ep->src_port;
	conn_info->dst.port = qedi_ep->dst_port;

	conn_info->layer_code = ISCSI_SLOW_PATH_LAYER_CODE;
	conn_info->sq_pbl_addr = qedi_ep->sq_pbl_dma;
	conn_info->vlan_id = qedi_ep->vlan_id;

	SET_FIELD(conn_info->tcp_flags, TCP_OFFLOAD_PARAMS_TS_EN, 1);
	SET_FIELD(conn_info->tcp_flags, TCP_OFFLOAD_PARAMS_DA_EN, 1);
	SET_FIELD(conn_info->tcp_flags, TCP_OFFLOAD_PARAMS_DA_CNT_EN, 1);
	SET_FIELD(conn_info->tcp_flags, TCP_OFFLOAD_PARAMS_KA_EN, 1);

	conn_info->शेष_cq = (qedi_ep->fw_cid % qedi->num_queues);

	conn_info->ka_max_probe_cnt = DEF_KA_MAX_PROBE_COUNT;
	conn_info->dup_ack_theshold = 3;
	conn_info->rcv_wnd = 65535;

	conn_info->ss_thresh = 65535;
	conn_info->srtt = 300;
	conn_info->rtt_var = 150;
	conn_info->flow_label = 0;
	conn_info->ka_समयout = DEF_KA_TIMEOUT;
	conn_info->ka_पूर्णांकerval = DEF_KA_INTERVAL;
	conn_info->max_rt_समय = DEF_MAX_RT_TIME;
	conn_info->ttl = DEF_TTL;
	conn_info->tos_or_tc = DEF_TOS;
	conn_info->remote_port = qedi_ep->dst_port;
	conn_info->local_port = qedi_ep->src_port;

	conn_info->mss = qedi_calc_mss(qedi_ep->pmtu,
				       (qedi_ep->ip_type == TCP_IPV6),
				       1, (qedi_ep->vlan_id != 0));

	conn_info->cwnd = DEF_MAX_CWND * conn_info->mss;
	conn_info->rcv_wnd_scale = 4;
	conn_info->da_समयout_value = 200;
	conn_info->ack_frequency = 2;

	QEDI_INFO(&qedi->dbg_ctx, QEDI_LOG_INFO,
		  "Default cq index [%d], mss [%d]\n",
		  conn_info->शेष_cq, conn_info->mss);

	rval = qedi_ops->offload_conn(qedi->cdev, qedi_ep->handle, conn_info);
	अगर (rval)
		QEDI_ERR(&qedi->dbg_ctx, "offload_conn returned %d, ep=%p\n",
			 rval, qedi_ep);

	kमुक्त(conn_info);
	वापस rval;
पूर्ण

अटल पूर्णांक qedi_conn_start(काष्ठा iscsi_cls_conn *cls_conn)
अणु
	काष्ठा iscsi_conn *conn = cls_conn->dd_data;
	काष्ठा qedi_conn *qedi_conn = conn->dd_data;
	काष्ठा qedi_ctx *qedi;
	पूर्णांक rval;

	qedi = qedi_conn->qedi;

	rval = qedi_iscsi_update_conn(qedi, qedi_conn);
	अगर (rval) अणु
		iscsi_conn_prपूर्णांकk(KERN_ALERT, conn,
				  "conn_start: FW offload conn failed.\n");
		rval = -EINVAL;
		जाओ start_err;
	पूर्ण

	clear_bit(QEDI_CONN_FW_CLEANUP, &qedi_conn->flags);
	qedi_conn->abrt_conn = 0;

	rval = iscsi_conn_start(cls_conn);
	अगर (rval) अणु
		iscsi_conn_prपूर्णांकk(KERN_ALERT, conn,
				  "iscsi_conn_start: FW offload conn failed!!\n");
	पूर्ण

start_err:
	वापस rval;
पूर्ण

अटल व्योम qedi_conn_destroy(काष्ठा iscsi_cls_conn *cls_conn)
अणु
	काष्ठा iscsi_conn *conn = cls_conn->dd_data;
	काष्ठा qedi_conn *qedi_conn = conn->dd_data;
	काष्ठा Scsi_Host *shost;
	काष्ठा qedi_ctx *qedi;

	shost = iscsi_session_to_shost(iscsi_conn_to_session(cls_conn));
	qedi = iscsi_host_priv(shost);

	qedi_conn_मुक्त_login_resources(qedi, qedi_conn);
	iscsi_conn_tearकरोwn(cls_conn);
पूर्ण

अटल पूर्णांक qedi_ep_get_param(काष्ठा iscsi_endpoपूर्णांक *ep,
			     क्रमागत iscsi_param param, अक्षर *buf)
अणु
	काष्ठा qedi_endpoपूर्णांक *qedi_ep = ep->dd_data;
	पूर्णांक len;

	अगर (!qedi_ep)
		वापस -ENOTCONN;

	चयन (param) अणु
	हाल ISCSI_PARAM_CONN_PORT:
		len = प्र_लिखो(buf, "%hu\n", qedi_ep->dst_port);
		अवरोध;
	हाल ISCSI_PARAM_CONN_ADDRESS:
		अगर (qedi_ep->ip_type == TCP_IPV4)
			len = प्र_लिखो(buf, "%pI4\n", qedi_ep->dst_addr);
		अन्यथा
			len = प्र_लिखो(buf, "%pI6\n", qedi_ep->dst_addr);
		अवरोध;
	शेष:
		वापस -ENOTCONN;
	पूर्ण

	वापस len;
पूर्ण

अटल पूर्णांक qedi_host_get_param(काष्ठा Scsi_Host *shost,
			       क्रमागत iscsi_host_param param, अक्षर *buf)
अणु
	काष्ठा qedi_ctx *qedi;
	पूर्णांक len;

	qedi = iscsi_host_priv(shost);

	चयन (param) अणु
	हाल ISCSI_HOST_PARAM_HWADDRESS:
		len = sysfs_क्रमmat_mac(buf, qedi->mac, 6);
		अवरोध;
	हाल ISCSI_HOST_PARAM_NETDEV_NAME:
		len = प्र_लिखो(buf, "host%d\n", shost->host_no);
		अवरोध;
	हाल ISCSI_HOST_PARAM_IPADDRESS:
		अगर (qedi->ip_type == TCP_IPV4)
			len = प्र_लिखो(buf, "%pI4\n", qedi->src_ip);
		अन्यथा
			len = प्र_लिखो(buf, "%pI6\n", qedi->src_ip);
		अवरोध;
	शेष:
		वापस iscsi_host_get_param(shost, param, buf);
	पूर्ण

	वापस len;
पूर्ण

अटल व्योम qedi_conn_get_stats(काष्ठा iscsi_cls_conn *cls_conn,
				काष्ठा iscsi_stats *stats)
अणु
	काष्ठा iscsi_conn *conn = cls_conn->dd_data;
	काष्ठा qed_iscsi_stats iscsi_stats;
	काष्ठा Scsi_Host *shost;
	काष्ठा qedi_ctx *qedi;

	shost = iscsi_session_to_shost(iscsi_conn_to_session(cls_conn));
	qedi = iscsi_host_priv(shost);
	qedi_ops->get_stats(qedi->cdev, &iscsi_stats);

	conn->txdata_octets = iscsi_stats.iscsi_tx_bytes_cnt;
	conn->rxdata_octets = iscsi_stats.iscsi_rx_bytes_cnt;
	conn->dataout_pdus_cnt = (uपूर्णांक32_t)iscsi_stats.iscsi_tx_data_pdu_cnt;
	conn->datain_pdus_cnt = (uपूर्णांक32_t)iscsi_stats.iscsi_rx_data_pdu_cnt;
	conn->r2t_pdus_cnt = (uपूर्णांक32_t)iscsi_stats.iscsi_rx_r2t_pdu_cnt;

	stats->txdata_octets = conn->txdata_octets;
	stats->rxdata_octets = conn->rxdata_octets;
	stats->scsicmd_pdus = conn->scsicmd_pdus_cnt;
	stats->dataout_pdus = conn->dataout_pdus_cnt;
	stats->scsirsp_pdus = conn->scsirsp_pdus_cnt;
	stats->datain_pdus = conn->datain_pdus_cnt;
	stats->r2t_pdus = conn->r2t_pdus_cnt;
	stats->पंचांगfcmd_pdus = conn->पंचांगfcmd_pdus_cnt;
	stats->पंचांगfrsp_pdus = conn->पंचांगfrsp_pdus_cnt;
	stats->digest_err = 0;
	stats->समयout_err = 0;
	म_नकल(stats->custom[0].desc, "eh_abort_cnt");
	stats->custom[0].value = conn->eh_पात_cnt;
	stats->custom_length = 1;
पूर्ण

अटल व्योम qedi_iscsi_prep_generic_pdu_bd(काष्ठा qedi_conn *qedi_conn)
अणु
	काष्ठा scsi_sge *bd_tbl;

	bd_tbl = (काष्ठा scsi_sge *)qedi_conn->gen_pdu.req_bd_tbl;

	bd_tbl->sge_addr.hi =
		(u32)((u64)qedi_conn->gen_pdu.req_dma_addr >> 32);
	bd_tbl->sge_addr.lo = (u32)qedi_conn->gen_pdu.req_dma_addr;
	bd_tbl->sge_len = qedi_conn->gen_pdu.req_wr_ptr -
				qedi_conn->gen_pdu.req_buf;
	bd_tbl = (काष्ठा scsi_sge  *)qedi_conn->gen_pdu.resp_bd_tbl;
	bd_tbl->sge_addr.hi =
			(u32)((u64)qedi_conn->gen_pdu.resp_dma_addr >> 32);
	bd_tbl->sge_addr.lo = (u32)qedi_conn->gen_pdu.resp_dma_addr;
	bd_tbl->sge_len = ISCSI_DEF_MAX_RECV_SEG_LEN;
पूर्ण

अटल पूर्णांक qedi_iscsi_send_generic_request(काष्ठा iscsi_task *task)
अणु
	काष्ठा qedi_cmd *cmd = task->dd_data;
	काष्ठा qedi_conn *qedi_conn = cmd->conn;
	अक्षर *buf;
	पूर्णांक data_len;
	पूर्णांक rc = 0;

	qedi_iscsi_prep_generic_pdu_bd(qedi_conn);
	चयन (task->hdr->opcode & ISCSI_OPCODE_MASK) अणु
	हाल ISCSI_OP_LOGIN:
		qedi_send_iscsi_login(qedi_conn, task);
		अवरोध;
	हाल ISCSI_OP_NOOP_OUT:
		data_len = qedi_conn->gen_pdu.req_buf_size;
		buf = qedi_conn->gen_pdu.req_buf;
		अगर (data_len)
			rc = qedi_send_iscsi_nopout(qedi_conn, task,
						    buf, data_len, 1);
		अन्यथा
			rc = qedi_send_iscsi_nopout(qedi_conn, task,
						    शून्य, 0, 1);
		अवरोध;
	हाल ISCSI_OP_LOGOUT:
		rc = qedi_send_iscsi_logout(qedi_conn, task);
		अवरोध;
	हाल ISCSI_OP_SCSI_TMFUNC:
		rc = qedi_iscsi_पात_work(qedi_conn, task);
		अवरोध;
	हाल ISCSI_OP_TEXT:
		rc = qedi_send_iscsi_text(qedi_conn, task);
		अवरोध;
	शेष:
		iscsi_conn_prपूर्णांकk(KERN_ALERT, qedi_conn->cls_conn->dd_data,
				  "unsupported op 0x%x\n", task->hdr->opcode);
	पूर्ण

	वापस rc;
पूर्ण

अटल पूर्णांक qedi_mtask_xmit(काष्ठा iscsi_conn *conn, काष्ठा iscsi_task *task)
अणु
	काष्ठा qedi_conn *qedi_conn = conn->dd_data;
	काष्ठा qedi_cmd *cmd = task->dd_data;

	स_रखो(qedi_conn->gen_pdu.req_buf, 0, ISCSI_DEF_MAX_RECV_SEG_LEN);

	qedi_conn->gen_pdu.req_buf_size = task->data_count;

	अगर (task->data_count) अणु
		स_नकल(qedi_conn->gen_pdu.req_buf, task->data,
		       task->data_count);
		qedi_conn->gen_pdu.req_wr_ptr =
			qedi_conn->gen_pdu.req_buf + task->data_count;
	पूर्ण

	cmd->conn = conn->dd_data;
	cmd->scsi_cmd = शून्य;
	वापस qedi_iscsi_send_generic_request(task);
पूर्ण

अटल पूर्णांक qedi_task_xmit(काष्ठा iscsi_task *task)
अणु
	काष्ठा iscsi_conn *conn = task->conn;
	काष्ठा qedi_conn *qedi_conn = conn->dd_data;
	काष्ठा qedi_cmd *cmd = task->dd_data;
	काष्ठा scsi_cmnd *sc = task->sc;

	अगर (test_bit(QEDI_IN_SHUTDOWN, &qedi_conn->qedi->flags))
		वापस -ENODEV;

	cmd->state = 0;
	cmd->task = शून्य;
	cmd->use_slowpath = false;
	cmd->conn = qedi_conn;
	cmd->task = task;
	cmd->io_cmd_in_list = false;
	INIT_LIST_HEAD(&cmd->io_cmd);

	अगर (!sc)
		वापस qedi_mtask_xmit(conn, task);

	cmd->scsi_cmd = sc;
	वापस qedi_iscsi_send_ioreq(task);
पूर्ण

अटल काष्ठा iscsi_endpoपूर्णांक *
qedi_ep_connect(काष्ठा Scsi_Host *shost, काष्ठा sockaddr *dst_addr,
		पूर्णांक non_blocking)
अणु
	काष्ठा qedi_ctx *qedi;
	काष्ठा iscsi_endpoपूर्णांक *ep;
	काष्ठा qedi_endpoपूर्णांक *qedi_ep;
	काष्ठा sockaddr_in *addr;
	काष्ठा sockaddr_in6 *addr6;
	काष्ठा iscsi_path path_req;
	u32 msg_type = ISCSI_KEVENT_IF_DOWN;
	u32 iscsi_cid = QEDI_CID_RESERVED;
	u16 len = 0;
	अक्षर *buf = शून्य;
	पूर्णांक ret, पंचांगp;

	अगर (!shost) अणु
		ret = -ENXIO;
		QEDI_ERR(शून्य, "shost is NULL\n");
		वापस ERR_PTR(ret);
	पूर्ण

	अगर (qedi_करो_not_recover) अणु
		ret = -ENOMEM;
		वापस ERR_PTR(ret);
	पूर्ण

	qedi = iscsi_host_priv(shost);

	अगर (test_bit(QEDI_IN_OFFLINE, &qedi->flags) ||
	    test_bit(QEDI_IN_RECOVERY, &qedi->flags)) अणु
		ret = -ENOMEM;
		वापस ERR_PTR(ret);
	पूर्ण

	अगर (atomic_पढ़ो(&qedi->link_state) != QEDI_LINK_UP) अणु
		QEDI_WARN(&qedi->dbg_ctx, "qedi link down\n");
		वापस ERR_PTR(-ENXIO);
	पूर्ण

	ep = iscsi_create_endpoपूर्णांक(माप(काष्ठा qedi_endpoपूर्णांक));
	अगर (!ep) अणु
		QEDI_ERR(&qedi->dbg_ctx, "endpoint create fail\n");
		ret = -ENOMEM;
		वापस ERR_PTR(ret);
	पूर्ण
	qedi_ep = ep->dd_data;
	स_रखो(qedi_ep, 0, माप(काष्ठा qedi_endpoपूर्णांक));
	qedi_ep->state = EP_STATE_IDLE;
	qedi_ep->iscsi_cid = (u32)-1;
	qedi_ep->qedi = qedi;

	अगर (dst_addr->sa_family == AF_INET) अणु
		addr = (काष्ठा sockaddr_in *)dst_addr;
		स_नकल(qedi_ep->dst_addr, &addr->sin_addr.s_addr,
		       माप(काष्ठा in_addr));
		qedi_ep->dst_port = ntohs(addr->sin_port);
		qedi_ep->ip_type = TCP_IPV4;
		QEDI_INFO(&qedi->dbg_ctx, QEDI_LOG_CONN,
			  "dst_addr=%pI4, dst_port=%u\n",
			  qedi_ep->dst_addr, qedi_ep->dst_port);
	पूर्ण अन्यथा अगर (dst_addr->sa_family == AF_INET6) अणु
		addr6 = (काष्ठा sockaddr_in6 *)dst_addr;
		स_नकल(qedi_ep->dst_addr, &addr6->sin6_addr,
		       माप(काष्ठा in6_addr));
		qedi_ep->dst_port = ntohs(addr6->sin6_port);
		qedi_ep->ip_type = TCP_IPV6;
		QEDI_INFO(&qedi->dbg_ctx, QEDI_LOG_CONN,
			  "dst_addr=%pI6, dst_port=%u\n",
			  qedi_ep->dst_addr, qedi_ep->dst_port);
	पूर्ण अन्यथा अणु
		QEDI_ERR(&qedi->dbg_ctx, "Invalid endpoint\n");
	पूर्ण

	ret = qedi_alloc_sq(qedi, qedi_ep);
	अगर (ret)
		जाओ ep_conn_निकास;

	ret = qedi_ops->acquire_conn(qedi->cdev, &qedi_ep->handle,
				     &qedi_ep->fw_cid, &qedi_ep->p_करोorbell);

	अगर (ret) अणु
		QEDI_ERR(&qedi->dbg_ctx, "Could not acquire connection\n");
		ret = -ENXIO;
		जाओ ep_मुक्त_sq;
	पूर्ण

	iscsi_cid = qedi_ep->handle;
	qedi_ep->iscsi_cid = iscsi_cid;

	init_रुकोqueue_head(&qedi_ep->ofld_रुको);
	init_रुकोqueue_head(&qedi_ep->tcp_ofld_रुको);
	qedi_ep->state = EP_STATE_OFLDCONN_START;
	qedi->ep_tbl[iscsi_cid] = qedi_ep;

	buf = (अक्षर *)&path_req;
	len = माप(path_req);
	स_रखो(&path_req, 0, len);

	msg_type = ISCSI_KEVENT_PATH_REQ;
	path_req.handle = (u64)qedi_ep->iscsi_cid;
	path_req.pmtu = qedi->ll2_mtu;
	qedi_ep->pmtu = qedi->ll2_mtu;
	अगर (qedi_ep->ip_type == TCP_IPV4) अणु
		स_नकल(&path_req.dst.v4_addr, &qedi_ep->dst_addr,
		       माप(काष्ठा in_addr));
		path_req.ip_addr_len = 4;
	पूर्ण अन्यथा अणु
		स_नकल(&path_req.dst.v6_addr, &qedi_ep->dst_addr,
		       माप(काष्ठा in6_addr));
		path_req.ip_addr_len = 16;
	पूर्ण

	ret = iscsi_offload_mesg(shost, &qedi_iscsi_transport, msg_type, buf,
				 len);
	अगर (ret) अणु
		QEDI_ERR(&qedi->dbg_ctx,
			 "iscsi_offload_mesg() failed for cid=0x%x ret=%d\n",
			 iscsi_cid, ret);
		जाओ ep_rel_conn;
	पूर्ण

	atomic_inc(&qedi->num_offloads);
	वापस ep;

ep_rel_conn:
	qedi->ep_tbl[iscsi_cid] = शून्य;
	पंचांगp = qedi_ops->release_conn(qedi->cdev, qedi_ep->handle);
	अगर (पंचांगp)
		QEDI_WARN(&qedi->dbg_ctx, "release_conn returned %d\n",
			  पंचांगp);
ep_मुक्त_sq:
	qedi_मुक्त_sq(qedi, qedi_ep);
ep_conn_निकास:
	iscsi_destroy_endpoपूर्णांक(ep);
	वापस ERR_PTR(ret);
पूर्ण

अटल पूर्णांक qedi_ep_poll(काष्ठा iscsi_endpoपूर्णांक *ep, पूर्णांक समयout_ms)
अणु
	काष्ठा qedi_endpoपूर्णांक *qedi_ep;
	पूर्णांक ret = 0;

	अगर (qedi_करो_not_recover)
		वापस 1;

	qedi_ep = ep->dd_data;
	अगर (qedi_ep->state == EP_STATE_IDLE ||
	    qedi_ep->state == EP_STATE_OFLDCONN_NONE ||
	    qedi_ep->state == EP_STATE_OFLDCONN_FAILED)
		वापस -1;

	अगर (qedi_ep->state == EP_STATE_OFLDCONN_COMPL)
		ret = 1;

	ret = रुको_event_पूर्णांकerruptible_समयout(qedi_ep->ofld_रुको,
					       QEDI_OFLD_WAIT_STATE(qedi_ep),
					       msecs_to_jअगरfies(समयout_ms));

	अगर (qedi_ep->state == EP_STATE_OFLDCONN_FAILED)
		ret = -1;

	अगर (ret > 0)
		वापस 1;
	अन्यथा अगर (!ret)
		वापस 0;
	अन्यथा
		वापस ret;
पूर्ण

अटल व्योम qedi_cleanup_active_cmd_list(काष्ठा qedi_conn *qedi_conn)
अणु
	काष्ठा qedi_cmd *cmd, *cmd_पंचांगp;

	spin_lock(&qedi_conn->list_lock);
	list_क्रम_each_entry_safe(cmd, cmd_पंचांगp, &qedi_conn->active_cmd_list,
				 io_cmd) अणु
		list_del_init(&cmd->io_cmd);
		qedi_conn->active_cmd_count--;
	पूर्ण
	spin_unlock(&qedi_conn->list_lock);
पूर्ण

अटल व्योम qedi_ep_disconnect(काष्ठा iscsi_endpoपूर्णांक *ep)
अणु
	काष्ठा qedi_endpoपूर्णांक *qedi_ep;
	काष्ठा qedi_conn *qedi_conn = शून्य;
	काष्ठा iscsi_conn *conn = शून्य;
	काष्ठा qedi_ctx *qedi;
	पूर्णांक ret = 0;
	पूर्णांक रुको_delay;
	पूर्णांक abrt_conn = 0;
	पूर्णांक count = 10;

	रुको_delay = 60 * HZ + DEF_MAX_RT_TIME;
	qedi_ep = ep->dd_data;
	qedi = qedi_ep->qedi;

	अगर (qedi_ep->state == EP_STATE_OFLDCONN_START)
		जाओ ep_निकास_recover;

	अगर (qedi_ep->state != EP_STATE_OFLDCONN_NONE)
		flush_work(&qedi_ep->offload_work);

	अगर (qedi_ep->conn) अणु
		qedi_conn = qedi_ep->conn;
		conn = qedi_conn->cls_conn->dd_data;
		iscsi_suspend_queue(conn);
		abrt_conn = qedi_conn->abrt_conn;

		जबतक (count--)	अणु
			अगर (!test_bit(QEDI_CONN_FW_CLEANUP,
				      &qedi_conn->flags)) अणु
				अवरोध;
			पूर्ण
			msleep(1000);
		पूर्ण

		अगर (test_bit(QEDI_IN_RECOVERY, &qedi->flags)) अणु
			अगर (qedi_करो_not_recover) अणु
				QEDI_INFO(&qedi->dbg_ctx, QEDI_LOG_INFO,
					  "Do not recover cid=0x%x\n",
					  qedi_ep->iscsi_cid);
				जाओ ep_निकास_recover;
			पूर्ण
			QEDI_INFO(&qedi->dbg_ctx, QEDI_LOG_INFO,
				  "Reset recovery cid=0x%x, qedi_ep=%p, state=0x%x\n",
				  qedi_ep->iscsi_cid, qedi_ep, qedi_ep->state);
			qedi_cleanup_active_cmd_list(qedi_conn);
			जाओ ep_release_conn;
		पूर्ण
	पूर्ण

	अगर (qedi_करो_not_recover)
		जाओ ep_निकास_recover;

	चयन (qedi_ep->state) अणु
	हाल EP_STATE_OFLDCONN_START:
	हाल EP_STATE_OFLDCONN_NONE:
		जाओ ep_release_conn;
	हाल EP_STATE_OFLDCONN_FAILED:
			अवरोध;
	हाल EP_STATE_OFLDCONN_COMPL:
		अगर (unlikely(!qedi_conn))
			अवरोध;

		QEDI_INFO(&qedi->dbg_ctx, QEDI_LOG_INFO,
			  "Active cmd count=%d, abrt_conn=%d, ep state=0x%x, cid=0x%x, qedi_conn=%p\n",
			  qedi_conn->active_cmd_count, abrt_conn,
			  qedi_ep->state,
			  qedi_ep->iscsi_cid,
			  qedi_ep->conn
			  );

		अगर (!qedi_conn->active_cmd_count)
			abrt_conn = 0;
		अन्यथा
			abrt_conn = 1;

		अगर (abrt_conn)
			qedi_clearsq(qedi, qedi_conn, शून्य);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	अगर (!abrt_conn)
		रुको_delay += qedi->pf_params.iscsi_pf_params.two_msl_समयr;

	qedi_ep->state = EP_STATE_DISCONN_START;

	अगर (test_bit(QEDI_IN_SHUTDOWN, &qedi->flags) ||
	    test_bit(QEDI_IN_RECOVERY, &qedi->flags))
		जाओ ep_release_conn;

	ret = qedi_ops->destroy_conn(qedi->cdev, qedi_ep->handle, abrt_conn);
	अगर (ret) अणु
		QEDI_WARN(&qedi->dbg_ctx,
			  "destroy_conn failed returned %d\n", ret);
	पूर्ण अन्यथा अणु
		ret = रुको_event_पूर्णांकerruptible_समयout(
					qedi_ep->tcp_ofld_रुको,
					(qedi_ep->state !=
					 EP_STATE_DISCONN_START),
					रुको_delay);
		अगर ((ret <= 0) || (qedi_ep->state == EP_STATE_DISCONN_START)) अणु
			QEDI_WARN(&qedi->dbg_ctx,
				  "Destroy conn timedout or interrupted, ret=%d, delay=%d, cid=0x%x\n",
				  ret, रुको_delay, qedi_ep->iscsi_cid);
		पूर्ण
	पूर्ण

ep_release_conn:
	ret = qedi_ops->release_conn(qedi->cdev, qedi_ep->handle);
	अगर (ret)
		QEDI_WARN(&qedi->dbg_ctx,
			  "release_conn returned %d, cid=0x%x\n",
			  ret, qedi_ep->iscsi_cid);
ep_निकास_recover:
	qedi_ep->state = EP_STATE_IDLE;
	qedi->ep_tbl[qedi_ep->iscsi_cid] = शून्य;
	qedi->cid_que.conn_cid_tbl[qedi_ep->iscsi_cid] = शून्य;
	qedi_मुक्त_id(&qedi->lcl_port_tbl, qedi_ep->src_port);
	qedi_मुक्त_sq(qedi, qedi_ep);

	अगर (qedi_conn)
		qedi_conn->ep = शून्य;

	qedi_ep->conn = शून्य;
	qedi_ep->qedi = शून्य;
	atomic_dec(&qedi->num_offloads);

	iscsi_destroy_endpoपूर्णांक(ep);
पूर्ण

अटल पूर्णांक qedi_data_avail(काष्ठा qedi_ctx *qedi, u16 vlanid)
अणु
	काष्ठा qed_dev *cdev = qedi->cdev;
	काष्ठा qedi_uio_dev *udev;
	काष्ठा qedi_uio_ctrl *uctrl;
	काष्ठा sk_buff *skb;
	u32 len;
	पूर्णांक rc = 0;

	udev = qedi->udev;
	अगर (!udev) अणु
		QEDI_ERR(&qedi->dbg_ctx, "udev is NULL.\n");
		वापस -EINVAL;
	पूर्ण

	uctrl = (काष्ठा qedi_uio_ctrl *)udev->uctrl;
	अगर (!uctrl) अणु
		QEDI_ERR(&qedi->dbg_ctx, "uctlr is NULL.\n");
		वापस -EINVAL;
	पूर्ण

	len = uctrl->host_tx_pkt_len;
	अगर (!len) अणु
		QEDI_ERR(&qedi->dbg_ctx, "Invalid len %u\n", len);
		वापस -EINVAL;
	पूर्ण

	skb = alloc_skb(len, GFP_ATOMIC);
	अगर (!skb) अणु
		QEDI_ERR(&qedi->dbg_ctx, "alloc_skb failed\n");
		वापस -EINVAL;
	पूर्ण

	skb_put(skb, len);
	स_नकल(skb->data, udev->tx_pkt, len);
	skb->ip_summed = CHECKSUM_NONE;

	अगर (vlanid)
		__vlan_hwaccel_put_tag(skb, htons(ETH_P_8021Q), vlanid);

	rc = qedi_ops->ll2->start_xmit(cdev, skb, 0);
	अगर (rc) अणु
		QEDI_ERR(&qedi->dbg_ctx, "ll2 start_xmit returned %d\n",
			 rc);
		kमुक्त_skb(skb);
	पूर्ण

	uctrl->host_tx_pkt_len = 0;
	uctrl->hw_tx_cons++;

	वापस rc;
पूर्ण

अटल व्योम qedi_offload_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा qedi_endpoपूर्णांक *qedi_ep =
		container_of(work, काष्ठा qedi_endpoपूर्णांक, offload_work);
	काष्ठा qedi_ctx *qedi;
	पूर्णांक रुको_delay = 5 * HZ;
	पूर्णांक ret;

	qedi = qedi_ep->qedi;

	ret = qedi_iscsi_offload_conn(qedi_ep);
	अगर (ret) अणु
		QEDI_ERR(&qedi->dbg_ctx,
			 "offload error: iscsi_cid=%u, qedi_ep=%p, ret=%d\n",
			 qedi_ep->iscsi_cid, qedi_ep, ret);
		qedi_ep->state = EP_STATE_OFLDCONN_FAILED;
		वापस;
	पूर्ण

	ret = रुको_event_पूर्णांकerruptible_समयout(qedi_ep->tcp_ofld_रुको,
					       (qedi_ep->state ==
					       EP_STATE_OFLDCONN_COMPL),
					       रुको_delay);
	अगर ((ret <= 0) || (qedi_ep->state != EP_STATE_OFLDCONN_COMPL)) अणु
		qedi_ep->state = EP_STATE_OFLDCONN_FAILED;
		QEDI_ERR(&qedi->dbg_ctx,
			 "Offload conn TIMEOUT iscsi_cid=%u, qedi_ep=%p\n",
			 qedi_ep->iscsi_cid, qedi_ep);
	पूर्ण
पूर्ण

अटल पूर्णांक qedi_set_path(काष्ठा Scsi_Host *shost, काष्ठा iscsi_path *path_data)
अणु
	काष्ठा qedi_ctx *qedi;
	काष्ठा qedi_endpoपूर्णांक *qedi_ep;
	पूर्णांक ret = 0;
	u32 iscsi_cid;
	u16 port_id = 0;

	अगर (!shost) अणु
		ret = -ENXIO;
		QEDI_ERR(शून्य, "shost is NULL\n");
		वापस ret;
	पूर्ण

	अगर (म_भेद(shost->hostt->proc_name, "qedi")) अणु
		ret = -ENXIO;
		QEDI_ERR(शून्य, "shost %s is invalid\n",
			 shost->hostt->proc_name);
		वापस ret;
	पूर्ण

	qedi = iscsi_host_priv(shost);
	अगर (path_data->handle == QEDI_PATH_HANDLE) अणु
		ret = qedi_data_avail(qedi, path_data->vlan_id);
		जाओ set_path_निकास;
	पूर्ण

	iscsi_cid = (u32)path_data->handle;
	अगर (iscsi_cid >= qedi->max_active_conns) अणु
		ret = -EINVAL;
		जाओ set_path_निकास;
	पूर्ण
	qedi_ep = qedi->ep_tbl[iscsi_cid];
	QEDI_INFO(&qedi->dbg_ctx, QEDI_LOG_INFO,
		  "iscsi_cid=0x%x, qedi_ep=%p\n", iscsi_cid, qedi_ep);
	अगर (!qedi_ep) अणु
		ret = -EINVAL;
		जाओ set_path_निकास;
	पूर्ण

	अगर (!is_valid_ether_addr(&path_data->mac_addr[0])) अणु
		QEDI_NOTICE(&qedi->dbg_ctx, "dst mac NOT VALID\n");
		qedi_ep->state = EP_STATE_OFLDCONN_NONE;
		ret = -EIO;
		जाओ set_path_निकास;
	पूर्ण

	ether_addr_copy(&qedi_ep->src_mac[0], &qedi->mac[0]);
	ether_addr_copy(&qedi_ep->dst_mac[0], &path_data->mac_addr[0]);

	qedi_ep->vlan_id = path_data->vlan_id;
	अगर (path_data->pmtu < DEF_PATH_MTU) अणु
		qedi_ep->pmtu = qedi->ll2_mtu;
		QEDI_INFO(&qedi->dbg_ctx, QEDI_LOG_INFO,
			  "MTU cannot be %u, using default MTU %u\n",
			   path_data->pmtu, qedi_ep->pmtu);
	पूर्ण

	अगर (path_data->pmtu != qedi->ll2_mtu) अणु
		अगर (path_data->pmtu > JUMBO_MTU) अणु
			ret = -EINVAL;
			QEDI_ERR(शून्य, "Invalid MTU %u\n", path_data->pmtu);
			जाओ set_path_निकास;
		पूर्ण

		qedi_reset_host_mtu(qedi, path_data->pmtu);
		qedi_ep->pmtu = qedi->ll2_mtu;
	पूर्ण

	port_id = qedi_ep->src_port;
	अगर (port_id >= QEDI_LOCAL_PORT_MIN &&
	    port_id < QEDI_LOCAL_PORT_MAX) अणु
		अगर (qedi_alloc_id(&qedi->lcl_port_tbl, port_id))
			port_id = 0;
	पूर्ण अन्यथा अणु
		port_id = 0;
	पूर्ण

	अगर (!port_id) अणु
		port_id = qedi_alloc_new_id(&qedi->lcl_port_tbl);
		अगर (port_id == QEDI_LOCAL_PORT_INVALID) अणु
			QEDI_ERR(&qedi->dbg_ctx,
				 "Failed to allocate port id for iscsi_cid=0x%x\n",
				 iscsi_cid);
			ret = -ENOMEM;
			जाओ set_path_निकास;
		पूर्ण
	पूर्ण

	qedi_ep->src_port = port_id;

	अगर (qedi_ep->ip_type == TCP_IPV4) अणु
		स_नकल(&qedi_ep->src_addr[0], &path_data->src.v4_addr,
		       माप(काष्ठा in_addr));
		स_नकल(&qedi->src_ip[0], &path_data->src.v4_addr,
		       माप(काष्ठा in_addr));
		qedi->ip_type = TCP_IPV4;

		QEDI_INFO(&qedi->dbg_ctx, QEDI_LOG_CONN,
			  "src addr:port=%pI4:%u, dst addr:port=%pI4:%u\n",
			  qedi_ep->src_addr, qedi_ep->src_port,
			  qedi_ep->dst_addr, qedi_ep->dst_port);
	पूर्ण अन्यथा अणु
		स_नकल(&qedi_ep->src_addr[0], &path_data->src.v6_addr,
		       माप(काष्ठा in6_addr));
		स_नकल(&qedi->src_ip[0], &path_data->src.v6_addr,
		       माप(काष्ठा in6_addr));
		qedi->ip_type = TCP_IPV6;

		QEDI_INFO(&qedi->dbg_ctx, QEDI_LOG_CONN,
			  "src addr:port=%pI6:%u, dst addr:port=%pI6:%u\n",
			  qedi_ep->src_addr, qedi_ep->src_port,
			  qedi_ep->dst_addr, qedi_ep->dst_port);
	पूर्ण

	INIT_WORK(&qedi_ep->offload_work, qedi_offload_work);
	queue_work(qedi->offload_thपढ़ो, &qedi_ep->offload_work);

	ret = 0;

set_path_निकास:
	वापस ret;
पूर्ण

अटल umode_t qedi_attr_is_visible(पूर्णांक param_type, पूर्णांक param)
अणु
	चयन (param_type) अणु
	हाल ISCSI_HOST_PARAM:
		चयन (param) अणु
		हाल ISCSI_HOST_PARAM_NETDEV_NAME:
		हाल ISCSI_HOST_PARAM_HWADDRESS:
		हाल ISCSI_HOST_PARAM_IPADDRESS:
			वापस 0444;
		शेष:
			वापस 0;
		पूर्ण
	हाल ISCSI_PARAM:
		चयन (param) अणु
		हाल ISCSI_PARAM_MAX_RECV_DLENGTH:
		हाल ISCSI_PARAM_MAX_XMIT_DLENGTH:
		हाल ISCSI_PARAM_HDRDGST_EN:
		हाल ISCSI_PARAM_DATADGST_EN:
		हाल ISCSI_PARAM_CONN_ADDRESS:
		हाल ISCSI_PARAM_CONN_PORT:
		हाल ISCSI_PARAM_EXP_STATSN:
		हाल ISCSI_PARAM_PERSISTENT_ADDRESS:
		हाल ISCSI_PARAM_PERSISTENT_PORT:
		हाल ISCSI_PARAM_PING_TMO:
		हाल ISCSI_PARAM_RECV_TMO:
		हाल ISCSI_PARAM_INITIAL_R2T_EN:
		हाल ISCSI_PARAM_MAX_R2T:
		हाल ISCSI_PARAM_IMM_DATA_EN:
		हाल ISCSI_PARAM_FIRST_BURST:
		हाल ISCSI_PARAM_MAX_BURST:
		हाल ISCSI_PARAM_PDU_INORDER_EN:
		हाल ISCSI_PARAM_DATASEQ_INORDER_EN:
		हाल ISCSI_PARAM_ERL:
		हाल ISCSI_PARAM_TARGET_NAME:
		हाल ISCSI_PARAM_TPGT:
		हाल ISCSI_PARAM_USERNAME:
		हाल ISCSI_PARAM_PASSWORD:
		हाल ISCSI_PARAM_USERNAME_IN:
		हाल ISCSI_PARAM_PASSWORD_IN:
		हाल ISCSI_PARAM_FAST_ABORT:
		हाल ISCSI_PARAM_ABORT_TMO:
		हाल ISCSI_PARAM_LU_RESET_TMO:
		हाल ISCSI_PARAM_TGT_RESET_TMO:
		हाल ISCSI_PARAM_IFACE_NAME:
		हाल ISCSI_PARAM_INITIATOR_NAME:
		हाल ISCSI_PARAM_BOOT_ROOT:
		हाल ISCSI_PARAM_BOOT_NIC:
		हाल ISCSI_PARAM_BOOT_TARGET:
			वापस 0444;
		शेष:
			वापस 0;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम qedi_cleanup_task(काष्ठा iscsi_task *task)
अणु
	अगर (!task->sc || task->state == ISCSI_TASK_PENDING) अणु
		QEDI_INFO(शून्य, QEDI_LOG_IO, "Returning ref_cnt=%d\n",
			  refcount_पढ़ो(&task->refcount));
		वापस;
	पूर्ण

	qedi_iscsi_unmap_sg_list(task->dd_data);
पूर्ण

काष्ठा iscsi_transport qedi_iscsi_transport = अणु
	.owner = THIS_MODULE,
	.name = QEDI_MODULE_NAME,
	.caps = CAP_RECOVERY_L0 | CAP_HDRDGST | CAP_MULTI_R2T | CAP_DATADGST |
		CAP_DATA_PATH_OFFLOAD | CAP_TEXT_NEGO,
	.create_session = qedi_session_create,
	.destroy_session = qedi_session_destroy,
	.create_conn = qedi_conn_create,
	.bind_conn = qedi_conn_bind,
	.start_conn = qedi_conn_start,
	.stop_conn = iscsi_conn_stop,
	.destroy_conn = qedi_conn_destroy,
	.set_param = iscsi_set_param,
	.get_ep_param = qedi_ep_get_param,
	.get_conn_param = iscsi_conn_get_param,
	.get_session_param = iscsi_session_get_param,
	.get_host_param = qedi_host_get_param,
	.send_pdu = iscsi_conn_send_pdu,
	.get_stats = qedi_conn_get_stats,
	.xmit_task = qedi_task_xmit,
	.cleanup_task = qedi_cleanup_task,
	.session_recovery_समयकरोut = iscsi_session_recovery_समयकरोut,
	.ep_connect = qedi_ep_connect,
	.ep_poll = qedi_ep_poll,
	.ep_disconnect = qedi_ep_disconnect,
	.set_path = qedi_set_path,
	.attr_is_visible = qedi_attr_is_visible,
पूर्ण;

व्योम qedi_start_conn_recovery(काष्ठा qedi_ctx *qedi,
			      काष्ठा qedi_conn *qedi_conn)
अणु
	काष्ठा iscsi_cls_session *cls_sess;
	काष्ठा iscsi_cls_conn *cls_conn;
	काष्ठा iscsi_conn *conn;

	cls_conn = qedi_conn->cls_conn;
	conn = cls_conn->dd_data;
	cls_sess = iscsi_conn_to_session(cls_conn);

	अगर (iscsi_is_session_online(cls_sess)) अणु
		qedi_conn->abrt_conn = 1;
		QEDI_ERR(&qedi->dbg_ctx,
			 "Failing connection, state=0x%x, cid=0x%x\n",
			 conn->session->state, qedi_conn->iscsi_conn_id);
		iscsi_conn_failure(qedi_conn->cls_conn->dd_data,
				   ISCSI_ERR_CONN_FAILED);
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा अणु
	क्रमागत iscsi_error_types error_code;
	अक्षर *err_string;
पूर्ण qedi_iscsi_error[] = अणु
	अणु ISCSI_STATUS_NONE,
	  "tcp_error none"
	पूर्ण,
	अणु ISCSI_CONN_ERROR_TASK_CID_MISMATCH,
	  "task cid mismatch"
	पूर्ण,
	अणु ISCSI_CONN_ERROR_TASK_NOT_VALID,
	  "invalid task"
	पूर्ण,
	अणु ISCSI_CONN_ERROR_RQ_RING_IS_FULL,
	  "rq ring full"
	पूर्ण,
	अणु ISCSI_CONN_ERROR_CMDQ_RING_IS_FULL,
	  "cmdq ring full"
	पूर्ण,
	अणु ISCSI_CONN_ERROR_HQE_CACHING_FAILED,
	  "sge caching failed"
	पूर्ण,
	अणु ISCSI_CONN_ERROR_HEADER_DIGEST_ERROR,
	  "hdr digest error"
	पूर्ण,
	अणु ISCSI_CONN_ERROR_LOCAL_COMPLETION_ERROR,
	  "local cmpl error"
	पूर्ण,
	अणु ISCSI_CONN_ERROR_DATA_OVERRUN,
	  "invalid task"
	पूर्ण,
	अणु ISCSI_CONN_ERROR_OUT_OF_SGES_ERROR,
	  "out of sge error"
	पूर्ण,
	अणु ISCSI_CONN_ERROR_TCP_IP_FRAGMENT_ERROR,
	  "tcp ip fragment error"
	पूर्ण,
	अणु ISCSI_CONN_ERROR_PROTOCOL_ERR_AHS_LEN,
	  "AHS len protocol error"
	पूर्ण,
	अणु ISCSI_CONN_ERROR_PROTOCOL_ERR_ITT_OUT_OF_RANGE,
	  "itt out of range error"
	पूर्ण,
	अणु ISCSI_CONN_ERROR_PROTOCOL_ERR_DATA_SEG_LEN_EXCEEDS_PDU_SIZE,
	  "data seg more than pdu size"
	पूर्ण,
	अणु ISCSI_CONN_ERROR_PROTOCOL_ERR_INVALID_OPCODE,
	  "invalid opcode"
	पूर्ण,
	अणु ISCSI_CONN_ERROR_PROTOCOL_ERR_INVALID_OPCODE_BEFORE_UPDATE,
	  "invalid opcode before update"
	पूर्ण,
	अणु ISCSI_CONN_ERROR_UNVALID_NOPIN_DSL,
	  "unexpected opcode"
	पूर्ण,
	अणु ISCSI_CONN_ERROR_PROTOCOL_ERR_R2T_CARRIES_NO_DATA,
	  "r2t carries no data"
	पूर्ण,
	अणु ISCSI_CONN_ERROR_PROTOCOL_ERR_DATA_SN,
	  "data sn error"
	पूर्ण,
	अणु ISCSI_CONN_ERROR_PROTOCOL_ERR_DATA_IN_TTT,
	  "data TTT error"
	पूर्ण,
	अणु ISCSI_CONN_ERROR_PROTOCOL_ERR_R2T_TTT,
	  "r2t TTT error"
	पूर्ण,
	अणु ISCSI_CONN_ERROR_PROTOCOL_ERR_R2T_BUFFER_OFFSET,
	  "buffer offset error"
	पूर्ण,
	अणु ISCSI_CONN_ERROR_PROTOCOL_ERR_BUFFER_OFFSET_OOO,
	  "buffer offset ooo"
	पूर्ण,
	अणु ISCSI_CONN_ERROR_PROTOCOL_ERR_R2T_SN,
	  "data seg len 0"
	पूर्ण,
	अणु ISCSI_CONN_ERROR_PROTOCOL_ERR_DESIRED_DATA_TRNS_LEN_0,
	  "data xer len error"
	पूर्ण,
	अणु ISCSI_CONN_ERROR_PROTOCOL_ERR_DESIRED_DATA_TRNS_LEN_1,
	  "data xer len1 error"
	पूर्ण,
	अणु ISCSI_CONN_ERROR_PROTOCOL_ERR_DESIRED_DATA_TRNS_LEN_2,
	  "data xer len2 error"
	पूर्ण,
	अणु ISCSI_CONN_ERROR_PROTOCOL_ERR_LUN,
	  "protocol lun error"
	पूर्ण,
	अणु ISCSI_CONN_ERROR_PROTOCOL_ERR_F_BIT_ZERO,
	  "f bit zero error"
	पूर्ण,
	अणु ISCSI_CONN_ERROR_PROTOCOL_ERR_EXP_STAT_SN,
	  "exp stat sn error"
	पूर्ण,
	अणु ISCSI_CONN_ERROR_PROTOCOL_ERR_DSL_NOT_ZERO,
	  "dsl not zero error"
	पूर्ण,
	अणु ISCSI_CONN_ERROR_PROTOCOL_ERR_INVALID_DSL,
	  "invalid dsl"
	पूर्ण,
	अणु ISCSI_CONN_ERROR_PROTOCOL_ERR_DATA_SEG_LEN_TOO_BIG,
	  "data seg len too big"
	पूर्ण,
	अणु ISCSI_CONN_ERROR_PROTOCOL_ERR_OUTSTANDING_R2T_COUNT,
	  "outstanding r2t count error"
	पूर्ण,
	अणु ISCSI_CONN_ERROR_SENSE_DATA_LENGTH,
	  "sense datalen error"
	पूर्ण,
पूर्ण;

अटल अक्षर *qedi_get_iscsi_error(क्रमागत iscsi_error_types err_code)
अणु
	पूर्णांक i;
	अक्षर *msg = शून्य;

	क्रम (i = 0; i < ARRAY_SIZE(qedi_iscsi_error); i++) अणु
		अगर (qedi_iscsi_error[i].error_code == err_code) अणु
			msg = qedi_iscsi_error[i].err_string;
			अवरोध;
		पूर्ण
	पूर्ण
	वापस msg;
पूर्ण

व्योम qedi_process_iscsi_error(काष्ठा qedi_endpoपूर्णांक *ep,
			      काष्ठा iscsi_eqe_data *data)
अणु
	काष्ठा qedi_conn *qedi_conn;
	काष्ठा qedi_ctx *qedi;
	अक्षर warn_notice[] = "iscsi_warning";
	अक्षर error_notice[] = "iscsi_error";
	अक्षर unknown_msg[] = "Unknown error";
	अक्षर *message;
	पूर्णांक need_recovery = 0;
	u32 err_mask = 0;
	अक्षर *msg;

	अगर (!ep)
		वापस;

	qedi_conn = ep->conn;
	अगर (!qedi_conn)
		वापस;

	qedi = ep->qedi;

	QEDI_ERR(&qedi->dbg_ctx, "async event iscsi error:0x%x\n",
		 data->error_code);

	अगर (err_mask) अणु
		need_recovery = 0;
		message = warn_notice;
	पूर्ण अन्यथा अणु
		need_recovery = 1;
		message = error_notice;
	पूर्ण

	msg = qedi_get_iscsi_error(data->error_code);
	अगर (!msg) अणु
		need_recovery = 0;
		msg = unknown_msg;
	पूर्ण

	iscsi_conn_prपूर्णांकk(KERN_ALERT,
			  qedi_conn->cls_conn->dd_data,
			  "qedi: %s - %s\n", message, msg);

	अगर (need_recovery)
		qedi_start_conn_recovery(qedi_conn->qedi, qedi_conn);
पूर्ण

व्योम qedi_clear_session_ctx(काष्ठा iscsi_cls_session *cls_sess)
अणु
	काष्ठा iscsi_session *session = cls_sess->dd_data;
	काष्ठा iscsi_conn *conn = session->leadconn;
	काष्ठा qedi_conn *qedi_conn = conn->dd_data;

	अगर (iscsi_is_session_online(cls_sess))
		qedi_ep_disconnect(qedi_conn->iscsi_ep);

	qedi_conn_destroy(qedi_conn->cls_conn);

	qedi_session_destroy(cls_sess);
पूर्ण

व्योम qedi_process_tcp_error(काष्ठा qedi_endpoपूर्णांक *ep,
			    काष्ठा iscsi_eqe_data *data)
अणु
	काष्ठा qedi_conn *qedi_conn;

	अगर (!ep)
		वापस;

	qedi_conn = ep->conn;
	अगर (!qedi_conn)
		वापस;

	QEDI_ERR(&ep->qedi->dbg_ctx, "async event TCP error:0x%x\n",
		 data->error_code);

	qedi_start_conn_recovery(qedi_conn->qedi, qedi_conn);
पूर्ण
