<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB
/* Copyright (c) 2019 Mellanox Technologies */

#समावेश <linux/mlx5/driver.h>
#समावेश "mlx5_core.h"
#समावेश "lib/pci_vsc.h"
#समावेश "lib/mlx5.h"

#घोषणा BAD_ACCESS			0xBADACCE5
#घोषणा MLX5_PROTECTED_CR_SCAN_CRSPACE	0x7

अटल bool mlx5_crdump_enabled(काष्ठा mlx5_core_dev *dev)
अणु
	वापस !!dev->priv.health.crdump_size;
पूर्ण

अटल पूर्णांक mlx5_crdump_fill(काष्ठा mlx5_core_dev *dev, u32 *cr_data)
अणु
	u32 crdump_size = dev->priv.health.crdump_size;
	पूर्णांक i, ret;

	क्रम (i = 0; i < (crdump_size / 4); i++)
		cr_data[i] = BAD_ACCESS;

	ret = mlx5_vsc_gw_पढ़ो_block_fast(dev, cr_data, crdump_size);
	अगर (ret <= 0) अणु
		अगर (ret == 0)
			वापस -EIO;
		वापस ret;
	पूर्ण

	अगर (crdump_size != ret) अणु
		mlx5_core_warn(dev, "failed to read full dump, read %d out of %u\n",
			       ret, crdump_size);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक mlx5_crdump_collect(काष्ठा mlx5_core_dev *dev, u32 *cr_data)
अणु
	पूर्णांक ret;

	अगर (!mlx5_crdump_enabled(dev))
		वापस -ENODEV;

	ret = mlx5_vsc_gw_lock(dev);
	अगर (ret) अणु
		mlx5_core_warn(dev, "crdump: failed to lock vsc gw err %d\n",
			       ret);
		वापस ret;
	पूर्ण
	/* Verअगरy no other PF is running cr-dump or sw reset */
	ret = mlx5_vsc_sem_set_space(dev, MLX5_SEMAPHORE_SW_RESET,
				     MLX5_VSC_LOCK);
	अगर (ret) अणु
		mlx5_core_warn(dev, "Failed to lock SW reset semaphore\n");
		जाओ unlock_gw;
	पूर्ण

	ret = mlx5_vsc_gw_set_space(dev, MLX5_VSC_SPACE_SCAN_CRSPACE, शून्य);
	अगर (ret)
		जाओ unlock_sem;

	ret = mlx5_crdump_fill(dev, cr_data);

unlock_sem:
	mlx5_vsc_sem_set_space(dev, MLX5_SEMAPHORE_SW_RESET, MLX5_VSC_UNLOCK);
unlock_gw:
	mlx5_vsc_gw_unlock(dev);
	वापस ret;
पूर्ण

पूर्णांक mlx5_crdump_enable(काष्ठा mlx5_core_dev *dev)
अणु
	काष्ठा mlx5_priv *priv = &dev->priv;
	u32 space_size;
	पूर्णांक ret;

	अगर (!mlx5_core_is_pf(dev) || !mlx5_vsc_accessible(dev) ||
	    mlx5_crdump_enabled(dev))
		वापस 0;

	ret = mlx5_vsc_gw_lock(dev);
	अगर (ret)
		वापस ret;

	/* Check अगर space is supported and get space size */
	ret = mlx5_vsc_gw_set_space(dev, MLX5_VSC_SPACE_SCAN_CRSPACE,
				    &space_size);
	अगर (ret) अणु
		/* Unlock and mask error since space is not supported */
		mlx5_vsc_gw_unlock(dev);
		वापस 0;
	पूर्ण

	अगर (!space_size) अणु
		mlx5_core_warn(dev, "Invalid Crspace size, zero\n");
		mlx5_vsc_gw_unlock(dev);
		वापस -EINVAL;
	पूर्ण

	ret = mlx5_vsc_gw_unlock(dev);
	अगर (ret)
		वापस ret;

	priv->health.crdump_size = space_size;
	वापस 0;
पूर्ण

व्योम mlx5_crdump_disable(काष्ठा mlx5_core_dev *dev)
अणु
	dev->priv.health.crdump_size = 0;
पूर्ण
