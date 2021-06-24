<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright (c) 2019 Mellanox Technologies. */

#अगर_अघोषित __MLX5E_EN_HEALTH_H
#घोषणा __MLX5E_EN_HEALTH_H

#समावेश "en.h"
#समावेश "diag/rsc_dump.h"

अटल अंतरभूत bool cqe_syndrome_needs_recover(u8 syndrome)
अणु
	वापस syndrome == MLX5_CQE_SYNDROME_LOCAL_QP_OP_ERR ||
	       syndrome == MLX5_CQE_SYNDROME_LOCAL_PROT_ERR ||
	       syndrome == MLX5_CQE_SYNDROME_WR_FLUSH_ERR;
पूर्ण

व्योम mlx5e_reporter_tx_create(काष्ठा mlx5e_priv *priv);
व्योम mlx5e_reporter_tx_destroy(काष्ठा mlx5e_priv *priv);
व्योम mlx5e_reporter_tx_err_cqe(काष्ठा mlx5e_txqsq *sq);
पूर्णांक mlx5e_reporter_tx_समयout(काष्ठा mlx5e_txqsq *sq);

पूर्णांक mlx5e_health_cq_diag_fmsg(काष्ठा mlx5e_cq *cq, काष्ठा devlink_fmsg *fmsg);
पूर्णांक mlx5e_health_cq_common_diag_fmsg(काष्ठा mlx5e_cq *cq, काष्ठा devlink_fmsg *fmsg);
पूर्णांक mlx5e_health_eq_diag_fmsg(काष्ठा mlx5_eq_comp *eq, काष्ठा devlink_fmsg *fmsg);
पूर्णांक mlx5e_health_fmsg_named_obj_nest_start(काष्ठा devlink_fmsg *fmsg, अक्षर *name);
पूर्णांक mlx5e_health_fmsg_named_obj_nest_end(काष्ठा devlink_fmsg *fmsg);

व्योम mlx5e_reporter_rx_create(काष्ठा mlx5e_priv *priv);
व्योम mlx5e_reporter_rx_destroy(काष्ठा mlx5e_priv *priv);
व्योम mlx5e_reporter_icosq_cqe_err(काष्ठा mlx5e_icosq *icosq);
व्योम mlx5e_reporter_rq_cqe_err(काष्ठा mlx5e_rq *rq);
व्योम mlx5e_reporter_rx_समयout(काष्ठा mlx5e_rq *rq);

#घोषणा MLX5E_REPORTER_PER_Q_MAX_LEN 256
#घोषणा MLX5E_REPORTER_FLUSH_TIMEOUT_MSEC 2000

काष्ठा mlx5e_err_ctx अणु
	पूर्णांक (*recover)(व्योम *ctx);
	पूर्णांक (*dump)(काष्ठा mlx5e_priv *priv, काष्ठा devlink_fmsg *fmsg, व्योम *ctx);
	व्योम *ctx;
पूर्ण;

पूर्णांक mlx5e_health_sq_to_पढ़ोy(काष्ठा mlx5_core_dev *mdev, काष्ठा net_device *dev, u32 sqn);
पूर्णांक mlx5e_health_channel_eq_recover(काष्ठा net_device *dev, काष्ठा mlx5_eq_comp *eq,
				    काष्ठा mlx5e_ch_stats *stats);
पूर्णांक mlx5e_health_recover_channels(काष्ठा mlx5e_priv *priv);
पूर्णांक mlx5e_health_report(काष्ठा mlx5e_priv *priv,
			काष्ठा devlink_health_reporter *reporter, अक्षर *err_str,
			काष्ठा mlx5e_err_ctx *err_ctx);
व्योम mlx5e_health_create_reporters(काष्ठा mlx5e_priv *priv);
व्योम mlx5e_health_destroy_reporters(काष्ठा mlx5e_priv *priv);
व्योम mlx5e_health_channels_update(काष्ठा mlx5e_priv *priv);
पूर्णांक mlx5e_health_rsc_fmsg_dump(काष्ठा mlx5e_priv *priv, काष्ठा mlx5_rsc_key *key,
			       काष्ठा devlink_fmsg *fmsg);
पूर्णांक mlx5e_health_queue_dump(काष्ठा mlx5e_priv *priv, काष्ठा devlink_fmsg *fmsg,
			    पूर्णांक queue_idx, अक्षर *lbl);
#पूर्ण_अगर
