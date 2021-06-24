<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB */
/* Copyright (c) 2019 Mellanox Technologies. */

#अगर_अघोषित __MLX5_PORT_TUN_H__
#घोषणा __MLX5_PORT_TUN_H__

#समावेश <linux/mlx5/driver.h>

काष्ठा mlx5_tun_entropy अणु
	काष्ठा mlx5_core_dev *mdev;
	u32 num_enabling_entries;
	u32 num_disabling_entries;
	u8  enabled;
	काष्ठा mutex lock;	/* lock the entropy fields */
पूर्ण;

व्योम mlx5_init_port_tun_entropy(काष्ठा mlx5_tun_entropy *tun_entropy,
				काष्ठा mlx5_core_dev *mdev);
पूर्णांक mlx5_tun_entropy_refcount_inc(काष्ठा mlx5_tun_entropy *tun_entropy,
				  पूर्णांक reक्रमmat_type);
व्योम mlx5_tun_entropy_refcount_dec(काष्ठा mlx5_tun_entropy *tun_entropy,
				   पूर्णांक reक्रमmat_type);

#पूर्ण_अगर /* __MLX5_PORT_TUN_H__ */
