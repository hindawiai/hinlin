<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB */
/* Copyright (c) 2020 Mellanox Technologies. */

#अगर_अघोषित __MLX5_EN_REP_NEIGH__
#घोषणा __MLX5_EN_REP_NEIGH__

#समावेश "en.h"
#समावेश "en_rep.h"

#अगर IS_ENABLED(CONFIG_MLX5_CLS_ACT)

पूर्णांक mlx5e_rep_neigh_init(काष्ठा mlx5e_rep_priv *rpriv);
व्योम mlx5e_rep_neigh_cleanup(काष्ठा mlx5e_rep_priv *rpriv);

काष्ठा mlx5e_neigh_hash_entry *
mlx5e_rep_neigh_entry_lookup(काष्ठा mlx5e_priv *priv,
			     काष्ठा mlx5e_neigh *m_neigh);
पूर्णांक mlx5e_rep_neigh_entry_create(काष्ठा mlx5e_priv *priv,
				 काष्ठा mlx5e_neigh *m_neigh,
				 काष्ठा net_device *neigh_dev,
				 काष्ठा mlx5e_neigh_hash_entry **nhe);
व्योम mlx5e_rep_neigh_entry_release(काष्ठा mlx5e_neigh_hash_entry *nhe);

व्योम mlx5e_rep_queue_neigh_stats_work(काष्ठा mlx5e_priv *priv);

#अन्यथा /* CONFIG_MLX5_CLS_ACT */

अटल अंतरभूत पूर्णांक
mlx5e_rep_neigh_init(काष्ठा mlx5e_rep_priv *rpriv) अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम
mlx5e_rep_neigh_cleanup(काष्ठा mlx5e_rep_priv *rpriv) अणुपूर्ण

#पूर्ण_अगर /* CONFIG_MLX5_CLS_ACT */

#पूर्ण_अगर /* __MLX5_EN_REP_NEIGH__ */
