<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB */
/* Copyright (c) 2021 Mellanox Technologies. */

#अगर_अघोषित __MLX5_EN_TC_TUN_ENCAP_H__
#घोषणा __MLX5_EN_TC_TUN_ENCAP_H__

#समावेश "tc_priv.h"

व्योम mlx5e_detach_encap(काष्ठा mlx5e_priv *priv,
			काष्ठा mlx5e_tc_flow *flow, पूर्णांक out_index);

पूर्णांक mlx5e_attach_encap(काष्ठा mlx5e_priv *priv,
		       काष्ठा mlx5e_tc_flow *flow,
		       काष्ठा net_device *mirred_dev,
		       पूर्णांक out_index,
		       काष्ठा netlink_ext_ack *extack,
		       काष्ठा net_device **encap_dev,
		       bool *encap_valid);
पूर्णांक mlx5e_attach_decap(काष्ठा mlx5e_priv *priv,
		       काष्ठा mlx5e_tc_flow *flow,
		       काष्ठा netlink_ext_ack *extack);
व्योम mlx5e_detach_decap(काष्ठा mlx5e_priv *priv,
			काष्ठा mlx5e_tc_flow *flow);

पूर्णांक mlx5e_attach_decap_route(काष्ठा mlx5e_priv *priv,
			     काष्ठा mlx5e_tc_flow *flow);
व्योम mlx5e_detach_decap_route(काष्ठा mlx5e_priv *priv,
			      काष्ठा mlx5e_tc_flow *flow);

काष्ठा ip_tunnel_info *mlx5e_dup_tun_info(स्थिर काष्ठा ip_tunnel_info *tun_info);

पूर्णांक mlx5e_tc_set_attr_rx_tun(काष्ठा mlx5e_tc_flow *flow,
			     काष्ठा mlx5_flow_spec *spec);

काष्ठा mlx5e_tc_tun_encap *mlx5e_tc_tun_init(काष्ठा mlx5e_priv *priv);
व्योम mlx5e_tc_tun_cleanup(काष्ठा mlx5e_tc_tun_encap *encap);

#पूर्ण_अगर /* __MLX5_EN_TC_TUN_ENCAP_H__ */
