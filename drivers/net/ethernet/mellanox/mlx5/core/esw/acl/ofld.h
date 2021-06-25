<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB */
/* Copyright (c) 2020 Mellanox Technologies Inc. All rights reserved. */

#अगर_अघोषित __MLX5_ESWITCH_ACL_OFLD_H__
#घोषणा __MLX5_ESWITCH_ACL_OFLD_H__

#समावेश "eswitch.h"

/* Eचयन acl egress बाह्यal APIs */
पूर्णांक esw_acl_egress_ofld_setup(काष्ठा mlx5_eचयन *esw, काष्ठा mlx5_vport *vport);
व्योम esw_acl_egress_ofld_cleanup(काष्ठा mlx5_vport *vport);
पूर्णांक mlx5_esw_acl_egress_vport_bond(काष्ठा mlx5_eचयन *esw, u16 active_vport_num,
				   u16 passive_vport_num);
पूर्णांक mlx5_esw_acl_egress_vport_unbond(काष्ठा mlx5_eचयन *esw, u16 vport_num);

अटल अंतरभूत bool mlx5_esw_acl_egress_fwd2vport_supported(काष्ठा mlx5_eचयन *esw)
अणु
	वापस esw && esw->mode == MLX5_ESWITCH_OFFLOADS &&
		mlx5_eचयन_vport_match_metadata_enabled(esw) &&
		MLX5_CAP_ESW_FLOWTABLE(esw->dev, egress_acl_क्रमward_to_vport);
पूर्ण

/* Eचयन acl ingress बाह्यal APIs */
पूर्णांक esw_acl_ingress_ofld_setup(काष्ठा mlx5_eचयन *esw, काष्ठा mlx5_vport *vport);
व्योम esw_acl_ingress_ofld_cleanup(काष्ठा mlx5_eचयन *esw, काष्ठा mlx5_vport *vport);
पूर्णांक mlx5_esw_acl_ingress_vport_bond_update(काष्ठा mlx5_eचयन *esw, u16 vport_num,
					   u32 metadata);

#पूर्ण_अगर /* __MLX5_ESWITCH_ACL_OFLD_H__ */
