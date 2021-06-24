<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2009-2010 Advanced Micro Devices, Inc.
 * Author: Joerg Roedel <jroedel@suse.de>
 */

#अगर_अघोषित AMD_IOMMU_H
#घोषणा AMD_IOMMU_H

#समावेश <linux/iommu.h>

#समावेश "amd_iommu_types.h"

बाह्य पूर्णांक amd_iommu_init_dma_ops(व्योम);
बाह्य पूर्णांक amd_iommu_init_passthrough(व्योम);
बाह्य irqवापस_t amd_iommu_पूर्णांक_thपढ़ो(पूर्णांक irq, व्योम *data);
बाह्य irqवापस_t amd_iommu_पूर्णांक_handler(पूर्णांक irq, व्योम *data);
बाह्य व्योम amd_iommu_apply_erratum_63(u16 devid);
बाह्य व्योम amd_iommu_reset_cmd_buffer(काष्ठा amd_iommu *iommu);
बाह्य पूर्णांक amd_iommu_init_devices(व्योम);
बाह्य व्योम amd_iommu_uninit_devices(व्योम);
बाह्य व्योम amd_iommu_init_notअगरier(व्योम);
बाह्य पूर्णांक amd_iommu_init_api(व्योम);

#अगर_घोषित CONFIG_AMD_IOMMU_DEBUGFS
व्योम amd_iommu_debugfs_setup(काष्ठा amd_iommu *iommu);
#अन्यथा
अटल अंतरभूत व्योम amd_iommu_debugfs_setup(काष्ठा amd_iommu *iommu) अणुपूर्ण
#पूर्ण_अगर

/* Needed क्रम पूर्णांकerrupt remapping */
बाह्य पूर्णांक amd_iommu_prepare(व्योम);
बाह्य पूर्णांक amd_iommu_enable(व्योम);
बाह्य व्योम amd_iommu_disable(व्योम);
बाह्य पूर्णांक amd_iommu_reenable(पूर्णांक);
बाह्य पूर्णांक amd_iommu_enable_faulting(व्योम);
बाह्य पूर्णांक amd_iommu_guest_ir;
बाह्य क्रमागत io_pgtable_fmt amd_iommu_pgtable;

/* IOMMUv2 specअगरic functions */
काष्ठा iommu_करोमुख्य;

बाह्य bool amd_iommu_v2_supported(व्योम);
बाह्य काष्ठा amd_iommu *get_amd_iommu(अचिन्हित पूर्णांक idx);
बाह्य u8 amd_iommu_pc_get_max_banks(अचिन्हित पूर्णांक idx);
बाह्य bool amd_iommu_pc_supported(व्योम);
बाह्य u8 amd_iommu_pc_get_max_counters(अचिन्हित पूर्णांक idx);
बाह्य पूर्णांक amd_iommu_pc_get_reg(काष्ठा amd_iommu *iommu, u8 bank, u8 cntr,
				u8 fxn, u64 *value);
बाह्य पूर्णांक amd_iommu_pc_set_reg(काष्ठा amd_iommu *iommu, u8 bank, u8 cntr,
				u8 fxn, u64 *value);

बाह्य पूर्णांक amd_iommu_रेजिस्टर_ppr_notअगरier(काष्ठा notअगरier_block *nb);
बाह्य पूर्णांक amd_iommu_unरेजिस्टर_ppr_notअगरier(काष्ठा notअगरier_block *nb);
बाह्य व्योम amd_iommu_करोमुख्य_direct_map(काष्ठा iommu_करोमुख्य *करोm);
बाह्य पूर्णांक amd_iommu_करोमुख्य_enable_v2(काष्ठा iommu_करोमुख्य *करोm, पूर्णांक pasids);
बाह्य पूर्णांक amd_iommu_flush_page(काष्ठा iommu_करोमुख्य *करोm, u32 pasid,
				u64 address);
बाह्य व्योम amd_iommu_update_and_flush_device_table(काष्ठा protection_करोमुख्य *करोमुख्य);
बाह्य व्योम amd_iommu_करोमुख्य_update(काष्ठा protection_करोमुख्य *करोमुख्य);
बाह्य व्योम amd_iommu_करोमुख्य_flush_complete(काष्ठा protection_करोमुख्य *करोमुख्य);
बाह्य व्योम amd_iommu_करोमुख्य_flush_tlb_pde(काष्ठा protection_करोमुख्य *करोमुख्य);
बाह्य पूर्णांक amd_iommu_flush_tlb(काष्ठा iommu_करोमुख्य *करोm, u32 pasid);
बाह्य पूर्णांक amd_iommu_करोमुख्य_set_gcr3(काष्ठा iommu_करोमुख्य *करोm, u32 pasid,
				     अचिन्हित दीर्घ cr3);
बाह्य पूर्णांक amd_iommu_करोमुख्य_clear_gcr3(काष्ठा iommu_करोमुख्य *करोm, u32 pasid);

#अगर_घोषित CONFIG_IRQ_REMAP
बाह्य पूर्णांक amd_iommu_create_irq_करोमुख्य(काष्ठा amd_iommu *iommu);
#अन्यथा
अटल अंतरभूत पूर्णांक amd_iommu_create_irq_करोमुख्य(काष्ठा amd_iommu *iommu)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

#घोषणा PPR_SUCCESS			0x0
#घोषणा PPR_INVALID			0x1
#घोषणा PPR_FAILURE			0xf

बाह्य पूर्णांक amd_iommu_complete_ppr(काष्ठा pci_dev *pdev, u32 pasid,
				  पूर्णांक status, पूर्णांक tag);

अटल अंतरभूत bool is_rd890_iommu(काष्ठा pci_dev *pdev)
अणु
	वापस (pdev->venकरोr == PCI_VENDOR_ID_ATI) &&
	       (pdev->device == PCI_DEVICE_ID_RD890_IOMMU);
पूर्ण

अटल अंतरभूत bool iommu_feature(काष्ठा amd_iommu *iommu, u64 mask)
अणु
	वापस !!(iommu->features & mask);
पूर्ण

अटल अंतरभूत u64 iommu_virt_to_phys(व्योम *vaddr)
अणु
	वापस (u64)__sme_set(virt_to_phys(vaddr));
पूर्ण

अटल अंतरभूत व्योम *iommu_phys_to_virt(अचिन्हित दीर्घ paddr)
अणु
	वापस phys_to_virt(__sme_clr(paddr));
पूर्ण

अटल अंतरभूत
व्योम amd_iommu_करोमुख्य_set_pt_root(काष्ठा protection_करोमुख्य *करोमुख्य, u64 root)
अणु
	atomic64_set(&करोमुख्य->iop.pt_root, root);
	करोमुख्य->iop.root = (u64 *)(root & PAGE_MASK);
	करोमुख्य->iop.mode = root & 7; /* lowest 3 bits encode pgtable mode */
पूर्ण

अटल अंतरभूत
व्योम amd_iommu_करोमुख्य_clr_pt_root(काष्ठा protection_करोमुख्य *करोमुख्य)
अणु
	amd_iommu_करोमुख्य_set_pt_root(करोमुख्य, 0);
पूर्ण


बाह्य bool translation_pre_enabled(काष्ठा amd_iommu *iommu);
बाह्य bool amd_iommu_is_attach_deferred(काष्ठा iommu_करोमुख्य *करोमुख्य,
					 काष्ठा device *dev);
बाह्य पूर्णांक __init add_special_device(u8 type, u8 id, u16 *devid,
				     bool cmd_line);

#अगर_घोषित CONFIG_DMI
व्योम amd_iommu_apply_ivrs_quirks(व्योम);
#अन्यथा
अटल अंतरभूत व्योम amd_iommu_apply_ivrs_quirks(व्योम) अणु पूर्ण
#पूर्ण_अगर

बाह्य व्योम amd_iommu_करोमुख्य_set_pgtable(काष्ठा protection_करोमुख्य *करोमुख्य,
					 u64 *root, पूर्णांक mode);
#पूर्ण_अगर
