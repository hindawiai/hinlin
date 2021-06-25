<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2016, Semihalf
 *	Author: Tomasz Nowicki <tn@semihalf.com>
 */

#अगर_अघोषित __ACPI_IORT_H__
#घोषणा __ACPI_IORT_H__

#समावेश <linux/acpi.h>
#समावेश <linux/fwnode.h>
#समावेश <linux/irqकरोमुख्य.h>

#घोषणा IORT_IRQ_MASK(irq)		(irq & 0xffffffffULL)
#घोषणा IORT_IRQ_TRIGGER_MASK(irq)	((irq >> 32) & 0xffffffffULL)

/*
 * PMCG model identअगरiers क्रम use in smmu pmu driver. Please note
 * that this is purely क्रम the use of software and has nothing to
 * करो with hardware or with IORT specअगरication.
 */
#घोषणा IORT_SMMU_V3_PMCG_GENERIC        0x00000000 /* Generic SMMUv3 PMCG */
#घोषणा IORT_SMMU_V3_PMCG_HISI_HIP08     0x00000001 /* HiSilicon HIP08 PMCG */

पूर्णांक iort_रेजिस्टर_करोमुख्य_token(पूर्णांक trans_id, phys_addr_t base,
			       काष्ठा fwnode_handle *fw_node);
व्योम iort_deरेजिस्टर_करोमुख्य_token(पूर्णांक trans_id);
काष्ठा fwnode_handle *iort_find_करोमुख्य_token(पूर्णांक trans_id);
#अगर_घोषित CONFIG_ACPI_IORT
व्योम acpi_iort_init(व्योम);
u32 iort_msi_map_id(काष्ठा device *dev, u32 id);
काष्ठा irq_करोमुख्य *iort_get_device_करोमुख्य(काष्ठा device *dev, u32 id,
					  क्रमागत irq_करोमुख्य_bus_token bus_token);
व्योम acpi_configure_pmsi_करोमुख्य(काष्ठा device *dev);
पूर्णांक iort_pmsi_get_dev_id(काष्ठा device *dev, u32 *dev_id);
/* IOMMU पूर्णांकerface */
व्योम iort_dma_setup(काष्ठा device *dev, u64 *dma_addr, u64 *size);
स्थिर काष्ठा iommu_ops *iort_iommu_configure_id(काष्ठा device *dev,
						स्थिर u32 *id_in);
पूर्णांक iort_iommu_msi_get_resv_regions(काष्ठा device *dev, काष्ठा list_head *head);
phys_addr_t acpi_iort_dma_get_max_cpu_address(व्योम);
#अन्यथा
अटल अंतरभूत व्योम acpi_iort_init(व्योम) अणु पूर्ण
अटल अंतरभूत u32 iort_msi_map_id(काष्ठा device *dev, u32 id)
अणु वापस id; पूर्ण
अटल अंतरभूत काष्ठा irq_करोमुख्य *iort_get_device_करोमुख्य(
	काष्ठा device *dev, u32 id, क्रमागत irq_करोमुख्य_bus_token bus_token)
अणु वापस शून्य; पूर्ण
अटल अंतरभूत व्योम acpi_configure_pmsi_करोमुख्य(काष्ठा device *dev) अणु पूर्ण
/* IOMMU पूर्णांकerface */
अटल अंतरभूत व्योम iort_dma_setup(काष्ठा device *dev, u64 *dma_addr,
				  u64 *size) अणु पूर्ण
अटल अंतरभूत स्थिर काष्ठा iommu_ops *iort_iommu_configure_id(
				      काष्ठा device *dev, स्थिर u32 *id_in)
अणु वापस शून्य; पूर्ण
अटल अंतरभूत
पूर्णांक iort_iommu_msi_get_resv_regions(काष्ठा device *dev, काष्ठा list_head *head)
अणु वापस 0; पूर्ण

अटल अंतरभूत phys_addr_t acpi_iort_dma_get_max_cpu_address(व्योम)
अणु वापस PHYS_ADDR_MAX; पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* __ACPI_IORT_H__ */
