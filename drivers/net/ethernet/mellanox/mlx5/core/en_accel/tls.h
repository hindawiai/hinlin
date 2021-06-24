<शैली गुरु>
/*
 * Copyright (c) 2018 Mellanox Technologies. All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the मुख्य directory of this source tree, or the
 * OpenIB.org BSD license below:
 *
 *     Redistribution and use in source and binary क्रमms, with or
 *     without modअगरication, are permitted provided that the following
 *     conditions are met:
 *
 *      - Redistributions of source code must retain the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer.
 *
 *      - Redistributions in binary क्रमm must reproduce the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer in the करोcumentation and/or other materials
 *        provided with the distribution.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 */
#अगर_अघोषित __MLX5E_TLS_H__
#घोषणा __MLX5E_TLS_H__

#समावेश "accel/tls.h"
#समावेश "en_accel/ktls.h"

#अगर_घोषित CONFIG_MLX5_EN_TLS
#समावेश <net/tls.h>
#समावेश "en.h"

काष्ठा mlx5e_tls_sw_stats अणु
	atomic64_t tx_tls_ctx;
	atomic64_t tx_tls_drop_metadata;
	atomic64_t tx_tls_drop_resync_alloc;
	atomic64_t tx_tls_drop_no_sync_data;
	atomic64_t tx_tls_drop_bypass_required;
	atomic64_t rx_tls_ctx;
	atomic64_t rx_tls_del;
	atomic64_t rx_tls_drop_resync_request;
	atomic64_t rx_tls_resync_request;
	atomic64_t rx_tls_resync_reply;
	atomic64_t rx_tls_auth_fail;
पूर्ण;

काष्ठा mlx5e_tls अणु
	काष्ठा mlx5e_tls_sw_stats sw_stats;
	काष्ठा workqueue_काष्ठा *rx_wq;
पूर्ण;

काष्ठा mlx5e_tls_offload_context_tx अणु
	काष्ठा tls_offload_context_tx base;
	u32 expected_seq;
	__be32 swid;
पूर्ण;

अटल अंतरभूत काष्ठा mlx5e_tls_offload_context_tx *
mlx5e_get_tls_tx_context(काष्ठा tls_context *tls_ctx)
अणु
	BUILD_BUG_ON(माप(काष्ठा mlx5e_tls_offload_context_tx) >
		     TLS_OFFLOAD_CONTEXT_SIZE_TX);
	वापस container_of(tls_offload_ctx_tx(tls_ctx),
			    काष्ठा mlx5e_tls_offload_context_tx,
			    base);
पूर्ण

काष्ठा mlx5e_tls_offload_context_rx अणु
	काष्ठा tls_offload_context_rx base;
	__be32 handle;
पूर्ण;

अटल अंतरभूत काष्ठा mlx5e_tls_offload_context_rx *
mlx5e_get_tls_rx_context(काष्ठा tls_context *tls_ctx)
अणु
	BUILD_BUG_ON(माप(काष्ठा mlx5e_tls_offload_context_rx) >
		     TLS_OFFLOAD_CONTEXT_SIZE_RX);
	वापस container_of(tls_offload_ctx_rx(tls_ctx),
			    काष्ठा mlx5e_tls_offload_context_rx,
			    base);
पूर्ण

अटल अंतरभूत bool mlx5e_is_tls_on(काष्ठा mlx5e_priv *priv)
अणु
	वापस priv->tls;
पूर्ण

व्योम mlx5e_tls_build_netdev(काष्ठा mlx5e_priv *priv);
पूर्णांक mlx5e_tls_init(काष्ठा mlx5e_priv *priv);
व्योम mlx5e_tls_cleanup(काष्ठा mlx5e_priv *priv);

पूर्णांक mlx5e_tls_get_count(काष्ठा mlx5e_priv *priv);
पूर्णांक mlx5e_tls_get_strings(काष्ठा mlx5e_priv *priv, uपूर्णांक8_t *data);
पूर्णांक mlx5e_tls_get_stats(काष्ठा mlx5e_priv *priv, u64 *data);

#अन्यथा

अटल अंतरभूत व्योम mlx5e_tls_build_netdev(काष्ठा mlx5e_priv *priv)
अणु
	अगर (mlx5_accel_is_ktls_device(priv->mdev))
		mlx5e_ktls_build_netdev(priv);
पूर्ण

अटल अंतरभूत bool mlx5e_is_tls_on(काष्ठा mlx5e_priv *priv) अणु वापस false; पूर्ण
अटल अंतरभूत पूर्णांक mlx5e_tls_init(काष्ठा mlx5e_priv *priv) अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम mlx5e_tls_cleanup(काष्ठा mlx5e_priv *priv) अणु पूर्ण
अटल अंतरभूत पूर्णांक mlx5e_tls_get_count(काष्ठा mlx5e_priv *priv) अणु वापस 0; पूर्ण
अटल अंतरभूत पूर्णांक mlx5e_tls_get_strings(काष्ठा mlx5e_priv *priv, uपूर्णांक8_t *data) अणु वापस 0; पूर्ण
अटल अंतरभूत पूर्णांक mlx5e_tls_get_stats(काष्ठा mlx5e_priv *priv, u64 *data) अणु वापस 0; पूर्ण

#पूर्ण_अगर

#पूर्ण_अगर /* __MLX5E_TLS_H__ */
