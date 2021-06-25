<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB */
/*
 * Copyright (c) 2013-2020, Mellanox Technologies inc. All rights reserved.
 */

#अगर_अघोषित _MLX5_IB_COUNTERS_H
#घोषणा _MLX5_IB_COUNTERS_H

#समावेश "mlx5_ib.h"

पूर्णांक mlx5_ib_counters_init(काष्ठा mlx5_ib_dev *dev);
व्योम mlx5_ib_counters_cleanup(काष्ठा mlx5_ib_dev *dev);
व्योम mlx5_ib_counters_clear_description(काष्ठा ib_counters *counters);
पूर्णांक mlx5_ib_flow_counters_set_data(काष्ठा ib_counters *ibcounters,
				   काष्ठा mlx5_ib_create_flow *ucmd);
u16 mlx5_ib_get_counters_id(काष्ठा mlx5_ib_dev *dev, u32 port_num);
#पूर्ण_अगर /* _MLX5_IB_COUNTERS_H */
