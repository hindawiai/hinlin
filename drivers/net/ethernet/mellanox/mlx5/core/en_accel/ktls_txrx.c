<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB
/* Copyright (c) 2020, Mellanox Technologies inc. All rights reserved. */

#समावेश "en_accel/ktls_txrx.h"
#समावेश "en_accel/ktls_utils.h"

क्रमागत अणु
	MLX5E_STATIC_PARAMS_CONTEXT_TLS_1_2 = 0x2,
पूर्ण;

क्रमागत अणु
	MLX5E_ENCRYPTION_STANDARD_TLS = 0x1,
पूर्ण;

#घोषणा EXTRACT_INFO_FIELDS करो अणु \
	salt    = info->salt;    \
	rec_seq = info->rec_seq; \
	salt_sz    = माप(info->salt);    \
	rec_seq_sz = माप(info->rec_seq); \
पूर्ण जबतक (0)

अटल व्योम
fill_अटल_params(काष्ठा mlx5_wqe_tls_अटल_params_seg *params,
		   काष्ठा tls12_crypto_info_aes_gcm_128 *info,
		   u32 key_id, u32 resync_tcp_sn)
अणु
	अक्षर *initial_rn, *gcm_iv;
	u16 salt_sz, rec_seq_sz;
	अक्षर *salt, *rec_seq;
	u8 tls_version;
	u8 *ctx;

	ctx = params->ctx;

	EXTRACT_INFO_FIELDS;

	gcm_iv      = MLX5_ADDR_OF(tls_अटल_params, ctx, gcm_iv);
	initial_rn  = MLX5_ADDR_OF(tls_अटल_params, ctx, initial_record_number);

	स_नकल(gcm_iv,      salt,    salt_sz);
	स_नकल(initial_rn,  rec_seq, rec_seq_sz);

	tls_version = MLX5E_STATIC_PARAMS_CONTEXT_TLS_1_2;

	MLX5_SET(tls_अटल_params, ctx, tls_version, tls_version);
	MLX5_SET(tls_अटल_params, ctx, स्थिर_1, 1);
	MLX5_SET(tls_अटल_params, ctx, स्थिर_2, 2);
	MLX5_SET(tls_अटल_params, ctx, encryption_standard,
		 MLX5E_ENCRYPTION_STANDARD_TLS);
	MLX5_SET(tls_अटल_params, ctx, resync_tcp_sn, resync_tcp_sn);
	MLX5_SET(tls_अटल_params, ctx, dek_index, key_id);
पूर्ण

व्योम
mlx5e_ktls_build_अटल_params(काष्ठा mlx5e_set_tls_अटल_params_wqe *wqe,
			       u16 pc, u32 sqn,
			       काष्ठा tls12_crypto_info_aes_gcm_128 *info,
			       u32 tis_tir_num, u32 key_id, u32 resync_tcp_sn,
			       bool fence, क्रमागत tls_offload_ctx_dir direction)
अणु
	काष्ठा mlx5_wqe_umr_ctrl_seg *ucseg = &wqe->uctrl;
	काष्ठा mlx5_wqe_ctrl_seg     *cseg  = &wqe->ctrl;
	u8 opmod = direction == TLS_OFFLOAD_CTX_सूची_TX ?
		MLX5_OPC_MOD_TLS_TIS_STATIC_PARAMS :
		MLX5_OPC_MOD_TLS_TIR_STATIC_PARAMS;

#घोषणा STATIC_PARAMS_DS_CNT DIV_ROUND_UP(माप(*wqe), MLX5_SEND_WQE_DS)

	cseg->opmod_idx_opcode = cpu_to_be32((pc << 8) | MLX5_OPCODE_UMR | (opmod << 24));
	cseg->qpn_ds           = cpu_to_be32((sqn << MLX5_WQE_CTRL_QPN_SHIFT) |
					     STATIC_PARAMS_DS_CNT);
	cseg->fm_ce_se         = fence ? MLX5_FENCE_MODE_INITIATOR_SMALL : 0;
	cseg->tis_tir_num      = cpu_to_be32(tis_tir_num << 8);

	ucseg->flags = MLX5_UMR_INLINE;
	ucseg->bsf_octowords = cpu_to_be16(MLX5_ST_SZ_BYTES(tls_अटल_params) / 16);

	fill_अटल_params(&wqe->params, info, key_id, resync_tcp_sn);
पूर्ण

अटल व्योम
fill_progress_params(काष्ठा mlx5_wqe_tls_progress_params_seg *params, u32 tis_tir_num,
		     u32 next_record_tcp_sn)
अणु
	u8 *ctx = params->ctx;

	params->tis_tir_num = cpu_to_be32(tis_tir_num);

	MLX5_SET(tls_progress_params, ctx, next_record_tcp_sn,
		 next_record_tcp_sn);
	MLX5_SET(tls_progress_params, ctx, record_tracker_state,
		 MLX5E_TLS_PROGRESS_PARAMS_RECORD_TRACKER_STATE_START);
	MLX5_SET(tls_progress_params, ctx, auth_state,
		 MLX5E_TLS_PROGRESS_PARAMS_AUTH_STATE_NO_OFFLOAD);
पूर्ण

व्योम
mlx5e_ktls_build_progress_params(काष्ठा mlx5e_set_tls_progress_params_wqe *wqe,
				 u16 pc, u32 sqn,
				 u32 tis_tir_num, bool fence,
				 u32 next_record_tcp_sn,
				 क्रमागत tls_offload_ctx_dir direction)
अणु
	काष्ठा mlx5_wqe_ctrl_seg *cseg = &wqe->ctrl;
	u8 opmod = direction == TLS_OFFLOAD_CTX_सूची_TX ?
		MLX5_OPC_MOD_TLS_TIS_PROGRESS_PARAMS :
		MLX5_OPC_MOD_TLS_TIR_PROGRESS_PARAMS;

#घोषणा PROGRESS_PARAMS_DS_CNT DIV_ROUND_UP(माप(*wqe), MLX5_SEND_WQE_DS)

	cseg->opmod_idx_opcode =
		cpu_to_be32((pc << 8) | MLX5_OPCODE_SET_PSV | (opmod << 24));
	cseg->qpn_ds           = cpu_to_be32((sqn << MLX5_WQE_CTRL_QPN_SHIFT) |
					     PROGRESS_PARAMS_DS_CNT);
	cseg->fm_ce_se         = fence ? MLX5_FENCE_MODE_INITIATOR_SMALL : 0;

	fill_progress_params(&wqe->params, tis_tir_num, next_record_tcp_sn);
पूर्ण

