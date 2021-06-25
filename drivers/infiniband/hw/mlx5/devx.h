<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB */
/*
 * Copyright (c) 2019-2020, Mellanox Technologies inc. All rights reserved.
 */

#अगर_अघोषित _MLX5_IB_DEVX_H
#घोषणा _MLX5_IB_DEVX_H

#समावेश "mlx5_ib.h"

#घोषणा MLX5_MAX_DESTROY_INBOX_SIZE_DW MLX5_ST_SZ_DW(delete_fte_in)
काष्ठा devx_obj अणु
	काष्ठा mlx5_ib_dev	*ib_dev;
	u64			obj_id;
	u32			dinlen; /* destroy inbox length */
	u32			dinbox[MLX5_MAX_DESTROY_INBOX_SIZE_DW];
	u32			flags;
	जोड़ अणु
		काष्ठा mlx5_ib_devx_mr	devx_mr;
		काष्ठा mlx5_core_dct	core_dct;
		काष्ठा mlx5_core_cq	core_cq;
		u32			flow_counter_bulk_size;
	पूर्ण;
	काष्ठा list_head event_sub; /* holds devx_event_subscription entries */
पूर्ण;
#अगर IS_ENABLED(CONFIG_INFINIBAND_USER_ACCESS)
पूर्णांक mlx5_ib_devx_create(काष्ठा mlx5_ib_dev *dev, bool is_user);
व्योम mlx5_ib_devx_destroy(काष्ठा mlx5_ib_dev *dev, u16 uid);
पूर्णांक mlx5_ib_devx_init(काष्ठा mlx5_ib_dev *dev);
व्योम mlx5_ib_devx_cleanup(काष्ठा mlx5_ib_dev *dev);
#अन्यथा
अटल अंतरभूत पूर्णांक mlx5_ib_devx_create(काष्ठा mlx5_ib_dev *dev, bool is_user)
अणु
	वापस -EOPNOTSUPP;
पूर्ण
अटल अंतरभूत व्योम mlx5_ib_devx_destroy(काष्ठा mlx5_ib_dev *dev, u16 uid) अणुपूर्ण
अटल अंतरभूत पूर्णांक mlx5_ib_devx_init(काष्ठा mlx5_ib_dev *dev)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत व्योम mlx5_ib_devx_cleanup(काष्ठा mlx5_ib_dev *dev)
अणु
पूर्ण
#पूर्ण_अगर
#पूर्ण_अगर /* _MLX5_IB_DEVX_H */
