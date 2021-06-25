<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * MDEV driver
 *
 * Copyright (c) 2016, NVIDIA CORPORATION. All rights reserved.
 *     Author: Neo Jia <cjia@nvidia.com>
 *             Kirti Wankhede <kwankhede@nvidia.com>
 */

#समावेश <linux/device.h>
#समावेश <linux/iommu.h>
#समावेश <linux/mdev.h>

#समावेश "mdev_private.h"

अटल पूर्णांक mdev_attach_iommu(काष्ठा mdev_device *mdev)
अणु
	पूर्णांक ret;
	काष्ठा iommu_group *group;

	group = iommu_group_alloc();
	अगर (IS_ERR(group))
		वापस PTR_ERR(group);

	ret = iommu_group_add_device(group, &mdev->dev);
	अगर (!ret)
		dev_info(&mdev->dev, "MDEV: group_id = %d\n",
			 iommu_group_id(group));

	iommu_group_put(group);
	वापस ret;
पूर्ण

अटल व्योम mdev_detach_iommu(काष्ठा mdev_device *mdev)
अणु
	iommu_group_हटाओ_device(&mdev->dev);
	dev_info(&mdev->dev, "MDEV: detaching iommu\n");
पूर्ण

अटल पूर्णांक mdev_probe(काष्ठा device *dev)
अणु
	काष्ठा mdev_driver *drv =
		container_of(dev->driver, काष्ठा mdev_driver, driver);
	काष्ठा mdev_device *mdev = to_mdev_device(dev);
	पूर्णांक ret;

	ret = mdev_attach_iommu(mdev);
	अगर (ret)
		वापस ret;

	अगर (drv->probe) अणु
		ret = drv->probe(mdev);
		अगर (ret)
			mdev_detach_iommu(mdev);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक mdev_हटाओ(काष्ठा device *dev)
अणु
	काष्ठा mdev_driver *drv =
		container_of(dev->driver, काष्ठा mdev_driver, driver);
	काष्ठा mdev_device *mdev = to_mdev_device(dev);

	अगर (drv->हटाओ)
		drv->हटाओ(mdev);

	mdev_detach_iommu(mdev);

	वापस 0;
पूर्ण

काष्ठा bus_type mdev_bus_type = अणु
	.name		= "mdev",
	.probe		= mdev_probe,
	.हटाओ		= mdev_हटाओ,
पूर्ण;
EXPORT_SYMBOL_GPL(mdev_bus_type);

/**
 * mdev_रेजिस्टर_driver - रेजिस्टर a new MDEV driver
 * @drv: the driver to रेजिस्टर
 *
 * Returns a negative value on error, otherwise 0.
 **/
पूर्णांक mdev_रेजिस्टर_driver(काष्ठा mdev_driver *drv)
अणु
	/* initialize common driver fields */
	drv->driver.bus = &mdev_bus_type;

	/* रेजिस्टर with core */
	वापस driver_रेजिस्टर(&drv->driver);
पूर्ण
EXPORT_SYMBOL(mdev_रेजिस्टर_driver);

/*
 * mdev_unरेजिस्टर_driver - unरेजिस्टर MDEV driver
 * @drv: the driver to unरेजिस्टर
 */
व्योम mdev_unरेजिस्टर_driver(काष्ठा mdev_driver *drv)
अणु
	driver_unरेजिस्टर(&drv->driver);
पूर्ण
EXPORT_SYMBOL(mdev_unरेजिस्टर_driver);

पूर्णांक mdev_bus_रेजिस्टर(व्योम)
अणु
	वापस bus_रेजिस्टर(&mdev_bus_type);
पूर्ण

व्योम mdev_bus_unरेजिस्टर(व्योम)
अणु
	bus_unरेजिस्टर(&mdev_bus_type);
पूर्ण
