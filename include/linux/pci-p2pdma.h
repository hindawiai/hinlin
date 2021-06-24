<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * PCI Peer 2 Peer DMA support.
 *
 * Copyright (c) 2016-2018, Logan Gunthorpe
 * Copyright (c) 2016-2017, Microsemi Corporation
 * Copyright (c) 2017, Christoph Hellwig
 * Copyright (c) 2018, Eideticom Inc.
 */

#अगर_अघोषित _LINUX_PCI_P2PDMA_H
#घोषणा _LINUX_PCI_P2PDMA_H

#समावेश <linux/pci.h>

काष्ठा block_device;
काष्ठा scatterlist;

#अगर_घोषित CONFIG_PCI_P2PDMA
पूर्णांक pci_p2pdma_add_resource(काष्ठा pci_dev *pdev, पूर्णांक bar, माप_प्रकार size,
		u64 offset);
पूर्णांक pci_p2pdma_distance_many(काष्ठा pci_dev *provider, काष्ठा device **clients,
			     पूर्णांक num_clients, bool verbose);
bool pci_has_p2pmem(काष्ठा pci_dev *pdev);
काष्ठा pci_dev *pci_p2pmem_find_many(काष्ठा device **clients, पूर्णांक num_clients);
व्योम *pci_alloc_p2pmem(काष्ठा pci_dev *pdev, माप_प्रकार size);
व्योम pci_मुक्त_p2pmem(काष्ठा pci_dev *pdev, व्योम *addr, माप_प्रकार size);
pci_bus_addr_t pci_p2pmem_virt_to_bus(काष्ठा pci_dev *pdev, व्योम *addr);
काष्ठा scatterlist *pci_p2pmem_alloc_sgl(काष्ठा pci_dev *pdev,
					 अचिन्हित पूर्णांक *nents, u32 length);
व्योम pci_p2pmem_मुक्त_sgl(काष्ठा pci_dev *pdev, काष्ठा scatterlist *sgl);
व्योम pci_p2pmem_publish(काष्ठा pci_dev *pdev, bool publish);
पूर्णांक pci_p2pdma_map_sg_attrs(काष्ठा device *dev, काष्ठा scatterlist *sg,
		पूर्णांक nents, क्रमागत dma_data_direction dir, अचिन्हित दीर्घ attrs);
व्योम pci_p2pdma_unmap_sg_attrs(काष्ठा device *dev, काष्ठा scatterlist *sg,
		पूर्णांक nents, क्रमागत dma_data_direction dir, अचिन्हित दीर्घ attrs);
पूर्णांक pci_p2pdma_enable_store(स्थिर अक्षर *page, काष्ठा pci_dev **p2p_dev,
			    bool *use_p2pdma);
sमाप_प्रकार pci_p2pdma_enable_show(अक्षर *page, काष्ठा pci_dev *p2p_dev,
			       bool use_p2pdma);
#अन्यथा /* CONFIG_PCI_P2PDMA */
अटल अंतरभूत पूर्णांक pci_p2pdma_add_resource(काष्ठा pci_dev *pdev, पूर्णांक bar,
		माप_प्रकार size, u64 offset)
अणु
	वापस -EOPNOTSUPP;
पूर्ण
अटल अंतरभूत पूर्णांक pci_p2pdma_distance_many(काष्ठा pci_dev *provider,
	काष्ठा device **clients, पूर्णांक num_clients, bool verbose)
अणु
	वापस -1;
पूर्ण
अटल अंतरभूत bool pci_has_p2pmem(काष्ठा pci_dev *pdev)
अणु
	वापस false;
पूर्ण
अटल अंतरभूत काष्ठा pci_dev *pci_p2pmem_find_many(काष्ठा device **clients,
						   पूर्णांक num_clients)
अणु
	वापस शून्य;
पूर्ण
अटल अंतरभूत व्योम *pci_alloc_p2pmem(काष्ठा pci_dev *pdev, माप_प्रकार size)
अणु
	वापस शून्य;
पूर्ण
अटल अंतरभूत व्योम pci_मुक्त_p2pmem(काष्ठा pci_dev *pdev, व्योम *addr,
		माप_प्रकार size)
अणु
पूर्ण
अटल अंतरभूत pci_bus_addr_t pci_p2pmem_virt_to_bus(काष्ठा pci_dev *pdev,
						    व्योम *addr)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत काष्ठा scatterlist *pci_p2pmem_alloc_sgl(काष्ठा pci_dev *pdev,
		अचिन्हित पूर्णांक *nents, u32 length)
अणु
	वापस शून्य;
पूर्ण
अटल अंतरभूत व्योम pci_p2pmem_मुक्त_sgl(काष्ठा pci_dev *pdev,
		काष्ठा scatterlist *sgl)
अणु
पूर्ण
अटल अंतरभूत व्योम pci_p2pmem_publish(काष्ठा pci_dev *pdev, bool publish)
अणु
पूर्ण
अटल अंतरभूत पूर्णांक pci_p2pdma_map_sg_attrs(काष्ठा device *dev,
		काष्ठा scatterlist *sg, पूर्णांक nents, क्रमागत dma_data_direction dir,
		अचिन्हित दीर्घ attrs)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत व्योम pci_p2pdma_unmap_sg_attrs(काष्ठा device *dev,
		काष्ठा scatterlist *sg, पूर्णांक nents, क्रमागत dma_data_direction dir,
		अचिन्हित दीर्घ attrs)
अणु
पूर्ण
अटल अंतरभूत पूर्णांक pci_p2pdma_enable_store(स्थिर अक्षर *page,
		काष्ठा pci_dev **p2p_dev, bool *use_p2pdma)
अणु
	*use_p2pdma = false;
	वापस 0;
पूर्ण
अटल अंतरभूत sमाप_प्रकार pci_p2pdma_enable_show(अक्षर *page,
		काष्ठा pci_dev *p2p_dev, bool use_p2pdma)
अणु
	वापस प्र_लिखो(page, "none\n");
पूर्ण
#पूर्ण_अगर /* CONFIG_PCI_P2PDMA */


अटल अंतरभूत पूर्णांक pci_p2pdma_distance(काष्ठा pci_dev *provider,
	काष्ठा device *client, bool verbose)
अणु
	वापस pci_p2pdma_distance_many(provider, &client, 1, verbose);
पूर्ण

अटल अंतरभूत काष्ठा pci_dev *pci_p2pmem_find(काष्ठा device *client)
अणु
	वापस pci_p2pmem_find_many(&client, 1);
पूर्ण

अटल अंतरभूत पूर्णांक pci_p2pdma_map_sg(काष्ठा device *dev, काष्ठा scatterlist *sg,
				    पूर्णांक nents, क्रमागत dma_data_direction dir)
अणु
	वापस pci_p2pdma_map_sg_attrs(dev, sg, nents, dir, 0);
पूर्ण

अटल अंतरभूत व्योम pci_p2pdma_unmap_sg(काष्ठा device *dev,
		काष्ठा scatterlist *sg, पूर्णांक nents, क्रमागत dma_data_direction dir)
अणु
	pci_p2pdma_unmap_sg_attrs(dev, sg, nents, dir, 0);
पूर्ण

#पूर्ण_अगर /* _LINUX_PCI_P2P_H */
