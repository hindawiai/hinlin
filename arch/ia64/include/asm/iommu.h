<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_IA64_IOMMU_H
#घोषणा _ASM_IA64_IOMMU_H 1

#समावेश <linux/acpi.h>

/* 10 seconds */
#घोषणा DMAR_OPERATION_TIMEOUT (((cycles_t) local_cpu_data->itc_freq)*10)

बाह्य व्योम no_iommu_init(व्योम);
#अगर_घोषित	CONFIG_INTEL_IOMMU
बाह्य पूर्णांक क्रमce_iommu, no_iommu;
बाह्य पूर्णांक iommu_detected;

अटल अंतरभूत पूर्णांक __init
arch_rmrr_sanity_check(काष्ठा acpi_dmar_reserved_memory *rmrr) अणु वापस 0; पूर्ण
#अन्यथा
#घोषणा no_iommu		(1)
#घोषणा iommu_detected		(0)
#पूर्ण_अगर

#पूर्ण_अगर
