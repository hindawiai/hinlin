<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* include this file अगर the platक्रमm implements the dma_ DMA Mapping API
 * and wants to provide the pci_ DMA Mapping API in terms of it */

#अगर_अघोषित _ASM_GENERIC_PCI_DMA_COMPAT_H
#घोषणा _ASM_GENERIC_PCI_DMA_COMPAT_H

#समावेश <linux/dma-mapping.h>

/* This defines the direction arg to the DMA mapping routines. */
#घोषणा PCI_DMA_BIसूचीECTIONAL	DMA_BIसूचीECTIONAL
#घोषणा PCI_DMA_TODEVICE	DMA_TO_DEVICE
#घोषणा PCI_DMA_FROMDEVICE	DMA_FROM_DEVICE
#घोषणा PCI_DMA_NONE		DMA_NONE

अटल अंतरभूत व्योम *
pci_alloc_consistent(काष्ठा pci_dev *hwdev, माप_प्रकार size,
		     dma_addr_t *dma_handle)
अणु
	वापस dma_alloc_coherent(&hwdev->dev, size, dma_handle, GFP_ATOMIC);
पूर्ण

अटल अंतरभूत व्योम *
pci_zalloc_consistent(काष्ठा pci_dev *hwdev, माप_प्रकार size,
		      dma_addr_t *dma_handle)
अणु
	वापस dma_alloc_coherent(&hwdev->dev, size, dma_handle, GFP_ATOMIC);
पूर्ण

अटल अंतरभूत व्योम
pci_मुक्त_consistent(काष्ठा pci_dev *hwdev, माप_प्रकार size,
		    व्योम *vaddr, dma_addr_t dma_handle)
अणु
	dma_मुक्त_coherent(&hwdev->dev, size, vaddr, dma_handle);
पूर्ण

अटल अंतरभूत dma_addr_t
pci_map_single(काष्ठा pci_dev *hwdev, व्योम *ptr, माप_प्रकार size, पूर्णांक direction)
अणु
	वापस dma_map_single(&hwdev->dev, ptr, size, (क्रमागत dma_data_direction)direction);
पूर्ण

अटल अंतरभूत व्योम
pci_unmap_single(काष्ठा pci_dev *hwdev, dma_addr_t dma_addr,
		 माप_प्रकार size, पूर्णांक direction)
अणु
	dma_unmap_single(&hwdev->dev, dma_addr, size, (क्रमागत dma_data_direction)direction);
पूर्ण

अटल अंतरभूत dma_addr_t
pci_map_page(काष्ठा pci_dev *hwdev, काष्ठा page *page,
	     अचिन्हित दीर्घ offset, माप_प्रकार size, पूर्णांक direction)
अणु
	वापस dma_map_page(&hwdev->dev, page, offset, size, (क्रमागत dma_data_direction)direction);
पूर्ण

अटल अंतरभूत व्योम
pci_unmap_page(काष्ठा pci_dev *hwdev, dma_addr_t dma_address,
	       माप_प्रकार size, पूर्णांक direction)
अणु
	dma_unmap_page(&hwdev->dev, dma_address, size, (क्रमागत dma_data_direction)direction);
पूर्ण

अटल अंतरभूत पूर्णांक
pci_map_sg(काष्ठा pci_dev *hwdev, काष्ठा scatterlist *sg,
	   पूर्णांक nents, पूर्णांक direction)
अणु
	वापस dma_map_sg(&hwdev->dev, sg, nents, (क्रमागत dma_data_direction)direction);
पूर्ण

अटल अंतरभूत व्योम
pci_unmap_sg(काष्ठा pci_dev *hwdev, काष्ठा scatterlist *sg,
	     पूर्णांक nents, पूर्णांक direction)
अणु
	dma_unmap_sg(&hwdev->dev, sg, nents, (क्रमागत dma_data_direction)direction);
पूर्ण

अटल अंतरभूत व्योम
pci_dma_sync_single_क्रम_cpu(काष्ठा pci_dev *hwdev, dma_addr_t dma_handle,
		    माप_प्रकार size, पूर्णांक direction)
अणु
	dma_sync_single_क्रम_cpu(&hwdev->dev, dma_handle, size, (क्रमागत dma_data_direction)direction);
पूर्ण

अटल अंतरभूत व्योम
pci_dma_sync_single_क्रम_device(काष्ठा pci_dev *hwdev, dma_addr_t dma_handle,
		    माप_प्रकार size, पूर्णांक direction)
अणु
	dma_sync_single_क्रम_device(&hwdev->dev, dma_handle, size, (क्रमागत dma_data_direction)direction);
पूर्ण

अटल अंतरभूत व्योम
pci_dma_sync_sg_क्रम_cpu(काष्ठा pci_dev *hwdev, काष्ठा scatterlist *sg,
		पूर्णांक nelems, पूर्णांक direction)
अणु
	dma_sync_sg_क्रम_cpu(&hwdev->dev, sg, nelems, (क्रमागत dma_data_direction)direction);
पूर्ण

अटल अंतरभूत व्योम
pci_dma_sync_sg_क्रम_device(काष्ठा pci_dev *hwdev, काष्ठा scatterlist *sg,
		पूर्णांक nelems, पूर्णांक direction)
अणु
	dma_sync_sg_क्रम_device(&hwdev->dev, sg, nelems, (क्रमागत dma_data_direction)direction);
पूर्ण

अटल अंतरभूत पूर्णांक
pci_dma_mapping_error(काष्ठा pci_dev *pdev, dma_addr_t dma_addr)
अणु
	वापस dma_mapping_error(&pdev->dev, dma_addr);
पूर्ण

#अगर_घोषित CONFIG_PCI
अटल अंतरभूत पूर्णांक pci_set_dma_mask(काष्ठा pci_dev *dev, u64 mask)
अणु
	वापस dma_set_mask(&dev->dev, mask);
पूर्ण

अटल अंतरभूत पूर्णांक pci_set_consistent_dma_mask(काष्ठा pci_dev *dev, u64 mask)
अणु
	वापस dma_set_coherent_mask(&dev->dev, mask);
पूर्ण
#अन्यथा
अटल अंतरभूत पूर्णांक pci_set_dma_mask(काष्ठा pci_dev *dev, u64 mask)
अणु वापस -EIO; पूर्ण
अटल अंतरभूत पूर्णांक pci_set_consistent_dma_mask(काष्ठा pci_dev *dev, u64 mask)
अणु वापस -EIO; पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर
