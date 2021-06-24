<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB */
/* Copyright (c) 2019 Mellanox Technologies. */

#अगर_अघोषित __MLX5_EN_XSK_TX_H__
#घोषणा __MLX5_EN_XSK_TX_H__

#समावेश "en.h"
#समावेश <net/xdp_sock_drv.h>

/* TX data path */

पूर्णांक mlx5e_xsk_wakeup(काष्ठा net_device *dev, u32 qid, u32 flags);

bool mlx5e_xsk_tx(काष्ठा mlx5e_xdpsq *sq, अचिन्हित पूर्णांक budget);

अटल अंतरभूत व्योम mlx5e_xsk_update_tx_wakeup(काष्ठा mlx5e_xdpsq *sq)
अणु
	अगर (!xsk_uses_need_wakeup(sq->xsk_pool))
		वापस;

	अगर (sq->pc != sq->cc)
		xsk_clear_tx_need_wakeup(sq->xsk_pool);
	अन्यथा
		xsk_set_tx_need_wakeup(sq->xsk_pool);
पूर्ण

#पूर्ण_अगर /* __MLX5_EN_XSK_TX_H__ */
