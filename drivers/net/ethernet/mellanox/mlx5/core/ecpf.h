<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB */
/* Copyright (c) 2019 Mellanox Technologies. */

#अगर_अघोषित __MLX5_ECPF_H__
#घोषणा __MLX5_ECPF_H__

#समावेश <linux/mlx5/driver.h>
#समावेश "mlx5_core.h"

#अगर_घोषित CONFIG_MLX5_ESWITCH

क्रमागत अणु
	MLX5_ECPU_BIT_NUM = 23,
पूर्ण;

bool mlx5_पढ़ो_embedded_cpu(काष्ठा mlx5_core_dev *dev);
पूर्णांक mlx5_ec_init(काष्ठा mlx5_core_dev *dev);
व्योम mlx5_ec_cleanup(काष्ठा mlx5_core_dev *dev);

पूर्णांक mlx5_cmd_host_pf_enable_hca(काष्ठा mlx5_core_dev *dev);
पूर्णांक mlx5_cmd_host_pf_disable_hca(काष्ठा mlx5_core_dev *dev);

#अन्यथा  /* CONFIG_MLX5_ESWITCH */

अटल अंतरभूत bool
mlx5_पढ़ो_embedded_cpu(काष्ठा mlx5_core_dev *dev) अणु वापस false; पूर्ण
अटल अंतरभूत पूर्णांक mlx5_ec_init(काष्ठा mlx5_core_dev *dev) अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम mlx5_ec_cleanup(काष्ठा mlx5_core_dev *dev) अणुपूर्ण

#पूर्ण_अगर /* CONFIG_MLX5_ESWITCH */

#पूर्ण_अगर /* __MLX5_ECPF_H__ */
