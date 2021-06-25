<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB */
/* Copyright (c) 2019 Mellanox Technologies. */

#अगर_अघोषित __MLX5_LAG_MP_H__
#घोषणा __MLX5_LAG_MP_H__

#समावेश "lag.h"
#समावेश "mlx5_core.h"

क्रमागत mlx5_lag_port_affinity अणु
	MLX5_LAG_NORMAL_AFFINITY,
	MLX5_LAG_P1_AFFINITY,
	MLX5_LAG_P2_AFFINITY,
पूर्ण;

काष्ठा lag_mp अणु
	काष्ठा notअगरier_block     fib_nb;
	काष्ठा fib_info           *mfi; /* used in tracking fib events */
	काष्ठा workqueue_काष्ठा   *wq;
पूर्ण;

#अगर_घोषित CONFIG_MLX5_ESWITCH

पूर्णांक mlx5_lag_mp_init(काष्ठा mlx5_lag *ldev);
व्योम mlx5_lag_mp_cleanup(काष्ठा mlx5_lag *ldev);

#अन्यथा /* CONFIG_MLX5_ESWITCH */

अटल अंतरभूत पूर्णांक mlx5_lag_mp_init(काष्ठा mlx5_lag *ldev) अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम mlx5_lag_mp_cleanup(काष्ठा mlx5_lag *ldev) अणुपूर्ण

#पूर्ण_अगर /* CONFIG_MLX5_ESWITCH */
#पूर्ण_अगर /* __MLX5_LAG_MP_H__ */
