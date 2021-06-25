<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2008 Advanced Micro Devices, Inc.
 *
 * Author: Joerg Roedel <joerg.roedel@amd.com>
 */

#अगर_अघोषित _KERNEL_DMA_DEBUG_H
#घोषणा _KERNEL_DMA_DEBUG_H

#अगर_घोषित CONFIG_DMA_API_DEBUG
बाह्य व्योम debug_dma_map_page(काष्ठा device *dev, काष्ठा page *page,
			       माप_प्रकार offset, माप_प्रकार size,
			       पूर्णांक direction, dma_addr_t dma_addr);

बाह्य व्योम debug_dma_unmap_page(काष्ठा device *dev, dma_addr_t addr,
				 माप_प्रकार size, पूर्णांक direction);

बाह्य व्योम debug_dma_map_sg(काष्ठा device *dev, काष्ठा scatterlist *sg,
			     पूर्णांक nents, पूर्णांक mapped_ents, पूर्णांक direction);

बाह्य व्योम debug_dma_unmap_sg(काष्ठा device *dev, काष्ठा scatterlist *sglist,
			       पूर्णांक nelems, पूर्णांक dir);

बाह्य व्योम debug_dma_alloc_coherent(काष्ठा device *dev, माप_प्रकार size,
				     dma_addr_t dma_addr, व्योम *virt);

बाह्य व्योम debug_dma_मुक्त_coherent(काष्ठा device *dev, माप_प्रकार size,
				    व्योम *virt, dma_addr_t addr);

बाह्य व्योम debug_dma_map_resource(काष्ठा device *dev, phys_addr_t addr,
				   माप_प्रकार size, पूर्णांक direction,
				   dma_addr_t dma_addr);

बाह्य व्योम debug_dma_unmap_resource(काष्ठा device *dev, dma_addr_t dma_addr,
				     माप_प्रकार size, पूर्णांक direction);

बाह्य व्योम debug_dma_sync_single_क्रम_cpu(काष्ठा device *dev,
					  dma_addr_t dma_handle, माप_प्रकार size,
					  पूर्णांक direction);

बाह्य व्योम debug_dma_sync_single_क्रम_device(काष्ठा device *dev,
					     dma_addr_t dma_handle,
					     माप_प्रकार size, पूर्णांक direction);

बाह्य व्योम debug_dma_sync_sg_क्रम_cpu(काष्ठा device *dev,
				      काष्ठा scatterlist *sg,
				      पूर्णांक nelems, पूर्णांक direction);

बाह्य व्योम debug_dma_sync_sg_क्रम_device(काष्ठा device *dev,
					 काष्ठा scatterlist *sg,
					 पूर्णांक nelems, पूर्णांक direction);
#अन्यथा /* CONFIG_DMA_API_DEBUG */
अटल अंतरभूत व्योम debug_dma_map_page(काष्ठा device *dev, काष्ठा page *page,
				      माप_प्रकार offset, माप_प्रकार size,
				      पूर्णांक direction, dma_addr_t dma_addr)
अणु
पूर्ण

अटल अंतरभूत व्योम debug_dma_unmap_page(काष्ठा device *dev, dma_addr_t addr,
					माप_प्रकार size, पूर्णांक direction)
अणु
पूर्ण

अटल अंतरभूत व्योम debug_dma_map_sg(काष्ठा device *dev, काष्ठा scatterlist *sg,
				    पूर्णांक nents, पूर्णांक mapped_ents, पूर्णांक direction)
अणु
पूर्ण

अटल अंतरभूत व्योम debug_dma_unmap_sg(काष्ठा device *dev,
				      काष्ठा scatterlist *sglist,
				      पूर्णांक nelems, पूर्णांक dir)
अणु
पूर्ण

अटल अंतरभूत व्योम debug_dma_alloc_coherent(काष्ठा device *dev, माप_प्रकार size,
					    dma_addr_t dma_addr, व्योम *virt)
अणु
पूर्ण

अटल अंतरभूत व्योम debug_dma_मुक्त_coherent(काष्ठा device *dev, माप_प्रकार size,
					   व्योम *virt, dma_addr_t addr)
अणु
पूर्ण

अटल अंतरभूत व्योम debug_dma_map_resource(काष्ठा device *dev, phys_addr_t addr,
					  माप_प्रकार size, पूर्णांक direction,
					  dma_addr_t dma_addr)
अणु
पूर्ण

अटल अंतरभूत व्योम debug_dma_unmap_resource(काष्ठा device *dev,
					    dma_addr_t dma_addr, माप_प्रकार size,
					    पूर्णांक direction)
अणु
पूर्ण

अटल अंतरभूत व्योम debug_dma_sync_single_क्रम_cpu(काष्ठा device *dev,
						 dma_addr_t dma_handle,
						 माप_प्रकार size, पूर्णांक direction)
अणु
पूर्ण

अटल अंतरभूत व्योम debug_dma_sync_single_क्रम_device(काष्ठा device *dev,
						    dma_addr_t dma_handle,
						    माप_प्रकार size, पूर्णांक direction)
अणु
पूर्ण

अटल अंतरभूत व्योम debug_dma_sync_sg_क्रम_cpu(काष्ठा device *dev,
					     काष्ठा scatterlist *sg,
					     पूर्णांक nelems, पूर्णांक direction)
अणु
पूर्ण

अटल अंतरभूत व्योम debug_dma_sync_sg_क्रम_device(काष्ठा device *dev,
						काष्ठा scatterlist *sg,
						पूर्णांक nelems, पूर्णांक direction)
अणु
पूर्ण
#पूर्ण_अगर /* CONFIG_DMA_API_DEBUG */
#पूर्ण_अगर /* _KERNEL_DMA_DEBUG_H */
