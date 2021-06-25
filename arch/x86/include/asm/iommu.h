<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_X86_IOMMU_H
#घोषणा _ASM_X86_IOMMU_H

#समावेश <linux/acpi.h>

#समावेश <यंत्र/e820/api.h>

बाह्य पूर्णांक क्रमce_iommu, no_iommu;
बाह्य पूर्णांक iommu_detected;

/* 10 seconds */
#घोषणा DMAR_OPERATION_TIMEOUT ((cycles_t) tsc_khz*10*1000)

अटल अंतरभूत पूर्णांक __init
arch_rmrr_sanity_check(काष्ठा acpi_dmar_reserved_memory *rmrr)
अणु
	u64 start = rmrr->base_address;
	u64 end = rmrr->end_address + 1;

	अगर (e820__mapped_all(start, end, E820_TYPE_RESERVED))
		वापस 0;

	pr_err(FW_BUG "No firmware reserved region can cover this RMRR [%#018Lx-%#018Lx], contact BIOS vendor for fixes\n",
	       start, end - 1);
	वापस -EINVAL;
पूर्ण

#पूर्ण_अगर /* _ASM_X86_IOMMU_H */
