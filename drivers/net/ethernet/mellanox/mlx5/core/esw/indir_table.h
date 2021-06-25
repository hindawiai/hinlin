<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB */
/* Copyright (c) 2021 Mellanox Technologies. */

#अगर_अघोषित __MLX5_ESW_FT_H__
#घोषणा __MLX5_ESW_FT_H__

#अगर_घोषित CONFIG_MLX5_CLS_ACT

काष्ठा mlx5_esw_indir_table *
mlx5_esw_indir_table_init(व्योम);
व्योम
mlx5_esw_indir_table_destroy(काष्ठा mlx5_esw_indir_table *indir);

काष्ठा mlx5_flow_table *mlx5_esw_indir_table_get(काष्ठा mlx5_eचयन *esw,
						 काष्ठा mlx5_flow_attr *attr,
						 काष्ठा mlx5_flow_spec *spec,
						 u16 vport, bool decap);
व्योम mlx5_esw_indir_table_put(काष्ठा mlx5_eचयन *esw,
			      काष्ठा mlx5_flow_attr *attr,
			      u16 vport, bool decap);

bool
mlx5_esw_indir_table_needed(काष्ठा mlx5_eचयन *esw,
			    काष्ठा mlx5_flow_attr *attr,
			    u16 vport_num,
			    काष्ठा mlx5_core_dev *dest_mdev);

u16
mlx5_esw_indir_table_decap_vport(काष्ठा mlx5_flow_attr *attr);

#अन्यथा
/* indir API stubs */
अटल अंतरभूत काष्ठा mlx5_esw_indir_table *
mlx5_esw_indir_table_init(व्योम)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत व्योम
mlx5_esw_indir_table_destroy(काष्ठा mlx5_esw_indir_table *indir)
अणु
पूर्ण

अटल अंतरभूत काष्ठा mlx5_flow_table *
mlx5_esw_indir_table_get(काष्ठा mlx5_eचयन *esw,
			 काष्ठा mlx5_flow_attr *attr,
			 काष्ठा mlx5_flow_spec *spec,
			 u16 vport, bool decap)
अणु
	वापस ERR_PTR(-EOPNOTSUPP);
पूर्ण

अटल अंतरभूत व्योम
mlx5_esw_indir_table_put(काष्ठा mlx5_eचयन *esw,
			 काष्ठा mlx5_flow_attr *attr,
			 u16 vport, bool decap)
अणु
पूर्ण

अटल अंतरभूत bool
mlx5_esw_indir_table_needed(काष्ठा mlx5_eचयन *esw,
			    काष्ठा mlx5_flow_attr *attr,
			    u16 vport_num,
			    काष्ठा mlx5_core_dev *dest_mdev)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत u16
mlx5_esw_indir_table_decap_vport(काष्ठा mlx5_flow_attr *attr)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* __MLX5_ESW_FT_H__ */
