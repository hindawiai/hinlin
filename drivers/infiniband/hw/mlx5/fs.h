<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB */
/*
 * Copyright (c) 2013-2020, Mellanox Technologies inc. All rights reserved.
 */

#अगर_अघोषित _MLX5_IB_FS_H
#घोषणा _MLX5_IB_FS_H

#समावेश "mlx5_ib.h"

#अगर IS_ENABLED(CONFIG_INFINIBAND_USER_ACCESS)
पूर्णांक mlx5_ib_fs_init(काष्ठा mlx5_ib_dev *dev);
#अन्यथा
अटल अंतरभूत पूर्णांक mlx5_ib_fs_init(काष्ठा mlx5_ib_dev *dev)
अणु
	dev->flow_db = kzalloc(माप(*dev->flow_db), GFP_KERNEL);

	अगर (!dev->flow_db)
		वापस -ENOMEM;

	mutex_init(&dev->flow_db->lock);
	वापस 0;
पूर्ण
#पूर्ण_अगर
अटल अंतरभूत व्योम mlx5_ib_fs_cleanup(काष्ठा mlx5_ib_dev *dev)
अणु
	kमुक्त(dev->flow_db);
पूर्ण
#पूर्ण_अगर /* _MLX5_IB_FS_H */
