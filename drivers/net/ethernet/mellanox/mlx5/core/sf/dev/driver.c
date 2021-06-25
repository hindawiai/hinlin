<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB
/* Copyright (c) 2020 Mellanox Technologies Ltd */

#समावेश <linux/mlx5/driver.h>
#समावेश <linux/mlx5/device.h>
#समावेश "mlx5_core.h"
#समावेश "dev.h"
#समावेश "devlink.h"

अटल पूर्णांक mlx5_sf_dev_probe(काष्ठा auxiliary_device *adev, स्थिर काष्ठा auxiliary_device_id *id)
अणु
	काष्ठा mlx5_sf_dev *sf_dev = container_of(adev, काष्ठा mlx5_sf_dev, adev);
	काष्ठा mlx5_core_dev *mdev;
	काष्ठा devlink *devlink;
	पूर्णांक err;

	devlink = mlx5_devlink_alloc();
	अगर (!devlink)
		वापस -ENOMEM;

	mdev = devlink_priv(devlink);
	mdev->device = &adev->dev;
	mdev->pdev = sf_dev->parent_mdev->pdev;
	mdev->bar_addr = sf_dev->bar_base_addr;
	mdev->iseg_base = sf_dev->bar_base_addr;
	mdev->coredev_type = MLX5_COREDEV_SF;
	mdev->priv.parent_mdev = sf_dev->parent_mdev;
	mdev->priv.adev_idx = adev->id;
	sf_dev->mdev = mdev;

	err = mlx5_mdev_init(mdev, MLX5_DEFAULT_PROF);
	अगर (err) अणु
		mlx5_core_warn(mdev, "mlx5_mdev_init on err=%d\n", err);
		जाओ mdev_err;
	पूर्ण

	mdev->iseg = ioremap(mdev->iseg_base, माप(*mdev->iseg));
	अगर (!mdev->iseg) अणु
		mlx5_core_warn(mdev, "remap error\n");
		err = -ENOMEM;
		जाओ remap_err;
	पूर्ण

	err = mlx5_init_one(mdev);
	अगर (err) अणु
		mlx5_core_warn(mdev, "mlx5_init_one err=%d\n", err);
		जाओ init_one_err;
	पूर्ण
	devlink_reload_enable(devlink);
	वापस 0;

init_one_err:
	iounmap(mdev->iseg);
remap_err:
	mlx5_mdev_uninit(mdev);
mdev_err:
	mlx5_devlink_मुक्त(devlink);
	वापस err;
पूर्ण

अटल व्योम mlx5_sf_dev_हटाओ(काष्ठा auxiliary_device *adev)
अणु
	काष्ठा mlx5_sf_dev *sf_dev = container_of(adev, काष्ठा mlx5_sf_dev, adev);
	काष्ठा devlink *devlink;

	devlink = priv_to_devlink(sf_dev->mdev);
	devlink_reload_disable(devlink);
	mlx5_uninit_one(sf_dev->mdev);
	iounmap(sf_dev->mdev->iseg);
	mlx5_mdev_uninit(sf_dev->mdev);
	mlx5_devlink_मुक्त(devlink);
पूर्ण

अटल व्योम mlx5_sf_dev_shutकरोwn(काष्ठा auxiliary_device *adev)
अणु
	काष्ठा mlx5_sf_dev *sf_dev = container_of(adev, काष्ठा mlx5_sf_dev, adev);

	mlx5_unload_one(sf_dev->mdev);
पूर्ण

अटल स्थिर काष्ठा auxiliary_device_id mlx5_sf_dev_id_table[] = अणु
	अणु .name = MLX5_ADEV_NAME "." MLX5_SF_DEV_ID_NAME, पूर्ण,
	अणु पूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(auxiliary, mlx5_sf_dev_id_table);

अटल काष्ठा auxiliary_driver mlx5_sf_driver = अणु
	.name = MLX5_SF_DEV_ID_NAME,
	.probe = mlx5_sf_dev_probe,
	.हटाओ = mlx5_sf_dev_हटाओ,
	.shutकरोwn = mlx5_sf_dev_shutकरोwn,
	.id_table = mlx5_sf_dev_id_table,
पूर्ण;

पूर्णांक mlx5_sf_driver_रेजिस्टर(व्योम)
अणु
	वापस auxiliary_driver_रेजिस्टर(&mlx5_sf_driver);
पूर्ण

व्योम mlx5_sf_driver_unरेजिस्टर(व्योम)
अणु
	auxiliary_driver_unरेजिस्टर(&mlx5_sf_driver);
पूर्ण
