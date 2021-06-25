<शैली गुरु>
/*
 * Copyright (c) 2013-2015, Mellanox Technologies. All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the मुख्य directory of this source tree, or the
 * OpenIB.org BSD license below:
 *
 *     Redistribution and use in source and binary क्रमms, with or
 *     without modअगरication, are permitted provided that the following
 *     conditions are met:
 *
 *      - Redistributions of source code must retain the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer.
 *
 *      - Redistributions in binary क्रमm must reproduce the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer in the करोcumentation and/or other materials
 *        provided with the distribution.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#समावेश <linux/mlx5/driver.h>
#समावेश <linux/mlx5/eचयन.h>
#समावेश <linux/mlx5/mlx5_अगरc_vdpa.h>
#समावेश "mlx5_core.h"

/* पूर्णांकf dev list mutex */
अटल DEFINE_MUTEX(mlx5_पूर्णांकf_mutex);
अटल DEFINE_IDA(mlx5_adev_ida);

अटल bool is_eth_rep_supported(काष्ठा mlx5_core_dev *dev)
अणु
	अगर (!IS_ENABLED(CONFIG_MLX5_ESWITCH))
		वापस false;

	अगर (!MLX5_ESWITCH_MANAGER(dev))
		वापस false;

	अगर (!is_mdev_चयनdev_mode(dev))
		वापस false;

	वापस true;
पूर्ण

अटल bool is_eth_supported(काष्ठा mlx5_core_dev *dev)
अणु
	अगर (!IS_ENABLED(CONFIG_MLX5_CORE_EN))
		वापस false;

	अगर (MLX5_CAP_GEN(dev, port_type) != MLX5_CAP_PORT_TYPE_ETH)
		वापस false;

	अगर (!MLX5_CAP_GEN(dev, eth_net_offloads)) अणु
		mlx5_core_warn(dev, "Missing eth_net_offloads capability\n");
		वापस false;
	पूर्ण

	अगर (!MLX5_CAP_GEN(dev, nic_flow_table)) अणु
		mlx5_core_warn(dev, "Missing nic_flow_table capability\n");
		वापस false;
	पूर्ण

	अगर (!MLX5_CAP_ETH(dev, csum_cap)) अणु
		mlx5_core_warn(dev, "Missing csum_cap capability\n");
		वापस false;
	पूर्ण

	अगर (!MLX5_CAP_ETH(dev, max_lso_cap)) अणु
		mlx5_core_warn(dev, "Missing max_lso_cap capability\n");
		वापस false;
	पूर्ण

	अगर (!MLX5_CAP_ETH(dev, vlan_cap)) अणु
		mlx5_core_warn(dev, "Missing vlan_cap capability\n");
		वापस false;
	पूर्ण

	अगर (!MLX5_CAP_ETH(dev, rss_ind_tbl_cap)) अणु
		mlx5_core_warn(dev, "Missing rss_ind_tbl_cap capability\n");
		वापस false;
	पूर्ण

	अगर (MLX5_CAP_FLOWTABLE(dev,
			       flow_table_properties_nic_receive.max_ft_level) < 3) अणु
		mlx5_core_warn(dev, "max_ft_level < 3\n");
		वापस false;
	पूर्ण

	अगर (!MLX5_CAP_ETH(dev, self_lb_en_modअगरiable))
		mlx5_core_warn(dev, "Self loop back prevention is not supported\n");
	अगर (!MLX5_CAP_GEN(dev, cq_moderation))
		mlx5_core_warn(dev, "CQ moderation is not supported\n");

	वापस true;
पूर्ण

अटल bool is_vnet_supported(काष्ठा mlx5_core_dev *dev)
अणु
	अगर (!IS_ENABLED(CONFIG_MLX5_VDPA_NET))
		वापस false;

	अगर (mlx5_core_is_pf(dev))
		वापस false;

	अगर (!(MLX5_CAP_GEN_64(dev, general_obj_types) &
	      MLX5_GENERAL_OBJ_TYPES_CAP_VIRTIO_NET_Q))
		वापस false;

	अगर (!(MLX5_CAP_DEV_VDPA_EMULATION(dev, event_mode) &
	      MLX5_VIRTIO_Q_EVENT_MODE_QP_MODE))
		वापस false;

	अगर (!MLX5_CAP_DEV_VDPA_EMULATION(dev, eth_frame_offload_type))
		वापस false;

	वापस true;
पूर्ण

अटल bool is_ib_rep_supported(काष्ठा mlx5_core_dev *dev)
अणु
	अगर (!IS_ENABLED(CONFIG_MLX5_INFINIBAND))
		वापस false;

	अगर (dev->priv.flags & MLX5_PRIV_FLAGS_DISABLE_IB_ADEV)
		वापस false;

	अगर (!is_eth_rep_supported(dev))
		वापस false;

	अगर (!MLX5_ESWITCH_MANAGER(dev))
		वापस false;

	अगर (!is_mdev_चयनdev_mode(dev))
		वापस false;

	अगर (mlx5_core_mp_enabled(dev))
		वापस false;

	वापस true;
पूर्ण

अटल bool is_mp_supported(काष्ठा mlx5_core_dev *dev)
अणु
	अगर (!IS_ENABLED(CONFIG_MLX5_INFINIBAND))
		वापस false;

	अगर (dev->priv.flags & MLX5_PRIV_FLAGS_DISABLE_IB_ADEV)
		वापस false;

	अगर (is_ib_rep_supported(dev))
		वापस false;

	अगर (MLX5_CAP_GEN(dev, port_type) != MLX5_CAP_PORT_TYPE_ETH)
		वापस false;

	अगर (!mlx5_core_is_mp_slave(dev))
		वापस false;

	वापस true;
पूर्ण

अटल bool is_ib_supported(काष्ठा mlx5_core_dev *dev)
अणु
	अगर (!IS_ENABLED(CONFIG_MLX5_INFINIBAND))
		वापस false;

	अगर (dev->priv.flags & MLX5_PRIV_FLAGS_DISABLE_IB_ADEV)
		वापस false;

	अगर (is_ib_rep_supported(dev))
		वापस false;

	अगर (is_mp_supported(dev))
		वापस false;

	वापस true;
पूर्ण

क्रमागत अणु
	MLX5_INTERFACE_PROTOCOL_ETH,
	MLX5_INTERFACE_PROTOCOL_ETH_REP,

	MLX5_INTERFACE_PROTOCOL_IB,
	MLX5_INTERFACE_PROTOCOL_IB_REP,
	MLX5_INTERFACE_PROTOCOL_MPIB,

	MLX5_INTERFACE_PROTOCOL_VNET,
पूर्ण;

अटल स्थिर काष्ठा mlx5_adev_device अणु
	स्थिर अक्षर *suffix;
	bool (*is_supported)(काष्ठा mlx5_core_dev *dev);
पूर्ण mlx5_adev_devices[] = अणु
	[MLX5_INTERFACE_PROTOCOL_VNET] = अणु .suffix = "vnet",
					   .is_supported = &is_vnet_supported पूर्ण,
	[MLX5_INTERFACE_PROTOCOL_IB] = अणु .suffix = "rdma",
					 .is_supported = &is_ib_supported पूर्ण,
	[MLX5_INTERFACE_PROTOCOL_ETH] = अणु .suffix = "eth",
					  .is_supported = &is_eth_supported पूर्ण,
	[MLX5_INTERFACE_PROTOCOL_ETH_REP] = अणु .suffix = "eth-rep",
					   .is_supported = &is_eth_rep_supported पूर्ण,
	[MLX5_INTERFACE_PROTOCOL_IB_REP] = अणु .suffix = "rdma-rep",
					   .is_supported = &is_ib_rep_supported पूर्ण,
	[MLX5_INTERFACE_PROTOCOL_MPIB] = अणु .suffix = "multiport",
					   .is_supported = &is_mp_supported पूर्ण,
पूर्ण;

पूर्णांक mlx5_adev_idx_alloc(व्योम)
अणु
	वापस ida_alloc(&mlx5_adev_ida, GFP_KERNEL);
पूर्ण

व्योम mlx5_adev_idx_मुक्त(पूर्णांक idx)
अणु
	ida_मुक्त(&mlx5_adev_ida, idx);
पूर्ण

पूर्णांक mlx5_adev_init(काष्ठा mlx5_core_dev *dev)
अणु
	काष्ठा mlx5_priv *priv = &dev->priv;

	priv->adev = kसुस्मृति(ARRAY_SIZE(mlx5_adev_devices),
			     माप(काष्ठा mlx5_adev *), GFP_KERNEL);
	अगर (!priv->adev)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

व्योम mlx5_adev_cleanup(काष्ठा mlx5_core_dev *dev)
अणु
	काष्ठा mlx5_priv *priv = &dev->priv;

	kमुक्त(priv->adev);
पूर्ण

अटल व्योम adev_release(काष्ठा device *dev)
अणु
	काष्ठा mlx5_adev *mlx5_adev =
		container_of(dev, काष्ठा mlx5_adev, adev.dev);
	काष्ठा mlx5_priv *priv = &mlx5_adev->mdev->priv;
	पूर्णांक idx = mlx5_adev->idx;

	kमुक्त(mlx5_adev);
	priv->adev[idx] = शून्य;
पूर्ण

अटल काष्ठा mlx5_adev *add_adev(काष्ठा mlx5_core_dev *dev, पूर्णांक idx)
अणु
	स्थिर अक्षर *suffix = mlx5_adev_devices[idx].suffix;
	काष्ठा auxiliary_device *adev;
	काष्ठा mlx5_adev *madev;
	पूर्णांक ret;

	madev = kzalloc(माप(*madev), GFP_KERNEL);
	अगर (!madev)
		वापस ERR_PTR(-ENOMEM);

	adev = &madev->adev;
	adev->id = dev->priv.adev_idx;
	adev->name = suffix;
	adev->dev.parent = dev->device;
	adev->dev.release = adev_release;
	madev->mdev = dev;
	madev->idx = idx;

	ret = auxiliary_device_init(adev);
	अगर (ret) अणु
		kमुक्त(madev);
		वापस ERR_PTR(ret);
	पूर्ण

	ret = auxiliary_device_add(adev);
	अगर (ret) अणु
		auxiliary_device_uninit(adev);
		वापस ERR_PTR(ret);
	पूर्ण
	वापस madev;
पूर्ण

अटल व्योम del_adev(काष्ठा auxiliary_device *adev)
अणु
	auxiliary_device_delete(adev);
	auxiliary_device_uninit(adev);
पूर्ण

पूर्णांक mlx5_attach_device(काष्ठा mlx5_core_dev *dev)
अणु
	काष्ठा mlx5_priv *priv = &dev->priv;
	काष्ठा auxiliary_device *adev;
	काष्ठा auxiliary_driver *adrv;
	पूर्णांक ret = 0, i;

	mutex_lock(&mlx5_पूर्णांकf_mutex);
	priv->flags &= ~MLX5_PRIV_FLAGS_DETACH;
	क्रम (i = 0; i < ARRAY_SIZE(mlx5_adev_devices); i++) अणु
		अगर (!priv->adev[i]) अणु
			bool is_supported = false;

			अगर (mlx5_adev_devices[i].is_supported)
				is_supported = mlx5_adev_devices[i].is_supported(dev);

			अगर (!is_supported)
				जारी;

			priv->adev[i] = add_adev(dev, i);
			अगर (IS_ERR(priv->adev[i])) अणु
				ret = PTR_ERR(priv->adev[i]);
				priv->adev[i] = शून्य;
			पूर्ण
		पूर्ण अन्यथा अणु
			adev = &priv->adev[i]->adev;

			/* Pay attention that this is not PCI driver that
			 * mlx5_core_dev is connected, but auxiliary driver.
			 *
			 * Here we can race of module unload with devlink
			 * reload, but we करोn't need to take extra lock because
			 * we are holding global mlx5_पूर्णांकf_mutex.
			 */
			अगर (!adev->dev.driver)
				जारी;
			adrv = to_auxiliary_drv(adev->dev.driver);

			अगर (adrv->resume)
				ret = adrv->resume(adev);
		पूर्ण
		अगर (ret) अणु
			mlx5_core_warn(dev, "Device[%d] (%s) failed to load\n",
				       i, mlx5_adev_devices[i].suffix);

			अवरोध;
		पूर्ण
	पूर्ण
	mutex_unlock(&mlx5_पूर्णांकf_mutex);
	वापस ret;
पूर्ण

व्योम mlx5_detach_device(काष्ठा mlx5_core_dev *dev)
अणु
	काष्ठा mlx5_priv *priv = &dev->priv;
	काष्ठा auxiliary_device *adev;
	काष्ठा auxiliary_driver *adrv;
	pm_message_t pm = अणुपूर्ण;
	पूर्णांक i;

	mutex_lock(&mlx5_पूर्णांकf_mutex);
	क्रम (i = ARRAY_SIZE(mlx5_adev_devices) - 1; i >= 0; i--) अणु
		अगर (!priv->adev[i])
			जारी;

		adev = &priv->adev[i]->adev;
		/* Auxiliary driver was unbind manually through sysfs */
		अगर (!adev->dev.driver)
			जाओ skip_suspend;

		adrv = to_auxiliary_drv(adev->dev.driver);

		अगर (adrv->suspend) अणु
			adrv->suspend(adev, pm);
			जारी;
		पूर्ण

skip_suspend:
		del_adev(&priv->adev[i]->adev);
		priv->adev[i] = शून्य;
	पूर्ण
	priv->flags |= MLX5_PRIV_FLAGS_DETACH;
	mutex_unlock(&mlx5_पूर्णांकf_mutex);
पूर्ण

पूर्णांक mlx5_रेजिस्टर_device(काष्ठा mlx5_core_dev *dev)
अणु
	पूर्णांक ret;

	mutex_lock(&mlx5_पूर्णांकf_mutex);
	dev->priv.flags &= ~MLX5_PRIV_FLAGS_DISABLE_ALL_ADEV;
	ret = mlx5_rescan_drivers_locked(dev);
	mutex_unlock(&mlx5_पूर्णांकf_mutex);
	अगर (ret)
		mlx5_unरेजिस्टर_device(dev);

	वापस ret;
पूर्ण

व्योम mlx5_unरेजिस्टर_device(काष्ठा mlx5_core_dev *dev)
अणु
	mutex_lock(&mlx5_पूर्णांकf_mutex);
	dev->priv.flags |= MLX5_PRIV_FLAGS_DISABLE_ALL_ADEV;
	mlx5_rescan_drivers_locked(dev);
	mutex_unlock(&mlx5_पूर्णांकf_mutex);
पूर्ण

अटल पूर्णांक add_drivers(काष्ठा mlx5_core_dev *dev)
अणु
	काष्ठा mlx5_priv *priv = &dev->priv;
	पूर्णांक i, ret = 0;

	क्रम (i = 0; i < ARRAY_SIZE(mlx5_adev_devices); i++) अणु
		bool is_supported = false;

		अगर (priv->adev[i])
			जारी;

		अगर (mlx5_adev_devices[i].is_supported)
			is_supported = mlx5_adev_devices[i].is_supported(dev);

		अगर (!is_supported)
			जारी;

		priv->adev[i] = add_adev(dev, i);
		अगर (IS_ERR(priv->adev[i])) अणु
			mlx5_core_warn(dev, "Device[%d] (%s) failed to load\n",
				       i, mlx5_adev_devices[i].suffix);
			/* We जारी to rescan drivers and leave to the caller
			 * to make decision अगर to release everything or जारी.
			 */
			ret = PTR_ERR(priv->adev[i]);
			priv->adev[i] = शून्य;
		पूर्ण
	पूर्ण
	वापस ret;
पूर्ण

अटल व्योम delete_drivers(काष्ठा mlx5_core_dev *dev)
अणु
	काष्ठा mlx5_priv *priv = &dev->priv;
	bool delete_all;
	पूर्णांक i;

	delete_all = priv->flags & MLX5_PRIV_FLAGS_DISABLE_ALL_ADEV;

	क्रम (i = ARRAY_SIZE(mlx5_adev_devices) - 1; i >= 0; i--) अणु
		bool is_supported = false;

		अगर (!priv->adev[i])
			जारी;

		अगर (mlx5_adev_devices[i].is_supported && !delete_all)
			is_supported = mlx5_adev_devices[i].is_supported(dev);

		अगर (is_supported)
			जारी;

		del_adev(&priv->adev[i]->adev);
		priv->adev[i] = शून्य;
	पूर्ण
पूर्ण

/* This function is used after mlx5_core_dev is reconfigured.
 */
पूर्णांक mlx5_rescan_drivers_locked(काष्ठा mlx5_core_dev *dev)
अणु
	काष्ठा mlx5_priv *priv = &dev->priv;

	lockdep_निश्चित_held(&mlx5_पूर्णांकf_mutex);
	अगर (priv->flags & MLX5_PRIV_FLAGS_DETACH)
		वापस 0;

	delete_drivers(dev);
	अगर (priv->flags & MLX5_PRIV_FLAGS_DISABLE_ALL_ADEV)
		वापस 0;

	वापस add_drivers(dev);
पूर्ण

अटल u32 mlx5_gen_pci_id(स्थिर काष्ठा mlx5_core_dev *dev)
अणु
	वापस (u32)((pci_करोमुख्य_nr(dev->pdev->bus) << 16) |
		     (dev->pdev->bus->number << 8) |
		     PCI_SLOT(dev->pdev->devfn));
पूर्ण

अटल पूर्णांक next_phys_dev(काष्ठा device *dev, स्थिर व्योम *data)
अणु
	काष्ठा mlx5_adev *madev = container_of(dev, काष्ठा mlx5_adev, adev.dev);
	काष्ठा mlx5_core_dev *mdev = madev->mdev;
	स्थिर काष्ठा mlx5_core_dev *curr = data;

	अगर (!mlx5_core_is_pf(mdev))
		वापस 0;

	अगर (mdev == curr)
		वापस 0;

	अगर (mlx5_gen_pci_id(mdev) != mlx5_gen_pci_id(curr))
		वापस 0;

	वापस 1;
पूर्ण

/* This function is called with two flows:
 * 1. During initialization of mlx5_core_dev and we करोn't need to lock it.
 * 2. During LAG configure stage and caller holds &mlx5_पूर्णांकf_mutex.
 */
काष्ठा mlx5_core_dev *mlx5_get_next_phys_dev(काष्ठा mlx5_core_dev *dev)
अणु
	काष्ठा auxiliary_device *adev;
	काष्ठा mlx5_adev *madev;

	अगर (!mlx5_core_is_pf(dev))
		वापस शून्य;

	adev = auxiliary_find_device(शून्य, dev, &next_phys_dev);
	अगर (!adev)
		वापस शून्य;

	madev = container_of(adev, काष्ठा mlx5_adev, adev);
	put_device(&adev->dev);
	वापस madev->mdev;
पूर्ण

व्योम mlx5_dev_list_lock(व्योम)
अणु
	mutex_lock(&mlx5_पूर्णांकf_mutex);
पूर्ण
व्योम mlx5_dev_list_unlock(व्योम)
अणु
	mutex_unlock(&mlx5_पूर्णांकf_mutex);
पूर्ण

पूर्णांक mlx5_dev_list_trylock(व्योम)
अणु
	वापस mutex_trylock(&mlx5_पूर्णांकf_mutex);
पूर्ण
