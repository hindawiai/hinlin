<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB */
/* Copyright (c) 2019 Mellanox Technologies */

#अगर_अघोषित __MLX5_PCI_VSC_H__
#घोषणा __MLX5_PCI_VSC_H__

क्रमागत mlx5_vsc_state अणु
	MLX5_VSC_UNLOCK,
	MLX5_VSC_LOCK,
पूर्ण;

क्रमागत अणु
	MLX5_VSC_SPACE_SCAN_CRSPACE = 0x7,
पूर्ण;

व्योम mlx5_pci_vsc_init(काष्ठा mlx5_core_dev *dev);
पूर्णांक mlx5_vsc_gw_lock(काष्ठा mlx5_core_dev *dev);
पूर्णांक mlx5_vsc_gw_unlock(काष्ठा mlx5_core_dev *dev);
पूर्णांक mlx5_vsc_gw_set_space(काष्ठा mlx5_core_dev *dev, u16 space,
			  u32 *ret_space_size);
पूर्णांक mlx5_vsc_gw_पढ़ो_block_fast(काष्ठा mlx5_core_dev *dev, u32 *data,
				पूर्णांक length);

अटल अंतरभूत bool mlx5_vsc_accessible(काष्ठा mlx5_core_dev *dev)
अणु
	वापस !!dev->vsc_addr;
पूर्ण

पूर्णांक mlx5_vsc_sem_set_space(काष्ठा mlx5_core_dev *dev, u16 space,
			   क्रमागत mlx5_vsc_state state);

#पूर्ण_अगर /* __MLX5_PCI_VSC_H__ */
