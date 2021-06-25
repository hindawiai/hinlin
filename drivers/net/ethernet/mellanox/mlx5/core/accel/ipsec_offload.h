<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB */
/* Copyright (c) 2020, Mellanox Technologies inc. All rights reserved. */

#अगर_अघोषित __MLX5_IPSEC_OFFLOAD_H__
#घोषणा __MLX5_IPSEC_OFFLOAD_H__

#समावेश <linux/mlx5/driver.h>
#समावेश "accel/ipsec.h"

#अगर_घोषित CONFIG_MLX5_IPSEC

स्थिर काष्ठा mlx5_accel_ipsec_ops *mlx5_ipsec_offload_ops(काष्ठा mlx5_core_dev *mdev);
अटल अंतरभूत bool mlx5_is_ipsec_device(काष्ठा mlx5_core_dev *mdev)
अणु
	अगर (!MLX5_CAP_GEN(mdev, ipsec_offload))
		वापस false;

	अगर (!MLX5_CAP_GEN(mdev, log_max_dek))
		वापस false;

	अगर (!(MLX5_CAP_GEN_64(mdev, general_obj_types) &
	    MLX5_HCA_CAP_GENERAL_OBJECT_TYPES_IPSEC))
		वापस false;

	वापस MLX5_CAP_IPSEC(mdev, ipsec_crypto_offload) &&
		MLX5_CAP_ETH(mdev, insert_trailer);
पूर्ण

#अन्यथा
अटल अंतरभूत स्थिर काष्ठा mlx5_accel_ipsec_ops *
mlx5_ipsec_offload_ops(काष्ठा mlx5_core_dev *mdev) अणु वापस शून्य; पूर्ण
अटल अंतरभूत bool mlx5_is_ipsec_device(काष्ठा mlx5_core_dev *mdev)
अणु
	वापस false;
पूर्ण

#पूर्ण_अगर /* CONFIG_MLX5_IPSEC */
#पूर्ण_अगर /* __MLX5_IPSEC_OFFLOAD_H__ */
