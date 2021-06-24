<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Arch specअगरic extensions to काष्ठा device
 */
#अगर_अघोषित _ASM_POWERPC_DEVICE_H
#घोषणा _ASM_POWERPC_DEVICE_H

काष्ठा device_node;
#अगर_घोषित CONFIG_PPC64
काष्ठा pci_dn;
काष्ठा iommu_table;
#पूर्ण_अगर

/*
 * Arch extensions to काष्ठा device.
 *
 * When adding fields, consider macio_add_one_device in
 * drivers/macपूर्णांकosh/macio_asic.c
 */
काष्ठा dev_archdata अणु
	/*
	 * These two used to be a जोड़. However, with the hybrid ops we need
	 * both so here we store both a DMA offset क्रम direct mappings and
	 * an iommu_table क्रम remapped DMA.
	 */
	dma_addr_t		dma_offset;

#अगर_घोषित CONFIG_PPC64
	काष्ठा iommu_table	*iommu_table_base;
#पूर्ण_अगर

#अगर_घोषित CONFIG_PPC64
	काष्ठा pci_dn		*pci_data;
#पूर्ण_अगर
#अगर_घोषित CONFIG_EEH
	काष्ठा eeh_dev		*edev;
#पूर्ण_अगर
#अगर_घोषित CONFIG_FAIL_IOMMU
	पूर्णांक fail_iommu;
#पूर्ण_अगर
#अगर_घोषित CONFIG_CXL_BASE
	काष्ठा cxl_context	*cxl_ctx;
#पूर्ण_अगर
#अगर_घोषित CONFIG_PCI_IOV
	व्योम *iov_data;
#पूर्ण_अगर
पूर्ण;

काष्ठा pdev_archdata अणु
	u64 dma_mask;
पूर्ण;

#पूर्ण_अगर /* _ASM_POWERPC_DEVICE_H */
