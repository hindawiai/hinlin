<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB */
/* Copyright (c) 2021 Mellanox Technologies. */

#अगर_अघोषित __MLX5_EN_TC_SAMPLE_H__
#घोषणा __MLX5_EN_TC_SAMPLE_H__

#समावेश "en.h"
#समावेश "eswitch.h"

काष्ठा mlx5e_priv;
काष्ठा mlx5_flow_attr;
काष्ठा mlx5_esw_psample;

काष्ठा mlx5_sample_attr अणु
	u32 group_num;
	u32 rate;
	u32 trunc_size;
	u32 restore_obj_id;
	u32 sampler_id;
	काष्ठा mlx5_flow_table *sample_शेष_tbl;
	काष्ठा mlx5_sample_flow *sample_flow;
पूर्ण;

व्योम mlx5_esw_sample_skb(काष्ठा sk_buff *skb, काष्ठा mlx5_mapped_obj *mapped_obj);

काष्ठा mlx5_flow_handle *
mlx5_esw_sample_offload(काष्ठा mlx5_esw_psample *sample_priv,
			काष्ठा mlx5_flow_spec *spec,
			काष्ठा mlx5_flow_attr *attr);

व्योम
mlx5_esw_sample_unoffload(काष्ठा mlx5_esw_psample *sample_priv,
			  काष्ठा mlx5_flow_handle *rule,
			  काष्ठा mlx5_flow_attr *attr);

काष्ठा mlx5_esw_psample *
mlx5_esw_sample_init(काष्ठा mlx5e_priv *priv);

व्योम
mlx5_esw_sample_cleanup(काष्ठा mlx5_esw_psample *esw_psample);

#पूर्ण_अगर /* __MLX5_EN_TC_SAMPLE_H__ */
