<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB */
/* Copyright (c) 2020 Mellanox Technologies Ltd */

#अगर_अघोषित __MLX5_SF_DEV_H__
#घोषणा __MLX5_SF_DEV_H__

#अगर_घोषित CONFIG_MLX5_SF

#समावेश <linux/auxiliary_bus.h>

#घोषणा MLX5_SF_DEV_ID_NAME "sf"

काष्ठा mlx5_sf_dev अणु
	काष्ठा auxiliary_device adev;
	काष्ठा mlx5_core_dev *parent_mdev;
	काष्ठा mlx5_core_dev *mdev;
	phys_addr_t bar_base_addr;
	u32 sfnum;
पूर्ण;

व्योम mlx5_sf_dev_table_create(काष्ठा mlx5_core_dev *dev);
व्योम mlx5_sf_dev_table_destroy(काष्ठा mlx5_core_dev *dev);

पूर्णांक mlx5_sf_driver_रेजिस्टर(व्योम);
व्योम mlx5_sf_driver_unरेजिस्टर(व्योम);

bool mlx5_sf_dev_allocated(स्थिर काष्ठा mlx5_core_dev *dev);

#अन्यथा

अटल अंतरभूत व्योम mlx5_sf_dev_table_create(काष्ठा mlx5_core_dev *dev)
अणु
पूर्ण

अटल अंतरभूत व्योम mlx5_sf_dev_table_destroy(काष्ठा mlx5_core_dev *dev)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक mlx5_sf_driver_रेजिस्टर(व्योम)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम mlx5_sf_driver_unरेजिस्टर(व्योम)
अणु
पूर्ण

अटल अंतरभूत bool mlx5_sf_dev_allocated(स्थिर काष्ठा mlx5_core_dev *dev)
अणु
	वापस false;
पूर्ण

#पूर्ण_अगर

#पूर्ण_अगर
