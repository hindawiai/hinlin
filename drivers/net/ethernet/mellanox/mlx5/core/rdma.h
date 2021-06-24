<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB */
/* Copyright (c) 2019 Mellanox Technologies. */

#अगर_अघोषित __MLX5_RDMA_H__
#घोषणा __MLX5_RDMA_H__

#समावेश "mlx5_core.h"

#अगर_घोषित CONFIG_MLX5_ESWITCH

व्योम mlx5_rdma_enable_roce(काष्ठा mlx5_core_dev *dev);
व्योम mlx5_rdma_disable_roce(काष्ठा mlx5_core_dev *dev);

#अन्यथा /* CONFIG_MLX5_ESWITCH */

अटल अंतरभूत व्योम mlx5_rdma_enable_roce(काष्ठा mlx5_core_dev *dev) अणुपूर्ण
अटल अंतरभूत व्योम mlx5_rdma_disable_roce(काष्ठा mlx5_core_dev *dev) अणुपूर्ण

#पूर्ण_अगर /* CONFIG_MLX5_ESWITCH */
#पूर्ण_अगर /* __MLX5_RDMA_H__ */
