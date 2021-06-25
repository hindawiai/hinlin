<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2014-2015 ARM Ltd.
 */
#अगर_अघोषित __DMA_IOMMU_H
#घोषणा __DMA_IOMMU_H

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/types.h>

#अगर_घोषित CONFIG_IOMMU_DMA
#समावेश <linux/dma-mapping.h>
#समावेश <linux/iommu.h>
#समावेश <linux/msi.h>

/* Doमुख्य management पूर्णांकerface क्रम IOMMU drivers */
पूर्णांक iommu_get_dma_cookie(काष्ठा iommu_करोमुख्य *करोमुख्य);
पूर्णांक iommu_get_msi_cookie(काष्ठा iommu_करोमुख्य *करोमुख्य, dma_addr_t base);
व्योम iommu_put_dma_cookie(काष्ठा iommu_करोमुख्य *करोमुख्य);

/* Setup call क्रम arch DMA mapping code */
व्योम iommu_setup_dma_ops(काष्ठा device *dev, u64 dma_base, u64 size);

/* The DMA API isn't _quite_ the whole story, though... */
/*
 * iommu_dma_prepare_msi() - Map the MSI page in the IOMMU device
 *
 * The MSI page will be stored in @desc.
 *
 * Return: 0 on success otherwise an error describing the failure.
 */
पूर्णांक iommu_dma_prepare_msi(काष्ठा msi_desc *desc, phys_addr_t msi_addr);

/* Update the MSI message अगर required. */
व्योम iommu_dma_compose_msi_msg(काष्ठा msi_desc *desc,
			       काष्ठा msi_msg *msg);

व्योम iommu_dma_get_resv_regions(काष्ठा device *dev, काष्ठा list_head *list);

व्योम iommu_dma_मुक्त_cpu_cached_iovas(अचिन्हित पूर्णांक cpu,
		काष्ठा iommu_करोमुख्य *करोमुख्य);

बाह्य bool iommu_dma_क्रमcedac;

#अन्यथा /* CONFIG_IOMMU_DMA */

काष्ठा iommu_करोमुख्य;
काष्ठा msi_desc;
काष्ठा msi_msg;
काष्ठा device;

अटल अंतरभूत व्योम iommu_setup_dma_ops(काष्ठा device *dev, u64 dma_base,
		u64 size)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक iommu_get_dma_cookie(काष्ठा iommu_करोमुख्य *करोमुख्य)
अणु
	वापस -ENODEV;
पूर्ण

अटल अंतरभूत पूर्णांक iommu_get_msi_cookie(काष्ठा iommu_करोमुख्य *करोमुख्य, dma_addr_t base)
अणु
	वापस -ENODEV;
पूर्ण

अटल अंतरभूत व्योम iommu_put_dma_cookie(काष्ठा iommu_करोमुख्य *करोमुख्य)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक iommu_dma_prepare_msi(काष्ठा msi_desc *desc,
					phys_addr_t msi_addr)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम iommu_dma_compose_msi_msg(काष्ठा msi_desc *desc,
					     काष्ठा msi_msg *msg)
अणु
पूर्ण

अटल अंतरभूत व्योम iommu_dma_get_resv_regions(काष्ठा device *dev, काष्ठा list_head *list)
अणु
पूर्ण

#पूर्ण_अगर	/* CONFIG_IOMMU_DMA */
#पूर्ण_अगर	/* __DMA_IOMMU_H */
