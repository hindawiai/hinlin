<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB
 * Copyright (c) 2021 Mellanox Technologies Ltd.
 */

#अगर_अघोषित _MLX5_MPFS_
#घोषणा _MLX5_MPFS_

काष्ठा mlx5_core_dev;

#अगर_घोषित CONFIG_MLX5_MPFS
पूर्णांक  mlx5_mpfs_add_mac(काष्ठा mlx5_core_dev *dev, u8 *mac);
पूर्णांक  mlx5_mpfs_del_mac(काष्ठा mlx5_core_dev *dev, u8 *mac);
#अन्यथा /* #अगर_अघोषित CONFIG_MLX5_MPFS */
अटल अंतरभूत पूर्णांक  mlx5_mpfs_add_mac(काष्ठा mlx5_core_dev *dev, u8 *mac) अणु वापस 0; पूर्ण
अटल अंतरभूत पूर्णांक  mlx5_mpfs_del_mac(काष्ठा mlx5_core_dev *dev, u8 *mac) अणु वापस 0; पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर
