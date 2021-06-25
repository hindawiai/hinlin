<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* QLogic iSCSI Offload Driver
 * Copyright (c) 2016 Cavium Inc.
 */

#समावेश <linux/types.h>
#समावेश <यंत्र/byteorder.h>
#समावेश "qedi_hsi.h"
#समावेश <linux/qed/qed_अगर.h>

#समावेश "qedi_fw_iscsi.h"
#समावेश "qedi_fw_scsi.h"

#घोषणा SCSI_NUM_SGES_IN_CACHE 0x4

अटल bool scsi_is_slow_sgl(u16 num_sges, bool small_mid_sge)
अणु
	वापस (num_sges > SCSI_NUM_SGES_SLOW_SGL_THR && small_mid_sge);
पूर्ण

अटल
व्योम init_scsi_sgl_context(काष्ठा scsi_sgl_params *ctx_sgl_params,
			   काष्ठा scsi_cached_sges *ctx_data_desc,
			   काष्ठा scsi_sgl_task_params *sgl_task_params)
अणु
	u8 sge_index;
	u8 num_sges;
	u32 val;

	num_sges = (sgl_task_params->num_sges > SCSI_NUM_SGES_IN_CACHE) ?
			     SCSI_NUM_SGES_IN_CACHE : sgl_task_params->num_sges;

	/* sgl params */
	val = cpu_to_le32(sgl_task_params->sgl_phys_addr.lo);
	ctx_sgl_params->sgl_addr.lo = val;
	val = cpu_to_le32(sgl_task_params->sgl_phys_addr.hi);
	ctx_sgl_params->sgl_addr.hi = val;
	val = cpu_to_le32(sgl_task_params->total_buffer_size);
	ctx_sgl_params->sgl_total_length = val;
	ctx_sgl_params->sgl_num_sges = cpu_to_le16(sgl_task_params->num_sges);

	क्रम (sge_index = 0; sge_index < num_sges; sge_index++) अणु
		val = cpu_to_le32(sgl_task_params->sgl[sge_index].sge_addr.lo);
		ctx_data_desc->sge[sge_index].sge_addr.lo = val;
		val = cpu_to_le32(sgl_task_params->sgl[sge_index].sge_addr.hi);
		ctx_data_desc->sge[sge_index].sge_addr.hi = val;
		val = cpu_to_le32(sgl_task_params->sgl[sge_index].sge_len);
		ctx_data_desc->sge[sge_index].sge_len = val;
	पूर्ण
पूर्ण

अटल u32 calc_rw_task_size(काष्ठा iscsi_task_params *task_params,
			     क्रमागत iscsi_task_type task_type,
			     काष्ठा scsi_sgl_task_params *sgl_task_params,
			     काष्ठा scsi_dअगर_task_params *dअगर_task_params)
अणु
	u32 io_size;

	अगर (task_type == ISCSI_TASK_TYPE_INITIATOR_WRITE ||
	    task_type == ISCSI_TASK_TYPE_TARGET_READ)
		io_size = task_params->tx_io_size;
	अन्यथा
		io_size = task_params->rx_io_size;

	अगर (!io_size)
		वापस 0;

	अगर (!dअगर_task_params)
		वापस io_size;

	वापस !dअगर_task_params->dअगर_on_network ?
	       io_size : sgl_task_params->total_buffer_size;
पूर्ण

अटल व्योम
init_dअगर_context_flags(काष्ठा iscsi_dअगर_flags *ctx_dअगर_flags,
		       काष्ठा scsi_dअगर_task_params *dअगर_task_params)
अणु
	अगर (!dअगर_task_params)
		वापस;

	SET_FIELD(ctx_dअगर_flags->flags, ISCSI_DIF_FLAGS_PROT_INTERVAL_SIZE_LOG,
		  dअगर_task_params->dअगर_block_size_log);
	SET_FIELD(ctx_dअगर_flags->flags, ISCSI_DIF_FLAGS_DIF_TO_PEER,
		  dअगर_task_params->dअगर_on_network ? 1 : 0);
	SET_FIELD(ctx_dअगर_flags->flags, ISCSI_DIF_FLAGS_HOST_INTERFACE,
		  dअगर_task_params->dअगर_on_host ? 1 : 0);
पूर्ण

अटल व्योम init_sqe(काष्ठा iscsi_task_params *task_params,
		     काष्ठा scsi_sgl_task_params *sgl_task_params,
		     काष्ठा scsi_dअगर_task_params *dअगर_task_params,
		     काष्ठा iscsi_common_hdr *pdu_header,
		     काष्ठा scsi_initiator_cmd_params *cmd_params,
		     क्रमागत iscsi_task_type task_type,
		     bool is_cleanup)
अणु
	अगर (!task_params->sqe)
		वापस;

	स_रखो(task_params->sqe, 0, माप(*task_params->sqe));
	task_params->sqe->task_id = cpu_to_le16(task_params->itid);
	अगर (is_cleanup) अणु
		SET_FIELD(task_params->sqe->flags, ISCSI_WQE_WQE_TYPE,
			  ISCSI_WQE_TYPE_TASK_CLEANUP);
		वापस;
	पूर्ण

	चयन (task_type) अणु
	हाल ISCSI_TASK_TYPE_INITIATOR_WRITE:
	अणु
		u32 buf_size = 0;
		u32 num_sges = 0;

		init_dअगर_context_flags(&task_params->sqe->prot_flags,
				       dअगर_task_params);

		SET_FIELD(task_params->sqe->flags, ISCSI_WQE_WQE_TYPE,
			  ISCSI_WQE_TYPE_NORMAL);

		अगर (task_params->tx_io_size) अणु
			buf_size = calc_rw_task_size(task_params, task_type,
						     sgl_task_params,
						     dअगर_task_params);

			अगर (scsi_is_slow_sgl(sgl_task_params->num_sges,
					     sgl_task_params->small_mid_sge))
				num_sges = ISCSI_WQE_NUM_SGES_SLOWIO;
			अन्यथा
				num_sges = min(sgl_task_params->num_sges,
					       (u16)SCSI_NUM_SGES_SLOW_SGL_THR);
		पूर्ण

		SET_FIELD(task_params->sqe->flags, ISCSI_WQE_NUM_SGES,
			  num_sges);
		SET_FIELD(task_params->sqe->contlen_cdbsize, ISCSI_WQE_CONT_LEN,
			  buf_size);

		अगर (GET_FIELD(pdu_header->hdr_second_dword,
			      ISCSI_CMD_HDR_TOTAL_AHS_LEN))
			SET_FIELD(task_params->sqe->contlen_cdbsize,
				  ISCSI_WQE_CDB_SIZE,
				  cmd_params->extended_cdb_sge.sge_len);
	पूर्ण
		अवरोध;
	हाल ISCSI_TASK_TYPE_INITIATOR_READ:
		SET_FIELD(task_params->sqe->flags, ISCSI_WQE_WQE_TYPE,
			  ISCSI_WQE_TYPE_NORMAL);

		अगर (GET_FIELD(pdu_header->hdr_second_dword,
			      ISCSI_CMD_HDR_TOTAL_AHS_LEN))
			SET_FIELD(task_params->sqe->contlen_cdbsize,
				  ISCSI_WQE_CDB_SIZE,
				  cmd_params->extended_cdb_sge.sge_len);
		अवरोध;
	हाल ISCSI_TASK_TYPE_LOGIN_RESPONSE:
	हाल ISCSI_TASK_TYPE_MIDPATH:
	अणु
		bool advance_statsn = true;

		अगर (task_type == ISCSI_TASK_TYPE_LOGIN_RESPONSE)
			SET_FIELD(task_params->sqe->flags, ISCSI_WQE_WQE_TYPE,
				  ISCSI_WQE_TYPE_LOGIN);
		अन्यथा
			SET_FIELD(task_params->sqe->flags, ISCSI_WQE_WQE_TYPE,
				  ISCSI_WQE_TYPE_MIDDLE_PATH);

		अगर (task_type == ISCSI_TASK_TYPE_MIDPATH) अणु
			u8 opcode = GET_FIELD(pdu_header->hdr_first_byte,
					      ISCSI_COMMON_HDR_OPCODE);

			अगर (opcode != ISCSI_OPCODE_TEXT_RESPONSE &&
			    (opcode != ISCSI_OPCODE_NOP_IN ||
			    pdu_header->itt == ISCSI_TTT_ALL_ONES))
				advance_statsn = false;
		पूर्ण

		SET_FIELD(task_params->sqe->flags, ISCSI_WQE_RESPONSE,
			  advance_statsn ? 1 : 0);

		अगर (task_params->tx_io_size) अणु
			SET_FIELD(task_params->sqe->contlen_cdbsize,
				  ISCSI_WQE_CONT_LEN, task_params->tx_io_size);

		अगर (scsi_is_slow_sgl(sgl_task_params->num_sges,
				     sgl_task_params->small_mid_sge))
			SET_FIELD(task_params->sqe->flags, ISCSI_WQE_NUM_SGES,
				  ISCSI_WQE_NUM_SGES_SLOWIO);
		अन्यथा
			SET_FIELD(task_params->sqe->flags, ISCSI_WQE_NUM_SGES,
				  min(sgl_task_params->num_sges,
				      (u16)SCSI_NUM_SGES_SLOW_SGL_THR));
		पूर्ण
	पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम init_शेष_iscsi_task(काष्ठा iscsi_task_params *task_params,
				    काष्ठा data_hdr *pdu_header,
				    क्रमागत iscsi_task_type task_type)
अणु
	काष्ठा e4_iscsi_task_context *context;
	u32 val;
	u16 index;
	u8 val_byte;

	context = task_params->context;
	val_byte = context->mstorm_ag_context.cdu_validation;
	स_रखो(context, 0, माप(*context));
	context->mstorm_ag_context.cdu_validation = val_byte;

	क्रम (index = 0; index <
	     ARRAY_SIZE(context->ystorm_st_context.pdu_hdr.data.data);
	     index++) अणु
		val = cpu_to_le32(pdu_header->data[index]);
		context->ystorm_st_context.pdu_hdr.data.data[index] = val;
	पूर्ण

	context->mstorm_st_context.task_type = task_type;
	context->mstorm_ag_context.task_cid =
					    cpu_to_le16(task_params->conn_icid);

	SET_FIELD(context->ustorm_ag_context.flags1,
		  E4_USTORM_ISCSI_TASK_AG_CTX_R2T2RECV, 1);

	context->ustorm_st_context.task_type = task_type;
	context->ustorm_st_context.cq_rss_number = task_params->cq_rss_number;
	context->ustorm_ag_context.icid = cpu_to_le16(task_params->conn_icid);
पूर्ण

अटल
व्योम init_initiator_rw_cdb_ystorm_context(काष्ठा ystorm_iscsi_task_st_ctx *ystc,
					  काष्ठा scsi_initiator_cmd_params *cmd)
अणु
	जोड़ iscsi_task_hdr *ctx_pdu_hdr = &ystc->pdu_hdr;
	u32 val;

	अगर (!cmd->extended_cdb_sge.sge_len)
		वापस;

	SET_FIELD(ctx_pdu_hdr->ext_cdb_cmd.hdr_second_dword,
		  ISCSI_EXT_CDB_CMD_HDR_CDB_SIZE,
		  cmd->extended_cdb_sge.sge_len);
	val = cpu_to_le32(cmd->extended_cdb_sge.sge_addr.lo);
	ctx_pdu_hdr->ext_cdb_cmd.cdb_sge.sge_addr.lo = val;
	val = cpu_to_le32(cmd->extended_cdb_sge.sge_addr.hi);
	ctx_pdu_hdr->ext_cdb_cmd.cdb_sge.sge_addr.hi = val;
	val = cpu_to_le32(cmd->extended_cdb_sge.sge_len);
	ctx_pdu_hdr->ext_cdb_cmd.cdb_sge.sge_len  = val;
पूर्ण

अटल
व्योम init_ustorm_task_contexts(काष्ठा ustorm_iscsi_task_st_ctx *ustorm_st_cxt,
			काष्ठा e4_ustorm_iscsi_task_ag_ctx *ustorm_ag_cxt,
			u32 reमुख्यing_recv_len, u32 expected_data_transfer_len,
			u8 num_sges, bool tx_dअगर_conn_err_en)
अणु
	u32 val;

	ustorm_st_cxt->rem_rcv_len = cpu_to_le32(reमुख्यing_recv_len);
	ustorm_ag_cxt->exp_data_acked = cpu_to_le32(expected_data_transfer_len);
	val = cpu_to_le32(expected_data_transfer_len);
	ustorm_st_cxt->exp_data_transfer_len = val;
	SET_FIELD(ustorm_st_cxt->reg1.reg1_map, ISCSI_REG1_NUM_SGES, num_sges);
	SET_FIELD(ustorm_ag_cxt->flags2,
		  E4_USTORM_ISCSI_TASK_AG_CTX_DIF_ERROR_CF_EN,
		  tx_dअगर_conn_err_en ? 1 : 0);
पूर्ण

अटल
व्योम set_rw_exp_data_acked_and_cont_len(काष्ठा e4_iscsi_task_context *context,
					काष्ठा iscsi_conn_params  *conn_params,
					क्रमागत iscsi_task_type task_type,
					u32 task_size,
					u32 exp_data_transfer_len,
					u8 total_ahs_length)
अणु
	u32 max_unsolicited_data = 0, val;

	अगर (total_ahs_length &&
	    (task_type == ISCSI_TASK_TYPE_INITIATOR_WRITE ||
	     task_type == ISCSI_TASK_TYPE_INITIATOR_READ))
		SET_FIELD(context->ustorm_st_context.flags2,
			  USTORM_ISCSI_TASK_ST_CTX_AHS_EXIST, 1);

	चयन (task_type) अणु
	हाल ISCSI_TASK_TYPE_INITIATOR_WRITE:
		अगर (!conn_params->initial_r2t)
			max_unsolicited_data = conn_params->first_burst_length;
		अन्यथा अगर (conn_params->immediate_data)
			max_unsolicited_data =
					  min(conn_params->first_burst_length,
					      conn_params->max_send_pdu_length);

		context->ustorm_ag_context.exp_data_acked =
				   cpu_to_le32(total_ahs_length == 0 ?
						min(exp_data_transfer_len,
						    max_unsolicited_data) :
						((u32)(total_ahs_length +
						       ISCSI_AHS_CNTL_SIZE)));
		अवरोध;
	हाल ISCSI_TASK_TYPE_TARGET_READ:
		val = cpu_to_le32(exp_data_transfer_len);
		context->ustorm_ag_context.exp_data_acked = val;
		अवरोध;
	हाल ISCSI_TASK_TYPE_INITIATOR_READ:
		context->ustorm_ag_context.exp_data_acked =
					cpu_to_le32((total_ahs_length == 0 ? 0 :
						     total_ahs_length +
						     ISCSI_AHS_CNTL_SIZE));
		अवरोध;
	हाल ISCSI_TASK_TYPE_TARGET_WRITE:
		val = cpu_to_le32(task_size);
		context->ustorm_ag_context.exp_cont_len = val;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल
व्योम init_rtdअगर_task_context(काष्ठा rdअगर_task_context *rdअगर_context,
			     काष्ठा tdअगर_task_context *tdअगर_context,
			     काष्ठा scsi_dअगर_task_params *dअगर_task_params,
			     क्रमागत iscsi_task_type task_type)
अणु
	u32 val;

	अगर (!dअगर_task_params->dअगर_on_network || !dअगर_task_params->dअगर_on_host)
		वापस;

	अगर (task_type == ISCSI_TASK_TYPE_TARGET_WRITE ||
	    task_type == ISCSI_TASK_TYPE_INITIATOR_READ) अणु
		rdअगर_context->app_tag_value =
				  cpu_to_le16(dअगर_task_params->application_tag);
		rdअगर_context->partial_crc_value = cpu_to_le16(0xffff);
		val = cpu_to_le32(dअगर_task_params->initial_ref_tag);
		rdअगर_context->initial_ref_tag = val;
		rdअगर_context->app_tag_mask =
			     cpu_to_le16(dअगर_task_params->application_tag_mask);
		SET_FIELD(rdअगर_context->flags0, RDIF_TASK_CONTEXT_CRC_SEED,
			  dअगर_task_params->crc_seed ? 1 : 0);
		SET_FIELD(rdअगर_context->flags0,
			  RDIF_TASK_CONTEXT_HOST_GUARD_TYPE,
			  dअगर_task_params->host_guard_type);
		SET_FIELD(rdअगर_context->flags0,
			  RDIF_TASK_CONTEXT_PROTECTION_TYPE,
			  dअगर_task_params->protection_type);
		SET_FIELD(rdअगर_context->flags0,
			  RDIF_TASK_CONTEXT_INITIAL_REF_TAG_VALID, 1);
		SET_FIELD(rdअगर_context->flags0,
			  RDIF_TASK_CONTEXT_KEEP_REF_TAG_CONST,
			  dअगर_task_params->keep_ref_tag_स्थिर ? 1 : 0);
		SET_FIELD(rdअगर_context->flags1,
			  RDIF_TASK_CONTEXT_VALIDATE_APP_TAG,
			  (dअगर_task_params->validate_app_tag &&
			  dअगर_task_params->dअगर_on_network) ? 1 : 0);
		SET_FIELD(rdअगर_context->flags1,
			  RDIF_TASK_CONTEXT_VALIDATE_GUARD,
			  (dअगर_task_params->validate_guard &&
			  dअगर_task_params->dअगर_on_network) ? 1 : 0);
		SET_FIELD(rdअगर_context->flags1,
			  RDIF_TASK_CONTEXT_VALIDATE_REF_TAG,
			  (dअगर_task_params->validate_ref_tag &&
			  dअगर_task_params->dअगर_on_network) ? 1 : 0);
		SET_FIELD(rdअगर_context->flags1,
			  RDIF_TASK_CONTEXT_HOST_INTERFACE,
			  dअगर_task_params->dअगर_on_host ? 1 : 0);
		SET_FIELD(rdअगर_context->flags1,
			  RDIF_TASK_CONTEXT_NETWORK_INTERFACE,
			  dअगर_task_params->dअगर_on_network ? 1 : 0);
		SET_FIELD(rdअगर_context->flags1,
			  RDIF_TASK_CONTEXT_FORWARD_GUARD,
			  dअगर_task_params->क्रमward_guard ? 1 : 0);
		SET_FIELD(rdअगर_context->flags1,
			  RDIF_TASK_CONTEXT_FORWARD_APP_TAG,
			  dअगर_task_params->क्रमward_app_tag ? 1 : 0);
		SET_FIELD(rdअगर_context->flags1,
			  RDIF_TASK_CONTEXT_FORWARD_REF_TAG,
			  dअगर_task_params->क्रमward_ref_tag ? 1 : 0);
		SET_FIELD(rdअगर_context->flags1,
			  RDIF_TASK_CONTEXT_FORWARD_APP_TAG_WITH_MASK,
			  dअगर_task_params->क्रमward_app_tag_with_mask ? 1 : 0);
		SET_FIELD(rdअगर_context->flags1,
			  RDIF_TASK_CONTEXT_FORWARD_REF_TAG_WITH_MASK,
			  dअगर_task_params->क्रमward_ref_tag_with_mask ? 1 : 0);
		SET_FIELD(rdअगर_context->flags1,
			  RDIF_TASK_CONTEXT_INTERVAL_SIZE,
			  dअगर_task_params->dअगर_block_size_log - 9);
		SET_FIELD(rdअगर_context->state,
			  RDIF_TASK_CONTEXT_REF_TAG_MASK,
			  dअगर_task_params->ref_tag_mask);
		SET_FIELD(rdअगर_context->state, RDIF_TASK_CONTEXT_IGNORE_APP_TAG,
			  dअगर_task_params->ignore_app_tag);
	पूर्ण

	अगर (task_type == ISCSI_TASK_TYPE_TARGET_READ ||
	    task_type == ISCSI_TASK_TYPE_INITIATOR_WRITE) अणु
		tdअगर_context->app_tag_value =
				  cpu_to_le16(dअगर_task_params->application_tag);
		tdअगर_context->partial_crc_value_b =
		       cpu_to_le16(dअगर_task_params->crc_seed ? 0xffff : 0x0000);
		tdअगर_context->partial_crc_value_a =
		       cpu_to_le16(dअगर_task_params->crc_seed ? 0xffff : 0x0000);
		SET_FIELD(tdअगर_context->flags0, TDIF_TASK_CONTEXT_CRC_SEED,
			  dअगर_task_params->crc_seed ? 1 : 0);

		SET_FIELD(tdअगर_context->flags0,
			  TDIF_TASK_CONTEXT_SET_ERROR_WITH_EOP,
			  dअगर_task_params->tx_dअगर_conn_err_en ? 1 : 0);
		SET_FIELD(tdअगर_context->flags1, TDIF_TASK_CONTEXT_FORWARD_GUARD,
			  dअगर_task_params->क्रमward_guard   ? 1 : 0);
		SET_FIELD(tdअगर_context->flags1,
			  TDIF_TASK_CONTEXT_FORWARD_APP_TAG,
			  dअगर_task_params->क्रमward_app_tag ? 1 : 0);
		SET_FIELD(tdअगर_context->flags1,
			  TDIF_TASK_CONTEXT_FORWARD_REF_TAG,
			  dअगर_task_params->क्रमward_ref_tag ? 1 : 0);
		SET_FIELD(tdअगर_context->flags1, TDIF_TASK_CONTEXT_INTERVAL_SIZE,
			  dअगर_task_params->dअगर_block_size_log - 9);
		SET_FIELD(tdअगर_context->flags1,
			  TDIF_TASK_CONTEXT_HOST_INTERFACE,
			  dअगर_task_params->dअगर_on_host    ? 1 : 0);
		SET_FIELD(tdअगर_context->flags1,
			  TDIF_TASK_CONTEXT_NETWORK_INTERFACE,
			  dअगर_task_params->dअगर_on_network ? 1 : 0);
		val = cpu_to_le32(dअगर_task_params->initial_ref_tag);
		tdअगर_context->initial_ref_tag = val;
		tdअगर_context->app_tag_mask =
			     cpu_to_le16(dअगर_task_params->application_tag_mask);
		SET_FIELD(tdअगर_context->flags0,
			  TDIF_TASK_CONTEXT_HOST_GUARD_TYPE,
			  dअगर_task_params->host_guard_type);
		SET_FIELD(tdअगर_context->flags0,
			  TDIF_TASK_CONTEXT_PROTECTION_TYPE,
			  dअगर_task_params->protection_type);
		SET_FIELD(tdअगर_context->flags0,
			  TDIF_TASK_CONTEXT_INITIAL_REF_TAG_VALID,
			  dअगर_task_params->initial_ref_tag_is_valid ? 1 : 0);
		SET_FIELD(tdअगर_context->flags0,
			  TDIF_TASK_CONTEXT_KEEP_REF_TAG_CONST,
			  dअगर_task_params->keep_ref_tag_स्थिर ? 1 : 0);
		SET_FIELD(tdअगर_context->flags1,
			  TDIF_TASK_CONTEXT_VALIDATE_GUARD,
			  (dअगर_task_params->validate_guard &&
			   dअगर_task_params->dअगर_on_host) ? 1 : 0);
		SET_FIELD(tdअगर_context->flags1,
			  TDIF_TASK_CONTEXT_VALIDATE_APP_TAG,
			  (dअगर_task_params->validate_app_tag &&
			  dअगर_task_params->dअगर_on_host) ? 1 : 0);
		SET_FIELD(tdअगर_context->flags1,
			  TDIF_TASK_CONTEXT_VALIDATE_REF_TAG,
			  (dअगर_task_params->validate_ref_tag &&
			   dअगर_task_params->dअगर_on_host) ? 1 : 0);
		SET_FIELD(tdअगर_context->flags1,
			  TDIF_TASK_CONTEXT_FORWARD_APP_TAG_WITH_MASK,
			  dअगर_task_params->क्रमward_app_tag_with_mask ? 1 : 0);
		SET_FIELD(tdअगर_context->flags1,
			  TDIF_TASK_CONTEXT_FORWARD_REF_TAG_WITH_MASK,
			  dअगर_task_params->क्रमward_ref_tag_with_mask ? 1 : 0);
		SET_FIELD(tdअगर_context->flags1,
			  TDIF_TASK_CONTEXT_REF_TAG_MASK,
			  dअगर_task_params->ref_tag_mask);
		SET_FIELD(tdअगर_context->flags0,
			  TDIF_TASK_CONTEXT_IGNORE_APP_TAG,
			  dअगर_task_params->ignore_app_tag ? 1 : 0);
	पूर्ण
पूर्ण

अटल व्योम set_local_completion_context(काष्ठा e4_iscsi_task_context *context)
अणु
	SET_FIELD(context->ystorm_st_context.state.flags,
		  YSTORM_ISCSI_TASK_STATE_LOCAL_COMP, 1);
	SET_FIELD(context->ustorm_st_context.flags,
		  USTORM_ISCSI_TASK_ST_CTX_LOCAL_COMP, 1);
पूर्ण

अटल पूर्णांक init_rw_iscsi_task(काष्ठा iscsi_task_params *task_params,
			      क्रमागत iscsi_task_type task_type,
			      काष्ठा iscsi_conn_params *conn_params,
			      काष्ठा iscsi_common_hdr *pdu_header,
			      काष्ठा scsi_sgl_task_params *sgl_task_params,
			      काष्ठा scsi_initiator_cmd_params *cmd_params,
			      काष्ठा scsi_dअगर_task_params *dअगर_task_params)
अणु
	u32 exp_data_transfer_len = conn_params->max_burst_length;
	काष्ठा e4_iscsi_task_context *cxt;
	bool slow_io = false;
	u32 task_size, val;
	u8 num_sges = 0;

	task_size = calc_rw_task_size(task_params, task_type, sgl_task_params,
				      dअगर_task_params);

	init_शेष_iscsi_task(task_params, (काष्ठा data_hdr *)pdu_header,
				task_type);

	cxt = task_params->context;


	अगर (task_type == ISCSI_TASK_TYPE_TARGET_READ) अणु
		set_local_completion_context(cxt);
	पूर्ण अन्यथा अगर (task_type == ISCSI_TASK_TYPE_TARGET_WRITE) अणु
		val = cpu_to_le32(task_size +
			   ((काष्ठा iscsi_r2t_hdr *)pdu_header)->buffer_offset);
		cxt->ystorm_st_context.pdu_hdr.r2t.desired_data_trns_len = val;
		cxt->mstorm_st_context.expected_itt =
						   cpu_to_le32(pdu_header->itt);
	पूर्ण अन्यथा अणु
		val = cpu_to_le32(task_size);
		cxt->ystorm_st_context.pdu_hdr.cmd.expected_transfer_length =
									    val;
		init_initiator_rw_cdb_ystorm_context(&cxt->ystorm_st_context,
						     cmd_params);
		val = cpu_to_le32(cmd_params->sense_data_buffer_phys_addr.lo);
		cxt->mstorm_st_context.sense_db.lo = val;

		val = cpu_to_le32(cmd_params->sense_data_buffer_phys_addr.hi);
		cxt->mstorm_st_context.sense_db.hi = val;
	पूर्ण

	अगर (task_params->tx_io_size) अणु
		init_dअगर_context_flags(&cxt->ystorm_st_context.state.dअगर_flags,
				       dअगर_task_params);
		init_dअगर_context_flags(&cxt->ustorm_st_context.dअगर_flags,
				       dअगर_task_params);
		init_scsi_sgl_context(&cxt->ystorm_st_context.state.sgl_params,
				      &cxt->ystorm_st_context.state.data_desc,
				      sgl_task_params);

		slow_io = scsi_is_slow_sgl(sgl_task_params->num_sges,
					   sgl_task_params->small_mid_sge);

		num_sges = !slow_io ? min_t(u16, sgl_task_params->num_sges,
					    (u16)SCSI_NUM_SGES_SLOW_SGL_THR) :
				      ISCSI_WQE_NUM_SGES_SLOWIO;

		अगर (slow_io) अणु
			SET_FIELD(cxt->ystorm_st_context.state.flags,
				  YSTORM_ISCSI_TASK_STATE_SLOW_IO, 1);
		पूर्ण
	पूर्ण अन्यथा अगर (task_params->rx_io_size) अणु
		init_dअगर_context_flags(&cxt->mstorm_st_context.dअगर_flags,
				       dअगर_task_params);
		init_scsi_sgl_context(&cxt->mstorm_st_context.sgl_params,
				      &cxt->mstorm_st_context.data_desc,
				      sgl_task_params);
		num_sges = !scsi_is_slow_sgl(sgl_task_params->num_sges,
				sgl_task_params->small_mid_sge) ?
				min_t(u16, sgl_task_params->num_sges,
				      (u16)SCSI_NUM_SGES_SLOW_SGL_THR) :
				ISCSI_WQE_NUM_SGES_SLOWIO;
		cxt->mstorm_st_context.rem_task_size = cpu_to_le32(task_size);
	पूर्ण

	अगर (exp_data_transfer_len > task_size  ||
	    task_type != ISCSI_TASK_TYPE_TARGET_WRITE)
		exp_data_transfer_len = task_size;

	init_ustorm_task_contexts(&task_params->context->ustorm_st_context,
				  &task_params->context->ustorm_ag_context,
				  task_size, exp_data_transfer_len, num_sges,
				  dअगर_task_params ?
				  dअगर_task_params->tx_dअगर_conn_err_en : false);

	set_rw_exp_data_acked_and_cont_len(task_params->context, conn_params,
					   task_type, task_size,
					   exp_data_transfer_len,
					GET_FIELD(pdu_header->hdr_second_dword,
						  ISCSI_CMD_HDR_TOTAL_AHS_LEN));

	अगर (dअगर_task_params)
		init_rtdअगर_task_context(&task_params->context->rdअगर_context,
					&task_params->context->tdअगर_context,
					dअगर_task_params, task_type);

	init_sqe(task_params, sgl_task_params, dअगर_task_params, pdu_header,
		 cmd_params, task_type, false);

	वापस 0;
पूर्ण

पूर्णांक init_initiator_rw_iscsi_task(काष्ठा iscsi_task_params *task_params,
				 काष्ठा iscsi_conn_params *conn_params,
				 काष्ठा scsi_initiator_cmd_params *cmd_params,
				 काष्ठा iscsi_cmd_hdr *cmd_header,
				 काष्ठा scsi_sgl_task_params *tx_sgl_params,
				 काष्ठा scsi_sgl_task_params *rx_sgl_params,
				 काष्ठा scsi_dअगर_task_params *dअगर_task_params)
अणु
	अगर (GET_FIELD(cmd_header->flags_attr, ISCSI_CMD_HDR_WRITE))
		वापस init_rw_iscsi_task(task_params,
					  ISCSI_TASK_TYPE_INITIATOR_WRITE,
					  conn_params,
					  (काष्ठा iscsi_common_hdr *)cmd_header,
					  tx_sgl_params, cmd_params,
					  dअगर_task_params);
	अन्यथा अगर (GET_FIELD(cmd_header->flags_attr, ISCSI_CMD_HDR_READ) ||
		 (task_params->rx_io_size == 0 && task_params->tx_io_size == 0))
		वापस init_rw_iscsi_task(task_params,
					  ISCSI_TASK_TYPE_INITIATOR_READ,
					  conn_params,
					  (काष्ठा iscsi_common_hdr *)cmd_header,
					  rx_sgl_params, cmd_params,
					  dअगर_task_params);
	अन्यथा
		वापस -1;
पूर्ण

पूर्णांक init_initiator_login_request_task(काष्ठा iscsi_task_params *task_params,
				      काष्ठा iscsi_login_req_hdr  *login_header,
				      काष्ठा scsi_sgl_task_params *tx_params,
				      काष्ठा scsi_sgl_task_params *rx_params)
अणु
	काष्ठा e4_iscsi_task_context *cxt;

	cxt = task_params->context;

	init_शेष_iscsi_task(task_params,
				(काष्ठा data_hdr *)login_header,
				ISCSI_TASK_TYPE_MIDPATH);

	init_ustorm_task_contexts(&cxt->ustorm_st_context,
				  &cxt->ustorm_ag_context,
				  task_params->rx_io_size ?
				  rx_params->total_buffer_size : 0,
				  task_params->tx_io_size ?
				  tx_params->total_buffer_size : 0, 0,
				  0);

	अगर (task_params->tx_io_size)
		init_scsi_sgl_context(&cxt->ystorm_st_context.state.sgl_params,
				      &cxt->ystorm_st_context.state.data_desc,
				      tx_params);

	अगर (task_params->rx_io_size)
		init_scsi_sgl_context(&cxt->mstorm_st_context.sgl_params,
				      &cxt->mstorm_st_context.data_desc,
				      rx_params);

	cxt->mstorm_st_context.rem_task_size =
			cpu_to_le32(task_params->rx_io_size ?
				    rx_params->total_buffer_size : 0);

	init_sqe(task_params, tx_params, शून्य,
		 (काष्ठा iscsi_common_hdr *)login_header, शून्य,
		 ISCSI_TASK_TYPE_MIDPATH, false);

	वापस 0;
पूर्ण

पूर्णांक init_initiator_nop_out_task(काष्ठा iscsi_task_params *task_params,
				काष्ठा iscsi_nop_out_hdr *nop_out_pdu_header,
				काष्ठा scsi_sgl_task_params *tx_sgl_task_params,
				काष्ठा scsi_sgl_task_params *rx_sgl_task_params)
अणु
	काष्ठा e4_iscsi_task_context *cxt;

	cxt = task_params->context;

	init_शेष_iscsi_task(task_params,
				(काष्ठा data_hdr *)nop_out_pdu_header,
				ISCSI_TASK_TYPE_MIDPATH);

	अगर (nop_out_pdu_header->itt == ISCSI_ITT_ALL_ONES)
		set_local_completion_context(task_params->context);

	अगर (task_params->tx_io_size)
		init_scsi_sgl_context(&cxt->ystorm_st_context.state.sgl_params,
				      &cxt->ystorm_st_context.state.data_desc,
				      tx_sgl_task_params);

	अगर (task_params->rx_io_size)
		init_scsi_sgl_context(&cxt->mstorm_st_context.sgl_params,
				      &cxt->mstorm_st_context.data_desc,
				      rx_sgl_task_params);

	init_ustorm_task_contexts(&cxt->ustorm_st_context,
				  &cxt->ustorm_ag_context,
				  task_params->rx_io_size ?
				  rx_sgl_task_params->total_buffer_size : 0,
				  task_params->tx_io_size ?
				  tx_sgl_task_params->total_buffer_size : 0,
				  0, 0);

	cxt->mstorm_st_context.rem_task_size =
				cpu_to_le32(task_params->rx_io_size ?
					rx_sgl_task_params->total_buffer_size :
					0);

	init_sqe(task_params, tx_sgl_task_params, शून्य,
		 (काष्ठा iscsi_common_hdr *)nop_out_pdu_header, शून्य,
		 ISCSI_TASK_TYPE_MIDPATH, false);

	वापस 0;
पूर्ण

पूर्णांक init_initiator_logout_request_task(काष्ठा iscsi_task_params *task_params,
				       काष्ठा iscsi_logout_req_hdr *logout_hdr,
				       काष्ठा scsi_sgl_task_params *tx_params,
				       काष्ठा scsi_sgl_task_params *rx_params)
अणु
	काष्ठा e4_iscsi_task_context *cxt;

	cxt = task_params->context;

	init_शेष_iscsi_task(task_params,
				(काष्ठा data_hdr *)logout_hdr,
				ISCSI_TASK_TYPE_MIDPATH);

	अगर (task_params->tx_io_size)
		init_scsi_sgl_context(&cxt->ystorm_st_context.state.sgl_params,
				      &cxt->ystorm_st_context.state.data_desc,
				      tx_params);

	अगर (task_params->rx_io_size)
		init_scsi_sgl_context(&cxt->mstorm_st_context.sgl_params,
				      &cxt->mstorm_st_context.data_desc,
				      rx_params);

	init_ustorm_task_contexts(&cxt->ustorm_st_context,
				  &cxt->ustorm_ag_context,
				  task_params->rx_io_size ?
				  rx_params->total_buffer_size : 0,
				  task_params->tx_io_size ?
				  tx_params->total_buffer_size : 0,
				  0, 0);

	cxt->mstorm_st_context.rem_task_size =
					cpu_to_le32(task_params->rx_io_size ?
					rx_params->total_buffer_size : 0);

	init_sqe(task_params, tx_params, शून्य,
		 (काष्ठा iscsi_common_hdr *)logout_hdr, शून्य,
		 ISCSI_TASK_TYPE_MIDPATH, false);

	वापस 0;
पूर्ण

पूर्णांक init_initiator_पंचांगf_request_task(काष्ठा iscsi_task_params *task_params,
				    काष्ठा iscsi_पंचांगf_request_hdr *पंचांगf_header)
अणु
	init_शेष_iscsi_task(task_params, (काष्ठा data_hdr *)पंचांगf_header,
				ISCSI_TASK_TYPE_MIDPATH);

	init_sqe(task_params, शून्य, शून्य,
		 (काष्ठा iscsi_common_hdr *)पंचांगf_header, शून्य,
		 ISCSI_TASK_TYPE_MIDPATH, false);

	वापस 0;
पूर्ण

पूर्णांक init_initiator_text_request_task(काष्ठा iscsi_task_params *task_params,
				     काष्ठा iscsi_text_request_hdr *text_header,
				     काष्ठा scsi_sgl_task_params *tx_params,
				     काष्ठा scsi_sgl_task_params *rx_params)
अणु
	काष्ठा e4_iscsi_task_context *cxt;

	cxt = task_params->context;

	init_शेष_iscsi_task(task_params,
				(काष्ठा data_hdr *)text_header,
				ISCSI_TASK_TYPE_MIDPATH);

	अगर (task_params->tx_io_size)
		init_scsi_sgl_context(&cxt->ystorm_st_context.state.sgl_params,
				      &cxt->ystorm_st_context.state.data_desc,
				      tx_params);

	अगर (task_params->rx_io_size)
		init_scsi_sgl_context(&cxt->mstorm_st_context.sgl_params,
				      &cxt->mstorm_st_context.data_desc,
				      rx_params);

	cxt->mstorm_st_context.rem_task_size =
				cpu_to_le32(task_params->rx_io_size ?
					rx_params->total_buffer_size : 0);

	init_ustorm_task_contexts(&cxt->ustorm_st_context,
				  &cxt->ustorm_ag_context,
				  task_params->rx_io_size ?
				  rx_params->total_buffer_size : 0,
				  task_params->tx_io_size ?
				  tx_params->total_buffer_size : 0, 0, 0);

	init_sqe(task_params, tx_params, शून्य,
		 (काष्ठा iscsi_common_hdr *)text_header, शून्य,
		 ISCSI_TASK_TYPE_MIDPATH, false);

	वापस 0;
पूर्ण

पूर्णांक init_cleanup_task(काष्ठा iscsi_task_params *task_params)
अणु
	init_sqe(task_params, शून्य, शून्य, शून्य, शून्य, ISCSI_TASK_TYPE_MIDPATH,
		 true);
	वापस 0;
पूर्ण
