<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB */
/* Copyright (c) 2020, Mellanox Technologies inc. All rights reserved. */

#अगर_अघोषित __MLX5E_EN_QOS_H
#घोषणा __MLX5E_EN_QOS_H

#समावेश <linux/mlx5/driver.h>

#घोषणा MLX5E_QOS_MAX_LEAF_NODES 256

काष्ठा mlx5e_priv;
काष्ठा mlx5e_channels;
काष्ठा mlx5e_channel;

पूर्णांक mlx5e_qos_max_leaf_nodes(काष्ठा mlx5_core_dev *mdev);
पूर्णांक mlx5e_qos_cur_leaf_nodes(काष्ठा mlx5e_priv *priv);

/* TX datapath API */
पूर्णांक mlx5e_get_txq_by_classid(काष्ठा mlx5e_priv *priv, u16 classid);
काष्ठा mlx5e_txqsq *mlx5e_get_sq(काष्ठा mlx5e_priv *priv, पूर्णांक qid);

/* SQ lअगरecycle */
पूर्णांक mlx5e_qos_खोलो_queues(काष्ठा mlx5e_priv *priv, काष्ठा mlx5e_channels *chs);
व्योम mlx5e_qos_activate_queues(काष्ठा mlx5e_priv *priv);
व्योम mlx5e_qos_deactivate_queues(काष्ठा mlx5e_channel *c);
व्योम mlx5e_qos_बंद_queues(काष्ठा mlx5e_channel *c);

/* HTB API */
पूर्णांक mlx5e_htb_root_add(काष्ठा mlx5e_priv *priv, u16 htb_maj_id, u16 htb_defcls,
		       काष्ठा netlink_ext_ack *extack);
पूर्णांक mlx5e_htb_root_del(काष्ठा mlx5e_priv *priv);
पूर्णांक mlx5e_htb_leaf_alloc_queue(काष्ठा mlx5e_priv *priv, u16 classid,
			       u32 parent_classid, u64 rate, u64 उच्चमान,
			       काष्ठा netlink_ext_ack *extack);
पूर्णांक mlx5e_htb_leaf_to_inner(काष्ठा mlx5e_priv *priv, u16 classid, u16 child_classid,
			    u64 rate, u64 उच्चमान, काष्ठा netlink_ext_ack *extack);
पूर्णांक mlx5e_htb_leaf_del(काष्ठा mlx5e_priv *priv, u16 classid, u16 *old_qid,
		       u16 *new_qid, काष्ठा netlink_ext_ack *extack);
पूर्णांक mlx5e_htb_leaf_del_last(काष्ठा mlx5e_priv *priv, u16 classid, bool क्रमce,
			    काष्ठा netlink_ext_ack *extack);
पूर्णांक mlx5e_htb_node_modअगरy(काष्ठा mlx5e_priv *priv, u16 classid, u64 rate, u64 उच्चमान,
			  काष्ठा netlink_ext_ack *extack);

#पूर्ण_अगर
