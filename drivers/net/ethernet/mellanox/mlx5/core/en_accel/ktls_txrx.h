<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB */
/* Copyright (c) 2020, Mellanox Technologies inc. All rights reserved. */

#अगर_अघोषित __MLX5E_KTLS_TXRX_H__
#घोषणा __MLX5E_KTLS_TXRX_H__

#अगर_घोषित CONFIG_MLX5_EN_TLS

#समावेश <net/tls.h>
#समावेश "en.h"
#समावेश "en/txrx.h"

काष्ठा mlx5e_accel_tx_tls_state अणु
	u32 tls_tisn;
पूर्ण;

u16 mlx5e_ktls_get_stop_room(काष्ठा mlx5e_params *params);

bool mlx5e_ktls_handle_tx_skb(काष्ठा tls_context *tls_ctx, काष्ठा mlx5e_txqsq *sq,
			      काष्ठा sk_buff *skb, पूर्णांक datalen,
			      काष्ठा mlx5e_accel_tx_tls_state *state);
व्योम mlx5e_ktls_handle_rx_skb(काष्ठा mlx5e_rq *rq, काष्ठा sk_buff *skb,
			      काष्ठा mlx5_cqe64 *cqe, u32 *cqe_bcnt);

व्योम mlx5e_ktls_handle_ctx_completion(काष्ठा mlx5e_icosq_wqe_info *wi);
व्योम mlx5e_ktls_handle_get_psv_completion(काष्ठा mlx5e_icosq_wqe_info *wi,
					  काष्ठा mlx5e_icosq *sq);

व्योम mlx5e_ktls_tx_handle_resync_dump_comp(काष्ठा mlx5e_txqsq *sq,
					   काष्ठा mlx5e_tx_wqe_info *wi,
					   u32 *dma_fअगरo_cc);
अटल अंतरभूत bool
mlx5e_ktls_tx_try_handle_resync_dump_comp(काष्ठा mlx5e_txqsq *sq,
					  काष्ठा mlx5e_tx_wqe_info *wi,
					  u32 *dma_fअगरo_cc)
अणु
	अगर (unlikely(wi->resync_dump_frag_page)) अणु
		mlx5e_ktls_tx_handle_resync_dump_comp(sq, wi, dma_fअगरo_cc);
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

bool mlx5e_ktls_rx_handle_resync_list(काष्ठा mlx5e_channel *c, पूर्णांक budget);

अटल अंतरभूत bool
mlx5e_ktls_rx_pending_resync_list(काष्ठा mlx5e_channel *c, पूर्णांक budget)
अणु
	वापस budget && test_bit(MLX5E_SQ_STATE_PENDING_TLS_RX_RESYNC, &c->async_icosq.state);
पूर्ण
#अन्यथा
अटल अंतरभूत bool
mlx5e_ktls_tx_try_handle_resync_dump_comp(काष्ठा mlx5e_txqsq *sq,
					  काष्ठा mlx5e_tx_wqe_info *wi,
					  u32 *dma_fअगरo_cc)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत bool
mlx5e_ktls_rx_handle_resync_list(काष्ठा mlx5e_channel *c, पूर्णांक budget)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत bool
mlx5e_ktls_rx_pending_resync_list(काष्ठा mlx5e_channel *c, पूर्णांक budget)
अणु
	वापस false;
पूर्ण

#पूर्ण_अगर /* CONFIG_MLX5_EN_TLS */

#पूर्ण_अगर /* __MLX5E_TLS_TXRX_H__ */
