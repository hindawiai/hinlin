<शैली गुरु>
/*
 * Copyright (c) 2017 Mellanox Technologies. All rights reserved.
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

#अगर_अघोषित __MLX5E_IPSEC_RXTX_H__
#घोषणा __MLX5E_IPSEC_RXTX_H__

#समावेश <linux/skbuff.h>
#समावेश <net/xfrm.h>
#समावेश "en.h"
#समावेश "en/txrx.h"

/* Bit31: IPsec marker, Bit30-24: IPsec syndrome, Bit23-0: IPsec obj id */
#घोषणा MLX5_IPSEC_METADATA_MARKER(metadata)  (((metadata) >> 31) & 0x1)
#घोषणा MLX5_IPSEC_METADATA_SYNDROM(metadata) (((metadata) >> 24) & GENMASK(6, 0))
#घोषणा MLX5_IPSEC_METADATA_HANDLE(metadata)  ((metadata) & GENMASK(23, 0))

काष्ठा mlx5e_accel_tx_ipsec_state अणु
	काष्ठा xfrm_offload *xo;
	काष्ठा xfrm_state *x;
	u32 tailen;
	u32 plen;
पूर्ण;

#अगर_घोषित CONFIG_MLX5_EN_IPSEC

काष्ठा sk_buff *mlx5e_ipsec_handle_rx_skb(काष्ठा net_device *netdev,
					  काष्ठा sk_buff *skb, u32 *cqe_bcnt);

व्योम mlx5e_ipsec_inverse_table_init(व्योम);
व्योम mlx5e_ipsec_set_iv_esn(काष्ठा sk_buff *skb, काष्ठा xfrm_state *x,
			    काष्ठा xfrm_offload *xo);
व्योम mlx5e_ipsec_set_iv(काष्ठा sk_buff *skb, काष्ठा xfrm_state *x,
			काष्ठा xfrm_offload *xo);
bool mlx5e_ipsec_handle_tx_skb(काष्ठा net_device *netdev,
			       काष्ठा sk_buff *skb,
			       काष्ठा mlx5e_accel_tx_ipsec_state *ipsec_st);
व्योम mlx5e_ipsec_handle_tx_wqe(काष्ठा mlx5e_tx_wqe *wqe,
			       काष्ठा mlx5e_accel_tx_ipsec_state *ipsec_st,
			       काष्ठा mlx5_wqe_अंतरभूत_seg *inlseg);
व्योम mlx5e_ipsec_offload_handle_rx_skb(काष्ठा net_device *netdev,
				       काष्ठा sk_buff *skb,
				       काष्ठा mlx5_cqe64 *cqe);
अटल अंतरभूत अचिन्हित पूर्णांक mlx5e_ipsec_tx_ids_len(काष्ठा mlx5e_accel_tx_ipsec_state *ipsec_st)
अणु
	वापस ipsec_st->tailen;
पूर्ण

अटल अंतरभूत bool mlx5_ipsec_is_rx_flow(काष्ठा mlx5_cqe64 *cqe)
अणु
	वापस MLX5_IPSEC_METADATA_MARKER(be32_to_cpu(cqe->ft_metadata));
पूर्ण

अटल अंतरभूत bool mlx5e_ipsec_is_tx_flow(काष्ठा mlx5e_accel_tx_ipsec_state *ipsec_st)
अणु
	वापस ipsec_st->x;
पूर्ण

अटल अंतरभूत bool mlx5e_ipsec_eseg_meta(काष्ठा mlx5_wqe_eth_seg *eseg)
अणु
	वापस eseg->flow_table_metadata & cpu_to_be32(MLX5_ETH_WQE_FT_META_IPSEC);
पूर्ण

व्योम mlx5e_ipsec_tx_build_eseg(काष्ठा mlx5e_priv *priv, काष्ठा sk_buff *skb,
			       काष्ठा mlx5_wqe_eth_seg *eseg);

अटल अंतरभूत bool mlx5e_ipsec_feature_check(काष्ठा sk_buff *skb, काष्ठा net_device *netdev,
					     netdev_features_t features)
अणु
	काष्ठा sec_path *sp = skb_sec_path(skb);

	अगर (sp && sp->len) अणु
		काष्ठा xfrm_state *x = sp->xvec[0];

		अगर (x && x->xso.offload_handle)
			वापस true;
	पूर्ण
	वापस false;
पूर्ण

#अन्यथा
अटल अंतरभूत
व्योम mlx5e_ipsec_offload_handle_rx_skb(काष्ठा net_device *netdev,
				       काष्ठा sk_buff *skb,
				       काष्ठा mlx5_cqe64 *cqe)
अणुपूर्ण

अटल अंतरभूत bool mlx5e_ipsec_eseg_meta(काष्ठा mlx5_wqe_eth_seg *eseg)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत bool mlx5_ipsec_is_rx_flow(काष्ठा mlx5_cqe64 *cqe) अणु वापस false; पूर्ण
अटल अंतरभूत bool mlx5e_ipsec_feature_check(काष्ठा sk_buff *skb, काष्ठा net_device *netdev,
					     netdev_features_t features) अणु वापस false; पूर्ण
#पूर्ण_अगर /* CONFIG_MLX5_EN_IPSEC */

#पूर्ण_अगर /* __MLX5E_IPSEC_RXTX_H__ */
