<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Arch specअगरic extensions to काष्ठा device
 */
#अगर_अघोषित ASMARM_DEVICE_H
#घोषणा ASMARM_DEVICE_H

काष्ठा dev_archdata अणु
#अगर_घोषित CONFIG_DMABOUNCE
	काष्ठा dmabounce_device_info *dmabounce;
#पूर्ण_अगर
#अगर_घोषित CONFIG_ARM_DMA_USE_IOMMU
	काष्ठा dma_iommu_mapping	*mapping;
#पूर्ण_अगर
	अचिन्हित पूर्णांक dma_coherent:1;
	अचिन्हित पूर्णांक dma_ops_setup:1;
पूर्ण;

काष्ठा omap_device;

काष्ठा pdev_archdata अणु
#अगर_घोषित CONFIG_ARCH_OMAP
	काष्ठा omap_device *od;
#पूर्ण_अगर
पूर्ण;

#अगर_घोषित CONFIG_ARM_DMA_USE_IOMMU
#घोषणा to_dma_iommu_mapping(dev) ((dev)->archdata.mapping)
#अन्यथा
#घोषणा to_dma_iommu_mapping(dev) शून्य
#पूर्ण_अगर

#पूर्ण_अगर
