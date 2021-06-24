<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB */
/* Copyright (c) 2019 Mellanox Technologies. */

#अगर_अघोषित __MLX5_LAG_H__
#घोषणा __MLX5_LAG_H__

#समावेश "mlx5_core.h"
#समावेश "lag_mp.h"

क्रमागत अणु
	MLX5_LAG_P1,
	MLX5_LAG_P2,
पूर्ण;

क्रमागत अणु
	MLX5_LAG_FLAG_ROCE   = 1 << 0,
	MLX5_LAG_FLAG_SRIOV  = 1 << 1,
	MLX5_LAG_FLAG_MULTIPATH = 1 << 2,
	MLX5_LAG_FLAG_READY = 1 << 3,
पूर्ण;

#घोषणा MLX5_LAG_MODE_FLAGS (MLX5_LAG_FLAG_ROCE | MLX5_LAG_FLAG_SRIOV |\
			     MLX5_LAG_FLAG_MULTIPATH)

काष्ठा lag_func अणु
	काष्ठा mlx5_core_dev *dev;
	काष्ठा net_device    *netdev;
पूर्ण;

/* Used क्रम collection of netdev event info. */
काष्ठा lag_tracker अणु
	क्रमागत   netdev_lag_tx_type           tx_type;
	काष्ठा netdev_lag_lower_state_info  netdev_state[MLX5_MAX_PORTS];
	अचिन्हित पूर्णांक is_bonded:1;
पूर्ण;

/* LAG data of a ConnectX card.
 * It serves both its phys functions.
 */
काष्ठा mlx5_lag अणु
	u8                        flags;
	u8                        v2p_map[MLX5_MAX_PORTS];
	काष्ठा lag_func           pf[MLX5_MAX_PORTS];
	काष्ठा lag_tracker        tracker;
	काष्ठा workqueue_काष्ठा   *wq;
	काष्ठा delayed_work       bond_work;
	काष्ठा notअगरier_block     nb;
	काष्ठा lag_mp             lag_mp;
पूर्ण;

अटल अंतरभूत काष्ठा mlx5_lag *
mlx5_lag_dev_get(काष्ठा mlx5_core_dev *dev)
अणु
	वापस dev->priv.lag;
पूर्ण

अटल अंतरभूत bool
__mlx5_lag_is_active(काष्ठा mlx5_lag *ldev)
अणु
	वापस !!(ldev->flags & MLX5_LAG_MODE_FLAGS);
पूर्ण

अटल अंतरभूत bool
mlx5_lag_is_पढ़ोy(काष्ठा mlx5_lag *ldev)
अणु
	वापस ldev->flags & MLX5_LAG_FLAG_READY;
पूर्ण

व्योम mlx5_modअगरy_lag(काष्ठा mlx5_lag *ldev,
		     काष्ठा lag_tracker *tracker);
पूर्णांक mlx5_activate_lag(काष्ठा mlx5_lag *ldev,
		      काष्ठा lag_tracker *tracker,
		      u8 flags);
पूर्णांक mlx5_lag_dev_get_netdev_idx(काष्ठा mlx5_lag *ldev,
				काष्ठा net_device *ndev);

#पूर्ण_अगर /* __MLX5_LAG_H__ */
