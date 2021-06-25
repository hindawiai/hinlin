<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Copyright (c) 2012 Samsung Electronics Co., Ltd.
// Author: Inki Dae <inki.dae@samsung.com>
// Author: Andrzej Hajda <a.hajda@samsung.com>

#समावेश <linux/dma-iommu.h>
#समावेश <linux/dma-map-ops.h>
#समावेश <linux/iommu.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश <drm/drm_prपूर्णांक.h>
#समावेश <drm/exynos_drm.h>

#समावेश "exynos_drm_drv.h"

#अगर defined(CONFIG_ARM_DMA_USE_IOMMU)
#समावेश <यंत्र/dma-iommu.h>
#अन्यथा
#घोषणा arm_iommu_create_mapping(...)	(अणु शून्य; पूर्ण)
#घोषणा arm_iommu_attach_device(...)	(अणु -ENODEV; पूर्ण)
#घोषणा arm_iommu_release_mapping(...)	(अणु पूर्ण)
#घोषणा arm_iommu_detach_device(...)	(अणु पूर्ण)
#घोषणा to_dma_iommu_mapping(dev) शून्य
#पूर्ण_अगर

#अगर !defined(CONFIG_IOMMU_DMA)
#घोषणा iommu_dma_init_करोमुख्य(...) (अणु -EINVAL; पूर्ण)
#पूर्ण_अगर

#घोषणा EXYNOS_DEV_ADDR_START	0x20000000
#घोषणा EXYNOS_DEV_ADDR_SIZE	0x40000000

/*
 * drm_iommu_attach_device- attach device to iommu mapping
 *
 * @drm_dev: DRM device
 * @subdrv_dev: device to be attach
 *
 * This function should be called by sub drivers to attach it to iommu
 * mapping.
 */
अटल पूर्णांक drm_iommu_attach_device(काष्ठा drm_device *drm_dev,
				काष्ठा device *subdrv_dev, व्योम **dma_priv)
अणु
	काष्ठा exynos_drm_निजी *priv = drm_dev->dev_निजी;
	पूर्णांक ret = 0;

	अगर (get_dma_ops(priv->dma_dev) != get_dma_ops(subdrv_dev)) अणु
		DRM_DEV_ERROR(subdrv_dev, "Device %s lacks support for IOMMU\n",
			  dev_name(subdrv_dev));
		वापस -EINVAL;
	पूर्ण

	dma_set_max_seg_size(subdrv_dev, DMA_BIT_MASK(32));
	अगर (IS_ENABLED(CONFIG_ARM_DMA_USE_IOMMU)) अणु
		/*
		 * Keep the original DMA mapping of the sub-device and
		 * restore it on Exynos DRM detach, otherwise the DMA
		 * framework considers it as IOMMU-less during the next
		 * probe (in हाल of deferred probe or modular build)
		 */
		*dma_priv = to_dma_iommu_mapping(subdrv_dev);
		अगर (*dma_priv)
			arm_iommu_detach_device(subdrv_dev);

		ret = arm_iommu_attach_device(subdrv_dev, priv->mapping);
	पूर्ण अन्यथा अगर (IS_ENABLED(CONFIG_IOMMU_DMA)) अणु
		ret = iommu_attach_device(priv->mapping, subdrv_dev);
	पूर्ण

	वापस ret;
पूर्ण

/*
 * drm_iommu_detach_device -detach device address space mapping from device
 *
 * @drm_dev: DRM device
 * @subdrv_dev: device to be detached
 *
 * This function should be called by sub drivers to detach it from iommu
 * mapping
 */
अटल व्योम drm_iommu_detach_device(काष्ठा drm_device *drm_dev,
				    काष्ठा device *subdrv_dev, व्योम **dma_priv)
अणु
	काष्ठा exynos_drm_निजी *priv = drm_dev->dev_निजी;

	अगर (IS_ENABLED(CONFIG_ARM_DMA_USE_IOMMU)) अणु
		arm_iommu_detach_device(subdrv_dev);
		arm_iommu_attach_device(subdrv_dev, *dma_priv);
	पूर्ण अन्यथा अगर (IS_ENABLED(CONFIG_IOMMU_DMA))
		iommu_detach_device(priv->mapping, subdrv_dev);
पूर्ण

पूर्णांक exynos_drm_रेजिस्टर_dma(काष्ठा drm_device *drm, काष्ठा device *dev,
			    व्योम **dma_priv)
अणु
	काष्ठा exynos_drm_निजी *priv = drm->dev_निजी;

	अगर (!priv->dma_dev) अणु
		priv->dma_dev = dev;
		DRM_INFO("Exynos DRM: using %s device for DMA mapping operations\n",
			 dev_name(dev));
	पूर्ण

	अगर (!IS_ENABLED(CONFIG_EXYNOS_IOMMU))
		वापस 0;

	अगर (!priv->mapping) अणु
		व्योम *mapping;

		अगर (IS_ENABLED(CONFIG_ARM_DMA_USE_IOMMU))
			mapping = arm_iommu_create_mapping(&platक्रमm_bus_type,
				EXYNOS_DEV_ADDR_START, EXYNOS_DEV_ADDR_SIZE);
		अन्यथा अगर (IS_ENABLED(CONFIG_IOMMU_DMA))
			mapping = iommu_get_करोमुख्य_क्रम_dev(priv->dma_dev);

		अगर (IS_ERR(mapping))
			वापस PTR_ERR(mapping);
		priv->mapping = mapping;
	पूर्ण

	वापस drm_iommu_attach_device(drm, dev, dma_priv);
पूर्ण

व्योम exynos_drm_unरेजिस्टर_dma(काष्ठा drm_device *drm, काष्ठा device *dev,
			       व्योम **dma_priv)
अणु
	अगर (IS_ENABLED(CONFIG_EXYNOS_IOMMU))
		drm_iommu_detach_device(drm, dev, dma_priv);
पूर्ण

व्योम exynos_drm_cleanup_dma(काष्ठा drm_device *drm)
अणु
	काष्ठा exynos_drm_निजी *priv = drm->dev_निजी;

	अगर (!IS_ENABLED(CONFIG_EXYNOS_IOMMU))
		वापस;

	arm_iommu_release_mapping(priv->mapping);
	priv->mapping = शून्य;
	priv->dma_dev = शून्य;
पूर्ण
