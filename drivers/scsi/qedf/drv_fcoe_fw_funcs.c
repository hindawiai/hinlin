<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* QLogic FCoE Offload Driver
 * Copyright (c) 2016-2018 Cavium Inc.
 */
#समावेश "drv_fcoe_fw_funcs.h"
#समावेश "drv_scsi_fw_funcs.h"

#घोषणा FCOE_RX_ID (0xFFFFu)

अटल अंतरभूत व्योम init_common_sqe(काष्ठा fcoe_task_params *task_params,
				   क्रमागत fcoe_sqe_request_type request_type)
अणु
	स_रखो(task_params->sqe, 0, माप(*(task_params->sqe)));
	SET_FIELD(task_params->sqe->flags, FCOE_WQE_REQ_TYPE,
		  request_type);
	task_params->sqe->task_id = task_params->itid;
पूर्ण

पूर्णांक init_initiator_rw_fcoe_task(काष्ठा fcoe_task_params *task_params,
				काष्ठा scsi_sgl_task_params *sgl_task_params,
				काष्ठा regpair sense_data_buffer_phys_addr,
				u32 task_retry_id,
				u8 fcp_cmd_payload[32])
अणु
	काष्ठा e4_fcoe_task_context *ctx = task_params->context;
	स्थिर u8 val_byte = ctx->ystorm_ag_context.byte0;
	काष्ठा e4_ustorm_fcoe_task_ag_ctx *u_ag_ctx;
	काष्ठा ystorm_fcoe_task_st_ctx *y_st_ctx;
	काष्ठा tstorm_fcoe_task_st_ctx *t_st_ctx;
	काष्ठा mstorm_fcoe_task_st_ctx *m_st_ctx;
	u32 io_size, val;
	bool slow_sgl;

	स_रखो(ctx, 0, माप(*(ctx)));
	ctx->ystorm_ag_context.byte0 = val_byte;
	slow_sgl = scsi_is_slow_sgl(sgl_task_params->num_sges,
				    sgl_task_params->small_mid_sge);
	io_size = (task_params->task_type == FCOE_TASK_TYPE_WRITE_INITIATOR ?
		   task_params->tx_io_size : task_params->rx_io_size);

	/* Ystorm ctx */
	y_st_ctx = &ctx->ystorm_st_context;
	y_st_ctx->data_2_trns_rem = cpu_to_le32(io_size);
	y_st_ctx->task_rety_identअगरier = cpu_to_le32(task_retry_id);
	y_st_ctx->task_type = (u8)task_params->task_type;
	स_नकल(&y_st_ctx->tx_info_जोड़.fcp_cmd_payload,
	       fcp_cmd_payload, माप(काष्ठा fcoe_fcp_cmd_payload));

	/* Tstorm ctx */
	t_st_ctx = &ctx->tstorm_st_context;
	t_st_ctx->पढ़ो_only.dev_type = (u8)(task_params->is_tape_device == 1 ?
					    FCOE_TASK_DEV_TYPE_TAPE :
					    FCOE_TASK_DEV_TYPE_DISK);
	t_st_ctx->पढ़ो_only.cid = cpu_to_le32(task_params->conn_cid);
	val = cpu_to_le32(task_params->cq_rss_number);
	t_st_ctx->पढ़ो_only.glbl_q_num = val;
	t_st_ctx->पढ़ो_only.fcp_cmd_trns_size = cpu_to_le32(io_size);
	t_st_ctx->पढ़ो_only.task_type = (u8)task_params->task_type;
	SET_FIELD(t_st_ctx->पढ़ो_ग_लिखो.flags,
		  FCOE_TSTORM_FCOE_TASK_ST_CTX_READ_WRITE_EXP_FIRST_FRAME, 1);
	t_st_ctx->पढ़ो_ग_लिखो.rx_id = cpu_to_le16(FCOE_RX_ID);

	/* Ustorm ctx */
	u_ag_ctx = &ctx->ustorm_ag_context;
	u_ag_ctx->global_cq_num = cpu_to_le32(task_params->cq_rss_number);

	/* Mstorm buffer क्रम sense/rsp data placement */
	m_st_ctx = &ctx->mstorm_st_context;
	val = cpu_to_le32(sense_data_buffer_phys_addr.hi);
	m_st_ctx->rsp_buf_addr.hi = val;
	val = cpu_to_le32(sense_data_buffer_phys_addr.lo);
	m_st_ctx->rsp_buf_addr.lo = val;

	अगर (task_params->task_type == FCOE_TASK_TYPE_WRITE_INITIATOR) अणु
		/* Ystorm ctx */
		y_st_ctx->expect_first_xfer = 1;

		/* Set the amount of super SGEs. Can be up to 4. */
		SET_FIELD(y_st_ctx->sgl_mode,
			  YSTORM_FCOE_TASK_ST_CTX_TX_SGL_MODE,
			  (slow_sgl ? SCSI_TX_SLOW_SGL : SCSI_FAST_SGL));
		init_scsi_sgl_context(&y_st_ctx->sgl_params,
				      &y_st_ctx->data_desc,
				      sgl_task_params);

		/* Mstorm ctx */
		SET_FIELD(m_st_ctx->flags,
			  MSTORM_FCOE_TASK_ST_CTX_TX_SGL_MODE,
			  (slow_sgl ? SCSI_TX_SLOW_SGL : SCSI_FAST_SGL));
		m_st_ctx->sgl_params.sgl_num_sges =
			cpu_to_le16(sgl_task_params->num_sges);
	पूर्ण अन्यथा अणु
		/* Tstorm ctx */
		SET_FIELD(t_st_ctx->पढ़ो_ग_लिखो.flags,
			  FCOE_TSTORM_FCOE_TASK_ST_CTX_READ_WRITE_RX_SGL_MODE,
			  (slow_sgl ? SCSI_TX_SLOW_SGL : SCSI_FAST_SGL));

		/* Mstorm ctx */
		m_st_ctx->data_2_trns_rem = cpu_to_le32(io_size);
		init_scsi_sgl_context(&m_st_ctx->sgl_params,
				      &m_st_ctx->data_desc,
				      sgl_task_params);
	पूर्ण

	/* Init Sqe */
	init_common_sqe(task_params, SEND_FCOE_CMD);

	वापस 0;
पूर्ण

पूर्णांक init_initiator_midpath_unsolicited_fcoe_task(
	काष्ठा fcoe_task_params *task_params,
	काष्ठा fcoe_tx_mid_path_params *mid_path_fc_header,
	काष्ठा scsi_sgl_task_params *tx_sgl_task_params,
	काष्ठा scsi_sgl_task_params *rx_sgl_task_params,
	u8 fw_to_place_fc_header)
अणु
	काष्ठा e4_fcoe_task_context *ctx = task_params->context;
	स्थिर u8 val_byte = ctx->ystorm_ag_context.byte0;
	काष्ठा e4_ustorm_fcoe_task_ag_ctx *u_ag_ctx;
	काष्ठा ystorm_fcoe_task_st_ctx *y_st_ctx;
	काष्ठा tstorm_fcoe_task_st_ctx *t_st_ctx;
	काष्ठा mstorm_fcoe_task_st_ctx *m_st_ctx;
	u32 val;

	स_रखो(ctx, 0, माप(*(ctx)));
	ctx->ystorm_ag_context.byte0 = val_byte;

	/* Init Ystorm */
	y_st_ctx = &ctx->ystorm_st_context;
	init_scsi_sgl_context(&y_st_ctx->sgl_params,
			      &y_st_ctx->data_desc,
			      tx_sgl_task_params);
	SET_FIELD(y_st_ctx->sgl_mode,
		  YSTORM_FCOE_TASK_ST_CTX_TX_SGL_MODE, SCSI_FAST_SGL);
	y_st_ctx->data_2_trns_rem = cpu_to_le32(task_params->tx_io_size);
	y_st_ctx->task_type = (u8)task_params->task_type;
	स_नकल(&y_st_ctx->tx_info_जोड़.tx_params.mid_path,
	       mid_path_fc_header, माप(काष्ठा fcoe_tx_mid_path_params));

	/* Init Mstorm */
	m_st_ctx = &ctx->mstorm_st_context;
	init_scsi_sgl_context(&m_st_ctx->sgl_params,
			      &m_st_ctx->data_desc,
			      rx_sgl_task_params);
	SET_FIELD(m_st_ctx->flags,
		  MSTORM_FCOE_TASK_ST_CTX_MP_INCLUDE_FC_HEADER,
		  fw_to_place_fc_header);
	m_st_ctx->data_2_trns_rem = cpu_to_le32(task_params->rx_io_size);

	/* Init Tstorm */
	t_st_ctx = &ctx->tstorm_st_context;
	t_st_ctx->पढ़ो_only.cid = cpu_to_le32(task_params->conn_cid);
	val = cpu_to_le32(task_params->cq_rss_number);
	t_st_ctx->पढ़ो_only.glbl_q_num = val;
	t_st_ctx->पढ़ो_only.task_type = (u8)task_params->task_type;
	SET_FIELD(t_st_ctx->पढ़ो_ग_लिखो.flags,
		  FCOE_TSTORM_FCOE_TASK_ST_CTX_READ_WRITE_EXP_FIRST_FRAME, 1);
	t_st_ctx->पढ़ो_ग_लिखो.rx_id = cpu_to_le16(FCOE_RX_ID);

	/* Init Ustorm */
	u_ag_ctx = &ctx->ustorm_ag_context;
	u_ag_ctx->global_cq_num = cpu_to_le32(task_params->cq_rss_number);

	/* Init SQE */
	init_common_sqe(task_params, SEND_FCOE_MIDPATH);
	task_params->sqe->additional_info_जोड़.burst_length =
				    tx_sgl_task_params->total_buffer_size;
	SET_FIELD(task_params->sqe->flags,
		  FCOE_WQE_NUM_SGES, tx_sgl_task_params->num_sges);
	SET_FIELD(task_params->sqe->flags, FCOE_WQE_SGL_MODE,
		  SCSI_FAST_SGL);

	वापस 0;
पूर्ण

पूर्णांक init_initiator_पात_fcoe_task(काष्ठा fcoe_task_params *task_params)
अणु
	init_common_sqe(task_params, SEND_FCOE_ABTS_REQUEST);
	वापस 0;
पूर्ण

पूर्णांक init_initiator_cleanup_fcoe_task(काष्ठा fcoe_task_params *task_params)
अणु
	init_common_sqe(task_params, FCOE_EXCHANGE_CLEANUP);
	वापस 0;
पूर्ण

पूर्णांक init_initiator_sequence_recovery_fcoe_task(
	काष्ठा fcoe_task_params *task_params, u32 desired_offset)
अणु
	init_common_sqe(task_params, FCOE_SEQUENCE_RECOVERY);
	task_params->sqe->additional_info_जोड़.seq_rec_updated_offset =
								desired_offset;
	वापस 0;
पूर्ण
