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

#अगर_अघोषित __MLX5E_IPSEC_H__
#घोषणा __MLX5E_IPSEC_H__

#अगर_घोषित CONFIG_MLX5_EN_IPSEC

#समावेश <linux/mlx5/device.h>
#समावेश <net/xfrm.h>
#समावेश <linux/idr.h>

#समावेश "accel/ipsec.h"

#घोषणा MLX5E_IPSEC_SADB_RX_BITS 10
#घोषणा MLX5E_IPSEC_ESN_SCOPE_MID 0x80000000L

काष्ठा mlx5e_priv;

काष्ठा mlx5e_ipsec_sw_stats अणु
	atomic64_t ipsec_rx_drop_sp_alloc;
	atomic64_t ipsec_rx_drop_sadb_miss;
	atomic64_t ipsec_rx_drop_syndrome;
	atomic64_t ipsec_tx_drop_bundle;
	atomic64_t ipsec_tx_drop_no_state;
	atomic64_t ipsec_tx_drop_not_ip;
	atomic64_t ipsec_tx_drop_trailer;
	atomic64_t ipsec_tx_drop_metadata;
पूर्ण;

काष्ठा mlx5e_ipsec_stats अणु
	u64 ipsec_dec_in_packets;
	u64 ipsec_dec_out_packets;
	u64 ipsec_dec_bypass_packets;
	u64 ipsec_enc_in_packets;
	u64 ipsec_enc_out_packets;
	u64 ipsec_enc_bypass_packets;
	u64 ipsec_dec_drop_packets;
	u64 ipsec_dec_auth_fail_packets;
	u64 ipsec_enc_drop_packets;
	u64 ipsec_add_sa_success;
	u64 ipsec_add_sa_fail;
	u64 ipsec_del_sa_success;
	u64 ipsec_del_sa_fail;
	u64 ipsec_cmd_drop;
पूर्ण;

काष्ठा mlx5e_accel_fs_esp;
काष्ठा mlx5e_ipsec_tx;

काष्ठा mlx5e_ipsec अणु
	काष्ठा mlx5e_priv *en_priv;
	DECLARE_HASHTABLE(sadb_rx, MLX5E_IPSEC_SADB_RX_BITS);
	bool no_trailer;
	spinlock_t sadb_rx_lock; /* Protects sadb_rx and halloc */
	काष्ठा ida halloc;
	काष्ठा mlx5e_ipsec_sw_stats sw_stats;
	काष्ठा mlx5e_ipsec_stats stats;
	काष्ठा workqueue_काष्ठा *wq;
	काष्ठा mlx5e_accel_fs_esp *rx_fs;
	काष्ठा mlx5e_ipsec_tx *tx_fs;
पूर्ण;

काष्ठा mlx5e_ipsec_esn_state अणु
	u32 esn;
	u8 trigger: 1;
	u8 overlap: 1;
पूर्ण;

काष्ठा mlx5e_ipsec_rule अणु
	काष्ठा mlx5_flow_handle *rule;
	काष्ठा mlx5_modअगरy_hdr *set_modअगरy_hdr;
पूर्ण;

काष्ठा mlx5e_ipsec_sa_entry अणु
	काष्ठा hlist_node hlist; /* Item in SADB_RX hashtable */
	काष्ठा mlx5e_ipsec_esn_state esn_state;
	अचिन्हित पूर्णांक handle; /* Handle in SADB_RX */
	काष्ठा xfrm_state *x;
	काष्ठा mlx5e_ipsec *ipsec;
	काष्ठा mlx5_accel_esp_xfrm *xfrm;
	व्योम *hw_context;
	व्योम (*set_iv_op)(काष्ठा sk_buff *skb, काष्ठा xfrm_state *x,
			  काष्ठा xfrm_offload *xo);
	u32 ipsec_obj_id;
	काष्ठा mlx5e_ipsec_rule ipsec_rule;
पूर्ण;

व्योम mlx5e_ipsec_build_inverse_table(व्योम);
पूर्णांक mlx5e_ipsec_init(काष्ठा mlx5e_priv *priv);
व्योम mlx5e_ipsec_cleanup(काष्ठा mlx5e_priv *priv);
व्योम mlx5e_ipsec_build_netdev(काष्ठा mlx5e_priv *priv);

काष्ठा xfrm_state *mlx5e_ipsec_sadb_rx_lookup(काष्ठा mlx5e_ipsec *dev,
					      अचिन्हित पूर्णांक handle);

#अन्यथा

अटल अंतरभूत व्योम mlx5e_ipsec_build_inverse_table(व्योम)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक mlx5e_ipsec_init(काष्ठा mlx5e_priv *priv)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम mlx5e_ipsec_cleanup(काष्ठा mlx5e_priv *priv)
अणु
पूर्ण

अटल अंतरभूत व्योम mlx5e_ipsec_build_netdev(काष्ठा mlx5e_priv *priv)
अणु
पूर्ण

#पूर्ण_अगर

#पूर्ण_अगर	/* __MLX5E_IPSEC_H__ */
