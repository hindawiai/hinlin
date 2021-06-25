<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB */
/* Copyright (c) 2020 Mellanox Technologies Inc. All rights reserved. */

#अगर_अघोषित __MLX5_ESWITCH_ACL_HELPER_H__
#घोषणा __MLX5_ESWITCH_ACL_HELPER_H__

#समावेश "eswitch.h"

/* General acl helper functions */
काष्ठा mlx5_flow_table *
esw_acl_table_create(काष्ठा mlx5_eचयन *esw, काष्ठा mlx5_vport *vport, पूर्णांक ns, पूर्णांक size);

/* Egress acl helper functions */
व्योम esw_acl_egress_table_destroy(काष्ठा mlx5_vport *vport);
पूर्णांक esw_egress_acl_vlan_create(काष्ठा mlx5_eचयन *esw, काष्ठा mlx5_vport *vport,
			       काष्ठा mlx5_flow_destination *fwd_dest,
			       u16 vlan_id, u32 flow_action);
व्योम esw_acl_egress_vlan_destroy(काष्ठा mlx5_vport *vport);
पूर्णांक esw_acl_egress_vlan_grp_create(काष्ठा mlx5_eचयन *esw, काष्ठा mlx5_vport *vport);
व्योम esw_acl_egress_vlan_grp_destroy(काष्ठा mlx5_vport *vport);

/* Ingress acl helper functions */
व्योम esw_acl_ingress_table_destroy(काष्ठा mlx5_vport *vport);
व्योम esw_acl_ingress_allow_rule_destroy(काष्ठा mlx5_vport *vport);

#पूर्ण_अगर /* __MLX5_ESWITCH_ACL_HELPER_H__ */
