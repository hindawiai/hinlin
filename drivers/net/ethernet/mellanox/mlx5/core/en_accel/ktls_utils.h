<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB */
/* Copyright (c) 2020, Mellanox Technologies inc. All rights reserved. */

#अगर_अघोषित __MLX5E_KTLS_UTILS_H__
#घोषणा __MLX5E_KTLS_UTILS_H__

#समावेश <net/tls.h>
#समावेश "en.h"
#समावेश "accel/tls.h"

क्रमागत अणु
	MLX5E_TLS_PROGRESS_PARAMS_AUTH_STATE_NO_OFFLOAD     = 0,
	MLX5E_TLS_PROGRESS_PARAMS_AUTH_STATE_OFFLOAD        = 1,
	MLX5E_TLS_PROGRESS_PARAMS_AUTH_STATE_AUTHENTICATION = 2,
पूर्ण;

क्रमागत अणु
	MLX5E_TLS_PROGRESS_PARAMS_RECORD_TRACKER_STATE_START     = 0,
	MLX5E_TLS_PROGRESS_PARAMS_RECORD_TRACKER_STATE_TRACKING  = 1,
	MLX5E_TLS_PROGRESS_PARAMS_RECORD_TRACKER_STATE_SEARCHING = 2,
पूर्ण;

पूर्णांक mlx5e_ktls_add_tx(काष्ठा net_device *netdev, काष्ठा sock *sk,
		      काष्ठा tls_crypto_info *crypto_info, u32 start_offload_tcp_sn);
व्योम mlx5e_ktls_del_tx(काष्ठा net_device *netdev, काष्ठा tls_context *tls_ctx);
पूर्णांक mlx5e_ktls_add_rx(काष्ठा net_device *netdev, काष्ठा sock *sk,
		      काष्ठा tls_crypto_info *crypto_info, u32 start_offload_tcp_sn);
व्योम mlx5e_ktls_del_rx(काष्ठा net_device *netdev, काष्ठा tls_context *tls_ctx);
व्योम mlx5e_ktls_rx_resync(काष्ठा net_device *netdev, काष्ठा sock *sk, u32 seq, u8 *rcd_sn);

काष्ठा mlx5e_set_tls_अटल_params_wqe अणु
	काष्ठा mlx5_wqe_ctrl_seg ctrl;
	काष्ठा mlx5_wqe_umr_ctrl_seg uctrl;
	काष्ठा mlx5_mkey_seg mkc;
	काष्ठा mlx5_wqe_tls_अटल_params_seg params;
पूर्ण;

काष्ठा mlx5e_set_tls_progress_params_wqe अणु
	काष्ठा mlx5_wqe_ctrl_seg ctrl;
	काष्ठा mlx5_wqe_tls_progress_params_seg params;
पूर्ण;

काष्ठा mlx5e_get_tls_progress_params_wqe अणु
	काष्ठा mlx5_wqe_ctrl_seg ctrl;
	काष्ठा mlx5_seg_get_psv  psv;
पूर्ण;

#घोषणा MLX5E_TLS_SET_STATIC_PARAMS_WQEBBS \
	(DIV_ROUND_UP(माप(काष्ठा mlx5e_set_tls_अटल_params_wqe), MLX5_SEND_WQE_BB))

#घोषणा MLX5E_TLS_SET_PROGRESS_PARAMS_WQEBBS \
	(DIV_ROUND_UP(माप(काष्ठा mlx5e_set_tls_progress_params_wqe), MLX5_SEND_WQE_BB))

#घोषणा MLX5E_KTLS_GET_PROGRESS_WQEBBS \
	(DIV_ROUND_UP(माप(काष्ठा mlx5e_get_tls_progress_params_wqe), MLX5_SEND_WQE_BB))

#घोषणा MLX5E_TLS_FETCH_SET_STATIC_PARAMS_WQE(sq, pi) \
	((काष्ठा mlx5e_set_tls_अटल_params_wqe *)\
	 mlx5e_fetch_wqe(&(sq)->wq, pi, माप(काष्ठा mlx5e_set_tls_अटल_params_wqe)))

#घोषणा MLX5E_TLS_FETCH_SET_PROGRESS_PARAMS_WQE(sq, pi) \
	((काष्ठा mlx5e_set_tls_progress_params_wqe *)\
	 mlx5e_fetch_wqe(&(sq)->wq, pi, माप(काष्ठा mlx5e_set_tls_progress_params_wqe)))

#घोषणा MLX5E_TLS_FETCH_GET_PROGRESS_PARAMS_WQE(sq, pi) \
	((काष्ठा mlx5e_get_tls_progress_params_wqe *)\
	 mlx5e_fetch_wqe(&(sq)->wq, pi, माप(काष्ठा mlx5e_get_tls_progress_params_wqe)))

#घोषणा MLX5E_TLS_FETCH_DUMP_WQE(sq, pi) \
	((काष्ठा mlx5e_dump_wqe *)\
	 mlx5e_fetch_wqe(&(sq)->wq, pi, माप(काष्ठा mlx5e_dump_wqe)))

व्योम
mlx5e_ktls_build_अटल_params(काष्ठा mlx5e_set_tls_अटल_params_wqe *wqe,
			       u16 pc, u32 sqn,
			       काष्ठा tls12_crypto_info_aes_gcm_128 *info,
			       u32 tis_tir_num, u32 key_id, u32 resync_tcp_sn,
			       bool fence, क्रमागत tls_offload_ctx_dir direction);
व्योम
mlx5e_ktls_build_progress_params(काष्ठा mlx5e_set_tls_progress_params_wqe *wqe,
				 u16 pc, u32 sqn,
				 u32 tis_tir_num, bool fence,
				 u32 next_record_tcp_sn,
				 क्रमागत tls_offload_ctx_dir direction);

#पूर्ण_अगर /* __MLX5E_TLS_UTILS_H__ */
