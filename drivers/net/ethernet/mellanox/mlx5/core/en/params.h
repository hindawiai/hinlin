<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB */
/* Copyright (c) 2019 Mellanox Technologies. */

#अगर_अघोषित __MLX5_EN_PARAMS_H__
#घोषणा __MLX5_EN_PARAMS_H__

#समावेश "en.h"

काष्ठा mlx5e_xsk_param अणु
	u16 headroom;
	u16 chunk_size;
पूर्ण;

काष्ठा mlx5e_cq_param अणु
	u32                        cqc[MLX5_ST_SZ_DW(cqc)];
	काष्ठा mlx5_wq_param       wq;
	u16                        eq_ix;
	u8                         cq_period_mode;
पूर्ण;

काष्ठा mlx5e_rq_param अणु
	काष्ठा mlx5e_cq_param      cqp;
	u32                        rqc[MLX5_ST_SZ_DW(rqc)];
	काष्ठा mlx5_wq_param       wq;
	काष्ठा mlx5e_rq_frags_info frags_info;
पूर्ण;

काष्ठा mlx5e_sq_param अणु
	काष्ठा mlx5e_cq_param      cqp;
	u32                        sqc[MLX5_ST_SZ_DW(sqc)];
	काष्ठा mlx5_wq_param       wq;
	bool                       is_mpw;
	bool                       is_tls;
	u16                        stop_room;
पूर्ण;

काष्ठा mlx5e_channel_param अणु
	काष्ठा mlx5e_rq_param      rq;
	काष्ठा mlx5e_sq_param      txq_sq;
	काष्ठा mlx5e_sq_param      xdp_sq;
	काष्ठा mlx5e_sq_param      icosq;
	काष्ठा mlx5e_sq_param      async_icosq;
पूर्ण;

काष्ठा mlx5e_create_sq_param अणु
	काष्ठा mlx5_wq_ctrl        *wq_ctrl;
	u32                         cqn;
	u32                         ts_cqe_to_dest_cqn;
	u32                         tisn;
	u8                          tis_lst_sz;
	u8                          min_अंतरभूत_mode;
पूर्ण;

अटल अंतरभूत bool mlx5e_qid_get_ch_अगर_in_group(काष्ठा mlx5e_params *params,
						u16 qid,
						क्रमागत mlx5e_rq_group group,
						u16 *ix)
अणु
	पूर्णांक nch = params->num_channels;
	पूर्णांक ch = qid - nch * group;

	अगर (ch < 0 || ch >= nch)
		वापस false;

	*ix = ch;
	वापस true;
पूर्ण

अटल अंतरभूत व्योम mlx5e_qid_get_ch_and_group(काष्ठा mlx5e_params *params,
					      u16 qid,
					      u16 *ix,
					      क्रमागत mlx5e_rq_group *group)
अणु
	u16 nch = params->num_channels;

	*ix = qid % nch;
	*group = qid / nch;
पूर्ण

अटल अंतरभूत bool mlx5e_qid_validate(स्थिर काष्ठा mlx5e_profile *profile,
				      काष्ठा mlx5e_params *params, u64 qid)
अणु
	वापस qid < params->num_channels * profile->rq_groups;
पूर्ण

/* Parameter calculations */

व्योम mlx5e_reset_tx_moderation(काष्ठा mlx5e_params *params, u8 cq_period_mode);
व्योम mlx5e_reset_rx_moderation(काष्ठा mlx5e_params *params, u8 cq_period_mode);
व्योम mlx5e_set_tx_cq_mode_params(काष्ठा mlx5e_params *params, u8 cq_period_mode);
व्योम mlx5e_set_rx_cq_mode_params(काष्ठा mlx5e_params *params, u8 cq_period_mode);

bool slow_pci_heuristic(काष्ठा mlx5_core_dev *mdev);
bool mlx5e_striding_rq_possible(काष्ठा mlx5_core_dev *mdev, काष्ठा mlx5e_params *params);
व्योम mlx5e_build_rq_params(काष्ठा mlx5_core_dev *mdev, काष्ठा mlx5e_params *params);
व्योम mlx5e_set_rq_type(काष्ठा mlx5_core_dev *mdev, काष्ठा mlx5e_params *params);
व्योम mlx5e_init_rq_type_params(काष्ठा mlx5_core_dev *mdev, काष्ठा mlx5e_params *params);

bool mlx5e_verअगरy_rx_mpwqe_strides(काष्ठा mlx5_core_dev *mdev,
				   u8 log_stride_sz, u8 log_num_strides);
u16 mlx5e_get_linear_rq_headroom(काष्ठा mlx5e_params *params,
				 काष्ठा mlx5e_xsk_param *xsk);
u32 mlx5e_rx_get_min_frag_sz(काष्ठा mlx5e_params *params,
			     काष्ठा mlx5e_xsk_param *xsk);
u8 mlx5e_mpwqe_log_pkts_per_wqe(काष्ठा mlx5e_params *params,
				काष्ठा mlx5e_xsk_param *xsk);
bool mlx5e_rx_is_linear_skb(काष्ठा mlx5e_params *params,
			    काष्ठा mlx5e_xsk_param *xsk);
bool mlx5e_rx_mpwqe_is_linear_skb(काष्ठा mlx5_core_dev *mdev,
				  काष्ठा mlx5e_params *params,
				  काष्ठा mlx5e_xsk_param *xsk);
u8 mlx5e_mpwqe_get_log_rq_size(काष्ठा mlx5e_params *params,
			       काष्ठा mlx5e_xsk_param *xsk);
u8 mlx5e_mpwqe_get_log_stride_size(काष्ठा mlx5_core_dev *mdev,
				   काष्ठा mlx5e_params *params,
				   काष्ठा mlx5e_xsk_param *xsk);
u8 mlx5e_mpwqe_get_log_num_strides(काष्ठा mlx5_core_dev *mdev,
				   काष्ठा mlx5e_params *params,
				   काष्ठा mlx5e_xsk_param *xsk);
u16 mlx5e_get_rq_headroom(काष्ठा mlx5_core_dev *mdev,
			  काष्ठा mlx5e_params *params,
			  काष्ठा mlx5e_xsk_param *xsk);

/* Build queue parameters */

व्योम mlx5e_build_create_cq_param(काष्ठा mlx5e_create_cq_param *ccp, काष्ठा mlx5e_channel *c);
पूर्णांक mlx5e_build_rq_param(काष्ठा mlx5_core_dev *mdev,
			 काष्ठा mlx5e_params *params,
			 काष्ठा mlx5e_xsk_param *xsk,
			 u16 q_counter,
			 काष्ठा mlx5e_rq_param *param);
व्योम mlx5e_build_drop_rq_param(काष्ठा mlx5_core_dev *mdev,
			       u16 q_counter,
			       काष्ठा mlx5e_rq_param *param);
व्योम mlx5e_build_sq_param_common(काष्ठा mlx5_core_dev *mdev,
				 काष्ठा mlx5e_sq_param *param);
व्योम mlx5e_build_sq_param(काष्ठा mlx5_core_dev *mdev,
			  काष्ठा mlx5e_params *params,
			  काष्ठा mlx5e_sq_param *param);
व्योम mlx5e_build_tx_cq_param(काष्ठा mlx5_core_dev *mdev,
			     काष्ठा mlx5e_params *params,
			     काष्ठा mlx5e_cq_param *param);
व्योम mlx5e_build_xdpsq_param(काष्ठा mlx5_core_dev *mdev,
			     काष्ठा mlx5e_params *params,
			     काष्ठा mlx5e_sq_param *param);
पूर्णांक mlx5e_build_channel_param(काष्ठा mlx5_core_dev *mdev,
			      काष्ठा mlx5e_params *params,
			      u16 q_counter,
			      काष्ठा mlx5e_channel_param *cparam);

u16 mlx5e_calc_sq_stop_room(काष्ठा mlx5_core_dev *mdev, काष्ठा mlx5e_params *params);
पूर्णांक mlx5e_validate_params(काष्ठा mlx5_core_dev *mdev, काष्ठा mlx5e_params *params);

#पूर्ण_अगर /* __MLX5_EN_PARAMS_H__ */
