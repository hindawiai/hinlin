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

#अगर_अघोषित __MLX5E_EN_ACCEL_H__
#घोषणा __MLX5E_EN_ACCEL_H__

#समावेश <linux/skbuff.h>
#समावेश <linux/netdevice.h>
#समावेश "en_accel/ipsec_rxtx.h"
#समावेश "en_accel/tls.h"
#समावेश "en_accel/tls_rxtx.h"
#समावेश "en.h"
#समावेश "en/txrx.h"

#अगर IS_ENABLED(CONFIG_GENEVE)
#समावेश <net/geneve.h>

अटल अंतरभूत bool mlx5_geneve_tx_allowed(काष्ठा mlx5_core_dev *mdev)
अणु
	वापस mlx5_tx_swp_supported(mdev);
पूर्ण

अटल अंतरभूत व्योम
mlx5e_tx_tunnel_accel(काष्ठा sk_buff *skb, काष्ठा mlx5_wqe_eth_seg *eseg, u16 ihs)
अणु
	काष्ठा mlx5e_swp_spec swp_spec = अणुपूर्ण;
	अचिन्हित पूर्णांक offset = 0;
	__be16 l3_proto;
	u8 l4_proto;

	l3_proto = vlan_get_protocol(skb);
	चयन (l3_proto) अणु
	हाल htons(ETH_P_IP):
		l4_proto = ip_hdr(skb)->protocol;
		अवरोध;
	हाल htons(ETH_P_IPV6):
		l4_proto = ipv6_find_hdr(skb, &offset, -1, शून्य, शून्य);
		अवरोध;
	शेष:
		वापस;
	पूर्ण

	अगर (l4_proto != IPPROTO_UDP ||
	    udp_hdr(skb)->dest != cpu_to_be16(GENEVE_UDP_PORT))
		वापस;
	swp_spec.l3_proto = l3_proto;
	swp_spec.l4_proto = l4_proto;
	swp_spec.is_tun = true;
	अगर (inner_ip_hdr(skb)->version == 6) अणु
		swp_spec.tun_l3_proto = htons(ETH_P_IPV6);
		swp_spec.tun_l4_proto = inner_ipv6_hdr(skb)->nexthdr;
	पूर्ण अन्यथा अणु
		swp_spec.tun_l3_proto = htons(ETH_P_IP);
		swp_spec.tun_l4_proto = inner_ip_hdr(skb)->protocol;
	पूर्ण

	mlx5e_set_eseg_swp(skb, eseg, &swp_spec);
	अगर (skb_vlan_tag_present(skb) && ihs)
		mlx5e_eseg_swp_offsets_add_vlan(eseg);
पूर्ण

#अन्यथा
अटल अंतरभूत bool mlx5_geneve_tx_allowed(काष्ठा mlx5_core_dev *mdev)
अणु
	वापस false;
पूर्ण

#पूर्ण_अगर /* CONFIG_GENEVE */

अटल अंतरभूत व्योम
mlx5e_udp_gso_handle_tx_skb(काष्ठा sk_buff *skb)
अणु
	पूर्णांक payload_len = skb_shinfo(skb)->gso_size + माप(काष्ठा udphdr);

	udp_hdr(skb)->len = htons(payload_len);
पूर्ण

काष्ठा mlx5e_accel_tx_state अणु
#अगर_घोषित CONFIG_MLX5_EN_TLS
	काष्ठा mlx5e_accel_tx_tls_state tls;
#पूर्ण_अगर
#अगर_घोषित CONFIG_MLX5_EN_IPSEC
	काष्ठा mlx5e_accel_tx_ipsec_state ipsec;
#पूर्ण_अगर
पूर्ण;

अटल अंतरभूत bool mlx5e_accel_tx_begin(काष्ठा net_device *dev,
					काष्ठा mlx5e_txqsq *sq,
					काष्ठा sk_buff *skb,
					काष्ठा mlx5e_accel_tx_state *state)
अणु
	अगर (skb_is_gso(skb) && skb_shinfo(skb)->gso_type & SKB_GSO_UDP_L4)
		mlx5e_udp_gso_handle_tx_skb(skb);

#अगर_घोषित CONFIG_MLX5_EN_TLS
	/* May send SKBs and WQEs. */
	अगर (mlx5e_tls_skb_offloaded(skb))
		अगर (unlikely(!mlx5e_tls_handle_tx_skb(dev, sq, skb, &state->tls)))
			वापस false;
#पूर्ण_अगर

#अगर_घोषित CONFIG_MLX5_EN_IPSEC
	अगर (test_bit(MLX5E_SQ_STATE_IPSEC, &sq->state) && xfrm_offload(skb)) अणु
		अगर (unlikely(!mlx5e_ipsec_handle_tx_skb(dev, skb, &state->ipsec)))
			वापस false;
	पूर्ण
#पूर्ण_अगर

	वापस true;
पूर्ण

अटल अंतरभूत bool mlx5e_accel_tx_is_ipsec_flow(काष्ठा mlx5e_accel_tx_state *state)
अणु
#अगर_घोषित CONFIG_MLX5_EN_IPSEC
	वापस mlx5e_ipsec_is_tx_flow(&state->ipsec);
#अन्यथा
	वापस false;
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक mlx5e_accel_tx_ids_len(काष्ठा mlx5e_txqsq *sq,
						  काष्ठा mlx5e_accel_tx_state *state)
अणु
#अगर_घोषित CONFIG_MLX5_EN_IPSEC
	अगर (test_bit(MLX5E_SQ_STATE_IPSEC, &sq->state))
		वापस mlx5e_ipsec_tx_ids_len(&state->ipsec);
#पूर्ण_अगर

	वापस 0;
पूर्ण

/* Part of the eseg touched by TX offloads */
#घोषणा MLX5E_ACCEL_ESEG_LEN दुरत्व(काष्ठा mlx5_wqe_eth_seg, mss)

अटल अंतरभूत bool mlx5e_accel_tx_eseg(काष्ठा mlx5e_priv *priv,
				       काष्ठा sk_buff *skb,
				       काष्ठा mlx5_wqe_eth_seg *eseg, u16 ihs)
अणु
#अगर_घोषित CONFIG_MLX5_EN_IPSEC
	अगर (xfrm_offload(skb))
		mlx5e_ipsec_tx_build_eseg(priv, skb, eseg);
#पूर्ण_अगर

#अगर IS_ENABLED(CONFIG_GENEVE)
	अगर (skb->encapsulation && skb->ip_summed == CHECKSUM_PARTIAL)
		mlx5e_tx_tunnel_accel(skb, eseg, ihs);
#पूर्ण_अगर

	वापस true;
पूर्ण

अटल अंतरभूत व्योम mlx5e_accel_tx_finish(काष्ठा mlx5e_txqsq *sq,
					 काष्ठा mlx5e_tx_wqe *wqe,
					 काष्ठा mlx5e_accel_tx_state *state,
					 काष्ठा mlx5_wqe_अंतरभूत_seg *inlseg)
अणु
#अगर_घोषित CONFIG_MLX5_EN_TLS
	mlx5e_tls_handle_tx_wqe(&wqe->ctrl, &state->tls);
#पूर्ण_अगर

#अगर_घोषित CONFIG_MLX5_EN_IPSEC
	अगर (test_bit(MLX5E_SQ_STATE_IPSEC, &sq->state) &&
	    state->ipsec.xo && state->ipsec.tailen)
		mlx5e_ipsec_handle_tx_wqe(wqe, &state->ipsec, inlseg);
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत पूर्णांक mlx5e_accel_init_rx(काष्ठा mlx5e_priv *priv)
अणु
	वापस mlx5e_ktls_init_rx(priv);
पूर्ण

अटल अंतरभूत व्योम mlx5e_accel_cleanup_rx(काष्ठा mlx5e_priv *priv)
अणु
	mlx5e_ktls_cleanup_rx(priv);
पूर्ण
#पूर्ण_अगर /* __MLX5E_EN_ACCEL_H__ */
