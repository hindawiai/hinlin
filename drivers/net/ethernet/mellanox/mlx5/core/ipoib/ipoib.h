<शैली गुरु>
/*
 * Copyright (c) 2017, Mellanox Technologies. All rights reserved.
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
 */

#अगर_अघोषित __MLX5E_IPOB_H__
#घोषणा __MLX5E_IPOB_H__

#अगर_घोषित CONFIG_MLX5_CORE_IPOIB

#समावेश <linux/mlx5/fs.h>
#समावेश "en.h"

#घोषणा MLX5I_MAX_NUM_TC 1

बाह्य स्थिर काष्ठा ethtool_ops mlx5i_ethtool_ops;
बाह्य स्थिर काष्ठा ethtool_ops mlx5i_pkey_ethtool_ops;
बाह्य स्थिर काष्ठा mlx5e_rx_handlers mlx5i_rx_handlers;

#घोषणा MLX5_IB_GRH_BYTES       40
#घोषणा MLX5_IPOIB_ENCAP_LEN    4
#घोषणा MLX5_IPOIB_PSEUDO_LEN   20
#घोषणा MLX5_IPOIB_HARD_LEN     (MLX5_IPOIB_PSEUDO_LEN + MLX5_IPOIB_ENCAP_LEN)

/* ipoib rdma netdev's निजी data काष्ठाure */
काष्ठा mlx5i_priv अणु
	काष्ठा rdma_netdev rn; /* keep this first */
	u32 qpn;
	bool   sub_पूर्णांकerface;
	u32    qkey;
	u16    pkey_index;
	काष्ठा mlx5i_pkey_qpn_ht *qpn_htbl;
	अक्षर  *mlx5e_priv[];
पूर्ण;

पूर्णांक mlx5i_create_tis(काष्ठा mlx5_core_dev *mdev, u32 underlay_qpn, u32 *tisn);

/* Underlay QP create/destroy functions */
पूर्णांक mlx5i_create_underlay_qp(काष्ठा mlx5e_priv *priv);
व्योम mlx5i_destroy_underlay_qp(काष्ठा mlx5_core_dev *mdev, u32 qpn);

/* Underlay QP state modअगरication init/uninit functions */
पूर्णांक mlx5i_init_underlay_qp(काष्ठा mlx5e_priv *priv);
व्योम mlx5i_uninit_underlay_qp(काष्ठा mlx5e_priv *priv);

/* Allocate/Free underlay QPN to net-device hash table */
पूर्णांक mlx5i_pkey_qpn_ht_init(काष्ठा net_device *netdev);
व्योम mlx5i_pkey_qpn_ht_cleanup(काष्ठा net_device *netdev);

/* Add/Remove an underlay QPN to net-device mapping to/from the hash table */
पूर्णांक mlx5i_pkey_add_qpn(काष्ठा net_device *netdev, u32 qpn);
पूर्णांक mlx5i_pkey_del_qpn(काष्ठा net_device *netdev, u32 qpn);

/* Get the net-device corresponding to the given underlay QPN */
काष्ठा net_device *mlx5i_pkey_get_netdev(काष्ठा net_device *netdev, u32 qpn);

/* Shared nकरो functions */
पूर्णांक mlx5i_dev_init(काष्ठा net_device *dev);
व्योम mlx5i_dev_cleanup(काष्ठा net_device *dev);
पूर्णांक mlx5i_ioctl(काष्ठा net_device *dev, काष्ठा अगरreq *अगरr, पूर्णांक cmd);

/* Parent profile functions */
पूर्णांक mlx5i_init(काष्ठा mlx5_core_dev *mdev, काष्ठा net_device *netdev);
व्योम mlx5i_cleanup(काष्ठा mlx5e_priv *priv);

पूर्णांक mlx5i_update_nic_rx(काष्ठा mlx5e_priv *priv);

/* Get child पूर्णांकerface nic profile */
स्थिर काष्ठा mlx5e_profile *mlx5i_pkey_get_profile(व्योम);

/* Extract mlx5e_priv from IPoIB netdev */
#घोषणा mlx5i_epriv(netdev) ((व्योम *)(((काष्ठा mlx5i_priv *)netdev_priv(netdev))->mlx5e_priv))

काष्ठा mlx5_wqe_eth_pad अणु
	u8 rsvd0[16];
पूर्ण;

काष्ठा mlx5i_tx_wqe अणु
	काष्ठा mlx5_wqe_ctrl_seg     ctrl;
	काष्ठा mlx5_wqe_datagram_seg datagram;
	काष्ठा mlx5_wqe_eth_pad      pad;
	काष्ठा mlx5_wqe_eth_seg      eth;
	काष्ठा mlx5_wqe_data_seg     data[];
पूर्ण;

#घोषणा MLX5I_SQ_FETCH_WQE(sq, pi) \
	((काष्ठा mlx5i_tx_wqe *)mlx5e_fetch_wqe(&(sq)->wq, pi, माप(काष्ठा mlx5i_tx_wqe)))

व्योम mlx5i_sq_xmit(काष्ठा mlx5e_txqsq *sq, काष्ठा sk_buff *skb,
		   काष्ठा mlx5_av *av, u32 dqpn, u32 dqkey, bool xmit_more);
व्योम mlx5i_get_stats(काष्ठा net_device *dev, काष्ठा rtnl_link_stats64 *stats);

#पूर्ण_अगर /* CONFIG_MLX5_CORE_IPOIB */
#पूर्ण_अगर /* __MLX5E_IPOB_H__ */
