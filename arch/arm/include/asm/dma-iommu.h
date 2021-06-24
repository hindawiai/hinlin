<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित ASMARM_DMA_IOMMU_H
#घोषणा ASMARM_DMA_IOMMU_H

#अगर_घोषित __KERNEL__

#समावेश <linux/mm_types.h>
#समावेश <linux/scatterlist.h>
#समावेश <linux/kref.h>

काष्ठा dma_iommu_mapping अणु
	/* iommu specअगरic data */
	काष्ठा iommu_करोमुख्य	*करोमुख्य;

	अचिन्हित दीर्घ		**biपंचांगaps;	/* array of biपंचांगaps */
	अचिन्हित पूर्णांक		nr_biपंचांगaps;	/* nr of elements in array */
	अचिन्हित पूर्णांक		extensions;
	माप_प्रकार			biपंचांगap_size;	/* size of a single biपंचांगap */
	माप_प्रकार			bits;		/* per biपंचांगap */
	dma_addr_t		base;

	spinlock_t		lock;
	काष्ठा kref		kref;
पूर्ण;

काष्ठा dma_iommu_mapping *
arm_iommu_create_mapping(काष्ठा bus_type *bus, dma_addr_t base, u64 size);

व्योम arm_iommu_release_mapping(काष्ठा dma_iommu_mapping *mapping);

पूर्णांक arm_iommu_attach_device(काष्ठा device *dev,
					काष्ठा dma_iommu_mapping *mapping);
व्योम arm_iommu_detach_device(काष्ठा device *dev);

#पूर्ण_अगर /* __KERNEL__ */
#पूर्ण_अगर
