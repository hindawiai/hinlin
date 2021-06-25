<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB */
/* Copyright (c) 2020 Mellanox Technologies */

#अगर_अघोषित __MLX5E_EN_MOD_HDR_H__
#घोषणा __MLX5E_EN_MOD_HDR_H__

#समावेश <linux/hashtable.h>
#समावेश <linux/mlx5/fs.h>

काष्ठा mlx5e_mod_hdr_handle;

काष्ठा mlx5e_tc_mod_hdr_acts अणु
	पूर्णांक num_actions;
	पूर्णांक max_actions;
	व्योम *actions;
पूर्ण;

काष्ठा mlx5e_mod_hdr_handle *
mlx5e_mod_hdr_attach(काष्ठा mlx5_core_dev *mdev,
		     काष्ठा mod_hdr_tbl *tbl,
		     क्रमागत mlx5_flow_namespace_type namespace,
		     काष्ठा mlx5e_tc_mod_hdr_acts *mod_hdr_acts);
व्योम mlx5e_mod_hdr_detach(काष्ठा mlx5_core_dev *mdev,
			  काष्ठा mod_hdr_tbl *tbl,
			  काष्ठा mlx5e_mod_hdr_handle *mh);
काष्ठा mlx5_modअगरy_hdr *mlx5e_mod_hdr_get(काष्ठा mlx5e_mod_hdr_handle *mh);

व्योम mlx5e_mod_hdr_tbl_init(काष्ठा mod_hdr_tbl *tbl);
व्योम mlx5e_mod_hdr_tbl_destroy(काष्ठा mod_hdr_tbl *tbl);

#पूर्ण_अगर /* __MLX5E_EN_MOD_HDR_H__ */
